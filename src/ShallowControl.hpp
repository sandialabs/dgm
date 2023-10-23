#ifndef DGM_REMOVE_FOR_RELEASE

#ifndef REO_SHALLOW_CONTROL_HPP
#define REO_SHALLOW_CONTROL_HPP

/** \file  ShallowControl.hpp
    \brief Control class declaration for the 2d Shallow equations
    \author Vincent Mousseau
    \author S. Scott Collis
*/

// system includes
#include <list>

// DGM includes
#include "State.hpp"
#include "Control.hpp"
using namespace DGM;

namespace Reo {

/// Shallow Control class
class ShallowControl: public Control {
public:
  ShallowControl(DGM::ArgList &, State *,
                 const DGM::Comm::Ptr = DGM::Comm::World);

  ShallowControl(const ShallowControl *);
  virtual ~ShallowControl(){}

  // override Control virtual functions
  virtual Control* clone() const {
    return new ShallowControl(this);
  }
};

} // namespace Reo

#endif  // REO_SHALLOW_CONTROL_HPP

#else // DGM_REMOVE_FOR_RELEASE
// This capability is under development.
#endif // DGM_REMOVE_FOR_RELEASE
