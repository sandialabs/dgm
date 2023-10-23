#ifndef FDM_CHECKPOINT_TPP
#define FDM_CHECKPOINT_TPP

/** \file FDM_Checkpoint.tpp
    \brief FDM::Checkpoint interfaces
    \author Bill Spotz
    \author Scott Collis
*/

// DTK includes
#include "DTK_InCore.tpp"
#include "DTK_Griewank.tpp"

// FDM includes
#include "FDM_Types.hpp"
#include "FDM_Domain.hpp"

namespace FDM
{

// Forward declarations
class VectorField;
class Domain;

//! FDM Checkpoint class
typedef DTK::Checkpoint< Scalar,
                         Ordinal,
                         VectorField,
                         Domain > Checkpoint;

//! FDM InCore class
typedef DTK::InCore< Scalar,
                     Ordinal,
                     VectorField,
                     Domain > InCore;

//! FDM Griewank class
typedef DTK::Griewank< Scalar,
                       Ordinal,
                       VectorField,
                       Domain > Griewank;

}

#endif
