/** \file  Couple.cpp
    \brief Multiphysics coupled domain implementation
    \author Scott Collis
    \author Guoquan Chen
*/

// DGM includes
#include "TimeInt.hpp"
#include "Wavetype.hpp"

// local includes
#include "Couple.hpp"
#include "CoupleBC.hpp"

namespace Reo {

#ifdef DGM_USE_MD_COUPLE

/// Constructor the Domain for coupled physics
Couple::Couple( DGM::ArgList &args, const DGM::Comm *comm_ )
  : Euler( args, comm_ ) {

  vis   = params["vis"];               // viscosity
  Pr    = params["Pr"];                // Prandtl number for air
  gamma = params["gamma"];             // ratio of specific heats

  setup_BCdb();                        // setup BC database

  // make auxiliary Fields using copy constructor
  for (int i=0; i<Nfields; i++) {
    Uv.push_back( new Field( U[i], root, U[i]->name));
    Um.push_back( new Field( U[0], root, U[i]->name));  // Mean(Base) flow
    Up.push_back( new Field( U[0], root, U[i]->name));  // Primitive
  }

  // try out the fluid_properties class
  fluid = new Sutherland(1.4, 287.0, 0.72, 1.716e-5, 110.0, 101000.0, 111.0);

  // allocate workspace
  work.resize(20*max(Lmax,Qmax));

  setup_side_maps();

  // make sure that storage is initialized
  zero_all_fields();

  setup_Sourcedb();        // setup Source term database

  set_TimeInt();
}

void Couple::time_derivative( vField &Us, vField &Uf ) {
  convection( Us, Uf );
  diffusion( Us, Uv, Uf );
  //  if(0) set_sponge(Us,Uf);  // add the sponge
  add_source(Us,Uf);
  project( Uf );
}

void Couple::convection( vField &Us, vField &Uf ) {
  Element *U[4], *F[4],*Fm[4];
  int qtot, e, i;
  dVector u1, v, p, d, d1;
  dVector r, ru, rv, E;

  dVector Fx1,Fx2,Fx3,Fx4,Fy1,Fy2,Fy3,Fy4;
  Scalar w[4],u[2],rho,T;

  Us.fill_sides();

  // fill edge for the mean flow field
  Um.fill_sides();
  Um.share_sides();
  enforce_mean_bc(Um);

  enforce_bc(Us);
  Us.share_sides();
  convective_flux( Us, Uf );

  for (e=0; e<Us[0]->ne; e++) {

    // local version of the state
    U[0] = Us[0]->el[e];
    U[1] = Us[1]->el[e];
    U[2] = Us[2]->el[e];
    U[3] = Us[3]->el[e];

    // local version of the flux
    F[0] = Uf[0]->el[e];
    F[1] = Uf[1]->el[e];
    F[2] = Uf[2]->el[e];
    F[3] = Uf[3]->el[e];

    // local version of the mean flow
    Fm[0] = Um[0]->el[e];
    Fm[1] = Um[1]->el[e];
    Fm[2] = Um[2]->el[e];
    Fm[3] = Um[3]->el[e];

    qtot = Us[0]->el[e]->qtot;

    if(F[0]->modeltype == Model::LINEULER){
      Fx1.alias(work,0,qtot);
      Fx2.alias(work,qtot,qtot);
      Fx3.alias(work,2*qtot,qtot);
      Fx4.alias(work,3*qtot,qtot);
      Fy1.alias(work,4*qtot,qtot);
      Fy2.alias(work,5*qtot,qtot);
      Fy3.alias(work,6*qtot,qtot);
      Fy4.alias(work,7*qtot,qtot);
      d.alias(work,8*qtot,qtot);

      //For simple case, the mean flow is uniform flow ,
      //  Since A(au),B(au) constant matrix
      // we can get F(u(x)),x = A(au) u,x
      //            G(u(x)),y = B(au) u,y
      // In future, if the mean flow has the spatial distribution, we should
      //     Set    F(u(x)),x = (A(au) u),x
      //            G(u(x)),y = (B(au) u),y

      for (int q=0; q<qtot; q++) {

        for(int i=0;i<Nfields;i++)
          w[i] = U[i]->u[q];

        rho  = Fm[0]->u[q];
        u[0] = Fm[1]->u[q];
        u[1] = Fm[2]->u[q];
        T    = Fm[3]->u[q];

        Fx1[q] = w[1];
        Fx2[q] = -3.0/2.0*w[0]*u[0]*u[0]+w[0]*u[0]*u[0]*gamma/2.0
          +w[0]*u[1]*u[1]*gamma/2.0-w[0]*u[1]*u[1]/2.0+3.0*w[1]*u[0]
          -w[1]*u[0]*gamma-w[2]*u[1]*gamma+w[2]*u[1]+w[3]*gamma-w[3];
        Fx3[q] = -u[0]*u[1]*w[0]+u[1]*w[1]+u[0]*w[2];
        Fx4[q] = -(3.0*u[0]*u[0]*u[0]*w[0]*gamma -2.0*u[0]*u[0]*u[0]*w[0]
                   +3.0*u[0]*w[0]*u[1]*u[1]*gamma + 2.0*u[0]*w[0]*T
                   -2.0*u[0]*w[0]*u[1]*u[1] - u[0]*u[0]*u[0]*w[0]*gamma*gamma
                   - u[0]*w[0]*u[1]*u[1]*gamma*gamma - 5.0*w[1]*u[0]*u[0]*gamma
                   + 3.0*w[1]*u[0]*u[0] -w[1]*u[1]*u[1]*gamma + w[1]*u[1]*u[1]
                   - 2.0*w[1]*T + 2.0*w[1]*u[0]*u[0]*gamma*gamma
                   +2.0*u[0]*u[1]*w[2]*gamma*gamma-4.0*u[0]*u[1]*w[2]*gamma
                   +2.0*u[0]*u[1]*w[2] - 2.0*u[0]*gamma*gamma*w[3]
                   +2.0*u[0]*gamma*w[3])/(gamma-1.0)/2.0;

        Fy1[q] = w[2];
        Fy2[q] = -u[0]*u[1]*w[0]+u[1]*w[1]+u[0]*w[2];
        Fy3[q] = -3.0/2.0*w[0]*u[1]*u[1]+w[0]*u[0]*u[0]*gamma/2.0
          -w[0]*u[0]*u[0]/2.0+w[0]*u[1]*u[1]*gamma/2.0
          -w[1]*u[0]*gamma+w[1]*u[0]
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

    } else if ( F[0]->modeltype == Model::EULER ||
                F[0]->modeltype == Model::NAVIER_STOKES ) {

      r.alias (U[0]->u);  // rho
      ru.alias(U[1]->u);  // rho u
      rv.alias(U[2]->u);  // rho v
      E.alias (U[3]->u);  // total Energy

      u1.alias(work,0,qtot);
      v.alias(work,qtot,qtot);
      p.alias(work,2*qtot,qtot);
      d.alias(work,3*qtot,qtot);
      d1.alias(work,4*qtot,qtot);

      dvdiv(ru, r, u1);  // compute u
      dvdiv(rv, r, v);   // compute v

      // p = (gamma-1.0)*(E-0.5*(r*u*u + r*v*v))
      dvmul(u1, ru, p);
      dvvtvp(v, rv, p, p);
      scale(-0.5*(gamma-1.0), p);
      daxpy(gamma-1.0, E, p);

      // Uf[0]->el[e]->u = (d/dx)(ru) + (d/dy)(rv)
      U[0]->gradient(ru, F[0]->u, 'x');
      U[0]->gradient(rv, d, 'y');
      dvadd(d, F[0]->u);

      // Uf[1]->el[e]->u = (d/dx)(ru*u+p) + (d/dy)(ru*v)
      dvvtvp(ru, u1, p, d);
      U[1]->gradient(d, F[1]->u, 'x');
      dvmul(ru, v, d);
      U[1]->gradient(d, d1, 'y');
      dvadd(d1, F[1]->u);

      // Uf[2]->el[e]->u = (d/dx)(rv*u) + (d/dy)(rv*v+p)
      dvmul(rv, u1, d);
      U[2]->gradient(d, F[2]->u, 'x');
      dvvtvp(rv, v, p, d);
      U[2]->gradient(d, d1, 'y');
      dvadd( d1, F[2]->u );

      // Uf[3]->el[e]->u = (d/dx)(u*(E+p)) + (d/dy)(v*(E+p))
      dvadd(E, p);
      dvmul(u1, p, d);
      U[3]->gradient(d, F[3]->u, 'x');
      dvmul(v, p, d);
      U[3]->gradient(d, d1, 'y');
      dvadd( d1, F[3]->u );

    } else if(F[0]->modeltype==Model::WAVE) {

      //Similar to LinEuler except that there is no Energy flux
      Fx1.alias(work,0,qtot);
      Fx2.alias(work,qtot,qtot);
      Fx3.alias(work,2*qtot,qtot);
      Fy1.alias(work,3*qtot,qtot);
      Fy2.alias(work,4*qtot,qtot);
      Fy3.alias(work,5*qtot,qtot);
      d.alias(work,6*qtot,qtot);

      //  Since A(au),B(au) constant matrix
      // we can get F(u(x)),x = A(au) u,x
      //            G(u(x)),y = B(au) u,y
      // In future, if the mean flow has the spatial distribution, we should
      //     Set    F(u(x)),x = (A(au) u),x
      //            G(u(x)),y = (B(au) u),y

      for (int q=0; q<qtot; q++) {

        for(int i=0;i<(Nfields-1);i++) w[i]=U[i]->u[q];
        rho = Fm[0]->u[q];
        u[0]= Fm[1]->u[q];
        u[1]= Fm[2]->u[q];
        T   = Fm[3]->u[q];
        Scalar c =  sqrt(T);

        Fx1[q] = w[1];
        Fx2[q] = -w[0]*u[0]*u[0]+w[0]*c*c+2.0*u[0]*w[1];
        Fx3[q] = -u[0]*u[1]*w[0]+u[1]*w[1]+u[0]*w[2];

        Fy1[q] = w[2];
        Fy2[q] = -u[0]*u[1]*w[0]+u[1]*w[1]+u[0]*w[2];
        Fy3[q] = -w[0]*u[1]*u[1]+w[0]*c*c+2.0*u[1]*w[2];

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
    }
    // add the surface contribution
    if(F[0]->modeltype!=Model::WAVE)
      for (i=0; i<Nfields; i++) U[i]->lift( F[i], F[i]->u );
    else
      for (i=0; i<(Nfields-1); i++) U[i]->lift(F[i],F[i]->u);
  }
}

/// Compute the convective_flux for coupled physics
/** Important for the coupling, especial for the inviscid flux, achieved by
    the local-defined edges(done as before) or using the coupling
    edges. current flux is only implemented using Lax_Friedrichs flux, the
    other types of numerical fluxes should be similar.  the computation of
    convective flux is too tedious and lengthy.

    For descriptions of the numerical fluxes
    See:  E.F. Toro, "Riemann Solvers and Numerical Methods for Fluid
    Dynamics," 2nd Edition, Springer, 1999, p. 305.

    \note Computes the flux along the edge point using the function call
*/
void Couple::convective_flux(vField &Us, vField &Uf) {
  flux_type flux = LaxFriedrichs;
  int qtot, qr, ql;
  Scalar nx, ny;
  dVector sl(Nfields), sr(Nfields), f(Nfields), U(Nfields), Ua(Nfields);
  Scalar rl, ml, nl, El, ul, vl, pl, Hl, Ml, cl;
  Scalar rr, mr, nr, Er, ur, vr, pr, Hr, Mr, cr;
  vector<Side *> Ssl(Nfields), Ssr(Nfields);
  vector<Side *> Sfl(Nfields), Sfr(Nfields);
  Scalar fpl[4], fmr[4], lmax;
  dVector lam(Nfields);
#ifdef REO_USE_GETSIDEMAPS
    iVector mapl, mapr;
#endif
  int nfields;

  Scalar rho,u[2],T,p,w[4];
  Scalar rhop,up,vp;

  // Variables for the coupling sides
  vector<Side *> Asl(Nfields), Asr(Nfields);
  dVector slA(Nfields), srA(Nfields);
  dVector fplA(Nfields), fmrA(Nfields),fA(Nfields);
  Scalar ulA,clA,urA,crA;
  vector<Side *> Sml(Nfields), Smr(Nfields);       // mean flow field sides

  for (int e=0; e<Us[0]->ne; e++) {                // loop over elements
    Element* U = Uf[0]->el[e];
    for (int i=0; i<Us[0]->el[e]->nSides; i++) {   // loop over sides
      if (Us[0]->el[e]->side[i]->master()) {       // compute if master
        qtot = Us[0]->el[e]->side[i]->qtot;        // quad pts on side
        nfields = Nfields;
        for (int ni=0; ni<nfields; ni++) {
          Ssl[ni] = Us[ni]->el[e]->side[i];        // local state side
          Ssr[ni] = Us[ni]->el[e]->side[i]->link;  // adjacent state side
          Sfl[ni] = Uf[ni]->el[e]->side[i];        // local flux side
          Sfr[ni] = Uf[ni]->el[e]->side[i]->link;  // adjacent flux side
          Sml[ni] = Um[ni]->el[e]->side[i];        // local mean side
          Smr[ni] = Um[ni]->el[e]->side[i]->link;  // adjacent mean side
        }
#ifdef REO_USE_GETSIDEMAPS
        get_side_maps( Ssl[0], Ssr[0], mapl, loc_adj );
#endif

        /* Here for those edges adjacent with the coupling surfaces,the
           upwind flux for the two adjacent edges will be computed,
           respectively.different from before (Sfr = -Sfl). We will
           create two edges for Sfl and Sfr */

        if(Ssl[0]->modeltype != Ssr[0]->modeltype ) {
          for (int ni=0; ni<nfields; ni++) {
            Asl[ni] = new Side(Ssl[ni]);
            Asr[ni] = new Side(Ssr[ni]);
          }
          convert_sides(Asl, Sml, Asl[0]->modeltype, Ssr[0]->modeltype);
          convert_sides(Asr, Smr, Asr[0]->modeltype, Ssl[0]->modeltype);
        }

        for (int q=0; q<qtot; q++) {         // loop over side quad-pts

#ifdef REO_USE_GETSIDEMAPS
          ql = mapl[q];
          qr = mapr[q];
#else
          ql = U->sideMap(Ssl[0], q);
          qr = U->sideMap(Ssr[0], q);
#endif

          nx = Us[0]->el[e]->side[i]->nx(ql);  // side normal
          ny = Us[0]->el[e]->side[i]->ny(ql);  // side normal

          Point normal(nx,ny);

          // compute normal flux from interior (left)

          // From solution U
          for(int k=0;k<nfields;k++)
            sl[k] = Ssl[k]->u[ql];

          compute_flux(ql,normal,Ssl,Sml,&cl,&ul);

          if( Ssl[0]->modeltype != Ssr[0]->modeltype) {
            for(int k=0;k<nfields;k++)
              slA[k] = Asl[k]->u[ql];
            compute_flux(ql,normal,Asl,Sml,&clA,&ulA);
          }

          // compute normal flux from exterior (right)
          // adjacent state
          for(int k=0;k<nfields;k++)
            sr[k] = Ssr[k]->u[qr];

          compute_flux(qr,normal,Ssr,Smr,&cr,&ur);

          if( Ssl[0]->modeltype != Ssr[0]->modeltype) {
            for(int k=0;k<nfields;k++)
              srA[k] = Asr[k]->u[qr];
            compute_flux(qr,normal,Asr,Smr,&crA,&urA);
          }

          switch (flux) {
          case LaxFriedrichs:

            // Possible problem for Wave (no mean flow OK!),
            // should be fixed later not true for Wave(field 3,not 4)!!!
            if( Ssl[0]->modeltype == Ssr[0]->modeltype) {
              lmax=0;
              lam[0] = ul;
              lam[1] = ul+cl;
              lam[2] = ul-cl;
              lam[3] = ul;
              for(int j=0; j<nfields;j++) {
                lmax=max(lmax,fabs(lam[j]));
                fpl[j] = Ssl[j]->u[ql];
              }
              lam[0] = ur;
              lam[1] = ur+cr;
              lam[2] = ur-cr;
              lam[3] = ur;
              for(int j=0; j<nfields; j++) {
                lmax=max(lmax,fabs(lam[j]));
                fmr[j] = Ssr[j]->u[qr];
              }
              // Lax-Friedrichs flux
              for(int j=0; j<nfields; j++)
                f[j] = 0.5 * ( fpl[j] + fmr[j] + lmax * ( sl[j] - sr[j] ) );

            } else {

                lmax=0;
                lam[0] = ul;
                lam[1] = ul+cl;
                lam[2] = ul-cl;
                lam[3] = ul;
                for(int j=0; j<nfields;j++) {
                  lmax=max(lmax,fabs(lam[j]));
                  fpl[j] = Ssl[j]->u[ql];
                }
                lam[0] = urA;
                lam[1] = urA+crA;
                lam[2] = urA-crA;
                lam[3] = urA;
                for(int j=0; j<nfields;j++) {
                  lmax=max(lmax,fabs(lam[j]));
                  fmrA[j] = Asr[j]->u[qr];
                }
                // Lax-Friedrichs flux for local
                for(int j=0; j<nfields; j++)
                  f[j] = 0.5 * ( fpl[j] + fmrA[j] + lmax * ( sl[j] - srA[j]));

                lmax=0;
                lam[0] = ulA;
                lam[1] = ulA+clA;
                lam[2] = ulA-clA;
                lam[3] = ulA;
                for(int j=0; j<nfields;j++) {
                  lmax=max(lmax,fabs(lam[j]));
                  fplA[j] = Asl[j]->u[ql];
                }
                lam[0] = ur;
                lam[1] = ur+cr;
                lam[2] = ur-cr;
                lam[3] = ur;
                for(int j=0; j<nfields; j++) {
                  lmax=max(lmax,fabs(lam[j]));
                  fmr[j] = Ssr[j]->u[qr];
                }
                // Lax-Friedrichs flux for adjacent
                for(int j=0; j<nfields; j++)
                  fA[j] = 0.5 * ( fplA[j] + fmr[j] + lmax * ( slA[j] - sr[j]));
              }
            break;
          case vanLeer:
          case StegerWarming:
          case Roe:                                  // Roe average
            cerr << "Those flux types haven't been"
                 <<" implemented yet for coupling problem" << endl;
            comm->exit(DGM::FAILURE);
            break;
          default:
            cerr << "Illegal value of flux type" << endl;
            comm->exit(DGM::FAILURE);
          }

          // put fluxes on flux field sides
          for (int ni=0; ni<nfields; ni++) {
            if (Ssl[0]->modeltype==Ssr[0]->modeltype) {
              Ssr[ni]->u[qr] *= -1.0;         // correct for normal
              Sfl[ni]->u[ql]  =  f[ni];
              Sfr[ni]->u[qr]  = -f[ni];
            } else {
              Ssr[ni]->u[qr] *= -1.0;         // correct for normal
              Sfl[ni]->u[ql]  =  f[ni];
              Sfr[ni]->u[qr]  = -fA[ni];
            }
          }
        }
        // delete the auxiliary Sides
        if(Ssl[0]->modeltype != Ssr[0]->modeltype ) {
          for (int ni=0; ni<nfields; ni++) {
            delete Asl[ni];
            delete Asr[ni];
          }
        }
      }
    }
  }
}

//===========================================================================

void Couple::enforce_bc(vField &F) {
  for (BC::db_itr i=BC_db.begin(); i!= BC_db.end(); ++i)
    i->second->apply( t, F );
}

void Couple::enforce_flux_bc(vField &F) {
  for (BC::db_itr i=BC_db.begin(); i!= BC_db.end(); ++i)
    i->second->apply_flux( t, F );
}

void Couple::enforce_mean_bc(vField &S) {
  dVector us[4];
  dVector ub[4];
  for (int n=0; n<S[0]->nbc; n++) {
    int sid = S[0]->bc[n]->sid;
    int qtot = S[0]->bc[n]->elmt->side[sid]->qtot;
    dVector &nx = S[0]->bc[n]->elmt->side[sid]->nx();
    dVector &ny = S[0]->bc[n]->elmt->side[sid]->ny();
    switch (S[0]->bc[n]->type[0]) {
    case 'W':
      for (int i=0; i<Nfields; i++) {
        us[i].alias( S[i]->bc[n]->elmt->side[sid]->u );
        ub[i].alias( S[i]->bc[n]->elmt->side[sid]->link->u );
      }
      // slip boundary here??
      for (int i=0; i<qtot; i++) {
        ub[0][i] = us[0][i]; // rho_m
        ub[1][i] = 0;        // u_m
        ub[2][i] = 0;        // v_m
        ub[3][i] = us[3][i]; // T_m

      }
      break;
    default:
      for (int i=0; i<Nfields; i++) {
        us[i].alias( S[i]->bc[n]->elmt->side[sid]->u );
        ub[i].alias( S[i]->bc[n]->elmt->side[sid]->link->u );
      }
      for (int i=0; i<qtot; i++) {
        ub[0][i] = us[0][i];
        ub[1][i] = us[1][i];
        ub[2][i] = us[2][i];
        ub[3][i] = us[3][i];
      }
      break;
    }
  }
}

// set the initial condition
void Couple::set_ic(vField &F, string ext) {
  t = 0.0; step = 0;
  string fname = root+ext;
  ifstream in(fname.c_str());
  if (!in) {
    cerr << "Could not open initial condition " << fname << endl;
    comm->exit(DGM::FAILURE);
  }
  string buffer, code;
  getline(in,buffer);
  if (!(in>>code)) error("Cannot read IC code",1);
  getline(in,buffer);
  if (lowerCase(code) == "given") {
    F.fill(in);
  // Restart from full Conservative
  } else if (lowerCase(code) == "restart") {
    string rstfile;
    if (!(in>>rstfile)) {
      cerr << "Cannot read restart file name from " << fname << endl;
      comm->exit(DGM::FAILURE);
    }
    read(rstfile, F);
    if (comm->Master()) cout << "Restarting from: " << rstfile << endl;

    // If restarting from one model
    //  Additional work to transform the full conservative
    //  to the peturbation primitive (U' = U - Um)
#if 1
    for (int k=0; k<F[0]->ne; k++) {
      dVector wk;
      wk.alias(work,0,F[0]->el[k]->qtot);  // WARNING: new memory
      dVector  r(F[0]->el[k]->u);     // rho
      dVector  u(F[1]->el[k]->u);     // rho u
      dVector  v(F[2]->el[k]->u);     // rho v
      dVector  T(F[3]->el[k]->u);     // total energy per volume
      dvdiv(u, r, u);                 // u-velocity
      dvdiv(v, r, v);                 // v-velocity
      dvdiv(T, r, T);                 // internal energy + 0.5 |V|^2
      dvmul(u, u, wk);                // wk = u^2
      dvvtvp(v, v, wk, wk);           // wk = u^2 + v^2
      daxpy(-0.5, wk, T);             // e  = e - 0.5 * wk = internal energy
      scale(gamma*(gamma-1.0),T);     // T

      dvsub(r,Um[0]->el[k]->u,r);
      dvsub(u,Um[1]->el[k]->u,u);
      dvsub(v,Um[2]->el[k]->u,v);
      dvsub(T,Um[3]->el[k]->u,T);
    }
#endif
    // Restart from Primitive Fluctuation
  } else if (lowerCase(code) == "restart_p") {
    string rstfile;
    if (!(in>>rstfile)) {
      cerr << "Cannot read restart file name from " << fname << endl;
      comm->exit(DGM::FAILURE);
    }
    read(rstfile, F);
    if (comm->Master()) cout << "Restarting from: " << rstfile << endl;
  }

#ifdef DGM_NO_PROJECT_IC
  if (comm->Master())
    cout << "WARNING:  No projection of Initial condition" << endl;
  for (int i=0; i<Nfields; i++)
    for (int e=0; e<ne; e++)
      F[i]->el[e]->state = Element::Physical;
#else
  // project fields to the polynomial space just to make sure
  project( F );
#endif
}

void Couple::zero_all_fields() {
  Domain::zero_all_fields();
  Uv.zero();
  Um.zero();
  Up.zero();
}

void Couple::get_viscosity( dVector &mu ) {
  mu = vis;
}

//===========================================================================
// Bassi-Rebay viscous flux
//===========================================================================

void Couple::diffusion( vField &Us, vField &Uf, vField &Ur ) {
  Element *S[4], *F[4];
  int qtot, n, k;
  dVector u, v, p, e, wk;
#if 1
  int NSe =0;
  for (int e=0; e<Us[0]->ne; e++)
    if(Us[0]->el[e]->modeltype==Model::NAVIER_STOKES) {
      NSe =1;
      break;
    }
  if(!NSe) return;
#endif

  Us.fill_sides();                   // put solution on the sides
  enforce_bc(Us);                    // update bc side values

  // Update coupling condition here
  primitive_sides(Us);               // convert sides to primative variables
  Us.share_sides();                  // communicate sides if parallel

  // Take care of the coupling edges
  average_flux( Us,Uf,Um, '+' );     // Uf's sides are average state

  for (k=0; k<Us[0]->ne; k++) {

    if(Us[0]->el[k]->modeltype==Model::NAVIER_STOKES) {
      S[0] = Us[0]->el[k];  // local version of the state
      S[1] = Us[1]->el[k];
      S[2] = Us[2]->el[k];
      S[3] = Us[3]->el[k];

      F[0] = Uf[0]->el[k];  // local version of the flux
      F[1] = Uf[1]->el[k];
      F[2] = Uf[2]->el[k];
      F[3] = Uf[3]->el[k];

      dVector r (S[0]->u);  // rho
      dVector ru(S[1]->u);  // rho u
      dVector rv(S[2]->u);  // rho v
      dVector E (S[3]->u);  // total energy per volume

      qtot = S[0]->qtot;
      dVector u(qtot);
      dVector v(qtot);
      dVector e(qtot);
      dVector wk(qtot);

      dvdiv(ru, r, u);   // u-velocity
      dvdiv(rv, r, v);   // v-velocity
      dvdiv(E,  r, e);   // internal energy + 0.5 |V|^2

      dvmul(u,u,wk);     // wk = u^2
      dvvtvp(v,v,wk,wk); // wk = u^2 + v^2
      daxpy(-0.5,wk,e);  // e  = e - 0.5 * wk = internal energy

      dVector ux(qtot);
      dVector uy(qtot);  dVector tau12(uy);  // note the alias
      dVector vx(qtot);  dVector tau11(vx);  // note the alias
      dVector vy(qtot);  dVector tau22(vy);  // note the alias

      gradient( S[1], F[1], u, ux, uy );
      gradient( S[2], F[2], v, vx, vy );

      get_viscosity( wk );

      // Viscous stress:  tau_{ij} = mu ( 2 S_{ij} - 2\delta_{ij}/3 u_{k,k} )
      dvadd(uy, vx, tau12);
      dvmul(wk, tau12);                // mu ( u_{,y} + v_{,x} )

      daxmy(2.0, ux, vy, tau11);       // 2 u_{,x} - v_{,y}
      scale(2.0/3.0, tau11);           // 2/3 ( 2 u_{,x} - v_{,y} )
      dvmul(wk, tau11);                // 2/3 mu ( 2 u_{,x} - v_{,y} )

      daxmy(2.0, vy, ux, tau22);       // 2 v_{,y} - u_{,x}
      scale(2.0/3.0, tau22);           // 2/3 ( 2 v_{,y} - u_{,x} )
      dvmul(wk, tau22);                // 2/3 mu ( 2 v_{,y} - u_{,x} )

      // x-momentum equation
      S[1]->fill_sides( tau11, tau12 );
      S[1]->gradient(tau11, ux, 'x');  // ux = tau_{11,1}
      S[1]->gradient(tau12, wk, 'y');  // wk = tau_{12,2}
      dvadd( ux, wk, F[1]->u );        // F[1]->u = tau_{11,1} + tau_{12,2}

      // y-momentum equation
      S[2]->fill_sides( tau12, tau22 );
      S[2]->gradient(tau12, ux, 'x');  // ux = tau_{21,1}
      S[2]->gradient(tau22, wk, 'y');  // wk = tau_{22,2}
      dvadd( ux, wk, F[2]->u );        // F[2]->u = tau_{21,1} + tau_{22,2}

      // dissipation: tau_11*u + tau_12*v in ux and tau_12*u + tau_22*v in uy
      dvmul (tau11,u,ux);
      dvvtvp(tau12,v,ux,ux);
      dvmul (tau12,u,uy);
      dvvtvp(tau22,v,uy,uy);

      // add in heat conduction (Note: mu*gamma/Pr = kappa/Cv)
      gradient( S[3], F[3], e, vx, vy );  // vx = e_{,x}, vy = e_{,y}
      get_viscosity( wk );
      dvmul(wk,vx);
      daxpy(gamma/Pr,vx,ux);
      dvmul(wk,vy);
      daxpy(gamma/Pr,vy,uy);

      // energy equation
      S[3]->fill_sides( ux, uy );
      S[3]->gradient(ux, wk, 'x'); // wk = (tau_{1j} u_j + k/Cv e_{,1})_{,1}
      S[3]->gradient(uy, ux, 'y'); // ux = (tau_{2j} u_j + k/Cv e_{,2})_{,2}
      dvadd( wk, ux, F[3]->u );  // F[3]->u = (tau_{ij} u_j + k/Cv e_{,i})_{,i}
    }
  }

  Us.share_sides();                        // Share sides with your neighbors
  enforce_flux_bc(Us);                     // put flux BC's on bc sides

  // Take care of the copling conditions
  average_flux( Us,Uf,Um, '-' );

  // Note there is no contribution to the continuity equation
  for (int e=0; e<Us[0]->ne; e++) {
    if(Us[0]->el[e]->modeltype==Model::NAVIER_STOKES){
      for (n=1; n<Us.size(); n++) {
        Element *S = Us[n]->el[e];
        Element *F = Uf[n]->el[e];
        S->lift( F, F->u ); // add side fluxes to interior
      }
    }
  }

  // add in viscous contribution
  scale(-1.0,Uf);

  for (int e=0; e<Uf[0]->ne; e++)
    if(Us[0]->el[e]->modeltype==Model::NAVIER_STOKES)
      for (n=1; n<Uf.size(); n++)
        dvadd( Uf[n]->el[e]->u, Ur[n]->el[e]->u );
}

void Couple::convert_sides(vector<Side *>side, vector<Side *>side_m,
                           const Model::Type otype, const Model::Type ntype) {
  primitive_sides_c(side,side_m);
  conservative_sides(side,side_m,otype,ntype);
}

void Couple::primitive_sides_c(vector<Side *>side, vector<Side *>side_m){
  Scalar factor = gamma*(gamma-1.0);
  Scalar rho,u[2],T,c_m,w[4];
  Scalar rho_p,u_p,v_p,T_p;

  if ( side[0]->modeltype == Model::EULER ||
       side[0]->modeltype == Model::NAVIER_STOKES ) {
    dVector wk;
    wk.alias(work,0,side[0]->qtot);
    dVector  r(side[0]->u);     // rho
    dVector  u(side[1]->u);     // rho u
    dVector  v(side[2]->u);     // rho v
    dVector  e(side[3]->u);     // total energy per volume
    dvdiv(u, r, u);       // u-velocity
    dvdiv(v, r, v);       // v-velocity
    dvdiv(e, r, e);       // internal energy + 0.5 |V|^2
    dvmul(u, u, wk);      // wk = u^2
    dvvtvp(v, v, wk, wk); // wk = u^2 + v^2
    daxpy(-0.5, wk, e);   // e  = e - 0.5 * wk = internal energy
    scale(factor,e);      // T  = e*(gamma*(gamma-1)
  } else if (side[0]->modeltype == Model::LINEULER) {
    dVector rho_p,u_p,v_p,T_p;

    rho_p.alias(side[0]->u);
    u_p.alias(side[1]->u);
    v_p.alias(side[2]->u);
    T_p.alias(side[3]->u);

    for(int q=0;q<side[0]->qtot;q++){

      rho  = side_m[0]->u[q];
      u[0] = side_m[1]->u[q];
      u[1] = side_m[2]->u[q];
      T    = side_m[3]->u[q];

      for(int m=0;m<Nfields;m++) w[m] = side[m]->u[q];

      rho_p[q] = w[0];
      u_p[q]   = -u[0]/rho*w[0]+1/rho*w[1];
      v_p[q]   = -u[1]/rho*w[0]+1/rho*w[2];
      T_p[q]   = 1/rho*(u[0]*u[0]*gamma*gamma
                        -u[0]*u[0]*gamma+u[1]*u[1]*gamma*gamma
                        -u[1]*u[1]*gamma-2.0*T)*w[0]/2.0
        -1/rho*u[0]*gamma*(gamma-1.0)*w[1]
        -1/rho*u[1]*gamma*(gamma-1.0)*w[2]
        +1/rho*gamma*(gamma-1.0)*w[3];
    }
  } else if(side[0]->modeltype ==Model::WAVE) {

    dVector rho_p,u_p,v_p,T_p;
    Scalar P_p;

    rho_p.alias(side[0]->u);
    u_p.alias(side[1]->u);
    v_p.alias(side[2]->u);
    T_p.alias(side[3]->u);

    for(int q=0;q<side[0]->qtot;q++){

      rho  = side_m[0]->u[q];
      u[0] = side_m[1]->u[q];
      u[1] = side_m[2]->u[q];
      T    = side_m[3]->u[q];
      c_m  = sqrt(T);

      for(int m=0;m<Nfields;m++) w[m] = side[m]->u[q];

      rho_p[q] = w[0];
      u_p[q]   = -u[0]/rho*w[0]+1/rho*w[1];
      v_p[q]   = -u[1]/rho*w[0]+1/rho*w[2];
      P_p      = c_m*c_m*rho_p[q];
      T_p[q]   = (P_p + rho*T/gamma)/(rho+rho_p[q])*gamma - T;

    }
  }
}


void Couple::conservative_sides(vector<Side *>side, vector<Side *>side_m,
                                const Model::Type otype,
                                const Model::Type ntype){
  Scalar factor = 1.0/(gamma*(gamma-1.0));
  Scalar rho,u[2],T,w[4];
  Scalar rho_p,u_p,v_p,T_p;

  if ( ( side[0]->modeltype == Model::EULER ||
         side[0]->modeltype == Model::NAVIER_STOKES ) &&
       ntype == Model::LINEULER) {

    dvsub(side[0]->u,side_m[0]->u,side[0]->u); //rho'
    dvsub(side[1]->u,side_m[1]->u,side[1]->u); //u'
    dvsub(side[2]->u,side_m[2]->u,side[2]->u); //v'
    dvsub(side[3]->u,side_m[3]->u,side[3]->u); //T'

    for(int q=0;q<side[0]->qtot;q++){

      for(int i=0;i<Nfields;i++) w[i] = side[i]->u[q];

      rho  = side_m[0]->u[q];
      u[0] = side_m[1]->u[q];
      u[1] = side_m[2]->u[q];
      T    = side_m[3]->u[q];

      side[0]->u[q] = w[0] ;
      side[1]->u[q] = u[0]*w[0]+rho*w[1];
      side[2]->u[q] = u[1]*w[0]+rho*w[2];
      side[3]->u[q] = (T/gamma/(gamma-1.0)
                       +u[0]*u[0]/2.0+u[1]*u[1]/2.0)*w[0]
        +rho*u[0]*w[1]+rho*u[1]*w[2]
        +rho/gamma/(gamma-1.0)*w[3];
    }

    for(int i=0;i<Nfields;i++) side[i]->modeltype = ntype;

  }
  else if ((side[0]->modeltype == Model::EULER ||
            side[0]->modeltype == Model::NAVIER_STOKES) &&
           ntype == Model::WAVE){

    dvsub(side[0]->u,side_m[0]->u,side[0]->u); //rho'
    dvsub(side[1]->u,side_m[1]->u,side[1]->u); //u'
    dvsub(side[2]->u,side_m[2]->u,side[2]->u); //v'

    for(int q=0;q<side[0]->qtot;q++){

      for(int i=0;i<(Nfields-1);i++) w[i] = side[i]->u[q];

      rho  = side_m[0]->u[q];
      u[0] = side_m[1]->u[q];
      u[1] = side_m[2]->u[q];

      side[0]->u[q] = w[0] ;
      side[1]->u[q] = u[0]*w[0]+rho*w[1];
      side[2]->u[q] = u[1]*w[0]+rho*w[2];
    }

    for(int i=0;i<3;i++) side[i]->modeltype = ntype;

  }
  else if ( (ntype == Model::EULER || ntype == Model::NAVIER_STOKES) &&
            side[0]->modeltype == Model::LINEULER ) {
    for(int q=0;q<side[0]->qtot;q++){
      rho  = side[0]->u[q];
      u[0] = side[1]->u[q];
      u[1] = side[2]->u[q];
      T    = side[3]->u[q];
      side[0]->u[q] = rho;
      side[1]->u[q] = rho*u[0];
      side[2]->u[q] = rho*u[1];
      side[3]->u[q] = rho*T/(gamma*(gamma-1.0))
        +0.5*rho*(u[0]*u[0]+u[1]*u[1]);
    }
    for(int i=0;i<Nfields;i++) side[i]->modeltype = ntype;
  }
  else if((ntype == Model::EULER || ntype==Model::NAVIER_STOKES) &&
          side[0]->modeltype == Model::WAVE) {
    dvadd(side_m[0]->u,side[0]->u); // rho
    dvadd(side_m[1]->u,side[1]->u); // u
    dvadd(side_m[2]->u,side[2]->u); // v
    dvadd(side_m[3]->u,side[3]->u); // T
    for(int q=0;q<side[0]->qtot;q++){
      for(int i=0;i<Nfields;i++) w[i] = side_m[i]->u[q];
      rho_p  = side[0]->u[q];
      u_p    = side[1]->u[q];
      v_p    = side[2]->u[q];
      Scalar c = sqrt(w[3]); //c=sqrt(Tm)
      T_p    = (c*c*rho_p + w[0]*w[3]/gamma)/(w[0]+rho_p)*gamma - w[3];
      rho    = rho_p + w[0];
      u[0]   = u_p + w[1];
      u[1]   = v_p + w[2];
      T      = T_p + w[3];
      side[0]->u[q] = rho;
      side[1]->u[q] = rho*u[0];
      side[2]->u[q] = rho*u[1];
      side[3]->u[q] = rho*T/(gamma*(gamma-1.0))
        +0.5*rho*(u[0]*u[0]+u[1]*u[1]);
    }
    for(int i=0;i<4;i++) side[i]->modeltype = ntype;
  }
}


void Couple::primitive_sides( vField &Us ) {
  // loop over all sides including boundary sides
  for (int k=0; k<Us[0]->ne; k++) {
    for (int i=0; i<Us[0]->el[k]->nSides; i++) {
      if (Us[0]->el[k]->side[i]->master()) {
        if (Us[0]->el[k]->side[i]->modeltype==Model::NAVIER_STOKES){
          dVector wk(Us[0]->el[k]->side[i]->qtot);  // WARNING: new memory
          dVector  r(Us[0]->el[k]->side[i]->u);     // rho
          dVector  u(Us[1]->el[k]->side[i]->u);     // rho u
          dVector  v(Us[2]->el[k]->side[i]->u);     // rho v
          dVector  e(Us[3]->el[k]->side[i]->u);     // total energy per volume
          dvdiv(u, r, u);       // u-velocity
          dvdiv(v, r, v);       // v-velocity
          dvdiv(e, r, e);       // internal energy + 0.5 |V|^2
          dvmul(u, u, wk);      // wk = u^2
          dvvtvp(v, v, wk, wk); // wk = u^2 + v^2
          daxpy(-0.5, wk, e);   // e  = e - 0.5 * wk = internal energy
        }
        if(Us[0]->el[k]->side[i]->link->modeltype==Model::NAVIER_STOKES){
          dVector wk(Us[0]->el[k]->side[i]->link->u.size());
          dVector r(Us[0]->el[k]->side[i]->link->u);  // rho
          dVector u(Us[1]->el[k]->side[i]->link->u);  // rho u
          dVector v(Us[2]->el[k]->side[i]->link->u);  // rho v
          dVector e(Us[3]->el[k]->side[i]->link->u); // total energy per volume
          dvdiv(u, r, u);       // u-velocity
          dvdiv(v, r, v);       // v-velocity
          dvdiv(e, r, e);       // internal energy + 0.5 |V|^2
          dvmul(u, u, wk);      // wk = u^2
          dvvtvp(v, v, wk, wk); // wk = u^2 + v^2
          daxpy(-0.5, wk, e);   // e  = e - 0.5 * wk = internal energy
        }
      }
    }
  }
}


void Couple::average_flux(vField &Us, vField &Uf,const vField &Um, char sign) {
  int qtot;
  int Qmax = Us[0]->Qmax;
#ifdef REO_USE_GETSIDEMAPS
  iVector mapl, mapr;
#endif
  Element *S[4], *Sm[4],*F[4];

  Scalar rho,u[2],T,w[4],E,c_m;
  Scalar rhop,up,vp,Tp;

  switch (sign) {
  case '+':
    for (int e=0; e<Us[0]->ne; e++) {
      S[0] = Us[0]->el[e];
      S[1] = Us[1]->el[e];
      S[2] = Us[2]->el[e];
      S[3] = Us[3]->el[e];

      Sm[0] = Um[0]->el[e];
      Sm[1] = Um[1]->el[e];
      Sm[2] = Um[2]->el[e];
      Sm[3] = Um[3]->el[e];

      F[0] = Uf[0]->el[e];
      F[1] = Uf[1]->el[e];
      F[2] = Uf[2]->el[e];
      F[3] = Uf[3]->el[e];

      for (int i=0; i<S[0]->nSides; i++) {
        if (S[0]->side[i]->master()) {
          if(S[0]->side[i]->modeltype==Model::NAVIER_STOKES ||
             S[0]->side[i]->link->modeltype==Model::NAVIER_STOKES) {

            qtot = S[0]->side[i]->qtot;
#ifdef REO_USE_GETSIDEMAPS
            get_side_maps( S[0]->side[i], S[0]->side[i]->link, mapl, mapr);
#endif

            // WARNING: May cause the problem later, not
            //          primitive @ Euler edges for NS/Euler
            //
            // make Euler edge adjacent with NS edge Primitive
            if(S[0]->side[i]->modeltype == S[0]->side[i]->link->modeltype ||
               S[0]->side[i]->modeltype == Model::EULER ||
               S[0]->side[i]->link->modeltype == Model::EULER) {
              // N-S/N-S Euler/N-S N-S/Euler

              for (int q=0; q<qtot; q++) {
#ifndef REO_USE_GETSIDEMAPS
                Ordinal ql = U->sideMap(S[0]->side[i], q);
                Ordinal qr = U->sideMap(S[0]->side[i]->link, q);
#endif
                for(int ni=0;ni<Us.size();ni++){
#ifdef REO_USE_GETSIDEMAPS
                  F[ni]->side[i]->u[mapl[q]] =
                    0.5*(S[ni]->side[i]->u[mapl[q]]+
                         S[ni]->side[i]->link->u[mapr[q]]);
                  F[ni]->side[i]->link->u[mapr[q]] =
                    F[ni]->side[i]->u[mapl[q]];
#else
                  F[ni]->side[i]->u[q] =
                    0.5*(S[ni]->side[i]->u[ql]+
                         S[ni]->side[i]->link->u[qr]);
                  F[ni]->side[i]->link->u[qr] = F[ni]->side[i]->u[ql];
#endif
                }
              }
            } else if(S[0]->side[i]->link->modeltype == Model::LINEULER ||
                      S[0]->side[i]->modeltype == Model::LINEULER) {
              if(S[0]->side[i]->link->modeltype == Model::LINEULER) {
                for (int q=0; q<qtot; q++) {
#ifndef REO_USE_GETSIDEMAPS
                  Ordinal ql = U->sideMap(S[0]->side[i], q);
                  Ordinal qr = U->sideMap(S[0]->side[i]->link, q);
#endif
#ifdef REO_USE_GETSIDEMAPS
                  rho  = Sm[0]->side[i]->link->u[mapr[q]];
                  u[0] = Sm[1]->side[i]->link->u[mapr[q]];
                  u[1] = Sm[2]->side[i]->link->u[mapr[q]];
                  T    = Sm[3]->side[i]->link->u[mapr[q]];
                  for(int m=0;m<4;m++)
                    w[m] = S[m]->side[i]->link->u[mapr[q]];
#else
                  rho  = Sm[0]->side[i]->link->u[qr];
                  u[0] = Sm[1]->side[i]->link->u[qr];
                  u[1] = Sm[2]->side[i]->link->u[qr];
                  T    = Sm[3]->side[i]->link->u[qr];
                  for(int m=0;m<4;m++)
                    w[m] = S[m]->side[i]->link->u[qr];
#endif

                  //Get Up
                  rhop = w[0];
                  up   = -u[0]/rho*w[0]+1/rho*w[1];
                  vp   = -u[1]/rho*w[0]+1/rho*w[2];
                  Tp   = 1/rho*(u[0]*u[0]*gamma*gamma
                                -u[0]*u[0]*gamma
                                +u[1]*u[1]*gamma*gamma
                                -u[1]*u[1]*gamma-2.0*T)*w[0]/2.0
                    -1/rho*u[0]*gamma*(gamma-1.0)*w[1]
                    -1/rho*u[1]*gamma*(gamma-1.0)*w[2]
                    +1/rho*gamma*(gamma-1.0)*w[3];

                  rho  = rhop + rho;
                  u[0] = up + u[0];
                  u[1] = vp + u[1];
                  T    = Tp + T;
                  E    = T/(gamma*(gamma-1.0));

                  F[0]->side[i]->u[ql] = 0.5*(S[0]->side[i]->u[ql] + rho);
                  F[1]->side[i]->u[ql] = 0.5*(S[1]->side[i]->u[ql] + u[0]);
                  F[2]->side[i]->u[ql] = 0.5*(S[2]->side[i]->u[ql] + u[1]);
                  F[3]->side[i]->u[ql] = 0.5*(S[3]->side[i]->u[ql] + E);
                }
              } else {
                for (int q=0; q<qtot; q++) {
#ifndef REO_USE_GETSIDEMAPS
                  Ordinal ql = U->sideMap(S[0]->side[i], q);
                  Ordinal qr = U->sideMap(S[0]->side[i]->link, q);
#endif
                  rho  = Sm[0]->side[i]->u[ql];
                  u[0] = Sm[1]->side[i]->u[ql];
                  u[1] = Sm[2]->side[i]->u[ql];
                  T    = Sm[3]->side[i]->u[ql];
                  for(int m=0;m<4;m++)
                    w[m] = S[m]->side[i]->u[ql];

                  //Get Up
                  rhop = w[0];
                  up   = -u[0]/rho*w[0]+1/rho*w[1];
                  vp   =  -u[1]/rho*w[0]+1/rho*w[2];
                  Tp   = 1/rho*(u[0]*u[0]*gamma*gamma
                                -u[0]*u[0]*gamma
                                +u[1]*u[1]*gamma*gamma
                                -u[1]*u[1]*gamma - 2.0*T)*w[0]/2.0
                    -1/rho*u[0]*gamma*(gamma-1.0)*w[1]
                    -1/rho*u[1]*gamma*(gamma-1.0)*w[2]
                    +1/rho*gamma*(gamma-1.0)*w[3];

                  rho  = rhop + rho;
                  u[0] = up + u[0];
                  u[1] = vp + u[1];
                  T    = Tp + T;
                  E    = T/(gamma*(gamma-1.0));

                  F[0]->side[i]->link->u[qr] =
                    0.5*(S[0]->side[i]->link->u[qr] + rho);
                  F[1]->side[i]->link->u[qr] =
                    0.5*(S[1]->side[i]->link->u[qr] + u[0]);
                  F[2]->side[i]->link->u[qr] =
                    0.5*(S[2]->side[i]->link->u[qr] + u[1]);
                  F[3]->side[i]->link->u[qr] =
                    0.5*(S[3]->side[i]->link->u[qr] + E);
                }
              }
            } else if(S[0]->side[i]->link->modeltype == Model::WAVE ||
                      S[0]->side[i]->modeltype == Model::WAVE) {

              if(S[0]->side[i]->link->modeltype == Model::WAVE) {
                for (int q=0; q<qtot; q++) {
#ifndef REO_USE_GETSIDEMAPS
                  Ordinal ql = U->sideMap(S[0]->side[i], q);
                  Ordinal qr = U->sideMap(S[0]->side[i]->link, q);
#endif
                  rho  = Sm[0]->side[i]->link->u[qr];
                  u[0] = Sm[1]->side[i]->link->u[qr];
                  u[1] = Sm[2]->side[i]->link->u[qr];
                  T    = Sm[3]->side[i]->link->u[qr];
                  c_m  = sqrt(T);
                  for(int m=0;m<4;m++)
                    w[m] = S[m]->side[i]->link->u[qr];

                  //Get Up
                  rhop = w[0];
                  up   = -u[0]/rho*w[0]+1/rho*w[1];
                  vp   = -u[1]/rho*w[0]+1/rho*w[2];
                  Tp   = (c_m*c_m*rhop + rho*T/gamma)
                    /(rho+rhop)*gamma - T;

                  rho  = rhop + rho;
                  u[0] = up + u[0];
                  u[1] = vp + u[1];
                  T    = T + Tp;

                  E  = T/(gamma*(gamma-1.0));

                  F[0]->side[i]->u[ql] =
                    0.5*(S[0]->side[i]->u[ql] + rho);
                  F[1]->side[i]->u[ql] =
                    0.5*(S[1]->side[i]->u[ql] + u[0]);
                  F[2]->side[i]->u[ql] =
                    0.5*(S[2]->side[i]->u[ql] + u[1]);
                  F[3]->side[i]->u[ql] = 0.5*(S[3]->side[i]->u[ql] + E);
                }
              } else {
                for (int q=0; q<qtot; q++) {
#ifndef REO_USE_GETSIDEMAPS
                  Ordinal ql = U->sideMap(S[0]->side[i], q);
                  Ordinal qr = U->sideMap(S[0]->side[i]->link, q);
#endif
                  rho  = Sm[0]->side[i]->u[ql];
                  u[0] = Sm[1]->side[i]->u[ql];
                  u[1] = Sm[2]->side[i]->u[ql];
                  T    = Sm[3]->side[i]->u[qr];
                  c_m  = sqrt(T);

                  for(int m=0;m<4;m++)
                    w[m] = S[m]->side[i]->u[ql];

                  //Get Up
                  rhop = w[0];
                  up   = -u[0]/rho*w[0]+1/rho*w[1];
                  vp   = -u[1]/rho*w[0]+1/rho*w[2];
                  Tp   = (c_m*c_m*rhop + rho*T/gamma)
                    /(rho+rhop)*gamma - T;

                  rho = rhop + rho;
                  u[0]= up + u[0];
                  u[1]= vp + u[1];
                  T   = T + Tp;
                  E   = T/(gamma*(gamma-1.0));

                  F[0]->side[i]->link->u[qr] =
                    0.5*(S[0]->side[i]->link->u[qr] + rho);
                  F[1]->side[i]->link->u[qr] =
                    0.5*(S[1]->side[i]->link->u[qr] + u[0]);
                  F[2]->side[i]->link->u[qr] =
                    0.5*(S[2]->side[i]->link->u[qr] + u[1]);
                  F[3]->side[i]->link->u[qr] =
                    0.5*(S[3]->side[i]->link->u[qr] + E);
                }
              }
            }
          }
        }
      }
    }
    break;
  case '-':
    for (int e=0; e<Us[0]->ne; e++) {
      S[0] = Us[0]->el[e];
      S[1] = Us[1]->el[e];
      S[2] = Us[2]->el[e];
      S[3] = Us[3]->el[e];

      Sm[0] = Um[0]->el[e];
      Sm[1] = Um[1]->el[e];
      Sm[2] = Um[2]->el[e];
      Sm[3] = Um[3]->el[e];

      F[0] = Uf[0]->el[e];
      F[1] = Uf[1]->el[e];
      F[2] = Uf[2]->el[e];
      F[3] = Uf[3]->el[e];

      for (int i=0; i<S[0]->nSides; i++) {
        if (S[0]->side[i]->master()) {
          if(S[0]->side[i]->modeltype==Model::NAVIER_STOKES
             ||S[0]->side[i]->link->modeltype==Model::NAVIER_STOKES) {

            qtot = S[0]->side[i]->qtot;

#ifdef REO_USE_GETSIDEMAPS
            get_side_maps(S[0]->side[i],S[0]->side[i]->link,mapl,mapr);
#endif

            if(S[0]->side[i]->modeltype == S[0]->side[i]->link->modeltype){
              // N-S/N-S
              for (int q=0; q<qtot; q++) {
#ifndef REO_USE_GETSIDEMAPS
                Ordinal ql = U->sideMap(S[0]->side[i], q);
                Ordinal qr = U->sideMap(S[0]->side[i]->link, q);
#endif
#ifdef REO_USE_GETSIDEMAPS
                for(int ni=0;ni<Us.size();ni++){
                  F[ni]->side[i]->u[mapl[q]] =
                    0.5*(S[ni]->side[i]->u[mapl[q]]
                         -S[ni]->side[i]->link->u[mapr[q]]);
                  F[ni]->side[i]->link->u[mapr[q]] =
                    -F[ni]->side[i]->u[mapl[q]];
                }
#else
                for(int ni=0;ni<Us.size();ni++){
                  F[ni]->side[i]->u[ql] =
                    0.5*(S[ni]->side[i]->u[ql]
                         -S[ni]->side[i]->link->u[qr]);
                  F[ni]->side[i]->link->u[qr] =
                    -F[ni]->side[i]->u[ql]];
#endif
              }
            } else if(S[0]->side[i]->link->modeltype!=Model::NAVIER_STOKES){
              // Ignoring the viscous flux from Wave/LinEuler/Euler side
              if(S[0]->side[i]->link->modeltype == Model::LINEULER
                 || S[0]->side[i]->link->modeltype == Model::EULER
                 || S[0]->side[i]->link->modeltype == Model::WAVE ) {
                for (int q=0; q<qtot; q++) {
#ifndef REO_USE_GETSIDEMAPS
                  Ordinal ql = U->sideMap(S[0]->side[i], q);
                  Ordinal qr = U->sideMap(S[0]->side[i]->link, q);
#endif
#ifdef REO_USE_GETSIDEMAPS
                  F[0]->side[i]->u[mapl[q]] =
                    0.5*(S[0]->side[i]->u[mapl[q]] -0);
                  F[1]->side[i]->u[mapl[q]] =
                    0.5*(S[1]->side[i]->u[mapl[q]] -0);
                  F[2]->side[i]->u[mapl[q]] =
                    0.5*(S[2]->side[i]->u[mapl[q]] -0);
                  F[3]->side[i]->u[mapl[q]] =
                    0.5*(S[3]->side[i]->u[mapl[q]] -0);
#else
                  F[0]->side[i]->u[ql] = 0.5*(S[0]->side[i]->u[ql] -0);
                  F[1]->side[i]->u[ql] = 0.5*(S[1]->side[i]->u[ql] -0);
                  F[2]->side[i]->u[ql] = 0.5*(S[2]->side[i]->u[ql] -0);
                  F[3]->side[i]->u[ql] = 0.5*(S[3]->side[i]->u[ql] -0);
#endif
                }
              } else {
                for (int q=0; q<qtot; q++) {
#ifndef REO_USE_GETSIDEMAPS
                  Ordinal ql = U->sideMap(S[0]->side[i], q);
                  Ordinal qr = U->sideMap(S[0]->side[i]->link, q);
#endif
#ifdef REO_USE_GETSIDEMAPS
                  F[0]->side[i]->link->u[mapr[q]] =
                    -0.5*(0 - S[0]->side[i]->link->u[mapr[q]] );
                  F[1]->side[i]->link->u[mapr[q]] =
                    -0.5*(0 - S[1]->side[i]->link->u[mapr[q]] );
                  F[2]->side[i]->link->u[mapr[q]] =
                    -0.5*(0 - S[2]->side[i]->link->u[mapr[q]] );
                  F[3]->side[i]->link->u[mapr[q]] =
                    -0.5*(0 - S[3]->side[i]->link->u[mapr[q]] );
#else
                  F[0]->side[i]->link->u[qr] =
                    -0.5*(0 - S[0]->side[i]->link->u[qr] );
                  F[1]->side[i]->link->u[qr] =
                    -0.5*(0 - S[1]->side[i]->link->u[qr] );
                  F[2]->side[i]->link->u[qr] =
                    -0.5*(0 - S[2]->side[i]->link->u[qr] );
                  F[3]->side[i]->link->u[qr] =
                    -0.5*(0 - S[3]->side[i]->link->u[qr] );
#endif
                }
              }
            }
          }
        }
      }
    }
    break;
  default:
    cerr << "Couple::average_flux() -- illegal sign" << endl;
    comm->exit(DGM::FAILURE);
  }
}

void Couple::set_mean(vField &Fm, char c) {
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
        for (int k=0; k<Fm[0]->ne; k++) {
          dVector wk;
          wk.alias(work,0,Fm[0]->el[k]->qtot);
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
  } else {
    cout<<"set_mean: can't find mean flow file, "
        <<"using the no mean flow instead, "
        <<"using reference Ma =0.3"
        <<endl;
    if(c=='p'){
      //test for the zero mean flow
      for (int e=0; e<ne; e++) {
        for (int q=0; q<Fm[0]->el[e]->qtot; q++) {
          Fm[0]->el[e]->u[q] = 1.0;
          Fm[1]->el[e]->u[q] = 0.0;
          Fm[2]->el[e]->u[q] = 0.0;
          Fm[3]->el[e]->u[q] = 11.11111; //1.0/Ma/Ma
        }
      }
    }
  }
  // project fields to the polynomial space just to make sure
  Fm.project();
}

void Couple::make_U(vField &F, const vField &Fm, const vField &Fp) {
  Scalar rho,T,u[2],w[4];

  for (int e=0; e<ne; e++) {
    if (F[0]->el[e]->modeltype==Model::LINEULER) {
      for (int q=0; q<F[0]->el[e]->qtot; q++) {
        for(int i=0;i<Nfields;i++) w[i]=Fp[i]->el[e]->u[q];
        rho  = Fm[0]->el[e]->u[q];
        u[0] = Fm[1]->el[e]->u[q];
        u[1] = Fm[2]->el[e]->u[q];
        T    = Fm[3]->el[e]->u[q];
        F[0]->el[e]->u[q] = w[0];
        F[1]->el[e]->u[q] = u[0]*w[0] + rho*w[1];
        F[2]->el[e]->u[q] = u[1]*w[0] + rho*w[2];
        F[3]->el[e]->u[q] = (T/gamma/(gamma-1.0) + u[0]*u[0]/2.0
                             + u[1]*u[1]/2.0)*w[0] + rho*u[0]*w[1]
                             + rho*u[1]*w[2] + rho/gamma/(gamma-1.0)*w[3];
      }
    } else if (F[0]->el[e]->modeltype==Model::EULER ||
               F[0]->el[e]->modeltype==Model::NAVIER_STOKES){
      Scalar rho,u1,v,T;
      for (int q=0; q<F[0]->el[e]->qtot; q++) {
        rho = Fp[0]->el[e]->u[q] + Fm[0]->el[e]->u[q];
        u1  = Fp[1]->el[e]->u[q] + Fm[1]->el[e]->u[q];
        v   = Fp[2]->el[e]->u[q] + Fm[2]->el[e]->u[q];
        T   = Fp[3]->el[e]->u[q] + Fm[3]->el[e]->u[q];
        F[0]->el[e]->u[q] = rho;
        F[1]->el[e]->u[q] = rho*u1;
        F[2]->el[e]->u[q] = rho*v;
        F[3]->el[e]->u[q] = rho*T/((gamma-1.0)*gamma)
                          + 0.5*rho*(u1*u1+v*v);
      }
    } else if (F[0]->el[e]->modeltype==Model::WAVE){
      for (int q=0; q<F[0]->el[e]->qtot; q++) {
        for(int i=0;i<Nfields;i++) w[i]=Fp[i]->el[e]->u[q];
        rho = Fm[0]->el[e]->u[q];
        u[0]= Fm[1]->el[e]->u[q];
        u[1]= Fm[2]->el[e]->u[q];
        F[0]->el[e]->u[q] = w[0];
        F[1]->el[e]->u[q] = u[0]*w[0]+rho*w[1];
        F[2]->el[e]->u[q] = u[1]*w[0]+rho*w[2];
      }
    }
  }
#if 0
  cout << "WARNING:  No projection of Initial condition" << endl;
  for (int i=0; i<Nfields; i++)
    for (int e=0; e<ne; e++)
      F[i]->el[e]->state = Physical;
#else
  // project fields to the polynomial space just to make sure
  F.project();
#endif
}

// Get the primitive pertuation variables (U' = U- Um)
void Couple::get_Up(vField &Fp, const vField &Fm, const vField &F) {
  Scalar rho,T,u[2],w[4],c_m;
  for (int e=0; e<ne; e++) {
    if(F[0]->el[e]->modeltype==Model::LINEULER) {
      for (int q=0; q<F[0]->el[e]->qtot; q++) {
        for(int i=0;i<Nfields;i++) w[i]=F[i]->el[e]->u[q];
        rho  = Fm[0]->el[e]->u[q];
        u[0] = Fm[1]->el[e]->u[q];
        u[1] = Fm[2]->el[e]->u[q];
        T    = Fm[3]->el[e]->u[q];
        //code produced by Maple
        Fp[0]->el[e]->u[q] = w[0];
        Fp[1]->el[e]->u[q] = -u[0]/rho*w[0]+1/rho*w[1];
        Fp[2]->el[e]->u[q] = -u[1]/rho*w[0]+1/rho*w[2];
        Fp[3]->el[e]->u[q] = 1/rho*(u[0]*u[0]*gamma*gamma
                                    -u[0]*u[0]*gamma
                                    +u[1]*u[1]*gamma*gamma
                                    -u[1]*u[1]*gamma
                                    -2.0*T)*w[0]/2.0
          -1/rho*u[0]*gamma*(gamma-1.0)*w[1]
          -1/rho*u[1]*gamma*(gamma-1.0)*w[2]
          +1/rho*gamma*(gamma-1.0)*w[3];
      }
    } else  if (F[0]->el[e]->modeltype==Model::EULER ||
                F[0]->el[e]->modeltype==Model::NAVIER_STOKES){
      Scalar rho,rho_u,rho_v,rho_e;
      for (int q=0; q<Fp[0]->el[e]->qtot; q++) {
        rho     = F[0]->el[e]->u[q];
        rho_u   = F[1]->el[e]->u[q];
        rho_v   = F[2]->el[e]->u[q];
        rho_e   = F[3]->el[e]->u[q];
        Fp[0]->el[e]->u[q] = rho;
        Fp[1]->el[e]->u[q] = rho_u/rho;
        Fp[2]->el[e]->u[q] = rho_v/rho;
        Fp[3]->el[e]->u[q] = (rho_e-0.5*(rho_u*rho_u+rho_v*rho_v)/rho)
                             *gamma*(gamma-1.0)/rho;
        Fp[0]->el[e]->u[q]   = Fp[0]->el[e]->u[q] - Fm[0]->el[e]->u[q];
        Fp[1]->el[e]->u[q]   = Fp[1]->el[e]->u[q] - Fm[1]->el[e]->u[q];
        Fp[2]->el[e]->u[q]   = Fp[2]->el[e]->u[q] - Fm[2]->el[e]->u[q];
        Fp[3]->el[e]->u[q]   = Fp[3]->el[e]->u[q] - Fm[3]->el[e]->u[q];
      }
    } else if(F[0]->el[e]->modeltype==Model::WAVE) {
      for (int q=0; q<F[0]->el[e]->qtot; q++) {
        for(int i=0;i<Nfields;i++) w[i]=F[i]->el[e]->u[q];
        rho  = Fm[0]->el[e]->u[q];
        u[0] = Fm[1]->el[e]->u[q];
        u[1] = Fm[2]->el[e]->u[q];
        T    = Fm[3]->el[e]->u[q];
        c_m  = sqrt(T);
        // code produced by Maple
        Fp[0]->el[e]->u[q] = w[0];
        Fp[1]->el[e]->u[q] = -u[0]/rho*w[0]+1/rho*w[1];
        Fp[2]->el[e]->u[q] = -u[1]/rho*w[0]+1/rho*w[2];
        Fp[3]->el[e]->u[q] = (c_m*c_m*w[0] + rho*T/gamma)
                             /(rho+w[0])*gamma - T;
      }
    }
  }
#if 0
  cout << "WARNING:  No projection of Initial condition" << endl;
  for (int i=0; i<Nfields; i++)
    for (int e=0; e<ne; e++)
      Fp[i]->el[e]->state = Physical;
#else
  // project fields to the polynomial space just to make sure
  Fp.project();
#endif
}

/** Override the version from the parent Class Domain, since LinEuler needs
    special operation by introducing Up,Um. */
int Couple::solve() {
  Format sci(4); sci.scientific().width(12);
  if (DGM::Comm::World->Master()) cout << "Title = " << title << endl;
  set_mean(Um,'p');    // set the mean flow field
  set_ic(Up);          // set the initial condition (primitive field)
  make_U(U,Um,Up);     // make the initial condition (solution variable)
#ifndef DGM_PARALLEL
  U.tecplot("ic.dat","Initial Condition");
#endif
  if (DGM::Comm::World->Master()) cout << "Advancing solution " << Nt
                                       << " time steps" << endl;
  Scalar ctime=0, stime=0, ttime=0;
  int cnt=0;
  Stopwatch cpu; cpu.start();
  for (lstep=1; lstep<=Nt; lstep++) {
    step++;
    time_int->advance(this);
#ifdef STAT_OBS
    obs_stat(U,t);
#endif
    ctime = cpu.restart();
    if (lstep>1) { ttime += ctime; stime += ctime*ctime; cnt++; }
#if 0
    if (DGM::Comm::World->Master()) cout << setw(5) << step <<  sci(t)
                                         << sci(ctime) << endl;
#else
    if (DGM::Comm::World->Master()) printf("%5d %12.4e %12.4e\n",step,t,ctime);
#endif
    if (step%Ntout==0)  {
      get_Up(Up,Um,U);
      write(step, Up);
      Up.norm();
      cpu.restart();
    }
  }
#ifdef DGM_PARALLEL
  Scalar atime=0, otime=0;
  DGM::Comm::World->SumAll(&ttime,&atime,1); // average cpu time
  DGM::Comm::World->SumAll(&stime,&otime,1); // standard deviation of cpu time
  int n = max(1,cnt*DGM::Comm::World->NumProc());
  if (DGM::Comm::World->Master()) {
    cout << "Average time per step: " << sci(atime/n)
         << ", standard deviation:  "
         << sci( ::sqrt((n*otime-atime*atime)/(n*max(int(n-1),1))) ) << endl;
  }
#endif
  U.write_side_stats();
  response->output( U[0] );
  return 0;
}

//===========================================================================
//                        BC database management
//===========================================================================

// Load up the available BC types
void Couple::setup_BCdb( ) {
  // set default BC types
  dVector ub(4);
  Scalar Eref = 20.34126984126985; // Ma_ref = 0.3
  ub[0] = 1.0;
  ub[1] = 1.0;
  ub[2] = 0.0;
  ub[3] = Eref;
  BC_db["S"].reset( new CStateBC("S", ub) );
  // Assume the wall boundary for NS domain
  BC_db["W"].reset( new Isothermal_WallBC("W", 1.0, Eref));

  // read new BC types from file
  string fname = root+".bct";
  ifstream in(fname.c_str());
  if (in) Couple::read_BCdb( in );   // database of active BC types
}

void Couple::read_BCdb( ifstream &in ) {
  //  cout << "Couple::read_BCdb( ifstream &in )" << endl;
  string tag;
  BC *pbc;
  while ( (pbc = Couple::make_BC(in,tag)) ) {
    if ( BC_db.find(tag) != BC_db.end() )
      cerr << "WARNING in Couple::read_BCdb:  Overriding BC type \""
           << tag << "\"." << endl;
    BC_db[tag].reset( pbc );
  }
}

BC* Couple::make_BC ( ifstream &in, string &tag) {
  string code;
  if (!(in>>code)) return NULL;
  code = lowerCase(code);
  if (code=="state") {
    if (!(in>>tag)) error("Couple::make_BC:  Cannot read State tag",1);
    return new StateBC(tag,in,4);
  } else if (code=="isothermal_wall") {
    if (!(in>>tag))
      error("Couple::make_BC:  Cannot read Isothermal_Wall tag",1);
    return new Isothermal_WallBC(tag,in);
  } else if (code=="isoflux_wall" || code=="wall" ) {
    if (!(in>>tag))
      error("Couple::make_BC:  Cannot read Isoflux_Wall tag",1);
    return new Isoflux_WallBC(tag,in,gamma,vis,Pr);
  } else if (code=="isothermal_control") {
    if (!(in>>tag))
      error("Couple::make_BC:  Cannot read Isothermal_Wall tag",1);
    return new Isothermal_ControlBC(tag,in,&U,gamma,vis,Pr);
  } else if (code=="isoflux_control" ) {
    if (!(in>>tag))
      error("Couple::make_BC:  Cannot read Isoflux_Wall tag",1);
    return new Isoflux_ControlBC(tag,in,&U,gamma,vis,Pr);
  } else {
    error("Couple::make_BC:  Illegal BC type:  "+code,1);
  }
  return NULL;
}

/// Construct source terms
Source::Ptr Couple::make_Source( ifstream &in, string &tag ) {
  // cout << "Couple::make_Source" << endl;
  string code;
  if (!(in >> code)) return NULL;
  while (code[0]=='#') {  // eat comment lines
    string buffer;
    getline(in,buffer);
    if (!(in >> code)) return p;
  }
  if (lowerCase(code) == "sponge") {
    if (!(in >> tag)) error("Couple::Cannot read distributedcontrol tag",1);;
    return new Sponge(tag, in,gamma,Um); // Default Um (primitive)
  } else {
    error("Couple::make_Source() Illegal Source type",1);
  }
  return NULL;
}

// Add source terms
void Couple::add_source(const vField &Us, vField &Ur) {
  // cout << "Couple::add_source(vField &)" << endl;
  for (Source::db_itr i=Source_db.begin(); i!= Source_db.end(); ++i)
    // cout << "Adding source: " << i->first << endl;
    i->second->apply( t, Us, Ur);
}

// This version is more useful since it takes a string as input
int Couple::plot(const string &rst) {

  string fname, name(rst);
  char buf[80];

  //Get the mean flow profile (primitive)
  set_mean(Um,'p');
  //Get the peturbation flow profile (primitive)
  read( rst, U);

  //Transform to the conservative variable (Um+U')
  for (int k=0; k<U[0]->ne; k++) {
    dVector wk;
    wk.alias(work,0,U[0]->el[k]->qtot);  // WARNING: new memory
    dVector  r(U[0]->el[k]->u);     // rho'
    dVector  u(U[1]->el[k]->u);     // u'
    dVector  v(U[2]->el[k]->u);     // v'
    dVector  T(U[3]->el[k]->u);     // T'

    dvadd(Um[0]->el[k]->u,r); // u_m+u'
    dvadd(Um[1]->el[k]->u,u);
    dvadd(Um[2]->el[k]->u,v);
    dvadd(Um[3]->el[k]->u,T);

    dvmul(u, u, wk);      // wk = u^2
    dvvtvp(v, v, wk, wk); // wk = u^2 + v^2
    dvmul(r,wk);         //wk = rho*( u^2 + v^2)
    dvmul(r, u);       // rho*u
    dvmul(r, v);       // rho*v
    dvmul(r, T);       // rho*T
    scale(1.0/(gamma*(gamma-1.0)),T);
    daxpy(0.5, wk, T);   // E  = e + 0.5 * wk = internal energy
  }

  name.erase(name.find(".rst"));  // erase extension
  sprintf(buf,"%s.dat",name.c_str()); fname = buf;
  // WARNING: should collect all information on the master if parallel...
  if (comm->Master()) U.tecplot(fname,"Solution");
#if 0
  // output to plot3d multi-grid format (should make 3d)
  sprintf(buf,"%s.xyz",name.c_str()); fname = buf;
  if (Process::master()) U.plot3d_xy(fname,"Solution");
  sprintf(buf,"%s.q",name.c_str()); fname = buf;
  if (comm->Master()) U.plot3d_q2(fname,"Solution");
#endif
  compute_vorticity();

  dVector pm;
  for (int k=0; k<Ut[0]->ne; k++) {

    dVector  pp(Ut[1]->el[k]->u);     // p'
    dVector  p(Ut[2]->el[k]->u);      // p

    // mean flow pressure
    pm.alias(work,0,Ut[0]->el[k]->qtot);
    dvmul(Um[0]->el[k]->u,Um[3]->el[k]->u,pm);
    scale(1.0/gamma,pm);

    //scattered pressure
    dvsub(p,pm,pp);
  }
  // WARNING: should collect all information on the master if parallel...
  sprintf(buf,"%s.aux.dat",name.c_str()); fname = buf;
  if (comm->Master()) Ut.tecplot(fname,rst);
  return 0;
}

int Couple::plot(const int &ver) {
  string fname;
  char buf[80];
  read( ver, Up );
  sprintf(buf,"%s.%d.dat",root.c_str(), ver);
  fname = buf;
  if (comm->Master()) U.tecplot(fname,"Solution");
  compute_vorticity();
  sprintf(buf,"%s.aux.%d.dat",root.c_str(), ver);
  fname = buf;
  if (comm->Master()) Ut.tecplot(fname,"Vorticity");
  return 0;

}

// turn off this stuff for now
#ifdef DGM_NOOP

/// Use jump savy gradient on the boundary
#define REO_COUPLE_JUMP

/// Computes lift and drag and saves every time-step
void Couple::write_bndry_stats() {
  static FILE *out = NULL;

  if (!U[0]->bndry_stats->valid) return;

  if (comm->Master()) {
    if (!out) {
      string fname;
      char buf[80];
      sprintf(buf,"%s.frc",root.c_str());
      fname = buf;
      out = fopen(fname.c_str(),"a+");  // append to end of file
    }
  }

  int qtot;
  dVector r, ru, rv, E;

  U[0]->bndry_stats->get_solution( r );
  U[1]->bndry_stats->get_solution( ru );
  U[2]->bndry_stats->get_solution( rv );
  U[3]->bndry_stats->get_solution( E );

  qtot = r.size();
  dVector u(qtot), v(qtot), p(qtot), e(qtot), wk(qtot);

  dvdiv(ru, r, u);   // compute u
  dvdiv(rv, r, v);   // compute v
  dvdiv(E,  r, e);   // internal energy + 0.5 |V|^2

  dvmul(u,u,wk);     // wk = u^2
  dvvtvp(v,v,wk,wk); // wk = u^2 + v^2
  daxpy(-0.5,wk,e);  // e  = e - 0.5 * wk = internal energy

  // p = (gamma-1.0)*(E-0.5*(r*u*u + r*v*v))
  dvmul(u, ru, p);
  dvvtvp(v, rv, p, p);
  scale(-0.5*(gamma-1.0), p);
  daxpy(gamma-1.0, E, p);

  // Compute the stress vector on the boundary
  dVector ru_x, ru_y, rv_x, rv_y, r_x, r_y, temp;
  dVector u_x(qtot), u_y(qtot), v_x(qtot), v_y(qtot);
  dVector tau12(u_y), tau11(v_x), tau22(v_y); // note the alias

#ifdef REO_COUPLE_JUMP
  U.fill_sides();
  enforce_state_bc( U );
  U.share_sides();
  Euler::primitive_sides( U );
  average_flux( U, Ut, '+' );

  Element *S[4], *F[4];
  size_t i;
  int eid, qtott=0, qsid;
  for ( i=0; i<U[0]->bndry_stats->sides.size(); ++i)
    qtott += U[0]->bndry_stats->sides[i]->qtot; // Total number of dof on bnd.

  r_x.resize(qtott) ; r_y.resize(qtott);
  ru_x.resize(qtott); ru_y.resize(qtott);
  rv_x.resize(qtott); rv_y.resize(qtott);

  qtott=0;
  for (i=0; i< U[0]->bndry_stats->sides.size(); i++) {
    eid  = U[0]->bndry_stats->sides[i]->eid;  // Element number on the boundary
    qsid = U[0]->bndry_stats->sides[i]->qtot; // No. quadrature pts on side[i]

    //local version of the state
    S[0] = U[0]->el[eid];
    S[1] = U[1]->el[eid];
    S[2] = U[2]->el[eid];
    S[3] = U[3]->el[eid];
    //local version of the flux
    F[0] = Ut[0]->el[eid];
    F[1] = Ut[1]->el[eid];
    F[2] = Ut[2]->el[eid];
    F[3] = Ut[3]->el[eid];

    qtot = U[0]->el[eid]->qtot;

    dVector pr(S[0]->u), pru(S[1]->u), prv(S[2]->u);  // rho, rhou, and rhov
    dVector pr_x(qtot), pr_y(qtot), pru_x(qtot), pru_y(qtot),
      prv_x(qtot), prv_y(qtot);

    gradient( S[0], F[0], pr,  pr_x,  pr_y );

    temp.alias(r_x,qtott,qsid);
    S[0]->fill_sides(pr_x , U[0]->bndry_stats->sides[i]->id, temp);
    temp.alias(r_y,qtott,qsid);
    S[0]->fill_sides(pr_y , U[0]->bndry_stats->sides[i]->id, temp);

    gradient( S[1], F[1], pru, pru_x, pru_y );

    temp.alias(ru_x,qtott,qsid);
    S[1]->fill_sides(pru_x, U[0]->bndry_stats->sides[i]->id, temp);
    temp.alias(ru_y,qtott,qsid);
    S[1]->fill_sides(pru_y, U[0]->bndry_stats->sides[i]->id, temp);

    gradient( S[2], F[2], prv, prv_x, prv_y );

    temp.alias(rv_x,qtott,qsid);
    S[2]->fill_sides(prv_x, U[0]->bndry_stats->sides[i]->id, temp);
    temp.alias(rv_y,qtott,qsid);
    S[2]->fill_sides(prv_y, U[0]->bndry_stats->sides[i]->id, temp);

    qtott += qsid;
  }
#else
  // No Jump Savy gradient
  U[0]->bndry_stats->get_solution_gradient(r_x, r_y);
  U[1]->bndry_stats->get_solution_gradient(ru_x, ru_y);
  U[2]->bndry_stats->get_solution_gradient(rv_x, rv_y);
#endif

  // Form derivatives of primitive variable in terms of conserved variables
  dvmul ( r_x , u  , u_x );
  dvsub ( ru_x, u_x, u_x );
  dvdiv ( u_x , r  , u_x );

  dvmul ( r_x , v  , v_x );
  dvsub ( rv_x, v_x, v_x );
  dvdiv ( v_x , r  , v_x );

  dvmul ( r_y , u  , u_y );
  dvsub ( ru_y, u_y, u_y );
  dvdiv ( u_y , r  , u_y );

  dvmul ( r_y , v  , v_y );
  dvsub ( rv_y, v_y, v_y );
  dvdiv ( v_y , r  , v_y );

  // Viscous stress:  tau_{ij} = mu ( 2 S_{ij} - 2\delta_{ij}/3 u_{k,k} )

  get_viscosity( wk );             // get viscosity

  dvadd(u_y, v_x, tau12);
  dvmul(wk, tau12);                // mu ( u_{,y} + v_{,x} )

  daxmy(2.0, u_x, v_y, tau11);     // 2 u_{,x} - v_{,y}
  scale(2.0/3.0, tau11);           // 2/3 ( 2 u_{,x} - v_{,y} )
  dvmul(wk, tau11);                // 2/3 mu ( 2 u_{,x} - v_{,y} )

  daxmy(2.0, v_y, u_x, tau22);     // 2 v_{,y} - u_{,x}
  scale(2.0/3.0, tau22);           // 2/3 ( 2 v_{,y} - u_{,x} )
  dvmul(wk, tau22);                // 2/3 mu ( 2 v_{,y} - u_{,x} )

#ifdef DGM_PARALLEL
  Scalar llift=0, ldrag=0;  // local lift and drag
  llift = U[0]->bndry_stats->liftcalc(p,tau12,tau22);
  ldrag = U[0]->bndry_stats->dragcalc(p,tau11,tau12);
  Scalar lift, drag;
  comm->SumAll( &llift, &lift, 1 );
  comm->SumAll( &ldrag, &drag, 1 );
  if (comm->Master()) {
    fprintf(out, "%18.11e %18.11e %18.11e\n", t, drag, lift);
    // fflush(out);
  }
#else
  fprintf(out, "%18.11e %18.11e %18.11e\n", t,
          U[0]->bndry_stats->dragcalc(p,tau11,tau12),
          U[0]->bndry_stats->liftcalc(p,tau12,tau22) );
  fflush(out);
#endif
}

#endif  // DGM_NOOP

void Couple::compute_flux(int q,Point normal,vector<Side *> s,vector<Side *>sm,
                          Scalar *c,Scalar *Un){
  Scalar rhom,lmax;
  Scalar w[4],u[2],rho,T;
  Scalar nx = normal.x;
  Scalar ny = normal.y;
  dVector Fx(4),Fy(4);

  if (s[0]->modeltype==Model::LINEULER) {

    //Un c  --from mean flow
    Un[0] = sm[1]->u[q]*nx +sm[2]->u[q]*ny;
    c[0] =  sqrt(sm[Nfields-1]->u[q]);
    //From solution U

    for(int k=0;k<Nfields;k++) w[k]=s[k]->u[q];
    rho = sm[0]->u[q];
    u[0]= sm[1]->u[q];
    u[1]= sm[2]->u[q];
    T =  sm[3]->u[q];

    Fx[0] = w[1];
    Fx[1] = -3.0/2.0*w[0]*u[0]*u[0]
      +w[0]*u[0]*u[0]*gamma/2.0
      +w[0]*u[1]*u[1]*gamma/2.0-w[0]*u[1]*u[1]/2.0
      +3.0*w[1]*u[0]-w[1]*u[0]*gamma-w[2]*u[1]*gamma
      +w[2]*u[1]+w[3]*gamma-w[3];
    Fx[2] = -u[0]*u[1]*w[0]+u[1]*w[1]+u[0]*w[2];
    Fx[3] = -(3.0*u[0]*u[0]*u[0]*w[0]*gamma
              -2.0*u[0]*u[0]*u[0]*w[0]
              +3.0*u[0]*w[0]*u[1]*u[1]*gamma
              +2.0*u[0]*w[0]*T-2.0*u[0]*w[0]*u[1]*u[1]
              -u[0]*u[0]*u[0]*w[0]*gamma*gamma
              -u[0]*w[0]*u[1]*u[1]*gamma*gamma
              -5.0*w[1]*u[0]*u[0]*gamma+3.0*w[1]*u[0]*u[0]
              -w[1]*u[1]*u[1]*gamma+w[1]*u[1]*u[1]
              -2.0*w[1]*T+2.0*w[1]*u[0]*u[0]*gamma*gamma
              +2.0*u[0]*u[1]*w[2]*gamma*gamma
              -4.0*u[0]*u[1]*w[2]*gamma+2.0*u[0]*u[1]*w[2]
              -2.0*u[0]*gamma*gamma*w[3]
              +2.0*u[0]*gamma*w[3])/(gamma-1.0)/2.0;

    Fy[0] = w[2];
    Fy[1] = -u[0]*u[1]*w[0]+u[1]*w[1]+u[0]*w[2];
    Fy[2] = -3.0/2.0*w[0]*u[1]*u[1] + w[0]*u[0]*u[0]*gamma/2.0
      -w[0]*u[0]*u[0]/2.0+w[0]*u[1]*u[1]*gamma/2.0
      -w[1]*u[0]*gamma+w[1]*u[0]+3.0*w[2]*u[1]-w[2]*u[1]*gamma
      +w[3]*gamma
      -w[3];
    Fy[3] = -(3.0*u[1]*w[0]*u[0]*u[0]*gamma
              -2.0*u[1]*w[0]*u[0]*u[0]
              +3.0*u[1]*u[1]*u[1]*w[0]*gamma + 2.0*u[1]*w[0]*T
              -2.0*u[1]*u[1]*u[1]*w[0]
              -u[1]*w[0]*u[0]*u[0]*gamma*gamma
              -u[1]*u[1]*u[1]*w[0]*gamma*gamma
              +2.0*u[0]*u[1]*w[1]*gamma*gamma
              -4.0*u[0]*u[1]*w[1]*gamma
              + 2.0*u[0]*u[1]*w[1]
              -5.0*w[2]*u[1]*u[1]*gamma+3.0*w[2]*u[1]*u[1]
              -w[2]*u[0]*u[0]*gamma + w[2]*u[0]*u[0]
              -2.0*w[2]*T+2.0*w[2]*u[1]*u[1]*gamma*gamma
              -2.0*u[1]*gamma*gamma*w[3]
              +2.0*u[1]*gamma*w[3])/(gamma-1.0)/2.0;

    s[0]->u[q] = Fx[0]*nx + Fy[0]*ny;
    s[1]->u[q] = Fx[1]*nx + Fy[1]*ny;
    s[2]->u[q] = Fx[2]*nx + Fy[2]*ny;
    s[3]->u[q] = Fx[3]*nx + Fy[3]*ny;


  } else if (s[0]->modeltype==Model::EULER ||
             s[0]->modeltype==Model::NAVIER_STOKES) {

    Scalar rl,ml,nl,El,ul,vl,pl,Hl;

    // normal interior flux
    rl = s[0]->u[q];                   // density
    ml = s[1]->u[q]*nx + s[2]->u[q] *ny;     // normal momentum
    nl = s[2]->u[q]*nx -s[1]->u[q] *ny;     // tangent momentum
    El = s[3]->u[q];                   // total energy per volume

    // local primative variables (projected to normal)
    ul = ml/rl;                                   // normal velocity
    vl = nl/rl;                                   // tangent velocity
    pl = (gamma-1.0)*(El - 0.5*(ml*ul + nl*vl));  // pressure
    Hl = (El + pl)/rl;                            // total enthalpy

    // put the local flux on the state edges
    s[0]->u[q] = rl*ul;
    s[1]->u[q] = (ml*ul+pl)*nx - (nl*ul)*ny;
    s[2]->u[q] = (ml*ul+pl)*ny + (nl*ul)*nx;
    s[3]->u[q] = ul*(El + pl);

    c[0] = sqrt((gamma-1.0)*(Hl - 0.5*(ul*ul + vl*vl)));
    Un[0] = ul;

  } else if (s[0]->modeltype==Model::WAVE) {

    Un[0] = sm[1]->u[q]*nx +sm[2]->u[q]*ny;
    c[0] = sqrt(sm[3]->u[q]);

    for(int k=0;k<(Nfields-1);k++) w[k]=s[k]->u[q];
    rho = sm[0]->u[q];
    u[0]= sm[1]->u[q];
    u[1]= sm[2]->u[q];
    Scalar mC = c[0];

    Fx[0] = w[1];
    Fx[1] = -w[0]*u[0]*u[0]+w[0]*mC*mC+2.0*u[0]*w[1];
    Fx[2] = -u[0]*u[1]*w[0]+u[1]*w[1]+u[0]*w[2];

    Fy[0] = w[2];
    Fy[1] = -u[0]*u[1]*w[0]+u[1]*w[1]+u[0]*w[2];
    Fy[2] = -w[0]*u[1]*u[1]+w[0]*mC*mC+2.0*u[1]*w[2];

    s[0]->u[q] = Fx[0]*nx + Fy[0]*ny;
    s[1]->u[q] = Fx[1]*nx + Fy[1]*ny;
    s[2]->u[q] = Fx[2]*nx + Fy[2]*ny;
  }
}


void Couple::compute_flux1(const iVector id,const dVector& nx_,
                           const dVector& ny_,vector<Side *> s,
                           vector<Side *>sm, dVector& c,dVector& Un){
  Scalar rhom,lmax;
  Scalar w[4],u[2],rho,T;
  dVector Fx(4),Fy(4);

  for(int i=0;i<id.size();i++) {
    int q = id[i];
    Scalar nx = nx_[q];
    Scalar ny = ny_[q];

    if(s[0]->modeltype==Model::LINEULER) {

      Un[q] = sm[1]->u[q]*nx +sm[2]->u[q]*ny;
      c[q] =  sqrt(sm[Nfields-1]->u[q]);

      for(int k=0;k<Nfields;k++) w[k]=s[k]->u[q];
      rho = sm[0]->u[q];
      u[0]= sm[1]->u[q];
      u[1]= sm[2]->u[q];
      T =  sm[3]->u[q];

      Fx[0] = w[1];
      Fx[1] = -3.0/2.0*w[0]*u[0]*u[0]
        +w[0]*u[0]*u[0]*gamma/2.0
        +w[0]*u[1]*u[1]*gamma/2.0-w[0]*u[1]*u[1]/2.0
        +3.0*w[1]*u[0]-w[1]*u[0]*gamma-w[2]*u[1]*gamma
        +w[2]*u[1]+w[3]*gamma-w[3];
      Fx[2] = -u[0]*u[1]*w[0]+u[1]*w[1]+u[0]*w[2];
      Fx[3] = -(3.0*u[0]*u[0]*u[0]*w[0]*gamma
                -2.0*u[0]*u[0]*u[0]*w[0]
                +3.0*u[0]*w[0]*u[1]*u[1]*gamma
                +2.0*u[0]*w[0]*T-2.0*u[0]*w[0]*u[1]*u[1]
                -u[0]*u[0]*u[0]*w[0]*gamma*gamma
                -u[0]*w[0]*u[1]*u[1]*gamma*gamma
                -5.0*w[1]*u[0]*u[0]*gamma+3.0*w[1]*u[0]*u[0]
                -w[1]*u[1]*u[1]*gamma+w[1]*u[1]*u[1]
                -2.0*w[1]*T+2.0*w[1]*u[0]*u[0]*gamma*gamma
                +2.0*u[0]*u[1]*w[2]*gamma*gamma
                -4.0*u[0]*u[1]*w[2]*gamma+2.0*u[0]*u[1]*w[2]
                -2.0*u[0]*gamma*gamma*w[3]
                +2.0*u[0]*gamma*w[3])/(gamma-1.0)/2.0;

      Fy[0] = w[2];
      Fy[1] = -u[0]*u[1]*w[0]+u[1]*w[1]+u[0]*w[2];
      Fy[2] = -3.0/2.0*w[0]*u[1]*u[1] + w[0]*u[0]*u[0]*gamma/2.0
        -w[0]*u[0]*u[0]/2.0+w[0]*u[1]*u[1]*gamma/2.0
        -w[1]*u[0]*gamma+w[1]*u[0]+3.0*w[2]*u[1]-w[2]*u[1]*gamma
        +w[3]*gamma
        -w[3];
      Fy[3] = -(3.0*u[1]*w[0]*u[0]*u[0]*gamma
                -2.0*u[1]*w[0]*u[0]*u[0]
                +3.0*u[1]*u[1]*u[1]*w[0]*gamma + 2.0*u[1]*w[0]*T
                -2.0*u[1]*u[1]*u[1]*w[0]
                -u[1]*w[0]*u[0]*u[0]*gamma*gamma
                -u[1]*u[1]*u[1]*w[0]*gamma*gamma
                +2.0*u[0]*u[1]*w[1]*gamma*gamma
                -4.0*u[0]*u[1]*w[1]*gamma
                + 2.0*u[0]*u[1]*w[1]
                -5.0*w[2]*u[1]*u[1]*gamma+3.0*w[2]*u[1]*u[1]
                -w[2]*u[0]*u[0]*gamma + w[2]*u[0]*u[0]
                -2.0*w[2]*T+2.0*w[2]*u[1]*u[1]*gamma*gamma
                -2.0*u[1]*gamma*gamma*w[3]
                +2.0*u[1]*gamma*w[3])/(gamma-1.0)/2.0;

      s[0]->u[q] = Fx[0]*nx + Fy[0]*ny;
      s[1]->u[q] = Fx[1]*nx + Fy[1]*ny;
      s[2]->u[q] = Fx[2]*nx + Fy[2]*ny;
      s[3]->u[q] = Fx[3]*nx + Fy[3]*ny;


    } else if (s[0]->modeltype==Model::EULER ||
               s[0]->modeltype==Model::NAVIER_STOKES) {

      Scalar rl,ml,nl,El,ul,vl,pl,Hl;

      // normal interior flux
      rl = s[0]->u[q];                   // density
      ml = s[1]->u[q]*nx + s[2]->u[q] *ny;     // normal momentum
      nl = s[2]->u[q]*nx -s[1]->u[q] *ny;     // tangent momentum
      El = s[3]->u[q];                   // total energy per volume

      // local primative variables (projected to normal)
      ul = ml/rl;                                   // normal velocity
      vl = nl/rl;                                   // tangent velocity
      pl = (gamma-1.0)*(El - 0.5*(ml*ul + nl*vl));  // pressure
      Hl = (El + pl)/rl;                            // total enthalpy

      // put the local flux on the state edges
      s[0]->u[q] = rl*ul;
      s[1]->u[q] = (ml*ul+pl)*nx - (nl*ul)*ny;
      s[2]->u[q] = (ml*ul+pl)*ny + (nl*ul)*nx;
      s[3]->u[q] = ul*(El + pl);

      c[q] = sqrt((gamma-1.0)*(Hl - 0.5*(ul*ul + vl*vl)));
      Un[q] = ul;

    } else if(s[0]->modeltype==Model::WAVE) {

      Un[q] = sm[1]->u[q]*nx +sm[2]->u[q]*ny;
      c[q] = sqrt(sm[3]->u[q]);

      for(int k=0;k<(Nfields-1);k++) w[k]=s[k]->u[q];
      rho = sm[0]->u[q];
      u[0]= sm[1]->u[q];
      u[1]= sm[2]->u[q];
      Scalar mC = c[q];

      Fx[0] = w[1];
      Fx[1] = -w[0]*u[0]*u[0]+w[0]*mC*mC+2.0*u[0]*w[1];
      Fx[2] = -u[0]*u[1]*w[0]+u[1]*w[1]+u[0]*w[2];

      Fy[0] = w[2];
      Fy[1] = -u[0]*u[1]*w[0]+u[1]*w[1]+u[0]*w[2];
      Fy[2] = -w[0]*u[1]*u[1]+w[0]*mC*mC+2.0*u[1]*w[2];

      s[0]->u[q] = Fx[0]*nx + Fy[0]*ny;
      s[1]->u[q] = Fx[1]*nx + Fy[1]*ny;
      s[2]->u[q] = Fx[2]*nx + Fy[2]*ny;

    }
  }
}

#endif


#if 0
//compute the flux along the edge using the function call
void Couple::convective_flux(vField &Us, vField &Uf) {
  flux_type flux = LaxFriedrichs;
  int qtot, qr, ql;
  Scalar nx, ny;
  dVector  f(Nfields), U(Nfields), Ua(Nfields);
  Scalar rl, ml, nl, El, vl, pl, Hl, Ml;
  Scalar rr, mr, nr, Er, vr, pr, Hr, Mr;
  vector<Side *> Ssl(Nfields), Ssr(Nfields);
  vector<Side *> Sfl(Nfields), Sfr(Nfields);
  Scalar fpl[4], fmr[4], lmax;
  dVector lam(Nfields);
  iVector mapl, mapr;

  int nfields;

  Scalar rho,u[2],T,p,w[4];
  Scalar rhop,up,vp;

  //Variables for the coupling edges
  vector<Side *> Asl(Nfields), Asr(Nfields);

  dVector fplA(Nfields), fmrA(Nfields),fA(Nfields);
  dVector ul,cl,ur,cr, ulA,clA,urA,crA;
  vector<Side *> Sml(Nfields), Smr(Nfields); //mean flow field edge --cgq
#if 0
  vector<Scalar> sl(Nfields), sr(Nfields),slA(Nfields), srA(Nfields);
#else
  dVector sl[4], sr[4],slA[4], srA[4];
#endif

  for (int e=0; e<Us[0]->ne; e++) {                 // loop over elements
    for (int i=0; i<Us[0]->el[e]->nSides(); i++) {  // loop over sides
      if (Us[0]->el[e]->side[i]->master()) {        // only if master
        qtot = Us[0]->el[e]->side[i]->qtot();       // quad pts on side
        nfields = Nfields;

        for (int ni=0; ni<nfields; ni++) {
          Ssl[ni] = Us[ni]->el[e]->side[i];        // local state side
          Ssr[ni] = Us[ni]->el[e]->side[i]->link;  // adjacent state side
          Sfl[ni] = Uf[ni]->el[e]->side[i];        // local flux side
          Sfr[ni] = Uf[ni]->el[e]->side[i]->link;  // adjacent flux side
          Sml[ni] = Um[ni]->el[e]->side[i];        // local mean side
          Smr[ni] = Um[ni]->el[e]->side[i]->link;  // adjacent mean side
        }

        get_side_maps( Ssl[0], Ssr[0], mapl, mapr );

         /* Here for those edges adjacent with the coupling surfaces,the
           upwind flux for the two adjacent edges will be computed,
           respectively.different from before (F_adj = -F_loc). We will
           create two edges for Sfl and Sfr */

        if(Ssl[0]->modeltype != Ssr[0]->modeltype ) {
          for (int ni=0; ni<nfields; ni++) {
            Asl[ni] = new Side(Ssl[ni]);
            Asr[ni] = new Side(Ssr[ni]);
          }
          convert_sides(Asl,Sml,
                        Asl[0]->modeltype,Ssr[0]->modeltype);
          convert_sides(Asr,Smr,
                        Asr[0]->modeltype,Ssl[0]->modeltype);
        }

        dVector &nx_  = Us[0]->el[e]->side[i]->nx();  // side normal
        dVector &ny_  = Us[0]->el[e]->side[i]->ny();  // side normal

        ul.resize(qtot);
        cl.resize(qtot);
        ulA.resize(qtot);
        clA.resize(qtot);
        for(int k=0;k<nfields;k++){
          sl[k].resize(qtot);
          sr[k].resize(qtot);
          slA[k].resize(qtot);
          srA[k].resize(qtot);
        }
        // compute normal flux from interior (left)

        //From solution U
        for(int k=0;k<nfields;k++)
          sl[k] = Ssl[k]->u; //ql

        compute_flux1(mapl,nx_,ny_,Ssl,Sml,cl,ul);

        if( Ssl[0]->modeltype != Ssr[0]->modeltype) {
          for(int k=0;k<nfields;k++)
            slA[k] = Asl[k]->u;
          compute_flux1(mapl,nx_,ny_,Asl,Sml,clA,ulA);
        }

        // compute normal flux from exterior (right)

        ur.resize(qtot);
        cr.resize(qtot);
        urA.resize(qtot);
        crA.resize(qtot);

        // adjacent state
        for(int k=0;k<nfields;k++)
          sr[k] = Ssr[k]->u;

        compute_flux1(mapr,nx_,ny_,Ssr,Smr,cr,ur);


        if( Ssl[0]->modeltype != Ssr[0]->modeltype) {
          for(int k=0;k<nfields;k++)
            srA[k] = Asr[k]->u;
          compute_flux1(mapr,nx_,ny_,Asr,Smr,crA,urA);
        }

        for (int q=0; q<qtot; q++) {         // loop over side quad-pts

          ql = mapl[q];
          qr = mapr[q];

          switch (flux) {
          case LaxFriedrichs:

            //Possible problem for Wave (no mean flow OK!),
            // should be fixed later  not true for Wave(field 3,not 4)!!!
            if( Ssl[0]->modeltype == Ssr[0]->modeltype) {
              lmax=0;
              lam[0] = ul[ql];
              lam[1] = ul[ql]+cl[ql];
              lam[2] = ul[ql]-cl[ql];
              lam[3] = ul[ql];
              // left flux
              for(int j=0; j<nfields;j++) {
                lmax=max(lmax,fabs(lam[j]));
                fpl[j] = Ssl[j]->u[ql];
              }

              lam[0] = ur[qr];
              lam[1] = ur[qr]+cr[qr];
              lam[2] = ur[qr]-cr[qr];
              lam[3] = ur[qr];

              for(int j=0; j<nfields; j++) {
                lmax=max(lmax,fabs(lam[j]));
                fmr[j] = Ssr[j]->u[qr];
              }
              // Lax-Friedrichs flux
              for(int j=0; j<nfields; j++)
                f[j] = 0.5 *( fpl[j] + fmr[j] + lmax * ( sl[j][q] - sr[j][q]));

            } else  //coupling edge
              {

                lmax=0;
                lam[0] = ul[ql];
                lam[1] = ul[ql]+cl[ql];
                lam[2] = ul[ql]-cl[ql];
                lam[3] = ul[ql];
                // left flux
                for(int j=0; j<nfields;j++) {
                  lmax=max(lmax,fabs(lam[j]));
                  fpl[j] = Ssl[j]->u[ql];
                }

                lam[0] = urA[qr];
                lam[1] = urA[qr]+crA[qr];
                lam[2] = urA[qr]-crA[qr];
                lam[3] = urA[qr];
                // left flux
                for(int j=0; j<nfields;j++) {
                  lmax=max(lmax,fabs(lam[j]));
                  fmrA[j] = Asr[j]->u[qr];
                }

                // Lax-Friedrichs flux for local
                for(int j=0; j<nfields; j++)
                  f[j] = 0.5 * ( fpl[j] + fmrA[j]
                                 + lmax * ( sl[j][q] - srA[j][q]));

                lmax=0;
                lam[0] = ulA[ql];
                lam[1] = ulA[ql]+clA[ql];
                lam[2] = ulA[ql]-clA[ql];
                lam[3] = ulA[ql];
                // left flux
                for(int j=0; j<nfields;j++) {
                  lmax=max(lmax,fabs(lam[j]));
                  fplA[j] = Asl[j]->u[ql];
                }

                lam[0] = ur[qr];
                lam[1] = ur[qr]+cr[qr];
                lam[2] = ur[qr]-cr[qr];
                lam[3] = ur[qr];

                for(int j=0; j<nfields; j++) {
                  lmax=max(lmax,fabs(lam[j]));
                  fmr[j] = Ssr[j]->u[qr];
                }

                // Lax-Friedrichs flux for adjacent
                for(int j=0; j<nfields; j++)
                  fA[j] = 0.5 * ( fplA[j] + fmr[j]
                                  + lmax * ( slA[j][q] - sr[j][q]));

              }

            break;
          case vanLeer:
          case StegerWarming:
          case Roe:                                  // Roe average
            cerr << "Those flux types haven't been"
                 <<" implemented yet for coupling problem" << endl;
            comm->exit(DGM::FAILURE);
            break;
          default:
            cerr << "Illegal value of flux type" << endl;
            comm->exit(DGM::FAILURE);
          }

          // put fluxes on flux field sides
          for (int ni=0; ni<nfields; ni++) {
            if(Ssl[0]->modeltype==Ssr[0]->modeltype) {
              Ssr[ni]->u[qr] *= -1.0;         // correct for normal
              Sfl[ni]->u[ql]  =  f[ni];
              Sfr[ni]->u[qr]  = -f[ni];

            }else {
              Ssr[ni]->u[qr] *= -1.0;         // correct for normal
              Sfl[ni]->u[ql]  =  f[ni];
              Sfr[ni]->u[qr]  = -fA[ni];

            }
          }
        }

        //delete the auxiliary Sides
        if(Ssl[0]->modeltype != Ssr[0]->modeltype ) {
          for (int ni=0; ni<nfields; ni++) {
            delete Asl[ni];
            delete Asr[ni];
          }
        }

      }
    }
  }
}
#endif

#if 0
//compute the flux along the edge point direct, NOT using the function call
void Couple::convective_flux(vField &Us, vField &Uf) {
  flux_type flux = LaxFriedrichs;
  int qtot, qr, ql;
  Scalar nx, ny;
  dVector sl(Nfields), sr(Nfields), f(Nfields), U(Nfields), Ua(Nfields);
  Scalar rl, ml, nl, El, ul, vl, pl, Hl, Ml, cl;
  Scalar rr, mr, nr, Er, ur, vr, pr, Hr, Mr, cr;
  vector<Side *> Ssl(Nfields), Ssr(Nfields);
  vector<Side *> Sfl(Nfields), Sfr(Nfields);
  Scalar fpl[4], fmr[4], lmax;
  dVector lam(Nfields);
  iVector mapl, mapr;

  int nfields;

  Scalar rho,u[2],T,p,w[4];
  Scalar rhop,up,vp;

  // Variables for the coupling edges
  vector<Side *> Asl(Nfields), Asr(Nfields);
  dVector slA(Nfields), srA(Nfields);
  dVector fplA(Nfields), fmrA(Nfields),fA(Nfields);
  Scalar ulA,clA,urA,crA;
  vector<Side *> Sml(Nfields), Smr(Nfields); //mean flow field edge
  dVector Fx(4),Fy(4);

  for (int e=0; e<Us[0]->ne; e++) {                 // loop over elements
    for (int i=0; i<Us[0]->el[e]->nSides(); i++) {  // loop over sides
      if (Us[0]->el[e]->side[i]->master()) {        // only if master
        qtot = Us[0]->el[e]->side[i]->qtot();       // quad pts on side

        nfields = Nfields;

        for (int ni=0; ni<nfields; ni++) {
          Ssl[ni] = Us[ni]->el[e]->side[i];        // local state side
          Ssr[ni] = Us[ni]->el[e]->side[i]->link;  // adjacent state side
          Sfl[ni] = Uf[ni]->el[e]->side[i];        // local flux side
          Sfr[ni] = Uf[ni]->el[e]->side[i]->link;  // adjacent flux side
          Sml[ni] = Um[ni]->el[e]->side[i];        // local mean side
          Smr[ni] = Um[ni]->el[e]->side[i]->link;  // adjacent mean side
        }

        get_side_maps( Ssl[0], Ssr[0], mapl, mapr );

        /* Here for those edges adjacent with the coupling surfaces,the
           upwind flux for the two adjacent edges will be computed,
           respectively.different from before (F_adj = -F_loc). We will
           create two edges for Sfl and Sfr */

        if(Ssl[0]->modeltype != Ssr[0]->modeltype ) {
          for (int ni=0; ni<nfields; ni++) {
            Asl[ni] = new Side(Ssl[ni]);
            Asr[ni] = new Side(Ssr[ni]);
          }
          convert_sides(Asl,Sml,
                        Asl[0]->modeltype,Ssr[0]->modeltype);
          convert_sides(Asr,Smr,
                        Asr[0]->modeltype,Ssl[0]->modeltype);
        }

        for (int q=0; q<qtot; q++) {         // loop over side quad-pts

          ql = mapl[q];
          qr = mapr[q];

          nx = Us[0]->el[e]->side[i]->nx(ql);  // side normal
          ny = Us[0]->el[e]->side[i]->ny(ql);  // side normal

          // compute normal flux from interior (left)

          // From solution U
          for(int k=0;k<nfields;k++)
            sl[k] = Ssl[k]->u[ql];

          if(Ssl[0]->modeltype==Model::LINEULER) {

            // Un c  --from mean flow
            ul = Sml[1]->u[ql]*nx +Sml[2]->u[ql]*ny;
            cl =  sqrt(Sml[Nfields-1]->u[ql]);

            // From solution U
            for(int k=0;k<Nfields;k++) w[k]=Ssl[k]->u[ql];
            rho = Sml[0]->u[ql];
            u[0]= Sml[1]->u[ql];
            u[1]= Sml[2]->u[ql];
            T   = Sml[3]->u[ql];

            Fx[0] = w[1];
            Fx[1] = -3.0/2.0*w[0]*u[0]*u[0]
              +w[0]*u[0]*u[0]*gamma/2.0
              +w[0]*u[1]*u[1]*gamma/2.0-w[0]*u[1]*u[1]/2.0
              +3.0*w[1]*u[0]-w[1]*u[0]*gamma-w[2]*u[1]*gamma
              +w[2]*u[1]+w[3]*gamma-w[3];
            Fx[2] = -u[0]*u[1]*w[0]+u[1]*w[1]+u[0]*w[2];
            Fx[3] = -(3.0*u[0]*u[0]*u[0]*w[0]*gamma
                      -2.0*u[0]*u[0]*u[0]*w[0]
                      +3.0*u[0]*w[0]*u[1]*u[1]*gamma
                      +2.0*u[0]*w[0]*T-2.0*u[0]*w[0]*u[1]*u[1]
                      -u[0]*u[0]*u[0]*w[0]*gamma*gamma
                      -u[0]*w[0]*u[1]*u[1]*gamma*gamma
                      -5.0*w[1]*u[0]*u[0]*gamm+3.0*w[1]*u[0]*u[0]
                      -w[1]*u[1]*u[1]*gamma+w[1]*u[1]*u[1]
                      -2.0*w[1]*T+2.0*w[1]*u[0]*u[0]*gamma*gamma
                      +2.0*u[0]*u[1]*w[2]*gamma*gamma
                      -4.0*u[0]*u[1]*w[2]*gamma+2.0*u[0]*u[1]*w[2]
                      -2.0*u[0]*gamma*gamma*w[3]
                      +2.0*u[0]*gamma*w[3])/(gamma-1.0)/2.0;

            Fy[0] = w[2];
            Fy[1] = -u[0]*u[1]*w[0]+u[1]*w[1]+u[0]*w[2];
            Fy[2] = -3.0/2.0*w[0]*u[1]*u[1] + w[0]*u[0]*u[0]*gamma/2.0
              -w[0]*u[0]*u[0]/2.0+w[0]*u[1]*u[1]*gamma/2.0
              -w[1]*u[0]*gamma+w[1]*u[0]+3.0*w[2]*u[1]-w[2]*u[1]*gamma
              +w[3]*gamma
              -w[3];
            Fy[3] = -(3.0*u[1]*w[0]*u[0]*u[0]*gamma
                      -2.0*u[1]*w[0]*u[0]*u[0]
                      +3.0*u[1]*u[1]*u[1]*w[0]*gamma + 2.0*u[1]*w[0]*T
                      -2.0*u[1]*u[1]*u[1]*w[0]
                      -u[1]*w[0]*u[0]*u[0]*gamma*gamma
                      -u[1]*u[1]*u[1]*w[0]*gamma*gamma
                      +2.0*u[0]*u[1]*w[1]*gamma*gamma
                      -4.0*u[0]*u[1]*w[1]*gamma
                      + 2.0*u[0]*u[1]*w[1]
                      -5.0*w[2]*u[1]*u[1]*gamma+3.0*w[2]*u[1]*u[1]
                      -w[2]*u[0]*u[0]*gamma + w[2]*u[0]*u[0]
                      -2.0*w[2]*T+2.0*w[2]*u[1]*u[1]*gamma*gamma
                      -2.0*u[1]*gamma*gamma*w[3]
                      +2.0*u[1]*gamma*w[3])/(gamma-1.0)/2.0;

            Ssl[0]->u[ql] = Fx[0]*nx + Fy[0]*ny;
            Ssl[1]->u[ql] = Fx[1]*nx + Fy[1]*ny;
            Ssl[2]->u[ql] = Fx[2]*nx + Fy[2]*ny;
            Ssl[3]->u[ql] = Fx[3]*nx + Fy[3]*ny;

          } else if (Ssl[0]->modeltype==Model::EULER ||
                     Ssl[0]->modeltype==Model::NAVIER_STOKES) {

            Scalar rl,ml,nl,El,vl,pl,Hl;

            // normal interior flux
            rl = Ssl[0]->u[ql];                   // density
            ml = Ssl[1]->u[ql]*nx + Ssl[2]->u[ql] *ny; // normal momentum
            nl = Ssl[2]->u[ql]*nx -Ssl[1]->u[ql] *ny; // tangent momentum
            El = Ssl[3]->u[ql];                   // total energy per volume

            // local primative variables (projected to normal)
            ul = ml/rl;                                   // normal velocity
            vl = nl/rl;                                   // tangent velocity
            pl = (gamma-1.0)*(El - 0.5*(ml*ul + nl*vl));  // pressure
            Hl = (El + pl)/rl;                            // total enthalpy

            // put the local flux on the state edges
            Ssl[0]->u[ql] = rl*ul;
            Ssl[1]->u[ql] = (ml*ul+pl)*nx - (nl*ul)*ny;
            Ssl[2]->u[ql] = (ml*ul+pl)*ny + (nl*ul)*nx;
            Ssl[3]->u[ql] = ul*(El + pl);

            cl = sqrt((gamma-1.0)*(Hl - 0.5*(ul*ul + vl*vl)));

          }else if(Ssl[0]->modeltype==Model::WAVE) {

            ul = Sml[1]->u[ql]*nx +Sml[2]->u[ql]*ny;
            cl = sqrt(Sml[3]->u[ql]);

            for(int k=0;k<(Nfields-1);k++) w[k]=Ssl[k]->u[ql];
            rho = Sml[0]->u[ql];
            u[0]= Sml[1]->u[ql];
            u[1]= Sml[2]->u[ql];
            Scalar mC = cl;

            Fx[0] = w[1];
            Fx[1] = -w[0]*u[0]*u[0]+w[0]*mC*mC+2.0*u[0]*w[1];
            Fx[2] = -u[0]*u[1]*w[0]+u[1]*w[1]+u[0]*w[2];

            Fy[0] = w[2];
            Fy[1] = -u[0]*u[1]*w[0]+u[1]*w[1]+u[0]*w[2];
            Fy[2] = -w[0]*u[1]*u[1]+w[0]*mC*mC+2.0*u[1]*w[2];

            Ssl[0]->u[ql] = Fx[0]*nx + Fy[0]*ny;
            Ssl[1]->u[ql] = Fx[1]*nx + Fy[1]*ny;
            Ssl[2]->u[ql] = Fx[2]*nx + Fy[2]*ny;

          }

          if( Ssl[0]->modeltype != Ssr[0]->modeltype) {
            for(int k=0;k<nfields;k++)
              slA[k] = Asl[k]->u[ql];

            if(Asl[0]->modeltype==Model::LINEULER) {

              //Un c  --from mean flow
              ulA = Sml[1]->u[ql]*nx +Sml[2]->u[ql]*ny;
              clA =  sqrt(Sml[Nfields-1]->u[ql]);

              //From solution U
              for(int k=0;k<Nfields;k++) w[k]=Asl[k]->u[ql];
              rho = Sml[0]->u[ql];
              u[0]= Sml[1]->u[ql];
              u[1]= Sml[2]->u[ql];
              T   = Sml[3]->u[ql];

              Fx[0] = w[1];
              Fx[1] = -3.0/2.0*w[0]*u[0]*u[0]
                +w[0]*u[0]*u[0]*gamma/2.0
                +w[0]*u[1]*u[1]*gamma/2.0-w[0]*u[1]*u[1]/2.0
                +3.0*w[1]*u[0]-w[1]*u[0]*gamma-w[2]*u[1]*gamma
                +w[2]*u[1]+w[3]*gamma-w[3];
              Fx[2] = -u[0]*u[1]*w[0]+u[1]*w[1]+u[0]*w[2];
              Fx[3] = -(3.0*u[0]*u[0]*u[0]*w[0]*gamma
                        -2.0*u[0]*u[0]*u[0]*w[0]
                        +3.0*u[0]*w[0]*u[1]*u[1]*gamma
                        +2.0*u[0]*w[0]*T-2.0*u[0]*w[0]*u[1]*u[1]
                        -u[0]*u[0]*u[0]*w[0]*gamma*gamma
                        -u[0]*w[0]*u[1]*u[1]*gamma*gamma
                        -5.0*w[1]*u[0]*u[0]*gamm+3.0*w[1]*u[0]*u[0]
                        -w[1]*u[1]*u[1]*gamma+w[1]*u[1]*u[1]
                        -2.0*w[1]*T+2.0*w[1]*u[0]*u[0]*gamma*gamma
                        +2.0*u[0]*u[1]*w[2]*gamma*gamma
                        -4.0*u[0]*u[1]*w[2]*gamma+2.0*u[0]*u[1]*w[2]
                        -2.0*u[0]*gamma*gamma*w[3]
                        +2.0*u[0]*gamma*w[3])/(gamma-1.0)/2.0;

              Fy[0] = w[2];
              Fy[1] = -u[0]*u[1]*w[0]+u[1]*w[1]+u[0]*w[2];
              Fy[2] = -3.0/2.0*w[0]*u[1]*u[1] + w[0]*u[0]*u[0]*gamma/2.0
                -w[0]*u[0]*u[0]/2.0+w[0]*u[1]*u[1]*gamma/2.0
                -w[1]*u[0]*gamma+w[1]*u[0]+3.0*w[2]*u[1]-w[2]*u[1]*gamma
                +w[3]*gamma
                -w[3];
              Fy[3] = -(3.0*u[1]*w[0]*u[0]*u[0]*gamma
                        -2.0*u[1]*w[0]*u[0]*u[0]
                        +3.0*u[1]*u[1]*u[1]*w[0]*gamma + 2.0*u[1]*w[0]*T
                        -2.0*u[1]*u[1]*u[1]*w[0]
                        -u[1]*w[0]*u[0]*u[0]*gamma*gamma
                        -u[1]*u[1]*u[1]*w[0]*gamma*gamma
                        +2.0*u[0]*u[1]*w[1]*gamma*gamma
                        -4.0*u[0]*u[1]*w[1]*gamma
                        + 2.0*u[0]*u[1]*w[1]
                        -5.0*w[2]*u[1]*u[1]*gamma+3.0*w[2]*u[1]*u[1]
                        -w[2]*u[0]*u[0]*gamma + w[2]*u[0]*u[0]
                        -2.0*w[2]*T+2.0*w[2]*u[1]*u[1]*gamma*gamma
                        -2.0*u[1]*gamma*gamma*w[3]
                        +2.0*u[1]*gamma*w[3])/(gamma-1.0)/2.0;

              Asl[0]->u[ql] = Fx[0]*nx + Fy[0]*ny;
              Asl[1]->u[ql] = Fx[1]*nx + Fy[1]*ny;
              Asl[2]->u[ql] = Fx[2]*nx + Fy[2]*ny;
              Asl[3]->u[ql] = Fx[3]*nx + Fy[3]*ny;

            } else if (Asl[0]->modeltype==Model::EULER ||
                       Asl[0]->modeltype==Model::NAVIER_STOKES) {

              Scalar rl,ml,nl,El,vl,pl,Hl;

              // normal interior flux
              rl = Asl[0]->u[ql];                   // density
              // normal momentum
              ml = Asl[1]->u[ql]*nx + Asl[2]->u[ql] *ny;
              // tangent momentum
              nl = Asl[2]->u[ql]*nx -Asl[1]->u[ql] *ny;
              El = Asl[3]->u[ql];      // total energy per volume

              // local primative variables (projected to normal)
              ul = ml/rl;                                   // normal velocity
              vl = nl/rl;                                   // tangent velocity
              pl = (gamma-1.0)*(El - 0.5*(ml*ul + nl*vl));  // pressure
              Hl = (El + pl)/rl;                            // total enthalpy

              // put the local flux on the state edges
              Asl[0]->u[ql] = rl*ul;
              Asl[1]->u[ql] = (ml*ul+pl)*nx - (nl*ul)*ny;
              Asl[2]->u[ql] = (ml*ul+pl)*ny + (nl*ul)*nx;
              Asl[3]->u[ql] = ul*(El + pl);

              clA = sqrt((gamma-1.0)*(Hl - 0.5*(ul*ul + vl*vl)));
              ulA = ul;

            } else if(Asl[0]->modeltype==Model::WAVE) {

              ulA = Sml[1]->u[ql]*nx +Sml[2]->u[ql]*ny;
              clA = sqrt(Sml[3]->u[ql]);

              for(int k=0;k<(Nfields-1);k++) w[k]=Asl[k]->u[ql];
              rho = Sml[0]->u[ql];
              u[0]= Sml[1]->u[ql];
              u[1]= Sml[2]->u[ql];
              Scalar mC = clA;

              Fx[0] = w[1];
              Fx[1] = -w[0]*u[0]*u[0]+w[0]*mC*mC+2.0*u[0]*w[1];
              Fx[2] = -u[0]*u[1]*w[0]+u[1]*w[1]+u[0]*w[2];

              Fy[0] = w[2];
              Fy[1] = -u[0]*u[1]*w[0]+u[1]*w[1]+u[0]*w[2];
              Fy[2] = -w[0]*u[1]*u[1]+w[0]*mC*mC+2.0*u[1]*w[2];

              Asl[0]->u[ql] = Fx[0]*nx + Fy[0]*ny;
              Asl[1]->u[ql] = Fx[1]*nx + Fy[1]*ny;
              Asl[2]->u[ql] = Fx[2]*nx + Fy[2]*ny;

            }
          }

          // compute normal flux from exterior (right)

          // adjacent state
          for(int k=0;k<nfields;k++)
            sr[k] = Ssr[k]->u[qr];

          if(Ssr[0]->modeltype==Model::LINEULER) {

            // Un c  --from mean flow
            ur = Smr[1]->u[qr]*nx +Smr[2]->u[qr]*ny;
            cr =  sqrt(Smr[Nfields-1]->u[qr]);

            // From solution U
            for(int k=0;k<Nfields;k++) w[k]=Ssr[k]->u[qr];
            rho = Smr[0]->u[qr];
            u[0]= Smr[1]->u[qr];
            u[1]= Smr[2]->u[qr];
            T   = Smr[3]->u[qr];

            Fx[0] = w[1];
            Fx[1] = -3.0/2.0*w[0]*u[0]*u[0]
              +w[0]*u[0]*u[0]*gamma/2.0
              +w[0]*u[1]*u[1]*gamma/2.0-w[0]*u[1]*u[1]/2.0
              +3.0*w[1]*u[0]-w[1]*u[0]*gamma-w[2]*u[1]*gamma
              +w[2]*u[1]+w[3]*gamma-w[3];
            Fx[2] = -u[0]*u[1]*w[0]+u[1]*w[1]+u[0]*w[2];
            Fx[3] = -(3.0*u[0]*u[0]*u[0]*w[0]*gamma
                      -2.0*u[0]*u[0]*u[0]*w[0]
                      +3.0*u[0]*w[0]*u[1]*u[1]*gamma
                      +2.0*u[0]*w[0]*T-2.0*u[0]*w[0]*u[1]*u[1]
                      -u[0]*u[0]*u[0]*w[0]*gamma*gamma
                      -u[0]*w[0]*u[1]*u[1]*gamma*gamma
                      -5.0*w[1]*u[0]*u[0]*gamm+3.0*w[1]*u[0]*u[0]
                      -w[1]*u[1]*u[1]*gamma+w[1]*u[1]*u[1]
                      -2.0*w[1]*T+2.0*w[1]*u[0]*u[0]*gamma*gamma
                      +2.0*u[0]*u[1]*w[2]*gamma*gamma
                      -4.0*u[0]*u[1]*w[2]*gamma+2.0*u[0]*u[1]*w[2]
                      -2.0*u[0]*gamma*gamma*w[3]
                      +2.0*u[0]*gamma*w[3])/(gamma-1.0)/2.0;

            Fy[0] = w[2];
            Fy[1] = -u[0]*u[1]*w[0]+u[1]*w[1]+u[0]*w[2];
            Fy[2] = -3.0/2.0*w[0]*u[1]*u[1] + w[0]*u[0]*u[0]*gamma/2.0
              -w[0]*u[0]*u[0]/2.0+w[0]*u[1]*u[1]*gamma/2.0
              -w[1]*u[0]*gamma+w[1]*u[0]+3.0*w[2]*u[1]-w[2]*u[1]*gamma
              +w[3]*gamma
              -w[3];
            Fy[3] = -(3.0*u[1]*w[0]*u[0]*u[0]*gamma
                      -2.0*u[1]*w[0]*u[0]*u[0]
                      +3.0*u[1]*u[1]*u[1]*w[0]*gamma + 2.0*u[1]*w[0]*T
                      -2.0*u[1]*u[1]*u[1]*w[0]
                      -u[1]*w[0]*u[0]*u[0]*gamma*gamma
                      -u[1]*u[1]*u[1]*w[0]*gamma*gamma
                      +2.0*u[0]*u[1]*w[1]*gamma*gamma
                      -4.0*u[0]*u[1]*w[1]*gamma
                      + 2.0*u[0]*u[1]*w[1]
                      -5.0*w[2]*u[1]*u[1]*gamma+3.0*w[2]*u[1]*u[1]
                      -w[2]*u[0]*u[0]*gamma + w[2]*u[0]*u[0]
                      -2.0*w[2]*T+2.0*w[2]*u[1]*u[1]*gamma*gamma
                      -2.0*u[1]*gamma*gamma*w[3]
                      +2.0*u[1]*gamma*w[3])/(gamma-1.0)/2.0;

            Ssr[0]->u[qr] = Fx[0]*nx + Fy[0]*ny;
            Ssr[1]->u[qr] = Fx[1]*nx + Fy[1]*ny;
            Ssr[2]->u[qr] = Fx[2]*nx + Fy[2]*ny;
            Ssr[3]->u[qr] = Fx[3]*nx + Fy[3]*ny;

          } else if (Ssr[0]->modeltype==Model::EULER ||
                     Ssr[0]->modeltype==Model::NAVIER_STOKES) {

            Scalar rl,ml,nl,El,vl,pl,Hl;

            // normal interior flux
            rl = Ssr[0]->u[qr];                   // density
            // normal momentum
            ml = Ssr[1]->u[qr]*nx + Ssr[2]->u[qr] *ny;
            // tangent momentum
            nl = Ssr[2]->u[qr]*nx -Ssr[1]->u[qr] *ny;
            El = Ssr[3]->u[qr];                   // total energy per volume

            // local primative variables (projected to normal)
            ul = ml/rl;                                   // normal velocity
            vl = nl/rl;                                   // tangent velocity
            pl = (gamma-1.0)*(El - 0.5*(ml*ul + nl*vl));  // pressure
            Hl = (El + pl)/rl;                            // total enthalpy

            // put the local flux on the state edges
            Ssr[0]->u[qr] = rl*ul;
            Ssr[1]->u[qr] = (ml*ul+pl)*nx - (nl*ul)*ny;
            Ssr[2]->u[qr] = (ml*ul+pl)*ny + (nl*ul)*nx;
            Ssr[3]->u[qr] = ul*(El + pl);

            cr = sqrt((gamma-1.0)*(Hl - 0.5*(ul*ul + vl*vl)));
            ur = ul;

          } else if(Ssr[0]->modeltype==Model::WAVE) {

            ur = Smr[1]->u[qr]*nx +Smr[2]->u[qr]*ny;
            cr = sqrt(Smr[3]->u[qr]);

            for(int k=0;k<(Nfields-1);k++) w[k]=Asr[k]->u[qr];
            rho = Smr[0]->u[qr];
            u[0]= Smr[1]->u[qr];
            u[1]= Smr[2]->u[qr];
            Scalar mC = cr;

            Fx[0] = w[1];
            Fx[1] = -w[0]*u[0]*u[0]+w[0]*mC*mC+2.0*u[0]*w[1];
            Fx[2] = -u[0]*u[1]*w[0]+u[1]*w[1]+u[0]*w[2];

            Fy[0] = w[2];
            Fy[1] = -u[0]*u[1]*w[0]+u[1]*w[1]+u[0]*w[2];
            Fy[2] = -w[0]*u[1]*u[1]+w[0]*mC*mC+2.0*u[1]*w[2];

            Ssr[0]->u[qr] = Fx[0]*nx + Fy[0]*ny;
            Ssr[1]->u[qr] = Fx[1]*nx + Fy[1]*ny;
            Ssr[2]->u[qr] = Fx[2]*nx + Fy[2]*ny;

          }

          if( Ssl[0]->modeltype != Ssr[0]->modeltype) {
            for(int k=0;k<nfields;k++)
              srA[k] = Asr[k]->u[qr];

            if(Asr[0]->modeltype==Model::LINEULER) {

              // Un c  --from mean flow
              urA = Smr[1]->u[qr]*nx +Smr[2]->u[qr]*ny;
              crA =  sqrt(Smr[Nfields-1]->u[qr]);

              // From solution U

              for(int k=0;k<Nfields;k++) w[k]=Ssr[k]->u[qr];
              rho = Smr[0]->u[qr];
              u[0]= Smr[1]->u[qr];
              u[1]= Smr[2]->u[qr];
              T   = Smr[3]->u[qr];

              Fx[0] = w[1];
              Fx[1] = -3.0/2.0*w[0]*u[0]*u[0]
                +w[0]*u[0]*u[0]*gamma/2.0
                +w[0]*u[1]*u[1]*gamma/2.0-w[0]*u[1]*u[1]/2.0
                +3.0*w[1]*u[0]-w[1]*u[0]*gamma-w[2]*u[1]*gamma
                +w[2]*u[1]+w[3]*gamma-w[3];
              Fx[2] = -u[0]*u[1]*w[0]+u[1]*w[1]+u[0]*w[2];
              Fx[3] = -(3.0*u[0]*u[0]*u[0]*w[0]*gamma
                        -2.0*u[0]*u[0]*u[0]*w[0]
                        +3.0*u[0]*w[0]*u[1]*u[1]*gamma
                        +2.0*u[0]*w[0]*T-2.0*u[0]*w[0]*u[1]*u[1]
                        -u[0]*u[0]*u[0]*w[0]*gamma*gamma
                        -u[0]*w[0]*u[1]*u[1]*gamma*gamma
                        -5.0*w[1]*u[0]*u[0]*gamm+3.0*w[1]*u[0]*u[0]
                        -w[1]*u[1]*u[1]*gamma+w[1]*u[1]*u[1]
                        -2.0*w[1]*T+2.0*w[1]*u[0]*u[0]*gamma*gamma
                        +2.0*u[0]*u[1]*w[2]*gamma*gamma
                        -4.0*u[0]*u[1]*w[2]*gamma+2.0*u[0]*u[1]*w[2]
                        -2.0*u[0]*gamma*gamma*w[3]
                        +2.0*u[0]*gamma*w[3])/(gamma-1.0)/2.0;

              Fy[0] = w[2];
              Fy[1] = -u[0]*u[1]*w[0]+u[1]*w[1]+u[0]*w[2];
              Fy[2] = -3.0/2.0*w[0]*u[1]*u[1] + w[0]*u[0]*u[0]*gamma/2.0
                -w[0]*u[0]*u[0]/2.0+w[0]*u[1]*u[1]*gamma/2.0
                -w[1]*u[0]*gamma+w[1]*u[0]+3.0*w[2]*u[1]-w[2]*u[1]*gamma
                +w[3]*gamma
                -w[3];
              Fy[3] = -(3.0*u[1]*w[0]*u[0]*u[0]*gamma
                        -2.0*u[1]*w[0]*u[0]*u[0]
                        +3.0*u[1]*u[1]*u[1]*w[0]*gamma + 2.0*u[1]*w[0]*T
                        -2.0*u[1]*u[1]*u[1]*w[0]
                        -u[1]*w[0]*u[0]*u[0]*gamma*gamma
                        -u[1]*u[1]*u[1]*w[0]*gamma*gamma
                        +2.0*u[0]*u[1]*w[1]*gamma*gamma
                        -4.0*u[0]*u[1]*w[1]*gamma
                        + 2.0*u[0]*u[1]*w[1]
                        -5.0*w[2]*u[1]*u[1]*gamma+3.0*w[2]*u[1]*u[1]
                        -w[2]*u[0]*u[0]*gamma + w[2]*u[0]*u[0]
                        -2.0*w[2]*T+2.0*w[2]*u[1]*u[1]*gamma*gamma
                        -2.0*u[1]*gamma*gamma*w[3]
                        +2.0*u[1]*gamma*w[3])/(gamma-1.0)/2.0;

              Asr[0]->u[qr] = Fx[0]*nx + Fy[0]*ny;
              Asr[1]->u[qr] = Fx[1]*nx + Fy[1]*ny;
              Asr[2]->u[qr] = Fx[2]*nx + Fy[2]*ny;
              Asr[3]->u[qr] = Fx[3]*nx + Fy[3]*ny;


            } else if (Asr[0]->modeltype==Model::EULER ||
                       Asr[0]->modeltype==Model::NAVIER_STOKES) {

              Scalar rl,ml,nl,El,vl,pl,Hl;

              // normal interior flux
              rl = Asr[0]->u[qr];                   // density
              // normal momentum
              ml = Asr[1]->u[qr]*nx + Asr[2]->u[qr] *ny;
              // tangent momentum
              nl = Asr[2]->u[qr]*nx -Asr[1]->u[qr] *ny;
              El = Asr[3]->u[qr];        // total energy per volume

              // local primative variables (projected to normal)
              ul = ml/rl;                                   // normal velocity
              vl = nl/rl;                                   // tangent velocity
              pl = (gamma-1.0)*(El - 0.5*(ml*ul + nl*vl));  // pressurAe
              Hl = (El + pl)/rl;                            // total enthalpy

              // put the local flux on the state edges
              Asr[0]->u[qr] = rl*ul;
              Asr[1]->u[qr] = (ml*ul+pl)*nx - (nl*ul)*ny;
              Asr[2]->u[qr] = (ml*ul+pl)*ny + (nl*ul)*nx;
              Asr[3]->u[qr] = ul*(El + pl);

              crA = sqrt((gamma-1.0)*(Hl - 0.5*(ul*ul + vl*vl)));
              urA = ul;

            }else if(Asr[0]->modeltype==Model::WAVE) {

              urA = Smr[1]->u[qr]*nx +Smr[2]->u[qr]*ny;
              crA = sqrt(Smr[3]->u[qr]);

              for(int k=0;k<(Nfields-1);k++) w[k]=Asr[k]->u[qr];
              rho = Smr[0]->u[qr];
              u[0]= Smr[1]->u[qr];
              u[1]= Smr[2]->u[qr];
              Scalar mC = crA;

              Fx[0] = w[1];
              Fx[1] = -w[0]*u[0]*u[0]+w[0]*mC*mC+2.0*u[0]*w[1];
              Fx[2] = -u[0]*u[1]*w[0]+u[1]*w[1]+u[0]*w[2];

              Fy[0] = w[2];
              Fy[1] = -u[0]*u[1]*w[0]+u[1]*w[1]+u[0]*w[2];
              Fy[2] = -w[0]*u[1]*u[1]+w[0]*mC*mC+2.0*u[1]*w[2];

              Asr[0]->u[qr] = Fx[0]*nx + Fy[0]*ny;
              Asr[1]->u[qr] = Fx[1]*nx + Fy[1]*ny;
              Asr[2]->u[qr] = Fx[2]*nx + Fy[2]*ny;

            }
          }

          switch (flux) {
          case LaxFriedrichs:

            // Possible problem for Wave (no mean flow OK!),
            // should be fixed later  not true for Wave(field 3,not 4)!!!
            if( Ssl[0]->modeltype == Ssr[0]->modeltype) {
              lmax=0;
              lam[0] = ul;
              lam[1] = ul+cl;
              lam[2] = ul-cl;
              lam[3] = ul;
              // left flux
              for(int j=0; j<nfields;j++) {
                lmax=max(lmax,fabs(lam[j]));
                fpl[j] = Ssl[j]->u[ql];
              }

              lam[0] = ur;
              lam[1] = ur+cr;
              lam[2] = ur-cr;
              lam[3] = ur;

              for(int j=0; j<nfields; j++) {
                lmax=max(lmax,fabs(lam[j]));
                fmr[j] = Ssr[j]->u[qr];
              }
              // Lax-Friedrichs flux
              for(int j=0; j<nfields; j++)
                f[j] = 0.5 * ( fpl[j] + fmr[j] + lmax * ( sl[j] - sr[j] ) );

            } else{  //coupling edge

              lmax=0;
              lam[0] = ul;
              lam[1] = ul+cl;
              lam[2] = ul-cl;
              lam[3] = ul;
              // left flux
              for(int j=0; j<nfields;j++) {
                lmax=max(lmax,fabs(lam[j]));
                fpl[j] = Ssl[j]->u[ql];
              }

              lam[0] = urA;
              lam[1] = urA+crA;
              lam[2] = urA-crA;
              lam[3] = urA;
              // left flux
              for(int j=0; j<nfields;j++) {
                lmax=max(lmax,fabs(lam[j]));
                fmrA[j] = Asr[j]->u[qr];
              }

              // Lax-Friedrichs flux for local
              for(int j=0; j<nfields; j++)
                f[j] = 0.5 * ( fpl[j] + fmrA[j] + lmax * ( sl[j] - srA[j]));

              lmax=0;
              lam[0] = ulA;
              lam[1] = ulA+clA;
              lam[2] = ulA-clA;
              lam[3] = ulA;
              // left flux
              for(int j=0; j<nfields;j++) {
                lmax=max(lmax,fabs(lam[j]));
                fplA[j] = Asl[j]->u[ql];
              }

              lam[0] = ur;
              lam[1] = ur+cr;
              lam[2] = ur-cr;
              lam[3] = ur;

              for(int j=0; j<nfields; j++) {
                lmax=max(lmax,fabs(lam[j]));
                fmr[j] = Ssr[j]->u[qr];
              }

              // Lax-Friedrichs flux for adjacent
              for(int j=0; j<nfields; j++)
                fA[j] = 0.5 * ( fplA[j] + fmr[j] + lmax * ( slA[j] - sr[j]));

            }

            break;
          case vanLeer:
          case StegerWarming:
          case Roe:
            cerr << "Those flux types haven't been"
                 <<" implemented yet for coupling problem" << endl;
            comm->exit(DGM::FAILURE);
            break;
          default:
            cerr << "Illegal value of flux type" << endl;
            comm->exit(DGM::FAILURE);
          }

          // put fluxes on flux field sides
          for (int ni=0; ni<nfields; ni++) {
            if(Ssl[0]->modeltype==Ssr[0]->modeltype) {
              Ssr[ni]->u[qr] *= -1.0;         // correct for normal
              Sfl[ni]->u[ql]  =  f[ni];
              Sfr[ni]->u[qr]  = -f[ni];

            }else {
              Ssr[ni]->u[qr] *= -1.0;         // correct for normal
              Sfl[ni]->u[ql]  =  f[ni];
              Sfr[ni]->u[qr]  = -fA[ni];

            }
          }
        }

        //delete the auxiliary Sides
        if(Ssl[0]->modeltype != Ssr[0]->modeltype ) {
          for (int ni=0; ni<nfields; ni++) {
            delete Asl[ni];
            delete Asr[ni];
          }
        }

      }
    }
  }

}
#endif


#if 0
//WARNING::Not correct!!!! [gqchen]
//      T_p[q]   = gamma*rho_p[q];
//      p = rho*T/(gamma*Ma*Ma);//P_m

P_p = c_m*c_m*rho_p[q];
#if 0
T_p[q] = gamma*Ma*Ma*P_p/rho;
#else
T_p[q] = (P_p + rho*T/(gamma*Ma*Ma))/(rho+rho_p[q])*gamma*Ma*Ma - T;
#endif

#endif


#if 0
// Need to setup the general framework for the sponge [gqchen]

// Add sponge in the far field
// the sponge length usually one or two wave length, the exponential coef.
// Current implementation is hard-wired, not flexible for the general geometry
// Only work for the vortex rebounding problem !!!![[gqchen]

void Couple::set_sponge(const vField &Us,vField &Ur) {
  Element *S[4], *R[4];
  int qtot;
  register int i, k;
  Scalar x,y;

  Scalar taus;
  Scalar As=20.0;
  int N=4;

  Scalar uquasi[4];

  for (k=0; k<Us[0]->ne; k++) {

    S[0] = Us[0]->el[k];  // local version of the state
    S[1] = Us[1]->el[k];
    S[2] = Us[2]->el[k];
    S[3] = Us[3]->el[k];

    R[0] = Ur[0]->el[k];  // local version of the state
    R[1] = Ur[1]->el[k];
    R[2] = Ur[2]->el[k];
    R[3] = Ur[3]->el[k];

    qtot = S[0]->qtot;

    for(i=0;i<qtot;i++){
      x = S[0]->C->x[i];
      y = S[0]->C->y[i];

      if(x>=3.72321&&y>=(-1.0)&&y<=1.0&&S[0]->modeltype==Model::NAVIER_STOKES){

#if 0
        // form the conservative_variable
        uquasi[0] = 1.0;//rho;
        uquasi[1] = 1.0;//u[0]*rho;
        uquasi[2] = 0.0;//u[1]*rho;
        uquasi[3] = 20.34126984126984126984;//
#else
        uquasi[0] = Um[0]->el[k]->u[i];
        uquasi[1] = Um[0]->el[k]->u[i]*Um[1]->el[k]->u[i];
        uquasi[2] = Um[0]->el[k]->u[i]*Um[2]->el[k]->u[i];
        uquasi[3] = Um[0]->el[k]->u[i]*Um[3]->el[k]->u[i]
          /(gamma*(gamma-1.0))
          + 0.5*(uquasi[1]* uquasi[1]+uquasi[2]* uquasi[2])/uquasi[0];

#endif

        // get taus
        taus = As*pow(fabs(x-3.72321)/2.77679,N);

        R[0]->u[i]=R[0]->u[i] + taus*(S[0]->u[i]-uquasi[0]);
        R[1]->u[i]=R[1]->u[i] + taus*(S[1]->u[i]-uquasi[1]);
        R[2]->u[i]=R[2]->u[i] + taus*(S[2]->u[i]-uquasi[2]);
        R[3]->u[i]=R[3]->u[i] + taus*(S[3]->u[i]-uquasi[3]);

      }
    }
  }
}

#endif


#ifdef STAT_OBS

void Couple::obs_stat(const vField& U, const Scalar t){

  int nid;
  int pid;
  Scalar rho,u,v,T,p;
  Scalar rhom,um,vm,Tm,pm;
  Scalar w[4];

  if(node_local.size()>0){
    fprintf(fobs_stat,"%11.4e",t);
    for(int i=0;i<node_local.size();i++){
      nid = node_local[i];
      pid    = p_local[i];
      if (U[0]->el[nid]->modeltype==Model::NAVIER_STOKES ||
          U[0]->el[nid]->modeltype==Model::EULER) {
        rho = U[0]->el[nid]->u[pid];
        u   = U[1]->el[nid]->u[pid]/rho;
        v   = U[2]->el[nid]->u[pid]/rho;
        p   = (U[3]->el[nid]->u[pid]- 0.5*(u*u+v*v)*rho)*(gamma-1.0);

        pm = Um[0]->el[nid]->u[pid]*Um[3]->el[nid]->u[pid]/gamma;

        fprintf(fobs_stat," %d %15.8e %15.8e %15.8e %15.8e %15.8e",
                i,rho,u,v,p,pm);
      }
      else if(U[0]->el[nid]->modeltype==Model::LINEULER){

        rhom = Um[0]->el[nid]->u[pid];
        um   = Um[1]->el[nid]->u[pid];
        vm   = Um[2]->el[nid]->u[pid];
        Tm   = Um[3]->el[nid]->u[pid];
        pm   = rhom*Tm/gamma;


        for(int j=0;j<Nfields;j++)
          w[j]=U[j]->el[nid]->u[pid];

        //code produced by Maple
        rho = w[0] + rhom;
        u = -um/rhom*w[0]+1/rhom*w[1] + um;
        v = -vm/rhom*w[0]+1/rhom*w[2] + vm;
        T = 1/rhom*(um*um*gamma*gamma
                    -um*um*gamma
                    +vm*vm*gamma*gamma
                    -vm*vm*gamma
                    -2.0*Tm)*w[0]/2.0
          -1/rhom*um*gamma*(gamma-1.0)*w[1]
          -1/rhom*vm*gamma*(gamma-1.0)*w[2]
          +1/rhom*gamma*(gamma-1.0)*w[3] + Tm;

        p=rho*T/(gamma);
        fprintf(fobs_stat," %d %15.8e %15.8e %15.8e %15.8e %15.8e",
                i,rho,u,v,p,pm);
      }
      else if(U[0]->el[nid]->modeltype==WAVE){

        rhom = Um[0]->el[nid]->u[pid];
        um   = Um[1]->el[nid]->u[pid];
        vm   = Um[2]->el[nid]->u[pid];
        Tm   = Um[3]->el[nid]->u[pid];
        pm   = rhom*Tm/(gamma);

        for(int j=0;j<(Nfields-1);j++)
          w[j]=U[j]->el[nid]->u[pid];

        //code produced by Maple
        rho =  w[0] + rhom;
        u   = -um/rhom*w[0]+1/rhom*w[1] + um;
        v   = -vm/rhom*w[0]+1/rhom*w[2] + vm;
        //p =p'+pm
        p = Tm*w[0] + Tm*rhom/(gamma);

        fprintf(fobs_stat," %d %15.8e %15.8e %15.8e %15.8e %15.8e",
                i,rho,u,v,p,pm);
      }
    }
    fprintf(fobs_stat,"\n");
  }
}

#endif


#if 0  // old BC implementation

//===========================================================================
//Notes: 1) The implementation is too old, should be updated
void Couple::enforce_bc(vField &S) {

  dVector us[4];
  dVector ub[4];
  dVector um[4];
  for (int n=0; n<S[0]->nbc; n++) {
    int sid = S[0]->bc[n]->sid;
    int qtot = S[0]->bc[n]->elmt->side[sid]->qtot;
    dVector &nx = S[0]->bc[n]->elmt->side[sid]->nx();
    dVector &ny = S[0]->bc[n]->elmt->side[sid]->ny();
    for (int i=0; i<Nfields; i++) {
      us[i].alias( S[i]->bc[n]->elmt->side[sid]->u );
      um[i].alias( Um[i]->bc[n]->elmt->side[sid]->u );
      ub[i].alias( S[i]->bc[n]->elmt->side[sid]->link->u );
    }
    if(S[0]->bc[n]->elmt->modeltype==Model::NAVIER_STOKES){
      BC::db_itr cur;
      if ( (cur = BC_db.find(S[0]->bc[n]->type)) == BC_db.end() ) {
        cerr << "ERRROR in Couple::enforce_state_bc:Undefined BC type \""
             << S[0]->bc[n]->type << "\"." << endl;
        comm->exit(DGM::FAILURE);
      }
      cur->second->apply( nx, ny, us, ub );
    }else {  //for LinEuler/Wave, still use the old implementation
      Scalar rho,u[2],T,rhop,up,vp,Tp,w[4];
      Scalar tmp;

      switch (S[0]->bc[n]->type[0]) {
      case 'W':

        if(S[0]->bc[n]->elmt->modeltype==Model::LINEULER){
          for (int i=0; i<qtot; i++) {

            for(int m=0;m<4;m++) w[m] = us[m][i];
            rho  = um[0][i];
            u[0] = um[1][i];
            u[1] = um[2][i];
            T    = um[3][i];
            //Get Up
            rhop = w[0];
            up   = -u[0]/rho*w[0] + 1/rho*w[1];
            vp   = -u[1]/rho*w[0] + 1/rho*w[2];
            Tp   = 1/rho*(u[0]*u[0]*gamma*gamma-u[0]*u[0]*gamma
                          +u[1]*u[1]*gamma*gamma-u[1]*u[1]*gamma
                          -2.0*T)*w[0]/2.0
              -1/rho*u[0]*gamma*(gamma-1.0)*w[1]
              -1/rho*u[1]*gamma*(gamma-1.0)*w[2]
              +1/rho*gamma*(gamma-1.0)*w[3];

            //Form the new Up
            rhop  = rhop;
            tmp   = (up*ny[i] - vp*nx[i])*ny[i];
            vp    = (vp*nx[i] - up*ny[i])*nx[i];
            up    = tmp;
            Tp    = Tp;

            w[0]  = rhop;
            w[1]  = up;
            w[2]  = vp;
            w[3]  = Tp;

            //For Quasi U = M*Up
            ub[0][i] = w[0];
            ub[1][i] = u[0]*w[0]+rho*w[1];
            ub[2][i] = u[1]*w[0]+rho*w[2];
            ub[3][i] = (T/gamma/(gamma-1.0)+u[0]*u[0]/2.0
                        +u[1]*u[1]/2.0)*w[0]+rho*u[0]*w[1]+rho*u[1]*w[2]
              +rho/gamma/(gamma-1.0)*w[3];
          }

        }else if(S[0]->bc[n]->elmt->modeltype==Model::EULER){

          for (int i=0; i<qtot; i++) {
            ub[0][i] = us[0][i];
            ub[1][i] = (us[1][i]*ny[i] - us[2][i]*nx[i])*ny[i];
            ub[2][i] = (us[2][i]*nx[i] - us[1][i]*ny[i])*nx[i];
            ub[3][i] = us[3][i]
              - 0.5*(us[1][i]*us[1][i] + us[2][i]*us[2][i])/us[0][i]
              + 0.5*(ub[1][i]*ub[1][i] + ub[2][i]*ub[2][i])/ub[0][i];
          }
        }
        else if(S[0]->bc[n]->elmt->modeltype==Model::WAVE){

          for (int i=0; i<qtot; i++) {

            for(int m=0;m<(Nfields-1);m++) w[m] = us[m][i];
            rho  = um[0][i];
            u[0] = um[1][i];
            u[1] = um[2][i];

            //Get Up
            rhop = w[0];
            up   = -u[0]/rho*w[0]+1/rho*w[1];
            vp   = -u[1]/rho*w[0]+1/rho*w[2];

            //Form the new Up
            rhop = rhop;
            tmp  = (up*ny[i] - vp*nx[i])*ny[i];
            vp   = (vp*nx[i] - up*ny[i])*nx[i];
            up   = tmp;

            w[0] = rhop;
            w[1] = up;
            w[2] = vp;

            //For Quasi U = M*Up
            ub[0][i] = w[0];
            ub[1][i] = u[0]*w[0]+rho*w[1];
            ub[2][i] = u[1]*w[0]+rho*w[2];
          }
        }

        break;

      default:  //State boundary

        if(S[0]->bc[n]->elmt->modeltype==Model::LINEULER){

          for (int i=0; i<qtot; i++) {

            w[0] = 0; //rho'
            w[1] = 0; //u'
            w[2] = 0; //v'
            w[3] = 0; //T'

            // transform to the quasi-variable

            rho   = um[0][i];
            u[0]  = um[1][i];
            u[1]  = um[2][i];
            T     = um[3][i];

            //form the quasi_variable
            ub[0][i] = w[0];
            ub[1][i] = u[0]*w[0]+rho*w[1];
            ub[2][i] = u[1]*w[0]+rho*w[2];
            ub[3][i] = (T/gamma/(gamma-1.0)+u[0]*u[0]/2.0
                        +u[1]*u[1]/2.0)*w[0]+ rho*u[0]*w[1]+rho*u[1]*w[2]
              +rho/gamma/(gamma-1.0)*w[3];
          }

        }else if(S[0]->bc[n]->elmt->modeltype==Model::EULER){

          Scalar rho,u1,v1,T1;

          //Warning: assume uniform flow,reference Ma=0.3
          //  (r=u=1.0,v=0,T=11.1111)

          for (int i=0; i<qtot; i++) {

            rho = 1.0; //rho +rhom
            u1  = 1.0; //u
            v1  = 0.0; //v
            T1  = 11.1111;

            ub[0][i] = rho;
            ub[1][i] = rho*u1;
            ub[2][i] = rho*v1;
            ub[3][i] = rho*T1/(gamma*(gamma-1.0))
              +0.5*rho*(u1*u1+v1*v1);
          }
        }else if(S[0]->bc[n]->elmt->modeltype==Model::WAVE){

          for (int i=0; i<qtot; i++) {

            w[0] = 0.0; //rho'
            w[1] = 0.0; //u'
            w[2] = 0.0; //v'

            // transform to the quasi-variable
            rho  = um[0][i];
            u[0] = um[1][i];
            u[1] = um[2][i];

            //form the quasi_variable
            ub[0][i] = w[0];
            ub[1][i] = u[0]*w[0]+rho*w[1];
            ub[2][i] = u[1]*w[0]+rho*w[2];
          }
        }
        break;
      }
    }
  }

}

void Couple::enforce_flux_bc(vField &S) {
  //Only available for N-S
  dVector us[4];
  dVector ub[4];
  for (int n=0; n<S[0]->nbc; n++) {
    int sid = S[0]->bc[n]->sid;
    int qtot = S[0]->bc[n]->elmt->side[sid]->qtot;
    dVector &nx = S[0]->bc[n]->elmt->side[sid]->nx();
    dVector &ny = S[0]->bc[n]->elmt->side[sid]->ny();
    for (int i=0; i<Nfields; i++) {
      us[i].alias( S[i]->bc[n]->elmt->side[sid]->u );
      ub[i].alias( S[i]->bc[n]->elmt->side[sid]->link->u );
    }
    if(S[0]->bc[n]->elmt->modeltype==Model::NAVIER_STOKES){
      BC::db_itr cur;
      if ( (cur = BC_db.find(S[0]->bc[n]->type)) == BC_db.end() ) {
        cerr << "ERRROR in Couple::enforce_flux_bc:  "
             << "Undefined BC type \""
             << S[0]->bc[n]->type << "\"." << endl;
        comm->exit(DGM::FAILURE);
      }
      cur->second->apply_flux( nx, ny, us, ub );
    }
  }
}

void Couple::enforce_mean_bc(vField &S) {
  dVector us[4];
  dVector ub[4];
  for (int n=0; n<S[0]->nbc; n++) {
    int sid = S[0]->bc[n]->sid;
    int qtot = S[0]->bc[n]->elmt->side[sid]->qtot;
    dVector &nx = S[0]->bc[n]->elmt->side[sid]->nx();
    dVector &ny = S[0]->bc[n]->elmt->side[sid]->ny();
    switch (S[0]->bc[n]->type[0]) {
    case 'W':
      for (int i=0; i<Nfields; i++) {
        us[i].alias( S[i]->bc[n]->elmt->side[sid]->u );
        ub[i].alias( S[i]->bc[n]->elmt->side[sid]->link->u );
      }
      // slip boundary here??
      for (int i=0; i<qtot; i++) {
        ub[0][i] = us[0][i]; // rho_m
        ub[1][i] = 0;        // u_m
        ub[2][i] = 0;        // v_m
        ub[3][i] = us[3][i]; // T_m
      }
      break;
    default:
      for (int i=0; i<Nfields; i++) {
        us[i].alias( S[i]->bc[n]->elmt->side[sid]->u );
        ub[i].alias( S[i]->bc[n]->elmt->side[sid]->link->u );
      }
      for (int i=0; i<qtot; i++) {
        ub[0][i] = us[0][i];
        ub[1][i] = us[1][i];
        ub[2][i] = us[2][i];
        ub[3][i] = us[3][i];
      }
      break;
    }
  }
}

#endif // DGM_USE_MD_COUPLE

} // namespace Reo
