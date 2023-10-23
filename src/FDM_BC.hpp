#ifndef FDM_BC_HPP
#define FDM_BC_HPP

/** \file FDM_BC.hpp
    \brief FDM::BC interface
    \author Scott Collis
    \author Bill Spotz
*/

// FDM includes
#include "FDM_Types.hpp"

namespace FDM
{

//! FDM BC class
typedef DTK::BC< VectorField,
                 ScalarVector,
                 Scalar,
                 Ordinal > BC;

}  // namespace FDM

#endif
