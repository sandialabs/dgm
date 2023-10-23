#ifndef DGM_ADJOINT_HPP
#define DGM_ADJOINT_HPP

/** \file Adjoint.hpp
    \brief Adjoint base class declaration
    \author Scott Collis
*/

// System includes
#include <iostream>
#include <string>

// DTK includes
#include "DTK.hpp"

// DGM includes
#include "Comm.hpp"
#include "Domain.hpp"
#include "vField.hpp"
#include "State.hpp"
#include "Control.hpp"
#include "DTK_InCore.tpp"

namespace DGM {

// forward declaration
class Objective;

/// Base class for Adjoint Domains
/** DGM::Domain derive off of this class to support adjoint computations. */
class Adjoint : public DTK::Adjoint<Control,Objective,vField,dVector,Scalar,
                                    Ordinal,Domain> {

  mutable Ordinal num_;    ///< The number of adjoint/gradient evaluations

protected:

  string name;             ///< The name of this Adjoint object

  int p_inc;               ///< Increment in polynomial order for this adjoint

  Ordinal npredict;        ///< Number of timesteps to optimize over

  const State *state_;     ///< State for which this is adjoint
  Objective *objective;    ///< Objectives (i.e. observations) for this Adjoint

  Control::Ptr control;    ///< Control
  Control::Ptr g_control;  ///< Gradient of objective functional w.r.t. control
  Control::Ptr p_control;  ///< Diagonal preconditioner
  Control::Ptr h_control;  ///< Hessian vector product

  vField Ustate;           ///< State Solution field

  string scratch;          ///< Path to scratch space
  Ordinal iter;            ///< Iteration index (default is 0)

  bool use_in_core;        ///< true activates the in-core adjoint storage

  /// Storage for in core database
  mutable DTK::InCore<Scalar,Ordinal,vField,Domain> in_core_storage;

public:

  /// Shared pointer to Adjoint
  typedef DGM::Shared<Adjoint>::Ptr Ptr;

  /// Constructor
  Adjoint(const State*, const int pinc=0);

  /// Destructor
  virtual ~Adjoint();

  /// Initialize the adjoint
  virtual void initialize();

  /// Default implementation sets the end condition from \c root.adj.ic file
  virtual void set_end_condition();

  /// Set end condition to a prescribed data at time \c t and timestep \c step
  /** @param[in] X values for the end condition
      @param[in] t time of the end condition
      @param[in] step time step at the end condition
  */
  virtual void set_end_condition(const dVector &X, const Scalar t=0.0,
                                 const Ordinal step=0);

  /// Defaults to undefined, must (if used) be supplied by derived class
  virtual void set(const int, const int=0) { DGM_UNDEFINED; }

  /// Compute the adjoint nsteps using supplied control and gradient
  virtual void compute(const Ordinal nsteps, Control::Ptr, Control::Ptr,
                       const Ordinal iteration=0);
#ifdef DGM_USE_TIME_REG
  /// Compute the adjoint using time-regularization
  virtual void compute(const Ordinal nsteps, Control::Ptr, Control::Ptr,
                       Control::Ptr, const Ordinal iteration=0);
#endif
  /// Compute the gradient given the adjoint and state solutions
  /** @param[in] A adjoint solution
      @param[in] S state solution
      @param[in] istep current time step
      @param[in] sstep current sub-step (optional)
  */
  virtual void computeGrad(vField &A, vField &S, Ordinal istep,
                           Ordinal sstep) { DGM_UNDEFINED; }

  /// Store the adjoint vField
  virtual void store(vField &, const Ordinal, const Ordinal=0);
  /// Load the adjoint vField
  virtual void load(vField &, const Ordinal, const Ordinal=0);
  /// Load the adjoint vField skipping the header
  virtual void load_field(vField &, const Ordinal, const Ordinal=0) const;

  /// Returns the Domain
  virtual const Domain* domain() const = 0;
  /// Returns the Domain
  virtual Domain* domain() = 0;

  /// Set the objective for this adjoint solution
  virtual void set_objective(Objective *obj) {objective=obj;}
  /// Returns the Objective
  virtual const Objective* get_objective() const { return objective; }
  /// Returns the Objective
  virtual Objective* get_objective() { return objective; }

  /// Returns the State
  // inline State* get_state() { return const_cast<State*>(state_); }
  /// Returns the State
  inline const State* get_state() const { return state_; }
  /// Accessor for the increment in polynomial order for this adjoint
  Ordinal get_p_inc() {return p_inc;}

  /// Sets the current iteration index
  void set_iter(const Ordinal i) {iter=i;}
  /// Resets the iteration index
  void reset_iter() {iter=0;}

  /// Set the preconditioner
  void set_preconditioner( Control::Ptr precond ) { p_control = precond; }

  /// Get the number of function evaluations
  Ordinal num() const { return num_; }
  /// Set the number of function evaluations
  void num(const Ordinal num) { num_=num; }

protected:

  /// Do not allow copy construction
  Adjoint(const Adjoint&) : num_(0), p_inc(0), npredict(0), state_(0),
    objective(0), Ustate(DGM::Comm::World,"Adjoint::Ustate"), iter(0), 
    use_in_core(false) { DGM_UNDEFINED; }

  /// Do not allow copy construction
  Adjoint(const Adjoint*) : num_(0), p_inc(0), npredict(0), state_(0), 
    objective(0), Ustate(DGM::Comm::World,"Adjoint::Ustate"),
    iter(0), use_in_core(false) { DGM_UNDEFINED; }

}; // class Adjoint

} // namespace DGM

#endif  // DGM_ADJOINT_HPP
