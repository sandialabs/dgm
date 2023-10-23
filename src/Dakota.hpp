#ifndef DGM_DAKOTA_HPP
#define DGM_DAKOTA_HPP

/** \file Dakota.hpp
    \brief Direct DGM-DAKOTA interface declaration
    \author Scott Collis
*/

// system includes
#include <iostream>

// DAKOTA includes
#include "DirectApplicInterface.H"
#ifdef DGM_PARALLEL
#include "ParallelLibrary.H"
#endif

// DGM includes
#include "OptProblem.hpp"

namespace DGM {

/// DGM/DAKOTA direct function interface
/** This class allows DGM to link directly with DAKOTA */
class DirectApplicInterface : public Dakota::DirectApplicInterface {

public:

  //
  //- Heading: Constructor and destructor
  //
  DirectApplicInterface( const Dakota::ProblemDescDB &problem_db,
                         const size_t &num_fns,
                         DGM::ArgList &args, const Table& = Table(),
                         const DGM::Comm *comm_in = DGM::Comm::World
                         );                      ///< constructor

  ~DirectApplicInterface();                      ///< destructor

protected:

  //
  //- Heading: Virtual function redefinitions
  //

  /// execute the input filter portion of a direct evaluation invocation
  int derived_map_if(const Dakota::String& if_name);
  /// execute an analysis code portion of a direct evaluation invocation
  int derived_map_ac(const Dakota::String& ac_name);
  /// execute the output filter portion of a direct evaluation invocation
  int derived_map_of(const Dakota::String& of_name);

private:

  //
  //- Heading: Data
  //

  OptProblem *ocp;         ///< DGM optimal control problem

  const DGM::Comm *comm;   ///< DGM communicator

  // These are due to the need for a delayed construction of the Problem
  DGM::ArgList &args;
  const Table &params;

  /// setup the optimal control problem
  void setup();

};

} // namespace DGM

#endif  // DGM_DAKOTA_HPP
