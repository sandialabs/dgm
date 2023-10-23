/** \file iEuler.cpp
    \brief Incompressible Euler equations
    \author Scott Collis
*/

// DGM includes
#ifdef DGM_PARALLEL
#include "MpiComm.hpp"
#endif

// local includes
#include "Reo.hpp"
#include "iEuler.hpp"
#include "iEulerIC.hpp"
#include "iEulerBC.hpp"

// Trilinos includes
#ifdef DGM_USE_EPETRA
#ifdef DGM_PARALLEL
#include "Epetra_MpiComm.h"
#else
#include "Epetra_SerialComm.h"
#endif
#include "Epetra_Map.h"
#include "Epetra_BlockMap.h"
#include "Epetra_Vector.h"
#include "Epetra_CrsGraph.h"
#include "Epetra_CrsMatrix.h"
#include "Epetra_VbrMatrix.h"
#include "Epetra_LinearProblem.h"
#include "AztecOO.h"
#include "AztecOO_Version.h"
#endif

namespace Reo {

using namespace DGM;

// constructor
iEuler::iEuler( DGM::ArgList &args, const DGM::Comm::Ptr comm_ ) :
  Domain(args, comm_), P(comm_), Pr(comm_) {

  Ordinal p, q;
  p = params["p"];                     // polynomial order
  if ( !(q=params["q"]) ) q = p + 2;   // number of quadrature points
  nsd = params["nsd"];                 // number of space dimensions

  params["tecplot"] = 1;               // Generate tecplot files
  params["auxtec"] = 0;                // Compute derivative quantities
  params["plot3d"]  = 0;               // Generate plot3d files
  params["plot3d_x"] = 1;              // plot3d grid file
  params["plot3d_q"] = 1;              // plot3d mesh file

  // read arguments (overrides defaults and input file)
  parse_args( args );

  setup_BCdb();                        // setup BC database

  vector<string> field_names;          // Field names
  field_names.push_back("u");

  // build a Field of Elements and Sides
  if (params["imesh"]) {
    Mesh mesh(params);
    U.push_back( new Field(p, q, mesh, root, field_names[0],
                           Field::FULL, comm ) );
    partition = U[0]->partition;
  } else if (params["bmesh"]) {
    U.push_back( new Field(p, q, root, field_names[0], partition, 1,
                           Reo::NumEqntype, p2i(IEULER), comm ) );
  } else {
    U.push_back( new Field(p, q, root, field_names[0], partition, comm ) );
  }

  // set some additional domain parameters
  ne = U[0]->ne;
  nsd = U[0]->nsd();

#ifdef REO_USE_GETSIDEMAPS
  setup_side_maps();
#endif

  if (nsd == 1) {
    Nfields = 1;
  } else if (nsd == 2) {
    Nfields = 2;
    field_names.push_back("v");
  } else if (nsd == 3) {
    Nfields = 3;
    field_names.push_back("v");
    field_names.push_back("w");
  } else {
    comm->cerr() << "Illegal value for nsd = " << nsd << " in Euler::Euler"
                 << endl;
    comm->exit(DGM::FAILURE);
  }

  // build the rest of the vector field
  for (vField::size_type i=1; i<Nfields; i++)
    U.push_back( new Field( U[0], root, field_names[i] ) );

  // make auxiliary Fields using copy constructor
  for (vField::size_type i=0; i<Nfields; i++) {
    Ut.push_back( new Field( U[i], root, field_names[i] ) );
  }

  // setup the pressure field and residual
  field_names.clear();
  field_names.push_back("P");
  P.push_back( new Field( U[0], root, field_names[0] ) );
  field_names[0] = "R";
  Pr.push_back( new Field( P[0], root, field_names[0] ) );

  // allocate workspace
  wk1.resize(5*max(Lmax(),Qmax()));
  wk2.resize(5*max(Lmax(),Qmax()));

  // make sure that storage is initialized
  zero_all_fields();

  // make analysis object
  response = Response::factory(U, this);

  setup_Sourcedb();        // setup Source term database

  set_TimeInt();
}

// Parse parameters from the argument list
void iEuler::parse_args( DGM::ArgList &args ) {
  string name, value;
  list< DGM::ArgList::iterator > li;
  for ( DGM::ArgList::iterator a = args.begin(); a != args.end(); a++ ) {
    if ( (*a)[0] == '-' ) {
      name = *a;
      if (name == "-nox") {
        li.push_back(a);
        params["plot3d_x"] = 0;
      } else if (name == "-noq") {
        li.push_back(a);
        params["plot3d_q"] = 0;
      } else if (name == "-aux") {
        li.push_back(a);
        params["auxtec"] = 1;
      } else if (name == "-help") {
        params["showUsage"] = 1;
        showUsage();
      }
    }
  }
  // remove tagged arguments
  for ( list< DGM::ArgList::iterator >::iterator a=li.begin();
        a!=li.end(); a++) args.erase(*a);
}

void iEuler::showUsage() {
  comm->cout()
    << "iEuler Class Options \n"
    << "----------------------------------------------------------------\n"
    << "-nox     " << '\t' << "No grid file                             \n"
    << "-noq     " << '\t' << "No solution file                         \n"
    << "-aux     " << '\t' << "Auxiliary Tecplot file                   \n"
    << "----------------------------------------------------------------\n";
}

void iEuler::set_material() { }

void iEuler::time_derivative( vField &Us, vField &Uf ) {
  pressure_projection( Us, Uf, P, Pr );
  Uf.zero();
#ifndef REO_IEULER_CONVECTION_OFF
  convection( Us, Uf );
#endif
  add_source( Us, Uf);
  project( Uf );
}

// WARNING: Does not work in parallel, should gather to master...
int iEuler::plot(const string &rst) {
  string fname, name(rst), caption;
  char buf[80];
  read( rst, U );
  pressure_projection( U, Ut, P, Pr );  // make sure div-free
  size_t loc = name.find(".rst");
  if ( loc != string::npos )
    name.erase(loc);
  sprintf(buf,"%s.dat",name.c_str()); fname = buf;
  sprintf(buf,"State variables at t =%11.4e, step = %lld",t,(long long)step);
  caption = buf;
  if (params["tecplot"] )
    if (comm->Master()) U.tecplot(fname,caption);
  if (params["plot3d"]) {
    if (params["plot3d_x"]) {
      sprintf(buf,"%s.xyz",name.c_str()); fname = buf;
      if (comm->Master()) U.plot3d_x(fname);
    }
    if (params["plot3d_q"]) {
      sprintf(buf,"%s.q",name.c_str()); fname = buf;
      if (comm->Master()) U.plot3d_q(fname);
    }
  }
  if (params["auxtec"]) {
    compute_vorticity();  // puts vorticity in Ut
    sprintf(buf,"%s.aux.dat",name.c_str()); fname = buf;
    sprintf(buf,"Auxiliary variables at t =%11.4e, step = %lld",t,
            (long long)step);
    caption = buf;
    if (comm->Master()) Ut.tecplot(fname,caption);
  }
  return 0;
}

// This is rather expensive and many of these steps are already done
// in the convection phase.
Scalar iEuler::set_time_step(vField &U) {
  //  cout << "iEuler::set_time_step()" << endl;
  Scalar cfl = 0;
  return cfl;
}

// set the initial condition
void iEuler::set_ic(vField &F, string ext) {
  t = 0.0; step = 0;
  string fname = root+ext;
  ifstream in(fname.c_str());
  if (!in) {
    comm->cerr() << "Could not open initial condition " << fname << endl;
    comm->exit(DGM::FAILURE);
  }
  string buffer, code;
  getline(in,buffer);
  if (!(in>>code)) error("Cannot read IC code");
  getline(in,buffer);
  //  cout << "IC code = " << code << endl;
  if (lowerCase(code) == "given") {
    F.fill(in);
  } else if (lowerCase(code) == "restart") {
    string rstfile;
    if (!(in>>rstfile)) {
      comm->cerr() << "Cannot read restart file name from " << fname << endl;
      comm->exit(DGM::FAILURE);
    }
    read(rstfile, F);
    //comm->cout() << "Restarting from: " << rstfile << endl;
  } else if (lowerCase(code) == "vortex") {  // superimpose Oseen vortex
    int nVorts;
    Scalar x0, y0, radius, amp;
    in>>nVorts;
    for (int nv=0; nv<nVorts; nv++) {
      in>>x0>>y0>>radius>>amp;
      OseenVortex vortex(x0,y0,radius,amp);
      for (LocalSize e=0; e<ne; e++) {
        for (LocalSize q=0; q<F[0]->el[e]->qtot; q++) {
          F[0]->el[e]->u[q] += vortex.u( (*F[0]->el[e]->C)[q] );
          F[1]->el[e]->u[q] += vortex.v( (*F[1]->el[e]->C)[q] );
        }
      }
    }
  } else {
    comm->error("iEuler::set_ic()  Unsupported IC type");
  }
#ifdef DGM_NO_PROJECT_IC
  comm->cout() << "WARNING:  No projection of Initial condition" << endl;
  for (LocalSize i=0; i<F.size(); i++)
    for (LocalSize e=0; e<ne; e++)
      F[i]->el[e]->state = Element::Physical;
#else
  project( F );
#endif
  cout << "Pressure projection of the initial condition" << endl;
  pressure_projection( U, Ut, P, Pr );
}

void iEuler::convection( vField &Us, vField &Uf ) {
  //cout << "iEuler::convection(...)" << endl;
  Element *U[2], *F[2];
  dVector u, v, uu, uv, vv, d;

  Us.fill_sides();
#ifdef USE_EULER_BC
  // The purpose of this compiler define is to override the default behavior
  // where the Euler BC's are enforced during the convection phase and the NS
  // BCs are used in the diffusion term.  This is useful when performing
  // optimization, although I still do not understand why this is
  // necessary. [SSC]
  iEuler::enforce_bc(Us);
#else
  enforce_bc(Us);
#endif
  Us.share_sides();
  convective_flux( Us, Uf );

  for (LocalSize e=0; e<Us[0]->ne; e++) {

    // local version of the state
    U[0] = Us[0]->el[e];
    U[1] = Us[1]->el[e];

    // local version of the flux
    F[0] = Uf[0]->el[e];
    F[1] = Uf[1]->el[e];

    const Ordinal qtot = Us[0]->el[e]->qtot;

    u.alias(U[0]->u);
    v.alias(U[1]->u);

    uu.alias(wk1,0,qtot);
    uv.alias(wk1,qtot,qtot);
    vv.alias(wk1,2*qtot,qtot);
    d.alias (wk1,3*qtot,qtot);

    dvmul( u, u, uu );
    dvmul( u, v, uv );
    dvmul( v, v, vv );

    // Uf[0]->el[e]->u = (d/dx)(u*u) + (d/dy)(v*u)
    U[0]->gradient(uu, F[0]->u, 'x');
    U[0]->gradient(uv, d, 'y');
    dvadd(d, F[0]->u);

    // Uf[1]->el[e]->u = (d/dx)(u*v) + (d/dy)(v*v)
    U[1]->gradient(uv, F[1]->u, 'x');
    U[1]->gradient(vv, d, 'y');
    dvadd(d, F[1]->u);

    // add the surface contribution
    for (vField::size_type i=0; i<Nfields; i++)
      U[i]->lift( F[i], F[i]->u );
  }
}

void iEuler::convective_flux(vField &Us, vField &Uf) {
  flux_type flux =  LaxFriedrichs; // StegerWarming; // vanLeer; // Roe;
  dVector sl(Nfields), sr(Nfields), f(Nfields);
  Scalar lmax, ml, nl, mr, nr;
  vector<Side *> Ssl(Nfields), Ssr(Nfields);
  vector<Side *> Sfl(Nfields), Sfr(Nfields);
  dVector fpl(Nfields), fmr(Nfields);
#ifdef REO_USE_GETSIDEMAPS
  iVector mapl, mapr;
#endif

  for (LocalSize e=0; e<Us[0]->ne; e++) {                   // element loop
    Element* U = Us[0]->el[e];
    for (LocalSize i=0; i<Us[0]->el[e]->nSides(); i++) {    // loop over sides
      if (Us[0]->el[e]->side[i]->master()) {                // master side
        const Ordinal qtot = Us[0]->el[e]->side[i]->qtot(); // side quad pts
        for (vField::size_type ni=0; ni<Nfields; ni++) {
          Ssl[ni] = Us[ni]->el[e]->side[i];             // left state side
          Ssr[ni] = Us[ni]->el[e]->side[i]->link;       // right state side
          Sfl[ni] = Uf[ni]->el[e]->side[i];             // left flux side
          Sfr[ni] = Uf[ni]->el[e]->side[i]->link;       // right flux side
        }
#ifdef REO_USE_GETSIDEMAPS
        get_side_maps(Ssl[0],Ssr[0],mapl,mapr);
#endif

        for (Ordinal q=0; q<qtot; q++) {          // loop over side quad-pts

#ifdef REO_USE_GETSIDEMAPS
          const Ordinal ql = mapl[q];
          const Ordinal qr = mapr[q];
#else
          const Ordinal ql = U->sideMap(Ssl[0], q);
          const Ordinal qr = U->sideMap(Ssr[0], q);
#endif

          const Scalar nx = Us[0]->el[e]->side[i]->nx(ql);
          const Scalar ny = Us[0]->el[e]->side[i]->ny(ql);

          // compute normal flux from interior (left)

          // interior state
          sl[0] = Ssl[0]->u[ql];
          sl[1] = Ssl[1]->u[ql];

          // normal interior flux
          ml = sl[0]*nx + sl[1]*ny;
          nl = sl[1]*nx - sl[0]*ny;

          // put the local flux on the state sides
          Ssl[0]->u[ql] = (ml*ml)*nx - (nl*ml)*ny;
          Ssl[1]->u[ql] = (ml*ml)*ny + (nl*ml)*nx;

          // compute normal flux from exterior (right)

          // adjacent state
          sr[0] = Ssr[0]->u[qr];
          sr[1] = Ssr[1]->u[qr];

          // normal adjacent state (note that local normal is used!)
          mr = sr[0]*nx + sr[1]*ny;
          nr = sr[1]*nx - sr[0]*ny;

          // put the adjacent flux on the state sides
          Ssr[0]->u[qr] = (mr*mr)*nx - (nr*mr)*ny;
          Ssr[1]->u[qr] = (mr*mr)*ny + (nr*mr)*nx;

          switch (flux) {
          case LaxFriedrichs:
            // left flux
            fpl[0] = (ml*ml)*nx - (nl*ml)*ny;
            fpl[1] = (ml*ml)*ny + (nl*ml)*nx;

            // right flux
            fmr[0] = (mr*mr)*nx - (nr*mr)*ny;
            fmr[1] = (mr*mr)*ny + (nr*mr)*nx;

            lmax = max(ml,mr);

            // Lax-Friedrichs flux
            f[0] = pt5 * ( fpl[0] + fmr[0] + lmax * ( sl[0] - sr[0] ) );
            f[1] = pt5 * ( fpl[1] + fmr[1] + lmax * ( sl[1] - sr[1] ) );
            break;
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

//===========================================================================
//                        BC database management
//===========================================================================

// Load up the available BC types
void iEuler::setup_BCdb( ) {
  //  cout << "iEuler::setup_BCdb()" << endl;

  // set default BC types
  dVector ub(2);
  ub[0] = 1.0;
  ub[1] = 0.0;
  BC_db["S"].reset( new StateBC("S", ub) );
  BC_db["W"].reset( new WallBC("W") );

  // read new BC types from file
  string fname = root+".bct";
  ifstream in(fname.c_str());
  if (in) iEuler::read_BCdb( in );   // database of active BC types
}


void iEuler::read_BCdb( ifstream &in ) {
  // cout << "iEuler::read_BCdb( ifstream &in )" << endl;
  string tag;
  BC *pbc;
  while ( (pbc = iEuler::make_BC(in,tag)) ) {
    if ( BC_db.find(tag) != BC_db.end() )
      comm->cerr() << "WARNING in iEuler::read_BCdb() Overriding BC type \""
                   << tag << "\"." << endl;
    BC_db[tag].reset( pbc );
  }
}

// Note that caution is required here as the iEuler module searches for
// substrings within the BC tag.  This makes it possible that many
// iNS BCs map onto a single iEuler BC, but care is required to make
// the substring search order correct and unique. [ssc]
BC* iEuler::make_BC( ifstream &in, string &tag ) {
  // cout << "iEuler::make_BC(ifstream &in, string &tag)" << endl;
  string code;
  if (!(in >> code)) return NULL;
  code = lowerCase(code);
  if (code == "state") {
    if (!(in >> tag)) error("iEuler::make_BC: Cannot read State tag",1);
    return new StateBC(tag,in,4);
  } else if ( code.find("wall") != code.npos ) {
    if (!(in >>tag)) error("iEuler::make_BC:  Cannot read Wall tag",1);
    return new WallBC(tag,in);
  } else {
    if(comm->Master())
      comm->cerr()<<"WARNING iEuler::make_BC() Illegal BC type: "+code<<endl;
  }
  return NULL;
}


// here you use the State vField for the construction of the SourceControl
// scratch vField, is it important to use the local projection. [gqchen]

/// Construct source terms
Source::Ptr iEuler::make_Source( ifstream &in, string &tag ) {
  string code;
  Source::Ptr p;
  // cout << "iEuler::make_Source" << endl;
  if (!(in >> code)) return p;
  while (code[0]=='#') {  // eat comment lines
    string buffer;
    getline(in,buffer);
    if (!(in >> code)) return p;
  }
  if (lowerCase(code) == "constant") {
    if (!(in >> tag)) error("iEuler::Cannot read ConstSource tag",1);;
    p.reset( new ConstSource(tag,in,1) );
  } else {
    error("iEuler::make_Source() Illegal Source type",1);
  }
  return p;
}

// Add source terms
void iEuler::add_source(const vField &Us, vField &Ur) {
  // cout << "iEuler::add_source(vField &)" << endl;
  for (Source::db_citr i=Source_db.begin(); i!= Source_db.end(); ++i)
    // cout << "Adding source: " << i->first << endl;
    i->second->apply( t, Us, Ur);
}

// if defined then perform a projection to compute diffusive flux
#define REO_IEULER_GRADIENT_PROJECT

// Compute a jump savy gradient
void iEuler::gradient( Element *S, Element *F, dVector &u,
                       dVector &ux, dVector &uy ) {
  dVector uxh(ux,S->nModes());
  dVector uyh(uy,S->nModes());
  S->gradient( u, ux, uy );
  S->lift( F, ux, 'x' );
#ifdef REO_IEULER_GRADIENT_PROJECT
  S->project(ux);
#endif
  S->lift( F, uy, 'y' );
#ifdef REO_IEULER_GRADIENT_PROJECT
  S->project(uy);
#endif
}

/// If defined than the side jumps are used in computing vorticity
#define REO_IEULER_JUMP

void iEuler::compute_vorticity() {
  Element *S[2], *F[2];
  dVector u, v, p, e, wk;
  dVector r, ru, rv, E;

#ifdef REO_IEULER_JUMP
  U.fill_sides();
  U.share_sides();
  enforce_bc( U );
  average_flux( U, Ut, '+' );
#endif

  for (LocalSize i=0; i<U[0]->ne; i++) {
    // local version of the state
    S[0] = U[0]->el[i];
    S[1] = U[1]->el[i];

    // local version of the state
    F[0] = Ut[0]->el[i];
    F[1] = Ut[1]->el[i];

    const Ordinal qtot = S[0]->qtot;

    u.alias(S[0]->u);
    v.alias(S[1]->u);

#ifdef REO_IEULER_JUMP
    dVector ux(qtot);
    dVector uy(qtot);
    dVector vx(qtot);
    dVector vy(qtot);

    gradient( S[0], F[0], u, ux, uy );
    gradient( S[1], F[1], v, vx, vy );

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
    dVector ux(qtot);
    F[0]->gradient(u, ux, 'x');
    F[1]->gradient(v, F[1]->u, 'y');
    dvadd(ux,F[1]->u);
#endif
  }
}

// Need to fix boundary conditions
void iEuler::divergence( vField &Us, vField &Uf, vField &Ur, int output ) {
  comm->cout() << "iEuler::divergence" << endl;

#ifdef REO_IEULER_MODAL_LAPLACE
  Ur[0]->unpack();
  Ur.backward_transform();
#endif

  assert( Us.size() == 2 );
  assert( Uf.size() == 2 );
  assert( Ur.size() == 1 );
  dVector ux, uy, vx, vy;
  Us.fill_sides();
  Us.share_sides();
  enforce_bc(Us);
  if (stab!=0) {
    // penalty_flux( Us, Us, Uf, stab*Us.get_max_sigma(), '+' );
    average_flux( Us, Uf, '+' );
  } else
    average_flux( Us, Uf, '+' );
  Element *S[2], *F[2];
  for (LocalSize e=0; e<Us[0]->ne; ++e) {
    S[0] = Us[0]->el[e];
    S[1] = Us[1]->el[e];

    F[0] = Uf[0]->el[e];
    F[1] = Uf[1]->el[e];

    const Ordinal qtot = S[0]->qtot;

    ux.alias(wk1,     0,qtot);
    uy.alias(wk1,  qtot,qtot);
    vx.alias(wk1,2*qtot,qtot);
    vy.alias(wk1,3*qtot,qtot);

    gradient( S[0], F[0], S[0]->u, ux, uy );
    gradient( S[1], F[1], S[1]->u, vx, vy );

    dvadd(ux, vy, Ur[0]->el[e]->u); // divergence
  }
  Ur.norm();

  if (output)
    Ur.tecplot("divergence.dat","divergence");

#ifdef REO_IEULER_MODAL_LAPLACE
  Ur.forward_transform();
  Ur[0]->pack();
#endif
}

// Need to fix boundary conditions
void iEuler::local_divergence( vField &Us, vField &Uf, vField &Ur,
                               int output ) {
  comm->cout() << "iEuler::local_divergence" << endl;

#ifdef REO_IEULER_MODAL_LAPLACE
  Ur[0]->unpack();
  Ur.backward_transform();
#endif

  assert( Us.size() == 2 );
  assert( Uf.size() == 2 );
  assert( Ur.size() == 1 );
  dVector ux, uy, vx, vy;
  Element *S[2]; //, *F[2];
  for (LocalSize e=0; e<Us[0]->ne; ++e) {
    S[0] = Us[0]->el[e];
    S[1] = Us[1]->el[e];

    //F[0] = Uf[0]->el[e];
    //F[1] = Uf[1]->el[e];

    const Ordinal qtot = S[0]->qtot;

    ux.alias(wk1,     0,qtot);
    vy.alias(wk1,1*qtot,qtot);

    S[0]->gradient( S[0]->u, ux, 'x' );
    S[1]->gradient( S[1]->u, vy, 'y' );

    dvadd( ux, vy, Ur[0]->el[e]->u );
  }
  Ur.norm();

  if (output)
    Ur.tecplot("divergence.dat","divergence");

#ifdef REO_IEULER_MODAL_LAPLACE
  Ur.forward_transform();
  Ur[0]->pack();
#endif
}

// Need to fix boundary conditions
void iEuler::weak_divergence( vField &Us, vField &Up, vField &Ur, int output ){
  comm->cout() << "iEuler::weak_divergence(...)" << endl;

#ifdef REO_IEULER_MODAL_LAPLACE
  Ur[0]->unpack();
  Ur.backward_transform();
  Up[0]->unpack();
  Up.backward_transform();
#endif

  assert( Us.size() == 2 );
  assert( Up.size() == 1 );
  assert( Ur.size() == 1 );
  dVector ux, vy;
  Us.fill_sides();
  Us.share_sides();
  enforce_bc(Us);
  Element *S[2], *P, *R;
  for (LocalSize e=0; e<Us[0]->ne; ++e) {
    S[0] = Us[0]->el[e];
    S[1] = Us[1]->el[e];

    P    = Up[0]->el[e];
    R    = Ur[0]->el[e];

    const Ordinal qtot = S[0]->qtot;
    ux.alias(wk1,   0,qtot);
    vy.alias(wk1,qtot,qtot);

    P->fill_sides( S[0]->u, S[1]->u );  // normal velocity on sides

    S[0]->gradient( S[0]->u, ux, 'x' );
    S[1]->gradient( S[1]->u, vy, 'y' );

    dvadd( ux, vy, R->u );
  }
  Up.share_sides();
  // enforce_flux_bc(Up);
  average_flux( Up, Ur, '-' );
  for (LocalSize e=0; e<Ur[0]->ne; e++) {
    Element *U = Up[0]->el[e];
    Element *F = Ur[0]->el[e];
    U->lift( F, F->u ); // add side fluxes to interior
  }
  project(Ur);
  Ur.norm();
  if (output)
    Ur.tecplot("divergence.dat","divergence");

#ifdef REO_IEULER_MODAL_LAPLACE
  Ur.forward_transform();
  Ur[0]->pack();
  Up.forward_transform();
  Up[0]->pack();
#endif
}

// Need to account for boundary conditions
void iEuler::Laplace( vField &Up, vField &Uf, vField &Ur ) {
  // comm->cout() << "iEuler::Laplace" << endl;
  Up.fill_sides();                   // put solution on the sidess
  Up.share_sides();
  // enforce_bc(Up);                 // update bc side values
  average_flux( Up, Uf, '+' );       // F's sides are average of the pressure
  if (stab!=0) {
    copy_sides(Up,Ur);               // Put the Uf sides on Rf
    Ur.share_sides();
    // enforce_bc(Ur);
  }
  for (LocalSize e=0; e<Up[0]->ne; ++e) {
    Element *U = Up[0]->el[e];
    Element *F = Uf[0]->el[e];
    const Ordinal qtot = U->qtot;
    const Ordinal nModes = U->nModes();
    dVector ux(wk1,qtot);
    dVector uxh(ux,nModes);
    dVector uy(wk2,qtot);
    dVector uyh(uy,nModes);
    U->gradient(U->u, ux, uy);
    U->lift( F, ux, 'x' );
    U->project(ux);
    U->lift( F, uy, 'y' );
    U->project(uy);
    U->fill_sides( ux, uy );                // normal flux on sides
    U->gradient(ux, ux, 'x');               // ux = u_{,xx}
    U->gradient(uy, uy, 'y');               // uy = u_{,yy}
    dvadd( ux, uy, F->u );                  // F->u = u_{,xx} + u_{,yy}
  }
  Up.share_sides();
  // enforce_flux_bc(Up);                   // put flux BC's on bc sides
  if (stab!=0.0) {
    penalty_flux( Ur, Up, Uf, stab*Up.get_max_sigma() );
  } else
    average_flux( Up, Uf, '-' );
  for (LocalSize e=0; e<Up[0]->ne; ++e) {
    Element *U = Up[0]->el[e];
    Element *F = Uf[0]->el[e];
    U->lift( F, F->u );    // add side fluxes to interior
  }
}

#ifdef DGM_USE_EPETRA

/// try out an Epetra_Operator for Matrix Free computation
class Laplace_Operator : public virtual Epetra_Operator {
  iEuler *flow;
  string label;
  const Epetra_Comm *comm;
  const Epetra_Map *domain_map, *range_map;
  vField x, y, z;
public:
  Laplace_Operator( iEuler *flow_, Epetra_Comm &comm_,
                    Epetra_Map &domain_map_ ) :
    flow(flow_),
    label("Laplace_Operator"),
    comm(&comm_),
    domain_map(&domain_map_),
    range_map(&domain_map_), x(DGM::Comm::World), y(DGM::Comm::World), 
    z(DGM::Comm::World)
  {
    x.push_back( new Field( flow->P[0], flow->root, flow->P[0]->name ) );
    y.push_back( new Field( flow->P[0], flow->root, flow->P[0]->name ) );
    z.push_back( new Field( flow->P[0], flow->root, flow->P[0]->name ) );
    cout << "Constructed " << label << endl;
  }
  ~Laplace_Operator() {
    cout << "Destructed " << label << endl;
  }
  int SetUseTranspose(bool UseTranspose) { return -1; }
  int Apply(const Epetra_MultiVector &X, Epetra_MultiVector &Y) const {
    // cout << "Apply " << label << endl;

    // WARNING:  size() should likely be ndof()
    X.ExtractCopy( x[0]->elmt_data.data(), x[0]->elmt_data.size() );

#ifdef REO_IEULER_MODAL_LAPLACE
//     cout << "X.GlobalLength() = " << X.GlobalLength() << endl;
//     cout << "x[0]->elmt_data.size() = " << x[0]->elmt_data.size() << endl;
//     cout << "x[0]->qtot() = " << x[0]->qtot << endl;
//     cout << "x[0]->ndof() = " << x[0]->ndof << endl;
//     cout << "Unpacking the data" << endl;
    x[0]->unpack();
    for (LocalSize e=0; e<x[0]->ne; ++e) x[0]->el[e]->state=Element::Transform;
    x[0]->backward_transform();
#endif

    // Note that z is just temporary side storage
    flow->Laplace( *(const_cast<vField *>(&x)), *(const_cast<vField *>(&y)),
                   *(const_cast<vField *>(&z)) );

    // try holding one mode at zero (didn't work)
    //y[0]->elmt_data[0] = 0.0;

#ifdef REO_IEULER_MODAL_LAPLACE
    y[0]->forward_transform();

    // try holding one point at zero (didn't work)
    //y[0]->elmt_data[0] = 0.0;

    //    cout << "Packing the data" << endl;
    y[0]->pack();
    std::copy( y[0]->elmt_data.data(),
               y[0]->elmt_data.data() + y[0]->ndof, Y.Values() );
    y[0]->zero();
    for (LocalSize e=0; e<x[0]->ne; ++e) x[0]->el[e]->state=Element::Undefined;
#else
    std::copy( y[0]->elmt_data.data(),
               y[0]->elmt_data.data() + y[0]->elmt_data.size(), Y.Values() );
#endif

    return 0;
  }
  int ApplyInverse(const Epetra_MultiVector &X, Epetra_MultiVector &Y) const {
    cout << "ApplyInverse " << label << endl;
    return -1;
  }
  Scalar NormInf() const { return 0.0; }
  const char *Label() const { return label.c_str(); }
  bool UseTranspose() const { return false; }
  bool HasNormInf() const { return false; }
  const Epetra_Comm &Comm() const { return *comm; }
  const Epetra_Map &OperatorDomainMap() const {
    // cout << "Laplace_Operator::OperatorDomainMap()"<<endl<<flush;
    return *domain_map;
  }
  const Epetra_Map &OperatorRangeMap() const {
    // cout << "Laplace_Operator::OperatorRangeMap()"<<endl<<flush;
    return *range_map;
  }
};

#endif // DGM_USE_EPETRA

//======================================================================
//               P r e s s u r e    P r o j e c t i o n
//======================================================================

void iEuler::pressure_projection( vField &Us, vField &Uf,
                                  vField &Up, vField &Ur ) {
#ifdef DGM_USE_EPETRA

#ifdef DGM_PARALLEL
  Epetra_MpiComm Comm(dynamic_cast<const DGM::MpiComm*>
                      (comm.get())->mpicomm());
#else
  Epetra_SerialComm Comm;
#endif
  //=========================================================================
  // This section of code deals with building the full Laplace matrix
  //=========================================================================
#ifdef REO_IEULER_LAPLACE_MATRIX
  cout << "nodal_glen = " << Up[0]->partition->nodal_glen << endl;
  cout << "Up.partition->nodal_disp.size() = "
       << Up[0]->partition->nodal_disp.size() << endl;
  cout << "Up.partition->nodal_len.size() = "
       << Up[0]->partition->nodal_len.size() << endl;
  cout << "Up.size() = " << Up.size() << endl;
  cout << "Up.qtot() = " << Up.qtot() << endl;
  cout << "Up.ndof() = " << Up.ndof() << endl;

  // Serial version
  cout << "epetra_blockmap is only valid in SERIAL" << endl;
  iVector MyGlobalElements(Up[0]->ne);
  iVector ElementSizeList(Up[0]->ne);
  for (LocalSize e=0; e<Up[0]->ne; ++e) {
    MyGlobalElements[e] = Up[0]->el[e]->id;
    ElementSizeList[e] = Up[0]->el[e]->qtot;
    //cout << "e = " << e << " " << Up[0]->el[e]->qtot << endl;
  }
  Epetra_BlockMap epetra_map(-1, Up[0]->ne, MyGlobalElements.data(),
                             ElementSizeList.data(), 0, Comm );
  //epetra_map.Print(cout);

  Epetra_Vector pressure( View, epetra_map, Up[0]->elmt_data.data() );

  Up[0]->el[0]->u = 2.0;      // set pressure on element 0 to 2.0

  pressure.PutScalar( 1.0 );  // set all pressures to 1.0
  pressure.Random();          // put random numbers in pressure
  pressure.Scale(10.0);       // scale by 10

  //pressure.Print(cout);

  cout << "Pressure GlobalLength = " << pressure.GlobalLength() << endl;
  cout << "Pressure MyLength = " << pressure.MyLength() << endl;
  cout << "Pressure NumVectors = " << pressure.NumVectors() << endl;

  Scalar minp; pressure.MinValue( &minp );
  Scalar maxp; pressure.MaxValue( &maxp );
  cout << "Min pressure = " << minp << endl;
  cout << "Max pressure = " << maxp << endl;

  // Now make a Graph
  // The NumIndicesPerRow are the number of adjacent elements to this element
  // which for a periodic quad mesh is always 5
  cout << "construct a CrsGraph" << endl;
  Epetra_CrsGraph epetra_graph( Copy, epetra_map, 5 );

  for (LocalSize e=0; e<Up[0]->ne; ++e) {
    iVector indices(Up[0]->el[e]->nSides()+1); indices=0;
    for (int n=0; n<Up[0]->el[e]->nSides(); ++n) {
      if (Up[0]->el[e]->side[n]->link) {
        //cout << e << " " << Up[0]->el[e]->side[n]->link << " "
        //     << Up[0]->el[e]->side[n]->link->eid << endl;
        indices[n] = Up[0]->el[e]->side[n]->link->eid;
      } else {
        //cout << e << " " << Up[0]->el[e]->side[n]->base << " "
        //     << Up[0]->el[e]->side[n]->base->eid << endl;
        indices[n] = Up[0]->el[e]->side[n]->base->eid;
      }
      indices[Up[0]->el[e]->nSides()] = e;
    }
    epetra_graph.InsertGlobalIndices( e, indices.size(), indices.data() );
  }
  epetra_graph.FillComplete();  // converts to local indices
  //epetra_graph.Print(cout);

  cout << "Construct a Variable Block-Row Matrix" << endl;
  Epetra_VbrMatrix epetra_matrix( Copy, epetra_graph );

  // Now fill the matrix with data.  Note that every single block in the graph
  // must be submitted or there will be a segmentation fault in Print()
  for (LocalSize e=0; e<Up[0]->ne; ++e) {
    int NumIndices;
    NumIndices = epetra_graph.NumGlobalIndices(e);
    iVector Indices(NumIndices);
    // this doesn't work if indices are local!
    // int *Indices;
    // epetra_graph.ExtractGlobalRowView( e, NumIndices, Indices );
    epetra_graph.ExtractGlobalRowCopy( e, NumIndices, NumIndices,
                                       Indices.data() );
#ifdef REO_IEULER_DEBUG
    cout << "e = " << e << " " << NumIndices << " ";
    for (int i=0; i<NumIndices; ++i) cout << Indices[i] << " ";
    cout << endl;
#endif
    epetra_matrix.BeginReplaceGlobalValues( e, NumIndices, Indices );
    const int lqtot(Up[0]->el[e]->qtot);
    for (int i=0; i<NumIndices; ++i) {
      const int aqtot(Up[0]->el[Indices[i]]->qtot);
      dVector block( lqtot*aqtot );
      dMatrix Block( block, lqtot, aqtot );
      block = 0.0;
      if (e==Indices[i])// diagonal block
        for (int j=0; j<lqtot; ++j) Block[j][j] = 1.0;
      epetra_matrix.SubmitBlockEntry( block.data(), lqtot, lqtot, aqtot );
    }
    epetra_matrix.EndSubmitEntries();
  }
  epetra_matrix.FillComplete(); // is this needed here?
  //epetra_matrix.Print(cout);

  // setup Linear Problem
  Epetra_Vector x( View, pressure, 0 ); // this is silly
  Epetra_Vector b( View, epetra_map, Ur[0]->elmt_data.data() );
  b.PutScalar(1.0);
  Epetra_LinearProblem problem( &epetra_matrix, &x, &b );

  // setup Aztec solver
  AztecOO solver(problem);

  // set the solver type, AZ_gmres is the default
  solver.SetAztecOption(AZ_solver, AZ_cg);
  //solver.SetAztecOption(AZ_solver, AZ_gmres);
  //solver.SetAztecOption(AZ_solver, AZ_cgs);
  //solver.SetAztecOption(AZ_solver, AZ_tfqmr);
  //solver.SetAztecOption(AZ_solver, AZ_bicgstab);

  // set the preconditioner, AZ_none is the default
  solver.SetAztecOption(AZ_precond, AZ_none);
  //solver.SetAztecOption(AZ_precond, AZ_Jacobi);

  solver.Iterate(100, 1.0e-3);
  cout << "Solver performed " << solver.NumIters() << " iterations." << endl
       << "Norm of true residual = " << solver.TrueResidual() << endl;

#endif  // REO_IEULER_LAPLACE_MATRIX

  //=========================================================================

  // point map (only valid in Serial mode)
  cout << "domain_map is only valid in SERIAL" << endl;
#ifdef REO_IEULER_MODAL_LAPLACE
  Epetra_Map domain_map(-1, Up.ndof(), 0, Comm);
#else
  Epetra_Map domain_map(-1, Up.qtot(), 0, Comm);
#endif
  // cout << domain_map;

  // Now try to use the Laplace_Operator
  Laplace_Operator laplace( this, Comm, domain_map );

  // make Epetra_Vector views
  Epetra_Vector p( View, domain_map, Up[0]->elmt_data.data() );

  // set initial guess
  p.PutScalar(0.0);
  Epetra_Vector r( View, domain_map, Ur[0]->elmt_data.data() );

  // evaluate RHS
#ifdef REO_STRONG_DIVERGENCE
  divergence( Us, Uf, Ur, 1 );
#else
#ifdef REO_LOCAL_DIVERGENCE
  local_divergence( Us, Uf, Ur, 1 );
#else
  weak_divergence( Us, Up, Ur, 1 );
#endif
#endif

  Epetra_LinearProblem poisson( &laplace, &p, &r );

  AztecOO poisson_solver(poisson);
  poisson_solver.SetAztecOption(AZ_solver, AZ_gmres);
  poisson_solver.SetAztecOption(AZ_precond, AZ_none);
  poisson_solver.SetAztecOption(AZ_conv, AZ_noscaled);
  //poisson_solver.SetAztecOption(AZ_output, AZ_last);

  poisson_solver.Iterate(200, 1.0e-12);
#if 0
  cout << "Solver performed "
       << poisson_solver.NumIters() << " iterations." << endl
       << "Norm of true residual = " << poisson_solver.TrueResidual() << endl;
#endif

#ifdef REO_IEULER_MODAL_LAPLACE
  Ur[0]->unpack();
  Ur.backward_transform();
  Up[0]->unpack();

  // try this out
  //Up.make_constant();

  Up.backward_transform();
#endif

  Up.tecplot("pressure.dat","pressure");

  //===========================================================================

  // now project out the divergence using the gradient of pressure

  Up.fill_sides();                   // put solution on the sidess
  Up.share_sides();
  // enforce_bc(Up);                 // update bc side values
  average_flux( Up, Ur, '+' );       // F's sides are average of the pressure
  for (LocalSize e=0; e<Up[0]->ne; ++e) {
    Element *U = Up[0]->el[e];
    Element *F = Ur[0]->el[e];
    const int qtot = U->qtot;
    const int nModes = U->nModes();
    dVector px(wk1,qtot);
    dVector pxh(px,nModes);
    dVector py(wk2,qtot);
    dVector pyh(py,nModes);
    U->gradient(U->u, px, py);
    U->lift( F, px, 'x' );
    U->project(px);
    U->lift( F, py, 'y' );
    U->project(py);
    dvsub( Us[0]->el[e]->u, px, Us[0]->el[e]->u ); // Us[0]->el[e]->u.Sub(px);
    dvsub( Us[1]->el[e]->u, py, Us[1]->el[e]->u ); // Us[1]->el[e]->u.Sub(py);
  }

#ifdef REO_IEULER_MODAL_LAPLACE
  Ur.forward_transform();
  Ur[0]->pack();
  Up.forward_transform();
  Up[0]->pack();
#endif

  // verify that the divergence is zero
#ifdef REO_STRONG_DIVERGENCE
  divergence( Us, Uf, Ur );
#else
#ifdef REO_LOCAL_DIVERGENCE
  local_divergence( Us, Uf, Ur );
#else
  weak_divergence( Us, Up, Ur );
#endif
#endif

#endif  // DGM_USE_EPETRA
}

/*! \todo Update for handing nodes */
void iEuler::penalty_flux(const vField &Up, const vField &Us,
                          vField &Uf, const Scalar sigma,
                          const char sign ) {
  // cout<<"iEuler::penalty_flux(...), sigma="<<sigma<<endl;
#ifdef REO_USE_GETSIDEMAPS
  iVector mapl, mapr;
#endif
  switch (sign) {
  case '+':
    for (vField::size_type n=0; n<Us.size(); n++) {
      for (LocalSize e=0; e<Us[n]->ne; e++) {
        const Element *P = Up[n]->el[e];
        const Element *S = Us[n]->el[e];
        Element *F = Uf[n]->el[e];
        for (LocalSize i=0; i<S->nSides(); i++) {
          if (S->side[i]->master()) {
            const LocalSize qtot = S->side[i]->qtot();
#ifdef REO_USE_GETSIDEMAPS
            get_side_maps(S->side[i],S->side[i]->link,mapl,mapr);
#endif
            for (LocalSize q=0; q<qtot; q++) {
#ifdef REO_USE_GETSIDEMAPS
              F->side[i]->u[mapl[q]] = 0.5*(S->side[i]->u[mapl[q]] +
                                            S->side[i]->link->u[mapr[q]]) +
                sigma*(P->side[i]->link->u[mapr[q]] -
                       P->side[i]->u[mapl[q]]);
              F->side[i]->link->u[mapr[q]] = -F->side[i]->u[mapl[q]];
#else
              const Ordinal ql = S->sideMap(S->side[i], q);
              const Ordinal qr = S->sideMap(S->side[i]->link, q);
              F->side[i]->u[ql] = 0.5*(S->side[i]->u[ql] +
                                            S->side[i]->link->u[qr]) +
                sigma*(P->side[i]->link->u[qr] -
                       P->side[i]->u[ql]);
              F->side[i]->link->u[qr] = -F->side[i]->u[ql];
#endif
            }
          }
        }
      }
    }
    break;
  case '-':
    for (vField::size_type n=0; n<Us.size(); n++) {
      for (LocalSize e=0; e<Us[n]->ne; e++) {
        const Element *P = Up[n]->el[e];
        const Element *S = Us[n]->el[e];
        Element *F = Uf[n]->el[e];
        for (LocalSize i=0; i<S->nSides(); i++) {
          if (S->side[i]->master()) {
            const LocalSize qtot = S->side[i]->qtot();
#ifdef REO_USE_GETSIDEMAPS
            get_side_maps(S->side[i],S->side[i]->link,mapl,mapr);
#endif
            for (LocalSize q=0; q<qtot; q++) {
#ifdef REO_USE_GETSIDEMAPS
              F->side[i]->u[mapl[q]] = 0.5*(S->side[i]->u[mapl[q]] -
                                            S->side[i]->link->u[mapr[q]]) +
                sigma*(P->side[i]->link->u[mapr[q]] -
                       P->side[i]->u[mapl[q]]);
              F->side[i]->link->u[mapr[q]] = -F->side[i]->u[mapl[q]];
#else
              const Ordinal ql = S->sideMap(S->side[i], q);
              const Ordinal qr = S->sideMap(S->side[i]->link, q);
              F->side[i]->u[ql] = 0.5*(S->side[i]->u[ql] -
                                            S->side[i]->link->u[qr]) +
                sigma*(P->side[i]->link->u[qr] -
                       P->side[i]->u[ql]);
              F->side[i]->link->u[qr] = -F->side[i]->u[ql];
#endif
            }
          }
        }
      }
    }
    break;
  default:
    comm->cerr() << "iEuler::penalty_flux() -- illegal sign" << endl;
    comm->exit(DGM::FAILURE);
  }
}

} // namespace Reo
