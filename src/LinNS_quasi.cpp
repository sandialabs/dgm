/*=============================================================================
  Module:     LinNS Quasi-conservative Module

  Contacts:   S. Scott Collis & Guoquan Chen

  Copyright:  (c)2003 Rice University
              (c)2013 Sandia National Laboratories
=============================================================================*/

/** \file  LinNS_quasi.cpp
    \brief Linearized Navier-Stokes equations in quasi-conservative variables
    \author Guoquan Chen
    \author Scott Collis

    Linearized solver based on the conservative form with primitive
    variables (currently assumes the mean flow is steady)
    \f[U = D(Q)/D(U_m) [\rho u v T] \f]
    where \f$Ma\f$ is the reference Mach number. */

// DGM includes
#include "TimeInt.hpp"
#include "Wavetype.hpp"
#include "String.hpp"

// Reo includes
#include "LinNS_quasi.hpp"
#include "Navier_Stokes.hpp"

namespace Reo {

// constructor
LinNS_quasi::LinNS_quasi( DGM::ArgList &args, const DGM::Comm::Ptr comm_ ) :
  Navier_Stokes(args, comm_), Up(comm_), Um(comm_), Um_x(comm_), Um_y(comm_) 
{
  header(comm->cout(),
         "WARNING:  LinNS_quasi is experimental and needs verification\n"
         "          Use at your own risk...");

  Ma = 0.3;             // Reference Ma number  (Why is this needed??) [SSC]
  Re = 1.0;             // To be consistent with the nondimensional state
  mu = vis;             // dynamic viscosity
  lambda = -2.0/3.0*mu; // Stokes hypothesis

  // Pr using that from parent class Navier_Stokes

  // Conductivity coefficient K is defined to be consistent with the state and
  // adjoint formulations
  K = mu;

  // Print a warning since these values are hardwired
  comm->cout()<<"[LinNS_quasi] WARNING:  \n  Using Ma="<<Ma<<", Re="<<Re
              <<", mu="<<mu<<", lambda="<<lambda<<", Pr="<<Pr
              <<", K="<<K<<std::endl;

  // make auxiliary Fields using copy constructor
  for (vField::size_type i=0; i<Nfields; i++) {
    // make the mean flow Field
    Um.push_back( new Field( U[0], root, U[i]->name) );
    Um_x.push_back( new Field( U[0], root, U[i]->name) );
    Um_y.push_back( new Field( U[0], root, U[i]->name) );
    // make the solution field.  This field may be unnecessary -- cgq
    Up.push_back( new Field( U[0], root, U[i]->name) );
  }

  // make sure that storage is initialized
  zero_all_fields();

  // allocate workspace -- increase the workspace [gqchen]
  wk3.resize(20*max(Lmax(),Qmax()));
  wk4.resize(20*max(Lmax(),Qmax()));
}

void LinNS_quasi::zero_all_fields() {
  Domain::zero_all_fields();
  Um.zero();
  Up.zero();
  Um_x.zero();
  Um_y.zero();
}

/*! Override the version from the parent Class, since LinNS needs special
    operations by introducing Up and Um */
int LinNS_quasi::solve() {
  Format sci(4); sci.scientific().width(12);

  if (DGM::Comm::World->Master()) cout << "Title = " << title << endl;

  set_mean(Um);    // set the mean flow field
  set_ic(Up);      // set the initial condition (primitive field)
  make_U(U,Um,Up); // make the initial condition (solution variables)

#ifndef DGM_PARALLEL
  U.tecplot("ic.dat","Initial Condition");
#endif

  // estimate the stability condition
  // if (DGM::Comm::World->Master())
  //   cout << "CFL = " << compute_cfl( U ) << endl;

  if (DGM::Comm::World->Master()) cout << "Advancing solution " << Nt
                                       << " time steps" << endl;

  Scalar ctime=0, stime=0, ttime=0;
  int cnt=0;
  Stopwatch cpu; cpu.start();
  for (lstep=1; lstep<=Nt; lstep++) {
    step++;
    time_int->advance(this);
    ctime = cpu.restart();
    if (lstep>1) { ttime += ctime; stime += ctime*ctime; cnt++; }
#if 0
    if (DGM::Comm::World->Master()) cout << setw(5) << step <<  sci(t)
                                         << sci(ctime) << endl;
#else
    if (DGM::Comm::World->Master())
      printf("%5lld %12.4e %12.4e\n",(long long)step,t,ctime);
#endif
    if (step%Ntout==0) {
      get_Up(Up,Um,U);
      write(step, Up);
      Up.norm();
      cpu.restart();
    }
  }
#ifdef DGM_PARALLEL
  Scalar atime=0, otime=0;
  DGM::Comm::World->SumAll( &ttime, &atime, 1 );  // average cpu time
  DGM::Comm::World->SumAll( &stime, &otime, 1 );  // standard deviation
  int n = max(1,cnt*DGM::Comm::World->NumProc());
  if (DGM::Comm::World->Master()) {
    cout << "Average time per step: " << sci(atime/n)
         << ", standard deviation:  "
         << sci( ::sqrt((n*otime-atime*atime)/(n*max(int(n-1),1))) ) << endl;
  }
#endif

  if (step%Ntout!=0) write(step, U);
#ifndef DGM_PARALLEL
  get_Up(Up,Um,U);
  Up.tecplot("out.dat","Final solution");
#endif
  U.write_side_stats();
  response->output( U[0] );
  return 0;
}

void LinNS_quasi::time_derivative( vField &Us, vField &Uf ) {
  convection( Us, Uf );
  viscous_convection( Us, Uv, Uf );
  diffusion(Us,Uv,Uf);
  project( Uf );
}

void LinNS_quasi::convection( vField &Us, vField &Uf ) {
  Element *U[4], *F[4], *Fm[4];
  dVector u1, u2, u3, Fx1, Fx2, Fx3, Fx4, Fy1, Fy2, Fy3, Fy4, d;

  Scalar w[4], rho, m, n, E;

  Us.fill_sides();

  // fill side for the mean flow field
  Um.fill_sides();
  Um.share_sides();
  enforce_mean_state_bc(Um);

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

    // local version of the mean flow
    Fm[0] = Um[0]->el[e];
    Fm[1] = Um[1]->el[e];
    Fm[2] = Um[2]->el[e];
    Fm[3] = Um[3]->el[e];

    const LocalSize qtot = Us[0]->el[e]->qtot;

    Fx1.alias(wk3,0,qtot);
    Fx2.alias(wk3,qtot,qtot);
    Fx3.alias(wk3,2*qtot,qtot);
    Fx4.alias(wk3,3*qtot,qtot);
    Fy1.alias(wk3,4*qtot,qtot);
    Fy2.alias(wk3,5*qtot,qtot);
    Fy3.alias(wk3,6*qtot,qtot);
    Fy4.alias(wk3,7*qtot,qtot);
    d.alias(wk3,8*qtot,qtot);

    // Set    F(u(x)),x = (A(\overline \bU) \bu'),x
    //        G(u(x)),y = (B(\overline \bU) \bu'),y

    for (LocalSize q=0; q<qtot; q++) {
      for(vField::size_type i=0; i<Nfields; i++) w[i]=U[i]->u[q];
      rho = Fm[0]->u[q];
      m= Fm[1]->u[q];
      n= Fm[2]->u[q];
      E= Fm[3]->u[q];

      // code produced by Maple
      Fx1[q] = w[1];
      Fx2[q] = (-3.0*w[0]*m*m+w[0]*gamma*m*m+w[0]*gamma*n*n-w[0]*n*n
                +6.0*m*w[1]*rho-2.0*m*w[1]*rho*gamma-2.0*n*w[2]*rho*gamma
                +2.0*n*w[2]*rho+2.0*w[3]*rho*rho*gamma-2.0*w[3]*rho*rho
        )/(rho*rho)/2.0;
      Fx3[q] = (-m*n*w[0]+n*w[1]*rho+m*w[2]*rho)/(rho*rho);
      Fx4[q] = (-2.0*m*w[0]*gamma*E*rho+2.0*m*m*m*w[0]*gamma
                +2.0*m*w[0]*gamma*n*n-2.0*m*m*m*w[0]-2.0*m*w[0]*n*n
                +2.0*w[1]*rho*rho*gamma*E-3.0*w[1]*rho*gamma*m*m
                -w[1]*rho*gamma*n*n+3.0*w[1]*rho*m*m+w[1]*rho*n*n
                -2.0*m*n*w[2]*rho*gamma+2.0*m*n*w[2]*rho
                +2.0*m*gamma*w[3]*rho*rho)/(rho*rho*rho)/2.0;

      Fy1[q] = w[2];
      Fy2[q] = (-m*n*w[0]+n*w[1]*rho+m*w[2]*rho)/(rho*rho);
      Fy3[q] = (-3.0*w[0]*n*n+w[0]*gamma*m*m+w[0]*gamma*n*n-w[0]*m*m
                -2.0*m*w[1]*rho*gamma+2.0*m*w[1]*rho+6.0*n*w[2]*rho
                -2.0*n*w[2]*rho*gamma+2.0*w[3]*rho*rho*gamma
                -2.0*w[3]*rho*rho)/(rho*rho)/2.0;
      Fy4[q] = (-2.0*n*w[0]*gamma*E*rho+2.0*n*w[0]*gamma*m*m
                +2.0*n*n*n*w[0]*gamma-2.0*n*w[0]*m*m-2.0*n*n*n*w[0]
                -2.0*m*n*w[1]*rho*gamma+2.0*m*n*w[1]*rho
                +2.0*w[2]*rho*rho*gamma*E-w[2]*rho*gamma*m*m
                -3.0*w[2]*rho*gamma*n*n+w[2]*rho*m*m+3.0*w[2]*rho*n*n
                +2.0*n*gamma*w[3]*rho*rho)/(rho*rho*rho)/2.0;
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
          Dynamics," 2nd Edition, Springer, 1999. */
void LinNS_quasi::convective_flux(vField &Us, vField &Uf) {
  flux_type flux = LaxFriedrichs; //StegerWarming; //vanLeer;
  dVector sl(Nfields), sr(Nfields), f(Nfields), U(Nfields), Ua(Nfields);
  dVector slm(Nfields), srm(Nfields);
  Scalar ulm, clm; // ul, rl, ml, nl, El, vl, pl, Hl, Ml,
  Scalar urm, crm; // ur, mr, nr, Er, vr, pr, Hr, Mr,
  // Scalar r1, u1, v1,c1,R,p,H,c2,ci,b1,b2
  vector<Side *> Ssl(Nfields), Ssr(Nfields);
  vector<Side *> Sbl(Nfields), Sbr(Nfields); //mean flow field side --cgq
  vector<Side *> Sfl(Nfields), Sfr(Nfields);
  dVector fpl(Nfields), fmr(Nfields),lam(Nfields);
  Scalar lmax;
  Scalar w[4], rho, m, n, E;
  dVector Fx(Nfields),Fy(Nfields);
#ifdef REO_USE_GETSIDEMAPS
  iVector mapl, mapr;
  setup_side_maps();
#endif
  for (LocalSize e=0; e<Us[0]->ne; e++) {                 // loop over elements
    Element* U = Us[0]->el[e];
    for (LocalSize i=0; i<Us[0]->el[e]->nSides(); i++) {  // loop over sides
      if (Us[0]->el[e]->side[i]->master()) {              // compute if master
        const LocalSize qtot = Us[0]->el[e]->side[i]->qtot();  // side quad pts
        for (vField::size_type ni=0; ni<Nfields; ni++) {
          Ssl[ni] = Us[ni]->el[e]->side[i];        // local state side
          Ssr[ni] = Us[ni]->el[e]->side[i]->link;  // adjacent state side
          Sfl[ni] = Uf[ni]->el[e]->side[i];        // local flux side
          Sfr[ni] = Uf[ni]->el[e]->side[i]->link;  // adjacent flux side
          Sbl[ni] = Um[ni]->el[e]->side[i];       // local mean side
          Sbr[ni] = Um[ni]->el[e]->side[i]->link; // adjacent mean side
        }
#ifdef REO_USE_GETSIDEMAPS
        get_side_maps(Ssl[0],Ssr[0],mapl,mapr);
#endif
        for (LocalSize q=0; q<qtot; q++) {           // loop over side quad-pts

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

          // From solution U (quasi-conservative)
          for(vField::size_type k=0;k<Nfields;k++) sl[k] = Ssl[k]->u[ql];

          // normal velocity -- mean flow

          ulm = (Sbl[1]->u[ql]*nx +Sbl[2]->u[ql]*ny)/Sbl[0]->u[ql];

          // sanity check
//        if(Ssl[0]->u[ql] < 0) {
//          cerr<<"Element "<<e<<", Side: "<<i<<", Density(l): "
//              <<Ssl[0]->u[ql]<<endl;
//          DGM::Comm::World->exit(DGM::FAILURE);
//        }
//        if(Ssl[3]->u[ql] < 0 ) {
//          cerr<<"Element "<<e<<", Side: "<<i<<", Temperature(l): "
//              <<Ssl[3]->u[ql]<<endl;
//          DGM::Comm::World->exit(DGM::FAILURE);
//        }

          for(vField::size_type k=0;k<Nfields;k++) w[k]=Ssl[k]->u[ql];

          rho = Sbl[0]->u[ql];
          m= Sbl[1]->u[ql];
          n= Sbl[2]->u[ql];
          E= Sbl[3]->u[ql];
          clm = sqrt((E-0.5*(m*m+n*n)/rho)/rho*gamma*(gamma-1.0));

          Fx[0] = w[1];
          Fx[1] = (-3.0*w[0]*m*m+w[0]*gamma*m*m+w[0]*gamma*n*n-w[0]*n*n
                   +6.0*m*w[1]*rho-2.0*m*w[1]*rho*gamma-2.0*n*w[2]*rho*gamma
                   +2.0*n*w[2]*rho+2.0*w[3]*rho*rho*gamma-2.0*w[3]*rho*rho
            )/(rho*rho)/2.0;
          Fx[2] = (-m*n*w[0]+n*w[1]*rho+m*w[2]*rho)/(rho*rho);
          Fx[3] = (-2.0*m*w[0]*gamma*E*rho+2.0*m*m*m*w[0]*gamma
                   +2.0*m*w[0]*gamma*n*n-2.0*m*m*m*w[0]-2.0*m*w[0]*n*n
                   +2.0*w[1]*rho*rho*gamma*E-3.0*w[1]*rho*gamma*m*m
                   -w[1]*rho*gamma*n*n+3.0*w[1]*rho*m*m+w[1]*rho*n*n
                   -2.0*m*n*w[2]*rho*gamma+2.0*m*n*w[2]*rho
                   +2.0*m*gamma*w[3]*rho*rho)/(rho*rho*rho)/2.0;

          Fy[0] = w[2];
          Fy[1] = (-m*n*w[0]+n*w[1]*rho+m*w[2]*rho)/(rho*rho);
          Fy[2] = (-3.0*w[0]*n*n+w[0]*gamma*m*m+w[0]*gamma*n*n-w[0]*m*m
                   -2.0*m*w[1]*rho*gamma+2.0*m*w[1]*rho+6.0*n*w[2]*rho
                   -2.0*n*w[2]*rho*gamma+2.0*w[3]*rho*rho*gamma
                   -2.0*w[3]*rho*rho)/(rho*rho)/2.0;
          Fy[3] = (-2.0*n*w[0]*gamma*E*rho+2.0*n*w[0]*gamma*m*m
                   +2.0*n*n*n*w[0]*gamma-2.0*n*w[0]*m*m-2.0*n*n*n*w[0]
                   -2.0*m*n*w[1]*rho*gamma+2.0*m*n*w[1]*rho
                   +2.0*w[2]*rho*rho*gamma*E-w[2]*rho*gamma*m*m
                   -3.0*w[2]*rho*gamma*n*n+w[2]*rho*m*m+3.0*w[2]*rho*n*n
                   +2.0*n*gamma*w[3]*rho*rho)/(rho*rho*rho)/2.0;

          Ssl[0]->u[ql] = Fx[0]*nx + Fy[0]*ny;
          Ssl[1]->u[ql] = Fx[1]*nx + Fy[1]*ny;
          Ssl[2]->u[ql] = Fx[2]*nx + Fy[2]*ny;
          Ssl[3]->u[ql] = Fx[3]*nx + Fy[3]*ny;

          // compute normal flux from exterior (right)

          // adjacent state (quasi-conservative form)
          for(vField::size_type k=0;k<Nfields;k++) sr[k] = Ssr[k]->u[qr];

          urm = (Sbr[1]->u[qr]*nx +Sbr[2]->u[qr]*ny)/Sbr[0]->u[qr];
          //ur = Ssr[1]->u[qr]*nx +Ssr[2]->u[qr]*ny;

          // sanity check
//        if(Ssr[0]->u[qr] < 0) {
//          cerr<<"Element "<<e<<", Side: "<<i<<", Density(l): "
//              <<Ssr[0]->u[qr]<<endl;
//          DGM::Comm::World->exit(DGM::FAILURE);
//        }

//        if(Ssr[3]->u[qr] < 0 ) {
//          cerr<<"Element "<<e<<", Side: "<<i<<", Temperature(l): "
//              <<Ssr[3]->u[qr]<<endl;
//          DGM::Comm::World->exit(DGM::FAILURE);
//        }

          // put the adjacent flux on the state sides
          for(Ordinal k=0;k<Nfields;k++) w[k]=Ssr[k]->u[qr];
          rho = Sbr[0]->u[qr];
          m= Sbr[1]->u[qr];
          n= Sbr[2]->u[qr];
          E= Sbr[3]->u[qr];
          crm = sqrt((E-0.5*(m*m+n*n)/rho)/rho*gamma*(gamma-1.0));

          // code produced by Maple
          Fx[0] = w[1];
          Fx[1] = (-3.0*w[0]*m*m+w[0]*gamma*m*m+w[0]*gamma*n*n-w[0]*n*n
                   +6.0*m*w[1]*rho-2.0*m*w[1]*rho*gamma-2.0*n*w[2]*rho*gamma
                   +2.0*n*w[2]*rho+2.0*w[3]*rho*rho*gamma-2.0*w[3]*rho*rho
            )/(rho*rho)/2.0;
          Fx[2] = (-m*n*w[0]+n*w[1]*rho+m*w[2]*rho)/(rho*rho);
          Fx[3] = (-2.0*m*w[0]*gamma*E*rho+2.0*m*m*m*w[0]*gamma
                   +2.0*m*w[0]*gamma*n*n-2.0*m*m*m*w[0]-2.0*m*w[0]*n*n
                   +2.0*w[1]*rho*rho*gamma*E-3.0*w[1]*rho*gamma*m*m
                   -w[1]*rho*gamma*n*n+3.0*w[1]*rho*m*m+w[1]*rho*n*n
                   -2.0*m*n*w[2]*rho*gamma+2.0*m*n*w[2]*rho
                   +2.0*m*gamma*w[3]*rho*rho)/(rho*rho*rho)/2.0;

          Fy[0] = w[2];
          Fy[1] = (-m*n*w[0]+n*w[1]*rho+m*w[2]*rho)/(rho*rho);
          Fy[2] = (-3.0*w[0]*n*n+w[0]*gamma*m*m+w[0]*gamma*n*n-w[0]*m*m
                   -2.0*m*w[1]*rho*gamma+2.0*m*w[1]*rho+6.0*n*w[2]*rho
                   -2.0*n*w[2]*rho*gamma+2.0*w[3]*rho*rho*gamma
                   -2.0*w[3]*rho*rho)/(rho*rho)/2.0;
          Fy[3] = (-2.0*n*w[0]*gamma*E*rho+2.0*n*w[0]*gamma*m*m
                   +2.0*n*n*n*w[0]*gamma-2.0*n*w[0]*m*m-2.0*n*n*n*w[0]
                   -2.0*m*n*w[1]*rho*gamma+2.0*m*n*w[1]*rho
                   +2.0*w[2]*rho*rho*gamma*E-w[2]*rho*gamma*m*m
                   -3.0*w[2]*rho*gamma*n*n+w[2]*rho*m*m+3.0*w[2]*rho*n*n
                   +2.0*n*gamma*w[3]*rho*rho)/(rho*rho*rho)/2.0;

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
            for(vField::size_type j=0; j<Nfields;j++) {
              lmax = max(lmax,fabs(lam[j]));
              fpl[j] = Ssl[j]->u[ql];
            }
            lam[0] = urm;
            lam[1] = urm+crm;
            lam[2] = urm-crm;
            lam[3] = urm;
            for(vField::size_type j=0; j<Nfields; j++) {
              lmax = max(lmax,fabs(lam[j]));
              fmr[j] = Ssr[j]->u[qr];
            }
            // Lax-Friedrichs flux
            f[0] = pt5 * ( fpl[0] + fmr[0] + lmax * ( sl[0] - sr[0] ) );
            f[1] = pt5 * ( fpl[1] + fmr[1] + lmax * ( sl[1] - sr[1] ) );
            f[2] = pt5 * ( fpl[2] + fmr[2] + lmax * ( sl[2] - sr[2] ) );
            f[3] = pt5 * ( fpl[3] + fmr[3] + lmax * ( sl[3] - sr[3] ) );
#ifdef DGM_VERBOSE_FLUX
            cout << "Lax-Friedrichs: Element " << e << ", Side " << i << endl;
            cout << f[0] << ", "
                 << f[1] << ", "
                 << f[2] << ","
                 << f[3] << endl;
#endif
            break;
          case vanLeer:       // Based on the Mach splitting
          case StegerWarming: // Based on the sound speed splitting
          case Roe:           // Roe average
          default:
            cerr << "Illegal value of flux type" << endl;
            DGM::Comm::World->exit(DGM::FAILURE);
          }
          // put fluxes on flux field sides
          for (vField::size_type ni=0; ni<Nfields; ni++) {
            Ssr[ni]->u[qr] *= -one;         // correct for normal
            Sfl[ni]->u[ql]  =  f[ni];       // upwind flux
            Sfr[ni]->u[qr]  = -f[ni];       // correct for normal
          }
        }
      }
    }
  }
}

// Calculate:
void LinNS_quasi::viscous_convection( vField &Us, vField &Uf, vField &Ur) {
  Element *U[4], *F[4],*Sm[4];
  dVector Fx1,Fx2,Fx3,Fx4,Fy1,Fy2,Fy3,Fy4,d;
  Scalar w[4],rho,m,n,E;
  dVector r_x,r_y,ru_x,ru_y,rv_x,rv_y,E_x,E_y;
  Scalar s1,s2,s3,s4;

  Um.fill_sides();

  // compute the gradient of the mean solution
  //   Um_x = the D_Um_x
  //   Um_y = the D_Um_y
  for (LocalSize e=0; e<Us[0]->ne; e++) {
    // local version of the state solution
    Sm[0] = Um[0]->el[e];
    Sm[1] = Um[1]->el[e];
    Sm[2] = Um[2]->el[e];
    Sm[3] = Um[3]->el[e];

    Sm[0]->gradient(Um[0]->el[e]->u,Um_x[0]->el[e]->u,
                    Um_y[0]->el[e]->u);
    Sm[1]->gradient(Um[1]->el[e]->u,Um_x[1]->el[e]->u,
                    Um_y[1]->el[e]->u);
    Sm[2]->gradient(Um[2]->el[e]->u,Um_x[2]->el[e]->u,
                    Um_y[2]->el[e]->u);
    Sm[3]->gradient(Um[3]->el[e]->u,Um_x[3]->el[e]->u,
                    Um_y[3]->el[e]->u);
  }

  enforce_mean_state_bc(Um);

  Um_x.fill_sides();
  Um_y.fill_sides();

  // Enforce the boundary state derivate [gqchen]
  enforce_mean_derivate_bc(Um_x);
  enforce_mean_derivate_bc(Um_y);

  Um.share_sides();
  Um_x.share_sides();
  Um_y.share_sides();

  Us.fill_sides();
  enforce_bc(Us);
  Us.share_sides();

  // Do the average flux operator  --central flux  [gqchen]

  // central flux
  viscous_convective_flux( Us, Uf );

  for (LocalSize e=0; e<Us[0]->ne; e++) {

    // local version of the quasi variable
    U[0] = Us[0]->el[e];
    U[1] = Us[1]->el[e];
    U[2] = Us[2]->el[e];
    U[3] = Us[3]->el[e];

    // local version of the  flux
    F[0] = Uf[0]->el[e];
    F[1] = Uf[1]->el[e];
    F[2] = Uf[2]->el[e];
    F[3] = Uf[3]->el[e];

    // local version of the mean
    Sm[0] = Um[0]->el[e];
    Sm[1] = Um[1]->el[e];
    Sm[2] = Um[2]->el[e];
    Sm[3] = Um[3]->el[e];

    dVector r(Sm[0]->u);
    dVector ru(Sm[1]->u);
    dVector rv(Sm[2]->u);
    dVector En(Sm[3]->u);

    const LocalSize qtot = Us[0]->el[e]->qtot;

    r_x.alias(Um_x[0]->el[e]->u);
    r_y.alias(Um_y[0]->el[e]->u);
    ru_x.alias(Um_x[1]->el[e]->u);
    ru_y.alias(Um_y[1]->el[e]->u);
    rv_x.alias(Um_x[2]->el[e]->u);
    rv_y.alias(Um_y[2]->el[e]->u);
    E_x.alias(Um_x[3]->el[e]->u);
    E_y.alias(Um_y[3]->el[e]->u);

    Fx1.alias(wk3,0,qtot);
    Fx2.alias(wk3,qtot,qtot);
    Fx3.alias(wk3,2*qtot,qtot);
    Fx4.alias(wk3,3*qtot,qtot);
    Fy1.alias(wk3,4*qtot,qtot);
    Fy2.alias(wk3,5*qtot,qtot);
    Fy3.alias(wk3,6*qtot,qtot);
    Fy4.alias(wk3,7*qtot,qtot);
    d.alias(wk3,8*qtot,qtot);

    // nD^1(u(x)),x =
    // nD^2(u(x)),y =

    for (LocalSize q=0; q<qtot; q++) {

      for(vField::size_type i=0; i<Nfields; i++) w[i]=U[i]->u[q];
      rho = Sm[0]->u[q];
      m   = Sm[1]->u[q];
      n   = Sm[2]->u[q];
      E   = Sm[3]->u[q];

      Fx1[q] = 0.0;
      Fx2[q] = -2.0*(2.0*w[0]*mu*ru_x[q]*rho-4.0*w[0]*mu*m*r_x[q]
                     +w[0]*lambda*ru_x[q]*rho-2.0*w[0]*lambda*m*r_x[q]
                     +w[0]*lambda*rv_y[q]*rho-2.0*w[0]*lambda*n*r_y[q]
                     +2.0*r_x[q]*w[1]*rho*mu+r_x[q]*w[1]*rho*lambda
                     +lambda*r_y[q]*w[2]*rho)/(rho*rho*rho)/Re;
      Fx3[q] = -2.0*mu*(w[0]*ru_y[q]*rho-2.0*w[0]*m*r_y[q]+w[0]*rv_x[q] *rho
                        -2.0*w[0]*n*r_x[q]+r_y[q]*w[1]*rho+r_x[q]*w[2]*rho)
        /(rho*rho*rho)/Re;
      s3 = -3.0*w[0]*m*Pr*lambda*rv_y[q]*rho+5.0*w[0]*m*Pr*lambda*n*r_y[q]
        -3.0*w[0]*gamma*K*r_x[q]*n*n-w[2]*rho*r_y[q]*mu*m*Pr
        +w[2]*rho*rho*mu*Pr*ru_y[q]+w[2]*rho*rho*mu*Pr*rv_x[q]
        -3.0*w[2]*rho*mu*Pr*n*r_x[q]-w[2]*rho*rho*gamma*K*rv_x[q]
        -gamma*r_x[q]*w[3]*rho*rho*K+2.0*w[2]*rho*K*gamma*n*r_x[q]
        -gamma*r_x[q]*w[3]*rho*rho*K;
      s2 = s3-w[2]*rho*rho*K*gamma*rv_x[q]+2.0*w[2]*rho*gamma*K*n*r_x[q]
        -3.0*w[0]*mu*n*Pr*rv_x[q]*rho+5.0*w[0]*mu*n*Pr*m*r_y[q]
        -3.0*w[0]*mu*n*Pr*ru_y[q]*rho+5.0*w[0]*mu*n*n*Pr*r_x[q]
        +5.0*w[0]*m*m*Pr*lambda*r_x[q]-3.0*w[0]*K*gamma*r_x[q]*m*m
        -3.0*w[0]*gamma*K*r_x[q]*m*m-w[0]*gamma*K*E_x[q]*rho*rho
        -3.0*w[1]*rho*r_x[q]*m*Pr*lambda;
      s3 = s2-6.0*w[1]*rho*r_x[q]*m*Pr*mu-w[0]*K*gamma*E_x[q]*rho*rho
        -3.0*w[0]*K*gamma*r_x[q]*n*n-w[1]*rho*Pr*lambda*n*r_y[q]
        +w[1]*rho*rho*Pr*lambda*rv_y[q]+w[1]*rho*rho*Pr*lambda*ru_x[q]
        +2.0*w[1]*rho*rho*Pr*mu*ru_x[q]-w[1]*rho*rho*K*gamma*ru_x[q]
        +2.0*w[1]*rho*gamma*K*m*r_x[q]-w[1]*rho*rho*gamma*K*ru_x[q];
      s1 = s3-2.0*w[1]*rho*r_y[q]*mu*n*Pr-2.0*w[2]*rho*lambda*r_y[q]*m*Pr
        +2.0*w[1]*rho*K*gamma*m*r_x[q]+2.0*w[0]*gamma*K*rho*m*ru_x[q]
        +10.0*w[0]*m*m*Pr*mu*r_x[q]+2.0*w[0]*gamma*K*rho*n*rv_x[q]
        +2.0*w[0]*gamma*K*r_x[q]*E*rho+2.0*w[0]*K*gamma*rho*m*ru_x[q]
        +2.0*w[0]*K*gamma*rho*n*rv_x[q]+2.0*w[0]*K*gamma*r_x[q]*E*rho
        -6.0*w[0]*m*Pr*mu*ru_x[q]*rho-3.0*w[0]*m*Pr*lambda*ru_x[q]*rho;
      s2 = 1/Pr/(rho*rho*rho*rho)/Re;
      Fx4[q] = s1*s2;

      Fy1[q] = 0.0;
      Fy2[q] = -2.0*mu*(w[0]*ru_y[q]*rho-2.0*w[0]*m*r_y[q]+w[0]*rv_x[q] *rho
                        -2.0*w[0]*n*r_x[q]+r_y[q]*w[1]*rho+r_x[q]*w[2]*rho)
        /(rho*rho*rho)/Re;
      Fy3[q] = -2.0*(2.0*w[0]*mu*rv_y[q]*rho-4.0*w[0]*mu*n*r_y[q]
                     +w[0]*lambda*rv_y[q]*rho-2.0*w[0]*lambda*n*r_y[q]
                     +w[0]*lambda*ru_x[q]*rho-2.0*w[0]*lambda*m*r_x[q]
                     +r_x[q]*w[1]*rho*lambda+2.0*r_y[q]*w[2]*rho*mu
                     +lambda*r_y[q]*w[2]*rho)/(rho*rho*rho)/Re;
      s4 = -gamma*r_y[q]*w[3]*rho*rho*K-6.0*w[0]*n*Pr*mu*rv_y[q] *rho
        +5.0*w[0]*mu*m*Pr*n*r_x[q]-3.0*w[0]*gamma*K*r_y[q]*m*m
        +5.0*w[0]*n*n*Pr*lambda*r_y[q]-3.0*w[0]*n*Pr*lambda*rv_y[q]*rho
        +2.0*w[2]*rho*rho*Pr*mu*rv_y[q]-w[0]*gamma*K*E_y[q]*rho*rho
        -3.0*w[0]*gamma*K*r_y[q] *n*n+2.0*w[0]*K*gamma*rho*n*rv_y[q]
        +2.0*w[0]*K*gamma*rho*m*ru_y[q];
      s3 = s4+10.0*w[0]*n*n*Pr*mu*r_y[q]+5.0*w[0]*mu*m*m*Pr*r_y[q]
        +2.0*w[0]*gamma*K*rho*n*rv_y[q]+2.0*w[0]*gamma*K*rho*m*ru_y[q]
        -w[0]*K*gamma*E_y[q]*rho*rho+5.0*w[0]*n*Pr*lambda*m*r_x[q]
        +2.0*w[0]*K*gamma*r_y[q]*E*rho-3.0*w[0]*n*Pr*lambda*ru_x[q]*rho
        -3.0*w[0]*K*gamma*r_y[q]*n*n+2.0*w[0]*gamma*K*r_y[q]*E*rho
        -3.0*w[0]*K*gamma*r_y[q]*m*m;
      s4 = s3-3.0*w[0]*mu*m*Pr*rv_x[q]*rho-3.0*w[0]*mu*m*Pr*ru_y[q]*rho
        -2.0*w[2]*rho*r_x[q]*m*Pr*mu-w[2]*rho*r_x[q]*m*Pr*lambda+w[2]
        *rho*rho*Pr*lambda*ru_x[q]+w[2]*rho*rho*Pr*lambda*rv_y[q]
        -3.0*w[2]*rho*Pr*lambda*n*r_y[q]-6.0*w[2]*rho*r_y[q]*mu*n*Pr
        +w[1]*rho*rho*mu*Pr*rv_x[q]+w[1]*rho*rho*mu*Pr*ru_y[q];
      s2 = s4-3.0*w[1]*rho*r_y[q]*mu*m*Pr-w[2]*rho*rho*gamma*K*rv_y[q]
        -2.0*w[1]*rho*lambda*r_x[q]*n*Pr-w[1]*rho*mu*Pr*n*r_x[q]
        -w[1]*rho*rho*gamma*K*ru_y[q]-w[1]*rho*rho*K*gamma*ru_y[q]
        +2.0*w[1]*rho*gamma*K*m*r_y[q]+2.0*w[1]*rho*K*gamma*m*r_y[q]
        +2.0*w[2]*rho*gamma*K*n*r_y[q]-w[2]*rho*rho*K*gamma*rv_y[q]
        +2.0*w[2]*rho*K*gamma*n*r_y[q]-gamma*r_y[q]*w[3]*rho*rho*K;
      s3 = 1/Pr;
      s1 = s2*s3;
      s2 = 1/(rho*rho*rho*rho)/Re;
      Fy4[q] = s1*s2;
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
  scale(-one,Uf);  // I currently put everything on the LHS
  for (vField::size_type k=0; k<Uf.size(); k++) add( Uf[k], Ur[k] );
}

// It is not helpful, since we are only using the central flux, the cheaper
// should be only to define the central operator at the boundary edge [gqchen]
void LinNS_quasi::viscous_convective_flux(vField &Us, vField &Uf) {
  flux_type flux = LaxFriedrichs; //StegerWarming; //vanLeer;
  dVector sl(Nfields), sr(Nfields), f(Nfields);
  dVector slm(Nfields), srm(Nfields);
  vector<Side *> Ssl(Nfields), Ssr(Nfields);
  vector<Side *> Sbl(Nfields), Sbr(Nfields);
  vector<Side *> Sfl(Nfields), Sfr(Nfields);
  dVector fpl(Nfields), fmr(Nfields), lam(Nfields);
  Scalar rho, m, n, E;
  dVector w(Nfields);
  dVector Fx(Nfields),Fy(Nfields);
  Scalar s1, s2, s3, s4;
  vector<Side *> Sbl_x(Nfields), Sbr_x(Nfields);
  vector<Side *> Sbl_y(Nfields), Sbr_y(Nfields);
#ifdef REO_USE_GETSIDEMAPS
  iVector mapl, mapr;
  setup_side_maps();
#endif
  // VALIDATE [gqchen]
  for (LocalSize e=0; e<Us[0]->ne; e++) {                 // loop over elements
    Element* U = Us[0]->el[e];
    for (LocalSize i=0; i<Us[0]->el[e]->nSides(); i++) {  // loop over sides
      if (Us[0]->el[e]->side[i]->master()) {              // if master side
        const LocalSize qtot = Us[0]->el[e]->side[i]->qtot(); // side quad pts
        for (vField::size_type ni=0; ni<Nfields; ni++) {
          Ssl[ni] = Us[ni]->el[e]->side[i];        // left state side
          Ssr[ni] = Us[ni]->el[e]->side[i]->link;  // right state side
          Sfl[ni] = Uf[ni]->el[e]->side[i];        // left flux side
          Sfr[ni] = Uf[ni]->el[e]->side[i]->link;  // right flux side
          Sbl[ni] = Um[ni]->el[e]->side[i];        // left base side
          Sbr[ni] = Um[ni]->el[e]->side[i]->link;  // right base side
          Sbl_x[ni] = Um_x[ni]->el[e]->side[i];
          Sbr_x[ni] = Um_x[ni]->el[e]->side[i]->link;
          Sbl_y[ni] = Um_y[ni]->el[e]->side[i];
          Sbr_y[ni] = Um_y[ni]->el[e]->side[i]->link;
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

        for (LocalSize q=0; q<qtot; q++) {         // loop over side quad-pts

#ifdef REO_USE_GETSIDEMAPS
          const LocalSize ql = mapl[q];
#else
          const LocalSize ql = U->sideMap(Ssl[0], q);
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

          // code produced by Maple

          Fx[0] = 0.0;
          Fx[1] = -2.0*(2.0*w[0]*mu*ru_x[q]*rho-4.0*w[0]*mu*m*r_x[q]
                        +w[0]*lambda*ru_x[q]*rho-2.0*w[0]*lambda*m*r_x[q]
                        +w[0]*lambda*rv_y[q]*rho-2.0*w[0]*lambda*n*r_y[q]
                        +2.0*r_x[q]*w[1]*rho*mu+r_x[q]*w[1]*rho*lambda
                        +lambda*r_y[q]*w[2]*rho)/(rho*rho*rho)/Re;
          Fx[2] = -2.0*mu*(w[0]*ru_y[q]*rho-2.0*w[0]*m*r_y[q]+w[0]*rv_x[q] *rho
                           -2.0*w[0]*n*r_x[q]+r_y[q]*w[1]*rho+r_x[q]*w[2]*rho)
            /(rho*rho*rho)/Re;
          s3 = -3.0*w[0]*m*Pr*lambda*rv_y[q]*rho+5.0*w[0]*m*Pr*lambda*n*r_y[q]
            -3.0*w[0]*gamma*K*r_x[q]*n*n-w[2]*rho*r_y[q]*mu*m*Pr
            +w[2]*rho*rho*mu*Pr*ru_y[q]+w[2]*rho*rho*mu*Pr*rv_x[q]
            -3.0*w[2]*rho*mu*Pr*n*r_x[q]-w[2]*rho*rho*gamma*K*rv_x[q]
            -gamma*r_x[q]*w[3]*rho*rho*K+2.0*w[2]*rho*K*gamma*n*r_x[q]
            -gamma*r_x[q]*w[3]*rho*rho*K;
          s2 = s3-w[2]*rho*rho*K*gamma*rv_x[q]+2.0*w[2]*rho*gamma*K*n*r_x[q]
            -3.0*w[0]*mu*n*Pr*rv_x[q]*rho+5.0*w[0]*mu*n*Pr*m*r_y[q]
            -3.0*w[0]*mu*n*Pr*ru_y[q]*rho+5.0*w[0]*mu*n*n*Pr*r_x[q]
            +5.0*w[0]*m*m*Pr*lambda*r_x[q]-3.0*w[0]*K*gamma*r_x[q]*m*m
            -3.0*w[0]*gamma*K*r_x[q]*m*m-w[0]*gamma*K*E_x[q]*rho*rho
            -3.0*w[1]*rho*r_x[q]*m*Pr*lambda;
          s3 = s2-6.0*w[1]*rho*r_x[q]*m*Pr*mu-w[0]*K*gamma*E_x[q]*rho*rho
            -3.0*w[0]*K*gamma*r_x[q]*n*n-w[1]*rho*Pr*lambda*n*r_y[q]
            +w[1]*rho*rho*Pr*lambda*rv_y[q]+w[1]*rho*rho*Pr*lambda*ru_x[q]
            +2.0*w[1]*rho*rho*Pr*mu*ru_x[q]-w[1]*rho*rho*K*gamma*ru_x[q]
            +2.0*w[1]*rho*gamma*K*m*r_x[q]-w[1]*rho*rho*gamma*K*ru_x[q];
          s1 = s3-2.0*w[1]*rho*r_y[q]*mu*n*Pr-2.0*w[2]*rho*lambda*r_y[q]*m*Pr
            +2.0*w[1]*rho*K*gamma*m*r_x[q]+2.0*w[0]*gamma*K*rho*m*ru_x[q]
            +10.0*w[0]*m*m*Pr*mu*r_x[q]+2.0*w[0]*gamma*K*rho*n*rv_x[q]
            +2.0*w[0]*gamma*K*r_x[q]*E*rho+2.0*w[0]*K*gamma*rho*m*ru_x[q]
            +2.0*w[0]*K*gamma*rho*n*rv_x[q]+2.0*w[0]*K*gamma*r_x[q]*E*rho
            -6.0*w[0]*m*Pr*mu*ru_x[q]*rho-3.0*w[0]*m*Pr*lambda*ru_x[q]*rho;
          s2 = 1/Pr/(rho*rho*rho*rho)/Re;
          Fx[3] = s1*s2;

          Fy[0] = 0.0;
          Fy[1] = -2.0*mu*(w[0]*ru_y[q]*rho-2.0*w[0]*m*r_y[q]+w[0]*rv_x[q] *rho
                           -2.0*w[0]*n*r_x[q]+r_y[q]*w[1]*rho+r_x[q]*w[2]*rho)
            /(rho*rho*rho)/Re;
          Fy[2] = -2.0*(2.0*w[0]*mu*rv_y[q]*rho-4.0*w[0]*mu*n*r_y[q]
                        +w[0]*lambda*rv_y[q]*rho-2.0*w[0]*lambda*n*r_y[q]
                        +w[0]*lambda*ru_x[q]*rho-2.0*w[0]*lambda*m*r_x[q]
                        +r_x[q]*w[1]*rho*lambda+2.0*r_y[q]*w[2]*rho*mu
                        +lambda*r_y[q]*w[2]*rho)/(rho*rho*rho)/Re;
          s4 = -gamma*r_y[q]*w[3]*rho*rho*K-6.0*w[0]*n*Pr*mu*rv_y[q] *rho
            +5.0*w[0]*mu*m*Pr*n*r_x[q]-3.0*w[0]*gamma*K*r_y[q]*m*m
            +5.0*w[0]*n*n*Pr*lambda*r_y[q]-3.0*w[0]*n*Pr*lambda*rv_y[q]*rho
            +2.0*w[2]*rho*rho*Pr*mu*rv_y[q]-w[0]*gamma*K*E_y[q]*rho*rho
            -3.0*w[0]*gamma*K*r_y[q] *n*n+2.0*w[0]*K*gamma*rho*n*rv_y[q]
            +2.0*w[0]*K*gamma*rho*m*ru_y[q];
          s3 = s4+10.0*w[0]*n*n*Pr*mu*r_y[q]+5.0*w[0]*mu*m*m*Pr*r_y[q]
            +2.0*w[0]*gamma*K*rho*n*rv_y[q]+2.0*w[0]*gamma*K*rho*m*ru_y[q]
            -w[0]*K*gamma*E_y[q]*rho*rho+5.0*w[0]*n*Pr*lambda*m*r_x[q]
            +2.0*w[0]*K*gamma*r_y[q]*E*rho-3.0*w[0]*n*Pr*lambda*ru_x[q]*rho
            -3.0*w[0]*K*gamma*r_y[q]*n*n+2.0*w[0]*gamma*K*r_y[q]*E*rho
            -3.0*w[0]*K*gamma*r_y[q]*m*m;
          s4 = s3-3.0*w[0]*mu*m*Pr*rv_x[q]*rho-3.0*w[0]*mu*m*Pr*ru_y[q]*rho
            -2.0*w[2]*rho*r_x[q]*m*Pr*mu-w[2]*rho*r_x[q]*m*Pr*lambda+w[2]
            *rho*rho*Pr*lambda*ru_x[q]+w[2]*rho*rho*Pr*lambda*rv_y[q]
            -3.0*w[2]*rho*Pr*lambda*n*r_y[q]-6.0*w[2]*rho*r_y[q]*mu*n*Pr
            +w[1]*rho*rho*mu*Pr*rv_x[q]+w[1]*rho*rho*mu*Pr*ru_y[q];
          s2 = s4-3.0*w[1]*rho*r_y[q]*mu*m*Pr-w[2]*rho*rho*gamma*K*rv_y[q]
            -2.0*w[1]*rho*lambda*r_x[q]*n*Pr-w[1]*rho*mu*Pr*n*r_x[q]
            -w[1]*rho*rho*gamma*K*ru_y[q]-w[1]*rho*rho*K*gamma*ru_y[q]
            +2.0*w[1]*rho*gamma*K*m*r_y[q]+2.0*w[1]*rho*K*gamma*m*r_y[q]
            +2.0*w[2]*rho*gamma*K*n*r_y[q]-w[2]*rho*rho*K*gamma*rv_y[q]
            +2.0*w[2]*rho*K*gamma*n*r_y[q]-gamma*r_y[q]*w[3]*rho*rho*K;
          s3 = 1/Pr;
          s1 = s2*s3;
          s2 = 1/(rho*rho*rho*rho)/Re;
          Fy[3] = s1*s2;

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

          // compute normal flux from exterior (right) adjacent state
          for(vField::size_type k=0;k<Nfields;k++) sr[k] = Ssr[k]->u[qr];

          // put the adjacent flux on the state sides

          // Local sound speed from state flow
          for(vField::size_type k=0;k<Nfields;k++) w[k]=Ssr[k]->u[qr];
          rho = Sbr[0]->u[qr];
          m   = Sbr[1]->u[qr];
          n   = Sbr[2]->u[qr];
          E   = Sbr[3]->u[qr];

          Fx[0] = 0.0;
          Fx[1] = -2.0*(2.0*w[0]*mu*ru_x[q]*rho-4.0*w[0]*mu*m*r_x[q]
                        +w[0]*lambda*ru_x[q]*rho-2.0*w[0]*lambda*m*r_x[q]
                        +w[0]*lambda*rv_y[q]*rho-2.0*w[0]*lambda*n*r_y[q]
                        +2.0*r_x[q]*w[1]*rho*mu+r_x[q]*w[1]*rho*lambda
                        +lambda*r_y[q]*w[2]*rho)/(rho*rho*rho)/Re;
          Fx[2] = -2.0*mu*(w[0]*ru_y[q]*rho-2.0*w[0]*m*r_y[q]+w[0]*rv_x[q] *rho
                           -2.0*w[0]*n*r_x[q]+r_y[q]*w[1]*rho+r_x[q]*w[2]*rho)
            /(rho*rho*rho)/Re;
          s3 = -3.0*w[0]*m*Pr*lambda*rv_y[q]*rho+5.0*w[0]*m*Pr*lambda*n*r_y[q]
            -3.0*w[0]*gamma*K*r_x[q]*n*n-w[2]*rho*r_y[q]*mu*m*Pr
            +w[2]*rho*rho*mu*Pr*ru_y[q]+w[2]*rho*rho*mu*Pr*rv_x[q]
            -3.0*w[2]*rho*mu*Pr*n*r_x[q]-w[2]*rho*rho*gamma*K*rv_x[q]
            -gamma*r_x[q]*w[3]*rho*rho*K+2.0*w[2]*rho*K*gamma*n*r_x[q]
            -gamma*r_x[q]*w[3]*rho*rho*K;
          s2 = s3-w[2]*rho*rho*K*gamma*rv_x[q]+2.0*w[2]*rho*gamma*K*n*r_x[q]
            -3.0*w[0]*mu*n*Pr*rv_x[q]*rho+5.0*w[0]*mu*n*Pr*m*r_y[q]
            -3.0*w[0]*mu*n*Pr*ru_y[q]*rho+5.0*w[0]*mu*n*n*Pr*r_x[q]
            +5.0*w[0]*m*m*Pr*lambda*r_x[q]-3.0*w[0]*K*gamma*r_x[q]*m*m
            -3.0*w[0]*gamma*K*r_x[q]*m*m-w[0]*gamma*K*E_x[q]*rho*rho
            -3.0*w[1]*rho*r_x[q]*m*Pr*lambda;
          s3 = s2-6.0*w[1]*rho*r_x[q]*m*Pr*mu-w[0]*K*gamma*E_x[q]*rho*rho
            -3.0*w[0]*K*gamma*r_x[q]*n*n-w[1]*rho*Pr*lambda*n*r_y[q]
            +w[1]*rho*rho*Pr*lambda*rv_y[q]+w[1]*rho*rho*Pr*lambda*ru_x[q]
            +2.0*w[1]*rho*rho*Pr*mu*ru_x[q]-w[1]*rho*rho*K*gamma*ru_x[q]
            +2.0*w[1]*rho*gamma*K*m*r_x[q]-w[1]*rho*rho*gamma*K*ru_x[q];
          s1 = s3-2.0*w[1]*rho*r_y[q]*mu*n*Pr-2.0*w[2]*rho*lambda*r_y[q]*m*Pr
            +2.0*w[1]*rho*K*gamma*m*r_x[q]+2.0*w[0]*gamma*K*rho*m*ru_x[q]
            +10.0*w[0]*m*m*Pr*mu*r_x[q]+2.0*w[0]*gamma*K*rho*n*rv_x[q]
            +2.0*w[0]*gamma*K*r_x[q]*E*rho+2.0*w[0]*K*gamma*rho*m*ru_x[q]
            +2.0*w[0]*K*gamma*rho*n*rv_x[q]+2.0*w[0]*K*gamma*r_x[q]*E*rho
            -6.0*w[0]*m*Pr*mu*ru_x[q]*rho-3.0*w[0]*m*Pr*lambda*ru_x[q]*rho;
          s2 = 1/Pr/(rho*rho*rho*rho)/Re;
          Fx[3] = s1*s2;

          Fy[0] = 0.0;
          Fy[1] = -2.0*mu*(w[0]*ru_y[q]*rho-2.0*w[0]*m*r_y[q]+w[0]*rv_x[q] *rho
                           -2.0*w[0]*n*r_x[q]+r_y[q]*w[1]*rho+r_x[q]*w[2]*rho)
            /(rho*rho*rho)/Re;
          Fy[2] = -2.0*(2.0*w[0]*mu*rv_y[q]*rho-4.0*w[0]*mu*n*r_y[q]
                        +w[0]*lambda*rv_y[q]*rho-2.0*w[0]*lambda*n*r_y[q]
                        +w[0]*lambda*ru_x[q]*rho-2.0*w[0]*lambda*m*r_x[q]
                        +r_x[q]*w[1]*rho*lambda+2.0*r_y[q]*w[2]*rho*mu
                        +lambda*r_y[q]*w[2]*rho)/(rho*rho*rho)/Re;
          s4 = -gamma*r_y[q]*w[3]*rho*rho*K-6.0*w[0]*n*Pr*mu*rv_y[q] *rho
            +5.0*w[0]*mu*m*Pr*n*r_x[q]-3.0*w[0]*gamma*K*r_y[q]*m*m
            +5.0*w[0]*n*n*Pr*lambda*r_y[q]-3.0*w[0]*n*Pr*lambda*rv_y[q]*rho
            +2.0*w[2]*rho*rho*Pr*mu*rv_y[q]-w[0]*gamma*K*E_y[q]*rho*rho
            -3.0*w[0]*gamma*K*r_y[q] *n*n+2.0*w[0]*K*gamma*rho*n*rv_y[q]
            +2.0*w[0]*K*gamma*rho*m*ru_y[q];
          s3 = s4+10.0*w[0]*n*n*Pr*mu*r_y[q]+5.0*w[0]*mu*m*m*Pr*r_y[q]
            +2.0*w[0]*gamma*K*rho*n*rv_y[q]+2.0*w[0]*gamma*K*rho*m*ru_y[q]
            -w[0]*K*gamma*E_y[q]*rho*rho+5.0*w[0]*n*Pr*lambda*m*r_x[q]
            +2.0*w[0]*K*gamma*r_y[q]*E*rho-3.0*w[0]*n*Pr*lambda*ru_x[q]*rho
            -3.0*w[0]*K*gamma*r_y[q]*n*n+2.0*w[0]*gamma*K*r_y[q]*E*rho
            -3.0*w[0]*K*gamma*r_y[q]*m*m;
          s4 = s3-3.0*w[0]*mu*m*Pr*rv_x[q]*rho-3.0*w[0]*mu*m*Pr*ru_y[q]*rho
            -2.0*w[2]*rho*r_x[q]*m*Pr*mu-w[2]*rho*r_x[q]*m*Pr*lambda+w[2]
            *rho*rho*Pr*lambda*ru_x[q]+w[2]*rho*rho*Pr*lambda*rv_y[q]
            -3.0*w[2]*rho*Pr*lambda*n*r_y[q]-6.0*w[2]*rho*r_y[q]*mu*n*Pr
            +w[1]*rho*rho*mu*Pr*rv_x[q]+w[1]*rho*rho*mu*Pr*ru_y[q];
          s2 = s4-3.0*w[1]*rho*r_y[q]*mu*m*Pr-w[2]*rho*rho*gamma*K*rv_y[q]
            -2.0*w[1]*rho*lambda*r_x[q]*n*Pr-w[1]*rho*mu*Pr*n*r_x[q]
            -w[1]*rho*rho*gamma*K*ru_y[q]-w[1]*rho*rho*K*gamma*ru_y[q]
            +2.0*w[1]*rho*gamma*K*m*r_y[q]+2.0*w[1]*rho*K*gamma*m*r_y[q]
            +2.0*w[2]*rho*gamma*K*n*r_y[q]-w[2]*rho*rho*K*gamma*rv_y[q]
            +2.0*w[2]*rho*K*gamma*n*r_y[q]-gamma*r_y[q]*w[3]*rho*rho*K;
          s3 = 1/Pr;
          s1 = s2*s3;
          s2 = 1/(rho*rho*rho*rho)/Re;
          Fy[3] = s1*s2;

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
            // right flux
            for(vField::size_type j=0; j<Nfields; j++)
              fmr[j] = Ssr[j]->u[qr];
            // Central flux [gqchen]
            f[0] = pt5 * ( fpl[0] + fmr[0]);
            f[1] = pt5 * ( fpl[1] + fmr[1]);
            f[2] = pt5 * ( fpl[2] + fmr[2]);
            f[3] = pt5 * ( fpl[3] + fmr[3]);
            break;
          case vanLeer:       // Based on the Mach splitting
          case StegerWarming: // Based on the sound speed splitting
          case Roe:           // Roe average
          default:
            cerr << "Illegal value of flux type" << endl;
            exit(DGM::FAILURE);
          }
          // put fluxes on flux field sides
          for (vField::size_type ni=0; ni<Nfields; ni++) {
            Ssr[ni]->u[qr] *= -one;         // correct for normal
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
// Ur      RHS field
// Um      State field
// Um_x    State_x field
// Um_y    State_y field
//
void LinNS_quasi::diffusion( vField &Us, vField &Uf, vField &Ur ) {
  Element *S[4],*Sm[4],*Sm_x[4],*Sm_y[4],*F[4];
  Scalar  rho,m,n,E;
  dVector wk,tmp;
  dVector lam1_x,lam1_y,lam2_x,lam2_y,lam3_x,lam3_y,lam4_x,lam4_y;
  dVector Fvx1,Fvx2,Fvx3,Fvx4,Fvy1,Fvy2,Fvy3,Fvy4;
  dVector r_x,r_y,ru_x,ru_y,rv_x,rv_y,E_x,E_y;

  enforce_mean_state_bc(Um);         // update bc side values
  Um.share_sides();                  // communicate sides if parallel

  Us.fill_sides();                   // put solution on the sides
  enforce_bc(Us);                    // update bc side values
  Us.share_sides();                  // communicate sides if parallel
  average_flux( Us, Uf, '+' );       // Uf's sides are average state

  for (LocalSize e=0; e<Us[0]->ne; e++) {

    S[0] = Us[0]->el[e];       // local version of the adjoint
    S[1] = Us[1]->el[e];
    S[2] = Us[2]->el[e];
    S[3] = Us[3]->el[e];

    Sm[0] = Um[0]->el[e];      // local version of the state
    Sm[1] = Um[1]->el[e];
    Sm[2] = Um[2]->el[e];
    Sm[3] = Um[3]->el[e];


    Sm_x[0] = Um_x[0]->el[e];  // local version of the state_x
    Sm_x[1] = Um_x[1]->el[e];
    Sm_x[2] = Um_x[2]->el[e];
    Sm_x[3] = Um_x[3]->el[e];

    Sm_y[0] = Um_y[0]->el[e];  // local version of the state_y
    Sm_y[1] = Um_y[1]->el[e];
    Sm_y[2] = Um_y[2]->el[e];
    Sm_y[3] = Um_y[3]->el[e];

    F[0] = Uf[0]->el[e];       // local version of the flux
    F[1] = Uf[1]->el[e];
    F[2] = Uf[2]->el[e];
    F[3] = Uf[3]->el[e];

    const LocalSize qtot = S[0]->qtot;

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

    // get Sum_j [K^j_i M^{-1} \bQ_xj]
    for(LocalSize q=0; q<qtot; q++) {
      rho = Sm[0]->u[q];
      m   = Sm[1]->u[q];
      n   = Sm[2]->u[q];
      E   = Sm[3]->u[q];

      Fvx1[q] = 0.0;
      Fvx2[q] = -(2.0*mu+lambda)/Re*m/(rho*rho)*lam1_x[q]
        +(2.0*mu+lambda)/Re/rho*lam2_x[q]-lambda/Re*n/(rho*rho)*lam1_y[q]
        +lambda/Re/rho*lam3_y[q];
      Fvx3[q] = -mu/Re*n/(rho*rho)*lam1_x[q]
        +mu/Re/rho*lam3_x[q]-mu/Re*m/(rho*rho)*lam1_y[q]+mu/Re/rho*lam2_y[q];
      Fvx4[q] = (-(2.0*mu+lambda)*m*m/(rho*rho*rho)/Re-n*n/(rho*rho*rho)*mu/Re
                 -K/Re/Pr*(-m*m-n*n+E*rho)*gamma/(rho*rho*rho))*lam1_x[q]
        +((2.0*mu+lambda)/Re*m/(rho*rho)-K/Re/Pr*gamma*m/(rho*rho))*lam2_x[q]
        +(mu/Re*n/(rho*rho)-K/Re/Pr*gamma*n/(rho*rho))*lam3_x[q]
        +K/Re/Pr*gamma/rho*lam4_x[q]
        +(-n/(rho*rho*rho)*mu/Re*m-m/(rho*rho*rho)*lambda/Re*n)*lam1_y[q]
        +mu/Re*n/(rho*rho)*lam2_y[q]+m/(rho*rho)*lambda/Re*lam3_y[q];

      Fvy1[q] = 0.0;
      Fvy2[q] = -mu/Re*n/(rho*rho)*lam1_x[q]+mu/Re/rho*lam3_x[q]
        -mu/Re*m/(rho*rho)*lam1_y[q]+mu/Re/rho*lam2_y[q];
      Fvy3[q] = -m/(rho*rho)*lambda/Re*lam1_x[q]+lambda/Re/rho*lam2_x[q]
        -(2.0*mu+lambda)/Re*n/(rho*rho)*lam1_y[q]
        +(2.0*mu+lambda)/Re/rho*lam3_y[q];
      Fvy4[q] =(-n/(rho*rho*rho)*mu/Re*m-m/(rho*rho*rho)*lambda/Re*n)*lam1_x[q]
        +lambda/Re*n/(rho*rho)*lam2_x[q]+mu/Re*m/(rho*rho)*lam3_x[q]
        +(-m*m/(rho*rho*rho)*mu/Re-n*n/(rho*rho*rho)*(2.0*mu+lambda)/Re
          -K/Re/Pr*(-m*m-n*n+E*rho)*gamma/(rho*rho*rho))*lam1_y[q]
        +(mu/Re*m/(rho*rho)-K/Re/Pr*gamma*m/(rho*rho))*lam2_y[q]
        +((2.0*mu+lambda)/Re*n/(rho*rho)-K/Re/Pr*gamma*n/(rho*rho))*lam3_y[q]
        +K/Re/Pr*gamma/rho*lam4_y[q];
    }

    // 0
    S[0]->fill_sides( Fvx1, Fvy1 );
    S[0]->gradient(Fvx1, wk, 'x');
    S[0]->gradient(Fvy1, tmp, 'y');
    dvadd( tmp, wk, F[0]->u );

    // 1
    S[1]->fill_sides( Fvx2, Fvy2 );
    S[1]->gradient(Fvx2, wk, 'x');
    S[1]->gradient(Fvy2, tmp, 'y');
    dvadd( tmp, wk, F[1]->u );

    // 2
    S[2]->fill_sides( Fvx3, Fvy3 );
    S[2]->gradient(Fvx3, wk, 'x');
    S[2]->gradient(Fvy3, tmp, 'y');
    dvadd( tmp, wk, F[2]->u );

    // 3
    S[3]->fill_sides( Fvx4, Fvy4 );
    S[3]->gradient(Fvx4, wk, 'x');
    S[3]->gradient(Fvy4, tmp, 'y');
    dvadd( tmp, wk, F[3]->u );

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

  scale(-1.0,Uf);  // I currently put everything on the LHS
  // add in viscous contribution
  for (vField::size_type k=0; k<Uf.size(); k++) add( Uf[k], Ur[k] );
}

void LinNS_quasi::enforce_mean_state_bc(vField &S) {
  dVector us[4];
  dVector ub[4];
  for (Ordinal n=0; n<S[0]->nbc; n++) {
    Ordinal sid = S[0]->bc[n]->sid;
    Ordinal qtot = S[0]->bc[n]->elmt->side[sid]->qtot();
    //dVector &nx = S[0]->bc[n]->elmt->side[sid]->nx();
    //dVector &ny = S[0]->bc[n]->elmt->side[sid]->ny();
    switch (S[0]->bc[n]->type[0]) {
    default:
      for (Ordinal i=0; i<Nfields; i++) {
        us[i].alias( S[i]->bc[n]->elmt->side[sid]->u );
        ub[i].alias( S[i]->bc[n]->elmt->side[sid]->link->u );
      }
      for (Ordinal i=0; i<qtot; i++) {
        ub[0][i] = us[0][i];
        ub[1][i] = us[1][i];
        ub[2][i] = us[2][i];
        ub[3][i] = us[3][i];
      }
      break;
    }
  }
}

void LinNS_quasi::enforce_mean_derivate_bc(vField &S) {
  dVector us[4];
  dVector ub[4];
  for (LocalSize n=0; n<S[0]->nbc; n++) {
    LocalSize sid = S[0]->bc[n]->sid;
    LocalSize qtot = S[0]->bc[n]->elmt->side[sid]->qtot();
    //dVector &nx = S[0]->bc[n]->elmt->side[sid]->nx();
    //dVector &ny = S[0]->bc[n]->elmt->side[sid]->ny();
    switch (S[0]->bc[n]->type[0]) {
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

// State boundary
// 1) our enforcing variable is \bQ = M \bu'
// 2) So each time, always force the constraints to \bu' @wall
//    then form \bQ = M \bu', one of the question here is
//    M, shoudld it also use the M at the boundary which considers
//    those physical constraints?
void LinNS_quasi::enforce_bc(vField &S) {
  // Here we only consider the zero mean flow, so the quasi-variable the first
  // three are same as the primitive ones, refer to the Jacobi matrix from
  // mean flow so for wall normal B.C, its implementation is similar to the
  // conservative form

  // For inflow B.C, since fluctuation there are all zero, so we set them all
  // zero, it should be O.K.
  Scalar rho, m, n, E, w[4];
  Scalar rhop, up, vp, Tp;
  dVector um[4];
  dVector us[4];
  dVector ub[4];

  for (LocalSize bn=0; bn<S[0]->nbc; bn++) {
    LocalSize sid = S[0]->bc[bn]->sid;
    LocalSize qtot = S[0]->bc[bn]->elmt->side[sid]->qtot();
    //dVector &nx = S[0]->bc[bn]->elmt->side[sid]->nx();
    //dVector &ny = S[0]->bc[bn]->elmt->side[sid]->ny();
    // Some problems for wall boundary
    switch (S[0]->bc[bn]->type[0]) {
    case 'W': // Isothermal wall
      for (vField::size_type i=0; i<Nfields; i++) {
        um[i].alias( Um[i]->bc[bn]->elmt->side[sid]->u );
        us[i].alias( S[i]->bc[bn]->elmt->side[sid]->u );
        ub[i].alias( S[i]->bc[bn]->elmt->side[sid]->link->u );
      }
      for (LocalSize q=0; q<qtot; q++) {
        for(int j=0; j<4; j++) w[j] = us[j][q];
        rho = um[0][q];
        m   = um[1][q];
        n   = um[2][q];
        E   = um[3][q];

        // Get Up
        rhop = w[0];
        up   = -m/(rho*rho)*w[0]+1/rho*w[1];
        vp   = -n/(rho*rho)*w[0]+1/rho*w[2];
        Tp   = -gamma*Ma*Ma*(gamma-1.0)*(-m*m-n*n+E*rho)/(rho*rho*rho)*w[0]
              - gamma*Ma*Ma*(gamma-1.0)*m/(rho*rho)*w[1]
              - gamma*Ma*Ma*(gamma-1.0)*n/(rho*rho)*w[2]
              + gamma*Ma*Ma*(gamma-1.0)/rho*w[3];

        // Form the new Up
        // rhop = rhop;
        up = zero;
        vp = zero;
        Tp = zero;

        w[0] = rhop;
        w[1] = up;
        w[2] = vp;
        w[3] = Tp;

        // Form Quasi U = M*Up
        ub[0][q] = w[0];
        ub[1][q] = m/rho*w[0]+rho*w[1];
        ub[2][q] = n/rho*w[0]+rho*w[2];
        ub[3][q] = E/rho*w[0]+m*w[1]+n*w[2]
          + rho/gamma/(Ma*Ma)/(gamma-1.0)*w[3];
      }
      break;
    default:
      // enforce an incoming acoustic wave, what is this for? [SSC]
      for (vField::size_type i=0; i<Nfields; i++) {
        um[i].alias( Um[i]->bc[bn]->elmt->side[sid]->u );
        us[i].alias( S[i]->bc[bn]->elmt->side[sid]->u );
        ub[i].alias( S[i]->bc[bn]->elmt->side[sid]->link->u );
      }
      const Scalar c = one/Ma;
      const Scalar k = 2.5;
      AcousticWave pw(Ma, 1.0, gamma, 0.02, 0.0, 0.7, 'x', 'p',
                      AcousticWave::Gaussian);
      // Why don't you use a Coord here instead of a Point* ?  [SSC]
      Point *pside = new Point[S[0]->bc[bn]->elmt->side[sid]->qtot()];
      S[0]->bc[bn]->elmt->get_side_coordinates(sid, pside);
      Point cxy;
      for (LocalSize q=0; q<qtot; q++) {
        cxy = Point(pside[q].x,pside[q].y);
        w[0] = pw.R(cxy)*sin(k*(cxy.x-0-c*t)); // rho
        w[1] = pw.U(cxy)*sin(k*(cxy.x-0-c*t)); // u
        w[2] = pw.V(cxy)*sin(k*(cxy.x-0-c*t)); // v
        w[3] = pw.T(cxy)*sin(k*(cxy.x-0-c*t)); // T

        rho = um[0][q];
        m   = um[1][q];
        n   = um[2][q];
        E   = um[3][q];

        // form the quasi_variable
        ub[0][q] = w[0];
        ub[1][q] = m/rho*w[0]+rho*w[1];
        ub[2][q] = n/rho*w[0]+rho*w[2];
        ub[3][q] = E/rho*w[0]+m*w[1]+n*w[2]
                 + rho/gamma/(Ma*Ma)/(gamma-1.0)*w[3];
      }
      delete[] pside;
      break;
    }
  }
}

//  Flux boundary
// 1) our enforcing variable is \bQ = M \bu'
// 2) so {\bQ}_{,x_j} = (M \bu')_{,x_j} = M_{,x_j} \bu' + M {\bu'}_{,x_j}
// 3) So each time, always force the constraints to \bu' and {\bu'}_{,x_j}@wall
//    then form {\bQ}_{,x_j}= M_{,x_j} \bu' + M {\bu'}_{,x_j},
//    It is a little troublesome:-(
// 4) For the inflow/outflow boundary, we can try ZERO traction first
void LinNS_quasi::enforce_flux_bc(vField &S) {
  dVector ub[4],us[4];
  for (LocalSize bn=0; bn<S[0]->nbc; bn++) {
    LocalSize sid = S[0]->bc[bn]->sid;
    LocalSize qtot = S[0]->bc[bn]->elmt->side[sid]->qtot();
    //dVector &nx = S[0]->bc[bn]->elmt->side[sid]->nx();
    //dVector &ny = S[0]->bc[bn]->elmt->side[sid]->ny();
    switch (S[0]->bc[bn]->type[0]) {
    case 'W': // Isothermal wall
      for (vField::size_type i=0; i<Nfields; i++) {
        us[i].alias( S[i]->bc[bn]->elmt->side[sid]->u );
        ub[i].alias( S[i]->bc[bn]->elmt->side[sid]->link->u );
      }
      for (LocalSize q=0; q<qtot; q++) {
        ub[0][q] = -us[0][q];
        ub[1][q] = -us[1][q];
        ub[2][q] = -us[2][q];
        ub[3][q] = -us[3][q];
      }
      break;
    default: // far-field flux BC, simple treatment: zero-traction [gqchen]
      for (vField::size_type i=0; i<Nfields; i++) {
        us[i].alias( S[i]->bc[bn]->elmt->side[sid]->u );
        ub[i].alias( S[i]->bc[bn]->elmt->side[sid]->link->u );
      }
      // hardwire the state for now
      for (LocalSize i=0; i<qtot; i++) {
        ub[0][i] = 0.0;
        ub[1][i] = 0.0;
        ub[2][i] = 0.0;
        ub[3][i] = 0.0;
      }
      break;
    }
  }
}

/*! \note Current only supports zero flow base state */
void LinNS_quasi::set_mean(vField &Fm) {
  for (LocalSize e=0; e<ne; e++) {
    for (LocalSize q=0; q<Fm[0]->el[e]->qtot; q++) {
      Fm[0]->el[e]->u[q] = 1.0;
      Fm[1]->el[e]->u[q] = 0.0;
      Fm[2]->el[e]->u[q] = 0.0;
      Fm[3]->el[e]->u[q] = 1.0*1.0/(gamma*(gamma-1.0)*Ma*Ma);
    }
  }
  // project fields to the polynomial space just to make sure
  Fm.project();
}

void LinNS_quasi::make_U(vField &F, const vField &Fm, const vField &Fp) {
  Scalar rho,m,n,E,w[4];
  for (LocalSize e=0; e<ne; e++) {
    for (LocalSize q=0; q<F[0]->el[e]->qtot; q++) {
      for(vField::size_type i=0;i<Nfields;i++) w[i]=Fp[i]->el[e]->u[q];
      rho = Fm[0]->el[e]->u[q];
      m = Fm[1]->el[e]->u[q];
      n = Fm[2]->el[e]->u[q];
      E = Fm[3]->el[e]->u[q];
      F[0]->el[e]->u[q] = w[0];
      F[1]->el[e]->u[q] = m/rho*w[0]+rho*w[1];
      F[2]->el[e]->u[q] = n/rho*w[0]+rho*w[2];
      F[3]->el[e]->u[q] = E/rho*w[0]+m*w[1]+n*w[2]
                        + rho/gamma/(Ma*Ma)/(gamma-1.0)*w[3];
    }
  }
#if 0
  cout << "WARNING:  No projection of Initial condition" << endl;
  for (vField::size_type i=0; i<Nfields; i++)
    for (LocalSize e=0; e<ne; e++)
      F[i]->el[e]->state = Physical;
#else
  // project fields to the polynomial space just to make sure
  F.project();
#endif
}

void LinNS_quasi::get_Up(vField &Fp, const vField &Fm, const vField &F) {
  Scalar rho,m,n,E,w[4];
  for (LocalSize e=0; e<ne; e++) {
    for (LocalSize q=0; q<F[0]->el[e]->qtot; q++) {
      for(vField::size_type i=0;i<Nfields;i++) w[i]=F[i]->el[e]->u[q];
      rho = Fm[0]->el[e]->u[q];
      m   = Fm[1]->el[e]->u[q];
      n   = Fm[2]->el[e]->u[q];
      E   = Fm[3]->el[e]->u[q];
      Fp[0]->el[e]->u[q] = w[0];
      Fp[1]->el[e]->u[q] = -m/(rho*rho)*w[0]+1/rho*w[1];
      Fp[2]->el[e]->u[q] = -n/(rho*rho)*w[0]+1/rho*w[2];
      Fp[3]->el[e]->u[q] = -gamma*Ma*Ma*(gamma-1.0)*(-m*m-n*n+E*rho)
        /(rho*rho*rho)*w[0]-gamma*Ma*Ma*(gamma-1.0)*m/(rho*rho)*w[1]
        -gamma*Ma*Ma*(gamma-1.0)*n/(rho*rho)*w[2]
        +gamma*Ma*Ma*(gamma-1.0)/rho*w[3];
    }
  }
#if 0
  cout << "WARNING:  No projection of Initial condition" << endl;
  for (vField::size_type i=0; i<Nfields; i++)
    for (LocalSize e=0; e<ne; e++)
      F[i]->el[e]->state = Physical;
#else
  // project fields to the polynomial space just to make sure
  Fp.project();
#endif
}

/// Generate output files for plotting
/*! \warning Not all methods work properly in parallel
 *  \note Need to update to include parallel Plot3d and Paraview writers
*/
int LinNS_quasi::plot(const string &rst) {
  string fname, name(rst);
  char buf[buflen];
  read( rst, Up );
  name.erase(name.find(".rst"));  // erase extension
  sprintf(buf,"%s.dat",name.c_str()); fname = buf;
  // Get Up is unnecessary,since the restart file saved as primitive form
  // get_Up(Up,Um,U);
  if (comm->Master()) Up.tecplot(fname,"Solution");
#ifdef DGM_LINNS_USE_PLOT3D
  // output to plot3d multi-grid format
  sprintf(buf,"%s.xyz",name.c_str()); fname = buf;
  if (comm->Master()) Up.plot3d_xy(fname,"Solution");
  sprintf(buf,"%s.q",name.c_str()); fname = buf;
  if (comm->Master()) Up.plot3d_q2(fname,"Solution");
#endif
  compute_vorticity();
  sprintf(buf,"%s.aux.dat",name.c_str()); fname = buf;
  if (comm->Master()) Ut.tecplot(fname,"Vorticity");
  return 0;
}

} // namespace Reo
