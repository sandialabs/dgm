/** \file  Navier_Stokes.cpp
    \brief Implements the 2d Navier-Stokes equations. */

// DGM includes
#include "TimeInt.hpp"

// Reo includes
#include "Fluid.hpp"
#include "Navier_Stokes.hpp"
#include "Navier_StokesBC.hpp"
#include "EulerBC.hpp"

namespace Reo {

using namespace DGM;

// Constructor
  Navier_Stokes::Navier_Stokes( DGM::ArgList &args, const DGM::Comm::Ptr comm_)
  : Euler( args, comm_ ), Uv(comm_) {
  // cout << "Navier_Stokes::Navier_Stokes(int argc, char *argv[])" << endl;

  vis   = params["vis"];               // viscosity
  Pr    = params["Pr"];                // Prandtl number for air
  gamma = params["gamma"];             // ratio of specific heats

  parse_args(args);

  setup_BCdb();                        // setup BC database

  // make auxiliary Fields using copy constructor
  for (vField::size_type i=0; i<Nfields; i++) {
    Uv.push_back( new Field( U[i], root, U[i]->name ) );
  }
  Uv.set_name("Uv");

  // allocate workspace
  work.resize(15*max(Lmax(),Qmax()));

  // make sure that storage is initialized
  zero_all_fields();
}

Navier_Stokes::~Navier_Stokes() {
}

// Parse parameters from the argument list
void Navier_Stokes::parse_args( DGM::ArgList &args ) {
  string name, value;
  list< DGM::ArgList::iterator > li;
  for ( DGM::ArgList::iterator a = args.begin(); a != args.end(); a++ ) {
    if ( (*a)[0] == '-' ) {
      name = *a;
      if (name == "-help") {
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

void Navier_Stokes::showUsage() {
  comm->cout()
    << "Navier-Stokes Class Options \n"
    << "----------------------------------------------------------------\n"
    << "         " << '\t' << "None currently supported\n"
    << "----------------------------------------------------------------\n";
}

void Navier_Stokes::set_material() {
  fluid = new Sutherland(gamma, 287.0, Pr, 1.716e-5, 110.0, 101000.0, 111.0);
  material = fluid;
#ifdef DGM_TEST_FLUID
  cout << "Sutherland::gamma() = " << fluid->gamma() << endl;
  cout << "Sutherland::Ma_ref() = " << fluid->Ma() << endl;
  cout << "Sutherland::Rgas() = " << fluid->Rgas() << endl;
  cout << "Sutherland::cv() = " << fluid->cv(110.0) << endl;
  cout << "Sutherland::cp() = " << fluid->cp(110.0) << endl;
  cout << "Sutherland::mu() = " << fluid->mu(110.0) << endl;
  cout << "Sutherland::lambda() = " << fluid->lambda(110.0) << endl;
  cout << "Sutherland::kappa() = " << fluid->kappa(110.0) << endl;
#endif
}

void Navier_Stokes::time_derivative( vField &Us, vField &Uf ) {
  convection( Us, Uf );
  diffusion( Us, Uv, Uf );
  add_source(Us,Uf);
  project( Uf );
}

void Navier_Stokes::zero_all_fields() {
  // cout << "zero_all_fields()" << endl;
  Domain::zero_all_fields();
  Uv.zero();
}

/// Return the viscosity
void Navier_Stokes::get_viscosity( dVector &mu ) {
  // cout << "Navier_Stokes::get_viscosity( dVector &mu )" << endl;
  mu = vis;
}

//===========================================================================
//                     Bassi-Rebay viscous flux
//===========================================================================

/// Compute the Navier-Stokes diffusion term
void Navier_Stokes::diffusion( vField &Us, vField &Uf, vField &Ur ) {
  Element *S[NFIELDS], *F[NFIELDS];
#ifdef LOCAL_TEMPS
  dVector u, v, p, e, wk;
  dVector r, ru, rv, rE;
  dVector ux, uy, vx, vy, tau12, tau11, tau22;
#endif

  // NOTE: We interpolate conservative vars, it is likely better to
  //       interpolate primitive variables but, it is easier for me to
  //       interpolate conservative.
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

#ifdef LOCAL_TEMPS
    r.alias (S[0]->u);  // rho
    ru.alias(S[1]->u);  // rho u
    rv.alias(S[2]->u);  // rho v
    rE.alias (S[3]->u); // total energy density

    u.alias(work,0,qtot);
    v.alias(work,qtot,qtot);
    e.alias(work,2*qtot,qtot);
    wk.alias(work,3*qtot,qtot);
#else
    dVector r (S[0]->u);  // rho
    dVector ru(S[1]->u);  // rho u
    dVector rv(S[2]->u);  // rho v
    dVector rE(S[3]->u);  // total energy density

    dVector u(qtot);
    dVector v(qtot);
    dVector e(qtot);
    dVector wk(qtot);
#endif

    dvdiv(ru, r, u);   // u-velocity
    dvdiv(rv, r, v);   // v-velocity
    dvdiv(rE, r, e);   // internal energy + 0.5 |V|^2

    dvmul(u,u,wk);     // wk = u^2
    dvvtvp(v,v,wk,wk); // wk = u^2 + v^2
    daxpy(-pt5,wk,e);  // e  = e - 0.5 * wk = internal energy

#ifdef LOCAL_TEMPS
    ux.alias(work,4*qtot,qtot);
    uy.alias(work,5*qtot,qtot);  tau12.alias(work,8*qtot,qtot);
    vx.alias(work,6*qtot,qtot);  tau11.alias(work,9*qtot,qtot);
    vy.alias(work,7*qtot,qtot);  tau22.alias(work,10*qtot,qtot);
#else
    dVector ux(qtot);
    dVector uy(qtot);  dVector tau12(qtot);
    dVector vx(qtot);  dVector tau11(qtot);
    dVector vy(qtot);  dVector tau22(qtot);
#endif

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
    dvadd( wk, ux, F[3]->u );    // F[3]->u = (tau_{ij} u_j + k/Cv e_{,i})_{,i}
  }

  Us.share_sides();                        // Share sides with your neighbors
  enforce_flux_bc(Us);                     // put flux BC's on bc sides
  average_flux( Us, Uf, '-' );

  // Note there is no contribution to the continuity equation
  for (vField::size_type n=1; n<Us.size(); n++) {
    for (LocalSize k=0; k<Us[n]->ne; k++) {
      S[n] = Us[n]->el[k];
      F[n] = Uf[n]->el[k];
      S[n]->lift( F[n], F[n]->u );
    }
  }

  // add in viscous contribution
  scale(-one, Uf);                         // put everything on the LHS
  for (vField::size_type n=1; n<Uf.size(); n++) add( Uf[n], Ur[n] );
}

//===========================================================================
//                        BC database management
//===========================================================================

// Load up the available BC types
void Navier_Stokes::setup_BCdb( ) {
  // cout << "Navier_Stokes::setup_BCdb()" << endl;

  // set default BC types
  dVector ub(4);
  const Scalar Eref = 20.34126984126985; // Uniform flow at Ma_ref = 0.3
  ub[0] = 1.0;
  ub[1] = 1.0;
  ub[2] = 0.0;
  ub[3] = Eref;
  BC_db["S"].reset( new StateBC("S", ub) );
  BC_db["W"].reset( new Isothermal_WallBC("W", 1.0, Eref) );

  // read new BC types from file
  string fname = root+".bct";
  ifstream in(fname.c_str());
  if (in) Navier_Stokes::read_BCdb( in );   // database of active BC types

  // Option:  you could slave Euler::BC_db to Navier_Stokes::BC_db here...
}

void Navier_Stokes::read_BCdb( ifstream &in ) {
  //  cout << "Navier_Stokes::read_BCdb( ifstream &in )" << endl;
  string tag;
  BC *pbc;
  while ( (pbc = Navier_Stokes::make_BC(in,tag)) ) {
    if ( BC_db.find(tag) != BC_db.end() )
      comm->cerr() << "WARNING in Navier_Stokes::read_BCdb:  "
                   << "Overriding BC type \"" << tag << "\"." << endl;
    BC_db[tag].reset( pbc );
  }
}

BC* Navier_Stokes::make_BC ( ifstream &in, string &tag) {
  //  cout << "Navier_Stokes::make_BC(ifstream &in, string &tag)" << endl;
  string code;
  if (!(in>>code)) return NULL;
  code = lowerCase(code);
  if (code=="state") {
    if (!(in>>tag)) error("Navier_Stokes::make_BC:  Cannot read State tag",1);
    return new StateBC(tag,in,4);
  } else if (code=="euler_wall") {
    if (!(in>>tag))
      error("Navier_Stokes::make_BC:  Cannot read Euler_Wall tag",1);
    return new Euler::WallBC(tag,in);
  } else if (code=="isothermal_wall") {
    if (!(in>>tag))
      error("Navier_Stokes::make_BC:  Cannot read Isothermal_Wall tag",1);
    return new Isothermal_WallBC(tag,in);
  } else if (code=="isoflux_wall" || code=="wall" ) {
    if (!(in>>tag))
      error("Navier_Stokes::make_BC:  Cannot read Isoflux_Wall tag",1);
    return new Isoflux_WallBC(tag,in,gamma,vis,Pr);
  } else if (code=="isothermal_slipwall") {
    if (!(in>>tag))
      error("Navier_Stokes::make_BC:  Cannot read Isothermal_Wall tag",1);
    return new Isothermal_SlipWallBC(tag,in);
  } else if (code=="isoflux_slipwall") {
    if (!(in>>tag))
      error("Navier_Stokes::make_BC:  Cannot read Isoflux_Wall tag",1);
    return new Isoflux_SlipWallBC(tag,in,gamma,vis,Pr);
  } else if (code=="isothermal_control") {
    if (!(in>>tag))
      error("Navier_Stokes::make_BC:  Cannot read Isothermal_Wall tag",1);
    return new Isothermal_ControlBC(tag,in,&U,gamma,vis,Pr);
  } else if (code=="isoflux_control" ) {
    if (!(in>>tag))
      error("Navier_Stokes::make_BC:  Cannot read Isoflux_Wall tag",1);
    return new Isoflux_ControlBC(tag,in,&U,gamma,vis,Pr);
  } else if (code=="isothermal_steadycontrol") {
    if (!(in>>tag))
      error("Navier_Stokes::make_BC:  Cannot read Isothermal_Wall tag",1);
    return new Isothermal_SteadyControlBC(tag,in,&U,gamma,vis,Pr);
  } else if (code=="isoflux_steadycontrol" ) {
    if (!(in>>tag))
      error("Navier_Stokes::make_BC:  Cannot read Isoflux_Wall tag",1);
    return new Isoflux_SteadyControlBC(tag,in,&U,gamma,vis,Pr);
  } else if (code=="isoflux_stress_control" ) {
    if (!(in>>tag))
      error("Navier_Stokes::make_BC:  Cannot read Isoflux_Stress tag",1);
    return new Isoflux_stress_ControlBC(tag,in,&U,gamma,vis,Pr);
  } else if (code=="jet_control" ) {
    if (!(in>>tag))
      error("Navier_Stokes::make_BC:  Cannot read Jet_Control tag",1);
    return new Jet_ControlBC(tag,in,&U,gamma,vis,Pr);
  } else if (code=="sondhaus" ) {
    if (!(in>>tag))
      error("Navier_Stokes::make_BC:  Cannot read SondhausWall tag",1);
    return new SondhausWallBC(tag,in,gamma);
  } else if (code=="subsonicoutflow" ) {
    if (!(in>>tag))
      error("Navier_Stokes::make_BC:  Cannot read SubsonicOutflow tag",1);
    return new Euler::SubsonicOutflowBC(tag,in);
  } else if ( code.find("supersonicoutflow") != code.npos ) {
    if (!(in >>tag)) error("Euler::make_BC: Cannot read SupersonicOutflow tag");
    return new Euler::SubsonicOutflowBC(tag,in);
  } else {
    error("Navier_Stokes::make_BC:  Illegal BC type:  "+code,1);
  }
  return NULL;
}

// Uses Navier_Stokes::BC_db
void Navier_Stokes::enforce_bc(vField &F) {
  for (BC::db_citr i=BC_db.begin(); i!= BC_db.end(); ++i)
    i->second->apply( t, F );
}

// Uses Navier_Stokes::BC_db
// On entry, F should hold the interior diffusive flux
void Navier_Stokes::enforce_flux_bc(vField &F) {
  for (BC::db_citr i=BC_db.begin(); i!= BC_db.end(); ++i)
    i->second->apply_flux( t, F );
}

// Add source terms
void Navier_Stokes::add_source(const vField &Us, vField &Ur) {
  // cout << "Navier_Stokes::add_source(vField &)" << endl;
  for (Source::db_citr i=Source_db.begin(); i!= Source_db.end(); ++i)
    // cout << "Adding source: " << i->first << endl;
    i->second->apply( t, Us, Ur );

}

/// If defined, then use the jump savy gradient on the boundary
#define REO_NS_JUMP

/// Computes lift and drag and saves every time-step
void Navier_Stokes::write_bndry_stats() {
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

  dVector r, ru, rv, E;
  U[0]->bndry_stats->get_solution( r );
  U[1]->bndry_stats->get_solution( ru );
  U[2]->bndry_stats->get_solution( rv );
  U[3]->bndry_stats->get_solution( E );

  const LocalSize qtot = r.size();
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
  dVector tau12(qtot), tau11(qtot), tau22(qtot);

#ifdef REO_NS_JUMP
  U.fill_sides();
  enforce_bc( U );
  U.share_sides();
  primitive_sides( U );
  average_flux( U, Ut, '+' );

  Element *S[NFIELDS], *F[NFIELDS];
  Size eid;
  LocalSize qtott=0, qsid;
  for (size_t i=0; i<U[0]->bndry_stats->sides.size(); ++i)
    qtott += U[0]->bndry_stats->sides[i]->qtot(); // Total number of dof on bnd.

  r_x.resize(qtott) ; r_y.resize(qtott);
  ru_x.resize(qtott); ru_y.resize(qtott);
  rv_x.resize(qtott); rv_y.resize(qtott);

  qtott=0;
  for (size_t i=0; i< U[0]->bndry_stats->sides.size(); i++) {
    eid  = U[0]->bndry_stats->sides[i]->leid();  // Element ie on the boundary
    qsid = U[0]->bndry_stats->sides[i]->qtot();  // Quadrature pts on side[i]

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

    const LocalSize qtot = U[0]->el[eid]->qtot;

    dVector pr(S[0]->u), pru(S[1]->u), prv(S[2]->u);  // rho, rhou, and rhov
    dVector pr_x(qtot), pr_y(qtot), pru_x(qtot), pru_y(qtot),
            prv_x(qtot), prv_y(qtot);

    gradient( S[0], F[0], pr,  pr_x,  pr_y );

    temp.alias(r_x,qtott,qsid);
    S[0]->load_side(pr_x , U[0]->bndry_stats->sides[i]->id(), temp);
    temp.alias(r_y,qtott,qsid);
    S[0]->load_side(pr_y , U[0]->bndry_stats->sides[i]->id(), temp);

    gradient( S[1], F[1], pru, pru_x, pru_y );

    temp.alias(ru_x,qtott,qsid);
    S[1]->load_side(pru_x, U[0]->bndry_stats->sides[i]->id(), temp);
    temp.alias(ru_y,qtott,qsid);
    S[1]->load_side(pru_y, U[0]->bndry_stats->sides[i]->id(), temp);

    gradient( S[2], F[2], prv, prv_x, prv_y );

    temp.alias(rv_x,qtott,qsid);
    S[2]->load_side(prv_x, U[0]->bndry_stats->sides[i]->id(), temp);
    temp.alias(rv_y,qtott,qsid);
    S[2]->load_side(prv_y, U[0]->bndry_stats->sides[i]->id(), temp);

    qtott += qsid;
  }
#else
  // No Jump Savy gradient
  U[0]->bndry_stats->get_solution_gradient(r_x, r_y);
  U[1]->bndry_stats->get_solution_gradient(ru_x, ru_y);
  U[2]->bndry_stats->get_solution_gradient(rv_x, rv_y);
#endif

  // Form derivatives of primitive variable in terms of conserved variables
  dvmul( r_x , u  , u_x );
  dvsub( ru_x, u_x, u_x );
  dvdiv( u_x , r  , u_x );

  dvmul( r_x , v  , v_x );
  dvsub( rv_x, v_x, v_x );
  dvdiv( v_x , r  , v_x );

  dvmul( r_y , u  , u_y );
  dvsub( ru_y, u_y, u_y );
  dvdiv( u_y , r  , u_y );

  dvmul( r_y , v  , v_y );
  dvsub( rv_y, v_y, v_y );
  dvdiv( v_y , r  , v_y );

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
  }
#else
  fprintf(out, "%18.11e %18.11e %18.11e\n", t,
          U[0]->bndry_stats->dragcalc(p,tau11,tau12),
          U[0]->bndry_stats->liftcalc(p,tau12,tau22) );
  fflush(out);
#endif
}

} // namespace Reo
