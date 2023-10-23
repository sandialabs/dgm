//
//  boxsurfaceinclusiontool.cpp
//  BoxTreeMesh
//
//  Created by Mitchell, Scott A on 5/3/16.
//  Copyright (c) 2016 Sandia National Labs. All rights reserved.
//

#include "boxsurfaceinclusiontool.h"

#include "TriangulationTool.h"
#include "windingnumber.h"

#include <algorithm>
#include <deque>
#include <cmath>
#include <ctgmath>

#include <fstream>
#include <cstdio>
#include <iomanip>

bool BoxSurfaceInclusionTool::refine_near_surface_implementation( double box_max, double height_variation, Index child_size, bool actually_refine )
{
 
  // refine boxes that are not smaller (in every coordinate) than this size
  //  Point upper_size( _s->grid_x() * grid_factor, _s->grid_y() * grid_factor, _bt->get_domain().diagonal_z() );
  Point upper_size( box_max, box_max, _bt->get_domain().diagonal_z() );

  // adjust size if needed
  if (actually_refine)
  {
    RefinerGridCheck rgc;
    Point min_upper_size;
    rgc.minimum_upper_size(_bt, _s, child_size, min_upper_size);
    min_upper_size.multiply(1.1);
    if ( upper_size.x < min_upper_size.x )
    {
      std::cout << "Adjusting minimum box refinement size.x from " << upper_size.x << " to " << min_upper_size.x << std::endl;
      upper_size.x = min_upper_size.x;
    }
    if ( upper_size.y < min_upper_size.y )
    {
      std::cout << "Adjusting minimum box refinement size.y from " << upper_size.y << " to " << min_upper_size.y << std::endl;
      upper_size.y = min_upper_size.y;
    }
    if ( upper_size.z < min_upper_size.z )
    {
      // silent, usually not an issue
      upper_size.z = min_upper_size.z;
    }
  }

  // uniform
  //  RefinerNearSurface refiner(_bt,_s);
  // denser in the corner
  RefinerVSS refiner(this);
  refiner.child_size = child_size;
  refiner.upper_size = upper_size;
  refiner.height_variation = height_variation;
  bool changed = refiner.refine_implementation(actually_refine);
  
  return changed;
}


bool RefinerVSS::refine_condition(BoxTreeNode *b)
{
  // simple grading
  /*
  const double x = b->corner_min().x;
  const double y = b->corner_min().y;
  const double z = b->corner_min().z;
  const double dx = _bst->_bt->get_domain().diagonal_x();
  const double dy = _bst->_bt->get_domain().diagonal_y();
  const double dz = _bst->_bt->get_domain().diagonal_z();
   */
  
//  double size_scale = 1.5 * (0.2 + ( x + 2. * y ) / ( dx + 2. * dy ));
  //  double size_scale = 1.5 * (0.2 + ( (dx-x) + 2. * y ) / ( dx + 2. * dy ));
  // double size_scale = 1.5 * (0.2 + ( x + 2. * (dy-y) ) / ( dx + 2. * dy )) * ( 1. + z / dz);
  // size_scale *= size_scale;
  double size_scale = 1.;
  Point my_size( upper_size * size_scale  );
  //  std::cout << my_size.x << " " ;
  
  // Box bb = b->dilate_box(_bst->_proximity);
  bool should_refine = ( !(my_size > b->diagonal()) && _bst->is_tet_box(b) );
  
  return should_refine;
}

bool BoxSurfaceInclusionTool::overlaps_surface_point(const Box *b ) const
{
  // subgrid inside box
  size_t xl, xh, yl, yh;
  subgrid_range(b, xl, xh, yl, yh);
  
  // debug
  if ( xl >= xh  || yl >= yh )
  {
    std::cout << "WARNING: empty range! box is too small compared to grid spacing to contain a surface point." << std::endl;
  }
  
  {
    // check if any surface point is inside the box
    // or some edge between two such points passes through the box
    for ( size_t xi = xl; xi < xh; ++xi)
    {
      for ( size_t yi = yl; yi < yh; ++yi )
      {
        for ( size_t si = 0; si < _s->num_surfs(); ++si)
        {
          const double q = _s->depth_ij(xi,yi,si);
          // surface point is inside the box
          if ( q <= b->corner_max().z && q >= b->corner_min().z )
            return true;
        }
      }
    }
  }
  return false;
}


// ============================================ classes for building a surface reconstruction

void BoxSurfaceInclusionTool::init_grid_nodes(AdvanceContext &ac)
{
  // agn
  ac.agn.reserve(_s->_surfs.size());
  for (size_t top_s=0; top_s < _s->_surfs.size(); ++top_s)
  {
    auto *gn = new GridNodes( *_s->_surfs[top_s] );
    ac.agn.push_back(gn);
  }
  // agn_saved
  ac.agn_saved.reserve(_s->_surfs.size());
  for (size_t top_s=0; top_s < _s->_surfs.size(); ++top_s)
  {
    auto *gn = new GridNodes( *_s->_surfs[top_s] );
    ac.agn_saved.push_back(gn);
  }

  // meshed
  ac.ameshed.reserve(_s->_surfs.size());
  for (size_t top_s=0; top_s < _s->_surfs.size(); ++top_s)
  {
    auto *gm = new GridMeshed( *_s->_surfs[top_s] );
    ac.ameshed.push_back(gm);
  }
  
  // flag nan and inf depths as if they were already meshed
  ac.ameshed.reserve(_s->_surfs.size());
  for (size_t s=0; s < _s->_surfs.size(); ++s)
  {
    GridMeshed *gm = ac.ameshed[s];
    Surface *surf = _s->_surfs[s];
    for (size_t i = 0; i < gm->grid_x_size(); ++i)
      for (size_t j = 0; j < gm->grid_y_size(); ++j)
      {
        const double z = surf->depth_ij(i,j);
        if ( !(isnormal(z) || (z==0.)) )
          set_previously_meshed(ac, s, i, j, true );
      }
  }
  
}


// ============================================ 
bool BoxSurfaceInclusionTool::find_flat_spot(AdvanceContext &ac, size_t top_s, size_t &flat_i, size_t &flat_j )
  // seed with a flat spot that isn't already triangulated
  // find the flattest spot
{
  const double flat_h_max = std::numeric_limits<double>::max();
  double flat_h = flat_h_max;
  double q00, q01, q11, q10, qc;
  for (size_t i = 0; i+1 < _s->grid_x_size(); ++i )
    for (size_t j = 0; j+1 < _s->grid_y_size(); ++j)
    {
      _s->_surfs[top_s]->grid_depth(i,j, q00, q01, q11, q10, qc);
      // no nan depths
      if ( isnormal(q00) && isnormal(q01) && isnormal(q11) && isnormal(q10) )
      {
        // check that there isn't any triangles containing those points already... 
        if (
          !previously_meshed(ac, top_s, i,   j  ) &&
          !previously_meshed(ac, top_s, i,   j+1) &&
          !previously_meshed(ac, top_s, i+1, j  ) &&
          !previously_meshed(ac, top_s, i+1, j+1)  )
        {
          // is this the flattest one? 
          // check the max difference between center and a corner
          double h = std::max( std::max( std::max( fabs(q00 - qc), fabs( q01 - qc) ), fabs(q11 - qc) ), fabs(q10 - qc) );
          if ( h < flat_h )
          {
            flat_h = h;
            flat_i = i;
            flat_j = j;
          }
        }
      }
    }
  return (flat_h < flat_h_max );
}

void BoxSurfaceInclusionTool::init_two_triangles( AdvanceContext &ac, size_t top_s, Triangulation *T, size_t flat_i, size_t flat_j, FrontEdges& front_edges)
{
  const size_t i = flat_i;
  const size_t j = flat_j;
  // Surface *ts = _s->_surfs[top_s];
  // double q00, q01, q11, q10, qc;
  // ts->grid_depth(i, j, q00, q01, q11, q10, qc);

  // GridNodes *grid_nodes = agn[top_s];
  Node *n00 = new_grid_node(ac.agn, T, top_s, i,   j  );
  Node *n01 = new_grid_node(ac.agn, T, top_s, i,   j+1);
  Node *n10 = new_grid_node(ac.agn, T, top_s, i+1, j  );
  Node *n11 = new_grid_node(ac.agn, T, top_s, i+1, j+1);

  // New triangles.
  // rhr right-hand-rule points up
  /* Triangle *t0 = */ T->new_triangle( n00, n10, n01 );
  /* Triangle *t1 = */ T->new_triangle( n11, n01, n10 );
  assert( T->_triangles.size() == 2);
  T->_horizontal_triangles = T->_triangles; // copy


    // put four edges on front
  FrontNode fn00(ac.agn, top_s, i,   j  );
  FrontNode fn01(ac.agn, top_s, i,   j+1);
  FrontNode fn10(ac.agn, top_s, i+1, j  );
  FrontNode fn11(ac.agn, top_s, i+1, j+1);
  assert( check_coordinates(ac.agn, fn00 ) );
  assert( check_coordinates(ac.agn, fn01 ) );
  assert( check_coordinates(ac.agn, fn10 ) );
  assert( check_coordinates(ac.agn, fn11 ) );
  push_back(ac, front_edges, FrontEdge( fn00, fn01, fn10 ) );
  push_back(ac, front_edges, FrontEdge( fn01, fn11, fn10 ) );
  push_back(ac, front_edges, FrontEdge( fn11, fn10, fn01 ) );
  push_back(ac, front_edges, FrontEdge( fn10, fn00, fn01 ) );
}

// crosswise overlap with some other extant triangle?
bool BoxSurfaceInclusionTool::other_cross( const BoxSurfaceInclusionTool::FrontNode & fn0, const BoxSurfaceInclusionTool::FrontNode & fn1, const BoxSurfaceInclusionTool::FrontNode & f)
{
  std::vector<Triangle*> tris;
  FrontEdge fe0f(fn0, f, FrontNode() );
  fe0f.triangles(tris);
  if ( !tris.empty() )
  {
    assert( tris.size() == 1 ); // else closed and caught earlier
    if ( fe0f.cross_triangles( *tris[0]->opposite_node(fe0f), *fn1._node ) )
      return true;
  }
  return false;
}

void BoxSurfaceInclusionTool::vet_candidates( AdvanceContext &ac, Triangle *t0, const FrontEdge &fe, const FrontNode &fn0, const FrontNode &fn1,
    BoxSurfaceInclusionTool::NodePool &np)
{
  Node *n2(0);
  bool t0_h(false), t0_v(false);
  if (t0)
  {
    assert( fe._fn_tri._si != -1 );
    n2 = fe._fn_tri._node;
    assert(n2);
    classify_triangle(fn0,fn1,fe._fn_tri, t0_h, t0_v);
  }

  // now check the candidates
  for (size_t i = 0; i < np.candidates.size(); ++i)
  {
    FrontNode &f = np.candidates[i];
    //==== index-only checks

    // beyond domain?
    if ( f.domain_boundary(_s) )
      continue;
    
    // already meshed by a prior triangulation?
    if ( previously_meshed(ac,f) )
      continue;

    // check vs. fn1 to see if would form a good triangle
    // same node, skip
    if ( f.same_front_node(fn1) || f.same_front_node(fn0) )
      continue;
    // too far away, skip
    // this also checks for colinear edges
    if ( !f.differs_at_most_one(fn1) && !_allow_far_index_triangles )
      continue;

    // update node of f based on its indices
    // refresh_node(*ac.agn, f); // may be null
    // fails if node coordinates is a nan
    if (!force_node(ac.agn, ac.T, f))  // meshes it if not meshed already
      continue;

    // skip nan or bad depth nodes
    if ( !isnormal(f._node->z) )
      continue;

    assert( check_coordinates(ac.agn, f) );
    Triangle t_can( fn0._node, fn1._node, f._node );

    // only one of t0 and t_can can be vertical, unless they connect the same indices
    if (t0_v && !_allow_far_index_triangles)
    {
      // is f_can horizontal or vertical?
      bool f_can_h, f_can_v;
      classify_triangle( fn0, fn1, f, f_can_h, f_can_v );
      if (f_can_v)
      {
        // make sure it spans the same vertical connection as t0
        if ( f._si != fe._fn_tri._si && f._si != fe._fn0._si && f._si != fe._fn1._si)
          // if ( f._si != fe._fn_tri._si )
          continue;
      }
    }
    
    // same as existing triangle?
    // cross existing triangle?
    // check the one triangle of fe
    if ( n2 && fe.cross_triangles( *n2, *f._node ) )
      continue;
    // the triangles of fn0-f and fn1-f are checked below

    if (f._node)
    {
      std::vector<Triangle*> &trisf = f._node->_triangles;
      bool extant(false);
      for (size_t i = 0; i < trisf.size(); ++i)
      {
        Triangle *t = trisf[i];
        if (t_can.same_triangle(t))
        {
          extant = true;
          break;
        }
      }
      if (extant)
        continue;
    }
    
    // check cross
    // find triangle abc with c = f, and a = fn0 or fn1, and d the other fn
    // determine if t shares edge fn0-f or fn1-f
    // also check if either of these edges is already closed
    bool good = true;
    if (f._node)
    {
      std::vector<Triangle*> &trisf = f._node->_triangles;
      
      bool cross(false);
      int num_0f(0);
      int num_1f(0);
      std::vector<Node*> star_nodes;
      star_nodes.reserve(trisf.size()*2);
      for (size_t i = 0; i < trisf.size(); ++i)
      {
        Triangle *t = trisf[i];
        Node *a=0;
        Node *b=0;
        Node *c=f._node;
        Node *d=0;
        for (size_t j = 0; j<3; ++j)
        {
          if (t->_nodes[j] == f._node)
          {
            size_t jp = (j+1) % 3;
            size_t jm = (j+2) % 3;
            if (fn0._node == t->_nodes[jp])
            {
              a = fn0._node;
              b = t->_nodes[jm];
              d = fn1._node;
              num_0f++;
            }
            else if (fn0._node == t->_nodes[jm])
            {
              a = fn0._node;
              b = t->_nodes[jp];
              d = fn1._node;
              num_0f++;
            }
            else if (fn1._node == t->_nodes[jp])
            {
              a = fn1._node;
              b = t->_nodes[jm];
              d = fn0._node;
              num_1f++;
            }
            else if (fn1._node == t->_nodes[jm])
            {
              a = fn1._node;
              b = t->_nodes[jp];
              d = fn0._node;
              num_1f++;
            }
            
            // collect edges of f
            star_nodes.push_back( t->_nodes[jm] );
            star_nodes.push_back( t->_nodes[jp] );
            
            break;
          }
        }
        if (a)
        {
          assert(b);
          if ( FrontEdge::cross_triangles(*a,*c,*d,*b) )
          {
            cross = true;
            break;
          }
        }
        
      }
      if (cross)
        continue;

      // pretend there is a triangle on the other side of the domain boundary, for checking closed
      const int num_0fbdy = (FrontEdge(fn0,f,FrontNode()).domain_boundary(_s) ? 1 : 0);
      const int num_1fbdy = (FrontEdge(fn1,f,FrontNode()).domain_boundary(_s) ? 1 : 0);
      
      // disallow forming a tri-valent edge
      // each of these will get one extra triangle, so it is OK if one or both of them are 0 or 1
      if ( (num_0f + num_0fbdy) > 1 || (num_1f + num_1fbdy) > 1)
        continue;
      
      // is f neighborhood a closed disk already?
      //    if ( f._node && f._node->closed()) // slow
      //      continue;
      if (!star_nodes.empty())
      {
        std::sort( star_nodes.begin(), star_nodes.end() );
        // closed if every node is there twice, or once and on the domain boundary
        bool closed = true;
        for ( size_t i = 0; i < star_nodes.size(); ++i)
        {
          // if node appears twice, then we found a closed spot
          if ( (i+1 < star_nodes.size()) && star_nodes[i] == star_nodes[i+1] )
          {
            ++i;
          }
          // node appears once. it is still closed if the edge is on the domain boundary
          else
          {
            if ( !Edge(f._node, star_nodes[i]).domain_boundary(_s) )
            {
              closed = false;
              break;
            }
          }
        }
        if (closed)
          continue;
      }
      
      // would something other than a half-disk or disk form by adding the triangle?
      if (!trisf.empty())
      {
        // assume existing tris are a half-disk
        // new triangle should share at least one edge with it to be good
        // the virtual boundary triangles don't count as being connected...
        if (num_0f == 0 && num_1f == 0 && !_allow_far_index_triangles)
          good = false;
      }
    }
    
    // weird advances from diagonal edges are valid, but not good
    // these result in skew triangles, not vertical and not horizontal
//    if ( fe.num_indices_different(f) > 2 )
//      good = false;
    
    if ( good || _allow_far_index_triangles )
      np.good.push_back(f);    
    else 
      np.valid.push_back(f);
  }
}


void BoxSurfaceInclusionTool::candidate_nodes(AdvanceContext &ac, Triangle *t0, const BoxSurfaceInclusionTool::FrontEdge &fe,
  BoxSurfaceInclusionTool::NodePool &np)
{
  np.good.clear();
  np.valid.clear();
  std::vector<FrontNode> &ns = np.candidates; // shorthand
  for ( size_t i = 0; i < 2; ++i)
  {
    ns.clear();
    const FrontNode &fn0 = fe.front_node(i);
    const FrontNode &fn1 = fe.front_node(1-i);

    
    if (_allow_far_index_triangles)
    {
      int min_i = std::max( 1, ((int) std::min( fn0._i, fn1._i)) - 2);
      int max_i = std::min( (int) _s->grid_x_size() - 1, ((int) std::max( fn0._i, fn1._i)) + 2);
      int min_j = std::max( 1, ((int) std::min( fn0._j, fn1._j)) - 2);
      int max_j = std::min( (int) _s->grid_y_size() - 1, ((int) std::max( fn0._j, fn1._j)) + 2);
      
      for (size_t s = 0; s < _s->_surfs.size(); s++)
        for (int i = min_i; i < max_i; ++i)
          for (int j = min_j; j < max_j; ++j)
          {
            ns.push_back( FrontNode(ac.agn, s, i, j) );
          }
    }
    else
    {
      // the plus and minus i,j ones
      // allow +2k and -2k in _si directions at the same time as +/- 1 in ij
      for (size_t s = fn0._si % 2; s < _s->_surfs.size(); s += 2)
      {
        FrontNode fcan = fn0;
        fcan._node = 0;
        fcan._si = s;
        fcan._i = fn0._i + 1;
        ns.push_back(fcan);
        fcan._i = fn0._i - 1;
        ns.push_back(fcan);
        fcan._i = fn0._i;
        fcan._j = fn0._j + 1;
        ns.push_back(fcan);
        fcan._j = fn0._j - 1;
        ns.push_back(fcan);
      }
      
      // true vertical
      // the plus and minus k ones
      {
        FrontNode fcan = fn0;
        fcan._node = 0;
        fcan._si = fn0._si + 1;
        if ( fcan._si < _s->_surfs.size() )
          ns.push_back(fcan);
        if ( fn0._si > 0 )
        {
          fcan._si = fn0._si - 1;
          np.candidates.push_back(fcan);
        }
      }
    }

    vet_candidates(ac, t0, fe, fn0, fn1, np );

  }
}

BoxSurfaceInclusionTool::FrontNode
BoxSurfaceInclusionTool::best_node(AdvanceContext &ac, Triangle *t0, const FrontEdge &fe, NodePool &np, bool &best_not_good, bool &best_too_long, bool recurse)
{
  // debug
  //=================
  if (_verbose)
  {
    std::cout << "\nfinding best node to advance from";
    fe.print();
    std::cout << "\nof triangle\n";
    fe._fn0.print();
    fe._fn1.print();
    fe._fn_tri.print();
  }

  const bool debug_quality = true;
  double best_cos_normals(0.), best_cos_big_angle(0.), best_l(0.), best_L(0.), best_h(0.);
  
  // sanity checks
  assert(t0);
  assert(fe._fn0._node == t0->_nodes[0] || fe._fn0._node == t0->_nodes[1] || fe._fn0._node == t0->_nodes[2]);
  assert(fe._fn1._node == t0->_nodes[0] || fe._fn1._node == t0->_nodes[1] || fe._fn1._node == t0->_nodes[2]);
  assert(fe._fn0._node != fe._fn1._node);
  assert( !np.empty() );
  
  size_t best_i = 0;
  size_t best_pp = 0;
  double best_value = std::numeric_limits<double>::max();
  
  // find normal to plane of triangle, make sure we get the right orientation!
  Point n;
  {
    // edge vectors
    // shorthand to triangle nodes
    const Point &pt = *fe._fn_tri._node;
    const Point &p0 = *fe._fn0._node;
    const Point &p1 = *fe._fn1._node;
    
    const Point vt0 = pt - p0;
    const Point v10 = p1 - p0;
    const Point vt1 = pt - p1;
    
    // compute normal two ways, take bigger one. Avoids some small-angle numerics.
    Point n0 = vt0.cross(v10);
    Point n1 = vt1.cross(v10); // == -v10.cross(vt1);
    
    const double ln0_2 = n0.length2();
    const double ln1_2 = n1.length2();
    
    if ( ln0_2 > ln1_2 )
      n = n0;
    else
      n = n1;

    n.normalize();
  }
  const Point w01 = *fe._n1 - *fe._n0;
  Point w01n = w01; w01n.normalize();

  const double min_l = std::max( _s->grid_x(), _s->grid_y() );
  
  // debug
  //=================
  if (_verbose)
  {
    std::cout <<" normal: ";
    n.print();
    std::cout << std::endl;
  }
  //=================
  
  for (size_t pp = 0; pp < 2; ++pp)
  {
    std::vector<FrontNode> &pool = (pp == 0 ? np.good : np.valid );
    if (_verbose)
      std::cout << "Evaluating " << (pp == 0 ? "good" : "valid" ) << " candidate nodes." << std::endl;
    
    for (size_t i = 0; i < pool.size(); ++i)
    {
      FrontNode &f = pool[i];
      // find distance from f to the plane of t0

      // Compute Quality Measures
      // height of candidate above the plane of t0
      // double h;
      // min and max length edges, for the two *new* edges of the triangle
      // double l,L;
      // cosine of largest angle of the new triangle
      // const double cos_big_angle
      // cosine of the angle between the normals of the candidate triangle and t0
      // const double cos_normals = fabs(n.dot(wn));
      //
      // penalize big triangle angles
      // penalize changing triangle normals
      // penalize long edges
      
      // h
      const Point pf = grid_point(f);
      const Point v0f = pf - *fe._fn0._node;
      const double h = fabs( n.dot( v0f ) ); // this is height above the plane of the triangle
      
      // l L
      const Point wf0 = *fe._n0 - pf;
      const Point wf1 = *fe._n1 - pf;
      const double l0 = wf0.length();
      const double l1 = wf1.length();
      // don't favor edges shorter than the max x or y grid spacing, as that just introduces an orientation bias
      const double l = std::max( std::min( l0, l1 ), min_l );
      const double L = std::max( l0, l1 );

      // cos_big_angle
      Point wf0n = wf0; wf0n.normalize();
      Point wf1n = wf1; wf1n.normalize();
      const double cos_f =  wf0n.dot(wf1n);
      const double cos_0 = -w01n.dot(wf0n);
      const double cos_1 =  w01n.dot(wf1n);
      const double cos_big_angle = std::min( std::min( cos_f, cos_0 ), cos_1);
      assert( cos_big_angle < 0.511 && cos_big_angle > -1.0001 );
      
      // cos_normals
      // wn = normal of new triangle
      Point wn = wf0.cross(wf1);
      wn.normalize();  // may be zero for colinear points 0 1 f, in which case cos_normals will be 0, the max penalty
      
      // const double cos_normals = fabs(n.dot(wn)); // ERROR! fabs encourages sharp dihedrals. we want flat ones. this was put in when I couldn't get the normals oriented right
      // 1 means coplanar and side by side, a flat surface; -1 means a sharp dihedral as in a cross triangle
      double cos_normals = n.dot(wn);
      assert( cos_normals > -1.0001 && cos_normals < 1.0001 );
      
      // cos_normals to triangles on other edges of candidate triangle, if any
      if ( f._node )
      {
        int num_normals(1); // average?
        // taking min has no effect, since the bad choices occur at creases
        // taking max ignores sharp ones...

        {
          const Edge e0 = Edge(f._node, fe._n0 );
          std::vector<Triangle*> tris0;
          e0.triangles(tris0);
          if (!tris0.empty())
          {
            const Triangle *t = tris0[0];
            const Node *p3 = t->opposite_node(e0);
            const Point u3f = pf - *p3;
            Point n0 = wf0.cross(u3f); // = u3f.cross(-wf0);
            n0.normalize();
            const double cos_normals0 = n0.dot(wn);
            // cos_normals = std::min( cos_normals, cos_normals0 );
            cos_normals += cos_normals0;
            num_normals++;
          }
        }
        
        {
          const Edge e0 = Edge(f._node, fe._n1 ); // different
          std::vector<Triangle*> tris0;
          e0.triangles(tris0);
          if (!tris0.empty())
          {
            const Triangle *t = tris0[0];
            const Node *p3 = t->opposite_node(e0);
            const Point u3f = pf - *p3;
            Point n0 = u3f.cross(wf1); // = -wf1.cross(u3f) = w1f.cross(u3f);  // different
            n0.normalize();
            const double cos_normals0 = n0.dot(wn);
            cos_normals = std::min( cos_normals, cos_normals0 );
            cos_normals += cos_normals0;
            num_normals++;
          }
        }
        
        cos_normals /= (double) (num_normals);

      }
      
      
      // consider angle between normals, value them staying the same
      
      // multiple angle_value by edge_value
      // double value = (1.6 - cos_normals - 1.2*cos_big_angle) * ( l + 0.2 * L + 0.3 * h );
      // double value = (1.8 - cos_normals - 1.2*cos_big_angle) * ( l + 0.5 * L + 0.3 * h );
      double value = (1.7 - cos_normals * fabs(cos_normals*cos_normals) - 1.2*cos_big_angle) * ( l + 0.3 * L + 0.15 * h );
      
      // debug
      //    if (_verbose)
      //    {
      //      std::cout << "edge length is " << l << std::endl;
      //      std::cout << "vector to "; pf.print(); std::cout << " is "; v0f.print(); std::cout << " of height " << h << std::endl;
      //    }
      if (_verbose)
      {
        std::cout << "\nCandidate node index " << i << " has value " << value << std::endl;
        f.print();
        std::cout << "  cos_normals:" << cos_normals << " cos_big_angle:" <<  cos_big_angle << " l:" << l << " L:" << L << " h:" << h << std::endl;
      }
      
      if ( value < best_value )
      {
        //debug
        best_cos_normals = cos_normals;
        best_cos_big_angle = cos_big_angle;
        best_l = l;
        best_L = L;
        best_h = h;
        
        best_value = value;
        best_i = i;
        best_pp = pp;
        if (_verbose) std::cout << "new best " << std::endl;
      }
    }
    if (_verbose) std::cout << std::endl;
  }
  // if the best is valid but not good, then let the caller know
  best_not_good = (best_pp == 1);
  std::vector<FrontNode> &pool = (best_pp == 0 ? np.good : np.valid );

  best_too_long = (best_L > 800);

  if (debug_quality && recurse)
  {
    if ( best_too_long )
    {
      
      // print out the advances state as well...
      if (/* DISABLES CODE */ (0))
      {
        std::cout << "\nlong triangle edge with ";
        fe.print();
        pool[best_i].print();
      }
      
      if (/* DISABLES CODE */ (0)) // verbose
      {
        fe.print();
        
        std::cout << "Best triangle has node local id " << best_i << " value " << best_value << std::endl;
        std::cout << "  cos_normals:" << best_cos_normals << " cos_big_angle:" <<  best_cos_big_angle << " l:" << best_l << " L:" << best_L << " h:" << best_h << std::endl;
        
        pool[best_i].print();
        pool[best_i]._node->print();
        
        // call again, with verbose output, to get values of all the nodes
        if (recurse)
        {
          bool old_verbose = _verbose;
          _verbose = true;
          bool bng, btl;
          best_node(ac, t0, fe, np, bng, btl, false);
          _verbose = old_verbose;
        }
      }
    }
  }

  return pool[best_i];
}


std::string to_string_with_commas(int value)
{
  std::string numWithCommas = std::to_string(value);
  int insertPosition = (int) numWithCommas.length() - 3;
  while (insertPosition > 0) {
    numWithCommas.insert(insertPosition, ",");
    insertPosition-=3;
  }
  return numWithCommas;
}

void BoxSurfaceInclusionTool::classify_triangle(const FrontNode &a, const FrontNode &b, const FrontNode &c, bool &is_horizontal, bool &is_vertical)
{
  const bool ab_horiz = FrontEdge::is_horizontal(a,b);
  const bool ac_horiz = FrontEdge::is_horizontal(a,c);
  const bool bc_horiz = FrontEdge::is_horizontal(b,c);
  const int num_horiz = (int)ab_horiz + (int)ac_horiz + (int)bc_horiz;

  // all three edges are horizontal
  is_horizontal = (num_horiz == 3);

  // strictly vertical if one edge is horizontal and one is vertical
  is_vertical = (num_horiz == 1) && // one horiz
    ( FrontEdge::is_vertical(a,c) || FrontEdge::is_vertical(a,b) || FrontEdge::is_vertical(b,c) );
}


Triangle * BoxSurfaceInclusionTool::add_triangle_feb(AdvanceContext &ac, BoxSurfaceInclusionTool::FrontEdges &front_edges,
                                                Triangle *t0, const BoxSurfaceInclusionTool::FrontEdge &fe,
                                                FrontNode &b, bool &is_horizontal, bool &is_vertical )
{
  
  // make a new triangle, update the front
  if (!b._node)
    b._node = new_grid_node(ac.agn, ac.T, b );
  Triangle *t1 = ac.T->new_triangle( fe._fn0._node, fe._fn1._node, b._node );
  
  // debug - separate horizontal and vertical triangles
  classify_triangle( fe._fn0, fe._fn1, b, is_horizontal, is_vertical );
  if (is_horizontal)
    ac.T->_horizontal_triangles.push_back(t1);
  if (is_vertical)
    ac.T->_vertical_triangles.push_back(t1);
  if (!is_vertical && !is_horizontal)
    ac.T->_skew_triangles.push_back(t1);
  
  // debug
  if (_verbose)
  {
    Point tn = t1->normal();
    std::cout << "new triangle normal is ";
    tn.print();
    double cos_alpha, cos_omega, lr;
    t1->quality(cos_alpha, cos_omega, lr);
    std::cout << "Quality : " << cos_alpha << "  " << cos_omega << " " << lr << std::endl;
    if ( cos_alpha > 0.9 )
      std::cout << "WARNING: small angle" << std::endl;
    if ( cos_omega < -0.8 )
      std::cout << "WARNING: large angle" << std::endl;
    if ( lr < 0.01 ) // ratio 100 to 1
      if ( fabs( tn.z ) > 0.1 ) // weed out vertical triangles
        std::cout << "WARNING: extreme edge length ratio on horizontal triangle" << std::endl;
  }
  
  // add two new edges to front queue
  //   defer non-horizontal edges to later
  FrontEdge fe0b( fe._fn0, b, fe._fn1 );
  assert( check_coordinates(ac.agn, fe0b) );
  push_back(ac, front_edges, fe0b, !fe0b.is_horizontal() );
  
  FrontEdge fe1b( fe._fn1, b, fe._fn0 );
  assert( check_coordinates(ac.agn, fe1b) );
  push_back(ac, front_edges, fe1b, !fe1b.is_horizontal() );
  
  // we'll check later when we pop them if any of these are already closed, etc.
  return t1;
}


void BoxSurfaceInclusionTool::advance_front(AdvanceContext &ac, FrontEdges &front_edges, size_t manifold_id )
{
  const bool debug_quality = false;

  std::vector<Triangle*> tris;
  NodePool np;
  
  // ====== status reporting ======
  int summary_advance = 100000; // print quick line of progress every summary_advance triangles
  int advances = 0; // num triangles so far
  int last_advance = 0; // value of advance the last time we successfully created a triangle
  int num_requeued = 0; // number of edges taken off the queue then put back on, since last time one was discarded or an advance was made
  int advances_inc = 0; // num triangles since last report
  const int multiplier = 1000; // divide by multiplier before reporting to avoid a lot of senseless zeros.
  
  std::cout << "\n\nReconstructing surfaces from points using advancing front" << std::endl;
  const int internal_nodes =  (int) ( (_s->grid_x_size()-2) * (_s->grid_y_size()-2) );
  std::cout << _s->num_surfs() << " data sets, each of internal size " << _s->grid_x_size() -2 << " by " << _s->grid_y_size() -2 << " = " << to_string_with_commas( internal_nodes ) << std::endl;
  const int expected_triangles = (int) ( 2 * internal_nodes * _s->num_surfs() );
  const int expected_advance = expected_triangles * 3; // why? just observed, seems too high, triangles have 3 edges but how does this factor in?
  std::cout << "Expected triangles = " << to_string_with_commas(expected_triangles) << " by advances = " << to_string_with_commas( expected_advance/multiplier ) << " in blocks of " << to_string_with_commas(multiplier) << " edges each." << std::endl;

  const bool print_progress = false; // true for verbose output
  // ====== status reporting ======
  
  
  // advancing front
  // the non-empty tests figure out if the algorithm is stuck with no progress being made
  while (!front_edges.empty() /* && (advances - last_advance) < 2.1 * front_edges.size() + 100 && num_requeued < 1.2 * front_edges.size() + 100 */ )
  {

    // ====== status reporting ======
    ++advances;
    if ( ++advances_inc == summary_advance )
    {
      std::cout << to_string_with_commas(advances/multiplier) << "  ";
      std::cout.flush();
      advances_inc = 0;

      // debug
      if ( advances >= 1700000 ) // where full starts to have troubles
      {
        // write out info on queue sequence
        front_edges.print_queue();
        // front_edges.print_all_pops();

        // write out info on partial mesh
        // write_mesh(ac.T, "r_" + std::to_string(manifold_id) + "_", advances);
        // summary_advance = 10000; // report more often, debug zzyk
      }
    }

    // debug, write out mesh file every iteration! 
    // slow but effective...
    if (/* DISABLES CODE */ (0))
    {
      write_mesh(ac.T, "ss_" + std::to_string(manifold_id) + "_", advances);
    }

    //quit early
    if ( (0) && advances > 83 )
    {
      std::cout << "DEBUG: quitting early at iteration " << advances << std::endl;
      return;
    }
    
    // debug
    if (/* DISABLES CODE */ (0) && advances == 1719178)
    {
      std::cout << "debugging advance_front iteration " << advances << std::endl;
    }
    // ====== status reporting ======
    

    // fe = current front edge
    // There seems to be something wrong with the copy constructor for FrontEdges.
    // Just use a reference for now as that seems to work.
    bool strict_requirements = true;
    const FrontEdge fe = pop_front(ac, front_edges, strict_requirements);

    if ( /* DISABLES CODE */ (0) && ( fe._fn0._si != 0 || fe._fn1._si != 0 || fe._fn_tri._si != 0 ) )
    {
      std::cout << "DEBUG: non si==0 front edge" << std::endl;
    }
    //debug
    if ( /* DISABLES CODE */ (0) && (fe._fn0._si == 1 && fe._fn1._si == 1 && fe._fn_tri._si == 0 ) )
    {
      std::cout << "DEBUG: should advance beyond this horizontal edge after a vertical triangle" << std::endl;
    }
    
    // check if fe is on the i,j  boundary of the domain, in which case it will only have one triangle, and we can skip it
    if ( fe.domain_boundary(_s) )
    {
      if (print_progress)
        std::cout << "front edge on domain boundary, skipping" << std::endl;
    }
    else
    {
      // assert( !fe.domain_boundary(_s) );
      tris.clear();
      fe.triangles(tris);
      if (tris.size() > 2)
      {
        std::cout << "\n\nERROR: mess up, tri-valent edge" << std::endl;
        return;
      }
      if (tris.size()==1)
      {
        if (print_progress) std::cout << "front edge with one triangle, advancing" << std::endl;
        
        Triangle *t0 = tris[0];
        
        // find best triangle to put on other side...
        
        // find candidate nodes, and vet them
        candidate_nodes( ac, t0, fe, np );
        
        // pick best one
        if (np.empty())
        {
          if (print_progress)
            std::cout << "no valid way to advance. FrontEdge discarded." << std::endl;
        }
        else
        {
          if (print_progress) std::cout << "advancing by picking best node of " << np.good.size() + np.valid.size() << std::endl;
          
          bool best_not_good, best_too_long;
          FrontNode b = best_node( ac, t0, fe, np, best_not_good, best_too_long );

          // three cases: too long - discard; not good and strict - defer; good - add triangle
          if (best_too_long)
          {
            // todo: explore other logic
            if (print_progress)
            {
              std::cout << "the best way to advance results in a long triangle. Skipping and discarding.\n";
              fe.print();
            }
          }
          else if (best_not_good && strict_requirements)
          {
            // debug
            if (print_progress)
            {
              std::cout << "the best way to advance is valid but not good because it would create non-disk topology.\n" <<
                "FrontEdge requeued until other advances make the best choice good, or invalid.";
              fe.print();
            }
            
            // defer until the topology would be disk-like when adding the triangle
            push_back(ac, front_edges, fe, fe.is_vertical(), true);
            num_requeued++;
          }
          else
          {
            if (print_progress)
            {
              // print nothing, otherwise output is too cluttered
              //std::cout << "Best node is good and not too long. Adding triangle \n";
              //fe.print();
            }
            bool is_horizontal, is_vertical;
            Triangle *t1 = add_triangle_feb( ac, front_edges, t0, fe, b, is_horizontal, is_vertical);
            last_advance = advances;
            num_requeued=0;
            
            // debug
            if ( /* DISABLES CODE */ (0) && (fe._fn0._si != b._si) )
            {
              std::cout << "DEBUG: quitting early, with first si jump, advances " << advances << std::endl;
              return;
            }
            
            
            // try to make a second vertical triangle to make a quad immediately
            if (is_vertical)
            {
              // debug
              if (/* DISABLES CODE */ (0))
              {
                std::cout << "DEBUG: vertical triangle at iteration advances=" << advances << std::endl;
                // return;
              }
              
              if (print_progress)
              {
                std::cout << "Vertical triangle added, attempting to add the other one that makes it a vertical quad." << std::endl;
              }
              
              // debug, all our vertical triangles should have equal _i coordinates in toy problem, but not full problem
              if ( 0 && debug_quality && (fe._fn0._i != fe._fn1._i) )
              {
                std::cout << " bad triangle formed, debug me, advances " << advances << std::endl;
              }
              
              // advance from the diagonal edge of the quad, to see if we can complete the quad
              
              // order vertical triangle t1 to label its nodes correctly
              //
              // f_above ---- f_side
              //  |          /  |
              //  |         /   |
              //  |  t1    /    |
              //  |       /     |
              //  |     ge      |
              //  |     /       |
              //  |    /        |
              // f_below --- g_below
              //
              FrontNode f_above, f_below, f_side;
              fe.find_below_node(b, f_above, f_side, f_below);
              FrontEdge ge(f_below, f_side, f_above);
              
              if (!ge.closed())
              {
                NodePool gn;
                
                // get restricted candidate, just the ones up/down from f_side
                FrontNode g_below = f_side; // copy i,j coordinates
                bool skip = false;
                if ( (f_side._si > 0) && (f_above._node->z > f_below._node->z))
                  g_below._si = f_side._si - 1;
                else if ( (f_side._si + 1 < _s->_surfs.size()) && (f_above._node->z < f_below._node->z) )
                  g_below._si = f_side._si + 1;
                else
                  skip = true;
                
                if (!skip)
                {
                  gn.candidates.push_back(g_below);
                  vet_candidates( ac, t1, ge, f_side, f_below, gn ); // updates g_below's nodes
                  
                  if (!gn.empty())
                  {
                    bool bng, btl;
                    FrontNode gb = best_node(ac, t1, ge, gn, bng, btl, false);
                    
                    const bool second_added = !( (strict_requirements && bng) || btl );
                    if (second_added)
                    {
                      bool g_is_horizontal, g_is_vertical;
                      add_triangle_feb( ac, front_edges, t1, ge, gb, g_is_horizontal, g_is_vertical);
                    }
                    
                    //== debug
                    if (print_progress)
                    {
                      if (second_added)
                      {
                        std::cout << "Adding second quad triangle\n.";
                      }
                      else
                      {
                        if (print_progress)
                        {
                          std::cout << "Skipping second quad triangle because triangle is ";
                          if ( bng )
                            std::cout << " not_good ";
                          if (btl)
                            std::cout << " too_long ";
                        }
                        ge.print();
                        gb.print();
                      }
                    }//== end debug
                  }
                }
              }
            }
          }
        }
      }
      else if (tris.size()==2)
      {
        if (print_progress) std::cout << "front edge already manifold" << std::endl;
      }
      else
      {
        // if (print_progress)
          std::cout << "ERROR: edge has " << tris.size() << " triangles." << std::endl;
      }
    }
    
  }
  std::cout << to_string_with_commas(advances/multiplier);
  if (front_edges.empty())
    std::cout << " done!" << std::endl;
  else
  {
    std::cout << "Giving up\n";
    std::cout << "  stuck with no progress from iteration " << last_advance << " to " << advances << ". Giving up with remaining FrontEdges queue\n";
    std::cout << "  (advances - last_advance)=" << (advances - last_advance) << " num_requeued=" << num_requeued << " front_edges.size()= " << front_edges.size() << std::endl;
    front_edges.print();
    std::cout << "  declaring done." << std::endl;
  }
}

void BoxSurfaceInclusionTool::write_mesh(Triangulation*T, std::string fname, size_t id)
{
      // debug
      // write out separate horizontal and vertical and skew triangles files
  TriangulationTool TT( T );
  fname += std::to_string(id);
  TT.write_ply( fname + "_all" + ".ply" );
  const size_t orig_size = T->_triangles.size();
  T->_triangles.swap( T->_vertical_triangles );
  TT.write_ply( fname + "_vertical" + ".ply" );
  T->_triangles.swap( T->_vertical_triangles );
//  T->_triangles.swap( T->_horizontal_triangles );
//  TT.write_ply( fname + "_horizontal" + ".ply" );
//  T->_triangles.swap( T->_horizontal_triangles );
//  T->_triangles.swap( T->_skew_triangles );
//  TT.write_ply( fname + "_skew" + ".ply" );
//  T->_triangles.swap( T->_skew_triangles );
  assert( T->_triangles.size() == orig_size );
}

void BoxSurfaceInclusionTool::connect_manifolds()
{
  assert(_triangulations.empty()); // delete_triangulations if not
  
  // set up the associativity between inclusion surface sample points and mesh nodes
  init_grid_nodes(ac);

  // initialize Triangulations
  // we will have one per reconstructed manifold, not per inclusion surface grid

  // for all the inclusion grids
  for (size_t top_s=0; top_s < _s->_surfs.size(); ++top_s)
  {
    ac.top_s = top_s;
    // seed with a flat triangle from that isn't triangulated
    size_t flat_i(_s->grid_x_size() / 2), flat_j( _s->grid_y_size() / 2);
    while ( find_flat_spot( ac, top_s, flat_i, flat_j ) )
    {
      // hold the new triangulation manifold
      Triangulation *T = new Triangulation;
      _triangulations.push_back(T);
      const size_t Ti = _triangulations.size()-1;
      ac.T = T;

      // form the first two triangles
      FrontEdges front_edges;
      init_two_triangles(ac, top_s, T, flat_i, flat_j, front_edges);

      advance_front(ac, front_edges, Ti );
      
      front_edges.print_all_pops();
      
      TriangulationTool TT( T );
      std::cout << "Checking connectivity of manifold " << std::endl;
      std::vector<Edge> open_edges;
      bool good = TT.good_connectivity( _s->min_x(), _s->min_y(), _s->max_x(), _s->max_y(), &open_edges );
      if (!good)
      {
        std::cout << "\nAttempting to fix remaining connectivity problems with the closure hack of advancing from those edges and considering node candidates with more different indices." << std::endl;
        _allow_far_index_triangles = true;
        FrontEdges front_edges_hack;
        convert_to_front_edges(ac, front_edges_hack, open_edges );
        advance_front(ac, front_edges_hack, Ti );
        _allow_far_index_triangles = false;

        front_edges_hack.print_all_pops();
        std::cout << "Checking connectivity of manifold after hack" << std::endl;
        std::vector<Edge> open_edges;
        good = TT.good_connectivity( _s->min_x(), _s->min_y(), _s->max_x(), _s->max_y() );
      }
      
      finalize_used_grid_marks(ac);
      
      // debug
      // write_mesh(T, "ss_manifold_", Ti );
      // goto quit; // debug, skip out after first one
    }
    
  } // for top_s

quit:
  
  // report output
  // make off () and ply (paraview) files
  // report_triangulations( triangulations )
  std::cout << "\nTriangulation consists of " << _triangulations.size() << " manifolds" << std::endl;
  for (size_t i = 0; i < _triangulations.size(); ++i)
  {
    std::cout << "Manifold " << i << std::endl;
    Triangulation *T = _triangulations[i];
    TriangulationTool TT( T );
    std::string fname = "inclusion_surface_triangulation_" + std::to_string(i);
    // TT.write_off_file( fname + ".off" );
    TT.write_ply( fname + ".ply" );
    
    std::cout << "\n";
  }

  // test output
  // already done in loop
//  for (size_t i = 0; i < triangulations.size(); ++i)
//  {
//    Triangulation *T = triangulations[i];
//    TriangulationTool TT( T );
//    std::cout << "Checking connectivity of manifold " << i << std::endl;
//    TT.good_connectivity( _s->min_x() + _s->grid_x(), _s->min_y() + _s->grid_y(), _s->max_x(), _s->max_y() ); // ? +/- _s->grid_y() _x?
//  }

  // todo: collect vertical and horizontal triangles and write out files with just those in them
  // todo: smaller test problem.  test triangles geometrically piercing one another.
}

void BoxSurfaceInclusionTool::FrontEdge::push_back_uniqueFE( std::vector<BoxSurfaceInclusionTool::FrontEdge> &fes ) const
{
  for (size_t i = 0; i < fes.size(); ++i)
    if ( same_front_edge( fes[i]) )
      return;
  fes.push_back(*this);
}

void BoxSurfaceInclusionTool::FrontEdge::find_below_node(const BoxSurfaceInclusionTool::FrontNode &b, BoxSurfaceInclusionTool::FrontNode &f_above, BoxSurfaceInclusionTool::FrontNode &f_side,  BoxSurfaceInclusionTool::FrontNode &f_below) const
{
  if ( is_horizontal() )
  {
    f_below = b;
    if ( FrontEdge::is_vertical(b,_fn0) )
    {
      f_above = _fn0;
      f_side = _fn1;
    }
    else
    {
      assert( FrontEdge::is_vertical(b,_fn1) );
      f_above = _fn1;
      f_side = _fn0;
    }
  }
  else if ( FrontEdge::is_horizontal( _fn0, b ) )
    FrontEdge(_fn0, b, _fn1).find_below_node(_fn1, f_above, f_side, f_below);
  else
  {
    assert( FrontEdge::is_horizontal( _fn1, b ) );
    FrontEdge(_fn1, b, _fn0).find_below_node(_fn0, f_above, f_side, f_below);
  }
}

void BoxSurfaceInclusionTool::FrontEdges::push_back(const FrontEdge &fe, bool is_vertical, bool is_deferred)
{
  assert( fe._fn_tri._si != -1 );
  if (is_deferred)
    _front_deferred.push_back(fe);
  else if (is_vertical)
    _front_vertical.push_back(fe);
  else
    _front.push_back(fe);
}

void BoxSurfaceInclusionTool::push_back(AdvanceContext &ac, FrontEdges &front_edges, const FrontEdge &fe, bool is_vertical, bool is_deferred)
{
  // debug
  if (/* DISABLES CODE */ (0))
  {
    std::cout << "pushing ";
    fe.print();
    if ( fe._fn0.same_front_node( FrontNode(ac.agn, 0,2,2)) )
    {
      _watch_me = fe._fn0._node;
    }
  }
  assert( check_coordinates(ac.agn, fe) );
  front_edges.push_back(fe, is_vertical, is_deferred);
}



BoxSurfaceInclusionTool::FrontEdge BoxSurfaceInclusionTool::FrontEdges::pop_front(bool &strict_requirements)
{
  strict_requirements = true;
  FrontEdge f; // null
  
  PopStat ps;

    // cycle through various fronts, popping and returning the first one
  if (!_front.empty())
  {
    // _num_consecutive_deferred = -1;  // experiment to avoid cycling through deferred edges forever
    f = pop_front(_front);
    ++_num_front;
    ps.which_queue = 0;
  }

    // cycle through deferred edges, to see if any of them are now OK
    // for efficiency, only reset the count when we advance the normal front
  else if (_num_consecutive_deferred != 0 && _front_deferred.size() )
  {
    // do once, the first time only
    // this means we will go through all the currently defered ones once, then do all the verticals
    if (_num_consecutive_deferred < 0)
      _num_consecutive_deferred = _front_deferred.size();
    
    --_num_consecutive_deferred;
    f = pop_front(_front_deferred);
    ++_num_deferred_0;
    ps.which_queue = 1;
  }

  else if (!_front_vertical.empty())
  {
    f = pop_front(_front_vertical);
    ++_num_vertical;
    ps.which_queue = 2;
  }

  // allows the deferred to succeed past vet_candidates
  // allow some advances that aren't perfect, in order to close the mesh
  else if (!_front_deferred.empty())
  {
    strict_requirements = false;
    f = pop_front(_front_deferred);
    ++_num_deferred_1;
    ps.which_queue = 3;
  }
  else
  {
    // caller should check if empty first
    assert(0);
    ps.which_queue = 4;
  }
  
  ps.f = f;
  all_pops.push_back(ps);

  return f;
}

BoxSurfaceInclusionTool::FrontEdge BoxSurfaceInclusionTool::pop_front(AdvanceContext &ac, FrontEdges &front_edges, bool &strict_requirements)
{
  FrontEdge fe = front_edges.pop_front(strict_requirements);
  // debug
  if (/* DISABLES CODE */ (0))
  {
    std::cout << "popping ";
    fe.print();
  }
  check_coordinates(ac.agn, fe);

  return fe;
}


void BoxSurfaceInclusionTool::FrontEdge::print() const
{
  std::cout << "FrontEdge\n  _fn0 ";
  _fn0.print();
  std::cout << "  _fn1 ";
  _fn1.print();
  std::cout << "  Edge ";
  Edge::print();
  std::cout << std::endl;
}

void BoxSurfaceInclusionTool::FrontEdges::print() const
{ 
  std::cout << "FrontEdges advancing front of edges\n";
  std::cout << "  normal   front size " << _front.size() << "\n";
  std::cout << "  vertical front size " << _front_vertical.size() << "\n";
  std::cout << "  deferred front size " << _front_deferred.size() << "\n";
  std::cout << "  _num_consecutive_deferred " << _num_consecutive_deferred << std::endl;
}

void BoxSurfaceInclusionTool::FrontNode::print() const
{
  std::cout << "FrontNode (i,j,s) = (" << _i << "," << _j << "," << _si << ")" << std::endl;
  if (_node)
  {
    std::cout << _node << " "; // pointer value
    _node->print();
  }
  else
    std::cout << "_node = 0\n";
  std::cout.flush();
}


void BoxSurfaceInclusionTool::convert_to_front_edges(AdvanceContext &ac, FrontEdges &front_edges, std::vector<Edge> &open_edges )
{
  // slow, but works ok for small problems
  
  for (size_t ei = 0; ei < open_edges.size(); ++ei)
  {
    Edge &e = open_edges[ei];
    FrontNode fn0, fn1, fntri;
    
    std::vector<Triangle*> tris;
    e.triangles(tris);
    assert(tris.size() == 1); // later support zero triangles
    Triangle *t = tris[0];
    Node *nt = t->opposite_node(e);
    //    FrontEdge fe(e);

    // find node in array, to get the front node
    for (size_t s = 0; s < ac.agn.size(); ++s)
    {
      GridNodes *gn = ac.agn[s];
      for (size_t i = 0; i < gn->grid_x_size(); ++i)
        for (size_t j = 0; j < gn->grid_y_size(); ++j)
        {
          Node *n = gn->marks[i][j];
          if (n == e._n0)
          {
            fn0 = FrontNode (ac.agn, s, i, j );
          }
          if (n == e._n1)
          {
            fn1 = FrontNode (ac.agn, s, i, j );
          }
          if (n == nt)
          {
            fntri = FrontNode( ac.agn, s, i, j );
          }
          if ( fn0._node && fn1._node && fntri._node ) // quit early if both found
            break;
        }
    }
    
    assert( fn0._node );
    assert( fn1._node );
    assert( fntri._node );
    
    FrontEdge fe(fn0, fn1, fntri );
    
    push_back( ac, front_edges, fe );
  }
};


void BoxSurfaceInclusionTool::finalize_used_grid_marks(AdvanceContext &ac)
{
  // clear nodes of this triangulation from agn
  // and mark the nodes with triangles as having been meshed
  // agn
  // agn_saved
  
  for (size_t s = 0; s < ac.agn.size(); ++s)
  {
    GridNodes *gn = ac.agn[s];
    GridNodes *gn_saved = ac.agn_saved[s];
    GridMeshed *gk = ac.ameshed[s];
    for (size_t i = 0; i < gn->grid_x_size(); ++i)
      for (size_t j = 0; j < gn->grid_y_size(); ++j)
      {
        Node *n = gn->marks[i][j];
        short &meshed = gk->marks[i][j];
        if (n && !n->_triangles.empty())
        {
          // flag surface point as in this triangulation
          // (same as if it was in a prior one)
          meshed = 1;
          gn_saved->marks[i][j] = n;
        }
        // else delete_unused_nodes will get rid of n below
        // regardless of triangles being empty, remove reference to node in gridnodes
        gn->marks[i][j] = 0;
      }
  }

  // triangulation
  ac.T->delete_unused_nodes();
}

bool BoxSurfaceInclusionTool::FrontNode::operator< (const FrontNode& right) const
{
  if ( _si == right._si )
  {
    if ( _i == right._i )
    {
//      if ( _j == right._j )
//      {
//        return (_node < right._node);
//      }
//      else
        return ( _j < right._j );
    }
    else
      return (_i < right._i);
    
  }
  else
    return (_si < right._si);
}


bool BoxSurfaceInclusionTool::FrontEdge::operator< (const FrontEdge& right) const
{
  // first sort the nodes of the edge
  FrontNode f0,f1,r0,r1;
  if (_fn0 < _fn1)
  {
    f0 = _fn0;
    f1 = _fn1;
  }
  else
  {
    f1 = _fn0;
    f0 = _fn1;
  }
  
  if (right._fn0 < right._fn1)
  {
    r0 = right._fn0;
    r1 = right._fn1;
  }
  else
  {
    r1 = right._fn0;
    r0 = right._fn1;
  }

  if ( f0 == r0 )
  {
    return f1 < r1;
  }
  else
    return f0 < r0;
}

bool BoxSurfaceInclusionTool::FrontEdges::PopStat::operator < (const PopStat& right) const
{
  if (f == right.f)
    return which_queue < right.which_queue;
  else
    return f < right.f;
}


void BoxSurfaceInclusionTool::FrontEdges::print_all_pops() const
{
  
  // print one long string of which queue nodes came from
  std::string s = ".dvD0";
  std::cout << "\n" << all_pops.size() << " pops, in sequence: .=normal, d=deferred before v, v=vertical, D=deferred after v" << std::endl;
  if (all_pops.empty())
  {
    std::cout << " no pops at all!" << std::endl;
    return;
  }
  long total_q[5] = {0};
  int num_same = 1;
  int prior_queue = all_pops[0].which_queue;
  for (size_t i = 1; i < all_pops.size(); ++i)
  {
    const PopStat &ps = all_pops[i];
    ++total_q[ps.which_queue];
    ++num_same;
    if (ps.which_queue != prior_queue || i+1 == all_pops.size())
    {
//      if ( num_same > 1 )
        std::cout << " " << num_same << s[prior_queue];
//      else
//        std::cout << " " << s[prior_queue];
      
      prior_queue = ps.which_queue;
      num_same = 1;
    }
  }
  std::cout << std::endl;
  std::cout << "Total pops by queue:";
  for (size_t q = 0; q < 5; ++q )
  {
    std::cout << " " << total_q[q] << s[q];
  }
  std::cout << "\n" << std::endl;
  
  
  // slow, edges appearing more than once
  if (/* DISABLES CODE */ (0))
  {
    std::cout << "Edges appearing lots:\n";
    const int afew=5;
    long few_num[afew] = {0};
    auto pops_copy = all_pops; // copy
    std::sort(pops_copy.begin(), pops_copy.end());
    long num_f = 1;
    long num_q [5] = {0};
    FrontEdge prior_f = pops_copy[0].f;
    for (size_t i = 0; i < pops_copy.size(); ++i)
    {
      const PopStat &ps = pops_copy[i];
      if ( ps.f == prior_f )
        ++num_f;
      else
      {
        if ( num_f < afew )
        {
          few_num[num_f]++;
          num_q[ps.which_queue]++;
        }
        else
        {
          prior_f.print();
          std::cout << " appeared " << num_f << " times:";
          for (size_t q = 0; q < 5; ++q)
          {
            if (num_q[q] > 0)
            {
              std::cout << " " << num_q[q] << s[q];
            }
          }
          std::cout << std::endl;
        }
        // move on to the next edge
        prior_f = ps.f;
        num_f = 1;
        for (size_t q = 0; q < 5; ++q)
          num_q[q] = 0;
        num_q[ps.which_queue] = 1;
      }
    }
    
    std::cout << "Edges appearing a few times, times:number_of_edges\n";
    for (size_t i = 1; i < afew; ++i )
    {
      std::cout << "  " << i << ":" << few_num[i] << std::endl;
    }
  }
}

void BoxSurfaceInclusionTool::FrontEdges::print_queue() const
{
  std::cout << "\n Current Queue of FrontEdges, num_consecutive_defered:" << _num_consecutive_deferred << ", queue sizes:";
  std::cout << "normal " << _front.size() << ",  vertical " << _front_vertical.size() << ", deferred " << _front_deferred.size() << std::endl;
  
}

bool BoxSurfaceInclusionTool::check_coordinates(AllGridNodes &agn, const FrontNode &f) const
{
  Node *fn = f._node;
  Node *mn = agn[f._si]->marks[f._i][f._j];
  assert( fn == mn );
  assert( fn );
  if ( f._node )
  {
    Point gp = grid_point(f);
    Point fp = *fn;
    if ( !(gp == fp ) )
    {
      std::cout << fn << " ";
      fn->print();
    }
    assert( gp == fp );
    Point mp = *mn;
    assert( mp == gp );
    return (gp == fp) && (gp == mp);
  }
  return true; // ok if node is unset
}


class CorePoint
{
public:
  Point p;
  int ti; // which triangulation
  int si; // which surface of depth map
  friend bool operator<(const CorePoint &lhs, const CorePoint& rhs) { return (lhs.p.z < rhs.p.z); }
};

int find_triangulation( std::vector<Triangulation*> &T, Point p)
{
  for (size_t ti = 0; ti < T.size(); ++ti)
  {
    Triangulation *t = T[ti];
    for (size_t i = 0; i < t->_nodes.size(); ++i)
    {
      if ( p.is_close( *t->_nodes[i], 1.e-4) )
      {
        return (int) ti;
      }
    }
  }
  return -1;
}

int BoxSurfaceInclusionTool::num_crossings_from_neg_infinity( BoxFace &bf, size_t t, int recursion_depth )
{
  // If we run into a near-coincidence with a triangulation vertex or edge, we will try a different face point.
  // Recall from the context of the caller that these faces are supposed to be well away from the triangulation,
  // so this randomization should work just fine.
  Point p = bf.first->random_face_point( bf.second );
  // in the case of a vertical box side, randomizing the face_point may not help enough. So instead use a point inside the box
  const int thresh = 2;
  if (recursion_depth > thresh)
  {
    const double a = bf.first->rand(); // in [0,1]
    // the higher the recursion_depth, the closer to the center we allow
    const double lambda = (1. / (1.+recursion_depth-thresh) ) + (1. - (1. / (1.+recursion_depth-thresh))) * (1. - a * a); // [0,1], tends towards 1 for small recursion_depth
    assert( lambda >= 0. );
    assert( lambda <= 1. );
    const Point c = bf.first->center();
    p  = p * lambda + c * (1-lambda);
  }
  
  int num_crossings = 0;
  
  // speedup - use the grid to speed up the search for the relevant triangles
  // ij extent around p
  size_t xl, xh, yl, yh;
  xl = xh = _s->x2i(p.x);
  yl = yh = _s->y2i(p.y);
  // add two to range in each direction: zzyk
  if ( xl < 2 ) xl = 0; else xl -= 2;
  if ( yl < 2 ) yl = 0; else yl -= 2;
  if ( xh > _s->grid_x_size() - 3 ) xh = _s->grid_x_size(); else xh += 3;
  if ( yh > _s->grid_y_size() - 3 ) yh = _s->grid_y_size(); else yh += 3;
  assert( _s->xi_ok(xl) );
  assert( _s->xi_ok(xh-1) );
  assert( _s->yi_ok(yl) );
  assert( _s->yi_ok(yh-1) );

  // use triangulation t
  Triangulation *T = _triangulations[t];
  for (size_t s = 0; s < _s->_surfs.size(); ++s)
  {
    GridNodes *gn = ac.agn_saved[s];
    for (size_t i = xl; i < xh; ++i)
      for (size_t j = yl; j < yh; ++j)
      {
        Node *n = gn->marks[i][j];
        if (n)
          for (size_t tt = 0; tt < n->_triangles.size(); ++tt )
          {
            Triangle *tri = n->_triangles[tt];
            if( tri->_triangulation == T && tri->_nodes[0] == n )
            {
              bool crosses = false;
              bool degenerate = false;
              TriangleMath::crosses_from_neg_infinity(*tri->_nodes[0], *tri->_nodes[1], *tri->_nodes[2], p, crosses, degenerate);

              if ( degenerate )
              {
                if (recursion_depth < 100)
                  return num_crossings_from_neg_infinity(bf, t, recursion_depth+1);
                else
                {
                  std::cerr << "ERROR: unable to determine whether box face is above or below a triangulated inclusion surface, due to geometric coincidence between box faces and triangles.\n Try reducing the domain by a grid point or two and rerunning" << std::endl;
                  // zzyk todo:
                  //   make some guess based on z depth
                }
              }
              if (crosses)
                num_crossings++;
            }
          }
      }
  }


// brute force, too slow
  /*
  for (size_t t = 0; t < T->_triangles.size(); ++t)
  {
    // debug
//    if (t==4) // and T is the second one, index 1
//    {
//      std::cout << "debugging num_crossings_from_neg_infinity" << std::endl;
//    }
    Triangle *tri = T->_triangles[t];
    bool crosses = false;
    bool degenerate = false;
    TriangleMath::crosses_from_neg_infinity(*tri->_nodes[0], *tri->_nodes[1], *tri->_nodes[2], p, crosses, degenerate);
    // recurse with a different random point
    if ( degenerate )
    {
      if (recursion_depth < 100)
        return num_crossings_from_neg_infinity(bf, t, recursion_depth+1);
      else
      {
        std::cerr << "ERROR: unable to determine whether box face is above or below a triangulated inclusion surface, due to geometric coincidence between box faces and triangles.\n Try reducing the domain by a grid point or two and rerunning" << std::endl;
        // zzyk todo:
        //   make some guess based on z depth
      }
    }
    if (crosses)
      num_crossings++;
  }
   */
  
  return num_crossings;
}


void BoxSurfaceInclusionTool::sort_box_tet_faces( BoxFacesVecVec &box_faces_per_T, std::vector<int> &is_closed, const BoxFacesVec &box_faces )
{
  // I don't need to check if a set of box faces spans domain-edge to domain-edge.
  // It is OK if the volume between two triangle layers is actually split into two connected components.
  // the Inria tet mesher can handle that just fine, and since the elements will be the same material and in the same block, there is no problem.
  box_faces_per_T.resize( _triangulations.size() + 1 ); // indices 0 to triangulations.size()
  for (size_t b = 0; b < box_faces.size(); ++b)
  {
    auto bf = box_faces[b];
    
    // debug
    const Point face_center = bf.first->face_center( bf.second );
    bool layer0(true);
    if (fabs(face_center.z - 12.5) > 1e-4)
    {
      layer0 = false;
      std::cout << "face " << bf.second << " of box " << bf.first->get_id() << " should not be in layer 0 " << std::endl;
      bf.first->print2();
    }
    if (bf.first->get_id() == 183 )
    {
      std::cout << "first error face " << bf.first->get_id() << std::endl;
    }
    
    // find number of crossings from -infinity
    int layer_id = 0;
    for (size_t t = 0; t < _triangulations.size(); ++t)
    {
      // determine number of crossings from z = +infinity to the point
      int num_from_infty = num_crossings_from_neg_infinity( bf, t );
      if (is_closed[t]) // surface is enclosed buble
      {
        if ( num_from_infty % 2 == 1 )
        {
          layer_id = (int) t+1; // lies inside t
          // debug
          if (!layer0 && layer_id == 0)
          {
            std::cout << "error, wrong layer" << std::endl;
          }
          break;
        }
        // else do nothing, ignore
        
      }
      else // surface spans xy domain
      {
        if ( num_from_infty % 2 == 0 )
        {
          // lies above t, since we didn't cross it.
          // use whatever layer_id was set to before

          // debug
          if (!layer0 && layer_id == 0)
          {
            std::cout << "error, wrong layer" << std::endl;
          }

          break;
        }
        else
          layer_id = (int) t + 1; // lies below t
      }
    }
    // if no break was hit, then it lies beyond last triangulation
    
    assert( layer_id >= 0 );
    assert( layer_id <= _triangulations.size() );
    box_faces_per_T[layer_id].push_back( bf );
  }
}

void BoxSurfaceInclusionTool::assign_box_elastic_inclusion_zones()
{
  BTIOutput bti(_bt);
  for ( BoxTreeNode *b = bti.get(); b != 0; b = bti.next() )
  {
    if ( b->get_zone() == b->UNSET )
    {
      int crossings = 0;
      BoxFace bf = std::make_pair( b, 0 );
      for (size_t t = 0; t < _triangulations.size(); ++t)
      {
        // determine number of crossings from z = +infinity to the point
        int num_from_infty = num_crossings_from_neg_infinity( bf, t );
        crossings += num_from_infty;
      }
      b->set_zone(  (crossings % 2 == 0) ? b->ELASTIC : b->INCLUSION );
    }
  }
}


int BoxSurfaceInclusionTool::triangulation_depth(std::vector<Triangulation*> &T, size_t i, size_t j, Point p)
{
  // find the surface point above p
  //  find the triangulation containing it
  Point cp = p; // set x,y coordinates
  std::vector<int> prior_t; // stack of triangulations encountered. remove closed ones when we find two of them in a row
  prior_t.push_back(-1);
  for (int s = 0; s < (int) _s->_surfs.size(); ++s )
  {
    cp.z = _s->depth_ij(i, j, s);
    int t = find_triangulation(T, cp);
    if ( fabs(p.z - cp.z) <= 1.e-8 * p.z ) // found self, should be exactly equal, but use relative error to be sure
    {
      return prior_t.back();
    }
    else
    {
      if ( t == prior_t.back() )
        prior_t.pop_back(); // assert closed
      else
        prior_t.push_back(t);
    }
  }
  // ERROR, p not found!
  assert(0);
  return -1;
}

void BoxSurfaceInclusionTool::sort_triangulations_by_z( std::vector<Triangulation*> &T, std::vector<int> &is_closed, std::vector< int > &new_order )
{
  is_closed.resize( T.size(), 0 );
  
  std::vector< CorePoint > core_sample;
  for (size_t i = 0; i < T.size(); ++i )
  {
    Triangulation *t = T[i];
    CorePoint cp;
    cp.p = *t->_nodes[0];
    cp.ti = (int) i;
    cp.si = -1;
    for (size_t j = 0; j < t->_nodes.size(); ++j)
    {
      Point *p = t->_nodes[j];
      if ( p->x < cp.p.x || (p->x == cp.p.x && p->y < cp.p.y) )
        cp.p = *p;
    }
    // doesn't reach corner 0,0
    if ( fabs(cp.p.x) + fabs(cp.p.y) > 1e-4 )
      is_closed[i] = true;
    else
      core_sample.push_back(cp);
  }
  std::sort( core_sample.begin(), core_sample.end() );
  
  new_order.resize( core_sample.size() );
  for (size_t i = 0; i < core_sample.size(); ++i)
  {
    new_order[i] = core_sample[i].ti;
  }
  
  // insert the closed ones in the right place in the core_sample
  for (size_t i = 0; i < T.size(); ++i)
  {
    if (is_closed[i])
    {
      // find the node of the closed surface with smallest z
      FrontNode fn;
      fn._node = T[i]->_nodes[0];
      fn._i = _s->x2xi( fn._node->x );
      fn._j = _s->y2yi( fn._node->y );
      for (size_t j = 0; j < T[i]->_nodes.size(); ++j )
      {
        if ( T[i]->_nodes[j]->z < fn._node->z )
        {
          fn._node = T[i]->_nodes[j];
          fn._i = _s->x2xi( fn._node->x );
          fn._j = _s->y2yi( fn._node->y );
        }
      }

      int after_ti = triangulation_depth(T, fn._i, fn._j, *fn._node);
      
      // acutally insert it
      if ( after_ti == -1 )
        new_order.insert( new_order.begin(), (int) i );
      else
      {
        for (auto j = new_order.begin(); j != new_order.end(); ++j)
        {
          if ( *j == after_ti )
          {
            new_order.insert( j+1, int (i) );
            break;
          }
        }
      }
      
    }
  }
  assert( new_order.size() == T.size() );
  assert( is_closed.size() == T.size() );
  
}

bool BoxSurfaceInclusionTool::is_tet_box(BoxTreeNode *b) const
{
  // brute force, takes too long for full model.
  // tet box if I contain the inclusion surface, or an immediate neighbor does and I'm close to the surface.
/*
 for (int i = 0; i < _triangulations.size(); ++i)
  {
    TriangulationTool tt( _triangulations[i] );
    Triangle *t(0);
    const Box bb = b->dilate_box(_proximity);
    if ( tt.box_intersects_triangle(&bb, t) )
      return true;
  }
  return false;
*/

  // for a dilated box, get its xy ij extent, then add two
  // for each surface, for each ij, get the mesh node
  // Just visit each triangle once: if the mesh node is the first node of the triangle, then
  //   check that triangle

  assert(b->is_leaf());

  // cached is_tet_box for speed!
//  const BoxTreeNode::TetBox tb = b->get_is_tet_box();
//  switch (tb) {
//    case BoxTreeNode::YES:
//      return true;
//      break;
//    case BoxTreeNode::NO:
//      return false;
//      break;
//    case BoxTreeNode::UNKNOWN:
//    default:
//      ; // nothing, need to test
//  }
  
  const Box bb = b->dilate_box(_proximity);

  // ij extent
  size_t xl, xh, yl, yh;
  subgrid_range( &bb, xl, xh, yl, yh);
  // add two to range in each direction:
  if ( xl < 2 ) xl = 0; else xl -= 2;
  if ( yl < 2 ) yl = 0; else yl -= 2;
  if ( xh > _s->grid_x_size() - 3 ) xh = _s->grid_x_size()-1; else xh += 2;
  if ( yh > _s->grid_y_size() - 3 ) yh = _s->grid_y_size()-1; else yh += 2;
  assert( _s->xi_ok(xl) );
  assert( _s->xi_ok(xh) );
  assert( _s->yi_ok(yl) );
  assert( _s->yi_ok(yh) );
  
  for (int s = 0; s < ac.agn_saved.size(); ++s)
  {
    GridNodes *gn = ac.agn_saved[s];
    for (size_t i = xl; i < xh; ++i)
      for (size_t j = yl; j < yh; ++j)
      {
        Node *n = gn->marks[i][j];
        if (n)
          for (size_t t = 0; t < n->_triangles.size(); ++t )
          {
            Triangle *T = n->_triangles[t];
            if (T->_nodes[0] == n)
            {
              if (TriangulationTool::triangle_node_in_box(&bb,T) ||
                  TriangulationTool::triangle_edge_cross_box_face(&bb,T) )
              {
                b->set_is_tet_box( BoxTreeNode::YES );
                return true;
              }
            }
          }
      }
  }
  b->set_is_tet_box( BoxTreeNode::NO );
  return false;

//  // I contain the inclusion surface
//  if ( overlaps_surface_point(b) )
//    return true;
//  
//  // I'm close to the inclusion surface
//  const Box bb = b->dilate_box(_proximity);
//  if ( overlaps_surface_point(&bb) )
//  {
//     // Do any neighbors contain the inclusion surface?
//    std::vector<BoxTreeNode*> neighbors;
//    b->find_connected_boxes(neighbors, false);
//    for (size_t j = 0; j < neighbors.size(); ++j)
//    {
//      BoxTreeNode *n = neighbors[j];
//      assert( n->is_leaf() );
//      if ( overlaps_surface_point(n) )
//      {
//        // dilate b by 1/2 the diagonal of the neighbor
//        Point cmax = b->corner_max() + n->diagonal() * 0.5;
//        Point cmin = b->corner_min() + n->diagonal() * 0.5;
//        Box bd(cmin,cmax);
//        if ( overlaps_surface_point( &bd ) )
//          return true;
//      }
//    }
//  }
//  return false;
}

void BoxSurfaceInclusionTool::set_output_boxes()
{
  // mark as no-output and should be filled with tets,
  // any box containing a surface point
  // any box
  {
    std::vector<BoxTreeNode*> neighbors;
    BTILeaf bti( _bt );
    for ( BoxTreeNode *b = bti.get(); b != 0; b = bti.next() )
    {
      if ( is_tet_box(b) )
      {
        b->tet_box(true);
        b->output_hex(false);
      }
      //debug
//      else
//      {
//        std::cout << " .";
//        std::cout.flush();
//      }
    }
  }
}

void BoxSurfaceInclusionTool::gather_box_tet_faces(BoxFacesVec &box_faces, BoxFacesVecVec &domain_sides, BoxFacesVec &imprint_faces, const bool exactly_two_triangles )
{
  // for all boxes that we will tet mesh (a "tex box")
  //   for all six neighbors,
  //     if neighber is not a tet box (e.g. is the domain boundary)
  //       gather that face

  // for now, see if cubit can stitch the quads together to make a closed surface for us without us having to worry about it
  std::vector<BoxTreeNode*> neighbors;
  domain_sides.resize(6);

  // gather box and face pairs to write
  // if exactly_two_triangles, then only gather the faces of hex boxes next to tet boxes into box_faces
  BTILeaf bti( _bt );
  for ( BoxTreeNode *b = bti.get(); b != 0; b = bti.next() )
  {
    if ( b->tet_box() )
    {
      for (int f = 0; f < 6; ++f)
      {
        neighbors.clear();
        b->find_leaf_neighbors(f, neighbors);
        // if there are no neighbors, we are on the domain boundary, and output face
        if ( neighbors.empty() )
        {
          // double check geometry
          Point center = b->face_center(f);
          assert(
                 center.x == _bt->get_domain().corner_min().x ||
                 center.x == _bt->get_domain().corner_max().x ||
                 center.y == _bt->get_domain().corner_min().y ||
                 center.y == _bt->get_domain().corner_max().y ||
                 center.z == _bt->get_domain().corner_min().z ||
                 center.z == _bt->get_domain().corner_max().z
                 );
          
          
          domain_sides[f].push_back( std::make_pair(b,f) );
        }
        // use only smaller of this and my neighbor's face, or this if the same size
        else if (neighbors.size() > 1 )
        {
          for (size_t j = 0; j < neighbors.size(); ++j)
          {
            BoxTreeNode *n = neighbors[j];
            if ( !n->tet_box() )
            {
              if (!exactly_two_triangles)
                box_faces.push_back( std::make_pair( n, Box::opposite_face(f) ) );
            }
            else
            {
              imprint_faces.push_back( std::make_pair( n, Box::opposite_face(f) ) );
            }
          }
        }
        else // one neighbor, it might be bigger, so use this box,
        {
          assert( neighbors.size() == 1 );
          BoxTreeNode *n = neighbors[0];
          if ( !n->tet_box() )
          {
            if (!exactly_two_triangles)
              box_faces.push_back( std::make_pair( b, f ) );
          }
          else
          {
            imprint_faces.push_back( std::make_pair( b, f ) );
          }
        }
      }
    }
    // hex box, not a tet box
    else
    {
      for (int f = 0; f < 6; ++f)
      {
        neighbors.clear();
        b->find_leaf_neighbors(f, neighbors);
        // if there are no neighbors, we are on the domain boundary, and we don't need to output that face
        bool has_tet_neighbor(false);
        for (size_t j = 0; j < neighbors.size(); ++j)
        {
          BoxTreeNode *n = neighbors[j];
          if ( n->tet_box() )
            has_tet_neighbor = true;
          else
            imprint_faces.push_back( std::make_pair(b, f) );
        }
        if (has_tet_neighbor && exactly_two_triangles)
          box_faces.push_back( std::make_pair( b, f ) );
      }
    }
  }
  
  // remove duplicates
  // the faces of larger neighbor boxes are listed four times each...
  uniquify_vec_ref( box_faces );  // doesn't matter what sorting criteria is used
  uniquify_vec_ref(imprint_faces); // still might have a face twice, once for each box, but in opposite directions. this is not a problem since we never need to merge imprint faces, just use them to imprint.
  // domain sides should already be unique - there is only one box on the interior of the domain
}


// write out the faces of boxes bounding the shell around the tetrahedra
void BoxSurfaceInclusionTool::write_box_tet_faces( BoxFacesVec &box_faces, std::string fname, const double scale )
{
  std::cout << "Writing hex-tet interface quads of boxes to cubit .facet file " << fname << "... ";
  std::cout.flush();

  size_t num_faces = box_faces.size();
  size_t num_vertices = box_faces.size() * 4;
  std::cout << num_vertices << " vertices and " << num_faces << " quads... ";
  std::cout.flush();

  // open file
  // erases any old data
  std::fstream file(fname.c_str(), std::ios::out);
  
  // header
  file << num_vertices << " " << num_faces << std::endl;
  
  // vertex coordinates
  // numbering starts at 0
  // vertices
  Point nodes[4];
  for ( size_t i = 0; i < box_faces.size(); ++i )
  {
    BoxTreeNode *b = box_faces[i].first;
    const int f = box_faces[i].second;
    
    b->face_nodes( f, nodes );
    for (size_t j = 0; j < 4; ++j)
    {
      Point *p = &nodes[j];
      file << 4*i + j << "   " << scale*p->x << " " <<  scale*p->y << " " <<  scale*p->z << "\n";
    }
  }

  // quad faces
  for ( size_t i = 0; i < box_faces.size(); ++i )
  {
    file << i << "  " << 4*i << " " << 4*i + 1 << " " << 4*i + 2 << " " << 4*i + 3 << "\n";
  }
  
  file.flush();
  
  std::cout << " done." << std::endl;

}

void imprint_all_hack( std::fstream &cubit_script_file )
{
  cubit_script_file << "cubit.cmd('import facets \"box_imprint.facet\"')\n";
  cubit_script_file << "dummy_imprint_id = cubit.get_last_id(\"body\")\n";
  cubit_script_file << "cubit.cmd('group \"dummy_imprint\" equals body ' + str(dummy_imprint_id) )\n";
  cubit_script_file << "cubit.cmd('imprint all')\n"; //  feature_angle " << dihedral_threshold << "  stitch')\n";
  cubit_script_file << "cubit.cmd('delete body in dummy_imprint')\n";
}

void imprint_self_hack( std::fstream &cubit_script_file )
{
  cubit_script_file << "cubit.cmd('brick wid 1')\n";
  cubit_script_file << "dummy_imprint_id = cubit.get_last_id(\"body\")\n";
  cubit_script_file << "cubit.cmd('group \"dummy_imprint\" equals body ' + str(dummy_imprint_id) )\n";
  cubit_script_file << "cubit.cmd('body str(dummy_imprint_id) move 0 0 -10')\n";
  cubit_script_file << "cubit.cmd('imprint all')\n"; //  feature_angle " << dihedral_threshold << "  stitch')\n";
  cubit_script_file << "cubit.cmd('delete body in dummy_imprint')\n";
}

// if exactly_two_triangles == true, then caller has balanced the tree so that a face of a hex box on the tet interface has no need for imprints, and can be immediately split into two triangles.
void BoxSurfaceInclusionTool::tri_tet_inclusion_surface( const double tri_edge_length, const bool exactly_two_triangles )
{
  
  //==== preamble
  std::fstream cubit_script_file("cubit_inclusion_mesh.py", std::ios::out);
  cubit_script_file << "# python script file to run inside cubit 14.1 or 14.0\n";
  cubit_script_file << "# dgm mesh, to create tet mesh of domain interior\n";
  cubit_script_file << "# cubit.cmd('label surface name')\n"; //comment out, too slow
  cubit_script_file << "cubit.cmd('set developer commands on')\n";
  
  // order triangulations by layer from top z=0 to bottom z=domain.max_x
  std::vector<int> is_closed; // is triangulation a closed shell, or does in interect the domain bdy? (in z order)

  //==== sort triangulations by z depth, shallowest to deepest
  {
    std::vector<int> z_order;
    std::vector<int> local_closed;
    sort_triangulations_by_z( _triangulations, local_closed, z_order );
    std::vector<Triangulation*> t_by_z;
    for (size_t ti = 0; ti < _triangulations.size(); ++ti)
    {
      size_t tj = z_order[ti];
      t_by_z.push_back(  _triangulations[ tj ] );
      is_closed.push_back( local_closed[ tj ] );
    }
    _triangulations.swap(t_by_z);
  }
  // count how many span the xy-extent of the domain, and how many are closed
  int num_closed = 0;
  for (size_t ti = 0; ti < _triangulations.size(); ++ti)
  {
    if (is_closed[ti])
      ++num_closed;
  }
  int num_span = (int) _triangulations.size() - num_closed;
  
  //==== split box faces into upper and lower faces, label them
  set_output_boxes();
  BoxFacesVec box_faces; // sides 0..5
  BoxFacesVecVec box_faces_domain_bdy;
  BoxFacesVec imprint_faces;
  gather_box_tet_faces(box_faces,box_faces_domain_bdy,imprint_faces, exactly_two_triangles);
  BoxFacesVecVec box_faces_per_T;
  sort_box_tet_faces( box_faces_per_T, is_closed, box_faces );
  
  //==== write faces to imprint against
  write_box_tet_faces(imprint_faces, "box_imprint.facet" );

  //==== write the box faces between layers
  std::string box_tet_faces_fname = "box_tet_faces";
  std::vector<std::string> box_faces_per_T_fname;
  for (size_t i=0; i < box_faces_per_T.size(); ++i)
  {
    box_faces_per_T_fname.push_back( box_tet_faces_fname + "_" + std::to_string(i) + ".facet" );
  }
  for (size_t i=0; i < box_faces_per_T.size(); ++i)
  {
    // for each box_faces_per_T, write out with the right name if not empty, and set the script to put it with the right triangulation
    if ( !box_faces_per_T[i].empty() )
    {
      write_box_tet_faces(box_faces_per_T[i], box_faces_per_T_fname[i]);
    }
  }
  
  //==== imprint triangulated inclusion surface boundary on the domain boundary
  // create mesh files of side surfaces, without block boundaries, typically 1 surface per side
  // write the box faces on the domain sides
  // read domain side faces, imprint and merge, write them out, then read them back in as single surfaces without any block imprints
  cubit_script_file << "# create smooth side faces of the domain, without unnecessary box imprints.\n";
  std::vector<std::string> fname_side_exo;
  for (size_t f = 0; f < 6; ++f )
  {
    fname_side_exo.push_back( box_tet_faces_fname + "_side" + std::to_string(f) + ".exo" );
    if (!box_faces_domain_bdy[f].empty())
    {
      std::string fname    ( box_tet_faces_fname + "_side" + std::to_string(f) + ".facet" );
      write_box_tet_faces(box_faces_domain_bdy[f], fname);
      
      cubit_script_file << "\n# making conformal triangle mesh for mesh-based geometry. Side " << f << "\n";
      cubit_script_file << "cubit.cmd('reset')\n";
      cubit_script_file << "cubit.cmd('import facets \"" << fname << "\"')\n"; //  feature_angle " << dihedral_threshold << "  stitch')\n";
      imprint_all_hack( cubit_script_file );
      cubit_script_file << "cubit.cmd('merge vertex all')\n";
      cubit_script_file << "cubit.cmd('merge curve all')\n";
      cubit_script_file << "cubit.cmd('surface all scheme trimesh')\n";
      cubit_script_file << "cubit.cmd('curve all interval 1')\n";
      cubit_script_file << "cubit.cmd('mesh surface all')\n";
      cubit_script_file << "cubit.cmd('block 1 surface all')\n";
      cubit_script_file << "cubit.cmd('export mesh \"" << fname_side_exo[f] << "\" dimension 3 block 1 overwrite')\n";
      // to retrieve, do
      // if (!box_faces_domain_bdy[f].empty())
      //   cubit_script_file << "cubit.cmd('import mesh geometry \"" << fname_side_exo[f] << "\" feature_angle 135  merge')\n"; //zzyk exo
    }
  }
  cubit_script_file << "\ncubit.cmd('reset')\n";
  
  
  //==== imprint tet boundary *not* on the domain boundary
  std::vector<std::string> fname_layer_exo;
  for (size_t i=0; i < box_faces_per_T.size(); ++i)
  {
    fname_layer_exo.push_back( box_tet_faces_fname + "_layer_" + std::to_string(i) + ".exo" );
  }
  // for each box_faces_per_T, write out with the right name if not empty, and set the script to put it with the right triangulation
  if (exactly_two_triangles)
  {
    cubit_script_file << "\n# Preparing faces of the non-hex boxes that bound the triangulation void and domain.\n";
    if ( exactly_two_triangles )
    {
      cubit_script_file << "# Exactly_two_triangles == TRUE\n";
      cubit_script_file << "# No need for box imprints, interface faces are already conformal.\n";
    }
    else
    {
      cubit_script_file << "# Exactly_two_triangles == FALSE\n";
      cubit_script_file << "# Cubit can't handle hanging nodes, so we will make box sides conformal through imprint and merge.";
    }
    for (size_t i=0; i < box_faces_per_T.size(); ++i)
    {
      // for each box_faces_per_T, write out with the right name if not empty, and set the script to put it with the right triangulation
      if ( !box_faces_per_T[i].empty() )
      {
        cubit_script_file << "\n# Preparing box faces before layer " << i << "\n";
        cubit_script_file << "cubit.cmd('reset')\n";
        // keep the faces as separate surfaces, but make the mesh connected along their edges
        cubit_script_file << "cubit.cmd('import facets \"" <<  box_faces_per_T_fname[i] << "\"";
        if (exactly_two_triangles)
        {
          cubit_script_file << "')\n";
          cubit_script_file << "# Splitting interface quads into exactly two triangles\n";
        }
        else
        {
          cubit_script_file << " feature_angle 0  stitch')\n";
          imprint_all_hack( cubit_script_file );
        }
        cubit_script_file << "cubit.cmd('merge vertex all')\n";
        cubit_script_file << "cubit.cmd('merge curve all')\n";
        cubit_script_file << "cubit.cmd('surface all scheme trimesh')\n";
        cubit_script_file << "cubit.cmd('curve all interval 1')\n";
        cubit_script_file << "cubit.cmd('mesh surface all')\n";
        cubit_script_file << "cubit.cmd('block 1 surface all')\n";
        cubit_script_file << "cubit.cmd('export mesh \"" << fname_layer_exo[i] << "\" dimension 3 block 1 overwrite')\n";
      }
    }
  }
  // to retrieve, do
  // if ( !box_faces_per_T[i].empty() )
  //   cubit_script_file << "cubit.cmd('import mesh geom \"" << fname_layer_exo[i] << "\" feature_angle 0 ')\n"; //zzyk exo

  cubit_script_file << "\ncubit.cmd('reset')\n";


  
  //==== write out in-memory triangulated surfaces in z order as facet files
  const std::string t_name = "inclusion_surface_triangulation_";
  std::vector< std::string > t_names; // names of triangulation surfaces in cubit
  std::vector< std::string > tri_surf_fname; // names of triangulation surfaces facet files
  for (size_t i = 0; i < _triangulations.size(); ++i)
  {
    TriangulationTool TT( _triangulations[ i ] );
    t_names.push_back( t_name + std::to_string(i) );
    tri_surf_fname.push_back( t_names.back() + ".facet" );
    TT.write_facet(tri_surf_fname.back());
  }
  // to recover
  // cubit_script_file << "cubit.cmd('import facets \"" << tri_surf_fname[i] << "\" feature_angle 135  merge')\n";

  //==== cubit read in smooth, single-surface triangulated sides of the domain,
  cubit_script_file << "\n# reading smooth side faces of the domain.\n";
  for (size_t f = 0; f < 6; ++f )
  {
    if (!box_faces_domain_bdy[f].empty())
    {
      cubit_script_file << "old_surf_id = cubit.get_last_id(\"surface\")\n";
      cubit_script_file << "cubit.cmd('import mesh geometry \"" << fname_side_exo[f] << "\" feature_angle 135  merge')\n";
      cubit_script_file << "new_surf_id = cubit.get_last_id(\"surface\")\n";
      cubit_script_file << "cubit.cmd('surface ' + str(old_surf_id+1) + ' to ' + str(new_surf_id) + ' name \"domain_bdy_f" << f << "\"')\n";
    }
    cubit_script_file << "cubit.cmd('group \"g_domain_bdy_f" << f << "\" equals surface with name \"domain_bdy_f" << f << "\"')\n";
  }
  // surface names   domain_bdyf0--5
  // group         g_domain_bdyf0--5
  
  //==== cubit read in triangulated surfaces
  {
    cubit_script_file << "# importing triangulations as surfaces in ascending z-coordinate order\n";
    for (size_t ti=0; ti < _triangulations.size(); ++ti)
    {
      cubit_script_file << "t_id_begin = cubit.get_last_id(\"surface\") + 1\n";
      cubit_script_file << "cubit.cmd('import facets \"" << tri_surf_fname[ti] << "\" feature_angle 135  merge')\n";
      cubit_script_file << "t_id_end = cubit.get_last_id(\"surface\")\n";
      cubit_script_file << "cubit.cmd('surface ' + str(t_id_begin) + ' to ' + str(t_id_end) + ' name \"" << t_names[ti] << "\"')\n";
      cubit_script_file << "cubit.cmd('group \"g_" << t_names[ti] <<  "\" equals surface with name \"" << t_names[ti] << "\"')\n\n";
      //  cubit_script_file << "id = cubit.get_entity_from_name(\"t0*\")\n";  // id from name
      //  cubit_script_file << "name = cubit.get_entity_name(\"surface\", t0_id )\n";  // name from id
    }
  }
  // command might be useful
  // cubit_journal_file << "simplify Surface " << triangulation0_id << " Respect Vertex "; id...
  
  
  // face normals of boxes meet at either 0 or pi/2,
  // to explore: I think we want to split the surface at the pi/2 angles
  // const double dihedral_threshold = 135; // cubit uses degrees
  // except for the import facets command, all else is just to keep track of the imported faces

  //==== imprint and merge the triangulation surfaces: the material surfaces, the domain sides, and the box faces
  cubit_script_file << "cubit.cmd('# imprinting and merging the faceted geoemtry, for a contiguous mesh')\n";
  
  //== import hex-tet interface triangles
  // import the faces that are above some triangulation, and those below
  cubit_script_file << "\n# importing hex-tet interface, the faces of the non-hex boxes that bound the triangulation void and domain.\n";
  for (size_t i=0; i < box_faces_per_T.size(); ++i)
  {
    // for each box_faces_per_T, write out with the right name if not empty, and set the script to put it with the right triangulation
    if ( !box_faces_per_T[i].empty() )
    {
      cubit_script_file << "old_surf_id = cubit.get_last_id(\"surface\")\n";
      cubit_script_file << "cubit.cmd('import mesh geom \"" << fname_layer_exo[i] << "\" feature_angle 0  merge')\n";
      cubit_script_file << "new_surf_id = cubit.get_last_id(\"surface\")\n";
      cubit_script_file << "cubit.cmd('surface ' + str(old_surf_id+1) + ' to ' + str(new_surf_id) + ' name \"hex_tet_faces_" << i << "\"')\n";
      // box faces in layer i all have the name "hex_tet_faces_<i>" and are in a group called "g_hex_tet_faces_i"  for i = 0..num_tet_layers. i=0 goes before triangle layer 1
      // these used to be called vz0 and vz5
    }
    cubit_script_file << "cubit.cmd('group \"g_hex_tet_faces_" << i << "\" equals surface with name \"hex_tet_faces_" << i << "\"')\n";
    
  }
  // group g_hex_tet_faces_<i>
  cubit_script_file.flush();
  
  cubit_script_file << "\ncubit.cmd('imprint all')\n";

  // re-read hex-tet box face mesh
  cubit_script_file << "\n# imprint all just deleted all the mesh on the hex-tet box faces, and lost all their names and groups!\n"
                    << "# Read the mesh in again and restore names and groups.\n";
  for (size_t i=0; i < box_faces_per_T.size(); ++i)
  {
    if ( !box_faces_per_T[i].empty() )
    {
      cubit_script_file << "cubit.cmd('group \"pre_meshed\" equals surface meshed')\n"; // already mesh surfaces
      cubit_script_file << "cubit.cmd('import mesh \"" << fname_layer_exo[i] << "\" ')\n";
      cubit_script_file << "cubit.cmd('group \"post_meshed\" equals surface meshed')\n"; // already mesh surfaces
      cubit_script_file << "cubit.cmd('group \"just_meshed\" subtract pre_meshed from post_meshed')\n";
      cubit_script_file << "cubit.cmd('surface in just_meshed name \"hex_tet_faces_" << i << "\"')\n";
    }
    cubit_script_file << "cubit.cmd('group \"g_hex_tet_faces_" << i << "\" equals surface with name \"hex_tet_faces_" << i << "\"')\n";
  }
  // g_hex_tet_faces_<ti> for each triangulation is defined, but the group could be empty
  
  // gather the surfaces bounding the tets on each of the sides of the domain, and give them names
  cubit_script_file << "\n#we just split the domain side faces by the boundaries of the triangulated surfaces\n";
  cubit_script_file << "# unfortunately, facet-based imprinting does not propagate names!\n";
  cubit_script_file << "# find domain side surfaces again and assign names and group them in the script\n";
  cubit_script_file << "xmin = " << _s->min_x() << "\nymin = "<< _s->min_y() << "\nxmax = " << _s->max_x() << "\nymax = " << _s->max_y() << "\n";
  cubit_script_file << "zmin = " << _bt->get_domain().min_z() << "\nzmax = " << _bt->get_domain().max_z() << "\n";
  cubit_script_file << "last_s = cubit.get_last_id(\"surface\")\n";
  cubit_script_file << "for s in range(1,last_s+1):\n";
  cubit_script_file << "  n=cubit.get_entity_name(\"surface\",s)\n";
  cubit_script_file << "  # if surface exists\n";
  cubit_script_file << "  if n!=\"\":\n";
  cubit_script_file << "    ct = cubit.get_surface_centroid(s)\n";
  cubit_script_file << "    if abs(ct[0] - xmin) < xmax*1e-4:\n";
  cubit_script_file << "      cubit.cmd('surface ' + str(s) + ' name \"" << "domain_bdy_f4" << "\"')\n";
  cubit_script_file << "    elif abs(ct[0] - xmax) < xmax*1e-4:\n";
  cubit_script_file << "      cubit.cmd('surface ' + str(s) + ' name \"" << "domain_bdy_f2" << "\"')\n";
  cubit_script_file << "    elif abs(ct[1] - ymin) < ymax*1e-4:\n";
  cubit_script_file << "      cubit.cmd('surface ' + str(s) + ' name \"" << "domain_bdy_f1" << "\"')\n";
  cubit_script_file << "    elif abs(ct[1] - ymax) < ymax*1e-4:\n";
  cubit_script_file << "      cubit.cmd('surface ' + str(s) + ' name \"" << "domain_bdy_f3" << "\"')\n\n";
  cubit_script_file << "    elif abs(ct[2] - zmin) < zmax*1e-4:\n";
  cubit_script_file << "      cubit.cmd('surface ' + str(s) + ' name \"" << "domain_bdy_f0" << "\"')\n";
  cubit_script_file << "    elif abs(ct[2] - zmax) < zmax*1e-4:\n";
  cubit_script_file << "      cubit.cmd('surface ' + str(s) + ' name \"" << "domain_bdy_f5" << "\"')\n\n";
  // The remaining *quads* are in the box_faces_per_T sets, roughly speaking horizontal layers and bubbles.
  // But the triangulation surfaces are mixed in as well.
  
  // put named side surfaces into groups
  std::string g_domain_bdy_f_name = "g_domain_bdy_f"; //f0--5
  for (size_t f = 0; f < 6; ++f)
  {
    // for this cubit command, with name "name_string", means with name containing "name_string" as a substring!
    //    cubit_journal_file << "group \"" << g_domain_bdy_f_name << f << "\" equals surface with name \"domain_bdy_f" << f << "\" ";
    cubit_script_file << "cubit.cmd('group \"" << g_domain_bdy_f_name << f << "\" equals surface with name \"domain_bdy_f" << f << "\"')\n";
    // g_id1 = group of surfaces that are on domain side 1, etc.
    cubit_script_file << "g_id" << f << " = cubit.get_id_from_name(\"" << g_domain_bdy_f_name << f << "\")\n";
  }
  // g_id1 is the ids of the surfaces in group g_domain_bdy_f1, etc., 1..4
  // g_domain_bdy_f1 contains surfaces on domain boundary 1
  // all those surfaces have the name "domain_bdy_f1"
  
  cubit_script_file << "\n# gather vs<i> groups of surfaces, the domain-boundary surfaces bounding volume <i>\n";
  cubit_script_file << "# assume each surface intersects the domain boundary in a single topological circle, spanning the domain and splitting it into an above and a below, or not at all\n";
  
  // how many are there?
  cubit_script_file << "num_layers = len(cubit.get_group_surfaces( g_id1 ))\n";
  cubit_script_file << "num_layers_expected = " << num_span << "\n";
  cubit_script_file << "# assume all the other side face groups have the same number of layers after imprinting\n";
  cubit_script_file << "# closed shells should have no side layers assigned to them\n";
  cubit_script_file << "# beware hexed boxes splitting sides into different ranges\n"; // zzyk, test after other stuff is working
  
  cubit_script_file << "import numpy #for argsort\n\n";
  cubit_script_file << "# get domain boundary surfaces in sorted order by z-coorindate\n";
  for (size_t f = 1; f < 5; ++f)
  {
    // get all the surfaces on that side of the domain
    cubit_script_file << "s" << f << " = cubit.get_group_surfaces( g_id" << f << " )\n";
    // find their z centroid coordinate, to put into a tuple
    cubit_script_file << "zc=list()\n";
    cubit_script_file << "for i in s" << f << ":\n";
    cubit_script_file << "  ct = cubit.get_surface_centroid(i)\n";
    cubit_script_file << "  zc.append(ct[2])\n";
    cubit_script_file << "sz" << f << " = numpy.argsort(zc)\n";
    
    cubit_script_file << "# put surfaces into cubit groups by layer, vs0, vs1, vs2...\n";
    cubit_script_file << "for i in range(num_layers):\n";
    cubit_script_file << "  cubit.cmd('group \"vs' + str(i+1) + '\" add surface ' + str(s" << f << "[sz"<< f << "[i]]) ) \n";
  }
  // sz1 = box faces on the domain side 1, for 0..5
  // vs0 = box faces on the sides of the domain above triangulation 0, etc
  // vs1..num_triangulation_layers
  
  cubit_script_file << "\n# merge all\n";
  cubit_script_file << "cubit.cmd('merge vertex all')\n";
  cubit_script_file << "cubit.cmd('merge curve all')\n";

  
  // composite away some things ??
  
  //  cubit_journal_file << "surface all scheme trimesh\n";
  //  cubit_journal_file << "curve all interval 1\n";
  //  cubit_journal_file << "mesh surface all\n";
  //  cubit_journal_file << "block 1 surface all\n";
  //  std::string surf_meshes = "surface_meshes.exo";
  //  cubit_journal_file << "export mesh \"" << surf_meshes << "\" dimension 3 overwrite\n";
  
  cubit_script_file << "\n\n# meshing the contiguous geometry.\n";
  cubit_script_file << "cubit.cmd('surface all scheme trimesh')\n";
  cubit_script_file << "# todo: replace next line with some real sizing information.\n";
  //  cubit_script_file << "cubit.cmd('curve all interval 2')\n";
  cubit_script_file << "cubit.cmd('curve all size " << tri_edge_length <<" ')\n"; //
  cubit_script_file << "cubit.cmd('mesh surface all')\n";
  
  cubit_script_file << "# put surfaces in groups that enclose volumes, for those volumes bounded by the domain boundary\n";
  // from top z=0 downwards
  
  //==== first layer
  // top and side
  size_t ti = 0; //index 0..(num_triangulations-1)
  size_t vol_id = 0;
  
  // domain_bdy 0
  cubit_script_file << "cubit.cmd('group \"vol1\" add surface in g_domain_bdy_f0')\n";
  bool closed = is_closed[ ti ] > 0;
  
  bool is_elastic(true); // material type of layer. elastic above the first interface
  std::fstream zone_file("zone_elastic_inclusion_tet_exo.txt", std::ios::out);
  
  //==== layers
  while (ti <= _triangulations.size() && !closed)
  {
    ++vol_id; // numbered 1..n
    zone_file << vol_id << " " << (is_elastic ? "elastic" : "inclusion" ) << "\n";
    is_elastic = !is_elastic;
    
    if (ti>0)
    {
      cubit_script_file << "#add last bottom triangulation as top of this layer\n";
      cubit_script_file << "cubit.cmd('group \"vol" << vol_id << "\" add surface in g_" << t_names[ti-1] << "')\n";
    }
    
    // add sides
    cubit_script_file << "if num_layers != num_layers_expected:\n";
    cubit_script_file << "  print(\"Automatic layer assignment will fail. You must manually edit the next lines to assign vs<i> domain-side surfaces to the correct vol<j>\")\n";
    // Next line, if triggered, will show up as an error in the "Error" tab
    cubit_script_file << "  cubit.cmd('ERROR_Automatic_layer_assignment_will_fail._You_must_manually_edit_the_next_lines_to_assign_vs<i>_domain-side_surfaces_to_the_correct_vol<j>')\n";
    cubit_script_file << "cubit.cmd('group \"vol" << vol_id << "\" add surface in vs" << vol_id << "')\n";
    // add box hex-tet faces, could be internal or boundary
    cubit_script_file << "cubit.cmd('group \"vol" << vol_id << "\" add surface in g_hex_tet_faces_" << ti << "')\n";

    // add any enclosed shells
    closed = (ti < _triangulations.size()) && (is_closed[ ti ] > 0);
    while (closed)
    {
      cubit_script_file << "# enclosed shell surface triangulation\n";
      cubit_script_file << "cubit.cmd('group \"vol" << vol_id << "\" add surface in g_" << t_names[ti] << "')\n";
      ++ti;
//      cubit_script_file << "cubit.cmd('group \"vol" << vol_id << "\" add surface in g_hex_tet_faces_" << ti << "')\n"; // fixed after examples 0--4 were generated. Retest 04
      closed = (ti < _triangulations.size()) && (is_closed[ ti ] > 0);
    }
    // add bottom (next triangulation), if any
    if (ti < _triangulations.size())
      cubit_script_file << "cubit.cmd('group \"vol" << vol_id << "\" add surface in g_" << t_names[ti] << "')\n";
    else
    {
      // domain_bdy 5
      cubit_script_file << "cubit.cmd('group \"vol" << vol_id << "\" add surface in g_domain_bdy_f5')\n";
    }
    ++ti;
  }
  
  //===== add a volume for each closed shell, assuming they are not nested
  cubit_script_file << "# assign a volume for each closed shell surface\n";
  cubit_script_file << "# assumption: all closed shells enclose a single volume, and are not nested\n";
  is_elastic = true;
  for (size_t ti = 0; ti < _triangulations.size(); ++ti)
  {
    bool closed = (is_closed[ ti ] > 0);
    if ( closed )
    {
      ++vol_id;
      zone_file << vol_id << " " << (!is_elastic ? "elastic" : "inclusion" ) << "\n"; // is_elastic inside the shell is the opposite of its sandwiching layer
      cubit_script_file << "cubit.cmd('group \"vol" << vol_id << "\" add surface in g_" << t_names[ti] << "')\n";
      // add any enclosed boxes
      cubit_script_file << "cubit.cmd('group \"vol" << vol_id << "\" add surface in g_hex_tet_faces_" << (ti+1) << "')\n";
    }
    else
      is_elastic = !is_elastic;
  }
  
  // export surface meshes needed for each volume
  cubit_script_file << "# export surface meshes needed for each volume as a single block in an individual exodus file\n";
  std::string surf_meshes = "surface_meshes";
  cubit_script_file << "cubit.cmd('set  Default Block off')\n";
  for (size_t v = 1; v <= vol_id; ++v)
  {
    cubit_script_file << "cubit.cmd('reset block')\n";
    cubit_script_file << "cubit.cmd('block " << v << " surface in vol" << v << "')\n";
    cubit_script_file << "cubit.cmd('export mesh \"" << surf_meshes << "_" << v << ".exo\" dimension 3 overwrite')\n";
  }
  
  // now read in the surface triangle meshes as shells of volumes and tet mesh them one by one
  cubit_script_file << "\n# tet meshing\n# import the triangulation for each shell and tet mesh the interior\n";
  for (size_t v = 1; v <= vol_id; ++v)
  {
    cubit_script_file << "\ncubit.cmd('reset')\n";
    
    // import triangles on shells and tetemesh volumes
    cubit_script_file << "cubit.cmd('import mesh \"surface_meshes_" << v << ".exo\" no_geom')\n";
    cubit_script_file << "cubit.cmd('tetmesh tri all')\n";
    cubit_script_file << "cubit.cmd('create mesh geometry tet all')\n";
    
    // export mesh
    cubit_script_file << "cubit.cmd('reset block ')\n";
    cubit_script_file << "cubit.cmd('block 1 volume all')\n";
    cubit_script_file << "cubit.cmd('export mesh \"volume" << v << ".exo\" overwrite')\n";
  }
  
}


bool BoxSurfaceInclusionTool::balance_for_two_triangles()
{
  
  // balance so no hex boxes on the interface have hanging nodes
  class BalancerHexTetNoHanging : public Balancer
  {
  public:
    BalancerHexTetNoHanging(BoxTree*bt, BoxSurfaceInclusionTool *bst) : Balancer(bt), _bst(bst) {}
    BoxSurfaceInclusionTool *_bst = 0; // caller must assign
  protected:
    // the test function of whether to balance or not
    virtual bool balance_condition( BoxTreeNode *b, std::vector<BoxTreeNode*> &q )
    {
      assert( b->is_leaf() );
      const size_t q_old_size = q.size();
      
//      // debug
//      if ( b->diagonal() > Point(40, 45, 45))
//      {
//        std::cout << " debug this box ";
//        b->print2();
//      }
      
      if ( _bst->is_tet_box( b ) )
        return false;
      
      // else, I'm a hex box
      // Are any leaf neighbors tet boxes? If so, make sure I'm not bigger than a neighboring hex box
      
      // gather all
      std::vector<BoxTreeNode*> neighbors, big_neighbors;
      bool im_big(false);
      b->find_connected_boxes( neighbors, false );
      
      bool is_bdy = false;
      for (size_t i = 0; i < neighbors.size(); ++i)
      {
        BoxTreeNode *n = neighbors[i];
        assert( n->is_leaf() );
        if (_bst->is_tet_box( n ))
        {
          is_bdy = true;
        }
        else if ( n->diagonal() < b->diagonal() * 0.9 )
        {
          im_big = true;
        }
        else if ( n->diagonal() * 0.9 >  b->diagonal() )
        {
          big_neighbors.push_back(n);
        }
      }
      if (is_bdy)
      {
        // see if we can avoid balancing this hard
        // q.insert(q.end(), big_neighbors.begin(), big_neighbors.end());
        if (im_big)
          q.push_back(b);
        return (q.size() > q_old_size);
      }
      return false;
    }
  };
  
  // BalancerChain; balance_hang, balance_face // not implemented
  bool any_changed = false;
  bool changed = false;
  BalancerHexTetNoHanging balancer_hang(_bt,this);
  BalancerFace bf(_bt);
  do
  {
    changed = balancer_hang.balance();
    if (changed)
    {
      any_changed = true;
      changed = bf.balance();
      if (changed)
        any_changed = true;
    }
  } while (changed);
  return any_changed;
}


void BoxSurfaceInclusionTool::delete_triangulations()
{
  for (size_t i = 0; i < _triangulations.size(); ++i )
    delete _triangulations[i];
}
