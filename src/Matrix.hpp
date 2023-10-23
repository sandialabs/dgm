#ifndef CMC_MATRIX_HPP
#define CMC_MATRIX_HPP

/** \file Matrix.hpp
    \brief CMC serial dense matrix data-structures
    \author Scott Collis
    \copyright (c)2003 Rice University
    \copyright (c)2014 Sandia National Laboratories
*/

//=============================================================================
// Concise Math Classes (CMC)
//
// Author:  S. Scott Collis
//
// Written: 10-11-2001
//
// Notes:
//
// 1) Need to make sure that reference counting (including Slice) is
// done correctly.  NOT ALWAYS THE CASE RIGHT NOW!
//
// 2) Need to make a consistent naming convention for all operators including
// Scalar-vector, vector-vector, and vector-vector-vector.
//
// 3) Need to speed up compile times by segregating Matrix and Vector (done)
//
// 4) Memory leak? (Fixed)
//
// 5) Warning:  these copy constructor symantics makes it impossible to use
//              these vectors in a std container -- this should be fixed.
//
// 6) Moved "cblas.h" and "clapack.h" out of the CMC namespace.
//
//=============================================================================

// system includes
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <cassert>
using namespace std;

#if 0
// CBLAS AND CLAPACK interface
extern "C" {
#ifdef CMC_USE_MKL
#include "mkl.h"
#else
#include "cblas.h"
#endif
}
#ifdef CMC_USE_INTERNAL_CLAPACK
// Use the CMC version of the clapack_* routines
#include "clapack.hpp"
#else
extern "C" {
// Use the ATLAS versions of the clapack_* routines
#include "clapack.h"
}
#endif
#endif

// CMC includes
#include "Slice.hpp"
#include "Vector.hpp"

// Trilinos includes
#ifdef CMC_USE_TEUCHOS_LAPACK
#include "Teuchos_LAPACK.hpp"
#endif

// If you want to read from a Matrix Market file, you must include MMio.h
#ifdef CMC_USE_MMIO
#include "MMio.hpp"
namespace mtl {
  template<class Scalar> class matrix_market_stream;
}
#endif

/// Concise Math Classes namespace
/** Contains templated classes for serial dense vectors, matrices, and slices.
    Also contains a basic timer called Stopwatch and several other useful
    utilities. */
namespace CMC {

//------------------------------------------------------------------------
//
// CMC Template Matrix class
//
//------------------------------------------------------------------------

/// CMC class for holding two-dimensional serial dense matrices
/** \note This cannot currently be usefully held in STL containers.  To do so
    we need to change the copy constructor semantics to do a deep copy instead
    of a shallow copy. */
template<typename Scalar, typename Ordinal>
class Matrix {
public:
  typedef Scalar value_type;     ///< Value type for data
  typedef Ordinal size_type;     ///< Size type
  typedef value_type* iterator;  ///< Non-const Iterator
  typedef const value_type* const_iterator;  ///< Const Iterator
private:
  Scalar *s;             ///< Start of data
  Scalar *v;             ///< Stores elements in row major format (like C)
  Ordinal d1;            ///< Number of rows
  Ordinal d2;            ///< Number of columns
  Ordinal *num_refs;     ///< Number of references to this storage
  bool own;              ///< Determines if the Matrix owns the storage or not

#ifdef CMC_USE_MMIO
  /// initialize from a matrix market file
  void initialize( mtl::matrix_market_stream<Scalar> & );
#endif

public:

#ifdef CMC_USE_TEUCHOS_LAPACK
  Teuchos::LAPACK<Ordinal,Scalar> lapack;   ///< Teuchos::LAPACK interface
#endif

  /// \name Constuctors and destructor
  //@{
  Matrix();
  Matrix(const Ordinal n1, const Ordinal n2);
  Matrix(const Ordinal n1, const Ordinal n2, const Scalar x);
  Matrix(const Matrix<Scalar,Ordinal> &);
  Matrix(Scalar*, const Ordinal n1, const Ordinal n2);
  Matrix(const Vector<Scalar,Ordinal> &, const Ordinal n1, const Ordinal n2);
#ifdef CMC_USE_MMIO
  /// Construct from an MMio file (see MMio.hpp)
  explicit Matrix(char *filename);
#endif
  ~Matrix();
  //@}

  /// \name Resize the current Matrix
  //@{
  void resize(const Ordinal x, const Ordinal y);
  void resize(const Matrix<Scalar,Ordinal> &);
  //@}

  /// \name Matrix views of memory allocated elsewhere
  //@{
  void alias(Matrix<Scalar,Ordinal> &);
  void alias(Vector<Scalar,Ordinal> &, const Ordinal n1, const Ordinal n2);
  void alias(Vector<Scalar,Ordinal> &, const Ordinal offset, const Ordinal n1,
             const Ordinal n2);
  void alias(Scalar*, const Ordinal n1, const Ordinal n2);
  void exclusive_alias(Matrix<Scalar,Ordinal> &);
  void exclusive_alias(Vector<Scalar,Ordinal> &, const Ordinal n1,
                       const Ordinal n2);
  void exclusive_alias(Vector<Scalar,Ordinal> &, const Ordinal offset,
                       const Ordinal n1, const Ordinal n2);
  //@}

  /// \name Query methods
  //@{
  /// Returns the total number of elements in this Matrix
  Ordinal size() const { return d1*d2; }
  /// Returns the size of the first dimension (rows)
  Ordinal dim1() const { return d1; }
  /// Returns the number of rows
  Ordinal rows() const { return d1; }
  /// Returns the size of the second dimension (columns)
  Ordinal dim2() const { return d2; }
  /// Returns the number of columns
  Ordinal cols() const { return d2; }
  /// Returns the number of references to this Matrix
  Ordinal nrefs() const { return num_refs ? *num_refs : 0; }
  /// Returns the ownership status
  bool get_own() const { return own; }
  /// Returns a pointer to the real storage
  Scalar* data() const { return v; };
  iterator begin() { return v; }
  iterator end() { return v+size(); }
  const_iterator begin() const { return v; }
  const_iterator end() const { return v+size(); }
  //@}

  /// \name Slice and element access
  //@{
#ifdef CMC_USE_MATRIX_ROW_SLICE
  Slice<Scalar,Ordinal> row(Ordinal i);
  ConstSlice<Scalar,Ordinal> row(Ordinal i) const;
#else
  /// Returns a vector for the ith row
  Vector<Scalar,Ordinal> row(Ordinal i);
  /// Returns a constant vector for the ith row
  const Vector<Scalar,Ordinal> row(Ordinal i) const;
#endif
  /// Returns a slice for the ith column
  Slice<Scalar,Ordinal> column(Ordinal i);
  /// Returns a constant slice for the ith column
  ConstSlice<Scalar,Ordinal> column(Ordinal i) const;

  /// Fortran-style subscript (however still 0 offset)
  Scalar& operator()(Ordinal x, Ordinal y) { 
    return *(v + x*d2 + y);
  }

  /// Fortran-style subscript (however still 0 offset)
  const Scalar operator()(Ordinal x, Ordinal y) const {
    return *(v + x*d2 + y);
}

  /// Slice access
#ifdef CMC_USE_MATRIX_ROW_SLICE
  Slice<Scalar,Ordinal> operator()(Ordinal i) { return row(i); }
#else
  Vector<Scalar,Ordinal> operator()(Ordinal i) { return row(i); }
#endif

  /// Slice access
#ifdef CMC_USE_MATRIX_ROW_SLICE
  ConstSlice<Scalar,Ordinal> operator()(Ordinal i) const { return row(i); }
#else
  const Vector<Scalar,Ordinal> operator()(Ordinal i) const { return row(i); }
#endif

  /// Standard subscript for row access
  Scalar* operator[](const Ordinal i) { 
    return v+i*d2;
  }

  /// Standard subscript for row access
  const Scalar* operator[](const Ordinal i) const { 
    return v+i*d2;
  }
  //@}

  /// \name Overload C++ operators
  //@{
  Matrix<Scalar,Ordinal> & operator=(const Matrix<Scalar,Ordinal> &);
  Matrix<Scalar,Ordinal> & operator*=(const Scalar);
  Matrix<Scalar,Ordinal> & operator+=(const Scalar);
  Matrix<Scalar,Ordinal> & operator=(const Scalar);
  //@}

#ifdef DGM_USE_GENERAL_GHOSTING
  friend class boost::serialization::access;
#endif
};

// Member functions

#ifdef CMC_USE_MATRIX_ROW_SLICE
template<typename Scalar, typename Ordinal>
inline Slice<Scalar,Ordinal> Matrix<Scalar,Ordinal>::row(Ordinal i) {
  return Slice<Scalar,Ordinal>(v,SliceData<Ordinal>(i*d2,d2,1));
}

template<typename Scalar, typename Ordinal>
inline ConstSlice<Scalar,Ordinal> Matrix<Scalar,Ordinal>::row(Ordinal i) const {
  return ConstSlice<Scalar,Ordinal>(v,SliceData<Ordinal>(i*d2,d2,1));
#else
template<typename Scalar, typename Ordinal>
inline Vector<Scalar,Ordinal> Matrix<Scalar,Ordinal>::row(Ordinal i) {
  return Vector<Scalar,Ordinal>(&v[i*d2],d2);
}

template<typename Scalar, typename Ordinal>
inline const Vector<Scalar,Ordinal> Matrix<Scalar,Ordinal>::row(Ordinal i)
const {
  return Vector<Scalar,Ordinal>(&v[i*d2],d2);
}
#endif

template<typename Scalar, typename Ordinal>
inline Slice<Scalar,Ordinal> Matrix<Scalar,Ordinal>::column(Ordinal i) {
  return Slice<Scalar,Ordinal>(v,SliceData<Ordinal>(i,d1,d2));
}

template<typename Scalar, typename Ordinal>
inline ConstSlice<Scalar,Ordinal> Matrix<Scalar,Ordinal>::column(Ordinal i)
const {
  return ConstSlice<Scalar,Ordinal>(v,SliceData<Ordinal>(i,d1,d2));
}

/// Default constructor -- no memory allocation
template<typename Scalar, typename Ordinal>
inline Matrix<Scalar,Ordinal>::Matrix() : own (false) {
  d1 = d2 = 0;
  s = v = 0;
  num_refs = 0;
}

/// Normal constructor -- makes internal storage
template<typename Scalar, typename Ordinal>
inline Matrix<Scalar,Ordinal>::Matrix(const Ordinal n1, const Ordinal n2) :
  own(true) {
  if(n1==0 && n2==0) {
    d1 = d2 = 0;
    s = v = 0;
    num_refs = 0;
  } else {
#ifdef CMC_CHECK_BOUNDS
    assert( n1 > 0 && n2 > 0);
#endif
    d1 = n1;
    d2 = n2;
    s = v = new Scalar[n1*n2];
    num_refs = new Ordinal;
    *num_refs = 1;
  }
}

/// Normal constructor -- makes internal storage and sets initial value
template<typename Scalar, typename Ordinal>
inline Matrix<Scalar,Ordinal>::Matrix(const Ordinal n1, const Ordinal n2,
                                      const Scalar x) : own(true) {
#ifdef CMC_CHECK_BOUNDS
  assert( n1 > 0 && n2 > 0);
#endif
  d1 = n1;
  d2 = n2;
  s = v = new Scalar[n1*n2];
  num_refs = new Ordinal;
  *num_refs = 1;
  this->operator=(x);
}

/// Copy constructor -- make a reference to existing storage
template<typename Scalar, typename Ordinal>
inline Matrix<Scalar,Ordinal>::Matrix(const Matrix<Scalar,Ordinal> &M)
  : own(M.get_own()) {
  d1 = M.dim1();
  d2 = M.dim2();
  s = v = M.v;
  num_refs = M.num_refs;
  if (num_refs) (*num_refs)++;
}

/// Construct a matrix that is a reference to a raw pointer
/** \warning Unsafe since calling program could delete memory. */
template<typename Scalar, typename Ordinal>
inline Matrix<Scalar,Ordinal>::Matrix(Scalar *m, const Ordinal x,
                                                 const Ordinal y) : own(false) {
#ifdef CMC_CHECK_BOUNDS
  assert(m != 0);
#endif
  d1 = x;
  d2 = y;
  s = v = m;
  num_refs = new Ordinal;
  *num_refs = 1;
}

/// Vector copy constructor
template<typename Scalar, typename Ordinal>
inline Matrix<Scalar,Ordinal>::Matrix(const Vector<Scalar,Ordinal> &m,
                                      const Ordinal x, const Ordinal y)
  : own(m.get_own()) {
  // d1 = d2 = 0;
  // s = v = 0;
  // num_refs = 0;
  // this->alias(m, x, y);
  d1 = x;
  d2 = y;
  s = v = m.data();
  num_refs = m.refs();
  //  num_refs = m.num_refs;
  if (num_refs) (*num_refs)++;
}

/// Destructor
template<typename Scalar, typename Ordinal>
inline Matrix<Scalar,Ordinal>::~Matrix<Scalar,Ordinal>() {
  if (num_refs) {
    if (*num_refs == 1) {
      if (own) delete[] s;
      delete num_refs;
    } else {
      (*num_refs)--;
    }
  }
}

/// Resize to new dimensions
template<typename Scalar, typename Ordinal>
inline void Matrix<Scalar,Ordinal>::resize(const Ordinal x, const Ordinal y) {
  d1 = x;
  d2 = y;
  if (num_refs) {
    if (*num_refs==1) {
      if (own) delete[] s;
      delete num_refs;
    } else {
      (*num_refs)--;
    }
  }
  s = v = new Scalar[d1*d2];
  num_refs = new Ordinal;
  *num_refs = 1;
  own = true;
}


/// Resize to match the dimensions of supplied Matrix
template<typename Scalar, typename Ordinal>
inline void Matrix<Scalar,Ordinal>::resize(const Matrix<Scalar,Ordinal> &m) {
  resize(m.dim1(), m.dim2());
}

/// Make an alias (view) of supplied Matrix
template<typename Scalar, typename Ordinal>
void Matrix<Scalar,Ordinal>::alias(Matrix<Scalar,Ordinal> &m) {
  d1 = m.dim1();
  d2 = m.dim2();
  if (num_refs) {
    if (*num_refs==1) {
      if (own) delete[] s;
      delete num_refs;
    } else {
      (*num_refs)--;
    }
  }
  s = v = m.v;
  num_refs = 0;
  if (num_refs) (*num_refs)++;
  own= m.get_own();
}

/// Make an exclusive alias (view) of supplied Matrix
template<typename Scalar, typename Ordinal>
void Matrix<Scalar,Ordinal>::exclusive_alias(Matrix<Scalar,Ordinal> &m) {
#ifdef CMC_CHECK_BOUNDS
  assert( *(m.num_refs) == 1);
#endif
  alias( m );
}

/// Make an alias (view) of the supplied raw memory
/** \warning Unsafe as the calling program could delete the memory. */
template<typename Scalar, typename Ordinal>
inline void Matrix<Scalar,Ordinal>::alias(Scalar *m, const Ordinal x,
                                                     const Ordinal y) {
#ifdef CMC_CHECK_BOUNDS
  assert(m != 0);
#endif
  d1 = x;
  d2 = y;
  if (num_refs) {
    if (*num_refs==1) {
      if (own) delete[] s;
      delete num_refs;
    } else {
      (*num_refs)--;
    }
  }
  s = v = m;
  num_refs = new Ordinal;
  //*num_refs = 2;
  *num_refs = 1;
  own = false;
}

/// Make an alias (view) of the supplied Vector with given bounds
template<typename Scalar, typename Ordinal>
inline void Matrix<Scalar,Ordinal>::alias(Vector<Scalar,Ordinal> &m,
                                          const Ordinal x, const Ordinal y) {
#ifdef CMC_CHECK_BOUNDS
  assert(m.v != 0);
  assert(m.size() >= x*y);
#endif
  d1 = x;
  d2 = y;
  if (num_refs) {
    if (*num_refs==1) {
      if (own) delete[] s;
      delete num_refs;
    } else {
      (*num_refs)--;
    }
  }
  s = v = m.v;
  num_refs = m.num_refs;
  if (num_refs) (*num_refs)++;
  own = m.get_own();
}

/// Make an exclusive alias (view) of the supplied Vector with given bounds
template<typename Scalar, typename Ordinal>
inline void Matrix<Scalar,Ordinal>::exclusive_alias(Vector<Scalar,Ordinal> &m,
                                                    const Ordinal x,
                                                    const Ordinal y) {
#ifdef CMC_CHECK_BOUNDS
  assert( *(m.num_refs) == 1);
#endif
  alias( m, x, y );
}

/// Make an alias (view) of the supplied Vector with given bounds
template<typename Scalar, typename Ordinal>
inline void Matrix<Scalar,Ordinal>::alias(Vector<Scalar,Ordinal> &m,
                                          const Ordinal start,
                                          const Ordinal x, const Ordinal y) {
#ifdef CMC_CHECK_BOUNDS
  assert(m.v != 0);
  assert(m.size() >= start + x*y);
#endif
  d1 = x;
  d2 = y;
  if (num_refs) {
    if (*num_refs==1) {
      if (own) delete[] s;
      delete num_refs;
    } else {
      (*num_refs)--;
    }
  }
  s = m.v;
  v = s + start;
  num_refs = m.num_refs;
  if (num_refs) (*num_refs)++;
  own = m.get_own();
}

/// Make an exclusive alias (view) of the supplied Vector with given bounds
template<typename Scalar, typename Ordinal>
inline void Matrix<Scalar,Ordinal>::exclusive_alias(Vector<Scalar,Ordinal> &m,
                                                    const Ordinal start,
                                                    const Ordinal x,
                                                    const Ordinal y) {
#ifdef CMC_CHECK_BOUNDS
  assert( *(m.num_refs) == 1);
#endif
  alias( m, start, x, y );
}

/// Multiply by a Scalar
template<typename Scalar, typename Ordinal>
inline Matrix<Scalar,Ordinal>& Matrix<Scalar,Ordinal>::operator*=(
                                                         const Scalar d) {
  Ordinal N = size();
  for (Ordinal i=0; i<N; i++) v[i] *= d;
  return *this;
}

/// Add a Scalar
template<typename Scalar, typename Ordinal>
inline Matrix<Scalar,Ordinal>& Matrix<Scalar,Ordinal>::operator+=(
                                                         const Scalar d) {
  Ordinal N = size();
  for (Ordinal i=0; i<N; i++) v[i] += d;
  return *this;
}

/// Equate to a Scalar
template<typename Scalar, typename Ordinal>
inline Matrix<Scalar,Ordinal>& Matrix<Scalar,Ordinal>::operator=(
                                                         const Scalar d) {
  using std::fill;
  fill(v, v+size(), d);
  return *this;
}

/// Set two Matrices equal to one another
template<typename Scalar, typename Ordinal>
inline Matrix<Scalar,Ordinal>& Matrix<Scalar,Ordinal>::operator=(
                                           const Matrix<Scalar,Ordinal> &m) {
  if (this == &m) return *this;   // self-test
  // if (m.size()==0) return *this;
#ifdef CMC_CHECK_BOUNDS
  assert( size() == m.size() );
  assert( rows() == m.rows() && cols() == m.cols() );
#endif
  for (Ordinal i=0; i<size(); i++) v[i] = m.v[i];
  return *this;
}

/// Free functions
template<typename Scalar, typename Ordinal>
typename Matrix<Scalar,Ordinal>::const_iterator
begin(const Matrix<Scalar,Ordinal>& m) {
  return m.begin();
}

template<typename Scalar, typename Ordinal>
typename Matrix<Scalar,Ordinal>::const_iterator
end(const Matrix<Scalar,Ordinal>& m) {
  return m.end();
}

template<typename Scalar, typename Ordinal>
typename Matrix<Scalar,Ordinal>::iterator
begin(Matrix<Scalar,Ordinal>& m) {
  return m.begin();
}

template<typename Scalar, typename Ordinal>
typename Matrix<Scalar,Ordinal>::iterator
end(Matrix<Scalar,Ordinal>& m) {
  return m.end();
}

/// Output to a stream
template<typename Scalar, typename Ordinal>
inline ostream& operator<<(ostream& os, const Matrix<Scalar,Ordinal> &m) {
  for(Ordinal x=0; x<m.dim1(); x++) {
    for(Ordinal y=0; y<m.dim2(); y++)
      os <<(m[x][y]<0?"":" ")<<m[x][y] << "\t";
    os << "\n";
  }
  return os;
}

/// Check if two Matrices are equal to one another
template<typename Scalar, typename Ordinal>
inline bool operator==(const Matrix<Scalar,Ordinal> &m,
                       const Matrix<Scalar,Ordinal> n) {
  if ( m.size() != n.size() ) return false;
  if ( m.rows() != n.rows() ) return false;
  if ( m.cols() != n.cols() ) return false;
  for (Ordinal i=0; m.size() != i; ++i) {
    if (m.data()[i] != n.data()[i]) return false;
  }
  return true;
}

} // namespace CMC

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
    const CMC::Matrix< Scalar, Ordinal > &t,
    const unsigned int file_version
){
  Ordinal d1 = t.dim1();
  Ordinal d2 = t.dim2();
  Ordinal size = t.size();
  ar & size & d1 & d2;
  for (Ordinal i = 0; i != size; i++) {
    ar & t.data()[i];
  }
}

template<class Archive, class Scalar, class Ordinal>
inline void load(
    Archive & ar,
    CMC::Matrix< Scalar, Ordinal > &t,
    const unsigned int file_version
){
  Ordinal size, d1, d2;
  ar & size & d1 & d2;
  t.resize(d1,d2);
  for (Ordinal i = 0; i != size; i++) {
    ar & t.data()[i];
  }
}

// split non-intrusive serialization function member into separate
// non intrusive save/load member functions
template<class Archive, class Scalar, class Ordinal>
inline void serialize(
    Archive & ar,
    CMC::Matrix< Scalar, Ordinal > &t,
    const unsigned int file_version
){
    boost::serialization::split_free(ar, t, file_version);
}

} // namespace serialization
} // namespace boost

#endif

#endif  // CMC_MATRIX_HPP
