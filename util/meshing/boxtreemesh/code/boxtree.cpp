//
//  boxtree.cpp
//  boxtree
//
//  Created by Mitchell, Scott A on 1/4/16.
//  Copyright (c) 2016 Sandia National Labs. All rights reserved.
//

#include "boxtree.h"
#include "windingnumber.h"

Random Box::_random;

//                      faces       0 1 2 3 4 5
const int Box::opposite_faces[6] = {5,3,4,1,2,0};

const int WarpedFace::corner_i_lookup[6 /*face*/ ][8 /*corner*/]
= {  {0,1,2,3,-1,-1,-1,-1}, {1,0,-1,-1,2,3,-1,-1}, {-1,0,1,-1,-1,3,2,-1}, {-1,-1,0,1,-1,-1,3,2}, {0,-1,-1,1,3,-1,-1,2}, {-1,-1,-1,-1,0,1,2,3}  };

const int WarpedFace::face_i_lookup[6 /*face*/ ][4 /*id in warpedface*/]
= {  {0,1,2,3}, {1,0,4,5}, {1,2,6,5}, {2,3,7,6}, {0,3,7,4}, {4,5,6,7}  };

const bool Box::lower_face_lookup[6 /*face*/ ]
= { true, true, false, false, true, false };
//face 0    1     2      3      4     5

bool Box::test_lookups()
{
  bool OK = true;
  for (int f = 0; f < 6; ++f)
  {
    // face_i_lookup corner_i_lookup = identity
    for (size_t c = 0; c < 8; ++c )
    {
      if ( WarpedFace::corner_i_lookup[f][c] < 0 )
        continue;
      if ( WarpedFace::face_i_lookup[f][ WarpedFace::corner_i_lookup[f][c]  ] != c )
        OK = false;
      assert( WarpedFace::face_i_lookup[f][  WarpedFace::corner_i_lookup[f][c]  ] == c );
    }
    // corner_i_lookup face_i_lookup = identity
    for (size_t i = 0; i < 4; ++i )
    {
      if ( WarpedFace::corner_i_lookup[f][  WarpedFace::face_i_lookup[f][i]  ] != i )
        OK = false;
      assert( WarpedFace::corner_i_lookup[f][  WarpedFace::face_i_lookup[f][i]  ] == i );
    }
    // if face is lower then opposite face is upper
    if ( Box::is_lower_face(f) != Box::is_lower_face( Box::opposite_face(f) ) )
      OK = false;
    assert( Box::is_lower_face(f) != Box::is_lower_face( Box::opposite_face(f) ) );
    // opposite_face opposite_face = identity
    if ( Box::opposite_face( Box::opposite_face(f) ) != f )
      OK = false;
    assert ( Box::opposite_face( Box::opposite_face(f) ) == f );
  }
  return OK;
}


// ===========================
// BoxTreeNode functions
// ===========================

void BoxTreeNode::create_children( Index set_size )
{
  if (level > boxtree_BIGLEVEL)
  {
    std::cout << "WARNING: fathoming create children at level " << level << std::endl;
    return;
  }
  
  assert( !children );
  child_size = set_size;
  max_child = child_size.x * child_size.y * child_size.z;
  children = new BoxTreeNode[max_child];
  
  Point child_diagonal = diagonal() * Point( 1./child_size.x, 1./child_size.y, 1./child_size.z );

  Point child_min = corner_min();
  Point child_max = corner_min() + child_diagonal;
  
  Index ind;
  int i(0);
  for (ind.x = 0; ind.x < child_size.x; ++ind.x)
  {
    child_min.y = corner_min().y;
    child_max.y = corner_min().y + child_diagonal.y;
    for (ind.y = 0; ind.y < child_size.y; ++ind.y)
    {
      child_min.z = corner_min().z;
      child_max.z = corner_min().z + child_diagonal.z;
      for (ind.z = 0; ind.z < child_size.z; ++ind.z)
      {
        BoxTreeNode *ch = get_child(ind);
        ch->parent = this;
        assert( i == index_to_int(ind) );
        ch->birth_order = i++;
        ch->level = level + 1;
        
        ch->_corner_min = child_min;
        ch->_corner_max = child_max;
        
        
        child_min.z += child_diagonal.z;
        child_max.z += child_diagonal.z;
      } // for z
      child_min.y += child_diagonal.y;
      child_max.y += child_diagonal.y;
    } // for y
    child_min.x += child_diagonal.x;
    child_max.x += child_diagonal.x;
  } // for x
}

BoxTreeNode::~BoxTreeNode()
{
  delete [] children; // should recurse
}

// ===========================
// BoxTree functions
// ===========================


BoxTree::BoxTree() : level_limit(0), root(0), num_leaves(0), domain()
{
  root = new BoxTreeNode;
  root->level = 0;
}

void BoxTree::set_domain_size( Point set_min_corner, Point set_max_corner )
{
  // can only change the domain size if the root has not been split already
  assert( root->is_leaf() );
  
  domain = Box(set_min_corner, set_max_corner);
  
  _clipped_boundary = domain.corner_max();
  
  root->_corner_min = set_min_corner;
  root->_corner_max = set_max_corner;
}


BoxTree::~BoxTree()
{
  delete root; // should recurse
}

BoxTreeNode *BoxTreeNode::get_neighbor_xp()
{
  if (!parent)
    return 0;
  
  Index index = get_birth_index();

  // can I immediately get a sibling?
  if ( ++index.x < max_sibling_x() )
  {
    return parent->get_child(index);
  }
  
  // recurse on parent
  BoxTreeNode *aunt = parent->get_neighbor_xp();
  
  if (!aunt)
    return 0;

  if ( aunt->is_leaf() )
    return aunt;

  // get the cousin closest to me
  index.x = 0;
  
  // if aunt has same number of y and z children as my parent, then I don't need to change y and z indices
  // otherwise, if the aunt has more children, then return the aunt
  //            else the aunt has less children, we can find the one whose x-face is a superface of my x-face
  if (!scale_child_index( index.y, parent->child_size.y, aunt->child_size.y ) ||
      !scale_child_index( index.z, parent->child_size.z, aunt->child_size.z ))
    return aunt;
  
  return aunt->get_child(index);
}

bool BoxTreeNode::scale_child_index( int &child_i, int parent_child_size, int aunt_child_size )
{
  if ( aunt_child_size < parent_child_size )
  {
    // works if divides evenly, if not, we need to stop at the aunt
    const int new_i = ( child_i *   aunt_child_size ) / parent_child_size;
    const int chk_i =   child_i * ( aunt_child_size   / parent_child_size );
    if (new_i != chk_i)
      return false;
    else
    {
      child_i = new_i;
      return true;
    }
  }
  else if ( aunt_child_size > parent_child_size )
    return false;
  return true;
}


BoxTreeNode *BoxTreeNode::get_neighbor_xm()
{
  if (!parent)
    return 0;
  
  Index index = get_birth_index();
  
  // can I immediately get a sibling?
  if ( --index.x >= 0 )
  {
    return parent->get_child(index);
  }
  
  // recurse on parent
  BoxTreeNode *aunt = parent->get_neighbor_xm();
  
  if (!aunt)
    return 0;

  if ( aunt->is_leaf() )
    return aunt;
  
  // get the cousin closest to me
  index.x = aunt->child_size.x - 1;
  if (!scale_child_index( index.y, parent->child_size.y, aunt->child_size.y ) ||
      !scale_child_index( index.z, parent->child_size.z, aunt->child_size.z ))
    return aunt;

  return aunt->get_child(index);
}


BoxTreeNode *BoxTreeNode::get_neighbor_yp()
{
  if (!parent)
    return 0;
  
  Index index = get_birth_index();
  
  // can I immediately get a sibling?
  if ( ++index.y < max_sibling_y() )
  {
    return parent->get_child(index);
  }
  
  // recurse on parent
  BoxTreeNode *aunt = parent->get_neighbor_yp();
  
  if (!aunt)
    return 0;

  if ( aunt->is_leaf() )
    return aunt;
  
  // get the cousin closest to me
  index.y = 0;
  if (!scale_child_index( index.x, parent->child_size.x, aunt->child_size.x ) ||
      !scale_child_index( index.z, parent->child_size.z, aunt->child_size.z ))
    return aunt;
  
  return aunt->get_child(index);
}


BoxTreeNode *BoxTreeNode::get_neighbor_ym()
{
  if (!parent)
    return 0;
  
  Index index = get_birth_index();
  
  // can I immediately get a sibling?
  if ( --index.y >= 0 )
  {
    return parent->get_child(index);
  }
  
  // recurse on parent
  BoxTreeNode *aunt = parent->get_neighbor_ym();
  
  if (!aunt)
    return 0;

  if ( aunt->is_leaf() )
    return aunt;
  
  // get the cousin closest to me
  index.y = aunt->child_size.y -1;
  if (!scale_child_index( index.x, parent->child_size.x, aunt->child_size.x ) ||
      !scale_child_index( index.z, parent->child_size.z, aunt->child_size.z ))
    return aunt;

  return aunt->get_child(index);
}


BoxTreeNode *BoxTreeNode::get_neighbor_zp()
{
  if (!parent)
    return 0;
  
  Index index = get_birth_index();
  
  // can I immediately get a sibling?
  if ( ++index.z < max_sibling_z() )
  {
    return parent->get_child(index);
  }
  
  // recurse on parent
  BoxTreeNode *aunt = parent->get_neighbor_zp();
  
  if (!aunt)
    return 0;

  if ( aunt->is_leaf() )
    return aunt;
  
  // get the cousin closest to me
  index.z = 0;
  if (!scale_child_index( index.x, parent->child_size.x, aunt->child_size.x ) ||
      !scale_child_index( index.y, parent->child_size.y, aunt->child_size.y ))
    return aunt;

  return aunt->get_child(index);
}


BoxTreeNode *BoxTreeNode::get_neighbor_zm()
{
  if (!parent)
    return 0;
  
  Index index = get_birth_index();
  
  // can I immediately get a sibling?
  if ( --index.z >= 0 )
    return parent->get_child(index);
  
  // recurse on parent
  BoxTreeNode *aunt = parent->get_neighbor_zm();
  
  if (!aunt)
    return 0;
  
  if ( aunt->is_leaf() )
    return aunt;
  
  // get the cousin closest to me
  index.z = aunt->child_size.z - 1;
  if (!scale_child_index( index.x, parent->child_size.x, aunt->child_size.x ) ||
      !scale_child_index( index.y, parent->child_size.y, aunt->child_size.y ))
    return aunt;

  return aunt->get_child(index);
}

void BoxTreeNode::find_leaf_neighbors(std::vector<BoxTreeNode*> &neighbors)
{
  for (int f = 0; f < 6; ++f)
    find_leaf_neighbors( f, neighbors );
}

void BoxTreeNode::find_leaf_neighbors(int face, std::vector<BoxTreeNode*> &neighbors)
{
  BoxTreeNode *n = get_neighbor(face);
  if (n)
    n->face_leaf_children( opposite_face(face), neighbors );
}

void Box::face_nodes( int f, Point nodes[4] ) const
{
  assert( f>=0 );
  assert( f<6 );
  for (size_t n = 0; n < 4; ++n)
    nodes[n] = node( WarpedFace::face_i_lookup[f][n] );
}

void Box::face_corners( int f, Point nodes[4] ) const
{
  assert( f>=0 );
  assert( f<6 );
  for (size_t n = 0; n < 4; ++n)
    nodes[n] = corner( WarpedFace::face_i_lookup[f][n] );
}

Point Box::face_center( int f ) const
{
  assert( f>=0 );
  assert( f<6 );
  Point nodes[4];
  face_nodes( f, nodes );
  Point c = (nodes[0] + nodes[1] + nodes[2] + nodes[3]) * 0.25;
  return c;
}

Point Box::random_face_point( int f ) const
{
  Point nodes[4];
  face_corners( f, nodes );
  // relies on the returned nodes being in consecutive order, clockwise or counter-clockwise
  // and only works exactly right for the corners, not any warped nodes

  const double a = _random.generate_a_random_number(); // in [0,1]
  const double b = _random.generate_a_random_number(); // in [0.1]
  Point v12 = nodes[2]-nodes[1];
  Point v10 = nodes[0]-nodes[1];
  Point c = (nodes[1] + v12*a + v10*b); //zzyk check that this is computing the right thing,
  // precedence is unaffected by overloading, so it should be fine.
  return c;
}

void Box::projected_face_nodes( int f, Point nodes[4] )
{
  face_nodes( f, nodes );
  // yz
  if ( changed_coordinate(f, nodes[0] ) == &nodes[0].x )
  {
    for ( size_t n = 0; n < 4; ++n )
    {
      nodes[n].x = nodes[n].y;
      nodes[n].y = nodes[n].z;
      nodes[n].z = 0.;
    }
  }
  // xz
  else if ( changed_coordinate(f, nodes[0] ) == &nodes[0].y )
  {
    for ( size_t n = 0; n < 4; ++n )
    {
      nodes[n].y = nodes[n].z;
      nodes[n].z = 0.;
    }
  }
  // xy
  else
  {
    assert( changed_coordinate(f, nodes[0] ) == &nodes[0].z );
    for ( size_t n = 0; n < 4; ++n )
    {
      nodes[n].z = 0.;
    }
  }
}


void BoxTreeNode::find_mesh_neighbors(int face, std::vector<BoxTreeNode*> &neighbors)
{
  // check that this does not have children?
  
  // in unwarped boxes, and in the warped face itself and its opposite, the face neighbors are not affected
  if (is_warped() && _warped_face->get_f() != face && _warped_face->get_f() != opposite_face(face) )
  {
    // geometry based query
    // get superset of box faces sharing this face
    // check for inclusion through winding number test, both directions: this in neighbor, and neighbor in this.
    
    // face geometry, pushed out normal to face, and expanded a bit parallel to face
    Point q_min( corner_min() ), q_max( corner_max() );
    // expand in all directions
    q_min -= diagonal() * 0.2;
    q_max += diagonal() * 0.2;
    // push out, overwriting unwanted expansion
    if ( is_lower_face(face) )
    {
      const double xyz0 = *changed_coordinate( face, _corner_min );
      *changed_coordinate( face, q_max ) = xyz0 -      coordinate_DELTA;
      *changed_coordinate( face, q_min ) = xyz0 - 2. * coordinate_DELTA;
    }
    else
    {
      const double xyz0 = *changed_coordinate( face, _corner_max );
      *changed_coordinate( face, q_max ) = xyz0 + 2. * coordinate_DELTA;
      *changed_coordinate( face, q_min ) = xyz0 +      coordinate_DELTA;
    }
    
    Box query_box( q_min, q_max );
    
    // find candidates by geometry
    std::vector<BoxTreeNode*> candidates;
    find_boxes_overlap(candidates, query_box);
    
    // for boxes that have been squashed, replace it by a neighbor
    // note candidates size can increase during this call
    for (size_t i = 0; i < candidates.size(); ++i)
    {
      BoxTreeNode *n = candidates[i];
      if ( n->squished_hex() )
      {
        // assumption: n was squished vertically!
        // up and down neighbors were constrained to be the same size during balancing
        switch (face)
        {
          case 0:
          case 5:
          {
            BoxTreeNode *far_b = n->get_neighbor( Box::opposite_face(face) );
            // far_b won't be on the list, so there is no need to check for uniqueness
            // also, far_b is not also squished
            assert( far_b->output_hex() );
            candidates[i] = far_b;
          }
            break;
          case 1:
          case 2:
          case 3:
          case 4:
          {
            BoxTreeNode *n0 = n->get_neighbor_zm();
            BoxTreeNode *n5 = n->get_neighbor_zp();

            // add the up and down neighbors if they aren't already on the list
            if(std::find(candidates.begin(), candidates.end(), n0) != candidates.end())
              n0 = 0;
            if(std::find(candidates.begin(), candidates.end(), n5) != candidates.end())
              n5 = 0;
            // neighbors should not be squished as well
            assert( !n0 || !n0->squished_hex() );
            assert( !n5 || !n5->squished_hex() );
            if ( n0 )
            {
              candidates[i] = n0;
              if ( n5 )
                candidates.push_back(n5);
            }
            else
            {
              if (n5)
                candidates[i] = n5;
              else
              {
                candidates[i] = candidates.back();
                candidates.pop_back();
              }
            }            
          }
            break;
          default:
            break;
        }
      }
    }
    
    
    // check candidates by geometry of faces overlapping
    for (size_t i = 0; i < candidates.size(); ++i)
    {
      BoxTreeNode *n = candidates[i];
      if ( face_overlap_geometry( face, n ) )
        neighbors.push_back(n);
    }

  }
  // ordinary box-tree based query
  else
    find_leaf_neighbors(face, neighbors);
}

bool Box::face_overlap_geometry( int face, Box *g )
{
  Point fn2[4], gn2[4]; // projection to xy plane
  projected_face_nodes( face, fn2 );
  g->projected_face_nodes( opposite_face(face), gn2 );

  // centers
  Point fc = (fn2[0] + fn2[1] + fn2[2] + fn2[3]) * 0.25;
  Point gc = (gn2[0] + gn2[1] + gn2[2] + gn2[3]) * 0.25;

  // check if center is inside the other, by winding number
  WindingNumber wn;
  // bool g_in_f = wn.point_in_face(gc, fn2);
  // bool f_in_g = wn.point_in_face(fc, gn2);
  return ( wn.point_in_face(gc, fn2) || wn.point_in_face(fc, gn2) );
}

void BoxTreeNode::face_children( int face, Index &i_first, Index &i_last )
{
  i_first = Index();
  i_last = child_size;
  if (is_leaf())
    return;
  switch (face)
  {
    case 0: i_first.z = 0; i_last.z = 1; break;
    case 1: i_first.y = 0; i_last.y = 1; break;
    case 2: i_first.x = child_size.x - 1; i_last.x = child_size.x; break;
    case 3: i_first.y = child_size.y - 1; i_last.y = child_size.y; break;
    case 4: i_first.x = 0; i_last.x = 1; break;
    case 5: i_first.z = child_size.z - 1; i_last.z = child_size.z; break;
  }
}
void BoxTreeNode::face_children( int face, IntVec &kids )
{
  Index i_first, i_last;
  face_children( face, i_first, i_last );
  kids.clear();
  Index ii;
  for ( ii.x = i_first.x; ii.x < i_last.x; ++ii.x )
    for ( ii.y = i_first.y; ii.y < i_last.y; ++ii.y )
      for ( ii.z = i_first.z; ii.z < i_last.z; ++ii.z )
      {
        const int i = index_to_int(ii);
        kids.push_back(i);
      }
}

void BoxTreeNode::face_leaf_children(int face, std::vector<BoxTreeNode*> &boxes)
{
  if (is_leaf())
  {
    boxes.push_back(this);
    return;
  }
  IntVec kids;
  face_children( face, kids );
  for ( int i = 0; i < kids.size(); ++i )
  {
    BoxTreeNode *b = get_child(kids[i]);
    b->face_leaf_children( face, boxes );
  }
}


BoxTreeNode *BoxTreeNode::get_child(const IndexVec &iv) const
{
  // avoid recursion, it would be slow to keep copying parts of the index vector...
  
  BoxTreeNode *b = const_cast<BoxTreeNode*>(this);

  for (size_t l = 0; l < iv.size(); ++l)
  {
    b = b->get_child(iv[l]);
  }
  return b;
}


BoxTreeNode * BoxTreeIterator::next()
{
  if (n->is_leaf())
  {
    // if I'm the last sibling, advance to my parent's next sibling
    while ( !iv.empty() && (iv.back() + 1 == n->parent->get_max_child()) )
    {
      iv.pop_back();
      n = n->parent;
    }
    // get the next sibling, or nothing
    if (iv.empty())
    {
      n = 0;
    }
    else
    {
      n = n->parent->get_child(++iv.back());
    }
  }
  // get first child
  else
  {
    iv.push_back(0);
    n = n->get_child(0);
  }
  return n;
}


IndexVec BoxTreeIterator::get_indexv() const
{
  IndexVec indexv;
  BoxTreeNode *nn = r;
  for (int i = 0; i < iv.size(); ++i )
  {
    indexv.push_back( nn->int_to_index( iv[i] ) );
    nn = nn->get_child(i);
  }    
  return indexv;
}

Box Box::surrounding_box() const
{
  Box bb(*this);
  bb._corner_max += coordinate_DELTA;
  bb._corner_min -= coordinate_DELTA;
  return bb;
}

Box Box::dilate_box(const double scale_factor) const
{
  Box db = *this;
  db._warped_face = 0;
  db._corner_max += diagonal() * (scale_factor-1.);
  db._corner_min -= diagonal() * (scale_factor-1.);
  return  db;
}


Box Box::face_box(int face) const
{
  // copy constructor of the geometry of this box
  Box fb(*this);
  // fatten and shrink in the face direction so the box actually contains the face
  switch (face)
  {
    case 0:
      fb._corner_max.z = fb._corner_min.z + coordinate_DELTA;
      fb._corner_min.z -= coordinate_DELTA;
      break;
    case 1:
      fb._corner_max.y = fb._corner_min.y + coordinate_DELTA;
      fb._corner_min.y -= coordinate_DELTA;
      break;
    case 2:
      fb._corner_min.x = fb._corner_max.x - coordinate_DELTA;
      fb._corner_max.x += coordinate_DELTA;
      break;
    case 3:
      fb._corner_min.y = fb._corner_max.y - coordinate_DELTA;
      fb._corner_max.y += coordinate_DELTA;
      break;
    case 4:
      fb._corner_max.x = fb._corner_min.x + coordinate_DELTA;
      fb._corner_min.x -= coordinate_DELTA;
      break;
    case 5:
      fb._corner_min.z = fb._corner_max.z - coordinate_DELTA;
      fb._corner_max.z += coordinate_DELTA;
      break;
    default:
      // return the whole box I guess
      ;
  }
  return fb;
}

void BoxTreeNode::find_connected_boxes(std::vector<BoxTreeNode*> &neighbors, const bool skip_node_neighbors, const int level_limit) const
{
  const size_t first_new_neighbor = neighbors.size();
  Box bb = surrounding_box();
  find_boxes_overlap(neighbors, bb, level_limit);

  // remove corner-connected neighbors?
  if ( skip_node_neighbors )
  {
    for ( size_t i = first_new_neighbor; i < neighbors.size(); /* no ++i */ )
    {
      if ( node_connected( *neighbors[i]) )
      {
        // throw away this neighbor, replacing it with the last of the list
        neighbors[i] = neighbors.back();
        neighbors.pop_back();
      }
      else
        ++i;
    }
  }
}


BoxTreeNode *BoxTreeNode::get_neighbor_by_geometry(int face)
{
  // query_point is center of face neighbor at same level
  // maybe provide this as a separate function
  Point query_point = center();
  switch (face)
  {
    case 0:
      query_point.z -= diagonal_z();
      break;
    case 1:
      query_point.y -= diagonal_y();
      break;
    case 2:
      query_point.x += diagonal_x();
      break;
    case 3:
      query_point.y += diagonal_y();
      break;
    case 4:
      query_point.x -= diagonal_x();
      break;
    case 5:
      query_point.z += diagonal_z();
      break;
    default:
      return 0;
  }
  BoxTreeNode *b = find_box(query_point, level);
  return b;
}

void BoxTreeNode::find_leaf_neighbors_by_geometry(int face, std::vector<BoxTreeNode*> &neighbors)
{
  BoxTreeNode *n = get_neighbor_by_geometry(face);
  if (n)
    n->face_leaf_children_by_geometry( opposite_face(face), neighbors );
}

void BoxTreeNode::face_children_by_geometry( int face, IntVec &kids )
{
  Box query_box = face_box( face );
  // get_child_overlap(<#std::vector<BoxTreeNode *> &boxes#>, <#const Box &query_box#>)
  for (int c = 0; c < max_child; ++c)
  {
    if ( get_child(c)->overlaps_box(query_box) )
      kids.push_back(c);
  }
}

void BoxTreeNode::face_leaf_children_by_geometry(int face, std::vector<BoxTreeNode*> &boxes)
{
  if (is_leaf())
  {
    boxes.push_back(this);
    return;
  }
  Box query_box = face_box( face );
  find_leaf_child_overlap(boxes, query_box);
}

void BoxTreeNode::find_boxes_overlap(std::vector<BoxTreeNode*> &boxes, const Box &query_box, int level_limit) const
{
  // boxes.clear(); // don't
  // up
  // until the box contains the whole query, or we've reached the root
  const BoxTreeNode *b = this;
  while ( !b->contains_box(query_box) )
  {
    if ( b->parent )
      b = b->parent;
    else
      break; // b is root
  }
  // down
  b->find_leaf_child_overlap(boxes, query_box, level_limit);
}

// recurse down
void BoxTreeNode::find_leaf_child_overlap(std::vector<BoxTreeNode*> &boxes, const Box &query_box, int level_limit ) const
{
  // boxes.clear(); // don't
  for (int c = 0; c < max_child; ++c)
  {
    BoxTreeNode *ch = get_child(c);
    if ( ch->overlaps_box(query_box) )
    {
      if ( ch->is_leaf() || ch->level >= level_limit )
        boxes.push_back(ch);
      else
        ch->find_leaf_child_overlap(boxes, query_box, level_limit);
    }
  }
}


// immediate children
void BoxTreeNode::get_child_overlap(std::vector<BoxTreeNode*> &boxes, const Box &query_box)
{
  // boxes.clear(); // don't
  
  // todo: make a version that is optimized for the root that has *lots* of children
  
  // check each child individually
  for (int c = 0; c < max_child; ++c)
  {
    if ( get_child(c)->overlaps_box(query_box) )
      boxes.push_back(get_child(c));
  }
}


BoxTreeNode *BoxTreeNode::get_child_contains(const Box &query_box)
{
  // boxes.clear(); // don't
  
  // todo: make a version that is optimized for the root that has *lots* of children
  
  // check each child individually
  for (int c = 0; c < max_child; ++c)
  {
    if ( get_child(c)->contains_box(query_box) )
      return get_child(c);
  }
  return 0;
}

BoxTreeNode *BoxTreeNode::find_box_contains(const Box &query_box, int level_limit )
{
  // up
  BoxTreeNode *b = this;
  while ( !b->contains_box(query_box) )
  {
    if ( b->parent )
      b = b->parent;
    else
      break; // b is root
  }
  // down
  return b->find_leaf_child_contains(query_box, level_limit);

}
// just go down the tree, not up
BoxTreeNode *BoxTreeNode::find_leaf_child_contains(const Box &query_box, int level_limit)
{
  if ( level < level_limit )
  {
    BoxTreeNode* ch = get_child_contains(query_box);
    if (ch)
      return ch->find_leaf_child_contains(query_box, level_limit);
  }
  return ( contains_box(query_box) ? this : 0 );
}


BoxTreeNode *BoxTreeNode::find_box(const Point &q, int level_limit)
{
  // up
  // until the box contains the point
  BoxTreeNode *b = this;
  while ( b && !b->contains_point(q) )
    b = b->parent;
  
  // down
  // get child box containing point until a leaf or level limit
  while ( b && !b->is_leaf() && b->level < level_limit )
  {
    b = b->get_child(q);
  }
  
  assert( !b || b->contains_point(q) );
  
  return b;
}

BoxTreeNode *BoxTreeNode::get_child(const Point& q, int &i, Index &ind)
{
  if (is_leaf())
  {
    i = -1;
    ind = -1;
    return 0;
  }
  
  // if this was always 2x2x2, could do this with a single query on each coordinate vs. this's center point
  i = 0;
  ind = 0;
  BoxTreeNode *ch = get_child(0);
  while (q.x > ch->max_x() && ind.x + 1 < child_size.x)
  {
    ++ind.x;
    i += child_size.y * child_size.z;
    ch = get_child(i);
  }

  while (q.y > ch->max_y() && ind.y + 1 < child_size.y)
  {
    ++ind.y;
    i += child_size.z;
    ch = get_child(i);
  }

  while (q.z > ch->max_z() && ind.z + 1 < child_size.z)
  {
    ++ind.z;
    ++i;
    ch = get_child(i);
  }

  assert(ch);
  assert( ch->contains_point(q) );

  return ch;
}


void Box::print() const
{
  corner_min().print();
  corner_max().print();
  std::cout << "diagonal: "; diagonal().print();
  std::cout << "length:" << diagonal().length() << std::endl;
}

void BoxTreeNode::print2() const
{
  std::cout << "BoxTreeNode:" << this << std::endl;
  Box::print();
  std::cout << "id:" << global_id << " level:" << level;
  std::cout << " parent:" << parent << " birth_order:" << birth_order;
  std::cout << " child_size:" << child_size << " max_child:" << max_child << " children:"  << children;
  std::cout << std::endl;
}


void BoxTreeNode::print_neighbors( int f, std::vector<BoxTreeNode*> &nbh, bool use_id )
{
  if (use_id)
  {
    std::cout << "Hex " << get_id() << " face " << f << " has " << nbh.size() << " neighbors:";
    for (size_t i = 0; i < nbh.size(); ++i)
      std::cout << " " << nbh[i]->get_id();
    std::cout << std::endl;
  }
  else
  {
    std::cout << "Hex " << this << " face " << f << " has " << nbh.size() << " neighbors:";
    for (size_t i = 0; i < nbh.size(); ++i)
      std::cout << " " << nbh[i];
    std::cout << std::endl;
  }
}

WarpedFace::WarpedFace() : f(-1)
{
  xyz[0] = 0.; xyz[1] = 0.; xyz[2] = 0.;
  xyz[3] = 0.;
}
