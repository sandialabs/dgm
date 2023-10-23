//
//  boxtreetool.h
//  BoxTreeMesh
//
//  Created by Mitchell, Scott A on 2/8/16.
//  Copyright (c) 2016 Sandia National Labs. All rights reserved.
//

#ifndef BoxTreeMesh_boxtreetool_h
#define BoxTreeMesh_boxtreetool_h

#include "boxtree.h"

// construction is lightweight

// given box b, return true if any neighbors need to be split
// those neighbors are returned in the vector
// boost::bind may be handy if there are additional parameters, such as how fine to split and allowed size differences
class BoxTreeTool;
typedef bool (BoxTreeTool::*BalanceFunction)(BoxTreeNode *b, std::vector<BoxTreeNode*> &neighbors_to_split );


class BoxTreeTool
{
public:
  BoxTreeTool(BoxTree*bt) : _bt(bt) {}
  BoxTreeTool() : _bt(0) {}
  
  // mark all hexes whose face f coordinate is bigger than the value defined by the domain fraction
  // as having no output hex.
  // calls assign_global_ids with clean_ids = true
  // return the number of discarded hexes
  size_t discard_hexes( int f, double domain_fraction );

  // if reset_ids is true, then any prior ids on non-leaves are overwritten with the bad / flag value
  void assign_global_ids( bool clean_ids = false );
  
  // for methods that write coordinates, they take a global "_write_corner_coords" flag,
  // if true, then write out the coordinates of the unwarped boxes, grid aligned orthogonal
  // if false, use the warped (e.g. snapped to surface) coordinates
  bool _write_corner_coords = false;
  
  // dgm file format
  // node coordinates will be multiplied by nodal_scale_factor on output
  void write_nodal_coordinates( std::string fname = "mesh.msh", const double nodal_scale_factor = 1.0 );
  void write_face_adjacencies( std::string fname = "mesh.con" );
  void write_boundary_conditions( std::string fname = "mesh.bc" );
  
  // off file format
  void write_off_file( std::string fname = "mesh.off", const double nodal_scale_factor = 1.0 );
  
  // cubit script to create free mesh
  void write_cubit_mesh_jou( std::string fname = "cubit_mesh.jou", const double nodal_scale_factor = 1.0 );

  // cubit facet file
  void write_box_facet( std::string fname = "box.facet", const double nodal_scale_factor = 1.0 );

  // ply file format
  void write_ply( std::string fname = "mesh.ply", const double nodal_scale_factor = 1.0);
  
  // cubit facet format, return full name of file written
  std::string write_box_face( const Box &box, int face, size_t id = 0, std::string fname = "box", const double nodal_scale_factor = 1.0 );  // writes "box0.facet"

  // print the sub box type as a string to the stream
  void print_sub_box_type( SubBoxType sub_box_type, std::ostream &o = std::cout );
  
  // be sure to assign the zones first!
  void write_box_zones( std::string fname_prefix );  

protected:
  // the tree I operate over
  BoxTree *_bt;
  
  void corners_or_nodes( BoxTreeNode *b, Point *nodes ); // 8 nodes
  
};


// Actual Refiners and balancers are defined as specialized version of base Refiner and Balancer 
// with overloaded refine and balance conditions.
// often we refine a boxtree based on some condition that depends on the surface
class Refiner
{
public:
  Refiner(BoxTree *bt) : _boxt(bt) {}
  virtual ~Refiner() {}

  // paramters
  Index child_size = Index(2,2,2);

  // interface
  // return whether the boxtree changed (or would change) because at least one box would be refined
  // refine actually changes the boxtree, would_refine just lets you know if a call to refine would actually change the boxtree
  bool refine()       { return refine_implementation( true ); }
  bool would_refine() { return refine_implementation( false); }

  // interface in case this is easier...
  bool refine_implementation(bool actually_refine);
protected:
  virtual bool refine_condition(BoxTreeNode *b) = 0;
  // print a warning if the refine condition combined with the specified parameters may cause problems
  virtual bool refine_parameters_ok() {return true;}

  BoxTree *_boxt;
  
  friend class RefinerChain;
};


class RefinerUniform: public Refiner
{
public:
  RefinerUniform(BoxTree *bt) : Refiner(bt) {}

  // refine a box if its diagonal is not smaller than upper_size
  Point upper_size = Point(1000., 1000., 1000.);
  
protected:
  virtual bool refine_condition(BoxTreeNode *b)
  {
//    if ( (b->diagonal() < upper_size) )
//    {
//      std::cout << "uniform refiner stopping with box diagonal ";
//      b->diagonal().print();
//    }

    return ! (b->diagonal() < upper_size);
  }
  // print a warning if the refine condition combined with the specified parameters may cause problems
  virtual bool refine_parameters_ok() {return upper_size > Point(1.,1.,1.); }
  
};


// refine if box center is inside the refinement box range
class RefinerBox: public RefinerUniform
{
public:
  RefinerBox(BoxTree *bt) : RefinerUniform(bt), centroid_range( Point(), Point() ) {}

  Box centroid_range; // defaults to both corners zero
  
protected:
  virtual bool refine_condition(BoxTreeNode *b)
  {
    bool r = centroid_range.contains_point( b->center() ) &&
             RefinerUniform::refine_condition(b);
    return r;
  }
};

// refines if any of the refiners in the chain would refine
class RefinerChain: public Refiner
{
public:
  RefinerChain(BoxTree *bt) : Refiner(bt) {}
  // owns these objects, will destruct them
  std::vector<Refiner*> chain;
  ~RefinerChain()
  {
    for (size_t i = 0; i< chain.size(); ++i)
      delete chain[i];
    chain.clear();
  }
  
  
protected:
  virtual bool refine_condition(BoxTreeNode *b)
  {
    for (size_t i = 0; i < chain.size(); ++i)
    {
      if (chain[i]->refine_condition(b) )
        return true;
    }
    return false;
  }
};



class Balancer
{
public:
  // constructor
  Balancer(BoxTree*bt) : _bt(bt), child_size(2,2,2) {}
  Balancer() : _bt(0) {}
  
  // parameter
  Index child_size;

  // Balance the tree by splitting boxes
  // so that boxes that share the specificied entity type are close to each other in size.
  // close means that a box edge in one is split into at most side_length_factor edges in its neighbors
  bool would_balance() {return balance_implementation(false);}
  bool balance() {return balance_implementation(true);}

  bool balance_implementation( bool actually_change );
  
protected:
  
  // the tree I operate over
  BoxTree *_bt;
  
  // the test function of whether to balance or not
  virtual bool balance_condition( BoxTreeNode *b, std::vector<BoxTreeNode*> &q ) = 0;

  // balance by splitting some of the neighbors, depending on the balance_condition.
  // Return the split neighbors in vector q, which are now no longer leaves.
  bool balance_neighbors( BoxTreeNode *b, std::vector<BoxTreeNode*> &q, bool actually_change );
  
  // implementation of several common types of balancing, based on edge and node neighbors
  bool balance_all_neighbors( BoxTreeNode *b, std::vector<BoxTreeNode*> &q, bool skip_node_neighbors);
  
  
  // b > bb
  bool bigger_xy( BoxTreeNode *b, BoxTreeNode *bb )
  {
    assert( b->is_leaf() ); // caller should check
    // by assumption, bb was a neighbor, and so is at most b's size.
    if ( !bb->is_leaf() )
      return true;
    // check numeric size
    return ( b->diagonal_x() > 1.01 * bb->diagonal_x() || b->diagonal_y() > 1.01 * bb->diagonal_y() );
  }
  
  // b > 2*bb ?
  bool bigger2_xy( BoxTreeNode *b, BoxTreeNode *bb )
  {
    assert( b->is_leaf() );
    assert( bb->is_leaf() ); // caller should check
    // check numeric size
    return ( b->diagonal_x() > 2.01 * bb->diagonal_x() || b->diagonal_y() > 2.01 * bb->diagonal_y() );
  }

};


// a couple of specific balancers that don't depend on a surface, or anything other than the tree itself
class BalancerNode: public Balancer
{
public:
  BalancerNode(BoxTree*bt) : Balancer(bt) {}
protected:
  bool balance_condition( BoxTreeNode *b, std::vector<BoxTreeNode*> &q )
  { return balance_all_neighbors( b, q, false ); }
};

class BalancerEdge: public Balancer
{
public:
  BalancerEdge(BoxTree*bt) : Balancer(bt) {}
protected:
  bool balance_condition( BoxTreeNode *b, std::vector<BoxTreeNode*> &q )
  { return balance_all_neighbors( b, q, true ); }
};

class BalancerFace: public Balancer
{
public:
  BalancerFace(BoxTree*bt) : Balancer(bt) {}
protected:
  virtual bool balance_condition( BoxTreeNode *b, std::vector<BoxTreeNode*> &q );
};

#endif
