#ifndef DGM_REMOVE_FOR_RELEASE

#ifndef REO_SHALLOW_OBS_HPP
#define REO_SHALLOW_OBS_HPP

/** \file ShallowObs.hpp
    \brief Shallow water observation terms
    \author Vincent Mousseau
    \author Scott Collis
*/

// system includes
#include <vector>
#include <string>
#include <iostream>
using namespace std;

// DGM includes
#include "Types.hpp"
#include "Comm.hpp"
#include "Response.hpp"
#include "Obs.hpp"

// local includes
#include "ShallowAdjoint.hpp"

namespace Reo {

//===========================================================================
//                    Phi Tracking Observation Source
//===========================================================================

/// Phi tracking observation source
class ShallowAdjoint::PhiTracking : public Source, public Obs {
  const ShallowState *state;  ///< State to observe
  Response::Ptr response;     ///< Local response
  const DGM::Comm::Ptr comm;  ///< parallel communicator
  string fname;               ///< filename for Observation data
  int verb;                   ///< Verbosity level
  dMatrix obj;                ///< Place to store missfit
  Ordinal Nprobes;            ///< Number of probes
  Ordinal Nrealizations;      ///< Number of realizations
  Ordinal Ncomponents;        ///< Number of things to measure
  dVector weights;            ///< Weights for each realization
  bool height_only;           ///< Measure only the height
  Size probe_data_length;     ///< Number of samples in probe data
  Scalar probe_data_dt;       ///< Probe data sample interval
  string probe_path;          ///< Path to probe data
  vector<string> names;       ///< Name of each component
public:
  PhiTracking( const string tag, ifstream &in, const vField &F,
               const ShallowState *s ) :
    Source(tag), state(s), comm(F.get_comm()), verb(0), Nprobes(0),
    Nrealizations(1), Ncomponents(state->U.size()), weights(Nrealizations,1.0),
    height_only(false), probe_data_length(state->Nt+1), probe_data_dt(0),
    probe_path("obj")
  {
#ifdef DGM_USE_JSON
    ndof = 1;
    Json::Value root;
    Json::Reader reader;
    string buffer;
    scan_lb(in);
    buffer = read_block(in);
    scan_rb(in);
    bool parsingSuccessful = reader.parse( buffer, root );
    if (!parsingSuccessful)
      throw DGM::exception("ShallowAdjoint::PhiTracking could not parse "
                           "JSON input:\n"+reader.getFormattedErrorMessages());
    verb = root.get("Verbosity",0).asInt();
    if (verb) {
      Json::StyledWriter writer;
      string output = writer.write(root);
      comm->cout() << "PhiTracking input:\n" << output;
    }
    penalty = root.get("Penalty",one).asDouble();
    probe_path = root.get("Probe path",probe_path).asString();
    height_only = root.set("Height only",false).asBool();

    // read the Response block
    if (!root.isMember("Response"))
      throw DGM::exception("PhiTracking input is missing Response section");
    Json::Value response_root = root["Response"];
    if (!response_root.isMember("Verbosity"))
      response_root.set("Verbosity",verb);
    fname = response_root.set("Filename",s->root+".anl").asString();
    if (verb)
      comm->cout() << "PhiTracking("<<type<<") objective penalty = "
                   << penalty << " with response " << fname << endl;
    response.reset(Response::factory(state->U, state->domain(), response_root));
    if (!response->isValid()) {
      throw DGM::exception("Invalid response in PhiTracking: "+fname);
    }
    Nprobes = numeric_cast<Ordinal>(response->probes_on_proc());
    if (height_only) {
      Ncomponents = 1;
      names.push_back("phi");
    } else {
      Ncomponents = state->U.size();
      names = state->U.get_Field_names();
    }
    if (Nprobes > 0) {
      obj.resize( Nprobes, Ncomponents );
      obj = zero;
    }
    if (verb>1)
      cout << "  Found " << Nprobes << " probes " << "on rank "
           << comm->MyPID() << " with " << Ncomponents
           << " components."<< endl;
#else
    DGM_UNDEFINED;
#endif
  }

  /// set the observation data at a given step (and substep)
  void set_data( const vField &Ustate, const Ordinal istep,
                 const Ordinal sstep=0 ) {
    response->integrate_probes(obj, Ustate);

    // The NULL indicates that no time interpolation is supported
    response->subtract_weighted_traces(obj, weights, state->time_int, NULL,
                                       state->dt, istep, sstep);
  }

  /// apply source to State
  void apply( const Scalar, const vField &, vField &Ur ) { }

  /// apply source to Adjoint
  void adjoint_apply( const Scalar, const vField &state,
                      const vField &adjoint, vField &Ur) {
    response->addScaled(Ur, obj, penalty);

  }

  // Source virtual methods
  inline Obs* obs() { return this; }
  inline const Obs* obs() const { return this; }

  // Obs virtual methods
  void initialize() {
    // comm->cout()<<"PhiTracking::initialize()"<<endl;
    read_probes();
  }

  /// Need to read probe data
  void read_probes() {
    comm->cout()<<"Reading probe data from "<< probe_path << endl;
    probe_data_length = response->init_probe_data(state->root, probe_path,
                                                  names, Nrealizations,
                                                  state->Nt);
    probe_data_dt = response->probeDeltaTime;
  }

  /// The end condition for this observation is null
  void end_condition( vField &F ) { }

  /// Provide the norm (squared) for this obs
  Scalar norm() const {
    Scalar result=zero;
    for (size_t p=0; p<response->probes.size(); ++p) {
      const Ordinal lp = numeric_cast<Ordinal>(p);
      const Response::Probe::Ptr probe = response->probes[p];
      if (probe->kernel->owned_by_this_proc()) {
        for (Ordinal i=0; i<Ncomponents; ++i) result += obj[lp][i]*obj[lp][i];
      }
    }
    return result;
  }

};

} //namespace Reo

#endif  // REO_SHALLOW_OBS_HPP

#else // DGM_REMOVE_FOR_RELEASE
// This capability is under development.
#endif // DGM_REMOVE_FOR_RELEASE
