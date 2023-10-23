/*=============================================================================
  Module:     Adjoint Navier-Stokes Module

  Author:     Guoquan Chen and S. Scott Collis

  Copyright:  S. Scott Collis
              Department of Mechanical Engineering and Materials Science
              Rice University, MS 321
              Houston, TX 77005-1892
              (713) 348-3617
              collis@rice.edu
=============================================================================*/

/** \file  NS_Adjoint.cpp
    \brief Adjoint Navier-Stokes equations implementation

     Adjoint Navier-Stokes solver based on conservative variables

     Notes:
     -# All matrix-matrix, matrix-vector operations are obtained by using
        Maple
     -# Currently using the nondimensionalization from CNS2d.  the
        following parameters must be introduced to be consistent with the
        state solver: \f$Re\f$, \f$Ma\f$, \f$\mu\f$,
        \f$\lambda(-2/3\mu)\f$, \f$Pr\f$, \f$K\f$
*/

// system includes
#include <cmath>
#include <cassert>

// DGM includes
#include "Format.hpp"
#include "TimeInt.hpp"

// local includes
#include "Reo.hpp"
#include "Fluid.hpp"
#include "NS_State.hpp"
#include "NS_Adjoint.hpp"

namespace Reo {

// if defined then perform a projection to when computing diffusive flux
#define REO_PROJECT_DIFF_FLUX

// constructor
NS_Adjoint::NS_Adjoint(DGM::ArgList &args, const State* S,
                       const DGM::Comm::Ptr comm_ ) :
  Domain(args,comm_), Adjoint(S), Ustate_x(comm_), Ustate_y(comm_),
  Uv(comm_)
 {

  // setup local pointer to State
  state = dynamic_cast<const NS_State*>(state_);

  // set the number of fields in the domain
  Nfields = 4;

  npredict = params.get("npredict", 0);    // Length of optimization window

  vis    = params["vis"];              // viscosity
  Pr     = params["Pr"];               // Prandtl number for air
  gamma  = params["gamma"];            // ratio of specific heats

  Ma     = state->Ma;                  // Reference Ma number
  Re     = state->Re;                  // Reynolds number
  mu     = state->mu;                  // dynamic viscosity
  lambda = state->lambda;              // Stokes hypothesis
  Pr     = state->Pr;                  // Prandtl number
  K      = state->K;                   // thermal conductivity

  Ordinal p, q;
  p = params["p"];                     // polynomial order
  if ( !(q=params["q"]) ) q = p + 2;   // number of quadrature points
  nsd = params["nsd"];                 // number of space dimensions

  // read arguments (overrides defaults and input file)
  parse_args( args );

  vector<string> field_names;          // Field names
  field_names.push_back("R");

  // build a Field of Elements and Sides
  if (params["imesh"]) {
     error("NS_Adjoint internal mesh not supported",-1);
  } else if (params["bmesh"]) {
    U.push_back( new Field(p, q, root, field_names[0], partition, 1,
                           Reo::NumEqntype, p2i(NAVIER_STOKES), comm ) );
  } else {
    U.push_back( new Field(p, q, root, field_names[0], partition, comm ) );
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

  // fluid_properties class (not currently used)
  fluid = new Sutherland(gamma, 287.0, Pr, 1.716e-5, 110.0, 101000.0, 111.0);

  // make auxiliary Fields using copy constructor
  for (vField::size_type i=0; i<Nfields; i++) {
    Ut.push_back( new Field( U[i], root, U[i]->name ) );
    Uv.push_back( new Field( U[i], root, U[i]->name ) );
    Ustate.push_back( new Field( U[i], root, U[i]->name) );
    Ustate_x.push_back( new Field( U[i], root, U[i]->name) );  // State_x
    Ustate_y.push_back( new Field( U[i], root, U[i]->name) );  // State_y
  }

  zero_all_fields();

  // allocate workspace
  wk3.resize(20*max(Lmax(),Qmax()));
  wk4.resize(20*max(Lmax(),Qmax()));

  // make analysis object
  response = Response::factory(U, this);

  // setup BC database
  setup_BCdb();

  // setup Source term database
  setup_Sourcedb();

  set_TimeInt();
}

// Need to override the default from Domain to use adjoint methods
void NS_Adjoint::set_TimeInt( Ordinal ) {
  int inttype = params["inttype"];
  switch(inttype) {
  case TimeInt::FORWARD_EULER: {
    comm->cout() << "NS_Adjoint:: using Forward Euler" << endl;
    time_int = new ForwardEuler( this );
    break; }
  case TimeInt::TVD_RK: {
    comm->cout() << "NS_Adjoint:: using TVD RK" << endl;
    time_int = new TVD( this );
    break; }
  case TimeInt::RUNGE_KUTTA: {
    comm->cout() << "NS_Adjoint:: using Runge-Kutta-4" << endl;
    time_int = new RungeKutta( this );
    break; }
  case TimeInt::SSPRK: {
    comm->cout() << "NS_Adjoint:: using SSPRK" << endl;
    time_int = new SSPRK( this );
    break; }
  case TimeInt::LSRK14: {
    comm->cout() << "NS_Adjoint:: using LSRK14" << endl;
    time_int = new LSRK14( this );
    break; }
  default:
    comm->cerr() << "NS_Adjoint::set_TimeInt() "
                 << "Unsupported time integration type" << endl;
    comm->exit(DGM::FAILURE);
  }
}


void NS_Adjoint::zero_all_fields() {
  Domain::zero_all_fields();
  Ut.zero();
  Uv.zero();
  Ustate.zero();
  Ustate_x.zero();
  Ustate_y.zero();
}


void NS_Adjoint::time_derivative( vField &Us, vField &Uf ) {
  convection( Us, Uf );
  viscous_convection( Us, Uv, Uf);
  diffusion( Us, Uv, Uf);
  conv_source(Us,Uf);
  viscous_conv_source( Us, Uv, Uf);
  add_source(Us,Uf);
  project( Uf );
}

void NS_Adjoint::prestep( vField &F, const Ordinal istep,
                          const Ordinal sstep, const Scalar time) {
  state->load_field( Ustate, istep, sstep);
  control->set_data( istep, sstep );
  objective->set_data( Ustate, istep, sstep );
  computeGrad( F, Ustate, istep, sstep );
}


void NS_Adjoint::poststep( vField &F, const Ordinal istep,
                           const Ordinal sstep, const Scalar time) { }


void NS_Adjoint::convection( vField &Us, vField &Uf ) {
  Element *U[4], *F[4],*Fm[4];
  dVector u1, u2, u3,Fx1,Fx2,Fx3,Fx4,Fy1,Fy2,Fy3,Fy4,d;

  Scalar w[4],rho,m,n,E;

  Ustate.fill_sides();
  const_cast<NS_State*>(state)->enforce_bc(Ustate);
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

    Fx1.alias(wk3,0,qtot);
    Fx2.alias(wk3,qtot,qtot);
    Fx3.alias(wk3,2*qtot,qtot);
    Fx4.alias(wk3,3*qtot,qtot);
    Fy1.alias(wk3,4*qtot,qtot);
    Fy2.alias(wk3,5*qtot,qtot);
    Fy3.alias(wk3,6*qtot,qtot);
    Fy4.alias(wk3,7*qtot,qtot);
    d.alias(wk3,8*qtot,qtot);

    // F(u(x)),x = (transpose(F^1_q) \lambda),x
    // G(u(x)),y = (transpose(F^2_q) \lambda),x

    for (LocalSize q=0; q<qtot; q++) {

      for(vField::size_type i=0; i<Nfields; i++) w[i]=U[i]->u[q];
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
    for (vField::size_type i=0; i<Nfields; i++)
      U[i]->lift( F[i], F[i]->u );
  }
}

/*! For descriptions of the numerical fluxes
    See:  E.F. Toro, "Riemann Solvers and Numerical Methods for Fluid
          Dynamics," 2nd Edition, Springer, 1999, p. 305.
    \note Not updated for hanging nodes
*/
void NS_Adjoint::convective_flux(vField &Us, vField &Uf) {
  flux_type flux = LaxFriedrichs; //StegerWarming; //vanLeer;
  dVector sl(Nfields), sr(Nfields), f(Nfields), U(Nfields), Ua(Nfields);
  dVector slm(Nfields), srm(Nfields);
  Scalar ulm, clm, urm, crm;
  vector<Side *> Ssl(Nfields), Ssr(Nfields);
  vector<Side *> Sbl(Nfields), Sbr(Nfields); // mean flow field sides
  vector<Side *> Sfl(Nfields), Sfr(Nfields);
  dVector fpl(Nfields), fmr(Nfields),lam(Nfields);
  Scalar lmax;
  Scalar rho, m, n, E, p;
  dVector w(Nfields);
#ifdef REO_USE_GETSIDEMAPS
  iVector mapl, mapr;
#endif
  dVector Fx(Nfields),Fy(Nfields);

  for (LocalSize e=0; e<Us[0]->ne; e++) {                 // loop over elements
    Element* U = Us[0]->el[e];
    for (LocalSize i=0; i<Us[0]->el[e]->nSides(); i++) {  // loop over sides
      if (Us[0]->el[e]->side[i]->master()) {              // compute if master
        const LocalSize qtot = Us[0]->el[e]->side[i]->qtot(); // quad pts on side

        for (vField::size_type ni=0; ni<Nfields; ni++) {
          Ssl[ni] = Us[ni]->el[e]->side[i];            // local state side
          Ssr[ni] = Us[ni]->el[e]->side[i]->link;      // adjacent state side
          Sfl[ni] = Uf[ni]->el[e]->side[i];            // local flux side
          Sfr[ni] = Uf[ni]->el[e]->side[i]->link;      // adjacent flux side
          Sbl[ni] = Ustate[ni]->el[e]->side[i];       // local mean side
          Sbr[ni] = Ustate[ni]->el[e]->side[i]->link; // adjacent mean side
        }
#ifdef REO_USE_GETSIDEMAPS
        get_side_maps(Ssl[0], Ssr[0], mapl, mapr);
#endif

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
          for(vField::size_type k=0;k<Nfields;k++)
            sl[k] = Ssl[k]->u[ql];

          for(vField::size_type k=0;k<Nfields;k++) w[k]=Ssl[k]->u[ql];
          rho = Sbl[0]->u[ql];
          m   = Sbl[1]->u[ql];
          n   = Sbl[2]->u[ql];
          E   = Sbl[3]->u[ql];

          p = (gamma-1.0)*(E - 0.5*(m*m + n*n)/rho);
          clm = sqrt((gamma-1.0)*((E+p)/rho - 0.5*(m*m + n*n)/rho/rho));
          ulm = (m*nx +n*ny)/rho;

          // code produced by Maple
          Fx[0] = 0.5*(-3.0*w[1]*rho*m*m+w[1]*rho*gamma*m*m
                       +w[1]*rho*gamma*n*n-w[1]*rho*n*n - 2.0*m*n*w[2]*rho
                       -2.0*m*w[3]*gamma*E*rho+2.0*m*m*m*w[3]*gamma
                       +2.0*m*w[3]*gamma*n*n -2.0*m*m*m*w[3]
                       -2.0*m*w[3]*n*n)/(rho*rho*rho);
          Fx[1] = -0.5*(-2.0*w[0]*rho*rho-6.0*m*w[1]*rho+2.0*m*w[1]*rho*gamma
                        -2.0*n*w[2]*rho - 2.0*w[3]*gamma*E*rho
                        +3.0*w[3]*gamma*m*m +w[3]*gamma*n*n-3.0*w[3]*m*m
                        - w[3]*n*n)/(rho*rho);
          Fx[2] = -(n*w[1]*rho*gamma-n*w[1]*rho-m*w[2]*rho+m*n*w[3]*gamma
                    -m*n*w[3])/(rho*rho);
          Fx[3] = (w[1]*rho*gamma-w[1]*rho+m*w[3]*gamma)/rho;


          Fy[0] = 0.5*(-2.0*m*n*w[1]*rho-3.0*w[2]*rho*n*n+w[2]*rho*gamma*m*m
                       +w[2]*rho*gamma*n*n - w[2]*rho*m*m
                       -2.0*n*w[3]*gamma*E*rho + 2.0*n*w[3]*gamma*m*m
                       +2.0*n*n*n*w[3]*gamma- 2.0*n*w[3]*m*m
                       -2.0*n*n*n*w[3])/(rho*rho*rho);
          Fy[1] = (n*w[1]*rho-m*w[2]*rho*gamma+m*w[2]*rho-m*n*w[3]*gamma
                   +m*n*w[3])/(rho*rho);
          Fy[2] = -0.5*(-2.0*w[0]*rho*rho-2.0*m*w[1]*rho-6.0*n*w[2]*rho
                        +2.0*n*w[2]*rho*gamma - 2.0*w[3]*gamma*E*rho
                        +w[3]*gamma*m*m+3.0*w[3]*gamma*n*n
                        -w[3]*m*m-3.0*w[3]*n*n)/(rho*rho);
          Fy[3] = (w[2]*rho*gamma-w[2]*rho+n*gamma*w[3])/rho;

          Ssl[0]->u[ql] = Fx[0]*nx + Fy[0]*ny;
          Ssl[1]->u[ql] = Fx[1]*nx + Fy[1]*ny;
          Ssl[2]->u[ql] = Fx[2]*nx + Fy[2]*ny;
          Ssl[3]->u[ql] = Fx[3]*nx + Fy[3]*ny;

          // compute normal flux from exterior (right)
          // adjacent state
          for(vField::size_type k=0;k<Nfields;k++)
            sr[k] = Ssr[k]->u[qr];

          // put the adjacent flux on the state sides

          // Local sound speed from state flow
          for(vField::size_type k=0;k<Nfields;k++) w[k]=Ssr[k]->u[qr];
          rho = Sbr[0]->u[qr];
          m   = Sbr[1]->u[qr];
          n   = Sbr[2]->u[qr];
          E   = Sbr[3]->u[qr];

          p = (gamma-1.0)*(E - 0.5*(m*m + n*n)/rho);
          crm = sqrt((gamma-1.0)*((E+p)/rho - 0.5*(m*m + n*n)/rho/rho));
          urm = (m*nx +n*ny)/rho;

          // code produced by Maple

          Fx[0] = 0.5*(-3.0*w[1]*rho*m*m+w[1]*rho*gamma*m*m
                       +w[1]*rho*gamma*n*n-w[1]*rho*n*n - 2.0*m*n*w[2]*rho
                       -2.0*m*w[3]*gamma*E*rho+2.0*m*m*m*w[3]*gamma
                       +2.0*m*w[3]*gamma*n*n -2.0*m*m*m*w[3]
                       -2.0*m*w[3]*n*n)/(rho*rho*rho);
          Fx[1] = -0.5*(-2.0*w[0]*rho*rho-6.0*m*w[1]*rho+2.0*m*w[1]*rho*gamma
                        -2.0*n*w[2]*rho - 2.0*w[3]*gamma*E*rho
                        +3.0*w[3]*gamma*m*m +w[3]*gamma*n*n-3.0*w[3]*m*m
                        - w[3]*n*n)/(rho*rho);
          Fx[2] = -(n*w[1]*rho*gamma-n*w[1]*rho-m*w[2]*rho+m*n*w[3]*gamma
                    -m*n*w[3])/(rho*rho);
          Fx[3] = (w[1]*rho*gamma-w[1]*rho+m*w[3]*gamma)/rho;


          Fy[0] = 0.5*(-2.0*m*n*w[1]*rho-3.0*w[2]*rho*n*n+w[2]*rho*gamma*m*m
                       +w[2]*rho*gamma*n*n - w[2]*rho*m*m
                       -2.0*n*w[3]*gamma*E*rho+2.0*n*w[3]*gamma*m*m
                       +2.0*n*n*n*w[3]*gamma- 2.0*n*w[3]*m*m
                       -2.0*n*n*n*w[3])/(rho*rho*rho);
          Fy[1] = (n*w[1]*rho-m*w[2]*rho*gamma+m*w[2]*rho-m*n*w[3]*gamma
                   +m*n*w[3])/(rho*rho);
          Fy[2] = -0.5*(-2.0*w[0]*rho*rho-2.0*m*w[1]*rho-6.0*n*w[2]*rho
                        +2.0*n*w[2]*rho*gamma - 2.0*w[3]*gamma*E*rho
                        +w[3]*gamma*m*m+3.0*w[3]*gamma*n*n
                        -w[3]*m*m-3.0*w[3]*n*n)/(rho*rho);
          Fy[3] = (w[2]*rho*gamma-w[2]*rho+n*gamma*w[3])/rho;

          Ssr[0]->u[qr] = Fx[0]*nx + Fy[0]*ny;
          Ssr[1]->u[qr] = Fx[1]*nx + Fy[1]*ny;
          Ssr[2]->u[qr] = Fx[2]*nx + Fy[2]*ny;
          Ssr[3]->u[qr] = Fx[3]*nx + Fy[3]*ny;

          switch (flux) {
          case LaxFriedrichs:
            lmax = zero;
            lam[0] = ulm;
            lam[1] = ulm+clm;
            lam[2] = ulm-clm;
            lam[3] = ulm;
            // left flux
            for(vField::size_type j=0; j<Nfields;j++) {
              lmax = max(lmax,fabs(lam[j]));
              fpl[j] = Ssl[j]->u[ql];
            }
            lam[0] = urm;
            lam[1] = urm+crm;
            lam[2] = urm-crm;
            lam[3] = urm;
            // right flux
            for(vField::size_type j=0; j<Nfields; j++) {
              lmax = max(lmax,fabs(lam[j]));
              fmr[j] = Ssr[j]->u[qr];
            }
            // Lax-Friedrichs flux
            f[0] = pt5 * ( fpl[0] + fmr[0] - lmax * ( sl[0] - sr[0] ) );
            f[1] = pt5 * ( fpl[1] + fmr[1] - lmax * ( sl[1] - sr[1] ) );
            f[2] = pt5 * ( fpl[2] + fmr[2] - lmax * ( sl[2] - sr[2] ) );
            f[3] = pt5 * ( fpl[3] + fmr[3] - lmax * ( sl[3] - sr[3] ) );
            break;
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

// Calculate:  Sum[(tran(D_Gi/D_Q]*Lambda)_xi]
void NS_Adjoint::viscous_convection( vField &Us, vField &Uf, vField &Ur) {
  Element *U[4], *F[4],*Sm[4];
  dVector Fx1,Fx2,Fx3,Fx4,Fy1,Fy2,Fy3,Fy4,d;
  Scalar w[4],rho,m,n,E;
  dVector r_x,r_y,ru_x,ru_y,rv_x,rv_y,E_x,E_y;
  Scalar s1,s2,s3;

  // fill/share side & enforceBC for State it only needs to be done once for
  // the state

  // Warning: I didn't consider the jump for the state gradient [gqchen]
  // compute the gradient of the state solution

  // Ustate_x = the D_Ustate_x
  // Ustate_y = the D_Ustate_y
  for (LocalSize e=0; e<Us[0]->ne; e++) {
    // local version of the state solution
    Sm[0] = Ustate[0]->el[e];
    Sm[1] = Ustate[1]->el[e];
    Sm[2] = Ustate[2]->el[e];
    Sm[3] = Ustate[3]->el[e];

    Sm[0]->gradient(Ustate[0]->el[e]->u,Ustate_x[0]->el[e]->u,
                    Ustate_y[0]->el[e]->u);
    Sm[1]->gradient(Ustate[1]->el[e]->u,Ustate_x[1]->el[e]->u,
                    Ustate_y[1]->el[e]->u);
    Sm[2]->gradient(Ustate[2]->el[e]->u,Ustate_x[2]->el[e]->u,
                    Ustate_y[2]->el[e]->u);
    Sm[3]->gradient(Ustate[3]->el[e]->u,Ustate_x[3]->el[e]->u,
                    Ustate_y[3]->el[e]->u);
  }

  Ustate_x.fill_sides();
  Ustate_y.fill_sides();

  // Enforce the boundary state derivate [gqchen] I use very simple
  // extrapolation get the state derivate @BC possible problem ???
  enforce_state_derivate_bc(Ustate_x);
  enforce_state_derivate_bc(Ustate_y);

  Ustate_x.share_sides();
  Ustate_y.share_sides();

  Us.fill_sides();
  enforce_bc(Us);
  Us.share_sides();

  // central flux
  // Do the average flux operator  --central flux  [gqchen]
  viscous_convective_flux( Us, Uf );

  for (LocalSize e=0; e<Us[0]->ne; e++) {

    // local version of the adjoint
    U[0] = Us[0]->el[e];
    U[1] = Us[1]->el[e];
    U[2] = Us[2]->el[e];
    U[3] = Us[3]->el[e];

    // local version of the  flux
    F[0] = Uf[0]->el[e];
    F[1] = Uf[1]->el[e];
    F[2] = Uf[2]->el[e];
    F[3] = Uf[3]->el[e];

    // local version of the state
    Sm[0] = Ustate[0]->el[e];
    Sm[1] = Ustate[1]->el[e];
    Sm[2] = Ustate[2]->el[e];
    Sm[3] = Ustate[3]->el[e];

    dVector r(Sm[0]->u);  //
    dVector ru(Sm[1]->u); //
    dVector rv(Sm[2]->u); //
    dVector En(Sm[3]->u); //

    const Ordinal qtot = Us[0]->el[e]->qtot;

    r_x.alias(Ustate_x[0]->el[e]->u);
    r_y.alias(Ustate_y[0]->el[e]->u);
    ru_x.alias(Ustate_x[1]->el[e]->u);
    ru_y.alias(Ustate_y[1]->el[e]->u);
    rv_x.alias(Ustate_x[2]->el[e]->u);
    rv_y.alias(Ustate_y[2]->el[e]->u);
    E_x.alias(Ustate_x[3]->el[e]->u);
    E_y.alias(Ustate_y[3]->el[e]->u);

    Fx1.alias(wk3,0,qtot);
    Fx2.alias(wk3,qtot,qtot);
    Fx3.alias(wk3,2*qtot,qtot);
    Fx4.alias(wk3,3*qtot,qtot);
    Fy1.alias(wk3,4*qtot,qtot);
    Fy2.alias(wk3,5*qtot,qtot);
    Fy3.alias(wk3,6*qtot,qtot);
    Fy4.alias(wk3,7*qtot,qtot);
    d.alias(wk3,8*qtot,qtot);

    ///! VALIDATE [gqchen]

    //  D^1(u(x)),x = (transpose(G^1_q) \lambda),x
    //  D^2(u(x)),y = (transpose(G^2_q) \lambda),y

    for (LocalSize q=0; q<qtot; q++) {

      //gamma = gamma;
      for(vField::size_type i=0;i<Nfields;i++) w[i]=U[i]->u[q];
      rho = Sm[0]->u[q];
      m   = Sm[1]->u[q];
      n   = Sm[2]->u[q];
      E   = Sm[3]->u[q];

      s3 = 2.0*w[1]*rho*Pr*lambda*n*r_y[q]+4.0*w[1]*rho*Pr*mu*m*r_x[q]
        -2.0*w[1]*rho*rho*Pr*mu*ru_x[q]-mu*w[2]*rho*rho*Pr*ru_y[q]
        +2.0*mu*w[2]*rho*Pr*m*r_y[q]-mu*w[2]*rho*rho*Pr*rv_x[q]
        +2.0*mu*w[2]*rho*Pr*n*r_x[q]+2.0*w[3]*gamma*K*rho*m*ru_x[q]
        +3.0*w[3]*mu*n*Pr*m*r_y[q]+2.0*w[3]*gamma*K*rho*n*rv_x[q]
        -2.0*w[3]*mu*n*Pr*rv_x[q]*rho+2.0*w[3]*gamma*K*r_x[q]*E*rho
        +3.0*w[3]*m*m*Pr*lambda*r_x[q];
      s2 = s3-2.0*w[3]*mu*n*Pr*ru_y[q]*rho+3.0*w[3]*mu*n*n*Pr*r_x[q]
        -3.0*w[3]*gamma*K*r_x[q]*n*n-w[3]*gamma*K*E_x[q]*rho*rho
        -3.0*w[3]*gamma*K*r_x[q]*m*m-2.0*w[3]*m*Pr*lambda*ru_x[q]*rho
        +3.0*w[3]*m*Pr*lambda*n*r_y[q]-4.0*w[3]*m*Pr*mu*ru_x[q]*rho
        -w[1]*rho*rho*Pr*lambda*ru_x[q]+6.0*w[3]*m*m*Pr*mu*r_x[q]
        -2.0*w[3]*m*Pr*lambda*rv_y[q]*rho+2.0*w[1]*rho*Pr*lambda*m*r_x[q]
        -w[1]*rho*rho*Pr*lambda*rv_y[q];
      s3 = 1/Pr;
      s1 = s2*s3;
      s2 = 1/(rho*rho*rho*rho)/Re;
      Fx1[q] = s1*s2;
      Fx2[q] = -(2.0*r_x[q]*w[1]*rho*Pr*mu+r_x[q]*w[1]*rho*Pr*lambda
                 +r_y[q]*mu*w[2]*rho*Pr+4.0*w[3]*r_x[q]*m*Pr*mu
                 +2.0*w[3]*r_x[q]*m*Pr*lambda-2.0*w[3]*Pr*mu*ru_x[q]*rho
                 -w[3]*Pr*lambda*ru_x[q]*rho-w[3]*Pr*lambda*rv_y[q]*rho
                 +w[3]*Pr*lambda*n*r_y[q]+w[3]*r_y[q]*mu*n*Pr
                 +w[3]*gamma*K*ru_x[q]*rho
                 -2.0*w[3]*gamma*K*m*r_x[q])/Pr/(rho*rho*rho)/Re;
      Fx3[q] = -(lambda*r_y[q]*w[1]*rho*Pr+r_x[q]*w[2]*rho*Pr*mu
                 +w[3]*lambda*r_y[q]*m*Pr+2.0*w[3]*r_x[q]*mu*n*Pr
                 -w[3]*mu*Pr*ru_y[q]*rho+w[3]*mu*Pr*m*r_y[q]
                 -w[3]*mu*Pr*rv_x[q]*rho+w[3]*gamma*K*rv_x[q]*rho
                 -2.0*w[3]*gamma*K*n*r_x[q])/Pr/(rho*rho*rho)/Re;
      Fx4[q] = -gamma/(rho*rho)*r_x[q]*K/Re/Pr*w[3];

      s3 = -w[2]*rho*rho*Pr*lambda*ru_x[q]+2.0*w[2]*rho*Pr*lambda*m*r_x[q]
        -w[2]*rho*rho*Pr*lambda*rv_y[q]+2.0*w[2]*rho*Pr*lambda*n*r_y[q]
        -2.0*w[3]*n*Pr*lambda*rv_y[q]*rho-4.0*w[3]*n*Pr*mu*rv_y[q]*rho
        +3.0*w[3]*mu*m*m*Pr*r_y[q]-w[3]*gamma*K*E_y[q]*rho*rho
        -3.0*w[3]*gamma*K*r_y[q]*m*m-3.0*w[3]*gamma*K*r_y[q]*n*n
        +3.0*w[3]*n*n*Pr*lambda*r_y[q]-2.0*w[3]*mu*m*Pr*rv_x[q]*rho
        +3.0*w[3]*mu*m*Pr*n*r_x[q];
      s2 = s3-2.0*w[3]*mu*m*Pr*ru_y[q]*rho+2.0*w[3]*gamma*K*r_y[q]*E*rho
        +2.0*w[3]*gamma*K*rho*n*rv_y[q]+2.0*w[3]*gamma*K*rho*m*ru_y[q]
        -mu*w[1]*rho*rho*Pr*ru_y[q]+6.0*w[3]*n*n*Pr*mu*r_y[q]
        +3.0*w[3]*n*Pr*lambda*m*r_x[q]-2.0*w[3]*n*Pr*lambda*ru_x[q]*rho
        +4.0*w[2]*rho*Pr*mu*n*r_y[q]-2.0*w[2]*rho*rho*Pr*mu*rv_y[q]
        +2.0*mu*w[1]*rho*Pr*n*r_x[q]+2.0*mu*w[1]*rho*Pr*m*r_y[q]
        -mu*w[1]*rho*rho*Pr*rv_x[q];
      s3 = 1/Pr;
      s1 = s2*s3;
      s2 = 1/(rho*rho*rho*rho)/Re;

      Fy1[q] = s1*s2;
      Fy2[q] = -(r_y[q]*mu*w[1]*rho*Pr+r_x[q]*w[2]*rho*Pr*lambda
                 +2.0*w[3]*mu*Pr*m*r_y[q]-w[3]*mu*Pr*ru_y[q]*rho
                 -w[3]*mu*Pr*rv_x[q]*rho+w[3]*r_x[q]*mu*n*Pr
                 +w[3]*lambda*r_x[q]*n*Pr+w[3]*gamma*K*ru_y[q]*rho
                 -2.0*w[3]*gamma*K*m*r_y[q])/Pr/(rho*rho*rho)/Re;
      Fy3[q] = -(r_x[q]*w[1]*rho*Pr*mu+2.0*r_y[q]*mu*w[2]*rho*Pr
                 +lambda*r_y[q]*w[2]*rho*Pr+w[3]*r_x[q]*m*Pr*mu
                 +4.0*w[3]*r_y[q]*mu*n*Pr+2.0*w[3]*Pr*lambda*n*r_y[q]
                 -2.0*w[3]*Pr*mu*rv_y[q]*rho-w[3]*Pr*lambda*rv_y[q]*rho
                 -w[3]*Pr*lambda*ru_x[q]*rho+w[3]*r_x[q]*m*Pr*lambda
                 +w[3]*gamma*K*rv_y[q]*rho-2.0*w[3]*gamma*K*n*r_y[q]
        )/Pr/(rho*rho*rho)/Re;
      Fy4[q] = -gamma/(rho*rho)*r_y[q]*K/Re/Pr*w[3];
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
    for (vField::size_type i=0; i<Nfields; i++)
      U[i]->lift( F[i], F[i]->u );
  }
  scale(-1.0,Uf);  // I currently put everything on the LHS
  for (vField::size_type k=0; k<Uf.size(); k++) add( Uf[k], Ur[k] );

}

// It is not helpful, since we are only using the central flux, the cheaper
// should be only to define the central operator at the boundary edge [gqchen]
void NS_Adjoint::viscous_convective_flux(vField &Us, vField &Uf) {
  flux_type flux = LaxFriedrichs; //StegerWarming; //vanLeer;
  dVector sl(Nfields), sr(Nfields), f(Nfields);
  dVector slm(Nfields), srm(Nfields);
  vector<Side *> Ssl(Nfields), Ssr(Nfields);
  vector<Side *> Sbl(Nfields), Sbr(Nfields);
  vector<Side *> Sfl(Nfields), Sfr(Nfields);
  dVector fpl(Nfields), fmr(Nfields),lam(Nfields);
  Scalar rho, m, n, E;
  dVector w(Nfields);
#ifdef REO_USE_GETSIDEMAPS
  iVector mapl, mapr;
#endif
  dVector Fx(Nfields), Fy(Nfields);
  Scalar s1, s2, s3;
  vector<Side *> Sbl_x(Nfields), Sbr_x(Nfields);
  vector<Side *> Sbl_y(Nfields), Sbr_y(Nfields);

  ///! VALIDATE [gqchen]
  for (LocalSize e=0; e<Us[0]->ne; e++) {                 // loop over elements
    Element* U = Us[0]->el[e];
    for (LocalSize i=0; i<Us[0]->el[e]->nSides(); i++) {  // loop over sides
      if (Us[0]->el[e]->side[i]->master()) {              // compute if master
        const LocalSize qtot = Us[0]->el[e]->side[i]->qtot();
        for (vField::size_type ni=0; ni<Nfields; ni++) {
          Ssl[ni] = Us[ni]->el[e]->side[i];             // left state side
          Ssr[ni] = Us[ni]->el[e]->side[i]->link;       // right state side
          Sfl[ni] = Uf[ni]->el[e]->side[i];             // left flux side
          Sfr[ni] = Uf[ni]->el[e]->side[i]->link;       // right flux side
          Sbl[ni] = Ustate[ni]->el[e]->side[i];         // left base side
          Sbr[ni] = Ustate[ni]->el[e]->side[i]->link;   // right base side
          Sbl_x[ni] = Ustate_x[ni]->el[e]->side[i];
          Sbr_x[ni] = Ustate_x[ni]->el[e]->side[i]->link;
          Sbl_y[ni] = Ustate_y[ni]->el[e]->side[i];
          Sbr_y[ni] = Ustate_y[ni]->el[e]->side[i]->link;
        }
#ifdef REO_USE_GETSIDEMAPS
        get_side_maps(Ssl[0], Ssr[0], mapl, mapr);
#endif

        dVector r_x(Sbl_x[0]->u);
        dVector r_y(Sbl_y[0]->u);
        dVector ru_x(Sbl_x[1]->u);
        dVector ru_y(Sbl_y[1]->u);
        dVector rv_x(Sbl_x[2]->u);
        dVector rv_y(Sbl_y[2]->u);
        dVector E_x(Sbl_x[3]->u);
        dVector E_y(Sbl_y[3]->u);

        for (LocalSize q=0; q<qtot; q++) {                 // loop side q pts

#ifdef REO_USE_GETSIDEMAPS
          const LocalSize ql = mapl[q];
#else
          const LocalSize ql = U->sideMap(Ssl[0], q);
#endif

          const Scalar nx = Us[0]->el[e]->side[i]->nx(ql);
          const Scalar ny = Us[0]->el[e]->side[i]->ny(ql);

          // compute normal flux from interior (left)

          //From solution U
          for(vField::size_type k=0;k<Nfields;k++)
            sl[k] = Ssl[k]->u[ql];

          for(vField::size_type k=0;k<Nfields;k++) w[k]=Ssl[k]->u[ql];
          rho = Sbl[0]->u[ql];
          m   = Sbl[1]->u[ql];
          n   = Sbl[2]->u[ql];
          E   = Sbl[3]->u[ql];

          ///  code produced by Maple
          s3 = 2.0*w[1]*rho*Pr*lambda*n*r_y[ql]+4.0*w[1]*rho*Pr*mu*m*r_x[ql]
            -2.0*w[1]*rho*rho*Pr*mu*ru_x[ql]-mu*w[2]*rho*rho*Pr*ru_y[ql]
            +2.0*mu*w[2]*rho*Pr*m*r_y[ql]-mu*w[2]*rho*rho*Pr*rv_x[ql]
            +2.0*mu*w[2]*rho*Pr*n*r_x[ql]+2.0*w[3]*gamma*K*rho*m*ru_x[ql]
            +3.0*w[3]*mu*n*Pr*m*r_y[ql]+2.0*w[3]*gamma*K*rho*n*rv_x[ql]
            -2.0*w[3]*mu*n*Pr*rv_x[ql]*rho+2.0*w[3]*gamma*K*r_x[ql]*E*rho
            +3.0*w[3]*m*m*Pr*lambda*r_x[ql];
          s2 = s3-2.0*w[3]*mu*n*Pr*ru_y[ql]*rho+3.0*w[3]*mu*n*n*Pr*r_x[ql]
            -3.0*w[3]*gamma*K*r_x[ql]*n*n-w[3]*gamma*K*E_x[ql]*rho*rho
            -3.0*w[3]*gamma*K*r_x[ql]*m*m-2.0*w[3]*m*Pr*lambda*ru_x[ql]*rho
            +3.0*w[3]*m*Pr*lambda*n*r_y[ql]-4.0*w[3]*m*Pr*mu*ru_x[ql]*rho
            -w[1]*rho*rho*Pr*lambda*ru_x[ql]+6.0*w[3]*m*m*Pr*mu*r_x[ql]
            -2.0*w[3]*m*Pr*lambda*rv_y[ql]*rho
            +2.0*w[1]*rho*Pr*lambda*m*r_x[ql]
            -w[1]*rho*rho*Pr*lambda*rv_y[ql];
          s3 = 1/Pr;
          s1 = s2*s3;
          s2 = 1/(rho*rho*rho*rho)/Re;
          Fx[0] = s1*s2;
          Fx[1] = -(2.0*r_x[ql]*w[1]*rho*Pr*mu+r_x[ql]*w[1]*rho*Pr*lambda
                    +r_y[ql]*mu*w[2]*rho*Pr+4.0*w[3]*r_x[ql]*m*Pr*mu
                    +2.0*w[3]*r_x[ql]*m*Pr*lambda
                    -2.0*w[3]*Pr*mu*ru_x[ql]*rho
                    -w[3]*Pr*lambda*ru_x[ql]*rho-w[3]*Pr*lambda*rv_y[ql]*rho
                    +w[3]*Pr*lambda*n*r_y[ql]+w[3]*r_y[ql]*mu*n*Pr
                    +w[3]*gamma*K*ru_x[ql]*rho
                    -2.0*w[3]*gamma*K*m*r_x[ql])/Pr/(rho*rho*rho)/Re;
          Fx[2] = -(lambda*r_y[ql]*w[1]*rho*Pr+r_x[ql]*w[2]*rho*Pr*mu
                    +w[3]*lambda*r_y[ql]*m*Pr+2.0*w[3]*r_x[ql]*mu*n*Pr
                    -w[3]*mu*Pr*ru_y[ql]*rho+w[3]*mu*Pr*m*r_y[ql]
                    -w[3]*mu*Pr*rv_x[ql]*rho+w[3]*gamma*K*rv_x[ql]*rho
                    -2.0*w[3]*gamma*K*n*r_x[ql])/Pr/(rho*rho*rho)/Re;
          Fx[3] = -gamma/(rho*rho)*r_x[ql]*K/Re/Pr*w[3];

          s3 = -w[2]*rho*rho*Pr*lambda*ru_x[ql]
            +2.0*w[2]*rho*Pr*lambda*m*r_x[ql]
            -w[2]*rho*rho*Pr*lambda*rv_y[ql]
            +2.0*w[2]*rho*Pr*lambda*n*r_y[ql]
            -2.0*w[3]*n*Pr*lambda*rv_y[ql]*rho-4.0*w[3]*n*Pr*mu*rv_y[ql]*rho
            +3.0*w[3]*mu*m*m*Pr*r_y[ql]-w[3]*gamma*K*E_y[ql]*rho*rho
            -3.0*w[3]*gamma*K*r_y[ql]*m*m-3.0*w[3]*gamma*K*r_y[ql]*n*n
            +3.0*w[3]*n*n*Pr*lambda*r_y[ql]-2.0*w[3]*mu*m*Pr*rv_x[ql]*rho
            +3.0*w[3]*mu*m*Pr*n*r_x[ql];
          s2 = s3-2.0*w[3]*mu*m*Pr*ru_y[ql]*rho
            +2.0*w[3]*gamma*K*r_y[ql]*E*rho
            +2.0*w[3]*gamma*K*rho*n*rv_y[ql]+2.0*w[3]*gamma*K*rho*m*ru_y[ql]
            -mu*w[1]*rho*rho*Pr*ru_y[ql]+6.0*w[3]*n*n*Pr*mu*r_y[ql]
            +3.0*w[3]*n*Pr*lambda*m*r_x[ql]
            -2.0*w[3]*n*Pr*lambda*ru_x[ql]*rho
            +4.0*w[2]*rho*Pr*mu*n*r_y[ql]-2.0*w[2]*rho*rho*Pr*mu*rv_y[ql]
            +2.0*mu*w[1]*rho*Pr*n*r_x[ql]+2.0*mu*w[1]*rho*Pr*m*r_y[ql]
            -mu*w[1]*rho*rho*Pr*rv_x[ql];
          s3 = 1/Pr;
          s1 = s2*s3;
          s2 = 1/(rho*rho*rho*rho)/Re;

          Fy[0] = s1*s2;
          Fy[1] = -(r_y[ql]*mu*w[1]*rho*Pr+r_x[ql]*w[2]*rho*Pr*lambda
                    +2.0*w[3]*mu*Pr*m*r_y[ql]-w[3]*mu*Pr*ru_y[ql]*rho
                    -w[3]*mu*Pr*rv_x[ql]*rho+w[3]*r_x[ql]*mu*n*Pr
                    +w[3]*lambda*r_x[ql]*n*Pr+w[3]*gamma*K*ru_y[ql]*rho
                    -2.0*w[3]*gamma*K*m*r_y[ql])/Pr/(rho*rho*rho)/Re;
          Fy[2] = -(r_x[ql]*w[1]*rho*Pr*mu+2.0*r_y[ql]*mu*w[2]*rho*Pr
                    +lambda*r_y[ql]*w[2]*rho*Pr+w[3]*r_x[ql]*m*Pr*mu
                    +4.0*w[3]*r_y[ql]*mu*n*Pr+2.0*w[3]*Pr*lambda*n*r_y[ql]
                    -2.0*w[3]*Pr*mu*rv_y[ql]*rho-w[3]*Pr*lambda*rv_y[ql]*rho
                    -w[3]*Pr*lambda*ru_x[ql]*rho+w[3]*r_x[ql]*m*Pr*lambda
                    +w[3]*gamma*K*rv_y[ql]*rho-2.0*w[3]*gamma*K*n*r_y[ql]
            )/Pr/(rho*rho*rho)/Re;
          Fy[3] = -gamma/(rho*rho)*r_y[ql]*K/Re/Pr*w[3];


          Ssl[0]->u[ql] = Fx[0]*nx + Fy[0]*ny;
          Ssl[1]->u[ql] = Fx[1]*nx + Fy[1]*ny;
          Ssl[2]->u[ql] = Fx[2]*nx + Fy[2]*ny;
          Ssl[3]->u[ql] = Fx[3]*nx + Fy[3]*ny;
        }

        r_x.alias(Sbr_x[0]->u);
        r_y.alias(Sbr_y[0]->u);
        ru_x.alias(Sbr_x[1]->u);
        ru_y.alias(Sbr_y[1]->u);
        rv_x.alias(Sbr_x[2]->u);
        rv_y.alias(Sbr_y[2]->u);
        E_x.alias(Sbr_x[3]->u);
        E_y.alias(Sbr_y[3]->u);

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

          // compute normal flux from exterior (right)
          // adjacent state
          for(vField::size_type k=0;k<Nfields;k++)
            sr[k] = Ssr[k]->u[qr];

          // put the adjacent flux on the state sides
          for(vField::size_type k=0;k<Nfields;k++) w[k]=Ssr[k]->u[qr];
          rho = Sbr[0]->u[qr];
          m   = Sbr[1]->u[qr];
          n   = Sbr[2]->u[qr];
          E   = Sbr[3]->u[qr];

          s3 = 2.0*w[1]*rho*Pr*lambda*n*r_y[qr]+4.0*w[1]*rho*Pr*mu*m*r_x[qr]
            -2.0*w[1]*rho*rho*Pr*mu*ru_x[qr]-mu*w[2]*rho*rho*Pr*ru_y[qr]
            +2.0*mu*w[2]*rho*Pr*m*r_y[qr]-mu*w[2]*rho*rho*Pr*rv_x[qr]
            +2.0*mu*w[2]*rho*Pr*n*r_x[qr]+2.0*w[3]*gamma*K*rho*m*ru_x[qr]
            +3.0*w[3]*mu*n*Pr*m*r_y[qr]+2.0*w[3]*gamma*K*rho*n*rv_x[qr]
            -2.0*w[3]*mu*n*Pr*rv_x[qr]*rho+2.0*w[3]*gamma*K*r_x[qr]*E*rho
            +3.0*w[3]*m*m*Pr*lambda*r_x[qr];
          s2 = s3-2.0*w[3]*mu*n*Pr*ru_y[qr]*rho+3.0*w[3]*mu*n*n*Pr*r_x[qr]
            -3.0*w[3]*gamma*K*r_x[qr]*n*n-w[3]*gamma*K*E_x[qr]*rho*rho
            -3.0*w[3]*gamma*K*r_x[qr]*m*m-2.0*w[3]*m*Pr*lambda*ru_x[qr]*rho
            +3.0*w[3]*m*Pr*lambda*n*r_y[qr]-4.0*w[3]*m*Pr*mu*ru_x[qr]*rho
            -w[1]*rho*rho*Pr*lambda*ru_x[qr]+6.0*w[3]*m*m*Pr*mu*r_x[qr]
            -2.0*w[3]*m*Pr*lambda*rv_y[qr]*rho
            +2.0*w[1]*rho*Pr*lambda*m*r_x[qr]
            -w[1]*rho*rho*Pr*lambda*rv_y[qr];
          s3 = 1/Pr;
          s1 = s2*s3;
          s2 = 1/(rho*rho*rho*rho)/Re;
          Fx[0] = s1*s2;
          Fx[1] = -(2.0*r_x[qr]*w[1]*rho*Pr*mu+r_x[qr]*w[1]*rho*Pr*lambda
                    +r_y[qr]*mu*w[2]*rho*Pr+4.0*w[3]*r_x[qr]*m*Pr*mu
                    +2.0*w[3]*r_x[qr]*m*Pr*lambda
                    -2.0*w[3]*Pr*mu*ru_x[qr]*rho
                    -w[3]*Pr*lambda*ru_x[qr]*rho-w[3]*Pr*lambda*rv_y[qr]*rho
                    +w[3]*Pr*lambda*n*r_y[qr]+w[3]*r_y[qr]*mu*n*Pr
                    +w[3]*gamma*K*ru_x[qr]*rho
                    -2.0*w[3]*gamma*K*m*r_x[qr])/Pr/(rho*rho*rho)/Re;
          Fx[2] = -(lambda*r_y[qr]*w[1]*rho*Pr+r_x[qr]*w[2]*rho*Pr*mu
                    +w[3]*lambda*r_y[qr]*m*Pr+2.0*w[3]*r_x[qr]*mu*n*Pr
                    -w[3]*mu*Pr*ru_y[qr]*rho+w[3]*mu*Pr*m*r_y[qr]
                    -w[3]*mu*Pr*rv_x[qr]*rho+w[3]*gamma*K*rv_x[qr]*rho
                    -2.0*w[3]*gamma*K*n*r_x[qr])/Pr/(rho*rho*rho)/Re;
          Fx[3] = -gamma/(rho*rho)*r_x[qr]*K/Re/Pr*w[3];

          s3 = -w[2]*rho*rho*Pr*lambda*ru_x[qr]
            +2.0*w[2]*rho*Pr*lambda*m*r_x[qr]
            -w[2]*rho*rho*Pr*lambda*rv_y[qr]
            +2.0*w[2]*rho*Pr*lambda*n*r_y[qr]
            -2.0*w[3]*n*Pr*lambda*rv_y[qr]*rho-4.0*w[3]*n*Pr*mu*rv_y[qr]*rho
            +3.0*w[3]*mu*m*m*Pr*r_y[qr]-w[3]*gamma*K*E_y[qr]*rho*rho
            -3.0*w[3]*gamma*K*r_y[qr]*m*m-3.0*w[3]*gamma*K*r_y[qr]*n*n
            +3.0*w[3]*n*n*Pr*lambda*r_y[qr]-2.0*w[3]*mu*m*Pr*rv_x[qr]*rho
            +3.0*w[3]*mu*m*Pr*n*r_x[qr];
          s2 = s3-2.0*w[3]*mu*m*Pr*ru_y[qr]*rho
            +2.0*w[3]*gamma*K*r_y[qr]*E*rho
            +2.0*w[3]*gamma*K*rho*n*rv_y[qr]+2.0*w[3]*gamma*K*rho*m*ru_y[qr]
            -mu*w[1]*rho*rho*Pr*ru_y[qr]+6.0*w[3]*n*n*Pr*mu*r_y[qr]
            +3.0*w[3]*n*Pr*lambda*m*r_x[qr]
            -2.0*w[3]*n*Pr*lambda*ru_x[qr]*rho
            +4.0*w[2]*rho*Pr*mu*n*r_y[qr]-2.0*w[2]*rho*rho*Pr*mu*rv_y[qr]
            +2.0*mu*w[1]*rho*Pr*n*r_x[qr]+2.0*mu*w[1]*rho*Pr*m*r_y[qr]
            -mu*w[1]*rho*rho*Pr*rv_x[qr];
          s3 = 1/Pr;
          s1 = s2*s3;
          s2 = 1/(rho*rho*rho*rho)/Re;

          Fy[0] = s1*s2;
          Fy[1] = -(r_y[qr]*mu*w[1]*rho*Pr+r_x[qr]*w[2]*rho*Pr*lambda
                    +2.0*w[3]*mu*Pr*m*r_y[qr]-w[3]*mu*Pr*ru_y[qr]*rho
                    -w[3]*mu*Pr*rv_x[qr]*rho+w[3]*r_x[qr]*mu*n*Pr
                    +w[3]*lambda*r_x[qr]*n*Pr+w[3]*gamma*K*ru_y[qr]*rho
                    -2.0*w[3]*gamma*K*m*r_y[qr])/Pr/(rho*rho*rho)/Re;
          Fy[2] = -(r_x[qr]*w[1]*rho*Pr*mu+2.0*r_y[qr]*mu*w[2]*rho*Pr
                    +lambda*r_y[qr]*w[2]*rho*Pr+w[3]*r_x[qr]*m*Pr*mu
                    +4.0*w[3]*r_y[qr]*mu*n*Pr+2.0*w[3]*Pr*lambda*n*r_y[qr]
                    -2.0*w[3]*Pr*mu*rv_y[qr]*rho-w[3]*Pr*lambda*rv_y[qr]*rho
                    -w[3]*Pr*lambda*ru_x[qr]*rho+w[3]*r_x[qr]*m*Pr*lambda
                    +w[3]*gamma*K*rv_y[qr]*rho-2.0*w[3]*gamma*K*n*r_y[qr]
            )/Pr/(rho*rho*rho)/Re;
          Fy[3] = -gamma/(rho*rho)*r_y[qr]*K/Re/Pr*w[3];

          Ssr[0]->u[qr] = Fx[0]*nx + Fy[0]*ny;
          Ssr[1]->u[qr] = Fx[1]*nx + Fy[1]*ny;
          Ssr[2]->u[qr] = Fx[2]*nx + Fy[2]*ny;
          Ssr[3]->u[qr] = Fx[3]*nx + Fy[3]*ny;
        }

        for (LocalSize q=0; q<qtot; q++) {         // loop over side quad-pts

#ifdef REO_USE_GETSIDEMAPS
          const LocalSize ql = mapl[q];
          const LocalSize qr = mapr[q];
#else
          const LocalSize ql = U->sideMap(Ssl[0], q);
          const LocalSize qr = U->sideMap(Ssr[0], q);
#endif

          switch (flux) {

          case LaxFriedrichs: //central flux

            // left flux
            for(vField::size_type j=0; j<Nfields;j++)
              fpl[j] = Ssl[j]->u[ql];

            for(vField::size_type j=0; j<Nfields; j++)
              fmr[j] = Ssr[j]->u[qr];

            // Central flux [gqchen]
            f[0] = 0.5 * ( fpl[0] + fmr[0]);
            f[1] = 0.5 * ( fpl[1] + fmr[1]);
            f[2] = 0.5 * ( fpl[2] + fmr[2]);
            f[3] = 0.5 * ( fpl[3] + fmr[3]);
            break;
          case vanLeer:       // Based on the Mach splitting
          case StegerWarming: // Based on the sound speed splitting
          case Roe:           // Roe average
          default:
            comm->cerr() << "Illegal value of flux type" << endl;
            exit(1);
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


//===========================================================================
// Bassi-Rebay  flux
//===========================================================================

// Us      Adjoint field
// Uf      Flux field
// Ur      LHS field
// Ustate  State field
// Ustate_x   State_x field
// Ustate_y   State_y field

void NS_Adjoint::diffusion( vField &Us, vField &Uf, vField &Ur ) {
  Element *S[4],*Sm[4],*Sm_x[4],*Sm_y[4],*F[4];
  Scalar rho,m,n,E;
  dVector wk,tmp;
  dVector lam1_x,lam1_y,lam2_x,lam2_y,lam3_x,lam3_y,lam4_x,lam4_y;
  dVector Fvx1,Fvx2,Fvx3,Fvx4,Fvy1,Fvy2,Fvy3,Fvy4;
  dVector r_x,r_y,ru_x,ru_y,rv_x,rv_y,E_x,E_y;

  Us.fill_sides();                   // put solution on the sides
  enforce_bc(Us);                    // update bc side values
  Us.share_sides();                  // communicate sides if parallel
  average_flux( Us, Uf, '+' );       // Uf's sides are average state

  for (LocalSize e=0; e<Us[0]->ne; e++) {

    S[0] = Us[0]->el[e];  // local version of the adjoint
    S[1] = Us[1]->el[e];
    S[2] = Us[2]->el[e];
    S[3] = Us[3]->el[e];

    Sm[0] = Ustate[0]->el[e];  // local version of the state
    Sm[1] = Ustate[1]->el[e];
    Sm[2] = Ustate[2]->el[e];
    Sm[3] = Ustate[3]->el[e];


    Sm_x[0] = Ustate_x[0]->el[e];  // local version of the state_x
    Sm_x[1] = Ustate_x[1]->el[e];
    Sm_x[2] = Ustate_x[2]->el[e];
    Sm_x[3] = Ustate_x[3]->el[e];

    Sm_y[0] = Ustate_y[0]->el[e];  // local version of the state_y
    Sm_y[1] = Ustate_y[1]->el[e];
    Sm_y[2] = Ustate_y[2]->el[e];
    Sm_y[3] = Ustate_y[3]->el[e];

    F[0] = Uf[0]->el[e];  // local version of the flux
    F[1] = Uf[1]->el[e];
    F[2] = Uf[2]->el[e];
    F[3] = Uf[3]->el[e];

    const Ordinal qtot = S[0]->qtot;

    Fvx1.alias(wk3,0,qtot);
    Fvx2.alias(wk3,qtot,qtot);
    Fvx3.alias(wk3,2*qtot,qtot);
    Fvx4.alias(wk3,3*qtot,qtot);
    Fvy1.alias(wk3,4*qtot,qtot);
    Fvy2.alias(wk3,5*qtot,qtot);
    Fvy3.alias(wk3,6*qtot,qtot);
    Fvy4.alias(wk3,7*qtot,qtot);

    lam1_x.alias(wk3,8*qtot,qtot);
    lam2_x.alias(wk3,9*qtot,qtot);
    lam3_x.alias(wk3,10*qtot,qtot);
    lam4_x.alias(wk3,11*qtot,qtot);
    lam1_y.alias(wk3,12*qtot,qtot);
    lam2_y.alias(wk3,13*qtot,qtot);
    lam3_y.alias(wk3,14*qtot,qtot);
    lam4_y.alias(wk3,15*qtot,qtot);

    wk.alias(wk3,16*qtot,qtot);
    tmp.alias(wk3,17*qtot,qtot);

    r_x.alias(Sm_x[0]->u);
    ru_x.alias(Sm_x[1]->u);
    rv_x.alias(Sm_x[2]->u);
    E_x.alias(Sm_x[3]->u);
    r_y.alias(Sm_y[0]->u);
    ru_y.alias(Sm_y[1]->u);
    rv_y.alias(Sm_y[2]->u);
    E_y.alias(Sm_y[3]->u);

    gradient( S[0], F[0], S[0]->u, lam1_x, lam1_y );
    gradient( S[1], F[1], S[1]->u, lam2_x, lam2_y );
    gradient( S[2], F[2], S[2]->u, lam3_x, lam3_y );
    gradient( S[3], F[3], S[3]->u, lam4_x, lam4_y );

    get_viscosity( wk ); // mu

    // get  Sum_j [transpose(K^j_i)Lambda_xj]
    for(LocalSize q=0; q<qtot; ++q){

      rho = Sm[0]->u[q];
      m   = Sm[1]->u[q];
      n   = Sm[2]->u[q];
      E   = Sm[3]->u[q];

      Fvx1[q] = -(2.0*mu+lambda)*m/(rho*rho)/Re*lam2_x[q]
        -n/(rho*rho)*mu/Re*lam3_x[q]
        +(-(2.0*mu+lambda)*m*m/(rho*rho*rho)/Re-n*n/(rho*rho*rho)*mu/Re
          +(gamma*(gamma-1.0)*(m*m+n*n)/(rho*rho*rho)/2.0
            -gamma*(gamma-1.0)
            *(E-(m*m+n*n)/rho/2.0)/(rho*rho))*K/Re/Pr/(gamma-1.0))
        *lam4_x[q]-n/(rho*rho)*mu/Re*lam2_y[q]-lambda/(rho*rho)/Re*m*lam3_y[q]
        +(-lambda*n/(rho*rho*rho)/Re*m-m/(rho*rho*rho)*mu/Re*n)*lam4_y[q];
      Fvx2[q] = (2.0*mu+lambda)/rho/Re*lam2_x[q]
        +((2.0*mu+lambda)*m/(rho*rho)/Re-gamma*m/(rho*rho)*K/Re/Pr)*lam4_x[q]
        +lambda/rho/Re*lam3_y[q]+lambda*n/(rho*rho)/Re*lam4_y[q];

      Fvx3[q] = 1/rho*mu/Re*lam3_x[q]
        +(n/(rho*rho)*mu/Re-gamma*n/(rho*rho)*K/Re/Pr)*lam4_x[q]
        +1/rho*mu/Re*lam2_y[q]+m/(rho*rho)*mu/Re*lam4_y[q];
      Fvx4[q] = gamma/rho*K/Re/Pr*lam4_x[q];
      Fvy1[q] = -lambda*n/(rho*rho)/Re*lam2_x[q]-m/(rho*rho)*mu/Re*lam3_x[q]
        +(-lambda*n/(rho*rho*rho)/Re*m-m/(rho*rho*rho)*mu/Re*n)*lam4_x[q]
        -m/(rho*rho)*mu/Re*lam2_y[q]-(2.0*mu+lambda)*n/(rho*rho)/Re*lam3_y[q]
        +(-m*m/(rho*rho*rho)*mu/Re-(2.0*mu+lambda)*n*n/(rho*rho*rho)/Re
          +(gamma*(gamma-1.0)*(m*m+n*n)/(rho*rho*rho)/2.0
            -gamma*(gamma-1.0)*(E-(m*m+n*n)/rho/2.0)/(rho*rho)
            )*K/Re/Pr/(gamma-1.0))*lam4_y[q];
      Fvy2[q] = 1/rho*mu/Re*lam3_x[q]+n/(rho*rho)*mu/Re*lam4_x[q]+1/rho*mu/Re
        *lam2_y[q]+(m/(rho*rho)*mu/Re-gamma*m/(rho*rho)*K/Re/Pr)*lam4_y[q];
      Fvy3[q] = lambda/rho/Re*lam2_x[q]+lambda/(rho*rho)/Re*m*lam4_x[q]+
        (2.0*mu+lambda)/rho/Re*lam3_y[q]
        +((2.0*mu+lambda)*n/(rho*rho)/Re-gamma*n/(rho*rho)*K/Re/Pr)*lam4_y[q];
      Fvy4[q] = gamma/rho*K/Re/Pr*lam4_y[q];

    }

    // 0
    S[0]->fill_sides( Fvx1, Fvy1 );
    S[0]->gradient(Fvx1, wk, 'x');  //
    S[0]->gradient(Fvy1, tmp, 'y'); //
    dvadd( tmp, wk, F[0]->u );      //

    // 1
    S[1]->fill_sides( Fvx2, Fvy2 );
    S[1]->gradient(Fvx2, wk, 'x');  //
    S[1]->gradient(Fvy2, tmp, 'y'); //
    dvadd( tmp, wk, F[1]->u );      //

    // 2
    S[2]->fill_sides( Fvx3, Fvy3 );
    S[2]->gradient(Fvx3, wk, 'x');  //
    S[2]->gradient(Fvy3, tmp, 'y'); //
    dvadd( tmp, wk, F[2]->u );      //

    // 3
    S[3]->fill_sides( Fvx4, Fvy4 );
    S[3]->gradient(Fvx4, wk, 'x');  //
    S[3]->gradient(Fvy4, tmp, 'y'); //
    dvadd( tmp, wk, F[3]->u );      //
  }

  Us.share_sides();                        // Share sides with your neighbors

  // put flux boundary on the state edge
  enforce_flux_bc(Us);
  // use the central flux for flux boundary
  average_flux( Us, Uf, '-' );

  for (vField::size_type k=0; k<Us.size(); k++) {
    for (LocalSize e=0; e<Us[k]->ne; e++) {
      Element *St = Us[k]->el[e];
      Element *Fl = Uf[k]->el[e];
      St->lift( Fl, Fl->u ); // add side fluxes to interior
    }
  }
  // add in viscous contribution
  for (vField::size_type k=0; k<Uf.size(); k++) add( Uf[k], Ur[k] );

}

///  Source term from the inviscid Jacobian
///  Calculate:  Sum[(tran(D_Fi/D_Q)_xi]*Lambda
void NS_Adjoint::conv_source(vField &Us,vField &Ur) {
  // Uv as Uf here
  Element *S[4], *F[4],*Sm[4];
  Scalar rho, m, n, E, w[4];
  Scalar Fx[4],Fy[4];
  dVector r_x, r_y, ru_x, ru_y, rv_x, rv_y, E_x, E_y;

  for (LocalSize e=0; e<Us[0]->ne; e++) {

    S[0] = Us[0]->el[e];  // local version of the state (adjoint)
    S[1] = Us[1]->el[e];
    S[2] = Us[2]->el[e];
    S[3] = Us[3]->el[e];

    Sm[0] = Ustate[0]->el[e];  // local version of the state (state)
    Sm[1] = Ustate[1]->el[e];
    Sm[2] = Ustate[2]->el[e];
    Sm[3] = Ustate[3]->el[e];

    F[0] = Uv[0]->el[e];  // local version of the RHS
    F[1] = Uv[1]->el[e];
    F[2] = Uv[2]->el[e];
    F[3] = Uv[3]->el[e];

    dVector r(Sm[0]->u);  //
    dVector ru(Sm[1]->u); //
    dVector rv(Sm[2]->u); //
    dVector En(Sm[3]->u); //

    const Ordinal qtot = S[0]->qtot;

    r_x.alias(Ustate_x[0]->el[e]->u);
    r_y.alias(Ustate_y[0]->el[e]->u);
    ru_x.alias(Ustate_x[1]->el[e]->u);
    ru_y.alias(Ustate_y[1]->el[e]->u);
    rv_x.alias(Ustate_x[2]->el[e]->u);
    rv_y.alias(Ustate_y[2]->el[e]->u);
    E_x.alias(Ustate_x[3]->el[e]->u);
    E_y.alias(Ustate_y[3]->el[e]->u);

    ///! VALIDATE [gqchen]

    for(LocalSize q=0; q<qtot; ++q){

      for(vField::size_type i=0; i<Nfields; ++i) w[i]=S[i]->u[q];
      rho = r[q];
      m = ru[q];
      n = rv[q];
      E = En[q];

      //Fx = Transpose(A1),x * Lamda

      Fx[0] = ((-6.0*ru_x[q]*m+2.0*gamma*ru_x[q]*m+2.0*gamma*rv_x[q]*n
                -2.0*rv_x[q]*n)/(rho*rho)/2.0-(-3.0*m*m+gamma*m*m+gamma*n*n
        -n*n)*r_x[q]/(rho*rho*rho))*w[1]+(-ru_x[q]*n/(rho*rho)
        -m*rv_x[q]/(rho*rho)+2.0*m*n*r_x[q]/(rho*rho*rho))*w[2]
        +(-ru_x[q]*(gamma*E*rho-gamma*m*m-gamma*n*n+m*m+n*n)
        /(rho*rho*rho)-m*(gamma*E_x[q]*rho+gamma*E*r_x[q]
        -2.0*gamma*ru_x[q]*m-2.0*gamma*rv_x[q]*n+2.0*ru_x[q]*m
              +2.0*rv_x[q]*n)/(rho*rho*rho)+3.0*m*(gamma*E*rho-gamma*m*m
              -gamma*n*n+m*m+n*n)*r_x[q]/(rho*rho *rho*rho))*w[3];
      Fx[1] = (-ru_x[q]*(-3.0+gamma)/rho+m*(-3.0+gamma)*r_x[q]/(rho*rho))
              *w[1]+(rv_x[q]/rho-n*r_x[q]/(rho*rho))*w[2]+((2.0*gamma*E_x[q]
              *rho+2.0*gamma*E*r_x[q] -6.0*gamma*ru_x[q]*m
              -2.0*gamma*rv_x[q]*n+6.0*ru_x[q]*m+2.0*rv_x[q]*n)/(rho*rho)/2.0
              -(2.0*gamma*E*rho-3.0*gamma*m*m-gamma*n*n+3.0*m*m+n*n)*r_x[q]
        /(rho*rho*rho))*w[3];
      Fx[2] = (-rv_x[q]*(gamma-1.0)/rho+n*(gamma-1.0)*r_x[q]/(rho*rho))*w[1]
       +(ru_x[q]/rho-m*r_x[q]/(rho*rho))*w[2]+(-ru_x[q]*n*(gamma-1.0)
             /(rho*rho)-m*rv_x[q]*(gamma-1.0)/(rho*rho)+2.0*m*n*(gamma-1.0)
             *r_x[q]/(rho*rho*rho))*w[3];
      Fx[3] = (ru_x[q]*gamma/rho-m*gamma*r_x[q]/(rho*rho))*w[3];

      //Fy = Transpose(A2),y * Lamda
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
              -3.0*w[3]*n*r_y[q]*m*m-3.0*w[3]*n*n*n*r_y[q])/(rho*rho*rho*rho);
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
  scale(-1.0,Uv);  // I currrently put everything on the LHS
  for(vField::size_type i=0; i<Uv.size(); i++) add( Uv[i], Ur[i] );
}


// Source term from the viscous Jacobian
// Calculate Sum[(tran(D_Gi/D_Q)_xi]*Lambda
void NS_Adjoint::viscous_conv_source(vField &Us,vField &Uf,vField &Ur) {
  Element *S[4], *F[4], *Sm[4], *Sm_x[4], *Sm_y[4];
  Scalar rho, m, n, E, w[4];
  Scalar Fx[4],Fy[4];
  Scalar s1,s2,s3,s4,s5,s6,s7,s8,s9,s10,s11,s12,s13,s14,s15,s16,s17;

  for (LocalSize e=0; e<Us[0]->ne; e++) {

    S[0] = Us[0]->el[e];  // local version of the adjoint
    S[1] = Us[1]->el[e];
    S[2] = Us[2]->el[e];
    S[3] = Us[3]->el[e];

    Sm[0] = Ustate[0]->el[e];  // local version of the state
    Sm[1] = Ustate[1]->el[e];
    Sm[2] = Ustate[2]->el[e];
    Sm[3] = Ustate[3]->el[e];

    Sm_x[0] = Ustate_x[0]->el[e];  // local version of the state_x
    Sm_x[1] = Ustate_x[1]->el[e];
    Sm_x[2] = Ustate_x[2]->el[e];
    Sm_x[3] = Ustate_x[3]->el[e];

    Sm_y[0] = Ustate_y[0]->el[e];  // local version of the state_y
    Sm_y[1] = Ustate_y[1]->el[e];
    Sm_y[2] = Ustate_y[2]->el[e];
    Sm_y[3] = Ustate_y[3]->el[e];

    F[0] = Uf[0]->el[e];  // local version of the flux
    F[1] = Uf[1]->el[e];
    F[2] = Uf[2]->el[e];
    F[3] = Uf[3]->el[e];

    dVector r(Sm[0]->u);  //
    dVector ru(Sm[1]->u); //
    dVector rv(Sm[2]->u); //
    dVector En(Sm[3]->u); //

    dVector r_x(Sm_x[0]->u);  //
    dVector ru_x(Sm_x[1]->u); //
    dVector rv_x(Sm_x[2]->u); //
    dVector E_x(Sm_x[3]->u); //

    dVector r_y(Sm_y[0]->u);  //
    dVector ru_y(Sm_y[1]->u); //
    dVector rv_y(Sm_y[2]->u); //
    dVector E_y(Sm_y[3]->u); //

    const Ordinal qtot = S[0]->qtot;

    dVector r_xx(qtot);
    dVector r_xy(qtot);
    dVector r_yy(qtot);

    dVector ru_xx(qtot);
    dVector ru_xy(qtot);
    dVector ru_yy(qtot);

    dVector rv_xx(qtot);
    dVector rv_xy(qtot);
    dVector rv_yy(qtot);

    dVector E_xx(qtot);
    dVector E_xy(qtot);
    dVector E_yy(qtot);

    dVector tmp1(qtot),tmp2(qtot),tmp3(qtot);

    Sm_x[0]->gradient(r_x, r_xx, r_xy);
    Sm_x[1]->gradient(ru_x, ru_xx, ru_xy);
    Sm_x[2]->gradient(rv_x, rv_xx, rv_xy);
    Sm_x[3]->gradient(E_x, E_xx, E_xy);

    Sm_y[0]->gradient(r_y, r_yy,'y');
    Sm_y[1]->gradient(ru_y, ru_yy,'y');
    Sm_y[2]->gradient(rv_y, rv_yy,'y');
    Sm_y[3]->gradient(E_y, E_yy,'y');

    for(LocalSize q=0; q<qtot; ++q) {

      for(vField::size_type i=0; i<Nfields; ++i) w[i]=S[i]->u[q];

      rho = r[q];
      m = ru[q];
      n = rv[q];
      E = En[q];

      // Fx = Transpose(D1),x * Lamda

      s1 = ((2.0*mu+lambda)*(-ru_xx[q]/(rho*rho)+4.0*ru_x[q]/(rho*rho*rho)
*r_x[q]-6.0*m/(rho*rho*rho*rho)*pow(r_x[q],2.0)+2.0*m/(rho*rho*rho)*
r_xx[q])+lambda*(-rv_xy[q]/(rho*rho)+2.0*rv_y[q]/(rho*rho*rho)*r_x[q]
+2.0*rv_x[q]/(rho*rho*rho)*r_y[q]-6.0*n/(rho*rho*rho*rho)*r_y[q]
*r_x[q]+2.0*n/(rho*rho*rho)*r_xy[q]))/Re*w[1];
      s3 = (-ru_xy[q]/(rho*rho)+2.0*ru_y[q]/(rho*rho*rho)*r_x[q]+2.0*
ru_x[q]/(rho*rho*rho)*r_y[q]-6.0*m/(rho*rho*rho*rho)*r_y[q]*r_x[q]
+2.0*m/(rho*rho*rho)*r_xy[q]-rv_xx[q]/(rho*rho)+4.0*rv_x[q]/(
rho*rho*rho)*r_x[q]-6.0*n/(rho*rho*rho*rho)*pow(r_x[q],2.0)+2.0*n/(
rho*rho*rho)*r_xx[q])*mu/Re*w[2];
      s7 = ((2.0*mu+lambda)*(-ru_xx[q]/(rho*rho)+4.0*ru_x[q]/(rho*rho*rho)
*r_x[q]-6.0*m/(rho*rho*rho*rho)*pow(r_x[q],2.0)+2.0*m/(rho*rho*rho)*
r_xx[q])+lambda*(-rv_xy[q]/(rho*rho)+2.0*rv_y[q]/(rho*rho*rho)*r_x[q]
+2.0*rv_x[q]/(rho*rho*rho)*r_y[q]-6.0*n/(rho*rho*rho*rho)*r_y[q]
*r_x[q]+2.0*n/(rho*rho*rho)*r_xy[q]))/Re*m/rho+((2.0*mu+lambda)*(
-ru_x[q]/(rho*rho)+2.0*m/(rho*rho*rho)*r_x[q])+lambda*(-rv_y[q]/(rho*
rho)+2.0*n/(rho*rho*rho)*r_y[q]))/Re*ru_x[q]/rho-((2.0*mu+lambda)*(-ru_x[q]
/(rho*rho)+2.0*m/(rho*rho*rho)*r_x[q])+lambda*(-rv_y[q]/(rho*rho)+
2.0*n/(rho*rho*rho)*r_y[q]))/Re*m/(rho*rho)*r_x[q];
      s6 = s7-((2.0*mu+lambda)*(ru_xx[q]/rho-2.0*ru_x[q]/(rho*rho)*r_x[q]
+2.0*m/(rho*rho*rho)*pow(r_x[q],2.0)-m/(rho*rho)*r_xx[q])+
lambda*(rv_xy[q]/rho-rv_y[q]/(rho*rho)*r_x[q]-rv_x[q]/(rho*rho)*
r_y[q]+2.0*n/(rho*rho*rho)*r_y[q]*r_x[q]-n/(rho*rho)*r_xy[q]
))/Re*m/(rho*rho)-((2.0*mu+lambda)*(ru_x[q]/rho-m/(rho*rho)*r_x[q])+
lambda*(rv_y[q]/rho-n/(rho*rho)*r_y[q]))/Re*ru_x[q]/(rho*rho)+2.0*((
2.0*mu+lambda)*(ru_x[q]/rho-m/(rho*rho)*r_x[q])+lambda*(rv_y[q]/rho-n/
(rho*rho)*r_y[q]))/Re*m/(rho*rho*rho)*r_x[q];
      s7 = s6+(-ru_xy[q]/(rho*rho)+2.0*ru_y[q]/(rho*rho*rho)*r_x[q]+
2.0*ru_x[q]/(rho*rho*rho)*r_y[q]-6.0*m/(rho*rho*rho*rho)*r_y[q]*
r_x[q]+2.0*m/(rho*rho*rho)*r_xy[q]-rv_xx[q]/(rho*rho)+4.0*rv_x[q]
/(rho*rho*rho)*r_x[q]-6.0*n/(rho*rho*rho*rho)*pow(r_x[q],2.0)+2.0*n
/(rho*rho*rho)*r_xx[q])*mu/Re*n/rho+(-ru_y[q]/(rho*rho)+2.0*m/(rho*rho*
rho)*r_y[q]-rv_x[q]/(rho*rho)+2.0*n/(rho*rho*rho)*r_x[q])*mu/Re*
rv_x[q]/rho-(-ru_y[q]/(rho*rho)+2.0*m/(rho*rho*rho)*r_y[q]-rv_x[q]/(
rho*rho)+2.0*n/(rho*rho*rho)*r_x[q])*mu/Re*n/(rho*rho)*r_x[q];
      s8 = s7-(ru_xy[q]/rho-ru_y[q]/(rho*rho)*r_x[q]-ru_x[q]/(rho*
rho)*r_y[q]+2.0*m/(rho*rho*rho)*r_y[q]*r_x[q]-m/(rho*rho)*r_xy[q]
+rv_xx[q]/rho-2.0*rv_x[q]/(rho*rho)*r_x[q]+2.0*n/(rho*rho*rho
)*pow(r_x[q],2.0)-n/(rho*rho)*r_xx[q])*mu/Re*n/(rho*rho);
      s9 = s8-(ru_y[q]/rho-m/(rho*rho)*r_y[q]+rv_x[q]/rho-n/(rho*rho)*
r_x[q])*mu/Re*rv_x[q]/(rho*rho);
      s10 = s9;
      s12 = 2.0*(ru_y[q]/rho-m/(rho*rho)*r_y[q]+rv_x[q]/rho-n/(rho*rho
)*r_x[q])*mu/Re*n/(rho*rho*rho)*r_x[q];
      s17 = gamma*(gamma-1.0)*((2.0*pow(ru_x[q],2.0)+2.0*m*ru_xx[q]
+2.0*pow(rv_x[q],2.0)+2.0*n*rv_xx[q])/(rho*rho)/2.0-2.0*(2.0*m*ru_x[q]+
2.0*n*rv_x[q])/(rho*rho*rho)*r_x[q]+3.0*(m*m+n*n)/(rho*rho*rho*rho)*pow(
r_x[q],2.0)-(m*m+n*n)/(rho*rho*rho)*r_xx[q])/rho-gamma*(
gamma-1.0)*((2.0*m*ru_x[q]+2.0*n*rv_x[q])/(rho*rho)/2.0-(m*m+n*n)/(rho*rho
*rho)*r_x[q])/(rho*rho)*r_x[q];
      s16 = s17-gamma*(gamma-1.0)*(E_xx[q]-(2.0*pow(ru_x[q],2.0)+
2.0*m*ru_xx[q]+2.0*pow(rv_x[q],2.0)+2.0*n*rv_xx[q])/rho/2.0+(2.0*m*ru_x[q]
+2.0*n*rv_x[q])/(rho*rho)*r_x[q]-(m*m+n*n)/(rho*rho*rho)*pow(r_x[q]
,2.0)+(m*m+n*n)/(rho*rho)*r_xx[q]/2.0)/(rho*rho)+4.0*gamma*(
gamma-1.0)*(E_x[q]-(2.0*m*ru_x[q]+2.0*n*rv_x[q])/rho/2.0+(m*m+n*n)/(rho
*rho)*r_x[q]/2.0)/(rho*rho*rho)*r_x[q];
      s15 = s16-gamma*(gamma-1.0)*(2.0*m*ru_x[q]+2.0*n*rv_x[q])/(
rho*rho*rho*rho)*r_x[q]/2.0+2.0*gamma*(gamma-1.0)*(m*m+n*n)/(rho*
rho*rho*rho*rho)*pow(r_x[q],2.0)-gamma*(gamma-1.0)*(m*m+n*n)/(rho*
rho*rho*rho)*r_xx[q]/2.0-6.0*gamma*(gamma-1.0)*(E-(m*m+n*n)/rho/
2.0)/(rho*rho*rho*rho)*pow(r_x[q],2.0)+2.0*gamma*(gamma-1.0)*(E-(m
*m+n*n)/rho/2.0)/(rho*rho*rho)*r_xx[q];
      s16 = K/Re;
      s14 = s15*s16;
      s15 = 1/Pr/(gamma-1.0);
      s13 = s14*s15;
      s11 = s12+s13;
      s5 = s10+s11;
      s6 = w[3];
      s4 = s5*s6;
      s2 = s3+s4;
      Fx[0] = s1+s2;
      s1 = (2.0*(2.0*mu+lambda)/(rho*rho*rho)*pow(r_x[q],2.0)/Re-(2.0*mu+
lambda)/(rho*rho)*r_xx[q]/Re)*w[1];
      s3 = (2.0/(rho*rho*rho)*r_y[q]*mu/Re*r_x[q]-1/(rho*rho)*r_xy[q]
*mu/Re)*w[2];
      s6 = 3.0*(2.0*mu+lambda)/(rho*rho*rho*rho)*pow(r_x[q],2.0)/Re*m-(2.0
*mu+lambda)/(rho*rho*rho)*r_xx[q]/Re*m-(2.0*mu+lambda)/(rho*rho*rho)*r_x[q]
/Re*ru_x[q]+((2.0*mu+lambda)*(ru_xx[q]/rho-2.0*ru_x[q]/(rho*rho)*
r_x[q]+2.0*m/(rho*rho*rho)*pow(r_x[q],2.0)-m/(rho*rho)*r_xx[q])
+lambda*(rv_xy[q]/rho-rv_y[q]/(rho*rho)*r_x[q]-rv_x[q]/(rho*rho)*
r_y[q]+2.0*n/(rho*rho*rho)*r_y[q]*r_x[q]-n/(rho*rho)*r_xy[q]
))/Re/rho;
      s5 = s6-((2.0*mu+lambda)*(ru_x[q]/rho-m/(rho*rho)*r_x[q])+lambda*(
rv_y[q]/rho-n/(rho*rho)*r_y[q]))/Re/(rho*rho)*r_x[q]+3.0/(rho*rho*
rho*rho)*r_y[q]*mu/Re*n*r_x[q]-1/(rho*rho*rho)*r_xy[q]*mu/Re*n-
1/(rho*rho*rho)*r_y[q]*mu/Re*rv_x[q]+(gamma*(gamma-1.0)*(-ru_xx[q]
/rho+2.0*ru_x[q]/(rho*rho)*r_x[q]-2.0*m/(rho*rho*rho)*pow(r_x[q]
,2.0)+m/(rho*rho)*r_xx[q])/rho-gamma*(gamma-1.0)*(-ru_x[q]/
rho+m/(rho*rho)*r_x[q])/(rho*rho)*r_x[q]+gamma*(gamma-1.0)*
ru_x[q]/(rho*rho*rho)*r_x[q]-3.0*gamma*(gamma-1.0)*m/(rho*rho*
rho*rho)*pow(r_x[q],2.0)+gamma*(gamma-1.0)*m/(rho*rho*rho)*r_xx[q]
)*K/Re/Pr/(gamma-1.0);
      s6 = w[3];
      s4 = s5*s6;
      s2 = s3+s4;
      Fx[1] = s1+s2;
      s1 = (2.0*lambda/(rho*rho*rho)*r_y[q]/Re*r_x[q]-lambda/(rho*rho
)*r_xy[q]/Re)*w[1];
      s3 = (2.0/(rho*rho*rho)*pow(r_x[q],2.0)*mu/Re-1/(rho*rho)*r_xx[q]
*mu/Re)*w[2];
      s6 = 3.0*lambda/(rho*rho*rho*rho)*r_y[q]/Re*m*r_x[q]-lambda/(
rho*rho*rho)*r_xy[q]/Re*m-lambda/(rho*rho*rho)*r_y[q]/Re*ru_x[q]+
3.0/(rho*rho*rho*rho)*pow(r_x[q],2.0)*mu/Re*n;
      s7 = s6-1/(rho*rho*rho)*r_xx[q]*mu/Re*n-1/(rho*rho*rho)*r_x[q]
*mu/Re*rv_x[q];
      s8 = s7+(ru_xy[q]/rho-ru_y[q]/(rho*rho)*r_x[q]-ru_x[q]/(rho*
rho)*r_y[q]+2.0*m/(rho*rho*rho)*r_y[q]*r_x[q]-m/(rho*rho)*r_xy[q]
+rv_xx[q]/rho-2.0*rv_x[q]/(rho*rho)*r_x[q]+2.0*n/(rho*rho*rho
)*pow(r_x[q],2.0)-n/(rho*rho)*r_xx[q])*mu/Re/rho;
      s5 = s8-(ru_y[q]/rho-m/(rho*rho)*r_y[q]+rv_x[q]/rho-n/(rho*rho)*
r_x[q])*mu/Re/(rho*rho)*r_x[q]+(gamma*(gamma-1.0)*(-rv_xx[q]
/rho+2.0*rv_x[q]/(rho*rho)*r_x[q]-2.0*n/(rho*rho*rho)*pow(r_x[q],
2.0)+n/(rho*rho)*r_xx[q])/rho-gamma*(gamma-1.0)*(-rv_x[q]/rho+n
/(rho*rho)*r_x[q])/(rho*rho)*r_x[q]+gamma*(gamma-1.0)*rv_x[q]
/(rho*rho*rho)*r_x[q]-3.0*gamma*(gamma-1.0)*n/(rho*rho*rho*rho)*
pow(r_x[q],2.0)+gamma*(gamma-1.0)*n/(rho*rho*rho)*r_xx[q])*K
/Re/Pr/(gamma-1.0);
      s6 = w[3];
      s4 = s5*s6;
      s2 = s3+s4;
      Fx[2] = s1+s2;
      Fx[3] = (2.0*gamma/(rho*rho*rho)*pow(r_x[q],2.0)*K/Re/Pr-gamma/
(rho*rho)*r_xx[q]*K/Re/Pr)*w[3];

      // Fy = Transpose(D2),y * Lamda
      s1 = (-ru_yy[q]/(rho*rho)+4.0*ru_y[q]/(rho*rho*rho)*r_y[q]-6.0*
m/(rho*rho*rho*rho)*pow(r_y[q],2.0)+2.0*m/(rho*rho*rho)*r_yy[q]-rv_xy[q]
/(rho*rho)+2.0*rv_x[q]/(rho*rho*rho)*r_y[q]+2.0*rv_y[q]/(rho*
rho*rho)*r_x[q]-6.0*n/(rho*rho*rho*rho)*r_y[q]*r_x[q]+2.0*n/(rho
*rho*rho)*r_xy[q])*mu/Re*w[1];
      s3 = ((2.0*mu+lambda)*(-rv_yy[q]/(rho*rho)+4.0*rv_y[q]/(rho*rho*rho)
*r_y[q]-6.0*n/(rho*rho*rho*rho)*pow(r_y[q],2.0)+2.0*n/(rho*rho*rho)*
r_yy[q])+lambda*(-ru_xy[q]/(rho*rho)+2.0*ru_x[q]/(rho*rho*rho)*r_y[q]
+2.0*ru_y[q]/(rho*rho*rho)*r_x[q]-6.0*m/(rho*rho*rho*rho)*r_y[q]
*r_x[q]+2.0*m/(rho*rho*rho)*r_xy[q]))/Re*w[2];
      s7 = (-ru_yy[q]/(rho*rho)+4.0*ru_y[q]/(rho*rho*rho)*r_y[q]-6.0*
m/(rho*rho*rho*rho)*pow(r_y[q],2.0)+2.0*m/(rho*rho*rho)*r_yy[q]-rv_xy[q]
/(rho*rho)+2.0*rv_x[q]/(rho*rho*rho)*r_y[q]+2.0*rv_y[q]/(rho*
rho*rho)*r_x[q]-6.0*n/(rho*rho*rho*rho)*r_y[q]*r_x[q]+2.0*n/(rho
*rho*rho)*r_xy[q])*mu/Re*m/rho+(-ru_y[q]/(rho*rho)+2.0*m/(rho*rho*rho)*
r_y[q]-rv_x[q]/(rho*rho)+2.0*n/(rho*rho*rho)*r_x[q])*mu/Re*ru_y[q]
/rho-(-ru_y[q]/(rho*rho)+2.0*m/(rho*rho*rho)*r_y[q]-rv_x[q]/(rho*rho)
+2.0*n/(rho*rho*rho)*r_x[q])*mu/Re*m/(rho*rho)*r_y[q];
      s6 = s7-(ru_yy[q]/rho-2.0*ru_y[q]/(rho*rho)*r_y[q]+2.0*m/(rho*
rho*rho)*pow(r_y[q],2.0)-m/(rho*rho)*r_yy[q]+rv_xy[q]/rho-rv_x[q]
/(rho*rho)*r_y[q]-rv_y[q]/(rho*rho)*r_x[q]+2.0*n/(rho*rho*rho)*
r_y[q]*r_x[q]-n/(rho*rho)*r_xy[q])*mu/Re*m/(rho*rho)-(ru_y[q]
/rho-m/(rho*rho)*r_y[q]+rv_x[q]/rho-n/(rho*rho)*r_x[q])*mu/Re*ru_y[q]
/(rho*rho)+2.0*(ru_y[q]/rho-m/(rho*rho)*r_y[q]+rv_x[q]/rho-n/(rho*
rho)*r_x[q])*mu/Re*m/(rho*rho*rho)*r_y[q];
      s7 = s6+((2.0*mu+lambda)*(-rv_yy[q]/(rho*rho)+4.0*rv_y[q]/(rho*rho*
rho)*r_y[q]-6.0*n/(rho*rho*rho*rho)*pow(r_y[q],2.0)+2.0*n/(rho*rho*
rho)*r_yy[q])+lambda*(-ru_xy[q]/(rho*rho)+2.0*ru_x[q]/(rho*rho*rho)*
r_y[q]+2.0*ru_y[q]/(rho*rho*rho)*r_x[q]-6.0*m/(rho*rho*rho*rho)*
r_y[q]*r_x[q]+2.0*m/(rho*rho*rho)*r_xy[q]))/Re*n/rho+((2.0*mu+
lambda)*(-rv_y[q]/(rho*rho)+2.0*n/(rho*rho*rho)*r_y[q])+lambda*(-ru_x[q]
/(rho*rho)+2.0*m/(rho*rho*rho)*r_x[q]))/Re*rv_y[q]/rho-((2.0*mu+lambda
)*(-rv_y[q]/(rho*rho)+2.0*n/(rho*rho*rho)*r_y[q])+lambda*(-ru_x[q]/(
rho*rho)+2.0*m/(rho*rho*rho)*r_x[q]))/Re*n/(rho*rho)*r_y[q];
      s8 = s7-((2.0*mu+lambda)*(rv_yy[q]/rho-2.0*rv_y[q]/(rho*rho)*r_y[q]
+2.0*n/(rho*rho*rho)*pow(r_y[q],2.0)-n/(rho*rho)*r_yy[q])+
lambda*(ru_xy[q]/rho-ru_x[q]/(rho*rho)*r_y[q]-ru_y[q]/(rho*rho)*
r_x[q]+2.0*m/(rho*rho*rho)*r_y[q]*r_x[q]-m/(rho*rho)*r_xy[q]
))/Re*n/(rho*rho);
      s9 = s8-((2.0*mu+lambda)*(rv_y[q]/rho-n/(rho*rho)*r_y[q])+lambda*(
ru_x[q]/rho-m/(rho*rho)*r_x[q]))/Re*rv_y[q]/(rho*rho);
      s10 = s9;
      s12 = 2.0*((2.0*mu+lambda)*(rv_y[q]/rho-n/(rho*rho)*r_y[q])+lambda
*(ru_x[q]/rho-m/(rho*rho)*r_x[q]))/Re*n/(rho*rho*rho)*r_y[q];
      s17 = gamma*(gamma-1.0)*((2.0*pow(ru_y[q],2.0)+2.0*m*ru_yy[q]
+2.0*pow(rv_y[q],2.0)+2.0*n*rv_yy[q])/(rho*rho)/2.0-2.0*(2.0*m*ru_y[q]+
2.0*n*rv_y[q])/(rho*rho*rho)*r_y[q]+3.0*(m*m+n*n)/(rho*rho*rho*rho)*pow(
r_y[q],2.0)-(m*m+n*n)/(rho*rho*rho)*r_yy[q])/rho-gamma*(
gamma-1.0)*((2.0*m*ru_y[q]+2.0*n*rv_y[q])/(rho*rho)/2.0-(m*m+n*n)/(rho*rho
*rho)*r_y[q])/(rho*rho)*r_y[q];
      s16 = s17-gamma*(gamma-1.0)*(E_yy[q]-(2.0*pow(ru_y[q],2.0)+
2.0*m*ru_yy[q]+2.0*pow(rv_y[q],2.0)+2.0*n*rv_yy[q])/rho/2.0+(2.0*m*ru_y[q]
+2.0*n*rv_y[q])/(rho*rho)*r_y[q]-(m*m+n*n)/(rho*rho*rho)*pow(r_y[q]
,2.0)+(m*m+n*n)/(rho*rho)*r_yy[q]/2.0)/(rho*rho)+4.0*gamma*(
gamma-1.0)*(E_y[q]-(2.0*m*ru_y[q]+2.0*n*rv_y[q])/rho/2.0+(m*m+n*n)/(rho
*rho)*r_y[q]/2.0)/(rho*rho*rho)*r_y[q];
      s15 = s16-gamma*(gamma-1.0)*(2.0*m*ru_y[q]+2.0*n*rv_y[q])/(
rho*rho*rho*rho)*r_y[q]/2.0+2.0*gamma*(gamma-1.0)*(m*m+n*n)/(rho*
rho*rho*rho*rho)*pow(r_y[q],2.0)-gamma*(gamma-1.0)*(m*m+n*n)/(rho*
rho*rho*rho)*r_yy[q]/2.0-6.0*gamma*(gamma-1.0)*(E-(m*m+n*n)/rho/
2.0)/(rho*rho*rho*rho)*pow(r_y[q],2.0)+2.0*gamma*(gamma-1.0)*(E-(m
*m+n*n)/rho/2.0)/(rho*rho*rho)*r_yy[q];
      s16 = K/Re;
      s14 = s15*s16;
      s15 = 1/Pr/(gamma-1.0);
      s13 = s14*s15;
      s11 = s12+s13;
      s5 = s10+s11;
      s6 = w[3];
      s4 = s5*s6;
      s2 = s3+s4;
      Fy[0] = s1+s2;
      s1 = (2.0/(rho*rho*rho)*pow(r_y[q],2.0)*mu/Re-1/(rho*rho)*r_yy[q]
*mu/Re)*w[1];
      s3 = (2.0*lambda/(rho*rho*rho)*r_y[q]/Re*r_x[q]-lambda/(rho*rho
)*r_xy[q]/Re)*w[2];
      s6 = 3.0/(rho*rho*rho*rho)*pow(r_y[q],2.0)*mu/Re*m-1/(rho*rho*rho)*
r_yy[q]*mu/Re*m-1/(rho*rho*rho)*r_y[q]*mu/Re*ru_y[q]+(ru_yy[q]/
rho-2.0*ru_y[q]/(rho*rho)*r_y[q]+2.0*m/(rho*rho*rho)*pow(r_y[q],2.0
)-m/(rho*rho)*r_yy[q]+rv_xy[q]/rho-rv_x[q]/(rho*rho)*r_y[q]-
rv_y[q]/(rho*rho)*r_x[q]+2.0*n/(rho*rho*rho)*r_y[q]*r_x[q]-n/(
rho*rho)*r_xy[q])*mu/Re/rho;
      s5 = s6-(ru_y[q]/rho-m/(rho*rho)*r_y[q]+rv_x[q]/rho-n/(rho*rho)*
r_x[q])*mu/Re/(rho*rho)*r_y[q]+3.0*lambda/(rho*rho*rho*rho)*r_x[q]
/Re*n*r_y[q]-lambda/(rho*rho*rho)*r_xy[q]/Re*n-lambda/(rho*rho*rho
)*r_x[q]/Re*rv_y[q]+(gamma*(gamma-1.0)*(-ru_yy[q]/rho+2.0*
ru_y[q]/(rho*rho)*r_y[q]-2.0*m/(rho*rho*rho)*pow(r_y[q],2.0)+m/(rho
*rho)*r_yy[q])/rho-gamma*(gamma-1.0)*(-ru_y[q]/rho+m/(rho*rho)*
r_y[q])/(rho*rho)*r_y[q]+gamma*(gamma-1.0)*ru_y[q]/(rho*rho
*rho)*r_y[q]-3.0*gamma*(gamma-1.0)*m/(rho*rho*rho*rho)*pow(r_y[q]
,2.0)+gamma*(gamma-1.0)*m/(rho*rho*rho)*r_yy[q])*K/Re/Pr/(gamma-1.0);
      s6 = w[3];
      s4 = s5*s6;
      s2 = s3+s4;
      Fy[1] = s1+s2;
      s1 = (2.0/(rho*rho*rho)*r_y[q]*mu/Re*r_x[q]-1/(rho*rho)*r_xy[q]
*mu/Re)*w[1];
      s3 = (2.0*(2.0*mu+lambda)/(rho*rho*rho)*pow(r_y[q],2.0)/Re-(2.0*mu+
lambda)/(rho*rho)*r_yy[q]/Re)*w[2];
      s6 = 3.0/(rho*rho*rho*rho)*r_x[q]*mu/Re*m*r_y[q]-1/(rho*rho*rho
)*r_xy[q]*mu/Re*m-1/(rho*rho*rho)*r_x[q]*mu/Re*ru_y[q]+3.0*(2.0*mu
+lambda)/(rho*rho*rho*rho)*pow(r_y[q],2.0)/Re*n;
      s7 = s6-(2.0*mu+lambda)/(rho*rho*rho)*r_yy[q]/Re*n-(2.0*mu+lambda)/
(rho*rho*rho)*r_y[q]/Re*rv_y[q];
      s8 = s7+((2.0*mu+lambda)*(rv_yy[q]/rho-2.0*rv_y[q]/(rho*rho)*r_y[q]
+2.0*n/(rho*rho*rho)*pow(r_y[q],2.0)-n/(rho*rho)*r_yy[q])+
lambda*(ru_xy[q]/rho-ru_x[q]/(rho*rho)*r_y[q]-ru_y[q]/(rho*rho)*
r_x[q]+2.0*m/(rho*rho*rho)*r_y[q]*r_x[q]-m/(rho*rho)*r_xy[q]
))/Re/rho;
      s5 = s8-((2.0*mu+lambda)*(rv_y[q]/rho-n/(rho*rho)*r_y[q])+lambda*(
ru_x[q]/rho-m/(rho*rho)*r_x[q]))/Re/(rho*rho)*r_y[q]+(gamma*
(gamma-1.0)*(-rv_yy[q]/rho+2.0*rv_y[q]/(rho*rho)*r_y[q]-2.0*n/(rho*
rho*rho)*pow(r_y[q],2.0)+n/(rho*rho)*r_yy[q])/rho-gamma*(
gamma-1.0)*(-rv_y[q]/rho+n/(rho*rho)*r_y[q])/(rho*rho)*r_y[q]+
gamma*(gamma-1.0)*rv_y[q]/(rho*rho*rho)*r_y[q]-3.0*gamma*
(gamma-1.0)*n/(rho*rho*rho*rho)*pow(r_y[q],2.0)+gamma*(gamma-1.0)
*n/(rho*rho*rho)*r_yy[q])*K/Re/Pr/(gamma-1.0);
      s6 = w[3];
      s4 = s5*s6;
      s2 = s3+s4;
      Fy[2] = s1+s2;
      Fy[3] = (2.0*gamma/(rho*rho*rho)*pow(r_y[q],2.0)*K/Re/Pr-gamma/
(rho*rho)*r_yy[q]*K/Re/Pr)*w[3];

      F[0]->u[q] = Fx[0]+Fy[0];
      F[1]->u[q] = Fx[1]+Fy[1];
      F[2]->u[q] = Fx[2]+Fy[2];
      F[3]->u[q] = Fx[3]+Fy[3];
    }
  }
  for(vField::size_type i=0; i<Uf.size(); i++) add( Uf[i], Ur[i] );
}


/** Ua = Adjoint Field
    Us = State   Field **/
void NS_Adjoint::computeGrad(vField& Ua, vField& Us,
                             Ordinal istep, Ordinal sstep) {
  // Don't you need to load the side and interior information like in Burgers
  control->gradient( Us, Ua, g_control, istep, sstep );
}

void NS_Adjoint::enforce_state_derivate_bc(vField &S) {
  dVector us[4];
  dVector ub[4];
  for (LocalSize n=0; n<S[0]->nbc; n++) {
    const LocalSize sid = S[0]->bc[n]->sid;
    const LocalSize qtot = S[0]->bc[n]->elmt->side[sid]->qtot();
    //dVector &nx = S[0]->bc[n]->elmt->side[sid]->nx();
    //dVector &ny = S[0]->bc[n]->elmt->side[sid]->ny();
    switch (S[0]->bc[n]->type[0]) {
    case 'W':
      for (vField::size_type i=0; i<Nfields; i++) {
        us[i].alias( S[i]->bc[n]->elmt->side[sid]->u );
        ub[i].alias( S[i]->bc[n]->elmt->side[sid]->link->u );
      }
      for (LocalSize i=0; i<qtot; i++) {
        ub[0][i] =  us[0][i];
        ub[1][i] =  us[1][i];
        ub[2][i] =  us[2][i];
        ub[3][i] =  us[3][i];
      }
      break;
    default:
      for (vField::size_type i=0; i<Nfields; i++) {
        us[i].alias( S[i]->bc[n]->elmt->side[sid]->u );
        ub[i].alias( S[i]->bc[n]->elmt->side[sid]->link->u );
      }
      for (LocalSize i=0; i<qtot; i++) {
        ub[0][i] = us[0][i];
        ub[1][i] = us[1][i];
        ub[2][i] = us[2][i];
        ub[3][i] = us[3][i];
      }
      break;
    }
  }
}

//===========================================================================
//                        BC database management
//===========================================================================

// Load up the available BC types
void NS_Adjoint::setup_BCdb( ) {
  BC_db = state->BC_db;  // Navier_Stokes::BC_db
  // Domain::BC_db = state->Domain::BC_db;
}

void NS_Adjoint::enforce_bc(vField &Ua) {
  for (BC::db_citr i=BC_db.begin(); i!= BC_db.end(); ++i)
    i->second->adjoint_apply( t, Ustate, Ua );
}

void NS_Adjoint::enforce_flux_bc(vField &Ua) {
  // cout << "NS_Adjoint::enforce_flux_bc(vField &F) "<< lstep << endl;
  for (BC::db_citr i=BC_db.begin(); i!= BC_db.end(); ++i)
    i->second->adjoint_apply_flux( t, Ustate, Ua );
}

//===========================================================================
//                        Source database management
//===========================================================================

/// Load up the available Source types
void NS_Adjoint::setup_Sourcedb( ) {
  // cout << "NS_Adjoint::setup_Sourcedb" << endl;
  Source_db = state->Source_db;  // use the State sources
  string fname = root+".obj";    // add sources due to objective function
  ifstream in(fname.c_str());
  if (in) read_Sourcedb( in );   // database of active Source types
}

/// make the Adjoint Source terms
Source::Ptr NS_Adjoint::make_Source( ifstream &in, string &tag ) {
  // cout << "NS_Adjoint::make_Source" << endl;
  string code;
  Source::Ptr p;
  if (!(in >> code)) return p;
  while (code[0]=='#') {  // eat comment lines
    string buffer;
    getline(in,buffer);
    if (!(in >> code)) return p;
  }
  if (lowerCase(code) == "flowtracking") {
    if (!(in >> tag)) error("NS_Adjoint::Cannot read FlowTracking tag",1);
    p.reset( new FlowTracking(tag,in,U,state) );
  } else if (lowerCase(code) == "momentumtracking") {
    if (!(in >> tag))
      error("NS_Adjoint::Cannot read MomentumTracking tag",1);;
    p.reset( new FlowTracking(tag,in,U,state,FlowTracking::Momentum) );
  } else if (lowerCase(code) == "pressuretracking") {
    if (!(in >> tag))
      error("NS_Adjoint::Cannot read PressureTracking tag",1);;
    p.reset( new FlowTracking(tag,in,U,state,FlowTracking::Pressure) );
  } else if (lowerCase(code) == "terminalkineticenergy") {
    if (!(in >> tag))
      error("NS_Adjoint::Cannot read TerminalKE tag",1);;
    p.reset( new TerminalKineticEnergy(tag,in,U,state,npredict) );
  } else if (lowerCase(code) == "shearstressreduction") {
    if (!(in >> tag))
      error("NS_Adjoint::Cannot read ShearStressReduction tag",1);
    p.reset( new ShearStressReduction(tag,in,U,state) );
  } else {
    cout<<code<<endl;
    error("NS_Adjoint::make_Source() Illegal Source type",1);
  }
  return p;
}

/// Add Source terms
void NS_Adjoint::add_source(const vField &Us, vField &Ur) {
  // cout << "NS_Adjoint::add_source(vField &)" << endl;
  for (Source::db_citr i=Source_db.begin(); i!= Source_db.end(); ++i) {
    // cout << "Adding source: " << i->first << endl;
    i->second->adjoint_apply(t, Ustate, Us, Ur );
  }
}

/// Compute a jump savy gradient
void NS_Adjoint::gradient( Element *S, Element *F, dVector &u,
                           dVector &ux, dVector &uy ) {
  dVector uxh(ux,S->nModes());
  dVector uyh(uy,S->nModes());
  S->gradient( u, ux, uy );
  S->lift( F, ux, 'x' );
#ifdef REO_PROJECT_DIFF_FLUX
  S->project(ux);                           // lifted ux
#endif
  S->lift( F, uy, 'y' );
#ifdef REO_PROJECT_DIFF_FLUX
  S->project(uy);                           // lifted uy
#endif
}

void NS_Adjoint::get_viscosity( dVector &mu ) {
  // cout << "Navier_Stokes::get_viscosity( dVector &mu )" << endl;
  mu = vis;
}

void NS_Adjoint::set_ic(vField &F, string ext) {
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
