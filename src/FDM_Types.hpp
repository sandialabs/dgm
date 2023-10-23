#ifndef FDM_TYPES_HPP
#define FDM_TYPES_HPP

//! \file FDM_Types.hpp
//! \brief Finite Difference data types
//! \author Bill Spotz
//! \author Scott Collis

// STL includes
#include <map>
#include <string>
#include <list>

// Teuchos includes
#include "Teuchos_RCP.hpp"
#include "Teuchos_Comm.hpp"

// Xpetra includes
// #include "Xpetra_Vector.hpp"

// DTK includes
#include "DTK.hpp"
#include "DTK_Types.hpp"

// CMC includes
#include "Vector.hpp"
#include "Matrix.hpp"
#include "Utils.hpp"

// Domi includes
#include "Domi_MDComm.hpp"
#include "Domi_MDMap.hpp"
#include "Domi_MDVector.hpp"

/// Macro used to stub in a unimplemented method
#define FDM_UNDEFINED std::cerr << "Undefined function: " \
  << __PRETTY_FUNCTION__ << std::endl; exit(1);

//! FDM provides basic support for parallel finite difference methods using
//! the DTK interface.
namespace FDM
{

//! Basic integer ordinal type
typedef DTK::Ordinal_t Ordinal;

//! Basic floating point scalar type
typedef DTK::Scalar_t Scalar;

//! Basic size type
typedef DTK::Size_t Size;

//! Serial scalar vector
typedef CMC::Vector< Scalar, Ordinal > ScalarVector;

//! Serial ordinal vector
typedef CMC::Vector< Ordinal, Ordinal > OrdinalVector;

//! Serial int vector
typedef CMC::Vector< int, Ordinal > IntVector;

//! \name Finite difference orders
//@{
const Scalar min_order =  2;  ///< minimum finite-difference order
const Scalar max_order = 12;  ///< maximum finite-difference order
//@}

/// \name Fourth-order central finite difference (staggered)
//@{
const Scalar c1_o4 =  9.0 /  8.0;          ///< 4th order coefficient at i
const Scalar c2_o4 = -1.0 / 24.0;          ///< 4th order coefficient at i+1
//@}
/// \name Sixth-order central finite difference (staggered)
//@{
const Scalar c1_o6 =  75.0 /  64.0;        ///< 6th order coefficient at i
const Scalar c2_o6 = -25.0 / 384.0;        ///< 6th order coefficient at i+1
const Scalar c3_o6 =   3.0 / 640.0;        ///< 6th order coefficient at i+2
//@}
/// \name Eighth-order central finite difference (staggered)
//@{
const Scalar c1_o8 = 1225.0 / 1024.0;      ///< 8th order coefficient at i
const Scalar c2_o8 = -245.0 / 3072.0;      ///< 8th order coefficient at i+1
const Scalar c3_o8 =   49.0 / 5120.0;      ///< 8th order coefficient at i+2
const Scalar c4_o8 =   -5.0 / 7168.0;      ///< 8th order coefficient at i+3
//@}
/// \name Tenth-order central finite difference (staggered)
//@{
const Scalar c1_o10 = 19854.0 /  16384.0;  ///< 10th order coefficient at i
const Scalar c2_o10 =  -735.0 /   8192.0;  ///< 10th order coefficient at i+1
const Scalar c3_o10 =   567.0 /  40960.0;  ///< 10th order coefficient at i+2
const Scalar c4_o10 =  -405.0 / 229376.0;  ///< 10th order coefficient at i+3
const Scalar c5_o10 =    35.0 / 294912.0;  ///< 10th order coefficient at i+4
//@}
/// \name Twelfth-order central finite difference (staggered)
//@{
const Scalar c1_o12 = 160083.0 /  131072.0; ///< 12th order coefficient at i
const Scalar c2_o12 = -12705.0 /  131072.0; ///< 12th order coefficient at i+1
const Scalar c3_o12 =  22869.0 / 1310720.0; ///< 12th order coefficient at i+2
const Scalar c4_o12 =  -5445.0 / 1835008.0; ///< 12th order coefficient at i+3
const Scalar c5_o12 =    847.0 / 2359296.0; ///< 12th order coefficient at i+4
const Scalar c6_o12 =    -63.0 / 2883584.0; ///< 12th order coefficient at i+5
//@}

//! Pointer to Teuchos::Comm
typedef Teuchos::RCP< const Teuchos::Comm< int > > CommPtr;

//! Pointer to Domi::MDComm
typedef Teuchos::RCP< const Domi::MDComm > MDCommPtr;

//! Pointer to Domi::MDMap
typedef Teuchos::RCP< const Domi::MDMap > MDMapPtr;

//! Pointer to Xpetra::Vector
// typedef Teuchos::RCP< Xpetra::Vector< Scalar, Ordinal > > VectorPtr;

//! Pointer to Domi::MDVector
typedef Teuchos::RCP< Domi::MDVector< Scalar > > MDVectorPtr;

} // namespace FDM

#endif  // FDM_TYPES_HPP
