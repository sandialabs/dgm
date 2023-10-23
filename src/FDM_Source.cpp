/** \file FDM_Source.cpp
    \brief FDM::Source interface
    \author Scott Collis
    \author Bill Spotz
*/

// FDM includes
#include "FDM_Source.hpp"

namespace FDM
{

/// Source Constructor
Source::Source(const std::string t) :
  DTK::Source< VectorField,
               ScalarVector,
               Scalar,
               Ordinal,
               Ctrl,
               Obs >(t)
{
}

/// Source Destructor
Source::~Source()
{
}

}  // namespace FDM
