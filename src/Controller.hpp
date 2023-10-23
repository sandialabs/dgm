#ifndef DGM_CONTROLLER_HPP
#define DGM_CONTROLLER_HPP

/** \file  Controller.hpp
    \brief Feedback control base class declarations
    \author Scott Collis
*/

// standard libraries
#include <string>

// DGM includes
#include "Comm.hpp"
#include "State.hpp"
#include "Control.hpp"

namespace DGM {

/// Feedback Controller abstract base class
class Controller {

protected:

  const DGM::Comm::Ptr comm;  ///< communicator for this optimizer

public:

  /// constructor
  Controller( State::Ptr state_in, Control::Ptr control_in,
              const DGM::Comm::Ptr comm_in = DGM::Comm::World)
    : state(state_in), control(control_in), comm(comm_in) {
    comm->cout() << "Controller(...)" << endl;
  }

  /// destructor
  virtual ~Controller() {
    comm->cout() << "~Controller()" << endl;
  }

  // member function

  /// advances the solution using a control
  virtual Scalar advance() {
    state->initialize();
    control->initialize();

    state->set_initial_condition();
    // this currently only does open loop control.  What is needed is a way to
    // tell the state that it must query the controller to update the control
    // for every step.
    return state->advance( state->domain()->get_Nt(), control );
  }

  // data

  State::Ptr   state;    ///< the state
  Control::Ptr control;  ///< the control

  /// shared pointer to a Controller
  typedef DGM::Shared<Controller>::Ptr Ptr;
};

} // namespace DGM

#endif // DGM_CONTROLLER_HPP
