/** \file ReoProblem.cpp
    \brief Reo Problem class implementation
    \author Scott Collis
    \author Axel Gerstenberger
    \author Guglielmo Scovazzi

    Problem hold the computational Domain and provides both solve and plot
    methods for the combined Reo solvers.  The Reo::Problem serves as an
    example of how to build new Problem classes deriving off of the
    DGM::Problem class.
*/

// DGM includes
#include "Problem.hpp"
#include "TimeInt.hpp"
#include "ArgList.hpp"

// Reo includes
#include "Reo.hpp"
#include "ReoProblem.hpp"
#include "Adv_Diff.hpp"
#include "Euler.hpp"
#include "Navier_Stokes.hpp"
#include "Turbulence.hpp"
#include "Wave.hpp"
#include "Burgers.hpp"
#include "LinEuler_quasi.hpp"
#include "LinEuler_prim.hpp"
#include "LinNS_quasi.hpp"
#include "Euler3d.hpp"
#include "Navier_Stokes3d.hpp"
#include "iEuler.hpp"
#include "iNS.hpp"
#include "EulerDC.hpp"
#include "Couple.hpp"
#include "Helmholtz.hpp"
#include "Darcy.hpp"
#include "Multi_Mat_Adv_Diff.hpp"
#include "MiscibleTransport.hpp"
#include "Poisson.hpp"
#ifndef DGM_REMOVE_FOR_RELEASE
#include "Shallow.hpp"
#endif // DGM_REMOVE_FOR_RELEASE
#include "Maxwell.hpp"

namespace Reo {

Problem::Problem( DGM::ArgList &args, DGM::Table &table,
                  const DGM::Comm::Ptr comm_ ) : 
  DGM::Problem(args,table,comm_) {
  setup(args);
}

/// Set default values for Reo problems
void Problem::setup(DGM::ArgList &args) {

  // set the root file name
  if (args.size()==1 || args.back()[0]=='-') args.push_back("root");
  const string root =  args.back();

  // extract equation type from JSON if available
  params["eqntype"] = Reo::p2i(parse_json(root, comm));

  // parse the root.inp file and command line arguments
  parse_args( args );

  const int eqntype = params["eqntype"];

#if REO_PROBLEM_DEBUG
  comm->cout()<<"Reo::Problem parameter table"<<endl;
  comm->cout()<<params;
  comm->cout()<<"Equation type = "<<Reo::p2s(Reo::i2p(params["eqntype"]))<<endl;
#endif
 
  switch(eqntype) {
  case Reo::ADV_DIFF: {
    Omega = new Reo::Adv_Diff( args, comm );
    break; }
  case Reo::MULTI_COMP_MISC_TRANS: {
    Omega = new Reo::Multi_Comp_Misc_Trans( args, comm );
    break; }
  case Reo::MULTI_MAT_ADV_DIFF: {
    Omega = new Reo::Multi_Mat_Adv_Diff( args, comm );
    break; }
  case Reo::MISC_DISPL_FLOW: {
    Omega = new Reo::Multi_Comp_Misc_Trans( args, comm, true );
    break; }
  case Reo::DENS_DRIVEN_CO2_SEQ: {
    Omega = new Reo::Multi_Mat_Adv_Diff( args, comm, true );
    break; }
  case Reo::EULER: {
    Omega = new Reo::Euler( args, comm );
    break; }
  case Reo::NAVIER_STOKES: {
    Omega = new Reo::Navier_Stokes( args, comm );
    break; }
  case Reo::TURBULENCE: {
    Omega = new Reo::Turbulence( args, comm );
    break; }
  case Reo::WAVE: {
    Omega = new Reo::Wave( args, comm );
    break; }
  case Reo::BURGERS: {
    Omega = new Reo::Burgers( args, comm );
    break; }
  case Reo::IEULER: {
    Omega = new Reo::iEuler( args, comm );
    break; }
  case Reo::INS: {
    Omega = new Reo::iNS( args, comm );
    break; }
  case Reo::LINEULER_QUASI: {
    Omega = new Reo::LinEuler_quasi( args, comm );
    break; }
  case Reo::LINEULER_PRIM: {
    Omega = new Reo::LinEuler_prim( args, comm );
    break; }
  case Reo::LIN_NS_QUASI: {
    Omega = new Reo::LinNS_quasi( args, comm );
    break; }
  case Reo::EULER3D: {
    Omega = new Reo::Euler3d( args, comm );
    break; }
  case Reo::EULERDC: {
    Omega = new Reo::EulerDC( args, comm );
    break; }
  case Reo::NAVIER_STOKES3D: {
    Omega = new Reo::Navier_Stokes3d( args, comm );
    break; }
#ifdef DGM_USE_MD_COUPLE
  case Reo::COUPLE: {
    Omega = new Couple( args, comm );
    break; }
#endif
  case Reo::HELMHOLTZ: {
    Omega = new Reo::Helmholtz( args, comm );
    break; }
  case Reo::DARCY: {
    Omega = new Reo::Darcy( args, comm );
    break; }
  case Reo::POISSON: {
    Omega = new Reo::Poisson( args, comm );
    break; }
#ifndef DGM_REMOVE_FOR_RELEASE
  case Reo::SHALLOW: {
    Omega = new Reo::Shallow( args, comm );
    break; }
#endif // DGM_REMOVE_FOR_RELEASE
  case Reo::MAXWELL: {
    Omega = new Reo::Maxwell( args, comm );
    break; }
  default:
    stringstream msg;
    msg << "Reo::Problem: Unsupported equation type: " << eqntype << endl
        << "See 'Reo.hpp' for a listing of the supported equation types.";
    comm->error(msg.str());
    break;
  }

  // set the material properties
  Omega->set_material();

  // Final check of argument list
  if ( params.defined("showUsage") ) comm->exit(0);
#ifdef DGM_REMOVE_ARGUMENTS
  if ( args.size() != 2 ) {
    comm->cout() << "WARNING:  " << args.size() << " unused arguments:  ";
    print( args );
  }
#endif
}

/** Get basic information from root.inp and command line argument list */
void Problem::parse_args( DGM::ArgList &args ) {
  code = args.front();
  if (args.size() < 2) {
    showUsage(code);
    comm->exit();
  }
  root = args.back();
  params.read(root+".inp");
  list< DGM::ArgList::iterator > li;
  for ( DGM::ArgList::iterator a = args.begin(); a != args.end(); a++ ) {
    if ( (*a)[0] == '-' ) {
      const string name = *a;
      if (name == "-e") {
        li.push_back(a);
        const string value = *(++a);
        li.push_back(a);
        params["eqntype"] = atoi(value.c_str());
      } else if (name == "-help") {
        params["showUsage"] = 1;
        showUsage(code);
      }
    }
  }
  // remove tagged arguments
  for (list< DGM::ArgList::iterator >::iterator a=li.begin();
       a!=li.end(); a++) args.erase(*a);
}

#ifdef DGM_USE_JSON
/// Local helper to parse JSON input
/** SSC:  this is inconsistent in that the Problem should not read anything
    from the Domain.  This means that the input structure should be improved
    to make the equation type a parameter on the Problem, not the Domain. */
EqnType Problem::parse_json(const string &root, const DGM::Comm::Ptr comm) const {
  int i = p2i(Reo::EULER);    // Set the default to 2d Euler solver
  if (comm->Master()) {
    Json::Value json;
    const string file = root + ".json";
    ifstream in(file.c_str());
    if (in) {
      Json::Reader reader;
      if (!reader.parse(in,json,true)) {
        throw DGM::exception("Failed to parse the json input file " + file +
                             ":  " + reader.getFormattedErrorMessages());
      }
    }
    if (json.isMember("Domain") && json["Domain"].isMember("Type")) {
      i = p2i(s2p(json["Domain"]["Type"].asString()));
    }
  }
  comm->Broadcast(&i);
  const EqnType p = i2p(i);
  return p;
}
#endif

void Problem::showUsage(const string &code) const {
  comm->cout()
    << "Reo::Problem Class Options \n"
    << "----------------------------------------------------------------\n"
    << "-e <int>" << '\t' << "Equation type \n"
    << "----------------------------------------------------------------\n";
}

/** \note The order must match that in the p2i method 
    \todo This is redundant with the Reo::p2s function and should be removed */
void Problem::physics_names(std::vector<std::string>& p) const {
  p.push_back("adv_diff");
  p.push_back("euler");
  p.push_back("navier_stokes");
  p.push_back("wave");
  p.push_back("lineuler_quasi");
  p.push_back("lineuler_prim");
  p.push_back("burgers");
  p.push_back("turbulence");
  p.push_back("euler3d");
  p.push_back("navier_stokes3d");
  p.push_back("couple");
  p.push_back("ieuler");
  p.push_back("ins");
  p.push_back("eulerdc");
  p.push_back("helmholtz");
  p.push_back("poisson");
#ifndef DGM_REMOVE_FOR_RELEASE
  p.push_back("shallow");
#endif // DGM_REMOVE_FOR_RELEASE
  p.push_back("linadv_diff");
  p.push_back("linburgers");
  p.push_back("darcy");
  p.push_back("multi_comp_misc_trans");
  p.push_back("multi_mat_adv_diff");
  p.push_back("misc_displ_flow");
  p.push_back("dens_driven_co2_seq");
  p.push_back("maxwell");
  p.push_back("lin_ns_quasi");
}

} // namespace Reo
