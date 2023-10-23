/*=============================================================================
  Module:     LinEuler Quasi-conservative Module

  Author:     Guoquan Chen

  Copyright:  S. Scott Collis
              Department of Mechanical Engineering and Materials Science
              Rice University, MS 321
              Houston, TX 77005-1892
              (713) 348-3617
              collis@rice.edu
=============================================================================*/

/** \file LinEuler_quasi.cpp
    \brief Linearized Euler solver in quasi-conservative variables
    \author Guoquan Chen
    \author Scott Collis

    Linearized solver based on the conservative form with primitive variables
    (currently assumes the mean flow is steady)
    \f[ U = D(Q)/D(U_m) [\rho u v T] \f]
    where \f$Ma\f$ is the reference Mach number, to avoid explicitly using it,
    we rescale \f$T_r*  = T_r / (Ma*Ma)\f$.
*/

// DGM includes
#include "TimeInt.hpp"

// Reo includes
#include "LinEuler_quasi.hpp"
#include "LinEuler_quasiBC.hpp"
#include "Wavetype.hpp"

namespace Reo {

// constructor
LinEuler_quasi::LinEuler_quasi( DGM::ArgList &args,
                                const DGM::Comm::Ptr comm_)
  : Euler(args,comm_), Up(comm_), Um(comm_) {

  setup_BCdb();                        // setup BC database

  // make auxiliary Fields using copy constructor
  for (vField::size_type i=0; i<Nfields; i++) {
    // make the mean flow Field
    Um.push_back( new Field( U[0], root, U[i]->name) );
    Up.push_back( new Field( U[0], root, U[i]->name) );
  }

#ifdef REO_USE_GETSIDEMAPS
  setup_side_maps();
#endif

  // allocate more workspace
  wk3.resize(10*max(Lmax(),Qmax()));
  wk4.resize(10*max(Lmax(),Qmax()));
}

void LinEuler_quasi::zero_all_fields() {
  Domain::zero_all_fields();
  Um.zero();
  Up.zero();
}

int LinEuler_quasi::plot(const string &rst) {
  // Get Up --- unnecessary,since the restart file saved as primitive form
  // get_Up(Um,U,Up);
  string fname, name(rst), caption;
  char buf[80];
  read( rst, U );
  size_t loc = name.find(".rst");
  if ( loc != string::npos )
    name.erase(loc);
  sprintf(buf,"%s.dat",name.c_str()); fname = buf;
  sprintf(buf,"State variables at t =%11.4e, step = %lld",t,(long long)step);
  caption = buf;
  if (params["tecplot"] )
    if (comm->Master()) Up.tecplot(fname,caption);
  if (params["plot3d"]) {
    if (params["plot3d_x"]) {
      sprintf(buf,"%s.xyz",name.c_str()); fname = buf;
      if (comm->Master()) Up.plot3d_x(fname);
    }
    if (params["plot3d_q"]) {
      sprintf(buf,"%s.q",name.c_str()); fname = buf;
      if (comm->Master()) Up.plot3d_q(fname);
    }
  }
  if (params["auxtec"]) {
    compute_vorticity();  // puts vorticity in Ut
    sprintf(buf,"%s.aux.dat",name.c_str()); fname = buf;
    sprintf(buf,"Auxiliary variables at t =%11.4e, step = %lld",
            t,(long long)step);
    caption = buf;
    if (comm->Master()) Ut.tecplot(fname,caption);
  }
  return 0;

}

int LinEuler_quasi::solve() {
  Format sci(4); sci.scientific().width(12);

  if (DGM::Comm::World->Master()) cout << "Title = " << title << endl;

  set_mean(Um,'p');    // set the mean flow field
  set_ic(Up);      // set the initial condition (primitive field)
  make_U(Um,Up,U); // make the initial condition (solution variable)

#ifndef DGM_PARALLEL
  Up.tecplot("ic.dat","Initial Condition");
#endif

  comm->cout() << "Advancing solution " << Nt << " time steps" << endl;
  Scalar ctime=0, stime=0, ttime=0;
  int cnt=0;
  Stopwatch cpu; cpu.start();
  comm->cout()<<"    Step      t           dt         CFL         dCPU\n";
  for (lstep=1; lstep<=Nt; lstep++) {
    step++;
    time_int->advance(this);
    ctime = cpu.restart();
    if (lstep>1) { ttime += ctime; stime += ctime*ctime; cnt++; }
    if (lstep%ntout==0)
      comm->cout()<<setw(8)<<step<<sci(t)<<sci(dt)<<sci(CFL)<<sci(ctime)<<endl;

    if (step%Ntout==0)  {
      get_Up(Um,U,Up);
      write(step, Up);
      Up.norm();
      cpu.restart();
    }

  }

#ifdef DGM_PARALLEL
  Scalar atime=0, otime=0;
  comm->SumAll( &ttime, &atime, 1 );  // average cpu time
  comm->SumAll( &stime, &otime, 1 );  // standard deviation of the cpu time
  int n = max(1,cnt*comm->NumProc());
  atime /= n; otime /= n;
  Scalar stdev = ::sqrt(otime - atime*atime);
  comm->cout() << "Average time per step: " << sci(atime)
               << ", standard deviation:  " << sci(stdev) << endl;
#endif


  return 0;
}

void LinEuler_quasi::time_derivative( vField &Us, vField &Uf ) {
  convection( Us, Uf );
#if 0
  set_sponge(Us,Uf);
#else
  add_source(Us,Uf);
#endif
  project( Uf );
}

void LinEuler_quasi::convection( vField &Us, vField &Uf ) {
  Element *U[4], *F[4],*Fm[4];
  dVector u1, u2, u3, Fx1, Fx2, Fx3, Fx4, Fy1, Fy2, Fy3, Fy4, d;

  Scalar w[4], u[2], T;

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

    //For simple case, the mean flow is uniform flow ,
    // Since A(au),B(au) constant matrix
    // we can get F(u(x)),x = A(au) u,x
    //            G(u(x)),y = B(au) u,y
    // In future, if the mean flow has the spatial distribution, we should
    //     Set    F(u(x)),x = (A(au) u),x
    //            G(u(x)),y = (B(au) u),y

    for (LocalSize q=0; q<qtot; q++) {

      //   AMinvQ = vector([q[2], (-u[1]^2+c^2)*q[1]+2*u[1]*q[2],
      //                   -u[1]*u[2]*q[1]+u[2]*q[2]+u[1]*q[3]])

      for(vField::size_type i=0;i<Nfields;i++) w[i]=U[i]->u[q];
      //rho = Fm[0]->u[q];
      u[0]= Fm[1]->u[q];
      u[1]= Fm[2]->u[q];
      T   = Fm[3]->u[q];

      // code produced by Maple
      Fx1[q] = w[1];
      Fx2[q] = -3.0/2.0*w[0]*u[0]*u[0]+w[0]*u[0]*u[0]*gamma/2.0
        +w[0]*u[1]*u[1]*gamma/2.0-w[0]*u[1]*u[1]/2.0+3.0*w[1]*u[0]
        -w[1]*u[0]*gamma-w[2]*u[1]*gamma+w[2]*u[1]+w[3]*gamma-w[3];
      Fx3[q] = -u[0]*u[1]*w[0]+u[1]*w[1]+u[0]*w[2];
      Fx4[q] = -(3.0*u[0]*u[0]*u[0]*w[0]*gamma -2.0*u[0]*u[0]*u[0]*w[0]
                 +3.0*u[0]*w[0]*u[1]*u[1]*gamma + 2.0*u[0]*w[0]*T
                 -2.0*u[0]*w[0]*u[1]*u[1] - u[0]*u[0]*u[0]*w[0]*gamma*gamma
                 - u[0]*w[0]*u[1]*u[1]*gamma*gamma - 5.0*w[1]*u[0]*u[0]*gamma
                 + 3.0*w[1]*u[0]*u[0] -w[1]*u[1]*u[1]*gamma
                 + w[1]*u[1]*u[1] - 2.0*w[1]*T + 2.0*w[1]*u[0]*u[0]*gamma*gamma
                 +2.0*u[0]*u[1]*w[2]*gamma*gamma-4.0*u[0]*u[1]*w[2]*gamma
                 +2.0*u[0]*u[1]*w[2] - 2.0*u[0]*gamma*gamma*w[3]
                 +2.0*u[0]*gamma*w[3])/(gamma-1.0)/2.0;

      Fy1[q] = w[2];
      Fy2[q] = -u[0]*u[1]*w[0]+u[1]*w[1]+u[0]*w[2];
      Fy3[q] = -3.0/2.0*w[0]*u[1]*u[1]+w[0]*u[0]*u[0]*gamma/2.0
        -w[0]*u[0]*u[0]/2.0+w[0]*u[1]*u[1]*gamma/2.0-w[1]*u[0]*gamma+w[1]*u[0]
        +3.0*w[2]*u[1]-w[2]*u[1]*gamma+w[3]*gamma-w[3];
      Fy4[q] = -(3.0*u[1]*w[0]*u[0]*u[0]*gamma - 2.0*u[1]*w[0]*u[0]*u[0]
                 +3.0*u[1]*u[1]*u[1]*w[0]*gamma + 2.0*u[1]*w[0]*T
                 -2.0*u[1]*u[1]*u[1]*w[0] - u[1]*w[0]*u[0]*u[0]*gamma*gamma
                 - u[1]*u[1]*u[1]*w[0]*gamma*gamma
                 + 2.0*u[0]*u[1]*w[1]*gamma*gamma - 4.0*u[0]*u[1]*w[1]*gamma
                 + 2.0*u[0]*u[1]*w[1] - 5.0*w[2]*u[1]*u[1]*gamma
                 + 3.0*w[2]*u[1]*u[1]
                 - w[2]*u[0]*u[0]*gamma + w[2]*u[0]*u[0] - 2.0*w[2]*T
                 + 2.0*w[2]*u[1]*u[1]*gamma*gamma - 2.0*u[1]*gamma*gamma*w[3]
                 + 2.0*u[1]*gamma*w[3])/(gamma-1.0)/2.0;
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
void LinEuler_quasi::convective_flux(vField &Us, vField &Uf) {
  flux_type flux = LaxFriedrichs; //StegerWarming; //vanLeer;
  dVector sl(Nfields), sr(Nfields), f(Nfields);
  dVector slm(Nfields), srm(Nfields);
  Scalar ulm, clm; // ul,ml,nl,El,vl,pl,Hl,Ml,
  Scalar urm,  crm; // ur,mr,nr,Er,vr,pr,Hr,Mr,
  vector<Side *> Ssl(Nfields), Ssr(Nfields);
  vector<Side *> Sbl(Nfields), Sbr(Nfields);     // mean flow field sides
  vector<Side *> Sfl(Nfields), Sfr(Nfields);
  dVector fpl(Nfields), fmr(Nfields),lam(Nfields);
  Scalar lmax;
  Scalar w[4], u[2], T;
#ifdef REO_USE_GETSIDEMAPS
  iVector mapl, mapr;
#endif
  dVector Fx(Nfields),Fy(Nfields);
  for (LocalSize e=0; e<Us[0]->ne; e++) {                   // loop over elements
    Element* U = Us[0]->el[e];
    for (LocalSize i=0; i<Us[0]->el[e]->nSides(); i++) {    // loop over sides
      if (Us[0]->el[e]->side[i]->master()) {                // compute if master
        const LocalSize qtot = Us[0]->el[e]->side[i]->qtot(); // side quad pts
        for (vField::size_type ni=0; ni<Nfields; ni++) {
          Ssl[ni] = Us[ni]->el[e]->side[i];        // left state side
          Ssr[ni] = Us[ni]->el[e]->side[i]->link;  // right state side
          Sfl[ni] = Uf[ni]->el[e]->side[i];        // left flux side
          Sfr[ni] = Uf[ni]->el[e]->side[i]->link;  // right flux side
          Sbl[ni] = Um[ni]->el[e]->side[i];       // left mean side
          Sbr[ni] = Um[ni]->el[e]->side[i]->link; // right mean side
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

          //From solution U
          for(vField::size_type k=0;k<Nfields;k++)
            sl[k] = Ssl[k]->u[ql];

          //normal velocity --mean flow
          ulm = Sbl[1]->u[ql]*nx +Sbl[2]->u[ql]*ny;
          // ul = Ssl[1]->u[ql]*nx +Ssl[2]->u[ql]*ny;

          for(vField::size_type k=0;k<Nfields;k++) w[k]=Ssl[k]->u[ql];
          // rho = Sbl[0]->u[ql];
          u[0] = Sbl[1]->u[ql];
          u[1] = Sbl[2]->u[ql];
          T    = Sbl[3]->u[ql];

          Fx[0] = w[1];
          Fx[1] = -3.0/2.0*w[0]*u[0]*u[0]+w[0]*u[0]*u[0]*gamma/2.0
            +w[0]*u[1]*u[1]*gamma/2.0-w[0]*u[1]*u[1]/2.0+3.0*w[1]*u[0]
            -w[1]*u[0]*gamma-w[2]*u[1]*gamma+w[2]*u[1]+w[3]*gamma-w[3];
          Fx[2] = -u[0]*u[1]*w[0]+u[1]*w[1]+u[0]*w[2];
          Fx[3] = -(3.0*u[0]*u[0]*u[0]*w[0]*gamma -2.0*u[0]*u[0]*u[0]*w[0]
                    +3.0*u[0]*w[0]*u[1]*u[1]*gamma + 2.0*u[0]*w[0]*T
                    - 2.0*u[0]*w[0]*u[1]*u[1] - u[0]*u[0]*u[0]*w[0]*gamma*gamma
                    - u[0]*w[0]*u[1]*u[1]*gamma*gamma -5.0*w[1]*u[0]*u[0]*gamma
                    + 3.0*w[1]*u[0]*u[0] -w[1]*u[1]*u[1]*gamma
                    + w[1]*u[1]*u[1]- 2.0*w[1]*T+2.0*w[1]*u[0]*u[0]*gamma*gamma
                    +2.0*u[0]*u[1]*w[2]*gamma*gamma-4.0*u[0]*u[1]*w[2]*gamma
                    +2.0*u[0]*u[1]*w[2] - 2.0*u[0]*gamma*gamma*w[3]
                    +2.0*u[0]*gamma*w[3])/(gamma-1.0)/2.0;

          Fy[0] = w[2];
          Fy[1] = -u[0]*u[1]*w[0]+u[1]*w[1]+u[0]*w[2];
          Fy[2] = -3.0/2.0*w[0]*u[1]*u[1]+w[0]*u[0]*u[0]*gamma/2.0
            -w[0]*u[0]*u[0]/2.0+w[0]*u[1]*u[1]*gamma/2.0-w[1]*u[0]*gamma
            +w[1]*u[0] + 3.0*w[2]*u[1]-w[2]*u[1]*gamma+w[3]*gamma-w[3];
          Fy[3] = -(3.0*u[1]*w[0]*u[0]*u[0]*gamma - 2.0*u[1]*w[0]*u[0]*u[0]
                    +3.0*u[1]*u[1]*u[1]*w[0]*gamma + 2.0*u[1]*w[0]*T
                    -2.0*u[1]*u[1]*u[1]*w[0] - u[1]*w[0]*u[0]*u[0]*gamma*gamma
                    - u[1]*u[1]*u[1]*w[0]*gamma*gamma
                    + 2.0*u[0]*u[1]*w[1]*gamma*gamma - 4.0*u[0]*u[1]*w[1]*gamma
                    + 2.0*u[0]*u[1]*w[1] - 5.0*w[2]*u[1]*u[1]*gamma
                    + 3.0*w[2]*u[1]*u[1]- w[2]*u[0]*u[0]*gamma + w[2]*u[0]*u[0]
                    - 2.0*w[2]*T  + 2.0*w[2]*u[1]*u[1]*gamma*gamma
                    - 2.0*u[1]*gamma*gamma*w[3]
                    + 2.0*u[1]*gamma*w[3])/(gamma-1.0)/2.0;


          Ssl[0]->u[ql] = Fx[0]*nx + Fy[0]*ny;
          Ssl[1]->u[ql] = Fx[1]*nx + Fy[1]*ny;
          Ssl[2]->u[ql] = Fx[2]*nx + Fy[2]*ny;
          Ssl[3]->u[ql] = Fx[3]*nx + Fy[3]*ny;

          // compute normal flux from exterior (right)

          // adjacent state (Primitive form)
          for(vField::size_type k=0;k<Nfields;k++)
            sr[k] = Ssr[k]->u[qr];

          urm = Sbr[1]->u[qr]*nx +Sbr[2]->u[qr]*ny;
          // ur = Ssr[1]->u[qr]*nx +Ssr[2]->u[qr]*ny;

          // put the adjacent flux on the state sides

          for(vField::size_type k=0;k<Nfields;k++) w[k]=Ssr[k]->u[qr];
          //rho = Sbr[0]->u[qr];
          u[0] = Sbr[1]->u[qr];
          u[1] = Sbr[2]->u[qr];
          T    = Sbr[3]->u[qr];

          Fx[0] = w[1];
          Fx[1] = -3.0/2.0*w[0]*u[0]*u[0]+w[0]*u[0]*u[0]*gamma/2.0
            +w[0]*u[1]*u[1]*gamma/2.0-w[0]*u[1]*u[1]/2.0+3.0*w[1]*u[0]
            -w[1]*u[0]*gamma-w[2]*u[1]*gamma+w[2]*u[1]+w[3]*gamma-w[3];
          Fx[2] = -u[0]*u[1]*w[0]+u[1]*w[1]+u[0]*w[2];
          Fx[3] = -(3.0*u[0]*u[0]*u[0]*w[0]*gamma -2.0*u[0]*u[0]*u[0]*w[0]
                    +3.0*u[0]*w[0]*u[1]*u[1]*gamma + 2.0*u[0]*w[0]*T
                    -2.0*u[0]*w[0]*u[1]*u[1] - u[0]*u[0]*u[0]*w[0]*gamma*gamma
                    - u[0]*w[0]*u[1]*u[1]*gamma*gamma-5.0*w[1]*u[0]*u[0]*gamma
                    + 3.0*w[1]*u[0]*u[0] -w[1]*u[1]*u[1]*gamma
                    + w[1]*u[1]*u[1] - 2.0*w[1]*T
                    + 2.0*w[1]*u[0]*u[0]*gamma*gamma
                    +2.0*u[0]*u[1]*w[2]*gamma*gamma-4.0*u[0]*u[1]*w[2]*gamma
                    +2.0*u[0]*u[1]*w[2] - 2.0*u[0]*gamma*gamma*w[3]
                    +2.0*u[0]*gamma*w[3])/(gamma-1.0)/2.0;

          Fy[0] = w[2];
          Fy[1] = -u[0]*u[1]*w[0]+u[1]*w[1]+u[0]*w[2];
          Fy[2] = -3.0/2.0*w[0]*u[1]*u[1]+w[0]*u[0]*u[0]*gamma/2.0
            -w[0]*u[0]*u[0]/2.0+w[0]*u[1]*u[1]*gamma/2.0-w[1]*u[0]*gamma
            +w[1]*u[0] + 3.0*w[2]*u[1]-w[2]*u[1]*gamma+w[3]*gamma-w[3];
          Fy[3] = -(3.0*u[1]*w[0]*u[0]*u[0]*gamma - 2.0*u[1]*w[0]*u[0]*u[0]
                    +3.0*u[1]*u[1]*u[1]*w[0]*gamma + 2.0*u[1]*w[0]*T
                    -2.0*u[1]*u[1]*u[1]*w[0] - u[1]*w[0]*u[0]*u[0]*gamma*gamma
                    - u[1]*u[1]*u[1]*w[0]*gamma*gamma
                    + 2.0*u[0]*u[1]*w[1]*gamma*gamma - 4.0*u[0]*u[1]*w[1]*gamma
                    + 2.0*u[0]*u[1]*w[1] - 5.0*w[2]*u[1]*u[1]*gamma
                    + 3.0*w[2]*u[1]*u[1] - w[2]*u[0]*u[0]*gamma
                    + w[2]*u[0]*u[0] - 2.0*w[2]*T
                    + 2.0*w[2]*u[1]*u[1]*gamma*gamma
                    - 2.0*u[1]*gamma*gamma*w[3]
                    + 2.0*u[1]*gamma*w[3])/(gamma-1.0)/2.0;

          Ssr[0]->u[qr] = Fx[0]*nx + Fy[0]*ny;
          Ssr[1]->u[qr] = Fx[1]*nx + Fy[1]*ny;
          Ssr[2]->u[qr] = Fx[2]*nx + Fy[2]*ny;
          Ssr[3]->u[qr] = Fx[3]*nx + Fy[3]*ny;

          switch (flux) {
          case LaxFriedrichs:
            lmax = zero;
            clm = ::sqrt(Sbl[Nfields-1]->u[ql]);
            lam[0] = ulm;
            lam[1] = ulm+clm;
            lam[2] = ulm-clm;
            lam[3] = ulm;
            for(vField::size_type j=0; j<Nfields;j++) {
              lmax = max(lmax,fabs(lam[j]));
              fpl[j] = Ssl[j]->u[ql];
            }
            crm = ::sqrt(Sbr[Nfields-1]->u[qr]);
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
#ifdef VERBOSE
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

// set a vector field from a file
void LinEuler_quasi::set_ic(vField &F, string ext) {
  string fname = root+ext;
  ifstream in(fname.c_str());
  if (!in) {
    cerr << "Could not open initial condition " << fname << endl;
    DGM::Comm::World->exit(DGM::FAILURE);
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
      cerr << "Cannot read restart file name from " << fname << endl;
      DGM::Comm::World->exit(DGM::FAILURE);
    }
    read(rstfile,F);
  } else if (lowerCase(code) == "wave_scatter" ) {   // planar acoustic wave
    Scalar Ma = 0.3;
    //Scalar x0 =0;
    Scalar amp = 0.02;
    Scalar k = 2.5; // wave number
    Scalar mC = 1.0/Ma;

    Scalar rhom = 0.5*amp/mC/mC;
    Scalar um = amp*0.5/mC/1.0;
    Scalar vm = 0;
    Scalar Tm = amp*(gamma*Ma*Ma*0.5 - 1.0 *0.5/mC/mC)/1.0/Ma/Ma;

    for (LocalSize e=0; e<ne; e++) {
      for (LocalSize q=0; q<F[0]->el[e]->qtot; q++) {
        Scalar x=F[0]->el[e]->C->x[q];
        Scalar rho = rhom*sin(k*(x-0)); //rho
        Scalar u   = um*sin(k*(x-0)); //u
        Scalar v   = vm*sin(k*(x-0)); //v
        Scalar T   = Tm*sin(k*(x-0)); //T
        F[0]->el[e]->u[q] = rho;
        F[1]->el[e]->u[q] = u;
        F[2]->el[e]->u[q] = v;
        F[3]->el[e]->u[q] = T;
      }
    }
  } else {
    comm->error("LinEuler_quasi::set_ic()  Unsupported IC type");
  }
#ifdef DGM_NO_PROJECT_IC
  cout << "WARNING:  No projection of Initial condition" << endl;
  for (LocalSize i=0; i<Nfields; i++)
    for (LocalSize e=0; e<ne; e++)
      F[i]->el[e]->state = Physical;
#else
  project( F );
#endif
}

/// define to include jumps in gradient computation
//#define REO_LINEULER_JUMP

// Need to modify to satisfy the LinEuler_quasi
void LinEuler_quasi::compute_vorticity() {

  cerr << "LinEuler_quasi::compute_vorticity() is not implemented" << endl;
  DGM::Comm::World->exit(DGM::FAILURE);

  Element *S[4], *F[4], *Sm[4];
  dVector r, u, v, p,T, e, E, wk;

#ifdef REO_LINEULER_JUMP
  Up.fill_sides();
  enforce_bc( Up );
  primitive_sides( Up );
  Up.share_sides();
  average_side_flux( U, Ut, '+' );
#endif

  for (LocalSize i=0; i<U[0]->ne; i++) {
    // local version of the state
    S[0] = Up[0]->el[i];
    S[1] = Up[1]->el[i];
    S[2] = Up[2]->el[i];
    S[3] = Up[3]->el[i];

    // local version of the state
    Sm[0] = Um[0]->el[i];
    Sm[1] = Um[1]->el[i];
    Sm[2] = Um[2]->el[i];
    Sm[3] = Um[3]->el[i];

    // local version of the state
    F[0] = Ut[0]->el[i];
    F[1] = Ut[1]->el[i];
    F[2] = Ut[2]->el[i];
    F[3] = Ut[3]->el[i];

    const Ordinal qtot = U[0]->el[i]->qtot;

    r.alias(wk3,0,qtot);        // rho
    u.alias(wk3,qtot,qtot);     // u
    v.alias(wk3,2*qtot,qtot);   // v
    T.alias(wk3,3*qtot,qtot);   // T

    p.alias(wk3,4*qtot,qtot);
    E.alias(wk3,5*qtot,qtot);
    e.alias(wk3,6*qtot,qtot);
    wk.alias(wk3,7*qtot,qtot);

    dvadd(Sm[0]->u,S[0]->u,r); // rho = rho_m + rho'
    dvadd(Sm[1]->u,S[1]->u,u); // u   = u_m   + u'
    dvadd(Sm[2]->u,S[2]->u,v); // v   = v_m   + v'
    dvadd(Sm[3]->u,S[3]->u,T); // T   = T_m   + T'

    // e
    multiply(1.0/(gamma*(gamma-1)),T,e);

    // E
    dvmul(u,u,wk);     // wk = u^2
    dvvtvp(v,v,wk,wk); // wk = u^2 + v^2
    daxpy(0.5,wk,e,E);
    dvmul(r,E);

    // p = (gamma-1.0)*(E-0.5*(r*u*u + r*v*v))
    dvmul(r, e, p);
    scale(gamma-1.0,p);

#ifdef REO_LINEULER_JUMP
    dVector ux(qtot);
    dVector uy(qtot);
    dVector vx(qtot);
    dVector vy(qtot);

    gradient( S[1], F[1], u, ux, uy );
    gradient( S[2], F[2], v, vx, vy );

    // vorticity:   F[0]
    scale(-1.0, uy);
    dvadd(vx, uy, F[0]->u);

    // divergence:  F[1]
    dvadd(ux, vy, F[1]->u);
#else
    // vorticity:   F[0]
    F[0]->gradient(u, F[0]->u, 'y');
    F[1]->gradient(v, F[1]->u, 'x');
    scale(-1.0,F[0]->u);
    dvadd(F[1]->u, F[0]->u);

    // divergence:  F[1]
    F[1]->gradient(u, F[1]->u, 'x');
    F[2]->gradient(v, F[2]->u, 'y');
    dvadd(F[2]->u,F[1]->u);
#endif
    F[2]->fill(p);
    F[3]->fill(e);
  }
}


void LinEuler_quasi::set_mean(vField &Fm, const char c) {
  string fname = root+".mean";
  ifstream in(fname.c_str());
  if (in) {
    string buffer, code;
    getline(in,buffer);
    if (!(in>>code)) error("Cannot read mean flow",1);
    getline(in,buffer);
    if (lowerCase(code) == "file") {
      string meanfile;
      if (!(in>>meanfile)) {
        cerr << "Cannot read mean flow  file name from " << fname << endl;
        comm->exit(DGM::FAILURE);
      }
      read(meanfile, Fm,SKIP_HEADER);
      if (comm->Master()) cout<< "Mean flow  from: " << meanfile << endl;

      if(c=='p'){
      //transform the mean flow field to primitive (rho,u,v,T)
        for (LocalSize k=0; k<Fm[0]->ne; k++) {
          dVector wk;
          wk.alias(wk3,0,Fm[0]->el[k]->qtot);  // WARNING: new memory
          dVector  r(Fm[0]->el[k]->u);     // rho
          dVector  u(Fm[1]->el[k]->u);     // rho u
          dVector  v(Fm[2]->el[k]->u);     // rho v
          dVector  T(Fm[3]->el[k]->u);     // total energy per volume
          dvdiv(u, r, u);       // u-velocity
          dvdiv(v, r, v);       // v-velocity
          dvdiv(T, r, T);       // internal energy + 0.5 |V|^2
          dvmul(u, u, wk);      // wk = u^2
          dvvtvp(v, v, wk, wk); // wk = u^2 + v^2
          daxpy(-0.5, wk, T);   // e  = e - 0.5 * wk = internal energy
          scale(gamma*(gamma-1.0),T);//T
        }
      }
    }
  }else {
    cout<<"set_mean: can't find mean flow file,"
        <<"using the no mean flow instead"<<endl;
    //Assume Ma = 0.3
    Scalar Ma = 0.3;
    if(c=='p'){
      //test for the zero mean flow
      for (LocalSize e=0; e<ne; e++) {
        for (LocalSize q=0; q<Fm[0]->el[e]->qtot; q++) {
          Fm[0]->el[e]->u[q] = 1.0;
          Fm[1]->el[e]->u[q] = 0.0;
          Fm[2]->el[e]->u[q] = 0.0;
          Fm[3]->el[e]->u[q] = 1.0/Ma/Ma; //Warning: rescale it [gqchen]
        }
      }
    }
  }

  project(Fm);
}


void LinEuler_quasi::make_U(const vField &Fm, const vField &Fp, vField &F) {

  Scalar rho,T,u[2],w[4];

  for (LocalSize e=0; e<ne; e++) {
    for (LocalSize q=0; q<F[0]->el[e]->qtot; q++) {
      for(vField::size_type i=0;i<Nfields;i++) w[i]=Fp[i]->el[e]->u[q];
      rho = Fm[0]->el[e]->u[q];
      u[0]= Fm[1]->el[e]->u[q];
      u[1]= Fm[2]->el[e]->u[q];
      T =   Fm[3]->el[e]->u[q];

      F[0]->el[e]->u[q] = w[0];
      F[1]->el[e]->u[q] = u[0]*w[0]+rho*w[1];
      F[2]->el[e]->u[q] = u[1]*w[0]+rho*w[2];
      F[3]->el[e]->u[q] = (T/gamma/(gamma-1.0) + u[0]*u[0]/2.0 + u[1]*u[1]/2.0)
        *w[0]  + rho*u[0]*w[1] +rho*u[1]*w[2] + rho/gamma/(gamma-1.0)*w[3];
    }
  }

#if 0
  cout << "WARNING:  No projection of Initial condition" << endl;
  for (LocalSize i=0; i<Nfields; i++)
    for (LocalSize e=0; e<ne; e++)
      F[i]->el[e]->state = Physical;
#else
  // project fields to the polynomial space just to make sure
  project(F);
#endif
}

void LinEuler_quasi::get_Up(const vField &Fm, const vField &F,vField &Fp) {
  Scalar rho,T,u[2],w[4];
  for (LocalSize e=0; e<ne; e++) {
    for (LocalSize q=0; q<F[0]->el[e]->qtot; q++) {
      for(vField::size_type i=0;i<Nfields;i++) w[i]=F[i]->el[e]->u[q];
      rho = Fm[0]->el[e]->u[q];
      u[0]= Fm[1]->el[e]->u[q];
      u[1]= Fm[2]->el[e]->u[q];
      T =   Fm[3]->el[e]->u[q];

      Fp[0]->el[e]->u[q] = w[0];
      Fp[1]->el[e]->u[q] = -u[0]/rho*w[0]+1/rho*w[1];
      Fp[2]->el[e]->u[q] = -u[1]/rho*w[0]+1/rho*w[2];
      Fp[3]->el[e]->u[q] = 1/rho*(u[0]*u[0]*gamma*gamma- u[0]*u[0]*gamma
                                  +u[1]*u[1]*gamma*gamma-u[1]*u[1]*gamma
                                  -2.0*T)
        * w[0]/2.0-1/rho*u[0]*gamma*(gamma-1.0)*w[1]
        - 1/rho*u[1]*gamma*(gamma-1.0)*w[2]
        +1/rho*gamma*(gamma-1.0)*w[3];
    }
  }
#if 0
  cout << "WARNING:  No projection of Initial condition" << endl;
  for (LocalSize i=0; i<Nfields; i++)
    for (LocalSize e=0; e<ne; e++)
      Fp[i]->el[e]->state = Physical;
#else
  // project fields to the polynomial space just to make sure
  project(Fp);
#endif
}

void LinEuler_quasi::enforce_mean_state_bc(vField &S) {
  dVector us[4];
  dVector ub[4];
  for (LocalSize n=0; n<S[0]->nbc; n++) {
    const LocalSize sid = S[0]->bc[n]->sid;
    const LocalSize qtot = S[0]->bc[n]->elmt->side[sid]->qtot();
    dVector &nx = S[0]->bc[n]->elmt->side[sid]->nx();
    dVector &ny = S[0]->bc[n]->elmt->side[sid]->ny();
    if (S[0]->bc[n]->type[0]=='W') {
      for (vField::size_type i=0; i<Nfields; i++) {
        us[i].alias( S[i]->bc[n]->elmt->side[sid]->u );
        ub[i].alias( S[i]->bc[n]->elmt->side[sid]->link->u );
      }
      for (LocalSize i=0; i<qtot; i++) {
        ub[0][i] =  us[0][i];
        ub[1][i] =  (us[1][i]*ny[i] - us[2][i]*nx[i])*ny[i];
        ub[2][i] =  (us[2][i]*nx[i] - us[1][i]*ny[i])*nx[i];
        ub[3][i] =  us[3][i];
      }
    } else {
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
    }
  }
}

//===========================================================================
//                        BC database management
//===========================================================================

// Load up the available BC types
void LinEuler_quasi::setup_BCdb( ) {
  // cout << "LinEuler_quasi::setup_BCdb()" << endl;

  // set default BC types
  dVector ub(4);
  // zero fluctuation
  ub[0] = 0.0;
  ub[1] = 0.0;
  ub[2] = 0.0;
  ub[3] = 0.0;
  BC_db["S"].reset( new LinStateBC("S", ub) );
  BC_db["W"].reset( new LinWallBC("W") );

  // read new BC types from file
  string fname = root+".bct";
  ifstream in(fname.c_str());
  if (in) LinEuler_quasi::read_BCdb( in );   // database of active BC types
}

void LinEuler_quasi::read_BCdb( ifstream &in ) {
  //  cout << "LinEuler_quasi::read_BCdb( ifstream &in )" << endl;
  string tag;
  BC *pbc;
  while ( (pbc = LinEuler_quasi::make_BC(in,tag)) ) {
    if ( BC_db.find(tag) != BC_db.end() )
      cerr << "WARNING in LinEuler_quasi::read_BCdb:  Overriding BC type \""
           << tag << "\"." << endl;
    BC_db[tag].reset( pbc );
  }
}

BC* LinEuler_quasi::make_BC ( ifstream &in, string &tag) {
  //  cout << "LinEuler_quasi::make_BC(ifstream &in, string &tag)" << endl;
  string code;
  if (!(in>>code)) return NULL;
  code = lowerCase(code);
  if (code=="state") {
    if (!(in>>tag)) error("LinEuler_quasi::make_BC:  Cannot read State tag",1);
    return new LinStateBC(tag,in,4);
  } else if (code=="wall") {
    if (!(in>>tag))
      error("LinEuler_quasi::make_BC:  Cannot read Wall tag",1);
    return new LinWallBC(tag,in,gamma);
#if 0
  } else if (code=="wave_state") { // for acoustic scattering
    if (!(in>>tag))
      error("LinEuler_quasi::make_BC:  Cannot read Wall tag",1);
    return new Wave_StateBC(tag,in);
#endif
  } else {
    error("LinEuler_quasi::make_BC:  Illegal BC type:  "+code,1);
  }
  return NULL;
}

void LinEuler_quasi::enforce_bc(vField &F) {
  // cout << "LinEuler_quasi::enforce_bc(vField &F) "<< lstep << endl;
  // for (BC::db_citr i=BC_db.begin(); i!= BC_db.end(); ++i)
  //   i->second->apply( t, F );
}

void LinEuler_quasi::enforce_flux_bc(vField &S) {
  // cout << "LinEuler_quasi::enforce_flux_bc(vField &U)" << endl;
}

#ifdef WAVE_SCATTER

void LinEuler_quasi::enforce_bc(vField &S) {

  // Here we only consider the zero mean flow, so the quasi-variable the first
  // three are same as the primitive ones, refer to the Jacobi matrix from
  // mean flow so for wall normal B.C, its implementation is similar to the
  // conservative form

  // For inflow B.C, since fluctuation there are all zero, so we set them all
  // zero, it should be O.K.

  Scalar rho, u[2], T, rhop, up, vp, Tp, w[4];
  Scalar tmp1;
  dVector um[4];
  dVector us[4];
  dVector ub[4];
  for (LocalSize n=0; n<S[0]->nbc; n++) {
    int sid = S[0]->bc[n]->sid;
    int qtot = S[0]->bc[n]->elmt->side[sid]->qtot;
    dVector &nx = S[0]->bc[n]->elmt->side[sid]->nx();
    dVector &ny = S[0]->bc[n]->elmt->side[sid]->ny();
    if (S[0]->bc[n]->type=="W") {
      for (LocalSize i=0; i<Nfields; i++) {
        um[i].alias( Um[i]->bc[n]->elmt->side[sid]->u );
        us[i].alias( S[i]->bc[n]->elmt->side[sid]->u );
        ub[i].alias( S[i]->bc[n]->elmt->side[sid]->link->u );

      }
      for (int i=0; i<qtot; i++) {
        for(int m=0;m<4;m++) w[m] = us[m][i];
        rho =  um[0][i];
        u[0] = um[1][i];
        u[1] = um[2][i];
        T = um[3][i];
        // Get Up
        rhop = w[0];
        up = -u[0]/rho*w[0]+1/rho*w[1];
        vp = -u[1]/rho*w[0]+1/rho*w[2];
        Tp = 1/rho*(u[0]*u[0]*gamma*gamma - u[0]*u[0]*gamma
                    + u[1]*u[1]*gamma*gamma- u[1]*u[1]*gamma-2.0*T)*w[0]/2.0
          -1/rho*u[0]*gamma*(gamma-1.0)*w[1]
          - 1/rho*u[1]*gamma*(gamma-1.0)*w[2]+1/rho*gamma*(gamma-1.0)*w[3];

        // Form the new Up
        rhop = rhop;
        tmp1 = (up*ny[i] - vp*nx[i])*ny[i];
        vp = (vp*nx[i] - up*ny[i])*nx[i];
        up = tmp1;
        Tp = Tp;

        w[0] = rhop; w[1] = up; w[2]=vp; w[3]=Tp;
        // For Quasi U = M*Up
        ub[0][i] = w[0];
        ub[1][i] = u[0]*w[0]+rho*w[1];
        ub[2][i] = u[1]*w[0]+rho*w[2];
        ub[3][i] = (T/gamma/(gamma-1.0)+u[0]*u[0]/2.0
                    + u[1]*u[1]/2.0)*w[0] + rho*u[0]*w[1]+rho*u[1]*w[2]
          +rho/gamma/(gamma-1.0)*w[3];
      }
    } else {
      for (LocalSize i=0; i<Nfields; i++) {
        um[i].alias( Um[i]->bc[n]->elmt->side[sid]->u );
        us[i].alias( S[i]->bc[n]->elmt->side[sid]->u );
        ub[i].alias( S[i]->bc[n]->elmt->side[sid]->link->u );
      }

      Scalar Ma=0.3;
      Scalar amp = 0.02;
      Scalar k = 2.5; // wave number
      Scalar mC = 1.0/Ma; Scalar c = mC;

      Scalar rhom = 0.5*amp/mC/mC;
      Scalar Um = amp*0.5/mC/1.0;
      Scalar vm = 0;
      Scalar Tm = amp*(gamma*Ma*Ma*0.5 - 1.0 *0.5/mC/mC)/1.0/Ma/Ma;

      Point *pside = new Point[S[0]->bc[n]->elmt->side[sid]->qtot];
      S[0]->bc[n]->elmt->get_side_coordinates(sid, pside);

      for (int i=0; i<qtot; i++) {
        Scalar x = pside[i].x;

        w[0] = rhom*sin(k*(x-0-c*t)); // rho
        w[1] = Um*sin(k*(x-0-c*t));   // u
        w[2] = vm*sin(k*(x-0-c*t));   // v
        w[3] = Tm*sin(k*(x-0-c*t));   // T

        // transform to the quasi-variable
        rho    = um[0][i];
        u[0]   = um[1][i];
        u[1]   = um[2][i];
        T      = um[3][i];

        // form the quasi_variable
        ub[0][i] = w[0];
        ub[1][i] = u[0]*w[0]+rho*w[1];
        ub[2][i] = u[1]*w[0]+rho*w[2];
        ub[3][i] = (T/gamma/(gamma-1.0)+u[0]*u[0]/2.0
                    + u[1]*u[1]/2.0)*w[0] + rho*u[0]*w[1]
          + rho*u[1]*w[2] + rho/gamma/(gamma-1.0)*w[3];
      }
      delete[] pside;
    }
  }
}

void LinEuler_quasi::enforce_flux_bc(vField &S) {
  // cout << "LinEuler_quasi::enforce_flux_bc(vField &U)" << endl;
}

void LinEuler_quasi::set_sponge(vField &Us,vField &Ur) {

  Element *S[4],*Sm[4],*R[4];
  int qtot;
  Scalar uquasi[4],w[4],rho,u[2],T;
  Point cxy;

  Scalar taus=0;
  Scalar As=100.0;
  int N=3;

  // For sponge function implementation
  Scalar Ma = 0.3;
  Scalar x0 =0;
  Scalar amp = 0.02;
  Scalar k = 2.5; // wave number
  Scalar mC = 1.0/Ma; Scalar c = mC;

  Scalar rhom = 0.5*amp/mC/mC;
  Scalar um = amp*0.5/mC/1.0;
  Scalar vm = 0;
  Scalar Tm = amp*(gamma*Ma*Ma*0.5 - 1.0 *0.5/mC/mC)/1.0/Ma/Ma;

  for (LocalSize e=0; e<Us[0]->ne; e++) {

    S[0] = Us[0]->el[e];  // local version of the state
    S[1] = Us[1]->el[e];
    S[2] = Us[2]->el[e];
    S[3] = Us[3]->el[e];

    R[0] = Ur[0]->el[e];  // local version of the state
    R[1] = Ur[1]->el[e];
    R[2] = Ur[2]->el[e];
    R[3] = Ur[3]->el[e];

    Sm[0] = Um[0]->el[e];  // local version of the state --mean(base) flow
    Sm[1] = Um[1]->el[e];
    Sm[2] = Um[2]->el[e];
    Sm[3] = Um[3]->el[e];

    qtot = S[0]->qtot;

    for(int q=0;q<qtot;q++){
      cxy = Point(S[0]->C->x[q],S[0]->C->y[q]);

      if(!(cxy.x>(-20)&&cxy.x<20&&cxy.y>(-20)&&cxy.y<20)){
        // add sponge
        // Construct the Uref
        w[0] = rhom*sin(k*(cxy.x-0-c*t)); //rho
        w[1] = um*sin(k*(cxy.x-0-c*t)); //u
        w[2] = vm*sin(k*(cxy.x-0-c*t)); //v
        w[3] = Tm*sin(k*(cxy.x-0-c*t)); //T

        // transform to the quasi-variable
        rho  = Sm[0]->u[q];
        u[0] = Sm[1]->u[q];
        u[1] = Sm[2]->u[q];
        T    = Sm[3]->u[q];

        // form the quasi_variable
        uquasi[0] = w[0];
        uquasi[1] = u[0]*w[0]+rho*w[1];
        uquasi[2] = u[1]*w[0]+rho*w[2];
        uquasi[3] = (T/gamma/(gamma-1.0)+u[0]*u[0]/2.0+
                     u[1]*u[1]/2.0)*w[0]+
          rho*u[0]*w[1]+rho*u[1]*w[2]+rho/gamma/(gamma-1.0)*w[3];

        // get taus
        if(cxy.x>=(-30)&&cxy.x<=(-20))
          taus = As*pow(fabs(20.+cxy.x)/10.,N);
        else if(cxy.x>=20&&cxy.x<=30)
          taus = As*pow(fabs(cxy.x-20.0)/10.,N);

        R[0]->u[q]=R[0]->u[q] + taus*(S[0]->u[q]-uquasi[0]);
        R[1]->u[q]=R[1]->u[q] + taus*(S[1]->u[q]-uquasi[1]);
        R[2]->u[q]=R[2]->u[q] + taus*(S[2]->u[q]-uquasi[2]);
        R[3]->u[q]=R[3]->u[q] + taus*(S[3]->u[q]-uquasi[3]);

        taus = 0.0;

        if(cxy.y>=(-30)&&cxy.y<=(-20))
          taus = As*pow(fabs(cxy.y+20.)/10.0,N);
        else if(cxy.y>=20&&cxy.y<=30)
          taus = As*pow(fabs(cxy.y-20.0)/10.0,N);

        R[0]->u[q]=R[0]->u[q] + taus*(S[0]->u[q]-uquasi[0]);
        R[1]->u[q]=R[1]->u[q] + taus*(S[1]->u[q]-uquasi[1]);
        R[2]->u[q]=R[2]->u[q] + taus*(S[2]->u[q]-uquasi[2]);
        R[3]->u[q]=R[3]->u[q] + taus*(S[3]->u[q]-uquasi[3]);

      }
    }
  }
}

#endif  // WAVE_SCATTER

} // namespace Reo
