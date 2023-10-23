//
//  Surface.cpp
//  BoxTreeMesh
//
//  Created by Mitchell, Scott A on 3/1/16.
//  Copyright (c) 2016 Sandia National Labs. All rights reserved.
//

#include "Surface.h"

#include <vector>
#include <valarray>
#include <limits.h>

void Surface::print() const
{
  std::cout << "printing surface " << this << std::endl;
  std::cout << "x,y number of data points " << x_size << " , " << y_size << std::endl;
  std::cout << "x,y data point spacing  " << grid_x() << " , " << grid_y() << std::endl;
  std::cout << "x,y coordinate box " << min_x() << "," << min_y() << "  to  " << max_x() << "," << max_y() << std::endl;
  // coarse map of depths
  std::cout << "depth samples:\n";
  for (size_t i = 0; i < 10; ++i)
  {
    for (size_t j = 0; j < 10; ++j)
    {
      size_t xi = i * (x_size / 10);
      size_t yj = j * (y_size / 10);
      
      double depth = depth_ij(xi,yj);
      
      printf( "  %10.3f", depth);
    }
    std::cout << std::endl;
  }
}

double Surface::depth( double x, double y) const
{
  // divide rectangle into triangles, planar interpolation in each
  //
  //     q01 --------------- q11     q01 --------------- q11   q01 --------------- q11
  //      | \               / |       |                 / |     | \                 |
  //      |  \             /  |       |                /  |     |  \                |
  //      |   \     3     /   |       |               /   |     |   \               |
  //      |    \         /    |       |              /    |     |    \              |
  //      |     \       /     |       |             /     |     |     \             |
  //      |      \     /      |       |            /      |     |      \            |
  //      |       \   /       |       |           /       |     |       \           |
  //      |        \ /        |       |          /        |     |        \          |
  //      |  2     qc     1   |       |         /         |     |         \         |
  //      |        / \        |       |        /          |     |          \        |
  //      |       /   \       |       |       /           |     |           \       |
  //      |      /     \      |       |      /            |     |            \      |
  //      |     /       \     |       |     /             |     |             \     |
  //      |    /         \    |       |    / lower00_11   |     | lower01_10   \    |
  //  ^   |   /     0     \   |       |   /               |     |               \   |
  //  |   |  /             \  |       |  /                |     |                \  |
  //  y  q00 --------------- q10     q00 --------------- q10   q00 --------------- q10
  //
  //      x->
  
  // find grid square containing query point
  double qxifrac, qyifrac;
  const size_t x0i = x2i(x, qxifrac);
  const size_t y0i = y2i(y, qyifrac);
  
  // debug
//  if ( x0i == x_size )
//    std::cout << "x0i out of range" << std::endl;
//  else if ( x0i + 1 == x_size )
//    std::cout << "x1i out of range" << std::endl;
//  if ( y0i == y_size )
//    std::cout << "y0i out of range" << std::endl;
//  else if ( y0i + 1 == y_size )
//    std::cout << "y1i out of range" << std::endl;

  // depth at corners and center of square
  double q00, q01, q10, q11, qc;
  grid_depth( x0i, y0i, q00, q01, q10, q11, qc);
  
  // find triangle containing query point q
  // map to this triangle:
  //             qc
  //            /  \
  //           /    \
  //          /  q   \
  //         /        \
  //        c0--------c1
  //
  // where Cartisian coordinates of c0 = (0,0); c1 = (1,0); and qc = (0.5,1)
  //
  // xfrac and yfrac are coorindates of q in this system
  //
  const bool lower00_11 = ( qxifrac > qyifrac );
  const bool lower01_10 = ( qxifrac < (1. - qyifrac) );
  double c0, c1, xfrac(-1.), yfrac(-1.);
  if ( lower00_11 )
  {
    if ( lower01_10 )
    {
      // triangle 0
      c0 = q00;
      c1 = q10;
      yfrac = qyifrac * 2.;
      xfrac = qxifrac;
    }
    else
    {
      // triangle 1
      c0 = q10;
      c1 = q11;
      yfrac = 1. - ( qxifrac - 0.5 ) * 2.;
      xfrac = qyifrac;
     }
  }
  else
  {
    if ( lower01_10 )
    {
      // triangle 2
      c0 = q01;
      c1 = q00;
      yfrac = qxifrac * 2.;
      xfrac = 1. - qyifrac;
    }
    else
    {
      // triangle 3
      c0 = q11;
      c1 = q01;
      yfrac = 1. - ( qyifrac - 0.5 ) * 2.;
      xfrac = 1. - qxifrac;
    }
  }
  // bounds check
  // could fail if we are using an xfrac or yfrac > 1 or less than 0 because of hitting the domain boundary
//  assert( yfrac < 1. + 1e-4 );
//  assert( yfrac >     -1e-4 );
//  assert( xfrac < 1. + 1e-4 );
//  assert( xfrac >     -1e-4 );
//  assert( xfrac > 0.5 || yfrac <= (     2. *  xfrac       ) * (1. + 1e-4) + 1e-4);
//  assert( xfrac < 0.5 || yfrac <= (1. - 2. * (xfrac - 0.5)) * (1. + 1e-4) + 1e-4);

  // barycentric coordinates are almost imediate from these fractions
  // https://en.wikipedia.org/wiki/Barycentric_coordinate_system
  const double g0 = 1. - xfrac - 0.5 * yfrac;
  const double g1 =      xfrac - 0.5 * yfrac;
  const double gc =                    yfrac;
  
  const double q = g0 * c0 + g1 * c1 + gc * qc;
  
  return q;
}

// bilinear interpolation - simple here but not worth it elsewhere
//  // https://en.wikipedia.org/wiki/Bilinear_interpolation
//
//  // position relative to corners
//  const double dx0 = x - xi2x( x0i );  const double dx1 = x_step - dx0;
//  const double dy0 = y - yi2y( y0i );  const double dy1 = y_step - dy0;
//
//  assert( dx0 > -1.e-4 ); assert( dx0 < x_step + 1.e-4);
//  assert( dx1 > -1.e-4 ); assert( dx1 < x_step + 1.e-4);
//  assert( dy0 > -1.e-4 ); assert( dy0 < y_step + 1.e-4);
//  assert( dy1 > -1.e-4 ); assert( dy1 < y_step + 1.e-4);
//
//  // interpolation
//  const double q =
//  (
//   q00 * dx1 * dy1 +
//   q10 * dx0 * dy1 +
//   q01 * dx1 * dy0 +
//   q11 * dx0 * dy0
//  )
//  / (x_step * y_step);
//
//  return q;


double Surface::max_slope() const
{
  double max_dx(0.), max_dy(0.), max_dxy(0.);

  double q00, q01, q10, q11, qc;
  for (size_t xi = 0; xi < x_size - 1; ++xi)
    for (size_t yi = 0; yi < y_size - 1; ++yi)
    {
      // depth at corners of square
      grid_depth(xi,yi, q00, q01, q10, q11, qc);

      // slope along x
      const std::valarray<double> dx = { max_dx, fabs(q00 - q10), fabs(q01 - q11) };
      max_dx = dx.max();

      // slope along y
      const std::valarray<double> dy = { max_dy, fabs(q00 - q10), fabs(q01 - q11) };
      max_dy = dy.max();

      // slope along diagonals
      const std::valarray<double> dxy = { max_dxy, fabs(qc - q00), fabs(qc - q01), fabs(qc - q10), fabs(qc - q11) };
      max_dxy = dxy.max();
    }
  
  const std::valarray<double> slopes =
  { max_dx / x_step,  max_dy / y_step,  max_dxy * 2. / sqrt( x_step * x_step + y_step * y_step )};
  const double max_slope = slopes.max();
  return max_slope;
}

void Surface::truncate_depth(double depth, double max_z)
{
  for (size_t i = 0; i < grid_x_size(); ++i )
    for (size_t j = 0; j < grid_y_size(); ++j )
    {
      double &d = depth_map[i][j];
      if (isnan(d) || isinf(d) || d > depth)
        d = max_z;
    }
}

