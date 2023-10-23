/** \file BoundingBox.hpp
    \brief Define a bounding box
    \author K. Noel Belcourt
*/

#ifndef DGM_BoundingBox_hpp
#define DGM_BoundingBox_hpp

// standard libraries
#include <limits>
#include <ostream>

// DGM libraries
#include "Box.hpp"
#include "Cartesian.hpp"
#include "Point.hpp"

namespace DGM {

// computes box inside which all added boxes reside
// i.e. the box the bounds all added boxes
template <typename T, typename Space>
struct bounding_box;

// 2d
template <typename T>
struct bounding_box<T,XY> : public box<T,XY> {
  typedef T            T_type;
  typedef XY           space_type;
  typedef point<T,XY>  Point;
  typedef box<T,XY>    base;
  using base::xmin;
  using base::xmax;
  using base::ymin;
  using base::ymax;

  bounding_box() :
    base(std::numeric_limits<T>::max()
      , -std::numeric_limits<T>::max()
      ,  std::numeric_limits<T>::max()
      , -std::numeric_limits<T>::max())
  {}

  bounding_box(T xi, T xm, T yi, T ym)
    : base(xi, xm, yi, ym) {}

  Point lower_left() const {
    return Point(xmin(), ymin());
  }

  Point upper_right() const {
    return Point(xmax(), ymax());
  }

  template <typename Iter>
  void update(Iter min_it, Iter min_end, Iter max_it) {
    using std::distance;
    assert(2 == distance(min_it, min_end));
    xmin(*min_it);
    xmax(*max_it);
    ymin(*++min_it);
    ymax(*++max_it);
  }

  T lower_bound(axis a) const {
    if (a == X_axis)
      return xmin();
    else {
      assert(a == Y_axis);
      return ymin();
    }
  }

  T range(axis a) const {
    if (a == X_axis)
      return xmax() - xmin();
    else if (a == Y_axis) {
      assert(a == Y_axis);
      return ymax() - ymin();
    }
  }

  void add(const base& b) {
    if (b.xmin() < xmin()) xmin(b.xmin());
    if (xmax() < b.xmax()) xmax(b.xmax());
    if (b.ymin() < ymin()) ymin(b.ymin());
    if (ymax() < b.ymax()) ymax(b.ymax());
  }

  void add(const point<T,XY>& p) {
    T xp = x(p);
    T yp = y(p);
    if (xp < xmin()) xmin(xp);
    if (xmax() < xp) xmax(xp);
    if (yp < ymin()) ymin(yp);
    if (ymax() < yp) ymax(yp);
  }

  axis most_elongated() const {
    T xdiff = xmax() - xmin();
    T ydiff = ymax() - ymin();
    axis a = Y_axis;
    if (ydiff <= xdiff) a = X_axis;
    return a;
  }

  void reset() {
    xmin(std::numeric_limits<T>::max());
    xmax(-std::numeric_limits<T>::max());
    ymin(std::numeric_limits<T>::max());
    ymax(-std::numeric_limits<T>::max());
  }
};

// 2d
template <typename T>
axis most_elongated(const bounding_box<T,XY>& bb) {
  return bb.most_elongated();
}

template <typename T>
point<T,XY> lower_left(const bounding_box<T,XY>& bb) {
  return bb.lower_left();
}

template <typename T>
point<T,XY> upper_right(const bounding_box<T,XY>& bb) {
  return bb.upper_right();
}

template <typename T>
T lower_bound(const bounding_box<T,XY>& bb, axis a) {
  return bb.lower_bound(a);
}

template <typename T>
T range(const bounding_box<T,XY>& bb, axis a) {
  return bb.range(a);
}

template <typename T>
void add(const box<T,XY>& b, bounding_box<T,XY>& bb) {
  bb.add(b);
}
template <typename T>
void add(const point<T,XY>& p, bounding_box<T,XY>& bb) {
  bb.add(p);
}

template <typename T>
std::ostream& operator<<(std::ostream& ofp, const bounding_box<T,XY>& bb) {
  const box<T,XY>& b = bb;
  ofp << b;
  return ofp;
}

// 3d
template <typename T>
struct bounding_box<T,XYZ> : public box<T,XYZ> {
  typedef T             T_type;
  typedef XYZ           space_type;
  typedef point<T,XYZ>  Point;
  typedef box<T,XYZ>    base;
  using base::xmin;
  using base::xmax;
  using base::ymin;
  using base::ymax;
  using base::zmin;
  using base::zmax;

  bounding_box() :
    base(std::numeric_limits<T>::max()
      , -std::numeric_limits<T>::max()
      ,  std::numeric_limits<T>::max()
      , -std::numeric_limits<T>::max()
      ,  std::numeric_limits<T>::max()
      , -std::numeric_limits<T>::max())
  {}

  bounding_box(const bounding_box& b) : base(b) {
  }

private:
  bounding_box& operator=(const bounding_box&);

public:
  bounding_box(T xi, T xm, T yi, T ym, T zi, T zm)
    : base(xi, xm, yi, ym, zi, zm) {}

  Point lower_left() const {
    return Point(xmin(), ymin(), zmin());
  }

  Point upper_right() const {
    return Point(xmax(), ymax(), zmax());
  }

  template <typename Iter>
  void update(Iter min_it, Iter min_end, Iter max_it) {
    using std::distance;
    assert(3 == distance(min_it, min_end));
    // mins
    xmin(*min_it);
    ymin(*++min_it);
    zmin(*++min_it);
    // maxs
    xmax(*max_it);
    ymax(*++max_it);
    zmax(*++max_it);
  }

  void reset() {
    xmin(std::numeric_limits<T>::max());
    xmax(-std::numeric_limits<T>::max());
    ymin(std::numeric_limits<T>::max());
    ymax(-std::numeric_limits<T>::max());
    zmin(std::numeric_limits<T>::max());
    zmax(-std::numeric_limits<T>::max());
  }

  void add(const base& b) {
    if (b.xmin() < xmin()) xmin(b.xmin());
    if (xmax() < b.xmax()) xmax(b.xmax());
    if (b.ymin() < ymin()) ymin(b.ymin());
    if (ymax() < b.ymax()) ymax(b.ymax());
    if (b.zmin() < zmin()) zmin(b.zmin());
    if (zmax() < b.zmax()) zmax(b.zmax());
  }

  void add(const point<T,XYZ>& p) {
    T xp = x(p);
    T yp = y(p);
    T zp = z(p);
    if (xp < xmin()) xmin(xp);
    if (xmax() < xp) xmax(xp);
    if (yp < ymin()) ymin(yp);
    if (ymax() < yp) ymax(yp);
    if (zp < zmin()) zmin(zp);
    if (zmax() < zp) zmax(zp);
  }

  axis most_elongated() const {
    T xdiff = xmax() - xmin();
    T ydiff = ymax() - ymin();
    T zdiff = zmax() - zmin();
    axis a = Z_axis;
    if (ydiff <= xdiff && zdiff <= xdiff)
      a = X_axis;
    else if (xdiff <= ydiff && zdiff <= ydiff)
      a = Y_axis;
    return a;
  }

  T range(axis a) const {
    if (a == X_axis)
      return xmax() - xmin();
    else if (a == Y_axis)
      return ymax() - ymin();
    else {
      assert(a == Z_axis);
      return zmax() - zmin();
    }
  }

  T lower_bound(axis a) const {
    if (a == X_axis)
      return xmin();
    else if (a == Y_axis)
      return ymin();
    else {
      assert(a == Z_axis);
      return zmin();
    }
  }

  T upper_bound(axis a) const {
    if (a == X_axis)
      return xmax();
    else if (a == Y_axis)
      return ymax();
    else {
      assert(a == Z_axis);
      return zmax();
    }
  }
};

// 3d
template <typename T>
void add(const box<T,XYZ>& b, bounding_box<T,XYZ>& bb) {
  bb.add(b);
}
template <typename T>
void add(const point<T,XYZ>& p, bounding_box<T,XYZ>& bb) {
  bb.add(p);
}

template <typename T>
void clear(bounding_box<T,XYZ>& bb) {
  bb.reset();
}

template <typename T>
point<T,XYZ> lower_left(const bounding_box<T,XYZ>& bb) {
  return bb.lower_left();
}

template <typename T>
point<T,XYZ> upper_right(const bounding_box<T,XYZ>& bb) {
  return bb.upper_right();
}

template <typename T>
axis most_elongated(const bounding_box<T,XYZ>& bb) {
  return bb.most_elongated();
}

template <typename T>
T range(const bounding_box<T,XYZ>& bb, axis a) {
  return bb.range(a);
}

template <typename T>
T lower_bound(const bounding_box<T,XYZ>& bb, axis a) {
  return bb.lower_bound(a);
}

template <typename T>
T upper_bound(const bounding_box<T,XYZ>& bb, axis a) {
  return bb.upper_bound(a);
}

template <typename T>
std::ostream& operator<<(std::ostream& ofp, const bounding_box<T,XYZ>& bb) {
  const box<T,XYZ>& b = bb;
  ofp << b;
  return ofp;
}

// Space agnostic
template <typename T, typename Space, typename Iter>
void update(bounding_box<T,Space>& bb, Iter min_it, Iter min_end
  , Iter max_it) {
  bb.update(min_it, min_end, max_it);
}

#if 0
template <typename PointIter, typename T, typename Space>
void global_bounding_box(PointIter p_it, PointIter p_end
  , bounding_box<T,Space>& bb, boost::mpi::communicator world)
{
  namespace mpi = boost::mpi;
  // bb is processor local bounding box, add each point
  // on this processor to this bounding box
  for (; p_it != p_end; ++p_it)
    add(*p_it, bb);
  // get number of space dimensions
  unsigned int n = n_dimensions(Space());
  T mins[n], maxs[n], global_mins[n], global_maxs[n];
  // local bounding box minimums and maximums into arrays
  minimums(bb, mins, mins+n);
  maximums(bb, maxs, maxs+n);
  // reduce to get globally consistent bounding box minimums and maximums
  mpi::all_reduce(world, mins, n, global_mins, mpi::minimum<T>());
  mpi::all_reduce(world, maxs, n, global_maxs, mpi::maximum<T>());
  // update bounding box with parallel consistent information
  update(bb, global_mins, global_mins+n, global_maxs);
}
#endif

typedef bounding_box<Scalar,XYZ> BoundingBox;

}  // namespace DGM

#endif
