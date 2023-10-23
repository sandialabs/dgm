#ifndef DGM_REMOVE_FOR_RELEASE
/*=============================================================================
  Module:     Shallow Adjoint Module

  Contact:    S. Scott Collis

  Copyright:  (c)2013 Sandia National Laboratories
=============================================================================*/

/** \file  ShallowAdjoint.cpp
    \brief Adjoint for the 2d Shallow water equations
    \author Vincent Mousseau
    \author S. Scott Collis
*/

// system includes
#include <cmath>
#include <cassert>

// DGM includes
#include "Format.hpp"
#include "TimeInt.hpp"

// Reo includes
#include "Reo.hpp"
#include "ShallowAdjoint.hpp"
#include "ShallowState.hpp"
#include "ShallowObs.hpp"
#include "Wavetype.hpp"

namespace Reo {

// constructor
ShallowAdjoint::ShallowAdjoint(DGM::ArgList &args, const State* S,
                              const DGM::Comm::Ptr comm_, const int pinc) :
  Domain(args,comm_), Adjoint(S,pinc), Utmp(comm_) {

  // setup local pointer to State
  state = dynamic_cast<const ShallowState*>(state_);

  params["npredict"] = 0;              // Add npredict to parameter Table
  params.read( root+".inp" );          // re-read input file
  npredict = params["npredict"];

  Ordinal p, q;
  p = params["p"];                     // polynomial order
  p += p_inc;                          // increment polynomial order if needed
  comm->cout() << "ShallowAdjoint:  p = "<< p <<endl;
  if ( !(q=params["q"]) ) q = p + 2;   // number of quadrature points
  nsd = params["nsd"];                 // number of space dimensions

  // read arguments (overrides defaults and input file)
  parse_args( args );

  vector<string> field_names;          // Field names
  field_names.push_back("phi");

  // build a Field of Elements and Sides
  if (params["imesh"]) {
     error("ShallowAdjoint internal mesh not supported",-1);
  } else if (params["bmesh"]) {
    U.push_back( new Field(p, q, root, field_names[0],partition,1,
                           Reo::NumEqntype, p2i(SHALLOW),comm,p_inc));
  } else {
    U.push_back( new Field(p, q, root, field_names[0],partition,comm,p_inc));
  }

  // set some additional domain parameters
  ne = U[0]->ne;
  nsd = U[0]->nsd();

#ifdef REO_USE_GETSIDEMAPS
  setup_side_maps();
#endif

  if (nsd == 1) {
    comm->error("Reo::ShallowAdjoint: nsd must be 2");
  } else if (nsd == 2) {
    Nfields = 3;  // is equal to NFIELDS in Shallow.hpp
    field_names.push_back("uphi");
    field_names.push_back("vphi");
  } else if (nsd == 3) {
    comm->error("Reo::ShallowAdjoint: nsd must be 2");
  } else {
    comm->cerr() << "Illegal value for nsd = " << nsd
                 << " in Reo::ShallowAdjoint::ShallowAdjoint" << endl;
    comm->exit(DGM::FAILURE);
  }

  // build the rest of the vector field
  for (vField::size_type i=1; i<Nfields; i++)
    U.push_back( new Field( U[0], root, field_names[i] ) );

  // make auxiliary Fields using copy constructor
  for (vField::size_type i=0; i<Nfields; i++) {
    Ut.push_back( new Field( U[0], root, field_names[i] ) );
    Ustate.push_back( new Field( U[0], root, field_names[i] ) );
    Utmp.push_back( new Field( U[0], root, field_names[i] ) );
  }

  // set vField names
  U.set_name("Adjoint U");
  Ut.set_name("Adjoint Ut");
  Ustate.set_name("Adjoint base state");
  Utmp.set_name("Adjoint Utmp");

  // allocate workspace
  wk1.resize(20*max(Lmax(),Qmax()));
  wk2.resize(20*max(Lmax(),Qmax()));

  // make sure that storage is initialized
  zero_all_fields();

  // make analysis object
  response = Response::factory(U, this);

  // setup BC database
  setup_BCdb();

  // setup source term database
  setup_Sourcedb();

  // setup time integrator
  set_TimeInt();
}

// Need to override the default from Domain to use adjoint methods
void ShallowAdjoint::set_TimeInt( Ordinal ) {
  int inttype = params["inttype"];
  switch(inttype) {
  case TimeInt::FORWARD_EULER: {
    comm->cout() << "ShallowAdjoint:: using Forward Euler" << endl;
    time_int = new ForwardEuler( this );
    break; }
  case TimeInt::TVD_RK: {
    comm->cout() << "ShallowAdjoint:: using TVD RK" << endl;
    time_int = new TVD( this );
    break; }
  case TimeInt::RUNGE_KUTTA: {
    comm->cout() << "ShallowAdjoint:: using Runge-Kutta-4" << endl;
    time_int = new RungeKutta( this );
    break; }
  case TimeInt::SSPRK: {
    comm->cout() << "ShallowAdjoint:: using SSPRK" << endl;
    time_int = new SSPRK( this );
    break; }
  case TimeInt::LSRK14: {
    comm->cout() << "ShallowAdjoint:: using LSRK14" << endl;
    time_int = new LSRK14( this );
    break; }
  default:
    comm->cerr() << "ShallowAdjoint::set_TimeInt() "
                 << "Unsupported time integration type" << endl;
    comm->exit(DGM::FAILURE);
    break;
  }
}

void ShallowAdjoint::zero_all_fields() {
  Domain::zero_all_fields();
  Ustate.zero();
  Utmp.zero();
}

void ShallowAdjoint::time_derivative( vField &Us, vField &Uf ) {
  convection( Us, Uf );
  conv_source(Us,Uf);
  add_source(Us,Uf);
  project( Uf );
}

void ShallowAdjoint::set_end_condition() {
  Adjoint::set_end_condition();
  store(U, npredict, 0);
}

void ShallowAdjoint::set_end_condition(const dVector &X,
                                       const Scalar t_, const Ordinal step_) {
  Adjoint::set_end_condition(X, t_, step_);
  store(U, npredict, 0);
}

void ShallowAdjoint::prestep( vField &F, const Ordinal istep,
                              const Ordinal sstep, const Scalar time) {
  state->load_field( Ustate, istep, sstep);
  control->set_data( istep, sstep );
  objective->set_data( Ustate, istep, sstep );
  if (time_int->is_explicit()) {
    store(F, istep, sstep);
    computeGrad( F, Ustate, istep, sstep );
  }
}

void ShallowAdjoint::poststep( vField &F, const Ordinal istep,
                               const Ordinal sstep, const Scalar time) {
  if (time_int->is_implicit()) {
    store(F,istep,sstep);
    computeGrad( F, Ustate, istep, sstep );
  }
}

/** \todo Refactor to use nonblocking share sides. */
void ShallowAdjoint::convection( vField &Us, vField &Uf ) {
  Element *U[Nfields], *F[Nfields], *Fm[Nfields];
  dVector u1, u2, u3, Fx1, Fx2, Fx3, Fy1, Fy2, Fy3, d;

  Ustate.fill_sides();
  const_cast<ShallowState*>(state)->enforce_bc(Ustate);
  Ustate.share_sides();

  Us.fill_sides();
  enforce_bc(Us);
  Us.share_sides();

  convective_flux( Us, Uf );

  for (LocalSize e=0; e<Us[0]->ne; e++) {

    // local version of the state
    U[0] = Us[0]->el[e];
    U[1] = Us[1]->el[e];
    U[2] = Us[2]->el[e];

    // local version of the  flux
    F[0] = Uf[0]->el[e];
    F[1] = Uf[1]->el[e];
    F[2] = Uf[2]->el[e];

    // local version of the state solution
    Fm[0] = Ustate[0]->el[e];
    Fm[1] = Ustate[1]->el[e];
    Fm[2] = Ustate[2]->el[e];

    const Ordinal qtot = Us[0]->el[e]->qtot;

    Fx1.alias(wk1,0,qtot);
    Fx2.alias(wk1,1*qtot,qtot);
    Fx3.alias(wk1,2*qtot,qtot);
    Fy1.alias(wk1,4*qtot,qtot);
    Fy2.alias(wk1,5*qtot,qtot);
    Fy3.alias(wk1,6*qtot,qtot);
    d.alias  (wk1,7*qtot,qtot);

    // F(u(x)),x = (transpose(F^1_q) \lambda),x
    // G(u(x)),y = (transpose(F^2_q) \lambda),y

    for (LocalSize q=0; q<qtot; q++) {

      const Scalar w1 = U[0]->u[q];
      const Scalar w2 = U[1]->u[q];
      const Scalar w3 = U[2]->u[q];

      const Scalar phi   = Fm[0]->u[q];
      const Scalar theta = Fm[1]->u[q];
      const Scalar psi   = Fm[2]->u[q];

      Fx1[q] = ( (phi - ((theta*theta) / (phi*phi))) * w2 )
             + ( -(theta * psi / (phi*phi)) * w3 );
      Fx2[q] = w1 + ( (2.0 * theta / phi) * w2 )
             + ( (psi / phi) * w3 );
      Fx3[q] = ( (theta / phi) * w3 );

      Fy1[q] = ( -(theta * psi / (phi*phi)) * w2 )
             + ( (phi - ((psi*psi) / (phi*phi))) * w3 );
      Fy2[q] = ( (psi / phi) * w2 );
      Fy3[q] = w1 + ( (theta / phi) * w2 )
             + ( (2.0 * psi / phi) * w3 );
    }

    U[0]->gradient(Fx1, F[0]->u, 'x');
    U[0]->gradient(Fy1, d, 'y');
    dvadd(d,F[0]->u);

    U[1]->gradient(Fx2, F[1]->u, 'x');
    U[1]->gradient(Fy2, d, 'y');
    dvadd(d,F[1]->u);

    U[2]->gradient(Fx3, F[2]->u, 'x');
    U[2]->gradient(Fy3, d, 'y');
    dvadd(d,F[2]->u);

    // add the surface contribution
    for (vField::size_type i=0; i<Nfields; i++)
      U[i]->lift( F[i], F[i]->u );
  }
}

/** For descriptions of the numerical fluxes See: E.F. Toro, "Riemann
    Solvers and Numerical Methods for Fluid Dynamics," 2nd Edition,
    Springer, 1999, p. 305.
*/
void ShallowAdjoint::convective_flux(vField &Us, vField &Uf) {
  flux_type flux = LaxFriedrichs; //StegerWarming; //vanLeer;
  dVector sl(Nfields), sr(Nfields), f(Nfields), U(Nfields), Ua(Nfields);
  dVector slm(Nfields), srm(Nfields);
  Scalar ulm, clm, urm, crm;
  vector<Side *> Ssl(Nfields), Ssr(Nfields);
  vector<Side *> Sbl(Nfields), Sbr(Nfields);   // base flow field sides
  vector<Side *> Sfl(Nfields), Sfr(Nfields);
  dVector fpl(Nfields), fmr(Nfields),lam(Nfields);
  Scalar phil, thetal, psil;
  Scalar phir, thetar, psir;
  dVector w(Nfields);
#ifdef REO_USE_GETSIDEMAPS
  iVector mapl, mapr;
#endif
  dVector Fx(Nfields), Fy(Nfields);

  for (LocalSize e=0; e<Us[0]->ne; e++) {                // loop over elements
    Element* U = Us[0]->el[e];
    for (LocalSize i=0; i<Us[0]->el[e]->nSides(); i++) { // loop over sides
      if (Us[0]->el[e]->side[i]->master()) {             // compute if master
        const LocalSize qtot =
            Us[0]->el[e]->side[i]->qtot();               // quad pts on side

        for (vField::size_type ni=0; ni<Nfields; ni++) {
          Ssl[ni] = Us[ni]->el[e]->side[i];            // left state side
          Ssr[ni] = Us[ni]->el[e]->side[i]->link;      // right state side
          Sfl[ni] = Uf[ni]->el[e]->side[i];            // left flux side
          Sfr[ni] = Uf[ni]->el[e]->side[i]->link;      // right flux side
          Sbl[ni] = Ustate[ni]->el[e]->side[i];        // left base side
          Sbr[ni] = Ustate[ni]->el[e]->side[i]->link;  // right base side
        }
#ifdef REO_USE_GETSIDEMAPS
        get_side_maps( Ssl[0], Ssr[0], mapl, mapr );
#endif

        Scalar wl1, wl2, wl3;
        Scalar wr1, wr2, wr3;

        for (LocalSize q=0; q<qtot; q++) {      // loop over side quad-pts

#ifdef REO_USE_GETSIDEMAPS
          const LocalSize ql = mapl[q];
          const LocalSize qr = mapr[q];
#else
          const LocalSize ql = U->sideMap(Ssl[0], q);
          const LocalSize qr = U->sideMap(Ssr[0], q);
#endif

          const Scalar nx = Us[0]->el[e]->side[i]->nx(ql);
          const Scalar ny = Us[0]->el[e]->side[i]->ny(ql);

          // compute normal flux from interior (left)

          // From solution U
          for(vField::size_type k=0;k<Nfields;k++) sl[k] = Ssl[k]->u[ql];

          for(vField::size_type k=0;k<Nfields;k++) w[k] = Ssl[k]->u[ql];

          wl1 = w[0];
          wl2 = w[1];
          wl3 = w[2];

          phil   = Sbl[0]->u[ql];
          thetal = Sbl[1]->u[ql];
          psil   = Sbl[2]->u[ql];

          clm = sqrt(phil);
          ulm = (thetal*nx + psil*ny)/phil;

          Fx[0] = ( (phil - ((thetal*thetal) / (phil*phil))) * wl2 )
                + ( -(thetal * psil / (phil*phil)) * wl3 );
          Fx[1] = wl1 + ( (2.0 * thetal / phil) * wl2 )
                + ( (psil / phil) * wl3 );
          Fx[2] = ( (thetal / phil) * wl3 );

          Fy[0] = ( -(thetal * psil / (phil*phil)) * wl2 )
                + ( (phil - ((psil*psil) / (phil*phil))) * wl3 );
          Fy[1] = ( (psil / phil) * wl2 );
          Fy[2] = wl1 + ( (thetal / phil) * wl2 )
                + ( (2.0 * psil / phil) * wl3 );

          Ssl[0]->u[ql] = Fx[0]*nx + Fy[0]*ny;
          Ssl[1]->u[ql] = Fx[1]*nx + Fy[1]*ny;
          Ssl[2]->u[ql] = Fx[2]*nx + Fy[2]*ny;

          // compute normal flux from exterior (right)

          // adjacent state
          for(vField::size_type k=0;k<Nfields;k++) sr[k] = Ssr[k]->u[qr];

          // put the adjacent flux on the state sides

          // Local sound speed from state flow
          for(vField::size_type k=0;k<Nfields;k++) w[k] = Ssr[k]->u[qr];

          wr1 = w[0];
          wr2 = w[1];
          wr3 = w[2];

          phir   = Sbr[0]->u[qr];
          thetar = Sbr[1]->u[qr];
          psir   = Sbr[2]->u[qr];

          crm = sqrt(phir);
          urm = (thetar*nx + psir*ny)/phir;

          Fx[0] = ( (phir - ((thetar*thetar) / (phir*phir))) * wr2 )
                + ( -(thetar * psir / (phir*phir)) * wr3 );
          Fx[1] = wr1 + ( (2.0 * thetar / phir) * wr2 )
                + ( (psir / phir) * wr3 );
          Fx[2] = ( (thetar / phir) * wr3 );

          Fy[0] = ( -(thetar * psir / (phir*phir)) * wr2 )
                + ( (phir - ((psir*psir) / (phir*phir))) * wr3 );
          Fy[1] = ( (psir / phir) * wr2 );
          Fy[2] = wr1 + ( (thetar / phir) * wr2 )
                + ( (2.0 * psir / phir) * wr3 );

          Ssr[0]->u[qr] = Fx[0]*nx + Fy[0]*ny;
          Ssr[1]->u[qr] = Fx[1]*nx + Fy[1]*ny;
          Ssr[2]->u[qr] = Fx[2]*nx + Fy[2]*ny;

          switch (flux) {
          case LaxFriedrichs: {
            Scalar lmax=0.0;

            lam[0] = ulm-clm;
            lam[1] = ulm;
            lam[2] = ulm+clm;

            for(vField::size_type j=0; j<Nfields;j++) {
              lmax = max(lmax,fabs(lam[j]));
              fpl[j] = Ssl[j]->u[ql];
            }

            lam[0] = urm-crm;
            lam[1] = urm;
            lam[2] = urm+crm;

            for(vField::size_type j=0; j<Nfields; j++) {
              lmax = max(lmax,fabs(lam[j]));
              fmr[j] = Ssr[j]->u[qr];
            }

            // Lax-Friedrichs flux
            f[0] = 0.5 * ( fpl[0] + fmr[0] - lmax * ( sl[0] - sr[0] ) );
            f[1] = 0.5 * ( fpl[1] + fmr[1] - lmax * ( sl[1] - sr[1] ) );
            f[2] = 0.5 * ( fpl[2] + fmr[2] - lmax * ( sl[2] - sr[2] ) );

            break;
          }
          default:
            throw DGM::exception("Illegal value of flux type "+asString(flux));
          }

          // put fluxes on flux field sides
          for (vField::size_type ni=0; ni<Nfields; ni++) {
            Ssr[ni]->u[qr] *= -1.0;         // correct for normal
            Sfl[ni]->u[ql]  =  f[ni];       // upwind flux
            Sfr[ni]->u[qr]  = -f[ni];       // correct for normal
          }
        }
      }
    }
  }
}

void ShallowAdjoint::conv_source(vField &Us, vField &Ur) {
  Element *S[Nfields], *F[Nfields], *Sm[Nfields];
  Scalar w[Nfields];
  Scalar Fx[Nfields], Fy[Nfields];

  for (LocalSize k=0; k<Us[0]->ne; k++) {

    S[0] = Us[0]->el[k];       // local version of the state (adjoint)
    S[1] = Us[1]->el[k];
    S[2] = Us[2]->el[k];

    Sm[0] = Ustate[0]->el[k];  // local version of the state (state)
    Sm[1] = Ustate[1]->el[k];
    Sm[2] = Ustate[2]->el[k];

    F[0] = Utmp[0]->el[k];     // local version of the RHS
    F[1] = Utmp[1]->el[k];
    F[2] = Utmp[2]->el[k];

    /** \todo this is slow. */
    dVector phi(Sm[0]->u);
    dVector theta(Sm[1]->u);
    dVector psi(Sm[2]->u);

    const Ordinal qtot = S[0]->qtot;

    /** \todo these should use work space and aliases. */
    dVector theta_x(qtot);
    dVector theta_y(qtot);
    dVector psi_x(qtot);
    dVector psi_y(qtot);
    dVector phi_x(qtot);
    dVector phi_y(qtot);
    dVector tmp1(qtot), tmp2(qtot), tmp3(qtot);

    Sm[0]->gradient(phi, phi_x, phi_y);
    Sm[1]->gradient(theta, theta_x, theta_y);
    Sm[2]->gradient(psi, psi_x, psi_y);

    Scalar w2, w3;

    for (LocalSize q=0; q<qtot; q++) {

      for (vField::size_type i=0; i<Nfields; i++) w[i] = S[i]->u[q];

      const Scalar phiq = phi[q];
      const Scalar thetaq = theta[q];
      const Scalar psiq = psi[q];

      w2 = w[1];
      w3 = w[2];

      // Fx = Transpose(B1),x * Lamda

      Fx[0] =  w2 * (
                     phi_x(q) - ( ( (phiq*phiq*2.0*thetaq*theta_x(q))
                                  - (thetaq*thetaq*2.0*phiq*phi_x(q)) )
                                / (phiq*phiq*phiq*phiq) )
                    )
             - w3 * (
                     ( (phiq*phiq*((thetaq*psi_x(q))+(psiq*theta_x(q))))
                     - (2.0*phiq*thetaq*psiq*phi_x(q)) )
                     / (phiq*phiq*phiq*phiq)
                    );
      Fx[1] = 2.0 * w2 * (
                          ( (phiq*theta_x(q))
                          - (thetaq*phi_x(q)) )
                          / (phiq*phiq)
                         )
                  + w3 * (
                          ( (phiq*psi_x(q))
                          - (psiq*phi_x(q)) )
                          / (phiq*phiq)
                         );
      Fx[2] = w3 * (
                    ( (phiq*theta_x(q))
                    - (thetaq*phi_x(q)) )
                    / (phiq*phiq)
                   );

      // Fy = Transpose(B2),y * Lamda
      Fy[0] = -w2 * (
                     ( (phiq*phiq*((thetaq*psi_y(q))+(psiq*theta_y(q))))
                     - (2.0*phiq*thetaq*psiq*phi_y(q)) )
                     / (phiq*phiq*phiq*phiq)
                    )
             + w3 * (
                     phi_y(q) - ( ( (phiq*phiq*2.0*psiq*psi_y(q))
                                  - (psiq*psiq*2.0*phiq*phi_y(q)) )
                                / (phiq*phiq*phiq*phiq) )
                    );
      Fy[1] = w2 * (
                    ( (phiq*psi_y(q))
                    - (psiq*phi_y(q)) )
                    / (phiq*phiq)
                   );
      Fy[2] = w2 * (
                    ( (phiq*theta_y(q))
                    - (thetaq*phi_y(q)) )
                    / (phiq*phiq)
                   )
      + 2.0 * w3 * (
                    ( (phiq*psi_y(q))
                    - (psiq*phi_y(q)) )
                    / (phiq*phiq)
                   );

      F[0]->u[q] = Fx[0]+Fy[0];
      F[1]->u[q] = Fx[1]+Fy[1];
      F[2]->u[q] = Fx[2]+Fy[2];
    }
  }
  // add in state flow contribution
#if 0
  scale(-one,Utmp);                  // I currently put everything on the LHS
  for(vField::size_type i=0; i<Utmp.size(); i++) add( Utmp[i], Ur[i] );
#else
  axpy(one,Utmp,Ur);
#endif
}

//===========================================================================
//                        BC database management
//===========================================================================

// Load up the available BC types
void ShallowAdjoint::setup_BCdb( ) {
  BC_db = state->BC_db;
}

void ShallowAdjoint::enforce_bc(vField &F) {
  for (BC::db_citr i=BC_db.begin(); i!= BC_db.end(); ++i)
    i->second->adjoint_apply( t, Ustate, F );
}

void ShallowAdjoint::enforce_flux_bc(vField &S) {
  cout << "ShallowAdjoint::enforce_flux_bc(vField &U) not valid" << endl;
  comm->exit(DGM::FAILURE);
}

//===========================================================================
//                        Source database management
//===========================================================================

/// Load up the available Source types
void ShallowAdjoint::setup_Sourcedb( ) {
  // cout << "ShallowAdjoint::setup_Sourcedb" << endl;
  Source_db = state->Source_db;  // use the State sources
  string fname = root+".obj";    // add sources due to objective function
  ifstream in(fname.c_str());
  if (in) read_Sourcedb( in );   // database of active Source types
}

/// make the Adjoint Source terms
Source::Ptr ShallowAdjoint::make_Source( ifstream &in, string &tag ) {
  // cout << "ShallowAdjoint::make_Source" << endl;
  string code;
  Source::Ptr p;
  if (!(in >> code)) return p;
  while (code[0]=='#') {  // eat comment lines
    string buffer;
    getline(in,buffer);
    if (!(in >> code)) return p;
  }
  if (lowerCase(code) == "phitracking") {
    if (!(in >> tag))
      error("ShallowAdjoint::Cannot read PhiTracking tag",1);
    p.reset( new PhiTracking(tag,in,U,state) );
  } else {
    comm->cout()<<code<<endl;
    error("ShallowAdjoint::make_Source() Illegal Source type",1);
  }
  return p;
}

/// Add Source terms
void ShallowAdjoint::add_source(const vField &Us, vField &Ur) {
  // cout << "ShallowAdjoint::add_source(vField &)" << endl;
  for (Source::db_citr i=Source_db.begin(); i!= Source_db.end(); ++i) {
    i->second->adjoint_apply(t, Ustate, Us, Ur );
  }
}

/** Shallow
    \warning: must give correct information on State/Adjoint boundary sides
    Ua = Adjoint Field
    Us = State   Field **/
void ShallowAdjoint::computeGrad(vField &Ua, vField &Us,
                                 Ordinal istep, Ordinal sstep) {
  control->gradient( Us, Ua, g_control, istep, sstep );
}

void ShallowAdjoint::set_ic(vField &F, string ext) {
  string fname = root+ext;
  ifstream in(fname.c_str());
  if (!in) {
    F.zero();
    return;
  }
  string buffer, code;
  getline(in,buffer);
  if (!(in>>code)) error("Cannot read IC code",1);
  getline(in,buffer);
  if (lowerCase(code) == "given") {
    F.fill(in);
  } else if (lowerCase(code) == "restart") {
    string rstfile;
    if (!(in>>rstfile)) {
      comm->cerr() << "Cannot read restart file name from " << fname << endl;
      comm->exit(1);
    }
    read(rstfile, F);
  } else {
    throw DGM::exception("Illegal initial condition code "+code);
  }
#ifdef DGM_NO_PROJECT_IC
  comm->cout() << "WARNING:  No projection of Initial condition" << endl;
  for (LocalSize i=0; i<Nfields; i++)
    for (LocalSize e=0; e<ne; e++)
      F[i]->el[e]->state = Element::Physical;
#else
  // project fields to the polynomial space just to make sure
  project( F );
#endif
}

} // namespace Reo

#else // DGM_REMOVE_FOR_RELEASE
// This capability is under development.
#endif // DGM_REMOVE_FOR_RELEASE
