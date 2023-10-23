#ifndef PEREO_HPP
#define PEREO_HPP

/** \file PEReo.hpp
    \brief Provides Reo specific functionality to peopt. */

// DGM includes
#include "Comm.hpp"
#include "BlackBox.hpp"
#include "PEDgm.hpp"

// local includes
#include "ReoOptProblem.hpp"

namespace peopt {

  struct Weighting {
    /// Type of source weighting strategies
    enum t{
      None,       ///< No weighting
      Unit,       ///< Weights every experiment with 1 and adds them
                  ///< together
      Negative,   ///< Weights every experiment with -1 and adds them
                  ///< together
    };

    /// Converts the weighting scheme to a string
    static std::string to_string(t weighting){
      switch(weighting){
      case None:
        return "None";
      case Unit:
        return "Unit";
      case Negative:
        return "Negative";
      default:
        throw;
      }
    }

    // Converts a string to a weighting scheme
    static t from_string(std::string weighting){
      if(weighting=="None")
        return None;
      else if(weighting=="Unit")
        return Unit;
      else if(weighting=="Negative")
        return Negative;
      else
        throw;
    }

    // Checks whether or not a string is valid
    struct is_valid : public std::unary_function<std::string, bool> {
      bool operator () (const std::string& name) const {
        if( name=="None" ||
            name=="Unit" ||
            name=="Negative"
        )
          return true;
        else
          return false;
      }
    };
  };

  namespace Params {
    /// Weighting parameters
    class Reo{
    private:
      /// Used for the error messages
      DGM::Shared <DGM::Comm>::Ptr comm;

    public:
      /// Weighting strategy
      Weighting::t weighting;

      /// Actual weights
      std::vector <std::vector <DGM::Scalar > > weights;

      /// Number of experiments after weighting
      unsigned int nexperiments;

      /// Reads all the parameters from a file
      void read(string fname);

      /// Writes the current inputs to a string
      string to_string();

      /// Writes out all the parameters to file
      void write(string fname);

      /// Validates the current input arguments
      void validate();

      /// Constructor where we make an empty parameter object
      Reo(DGM::Shared <DGM::Comm>::Ptr comm_)
          : weighting(Weighting::None) {}
    };
  }

  /// Combined DGM and diagnostic parameters
  typedef Params::Merge <Params::Dgm,Params::Diagnostic> DgmDiagnosticParams;

  /// Combine DGM, diagnostic, and restart parameters
  typedef Params::Merge <DgmDiagnosticParams,Params::Restart <Reo::OptProblem> >
      DgmDiagnosticRestartParams;

  /// Combined DGM, diagnostic, restart, and Reo parameters
  typedef Params::Merge <DgmDiagnosticRestartParams,Params::Reo> ReoParams;

  /// Reo state manipulator
  template<class OptProblem, class Params>
  class ReoManipulator
      : public peopt::StateManipulator <DGM_InequalityConstrained>
  {
  private:
    /// This communicator needs to span all the groups.  Basically, the
    /// group and rank communicators needed to have been carved out of this
    /// communicator.
    DGM::Shared <DGM::Comm>::Ptr comm;

    /// The optimization problem that we're controlling
    DGM::MultiOptProblem <OptProblem>& mocp;

    /// Parameters that control the weighting
    Params& params;

    /// A reference to a restarting manipulator
    peopt::RestartManipulator <OptProblem,Params> rmanip;

  public:

    /// Constructor
    ReoManipulator(
      DGM::Shared <DGM::Comm>::Ptr comm_,
      DGM::MultiOptProblem <OptProblem>& mocp_,
      Params& params_,
      peopt::RestartManipulator <OptProblem,Params>& rmanip_
    ) : comm(comm_), mocp(mocp_), params(params_), rmanip(rmanip_) {};

    /// Set the weights
    void set_weights() const {
      // Clear out the old global weights
      params.weights.resize(0);

      // If we're doing no weighting, set the number of experiments
      // to the number of PDEs
      if(params.weighting==Weighting::None)
        params.nexperiments=mocp.npdes;

      // Otherwise, we have a single weight
      else
        params.nexperiments=1;

      // Next, if we're the master node, we create a new set of global weights
      if(comm->MyPID()==0){
        switch(params.weighting) {
        case Weighting::None:
          // Add a separate weight for every PDE
          for(int i=0;i<mocp.npdes;i++){
            vector <DGM::Scalar> weight(mocp.npdes,0.);
            weight[i]=1.;
            params.weights.push_back(weight);
          }
          break;
        case Weighting::Unit: {
          vector <DGM::Scalar> weight(mocp.npdes,1.);
          params.weights.push_back(weight);
          break;
        }
        case Weighting::Negative: {
          vector <DGM::Scalar> weight(mocp.npdes,-1.);
          params.weights.push_back(weight);
          break;
        } }
      }

      // Next, we broadcast each of the weights to everyone else
      for(unsigned int i=0;i<params.nexperiments;i++){
        vector <DGM::Scalar> weight(mocp.npdes);
        if(comm->MyPID()==0) weight=params.weights[i];
        comm->Broadcast(&(weight.front()),mocp.npdes,0);
        if(comm->MyPID()!=0) params.weights.push_back(weight);
      }

      // Divide the number of experiments between the groups as evenly as
      // possible.
      vector <int> whichExperiments;
      for(unsigned int i=0;i<params.nexperiments;i++){
        // Determine which group the pde belongs
        int which_group=
          DGM::Multi::get_group(params.nexperiments,params.num_groups,i);

        // If this PDE belongs to this group, add it to the list
        if(which_group==mocp.gnum){
          whichExperiments.push_back(i);
        }
      }

      // Finally, prime the MultiOptProblem with the weights this node controls
      mocp.weights.resize(0);
      for(vector <int>::iterator i=whichExperiments.begin();
          i!=whichExperiments.end();i++
      )
        mocp.weights.push_back(params.weights[*i]);
    }

    /// Application of the manipulator
    void operator() (
      const typename DGM_InequalityConstrained::Functions::t& fns,
      typename DGM_InequalityConstrained::State::t& state,
      peopt::OptimizationLocation::t loc
    ) const {

      // Call the restart manipulator
      rmanip(fns,state,loc);

      // Make sure we set the weights at the appropriate time
      switch(loc) {
      case peopt::OptimizationLocation::BeginningOfOptimization:
        set_weights();
        break;
      default:
        break;
      }
    }
  };
}

#endif
