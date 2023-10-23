//
//  point.h
//  BoxTreeMesh
//
//  Created by Mitchell, Scott A on 1/5/16.
//  Copyright (c) 2016 Sandia National Labs. All rights reserved.
//

#ifndef __BoxTreeMesh__point__
#define __BoxTreeMesh__point__

#include <stdio.h>
#include <iostream>
#include <math.h>
#include <assert.h>
#include <vector>

// Multiply indexed arrays
// Suitable for large multidimensional arrays, when memory is important.
// When memory is unimportant, use std::vector
// For small arrays, having the separate single-index array is unwanted memory.
//
// From: 1d array as 2d array
// http://stackoverflow.com/questions/29375797/copy-2d-array-using-memcpy/29375830#29375830
// See also BoxTree.h implementation of children 3d arrays. That could be templatized to support any type of 3d array
template <class ElementType> class ArrayFactory
{
public:
  // usage:
  // double **da = ArrayFactory<double>::new_array2(10,16);
  // da[4][3] = 3.4;
  // ArrayFactory<double>::delete_array2(da);

  ArrayFactory() {}; // does nothing, lightweight

  // could make this singleton class, rather than static functions...
  // could templatize "double" to class T if needed
  static ElementType **new_array2( const size_t x, const size_t y)
  {
    ElementType** da;
    da = new ElementType*[x];
    // contiguous block
    da[0] = new ElementType[ x * y ];
    // make rows of da point to the right spot in the contiguous block
    for (size_t i = 1; i < x; ++i)
      da[i] = da[i-1] + y;
    return da;
  }

  static void delete_array2(ElementType ** &array)
  {
    if (array)
    {
      delete[] array[0];
      delete[] array;
      array = 0;
    }
  }
};


// todo: pool memory manage Point

class Point
{
public:
  double x, y, z;
  Point() : x(0.), y(0.), z(0.) {}
  Point(double px, double py, double pz) : x(px), y(py), z(pz) {}
  Point(const Point &p) : x(p.x), y(p.y), z(p.z) {}
  
  void multiply( double dx, double dy, double dz ); // component-wise multiplication
  void multiply( double d ); // multiply all components by d
  void add( Point p2 );
  void subtract( Point p2 );
  
  double length2() const { return       dot(*this)  ; }
  double length()  const { return sqrt( dot(*this) ); }
  
  // vector +/-
  Point& operator+=(const Point& o) { x+= o.x; y += o.y; z += o.z; return *this; }
  friend Point operator+(Point lhs, const Point& rhs) { lhs += rhs; return lhs; }
  Point& operator-=(const Point& o) { x-= o.x; y -= o.y; z -= o.z; return *this; }
  friend Point operator-(Point lhs, const Point& rhs) { lhs -= rhs; return lhs; }

  // scalar */+/-
  Point& operator*=(double dd) { x *= dd; y *= dd; z *= dd; return *this; }
  friend Point operator*(Point lhs, const double rhs) { lhs *= rhs; return lhs; }
  Point& operator+=(double dd) { x += dd; y += dd; z += dd; return *this; }
  friend Point operator+(Point lhs, const double rhs) { lhs += rhs; return lhs; }
  Point& operator-=(double dd) { x -= dd; y -= dd; z -= dd; return *this; }
  friend Point operator-(Point lhs, const double rhs) { lhs -= rhs; return lhs; }

  // component-wise product
  Point& operator*=(const Point & o) { x *= o.x; y *= o.y; z *= o.z; return *this; }
  friend Point operator*(Point lhs, const Point& rhs) { lhs *= rhs; return lhs; }

  bool operator==(const Point &other) const 
  {
    return (x == other.x && y == other.y && z == other.z);
  }
  
  // dot product
  double dot(const Point& o) const { return x * o.x + y * o.y + z * o.z; }
  // operator * is defined as cross product, not dot product!
  
  // cross product of this and o
  Point cross(const Point &o) const;
  
  void normalize();

  // operators return true iff true for all components
  friend bool operator<=(Point lhs, const Point& rhs) { return (lhs.x <= rhs.x && lhs.y <= rhs.y && lhs.z <= rhs.z);}
  friend bool operator>=(Point lhs, const Point& rhs) { return (lhs.x >= rhs.x && lhs.y >= rhs.y && lhs.z >= rhs.z);}
  friend bool operator<(Point lhs, const Point& rhs) { return (lhs.x < rhs.x && lhs.y < rhs.y && lhs.z < rhs.z);}
  friend bool operator>(Point lhs, const Point& rhs) { return (lhs.x > rhs.x && lhs.y > rhs.y && lhs.z > rhs.z);}

  // is the squared distance between this and p less than tol2?
  bool is_close( Point p, double tol2 ) const;
  
  // fabs( cos(this,p) ) > tol?
  // is the cosine of the angle between this and p as vectors are extreme.
  bool is_colinear(const Point& p, const double tol = 0.999) const;

  // debug
  void print() const;
  
  // return the cosine of the dihedral angle between planes p0,p1,p2 and plane p0,p1,p3
  static double cos_dihedral( const Point &p0, const Point &p1, const Point &p2, const Point &p3 );
};

class Boxmath
{
public:
  static bool intervals_overlap(double i0, double i1, double j0, double j1)
  {
    assert( i0 <= i1 );
    assert( j0 <= j1 );
    return ( i0 <= j1 ) && ( i1 >= j0 );
  }
};

class TriangleMath
{
public:
  // return p_bary, the barycentric coordinates of p for the triangle t0,1,2
  // this is after projecting all points to the z=0 plane
  static
  void barycentric_z(const Point &t0, const Point &t1, const Point &t2, const Point &p, Point &p_bary);
  // z coordinate of point p with barycentric coordinates p_bary
  static
  double depth_z_from_bary(const Point &t0, const Point &t1, const Point &t2, Point &p_bary);

  // crosses = true if the ray from p to z = -infty crosses through the interior of the triangle.
  // degenerate = true if the ray comes within a small fraction of the boundary of the triangle.
  // cases to watch for: the triangle has a degenerate area when projected ...
  //                     does the triangle orientation matter?
  static
  void crosses_from_neg_infinity(const Point &t0, const Point &t1, const Point &t2, const Point &p, bool &crosses, bool &degenerate);
  
  // true if p is close to any of the edges of the triangle t0,t1,t2
  static
  bool close_to_edges_z(const Point &t0, const Point &t1, const Point &t2, const Point &p );

  // true if p is close to the segement ab
  static
  bool close_to_segment( const Point &a, const Point&b, const Point& p, const double rel_tol2, const double abs_tol2);

};

template<typename T>
void uniquify_vec_ptr( std::vector<T*> &v )
{
  std::vector<T*> tunique;
  tunique.reserve(v.size());
  std::sort(v.begin(), v.end());
  T *prior_t = 0;
  for ( size_t i = 0; i < v.size(); ++i )
  {
    T *t = v[i];
    if ( t != prior_t )
    {
      tunique.push_back(t);
      prior_t = t;
    }
  }
  tunique.swap(v);
}

template<typename T>
void uniquify_vec_ref( std::vector<T> &v )
{
  if (v.empty())
    return;
  
  std::vector<T> tunique;
  tunique.reserve(v.size());
  std::sort(v.begin(), v.end());
  T prior_t;
  for ( size_t i = 0; i < v.size(); ++i )
  {
    T &t = v[i];
    if ( t != prior_t ) 
    {
      tunique.push_back(t);
      prior_t = t;
    }
  }
  tunique.swap(v);
}



// =============================================
// Point inline functions
// =============================================
inline
void Point::multiply( double dx, double dy, double dz )
{ x *= dx; y *= dy; z *= dz; }

inline
void Point::multiply( double d )
{ x *= d; y*=d; z*=d; }

inline
void Point::add( Point p )
{ x += p.x; y += p.y; z += p.z; }

inline
void Point::subtract( Point p )
{ x -= p.x; y -= p.y; z -= p.z; }

inline
bool Point::is_close( Point p, double tol2 ) const
{
  p -= *this;
  return p.length2() < tol2;
}

inline
bool Point::is_colinear(const Point& p, const double tol) const
{
  return fabs( dot( p ) ) / (length() * p.length()) > tol;
}


inline
Point Point::cross(const Point &o) const
{
  return Point( y * o.z - z * o.y, z * o.x - x * o.z, x * o.y - y * o.x );
}

inline
void Point::normalize()
{
  const double l = length();
  if ( l > 1.e-10 )
    multiply( 1. / length() );
  else
  {
    x = 0.; y = 0.; z = 0.;
  }
}
#endif /* defined(__BoxTreeMesh__point__) */
