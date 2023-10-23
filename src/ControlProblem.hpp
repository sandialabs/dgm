#ifndef DGM_CONTROL_PROBLEM_HPP
#define DGM_CONTROL_PROBLEM_HPP

/** \file  ControlProblem.hpp
    \brief Feedback control problem declarations
    \author Scott Collis
*/

// standard libraries
#include <iostream>
#include <string>
#include <list>
using namespace std;

// DGM libraries
#include "Comm.hpp"

#include "Problem.hpp"
#include "Table.hpp"
#include "Domain.hpp"

#include "State.hpp"
#include "Adjoint.hpp"
#include "Control.hpp"
#include "Objective.hpp"
#include "Optimizer.hpp"
#include "Controller.hpp"

namespace DGM {

/// Feedback Control Problem
/** \warning This is not finished nor is it tested
    Setup a feedback control problem.  The idea here is to derive off of the
    Problem class for a feedback (no optimization) control problem as an
    example of how to do this. */
class ControlProblem : public Problem {

public:

  /// Constructor for feedback control problems
  ControlProblem( DGM::ArgList &args_in, Table &table_in = Table(),
                  const DGM::Comm::Ptr comm_in = DGM::Comm::World );

  /// destructor
  ~ControlProblem() {
    cout << "~ControlProblem()" << endl;
  }

  /// virtual methods override
  virtual int solve();

private:

  State::Ptr      state;        ///< State solution
  Adjoint::Ptr    adjoint;      ///< Adjoint solution (is this needed)
  Control::Ptr    control;      ///< Control for this Problem
  Objective::Ptr  objective;    ///< Objective for this Problem
  Controller::Ptr controller;   ///< Controller for feedback control

};

} // namespace DGM

#endif // DGM_CONTROL_PROBLEM_HPP
