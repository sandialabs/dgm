#ifndef DGM_TYPES_HPP
#define DGM_TYPES_HPP

/** \file Types.hpp
    \brief Basic type definitions for the DGM library
    \author Scott Collis
*/

#ifdef DGM_DOXYGEN
/// Use this to turn off C++ assertions
#define NDEBUG
#endif

// system includes
#include <cassert>
#include <complex>
#include <limits>
#include <string>

// DGM configuration
#include "Config.hpp"

#ifdef DGM_USE_TEUCHOS_RCP
#include <Teuchos_RCP.hpp>
#else
#include <boost/version.hpp>
#include <boost/shared_ptr.hpp>
#endif

// DTK
#include "DTK_Types.hpp"

// load the CMC data structures
#include "Vector.hpp"
#include "Matrix.hpp"
#include "Utils.hpp"
#include "Array.hpp"

// include the hi-resolution timer
#include "Stopwatch.hpp"
using CMC::Stopwatch;

namespace DGM {

/// \name Fundamental DGM types
//@{
/// Define the standard DGM scalar type (could be real or complex)
typedef DTK::Scalar_t Scalar;

/// Define the standard DGM real type (must be real valued)
typedef DTK::Real_t Real;

/// Define the standard DGM integral type (used for LocalSize)
typedef DTK::Ordinal_t Ordinal;

/// Define the standard DGM size type (used for GlobalSize)
/** \note You should make sure that GlobalSize is >= in size to LocalSize. */
typedef DTK::Size_t Size;
//@}

/// Use the max allowable value to denote undefined status
template <typename T>
T undefined() { return std::numeric_limits<T>::max(); }

/// Check if value is defined
template <typename T>
bool defined(T i) { return i!=undefined<T>(); }

/// \name Standard DGM container types
/*! These define the standard types used in DGM for storing dense vectors
    matrices and multi-dimensional arrays */
//@{
typedef CMC::Vector<Scalar, Ordinal> dVector;            ///< dense vector
typedef CMC::Slice<Scalar, Ordinal> dSlice;              ///< vector slice
typedef CMC::Matrix<Scalar, Ordinal> dMatrix;            ///< dense matrix
typedef CMC::Matrix<float,  Ordinal> fMatrix;            ///< dense matrix
typedef CMC::Matrix<Ordinal,Ordinal> iMatrix;            ///< dense matrix
typedef CMC::Vector<float,  Ordinal> fVector;            ///< dense vector
typedef CMC::Vector<std::complex<Real>, Ordinal> cVector;///< complex vector
typedef CMC::Slice<std::complex<Real>, Ordinal> cSlice;  ///< complex slice
typedef CMC::Vector<Ordinal, Ordinal> iVector;           ///< ordinal vector
typedef CMC::Vector<Size, Ordinal> gVector;              ///< global vector
typedef CMC::Slice<Ordinal, Ordinal> iSlice;             ///< ordinal slice
typedef CMC::Array<Scalar, Ordinal> dArray;              ///< dense array
typedef CMC::Vector<int,Ordinal> intVector;              ///< integer vector
typedef CMC::Array<float, Ordinal> fArray;               ///< dense array
typedef CMC::Vector<Real, Ordinal> rVector;              ///< real vector
typedef CMC::Matrix<Real, Ordinal> rMatrix;              ///< real array
typedef CMC::Array<Real, Ordinal> rArray;                ///< real array
//@}

//============================================================================
//            S e t u p   D G M   s h a r e d   p o i n t e r s
//============================================================================

/// Provides a generic shared pointer for DGM
template<class Type> class Shared {
public:
#ifdef DGM_USE_TEUCHOS_RCP
  typedef Teuchos::RCP<Type> Ptr;       ///< Use Trilinos smart pointer
#else
  typedef boost::shared_ptr<Type> Ptr;  ///< Use Boost smart pointer
#endif
};

//============================================================================
//                         D G M   t y p e s
//============================================================================

template <typename T>
std::string type(T type=0) {
  if (typeid(type) == typeid(int32_t)) {
    return "int32";
  } else if (typeid(type) == typeid(uint32_t)) {
      return "uint32";
  } else if (typeid(type) == typeid(int64_t)) {
    return "int64";
  } else if (typeid(type) == typeid(uint64_t)) {
    return "uint64";
  } else if (typeid(type) == typeid(size_t)) {
    if (sizeof(type)==4)
      return "uint32";
    else if (sizeof(type)==8)
      return "uint64";
  } else if (typeid(type) == typeid(unsigned long )) {
    if (sizeof(type)==8) return "uint64";
    else if (sizeof(type)==4) return "uint32";
  } else if (typeid(type) == typeid(long long)) {
    if (sizeof(type)==8) return "int64";
  } else if (typeid(type) == typeid(unsigned long long)) {
    if (sizeof(type)==8) return "uint64";
  } else if (typeid(type) == typeid(float)) {
    return "float32";
  } else if (typeid(type) == typeid(double)) {
    return "float64";
  }
  return "unknown";
}

} // namespace DGM

#endif  // DGM_TYPES_HPP
