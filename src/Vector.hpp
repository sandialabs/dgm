#ifndef CMC_VECTOR_HPP
#define CMC_VECTOR_HPP

/** \file Vector.hpp
    \brief Concise Math Classes serial dense vector.
    \author Scott Collis
    \copyright (c)2003 Rice University
    \copyright (c)2014 Sandia National Laboratories
*/

// system includes
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <functional>
#include <iomanip>
#include <iostream>
#include <sstream>

// Setup for x86 vector intrinsics
#if defined(CMC_USE_AVX) && defined(__AVX__)
#include <emmintrin.h>  // SSE2
#include <immintrin.h>  // AVX
#include <x86intrin.h>  // Other
#ifdef __FMA__
#include <fmaintrin.h>  // FMA
#endif
#if defined(__GNUC__) || defined(__PGI)
#define ALIGN16 __attribute__((__aligned__(16)))
#else
#define ALIGN16 __declspec(align(16))
#endif
#endif

// boost includes
#include <boost/math/special_functions/fpclassify.hpp>
#ifdef DGM_USE_GENERAL_GHOSTING
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#endif

// CMC includes
#include "Slice.hpp"

// To check all bounds uncomment (useful for debugging but slower, of course)
// #define CMC_CHECK_BOUNDS
// #define CMC_CHECK_ALL_BOUNDS

// Concise Math Classes namespace
namespace CMC {

// Forward declarations
template<typename Scalar, typename Ordinal>
class Matrix;

//------------------------------------------------------------------------
// CMC template Vector class
//------------------------------------------------------------------------

/// CMC class for holding serial dense vectors
/** \warning Care must be taken if you wish to hold Vector in STL containers.
    Basically, Vector is a smart pointer so that the issue is the same as
    holding any pointer in an STL container.  STL containers do a deep copy
    when they create new elements which, for a pointer, means that the new
    element is just a pointer to the old element.  If you change its value,
    you will also change the value of the original.  So, if you want to hold
    Vectors in STL containers, after adding a new element, you need to
    explicitly associate it's memory by either using \c resize or \c alias.

    \todo This could be optimized to reduce memory by have a Vector::Info
    helper class that manages a shared b, d, num_refs, and own.  This way,
    each Vector would only take 24 bytes for each Vector + 24 for each Info
    instead of 40 bytes/Vector which the current implementation takes.  Of
    course, this only saves memory when you have two or more Vectors
    that point to the same memory:  2*24+24 = 72 instead of 80 bytes.
*/
template<typename Scalar, typename Ordinal>
class Vector {

public:

  typedef Scalar value_type;             ///< scalar type
  typedef Scalar& reference;             ///< reference
  typedef const Scalar& const_reference; ///< const reference
  typedef Ordinal size_type;             ///< size type
  typedef Scalar* iterator;              ///< iterator
  typedef const Scalar* const_iterator;  ///< constant iterator

private:

  Scalar* b;           ///< base storage, the same as v except for some aliases
  Scalar* v;           ///< stores elements in an array
  Ordinal d;           ///< number of elements
  Ordinal* num_refs;   ///< number of references to representation
  bool own;            ///< determines if the Vector owns the storage or not

  static const size_t ALIGNMENT = 32;  ///< Byte alignment for AVX instructions

public:

  /// \name Constructors and destructor
  //@{
  Vector();
  explicit Vector(const Ordinal);
  Vector(const Ordinal, const Scalar);
  Vector(const Vector<Scalar,Ordinal>&);
  Vector(const Vector<Scalar,Ordinal>&, const Ordinal);
  Vector(const Vector<Scalar,Ordinal>&, const Ordinal, const Ordinal);
  Vector(Scalar*, const Ordinal);
  ~Vector();
  /// Clone a copy (deep copy) of this vector
  void clone(const Vector<Scalar,Ordinal>&in) {
    resize(in.size()); *this = in;
  }
  //@}

  void make_readonly();

  /// \name Resize the current vector
  //@{
  void resize(const Ordinal x);
  Vector<Scalar,Ordinal>& resize(const Vector<Scalar,Ordinal>&);
  //@}

  /// \name STL iterator support
  //@{
  /// returns an iterator that points to the beginning of the vector
  iterator begin() { return v; }
  /// returns a constant iterator to the beginning of the vector
  const_iterator begin() const { return v; }
  /// returns an iterator pointing to past the end of the vector
  iterator end() { return v+d; }
  /// returns a constant iterator to past the end of the vector
  const_iterator end() const { return v+d; }
  /// back references the last member in the vector
  reference back() { return v[d-1]; }
  /// back references the last member in the vector
  const_reference back() const { return v[d-1]; }
  //@}

  /// \name Raw pointer access
  //
  // Deprecated: Use ptr(), get(), data() or begin() instead.
  //
  // These are evil! They make something like A[0] ambiguous because the
  // member function operator[](int) is a match when promoting unsigned 0 to
  // int 0 and built-in operator[](Scalar *. unsigned) is a match by converting
  // the Vector A to a Scalar* using the operator below and then using
  // the built-in subscript operator for pointers. This causes compile
  // errors on some platforms.
  //@{
  //operator Scalar*(){ return v; }         ///< return C-array
  //operator Scalar*() const { return v; }  ///< return a constant C-array
  //@}

  /// \name Vector views of memory allocated elsewhere
  //@{
  void alias(Vector<Scalar,Ordinal>&);
  void alias(const Vector<Scalar,Ordinal>&);
  void alias(Vector<Scalar,Ordinal>&, const Ordinal);
  void alias(const Vector<Scalar,Ordinal>&, const Ordinal);
  void alias(Vector<Scalar,Ordinal>&, const Ordinal, const Ordinal);
  void alias(const Vector<Scalar,Ordinal>&, const Ordinal, const Ordinal);
  void alias(Scalar*, const Ordinal);
  void exclusive_alias(Vector<Scalar,Ordinal>&);
  void exclusive_alias(Vector<Scalar,Ordinal>&, const Ordinal);
  void exclusive_alias(Vector<Scalar,Ordinal>&, const Ordinal, const Ordinal);
  //@}

  /// \name Query methods
  //@{
  /// returns the number of elements in this Vector
  Ordinal size() const { return d; }
  /// returns the number of references to this same memory
  Ordinal nrefs() const { return num_refs ? *num_refs : 0; }
  /// returns a raw pointer to the storage memory
  Scalar* data() const { return v; };
  /// Needed to make compatable with slice for templated functions.
  Ordinal stride() const { return 1; };
  /// returns a raw pointer to the storage memory
  Scalar* ptr() const { return v; };
  /// returns a raw pointer to the storage memory
  Scalar* get() const { return v; };
  /// returns the pointer to the number of references
  Ordinal* refs() const { return num_refs; }
  /// returns the ownership status
  bool get_own() const { return own; }
  //@}

  /// \name Element access
  //@{
  Scalar& operator()(const Ordinal x);  // Fortran-style (zero base)
  Scalar operator()(const Ordinal x) const;

  Scalar& operator[](const Ordinal x);  // C-style subscripts
  Scalar operator[](const Ordinal x) const;
  //@}

  /// \name Overload C++ operators
  //@{
  Vector<Scalar,Ordinal>& operator=(const Vector<Scalar,Ordinal>&);
  Vector<Scalar,Ordinal>& operator=(const Slice<Scalar,Ordinal>);
  Vector<Scalar,Ordinal>& operator=(const Scalar);
  Vector<Scalar,Ordinal>& operator*=(const Scalar);
  Vector<Scalar,Ordinal>& operator*=(const Vector<Scalar,Ordinal>&);
  Vector<Scalar,Ordinal>& operator/=(const Scalar);
  Vector<Scalar,Ordinal>& operator/=(const Vector<Scalar,Ordinal>&);
  Vector<Scalar,Ordinal>& operator+=(const Scalar);
  Vector<Scalar,Ordinal>& operator+=(const Vector<Scalar,Ordinal>&);
  Vector<Scalar,Ordinal>& operator-=(const Scalar);
  Vector<Scalar,Ordinal>& operator-=(const Vector<Scalar,Ordinal>&);
  Vector<Scalar,Ordinal>& operator++();
  const Vector<Scalar,Ordinal> operator++(int);
  //@}

  /// \name Basic vector operations
  //@{
  void Add(const Vector<Scalar,Ordinal> &);
  void Add(const Vector<Scalar,Ordinal> &, const Vector<Scalar,Ordinal> &);
  void Neg();
  Vector<Scalar,Ordinal>& Zero();
  void Set(const Scalar);
  Scalar Norm() const;
  Scalar Norm2() const;
  void Sub(const Scalar);
  Vector<Scalar,Ordinal> & Sub(const Vector<Scalar,Ordinal> &);
  void Sub(const Vector<Scalar,Ordinal> &, const Vector<Scalar,Ordinal> &);
  void Mul(const Scalar);
  void Mul(const Scalar, const Vector<Scalar,Ordinal> &);
  void Recip(const Scalar);
  Scalar Dot(const Vector<Scalar,Ordinal> &) const;
  void Copy(const Vector<Scalar,Ordinal> &);
  void ScaleAdd(const Scalar, const Vector<Scalar,Ordinal> &);
  void ScaleAdd(const Scalar, const Vector<Scalar,Ordinal> &,
                const Vector<Scalar,Ordinal> &);
  void AddScale(const Scalar, const Vector<Scalar,Ordinal> &);
  void Floor(const Scalar);
  void Clamp(const Scalar, const Scalar);
  void Abs();  // make values non-negative
  Scalar Max() const;
  Scalar Min() const;
  Scalar MaxAbs() const;
  // return index along with Max / Min value
  Scalar Max(Ordinal& index) const;
  Scalar Min(Ordinal& index) const;
  Scalar Sum() const;
  void Sqrt();
  /// Return true if the vector data are all normalized numbers
  bool isNormal() const {
    using std::fpclassify;
    for (Ordinal i=0; i<size(); ++i) {
      if (fpclassify(v[i]) == FP_SUBNORMAL) return false;
    }
    return true;
  }
  /// Force all vector data to be normalized numbers
  void makeNormal() {
    using std::fpclassify;
    for (Ordinal i=0; i<size(); ++i) {
      if (fpclassify(v[i]) == FP_SUBNORMAL) v[i]=0.0;
    }
  }
  //@}

  friend void Matrix<Scalar,Ordinal>::alias(Vector<Scalar,Ordinal>&,
                                            const Ordinal,
                                            const Ordinal);
  friend void Matrix<Scalar,Ordinal>::alias(Vector<Scalar,Ordinal>&,
                                            const Ordinal,
                                            const Ordinal, const Ordinal);
  friend void Matrix<Scalar,Ordinal>::exclusive_alias(Vector<Scalar,Ordinal>&,
                                                      const Ordinal,
                                                      const Ordinal);
  friend void Matrix<Scalar,Ordinal>::exclusive_alias(Vector<Scalar,Ordinal>&,
                                                      const Ordinal,
                                                      const Ordinal,
                                                      const Ordinal);
protected:

  /// Ensures that x is between a and b
  inline static Scalar clamp(const Scalar x, const Scalar a, const Scalar b) {
    using std::max;
    using std::min;
    return max(min(x,b),a);
  }

  /// No copy construction from a pointer
  explicit Vector(const Vector<Scalar,Ordinal> *);

#ifdef DGM_USE_GENERAL_GHOSTING
  friend class boost::serialization::access;
#endif
};

//=============================================================================
//      C o n s t r u c t o r   a n d   M e m o r y   M a n a g e m e n t
//=============================================================================

/// Default constructor does no memory allocation
template<typename Scalar, typename Ordinal>
inline Vector<Scalar,Ordinal>::Vector() : own(false) {
  d = 0;
  v = 0;
  b = 0;
  num_refs = 0;
}

/// Constructor with memory allocation and initialize to zero
template<typename Scalar, typename Ordinal>
inline Vector<Scalar,Ordinal>::Vector(const Ordinal n) : own(true) {
  d = n;
  v = 0;
#ifdef CMC_USE_AVX
  if (n > 0) v = (Scalar*)_mm_malloc(n*sizeof(Scalar),ALIGNMENT);
#else
  if (0 < n) v = new Scalar[n];
#endif
  b = v;
  num_refs = new Ordinal;
  *num_refs = 1;
  this->operator=(Scalar(0.0));
}

/// Constructor with allocation and initialization
template<typename Scalar, typename Ordinal>
inline Vector<Scalar,Ordinal>::Vector(const Ordinal n, const Scalar x)
  : own(true) {
  d = n;
  v = 0;
#ifdef CMC_USE_AVX
    if (n > 0) v = (Scalar*)_mm_malloc(n*sizeof(Scalar),ALIGNMENT);
#else
    if (0 < n) v = new Scalar[n];
#endif
  b = v;
  num_refs = new Ordinal;
  *num_refs = 1;
  this->operator=(x);
}

/// Copy constructor makes a reference to a vector (same size)
/** \warning The copy constructor semantics makes it impossible to use
    these vectors in a stl container -- stl needs deep copy. */
template<typename Scalar, typename Ordinal>
inline Vector<Scalar,Ordinal>::Vector(const Vector<Scalar,Ordinal> &M)
  : own(M.get_own()) {
  d = M.size();
  v = M.v;
  b = M.b;
  num_refs = M.num_refs;
  if (num_refs) (*num_refs)++;
}

/// Copy constructor makes a reference to a vector (smaller size)
/** \warning The copy constructor semantics makes it difficult to use
    these vectors in a stl container -- stl needs deep copy. */
template<typename Scalar, typename Ordinal>
inline Vector<Scalar,Ordinal>::Vector(const Vector<Scalar,Ordinal> &M,
                                      const Ordinal x)
  : own(M.get_own()) {
#ifdef CMC_CHECK_BOUNDS
  assert( M.size() >= x);
#endif
  d = x;
  v = M.v;
  b = M.b;
  num_refs = M.num_refs;
  if (num_refs) (*num_refs)++;
}

/// Copy constructor makes a reference to a vector subset (smaller size)
/** \warning The copy constructor semantics makes it difficult to use
    these vectors in a stl container -- stl needs deep copy. */
template<typename Scalar, typename Ordinal>
inline Vector<Scalar,Ordinal>::Vector(const Vector<Scalar,Ordinal> &M,
                                      const Ordinal start,
                                      const Ordinal len)
  : own(M.get_own()) {
#ifdef CMC_CHECK_BOUNDS
  if (len > 0)   assert( M.size() >= len+start);
  if (start > 0) assert( start < M.size() );
#endif
  d = len;
  v = M.v+start;
  b = M.b;                   // here is where they are different
  num_refs = M.num_refs;
  (*num_refs)++;
}

/// Construct a vector that is a reference to a C-pointer
/** \warning Use of this is unsafe as the calling program could delete the
    memory accessed through this pointer and this Vector would never know. */
template<typename Scalar, typename Ordinal>
inline Vector<Scalar,Ordinal>::Vector(Scalar* m, const Ordinal x) : own(false) {
#ifdef CMC_CHECK_BOUNDS
  assert( m != 0 );
#endif
  d = x;
  v = m;
  b = v;
  num_refs = new Ordinal;
  *num_refs = 1;
}

/// Destructor
template<typename Scalar, typename Ordinal>
inline Vector<Scalar,Ordinal>::~Vector() {
  if (num_refs) {
    if (*num_refs==1) {
#ifdef CMC_USE_AVX
      if (own) _mm_free(b);
#else
      if (own) delete[] b;
#endif
      delete num_refs;
    } else {
      (*num_refs)--;
    }
  }
}

/// Method for allocating memory in single page of memory
/*! Doing so allows the page can be marked as either readonly or writeonly.
    Attempts to access memory withuot access triggers a seg fault
    bus error on Mac) and allows use to catch the generated signal,
    dump the call stack where the access violation occurred, and then
    change page access so the operation completes. */
template<typename Scalar, typename Ordinal>
inline void Vector<Scalar,Ordinal>::make_readonly() {
#ifdef CMC_USE_READ_ONLY
  using std::copy;
  // if (num_refs) assert(1 == *num_refs);
  // reallocate memory into own page
  Scalar *p = tsro_allocate_page(b, d);
  // initialize page of memory
  copy(b, b+d, p);
  // make this page of memory readonly
  tsro_make_readonly(p, d);
  // free old memory
  tsro_free(b, d);
  // update raw pointers
  b = v = p;
#endif
}

/// Resize the vector to have a new length
template<typename Scalar, typename Ordinal>
inline void Vector<Scalar,Ordinal>::resize(const Ordinal n) {
  d = n;
  if (num_refs) {
    if (*num_refs==1) {
#ifdef CMC_USE_AVX
      if (own) _mm_free(b);
#else
      if (own) delete[] b;
#endif
      delete num_refs;
    } else {
      (*num_refs)--;
    }
  }
  v = 0;
#ifdef CMC_USE_AVX
  if (n > 0) v = (Scalar*)_mm_malloc(n*sizeof(Scalar),ALIGNMENT);
#else
  if (0 < n) v = new Scalar[n];
#endif
  b = v;
  num_refs = new Ordinal;
  *num_refs = 1;
  own = true;
}

/// Resize the vector to be conformal to input vector
template<typename Scalar, typename Ordinal>
inline Vector<Scalar,Ordinal> &Vector<Scalar,Ordinal>::resize(
    const Vector<Scalar,Ordinal> &M)
{
  resize(M.size());
  return *this;
}

/// Create an alias (or view) of the input vector
template<typename Scalar, typename Ordinal>
inline void Vector<Scalar,Ordinal>::alias(Vector<Scalar,Ordinal> &M) {
  d = M.size();
  if (num_refs) {
    if (*num_refs==1) {
#ifdef CMC_USE_AVX
      if (own) _mm_free(b);
#else
      if (own) delete[] b;
#endif
      delete num_refs;
    } else {
      (*num_refs)--;
    }
  }
  v = M.v;
  b = M.b;
  num_refs = M.num_refs;
  if (num_refs) (*num_refs)++;
  own = M.get_own();
}

/// Create an alias (or view) of the input vector
template<typename Scalar, typename Ordinal>
inline void Vector<Scalar,Ordinal>::alias(const Vector<Scalar,Ordinal> &M) {
  d = M.size();
  if (num_refs) {
    if (*num_refs==1) {
#ifdef CMC_USE_AVX
      if (own) _mm_free(b);
#else
      if (own) delete[] b;
#endif
      delete num_refs;
    } else {
      (*num_refs)--;
    }
  }
  v = M.v;
  b = M.b;
  num_refs = M.num_refs;
  if (num_refs) (*num_refs)++;
  own = M.get_own();
}

/// Create an exclusive alias (view) of the input vector
template<typename Scalar, typename Ordinal>
inline void Vector<Scalar,Ordinal>::exclusive_alias(Vector<Scalar,Ordinal> &M) {
#ifdef CMC_CHECK_BOUNDS
  assert( *(M.num_refs) == 1);
#endif
  alias( M );
}

/// Create an alias (view) of first part of the input vector
template<typename Scalar, typename Ordinal>
inline void Vector<Scalar,Ordinal>::alias(const Vector<Scalar,Ordinal> &M,
                                          const Ordinal len) {
#ifdef CMC_CHECK_BOUNDS
  assert(M.size() >= len);
#endif
  d = len;
  if (num_refs) {
    if (*num_refs==1) {
#ifdef CMC_USE_AVX
      if (own) _mm_free(b);
#else
      if (own) delete[] b;
#endif
      delete num_refs;
    } else {
      (*num_refs)--;
    }
  }
  v = M.v;
  b = M.b;
  num_refs = M.num_refs;
  if (num_refs) (*num_refs)++;
  own = M.get_own();
}

/// Create an alias (view) of first part of the input vector
template<typename Scalar, typename Ordinal>
inline void Vector<Scalar,Ordinal>::alias(Vector<Scalar,Ordinal> &M,
                                          const Ordinal len) {
#ifdef CMC_CHECK_BOUNDS
  assert(M.size() >= len);
#endif
  d = len;
  if (num_refs) {
    if (*num_refs==1) {
      if (own) delete[] b;
      delete num_refs;
    } else {
      (*num_refs)--;
    }
  }
  v = M.v;
  b = M.b;
  num_refs = M.num_refs;
  if (num_refs) (*num_refs)++;
  own = M.get_own();
}

/// Create an exclusive alias (view) of first part of the input vector
template<typename Scalar, typename Ordinal>
inline void Vector<Scalar,Ordinal>::exclusive_alias(Vector<Scalar,Ordinal> &M,
                                                    const Ordinal len) {
#ifdef CMC_CHECK_BOUNDS
  assert( *(M.num_refs) == 1);
#endif
  alias( M, len );
}

/// Make an alias (view) of a subset of the input vector
template<typename Scalar, typename Ordinal>
inline void Vector<Scalar,Ordinal>::alias(Vector<Scalar,Ordinal> &M,
                                          const Ordinal start,
                                          const Ordinal len) {
#ifdef CMC_CHECK_BOUNDS
  if (len > 0) assert( (M.size()-start) >= len);
  if (start > 0) assert( start < M.size() );
#endif
  d = len;
  if (num_refs) {
    if (*num_refs==1) {
      if (own) delete[] b;
      delete num_refs;
    } else {
      (*num_refs)--;
    }
  }
  v = M.v+start;
  b = M.b;                   // here is where they are different
  num_refs = M.num_refs;
  if (num_refs) (*num_refs)++;
  own = M.get_own();
}

/// Make an alias (view) of a subset of the input vector
template<typename Scalar, typename Ordinal>
inline void Vector<Scalar,Ordinal>::alias(const Vector<Scalar,Ordinal> &M,
                                          const Ordinal start,
                                          const Ordinal len){
#ifdef CMC_CHECK_BOUNDS
  assert( (M.size()-start) >= len);
#endif
  d = len;
  if (num_refs) {
    if (*num_refs==1) {
      if (own) delete[] b;
      delete num_refs;
    } else {
      (*num_refs)--;
    }
  }
  v = M.v+start;
  b = M.b;
  num_refs = M.num_refs;
  if (num_refs) (*num_refs)++;
  own = M.get_own();
}

/// Make an exclusive alias (view) of a subset of the input vector
template<typename Scalar, typename Ordinal>
inline void Vector<Scalar,Ordinal>::exclusive_alias(Vector<Scalar,Ordinal> &M,
                                                    const Ordinal start,
                                                    const Ordinal len) {
#ifdef CMC_CHECK_BOUNDS
  assert( *(M.num_refs) == 1);
#endif
  alias( M, start, len );
}

/// Make an alias (view) of a raw pointer with length
/** \warning This is unsafe as the calling program could delete the memory. */
template<typename Scalar, typename Ordinal>
inline void Vector<Scalar,Ordinal>::alias(Scalar *m, const Ordinal len) {
#ifdef CMC_CHECK_BOUNDS
  assert(m != 0);
#endif
  d = len;
  if (num_refs) {
    if (*num_refs==1) {
      if (own) delete[] b;
      delete num_refs;
    } else {
      (*num_refs)--;
    }
  }
  v = m;
  b = v;
  num_refs = new Ordinal;
  *num_refs = 1;
  own = false;
}

//=============================================================================
//           I n d e x i n g   a n d   a c c e s s   m e t h o d s
//=============================================================================

/// vector indexing
template<typename Scalar, typename Ordinal>
inline Scalar& Vector<Scalar,Ordinal>::operator()(const Ordinal i) {
#if defined(CMC_CHECK_BOUNDS) && defined(CMC_CHECK_ALL_BOUNDS)
  assert(i >= 0 && i < d);
#endif
  return v[i];
}

/// vector indexing
template<typename Scalar, typename Ordinal>
inline Scalar Vector<Scalar,Ordinal>::operator()(const Ordinal i) const {
#if defined(CMC_CHECK_BOUNDS) && defined(CMC_CHECK_ALL_BOUNDS)
  assert(i >= 0 && i < d);
#endif
  return v[i];
}

/// vector indexing
template<typename Scalar, typename Ordinal>
inline Scalar& Vector<Scalar,Ordinal>::operator[](const Ordinal i) {
#if defined(CMC_CHECK_BOUNDS) && defined(CMC_CHECK_ALL_BOUNDS)
  assert(i >= 0 && i < d);
#endif
  return v[i];
}

/// vector indexing
template<typename Scalar, typename Ordinal>
inline Scalar Vector<Scalar,Ordinal>::operator[](const Ordinal i) const {
#if defined(CMC_CHECK_BOUNDS) && defined(CMC_CHECK_ALL_BOUNDS)
  assert(i >= 0 && i < d);
#endif
  return v[i];
}

/// set the values of this Vector to equal a Scalar
template<typename Scalar, typename Ordinal>
inline Vector<Scalar,Ordinal>&
Vector<Scalar,Ordinal>::operator=(const Scalar value) {
  using std::fill;
  fill(v, v+size(), value);
  return *this;
}

/// scale the vector
template<typename Scalar, typename Ordinal>
inline Vector<Scalar,Ordinal>&
Vector<Scalar,Ordinal>::operator*=(const Scalar value) {
  Ordinal N = size();
  for (Ordinal i=0; i<N; i++) v[i] *= value;
  return *this;
}

/// scale the vector
template<typename Scalar, typename Ordinal>
inline Vector<Scalar,Ordinal>&
Vector<Scalar,Ordinal>::operator/=(const Scalar value) {
  Ordinal N = size();
  for (Ordinal i=0; i<N; i++) v[i] /= value;
  return *this;
}

/// shift the vector
template<typename Scalar, typename Ordinal>
inline Vector<Scalar,Ordinal>&
Vector<Scalar,Ordinal>::operator+=(const Scalar value) {
  Ordinal N = size();
  for (Ordinal i=0; i<N; i++) v[i] += value;
  return *this;
}

/// shift the vector
template<typename Scalar, typename Ordinal>
inline Vector<Scalar,Ordinal>&
Vector<Scalar,Ordinal>::operator-=(const Scalar value) {
  Ordinal N = size();
  for (Ordinal i=0; i<N; i++) v[i] -= value;
  return *this;
}

/// sets the values of two conforming vectors equal
template<typename Scalar, typename Ordinal>
inline Vector<Scalar,Ordinal>&
Vector<Scalar,Ordinal>::operator=(const Vector<Scalar,Ordinal> &rhs) {
  if (this == &rhs) return *this;   // self-test
#ifdef CMC_CHECK_BOUNDS
  assert( size() == rhs.size() );
#endif
  for (Ordinal i=0; i<size(); i++) v[i] = rhs.v[i];
  return *this;
}

/// adds the values of two conforming vectors
template<typename Scalar, typename Ordinal>
inline Vector<Scalar,Ordinal>&
Vector<Scalar,Ordinal>::operator+=(const Vector<Scalar,Ordinal> &rhs) {
#ifdef CMC_CHECK_BOUNDS
  assert( size() == rhs.size() );
#endif
  for (Ordinal i=0; i<size(); i++) v[i] += rhs.v[i];
  return *this;
}

/// subtracts the input vector from the values of this vector
template<typename Scalar, typename Ordinal>
inline Vector<Scalar,Ordinal>&
Vector<Scalar,Ordinal>::operator-=(const Vector<Scalar,Ordinal> &rhs) {
#ifdef CMC_CHECK_BOUNDS
  assert( size() == rhs.size() );
#endif
  for (Ordinal i=0; i<size(); i++) v[i] -= rhs.v[i];
  return *this;
}

/// multiply the values of two conforming vectors elementwise
template<typename Scalar, typename Ordinal>
inline Vector<Scalar,Ordinal>&
Vector<Scalar,Ordinal>::operator*=(const Vector<Scalar,Ordinal> &rhs) {
#ifdef CMC_CHECK_BOUNDS
  assert( size() == rhs.size() );
#endif
  for (Ordinal i=0; i<size(); i++) v[i] *= rhs.v[i];
  return *this;
}

/// divide the values of two conforming vectors elementwise
template<typename Scalar, typename Ordinal>
inline Vector<Scalar,Ordinal>&
Vector<Scalar,Ordinal>::operator/=(const Vector<Scalar,Ordinal> &rhs) {
#ifdef CMC_CHECK_BOUNDS
  assert( size() == rhs.size() );
#endif
  for (Ordinal i=0; i<size(); i++) v[i] /= rhs.v[i];
  return *this;
}

/// Prefix increment operator
template<typename Scalar, typename Ordinal>
inline Vector<Scalar,Ordinal>& Vector<Scalar,Ordinal>::operator++() {
  for (Ordinal i=0; i<size(); i++) v[i]++;
  return *this;
}

/// Postfix increment operator
template<typename Scalar, typename Ordinal>
inline const Vector<Scalar,Ordinal> Vector<Scalar,Ordinal>::operator++(int) {
  Vector<Scalar,Ordinal> oldValue = *this;
  ++(*this);
  return oldValue;
}

/// equate the values of this vector to those of a slice
template<typename Scalar, typename Ordinal>
inline Vector<Scalar,Ordinal>&
Vector<Scalar,Ordinal>::operator=(const Slice<Scalar,Ordinal> m) {
#ifdef CMC_CHECK_BOUNDS
  assert( size() == m.size() );
#endif
  for (Ordinal i=0; i<size(); i++) v[i] = m[i];
  return *this;
}

/// pretty output of vector values
template<typename Scalar, typename Ordinal>
inline std::ostream& operator<<(std::ostream &os,
                                const Vector<Scalar,Ordinal> &m) {
  using std::setw;
  os << "Vector.size() = " << m.size() << "\n";
  for(Ordinal i=0; i<m.size(); i++) {
    //os << '\t' << m[i];
    os << setw(10) << m[i];
    os << "\n";
  }
  return os;
}

//=============================================================================
//              B a s i s   v e c t o r   o p e r a t i o n s
//=============================================================================

/// multiply a vector by a scalar (A = alpha * A)
template<typename Scalar, typename Ordinal>
inline void multiply(const Scalar alpha, Vector<Scalar,Ordinal> &A) {
  Ordinal N = A.size();
  for (Ordinal i=0; i<N; i++) A[i] = alpha * A[i];
}

/// multiply a vector by a vector (B = B * A)
template<typename Scalar, typename Ordinal>
inline void multiply(const Vector<Scalar,Ordinal> &A,
                     Vector<Scalar,Ordinal> &B) {
  Ordinal N = A.size();
#ifdef CMC_CHECK_BOUNDS
  assert(N==B.size());
#endif
  for (Ordinal i=0; i<N; ++i) B[i] *= A[i];
}

/// divide vector values by a Scalar (B = alpha / A_i)
template<typename Scalar, typename Ordinal>
inline void divide(const Scalar alpha, const Vector<Scalar,Ordinal> &A,
                   Vector<Scalar,Ordinal> &B) {
  Ordinal N = A.size();
#ifdef CMC_CHECK_BOUNDS
  assert(N==B.size());
#endif
  for (Ordinal i=0; i<N; i++) B[i] = alpha / A[i];
}

/// invert vector (A = 1.0 / A)
template<typename Scalar, typename Ordinal>
inline void invert(Vector<Scalar,Ordinal> &A) {
  Ordinal N = A.size();
  for (Ordinal i=0; i<N; i++) A[i] = 1.0 / A[i];
}

/// subtract a vector from a Scalar (B_i = alpha - A)
template<typename Scalar, typename Ordinal>
inline void subtract(const Scalar alpha, const Vector<Scalar,Ordinal> &A,
                     Vector<Scalar,Ordinal> &B) {
  Ordinal N = A.size();
#ifdef CMC_CHECK_BOUNDS
  assert(N==B.size());
#endif
  for (Ordinal i=0; i<N; i++) B[i] = alpha - A[i];
}

/// add a vector and a Scalar (B_i = A_i + alpha)
template<typename Scalar, typename Ordinal>
inline void add(const Scalar alpha, const Vector<Scalar,Ordinal> &A,
                Vector<Scalar,Ordinal> &B) {
  Ordinal N = A.size();
#ifdef CMC_CHECK_BOUNDS
  assert(N==B.size());
#endif
  for (Ordinal i=0; i<N; i++) B[i] = A[i] + alpha;
}

//=============================================================================
//             B a s i c   V e c t o r   O p e r a t i o n s
//=============================================================================

/// add two conformal vectors and put the result in this vector
template<typename Scalar, typename Ordinal>
inline void Vector<Scalar,Ordinal>::Add(const Vector<Scalar,Ordinal> &A) {
  Ordinal N = A.size();
#ifdef CMC_CHECK_BOUNDS
  assert(N==size());
#endif
  for (Ordinal i=0; i<N; i++) (*this)[i] += A[i];
}

/// add two vectors and put their sum in this vector
template<typename Scalar, typename Ordinal>
inline void Vector<Scalar,Ordinal>::Add(const Vector<Scalar,Ordinal> &A,
                                const Vector<Scalar,Ordinal> &B) {
  Ordinal N = A.size();
#ifdef CMC_CHECK_BOUNDS
  assert(N==size());
  assert(B.size()==size());
#endif
  for (Ordinal i=0; i<N; i++) (*this)[i] = A[i] + B[i];
}

/// negate this vector
template<typename Scalar, typename Ordinal>
inline void Vector<Scalar,Ordinal>::Neg() {
  using std::negate;
  using std::transform;
  transform(begin(), end(), begin(), negate<Scalar>());
}

/// zero this vector
template<typename Scalar, typename Ordinal>
inline Vector<Scalar,Ordinal>& Vector<Scalar,Ordinal>::Zero() {
  using std::fill;
  fill(begin(), end(), 0.0);
  return *this;
}

/// set the value of this vector to a Scalar
template<typename Scalar, typename Ordinal>
inline void Vector<Scalar,Ordinal>::Set(const Scalar alpha) {
  for (Ordinal i=0; i<size(); i++) (*this)[i] = alpha;
}

/// returns the Euclidian norm of this vector
template<typename Scalar, typename Ordinal>
inline Scalar Vector<Scalar,Ordinal>::Norm() const {
  Scalar result = 0.0;
  for (Ordinal i=0; i<size(); i++) result += (*this)[i] * (*this)[i];
  return sqrt(result);
}

/// returns the Euclidian norm squared for this vector
template<typename Scalar, typename Ordinal>
inline Scalar Vector<Scalar,Ordinal>::Norm2() const {
  Scalar result = 0.0;
  for (Ordinal i=0; i<size(); i++) result += (*this)[i] * (*this)[i];
  return result;
}

/// subtracts a Scalar off of this vector
template<typename Scalar, typename Ordinal>
inline void Vector<Scalar,Ordinal>::Sub(const Scalar a) {
  for (Ordinal i=0; i<size(); i++) (*this)[i] -= a;
}

/// subtracts a vector off of this vector
template<typename Scalar, typename Ordinal>
inline Vector<Scalar,Ordinal> &Vector<Scalar,Ordinal>::Sub(
    const Vector<Scalar,Ordinal> &A)
{
  Ordinal N = A.size();
#ifdef CMC_CHECK_BOUNDS
  assert(N==size());
#endif
  for (Ordinal i=0; i<N; i++) (*this)[i] -= A[i];
  return *this;
}

/// subtracts two vectors and puts the result in this vector
template<typename Scalar, typename Ordinal>
inline void Vector<Scalar,Ordinal>::Sub(const Vector<Scalar,Ordinal> &A,
                                const Vector<Scalar,Ordinal> &B) {
  Ordinal N = A.size();
#ifdef CMC_CHECK_BOUNDS
  assert(N==size());
  assert(B.size()==size());
#endif
  for (Ordinal i=0; i<N; i++) (*this)[i] = A[i] - B[i];
}

/// multiply this vector by a Scalar
template<typename Scalar, typename Ordinal>
inline void Vector<Scalar,Ordinal>::Mul(const Scalar alpha) {
  for (Ordinal i=0; i<size(); i++) (*this)[i] *= alpha;
}

/// scale a vector by a Scalar and put the result in this vector
template<typename Scalar, typename Ordinal>
inline void Vector<Scalar,Ordinal>::Mul(const Scalar alpha,
                                        const Vector<Scalar,Ordinal> &A) {
  Ordinal N = A.size();
#ifdef CMC_CHECK_BOUNDS
  assert(N==size());
#endif
  for (Ordinal i=0; i<N; i++) (*this)[i] = alpha * A[i];
}

/// multiply the reciprocal of this vector by a Scalar
template<typename Scalar, typename Ordinal>
inline void Vector<Scalar,Ordinal>::Recip(const Scalar alpha) {
  for (Ordinal i=0; i<size(); i++) (*this)[i] = alpha/(*this)[i];
}

/// compute the dot-product of two vectors
template<typename Scalar, typename Ordinal>
inline Scalar Vector<Scalar,Ordinal>::Dot(const Vector<Scalar,Ordinal> &A)
  const {
  Ordinal N = A.size();
#ifdef CMC_CHECK_BOUNDS
  assert(N==size());
#endif
  Scalar result = 0.0;
  for (Ordinal i=0; i<N; i++) result += (*this)[i] * A[i];
  return result;
}

/// copy the values of the input vector Ordinalo this vector
template<typename Scalar, typename Ordinal>
inline void Vector<Scalar,Ordinal>::Copy(const Vector<Scalar,Ordinal> &A) {
  Ordinal N = A.size();
#ifdef CMC_CHECK_BOUNDS
  assert(N==size());
#endif
  for (Ordinal i=0; i<N; i++) (*this)[i] = A[i];
}

/// scale this vector and add with another vector with result in this vector
template<typename Scalar, typename Ordinal>
inline void Vector<Scalar,Ordinal>::ScaleAdd(const Scalar alpha,
                                             const Vector<Scalar,Ordinal> &A) {
  Ordinal N = A.size();
#ifdef CMC_CHECK_BOUNDS
  assert(N==size());
#endif
  for (Ordinal i=0; i<N; i++) (*this)[i] = alpha*(*this)[i] + A[i];
}

/// scale input vector and add with another vector with result in this vector
template<typename Scalar, typename Ordinal>
inline void Vector<Scalar,Ordinal>::ScaleAdd(const Scalar alpha,
                                             const Vector<Scalar,Ordinal> &A,
                                             const Vector<Scalar,Ordinal> &B) {
  Ordinal N = A.size();
#ifdef CMC_CHECK_BOUNDS
  assert(N==size());
  assert(B.size()==size());
#endif
  for (Ordinal i=0; i<N; i++) (*this)[i] = alpha*A[i] + B[i];
}

/// add a scaled vector to this vector
template<typename Scalar, typename Ordinal>
inline void Vector<Scalar,Ordinal>::AddScale(const Scalar alpha,
                                             const Vector<Scalar,Ordinal> &A) {
  Ordinal N = A.size();
#ifdef CMC_CHECK_BOUNDS
  assert(N==size());
#endif
  for (Ordinal i=0; i<N; i++) (*this)[i] += alpha*A[i];
}

/// floor a vector to zero if values are less then input
template<typename Scalar, typename Ordinal>
inline void Vector<Scalar,Ordinal>::Floor(const Scalar floor) {
  using std::abs;
  for (Ordinal i=0; i<size(); i++) {
    Scalar value = (*this)[i];
    if (abs(value) <= floor) (*this)[i] = 0.0;
  }
}

/// clamp the values of a vector between a low and high values
template<typename Scalar, typename Ordinal>
inline void Vector<Scalar,Ordinal>::Clamp(const Scalar low, const Scalar high) {
  for (Ordinal i=0; i<size(); i++) {
    Scalar value = (*this)[i];
    (*this)[i] = clamp( value, low, high );
  }
}

/// absolute value
template<typename Scalar, typename Ordinal>
inline void Vector<Scalar,Ordinal>::Abs() {
  using std::abs;
  for (iterator it = begin(); it != end(); ++it)
    *it = abs(*it);
}

/// return the maximum absolute value in the vector
template<typename Scalar, typename Ordinal>
inline Scalar Vector<Scalar,Ordinal>::MaxAbs() const {
  using std::abs;
  using std::max;
  assert(size()!=0);
  const_iterator it = begin();
  Scalar result = abs(*it);
  for (++it; it != end(); ++it) result = max(abs(*it), result);
  return result;
}

/// return the maximum value in the vector
template<typename Scalar, typename Ordinal>
inline Scalar Vector<Scalar,Ordinal>::Max() const {
  using std::max_element;
  assert(size()!=0);
  return *max_element(begin(), end());
}

/// return the maximum value in the vector along
/// with the element id where it occurred
template<typename Scalar, typename Ordinal>
inline Scalar Vector<Scalar,Ordinal>::Max(Ordinal& index) const {
  using std::max_element;
  assert(size()!=0);
  const_iterator it = max_element(begin(), end());
  index = it - begin();
  return *it;
}

/// return the minimum value in the vector
template<typename Scalar, typename Ordinal>
inline Scalar Vector<Scalar,Ordinal>::Min() const {
  using std::min_element;
  assert(size()!=0);
  return *min_element(begin(), end());
}

/// return the minimum value in the vector along
/// with the element id where it occurred
template<typename Scalar, typename Ordinal>
inline Scalar Vector<Scalar,Ordinal>::Min(Ordinal& index) const {
  using std::min_element;
  assert(size()!=0);
  const_iterator it = min_element(begin(), end());
  index = it - begin();
  return *it;
}

/// Free functions

template<typename Scalar, typename Ordinal>
typename Vector<Scalar, Ordinal>::const_iterator
begin(const Vector<Scalar, Ordinal>& v) {
  return v.begin();
}

template<typename Scalar, typename Ordinal>
typename Vector<Scalar, Ordinal>::const_iterator
end(const Vector<Scalar, Ordinal>& v) {
  return v.end();
}

template<typename Scalar, typename Ordinal>
typename Vector<Scalar, Ordinal>::iterator
begin(Vector<Scalar, Ordinal>& v) {
  return v.begin();
}

template<typename Scalar, typename Ordinal>
typename Vector<Scalar, Ordinal>::iterator
end(Vector<Scalar, Ordinal>& v) {
  return v.end();
}

/// return the sum of all elements in the vector
template<typename Scalar, typename Ordinal>
inline Scalar Vector<Scalar,Ordinal>::Sum() const {
  Scalar result = (Scalar)0.0;
  for (Ordinal i=0; i<size(); i++) {
    result += (*this)[i];
  }
  return result;
}

/// take the component-wise sqrt of a vector
template<typename Scalar, typename Ordinal>
inline void Vector<Scalar,Ordinal>::Sqrt() {
  for (Ordinal i=0; i<size(); i++) (*this)[i] = sqrt((*this)[i]);
}

//=============================================================================
//               N o n - m e m b e r   F u n c t i o n s
//=============================================================================

/// Provides a less-than operator that works for unequal length vectors
template<typename Scalar, typename Ordinal>
inline bool operator<
(const Vector<Scalar,Ordinal> &u, const Vector<Scalar,Ordinal> &v) {
  Ordinal i=0;
  while (u.size() != i) {
    if (v.size() == i) return false;  // SSC added to prevent out of bounds
    const Scalar d = v[i] - u[i];
    if ( d < 0 || v.size() == i) return false;
    if ( 0 < d                 ) return true;
    ++i;
  }
  return (v.size() != i);
}

/// Determines if two vectors are equal accounting for different lengths
template<typename Scalar, typename Ordinal>
inline bool operator==
(const Vector<Scalar,Ordinal> &u, const Vector<Scalar,Ordinal> &v) {
  if (u.size() != v.size()) return false;
  for (Ordinal i=0; u.size() != i; ++i) {
    if (u[i] != v[i]) return false;
  }
  return true;
}

/// Determine if two scalars are approximately equal
template<typename Scalar>
inline bool approx_equal(const Scalar u, const Scalar v,
                         const Scalar REL = 1.0e-8, const Scalar ABS=1.0e-8) {
  using std::abs;
  using std::max;
  if (u == v) return true;
  const Scalar diff = abs(u - v);
  if (diff <= ABS) return true;
  const Scalar ref = max(abs(u),abs(v));
  return (diff <= REL*ref );
}

/// Determine if two scalars are approximately less then
template<typename Scalar>
inline int approx_less(const Scalar u,
                       const Scalar v,
                       const Scalar REL = 1.0e-8,
                       const Scalar ABS = 1.0e-8) {
  if      (approx_equal(u,v,REL,ABS)) return  0;
  else if (u<v)                       return  1;
  else                                return -1;
}

/// Determines if two vectors are approximately equal
template<typename Scalar, typename Ordinal>
inline bool approx
(const Vector<Scalar,Ordinal> &u, const Vector<Scalar,Ordinal> &v,
 const Scalar REL, const Scalar ABS) {
  if (u.size() != v.size()) return false;
  Ordinal i=0;
  for (; u.size() != i && v.size() != i; ++i) {
    if (!approx_equal(u[i],v[i],REL,ABS)) return false;
  }
  return (v.size() == i && u.size() == i);
}

/// Provides an approximately less-than that works for unequal length vectors
template<typename Scalar, typename Ordinal>
inline bool approx_less
(const Vector<Scalar,Ordinal> &u, const Vector<Scalar,Ordinal> &v,
 const Scalar REL, const Scalar ABS) {
                                         // If u and v are of different lengths
  if      (u.size() < v.size()) return true;  // make sure that switching
  else if (v.size() < u.size()) return false; // u and v returns true one way
                                         // and false the other.
  else {                                 // else: same length.
    for (Ordinal i=0; i!=u.size(); ++i) {
      const int s = approx_less(u[i],v[i],REL,ABS);
      if      (0<s) return true;
      else if (s<0) return false;
    }
  }
  return false; // must be approx_equal for every i, so NOT LESS
}

/// This is a wrapper for a CMC::Vector that uses deepcopy construction
/*! Be advised that this type of Vector works more as expected when held
    in a std container but that in general you should make sure to pass
    this type by reference and not value as there will be a deep-copy
    if you pass by value */
template <typename Scalar, typename Ordinal>
class RefVector : public CMC::Vector<Scalar,Ordinal> {
public:
  RefVector() : Vector<Scalar,Ordinal>() {}
  /// Copy constructor needs to allocate new memory via resize
  RefVector(const RefVector &in) : CMC::Vector<Scalar,Ordinal>() {
    Vector<Scalar,Ordinal> &self = *this;
    self.resize(in.size());
    self = in;
  }
  /// Needs to be able to construct from a dVector too
  RefVector(const Vector<Scalar,Ordinal> &in) : CMC::Vector<Scalar,Ordinal>() {
    Vector<Scalar,Ordinal> &self = *this;
    self.resize(in.size());
    self = in;
  }
};

}  // namespace CMC

#ifdef DGM_USE_GENERAL_GHOSTING
/////////////////////////////////////////////////////////////
// implement serialization for CMC::Vector< Scalar, Ordinal >
// note: this must be added to the boost namespace in order to
// be called by the library
namespace boost {
namespace serialization {

template<class Archive, class Scalar, class Ordinal>
inline void save(
    Archive & ar,
    const CMC::Vector< Scalar, Ordinal > &t,
    const unsigned int file_version
){
  Ordinal size = t.size();
  ar & size;
  for (Ordinal i = 0; i != size; i++) {
    ar & t.data()[i];
  }
}

template<class Archive, class Scalar, class Ordinal>
inline void load(
    Archive & ar,
    CMC::Vector< Scalar, Ordinal > &t,
    const unsigned int file_version
){
  Ordinal size;
  ar & size;
  t.resize(size);
  for (Ordinal i = 0; i != size; i++) {
    ar & t.data()[i];
  }
}

// split non-intrusive serialization function member into separate
// non intrusive save/load member functions
template<class Archive, class Scalar, class Ordinal>
inline void serialize(
    Archive & ar,
    CMC::Vector< Scalar, Ordinal > &t,
    const unsigned int file_version
){
    boost::serialization::split_free(ar, t, file_version);
}

} // namespace serialization
} // namespace boost

namespace CMC {

template<typename Scalar, typename Ordinal>
static int test_CMC_Vector_serialization() {
  using std::cout;
  using std::endl;
  using std::flush;
  using std::istringstream;
  using std::ostringstream;
  using std::string;

  cout << "CMC::test_CMC_Vector_serialization: " << flush;

  // create test data
  CMC::Vector<Scalar,Ordinal> v(5);
  v(0) = 1;
  v(1) = 2;
  v(2) = 3;
  v(3) = 4;
  v(4) = 5;

  // serialize
  ostringstream sendstream;
  boost::archive::binary_oarchive oar(sendstream);
  oar & v;
  string sendstring(sendstream.str());

  // dummy transfer: this could be a distributed memory data transfer
  string recvstring = sendstring;

  // deserialize
  string s(recvstring);
  istringstream recvstream(s);
  boost::archive::binary_iarchive iar(recvstream);
  CMC::Vector<Scalar,Ordinal> v_new;
  iar & v_new;

  // test size
  int status = 0;
  if (v.size() != v_new.size())  status = -1;

  // test content
  for (Ordinal i=0; i != v.size();i++) {
    if (v[i] != v_new[i])  status = -1;
  }

  if (status != 0) {
    cout << endl;
    cout << v << endl;
    cout << v_new << endl;
  }

  if (status)
    cout << "Test FAILED" << endl;
  else
    cout << "Test SUCCESS" << endl;

  return status;
}

} // namespace CMC

#endif // DGM_USE_GENERAL_GHOSTING

#endif // CMC_VECTOR_HPP
