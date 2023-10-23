//
//  boxsurfaceinclusiontool.h
//  BoxTreeMesh
//
//  Created by Mitchell, Scott A on 5/3/16.
//  Copyright (c) 2016 Sandia National Labs. All rights reserved.
//

#ifndef __BoxTreeMesh__boxsurfaceinclusiontool__
#define __BoxTreeMesh__boxsurfaceinclusiontool__

#include <deque>

#include "boxsurfacetool.h"
#include "surfaceinclusion.h"
#include "triangulation.h"

// absolute value of dfference between a and b
template<typename T>
T abs_diff(T a, T b) {
  return a > b ? a - b : b - a;
}


class BoxSurfaceInclusionTool: public BSTool
{
  
public:
  
  BoxSurfaceInclusionTool(BoxTree *bt, SurfaceInclusion *s) :  BSTool(bt,s), _s(s) {}
  // only use this second form if we already have triangulations of the surface and we just want to re-use it.
  BoxSurfaceInclusionTool(BoxTree *bt, SurfaceInclusion *s, std::vector<Triangulation*> *triangulations) :  BSTool(bt,s), _s(s), _triangulations(*triangulations) {}
  
  void delete_triangulations();
  
  // consistency is key
  // make decision process robust in the face of errors

  // true if the surface cuts through the box
  // just uses the "points" of the surface, not any of its edges or triangles
  bool overlaps_surface_point( const Box *b ) const;

  // refine 
  //   refine boxes based on overlapping and a sizing function
  bool refine_near_surface( double box_max, double height_variation, Index child_size );
  bool would_refine_near_surface( double box_max, double height_variation );
  
  // balance
  //   for boxes overlapping the surface, corner-adjacent must be at most a factor-of-two different
  //   all boxes: factor of two for face-adjacent
  // mesh box face 
  //   find all smaller neighbor faces. 
  //   If neighbor is same size, switch to lexicographic smaller for consistency
  //   generate triangles for that face
  //      here is where we have to use the actual edges/triangles of the surface, not just the points
  // mesh box
  //   for each of the faces, mesh them into triangles
  //   pick a central point of the box
  //     snap it to the surface, if any
  //   attach central point to those triangles to form tets
  //   assign material
  //     determine whether the center of each tet is inside or outside the inclusion surface,
  //     by finding the closest grid point, then counting how many times the inclusion interface is crossed


  // warp box
  //   for each corner, 
  //     find the smallest box containing it
  //     if the corner is close to the surface compared to the smallest box size
  //     move the point away from the surface

  // oct 2016
  // meshing methods
  // connect manifolds -> create quad elements that connect up the surface into manifold surfaces
  //   do in advancing front
  // create triangulation of manifold, simply by adding a diagonal
  // decimate triangulation, based on a sizing function, leaving well-shaped triangles (we hope)
  // tetrahedralize the space between the triangulation and the box boundaries

  //============================ begin tri tet meshing  =====================
  // after connect manifolds, and refining and balancing the boxtree,
  // output the python scripts needed for cubit to generate the triangles and tets of the inclusion surface
  // the order of the triangulations in the vector will change, but not the set
  // if exactly_two_triangles == true, then caller has balanced the tree so that a face of a hex box on the tet interface has no need for imprints, and can be immediately split into two triangles.
  void tri_tet_inclusion_surface( const double tri_edge_length, const bool exactly_two_triangles = false );
  //========================= end tri tet meshing  =====================

  //============================ begin connect_manifolds =====================
  void connect_manifolds(); // sets std::vector<Triangulation*> _triangulations ;

  // sort the triangulations from top z=0 to bottom z=inf, those that do not hit the domain boundary are closed
  // is_closed is the indices in T of which triangulations are closed and which hit the domain boundary == open
  // new_order is the indices of T in vertical order, top (z=0) to bottom (z=max)
  // limitation: assumes open manifolds intersect the domain boundary in a simple circle
  //   a more general solution would build triangles on the domain boundaries, build shells by advancing front,
  //   then determine nesting of shells by shooting vertical rays.
  int triangulation_depth(std::vector<Triangulation*> &T, size_t i, size_t j, Point p);
  void sort_triangulations_by_z( std::vector<Triangulation*> &T, std::vector<int> &is_closed, std::vector< int > &new_order );
  
  // balance the boxtree so that every hex-tet interface quad gets split into exactly two triangles
  // return true if something changed
  bool balance_for_two_triangles();

protected:
    // mark all grid points as untriangulated
  template <class MarkType> class GridMark : public Grid
  {
  public:
    // upgrade a Grid to a GridMark. note copies grid rather than reference it
    GridMark( Grid g ) : Grid(g) 
    { 
      marks = ArrayFactory<MarkType>::new_array2(g.grid_x_size(), g.grid_y_size());
      for (size_t i = 0; i < grid_x_size(); ++i )
        for (size_t j = 0; j < grid_y_size(); ++j )
          marks[i][j] = 0;
    }
    ~GridMark() { ArrayFactory<MarkType>::delete_array2(marks); }
    MarkType **marks;
  };

  // 1 = meshed in a prior iteration, so node belongs to a different triangulation than the current one
  typedef GridMark<short> GridMeshed; // for each grid i,j 
  typedef std::vector<GridMeshed *> AllGridMeshed; // for each inclusion surface s

  // node for each surface point, in current triangulation
  typedef GridMark<Node*> GridNodes; // for each grid i,j
  typedef std::vector<GridNodes *> AllGridNodes; // for each inclusion surface s

  // constant used when determining if a box is close enough to the surface to be a tet box
  const double _proximity = 1.5;
  
  class FrontNode
  {
  public:
    size_t _si, _i, _j;
    Node *_node;
    FrontNode() :  _si(-1), _i(-1), _j(-1), _node(0) {}
    FrontNode( const AllGridNodes &agn, size_t si, size_t i, size_t j) :
    _si(si), _i(i), _j(j), _node( agn[si]->marks[i][j] )
    {}
    bool same_front_node( const FrontNode &f ) const 
    {
      return (_si == f._si && _i == f._i && _j == f._j);
    }

    bool differs_at_most_one( const FrontNode &f ) const
    {
      return ( abs_diff(_i, f._i) < 2 && abs_diff(_j, f._j) < 2 ); // doesn't check si
    }
    // true if front node is beyond the part of the grid we are meshing. Pass with _s
    bool domain_boundary( const Grid *g /* pass _s */ ) const
    {
      return ( /* _i == 0 || */ _i >= g->grid_x_size() ||
               /* _j == 0 || */ _j >= g->grid_y_size() );
    }

    // overload compare for sorting by index
    bool operator== (const FrontNode& right) const
    { return same_front_node(right); }
    // lexicographic compare,  _s, _i, _j, (skip _node)
    bool operator< (const FrontNode& right) const;

    void print() const;
    
  };
  
  // debug
  Node *_watch_me = 0;
  // set a watch point on the location pointed to by _watch_me
  // in xcode:
  // set a breakpoint where _watch_me is set
  // when code gets to that point, do in console
  //    (lldb) p _watch_me
  //    (int *) $0 = 0xbfffcbd8
  //    (lldb) w s e -- 0xbfffcbd8
  //    Watchpoint created: Watchpoint 1: addr = 0xbfffcbd8 size = 4 state = enabled type = w
  //    ..
  //    Watchpoint 1 hit:
  //    old value: 23023923980394
  //    new value: 52392304892309
  //    (lldb)

  
  // return the coordinates of f, regardless of whether there is a node
  Point grid_point(size_t s, size_t i, size_t j) const
  {
    assert( i< _s->grid_x_size() );
    assert( j< _s->grid_y_size() );
    Surface *ts = _s->_surfs[s];
    double q00 = ts->depth_ij(i,j);
    return Point( ts->xi2x(i),   ts->yi2y(j),   q00);
  }
  Point grid_point(const FrontNode &f) const
  {
    return grid_point(f._si, f._i, f._j);
  }
  // makes a new node at the grid point, and associates it with the grid 
  Node *new_grid_node(AllGridNodes &agn, Triangulation *T, size_t top_s, size_t i, size_t j)
  {
    assert( i< agn[top_s]->grid_x_size() );
    assert( j< agn[top_s]->grid_y_size() );
    Node *n00 = T->new_node( grid_point(top_s, i, j) );
    if (!n00) // likely that z-coordinate was a nan or infinite
      return 0;
    assert(agn[top_s]->marks[i][j] == 0); // call force instead if it might exist
    agn[top_s]->marks[i][j] = n00;
    assert( check_coordinates(agn, FrontNode(agn,top_s,i,j)) );
    return n00;
  }
  // makes a new node at the grid point, and associates it with the grid
  Node *new_grid_node(AllGridNodes &agn, Triangulation *T, FrontNode &fn)
  {
    Node *n = new_grid_node(agn, T, fn._si, fn._i, fn._j);
    fn._node = n;
    return n;
  }
  
  bool check_coordinates(AllGridNodes &agn, const FrontNode &f) const;

  // get versions of the above
  // could be null if point does not yet have a mesh node
  Node *get_node(AllGridNodes &agn, size_t top_s, size_t i, size_t j)
  { 
    assert( agn[top_s]->marks[i][j] == 0 || check_coordinates(agn, FrontNode(agn,top_s,i,j)) );
    return agn[top_s]->marks[i][j]; 
  } 
  Node *get_node(AllGridNodes &agn, const FrontNode &fn)
  { return agn[fn._si]->marks[fn._i][fn._j]; } 
  void refresh_node(AllGridNodes &agn, FrontNode &fn)
  { fn._node = get_node(agn,fn); }


  FrontNode get_front_node(AllGridNodes &agn, size_t top_s, size_t i, size_t j)
  { return FrontNode( agn, top_s, i, j); }

  Node *force_node(AllGridNodes &agn, Triangulation *T, FrontNode &fn)
  {
    refresh_node(agn, fn);
    if (!fn._node)
      new_grid_node(agn,T,fn);
    if (!fn._node)
      return 0;
    assert( check_coordinates(agn,fn) );
    return fn._node;
  }
  
  class FrontEdge : public Edge
  {
  public:
    // which inclusion surface sample point do I correspond to?
    FrontEdge( const FrontNode &fn0, const FrontNode &fn1, const FrontNode &fn_tri ) :
    _fn0(fn0), _fn1(fn1), _fn_tri(fn_tri), Edge( fn0._node, fn1._node ) {}
    FrontEdge() {}
    FrontNode _fn0;
    FrontNode _fn1;
    FrontNode _fn_tri; // if this FrontEdge is an edge of a triangle, _fn_other is the other node of that triangle
    const FrontNode &front_node( size_t i) const
    {
      return ( i==0 ? _fn0 : _fn1);
    }
    
    // overload compare for sorting by index
    // lexicographic on smaller edge node, larger edge node
    bool operator< (const FrontEdge& right) const;
    
    bool same_front_edge(const FrontEdge&fe) const
    // node coordinates
    // { return ( (_n0 == fe._n0 && _n1 == fe._n1 ) || (_n1 == fe._n0 && _n0 == fe._n1 ) ); }
    // front nodes
    { return ( (_fn0 == fe._fn0 && _fn1 == fe._fn1 ) || (_fn1 == fe._fn0 && _fn0 == fe._fn1 ) ); }
    bool operator== (const FrontEdge& right) const
    { return same_front_edge(right); }
    
    // true if the front edge hits the domain boundary, and we can't advance horizontally. Pass with _s
    bool domain_boundary( const Grid *g /* pass _s */ ) const
    {
      return ( ( (_fn0._i == _fn1._i) && (_fn0._i <= 0 || _fn0._i + 1 >= g->grid_x_size()) ) ||
               ( (_fn0._j == _fn1._j) && (_fn0._j <= 0 || _fn0._j + 1 >= g->grid_y_size()) ) );
    }

    // todo: this will fail (false positive) for sharp features.
    // todo: make a logical version of this, using indices! and replace
    // to use it, the caller must reconstruct the FrontNode, which is why I didn't do the logical form the first time
    // true if triangle(n0, n1, n3) and triangle(n0,n1,m3) logically cross,
    // as in the two ways to triangulate a quad having four triangles that cross
    static bool cross_triangles(const Point &p0, const Point &p1, const Point &n3, const Point &m3)
    {
      return ( 0.9 < Point::cos_dihedral(p0, p1, n3, m3 ) );
    }
    bool cross_triangles(const Point &n3, const Point &m3) const
    {
      return cross_triangles(*_fn0._node, *_fn1._node, n3, m3 );
    }
    // ( 0.9 < Point::cos_dihedral(*fn0._node, *fn1._node, *n2, grid_point(f)) )

    // add this to fes if it is not already in fes
    void push_back_uniqueFE( std::vector<FrontEdge> &fes ) const;
    
    // number of i,j, and si%2 indices that are not identical for the
    // three nodes (2 for edge, 1 passed in)
    // if the i index is not the same for all three, then add 1, same for j,
    // and for si, use difference of si mod 2
    int num_indices_different(const FrontNode &f) const;
    
    static
    bool is_horizontal(const FrontNode &a, const FrontNode &b)
    { return (abs_diff(a._si,b._si)%2==0 && abs_diff(a._i,b._i)<2 && abs_diff(a._j,b._j)<2); }
    bool is_horizontal() const
    { return is_horizontal(_fn0,_fn1); }

    static
    bool is_vertical(const FrontNode &a, const FrontNode &b)
    { return (a._i==b._i && a._j==b._j && (abs_diff(a._si,b._si)%2 == 1)); }
    bool is_vertical() const
    { return is_vertical(_fn0,_fn1); }

    static
    void classify_edge(const FrontNode &a, const FrontNode &b, bool &is_horiz, bool &is_vert)
    {
      is_vert = is_vertical(a,b);
      is_horiz = is_horizontal(a,b);
    }
    void classify_edge(bool &is_horiz, bool &is_vert)
    { classify_edge(_fn0,_fn1,is_horiz,is_vert); }
    
    // given vertical triangle this-b, find the horizontal edge and return it as f_above and f_side
    void find_below_node(const FrontNode &b, FrontNode &f_above, FrontNode &f_side, FrontNode &f_below) const;
    
    virtual void print() const;
    
  };
  
  bool check_coordinates(AllGridNodes &agn, const FrontEdge &fe) const
  {
    return
    check_coordinates(agn, fe._fn0) &&
    check_coordinates(agn, fe._fn1) &&
    check_coordinates(agn, fe._fn_tri);
  }


  // the "queue" of edges on the front
  class FrontEdges
  {
    // zzyk
    // todo: replace with a priority queue
    // put on with priority equal to value of best node, +1 for vertical, +2 for non-ball topology (low is best)
    // when popping, re-evaluate best node, and put back on queue if value is now greater than the next-best node
  public:
    typedef std::deque<FrontEdge> FEdeque;
    FrontEdge pop_front(bool &strict_requirements);

    bool empty() const
    {
      return _front.empty() && _front_vertical.empty() && _front_deferred.empty();
    }
    size_t size() const
    {
      return _front.size() + _front_vertical.size() + _front_deferred.size();
    }

    // call through BoxSurfaceTool to invoke extra checks
    void push_back(const FrontEdge &fe, bool is_vertical = false, bool is_deferred = false);
    
    void print() const;

  protected:
    FrontEdge pop_front( FEdeque &front )
    {
      assert( !front.empty() );
      FrontEdge fe = front.front(); // copy
      front.pop_front();
      return fe;
    }

    // data
    FEdeque _front;
    FEdeque _front_vertical;   // second_front -> rename as front_vertical
    FEdeque _front_deferred; // ones we can't fill currently, but should be filled

    // how many we've consecutively popped off front_deferred and enforced strict_requirements 
    // and was not able to generate a new triangle.
    long _num_consecutive_deferred = -1;

    // debugging data
    class PopStat
    {
    public:
      FrontEdge f;
      int which_queue;

      bool operator== (const PopStat& right) const
      { return ((f==right.f) && (which_queue == right.which_queue)); }
      // lexicographic compare,  _s, _i, _j, (skip _node)
      bool operator < (const PopStat& right) const;
    };
    std::vector<PopStat> all_pops;
    int _num_front = 0;
    int _num_deferred_0 = 0;
    int _num_deferred_1 = 0;
    int _num_vertical = 0;

  public:
    void print_all_pops() const;
    void print_queue() const;


  };
  
  // return whether triangle abc is horizontal (i.e. all TopInclusion or all BotInclusion)
  // or vertical (e.g. ab is horizontal and c is directly above/below a or b in the ij grid)
  // could be neither
  void classify_triangle(const FrontNode &a, const FrontNode &b, const FrontNode &c, bool &is_horizontal, bool &is_vertical);
  
  class NodePool
  {
  public:
    std::vector<FrontNode> candidates, good, valid;

    bool empty() const { return good.empty() && valid.empty(); }
  };

  class AdvanceContext
  {
  public:
    AllGridNodes agn;
    AllGridNodes agn_saved;
    AllGridMeshed ameshed;
    size_t top_s = -1;
    Triangulation *T = 0;
  };
  AdvanceContext ac; // used to connect manifolds, and later for searching if boxes intersect the surface

  bool find_flat_spot(AdvanceContext &ac, size_t top_s, size_t &flat_i, size_t &flat_j );
  void init_two_triangles(AdvanceContext &agn, size_t top_s, Triangulation *T, size_t flat_i, size_t flat_j, FrontEdges & front_edges);

  // Given a front edge, find the nodes that I can add to make a valid triangle
  //  other_cross returns true if there is some extant triangle of edge fn0,f that would cross triangle fn0,fn1,f (if formed)
  bool other_cross(const FrontNode & fn0, const FrontNode & fn1, const FrontNode & f); // test within candidate nodes

  bool _allow_far_index_triangles = false; // flag to use hack to try to get closure of last few open spots
  void convert_to_front_edges(AdvanceContext &ac, FrontEdges &front_edges, std::vector<Edge> &open_edges ); // convert edges to front edges, to try advancing again

  void candidate_nodes(AdvanceContext &ac, Triangle *t0, const FrontEdge &fe, NodePool &np );
  // given a candidate list of nodes for advancing on front edge fe=fn0,fn1 (or reversed 1,0) of triangle t0 = fe,n2
  // append to the vector of "valid" ones, meaning triangle fn0,fn1,n2 is well-formed
  // caller must clear valid_fn if desired, vet_candidates appends to valid_fn
  // Assumes that candidates were generated by changing one index of fn0, and was generated independent of fn1 and so must
  // be checked against it.
  // fe is an edge of t0 (may be NULL) and n2 is the other node of triangle t0
  void vet_candidates(AdvanceContext &ac, Triangle *t0, const FrontEdge &fe, const FrontNode &fn0, const FrontNode &fn1,
    NodePool &np);
  // return the best-valued node, based on triangle quality and surface angles and such
  // if the best one is in the valid but not the good pool, then return best_not_good flag
  // Recurse is a debugging flag. If true, it will recall itself once with verbose on in order to be able to debug its decision.
  FrontNode best_node(AdvanceContext &ac, Triangle *t0, const FrontEdge &fe, NodePool &np, bool &best_not_good, bool &best_too_long, bool recurse = true);
  // make and return a triangle using front edge fe and b.
  // return the third vertex as b, and whether the triangle is horizontal (connecting three top or three bottom surface nodes)
  Triangle *add_triangle_feb(AdvanceContext &ac,  FrontEdges &front_edges,
                             Triangle *t0, const FrontEdge &fe, FrontNode &b,
                             bool &is_horizontal, bool &is_vertical);
  
  // and fe to front_edges
  void push_back(AdvanceContext &ac, FrontEdges &front_edges, const FrontEdge &fe, bool is_vertical = false, bool is_deferred = false);
  // pop one
  FrontEdge pop_front(AdvanceContext &ac, FrontEdges &front_edges, bool &strict_requirements);

  void advance_front(AdvanceContext &ac, FrontEdges &front_edges, size_t manifold_id);

  void init_grid_nodes( AdvanceContext &ac );

  // When finished triangulating one manifold, 
  // clear/set the marks on surface points 
  // to get ready for meshing the next manifold
  void finalize_used_grid_marks(AdvanceContext &ac);
  
  bool previously_meshed( const AdvanceContext &ac, const size_t s, const size_t i, const size_t j ) const
  { return ( ac.ameshed[s]->marks[i][j] > 0 ); }
  bool previously_meshed( const AdvanceContext &ac, const FrontNode &f ) const
  { return previously_meshed(ac, f._si, f._i, f._j); }
  void set_previously_meshed( AdvanceContext &ac, size_t s, size_t i, size_t j, bool value )
  { ac.ameshed[s]->marks[i][j] = (short) value; }
  void set_previously_meshed( AdvanceContext &ac, const FrontNode &f, bool value )
  { ac.ameshed[f._si]->marks[f._i][f._j] = (short) value; }


  //============================ end connect_manifolds =====================

public:
  //============================ begin box-tet interface =====================
  
  // define which boxes will not be output, based on proximity to the inclusion surface
  bool is_tet_box(BoxTreeNode *b) const; // true if close enough to surface to use tets instead of hexes
  void set_output_boxes();
  
  // gather faces of boxes bounding the shell around the tetrahedra
  typedef std::pair< BoxTreeNode*, int > BoxFace;
  typedef std::vector< BoxFace > BoxFacesVec;
  typedef std::vector< BoxFacesVec > BoxFacesVecVec;
  // box_faces_domain_bdy are on the sides of the domain, 0..5
  // box_faces are somewhere interior to the domain, with a box that will have a hex outside it
  // if exactly_two_triangles is set, then we don't need to use the smaller box faces on the tet side, and can just use the big ones on the hex side of the hextet interface
  void gather_box_tet_faces(BoxFacesVec &box_faces, BoxFacesVecVec &box_faces_domain_bdy, BoxFacesVec &imprint_faces, const bool exactly_two_triangles = false);
  
  // for a vector from a random point on a box face bf, to the same xy but with z=-infinity
  // return the number of times the ray crosses a triangle of T
  // (which is identical for the reverse vector)
  int num_crossings_from_neg_infinity( BoxFace &bf, size_t t, int recursion_depth = 0 );


  // put box faces by the triangulation that it goes before
  // that is, the top faces, above the first surface, go into index 0 of box_faces_per_T
  void sort_box_tet_faces( BoxFacesVecVec &box_faces_per_T, std::vector<int> &is_closed, const BoxFacesVec &box_faces );
  
  // write out the faces of boxes
  void write_box_tet_faces( BoxFacesVec &box_faces, std::string fname = "box_tet_faces.facet", const double nodal_scale_factor = 1.0   );
  
  void assign_box_elastic_inclusion_zones(); // sets elastic or inclusion. won't overwrite acoustic

  //============================ end box-tet interface =====================

  
  
protected:
  
  bool refine_near_surface_implementation( double box_max, double height_variation, Index child_size, bool actually_refine );

  // data
  // BoxTree *_bt; // inherited from BoxTreeTool
  SurfaceInclusion *_s;
public:
  std::vector<Triangulation*> _triangulations;
  
public:
  // debug
  bool _verbose = false;
  void write_mesh(Triangulation*T, std::string fname, size_t id);

  friend class RefinerVSS;
};

// defines some sizing function over the xy space
class RefinerVSS : public Refiner
{
public:
  RefinerVSS(BoxSurfaceInclusionTool *bst) : Refiner(bst->_bt), _bst(bst) {}

  // refine a box if it overlaps (is cut by) the surface, and
  // at least one of these conditions are met:
  
  // refine a box if its diagonal is bigger than upper_size
  Point upper_size = Point(1000., 1000., 1000.);
  
  // refine a box if the surface varies more than height_variation within it
  // note height_variation is an absolute value, not relative to the box size
  double height_variation = 1000;
  
protected:
  // defines some sizing function over the xy space
  virtual bool refine_condition(BoxTreeNode *b);
  virtual bool refine_parameters_ok()
  {
    RefinerGridCheck rgc;
    return rgc.refine_parameters_ok(_bst->_bt, _bst->_s, child_size, upper_size);
  }
  BoxSurfaceInclusionTool *_bst;
};

inline
bool BoxSurfaceInclusionTool::refine_near_surface( double box_max, double height_variation, Index child_size )
{
  return refine_near_surface_implementation( box_max, height_variation, child_size, true);
}

inline
bool BoxSurfaceInclusionTool::would_refine_near_surface( double box_max, double height_variation )
{
  return refine_near_surface_implementation( box_max, height_variation, Index(2,2,2), false); // change to pass in child_size??
}

inline
int BoxSurfaceInclusionTool::FrontEdge::num_indices_different(const BoxSurfaceInclusionTool::FrontNode &f) const
{
  return
    (_fn0._i  != _fn1._i  || _fn0._i  != f._i ) +
    (_fn0._j  != _fn1._j  || _fn0._j  != f._j ) +
    ( (abs_diff(_fn0._si, _fn1._si) % 2 == 1) || (abs_diff(_fn0._si, f._si) % 2 == 1) );
}


#endif /* defined(__BoxTreeMesh__boxsurfaceinclusiontool__) */
