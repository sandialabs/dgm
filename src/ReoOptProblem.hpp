#ifndef REO_OPT_PROBLEM_HPP
#define REO_OPT_PROBLEM_HPP

/** \file ReoOptProblem.hpp
    \brief Reo optimization problem declaration
    \author S. Collis and J. Overfelt
*/

// standard libraries
#include <iostream>
#include <string>
#include <list>
using namespace std;

// local libraries
#include "Comm.hpp"
#include "Table.hpp"
#include "Domain.hpp"
#include "State.hpp"
#include "Adjoint.hpp"
#include "Control.hpp"
#include "Objective.hpp"
#include "Optimizer.hpp"
#include "OptProblem.hpp"

namespace Reo {

  /// Reo optimization problem class
  /** Determines run parameters and sets up a Reo problem on a domain. */
  class OptProblem : public DGM::OptProblem {

  public:

    /// Constructor for regular optimization problems
    OptProblem( DGM::ArgList &, const DGM::Table & = DGM::Table(),
                const DGM::Comm::Ptr = DGM::Comm::World );

    /// Constructor for a linearized optimization problems
    OptProblem( const OptProblem *, DGM::ArgList &,
                const DGM::Table & = DGM::Table(),
                const DGM::Comm::Ptr = DGM::Comm::World );

    /// Destructor
    virtual ~OptProblem() {
      if (comm->verbosity()>1) comm->cout() << "Reo::~OptProblem" << endl;
    }

    /// Extract arguments
    virtual void parse_args( DGM::ArgList &args );

    /// Show supported command line arguments
    virtual void showUsage(const string &) const;

    /// Main solve interface
    virtual int solve();

  };

}  // namespace Reo


#endif // REO_OPT_PROBLEM_HPP
