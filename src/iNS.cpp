/** \file iNS.cpp
    \brief Incompressible Navier-Stokes equations   */

// DGM includes
#include "TimeInt.hpp"

// local includes
#include "iNS.hpp"
#include "iNSBC.hpp"

namespace Reo {

// constructor
iNS::iNS( DGM::ArgList &args, const DGM::Comm::Ptr comm_ ) :
  iEuler( args, comm_ ), Uv(comm_) {

  vis   = params["vis"];               // viscosity

  setup_BCdb();                        // setup BC database

  // make auxiliary Fields using copy constructor
  for (vField::size_type i=0; i<Nfields; i++) {
    Uv.push_back( new Field( U[i], root, U[i]->name ) );
  }

  // allocate workspace
  work.resize(10*max(Lmax(),Qmax()));

  // make sure that storage is initialized
  zero_all_fields();
}

void iNS::set_material() {
}

// override iEuler::time_derivative
void iNS::time_derivative( vField &Us, vField &Uf ) {
  pressure_projection( Us, Uf, P, Pr );
  Uf.zero();
#ifndef REO_IEULER_CONVECTION_OFF
  convection( Us, Uf );
#endif
  diffusion( Us, Uv, Uf );
  add_source(Us,Uf);
  project( Uf );
}

void iNS::zero_all_fields() {
  // cout << "zero_all_fields()" << endl;
  Domain::zero_all_fields();
  Uv.zero();
}

void iNS::get_viscosity( dVector &mu ) {
  // cout << "iNS::get_viscosity( dVector &mu )" << endl;
  mu = vis;
}

//===========================================================================
// Bassi-Rebay viscous flux
//===========================================================================
void iNS::diffusion( vField &Us, vField &Uf, vField &Ur ) {
  Element *S[2], *F[2];
  dVector u, v, ux, uy, vx, vy, tau11, tau12, tau22, wk;

  Us.fill_sides();                   // put solution on the sides
  enforce_bc(Us);                    // update bc side values
  Us.share_sides();                  // communicate sides if parallel
  average_flux( Us, Uf, '+' );       // Uf's sides are average state

  for (LocalSize k=0; k<Us[0]->ne; k++) {

    S[0] = Us[0]->el[k];  // local version of the state
    S[1] = Us[1]->el[k];

    F[0] = Uf[0]->el[k];  // local version of the flux
    F[1] = Uf[1]->el[k];

    const Ordinal qtot = S[0]->qtot;

    u.alias(S[0]->u);
    v.alias(S[1]->u);

    ux.alias(work,     0,qtot);
    uy.alias(work,  qtot,qtot);  tau12.alias(work,2*qtot,qtot);
    vx.alias(work,3*qtot,qtot);  tau11.alias(work,4*qtot,qtot);
    vy.alias(work,5*qtot,qtot);  tau22.alias(work,6*qtot,qtot);
    wk.alias(work,7*qtot,qtot);

    gradient( S[0], F[0], u, ux, uy );
    gradient( S[1], F[1], v, vx, vy );

    get_viscosity( wk );

    // Viscous stress:  tau_{ij} = mu ( 2 S_{ij} - 2\delta_{ij}/3 u_{k,k} )
    dvadd(uy, vx, tau12);
    dvmul(wk, tau12);                // mu ( u_{,y} + v_{,x} )

    scale(2.0, ux);                  // 2 u_{,x}
    dvmul(wk, ux, tau11);            // 2 mu u_{,x}

    scale(2.0, vy);                  // 2 v_{,y}
    dvmul(wk, vy, tau22);            // 2 mu v_{,y}

    // x-momentum equation
    S[0]->fill_sides( tau11, tau12 );
    S[0]->gradient(tau11, ux, 'x');  // ux = tau_{11,1}
    S[0]->gradient(tau12, wk, 'y');  // wk = tau_{12,2}
    dvadd( ux, wk, F[0]->u );        // F[1]->u = tau_{11,1} + tau_{12,2}

    // y-momentum equation
    S[1]->fill_sides( tau12, tau22 );
    S[1]->gradient(tau12, ux, 'x');  // ux = tau_{21,1}
    S[1]->gradient(tau22, wk, 'y');  // wk = tau_{22,2}
    dvadd( ux, wk, F[1]->u );        // F[2]->u = tau_{21,1} + tau_{22,2}
  }

  Us.share_sides();                  // Share sides with your neighbors
  enforce_flux_bc(Us);               // put flux BC's on bc sides
  average_flux( Us, Uf, '-' );

  for (vField::size_type n=0; n<Us.size(); n++) {
    for (LocalSize k=0; k<Us[n]->ne; k++) {
      S[k] = Us[n]->el[k];
      F[k] = Uf[n]->el[k];
      S[k]->lift( F[k], F[k]->u );
    }
  }

  // add in viscous contribution
  scale(-one,Uf);  // I currrently put everything on the LHS
  for (vField::size_type n=0; n<Uf.size(); n++) add( Uf[n], Ur[n] );
}

//===========================================================================
//                        BC database management
//===========================================================================

// Load up the available BC types
void iNS::setup_BCdb( ) {
  // cout << "iNS::setup_BCdb()" << endl;

  // set default BC types
  dVector ub(2);
  ub[0] = 1.0;
  ub[1] = 0.0;
  BC_db["S"].reset( new StateBC("S", ub) );
  BC_db["W"].reset( new WallBC("W") );

  // read new BC types from file
  string fname = root+".bct";
  ifstream in(fname.c_str());
  if (in) iNS::read_BCdb( in );   // database of active BC types

  // Option:  you could slave Euler::BC_db to iNS::BC_db here...
}

void iNS::read_BCdb( ifstream &in ) {
  //  cout << "iNS::read_BCdb( ifstream &in )" << endl;
  string tag;
  BC *pbc;
  while ( (pbc = iNS::make_BC(in,tag)) ) {
    if ( BC_db.find(tag) != BC_db.end() )
      cerr << "WARNING in iNS::read_BCdb:  Overriding BC type \""
           << tag << "\"." << endl;
    BC_db[tag].reset( pbc );
  }
}

BC* iNS::make_BC ( ifstream &in, string &tag) {
  //  cout << "iNS::make_BC(ifstream &in, string &tag)" << endl;
  string code;
  if (!(in>>code)) return NULL;
  code = lowerCase(code);
  if (code=="state") {
    if (!(in>>tag)) error("iNS::make_BC:  Cannot read State tag",1);
    return new StateBC(tag,in,4);
  } else if (code=="wall") {
    if (!(in>>tag))
      error("iNS::make_BC:  Cannot read Wall tag",1);
    return new WallBC(tag,in);
  } else {
    error("iNS::make_BC:  Illegal BC type:  "+code,1);
  }
  return NULL;
}

// Add source terms
void iNS::add_source(const vField &Us, vField &Ur) {
  // cout << "Euler::add_source(vField &)" << endl;
  for (Source::db_citr i=Source_db.begin(); i!= Source_db.end(); ++i)
    // cout << "Adding source: " << i->first << endl;
    i->second->apply( t, Us, Ur );

}

// Uses iNS::BC_db
void iNS::enforce_bc(vField &F) {
  for (BC::db_citr i=BC_db.begin(); i!= BC_db.end(); ++i)
    i->second->apply( t, F );
}

// Uses iNS::BC_db
// On entry, S should hold the interior diffusive flux
void iNS::enforce_flux_bc(vField &F) {
  for (BC::db_citr i=BC_db.begin(); i!= BC_db.end(); ++i)
    i->second->apply_flux( t, F );
}

} // namespace Reo
