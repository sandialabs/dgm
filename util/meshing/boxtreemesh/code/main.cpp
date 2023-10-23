//
//  main.cpp
//  octree
//
//  Created by Mitchell, Scott A on 1/4/16.
//  Copyright (c) 2016 Sandia National Labs. All rights reserved.
//

#include <iostream>
// #include "boxtree.h"
#include "testboxtree.h"
#include "example.h"
#include "surface.h"
#include "surfacefactory.h"
#include "boxsurfacetool.h"

int main(int argc, const char * argv[])
{

  std::cout << "Starting BoxTree\n";
  
  // use this to mesh the [top|bot]Inclusion#.xyz and acousticsurface.xyz files in the current directory
  if (/* DISABLES CODE */ (1))
  {
    Example ex;
    ex.inclusion_manifold();
    return 0;
  }
  

  
  if (/* DISABLES CODE */ (0))
  {
    Example ex;
    ex.make_surface_3();
    return 0;
  }

  if (/* DISABLES CODE */ (0))
  {
    TestBoxTree test;
    return test.test_inclusionbodies();
  }

  if (/* DISABLES CODE */ (0))
  {
    Example ex;
    // ex.create_miniinclusion(); // do once
    // ex.create_mini2inclusion(); // do once
    ex.volume_mesh_workflow();
    return 0;
  }
  
  if (/* DISABLES CODE */ (0))
  {
    Example ex;
    double element_size = 4.0; // 2.0; //1.0 is original
    ex.slide(element_size);
    return 0;
  }

  if (/* DISABLES CODE */ (1))
  {
    Example ex;
    ex.create_test_suite_A();
    return 0;
  }

  if (/* DISABLES CODE */ (0))
    Box::test_lookups();
  
  if (/* DISABLES CODE */ (0))
    {   Example ex;  ex.create_2(); }

  // examples
  if (/* DISABLES CODE */ (0))
  {
    {   Example ex;  ex.create_1(); }
    {   Example ex;  ex.create_2(); }
    {   Example ex;  ex.create_3(); }
    {   Example ex;  ex.create_4(); }
    {   Example ex;  ex.create_5(); }
    {   Example ex;  ex.create_6(); }
    return 0;
  }

  // big example
  if (/* DISABLES CODE */ (0))
  {
    {   Example ex;  ex.create_7(); }
  }
  
  if (/* DISABLES CODE */ (0))
  {
    // an unbalanced tree
    Example ex; ex.create_8();
    ex.test.test_balance( &ex.tree, 2, FACE);
    ex.tool.assign_global_ids(true);
    ex.tool.write_face_adjacencies(  "boxes-balanced.con" );
    ex.tool.write_nodal_coordinates( "boxes-balanced.msh" );

  }

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
    
    // read/write surface
    // acousticsurface examples
    if (/* DISABLES CODE */ (0))
    {
      SurfaceFactory sf(&surf);
      sf.read("acousticsurface.xyz");
      sf.write("acousticsurfaceCopy.xyz");
    }
    // for a big mesh, try parameters
    // (0, 0, 50, 25, 30, 30)
    else if (/* DISABLES CODE */ (0))
    {
      SFFlat sf(&surf);
      sf.depth = nominal_surface_depth;
      sf.set_surface(xmin, ymin, dx, dy, x_size, y_size);
      sf.write("acousticsurfaceFlat.xyz");
    }
    else if (/* DISABLES CODE */ (0))
    {
      SFSlant sf(&surf);
      sf.depth = nominal_surface_depth;
      sf.set_surface(xmin, ymin, dx, dy, x_size, y_size);
      sf.write("acousticsurfaceSlant.xyz");
    }
    else if (/* DISABLES CODE */ (0))
    {
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
      
      sf.write("acousticsurfaceSine.xyz");
    }
    else if (/* DISABLES CODE */ (1))
    {
      SFRandom sf(&surf);
      sf.depth = nominal_surface_depth;
      sf.slope = nominal_surface_depth / 8;
      sf.set_surface(xmin, ymin, dx, dy, x_size, y_size);
      sf.write("acousticsurfaceNoise.xyz");
    }

  
    BoxTree bt;
    BoxSurfaceTool bst( &bt, &surf);

    // make sure surface was property defined
    assert( surf.min_x() < surf.max_x() );
    assert( surf.min_y() < surf.max_y() );

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
    double max_dz =  toy ? 20 : 500;
    
    // refine boxes that are not smaller (in every coordinate) than this size
    //  Point upper_size( _s->grid_x() * grid_factor, _s->grid_y() * grid_factor, _bt->get_domain().diagonal_z() );
    Point upper_size( min_dxy, min_dxy, bt.get_domain().diagonal_z() );
    
    // uniform
    // max_dz = 10000;
    // RefinerNearSurface refiner(&bt,&surf);

    // denser in the corner
    RefinerVariableNearSurface refiner(&bt, &surf);

    refiner.child_size = two_box;
    refiner.upper_size = upper_size;
    refiner.height_variation = max_dz;
    
    bst.set_refiner_near_surface(&refiner);
    bst.refine_near_surface();

    // debug
    bst.assign_global_ids(true);
    std::cout << "refining near surface #hexes = " << bt.get_number_hexes() << std::endl;

    
    // balance so boxes on either side of surface have same xy size
    bst.balance_for_merging();

    // debug
    bst.assign_global_ids(true);
    std::cout << "balance for merging #hexes = " << bt.get_number_hexes() << std::endl;

//    // refine in xy only if surface varies too much
//    bst.refine_xy_to_reduce_surface_variation( two_box );
    
    // doesn't work
//    // balance in xy direction only for merging
//    bst.balance_xy_for_merging();

    
//    bool changed = false;
//    int num_passes(0);
//    do
//    {
//      // refine in xy only if surface varies too much
//      changed = bst.refine_xy_to_reduce_surface_variation( two_box );
//      
//      // balance so boxes on either side of surface have same xy size
//      if ( changed )
//      {
//        std::cout << "balance for merging second pass skipped" << std::endl;
//        // bst.balance_for_merging();
//      }
//      
//      ++num_passes;
//      
//    } while (changed && num_passes < 12);

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
//    if ( bst.would_refine_xy_to_reduce_surface_variation() )
//    {
//      std::cout << "ERROR: refine xy to reduce surface variation violated" << std::endl;
//    }
    
    bst.mesh_boxes(); // cut and merge
    
    // debug
    bst.assign_global_ids(true);
    std::cout << "cut and merge #hexes = " << bt.get_number_hexes() << std::endl;

    
    TestBoxTree tbt;
    tbt.test_adjacent_face_subsets( &bt );

    
    const bool do_facade = true;
    
    // take just a facade of hexes, for creating small test problems
    if (do_facade)
    {
      bst.discard_hexes(2, 0.25);
      bst.discard_hexes(3, 0.25);
      
      tbt.test_adjacent_face_subsets( &bt );
    }
    
    //raw boxes without cutting and merging
    BoxTreeTool t( &bt );
    t._write_corner_coords = false;
    t.assign_global_ids(true);
    
    std::cout << "Created #boxes = " << bt.get_number_leaves() << " and #hexes = " << bt.get_number_hexes() << std::endl;
    t.write_face_adjacencies(  "acoustic.con" );
    t.write_nodal_coordinates( "acoustic.msh" );
    t.write_boundary_conditions( "acoustic.bc" );

    t.write_off_file( "acoustic.off" );

    t.write_ply( "acoustic.ply" );

    t.write_cubit_mesh_jou( "acoustic_mesh.jou" );
    t._write_corner_coords = true;
    t.write_cubit_mesh_jou( "acoustic_box.jou" );
    t._write_corner_coords = false;

    SurfaceFactory sf(&surf);
    sf.write_cubit_surface_jou( "acoustic_surf.jou" );
  }
  
  
  // test
  if (/* DISABLES CODE */ (0))
  {
    TestBoxTree test;
    //  test.create_tree();
  
    //  test.refine_tree();
  
    //  test.test_adjacency();
  
    test.test_neighbor_functions();
  }
  std::cout << "Done BoxTree\n";

  return 0;
}