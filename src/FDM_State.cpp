/** \file FDM_State.cpp
    \brief FDM::State interface
    \author Scott Collis
    \author Bill Spotz
*/

// FDM includes
#include "FDM_State.hpp"

namespace FDM
{

//=============================================================================
 
// Constructor
State::State() :
  control(),
  objective(),
  objfunc(),
  checkpoint()
{
#ifdef DGM_USE_GRIEWANK
  checkpoint = Checkpoint::Ptr(new Griewank(this));
#else
  checkpoint = Checkpoint::Ptr(new InCore());
#endif
}

//=============================================================================
 
// Destructor
State::~State()
{
}

//=============================================================================
 
// Sets the State Control pointer
void State::set_control(Control *ctrl)
{
  control = Teuchos::rcp(ctrl,false);
}

//=============================================================================
 
// Return the Control for this State
const Control* State::get_control() const
{
  return control.get();
}

//=============================================================================
 
// Return the Control for this State
Control* State::get_control()
{
  return control.get();
}

//=============================================================================
 
// Sets the State objective pointer
void State::set_objective(Objective *obj)
{
  objective = Teuchos::rcp(obj,false);
}

//=============================================================================
 
// Return the Objective for this State
Objective* State::get_objective()
{
  return objective.get();
}

//=============================================================================
 
// Return the Objective for this State
const Objective* State::get_objective() const
{
  return objective.get();
}

//=============================================================================
 
// Initialize the AtomicOps base class

// Currently, this must be implemented by the physics, although we are
// contemplating a defualt implementation here, assuming we can
// generalize the more generic TimeIntegrator interface.

void State::atomic_initialize()
{
  FDM_UNDEFINED;
}

//=============================================================================
 
// Checkpointing interface

// Currently, this must be implemented by the physics, although we are
// contemplating a defualt implementation here, assuming we can
// generalize the more generic TimeIntegrator interface.

Scalar State::atomic_advance(const Ordinal nstep)
{
  FDM_UNDEFINED;
  return 0.0;
}

//=============================================================================
 
// Checkpointing interface

// Currently, this must be implemented by the physics, although we are
// contemplating a defualt implementation here, assuming we can
// generalize the more generic TimeIntegrator interface.

Scalar State::atomic_advance(const Ordinal lstep,
                             const Ordinal nstep)
{
  FDM_UNDEFINED;
  return 0.0;
}

//=============================================================================
 
}  // namespace FDM
