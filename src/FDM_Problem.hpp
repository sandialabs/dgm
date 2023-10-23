#ifndef FDM_PROBLEM_HPP
#define FDM_PROBLEM_HPP

/** \file FDM_Problem.hpp
    \brief FDM::Problem interface
    \author Scott Collis
    \author Bill Spotz
*/

// FDM includes
#include "FDM_Types.hpp"

namespace FDM
{

//! FDM Problem
class Problem : public DTK::Problem
{
public:
  typedef Teuchos::RCP< Problem > Ptr;
};

}  // namespace FDM

#endif
