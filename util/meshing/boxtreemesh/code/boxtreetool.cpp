//
//  boxtreetool.cpp
//  BoxTreeMesh
//
//  Created by Mitchell, Scott A on 2/8/16.
//  Copyright (c) 2016 Sandia National Labs. All rights reserved.
//

#include "boxtreetool.h"

#include <fstream>
#include <cstdio>
#include <iomanip>

size_t BoxTreeTool::discard_hexes( int f, double domain_fraction )
{
  size_t num_discarded(0);
  const double dx = domain_fraction * *Box::changed_coordinate(f, _bt->get_domain().diagonal());
  const double x_min = dx + *Box::changed_coordinate(f, _bt->get_domain().corner_min());

  std::cout << "\nDiscarding hexes with coordinate > " << x_min << " out of " << *Box::changed_coordinate(f, _bt->get_domain().diagonal()) << std::endl;
  
  double *new_bdy = Box::changed_coordinate( f, _bt->_clipped_boundary );
  *new_bdy = 0.;
  
  BTIOutput bti( _bt );
  for ( BoxTreeNode *b = bti.get(); b != 0; b = bti.next() )
  {
    double bx = *b->changed_coordinate(f);
    if ( bx > x_min )
    {
      b->output_hex(false);
      b->discarded(true);
      ++num_discarded;
    }
    else
    {
      if (bx > *new_bdy)
        *new_bdy = bx;
    }
  }
  assign_global_ids(true);

  std::cout << "discarded " << num_discarded << " hexes, and " << _bt->get_number_hexes() << " remain.\n" << std::endl;
  
  return num_discarded;
}


void BoxTreeTool::corners_or_nodes( BoxTreeNode *b, Point *nodes )
{
  if (_write_corner_coords)
    // box corners, aligned with grid axes
    b->corners(nodes);
  else
    // warped coordinates
    b->nodes(nodes);
}


void BoxTreeTool::assign_global_ids(bool clean_ids)
{
  unsigned int id(0), idh(0);
  
  if (clean_ids)
  {
    BTIAll bti( _bt );
    for ( BoxTreeNode *b = bti.get(); b != 0; b = bti.next() )
    {
      assert( id  < std::numeric_limits< unsigned int >::max() );
      assert( idh < std::numeric_limits< unsigned int >::max() );
      if (b->is_leaf())
      {
        if ( b->output_hex() )
          b->set_id( idh++ );
        else
          b->set_id();
        
        id++;
      }
      else
      {
        b->output_hex(false);
        b->set_id();
      }
    }
  }
  else
  {
    BTILeaf bti( _bt );
    for ( BoxTreeNode *b = bti.get(); b != 0; b = bti.next() )
    {
      assert( id  < std::numeric_limits< unsigned int >::max() );
      assert( idh < std::numeric_limits< unsigned int >::max() );
      if ( b->output_hex() )
        b->set_id( idh++ );
      id++;
    }
  }
  _bt->set_number_leaves( id );
  _bt->set_number_hexes( idh );
}

void BoxTreeTool::write_boundary_conditions( std::string fname )
{
  std::cout << "Writing dgm boundary conditions (.bc) to " << fname << "...";
  std::cout.flush();
  
  // assign ids if not already done
  if (_bt->get_number_leaves() == 0)
    assign_global_ids();
  assert( _bt->get_number_leaves() > 0 );
  
  // gather the bc in vectors, one vector for each of the six face directions
  std::vector< std::vector<size_t> > bc(6);
  
  for (int f = 0; f<6; ++f)
  {
    // get all the leaves with a face on the domain boundary
    std::vector<BoxTreeNode*> fc;
    
    // using the tree topology only works if we haven't discarded any hexes
    // get all the face leaves of the root
    const double clipped_bdy = *Box::changed_coordinate(f,_bt->_clipped_boundary);
    const double domain_bdy = *Box::changed_coordinate(f,_bt->get_domain().corner_max());
    if ( Box::is_lower_face(f) || clipped_bdy == domain_bdy )
      _bt->root->face_leaf_children(f, fc);
    else
    {
      Box query_box( _bt->get_domain() );
      assert( !Box::is_lower_face(f) );
      *query_box.changed_coordinate(f) = clipped_bdy -    coordinate_DELTA;
      *query_box.changed_coordinate(Box::opposite_face(f)) = clipped_bdy - 2.*coordinate_DELTA;
      _bt->root->find_leaf_child_overlap(fc, query_box);
    }
    
    // keep the boxes that have an output hex
    bc[f].reserve(fc.size());
    for (size_t i = 0; i < fc.size(); ++i)
    {
      BoxTreeNode *b = fc[i];
      if (b->output_hex())
        bc[f].push_back(b->get_id());
    }
  }
  size_t nbc = bc[0].size() + bc[1].size() + bc[2].size() + bc[3].size() + bc[4].size() + bc[5].size();
  
  // write to file
  {
    // open file - erases any old data
    std::fstream file(fname.c_str(), std::ios::out);
    
    // header comment line
    file << "** Boundary Conditions **\n";
    
    // header
    // # number boundary conditions bc
    file << nbc << " nbc\n";
    
    // F Free type
    // face 0 bc, min-z of domain,
    // F h 0
    size_t f = 0;
    for (size_t i = 0; i < bc[f].size(); ++i)
    {
      file << "F " << bc[f][i] << " 0\n";
    }
    // Z abZorbing type
    // face 1..5, sides and max-z of domain,
    for (size_t f = 1; f < 6; f++)
    {
      for (size_t i = 0; i < bc[f].size(); ++i)
      {
        file << "Z " << bc[f][i] << " " << f << "\n";
      }
    }
    file.flush();
  }
  
  // debug in cubit
  if (/* DISABLES CODE */ (1))
  {
    std::string fname_debug = fname + "_debug";
    std::cout << "Writing dgm boundary conditions (.bc) to " << fname_debug << "...";
    
    // write to file
    // open file - erases any old data
    std::fstream file_debug(fname_debug.c_str(), std::ios::out);
    
    // header comment line
    file_debug << "** Boundary Conditions **\n";
    
    // header
    // # number bc
    file_debug << nbc << " nbc\n";
    
    for (size_t f = 0; f < 6; ++f )
    {
      file_debug << "cubit hexes (numbered from 1) with boundary face " << f << ", " << bc[f].size() << " of them:\n";
      for (size_t i = 0; i < bc[f].size(); ++i)
      {
        file_debug << " " << bc[f][i] + 1;
      }
      file_debug << "\n";
    }
    file_debug.flush();
  }
  
  std::cout << " done." << std::endl;

}

// not needed?
// faster assignment of neighbors, by saving adjacent cousins in a single pass
// profile time to test all face adjacencies

// binary file output?
// Binary is tricky.  You could look at the hex_mesh.cpp source to see how to create the header and how the data is written.  The values for HEX are in Topology.hpp.

void BoxTreeTool::write_face_adjacencies( std::string fname )
{
  std::cout << "Writing dgm hex face adjacencies (.con) to " << fname << "...";
  std::cout.flush();

  // assign ids if not already done
  if (_bt->get_number_leaves() == 0)
    assign_global_ids();
  assert( _bt->get_number_leaves() > 0 );
  
  // open file
  // erases any old data
  std::fstream file(fname.c_str(), std::ios::out);
 
  // header comment line
  file << "# CONNECTIVITY DATA - boxtree mesh -  \"E w x y z\" means hex w face x touches hex y face z" << std::endl;
  
  // header # elements, ne = nodal element?
  file << _bt->get_number_hexes() << " ne" << std::endl;
  
  // vector of face neighbors
  std::vector<BoxTreeNode*> nbh;

  BTIOutput bti( _bt );
  for ( BoxTreeNode *b = bti.get(); b != 0; b = bti.next() )
  {
    long id = b->get_id();
    
    // iterate over neighbors
    for ( int f = 0; f < 6; ++f )
    {
      const int ff = Box::opposite_face(f);
      nbh.clear();
      b->find_mesh_neighbors(f, nbh);
      // if nbh.empty, then double-check that we are indeed on the domain boundary
      if (nbh.empty())
      {
        Point c = b->face_center(f);
        double box_coordinate = *Box::changed_coordinate(f, c);
        Box domain = _bt->get_domain();
        double domain_coordinate = *Box::changed_coordinate(f, (Box::is_lower_face(f) ? domain.corner_min() : domain.corner_max()) );
        if ( fabs( box_coordinate - domain_coordinate ) > 1.0e-8 * *Box::changed_coordinate(f, domain.diagonal()) )
        {
          std::cerr << "ERROR: hex has no face-neighbor box, but that face is not on the domain boundary\n";
          std::cerr << "Face " << f << std::endl;
          b->print();
        }
      }
      else
      {
        bool has_hex_neighbor(false), has_tet_neighbor(false), has_discarded_neighbor(false);
        BoxTreeNode *nb(0);
        for (size_t n = 0; n < nbh.size(); ++n)
        {
          nb = nbh[n];
          if (nb->output_hex())
          {
            has_hex_neighbor = true;
            //file << "(" << id << "," << f << ")  (" << nbh[n]->get_id() << "," << ff << ")" << std::endl;
            // "E w x y z" means hex w face x touches hex y face z
            file << "E " << id << " " << f << " " << nbh[n]->get_id() << " " << ff << "\n"; // std::endl;
          }
          else if (nb->tet_box() )
          {
            has_tet_neighbor = true;
          }
          if (nb->discarded())
          {
            has_discarded_neighbor = true;
          }
        }
        if (!has_hex_neighbor && !has_tet_neighbor && !has_discarded_neighbor)
        {
          std::cerr << "ERROR: hex has no face-neighbor hex or tet, for a face that is not on the (clipped) domain boundary.\n";
          std::cerr << "Face " << f << std::endl << "Hex-box ";
          b->print();
          std::cerr << "Last neighbor box " ;
          nb->print();
          std::cerr <<std::endl;        
        }
      }
    }
  }
  file.flush();
  
  std::cout << " done." << std::endl;
}

void BoxTreeTool::write_nodal_coordinates( std::string fname, const double f )
{
  std::cout << "Writing dgm hex nodal coordinates (.msh) to " << fname << "...";
  std::cout.flush();
  

  // assign ids if not already done
  if (_bt->get_number_leaves() == 0)
    assign_global_ids();
  assert( _bt->get_number_leaves() > 0 );

  // open file
  // erases any old data
  std::fstream file(fname.c_str(), std::ios::out);
  
  // header comment line
  file << "# MESH DATA coordinates - boxtree mesh - rows are x,y,z coordinates" << std::endl;
  
  // header # elements, ne = nodal element?, nsd = number spatial dimensions?
  file << _bt->get_number_hexes() << " " << 3 << " NE NSD" << std::endl;
  
  // make pretty columns?
  if (/* DISABLES CODE */ (0))
  {
    // use fixed width for human readability, otherwise skip to write fewer characters
    file << std::fixed;

    // precision for numbers. default is 7 digits
    file.precision(16);
  }
  
  
  // fixed field width for readability
  // file.setf(ios::fixed);
  // file.setf(ios::showpoint);

  Point n[8];
  
  BTIOutput bti( _bt );
  for ( BoxTreeNode *b = bti.get(); b != 0; b = bti.next() )
  {
    // debug
    assert(b->is_leaf());
    assert(b->output_hex());
    
    if (/* DISABLES CODE */ (0))
    {
      long id = b->get_id();
      std::cout << "hex " << id << std::endl;
      file << "<hex " << id << "> ";
    }
  
    // element n type
    file << "ELEMENT " << b->get_id() << "  HEX\n";

    corners_or_nodes(b, n);
    
    // x, y, z coordinates, corners 0..7
    file << " " << f*n[0].x << " " << f*n[1].x << " " << f*n[2].x << " " << f*n[3].x << " " << f*n[4].x << " " << f*n[5].x << " " << f*n[6].x << " " << f*n[7].x << "\n";
    file << " " << f*n[0].y << " " << f*n[1].y << " " << f*n[2].y << " " << f*n[3].y << " " << f*n[4].y << " " << f*n[5].y << " " << f*n[6].y << " " << f*n[7].y << "\n";
    file << " " << f*n[0].z << " " << f*n[1].z << " " << f*n[2].z << " " << f*n[3].z << " " << f*n[4].z << " " << f*n[5].z << " " << f*n[6].z << " " << f*n[7].z << "\n";
  }
  file.flush();
  
  std::cout << " done." << std::endl;
}

void BoxTreeTool::write_off_file( std::string fname, const double f )
{
  std::cout << "Writing mesh to Object File Format (.off) file " << fname << "...";
  std::cout.flush();
  

  // assign ids if not already done
  if (_bt->get_number_leaves() == 0)
    assign_global_ids();
  assert( _bt->get_number_leaves() > 0 );
  
  // open file
  // erases any old data
  std::fstream file(fname.c_str(), std::ios::out);
  
  // header
  file << "OFF" << std::endl; // off = object file format
  const size_t num_hexes = _bt->get_number_hexes();
  const size_t num_vertices = 8 * num_hexes;
  const size_t num_faces = 6 * num_hexes;
  const size_t num_edges = 12 * num_hexes;
  file << num_vertices << " " << num_faces << " " << num_edges << std::endl;
  
  // vertices
  size_t num_vertices_written(0);
  BTIOutput bti( _bt );
  Point nodes[8];
  for ( BoxTreeNode *b = bti.get(); b != 0; b = bti.next() )
  {
    // debug
    assert(b->is_leaf());
    assert(b->output_hex());
    
    corners_or_nodes(b, nodes);

    for (size_t n = 0; n < 8; ++n)
      file << f*nodes[n].x << " " <<  f*nodes[n].y << " " <<  f*nodes[n].z << "\n";
    num_vertices_written+=8;
  }
  assert( num_vertices_written == num_vertices );
  
  // faces
  for ( size_t i = 0; i < num_hexes; ++i )
  {
    size_t offset = i*8;
    for ( size_t f = 0; f < 6; ++f )
    {
      file << "4 ";
      for (size_t n = 0; n < 4; ++n )
        file << WarpedFace::face_i_lookup[f][n] + offset << " ";
      file << "\n";
    }
  }
  
  std::cout << " done." << std::endl;
}


void BoxTreeTool::write_box_facet( std::string fname, const double f )
{
  std::cout << "Writing box faces to cubit facet file (.facet) " << fname << "... ";
  std::cout.flush();
  
  // assign ids if not already done
  size_t num_hexes = _bt->get_number_hexes();
  if (num_hexes == 0)
  {
    assign_global_ids();
    num_hexes = _bt->get_number_hexes();
  }
  assert( num_hexes > 0 );
  
  size_t num_vertices = num_hexes * 8;
  size_t num_faces = num_hexes * 6;
  
  // open file
  // erases any old data
  std::fstream file(fname.c_str(), std::ios::out);
  
  // header
  file << num_vertices << " " << num_faces << std::endl;
  
  BTIOutput bti( _bt );
  Point nodes[8];
  size_t i(0);
  for ( BoxTreeNode *b = bti.get(); b != 0; b = bti.next() )
  {
    // debug
    assert(b->is_leaf());
    assert(b->output_hex());
    
    corners_or_nodes(b, nodes);
    for (size_t n = 0; n < 8; ++n)
    {
      file << i++ << "   " << f*nodes[n].x << " " <<  f*nodes[n].y << " " <<  f*nodes[n].z << "\n";
    }
  }
  
  // faces of hexes
  size_t fid(0);
  for ( size_t h = 0; h < num_hexes; ++h )
  {
    size_t v0 = h * 8;
    size_t v1 = h * 8 + 1;
    size_t v2 = h * 8 + 2;
    size_t v3 = h * 8 + 3;
    size_t v4 = h * 8 + 4;
    size_t v5 = h * 8 + 5;
    size_t v6 = h * 8 + 6;
    size_t v7 = h * 8 + 7;
    
    //    0 1 2 3
    //    7 6 5 4
    //    0 4 5 1
    //    1 5 6 2
    //    2 6 7 3
    //    3 7 4 0
    
    file << fid++ << "   " << v0 << " " << v1 << " " << v2 << " " << v3 << "\n";
    file << fid++ << "   " << v7 << " " << v6 << " " << v5 << " " << v4 << "\n";
    file << fid++ << "   " << v0 << " " << v4 << " " << v5 << " " << v1 << "\n";
    file << fid++ << "   " << v1 << " " << v5 << " " << v6 << " " << v2 << "\n";
    file << fid++ << "   " << v2 << " " << v6 << " " << v7 << " " << v3 << "\n";
    file << fid++ << "   " << v3 << " " << v7 << " " << v4 << " " << v0 << "\n";
  }
  
  file.flush();
  
  std::cout << " done." << std::endl;
}


void BoxTreeTool::write_ply( std::string fname, const double f )
{
  std::cout << "Writing mesh to polygon file (.ply) " << fname << "...";
  std::cout.flush();
  
  // assign ids if not already done
  size_t num_hexes = _bt->get_number_hexes();
  if (num_hexes == 0)
  {
    assign_global_ids();
    num_hexes = _bt->get_number_hexes();
  }
  assert( num_hexes > 0 );
  
  size_t num_vertices = num_hexes * 8;
  size_t num_faces = num_hexes * 6;
  
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
  BTIOutput bti( _bt );
  Point nodes[8];
  for ( BoxTreeNode *b = bti.get(); b != 0; b = bti.next() )
  {
    // debug
    assert(b->is_leaf());
    assert(b->output_hex());
    
    corners_or_nodes(b, nodes);
    for (size_t n = 0; n < 8; ++n)
    {
      file << f*nodes[n].x << " " <<  f*nodes[n].y << " " <<  f*nodes[n].z << "\n";
    }
  }

  // faces of hexes
  for ( size_t h = 0; h < num_hexes; ++h )
  {
    size_t v0 = h * 8;
    size_t v1 = h * 8 + 1;
    size_t v2 = h * 8 + 2;
    size_t v3 = h * 8 + 3;
    size_t v4 = h * 8 + 4;
    size_t v5 = h * 8 + 5;
    size_t v6 = h * 8 + 6;
    size_t v7 = h * 8 + 7;

    //    4 0 1 2 3
    //    4 7 6 5 4
    //    4 0 4 5 1
    //    4 1 5 6 2
    //    4 2 6 7 3
    //    4 3 7 4 0
    
    file << "4 " << v0 << " " << v1 << " " << v2 << " " << v3 << "\n";
    file << "4 " << v7 << " " << v6 << " " << v5 << " " << v4 << "\n";
    file << "4 " << v0 << " " << v4 << " " << v5 << " " << v1 << "\n";
    file << "4 " << v1 << " " << v5 << " " << v6 << " " << v2 << "\n";
    file << "4 " << v2 << " " << v6 << " " << v7 << " " << v3 << "\n";
    file << "4 " << v3 << " " << v7 << " " << v4 << " " << v0 << "\n";
  }

  file.flush();
  
  std::cout << " done." << std::endl;
}

void BoxTreeTool::write_cubit_mesh_jou( std::string fname, const double f )
{
  std::cout << "Writing mesh construction script to cubit journal file (.jou) " << fname << "...";
  std::cout.flush();
  

  // assign ids if not already done
  if (_bt->get_number_leaves() == 0)
    assign_global_ids();
  assert( _bt->get_number_leaves() > 0 );
  
  // open file
  // erases any old data
  std::fstream file(fname.c_str(), std::ios::out);
 
  // header
  file << "# play cubit journal file to create mesh of disconnected hexes\n";
  file << "echo off\n" << "journal off\n" << "color background grey\ngraphics pause\n";

  const size_t num_hexes = _bt->get_number_hexes();
  if (num_hexes==0)
    file << "# empty mesh, no hexes!\n";
  else
  {
    // nodes
    // numbering starts at 1
    BTIOutput bti( _bt );
    Point nodes[8];
    for ( BoxTreeNode *b = bti.get(); b != 0; b = bti.next() )
    {
      // debug
      assert(b->is_leaf());
      assert(b->output_hex());
      
      corners_or_nodes(b, nodes);
      for (size_t n = 0; n < 8; ++n)
      {
        file << "create node " << f*nodes[n].x << " " <<  f*nodes[n].y << " " <<  f*nodes[n].z << "\n";
      }
    }
    const size_t num_nodes = 8 * num_hexes;
    
    // aprepro define starting id of the newly created nodes
    file << "#{node1=Id(\"node\")} {node0=node1-" << num_nodes-1 << "}\n";
    file << "group 'meshnodes' equals node {node0} to {node1}\n";
    
    // hexes
    file << "#{numhexes=" << num_hexes << "}\n";
    file << "#{_i=0}\n";
    file << "#{loop("<< num_hexes << ")}\n";
    file << "#{_hex0=Id(\"hex\")}\n";
    file << "#{_offset=node0+_i*8}\n";
    file << "create hex node {_offset} to {_offset+7}\n";
    
    // debug if failed to create hex
    file << "#{_hex1=Id(\"hex\")}\n#{If(_hex0==_hex1)}\n#{_numfails++}\n#{_failedhex=_hex1+_numfails}\necho on\nComment \"Failed to create hex \" {_failedhex} \". numfails=\" {_numfails}\n# create an error\nlist hex {_failedhex}\necho off\n#{EndIf}\n";
    file << "#{++_i}\n";
    
    
    file << "#{endloop}\n";
//    for ( size_t i = 0; i < num_hexes; ++i )
//    {
//      size_t offset = 1 + i*8;
//      file << "create hex node " << offset << " to " << offset + 7 << "\n";
//    }
    file << "#{hex1=Id(\"hex\")} {hex0=hex1-num_hexes-1}\n";
    file << "group 'meshhexes' equals hex {hex0} to {hex1}\n";
  }
  
  file << "zoom reset\ndisplay\necho on\njournal on" << std::endl;
  
  std::cout << " done." << std::endl;
}


std::string BoxTreeTool::write_box_face( const Box &box, int face, size_t id, std::string fname, const double f )
{
  fname += "_b" + std::to_string(id) + "_f" + std::to_string(face) + ".facet";
  {
    std::cout << "Writing box face to cubit facet file (.facet) " << fname << "... ";
    std::cout.flush();
    
    size_t num_vertices = 4;
    size_t num_faces = 1;
    std::cout << num_vertices << " vertices and " << num_faces << " quad.";
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
    box.face_nodes(face, nodes);
    for ( size_t i = 0; i < 4; ++i )
    {
      Point &p = nodes[i];
      file << i << "   " << f*p.x << " " <<  f*p.y << " " <<  f*p.z << "\n";
    }
    
    // quad connectivity
    file << "0   0 1 2 3\n";
    
    file.flush();
    
    std::cout << " done." << std::endl;
  }
  return fname;
}


void BoxTreeTool::write_box_zones( std::string fname_prefix )
{
  // open files
  // overwrites
  std::string fname_acoustic = fname_prefix + "_acoustic_hex.txt";
  std::ofstream facoustic(fname_acoustic, std::ios::out );
  if (!facoustic.is_open())
  {
    std::cout << " ERROR" << std::endl;
    std::cerr << "Error opening " << fname_acoustic << std::endl;
    return;
  }
  std::string fname_elastic = fname_prefix + "_elastic_hex.txt";
  std::ofstream felastic(fname_elastic, std::ios::out );
  if (!felastic.is_open())
  {
    std::cout << " ERROR" << std::endl;
    std::cerr << "Error opening " << fname_elastic << std::endl;
    return;
  }
  std::string fname_inclusion = fname_prefix + "_inclusion_hex.txt";
  std::ofstream finclusion(fname_inclusion, std::ios::out );
  if (!felastic.is_open())
  {
    std::cout << " ERROR" << std::endl;
    std::cerr << "Error opening " << fname_inclusion << std::endl;
    return;
  }
  
  // write to one of two files
  bool print_once = true;
  BTIOutput bti( _bt );
  for ( BoxTreeNode *b = bti.get(); b != 0; b = bti.next() )
  {
    switch (b->get_zone())
    {
      case BoxTreeNode::INCLUSION:
        finclusion << b->get_id() << "\n";
        break;
      case BoxTreeNode::ELASTIC:
        felastic << b->get_id() << "\n";
        break;
      case BoxTreeNode::ACOUSTIC:
        facoustic << b->get_id() << "\n";
        break;
      case BoxTreeNode::UNSET:
      default:
        // no output
        if (print_once)
        {
          std::cout << "Warning: box zone is unset. It should be one of {acoustic, elastic, inclusion}." << std::endl;
          print_once = false;
        }
        break;
    }
  }
  // close files
}


void BoxTreeTool::print_sub_box_type( SubBoxType sub_box_type, std::ostream &o )
{
  switch (sub_box_type)
  {
    case BOX:
      o << "BOX";
      break;
    case FACE:
      o << "FACE";
      break;
    case EDGE:
      o << "EDGE";
      break;
    case NODE:
      o << "NODE";
      break;
    default:
      o << "DEFAULT";
      break;
  }
}




bool Refiner::refine_implementation(bool actually_refine)
{
  if (! refine_parameters_ok())
  {
    std::cout << "WARNING: refinement parameters are not provably safe!\n" << std::endl;
//    std::cerr << "WARNING: refinement parameters are not OK!\n" << std::endl;
    // go ahead and refine anyway
  }
  bool was_refined = false;
  
  // enqueu current leaves
  std::vector<BoxTreeNode *> q;
  BTILeaf bti(_boxt);
  for ( BoxTreeNode *b = bti.get(); b != 0; b = bti.next() )
    q.push_back(b);

  while (!q.empty())
  {
    // LIFO q, not sure queue order it makes a difference
    // could use dequeue
    BoxTreeNode *b = q.back();
    q.pop_back();
    assert(b);
    assert( b->is_leaf() );
    
    // checks here
    // check box size and height variation
    const bool should_refine = refine_condition(b);
    
    // refine and enque children
    if (should_refine)
    {
      if (!actually_refine)
        return true;
      
      was_refined = true;
      b->create_children(child_size);
      b->get_children(q);
    }
  }
  
  return was_refined;
}




bool Balancer::balance_all_neighbors( BoxTreeNode *b, std::vector<BoxTreeNode*> &q, bool skip_node_neighbors)
{
  // these are really parameters, hard-coded for now
  const int side_length_factor = 2.;
  
  bool split_some = false;
  
  const double sf = side_length_factor + 0.5;
  const double mx = sf * b->diagonal_x();
  const double my = sf * b->diagonal_y();
  const double mz = sf * b->diagonal_z();
  
  // get neighbors by geometry,
  // since we are just looking for bigger boxes, and we will check if they are leaves,
  // stop the search when we get to to one less level (bigger diagonal) than b
  std::vector<BoxTreeNode*> nbr;
  b->find_connected_boxes(nbr, skip_node_neighbors, b->get_level() - 1);
  for (size_t i = 0; i < nbr.size(); ++i)
  {
    BoxTreeNode *n = nbr[i];
    
    // check size vs b
    // for now, we check all the diagonals.
    // not sure what else would make sense for node-connected neighbors...
    if ( n->is_leaf() && (n->diagonal_x() > mx || n->diagonal_y() > my || n->diagonal_z() > mz ) )
    {
      q.push_back(n);
      split_some = true;
    }
  }
  return split_some;
}

bool Balancer::balance_neighbors( BoxTreeNode *b, std::vector<BoxTreeNode*> &q, bool actually_change )
{
  bool changed = false;
  size_t old_q_size = q.size();

  if ( balance_condition( b, q ) )
  {
    if (!actually_change)
      return true;

    changed = true;
    for (size_t i = old_q_size; i < q.size(); ++i )
    {
      q[i]->create_children(child_size);
    }
  }
  return changed;
}

bool Balancer::balance_implementation(bool actually_change)
{
  // visit all leaves
  // split all neighbors of a leaf that are too big compared to it.
  // Add those split neighbors to the queue, as they may require their neighbors to be split.

  // for more complicated balance conditions, or when it started strongly unbalanced,
  // we may need to iterate over all boxes several times
  
  // queue of boxes to revisit
  std::vector<BoxTreeNode*> q;
  
  // conceptually:
  //        for (size_t f = 0; f < 6; ++f)
  //        {
  //          BoxTreeNode *n = b->get_neighbor(f);
  //          if (n->diagonal() > side_length_factor * b->diagonal)
  //            n->split
  //        }
  
  bool changed_this_pass = false;
  bool changed_ever = false;
  
  do
  {
    changed_this_pass = false;

    // debug timing
//    size_t num_leaves = 0;
//    {
//      BTILeaf bti( _bt );
//      for ( BoxTreeNode *b = bti.get(); b != 0; b = bti.next() )
//      {
//        ++num_leaves;
//      }
//      std::cout << "num_leaves to balance = " << num_leaves << std::endl;
//    }
//    size_t report_period = (num_leaves / 100) + 1;
//    

    // check all leaves
//    size_t i = 0;
    BTILeaf bti( _bt );
    for ( BoxTreeNode *b = bti.get(); b != 0; b = bti.next() )
    {

      // debug
//      ++i;
//      if (i % report_period == 0)
//      {
//        std::cout << i << " ";
//        std::cout.flush();
//      }
      
      if (b->get_level() > boxtree_BIGLEVEL)
        std::cout << "Warning: fathoming balance condition for box at level " << b->get_level() << std::endl;
      else
        if ( balance_neighbors( b, q, actually_change ) )
        {
          changed_this_pass = true;
          changed_ever = true;
          if (!actually_change)
            return true;
        }
    }
    // repeatedly check all leaf children of boxes that were split
    std::vector<BoxTreeNode*> q2;
    while (!q.empty())
    {
      assert(actually_change);
      assert(changed_this_pass);
      assert(changed_ever);
      
      // for all boxes that were split in the last pass
      std::vector<BoxTreeNode*>::iterator i;
      for ( i = q.begin(); i != q.end(); ++i )
      {
        // for all their children
        BTILeaf qli( *i );
        BoxTreeNode *b;
        while ( ( b = qli.get() ) ) // assignment to b
        {
          assert(b);
          assert(b->is_leaf());
          
          // check balance condition, unless we've refined too deep
          if (b->get_level() > boxtree_BIGLEVEL)
            std::cout << "Warning: fathoming balance condition for box at level " << b->get_level() << std::endl;
          else
            balance_neighbors( b, q2, actually_change );
          
          qli.next();
        }
      }
      // forget the boxes we balanced, and check the new split boxes
      q.clear();
      q.swap(q2);
    }
  } while (changed_this_pass);
  
  return changed_ever;
}





bool BalancerFace::balance_condition(BoxTreeNode *b, std::vector<BoxTreeNode*> &q)
{
  bool split_some = false;

  // neighbors may be one split larger, but not two
  // unless splitting in a direction doesn't change the size, in which case we don't flag a split, and leave it unbalanced
  const double mx = (child_size.x + 0.5) * b->diagonal_x();
  const double my = (child_size.y + 0.5) * b->diagonal_y();
  const double mz = (child_size.z + 0.5) * b->diagonal_z();
  
  BoxTreeNode *n;

  // x
  // check y z sizes only, not x directions
  n = b->get_neighbor_xp();
  if ( n && n->is_leaf() && ((n->diagonal_y() > my && child_size.y > 1) || (n->diagonal_z() > mz && child_size.z > 1)) )
  {
    q.push_back(n); split_some = true;
  }
  n = b->get_neighbor_xm();
  if ( n && n->is_leaf() && ((n->diagonal_y() > my && child_size.y > 1) || (n->diagonal_z() > mz && child_size.z > 1)) )
  {
    q.push_back(n); split_some = true;
  }
  
  // y
  // check x z sizes only, not y directions
  n = b->get_neighbor_yp();
  if ( n && n->is_leaf() && ((n->diagonal_x() > mx && child_size.x > 1) || (n->diagonal_z() > mz && child_size.z > 1)) )
  {
    q.push_back(n); split_some = true;
  }
  n = b->get_neighbor_ym();
  if ( n && n->is_leaf() && ((n->diagonal_x() > mx && child_size.x > 1) || (n->diagonal_z() > mz && child_size.z > 1)) )
  {
    q.push_back(n); split_some = true;
  }

  // z
  // check x y sizes only, not z directions
  n = b->get_neighbor_zp();
  if ( n && n->is_leaf() && ((n->diagonal_x() > mx && child_size.x > 1) || (n->diagonal_y() > my && child_size.y > 1)) )
  {
    q.push_back(n); split_some = true;
  }
  n = b->get_neighbor_zm();
  if ( n && n->is_leaf() && ((n->diagonal_x() > mx && child_size.x > 1) || (n->diagonal_y() > my && child_size.y > 1)) )
  {
    q.push_back(n); split_some = true;
  }
  
  return split_some;
}


