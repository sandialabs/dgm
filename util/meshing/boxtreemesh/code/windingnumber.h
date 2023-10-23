//
//  windingnumber.h
//  BoxTreeMesh
//
//  Created by Mitchell, Scott A on 4/14/16.
//  Copyright (c) 2016 Sandia National Labs. All rights reserved.
//
//  Compute "is point in polygon" for 2d polygons in xy plane

//  Wrapper around free code from http://geomalgorithms.com/a03-_inclusion.html
//
// Copyright 2000 softSurfer, 2012 Dan Sunday
// This code may be freely used and modified for any purpose
// providing that this copyright notice is included with it.
// SoftSurfer makes no warranty for this code, and cannot be held
// liable for any real or imagined damage resulting from its use.
// Users of this code must verify correctness for their application.


#ifndef __BoxTreeMesh__windingnumber__
#define __BoxTreeMesh__windingnumber__

#include <stdio.h>
#include "point.h"

class Triangle;

class WindingNumber
{
public:

  bool point_in_face( Point q, Point face_nodes[4] );
  
private:
  // original
  // a Point is defined by its coordinates {int x, y;}
  //===================================================================
  // scott: code doesn't look like it cares what type x and y are  
  
  double isLeft( Point P0, Point P1, Point P2 );
  
  // unused
  // crossing number algorithm
  // int cn_PnPoly( Point P, Point* V, int n );
  
  // winding number algorithm
  int wn_PnPoly( Point P, Point* V, int n );
  
};

inline
bool WindingNumber::point_in_face( Point q, Point face_nodes[4] )
{
  // make a polygon with the first node repeated at the end
  Point pn[5] = { face_nodes[0], face_nodes[1], face_nodes[2], face_nodes[3], face_nodes[0] };
  
  return (bool) wn_PnPoly( q, pn, 4 );
}

// isLeft(): tests if a point is Left|On|Right of an infinite line.
//    Input:  three points P0, P1, and P2
//    Return: >0 for P2 left of the line through P0 and P1
//            =0 for P2  on the line
//            <0 for P2  right of the line
//    See: Algorithm 1 "Area of Triangles and Polygons"
inline double
WindingNumber::isLeft( Point P0, Point P1, Point P2 )
{
  return ( (P1.x - P0.x) * (P2.y - P0.y)
          - (P2.x -  P0.x) * (P1.y - P0.y) );
}
//===================================================================




#endif /* defined(__BoxTreeMesh__windingnumber__) */
