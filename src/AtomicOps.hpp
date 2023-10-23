#ifndef DGM_ATOMIC_OPS_HPP
#define DGM_ATOMIC_OPS_HPP

/** \file AtomicOps.hpp
    \brief Atomic operations base class declaration
    \author Scott Collis
*/

#include "DTK_AtomicOps.hpp"

namespace DGM {

/// Base class for Domains that support Atomic Operations
/** Any Domain that derives off this class can be used as the AtomicOps
    evaluation for Griewank storage. */
class AtomicOps : public DTK::AtomicOps<Scalar,Ordinal> {

  /// number of atomic advances
  mutable Ordinal numAdvances;

public:

  /// Constructor
  AtomicOps() : numAdvances(0) {}

  /// Destructor
  virtual ~AtomicOps() {}

  /// Atomic advance
  virtual Scalar atomic_advance(const Ordinal) = 0;

  /// Atomic advance
  virtual Scalar atomic_advance(const Ordinal, const Ordinal) = 0;

  /// Increment the number of advances
  void atomic_advances(const Ordinal t) const {
    numAdvances += t;
  }

  /// Return and reset the number of advances
  Ordinal atomic_advances() {
    const Ordinal t=numAdvances;
    numAdvances = 0;
    return t;
  }

};

} // namespace DGM

#endif  // DGM_ATOMIC_OPS_HPP
