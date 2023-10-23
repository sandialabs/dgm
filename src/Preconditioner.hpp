#ifndef DGM_PRECONDITIONER_HPP
#define DGM_PRECONDITIONER_HPP

/** \file Preconditioner.hpp

    \brief Optimization preconditioner base class declaration and a basic
    Identity preconditioner
*/

// System includes
#include <string>

// DGM includes
#include "Types.hpp"
#include "State.hpp"
#include "Control.hpp"

namespace DGM {

/// Base class for Optimization preconditioner
/** A simple interface for a preconditioner for an optimization problem

    The apply() method must apply the action of the inverse approximate
    Hessian on the supplied Control vector \f[ \bX \leftarrow {\tilde
    \bH}^{-1} \bX \f] where \f$\tilde \bH\f$ is an approximation to the true
    reduced Hessian, \f$\bH\f$.  Note that we do not specify in what sense
    that the preconditioner approximates the true Hessian.  Instead, the
    preconditioner can and should be selected to improve the solution of the
    optimization problem.

    \todo It might make sense to put this in the Control or Optimizer
    namespace in the future.
*/
class Preconditioner {
public:
  /// Shared pointer to a preconditioner
  typedef DGM::Shared<Preconditioner>::Ptr Ptr;
  /// Constructor
  Preconditioner() {}
  /// Destructor
  virtual ~Preconditioner() {}
  /// Compute the preconditioner
  virtual void compute() = 0;
  /// Apply the preconditioner to a vector X in the control space
  virtual void apply(const Control::Ptr X, Control::Ptr pX) = 0;
};

/// Identity preconditioner
/** This is the simple, do-nothing Preconditioner. */
class IdentityPreconditioner : public Preconditioner {
public:
  /// Constructor
  IdentityPreconditioner() : Preconditioner() {}
  /// Destructor
  virtual ~IdentityPreconditioner() {}
  /// Compute the preconditioner
  virtual void compute() {}
  /// Apply the preconditioner to a vector X in the Control space
  virtual void apply(const Control::Ptr X, Control::Ptr pX) {}
};

} // namespace DGM

#endif // DGM_PRECONDITIONER_HPP
