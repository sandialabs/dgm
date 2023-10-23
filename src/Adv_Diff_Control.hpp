#ifndef REO_ADV_DIFF_CONTROL_HPP
#define REO_ADV_DIFF_CONTROL_HPP

/** \file Adv_Diff_Control.hpp
    \brief Advection diffusion Control declaration and implementation
    \author Scott Collis
*/

// system includes
#include <list>

// local includes
#include "State.hpp"
#include "Control.hpp"

namespace Reo {

/// Control object for the Advection Diffusion equation
class Adv_Diff_Control: public Control {

 public:

  Adv_Diff_Control(DGM::ArgList &args_, State *state_,
                   const DGM::Comm::Ptr comm_ = DGM::Comm::World)
    : Control(args_,state_,comm_) {

    comm->cout() << "Building Adv_Diff_Control..." << std::endl;

    setup();
  }

  Adv_Diff_Control(const Adv_Diff_Control *in) : Control(in) {}
  virtual ~Adv_Diff_Control(){}

  // override Control virtual functions
  virtual DGM::Control * clone() const {
    return new Adv_Diff_Control(this);
  }

};

} // namespace Reo

#endif // REO_ADV_DIFF_CONTROL_HPP
