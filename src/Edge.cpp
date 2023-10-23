/** \file Edge.cpp
    \brief Edge implementation
    \author Scott Collis
*/

// system includes
#include <iostream>
#include <cstdio>
#include <math.h>

// boost includes
#ifdef DGM_USE_GENERAL_GHOSTING
#include <boost/serialization/vector.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/export.hpp>
#endif
using namespace std;

// DGM includes
#include "Edge.hpp"
#include "Utilities.hpp"
#include "Polylib.tpp"

#ifdef DGM_USE_GENERAL_GHOSTING
/// register class for serialization of polymorphic types
BOOST_CLASS_EXPORT_GUID(DGM::Edge, "DGM::Edge");
#endif

namespace DGM {

// default constructor
Edge::Edge() {
  // cout << "Edge::Edge() " << this << endl;
}

#ifdef DGM_USE_MD_COUPLE
// normal constructor
Edge::Edge(const Ordinal id_i, Element *e_i, const Ordinal nModes_i,
           const Ordinal q1_i, const Model::Type model)
  : Side( id_i, e_i, nModes_i, q1_i,0,model ),
    interpolate_from_side_to_subside(){
}
#else
// normal constructor
Edge::Edge(const Ordinal id_i, Element *e_i, const Ordinal nModes_i,
           const Ordinal q1_i, const bool GLL)
  : Side( id_i, e_i, nModes_i, q1_i, GLL ),
    interpolate_from_side_to_subside(){
}
#endif
// copy constructor
Edge::Edge( const Edge &ed) :
  Side(ed),
  interpolate_from_side_to_subside(ed.interpolate_from_side_to_subside) {
}

// copy constructor
Edge::Edge( const Edge *ed) : Side(ed),
    interpolate_from_side_to_subside(ed->interpolate_from_side_to_subside){
}

Side* Edge::deep_copy() const {
  Edge *e=new Edge(id(),elink,nModes(),q1(),Gauss_Lobatto());
  e->deep_copy_info(*this);
  e->interpolate_from_side_to_subside.
    resize(this->interpolate_from_side_to_subside);
  e->interpolate_from_side_to_subside=this->interpolate_from_side_to_subside;
  return e;
}

Edge& Edge::operator=(const Edge& ed){
  // cout << "Edge& operator=: "<<&ed <<" to "<<this<< endl;
  if (this == &ed) return *this;  // self-test
  Side::operator=(ed);
  interpolate_from_side_to_subside.resize(ed.interpolate_from_side_to_subside);
  interpolate_from_side_to_subside=ed.interpolate_from_side_to_subside;
  return *this;
}

// destructor
Edge::~Edge() {
  // cout << "~Edge " << this << endl;
}

/// Push values from sides to all subsides, interpolating as needed.
void Edge::push_to_subsides() {
  const vector<Side::Ptr> &ss = subsides();
  for (size_t s=0; s<ss.size(); ++s) ss[s]->push_to_subside(u);
}
/// Push values from vector to owned vector u.
/** It is assumed "this" is a subside. */
void Edge::push_to_subside(const dVector &s) {
  push_to_subside(s,u);
}

/// Push values from vector to owned vector u.
/** It is assumed "this" is a subside. */
void Edge::push_to_subside(const dVector &s, dVector &u) const {
  mvmult(interpolate_from_side_to_subside, s, u);
}

namespace {

// This is the core of a projection of subside coordinates onto side
// coordinates.  The input are real coordinates, the output is equivalent to
// parametric coordinates.  Works because the sides of a quad are just line
// segments.
pair<Scalar,Scalar> slope_intercept(const Point &p1,
                                    const Point &p2,
                                    const Point &p3,
                                    const Point &p4)
{
  /* maps (p1,p2) -> (p3,p4) as if p1=-1 and p2 = 1 */
  const Scalar  d =   distance_sq(p2,p1);
  const Scalar y1 = 2*((p2-p1)*(p3-p1))/d - 1;
  const Scalar y2 = 2*((p2-p1)*(p4-p1))/d - 1;
  const Scalar m  =  (y2-y1)/2;
  const Scalar b  =  (y2+y1)/2;
  pair<Scalar,Scalar> slope_int(m,b);
  return slope_int;
}

// project a point onto a line.
pair<Point,Point> project_to_line(const Point &p1,
                                  const Point &p2,
                                  const Point &p3,
                                  const Point &p4)
{
  const Point d = p2-p1;
  pair<Point,Point> r(d,d);
  {
    const Point   p = p3-p1;
    const Scalar  l = dot(d,p)/dot(d,d);
    r.first *= l;
  }{
    const Point   p = p4-p1;
    const Scalar  l = dot(d,p)/dot(d,d);
    r.second *= l;
  }
  r.first   += p1;
  r.second  += p1;
  return r;
}

// find the coordinates of a subside in a side and if that fails, try to
// project first and do it again.  Useful for periodic domains where the
// subside and side are not on the same periodic boundary.
pair<Scalar,Scalar> slope_intercept2(const Point &p1,
                                     const Point &p2,
                                     const Point &p3,
                                     const Point &p4)
{
  pair<Scalar,Scalar> si = slope_intercept(p1,p2,p3,p4);
  if (1<abs(si.first) || 1<abs(si.second)) {
    pair<Point,Point> p = project_to_line(p1,p2,p3,p4);
    si = slope_intercept(p1,p2,p.first,p.second);
    if (2<abs(si.first) || 2<abs(si.second)) {
      cerr << __FILE__<<":"<<__LINE__<<endl
           <<" p1:"<<p1<<endl
           <<" p2:"<<p2<<endl
           <<" p3:"<<p3<<endl
           <<" p4:"<<p4<<endl
           <<" p:" <<p.first <<endl
           <<" p:" <<p.second <<endl
           <<" si:"<<si.first<<" "<<si.second<<endl
           <<"Side::slope_intercept2 error" << endl;
      DGM::Comm::World->exit(-1);
    }
  }
  return si;
}

Scalar parametric_coord(const Point &p1,
                        const Point &p2,
                        const Point &p3)
{
  const Point d = p3-p2;
  const Scalar r = dot (p1-p2, d)/dot(d,d);
  return 2*r-1;
}

void make_interpolation_matrix_si(dMatrix &M,
                                  const Ordinal q1,
                                  const Ordinal q2,
                                  const Scalar slope,
                                  const Scalar intercept,
                                  const bool Gauss_Lobatto)
{
  M.resize(q1,q2);
  M = 0;
  dVector z1(q1), z2(q2), w1(q1), w2(q2);
  if (Gauss_Lobatto) zwgll(z2,w2);
  else               zwgl (z2,w2);
  if (Gauss_Lobatto) zwgll(z1,w1);
  else               zwgl (z1,w1);
  const Scalar m  =  slope;
  const Scalar b  =  intercept;
  for(Ordinal i=0; i<q1; ++i) z1[i] = m*z1[i] + b;
  if (Gauss_Lobatto) igllm(M,z2,z1);
  else               iglm (M,z2,z1);
}

}  // anonymous namespace

// create a matrix to project values from a side to a subside.  It is assumed
// that the subside is completely contained within the side so that no
// extrapolation is needed.
Scalar Edge::make_interpolation_matrix(const Ordinal q2,
                                       const Ordinal ,
                                       const vector<Point>&p1,
                                       const vector<Point>&p4)
{
  dMatrix &M = interpolate_from_side_to_subside;
  const Scalar a = parametric_coord(p4[0],p1[0],p1[1]);
  const Scalar b = parametric_coord(p4[1],p1[0],p1[1]);
  make_1d_interpolation_matrix(M,q1(),q2,a,b,Gauss_Lobatto());
  {
    dMatrix N;
    const pair<Scalar,Scalar> si = slope_intercept2(p1[0],p1[1],p4[0],p4[1]);
    make_interpolation_matrix_si
      (N,(unsigned)q1(),q2,si.first,si.second,Gauss_Lobatto());
    for (Ordinal i=0; i<q1(); ++i) {
      for (Ordinal j=0; j<q2; ++j) {
        if (.000001 < abs(M[i][j]-N[i][j])) {
          cerr <<__FILE__<<":"<<__LINE__
               <<" Edge::make_interpolation_matrix error:"
               <<abs(M[i][j]-N[i][j])
               << " (i,j):("<<i<<","<<j<<")"<<endl;
          for (Ordinal k=0; k<q1(); ++k) {
            for (Ordinal l=0; l<q2; ++l) {
              cout << "  M["<<k<<"]["<<l<<"]:"<<M[k][l]
                   << "  N["<<k<<"]["<<l<<"]:"<<N[k][l]<<endl;
            }
          }
          DGM::Comm::World->exit(-1);
        }
      }
    }
  }
  const Scalar J = abs(b-a)/2;
  return J;
}

void Edge::make_1d_interpolation_matrix(dMatrix &M,
                                        const Ordinal q1,
                                        const Ordinal q2,
                                        const Scalar a,
                                        const Scalar b,
                                        const bool Gauss_Lobatto)
{
  M.resize(q1,q2);
  M = 0;
  dVector z1(q1), z2(q2), w1(q1), w2(q2);

  if (Gauss_Lobatto) {
    zwgll(z2,w2);
    if (a==b) for(Ordinal i=0; i<q1; ++i) z1[i] = a;
    else {
      zwgll(z1,w1);
      for(Ordinal i=0; i<q1; ++i) z1[i] = a*(1-z1[i])/2 + b*(1+z1[i])/2;
    }
    igllm(M,z2,z1);
  } else {            
    zwgl (z2,w2);
    if (a==b) for(Ordinal i=0; i<q1; ++i) z1[i] = a;
    else {
      zwgl (z1,w1);
      for(Ordinal i=0; i<q1; ++i) z1[i] = a*(1-z1[i])/2 + b*(1+z1[i])/2;
    }
    iglm (M,z2,z1);
  }
}
#ifdef DGM_USE_GENERAL_GHOSTING
// test serialization
int DGM::Edge::test_serialization() {
  std::cout << "DGM::Edge::test_serialization: " << std::flush;

  // test element
  Element* ele = NULL;

  // create test data
  std::vector<DGM::Edge> edge;
  std::vector<DGM::Side*> side;
  Ordinal nEdges = 1; Ordinal Nmode = 2;
  edge.reserve(nEdges);
  for (Ordinal i=0; i<nEdges; i++) {
    Ordinal qedg = 2;
    edge.push_back(Edge(i+5,ele,Nmode,qedg,false));
    side.push_back( &(edge[i]) );

    edge[i].bc(true);
#ifndef DGM_CONTIGUOUS
    edge[i].u.resize(qedg);
    edge[i].u[0] = 0;
    edge[i].u[1] = 1;
#endif
    edge[i].nx().resize(qedg);
    edge[i].nx(0) = -1;
    edge[i].nx(1) = -1;
    edge[i].ny().resize(qedg);
    edge[i].ny(0) = 1;
    edge[i].ny(1) = 1;

    edge[i].J(0) = 0.4;
    edge[i].J(1) = 0.5;
  }

  // serialize
  std::ostringstream sendstream;
  {
    boost::archive::binary_oarchive oar(sendstream);
    oar << edge;
  }

  // dummy transfer: this could be a distributed memory data transfer
  std::string recvstring = sendstream.str();

  // deserialize
  std::vector<DGM::Edge> recv_edge;
  {
    std::istringstream recvstream(recvstring);
    boost::archive::binary_iarchive iar(recvstream);
    iar >> recv_edge;
  }

  // test size of vector
  int status = 0;
  if (nEdges != (Ordinal)recv_edge.size()) {
    cout << "nEdges != (Ordinal)recv_edge.size()" << endl;
    status = -1;
    cout << recv_edge.size() << endl;
    abort();
  }
  if (edge.size() != recv_edge.size()) {
    status = -1;
  }
  // test content
  for (std::size_t i=0; i != recv_edge.size();i++) {
    if (edge[i].id()  != recv_edge[i].id()  or
        edge[i].gid() != recv_edge[i].gid()) {
      status = -1;
    }
#ifndef DGM_CONTIGUOUS
    if (edge[i].u[1] != recv_edge[i].u[1])
    { status = -1; cout << "u not equal" << endl; }
#endif
    if (edge[i].nx(1) != recv_edge[i].nx(1))
    { status = -1; cout << "nx not equal" << endl; }
    if (edge[i].ny(1) != recv_edge[i].ny(1))
    { status = -1; cout << "ny not equal" << endl; }
    if (edge[i].J(1) != recv_edge[i].J(1))
    { status = -1; cout << "J not equal" << endl; }

    if (status != 0) {
      std::cout << edge[i] << std::endl;
      std::cout << recv_edge[i] << std::endl;
    }
  }
  if (status != 0)
    cout << "Test FAILED" << endl;
  else
    cout << "Test SUCCESS" << endl;
  return status;
}
#endif // #ifdef DGM_USE_GENERAL_GHOSTING

} // namespace DGM
