#ifndef DGM_REMOVE_FOR_RELEASE

/*=============================================================================
  Module:     Shallow Water Module

  Contact:    S. Scott Collis
              sscoll@sandia.gov

  Copyright:  (c)2013 Sandia National Laboratories
=============================================================================*/

/** \file Shallow.cpp
    \brief Implementation of the 2d Shallow equations
    \author Vincent Mousseau
    \author S. Scott Collis
*/

// local includes
#include "Reo.hpp"
#include "Shallow.hpp"
#include "ShallowIC.hpp"
#include "ShallowBC.hpp"
#include "Wavetype.hpp"
#include "Fluid.hpp"

// DGM includes
#include "Element.hpp"

namespace Reo {

using namespace DGM;

// Print out detailed flux information
// #define DGM_VERBOSE_FLUX

void
Shallow::verify_input_parameters(){
  string objName = root+".obj";
  string srcName = root+".src";
  Json::Value objRoot;
  Json::Value srcRoot;

  // read in the parameters from the .obj file
  ifstream objIn(objName.c_str());
  if(objIn){
    bool readingComments = true;
    string commentBuffer;
    while(readingComments){
      commentBuffer.clear();
      getline(objIn,commentBuffer);
      if(commentBuffer[0]!='#'&&commentBuffer[0]!=' '&&commentBuffer.size()!=0)
        readingComments = false;
    }
    Json::Reader reader;
    string buffer = read_block(objIn);
    bool parsingSuccessful = reader.parse(buffer,objRoot,true);
    if (!parsingSuccessful) {
      comm->cout()<<"Shallow::verify_input_parameters() could not "
          "parse Json input"<<endl;
      comm->cout()<<reader.getFormattedErrorMessages();
      throw DGM::exception("Json parsing error");
    }
  }
  // read in the parameters from the .src file
  ifstream srcIn(srcName.c_str());
  if(srcIn){
    // dispose of the comment lines:
    bool readingComments = true;
    string commentBuffer;
    while(readingComments){
      commentBuffer.clear();
      getline(srcIn,commentBuffer);
      if(commentBuffer[0]!='#'&&commentBuffer[0]!=' '&&commentBuffer.size()!=0)
        readingComments = false;
    }
    Json::Reader reader;
    string buffer = read_block(srcIn);
    bool parsingSuccessful = reader.parse(buffer,srcRoot,true);
    if (!parsingSuccessful) {
      comm->cout()<<"Shallow::verify_input_parameters() could not "
          "parse Json input"<<endl;
      comm->cout()<<reader.getFormattedErrorMessages();
      throw DGM::exception("Json parsing error");
    }
  }

  // now check for duplicate keys with different values:
  Json::ValueIterator srcIt = srcRoot.begin();
  for(;srcIt!=srcRoot.end();++srcIt){
    string srcVarName = srcIt.memberName();
    Json::ValueIterator objIt = objRoot.begin();
    for(;objIt!=objRoot.end();++objIt){
      string objVarName = objIt.memberName();
      if(srcVarName==objVarName&&srcVarName!="Verbosity"){ // different values for verbosity is okay
        if(srcRoot.get(srcVarName,0.0)!=objRoot.get(objVarName,0.0)){
          comm->cout()<< " ERROR:  The following variable has been defined in " << srcName << " and " << objName << endl
                      << " but the values are not equal (unclear how to proceed): " << srcVarName << endl;
          throw DGM::exception("Input parameters verification error");
        }
      }
    }
  }
}

/// Constructor
Shallow::Shallow( DGM::ArgList &args, const DGM::Comm::Ptr comm_,
                  const int p_inc )
  : Domain(args, comm_), Usrc(comm_), Utmp(comm_), flux(LaxFriedrichs) {
  if (comm->verbosity())
    comm->cout() << "Shallow::Shallow(...)" << endl;

  Ordinal p, q;
  p = params["p"];                     // polynomial order
  p += p_inc;
  if ( !(q=params["q"]) ) q = p + 2;   // number of quadrature points
  nsd = params["nsd"];                 // number of space dimensions

  params.get("auxtec", 0);                // Compute derivative quantities
  params.get("plot3d_x", 1);              // plot3d grid file
  params.get("plot3d_q", 1);              // plot3d mesh file
  params.get("flux", "LaxFriedrichs");    // Numerical flux

  // read arguments (overrides defaults and input file)
  parse_args( args );

  // Numerical fluxes
  string value = (string)params["flux"];
  if (lowerCase(value).compare("laxfriedrichs") == 0)
    flux = LaxFriedrichs;
  else
    comm->error("Reo::Shallow::Unknown numerical flux");

  vector<string> field_names;          // Field names
  field_names.push_back("phi");

  // build a Field of Elements and Sides
  if (params["imesh"]) {
    Mesh mesh(params);
    U.push_back( new Field(p, q, mesh, root, field_names[0],
                           Field::FULL, comm ) );
    partition = U[0]->partition;
  } else if (params["bmesh"]) {
    U.push_back( new Field(p, q, root, field_names[0], partition, 1,
                           Reo::NumEqntype, p2i(SHALLOW), comm ) );
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
    comm->error("Reo::Shallow: nsd must be 2");
  } else if (nsd == 2) {
    Nfields = 3;  // is equal to NFIELDS in Shallow.hpp
    field_names.push_back("uphi");
    field_names.push_back("vphi");
  } else if (nsd == 3) {
    comm->error("Reo::Shallow: nsd must be 2");
  } else {
    comm->cerr() << "Illegal value for nsd = " << nsd
                 << " in Reo::Shallow::Shallow" << endl;
    comm->exit(DGM::FAILURE);
  }

  // build the rest of the vector field
  for (vField::size_type i=1; i<Nfields; i++)
    U.push_back( new Field( U[0], root, field_names[i] ) );

  // make auxilary Fields using copy constructor
  for (vField::size_type i=0; i<Nfields; i++) {
    Ut.push_back( new Field( U[0], root, field_names[i] ) );
    Usrc.push_back( new Field( U[0], root, field_names[i] ) );
  }

  // set vField names
  U.set_name("U");
  Ut.set_name("Ut");
  Usrc.set_name("Usrc");

  // allocate workspace
  wk1.resize(5*max(Lmax(),Qmax()));
  wk2.resize(5*max(Lmax(),Qmax()));

  // make sure that storage is initialized
  zero_all_fields();

  // make analysis object
  response = Response::factory(U, this);

  setup_BCdb();            // setup BC database

  //verify_input_parameters();

  setup_Sourcedb();        // setup Source term database

  set_TimeInt();
}

/// Parse parameters from the argument list
void Shallow::parse_args( DGM::ArgList &args ) {
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
#ifdef DGM_REMOVE_ARGUMENTS
  // remove tagged arguments
  for ( list< DGM::ArgList::iterator >::iterator a=li.begin();
        a!=li.end(); a++) args.erase(*a);
#endif
}

Shallow::~Shallow() {
  if (comm->verbosity()) comm->cout()<<"~Shallow()"<<endl;
}

void Shallow::showUsage() {
  comm->cout()
    << "Reo::Shallow Class Options \n"
    << "----------------------------------------------------------------\n"
    << "-nox     " << '\t' << "No grid file         \n"
    << "-noq     " << '\t' << "No solution file     \n"
    << "-aux     " << '\t' << "Auxilary Tecplot file\n"
    << "----------------------------------------------------------------\n";
}

void Shallow::set_material() {
}

/// Activate to force a well-balanced method for a flat bottom, no-flow
#define REO_SHALLOW_ENFORCE_BALANCE

/// (Negative) of the time derivative
void Shallow::time_derivative( vField &Us, vField &Uf ) {
  static bool firsttime=true;
  convection( Us, Uf );
  add_source( Us, Uf );
  project( Uf );
#ifdef REO_SHALLOW_ENFORCE_BALANCE
  if (firsttime) {
    copy(Uf,Usrc);
    firsttime=false;
  }
  axpy(-one,Usrc,Uf);
#endif
}

/// Evaluate the convection term
/** See: E.F. Toro, "Riemann Solvers and Numerical Methods for Fluid
    Dynamics," 2nd Edition, Springer, 1999, Section 1.6.9 for a detailed
    description of the Shallow equations.  In general, we follow the now
    standard notation presented therein except that we use S for the state
    vector of conservation variables in lieu of U since U is used for
    the solution vector field at the Domain level. */
void Shallow::convection( vField &Us, vField &Uf ) {
  Element *S[NFIELDS], *F[NFIELDS];
  dVector u, v, p, d, d1;
  dVector phi, uphi, vphi;

  Us.fill_sides();
#ifdef USE_SHALLOW_BC
  // The purpose of this compiler define is to override the default behavior
  // where the Shallow BC's are enforced during the convection phase and the NS
  // BCs are used in the diffusion term.  This is useful when performing
  // optimization, although I still do not understand why this is
  // necessary. [SSC]
  Shallow::enforce_bc(Us);
#else
  enforce_bc(Us);
#endif
  Us.begin_share_sides();
  // Add the interior contribution
  for (LocalSize e=0; e<Us[0]->ne; e++) {
    S[0] = Us[0]->el[e]; // local version of the state
    S[1] = Us[1]->el[e];
    S[2] = Us[2]->el[e];

    F[0] = Uf[0]->el[e]; // local version of the flux
    F[1] = Uf[1]->el[e];
    F[2] = Uf[2]->el[e];

    const Ordinal qtot = S[0]->qtot;

    phi.alias (S[0]->u);  // geopotential
    uphi.alias(S[1]->u);  // x momentum
    vphi.alias(S[2]->u);  // y momentum

    u.alias(wk1,0,qtot);
    v.alias(wk1,qtot,qtot);
    p.alias(wk1,2*qtot,qtot);
    d.alias(wk1,3*qtot,qtot);
    d1.alias(wk1,4*qtot,qtot);

    dvdiv(uphi, phi, u);    // compute u
    dvdiv(vphi, phi, v);    // compute v

    // P = 0.5 * phi * phi
    dvmul(phi, phi, p);
    scale(pt5, p);

    // F[0] = (uphi),x + (vphi),y
    S[0]->gradient(uphi, F[0]->u, 'x');
    S[0]->gradient(vphi, d, 'y');
    dvadd(d, F[0]->u);

    // F[1] = (uphi*u+p),x + (uphi*v),y
    dvvtvp(uphi, u, p, d);
    S[1]->gradient(d, F[1]->u, 'x');
    dvmul(uphi, v, d);
    S[1]->gradient(d, d1, 'y');
    dvadd(d1, F[1]->u);

    // F[2] = (vphi*u),x + (vphi*v+p),y
    dvmul(vphi, u, d);
    S[2]->gradient(d, F[2]->u, 'x');
    dvvtvp(vphi, v, p, d);
    S[2]->gradient(d, d1, 'y');
    dvadd( d1, F[2]->u );
  }
  Us.end_share_sides();

  // add the surface integral
  convective_flux( Us, Uf );
  for (LocalSize e=0; e<Us[0]->ne; e++) {
    for (vField::size_type n=0; n<Nfields; n++) {
      F[n] = Uf[n]->el[e];
      Us[n]->el[e]->lift( F[n], F[n]->u );
    }
  }
}

/// Compute the Shallow flux
/** For descriptions of the numerical fluxes See: E.F. Toro, "Riemann
    Solvers and Numerical Methods for Fluid Dynamics," 2nd Edition,
    Springer, 1999. */
void Shallow::convective_flux(vField &Us, vField &Uf) {
#ifdef REO_USE_GETSIDEMAPS
  iVector mapl, mapr;
#endif
  Scalar Ul[NFIELDS], Ur[NFIELDS];
  Scalar Fh[NFIELDS], Fpl[NFIELDS], Fmr[NFIELDS];
  Scalar lambda[NFIELDS];
  Scalar phil, uphil, vphil, ul, pl;
  Scalar phir, uphir, vphir, ur, pr;
  vector<Side *> sl(Nfields), sr(Nfields);
  vector<Side *> fl(Nfields), fr(Nfields);

  for (Ordinal e=0; e<ne; ++e) {                  // loop over elements
    Element* U = Us[0]->el[e];
    for (Ordinal i=0; i<Us[0]->el[e]->nSides(); ++i) {  // loop over sides
      if (Us[0]->el[e]->side[i]->master()) {      // master side
        // localize the state and flux side pointers
        for (vField::size_type n=0; n<Nfields; n++) {
          sl[n] = Us[n]->el[e]->side[i];          // left state side
          sr[n] = Us[n]->el[e]->side[i]->link;    // right state side
          fl[n] = Uf[n]->el[e]->side[i];          // left flux side
          fr[n] = Uf[n]->el[e]->side[i]->link;    // right flux side
        }
#ifdef REO_USE_GETSIDEMAPS
        get_side_maps( sl[0], sr[0], mapl, mapr );
#endif

        const Ordinal qtot = sl[0]->qtot();       // number of quad pts on side
        for (Ordinal q=0; q<qtot; ++q) {          // loop over side quad-pts

#ifdef REO_USE_GETSIDEMAPS
          const Ordinal ql = mapl[q];              // quadrature on the left
          const Ordinal qr = mapr[q];              // quadrature on the right
#else
          const Ordinal ql = U->sideMap(sl[0], q);
          const Ordinal qr = U->sideMap(sr[0], q);
#endif

          const Scalar nxl = sl[0]->nx(ql);
          const Scalar nyl = sl[0]->ny(ql);

          // compute normal flux from interior (left)

          // left state
          Ul[0] = sl[0]->u[ql];                   // geopotential
          Ul[1] = sl[1]->u[ql];                   // x momentum
          Ul[2] = sl[2]->u[ql];                   // y momentum

          //cout << "LEFT element: " << e << " side: " << i << " phi: " << Ul[0] << " uphi: " << Ul[1] << " vphi: " << Ul[2] << endl;

          // left state projected to the normal
          phil = Ul[0];                           // geopotential
          uphil = Ul[1]*nxl + Ul[2]*nyl;          // normal momentum
          vphil = Ul[2]*nxl - Ul[1]*nyl;          // tangent momentum

          // left primative variables (projected to left normal)
          const Scalar iphil = one/phil;
          ul = iphil*uphil;                       // normal velocity
          //vl = iphil*vphil;                     // tangent velocity
          pl = pt5 * phil * phil;                 // pressure

          // make sure that density and pressure are realizable
          if (phil < aepsM) {
            comm->cerr()<<"Element: "<<e<<", Side: "<<i<<", Geopotenial left (g*(eta +h)): "
                        <<phil<<endl;
            comm->exit();
          }
          if (pl < aepsM) {
            comm->cerr()<<"Element: "<<e<<", Side: "<<i<<", Pressure left (1/2 phi^2): "
                        <<pl<<endl;
            comm->exit();
          }

          // put the left flux on the left state sides
          sl[0]->u[ql] = Fpl[0] = uphil;
          sl[1]->u[ql] = Fpl[1] = (uphil*ul+pl)*nxl - (vphil*ul)*nyl;
          sl[2]->u[ql] = Fpl[2] = (uphil*ul+pl)*nyl + (vphil*ul)*nxl;

          //cout << "LEFT element: " << e << " side: " << i << " sl[0]: " << sl[0]->u[qr] << " sl[1]: " << sl[1]->u[qr] << " sl[2]: " << sl[2]->u[qr] << endl;

          // compute normal flux from exterior (right)

          // right state
          Ur[0] = sr[0]->u[qr];
          Ur[1] = sr[1]->u[qr];
          Ur[2] = sr[2]->u[qr];

          //cout << "RIGHT element: " << e << " side: " << i << " phi: " << Ur[0] << " uphi: " << Ur[1] << " vphi: " << Ur[2] << endl;


          // normal right state (note that left normal is used!)
          phir = Ur[0];
          uphir = Ur[1]*nxl + Ur[2]*nyl;
          vphir = Ur[2]*nxl - Ur[1]*nyl;

          // right primative variables (projected to left normal)
          const Scalar iphir=one/phir;
          ur = iphir*uphir;
          //vr = iphir*vphir;
          pr = pt5 * phir * phir;                 // pressure

          // make sure that density and pressure are realizable
          if (phir < aepsM) {
            comm->cerr()<<"Element: "<<e<<", Side: "<<i<<", Geopotential right ( g(h+eta) ): "
                        <<phir<<" aepsM: "<<aepsM<<endl;
            comm->exit();
          }
          if (pr < aepsM) {
            comm->cerr()<<"Element: "<<e<<", Side: "<<i<<", Pressure right (1/2 phi^2): "
                        <<pr<<endl;
            comm->exit();
          }

          // put the left flux on the left state sides
          sr[0]->u[qr] = Fmr[0] = uphir;
          sr[1]->u[qr] = Fmr[1] = (uphir*ur+pr)*nxl - (vphir*ur)*nyl;
          sr[2]->u[qr] = Fmr[2] = (uphir*ur+pr)*nyl + (vphir*ur)*nxl;

          //cout << "RIGHT element: " << e << " side: " << i << " sr[0]: " << sr[0]->u[qr] << " sr[1]: " << sr[1]->u[qr] << " sr[2]: " << sr[2]->u[qr] << endl;


#ifdef TRY_NUMERICAL_FLUX
          // test of the new class to compute the fluxes
          dVector N(2);
          N[0] = nxl; N[1] = nyl;
          LF.evaluate( Ul, Ur, N, Fpl, Fmr, Fh );
#else
          switch (flux) {
          case LaxFriedrichs: {

            Scalar lmax = zero;

            const Scalar al = sqrt(phil);

            lambda[0] = ul-al;
            lambda[1] = ul;
            lambda[2] = ul+al;

            for(vField::size_type n=0; n<Nfields; ++n)
              lmax=max(lmax,fabs(lambda[n]));

            const Scalar ar = sqrt(phir);

            lambda[0] = ur-ar;
            lambda[1] = ur;
            lambda[2] = ur+ar;

            for(vField::size_type n=0; n<Nfields; ++n)
              lmax=max(lmax,fabs(lambda[n]));

            // Lax-Friedrichs flux
            Fh[0] = pt5 * ( Fpl[0] + Fmr[0] + lmax * ( Ul[0] - Ur[0] ) );
            Fh[1] = pt5 * ( Fpl[1] + Fmr[1] + lmax * ( Ul[1] - Ur[1] ) );
            Fh[2] = pt5 * ( Fpl[2] + Fmr[2] + lmax * ( Ul[2] - Ur[2] ) );

#ifdef DGM_VERBOSE_FLUX
            cout << "Lax-Friedrichs: Element " << e << ", Side " << i << endl;
            cout << Fh[0]<< ", "<<Fh[1]<<", "<<Fh[2]<<endl;
#endif
            break;
          }
          default:
            throw DGM::exception("Illegal value of flux type");
          }
#endif
          //cout << " BREAK " << endl;
          // put fluxes on field sides
          for (vField::size_type n=0; n<Nfields; ++n) {
            sr[n]->u[qr] *= -one;        // correct for right normal
            fl[n]->u[ql]  =  Fh[n];      // upwind flux
            fr[n]->u[qr]  = -Fh[n];      // correct for right normal
            //cout << " n: " << n << " Fh[n]: " << Fh[n] << " sr[n]: " << sr[n]->u << " sl[n]: " << sl[n]->u << endl;
          }
        }
      }
    }
  }
}

/// Generate plot output
int Shallow::plot(const string &rst) {
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
    if (comm->Master()) U.tecplot(fname,caption);
  if (params["paraview"]) U.paraview(name,caption);
  if (params["plot3d"]) {
    if (params["plot3d_x"]) {
      sprintf(buf,"%s.xyz",name.c_str()); fname = buf;
      U.plot3d_x(fname);
    }
    if (params["plot3d_q"]) {
      sprintf(buf,"%s.q",name.c_str()); fname = buf;
      U.plot3d_q(fname);
    }
  }
  if (params["auxtec"]) {
    compute_primatives();     // puts primatives in Ut
    sprintf(buf,"%s.aux.dat",name.c_str()); fname = buf;
    sprintf(buf,"Auxilary variables at t =%11.4e, step = %lld",
            t,(long long)step);
    caption = buf;
    if (comm->Master()) Ut.tecplot(fname,caption);
  }
  return 0;
}

/** This is rather expensive and many of these steps are already done
    in the convection phase. */
Scalar Shallow::set_time_step(vField &U) {
  // cout << "Shallow::set_time_step()" << endl;
  Scalar cfl = 0;
#ifdef DGM_STORE_METRICS
  Element *S;
  dVector phi, uphi, vphi;
  dVector u, v, c, wk, idt;

  if (dtl.size()==0) dtl.resize(U[0]->ne);  // make space for local dt

  for (LocalSize e=0; e<ne; e++) {
    S = U[0]->el[e];
    const int qtot = S->qtot;

    phi.alias (U[0]->el[e]->u);  // geopotential
    uphi.alias(U[1]->el[e]->u);  // x momentum
    vphi.alias(U[2]->el[e]->u);  // y momentum

    u.alias(wk1,0,qtot);
    v.alias(wk1,qtot,qtot);
    c.alias(wk1,2*qtot,qtot);
    wk.alias(wk1,3*qtot,qtot);
    idt.alias(wk1,4*qtot,qtot);

    dvdiv(uphi, phi, u);  // compute u
    dvdiv(vphi, phi, v);  // compute v

    // c = sqrt(phi)
    CMC::set(1.0,c);
    dvmul(phi, c, c);
    dvsqrt( c, c );

    dvmul( u, S->geom->dxr, idt );
    dvvtvp( v, S->geom->dyr, idt, idt );
    abs( idt );
    dvmul( u, S->geom->dxs, wk );
    dvvtvp( v, S->geom->dys, wk, wk );
    abs( wk );
    dvadd( wk, idt );
    dvvtvp( c, S->geom->acoustic, idt, idt );
    dvmul( S->geom->ivol, idt );
#ifdef REO_SHALLOW_DEBUG
    if (comm->MyPID() == 0)
      cout << "Eid = " << e << ", max(idt) = " << idt[max(idt)]
           << ", max(c) = " << c[max(c)] << endl;
#endif
    cfl = max( cfl, dt * idt.Max() );
    dtl[e] = one/idt.Max();
  }
#ifdef DGM_PARALLEL
  Scalar local = cfl;
  // cout << comm->MyPID() << " cfl = " << local << endl;
  comm->MaxAll( &local, &cfl, 1 );
#endif

  Scalar dt_old = dt;
  if (CFLmax != 0 && dtmax != 0) {
    dt = min( dtmax, CFLmax * dt / cfl );
    for (LocalSize e=0; e<U[0]->ne; e++) dtl[e] = min(dtmax, CFLmax * dtl[e]);
  } else if (CFLmax != 0) {
    dt = CFLmax * dt / cfl;
    for (LocalSize e=0; e<U[0]->ne; e++) dtl[e] = CFLmax * dtl[e];
  } else {
    for (LocalSize e=0; e<U[0]->ne; e++) dtl[e] = dt;
  }
  cfl = cfl * dt / dt_old;
#endif  // DGM_STORE_METRICS
  return cfl;
}

/// Set the initial condition
void Shallow::set_ic(vField &F, string ext) {
  //comm->cout()<<"Shallow::set_ic"<<endl;
  t = 0.0; step = 0;
  string fname = root+ext;
  ifstream in(fname.c_str());
  if (!in) {
    comm->cerr() << "Reo::Shallow: Could not open initial condition "
                 << fname << endl;
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
    if (comm->verbosity())
      comm->cout() << "Restarting from: " << rstfile << endl;
  } else if (lowerCase(code) == "restart_p") {
    string rstfile;
    if (!(in>>rstfile)) {
      comm->cerr() << "Cannot read restart file name from " << fname << endl;
      comm->exit(DGM::FAILURE);
    }
    LocalSize eid, dof;
    Scalar eps;
    in >> eid >> dof >> eps;
    read(rstfile, F);
#ifdef DGM_PARALLEL
    if ( partition->owns(eid) ) F[dof]->el[eid]->u += eps;
#else
    F[dof]->el[eid]->u += eps;
#endif
    comm->cout() << "Restarting from: " << rstfile
                 << " with added perturbations." << endl;
  } else if (lowerCase(code) == "bore") {
    // two dimensional bore problem
    Bore ic;
    for (Ordinal e=0; e<ne; e++) {
      for (Ordinal q=0; q<F[0]->el[e]->qtot; q++) {
        F[0]->el[e]->u[q] = ic.PHI( (*F[0]->el[e]->C)[q] );
        F[1]->el[e]->u[q] = ic.UPHI( (*F[1]->el[e]->C)[q] );
        F[2]->el[e]->u[q] = ic.VPHI( (*F[2]->el[e]->C)[q] );
      }
    }
  } else if (lowerCase(code) == "mmsinitialcondition") {
    // two dimensional still domain with a flat bottom and unit height
    MMSInitialCondition ic;
    for (Ordinal e=0; e<ne; e++) {
      for (Ordinal q=0; q<F[0]->el[e]->qtot; q++) {
        F[0]->el[e]->u[q] = ic.PHI( (*F[0]->el[e]->C)[q] );
        F[1]->el[e]->u[q] = ic.UPHI( (*F[1]->el[e]->C)[q] );
        F[2]->el[e]->u[q] = ic.VPHI( (*F[2]->el[e]->C)[q] );
      }
    }
  } else if (lowerCase(code) == "brsinitialcondition") {
    // two dimensional still domain with a flat bottom and unit height
    BRSInitialCondition ic;
    for (Ordinal e=0; e<ne; e++) {
      for (Ordinal q=0; q<F[0]->el[e]->qtot; q++) {
        F[0]->el[e]->u[q] = ic.PHI( (*F[0]->el[e]->C)[q] );
        F[1]->el[e]->u[q] = ic.UPHI( (*F[1]->el[e]->C)[q] );
        F[2]->el[e]->u[q] = ic.VPHI( (*F[2]->el[e]->C)[q] );
      }
    }
  } else if (lowerCase(code) == "pbinitialcondition") {
    // two dimensional still domain with a flat bottom and unit height
    BRSInitialCondition ic;
    for (Ordinal e=0; e<ne; e++) {
      for (Ordinal q=0; q<F[0]->el[e]->qtot; q++) {
        F[0]->el[e]->u[q] = ic.PHI( (*F[0]->el[e]->C)[q] );
        F[1]->el[e]->u[q] = ic.UPHI( (*F[1]->el[e]->C)[q] );
        F[2]->el[e]->u[q] = ic.VPHI( (*F[2]->el[e]->C)[q] );
      }
    }
  } else{
    comm->error("Reo::Shallow::set_ic()  Unsupported IC type: " + code);
  }
#ifdef DGM_NO_PROJECT_IC
  comm->cout() << "WARNING:  No projection of Initial condition" << endl;
  for (LocalSize i=0; i<F.size(); i++)
    for (LocalSize e=0; e<ne; e++)
      F[i]->el[e]->state = Element::Physical;
#else
  project( F );
#endif
}

//===========================================================================
//                        BC database management
//===========================================================================

/// Load up the available BC types
void Shallow::setup_BCdb( ) {
  // cout << "Shallow::setup_BCdb()" << endl;
  // set default BC types
  dVector ub(Nfields);
  ub[0] = 1.0;
  ub[1] = 1.0;
  ub[2] = 0.0;
  BC_db["W"].reset( new WallBC("W") );

  // read new BC types from file
  string fname = root+".bct";
  ifstream in(fname.c_str());
  if (in) Shallow::read_BCdb( in );   // database of active BC types
}

void Shallow::read_BCdb( ifstream &in ) {
  // cout << "Shallow::read_BCdb( ifstream &in )" << endl;
  string tag;
  BC *pbc;
  while ( (pbc = Shallow::make_BC(in,tag)) ) {
    if ( BC_db.find(tag) != BC_db.end() )
      comm->cerr() << "WARNING in Reo::Shallow::read_BCdb() Overriding BC "
        "type \"" << tag << "\"." << endl;
    BC_db[tag].reset( pbc );
  }
}

/** Note that caution is required here as the Shallow module searches for
    substrings within the BC tag.  This makes it possible that many
    Navier-Stokes BCs map onto a single Shallow BC, but care is required to
    make the substring search order correct and unique. */
BC* Shallow::make_BC( ifstream &in, string &tag ) {
  // cout << "Shallow::make_BC(ifstream &in, string &tag)" << endl;
  string code;
  if (!(in >> code)) return NULL;
  code = lowerCase(code);

  if ( code.find("wall") != code.npos ) {
    if (!(in >>tag)) error("Shallow::make_BC: Cannot read WallBC tag",1);
    return new WallBC(tag,in);
  }
  else if (code == "function") {
    if (!(in >> tag))
      error("Shallow::make_BC() Cannot read FuncBC tag");
    return new FuncBC(tag,in,3,false);
  }
  else {
    if(comm->Master())
      comm->cerr()<<"WARNING in Shallow::make_BC() Illegal BC type: "+
        code<<endl;
  }
  return NULL;
}

//===========================================================================
//                        Source database management
//===========================================================================

// here you use the State vField for the construction of the SourceControl
// scratch vField, is it important to use the local projection. [gqchen]

/// Construct source terms
Source::Ptr Shallow::make_Source( ifstream &in, string &tag ) {
  // cout << "Shallow::make_Source" << endl;
  string code;
  Source::Ptr p;
  if (!(in >> code)) return p;
  while (code[0]=='#') {  // eat comment lines
    string buffer;
    getline(in,buffer);
    if (!(in >> code)) return p;
  }
  //
  //  Momentum sources
  //
  if (lowerCase(code)=="xmom" || lowerCase(code)=="xmomentumsource") {
    if (!(in >> tag)) error("Reo::Shallow::Cannot read Xmom tag");
    p.reset( new XMomSource(tag,in) );
  } else if (lowerCase(code)=="ymom" || lowerCase(code)=="ymomentumsource") {
    if (!(in >> tag)) error("Reo::Shallow::Cannot read Ymom tag");
    p.reset( new YMomSource(tag,in) );
  } else if (lowerCase(code) == "function") {
    if (!(in >> tag)) error("Reo::Shallow::Cannot read FuncSource tag",1);;
    p.reset( new FuncSource(tag,in,3,false) );
  }else if (lowerCase(code)=="forcesource") {
    if (!(in >> tag)) error("Reo::Shallow::Cannot read ForceSource tag");
    p.reset( new ForceSource(tag,in,get_comm()) );
  } else if (lowerCase(code)=="forcesourcectrl") {
    if (!(in >> tag)) error("Reo::Shallow::Cannot read ForceSourceCtrl tag");
    p.reset( new ForceSourceCtrl(tag,in,get_comm()) );
  } else if (lowerCase(code)=="g3d" || lowerCase(code)=="gaussiansource") {
    if (!(in >> tag)) error("Reo::Shallow::Cannot read GaussianSource tag");
    p.reset( new GaussianSource(tag,in) );
  } else if (lowerCase(code) == "distributedcontrol") {
    if (!(in >> tag)) error("Reo::Shallow::Cannot read DistributedControl tag");
    p.reset( new DistributedControl(tag, in, U) );
  } else if (lowerCase(code)=="forcesourcectrlii") {
    if (!(in >> tag)) error("Reo::Shallow::Cannot read ForceSourceCtrlII tag");
    p.reset( new ForceSourceCtrlII(tag,in,get_comm()) );
  } else {
    throw DGM::exception("Reo::Shallow::make_Source() Illegal Source type");
  }
  return p;
}

// Add source terms
void Shallow::add_source(const vField &Us, vField &Ur) {
  // cout << "Shallow::add_source(vField &)" << endl;
  for (Source::db_citr i=Source_db.begin(); i!= Source_db.end(); ++i)
    // cout << "Adding source: " << i->first << endl;
    i->second->apply( t, Us, Ur);
}

//===========================================================================
//                        Output methods
//===========================================================================

// Compute primative variables and put them in Ut for plotting
// The base case plots eta, h, and v.  The ability to replace h with u is
// commented below
void Shallow::compute_primatives() {
  Element *S[NFIELDS], *F[NFIELDS];
  dVector u, v;
  dVector phi, uphi, vphi;
  Bore ic;

  for (LocalSize k=0; k<U[0]->ne; k++) {

    // local version of the state
    S[0] = U[0]->el[k];
    S[1] = U[1]->el[k];
    S[2] = U[2]->el[k];

    // local version of the state
    F[0] = Ut[0]->el[k];
    F[1] = Ut[1]->el[k];
    F[2] = Ut[2]->el[k];

    const Ordinal qtot = S[0]->qtot;

    phi.alias (S[0]->u);  // geopotential
    uphi.alias(S[1]->u);  // x momentum
    vphi.alias(S[2]->u);  // y momentum

    u.alias(wk1,0,qtot);
    v.alias(wk1,qtot,qtot);

    dvdiv(uphi, phi, u);    // compute u
    dvdiv(vphi, phi, v);    // compute v

    for (LocalSize q=0; q<F[0]->qtot; q++) { // Loop over quadrature pts
      const Scalar phi = U[0]->el[k]->u[q];
      const Scalar grav = ic.G((*F[0]->C)[q]);
      const Scalar high = ic.h((*F[0]->C)[q]);
      const Scalar eta = (phi / grav) - high;
      F[0]->u[q] = eta;
      // This plots h not u
      F[1]->u[q] = high;
    }

    // This plots u not h
    // F[1]->fill(u);
    F[2]->fill(v);
  }
}

/// if defined then perform a projection to compute diffusive flux
#define SHALLOW_GRADIENT_PROJECT

/// Compute a jump savy gradient
void Shallow::gradient( Element *S, Element *F, dVector &u,
                        dVector &ux, dVector &uy ) {
  S->gradient( u, ux, uy );
  S->lift( F, ux, 'x' );
#ifdef SHALLOW_GRADIENT_PROJECT
  S->project(ux);
#endif
  S->lift( F, uy, 'y' );
#ifdef SHALLOW_GRADIENT_PROJECT
  S->project(uy);
#endif
}

/// Convert edge values from conservative to primitive variables
void Shallow::primitive_sides( vField &Us ) {
  // loop over all sides including boundary sides
  for (LocalSize k=0; k<Us[0]->ne; k++) {
    for (LocalSize i=0; i<Us[0]->el[k]->nSides(); i++) {
      if (Us[0]->el[k]->side[i]->master()) {
        dVector wk(Us[0]->el[k]->side[i]->qtot());// WARNING: new memory
        // left side
        dVector  phi(Us[0]->el[k]->side[i]->u);     // geopotential
        dVector  u(Us[1]->el[k]->side[i]->u);     // x momentum
        dVector  v(Us[2]->el[k]->side[i]->u);     // y momentum
        dvdiv(u, phi, u);       // u-velocity
        dvdiv(v, phi, v);       // v-velocity
        // right side
        phi.alias(Us[0]->el[k]->side[i]->link->u);  // geopotential
        u.alias(Us[1]->el[k]->side[i]->link->u);  // x momentum
        v.alias(Us[2]->el[k]->side[i]->link->u);  // y momentum
        dvdiv(u, phi, u);       // u-velocity
        dvdiv(v, phi, v);       // v-velocity
      }
    }
  }
}

/** Computes lift and drag and saves every time-step. Also output profiles
    every Ntout time steps */
void Shallow::write_bndry_stats() {
  static FILE *frc = NULL;
  if (!U[0]->bndry_stats->valid) return;
  if (comm->Master()) {  // unsteady forces
    if (!frc) {
      string fname;
      char buf[80];
      sprintf(buf,"%s.frc",root.c_str());
      fname = buf;
      frc = fopen(fname.c_str(),"a+");  // append to end of file
    }
  }
  Coord C;
  dVector phi, uphi, vphi;

  U[0]->bndry_stats->get_coordinates( C );
  U[0]->bndry_stats->get_solution( phi );
  U[1]->bndry_stats->get_solution( uphi );
  U[2]->bndry_stats->get_solution( vphi );

  Ordinal qtot = phi.size();
  dVector u(qtot), v(qtot), p(qtot), e(qtot), wk(qtot);

  dvdiv(uphi, phi, u);   // compute u
  dvdiv(vphi, phi, v);   // compute v

  // p = 0.5 * phi * phi
  dvmul(phi, phi, p);
  scale(pt5,p);

#ifdef DGM_PARALLEL
#else
  // output unsteady loads
  fprintf(frc, "%18.11e %18.11e %18.11e\n", t, U[0]->bndry_stats->dragcalc(p),
          U[0]->bndry_stats->liftcalc(p));
  fflush(frc);

  if (step%Ntout==0) {
    // output full boundary data
    string fname;
    char buf[80];
    sprintf(buf,"%s.%lld.bdt",root.c_str(),(long long)step);
    fname = buf;
    FILE *out = fopen(fname.c_str(),"w");
    for (Ordinal q=0; q<qtot; ++q )
      fprintf(out,"%18.11e %18.11e %18.11e %18.11e "
              "%18.11e %18.11e\n",
              C.x[q], C.y[q], phi[q], uphi[q], vphi[q], p[q]);
    fclose(out);

    // output pressure distribution
    sprintf(buf,"%s.%lld.cp",root.c_str(),(long long)step);
    fname = buf;
    out = fopen(fname.c_str(),"w");
    fprintf(out,"#%18.11e %18.11e\n", U[0]->bndry_stats->dragcalc(p),
            U[0]->bndry_stats->liftcalc(p));
    for (Ordinal q=0; q<qtot; ++q )
      fprintf(out," %18.11e %18.11e %18.11e\n", C.x[q], C.y[q], p[q]);
    fclose(out);
  }
#endif  // DGM_PARALLEL
}

} // namespace Reo

#else // DGM_REMOVE_FOR_RELEASE
// This capability is under development.
#endif // DGM_REMOVE_FOR_RELEASE
