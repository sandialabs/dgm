//
//  TriangulationTool.cpp
//  BoxTreeMesh
//
//  Created by Mitchell, Scott A on 10/24/16.
//  Copyright (c) 2016 Sandia National Labs. All rights reserved.
//

#include "TriangulationTool.h"
#include <fstream>
#include <cstdio>
#include <iomanip>
#include "boxtree.h"

// from /Users/samitch/Documents/repos/ct/boxtreemesh/exodus/seacas-exodus/include
//#include "exodusII.h"


void TriangulationTool::write_off_file( std::string fname, const double f )
{
  std::cout << "Writing triangulation to Object File Format (.off) file " << fname << "...";
  std::cout.flush();
  
  // assign ids if not already done
  
  // open file
  // erases any old data
  std::fstream file(fname.c_str(), std::ios::out);
  
  // header
  file << "OFF" << std::endl; // off = object file format
  const size_t num_faces = _T->_triangles.size();
  const size_t num_vertices = _T->_nodes.size();
  const size_t num_edges = 3 * num_faces; // repeated, not shared
  file << num_vertices << " " << num_faces << " " << num_edges << std::endl;
  
  // vertices
  for ( size_t i = 0; i < num_vertices; ++i )
  {
    assert( _T->_nodes[i]->_id == i );
    
    Point *p = _T->_nodes[i];
    file << f*p->x << " " <<  f*p->y << " " <<  f*p->z << "\n";
  }
  
  // faces
  for ( size_t i = 0; i < num_faces; ++i )
  {
    
    Triangle *t = _T->_triangles[i];
    assert( t->_nodes.size() == 3 );
    
    file << "3 ";
    for ( size_t j = 0; j < 3; ++j )
    {
      file << t->_nodes[j]->_id << " ";
    }
    file << "\n";
  }
  
  std::cout << " done." << std::endl;
}



void TriangulationTool::write_ply( std::string fname, const double f )
{
  std::cout << "Writing triangulation to polygon file (.ply) " << fname << "... ";
  std::cout.flush();
  
  size_t num_vertices = _T->_nodes.size();
  size_t num_faces = _T->_triangles.size();
  std::cout << num_vertices << " vertices and " << num_faces << " triangles.";
  std::cout.flush();
  
  // open file
  // erases any old data
  std::fstream file(fname.c_str(), std::ios::out);
  
  // header
  file << "ply\n";
  file << "format ascii 1.0\n";
  file << "element vertex " << num_vertices << "\n";
  file << "property float x\n";
  file << "property float y\n";
  file << "property float z\n";
  file << "element face " << num_faces << "\n";
  file << "property list uchar int vertex_index\n";
  file << "end_header\n";
  
  // vertex coordinates
  // numbering starts at 0
  // vertices
  for ( size_t i = 0; i < num_vertices; ++i )
  {
    assert( _T->_nodes[i]->_id == i );
    
    Point *p = _T->_nodes[i];
    file << f*p->x << " " <<  f*p->y << " " <<  f*p->z << "\n";
  }

  // triangle faces
  for ( size_t i = 0; i < num_faces; ++i )
  {
    
    Triangle *t = _T->_triangles[i];
    assert( t->_nodes.size() == 3 );
    // assert( t->_id == i ); // not true when writing subsets of triangles
    
    file << "3 ";
    for ( size_t j = 0; j < 3; ++j )
    {
      size_t id = t->_nodes[j]->_id;
      assert( id < num_vertices );
      file << id << " ";
    }
    file << "\n";
  }
    
  file.flush();
  
  std::cout << " done." << std::endl;
}

void TriangulationTool::write_facet( std::string fname, const double f )
{
  std::cout << "Writing triangulation to cubit facet file (.facet) " << fname << "... ";
  std::cout.flush();
  
  size_t num_vertices = _T->_nodes.size();
  size_t num_faces = _T->_triangles.size();
  std::cout << num_vertices << " vertices and " << num_faces << " triangles.";
  std::cout.flush();
  
  // open file
  // erases any old data
  std::fstream file(fname.c_str(), std::ios::out);
  
  // header
  file << num_vertices << " " << num_faces << std::endl;
  
  // vertex coordinates
  // numbering starts at 0
  // vertices
  for ( size_t i = 0; i < num_vertices; ++i )
  {
    assert( _T->_nodes[i]->_id == i );
    
    Point *p = _T->_nodes[i];
    file << i << "   " << f*p->x << " " <<  f*p->y << " " <<  f*p->z << "\n";
  }
  
  // triangle faces
  for ( size_t i = 0; i < num_faces; ++i )
  {
    
    Triangle *t = _T->_triangles[i];
    assert( t->_nodes.size() == 3 );
    // assert( t->_id == i ); // not true when writing subsets of triangles
    
    assert(i == t->_id);
    file << t->_id << "   ";
    
    for ( size_t j = 0; j < 3; ++j )
    {
      size_t id = t->_nodes[j]->_id;
      assert( id < num_vertices );
      file << id << " ";
    }
    file << "\n";
  }
  
  file.flush();
  
  std::cout << " done." << std::endl;
}


//void TriangulationTool::write_exodus( std::string fname, const double nodal_scale_factor )
//{
//  std::string path = fname;
//  int mode = EX_BULK_INT64_DB;
//  const int comp_ws = 64; // computer word size
//  
//  ex_create(path.c_str(), mode, comp_ws, io_ws);
//  // ex_open(path.c_str(), mode, comp_ws, io_ws, version);
//  
//}

bool TriangulationTool::good_connectivity(double min_x, double min_y, double max_x, double max_y, std::vector<Edge> *open_edges)
{
  bool OK(true);
  // all non-boundary edges should be manifold
  // triangle faces
  std::vector<Edge> es;
  std::vector<Triangle*> tris;
  
  const int max_reports = 10;
  int num_extra_tri_bdy = 0;
  int num_extra_tri_int = 0;
  int num_lone_edges = 0;
  int num_one_tri = 0;
  
  // triangles with one edge, and the triangles surrounding each of those vertices
  std::vector<Triangle*> singletons, nbhd;
  
  for ( size_t i = 0; i < _T->_nodes.size(); ++i )
  {
    Node *n = _T->_nodes[i];
    es.clear();
    n->edges(es);
    for (size_t e = 0; e < es.size(); ++e )
    {
      bool e_OK(true);
      Edge &ed = es[e];
      tris.clear();
      ed.triangles(tris);
      bool do_print = false;

      bool is_bdy_edge =
      ( ed._n0->x == min_x && ed._n1->x == min_x ) ||
      ( ed._n0->y == min_y && ed._n1->y == min_y ) ||
      ( ed._n0->x == max_x && ed._n1->x == max_x ) ||
      ( ed._n0->y == max_y && ed._n1->y == max_y );

      if (is_bdy_edge && tris.size() > 1 )
      {
        e_OK = false;
        do_print = (++num_extra_tri_bdy < max_reports);
        if (do_print)
          std::cout << "ERROR: edge at domain boundary has more than one triangle, " << tris.size() << std::endl;
      }
      
      if (!is_bdy_edge && tris.size() > 2 )
      {
        e_OK = false;
        do_print = (++num_extra_tri_int < max_reports);
        if (do_print)
          std::cout << "ERROR: edge interior to domain has more than two triangles, non-manifold, " << tris.size() << std::endl;
      }
      
      if (tris.empty())
      {
        e_OK = false;
        do_print = ++num_lone_edges < max_reports;
        if (do_print)
          std::cout << "ERROR: edge has no triangles." << std::endl;

        if (open_edges)
          open_edges->push_back( ed );
      }
      
      if (!is_bdy_edge && tris.size() == 1)
      {
        // zzyk todo:
        // Case: input the inclusion does not extend to the domain boundaries, and the surface ends internally
        // for test input, this should not happen, but in principle it is an OK case
        e_OK = false;
        do_print = (++num_one_tri < max_reports);
        if (do_print)
        {
          std::cout << "WARNING: edge interior to domain has one triangle, which is only OK for the boundary of a surface." << std::endl;
          std::cout << "  ERROR: this is an error for our test input." << std::endl;
        }
        
        if (open_edges)
          open_edges->push_back( ed );
        
        singletons.push_back(tris[0]);
        // nbhd += ed._n0->_triangles;
        nbhd.insert(nbhd.end(), ed._n0->_triangles.begin(), ed._n0->_triangles.end());
        nbhd.insert(nbhd.end(), ed._n1->_triangles.begin(), ed._n1->_triangles.end());
      }
      
      if (!e_OK)
      {
        if (do_print)
        {
          std::cout << "Bad ";
          ed.print();
        }
        OK = false;
      }
    }
  }
  
  // summary
  if ( !OK )
  {
    
    // remove duplicates
    uniquify_vec_ptr( nbhd );
    uniquify_vec_ptr( singletons );
    if (open_edges)
      uniquify_vec_ref( *open_edges );
    
    // divide by 2 because each edge has two nodes, and is hence visited twice
    std::cout << "\nTriangulation had connectivity problems:\n";
    if ( num_extra_tri_bdy )
      std::cout << "  " << num_extra_tri_bdy / 2 << " boundary edges with more than one triangle;\n";
    if ( num_extra_tri_int )
      std::cout << "  " << num_extra_tri_int / 2 << " interior edges with more than two triangles;\n";
    if ( num_lone_edges )
      std::cout << "  " << num_lone_edges / 2 << " edges with no triangles;\n";
    if ( num_one_tri )
      std::cout << "  " << num_one_tri / 2 << " interior edges with one triangles, " << singletons.size() << " such triangles;\n";
    std::cout << std::endl;
    
    // write out triangles with a problem edge
    std::string fname = "bad_singletons_" + std::to_string( _T->_triangles.size() ) + "_" ; // common prefix
    {
      singletons.swap(_T->_triangles);
      write_ply( fname + "tris_" + std::to_string( _T->_triangles.size() ) + ".ply" );
      singletons.swap(_T->_triangles);
    }
    
    // write out neighborhoods
    {
      nbhd.swap(_T->_triangles);
      write_ply( fname + "nbhd_" + std::to_string( _T->_triangles.size() ) + ".ply" );
      nbhd.swap(_T->_triangles);
    }
  }
  else
    std::cout << "No connectivity problems." << std::endl;
    
  return OK;
}

bool TriangulationTool::triangle_node_in_box( const Box *b, const Triangle *t )
{
  return (b->contains_point( *t->_nodes[0]) || b->contains_point( *t->_nodes[1]) || b->contains_point( *t->_nodes[2]) );
}


bool TriangulationTool::triangle_edge_cross_box_face( const Box *b, const Triangle *t )
{
  Point *n0 = t->_nodes[2];
  for ( int j = 0; j < 3; ++j )
  {
    Point *n1 = t->_nodes[j];
    
    double t;
    Point p;
    
    // find where line of edge crosses the plane of the box face
    
    // +z and -z faces
    t = (b->corner_max().z - n0->z) / ( n1->z - n0->z);
    if ( t >= 0. && t <= 1.)
    {
      p = *n0 + (*n1 - *n0) * t;
      if ( p.x <= b->corner_max().x && p.x >= b->corner_min().x && p.y <= b->corner_max().y && p.y >= b->corner_min().y )
        return true;
    }
    t = (b->corner_min().z - n0->z) / ( n1->z - n0->z);
    if ( t >= 0. && t <= 1.)
    {
      p = *n0 + (*n1 - *n0) * t;
      if ( p.x <= b->corner_max().x && p.x >= b->corner_min().x && p.y <= b->corner_max().y && p.y >= b->corner_min().y )
        return true;
    }
    
    // +y and -y faces
    t = (b->corner_max().y - n0->y) / ( n1->y - n0->y);
    if ( t >= 0. && t <= 1.)
    {
      p = *n0 + (*n1 - *n0) * t;
      if ( p.x <= b->corner_max().x && p.x >= b->corner_min().x && p.z <= b->corner_max().z && p.z >= b->corner_min().z )
        return true;
    }
    t = (b->corner_min().y - n0->y) / ( n1->y - n0->y);
    if ( t >= 0. && t <= 1.)
    {
      p = *n0 + (*n1 - *n0) * t;
      if ( p.x <= b->corner_max().x && p.x >= b->corner_min().x && p.z <= b->corner_max().z && p.z >= b->corner_min().z )
        return true;
    }
    
    // +x and -x faces
    t = (b->corner_max().x - n0->x) / ( n1->x - n0->x);
    if ( t >= 0. && t <= 1.)
    {
      p = *n0 + (*n1 - *n0) * t;
      if ( p.y <= b->corner_max().y && p.y >= b->corner_min().y && p.z <= b->corner_max().z && p.z >= b->corner_min().z )
        return true;
    }
    t = (b->corner_min().x - n0->x) / ( n1->x - n0->x);
    if ( t >= 0. && t <= 1.)
    {
      p = *n0 + (*n1 - *n0) * t;
      if ( p.y <= b->corner_max().y && p.y >= b->corner_min().y && p.z <= b->corner_max().z && p.z >= b->corner_min().z )
        return true;
    }
    
    n0 = n1;
  }
  return false;
}

// if the box has a non-empty intersection with a triangle, then return true and one such triangle
bool TriangulationTool::box_intersects_triangle( const Box *b, Triangle *&t  )
{
  // cases:
  // triangle is inside box
  // triangle edge pierces a box face
  // box edge pierces the triangle
  
  // box contains a node?
  for (int i = 0; i < _T->_nodes.size(); ++i)
  {
    Node *n = _T->_nodes[i];
    if (b->contains_point(*n))
    {
      t = n->_triangles.front();
      return true;
    }
  }
  
  // triangle edge pierces box face?
  for (int i = 0; i < _T->_triangles.size(); ++i)
  {
    Triangle *t = _T->_triangles[i];
    if (triangle_edge_cross_box_face(b,t))
      return true;
  }
  
  // box edge pierces triangle face
  // this will only occur if box is tiny compared to the triangle, so skip checking this case
  
  return false;
}



