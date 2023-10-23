//
//  example.cpp
//  BoxTreeMesh
//
//  Created by Mitchell, Scott A on 2/16/16.
//  Copyright (c) 2016 Sandia National Labs. All rights reserved.
//

#include "example.h"
#include "surfacefactory.h"
#include "boxsurfacetool.h"
#include "boxsurfaceinclusiontool.h"
#include "triangulationtool.h"

#include <fstream>
#include <cstdio>
#include <iomanip>


// uniform boxes
// 8x8x8 each side length is 1
// 512 elements
void Example::create_1()
{
  Point min_corner(0,0,0);
  Point max_corner(8,8,8);
  tree.set_domain_size(min_corner, max_corner);

  Index two_cube(2,2,2);

  // refine 3 levels
  BTILeaf bti(&tree);
  BoxTreeNode *b;
  for ( b = bti.get(); b; b = bti.next() )
  {
    if ( b->get_level() < 3 )
      b->create_children(two_cube);
  }
  
  tool.assign_global_ids();
  assert( test.test_neighbor_functions(&tree) );
  
  std::cout << "writing example 1." << std::endl;
  tool.write_face_adjacencies(    "boxes1.con" );
  tool.write_nodal_coordinates(   "boxes1.msh" );
  tool.write_boundary_conditions( "boxes1.bc" );
  tool.write_cubit_mesh_jou(      "boxes1.jou" );
  std::cout << "done writing example 1." << std::endl;

}

// uniform boxes
// 64x64x64 each side length is 1
// 262144 elements
void Example::create_2()
{
  
  // this one takes a while - let user know
  std::cout << "creating example 2 ..." << std::flush;
  
  Point min_corner(0,0,0);
  Point max_corner(64,64,64);
  tree.set_domain_size(min_corner, max_corner);
  
  Index two_cube(2,2,2);
  
  // refine to side length 1
  BTILeaf bti(&tree);
  BoxTreeNode *b;
  for ( b = bti.get(); b; b = bti.next() )
  {
    if ( b->diagonal_x() > 1.2 )
      b->create_children(two_cube);
  }
  
  tool.assign_global_ids();
  std::cout << "done." << std::endl;

  std::cout << "testing adjacencies ..." << std::flush;
  test.test_neighbor_functions(&tree);
  std::cout << "done" << std::endl;
  

  std::cout << "writing example 2." << std::endl;
  tool.write_face_adjacencies(    "boxes2.con" );
  tool.write_nodal_coordinates(   "boxes2.msh" );
  tool.write_boundary_conditions( "boxes2.bc" );
  tool.write_cubit_mesh_jou(      "boxes2.jou" );
  std::cout << "done writing example 2." << std::endl;

  
}

// big
void Example::create_7()
{
  
  // this one takes a while - let user know
  std::cout << "creating example 7 ..." << std::flush;
  
  Point min_corner(0,0,0);
  Point max_corner(64,64,64);
  tree.set_domain_size(min_corner, max_corner);
  
  Index two_cube(2,2,2);
  
  // refine to side length 1
  BTILeaf bti(&tree);
  BoxTreeNode *b;
  for ( b = bti.get(); b; b = bti.next() )
  {
    if ( b->diagonal_x() > 0.6 )
      b->create_children(two_cube);
  }
  
  tool.assign_global_ids();
  assert( test.test_neighbor_functions(&tree) );
  
  std::cout << "done. " << tree.get_number_leaves() << " elements." << std::endl;
  
  std::cout << "writing example 7." << std::endl;
  tool.write_face_adjacencies(    "boxes7.con" );
  tool.write_nodal_coordinates(   "boxes7.msh" );
  tool.write_boundary_conditions( "boxes7.bc" );
  tool.write_cubit_mesh_jou(      "boxes7.jou" );
  std::cout << "done writing example 7." << std::endl;
}

// some boxes of different sizes, differ by 2
void Example::create_3()
{
  Point min_corner(0,0,0);
  Point max_corner(8,8,8);
  tree.set_domain_size(min_corner, max_corner);
  
  Index two_cube(2,2,2);
  
  // refine 3 levels
  BTILeaf bti(&tree);
  BoxTreeNode *b;
  for ( b = bti.get(); b; b = bti.next() )
  {
    if ( b->get_level() < 3 )
      b->create_children(two_cube);
  }

  // refine a couple 3rd level child into 2x2x2
  // get some isolated, some on bdy, some adjacent, some corner-adjacent
  // only one level of difference, though
  if (/* DISABLES CODE */ (1))
  {
    IndexVec some_box_iv;
    some_box_iv.push_back( Index(0,0,0) );
    some_box_iv.push_back( Index(1,1,1) );
    some_box_iv.push_back( Index(0,1,0) );
    tree.root->get_child(some_box_iv)->create_children(two_cube);

    some_box_iv.clear();
    some_box_iv.push_back( Index(0,0,0) );
    some_box_iv.push_back( Index(0,0,0) );
    some_box_iv.push_back( Index(0,0,0) );
    tree.root->get_child(some_box_iv)->create_children(two_cube);

    some_box_iv.clear();
    some_box_iv.push_back( Index(0,1,1) );
    some_box_iv.push_back( Index(1,1,0) );
    some_box_iv.push_back( Index(1,0,0) );
    tree.root->get_child(some_box_iv)->create_children(two_cube);

    some_box_iv.clear();
    some_box_iv.push_back( Index(0,1,1) );
    some_box_iv.push_back( Index(1,1,0) );
    some_box_iv.push_back( Index(1,1,0) );
    tree.root->get_child(some_box_iv)->create_children(two_cube);

    some_box_iv.clear();
    some_box_iv.push_back( Index(0,1,1) );
    some_box_iv.push_back( Index(1,1,0) );
    some_box_iv.push_back( Index(0,0,1) );
    tree.root->get_child(some_box_iv)->create_children(two_cube);
  }

  
  tool.assign_global_ids();
  assert( test.test_neighbor_functions(&tree) );
  
  tool.write_face_adjacencies(    "boxes3.con" );
  tool.write_nodal_coordinates(   "boxes3.msh" );
  tool.write_boundary_conditions( "boxes3.bc" );
  tool.write_cubit_mesh_jou(      "boxes3.jou" );


}

// some boxes of different sizes, differ by 2,3,4
void Example::create_4()
{
  Point min_corner(0,0,0);
  Point max_corner(8,8,8);
  tree.set_domain_size(min_corner, max_corner);
  
  const Index two_cube(2,2,2);
  const Index three_cube(3,3,3);
  const Index four_cube(4,4,4);
  
  // refine 3 levels
  BTILeaf bti(&tree);
  BoxTreeNode *b;
  for ( b = bti.get(); b; b = bti.next() )
  {
    if ( b->get_level() < 3 )
      b->create_children(two_cube);
  }
  
  // refine a couple 3rd level child
  // get some isolated, some on bdy, some adjacent, some corner-adjacent
  // make sure we don't have a three adjacent to a two...
  if (/* DISABLES CODE */ (1))
  {
    IndexVec some_box_iv;
    some_box_iv.push_back( Index(0,0,0) );
    some_box_iv.push_back( Index(1,1,1) );
    some_box_iv.push_back( Index(0,1,0) );
    tree.root->get_child(some_box_iv)->create_children(four_cube);
    
    some_box_iv.clear();
    some_box_iv.push_back( Index(0,0,0) );
    some_box_iv.push_back( Index(0,0,0) );
    some_box_iv.push_back( Index(0,0,0) );
    tree.root->get_child(some_box_iv)->create_children(three_cube);
    
    some_box_iv.clear();
    some_box_iv.push_back( Index(0,1,1) );
    some_box_iv.push_back( Index(1,1,0) );
    some_box_iv.push_back( Index(1,0,0) );
    tree.root->get_child(some_box_iv)->create_children(three_cube);
    
    some_box_iv.clear();
    some_box_iv.push_back( Index(0,1,1) );
    some_box_iv.push_back( Index(1,1,0) );
    some_box_iv.push_back( Index(1,1,0) );
    tree.root->get_child(some_box_iv)->create_children(three_cube);
    
    some_box_iv.clear();
    some_box_iv.push_back( Index(0,1,1) );
    some_box_iv.push_back( Index(1,1,0) );
    some_box_iv.push_back( Index(0,0,1) );
    tree.root->get_child(some_box_iv)->create_children(three_cube);
  }
  
  
  tool.assign_global_ids();
  assert( test.test_neighbor_functions(&tree) );
  
  tool.write_face_adjacencies(    "boxes4.con" );
  tool.write_nodal_coordinates(   "boxes4.msh" );
  tool.write_boundary_conditions( "boxes4.bc" );
  tool.write_cubit_mesh_jou(      "boxes4.jou" );


}

// refine boxes with z coordinate in certain range, to mimic a surface
void Example::create_5()
{
  Point min_corner(0,0,0);
  Point max_corner(32,32,32);
  tree.set_domain_size(min_corner, max_corner);
  
  const Index two_cube(2,2,2);
  
  // refine 3 levels
  BTILeaf bti(&tree);
  BoxTreeNode *b;
  for ( b = bti.get(); b; b = bti.next() )
  {
    if ( b->get_level() < 4 )
      b->create_children(two_cube);
  }
  
  Box layer0( Point(0,0,23.5), Point(32,32,23.5) );
  
  bti.reset();
  for ( b = bti.get(); b; b = bti.next() )
  {
    if ( b->get_level() == 4 )
    {
      if (b->overlaps_box(layer0))
        b->create_children(two_cube);
    }
  }
  
  
  tool.assign_global_ids();
  assert( test.test_neighbor_functions(&tree) );

  tool.write_face_adjacencies(    "boxes5.con" );
  tool.write_nodal_coordinates(   "boxes5.msh" );
  tool.write_boundary_conditions( "boxes5.bc" );
  tool.write_cubit_mesh_jou(      "boxes5.jou" );

}

// refine boxes with z coordinate in certain range, to mimic a surface
void Example::create_6()
{
  Point min_corner(0,0,0);
  Point max_corner(32,32,32);
  tree.set_domain_size(min_corner, max_corner);
  
  const Index two_cube(2,2,2);
  
  // refine 3 levels
  BTILeaf bti(&tree);
  BoxTreeNode *b;
  for ( b = bti.get(); b; b = bti.next() )
  {
    if ( b->get_level() < 4 )
      b->create_children(two_cube);
  }

  Box layer0( Point(0,0,23.5), Point(24,30,23.5) );
  Box layer1( Point(19.1,19.1,19.1), Point(29,30,23.5) );

  bti.reset();
  for ( b = bti.get(); b; b = bti.next() )
  {
    if ( b->get_level() == 4 )
    {
      if (b->overlaps_box(layer0) || b->overlaps_box(layer1))
        b->create_children(two_cube);
    }
  }
  
  
  tool.assign_global_ids();
  assert( test.test_neighbor_functions(&tree) );
  
  tool.write_face_adjacencies(    "boxes6.con" );
  tool.write_nodal_coordinates(   "boxes6.msh" );
  tool.write_boundary_conditions( "boxes6.bc" );
  tool.write_cubit_mesh_jou(      "boxes6.jou" );

}


// unbalanced
void Example::create_8()
{
  
  // this one takes a while - let user know
  std::cout << "creating example 8 ..." << std::flush;
  
  Point min_corner(0,0,0);
  Point max_corner(64,64,64);
  tree.set_domain_size(min_corner, max_corner);
  
  Index two_cube(2,2,2);
  
  // b initially lowest corner child, then upper corner child forever after
  tree.root->create_children(two_cube);
  BoxTreeNode *b = tree.root->get_child(0);
  for ( size_t level = 1; level < 6; ++level )
  {
    b->create_children(two_cube);
    b = b->get_child(7);
  }
  
  tool.assign_global_ids();
  assert( test.test_neighbor_functions(&tree) );
  
  std::cout << "done. " << tree.get_number_leaves() << " elements." << std::endl;
  
  std::cout << "writing example 8." << std::endl;
  tool.write_face_adjacencies(    "boxes8.con" );
  tool.write_nodal_coordinates(   "boxes8.msh" );
  tool.write_boundary_conditions( "boxes8.bc" );
  tool.write_cubit_mesh_jou(      "boxes8.jou" );
  std::cout << "done writing example 8." << std::endl;
  
}


void Example::slide(double element_size)
{
  std::cout << "Creating slide acousticsurface example for Curt conference" << std::endl;

  Surface surf;
  
  // domain and surface extent
  
  double scalexy = 0.5; // make the xy domain smaller to have a smaller number of elements
  
  const double xmin = 0.;
  const double ymin = 0.;
  const double dx = 10; // 50.;
  const double dy = 8; // 25.;
  double x_max = 1500 * scalexy;
  double y_max = 1250 * scalexy;
  double z_max = 3000;
  const double x_size = x_max / dx + 1;
  const double y_size = y_max / dy + 1;
  
  std::string prefix = "boxtreemeshes/acousticsurface/slide/";
  std::string surf_name = "slide";
  
  // do Curt's new request
  const bool curt_A = false;
  if (curt_A)
  {
    z_max = 1000;
    surf_name += "_A";
  }
  if (element_size != 1.0)
  {
    surf_name += "_" + std::to_string(element_size);
  }
  
  

  // =================================
  // create surface
  // =================================
  class SFSlide : public SurfaceFactory
  {
  public:
    double _x_max, _y_max; // extent of surface, from corner 0,0 to corner (_x_max, _y_max)
    SFSlide(Surface *s, double x_max, double y_max) : SurfaceFactory(s), _x_max(x_max), _y_max(y_max) {}
    
    // base depth
    double depth = 500;

    // rolling
    double amplitude = 20; // +/- peak-to-trough, smaller than ridgeheight
    double x_period = 1.2 * 200;
    double y_period = sqrt(3.) * 200;
    
    // ridge
    // h=40, 2 to 5 elements = 80 -- 200.
    // -280 works but gives a long ridge
    double ridgeheight = -120;
    
    // slope
    double delta_depth = -100; // difference between one corner and the other

    // testing, reduce the slope
    // fails > 0.83. 0.8 is good. set to 0.0 to just use a flat surface
    // const double attenuate = 0.8;
    double attenuate = 0.8;
    double noise_factor = 1.; // set this lower to attenuate the rolling part
    
    
    double scalexy = 1.;
    
    
    double ridge( double x, double y ) const
    {
      double pos = x; // one-dimensional parameter. keep coefficients <= 1
      const double pos_start = _x_max * 0.3; // for 1500 and 6000 : _x_max * 0.3 * scalexy;
      const double pos_end = pos_start + 1.2 * fabs(ridgeheight); // 1. * ridgeheight for slope 1, >1 for smaller slope
      bool ridge_start = (pos > pos_start);
      bool ridge_end   = (pos > pos_end);
      if (!ridge_start)
        return 0.;
      if (ridge_end)
        return ridgeheight;
      // transition
      return ridgeheight * (pos - pos_start) / ( pos_end - pos_start );
    }
    
    double rolling( double x, double y ) const
    {
      const double PI = 2. * acos(0.0);
      // xx and yy are used to make the hills off-axis and non-orthogonal to each other
      double xx = 0.2 * x + 0.8 * y;
      double yy = 0.5 * x + 0.5 * y;
      double zz = 0.6 * x + 0.4 * y; // high frequency noise to break up patterns
      return ( sin( xx * 2. * PI / x_period) + 0.8 * sin( yy * 2. * PI / y_period ) + 0.4 * sin( zz * 2. * PI / ( 0.25 * (y_period + x_period) ) ) ) * amplitude;
    }
    double slope( double x, double y ) const
    {
      double pos = 1.5 * x + y;
      const double max_pos = 1.5 * _x_max + _y_max;
      return (pos / max_pos) * delta_depth;
      
    }
    virtual double depth_function(double x, double y)
    {
      return depth + attenuate * (slope(x,y) + noise_factor * rolling(x,y) + ridge(x,y));
    }
    
  };
  
  
  SFSlide sf(&surf,x_max,y_max);
  if (curt_A)
  {
    sf.attenuate = 0.8;
    sf.noise_factor = 0.7;
  }
  sf.delta_depth *= scalexy;
  sf.scalexy = scalexy;
  sf.set_surface(xmin, ymin, dx, dy, x_size, y_size);
  sf.write(prefix + surf_name + ".xyz");
  sf.write_ply( prefix + surf_name + ".ply");
  sf.write_cubit_surface_jou( prefix + surf_name + ".jou" );
  
  // =================================
  // initial boxes
  // =================================
  
  BoxTree bt;
  BoxSurfaceTool bst( &bt, &surf);
  
  // make sure surface was property defined
  
  // xy-size from the surface. z-size specified here
  bst.set_domain_size(0., z_max);
  
  // start with squarish boxes:
  unsigned zsplit = 2;
  if (scalexy < 0.8 )
    zsplit = 3;
  if (scalexy < 0.6 )
    zsplit = 4;
  
  if (curt_A)
  {
    // do 3 because 3000/1000 = 3
    bt.root->create_children( Index(3,3,zsplit) ); // try also (5,4,10)
  }
  else
  {
    bt.root->create_children( Index(1,1,zsplit) ); // try also (5,4,10)
  }
  
  // refine box based on surface triangle size
  Index two_box(2,2,2);
//  Index skinny_box(2,2,1);
//  Index skinny_box(4,4,2);
//  Index two_box(3,3,3);
  // Index three_box(3,3,3); // doesn't work currently
  
  // =================================
  // mesh refiner
  // =================================

  // refine boxes that are not smaller (in every coordinate) than this size
  //  Point upper_size( _s->grid_x() * grid_factor, _s->grid_y() * grid_factor, _bt->get_domain().diagonal_z() );

  // desired size
  double h_acoustic = 100;
  double h_shallow = 40;
  double h_deep = 150;
  
  // want elements 1/2 as big
  if ( curt_A )
  {
    h_acoustic *= 0.5;
    h_shallow *= 0.5;
    h_deep *= 0.5;
  }
  
  // target range
  // elements will be within target_factor and target_factor / 2 of the desired size
  const double target_factor = 1.5 * element_size;
  double ht_acoustic  = h_acoustic  * target_factor;
  double ht_shallow = h_shallow * target_factor;
  double ht_deep   = h_deep   * target_factor;
  
  RefinerChain *rf = new RefinerChain(&bt);

  // biggest
  {
    assert( ht_deep > ht_acoustic);
    assert( ht_deep > ht_shallow);
    RefinerUniform *r = new RefinerUniform(&bt);
    Point upper_size( ht_deep, ht_deep, ht_deep );
    r->upper_size = upper_size;
    rf->chain.push_back( r );
  }
  
  // at acousticsurface
  {
    RefinerNearSurface *r = new RefinerNearSurface(&bt,&surf);
    Point upper_size( ht_shallow, ht_shallow, ht_shallow );
    r->upper_size = upper_size;
    rf->chain.push_back( r );
  }
  
  // acoustic, above acousticsurface
  {
    RefinerAcoustic *r = new RefinerAcoustic(&bt,&surf);
    Point upper_size( ht_acoustic, ht_acoustic, ht_acoustic );
    r->upper_size = upper_size;
    rf->chain.push_back( r );
  }
  
  rf->child_size = two_box;
  
  bst.set_refiner_near_surface(rf);
  bst.refine_near_surface();

  // balance for merging fails if the mesh was refined with anything other than two-box
  // what we need is to be able to switch the child size after refinement, but before merging,
  // and still be able to traverse the tree

  // balance so boxes on either side of surface have same xy size
  bst.balance_for_merging(two_box);
  // infinite loop for child size 4,4,2 or 2,2,1. balance condition is complicated. for now, stick to 2,2,2 and live with the limitations. it isn't central to the project goals

  // debug
  if (1)
  {
    bst.assign_global_ids();
    
    // recheck balance conditions
    // all should hold without actually doing a refinement or balance
    if ( bst.would_refine_near_surface() )
    {
      std::cout << "ERROR: refine near surface violated" << std::endl;
    }
    if ( bst.would_balance_for_merging() )
    {
      std::cout << "ERROR: balance for merging violated" << std::endl;
    }
  }
  
  bst.mesh_boxes(); // cut and merge
  
  // debug
  TestBoxTree tbt;
  if ( tbt.test_adjacent_face_subsets( &bt ) )
    std::cout << "Face adjacencies OK" << std::endl;
  else
    std::cout << "*** MESH FAIL, try reducing the surface slope. ***" << std::endl;

  BoxTreeTool t( &bt );
  t._write_corner_coords = false;
  t.assign_global_ids(true);
  
  std::cout << "Created #boxes = " << bt.get_number_leaves() << " and #hexes = " << bt.get_number_hexes() << std::endl;
  t.write_face_adjacencies(    prefix + surf_name + ".con" );
  t.write_nodal_coordinates(   prefix + surf_name + ".msh" );
  t.write_boundary_conditions( prefix + surf_name + ".bc" );

  bst.assign_box_acoustic_zone();
  bst.write_box_zones( prefix + surf_name );
  
  // paraview
  t.write_off_file( prefix + surf_name + ".off" );
  // tecplot
  t.write_ply( prefix + surf_name + ".ply" );
  
  // cubit
  t.write_cubit_mesh_jou( prefix + surf_name + "_mesh.jou" );
  t._write_corner_coords = true;
  t.write_cubit_mesh_jou( prefix + surf_name + "_box.jou" );
  t._write_corner_coords = false;
  
}


void Example::create_test_suite_A()
{
  std::cout << "Creating test suite A" << std::endl;
  
  //  for ( size_t p = 0; p < 8; ++p )
  for ( size_t p = 3; p < 6; ++p )
  {
    
    // acousticsurface examples
    if (/* DISABLES CODE */ (1))
    {
      //    const bool toy = true;
      const bool toy = false; // acousticsurface file
      Surface surf;
      
      // domain and surface extent
      const double xmin = 0.;
      const double ymin = 0.;
      const double dx = toy ? 50. : 1000; // 5000;
      const double dy = toy ? 25. :  500; // 2500;
      const double x_size =  toy ? 4   : 30000 / dx + 1;
      const double y_size =  toy ? 8   : 25000 / dy + 1;
      const double z_depth = toy ? 200 : 15000;
      const double nominal_surface_depth = toy ? 50 : 500;
      
      const double nodal_scale_factor = 0.2;
      
      std::string prefix = "boxtreemeshes/acousticsurface/";
      if (p<6)
        prefix += std::to_string(p);
      else
        switch (p) {
          case 6:
            prefix += "0a";
            break;
          case 7:
            prefix += "0b";
            break;
          default:
            break;
        }
      prefix += "/mesh/";
      
      std::cout << "\n\n***   p = " << p << "  Creating " << prefix << "***" << std::endl;
      
      switch (p)
      {
        case 0:
        case 6:
        case 7:
        {
          std::cout << "***   0 & 0a & 0b Zero surface   ***\n" << std::endl;
          
          SFFlat sf(&surf);
          sf.depth = z_depth * 0.5;
          sf.set_surface(xmin, ymin, dx, dy, x_size, y_size);
          sf.write(prefix + "acousticsurfaceZero.xyz");
          
        }
          break;
          
        case 1:
        {
          std::cout << "***   1. ACOUSTICSURFACE FLAT   ***\n" << std::endl;
          
          SFFlat sf(&surf);
          sf.depth = nominal_surface_depth;
          sf.set_surface(xmin, ymin, dx, dy, x_size, y_size);
          sf.write(prefix + "acousticsurfaceFlat.xyz");
          
        }
          break;
          
        case 2:
        case 5:
        {
          std::cout << "***   2. & 5. ACOUSTICSURFACE Nathan's file   ***\n" << std::endl;
          SurfaceFactory sf(&surf);
          sf.read("acousticsurface.xyz"); // no prefix
          sf.write(prefix + "acousticsurfaceCopy.xyz");
        }
          break;
          
        case 3:
        {
          std::cout << "***   3. ACOUSTICSURFACE SLANT   ***\n" << std::endl;
          SFSlant sf(&surf);
          sf.depth = nominal_surface_depth;
          sf.slope = nominal_surface_depth / ( dx * x_size + dy * y_size );
          sf.slope = sf.slope * 20; // make it visible in the small corner
          sf.set_surface(xmin, ymin, dx, dy, x_size, y_size);
          sf.write(prefix + "acousticsurfaceSlant.xyz");
        }
          break;
          
        case 4:
        {
          std::cout << "***   4. ACOUSTICSURFACE SINE   ***\n" << std::endl;
          
          SFSine sf(&surf);
          sf.depth = nominal_surface_depth;
          if (toy)
          {
            sf.amplitude = 16; // at 18, we get some squished hexes. at 20, we get adjacency errors
            sf.x_period = 400;
            sf.y_period = 200;
          }
          else
          {
            //        sf.amplitude = 500;
            //        // keep it from being too shallow
            //        sf.depth = nominal_surface_depth + sf.amplitude;
            sf.amplitude = 400; // 400 is fine. 440+ 500 gives bad neighbors
            sf.depth = nominal_surface_depth + sf.amplitude; // amplitude * 0.7 is also OK
            sf.x_period =  dx*7.134;
            sf.y_period =  sf.x_period * 1.359;
          }
          sf.set_surface(xmin, ymin, dx, dy, x_size, y_size);
          
          sf.write(prefix + "acousticsurfaceSine.xyz");
        }
          break;
        default:
          break;
      }
      
      BoxTree bt;
      BoxSurfaceTool bst( &bt, &surf);
      
      // make sure surface was property defined
      
      // xy-size from the surface. z-size specified here
      bst.set_domain_size(0., z_depth);
      
      // start with squarish boxes:
      if (!toy)
      {
        bt.root->create_children( Index(2,2,1) );
      }
      
      // refine box based on surface triangle size
      Index two_box(2,2,2);
      
      // surface deviation allowed for toy problems and acousticsurface
      double min_dxy = toy ? 20 : 5000;
      double max_dz =  toy ? 20 : 1000; // 500;
      
      // refine boxes that are not smaller (in every coordinate) than this size
      //  Point upper_size( _s->grid_x() * grid_factor, _s->grid_y() * grid_factor, _bt->get_domain().diagonal_z() );
      Point upper_size( min_dxy, min_dxy, bt.get_domain().diagonal_z() );
      
      Refiner *refiner = 0;
      switch (p)
      {
          
        case 0:
        {
          // uniform by volume
          RefinerUniform *rf = new RefinerUniform(&bt);
          rf->upper_size = upper_size * 0.2;
          refiner = rf;
        }
          break;
        case 6:
        {
          // z = 0 to 3000 is 1/2 size of the rest
          RefinerChain *rf = new RefinerChain(&bt);
          
          RefinerUniform *r0 = new RefinerUniform(&bt);
          r0->upper_size = upper_size * 0.4;
          rf->chain.push_back( r0 );
          
          RefinerBox *r1 = new RefinerBox(&bt);
          r1->upper_size = upper_size * 0.2;
          r1->centroid_range = Box( Point(0.,0.,0.), Point( std::numeric_limits<double>::max(), std::numeric_limits<double>::max(), 3000 ) );
          rf->chain.push_back( r1 );
          
          refiner = rf;
        }
          break;
        case 7:
        {
          // z = 0 to 3000 in two xy corners is 1/2 size of the rest
          //
          RefinerChain *rf = new RefinerChain(&bt);
          
          RefinerUniform *r0 = new RefinerUniform(&bt);
          r0->upper_size = upper_size * 0.4;
          rf->chain.push_back( r0 );
          
          RefinerBox *r1 = new RefinerBox(&bt);
          r1->upper_size = upper_size * 0.2;
          r1->centroid_range = Box( Point(0.,0.,0.), Point( 3750, 3125, 3000 ) );
          rf->chain.push_back( r1 );
          
          RefinerBox *r2 = new RefinerBox(&bt);
          r2->upper_size = upper_size * 0.2;
          r2->centroid_range = Box( Point( 3750, 3125, 0 ), Point( std::numeric_limits<double>::max(), std::numeric_limits<double>::max(), 3000 ) );
          rf->chain.push_back( r2 );
          
          refiner = rf;
        }
          break;
        default:
          // uniform along a surface
          // max_dz = 10000;
          // RefinerNearSurface refiner(&bt,&surf);
          
          RefinerChain *rf = new RefinerChain(&bt);
          
          RefinerUniform *r0 = new RefinerUniform(&bt);
          r0->upper_size = upper_size;
          rf->chain.push_back( r0 );
          
          // denser in one corner
          RefinerVariableNearSurface *rs = new RefinerVariableNearSurface(&bt, &surf);
          rs->upper_size = upper_size*1.5;
          rs->height_variation = max_dz*3.;
          if (p==3)
          {
            rs->min_size_factor = 0.6;
            rs->max_size_factor = 3;
            rs->upper_size = upper_size;
          }
          // this makes meshes too fine for dgm to have tractable serial runtime
          // rs->upper_size = upper_size;
          // rs->height_variation = max_dz;
          rf->chain.push_back(rs);
          
          
          // denser in the corner
          refiner = rf;
      }
      
      
      refiner->child_size = two_box;
      
      bst.set_refiner_near_surface(refiner);
      bst.refine_near_surface();
      
      // debug
      bst.assign_global_ids(true);
      std::cout << "refining near surface #hexes = " << bt.get_number_hexes() << std::endl;
      
      
      // balance so boxes on either side of surface have same xy size
      bst.balance_for_merging();
      
      // debug
      bst.assign_global_ids(true);
      std::cout << "balance for merging #hexes = " << bt.get_number_hexes() << std::endl;
      
      // debug
      bst.assign_global_ids();
      
      // recheck balance conditions
      // all should hold without actually doing a refinement or balance
      if ( bst.would_refine_near_surface() )
      {
        std::cout << "ERROR: refine near surface violated" << std::endl;
      }
      if ( bst.would_balance_for_merging() )
      {
        std::cout << "ERROR: balance for merging violated" << std::endl;
      }
      
      bst.mesh_boxes(); // cut and merge
      
      // debug
      bst.assign_global_ids(true);
      std::cout << "cut and merge #hexes = " << bt.get_number_hexes() << std::endl;
      
      
      TestBoxTree tbt;
      tbt.test_adjacent_face_subsets( &bt );
      
      bool do_facade = true;
      
      if (p==5)
        do_facade = false;
      
      // take just a facade of hexes, for creating small test problems
      if (do_facade)
      {
        bst.discard_hexes(2, 0.25);
        bst.discard_hexes(3, 0.25);
        
        tbt.test_adjacent_face_subsets( &bt );
      }
      
      BoxTreeTool t( &bt );
      //if true, then we write the raw boxes without cutting and merging
      t._write_corner_coords = false;
      t.assign_global_ids(true);
      
      std::cout << "Created #boxes = " << bt.get_number_leaves() << " and #hexes = " << bt.get_number_hexes() << std::endl;
      t.write_face_adjacencies(    prefix + "acousticsurface.con" );
      t.write_nodal_coordinates(   prefix + "acousticsurface.msh", nodal_scale_factor );
      t.write_boundary_conditions( prefix + "acousticsurface.bc" );
      
      
      t.write_off_file( prefix + "acousticsurface.off" );
      
      t.write_ply( prefix + "acousticsurface.ply" );
      
      t.write_cubit_mesh_jou( prefix + "acousticsurface_mesh.jou" );
      t._write_corner_coords = true;
      t.write_cubit_mesh_jou( prefix + "acousticsurface_box.jou" );
      t._write_corner_coords = false;
      
      SurfaceFactory sf(&surf);
      sf.write_cubit_surface_jou( prefix + "acousticsurface_surf.jou" );
    }
    
    
  }
}



void Example::make_surface_1()
{
  std::cout << "make_surface_1" << std::endl;
  
  // acousticsurface examples
  if (/* DISABLES CODE */ (1))
  {
    //    const bool toy = true;
    const bool toy = true; // acousticsurface file
    Surface surf;
    
    // domain and surface extent
    const double xmin = 0.;
    const double ymin = 0.;
    const double dx = toy ? 10. : 1000; // 5000;
    const double dy = toy ?  5. :  500; // 2500;
    const double x_size =  toy ? 10   : 30000 / dx + 1;
    const double y_size =  toy ? 21   : 25000 / dy + 1;
    // const double z_depth = toy ? 200 : 15000;
    const double nominal_surface_depth = toy ? 50 : 500;
    
    // const double nodal_scale_factor = 1;
    
    std::string prefix = ""; // boxtreemeshes/acousticsurface/";
    
    {
      std::cout << "***   4. ACOUSTICSURFACE SINE   ***\n" << std::endl;
      
      SFSine sf(&surf);
      sf.depth = nominal_surface_depth;
      if (toy)
      {
        sf.amplitude = 16; // for acousticsurface meshing, at 18, we get some squished hexes. at 20, we get adjacency errors
        sf.x_period = x_size * dx;
        sf.y_period = y_size * dy;
      }
      else
      {
        //        sf.amplitude = 500;
        //        // keep it from being too shallow
        //        sf.depth = nominal_surface_depth + sf.amplitude;
        sf.amplitude = 400; // 400 is fine. 440+ 500 gives bad neighbors
        sf.depth = nominal_surface_depth + sf.amplitude; // amplitude * 0.7 is also OK
        sf.x_period =  dx*7.134;
        sf.y_period =  sf.x_period * 1.359;
      }
      sf.set_surface(xmin, ymin, dx, dy, x_size, y_size);
      
      sf.write(prefix + "acousticsurfaceSine.xyz");
    }
  }
}


void Example::make_surface_3()
{
  std::cout << "make_surface_3" << std::endl;
  
  // acousticsurface examples
  if (/* DISABLES CODE */ (1))
  {
    //    const bool toy = true;
    const bool toy = true; // acousticsurface file
    Surface surf;
    
    // domain and surface extent
    const double xmin = 0.;
    const double ymin = 0.;
    const double dx = toy ? 10. : 1000; // 5000;
    const double dy = toy ?  5. :  500; // 2500;
    const double x_size =  toy ? 10   : 30000 / dx + 1;
    const double y_size =  toy ? 21   : 25000 / dy + 1;
    // const double z_depth = toy ? 20 : 15000;
    const double nominal_surface_depth = toy ? 110 : 1500;
    
    // const double nodal_scale_factor = 1;
    
    std::string prefix = ""; // boxtreemeshes/acousticsurface/";
    
    {
      std::cout << "***  ACOUSTICSURFACE SINE   ***\n" << std::endl;
      
      SFSine sf(&surf);
      sf.depth = nominal_surface_depth;
      if (toy)
      {
        sf.amplitude = 20; // for acousticsurface meshing, at 18, we get some squished hexes. at 20, we get adjacency errors
        sf.x_period = 1.5 * x_size * dx;
        sf.y_period = 2.0 * y_size * dy;
      }
      else
      {
        //        sf.amplitude = 500;
        //        // keep it from being too shallow
        //        sf.depth = nominal_surface_depth + sf.amplitude;
        sf.amplitude = 400; // 400 is fine. 440+ 500 gives bad neighbors
        sf.depth = nominal_surface_depth + sf.amplitude; // amplitude * 0.7 is also OK
        sf.x_period =  dx*7.134;
        sf.y_period =  sf.x_period * 1.359;
      }
      sf.set_surface(xmin, ymin, dx, dy, x_size, y_size);
      
      sf.write(prefix + "Sine3.xyz");
    }
  }
}


void Example::make_surface_2()
{
  std::cout << "make_surface_2" << std::endl;
  
  // acousticsurface examples
  if (/* DISABLES CODE */ (1))
  {
    //    const bool toy = true;
    const bool toy = true; // acousticsurface file
    Surface surf;
    
    // domain and surface extent
    const double xmin = 0.;
    const double ymin = 0.;
    const double dx = toy ? 10. : 1000; // 5000;
    const double dy = toy ?  5. :  500; // 2500;
    const double x_size =  toy ? 10   : 30000 / dx + 1;
    const double y_size =  toy ? 21   : 25000 / dy + 1;
    // const double z_depth = toy ? 200 : 15000;
    const double nominal_surface_depth = toy ? 50 : 500;
    
    // const double nodal_scale_factor = 1;
    
    std::string prefix = ""; // boxtreemeshes/acousticsurface/";
    
    {
      std::cout << "***   ACOUSTICSURFACE SLANT   ***\n" << std::endl;
      
      SFSlant sf(&surf);
      sf.depth = nominal_surface_depth;
      if (toy)
      {
      }
      else
      {
      }
      sf.depth = nominal_surface_depth;
      sf.slope = nominal_surface_depth / ( dx * x_size + dy * y_size ); // twice as deep in far corner
      sf.slope = sf.slope * 0.2;
      sf.set_surface(xmin, ymin, dx, dy, x_size, y_size);
      
      sf.write(prefix + "acousticsurfaceSlant.xyz");
    }
  }
}

void Example::inclusion_manifold()
{
  // if true, then we must have exactly two triangles per quad face, not three or more.
  // This precludes boxes with hanging nodes on the interface.
  const bool exactly_two_triangles = true;
  
  const bool toy = true; // examples 00 to 05
  // const bool toy = false; // example 06
  
  SurfaceInclusion ss;
  SurfaceInclusionFactory ssf;
  ssf._s = &ss;
  
  bool do_inclusion(true);
  if (do_inclusion)
  {
    // "Inclusion"
    ssf.read( "Inclusion" ); // all surfaces that exist
//  ssf.read( "Inclusion", 6 ); // parameter 1 = just TopInclusion1, 2 = TopInclusion1,BotInclusion1, etc. 3=T1 B1 T2
    //ssf.write("InclusionCopy");
    bool OK = ss.verify();
    if (!OK)
      std::cout << "There is something wrong with the read in inclusion surface." << std::endl;
    else
      std::cout << "Surfaces look good." << std::endl;
    
    // debug
    ss.print();
    
    do_inclusion = OK;
    
    // make sure surface was property defined
  }

  BoxTree bt;
  BoxSurfaceInclusionTool bst( &bt, &ss);
  
  if (do_inclusion)
  {
    assert( ss.min_x() < ss.max_x() );
    assert( ss.min_y() < ss.max_y() );
    // simple toy examples domain size
    if (toy)
    {
      bst.set_domain_size(0., 200.);
      bt.root->create_children( Index(1,1,2) );
    }
    else
    {
      // 0--15000 is the depth of the example, based on the powerpoint picture
      bst.set_domain_size(0., 15000.);
      // start with squarish boxes:
      bt.root->create_children( Index(2,2,1) );
    }
  }
  
  Index two_box(2,2,2);
  
  // sizing parameters.
  // dxy is about the size of boxes near the acousticsurface surface
  // inclusion_dx near the inclusion-elastic interface surfaces
  // max box size througout the domain is max_box * min_dxy;
// for 00, 01, 02 examples
  double min_dxy = toy ? 30 : 5000;
  double max_dz =  toy ? 30 : 1000; // 500;
  double inclusion_min_dxy = toy ? 30 : 5000;
  double inclusion_max_dz =  toy ? 30 : 500; // 1000; // 500;
  double max_box = 4.; // most examples
  
//  // for 03_hextet-acoustic example
//  min_dxy = 10;
//  max_dz = 10;
//  inclusion_min_dxy = 40;
//  inclusion_max_dz = 40;
  
  // for 05_layers example
  inclusion_min_dxy = 14.5;
  
  // for 06 full example
  // domain is 30,000 by 25,000 by 15,000
  // acousticsurface is about 380-500
//  {
//    min_dxy = 5000; // 300;
//    max_dz = 1000;
//    inclusion_min_dxy = 5000;
//    inclusion_max_dz = 5000;
//    max_box = 64;
//  }

  // ============================ boxes for acousticsurface =========
  bool do_acousticsurface(true);
  Surface surf;
  BoxSurfaceTool *bwt_p=0;
  if ( do_acousticsurface )
  {
    SurfaceFactory sf(&surf);
    do_acousticsurface = sf.read("acousticsurface.xyz");
  }
  if (do_acousticsurface)
  {
    bwt_p = new BoxSurfaceTool( &bt, &surf); // box acousticsurface tool
    BoxSurfaceTool &bwt = *bwt_p;
    
    // save acousticsurface for viewing
    // paraview
    bwt.write_off_file( "acousticsurface.off" );
    // tecplot
    bwt.write_ply( "acousticsurface.ply" );

    if (!do_inclusion)
    {
      if (toy)
      {
        bwt.set_domain_size(0., 200.);
        bt.root->create_children( Index(1,1,2) );
      }
      else
      {
        // 0--15000 is the depth of the example, based on the powerpoint picture
        bwt.set_domain_size(0., 15000.);
        // start with squarish boxes:
        bt.root->create_children( Index(2,2,1) );
      }
    }
        
    // uniform along a surface
    // max_dz = 10000;
    // RefinerNearSurface refiner(&bt,&surf);
    
    RefinerChain *rf = new RefinerChain(&bt);
    
    RefinerUniform *r0 = new RefinerUniform(&bt);
    // surface deviation allowed for toy problems and acousticsurface
    
    // refine boxes that are not smaller (in every coordinate) than this size
    //  Point upper_size( _s->grid_x() * grid_factor, _s->grid_y() * grid_factor, _bt->get_domain().diagonal_z() );
    Point upper_size( max_box * min_dxy, max_box * min_dxy, bt.get_domain().diagonal_z() );
    // Point upper_size( 8.*min_dxy, 8.*min_dxy, bt.get_domain().diagonal_z() );

    r0->upper_size = upper_size;
    rf->chain.push_back( r0 );
    
    // denser in one corner
    RefinerVariableNearSurface *rs = new RefinerVariableNearSurface(&bt, &surf);
    rs->height_variation = max_dz*3.;
    {
      rs->min_size_factor = 0.6;
      rs->max_size_factor = 3;
      rs->upper_size = upper_size * 1.5; // * 0.5;
    }
    // this makes meshes too fine for dgm to have tractable serial runtime
    // rs->upper_size = upper_size;
    // rs->height_variation = max_dz;
    rf->chain.push_back(rs);
    
    
    // denser in the corner
    Refiner *refiner = rf;
  
    refiner->child_size = two_box;
  
    bwt.set_refiner_near_surface(refiner);
    bwt.refine_near_surface();
  }
  
  // zzyk, general routine to choose initial refinement to get roughly square box sizes
  // find approximate ratio of x,y,z domain extent, as a ratio of small integers

  // turn nans into the bottom of the domain for the triangulation
  // get rid of those horizontal triangles later
  // zzyk - turn this off for the actual inclusion surface
  // zzyk - this causes problems if multiple surfaces end up coincident at the max
  // ss.truncate_depth( bt.get_domain().max_z(), bt.get_domain().max_z() );
    
  // ============================ manifold reconstruction for inclusion =====
  const bool do_manifold = true;
  if (do_manifold)
  {
    bst.connect_manifolds();
  }
  
  
  // ============================ boxes for inclusion ===========
  const bool do_boxes = true;
  double tri_edge_length(30);
  if (do_boxes)
  {
    // refine box based on surface triangle size

    tri_edge_length = inclusion_min_dxy * 0.8; // what should the size be? min_dxy is about the size of the box sides on the hex-tet interface
    // beware: small dxy less than 120 may result in boxes too small compared to the grid size to contain a surface point!
    // a tiny max_dz could also cause problems, depending on the slope of the surface
    bst.refine_near_surface( inclusion_min_dxy, inclusion_max_dz, two_box );
    
    // balance so face-adjacent boxes differ by at most a factor of two
    const bool do_balance=true;
    BalancerFace bf(&bt);
    if (do_balance)
    {
      bf.balance();
    }

    if (exactly_two_triangles)
    {
      bst.balance_for_two_triangles();
    }

    // define which boxes will not be output, based on proximity to the inclusion surface
    if (!do_acousticsurface)
      bst.set_output_boxes();
    
    // debug
    BoxTreeTool btt( &bt );
    bst.assign_global_ids();
    
    // recheck balance conditions
    // all should hold without actually doing a refinement or balance
    std::cout << "inclusionsurface checking if original refinement and balance conditions were met" << std::endl;
    if ( bst.would_refine_near_surface( inclusion_min_dxy, inclusion_max_dz ) )
    {
      std::cout << "ERROR: inclusionsurface refine near surface violated" << std::endl;
    }
    if (do_balance && bf.would_balance() )
    {
      std::cout << "ERROR: inclusionsurface two balance violated" << std::endl;
    }
    
  }
  
  // ============================ boxes - acousticsurface finish ===========
  // final balancing, cutting and merging and meshing for acousticsurface
  if (do_acousticsurface)
  {
    BoxSurfaceTool &bwt = *bwt_p;
    
    // debug
    bwt.assign_global_ids(true);
    std::cout << "acousticsurface refining near surface #hexes = " << bt.get_number_hexes() << std::endl;
    
    
    // balance so boxes on either side of surface have same xy size
    bool changed = false;
    do
    {
      changed = bwt.balance_for_merging();
      if (changed && exactly_two_triangles)
      {
        changed = bst.balance_for_two_triangles();
      }
    } while (changed);

    // need to do here, not previously, as there are new leaves!
    bst.set_output_boxes();

    // debug
    bwt.assign_global_ids(true);
    std::cout << "acousticsurface balance for merging #hexes = " << bt.get_number_hexes() << std::endl;
    
    // debug
    bwt.assign_global_ids();
    
    // recheck balance conditions
    // all should hold without actually doing a refinement or balance
    if ( bwt.would_refine_near_surface() )
    {
      std::cout << "ERROR: acousticsurface refine near surface violated" << std::endl;
    }
    if ( bwt.would_balance_for_merging() )
    {
      std::cout << "ERROR: acousticsurface balance for merging violated" << std::endl;
    }
    
    bwt.mesh_boxes(); // cut and merge

    // debug
    //bwt.assign_global_ids(true);
    std::cout << "acousticsurface cut and merge #hexes = " << bt.get_number_hexes() << std::endl;
    
    bwt.assign_box_acoustic_zone();
  }
  
  // ============================ boxes - inclusion finish ===========
  if (do_boxes)
  {
    BoxTreeTool t( &bt );
    t.assign_global_ids(true);
    
    std::cout << "Created #boxes = " << bt.get_number_leaves() << " and #hexes = " << bt.get_number_hexes() << std::endl;
    
    // write out the faces of boxes bounding the shell around the tetrahedra
    BoxSurfaceInclusionTool::BoxFacesVec box_faces, imprint_faces;
    BoxSurfaceInclusionTool::BoxFacesVecVec box_faces_domain_sides;
    bst.gather_box_tet_faces( box_faces, box_faces_domain_sides, imprint_faces );
    // bst.write_box_tet_faces(imprint_faces, "box_imprint.facet" );
    
    bst.write_box_tet_faces( box_faces, "hex_tet.facet" );
    // for (size_t i = 0; i < box_faces_domain_sides.size(); ++i)
    //  bst.write_box_tet_faces( box_faces_domain_sides[i], "hex_tet_domain_bdy" + std::to_string(i) + ".facet" );
    t.write_box_facet( "hexes.facet" );

    bst.assign_box_elastic_inclusion_zones();
  }
  
  if (do_acousticsurface || do_boxes)
  {
    BoxTreeTool t( &bt );
    t.assign_global_ids(false);
    
    t.write_box_zones( "zone" );
    
    // now write out the kept boxes themselves
    t.write_off_file( "inclusion.off" );
    
    t.write_ply( "inclusion.ply" );
    
    t.write_cubit_mesh_jou( "inclusion_mesh.jou" );
    
    SurfaceInclusionFactory sf(&ss);
    sf.write_cubit_surface_jou( "inclusion_surf.jou" );
    
    // slowest
    t.write_face_adjacencies(  "inclusion.con" );
    t.write_nodal_coordinates( "inclusion.msh" );
  }

  // ============================ tets ===========
  bool do_tets = true && do_inclusion;
  if ( do_tets )
  {
    bst.tri_tet_inclusion_surface(  tri_edge_length, exactly_two_triangles );
  }
  
  
}

void Example::create_miniinclusion()
{
  // open file
  // erases any old data
  std::fstream file("topMiniinclusion1.xyz", std::ios::out);
  
  for (double x = 0.; x < 110.; x+=50.)
  {
    for (double y = 0.; y < 110.; y+=25.)
    {
      double z = 50;
      z += ((double) rand()) / RAND_MAX;
      file << x << "   " << y << "   " << z << std::endl;
    }
  }
  file.close();
}

bool in_sphere( Point sphere_center, double sphere_radius, double x, double y)
{
  double dx = x-sphere_center.x;
  double dy = y-sphere_center.y;
  
  return dx*dx + dy*dy  < sphere_radius * sphere_radius;
}

void sphere_z( Point sphere_center, double sphere_radius, double x, double y, double &ztop, double &zbot)
{
  double dx = x-sphere_center.x;
  double dy = y-sphere_center.y;
  
  double dz2 = sphere_radius * sphere_radius - dx*dx - dy*dy;
  if (dz2 < 0.)
    dz2 = 0.;
  
  double dz = sqrt( dz2 );
  
  ztop = sphere_center.z + dz;
  zbot = sphere_center.z - dz;
}

void Example::create_mini2inclusion()
{

  // two flat layers with a hollow sphere in the middle
  Point sphere_center(50,50,50);
  double sphere_radius = 20.;
 
  // open file
  // erases any old data
  std::fstream fileT1("topMini2inclusion1.xyz", std::ios::out);
  std::fstream fileT2("topMini2inclusion2.xyz", std::ios::out);
  std::fstream fileB1("botMini2inclusion1.xyz", std::ios::out);
  std::fstream fileB2("botMini2inclusion2.xyz", std::ios::out);
  
  for (double x = 0.; x < 110.; x+=10.) // 50
  {
    for (double y = 0.; y < 110.; y+=5.)  // 25
    {
      // T1 always
      double z = 20;
      z += ((double) rand()) / RAND_MAX;
      fileT1 << x << "   " << y << "   " << z << std::endl;
      
      // acousticsurface flat layer
      double zz = 85;
      // zz += 2. * ((double) rand()) / RAND_MAX; // causes an imprint error in cubit
      
      if ( in_sphere( sphere_center, sphere_radius, x, y ) )
      {
        double ztop, zbot;
        sphere_z( sphere_center, sphere_radius, x, y, ztop, zbot );
        
        fileB1 << x << "   " << y << "   " << ztop << std::endl;
        fileT2 << x << "   " << y << "   " << zbot << std::endl;
        
        fileB2 << x << "   " << y << "   " << zz << std::endl;
      }
      else
      {
        fileB1 << x << "   " << y << "   " << zz << std::endl;

        fileT2 << x << "   " << y << "   " << "nan" << std::endl;
        fileB2 << x << "   " << y << "   " << "nan" << std::endl;
        
      }
    }
  }
}

void Example::full_mesh()
{
  const bool toy = false;
  
  SurfaceInclusion ss;
  SurfaceInclusionFactory ssf;
  ssf._s = &ss;
  ssf.read( "Inclusion" );
  // bool OK =
  ss.verify();
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
  
}

void Example::volume_mesh_workflow()
{
  SurfaceInclusion ss;
  SurfaceInclusionFactory ssf;
  ssf._s = &ss;
  ssf.read( "Mini2inclusion" );

  BoxTree bt;
  BoxTreeTool btt(&bt);
  BoxSurfaceInclusionTool bst( &bt, &ss);

  bst.set_domain_size(0., 100.);

  bst.connect_manifolds(); // builds std::vector<Triangulation*> &triangulations,
  
  // the following is a prototype for bst.tri_tet_inclusion_surface( triangulations );
  // but without dealing with the boxes, just the domain boundaries
  
  // switched from cubit journal to cubit python file
  //std::fstream cubit_journal_file("inclusion_mesh.jou", std::ios::out);
  std::fstream cubit_script_file("inclusion_mesh.py", std::ios::out);
  cubit_script_file << "cubit.cmd('label surface name')\n";

  // order triangulations by layer from top z=0 to bottom z=domain.max_x
  std::vector<int> is_closed; // is triangulation a closed shell, or does in interect the domain bdy? (in z order)
  std::vector< std::string > t_names; // names of triangulation files, in z order
  {
    std::vector<int> z_order;
    {
      std::vector<int> local_closed;
      bst.sort_triangulations_by_z( bst._triangulations, local_closed, z_order );
      for (size_t ti = 0; ti < bst._triangulations.size(); ++ti)
      {
        is_closed.push_back( local_closed[ z_order[ti]] );
      }
    }
    
    // write out facet files in z order
    // issue cubit commands to read them in as mesh based geometry
    cubit_script_file << "# importing triangulations as surfaces in ascending z-coordinate order\n";
    for (size_t ti=0; ti < bst._triangulations.size(); ++ti)
    {
      TriangulationTool TT( bst._triangulations[ z_order[ti] ] );
      std::string t_name = "inclusion_surface_triangulation_";
      std::string tri_surf_name = t_name + std::to_string(ti);
      std::string tri_surf_file_name = tri_surf_name + ".facet";
      TT.write_facet(tri_surf_file_name);
      cubit_script_file << "cubit.cmd('import facets \"" << tri_surf_file_name << "\" feature_angle 0')\n";
      cubit_script_file << "t_id = cubit.get_last_id(\"surface\")\n";
      t_names.push_back( tri_surf_name );
      cubit_script_file << "cubit.cmd('surface ' + str(t_id) + ' name \"" << t_names.back() << "\"')\n\n";
      //  cubit_script_file << "id = cubit.get_entity_from_name(\"t0*\")\n";  // id from name
      //  cubit_script_file << "name = cubit.get_entity_name(\"surface\", t0_id )\n";  // name from id
    }
  }
  
  // write out bottom of domain as a single quad ...?? or just generate it on the fly in cubit as we do now...

  // cubit_journal_file << "simplify Surface " << triangulation0_id << " Respect Vertex "; id...
  
  // bt.root; // this is a single box for the domain...

  // write out the box faces bounding the part of the domain to be triangulated
  // including some faces on the domain boundary
  std::string fname;
  // write each of the box side faces of the domain
  size_t box_id = 0;
  cubit_script_file << "# importing box faces outside the triangulation and domain boundary sides\n";
  cubit_script_file << "# assumption: all the triangulated surfaces lie in a topological ball of (not-written) boxes, so boundary of the tet-meshed area is a single shell\n";
  for (int f = 0; f < 6; ++f)
  {
    // if (box.contains_surface())
    //   check each face to see if has a neighbor without surface, and if so, write that face out.
    fname = btt.write_box_face( *bt.root, f );
//    cubit_journal_file << "import facets \"" << fname << "\" feature_angle 0\n";
//    cubit_journal_file << "#{_surf_id=Id(\"surface\")}" << std::endl;
    cubit_script_file << "cubit.cmd('import facets \"" << fname << "\" feature_angle 0')\n";
    cubit_script_file << "surf_id = cubit.get_last_id(\"surface\")\n";
    std::string cubit_name_b = "surf_b_" + std::to_string(box_id);
    std::string cubit_name_f = + "_f" + std::to_string(f);

    // give surface names based on sides
    if ( f != 0 && f != 5 )
    {
      // name the surface on domain side <f> as "b<id>_domain_bdy_f<f>", etc
      cubit_script_file << "cubit.cmd('surface ' + str(surf_id) + ' name \"" << cubit_name_b << "domain_bdy" << cubit_name_f << "\"')\n" << std::endl;
    }
    else
    {
      // name the surface on top and bottom something else
      cubit_script_file << "cubit.cmd('surface ' + str(surf_id) + ' name \"" << cubit_name_b << "box_bdy" << cubit_name_f << "\"')\n" << std::endl;
      if ( f==5 )
        cubit_script_file << "cubit.cmd('surface ' + str(surf_id) + ' name \"" << "dummy_imprint" << "\"')\n" << std::endl;
    }
    
    // no need to intersect the triangulation with the boxes
    // cubits imprint and merge seems to be able to handle this case
    // hack: output a mesh consisting of four mega quads, an empty band spanning each side of the domain and containing the triangulated inclusion surface
    
    /* here is a way to deal with
    std::vector<Node*> chain;
    TT.find_boundary_edge_chain(chain, f);
    Node face_nodes[4], loop_nodes[8];
    bt.root->face_nodes(f, face_nodes);
    // partition the face nodes into the above and below set
    partition_face_nodes(edge_chain, face_nodes, above_nodes, below_nodes );
    // when there is more than one face, cut the chain
    // cut_chain bti , i
     */
  }
  
  // add a surface on the bottom of the domain, assuming no boxes went that low...
  // b0_f5 takes care of it...
//  double dx = ss.max_x() - ss.min_x();
//  double dy = ss.max_y() - ss.min_y();
//  cubit_script_file << "# assumption: there are no boxes on the bottom of the domain, and we have to create surface there to close the volume.\n";
//  cubit_script_file << "cubit.cmd('create surface rectangle width " << dx << " height " << dy << "')\n";
//  cubit_script_file << "bottom_s_id = cubit.get_last_id(\"surface\")\n";
//  cubit_script_file << "bottom_b_id = cubit.get_last_id(\"body\")\n";
//  cubit_script_file << "cubit.cmd('surface ' + str(bottom_s_id) + ' name \"domain_bottom\"')\n";
//  cubit_script_file << "cubit.cmd('body ' + str(bottom_b_id) + ' move " << dx/2 << " " << dy/2 << " " << bt.get_domain().max_z() << "')\n";
  
  cubit_script_file << "cubit.cmd('# imprinting and merging the faceted geoemtry, for a contiguous mesh')\n";
  cubit_script_file << "cubit.cmd('set developer commands on')\n";
  
  cubit_script_file << "# imprinting curved surfaces with itself fractures it into a bunch of surfaces.\n";
  cubit_script_file << "# let's do that first and then regather them.\n";
  for (size_t i = 0; i < bst._triangulations.size(); ++i)
  {
    cubit_script_file << "\npre_s = cubit.get_last_id(\"surface\")\n";
    cubit_script_file << "cubit.cmd('imprint body in " << t_names[i] << " body in dummy_imprint')\n";
    cubit_script_file << "post_s = cubit.get_last_id(\"surface\")\n";
    cubit_script_file << "for s in range(pre_s+1,post_s+1):\n";
    cubit_script_file << "  n=cubit.get_entity_name(\"surface\",s)\n";
    cubit_script_file << "  # if surface exists\n";
    cubit_script_file << "  if n!=\"\":\n";
    cubit_script_file << "    cubit.cmd('surface ' + str(s) + ' name \"" << t_names[i] << "\"')\n";
    cubit_script_file << "# should group both the old and new surfaces\n";
    cubit_script_file << "cubit.cmd('group \"g_" << t_names[i] << "\" equals surface name \"" << t_names[i] << "\"')\n";
  }
  
  
  cubit_script_file << "\ncubit.cmd('imprint all')\n";
  cubit_script_file << "cubit.cmd('merge all')\n";
  
  // gather the surfaces on each of the four faces, for partitioning into volumes and such
  cubit_script_file << "# unfortunately, facet-based imprinting does not propagate names!\n# find domain side surfaces again and assign names and group them in the script\n";
  cubit_script_file << "xmin = " << ss.min_x() << "\nymin = "<< ss.min_y() << "\nxmax = " << ss.max_x() << "\nymax = " << ss.max_y() << "\n";
  
  cubit_script_file << "last_s = cubit.get_last_id(\"surface\")\n";
  cubit_script_file << "for s in range(1,last_s+1):\n";
  cubit_script_file << "  n=cubit.get_entity_name(\"surface\",s)\n";
  cubit_script_file << "  # if surface exists\n";
  cubit_script_file << "  if n!=\"\":\n";
  cubit_script_file << "    ct = cubit.get_surface_centroid(s)\n";
  cubit_script_file << "    if abs(ct[0] - xmin) < xmax*1e-4:\n";
  cubit_script_file << "      cubit.cmd('surface ' + str(s) + ' name \"" << "domain_bdy_f4" << "\"')\n";
  cubit_script_file << "    if abs(ct[0] - xmax) < xmax*1e-4:\n";
  cubit_script_file << "      cubit.cmd('surface ' + str(s) + ' name \"" << "domain_bdy_f2" << "\"')\n";
  cubit_script_file << "    if abs(ct[1] - ymin) < ymax*1e-4:\n";
  cubit_script_file << "      cubit.cmd('surface ' + str(s) + ' name \"" << "domain_bdy_f1" << "\"')\n";
  cubit_script_file << "    if abs(ct[1] - ymax) < ymax*1e-4:\n";
  cubit_script_file << "      cubit.cmd('surface ' + str(s) + ' name \"" << "domain_bdy_f3" << "\"')\n\n";

  std::string g_domain_bdy_f_name = "g_domain_bdy_f"; //f1, f2, f3, f4, f5
  for (size_t f = 1; f < 5; ++f)
  {
    // for this cubit command, with name "name_string", means with name containing "name_string" as a substring!
//    cubit_journal_file << "group \"" << g_domain_bdy_f_name << f << "\" equals surface with name \"domain_bdy_f" << f << "\" ";
    cubit_script_file << "cubit.cmd('group \"" << g_domain_bdy_f_name << f << "\" equals surface with name \"domain_bdy_f" << f << "\"')\n";
    // g_id1 = group of surfaces that are on domain side 1, etc.
    cubit_script_file << "g_id" << f << " = cubit.get_id_from_name(\"" << g_domain_bdy_f_name << f << "\")\n";
  }
  
  cubit_script_file << "# assume each surface intersects the domain boundary in a single topological circle, or not at all\n";
  
  // how many are there?
  cubit_script_file << "num_layers = len(cubit.get_group_surfaces( g_id1 ))\n";
  cubit_script_file << "# assume all the other groups have the same number of layers\n";

  // hardcode two layers for now...
  
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
  
  cubit_script_file << "# gather groups of top and bottom box surfaces\n";
  cubit_script_file << "cubit.cmd('group \"vz0\" equals surface name \"box_bdy_f0\"')\n";  // when we have real octree boxes outside, gather their f5 not f0
  cubit_script_file << "cubit.cmd('group \"vz5\" equals surface name \"box_bdy_f5\"')\n";  // " " "   f0 not f5

  // composite away some things ??

//  cubit_journal_file << "surface all scheme trimesh\n";
//  cubit_journal_file << "curve all interval 1\n";
//  cubit_journal_file << "mesh surface all\n";
//  cubit_journal_file << "block 1 surface all\n";
//  std::string surf_meshes = "surface_meshes.exo";
//  cubit_journal_file << "export mesh \"" << surf_meshes << "\" dimension 3 overwrite\n";

  cubit_script_file << "\n\ncubit.cmd('surface all scheme trimesh')\n";
  cubit_script_file << "# todo: replace next line with some real sizing information.\n";
//  cubit_script_file << "cubit.cmd('curve all interval 2')\n";
  cubit_script_file << "cubit.cmd('curve all size 10')\n";
  cubit_script_file << "cubit.cmd('mesh surface all')\n";

  cubit_script_file << "# put surfaces in groups that enclose volumes, for those volumes bounded by the domain boundary\n";
  // from top z=0 downwards

  //==== first layer
  // top and side
  size_t ti = 0;
  size_t vol_id = 1;
  cubit_script_file << "cubit.cmd('group \"vol" << vol_id << "\" unite vz0 with vs" << vol_id << "')\n";
  bool closed = is_closed[ ti ] > 0;
  // interior shells
  while (closed)
  {
    cubit_script_file << "cubit.cmd('group \"vol" << vol_id << "\" add surface in g_" << t_names[ti] << "')\n";
    ++ti;
    closed = (ti < bst._triangulations.size()) && (is_closed[ ti ] > 0);
  }
  // bottom of first layer
  cubit_script_file << "cubit.cmd('group \"vol" << vol_id << "\" add surface in g_" << t_names[ti] << "')\n";
  
  //==== middle and last layer
  while (ti < bst._triangulations.size() && !closed)
  {
    ++vol_id;
    // add last bottom as top
    cubit_script_file << "cubit.cmd('group \"vol" << vol_id << "\" equals surface in g_" << t_names[ti] << "')\n";
    // add next side
    cubit_script_file << "cubit.cmd('group \"vol" << vol_id << "\" unite vol" << vol_id << " with vs" << vol_id << "')\n";
    ++ti;
    
    // add any shells
    closed = (ti < bst._triangulations.size()) && (is_closed[ ti ] > 0);
    while (closed)
    {
      cubit_script_file << "cubit.cmd('group \"vol" << vol_id << "\" add surface in g_" << t_names[ti] << "')\n";
      ++ti;
      closed = (ti < bst._triangulations.size()) && (is_closed[ ti ] > 0);
    }
    // add bottom
    if (ti < bst._triangulations.size())
      cubit_script_file << "cubit.cmd('group \"vol" << vol_id << "\" add surface in g_" << t_names[ti] << "')\n";
    else
      cubit_script_file << "cubit.cmd('group \"vol" << vol_id << "\" unite vz5 with vol" << vol_id << "')\n";
  }
  
  //===== add a volume for each closed shell, assuming they are not nested
  cubit_script_file << "# assign a volume for each closed shell surface\n";
  cubit_script_file << "# assumption: all closed shells enclose a single volume, and are not nested\n";
  for (size_t ti = 0; ti < bst._triangulations.size(); ++ti)
  {
    bool closed = (is_closed[ ti ] > 0);
    if ( closed )
    {
      ++vol_id;
      cubit_script_file << "cubit.cmd('group \"vol" << vol_id << "\" add surface in g_" << t_names[ti] << "')\n";
    }
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
  cubit_script_file << "# import the triangulation for each shell and tet mesh the interior\n";
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

// more cubit commands for reference:


// now read in the surface triangle meshes as shells of volumes and tet mesh them one by one
// this doesn't work for volumes with more than one shell
//    cubit_script_file << "cubit.cmd('import mesh geometry \"" << surf_meshes << "_" << v << ".exo\"')\n";
//    cubit_script_file << "cubit.cmd('create body surface all')\n"; // destroys the surface mesh, import it again!
//    cubit_script_file << "cubit.cmd('import mesh \"" << surf_meshes << "_" << v << ".exo\" body all')\n";
//    cubit_script_file << "cubit.cmd('volume all scheme tetmesh')\n";
//    cubit_script_file << "cubit.cmd('mesh volume all')\n";

// creating geometry with two shells defined by meshes fails
//crash making body from multiple shells, mesh-based geometry.
//I can make a body out of each shell individually no problem.
//cubit.cmd('reset')
//cubit.cmd('import mesh geometry "surface_meshes_2.exo"')
//cubit.cmd('create body surface all')
//- Scott
//
//Corey says this is the way to mesh the volume between two shells
//reset
//import mesh 'surface_meshes_2.exo' no_geom
//tetmesh tri all
//create mesh geometry tet all
//You need to have 3d volume elements to create a mesh-based geometry volume.
//--Corey Earnst


// make the triangulation have just one boundary curve
// Composite Create Curve <id_range> [Keep Vertex <id_list>] [Angle <degrees>]
// cubit_journal_file << "# ignore warnings from the next composite command\n";
// cubit_journal_file << "Composite Create ";
// cubit_journal_file << "curve in surface with name '" << t0_name << "'" << std::endl;
// No need to keep vertices. Imprinting with the mega quad facets should take care of it.

//  Volume Location options:
//  { [Position] <xval yval zval> | Last | [At] {Node|Vertex} <id_list> |
//    [On] Curve <id_list> [location on curve options] |
//    [On] Surface <id_list> [{Close_To|At Location {options}}|CENTER] |
//    [On] Plane <options> {Close_To|At} Location {options} |
//    Center Curve <id_list> |
//    Extrema {Curve|Surface|Volume|Body|Group} <id_list> [Direction] {options}
//    [Direction {options}] [Direction {options}] |
//    Fire Ray Location {options} Direction {options} At {geometry_entities}
//    [Maximum Hits <val>] [Ray Radius <val>] |
//    Between { Location {options} Location {options} |
//      { Location {options} Project {Curve|Surface} <id> }
//      [Stop] [Fraction <val>] }
//    [ Move [All] { <xval yval zval> | {Dx|X|Dy|Y|Dz|Z} <val> |
//     Direction {options} Distance <val> } ]
//    [ Swing [All] [About] Axis {options} Angle <ang> ]
//    [Stop]
//
//  Surface Location options
//  Direction options:
//  { [Vector] <xval yval zval> | Last | x|y|z|nx|ny|nz |
//    [On] | [At] Curve <id> {location on curve options} [TANGENT|Curvature] |
//    [On] Surface <id> [{Close_To|At Location {options}}|CENTER] |
//    [From] { Location <options> Location <options>} |
//    { Location <options> Project {Curve|Surface} <id> }
//    [ Rotate {options} ] [ Cross [With] Direction {options} ]
//    [Reverse] [Unitlength] [Stop]
//  Location options:
//    { [Position] <xval yval zval> | Last | [At] {Node|Vertex} <id_list> |
//      [On] Curve <id_list> [location on curve options] |
//      [On] Surface <id_list> [{Close_To|At Location {options}}|CENTER] |
//      [On] Plane <options> {Close_To|At} Location {options} |
//      Center Curve <id_list> |
//      Extrema {Curve|Surface|Volume|Body|Group} <id_list> [Direction] {options}
//      [Direction {options}] [Direction {options}] |
//      Fire Ray Location {options} Direction {options} At {geometry_entities}
//      [Maximum Hits <val>] [Ray Radius <val>] |
//      Between { Location {options} Location {options} |
//        { Location {options} Project {Curve|Surface} <id> }
//        [Stop] [Fraction <val>] }
//      [ Move [All] { <xval yval zval> | {Dx|X|Dy|Y|Dz|Z} <val> |
//       Direction {options} Distance <val> } ]
//      [ Swing [All] [About] Axis {options} Angle <ang> ]
//      [Stop]
//  Location(s) On Curve(s) options:
//      { MIDPOINT | Start | End |
//        Fraction <val 0.0 to 1.0> [From Vertex <id> | Start|End] |
//        Distance <val> [From {Vertex|Curve|Surface} <id> | Start|End] |
//        {{Close_To|At} Location {options} | Position <xval><yval><zval> |
//          {Node|Vertex} <id>} |
//        Extrema [Direction] {options} [Direction {options}] [Direction {options}] |
//        Segment <num_segs> |
//        Crossing {Curve|Surface} <id_list> [Bounded|Near] }
//  Plane options:
//      { {Location|Vertex|Node} <origin> Direction <normal> |
//        {Location|Vertex|Node} <origin> Direction <vec on plane> Direction <vec on plane> |
//        {Location|Vertex|Node} <2 locations> Direction <vector on the plane> |
//        {Location|Vertex|Node} <3 locations> |
//        {Location|Vertex|Node} <location list> |
//        Surface <id> [at location <loc>] |
//        [Normal To] Curve <id> [loc on curve options] |
//        Arc Curve <id> |
//        Linear Curve <id id> |
//        Direction <Normal> Coefficient <val> |
//        X|Xplane|Yz|Zy|Y|Yplane|Zx|Xz|Z|Zplane|Xy|Yx |
//        Last }
//      [ Offset <val> ]
//      [ Move { <xval yval zval> | {Dx|X|Dy|Y|Dz|Z} <val> |
//       Direction {options} [Distance <val>] | [To] Location {options} } ]
//      [ Spin [About] Axis {options} Angle <ang> ]




//  Import Mesh Geometry '<exodusII_filename>' [Block <id_range>|ALL]
//  [Start_id <id>]
//  [Use [NODESET|no_nodeset] [SIDESET|no_sideset] [FEATURE_ANGLE <angle=135>]
//   [LINEAR|Gradient|Quadratic|Spline]
//   [Deformed {Time <time>|Step <step>|Last} [Scale <value>] ] ]
//  [MERGE|No_Merge] [export_facets <1|2|3>]
//  cubit_journal_file << "import mesh geometry \"" << surf_meshes << "\" feature_angle 0\n";
//  cubit_script_file << "cubit.cmd('import mesh geometry \"" << surf_meshes << "\" feature_angle 0 block 2')\n";

// zzyk todo
// Create Body Surface ...id range...
// cubit_journal_file << "import mesh \"" << surf_meshes << "\" surface in volume ...id...\n";

//  cubit_journal_file << "volume all scheme tetmesh\n";
//  cubit_journal_file << "mesh volume all\n";
//  cubit_journal_file << "# by default, each volume get's its own block\n";
//  cubit_journal_file << "export mesh \"volume_meshes.exo\" overwrite\n";
//
//  cubit_script_file << "cubit.cmd('volume all scheme tetmesh')\n";
//  cubit_script_file << "cubit.cmd('mesh volume all')\n";
//  cubit_script_file << "# by default, each volume get's its own block, but apparently not for tets\n";
//  cubit_script_file << "cubit.cmd('block 1 volume 1')\n";
//  cubit_script_file << "cubit.cmd('block 2 volume 2')\n";
//  cubit_script_file << "cubit.cmd('export mesh \"volume_meshes.exo\" overwrite')\n";
