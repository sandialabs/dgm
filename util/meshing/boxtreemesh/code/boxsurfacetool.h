//
//  BoxSurfaceTool.h
//  BoxTreeMesh
//
//  Created by Mitchell, Scott A on 3/2/16.
//  Copyright (c) 2016 Sandia National Labs. All rights reserved.
//
//  Operations BoxTree operations driven by a surface
//  E.g. split boxes, move nodes to surface

#ifndef __BoxTreeMesh__BoxSurfaceTool__
#define __BoxTreeMesh__BoxSurfaceTool__

#include <stdio.h>
#include <map>

#include "surface.h"
#include "boxtreetool.h"

// some common things for all types of surfaces
class BSTool: public BoxTreeTool
{
public:
  BSTool(BoxTree *bt, Grid *g) :  BoxTreeTool(bt), _g(g) {}

  void set_domain_size(double z_min, double z_max);
  
  // write out files describing which boxes are above the surface, which are below
  virtual void write_box_zones( std::string fname_prefix ) {};

protected:
    // return the range of grid points that lie inside the box in x and y
    // that is, for ( x = xl; x < xh; ++x ) (x lies in box == true)
  void subgrid_range( const Box *b, size_t &xl, size_t &xh, size_t &yl, size_t &yh ) const;
  

  Grid *_g;
};

class BoxSurfaceTool: public BSTool
{
  
public:
  
  BoxSurfaceTool(BoxTree *bt, Surface *s) :  BSTool(bt,s), _s(s) {}

  //== high level interface ==  
  // refinement types.
  // "would" only returns whether the mesh would be changed, but does not actually change it

  // refine boxes until the surface has at most height_variation inside them, an absolute value,
  // and until the x and y coordinates are at most box_max.
  bool refine_near_surface();
  bool would_refine_near_surface();
  void set_refiner_near_surface( Refiner *refiner ) { _refiner_near_surface = refiner; }
  
  // Refine in xy (only) to limit surface variation within a box, for unambiguous merges.
  // Requiring variation < 1/4 of the box height is sufficient, but here we refine less than that
  bool refine_xy_to_reduce_surface_variation( Index xy_child_size );
  bool would_refine_xy_to_reduce_surface_variation();
  
  // Balance to enforce the condition that allows boxes to be merged
  bool balance_for_merging(const Index child_size = Index(2,2,2));
  bool would_balance_for_merging();

  bool balance_xy_for_merging();
  bool would_balance_xy_for_merging();

  // finalize the mesh node positions
  // boxes cut by the surface will be cut into two boxes
  // boxes with a merge face will have that face warped
  void mesh_boxes();

  // collect all boxes that will merge into merge_boxes
  // implied: merge b face 5 with its neighbor n face 0
  // split a cut box into two in z direction only, and collects one for merging.
  // thus we don't need to special case cut boxes later
  void cut_and_collect_merges();

  //== lower level routines useful for other tools ==

  // depth at box corners
  // z[i] refers to xy = { 00, 10, 11, 01 }
  void depth_box( BoxTreeNode *b, double z[4] );
  
  // true if the surface cuts through the box
  bool overlaps_surface( BoxTreeNode *b ) const;
  // true if center of box has a smaller z coordinate (less depth)
  // than the surface does at the box center's xy
  bool is_acoustic( BoxTreeNode *b ) const;
  // true if surface varies at least height_variation within the box
  // assumes the box overlaps the surface
  bool height_varies_at_least( BoxTreeNode *b, double height_variation );
  
  // true if any triangle of the xi yi grid square overlaps the box
  bool overlaps_grid( BoxTreeNode *b, size_t xi, size_t yi ) const;
  // true if triangle p0, p1, p2 overlaps the box
  bool tri_box_overlap( BoxTreeNode *b, const Point &p0, const Point &p1, const Point &p2 ) const;
  
  // min and max surface depth at box's xy corners
  void surface_range( BoxTreeNode *b, double &zmin, double &zmax );

  void assign_box_acoustic_zone();

  
protected:
  
  bool refine_near_surface_implementation( bool actually_refine );

  bool refine_xy_to_reduce_surface_variation_implementation( Index xy_child_size, bool actually_change ); // unused untested

  bool balance_for_merging_implementation(bool actually_change, const Index child_size = Index(2,2,2) );
  bool balance_xy_for_merging_implementation(bool actually_change);

  
//  // new approach 27 May 2016
//  enum bs_interaction {DOWN, UP, CUT, BALANCE, NOTHING};
//  // given the four xy corners of box b, find the surface depth at the box corners, and determine its interaction status with the surface
//  // choices are:
//  //   0 - merge face 0 with face 5 of b2
//  //   5 - merge face 5 with face 0 of b2
//  // CUT - split box into two, merge along interface surface
//  // BALANCE - need to refine the box
//  // NOTHING - no interaction with the surface
//  bool surface_interaction( BoxTreeNode *b1, bs_interaction &bsi1, BoxTreeNode *&b2, bs_interaction &bsi2 );
//  
//  
  
  // return whether a merge across the surface will take place
  // note will_merge could be true and still have the neighbor 0, if box b is on domain boundary
  // m0 is true if b will merge its face 0 with face opposite_face(f) of neighbor n0
  // m5 is true if b will merge its face 5 with face opposite_face(f) of neighbor n5
  // because of proximity to the surface
  // There is no guarantee that the merge neighbor is actuall a leaf! If not, then the box b should be split.
  // A special case is if the merge neighbor is split in the z but not xy direction. In that case we return its correct leaf descendent.
  void will_merge( BoxTreeNode *b, bool &m0, BoxTreeNode* &n0, bool &m5, BoxTreeNode* &n5 );
  // if both m0 and m5 are true, return one of them prefered by the magnitude of surface variaton
  bool will_merge( BoxTreeNode *b, BoxTreeNode *&n, int &f );

  // true if surface range is close to box minimum, causing a merge with its face0 neighbor
  bool will_merge0( BoxTreeNode *b );
  bool merge0_condition( BoxTreeNode *b, double zmin, double zmax );

  // true if surface range is close to box maximum, causing a merge with its face5 neighbor
  bool will_merge5( BoxTreeNode *b );
  bool merge5_condition( BoxTreeNode *b, double zmin, double zmax );

  // find the neighbor deepest in the tree that still has the same xy-size face as me. Only descends when it is not split in x or y directions
  void get_smallest_merge_neighbor_zm(BoxTreeNode *b, BoxTreeNode* &n0 );
  void get_smallest_merge_neighbor_zp(BoxTreeNode *b, BoxTreeNode* &n5 );
  
  // merge the two specified boxes
  void merge_boxes( BoxTreeNode *b, BoxTreeNode *n, int f);

private:
  // used by height_varies_at_least
  bool update_min_max_depth( double q, double height_variation, double &z_min, double &z_max) const;

protected:
  
  // data
  // BoxTree *_bt; // inherited from BoxTreeTool
  Surface *_s;
  
  Refiner *_refiner_near_surface = 0;
  

};

// check that the refiner would never make a box smaller than the grid size
class RefinerGridCheck
{
public:
  RefinerGridCheck() {}
  void minimum_upper_size(BoxTree*bt, Grid *g, Index child_size, Point &min_upper_size);
  bool refine_parameters_ok(BoxTree*bt, Grid *g, Index child_size, Point upper_size);
};

class RefinerXYSurfaceVariation : public Refiner, protected BoxSurfaceTool
{
public:
  RefinerXYSurfaceVariation(BoxTree *bt, Surface *s) : Refiner(bt), BoxSurfaceTool(bt,s) { child_size.z = 1; }
protected:
  virtual bool refine_condition(BoxTreeNode *b);
};

class RefinerNearSurface : public Refiner, protected BoxSurfaceTool
{
public:
  RefinerNearSurface(BoxTree *bt, Surface *s) : Refiner(bt), BoxSurfaceTool(bt,s) {}
  
  // refine if a box if it overlaps (is cut by) the surface, and
  // at least one of these conditions are met:
  
  // refine a box if its diagonal is bigger than upper_size
  Point upper_size = Point(1000., 1000., 1000.);
  
  // refine a box if the surface varies more than height_variation within it
  // note height_variation is an absolute value, not relative to the box size
  double height_variation = 1000;
  
protected:
  virtual bool refine_condition(BoxTreeNode *b);
  virtual bool refine_parameters_ok()
  {
    RefinerGridCheck rgc;
    return rgc.refine_parameters_ok(_bt, _s, child_size, upper_size);
  }

};

// defines some sizing function over the xy space
class RefinerVariableNearSurface : public Refiner, protected BoxSurfaceTool
{
public:
  RefinerVariableNearSurface(BoxTree *bt, Surface *s) : Refiner(bt), BoxSurfaceTool(bt,s) {}

  // refine if a box if it overlaps (is cut by) the surface, and
  // at least one of these conditions are met:
  
  // refine a box if its diagonal is bigger than upper_size
  Point upper_size = Point(1000., 1000., 1000.);
  
  // refine a box if the surface varies more than height_variation within it
  // note height_variation is an absolute value, not relative to the box size
  double height_variation = 1000;
  
  double min_size_factor = 0.4; // factor of upper size in smallest corner
  double max_size_factor = 2.2; // factor of upper size in largest corner
  double y_factor = 2.; // varies twice as much in y direction than in x
  
protected:
  // defines some sizing function over the xy space
  virtual bool refine_condition(BoxTreeNode *b);
  virtual bool refine_parameters_ok()
  {
    RefinerGridCheck rgc;
    return rgc.refine_parameters_ok(_bt, _s, child_size, upper_size);
  }
};

class RefinerAcoustic : public Refiner, protected BoxSurfaceTool
{
public:
  RefinerAcoustic(BoxTree *bt, Surface *s) : Refiner(bt), BoxSurfaceTool(bt,s) {}
  
  // refine a box if its diagonal is not smaller than upper_size
  // and the box (center) is acoustic
  Point upper_size = Point(1000., 1000., 1000.);
  
protected:
  virtual bool refine_condition(BoxTreeNode *b)
  {
    // debug
//    if (is_acoustic(b) && (b->diagonal() < upper_size))
//    {
//      std::cout << "acoustic refiner stopping with box diagonal ";
//      b->diagonal().print();
//    }

    // refine it if it is not smaller than upper_size, and it is above the surface
    return !(b->diagonal() < upper_size) && is_acoustic(b);

  }

};


class BalancerSurface : public BalancerFace, protected BoxSurfaceTool
{
public:
  BalancerSurface(BoxTree *bt, Surface *s) : BalancerFace(bt), BoxSurfaceTool(bt,s) {}
private:
  // Enforce the complicated sub-face condition for corners of merge boxes.
  bool balance_condition( BoxTreeNode *b, std::vector<BoxTreeNode*> &q );
};

class BalancerXYSurface : public BalancerFace, protected BoxSurfaceTool
{
public:
  BalancerXYSurface(BoxTree *bt, Surface *s) : BalancerFace(bt), BoxSurfaceTool(bt,s)
  { child_size = Index(2,2,1); }
private:
  // Enforce the complicated sub-face condition for corners of merge boxes.
  bool balance_condition( BoxTreeNode *b, std::vector<BoxTreeNode*> &q );
};

////////////////  inline

inline
bool BoxSurfaceTool::balance_for_merging_implementation( bool actually_change, const Index child_size )
{
  BalancerSurface balancer( _bt, _s);
  balancer.child_size = child_size;
  return balancer.balance_implementation( actually_change );
}

inline
bool BoxSurfaceTool::balance_xy_for_merging_implementation( bool actually_change )
{
  BalancerXYSurface balancer( _bt, _s);
  return balancer.balance_implementation( actually_change );
}

inline
bool BoxSurfaceTool::refine_near_surface()
{
  return refine_near_surface_implementation(true);
}

inline
bool BoxSurfaceTool::would_refine_near_surface()
{
  if (!_refiner_near_surface)
    return false;
  
  Index I = _refiner_near_surface->child_size;
  _refiner_near_surface->child_size = Index(1,1,1);
  bool would_change = refine_near_surface_implementation(false);
  _refiner_near_surface->child_size = I;
  return would_change;
}

// Refine in xy (only) to limit surface variation within a box, for unambiguous merges.
// Requiring variation < 1/4 of the box height is sufficient, but here we refine less than that
inline
bool BoxSurfaceTool::refine_xy_to_reduce_surface_variation( Index xy_child_size )
{
  return refine_xy_to_reduce_surface_variation_implementation( xy_child_size, true );
}

inline
bool BoxSurfaceTool::would_refine_xy_to_reduce_surface_variation()
{
  return refine_xy_to_reduce_surface_variation_implementation( Index(1,1,1), false );
}

// Balance to enforce the condition that allows boxes to be merged
inline
bool BoxSurfaceTool::balance_for_merging(const Index child_size)
{
  return balance_for_merging_implementation(true,child_size);
}

inline
bool BoxSurfaceTool::would_balance_for_merging()
{
  return balance_for_merging_implementation(false);
}

// Balance to enforce the condition that allows boxes to be merged
inline
bool BoxSurfaceTool::balance_xy_for_merging()
{
  return balance_xy_for_merging_implementation(true);
}

inline
bool BoxSurfaceTool::would_balance_xy_for_merging()
{
  return balance_xy_for_merging_implementation(false);
}

inline
bool BoxSurfaceTool::is_acoustic( BoxTreeNode *b ) const
{
  Point bc( b->center() );          // box center
  double d = _s->depth(bc.x, bc.y); // surface depth
  return (d > bc.z);                // surface depth > box center
}

#endif /* defined(__BoxTreeMesh__BoxSurfaceTool__) */
