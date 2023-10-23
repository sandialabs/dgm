#ifndef FDM_STATE_HPP
#define FDM_STATE_HPP

/** \file FDM_State.hpp
    \brief FDM::State interface
    \author Scott Collis
    \author Bill Spotz
*/

// DTK includes
#include "DTK_AtomicOps.hpp"

// FDM includes
#include "FDM_Types.hpp"
#include "FDM_Control.hpp"
#include "FDM_Objective.hpp"
#include "FDM_ObjFunc.hpp"
#include "FDM_Checkpoint.tpp"

namespace FDM
{

// Forward declarations
class Control;
class Objective;
class ObjFunc;
class Adjoint;
class Domain;

//! FDM State
class State : public DTK::State< Control,
                                 Objective,
                                 VectorField,
                                 ScalarVector,
                                 Scalar,
                                 Ordinal >,
              public DTK::AtomicOps< Scalar,
                                     Ordinal >
{
protected:
  Control::Ptr   control;
  Objective::Ptr objective;
  ObjFunc::Ptr   objfunc;
  mutable Checkpoint::Ptr checkpoint;

  /// Do not allow copy construction
  State(const State &s);

  /// Do not allow copy construction
  State(const State *s);

public:
  typedef Teuchos::RCP<State> Ptr;

  //ObjFunc::Ptr objfunc;  ///< Objective function (observations and penalties)

  /// Constructor
  State();

  /// Destructor
  virtual ~State();

  /// Return the Domain for this State
  virtual const Domain* domain() const = 0;

  /// Return the Domain for this State
  virtual Domain* domain() = 0;

  /// Sets the State Control pointer
  virtual void set_control(Control *ctrl);

  /// Return the Control for this State
  virtual const Control* get_control() const;

  /// Return the Control for this State
  virtual Control* get_control();

  /// Sets the State objective pointer
  virtual void set_objective(Objective *obj);

  /// Return the Objective for this State
  virtual Objective* get_objective();

  /// Return the Objective for this State
  virtual const Objective* get_objective() const;

  /// Initialize the AtomicOps base class
  virtual void atomic_initialize();

  /// Atomic advance
  virtual Scalar atomic_advance(const Ordinal nstep);

  /// Atomic advance
  virtual Scalar atomic_advance(const Ordinal lstep,
                                const Ordinal nstep);

};

}  // namespace FDM

#endif
