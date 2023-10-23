/** \file Box.hpp
    \brief Define a box in space
    \author K. Noel Belcourt
*/

#ifndef DGM_Box_hpp
#define DGM_Box_hpp

// standard libraries
#include <algorithm>
#include <ostream>
#include <sstream>
#include <string>

// DGM libraries
#include "Cartesian.hpp"
#include "Point.hpp"

namespace DGM {

// forward declaration
template <typename Scalar, typename Space>
struct box;

// 2d
template <typename Scalar>
struct box<Scalar, XY> {
  typedef Scalar*       iterator;
  typedef const Scalar* const_iterator;

  box() {
    using std::fill;
    fill(begin(), end(), 0.0);
  }

private:
  box& operator=(const box& b) {
    using std::copy;
    copy(b.begin(), b.end(), begin());
    return *this;
  }

  box(const box& b) {
    using std::copy;
    copy(b.begin(), b.end(), begin());
  }

public:
  box(const Scalar* source) {
    using std::copy;
    // iterator to 4 Scalars, assumed ordering so error prone
    copy(source, source+4, begin());
  }

  box(Scalar xi, Scalar xm, Scalar yi, Scalar ym) {
    xmin(xi);
    xmax(xm);
    ymin(yi);
    ymax(ym);
  }

  iterator begin() { return &data[0]; }
  iterator end() { return begin()+4; }

  const_iterator begin() const { return &data[0]; }
  const_iterator end() const { return begin()+4; }

  void xmin(Scalar x) { data[0] = x; }
  void xmax(Scalar x) { data[1] = x; }
  void ymin(Scalar y) { data[2] = y; }
  void ymax(Scalar y) { data[3] = y; }

  Scalar xmin() const { return data[0]; }
  Scalar xmax() const { return data[1]; }
  Scalar ymin() const { return data[2]; }
  Scalar ymax() const { return data[3]; }

private:
  Scalar data[4];
};

template <typename Scalar, typename Space, typename Iter>
void minimums(const box<Scalar,Space>&, Iter, Iter);

template <typename Scalar, typename Space, typename Iter>
void maximums(const box<Scalar,Space>&, Iter, Iter);

// box minimums along each axis
template <typename Scalar, typename Iter>
void minimums(const box<Scalar,XY>& b, Iter it, Iter end) {
  using std::distance;
  using std::iterator_traits;
  typedef typename iterator_traits<Iter>::difference_type difference_type;
  difference_type n = distance(it, end);
  assert(n == n_dimensions(XY()));
  *it = b.xmin();
  *++it = b.ymin();
}

// box maximums along each axis
template <typename Scalar, typename Iter>
void maximums(const box<Scalar,XY>& b, Iter it, Iter end) {
  using std::distance;
  using std::iterator_traits;
  typedef typename iterator_traits<Iter>::difference_type difference_type;
  difference_type n = distance(it, end);
  assert(n == n_dimensions(XY()));
  *it = b.xmax();
  *++it = b.ymax();
}

template <typename Scalar>
std::ostream& operator<<(std::ostream& ofp, const box<Scalar,XY> &b) {
  ofp << "x[" << b.xmin() << "," << b.xmax() << "], ";
  ofp << "y[" << b.ymin() << "," << b.ymax() << "]";
  return ofp;
}

// 3d
template <typename Scalar>
struct box<Scalar, XYZ> {
  typedef Scalar*       iterator;
  typedef const Scalar* const_iterator;

  box() {
    using std::fill;
    fill(begin(), end(), 0.0);
  }

  box(const box& b) {
    using std::copy;
    copy(b.begin(), b.end(), begin());
  }

private:
  box& operator=(const box&);

public:
  box(const Scalar* source) {
    using std::copy;
    // iterator to 6 Scalars, assumed ordering so error prone
    copy(source, source+6, begin());
  }

  box(Scalar xi, Scalar xm, Scalar yi, Scalar ym, Scalar zi, Scalar zm) {
    xmin(xi);
    xmax(xm);
    ymin(yi);
    ymax(ym);
    zmin(zi);
    zmax(zm);
  }

  template <typename Point>
  bool contains(const Point& p) const {
    Scalar a = x(p);
    if (xmin() <= a && a <= xmax()) {
      Scalar b = y(p);
      if (ymin() <= b && b <= ymax()) {
        Scalar c = z(p);
        return zmin() <= c && c <= zmax();
      }
    }
    return false;
  }

  iterator begin() { return &data[0]; }
  iterator end() { return begin()+6; }

  const_iterator begin() const { return &data[0]; }
  const_iterator end() const { return begin()+6; }

  void xmin(Scalar x) { data[0] = x; }
  void xmax(Scalar x) { data[1] = x; }
  void ymin(Scalar y) { data[2] = y; }
  void ymax(Scalar y) { data[3] = y; }
  void zmin(Scalar z) { data[4] = z; }
  void zmax(Scalar z) { data[5] = z; }

  Scalar xmin() const { return data[0]; }
  Scalar xmax() const { return data[1]; }
  Scalar ymin() const { return data[2]; }
  Scalar ymax() const { return data[3]; }
  Scalar zmin() const { return data[4]; }
  Scalar zmax() const { return data[5]; }

private:
  Scalar data[6];
};

template <typename Scalar, typename S>
std::string name(const box<Scalar,S>&) {
  return "box";
}

// 3d
template <typename Scalar>
point<Scalar,XYZ> compute_centroid(const box<Scalar,XYZ>& b) {
  point<Scalar,XYZ> p((b.xmax()+b.xmin())/2,(b.ymax()+b.ymin())/2, (b.zmax()+b.zmin())/2);
  return p;
}

template <typename Scalar, typename Iter>
void minimums(const box<Scalar,XYZ>& b, Iter it, Iter end) {
  using std::distance;
  using std::iterator_traits;
  typedef typename iterator_traits<Iter>::difference_type difference_type;
  difference_type n = distance(it, end);
  assert(n == n_dimensions(XYZ()));
  *it = b.xmin();
  *++it = b.ymin();
  *++it = b.zmin();
}

template <typename Scalar, typename Iter>
void maximums(const box<Scalar,XYZ>& b, Iter it, Iter end) {
  using std::distance;
  using std::iterator_traits;
  typedef typename iterator_traits<Iter>::difference_type difference_type;
  difference_type n = distance(it, end);
  assert(n == n_dimensions(XYZ()));
  *it = b.xmax();
  *++it = b.ymax();
  *++it = b.zmax();
}

template <typename S>
box<S,XYZ> compute_bounding_box(const box<S,XYZ>& b) {
  return b;
}

template <typename Scalar>
std::ostream& operator<<(std::ostream& ofp, const box<Scalar,XYZ> &b) {
  ofp << "x[" << b.xmin() << "," << b.xmax() << "], ";
  ofp << "y[" << b.ymin() << "," << b.ymax() << "], ";
  ofp << "z[" << b.zmin() << "," << b.zmax() << "]";
  return ofp;
}

template <typename Scalar>
std::string as_string(const box<Scalar,XYZ> &b) {
  using std::ostringstream;
  ostringstream ss;
  ss << "x[" << b.xmin() << "," << b.xmax() << "], ";
  ss << "y[" << b.ymin() << "," << b.ymax() << "], ";
  ss << "z[" << b.zmin() << "," << b.zmax() << "]";
  return ss.str();
}

template <typename Point, typename Scalar>
bool is_point_in_geometry(const Point& p, const box<Scalar,XYZ>& b) {
  return b.contains(p);
}

typedef struct box<Scalar, XYZ> Box;

}  // namespace DGM

#endif
