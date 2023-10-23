/** \file Face.cpp
    \brief DGM Face implementation
    \author Scott Collis
*/

// system includes
#include <iostream>
#include <cstdio>
#include <cmath>
#include <limits>
using namespace std;

// boost includes
#ifdef DGM_USE_GENERAL_GHOSTING
#include <boost/serialization/vector.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/export.hpp>
#endif

// DGM includes
#include "Comm.hpp"
#include "Face.hpp"
#include "Edge.hpp"
#include "Polylib.hpp"
#include "NodalTet.hpp"

#ifdef DGM_USE_GENERAL_GHOSTING
/// register class for serialization of polymorphic types
BOOST_CLASS_EXPORT_GUID(DGM::Face, "DGM::Face");
#endif

namespace DGM {

// Default constructor
Face::Face() : self_simular(true) { }

/// Normal constructor
Face::Face(const Ordinal id_i, Element *e_i, const Ordinal nModes_i,
           const Ordinal q1_i, const Ordinal q2_i, const bool GLL)
  : Side( id_i, e_i, nModes_i, q1_i, GLL, q2_i),
    interpolate_from_side_to_subside_x(),
    interpolate_from_side_to_subside_y(), self_simular(true), psi()
{
  // cout << "Face constructor " << this << endl;
}

// copy constructor
Face::Face( const Face &ed) : Side(ed),
    interpolate_from_side_to_subside_x(ed.interpolate_from_side_to_subside_x),
    interpolate_from_side_to_subside_y(ed.interpolate_from_side_to_subside_y),
    self_simular(true), psi()
{
  //  cout<<"Face& copy constructor: "<<&ed<<" to "<<this<<endl;
}

// copy constructor
Face::Face( const Face *ed) : Side(ed),
    interpolate_from_side_to_subside_x(ed->interpolate_from_side_to_subside_x),
    interpolate_from_side_to_subside_y(ed->interpolate_from_side_to_subside_y),
    self_simular(true), psi()
{
  //  cout<<"Face& copy constructor: "<<&ed<<" to "<<this<<endl;
}

Side* Face::deep_copy() const {
  Face *f = new Face(id(), elink, nModes(), q1(),q2(),Gauss_Lobatto());
  f->deep_copy_info(*this);
  f->interpolate_from_side_to_subside_x.
    resize(this->interpolate_from_side_to_subside_x);
  f->interpolate_from_side_to_subside_y.
    resize(this->interpolate_from_side_to_subside_y);
  f->interpolate_from_side_to_subside_x=
    this->interpolate_from_side_to_subside_x;
  f->interpolate_from_side_to_subside_y=
    this->interpolate_from_side_to_subside_y;
  f->self_simular= this->self_simular;
  f->psi= this->psi;
  return f;
}

Face& Face::operator=(const Face& ed) {
  // cout << "Face& operator=: "<<&ed <<" to "<<this<< endl;
  if (this == &ed) return *this;  // self-test
  Side::operator=(ed);
  interpolate_from_side_to_subside_x.
    resize(ed.interpolate_from_side_to_subside_x);
  interpolate_from_side_to_subside_y.
    resize(ed.interpolate_from_side_to_subside_y);
  interpolate_from_side_to_subside_x=ed.interpolate_from_side_to_subside_x;
  interpolate_from_side_to_subside_y=ed.interpolate_from_side_to_subside_y;
  self_simular=ed.self_simular;
  psi=ed.psi;
  return *this;
}

// destructor
Face::~Face() {}

// Push values from sides to all subsides, interpolating as needed.
void Face::push_to_subsides() {
  const vector<Side::Ptr> &ss = subsides();
  for (size_t s=0; s<ss.size(); ++s) ss[s]->push_to_subside(u);
}

// Push values from vector to owned vector u. It is assumed "this" is a subside.
void Face::push_to_subside(const dVector &owning_side) {
  push_to_subside(owning_side,u);
}

void Face::push_to_subside(const dVector &s, dVector &u) const {

  const dMatrix &X = interpolate_from_side_to_subside_x;
  const dMatrix &Y = interpolate_from_side_to_subside_y;
  dMatrix       T(   Y.rows(), X.cols());

  const dMatrix S(s, Y.cols(), X.cols());
  if (s.size() != S.rows()*S.cols())
    error("A Face::push_to_subside s, Y, X size mismatch");


  if (u.size() == T.rows() && 1 != T.cols()) {
    if (u.size() != X.rows())
      error("B Face::push_to_subside u, Y, X size mismatch");
    // Now, we are pushing from a quad to a triangle.  This is tricky.
    const Ordinal q1 = u.size();
    dMatrix R(S.rows(), S.cols());
    R = S;
    Ordinal N; for (N=0; N<100 && q1!=N*(N+1)/2; ++N);
    if (self_simular && N < R.rows() + R.cols()) {
      // filter higher order coefficients?
      const Ordinal L = R.cols();
      dVector z(L), w(L);
      dMatrix B(L, L);
      if (Gauss_Lobatto()) zwgll(z,w); 
      else                 zwgl (z,w);  // Gauss-Legendre points and weights
      Basis::make_Legendre( 0, L, L, z, B);
      for (Ordinal i=0; i<L; ++i) 
        for (Ordinal j=0; j<L; ++j) 
          R(i,j) *= w[i]*w[j];
      dMatrix W(L,L);
      matmult( B,      R, W); 
      matmult( W, 'T', B, R); 
      for (Ordinal i=0; i<L; ++i) 
        for (Ordinal j=0; j<L; ++j) 
          if (N<i+j) R(i,j) = 0;
      matmult( 'T', B, R, W); 
      matmult(  W,  B, R);
    }
    matmult(Y, R, T);
    for (Ordinal i=0; i<u.size(); ++i) 
       u[i] = dot(T.row(i), X.row(i));
  } else {
    dMatrix       U(u, Y.rows(), X.rows());
    if (u.size() != U.rows()*U.cols())
      error("C Face::push_to_subside u, Y, X size mismatch");

    matmult(Y,      S, T);
    matmult(T, 'T', X, U);
  }
}

void Face::push_to_subside_x(const dVector &s, dVector &u) const {
  mvmult(interpolate_from_side_to_subside_x, s, u);
}
void Face::push_to_subside_y(const dVector &s, dVector &u) const {
  mvmult(interpolate_from_side_to_subside_y, s, u);
}

namespace {

bool filter_for_constant_jac(vector<Point>       &L,
                             const vector<Point> &P,
                             const Size   geid,
                             const Ordinal  id) {
  // Only handle rectangular (self-simular) subsides....
  // but rotations are a pain...
  const Scalar EPSILON = .001;
  vector<Scalar> max(2,-numeric_limits<Scalar>::max());
  vector<Scalar> min(2, numeric_limits<Scalar>::max());

  // So, is P a rectangle?  That is what we would like it to be. If
  // it is then the corners are (min,min),(max,min),(max,max),(min,max)
  for (unsigned i=0; i<4; ++i) {
    for (unsigned j=0; j<2; ++j) {
      if (max[j] < P[i][j]) max[j] = P[i][j];
      if (P[i][j] < min[j]) min[j] = P[i][j];
    }
  }
  L.resize(2);
  L[0].x = min[0];
  L[0].y = min[1];
  L[1].x = max[0];
  L[1].y = max[1];

  bool self_simular = true;
  for (unsigned i=0; i<4 && self_simular; ++i) {
    for (unsigned j=0; j<2 && self_simular; ++j) {
      self_simular = max[j]-P[i][j]<EPSILON || P[i][j]-min[j]<EPSILON;
    }
  }
  return self_simular;
}

typedef vector<Scalar> V;
class M:public vector<V>{ public: M(const Ordinal r,
                                    const Ordinal c):vector<V>(r,V(c,0)){}};

class MM:public vector<M>{ public:MM(const Ordinal r,
                                     const Ordinal c,
                                     const Ordinal n):vector<M>(r,M(c,n)){}};
void shape_fcn_deriv(M &dNds, const V &param_coord);

Scalar inv_2x2(M &A_inv, const M A)
{
  const Scalar det = A[0][0] * A[1][1] - A[1][0] * A[0][1];
  const Scalar denom = 1/det;
  // inverse:
  A_inv[0][0] =  denom * A[1][1]; // dxidx
  A_inv[1][0] = -denom * A[1][0]; // detadx
  A_inv[0][1] = -denom * A[0][1]; // dxidy
  A_inv[1][1] =  denom * A[0][0]; // detady
  return det;
}

void ATA(M &ata, const M A)
{
  for (unsigned i=0; i<2; ++i)
    for (unsigned j=0; j<2; ++j)
      ata[i][j] = 0;
  for (unsigned i=0; i<2; ++i)
    for (unsigned j=0; j<2; ++j)
      for (unsigned k=0; k<3; ++k)
        ata[i][j] += A[k][i]*A[k][j];
}

void BAT(M &bat,
         const M B,
         const M A)
{
  for (unsigned i=0; i<2; ++i)
    for (unsigned j=0; j<3; ++j)
      bat[i][j] = 0;
  for (unsigned i=0; i<2; ++i)
    for (unsigned j=0; j<3; ++j)
      for (unsigned k=0; k<2; ++k)
        bat[i][j] += B[i][k]*A[j][k];
}

void DDXDS (MM &ddxds, const M &coord, const MM &ddNds)
{
  const size_t n = coord[0].size();
  for (unsigned k=0; k<n; ++k)
    for (unsigned i=0; i<2; ++i)
      for (unsigned j=0; j<2; ++j)
        ddxds[k][i][j] = 0;

  for (unsigned l=0; l<4; ++l)
    for (unsigned k=0; k<n; ++k)
      for (unsigned i=0; i<2; ++i)
        for (unsigned j=0; j<2; ++j)
          ddxds[k][i][j] += coord[l][k] * ddNds[l][i][j];
}

void shape_fcn(V &N, const V &pc)
{
  //shape function for each node evaluated at param_coords
  N[0] = 0.25 * (1.0 - pc[0]) * (1.0 - pc[1]);
  N[1] = 0.25 * (1.0 + pc[0]) * (1.0 - pc[1]);
  N[2] = 0.25 * (1.0 + pc[0]) * (1.0 + pc[1]);
  N[3] = 0.25 * (1.0 - pc[0]) * (1.0 + pc[1]);
}

void shape_fcn_deriv(M &dNds, const V &pc)
{
  dNds[0][0] = - 0.25 * (1.0 - pc[1]);
  dNds[0][1] = - 0.25 * (1.0 - pc[0]);

  dNds[1][0] =   0.25 * (1.0 - pc[1]);
  dNds[1][1] = - 0.25 * (1.0 + pc[0]);

  dNds[2][0] =   0.25 * (1.0 + pc[1]);
  dNds[2][1] =   0.25 * (1.0 + pc[0]);

  dNds[3][0] = - 0.25 * (1.0 + pc[1]);
  dNds[3][1] =   0.25 * (1.0 - pc[0]);
}

void shape_fcn_dderiv(MM &ddNds)
{
  ddNds[0][0][0] =      0 ;       ddNds[0][0][1] = + 0.25 ;
  ddNds[0][1][0] = + 0.25 ;       ddNds[0][1][1] =      0 ;

  ddNds[1][0][0] =      0 ;       ddNds[1][0][1] = - 0.25 ;
  ddNds[1][1][0] = - 0.25 ;       ddNds[1][1][1] =      0 ;

  ddNds[2][0][0] =      0 ;       ddNds[2][0][1] =   0.25 ;
  ddNds[2][1][0] =   0.25 ;       ddNds[2][1][1] =      0 ;

  ddNds[3][0][0] =      0 ;       ddNds[3][0][1] = - 0.25 ;
  ddNds[3][1][0] = - 0.25 ;       ddNds[3][1][1] =      0 ;
}

void DXDS (M &dxds, const M &coord, const M &dNds)
{
  const Ordinal n = numeric_cast<Ordinal>(coord[0].size());
  for (Ordinal i=0; i<n; ++i)
    for (Ordinal j=0; j<2; ++j)
      dxds[i][j] = 0;
  for (Ordinal k=0; k<4; ++k)
    for (Ordinal i=0; i<n; ++i)
      for (Ordinal j=0; j<2; ++j)
        dxds[i][j] += coord[k][i] * dNds[k][j];
}

bool DSDX_2(M       &dsdx,
            const M &coord,
            const M &dNds)
{
  M dxds(2,2);
  DXDS(dxds, coord, dNds);
  //    dxds = | dxdxi   dxdeta |
  //           | dydxi   dydeta |
  const Scalar det = inv_2x2(dsdx, dxds);
  //    dsdx = |  dxidx   dxidy  |
  //           | detadx  detady  |
  {
    M id(2,2);
    for (unsigned i=0; i<2; ++i)
      for (unsigned j=0; j<2; ++j)
        for (unsigned k=0; k<2; ++k)
          id[i][j] += dxds[i][k]*dsdx[k][j];
    vector<int> I(4);
    I[0]  =  (int)(.00001+id[0][0]);
    I[1]  =  (int)(.00001+id[1][1]);
    I[2]  =  (int)(1000000*id[0][1]);
    I[3]  =  (int)(1000000*id[1][0]);
    if (!I[0] || !I[1] || I[2] || I[3])
      cout << __FILE__<<":"<<__LINE__<<":"
          <<id[0][0]<<id[0][1]<<id[1][0]<<id[1][1]<<endl;
  }
  return (det < 1.0E-16);
}

bool DSDX_3(M       &dsdx,
            const M &coord,
            const M &dNds)
{
  M dxds   (3,2);
  M ata    (2,2);
  M ata_inv(2,2);
  DXDS(dxds, coord, dNds);
  //    dsdx = |  dxidx   dxidy   dxidz |
  //    dxds = | dxdxi   dxdeta |
  //           | dydxi   dydeta |
  //           | dzdxi   dzdeta |
  ATA(ata, dxds);
  const Scalar det = inv_2x2(ata_inv, ata);
  BAT(dsdx, ata_inv, dxds);
  //    dsdx = |  dxidx   dxidy   dxidz |
  //           | detadx  detady  detadz |
  {
    M id(2,2);
    for (unsigned i=0; i<2; ++i)
      for (unsigned j=0; j<2; ++j)
        for (unsigned k=0; k<3; ++k)
          id[i][j] += dsdx[i][k] * dxds[k][j];
    vector<int> I(4);
    I[0]  =  (int)(.00001+id[0][0]);
    I[1]  =  (int)(.00001+id[1][1]);
    I[2]  =  (int)(1000000*id[0][1]);
    I[3]  =  (int)(1000000*id[1][0]);
    if (!I[0] || !I[1] || I[2] || I[3])
      cout << __FILE__<<":"<<__LINE__<<":"
          <<id[0][0]<<" "<<id[0][1]<<" "<<id[1][0]<<" "<<id[1][1]<<endl;
  }
  return (det < 1.0E-16);
}

bool DSDX(M       &dsdx,
                    const M &coord,
                    const M &dNds)
{
  if (2 == coord[0].size())
    return DSDX_2(dsdx, coord, dNds);
  else
    return DSDX_3(dsdx, coord, dNds);
}

V fcn(const V &pc,
      const M &coords) {
  const Ordinal n = numeric_cast<Ordinal>(coords[0].size());
  V N(4,0);
  V g(n,0);
  shape_fcn(N,pc);
  for (Ordinal i=0; i<4; ++i) {
    for (Ordinal k=0; k<n; ++k) g[k] += N[i] * coords[i][k];
  }
  return g;
}

bool quad_nearest_parametric_coord(V &pc,
                                   const V &p,
                                   const M &coords)
{
  static const Ordinal  MAXIT = 20;
  static const Scalar TOL = 1.0E-14;
  const Ordinal n = numeric_cast<Ordinal>(coords[0].size());

  V    grad(2,0);
  V    ds(2,0);
  V     g(n);
  M  dNds(4,2);
  MM ddNds(4,2,2);
  M  dxds(n,2);
  MM ddxds(n,2,2);
  M  hess(2,2);
  M  hess_inv(2,2);

  /*-------------------------------------------------------------------------*/

  Scalar dist      = numeric_limits<Scalar>::max();
  Scalar prev_dist = 0;
  Scalar step      = numeric_limits<Scalar>::max();
  Ordinal iter = 0;

  while ( TOL*TOL < dist && TOL*TOL < step) {
    ++iter;

    dist = numeric_limits<Scalar>::max();
    Ordinal sub_iter = 0;
    while (prev_dist < dist && sub_iter < MAXIT) {
      ++sub_iter;
      shape_fcn_deriv  ( dNds, pc);
      DXDS             ( dxds, coords,  dNds) ;
      g         =   fcn(pc,    coords);

      for (Ordinal i=0; i<2; ++i) grad[i] = 0;
      for (Ordinal k=0; k<n; ++k)
        for (Ordinal i=0; i<2; ++i)
          grad[i] += (g[k]-p[k])*dxds[k][i];

      dist = 0.0;
      for (Ordinal i=0; i<2; ++i) dist += grad[i]*grad[i];
      if (prev_dist < dist) { //back off step length
        for (Ordinal j=0; j<2; ++j) ds[j] /= 2;
        for (Ordinal j=0; j<2; ++j) pc[j] += ds[j];
      }
    }
    if (MAXIT < iter) break;
    prev_dist = dist;

    shape_fcn_dderiv (ddNds);
    DDXDS            (ddxds, coords, ddNds) ;
    for (Ordinal i=0; i<2; ++i)
      for (Ordinal j=0; j<2; ++j) hess[i][j] = 0;

    for (Ordinal i=0; i<2; ++i)
      for (Ordinal j=0; j<2; ++j)
        for (Ordinal k=0; k<n; ++k)
          hess[i][j] += dxds[k][j]*dxds[k][i] + (g[k]-p[k])*ddxds[k][i][j];

    inv_2x2(hess_inv, hess);

    for (Ordinal j=0; j<2; ++j) ds[j] = 0;
    for (Ordinal i=0; i<2; ++i)
      for (Ordinal j=0; j<2; ++j) ds[i] += hess_inv[i][j]*grad[j];

    for (Ordinal j=0; j<2; ++j) pc[j] -= ds[j];
    step = ds[0]*ds[0] + ds[1]*ds[1];
  }
  return MAXIT==iter;
}

}  // anonymous namespace

bool Face::quad_parametric_coord_3d(Point &para,
                              const Point &P,
                              const vector<Point> &C) {
  static const unsigned  MAXIT = 20;
  static const Scalar TOL = 1.0E-14;
  const unsigned n = 3;

  if (C.size()!=4)
    error("quad_parametric_coord_3d:"
          " Wrong number of corner nodes for quad element.");

  M coords(4,3);
  const unsigned t[4]={0,1,3,2};
  for (unsigned i=0; i<4; ++i) {
    coords[i][0] = C[t[i]].x;
    coords[i][1] = C[t[i]].y;
    coords[i][2] = C[t[i]].z;
  }
  V    pc(3,0);
  V     p(3,0);
  p[0] = P.x; p[1] = P.y; p[2] = P.z;

  V    dx(n,0);
  V    ds(2,0);
  M  dNds(4,2);
  M  dsdx(2,n);

  /*-------------------------------------------------------------------------*/

  // Initial guess, center of element
  pc[0] = 0;
  pc[1] = 0;
  Scalar dist = numeric_limits<Scalar>::max();
  Scalar step = numeric_limits<Scalar>::max();
  unsigned iter = 0;

  while ( TOL*TOL < dist && iter < MAXIT && TOL*TOL < step) {
    ++iter;

    shape_fcn_deriv  (dNds, pc);
    DSDX   (dsdx, coords, dNds);
    const V g = fcn(pc,coords);

    dist = 0.0;
    for (unsigned j=0; j<n; ++j) dx[j] = g[j] - p[j];
    for (unsigned j=0; j<n; ++j) dist += dx[j]*dx[j];

    for (unsigned j=0; j<2; ++j) ds[j] = 0;
    for (unsigned i=0; i<2; ++i) {
      for (unsigned j=0; j<n; ++j) ds[i] += dsdx[i][j] * dx[j];
    }
    for (unsigned j=0; j<2; ++j) pc[j] -= ds[j];
    step = ds[0]*ds[0] + ds[1]*ds[1];
  }
  bool r = MAXIT==iter;
  if (r) r = quad_nearest_parametric_coord(pc,p,coords);
  para.x = pc[0];
  para.y = pc[1];
  return r;
}

namespace {
Scalar tri_area(const vector<Point> &V) {
  const Scalar a = V[0].distance(V[1]);
  const Scalar b = V[0].distance(V[2]);
  const Scalar c = V[1].distance(V[2]);
  const Scalar s = (a+b+c)/2;
  const Scalar A = std::sqrt(s*(s-a)*(s-b)*(s-c));
  return A;
}
Scalar quad_area(const vector<Point> &V) {
  vector<Point> T(3);
  T[0] = V[0]; T[1] = V[1]; T[2] = V[2];
  const Scalar t1 = tri_area(T);
  T[0] = V[1]; T[1] = V[2]; T[2] = V[3];
  const Scalar t2 = tri_area(T);
  return t1 + t2;
}
}

// create a matrix to project values from a side to
// a subside.  It is assumed that the subside is
// completely contained within the side so that
// no extrapolation is needed.
Scalar Face::make_interpolation_matrix(const Ordinal q1,
                                       const Ordinal q2,
                                       const vector<Point> &side_node,
                                       const vector<Point> &subside_node)
{
  if (side_node.size()!=4) {
    cerr<<"Face::make_interpolation_matrix: Input vector size error. A"<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }

  Scalar J;
  const Ordinal sq1=this->q1(), sq2=this->q2();
  dMatrix &Mx = interpolate_from_side_to_subside_x;
  dMatrix &My = interpolate_from_side_to_subside_y;

  if (sq1 != 1 && sq2 == 1) { // Triangle sub-face
    const Ordinal q = base ? base->q1() : link->q1();
    Ordinal N; for (N=0; N<100 && q!=(N+2)*(N+1)/2; ++N);
    if (q != (N+2)*(N+1)/2)
       throw DGM::exception("BaseHex::compute_subside_geometry internal error");
    vector<Point> Q(q);
    NodalTet::nodal_tet_quadrature(Q,subside_node,N);

    dMatrix X(1,q1), Y(1,q2);
    const bool GL=Gauss_Lobatto();
    Mx.resize(q, q1);
    My.resize(q, q2);
    for (Ordinal p=0; p<q; ++p) {
      Point P;
      quad_parametric_coord_3d(P, Q[p], side_node);
      Edge::make_1d_interpolation_matrix(X, 1, q1, P.x, P.x, GL);
      Edge::make_1d_interpolation_matrix(Y, 1, q2, P.y, P.y, GL);
      for (Ordinal i=0; i<q1; ++i) Mx(p,i) = X(0,i);
      for (Ordinal i=0; i<q2; ++i) My(p,i) = Y(0,i);
    }
    J = 1; 
  } else {
    if (subside_node.size()!=4) {
      cerr<<"Face::make_interpolation_matrix: Input vector size error. B"<<endl;
      DGM::Comm::World->exit(DGM::FAILURE);
    }
    vector<Point> P(4);
    for (unsigned i=0; i<4; ++i) 
      quad_parametric_coord_3d(P[i], subside_node[i], side_node);
    vector<Point> X(2);
    self_simular = filter_for_constant_jac(X, P, geid(), id());
    const bool GL=Gauss_Lobatto();
    if (self_simular) {
      Mx.resize(sq1, q1);
      My.resize(sq2, q2);
      Edge::make_1d_interpolation_matrix(Mx,sq1,q1,X[0].x,X[1].x,GL);
      Edge::make_1d_interpolation_matrix(My,sq2,q2,X[0].y,X[1].y,GL);
      Point L(X[1]); L-=X[0];
      J = std::abs(L.x*L.y)/4;
    } else {
      const Ordinal q = sq1*sq2;
      Mx.resize(q, q1);
      My.resize(q, q2);

      dVector z1(sq1), w1(sq1), z2(sq2), w2(sq2);
      if (GL) zwgll(z1, w1);
      else    zwgl (z1, w1);
      if (GL) zwgll(z2, w2);
      else    zwgl (z2, w2);

      dMatrix X(1,q1), Y(1,q2);
      const vector<Point> &C = subside_node;
      vector<Point> V(4);
      for (Ordinal p2=0, p=0; p2<sq2; ++p2) {
        for (Ordinal p1=0; p1<sq1; ++p1,++p) {
          const Scalar W[4] = {
            (1-z1[p1])*(1-z2[p2])/4,
            (1+z1[p1])*(1-z2[p2])/4,
            (1-z1[p1])*(1+z2[p2])/4,
            (1+z1[p1])*(1+z2[p2])/4};
          const Point Q
            (C[0].x*W[0] + C[1].x*W[1] + C[2].x*W[2] + C[3].x*W[3],
             C[0].y*W[0] + C[1].y*W[1] + C[2].y*W[2] + C[3].y*W[3],
             C[0].z*W[0] + C[1].z*W[1] + C[2].z*W[2] + C[3].z*W[3]);
          Point P;
          quad_parametric_coord_3d(P, Q, side_node);
          Edge::make_1d_interpolation_matrix(X, 1, q1, P.x, P.x, GL);
          Edge::make_1d_interpolation_matrix(Y, 1, q2, P.y, P.y, GL);
          for (Ordinal i=0; i<q1; ++i) Mx(p,i) = X(0,i);
          for (Ordinal i=0; i<q2; ++i) My(p,i) = Y(0,i);
          if (p1==0     && p2==0    ) V[0] = P;
          if (p1==0     && p2==sq2-1) V[1] = P;
          if (p1==sq1-1 && p2==0    ) V[2] = P;
          if (p1==sq1-1 && p2==sq2-1) V[3] = P;
        }
      }
      J = quad_area(V)/4;
    }
  }
  return J;
}

} // namespace DGM
