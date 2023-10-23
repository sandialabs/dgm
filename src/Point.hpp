#ifndef DGM_POINT_HPP
#define DGM_POINT_HPP

/** \file Point.hpp
    \brief Data-structure for holding spatial coordinates
    \author S. Scott Collis
    \author K. Noel Belcourt
*/

// Boost includes
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include "boost/numeric/conversion/cast.hpp"

// System includes
#include <cassert>
#include <cmath>
#include <iostream>
#include <iterator>
#include <vector>
#ifdef DGM_USE_GENERAL_GHOSTING
#include <boost/serialization/serialization.hpp>
#endif

// DGM includes
#include "Cartesian.hpp"
#include "Comm.hpp"
#include "Types.hpp"

namespace DGM {

/// Provides a class to hold a point in space
/** Parameterized on the Scalar type and the coordinate space
    Forward declaration */
template <typename Scalar, typename Space>
struct point;

/// 1d point
template <typename Scalar>
struct point<Scalar, X> {
  typedef Scalar  scalar_type;
  typedef X  space_type;
  point() : x(0) {}
  point(scalar_type a) : x(a) {}
  scalar_type x;
};

/// 2d point
template <typename Scalar>
struct point<Scalar, XY> {
  typedef Scalar   scalar_type;
  typedef XY  space_type;
  point() : x(0), y(0) {}
  point(scalar_type a, scalar_type b) : x(a), y(b) {}
  point(const point& p) : x(p.x), y(p.y) {}
  scalar_type x, y;
};

/// 3d point
template <typename Scalar>
struct point<Scalar, XYZ> {
  typedef Scalar    scalar_type;
  typedef XYZ  space_type;

 public:
  scalar_type x;  ///< x-coordinate
  scalar_type y;  ///< y-coordinate
  scalar_type z;  ///< z-coordinate

  /// Default constructor
  explicit point(const Scalar X=0, const Scalar Y=0, const Scalar Z=0) :
    x(X), y(Y), z(Z) {}

  /// Copy constructor
  point(const point &rhs) {
    x = rhs.x; y = rhs.y; z = rhs.z;
  }

  void operator()(Scalar i, Scalar j) {
    x = i;
    y = j;
  }

  void operator()(Scalar i, Scalar j, Scalar k) {
    x = i;
    y = j;
    z = k;
  }

  void cross(const point& r, const point& s) {
    x = r.y * s.z - s.y * r.z;
    y = r.x * s.z - s.x * r.z;
    z = r.x * s.y - s.x * r.y;
  }

#ifdef DGM_USE_GENERAL_GHOSTING
 private:
  friend class boost::serialization::access;

  template<class Archive>
  void serialize(Archive &ar, const unsigned int version) {
    ar & x & y & z;
  }
 public:
#endif

  /// Set two points equal
  point & operator=(const point &rhs) {
    if (this == &rhs) return *this;   // self-test
    x = rhs.x; y = rhs.y; z = rhs.z;
    return *this;
  }

  /// Set the coordinates of a point to a single value
  point & operator=(const Scalar s) {
    x=s; y=s; z=s;
    return *this;
  }

  /// Return the x, y, or z coordinates for index 1, 2, or 3 respectively
  Scalar operator[](const Ordinal i) const {
    switch(i) {
    case 0:
      return x;
    case 1:
      return y;
    case 2:
      return z;
    default:
      DGM::Comm::World->cerr()
          << "point::operator[] -- Index out of range: "<< i << endl;
      DGM::Comm::World->exit(DGM::FAILURE);
      break;
    }
    return 0;
  }

  /// Increment by another point
  const point & operator+=(const point &rhs) {
    x += rhs.x; y += rhs.y; z += rhs.z;
    return *this;
  }
  /// Decrement by another point
  point & operator-=(const point &rhs) {
    x -= rhs.x; y -= rhs.y; z -= rhs.z;
    return *this;
  }

  /// Increment by a constant Scalar
  point & operator+=(const Scalar rhs) {
    x += rhs; y += rhs; z += rhs;
    return *this;
  }

  /// Multiply by a constant Scalar
  point & operator*=(const Scalar rhs) {
    x *= rhs; y *= rhs; z *= rhs;
    return *this;
  }

  /// Divide by a constant Scalar
  point & operator/=(const Scalar rhs) {
    x /= rhs; y /= rhs; z /= rhs;
    return *this;
  }

  /// Inner product with another point
  Scalar operator*(const point &p2) const {
  const Scalar d = (p2.x*x) + (p2.y*y) + (p2.z*z);
    return d;
  }

  /// Multiply by Scalar (postfix)
  point operator*(const Scalar rhs) const {
    return point(*this) *= rhs;
  }

  /// Divide by Scalar
  point operator/(const Scalar rhs) const {
    return point(*this) /= rhs;
  }

  /// Add two point
  const point operator+(const point &rhs) const {
    return point(*this) += rhs;
  }

  /// Increment by one
  const point & operator++() {
    x += 1; y += 1; z += 1;
    return *this;
  }

  /// Increment by one (postfix)
  const point operator++(int) { // postfix form
    point oldValue = *this;
    ++(*this);
    return oldValue;
  }

  /// return the distance squared between this point and another
  Scalar distance_sq(const point &p2) const {
    const point &p1(*this);
    const Scalar d = std::pow(p2.x - p1.x, 2)
                   + std::pow(p2.y - p1.y, 2)
                   + std::pow(p2.z - p1.z, 2);
    return d;
  }

  /// return the distance between this point and another
  Scalar distance(const point &p2) const {
    return sqrt(distance_sq(p2));
  }

  /// Scalarest equality
  bool operator==(const point &p) const {
    return x==p.x && y==p.y && z==p.z;
  }
};

/// Output a point to a output stream
template <typename Scalar>
inline std::ostream &operator<<(std::ostream &os, const point<Scalar, XYZ> &p) {
  // cout << "point& operator<<()" << endl;
  os << "(" << p.x << ", " << p.y << ", " << p.z << ")";
  return os;
}

/// Input a point from an input stream
template <typename Scalar>
inline std::istream &operator>>(std::istream &is, point<Scalar, XYZ> &p) {
  // cout << "point& operator>>()" << endl;
  is >> p.x >> p.y >> p.z;
  return is;
}

/// Multiply by Scalar (prefix)
template <typename Scalar>
inline point<Scalar, XYZ> operator*(const Scalar lhs, 
                                    const point<Scalar, XYZ> &p) {
  return point<Scalar, XYZ>(p) *= lhs;
}

template <typename Scalar>
inline Scalar dot(const point<Scalar, XYZ> &p1, const point<Scalar, XYZ> &p2) {
  const Scalar d = (p2.x*p1.x) + (p2.y*p1.y) + (p2.z*p1.z);
  return d;
}

template <typename Scalar>
inline Scalar distance_sq(const point<Scalar, XYZ> &p1, 
                          const point<Scalar, XYZ> &p2) {
  const Scalar d = std::pow(p2.x - p1.x, 2)
                 + std::pow(p2.y - p1.y, 2)
                 + std::pow(p2.z - p1.z, 2);
  return d;
}

template <typename Scalar>
inline Scalar distance(const point<Scalar, XYZ> &p1, 
                       const point<Scalar, XYZ> &p2) {
  return std::sqrt(distance_sq(p1,p2));
}

/// return the midpoint between two points
template <typename Scalar>
inline const point<Scalar, XYZ> midpoint( const point<Scalar, XYZ> &p1,
                                          const point<Scalar, XYZ> &p2 ) {
  return (p1+p2)/2.0;
}

// 1d
template <typename Scalar>
Scalar x(const point<Scalar,X>& p) {
  return p.x;
}

// 2d
template <typename Scalar>
Scalar x(const point<Scalar,XY>& p) {
  return p.x;
}

template <typename Scalar>
Scalar y(const point<Scalar,XY>& p) {
  return p.y;
}

template <typename Scalar>
bool operator<(const point<Scalar,XY>& p, const point<Scalar,XY>& q) {
  return x(p) < x(q) || ( !(x(q) < x(p)) && y(p) < y(q) );
}

template <typename Scalar>
Scalar value(const point<Scalar,XY>& p, const axis a) {
  if (a == X_axis)
    return x(p);
  else {
    assert(a == Y_axis);
    return y(p);
  }
}

template <typename Scalar>
void add(const point<Scalar,XY>& p, point<Scalar,XY>& q) {
  q.x += p.x;
  q.y += p.y;
}

template <typename Divisor, typename Scalar>
void divide(const Divisor n, point<Scalar,XY>& p) {
  p.x /= n;
  p.y /= n;
}

// 3d
template <typename Scalar>
Scalar x(const point<Scalar,XYZ>& p) {
  return p.x;
}

template <typename Scalar>
Scalar y(const point<Scalar,XYZ>& p) {
  return p.y;
}

template <typename Scalar>
Scalar z(const point<Scalar,XYZ>& p) {
  return p.z;
}

// hack for getting value of Scalar
template <typename Scalar>
Scalar value(const Scalar s, const axis) {
  return s;
}

template <typename Scalar>
Scalar value(const point<Scalar,XYZ>& p, const axis a) {
  if (a == X_axis)
    return x(p);
  else if (a == Y_axis)
    return y(p);
  else {
    assert(a == Z_axis);
    return z(p);
  }
}

template <typename Scalar>
void update(point<Scalar, XYZ>& p, Scalar v, axis a) {
  if (a == X_axis)
    p.x = v;
  else if (a == Y_axis)
    p.y = v;
  else {
    assert(a == Z_axis);
    p.z = v;
  }
}

template <typename Scalar>
void add(const point<Scalar,XYZ>& p, point<Scalar,XYZ>& q) {
  q.x += p.x;
  q.y += p.y;
  q.z += p.z;
}

template <typename Divisor, typename Scalar>
void divide(const Divisor n, point<Scalar,XYZ>& p) {
  p.x /= n;
  p.y /= n;
  p.z /= n;
}

// Substract two points
template <typename Scalar>
inline
const point<Scalar, XYZ> operator-(const point<Scalar, XYZ> &p, 
                                   const point<Scalar, XYZ> &q) {
  return point<Scalar, XYZ>(p.x - q.x, p.y - q.y, p.z - q.z);
}

template <typename Scalar>
inline bool operator<(const point<Scalar, XYZ>& p, 
                      const point<Scalar, XYZ>& q) {
  return x(p) < x(q)
    || ( !(x(q) < x(p)) && y(p) < y(q) )
    || ( !(x(q) < x(p)) && !(y(q) < y(p)) && z(p) < z(q));
}

template <typename Scalar>
inline bool operator<=(const point<Scalar, XYZ>& p, 
                       const point<Scalar, XYZ>& q) {
  return x(p) <= x(q)
    || ( !(x(q) <= x(p)) && y(p) <= y(q) )
    || ( !(x(q) <= x(p)) && !(y(q) <= y(p)) && z(p) <= z(q));
}

template <typename Scalar>
inline bool operator==(const point<Scalar, XYZ>& p, 
                       const point<Scalar, XYZ>& q) {
  return x(p) == x(q) && y(p) == y(q) && z(p) == z(q);
}

// 3d
template <typename PointIter>
typename std::iterator_traits<PointIter>::value_type
average(const PointIter p_it, const PointIter p_end) {
  using std::distance;
  using std::iterator_traits;
  typedef typename iterator_traits<PointIter>::difference_type difference_type;
  typedef typename iterator_traits<PointIter>::value_type Point;
  Point p;
  difference_type n = distance(p_it, p_end);
  for (; p_it != p_end; ++p_it) add(*p_it, p);
  if (0 < n) divide(n, p);
  return p;
}

// predicate returns true if iterate is less than p
template <typename Scalar>
struct less_than_point {
  axis a;
  Scalar q;
  less_than_point(axis ax, Scalar s) : a(ax), q(s) {}

  template <typename Space>
  bool operator()(const point<Scalar,Space>& p) {
    return value(p,a) < q;
  }
};

// predicate returns true if iterate is less equal than p
template <typename Scalar>
struct less_equal_than_point {
  axis a;
  Scalar q;
  less_equal_than_point(axis ax, Scalar s) : a(ax), q(s) {}

  template <typename Space>
  bool operator()(const point<Scalar,Space>& p) {
    return value(p,a) <= q;
  }
};

struct strict_weak_ordering {
  axis a;
  strict_weak_ordering(axis ax) : a(ax) {}

  template <typename Scalar, typename Space>
  bool operator()(const point<Scalar,Space>& p, const point<Scalar,Space>& q) {
    return value(p,a) < value(q,a);
  }
};

} // namespace DGM

// Serialization for Boost::MPI
namespace boost {
  namespace serialization {

    // unimplemented to force linker error
    template<class Archive, typename Scalar, typename Space>
    void serialize(Archive& ar, DGM::point<Scalar, Space>& p, 
                   const unsigned int);

    template<class Archive, typename Scalar>
    void serialize(Archive& ar, DGM::point<Scalar, DGM::XY>& p, 
         const unsigned int) {
      ar & p.x & p.y;
    }

    template<class Archive, typename Scalar>
    void serialize(Archive& ar, DGM::point<Scalar, DGM::XYZ>& p, 
                   const unsigned int) {
      ar & p.x & p.y & p.z;
    }
  }
}

template <typename Point>
struct point_traits {
  typedef typename Point::scalar_type  scalar_type;
  typedef typename Point::space_type   space_type;
};

namespace DGM {
  // typedef for use by all DGM and derived codes.
  typedef point<Scalar, XYZ> Point;
}

#endif  // DGM_POINT_HPP
