#ifndef CMC_UTILS_HPP
#define CMC_UTILS_HPP

/** \file Utils.hpp
    \brief CMC utilities including partial BLAS and LAPACK interfaces
    \author Scott Collis
    \copyright (c)2003 Rice University
    \copyright (c)2014 Sandia National Laboratories

    This provides BLAS and LAPACK interfaces for concrete CMC::Vector<double>
    and CMC::Slice<double>.
*/

// system includes
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <cassert>
#include <limits>
#include <stdexcept>

// Setup for x86 vector intrinsics
#if defined(CMC_USE_AVX) && defined(__AVX__)
#include <emmintrin.h>  // SSE2
#include <immintrin.h>  // AVX
#include <x86intrin.h>  // Other (FMA4)
#ifdef __FMA__
#include <fmaintrin.h>  // FMA
#endif
#if defined(__GNUC__) || defined(__PGI)
#define ALIGN16 __attribute__((__aligned__(16)))
#define ALIGN32 __attribute__((__aligned__(32)))
#else
#define ALIGN16 __declspec(align(16))
#define ALIGN32 __declspec(align(32))
#endif
#endif

// CBLAS AND CLAPACK interface
extern "C" {
#ifdef CMC_USE_MKL
#include "mkl.h"
#else
#include "cblas.h"
#endif
}
#ifdef CMC_USE_INTERNAL_CLAPACK
// Use the CMC version of clapack_* routines
#include "clapack.hpp"
#define CLAPACK(name) clapack_##name
#elif CMC_USE_LAPACKE
extern "C" {
// Use LAPACKE from OpenBLAS
#include "lapacke.h"
}
#define CLAPACK(name) LAPACKE_##name
#else
extern "C" {
// Use the ATLAS clapack_* routines
#include "clapack.h"
}
#define CLAPACK(name) clapack_##name
#endif

// CMC includes
#include "Slice.hpp"
#include "Vector.hpp"
#include "Matrix.hpp"

// DGM specific options shouldn't really be here as this code
// should be usable in other, non-DGM applications.  So, are replaced by
// CMC_USE_TEUCHOS_LAPACK and CMC_USE_KOKKOS if set
#if defined(DGM_USE_KOKKOS) && !defined(CMC_USE_KOKKOS)
#define CMC_USE_KOKKOS
#endif

#ifdef CMC_USE_TEUCHOS_LAPACK
#include "Teuchos_LAPACK.hpp"
#endif

#ifdef CMC_USE_KOKKOS
#include "GpGpu.hpp"
#endif

// Concise Math Classes namespace
namespace CMC {

namespace {

/// Make sure that integral types are within range for int
template <typename T>
void checkInt(T N) {
  using std::numeric_limits;
#ifdef CMC_CHECK_INT
  assert( (N >= (T)0) && (N <= (T)numeric_limits<int>::max()) );
#endif
}

/// Cast integral types to int but make sure that are within range
template <typename T>
int castInt(T N) {
  using std::numeric_limits;
  using std::range_error;
#ifdef CMC_CHECK_INT
  if (numeric_limits<T>::is_signed)
    if (N<(T)numeric_limits<int>::min())
      throw range_error("Integral type is less than min int");
  if (N>(T)numeric_limits<int>::max())
    throw range_error("Integral type is greater than max int");
#endif
  return static_cast<int>(N);
}

/// Cast integral types to unsinged but make sure that are within range
template <typename T>
unsigned castUnsigned(T N) {
  using std::numeric_limits;
  using std::range_error;
#ifdef CMC_CHECK_INT
  //if (numeric_limits<T>::is_signed)
  //  if (N<(T)0)
  //    throw std::range_error("Integral type is less than zero");
  if (N>(T)numeric_limits<unsigned>::max())
    throw range_error("Integral type is greater than max unsigned");
#endif
  return static_cast<unsigned>(N);
}

}  // anonomous namespace

//------------------------------------------------------------------------
//
// CMC Interface to CBLAS and CLAPACK (e.g. ATLAS)
//
//------------------------------------------------------------------------

/// Returns the sign of the argument
template <class Scalar>
Scalar sgn(Scalar x) { return (x<0) ? Scalar(-1) : Scalar(1); }

/// approximately equal
template <class Scalar>
bool approx( const Scalar x, const Scalar y,
             const Scalar REL, const Scalar ABS ) {
  using std::abs;
  const Scalar a = abs(x-y);
  if ((REL*abs(x) < a || ABS < a))
    return false;
  else
    return true;
}

/// templated absolute value of a CMC::Vector
template <class Scalar, class Ordinal>
inline void abs( Vector<Scalar,Ordinal> &X ) {
  using std::fabs;
#ifdef CMC_CHECK_BOUNDS
  assert(X.size()>0);
#endif
  for (Ordinal i=0; i<X.size(); i++) X[i] = fabs(X[i]);
}

/// absolute value of a CMC::Vector<double>
template <class Ordinal>
inline void abs( Vector<double,Ordinal> &X ) {
  using std::fabs;
#ifdef CMC_CHECK_BOUNDS
  assert(X.size()>0);
#endif
  for (Ordinal i=0; i<X.size(); i++) X[i] = fabs(X[i]);
}

/// return the location of the maximum element
template<typename Ordinal>
inline Ordinal id_max( const Vector<double,Ordinal> &X ) {
#ifdef CMC_CHECK_BOUNDS
  assert(X.size()>0);
#endif
  return cblas_idamax( X.size(), X.data(), 1 );
}

/// return the location of the maximum element
template<typename Ordinal>
inline Ordinal id_max( const Slice<double,Ordinal> X ) {
#ifdef CMC_CHECK_BOUNDS
  assert(X.size()>0);
#endif
  return cblas_idamax( X.size(), X.data(), X.stride() );
}

/// return the maximum entry
template<typename Ordinal>
inline double maximum( const Vector<double,Ordinal> &X ) {
  return X[id_max(X)];
}

/// return the maximum entry
template<typename Ordinal>
  inline double maximum( const Slice<double,Ordinal> X ) {
  return X[id_max(X)];
}

/// return index of the minimum entry
template<typename Scalar, typename Ordinal>
inline Ordinal id_min(const Vector<Scalar,Ordinal> &X) {
  const Ordinal n = X.size();
  if(!n) return 0;
  Ordinal cnt = 0;
  for(Ordinal i=1; i<n;++i) cnt = (X[i] < X[cnt]) ? i: cnt;
  return cnt;
}

/// return the minimum entry
template<typename Scalar, typename Ordinal>
inline Ordinal minimum(const Vector<Scalar,Ordinal> &X) {
  return X[id_min(X)];
}

/// return the maximum absolute value of a vector
template<typename Ordinal>
inline double norm_inf(const Vector<double,Ordinal> &X) {
  using std::fabs;
  const Ordinal n = X.size();
  if(!n) return 0;
  Ordinal cnt=0;
  for(Ordinal i=1; i<n;++i) cnt = (fabs(X[i]) > fabs(X[cnt])) ? i: cnt;
  return fabs(X[cnt]);
}

/// rotate the input vector
template<typename Ordinal>
inline void rotate( Vector<double,Ordinal> &X, Vector<double,Ordinal> &Y,
                    const double c, const double s ) {
#ifdef CMC_CHECK_BOUNDS
  assert(X.size()==Y.size());
#endif
  checkInt(X.size());
  cblas_drot( (int)X.size(), X.data(), 1, Y.data(), 1, c, s );
}

/// return the dot product
template<typename Ordinal>
inline double dot( const Vector<double,Ordinal> &X,
                   const Vector<double,Ordinal> &Y ) {
#ifdef CMC_CHECK_BOUNDS
  assert(X.size()==Y.size());
#endif
  checkInt(X.size());
#ifndef CMC_USE_KOKKOS
  return cblas_ddot( (int)X.size(), X.data(), 1, Y.data(), 1 );
#else
  using DGM::GpGpu::dot;
  return dot(X.size(), X.data(), Y.data(), 1, 1);
#endif
}

/// return the dot product
template<typename Ordinal>
inline float dot( const Vector<float,Ordinal> &X,
                  const Vector<float,Ordinal> &Y ) {
#ifdef CMC_CHECK_BOUNDS
  assert(X.size()==Y.size());
#endif
  checkInt(X.size());
#ifndef CMC_USE_KOKKOS
  return cblas_sdot( (int)X.size(), X.data(), 1, Y.data(), 1 );
#else
  using DGM::GpGpu::dot;
  return dot(X.size(), X.data(), Y.data(), 1, 1);
#endif
}

/// return the dot product
template<typename Ordinal>
inline double dot( const Slice<double,Ordinal> &X,
                   const Vector<double,Ordinal> &Y ) {
#ifdef CMC_CHECK_BOUNDS
  assert(X.size()==Y.size());
#endif
#ifndef CMC_USE_KOKKOS
  checkInt(X.size());
  checkInt(X.stride());
  return cblas_ddot( (int)X.size(), X.data(), (int)X.stride(), Y.data(), 1 );
#else
  using DGM::GpGpu::dot;
  return dot(X.size(), X.data(), Y.data(), X.stride(), 1);
#endif
}

/// return the dot product
template<typename Ordinal>
inline double dot( const Vector<double,Ordinal> &X,
                   const Slice<double,Ordinal> Y ) {
#ifdef CMC_CHECK_BOUNDS
  assert(X.size()==Y.size());
#endif
#ifndef CMC_USE_KOKKOS
  checkInt(X.size());
  checkInt(Y.stride());
  return cblas_ddot( (int)X.size(), X.data(), 1, Y.data(), (int)Y.stride() );
#else
  using DGM::GpGpu::dot;
  return dot(X.size(), X.data(), Y.data(), 1, Y.stride());
#endif
}

/// return the dot product
template<typename Ordinal>
inline double dot( const Slice<double,Ordinal> X,
                   const Slice<double,Ordinal> Y ) {
#ifdef CMC_CHECK_BOUNDS
  assert(X.size()==Y.size());
#endif
#ifndef CMC_USE_KOKKOS
  return cblas_ddot( X.size(), X.data(), X.stride(), Y.data(), Y.stride() );
#else
  using DGM::GpGpu::dot;
  return dot(X.size(), X.data(), Y.data(), X.stride(), Y.stride());
#endif
}

/// returns the sum of all vector elements
template<typename Ordinal>
inline double sum( const Vector<double,Ordinal> &X ) {
#ifdef CMC_CHECK_BOUNDS
  assert(X.size()>0);
#endif
  checkInt(X.size());
  return cblas_dasum( (int)X.size(), X.data(), 1 );
}

/// scale a slice or a vector by a Scalar
template <typename Scalar, typename DEST_VEC >
inline void scale( const Scalar alpha, DEST_VEC &X ) {
  typedef typename DEST_VEC::size_type size_type;
  const size_type N = X.size();
  for (size_type i=0; i<N; i++) X[i] *= alpha;
}

/// scale a slice or a vector by a Scalar
template <typename DEST_VEC >
inline void scale( const double alpha, DEST_VEC &X ) {
  typedef typename DEST_VEC::size_type size_type;
  const size_type N = X.size();
  checkInt(N);
  checkInt(X.stride());
  cblas_dscal( (int)N, alpha, X.data(), (int)X.stride() );
}

/// scale a slice or a vector by a Scalar
template <typename DEST_VEC >
inline void scale( const float alpha, DEST_VEC &X ) {
  typedef typename DEST_VEC::size_type size_type;
  const size_type N = X.size();
  cblas_sscal( (int)N, alpha, X.data(), X.stride() );
}

/// axpy for double vectors
template <typename Ordinal>
void axpy(const double a, const Vector<double,Ordinal> &X,
          const Vector<double,Ordinal> &Y, Vector<double,Ordinal> &Z) {
  daxpy(a,X,Y,Z);
}

/// in place axpy for double vectors
template <typename Ordinal>
void axpy(const double a, const Vector<double,Ordinal> &X,
          Vector<double,Ordinal> &Y) {
  daxpy(a,X,Y);
}

/// put a Scalar into a slice or a vector
template <typename Scalar, typename DEST_VEC>
inline void set( const Scalar alpha, DEST_VEC &X ) {
  typedef typename DEST_VEC::size_type Ordinal;
  const Ordinal N = X.size();
  for (Ordinal i=0; i<N; i++) X[i] = (typename DEST_VEC::value_type)alpha;
}

/// Add two double vectors: y += x
template <typename Ordinal>
inline void dvadd( const Vector<double,Ordinal> &X,
                         Vector<double,Ordinal> &Y ) {
  const Ordinal N = Y.size();
#ifdef CMC_CHECK_BOUNDS
  assert(N==X.size());
#endif
#ifdef CMC_USE_ARRAY
  for (Ordinal i=0; i<N; i++) Y[i] += X[i];
#else
  checkInt(N);
  cblas_daxpy( (int)N, 1.0, X.data(), 1, Y.data(), 1 );
#endif
}

/// Add two double slices
template<typename Ordinal>
inline void dvadd( const Slice<double,Ordinal> X, Slice<double,Ordinal> Y ) {
#ifdef CMC_CHECK_BOUNDS
  assert(X.size()==Y.size());
#endif
  cblas_daxpy( X.size(), 1.0, X.data(), X.stride(), Y.data(), Y.stride() );
}

/// Add a double vector to a double slice
template<typename Ordinal>
inline void dvadd( const Vector<double,Ordinal> &X, Slice<double,Ordinal> Y ) {
#ifdef CMC_CHECK_BOUNDS
  assert(X.size()==Y.size());
#endif
  checkInt(X.size());
  checkInt(Y.stride());
  cblas_daxpy( (int)X.size(), 1.0, X.data(), 1, Y.data(), (int)Y.stride() );
}

/// Add a double slice to a double vector
template<typename Ordinal>
inline void dvadd( const Slice<double,Ordinal> X, Vector<double,Ordinal> &Y ) {
#ifdef CMC_CHECK_BOUNDS
  assert(X.size()==Y.size());
#endif
  cblas_daxpy( X.size(), 1.0, X.data(), X.stride(), Y.data(), 1 );
}

/// Subtract two vectors: y -= x
template <class SRC_VEC, class DEST_VEC>
inline void dvsub( const SRC_VEC &X, DEST_VEC &Y ) {
  typedef typename DEST_VEC::size_type Ordinal;
  const Ordinal N = Y.size();
#ifdef CMC_CHECK_BOUNDS
  assert(N==X.size());
#endif
  for (Ordinal i=0; i<N; i++) Y[i] -= X[i];
}

/// Subtract two vectors: y -= x
template <typename Ordinal>
inline void dvsub(const Vector<double,Ordinal> &X,
                  Vector<double,Ordinal> &Y ) {
  const Ordinal N = Y.size();
#ifdef CMC_CHECK_BOUNDS
  assert(N==X.size());
#endif
#ifdef CMC_USE_ARRAY
  for (Ordinal i=0; i<N; i++) Y[i] -= X[i];
#else
  checkInt(N);
  checkInt(X.stride());
  checkInt(Y.stride());
  cblas_daxpy((int)N, -1.0, X.data(), (int)X.stride(), Y.data(),
              (int)Y.stride() );
#endif
}

/// Computes the elementwise maximum of two vectors
template<typename Ordinal>
inline void dvmax( const Vector<double,Ordinal> &X,
                   const Vector<double,Ordinal> &Y,
                   Vector<double,Ordinal> &Z) {
  const Ordinal N = Y.size();
#ifdef CMC_CHECK_BOUNDS
  assert(N==X.size());
  assert(N==Z.size());
#endif
  for (Ordinal i=0; i<N; i++) Z[i] = std::max(X[i],Y[i]);
}

/// Hadamard multiply (elementwise) two double vectors: y *= x
template <typename Ordinal>
inline void dvhmult( const Vector<double,Ordinal> &X,
                           Vector<double,Ordinal> &Y ) {
  const Ordinal N = Y.size();
#ifdef CMC_CHECK_BOUNDS
  assert(N==X.size());
#endif
  for (Ordinal i=0; i<N; i++) Y[i] *= X[i];
  /// Note: this could be implemented in terms of multiplication with
  /// a diagonal matrix using the BLAS level 2 function dsbmv, which 
  /// performs symmetric, banded, matrix-vector multiplication.  
  /// An new wrapper function cblas_dsbmv would need to be added. 
}

//==============================================================================

/// Add two generalized vectors and place in a destination vector
template <class SRC1_VEC, class SRC2_VEC, class DEST_VEC>
inline void dvadd( const SRC1_VEC &X, const SRC2_VEC &Y, DEST_VEC &Z) {
  typedef typename DEST_VEC::size_type Ordinal;
  const Ordinal N = Y.size();
#ifdef CMC_CHECK_BOUNDS
  assert(N==X.size());
  assert(N==Z.size());
#endif
  if (1==X.stride() && 1==Y.stride() && 1==Z.stride()) {
    typedef typename DEST_VEC::value_type Scalar;
    Scalar *px = X.ptr(), *py = Y.ptr(), *pz = Z.ptr();
    for (Ordinal i=0; i<N; i++) { *pz = *px + *py; px++; py++; pz++; }
  } else {
    for (Ordinal i=0; i<N; i++) Z[i] = X[i] + Y[i];
  }
}

/// Add two double vectors and place in a destination vector
template<typename Ordinal>
inline void dvadd(const Vector<double,Ordinal> &X,
                  const Vector<double,Ordinal> &Y,
                  Vector<double,Ordinal> &Z ) {
  const Ordinal N = Y.size();
#ifdef CMC_CHECK_BOUNDS
  assert(X.size()==N);
  assert(Y.size()==N);
  assert(X.ptr()!=Z.ptr() /* Input X and output Z may not be aliased */);
#endif
  if (Y.ptr()!=Z.ptr()) cblas_dcopy( N,      Y.data(), Y.stride(), Z.data(), Z.stride() );
  cblas_daxpy( N, 1.0, X.data(), X.stride(), Z.data(), Z.stride() );
}

/// Add three general vectors
template <class SRC1_VEC, class SRC2_VEC, class SRC3_VEC, class DEST_VEC>
inline void dvadd(const SRC1_VEC &X, const SRC2_VEC &Y, const SRC3_VEC &Z,
                  DEST_VEC &W) {
  typedef typename DEST_VEC::size_type Ordinal;
  const Ordinal N = X.size();
#ifdef CMC_CHECK_BOUNDS
  assert(N==Y.size());
  assert(N==Z.size());
  assert(N==W.size());
#endif
  for (Ordinal i=0; i<N; i++) W[i] = X[i] + Y[i] + Z[i];
}

/// Add three double vectors
template <typename Ordinal>
inline void dvadd(const Vector<double,Ordinal> &X,
                  const Vector<double,Ordinal> &Y,
                  const Vector<double,Ordinal> &Z,
                  Vector<double,Ordinal> &W) {
  const Ordinal N = X.size();
#ifdef CMC_CHECK_BOUNDS
  assert(N==Y.size());
  assert(N==Z.size());
  assert(N==W.size());
  assert(X.ptr()!=W.ptr() /* Input X and output W may not be aliased */);
#endif
#ifdef CMC_USE_ARRAY
  for (Ordinal i=0; i<N; i++) W[i] = X[i] + Y[i] + Z[i];
#else
  checkInt(N);
  cblas_dcopy( N,      X.data(), X.stride(), W.data(), W.stride() );
  cblas_daxpy( N, 1.0, Y.data(), Y.stride(), W.data(), W.stride() );
  cblas_daxpy( N, 1.0, Z.data(), Z.stride(), W.data(), W.stride() );
#endif
}

/// Sum three double vectors
template<typename Ordinal>
inline void dvsum( const Vector<double,Ordinal> &X,
                   const Vector<double,Ordinal> &Y,
                   Vector<double,Ordinal> &Z) {
  const Ordinal N = Y.size();
#ifdef CMC_CHECK_BOUNDS
  assert(N==X.size());
  assert(N==Z.size());
  assert(X.ptr()!=Z.ptr() /* Input X and output Z may not be aliased */);
#endif
#ifdef CMC_USE_ARRAY
  for (Ordinal i=0; i<N; i++) Z[i] += X[i] + Y[i];
#else
  checkInt(N);
  cblas_daxpy( (int)N, 1.0, Y.data(), Y.stride(), Z.data(), Z.stride() );
  cblas_daxpy( (int)N, 1.0, X.data(), X.stride(), Z.data(), Z.stride() );
#endif
}

/// Copy one vector to another
template<class SRC_VEC, class DEST_VEC>
inline void copy( const SRC_VEC &X, DEST_VEC &Y ) {
  typedef typename DEST_VEC::size_type Ordinal;
  const Ordinal N = X.size();
#ifdef CMC_CHECK_BOUNDS
  assert(X.size()==Y.size());
#endif
  for (Ordinal i=0; i<N; i++) { Y[i] = X[i]; }
}

/// Copy a double vector to another double vector
template<typename Ordinal>
inline void copy( const Vector<double,Ordinal> &X, Vector<double,Ordinal> &Y ) {
#ifdef CMC_CHECK_BOUNDS
  assert(X.size()==Y.size());
#endif
  checkInt(X.size());
  checkInt(X.stride());
  checkInt(Y.stride());
  cblas_dcopy((int)X.size(),X.data(),(int)X.stride(),Y.data(),(int)Y.stride());
}

/// Copy one double vector to another double vector
template <typename Ordinal>
inline void dvcopy(const Vector<double,Ordinal> &X,
                   Vector<double,Ordinal> &Y ) {
  copy(X,Y);
}

/// general Vector add
template <class Scalar, class Ordinal>
inline void add( const Vector<Scalar,Ordinal> &X, Vector<Scalar,Ordinal> &Y ) {
  const Ordinal N = Y.size();
#ifdef CMC_CHECK_BOUNDS
  assert(N==X.size());
#endif
  for (Ordinal i=0; i<N; i++) Y[i] += X[i];
}

/// specialized Vector<double,Ordinal> add
template <class Ordinal>
inline void add( const Vector<double,Ordinal> &X, Vector<double,Ordinal> &Y ) {
  dvadd( X, Y );
}

/// Subtract vectors:  Z = x - y
template <class SRC1_VEC, class SRC2_VEC, class DEST_VEC>
inline void dvsub( const SRC1_VEC &X, const SRC2_VEC &Y, DEST_VEC &Z ) {
  typedef typename DEST_VEC::size_type size_type;
  const size_type N = Z.size();
#ifdef CMC_CHECK_BOUNDS
  assert(N==X.size());
  assert(N==Y.size());
#endif
  if (1==X.stride() && 1==Y.stride() && 1==Z.stride()) {
    double *px = X.ptr();
    double *py = Y.ptr();
    double *pz = Z.ptr();
    for (size_type i=0; i<N; i++) { *pz = *px - *py; px++; py++; pz++; }
  } else {
    for (size_type i=0; i<N; i++) { Z[i] = X[i] - Y[i]; }
  }
}

/// Subtract vectors:  Z = x - y (double)
template <class Ordinal>
inline void dvsub(const Vector<double,Ordinal> &X,
                  const Vector<double,Ordinal> &Y,
                  Vector<double,Ordinal> &Z) {
  const Ordinal N = Z.size();
#ifdef CMC_CHECK_BOUNDS
  assert(N==X.size());
  assert(N==Y.size());
  assert(X.ptr()!=Z.ptr() /* Input X and output Z may not be aliased */);
#endif
#ifdef CMC_USE_ARRAY
  for (Ordinal i=0; i<N; i++) Z[i] = X[i] - Y[i];
#else
  checkInt(N);
  cblas_dcopy( (int)N,       X.data(), X.stride(), Z.data(), Z.stride() );
  cblas_daxpy( (int)N, -1.0, Y.data(), Y.stride(), Z.data(), Z.stride() );
#endif
}

/// Elementwise square a vector:  x = x^2 (elementwise)
template<typename Scalar, typename Ordinal>
inline void square( Vector<Scalar,Ordinal> &X) {
  for (Ordinal i=0; i<X.size(); i++) X[i] *= X[i];
}

/// Elementwise power of a vector:  x = x^n (elementwise)
template<typename Scalar, typename Ordinal>
inline void vpow( Vector<Scalar,Ordinal> &X, Ordinal n) {
  Vector<Scalar,Ordinal> Z(X.size());
  for (Ordinal i=0;i<Z.size();i++)Z[i]=X[i];
  for (Ordinal j=1; j<n; ++j){
    for (Ordinal i=0; i<Z.size(); i++)
      Z[i] *= X[i];
  }
}

/// Elementwise power of a vector:  z = x^n (elementwise)
template<typename Scalar, typename Ordinal>
inline void vpow( Vector<Scalar,Ordinal> &X, Ordinal n,
                  Vector<Scalar,Ordinal> &Z) {
  for (Ordinal i=0; i<Z.size(); i++)Z[i]=X[i];
  for (Ordinal j=1; j<n; ++j){
    for (Ordinal i=0; i<Z.size(); i++)
      Z[i] *= X[i];
  }
}

/// Elementwise multiply two vectors:  y *= x (elementwise)
template <class SRC_VEC, class DEST_VEC>
inline void dvmul( const SRC_VEC &X, DEST_VEC &Y ) {
  typedef typename SRC_VEC::size_type size_type;
  const size_type N = Y.size();
#ifdef CMC_CHECK_BOUNDS
  assert(N==X.size());
#endif
  if (1==X.stride() && 1==Y.stride()) {
    const typename SRC_VEC::value_type *px = X.ptr();
    typename SRC_VEC::value_type *py = Y.ptr();
    for (size_type i=0; i<N; i++) { *py *= *px; py++; px++; }
  } else {
    for (size_type i=0; i<N; i++) Y[i] *= X[i];
  }
}

/// Explicit instantiation for double
template <typename Ordinal>
inline void dvmul(const Vector<double,Ordinal> &X, Vector<double,Ordinal> &Y) {
  const Ordinal N = Y.size();
#if defined(CMC_USE_AVX) && defined(__AVX__)
  const Ordinal lowerN = N & ~3UL;
  double *px=X.ptr(), *py=Y.ptr();
  for (Ordinal i=0; i<lowerN; i+=4, px+=4, py+=4) {
    __m256d ymm0 = _mm256_loadu_pd(px);
    __m256d ymm1 = _mm256_loadu_pd(py);
    __m256d ymm3 = _mm256_mul_pd(ymm0,ymm1);
    _mm256_storeu_pd(py,ymm3);
  }
  if (lowerN<N) {
    double *px=X.ptr()+lowerN, *py=Y.ptr()+lowerN;
    for (Ordinal i=lowerN; i<N; i++, px++, py++) { *py *= *px; }
  }
#else
#if 0
  // this is simple but slow
  for (Ordinal i=0; i<N; i++) Y[i] *= X[i];
#else
  // this is faster since it doesn't have to use operator[]
  const double *px = X.ptr(); double *py = Y.ptr();
  for (Ordinal i=0; i<N; i++) { *py *= *px; py++; px++; }
#endif
#endif
}

/// Multiply two vectors:  Y *= X (elementwise)(strided)
template <class SRC_VEC, class DEST_VEC>
inline void dvmul( const SRC_VEC &X, DEST_VEC &Y,
                   const typename DEST_VEC::size_type stride) {
  typedef typename DEST_VEC::size_type size_type;
  const size_type N = X.size();
#ifdef CMC_CHECK_BOUNDS
  assert(stride*N==Y.size());
#endif
  size_type k=0;
  for (size_type j=0; j<stride; ++j) {
    for (size_type i=0; i<N; ++i) {
      Y[k] *= X[i];
      ++k;
    }
  }
}

/// Multiply two vectors:  z = x * y (elementwise)
template <class SRC1_VEC, class SRC2_VEC, class DEST_VEC>
inline void dvmul( const SRC1_VEC &X, const SRC2_VEC &Y, DEST_VEC &Z) {
  typedef typename DEST_VEC::size_type size_type;
  const size_type N = Z.size();
#ifdef CMC_CHECK_BOUNDS
  assert(N==X.size());
  assert(N==Y.size());
#endif
  if (1==X.stride() && 1==Y.stride() && 1==Z.stride() ) {
    const typename SRC1_VEC::value_type *x=X.data();
    const typename SRC2_VEC::value_type *y=Y.data();
    typename       DEST_VEC::value_type *z=Z.data();
    const typename DEST_VEC::value_type *e=z+N;
    while (z!=e) {*z++ = *x++ * *y++;}
  } else {
    for (size_type i=0; i<N; i++) Z[i] = X[i] * Y[i];
  }
}

/// Explicit instantiation for <double, int>
template <typename Ordinal>
inline void dvmul(const Vector<double,Ordinal> &X,
                  const Vector<double,Ordinal> &Y,
                  Vector<double,Ordinal> &Z) {
  const Ordinal N = Y.size();
  checkInt(N);
#if defined(CMC_USE_AVX) && defined(__AVX__)
  const Ordinal lowerN = N & ~3UL;
  double *px=X.ptr(), *py=Y.ptr(), *pz=Z.ptr();
  for (Ordinal i=0; i<lowerN; i+=4, px+=4, py+=4, pz+=4) {
    __m256d ymm0 = _mm256_loadu_pd(px);
    __m256d ymm1 = _mm256_loadu_pd(py);
    __m256d ymm3 = _mm256_mul_pd(ymm0,ymm1);
    _mm256_storeu_pd(pz,ymm3);
  }
  if (lowerN<N) {
    double *px=X.ptr()+lowerN, *py=Y.ptr()+lowerN, *pz=Z.ptr()+lowerN;
    for (Ordinal i=lowerN; i<N; i++) { *pz = *px * *py; px++; py++; pz++; }
  }
#else
#if 0
  // This is the slowest
  for (int i=0; i<N; i++) Y[i] *= X[i];
#else
  // this is faster since it doesn't have to use operator[]
  const double *px = X.ptr(); const double *py = Y.ptr(); double *pz = Z.ptr();
  for (Ordinal i=0; i<N; i++) { *pz = *px * *py; px++; py++; pz++; }
#endif
#endif
}

/// Multiply two vectors:  z = x * y (elementwise)(strided)
template <class SRC1_VEC, class SRC2_VEC, class DEST_VEC>
inline void dvmul(const SRC1_VEC &X, const SRC2_VEC &Y, DEST_VEC &Z,
                  const typename DEST_VEC::size_type stride) {
  typedef typename DEST_VEC::size_type size_type;
  const size_type N = X.size();
#ifdef CMC_CHECK_BOUNDS
  assert(stride*N==Y.size());
  assert(stride*N==Z.size());
#endif
  size_type k=0;
  for (size_type j=0; j<stride; ++j) {
    for (size_type i=0; i<N; ++i) {
      Z[k] = X[i] * Y[k];
      ++k;
    }
  }
}

/// Multiply and sum into:   z += x * y (elementwise)
template <class SRC1_VEC, class SRC2_VEC, class DEST_VEC>
inline void dvmulsum( const SRC1_VEC &X, const SRC2_VEC &Y, DEST_VEC &Z) {
  typedef typename DEST_VEC::size_type size_type;
  const size_type N = Z.size();
#ifdef CMC_CHECK_BOUNDS
  assert(N==X.size());
  assert(N==Y.size());
#endif
  for (size_type i=0; i<N; i++) Z[i] += X[i] * Y[i];
}

/// Multiply and subtract into:  z -= x * y (elementwise)
template <class SRC1_VEC, class SRC2_VEC, class DEST_VEC>
inline void dvmulsub( const SRC1_VEC &X, const SRC2_VEC &Y, DEST_VEC &Z) {
  typedef typename DEST_VEC::size_type size_type;
  const size_type N = Z.size();
#ifdef CMC_CHECK_BOUNDS
  assert(N==X.size());
  assert(N==Y.size());
#endif
  for (size_type i=0; i<N; i++) Z[i] -= X[i] * Y[i];
}

/// Multiply and subtract into:  w -= x * y * z (elementwise)
template <class SRC1_VEC, class SRC2_VEC, class SRC3_VEC, class DEST_VEC>
inline void dvmulmulsub( const SRC1_VEC &X, const SRC2_VEC &Y,
                         const SRC3_VEC &Z, DEST_VEC &W) {
  typedef typename DEST_VEC::size_type size_type;
  const size_type N = W.size();
#ifdef CMC_CHECK_BOUNDS
  assert(N==X.size());
  assert(N==Y.size());
  assert(N==Z.size());
#endif
  for (size_type i=0; i<N; i++) W[i] -= X[i] * Y[i] * Z[i];
}

/// General scalar multiply
template<class Scalar, class Ordinal>
inline void multiply( const Scalar alpha, const Vector<Scalar,Ordinal> &X,
                      Vector<Scalar,Ordinal> &Y) {
  const Ordinal N = Y.size();
#ifdef CMC_CHECK_BOUNDS
  assert(N==X.size());
#endif
  for (Ordinal i=0; i<N; i++) Y[i] = alpha * X[i];
}

/// Double scalar multiply:  y = alpha * x (elementwise)
template<class Ordinal>
inline void multiply( const double alpha, const Vector<double,Ordinal> &X,
                      Vector<double,Ordinal> &Y) {
  const Ordinal N = Y.size();
#ifdef CMC_CHECK_BOUNDS
  assert(N==X.size());
#endif
  checkInt(N);
  if (X.ptr()!=Y.ptr())
    cblas_dcopy( (int)N, X.data(), 1, Y.data(), 1 );
  cblas_dscal( (int)N, alpha, Y.data(), 1 );
}

/// Float scalar multiply:  y = alpha * x (elementwise)
template<class Ordinal>
inline void multiply( const float alpha, const Vector<float,Ordinal> &X,
                      Vector<float,Ordinal> &Y) {
  const Ordinal N = Y.size();
#ifdef CMC_CHECK_BOUNDS
  assert(N==X.size());
#endif
  checkInt(N);
  cblas_scopy( N, X.data(), 1, Y.data(), 1 );
  cblas_sscal( N, alpha, Y.data(), 1 );
}

/// Vector times vector plus vector:  w = x * y + z (elementwise)
/** This is a special version for comparison to AVX version */
template<class Ordinal>
inline void dvtvp( const Vector<double,Ordinal> &X,
                   const Vector<double,Ordinal> &Y,
                   const Vector<double,Ordinal> &Z,
                   Vector<double,Ordinal> &W ) {
  const Ordinal N = W.size();
#ifdef CMC_CHECK_BOUNDS
  assert(N==X.size());
  assert(N==Y.size());
  assert(N==Z.size());
#endif
  const double *px = X.ptr(); const double *py = Y.ptr();
  const double *pz = Z.ptr(); double *pw = W.ptr();
  for (Ordinal i=0; i<N; i++) {*pw = *px * *py + *pz; px++; py++; pz++; pw++;}
}

#define is_aligned(POINTER, BYTE_COUNT) \
(((uintptr_t)(const void *)(POINTER)) % (BYTE_COUNT) == 0)

/// Vector times vector plus vector:  w = x * y + z (elementwise)
template<class Ordinal>
inline void dvvtvp( const Vector<double,Ordinal> &X,
                    const Vector<double,Ordinal> &Y,
                    const Vector<double,Ordinal> &Z,
                    Vector<double,Ordinal> &W ) {
  //std::cout << "dvvtvp with N = " << N << std::endl;
  const Ordinal N = W.size();
  checkInt(N);
#ifdef CMC_CHECK_BOUNDS
  assert(N==X.size());
  assert(N==Y.size());
  assert(N==Z.size());
#endif
#if defined(CMC_USE_AVX) && defined(__AVX__)
  // This is the Intel way of allocating and freeing aligned memory
  //   void * _mm_malloc(size_t size, size_t align);
  //   void _mm_free(void *p);
  // But the compiler still needs to be told that it is aligned!
  // with ICC this is _assume_aligned(x,32) inside a loop body
  const Ordinal lowerN = N & ~3UL;
  const double *px=X.ptr(), *py=Y.ptr(), *pz=Z.ptr(); double *pw=W.ptr();
  // if aligned, use faster load/store
//  if (is_aligned(px,32) && is_aligned(py,32) &&
//      is_aligned(pz,32) && is_aligned(pw,32)) {
//    for (Ordinal i=0; i<lowerN; i+=4, px+=4, py+=4, pz+=4, pw+=4) {
//      __m256d ymm0 = _mm256_load_pd(px);
//      __m256d ymm1 = _mm256_load_pd(py);
//      __m256d ymm3 = _mm256_load_pd(pz);
//#ifdef __FMA__
//      // FMA3 (Intel)
//      __m256d ymm5 = _mm256_fmadd_pd(ymm0,ymm1,ymm3);
//#elif __FMA4__
//      // FMA4 (AMD)
//      __m256d ymm5 = _mm256_macc_pd(ymm0,ymm1,ymm3);
//#else
//      __m256d ymm4 = _mm256_mul_pd(ymm0,ymm1);
//      __m256d ymm5 = _mm256_add_pd(ymm3,ymm4);
//#endif
//      _mm256_store_pd(pw,ymm5);
//    }
//  } else {
    for (Ordinal i=0; i<lowerN; i+=4, px+=4, py+=4, pz+=4, pw+=4) {
      __m256d ymm0 = _mm256_loadu_pd(px);
      __m256d ymm1 = _mm256_loadu_pd(py);
      __m256d ymm3 = _mm256_loadu_pd(pz);
#ifdef __FMA__
      // FMA3 (Intel)
      __m256d ymm5 = _mm256_fmadd_pd(ymm0,ymm1,ymm3);
#elif __FMA4__
      // FMA4 (AMD)
      __m256d ymm5 = _mm256_macc_pd(ymm0,ymm1,ymm3);
#else
      __m256d ymm4 = _mm256_mul_pd(ymm0,ymm1);
      __m256d ymm5 = _mm256_add_pd(ymm3,ymm4);
#endif
      _mm256_storeu_pd(pw,ymm5);
    }
//  }
  // If not even vector length, finish off with scalar loop
  if (lowerN<N) {
    const double *px = X.ptr()+lowerN; const double *py = Y.ptr()+lowerN;
    const double *pz = Z.ptr()+lowerN; double *pw = W.ptr()+lowerN;
    for (Ordinal i=lowerN; i<N; i++, px++, py++, pz++, pw++) {
      *pw = fma(*px,*py,*pz);
      //*pw = *px * *py + *pz;
    }
  }
#else
#if 1
  // This has higher performance without operator[]
  const double *px=X.ptr(), *py=Y.ptr(), *pz=Z.ptr(); double *pw = W.ptr();
  for (Ordinal i=0; i<N; i++, px++, py++, pz++, pw++) {
    *pw = fma(*px,*py,*pz);
    //*pw = *px * *py + *pz;
  }
#else
  for (Ordinal i=0; i<N; i++) { W[i] = X[i]*Y[i] + Z[i]; }
#endif
#endif
  //for (Ordinal i=0; i<N; ++i) std::cout<<"W["<<i<<"] = "<<W[i]<<std::endl;
}

/// Vector times vector plus vector:  w = x * y + z (elementwise) (strided)
template<class Ordinal>
inline void dvvtvp( const Vector<double,Ordinal> &X,
                    const Vector<double,Ordinal> &Y,
                    const Vector<double,Ordinal> &Z,
                    Vector<double,Ordinal> &W, const Ordinal stride ) {
  const Ordinal N = X.size();
#ifdef CMC_CHECK_BOUNDS
  assert(stride*N==Y.size());
  assert(stride*N==Z.size());
  assert(stride*N==W.size());
#endif
  Ordinal k=0;
  for (Ordinal j=0; j<stride; ++j) {
    for (Ordinal i=0; i<N; ++i, ++k) {
      W[k] = fma(X[i],Y[k],Z[k]);
      //W[k] = X[i] * Y[k] + Z[k];
    }
  }
}

/// Vector times vector add into:   z += x * y (elementwise)
template<class Ordinal>
inline void dvvtva( const Vector<double,Ordinal> &X,
                    const Vector<double,Ordinal> &Y,
                    Vector<double,Ordinal> &Z) {
  const Ordinal N = Z.size();
#ifdef CMC_CHECK_BOUNDS
  assert(N==X.size());
  assert(N==Y.size());
#endif
  for (Ordinal i=0; i<N; i++) Z[i] += X[i] * Y[i];
}

/// Vector times vector minus:  w = z - x * y  (elementwise)
template<class Ordinal>
inline void dvvtvm( const Vector<double,Ordinal> &X,
                    const Vector<double,Ordinal> &Y,
                    const Vector<double,Ordinal> &Z,
                    Vector<double,Ordinal> &W ) {
  const Ordinal N = W.size();
#ifdef CMC_CHECK_BOUNDS
  assert(N==X.size());
  assert(N==Y.size());
  assert(N==Z.size());
#endif
  for (Ordinal i=0; i<N; i++) W[i] = Z[i] - X[i] * Y[i];
}

/// Scaled vector minus vector:  z = a * x - y (elementwise)
template<class Ordinal>
inline void daxmy( const double a, const Vector<double,Ordinal> &X,
                   const Vector<double,Ordinal> &Y,
                   Vector<double,Ordinal> &Z ) {
  const Ordinal N = Z.size();
#ifdef CMC_CHECK_BOUNDS
  assert(N==X.size());
  assert(N==Y.size());
#endif
  for (Ordinal i=0; i<N; i++) Z[i] = a * X[i] - Y[i];
}

/// Elementwise square root:  y = sqrt(y) (elementwise)
template<class Ordinal>
inline void dvsqrt( Vector<double,Ordinal> &Y ) {
  using std::sqrt;
  const Ordinal N = Y.size();
  for (Ordinal i=0; i<N; i++) Y[i] = sqrt(Y[i]);
}

/// Elementwise square root:  y = sqrt(x) (elementwise)
template<class Ordinal>
inline void dvsqrt( const Vector<double,Ordinal> &X,
                    Vector<double,Ordinal> &Y ) {
  using std::sqrt;
  const Ordinal N = Y.size();
#ifdef CMC_CHECK_BOUNDS
  assert(N==X.size());
#endif
  for (Ordinal i=0; i<N; i++) Y[i] = sqrt(X[i]);
}

/// Elementwise log base 10:  y = log_10(x) (elementwise)
template<class Ordinal>
inline void dvlog10( const Vector<double,Ordinal> &X,
                     Vector<double,Ordinal> &Y ) {
  using std::log10;
  const Ordinal N = Y.size();
#ifdef CMC_CHECK_BOUNDS
  assert(N==X.size());
#endif
  for (Ordinal i=0; i<N; i++) Y[i] = log10(X[i]);
}

/// Vector inverse:  x = one / x (elementwise)
template <class SRC_DEST_VEC>
inline void dvinv( SRC_DEST_VEC &X ) {
  typedef typename SRC_DEST_VEC::size_type size_type;
  for (size_type i=0; i<X.size(); i++) X[i] = 1.0/X[i];
}

/// Vector divide:  y /= x (elementwise)
template <class SRC_VEC, class DEST_VEC>
inline void dvdiv( const SRC_VEC &X, DEST_VEC &Y ) {
  typedef typename DEST_VEC::size_type size_type;
  const size_type N = Y.size();
#ifdef CMC_CHECK_BOUNDS
  assert(N==X.size());
#endif
  for (size_type i=0; i<N; i++) Y[i] /= X[i];
}

/// Vector divide:  z = x / y
template<class Ordinal>
inline void dvdiv( const Vector<double,Ordinal> &X,
                   const Vector<double,Ordinal> &Y,
                   Vector<double,Ordinal> &Z ) {
  const Ordinal N = Y.size();
#ifdef CMC_CHECK_BOUNDS
  assert(N==X.size());
  assert(N==Z.size());
#endif
  for (Ordinal i=0; i<N; i++) Z[i] = X[i] / Y[i];
}

//=============================================================================
//          Operation:  AXPY
//=============================================================================

/// Scale and add:  y = a x + y
template<class Ordinal>
inline void daxpy( const double alpha, const Vector<double,Ordinal> &X,
                   Vector<double,Ordinal> &Y) {
#ifdef CMC_CHECK_BOUNDS
  assert(Y.size()==X.size());
#endif
  checkInt(X.size());
  cblas_daxpy( (int)X.size(), alpha, X.data(), 1, Y.data(), 1 );
}

/// Scale and add
template<class Ordinal>
inline void daxpy( const double alpha, const Slice<double,Ordinal> X,
                   Slice<double,Ordinal> Y) {
#ifdef CMC_CHECK_BOUNDS
  assert(Y.size()==X.size());
#endif
  checkInt(X.size());
  checkInt(X.stride());
  checkInt(Y.stride());
  cblas_daxpy( (int)X.size(), alpha, X.data(), (int)X.stride(), Y.data(),
               (int)Y.stride() );
}

/// Scale and add
template<class Ordinal>
inline void daxpy( const double alpha, const Vector<double,Ordinal> &X,
                   Slice<double,Ordinal> Y) {
  const Ordinal N = X.size();
#ifdef CMC_CHECK_BOUNDS
  assert(Y.size()==N);
#endif
  checkInt(N);
  checkInt(Y.stride());
  cblas_daxpy( (int)X.size(), alpha, X.data(), 1, Y.data(), (int)Y.stride() );
}

/// Scale and add:  z = a x + y
template<class Ordinal>
inline void daxpy( const double alpha, const Vector<double,Ordinal> &X,
                   const Vector<double,Ordinal> &Y, Vector<double,Ordinal> &Z) {
  const Ordinal N = X.size();
#ifdef CMC_CHECK_BOUNDS
  assert(Y.size()==N);
  assert(Z.size()==N);
#endif
#ifdef CMC_USE_ARRAY
#if 0
  for (Ordinal i=0; i<N; i++) Z[i] = alpha * X[i] + Y[i];
#else
  const double *px = X.ptr(), *py = Y.ptr();
  double *pz = Z.ptr();
  for (Ordinal i=0; i<N; i++) { *pz = alpha * *px + *py; px++; py++; pz++; }
#endif
#else
  checkInt(N);
  if (X.ptr()==Z.ptr()) {
    cblas_dscal( (int)N, alpha, X.data(), 1 );
    cblas_daxpy( (int)N, 1.0, Y.data(), 1, X.data(), 1 );
  } else {
    if (Y.ptr()!=X.ptr()) cblas_dcopy( (int)N, Y.data(), 1, Z.data(), 1 );
    cblas_daxpy( (int)N, alpha, X.data(), 1, Z.data(), 1 );
  }
#endif
}

//=============================================================================

/* LAPACK dgeev computes for an N-by-N real nonsymmetric matrix A,
   the eigenvalues and, optionally, the left and/or right eigenvectors. */
extern "C" {
#if defined(DGM_DGEEV_UNDERSCORE)
int dgeev_(char *jobvl, char *jobvr, const int* n, double* a, const int* lda,
          double* wr, double* wi,
          double* vl, const int* ldvl,
          double* vr, const int* ldvr,
          double* work, const int* lwork, int* info);

inline
int dgeev(char *jobvl, char *jobvr, const int* n, double* a, const int* lda,
          double* wr, double* wi,
          double* vl, const int* ldvl,
          double* vr, const int* ldvr,
          double* work, const int* lwork, int* info)
  {
    return dgeev_(jobvl, jobvr, n, a, lda, wr, wi,
      vl, ldvl, vr, ldvr, work, lwork, info);
  }
#else
int dgeev(char *jobvl, char *jobvr, const int* n, double* a, const int* lda,
          double* wr, double* wi,
          double* vl, const int* ldvl,
          double* vr, const int* ldvr,
          double* work, const int* lwork, int* info);
#endif
}

/// Generalized Matrix-Vector multiplication:  y = alpha A x + beta y
template<class Ordinal>
inline void dgemv(const double alpha, const Matrix<double,Ordinal> &A,
                  const Vector<double,Ordinal> &X, const double beta,
                  Vector<double,Ordinal> &Y) {
#ifdef CMC_CHECK_BOUNDS
  assert(A.cols()==X.size());
  assert(A.rows()==Y.size());
#endif
  checkInt(A.rows()); checkInt(A.cols());
  cblas_dgemv( CblasRowMajor, CblasNoTrans,
               (int)A.rows(), (int)A.cols(), alpha, A.data(), (int)A.cols(),
               X.data(), 1, beta, Y.data(), 1 );
}

/// Generalized Matrix-Vector multiplication:  y = alpha A x + beta y
template<class Ordinal>
inline void dgemv(const char at, const double alpha,
                  const Matrix<double,Ordinal> &A,
                  const Vector<double,Ordinal> &X, const double beta,
                  Vector<double,Ordinal> &Y) {
  using std::cerr;
  using std::endl;
  switch (at) {
  case ('N'):
#ifdef CMC_CHECK_BOUNDS
    assert(A.cols()==X.size());
    assert(A.rows()==Y.size());
#endif
    checkInt(A.rows()); checkInt(A.cols());
    cblas_dgemv( CblasRowMajor, CblasNoTrans,
                 (int)A.rows(), (int)A.cols(), alpha, A.data(), (int)A.cols(),
                 X.data(), 1, beta, Y.data(), 1 );
    break;
  case ('T'):
#ifdef CMC_CHECK_BOUNDS
    assert(A.rows()==X.size());
    assert(A.cols()==Y.size());
#endif
    checkInt(A.rows()); checkInt(A.cols());
    cblas_dgemv( CblasRowMajor, CblasTrans,
                 (int)A.rows(), (int)A.cols(), alpha, A.data(), (int)A.cols(),
                 X.data(), 1, beta, Y.data(), 1 );
    break;
  default:
    cerr << "dgemv: Illegal code" << endl;
    exit(EXIT_FAILURE);
  }
}

/// Generalized Matrix-Vector multiplication:  y = alpha A x + beta y
template<class Ordinal>
inline void dgemv(const double alpha, const Matrix<double,Ordinal> &A,
                  const Slice<double,Ordinal> X, const double beta,
                  Vector<double,Ordinal> &Y) {
#ifdef CMC_CHECK_BOUNDS
  assert(A.cols()==X.size());
  assert(A.rows()==Y.size());
#endif
  checkInt(A.rows()); checkInt(A.cols()); checkInt(X.stride());
  cblas_dgemv( CblasRowMajor, CblasNoTrans,
               (int)A.rows(), (int)A.cols(), alpha, A.data(), (int)A.cols(),
               X.data(), (int)X.stride(), beta, Y.data(), 1 );
}

/// Generalized Matrix-Vector multiplication:  y = alpha A x + beta y
template<class Ordinal>
inline void dgemv(const double alpha, const Matrix<double,Ordinal> &A,
                  const Vector<double,Ordinal> &X, const double beta,
                  Slice<double,Ordinal> Y) {
#ifdef CMC_CHECK_BOUNDS
  assert(A.cols()==X.size());
  assert(A.rows()==Y.size());
#endif
  checkInt(A.rows()); checkInt(A.cols()); checkInt(Y.stride());
  cblas_dgemv( CblasRowMajor, CblasNoTrans,
               (int)A.rows(), (int)A.cols(), alpha, A.data(), (int)A.cols(),
               X.data(), 1, beta, Y.data(), (int)Y.stride() );
}

/// Generalized Matrix-Vector multiplication:  y = alpha A x + beta y
template<class Ordinal>
inline void dgemv(const double alpha, const Matrix<double,Ordinal> &A,
                  const Slice<double,Ordinal> X, const double beta,
                  Slice<double,Ordinal> Y) {
#ifdef CMC_CHECK_BOUNDS
  assert(A.cols()==X.size());
  assert(A.rows()==Y.size());
#endif
  checkInt(A.rows()); checkInt(A.cols());
  checkInt(X.stride()); checkInt(Y.stride());
  cblas_dgemv( CblasRowMajor, CblasNoTrans,
               (int)A.rows(), (int)A.cols(), alpha, A.data(), (int)A.cols(),
               X.data(), (int)X.stride(), beta, Y.data(), (int)Y.stride() );
}

/// Matrix subtraction:  Z = x - y
template<class Scalar, class Ordinal>
inline void subtract( const Matrix<Scalar,Ordinal> &X,
                      const Matrix<Scalar,Ordinal> &Y,
                      Matrix<Scalar,Ordinal> &Z) {
  const Ordinal N = Z.rows();
  const Ordinal M = Z.cols();
#ifdef CMC_CHECK_BOUNDS
  assert(N<=X.rows());
  assert(N<=Y.rows());
  assert(M<=X.cols());
  assert(M<=Y.cols());
#endif
  for (Ordinal i=0; i<N; i++)
    for (Ordinal j=0; j<M; j++)
      Z[i][j] = X[i][j] - Y[i][j];
}

/// Scale columns of a matrix by the values of a vector
template<class Scalar, class Ordinal>
inline void scale(const Vector<Scalar,Ordinal> &X,
                  Matrix<Scalar,Ordinal> &M) {
  const Ordinal m = M.rows();
  const Ordinal n = M.cols();
#ifdef CMC_CHECK_BOUNDS
  assert(n==X.size());
#endif
  for (Ordinal i=0; i<m; i++)
    for (Ordinal j=0; j<n; j++)
      M[i][j] *= X[j];
}

//=============================================================================

/// Matrix-vector multiplication:  y = A x
template<class Ordinal>
inline void mvmult(const Matrix<double,Ordinal> &A,
                   const Vector<double,Ordinal> &X,
                   Vector<double,Ordinal> &Y) {
  assert(X.ptr() != Y.ptr());
#ifdef CMC_CHECK_BOUNDS
  assert(A.cols()==X.size());
  assert(A.rows()==Y.size());
#endif
#ifdef CMC_USE_ARRAY
  for (Ordinal i=0; i<A.rows(); i++) {
    Y[i] = 0.0;
    for (Ordinal j=0; j<A.cols(); j++) Y[i] += A[i][j] * X[j];
  }
#else
  checkInt(A.rows()); checkInt(A.cols());
  cblas_dgemv( CblasRowMajor, CblasNoTrans,
               (int)A.rows(), (int)A.cols(), 1.0, A.data(), (int)A.cols(),
               X.data(), 1, 0.0, Y.data(), 1 );
#endif
}
/// Matrix-vector multiplication:  y = A x
template<class Ordinal>
inline void mvmult(const Matrix<float,Ordinal> &A,
                   const Vector<float,Ordinal> &X,
                   Vector<float,Ordinal> &Y) {
  assert(X.ptr() != Y.ptr());
#ifdef CMC_CHECK_BOUNDS
  assert(A.cols()==X.size());
  assert(A.rows()==Y.size());
#endif
#ifdef CMC_USE_ARRAY
  for (Ordinal i=0; i<A.rows(); i++) {
    Y[i] = 0.0;
    for (Ordinal j=0; j<A.cols(); j++) Y[i] += A[i][j] * X[j];
  }
#else
  checkInt(A.rows()); checkInt(A.cols());
  cblas_sgemv( CblasRowMajor, CblasNoTrans,
               (int)A.rows(), (int)A.cols(), 1.0, A.data(), (int)A.cols(),
               X.data(), 1, 0.0, Y.data(), 1 );
#endif
}

/// Transpose matrix-vector multiplication:  y = A^T x
template<class Ordinal>
inline void tmvmult(const Matrix<double,Ordinal> &A,
                    const Vector<double,Ordinal> &X,
                    Vector<double,Ordinal> &Y) {
  assert(X.ptr() != Y.ptr());
#ifdef CMC_CHECK_BOUNDS
  assert(A.rows()==X.size());
  assert(A.cols()==Y.size());
#endif
#ifdef CMC_USE_ARRAY
  for (Ordinal i=0; i<A.cols(); i++) {
    Y[i] = 0.0;
    for (Ordinal j=0; j<A.rows(); j++) Y[i] += A[j][i] * X[j];
  }
#else
  checkInt(A.rows()); checkInt(A.cols());
  cblas_dgemv( CblasRowMajor, CblasTrans,
               (int)A.rows(), (int)A.cols(), 1.0, A.data(), (int)A.cols(),
               X.data(), 1, 0.0, Y.data(), 1 );
#endif
}

/// Matrix-vector multiplication
/** Note that the Slice<double>'s are passed by value -- this is required
    so that I can use the matrix row and column member functions.  This is
    ok, in fact I could have passed all matrices and vectors by value since
    they are rather small, however, for now I will only do this with the
    sliced vectors. */
template<class Ordinal>
inline void mvmult(const Matrix<double,Ordinal> &A,
                   const Slice<double,Ordinal> X,
                   Vector<double,Ordinal> &Y) {
  assert(X.ptr() != Y.ptr());
#ifdef CMC_CHECK_BOUNDS
  assert(A.cols()==X.size());
  assert(A.rows()==Y.size());
#endif
  checkInt(A.rows()); checkInt(A.cols()); checkInt(X.stride());
  cblas_dgemv( CblasRowMajor, CblasNoTrans,
               (int)A.rows(), (int)A.cols(), 1.0, A.data(), (int)A.cols(),
               X.data(), (int)X.stride(), 0.0, Y.data(), 1 );
}

/// Matrix-vector multiplication
template<class Ordinal>
inline void mvmult(const Matrix<double,Ordinal> &A,
                   const Vector<double,Ordinal> &X,
                   Slice<double,Ordinal> Y) {
  assert(X.ptr() != Y.ptr());
#ifdef CMC_CHECK_BOUNDS
  assert(A.cols()==X.size());
  assert(A.rows()==Y.size());
#endif
  checkInt(A.rows()); checkInt(A.cols()); checkInt(Y.stride());
  cblas_dgemv( CblasRowMajor, CblasNoTrans,
               (int)A.rows(), (int)A.cols(), 1.0, A.data(), (int)A.cols(),
               X.data(), 1, 0.0, Y.data(), (int)Y.stride() );
}

/// Matrix-vector multiplication
template<class Ordinal>
inline void mvmult(const Matrix<double,Ordinal> &A,
                   const Slice<double,Ordinal> X,
                   Slice<double,Ordinal> Y) {
  assert(X.ptr() != Y.ptr());
#ifdef CMC_CHECK_BOUNDS
  assert(A.cols()==X.size());
  assert(A.rows()==Y.size());
#endif
  checkInt(A.rows()); checkInt(A.cols());
  checkInt(X.stride()); checkInt(Y.stride());
  cblas_dgemv( CblasRowMajor, CblasNoTrans,
               (int)A.rows(), (int)A.cols(), 1.0, A.data(), (int)A.cols(),
               X.data(), (int)X.stride(), 0.0, Y.data(), (int)Y.stride() );
}

//=============================================================================

/// Matrix-matrix multiplication:  C = A B
template<class Ordinal>
inline void matmult(const Matrix<double,Ordinal> &A,
                    const Matrix<double,Ordinal> &B,
                    Matrix<double,Ordinal> &C) {
#ifdef CMC_CHECK_BOUNDS
  assert(A.cols()==B.rows());
  assert(A.rows()==C.rows());
  assert(B.cols()==C.cols());
#endif
  checkInt(A.rows()); checkInt(A.cols());
  checkInt(B.rows()); checkInt(B.cols());
  checkInt(C.rows()); checkInt(C.cols());
  cblas_dgemm( CblasRowMajor, CblasNoTrans, CblasNoTrans,
               (int)A.rows(), (int)B.cols(), (int)A.cols(), 1.0,
               A.data(), (int)A.cols(), B.data(), (int)B.cols(), 0.0,
               C.data(), (int)C.cols() );
}

/// Matrix-matrix multiplication with transpose:  C = A B
template<class Ordinal>
inline void matmult(const Matrix<double,Ordinal> &A, const char bt,
                    const Matrix<double,Ordinal> &B,
                    Matrix<double,Ordinal> &C) {
  using std::cerr;
  using std::endl;
  switch (bt) {
  case ('N'):
#ifdef CMC_CHECK_BOUNDS
    assert(A.cols()==B.rows());
    assert(A.rows()==C.rows());
    assert(B.cols()==C.cols());
#endif
    checkInt(A.rows()); checkInt(A.cols());
    checkInt(B.rows()); checkInt(B.cols());
    checkInt(C.rows()); checkInt(C.cols());
    cblas_dgemm( CblasRowMajor, CblasNoTrans, CblasNoTrans,
                 (int)A.rows(), (int)B.cols(), (int)A.cols(), 1.0,
                 A.data(), (int)A.cols(), B.data(), (int)B.cols(), 0.0,
                 C.data(), (int)C.cols() );
    break;
  case ('T'):
    // compute C = A * B^T
#ifdef CMC_CHECK_BOUNDS
    assert(A.cols()==B.cols());
    assert(A.rows()==C.rows());
    assert(B.rows()==C.cols());
#endif
    checkInt(A.rows()); checkInt(A.cols());
    checkInt(B.rows()); checkInt(B.cols());
    checkInt(C.rows()); checkInt(C.cols());
    cblas_dgemm( CblasRowMajor, CblasNoTrans, CblasTrans,
                 (int)A.rows(), (int)B.rows(), (int)A.cols(), 1.0,
                 A.data(), (int)A.cols(), B.data(), (int)B.cols(), 0.0,
                 C.data(), (int)C.cols() );
    break;
  default:
    cerr << "matmult: Illegal code" << endl;
    exit(EXIT_FAILURE);
  }
}

/// Matrix-matrix multiplication with transpose:  C = A^T B^T
template<class Ordinal>
inline void matmult(const char at, const Matrix<double,Ordinal> &A,
                    const char bt, const Matrix<double,Ordinal> &B,
                    Matrix<double,Ordinal> &C) {
  using std::cerr;
  using std::endl;
  switch (bt) {
  case ('N'):
    switch (at) {
    case ('N'):
#ifdef CMC_CHECK_BOUNDS
      assert(A.cols()==B.rows());
      assert(A.rows()==C.rows());
      assert(B.cols()==C.cols());
#endif
      checkInt(A.rows()); checkInt(A.cols());
      checkInt(B.rows()); checkInt(B.cols());
      checkInt(C.rows()); checkInt(C.cols());
      cblas_dgemm( CblasRowMajor, CblasNoTrans, CblasNoTrans,
                   (int)C.rows(), (int)C.cols(), (int)A.cols(), 1.0,
                   A.data(), (int)A.cols(), B.data(), (int)B.cols(), 0.0,
                   C.data(), (int)C.cols() );
      break;
    case ('T'):
#ifdef CMC_CHECK_BOUNDS
      assert(A.rows()==B.rows());
      assert(A.cols()==C.rows());
      assert(B.cols()==C.cols());
#endif
    checkInt(A.rows()); checkInt(A.cols());
      cblas_dgemm( CblasRowMajor, CblasTrans,   CblasNoTrans,
                   (int)C.rows(), (int)C.cols(), (int)A.rows(), 1.0,
                   A.data(), (int)A.cols(), B.data(), (int)B.cols(), 0.0,
                   C.data(), (int)C.cols() );
      break;
    }
    break;
  case ('T'):
    switch (at) {
    case ('N'):
#ifdef CMC_CHECK_BOUNDS
      assert(A.cols()==B.cols());
      assert(A.rows()==C.rows());
      assert(B.rows()==C.cols());
#endif
      checkInt(A.rows()); checkInt(A.cols());
      checkInt(B.rows()); checkInt(B.cols());
      checkInt(C.rows()); checkInt(C.cols());
      cblas_dgemm( CblasRowMajor, CblasNoTrans, CblasTrans,
                   (int)C.rows(), (int)C.cols(), (int)A.cols(), 1.0,
                   A.data(), (int)A.cols(), B.data(), (int)B.cols(), 0.0,
                   C.data(), (int)C.cols() );
      break;
    case ('T'):
#ifdef CMC_CHECK_BOUNDS
      assert(A.rows()==B.cols());
      assert(A.cols()==C.rows());
      assert(B.rows()==C.cols());
#endif
      checkInt(A.rows()); checkInt(A.cols());
      checkInt(B.rows()); checkInt(B.cols());
      checkInt(C.rows()); checkInt(C.cols());
      cblas_dgemm( CblasRowMajor, CblasTrans, CblasTrans,
                   (int)C.rows(), (int)C.cols(), (int)A.rows(), 1.0,
                   A.data(), (int)A.cols(), B.data(), (int)B.cols(), 0.0,
                   C.data(), (int)C.cols() );
      break;
    }
    break;
  default:
    cerr << "matmult: Illegal code" << endl;
    exit(EXIT_FAILURE);
  }
}

/// Matrix-matrix multiplication with transpose:  C = A B
template<class Ordinal>
inline void matmult(const Matrix<float,Ordinal> &A, const char bt,
                    const Matrix<float,Ordinal> &B,
                    Matrix<float,Ordinal> &C) {
  using std::cerr;
  using std::endl;
  switch (bt) {
  case ('N'):
#ifdef CMC_CHECK_BOUNDS
    assert(A.cols()==B.rows());
    assert(A.rows()==C.rows());
    assert(B.cols()==C.cols());
#endif
    checkInt(A.rows()); checkInt(A.cols());
    checkInt(B.rows()); checkInt(B.cols());
    checkInt(C.rows()); checkInt(C.cols());
    cblas_sgemm( CblasRowMajor, CblasNoTrans, CblasNoTrans,
                 (int)A.rows(), (int)B.cols(), (int)A.cols(), 1.0,
                 A.data(), (int)A.cols(), B.data(), (int)B.cols(), 0.0,
                 C.data(), (int)C.cols() );
    break;
  case ('T'):
#ifdef CMC_CHECK_BOUNDS
    assert(A.cols()==B.cols());
    assert(A.rows()==C.rows());
    assert(B.rows()==C.cols());
#endif
    checkInt(A.rows()); checkInt(A.cols());
    checkInt(B.rows()); checkInt(B.cols());
    checkInt(C.rows()); checkInt(C.cols());
    cblas_sgemm( CblasRowMajor, CblasNoTrans, CblasTrans,
                 (int)A.rows(), (int)B.rows(), (int)A.cols(), 1.0,
                 A.data(), (int)A.cols(), B.data(), (int)B.cols(), 0.0,
                 C.data(), (int)C.cols() );
    break;
  default:
    cerr << "matmult: Illegal code" << endl;
    exit(EXIT_FAILURE);
  }
}

/// Matrix-matrix multiplication with transpose:  C = A B
template<class Ordinal>
inline void matmult(const char at, const Matrix<double,Ordinal> &A,
                    const Matrix<double,Ordinal> &B,
                    Matrix<double,Ordinal> &C) {
  using std::cerr;
  using std::endl;
  switch (at) {
  case ('N'):
#ifdef CMC_CHECK_BOUNDS
    assert(A.cols()==B.rows());
    assert(A.rows()==C.rows());
    assert(B.cols()==C.cols());
#endif
    checkInt(A.rows()); checkInt(A.cols());
    checkInt(B.rows()); checkInt(B.cols());
    checkInt(C.rows()); checkInt(C.cols());
    cblas_dgemm( CblasRowMajor, CblasNoTrans, CblasNoTrans,
                 (int)A.rows(), (int)B.cols(), (int)A.cols(), 1.0,
                 A.data(), (int)A.cols(), B.data(), (int)B.cols(), 0.0,
                 C.data(), (int)C.cols() );
    break;
  case ('T'):
#ifdef CMC_CHECK_BOUNDS
    assert(A.rows()==B.rows());
    assert(A.cols()==C.rows());
    assert(B.cols()==C.cols());
#endif
    checkInt(A.rows()); checkInt(A.cols());
    checkInt(B.rows()); checkInt(B.cols());
    checkInt(C.rows()); checkInt(C.cols());
    cblas_dgemm( CblasRowMajor, CblasTrans, CblasNoTrans,
                 (int)A.cols(), (int)B.cols(), (int)A.rows(), 1.0,
                 A.data(), (int)A.cols(), B.data(), (int)B.cols(), 0.0,
                 C.data(), (int)C.cols() );
    break;
  default:
    cerr << "matmult: Illegal code" << endl;
    exit(EXIT_FAILURE);
  }
}

/// Generalized matrix-matrix multiplication:  C = alpha*A*B + beta*C
template<class Ordinal>
inline void gmatmult(const double alpha, const Matrix<double,Ordinal> &A,
                     const Matrix<double,Ordinal> &B, const double beta,
                     Matrix<double,Ordinal> &C) {
#ifdef CMC_CHECK_BOUNDS
  assert(A.cols()==B.rows());
  assert(A.rows()==C.rows());
  assert(B.cols()==C.cols());
#endif
  checkInt(A.rows()); checkInt(A.cols());
  checkInt(B.rows()); checkInt(B.cols());
  checkInt(C.rows()); checkInt(C.cols());
  cblas_dgemm( CblasRowMajor, CblasNoTrans, CblasNoTrans,
               (int)A.rows(), (int)B.cols(), (int)A.cols(), alpha,
               A.data(), (int)A.cols(), B.data(), (int)B.cols(), beta,
               C.data(), (int)C.cols() );
}
template<class Ordinal>
inline void gmatmult(const double alpha, const Matrix<double,Ordinal> &A,
                     const char bt,
                     const Matrix<double,Ordinal> &B, const double beta,
                     Matrix<double,Ordinal> &C) {
  using std::cerr;
  using std::endl;
  switch (bt) {
  case ('N'):
#ifdef CMC_CHECK_BOUNDS
    assert(A.cols()==B.rows());
    assert(A.rows()==C.rows());
    assert(B.cols()==C.cols());
#endif
    cblas_dgemm( CblasRowMajor, CblasNoTrans, CblasNoTrans,
             A.rows(), B.cols(), A.cols(), alpha,
             A.data(), A.cols(), B.data(), B.cols(), beta,
           C.data(), C.cols() );
    break;
  case ('T'):
#ifdef CMC_CHECK_BOUNDS
    assert(A.cols()==B.cols());
    assert(A.rows()==C.rows());
    assert(B.rows()==C.cols());
#endif
    cblas_dgemm( CblasRowMajor, CblasNoTrans, CblasTrans,
             A.rows(), B.cols(), A.cols(), alpha,
             A.data(), A.cols(), B.data(), B.cols(), beta,
           C.data(), C.cols() );
    break;
  default:
    cerr << "matmult: Illegal code" << endl;
    exit(EXIT_FAILURE);
  }
}

/// Compute an LU factorization of a Matrix
template<class Ordinal, class Index>
inline int LU_factor( Matrix<double,Ordinal> &A,
                      Vector<Index,Ordinal> &A_pivots ) {
#ifdef CMC_CHECK_BOUNDS
  assert(A.rows()==A.cols());
#endif
  A_pivots.resize( min(A.rows(),A.cols()) );
#ifdef CMC_USE_TEUCHOS_LAPACK
  int info=0;
  A.lapack.GETRF(A.cols(),A.rows(),A.data(),A.cols(),A_pivots.data(),&info);
  return info;
#else
  checkInt(A.rows()); checkInt(A.cols());
  return CLAPACK(dgetrf)( CblasRowMajor, (int)A.rows(), (int)A.cols(), A.data(),
                          (int)A.cols(), (int*)A_pivots.data() );
#endif
}

/// Do a inverse of a Matrix that has already been factored
template<class Ordinal, class Index>
inline int LU_inverse( Matrix<double,Ordinal> &A,
                       const Vector<Index,Ordinal> &A_pivots) {
#ifdef CMC_CHECK_BOUNDS
  assert(A.rows()==A.cols());
#endif
#ifdef CMC_USE_TEUCHOS_LAPACK
  int info=0;
  const Ordinal lwork = A.cols();
  Vector<double,Ordinal> work(lwork);
  A.lapack.GETRI(A.cols(),A.data(),A.cols(),A_pivots.data(),work.data(),
                 lwork,&info);
  return info;
#else
  checkInt(A.rows()); checkInt(A.cols());
  return CLAPACK(dgetri)( CblasRowMajor, (int)A.cols(), A.data(),
                          (int)A.cols(), (int*)A_pivots.data() );
#endif
}

/// Do a solve of a Matrix that has already been factored
template<class Ordinal>
inline int LU_solve( const Matrix<double,Ordinal> &A,
                     const Vector<int,Ordinal> &A_pivots,
                     Vector<double,Ordinal> &X ) {
#ifdef CMC_CHECK_BOUNDS
  assert(A.rows()==A.cols());
  assert(A.rows()==X.size());
#endif
  int info=0;
  //cout<<"Initial A="<<A<<endl;
#ifdef CMC_USE_TEUCHOS_LAPACK
  const char TRANS='T';
  A.lapack.GETRS( TRANS, A.rows(), 1, A.data(), A.cols(),
                  A_pivots.data(), X.data(), A.cols(), &info );
#else
  //cout<<"About to call CLAPACK_dgetrs"<<endl;
  checkInt(A.rows()); checkInt(A.cols());
  info = CLAPACK(dgetrs)( CblasRowMajor, CblasNoTrans, (int)A.rows(), 1,
                          A.data(), (int)A.cols(), (int*)A_pivots.data(),
                         X.data(), (int)A.cols() );
#endif
  //cout<<"Final A="<<A<<std::endl;
  //exit(1);
  return info;
}

/// Do a solve of a Matrix that has already been factored
template<class Ordinal>
inline int LU_solve( const Matrix<double,Ordinal> &A,
                     const Vector<int,Ordinal> &A_pivots,
                     Matrix<double,Ordinal> &X ) {
#ifdef CMC_CHECK_BOUNDS
  assert(A.rows()==A.cols());
  assert(A.rows()==X.cols());
#endif
#ifdef CMC_USE_TEUCHOS_LAPACK
  int info=0;
  const char TRANS='T';
  A.lapack.GETRS( TRANS, A.rows(), X.rows(), A.data(),
                  A.cols(), A_pivots.data(), X.data(), A.cols(), &info );
  return info;
#else
  checkInt(A.rows()); checkInt(A.cols()); checkInt(X.rows());
  return CLAPACK(dgetrs)( CblasRowMajor, CblasNoTrans, (int)A.rows(),
                          (int)X.rows(), A.data(), (int)A.cols(),
                         A_pivots.data(), X.data(), (int)A.cols() );
#endif
}

/// Compute a Cholesky factorization of a Matrix
template<class Ordinal>
inline int Cholesky_factor( Matrix<double,Ordinal> &A ) {
#ifdef CMC_CHECK_BOUNDS
  assert(A.rows()==A.cols());
#endif
#ifdef CMC_USE_TEUCHOS_LAPACK
  int info=0;
  const char uplo='U';
  A.lapack.POTRF(uplo, A.rows(),A.data(),A.rows(),&info);
  return info;
#else
  checkInt(A.rows());
  return CLAPACK(dpotrf)(CblasRowMajor,CblasUpper,(int)A.rows(),A.data(),
                         (int)A.rows());
#endif
}

/// Do a solve of a Matrix that has already been factored
template<class Ordinal>
inline int Cholesky_solve( const Matrix<double,Ordinal> &A,
                           Vector<double,Ordinal> &X ) {
#ifdef CMC_CHECK_BOUNDS
  assert(A.rows()==A.cols());
  assert(A.rows()==X.size());
#endif
#ifdef CMC_USE_TEUCHOS_LAPACK
  int info=0;
  const char uplo='U';
  A.lapack.POTRS(uplo,A.rows(),1,A.data(),A.rows(),X.data(),X.size(),&info);
  return info;
#else
  checkInt(A.rows());
  return CLAPACK(dpotrs)(CblasRowMajor,CblasUpper,(int)A.rows(),1,A.data(),
                         (int)A.rows(), X.data(), (int)A.rows());
#endif
}

/// Do a solve of a Matrix that has already been factored
template<class Ordinal>
inline int Cholesky_solve( const Matrix<double,Ordinal> &A,
                           Matrix<double,Ordinal> &X_transpose ) {
#ifdef CMC_CHECK_BOUNDS
  assert(A.rows()==A.cols());
  assert(A.rows()==X_transpose.cols());
#endif
#ifdef CMC_USE_TEUCHOS_LAPACK
  int info=0;
  const char uplo='U';
  A.lapack.POTRS(uplo,A.rows(),X_transpose.rows(),A.data(),A.rows(),
                 X_transpose.data(),X_transpose.cols(),&info);
  return info;
#else
  checkInt(A.rows()); checkInt(X_transpose.rows());
  return CLAPACK(dpotrs)(CblasRowMajor, CblasUpper, (int)A.rows(),
                         (int)X_transpose.rows(), A.data(),(int)A.rows(),
                        X_transpose.data(), (int)A.rows());
#endif
}

} // end namespace CMC

#endif // CMC_UTILS_HPP
