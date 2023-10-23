#ifndef REO_EULER_CONTROL_HPP
#define REO_EULER_CONTROL_HPP

/** \file  Euler_Control.hpp
    \brief Control class declaration for the 2d Euler equations
    \author Scott Collis
*/

// system includes
#include <list>

// DGM includes
#include "State.hpp"
#include "Control.hpp"
using namespace DGM;

namespace Reo {

/// Euler Control class
class Euler_Control: public Control {

 public:

  Euler_Control(DGM::ArgList &, State *,
                const DGM::Comm::Ptr = DGM::Comm::World);

  Euler_Control(const Euler_Control *);
  virtual ~Euler_Control(){}

  // override Control virtual functions
  virtual Control* clone() const {
    return new Euler_Control(this);
  }

};

} // namespace Reo

#endif  // REO_EULER_CONTROL_HPP
