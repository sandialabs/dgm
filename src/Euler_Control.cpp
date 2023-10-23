/** \file  Euler_Control.cpp
    \brief Control class declaration for the 2d Euler equations
    \author Scott Collis
*/

// Reo includes
#include "Euler_Control.hpp"

namespace Reo {

// Constructor
Euler_Control::Euler_Control(DGM::ArgList &args_, State *state_,
                             const DGM::Comm::Ptr comm_ )
  : Control(args_,state_,comm_) {

  comm->cout() << "Building Euler_Control..." << std::endl;

  setup();
}

// Copy constructor
Euler_Control::Euler_Control( const Euler_Control *in) : Control(in) {}

} // namespace Reo
