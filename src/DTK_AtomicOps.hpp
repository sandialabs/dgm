#ifndef DTK_ATOMIC_OPS_HPP
#define DTK_ATOMIC_OPS_HPP

/** \file DTK_AtomicOps.hpp
    \brief Atomic operations base class declaration
    \author Scott Collis
    \author Bill Spotz
*/

namespace DTK {

/// Base class for Domains that support Atomic Operations
/** Any Domain that derives off this class can be used as the AtomicOps
    evaluation for Griewank storage. */
template < typename Scalar, typename Ordinal >
class AtomicOps {

public:

  /// Constructor
  AtomicOps(){}

  /// Destructor
  virtual ~AtomicOps(){}

  /// Atomic initialization
  virtual void atomic_initialize() = 0;

  /// Atomic advance
  virtual Scalar atomic_advance(const Ordinal,
                                const Ordinal) = 0;

};

} // namespace DTK

#endif  // DTK_ATOMIC_OPS_HPP
