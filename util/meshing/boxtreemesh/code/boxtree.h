//
//  boxtree.h
//  boxtree
//
//  Created by Mitchell, Scott A on 1/4/16.
//  Copyright (c) 2016 Sandia National Labs. All rights reserved.
//
// Store the actual tree, and primitives for splitting node, etc
// The *decisions* of which node to split, etc, are done elsewhere
//

#ifndef __BoxTreeMesh__boxtree__
#define __BoxTreeMesh__boxtree__

#include <stdio.h>
#include <iostream>
#include <vector>
#include <assert.h>
#include <limits.h>
#include "point.h"
#include "random.h"


// index into children
class Index
{
public:
  // shoud x,y,z be int or short? root could have a lot of children...
  // typedef short IndexScalar;
  int x, y, z;
  Index() : x(0), y(0), z(0) {}
  Index( int ix, int iy, int iz ) : x(ix), y(iy), z(iz) {}
  
  Index& operator++() { ++x; ++y; ++z; return *this;}
  Index& operator--() { --x; --y; --z; return *this;}
  Index& operator+=(const Index& o) { x+= o.x; y += o.y; z += o.z; return *this; }
  Index& operator+=(const int& i) { x+= i; y += i; z += i; return *this; }
  Index& operator=(const int& i) { x = i; y = i; z = i; return *this; }
  friend bool operator==(const Index& lhs, const Index& rhs) { return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z; }
  friend Index operator+(Index lhs, const Index& rhs) { lhs += rhs; return lhs; }
  friend Index operator+(Index lhs, const int rhs) { lhs += rhs; return lhs; }
  
  friend std::ostream& operator<<(std::ostream& os, const Index& ind);
};

inline
std::ostream& operator<<(std::ostream& os, const Index& ind)
{
  os << " x:" << ind.x << " y:" << ind.y << " z:" << ind.z;
  return os;
}

// index from root
typedef std::vector<Index> IndexVec;
typedef std::vector<int> IntVec;


// class-specific constants, made global so can really be constant
const int boxtree_MAXLEVEL = 12000; // used to represent infinity
const int boxtree_BIGLEVEL = 16; // debugging, flag boxes lower than this level
// 2^1024 is about 10^308...

// some non-trivial value smaller than smallest box, to avoid ties in queries
const double coordinate_DELTA = 1e-8;

enum SubBoxType {BOX, FACE, EDGE, NODE};

class WarpedFace; //forward

// Geometric box, independent of tree
class Box
{
  // ============================================
  // ==== construction
  // ============================================
public:
  Box() : _warped_face(0) {}
  Box( const Point& c_min, const Point& c_max ) : _warped_face(0)
  { _corner_min = c_min; _corner_max = c_max; }
  ~Box();

public:
  // don't copy the warped face!
  Box& operator=(const Box& b) { _corner_max = b._corner_max; _corner_min = b._corner_min; return *this; }

  static
  double rand()
  { return _random.generate_a_random_number(); }
  // =================
  // ==== data
  // =================

protected:
  // point at center, and the (positive) dx, dy, dz to the other corners
  // Point center, corner_offset;
  Point _corner_max, _corner_min;
  
  // one of the faces can be warped, typically face 0 or 5 moved up or down
  // affects coordinates of many nodes
  WarpedFace *_warped_face = 0;
  
  // index lookup tables
  static const int opposite_faces[6 /*face*/ ];  // opposite side of box
  // true if is a lower face, meaning in the negative direction along one of the tree coordinate axes.
  static const bool lower_face_lookup[6 /*face*/ ];
  
  // random number generator for use with box geometry
  static Random _random;
  
    // convert int f face direction into boolean about which axis direction
  static bool face_is_zp(int f) {return f==5;} // zp = z-axis, positive direction
  static bool face_is_zm(int f) {return f==0;}
  static bool face_is_xp(int f) {return f==2;}
  static bool face_is_xm(int f) {return f==4;}
  static bool face_is_yp(int f) {return f==3;}
  static bool face_is_ym(int f) {return f==1;}
  // convert axis direction into int f face direction
  static int  zp_to_face() {return 5;}
  static int  zm_to_face() {return 0;}
  static int  xp_to_face() {return 2;}
  static int  xm_to_face() {return 4;}
  static int  yp_to_face() {return 3;}
  static int  ym_to_face() {return 1;}

  // =================
  // ==== methods
  // =================
  
public:
  static bool test_lookups(); // test the lookup tables
  
  // == access corner positions
  Point  center()   const { return (_corner_max + _corner_min) * 0.5; };
  double center_x() const { return (_corner_max.x + _corner_min.x) * 0.5; };
  double center_y() const { return (_corner_max.y + _corner_min.y) * 0.5; };
  double center_z() const { return (_corner_max.z + _corner_min.z) * 0.5; };
  // diagonal = vector from min to max corner
  Point  diagonal() const { return _corner_max - _corner_min; }
  double diagonal_x() const {return _corner_max.x - _corner_min.x; }
  double diagonal_y() const {return _corner_max.y - _corner_min.y; }
  double diagonal_z() const {return _corner_max.z - _corner_min.z; }
  // corner_offset = vector from center to max corner
  Point  corner_offset() const { return (_corner_max - _corner_min) * 0.5; }
  const Point &corner_max()    const { return _corner_max; }
  const Point &corner_min()    const { return _corner_min; }
  double max_x() const { return _corner_max.x; }
  double min_x() const { return _corner_min.x; }
  double max_y() const { return _corner_max.y; }
  double min_y() const { return _corner_min.y; }
  double max_z() const { return _corner_max.z; }
  double min_z() const { return _corner_min.z; }

  // corners use the box coordinates
  Point corner(int c) const; // c in 0..7
  void  corners( Point corners[8]) const;
  void face_corners( int f, Point corners[4] ) const;

  // nodes use the warped faces, if any
  Point node(int c) const;  // c in 0..7
  void  nodes( Point nodes[8] ) const;
  void face_nodes( int f, Point nodes[4] ) const;
  Point face_center( int f ) const;
  Point random_face_point( int f ) const;
  // set the warped coordinate of an individual node.
  // This relies on warped face being already set.
  // Note only the one coordinate will change
  void update_node(int c, Point &new_coordinates);
  // nodes projected onto an xy plane, by removing the changed coordinate
  // face nodes are in counter-clockwise order around the face perimeter when viewed from above
  void projected_face_nodes( int f, Point nodes[4] );
  
  bool face_overlap_geometry( int face, Box *n );
  
  // set the warped face
  bool is_warped() const {return _warped_face;}
  int warped_face_id() const;
  void set_warped( int f, double c[4] );
  
  // == queries
  
  // does this box contain point?
  bool contains_point( const Point &q ) const
  { return q <= corner_max() && q >= corner_min(); }

  // does this box completely contain box?
  bool contains_box( const Box &q ) const
  { return q.corner_max() <= corner_max() && q.corner_min() >= corner_min(); }

  // does this box overlap with box?
  bool overlaps_box( const Box &q ) const
  { return q.corner_max() >= corner_min() && q.corner_min() <= corner_max(); }

  // is the center of this box close to c? useful for debugging
  bool center_close( Point c )
  { return c.is_close(center(), 0.1 * diagonal().length2() ); }

  // assuming q is connected by a face, edge, or node to this box, return true if it's *only* node connected
  bool node_connected( const Box &q ) const;

  static int opposite_face(int f) { return opposite_faces[f]; }
  static bool is_lower_face( int f ) { return lower_face_lookup[f]; }
  // return the coordinate of p, in the axis direction the face is normal to
  static double *changed_coordinate( int f, Point &p );
  static const double *changed_coordinate( int f, const Point &p );
  // for a box, rather than a point. Uses lower and upper.
  double *changed_coordinate(int f);
  
  // return a box that is a fattened version of the geometry of the face
  Box face_box(int f) const;
  // fattened version of self
  Box surrounding_box() const;
  
  // box with same center as this, but with edge lengths multiplied by scale_factor
  Box dilate_box(const double scale_factor) const;

  // debug
  // virtual
  void print() const;
};

// For a face of a box, we can override the x,y, or z coordinates of four nodes of the face
// without warping, a lot of face function are in Box
class WarpedFace
{
  int f; // which face
  double xyz[4]; // overridden coordinates
  // which face determines how to map the overridden coordinates

public:
  
  // constructor
  WarpedFace();
  WarpedFace( int fin, double xyzin[4] ) : f(fin)
  {
    xyz[0] = xyzin[0]; xyz[1] = xyzin[1]; xyz[2] = xyzin[2];
    xyz[3] = xyzin[3];
    assert( f >= 0 );
    assert( f < 6 );
  }
  ~WarpedFace()
  {
    f = -1;    
  }
  
  int get_f() const
  {
    assert( f >= 0 );
    assert( f < 6 );
    return f;
  }
  const double *get_xyz() const { return xyz; }
  double *set_xyz() { return xyz; }
  
  // return the coordinates of corner c of box, after warping by this
  Point corner( const Box *box, int c ) const;
  // x,y, or z coordinate to replace, depending on f
  double *changed_coordinate( Point &p ) const { return Box::changed_coordinate( f, p ); }
  bool is_lower_face() const {return Box::is_lower_face( f );}
  
  // return the index into the face array for the given faceid and corner
  static const int corner_i_lookup[6 /*face*/ ][8 /*corner*/];
  // return the index into the corner array for the given faceid and face array index
  static const int face_i_lookup[6 /*face*/ ][4 /*id in warpedface*/];
  // the above two are inverses of each other
  
};


// ============================================
// a box of the tree
// ============================================
// todo: pool memory manage BoxTreeNode
class BoxTreeNode : public Box
{
public:

  // ============================================
  // ==== construction
  // ============================================
  BoxTreeNode();
  ~BoxTreeNode();

  // = Children
  // Subdivide this box into the specified number of subboxes in each dimension
  void create_children( Index set_size );

 
  // ============================================
  // ==== geometry
  // ============================================
  // Primitives inherited from Box
  
  
  // =================
  // ==== data
  // =================
  // inherited from Box
  
  
  // =================
  // ==== methods
  // =================

public:
  
  // "find" means a potentially non-local search
  // "get" means an immediate child, parent, or somesuch
  
  // search for the box containing point
  // start the search at this box, but go up and down the tree
  // return the smallest box containing the point, with level >= level_limit. use boxtree_MAXLEVEL for no level limit
  BoxTreeNode* find_box(const Point &q, int level_limit = boxtree_MAXLEVEL);

  // find the immediate child containing the point.
  // if the point lies outside the box, still return one of the boxes, for robustness to roundoff issues
  int get_child_i(const Point& q)  { int i; Index ind; get_child(q,i,ind); return i; }
  Index get_child_ind(const Point& q)  { int i; Index ind; get_child(q,i,ind); return ind; }
  BoxTreeNode *get_child(const Point& q)  { int i; Index ind; return get_child(q,i,ind); }
  BoxTreeNode *get_child(const Point& q, int &i, Index &ind); // workhorse
  void get_children( std::vector<BoxTreeNode*> &childvec ); // appends

  // immediate children
  void get_child_overlap(std::vector<BoxTreeNode*> &boxes, const Box &query_box);
  // warning: if query_box is flat and aligned with a subdivision, you may not get the child you want
  BoxTreeNode *get_child_contains(const Box &query_box);

  
  // return all the leaf boxes that overlap the query box
  // if there is a level limit, then we will return a non-leaf box at that level
  // go up and down the tree
  void find_boxes_overlap(std::vector<BoxTreeNode*> &boxes, const Box &query, int level_limit = boxtree_MAXLEVEL) const;
  // just go down the tree, not up
  void find_leaf_child_overlap(std::vector<BoxTreeNode*> &boxes, const Box &query_box, int level_limit = boxtree_MAXLEVEL) const;

  // return the leaf box containing the query box
  // if there is a level limit, then we will return a non-leaf box at that level
  // go up and down the tree
  BoxTreeNode *find_box_contains(const Box &query_box, int level_limit = boxtree_MAXLEVEL);
  // just go down the tree, not up
  // I may return a non-leaf if the level limit is reached, or if a box contains the query box but none of its children do
  BoxTreeNode *find_leaf_child_contains(const Box &query_box, int level_limit = boxtree_MAXLEVEL);

  // debug
  // logical queries using geometry
  // slow compared to the logical ones, useful for verification of the logical queries
  BoxTreeNode *get_neighbor_by_geometry(int face);
  void find_leaf_neighbors_by_geometry(int face, std::vector<BoxTreeNode*> &neighbors);
  void face_leaf_children_by_geometry(int face, std::vector<BoxTreeNode*> &boxes);
  void face_children_by_geometry( int face, IntVec &kids );

  // actually useful
  // find neighbors, including those connected by a node or edge
  void find_connected_boxes(std::vector<BoxTreeNode*> &neighbors, const bool skip_node_neighbors, const int level_limit = boxtree_MAXLEVEL ) const;

  // debug
  //virtual
  void print2() const;

  
  // ============================================
  // ==== logical tree structure
  // ============================================

  // =================
  // ==== data
  // =================
  
  enum TetBox {UNKNOWN, NO, YES };
  TetBox get_is_tet_box() const {return _is_tet_box;}
  void set_is_tet_box( TetBox new_value ) { _is_tet_box = new_value; }

protected:
  TetBox _is_tet_box = UNKNOWN;
  
  int level;

  BoxTreeNode *parent;
  int birth_order; // which child of the parent am I?

  Index child_size; // number of children in each dimension
  BoxTreeNode *children; // internal representation is 1-d array
  int max_child; // 1 + linear index of the last child
  
  // =================
  // ==== methods
  // =================
public:

  // == access
  
  int get_level() const {return level;}
  
  // = parent
  
  BoxTreeNode *get_parent() const { return parent; }
  int get_birth_order() const {return birth_order;}
  Index get_birth_index() const
  { return (parent ? parent->int_to_index(birth_order) : Index()); }

  // = siblings

  // range of valid siblings
  // note the max is one more than the largest valid index
  // the min is zero
  int max_sibling_x() const { return (parent ? parent->child_size.x : 0);}
  int max_sibling_y() const { return (parent ? parent->child_size.y : 0);}
  int max_sibling_z() const { return (parent ? parent->child_size.z : 0);}
  static int min_sibling_x() { return 0; }
  static int min_sibling_y() { return 0; }
  static int min_sibling_z() { return 0; }

  // = children
  
  // leaf == no children
  bool is_leaf() const { return max_child == 0; }

  // children range
  Index get_child_size() const { return child_size; }
  int get_max_child() const { return max_child; }
  
  // child range checking
  bool in_child_range( Index index ) const;
  bool in_child_range( int i ) const;
  
  // immediate child
  BoxTreeNode *get_child( Index child_index ) const;
  BoxTreeNode *get_child( int child_int ) const;
  
  // descendent, for going deeper than one level
  // follow the vector of descendents from this downward
  BoxTreeNode *get_child(const IndexVec &iv) const;
  
  // get all the child boxes (or self) touching the specified face
  void face_leaf_children( int face, std::vector<BoxTreeNode*> &boxes); // pointers, leaves
  void face_children( int face, Index &i_first, Index &i_last );   // Index ranges, immediate children only
  void face_children( int face, IntVec &kids );                    // linear index, immediate children only

  // = neighbors
  
  // returns boxes the same size as this, or larger
  // if you want the smaller neighboring boxes, call find_leaf_neighbors
  // face is in 0..5
  BoxTreeNode *get_neighbor(int face);
  // BoxTreeNode *get_neighbor(Index index_increment);
  // xp = neighbor in x-coorinate direction, plus (increasing). xm is minus, etc
  BoxTreeNode *get_neighbor_xp();
  BoxTreeNode *get_neighbor_xm();
  BoxTreeNode *get_neighbor_yp();
  BoxTreeNode *get_neighbor_ym();
  BoxTreeNode *get_neighbor_zp();
  BoxTreeNode *get_neighbor_zm();

  // superface is true if the given face is split into multiple neighbor faces
  // subface is true if the neighbor face is a superface
  // if a face is shared by two leaves, i.e. same size as its neighbor, then both return false
  bool is_superface(int f);
  bool is_subface(int f);
  // return the neighbors
  bool is_superface(int f, std::vector<BoxTreeNode*> &n);
  bool is_subface(int f, BoxTreeNode* &n);

  // get the lowest level neighbors, sharing some portion of a mesh face with me
  void find_leaf_neighbors( std::vector<BoxTreeNode*> &neighbors ); // over all faces, but not nodes or edges... see find_connected_boxes
  void find_leaf_neighbors(int face, std::vector<BoxTreeNode*> &neighbors);

  // find other mesh elements sharing some portion of a mesh face with me
  // takes warped faces into account
  void find_mesh_neighbors(int face, std::vector<BoxTreeNode*> &neighbors);
  void print_neighbors( int f, std::vector<BoxTreeNode*> &nbh, bool use_id = false );

  void output_hex(bool set_output_hex) { _output_hex = set_output_hex; }
  bool output_hex() const { return _output_hex; }

  void discarded(bool set_discarded) { _discarded = set_discarded; }
  bool discarded() const { return _discarded; }

  void squished_hex(bool set_squished_hex) { _squished_hex = set_squished_hex; }
  bool squished_hex() const { return _squished_hex; }
  
  void tet_box(bool set_tet_box) { _tet_box = set_tet_box; }
  bool tet_box() const { return _tet_box; }
  
  // ============================================
  // ==== other
  // ============================================

  friend class BoxTree;
  friend class BoxTreeIterator;

  // =================
  // ==== data
  // =================
protected:
  
  // unsigned int goes up to about 4 billion
  unsigned int global_id;
  
  // should we output a hex for this box?
  // usually all leaves get a hex, unless deleted by a nearby surface
  bool _output_hex = true;
  // if we are outputting just a subset of the domain, then some hexes get discarded
  bool _discarded = false;
  // a hex is squished if we warped both its top and bottom face onto the surface, coincident
  bool _squished_hex = false;

  bool _tet_box = false;
  
  
public:
  enum Zone {UNSET, ACOUSTIC, ELASTIC, INCLUSION};
protected:
  Zone _zone = UNSET;
public:
  Zone get_zone() const {return _zone;}
  void set_zone( Zone zone ) {_zone=zone;}
  
  // =================
  // ==== methods
  // =================
protected:
  // if I'm the ith child of my parent, find the corresponding cousin index in my aunt's family.
  // E.g. parent has two children, I'm 2, aunt has 1 children, set child_i to the only child of aunt, return true
  // E.g. parent has one child, I'm 1, aunt has 2 children, return false, no unambiguous smaller neighbor, stop at aunt
  bool scale_child_index( int &child_i, int parent_child_size, int aunt_child_size );

public:
  
  // with no arguments, the id is set to a bad / flag value
  void set_id( unsigned int id = (long) -1) { global_id = id; }
  unsigned int get_id() const { return global_id; }

  // convert between linear and array indexing
  int index_to_int( const Index &index ) const;
  Index int_to_index( int i ) const;

};

// shorthand?? Should I just call the node the box?
//typedef BoxTreeNode Box;

// ============================================
// tree of boxes
// ============================================
class BoxTree
{
public:
  BoxTree();
  ~BoxTree();

  // if the domain is shrunk by throwing away boxes larger than some value, we must keep track of the new domain boundary
  Point _clipped_boundary;

protected:
  Box domain;
  
  unsigned int num_leaves=0, num_hexes=0;
  
public:
  int level_limit; // max leaf depth we're interested in generating
  
  BoxTreeNode *root;
  // root defines extent of space
  
  // methods
  // output the tree as a mesh of hexes, conformal
  BoxTreeNode *get_child(const IndexVec &iv) const
  {return root->get_child(iv);}
   
  void set_domain_size( Point set_min_corner, Point set_max_corner );
  const Box& get_domain() { return domain; }
  
  unsigned int get_number_hexes() const { return num_hexes; }
  void set_number_hexes( unsigned int n ) { num_hexes = n; }

  unsigned int get_number_leaves() const { return num_leaves; }
  void set_number_leaves( unsigned int n ) { num_leaves = n; }
  
};


// ============================================
// iterators
// ============================================
class BoxTreeIterator
{
public:
  BoxTreeIterator() : r(0), iv(), n(0) {}
  BoxTreeIterator(BoxTree* bt) : r(bt->root), iv(), n(bt->root) {}
  BoxTreeIterator(BoxTreeNode* b) : r(b), iv(), n(b) {}


  // get() and next() return 0 if at end

  // get the current position
  BoxTreeNode *get() const {return n;}
  // return position relative to the root of the tree
  const IntVec& get_iv() const { return iv; }
  IndexVec get_indexv() const;

  // reset the iterator
  virtual void reset() { iv.clear(); n = r; }
  // advance the iterator
  virtual BoxTreeNode *next();

  // returns true if the current value of get is nothing
  // bool is_end();
  
protected:
  // state data
  // should not be changed by outsiders
  IntVec iv;   // position relative to the root of the tree
  // n is current node. r is root of tree I'm running over
  BoxTreeNode *n, *r;
};

// all boxes
typedef BoxTreeIterator BTIAll;

// leaf boxes only
class BTILeaf : public BoxTreeIterator
{
public:
  BTILeaf(BoxTree* bt) : BoxTreeIterator(bt) { reset(); }
  BTILeaf(BoxTreeNode* b) : BoxTreeIterator(b) { reset(); }
  virtual void reset();
  virtual BoxTreeNode *next();
};

class BTIOutput : public BoxTreeIterator
{
public:
  BTIOutput(BoxTree* bt) : BoxTreeIterator(bt) { reset(); }
  BTIOutput(BoxTreeNode* b) : BoxTreeIterator(b) { reset(); }
  virtual void reset();
  virtual BoxTreeNode *next();
};

// =============================================
// BoxTreeNode inline functions
// =============================================
inline bool Box::node_connected( const Box &q ) const
{
  // it is only node connected if the fattened box contains only one of the corners
  // we don't know which box is bigger so check both ways
  
  // q covers corners of this?
  const Box bq = q.surrounding_box();
  size_t q_covers = 0;
  for ( int c = 0; c < 8; ++c )
    q_covers += (unsigned) bq.contains_point( corner(c) );
  assert( q_covers > 0 );
  if (q_covers > 1)
    return false;
  
  // this covers corners of q?
  const Box bb = surrounding_box();
  size_t this_covers = 0;
  for ( int c = 0; c < 8; ++c )
    this_covers += (unsigned) bb.contains_point( q.corner(c) );
  assert( this_covers > 0 );
  return (this_covers == 1);
}

inline BoxTreeNode::BoxTreeNode() :
level(-1), // bad value
parent(0), children(0), max_child(0), global_id( (long) -1), birth_order(0)
{}

inline
int BoxTreeNode::index_to_int( const Index &index ) const
{
  assert( in_child_range( index ) );
  // loops are x,y,z so z changes most rapidly, y second most, and x the least
  // int i = index.z + index.y * child_size.z + index.x * child_size.y * child_size.z;
  const int i = index.z + (index.y + index.x * child_size.y) * child_size.z;
  assert( in_child_range( i ) );
  // assert( index == int_to_index(i) ); // circular call
  return i;
}

inline
Index BoxTreeNode::int_to_index( int i ) const
{
  assert( in_child_range( i ) );
  int i_save(i);
  
  Index index;
  index.x = i / (child_size.y * child_size.z); // integer division
  i -= index.x * (child_size.y * child_size.z); // mod
  index.y = i / child_size.z;
  i -= index.y * child_size.z;
  index.z = i;
  
  assert( in_child_range( index ) );
  assert( i_save == index_to_int(index) ); // beware circular call
  return index;
}

inline
bool BoxTreeNode::in_child_range( Index index ) const
{
  return
  index.x < child_size.x && index.x >= 0 &&
  index.y < child_size.y && index.y >= 0 &&
  index.z < child_size.z && index.z >= 0;
}
inline
bool BoxTreeNode::in_child_range( int i ) const
{
  return i < get_max_child() && i >= 0;
}

inline
BoxTreeNode *BoxTreeNode::get_child( Index index ) const
{
  assert( in_child_range( index ) );
  //  return children[index.x][index.y][index.z];
  return get_child( index_to_int( index ) );
}
inline
BoxTreeNode *BoxTreeNode::get_child( int c ) const
{
  assert( in_child_range( c ) );
  return &children[c];
}

inline
void BoxTreeNode::get_children( std::vector<BoxTreeNode*> &childvec )
{
  // because children is an array of BoxTreeNodes, rather than an array of pointers,
  // the stride is different and
  // copying pointers to the children can't make use of std::vector insert, etc.
  childvec.reserve( childvec.size() + max_child );
  for (size_t i = 0; i < max_child; ++i )
  {
    childvec.push_back( &children[i] );
  }
}


inline
BoxTreeNode *BoxTreeNode::get_neighbor(int face)
{
  switch (face)
  {
    case 0:
      return get_neighbor_zm();
      break;
    case 1:
      return get_neighbor_ym();
      break;
    case 2:
      return get_neighbor_xp();
      break;
    case 3:
      return get_neighbor_yp();
      break;
    case 4:
      return get_neighbor_xm();
      break;
    case 5:
      return get_neighbor_zp();
      break;
    default:
      std::cerr << "invalid face index " << face << std::endl;
      return 0;
      break;
  }
}

inline
Point Box::corner(int c) const
{
  Point cp = _corner_min;
  switch (c)
  {
    case 6:
      cp.z = _corner_max.z;
      // no break;
    case 2:
      cp.y = _corner_max.y;
      // no break;
    case 1:
      cp.x = _corner_max.x;
      // no break;
    case 0:
      break;
      
    case 7:
      cp.z = _corner_max.z;
      // no break;
    case 3:
      cp.y = _corner_max.y;
      break;
      
    case 5:
      cp.x = _corner_max.x;
      // no break;
    case 4:
      cp.z = _corner_max.z;
      break;
      
    default:
      assert(0);
      break;
  }
  return cp;
}

inline
Point Box::node(int c) const
{
  if (_warped_face)
    return _warped_face->corner(this, c);
  return corner(c);
}

inline
void  Box::corners( Point corners[8]) const
{
  corners[0].x = min_x();
  corners[0].y = min_y();
  corners[0].z = min_z();

  corners[1].x = max_x();
  corners[1].y = min_y();
  corners[1].z = min_z();
  
  corners[2].x = max_x();
  corners[2].y = max_y();
  corners[2].z = min_z();

  corners[3].x = min_x();
  corners[3].y = max_y();
  corners[3].z = min_z();

  //
  corners[4].x = min_x();
  corners[4].y = min_y();
  corners[4].z = max_z();
  
  corners[5].x = max_x();
  corners[5].y = min_y();
  corners[5].z = max_z();
  
  corners[6].x = max_x();
  corners[6].y = max_y();
  corners[6].z = max_z();
  
  corners[7].x = min_x();
  corners[7].y = max_y();
  corners[7].z = max_z();
}

inline
void Box::nodes( Point nodes[8] ) const
{
  corners( nodes );
  if (_warped_face)
  {
    for (size_t i = 0; i < 4; ++i)
    {
      * _warped_face->changed_coordinate( nodes[ WarpedFace::face_i_lookup[ _warped_face->get_f() ][i] ] ) = _warped_face->get_xyz()[i];
    }
  }
}


// =============================================
// iterator inline functions
// =============================================

inline
void BTILeaf::reset()
{
  BoxTreeIterator::reset();
  if (n && !n->is_leaf())
    next();
  assert( get() == 0 || get()->is_leaf() );
}

inline
BoxTreeNode * BTILeaf::next()
{
  BoxTreeIterator::next();
  while ( n && !n->is_leaf() )
    BoxTreeIterator::next();
  assert( get() == 0 || get()->is_leaf() );
  return get();
}

inline
void BTIOutput::reset()
{
  BoxTreeIterator::reset();
  if (n && (!n->is_leaf() || !n->output_hex()))
    next();
  assert( get() == 0 || (get()->is_leaf() && get()->output_hex()) );
}

inline
BoxTreeNode * BTIOutput::next()
{
  BoxTreeIterator::next();
  while ( n && (!n->is_leaf() || !n->output_hex()))
    BoxTreeIterator::next();
  assert( get() == 0 || (get()->is_leaf() && get()->output_hex()) );
  return get();
}


// =============================================
// warped face inline functions
// =============================================
inline
Point WarpedFace::corner( const Box *box, int c ) const
{
  Point p = box->corner(c);

  int xyzi = corner_i_lookup[get_f()][c];
  if ( xyzi >= 0 )
    *changed_coordinate( p ) = get_xyz()[xyzi];

  return p;
}

inline
double * Box::changed_coordinate( int f, Point &p )
{
  switch (f)
  {
    case 0:
    case 5:
      return &p.z;
      break;
    case 1:
    case 3:
      return &p.y;
      break;
    case 2:
    case 4:
      return &p.x;
      break;
    default:
      return 0;
  }
  return 0;
}

// same, only return type differs
inline
const double * Box::changed_coordinate( int f, const Point &p )
{
  switch (f)
  {
    case 0:
    case 5:
      return &p.z;
      break;
    case 1:
    case 3:
      return &p.y;
      break;
    case 2:
    case 4:
      return &p.x;
      break;
    default:
      return 0;
  }
  return 0;
}

inline
double *Box::changed_coordinate(int f)
{
  return Box::changed_coordinate(f, is_lower_face(f) ? _corner_min : _corner_max );
}

inline Box::~Box()
{ delete _warped_face; _warped_face = 0; }


inline
void Box::set_warped( int f, double c[4] )
{
  assert(_warped_face==0);
  _warped_face = new WarpedFace(f, c);
}

inline
bool BoxTreeNode::is_superface(int f)
{
  std::vector<BoxTreeNode*> n;
  return is_superface(f,n);
}
inline
bool BoxTreeNode::is_superface(int f, std::vector<BoxTreeNode*> &n)
{
  find_leaf_neighbors(f, n);
  return (n.size() > 1);
}
inline
bool BoxTreeNode::is_subface(int f)
{
  BoxTreeNode *n;
  return is_subface(f, n);
}
inline
bool BoxTreeNode::is_subface(int f, BoxTreeNode* &n)
{
  n = get_neighbor(f);
  return (n && n->is_superface( opposite_face(f) ));
}

inline
int Box::warped_face_id() const {return (_warped_face ? _warped_face->get_f() : -1); }

inline
void Box::update_node(int c, Point &new_coordinates)
{
  if( !_warped_face )
    return; // ignore request
  int wc = WarpedFace::corner_i_lookup[_warped_face->get_f()][c];
  if ( wc < 0 )
    return; // ignore request
  _warped_face->set_xyz()[wc] = *changed_coordinate( _warped_face->get_f(), new_coordinates );
}


#endif /* defined(__BoxTreeMesh__boxtree__) */
