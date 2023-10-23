#ifndef CMC_SLICE_HPP
#define CMC_SLICE_HPP

/** \file Slice.hpp
    \brief CMC serial dense slice data structures
    \author Scott Collis
    \copyright (c)2003 Rice University
    \copyright (c)2014 Sandia National Laboratories
*/

#include<iostream>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#include<cassert>

// Concise Math Classes namespace
namespace CMC {

//----------------------------------------------------------------------------
//
//  CMC Slice Data
//
//----------------------------------------------------------------------------

/// Data-structure to extract a slice from a CMC data structure
template<typename Ordinal>
class SliceData {
public:
  typedef Ordinal size_type;  ///< size type
private:
  size_type start_;           ///< start of the slice
  size_type size_;            ///< size of the slice
  size_type stride_;          ///< stride for this slice
public:
  /// Default constructor
  SliceData() : start_(0), size_(0), stride_(0) {}
  /// Constructor
  SliceData(size_type strt, size_type sz, size_type strd) :
    start_(strt), size_(sz), stride_(strd) {}
  /// Returns the start of the slice
  size_type start() const {return start_;}
  /// Returns the size of the slice
  size_type size() const {return size_;}
  /// Returns the stride for this slice
  size_type stride() const {return stride_;}
};

//----------------------------------------------------------------------------
//
//  CMC Slice Iterator
//
//----------------------------------------------------------------------------

/// An iterator for CMC::SliceData
template<typename Scalar, typename Ordinal>
class Slice {

public:
  typedef Scalar value_type; ///< value type of data stored in Slice
  typedef Ordinal size_type; ///< size type of the index for Slice

private:
  Scalar* v;               ///< raw pointer to storage
  SliceData<size_type> s;  ///< a slice datastructure
  size_type curr;          ///< index of current element

  /// returns a reference to the data at the prescribed index
  Scalar& ref(size_type i) const { return v[s.start()+i*s.stride()]; }

public:

  /// \name Constructors
  //@{
  /// Construct a Slice
  Slice(Scalar* vv, SliceData<Ordinal> ss) : v(vv), s(ss), curr(0) {}

  /// Copy constructor
  Slice(const Slice &S) :  v(S.v), s(S.s), curr(S.curr) {}
  //@}

  /// Returns last-plus-one element
  Slice end() const {
    Slice t = *this;
    t.curr = s.size();  // index of last-plus-one element
    return t;
  }

  /// \name Query methods
  //@{
  /// Returns the number of elements
  size_type size() const { return s.size(); }

  /// Returns the index to the start
  size_type start() const { return s.start(); }

  /// Returns the stride
  size_type stride() const { return s.stride(); }

  /// Returns a raw pointer to the first element
  Scalar* data() const { return &(ref(0)); }

  /// Returns a raw pointer to the first element
  Scalar* ptr() const { return &(ref(0)); }
  //@}

  /// \name Override C++ operators
  //@{
  /// Prefix increment the current location
  Slice &operator++() { curr++; return *this; }
  /// Postfix increment the current location
  Slice operator++(int) { Slice t = *this; curr++; return t; }

  // Using the ref method may make element access a little slower
#ifdef CMC_USE_REF_METHOD
  /// C-style subscript
  Scalar& operator[](size_type i) { return ref(i); }
  /// Fortran-style subscript
  Scalar& operator()(size_type i) { return ref(i); }
  /// Current element
  Scalar& operator*() { return ref(curr); }
#else
  /// C-style subscript
  Scalar& operator[](size_type i) { return v[s.start()+i*s.stride()]; }
  /// C-style subscript
  const Scalar& operator[](size_type i) const {
    return v[s.start()+i*s.stride()];
  }
  /// Fortran-style subscript
  Scalar& operator()(size_type i) { return v[s.start()+i*s.stride()]; }
  /// Current element
  Scalar& operator*() { return v[s.start()+curr*s.stride()]; }
#endif

  /// Equate two Slices
  Slice& operator=(const Scalar&);
  //@}

#ifdef VCC
  friend bool operator==(const Slice& p, const Slice& q);
  friend bool operator!=(const Slice& p, const Slice& q);
  friend bool operator< (const Slice& p, const Slice& q);
#else
#if (!defined(__GNUC__) || (__GNUC__ < 4))
#if 0 // fails to compile with nvcc on Cray
  friend bool operator==<>(const Slice& p, const Slice& q);
  friend bool operator!=<>(const Slice& p, const Slice& q);
  friend bool operator< <>(const Slice& p, const Slice& q);
#endif
#else
  bool operator==(const Slice& p) const;
  bool operator!=(const Slice& p) const;
  bool operator< (const Slice& p) const;
#endif
#endif

};

#if (!defined(__GNUC__) || (__GNUC__ < 4))
/// test equality
template<typename Scalar, typename Ordinal>
inline bool operator==(const Slice<Scalar,Ordinal>& p,
                       const Slice<Scalar,Ordinal>& q) {
  return p.curr==q.curr
    && p.s.stride()==q.s.stride()
    && p.s.start()==q.s.start();
}
/// test inequality
template<typename Scalar, typename Ordinal>
inline bool operator!=(const Slice<Scalar,Ordinal>& p,
                       const Slice<Scalar,Ordinal>& q) {
  return !(p==q);
}
/// test less than
template<typename Scalar, typename Ordinal>
inline bool operator<(const Slice<Scalar,Ordinal>& p,
                      const Slice<Scalar,Ordinal>& q) {
  return p.curr<q.curr
    && p.s.stride()==q.s.stride()
    && p.s.start()==q.s.start();
}

#else
/// test equality
template<typename Scalar, typename Ordinal>
inline bool Slice<Scalar,Ordinal>::operator==(const Slice<Scalar,Ordinal>& p)
  const {
  return p.curr==curr
    && p.s.stride()==s.stride()
    && p.s.start()==s.start();
}
/// test inequality
template<typename Scalar, typename Ordinal>
inline bool Slice<Scalar,Ordinal>::operator!=(const Slice<Scalar,Ordinal>& p)
  const {
  return !(p==*this);
}
/// test less than
template<typename Scalar, typename Ordinal>
inline bool Slice<Scalar,Ordinal>::operator<(const Slice<Scalar,Ordinal>& p)
  const {
  return p.curr<curr
    && p.s.stride()==s.stride()
    && p.s.start()==s.start();
}

#endif

/// equate two Slices
template<typename Scalar, typename Ordinal>
inline Slice<Scalar,Ordinal>& Slice<Scalar,Ordinal>::
operator=(const Scalar &sother) {
  for (Slice<Scalar,Ordinal> si=*this; si!=this->end(); si++) {
    *si = sother;
  }
  return *this;
}

/// output a Slice to an output stream
template<typename Scalar, typename Ordinal>
inline std::ostream& operator<<(std::ostream& os, const Slice<Scalar,Ordinal> m)
{
  typedef typename Slice<Scalar,Ordinal>::size_type size_type;
  for(size_type x=0; x<m.size(); x++) {
    os << '\t' << m[x];
    os << "\n";
  }
  return os;
}

//----------------------------------------------------------------------------
//
//  CMC Constant Slice Iterator
//
//----------------------------------------------------------------------------

/// A const iterator for CMC::SliceData
template<typename Scalar, typename Ordinal>
class ConstSlice {

public:

  typedef Scalar value_type;   ///< type of values held by slice
  typedef Ordinal size_type;   ///< type of size

private:

  Scalar *v;               ///< raw pointer to storage
  SliceData<size_type> s;  ///< a slice datastructure
  size_type curr;          ///< index of current element

  /// returns a reference to the data at the prescribed index
  const Scalar& ref(size_type i) const { return v[s.start()+i*s.stride()]; }

public:

  /// constructor
  ConstSlice(Scalar* vv, SliceData<size_type> ss): v(vv), s(ss), curr(0){}

  /// returns last-plus-one element
  ConstSlice end() const {
    ConstSlice t = *this;
    t.curr = s.size();  // index of one plus last element
    return t;
  }
  /// Prefix increment
  ConstSlice &operator++() { curr++; return *this; }
  /// Postfix increment postfix
  ConstSlice operator++(int) { ConstSlice t = *this; curr++; return t; }

  // Using the ref method may make element access a little slower
#ifdef CMC_USE_REF_METHOD
  /// C style subscript
  const Scalar& operator[](size_type i) { return ref(i); }
  /// Fortran-style subscript
  const Scalar& operator()(size_type i) { return ref(i); }
  /// Current element
  const Scalar& operator*() { return ref(curr); }
#else
  /// C style subscript
  const Scalar& operator[](size_type i) { return v[s.start()+i*s.stride()]; }
  /// Fortran-style subscript
  const Scalar& operator()(size_type i) { return v[s.start()+i*s.stride()]; }
  /// Current element
  const Scalar& operator*() { return v[s.start()+curr*s.stride()]; }
#endif

#if (!defined(__GNUC__) || (__GNUC__ < 4))
#ifdef VCC
  friend bool operator==(const ConstSlice& p, const ConstSlice& q);
  friend bool operator!=(const ConstSlice& p, const ConstSlice& q);
  friend bool operator< (const ConstSlice& p, const ConstSlice& q);
#else
  friend bool operator==<>(const ConstSlice& p, const ConstSlice& q);
  friend bool operator!=<>(const ConstSlice& p, const ConstSlice& q);
  friend bool operator< <>(const ConstSlice& p, const ConstSlice& q);
#endif
#endif
};

#if (!defined(__GNUC__) || (__GNUC__ < 4))
/// test equality
template<typename Scalar, typename Ordinal>
inline bool operator==(const ConstSlice<Scalar,Ordinal>& p,
                       const ConstSlice<Scalar,Ordinal>& q) {
  return p.curr==q.curr
    && p.s.stride()==q.s.stride()
    && p.s.start()==q.s.start();
}
/// test inequality
template<typename Scalar, typename Ordinal>
inline bool operator!=(const ConstSlice<Scalar,Ordinal>& p,
                       const ConstSlice<Scalar,Ordinal>& q) {
  return !(p==q);
}
/// test less than
template<typename Scalar, typename Ordinal>
inline bool operator<(const ConstSlice<Scalar,Ordinal>& p,
                      const ConstSlice<Scalar,Ordinal>& q) {
  return p.curr<q.curr
    && p.s.stride()==q.s.stride()
    && p.s.start()==q.s.start();
}

#endif

}  // namespace CMC

#endif
