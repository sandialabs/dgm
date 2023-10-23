/** \file ArtDiff.cpp
    \brief Artificial diffusion implementation
    \author Scott Collis
    \warning This is currently experimental, use with extreme caution
*/

// DGM includes
#include "vField.hpp"
#include "ArtDiff.hpp"

namespace DGM {

//=============================================================================
//                A r t i f i c i a l    D i f f u s i o n
//=============================================================================

/// Compute Bassi and Rebay diffusive flux (artificial viscosity term)
void ArtDiff::operator() ( vField &Uf, vField &Ff, vField &Rf ) const {

  comm->cout() << "ArtDiff::operator()" << endl;

  if ( ((C_epsi0 == zero) || (sensor == None)) ) return;

  Uf.fill_sides();                         // put solution on the sides
  Uf.share_sides();                        // parallel communication

  omega->enforce_bc(Uf);                   // update bc side values

  // F's sides are average of the fine-scale solution ...
  average_flux( Uf, Ff, '+' );              // used to lift the gradient
  // average_flux_finescale( Uf, Ff, '+' ); // used to lift the gradient

  // Dimension character vector
  //char vdir[3] = {'x','y','z'};           // direction vector

  for (vField::size_type ni=0; ni<Uf.size(); ni++) {
    for (Ordinal e=0; e<Uf[ni]->ne; e++) {
      Element *U = Uf[ni]->el[e];
      Element *F = Ff[ni]->el[e];
      const Ordinal qtot = U->qtot;
      const Ordinal nModes = U->nModes();
      const Ordinal nsd = Uf.nsd();

      // Compute convective velocity
      dVector vel_convect(wka,qtot);
      dVector veltemp(wkb,qtot);
      dVector velsum(wkc,qtot);
      velsum = 0.0;

      for (Ordinal d=0; d<nsd; d++) {
        dvmul(Vt[d]->el[e]->u, Vt[d]->el[e]->u, veltemp);
        dvadd(veltemp, velsum);
      }
      dvsqrt(velsum, vel_convect);

      Scalar epsi0 = pow(U->measure(),1.0/Scalar(nsd));
      epsi0 *= (U->pOrder() > 0) ? C_epsi0/Scalar(U->pOrder()) : C_epsi0;

      // Select discontinuity capturing sensor
      Scalar nu_art = 0.0;
      switch(sensor) {
      case None:
        nu_art = 0.0;
        break;
      case Jump:
        nu_art = epsi0*Sv[ni]->el[e]->u[0];
        break;
      case Resolution:
        nu_art = epsi0*Nu[ni]->el[e]->u[0];
        break;
      default:
        comm->error("ArtDiff::artificial_diffusion illegal sensor");
      }

      //// Add constant value dissipation for water or gas
      //if (ni == 0) nu_art += eps_w;
      //else if (ni == 1) nu_art += eps_g;

      // dVector ut_a(wk1,qtot); // constructor: all-scale temp. vector
      // ut_a = U->u;            // copy "u" into all-scale vec.
      // U->fine_scales(U->L-1); // fine scales of "u", removing the constant

      /*
      // Beginning on dimension independent coding
      for (int d=0; d<nsd; d++) {
        dVector gu(wk2,qtot);
        dVector guh(gu,nModes);

        U->gradient( U->u, gu, vdir[d] );
        U->lift( F, gu, vdir[d] );
#ifdef REO_PROJECT_DIFF_FLUX
        U->project(gu);
#endif
        scale(nu_art, gu);
      }
      */

      if (nsd==3) {
        dVector ux(wk2,qtot);
        dVector uy(wk3,qtot);
        dVector uz(wk4,qtot);
        dVector uxh(ux,nModes);
        dVector uyh(uy,nModes);
        dVector uzh(uz,nModes);

        U->gradient(U->u, ux, uy, uz);
        U->lift( F, ux, 'x' );
        U->lift( F, uy, 'y' );
        U->lift( F, uz, 'z' );
#ifdef REO_PROJECT_DIFF_FLUX
        U->project(ux);
        U->project(uy);
        U->project(uz);
#endif
        scale( nu_art, ux );
        scale( nu_art, uy );
        scale( nu_art, uz );
        dvmul(vel_convect, ux);
        dvmul(vel_convect, uy);
        dvmul(vel_convect, uz);
        U->fill_sides( ux, uy, uz );            // normal viscous flux on sides

        U->gradient(ux, ux, 'x');               // ux = u_{,xx}
        U->gradient(uy, uy, 'y');               // uy = u_{,yy}
        U->gradient(uz, uz, 'z');               // uz = u_{,zz}
        dvadd( ux, uy, F->u );                  // F->u = u_{,xx} + u_{,yy}
        dvadd( uz, F->u );                      // F->u += u_{,zz}
      } else if (nsd==2) {
        dVector ux(wk2,qtot);
        dVector uy(wk3,qtot);
        dVector uxh(ux,nModes);
        dVector uyh(uy,nModes);

        U->gradient(U->u, ux, uy);
        U->lift( F, ux, 'x' );
        U->lift( F, uy, 'y' );
#ifdef REO_PROJECT_DIFF_FLUX
        U->project(ux);
        U->project(uy);
#endif
        scale( nu_art, ux );
        scale( nu_art, uy );
        dvmul(vel_convect, ux);
        dvmul(vel_convect, uy);
        U->fill_sides( ux, uy );                // normal viscous flux on sides

        U->gradient(ux, ux, 'x');               // ux = u_{,xx}
        U->gradient(uy, uy, 'y');               // uy = u_{,yy}
        dvadd( ux, uy, F->u );                  // F->u = u_{,xx} + u_{,yy}
      } else if (nsd==1) {
        dVector ux(wk2,qtot);
        dVector uxh(ux,nModes);
        U->gradient(U->u, ux, ux);
        // add the edge terms lifted in the el. interior
        U->lift( F, ux, 'x' );
#ifdef REO_PROJECT_DIFF_FLUX
        U->project(ux);
#endif
        // form the artificial viscous flux
        scale( nu_art, ux );
        dvmul(vel_convect, ux);
        U->fill_sides( ux, ux );                // normal viscous flux on sides
        U->gradient(ux, F->u, 'x');             // ux = uxx
      } else {
        comm->cerr()<< "ArtDiff:artificial_diffusion -- "
                    << "illegal value of nsd" << endl;
        comm->exit(DGM::FAILURE);
      }
    }
  }
  Uf.share_sides();                             // parallel communication
  omega->enforce_flux_bc(Uf);                   // put flux BC's on bc sides
  average_flux( Uf, Ff, '-' );

  for (vField::size_type ni=0; ni<Uf.size(); ni++) {
    for (Ordinal e=0; e<Uf[ni]->ne; e++) {
      Element *U = Uf[ni]->el[e];
      Element *F = Ff[ni]->el[e];
      U->lift( F, F->u );      // add side fluxes to interior
    }
  }
  scale( -1.0, Ff);                             // Currently on LHS
  add( Ff, Rf );                                // add in viscous contribution
}

/// compute jump sensor
/*! \note Not defined in dimension one, since, U->compute_side_integral() is
          not defined in this case. We need to implement this case. */
void ArtDiff::jump_sensor( vField &Us ) const {

  if ( (C_epsi0 == zero) || (sensor == None)) return;

#ifdef REO_USE_GETSIDEMAPS
  iVector mapl, mapr;
#endif

  // cout << "Diffusion for Field = " << Us[0]->name << endl;
  // cout << "Diffusion for Field = " << Us[1]->name << endl;

  Us.fill_sides();                       // put solution on the sides
  Us.share_sides();                      // parallel communication
  omega->enforce_bc(Us);                 // update bc side values

  // Sv's sides are the jump of the solution
  // Nu's sides are average of the solution ...
  // Use jump and average of exponential values to
  // eschew working around 0-values
  average_flux_exp( Us, Sv, '-' );
  average_flux_exp( Us, Nu, '+' );

#ifdef REO_USE_GETSIDEMAPS
  omega->setup_side_maps();
#endif

  const Ordinal nsd = Us.nsd();

  // Scaling constants
  Scalar const1 = (nsd == 1) ? 1.50 : 1.75; // 2.0; // 1.25;
  Scalar const2 = (nsd == 1) ? 1.50 : 1.75; // 2.0; // 1.5;

  // Loop over elements, compute jumps and store in quad points
  for (vField::size_type ifield=0; ifield<Us.size(); ifield++) {
    for (Ordinal e=0; e<Us[ifield]->ne; e++) {
      Element *U = Sv[ifield]->el[e];
      Element *F = Nu[ifield]->el[e];
      for (Ordinal i=0; i<U->nSides(); i++) {
        if (U->side[i]->master()) {
          Side *Sfl = F->side[i];
          Side *Sfr = F->side[i]->link;
          Side *Sul = U->side[i];
          Side *Sur = U->side[i]->link;
          const Ordinal qtot  = Sul->qtot();
#ifdef REO_USE_GETSIDEMAPS
          omega->get_side_maps(Sul,Sur,mapl,mapr);
#endif
          for (Ordinal q=0; q<qtot; q++) {
#ifdef REO_USE_GETSIDEMAPS
            Sul->u[mapl[q]] = 2.0*fabs( Sul->u[mapl[q]] /
                                        Sfl->u[mapl[q]] );
            Sur->u[mapr[q]] = 2.0*fabs( Sur->u[mapr[q]] /
                                        Sfr->u[mapr[q]] );
#else
            const Ordinal ql = U->sideMap(Sul,q);  // quadrature on the left
            const Ordinal qr = U->sideMap(Sur,q);  // quadrature on the right
            Sul->u[ql] = 2.0*fabs( Sul->u[ql] / Sfl->u[ql] );
            Sur->u[qr] = 2.0*fabs( Sur->u[qr] / Sfr->u[qr] );
#endif
          }
        }
      }
    }

    // Now compute the integral
    for (Ordinal e=0; e<Us[ifield]->ne; e++) {
      Element *U = Sv[ifield]->el[e];

      // Compute scaling constants of jump sensor
      Scalar delta = 0.5;
      Scalar cap   = 1.0;
      Scalar So    = (U->pOrder() > 0) ?
          -(const1 + const2*log10((Scalar)U->pOrder())) : -const1;

      // Sum integral of quad points
      Scalar S = log10( U->compute_side_integral()/U->compute_side_measure() );

      // Scale the sensor between 0 and 1
      if (S < So - delta)
        S = 0.0;
      else if (S > So + delta)
        S = cap;
      else {
        //S = 0.25*cap*(S-So+delta)*(S-So+delta)/(delta*delta);
        S = 0.5*cap*(1+sin(0.5*pi*(S-So)/delta));
      }

      // Store final jump sensor value in Sv
      const Ordinal qtot = U->qtot;
      for (Ordinal iq=0; iq<qtot; iq++) U->u[iq] = S;
    }
  }

  // zero out the viscosity before exiting ...
  Nu.zero();
#if 0
#ifndef DGM_PARALLEL
  if (step%Ntout==0) {
    char vs_name[128];
    sprintf(vs_name,"sensor.%d.dat",step);
    Sv.tecplot(vs_name,"art_visc_sensor");
  }
#else
  if (step%Ntout==0) {
    char vs_name[128];
    sprintf(vs_name,"sensor.%d.rst",step);
    write(vs_name,Sv);
  }
#endif
#endif
}

/// compute the resolution sensor
void ArtDiff::resolution_sensor( vField &Uf ) const {
  using std::isfinite;
  if ( (C_epsi0 == zero) || (sensor == None)) return;
  Uf.fill_sides();                       // put solution on the sides
  Uf.share_sides();                      // MPI -> parallel communication
  omega->enforce_bc(Uf);                 // update bc side values
  for (Ordinal ni=0; ni<Uf.size(); ni++) {
    for (Ordinal e=0; e<Uf[ni]->ne; e++) {
      Element *U = Uf[ni]->el[e];
      const Ordinal qtot = U->qtot;
      // const int nModes = U->nModes();
      // build the discontinuity sensor ...
      dVector ut_a(wk1,qtot); // constructor: all-scale temp. vector
      ut_a = U->u;            // copy "u" into all-scale vec.
      Scalar el_volume = 0.0; // work Scalar variable
      const Scalar sq_norm_a =
        U->L2_inner_product(ut_a,ut_a,&el_volume); // norm(U->u)^2
      // u' = "fine scales of u" -> stored into ut_a
      U->fine_scales_transform(L_fs,ut_a);
      const Scalar sq_norm_f =
        U->L2_inner_product(ut_a,ut_a,&el_volume); // norm((U->u)')^2
      ut_a = U->u;            // copy "u" into all-scale vec.
      Scalar S_e = sq_norm_f/(sq_norm_a+1.0e-8*U->measure());
      if ((!isfinite(S_e)) || (S_e==0.0)) S_e = 1.0e-40; // trap division errors
      Scalar s_0= (U->pOrder() > 0) ? C_s0/pow((Scalar)U->pOrder(),4.0) : C_s0;

      // build the artificial viscosity...
      Scalar nu_art = 0.0;
      S_e = log10(S_e);
      s_0 = log10(s_0);
      if (S_e<(s_0-kappa_dc)) {
        nu_art = 0.0;
      } else if (((s_0-kappa_dc)<=S_e) && (S_e<=(s_0+kappa_dc))) {
        nu_art = 0.5*(1.0+sin(0.5*pi*(S_e-s_0)/kappa_dc));
      } else {
        nu_art = 1.0;
      }
      for (Ordinal iq=0; iq<qtot; iq++) {
        Nu[ni]->el[e]->u[iq] = nu_art;
      }
    }
  }
#if 0
#ifndef DGM_PARALLEL
  if (step%Ntout==0) {
    char vs_name[128];
    sprintf(vs_name,"nu.%d.dat",step);
    Nu.tecplot(vs_name,"art_visc_sensor");
  }
#else
  if (step%Ntout==0) {
    char vs_name[128];
    sprintf(vs_name,"nu.%d.rst",step);
    write(vs_name,Nu);
  }
#endif
#endif
}

/// generalized average flux
void ArtDiff::average_flux(vField &Uf, vField &Ff, const char sign) const {
#ifdef REO_USE_GETSIDEMAPS
  iVector mapl, mapr;
  omega->setup_side_maps();
#endif
  switch (sign) {
  case '+':
    for (Ordinal ni=0; ni<Uf.size(); ni++) {
      for (Ordinal e=0; e<Uf[ni]->ne; e++) {
        Element *U = Uf[ni]->el[e];
        Element *F = Ff[ni]->el[e];
        for (Ordinal i=0; i<U->nSides(); i++) {
          if (U->side[i]->master()) {
            const Ordinal qtot = U->side[i]->qtot();
#ifdef REO_USE_GETSIDEMAPS
            omega->get_side_maps(U->side[i],U->side[i]->link,mapl,mapr);
#endif
            for (Ordinal q=0; q<qtot; q++) {
#ifdef REO_USE_GETSIDEMAPS
              F->side[i]->u[mapl[q]] = 0.5*(U->side[i]->u[mapl[q]] +
                                            U->side[i]->link->u[mapr[q]]);
              F->side[i]->link->u[mapr[q]] = F->side[i]->u[mapl[q]];
#else
              const Ordinal ql = U->sideMap(U->side[i],q);
              const Ordinal qr = U->sideMap(U->side[i]->link, q);
              F->side[i]->u[ql] = 0.5*(U->side[i]->u[ql] +
                                            U->side[i]->link->u[qr]);
              F->side[i]->link->u[qr] = F->side[i]->u[ql];
#endif
            }
          }
        }
      }
    }
    break;
  case '-':
    for (Ordinal ni=0; ni<Uf.size(); ni++) {
      for (Ordinal e=0; e<Uf[ni]->ne; e++) {
        Element *U = Uf[ni]->el[e];
        Element *F = Ff[ni]->el[e];
        for (Ordinal i=0; i<U->nSides(); i++) {
          if (U->side[i]->master()) {
            const Ordinal qtot = U->side[i]->qtot();
#ifdef REO_USE_GETSIDEMAPS
            omega->get_side_maps(U->side[i],U->side[i]->link,mapl,mapr);
#endif
            for (Ordinal q=0; q<qtot; q++) {
#ifdef REO_USE_GETSIDEMAPS
              F->side[i]->u[mapl[q]] = 0.5*(U->side[i]->u[mapl[q]] -
                                            U->side[i]->link->u[mapr[q]]);
              F->side[i]->link->u[mapr[q]] = -F->side[i]->u[mapl[q]];
#else
              const Ordinal ql = U->sideMap(U->side[i],q);
              const Ordinal qr = U->sideMap(U->side[i]->link, q);
              F->side[i]->u[ql] = 0.5*(U->side[i]->u[ql] -
                                            U->side[i]->link->u[qr]);
              F->side[i]->link->u[qr] = -F->side[i]->u[ql];
#endif
            }
          }
        }
      }
    }
    break;
  default:
    comm->cerr()<< "ArtDiff::average_flux() -- illegal sign" << endl;
    comm->exit(DGM::FAILURE);
  }
}

/// generalized average flux with exponential
void ArtDiff::average_flux_exp(vField &Uf, vField &Ff, const char sign) const {
#ifdef REO_USE_GETSIDEMAPS
  iVector mapl, mapr;
  omega->setup_side_maps();
#endif
  switch (sign) {
  case '+':
    for (Ordinal ni=0; ni<Uf.size(); ni++) {
      for (Ordinal e=0; e<Uf[ni]->ne; e++) {
        Element *U = Uf[ni]->el[e];
        Element *F = Ff[ni]->el[e];
        for (Ordinal i=0; i<U->nSides(); i++) {
          if (U->side[i]->master()) {
            const Ordinal qtot = U->side[i]->qtot();
#ifdef REO_USE_GETSIDEMAPS
            omega->get_side_maps(U->side[i],U->side[i]->link,mapl,mapr);
#endif
            for (Ordinal q=0; q<qtot; q++) {
#ifdef REO_USE_GETSIDEMAPS
              F->side[i]->u[mapl[q]] = 0.5*
                (exp(U->side[i]->u[mapl[q]]) +
                 exp(U->side[i]->link->u[mapr[q]]));
              F->side[i]->link->u[mapr[q]] = F->side[i]->u[mapl[q]];
#else
              const Ordinal ql = U->sideMap(U->side[i],q);
              const Ordinal qr = U->sideMap(U->side[i]->link, q);
              F->side[i]->u[ql] = 0.5*
                (exp(U->side[i]->u[ql]) +
                 exp(U->side[i]->link->u[qr]));
              F->side[i]->link->u[qr] = F->side[i]->u[ql];
#endif
            }
          }
        }
      }
    }
    break;
  case '-':
    for (Ordinal ni=0; ni<Uf.size(); ni++) {
      for (Ordinal e=0; e<Uf[ni]->ne; e++) {
        Element *U = Uf[ni]->el[e];
        Element *F = Ff[ni]->el[e];
        for (Ordinal i=0; i<U->nSides(); i++) {
          if (U->side[i]->master()) {
            const Ordinal qtot = U->side[i]->qtot();
#ifdef REO_USE_GETSIDEMAPS
            omega->get_side_maps(U->side[i],U->side[i]->link,mapl,mapr);
#endif
            for (Ordinal q=0; q<qtot; q++) {
#ifdef REO_USE_GETSIDEMAPS
              F->side[i]->u[mapl[q]] = 0.5*
                (exp(U->side[i]->u[mapl[q]]) -
                 exp(U->side[i]->link->u[mapr[q]]));
              F->side[i]->link->u[mapr[q]] = -F->side[i]->u[mapl[q]];
#else
              const Ordinal ql = U->sideMap(U->side[i],q);
              const Ordinal qr = U->sideMap(U->side[i]->link, q);
              F->side[i]->u[ql] = 0.5*
                (exp(U->side[i]->u[ql]) -
                 exp(U->side[i]->link->u[qr]));
              F->side[i]->link->u[qr] = -F->side[i]->u[ql];
#endif
            }
          }
        }
      }
    }
    break;
  default:
    comm->cerr()<< "ArtDiff::average_flux_exp() -- illegal sign" << endl;
    comm->exit(DGM::FAILURE);
  }
}

} // namespace DGM
