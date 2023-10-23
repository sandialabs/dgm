#ifndef DTK_TYPES_HPP
#define DTK_TYPES_HPP

/** \file DTK_Types.hpp
    \brief Basic type definitions for the DTK library
    \author Scott Collis
*/

#include <complex>
#include <stdint.h>

#ifdef DTK_USE_TEUCHOS_RCP
#include <Teuchos_RCP.hpp>
#else
#include <boost/shared_ptr.hpp>
#endif

// CMC includes
#include "Vector.hpp"
#include "Config.hpp"

namespace DTK {

/// \name Fundamental DTK types
//@{
#if defined(DTK_SCALAR_FLOAT32)
typedef float Scalar_t;
typedef float Real_t;
#elif defined(DTK_SCALAR_COMPLEX32)
typedef std::complex<float> Scalar_t;
typedef float Real_t;
#elif defined(DTK_SCALAR_COMPLEX64)
typedef std::complex<double> Scalar_t;
typedef double Real_t;
#else
/// The standard DTK scalar type
typedef double Scalar_t;
/// The standard DTK real type
typedef double Real_t;
#endif

#if defined(DTK_ORDINAL_INT64)
/// \brief The standard DTK ordinal (LocalSize) type when
/// DTK_ORDINAL_INT64 is defined.  This determines the maximum size a
/// local array can be on a single processor.
typedef int64_t Ordinal_t;
#elif defined(DTK_ORDINAL_SIZE_T)
/// \brief The standard DTK ordinal (LocalSize) type when
/// DTK_ORDINAL_SIZE_T is defined.  This determines the maximum size a
/// local array can be on a single processor.
typedef size_t Ordinal_t;
#elif defined(DTK_ORDINAL_UINT64)
/// \brief The standard DTK ordinal (LocalSize) type when
/// DTK_ORDINAL_UINT64 is defined.  This determines the maximum size a
/// local array can be on a single processor.
typedef uint64_t Ordinal_t;
#elif defined(DTK_ORDINAL_UINT32)
/// \brief The standard DTK ordinal (LocalSize) type when
/// DTK_ORDINAL_UINT32 is defined.  This determines the maximum size a
/// local array can be on a single processor.
typedef uint32_t Ordinal_t;
#elif defined(DTK_ORDINAL_UNSIGNED_LONG_LONG) || \
      defined(DTK_ORDINAL_LONG_LONG_UNSIGNED)
/// \brief The standard DTK ordinal (LocalSize) type when either
/// DTK_ORDINAL_UNSIGNED_LONG_LONG or DTK_ORDINAL_LONG_LONG_UNSIGNED
/// are defined.  This determines the maximum size a local array can
/// be on a single processor.
typedef unsigned long long Ordinal_t;
#elif defined(DTK_ORDINAL_UNSIGNED_LONG) || \
      defined(DTK_ORDINAL_LONG_UNSIGNED)
/// \brief The standard DTK ordinal (LocalSize) type when either
/// DTK_ORDINAL_UNSIGNED_LONG or DTK_ORDINAL_LONG_UNSIGNED are
/// defined.  This determines the maximum size a local array can be on
/// a single processor.
typedef unsigned long Ordinal_t;
#else
/// \brief The standard DTK ordinal (LocalSize) type (default is int).
/// This determines the maximum size a local array can be on a single
/// processor.
typedef int Ordinal_t;
#endif

#if defined(DTK_SIZE_INT64)
/// \brief The standard DTK size (GlobalSize) type when DTK_SIZE_INT64
/// is defined.  This determines the maximum size the a global array
/// can be across all processors.
typedef int64_t Size_t;
#elif defined(DTK_SIZE_SIZE_T)
/// \brief The standard DTK size (GlobalSize) type when
/// DTK_SIZE_SIZE_T is defined.  This determines the maximum size a
/// global array can be across all processors.
typedef size_t Size_t;
#elif defined(DTK_SIZE_UINT64)
/// \brief The standard DTK size (GlobalSize) type when
/// DTK_SIZE_UINT64 is defined.  This determines the maximum size a
/// global array can be across all processors.
typedef uint64_t Size_t;
#elif defined(DTK_SIZE_UINT32)
/// \brief The standard DTK size (GlobalSize) type when
/// DTK_SIZE_UINT32 is defined.  This determines the maximum size a
/// global array can be across all processors.
typedef uint32_t Size_t;
#elif defined(DTK_SIZE_LONG_LONG)
/// \brief The standard DTK size (GlobalSize) type when either
/// DTK_SIZE_UNSIGNED_LONG_LONG or DTK_SIZE_LONG_LONG_UNSIGNED are
/// defined.  This determines the maximum size a global array can be
/// across all processors.
typedef long long Size_t;
#elif defined(DTK_SIZE_UNSIGNED_LONG_LONG) || \
      defined(DTK_SIZE_LONG_LONG_UNSIGNED)
/// \brief The standard DTK size (GlobalSize) type when either
/// DTK_SIZE_UNSIGNED_LONG_LONG or DTK_SIZE_LONG_LONG_UNSIGNED are
/// defined.  This determines the maximum size a global array can be
/// across all processors.
typedef unsigned long long Size_t;
#elif defined(DTK_SIZE_UNSIGNED_LONG) || \
      defined(DTK_SIZE_LONG_UNSIGNED)
/// \brief The standard DTK size (GlobalSize) type when either
/// DTK_SIZE_UNSIGNED_LONG or DTK_SIZE_LONG_UNSIGNED are defined.
/// This determines the maximum size a global array can be across all
/// processors.
typedef unsigned long Size_t;
#else
/// \brief The standard DTK size (GlobalSize) type (default is int).
/// This determines the maximum size a global array can be across all
/// processors.
typedef int Size_t;
#endif
//@}

/// The standard DTK serial scalar vector
typedef CMC::Vector<Scalar_t,Ordinal_t> ScalarVector;

/// The standard DTK serial ordinal vector
typedef CMC::Vector<Ordinal_t,Ordinal_t> OrdinalVector;

/// Provide a generic shared pointer for DTK
template< class Type >
struct Shared {
#ifdef DTK_USE_TEUCHOS_RCP
  typedef Teuchos::RCP< Type > Ptr;       ///< Use Trilinos shared pointer
#else
  typedef boost::shared_ptr< Type > Ptr;  ///< Use Boost shared pointer
#endif
};

}  /// Namespace DTK

#endif
