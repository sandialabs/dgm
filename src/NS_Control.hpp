#ifndef REO_NS_CONTROL_HPP
#define REO_NS_CONTROL_HPP

/** \file  NS_Control.hpp
    \brief Navier-Stokes Control class

    \todo Remove this almost empty class
*/

// system includes
#include <list>

// DGM includes
#include "State.hpp"
#include "Control.hpp"

namespace Reo {

/// Navier-Stokes Control class
class NS_Control: public Control {

 public:

  NS_Control(DGM::ArgList &, State *,
             const DGM::Comm::Ptr = DGM::Comm::World);

  NS_Control(const NS_Control *);
  virtual ~NS_Control(){}

  // override Control virtual functions
  virtual Control* clone() const { return new NS_Control(this); }

};

} // namespace Reo

#endif  // REO_NS_CONTROL_HPP
