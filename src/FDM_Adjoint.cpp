/** \file FDM_Adjoint.cpp
    \brief FDM::Adjoint interface
    \author Scott Collis
    \author Bill Spotz
*/

// FDM includes
#include "FDM_Adjoint.hpp"

namespace FDM
{

/// Destructor
Adjoint::~Adjoint()
{
}

/// Set the objective function for this adjoint
void Adjoint::set_objective(Objective *obj)
{
  objective = obj;
}

}  // namespace FDM
