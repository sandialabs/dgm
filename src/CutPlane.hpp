/** \file CutPlane.hpp
    \brief Class to define a cut plane
    \author K. Noel Belcourt
*/

#ifndef DGM_CutPlane_hpp
#define DGM_CutPlane_hpp

// standard libraries
#include <ostream>

// Boost includes
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

// DGM libraries
#include "Cartesian.hpp"
#include "Point.hpp"

namespace DGM {

template <typename scalar>
struct cutting_plane {
  typedef scalar Scalar;
  typedef cutting_plane<Scalar> CuttingPlane;

  cutting_plane() : p(0), rank(0), a(X_axis) {}
  cutting_plane(axis x, Scalar s) : p(s), rank(0), a(x) {}

  void set(axis x, Scalar s) {
    p = s;
    a = x;
  }

  Scalar p;
  int rank;
  axis a;
};

template <typename Point, typename Scalar>
void as_point(Point& p, const cutting_plane<Scalar>& c) {
  update(p, c.p, c.a);
}

template <typename Scalar>
bool operator==(const cutting_plane<Scalar>& c, const cutting_plane<Scalar>& d) {
  return c.a == d.a && c.p == d.p && c.rank == d.rank;
}

template <typename Scalar>
bool operator!=(const cutting_plane<Scalar>& c, const cutting_plane<Scalar>& d) {
  return !(c == d);
}

template <typename Scalar>
bool operator<(const cutting_plane<Scalar>& c, const cutting_plane<Scalar>& d) {
  return c.p < d.p;
}

// 2d
template <typename Scalar>
bool operator<(const DGM::point<Scalar,XY>& p, const cutting_plane<Scalar>& c) {
  // order using cutting plane axis
  return value(p, c.a) < c.p;
}

template <typename Scalar>
bool operator==(const DGM::point<Scalar,XY>& p, const cutting_plane<Scalar>& c) {
  return value(p, c.a) == c.p;
}

template <typename Scalar>
bool operator!=(const DGM::point<Scalar,XY>& p, const cutting_plane<Scalar>& c) {
  return !(p == c);
}

// 3d
template <typename Scalar>
bool operator<(const DGM::point<Scalar,XYZ>& p, const cutting_plane<Scalar>& c) {
  // order using cutting plane axis
  return value(p, c.a) < c.p;
}

template <typename Scalar>
bool operator==(const DGM::point<Scalar,XYZ>& p, const cutting_plane<Scalar>& c) {
  return value(p, c.a) == c.p;
}

template <typename Scalar>
bool operator!=(const DGM::point<Scalar,XYZ>& p, const cutting_plane<Scalar>& c) {
  return !(p == c);
}

template <typename Scalar>
std::ostream& operator<<(std::ostream& ofp, const cutting_plane<Scalar>& c) {
 ofp << "cut plane on " << c.a << " at location " << c.p
     << " owned by rank " << c.rank ;
 return ofp;
}

template <typename Scalar>
struct is_less_than {
  typedef cutting_plane<Scalar> CuttingPlane;

  CuttingPlane cp;
  is_less_than(CuttingPlane c) : cp(c) {}

  // return true if point is less than value
  // along the cut plane axis, false otherwise
  template <typename Space>
  bool operator()(const DGM::point<Scalar,Space>& p) {
    return p < cp;
  }
};

}  // namespace DGM

// Serialization for Boost::MPI
namespace boost {
  namespace serialization {

    template<class Archive, typename Scalar>
    void serialize(Archive& ar, DGM::cutting_plane<Scalar> &v, const unsigned int) {
      ar & v.p & v.rank & v.a;
    }

  }
}

#endif
