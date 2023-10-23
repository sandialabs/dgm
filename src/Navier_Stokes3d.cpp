/*=============================================================================
  Module:     Navier-Stokes3d Module

  Contact:    S. Scott Collis
              sscoll@sandia.gov

  Copyright:  (c) 2003 Rice University
              (c) 2008 Sandia National Laboratories
=============================================================================*/

/** \file Navier_Stokes3d.cpp
    \brief Implementation of the 3d Navier-Stokes Equations
    \author S. Scott Collis
*/

// system includes
#include <iostream>
#include <ostream>
#include <sstream>

// DGM includes
#include "TimeInt.hpp"
#include "Fluid.hpp"

// local includes
#include "Navier_Stokes3d.hpp"
#include "Channel.hpp"

namespace Reo {

// Define filter database
FilterDB Navier_Stokes3d::fdb;

// Constructor
Navier_Stokes3d::Navier_Stokes3d( DGM::ArgList &args,
                                  const DGM::Comm::Ptr comm_ )
  : Euler3d(args,comm_), Uv(comm_) {

  // comm->cout()<<"Navier_Stokes3d(int argc, char *argv[])"<<endl;

#ifdef DGM_TRY_ANY

  //===========================================================================
  // try out the any class
  //===========================================================================
  Any value;
  value = LES;
  cout << "Any value = " << value << " of type "
       << value.type().name() << endl;
  map<string,Any> table;
  table["test"] = 1.4;
  table["model"] = LES;
  table["string"] = string("this is a test");
  cout << " test = " << table["test"] << endl;
  cout << " model = " << table["model"] << " for type "
       << table["model"].type().name() << endl;
  cout << " string = " << table["string"] << endl;
  ModelType m(DNS);
  m = table["model"];
  cout << "model = " << m << endl;
  Scalar t(table["test"]);
  cout << "test = " << t << endl;
  //===========================================================================
  // end of try out the any class
  //===========================================================================

#endif

  vis = params["vis"];                  // viscosity
  Pr =  params["Pr"];                   // Prandtl number for air
  gamma = params["gamma"];              // ratio of specific heats

  setup_BCdb();                         // setup BC database

  // make auxiliary Fields using copy constructor
  for (vField::size_type i=0; i<Nfields; i++) {
    Uv.push_back( new Field( U[i], root, U[i]->name ) );
  }

  // setup turbulence model (should be in Turbulence constructor) [SSC]
  model = DNS;                          // defaults to DNS
  model = params["turbtype"];           // Turbulence simulation type
  if (model==LES) {
    comm->cout()<<"Navier_Stokes3d::model == LES"<<endl;
    Cs = params["cs"];                  // Smagorinsky Coefficient
    Delta2 = params["delta2"];          // length scale in the planes
  }

  // setup filter (should be in Filter constructor) [SSC]
  filter = NOFILTER;                    // default to unfilterd filter
  filter = params["filtype"];           // set filter flag
  filter_freq = params["filfreq"];      // set filter frequency
  if (filter != NOFILTER) {
    comm->cout()<< "Navier_Stokes3d::Filter is active at interval "
        << filter_freq << endl;
    string f_name = root + ".fil";
    ifstream specfil(f_name.c_str());
    if (!specfil) {
      stringstream msg;
      msg << "Unable to find spectral filter file: " << f_name << endl;
      comm->error(msg.str());
    }
    efilter.resize(ne);
    for(LocalSize e=0; e<ne; e++) efilter[e] = get_filter(e);
  }

  // try out the fluid_properties class
  fluid = new Sutherland(gamma, 287.0, Pr, 1.716e-5, 110.0, 101000.0, 111.0);

  // allocate workspace
  wk2.resize(20*max(Lmax(),Qmax()));

  // make sure that storage is initialized
  zero_all_fields();
}

/// Filter database management
Filter*  Navier_Stokes3d::get_filter(const Ordinal e) {
  Filter *f;
  char buf[128];
  Ordinal pl = Uv[0]->el[e]->L();
  sprintf(buf,"%lld_",(long long)pl);       // this still can be slow
  string key = buf;
  FilterDB::iterator p = fdb.filters.find(key);
  if ( p == fdb.filters.end() ) {           // not found, make a new one
    f = new SpectralFilter(pl,nsd,root);
    fdb.filters[key] = f;
    // cout<<"Element no:e=>"<<e <<endl;
  } else {                                  // found, return the filter
    f = p->second;
  }
  return f;
}

void Navier_Stokes3d::time_derivative( vField &Us, vField &Uf ) {
  // cout<<"Navier_Stokes3d::time_derivative(...)"<<endl;
  convection( Us, Uf );
  diffusion( Us, Uv, Uf );
  // filter at specified filter frequency
  switch (filter) {
    case APPLYFILTER: {
      if (step%filter_freq==0) {
        // cout << "step%filfreq=>" << step%Filter_freq << endl;
        filter_project(Uf,efilter);
      } else {
        project(Uf);
      }
      break;
    }
    case NOFILTER: {
      project(Uf);
      break;
    }
    default: {
      stringstream msg;
      msg << "Unrecognized filtering directive" << endl;
      comm->error(msg.str());
    }
  }
  if (channel.get()) channel->holdBulkMassFlow(t,Uf);
}

void Navier_Stokes3d::zero_all_fields() {
  Domain::zero_all_fields();
  Uv.zero();
}

/// Set the viscosity
void Navier_Stokes3d::get_viscosity( dVector &mu ) {
  // cout << "Navier_Stokes3d::get_viscosity( dVector &mu )" << endl;
  mu = vis;
}

//===========================================================================
//                        Bassi-Rebay viscous flux
//===========================================================================

/// Add in viscous diffusion
/** \note Currently we interpolate conservative variables. Interpolating
    primitive variable is likely better but, it is easier to interpolate
    conservative. */
void Navier_Stokes3d::diffusion( vField &Us, vField &Uf, vField &Ur ) {
  // cout<<"Navier_Stokes3d::diffusion(...)"<<endl;
  Element *S[NFIELDS], *F[NFIELDS];
  dVector r, ru, rv, rw, rE;
  dVector u, v, w, e, mu, wk;
  dVector ux, uy, uz, vx, vy, vz, wx, wy, wz;
  dVector tau11, tau12, tau13, tau22, tau23, tau33;
  dVector Snorm;

  Us.fill_sides();              // put solution on the sides
  enforce_bc(Us);               // update bc side values
  Us.share_sides();             // communicate sides if parallel

  primitive_sides(Us);          // convert sides to primative variables
  average_flux( Us, Uf, '+' );  // Uf's sides are average state

  for (LocalSize k=0; k<Us[0]->ne; k++) {

    S[0] = Us[0]->el[k];        // local version of the state
    S[1] = Us[1]->el[k];
    S[2] = Us[2]->el[k];
    S[3] = Us[3]->el[k];
    S[4] = Us[4]->el[k];

    F[0] = Uf[0]->el[k];        // local version of the flux
    F[1] = Uf[1]->el[k];
    F[2] = Uf[2]->el[k];
    F[3] = Uf[3]->el[k];
    F[4] = Uf[4]->el[k];

    r.alias (S[0]->u);          // rho
    ru.alias(S[1]->u);          // rho u
    rv.alias(S[2]->u);          // rho v
    rw.alias(S[3]->u);          // rho w
    rE.alias(S[4]->u);          // total energy per volume

    const Ordinal qtot = S[0]->qtot;

    u.alias (wk1,     0,qtot);
    v.alias (wk1,  qtot,qtot);
    w.alias (wk1,2*qtot,qtot);
    e.alias (wk1,3*qtot,qtot);
    mu.alias(wk1,4*qtot,qtot);
    wk.alias(wk1,5*qtot,qtot);

    dvdiv(ru, r, u);            // u-velocity
    dvdiv(rv, r, v);            // v-velocity
    dvdiv(rw, r, w);            // w-velocity
    dvdiv(rE, r, e);            // internal energy + 0.5 |V|^2

    dvmul(u,u,wk);              // wk = u^2
    dvvtvp(v,v,wk,wk);          // wk = u^2 + v^2
    dvvtvp(w,w,wk,wk);          // wk = u^2 + v^2 + w^2
    daxpy(-pt5,wk,e);           // e  = e - 0.5 * wk = internal energy

    ux.alias(wk2,     0,qtot);
    uy.alias(wk2,  qtot,qtot);   tau12.alias(wk2,2*qtot,qtot);
    uz.alias(wk2,3*qtot,qtot);   tau23.alias(wk2,4*qtot,qtot);

    vx.alias(wk2,5*qtot,qtot);   tau11.alias(wk2,6*qtot,qtot);
    vy.alias(wk2,7*qtot,qtot);
    vz.alias(wk2,8*qtot,qtot);   tau22.alias(wk2,9*qtot,qtot);

    wx.alias(wk2,10*qtot,qtot);  tau13.alias(wk2,11*qtot,qtot);
    wy.alias(wk2,12*qtot,qtot);  tau33.alias(wk2,13*qtot,qtot);
    wz.alias(wk2,14*qtot,qtot);

    gradient( S[1], F[1], u, ux, uy, uz );
    gradient( S[2], F[2], v, vx, vy, vz );
    gradient( S[3], F[3], w, wx, wy, wz );

    get_viscosity( mu );

    // ================== Begin LES SGS Model =================

    if (model==LES) {

      // Compute the norm of the strain-rate
      Snorm.alias(wk1,6*qtot,qtot);
      dvmul (ux,ux,Snorm);
      dvvtvp(vy,vy,Snorm,Snorm);
      dvvtvp(wz,wz,Snorm,Snorm);
      scale (2.0, Snorm);
      dvadd (uy, vx, wk);
      dvvtvp(wk,wk,Snorm,Snorm);
      dvadd (uz, wx, wk);
      dvvtvp(wk,wk,Snorm,Snorm);
      dvadd (vz, wy, wk);
      dvvtvp(wk,wk,Snorm,Snorm);
      dvsqrt(Snorm,Snorm);

      // cout<<"Cs=>"<<Cs<<"Delta2=>"<<Delta2<<endl;

      // Van Driest wall damping
      wk = S[0]->C->z;
      for (Ordinal i=0; i<wk.size(); i++)
        wk[i] = min( wk[i], 2.0-wk[i] ); // Distance from wall
      scale( -1.0/25.0/vis, wk );        // Need to specify Re_\tau here!
      for (Ordinal i=0; i<wk.size(); i++)
        wk[i] = 1.0 - exp(wk[i]);
      dvmul( wk, wk );                   // square the damping function
      dvmul( wk, Snorm );
      scale( Cs * Cs * Delta2, Snorm );  // Smagorinsky
      dvadd( Snorm, mu );
    }

    // ================== End LES SGS Model ==================

    // Viscous stress:  tau_{ij} = mu ( 2 S_{ij} - 2\delta_{ij}/3 u_{k,k} )
    dvadd(uy, vx, tau12);
    dvmul(mu, tau12);                // mu ( u_{,y} + v_{,x} )

    dvadd(uz, wx, tau13);
    dvmul(mu, tau13);                // mu ( u_{,z} + w_{,x} )

    dvadd(vz, wy, tau23);
    dvmul(mu, tau23);                // mu ( v_{,z} + w_{,y} )

    daxmy(2.0, ux, vy, wk);          // 2 u_{,x} - v_{,y}
    daxmy(1.0, wk, wz, tau11);       // 2 u_{,x} - v_{,y} - w_{,z}
    scale(2.0/3.0, tau11);           // 2/3 ( 2 u_{,x} - v_{,y} - w_{,z} )
    dvmul(mu, tau11);                // 2/3 mu ( 2 u_{,x} - v_{,y} - w_{,z} )

    daxmy(2.0, vy, ux, wk);          // 2 v_{,y} - u_{,x}
    daxmy(1.0, wk, wz, tau22);       // 2 v_{,y} - u_{,x} - w_{,z}
    scale(2.0/3.0, tau22);           // 2/3 ( 2 v_{,y} - u_{,x} - w_{,z} )
    dvmul(mu, tau22);                // 2/3 mu ( 2 v_{,y} - u_{,x} - w_{,z} )

    daxmy(2.0, wz, ux, wk);          // 2 w_{,z} - u_{,x}
    daxmy(1.0, wk, vy, tau33);       // 2 w_{,z} - u_{,x} - v_{,y}
    scale(2.0/3.0, tau33);           // 2/3 ( 2 w_{,z} - u_{,x} - v_{,y} )
    dvmul(mu, tau33);                // 2/3 mu ( 2 w_{,z} - u_{,x} - v_{,y} )

    // x-momentum equation
    S[1]->fill_sides( tau11, tau12, tau13 );
    S[1]->gradient(tau11, ux, 'x');  // ux = tau_{11,1}
    S[1]->gradient(tau12, wk, 'y');  // wk = tau_{12,2}
    dvadd( ux, wk, F[1]->u );        // F[1]->u = tau_{11,1} + tau_{12,2}
    S[1]->gradient(tau13, wk, 'z');  // wk = tau_{13,3}
    dvadd( wk, F[1]->u );            // F[1]->u += tau_{13,3}

    // y-momentum equation
    S[2]->fill_sides( tau12, tau22, tau23 );
    S[2]->gradient(tau12, ux, 'x');  // ux = tau_{21,1}
    S[2]->gradient(tau22, wk, 'y');  // wk = tau_{22,2}
    dvadd( ux, wk, F[2]->u );        // F[2]->u = tau_{21,1} + tau_{22,2}
    S[2]->gradient(tau23, wk, 'z');  // wk = tau_{23,3}
    dvadd( wk, F[2]->u );            // F[2]->u += tau_{23,3}

    // z-momentum equation
    S[3]->fill_sides( tau13, tau23, tau33 );
    S[3]->gradient(tau13, ux, 'x');  // ux = tau_{31,1}
    S[3]->gradient(tau23, wk, 'y');  // wk = tau_{32,2}
    dvadd( ux, wk, F[3]->u );        // F[3]->u = tau_{31,1} + tau_{32,2}
    S[3]->gradient(tau33, wk, 'z');  // wk = tau_{33,3}
    dvadd( wk, F[3]->u );            // F[3]->u += tau_{33,3}

#ifdef NO_DISSIPATION
    // Turn off dissipation which is equivalent to adding an energy source
    ux = 0.0;
    uy = 0.0;
    uz = 0.0;
#else
    // dissipation: tau_11*u + tau_12*v + tau_13*w in ux
    //              tau_12*u + tau_22*v + tau_23*w in uy
    //              tau_13*u + tau_23*v + tau_33*w in uz
    dvmul (tau11,u,ux);
    dvvtvp(tau12,v,ux,ux);
    dvvtvp(tau13,w,ux,ux);
    dvmul (tau12,u,uy);
    dvvtvp(tau22,v,uy,uy);
    dvvtvp(tau23,w,uy,uy);
    dvmul (tau13,u,uz);
    dvvtvp(tau23,v,uz,uz);
    dvvtvp(tau33,w,uz,uz);
#endif

    // heat conduction (Note: mu*gamma/Pr = kappa/Cv)
    gradient( S[4], F[4], e, vx, vy, vz );  // vx=e_{,x}, vy=e_{,y}, vz=e_{,z}
    dvmul(mu,vx);
    daxpy(gamma/Pr,vx,ux);
    dvmul(mu,vy);
    daxpy(gamma/Pr,vy,uy);
    dvmul(mu,vz);
    daxpy(gamma/Pr,vz,uz);

    // energy equation
    S[4]->fill_sides( ux, uy, uz );
    S[4]->gradient(ux, wk, 'x'); // wk = (tau_{1j} u_j + k/Cv e_{,1})_{,1}
    S[4]->gradient(uy, ux, 'y'); // ux = (tau_{2j} u_j + k/Cv e_{,2})_{,2}
    dvadd( wk, ux, F[4]->u );
    S[4]->gradient(uz, wk, 'z'); // wk = (tau_{3j} u_j + k/Cv e_{,3})_{,3}
    dvadd( wk, F[4]->u );        // F[4]->u = (tau_{ij} u_j + k/Cv e_{,i})_{,i}
  }

  Us.share_sides();                        // Share sides with your neighbors
  enforce_flux_bc(Us);                     // put flux BC's on bc sides
  average_flux( Us, Uf, '-' );

  // Note there is no diffusion contribution to the continuity equation
  for (vField::size_type n=1; n<Us.size(); n++) {
    for (LocalSize k=0; k<Us[n]->ne; k++) {
      S[n] = Us[n]->el[k];
      F[n] = Uf[n]->el[k];
      S[n]->lift( F[n], F[n]->u );
    }
  }
  scale(-one, Uf);                         // everything is on the LHS
  for (vField::size_type n=1; n<Uf.size(); n++) add( Uf[n], Ur[n] );
}

//===========================================================================
//                        BC database management
//===========================================================================

/// Load up the available BC types
void Navier_Stokes3d::setup_BCdb( ) {
  //  cout << "Navier_Stokes3d::setup_BCdb()" << endl;

  // set default BC types
  dVector ub(Nfields);
  Scalar Eref = 20.34126984126985; // Ma_ref = 0.3
  ub[0] = 1.0;
  ub[1] = 1.0;
  ub[2] = 0.0;
  ub[3] = 0.0;
  ub[4] = Eref;
  BC_db["S"].reset( new StateBC("S",ub) );
  BC_db["W"].reset( new Isothermal_WallBC("W", 5, 1.0, Eref) );

  // read new BC types from file
  string fname = root+".bct";
  ifstream in(fname.c_str());
  if (in) Navier_Stokes3d::read_BCdb( in );   // database of active BC types
}

void Navier_Stokes3d::read_BCdb( ifstream &in ) {
  //  cout << "Navier_Stokes3d::read_BCdb( ifstream &in )" << endl;
  string tag;
  BC *pbc;
  while ( (pbc = Navier_Stokes3d::make_BC(in,tag)) ) {
    if ( BC_db.find(tag) != BC_db.end() )
      cerr << "WARNING in Navier_Stokes3d::read_BCdb:  Overriding BC type \""
      << tag << "\"." << endl;
    BC_db[tag].reset( pbc );
  }
}

BC* Navier_Stokes3d::make_BC ( ifstream &in, string &tag) {
  // cout << "Navier_Stokes3d::make_BC(ifstream &in, string &tag)" << endl;
  string code;
  if (!(in>>code)) return NULL;
  code = lowerCase(code);
  if (code=="state") {
    if (!(in>>tag))
      error("Navier_Stokes3d::make_BC: Cannot read StateBC tag",1);
    return new StateBC(tag,in,5);
  } else if (code=="isothermal_wall") {
    if (!(in>>tag))
      error("Navier_Stokes3d::make_BC:  Cannot read Isothermal_WallBC tag",1);
    return new Isothermal_WallBC(tag,in,5);
  } else if (code=="periodic_wall") {
    if (!(in>>tag))
      error("Navier_Stokes3d::make_BC:  Cannot read Isothermal_WallBC tag",1);
    return new Periodic_WallBC(tag,in,5);
  } else if (code=="isoflux_wall" || code=="wall" ) {
    if (!(in>>tag))
      error("Navier_Stokes3d::make_BC:  Cannot read Isoflux_WallBC tag",1);
    return new Isoflux_WallBC(tag,in,5);
  } else {
    error("Navier_Stokes3d::make_BC:  Illegal BC type:  "+code,1);
  }
  return NULL;
}

void Navier_Stokes3d::enforce_bc(vField &F) {
  for (BC::db_citr i=BC_db.begin(); i!= BC_db.end(); ++i)
    i->second->apply( t, F );
}

/** \pre On entry, F should hold the interior diffusive flux. */
void Navier_Stokes3d::enforce_flux_bc(vField &F) {
  for (BC::db_citr i=BC_db.begin(); i!= BC_db.end(); ++i)
    i->second->apply_flux( t, F );
}

//===========================================================================
//                        Isothermal Solid Wall
//===========================================================================

void Navier_Stokes3d::Isothermal_WallBC::apply( const Scalar t,
                                                const vField &F ) {
  vector<Side*> S(F.size()), B(F.size());
  for (LocalSize n=0; n<F[0]->nbc; ++n)   // loop over field boundaries
    if (F[0]->bc[n]->type == type ){
      //dVector &nx = F[0]->bc[n]->S->nx();
      //dVector &ny = F[0]->bc[n]->S->ny();
      for (vField::size_type i=0; i<F.size(); ++i){
        S[i] = F[i]->bc[n]->S;
        B[i] = F[i]->bc[n]->B;
      }
      for (LocalSize i=0; i<S[0]->qtot(); i++) {
        B[0]->u[i] = S[0]->u[i];
        B[1]->u[i] = 0.0;
        B[2]->u[i] = 0.0;
        B[3]->u[i] = 0.0;
        // Ew = (rho*Tw)/(gamma*(gamma-1)*Ma^2)
        B[4]->u[i] = (Eref-pt5)*B[0]->u[i]*Tw;
      }
    }
}

void Navier_Stokes3d::Isothermal_WallBC::apply_flux( const Scalar t,
                                                     const vField &F ) {
  vector<Side*> S(F.size()), B(F.size());
  for (LocalSize n=0; n<F[0]->nbc; ++n)   // loop over field boundaries
    if (F[0]->bc[n]->type == type ) {
      //dVector &nx = F[0]->bc[n]->S->nx();
      //dVector &ny = F[0]->bc[n]->S->ny();
      for (vField::size_type i=0; i<F.size(); ++i) {
        S[i] = F[i]->bc[n]->S;
        B[i] = F[i]->bc[n]->B;
      }
      for (LocalSize i=0; i<S[0]->qtot(); i++) {
        B[0]->u[i] = -S[0]->u[i];
        B[1]->u[i] = -S[1]->u[i];
        B[2]->u[i] = -S[2]->u[i];
        B[3]->u[i] = -S[3]->u[i];
        B[4]->u[i] = -S[4]->u[i];
      }
    }
}

void Navier_Stokes3d::Isothermal_WallBC::adjoint_apply(const Scalar t,
                                                       const vField &state,
                                                       const vField &adjoint) {
  error("Navier_stokes3d::Isothermal_WallBC::adjoint_apply() not implemented");
}

void Navier_Stokes3d::Isothermal_WallBC::adjoint_apply_flux
(const Scalar t, const vField &state, const vField &adjoint) {
  error("NS3d::Isothermal_WallBC::adjoint_apply_flux() not implemented.");
}

//===========================================================================
//                     Constant Heat Flux Solid Wall
//===========================================================================

void Navier_Stokes3d::Isoflux_WallBC::apply( const Scalar t, const vField &F) {
  vector<Side*> S(F.size()), B(F.size());
  for (LocalSize n=0; n<F[0]->nbc; ++n)   // loop over field boundaries
    if (F[0]->bc[n]->type == type ) {
      //dVector &nx = F[0]->bc[n]->S->nx();
      //dVector &ny = F[0]->bc[n]->S->ny();
      for (vField::size_type i=0; i<F.size(); ++i){
        S[i] = F[i]->bc[n]->S;
        B[i] = F[i]->bc[n]->B;
      }
      for (LocalSize i=0; i<S[0]->qtot(); i++) {
        B[0]->u[i] = S[0]->u[i];
        B[1]->u[i] = 0.0;
        B[2]->u[i] = 0.0;
        B[3]->u[i] = 0.0;
        B[4]->u[i] = S[3]->u[i]
              - pt5*(S[1]->u[i]*S[1]->u[i] + S[2]->u[i]*S[2]->u[i])/S[0]->u[i]
              + pt5*(B[1]->u[i]*B[1]->u[i] + B[2]->u[i]*B[2]->u[i])/B[0]->u[i];
      }
    }
}

void Navier_Stokes3d::Isoflux_WallBC::apply_flux( const Scalar t,
    const vField &F ) {
  vector<Side*> S(F.size()), B(F.size());
  for (LocalSize n=0; n<F[0]->nbc; ++n)   // loop over field boundaries
    if (F[0]->bc[n]->type == type ) {
      //dVector &nx = F[0]->bc[n]->S->nx();
      //dVector &ny = F[0]->bc[n]->S->ny();
      for (vField::size_type i=0; i<F.size(); ++i){
        S[i] = F[i]->bc[n]->S;
        B[i] = F[i]->bc[n]->B;
      }
      for (LocalSize i=0; i<S[0]->qtot(); i++) {
        B[0]->u[i] = -S[0]->u[i];
        B[1]->u[i] = -S[1]->u[i];
        B[2]->u[i] = -S[2]->u[i];
        B[3]->u[i] = -S[2]->u[i];
        B[4]->u[i] = -qw;
      }
    }
}

void Navier_Stokes3d::Isoflux_WallBC::adjoint_apply( const Scalar t,
    const vField &state,
    const vField &adjoint) {
  error("Navier_stokes3d::Isoflux_WallBC::adjoint_apply() not implemented.");
}


void Navier_Stokes3d::Isoflux_WallBC::adjoint_apply_flux(const Scalar t,
    const vField &state,
    const vField &adjoint)
{
  error("Navier_stokes3d::Isoflux_WallBC::adjoint_apply_flux() unimplemented");
}

//--===========================================================================

/// Computes forces on a boundary and saves every time-step
void Navier_Stokes3d::write_bndry_stats() {
  static FILE *out = NULL;

  if (!U[0]->bndry_stats->valid) return;

  comm->error("Navier_Stokes3d::write_bndry_stats() not implemented");

  if (comm->Master()) {
    if (!out) {
      string fname;
      char buf[80];
      sprintf(buf,"%s.frc",root.c_str());
      fname = buf;
      out = fopen(fname.c_str(),"a+");  // append to end of file
    }
  }

  dVector r, ru, rv, rw, rE;
  U[0]->bndry_stats->get_solution( r );
  U[1]->bndry_stats->get_solution( ru );
  U[2]->bndry_stats->get_solution( rv );
  U[3]->bndry_stats->get_solution( rw );
  U[4]->bndry_stats->get_solution( rE );

  const Ordinal qtot = r.size();
  dVector u(qtot), v(qtot), w(qtot), p(qtot), e(qtot), wk(qtot);

  dvdiv(ru, r, u);   // compute u
  dvdiv(rv, r, v);   // compute v
  dvdiv(rw, r, w);   // compute w
  dvdiv(rE, r, e);   // internal energy + 0.5 |V|^2

  dvmul(u,u,wk);     // wk = u^2
  dvvtvp(v,v,wk,wk); // wk = u^2 + v^2
  dvvtvp(w,w,wk,wk); // wk = u^2 + v^2 + w^2
  daxpy(-pt5,wk,e);  // e  = e - 0.5 * wk = internal energy

  // p = (gamma-1.0)*(rE-0.5*(r*u*u + r*v*v + r*w*w))
  dvmul(u, ru, p);
  dvvtvp(v, rv, p, p);
  dvvtvp(w, rw, p, p);
  scale(-pt5*(gamma-1.0), p);
  daxpy(gamma-1.0, rE, p);

#ifdef DGM_PARALLEL
  Scalar llift=0, ldrag=0;  // local lift and drag
  llift = U[0]->bndry_stats->liftcalc(p);
  ldrag = U[0]->bndry_stats->dragcalc(p);
  Scalar lift, drag;
  comm->SumAll( &llift, &lift, 1 );
  comm->SumAll( &ldrag, &drag, 1 );
  if (comm->Master()) {
    fprintf(out, "%18.11e %18.11e %18.11e\n", t, drag, lift);
  }
#else
  fprintf(out, "%14.7e %14.7e %14.7e\n", t,
      U[0]->bndry_stats->dragcalc(p),
      U[0]->bndry_stats->liftcalc(p));
  fflush(out);
#endif
}

} // namespace Reo
