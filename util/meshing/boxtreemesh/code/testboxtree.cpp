//
//  testboxtree.cpp
//  BoxTreeMesh
//
//  Created by Mitchell, Scott A on 1/5/16.
//  Copyright (c) 2016 Sandia National Labs. All rights reserved.
//

#include "testboxtree.h"
#include "boxtree.h"
#include "boxtreetool.h"
#include "surfaceinclusion.h"
#include "surfacefactory.h"
#include "boxsurfacetool.h"
#include "boxsurfaceinclusiontool.h"

void TestBoxTree::create_tree()
{
  BoxTree *box_tree = new BoxTree;
  
  delete box_tree;
}

void TestBoxTree::refine_tree()
{
  BoxTree *box_tree = new BoxTree;
  refine_tree(box_tree);
  delete box_tree;
}

void TestBoxTree::refine_tree(BoxTree *box_tree)
{

  // define the root
  Point min_corner(0,0,0);
  Point max_corner(8,8,8);
  box_tree->set_domain_size(min_corner, max_corner);
  
  // initial box layout
  Index two_cube(2,2,2);
  Index three_cube(3,3,3);

  box_tree->root->create_children(two_cube);
  
  // refine one corner
  if (/* DISABLES CODE */ (1))
  {
    Index ind(0, 0, 0);
    BoxTreeNode *b = box_tree->root->get_child(ind);
    b->create_children(two_cube);
  }
  
  // refine each root child one level
  if (/* DISABLES CODE */ (0))
  {
    for( int i = 0; i < box_tree->root->get_max_child(); ++i )
    {
      BoxTreeNode *child = box_tree->root->get_child(i);
      child->create_children(two_cube);
    }
  }
  
  // refine some 2nd level child into 3x3x3
  if (/* DISABLES CODE */ (0))
  {
    IndexVec some_box_iv;
    some_box_iv.push_back( Index(0, 0, 0) );
    some_box_iv.push_back( Index(1,1,1) );
    BoxTreeNode *b = box_tree->root->get_child(some_box_iv);
    b->create_children(three_cube);
  }
}

bool TestBoxTree::test_adjacency()
{
  BoxTree *bt = new BoxTree;
  
  refine_tree(bt);
  report_tree(bt);
  
  delete bt;
  
  return true;
}

void TestBoxTree::report_tree( BoxTree *box_tree )
{
  
  BoxTreeTool t( box_tree );
  
  t.assign_global_ids();
  t.write_face_adjacencies();
  t.write_nodal_coordinates();
}

template <class T>
bool vectors_same(std::vector<T> A, std::vector<T> B)
{
  assert( A.size() == B.size() );
  std::sort( A.begin(), A.end() );
  std::sort( B.begin(), B.end() );
  for (size_t i = 0; i < A.size(); ++i)
    assert( A[i] == B[i] );
  return true;
}

bool TestBoxTree::test_neighbor_functions()
{
  BoxTree box_tree;
  refine_tree( &box_tree );
  return test_neighbor_functions( &box_tree );
}


bool TestBoxTree::test_neighbor_functions( BoxTree *box_tree )
{
  BoxTreeTool t( box_tree );
  t.assign_global_ids();

  // go over all the boxes, not just leaves
  BoxTreeIterator bti( box_tree );
  BoxTreeNode *b;
  while ( (b = bti.next()) ) // skip the root
  {
    for (int f = 0; f < 6; ++f )
    {
      // neighbor
      BoxTreeNode *n_i = b->get_neighbor(f);
      BoxTreeNode *n_g = b->get_neighbor_by_geometry(f);
      assert( n_i == n_g );
      if ( n_i )
        assert( n_i->get_level() <= b->get_level() );
      if ( n_i != n_g )
        return false;
      
      // face children
      IntVec kids_i, kids_g;
      b->face_children( f, kids_i );
      b->face_children_by_geometry( f, kids_g );
      assert( vectors_same(kids_i, kids_g) );
      if ( !vectors_same(kids_i, kids_g) )
        return false;
      
      // face leaf children
      std::vector<BoxTreeNode*> boxes_i, boxes_g;
      b->face_leaf_children(f, boxes_i);
      b->face_leaf_children_by_geometry(f, boxes_g);
      assert( vectors_same(boxes_i, boxes_g) );
      if( ! vectors_same(boxes_i, boxes_g) )
        return false;
      
      if ( n_i )
      {
        boxes_i.clear(); boxes_g.clear();
        n_i->face_leaf_children( Box::opposite_face(f), boxes_i);
        n_i->face_leaf_children_by_geometry( Box::opposite_face(f), boxes_g);
        assert( vectors_same(boxes_i, boxes_g) );
        if ( !vectors_same(boxes_i, boxes_g) )
          return false;
      }
      
      // neighbor leaves
      std::vector<BoxTreeNode*> neighbors_i, neighbors_g;
      b->find_leaf_neighbors(f, neighbors_i);
      b->find_leaf_neighbors_by_geometry(f, neighbors_g );
      assert( vectors_same( neighbors_i, neighbors_g) );
      if ( !vectors_same( neighbors_i, neighbors_g) )
        return false;
    }
  }
  return true;
}


bool TestBoxTree::test_balance(BoxTree *bt, int side_length_factor, SubBoxType balance_type)
{
  BoxTreeTool t( bt );
  
  Balancer *balancer(0);
  switch (balance_type)
  {
    case NODE:
      balancer = new BalancerNode(bt);
      break;
    case EDGE:
      balancer = new BalancerEdge(bt);
     break;
    case FACE:
      balancer = new BalancerFace(bt);
      break;
    default:
      break;
  }
  balancer->balance();
  
  bool nbr_ok = test_neighbor_functions(bt);
  assert(nbr_ok);
  
  std::vector<BoxTreeNode*> face_neighbors, all_neighbors;

  bool all_sizes_ok(true);
  
  int bdy_faces(0); // how many faces are on the domain boundary?
  
  BTILeaf bti( bt );
  while ( bti.get() )
  {
    BoxTreeNode *b = bti.get();
    face_neighbors.clear();
    bdy_faces = 0;
    size_t old_size = 0;
    for (int f = 0; f < 6; ++f)
    {
      b->find_leaf_neighbors(f, face_neighbors);
      size_t fn = face_neighbors.size() - old_size; // number of new face_neighbors
      assert( fn == 0 || fn == 1 || fn == side_length_factor * side_length_factor );
      if ( fn == 0 )
        ++bdy_faces;
      old_size = face_neighbors.size();
    }
    
    // check dimensions
    for ( size_t n = 0; n < face_neighbors.size(); ++n)
    {
      bool big_x = face_neighbors[n]->diagonal_x() > b->diagonal_x() * 0.45;
      bool lit_x = face_neighbors[n]->diagonal_x() < b->diagonal_x() * 2.1;
      bool big_y = face_neighbors[n]->diagonal_y() > b->diagonal_y() * 0.45;
      bool lit_y = face_neighbors[n]->diagonal_y() < b->diagonal_y() * 2.1;
      bool big_z = face_neighbors[n]->diagonal_z() > b->diagonal_z() * 0.45;
      bool lit_z = face_neighbors[n]->diagonal_z() < b->diagonal_z() * 2.1;
      assert(big_x);
      assert(lit_x);
      assert(big_y);
      assert(lit_y);
      assert(big_z);
      assert(lit_z);
      bool size_ok = big_x && lit_x && big_y && lit_y && big_z && lit_z;
      all_sizes_ok = all_sizes_ok && size_ok;
    }
    
    // get neighbors by geometry
    if ( balance_type != FACE )
    {
      const bool skip_node_neighbors = ( balance_type != NODE );
      b->find_connected_boxes(all_neighbors, skip_node_neighbors);
      
      // assumes that boxes do not span from one side of the domain to the other, except for the top boxes
      size_t min_size(0), max_size(0);
      
      if ( side_length_factor == 2 )
      {
        min_size = 7 + 7;
        max_size = 4 * 4 * 4 - 1;
        
        if ( bdy_faces == 1 )
        {
          min_size -= 4;
          max_size = 4 * 4 * 3 - 1;
        }
        
        if ( bdy_faces == 2 )
        {
          min_size = 4; // punt
          max_size = 4 * 3 * 3 -1;
        }
        if ( bdy_faces == 3 )
        {
          min_size = 3; // punt
          max_size = 3 * 3 * 3 - 1;
        }
        if ( bdy_faces > 3 )
        {
          min_size = 6 - bdy_faces;
          max_size = 10; // ok for 4
        }
        
        assert( all_neighbors.size() >= min_size );
        assert( all_neighbors.size() <= max_size );
      }
      // between 0 and (2 + side_length_factor)^3 - 1
    }
    
    
    bti.next();
  }
  
//  t.assign_global_ids();
//  t.write_nodal_coordinates();
//  t.write_face_adjacencies();

  return nbr_ok && all_sizes_ok;
}

bool TestBoxTree::test_inclusionbodies()
{
  const bool toy = false;
  
  SurfaceInclusion ss;
  SurfaceInclusionFactory ssf;
  ssf._s = &ss;
  ssf.read( "Inclusion" );
  bool OK = ss.verify();
  // debug
  ss.print();
  
  // refine near surface
  BoxTree bt;
  BoxSurfaceInclusionTool bst( &bt, &ss);
  
  // make sure surface was property defined
  assert( ss.min_x() < ss.max_x() );
  assert( ss.min_y() < ss.max_y() );
  
  // simple toy examples domain size
  if (toy)
  {
    bst.set_domain_size(0., 200.);
  }
  // acousticsurface input file
  else
  {
    // 0--15000 is the depth of the example, based on the powerpoint picture
    bst.set_domain_size(0., 15000.);
    // start with squarish boxes:
    bt.root->create_children( Index(2,2,1) );
  }
  
  // refine box based on surface triangle size
  Index two_box(2,2,2);
  // for Scott's toy problems
  double min_dxy = 20;
  double max_dz = 20;
  if ( toy )
  {
    min_dxy = 20;
    max_dz = 20;
  }
  // for inclusion
  else
  {
    min_dxy = 400;
    max_dz = 400;
  }
  // beware: small dxy less than 120 may result in boxes too small compared to the grid size to contain a surface point!
  // a tiny max_dz could also cause problems, depending on the slope of the surface
  bst.refine_near_surface( min_dxy, max_dz, two_box );
  
  // balance so face-adjacent boxes differ by at most a factor of two
  const bool do_balance=true;
  BalancerFace bf(&bt);
  if (do_balance)
  {
    bf.balance();
  }
  
  // debug
  BoxTreeTool btt( &bt );
  bst.assign_global_ids();
  
  // recheck balance conditions
  // all should hold without actually doing a refinement or balance
  std::cout << "checking if original refinement and balance conditions were met" << std::endl;
  if ( bst.would_refine_near_surface( min_dxy, max_dz ) )
  {
    std::cout << "ERROR: refine near surface violated" << std::endl;
  }
  if (do_balance && bf.would_balance() )
  {
    std::cout << "ERROR: two balance violated" << std::endl;
  }
  
  //zzyk bst.mesh_boxes(); // cut and merge
  bst.assign_global_ids();
  //raw boxes without cutting and merging
  
  BoxTreeTool t( &bt );
  t.assign_global_ids(true);
  std::cout << "Created #boxes = " << bt.get_number_leaves() << " and #hexes = " << bt.get_number_hexes() << std::endl;
  
  t.write_off_file( "inclusion.off" );
  
  t.write_ply( "inclusion.ply" );
  
  t.write_cubit_mesh_jou( "inclusion_mesh.jou" );
  
  SurfaceInclusionFactory sf(&ss);
  sf.write_cubit_surface_jou( "inclusion_surf.jou" );

  // slowest
  t.write_face_adjacencies(  "inclusion.con" );
  t.write_nodal_coordinates( "inclusion.msh" );
  
  return OK;
}

bool TestBoxTree::test_adjacent_face_subsets( BoxTree *box_tree )
{
  BoxTreeTool btt( box_tree );
  btt.assign_global_ids();

  // vector of face neighbors
  std::vector<BoxTreeNode*> nbh, nbhh;

  bool OK(true);
  BTIOutput bti( box_tree );
  for ( BoxTreeNode *b = bti.get(); b != 0; b = bti.next() )
  {
    long id = b->get_id();

    assert(b->output_hex());
    
    // iterate over neighbors
    for ( int f = 0; f < 6; ++f )
    {
//      if ( id == 19 && f == 3 )
//      {
//        std::cout << "debug me" << std::endl;
//      }
      
      const int ff = Box::opposite_face(f);
      nbh.clear();
      b->find_mesh_neighbors(f, nbh);
      
      // test for zero neighbors on the domain boundary, and only there
      {
        Point nodes[4];
        b->face_nodes(f, nodes);
        const double x  = *Box::changed_coordinate(f,nodes[0]);
        const double bx = *Box::changed_coordinate(f,b->diagonal());
        const double xmin = *Box::changed_coordinate(f, box_tree->get_domain().corner_min() );
        const double xmax = *Box::changed_coordinate(f, box_tree->get_domain().corner_max() );
        const double dx = std::min( fabs(x-xmin), fabs(x-xmax) );
        const bool on_boundary = dx <= 0.001 * bx;
        if (on_boundary && !nbh.empty())
        {
          OK = false;
          std::cout << "ERROR: test_adjacent_subsets.\n";
          std::cout << "Hex face is on domain boundary, yet it has a neighbor.\n";
          BoxTreeNode *bb = nbh[0];
          long idd = bb->get_id();
          std::cout << "Domain range [ " << xmin << ", " << xmax << " ]\n";
          std::cout << "Hex " << id << " face " << f << " has coordinate " << x << "\n";
          std::cout << "Hex " << id << " face " << f << " has hex " << idd << " as a neighbor, ";
          
          b ->print_neighbors(f , nbh , true);
          bb->print_neighbors(ff, nbhh, true);
        }
        else if (!on_boundary && nbh.empty())
        {
          OK = false;
          std::cout << "ERROR: test_adjacent_subsets.\n";
          std::cout << "Hex face is not on domain boundary, yet it has no neighbors.\n";
          std::cout << "Domain range [ " << xmin << ", " << xmax << " ]\n";
          std::cout << "Hex " << id << " face " << f << " has coordinate " << x << "\n";
          
          b ->print_neighbors(f , nbh , true);
          
        }
      }
      
      for (size_t n = 0; n < nbh.size(); ++n)
      {
        BoxTreeNode *bb = nbh[n];
        nbhh.clear();
        bb->find_mesh_neighbors(ff, nbhh);
        long idd = bb->get_id();
        
        // test faces are subsets
        if (nbh.size() > 1 && nbhh.size() > 1)
        {
          OK = false;
          std::cout << "ERROR: test_adjacent_subsets.\n";
          std::cout << "For shared faces, one face must be a strict subset of the other.\n";

          b ->print_neighbors(f , nbh , true);
          bb->print_neighbors(ff, nbhh, true);
        }
        
        // test reciprocation
        bool found = false;
        for (size_t i = 0; i < nbhh.size(); ++i)
          if (nbhh[i] == b)
          {
            assert(nbhh[i]->get_id() == id);
            found = true;
          }
        if (!found)
        {
          OK = false;
          std::cout << "ERROR: test_adjacent_subsets.\n";
          std::cout << "Hex " << id << " face " << f << " has hex " << idd << " as a neighbor, ";
          std::cout << "but this is not reciprocated." << std::endl;
          
          b ->print_neighbors(f , nbh , true);
          bb->print_neighbors(ff, nbhh, true);
        }
      }
    }
  }
  return OK;
}
