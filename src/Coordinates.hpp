#ifndef DGM_COORDINATES_HPP
#define DGM_COORDINATES_HPP

/** \file Coordinates.hpp
    \brief Data-structures for holding spatial coordinates
    \author S. Scott Collis
*/

// boost includes
#include "boost/numeric/conversion/cast.hpp"
using boost::numeric_cast;

// system includes
#include <iostream>
#include <cassert>
#include <cmath>
#include <vector>
#ifdef DGM_USE_GENERAL_GHOSTING
#include <boost/serialization/serialization.hpp>
#endif
using namespace std;

// DGM includes
#include "Comm.hpp"
#include "Types.hpp"
#include "Point.hpp"

namespace DGM {

/// Coordinate class which holds a vector of coordinates
class Coordinates {
 public:
  dVector x;  ///< vector of x-coordinates
  dVector y;  ///< vector of y-coordinates
  dVector z;  ///< vector of z-coordinates

  typedef DGM::Shared<Coordinates>::Ptr Ptr;  ///< Smart Pointer

  /// Default constructor
  Coordinates() {}

  /// Construct with size N and initialize to zero
  Coordinates(const Ordinal N) {
    resize(N);
  }

  /// Copy constructor
  Coordinates(const Coordinates &rhs) {
    resize(rhs.size());
    x = rhs.x; y = rhs.y; z = rhs.z;
  }

  /// Construct a Coordinates from CMC::Vector<Scalar> for each of x, y, and z
  Coordinates(const dVector &X, const dVector &Y, const dVector &Z) {
    assert( X.size() == Y.size() && X.size() ==  Z.size() );
    resize( X.size() );
    x=X; y=Y; z=Z;
  }

  /// Construct a Coordinates from a std Vector of Point
  Coordinates(const vector<Point> &rhs ) {
      resize(boost::numeric_cast<Ordinal>(rhs.size()));
    for (Ordinal i=0; i<boost::numeric_cast<Ordinal>(rhs.size()); i++) {
      x[i] = rhs[i].x;
      y[i] = rhs[i].y;
      z[i] = rhs[i].z;
    }
  }

  /// Destructor
  ~Coordinates() {}

  /// This gives you const access to a Point
  Point operator[](const Ordinal i) const {
    return Point( x[i], y[i], z[i] );
  }

  /// Equate two Coordinates
  Coordinates & operator=(const Coordinates &rhs) {
    if (this == &rhs) return *this;   // self-test
    x = rhs.x; y = rhs.y; z = rhs.z;
    return *this;
  }

  /// Set all coordinates to a const value
  Coordinates & operator=(const Scalar rhs) {
    x=rhs; y=rhs; z=rhs;
    return *this;
  }

  /// Increment a Coordinates by another Coordinates
  const Coordinates & operator+=(const Coordinates &rhs) {
    x += rhs.x; y += rhs.y; z += rhs.z;
    return *this;
  }

  /// Increment a Coordinates by a constant
  const Coordinates & operator+=(const Scalar rhs) {
    x += rhs; y += rhs; z += rhs;
    return *this;
  }

  /// Add two Coordinates
  const Coordinates operator+(const Coordinates &rhs) {
    return Coordinates(*this) += rhs;
  }

  /// Increment all coordinates by one (not sure if this is really useful)
  const Coordinates & operator++() {
    x += 1; y += 1; z += 1;
    return *this;
  }

  /// Increment all coordinates by one (postfix version)
  const Coordinates operator++(int) { // postfix form
    Coordinates oldValue = *this;
    ++(*this);
    return oldValue;
  }

  /// Returns the number of points in the Coordinates
  Ordinal size() const { return x.size(); }

  /// Resizes the Coordinates and initializes to zero
  void resize(const Ordinal N) {
    x.resize(N); x = 0;
    y.resize(N); y = 0;
    z.resize(N); z = 0;
  }

  /// Output the Coordinates to a stream
  friend inline std::ostream & operator<<(std::ostream &, const Coordinates &);
};

/// Output the Coordinates to a stream
inline std::ostream & operator<<(std::ostream &os, const Coordinates &c) {
  for (Ordinal i=0; i<c.size(); i++)
    os << c[i] << endl;
  return os;
}

/// Make a shorthand for Coordinates since it is tedious to type
typedef Coordinates Coord;

} // namespace DGM

#endif  // DGM_COORDINATES_HPP
