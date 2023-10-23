//
//  TriangulationTool.h
//  BoxTreeMesh
//
//  Created by Mitchell, Scott A on 10/24/16.
//  Copyright (c) 2016 Sandia National Labs. All rights reserved.
//

#ifndef __BoxTreeMesh__TriangulationTool__
#define __BoxTreeMesh__TriangulationTool__

#include <stdio.h>

#include "triangulation.h"

class Box;

class TriangulationTool
{
public:
  TriangulationTool( Triangulation * T ) : _T(T) {}
  
  // off file format
  void write_off_file( std::string fname = "triangulation.off", const double nodal_scale_factor = 1.0 );
  
  // cubit script to create free mesh
  void write_cubit_mesh_jou( std::string fname = "cubit_triangulation.jou", const double nodal_scale_factor = 1.0 );

  // ply file format
  void write_ply( std::string fname = "triangulation.ply", const double nodal_scale_factor = 1.0 );

  //  void write_exodus( std::string fname = "triangulation.exo", const double nodal_scale_factor = 1.0 );
  
  void write_facet( std::string fname = "triangulation.facet", const double nodal_scale_factor = 1.0 );

  
  // ensure the triangulation is well formed, logical tests
  // true if OK
  bool good_connectivity(double min_x = 0., double min_y = 0., double max_x = 50000., double max_y = 50000., std::vector<Edge> *open_edges = 0);
  
  // if the box has a non-empty intersection with a triangle, then return true and one such triangle
  // currently very slow because we don't have a search datastructure for finding nearby points and edges and triangles
  // does box contain a node of the triangle? const time
  static bool triangle_node_in_box( const Box *b, const Triangle *t );
  // does an edge of this triangle cross a box face? const time
  static bool triangle_edge_cross_box_face( const Box *b, const Triangle *t );
  // does box intersect any triangle? Beware this is brute force search, very slow for large triangulations!!!
  bool box_intersects_triangle( const Box*b, Triangle *&t  );

protected:
  Triangulation *_T;
  
};

#endif /* defined(__BoxTreeMesh__TriangulationTool__) */
