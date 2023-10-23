//
//  surfaceinclusion.cpp
//  BoxTreeMesh
//
//  Created by Mitchell, Scott A on 5/3/16.
//  Copyright (c) 2016 Sandia National Labs. All rights reserved.
//

#include "surfaceinclusion.h"

bool SurfaceInclusion::verify() const
{
  if (_surfs.empty())
  {
    std::cout << "SurfaceInclusion is empty" << std::endl;
    return false;
  }
  
  // grids of all surfaces are the same
  for ( size_t i = 0; i < _surfs.size(); ++i )
  {
    Surface *si = _surfs[i];
    
    if ( !same_grid(si) )
    {
      std::cout << "ERROR SurfaceInclusion: surf " << i << " is defined over a different grid." << std::endl;
      return false;
    }
  }
  
  bool bad = false;
  
  // depths are monotonically increasing
  // but not necessarily strictly increasing
  for ( size_t i = 0; i < grid_x_size(); ++i )
    for ( size_t j = 1; j < grid_y_size(); ++j )
    {
      for (int s = 0; s+1 < _surfs.size(); ++s)
      {
        Surface *sA = _surfs[s];
        double d = sA->depth_ij(i,j);
        for ( size_t ss = s+1; ss < _surfs.size(); ++ss )
        {
          Surface *sB = _surfs[ss];
          double di = sB->depth_ij(i,j);
          if ( d > di )
          {
            std::cout << "ERROR SurfaceInclusion: surf " << s << " (of 0.." << _surfs.size()-1 << ") is below surf " << ss;
            std::cout << " depth " << d << " > " << di;
            std::cout << " at grid ij (" << i << ", " << j << ") = xy (" << _surfs[s]->xi2x(i) << ", " << _surfs[s]->yi2y(j) << ")"  << std::endl;
            bad = true;
            // return false;
          }
        }
      }
    }
  
  return !bad;
  // return true;
}

// debug
void SurfaceInclusion::print() const
{
  std::cout << "SurfaceInclusion " << this << std::endl;
  verify();
  if (!_surfs.empty())
  {
    std::cout << _surfs.size() << " underlying surfaces." << std::endl;
  }
  
  // grids of all surfaces are the same
  for ( size_t i = 0; i < _surfs.size(); ++i )
  {
    std::cout << "Underlying surface " << i << std::endl;
    Surface *si = _surfs[i];
    si->print();
  }
  
  
}

void SurfaceInclusion::truncate_depth(double depth, double max_z)
{
  for (size_t s=0; s<_surfs.size(); ++s)
    _surfs[s]->truncate_depth(depth, max_z);
}
