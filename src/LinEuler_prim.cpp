/*=============================================================================
  Module:     LinEuler_prim Module

  Author:     Guoquan Chen & S. Scott Collis

  Copyright:  S. Scott Collis
              Department of Mechanical Engineering and Materials Science
              Rice University, MS 321
              Houston, TX 77005-1892
              (713) 348-3617
              collis@rice.edu
=============================================================================*/

/** \file  LinEuler_prim.cpp
    \brief Linearized Euler equations in primative variables
    \author Guoquan Chen
    \author Scott Collis
*/

#include "LinEuler_prim.hpp"

#include "Wavetype.hpp"

namespace Reo {

//#define VERBOSE_FLUX

/// Constructor
LinEuler_prim::LinEuler_prim(DGM::ArgList &args, const DGM::Comm::Ptr comm_) :
  Euler(args,comm_), Utmp(comm_), Um(comm_) {

  Ma = 0.3;  // Reference Ma number (Why is this 0.3???) [SSC]

  // Print a warning since these values are hardwired
  comm->cout()<<"[LinEuler_prim] WARNING:  \n  Using Ma="<<Ma<<std::endl;

  // make the mean flow Field
  for (vField::size_type i=0; i<Nfields; i++) {
    Um.push_back( new Field( U[0], root,U[i]->name) );
    Utmp.push_back( new Field( U[0], root,U[i]->name));
  }

#ifdef REO_USE_GETSIDEMAPS
  setup_side_maps();
#endif

  // allocate workspace -- increase the workspace -- cgq
  wk3.resize(10*max(Lmax(),Qmax()));
  wk4.resize(10*max(Lmax(),Qmax()));

  // make sure that storage is initialized
  zero_all_fields();
}

void LinEuler_prim::zero_all_fields() {
  Domain::zero_all_fields();
  Um.zero();
  Utmp.zero();
}

void LinEuler_prim::time_derivative( vField &Us, vField &Uf ) {
  convection(Us, Uf);
  meansource(Us,Utmp,Uf); // here Ut acts as the temporary vField
  // set_sponge(Us,Uf);
  project( Uf );
}

/*! \todo Overlap interior computation with communication */
void LinEuler_prim::convection(vField &Us, vField &Uf) {
  Element *U[4], *F[4], *Fm[4];
  dVector u1, u2, u3, Fx1, Fx2, Fx3, Fx4, Fy1, Fy2, Fy3, Fy4, d;
  Scalar w[4], u[2], rho, p;

  Us.fill_sides();
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

    // For simple case, the mean flow is uniform flow,
    // Since A(au),B(au) constant matrix
    // we can get F(u(x)),x = A(au) u,x
    //            G(u(x)),y = B(au) u,y
    // In future, if the mean flow has the spatial distribution, we should
    //     Set    F(u(x)),x = (A(au) u),x
    //            G(u(x)),y = (B(au) u),y
    for (LocalSize q=0; q<qtot; q++) {
      for(vField::size_type i=0;i<Nfields;i++) w[i]=U[i]->u[q];
      rho = Fm[0]->u[q];
      u[0]= Fm[2]->u[q];
      u[1]= Fm[3]->u[q];
      p =  Fm[1]->u[q];

      Fx1[q] = u[0]*w[0]+rho*w[2];
      Fx2[q] = u[0]*w[1]+p*gamma*w[2];
      Fx3[q] = (w[1]+u[0]*w[2]*rho)/rho;
      Fx4[q] = u[0]*w[3];

      Fy1[q] = u[1]*w[0]+rho*w[3];
      Fy2[q] = u[1]*w[1]+p*gamma*w[3];
      Fy3[q] = u[1]*w[2];
      Fy4[q] = (w[1]+u[1]*w[3]*rho)/rho;
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

    for (vField::size_type i=0; i<Nfields; i++)
      U[i]->lift( F[i], F[i]->u );
  }
}

/*! For descriptions of the numerical fluxes
    See:  E.F. Toro, "Riemann Solvers and Numerical Methods for Fluid
          Dynamics," 2nd Edition, Springer, 1999. */
void LinEuler_prim::convective_flux(vField &Us, vField &Uf) {
  flux_type flux = LaxFriedrichs; //StegerWarming; //vanLeer;
  dVector sl(Nfields), sr(Nfields), f(Nfields);
  dVector bl(Nfields), br(Nfields);
  Scalar ulm, clm;
  Scalar urm, crm;
  vector<Side *> Ssl(Nfields), Ssr(Nfields);
  vector<Side *> Sbl(Nfields), Sbr(Nfields);    // base flow field edge
  vector<Side *> Sfl(Nfields), Sfr(Nfields);
  dVector fpl(Nfields), fmr(Nfields), lam(Nfields);
  Scalar lmax;
  Scalar w[4],u[2],rho,p;
#ifdef REO_USE_GETSIDEMAPS
  iVector mapl, mapr;
#endif
  dVector Fx(Nfields), Fy(Nfields);

  for (LocalSize e=0; e<Us[0]->ne; e++) {                 // loop over elements
    Element* U = Us[0]->el[e];
    for (LocalSize i=0; i<Us[0]->el[e]->nSides(); i++) {  // loop over edges
      if (Us[0]->el[e]->side[i]->master()) {              // compute if master
        const LocalSize qtot = Us[0]->el[e]->side[i]->qtot(); // side quad pts
        for (vField::size_type ni=0; ni<Nfields; ni++) {
          Ssl[ni] = Us[ni]->el[e]->side[i];          // left state edge
          Ssr[ni] = Us[ni]->el[e]->side[i]->link;    // right state edge
          Sfl[ni] = Uf[ni]->el[e]->side[i];          // left flux edge
          Sfr[ni] = Uf[ni]->el[e]->side[i]->link;    // right flux edge
          Sbl[ni] = Um[ni]->el[e]->side[i];          // left base edge
          Sbr[ni] = Um[ni]->el[e]->side[i]->link;    // right base edge
        }
#ifdef REO_USE_GETSIDEMAPS
        get_side_maps(Ssl[0],Ssr[0],mapl,mapr);
#endif

        for (LocalSize q=0; q<qtot; q++) {           // loop over edge quad-pts

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

          // normal velocity -- mean flow
          ulm = Sbl[2]->u[ql]*nx +Sbl[3]->u[ql]*ny;
          // ul = Ssl[2]->u[ql]*nx +Ssl[3]->u[ql]*ny;

          for(vField::size_type k=0;k<Nfields;k++) w[k]=Ssl[k]->u[ql];
          rho = Sbl[0]->u[ql];
          p   = Sbl[1]->u[ql];
          u[0]= Sbl[2]->u[ql];
          u[1]= Sbl[3]->u[ql];

          Fx[0] = u[0]*w[0]+rho*w[2];
          Fx[1] = u[0]*w[1]+p*gamma*w[2];
          Fx[2] = (w[1]+u[0]*w[2]*rho)/rho;
          Fx[3] = u[0]*w[3];

          Fy[0] = u[1]*w[0]+rho*w[3];
          Fy[1] = u[1]*w[1]+p*gamma*w[3];
          Fy[2] = u[1]*w[2];
          Fy[3] = (w[1]+u[1]*w[3]*rho)/rho;

          Ssl[0]->u[ql] = Fx[0]*nx + Fy[0]*ny;
          Ssl[1]->u[ql] = Fx[1]*nx + Fy[1]*ny;
          Ssl[2]->u[ql] = Fx[2]*nx + Fy[2]*ny;
          Ssl[3]->u[ql] = Fx[3]*nx + Fy[3]*ny;

          // compute normal flux from exterior (right)

          // adjacent state (Primitive form)
          for(vField::size_type k=0;k<Nfields;k++)
            sr[k] = Ssr[k]->u[qr];

          urm = Sbr[2]->u[qr]*nx +Sbr[3]->u[qr]*ny;
          // ur = Ssr[2]->u[qr]*nx +Ssr[3]->u[qr]*ny;

          // put the adjacent flux on the state edges
          for(vField::size_type k=0;k<Nfields;k++) w[k]=Ssr[k]->u[qr];
          rho = Sbr[0]->u[qr];
          p =  Sbr[1]->u[qr];
          u[0]= Sbr[2]->u[qr];
          u[1]= Sbr[3]->u[qr];

          Fx[0] = u[0]*w[0]+rho*w[2];
          Fx[1] = u[0]*w[1]+p*gamma*w[2];
          Fx[2] = (w[1]+u[0]*w[2]*rho)/rho;
          Fx[3] = u[0]*w[3];

          Fy[0] = u[1]*w[0]+rho*w[3];
          Fy[1] = u[1]*w[1]+p*gamma*w[3];
          Fy[2] = u[1]*w[2];
          Fy[3] = (w[1]+u[1]*w[3]*rho)/rho;

          Ssr[0]->u[qr] = Fx[0]*nx + Fy[0]*ny;
          Ssr[1]->u[qr] = Fx[1]*nx + Fy[1]*ny;
          Ssr[2]->u[qr] = Fx[2]*nx + Fy[2]*ny;
          Ssr[3]->u[qr] = Fx[3]*nx + Fy[3]*ny;

          // Local sound speed from mean flow

          switch (flux) {
          case LaxFriedrichs:
            lmax = zero;
            clm = sqrt(gamma*Sbl[1]->u[ql]/Sbl[0]->u[ql]);
            lam[0] = ulm;
            lam[1] = ulm+clm;
            lam[2] = ulm-clm;
            lam[3] = ulm;

            // left flux
            for(vField::size_type j=0; j<Nfields;j++) {
              lmax = max(lmax,fabs(lam[j]));
              fpl[j] = Ssl[j]->u[ql];
            }

            crm = sqrt(gamma*Sbr[1]->u[qr]/Sbr[0]->u[qr]);
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
            f[0] = pt5 * ( fpl[0] + fmr[0] + lmax * ( sl[0] - sr[0] ) );
            f[1] = pt5 * ( fpl[1] + fmr[1] + lmax * ( sl[1] - sr[1] ) );
            f[2] = pt5 * ( fpl[2] + fmr[2] + lmax * ( sl[2] - sr[2] ) );
            f[3] = pt5 * ( fpl[3] + fmr[3] + lmax * ( sl[3] - sr[3] ) );
#ifdef VERBOSE_FLUX
            cout << "Lax-Friedrichs: Element " << e << ", Edge " << i << endl;
            cout << f[0] << ", "
                 << f[1] << ", "
                 << f[3] << endl;
            << f[3] << endl;
#endif
            break;
          default:
            cerr << "Illegal value of flux type" << endl;
            DGM::Comm::World->exit(DGM::FAILURE);
          }

          // put fluxes on flux field edges
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

// set a vector field from a file
void LinEuler_prim::set_ic(vField &F, string ext) {
  set_mean(Um);
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
  } else if (lowerCase(code) == "wave" ) {
    // Initialization for the plane LinEuler_prim
    // 1d acoustics
    // AcousticWave(Scalar R_e,Scalar M_a,Scalar P_r,Scalar am_p,Scalar
    //              x_0,Scalar sigm_a,char c ='x',char d='p',int wavetyp_e=1)
    // Scalar k = 2.5;
    // AcousticWave pw(50.,0.3,1.0,0.02,0.0,0.7,'x','p',2);

    // 2d acoustics
    Scalar x0, y0, xn, yn;
    x0 = 2.0; y0 = 2.0; xn = 1.0; yn = 1.0;
    AcousticWave pw( 0.3, 1.0, gamma, 0.005, x0, y0, 0.2, 'p',
                     AcousticWave::Cylindrical, 1.2, xn, yn);
    for (LocalSize e=0; e<ne; e++) {
      for (LocalSize q=0; q<F[0]->el[e]->qtot; q++) {
        F[0]->el[e]->u[q] = pw.R(Point(F[3]->el[e]->C->x[q],
                                       F[3]->el[e]->C->y[q]));
        //   *sin(k*(F[0]->el[e]->C->x[q]-0));
        F[2]->el[e]->u[q] = pw.U(Point(F[3]->el[e]->C->x[q],
                                       F[3]->el[e]->C->y[q] ));
        //   *sin(k*(F[0]->el[e]->C->x[q]-0));
        F[3]->el[e]->u[q] = pw.V(Point(F[3]->el[e]->C->x[q],
                                       F[3]->el[e]->C->y[q]));
        //        *sin(k*(F[0]->el[e]->C->x[q]-0));
        F[1]->el[e]->u[q] = pw.R( Point(F[3]->el[e]->C->x[q],
                                        F[3]->el[e]->C->y[q] ));
        //   *sin(k*(F[0]->el[e]->C->x[q]-0))*(1.0/Ma)*(1.0/Ma); // p
      }
    }
  } else {
    comm->error("LinEuler_prim::set_ic()  Unsupported IC type");
  }
#ifdef DGM_NO_PROJECT_IC
  cout << "WARNING:  No projection of Initial condition" << endl;
  for (LocalSize i=0; i<Nfields; i++)
    for (LocalSize e=0; e<ne; e++)
      F[i]->el[e]->state = Physical;
#else
  // project fields to the polynomial space just to make sure
  F.project();
#endif
}

void LinEuler_prim::meansource(vField &Us,vField &Uf,vField &Ur) {
  Element *S[4], *F[4], *Sm[4];
  //dVector u, v, p, e, wk;

  Us.fill_sides();                   // put solution on the edges
  enforce_bc(Us);              // update bc edge values

  // Steady mean flow, so unnecessary
  // Um.fill_edges();                // put mean flow on the edges
  // enforce_mean_state_bc(Um);      // update mean bc edge values

  Us.share_sides();                  // communicate edges if parallel
  average_flux( Us, Uf, '+' );       // Uf's edges are average state

  for (LocalSize k=0; k<Us[0]->ne; k++) {

    S[0] = Us[0]->el[k];  // local version of the state
    S[1] = Us[1]->el[k];
    S[2] = Us[2]->el[k];
    S[3] = Us[3]->el[k];

    Sm[0] = Um[0]->el[k];  // local version of the mean flow
    Sm[1] = Um[1]->el[k];
    Sm[2] = Um[2]->el[k];
    Sm[3] = Um[3]->el[k];

    F[0] = Uf[0]->el[k];  // local version of the flux
    F[1] = Uf[1]->el[k];
    F[2] = Uf[2]->el[k];
    F[3] = Uf[3]->el[k];

    dVector rho(S[0]->u);  // rho
    dVector p(S[1]->u);    //  p
    dVector u(S[2]->u);    //  u
    dVector v(S[3]->u);    // v

    dVector rhom(Sm[0]->u);  // rhom
    dVector pm(Sm[1]->u);    //  pm
    dVector um(Sm[2]->u);    //  um
    dVector vm(Sm[3]->u);    // vm

    const Ordinal qtot = S[0]->qtot;
    dVector um_x(qtot);
    dVector um_y(qtot);
    dVector vm_x(qtot);
    dVector vm_y(qtot);
    dVector rhom_x(qtot);
    dVector rhom_y(qtot);
    dVector pm_x(qtot);
    dVector pm_y(qtot);
    dVector tmp1(qtot),tmp2(qtot),tmp3(qtot);

    Sm[0]->gradient(rhom, rhom_x, rhom_y);
    Sm[1]->gradient(pm, pm_x, pm_y);
    Sm[2]->gradient(um, um_x, um_y);
    Sm[3]->gradient(vm, vm_x, vm_y);

    //      gradient( Sm[1], F[1], pm, pm_x, pm_y );
    //      gradient( Sm[2], F[2], um, um_x, um_y );
    //      gradient( Sm[3], F[3], vm, vm_x, vm_y );

    // (1-gamma)*(Um_x+Vm_y)*P
    dvadd(um_x,vm_y,tmp1);
    scale(1.0-gamma,tmp1);
    dvmul(p,tmp1);
    // (gamma-1)*Pm_x*U
    dvmul(pm_x,u,tmp2);
    scale(gamma-1.0,tmp2);
    //(1-gamma)*(Um_x+Vm_y)*P +(gamma-1)*Pm_x*U
    dvadd(tmp1,tmp2,tmp3);
    // (gamma-1)*Pm_y*V
    dvmul(pm_y,v,tmp1);
    scale(gamma-1.0,tmp1);
    // F[1]=(1-gamma)*(Um_x+Vm_y)*P + (gamma-1)*Pm_x*U + (gamma-1)*Pm_y*V
    dvadd( tmp1, tmp3,F[1]->u);

    //-(Um*Um_x+Vm*Um_y)/Rhom*Rho
    dvmul(um,um_x,tmp1);
    dvmul(vm,um_y,tmp2);
    dvadd(tmp1,tmp2,tmp3);
    dvdiv(tmp3,rhom,tmp2);
    dvmul(tmp2,rho,tmp1);
    scale(-1.0,tmp1);
    //(1/Rhom)_x*P
    dvdiv(rhom_x,rhom,tmp2);
    dvdiv(tmp2,rhom,tmp3);
    dvmul(p,tmp3,tmp2);
    scale(-1.0,tmp2);
    //-(Um*Um_x+Vm*Um_y)/Rhom*Rho + 1/Rhom_x*P
    dvadd(tmp1,tmp2,tmp3);
    //Vm_y*U
    dvmul(vm_y,u,tmp1);
    //-(Um*Um_x+Vm*Um_y)/Rhom*Rho + 1/Rhom_x*P + Vm_y*U
    dvadd(tmp1,tmp3,tmp2);
    //-Um_y*V
    dvmul(um_y,v,tmp1);
    scale(-1.0,tmp1);
    //F[2]=-(Um*Um_x+Vm*Um_y)/Rhom*Rho + 1/Rhom_x*P + Vm_y*U-Um_y*V
    dvadd(tmp2,tmp1,F[2]->u);

    //-(Um*Vm_x+Vm*Vm_y)/Rhom*Rho
    dvmul(um,vm_x,tmp1);
    dvmul(vm,vm_y,tmp2);
    dvadd(tmp1,tmp2,tmp3);
    dvdiv(tmp3,rhom,tmp2);
    dvmul(tmp2,rho,tmp1);
    scale(-1.0,tmp1);
    //(1/Rhom)_y*P
    dvdiv(rhom_y,rhom,tmp2);
    dvdiv(tmp2,rhom,tmp3);
    dvmul(p,tmp3,tmp2);
    scale(-1.0,tmp2);
    //-(Um*Vm_x+Vm*Vm_y)/Rhom*Rho + 1/Rhom_y*P
    dvadd(tmp1,tmp2,tmp3);
    //-Vm_x*U
    dvmul(vm_x,u,tmp1);
    scale(-1.0,tmp1);
    //-(Um*Um_x+Vm*Um_y)/Rhom*Rho + (1/Rhom)_x*P + Vm_y*U
    dvadd(tmp1,tmp3,tmp2);
    //Um_x*V
    dvmul(um_x,v,tmp1);
    //F[2]=-(Um*Vm_x+Vm*Vm_y)/Rhom*Rho + 1/Rhom_y*P - Vm_x*U+Um_x*V
    dvadd(tmp2,tmp1,F[3]->u);
  }

  Us.share_sides();                        // Share edges with your neighbors
  enforce_flux_bc(Us);                     // put flux BC's on bc edges
  average_flux( Us, Uf, '+' );

  // Note there is no contribution to the continuity equation
  for (vField::size_type n=1; n<Us.size(); n++) {
    for (LocalSize k=0; k<Us[n]->ne; k++) {
      S[k] = Us[n]->el[k];
      F[k] = Uf[n]->el[k];
      S[k]->lift( F[k], F[k]->u );
    }
  }

  // add in mean flow  contribution
  scale(-one,Uf);  // I currrently put everything on the LHS
  for (vField::size_type n=1; n<Uf.size(); n++) add( Uf[n], Ur[n] );
}

/*! \todo Read the mean flow from the file */
void LinEuler_prim::set_mean(vField &Fm) {
  // test for the zero mean flow
  for (LocalSize e=0; e<ne; e++) {
    for (LocalSize q=0; q<Fm[0]->el[e]->qtot; q++) {
      Fm[0]->el[e]->u[q] = 1.0;                    //rho
      Fm[1]->el[e]->u[q] = 7.93650793650793650786; //p
      Fm[2]->el[e]->u[q] = 0.0;                    //u
      Fm[3]->el[e]->u[q] = 0.0;                    //v
    }
  }
  // project fields to the polynomial space just to make sure
  Fm.project();
}

void LinEuler_prim::enforce_bc(vField &S) {
  dVector us[4];
  dVector ub[4];
  for (LocalSize n=0; n<S[0]->nbc; n++) {
    const LocalSize sid = S[0]->bc[n]->sid;
    const LocalSize qtot = S[0]->bc[n]->elmt->side[sid]->qtot();
    dVector &nx = S[0]->bc[n]->elmt->side[sid]->nx();
    dVector &ny = S[0]->bc[n]->elmt->side[sid]->ny();
    if (S[0]->bc[n]->type=="W") {
      for (vField::size_type i=0; i<Nfields; i++) {
        us[i].alias( S[i]->bc[n]->elmt->side[sid]->u );
        ub[i].alias( S[i]->bc[n]->elmt->side[sid]->link->u );
      }
      for (LocalSize i=0; i<qtot; i++) {
        ub[0][i] = us[0][i];
        ub[1][i] = us[1][i];
        ub[2][i] = (us[2][i]*ny[i] - us[3][i]*nx[i])*ny[i];
        ub[3][i] = (us[3][i]*nx[i] - us[2][i]*ny[i])*nx[i];

      }
    } else {
      for (vField::size_type i=0; i<Nfields; i++) {
        us[i].alias( S[i]->bc[n]->elmt->side[sid]->u );
        ub[i].alias( S[i]->bc[n]->elmt->side[sid]->link->u );
      }
      Scalar rho,u,v,Ma,k; // T
      // int indexp;
      Point cxy;
      Ma = 0.3;
      Scalar c = 1.0/Ma;
      k = 2.5;
      AcousticWave pw(0.3,1.0,gamma,0.02,0.0,0.7,'x','p',
                      AcousticWave::Gaussian);
      Point *pside = new Point[S[0]->bc[n]->elmt->side[sid]->qtot()];
      S[0]->bc[n]->elmt->get_side_coordinates(sid, pside);
      for (LocalSize i=0; i<qtot; i++) {
        // indexp = get_edge_point(S[0]->bc[n]->elmt,side,i);
        // cxy = Point(S[0]->bc[n]->elmt->C->x[indexp],
        // S[0]->bc[n]->elmt->C->y[indexp]);
        cxy = Point(pside[i].x,pside[i].y);

        rho = pw.R(cxy)*sin(k*(cxy.x-0-c*t));  // rhom
        u = pw.U(cxy)*sin(k*(cxy.x-0-c*t));    // u
        v = pw.V(cxy)*sin(k*(cxy.x-0-c*t));    // v
        // T = pw.T(cxy)*sin(k*(cxy.x-0-c*t)); // T +Tm

        ub[0][i] = rho;
        ub[1][i] = rho/Ma/Ma;                  // rho*T/(gamma*Ma*Ma);
        ub[2][i] = u;
        ub[3][i] = v;
      }
    }
  }
}

void LinEuler_prim::enforce_flux_bc(vField &S) {
  //  cout << "Euler::enforce_flux_bc(vField &U)" << endl;
}

void LinEuler_prim::enforce_mean_state_bc(vField &S) {
  dVector us[4];
  dVector ub[4];
  for (LocalSize n=0; n<S[0]->nbc; n++) {
    const LocalSize sid = S[0]->bc[n]->sid;
    const LocalSize qtot = S[0]->bc[n]->elmt->side[sid]->qtot();
    dVector &nx = S[0]->bc[n]->elmt->side[sid]->nx();
    dVector &ny = S[0]->bc[n]->elmt->side[sid]->ny();
    if (S[0]->bc[n]->type=="W") {
      for (vField::size_type i=0; i<Nfields; i++) {
        us[i].alias( S[i]->bc[n]->elmt->side[sid]->u );
        ub[i].alias( S[i]->bc[n]->elmt->side[sid]->link->u );
      }
      for (LocalSize i=0; i<qtot; i++) {
        ub[0][i] = us[0][i];
        ub[1][i] = us[1][i];
        ub[2][i] = (us[2][i]*ny[i] - us[3][i]*nx[i])*ny[i];
        ub[3][i] = (us[3][i]*nx[i] - us[2][i]*ny[i])*nx[i];

      }
    } else {
      for (vField::size_type i=0; i<Nfields; i++) {
        us[i].alias( S[i]->bc[n]->elmt->side[sid]->u );
        ub[i].alias( S[i]->bc[n]->elmt->side[sid]->link->u );
      }
      for (LocalSize i=0; i<qtot; i++) {
        ub[0][i] = 1.0; //us[0][i];
        ub[1][i] = 7.93650793650793650786; //us[1][i];
        ub[2][i] = 0.0; //us[2][i];
        ub[3][i] = 0.0; //us[3][i];
      }
    }
  }
}

#if 0
// Need to modify to satisfy the LinEuler_prim -- cgq
void LinEuler_prim::compute_vorticity() {
  Element *S[4], *F[4];
  dVector u, v, p, e, wk;
  dVector r, ru, rv, E;

#ifdef REO_LINEULER_JUMP
  U.fill_sides();
  enforce_bc( U );
  primitive_sides( U );
  U.share_sides();
  average_side_flux( U, Ut, '+' );
#endif

  for (LocalSize i=0; i<U[0]->ne; i++) {
    // local version of the state
    S[0] = Up[0]->el[i]; //rho
    S[1] = Up[1]->el[i]; //p
    S[2] = Up[2]->el[i]; //u
    S[3] = Up[3]->el[i]; //v

    // local version of the state
    F[0] = Ut[0]->el[i];
    F[1] = Ut[1]->el[i];
    F[2] = Ut[2]->el[i];
    F[3] = Ut[3]->el[i];

    const int qtot = U[0]->el[i]->qtot;

    r.alias(S[0]->u);  // rho
    p.alias(S[1]->u);  // rho u
    u.alias(S[2]->u);  // rho v
    v.alias(S[3]->u);  // total Energy

    e.alias(wk3,0,qtot);
    E.alias(wk3,qtot,qtot);
    wk.alias(wk3,2*qtot,qtot);

    dvdiv(p,r,e);
    scale(1.0/(gamma-1.0),e);

    dvmul(u,u,wk);     // wk = u^2
    dvvtvp(v,v,wk,wk); // wk = u^2 + v^2
    scale(0.5,wk);
    dvadd(e,wk);
    dvmul(r,wk,E);

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
#endif

} // namespace Reo
