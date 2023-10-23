#ifndef DGM_EUCLIDEAN_VECTOR_HPP
#define DGM_EUCLIDEAN_VECTOR_HPP

/** \file EuclideanVector.hpp
    \brief Data-structures for holding Euclidean vectors 
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

/// Euclidean vector
/*! Defines a Euclidean vector with origin (0,0,0) 
    This could/should be fleshed out to include:
      - Arbitrary bases
      - Specification of origin
      - Various basic operations
      - Coordinate transformations
*/
class EuclideanVector {
public:
  Scalar x;     ///< x coordinate 
  Scalar y;     ///< y coordinate 
  Scalar z;     ///< z coordinate 
  /// default constructor  
  EuclideanVector() : x(0), y(0), z(0) { }
  /// construct from a point 
  EuclideanVector(const Point &p1) {
    x = p1.x;
    y = p1.y;
    z = p1.z;
  }
  /// construct from two points
  EuclideanVector(const Point &p1, const Point &p2) {
    x = p2.x - p1.x;
    y = p2.y - p1.y;
    z = p2.z - p1.z;
  }
  /// copy constructor
  EuclideanVector(const EuclideanVector &rhs) {
    x = rhs.x; y = rhs.y; z = rhs.z;
  }
  /// add two vectors
  EuclideanVector & operator+=(const EuclideanVector &rhs) {
    x += rhs.x; y += rhs.y; z += rhs.z;
    return *this;
  }
  /// scalar decrement
  EuclideanVector & operator-=(const EuclideanVector &rhs) {
    x -= rhs.x; y -= rhs.y; z -= rhs.z;
    return *this;
  }
  /// scalar increment
  EuclideanVector & operator+=(const Scalar rhs) {
    x += rhs; y += rhs; z += rhs;
    return *this;
  }
  /// scalar multiply
  EuclideanVector & operator*=(const Scalar rhs) {
    x *= rhs; y *= rhs; z *= rhs;
    return *this;
  }
  /// scalar divide
  EuclideanVector & operator/=(const Scalar rhs) {
    x /= rhs; y /= rhs; z /= rhs;
    return *this;
  }
  /// normalize the current vector to unit length
  void normalize() {
    const Scalar length = norm();
    x /= length;
    y /= length;
    z /= length;
  }
  /// compute the dot product between two vectors
  Scalar dot(const EuclideanVector &b) const {
    return x*b.x + y*b.y + z*b.z;
  }
  /// compute the norm (lenth)
  Scalar norm() const {
    return sqrt(x*x+y*y+z*z);
  }
  /// compute the length
  Scalar length() const {
    return norm();
  }
  /// compute the cross product
  EuclideanVector cross(const EuclideanVector &b) const {
    const EuclideanVector &a=*this;
    EuclideanVector c;
    c.x = a.y*b.z - a.z*b.y;
    c.y = a.z*b.x - a.x*b.z;
    c.z = a.x*b.y - a.y*b.x; 
    return c;
  }
  /// compute the scalar triple product
  Scalar triple(const EuclideanVector &b, const EuclideanVector &c) const {
    const EuclideanVector &a=*this;
    return a.dot(b.cross(c));
  }

};

} // namespace DGM

#endif  // DGM_COORD_HPP
