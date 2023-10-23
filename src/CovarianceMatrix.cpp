/** \file CovarianceMatrix.cpp
    \brief Introduce objective weightings from Response JSON 
    \author Greg von Winckel 
*/

#include "CovarianceMatrix.hpp"

namespace DGM {

/*  Implementation moved to header as it kept leading to linker errors:
    undefined reference to `vtable for DGM::CovarianceMatrix_Linear'
    undefined reference to `vtable for DGM::CovarianceMatrix_Exponential'
 */

} // namespace DGM
