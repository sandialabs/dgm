#ifndef REO_PROBLEM_HPP
#define REO_PROBLEM_HPP

/** \file ReoProblem.hpp
    \brief Reo Problem class declaration
    \author Scott Collis
    \author Axel Gerstenberger

    Problem hold the computational Domain and provides both solve and plot
    methods for forward solvers
*/

// standard libraries
#include <cstdio>
#include <iostream>
#include <string>
#include <list>
using namespace std;

// DGM libraries
#include "Comm.hpp"
#include "ArgList.hpp"
#include "Table.hpp"
#include "Domain.hpp"
#include "Problem.hpp"

// local includes
#include "Reo.hpp"

namespace Reo {

  /// Reo problem class
  /** The Reo::Problem serves as an example of how to define application
      problems built off of the DGM::Problem. */
  class Problem : public DGM::Problem {

    void setup(DGM::ArgList &);

  public:

    /// Constructor for Reo::Problem
    Problem(DGM::ArgList &, DGM::Table &,
            const DGM::Comm::Ptr = DGM::Comm::World);

    /// Destructor
    virtual ~Problem() {
      //cout << "~Reo::Problem" << endl;
    }

    /// Extract arguments for this Problem
    virtual void parse_args( DGM::ArgList &args );

    /// Show the commandline usage for this Problem
    virtual void showUsage(const string &code) const;

    virtual void physics_names(std::vector<std::string>& p) const;

  private:

#ifdef DGM_USE_JSON
    /// Local helper to parse JSON input
    EqnType parse_json(const string &root, const DGM::Comm::Ptr comm) const;
#endif
  };

#ifdef DGM_TEST_PYTHON_INTERFACE
  class Test {
  public:
    Test( DGM::ArgList *args, DGM::Table *table, DGM::Comm *comm ) {
      std::cout << "Reo::Test constructor" << std::endl;
      std::cout << "  args->size() = " << args->size() << std::endl;
      std::cout << "  table->size() = " << table->size() << std::endl;
      std::cout << "  comm->Name() = " << comm->Name() << std::endl;
      std::cout << "Finished test" << std::endl;
    }
  };
#endif

} // namespace Reo

#endif  // REO_PROBLEM_HPP
