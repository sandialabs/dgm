/** \file SubdomainGrouping.hpp
    \brief Determine subdomain grouping given bounding boxes
    \author K. Noel Belcourt
*/

#ifndef SubdomainGrouping_hpp
#define SubdomainGrouping_hpp

#include <algorithm>
#include <cassert>
#include <cmath>
#include <limits>
#include <map>
#include <ostream>
#include <set>
#include <utility>
#include <vector>

#include <boost/tuple/tuple.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/property_map/vector_property_map.hpp>

#include "Box.hpp"
#include "Cartesian.hpp"
#include "Point.hpp"

// Algorithm for determining optimal subdomain grouping given subdomain
// bounding boxes.  Goal is to solve (pack) as many subdomains as possible
// in each MultiOptProblem subject to constraint that none of the
// subdomains can overlap with any other in the same MultiOptProblem solve.

// Matula, D. W. and Beck, L. L. Smallest-Last Ordering, Clustering
// and Graph Coloring Algorithms, ACM Vol. 30, 3 July 1983, pp 417-427.

// Algorithm is 4 pass:
// 1) Coarse grained check: construct bounding box around subdomain and
//    exclude subdomains that it can't possibly overlap.
// 2) Detailed check if any remaining boxes overlap (since bounding boxes
//    can be much larger than the subdomain itself if the subdomain is not
//    axis-aligned or rectilinear).  Create an edge in the overlap graph
//    for each pair of overlapping boxes (note that each subdomain is a
//    vertex in the graph).
// 3) Order vertices in graph using smallest last ordering algorithm (recall
//    that adjacent vertices, with an edge between them, must be assigned a
//    different color i.e. must run in a different MultiOptProblem).
// 4) Color the ordered vertices.  Note that a different ordering will result
//    in a different coloring with potentially different numbers of colors,
//    hence the NP-complete aspect of the coloring problem.

namespace DGM {

template <class VertexListGraph, class Order, class Color>
typename boost::graph_traits<VertexListGraph>::vertices_size_type
sequential_vertex_coloring(const VertexListGraph& G,
  Order order, Color& color)
{
  using boost::graph_traits;
  using boost::property_traits;
  using boost::tie;
  using std::numeric_limits;
  using std::vector;

  typedef graph_traits<VertexListGraph> GraphTraits;
  typedef typename GraphTraits::vertex_descriptor vertex_descriptor;
  typedef typename GraphTraits::vertices_size_type size_type;

  size_type max_color = 0;
  const size_type V = num_vertices(G);
  vector<size_type> mark(V, numeric_limits<size_type>::max());

  typename GraphTraits::vertex_iterator v, vend;
  for (tie(v, vend) = vertices(G); v != vend; ++v)
    color[*v] = V - 1; // which means "not colored"

  for (size_type i = 0; i < V; ++i) {
    vertex_descriptor current = order[i];

    // mark all the colors of the adjacent vertices
    typename GraphTraits::adjacency_iterator ai, aend;
    for (tie(ai, aend) = adjacent_vertices(current, G); ai != aend; ++ai)
      mark[color[*ai]] = i;

    // find the smallest color unused by the adjacent vertices
    size_type smallest_color = 0;
    while (smallest_color < max_color && mark[smallest_color] == i)
      ++smallest_color;

    // if all the colors are used up, increase the number of colors
    if (smallest_color == max_color)
      ++max_color;

    color[current] = smallest_color;
  }
  return max_color;
}

template <class VertexListGraph, class Order, class Degree,
  class Marker, class BucketSorter>
void largest_first_ordering(const VertexListGraph& G, Order order,
  Degree degree, Marker marker, BucketSorter& degree_buckets)
{
  using boost::graph_traits;
  using boost::put;
  using boost::tie;
  using std::max;

  typedef graph_traits<VertexListGraph> GraphTraits;
  typedef typename GraphTraits::vertex_descriptor Vertex;
  typedef size_t size_type;

  const size_type num = num_vertices(G);

  size_type maximum_degree = 0;

  typename GraphTraits::vertex_iterator v, vend;
  for (tie(v, vend) = vertices(G); v != vend; ++v) {
    put(marker, *v, num);
    put(degree, *v, out_degree(*v, G));
    degree_buckets.push(*v);
    maximum_degree = max(maximum_degree, degree[*v]);
  }
  // cout << "maximum_degree = " << maximum_degree << endl;

  size_type current_order = 0;

  while (current_order != num) {
    typedef typename BucketSorter::stack_t BSstack;
    BSstack* maximum_degree_stack = degree_buckets[maximum_degree];
    while (maximum_degree_stack->empty() && 0 <= maximum_degree)
      maximum_degree_stack = degree_buckets[--maximum_degree];

    while(!maximum_degree_stack->empty()) {
      Vertex node = maximum_degree_stack->top();
      put(order, current_order, node);
      maximum_degree_stack->pop();
      ++current_order;
    }
  }
}

template <class VertexListGraph, class Order, class Degree,
  class Marker, class BucketSorter>
void smallest_last_ordering(const VertexListGraph& G, Order order,
  Degree degree, Marker marker, BucketSorter& degree_buckets)
{
  using boost::graph_traits;
  using boost::get;
  using boost::put;
  using boost::tie;
  using std::min;

  typedef graph_traits<VertexListGraph> GraphTraits;
  typedef typename GraphTraits::vertex_descriptor Vertex;
  typedef size_t size_type;

  const size_type num = num_vertices(G);

  typename GraphTraits::vertex_iterator v, vend;
  for (tie(v, vend) = vertices(G); v != vend; ++v) {
    put(marker, *v, num);
    put(degree, *v, out_degree(*v, G));
    degree_buckets.push(*v);
  }

  size_type minimum_degree = 0;
  size_type current_order = num - 1;

  while (1) {
    typedef typename BucketSorter::stack_t BSstack;
    BSstack* minimum_degree_stack = degree_buckets[minimum_degree];
    while (minimum_degree_stack->empty())
      minimum_degree_stack = degree_buckets[++minimum_degree];

    Vertex node = minimum_degree_stack->top();
    put(order, current_order, node);

    if ( current_order == 0 ) // find all vertices
      break;

    minimum_degree_stack->pop();
    put(marker, node, 0); // node has been ordered.

    typename GraphTraits::adjacency_iterator v, vend;
    for (tie(v,vend) = adjacent_vertices(node, G); v != vend; ++v) {

      if (current_order < get(marker, *v)) {
        put(marker, *v, current_order);
        // minimum degree might go down, update it
        put(degree, *v, get(degree, *v) - 1);
        minimum_degree = min(minimum_degree, get(degree, *v));
        // move the vertex to new bucket
        degree_buckets.update(*v);
      }
    }
    --current_order;
  }
}

// D is the degree type
// T is graph vertex descriptor
template <typename Degree, typename T>
struct degree_buckets {

  // stack like interface to an O(1) insert / remove,
  // and log N search, data structure
  struct stack_t {
    std::set<T> ids;
    void pop() {
      assert(!ids.empty());
      ids.erase(ids.begin());
    }
    T top() {
      assert(!ids.empty());
      return *ids.begin();
    }
    bool empty() {
      return ids.empty();
    }
    void push(T id) {
      ids.insert(id);
    }
    void erase(T id) {
      typename std::set<T>::iterator it = ids.find(id);
      assert(it != ids.end());
      ids.erase(it);
    }
  };

  typedef typename boost::vector_property_map<Degree> degree_map_t;
  typedef typename std::map<T, stack_t> container_t;
  typedef typename container_t::iterator iterator;
  typedef typename container_t::value_type vt;
  container_t degree2id;
  degree_map_t& degree;
  iterator it, end;
  std::pair<iterator, bool> pib;

  degree_buckets(degree_map_t& vpm) : degree(vpm),
    end(degree2id.end()) {}

  void push(T id) {
    Degree d = get(degree, id);
    it = degree2id.find(d);
    if (end == it) {
      // no stack for this degree, insert one
      stack_t st;
      pib = degree2id.insert(vt(d, st));
      assert(pib.second);
      it = pib.first;
    }
    // insert id into appropriate degree stack
    stack_t& st = it->second;
    st.push(id);
  }

  void remove(T id) {
    Degree d = get(degree, id);
    it = degree2id.find(d+1);
    assert(it != end);
    // find this id in stack
    it->second.erase(id);
  }

  void update(T id) {
    remove(id);
    push(id);   // add to new degree stack
  }

  stack_t* operator[](Degree d) {
    it = degree2id.find(d);
    if (end == it) {
      // no stack for this degree, insert one so can return
      // an empty stack in response to query for this degree
      stack_t st;
      pib = degree2id.insert(vt(d, st));
      assert(pib.second);
      it = pib.first;
    }
    return &it->second;
  }
};

template <typename Coord>
struct edge {
  // two vertices define an edge
  Point pts[2];
  // typedef Point* iterator;
  void set(const Point &u, const Point &v) {
    pts[0] = u;
    pts[1] = v;
  }
};

// total-ordering for use as map key
template <typename Coord>
bool operator<(const edge<Coord> &p, const edge<Coord> &q) {
  return (p.pts[0] < q.pts[0] && p.pts[0] < q.pts[1]) ||
       (!(p.pts[0] < q.pts[0] && p.pts[0] < q.pts[1]) &&
         (p.pts[1] < q.pts[0] && p.pts[1] < q.pts[1]));
}

template <typename Edge>
typename DGM::Point first(Edge &e) {
  return e.pts[0];
}

template <typename Edge>
typename DGM::Point second(Edge &e) {
  return e.pts[1];
}

template <typename Coord>
struct face {
  typedef edge<Coord> Edge;
  // Anchor (first corner of) face
  Point anchor;
  // edges of this face
  std::vector<Edge> edge_list;
  typedef typename std::vector<Edge>::iterator EdgeIterator;
  typedef std::pair<EdgeIterator, EdgeIterator> EdgeIteratorPair;
  // equation of this face is ax + by + cz + d = 0
  Coord a, b, c, d;
  face() : edge_list(4), a(0), b(0), c(0), d(0) {}
  face(const face& f) : edge_list(4), a(0), b(0), c(0), d(0) {
    edge_list = f.edge_list;
    anchor = f.anchor;
    a = f.a;
    b = f.b;
    c = f.c;
    d = f.d;
  }
  void set_edges(const Point &ll, const Point &lr, const Point &ur,
    const Point &ul)
  {
    assert(4 == edge_list.size());
    anchor = ll;
    edge_list[0].set(ll, lr);
    edge_list[1].set(lr, ur);
    edge_list[2].set(ur, ul);
    edge_list[3].set(ul, ll);
  }
  void set_normal(const Point &t, Coord w) {
    // normal must face outward
    a = t.x;
    b = t.y;
    c = t.z;
    d = w;
  }
  EdgeIteratorPair edges() {
    return EdgeIteratorPair(edge_list.begin(), edge_list.end());
  }
  bool in_front_of(const Point &p) const {
    Point q = p - anchor;
    Coord v = a * q.x + b * q.y + c * q.z + d;
    return 0 < v;
  }
};

template <typename Coord>
typename face<Coord>::EdgeIteratorPair edges(face<Coord> &f) {
  return f.edges();
}

template <typename Point, typename Coord>
bool opposite_side_of(const Point &p, const Point &q, const face<Coord> &f) {
  if (f.in_front_of(p))
    return !f.in_front_of(q);
  return f.in_front_of(q);
}

template <typename Scalar, typename Space, typename Id>
struct box_with_id : public DGM::box<Scalar, Space> {
  // bounding box
  Scalar x_min, x_max, y_min, y_max, z_min, z_max;
  // corner points of box
  Point fll, flr, fur, ful, bll, blr, bur, bul;
  // Edges
  typedef edge<Scalar> Edge;
  std::vector<Edge> edge_list;
  typedef typename std::vector<Edge>::iterator EdgeIterator;
  typedef typename std::pair<EdgeIterator, EdgeIterator> EdgeIteratorPair;
  // Faces
  typedef face<Scalar> Face;
  std::multimap<Edge, Face> faces_by_edge;
  typedef typename std::multimap<Edge, Face>::value_type vt;
  typedef typename std::multimap<Edge, Face>::iterator FaceIterator;
  typedef typename std::pair<FaceIterator, FaceIterator> FaceIteratorPair;
  // face normals (ax + by + cz +d) and edge connectivity
  Face front, back, left, right, top, bottom;
  Id id;
  Id vertex;
  box_with_id() : x_min(0), x_max(0), y_min(0), y_max(0),
    z_min(0), z_max(0), id(0), vertex(0) {}
  box_with_id(Id i) : x_min(0), x_max(0), y_min(0), y_max(0),
    z_min(0), z_max(0), id(i), vertex(0) {}
  box_with_id& operator=(const box_with_id& b) {
    x_min = b.x_min, x_max = b.x_max;
    y_min = b.y_min, y_max = b.y_max;
    z_min = b.z_min, z_max = b.z_max;
    id = b.id;
    vertex = b.vertex;
    front = b.front, back = b.back;
    left = b.left, right = b.right;
    top = b.top, bottom = b.bottom;
    return *this;
  }

  void bounding_box() {
    using std::min;
    using std::max;
    // compute box dimensions
    x_min = min(fll.x, min(ful.x, min(bll.x, bul.x)));
    x_max = max(flr.x, max(fur.x, max(blr.x, bur.x)));
    y_min = min(fll.y, min(flr.y, min(bll.y, blr.y)));
    y_max = max(ful.y, max(fur.y, max(bul.y, bur.y)));
    z_min = min(fll.z, min(flr.z, min(fur.z, ful.z)));
    z_max = max(bll.z, max(blr.z, max(bur.z, bul.z)));
  }

  void compute_face_normals() {
    using boost::tie;
    // normals computed so positive normal faces outside domain
    // equation of plane using direction numbers for the normal
    // a(x-x1) + b(y-y1) + c(z-z1) = 0 ==>
    // ax + by + cz + d = 0 where d = -a*x1 + -b*y1 + -c*z1
    // front face
    Point r(flr.x-fll.x, flr.y-fll.y, flr.z-fll.z);
    Point s(ful.x-fll.x, ful.y-fll.y, ful.z-fll.z);
    Point t;
    t.cross(r, s);
    Scalar d = (t.x * - r.x) + (t.y * - r.y) + (t.z * - r.z);
    front.set_normal(t, d);
    front.set_edges(fll, flr, fur, ful);
    // back face
    r(bul.x-bll.x, bul.y-bll.y, bul.z-bll.z);
    s(blr.x-bll.x, blr.y-bll.y, blr.z-bll.z);
    t.cross(r, s);
    d = (t.x * - r.x) + (t.y * - r.y) + (t.z * - r.z);
    back.set_normal(t, d);
    back.set_edges(bll, bul, bur, blr);
    // left face
    r(fll.x-bll.x, fll.y-bll.y, fll.z-bll.z);
    s(bul.x-bll.x, bul.y-bll.y, bul.z-bll.z);
    t.cross(r, s);
    d = (t.x * - r.x) + (t.y * - r.y) + (t.z * - r.z);
    left.set_normal(t, d);
    left.set_edges(bll, fll, ful, bul);
    // right face
    r(bur.x-blr.x, bur.y-blr.y, bur.z-blr.z);
    s(flr.x-blr.x, flr.y-blr.y, flr.z-blr.z);
    t.cross(r, s);
    d = (t.x * - r.x) + (t.y * - r.y) + (t.z * - r.z);
    right.set_normal(t, d);
    right.set_edges(blr, bur, fur, flr);
    // top face
    r(fur.x-ful.x, fur.y-ful.y, fur.z-ful.z);
    s(bul.x-ful.x, bul.y-ful.y, bul.z-ful.z);
    t.cross(r, s);
    d = (t.x * - r.x) + (t.y * - r.y) + (t.z * - r.z);
    top.set_normal(t, d);
    top.set_edges(ful, fur, bur, bul);
    // bottom face
    r(bll.x-fll.x, bll.y-fll.y, bll.z-fll.z);
    s(flr.x-fll.x, flr.y-fll.y, flr.z-fll.z);
    t.cross(r, s);
    d = (t.x * - r.x) + (t.y * - r.y) + (t.z * - r.z);
    bottom.set_normal(t, d);
    bottom.set_edges(fll, bll, blr, flr);
    // fill edge list (front + back + 4 in the middle)
    EdgeIteratorPair eip = front.edges();
    edge_list.insert(edge_list.end(), eip.first, eip.second);
    eip = back.edges();
    edge_list.insert(edge_list.end(), eip.first, eip.second);
    edge_list.push_back(top.edge_list[1]);
    edge_list.push_back(top.edge_list[3]);
    edge_list.push_back(bottom.edge_list[0]);
    edge_list.push_back(bottom.edge_list[2]);
    // faces by edge, front and back face plus 4 middle edges
    EdgeIterator it, end;
    tie(it, end) = edges(front);
    faces_by_edge.insert(vt(*it, front));
    faces_by_edge.insert(vt(*it, bottom));
    faces_by_edge.insert(vt(*++it, front));
    faces_by_edge.insert(vt(*it, right));
    faces_by_edge.insert(vt(*++it, front));
    faces_by_edge.insert(vt(*it, top));
    faces_by_edge.insert(vt(*++it, front));
    faces_by_edge.insert(vt(*it, left));
    tie(it, end) = edges(back);
    faces_by_edge.insert(vt(*it, back));
    faces_by_edge.insert(vt(*it, left));
    faces_by_edge.insert(vt(*++it, back));
    faces_by_edge.insert(vt(*it, top));
    faces_by_edge.insert(vt(*++it, back));
    faces_by_edge.insert(vt(*it, right));
    faces_by_edge.insert(vt(*++it, back));
    faces_by_edge.insert(vt(*it, bottom));
    // 4 edges connecting front and back faces
    faces_by_edge.insert(vt(top.edge_list[1], top));
    faces_by_edge.insert(vt(top.edge_list[1], right));
    faces_by_edge.insert(vt(top.edge_list[3], top));
    faces_by_edge.insert(vt(top.edge_list[3], left));
    faces_by_edge.insert(vt(bottom.edge_list[0], bottom));
    faces_by_edge.insert(vt(bottom.edge_list[0], left));
    faces_by_edge.insert(vt(bottom.edge_list[2], bottom));
    faces_by_edge.insert(vt(bottom.edge_list[2], right));
  }

  template <typename Iter>
  bool face_overlaps(Iter it, box_with_id &b, Face &f) {
    using boost::tie;
    EdgeIterator e_it, e_end;
    FaceIterator f_it, f_end;
    if (opposite_side_of(first(*it), second(*it), f)) {
      // get faces attached to this edge
      for (tie(f_it, f_end) = faces(*it, b); f_it != f_end; ++f_it) {
        // get edges on this face and check for intersection
        for (tie(e_it, e_end) = edges(f); e_it != e_end; ++e_it) {
          if (opposite_side_of(first(*e_it), second(*e_it), (*f_it).second)) {
            return true;
          }
        }
      }
    }
    return false;
  }

  bool any_face_overlaps(box_with_id& c) {
    using boost::tie;
    EdgeIterator it, end; //, e_it, e_end;
    FaceIterator f_it, f_end;
    // check if any edge bisects (the infinite plane of) the any face
    for (tie(it, end) = edges(c); it != end; ++it) {
      if (face_overlaps(it, c, front) || face_overlaps(it, c, back) ||
          face_overlaps(it, c, left) || face_overlaps(it, c, right) ||
          face_overlaps(it, c, top) || face_overlaps(it, c, bottom)) {
            return true;
      }
    }
    return false;
  }
};

template <typename Scalar, typename Space, typename Id>
std::ostream& operator<<(std::ostream& ofp, const box_with_id<Scalar, Space, Id>& b) {
  ofp << "[" << b.x_min << "," << b.x_max << "], " <<
         "[" << b.y_min << "," << b.y_max << "], " <<
         "[" << b.z_min << "," << b.z_max << "]" << std::endl;
  return ofp;
}

template <typename Coord, typename Space, typename Id>
typename box_with_id<Coord, Space, Id>::EdgeIteratorPair
edges(box_with_id<Coord, Space, Id> &b) {
  typedef box_with_id<Coord, Space, Id> Box;
  typedef typename Box::EdgeIteratorPair EdgeIteratorPair;
  return EdgeIteratorPair(b.edge_list.begin(), b.edge_list.end());
}

template <typename Coord, typename Space, typename Id>
typename box_with_id<Coord, Space, Id>::FaceIteratorPair
faces(edge<Coord> &e, box_with_id<Coord, Space, Id> &b) {
  return b.faces_by_edge.equal_range(e);
}

template <typename Coord, typename Space, typename Id>
struct id_coords {
  typedef edge<Coord> Edge;
  typedef face<Coord> Face;
  // construct graph for use with coloring algorithm to do packing
  // each subdomain is a vertex in graph
  // each edge connects two subdomains (vertices) that overlap
  // each color is a group of non-overlapping subdomains
  typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS>
    undirected_graph;
  typedef typename boost::graph_traits<undirected_graph>::vertex_descriptor
    Vertex;
  undirected_graph udg;
  vector<Id> color;
  // Boxes
  typedef box_with_id<Coord, Space, Id> Box;
  std::vector<Box> boxes;
  // Graph colors
  std::size_t n_colors;
  // Whether processing 3d or 2d boxes
  bool subdomains_3d;
  // final list of groups of non-overlapping subdomains
  typedef std::vector<Id> id_list_t;
  typedef std::vector<id_list_t> grouping_t;
  grouping_t groups;

  id_coords() : n_colors(0), subdomains_3d(false) {}

  Coord direction(const Point& i, const Point& j, const Point& k) {
    Point p = k - i;
    Point q = j - i;
    // cross product
    return p.x * q.y - p.y * q.x;
  }

  bool on_segment(const Point& i, const Point& j, const Point& k) {
    using std::min;
    using std::max;
    return min(i.x, j.x) <= k.x && k.x <= max(i.x, j.x) &&
           min(i.y, j.y) <= k.y && k.y <= max(i.y, j.y);
  }

  // given 4 points (two line segments), check for intersection
  // p and q are endpoints of first line segment, r and s and 2nd line segment
  bool intersect(const Point& p, const Point& q, const Point& r, const Point& s) {
    Coord d1 = direction(r, s, p);
    Coord d2 = direction(r, s, q);
    Coord d3 = direction(p, q, r);
    Coord d4 = direction(p, q, s);
    if (((0 < d1 && d2 < 0) || (d1 < 0 && 0 < d2)) &&
        ((0 < d3 && d4 < 0) || (d3 < 0 && 0 < d4))) {
      return true;
    }
    else if (d1 == 0 && on_segment(r, s, p)) {
      return true;
    }
    else if (d2 == 0 && on_segment(r, s, q)) {
      return true;
    }
    else if (d3 == 0 && on_segment(p, q, r)) {
      return true;
    }
    else if (d4 == 0 && on_segment(p, q, s)) {
      return true;
    }
    return false;
  }

  // add a 2d axis-aligned box to list
  void add_2d(Coord x_min, Coord x_max, Coord y_min, Coord y_max, Id id) {
    subdomains_3d = false;
    // add check that we don't add subdomain more than once (id is unique)
    Box b(id);
    b.fll(x_min, y_min);
    b.flr(x_max, y_min);
    b.fur(x_max, y_max);
    b.ful(x_min, y_max);
    // 2d make back equal to front
    b.bll = b.fll;
    b.blr = b.flr;
    b.bur = b.fur;
    b.bul = b.ful;
    // compute bounding box and add to list of boxes
    b.bounding_box();
    b.vertex = add_vertex(udg);
    boxes.push_back(b);
  }

  // generalized 3d interface
  template <typename Iter>
  void add_3d(Iter x, Iter x_end, Iter y, Iter z, Id id) {
    using std::distance;
    assert(8 == distance(x, x_end));
    // points are ordered, first 4 are front face, others back face
    // first point on face starts in lower left, counter-clockwise so
    // that face normals point outside the subdomain.
    subdomains_3d = true;
    // add check that we don't add subdomain more than once (id is unique)
    Box b(id);
    b.fll(*x, *y, *z);
    b.flr(*++x, *++y, *++z);
    b.fur(*++x, *++y, *++z);
    b.ful(*++x, *++y, *++z);
    b.bll(*++x, *++y, *++z);
    b.blr(*++x, *++y, *++z);
    b.bul(*++x, *++y, *++z);
    b.bur(*++x, *++y, *++z);
    b.bul(*++x, *++y, *++z);
    // compute bounding box and add to list of boxes
    b.bounding_box();
    b.vertex = add_vertex(udg);
    boxes.push_back(b);
  }

  // add a 3d axis-aligned box to list
  void add_3d(Coord x_min, Coord x_max, Coord y_min, Coord y_max, Coord z_min,
    Coord z_max, Id id)
  {
    subdomains_3d = true;
    // add check that we don't add subdomain more than once (id is unique)
    Box b(id);
    b.fll(x_min, y_min, z_min);
    b.flr(x_max, y_min, z_min);
    b.fur(x_max, y_max, z_min);
    b.ful(x_min, y_max, z_min);
    b.bll(x_min, y_min, z_max);
    b.blr(x_max, y_min, z_max);
    b.bur(x_max, y_max, z_max);
    b.bul(x_min, y_max, z_max);
    // compute bounding box and add to list of boxes
    b.bounding_box();
    b.vertex = add_vertex(udg);
    boxes.push_back(b);
  }

  template <typename Iter>
  Iter duplicates(Iter it, Iter end) {
    using std::distance;
    // inverse of std::unique, return iterator to first
    // element that is not a duplicate, i.e. duplicates
    // are in range [begin, returned iter), sorted list.
    Iter d_it = it;  // d_it is the insertion point
    for (; it != end;) {
      Iter tmp_it = it;
      while (it != end && *it == *tmp_it) ++it;
      if (1 < distance(tmp_it, it)) {
        *d_it = *tmp_it;
        ++d_it;
      }
    }
    return d_it;
  }

  void setup_and_solve() {
    using std::copy;
    using std::cout;
    using std::distance;
    using std::endl;
    using std::multimap;
    using std::ostream_iterator;
    using std::size_t;
    using std::sort;
    using std::vector;
    using boost::tie;
    using boost::vector_property_map;

    multimap<Coord, Id> x_mins, x_maxs, y_mins, y_maxs, z_mins, z_maxs;
    typedef typename multimap<Coord, Id>::value_type vt;

    // multi-stage algorithm: first coarse grain check if boxes can overlap
    // 2nd check: if boxes can overlap, fine grain (exact) check if they do

    // cout << "initialize for coarse search" << endl;

    // populate maps for fast coarse grained searches for overlapping boxes
    typename vector<Box>::iterator b_it = boxes.begin(), b_end = boxes.end();
    for (; b_it != b_end; ++b_it) {
      Box& b = *b_it;
      Id id = b.vertex;
      x_mins.insert(vt(b.x_min, id));
      x_maxs.insert(vt(b.x_max, id));
      y_mins.insert(vt(b.y_min, id));
      y_maxs.insert(vt(b.y_max, id));
      z_mins.insert(vt(b.z_min, id));
      z_maxs.insert(vt(b.z_max, id));
      // cout << b << endl;
      if (subdomains_3d) b.compute_face_normals();
    }

    // cout << "perform coarse and detailed search, populate overlap graph" << endl;

    // find possible overlapped subdomains by fast map search
    int i = 0;
    vector<Id> candidates, t_candidates;
    typename vector<Id>::iterator v_it, v_end;
    typename multimap<Coord, Id>::iterator m_it, n_it, m_end, n_end;
    for (b_it = boxes.begin(); b_it != b_end; ++b_it) {
      // clear candidate lists for next box
      candidates.clear();
      t_candidates.clear();

      Box& b = *b_it;
      Id id = b.vertex;

      // x axis, only keep duplicates (must be in both maps)
      m_it = x_mins.begin(), m_end = x_mins.lower_bound(b.x_max);
      n_it = x_maxs.upper_bound(b.x_min), n_end = x_maxs.end();
      candidates.resize(distance(m_it, m_end) + distance(n_it, n_end));
      for (i=0; m_it != m_end; ++m_it) {
        if (id != m_it->second)
          candidates[i++] = m_it->second;
      }
      for (; n_it != n_end; ++n_it) {
        if (id != n_it->second)
          candidates[i++] = n_it->second;
      }
      candidates.resize(i);
      sort(candidates.begin(), candidates.end());
      v_it = duplicates(candidates.begin(), candidates.end());
      candidates.erase(v_it, candidates.end());
      if (candidates.empty()) continue;  // no overlap possible

#if 0
      cout << "box id: " << id << " x candidates: ";
      copy(candidates.begin(), candidates.end(), ostream_iterator<Id>(cout, " "));
      cout << endl;
#endif

      // candidates holds all possible overlapping subdomains

      // y axis
      m_it = y_mins.begin(), m_end = y_mins.lower_bound(b.y_max);
      n_it = y_maxs.upper_bound(b.y_min), n_end = y_maxs.end();
      t_candidates.resize(distance(m_it, m_end) + distance(n_it, n_end) - 2);
      for (i=0; m_it != m_end; ++m_it) {
        if (id != m_it->second)
          t_candidates[i++] = m_it->second;
      }
      for (; n_it != n_end; ++n_it) {
        if (id != n_it->second)
          t_candidates[i++] = n_it->second;
      }
      t_candidates.resize(i);
      sort(t_candidates.begin(), t_candidates.end());
      v_it = duplicates(t_candidates.begin(), t_candidates.end());
      t_candidates.erase(v_it, t_candidates.end());
      if (t_candidates.empty()) continue;  // no overlap possible

#if 0
      cout << "box id: " << id << " y candidates: ";
      copy(t_candidates.begin(), t_candidates.end(), ostream_iterator<Id>(cout, " "));
      cout << endl;
#endif

      // combine into single list of candidates
      candidates.insert(candidates.end(), t_candidates.begin(), t_candidates.end());
      sort(candidates.begin(), candidates.end());
      v_it = duplicates(candidates.begin(), candidates.end());;
      candidates.erase(v_it, candidates.end());

      if (subdomains_3d) {
        // z axis
        m_it = z_mins.begin(), m_end = z_mins.lower_bound(b.z_max);
        n_it = z_maxs.upper_bound(b.z_min), n_end = z_maxs.end();
        t_candidates.resize(distance(m_it, m_end) + distance(n_it, n_end));
        for (i=0; m_it != m_end; ++m_it) {
          if (id != m_it->second)
            t_candidates[i++] = m_it->second;
        }
        for (; n_it != n_end; ++n_it) {
          if (id != n_it->second)
            t_candidates[i++] = n_it->second;
        }
        t_candidates.resize(i);

        sort(t_candidates.begin(), t_candidates.end());
        v_it = duplicates(t_candidates.begin(), t_candidates.end());
        t_candidates.erase(v_it, t_candidates.end());
        if (t_candidates.empty()) continue;  // no overlap possible
#if 0
      cout << "box id: " << id << " z candidates: ";
      copy(t_candidates.begin(), t_candidates.end(), ostream_iterator<Id>(cout, " "));
      cout << endl;
#endif


         // combine into single list of candidates
        candidates.insert(candidates.end(), t_candidates.begin(),
          t_candidates.end());
        sort(candidates.begin(), candidates.end());
        v_it = duplicates(candidates.begin(), candidates.end());
        candidates.erase(v_it, candidates.end());
      }

#if 0
      cout << "box id: " << id << " candidates: ";
      copy(candidates.begin(), candidates.end(), ostream_iterator<Id>(cout, " "));
      cout << endl;
#endif

      // candidates holds all possible overlapping subdomains
      v_it = candidates.begin();
      v_end = candidates.end();
      // compute once outside candidate loop
      if (subdomains_3d) {
        for (; v_it != v_end; ++v_it) {
          // candidate for overlap
          Box& c = boxes[*v_it];
          // check if any corner has all negative distance vectors from face
          // algorithm assume N is face normal vector on box
          // compute d = (ax + by + cz + d) for each candidate subdomain corner
          // if distance vector is negative for all 6 faces, then that corner is
          // inside box, add edge in overlap graph between box and subdomain
          // check if any subdomain corner has all negative face normal distances
          if (id < c.id && b.any_face_overlaps(c)) {
            // corner is inside box, add edge and check next candidate
            add_edge(id, c.vertex, udg);
            continue;
          }
        }
      }
      else {
        for (; v_it != v_end; ++v_it) {
          // candidate for overlap
          Box& c = boxes[*v_it];
          // find
          Point ll(c.fll), ur(c.fur);
          if (b.x_min <= ll.x && ur.x <= b.x_max &&
              b.y_min <= ll.y && ur.y <= b.y_max)
          {
            // box completely contains iterator, add edge
            if (id != c.vertex) add_edge(id, c.vertex, udg);
          }
          else if (ll.x <= b.x_min && b.x_max <= ur.x &&
                   ll.y <= b.y_min && b.y_max <= ur.y)
          {
            // box is completely inside iterator, add edge
            if (id != c.vertex) add_edge(id, c.vertex, udg);
          }
          else {
            // boxes might overlap, fine grained check
            Point lr(c.flr), ul(c.ful);
            Point bll(b.fll), blr(b.flr), bur(b.fur), bul(b.ful);
            bool overlap = false;
            // check if either horizontal segment intersects this box
            if (ll.y <= bll.y && bll.y <= ur.y) {
              overlap = intersect(bll, blr, ll, ul);
              if (!overlap) overlap = intersect(bll, blr, lr, ur);
            }
            if (!overlap && ll.y <= bur.y && bur.y <= ur.y) {
              overlap = intersect(bul, bur, ll, ul);
              if (!overlap) overlap = intersect(bul, bur, lr, ur);
            }
            // check if either vertical segment intersects this box
            if (!overlap && ll.x <= bll.x && bll.x <= ur.x) {
              overlap = intersect(bll, bul, ll, lr);
              if (!overlap) overlap = intersect(bll, bul, ul, ur);
            }
            if (!overlap && ll.x <= bur.x && bur.x <= ur.x) {
              overlap = intersect(blr, bur, ll, lr);
              if (!overlap) overlap = intersect(blr, bur, ul, ur);
            }
            if (overlap) {
              // u is new vertex id, *it is id of overlapping subdomain
              // add edge in graph between these two vertices
              if (id != c.vertex) add_edge(id, c.vertex, udg);
            }
          }
        }
      }
    }

    // cout << "compute coloring ordering using the overlap graph" << endl;

    // setup buckets and property maps for ordering algorithm
    const size_t N = num_vertices(udg);  // N is number of subdomains
    vector_property_map<size_t> order(N), marker(N), degree(N);
    degree_buckets<size_t, Vertex> dbs(degree);

    // run ordering algorithm on the overlap graph
    smallest_last_ordering(udg, order, degree, marker, dbs);
    // largest_first_ordering(udg, order, degree, marker, dbs);
    // cout << "color the smallest last vertex ordering" << endl;

    // run coloring algorithm on the ordering
    color.resize(N);
    n_colors = sequential_vertex_coloring(udg, order, color);
    // cout << "number colors: " << n_colors << endl;

    // populate groupings based on the color of each subdomain
    groups.clear();           // erase everything
    groups.resize(n_colors);  // resize for what we need
    for (size_t i=0; i<N; ++i) {
      groups[color[i]].push_back(boxes[i].id);
      // cout << "id: " << boxes[i].id << " color: " << color[i] << " order: " << order[i] << endl;
    }
  }

  std::size_t largest_group() {
    using std::max;
    using std::size_t;
    if (groups.empty()) return 0;
    grouping_t &g = groups;
    typename grouping_t::iterator g_it = g.begin(), g_end = g.end();
    size_t max_g = (*g_it).size();
    for (++g_it; g_it != g_end; ++g_it)
      max_g = max(max_g, (*g_it).size());
    return max_g;
  }

  void clear() {
    // empty the graph and other data structures
    // in preparation for the next set of boxes
    udg.clear();
    boxes.clear();
    groups.clear();
    // color.clear();
    n_colors = 0;
  }

  void output_histogram(std::ostream& out, unsigned int n_subdomains,
                        std::string s)
  {
    using std::count;
    using std::endl;
    using std::map;
    using std::sort;
    using std::vector;
    // copy coloring and sort
    map<int, int> histogram;
    vector<Id> coloring(&color[0], &color[num_vertices(udg)]);
    sort(coloring.begin(), coloring.end());
    typename vector<Id>::reverse_iterator r_it = coloring.rbegin(),
      r_end = coloring.rend();
    // get final groupings and output histogram
    for (; r_it != r_end;) {
      Id n = count(r_it, r_end, *r_it);
      ++histogram[n];
      r_it +=n;
    }

#if 1
    const size_t N = num_vertices(udg);  // N is number of subdomains
    for (size_t i=0; i<N; ++i) {
      out << "id: " << boxes[i].id << " color: " << color[i] << "\n";
    }
#endif

    out << "Processing " << n_subdomains << " " << s << " subdomains" << endl;
    out << "Histogram (# Subdomains in Group / # Groups of that size)" << endl;
    out << "Group Size / # of Groups" << endl;

    // output histogram
    map<int, int>::reverse_iterator h_it, h_end;
    h_it = histogram.rbegin();
    h_end = histogram.rend();
    for (; h_it != h_end; ++h_it) {
      out << "      " << (*h_it).first << "       " << (*h_it).second << endl;
    }

    out << "Total number of groups " << n_colors << endl;
    double avg = double(n_subdomains) / n_colors;
    out << "Avg. # subdomains per group = (" << n_subdomains
      << "/" << n_colors << ") = " << avg << endl;
  }
};

} // namespace DGM

#endif
