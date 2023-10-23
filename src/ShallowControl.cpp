#ifndef DGM_REMOVE_FOR_RELEASE

/** \file  ShallowControl.cpp
    \brief Control class declaration for the 2d Shallow equations
    \author Vincent Mousseau
    \author S. Scott Collis
*/

// Reo includes
#include "ShallowControl.hpp"

namespace Reo {

// Constructor
ShallowControl::ShallowControl(DGM::ArgList &args_, State *state_,
                             const DGM::Comm::Ptr comm_ )
  : Control(args_,state_,comm_) {
  comm->cout() << "Building ShallowControl..." << std::endl;
  setup();
}

// Copy constructor
ShallowControl::ShallowControl( const ShallowControl *in) : Control(in) {}

} // namespace Reo

#else // DGM_REMOVE_FOR_RELEASE
// This capability is under development.
#endif // DGM_REMOVE_FOR_RELEASE
