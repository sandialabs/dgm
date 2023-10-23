/*=============================================================================
  Module:     EulerDC Module

  Contacts:   S. Scott Collis & Guglielmo Scovazzi

  Copyright:  (c)2009 Sandia National Laboratories
=============================================================================*/

/** \file  EulerDC.cpp
    \brief Euler equations (2d) with discontinuity capturing.
    \author Scott Collis
*/

// DGM includes
#include "TimeInt.hpp"

// Reo includes
#include "EulerDC.hpp"
#include "Fluid.hpp"

namespace Reo {

// constructor
EulerDC::EulerDC( DGM::ArgList &args, const DGM::Comm::Ptr comm_ ) :
  Euler( args, comm_ ), Uv(comm_), Nu(comm_) {
  // cout << "EulerDC::EulerDC(int argc, char *argv[])" << endl;

  vis   = params["vis"];        // viscosity
  Pr    = params["Pr"];         // Prandtl number for air
  gamma = params["gamma"];      // ratio of specific heats

  // read arguments
  parse_args( args );

  C_epsi0  = params.get("C_epsi0", 1.0e0);
  kappa_dc = params.get("kappa", 3.0);
  L_fs     = params.get("Lfs",   1);
  C_s0     = params.get("C_s0", 0.1);

  comm->cout() << "EulerDC parameters:" << endl;
  comm->cout() << "  C_epsi0 = " << C_epsi0 << endl;
  comm->cout() << "  kappa = " << kappa_dc << endl;
  comm->cout() << "  Lfs = " << L_fs << endl;
  comm->cout() << "  C_s0 = " << C_s0 << endl;
  comm->cout() << "  vis = " << vis << endl;

  // make auxiliary Fields using copy constructor
  for (vField::size_type i=0; i<Nfields; i++) {
    Uv.push_back( new Field( U[i], root, U[i]->name ) );
  }

  // make a field to store and plot the artificial viscosity
  Nu.push_back( new Field( U[0], root, "Nu" ) );

  // allocate workspace
  work.resize(10*max(Lmax(),Qmax()));

  // make sure that storage is initialized
  zero_all_fields();
}

// Parse parameters from the argument list
void EulerDC::parse_args( DGM::ArgList &args ) {
  string name, value;
  list< DGM::ArgList::iterator > li;
  for ( DGM::ArgList::iterator a = args.begin(); a != args.end(); a++ ) {
    if ( (*a)[0] == '-' ) {
      name = *a;
      if (name == "-C_epsi0") {
        li.push_back(a);
        value = *(++a);
        li.push_back(a);
        params["C_epsi0"] = atof(value.c_str());
      } else if (name == "-kappa") {
        li.push_back(a);
        value = *(++a);
        li.push_back(a);
        params["kappa"] = atof(value.c_str());
      } else if (name == "-Lfs") {
        li.push_back(a);
        value = *(++a);
        li.push_back(a);
        params["Lfs"] = atoi(value.c_str());
      } else if (name == "-C_s0") {
        li.push_back(a);
        value = *(++a);
        li.push_back(a);
        params["C_s0"] = atof(value.c_str());
      } else if (name == "-help") {
        params["showUsage"] = 1;
        showUsage();
      }
    }
  }
#ifdef DGM_REMOVE_ARGUMENTS
  // remove tagged arguments
  for ( list< DGM::ArgList::iterator >::iterator a=li.begin();
        a!=li.end(); a++) args.erase(*a);
#endif

}

/// print usage for the Adv_Diff Domain
void EulerDC::showUsage() {
  comm->cout()
    << "EulerDC Class Options \n"
    << "----------------------------------------------------------------\n"
    << "-C_epsi0  " << '\t' << "discontinuity capturing parameter \n"
    << "-kappa    " << '\t' << "discontinuity capturing parameter \n"
    << "-Lfs      " << '\t' << "discontinuity capturing parameter \n"
    << "-C_s0     " << '\t' << "discontinuity capturing parameter \n"
    << "----------------------------------------------------------------\n";
}

//===========================================================================
//                             Solve Methods
//===========================================================================

void EulerDC::time_derivative( vField &Us, vField &Uf ) {
  convection( Us, Uf );
  diffusion( Us, Uv, Uf );
#ifndef DGM_PARALLEL
  if (step%Ntout==0) {
    string fname;
    char buffer[BUFLEN];
#if 0
    sprintf(buffer,"nu.%lld.dat",(long long)step); fname = buffer;
    Nu.tecplot(fname,"Artificial viscosity");
#else
    sprintf(buffer,"nu.%lld",(long long)step); fname = buffer;
    Nu.paraview(fname,"Artificial viscosity");
#endif
  }
#else
  if (step%Ntout==0) {
    string fname;
    char buffer[BUFLEN];
    sprintf(buffer,"nu.%lld",(long long)step); fname = buffer;
    Nu.paraview(fname,"Artificial viscosity");
  }
#endif
  add_source(Us,Uf);
  project( Uf );
}

void EulerDC::zero_all_fields() {
  // cout << "zero_all_fields()" << endl;
  Domain::zero_all_fields();
  Uv.zero();
}

/** Computes and elementwise constant artificial viscosity based on the
    multiscale sensor of Jaime Peraire (MIT). */
void EulerDC::get_viscosity( const Element *U, dVector &ut_a,
                             dVector &mu ) {
  using std::isfinite;
  // cout << "EulerDC::get_viscosity(..) for element = " << U->id << endl;
  Scalar el_volume(zero);                      // work Scalar variable
  const Scalar sq_norm_a =
    U->L2_inner_product(ut_a,ut_a,&el_volume); // norm(U->u)^2
  // u' = "fine scales of u" -> stored in ut_a
  U->fine_scales_transform(L_fs,ut_a);
  const Scalar sq_norm_f =
    U->L2_inner_product(ut_a,ut_a,&el_volume); // norm((U->u)')^2
  Scalar S_e = sq_norm_f/(sq_norm_a+1.0e-6);
  if ( (!isfinite(S_e)) || (S_e==0.0) ) S_e = 1.0e-40; // trap division errors
  Scalar s_0 = C_s0/pow((Scalar)U->pOrder(),four);
  Scalar epsi0 = C_epsi0*(pow(el_volume,one/Scalar(nsd))/Scalar(U->pOrder()));
  // build the artificial viscosity...
  Scalar nu_art = zero;
  S_e = log10(S_e);
  s_0 = log10(s_0);
  if (S_e<(s_0-kappa_dc)) {
    nu_art = zero;
  } else if ( ( (s_0-kappa_dc)<=S_e) && (S_e<=(s_0+kappa_dc) ) )  {
    nu_art = epsi0*pt5*(one+sin(0.5*pi*(S_e-s_0)/kappa_dc));
  } else {
    nu_art = epsi0;
  }
  // cout << "nu_art = " << nu_art << endl;
  mu = nu_art;  // put the constant onto the element
#ifdef REO_HACK_DC
  mu = vis;
#endif
}

//===========================================================================
//                      Bassi-Rebay viscous flux
//===========================================================================

void EulerDC::diffusion( vField &Us, vField &Uf, vField &Ur ) {
  Element *S[NFIELDS], *F[NFIELDS];

#ifdef REO_EULERDC_LOCAL_TEMPS
  dVector u, v, p, e, wk;
  dVector r, ru, rv, E;
  dVector ux, uy, vx, vy, tau12, tau11, tau22;
#endif

  Us.fill_sides();                   // put solution on the sides
  enforce_bc(Us);                    // update bc side values
  Us.share_sides();                  // communicate sides if parallel
  primitive_sides(Us);               // convert sides to primitive variables
  average_flux( Us, Uf, '+' );       // Uf's sides are average state

  for (LocalSize k=0; k<Us[0]->ne; k++) {

    S[0] = Us[0]->el[k];  // local version of the state
    S[1] = Us[1]->el[k];
    S[2] = Us[2]->el[k];
    S[3] = Us[3]->el[k];

    F[0] = Uf[0]->el[k];  // local version of the flux
    F[1] = Uf[1]->el[k];
    F[2] = Uf[2]->el[k];
    F[3] = Uf[3]->el[k];

    const Ordinal qtot = S[0]->qtot;

#ifdef REO_EULERDC_LOCAL_TEMPS
    r.alias (S[0]->u);  // rho
    ru.alias(S[1]->u);  // rho u
    rv.alias(S[2]->u);  // rho v
    E.alias (S[3]->u);  // total Energy

    u.alias(work,0,qtot);
    v.alias(work,qtot,qtot);
    e.alias(work,2*qtot,qtot);
    wk.alias(work,3*qtot,qtot);
#else
    dVector r (S[0]->u);  // rho
    dVector ru(S[1]->u);  // rho u
    dVector rv(S[2]->u);  // rho v
    dVector E (S[3]->u);  // total energy per volume

    dVector u(qtot);
    dVector v(qtot);
    dVector e(qtot);
    dVector wk(qtot);
#endif

    dvdiv(ru, r, u);   // u-velocity
    dvdiv(rv, r, v);   // v-velocity
    dvdiv(E,  r, e);   // internal energy + 0.5 |V|^2

    dvmul(u,u,wk);     // wk = u^2
    dvvtvp(v,v,wk,wk); // wk = u^2 + v^2
    daxpy(-0.5,wk,e);  // e  = e - 0.5 * wk = internal energy

#ifdef REO_EULERDC_LOCAL_TEMPS
    ux.alias(work,4*qtot,qtot);
    uy.alias(work,5*qtot,qtot);  tau12.alias(uy);
    vx.alias(work,6*qtot,qtot);  tau11.alias(vx);
    vy.alias(work,7*qtot,qtot);  tau22.alias(vy);
#else
    dVector ux(qtot);
    dVector uy(qtot);  dVector tau12(uy);  // note the alias
    dVector vx(qtot);  dVector tau11(vx);  // note the alias
    dVector vy(qtot);  dVector tau22(vy);  // note the alias
#endif

    gradient( S[1], F[1], u, ux, uy );
    gradient( S[2], F[2], v, vx, vy );

    // compute pressure and entropy for use in the DC sensor
    dVector p(qtot), s(qtot);
    for (Ordinal q=0; q<qtot; q++) {
      p[q] = (gamma-one)*e[q]*r[q];               // pressure
      s[q] = log(e[q])+(gamma-one)*log(one/r[q]); // entropy (watch out for Cv)
    }
#ifdef REO_EULERDC_ENTROPY_SENSOR
    get_viscosity( S[0], s, wk );  // Peraire uses entropy...
#else
    get_viscosity( S[0], p, wk );  // make pressure the default for now
#endif
    Nu[0]->el[k]->u = wk;          // store the art viscosity in Nu

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

    // compute pressure and entropy for use in the DC sensor
    for (Ordinal q=0; q<qtot; q++) {
      p[q] = (gamma-one)*e[q]*r[q];               // pressure
      s[q] = log(e[q])+(gamma-one)*log(one/r[q]); // entropy (watch out for Cv)
    }
#ifdef REO_EULERDC_ENTROPY_SENSOR
    get_viscosity( S[0], s, wk );
#else
    get_viscosity( S[0], p, wk );
#endif
    dvmul(wk,vx);
    daxpy(gamma/Pr,vx,ux);
    dvmul(wk,vy);
    daxpy(gamma/Pr,vy,uy);

    // energy equation
    S[3]->fill_sides( ux, uy );
    S[3]->gradient(ux, wk, 'x'); // wk = (tau_{1j} u_j + k/Cv e_{,1})_{,1}
    S[3]->gradient(uy, ux, 'y'); // ux = (tau_{2j} u_j + k/Cv e_{,2})_{,2}
    dvadd( wk, ux, F[3]->u );    // F[3]->u = (tau_{ij} u_j + k/Cv e_{,i})_{,i}
  }

  Us.share_sides();                        // Share sides with your neighbors
  enforce_flux_bc(Us);                     // put flux BC's on bc sides
  average_flux( Us, Uf, '-' );

  // Note there is no contribution to the continuity equation
  for (vField::size_type n=1; n<Us.size(); n++) {
    for (LocalSize k=0; k<Us[n]->ne; k++) {
      S[k] = Us[n]->el[k];
      F[k] = Uf[n]->el[k];
      S[k]->lift( F[k], F[k]->u );
    }
  }

  scale(-one,Uf);  // I currently put everything on the LHS
  for (vField::size_type n=1; n<Uf.size(); n++) add( Uf[n], Ur[n] );
}

//===========================================================================
//                        BC database management
//===========================================================================

void EulerDC::enforce_flux_bc(vField &F) {
  //comm->cout() << "EulerDC::enforce_flux_bc(...)" << endl;
  for (BC::db_citr i=BC_db.begin(); i!= BC_db.end(); ++i)
    i->second->apply_flux( t, F );
}

} // namespace Reo
