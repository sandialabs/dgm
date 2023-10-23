#ifndef CMC_ARRAY_HPP
#define CMC_ARRAY_HPP

/** \file Array.hpp
    \brief CMC serial dense three-dimensional array data-structure
    \author Scott Collis
    \copyright (c)2003 Rice University
    \copyright (c)2014 Sandia National Laboratories
*/

// system includes
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <cassert>

// Concise Math Classes
namespace CMC {

/// Templated three-dimensional CMC::Array class
/** \note This cannot currently be usefully held in STL containers.  To do so
    we need to change the copy constructor semantics to do a deep copy instead
    of a shallow copy. */
template<class Scalar, class Ordinal>
class Array {
public:
  typedef Scalar value_type;
  typedef Ordinal size_type;
private:
  Scalar* v;            ///< Stores elements by in Row Major format (like C)
  Ordinal d1;           ///< Number of rows
  Ordinal d2;           ///< Number of columns
  Ordinal d3;           ///< Number of layers
  Ordinal *num_refs;    ///< Number of references
  Scalar*** ptr;        ///< C-pointer system
  void set_pointers();  ///< Setup C array pointers
public:

  /// \name Constructors and destructor
  //@{
  /// Default constructor with no memory allocation
  Array();

  /// Normal use constructor that allocates memory
  Array(const Ordinal n1, const Ordinal n2, const Ordinal n3);

  /// Constructor that uses a Vector's memory
  Array(const Vector<Scalar,Ordinal> &, const Ordinal n1, const Ordinal n2,
        const Ordinal n3);

  /// Copy constructor
  Array(const Array<Scalar,Ordinal> &);

  /// Destructor
  ~Array();
  //@}

  /// \name Resize methods
  //@{
  /// Resize method reallocates memory
  void resize( const Ordinal n1, const Ordinal n2, const Ordinal n3 );
  //@}

  /// \name Query methods
  //@{
  /// Overall number of storage locations
  Ordinal size() const { return d1*d2*d3; }

  /// Number of rows
  Ordinal dim1() const { return d1; }
  /// Number of rows
  Ordinal rows() const { return d1; }

  /// Number of columns
  Ordinal dim2() const { return d2; }
  /// Number of columns
  Ordinal cols() const { return d2; }

  /// Number of dimensions in depth
  Ordinal dim3() const { return d3; }
  /// Number of dimensions in depth
  Ordinal dpth() const { return d3; }

  /// Return the number of references to this storage
  Ordinal nrefs() const { return *num_refs; }

  /// Return a raw pointer to the data
  Scalar* data() const { return v; };
  //@}

  /// \name Element access
  //@{
  /// Index like a C-array
  Scalar** operator[](Ordinal i) { return ptr[i]; }

  /// Index like a C-array
  Scalar** operator[](Ordinal i) const { return ptr[i]; }

  /// Index like a Fortran array (but still zero-offset and row-major)
  Scalar &operator()(const Ordinal i, const Ordinal j, const Ordinal k) {
    return v[k+d3*j+(d3*d2)*i];
  }
  /// Index like a Fortran array (but still zero-offset and row-major)
  Scalar operator()(const Ordinal i, const Ordinal j,
                    const Ordinal k) const {
    return v[k+d3*j+(d3*d2)*i];
  }
  //@}

  /// \name Overload C++ operators
  //@{
  Array<Scalar,Ordinal> & operator=(const Array<Scalar,Ordinal> &);

  Array<Scalar,Ordinal> & operator*=(const Scalar);

  Array<Scalar,Ordinal> & operator=(const Scalar);
  //@}
};

/// Sets up the C-type array pointers
template<class Scalar, class Ordinal>
inline void Array<Scalar, Ordinal>::set_pointers() {
  if (ptr) {
    for (Ordinal i=0; i<d1; i++)
      delete[] ptr[i];
    delete[] ptr;
  }
  ptr = new Scalar**[d1];
  Scalar* p = v;
  for (Ordinal i=0; i<d1; i++) {
    ptr[i] = new Scalar*[d2];
    for (Ordinal j=0; j<d2; j++) {
      ptr[i][j] = p;
      p += d3;
    }
  }
}

/// Default constructor -- make zero size
template<class Scalar, class Ordinal>
inline Array<Scalar, Ordinal>::Array() {
  d1 = d2 = d3 = 0;
  v = 0;
  num_refs = 0;
  ptr = 0;
}

/// Normal constructor -- makes internal storage
template<class Scalar, class Ordinal>
inline Array<Scalar,Ordinal>::Array(const Ordinal x, const Ordinal y,
                                    const Ordinal z) {
#ifdef CMC_CHECK_BOUNDS
  //assert( ((x > 0) && (y > 0)) && (z > 0) );
#endif
  if (x*y*z>0) {
    d1 = x;
    d2 = y;
    d3 = z;
    v = new Scalar[d1*d2*d3];
    num_refs = new Ordinal;
    *num_refs = 1;
    ptr = 0;
    set_pointers();
  } else {
    d1 = d2 = d3 = 0;
    v = 0;
    num_refs = 0;
    ptr = 0;
  }
}

/// Copy constructor
template<class Scalar, class Ordinal>
inline Array<Scalar,Ordinal>::Array(const Array<Scalar,Ordinal> &A) {
  d1 = A.d1;
  d2 = A.d2;
  d3 = A.d3;
  v = A.v;
  num_refs = A.num_refs;
  if (num_refs) (*num_refs)++;
  ptr = 0;
  set_pointers();
}

/// Vector copy constructor
template<class Scalar, class Ordinal>
inline Array<Scalar,Ordinal>::Array(const Vector<Scalar,Ordinal> &m,
                                    const Ordinal x,
                                    const Ordinal y, const Ordinal z) {
  d1 = x;
  d2 = y;
  d3 = z;
  v = m.data();
  num_refs = m.refs();
  (*num_refs)++;
  ptr = 0;
  set_pointers();
}

/// Resize the Array
template<class Scalar, class Ordinal>
inline void Array<Scalar,Ordinal>::resize(const Ordinal x, const Ordinal y,
                                          const Ordinal z) {
  d1 = x;
  d2 = y;
  d3 = z;
  if (num_refs) {
    if (*num_refs==1) {
      delete[] v;
      delete num_refs;
    } else {
      (*num_refs)--;
    }
  }
  v = new Scalar[d1*d2*d3];
  num_refs = new Ordinal;
  *num_refs = 1;
  set_pointers();
}

/// Scale all Array values by a scalar
template<class Scalar, class Ordinal>
inline Array<Scalar,Ordinal>&
Array<Scalar,Ordinal>::operator*=(const Scalar d) {
  Ordinal N = size();
  for (Ordinal i=0; i<N; i++) v[i] *= d;
  return *this;
}

/// Set all Array values to a scalar
template<class Scalar, class Ordinal>
inline Array<Scalar,Ordinal>&
Array<Scalar,Ordinal>::operator=(const Scalar d) {
  Ordinal N = size();
  for (Ordinal i=0; i<N; i++) v[i] = d;
  return *this;
}

/// Set the values of two conforming Arrays equal
template<class Scalar, class Ordinal>
inline Array<Scalar,Ordinal>&
Array<Scalar,Ordinal>::operator=(const Array<Scalar,Ordinal> &m) {
  if (this == &m) return *this;
#ifdef CMC_CHECK_BOUNDS
  assert( size() == m.size() );
  assert( rows() == m.rows() && cols() == m.cols() && dpth() == m.dpth() );
#endif
  for (Ordinal i=0; i<size(); i++) v[i] = m.v[i];
  return *this;
}

/// Destructor
template<class Scalar, class Ordinal>
inline Array<Scalar,Ordinal>::~Array<Scalar,Ordinal>() {
  if (num_refs) {
    if (*num_refs == 1) {
      delete[] v;
      delete num_refs;
    } else {
      (*num_refs)--;
    }
    if (ptr) {
      for (Ordinal i=0; i<d1; i++)
        delete[] ptr[i];
      delete[] ptr;
    }
  }
}

/// Output to a stream
template<typename Scalar, typename Ordinal>
inline
std::ostream& operator<<(std::ostream& os, const Array<Scalar,Ordinal> &m) {
  for(Ordinal x=0; x<m.dim1(); x++) {
    for(Ordinal y=0; y<m.dim2(); y++) {
      for(Ordinal z=0; z<m.dim3(); z++)
        os <<(m(x,y,z)<0?"":" ")<<m(x,y,z)<< "\t";
      os << "\n";
    }
  }
  return os;
}


}  // namespace CMC

#endif // CMC_ARRAY_HPP
