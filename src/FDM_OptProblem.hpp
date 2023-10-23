#ifndef FDM_OPTPROBLEM_HPP
#define FDM_OPTPROBLEM_HPP

/** \file FDM_OptProblem.hpp
    \brief FDM::OptProblem interface
    \author Scott Collis
    \author Bill Spotz
*/

// FDM includes
#include "FDM_Types.hpp"

namespace FDM
{

//! FDM OptProblem
class OptProblem : public DTK::Problem
{
public:
  typedef Teuchos::RCP< OptProblem > Ptr;
};

}  // namespace FDM

#endif
