//
//  BoxSurfaceTool.cpp
//  BoxTreeMesh
//
//  Created by Mitchell, Scott A on 3/2/16.
//  Copyright (c) 2016 Sandia National Labs. All rights reserved.
//

#include "BoxSurfaceTool.h"
#include "tribox3.c"
#include <valarray>
#include <iostream>
#include <fstream>
#include <sstream>

void BSTool::set_domain_size(double z_min, double z_max)
{
  Point d_min, d_max;
  d_min.x = _g->min_x();
  d_min.y = _g->min_y();

  d_max.x = _g->max_x();
  d_max.y = _g->max_y();

  d_min.z = z_min;
  d_max.z = z_max;
  
  _bt->set_domain_size( d_min, d_max );
  
}

void BSTool::subgrid_range( const Box *b, size_t &xl, size_t &xh, size_t &yl, size_t &yh ) const
{
  xl = _g->x2i( b->corner_min().x ) + 1;
  xh = _g->x2i( b->corner_max().x ) + 1;
  yl = _g->y2i( b->corner_min().y ) + 1;
  yh = _g->y2i( b->corner_max().y ) + 1;
}


bool BoxSurfaceTool::overlaps_surface( BoxTreeNode *b ) const
{
  // subgrid inside box
  size_t xl, xh, yl, yh;
  subgrid_range(b, xl, xh, yl, yh);
  
  // check the triangles whose grid lies inside the box
  {
    // is the box above or below the surface?
    bool above = false;
    bool below = false;
    
    // check if any surface point is inside the box
    // or some edge between two such points passes through the box
    for ( size_t xi = xl; xi < xh; ++xi)
    {
      for ( size_t yi = yl; yi < yh; ++yi )
      {
        const double q = _s->depth_ij(xi,yi);
        if ( q > b->corner_max().z )
          above = true;
        else if ( q < b->corner_min().z )
          below = true;
        else
          return true; // surface point is inside the box
        // if some depths are above, some are below, then it must intersect
        if ( above && below )
          return true;
      }
    }
  }
  
  // The entire box was above or below the depth of the xy surface points in the box

  // check the triangles whose grid overlaps the boundary of the box
  // check each surface square that is partially contained to see if it crosses the box
  
  // indices are (xl-1, xl), (yl-1,yl), (xh,xh+1), (yh,yh+1)

  const size_t xol = xl-1;
  const size_t xoh = xh;
  const size_t yol = yl-1;
  const size_t yoh = yh;

  {
    size_t xi, yi;
    for ( yi = yol; yi < yoh; ++yi )
    {
      if ( overlaps_grid( b, xol, yi ) )
        return true;
      if ( overlaps_grid( b, xh-1,  yi ) )
        return true;
    }
    // indices +1 to skip checking the corner squares a second time
    for ( xi = xol+1; xi+1 < xoh; ++xi )
    {
      if ( overlaps_grid( b, xi, yol ) )
        return true;
      if ( overlaps_grid( b, xi, yh-1 ) )
        return true;
    }
  
  }
  
  return false;
}

bool BoxSurfaceTool::overlaps_grid( BoxTreeNode *b, size_t xi, size_t yi ) const
{
  // depth at corners and center of square
  double q00, q01, q10, q11, qc;
  _s->grid_depth( xi, yi, q00, q01, q10, q11, qc);

  // xy coordinates at corners and center of square
  double x0, x1, y0, y1, xc, yc;
  _s->grid_xy( xi, yi, x0, x1, y0, y1, xc, yc );

  // heuristic speedup: toss a square with all vertices below (above) the box.
  std::valarray<double> q = {q00, q01, q10, q11};
  if ( q.min() > b->corner_max().z )
    return false;
  if ( q.max() < b->corner_min().z )
    return false;

  // check intersection

  // call triBoxOverlap code on each of the four triangles
  if ( tri_box_overlap( b,  Point(x0, y0, q00),  Point(x0, y1, q01),  Point(xc, yc, qc) ) )
    return true;
  if ( tri_box_overlap( b,  Point(x0, y1, q01),  Point(x1, y1, q11),  Point(xc, yc, qc) ) )
    return true;
  if ( tri_box_overlap( b,  Point(x1, y1, q11),  Point(x1, y0, q10),  Point(xc, yc, qc) ) )
    return true;
  if ( tri_box_overlap( b,  Point(x1, y0, q10),  Point(x0, y0, q00),  Point(xc, yc, qc) ) )
    return true;
  
  // an alternative to triBoxOverlap is to
  // check if any triangle edge crosses a box face
  // check if any box edge crosses a triangle face (probably only need to consider the ones at a single corner).
  
  return false;
}

bool BoxSurfaceTool::tri_box_overlap( BoxTreeNode *b, const Point &p0, const Point &p1, const Point &p2 ) const
{
  // package data and call public domain code triboxoverlap in tribox3.c
  double boxcenter [] = {b->center_x(), b->center_y(), b->center_z()};
  double boxhalfsize [] = {b->diagonal_x() * 0.5, b->diagonal_y() * 0.5, b->diagonal_z() * 0.5};
  double triverts [3][3] = { {p0.x, p0.y, p0.z}, {p1.x, p1.y, p1.z}, {p2.x, p2.y, p2.z} };
  
  return (bool) triBoxOverlap( boxcenter, boxhalfsize, triverts );
}

void BoxSurfaceTool::depth_box( BoxTreeNode *b, double z[4] )
{
  z[0] = _s->depth( b->corner_min().x, b->corner_min().y ); // z00
  z[1] = _s->depth( b->corner_max().x, b->corner_min().y ); // z10
  z[2] = _s->depth( b->corner_max().x, b->corner_max().y ); // z11
  z[3] = _s->depth( b->corner_min().x, b->corner_max().y ); // z01
}

bool BoxSurfaceTool::update_min_max_depth( double q, double height_variation, double &z_min, double &z_max) const
{
  bool retval(false);
  // update min / max so far
  if ( q > z_max )
  {
    z_max = q;
    if ( ( z_max - z_min ) > height_variation )
      retval = true;
  }
  // not elseif because there might be only one point
  if ( q < z_min )
  {
    z_min = q;
    if ( ( z_max - z_min ) > height_variation )
      retval = true;
  }
  return retval;
}

bool BoxSurfaceTool::height_varies_at_least( BoxTreeNode *b, double height_variation )
{
  // subgrid inside box
  size_t xl, xh, yl, yh;
  subgrid_range(b, xl, xh, yl, yh);
  
  double z_min( _bt->get_domain().max_z() ), z_max(-1.);
  
  // height of surface grid points inside the box
  {
    for ( size_t xi = xl; xi < xh; ++xi)
    {
      for ( size_t yi = yl; yi < yh; ++yi )
      {
        double q = _s->depth_ij(xi,yi);

        // truncate q at box boundary
        if ( q > b->corner_max().z )
          q = b->corner_max().z;
        else if ( q < b->corner_min().z )
          q = b->corner_min().z;

        if ( update_min_max_depth( q, height_variation, z_min, z_max ) )
          return true;
      }
    }
  }
  
  // height at box corners
  double z[4];
  depth_box( b, z );
  if ( update_min_max_depth( z[0], height_variation, z_min, z_max ) ||
       update_min_max_depth( z[1], height_variation, z_min, z_max ) ||
       update_min_max_depth( z[2], height_variation, z_min, z_max ) ||
       update_min_max_depth( z[3], height_variation, z_min, z_max ) )
    return true;
  
  // height at side edges of grid squares crossing box boundary
  // I don't think we need to check the diagonal edges
  {
    size_t xi, yi;
    for ( yi = yl; yi < yh; ++yi )
    {
      const double y = _s->yi2y(yi);
      if ( update_min_max_depth( _s->depth( b->corner_min().x, y ), height_variation, z_min, z_max ) ||
           update_min_max_depth( _s->depth( b->corner_max().x, y ), height_variation, z_min, z_max ) )
        return true;
    }
    for ( xi = xl; xi < xh; ++xi )
    {
      const double x = _s->yi2y(yi);
      if ( update_min_max_depth( _s->depth(x, b->corner_min().y ), height_variation, z_min, z_max ) ||
           update_min_max_depth( _s->depth(x, b->corner_max().y ), height_variation, z_min, z_max ) )
        return true;
    }
  }
  
  return false;
}


bool BoxSurfaceTool::refine_near_surface_implementation(bool actually_refine)
{
  // combining boxes works for sure if the variation of height within a cubical box is less than 1/4 of the edge length.
  const double safe_slope = 0.25 / 1.415;
  const double max_slope = _s->max_slope();
  std::cout << "max slope:" << max_slope << " threshold:" << safe_slope;
  if ( max_slope < safe_slope )
    std::cout << " absolutely safe!";
  else
    std::cout << " proceed with caution.";
  std::cout << std::endl;
  
  bool changed = _refiner_near_surface && _refiner_near_surface->refine_implementation(actually_refine);
  
  return changed;
}


bool BoxSurfaceTool::refine_xy_to_reduce_surface_variation_implementation( Index xy_child_size, bool actually_change )
{  
  xy_child_size.z = 1;
  
  RefinerXYSurfaceVariation refiner(_bt,_s);
  refiner.child_size = xy_child_size;
  bool changed = refiner.refine_implementation(actually_change);
  return changed;
}

void BoxSurfaceTool::assign_box_acoustic_zone()
{
  // write to one of two files
  BTIOutput bti( _bt );
  for ( BoxTreeNode *b = bti.get(); b != 0; b = bti.next() )
  {
    if (is_acoustic(b))
      b->set_zone(BoxTreeNode::ACOUSTIC);
  }
}


bool RefinerXYSurfaceVariation::refine_condition(BoxTreeNode *b)
{
  // true if double merges, or one merge and surface gets too far from the merge surface,
  // or has extreme height variation
  
  double zmin, zmax;
  surface_range(b, zmin, zmax);
  
  // extreme height variation, more than 1/2 the box height?
  if ( zmax - zmin > 0.5 * b->diagonal_z() )
    return true;

  // merges?
  const bool m0 = merge0_condition(b, zmin, zmax);
  const bool m5 = merge5_condition(b, zmin, zmax);
  
  // double merges?
  if ( m0 && m5 )
    return true;
  
  // no merges?
  if ( !m0 && !m5 )
    return false;
  
  // one merge &&
  
  // surface crosses box midpoint, to far side from the merge face?
  if ( m0 && zmax > b->center_z() )
    return true;
  if ( m5 && zmin < b->center_z() )
    return true;
  
  return false;
}

bool RefinerNearSurface::refine_condition(BoxTreeNode *b)
{
  bool should_refine = ( overlaps_surface(b) ) && ( !(upper_size > b->diagonal()) || height_varies_at_least(b, height_variation ) );
  // debug
//  if (overlaps_surface(b) && !should_refine)
//  {
//    std::cout << "surface refiner stopping with box diagonal ";
//    b->diagonal().print();
//  }
  return should_refine;
}

void RefinerGridCheck::minimum_upper_size(BoxTree*bt, Grid *g, Index child_size, Point &min_upper_size)
{
  min_upper_size = bt->root->corner_max() - bt->root->corner_min();
  if (child_size == Index(1,1,1))
    return;

  Point lower_size (g->grid_x(), g->grid_y(), 0.);
  
  Point test_size = min_upper_size;
  while ( test_size > lower_size )
  {
    min_upper_size = test_size;
    test_size.multiply( 1./child_size.x, 1. / child_size.y, 1. / child_size.z );
  }
}

bool RefinerGridCheck::refine_parameters_ok(BoxTree*bt, Grid *g, Index child_size, Point upper_size)
{
  Point min_upper_size;
  minimum_upper_size(bt,g,child_size,min_upper_size);
  if ( !(upper_size >= min_upper_size) )
  {
    std::cout << "WARNING: refinement may result in boxes smaller than the surface grid" << std::endl;
    return false;
  }
  return true;
}

bool RefinerVariableNearSurface::refine_condition(BoxTreeNode *b)
{
  // simple grading
  double x = b->min_x();
  double y = b->min_y();
  double dx = _bt->get_domain().max_x();
  double dy = _bt->get_domain().max_y();
  
//  double size_scale = 1.5 * (0.2 + ( x + 2. * y ) / ( dx + 2. * dy ));
  //  double size_scale = 1.5 * (0.2 + ( (dx-x) + 2. * y ) / ( dx + 2. * dy ));
//  double size_scale = 1.5 * (0.2 + ( x + 2. * (dy-y) ) / ( dx + 2. * dy ));

  //  old acousticsurface, too small in corner
  //  double size_scale = 2. * (0.2 + ( x + 2. * y ) / ( dx + 2. * dy ));
  
  // about 1 to 4 variation from one corner to the other
//  double size_scale = max_size_factor * (min_size_factor + ( x + y_factor * y ) / ( dx + y_factor * dy ));
  double size_scale = (max_size_factor - min_size_factor) * (( x + y_factor * y ) / ( dx + y_factor * dy )) + min_size_factor;
  size_scale *= size_scale;
  Point my_size( upper_size * size_scale  );
  //  std::cout << my_size.x << " " ;
  
  bool should_refine = ( overlaps_surface(b) ) && ( !(my_size > b->diagonal() ) );
  
  return should_refine;
}


void BoxSurfaceTool::surface_range( BoxTreeNode *b, double &zmin, double &zmax )
{
  const std::valarray<double> z =
  { _s->depth( b->min_x(), b->min_y() ),
    _s->depth( b->min_x(), b->max_y() ),
    _s->depth( b->max_x(), b->min_y() ),
    _s->depth( b->max_x(), b->max_y() ) };
  
  zmin = z.min();
  zmax = z.max();
}

bool BoxSurfaceTool::merge0_condition( BoxTreeNode *b, double zmin, double zmax )
{
  const double zclose = b->diagonal_z() * 0.25;
  const bool merge0 = Boxmath::intervals_overlap( zmin, zmax, b->min_z() - zclose, b->min_z() + zclose );
  return merge0;
}

bool BoxSurfaceTool::merge5_condition( BoxTreeNode *b, double zmin, double zmax )
{
  const double zclose = b->diagonal_z() * 0.25;
  const bool merge5 = Boxmath::intervals_overlap( zmin, zmax, b->max_z() - zclose, b->max_z() + zclose );
  return merge5;
}

// merge face 0?
bool BoxSurfaceTool::will_merge0( BoxTreeNode *b )
{
  double zmin, zmax; // surface max and min
  surface_range(b, zmin, zmax);
  return merge0_condition(b, zmin, zmax);
}

// merge face 5?
bool BoxSurfaceTool::will_merge5( BoxTreeNode *b )
{
  double zmin, zmax; // surface max and min
  surface_range(b, zmin, zmax);
  return merge5_condition(b, zmin, zmax);
}

void BoxSurfaceTool::will_merge( BoxTreeNode *b, bool &m0, BoxTreeNode* &n0, bool &m5, BoxTreeNode* &n5 )
{
  double zmin, zmax; // surface max and min
  surface_range(b, zmin, zmax);
  
  m0 = merge0_condition(b, zmin, zmax);
  m5 = merge5_condition(b, zmin, zmax);

  n0 = 0;
  n5 = 0;
  
  // merge 0, down
  get_smallest_merge_neighbor_zm(b,n0);

  // merge 5, up
  get_smallest_merge_neighbor_zp(b,n5);
}

void BoxSurfaceTool::get_smallest_merge_neighbor_zm(BoxTreeNode *b, BoxTreeNode* &n0 )
{
  n0 = b->get_neighbor_zm();
  // keep going down if n0 does not get smaller in xy directions
  while ( n0 && n0->get_child_size().x == 1 && n0->get_child_size().y == 1 )
    n0 = n0->get_child( Index(0,0, n0->get_child_size().z-1) );
}

void BoxSurfaceTool::get_smallest_merge_neighbor_zp(BoxTreeNode *b, BoxTreeNode* &n5 )
{
  n5 = b->get_neighbor_zp();
  while ( n5 && n5->get_child_size().x == 1 && n5->get_child_size().y == 1 )
    n5 = n5->get_child( Index(0,0,0) );
}

bool BoxSurfaceTool::will_merge( BoxTreeNode *b, BoxTreeNode *&n, int &f )
{
  double zmin, zmax; // surface max and min
  surface_range(b, zmin, zmax);
  
  bool m0 = merge0_condition(b, zmin, zmax);
  bool m5 = merge5_condition(b, zmin, zmax);

  // which side is closer?
  if (m0 && m5)
  {
    if (b->min_z() - zmin > zmax - b->max_z())
      m0 = false;
    else
      m5 = false;
  }
  
  // merge 0, down
  if (m0)
  {
    f = 0;
    get_smallest_merge_neighbor_zm(b, n);
    return true;
  }
  // merge 5, up
  else if (m5)
  {
    f = 5;
    get_smallest_merge_neighbor_zp(b, n);
    return true;
  }
  n = 0;
  f = -1;
  return false;
}

// Rules for horizontal surfaces
// Parameters 1 are conditions to enforce for all boxes,
// 2 are additional conditions for cut boxes
// Mark "merge faces" and enforce "merge face adjacent" boxes are the same size.

// Enforce the complicated sub-face condition for corners of merge boxes.

//  // identify cut boxes
//  BTILeaf bti( _bt );
//  for ( BoxTreeNode *b = bti.get(); b != 0; b = bti.next() )
//  {
//
//
//  }

// BalanceFunction
bool BalancerXYSurface::balance_condition( BoxTreeNode *b, std::vector<BoxTreeNode*> &neighbors_to_split )
{
  // only split boxes that are z neighbors, in xy direction
  //   z-neighbor across merge face must be same size
  //   z-neighbor across other z-face must be at most 2x bigger

  assert(0); // untested. Remove this when we're ready to use it and test it
  
  assert( b->is_leaf() );

  //already satisfied: smaller xy-neighbors must not merge away one of my corners I keep
  size_t old_size = neighbors_to_split.size();
  
  BoxTreeNode *zn(0);
  int f(-1);
  const bool mergez = will_merge(b, zn, f); // use 0
  if ( mergez )
  {
    // no merge neighbor, split b itself
    if (!zn)
      neighbors_to_split.push_back(b);
    else
    {
      // merge neighbor must be same size.
      // split this or neighbor if not
      // zneighbor bigger?
      if ( bigger_xy(b,zn) )
      {
        neighbors_to_split.push_back(b);
      }
      else if ( bigger_xy(zn,b) )
      {
        neighbors_to_split.push_back(zn);
      }
      
      // other z-neighbor at most 2x bigger
      // but these can be split 2x2x2, not 2x2x1 zzyk todo
      BoxTreeNode *znn = b->get_neighbor( Box::opposite_face(f) );
      if (znn && znn->is_leaf() && ( bigger2_xy(znn,b) ) )
        neighbors_to_split.push_back(znn);
      
      // ensure shared faces are subsets of the larger box's face:
      // A *larger* neighbor must not keep a corner I'm going to merge away. A smaller neighbor can.
      // Also, normal balance condition of face neighbors not being more than 2x larger
      for (int ff = 1; ff < 5; ++ff)
      {
        BoxTreeNode *n = b->get_neighbor(ff);
        if ( !n || !n->is_leaf() ) continue;
        
        // more than 2x larger?
        if ( bigger2_xy(n,b) )
        {
          neighbors_to_split.push_back(n);
        }
        // merge away b's corner?
        else if ( bigger_xy(n,b) )
        {
          // which face of b is being merged away?
          if ( f == 0 ) // merge lower face
          {
            // b's merge corner is a corner of n?
            if ( b->min_z() - n->min_z() < 1e-2 * (b->diagonal_z()) )
              neighbors_to_split.push_back(n);
          }
          else
          {
            assert( f == 5 ); // merge upper face
            // b's merge corner is a corner of n?
            if ( b->max_z() - n->max_z() < 1e-2 * (b->diagonal_z()) )
              neighbors_to_split.push_back(n);
          }
        }
      }
    }
  }
  
  return neighbors_to_split.size() > old_size;
}

// BalanceFunction
bool BalancerSurface::balance_condition( BoxTreeNode *b, std::vector<BoxTreeNode*> &neighbors_to_split )
{
  assert( b->is_leaf() );

  // search for a hex?
// #define SEARCH_FOR_HEX
  
#ifdef SEARCH_FOR_HEX
  // point near center of hex
  Point p(9.375, 75.0625, 37.5);
  if (b->center_close(p))
  {
    std::cout << "found b 20" << std::endl;
  }
  size_t sz0( neighbors_to_split.size() );
  size_t s;
#endif
  
  // if b does not merge with anybody
  //  return balance_face_neighbors
  // else
  //   z-neighbor across merge face must be same size
  //   z-neighbor across other z-face must be at most 2x bigger
  //   bigger xyz-neighbors must not keep a corner I will merge away
  //   this is checked when looking at the smaller xy-neighbors
  //     ( smaller xy-neighbors must not merge away one of my corners I keep )
  
  size_t old_size = neighbors_to_split.size();
  
  bool split_b = false;
  
  bool m0, m5;
  BoxTreeNode *z0, *z5;
  will_merge(b, m0, z0, m5, z5);  // use 1

  // no merge neighbor, split b itself
  if ( (m0 && !z0)  ||  (m5 && !z5) )
  {
    split_b = true;
  }

#ifdef SEARCH_FOR_HEX
  for (s = sz0; s < neighbors_to_split.size(); ++s)
  {
    BoxTreeNode *n = neighbors_to_split[s];
    if (n->center_close(p))
      std::cout << "found n" << std::endl;
  }
  sz0 = neighbors_to_split.size();
#endif
  
  if (m0 || m5)
  {
    // up/down directions
    // 2x size at most
    // 1x size at most if merging
    if (m0)
    {
      // merge neighbor must be same size
      if (z0)
      {
        // b bigger than z0
        if (bigger_xy(b,z0))
        {
          split_b = true;
        }
        // z0 bigger than b
        else if (bigger_xy(z0,b) && z0->is_leaf())
        {
          neighbors_to_split.push_back(z0);
        }
      }
      // other neighbor must be at most twice as big
      // find other neighbor, even if we're not merging with it
      if (!z5)
        z5 = b->get_neighbor_zp();
      if (z5 && z5->is_leaf() )
      {
        if (bigger2_xy(z5,b))
        {
          neighbors_to_split.push_back(z5);
        }
        // I can't tell if b is 2x bigger without descending the tree farther.
        // so just defer the decision until the neighbors look for b
      }
    }
    else if (m5)
    {
      // merge neighbor must be same size
      if (z5)
      {
        // b bigger than z0
        if (bigger_xy(b,z5))
        {
          split_b = true;
        }
        // z0 bigger than b
        else if (bigger_xy(z5,b) && z5->is_leaf())
        {
          neighbors_to_split.push_back(z5);
        }
      }
      // other neighbor must be at most twice as big
      // find other neighbor, even if we're not merging with it
      if (!z0)
        z0 = b->get_neighbor_zm();
      if (z0 && z0->is_leaf() )
      {
        if (bigger2_xy(z0,b))
        {
          neighbors_to_split.push_back(z0);
        }
        // I can't tell if b is 2x bigger without descending the tree farther.
        // so just defer the decision until the neighbors look for b
      }
    }
    if (split_b)
      neighbors_to_split.push_back(b);

    // xy neighbors
    // ensure shared side faces are subsets of the larger box's face:
    // A *larger* neighbor must not keep a corner I'm going to merge away. A smaller neighbor can.
    // Also, normal balance condition of face neighbors not being more than 2x larger
    for (int ff = 1; ff < 5; ++ff)
    {
      BoxTreeNode *n = b->get_neighbor(ff);
      if ( !n || !n->is_leaf() ) continue;
      
      // if n is more than 2x larger than b, split n
      bool split_n = false;
      if ( n->diagonal_z() > 2.1 * b->diagonal_z() )
      {
        split_n = true;
      }
      // rule: b can't merge away a corner if it is a non-merged corner of a bigger neighbor
      // check if n is strictly bigger than b
      else if ( n->diagonal_z() > 1.1 * b->diagonal_z() )
      {
        // which face of b is being merged away?
        // b's merge corner is that corner of n?
        // n is going to keep that corner, without merging it?
        // if all are true, then split n

        // if b and n share a corner that b is merging away (as opposed to a hanging node)
        if ( ( m0 && ( fabs(b->min_z() - n->min_z()) < 1e-2 * (b->diagonal_z()) ) ) ||  // merge and share small-coordinate corner
             ( m5 && ( fabs(b->max_z() - n->max_z()) < 1e-2 * (b->diagonal_z()) ) )  )  // merge and share big-coordinate   corner
        {

          // Will neighbor keep this corner? Check its merge status to find out.
          bool nm0, nm5;
          BoxTreeNode *nz0, *nz5;
          will_merge(n, nm0, nz0, nm5, nz5); // use 1A
          // neighbor *wants* to merge if nm0 is true, but it will only actually merge in the present state if all of the subsequent conditions are true, too.
          nm0 = nm0 && nz0 && nz0->is_leaf();
          nm5 = nm5 && nz5 && nz5->is_leaf();
          if ( (m0 && !nm0) || (m5 && !nm5) )
            split_n = true;
        }
      }
      if (split_n)
      {
        assert( n->is_leaf() );
        neighbors_to_split.push_back(n);
#ifdef SEARCH_FOR_HEX
        if (n->center_close(p))
          std::cout << "found n" << std::endl;
        sz0 = neighbors_to_split.size();
#endif
      }
    }
  }

  if ( !m0 && !m5 )
  {
    // non-merging box
    // ordinary balance condition
    BalancerFace::balance_condition(b, neighbors_to_split);
    
#ifdef SEARCH_FOR_HEX
    for (s = sz0; s < neighbors_to_split.size(); ++s)
    {
      BoxTreeNode *n = neighbors_to_split[s];
      if (n->center_close(p))
        std::cout << "found n" << std::endl;
    }
    sz0 = neighbors_to_split.size();
#endif
    
  }
  
  return neighbors_to_split.size() > old_size;
}


void BoxSurfaceTool::merge_boxes( BoxTreeNode *b, BoxTreeNode *n, int f)
{
  assert( b );
  assert( b->is_leaf() );
  assert( !b->is_warped() );
  assert( n );
  assert( n->is_leaf() );
  assert( !n->is_warped() );
  
  // coordinates
  double z[4];
  depth_box( b, z );
  
  b->set_warped(f, z);
  
  n->set_warped(BoxTreeNode::opposite_face(f), z);
}



void BoxSurfaceTool::cut_and_collect_merges()
{
  const Index splitz(1,1,2);
  const Index child_lower_index(0,0,0);
  const Index child_upper_index(0,0,1);
  
  // two passes, to try to center the merges better

  // pass 0 : two-sided merges and cuts
  {
    BTILeaf bti( _bt );
    size_t hex_id = 0; // debug, starting numbering as in cubit
    for ( BoxTreeNode *b = bti.get(); b != 0; b = bti.next() )
    {
      // debug
      ++hex_id; // first hex is 1, just as in cubit
//      if (hex_id==6 || hex_id==13)
//      {
//        std::cout << "hex " << hex_id << " found. " << std::endl;
//      }
      
      // skip if already handled by its neighbor
      if (b->is_warped())
        continue;

      // double merge
      bool m0, m5;
      BoxTreeNode *n0, *n5;
      will_merge(b, m0, n0, m5, n5);
      
      int f=-1;
      BoxTreeNode *n=0;
      bool is_merge = false;
      
      // double merge
      if (m0 && m5 && n0 && n5)
      {
        is_merge = true;

        // mark this hex as being squished and having no output
        b->output_hex(false);
        b->squished_hex(true);
        // tell its two neighbors n0 and n5 to merge
        b = n0;
        f = 5; // not 0. n0 shares face 5 with the original b
        n = n5;

        --hex_id; // debug
      }
      
      // cut?
      if ( !m0 && !m5 )
      {
        double zmin, zmax;
        surface_range(b, zmin, zmax);
        const bool cut = Boxmath::intervals_overlap(zmin, zmax, b->corner_min().z, b->corner_max().z);
        if (cut)
        {
          // split then merge the two children
          b->create_children(splitz);
          ++hex_id;
          
          // force two children to merge, even though the cut may be still near the middle of one of the children
          is_merge = true;
          n = b->get_child( child_upper_index );
          b = b->get_child( child_lower_index );
          f = 5;
        }
      }
      
      if (is_merge)
        merge_boxes( b, n, f);
      
    } // bti
  } // pass 0
  
  // pass 1, one-sided merges
  {
    
    BTIOutput bti( _bt );
    size_t hex_id = 0; // debug, starting numbering as in cubit
    for ( BoxTreeNode *b = bti.get(); b != 0; b = bti.next() )
    {
      // debug
      ++hex_id; // first hex is 1, just as in cubit
//      if (hex_id==6 || hex_id==13)
//      {
//        std::cout << "hex " << hex_id << " found. " << std::endl;
//      }
      
      // skip if already handled, by the prior pass or a neighbor
      if (b->is_warped())
        continue;
      
      // get the closer merge, if any
      BoxTreeNode *n;
      int f;
      bool is_merge = will_merge(b, n, f); // use 2 - cut and collect
      
      // additional checks, for the case that the neighbor has multiple merges possible.
      if (!n || n->is_warped() || !n->output_hex() )
        is_merge = false;
      if ( is_merge )
      {
        // is n's merge neighbor b?
        BoxTreeNode *bb;
        int ff;
        bool reciprocates = will_merge(n,bb,ff); // use 2A
        // if n is not a leaf, then there exists a smaller neighbor, probably cut by the surface, so don't warp my face either
        is_merge = reciprocates && bb==b && ff==Box::opposite_face(f) && n->is_leaf() && !n->is_warped();
        //        std::cout << " ff:" << ff << " f:" << f << " n->warped:" << n->is_warped() << " n->leaf:" << n->is_leaf() << " b:" << b << " bb:" << bb << std::endl;
        }

      if (is_merge)
        merge_boxes( b, n, f);
      
    } // bti
  } // pass 1
  
  // micro-adjust midnodes to be linear between long edges for face conformality
  {
    // vector of face neighbors
    std::vector<BoxTreeNode*> nbh;
    
    BTIOutput bti( _bt );
    for ( BoxTreeNode *b = bti.get(); b != 0; b = bti.next() )
    {
      // iterate over neighbors
      for ( int f = 1; f < 5; ++f )
      {
        const int ff = Box::opposite_face(f);
        nbh.clear();
        b->find_mesh_neighbors(f, nbh);
        for (size_t n = 0; n < nbh.size(); ++n)
        {
          BoxTreeNode *bb = nbh[n];
          if (bb->output_hex())
          {
            // face nodes
            Point bfn[4], bbfn[4];
            b ->face_nodes( f,  bfn );
            bb->face_nodes(ff, bbfn );

            double tol = 0.1 * std::min( b->diagonal_z(), bb->diagonal_z() );
            double tol2 = tol * tol;
            
            bool b_smaller = ( b->diagonal_x() + b->diagonal_y() < bb->diagonal_x() + bb->diagonal_y() );
            

            // for the top edge and the bottom edge
            // bottom edge is always face nodes 0,1
            int n0=0;
            int n1=1;

            for (int p = 0; p < 2; ++p )
            {
              // points line up
              Point * b0 = & bfn[n0];
              Point * b1 = & bfn[n1];
              Point *bb0 = &bbfn[n0];
              Point *bb1 = &bbfn[n1];
              
              Point mid = b_smaller ? (*bb0 + *bb1) * 0.5 : (*b0 + *b1) * 0.5;
              
              // check if snap is needed
              const bool same0 = b0->is_close(*bb0, tol2);
              const bool same1 = b1->is_close(*bb1, tol2);
              if ( same0 && !same1 )
              {
                if (b_smaller)
                {
                  // *b1 = mid
                  b->update_node( WarpedFace::face_i_lookup[f][n1], mid );
                }
                else
                {
                  // *bb1 = mid
                  bb->update_node( WarpedFace::face_i_lookup[ff][n1], mid );
                }
              }
              else if ( same1 && !same0 )
              {
                if (b_smaller)
                {
                  // *b0 = mid;
                  b->update_node( WarpedFace::face_i_lookup[f][n0], mid );
                }
                else
                {
                  // *bb0 = mid;
                  bb->update_node( WarpedFace::face_i_lookup[ff][n0], mid );
                }
              }
              
              // iterate
              // top edge is always face nodes 2,3
              n0=2;
              n1=3;
            }
          }
        }
      }
    }
  }
}


// finalize the mesh node positions, merging faces and adding cut nodes for cut boxes.
void BoxSurfaceTool::mesh_boxes()
{
  cut_and_collect_merges();
  assign_global_ids();
}


// unused
//bool BoxSurfaceTool::surface_interaction( BoxTreeNode *b1, bs_interaction &bsi1, BoxTreeNode *&b2, bs_interaction &bsi2 )
//{
//  b2 = 0;
//  bsi2 = NOTHING;
//  bsi1 = NOTHING;
//
//  // consistency is KING!!!
//
//  // start with box containing surface at box xy-center, and determine *its* status first
//  // find box containing surface at its x-y center: always start with reference to that one
//  Point c( b1->center_x(), b1->center_y(), 0.);
//  c.z = _s->depth( c.x, c.y );
//  BoxTreeNode *b = b1->find_box( c );
//  bs_interaction bsi = NOTHING;
//
//  double zmin, zmax;
//  surface_range(b, zmin, zmax);
//  const double middle_max = 0.75 * b->max_z() + 0.25 * b->min_z();
//  const double middle_min = 0.25 * b->max_z() + 0.75 * b->min_z();
//  
//  // in middle
//  if (zmin > middle_min && zmax < middle_max)
//  {
//    bsi = CUT;
//  }
//
//  // candidate to merge up or down?
//  else if (b->max_z() - zmax < zmin - b->min_z() )
//  {
//    bsi = UP;
//  }
//  else
//  {
//    bsi = DOWN;
//  }
//
//
//  // do this consistently
//  return true;
//}
//
