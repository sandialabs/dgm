/** \file FDM_Optimizer.cpp
    \brief Base class for all FDM optimization algorithms
    \author Bill Spotz
*/

#include "FDM_Optimizer.hpp"

namespace FDM
{

Optimizer::Optimizer(State *state_,
                     Adjoint *adjoint_,
                     Control::Ptr control_,
                     const DGM::Comm::Ptr comm_) :
  comm(comm_),
  ctl_comm(comm_),
  opt_stat(NULL),
  iter(1),
  state(state_),
  adjoint(adjoint_),
  control(control_)
{
  // comm->cout() << "Optimizer::Optimizer()" << endl;
}

Optimizer::~Optimizer()
{
  if (comm->verbosity() > 1)
    comm->cout() << "~Optimizer()" << endl;

  if (opt_stat)
    fclose(opt_stat);
}

} // namespace FDM
