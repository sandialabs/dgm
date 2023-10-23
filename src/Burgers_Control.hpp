#ifndef REO_BURGERS_CONTROL_HPP
#define REO_BURGERS_CONTROL_HPP

/** \file Burgers_Control.hpp
    \brief Burgers Control declaration and implementation
    \author Scott Collis
*/

// system includes
#include <list>

// local includes
#include "State.hpp"
#include "Control.hpp"

namespace Reo {

/// Burgers Control class
class Burgers_Control: public Control {
 public:
  /// Constructor
  Burgers_Control(DGM::ArgList &args_, State *state_,
                  const DGM::Comm::Ptr comm_ = DGM::Comm::World) :
    Control(args_,state_,comm_) {
    comm->cout() << "Building Burgers_Control..." << std::endl;
    setup();
  }

  /// Copy constructor
  Burgers_Control(const Burgers_Control *in) : Control(in) {}
  virtual ~Burgers_Control(){}

  /// Clone the control
  virtual Control* clone() const {
    return new Burgers_Control(this);
  }
};

} // namespace Reo

#endif  // REO_BURGERS_CONTROL_HPP
