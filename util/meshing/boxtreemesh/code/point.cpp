//
//  point.cpp
//  BoxTreeMesh
//
//  Created by Mitchell, Scott A on 1/5/16.
//  Copyright (c) 2016 Sandia National Labs. All rights reserved.
//

#include "point.h"
#include <vector>

void Point::print() const
{
  std::cout << "Point ( " << x << ", " << y << ", " << z << " )" << std::endl;
}

double Point::cos_dihedral( const Point &p0, const Point &p1, const Point &p2, const Point &p3 )
{
  // vectors between points
  Point v01 = p1 - p0;
  Point v02 = p2 - p0;
  Point v03 = p3 - p0;
  
  // normals to plane p0,p1,p2 and p0,p1,p3
  Point n2 = v01.cross(v02);
  Point n3 = v01.cross(v03);
  
  // normalize
  n2.normalize();
  n3.normalize();
  
  double costheta = n2.dot(n3);
  return costheta;
}

bool TriangleMath::close_to_segment( const Point &a, const Point&b, const Point& p, const double rel_tol2, const double abs_tol2)
{
  // distance to points
  Point pa = p-a;
  Point pb = p-b;
  Point ba = b-a;
  const double pa2 = pa.length2();
  const double pb2 = pb.length2();
  const double ba2 = ba.length2();
  // close to an endpoint?
  if (pa2 < abs_tol2 || pb2 < abs_tol2)
    return true;
  // is p farther from both endpoints than half the segment length?
  // takes care of the case that a==b or nearly so
  if ( 4. * pa2 > ba2 * (1.0 + rel_tol2) && 4. * pb2 > ba2 * (1.0 + rel_tol2))
    return false;
  // close to the interior of the segment?
  // project p to q, on line of segment
  // point to line distance
  // parameter t : q = a + t|ab| = a + tab
  assert(ba2 > 0.);
  double tab = pa.dot(ba); // / ab.length(); to get t
  // if outside segment, then not close
  if ( tab < 0. || tab > ba2 )
    return false;
  // distance between pa and qa
  const Point qa = ba * (tab / ba2);
  const double dist2 = (pa-qa).length2();
  const bool is_close = (dist2 < rel_tol2 * ba2);
//  if (is_close)
//  {
//    // debug
//    std::cout << "I found a random box point close to a triangle edge when projected, I'll use another random point." << std::endl;
//  }
  
  return is_close;
}


bool TriangleMath::close_to_edges_z(const Point &t0, const Point &t1, const Point &t2, const Point &p )
{
  const double tol2 = 1.0e-6; // relative to edge length2, so this is really like 1.0e-3
  Point tz0(t0); tz0.z = 0.;
  Point tz1(t1); tz1.z = 0.;
  Point tz2(t2); tz2.z = 0.;
  Point pz(p);    pz.z = 0.;
  std::vector<Point> verts;
  verts.push_back(tz0);
  verts.push_back(tz1);
  verts.push_back(tz2);
  verts.push_back(tz0);
  // add up squared length of all triangle edges, for use in the absolute tolerance
  const double seg_z_length2 = (tz0-tz1).length2() + (tz1-tz2).length2() + (tz0-tz2).length2();
  const double dist2_tol = seg_z_length2 * tol2;
  
  for (size_t i = 0; i < 3; ++i)
  {
    if ( close_to_segment( verts[i], verts[i+1], pz, tol2, dist2_tol) )
      return true;
  }
  return false;
  
}

void TriangleMath::barycentric_z(const Point &a, const Point &b, const Point &c, const Point &p, Point &p_bary)
{
  // Adapted from Christer Ericson's book Real-Time Collision Detection
  // Compute barycentric coordinates (u, v, w) for
  // point p with respect to triangle (a, b, c)
  // void Barycentric(Point p, Point a, Point b, Point c, float &u, float &v, float &w)
  Point v0 = b - a, v1 = c - a, v2 = p - a;
  const double d00 = v0.x * v0.x + v0.y * v0.y; // float d00 = Dot(v0, v0);
  const double d01 = v0.x * v1.x + v0.y * v1.y; // float d01 = Dot(v0, v1);
  const double d11 = v1.x * v1.x + v1.y * v1.y; // float d11 = Dot(v1, v1);
  const double d20 = v2.x * v0.x + v2.y * v0.y; // float d20 = Dot(v2, v0);
  const double d21 = v2.x * v1.x + v2.y * v1.y; // float d21 = Dot(v2, v1);
  const double denom = d00 * d11 - d01 * d01;
  p_bary.x = (d11 * d20 - d01 * d21) / denom; // v
  p_bary.y = (d00 * d21 - d01 * d20) / denom; // w
  p_bary.z = 1.0f - p_bary.x - p_bary.y; // u
}


double TriangleMath::depth_z_from_bary(const Point &t0, const Point &t1, const Point &t2, Point &p_bary)
{
  const double z = t0.z * p_bary.x + t1.z * p_bary.y + t2.z * p_bary.z;
  return z;
}

void TriangleMath::crosses_from_neg_infinity(const Point &t0, const Point &t1, const Point &t2, const Point &p, bool &crosses, bool &degenerate)
{
  Point p_bary;
  barycentric_z(t0, t1, t2, p, p_bary);
  // check for degeneracy
  const double tol = 1e-4; // relative to the 0-1 barycentric coordinates
  
  // outside triangle? check this before degeneracy
  if (p_bary.x > 1.0 + tol || p_bary.x < -tol ||
      p_bary.y > 1.0 + tol || p_bary.y < -tol ||
      p_bary.z > 1.0 + tol || p_bary.z < -tol)
  {
    crosses = false;
    degenerate = false;
    return;
  }
  
  // interior to triangle
  if (p_bary.x < 1.0 - tol && p_bary.x > tol &&
      p_bary.y < 1.0 - tol && p_bary.y > tol &&
      p_bary.z < 1.0 - tol && p_bary.z > tol)
  {
    degenerate = false;
    // check z coordinate of triangle
    const double tz = depth_z_from_bary(t0, t1, t2, p_bary);
    crosses = (tz < p.z);
  }
  
  // some sort of degeneracy, barycentric coordinates almost on triangle edge
  else
  {
    // The degeneracy may be just that a triangle was vertical.
    // So, double-check that p is close to an edge. If not, then call it a non-crossing
    bool near_degen = close_to_edges_z(t0, t1, t2, p );
    if (near_degen)
    {
      degenerate = true;
      crosses = false;
      return;
    }
    else
    {
      degenerate = false;
      crosses = false;
      return;
    }
  }
}

