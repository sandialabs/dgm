//
//  surfaceinclusion.h
//  BoxTreeMesh
//
//  Created by Mitchell, Scott A on 5/3/16.
//  Copyright (c) 2016 Sandia National Labs. All rights reserved.
//

#ifndef __BoxTreeMesh__surfaceinclusion__
#define __BoxTreeMesh__surfaceinclusion__

#include <vector>
#include "surface.h"

// grid x and y index, and si is which surface, an index into _surfs
class SSGridI : public GridIndex
{
public:
  SSGridI() : GridIndex() {}
  size_t si = (size_t) -1;
};

// representation of the bounding surface of some volume of inclusion
class SurfaceInclusion: public Grid
// Grid is the common base class with Surface
{
public:
  SurfaceInclusion() {}
  
  // is the surface well defined?
  bool verify() const;
 
  // given inclusionsurface "point" p, return the "point" it is connected to in the +x, -x, +y, or -y direction.
  // return true if that point is a horizontal point
  // false if it is a "vertical" connection, to a point immediately above or below the current one
  // false if there is no connection, such as at the sides of the domain, or the surface patch extends beyond the bottom of the domain
  // f is the "direction", the same as the face indices of a hex: 0 is down, 5 is up, 1 to 4 are horizontal, etc.
  // if there is no connection, then si == -1, 
  bool edge( SSGridI p, SSGridI &q, int f ) const;

  // how many surfaces (depth maps) are there?
  size_t num_surfs() const { return _surfs.size(); }
  // depth of the i'th one
  double depth_ij( size_t xi, size_t yj, size_t sk ) const
  { return _surfs[sk]->depth_ij(xi,yj); }

  // convert any depths beyond the given depth, to the new max_z value
  // can be used to expand depths as well
  void truncate_depth(double depth, double max_z);

  // debug
  void print() const;

protected:
  friend class SurfaceInclusionFactory;
  friend class BoxSurfaceInclusionTool;

  // collection of depth-maps defining the bounding surfaces
  std::vector<Surface*> _surfs;
};

#endif /* defined(__BoxTreeMesh__surfaceinclusion__) */
