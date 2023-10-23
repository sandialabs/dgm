//
//  Surface.h
//  BoxTreeMesh
//
//  Created by Mitchell, Scott A on 3/1/16.
//  Copyright (c) 2016 Sandia National Labs. All rights reserved.
//
// Depth map surface over a grid of rectangles.
// For interpolating the geometry within the rectangle,
// we divide the square into four triangles by the center of the rectangle.
//
// Bilinear interpolation results in quadtratic patches, leading to a host of complications
// that aren't worth it.

#ifndef __BoxTreeMesh__Surface__
#define __BoxTreeMesh__Surface__

#include <assert.h>
#include <math.h>

#include "point.h"
// avoid including BoxTree

class GridIndex
{
public:
  size_t i,j;
  GridIndex(size_t ii = size_t(-1), size_t jj = size_t(-1)) : i(ii), j(jj) {}
};

// shared interface functions, define the xy grid
class Grid
{
public:
  Grid() : x_size(0), y_size(0), x_step(0.), y_step(0.) {};
  virtual ~Grid() {}
  
  // xy coordinates at the four corners and center of the grid cell (xi,xi+1) X (yi,yi+1)
  void grid_xy( size_t xi, size_t yi, double &x0, double &x1, double &y0, double &y1, double &xc, double &yc ) const;
  
  // extent of surface
  double min_x() const { return x_min; }
  double min_y() const { return y_min; }
  double max_x() const { return xi2x( x_size-1 ); }
  double max_y() const { return yi2y( y_size-1 ); }
  
  // spacing in x and y directions
  double grid_x() const {return x_step;}
  double grid_y() const {return y_step;}
  
  // return true if the two surfaces have the same grid
  bool same_grid( const Grid *s ) const;
  // copy grid from s to this
  void copy_grid( const Grid *s );
  
  // number of gridlines in x and y directions
  size_t grid_x_size() const {return x_size;}
  size_t grid_y_size() const {return y_size;}
  
  // convert between index and position
  size_t x2i( double x ) const; // floor i: x is between i and i+1, where i and i+1 are valid
  size_t y2i( double y ) const; // floor i: y is between i and i+1
  size_t x2i( double x, double &xifrac ) const; // x = x2i*x_step + xifrac
  size_t y2i( double x, double &xifrac ) const; // y = y2i*y_step + yifrac
  
  size_t x2xi( double x ) const; // rounds
  size_t y2yi( double y ) const; // rounds
  double xi2x( size_t xi ) const;
  double yi2y( size_t yi ) const;
  
  // bounds checking
  bool x_ok(double x) const;
  bool y_ok(double y) const;
  bool xi_ok(size_t xi) const { return xi < x_size; }
  bool yi_ok(size_t yi) const { return yi < y_size; }
  
protected:
  friend class SurfaceFactory;
  friend class BoxSurfaceTool;

  // xi, yi indices, 0..
  size_t x_size, y_size;
  // each x or y increment represents how many meters? e.g. x=25, y=50
  double x_step, y_step;
  double x_min, y_min;

};

// simple surface defined by a single height map over a structured grid
// examples are acousticsurface (full xy extent)
// and reflectors (beware places where it terminates, untested)
class Surface: public Grid
{
public:
  Surface() : Grid(), depth_map(0){};
  virtual ~Surface() { ArrayFactory<double>::delete_array2(depth_map); depth_map = 0; }

  // find (an) intersection of segment ab with the surface.
  Point intersection( const Point &a, const Point &b) const;
  
  // depth below any point
  double depth( double x, double y) const;
  
  // depth of the four corners and center of the grid cell (xi,xi+1) X (yi,yi+1)
  void grid_depth( size_t xi, size_t yi, double &q00, double &q01, double &q11, double &q10, double &qc ) const;

  // compute the maximum slope of the surface within any one cell
  double max_slope() const;
  
  // depth at grid points
  // access function
  // could call them both "depth," but this is more type careful
  double depth_xy( double x, double y ) const;
  double depth_ij( size_t xi, size_t yj ) const;

  // convert any depths beyond the given depth, to the new max_z value
  // can be used to expand depths as well
  void truncate_depth(double depth, double max_z);
  
  // debug
  void print() const;
  
protected:
  friend class SurfaceFactory; 
  friend class BoxSurfaceTool;
  friend class SurfaceInclusion;

  //== methods
  
  // set depth, by reference. Called something different than depth_xy for clarity of where we do assignment
  double &depth_xy_reference( double x, double y );

  //== data
  
  // 2d array of depth data. 0 .. 10^5 or so
  double **depth_map;
}; //class SurfaceSingle

// return true if the two surfaces have the same grid
inline
bool Grid::same_grid( const Grid *s ) const
{
  return ( x_size == s->x_size && y_size == s->y_size && x_step == s->x_step && y_step == s->y_step && x_min == s->x_min && y_min == s->y_min );
}
inline
void Grid::copy_grid( const Grid *s )
{
  x_size = s->x_size;
  y_size = s->y_size;
  x_step = s->x_step;
  y_step = s->y_step;
  x_min = s->x_min;
  y_min = s->y_min;
}

// ==========================
//  inlines
// ==========================
inline
bool Grid::x_ok(double x) const
{
  double intpart;
  const double fracpart = modf( (x - x_min) / x_step, &intpart);
  return( fabs(fracpart) < 1.0e-4 ); // absolute, or relative to intpart?
}

inline
bool Grid::y_ok(double y) const
{
  double intpart;
  const double fracpart = modf( (y - y_min) / y_step, &intpart);
  return( fabs(fracpart) < 1.0e-4 ); // absolute, or relative to intpart?
}


inline
size_t Grid::x2i( double x ) const
{
  // return floor( (x - x_min) / x_step );
  
  // truncate to valid range
  const double dx = x - x_min;
  if ( dx < 0. )
    return 0.;
  
  const size_t i = floor( dx / x_step );
  // return at most x_size-2 because x_size-1 is the largest valid index into the grid
  if ( !(i < x_size-1) )
    return x_size-2;
  return i;
}

inline
size_t Grid::y2i( double y ) const
{
  // return floor( (y - y_min) / y_step );
  
  // truncate to valid range
  const double dy = y - y_min;
  if ( dy < 0. )
    return 0.;
  
  const size_t i = floor( dy / y_step );
  // return at most y_size-2 because y_size-1 is the largest valid index into the grid
  if (! (i < y_size-1) )
    return y_size-2;
  return i;
}


inline
size_t Grid::x2i( double x, double &xifrac ) const
{
  // return floor( (x - x_min) / x_step );
  
  // truncate to valid range
  const double dx = x - x_min;
  
  // const size_t i = floor( dx / x_step );
  double intpart;
  xifrac = modf( dx / x_step, &intpart );
  
  if (intpart < 0.)
    return 0.;
  while (! (intpart < x_size-1) )
  {
    intpart--;
    xifrac++;
  }
  return size_t ( intpart );
}

inline
size_t Grid::y2i( double y, double &yifrac ) const
{
  // return floor( (y - y_min) / y_step );
  
  // truncate to valid range
  const double dy = y - y_min;
  
  //  const size_t i = floor( dy / y_step );
  double intpart;
  yifrac = modf( dy / y_step, &intpart );
  if (intpart < 0.)
    return 0.;
  while (! (intpart < y_size-1) )
  {
    intpart--;
    yifrac++;
  }
  return size_t ( intpart );
}

inline
size_t Grid::x2xi( double x ) const
{
  assert( x_ok(x) );
  const size_t xi = floor( (x - x_min) / x_step  + 0.5 );
  assert( xi < x_size );
  return xi;
}

inline
size_t Grid::y2yi( double y ) const
{
  assert( y_ok(y) );
  const size_t yi = floor( (y - y_min) / y_step  + 0.5 );
  assert( yi < y_size );
  return yi;
}

inline
double Grid::xi2x( size_t xi ) const
{
  assert( xi_ok(xi) );
  return x_min + x_step * xi;
}

inline
double Grid::yi2y( size_t yi ) const
{
  assert( yi_ok(yi) );
  return y_min + y_step * yi;
}


inline
double &Surface::depth_xy_reference( double x, double y )
{
  assert( x_ok(x) );
  assert( y_ok(y) );
  return depth_map [x2xi(x)] [y2yi(y)];
}

inline
double Surface::depth_xy( double x, double y ) const
{
  assert( x_ok(x) );
  assert( y_ok(y) );
  return depth_map [x2xi(x)] [y2yi(y)];
}

inline
double Surface::depth_ij( size_t xi, size_t yi ) const
{
  assert( xi_ok(xi) );
  assert( yi_ok(yi) );
  return depth_map[xi][yi];
}


inline
void Surface::grid_depth( size_t xi, size_t yi, double &q00, double &q01, double &q10, double &q11, double &qc ) const
{
  // depth at corners of square
  q00 = depth_ij(xi,   yi   );
  q01 = depth_ij(xi,   yi+1 );
  q10 = depth_ij(xi+1, yi   );
  q11 = depth_ij(xi+1, yi+1 );
  
  // depth at center
  qc = ( q00 + q01 + q10 + q11 ) * 0.25;
}

inline
void Grid::grid_xy( size_t xi, size_t yi, double &x0, double &x1, double &y0, double &y1, double &xc, double &yc ) const
{
  x0 = xi2x(xi);
  x1 = x0 + grid_x();
  xc = x0 + grid_x() * 0.5;

  y0 = yi2y(yi);
  y1 = y0 + grid_y();
  yc = x0 + grid_x() * 0.5;
}

#endif /* defined(__BoxTreeMesh__Surface__) */
