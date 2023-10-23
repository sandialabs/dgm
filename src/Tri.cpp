/** \file Tri.cpp
    \brief Modal triangle Element implementation
    \author Scott Collis

    Tri is a three node triangular element that supports both affine and
    curved sided isoparametric mappings from the master element to the
    physical space element.  It is based on the Dubiner warped mapping.
*/

// system includes
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#ifdef DGM_USE_GENERAL_GHOSTING
#include <boost/serialization/export.hpp>
#endif
using namespace std;

// boost includes
#include "boost/numeric/conversion/cast.hpp"
using boost::numeric_cast;

// DGM includes
#include "Comm.hpp"
#include "Tri.hpp"
#include "Polylib.tpp"
#include "Utilities.hpp"
#include "String.hpp"
#include "Vector.hpp"

#ifdef DGM_USE_GENERAL_GHOSTING
/// register class for serialization of polymorphic types
BOOST_CLASS_EXPORT_GUID(DGM::Tri, "DGM::Tri");
#endif

namespace DGM {

/// Use Gauss-Legendre quadrature instead of Gauss-Lobatto-Legendre
#define DGM_TRI_GAUSS_LEGENDRE

// define static storage

BasisDB Tri::bdb;                   // define Basis database
Tri::GeometryDB  Tri::gdb("Tri ");  // define Geom database
IMDB Tri::imdb;                     // define Interpolation matrix database

Ordinal Tri::Qmax = 0;
Ordinal Tri::Lmax = 0;
dVector Tri::g1_wk;
dVector Tri::g2_wk;

dVector Tri::n1_wk;
dVector Tri::n2_wk;
dVector Tri::n3_wk;
dVector Tri::Lwk;

bool Tri::first_warn(true);

#ifdef DGM_USE_MD_COUPLE
// Constructor for coupled physics
Tri::Tri(const Size ID, const Ordinal P, const Ordinal Q,
         const vector<Point> &X, const Model::Type model)
#else
/*! \param[in] ID    - Local element id
    \param[in] P     - Polynomial order
    \param[in] Q     - Quadrature order
    \param[in] X     - Vector of points defining the vertices */
Tri::Tri(const Size ID, const Ordinal P, const Ordinal Q,
         const vector<Point> &X)
#endif
  : Element(ID,Basis::Ortho) {
  // cout << "Tri::Tri, eid = " << ID << endl;
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

  // you might want to use different quadrature order in a and b
  qa = qb = Q; qc = 0;
  qtot = qa * qb;

  make_workspace(qtot,nModes());

  // construct vertex data-structure
  vert.resize(nVerts());
  for (Ordinal i = 0; i < nVerts(); i++){
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
    const Ordinal qedg = (i==0) ? qa-1 : qb-1;
    // cout << "Element = " << gid() << "qedg = " << qedg << endl;
#ifdef DGM_USE_MD_COUPLE
    Edge ed(i,id,nModes(),qedg,modeltype);
#else
    Edge ed(i,this,nModes(),qedg,false);
#endif
    edge.push_back(ed);
    side.push_back( &(edge[i]) );
  }
}

/** This should not allocate new space for P, M, etc. */
Tri::Tri(const Tri *E) {
  //  cout << "Tri copy constructor for Eid = " << E->gid() << endl;

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

Tri::~Tri() {
  // cout << "~Tri: eid= "<<id<<endl;
}

Basis* Tri::get_basis(const int der=0) const {
  Basis* b;
  char buf[128];
  sprintf(buf,"%llu_%llu_%llu_%llu_%llu",
          (long long unsigned)L(),
          (long long unsigned)der,(long long unsigned)qa,
          (long long unsigned)qb,(long long unsigned)qc);
  string key = buf;
  BasisDB::iterator p = bdb.bases.find(key);
  if ( p == bdb.bases.end() ) {             // not found, make a new one
    b = new Basis(L(),qa,qb,qc,nModes());
    make_basis(b,der);
    bdb.bases[key] = b;
  } else {                                  // found, return the basis
    b = p->second;
  }
  return b;
}

void Tri::make_basis(Basis *psi, const int der=0) {
  // cout << "Tri::make_basis" << endl;
  const Ordinal L=psi->L, qa=psi->qa, qb=psi->qb;
  dVector &za=psi->za, &wa=psi->wa, &zb=psi->zb, &wb=psi->wb;

  zwgll(za,wa);                // Gauss-Lobatto-Legendre points and weights
#ifdef DGM_TRI_GAUSS_LEGENDRE
  zwgrj(zb,wb,0.0,0.0);        // Gauss-Radau-Legendre points and weights
  for (Ordinal i=0; i<qb; i++)
    wb[i] *= (1.0-zb[i])*0.5;  // correct for triangle coordinates
#else
  zwgrj(zb,wb,1.0,0.0);        // Gauss-Radau-Jacobi points and weights
  for (Ordinal i=0; i<qb; i++)
    wb[i] *= 0.5;              // Automatically accounts for triangle coords
#endif

  // orthogonal basis as primary
  psi->ba = Basis::make_Legendre( der, L, qa, za );
  psi->Ba.alias( psi->ba[0].data(), L, qa );    // unsafe
  psi->bb = Basis::make_Dubiner( L, qb, zb );

  // setup modal access pointers
  psi->mode.resize(L*(L+1)/2);
  for (Ordinal i=0, m=0; i<L; i++) {
    for (Ordinal j=0; j<L-i; m++, j++) {
      psi->mode[m].a.alias( psi->ba[i] );
      psi->mode[m].b.alias( psi->bb[i][j], psi->bb[i].row(j).size() ); // unsafe
    }
  }

  // NOTE: secondary basis is not build!

  // setup C^0 modified Jacobi basis on a triangle
  psi->nVerts = 3;
  psi->nEdges = 3;
  psi->nFaces = 1;
  psi->mFace  = (L>3) ? L-3 : 0;
  psi->mIntr  = 0;

  // make the storage for the a and b modes
  psi->amem.resize(qa*max((Ordinal)3,L+1));
  psi->bmem.resize(qb*max((Ordinal)2,L+(L-2)*(L-1)/2));

  // reset the vert and edge maps for this element type
  VertMode *vm = new VertMode(psi);
  psi->vm.reset( vm );
  EdgeMode *em = new EdgeMode(psi, vm);
  psi->em.reset( em );
  psi->fm.reset( new FaceMode(psi, vm, em) );

  // 'a' direction
  {
    // vertex modes
    dVector v0(psi->vertMode(0).a);
    dVector v1(psi->vertMode(1).a);
    dVector v2(psi->vertMode(2).a);
    subtract(1.0, za, v0);
    scale(0.5, v0);
    add(1.0, za, v1);
    scale(0.5, v1);
    v2 = 1.0;

    // edge modes
    if (L>2) {
      dVector e0(psi->edgeMode(0,0).a);
      dvmul(v0, v1, e0);
      for (Ordinal i=1; i<L-2; i++) {
        dVector ei(psi->edgeMode(0,i).a);
        jacobf(za, ei, i, 1.0, 1.0 );
        dvmul(e0, ei, ei);
      }
    }
  }

  // 'b' direction
  {
    // vertex modes
    dVector v0(psi->vertMode(0).b);
    dVector v1(psi->vertMode(1).b);
    dVector v2(psi->vertMode(2).b);
    subtract(1.0, zb, v0);
    scale(0.5, v0);
    add(1.0, zb, v2);
    scale(0.5, v2);
    // edge modes
    if (L>2) {
      dVector e0(psi->edgeMode(0,0).b);
      dVector e1(psi->edgeMode(1,0).b);
      dvmul( v0, v0, e0 );
      dvmul( v1, v2, e1 );
      for (Ordinal i=1; i<L-2; i++) {
        dVector e0im1(psi->edgeMode(0,i-1).b);
        dVector e0i(psi->edgeMode(0,i).b);
        dVector e10(psi->edgeMode(1,0).b);
        dVector e1i(psi->edgeMode(1,i).b);
        dvmul( e0im1, v0, e0i );
        jacobf(zb, e1i, i, 1.0, 1.0 );
        dvmul(e10, e1i, e1i );
      }
    }
    // face modes
    if (L>3) {
      for (Ordinal i=0; i<L-3; i++) {
        dVector e0i(psi->edgeMode(0,i).b);
        dVector f0(psi->faceMode(0,i,0).b);
        dvmul( v2, e0i, f0);
      }
      for (Ordinal i=0; i<L-3; i++) {
        dVector fi0(psi->faceMode(0,i,0).b);
        for (Ordinal j=0; j<L-3-i; j++) {
          dVector fij(psi->faceMode(0,i,j).b);
          jacobf(zb, fij, j, 2.0*i+3.0, 1.0 );
          dvmul(fi0, fij, fij);
        }
      }
    }
  }
}

void Tri::get_mass_matrix() {
  //  cout << "Tri::get_mass_matrix for element " << gid() << endl;
  if (curve.get()) {
    M.reset( new Minfo );
    M->mat.resize(nModes(),nModes());
    M->pivots.resize(nModes());
    dVector f(qtot);
    dVector fh(f,nModes());
    for (Ordinal m=0; m<nModes(); m++) {
      fill( psi->mode[m], f );
      inner_product(f, fh);
      for (Ordinal n=0; n<nModes(); n++) M->mat[m][n] = fh[n];
    }
#ifdef DGM_CHOLESKY_MASS_MATRIX
    if (Cholesky_factor(M->mat) != 0) {
      DGM::Comm::World->cerr() << "Tri:  Cholesky_factor() failed." << endl;
      DGM::Comm::World->exit(DGM::FAILURE);
    }
#else
    if (LU_factor(M->mat, M->pivots) != 0) {
      DGM::Comm::World->cerr() << "Tri:  LU_factor() failed." << endl;
      DGM::Comm::World->exit(DGM::FAILURE);
    }
#endif
  }  else {
#ifdef DGM_BASIS_NORM
    // This only works if the Jacobian is constant
    M.reset( new Minfo );
    M->mat.resize(1,nModes());
    for (Ordinal j=0; j<nModes(); j++) M->mat[0][j] = 1.0/geom->J[0];
#else
    M.reset( new Minfo );
    M->mat.resize(1,nModes());
    dVector f(qtot);
    dVector fh(f,nModes());
    for (Ordinal m=0; m<nModes(); m++) {
      fill( psi->mode[m], f );
      inner_product(f, fh);
      M->mat[0][m] = fh[m];
    }
    for (Ordinal j=0; j<nModes(); j++) M->mat[0][j] = 1.0/M->mat[0][j];
#endif
  }
}

void Tri::get_mass_matrix(const dVector &x) {
  // cout << "Tri::get_mass_matrix(x) for element " << gid() << endl;
  // WARNING:  might be dangerous to reset the mass matrix to this new value
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
      World->error("Tri:get_mass_matrix(x):  Cholesky_factor() failed.");
#else
  if (LU_factor(M->mat, M->pivots) !=0)
    DGM::Comm::World->error("Tri:get_mass_matrix(x):  LU_factor() failed.");
#endif
  full_mass = true;
}

void Tri::solve_mass_matrix(dVector &fh) const {
#ifdef DGM_TIME_TRI
  static FunctionTimer T("Tri::solve_mass_matrix");
  FunctionSentry sentry(T);
#endif
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

/// Computes the normal gradient on a supplied side
/** \note Be careful as we use n1_wk and n2_wk here. */
void Tri::normal_times_gradient_side(const dVector &f, const int sid,
                                     dVector &fssum ) const {
  dVector dfx( n1_wk, qtot );
  dVector dfy( n2_wk, qtot );
  gradient( f, dfx, dfy );
#if 0
  // This is the older slower version
  assert ( f.size() == dfx.size() );
  assert ( fssum.size() == (dVector::size_type)side[sid]->qtot );
  dVector dfs( side[sid]->qtot );
  load_side( dfx, sid, dfs );
  dvmul( side[sid]->nx(), dfs );
  fssum = dfs;
#else
  load_side( dfx, sid, fssum );
  dvmul( side[sid]->nx(), fssum );
  dVector dfs( n1_wk, side[sid]->qtot() );
#endif
  load_side( dfy, sid, dfs );
  dvmul( side[sid]->ny(), dfs );
  dvadd( dfs, fssum );  // BLAS may be slightly faster than fssum += dfs;
}

// fill element with a function string
void Tri::fill(string function_string, Operation operation) {
  state = Physical;
  parser_init();
  Parser::VectorFunction f("x", "y", "t", function_string );
  f.evaluate( C->x, C->y, u, 0.0, convert(operation) );
  state = Physical;
}

// fill element with a mode
void Tri::fill(Mode &v) {
  //  cout << "Tri::fill(Mode &)" << endl;
  dMatrix U(u,qa,qb);
  for (Ordinal i=0; i<qa; i++)
    for (Ordinal j=0; j<qb; j++)
      U[i][j] = v.a[i] * v.b[j];
  state = Physical;
}

// fill a vector with a mode
void Tri::fill(Mode &v, dVector &f) const {
  //  cout << "Tri::fill(Mode &, dVector &)" << endl;
  dMatrix F(f,qa,qb);
  for (Ordinal i=0; i<qa; i++)
    for (Ordinal j=0; j<qb; j++) {
      F[i][j] = v.a[i] * v.b[j];
    }
}

/// Fill element with a random polynomial
void Tri::random() {
  // cout << "Tri::random()" << endl;
  state = Transform;
  for (Ordinal i=0; i<nModes(); i++) uh[i] = Element::random(-one,one);
  backward_transform();
}

void Tri::set(const dVector &fh, const Ordinal nModes2) {
  //cout << "Tri::set(const dVector &, const int)" << endl;
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

void Tri::inner_product() {
  //  cout << "Tri::inner_product() for Eid = " << gid() << endl;
  inner_product(u, uh);
  state = Transform;
}

void Tri::inner_product(dVector &f, dVector &fh) const {
  //  cout<<"Tri::inner_product(dVector&, dVector&) for Eid = "<<id<<endl;
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
  // for(Ordinal i=0; i<qa; i++) dvmul( wb, F.row(i) );  // more expensive
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

void Tri::forward_transform() {
  // cout << "Tri::forward_transform()" << endl;
  if (state == Transform) {
    cerr << "Tri::transform -- already in transform space"<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  forward_transform(u,uh);
  state = Transform;
}

void Tri::forward_transform(dVector &f, dVector &fh) const {
  // cout << "Tri::forward_transform(dVector &f, dVector &fh)" << endl;
#ifdef DGM_TIME_TRI
  static FunctionTimer T("Tri::forward_transform");
  FunctionSentry sentry(T);
#endif
  inner_product(f,fh);
  solve_mass_matrix(fh);
}

void Tri::forward_transform(Element *F, Element *) {
  //cout << "Tri::forward_transform(*F,*)" << endl;
  if (state == Transform) {
    cerr << "Tri::transform -- already in transform space"<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  inner_product(u,uh);
  F->solve_mass_matrix(uh);  // Use element F's Mass matrix
  state = Transform;
}

void Tri::backward_transform() {
  if (state == Physical) {
    cerr << "Tri::transform_to_physical -- already in physical space"<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  backward_transform(uh, u);
  state = Physical;
}

void Tri::backward_transform(dVector &fh, dVector &f) const {
  dVector Fh, wk;
  int mode = 0;
  for (Ordinal i = 0; i < L(); ++i){
    Fh.alias( fh, mode, L()-i );
    wk.alias( Lwk, i*qb, qb );
    tmvmult( psi->bb[i], Fh, wk );
    mode += L()-i;
  }
  dMatrix Wk( Lwk, L(), qb );
  dMatrix F( f, qa, qb );
  matmult( 'T', psi->Ba, Wk, F); // F[qa][qb] = (Ba[La][qa])^T * wk[La][qb]
}

void Tri::get_side(const dVector &from, const Ordinal edge, dVector &to) const {
  // cout<<"Tri::get_side() Element = "<<id<<" Edge = "<<edge<<endl<<to<<endl;
  Ordinal p, q;
  if (state == Transform) {
    cerr << "Tri::get_side -- must be in physical space"<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  switch(edge) {
  case 0:
    q = 0;
    for (p=0; p<qa; p++) to[p] = from[q + p * qb];
    break;
  case 1:
    p = qa-1;
    for (q=0; q<qb; q++) to[q] = from[q + p * qb];
    break;
  case 2:
    p = 0;
    for (q=0; q<qb; q++) to[q] = from[q + p * qb];
    break;
  default:
    cerr << "Tri::get_side -- unknown edge" << endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
}

// Interpolation matrix
void Tri::make_interpolation_matrix( const Ordinal q1, const Ordinal q2,
  const Interp::Type interp, dMatrix &im ) {
  //  cout << "Tri::make_interpolation_matrix" << endl;
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
    cerr << "Tri::make_interpolation_matrix - Invalid interpolation type"
         << endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
}

dMatrix* Tri::get_interpolation_matrix(const Ordinal q1, const Ordinal q2,
                                       const Interp::Type interp=Interp::GL2G) {
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

// Interpolate physical space values "f" to the side Gauss points.
void Tri::fill_sides(const dVector &f) {
  dVector wka(g1_wk,qa);
  dVector wkb(g2_wk,qb);
  dMatrix *im;

  im = get_interpolation_matrix( edge[0].qtot(), qa, Interp::GL2G);
  get_side(f,0,wka);
  mvmult( *im, wka, edge[0].u );

  im = get_interpolation_matrix( edge[1].qtot(), qb, Interp::GRJ2G);
  get_side(f,1,wkb);
  mvmult( *im, wkb, edge[1].u );

  im = get_interpolation_matrix( edge[2].qtot(), qb, Interp::GRJ2G);
  get_side(f,2,wkb);
  mvmult( *im, wkb, edge[2].u );
}

// Interpolate physical space values "f" to a uniform mesh on the sides.
void Tri::fill_sides_uniform(const dVector &f) {
  dVector wka(g1_wk,qa);
  dVector wkb(g2_wk,qb);
  dMatrix *im;

  im = get_interpolation_matrix( edge[0].qtot(), qa, Interp::GL2U);
  get_side(f,0,wka);
  mvmult( *im, wka, edge[0].u );

  im = get_interpolation_matrix( edge[1].qtot(), qb, Interp::GRJ2U);
  get_side(f,1,wkb);
  mvmult( *im, wkb, edge[1].u );

  im = get_interpolation_matrix( edge[2].qtot(), qb, Interp::GRJ2U);
  get_side(f,2,wkb);
  mvmult( *im, wkb, edge[2].u );
}

// flux version
void Tri::fill_sides(const dVector &fx, const dVector &fy) {
  dVector wka(g1_wk,qa);
  dVector wkb(g2_wk,qb);
  dVector wk;
  dMatrix *im;

  im = get_interpolation_matrix( edge[0].qtot(), qa, Interp::GL2G);
  wk.alias(Lwk,edge[0].qtot());
  get_side(fx,0,wka);
  mvmult( *im, wka, edge[0].u );
  get_side(fy,0,wka);
  mvmult( *im, wka, wk );
  dvmul( edge[0].nx(), edge[0].u );
  dvvtvp( edge[0].ny(), wk, edge[0].u, edge[0].u );

  im = get_interpolation_matrix( edge[1].qtot(), qb, Interp::GRJ2G);
  wk.alias(Lwk,edge[1].qtot());
  get_side(fx,1,wkb);
  mvmult( *im, wkb, edge[1].u );
  get_side(fy,1,wkb);
  mvmult( *im, wkb, wk );
  dvmul( edge[1].nx(), edge[1].u );
  dvvtvp( edge[1].ny(), wk, edge[1].u, edge[1].u );

  im = get_interpolation_matrix( edge[2].qtot(), qb, Interp::GRJ2G);
  wk.alias(Lwk,edge[2].qtot());
  get_side(fx,2,wkb);
  mvmult( *im, wkb, edge[2].u );
  get_side(fy,2,wkb);
  mvmult( *im, wkb, wk );
  dvmul( edge[2].nx(), edge[2].u );
  dvvtvp( edge[2].ny(), wk, edge[2].u, edge[2].u );
}

// Interpolate physical space values "f" to the edge Gauss points.
// But store the result in vector g
void Tri::load_side(const dVector &f, const Ordinal side_number, dVector &g)
  const {
  dVector wka(g1_wk,qa);
  dVector wkb(g2_wk,qb);
  dMatrix *im;
  switch(side_number) {
  case 0:
    im = get_interpolation_matrix( edge[0].qtot(), qa, Interp::GL2G);
    get_side(f,0,wka);
    mvmult( *im, wka, g );
    break;
  case 1:
    im = get_interpolation_matrix( edge[1].qtot(), qb, Interp::GRJ2G);
    get_side(f,1,wkb);
    mvmult( *im, wkb, g );
    break;
  case 2:
    im = get_interpolation_matrix( edge[2].qtot(), qb, Interp::GRJ2G);
    get_side(f,2,wkb);
    mvmult( *im, wkb, g );
    break;
  }
}

// compute coordinates of quadrature points
void Tri::get_coordinates() {
  if (curve.get())
    get_curved_coordinates();
  else
    get_straight_coordinates();
}

void Tri::get_straight_coordinates() {
  //  cout << "Tri::get_straight_coordinates for element " << gid() << endl;
  Ordinal q;
  C.reset( new Coord(qtot) ); *C = 0;
  dMatrix phi(qa,qb);
  for (Ordinal n = 0; n<nVerts(); n++) {
    for (Ordinal i=0; i<qa; i++) {        // fill basis matrix
      for (Ordinal j=0; j<qb; j++) {
        phi[i][j] = psi->vertMode(n).a[i] * psi->vertMode(n).b[j];
      }
    }
    for (Ordinal i=0; i<qa; i++) {
      for (Ordinal j=0; j<qb; j++) {
        q = j + i*qb;
        C->x[q] += vert[n]->x * phi[i][j];
        C->y[q] += vert[n]->y * phi[i][j];
      }
    }
  }
}

/// Returns the side vertices and quadrature points
void Tri::get_curved_side_info(const Ordinal sid, vector<Point> &p,
                               dVector &z, int &orientation) const {
  orientation = (sid==0 || sid==1) ? 1 : -1;
  const Ordinal q = (sid==0) ? qa : qb;
  dVector w(q);
  z.resize(q);
  zwgll(z,w);      // always use GLL points even on sides 1 and 2
  p.resize(2);
  p[0].x = vert[sid]->x;
  p[0].y = vert[sid]->y;
  p[1].x = vert[(sid+1)%nVerts()]->x;
  p[1].y = vert[(sid+1)%nVerts()]->y;
}

/// Transform from C^0 modified Jacobi basis to physical space
/** This is primarily used to work with curved elements to transform the
    quadrature points from the reference coordinates to physical space. */
void Tri::J_backward_transform(dVector &fh, dVector &f) {
  //  cout << "J_backward_transform for elmt = " << gid() << endl;
  dMatrix B;
  dVector Fh, wk;
  int mode = 0;

  Fh.alias( fh, mode, L() );
  wk.alias( Lwk, 0, qb);
  B.alias( psi->vertMode(2).b.data(), L(), qb );  // unsafe alias
  tmvmult( B, Fh, wk );                       // wk[qb] = B[qb,Lb] F[Lb]
  mode+=L();

  Fh.alias( fh, mode, L() );
  wk.alias( Lwk, 1*qb, qb);
  B.alias ( psi->vertMode(2).b.data(), L(), qb );  // unsafe alias
  tmvmult( B, Fh, wk );                        // wk[qb] = B[qb,Lb] F[Lb]
  mode+=L();

  for (Ordinal i=0; i<L()-2; mode+=L()-2-i, i++) {
    Fh.alias( fh, mode, L()-2-i );
    wk.alias( Lwk, (i+2)*qb, qb );
    B.alias( psi->edgeMode(0,i).b.data(), L()-2-i, qb );  // unsafe alias
    tmvmult( B, Fh, wk );                      // wk[qb] = B[qb,L-2-i] F[L-2-i]
  }

  dMatrix Wk( Lwk, L(), qb );
  dMatrix F( f, qa, qb );
  B.alias( psi->vertMode(1).a.data(), L(), qa );   // unsafe alias
  matmult( 'T', B, Wk, F );                    // F[qb,qb] = B[L,qa] F[qb,qb]
}

void Tri::get_curved_coordinates() {
  Ordinal i, l, m;
  // cout << "Tri::get_curved_coordinates()" << endl;
  C.reset( new Coord(qtot) ); *C = 0.0;
  dVector fh(nModes()+1);  // note the +1 for the top vertex!
  fh = 0;
#if 1
  // copy xh into fh (lay 'b' modes first -- opposite of Quad's)
  l = m = 0;
  fh[m++] = vert[2]->x;
  fh[m++] = vert[1]->x;
  if (curve->side == 1)
    for (i=0; i<L()-2; i++)
      fh[m++] = curve->xh[i];
  else
    for (i=0; i<L()-2; i++)
      fh[m++] = 0.0;

  fh[m++] = vert[2]->x;
  fh[m++] = vert[0]->x;
  if (curve->side == 2)
#if 0
    for (i=0; i<L()-2; i++)
      if (i%2)
        fh[m++] = -curve->xh[i];
      else
        fh[m++] = curve->xh[i];
#else
    for (i=0; i<L()-2; i++)
      fh[m++] = curve->xh[i];
#endif
  else
    for (i=0; i<L()-2; i++)
      fh[m++] = 0.0;

  if (curve->side == 0)
    for (i=0, l=m; i<L()-2; l+=L()-2-i, i++)
      fh[l] = curve->xh[i];
  else
    for (i=0, l=m; i<L()-2; l+=L()-2-i, i++)
      fh[l] = 0.0;
#ifndef __clang__
  // Need to turn this off for CLANG
  m++;
  for (i=0; i<L()-3; m += L()-2-i, i++)
    for (Ordinal j=0, l=m; j<L()-3-i; l++, j++)
      fh[l] = 0.0;
#endif
#endif
  J_backward_transform( fh, C->x );
  fh = 0.0;
#if 1
  // copy yh into fh (lay 'b' modes first -- opposite of Quad's)
  l = m = 0;
  fh[m++] = vert[2]->y;
  fh[m++] = vert[1]->y;
  if (curve->side == 1)
    for (i=0; i<L()-2; i++)
      fh[m++] = curve->yh[i];
  else
    for (i=0; i<L()-2; i++)
      fh[m++] = 0.0;

  fh[m++] = vert[2]->y;
  fh[m++] = vert[0]->y;
  if (curve->side == 2)
#if 0
    for (i=0; i<L()-2; i++)
      if (i%2)
        fh[m++] = -curve->yh[i];
      else
        fh[m++] = curve->yh[i];
#else
    for (i=0; i<L()-2; i++)
      fh[m++] = curve->yh[i];
#endif
  else
    for (i=0; i<L()-2; i++)
      fh[m++] = 0.0;

  if (curve->side == 0)
    for (i=0, l=m; i<L()-2; l+=L()-2-i, i++)
      fh[l] = curve->yh[i];
  else
    for (i=0, l=m; i<L()-2; l+=L()-2-i, i++)
      fh[l] = 0.0;
#ifndef __clang__
  // Need to turn this off for CLANG
  m++;
  for (i=0; i<L()-3; m += L()-2-i, i++)
    for (Ordinal j=0, l=m; j<L()-3-i; l++, j++)
      fh[l] = 0.0;
#endif
#endif
  J_backward_transform( fh, C->y );
}

void Tri::get_side_coordinates(const Ordinal nedge, Point *pedge)const {
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
    cerr << "Tri::compute_side_coordinates illegal edge id." << endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
}

void Tri::compute_geometry() {
  // cout << "Tri::compute_geometry for element " << gid() << endl;
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

/// Compute the geometric factors
/** This version is valid for simplicial elements using an
    isoparametric mapping.

    The Jacobian matrix is given by
    \f[\boldsymbol{J} =
       \begin{bmatrix}
         x_{,r} && x_{,s} \\
         y_{,r} && y_{,s}
       \end{bmatrix}
    \f]
    such that the determinate of the Jacobian is
    \f[ J = x_{,r} y_{,s} - x_{,s} y_{,r} \f]
    where, for example
    \f[ x_{,r} = \frac{\partial x}{\partial r} \f]

    Simplicial elements have a constant Jacobian matrix over the element
*/
void Tri::compute_straight_geometry() {
  // cout << "Tri::compute_straight_geometry for element " << gid() << endl;

  // compute coordinate gradients in mapped space
  const Scalar pt5 = 0.5;
  Scalar xr = (vert[1]->x - vert[0]->x)*pt5;
  Scalar xs = (vert[2]->x - vert[0]->x)*pt5;
  Scalar yr = (vert[1]->y - vert[0]->y)*pt5;
  Scalar ys = (vert[2]->y - vert[0]->y)*pt5;

  // Jacobian is constant by construction for a simplex so no need to check

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

#ifdef DGM_USE_WJ
  const dVector &wa = psi->wa;
  const dVector &wb = psi->wb;
  dVector &b =  geom->wJ;
  dMatrix B(b,qa,qb);

  b = detJ;  // load in the Jacobian

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
}

/// Compute the geometric factors
/** This version is valid for general curved elements using an
    isoparametric mapping.

    The Jacobian matrix is given by
    \f[\boldsymbol{J} =
       \begin{bmatrix}
         x_{,r} && x_{,s} \\
         y_{,r} && y_{,s}
       \end{bmatrix}
    \f]
    such that the determinate of the Jacobian is
    \f[ J = x_{,r} y_{,s} - x_{,s} y_{,r} \f]
    where, for example
    \f[ x_{,r} = \frac{\partial x}{\partial r} \f]
*/
void Tri::compute_curved_geometry() {
  //  cout << "Tri::compute_curved_geometry for element " << gid() << endl;

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
      DGM::Comm::World->exit(DGM::FAILURE);
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
#endif // DGM_STORE_METRICS
}

/// Compute the stability metrics for timestep size calucations.
Element::StabMetrics Tri::compute_metrics() {
  return compute_metrics_2d_tensor_prod();
}

/// Computes geometric factors for the Element Sides
void Tri::compute_side_geometry() {
  //  cout << "Tri::compute_side_geometry(), Eid = "<< gid() << endl;
  sigma(0.0);
  for (Ordinal i=0; i<nEdges(); i++) {
    Edge &e = edge[i];
    const Ordinal qedg = e.qtot();
    // cout << "Edge " << i << ", qedg = " << qedg << endl;
    const Ordinal q = (i==0) ? qa : qb;
    const dMatrix &Der = (i==0) ? D->Da : D->Db;
    dMatrix *im;
    if (i==0)
      im = get_interpolation_matrix( qedg, q, Interp::GL2G );  // to, from
    else
      im = get_interpolation_matrix( qedg, q, Interp::GRJ2G ); // to, from
    dVector wk(q), wk2(q);

    switch(i) {
    case 0:
      get_side(geom->sx,i,wk);         // wk is at Gauss-Lobatto points
      mvmult( *im, wk, e.nx() );         // interpolate to Gauss
      scale( -1.0, e.nx() );             // negate since on bottom
      get_side(geom->sy,i,wk);
      mvmult( *im, wk, e.ny() );
      scale( -1.0, e.ny() );
      break;
    case 1:
      get_side(geom->rx,i,wk);
      get_side(geom->sx,i,wk2);
      dvadd(wk2,wk);
      mvmult( *im, wk, e.nx() );
      get_side(geom->ry,i,wk);
      get_side(geom->sy,i,wk2);
      dvadd(wk2,wk);
      mvmult( *im, wk, e.ny() );
      break;
    case 2:
      get_side(geom->rx,i,wk);
      mvmult( *im, wk, e.nx() );
      scale( -1.0, e.nx() );             // negate since on left
      get_side(geom->ry,i,wk);
      mvmult( *im, wk, e.ny() );
      scale( -1.0, e.ny() );
      break;
    }

    dVector interior_J(qedg);
    get_side(geom->J,i,wk);            // interpolate interior J to edge
    mvmult( *im, wk, interior_J );

    // make normals have unit length
    for (Ordinal j=0; j<qedg; j++) {
      Scalar len = sqrt( e.nx(j)*e.nx(j) +
                         e.ny(j)*e.ny(j) );
      e.nx(j) /= len;
      e.ny(j) /= len;
#if 0
      cout << "Element = " << gid() << ", edge = " << i << ", q = " << j
           << ", (nx,ny) = " << e.nx(j) << ", " << e.ny(j)
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
    dvmul( x, x, x);       // x = x^2
    dvvtvp( y, y, x, x );  // x = x^2 + y^2
    dvsqrt( x, wk );       // wk = sqrt(x)

    // interpolate to Gauss points
    mvmult( *im, wk, e.J() );

    // divide the side Jacobian by the interior Jacobian
    dvdiv( interior_J, e.J() );

    // This is done so that you can use an interior integration to perform the
    // surface integration.  For this to work you must use an interior
    // quadrature rule that includes the boundaries and you must divide the
    // edge contributions by the integration weight in the other direction(s).

    // store the max ratio of side to element Jacobians
    e.h_n_inv(0.0);
    for (Ordinal k=0; k<qedg; ++k) {
      const Scalar Jedge = fabs(e.J(k));
      sigma(max( sigma(), Jedge ));
      e.h_n_inv(max( e.h_n_inv(), 0.5*Jedge ));
    }

    // compute and store the Edge measure for each Side
    dVector p(qedg); p = one;
    e.measure(compute_side_integral(p,i));
  }
}

void Tri::forward_transform_side(dVector &f, dVector &fh) {
  //  cout << "Tri::forward_transform_side(), Eid = "<< gid() << endl;
  fh.resize(L()-2);  // vertices are not included
  // subtract off vertices
  daxpy( -f[0], psi->vertMode(0).a, f );
  daxpy( -f[qa-1], psi->vertMode(1).a, f);
  // inner product
  dvmul( psi->wa, f );
  for (Ordinal i=0; i<L()-2; i++)
    fh[i] = dot( psi->edgeMode(0,i).a, f );
  if (L()-2) solve_1d_mass_matrix(fh);
}

void Tri::solve_1d_mass_matrix(dVector &fh) const {
  Minfo M1d;
  get_1d_mass_matrix(M1d);
#ifdef DGM_CHOLESKY_MASS_MATRIX
  Cholesky_solve(M1d.mat, fh);
#else
  LU_solve(M1d.mat, M1d.pivots, fh);
#endif
}

void Tri::get_1d_mass_matrix(Minfo &M1d) const {
  dVector w, psi1, psi2, tmp(qa-2);
  M1d.mat.resize(L()-2,L()-2);
  M1d.pivots.resize(L()-2);
  for (Ordinal i=0; i<L()-2; i++) {
    w.alias(psi->wa,1,qa-2);
    psi1.alias( psi->edgeMode(0,i).a, 1, qa-2 );
    dvmul( w, psi1, tmp );
    for (Ordinal j=0; j<L()-2; j++) {
      psi2.alias( psi->edgeMode(0,j).a, 1, qa-2 );
      M1d.mat[i][j] = dot( tmp, psi2 );
    }
  }
#ifdef DGM_CHOLESKY_MASS_MATRIX
  if (Cholesky_factor(M1d.mat) !=0) {
    cerr << "Cholesky_factor() failed." << endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
#else
  if (LU_factor(M1d.mat, M1d.pivots) !=0) {
    cerr << "LU_factor() failed." << endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
#endif
}

Scalar Tri::compute_side_integral( dVector &f, Ordinal sid ) const {
  Ordinal qsid = side[sid]->qtot();
  dVector z(qsid), w(qsid);
  zwgl(z,w);                 // Gauss-Legendre
  dvmul( side[sid]->J(), f);
  dMatrix *im;
  Ordinal q = (sid==0) ? qa : qb;
  if (sid==0)
    im = get_interpolation_matrix( qsid, q, Interp::GL2G );   // to, from
  else
    im = get_interpolation_matrix( qsid, q, Interp::GRJ2G );  // to, from
  dVector wk(q);
  dVector interior_J(qsid);
  get_side(geom->J,sid,wk);       // interpolate interior J to edge
  mvmult( *im, wk, interior_J );
  dvmul( interior_J, f );
  return dot( f, w );
}

/** Add a discrete version of a Dirac delta function at a quadrature point
    with amplitude equal amp. */
void Tri::add_Dirac_delta(const Ordinal qpt, const Scalar amp) {
  assert( qpt >= 0 && qpt < qtot );
  Ordinal i, j;
  // recover i and j from qpt =  j  + i*qb;
  j = qpt % qb;
  i = (qpt-j)/qb;
  Scalar wght = (psi->wa[i])*(psi->wb[j]);
  u[qpt] += amp/(wght*geom->J[qpt]);
}

/** Add a discrete version of a Dirac delta function at an arbitrary point p
    with amplitude equal amp.  The Point, p, must be within the Tri element.
*/
void Tri::add_Dirac_delta(const Point &p, const Scalar amp) {
  Scalar r, s;
  if(!get_local_coordinates(p,r,s))
    throw DGM::exception("Tri::Add_Dirac_delta: could not find (r,s)");
  const Point q(r,s);
  return add_local_Dirac_delta(q,amp);
}

void Tri::add_local_Dirac_delta(const Point &p, const Scalar amp) {
  const Scalar r=p.x;
  const Scalar s=p.y;

  dMatrix imx, imy;
  dVector tmp(qa);

  // 2D interpolation
  dVector tmpy;
  dVector z2(qb), w2(qb);

  // Compute Gauss-Radau-Legendre points and weights
  zwgrl(z2,w2);     // y direction
  // Form the interpolation matrix from Gauss-Radau-Legendre to s
  imy.resize(1,qb);
  igrlm(imy,z2,s);

  // 1D interpolation in the a-direction
  dVector z1(qa), w1(qa);
  // Compute Gauss-Lobatto-Legendre points and weights
  zwgll(z1,w1);
  imx.resize(1,qa);
  // Form the interpolation matrix from Gauss-Lobatto-Legendre to r
  igllm(imx,z1,r);
  for (Ordinal i=0; i<qa; i++) {
    for (Ordinal j=0; j<qb; j++) {
      Ordinal qpt = j + i*qb;
      Scalar im = imx(0,i)*imy(0,j);
      Scalar wght = (psi->wa[i])*(psi->wb[j]);
      u[qpt] += im * amp/(wght*geom->J[qpt]);
    }
  }
}

/// Extract the solution at the Point p
Scalar Tri::interpolate_point(const Point &p) const {
  Scalar r, s;
  if(!get_local_coordinates(p,r,s))
    throw DGM::exception("Tri::interpolate_point: could not find (r,s)");
  const Point q(r,s);
  return interpolate_local_point(q);
}

/// Extract the solution at the Point p
Scalar Tri::interpolate_local_point(const Point &p) const {
  const Scalar r=p.x;
  const Scalar s=p.y;
  dMatrix im;
  dVector tmp(qa), result(1);

  // 2D interpolation
  dVector tmpy;
  dVector z2(qb), w2(qb);

  // Compute Gauss-Radau-Legendre points and weights
  zwgrl(z2,w2); // y direction
  // Form the interpolation matrix from Gauss-Radau-Legendre to s
  im.resize(1,qb);
  igrlm(im,z2,s);

  // Interpolate to temporary points at y=s at each x location
  for (Ordinal i=0;i<qa;i++) {
    // Now get the solution values at the appropriate quadrature points.
    // We need to get qb values starting at i*qb
    tmpy.alias(const_cast<dVector&>(u),i*qb,qb);  // watch out
    mvmult( im, tmpy, result);
    tmp[i] = result[0];
  }
  // 1D interpolation in the a-direction
  dVector z1(qa), w1(qa);
  // Compute Gauss-Lobatto-Legendre points and weights
  zwgll(z1,w1); // x direction
  im.resize(1,qa);
  // Form the interpolation matrix from Gauss-Lobatto-Legendre to r
  igllm(im,z1,r);
  // Now interpolate along our temporary y points to get the value at r,s
  mvmult(im, tmp, result);
  return result[0]; // the interpolated solution is returned
}

void Tri::calculate_interpolation_matrices(vector<fMatrix>     &M,
                                           const vector<Point> &P) const{
  const Ordinal N = numeric_cast<Ordinal>(P.size());

  M.resize(2);
  M[0].resize(N,qb);
  M[1].resize(N,qa);

  fVector z(qb), w(qb);
  fVector X(N);

  // Compute Gauss-Radau-Legendre points and weights
  zwgrl(z,w); // y direction

  // Form the interpolation matrix from Gauss-Radau-Legendre to s
  for (Ordinal i=0; i<N; ++i) X[i] = P[i].y;
  igrlm(M[0],z,X);

  if (qa != qb) {
    z.resize(qa); w.resize(qa);
  }
  // Compute Gauss-Lobatto-Legendre points and weights
  zwgll(z,w); // x direction

  // Form the interpolation matrix from Gauss-Lobatto-Legendre to r
  for (Ordinal i=0; i<N; ++i) X[i] = P[i].x;
  igllm(M[1],z,X);
}

void Tri::apply_interpolation_matrices(dVector &V,
   const vector<fMatrix>&M) const {

  if (state != Physical) {
    cerr << "Tri::interpolate_points -- not in physical space"<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }

  if (2!=M.size())
    error("Tri::apply_interplation_matrices: Incorrect matrix size.");
  if (M[0].rows() != M[1].rows())
    error("Tri::apply_interplation_matrices: Inconsistant matrix size.");
  Ordinal sqa = qa, sqb = qb;
  if (M[0].cols() != sqb || M[1].cols() != sqa)
    error("Tri::apply_interplation_matrices: Inconsistant matrix size.");


  const Ordinal N = M[0].rows();

  fMatrix T(N,qa);
  fVector F(qa*qb);
  for (Ordinal i=0; i<qa*qb; ++i) F[i] = u[i];
  fMatrix U(F,qa,qb);
  matmult(M[0], 'T', U, T);

  V.resize(N);
  for (Ordinal i=0; i<N; ++i) {
    const fVector r1 = M[1].row(i);
    const fVector r2 = T.row(i);
    V[i] = dot(r1,r2);
  }
}

void Tri::calculate_interpolation_matrices(vector<dMatrix>     &M,
                                           const vector<Point> &P) const{
  const Ordinal N = numeric_cast<Ordinal>(P.size());

  M.resize(2);
  M[0].resize(N,qb);
  M[1].resize(N,qa);

  dVector z(qb), w(qb);
  dVector X(N);

  // Compute Gauss-Radau-Legendre points and weights
  zwgrl(z,w); // y direction

  // Form the interpolation matrix from Gauss-Radau-Legendre to s
  for (Ordinal i=0; i<N; ++i) X[i] = P[i].y;
  igrlm(M[0],z,X);

  if (qa != qb) {
    z.resize(qa); w.resize(qa);
  }
  // Compute Gauss-Lobatto-Legendre points and weights
  zwgll(z,w); // x direction

  // Form the interpolation matrix from Gauss-Lobatto-Legendre to r
  for (Ordinal i=0; i<N; ++i) X[i] = P[i].x;
  igllm(M[1],z,X);
}

void Tri::apply_interpolation_matrices(dVector              &V,
                                       const vector<dMatrix>&M) const {

  if (state != Physical) {
    cerr << "Tri::interpolate_points -- not in physical space"<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }

  if (2!=M.size())
    error("Tri::apply_interplation_matrices: Incorrect matrix size.");
  if (M[0].rows() != M[1].rows())
    error("Tri::apply_interplation_matrices: Inconsistant matrix size.");
  Ordinal sqa = qa, sqb = qb;
  if (M[0].cols() != sqb || M[1].cols() != sqa)
    error("Tri::apply_interplation_matrices: Inconsistant matrix size.");


  const Ordinal N = M[0].rows();

  dMatrix T(N,qa);
  dVector F(qa*qb);
  for (Ordinal i=0; i<qa*qb; ++i) F[i] = u[i];
  dMatrix U(F,qa,qb);
  matmult(M[0], 'T', U, T);

  V.resize(N);
  for (Ordinal i=0; i<N; ++i) {
    const dVector r1 = M[1].row(i);
    const dVector r2 = T.row(i);
    V[i] = dot(r1,r2);
  }
}

/// Extract the solution at the Points ps
void Tri::interpolate_points(const vector<Point> &ps,
                             dVector &vals) const {
  if (state != Physical) {
    cerr << "Tri::interpolate_points -- not in physical space"<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  const Ordinal N = numeric_cast<Ordinal>(ps.size());

  dMatrix M(N,qb);
  dVector z(qb), w(qb);
  dVector X(N);

  // Compute Gauss-Radau-Legendre points and weights
  zwgrl(z,w); // y direction

  // Form the interpolation matrix from Gauss-Radau-Legendre to s
  for (Ordinal i=0; i<N; ++i) X[i] = ps[i].y;
  igrlm(M,z,X);

  dMatrix T(N,qa);
  dMatrix U(u,qa,qb);
  matmult(M, 'T', U, T);

  if (qa != qb) {
    z.resize(qa); w.resize(qa);
    M.resize(N,qa);
  }

  // Compute Gauss-Lobatto-Legendre points and weights
  zwgll(z,w); // x direction

  // Form the interpolation matrix from Gauss-Lobatto-Legendre to r
  for (Ordinal i=0; i<N; ++i) X[i] = ps[i].x;
  igllm(M,z,X);

  // Now interpolate along our temporary y points to get the value at ps
  vals.resize(N);
  for (Ordinal i=0; i<N; ++i) {
    const dVector r1 = M.row(i);
    const dVector r2 = T.row(i);
    vals[i] = dot(r1,r2);
  }
}

/// Find the local coordinates \f$(r,s)\f$ at the point \f$p\f$
Point Tri::get_local_coordinates(const Point &p) const {
  Scalar r=0, s=0;
  if(!get_local_coordinates(p,r,s)) {
    DGM::Comm::World->cerr()<<
      "Tri::get_local_coordinates: could not find (r,s)"<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  const Point q(r,s);
  return q;
}

/// Find the local coordinates \f$(r,s)\f$ at the point \f$p\f$
/** \warning This seems to use the wrong Guass points for a Triangle. */
int Tri::get_local_coordinates(const Point &p, Scalar &r, Scalar &s) const {

  if (!curve.get()) {       // This is the code specific for straight Tri's

    Scalar r1, s1;
    Scalar x = p.x, y = p.y;
    Scalar x1 = vert[0]->x, y1 = vert[0]->y;
    Scalar x2 = vert[1]->x, y2 = vert[1]->y;
    Scalar x3 = vert[2]->x, y3 = vert[2]->y;

    dMatrix Nmals(3,2);

    for(Ordinal i=0;i<nEdges();++i){
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

    // Mapping (r,s) -> (a,b)
    r = (1.0-s1)? 2*(1.0+r1)/(1.0-s1) - 1.0: 1.0;
    s = s1;

    if (1 == CMC::approx_less(1.,abs(r)) ||
        1 == CMC::approx_less(1.,abs(s))) return 0;

    r = clamp(r, -1., 1.);
    s = clamp(s, -1., 1.);

    return 1;

  } else {

    const Scalar EPSILON = 1.0e-6;   // tolerance on updates
    const int MAXITER = 100;         // maximum iterations allowed
    const Scalar TOL = 1.001;        // Tolerance on whether inside element
    const Scalar DIV = 1.5;          // Allowable divergence outside element

    // This is the general code from Quad that will work for curved Tri's

    Scalar  drdx, drdy;
    Scalar  dsdx, dsdy;

    Scalar  xp(0.0), yp(0.0);
    Scalar  rr, ss;
    Scalar  x, y;
    int     converged = 0, iter = 0;

    r = 0.0;   // always start from 0
    s = 0.0;   // always start from 0
    x = p.x;
    y = p.y;
    Scalar length = sqrt(x*x + y*y) + sqrt(measure())*EPSILON;

    Scalar dx = 1.0;
    Scalar dy = 1.0;

    rr = clamp (r, -one, one);   // make sure inside element
    ss = clamp (s, -one, one);   // make sure insdie element

    dVector z1(qa), z2(qb);
    dVector w1(qa), w2(qb);
    dMatrix im(1,qb);
    dVector vxp(qa),   vyp(qa),
            vdrdx(qa), vdrdy(qa),
            vdsdx(qa), vdsdy(qa),
            tmpy(qb),  tmp1(1);

    dVector tmpvxp(qa*qb),   tmpvyp(qa*qb),
            tmpvdrdx(qa*qb), tmpvdrdy(qa*qb),
            tmpvdsdx(qa*qb), tmpvdsdy(qa*qb);

    // Get the quadrature points
    zwgll(z1,w1);
    if (qa != qb) zwgll(z2,w2);
    else          z2 = z1;

    while (!converged && iter++ <= MAXITER) {

      xp   = 0.0;
      yp   = 0.0;
      drdx = 0.0;
      drdy = 0.0;
      dsdx = 0.0;
      dsdy = 0.0;

      // Form the interpolation matrix
      igllm(im,z2,ss);

      // Interpolate to temporary points at y=s at each x location
      for(Ordinal i=0;i<qa;i++) {
        Ordinal offset = i*qb;

        tmpy.alias(C->x,offset,qb);
        mvmult( im, tmpy, tmp1);
        vxp[i]=tmp1[0];
        tmpy.alias(C->y,offset,qb);
        mvmult( im, tmpy, tmp1);
        vyp[i]=tmp1[0];

        // interpolating mapping metrics
        tmpy.alias(geom->rx,offset,qb);
        mvmult( im, tmpy, tmp1);
        vdrdx[i]=tmp1[0];
        tmpy.alias(geom->ry,offset,qb);
        mvmult( im, tmpy, tmp1);
        vdrdy[i]=tmp1[0];

        tmpy.alias(geom->sx,offset,qb);
        mvmult( im, tmpy, tmp1);
        vdsdx[i]=tmp1[0];
        tmpy.alias(geom->sy,offset,qb);
        mvmult( im, tmpy, tmp1);
        vdsdy[i]=tmp1[0];
      }

      // Form the interpolation matrix
      im.resize(1,qa);
      igllm(im,z1,rr);

      mvmult( im, vxp, tmp1);
      xp = tmp1[0];
      mvmult( im, vyp, tmp1);
      yp = tmp1[0];

      mvmult( im, vdrdx, tmp1);
      drdx = tmp1[0];
      mvmult( im, vdrdy, tmp1);
      drdy = tmp1[0];

      mvmult( im, vdsdx, tmp1);
      dsdx = tmp1[0];
      mvmult( im, vdsdy, tmp1);
      dsdy = tmp1[0];

      dx = x - xp;                    // Distance from the point (x,y,z)
      dy = y - yp;

      rr += (drdx * dx + drdy * dy);  // Update
      ss += (dsdx * dx + dsdy * dy);

      // Convergence test
      if (sqrt(dx*dx + dy*dy )/length < EPSILON) converged = iter;
      if (fabs(rr) > DIV || fabs(ss) > DIV ) converged = -iter;
    }

    if (fabs(rr) > TOL || fabs(ss) > TOL ) {
      if (DGM::Comm::World->verbosity()>4) {
        DGM::Comm::World->cerr()<<__FILE__<<":"<<__LINE__
            <<" get_local_coordinates: point outside element" <<endl
            <<"    "<< fabs(rr) <<" > " << TOL
            <<" || "<< fabs(ss) <<" > " << TOL <<endl
            << setiosflags(ios::fixed) << setprecision(8)
            <<"Searching for point : "<< p <<endl
            <<"Last determined location : ( "<<xp<<", "<<yp<<" )"<<endl
            << *this;
        DGM::Comm::World->cerr()<<"Vertices:"<<endl;
        for(Ordinal i=0;i<nVerts();i++) {
          DGM::Comm::World->cerr()<<" ( "<<vert[i]->x<<", "
                                  <<vert[i]->y<<" )"<<endl;
        }
      }
      return 0;
    }
    if(iter > MAXITER){
      DGM::Comm::World->cerr()<<__FILE__<<":"<<__LINE__<<endl
          <<"get_local_coordinates: did not converge after "
          <<iter<<" iterations."<<endl
          << setiosflags(ios::fixed) << setprecision(8)
          <<"Searching for point : "<< p <<endl
          <<"Last determined location : ( "<<xp<<", "<<yp<<" )"<<endl
          << *this;
      DGM::Comm::World->cerr()<<"Vertices:"<<endl;
      for(Ordinal i=0;i<nVerts();i++) {
        DGM::Comm::World->cerr()<<" ( "<<vert[i]->x<<", "
                                <<vert[i]->y<<" )"<<endl;
      }
      return 0;
    }
    r = rr;
    s = ss;
    return 1;
  }
}

void Tri::lift(const Element *const F, dVector &in, const char dir) const {
  // cout << "Tri::lift for Eid = " << gid() << endl;
#ifdef DGM_TIME_TRI
  static FunctionTimer T("Tri::lift");
  FunctionSentry sentry(T);
#endif
  const Element *const U = this;
  dMatrix *im;
  const dVector &wa = U->psi->wa;
  const dVector &wb = U->psi->wb;
  // dVector &za = U->psi->za;
  const dVector &zb = U->psi->zb;

  // F->edges holds the upwind flux at the Gauss pts
  // U->edges holds the interior flux at the Gauss pts

  dMatrix In(in,qa,qb);

  // Edge 0
  {
    Ordinal const q = qa;
    Ordinal const qedg = U->edge[0].qtot();
    im = get_interpolation_matrix(q, qedg, Interp::G2GL);
    dVector f(g1_wk,qedg);
    dVector fi(g2_wk,q);
    dvsub( F->edge[0].u, U->edge[0].u, f );
    dvmul( U->edge[0].J(), f);
    if (dir == 'x')
      dvmul( U->edge[0].nx(), f );
    else if (dir == 'y')
      dvmul( U->edge[0].ny(), f );
    mvmult( *im, f, fi );
    scale( 1/wb[0], fi );
    dSlice column(In.column(0));
    dvadd( fi, column );
  }
  // Edge 1
  {
    Ordinal const q = qb;
    Ordinal const qedg = U->edge[1].qtot();
    im = get_interpolation_matrix(q, qedg, Interp::G2GRJ);  // to, from
    dVector f(g1_wk,qedg);
    dVector fi(g2_wk,q);
    dvsub( F->edge[1].u, U->edge[1].u, f );
    dvmul( U->edge[1].J(), f);
    if (dir == 'x')
      dvmul( U->edge[1].nx(), f );
    else if (dir == 'y')
      dvmul( U->edge[1].ny(), f );
    mvmult( *im, f, fi );
#ifdef DGM_TRI_GAUSS_LEGENDRE
    for(Ordinal i=0; i<qb; i++) fi[i] *= 2.0/(wa[qa-1]*(1.0-zb[i]));
#else
    for(Ordinal i=0; i<qb; i++) fi[i] *= 2.0/(wa[qa-1]*(1.0-zb[i]));
#endif
    dVector row(In.row(qa-1));
    dvadd( fi, row );
  }
  // Edge 2
  {
    Ordinal const q = qb;
    Ordinal const qedg = U->edge[2].qtot();
    im = get_interpolation_matrix(q, qedg, Interp::G2GRJ);  // to, from
    dVector f(g1_wk,qedg);
    dVector fi(g2_wk,q);
    dvsub( F->edge[2].u, U->edge[2].u, f );
    dvmul( U->edge[2].J(), f);
    if (dir == 'x')
      dvmul( U->edge[2].nx(), f );
    else if (dir == 'y')
      dvmul( U->edge[2].ny(), f );
    mvmult( *im, f, fi );
#ifdef DGM_TRI_GAUSS_LEGENDRE
    for(Ordinal i=0; i<qb; i++) fi[i] *= 2.0/(wa[0]*(1.0-zb[i]));
#else
    for(Ordinal i=0; i<qb; i++) fi[i] *= 2.0/(wa[0]*(1.0-zb[i]));
#endif
    dVector row(In.row(0));
    dvadd( fi, row );
  }
}

// collocation derivative matrix
void Tri::get_derivative_matrix() {
  //  cout << "Tri::get_derivative_matrix()" << endl;
  D.reset(new Dinfo);
  D->Da.resize(qa,qa);
  D->Dat.resize(qa,qa);
  D->Db.resize(qb,qb);
  D->Dbt.resize(qb,qb);
  dgll(D->Da,D->Dat,psi->za);
#ifdef DGM_TRI_GAUSS_LEGENDRE
  dgrj(D->Db,D->Dbt,psi->zb,0.0,0.0);
#else
  dgrj(D->Db,D->Dbt,psi->zb,1.0,0.0);
#endif
}

/**
   df/dx = df/dr * dr/dx + df/ds * ds/dx
   df/dy = df/dr * dr/dy + df/ds * ds/dy
*/
void Tri::gradient( const dVector &f, dVector &fx, dVector &fy ) const {
  dMatrix F(f,qa,qb);      // matrix alias of vector
  dVector fr(g1_wk,qtot);  // use gradient workspace
  dVector fs(g2_wk,qtot);  // use gradient workspace
  dMatrix Fr(fr,qa,qb);    // matrix alias of vector
  dMatrix Fs(fs,qa,qb);    // matrix alias of vector
  matmult( D->Da, F, Fr );  // df/da
  for (Ordinal i=0; i<qa; i++)
    for (Ordinal j=0; j<qb; j++)
      Fr[i][j] *= 2.0/(1.0 - psi->zb[j]);
  if (!curve.get()) {           // straight sided element
    Scalar rx,ry,sx,sy;
    rx  =  geom->rx[0];
    ry  =  geom->ry[0];
    sx  =  geom->sx[0];
    sy  =  geom->sy[0];
    if (sx||sy) {
      matmult( F, D->Dbt, Fs ); // df/db
      for (Ordinal i=0; i<qa; i++)
        for (Ordinal j=0; j<qb; j++)
          Fs[i][j] += (1.0 + psi->za[i]) * 0.5 * Fr[i][j];
    }
    if (sy) {
      multiply( sy, fs, fy );
      if (ry) daxpy( ry, fr, fy );
    } else
      multiply( ry, fr, fy );
    if (sx) {
      multiply( sx, fs, fx );
      if (rx) daxpy( rx, fr, fx );
    } else
      multiply( rx, fr, fx );
  } else {                    // curved element
    matmult( F, D->Dbt, Fs ); // df/db
    for (Ordinal i=0; i<qa; i++)
      for (Ordinal j=0; j<qb; j++)
        Fs[i][j] += (1.0 + psi->za[i]) * 0.5 * Fr[i][j];
    dvmul ( geom->rx, fr, fx);       // fx  = rx * fr
    dvvtvp( geom->sx, fs, fx, fx );  // fx += sx * fs
    dvmul ( geom->ry, fr, fy);       // fy  = ry * fr
    dvvtvp( geom->sy, fs, fy, fy );  // fy += sy * fs
  }
}

void Tri::gradient( const dVector &f, dVector &df, char dir) const {
  dMatrix F(f,qa,qb);
  dVector fr(g1_wk,qtot);  // use gradient workspace
  dVector fs(g2_wk,qtot);  // use gradient workspace
  dMatrix Fr(fr,qa,qb);    // matrix alias of vector
  dMatrix Fs(fs,qa,qb);    // matrix alias of vector

  matmult( D->Da, F, Fr );  // df/da
  for (Ordinal i=0; i<qa; i++)
    for (Ordinal j=0; j<qb; j++)
      Fr[i][j] *= 2.0/(1.0 - psi->zb[j]);

  matmult( F, D->Dbt, Fs ); // df/db
  for (Ordinal i=0; i<qa; i++)
    for (Ordinal j=0; j<qb; j++)
      Fs[i][j] += (1.0 + psi->za[i]) * 0.5 * Fr[i][j];

  if (!curve.get()) {       // straight sided
    Scalar rx,ry,sx,sy;
    rx  =  geom->rx[0];
    ry  =  geom->ry[0];
    sx  =  geom->sx[0];
    sy  =  geom->sy[0];
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
    }
  } else {                             // curved
    switch(dir) {
    case 'x':
      dvmul ( geom->rx, fr, df);       // fx  = rx * fr
      dvvtvp( geom->sx, fs, df, df );  // fx += sx * fs
      break;
    case 'y':
      dvmul ( geom->ry, fr, df);       // fy  = ry * fr
      dvvtvp( geom->sy, fs, df, df );  // fy += sy * fs
      break;
    }
  }
}

void Tri::local_gradient( const dVector &f, dVector &fr, dVector &fs ) const {
  dMatrix F(f,qa,qb);       // matrix alias of vector
  dMatrix Fr(fr,qa,qb);     // matrix alias of vector
  dMatrix Fs(fs,qa,qb);     // matrix alias of vector

  matmult( D->Da, F, Fr );  // df/da
  for (Ordinal i=0; i<qa; i++)
    for (Ordinal j=0; j<qb; j++)
      Fr[i][j] *= 2.0/(1.0 - psi->zb[j]);

  matmult( F, D->Dbt, Fs ); // df/db
  for (Ordinal i=0; i<qa; i++)
    for (Ordinal j=0; j<qb; j++)
      Fs[i][j] += (1.0 + psi->za[i]) * 0.5 * Fr[i][j];
}

void Tri::interpolate_to_uniform() {
  cout << "Tri::interpolate_to_uniform()" << endl;
}

void Tri::tecplot(FILE *fp) {
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
      const Ordinal q = j + i * qb;
      fprintf(fp,"%15.8e %15.8e %15.8e %15.8e %15.8e\n",
          C->x[q],C->y[q],u[q],ux[q],uy[q]);
    }
  }
  if (tnsf) forward_transform();
}

/// Output requested element information to a file
void Tri::binaryOutput(FILE *fp, const OutputType flag) const {
  if (state == Transform)
    throw DGM::exception("Tri::output called when in transform space");
  switch(flag) {
  case ParaviewBinary: {
    const uint32_t length = numeric_cast<uint32_t>(qa*qb*sizeof(float));
    fwrite(&length,sizeof(uint32_t),1,fp);
    for (Ordinal j=0; j<qb; j++) {
      for (Ordinal i=0; i<qa; i++) {
        const Ordinal q = j+i*qb;
        const float tmp = u[q];
        fwrite(&tmp,sizeof(float),1,fp);
      }
    }
    break;
  }
  case ParaviewCoordinates: {
    const uint32_t length = numeric_cast<uint32_t>(3*qa*qb*sizeof(float));
    fwrite(&length,sizeof(uint32_t),1,fp);
    CMC::Vector<float,int> xyz(3);
    for (Ordinal j=0; j<qb; j++) {
      for (Ordinal i=0; i<qa; i++) {
        const Ordinal q = j+i*qb;
        xyz[0] = C->x[q];
        xyz[1] = C->y[q];
        xyz[2] = 0.0;
        fwrite(xyz.ptr(),sizeof(float),3,fp);
      }
    }
    break;
  }
  case ParaviewConnectivity: {
    const uint32_t length =
      numeric_cast<uint32_t>(4*(qa-1)*(qb-1)*sizeof(int32_t));
    fwrite(&length,sizeof(uint32_t),1,fp);
    CMC::Vector<int32_t,int> con(4);
    for (Ordinal i=0; i<qa-1; i++) {
      for (Ordinal j=0; j<qb-1; j++) {
        con[0] = numeric_cast<uint32_t>(j+i*qb);
        con[1] = numeric_cast<uint32_t>(j+(i+1)*qb);
        con[2] = numeric_cast<uint32_t>(j+1+(i+1)*qb);
        con[3] = numeric_cast<uint32_t>(j+1+i*qb);
        fwrite(con.ptr(),sizeof(int32_t),4,fp);
      }
    }
    break;
  }
  case ParaviewOffsets: {
    const uint32_t length =
      numeric_cast<uint32_t>((qa-1)*(qb-1)*sizeof(Ordinal));
    fwrite(&length,sizeof(uint32_t),1,fp);
    Ordinal q=4;
    for (Ordinal j=0; j<qb-1; j++) {
      for (Ordinal i=0; i<qa-1; i++) {
        fwrite(&q,sizeof(uint32_t),1,fp);
        q+=4;
      }
    }
    break;
  }
  case ParaviewTypes: {
    const uint32_t length =
      numeric_cast<uint32_t>((qa-1)*(qb-1)*sizeof(uint8_t));
    fwrite(&length,sizeof(uint32_t),1,fp);
    const uint8_t t=VTK_QUAD;
    for (Ordinal j=0; j<qb-1; j++) {
      for (Ordinal i=0; i<qa-1; i++) {
        fwrite(&t,sizeof(uint8_t),1,fp);
      }
    }
    break;
  }
  default:
    error("Illegal output type requested in Tri::binaryOutput");
  }
}

/// Output requested element information to a file
streamoff Tri::binaryLength(const OutputType flag) const {
  switch(flag) {
  case ParaviewBinary: {
    return sizeof(uint32_t)+qa*qb*sizeof(float);
    break;
  }
  case ParaviewCoordinates: {
    return sizeof(uint32_t)+3*qa*qb*sizeof(float);
    break;
  }
  case ParaviewConnectivity: {
    return sizeof(uint32_t)+4*(qa-1)*(qb-1)*sizeof(int32_t);
    break;
  }
  case ParaviewOffsets: {
    return sizeof(uint32_t)+(qa-1)*(qb-1)*sizeof(int32_t);
    break;
  }
  case ParaviewTypes: {
    return sizeof(uint32_t)+(qa-1)*(qb-1)*sizeof(uint8_t);
    break;
  }
  default:
    error("Illegal output type requested in Tri::binaryLength");
  }
  error("Fell through case statement in Tri::binaryLength");
  return 0;
}

/// Output requested element information to a file
void Tri::output(FILE *fp, const char flag) const {
  if (state == Transform)
    throw DGM::exception("Tri::output called when in transform space");
  int c = 0;
  switch(flag) {
  case 'h':  // Tecplot header
    fprintf(fp,"\nZONE T=\"Element %llu\", ", (unsigned long long)gid());
    fprintf(fp,"I=%llu, J=%llu, F=BLOCK",(unsigned long long)qa,
            (unsigned long long)qb);
    break;
  case 'd':  // solution
    for (Ordinal j=0; j<qb; j++)
      for (Ordinal i=0; i<qa; i++) {
        const Ordinal q = j + i*qb;
        if (c++%5==0) fprintf(fp,"\n");
        fprintf(fp,"%15.8e ",u[q]);
      }
    break;
  case 'x':  // x-coordinates
    for (Ordinal j=0; j<qb; j++)
      for (Ordinal i=0; i<qa; i++) {
        const Ordinal q = j + i*qb;
        if (c++%5==0) fprintf(fp,"\n");
        fprintf(fp,"%15.8e ",C->x[q]);
      }
    break;
  case 'y':  // y-coordinates
    for (Ordinal j=0; j<qb; j++)
      for (Ordinal i=0; i<qa; i++) {
        const Ordinal q = j + i*qb;
        if (c++%5==0) fprintf(fp,"\n");
        fprintf(fp,"%15.8e ",C->y[q]);
      }
    break;
  case 'p':  // points
    for (Ordinal j=0; j<qb; j++)
      for (Ordinal i=0; i<qa; i++) {
        const Ordinal q = j+i*qb;
        fprintf(fp,"\n%15.8e %15.8e %15.8e ",C->x[q],C->y[q],0.0);
    }
    break;
  case 'c': // connectivity
    for (Ordinal i=0; i<qa-1; i++)
      for (Ordinal j=0; j<qb-1; j++) {
        const Ordinal qij = j+i*qb;
        const Ordinal qipj = j+(i+1)*qb;
        const Ordinal qijp = j+1+i*qb;
        const Ordinal qipjp = j+1+(i+1)*qb;
        fprintf(fp,"\n%llu %llu %llu %llu",(unsigned long long)qij,
                (unsigned long long)qipj,(unsigned long long)qipjp,
                (unsigned long long)qijp);
      }
    break;
  case 't': // paraview element type
    for (Ordinal i=0; i<qa-1; i++)
      for (Ordinal j=0; j<qb-1; j++) {
        if (c++%5==0) fprintf(fp,"\n");
        fprintf(fp,"%d ",VTK_QUAD);
      }
    break;
  case 'o': // paraview offset
    for (Ordinal i=0, q=4; i<qa-1; i++)
      for (Ordinal j=0; j<qb-1; j++) {
        if (c++%5==0) fprintf(fp,"\n");
        fprintf(fp,"%llu ",(unsigned long long)q);
        q+=4;
      }
    break;
  case 'f': // Tecplot footer
    break;
  default:
    throw DGM::exception("Illegal flag in Tri::output with value "
                         +asString(flag));
  }
}

//============================================================================
//                       Norm and Error routines
//============================================================================

Scalar Tri::norm_Linf() const {
  return norm_inf(u);
}

void Tri::norm_L2(Scalar *L2, Scalar *area) const {
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
  dvmul( u, u, f );            // f = u^2
  *L2 = dot( b, f );           // integrate
  *area = sum( b );
}

Scalar Tri::norm_L2() const {
  Scalar L2, area;
  norm_L2( &L2, &area );
  return sqrt(L2/area);
}

void Tri::norm_H1(Scalar *H1, Scalar *area) const {
  dVector ux(n1_wk,qtot), uy(n2_wk,qtot),  du2(n3_wk,qtot);
  gradient( u, ux, uy );   // compute x and y derivatives
  dvmul( ux, ux, ux );     // ux = ux^2
  dvmul( uy, uy, uy );     // uy = uy^2
  dvadd( ux, uy, du2 );    // du2 = ux^2 + uy^2

#ifdef DGM_USE_WJ
  const dVector &b = geom->wJ;
#else
  const dVector &wa = psi->wa;
  const dVector &wb = psi->wb;
  const dVector &J = geom->J;

  dVector b(g1_wk,qtot);
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
  dVector f(g2_wk,qtot);
  dvmul(  u,  u,  f );     // f  = u^2
  dvadd(du2,  f,  f );     // f  = u^2 + ux^2 + uy^2

  *H1 = dot( b, f );       // integrate
  *area = sum( b );
}

Scalar Tri::norm_H1() const {
  Scalar H1, area;
  norm_H1( &H1, &area );
  return sqrt(H1/area);
}

Scalar Tri::integrate( Scalar *area ) const {
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

Scalar Tri::integrate( const dVector &v, Scalar *area ) const {
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
  return dot( b, v );                      // integrate
}

void Tri::get_weight_props(Topology::ElementType& e, bool& c,
                           Ordinal& porder) const {
  e = Topology::Tri;
  c = true; // assume affine by default
  if (curve.get()) c = false;  // non-affine element
  porder = pOrder();
}

/// Returns the relative cost of this element's computations
/** This is a first step towards having a self tuning, load balancing
    code. See the more detailed comments in Quad.cpp. */
int Tri::get_weight() const {
  static Ordinal Pmax = 20;
  static int Weight[21][2] = {
      { 61,   1},
      {116,  84},
      {132,  90},
      {156, 115},
      {170, 138},
      {199, 155},
      {221, 172},
      {249, 213},
      {270, 242},
      {319, 282},
      {309, 319},
      {351, 380},
      {382, 423},
      {449, 496},
      {468, 541},
      {537, 772},
      {573, 880},
      {625, 944},
      {625, 956},
      {697, 1112},
      {806, 1218}};
  int cflag = 0;
  if (curve.get()) cflag = 1;
  if (pOrder() > Pmax) {
    cout << "WARNING - Tri::get_weight(): "
         << "pOrder (="<<pOrder()<<") > Pmax (="<<Pmax<<")"<< endl;
    return Weight[Pmax][cflag];
  } else
    return Weight[pOrder()][cflag];
}

Scalar Tri::compute_measure() const {
#ifdef DGM_USE_WJ
  const dVector &b = geom->wJ;
#else
  const dVector &wa = psi->wa;
  const dVector &wb = psi->wb;
  const dVector &J = geom->J;

  dVector b(n1_wk,qtot);
  dMatrix B(b,qa,qb);
  dVector f(n2_wk,qtot);

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
  return sum( b );    // integrate
}

Scalar Tri::L2_inner_product(const Element *el, Scalar *area) const {
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
  dvmul( el->u, u, f );      // f = u*el->u
  if (area) *area = sum( b );
  return dot( b, f );    // integrate
}

Scalar Tri::L2_inner_product(const dVector& vh, const dVector& wh,
                             Scalar *area) const {
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
  dvmul( vh, wh, f );      // f = vh*wh
  if (area) *area = sum( b );
  return dot( b, f );    // integrate
}

void Tri::get_side_Ds(const int sid, const dVector& dv, dVector& dv_s) const {
  Ordinal p, q;
  assert((dVector::size_type)edge[sid].qtot()==dv.size());
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
    im = get_interpolation_matrix(qb, (Ordinal)dv.size(), Interp::G2GL);
    mvmult( *im,dv,tmp1);
    for(q=0; q<qb; q++)
      for (p=0; p<qa; p++)
        wk[q + p * qb] = tmp1[p];
    break;
  case 1:
    tmp1.resize(qb);
    im = get_interpolation_matrix(qb, (Ordinal)dv.size(), Interp::G2GRJ);
    mvmult( *im,dv,tmp1);
    for(p=0;p<qa;p++)
      for (q=0; q<qb; q++)
        wk[q + p * qb] = tmp1[q];
    break;
  case 2:
    tmp1.resize(qb);
    im = get_interpolation_matrix(qb, (Ordinal)dv.size(), Interp::G2GRJ);
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
  scale(-1.0,fx_s);             // -ny*f_x
  dvvtvp(edge[sid].nx(),fy_s,fx_s,dv_s);
  return ;
}

void Tri::get_side_curvature( const int sid, dVector &dcurv) const {
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
        cerr << "Tri::get_side_curvature -- singular curvature radius"<<endl;
        DGM::Comm::World->exit(DGM::FAILURE);
      }
      dcurv[i] = dtheta/ds;
    }
  } else  //straight side
    dcurv = 0.0;
}

#if 0  // SSC: turned off until we can get it working

/// Get a 1d derivative matrix
/** \warning Something wrong in getting the geometry information...?

           /\
          /  \       y
       2 /    \ 1    |
        /______\     |
           0         +----x

          ||
          \/

           b
           |             Edge Order:  0) bottom {0,1}
       3-------2                      1) right  {1,2}
       |   |   |                      2) left   {3,0}
     2 |   +---|-- a
       |       | 1
       0-------1
          0
*/
void Tri::get_D1( const int sid, dMatrix &dm1) const {
#if 1
  cerr << "Tri::get_D1(const int, dMatrix& ) undefined" << endl;
  DGM::Comm::World->exit(DGM::FAILURE);
#else
  dVector wk;
  dVector tmp1,tmp2;
  dMatrix *im;
  switch(sid) {
  case 0:
    dm1.resize(qa,qa);
    dm1 = D->Da;
    dm1*= 2.0/(1.0 - psi->zb[0]);
    if (!curve.get()) {           // straight sided element
      wk.resize(1);
      tmp1.resize(1);
      tmp1 = side[sid]->ny(0);
      wk = geom->rx[0];
      tmp1[0]*=wk[0]; // ny*r_x

      tmp2.resize(1);
      tmp2 = side[sid]->nx(0);
      wk = geom->ry[0];
      tmp2[0]*=wk[0]; // nx*r_y

      tmp2[0] -=tmp1[0]; //-ny*r_x + nx*r_y

      dm1 *= tmp2[0];
    } else {
      wk.resize(qa);
      tmp1.resize(qa);
      tmp1 = side[sid]->ny();
      get_side(geom->rx,sid,wk);
      dvmul(wk,tmp1); // ny*r_x

      tmp2.resize(qa);
      tmp2 = side[sid]->nx();
      get_side(geom->ry,sid,wk);
      dvmul(wk,tmp2); // nx*r_y

      daxpy(-1.0,tmp1,tmp2); //-ny*r_x + nx*r_y

      for(Ordinal i=0;i<qa;i++)
      for(Ordinal j=0;j<qa;j++)
      dm1[i][j] = tmp2[j]*D->Da[i][j];
    }
#if 0
    dMatrix wk1(Lwk,qa,qa);
    //Interpolation matrix from Gauss-Lobatto to interior
    im = get_interpolation_matrix(qa, side[sid]->qtot, Interp::G2GL);
    matmult(dm,*im,wk1);
    //Interpolation matrix from interior to Gauss-Lobatto
    im = get_interpolation_matrix( side[sid]->qtot, qa, Interp::GL2G);
    matmult(*im,wk1,dm);
#endif
    break;
  case 1:
  case 2:
    dm1.resize(qb,qb);
    dm1 = D->Db;
    if (!curve.get()) {           // straight sided element
      wk.resize(1);
      tmp1.resize(1);
      tmp1 = side[sid]->ny(0);
      wk = geom->sx[0];
      tmp1[0]*=wk[0]; // ny*s_x

      tmp2.resize(1);
      tmp2 = side[sid]->nx(0);
      wk = geom->sy[0];
      tmp2[0]*=wk[0]; // nx*s_y

      tmp2[0] -=tmp1[0]; //-ny*s_x + nx*s_y

      dm1 *= tmp2[0];
    } else {
      wk.resize(qb);
      tmp1.resize(qb);
      tmp1 = side[sid]->ny();
      get_side(geom->sx,sid,wk);
      dvmul(wk,tmp1); // ny*s_x

      tmp2.resize(qb);
      tmp2 = side[sid]->nx();
      get_side(geom->sy,sid,wk);
      dvmul(wk,tmp2); // nx*s_y

      daxpy(-1.0,tmp1,tmp2); //-ny*s_x + nx*s_y

      for(Ordinal i=0;i<qb;i++)
      for(Ordinal j=0;j<qb;j++)
      dm1[i][j] = tmp2[j]*D->Db[i][j];
    }
#if 0
    dMatrix wk2(Lwk,qb,qb);
    //Interpolation matrix from Gauss-Lobatto to interior
    im = get_interpolation_matrix(qb, side[sid]->qtot, G2GRJ);
    matmult(dm,*im,wk2);
    //Interpolation matrix from interior to Gauss-Lobatto
    im = get_interpolation_matrix( side[sid]->qtot, qb, GRJ2G);
    matmult(*im,wk2,dm);
#endif
    break;
  default:
    cerr << "Tri::get_D1 -- unknown side = " << sid << endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
#endif
}

#endif  // 1d derivative is turned off

/// Zero all modes but the constant
void Tri::make_constant() {
  //cout << "Tri::make_constant()" <<endl;
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

/// Zero all modes greater than np
void Tri::low_modes(const Ordinal inp) {
  // cout << "Tri::low_modes()" <<endl;
  const Ordinal np = numeric_cast<Ordinal>(inp);
  if (np>=pOrder()) return;  // nothing to do
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

/// Zero the constant mode (only)
void Tri::kill_constant() {
  bool needs_transform = false;
  if (state == Physical) {
    forward_transform();
    needs_transform = true;
  }
  uh[0] = 0.0;
  if (needs_transform)
    backward_transform();
}

/// Transform, zero low modes, and backward transform supplied vector
void Tri::fine_scales_transform(const int p_inc, dVector &vh) const {
  //cout << "Tri::fine_scales_transform(const int p, dVector &vh)" <<endl;
  Ordinal i, j, n;
  this->forward_transform(vh,vh);
  // lower-left quadrant
  for (i=0; i<L()-p_inc; i++) {
    for (j=0; j<L()-p_inc; j++) {
      n = j + i*L();
      vh[n] = 0.0;
    }
  }
  this->backward_transform(vh,vh);
}

} // namespace DGM
