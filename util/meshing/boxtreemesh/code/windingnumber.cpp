//
//  windingnumber.cpp
//  BoxTreeMesh
//
//  Created by Mitchell, Scott A on 4/14/16.
//  Copyright (c) 2016 Sandia National Labs. All rights reserved.
//

#include "windingnumber.h"

/*
// cn_PnPoly(): crossing number test for a point in a polygon
//      Input:   P = a point,
//               V[] = vertex points of a polygon V[n+1] with V[n]=V[0]
//      Return:  0 = outside, 1 = inside
// This code is patterned after [Franklin, 2000]
int
WindingNumber::cn_PnPoly( Point P, Point* V, int n )
{
  int    cn = 0;    // the  crossing number counter
  
  // loop through all edges of the polygon
  for (int i=0; i<n; i++) {    // edge from V[i]  to V[i+1]
    if (((V[i].y <= P.y) && (V[i+1].y > P.y))     // an upward crossing
        || ((V[i].y > P.y) && (V[i+1].y <=  P.y))) { // a downward crossing
      // compute  the actual edge-ray intersect x-coordinate
      // original:     float vt = (float)(P.y  - V[i].y) / (V[i+1].y - V[i].y);
      double vt = (P.y  - V[i].y) / (V[i+1].y - V[i].y);
      if (P.x <  V[i].x + vt * (V[i+1].x - V[i].x)) // P.x < intersect
        ++cn;   // a valid crossing of y=P.y right of P.x
    }
  }
  return (cn&1);    // 0 if even (out), and 1 if  odd (in)
  
}
//===================================================================
*/

// wn_PnPoly(): winding number test for a point in a polygon
//      Input:   P = a point,
//               V[] = vertex points of a polygon V[n+1] with V[n]=V[0]
//      Return:  wn = the winding number (=0 only when P is outside)
int
WindingNumber::wn_PnPoly( Point P, Point* V, int n )
{
  int    wn = 0;    // the  winding number counter
  
  // loop through all edges of the polygon
  for (int i=0; i<n; i++) {   // edge from V[i] to  V[i+1]
    if (V[i].y <= P.y) {          // start y <= P.y
      if (V[i+1].y  > P.y)      // an upward crossing
        if (isLeft( V[i], V[i+1], P) > 0)  // P left of  edge
          ++wn;            // have  a valid up intersect
    }
    else {                        // start y > P.y (no test needed)
      if (V[i+1].y  <= P.y)     // a downward crossing
        if (isLeft( V[i], V[i+1], P) < 0)  // P right of  edge
          --wn;            // have  a valid down intersect
    }
  }
  return wn;
}
//===================================================================


