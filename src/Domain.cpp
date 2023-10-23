/*=============================================================================
  Module:     Domain base class

  Contact:    S. Scott Collis
              Computational Science and Mathematics
              sscoll@sandia.gov

  Copyright:  (c) 2003 Rice University
              (c) 2008 Sandia National Laboratories
=============================================================================*/

/** \file  Domain.cpp
    \brief Domain base class implementation.
    \author Scott Collis
*/

// system libraries
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <string>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <limits>
using namespace std;

// boost includes
#if defined(DGM_PARALLEL)
#include <boost/mpi.hpp>
#include <boost/mpi/environment.hpp>
#include <boost/mpi/communicator.hpp>
#include <boost/mpi/collectives.hpp>
#ifdef DGM_USE_GENERAL_GHOSTING
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/vector.hpp>
#include "boost/serialization/map.hpp"
#include "boost/serialization/string.hpp"
#include "boost/serialization/set.hpp"
#include "boost/archive/binary_iarchive.hpp"
#include "boost/archive/binary_oarchive.hpp"
#endif
#endif

/// Activate the DTK time integration capability
#define DGM_USE_TIMEINTEGRATE

// DTK includes
#ifdef DGM_USE_TIMEINTEGRATE
#include "DTK_TimeIntegrate.hpp"
#endif

// DGM libraries
#include "Domain.hpp"
#include "vField.hpp"
#include "vField.tpp"
#include "TimeInt.hpp"
#include "Trilinos.hpp"
#include "Utilities.hpp"
#include "Material.hpp"
#include "Operator.hpp"
#include "FieldSlice.hpp"
#include "Info.hpp"
#include "Partition.tpp"
#include "RuntimeControl.hpp"
#include "Color.hpp"

// JSON include
#ifdef DGM_USE_JSON
#include "json/json.h"
#endif

// Trilinos include
#ifdef DGM_USE_TRILINOS
#include "Trilinos_version.h"
#endif
#ifdef DGM_USE_EPETRA
#include "ml_LevelWrap.h"
#endif

#ifdef DGM_DOXYGEN
/// Define if the system does not support the strftime command
#define DGM_NO_TIME
#endif

namespace DGM {

namespace {

/// Local helper to parse Json input
Json::Value parse_json(const string &root, const DGM::Comm::Ptr comm) {
  Json::Value json;
  if (comm->Master()) {
    const string file = root + ".json";
    ifstream in(file.c_str());
    if (in) {
      Json::Reader reader;
      if (!reader.parse(in,json,true)) {
        throw DGM::exception("Failed to parse the json input file " + file +
                             ":  " + reader.getFormattedErrorMessages());
      }
    }
  }
  if (!json.isMember("Domain")) json["Domain"] = Json::Value();
  Json::broadcast(comm,json);
  return json;
}

#ifdef DGM_JSON_TO_TABLE

/// type for a hierarchical path
typedef std::vector<std::string> JSON_PATH;

/// type for DGM::Table to JSON::Value mapping
typedef std::map<std::string,JSON_PATH> TBL_TO_JSON;

TBL_TO_JSON & table_to_json_map() {
  using namespace std;
  static TBL_TO_JSON tbl_to_json;
  if (tbl_to_json.empty()) {
    JSON_PATH P(2);
#if !defined(DGM_INPUT_SPEC) || DGM_INPUT_SPEC == 1
    P[0] = "root";                                 tbl_to_json["root"]=P;
    P[0] = "IO";                                   tbl_to_json["IO"]=P;
    P[0] = "paraview";                             tbl_to_json["paraview"]=P;
    P[0] = "paraview_combined";                    tbl_to_json["paraview_combined"]=P;
    P[0] = "tecplot";                              tbl_to_json["tecplot"]=P;
    P[0] = "diagnostics";                          tbl_to_json["diagnostics"]=P;
    P[0] = "plot3d";                               tbl_to_json["plot3d"]=P;
    P[0] = "Space";
    P[1] = "bmesh";                                tbl_to_json["bmesh"]=P;
    P[1] = "contiguous";                           tbl_to_json["contiguous"]=P;
    P[1] = "p";                                    tbl_to_json["p"]    =P;
    P[1] = "q";                                    tbl_to_json["q"]    =P;
    P[1] = "imesh";                                tbl_to_json["imesh"]=P;
    P[1] = "nsd";                                  tbl_to_json["nsd"]=P;
    P[0] = "Time";
    P[1] = "Nt";                                   tbl_to_json["Nt"]   =P;
    P[1] = "Ntout";                                tbl_to_json["Ntout"]=P;
    P[1] = "ntout";                                tbl_to_json["ntout"]=P;
    P[1] = "dt";                                   tbl_to_json["dt"]   =P;
    P[1] = "inttype";                              tbl_to_json["inttype"]=P;
    P[1] = "ssiorder";                             tbl_to_json["ssiorder"]=P;
    P[1] = "CFLmax";                               tbl_to_json["CFLmax"]=P;
    P[1] = "Method";                               tbl_to_json["method"]=P;
    P[1] = "Integrator";                           tbl_to_json["integrator"]=P;
#elif DGM_INPUT_SPEC == 2
    // SSC:  This input specification is experimental and incomplete
    P[0] = "Space";
    P[1] = "Binary mesh";                          tbl_to_json["bmesh"]=P;
    P[1] = "Contiguous memory storage";            tbl_to_json["contiguous"]=P;
    P[1] = "Polynomial order";                     tbl_to_json["p"]    =P;
    P[1] = "Quadrature order";                     tbl_to_json["q"]    =P;
    P[0] = "Time";
    P[1] = "Number of time steps";                 tbl_to_json["Nt"]   =P;
    P[1] = "Interval between restart file output"; tbl_to_json["Ntout"]=P;
    P[1] = "Interval between minor info output";   tbl_to_json["ntout"]=P;
    P[1] = "Time step";                            tbl_to_json["dt"]   =P;
    P[1] = "Method";                               tbl_to_json["inttype"]=P;
    P[1] = "Substep interpolation order";          tbl_to_json["ssiorder"]=P;
    P[1] = "Integrator";                           tbl_to_json["integrator"]=P;
#endif
  }
  return tbl_to_json;
}

void enums_to_strings(Json::Value  &J) {
  string integrator = "DGM::TimeInt";
#ifdef DGM_USE_TIMEINTEGRATE
  if (J.isMember("Time") && J["Time"].isMember("Integrator")) {
    integrator = J["Time"]["Integrator"].asString();
  }
  if (integrator == "DTK::TimeIntegrate" &&
      J.isMember("Time") &&
      J["Time"].isMember("Method") &&
      J["Time"]["Method"].isInt()) {
    const int i = J["Time"]["Method"].asInt();
    const Domain::TimeIntegrate::IntType e =
        static_cast<Domain::TimeIntegrate::IntType>(i);
    const string n = Domain::TimeIntegrate::enumToName(e);
    J["Time"]["Method"] = n;
  }
#endif
  if (integrator == "DGM::TimeInt" &&
      J.isMember("Time") &&
      J["Time"].isMember("Method") &&
      J["Time"]["Method"].isInt()) {
    const int i = J["Time"]["Method"].asInt();
    const TimeInt::IntType e = static_cast<TimeInt::IntType>(i);
    const string n = TimeInt::enumToName(e);
    J["Time"]["Method"] = n;
  }
}

void strings_to_enums(Table  &T) {
  string integrator = "DGM::TimeInt";
#ifdef DGM_USE_TIMEINTEGRATE
  if (T.defined("Integrator"))
    integrator = static_cast<string>(T["Integrator"]);
  if (integrator == "DTK::TimeIntegrate" &&
      T.defined("Method")                &&
      T["Method"].isString()) {
    T["Method"] =
      Domain::TimeIntegrate::nameToEnum(static_cast<string>(T["Method"]));
  }
#endif
  if (integrator == "DGM::TimeInt" &&
      T.defined("inttype")         &&
      T["inttype"].isString()) {
    T["inttype"] =
      TimeInt::nameToEnum(static_cast<string>(T["inttype"]));
  }
}
#endif

}  // anonymous namespace

/// Domain constructor
/** This is an abstract Domain class that is used as a base class for
    specific problem types (Adv_Diff, Burgers, Euler, Navier_Stokes, etc.) */
Domain::Domain( DGM::ArgList &args_, const DGM::Comm::Ptr comm_) :
  args(args_), fieldslice("Field Slice"),
  comm(comm_), his(0), U(comm_,"U"), Ut(comm_,"Ut"),
  root(args.back()),
  json_root(parse_json(root, comm_)),
  json_domain(json_root["Domain"]),
  time_int(0), material(0),
  response(0), stats(0),
  CFL(0), compute_CFL(true), atime(0), ssiorder(-1), useRTC(false) {

  // get basic information from argument list
  code = args.front();
  if (args.size() < 2) showUsage();

  // set default values (this should really be moved elsewhere)
  params["imesh"] = false;      // do not use internal mesh
  params["bmesh"] = false;      // do not use parallel mesh
  params["inttype"] = 3;        // TVD-RK time integration
  params["p"] = 5;              // polynomial degree
  params["q"] = 0;              // quadrature points (0 = set internally)
  params["nsd"] = 1;            // number of space dimensions
  params["Nt"] = 100;           // number of time steps
  params["tf"] =  0.0;          // final time (0.0 = none)
  params["Ntout"] = 50;         // interval between restart file output
  params["ntout"] = 1;          // interval between minor info output
  params["dtmax"] = 0.0;        // Maximum allowable time step (0 means ignore)
  params["dt"] = 0.01;          // Time step
  params["ssiorder"] = -1;      // Substep interp order (-1 = no interpolation)
  params["root"] = root;        // root of the input file names
  params["CFLmax"] = 0.0;       // Maximum allowable CFL (0 means ignore)
  params["Ntprb"] = 10;         // Response probe output interval
  params["IO"] = true;          // True to use Domain IO (otherwise no IO)
  params["contiguous"] = false; // use contiguous vField for U
  params["useRTC"] = useRTC;    // whether to use RuntimeControl

  params["paraview"] = 0;       // Generate paraview files
  params["paraview_combined"] = 0;  // Generate paraview files, different format
  params["tecplot"] = 1;        // Generate tecplot files
  params["diagnostics"] = 0;    // Extra diagnostic files (e.g., tecplot 3D)
  params["plot3d"]  = 0;        // Generate plot3d files
  params["plot3d"]  = 0;        // Generate plot3d files

  // These should be in physics that support diffusion terms
  params["stab"] = 0.0;         // Diffusion stabilization
  params["bstab"] = 0.0;        // Boundary stabilization

  // These should not be here, but instead in the Fluid class
  params["gamma"] = 1.4;        // Ratio of specific heats, Cp/Cv (NS)
  params["vis"] = 0.0;          // viscosity coefficient
  params["Pr"]  = 0.72;         // Prandtl number (Air)

  // These should not be here, but instead in the Turbulence class
  params["cs"] = 0.0;           // Smagorinsky Coefficient
  params["delta2"] = 0.0;       // Model length scale
  params["turbtype"] = 0;       // Defaults to DNS
  params["filtype"] = 0;        // Filter type
  params["filfreq"] = 1;        // Filter frequency

  // set the run title
  title = "Discontinuous Galerkin Solver";

  // check to see if input file exists
  if (comm->Master()) {
    if (!params.exists(root+".inp"))
      cout << "WARNING:  using defaults as " << root+".inp" << " file does "
      "not exist" << endl;
  }

  // setup some initial JSON Domsin sub-blocks
  json_domain["Space"];
  json_domain["Time"];

  // read parameters from an input file
  params.read_all( root+".inp" );

#ifdef DGM_TABLE_USE_JSON
  // Debug:  output the parameter table
  comm->cout()<<params<<endl;
#endif

  // read command line arguments (overrides defaults and input file)
  parse_args( args );

#ifdef DGM_JSON_TO_TABLE
  // convert JSON parameters to parameter table
  params.convert(json_domain,table_to_json_map());
  if (params.defined("Integrator") &&
      params.defined("Method")     &&
      params["Integrator"] == "DTK::TimeIntegrate") {
    json_domain["Time"]["Method"] = static_cast<string>(params["Method"]);
  }
  enums_to_strings(json_domain);
  strings_to_enums(params);
#endif

  const int verb = json_domain.set("Verbosity",0).asInt();
  if (verb>1) {
    Json::StyledWriter writer;
    string output = writer.write(json_domain);
    comm->cout() << "Domain parameters:\n" << output;
  }
#if defined(DGM_TABLE_USE_JSON) && defined(DGM_USE_JSON)
  {
    json_root["Input"] = Json::Value();
    json_root["Input"]["Domain"] = Json::Value();
    params.convert(json_root["Input"]["Domain"]);
    Json::StyledWriter writer;
    string output = writer.write(json_root["Input"]);
    std::cout<<"DGM Domain parameters:\n" << output;
    ofstream fs("Domain-inp.json");
    fs<<output;
  }
#endif

  // initialize time stepping parameters
  step   = 0;
  t      = 0.0;
  dt     = params["dt"];
  dtmax  = params["dtmax"];
  Nt     = params["Nt"];
  Ntout  = params["Ntout"];
  ntout  = params["ntout"];
  tf     = params["tf"];
  ssiorder=params["ssiorder"];
  CFLmax = params["CFLmax"];
  stab   = params["stab"];
  bstab  = params["bstab"];
  Ntprb  = params["Ntprb"];
  IO     = params["IO"];
  useRTC = params["useRTC"];

  // Try new logic on tf
  if (tf!=0.0) {
    const Ordinal Ntf = numeric_cast<Ordinal>(floor(tf/dt));
    Nt = max(Ntf,Nt);
  }
}

/// destructor
Domain::~Domain() {
  if (verbosity()) comm->cout()<<"~DGM::Domain()"<<endl;
  if (response) delete response;
  if (stats) delete stats;
  if (time_int) delete time_int;
  //if (material) delete material;  // derived Domains must delete this
}

/// Parse some popular domain parameters from the argument list.
void Domain::parse_args( DGM::ArgList &args ) {
  string name, value;
  list< DGM::ArgList::iterator > li;
  for ( DGM::ArgList::iterator a = args.begin(); a != args.end(); a++ ) {
    if ( (*a)[0] == '-' ) {
      name = *a;
      if (name == "-p") {
        li.push_back(a);
        value = *(++a);
        li.push_back(a);
        params["p"] = atoi(value.c_str());
        json_domain["Space"]["p"] = atoi(value.c_str());
      } else if (name == "-q") {
        li.push_back(a);
        value = *(++a);
        li.push_back(a);
        params["q"] = atoi(value.c_str());
        json_domain["Space"]["q"] = atoi(value.c_str());
      } else if (name == "-dt") {
        li.push_back(a);
        value = *(++a);
        li.push_back(a);
        params["dt"] = atof(value.c_str());
        json_domain["Time"]["dt"] = atof(value.c_str());
      } else if (name == "-dtmax") {
        li.push_back(a);
        value = *(++a);
        li.push_back(a);
        params["dtmax"] = atof(value.c_str());
        json_domain["Time"]["dtmax"] = atof(value.c_str());
      } else if (name == "-CFLmax") {
        li.push_back(a);
        value = *(++a);
        li.push_back(a);
        params["CFLmax"] = atof(value.c_str());
        json_domain["Time"]["CFLmax"] = atof(value.c_str());
      } else if (name == "-Ntout") {
        li.push_back(a);
        value = *(++a);
        li.push_back(a);
        params["Ntout"] = atoi(value.c_str());
        json_domain["Time"]["Ntout"] = atoi(value.c_str());
      } else if (name == "-ntout") {
        li.push_back(a);
        value = *(++a);
        li.push_back(a);
        params["ntout"] = atoi(value.c_str());
        json_domain["Time"]["ntout"] = atoi(value.c_str());
      } else if (name == "-Nt") {
        li.push_back(a);
        value = *(++a);
        li.push_back(a);
        params["Nt"] = atoi(value.c_str());
        json_domain["Time"]["Nt"] = atoi(value.c_str());
      } else if (name == "-tf") {
        li.push_back(a);
        value = *(++a);
        li.push_back(a);
        params["tf"] = atof(value.c_str());
        json_domain["Time"]["tf"] = atof(value.c_str());
      } else if (name == "-inttype") {
        li.push_back(a);
        value = *(++a);
        li.push_back(a);
        params["inttype"] = atoi(value.c_str());
        const TimeInt::IntType j =
          static_cast<TimeInt::IntType>(atoi(value.c_str()));
        json_domain["Time"]["Method"] = TimeInt::enumToName(j);
      } else if (name == "-ssiorder") {
        li.push_back(a);
        value = *(++a);
        li.push_back(a);
        params["ssiorder"] = atoi(value.c_str());
        json_domain["Time"]["Substep interpolation order"] = atoi(value.c_str());
      } else if (name == "-method") {
        li.push_back(a);
        value = *(++a);
        li.push_back(a);
        const TimeIntegrate::IntType j =
          static_cast<TimeIntegrate::IntType>(atoi(value.c_str()));
        params["Method"] = TimeIntegrate::enumToName(j);
        json_domain["Time"]["Method"] = TimeIntegrate::enumToName(j);
#ifdef DGM_USE_TIMEINTEGRATE
      } else if (name == "-integrator") {
        li.push_back(a);
        value = *(++a);
        li.push_back(a);
        const int iflag = atoi(value.c_str());
        if (iflag == 0 ) {
          params["Integrator"] = "DGM::TimeInt";
          json_domain["Time"]["Integrator"] = "DGM::TimeInt";
        } else {
          params["Integrator"] = "DTK::TimeIntegrate";
          json_domain["Time"]["Integrator"] = "DTK::TimeIntegrate";
        }
#endif
      } else if (name == "-contiguous") {
        li.push_back(a);
        params["contiguous"] = true;
        json_domain["Space"]["Contiguous memory storage"] = true;
      } else if (name == "-stab") {
        li.push_back(a);
        value = *(++a);
        li.push_back(a);
        params["stab"] = atof(value.c_str());
      } else if (name == "-bstab") {
        li.push_back(a);
        value = *(++a);
        li.push_back(a);
        params["bstab"] = atof(value.c_str());
      } else if (name == "-vis") {
        li.push_back(a);
        value = *(++a);
        li.push_back(a);
        params["vis"] = atof(value.c_str());
      } else if (name == "-Ntprb") {
        li.push_back(a);
        value = *(++a);
        li.push_back(a);
        params["Ntprb"] = atoi(value.c_str());
      } else if ((name == "-noIO") || (name == "-no-rst")) {
        li.push_back(a);
        params["IO"] = false;
      } else if (name == "-bmesh") {
        li.push_back(a);
        value = *(++a);
        li.push_back(a);
        const int ivalue = atoi(value.c_str());
        params["bmesh"] = (bool)ivalue;
        json_domain["Space"]["bmesh"] = (bool)ivalue;
        json_domain["Space"]["Binary mesh"] = (bool)ivalue;
      } else if (name == "-p3d") {
        li.push_back(a);
        params["plot3d"] = 1;
      } else if (name == "-paraview") {
        li.push_back(a);
        params["paraview"] = 1;
      } else if (name == "-paraview_combined") {
        li.push_back(a);
        params["paraview_combined"] = 1;
      } else if (name == "-notec") {
        li.push_back(a);
        params["tecplot"] = 0;
      } else if (name == "-diagnostics") {
        li.push_back(a);
        params["diagnostics"] = 1;
      } else if (name == "-help") {
        params["showUsage"] = 1;
        showUsage();
      }
    }
  }
  // remove tagged arguments
#ifdef DGM_REMOVE_ARGUMENTS
  for ( list< DGM::ArgList::iterator >::iterator a=li.begin();
        a!=li.end(); a++) args.erase(*a);
#endif
}

/// command line argument usage
void Domain::showUsage() {
  comm->cout()
    << "DGM::Domain Class Options                                       \n";
  line(comm->cout(),'-',65);
  comm->cout()
    << "-p         " << '\t' << "Polynomial order                       \n"
    << "-q         " << '\t' << "Quadrature order                       \n"
    << "-inttype   " << '\t' << "Type for DGM::TimeInt                  \n"
    << "-method    " << '\t' << "Method for DTK::TimeIntegrate          \n"
#ifdef DGM_USE_TIMEINTEGRATE
    << "-integrator" << '\t' << "Time integrator (0=DGM::TimeInt, "
                                "1=DTK::TimeIntegrate) \n"
#endif
    << "-contiguous" << '\t' << "Use contiguous solution vField         \n"
    << "-dt        " << '\t' << "Time step                              \n"
    << "-CFLmax    " << '\t' << "Max allowable CFL                      \n"
    << "-dtmax     " << '\t' << "Max allowable time step (0=ignore)     \n"
    << "-Nt        " << '\t' << "Number of time steps                   \n"
    << "-Ntout     " << '\t' << "Restart file output interval           \n"
    << "-ntout     " << '\t' << "Minor information output interval      \n"
    << "-Ntprb     " << '\t' << "Response probe output interval         \n"
    << "-tf        " << '\t' << "Final time                             \n"
    << "-noIO      " << '\t' << "Turn off Domain restart-file IO        \n"
    << "-bmesh     " << '\t' << "Use binary mesh reader (root.grd,"
                                "root.cn) (0/1) \n"
    << "-notec     " << '\t' << "Do not generate Tecplot files          \n"
    << "-p3d       " << '\t' << "Generate Plot3d output files           \n"
    << "-paraview  " << '\t' << "Generate Paraview VTU files            \n"
    << "*************** The following are deprecated *******************\n"
    << "-vis       " << '\t' << "Diffusion coefficient                  \n"
    << "-stab      " << '\t' << "Diffusion stabilization parameter      \n"
    << "-bstab     " << '\t' << "Boundary stabilization parameter       \n";
  line(comm->cout(),'-',65);
}

void Domain::old_set_TimeInt(const int inttype) {
  switch(inttype) {
  case TimeInt::FORWARD_EULER: {
    time_int = new ForwardEuler( this );
    break; }
#ifdef DGM_USE_ITL
  case TimeInt::BACKWARD_EULER: {
    time_int = new BackwardEuler( this );
    break; }
#endif
  case TimeInt::MULTISTEP: {
    time_int = new Multistep( this );
    break; }
  case TimeInt::TVD_RK: {
    time_int = new TVD( this );
    break; }
  case TimeInt::RUNGE_KUTTA: {
    time_int = new RungeKutta( this );
    break; }
#ifdef DGM_USE_ITL
  case TimeInt::TRAPEZOIDAL: {
    time_int = new Trapezoidal( this );
    break; }
#endif
  case TimeInt::SSPRK: {
    time_int = new SSPRK( this );
    break; }
  case TimeInt::HALE_RK7: {
    time_int = new HALERK7( this );
    break; }
  case TimeInt::JAMESON: {
    time_int = new Jameson( this );
    break; }
  case TimeInt::HALE_RK67: {
    time_int = new HALERK67( this );
    break; }
  case TimeInt::LSRK14: {
    time_int = new LSRK14( this );
    break; }
#ifdef DGM_USE_EPETRA
  case DGM::Trilinos::BackwardEuler::id : {
    if (!U.is_contiguous()) make_contiguous();
    time_int = new DGM::Trilinos::BackwardEuler( this );
    break; }
  case DGM::Trilinos::Trapezoidal::id : {
    if (!U.is_contiguous()) make_contiguous();
    time_int = new DGM::Trilinos::Trapezoidal( this );
    break; }
#ifdef DGM_USE_RYTHMOS
  case DGM::Trilinos::Rythmos::id : {
    if (!U.is_contiguous()) make_contiguous();
    time_int = new DGM::Trilinos::Rythmos( this );
    break; }
#endif
#endif
  default:
#ifndef DGM_USE_TIMEINTEGRATE
    stringstream msg;
    msg << "Domain::set_TimeInt() Unsupported time integration type: "
        << inttype;
    comm->error(msg.str());
#endif
    break;
  }
}

/// setup the time integration method
void Domain::set_TimeInt( Ordinal ) {
#ifndef DGM_USE_TIMEINTEGRATE
  const int inttype = params["inttype"];
  old_set_TimeInt(inttype);
  comm->cout() << "Domain is using DGM::TimeInt with inttype = "
               << inttype << endl;
#else
  // If specified in the Json input file, use DTK time integration
  if (!json_domain.isMember("Time")) json_domain.set("Time",Json::objectValue);
  const string integrator =
      json_domain["Time"].set("Integrator","DGM::TimeInt").asString();
  const int verb = json_domain["Time"].get("Verbosity",0).asInt();
  if (integrator == "DTK::TimeIntegrate") {
    const string method = json_domain["Time"].set("Method","RK4").asString();
    comm->cout() << "Domain is using DTK::TimeIntegrate with "
                 << method << endl;
    if (method=="RK4" || method=="Runge Kutta")
      timeIntegrate.reset(new
          DTK::RungeKutta<Scalar,Ordinal,vField,Domain>(this));
    else if (method=="Multistep")
      timeIntegrate.reset( new
          DTK::Multistep<Scalar,Ordinal,vField,Domain>(this));
    else if (method=="ForwardEuler" || method=="Forward Euler")
      timeIntegrate.reset(new
          DTK::ForwardEuler<Scalar,Ordinal,vField,Domain>(this));
    else if (method=="TVD" || method=="TVD RK")
      timeIntegrate.reset(new
          DTK::TVD<Scalar,Ordinal,vField,Domain>(this));
    else if (method=="LeapFrog" || method=="Leap Frog")
      timeIntegrate.reset(new
          DTK::LeapFrog<Scalar,Ordinal,vField,Domain>(this));
    else if (method=="LSRK14")
      timeIntegrate.reset(new
          DTK::LSRK14<Scalar,Ordinal,vField,Domain>(this,verb));
    else if (method=="Nothing")
      timeIntegrate.reset(new
          DTK::Nothing<Scalar,Ordinal,vField,Domain>(this));
    else
      throw DGM::exception("Unsupported time integrator method "+method);
  } else if (integrator == "DGM::TimeInt") {
    // SSC:  currently experimenting with having Json override root.inp
#define DGM_DOMAIN_IGNORE_TIMEINT_METHOD
    int inttype(TimeInt::UNDEFINED);
    if (json_domain["Time"].isMember("Method")) {
#ifdef DGM_DOMAIN_IGNORE_TIMEINT_METHOD
      comm->cout()<<"Warning:  ignoring \"Method\" in JSON and using inttype "
                    "from root.inp"<<endl;
      inttype = params["inttype"];
#else
      inttype = TimeInt::nameToEnum(json_domain["Time"]["Method"].asString());
#endif
    } else {
      //comm->cout()<<"Warning:  no \"Method\" found in JSON so using inttype "
      //              "from root.inp"<<endl;
      inttype = params["inttype"];
    }
    old_set_TimeInt(inttype);
    comm->cout() << "Domain is using DGM::TimeInt with inttype = " << inttype
                 << " = " << TimeInt::enumToName(TimeInt::IntType(inttype))
                 << endl;
  } else {
    throw DGM::exception("Unsupported time integrator "+integrator);
  }
  if (ssiorder > 0) {
     comm->cout() << "Domain is using substep interpolation order " << ssiorder
                 << endl;
  }
  if (verb) {
    Json::StyledWriter writer;
    string output = writer.write(json_domain["Time"]);
    comm->cout() << "Domain Time parameters:\n" << output;
  }
#endif
}

// Return the number of substeps
Ordinal Domain::get_sstep() const {
  if (ssiorder < 0)
    if (timeIntegrate.get())
      return timeIntegrate->numsubstep();
    else if (time_int)
      return time_int->numsubstep();
    else
      throw DGM::exception("get_sstep called without time integrator defined");
  else
    return 1; // Interpolating
}

//===========================================================================
//                        BC database management
//===========================================================================

void Domain::clear_BCdb() {
  BC_db.clear();
}

/// Load up the available BC types
void Domain::setup_BCdb( ) {
  // cout << "Domain::setup_bc" << endl;
  string fname = root+".bct";
  ifstream in(fname.c_str());
  if (in) read_BCdb( in );   // database of active BC types
}

/// Read boundary conditions from a file
void Domain::read_BCdb( ifstream &in ) {
  // cout << "Domain::read_BCdb( ifstream &in )" << endl;
  string tag;
  BC *pbc;
  while ( (pbc = make_BC(in,tag)) ) {
    if ( BC_db.find(tag) != BC_db.end() )
      comm->cerr() << "Domain::read_BCdb:  Overriding BC type \""
                   << tag << "\"." << endl;
    BC_db[tag].reset( pbc );
  }
}

// Construct boundary conditions
BC* Domain::make_BC( ifstream &in, string &tag ) {
  // cout << "Domain::make_bc" << endl;
  if (!(in >> code)) return 0;
  if (lowerCase(code) == "state") {
    if (!(in >> tag)) comm->error("Domain::Cannot read State tag");
    return new StateBC(tag,in);
  } else {
    comm->error("Domain::make_BC:  Illegal BC type");
  }
  return 0;
}

/// loop over all boundary sides to check, if their type is in the BC database
void Domain::verifyBCs(const vField &F) const {
  for (vField::size_type ifield=0; ifield<F.size(); ++ifield) {
    for (LocalSize ibc=0; ibc<F[ifield]->nbc; ++ibc) {
      const string& tag = F[ifield]->bc[ibc]->type;
      BC::db_citr it = BC_db.find(tag);
      if ( it == BC_db.end() ) {
        const Side *const S = F[ifield]->bc[ibc]->S;
        comm->cout() << "The following side has a BC named '"<< tag
                     << "' applied that is not in BC_db. "
                     << "This is an fatal error!" << endl;
        comm->cout() << *S << endl;
        comm->error("Domain::verifyBCs:  Wrong input!");
      }
    }
  }
}

//===========================================================================
//                        Source database management
//===========================================================================

void Domain::clear_Sourcedb() {
  Source_db.clear();
}

/// Load up the available Source types
void Domain::setup_Sourcedb( ) {
  if (verbosity()>1) comm->cout() << "Domain::setup_Sourcedb" << endl;
  string fname = root+".src";
  ifstream in(fname.c_str());
  if (in) read_Sourcedb( in );   // database of active Source types
}

/// Read source terms from a file
void Domain::read_Sourcedb( ifstream &in ) {
  if (verbosity()>1)
    comm->cout() << "Domain::read_Sourcedb( ifstream &in )" << endl;
  string tag;
  Source::Ptr psrc;
#ifdef DGM_USE_TEUCHOS_RCP
  while ( (psrc = make_Source(in,tag)).get() ) {
#else
  while ( (psrc = make_Source(in,tag)) ) {
#endif
    if ( Source_db.find(tag) != Source_db.end() )
      comm->cerr() << "Domain::read_Sourcedb:  Overriding Source type \""
                   << tag << "\"." << endl;
    Source_db[tag] = psrc;
    tag.clear();
  }
  vector<pair<string,Source::Ptr> > sources;
  make_Source(sources);
  for (size_t i=0; i<sources.size(); ++i) {
    tag  = sources[i].first;
    psrc = sources[i].second;
    if ( Source_db.find(tag) != Source_db.end() )
      comm->cerr() << "Domain::read_Sourcedb:  Overriding Source type \""
                   << tag << "\"." << endl;
    Source_db[tag] = psrc;
  }
}

/// Construct source terms
Source::Ptr Domain::make_Source( ifstream &in, string &tag ) {
  if (verbosity()>1) comm->cout() << "Domain::make_Source " << tag << endl;
  string code;
  Source::Ptr p;
  if (!(in >> code)) return p;
  while (code[0]=='#') {  // eat comment lines
    string buffer;
    getline(in,buffer);
    if (!(in >> code)) return p;
  }
  if (lowerCase(code) == "constant") {
    if (!(in >> tag)) comm->error("Domain::Cannot read ConstSource tag");
    p.reset(new ConstSource(tag,in));
  } else {
    comm->error("Domain::make_Source:  Illegal Source type");
  }
  return p;
}

/** \note SSC:  I don't understand the purpose of this as I don't think
    that "Sources" can be a member of the json_root */
void Domain::make_Source(vector<pair<string,Source::Ptr> > &sources) {
  if (json_root.isMember("Sources")) {
    Json::Value sjson = json_root["Sources"];
    if  (!sjson.isArray())
      comm->error("Domain::make_Source: "
                  "'Sources' is not an ARRAY of source blocks "
                  " (in square brackets).");
    const Ordinal num_src = sjson.size();
    if (!num_src)
     comm->error("Domain::make_Source: "
                 "'sources' is a zero length array.");
    sources.resize(num_src);
    unsigned n=0;
    for (Json::ValueIterator s_iter = sjson.begin();
         s_iter != sjson.end(); ++s_iter, ++n ) {
      Json::Value &s_param = *s_iter;
      if (!s_param.isMember("Type"))
        comm->error("Domain::Cannot read 'Type' parameter in Source array");

      const string code = s_param["Type"].asString();
      const string tag  = s_iter.key().asString();

      if (lowerCase(code) == "constant") {
        sources[n].first = tag;
        sources[n].second.reset(new ConstSource(tag,s_param));
      } else {
        comm->error("Domain::make_Source:  Illegal Source type");
      }
    }
  }
}

//===========================================================================
//                        Basic Domain Solver
//===========================================================================

/// Solve the equations for this Domain
int Domain::solve() {
  static Color bold(Color::BOLD);
  static Color red(Color::RED);
  static Color green(Color::GREEN);
  static Color def(Color::DEFAULT);

  if(verbosity()>2) comm->cout() << "Domain::solve()..." << endl;
  enum Status { Normal=0, Restart=1, Redo=2 };
  static Format sci_lo(4,10,'e');
  static Format sci(4,12,'e');
  Status status = Normal;
  if (comm->Master()) {
    string fname = root+".his";
    history.open(fname.c_str(), ios::app);
  }
  set_ic(U);
  if (step==0) {
    write(step,U);
    response->probe( U, root, t, false );
  }
  fieldslice.initialize(U[0]);
#ifndef DGM_PARALLEL
  char buffer[buflen];
  string caption;
  sprintf(buffer,"Initial condition at t = %11.4e, step = %lld",
          t,(long long)step);
  caption = buffer;
  if (nsd<3 || params["diagnostics"]) U.tecplot("ic.dat",caption);
#endif
  Stopwatch wall; wall.start();
  string timestamp = comm->dateTime();
  comm->cout() << "Starting solve on " << timestamp << endl;
  comm->cout() << "Advancing solution " << Nt << " time steps" << endl;
  Scalar ctime=0, stime=0, ttime=0;
  int cnt=0;
  RuntimeControl rtc(root,Nt,Ntout,ntout);
#ifdef DGM_USE_JOBSTATUS
  JobStatus job(60);                // job status object, tolerance 60 seconds
#endif
  prepareToAdvance();
  Stopwatch cpu; cpu.start();
  wallTime.start();
  comm->cout()<<"    Step      t           dt         CFL         dCPU\n";
  compute_CFL = true;
  for (lstep=1; lstep<=Nt; lstep++) {
    if (useRTC && lstep%ntout==0) rtc.check();
    if (useRTC && rtc.restart()) break;
    step++;
    CFL = set_time_step(U);
    if (timeIntegrate.get()) {
      timeIntegrate->advance(this);
    } else {
      time_int->advance(this);
    }
    ctime = cpu.restart();
    if (lstep>1) { ttime += ctime; stime += ctime*ctime; cnt++; }
    if ((lstep%ntout==0) || (lstep==Nt))
      comm->cout()<<setw(8)<<step<<sci(t)<<sci(dt)<<sci(CFL)<<sci(ctime)<<endl;
    if (comm->Master())
      history<<setw(8)<<step<<sci(t)<<sci(dt)<<sci(CFL)<<sci(ctime)<<'\n';
    if (Ntout==0 || step%Ntout==0)  {
      write(step, U);
      U.norm();
      cpu.restart();
    }
    write_bndry_stats();
    if (stats) stats->write();
    if (step%Ntprb==0) response->probe( U, root, t, lstep==Nt );
    this->output_slices();
#ifdef DGM_USE_JOBSTATUS
    // this slows down the code a little
    if ( ((t >= tf) && (tf > 0)) || job.finished() ) break;
#endif
    comm->Barrier();
  }
  timestamp = comm->dateTime();
  comm->cout() << green << "Finished solve on " << timestamp << " in "
               << sci_lo(wall.stop()) << " sec" << def << endl;
  if (useRTC) {
    if (rtc.restart())
      status = Redo;
    else if (t < tf)
      status = Restart;
  }
  Scalar otime=0, xtime=0, ntime=0;
  comm->SumAll( &ttime, &atime, 1 );  // average cpu time
  comm->SumAll( &stime, &otime, 1 );  // standard deviation of the cpu time
  comm->MaxAll( &ttime, &xtime, 1 ); 
  comm->MinAll( &ttime, &ntime, 1 ); 
  const int nproc = max(1,cnt*comm->NumProc());
  atime /= nproc; otime /= nproc; xtime /= max(1,cnt); ntime /= max(1,cnt);
  const Scalar stdev = ::sqrt(otime - atime*atime);
  comm->cout() << "Average CPU time per step:" << sci(atime)
               << " standard deviation:" << sci(stdev) 
#ifdef DGM_PARALLEL
               << "\n          minimum average:" << sci(ntime) 
               << "    maximum average:" << sci(xtime) 
#endif
               << endl;
  write(root+".rst", U);
  if (Ntout==0 || step%Ntout!=0) U.norm();
#ifndef DGM_PARALLEL
  sprintf(buffer,"Solution at t = %11.4e, step = %lld",t,(long long)step);
  caption = buffer;
  if (nsd<3 || params["diagnostics"]) U.tecplot("out.dat",caption);
#endif
  if (Ntout==0 || step%Ntout!=0) write_bndry_stats();
  char tmp[buflen];
  for (vField::size_type n=0; n<Nfields; ++n) {
    sprintf(tmp,".%lld",(long long)step);
    string filename = root + tmp + "." + U[n]->name + ".rak";
    response->output( U[n], filename );
  }
  comm->Barrier();
  return status;
}

int Domain::diff(const string &rst1, const string &rst2,
                 const Scalar aeps, const Scalar reps, const Scalar meps)
{
  using std::isnan;
  int status(0);
  static int LINF_FAILED(0x01);
  static int L2_FAILED(0x02);
  static int H1_FAILED(0x04);
  static int LINF_REL_FAILED(0x08);
  static int L2_REL_FAILED(0x010);
  static int H1_REL_FAILED(0x020);
  static Format sci(10,18,'e');
  dVector rLinf, rL2, rH1;
  dVector mLinf, mL2, mH1;
  read( rst1, U );
  U.norm(rLinf, rL2, rH1);
  read( rst2, Ut );
  U.relative_max_error(Ut, mLinf, mL2, mH1);
  axpy( -one, Ut, U);  //  U = U - Ut
  dVector Linf, L2, H1;
  U.norm(Linf, L2, H1);
  //U.tecplot(root+".diff.dat","Difference");
  write(root+".diff.rst",U);  // output a restart file of the difference
  if (aeps >= 0 && meps == 0) {
    comm->cout()<<"Absolute Tolerance:  aeps = "<<aeps<<endl;
    for (vField::size_type i=0; i<U.size(); i++) {
      comm->cout()<<"Field: "<<setw(5)<<U[i]->name<<sci(Linf[i])
                          <<sci(L2[i])<<sci(H1[i])
                          <<" (Linf L2 H1)"<<endl;
      if (Linf[i]>aeps || isnan(Linf[i])) status |= LINF_FAILED;
      if (L2[i]>aeps || isnan(L2[i])) status |= L2_FAILED;
      if (H1[i]>aeps || isnan(H1[i])) status |= H1_FAILED;
    }
  }
  if (reps >= 0 && meps == 0) {
    comm->cout()<<"Relative Tolerance:  reps = "<<reps<<endl;
    for (vField::size_type i=0; i<U.size(); i++) {
      comm->cout()<<"Field: "<<setw(5)<<U[i]->name;
      if (rLinf[i]>repsM || isnan(rLinf[i])) {
        if (Linf[i]/rLinf[i]>reps ||
            isnan(Linf[i]/rLinf[i])) status |= LINF_REL_FAILED;
        comm->cout() << sci(Linf[i]/rLinf[i]);
      } else
        comm->cout() << sci(Linf[i]);
      if (rL2[i]>repsM || isnan(rL2[i])) {
        if (L2[i]/rL2[i]>reps ||
            isnan(L2[i]/rL2[i])) status |= L2_REL_FAILED;
        comm->cout() << sci(L2[i]/rL2[i]);
      } else
        comm->cout() << sci(L2[i]);
      if (rH1[i]>repsM || isnan(rH1[i])) {
        if (H1[i]/rH1[i]>reps ||
            isnan(H1[i]/rH1[i])) status |= H1_REL_FAILED;
        comm->cout() << sci(H1[i]/rH1[i]);
      } else
        comm->cout() << sci(H1[i]);
      comm->cout() <<" (Linf L2 H1)"<<endl;
    }
  }
  if (meps > 0) {
    comm->cout()<<"Maximum Element Relative Tolerance:  meps = "<<meps<<endl;
    for (vField::size_type i=0; i<U.size(); ++i) {
      comm->cout()<<"Field: "<<setw(5)<<U[i]->name;
      if (mL2[i]>repsM || isnan(mL2[i]) || mL2[i]>meps) 
        status |= L2_REL_FAILED;
      comm->cout() << sci(mL2[i]);
      comm->cout() <<endl;
    }
  }
  if (aeps < 0 && reps < 0) comm->error("Domain::diff() No tests requested");
  return status;
}

/// Zero all the Fields in the Domain
void Domain::zero_all_fields() {
  U.zero(); Ut.zero();
}

/// Make all Fields contiguous in this Domain
void Domain::make_contiguous() {
  U.reset_storage();
  Ut.reset_storage();
}

/// Anonymous namespace
namespace {

  /// Helper for making a final name
  const char *makename(const string &root,const string &s,
                       const Ordinal iter, const Ordinal istep,
                       const Ordinal sstep) {
    static char buf[132];
    if(iter) {
      if(sstep==0)
        if (s.empty())
          sprintf(buf,"%s.%lld_%lld.rst",root.c_str(),(long long)istep,
                  (long long)iter);
        else
          sprintf(buf,"%s.%s.%lld_%lld.rst",root.c_str(),s.c_str(),
                  (long long)istep,(long long)iter);
      else
        if (s.empty())
          sprintf(buf,"%s.%lld.%lld_%lld.rst",root.c_str(),(long long)istep,
                  (long long)sstep,(long long)iter);
        else
          sprintf(buf,"%s.%s.%lld.%lld_%lld.rst",root.c_str(),s.c_str(),
                  (long long)istep,
                  (long long)sstep,(long long)iter);
    } else {
      if(sstep==0)
        if (s.empty())
          sprintf(buf,"%s.%lld.rst",root.c_str(),(long long)istep);
        else
          sprintf(buf,"%s.%s.%lld.rst",root.c_str(),s.c_str(),
                  (long long)istep);
      else
        if (s.empty())
          sprintf(buf,"%s.%lld.%lld.rst",root.c_str(),(long long)istep,
                  (long long)sstep);
        else
          sprintf(buf,"%s.%s.%lld.%lld.rst",root.c_str(),s.c_str(),
                  (long long)istep,(long long)sstep);
    }
    return buf;
  }

}  // end anonymous namespace

std::string Domain::mkname( const std::string &path, const Ordinal iter,
                            const Ordinal istep, const Ordinal sstep) const {
  string s, fname = path;
#ifdef DGM_PARALLEL
  char node[80];
  sprintf(node,"%lld",(long long)get_comm()->MyPID());
  fname += node;
#endif
  fname +=  "/";
  fname += makename(root,s,iter,istep,sstep);
  // cout << "Domain::mkname " << fname << endl;
  return fname;
}

std::string Domain::mkname( const Ordinal iter, const Ordinal istep,
                            const Ordinal sstep, const std::string &s) const {
  const string fname = get_comm()->Scratch() +
                       makename(root,s,iter,istep,sstep);
  return fname;
}

/// Read a restart file from fname
void Domain::read(const std::string &fname, vField &F, const HeaderType ht) {
  if (!IO) return;
  if(verbosity()>1) {
    comm->cout() << "Domain::read("<<fname<<")...";
    if(verbosity()>2)
      comm->cout() << endl;
    else
      comm->cout().flush();
  }
  Json::Value header;
  const streamoff disp = (ht==SKIP_HEADER) ? skip_header(header, fname, F )
                                           : read_header(header, fname, F );
  if (header.isMember("Types")) header = header["Types"];
  const string global_size = header["GlobalSize"].asString();
  const string local_size  = header["LocalSize"].asString();
  const string scalar_size = header["Scalar"].asString();

  F.read(fname, global_size, local_size, scalar_size, disp );
}

/// Read a restart file from root.ver.rst
/** \param[in]     ver version number
    \param[in,out] F   Field to read data into. */
void Domain::read(const Ordinal ver, vField &F) {
  ostringstream fname;
  fname << root << "." << ver << ".rst";
  read( fname.str(), F );
}

/// Read a restart file from fname
void Domain::read_field(const string &fname, vField &F) const {
  if (!IO) return;
  Json::Value header;
  const streamoff disp =  skip_header(header, fname, F );

  const string global_size = header["Types"]["GlobalSize"].asString();
  const string local_size  = header["Types"]["LocalSize"].asString();
  const string scalar_size = header["Types"]["Scalar"].asString();

  F.read(fname,  global_size, local_size, scalar_size, disp);
}

/// Read a restart file from fname
void Domain::local_read(const std::string &fname, vField &F,
                        const HeaderType ht, const bool saved_as_float) {
  Json::Value header;
  const streamoff disp = (ht==SKIP_HEADER) ? skip_header(header,fname, F)
                                           : read_header(header,fname, F);
  F.local_read( fname, disp, saved_as_float );
}

/// Read a restart file from an input file stream
void Domain::local_read(istream &fs, vField &F, const std::string &fname,
                        const HeaderType ht, const bool saved_as_float) {
  Json::Value header;
  if (ht == SKIP_HEADER) {
    skip_header(header, fs, fname, F );
  } else {
    read_header(header, fs, F, fname );
  }
  F.local_read( fs, saved_as_float );
}

/// Return whether the local file exists
bool Domain::local_exists(const string &fname, const vField &F) const {
  return F.local_exists(fname);
}

/// Read a restart file from fname (skipping header)
void Domain::local_read_field(const std::string &fname, vField &F) const {
  Json::Value header;
  const streamoff disp =  skip_header(header, fname, F);
  F.local_read( fname, disp );
}

/// Write a restart file to fname
void Domain::write(const std::string &fname, const vField &F) const {
  if (!IO) return;
  Stopwatch cpu; cpu.start();
  if(verbosity()>1) {
    comm->cout() << "Domain::write("<<fname<<")...";
    if(verbosity()>2)
      comm->cout() << endl;
    else
      comm->cout().flush();
  }
  F.write( fname, write_header( fname, F ) );
  if(verbosity()>1) {
    if (verbosity()>2)
      comm->cout() << "Domain::write("<<fname<<") ";
    comm->cout() << "completed in " << cpu.stop() << " seconds." << endl;
  }
}

/// Write a restart file to root.ver.rst
/** \param[in] ver version number
    \param[in] F   Field to read data into. */
void Domain::write(const Ordinal ver, const vField &F) const {
  ostringstream fname;
  fname << root << "." << ver << ".rst";
  write( fname.str(), F );
}

/// Write a restart file to fname
void Domain::local_write(const std::string &fname, const vField &F,
                         const bool save_as_float) const {
  F.local_write( fname, write_header( fname, F, true ), save_as_float );
}

/// Write a restart file to an output stream
void Domain::local_write(ostream &fs, const vField &F,
                         const std::string &fname,
                         const bool save_as_float) const {
  write_header ( fs, F, fname );
  F.local_write( fs, save_as_float );
}

//=============================================================================
//                    Local I/O with compression
//=============================================================================

/// Read a restart file from fname
void Domain::comp_read(const std::string &fname, vField &F,
                       const HeaderType ht, const Json::Value &traits) {
  Json::Value header;
  const streamoff disp = (ht==SKIP_HEADER) ? skip_header(header,fname, F)
                                           : read_header(header,fname, F);
  ifstream fs(fname.c_str());
  fs.seekg(disp);
  if (traits["Save as single precision"].asBool())
    F.compressed_local_read<float>(fs,traits);
  else
    F.compressed_local_read<Scalar>(fs,traits);
}

/// Read a restart file from an input file stream
void Domain::comp_read(istream &fs, vField &F, const std::string &fname,
                        const HeaderType ht, const Json::Value &traits) {
  Json::Value header;
  if (ht == SKIP_HEADER) {
    skip_header(header, fs, fname, F );
  } else {
    read_header(header, fs, F, fname );
  }
  if (traits["Save as single precision"].asBool())
    F.compressed_local_read<float>(fs,traits);
  else
    F.compressed_local_read<Scalar>(fs,traits);
}
/// Write a restart file to fname using compression
void Domain::comp_write(const std::string &fname, const vField &F,
                        const Json::Value &traits) const {
  // might be a good idea to update the header information with the scalar
  // type and the compression status
  write_header(fname, F, true);
  ofstream fs(fname.c_str(), ios::app);
  if (traits["Save as single precision"].asBool())
    F.compressed_local_write<float>(fs,traits);
  else
    F.compressed_local_write<Scalar>(fs,traits);
}

/// Write a restart file to an output stream using compression
void Domain::comp_write(ostream &fs, const vField &F,
                         const std::string &fname,
                         const Json::Value &traits) const {
  // might be a good idea to update the header information with the scalar
  // type and the compression status
  write_header(fs, F, fname);
  if (traits["Save as single precision"].asBool())
    F.compressed_local_write<float>(fs,traits);
  else
    F.compressed_local_write<Scalar>(fs,traits);
}

//=============================================================================

/// Output the boundary statistics for primary field U
void Domain::write_bndry_stats() {
  //cout<<"Domain::write_bndry_stats()"<<endl;
  if (!U[0]->bndry_stats->valid) return;
  if (Ntout==0 || step%Ntout==0) U.write_side_stats(step);
}

/// Not implemented
void Domain::compute_stats(const string &) {
  cout << "Domain::compute_stats is not implemented." << endl;
}

/// Not implemented
void Domain::plot_stats(const int) {
  cout << "Domain::plot_stats is not implemented." << endl;
}

/** Default implementation just iterates over the BC database
    \warning Overriding this method is deprecated. */
void Domain::enforce_bc(vField &F) {
  // cout << "Domain::enforce_bc(vField &F) "<< lstep << endl;
  for (BC::db_citr i=BC_db.begin(); i!= BC_db.end(); ++i)
    i->second->apply( t, F );
}

/** Default implementation just iterates over the BC database
    \warning Overriding this method is deprecated. */
void Domain::enforce_flux_bc(vField &F) {
  for (BC::db_citr i=BC_db.begin(); i!= BC_db.end(); ++i) {
    i->second->apply_flux( t, F );
  }
}

/// If defined, find time on the Master and broadcast to other ranks
#define DGM_BROADCAST_TIME

//=============================================================================
//                          JSON Header Support
//=============================================================================

/// Read a Json header
streamoff Domain::read_json_header(Json::Value &header,
                                   istream &fs,
                                   const vField &F,
                                   const string &fname) const {
  if(verbosity()>2)
    comm->cout()<<"Domain::read_json_header("<<fname<<")"<<endl;
  char c = fs.peek();
  if (!fs) throw DGM::exception("Cannot read Json header from "+fname);
  if (c!='{') {
    throw DGM::exception("Cannot read Json header from "+fname+
                         " first character is not an open bracket:`{`");
  }
  string token;
  if (!(fs >> token))
    throw DGM::exception("Error reading Json header from "+fname);

  string buffer = read_block(fs);
  const int status = scan_rb(fs);
  if (status) comm->error("Could not find closing bracket for Json header "
                          " on file "+fname);
  //cout << "Read header from " << fname << "\n" << buffer << endl;
  Json::Reader reader;
  bool parsingSuccessful = reader.parse( buffer, header, true );
  if (!parsingSuccessful)
    comm->error("Domain::read_json_header could not parse input from "+
                fname+"\n"+reader.getFormattedErrorMessages());
  getline(fs,buffer);
  if (fs.fail())
    throw DGM::exception("Could not read Json data from file "+fname);
  if (fs.bad())
    throw DGM::exception("Stream is bad when reading Json data "
                         "from file "+fname);
  if (fs.eof())
    throw DGM::exception("End of file encountered when reading from "+fname);

  if (!header.isMember("Nel"))
    throw DGM::exception("Header is missing Nel from file "+fname);
  if (header["Nel"].asUInt64() != numeric_cast<uint64_t>(F[0]->gne))
    throw DGM::exception("Header for file "+fname+" has the wrong number of\n"
                         "  elements.  Should be "+asString(F[0]->gne)+
                         " but is "+asString(header["Nel"].asUInt64())+".\n"
                         "  "+fname+" possibly left over from previous run?");
  if (!header.isMember("Nsd"))
    throw DGM::exception("Header is missing Nsd from file "+fname);
  if (header["Nsd"].asInt() != numeric_cast<int>(F[0]->nsd()))
    throw DGM::exception("Header for file "+fname+" has the wrong number of\n"
                         "spatial dimensions. Should be "+asString(F[0]->nsd())+
                         " but is "+asString(header["Nsd"].asUInt64())+".\n"
                         "  "+fname+" possibly left over from previous run?");
  if (!header.isMember("Step"))
    throw DGM::exception("Header is missing Step from file "+fname);
  if (!header.isMember("Time"))
    throw DGM::exception("Header is missing Time from file "+fname);
  if (!header.isMember("Basis type"))
    throw DGM::exception("Header is missing \"Basis type\" from file "+fname);
  string format = header["Basis type"].asString();
#ifdef DGM_BASIS_NORM
  if (lowerCase(format)!="normalized")
    comm->error("Only normalized Basis type is accepted.\n"
                "Basis type = " + format);
#else
  if (lowerCase(format)!="unnormalized")
    comm->error("Only unnormalized Basis type is accepted.\n"
                "Basis type = " + format);
#endif
  // Types block
  // Allow for both a Types block and types in main header
  const Json::Value &types =
    header.isMember("Types") ?  header["Types"] : header;
#if 1
  // Turn off some error checking so that we can read more files
  if (!types.isMember("GlobalSize"))
    throw DGM::exception("Header is missing \"GlobalSize\""
                         " from file "+fname);
  if (types["GlobalSize"].asString() == "unknown")
    throw DGM::exception("Domain restart file "+fname+" is incompatible: "
                         "GlobalSize = "+types["GlobalSize"].asString()+
                         "\n  while code expects "+type<DGM::Size>());
  if (!types.isMember("LocalSize"))
    throw DGM::exception("Header is missing \"LocalSize\""
                         " from file "+fname);
#endif
  if (!types.isMember("Scalar"))
    throw DGM::exception("Header is missing \"Scalar\""
                         " from file "+fname);
  if (types.isMember("ByteOrder")) {
    DGM::ByteOrder byteOrder;
    if (!byteOrder.is(types["ByteOrder"].asString())) {
      throw DGM::exception("Domain restart file "+fname+" is incompatible: "
                           "ByteOrder = "+types["ByteOrder"].asString()+
                           "\n  while code expects "+byteOrder.asString());
    }
  }
  // Get the cumulative wall time
  if (!header.isMember("Wall time"))
    wallTime.reset();
  else
    wallTime.reset(header["Wall time"].asDouble());
  streamoff disp = fs.tellg();   // get the header length (in bytes)
  if (verbosity()>2) comm->cout() << "Domain::read_json_header("<<fname
                                  <<") with displacement = " << disp << endl;
  return disp;
}

/// Write a Json header
streamoff Domain::write_json_header(ostream &fs,
                                    const vField &F,
                                    const string &fname,
                                    const bool all) const {
  if(verbosity()>2)
    comm->cout()<<"Domain::write_json_header("<<fname<<")"<<endl;
  streamoff disp=0;
  char now[buflen] = "Time is not available";
#if !defined(DGM_REDSTORM) && !defined(DGM_NO_TIME)
#ifdef DGM_BROADCAST_TIME
   // Only get the time from rank 0 and broadcast
  if (comm->Master()) {
    // get the current date and time from <time.h>
    time_t tp = ::time(0);
    strftime(now,buflen,"%a %b %d %H:%M:%S %Y", localtime(&tp));
  }
  if (all) comm->Broadcast(now, buflen);
#else
  // all ranks get the current date and time from <time.h>
  time_t tp = ::time(0);
  strftime(now,buflen,"%a %b %d %H:%M:%S %Y", localtime(&tp));
#endif
#endif
  Json::Value header;
  header["DGM library"] = Json::Value(Json::objectValue);
  header["DGM library"]["Version"] = DGM::Comm::information.version();
  header["DGM library"]["Build date"] = DGM::Comm::information.date();
  header["DGM library"]["Build time"] = DGM::Comm::information.time();
  header["DGM library"]["Compiler"] = DGM::Comm::information.compiler();
  header["DGM library"]["Host name"] = DGM::Comm::information.hostname();
  header["DGM library"]["System"] = DGM::Comm::information.system();
#ifdef DGM_USE_TRILINOS
  header["DGM library"]["Trilinos"] = TRILINOS_VERSION_STRING;
#endif
#ifdef BOOST_VERSION
  { 
    std::stringstream ss;
    ss << BOOST_VERSION / 100000 << "." << BOOST_VERSION / 100 % 1000 << "."
       << BOOST_VERSION % 100;
    header["DGM library"]["Boost"] = ss.str();
  }
#endif
  header["Executable"] = code;
  header["File created"] = now;
  header["Restart file name"] = fname;
  header["Number of processors"] = comm->NumProc();
  header["Nel"] = partition->gne();
  header["Nsd"] = nsd;
  header["Lmax"] = Lmax();
  header["Qmax"] = Qmax();
  header["Step"] = step;
  header["Time"] = t;
  header["Time step"] = dt;
  header["Wall time"] = wallTime.read();
#ifdef DGM_BASIS_NORM
  header["Basis type"] = "Normalized";
#else
  header["Basis type"] = "Unnormalized";
#endif
  header["Number of fields"] = F.size();
  header["Root file name"] = root;
  header["CFL"] = CFL;
  header["Field names"] = Json::Value(Json::arrayValue);
  header["Field names"].resize(numeric_cast<Json::ArrayIndex>(F.size()));
  for (vField::size_type i=0; i<F.size(); ++i) {
    const Json::ArrayIndex m = numeric_cast<Json::ArrayIndex>(i);
    header["Field names"][m] = F[i]->name;
  }
  header["Types"] = Json::Value(Json::objectValue);
  header["Types"]["GlobalSize"] = type<DGM::Size>();
  header["Types"]["LocalSize"] = type<DGM::Ordinal>();
  header["Types"]["Scalar"] = type<DGM::Scalar>();
  DGM::ByteOrder byteOrder;
  header["Types"]["ByteOrder"] = byteOrder.asString();
  Json::StyledWriter writer;
  string output = writer.write(header);
  if (!fs) throw DGM::exception("Domain::write_json_header file stream in bad "
                                "state for restart file "+fname);
  fs << output;
  if (!fs) throw DGM::exception("Domain::write_json_header could not write "
                                "header to restart file "+fname);
  disp = fs.tellp();
  if (verbosity()>2)
    comm->cout() << "Domain::write_json_header("<<fname
                 <<") completed with disp = " << disp <<" bytes" << endl;
  return disp;
}

//=============================================================================
//                          Old header support
//============================================================================

streamoff Domain::read_old_header(Json::Value &header,
                                  istream &fs,
                                  const vField &F,
                                  const string &fname) {
  if(verbosity()>2) comm->cout()<<"Domain::read_header("<<fname<<")"<<endl;

  // Fill in Json header with appropriate values for an old style file
  header["Types"] = Json::Value(Json::objectValue);
  header["Types"]["GlobalSize"] = type<int>   ();
  header["Types"]["LocalSize"]  = type<int>   ();
  header["Types"]["Scalar"]     = type<double>();

  Size i_ne;
  Ordinal i_nsd, i_Lmax;
  Scalar i_dt, i_vis;
  string buffer, format;
  if (!(fs>>code)) {
    comm->cerr() <<" Read Error.  rdstate decoded: "
    <<" eofbit - "  << (fs.rdstate() & ifstream::eofbit)
    <<" failbit - " << (fs.rdstate() & ifstream::failbit)
    <<" badbit - "  << (fs.rdstate() & ifstream::badbit)
    <<" goodbit - " << (fs.rdstate() & ifstream::goodbit)
    <<endl;
    comm->error(string("Cannot read code name. Program: ")
    +code+" Filename: "+fname+" Root: "+root+
    " Current Run: "+title);
  }
  getline(fs,buffer);
  getline(fs,buffer);
  if (!(fs>>buffer)) comm->error("Cannot read restart name");
  getline(fs,buffer);
  if (!(fs>>i_ne>>i_nsd>>i_Lmax)) comm->error("Cannot read ne,nsd,Lmax");
  if ( i_ne != F[0]->gne ) {
    stringstream ss;
    ss << "Error: " << fname
    << "\n    does not have the correct number of elements. \n"
    << "    Should be " << F[0]->gne << " but is " << i_ne << "." << endl;
    comm->error(ss.str());
  }
  if ( i_nsd != F[0]->nsd() ) {
    stringstream ss;
    ss << "Error: " << fname
    << "\n    does not have the correct number of spatial dimensions. \n"
    << "    Should be " << F[0]->nsd() << " but is " << i_nsd << "." << endl;
    comm->error(ss.str());
  }
  getline(fs,buffer);
  if (!(fs>>step)) comm->error("Cannot read step");
  getline(fs,buffer);
  if (!(fs>>t)) comm->error("Cannot read time");
  getline(fs,buffer);
  if (!(fs>>i_dt)) comm->error("Cannot read time step");
  getline(fs,buffer);
  if (!(fs>>i_vis)) comm->error("Cannot read viscosity");
  getline(fs,buffer);
  if (Nfields>F.size()) comm->cout() << "Nfields = " << Nfields
  << " F.size = " << F.size() << endl;
  assert(Nfields<=F.size());
  for (vField::size_type i=0; i<Nfields; i++)
    if (!(fs>>buffer)) comm->error("Cannot read Field name");
  getline(fs,buffer);
  if (!(fs>>format)) comm->error("Cannot read format");
  getline(fs,buffer);
#ifdef DGM_BASIS_NORM
  if (lowerCase(format)!="normalized")
    comm->error("Only normalized format is accepted.\nformat = " + format);
#else
  if (lowerCase(format)!="unnormalized")
    comm->error("Only unnormalized format is accepted.\nformat = " + format);
#endif
  streamoff disp = fs.tellg(); // get the header length (in bytes)
  if (verbosity()>2) comm->cout() << "Domain::read_header("<<fname
  <<") with displacement = " << disp << endl;
  return disp;
}

streamoff Domain::read_header(Json::Value  &header,
                              istream      &fs,
                              const vField &F,
                              const std::string &fname) {
#ifdef DGM_USE_JSON_HEADER
  streamoff disp = 0;
  char c = fs.peek();
  if (!fs) throw DGM::exception("Cannot read Json header from "+fname);
  if (c!='{') disp = read_old_header(header, fs,F,fname);
  else {
    disp = read_json_header(header, fs,F,fname);
    step = numeric_cast<Ordinal>(header["Step"].asUInt64());
    t    = numeric_cast<Scalar >(header["Time"].asDouble());
  }
  return disp;
#else
  return read_old_header(header, fs,F,fname);
#endif
}

streamoff Domain::skip_header(Json::Value &header,
                              istream     &fs,
                              const std::string &fname,
                              const vField &F) const {
#ifdef DGM_USE_JSON_HEADER
  streamoff disp = 0;
  char c = fs.peek();
  if (!fs) throw DGM::exception("Cannot read Json header from "+fname);
  if (c!='{') disp = skip_old_header (header, fs, F);
  else        disp = read_json_header(header, fs,F,fname);
  return disp;
#else
  return skip_old_header(header, fs,F);
#endif
}

streamoff Domain::skip_old_header(Json::Value &header,
                                  istream &fs,
                                  const vField &F) const {
  // Fill in Json header with appropriate values for an old style file
  header["Types"] = Json::Value(Json::objectValue);
  header["Types"]["GlobalSize"] = type<int>   ();
  header["Types"]["LocalSize"]  = type<int>   ();
  header["Types"]["Scalar"]     = type<double>();
  //int i_ne, i_nsd, i_Lmax, i_step;
  //Scalar i_dt, i_vis, i_t;
  string buffer, format, i_name;
  //if (!(fs>>buffer)) comm->error("Cannot read code name");
  getline(fs,buffer);
  getline(fs,buffer);
  //if (!(fs>>buffer)) comm->error("Cannot read restart name");
  getline(fs,buffer);
  //if (!(fs>>i_ne>>i_nsd>>i_Lmax)) comm->error("Cannot read ne,nsd,Lmax");
  getline(fs,buffer);
  //if (!(fs>>i_step)) comm->error("Cannot read step");
  getline(fs,buffer);
  //if (!(fs>>i_t)) comm->error("Cannot read time");
  getline(fs,buffer);
  //if (!(fs>>i_dt)) comm->error("Cannot read time step");
  getline(fs,buffer);
  //if (!(fs>>i_vis)) comm->error("Cannot read viscosity");
  getline(fs,buffer);
  //for (int i=0; i<F.size(); i++)
  //if (!(fs>>i_name)) comm->error("Cannot read Field name");
  getline(fs,buffer);
  //if (!(fs>>format)) comm->error("Cannot read format");
  getline(fs,buffer);
#ifdef DGM_BASIS_NORM
  //if (lowerCase(format)!="normalized")
  //  comm->error("Domain: Only normalized restart format is accepted.");
#else
  //if (lowerCase(format)!="unnormalized")
  //  comm->error("Domain: Only unnormalized restart format is accepted.");
#endif
  streamoff disp = fs.tellg(); // get the header length (in bytes)
  // comm->cout() << "Header displacement = " << disp << endl;
  return disp;
}

/// write file header
streamoff Domain::write_header(ostream &fs,
                               const vField &F,
                               const std::string &fname,
                               const bool all) const {
#ifdef DGM_USE_JSON_HEADER
  return write_json_header(fs,F,fname,all);
#else
  if(verbosity()>2) comm->cout()<<"Domain::write_header("<<fname<<")"<<endl;
  streamoff disp=0;
  const Size width = 60;
  const Scalar vis = params.get("vis");
  char now[buflen] = "Time is not available";
#if !defined(DGM_REDSTORM) && !defined(DGM_NO_TIME)
#ifdef DGM_BROADCAST_TIME
  // Only get the time from rank 0 and broadcast
  if (comm->Master()) {
    // get the current date and time from <time.h>
    time_t tp = ::time(0);
    strftime(now,buflen,"%a %b %d %H:%M:%S %Y", localtime(&tp));
  }
  if (all) comm->Broadcast(now, buflen);
#else
  // all ranks get the current date and time from <time.h>
  time_t tp = ::time(0);
  strftime(now,buflen,"%a %b %d %H:%M:%S %Y", localtime(&tp));
#endif
#endif
  // write header
  fs.setf(ios::left);
  if (code.size() > (size_t)width)
    fs<<setw(width)<<code.substr(code.size()-width,width)<<" Session"<<endl;
  else
    fs<<setw(width)<<code<<" Session"<<endl;
  fs<<setw(width)<<now<<" Created"<<endl;
  fs<<setw(width)<<fname.c_str()<<" Name"<<endl;
  // write state flag?
  // make sure to write out the global number of elements
#ifdef DGM_PARALLEL
  fs<<setw(width/3)<<partition->gne()<<setw(width/3)<<nsd
    <<setw(width/3)<<Lmax();
#else
  fs<<setw(width/3)<<ne<<setw(width/3)<<nsd<<setw(width/3)<<Lmax();
#endif
  fs<<" Nel, Nsd, Lmax"<<endl;
  fs<<setw(width)<<step<<" Step"<<endl;
  fs<<setw(width)<<t<<" Time"<<endl;
  fs<<setw(width)<<dt<<" Time step"<<endl;
  fs<<setw(width)<<vis<<" Viscosity"<<endl;
  for (vField::size_type i=0; i<F.size(); i++) {
    size_t tempw = width/(int)F.size();
    if (strlen(F[i]->name.c_str())+1 > tempw)
      tempw = strlen(F[i]->name.c_str())+1;
    fs<<setw((int)tempw)<<F[i]->name.c_str();
  }
  // correct for off by one when F.size() is odd
  if ( numeric_cast<vField::size_type>((width/F.size())*F.size()) <
       numeric_cast<vField::size_type>(width)) fs<<" ";
  fs<<" Field names"<<endl;
#ifdef DGM_BASIS_NORM
  fs<<setw(width)<<"Normalized"<<" Format"<<endl;
#else
  fs<<setw(width)<<"Unnormalized"<<" Format"<<endl;
#endif
  disp = fs.tellp(); // get the header length (in bytes)
  if (verbosity()>2) comm->cout() << "Domain::write_header("<<fname
                                  <<") completed with disp = " << disp
                                  <<" bytes" << endl;
  return disp;
#endif
}

//=============================================================================

streamoff Domain::read_header(Json::Value &header,
                              const std::string &fname,
                              const vField &F) {
  ifstream fs(fname.c_str());
  if (!fs) {
    stringstream msg;
    msg << "Domain::read_header: Could not open restart file: "<<fname;
    comm->error(msg.str());
  }
  const streamoff n = read_header(header, fs, F, fname);
  fs.close();
  return n;
}

streamoff Domain::skip_header(Json::Value &header,
                              const std::string &fname,
                              const vField &F) const {
  ifstream fs(fname.c_str());
  if (!fs) {
    stringstream msg;
    msg << "Domain::skip_header: Could not open restart file: "<<fname<<endl;
    comm->error(msg.str());
  }
  const streamoff disp = skip_header(header, fs, fname, F);
  fs.close();
  return disp;
}

streamoff Domain::write_header(const std::string &fname,
                               const vField &F,
                               const bool all) const {
  if(verbosity()>2) comm->cout() << "Domain::write_header all version "
                    "with all = " << all << endl;
  streamoff disp=0;
  if (comm->Master() || all) {
    ofstream fs(fname.c_str());
    if (!fs) {
      stringstream msg;
      msg << "Domain::write_header: Could not open restart file: "
          << fname<<endl;
      comm->error(msg.str());
    }
    disp = write_header(fs, F, fname, all);
    fs.close();
  }
  const int stat = comm->Broadcast(&disp, 1, 0);
  if (stat != 0) {
    stringstream msg;
    msg << "Domain::write_header: Non-zero return value for "
           "comm->Broadcast(&disp, 1, 0)!" << endl;
    comm->error(msg.str());
  }
  return disp;
}

//=============================================================================

#ifdef DGM_USE_GETSIDEMAPS

/// Flips the quadrature points to make both sides conformal
/*! \note Implement sideMap for 2d elements and then can unify this */
void Domain::get_side_maps( const Side *const sl, const Side *const sr,
                            iVector &mapl, iVector &mapr) const {
  const LocalSize qtot = sl->qtot();
  if (sl->el() || sr->el()) {
    const Ordinal qtot = sl->qtot();
    if (mapl.size() != qtot) mapl.resize(qtot);
    if (mapr.size() != qtot) mapr.resize(qtot);
    const Element *el = sl->el() ? sl->el() : sr->el();
    const Element *er = sr->el() ? sr->el() : sl->el();
    for (Ordinal q=0; q<sl->qtot(); q++) {
      const Ordinal ql = el->sideMap(sl,q);
      const Ordinal qr = er->sideMap(sr,q);
      mapl[q] = ql;
      mapr[q] = qr;
    }
  }
}

#endif

/// Generalized average flux
/** \param[in]  Uf   Solution field
    \param[out] Ff   Flux field
    \param[in]  sign Sets the sign of the "average"

    Note that the sign parameter allows your to flip the sign due to an
    outward normal if needed.
*/
void Domain::average_flux(const vField &Uf, vField &Ff, const char sign) const {
#ifdef DGM_USE_GETSIDEMAPS
  SideMap smap;
  setup_side_maps();
#endif
  assert( (sign=='+') || (sign=='-') );
  const Scalar fact = (sign=='+') ? 1.0 : -1.0;
  for (vField::size_type ni=0; ni<Uf.size(); ni++) {
    for (LocalSize e=0; e<Uf[ni]->ne; e++) {
      const Element* const U = Uf[ni]->el[e];
      for (Ordinal i=0; i<Uf[ni]->el[e]->nSides(); i++) {
        const Side* const Us = Uf[ni]->el[e]->side[i];
        Side* Fs             = Ff[ni]->el[e]->side[i];
        if (Us->master()) {
#ifdef DGM_USE_GETSIDEMAPS
          get_side_maps(Us, Us->link, smap.idl(), smap.idr());
#endif
          for (Ordinal q=0; q<Us->qtot(); q++) {
#ifdef DGM_USE_GETSIDEMAPS
            smap.l(Fs, q) = pt5 * ( smap.l(Us, q) + smap.r(Us, q) );
            smap.r(Fs, q) = smap.l(Fs, q);
#else
            const Ordinal ql = U->sideMap(Us, q);
            const Ordinal qr = U->sideMap(Us->link, q);
            Fs->u[ql]       = pt5 * ( Us->u[ql] + fact*Us->link->u[qr] );
            Fs->link->u[qr] = fact*Fs->u[ql];
#endif
          }
        }
#ifdef DGM_ALLOW_HANGING_NODES
        for (size_t j=0; j<Fs->subsides().size(); j++) {
          const Side* const Uss = Us->subsides()[j].get();
          Side* Fss             = Fs->subsides()[j].get();
          if (Fss->master()) {
#ifdef DGM_USE_GETSIDEMAPS
            get_side_maps(Uss, Uss->link, smap.idl(), smap.idr());
#endif
            for (Ordinal q=0; q<Uss->qtot(); q++) {
#ifdef DGM_USE_GETSIDEMAPS
              smap.l(Fss, q) = pt5 * ( smap.l(Uss, q) + smap.r(Uss, q) );
              smap.r(Fss, q) = smap.l(Fss, q);
#else
              const Ordinal ql = U->sideMap(Uss, q);
              const Ordinal qr = U->sideMap(Uss->link, q);
              Fss->u[ql]       = pt5 * ( Uss->u[ql] + fact*Uss->link->u[qr] );
              Fss->link->u[qr] = fact*Fss->u[ql];
#endif
            }
          }
        }
#endif
      }
    }
  }
}

#ifdef DGM_USE_EPETRA

/// Scatter values to global Epetra vector
void Domain::scatterVector(
    const vector<int> &indexlist,        ///< global ids for test modes
    const dVector     &vh,               ///< local vector
    Epetra_Vector     &erhs              ///< parallel, global vector
) {
  const Ordinal nModes = numeric_cast<Ordinal>(indexlist.size());
  for (Ordinal itest = 0; itest < nModes; ++itest) {
    const int gid = indexlist[itest];
    const int lid = erhs.Map().LID(gid);
    erhs[lid] += vh(itest);
  }
}

/// Scatter local matrix to global matrix
void Domain::scatterMatrix(
    const vector<int> &indexlist_test,   ///< global ids for test modes
    const vector<int> &indexlist_trial,  ///< global ids for trial modes
    const dMatrix     &MATloc,           ///< local matrix
    Epetra_CrsMatrix  &A                 ///< parallel, global matrix
) {
  const size_t nModes_test  = indexlist_test.size();
  const size_t nModes_trial = indexlist_trial.size();
  for (size_t itest = 0; itest < nModes_test; ++itest) {
    const Ordinal litest = numeric_cast<Ordinal>(itest);
    vector<double> rowvaluelist(nModes_trial);
    for (size_t jtrial=0; jtrial<nModes_trial; jtrial++) {
      const Ordinal ljtrial = numeric_cast<Ordinal>(jtrial);
      // \todo: Should we add some dropping here to keep A sparser?
      //        Or should there be a scatterMatrixWithTol()?
      // -> because there might be actual zeros in the element stiffness
      //    and the graph of A may benefit from this extra sparsity...
      //    (agerste)
      rowvaluelist[jtrial] = MATloc(litest,ljtrial);
    }
    const int gdofid = indexlist_test[itest];
    const int lnModes_trial = numeric_cast<int>(nModes_trial);
    const int status =
    A.InsertGlobalValues(gdofid, lnModes_trial,
                         &rowvaluelist[0], &indexlist_trial[0]);
    if (status < 0) 
      throw DGM::exception("Error status from InsertGlobalValues");
  }
}

/// A very expensive way of creating a matrix from a residual
Epetra_CrsMatrix* Domain::GenerateMatrixViaMatlabOutput(
    const DGM::Operator &op
    ) const {
  // Build a CRS matrix and use AztecOO to solve
  comm->cout() << "Making Epetra CRS matrix. This can take a while" << endl;
  EpetraExt::OperatorToMatlabFile("tmp_A.dat", op);
  Epetra_CrsMatrix *Aloc;
  EpetraExt::MatlabFileToCrsMatrix("tmp_A.dat", *(U.eComm.get()), Aloc);
  //EpetraExt::MultiVectorToMatlabFile((root+"_dump_b.dat").c_str(),b);
  return Aloc;
}

/// Simple iterative solver using AztecOO
void Domain::iterative_solve_matrixfree(
    const Teuchos::ParameterList &params,
    const bool refactor
    ) const {
  comm->cout() << "  Domain::iterative_solve_matrixfree()" << flush;
  AztecOO solver(*lp);
  solver.SetAztecOption(AZ_solver, AZ_gmres);
  solver.SetAztecOption(AZ_kspace, params.get<int>("kspace"));
  solver.SetAztecOption(AZ_precond, AZ_none);
  solver.SetAztecOption(AZ_conv, AZ_noscaled);
  solver.SetAztecOption(AZ_output, AZ_warnings);
  solver.Iterate(params.get<int>("iterations"),params.get<double>("tolerance"));
  comm->cout() << ": iter = " << solver.NumIters()
      << ", |true-res| = " << solver.TrueResidual() << std::endl;
}

/// Simple iterative solver using AztecOO for Helmholtz problem
/// I should switch to a solver xml file before this gets out of hand here
/// (agerste)
void Domain::iterative_solve(
    const Teuchos::ParameterList &params,
    const bool refactor
    ) const {
  comm->cout() << "  Domain::iterative_solve()" << flush;
  AztecOO solver(*lp);
  solver.SetAztecOption(AZ_solver, AZ_gmres);
  solver.SetAztecOption(AZ_kspace, params.get<int>("kspace"));
  solver.SetAztecOption(AZ_precond, AZ_dom_decomp);
  solver.SetAztecOption(AZ_subdomain_solve, AZ_ilu);
  solver.SetAztecOption(AZ_conv, AZ_r0);
  solver.SetAztecOption(AZ_output, AZ_warnings);
  solver.Iterate(params.get<int>("iterations"),params.get<double>("tolerance"));
  comm->cout() << ": iter = " << solver.NumIters()
      << ", |true-res| = " << solver.TrueResidual() << std::endl;
}

/** \brief Algebraic Multigrid solver using AztecOO and ML for implicit problems
 *
 * \note One should switch to a xml input file to manage the input of solvers
 *       (agerste)
*/
void Domain::iterative_ML_solve(
    const Teuchos::ParameterList &params,
    const bool rebuild,
    const bool matlab_output
    ) {
  comm->cout() << "  Domain::iterative_ML_solve()" << flush;

  // build high-order Legendre to linear Lagrange transformation matrix
  ml = Teuchos::rcp(new DGM::SolverML(comm));
  ml->compute_transformation_matrix_global_appr(U);
  if (matlab_output) {
    comm->cout() << ", output G" << std::flush;
    EpetraExt::OperatorToMatlabFile((root+"_dump_G.dat").c_str(),*(ml->G));
    ml->output_element_corner_coordinates(U, root);
  }

  // start new solver parameter list, this could/should be a separate xml file,
  // which could be a new input file root.xml or something like that
  Teuchos::ParameterList solparams;
#if (__clang_major__ == 5)
  solparams.set("kspace", params.get<int>("kspace"));
  solparams.set("iterations", params.get<int>("iterations"));
  solparams.set("tolerance", params.get<double>("tolerance"));
#else
  solparams.set<int>("kspace", params.get<int>("kspace"));
  solparams.set<int>("iterations", params.get<int>("iterations"));
  solparams.set<double>("tolerance", params.get<double>("tolerance"));
#endif

  // Setup preconditioner
  ML_Epetra::SetDefaultsLevelWrap(solparams,false);

  Teuchos::ParameterList &ilist=solparams.sublist("smoother: ifpack list");
  const int p = params.get<int>("Legendre polynomial order");
  int blocksize = 0; // didn't use pow(p+1,nsd), because I wan't to make sure
                     // that blocksize stays an int and is not rounded
  switch (nsd) {
    case 1: blocksize = (p+1); break;
    case 2: blocksize = (p+1)*(p+1); break;
    case 3: blocksize = (p+1)*(p+1)*(p+1); break;
    default: error("wrong number of space dimensions"); break;
  }
  const int NumLocalBlocks = A->NumMyRows()/blocksize;
  ilist.set("partitioner: local parts",NumLocalBlocks);
  ilist.set("partitioner: type","linear");
  //ilist.set("relaxation: type","Jacobi"); // <-- serial parallel consistency

  // configure transformation layer between Legendre -> Lagrange
  Teuchos::ParameterList &clist=solparams.sublist("levelwrap: coarse list");
//#define OUTPUT_FOR_ML_PAPER
#ifdef OUTPUT_FOR_ML_PAPER
  clist.set("ML output",10);
#else
  clist.set("ML output",1);
#endif
  //clist.set("coarse: max size",500);
  //clist.set("max levels",1); // <-- debug & serial parallel consistency
  //clist.set("coarse: type","do-nothing");

  // general smoother settings
  solparams.set("smoother: ifpack type","block relaxation stand-alone");
#ifdef OUTPUT_FOR_ML_PAPER
  solparams.set("ML output",10);
#endif

  // manual matrix multiply (debug code)
  //Epetra_CrsMatrix tmp(Copy,A->RowMap(),0);
  //Epetra_CrsMatrix A1(Copy,ml->G->DomainMap(),0);
  //assert(EpetraExt::MatrixMatrix::Multiply(*A,false,*ml->G,false,tmp) == 0);
  //assert(EpetraExt::MatrixMatrix::Multiply(*ml->G,true,tmp,false,A1) == 0);
  //solparams.set("user coarse matrix",&A1);

  // Coordinates & aux aggregation (better handle anisotropy).
  std::vector<double> coordx, coordy, coordz;
  ml->compute_nodal_coordinates(U,coordx,coordy,coordz);
  clist.set("x-coordinates",&coordx[0]);
  if(nsd>1) clist.set("y-coordinates",&coordy[0]);
  if(nsd>2) clist.set("z-coordinates",&coordz[0]);
  clist.set("aggregation: aux: enable",true);
  clist.set("aggregation: aux: threshold",.05);
  clist.set("coarse: max size",500);

  // configure ML preconditioner and Aztec
  Teuchos::RCP<ML_Epetra::LevelWrap> mlp =
      Teuchos::rcp(new ML_Epetra::LevelWrap(A, ml->G, solparams));

  AztecOOSolver = Teuchos::rcp(new AztecOO(*lp));
  AztecOOSolver->SetPrecOperator(mlp.get());
  AztecOOSolver->SetAztecOption(AZ_solver, AZ_cg);
  //AztecOOSolver->SetAztecOption(AZ_kspace, solparams.get<int>("kspace"));
  AztecOOSolver->SetAztecOption(AZ_conv, AZ_r0);
#ifdef OUTPUT_FOR_ML_PAPER
  AztecOOSolver->SetAztecOption(AZ_output, 10);
#else
  AztecOOSolver->SetAztecOption(AZ_output, AZ_warnings);
#endif
  AztecOOSolver->SetAztecOption(AZ_diagnostics, AZ_none);

  // solve
  AztecOOSolver->Iterate(solparams.get<int>("iterations"),
                         solparams.get<double>("tolerance"));
  comm->cout() << ": iter = " << AztecOOSolver->NumIters()
      << ", |true-res| = " << AztecOOSolver->TrueResidual() << std::endl;

  if (matlab_output) {
    EpetraExt::OperatorToMatlabFile((root+"_dump_A1.dat").c_str(),
        *(mlp->GetA1()));
  }
}

/// Simple direct solve using Amesos KLU
void Domain::direct_solve(const bool refactor) {
  //static FunctionTimer timer(__PRETTY_FUNCTION__);
  //FunctionSentry sentry(timer);
  if ( refactor ) {
    Amesos Factory;
    //comm->cout() << endl << endl;
    //comm->cout() << Factory.Query("Amesos_Klu") << endl;
    //comm->cout() << Factory.Query("Amesos_Umfpack") << endl;
    //comm->cout() << Factory.Query("Amesos_Mumps") << endl;
    //comm->cout() << Factory.Query("Amesos_Scalapack") << endl;
    //comm->cout() << Factory.Query("Amesos_Paraklete") << endl;
    string solver("Amesos_Klu");
#ifdef DGM_PARALLEL
    if (Factory.Query("Mumps") == true) {
      solver = "Mumps";
    }
#endif
    AmesosSolver = Teuchos::rcp(Factory.Create(solver, *lp));
    assert(AmesosSolver != Teuchos::null);
    comm->cout() << "Amesos::Factorization("<<solver<<")" << endl;
    const int status = AmesosSolver->NumericFactorization();
    if (status != 0) throw DGM::exception("Amesos Factorization error");
  }
  comm->cout() << "Amesos::Solve" << endl;
  const int status = AmesosSolver->Solve();
  if (status != 0) throw DGM::exception("Amesos Solve error");
}

#endif  // DGM_USE_EPETRA

} // namespace DGM
