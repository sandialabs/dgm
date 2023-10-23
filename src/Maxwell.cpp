/*=============================================================================
  Module:     Maxwell Module

  Contact:    S. Scott Collis
              sscollis@me.com

  Copyright:  (c)2014 Scott Collis
=============================================================================*/

/** \file Maxwell.cpp
    \brief Implementation of the 2d Maxwell equations
    \author S. Scott Collis
*/

// local includes
#include "Reo.hpp"
#include "Maxwell.hpp"
#include "MaxwellIC.hpp"
#include "MaxwellBC.hpp"

// DGM includes
#include "IC.hpp"
#include "Edge.hpp"
#include "Side.hpp"
#include "Vertex.hpp"

namespace Reo {

using namespace DGM;

/// Constructor
Maxwell::Maxwell(DGM::ArgList &args, const DGM::Comm::Ptr comm_,
                 const int p_inc) :
  Domain(args, comm_), flux(LaxFriedrichs) {
  const int verb(comm->verbosity());
  Stopwatch cpu; cpu.start();
  if (verb) comm->cout() << "Building Maxwell domain..." << endl;

  // Memory diagnostics (for debugging)
  if (verb>1) {
    comm->cout() << "  Size of Element = " << sizeof(Element) << endl;
    comm->cout() << "  Size of Tri = " << sizeof(Tri) << endl;
    comm->cout() << "  Size of Edge = " << sizeof(Edge) << endl;
    comm->cout() << "  Size of Side = " << sizeof(Side) << endl;
    comm->cout() << "  Size of Vertex = " << sizeof(Vertex) << endl;
    comm->cout() << "  Size of Maxwell = " << sizeof(Maxwell) << endl;
    comm->cout() << "  Size of Field = " << sizeof(Field) << endl;
    comm->cout() << "  Size of vField = " << sizeof(vField) << endl;
    comm->cout() << "  Size of dVector = " << sizeof(dVector) << endl;
    comm->cout() << "  Size of Vector<Scalar,size_t> = "
                 << sizeof(CMC::Vector<Scalar,size_t>) << endl;
    comm->cout() << "  Size of Vector<Scalar,int> = "
                 << sizeof(CMC::Vector<Scalar,int>) << endl;
    comm->cout() << "  Size of Vector<float,int> = "
                 << sizeof(CMC::Vector<float,int>) << endl;
    comm->cout() << "  Size of DGM::Size = " << sizeof(DGM::Size) << endl;
    comm->cout() << "  Size of DGM::Ordinal = " << sizeof(DGM::Ordinal) << endl;
    comm->cout() << "  Size of DGM::Side::Info<Size,Ordinal,Scalar> = "
                 << sizeof(DGM::Side::Info<Size,Ordinal,Scalar>) << endl;
    comm->cout() << "  Size of DGM::Side::Info<Size,Ordinal,Scalar>::Ptr = "
                 << sizeof(DGM::Side::Info<Size,Ordinal,Scalar>::Ptr) << endl;
  }

  Ordinal p, q;
  p = params["p"];                     // polynomial order
  p += p_inc;                          // increment p if requested
  if ( !(q=params["q"]) ) q = p + 2;   // number of quadrature points
  nsd = params["nsd"];                 // number of space dimensions

  params["auxtec"] = 0;                // Compute derivative quantities
  params["plot3d_x"] = 1;              // plot3d grid file
  params["plot3d_q"] = 1;              // plot3d mesh file
  params.get("flux", "LaxFriedrichs");    // Numerical flux
  params.get("filter", false);            // Whether to filter solution

  // read arguments (overrides defaults and input file)
  parse_args( args );

  // Numerical fluxes
  string value = (string)params["flux"];
  if (lowerCase(value).compare("laxfriedrichs") == 0)
    flux = LaxFriedrichs;
  else
    comm->error("Reo::Maxwell::Unknown numerical flux");

  vector<string> field_names;          // Field names
  field_names.push_back("Hx");

  // build a Field of Elements and Sides
  if (params["imesh"]) {
    Mesh mesh(params);
    U.push_back( new Field(p, q, mesh, root, field_names[0],
                           Field::FULL, comm ) );
    partition = U[0]->partition;
  } else if (params["bmesh"]) {
    U.push_back( new Field(p, q, root, field_names[0], partition, 1,
                           Reo::NumEqntype, p2i(MAXWELL), comm ) );
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
    comm->error("Reo::Maxwell: number of space dimensions (nsd) must be 2");
  } else if (nsd == 2) {
    Nfields = NFIELDS;
    field_names.push_back("Hy");
    field_names.push_back("Ez");
  } else if (nsd == 3) {
    comm->error("Reo::Maxwell: nsd must be 2");
  } else {
    comm->cerr() << "Illegal value for nsd = " << nsd
                 << " in Reo::Maxwell::Maxwell" << endl;
    comm->exit(DGM::FAILURE);
  }

  // build the rest of the vector field
  for (vField::size_type i=1; i<Nfields; i++) {
    // comm->cout() << "Push back field " << field_names[i] << endl;
    U.push_back( new Field( U[0], root, field_names[i] ) );
  }

  // make auxiliary Fields using copy constructor
  for (vField::size_type i=0; i<Nfields; i++) {
    // comm->cout() << "Push back auxiliary field " << field_names[i] << endl;
    Ut.push_back( new Field( U[i], root, field_names[i] ) );
  }

  // optionally make storage contiguous
  if (json_domain["Space"]["Contiguous Memory Storage"].asBool()) {
    comm->cout() << "  Making U vField contiguous" << endl;
    U.reset_storage();
    Ut.reset_storage();
  }

  // set vField names
  U.set_name("U");
  Ut.set_name("Ut");

  // allocate workspace
  wk1.resize(5*max(Lmax(),Qmax()));
  wk2.resize(5*max(Lmax(),Qmax()));

  // make sure that storage is initialized
  CMC::Stopwatch timer;
  timer.start();
  zero_all_fields();
  if (verb)
    comm->cout() << "Zero fields in " << timer.restart() << " seconds" << endl;

  // make analysis object
  response = Response::factory(U, this);
  if (verb)
    comm->cout() << "Built Response in " << timer.restart()
                 << " seconds" << endl;

  setup_BCdb();            // setup BC database
  if (verb)
    comm->cout() << "Built BCs in " << timer.restart() << " seconds" << endl;

  setup_Sourcedb();        // setup Source term database
  if (verb)
    comm->cout() << "Built Sources in " << timer.restart()
                 << " seconds" << endl;

  timer.restart();
  set_TimeInt();
  if (verb) comm->cout() << "Built Time integrator in " << timer.restart()
                         << " seconds" << endl;

  if (verb) comm->cout() << "Completed Maxwell construction in " << cpu.stop()
                         << " seconds"<< endl;
}

/// Parse parameters from the argument list
void Maxwell::parse_args( DGM::ArgList &args ) {
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
      } else if (name == "-filter") {
        li.push_back(a);
        params["filter"] = true;
      } else if (name == "-flux") {
        li.push_back(a);
        value = *(++a);
        li.push_back(a);
        params["flux"] = value;
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

Maxwell::~Maxwell() {
  // delete heap storage here
}

void Maxwell::showUsage() {
  comm->cout()
    << "Reo::Maxwell Class Options \n"
    << "----------------------------------------------------------------\n"
    << "-nox     " << '\t' << "No grid file                             \n"
    << "-noq     " << '\t' << "No solution file                         \n"
    << "-aux     " << '\t' << "Auxiliary Tecplot file                   \n"
    << "-filter  " << '\t' << "Apply spectral filter                    \n"
    << "-flux    " << '\t' << "Numerical flux type                      \n"
    << "----------------------------------------------------------------\n";
}

void Maxwell::set_material() {
}

void Maxwell::time_derivative( vField &Us, vField &Uf ) {
  interior( Us, Uf );
  add_source( Us, Uf );
  project( Uf );
}

/// Evaluate the interior term
void Maxwell::interior( vField &Us, vField &Uf ) {
#ifdef DGM_TIME_MAXWELL
  static FunctionTimer T("Maxwell::interior");
  FunctionSentry sentry(T);
#endif
//Element *S[NFIELDS], *F[NFIELDS];
  Element *F[NFIELDS];

  Us.fill_sides();
  enforce_bc(Us);
  Us.begin_share_sides();

  // Add the interior contribution
  for (LocalSize e=0; e<Us[0]->ne; e++) {
//  S[0] = Us[0]->el[e]; // local version of the state
//  S[1] = Us[1]->el[e];
//  S[2] = Us[2]->el[e];

    F[0] = Uf[0]->el[e]; // local version of the flux
    F[1] = Uf[1]->el[e];
    F[2] = Uf[2]->el[e];

    // const Ordinal qtot = S[0]->qtot;

    // put volume terms here
    F[0]->u = zero;
    F[1]->u = zero;
    F[2]->u = zero;
  }
  Us.end_share_sides();
  surface( Us, Uf );
  for (LocalSize e=0; e<Us[0]->ne; e++) {
    for (vField::size_type n=0; n<Nfields; n++) {
      F[n] = Uf[n]->el[e];
      Us[n]->el[e]->lift( F[n], F[n]->u );
    }
  }
}

/// Evaluate the surface term
void Maxwell::surface(vField &Us, vField &Uf) {
#ifdef DGM_TIME_MAXWELL
  static FunctionTimer T("Maxwell::surface");
  FunctionSentry sentry(T);
#endif
  Scalar Fh[NFIELDS]; //, Gh[NFIELDS], Fpl[NFIELDS], Fmr[NFIELDS];

  vector<Side *> sl(Nfields), sr(Nfields);
  vector<Side *> fl(Nfields), fr(Nfields);

  for (LocalSize e=0; e<ne; ++e) {                // loop over elements
    Element *U = Us[0]->el[e];
    for (SideLoop S(U); !S.end(); ++S) {
      if (S.master_side()) {
        const Ordinal qtot = S.qtot();
        // localize the state and flux sides
        for (vField::size_type n=0; n<Nfields; ++n) {
          sl[n] = S.side(Us[n]->el[e]);           // left state side
          sr[n] = S.link(Us[n]->el[e]);           // right state side
          fl[n] = S.side(Uf[n]->el[e]);           // left flux side
          fr[n] = S.link(Uf[n]->el[e]);           // right flux side
        }
        for (Ordinal q=0; q<qtot; ++q) {          // loop over side quad-pts
          const Ordinal ql = U->sideMap(sl[0],q); // quadrature on the left
          const Ordinal qr = U->sideMap(sr[0],q); // quadrature on the left

          // const Scalar nxl = sl[0]->nx(ql);
          // const Scalar nyl = sl[0]->ny(ql);

          // compute real and numerical fluxes here
          sl[0]->u[ql] = zero;
          sl[1]->u[ql] = zero;
          sl[2]->u[ql] = zero;

          sr[0]->u[qr] = zero;
          sr[1]->u[qr] = zero;
          sr[2]->u[qr] = zero;

          Fh[0] = zero;
          Fh[1] = zero;
          Fh[2] = zero;

          // put fluxes on field sides
          for (vField::size_type n=0; n<Nfields; ++n) {
            sr[n]->u[qr] *= -one;        // correct for right normal
            fl[n]->u[ql]  =  Fh[n];      // upwind flux
            fr[n]->u[qr]  = -Fh[n];      // correct for right normal
          }
        }
      }
    }
  }
}

/// Generate plot output
int Maxwell::plot(const string &rst) {
  string fname, name(rst), caption;
  char buf[buflen];
  read( rst, U );
  const size_t loc = name.find(".rst");
  if ( loc != string::npos ) name.erase(loc);
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
    //compute_vorticity();
    sprintf(buf,"%s.aux.dat",name.c_str()); fname = buf;
    sprintf(buf,"Auxiliary variables at t =%11.4e, step = %lld",t,
            (long long)step);
    caption = buf;
    if (comm->Master()) Ut.tecplot(fname,caption);
  }
  return 0;
}

/** Compute the stable timestep. */
Scalar Maxwell::set_time_step(vField &U) {
  // cout << "Maxwell::set_time_step()" << endl;
  Scalar cfl = 0;
  // add computation of CFL condition here
  return cfl;
}

//===========================================================================
//                         Initial Condition
//===========================================================================

#define REO_MAXWELL_USE_JSON_IC

/// Set the initial condition
void Maxwell::set_ic(vField &F, string ext) {
  t = 0.0; step = 0;
  const string fname = root+ext;
#ifdef REO_MAXWELL_USE_JSON_IC
  ifstream in(fname.c_str());
  if (!in) {
    comm->cerr() << "DGM::IC Could not open initial condition file "
                 << fname << endl;
    comm->exit(DGM::FAILURE);
  }
  char c = in.peek();
  if (!in) throw DGM::exception("Cannot read Json header from "+fname);
  if (c!='{')
    throw DGM::exception("Cannot read Json header from "+fname+
                         " first character is not an open bracket:`{`");
  string token;
  if (!(in >> token))
    throw DGM::exception("Error reading Json header from "+fname);
  string buffer = read_block(in);
  const int status = scan_rb(in);
  if (status) comm->error("Could not find closing bracket for Json header "
                          " on file "+fname);
  Json::Reader reader;
  Json::Value value;
  bool parsingSuccessful = reader.parse(buffer, value, true);
  if (!parsingSuccessful)
    comm->error("IC could not parse input from "+
                fname+"\n"+reader.getFormattedErrorMessages());
  if (!value.isMember("Initial Condition"))
    comm->error("Initial Condition object is missing");
  if (!value["Initial Condition"].isObject())
    comm->error("Initial Condition must be a Json object");
  const int verb = value["Initial Condition"].set("Verbosity",0).asInt();
  if (verb) comm->cout()<<"Read IC types from "<<fname<<"\n"<<buffer<<endl;
  getline(in,buffer);
  IC::Ptr ic(IC::factory(value["Initial Condition"],*this,F));
#else
  IC::Ptr ic(IC::factory(fname,*this,F));
#endif
}

//===========================================================================
//                        BC database management
//===========================================================================

/// Load up the available BC types
void Maxwell::setup_BCdb( ) {
  // cout << "Maxwell::setup_BCdb()" << endl;
  // set default BC types
  dVector ub(Nfields);
  ub[0] = 0.0;
  ub[1] = 0.0;
  ub[2] = 0.0;
  BC_db["S"].reset( new StateBC("S", ub) );
  BC_db["W"].reset( new WallBC("W") );

  // read new BC types from file
  string fname = root+".bct";
  ifstream in(fname.c_str());
  if (in) Maxwell::read_BCdb( in );   // database of active BC types
}

void Maxwell::read_BCdb( ifstream &in ) {
  // cout << "Maxwell::read_BCdb( ifstream &in )" << endl;
  string tag;
  BC *pbc;
  while ( (pbc = Maxwell::make_BC(in,tag)) ) {
    if ( BC_db.find(tag) != BC_db.end() )
      comm->cerr() << "WARNING in Reo::Maxwell::read_BCdb() Overriding BC "
        "type \"" << tag << "\"." << endl;
    BC_db[tag].reset( pbc );
  }
}

/** \warning Is this really needed. */
BC* Maxwell::make_BC( ifstream &in, string &tag ) {
  // cout << "Maxwell::make_BC(ifstream &in, string &tag)" << endl;
  string code;
  if (!(in >> code)) return NULL;
  code = lowerCase(code);
  if (code == "state") {
    if (!(in >> tag)) error("Maxwell::make_BC: Cannot read State tag");
    return new StateBC(tag,in,4);
  } else if ( code.find("wall") != code.npos ) {
    if (!(in >>tag)) error("Maxwell::make_BC: Cannot read WallBC tag");
    return new WallBC(tag,in);
  } else {
    if(comm->Master())
      comm->cerr()<<"WARNING in Maxwell::make_BC() Illegal BC type: "+
      code<<endl;
  }
  return NULL;
}

//===========================================================================
//                        Source database management
//===========================================================================

/// Construct source terms
Source::Ptr Maxwell::make_Source( ifstream &in, string &tag ) {
  // cout << "Maxwell::make_Source" << endl;
  string code;
  Source::Ptr p;
  if (!(in >> code)) return p;
  while (code[0]=='#') {  // eat comment lines
    string buffer;
    getline(in,buffer);
    if (!(in >> code)) return p;
  }
  if (lowerCase(code) == "constant") {
    if (!(in >> tag)) error("Reo::Maxwell::Cannot read ConstSource tag",1);;
    p.reset( new ConstSource(tag,in,1) );
  } else {
    error("Reo::Maxwell::make_Source() Illegal Source type",1);
  }
  return p;
}

/// Add source terms
void Maxwell::add_source(const vField &Us, vField &Ur) {
  // cout << "Maxwell::add_source(vField &)" << endl;
  for (Source::db_citr i=Source_db.begin(); i!= Source_db.end(); ++i)
    // cout << "Adding source: " << i->first << endl;
    i->second->apply( t, Us, Ur);
}

//===========================================================================
//                             Output methods
//===========================================================================

/// Computes boundary statistics every time step
void Maxwell::write_bndry_stats() {
  static bool firsttime=true;
  if (firsttime) {
    comm->cout()<<"Maxwell::write_bndry_stats() not implemented"<<endl;
    firsttime=false;
  }
}

} // namespace Reo
