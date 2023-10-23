/** \file NodalTri.cpp
    \brief Nodal triangle Element implementation
    \author Scott Collis
    \author Mike Levy

    NodalTri is a three node triangular element that supports both affine
    mappings from the master element to the physical space element.
*/

// system includes
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

// boost includes
#include "boost/numeric/conversion/cast.hpp"
using boost::numeric_cast;

// DGM includes
#include "Comm.hpp"
#include "Types.hpp"
#include "NodalTri.hpp"
#include "Polylib.tpp"
#include "String.hpp"

namespace DGM {

namespace {

/// Map nodal triangle quadrature points from ref triangle to element
void nodal_tri_quadrature(Scalar Cx[], Scalar Cy[],
                          const vector<DGM::Vertex::Ptr> vert,
                          const Ordinal N) {
  const Ordinal Nmode = (N+2)*(N+1)/2;
  DGM::dVector r(Nmode), s(Nmode);
  DGM::zwntri(r, s, N);
  for(Ordinal m=0; m<Nmode; m++) {
    const Scalar l0 =  ( 1.0 + s[m])/2.0;
    const Scalar l1 = -(r[m] + s[m])/2.0;
    const Scalar l2 =  (r[m] +    1)/2.0;
    Cx[m] = l1*vert[0]->x + l2*vert[1]->x + l0*vert[2]->x;
    Cy[m] = l1*vert[0]->y + l2*vert[1]->y + l0*vert[2]->y;
  }
}

/** lift needs a fast way to determine if
    a quadrature node i is on the edge of an element of size
    qtot = qa*(qa+1)/2. direct_left/right_edge() computes this
    exactly, while is_on_edge() store information in a table.
    The table can be used for qa<=max_p, which is set below. Note that
    if qa>max_p, the direct methods will be used (so the run may be
    slower, but still correct).
*/

/// Largest polynomial order stored in table
static const Ordinal max_p=20;

Ordinal direct_left_edge(const Ordinal i, const Ordinal qa) {
  const Scalar left = (1.0+sqrt(4.0*qa*(qa+1.0)-8.0*i+1.0))*0.5;
  // if index i is on left edge, left will be an integer value
  return(left == int(left));
}

Ordinal direct_right_edge(const Ordinal i, const Ordinal qa) {
  const Scalar right = (1.0+sqrt(4.0*qa*(qa+1.0)-8.0*i-7.0))*0.5;
  // if index i is on right edge, right will be an integer value
  return(right == int(right));
}

Ordinal is_on_edge(const Ordinal i, const Ordinal qa) {
  if (qa>max_p)
    return( i<qa || direct_left_edge(i, qa) || direct_right_edge(i, qa) );

  static bool ioe_first_time=true;
  static std::vector< std::vector<int> > on_edge;

  if (ioe_first_time) {
    on_edge.resize(max_p);
    for(Ordinal p=0; p<max_p; p++) {
      on_edge[p].resize((p+1)*(p+2)/2);
      for(Ordinal ii=0, m=0; ii<=p; ii++)
        for(Ordinal jj=0; ii+jj<=p; jj++, m++)
          if ( ii==0 || jj==0 || ii+jj==p )
            on_edge[p][m] = 1;
          else
            on_edge[p][m] = 0;
      }
      ioe_first_time = false;
  }

  return(on_edge[qa-1][i]);
}

} // anonymous namespace

/// Use Gauss-Legendre quadrature instead of Gauss-Lobatto-Legendre
#define DGM_TRI_GAUSS_LEGENDRE

// define static storage

BasisDB NodalTri::bdb;                         // define Basis database
NodalTri::GeometryDB  NodalTri::gdb("NodalTri ");  // define Geom database
IMDB NodalTri::imdb;                           // define Interpolation database

Ordinal NodalTri::Qmax = 0;
Ordinal NodalTri::Lmax = 0;
dVector NodalTri::g1_wk;
dVector NodalTri::g2_wk;

dVector NodalTri::n1_wk;
dVector NodalTri::n2_wk;
dVector NodalTri::n3_wk;
dVector NodalTri::Lwk;

#ifdef DGM_USE_MD_COUPLE
/// Constructor
/*! \param[in] ID    - Local element id
    \param[in] P     - Polynomial order
    \param[in] X     - Vector of points defining the vertices
    \param[in] model - Model type */
NodalTri::NodalTri(const Size ID, const Ordinal P,
                   const vector<Point> &X, const Model::Type model)
#else
/// Constructor
/*! \param[in] ID    - Local element id
    \param[in] P     - Polynomial order
    \param[in] X     - Vector of points defining the vertices */
NodalTri::NodalTri(const Size ID, const Ordinal P, const vector<Point> &X)
#endif
: Element(ID) {
  //  cout << "NodalTri::NodalTri, eid = " << ID << endl;
  type   = Basis::Ortho;
  nVerts(3);
  nEdges(3);
  nFaces(1);
  nSides(3);
  pOrder(P);
  L(P+1);
  nModes(L()*(L()+1)/2);
#ifdef DGM_USE_MD_COUPLE
  modeltype = model;
#endif

  // Nodal triangles must use the same number of points in a and b
  qa = L(); qb = L(); qc = 0;
  qtot = nModes();

  make_workspace(qtot,nModes());

  // construct vertex data-structure
  vert.resize(nVerts());
  for (Ordinal i=0; i<nVerts(); i++){
    vert[i].reset( new Vertex(i,lid(),X[i]) );
  }

  set_box();

  // Form the basis functions
  psi = get_basis(0);

  // collocation derivative matrix
  get_derivative_matrix();

  // initial state is undefined
  state = Unallocated;

#ifndef DGM_CONTIGUOUS
  // storage for the nodal coefficients
  u.resize(qtot);
  // storage for the modal coefficients (aliased to nodal storage)
  uh.alias(u,nModes());
#endif

  // construct edge data-structure

  // The convergence analysis of Cockburn & Shu (JCP 141, p.203 1998) requires
  // that the edge integrals be exact for polynomials of order (2p+1).  Since
  // we use Gauss-Legendre quadrature which is exact for polynomials of order
  // (2q-1) we must use q=p+1.  But, since qa=p+2, we can also set qedg=qa-1.
  edge.reserve(nEdges());
  for (Ordinal i=0; i<nEdges(); i++) {
    const Ordinal qedg = pOrder()+1;
    //cout << "Element = " << gid() << "qedg = " << qedg << endl;
#ifdef DGM_USE_MD_COUPLE
    Edge ed(i,id,nModes(),qedg,modeltype);
#else
    Edge ed(i,this,nModes(),qedg,true);
#endif
    edge.push_back(ed);
    side.push_back( &(edge[i]) );
  }
}

/** \note This should not allocate new space for P, M, etc. */
NodalTri::NodalTri(const NodalTri *E) {
  // cout << "NodalTri copy constructor for Eid = " << E->gid() << endl;

  // allocate storage for solution at quadrature points
  u.resize(E->u.size());

  // allocate modal coefficients
  uh.alias(u,E->uh.size());

  *this = *E;  // only copies pointers -- be careful -- use shared_ptr

  // allocate storage for edges
  for (Ordinal i=0; i<nEdges(); i++) {
    // cout << "Edge = " << i << ", qtot = " <<  edge[i].qtot() << endl;
    edge[i].u.resize(edge[i].qtot());
    edge[i].u = 0.0;
    side[i] = &(edge[i]);
  }

  // initialize values
  state = Undefined;
  u = 0.0;
}

NodalTri::~NodalTri() {
  // cout << "~NodalTri: eid= "<<id<<endl;
}

Basis* NodalTri::get_basis(const int der=0) const {
  Basis* b;
  char buf[128];
  sprintf(buf,"%llu_%d_%llu_%llu_%llu",(long long unsigned)L(),der,
          (long long unsigned)qa,(long long unsigned)qb,(long long unsigned)qc);
  string key = buf;
  BasisDB::iterator p = bdb.bases.find(key);
  if ( p == bdb.bases.end() ) {
    b = new Basis(L(),qa,qb,qc,nModes(),nModes());
    make_basis(b,der);
    bdb.bases[key] = b;
  } else {
    b = p->second;
  }
  return b;
}

void NodalTri::make_basis(Basis *psi, const int der=0) {
  // cout << "NodalTri::make_basis" << endl;
  const Ordinal L = psi->L, nModes = psi->nModes, qa = psi->qa;

  dVector &zr = psi->znt_r, &zs = psi->znt_s;
  dVector &za = psi->za, &wa = psi->wa;

  psi->bnt = Basis::make_NodalTri(L, nModes, zr, zs);

  // setup modal access points
  psi->mode.resize(nModes);
  for(Ordinal m=0; m<nModes; m++) {
    psi->mode[m].nt.alias(psi->bnt[m]);
  }

  zwgll(za, wa);
  psi->ba = Basis::make_Legendre(0, L, qa, za);
  psi->Ba.alias( psi->ba[0].data(), L, qa); // unsafe
}

// Gets the mass matrix for NodalTri
/** \note This really computes the inverse mass matrix directly. */
void NodalTri::get_mass_matrix() {
  //  cout << "NodalTri::get_mass_matrix for element " << gid() << endl;
  M.reset( new Minfo );
  M->mat.resize(nModes(),nModes());
  M->pivots.resize(nModes());

  // build Vandermonde matrix
  dMatrix V(nModes(),nModes());
  dVector Vrow(nModes());
  for (Ordinal i=0; i<nModes(); i++) {
    fill( psi->mode[i], Vrow );
    for (Ordinal j=0; j<nModes(); j++) V[i][j] = Vrow[j];
  }
  matmult( V, 'T', V, M->mat );
  for (Ordinal i=0; i<nModes(); i++)
    for(Ordinal j=0; j<nModes(); j++)
      M->mat[i][j] /= geom->J[0]; // only works for constant Jacobian

  // Also build mass matrix with columns on edges only
  // (Used for sparse lift)
  Mbound.reset( new Minfo );
  Mbound->mat.resize(nModes(),3*(qa-1));
  Ordinal j2=0;
  for(Ordinal i=0; i<qtot; i++)
    if (is_on_edge(i,qa)) {
      for(Ordinal k=0; k<qtot; k++)
        Mbound->mat[k][j2] = M->mat[k][i];
      j2++;
    }
}

// Resets the mass matrixing using a weighted mass matrix
/** \warning Might be dangerous to reset the mass matrix to this new value. */
void NodalTri::get_mass_matrix(const dVector &x) {
  cout << "NodalTri::get_mass_matrix(x) for element " << gid() << endl;
  DGM_UNDEFINED; // Just like NodalQuad
  M.reset( new Minfo );
  M->mat.resize(nModes(),nModes());
  M->pivots.resize(nModes());
  dVector f(qtot);
  dVector fh(f,nModes());
  for (Ordinal m=0; m<nModes(); m++) {
    fill( psi->mode[m], f );
    dvmul( x, f );
    inner_product(f, fh);
    for (Ordinal n=0; n<nModes(); n++) M->mat[m][n] = fh[n];
  }
#ifdef DGM_CHOLESKY_MASS_MATRIX
  if (Cholesky_factor(M->mat) !=0)
    DGM::Comm::
      World->error("NodalTri:get_mass_matrix(x):  Cholesky_factor() failed.");
#else
  if (LU_factor(M->mat, M->pivots) !=0)
    DGM::Comm::World->error("NodalTri:get_mass_matrix(x):  "
                            "LU_factor() failed.");
#endif
  full_mass = true;
}

void NodalTri::solve_mass_matrix(dVector &fh) const {
  DGM_UNDEFINED;
  if (curve.get() || full_mass) {
#ifdef DGM_CHOLESKY_MASS_MATRIX
    Cholesky_solve(M->mat, fh);
#else
    LU_solve(M->mat, M->pivots, fh);
#endif
  } else {
    for (Ordinal i=0; i<nModes(); i++) fh[i] *= M->mat[0][i];
  }
}

//=============================================================================

//=============================================================================

/// fill element with a function string
void NodalTri::fill(string function_string, Operation operation) {
  state = Physical;
  parser_init();
  Parser::VectorFunction f("x", "y", "t", function_string );
  f.evaluate( C->x, C->y, u, 0.0, convert(operation) );
  state = Physical;
}

/// fill element with a mode
void NodalTri::fill(Mode &v) {
  DGM_UNDEFINED;
  // cout << "NodalTri::fill(Mode &)" << endl;
  dMatrix U(u,qa,qb);
  for (Ordinal i=0; i<qa; i++)
    for (Ordinal j=0; j<qb; j++)
      U[i][j] = v.a[i] * v.b[j];
  state = Physical;
}

/// fill a vector with a mode
void NodalTri::fill(Mode &v, dVector &f) const {
  // cout << "NodalTri::fill(Mode &, dVector &)" << endl;
  for(Ordinal m=0; m<nModes(); m++) f[m] = v.nt[m];
}

/// Fill element with a random polynomial
void NodalTri::random() {
  // cout << "NodalTri::random()" << endl;
  state = Physical;
  for (Ordinal i=0; i<nModes(); i++) uh[i] = Element::random(-one,one);
}

void NodalTri::set(const dVector &fh, const Ordinal nModes2) {
  //cout << "NodalTri::set(const dVector &, const int)" << endl;
  Ordinal L2 = static_cast<Ordinal>((sqrt(1.0+8.0*nModes2)-1.0)/2.0);
  Ordinal Lm = min(L(),L2);
  dVector Uh, Fh;
  for (Ordinal i=0, m=0, m2=0; i<Lm; i++) {
    Uh.alias( uh, m, L()-i );
    Fh.alias( fh, m2, L2-i );
    for (Ordinal j=0; j<Lm-i; j++) Uh[j] = Fh[j];
    m += L()-i;
    m2 += L2-i;
  }
  state = Transform;
  //cout<<"Eid = "<<id<<", |mode(nModes())| = "<<fabs(uh(nModes()-1))<<endl;
}

void NodalTri::inner_product() {
  DGM_UNDEFINED;
  // cout << "NodalTri::inner_product() for Eid = " << gid() << endl;
  dMatrix WK(Lwk,L(),qb);
  dMatrix U(u,qa,qb);
#ifdef DGM_USE_WJ
  const dVector &wJ = geom->wJ;
  dvmul( wJ, u );
  matmult( psi->Ba, U, WK);          // wk[La][qb] = Ba[La][qa] * U[qa][qb]
  dVector Uh, wk;
  int mode = 0;
  for (Ordinal i = 0; i < L(); ++i) {
    Uh.alias( uh, mode, L()-i );
    wk.alias( Lwk, i*qb, qb );
    mvmult( psi->bb[i], wk, Uh );
    mode += L()-i;
  }
#else
  const dVector &wb = psi->wb;
  const dVector &wa = psi->wa;
  const dVector &J = geom->J;
  if (curve.get())
    dvmul( J, u );
  else
    scale( J[0], u );

  for(Ordinal j=0; j<qb; j++) {
    dSlice column(U.column(j));
    dvmul( wa, column );
  }
  //  for(Ordinal i=0; i<qa; i++) dvmul( wb, U.row(i) );  // more expensive
  matmult( psi->Ba, U, WK);

  dVector Uh, wk;
  int mode = 0;
  for (Ordinal i = 0; i < L(); ++i){
    Uh.alias( uh, mode, L()-i );
    wk.alias( Lwk, i*qb, qb );
    dvmul( wb, wk );                                  // less expensive
    mvmult( psi->bb[i], wk, Uh );
    mode += L()-i;
  }
#endif
  state = Transform;
}

void NodalTri::inner_product(dVector &f, dVector &fh) const {
  DGM_UNDEFINED;
  //  cout<<"NodalTri::inner_product(dVector&, dVector&) for Eid = "<<id<<endl;
  dMatrix WK(Lwk,L(),qb);
  dMatrix F(f,qa,qb);
#ifdef DGM_USE_WJ
  const dVector &wJ = geom->wJ;
  dvmul( wJ, f );
#else
  const dVector &wa = psi->wa;
  const dVector &wb = psi->wb;

  if (curve.get())
    dvmul( geom->J, f );
  else
    scale( geom->J[0], f );

  for(Ordinal j=0; j<qb; j++) {
    dSlice column(F.column(j));
    dvmul( wa, column );
  }
  //  for(Ordinal i=0; i<qa; i++) dvmul( wb, F.row(i) );  // more expensive
#endif

  matmult( psi->Ba, F, WK);

  dVector Fh, wk;
  int mode = 0;
  for (Ordinal i = 0; i < L(); ++i){
    Fh.alias( fh, mode, L()-i );
    wk.alias( Lwk, i*qb, qb );
#ifndef DGM_USE_WJ
    dvmul( wb, wk );                                  // less expensive
#endif
    mvmult( psi->bb[i], wk, Fh );
    mode += L()-i;
  }
}

void NodalTri::forward_transform() {
  // cout << "NodalTri::forward_transform()" << endl;
  if (state == Transform) {
    cerr << "NodalTri::transform -- already in transform space"<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  forward_transform(u,uh);
  state = Transform;
}

void NodalTri::forward_transform(dVector &f, dVector &fh) const {
  //cout << "NodalTri::forward_transform(f,fh)" << endl;
  assert(qtot==nModes());
  // Need to make a local copy of f so that mvmult doesn't break
  dVector floc(nModes());
  floc = f;
  mvmult(Viloc->mat, floc, fh);
}

void NodalTri::forward_transform(Element *F, Element *) {
  DGM_UNDEFINED;
  //cout << "NodalTri::forward_transform(*F,*)" << endl;
  if (state == Transform) {
    cerr << "NodalTri::transform -- already in transform space"<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  inner_product(u,uh);
  F->solve_mass_matrix(uh);  // Use element F's Mass matrix
  state = Transform;
}

void NodalTri::backward_transform() {
  if (state == Physical) {
    cerr<<"NodalTri::transform_to_physical -- already in physical space"<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  backward_transform(uh, u);
  state = Physical;
}

void NodalTri::backward_transform(dVector &fh, dVector &f) const {
  //cout << "NodalTri::backward_transform(fh,f)" << endl;
  Minfo V;
  assert(qtot==nModes());
  V.mat.resize(nModes(),qtot); // build Vandermonde matrix
  dVector Vrow(qtot);
  for (Ordinal i=0; i<nModes(); i++) {
    fill( psi->mode[i], Vrow );
    for (Ordinal j=0; j<qtot; j++) V.mat[i][j] = Vrow[j];
  }
  dVector wk(Lwk,qtot);      // Needed for case that fh is alias of f
  wk = fh;
  mvmult(V.mat,wk,f);        // f[qtot] = V[qtot][nModes()] * fh[nModes()]
}

void NodalTri::get_side(const dVector &from, const Ordinal edge,
                        dVector &to) const {
  // cout<<"NodalTri::get_side() Element = "<<id<<" Edge = "<<edge<<endl<<to<<endl;
  Ordinal i;
  if (state == Transform) {
    cerr << "NodalTri::get_side -- must be in physical space"<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  switch(edge) {
  case 0:
    // bottom of triangle is first qa nodes
    for (i=0; i<qa; i++) to[i] = from[i];
    break;
  case 1:
    // Right edge (Start at qa-1, add qa-1, then qa-2, ..., then 1)
    for (i=0; i<qa; i++) to[i] = from[(qa-1)*(i+1) - i*(i-1)/2];
    break;
  case 2:
    // Left edge (Start at 0, add qa, then qa-1, ..., then 2)
    for (i=0; i<qa; i++) to[i] = from[qa*i - i*(i-1)/2];
    break;
  default:
    cerr << "NodalTri::get_side -- unknown edge" << endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
}

// Interpolation matrix
void NodalTri::make_interpolation_matrix( const Ordinal q1, const Ordinal q2,
                                          const Interp::Type interp,
                                          dMatrix &im ) {
  //  cout << "NodalTri::make_interpolation_matrix" << endl;
  im.resize(q1,q2);
  dVector z1(q1), z2(q2), w1(q1), w2(q2);
  Scalar delta;
  switch(interp){
  case(Interp::GL2G):
    zwgll(z2,w2);               // Gauss-Lobatto-Legendre
    zwgl (z1,w1);               // Gauss-Legendre
    igllm(im,z2,z1);            // Interpolation matrix
    break;
  case(Interp::G2GL):
    zwgl (z2,w2);               // Gauss-Legendre
    zwgll(z1,w1);               // Gauss-Lobatto-Legendre
    iglm(im,z2,z1);             // Interpolation matrix
    break;
  case(Interp::GL2U):
    zwgll(z2,w2);
    delta=two/(Scalar)(q1);
    for(Ordinal i=0; i<q1; ++i) z1[i] = i*delta - one + pt5*delta;
    igllm(im,z2,z1);
    break;
  case(Interp::GRJ2G):
#ifdef DGM_TRI_GAUSS_LEGENDRE
    zwgrj(z2,w2,0.0,0.0);       // Gauss-Radau-Jacobi
    zwgl (z1,w1);               // Gauss-Legendre
    igrjm(im,z2,z1,0.0,0.0);    // Interpolation matrix
#else
    zwgrj(z2,w2,1.0,0.0);       // Gauss-Radau-Jacobi
    zwgl (z1,w1);               // Gauss-Lobatto-Legendre
    igrjm(im,z2,z1,1.0,0.0);    // Interpolation matrix
#endif
    break;
  case(Interp::G2GRJ):
#ifdef DGM_TRI_GAUSS_LEGENDRE
    zwgl (z2,w2);               // Gauss-Legendre
    zwgrj(z1,w1,0.0,0.0);       // Gauss-Radau-Jacobi
    igjm(im,z2,z1,0.0,0.0);     // Interpolation matrix
#else
    zwgl (z2,w2);               // Gauss-Lobatto-Legendre
    zwgrj(z1,w1,1.0,0.0);       // Gauss-Radau-Jacobi
    iglm(im,z2,z1);             // Interpolation matrix
#endif
    break;
  case(Interp::GRJ2U):
#ifdef DGM_TRI_GAUSS_LEGENDRE
    zwgrj(z2,w2,0.0,0.0);       // Gauss-Radau-Jacobi
    delta=two/(Scalar)(q1);
    for(Ordinal i=0; i<q1; ++i) z1[i] = i*delta - one + pt5*delta;
    igrjm(im,z2,z1,0.0,0.0);    // Interpolation matrix
#else
    zwgrj(z2,w2,1.0,0.0);       // Gauss-Radau-Jacobi
    delta=two/(Scalar)(q1);
    for(Ordinal i=0; i<q1; ++i) z1[i] = i*delta - one + pt5*delta;
    igrjm(im,z2,z1,1.0,0.0);    // Interpolation matrix
#endif
    break;
  default:
    cerr << "NodalTri::make_interpolation_matrix - Invalid interpolation type"
    << endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
}

dMatrix* NodalTri::get_interpolation_matrix( const Ordinal q1, const Ordinal q2,
                                             const Interp::Type interp=
                                             Interp::GL2G) {
  dMatrix* im;
  IMinfo key(interp,q1,q2);
  IMDB::iterator p = imdb.entry.find(key);
  if ( p == imdb.entry.end() ) {            // not found, make a new one
    im = new dMatrix;
    make_interpolation_matrix(q1,q2,interp,*im);
    imdb.entry[key] = im;
  } else {                                  // found, return the basis
    im = p->second;
  }
  return im;
}

// Fill physical space values "f" in the side GLL points.
void NodalTri::fill_sides(const dVector &f) {
  for(Ordinal sid=0; sid<3; sid++) {
    get_side(f,sid,edge[sid].u);
  }
}

// Interpolate physical space values "f" to a uniform mesh on the sides.
void NodalTri::fill_sides_uniform(const dVector &f) {
  dVector wk(g1_wk,pOrder()+1);
  dMatrix *im;
  for(Ordinal sid=0; sid<3; sid++) {
    im = get_interpolation_matrix( edge[sid].qtot(), pOrder()+1, Interp::GL2U);
    get_side(f,sid,wk);
    mvmult( *im, wk, edge[sid].u );
  }
}

// flux version
void NodalTri::fill_sides(const dVector &fx, const dVector &fy) {
  dVector wka(g1_wk,pOrder()+1);
  for(Ordinal sid=0; sid<3; sid++) {
    get_side(fx,sid,edge[sid].u);
    dvmul( edge[sid].nx(), edge[sid].u );
    get_side(fy,sid,wka);
    dvvtvp( edge[sid].ny(), wka, edge[sid].u, edge[sid].u );
  }
}

// Interpolate physical space values "f" to the edge Gauss points.  But store
// the result in vector g
void NodalTri::load_side(const dVector &f, const Ordinal side_number,
                         dVector &g) const {
  DGM_UNDEFINED;
  dVector wk(g1_wk,pOrder()+1);
  dMatrix *im;
  im = get_interpolation_matrix( edge[side_number].qtot(), pOrder()+1,
                                 Interp::GL2G);
  get_side(f,side_number,wk);
  mvmult( *im, wk, g );
}

// compute coordinates of quadrature points
void NodalTri::get_coordinates() {
  if (curve.get())
    get_curved_coordinates();
  else
    get_straight_coordinates();
}

void NodalTri::get_straight_coordinates() {
  // cout << "NodalTri::get_straight_coordinates for element "<<gid()<<endl;
  C.reset( new Coord(qtot) );
  *C = 0;
  nodal_tri_quadrature(C->x.ptr(), C->y.ptr(), vert, pOrder());
}

void NodalTri::J_backward_transform(dVector &fh, dVector &f) {
  cout << "NodalTri::J_backward_transform for elmt = " << gid() << endl;
  DGM::Comm::World->error("Curved elements not supported in NodalTri");
}

void NodalTri::get_curved_coordinates() {
  DGM::Comm::World->error("Curved elements not supported in NodalTri");
}

void NodalTri::get_side_coordinates(const Ordinal nedge, Point *pedge)const {
  DGM_UNDEFINED;
  dVector wka, px, py;
  dMatrix *im;
  px.resize(edge[nedge].qtot());
  py.resize(edge[nedge].qtot());
  Ordinal q;
  switch(nedge) {
  case 0:
    q = qa;
    im = get_interpolation_matrix( edge[nedge].qtot(),q,Interp::GL2G);//to,from
    wka.resize(q);
    get_side(C->x,nedge,wka);
    mvmult( *im, wka, px);
    get_side(C->y,nedge,wka);
    mvmult( *im, wka, py);
    for(Ordinal i=0; i<edge[nedge].qtot(); i++) pedge[i] = Point(px[i],py[i]);
    break;
  case 1: case 2:
    q = qb;
    im = get_interpolation_matrix( edge[nedge].qtot(),q,Interp::GRJ2G);//to,from
    wka.resize(q);
    get_side(C->x,nedge,wka);
    mvmult( *im, wka, px);
    get_side(C->y,nedge,wka);
    mvmult( *im, wka, py);
    for(Ordinal i=0; i<edge[nedge].qtot(); i++) pedge[i] = Point(px[i],py[i]);
    break;
  default:
    cerr << "NodalTri::compute_side_coordinates illegal edge id." << endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
}

void NodalTri::compute_geometry() {
  //cout << "NodalTri::compute_geometry for element " << gid() << endl;
  // if (geom) delete geom;
  // geom = new Geometry( id, 2, nVerts(), qtot );
  geom.reset( new Geometry( lid(), 2, nVerts(), qtot ) );
  if (curve.get())
    compute_curved_geometry();
  else
    compute_straight_geometry();
  measure(compute_measure());   // area
#ifdef DGM_USE_GEOM_DB
  gdb.add(geom);
#endif
}

void NodalTri::compute_straight_geometry() {
  // cout<<"NodalTri::compute_straight_geometry for element "<<gid()<<endl;

  // compute coordinate gradients in mapped space
  Scalar xr = (vert[1]->x - vert[0]->x)/2.0;
  Scalar xs = (vert[2]->x - vert[0]->x)/2.0;
  Scalar yr = (vert[1]->y - vert[0]->y)/2.0;
  Scalar ys = (vert[2]->y - vert[0]->y)/2.0;

  // compute determinate of the Jacobian
  Scalar detJ = xr*ys - xs*yr;
  if(detJ <= 0.0) {
    cerr << "Element " << gid() <<" has a nonpositive Jacobian = "
         << detJ << endl;
    detJ = fabs(detJ);
  }
  geom->J = detJ;

  geom->rx =  ys / detJ;
  geom->ry = -xs / detJ;
  geom->sx = -yr / detJ;
  geom->sy =  xr / detJ;

#ifdef DGM_STORE_METRICS
  // Compute metrics for CFL and timestep size (stability) estimates.
  compute_metrics();
#endif
}

void NodalTri::compute_curved_geometry() {
  DGM_UNDEFINED;
#if 0
  // cout << "NodalTri::compute_curved_geometry for element " << gid()<<endl;
  for (Ordinal i=1; i<nVerts(); i++) {
    geom->dx[i-1] = vert[i]->x - vert[0]->x;
    geom->dy[i-1] = vert[i]->y - vert[0]->y;
  }

  // temporary storage
  dVector xr(qtot), xs(qtot);
  dVector yr(qtot), ys(qtot);

  // compute coordinate gradients in mapped space
  local_gradient( C->x, xr, xs );
  local_gradient( C->y, yr, ys );

  // compute determinate of the Jacobian
  dvmul( xs, yr, geom->J );
  scale( -1.0, geom->J );
  dvvtvp( xr, ys, geom->J, geom->J);

  for (Ordinal i=0; i<qtot; i++) {
    if(geom->J[i] <= 0.0) {
      cerr << "Element " << gid() <<" has a nonpositive Jacobian" << endl;
      geom->J[i] = fabs(geom->J[i]);
    }
  }

  dvdiv( ys, geom->J, geom->rx);
  dvdiv( xs, geom->J, geom->ry);
  dvdiv( yr, geom->J, geom->sx);
  dvdiv( xr, geom->J, geom->sy);

  scale( -1.0, geom->ry );
  scale( -1.0, geom->sx );

#ifdef DGM_USE_WJ
  const dVector &wa = psi->wa;
  const dVector &wb = psi->wb;
  dVector &b =  geom->wJ;
  dMatrix B(b,qa,qb);

  b = geom->J ;  // load in the Jacobian

  // apply integration weights
  for(Ordinal j=0; j<qb; j++) {
    dSlice column(B.column(j));
    dvmul( wa, column );
  }
  for(Ordinal i=0; i<qa; i++) {
    dVector row(B.row(i));
    dvmul( wb, row);
  }
  dvsqrt( b, geom->srwJ );
  geom->isrwJ = one;
  dvdiv( geom->srwJ, geom->isrwJ );
#endif

#ifdef DGM_STORE_METRICS
  // Compute metrics for CFL and timestep size (stability) estimates.
  compute_metrics();
#endif

#endif
}

/// Compute the stability metrics for timestep size calucations.
Element::StabMetrics NodalTri::compute_metrics() {
  return compute_metrics_nodal_tri();
}

void NodalTri::compute_side_geometry() {
  //  cout << "NodalTri::compute_side_geometry(), Eid = "<< gid() << endl;
  sigma(0.0);
  for (Ordinal i=0; i<nEdges(); i++) {
    Edge &e = edge[i];
    Ordinal qedg = e.qtot();
    Ordinal q = pOrder()+1;
    dMatrix &Der = D->Da;
    dVector wk(q);

    switch(i) {
    case 0:
      get_side(geom->sx,i,edge[i].nx()); // wk is at Gauss-Lobatto points
      scale( -1.0, edge[i].nx() );       // negate since on bottom
      get_side(geom->sy,i,edge[i].ny());
      scale( -1.0, edge[i].ny() );
      break;
    case 1:
      get_side(geom->rx,i,edge[i].nx());
      get_side(geom->sx,i,wk);
      dvadd(wk,edge[i].nx());
      get_side(geom->ry,i,edge[i].ny());
      get_side(geom->sy,i,wk);
      dvadd(wk,edge[i].ny());
      break;
    case 2:
      get_side(geom->rx,i,edge[i].nx());
      scale( -1.0, edge[i].nx() );       // negate since on left
      get_side(geom->ry,i,edge[i].ny());
      scale( -1.0, edge[i].ny() );
      break;
    }

    dVector interior_J(qedg);
    get_side(geom->J,i,interior_J);    // interpolate interior J to edge

    // make normals have unit length
    for (Ordinal j=0; j<qedg; j++) {
      Scalar len = sqrt( edge[i].nx(j)*edge[i].nx(j) +
          edge[i].ny(j)*edge[i].ny(j) );
      edge[i].nx(j) /= len;
      edge[i].ny(j) /= len;
#if 0
      cout << "Element = " << gid() << ", edge = " << i << ", q = " << j
           << ", (nx,ny) = " << edge[i].nx(j) << ", " << edge[i].ny(j)
           << ", int_J = " << interior_J[j] << endl;
#endif
    }

    // get coordinates along the edge  (Gauss-Lobatto)
    dVector x(q);
    dVector y(q);
    get_side(C->x,i,wk);
    mvmult( Der, wk, x );
    get_side(C->y,i,wk);
    mvmult( Der, wk, y );
    dvmul( x, x, x);           // x = x^2
    dvvtvp( y, y, x, x );      // x = x^2 + y^2
    dvsqrt( x, edge[i].J() );  // edge.J = sqrt(x)

    // store the max ratio of side to element Jacobians
    for (Ordinal k=0; k<qedg; ++k)
      sigma(max(sigma(), fabs( edge[i].J(k) ) ));

    // compute and store the Edge measure for each Side
    dVector p(qedg); p = one;
    e.measure(compute_side_integral(p,i));
  }
}

void NodalTri::forward_transform_side(dVector &f, dVector &fh) {
  DGM_UNDEFINED;
}

void NodalTri::solve_1d_mass_matrix(dVector &fh) const {
  DGM_UNDEFINED;
}

void NodalTri::get_1d_mass_matrix(Minfo &M1d) const {
  DGM_UNDEFINED;
}

Scalar NodalTri::compute_side_integral( dVector &f, Ordinal sid ) const {
  const Ordinal qsid = this->side[sid]->qtot();

  dVector z(qsid), w(qsid);
  zwgl(z,w);                 // Gauss-Legendre

  dvmul( side[sid]->J(), f);

  dMatrix *im;
  im = get_interpolation_matrix( qsid, qa, Interp::GL2G );   // to, from
  dVector wk(qa);

  dVector interior_J(qsid);
  get_side(geom->J,sid,wk);       // interpolate interior J to edge
  mvmult( *im, wk, interior_J );

  dvmul( interior_J, f );
  return dot( f, w );
}

/** Add a discrete version of a Dirac delta function at a quadrature point
    with amplitude equal amp */
void NodalTri::add_Dirac_delta(const Ordinal qpt, const Scalar amp) {
  DGM_UNDEFINED;
}

/** Add a discrete version of a Dirac delta function at an arbitrary point p
    with amplitude equal amp.  The Point, p, must be within the NodalTri
    element. */
void NodalTri::add_Dirac_delta(const Point &p, const Scalar amp) {
  Scalar r, s;
  if(!get_local_coordinates(p,r,s)) {
    DGM::Comm::World->cerr()<<
      "NodalTri::Add_Dirac_delta: could not find (r,s)"<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  const Point q(r,s);
  return add_local_Dirac_delta(q,amp);
}

void NodalTri::add_local_Dirac_delta(const Point &p, const Scalar amp) {
  Scalar r = p.x;
  Scalar s = p.y;
  dMatrix delta(nModes(),1);
  dMatrix P(1,nModes());
  fntri(qa, (Ordinal)1, &r, &s, P);
  dMatrix V(nModes(),nModes());  // build Vandermonde matrix
  dVector Vrow(nModes());
  for (Ordinal i=0; i<nModes(); i++) {
    fill( psi->mode[i], Vrow );
    for (Ordinal j=0; j<nModes(); j++) V[i][j] = Vrow[j];
  }
  matmult(V, 'T', P, delta);
  Scalar wgt = one/geom->J[0];
  for(Ordinal q=0; q<qtot; ++q)
    u(q) += delta(q,0)*amp*wgt;
}

/// Extract the solution at the Point p
Scalar NodalTri::interpolate_point(const Point &p) const {
  Scalar r, s;
  if(!get_local_coordinates(p,r,s)) {
    DGM::Comm::World->cerr()
      <<"NodalTri::interpolate_point: could not find (r,s)"<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  const Point q(r,s);
  return interpolate_local_point(q);
}

/// Extract the solution at the Point p
Scalar NodalTri::interpolate_local_point(const Point &p) const {
  Scalar r = p.x;
  Scalar s = p.y;
  dMatrix P(1, nModes());
  fntri(qa, (Ordinal)1, &r, &s, P);
  dVector uhloc(qtot);
  // Forward Transform
  mvmult(Viloc->mat, u, uhloc);
  Scalar result=0;
  for(Ordinal m=0; m < nModes(); m++)
    result += uhloc(m)*P(0,m);
  return(result);
}

/// Extract the solution at the Points ps
/** \todo Need to vectorize this for efficiency. */
void NodalTri::interpolate_points( const vector<Point> &ps,
                                   dVector &vals) const {
  if (state != Physical) {
    cerr << "NodalTri::interpolate_points -- not in physical space"<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  vals.resize(numeric_cast<Ordinal>(ps.size()));
  for (size_t ip = 0; ip != ps.size(); ip++) {
    const Point &p = ps[ip];
    // Should copy / paste interpolate_local_points here
    // but change r,s,a,b,Pi, and Pj to vectors of length ps.size
    vals(numeric_cast<Ordinal>(ip)) = interpolate_local_point(p);
  }
}

Point NodalTri::get_local_coordinates(const Point &p) const {
  Scalar r=0, s=0;
  if(!get_local_coordinates(p,r,s)) {
    DGM::Comm::World->cerr()<<
      "NodalTri::get_local_coordinates: could not find (r,s)"<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  const Point q(r,s);
  return q;
}

/// Find the local coordinates \f$(r,s)\f$ at the point \f$p\f$
int NodalTri::get_local_coordinates(const Point &p, Scalar &r,
                                    Scalar &s) const {
  const Scalar EPSILON = 1.0e-10;

  Scalar r1, s1;
  Scalar x = p.x, y = p.y;
  Scalar x1 = vert[0]->x, y1 = vert[0]->y;
  Scalar x2 = vert[1]->x, y2 = vert[1]->y;
  Scalar x3 = vert[2]->x, y3 = vert[2]->y;

  dMatrix Nmals(3,2);

  for(Ordinal i=0; i<nEdges(); ++i){
    Nmals[i][0] = -(vert[(i+1)%nVerts()]->y - vert[i]->y);
    Nmals[i][1] =   vert[(i+1)%nVerts()]->x - vert[i]->x;
  }

  // first calculate r and s
  r1  = 2*((x  - x1)*Nmals[2][0] + (y  - y1)*Nmals[2][1]);
  r1 /=    (x2 - x1)*Nmals[2][0] + (y2 - y1)*Nmals[2][1];
  r1 -= 1.0;

  s1  = 2*((x  - x1)*Nmals[0][0] + (y  - y1)*Nmals[0][1]);
  s1 /=    (x3 - x1)*Nmals[0][0] + (y3 - y1)*Nmals[0][1];
  s1 -= 1.0;

  r = r1;
  s = s1;
  // Mapping (r,s) -> (a,b) not needed in Nodal
  //  r[0] = (1.0-s1) ? 2*(1.0+r1)/(1.0-s1) - 1.0: 1.0;
  //  s[0] = s1;

  if (r > 1.+EPSILON || r < -1.-EPSILON ||
      s > 1.+EPSILON || s < -1.-EPSILON) return 0;

  r = clamp(r, -1., 1.);
  s = clamp(s, -1., 1.);

  return 1;
}

/// Used to limit the number of times the side mass matrix is formed
#define DO_IT_ONCE

/// Use sparse local-global lift
#define USE_SPARSE_LIFT

/// Select LU factorization over Cholesky
//#define DGM_NODAL_TRI_USE_LU

/** F->edges holds the upwind flux at the Gauss pts
    U->edges holds the interior flux at the Gauss pts   */
void NodalTri::lift(const Element *const F, dVector &in, const char dir) const {
  // cout << "NodalTri::lift for Eid = " << gid() << endl;

  dVector tmp(qtot);
  tmp = 0.0;
  const Element *const U = this;

  // F->edges holds the upwind flux at the Gauss pts
  // U->edges holds the interior flux at the Gauss pts

#ifdef DO_IT_ONCE
  static bool firsttime=true;
  Ordinal qedg = U->edge[0].qtot();
  static dMatrix V(qedg,qedg);
  static dVector Vcol(qedg);
  static dMatrix M1(qedg,qedg);
#ifdef DGM_NODAL_TRI_USE_LU
  static iVector pivots(qedg);
#endif
  if (firsttime) {
    // cout << DGM::Comm::World->MyPID() << ": gid = " << U->gid << endl;
    // get the edge Vandermonde matrix
    for (Ordinal j=0; j<qedg; j++) {
      Vcol = psi->ba[j];
      for (Ordinal i=0; i<qedg; i++) V[i][j] = Vcol[i];
    }
    // get the edge mass matrix and factor
    matmult( V, 'T', V, M1 );
#ifdef DGM_NODAL_TRI_USE_LU
    if (LU_factor(M1, pivots) !=0)
      DGM::Comm::World->error("NodalTri LU_factor() failed.");
#else
    if (Cholesky_factor(M1) !=0)
      DGM::Comm::World->error("NodalTri Cholesky_factor() failed.");
#endif
    firsttime = false;
  }
#endif

  // Edge 0
  {
    Ordinal qedg = U->edge[0].qtot();
#ifndef DO_IT_ONCE
    // get the edge Vandermonde matrix
    dMatrix V(qedg,qedg);
    dVector Vcol(qedg);
    for (Ordinal j=0; j<qedg; j++) {
      Vcol = psi->ba[j];
      for (Ordinal i=0; i<qedg; i++) V[i][j] = Vcol[i];
    }
    // get the edge mass matrix and factor
    dMatrix M1(qedg,qedg);
    matmult( V, 'T', V, M1 );
#ifdef DGM_NODAL_TRI_USE_LU
    iVector pivots(qedg);
    if (LU_factor(M1, pivots) !=0)
      DGM::Comm::World->error("LU_factor() failed.");
#else
    if (Cholesky_factor(M1) !=0)
      DGM::Comm::World->error("Cholesky_factor() failed.");
#endif
#endif
    dVector f(g1_wk,qedg);
    dvsub( F->edge[0].u, U->edge[0].u, f );
    dvmul( U->edge[0].J(), f);
    if (dir == 'x')
      dvmul( U->edge[0].nx(), f );
    else if (dir == 'y')
      dvmul( U->edge[0].ny(), f );
#ifdef DGM_NODAL_TRI_USE_LU
    LU_solve(M1, pivots, f);
#else
    Cholesky_solve(M1, f);
#endif
    // assemble into element storage
    for(Ordinal i=0; i<qa; i++) tmp(i) += f(i);
  }

  // Edge 1
  {
    Ordinal qedg = U->edge[1].qtot();
#ifndef DO_IT_ONCE
    // get the edge Vandermonde matrix
    dMatrix V(qedg,qedg);
    dVector Vcol(qedg);
    for (Ordinal j=0; j<qedg; j++) {
      Vcol = psi->ba[j];
      for (Ordinal i=0; i<qedg; i++) V[i][j] = Vcol[i];
    }
    // get the edge mass matrix and factor
    dMatrix M1(qedg,qedg);
    matmult( V, 'T', V, M1 );
#ifdef DGM_NODAL_TRI_USE_LU
    iVector pivots(qedg);
    if (LU_factor(M1, pivots) !=0)
      DGM::Comm::World->error("LU_factor() failed.");
#else
    if (Cholesky_factor(M1) !=0)
      DGM::Comm::World->error("Cholesky_factor() failed.");
#endif
#endif
    dVector f(g1_wk,qedg);
    dvsub( F->edge[1].u, U->edge[1].u, f );
    dvmul( U->edge[1].J(), f);
    if (dir == 'x')
      dvmul( U->edge[1].nx(), f );
    else if (dir == 'y')
      dvmul( U->edge[1].ny(), f );
#ifdef DGM_NODAL_TRI_USE_LU
    LU_solve(M1, pivots, f);
#else
    Cholesky_solve(M1, f);
#endif
    // assemble into element storage
    for(Ordinal i=0; i<qa; i++) tmp((qa-1)*(i+1) - i*(i-1)/2) += f(i);
  }

  // Edge 2
  {
    Ordinal qedg = U->edge[2].qtot();
#ifndef DO_IT_ONCE
    // get the edge Vandermonde matrix
    dMatrix V(qedg,qedg);
    dVector Vcol(qedg);
    for (Ordinal j=0; j<qedg; j++) {
      Vcol = psi->ba[j];
      for (Ordinal i=0; i<qedg; i++) V[i][j] = Vcol[i];
    }
    // get the edge mass matrix and factor
    dMatrix M1(qedg,qedg);
    matmult( V, 'T', V, M1 );
#ifdef DGM_NODAL_TRI_USE_LU
    iVector pivots(qedg);
    if (LU_factor(M1, pivots) !=0)
      DGM::Comm::World->error("LU_factor() failed.");
#else
    if (Cholesky_factor(M1) !=0)
      DGM::Comm::World->error("Cholesky_factor() failed.");
#endif
#endif
    dVector f(g1_wk,qedg);
    dvsub( F->edge[2].u, U->edge[2].u, f );
    dvmul( U->edge[2].J(), f);
    if (dir == 'x')
      dvmul( U->edge[2].nx(), f );
    else if (dir == 'y')
      dvmul( U->edge[2].ny(), f );
#ifdef DGM_NODAL_TRI_USE_LU
    LU_solve(M1, pivots, f);
#else
    Cholesky_solve(M1, f);
#endif
    // assemble into element storage
    for(Ordinal i=0; i<qa; i++) tmp(qa*i - i*(i-1)/2) += f(i);
  }

  // Lift
  dVector ans(qtot);
  ans = 0.0;
#ifdef USE_SPARSE_LIFT
  // tmp2 = entries from tmp on boundary
  static dVector tmp2(3*(qa-1));
  Ordinal j=0;
  for(Ordinal i=0; i<qtot; i++)
    if (is_on_edge(i,qa)) {
      tmp2[j] = tmp[i];
      j++;
    }
  mvmult(Mbound->mat, tmp2, ans);
#else
  mvmult(M->mat, tmp, ans);
#endif
  dvadd(ans, in);
}

// Collocation derivative matrix
void NodalTri::get_derivative_matrix() {
  //  cout << "NodalTri::get_derivative_matrix()" << endl;
  dMatrix Vr(qtot, qtot), Vs(qtot,qtot);
  dVector Vrow(qtot);

  // Build inverse Vandermonde Matrix
  Viloc.reset( new Minfo );
  Viloc->mat.resize(qtot,nModes());  // build inverse Vandermonde matrix
  for(Ordinal i=0; i<nModes(); i++) {
    fill( psi->mode[i], Vrow );
    for(Ordinal j=0; j<qtot; j++)
      Viloc->mat[i][j] = Vrow[j];
  }

  if (LU_factor(Viloc->mat, Viloc->pivots)!=0)
    DGM::Comm::World->error("NodalTri::get_derivative_matrix -- LU_factor of "
                            "Vandermonde failed.");
  if (LU_inverse(Viloc->mat, Viloc->pivots)!=0)
    DGM::Comm::World->error("NodalTri::get_derivative_matrix -- LU_inverse of "
                            "Vandermonde failed.");

  D.reset(new Dinfo);
  D->Dr.resize(qtot,qtot);
  D->Drt.resize(qtot,qtot);
  D->Ds.resize(qtot,qtot);
  D->Dst.resize(qtot,qtot);
  dntri(Vr, Vs, psi->znt_r.ptr(), psi->znt_s.ptr(), L());

  matmult(Vr, Viloc->mat, D->Dr);
  matmult(Vs, Viloc->mat, D->Ds);

  // Store transposes of D->Dr and D->Ds!
  for(Ordinal i=0; i<qtot; i++)
    for(Ordinal j=0; j<qtot; j++) {
      D->Drt(i,j) = D->Dr(j,i);
      D->Dst(i,j) = D->Ds(j,i);
  }
  D->Da.resize(qa,qa);
  D->Dat.resize(qa,qa);
  dgll(D->Da,D->Dat,psi->za);
}

/** df/dx = df/dr * dr/dx + df/ds * ds/dx
    df/dy = df/dr * dr/dy + df/ds * ds/dy. */
void NodalTri::gradient( const dVector &f, dVector &fx, dVector &fy ) const {
  dVector fr(g1_wk,qtot);   // use gradient workspace
  dVector fs(g2_wk,qtot);   // use gradient workspace
  mvmult(D->Dr, f, fr);     // df/dr
  mvmult(D->Ds, f, fs);     // df/ds
  if (!curve.get()) {       // straight sided element
    const Scalar rx = geom->rx[0];
    const Scalar ry = geom->ry[0];
    const Scalar sx = geom->sx[0];
    const Scalar sy = geom->sy[0];
    if (sx) {
      multiply( sx, fs, fx );
      if (rx) daxpy( rx, fr, fx );
    } else
      multiply( rx, fr, fx );
    if (sy) {
      multiply( sy, fs, fy );
      if (ry) daxpy( ry, fr, fy );
    } else
      multiply( ry, fr, fy );
  } else {
    DGM::Comm::World->error("NodalTri::gradient -- no curved elements!");
  }
}

void NodalTri::gradient( const dVector &f, dVector &df, char dir) const {
  dVector fr(g1_wk,qtot);  // use gradient workspace
  dVector fs(g2_wk,qtot);  // use gradient workspace
  mvmult(D->Dr, f, fr);    // df/dr
  mvmult(D->Ds, f, fs);    // df/ds
  if (!curve.get()) {      // straight sided element
    const Scalar rx = geom->rx[0];
    const Scalar ry = geom->ry[0];
    const Scalar sx = geom->sx[0];
    const Scalar sy = geom->sy[0];
    switch(dir) {
    case 'x':
      if (sx) {
        multiply( sx, fs, df );
        if (rx) daxpy( rx, fr, df );
      } else
        multiply( rx, fr, df );
      break;
    case 'y':
      if (sy) {
        multiply( sy, fs, df );
        if (ry) daxpy( ry, fr, df );
      } else
        multiply( ry, fr, df );
      break;
    default:
      throw DGM::exception("Illegal direction in NodalTri::gradient value = "
                           +asString(dir));
      break;
    }
  } else {
    DGM::Comm::World->error("NodalTri::gradient -- no curved elements!");
  }
}

void NodalTri::local_gradient( const dVector &f, dVector &fr,
                               dVector &fs ) const {
  mvmult(D->Dr, f, fr); // df/dr
  mvmult(D->Ds, f, fs); // df/ds
}

void NodalTri::interpolate_to_uniform() {
  cout << "NodalTri::interpolate_to_uniform()" << endl;
}

void NodalTri::tecplot(FILE *fp) {
  DGM_UNDEFINED;
  int tnsf = 0;
  if (state == Transform) {
    tnsf = 1;
    backward_transform();
  }
  dVector ux(qa*qb);
  dVector uy(qa*qb);
  gradient( u, ux, uy );
  fprintf(fp,"ZONE T=\"Zone%llu\", ",(unsigned long long)gid());
  fprintf(fp,"I=%llu, J=%llu,  F=POINT\n",(unsigned long long)qa,
          (unsigned long long)qb);
  for (Ordinal j=0; j<qb; j++) {
    for (Ordinal i=0; i<qa; i++) {
      Ordinal q = j + i * qb;
      fprintf(fp,"%15.8e %15.8e %15.8e %15.8e %15.8e\n",
          C->x[q],C->y[q],u[q],ux[q],uy[q]);
    }
  }
  if (tnsf) forward_transform();
}

/// Output requested element information to a file
void NodalTri::binaryOutput(FILE *fp, const OutputType flag) const {
  const Ordinal Nel = (qa-1)*(qb-1);  // Number of sub-elements
  if (state == Transform)
    throw DGM::exception("NodalTri::output called when in transform space");
  switch(flag) {
  case ParaviewBinary: {
    const uint32_t length = numeric_cast<uint32_t>(qtot*sizeof(float));
    fwrite(&length,sizeof(uint32_t),1,fp);
    for (Ordinal q=0; q<qtot; q++) {
        const float tmp = u[q];
        fwrite(&tmp,sizeof(float),1,fp);
    }
    break;
  }
  case ParaviewCoordinates: {
    const uint32_t length = numeric_cast<uint32_t>(3*qtot*sizeof(float));
    fwrite(&length,sizeof(uint32_t),1,fp);
    CMC::Vector<float,int> xyz(3);
    for (Ordinal q=0; q<qtot; q++) {
      xyz[0] = C->x[q];
      xyz[1] = C->y[q];
      xyz[2] = 0.0;
      fwrite(xyz.ptr(),sizeof(float),3,fp);
    }
    break;
  }
  case ParaviewConnectivity: {
    const uint32_t length = numeric_cast<uint32_t>((3*Nel*sizeof(int32_t)));
    fwrite(&length,sizeof(uint32_t),1,fp);
    CMC::Vector<int32_t,int> con(3);
    for (Ordinal i=0,q=0; i<qa-1; i++) {
      for (Ordinal j=0; j<qa-i; j++,q++) {
        if (j != qa-i-1) {
          con[0] = numeric_cast<uint32_t>(q);
          con[1] = numeric_cast<uint32_t>(q+1);
          con[2] = numeric_cast<uint32_t>(q+qa-i);
          fwrite(con.ptr(),sizeof(int32_t),3,fp);
          if (i) {
            con[0] = numeric_cast<uint32_t>(q);
            con[1] = numeric_cast<uint32_t>(q+1);
            con[2] = numeric_cast<uint32_t>(q-(qa-i));
            fwrite(con.ptr(),sizeof(int32_t),3,fp);
          }
        }
      }
    }
    break;
  }
  case ParaviewOffsets: {
    const uint32_t length = numeric_cast<uint32_t>(Nel*sizeof(int32_t));
    fwrite(&length,sizeof(uint32_t),1,fp);
    int32_t q=3;
    for (Ordinal j=0; j<qb-1; j++) {
      for (Ordinal i=0; i<qa-1; i++) {
        fwrite(&q,sizeof(int32_t),1,fp);
        q+=3;
      }
    }
    break;
  }
  case ParaviewTypes: {
    const uint32_t length = numeric_cast<uint32_t>(Nel*sizeof(uint8_t));
    fwrite(&length,sizeof(uint32_t),1,fp);
    const uint8_t t=VTK_TRIANGLE;
    for (Ordinal j=0; j<qb-1; j++) {
      for (Ordinal i=0; i<qa-1; i++) {
        fwrite(&t,sizeof(uint8_t),1,fp);
      }
    }
    break;
  }
  default:
    error("Illegal output type requested in NodalTri::binaryOutput");
  }
}

/// Output requested element information to a file
streamoff NodalTri::binaryLength(const OutputType flag) const {
  const Ordinal Nel = (qa-1)*(qb-1);  // Number of sub-elements
  switch(flag) {
  case ParaviewBinary: {
    return sizeof(uint32_t)+qtot*sizeof(float);
    break;
  }
  case ParaviewCoordinates: {
    return sizeof(uint32_t)+3*qtot*sizeof(float);
    break;
  }
  case ParaviewConnectivity: {
    return sizeof(uint32_t)+3*Nel*sizeof(int32_t);
    break;
  }
  case ParaviewOffsets: {
    return sizeof(uint32_t)+Nel*sizeof(int32_t);
    break;
  }
  case ParaviewTypes: {
    return sizeof(uint32_t)+Nel*sizeof(uint8_t);
    break;
  }
  default:
    error("Illegal output type requested in NodalTri::binaryLength");
  }
  error("Fell through case statement in NodalTri::binaryLength");
  return 0;
}

/// Dump requested element information to a file
void NodalTri::output(FILE *fp, const char flag) const {
  if (state == Transform)
    throw DGM::exception("NodalTri::output called when in transform space");
  int c = 0;
  switch(flag) {
  case 'h':  // Tecplot header
    fprintf(fp,"\nZONE T=\"Element %llu\", ",(unsigned long long)gid());
    fprintf(fp,"n=%llu, e=%llu",(unsigned long long)nModes(),
            (unsigned long long)(qa-1)*(qb-1));
    fprintf(fp,", DATAPACKING=BLOCK, ZONETYPE=FETRIANGLE");
    break;
  case 'd':  // solution
    for (Ordinal q=0; q<qtot; q++) {
      if (c++%5==0) fprintf(fp,"\n");
      fprintf(fp,"%15.8e ",u[q]);
    }
    break;
  case 'x':  // x-coordinates
    for (Ordinal q=0; q<qtot; q++) {
      if (c++%5==0) fprintf(fp,"\n");
      fprintf(fp,"%15.8e ",C->x[q]);
    }
    break;
  case 'y':  // y-coordinates
    for (Ordinal q=0; q<qtot; q++) {
      if (c++%5==0) fprintf(fp,"\n");
      fprintf(fp,"%15.8e ",C->y[q]);
    }
    break;
  case 'p':  // points
    for (Ordinal q=0; q<qtot; q++) {
      fprintf(fp,"\n%15.8e %15.8e %15.8e ",C->x[q],C->y[q],0.0);
    }
    break;
  case 'c': // connectivity
    for (Ordinal i=0,q=0; i<qa-1; i++)
      for (Ordinal j=0; j<qa-i; j++,q++)
        if (j != qa-i-1) {
          fprintf(fp,"\n%llu %llu %llu ", (unsigned long long)q,
              (unsigned long long)(q+1), (unsigned long long)(q+qa-i));
          if (i) fprintf(fp,"\n%llu %llu %llu ", (unsigned long long)q,
              (unsigned long long)(q+1), (unsigned long long)(q-(qa-i)));
        }
    break;
  case 'f': // Tecplot footer
    for (Ordinal i=0,q=0; i<qa-1; i++)
      for (Ordinal j=0; j<qa-i; j++,q++)
        if (j != qa-i-1) {
          fprintf(fp,"\n%llu %llu %llu ", (unsigned long long)(q+1),
              (unsigned long long)(q+2), (unsigned long long)(q+1+qa-i));
          if (i) fprintf(fp,"\n%llu %llu %llu ", (unsigned long long)(q+1),
              (unsigned long long)(q+2), (unsigned long long)(q+1-(qa-i)));
        }
    break;
  case 't': // paraview element type
    for (Ordinal i=0; i<qa-1; i++)
      for (Ordinal j=0; j<qa-1; j++) {
        if (c++%5==0) fprintf(fp,"\n");
        fprintf(fp,"%d ",VTK_TRIANGLE);
      }
    break;
  case 'o': // paraview offset
    for (Ordinal i=0, off=3; i<qa-1; i++)
      for (Ordinal j=0; j<qa-1; j++) {
        if (c++%5==0) fprintf(fp,"\n");
        fprintf(fp,"%llu ",(unsigned long long)off);
        off+=3;
      }
    break;
  default:
    throw DGM::exception("Illegal flag in NodalTri::output value = "
                         +asString(flag));
  }
}

//============================================================================
//                       Norm and Error routines
//============================================================================

Scalar NodalTri::norm_Linf() const {
  return norm_inf(u);
}

void NodalTri::norm_L2(Scalar *L2, Scalar *area) const {
  // area ?
  dVector f(qtot);
  // integral of u*u
  dvmul(u, u, f);
  *L2 = integrate(f, area);
}

Scalar NodalTri::norm_L2() const {
  Scalar L2, area;
  norm_L2( &L2, &area );
  return sqrt(L2/area);
}

void NodalTri::norm_H1(Scalar *H1, Scalar *area) const {
  dVector ux(n1_wk,qtot), uy(n2_wk,qtot), du2(n3_wk,qtot);
  dVector f(qtot);

  gradient( u, ux, uy );   // compute x and y derivatives
  dvmul( ux, ux, ux );     // ux = ux^2
  dvmul( uy, uy, uy );     // uy = uy^2
  dvadd( ux, uy, du2 );    // ux = ux^2 + uy^2

  dvmul(  u,  u,  f );     // f  = u^2
  dvadd(du2,  f,  f );     // f  = u^2 + ux^2 + uy^2

  // integral of u^2 + ux^2 + uy^2
  *H1 = integrate(f, area);
}

Scalar NodalTri::norm_H1() const {
  Scalar H1, area;
  norm_H1( &H1, &area );
  return sqrt(H1/area);
}

Scalar NodalTri::integrate( Scalar *area ) const {
  DGM_UNDEFINED;
#ifdef DGM_USE_WJ
  const dVector &b = geom->wJ;
#else
  const dVector &wa = psi->wa;
  const dVector &wb = psi->wb;

  dVector b(n1_wk,qtot);
  dMatrix B(b,qa,qb);

  b = geom->J;  // load in the Jacobian

  // apply integration weights
  for(Ordinal j=0; j<qb; j++) {
    dSlice column(B.column(j));
    dvmul( wa, column );
  }
  for(Ordinal i=0; i<qa; i++) {
    dVector row(B.row(i));
    dvmul( wb, row);
  }
#endif
  if (area!=NULL) *area = sum( b );        // element area
  return dot( b, u );                      // integrate
}

/** Calculate integral of function stored in v using mass matrix
    useful for calculating various norms. */
Scalar NodalTri::integrate( const dVector &v, Scalar *area ) const {
  dVector f(qtot), fint(qtot);
  Scalar pos, neg;
  if (area!=NULL) {
    // Note: should be able to do both multiplies at once
    // with dMatrix(qtot,2)... but matmult(Vi,'T',v) transposes
    // v, not Vi

    // Equivalent of f = Vt*V*ones:
    dVector ones(qtot);
    for(Ordinal j=0; j<qtot; j++) ones(j) = 1.0;

    mvmult(Viloc->mat, ones, fint);
    tmvmult(Viloc->mat, fint, f);

    // Sum f (be smart, don't add small positive and negative numbers!)
    pos = 0.0;
    neg = 0.0;
    for(Ordinal j=0; j<qtot; j++) {
      if (f(j) > 0) pos += f(j);
      if (f(j) < 0) neg -= f(j);
    }
    *area = geom->J[0]*(pos-neg);
  }

  // Equivalent of f = Vt*V*v:
  mvmult (Viloc->mat, v, fint);
  tmvmult(Viloc->mat, fint, f);

  // Sum f (be smart, don't add small positive and negative numbers!)
  pos = 0.0;
  neg = 0.0;
  for(Ordinal j=0; j<qtot; j++) {
    if (f(j) > 0) pos += f(j);
    if (f(j) < 0) neg -= f(j);
  }
  return(geom->J[0]*(pos-neg));
}

/** This is a first stop towards having a self tuning, load balancing
    code. See the more detailed comments in Quad.cpp. */
int NodalTri::get_weight() const {
  static Ordinal Pmax = 10;
  static int Weight[11][2] = {
      { 89,  91},
      {108, 107},
      {133, 134},
      {157, 169},
      {194, 207},
      {231, 255},
      {263, 298},
      {313, 372},
      {373, 457},
      {437, 562},
      {480, 658}};
  int cflag = 0;
  if (curve.get()) cflag = 1;
  if (pOrder() > Pmax) {
    cout << "WARNING - NodalTri::get_weight(): "
         << "pOrder (="<<pOrder()<<") > Pmax (="<<Pmax<<")"<< endl;

    return Weight[Pmax][cflag];
  } else
    return Weight[pOrder()][cflag];
}

Scalar NodalTri::compute_measure() const {
  const dVector &J = geom->J;
  return ( integrate(J) );      // integrate
}

Scalar NodalTri::L2_inner_product(const Element *el, Scalar *area) const {
  DGM_UNDEFINED;
#ifdef DGM_USE_WJ
  const dVector &b = geom->wJ;
#else
  const dVector &wa = psi->wa;
  const dVector &wb = psi->wb;
  const dVector &J = geom->J;

  dVector b(n1_wk,qtot);
  dMatrix B(b,qa,qb);

  b = J;
  for(Ordinal j=0; j<qb; j++) {
    dSlice column(B.column(j));
    dvmul( wa, column );
  }
  for(Ordinal i=0; i<qa; i++) {
    dVector row(B.row(i));
    dvmul( wb, row);
  }
#endif
  dVector f(n2_wk,qtot);
  dvmul( el->u, u, f );       // f = u*el->u
  if (area) *area = sum( b );
  return dot( b, f );        // integrate
}

Scalar NodalTri::L2_inner_product(const dVector& vh, const dVector& wh,
                                  Scalar *area) const {
  DGM_UNDEFINED;
#ifdef DGM_USE_WJ
  const dVector &b = geom->wJ;
#else
  const dVector &wa = psi->wa;
  const dVector &wb = psi->wb;
  const dVector &J = geom->J;

  dVector b(n1_wk,qtot);
  dMatrix B(b,qa,qb);

  b = J;
  for(Ordinal j=0; j<qb; j++) {
    dSlice column(B.column(j));
    dvmul( wa, column );
  }
  for(Ordinal i=0; i<qa; i++) {
    dVector row(B.row(i));
    dvmul( wb, row);
  }
#endif
  dVector f(n2_wk,qtot);
  dvmul( vh, wh, f );         // f = vh*wh
  if (area) *area = sum( b );
  return dot( b, f );         // integrate
}

void NodalTri::get_side_Ds(const int sid, const dVector& dv,
                           dVector& dv_s) const {
  DGM_UNDEFINED;
  Ordinal p,q;
  assert( (dVector::size_type)edge[sid].qtot() == dv.size() );
  dv_s.resize(dv.size());
  dVector wk(qtot);
  dVector tmp1;
  dVector fx(qtot);
  dVector fy(qtot);
  dVector fx_s(dv.size());
  dVector fy_s(dv.size());
  dMatrix *im;
  switch(sid) {
  case 0:
    tmp1.resize(qa);
    im = get_interpolation_matrix(qb, dv.size(), Interp::G2GL);
    mvmult( *im,dv,tmp1);
    for(q=0; q<qb; q++)
      for (p=0; p<qa; p++)
        wk[q + p * qb] = tmp1[p];
    break;
  case 1:
    tmp1.resize(qb);
    im = get_interpolation_matrix(qb, dv.size(), Interp::G2GRJ);
    mvmult( *im,dv,tmp1);
    for(p=0;p<qa;p++)
      for (q=0; q<qb; q++)
        wk[q + p * qb] = tmp1[q];
    break;
  case 2:
    tmp1.resize(qb);
    im = get_interpolation_matrix(qb, dv.size(), Interp::G2GRJ);
    mvmult( *im,dv,tmp1);
    for(p=0;p<qa;p++)
      for (q=0; q<qb; q++)
        wk[q + p * qb] = tmp1[q];
    break;
  default:
    cerr << "tri::Ds -- unknown side" << endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  gradient(wk,fx,fy);
  load_side(fx,sid,fx_s);
  load_side(fx,sid,fy_s);
  dvmul(edge[sid].ny(),fx_s);
  scale(-1.0,fx_s); //-ny*f_x
  dvvtvp(edge[sid].nx(),fy_s,fx_s,dv_s);
  return;
}

void NodalTri::get_side_curvature( const int sid, dVector &dcurv) const {
  DGM_UNDEFINED;
  dcurv.resize(qa);
  if (curve.get()) {
    dVector tmp;
    dVector x1r,y1r,x2r,y2r;
    tmp.resize(qa);
    x1r.resize(qa);
    y1r.resize(qa);
    x2r.resize(qa);
    y2r.resize(qa);

    get_side(C->y,sid,tmp);
    mvmult(D->Da,tmp,y1r);
    mvmult(D->Da,y1r,y2r);  //D^2 y/ D r^2

    get_side(C->x,sid,tmp);
    mvmult(D->Da,tmp,x1r);
    mvmult(D->Da,x1r,x2r);  //D^2 x/ D r^2

    for(Ordinal i=0;i<qa;i++){
      Scalar ds = pow((x1r[i]*x1r[i]+y1r[i]*y1r[i]),1.5);
      Scalar dtheta = -(x1r[i]*y2r[i] - y1r[i]*x2r[i]);
      if(fabs(ds)<1.0e-6||fabs(dtheta)>1.0e10){
        cerr << "NodalTri::get_side_curvature -- singular curvature radius"
             <<endl;
        DGM::Comm::World->exit(DGM::FAILURE);
      }
      dcurv[i] = dtheta/ds;
    }
  } else  //straight side
    dcurv = 0.0;
}

void NodalTri::make_constant() {
  //cout << "NodalTri::make_constant()" <<endl;
  Ordinal i, j, n;
  bool needs_transform = false;
  if (state == Physical) {
    forward_transform();
    needs_transform = true;
  }
  i = 0;
  for (j=1; j<L(); j++) {
    n = j + i*L();
    uh[n] = 0.0;
  }
  j = 0;
  for (i=1; i<L(); i++) {
    n = j + i*L();
    uh[n] = 0.0;
  }
  for (i=1; i<L(); i++) {
    for (j=1; j<L(); j++) {
      n = j + i*L();
      uh[n] = 0.0;
    }
  }
  if (needs_transform)
    backward_transform();
}

void NodalTri::low_modes(const Ordinal inp) {
  const Ordinal np = numeric_cast<Ordinal>(inp);
  // cout << "NodalTri::low_modes()" <<endl;
  if (np>=pOrder()) return;  // nothing to do
  DGM_UNDEFINED;
  Ordinal i, j, n;
  bool needs_transform = false;
  if (state == Physical) {
    forward_transform();
    needs_transform = true;
  }
  // upper left
  for (i=0; i<np+1; i++) {
    for (j=np+1; j<L(); j++) {
      n = j + i*L();
      uh[n] = 0.0;
    }
  }
  // lower right
  for (j=0; j<=np+1; j++) {
    for (i=np+1; i<L(); i++) {
      n = j + i*L();
      uh[n] = 0.0;
    }
  }
  // upper right
  for (i=np+1; i<L(); i++) {
    for (j=np+1; j<L(); j++) {
      n = j + i*L();
      uh[n] = 0.0;
    }
  }
  if (needs_transform)
    backward_transform();
}

void NodalTri::kill_constant() {
  bool needs_transform = false;
  if (state == Physical) {
    forward_transform();
    needs_transform = true;
  }
  uh[0] = 0.0;
  if (needs_transform)
    backward_transform();
}

} // namespace DGM
