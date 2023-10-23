/*=============================================================================
  Module:     Euler Adjoint Module

  Author:     S. Scott Collis and Guoquan Chen

  Copyright:  S. Scott Collis
              Department of Mechanical Engineering and Materials Science
              Rice University, MS 321
              Houston, TX 77005-1892
              (713) 348-3617
              collis@rice.edu
=============================================================================*/

/** \file  Euler_Adjoint.cpp
    \brief Adjoint for the 2d Euler equations
    \author Scott Collis
*/

// system includes
#include <cmath>
#include <cassert>

// DGM includes
#include "Format.hpp"
#include "TimeInt.hpp"
#include "Wavetype.hpp"

// Reo includes
#include "Reo.hpp"
#include "Euler_Adjoint.hpp"
#include "Euler_State.hpp"

namespace Reo {

// constructor
Euler_Adjoint::Euler_Adjoint(DGM::ArgList &args, const State* S,
                             const DGM::Comm::Ptr comm_, const int pinc) :
  Domain(args,comm_), Adjoint(S,pinc), Utmp(comm_) {


  // setup local pointer to State
  state = dynamic_cast<const Euler_State*>(state_);

  // set the number of fields in the domain
  Nfields = 4;

  npredict = params.get("npredict",0);

  Ordinal p, q;
  p = params["p"];                     // polynomial order
  p += p_inc;                          // increment polynomial order if needed
  comm->cout() << "Euler_Adjoint:  p = "<< p <<endl;
  if ( !(q=params["q"]) ) q = p + 2;   // number of quadrature points
  nsd = params["nsd"];                 // number of space dimensions

  // read arguments (overrides defaults and input file)
  parse_args( args );

  gamma = params["gamma"];             // ratio of specific heats

  vector<string> field_names;          // Field names
  field_names.push_back("R");

  // build a Field of Elements and Sides
  if (params["imesh"]) {
     error("Euler_Adjoint internal mesh not supported",-1);
  } else if (params["bmesh"]) {
    U.push_back( new Field(p, q, root, field_names[0],partition,1,
                           Reo::NumEqntype, p2i(EULER),comm,p_inc));
  } else {
    U.push_back( new Field(p, q, root, field_names[0],partition,comm,p_inc));
  }

  // set some additional domain parameters
  ne = U[0]->ne;
  nsd = U[0]->nsd();

#ifdef REO_USE_GETSIDEMAPS
  setup_side_maps();
#endif

  field_names.push_back("U");
  field_names.push_back("V");
  field_names.push_back("E");

  // build the rest of the vector field
  for (vField::size_type i=1; i<Nfields; i++)
    U.push_back( new Field( U[0], root, field_names[i] ) );

  // make auxiliary Fields using copy constructor
  for (vField::size_type i=0; i<Nfields; i++) {
    Ut.push_back( new Field( U[0], root, field_names[i] ) );
    Ustate.push_back( new Field( U[0], root, field_names[i] ) );
    Utmp.push_back( new Field( U[0], root, field_names[i] ) );
  }

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
void Euler_Adjoint::set_TimeInt( Ordinal ) {
  int inttype = params["inttype"];
  switch(inttype) {
  case TimeInt::FORWARD_EULER: {
    comm->cout() << "Euler_Adjoint:: using Forward Euler" << endl;
    time_int = new ForwardEuler( this );
    break; }
  case TimeInt::TVD_RK: {
    comm->cout() << "Euler_Adjoint:: using TVD RK" << endl;
    time_int = new TVD( this );
    break; }
  case TimeInt::RUNGE_KUTTA: {
    comm->cout() << "Euler_Adjoint:: using Runge-Kutta-4" << endl;
    time_int = new RungeKutta( this );
    break; }
  case TimeInt::SSPRK: {
    comm->cout() << "Euler_Adjoint:: using SSPRK" << endl;
    time_int = new SSPRK( this );
    break; }
#ifdef DGM_USE_ITL
  case TimeInt::BACKWARD_EULER: {
    comm->cout() << "Euler_Adjoint:: using Backward-Euler" << endl;
    time_int = new BackwardEuler( this, ".adj" );
    break; }
#endif
  case TimeInt::LSRK14: {
    comm->cout() << "Euler_Adjoint:: using LSRK14" << endl;
    time_int = new LSRK14( this );
    break; }
  default:
    comm->cerr() << "Euler_Adjoint::set_TimeInt() "
                 << "Unsupported time integration type" << endl;
    comm->exit(DGM::FAILURE);
  }
}


void Euler_Adjoint::zero_all_fields() {
  Domain::zero_all_fields();
  Ustate.zero();
  Utmp.zero();
}


void Euler_Adjoint::time_derivative( vField &Us, vField &Uf ) {
  convection( Us, Uf );
  conv_source(Us,Uf);
  add_source(Us,Uf);
  project( Uf );
}

void Euler_Adjoint::set_end_condition() {
  Adjoint::set_end_condition();
  store(U, npredict, 0);
}

void Euler_Adjoint::set_end_condition(const dVector &X,
                                      const Scalar t_, const Ordinal step_) {
  Adjoint::set_end_condition(X, t_, step_);
  store(U, npredict, 0);
}

void Euler_Adjoint::prestep( vField &F, const Ordinal istep,
                             const Ordinal sstep, const Scalar time) {
  state->load_field( Ustate, istep, sstep);
  control->set_data( istep, sstep );
  objective->set_data( Ustate, istep, sstep );
  if (time_int->is_explicit()) {
    store(F, istep, sstep);
    computeGrad( F, Ustate, istep, sstep );
  }
}

void Euler_Adjoint::poststep( vField &F, const Ordinal istep,
                              const Ordinal sstep, const Scalar time) {
  if (time_int->is_implicit()) {
    store(F,istep,sstep);
    computeGrad( F, Ustate, istep, sstep );
  }
}

void Euler_Adjoint::convection( vField &Us, vField &Uf ) {
  Element *U[4], *F[4],*Fm[4];
  dVector u1, u2, u3,Fx1,Fx2,Fx3,Fx4,Fy1,Fy2,Fy3,Fy4,d;
  Scalar w[4], rho, m, n, E;

  Ustate.fill_sides();
  const_cast<Euler_State*>(state)->enforce_bc(Ustate);

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
    U[3] = Us[3]->el[e];

    // local version of the  flux
    F[0] = Uf[0]->el[e];
    F[1] = Uf[1]->el[e];
    F[2] = Uf[2]->el[e];
    F[3] = Uf[3]->el[e];

    // local version of the state solution
    Fm[0] = Ustate[0]->el[e];
    Fm[1] = Ustate[1]->el[e];
    Fm[2] = Ustate[2]->el[e];
    Fm[3] = Ustate[3]->el[e];

    const Ordinal qtot = Us[0]->el[e]->qtot;

    Fx1.alias(wk1,0,qtot);
    Fx2.alias(wk1,qtot,qtot);
    Fx3.alias(wk1,2*qtot,qtot);
    Fx4.alias(wk1,3*qtot,qtot);
    Fy1.alias(wk1,4*qtot,qtot);
    Fy2.alias(wk1,5*qtot,qtot);
    Fy3.alias(wk1,6*qtot,qtot);
    Fy4.alias(wk1,7*qtot,qtot);
    d.alias(wk1,8*qtot,qtot);

    //  F(u(x)),x = (transpose(F^1_q) \lambda),x
    //  G(u(x)),y = (transpose(F^2_q) \lambda),x

    for (Ordinal q=0; q<qtot; q++) {

      for(vField::size_type i=0;i<Nfields;i++) w[i]=U[i]->u[q];
      rho = Fm[0]->u[q];
      m   = Fm[1]->u[q];
      n   = Fm[2]->u[q];
      E   = Fm[3]->u[q];

      // code produced by Maple

      Fx1[q] = 0.5*(-3.0*w[1]*rho*m*m+w[1]*rho*gamma*m*m+w[1]*rho*gamma*n*n
                    -w[1]*rho*n*n - 2.0*m*n*w[2]*rho-2.0*m*w[3]*gamma*E*rho
                    +2.0*m*m*m*w[3]*gamma+2.0*m*w[3]*gamma*n*n
                    - 2.0*m*m*m*w[3] -2.0*m*w[3]*n*n)/(rho*rho*rho);
      Fx2[q] = -0.5*(-2.0*w[0]*rho*rho-6.0*m*w[1]*rho+2.0*m*w[1]*rho*gamma
                     -2.0*n*w[2]*rho - 2.0*w[3]*gamma*E*rho
                     +3.0*w[3]*gamma*m*m +w[3]*gamma*n*n-3.0*w[3]*m*m
                     - w[3]*n*n)/(rho*rho);
      Fx3[q] = -(n*w[1]*rho*gamma-n*w[1]*rho-m*w[2]*rho+m*n*w[3]*gamma
                 -m*n*w[3])/(rho*rho);
      Fx4[q] = (w[1]*rho*gamma-w[1]*rho+m*w[3]*gamma)/rho;

      Fy1[q] = 0.5*(-2.0*m*n*w[1]*rho-3.0*w[2]*rho*n*n+w[2]*rho*gamma*m*m
                    +w[2]*rho*gamma*n*n - w[2]*rho*m*m-2.0*n*w[3]*gamma*E*rho
                    +2.0*n*w[3]*gamma*m*m+2.0*n*n*n*w[3]*gamma
                    - 2.0*n*w[3]*m*m -2.0*n*n*n*w[3])/(rho*rho*rho);
      Fy2[q] = (n*w[1]*rho-m*w[2]*rho*gamma+m*w[2]*rho-m*n*w[3]*gamma
                +m*n*w[3])/(rho*rho);
      Fy3[q] = -0.5*(-2.0*w[0]*rho*rho-2.0*m*w[1]*rho-6.0*n*w[2]*rho
                     +2.0*n*w[2]*rho*gamma - 2.0*w[3]*gamma*E*rho
                     +w[3]*gamma*m*m +3.0*w[3]*gamma*n*n-w[3]*m*m
                     -3.0*w[3]*n*n)/(rho*rho);
      Fy4[q] = (w[2]*rho*gamma-w[2]*rho+n*gamma*w[3])/rho;
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

    U[3]->gradient(Fx4, F[3]->u, 'x');
    U[3]->gradient(Fy4, d, 'y');
    dvadd(d,F[3]->u);

    // add the surface contribution
    for (vField::size_type i=0; i<Nfields; i++) U[i]->lift( F[i], F[i]->u );
  }
}

/** For descriptions of the numerical fluxes See: E.F. Toro, "Riemann
    Solvers and Numerical Methods for Fluid Dynamics," 2nd Edition,
    Springer, 1999, p. 305.
*/
void Euler_Adjoint::convective_flux(vField &Us, vField &Uf) {
  flux_type flux = LaxFriedrichs; //StegerWarming; //vanLeer;
  dVector sl(Nfields), sr(Nfields), f(Nfields);
  dVector bl(Nfields), br(Nfields);
  Scalar ulb, clb, urb, crb;
  vector<Side *> Ssl(Nfields), Ssr(Nfields);
  vector<Side *> Sbl(Nfields), Sbr(Nfields);
  vector<Side *> Sfl(Nfields), Sfr(Nfields);
  dVector fpl(Nfields), fmr(Nfields), lam(Nfields);
  Scalar rho, m, n, E, p;
  dVector w(Nfields);
#ifdef REO_USE_GETSIDEMAPS
  iVector mapl, mapr;
#endif
  dVector fx(Nfields), fy(Nfields);

  for (LocalSize e=0; e<Us[0]->ne; e++) {                 // loop over elements
    Element* U = Us[0]->el[e];
    for (LocalSize i=0; i<Us[0]->el[e]->nSides(); i++) {  // loop over sides
      if (Us[0]->el[e]->side[i]->master()) {              // compute if link

        for (vField::size_type ni=0; ni<Nfields; ni++) {
          Ssl[ni] = Us[ni]->el[e]->side[i];            // local state side
          Ssr[ni] = Us[ni]->el[e]->side[i]->link;      // adjacent state side
          Sfl[ni] = Uf[ni]->el[e]->side[i];            // local flux side
          Sfr[ni] = Uf[ni]->el[e]->side[i]->link;      // adjacent flux side
          Sbl[ni] = Ustate[ni]->el[e]->side[i];        // local base side
          Sbr[ni] = Ustate[ni]->el[e]->side[i]->link;  // adjacent base side
        }
#ifdef REO_USE_GETSIDEMAPS
        get_side_maps( Ssl[0], Ssr[0], mapl, mapr );
#endif

        const LocalSize qtot = Us[0]->el[e]->side[i]->qtot();  // qpts on side
        for (LocalSize q=0; q<qtot; q++) {         // loop over side quad-pts

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

          for(vField::size_type k=0;k<Nfields;k++) w[k]=Ssl[k]->u[ql];
          rho = Sbl[0]->u[ql];
          m   = Sbl[1]->u[ql];
          n   = Sbl[2]->u[ql];
          E   = Sbl[3]->u[ql];

          p = (gamma-1.0)*(E - 0.5*(m*m + n*n)/rho);
          clb = sqrt((gamma-1.0)*((E+p)/rho - 0.5*(m*m + n*n)/rho/rho));
          ulb = (m*nx +n*ny)/rho;

          // code produced by Maple
          fx[0] = 0.5*(-3.0*w[1]*rho*m*m+w[1]*rho*gamma*m*m
                       +w[1]*rho*gamma*n*n-w[1]*rho*n*n - 2.0*m*n*w[2]*rho
                       -2.0*m*w[3]*gamma*E*rho+2.0*m*m*m*w[3]*gamma
                       +2.0*m*w[3]*gamma*n*n -2.0*m*m*m*w[3]
                       -2.0*m*w[3]*n*n)/(rho*rho*rho);
          fx[1] = -0.5*(-2.0*w[0]*rho*rho-6.0*m*w[1]*rho+2.0*m*w[1]*rho*gamma
                        -2.0*n*w[2]*rho - 2.0*w[3]*gamma*E*rho
                        +3.0*w[3]*gamma*m*m +w[3]*gamma*n*n-3.0*w[3]*m*m
                        - w[3]*n*n)/(rho*rho);
          fx[2] = -(n*w[1]*rho*gamma-n*w[1]*rho-m*w[2]*rho+m*n*w[3]*gamma
                    -m*n*w[3])/(rho*rho);
          fx[3] = (w[1]*rho*gamma-w[1]*rho+m*w[3]*gamma)/rho;


          fy[0] = 0.5*(-2.0*m*n*w[1]*rho-3.0*w[2]*rho*n*n+w[2]*rho*gamma*m*m
                       +w[2]*rho*gamma*n*n - w[2]*rho*m*m
                       -2.0*n*w[3]*gamma*E*rho + 2.0*n*w[3]*gamma*m*m
                       +2.0*n*n*n*w[3]*gamma- 2.0*n*w[3]*m*m
                       -2.0*n*n*n*w[3])/(rho*rho*rho);
          fy[1] = (n*w[1]*rho-m*w[2]*rho*gamma+m*w[2]*rho-m*n*w[3]*gamma
                   +m*n*w[3])/(rho*rho);
          fy[2] = -0.5*(-2.0*w[0]*rho*rho-2.0*m*w[1]*rho-6.0*n*w[2]*rho
                        +2.0*n*w[2]*rho*gamma - 2.0*w[3]*gamma*E*rho
                        +w[3]*gamma*m*m+3.0*w[3]*gamma*n*n
                        -w[3]*m*m-3.0*w[3]*n*n)/(rho*rho);
          fy[3] = (w[2]*rho*gamma-w[2]*rho+n*gamma*w[3])/rho;

          Ssl[0]->u[ql] = fx[0]*nx + fy[0]*ny;
          Ssl[1]->u[ql] = fx[1]*nx + fy[1]*ny;
          Ssl[2]->u[ql] = fx[2]*nx + fy[2]*ny;
          Ssl[3]->u[ql] = fx[3]*nx + fy[3]*ny;

          // compute normal flux from exterior (right)

          // adjacent state
          for(vField::size_type k=0;k<Nfields;k++) sr[k] = Ssr[k]->u[qr];

          // put the adjacent flux on the state sides

          // Local sound speed from state flow
          for(vField::size_type k=0;k<Nfields;k++) w[k]=Ssr[k]->u[qr];
          rho = Sbr[0]->u[qr];
          m   = Sbr[1]->u[qr];
          n   = Sbr[2]->u[qr];
          E   = Sbr[3]->u[qr];

          p = (gamma-1.0)*(E - 0.5*(m*m + n*n)/rho);
          crb = sqrt((gamma-1.0)*((E+p)/rho - 0.5*(m*m + n*n)/rho/rho));
          urb = (m*nx +n*ny)/rho;

          // code produced by Maple
          fx[0] = 0.5*(-3.0*w[1]*rho*m*m+w[1]*rho*gamma*m*m
                       +w[1]*rho*gamma*n*n-w[1]*rho*n*n - 2.0*m*n*w[2]*rho
                       -2.0*m*w[3]*gamma*E*rho+2.0*m*m*m*w[3]*gamma
                       +2.0*m*w[3]*gamma*n*n -2.0*m*m*m*w[3]
                       -2.0*m*w[3]*n*n)/(rho*rho*rho);
          fx[1] = -0.5*(-2.0*w[0]*rho*rho-6.0*m*w[1]*rho+2.0*m*w[1]*rho*gamma
                        -2.0*n*w[2]*rho - 2.0*w[3]*gamma*E*rho
                        +3.0*w[3]*gamma*m*m +w[3]*gamma*n*n-3.0*w[3]*m*m
                        - w[3]*n*n)/(rho*rho);
          fx[2] = -(n*w[1]*rho*gamma-n*w[1]*rho-m*w[2]*rho+m*n*w[3]*gamma
                    -m*n*w[3])/(rho*rho);
          fx[3] = (w[1]*rho*gamma-w[1]*rho+m*w[3]*gamma)/rho;

          fy[0] = 0.5*(-2.0*m*n*w[1]*rho-3.0*w[2]*rho*n*n+w[2]*rho*gamma*m*m
                       +w[2]*rho*gamma*n*n - w[2]*rho*m*m
                       -2.0*n*w[3]*gamma*E*rho+2.0*n*w[3]*gamma*m*m
                       +2.0*n*n*n*w[3]*gamma- 2.0*n*w[3]*m*m
                       -2.0*n*n*n*w[3])/(rho*rho*rho);
          fy[1] = (n*w[1]*rho-m*w[2]*rho*gamma+m*w[2]*rho-m*n*w[3]*gamma
                   +m*n*w[3])/(rho*rho);
          fy[2] = -0.5*(-2.0*w[0]*rho*rho-2.0*m*w[1]*rho-6.0*n*w[2]*rho
                        +2.0*n*w[2]*rho*gamma - 2.0*w[3]*gamma*E*rho
                        +w[3]*gamma*m*m+3.0*w[3]*gamma*n*n
                        -w[3]*m*m-3.0*w[3]*n*n)/(rho*rho);
          fy[3] = (w[2]*rho*gamma-w[2]*rho+n*gamma*w[3])/rho;

          Ssr[0]->u[qr] = fx[0]*nx + fy[0]*ny;
          Ssr[1]->u[qr] = fx[1]*nx + fy[1]*ny;
          Ssr[2]->u[qr] = fx[2]*nx + fy[2]*ny;
          Ssr[3]->u[qr] = fx[3]*nx + fy[3]*ny;

          switch (flux) {
          case LaxFriedrichs: {
            Scalar lmax=0.0;

            lam[0] = ulb;
            lam[1] = ulb+clb;
            lam[2] = ulb-clb;
            lam[3] = ulb;

            for(vField::size_type j=0; j<Nfields;j++) {
              lmax = max(lmax,fabs(lam[j]));
              fpl[j] = Ssl[j]->u[ql];
            }

            lam[0] = urb;
            lam[1] = urb+crb;
            lam[2] = urb-crb;
            lam[3] = urb;

            for(vField::size_type j=0; j<Nfields; j++) {
              lmax = max(lmax,fabs(lam[j]));
              fmr[j] = Ssr[j]->u[qr];
            }

            // Lax-Friedrichs flux
            f[0] = 0.5 * ( fpl[0] + fmr[0] - lmax * ( sl[0] - sr[0] ) );
            f[1] = 0.5 * ( fpl[1] + fmr[1] - lmax * ( sl[1] - sr[1] ) );
            f[2] = 0.5 * ( fpl[2] + fmr[2] - lmax * ( sl[2] - sr[2] ) );
            f[3] = 0.5 * ( fpl[3] + fmr[3] - lmax * ( sl[3] - sr[3] ) );

            break;
          }
          case vanLeer:       // Based on the Mach splitting
          case StegerWarming: // Based on the sound speed splitting
          case Roe:           // Roe average
          default:
            comm->cerr() << "Illegal value of flux type" << endl;
            comm->exit(DGM::FAILURE);
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


void Euler_Adjoint::conv_source(vField &Us,vField &Ur) {
  Element *S[4], *F[4], *Sm[4];
  Scalar w[4];
  Scalar Fx[4], Fy[4];

  for (LocalSize k=0; k<Us[0]->ne; k++) {

    S[0] = Us[0]->el[k];  // local version of the state (adjoint)
    S[1] = Us[1]->el[k];
    S[2] = Us[2]->el[k];
    S[3] = Us[3]->el[k];

    Sm[0] = Ustate[0]->el[k];  // local version of the state (state)
    Sm[1] = Ustate[1]->el[k];
    Sm[2] = Ustate[2]->el[k];
    Sm[3] = Ustate[3]->el[k];

    F[0] = Utmp[0]->el[k];  // local version of the RHS
    F[1] = Utmp[1]->el[k];
    F[2] = Utmp[2]->el[k];
    F[3] = Utmp[3]->el[k];

    dVector r(Sm[0]->u);
    dVector ru(Sm[1]->u);
    dVector rv(Sm[2]->u);
    dVector En(Sm[3]->u);

    const Ordinal qtot = S[0]->qtot;

    dVector ru_x(qtot);
    dVector ru_y(qtot);
    dVector rv_x(qtot);
    dVector rv_y(qtot);
    dVector r_x(qtot);
    dVector r_y(qtot);
    dVector E_x(qtot);
    dVector E_y(qtot);
    dVector tmp1(qtot), tmp2(qtot), tmp3(qtot);

    Sm[0]->gradient(r, r_x, r_y);
    Sm[1]->gradient(ru, ru_x, ru_y);
    Sm[2]->gradient(rv, rv_x, rv_y);
    Sm[3]->gradient(En, E_x, E_y);

    for (LocalSize q=0; q<qtot; q++) {

      for (LocalSize i=0; i<4; i++) w[i] = S[i]->u[q];
      const Scalar rho = r[q];
      const Scalar m = ru[q];
      const Scalar n = rv[q];
      const Scalar E = En[q];

      // Fx = Transpose(B1),x * Lamda

      Fx[0] = ((-6.0*ru_x[q]*m+2.0*gamma*ru_x[q]*m +2.0*gamma*rv_x[q]*n
                -2.0*rv_x[q]*n)/(rho*rho)/2.0
               -(-3.0*m*m+gamma*m*m+gamma*n*n-n*n)*r_x[q]/(rho*rho*rho))*w[1]
        +(-ru_x[q]*n/(rho*rho)-m*rv_x[q]/(rho*rho)
          + 2.0*m*n*r_x[q]/(rho*rho*rho))*w[2]
        +(-ru_x[q]*(gamma*E*rho-gamma*m*m-gamma*n*n+m*m+n*n)/(rho*rho*rho)
          -m*(gamma*E_x[q]*rho+gamma*E*r_x[q]
              -2.0*gamma*ru_x[q]*m-2.0*gamma*rv_x[q]*n
              +2.0*ru_x[q]*m +2.0*rv_x[q]*n)/(rho*rho*rho)
          +3.0*m*(gamma*E*rho-gamma*m*m
                  -gamma*n*n+m*m+n*n)*r_x[q]/(rho*rho *rho*rho))*w[3];
      Fx[1] = (-ru_x[q]*(-3.0+gamma)/rho+m*(-3.0+gamma)*r_x[q]/(rho*rho))
        *w[1]+(rv_x[q]/rho-n*r_x[q]/(rho*rho))*w[2]
        +((2.0*gamma*E_x[q] *rho+2.0*gamma*E*r_x[q]
           -6.0*gamma*ru_x[q]*m-2.0*gamma*rv_x[q]*n+6.0*ru_x[q]*m
           +2.0*rv_x[q]*n)/(rho*rho)/2.0
          -(2.0*gamma*E*rho-3.0*gamma*m*m-gamma*n*n+3.0*m*m+n*n)*r_x[q]
          /(rho*rho*rho))*w[3];
      Fx[2] = (-rv_x[q]*(gamma-1.0)/rho+n*(gamma-1.0)*r_x[q]/(rho*rho))*w[1]
        +(ru_x[q]/rho-m*r_x[q]/(rho*rho))*w[2]
        +(-ru_x[q]*n*(gamma-1.0)/(rho*rho)-m*rv_x[q]*(gamma-1.0)/(rho*rho)
          +2.0*m*n*(gamma-1.0)*r_x[q]/(rho*rho*rho))*w[3];
      Fx[3] = (ru_x[q]*gamma/rho-m*gamma*r_x[q]/(rho*rho))*w[3];

      // Fy = Transpose(B2),y * Lamda
      Fy[0] = -(w[1]*rho*rho*ru_y[q]*n+w[1]*rho*rho*m*rv_y[q]
                -2.0*w[1]*rho*m*n*r_y[q]+3.0*w[2]*rho*rho*rv_y[q]*n
                -w[2]*rho*rho*gamma*ru_y[q]*m-w[2]*rho*rho*gamma*rv_y[q]*n
                +w[2]*rho*rho*ru_y[q]*m-3.0*w[2]*rho*r_y[q]*n*n
                +w[2]*rho*r_y[q]*gamma*m*m+w[2]*rho*r_y[q]*gamma*n*n
                -w[2]*rho*r_y[q]*m*m+w[3]*rv_y[q]*rho*rho*gamma*E
                -w[3]*rv_y[q]*rho*gamma*m*m-3.0*w[3]*rv_y[q]*rho*gamma*n*n
                +w[3]*rv_y[q]*rho*m*m+3.0*w[3]*rv_y[q]*rho*n*n
                +w[3]*n*rho*rho*gamma*E_y[q]-2.0*w[3]*n*rho*gamma*E*r_y[q]
                -2.0*w[3]*n*rho*gamma*ru_y[q]*m+2.0*w[3]*n*rho*ru_y[q]*m
                +3.0*w[3]*n*r_y[q]*gamma*m*m+3.0*w[3]*n*n*n*r_y[q]*gamma
                -3.0*w[3]*n*r_y[q]*m*m-3.0*w[3]*n*n*n*r_y[q])/
        (rho*rho*rho*rho);
      Fy[1] = (w[1]*rho*rho*rv_y[q]-w[1]*rho*n*r_y[q]
               -w[2]*rho*rho*gamma*ru_y[q]+w[2]*rho*gamma*m*r_y[q]
               +w[2]*rho*rho*ru_y[q]-w[2]*rho*m*r_y[q]
               -w[3]*gamma*ru_y[q]*n*rho-w[3]*gamma*m*rv_y[q]*rho
               +2.0*w[3]*gamma*m*n*r_y[q]+w[3]*ru_y[q]*n*rho
               +w[3]*m*rv_y[q]*rho-2.0*w[3]*m*n*r_y[q])/(rho*rho*rho);
      Fy[2] = (w[1]*rho*rho*ru_y[q]-w[1]*rho*m*r_y[q]+3.0*w[2]*rho*rho*rv_y[q]
               -3.0*w[2]*rho*n*r_y[q]-w[2]*rho*rho*gamma*rv_y[q]
               +w[2]*rho*gamma*n*r_y[q]+w[3]*gamma*E_y[q]*rho*rho
               -w[3]*rho*gamma*E*r_y[q]-w[3]*rho*gamma*ru_y[q]*m
               -3.0*w[3]*rho*gamma*rv_y[q]*n+w[3]*rho*ru_y[q]*m
               +3.0*w[3]*rho*rv_y[q]*n+w[3]*r_y[q]*gamma*m*m
               +3.0*w[3]*r_y[q]*gamma*n*n-w[3]*r_y[q]*m*m
               -3.0*w[3]*r_y[q]*n*n)/(rho*rho*rho);
      Fy[3] = -gamma*(-rv_y[q]*rho+n*r_y[q])*w[3]/(rho*rho);

      F[0]->u[q] = Fx[0]+Fy[0];
      F[1]->u[q] = Fx[1]+Fy[1];
      F[2]->u[q] = Fx[2]+Fy[2];
      F[3]->u[q] = Fx[3]+Fy[3];
    }
  }
  // add in state flow  contribution
  scale(-one,Utmp);                  // I currently put everything on the LHS
  for(vField::size_type i=0; i<Utmp.size(); i++) add( Utmp[i], Ur[i] );
}

//===========================================================================
//                        BC database management
//===========================================================================
// Load up the available BC types
void Euler_Adjoint::setup_BCdb( ) {
  BC_db = state->BC_db;
}

void Euler_Adjoint::enforce_bc(vField &F) {
  for (BC::db_citr i=BC_db.begin(); i!= BC_db.end(); ++i)
    i->second->adjoint_apply( t, Ustate, F );
}

void Euler_Adjoint::enforce_flux_bc(vField &S) {
  cout << "Euler_Adjoint::enforce_flux_bc(vField &U) not valid" << endl;
  comm->exit(DGM::FAILURE);
}

//===========================================================================
//                        Source database management
//===========================================================================

/// Load up the available Source types
void Euler_Adjoint::setup_Sourcedb( ) {
  // cout << "Euler_Adjoint::setup_Sourcedb" << endl;
  Source_db = state->Source_db;  // use the State sources
  string fname = root+".obj";    // add sources due to objective function
  ifstream in(fname.c_str());
  if (in) read_Sourcedb( in );   // database of active Source types
}

/// make the Adjoint Source terms
Source::Ptr Euler_Adjoint::make_Source( ifstream &in, string &tag ) {
  // cout << "Euler_Adjoint::make_Source" << endl;
  string code;
  Source::Ptr p;
  if (!(in >> code)) return p;
  while (code[0]=='#') {  // eat comment lines
    string buffer;
    getline(in,buffer);
    if (!(in >> code)) return p;
  }
  if (lowerCase(code) == "pressuretracking") {
    if (!(in >> tag))
      error("Euler_Adjoint::Cannot read PressureTracking tag",1);
    p.reset( new PressureTracking(tag,in,U,gamma) );
#ifdef EULER_TERMINAL_TRACKING
  } else if (lowerCase(code) == "terminaltracking") {
    if (!(in >> tag))
      error("Euler_Adjoint::Cannot read TerminalTracking tag",1);;
    p.reset( new TerminalTracking(tag,in,U) );
#endif
  } else if (lowerCase(code) == "steadyerror") {
    if (!(in >> tag))
      error("Euler_Adjoint::Cannot read SteadyError tag",1);;
    p.reset( new SteadyError(tag,in,state,U,npredict) );
  } else if (lowerCase(code) == "sponge") {
    if (!(in >> tag)) error("Euler::Cannot read distributedcontrol tag",1);;
    p.reset( new Euler::Sponge(tag,in) );
  } else {
    comm->cout()<<code<<endl;
    error("Euler_Adjoint::make_Source() Illegal Source type",1);
  }
  return p;
}

/// Add Source terms
void Euler_Adjoint::add_source(const vField &Us, vField &Ur) {
  // cout << "Euler_Adjoint::add_source(vField &)" << endl;
  for (Source::db_citr i=Source_db.begin(); i!= Source_db.end(); ++i) {
    // cout << "Adding source: " << i->first << endl;
    i->second->adjoint_apply(t, Ustate, Us, Ur );
  }
}


/** Euler
    \warning: must give correct information on State/Adjoint boundary sides
    Ua = Adjoint Field
    Us = State   Field **/
void Euler_Adjoint::computeGrad(vField& Ua, vField& Us,
                                Ordinal istep, Ordinal sstep) {
  control->gradient( Us, Ua, g_control, istep, sstep );
}


void Euler_Adjoint::set_ic(vField &F, string ext) {
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
  //  cout << "IC code = " << code << endl;
  if (lowerCase(code) == "given") {
    F.fill(in);
  } else if (lowerCase(code) == "restart") {
    string rstfile;
    if (!(in>>rstfile)) {
      comm->cerr() << "Cannot read restart file name from " << fname << endl;
      comm->exit(1);
    }
    read(rstfile, F);
  } else if (lowerCase(code) == "wave") {
    // adjoint planar acoustic wave.  Is this correct? [SSC]
    for (LocalSize e=0; e<ne; e++) {
      for (LocalSize q=0; q<F[0]->el[e]->qtot; q++) {
        Point cxy = Point(F[0]->el[e]->C->x[q],F[0]->el[e]->C->y[q]);
        Scalar rho = 0.0;
        Scalar u   = 0.0;
        Scalar T   = pt5*0.01*exp(-pt5*pow((cxy.x - 0)/0.25,2))/2.0/2.0/20;
        Scalar v   = -10.0*T/2.0;
        F[0]->el[e]->u[q] =  rho;
        F[1]->el[e]->u[q] =  v;
        F[2]->el[e]->u[q] =  u;
        F[3]->el[e]->u[q] =  T;
      }
    }
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
