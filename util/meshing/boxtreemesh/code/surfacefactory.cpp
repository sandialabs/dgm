//
//  SurfaceFactory.cpp
//  BoxTreeMesh
//
//  Created by Mitchell, Scott A on 3/1/16.
//  Copyright (c) 2016 Sandia National Labs. All rights reserved.
//

#include "SurfaceFactory.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits.h>
#include <assert.h>

inline
void SurfaceFactory::dimensions( double x, double &x_max, double &x_min, double &x_step )
{
  if (isnan(x))
    return;
  
  if ( x > x_max )
    x_max = x;

  // x_step, smallest non-zero difference between any x and xmin
  const double dx = x - x_min;
  if ( fabs(dx) > 0. )
  {
    if ( fabs(dx) < x_step )
      x_step = fabs(dx);
    else
    {
      // sanity check, dx_step should be an integer multiple of x_step
      double intpart;
      const double fracpart = modf(dx / x_step, &intpart);
      assert( fabs(fracpart) < 1.0e-7 );
    }
  }
  
  if ( x < x_min )
    x_min = x;

}


void SurfaceFactory::set_surface( double xmin, double ymin, double x_step, double y_step, size_t x_size, size_t y_size )
{
  _s->x_size = x_size;
  _s->y_size = y_size;
  _s->x_min = xmin;
  _s->x_step = x_step;
  _s->y_min = ymin;
  _s->y_step = y_step;
  _s->depth_map = ArrayFactory<double>::new_array2(x_size,y_size);
  
  for (size_t xi = 0; xi < x_size; ++xi )
  {
    double x = _s->xi2x(xi);
    for (size_t yi = 0; yi < y_size; ++yi )
    {
      double y = _s->yi2y(yi);
      _s->depth_map[xi][yi] = depth_function(x,y);
    }
  }
}

bool SurfaceFactory::read( std::string fname, bool error_if_fail, Grid *surface_hint )
{
  // determine size and dimensions,
  // allocate memory
  // fill in depth map

  // * implement this first
  // less memory
  // take two passes reading the data from file
  
  // less time
  // store data in a temporary vector
  
  // both
  // add header information to the files
  
  // call should set _s surface first
  assert(_s);
  if (!_s)
  {
    if (error_if_fail)
      std::cerr << "ERROR: SurfaceFactory::read, no surface storage provided." << std::endl;
    return false;
  }

  //==== read file

  // header line
  // none
  
  std::ifstream file( fname, std::ios::in );
  
  std::cout << "reading depth-map surface from " << fname << " ...";
  std::cout.flush();
  if (!file.is_open())
  {
    if (error_if_fail)
    {
      std::cout << " ERROR" << std::endl;
      std::cerr << "Error opening " << fname << std::endl;
    }
    return false;
  }
 
  //== first pass, determine dimensions
  std::string line;
  std::stringstream ss;
  
  if (surface_hint)
  {
    _s->copy_grid( surface_hint );
  }
  else
  {
    // read data coordinates
    // x  y z
    const double dmax = std::numeric_limits<double>::max();
    const double dmin = std::numeric_limits<double>::lowest();
    _s->x_min = dmax; _s->y_min = dmax;
    double  x_max(dmin), y_max(dmin);
    _s->x_step = dmax; _s->y_step = dmax;
    while (std::getline(file, line))
    {
      ss.clear();
      ss.str(line);
      double x,y,z;
      ss >> x >> y >> z;
      
      // z is either a number of a NaN
      // we don't care at this point
      // isnan(z);
      
      dimensions( x, x_max, _s->x_min, _s->x_step );
      dimensions( y, y_max, _s->y_min, _s->y_step );
    }
    // no data? bad data?
    if ( x_max < _s->x_min || y_max < _s->y_min )
    {
      if (error_if_fail)
      {
        std::cerr << " ERROR: bad or missing xy coordinate data" << std::endl;
      }
      return false;
    }
    _s->x_size = floor( (x_max - _s->x_min) / _s->x_step + 0.5) + 1;
    _s->y_size = floor( (y_max - _s->y_min) / _s->y_step + 0.5) + 1;
  }
  
  std::cout << "values:" << _s->x_size * _s->y_size << " as " << _s->x_size << " by " << _s->y_size << ", dx:" << _s->x_step << " dy:" << _s->y_step << " ...";
  std::cout.flush();
  
  // allocate memory for depth_map
  _s->depth_map = ArrayFactory<double>::new_array2(_s->x_size,_s->y_size);
  // initialize depths to NAN, in case the file has missing x,y values
  std::fill_n(_s->depth_map[0], _s->x_size * _s->y_size, NAN);
  
  // reset file, read a second time, filling in with real values
  // reset file
  file.clear();
  file.seekg(0, std::ios::beg);

  while (std::getline(file, line))
  {
    ss.clear();
    ss.str(line);
    double x,y,z;
    ss >> x >> y >> z;
    
    // ? valid x and y?
    if (isnan(x) || isnan(y))
      continue;
    
    // fill in
    // do we need to do anything with NaN?
    _s->depth_xy_reference(x,y) = z;
  }
  std::cout << " done." << std::endl;
  return true;
}


void SurfaceInclusionFactory::read( std::string fname, int max_layers )
{
  std::cout << "Reading depth maps for inclusion surface " << fname << std::endl;
  bool read_success = true;
  int fileid = 0;
  std::stringstream ss;
  Grid *surf_hint(0);
  SurfaceFactory sf(0);
  while (read_success)
  {
    fileid++;
    ss.clear();
    ss.str(""); // clear();
    ss << "top" << fname << fileid << ".xyz";
    sf.new_surface();
    // error if first read fails
    bool read_top_success = sf.read(ss.str(), fileid == 1, surf_hint );
    // debuggin, quit early, just read a few surfaces
    if ( read_top_success )
    {
      _s->_surfs.push_back(sf._s);
      if (!surf_hint)
      {
        surf_hint = sf._s;
        _s->copy_grid( surf_hint );
      }
      if ( 1+(fileid-1)*2 == max_layers )
        goto quit;
    
      ss.clear();
      ss.str(""); // clear();
      ss << "bot" << fname << fileid << ".xyz";
      sf.new_surface();
      bool read_bot_success = sf.read(ss.str(), false, surf_hint );
      // if no bottom, then inclusion extends below domain, which is OK.
      // assert( read_bot_success );
      if (read_bot_success)
      {
        _s->_surfs.push_back(sf._s);
      }
      else
      {
        std::cout << "no such file.\n";
        read_success = false;
      }
    }
    else
    {
      std::cout << "no such file.\n";
      read_success = false;
    }
    if ( (fileid)*2 == max_layers )
      goto quit;
  }
quit:
  std::cout << "Done reading depth maps for inclusion surface " << fname << std::endl;
}

void SurfaceInclusionFactory::write( std::string fname, const double f )
{
  int fileid=0;
  int is_top=0;
  for (size_t s=0; s < _s->_surfs.size(); ++s )
  {
    std::string fn;
    if (is_top==0)
    {
      is_top = 1;
      ++fileid;
      fn = "top";
    }
    else
    {
      is_top = 0;
      fn = "bot";
    }
    fn += fname + std::to_string(fileid) + ".xyz";
    
    Surface *surf = _s->_surfs[s];
    SurfaceFactory sf(surf);
    sf.write(fn);
  }
}


void SurfaceFactory::write( std::string fname, const double f  )
{
  std::cout << "writing depth-map surface to " << fname << " ...";
  std::cout.flush();

  // overwrites
  std::ofstream file( fname, std::ios::out );
  if (!file.is_open())
  {
    std::cout << " ERROR" << std::endl;
    std::cerr << "Error opening " << fname << std::endl;
    return;
  }
  
  std::cout << "values:" << _s->x_size * _s->y_size << " as " << _s->x_size << " by " << _s->y_size << ", dx:" << _s->x_step << " dy:" << _s->y_step << " ...";
  std::cout.flush();
  
  // c-style seems easier to get the exact same output as input
  char c[100]; // 13*3 + 6 + 1
  for (size_t i = 0; i < _s->x_size; ++i )
  {
    const double x = _s->xi2x(i);
    for (size_t j = 0; j < _s->y_size; ++j )
    {
      const double y = _s->yi2y(j);
      const double z = _s->depth_ij(i,j);
      sprintf(c,"   %13.7e   %13.7e   %13.7e\n",f*x,f*y,f*z);
      // convert "nan" to "NaN", to get exact same output as input
      if ( c[45] == 'n' )
      {
        c[45] = 'N';
        c[47] = 'N';
      }
      file << c;
    }
  }
  std::cout << " done." << std::endl;
}

void SurfaceFactory::write_ply( std::string fname, const double f )
{
  std::cout << "Writing surface to polygon file (.ply) " << fname << "...";
  std::cout.flush();
  
  // assign ids if not already done
  size_t num_vertices = _s->grid_x_size() * _s->grid_y_size();
  size_t num_faces = (_s->grid_x_size()-1) * (_s->grid_y_size()-1);
  
  // open file
  // erases any old data
  std::fstream file(fname.c_str(), std::ios::out);
  
  // header
  file << "ply\n";
  file << "format ascii 1.0\n";
  file << "element vertex " << num_vertices << "\n";
  file << "property float x\n";
  file << "property float y\n";
  file << "property float z\n";
  file << "element face " << num_faces << "\n";
  file << "property list uchar int vertex_index\n";
  file << "end_header\n";
  
  // vertex coordinates
  // numbering starts at 0
  size_t id(0);
  for ( size_t xi = 0; xi < _s->grid_x_size(); ++xi )
    for ( size_t yi = 0; yi < _s->grid_y_size(); ++yi )
    {
      file << f*_s->xi2x(xi) << " " << f*_s->yi2y(yi) << " " <<  f*_s->depth_ij( xi, yi ) << "\n";
      ++id;
    }
  
  for ( size_t xi = 0; xi < _s->grid_x_size()-1; ++xi )
    for ( size_t yi = 0; yi < _s->grid_y_size()-1; ++yi )
    {
      // id of four corners of the quad
      size_t a = id;
      size_t b = id+1;
      size_t c = b + _s->grid_x_size();
      size_t d = a + _s->grid_x_size();
      
      file << "4 " << a << " " << b << " " << c << " " << d << "\n";

      ++id;
    }
  
  file.flush();
  
  std::cout << " done." << std::endl;
}


void SurfaceFactory::write_cubit_surface_jou( std::string fname, const double f )
{
  std::cout << "Writing surface construction script to cubit journal file (.jou) " << fname << "...";
  std::cout.flush();
  
  // overwrites
  std::ofstream file( fname, std::ios::out );
  if (!file.is_open())
  {
    std::cout << " ERROR" << std::endl;
    std::cerr << "Error opening " << fname << std::endl;
    return;
  }

  file << "# play cubit journal file to create surface as connected quads\n"
  << "echo off\njournal off\ngraphics pause\n";

  const size_t num_nodes = _s->x_size * _s->y_size;
  const size_t num_faces = (_s->x_size-1) * (_s->y_size-1);
  
  if (num_nodes==0 || num_faces==0)
    file << "empty mesh, no faces!\n";
  else
  {
    // nodes
    for (size_t i = 0; i < _s->x_size; ++i )
    {
      const double x = _s->xi2x(i);
      for (size_t j = 0; j < _s->y_size; ++j )
      {
        const double y = _s->yi2y(j);
        const double z = _s->depth_ij(i,j);
        file << "create node " << f*x << " " << f*y << " " << f*z << "\n";
      }
    }
    
    // aprepro define starting id of the newly created nodes
    file << "#{node1=Id(\"node\")} {node0=node1-" << num_nodes-1 << "}\n";
    file << "group 'surfacenodes' equals node {node0} to {node1}\n";
    
    // faces
    file << "#{numfaces=" << num_faces << "} {xsize=" << _s->x_size << "} {ysize=" << _s->y_size << "}\n";
    file << "#{i=0}\n";
    file << "#{loop("<< _s->x_size-1 << ")}\n";
    file << "#{j=0}\n";
    file << "#{loop("<< _s->y_size-1 << ")}\n";
    file << "#{n1 = node0 + 1 +  i    * ysize + j};\n";
    file << "#{n2 = node0     +  i    * ysize + j};\n";
    file << "#{n4 = node0 + 1 + (i+1) * ysize + j};\n";
    file << "#{n3 = node0     + (i+1) * ysize + j};\n";
    file << "create face node {n1} {n2} {n3} {n4}\n";
    file << "#{++j}\n";
    file << "#{endloop}\n";
    file << "#{++i}\n";
    file << "#{endloop}\n";
    
    file << "#{face1=Id(\"face\")} {face0=face1-" << num_faces-1 << "}\n";
    file << "group 'surfacefaces' equals face {face0} to {face1}\n";

//  // faces
//  for (size_t i = 0; i + 1 < x_size; ++i )
//  {
//    for (size_t j = 0; j + 1 < y_size; ++j )
//    {
//      size_t n1 = 2 +  i    * y_size + j;
//      size_t n2 = 1 +  i    * y_size + j;
//      size_t n4 = 2 + (i+1) * y_size + j;
//      size_t n3 = 1 + (i+1) * y_size + j;
//      file << "create face node " << n1 << " " << n2 << " " << n3 << " " << n4 << "\n";
//    }
//  }
  
  }
  file << "zoom reset\ndisplay\necho on\njournal on" << std::endl;
  
  std::cout << " done." << std::endl; 
}
