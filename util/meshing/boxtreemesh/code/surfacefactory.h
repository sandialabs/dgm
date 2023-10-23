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

#ifndef __BoxTreeMesh__SurfaceFactory__
#define __BoxTreeMesh__SurfaceFactory__

#include <stdio.h>
#include <string>
#include <assert.h>
#include <math.h>

#include "surface.h"
#include "surfaceinclusion.h"
#include "random.h"
// avoid including BoxTree

class SurfaceFactory
{
public:
  SurfaceFactory(Surface *s) : _s(s) {}
  
  Surface *_s; // the surface modified
  
  void new_surface() { _s = new Surface; }
  void delete_surface() { delete _s; }
  
  // to create a particular surface, pass it a function that returns the depth at x and y points within the bounding box
  Surface *create_surface( double xmin, double ymin, double x_step, double y_step, size_t x_size, size_t y_size)
  {
    _s = new Surface;
    set_surface( xmin, ymin, x_step, y_step, x_size, y_size );
    return _s;
  }
  
  // set the depth of each grid point of the surface
  void set_surface( double xmin, double ymin, double x_step, double y_step, size_t x_size, size_t y_size);

  // given a surface with some depth set already, add the depth_function to
  void offset_surface();

  // used by set_surface to define the depth of the surface
  virtual double depth_function(double x, double y) {return 50;}

  // read surface from file
  // return true if success
  // if failure and error_if_fail, then print an error message
  // assume surface has same dimensions as surface_hint, if provided
  bool read( std::string fname, bool error_if_fail = true, Grid *surface_hint = 0 );
  // write surface to file
  // same file format as read
  // beware: overwrites any old file
  void write( std::string fname, const double nodal_scale_factor=1.0 );
  
  void write_ply( std::string fname, const double nodal_scale_factor=1.0 );
  
  // cubit script to create surface defined by free mesh
  void write_cubit_surface_jou( std::string fname = "cubit_surface.jou", const double nodal_scale_factor=1.0 );

private:
  // utility for read
  // given a new x value of a surface grid point, update the best guess of x_max, etc.
  void dimensions( double x, double &x_max, double &x_min, double &x_step );

};


class SurfaceInclusionFactory
{
public:
  SurfaceInclusionFactory(SurfaceInclusion *s = 0): _s(s) {}
  
  SurfaceInclusion *_s;

  // read surface from file
  // reads top<fname>?.xyz, bot<fname>?.xyz, where ? is [1..]
  void read( std::string fname, int max_layers = -1 );
  void write( std::string fname, const double nodal_scale_factor=1.0 );
  void write_cubit_surface_jou( std::string fname = "cubit_surface.jou", const double nodal_scale_factor=1.0 ) {}
};

// some surface depth definitions
class SFSlant : public SurfaceFactory
{
  public:
  SFSlant(Surface *s) : SurfaceFactory(s) {}
  double depth = 50.;
  double slope = 0.1;
  virtual double depth_function(double x, double y)
  {
    return depth + (0.5 * x + 1. * y)*slope;
  }
};

class SFSine : public SurfaceFactory
{
public:
  SFSine(Surface *s) : SurfaceFactory(s) {}

  double amplitude = 10;
  double x_period = 300;
  double y_period = 500;
  double depth = 50;

  virtual double depth_function(double x, double y)
  {
    const double PI = 2 * acos(0.0);
    return depth + ( sin( x * 2. * PI / x_period) + 0.8 * sin( y * 2. * PI / y_period ) ) * amplitude;
  }
};

class SFRandom : public SurfaceFactory
{
public:
  SFRandom(Surface *s) : SurfaceFactory(s), slope(1.) {}
  
  double slope; // settable
  double depth;
  virtual double depth_function(double x, double y)
  {
    const double r = Random::random_instance.generate_a_random_number(); // [0,1]
    return depth  + slope * r;
  }
};

class SFFlat : public SurfaceFactory
{
public:
  SFFlat(Surface *s) : SurfaceFactory(s), depth(50) {}
  
  double depth; // settable
  
  virtual double depth_function(double x, double y)
  {
    return depth;
  }
};

#endif /* defined(__BoxTreeMesh__SurfaceFactory__) */
