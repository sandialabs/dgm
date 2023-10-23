// triangulation.h
//   node, edge, triangle
//
//  Created by Mitchell, Scott A on 18 Oct 2016.
//  Copyright (c) 2016 Sandia National Labs. All rights reserved.
//
//
#ifndef __BoxTreeMesh__triangulation__
#define __BoxTreeMesh__triangulation__

#define __BoxTreeMesh__triangulation__debug

//zzyk memory manage the triangles and nodes

#include <vector>
#include "point.h"
class Grid;
class Triangulation;
class Triangle;
class Edge;
class Node : public Point
{
public:
	Node() {}
  Node(Point *p) : Point(*p) {}
  Node(Point p) : Point(p) {}

  // == data  
  // Triangles containing the node
  std::vector<Triangle*> _triangles;
  
  // debug
  size_t _id = -1;

  // == methods 
  // get all the edges containing the Node
  void edges( std::vector<Edge> &es ) const;

  // get the two edges of t and this node
  void edges( Triangle *t, Edge &e0, Edge &e1 ) const;

  // closed means the node is already manifold
  // this returns a false negative for nodes on the
  // domain boundary that have a complete half-disk neighborhood
  bool closed() const; //beware slow
  // no pinch points
  bool simple_topology() const; //beware slow

protected:  
  // utilities for simple_topology
  // march_fan
  //   given e containing this, and t0 containing e, 
  //   visit the chain of triangles containing this, starting with the other triangle of e
  void march_fan( Triangle *t0, Edge e, std::vector<int> &visited) const;
  bool all_visited(const std::vector<int> &visited) const;

  // get triangle t2 sharing e0 with t,
  // and its edge e2 containing this
  void next_triangle( Triangle *t, const Edge &e, Triangle *&t2, Edge &e2 ) const;
};

// edges are just temporary objects, use them directly, not pointers to them, in vectors
class Edge
{
public:
  Edge(Node* n0, Node* n1) : _n0(n0), _n1(n1) {}
  Edge() : _n0(0), _n1(0) {}
  Node *_n0 = 0;
  Node *_n1 = 0;
  
  bool same_edge(Edge*e) const;
  bool same_edge(const Edge &e) const;
  
  void triangles(std::vector<Triangle*> &tris) const;
  
  bool closed() const;
  virtual void print() const;

  // add this to es if it is not already in es
  void push_back_unique( std::vector<Edge> &es ) const;

  bool domain_boundary( const Grid *g /* pass _s */ ) const;
  
  bool operator< (const Edge& right) const;
  bool operator==(const Edge& right) const
  { return same_edge(right); }
  bool operator!=(const Edge& right) const
  { return !same_edge(right); }

};

class Triangle
{
public:
  Triangle() : _nodes(3,0), _id(-1) {}
  Triangle(Node *n0, Node *n1, Node *n2);

  void edges(std::vector<Edge> &es) const;
  
  bool same_triangle(Triangle*t) const;

  // true if this and e share an edge, and return that edge in e
  bool shared_edge(Triangle *t, Edge &e) const;
  
  Node* opposite_node( Edge e ) const;
  
  Point normal() const;
  
  // double quality() const; // can I figure out Knupp's shape metric and calculate it here?
  
  // return cosine of smallest (0,1), biggest angles (-1,0.5), and minimum edge length ratio (0,1)
  void quality( double &cos_alpha, double &cos_omega, double &lr) const;
  
  // nodes of the triangle
  std::vector<Node*> _nodes;
  
  // debug
  size_t _id = -1;

  Triangulation *_triangulation = 0;
  
  void print() const;

};

class Triangulation
{
public:
	Triangulation() {}
  ~Triangulation();

  std::vector<Triangle*> _triangles;
	std::vector<Node*> _nodes;

  // empty triangle
  Triangle *new_triangle();

  // also adds triangle to the nodes
  Triangle *new_triangle(Node*n0, Node*n1, Node*n2);

  // delete the triangle I just new_triangle'd
  // but leaves nodes
  void delete_last_triangle();

  Node *new_node();
  Node *new_node(Point p);

  // debug
  std::vector<Triangle*> _vertical_triangles;
  std::vector<Triangle*> _horizontal_triangles;
  std::vector<Triangle*> _skew_triangles;

  void delete_unused_nodes();

};

inline
bool Edge::same_edge(const Edge &e) const
{
  return
  (_n0 == e._n0 && _n1 == e._n1) ||
  (_n0 == e._n1 && _n1 == e._n0);
}
inline
bool Edge::same_edge(Edge*e) const
{
  return same_edge(*e);
}

inline
bool Edge::closed() const
{
  std::vector<Triangle*> tris;
  triangles(tris);
  return tris.size() == 2;
}

inline
Node* Triangle::opposite_node( Edge e ) const
{
  for (size_t i = 0; i < _nodes.size(); ++i)
    if ( _nodes[i] != e._n0 && _nodes[i] != e._n1 )
      return _nodes[i];
  assert(0); // e is not an edge of the triangle, or the triangle is not well defined
  return 0;
}

inline
void Edge::push_back_unique( std::vector<Edge> &es ) const
{
  for (size_t i = 0; i < es.size(); ++i)
    if ( same_edge(&es[i]))
      return;
  es.push_back(*this);
}


#endif // __BoxTreeMesh__triangulation__