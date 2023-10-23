// triangulation.cpp
//
//  Created by Mitchell, Scott A on 18 Oct 2016.
//  Copyright (c) 2016 Sandia National Labs. All rights reserved.
//
//
#include "triangulation.h"

#include "surface.h"
// ========================== Node =====================


// get two edges of t containing this
void Node::edges(Triangle *t, Edge &e0, Edge &e1) const
{
  // on = other node
  size_t i = 0;
  if (t->_nodes[i] == this) ++i;
  Node *on0 = t->_nodes[i];
  ++i;
  if (t->_nodes[i] == this) ++i;
  Node *on1 = t->_nodes[i];
  
  assert( i < 3 );
  assert( on0 != this );
  assert( on1 != this );
  
  Node *this_node = const_cast<Node*>( this );
  
  e0 = Edge(this_node, on0);
  e1 = Edge(this_node, on1);
}

void Node::edges( std::vector<Edge> &es ) const
{
  es.clear();
  es.reserve(_triangles.size() * 2);
  Edge e0,e1;
  for (size_t i = 0; i < _triangles.size(); ++i)
  {
    edges(_triangles[i],e0,e1);
    e0.push_back_unique( es );
    e1.push_back_unique( es );
  }
}


bool Node::closed() const
{
  // closed if every edge is closed: that was slow, implemented
  // checking the number of edges instead
  std::vector<Edge> es;
  edges(es);
  // special case, node is on domain boundary
  return (es.size() == _triangles.size());
}


// true if triangles around n form disk or half-disk topology
bool Node::simple_topology() const
{
  if (_triangles.empty())
    return true;

  // mark all triangles as not having been visited
  std::vector<int> visited(_triangles.size(), 0);

  // march from one edge of the first triangle
  Triangle *t0 = _triangles[0];
  visited[0] = 1;

  // get two edges of triangle containing this
  Edge e0, e1;
  edges(t0, e0, e1);

  // march from e0 around this node
  march_fan( t0, e0, visited);
  // did we visit everyone?
  if (all_visited(visited))
    return true;

  // march from e1
  march_fan( t0, e1, visited);
  if (all_visited(visited))
    return true;

  return false;  

};

bool Node::all_visited(const std::vector<int> &visited) const
{
  for (size_t i = 0; i < visited.size(); ++i)
  {
    if (visited[i] == 0)
      return false;
  }
  return true;
}


void Node::march_fan( Triangle *t0, Edge e, std::vector<int> &visited) const
{
  Triangle *t = t0;
  while( true)
  {
    Edge e2;
    Triangle *t2(0);
    next_triangle( t, e, t2, e2 );

    // completed circle or end of fan?
    if (t2 == 0 || t2 == t0)
      return;

    // mark t2 as visited
    bool found = false;
    for (size_t j = 1; j < _triangles.size(); ++j)
    {
      if ( t2 == _triangles[j] )
      {
        visited[j] = true;
        found = true;
        break;
      }
    }
    assert(found);

    // advance
    t = t2;
    e = e2;
  }
}

void Node::next_triangle( Triangle *t, const Edge &e, Triangle *&t2, Edge &e2 ) const
{ // zzyk redo so goes over the node's triangles, not the edge's
  std::vector<Triangle*> tris;
  e.triangles(tris);
  for (size_t i = 0; i < tris.size(); ++i)
  {
    // found a triangle that isn't t
    t2 = tris[i];
    if (t2 != t)
    {
      // find the edge of t2 containing this, that isn't e
      Edge eA, eB;
      edges(t2, eA, eB);
      // eA ^| eB should be e, pick e2 to be the other one
      e2 = ( eA.same_edge(e) ? eB : eA );

      assert( eA.same_edge(e) || eB.same_edge(e));
      assert( ! (eA.same_edge(e) && eB.same_edge(e) ) );
      assert( !e2.same_edge(e) );

      return;
    }
  }
  // return null
  t2 = 0;
  e2 = Edge();
  return;
}



// ========================== Edge =====================

void Edge::triangles(std::vector<Triangle*> &tris) const
{
  tris.clear();
  if (!_n0 || !_n1) return;
  for (size_t i = 0; i <_n0->_triangles.size(); ++i)
    for (size_t j = 0; j <_n1->_triangles.size(); ++j)
      if ( _n0->_triangles[i] == _n1->_triangles[j] )
        tris.push_back( _n0->_triangles[i] );
  // manifold or sub-manifold
  // assert(tris.size() == 0 || tris.size() == 1 || tris.size() == 2);
}


void Edge::print() const
{
  std::cout << "Edge\n  _n0 ";
  if (_n0)
    _n0->print();
  else
    std::cout << " null\n";
  std::cout << "  _n1 ";
  if (_n1)
    _n1->print();
  else
    std::cout << " null\n";
}

// ========================== Triangle =====================


void Triangle::print() const
{
  std::cout << "Triangle\n";
  for (size_t i = 0; i < _nodes.size(); ++i )
  {
    std::cout << "  node " << i << " ";
    if (_nodes[i])
      _nodes[i]->print();
    else
      std::cout << " null\n";
  }
}


void Triangle::edges(std::vector<Edge> &es) const
{
  es.clear();
  if (_nodes.empty())
    return;
  assert(_nodes.size()==3);
  es.push_back( Edge(_nodes[0],_nodes[1]) );
  es.push_back( Edge(_nodes[1],_nodes[2]) );
  es.push_back( Edge(_nodes[2],_nodes[0]) );
}


bool Triangle::same_triangle(Triangle*t) const
{
  if (!t) return false;
  if (_nodes.size() != t->_nodes.size()) return false;
  if (_nodes.empty()) return true;
  assert(_nodes.size()==3);
  for (size_t i=0; i<_nodes.size(); ++i)
    if ( _nodes[i] != t->_nodes[0] &&
        _nodes[i] != t->_nodes[1] &&
        _nodes[i] != t->_nodes[2] )
      return false;
  return true;
}

bool Triangle::shared_edge(Triangle *t, Edge &e) const
{
  std::vector<Edge> es;
  edges(es);
  std::vector<Edge> es2;
  t->edges(es2);
  for (size_t i = 0; i < es.size(); ++i)
    for (size_t j = 0; j < es2.size(); ++j)
      if (es[i].same_edge(&es2[j]))
      {
        e = es[i];
        return true;
      }
  e = Edge();
  return false;
}


Point Triangle::normal() const
{
  
  // find normal to plane of triangle
  const Point &p0 = * _nodes[0];
  const Point &p1 = * _nodes[1];
  const Point &p2 = * _nodes[2];
  
  const Point v01 = p1 - p0;
  const Point v02 = p2 - p0;
  
  // make sure not colinear degenerate triangle, for horizontal triangles
  assert( fabs(v01.z) > 10. || fabs(v02.z) > 10. || !v01.is_colinear(v02, 0.999) );
  
  // normals to plane p0,p1,p2
  Point n = v01.cross(v02);
  n.normalize();
  return n;
}

void Triangle::quality( double &cos_alpha, double &cos_omega, double &lr) const
{
  // first convert to reference plane
  const Point &p0 = * _nodes[0];
  const Point &p1 = * _nodes[1];
  const Point &p2 = * _nodes[2];
  
  Point v01 = p1 - p0;
  Point v02 = p2 - p0;
  Point v12 = p2 - p1;
  
  double l01 = v01.length(); // "el 01"
  double l02 = v02.length(); // "el 02"
  double l12 = v02.length(); // "el 12"
  
  double l = std::min( std::min( l01, l02 ), l12 );
  double L = std::max( std::max( l01, l02 ), l12 );
  lr = l / L;
  
  double cos0 =  v01.dot(v02) / (l01 * l02);
  double cos1 = -v01.dot(v12) / (l01 * l12);
  double cos2 =  v02.dot(v12) / (l02 * l12);

  cos_alpha = std::min( std::min( cos0, cos1 ), cos2 );
  cos_omega = std::max( std::max( cos0, cos1 ), cos2 );
  
//  // here's how to get the matrix of the element in the reference plane, [q0; q1]
//  // in reference plane
//  Point q0 ( l01, 0., 0. );
//
//  double cos_theta = v01.dot(v02) / (l01 * l02);
//  double sin_theta = sqrt( 1. - cos_theta * cos_theta );
//  
//  Point q1 ( l02 * cos_theta, l02 * sin_theta, 0. );
  
  
}


Triangulation::~Triangulation()
{
		for (size_t i = 0; i < _triangles.size(); ++i )
      delete _triangles[i];
		_triangles.clear();
		for (size_t i = 0; i < _nodes.size(); ++i )
      delete _nodes[i];
		_nodes.clear();
}

void Triangulation::delete_last_triangle( )
{
  Triangle *t = _triangles.back();
  _triangles.pop_back();
  for (int i = 0; i < t->_nodes.size(); ++i)
  {
    Node *n = t->_nodes[i];
    assert( n->_triangles.back() == t );
    n->_triangles.pop_back();
  }

  // grid_point of n will remain with a node, so all the checks that are done for already-meshed nodes will be done
  // double check that none of those rely on there being at least one triangle attached
  delete t;
}

bool Edge::domain_boundary( const Grid *g /* pass _s */ ) const
{
	// check if two nodes are at extreme x or y coordinates
	return ( 
		( _n0->x == g->min_x() && _n1->x == g->min_x() ) ||
		( _n0->x == g->max_x() && _n1->x == g->max_x() ) ||
		( _n0->y == g->min_y() && _n1->y == g->min_y() ) ||
		( _n0->y == g->max_y() && _n1->y == g->max_y() ) );
}

Triangle::Triangle(Node *n0, Node *n1, Node *n2) : _id(-1)
{
  assert(n0);
  assert(n1);
  assert(n2);
  assert(n0->z > 5.); //debug
  assert(n1->z > 5.); //debug
  assert(n2->z > 5.); //debug
  _nodes.resize(3);
  _nodes[0] = n0;
  _nodes[1] = n1;
  _nodes[2] = n2;
}

Triangle *Triangulation::new_triangle()
{
  Triangle *t = new Triangle;
  t->_id = _triangles.size();
	_triangles.push_back(t);
  t->_triangulation = this;
	return t;
}

Triangle *Triangulation::new_triangle(Node*n0, Node*n1, Node*n2)
{
	Triangle *t = new Triangle(n0,n1,n2);
  t->_id = _triangles.size();
  n0->_triangles.push_back(t);
  n1->_triangles.push_back(t);
  n2->_triangles.push_back(t);
	_triangles.push_back(t);
  t->_triangulation = this;
	return t;
}

Node *Triangulation::new_node()
{
	Node *n = new Node;
  n->_id = _nodes.size();
	_nodes.push_back(n);
	return n;
}

Node *Triangulation::new_node(Point p)
{
  if ( isnormal(p.z) || (p.z == 0.) )
  {
    assert( p.z > 5.); // debug, our surfaces all have z coordinates larger than zero
    Node *n = new Node(p);
    n->_id = _nodes.size();
    _nodes.push_back(n);
    return n;
  }
  return 0;
}

void Triangulation::delete_unused_nodes()
{
  // go through all the nodes, deleting the ones that have no triangles,
  // and adding back in the ones that do
  std::vector<Node*>all_nodes;
  all_nodes.swap( _nodes );
  for (size_t i = 0; i < all_nodes.size(); ++i)
  {
    Node *n = all_nodes[i];
    if (n->_triangles.empty())
      delete n;
    else
    {
      n->_id = _nodes.size();
      _nodes.push_back(n);
    }
  }
}

bool Edge::operator< (const Edge& right) const
{
  // first sort the nodes of the edge
  Node *f0,*f1,*r0,*r1;
  if (_n0 < _n1)
  {
    f0 = _n0;
    f1 = _n1;
  }
  else
  {
    f1 = _n0;
    f0 = _n1;
  }
  
  if (right._n0 < right._n1)
  {
    r0 = right._n0;
    r1 = right._n1;
  }
  else
  {
    r1 = right._n0;
    r0 = right._n1;
  }
  
  if ( f0 == r0 )
  {
    return f1 < r1;
  }
  else
    return f0 < r0;
}