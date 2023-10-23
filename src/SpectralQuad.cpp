/** \file SpectralQuad.cpp
    \brief SpectralQuad Element implementation
    \author S. Scott Collis
    \author James Overfelt
    \author Thomas Smith

    SpectralQuad is a four node quadrilateral element that supports both
    affine and curved sided isoparametric mappings from the master element to
    the physical space element.

    \note A number of methods currently are Undefined and will generate
    runtime errors if called
*/

// System includes
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <vector>
#ifdef DGM_USE_GENERAL_GHOSTING
#include <boost/serialization/export.hpp>
#endif
using namespace std;

// boost includes
#include "boost/numeric/conversion/cast.hpp"
using boost::numeric_cast;

// DGM includes
#include "Comm.hpp"
#include "SpectralQuad.hpp"
#include "Polylib.tpp"
#include "Utilities.hpp"
#include "String.hpp"

#ifdef DGM_USE_GENERAL_GHOSTING
/// register class for serialization of polymorphic types
BOOST_CLASS_EXPORT_GUID(DGM::SpectralQuad, "DGM::SpectralQuad");
#endif

namespace DGM {

// define static storage

BasisDB SpectralQuad::bdb;
SpectralQuad::GeometryDB  SpectralQuad::gdb("SpectralQuad");
IMDB SpectralQuad::imdb;

Ordinal SpectralQuad::Qmax = 0;
Ordinal SpectralQuad::Lmax = 0;
dVector SpectralQuad::g1_wk;
dVector SpectralQuad::g2_wk;

dVector SpectralQuad::n1_wk;
dVector SpectralQuad::n2_wk;
dVector SpectralQuad::Lwk;

bool SpectralQuad::first_warn(true);

#ifdef DGM_USE_MD_COUPLE

/// Constructor for coupled physics (experimental only)
/*! \param[in] ID    - Local element id
    \param[in] P     - Polynomial order
    \param[in] X     - Vector of points defining the vertices
    \param[in] model - Model type */
SpectralQuad::SpectralQuad(const Ordinal ID, const Ordinal P,
                           const vector<Point> &X,
                           const Model::Type model)
  : BaseQuad(ID,Basis::Lagrange) {
  nVerts(4);
  nEdges(4);
  nFaces(1);
  nSides(4);
  pOrder(P);
  L(P+1);
  nModes(L()*L());
  modeltype = model;

  if (P==0) throw DGM::exception("Spectral elements must have P>0");

  // for spectral elements the quadrature is always Q = L = P + 1
  qa = qb = L(); qc = 0;
  qtot = qa * qb;

  make_workspace(qtot,nModes);

  // construct vertex data-structure
  for (Ordinal i = 0; i < nVerts(); ++i){
    Vertex v(i,lid(),X[i]);
    vert.push_back(v);
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
  uh.alias(u,nModes);
#endif

  // construct edge data-structure
  edge.reserve(nEdges());
  for (Ordinal i=0; i<nEdges(); ++i) {
    const int qedg = (i==0 || i==2) ? qa : qb;
    Edge ed(i,id,nModes,qedg,modeltype);
    edge.push_back(ed);
    side.push_back(&(edge[i]));
  }
}

#else  // !DGM_USE_MD_COUPLE

/// Constructor
/*! \param[in] ID    - Local element id
    \param[in] P     - Polynomial order
    \param[in] X     - Vector of points defining the vertices */
SpectralQuad::SpectralQuad(const Ordinal ID, const Ordinal P,
                           const vector<Point> &X)
  : BaseQuad(ID,Basis::Lagrange) {
  // cout << "SpectralQuad constructor for element " << ID << endl;
  nVerts(4);
  nEdges(4);
  nFaces(1);
  nSides(4);
  pOrder(P);
  L(P+1);
  nModes(L()*L());

  if (P==0) throw DGM::exception("Spectral elements must have P>0");

  // for spectral elements the quadrature is always Q = L = P + 1
  qa = qb = L(); qc = 0;
  qtot = qa * qb;

  make_workspace(qtot,nModes());

  // construct vertex data-structure
  vert.resize(nVerts());
  for (Ordinal i=0; i<nVerts(); ++i){
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
  edge.reserve(nEdges());
  for (Ordinal i=0; i<nEdges(); ++i) {
    const Ordinal qedg = (i==0 || i==2) ? qa : qb;
    Edge ed(i,this,nModes(),qedg,true);
    edge.push_back(ed);
    side.push_back( &(edge[i]) );
  }
}

#endif  // DGM_USE_MD_COUPLE

/// Copy constructor -- This should not allocate new space for P, M, etc.
SpectralQuad::SpectralQuad(const SpectralQuad *E) {
  // cout << "SpectralQuad copy constructor for Eid = " << E->id << endl;

  // allocate storage for solution at quadrature points
  u.resize(E->u.size());

  // allocate modal coefficients
  uh.alias(u,E->uh.size());

  *this = *E;  // only copies pointers -- be careful -- use shared_ptr

  // allocate storage for edges
  for (Ordinal i=0; i<nEdges(); ++i) {
    // cout << "Edge = " << i << ", qtot = " <<  edge[i].qtot() << endl;
    edge[i].u.resize(edge[i].qtot());
    edge[i].u = 0.0;
    side[i] = &(edge[i]);
#ifdef DGM_ALLOW_HANGING_NODES
    for (size_t j=0; j<side[i]->subsides().size(); j++) {
      Side *ss = side[i]->subsides()[j]->deep_copy();
      side[i]->subsides()[j].reset(ss);
      ss->u.resize(ss->qtot());
      ss->u = 0.0; 
    }    
#endif
  }

  // initialize values
  state = Undefined;
  u = 0.0;
}

/// Destructor
SpectralQuad::~SpectralQuad() {
  // cout << DGM::Comm::World->MyPID() << " ~SpectralQuad: eid= " << id << endl;
}

/// Retrieves a basis from the basis database
/** If the basis is not in the database, makes a new basis and adds to
    database
    \todo Switch to a non-string key like the interpolation matrix. */
Basis* SpectralQuad::get_basis(const int der=0) const {
  // cout << "SpectralQuad::get_basis" << endl;
  Basis* b;
  char buf[128];
  sprintf(buf,"%lld_%llu_%d_%llu_%llu_%llu",
      (long long)type,(long long unsigned)L(),der,
      (long long unsigned)qa,(long long unsigned)qb,(long long unsigned)qc);
  string key = buf;
  BasisDB::iterator p = bdb.bases.find(key);
  if ( p == bdb.bases.end() ) {                    // not found, make a new one
    b = new Basis(L(),qa,qb,qc,nModes());
    make_basis(b,type,der);
    bdb.bases[key] = b;
  } else {                                         // found, return the basis
    b = p->second;
  }
  return b;
}

/// Gets the mass matrix for this SpectralQuad
/** \note For spectral elements the mass matrix is always diagonal and this
    routine actually computes the inverse of the mass matrix. */
void SpectralQuad::get_mass_matrix() {
  // cout << "SpectralQuad::get_mass_matrix for element " << id << endl;
  M.reset( new Minfo );
  M->mat.resize(1,nModes());
  dVector f(qtot);
  dVector fh(f,nModes());
  for (Ordinal m=0; m<nModes(); m++) {
    fill( psi->mode[m], f );
    inner_product(f, fh);
    M->mat[0][m] = fh[m];
  }
  // cout << "Mass matrix for elmt " << gid() << endl << M->mat << endl;
  for (Ordinal j=0; j<nModes(); j++) M->mat[0][j] = one/M->mat[0][j];
}

/// Resets the mass matrix using a weighted mass matrix
/** \warning Might be dangerous to reset the mass matrix to this new value */
void SpectralQuad::get_mass_matrix(const dVector &x) {
  DGM_UNDEFINED;
}

/// Solves the mass matrix
/** \note For spectral elements, the mass matrix is always diagonal. */
void SpectralQuad::solve_mass_matrix(dVector &fh) const {
  for (Ordinal i=0; i<nModes(); i++) fh[i] *= M->mat[0][i];
}

//=============================================================================

/// Computes the normal gradient on a supplied side
/** \note Be careful as we use n1_wk and n2_wk here. */
void SpectralQuad::normal_times_gradient_side(const dVector &f, const int sid,
                                              dVector &fssum ) const {
  DGM_UNDEFINED;
}

/// Computes a mass matrix but does not factor it
/** \warning Might be dangerous to reset the mass matrix to this new value. */
void SpectralQuad::get_local_mass_matrix(const dVector &factor) {
  DGM_UNDEFINED;
}

/// Computes the local derivative matrix
void SpectralQuad::get_local_derivative_matrix() {
  // cout << "SpectralQuad::get_mass_matrix for element " << id << endl;
  DGM_UNDEFINED;
}

/// Computes the local derivative matrix
void SpectralQuad::get_local_derivative_matrix(const dVector &factor) {
  DGM_UNDEFINED;
}

/// Computes the local Laplace matrix
void SpectralQuad::get_local_laplace_matrix() {
  DGM_UNDEFINED;
}

/// Computes the local Laplace matrix
void SpectralQuad::get_local_laplace_matrix(const dVector & factor) {
  DGM_UNDEFINED;
}

//=============================================================================

/// Fill element with a function string
void SpectralQuad::fill(string function_string, Operation operation) {
  state = Physical;
  parser_init();
  Parser::VectorFunction f("x", "y", "t", function_string );
  f.evaluate( C->x, C->y, u, 0.0, convert(operation) );
  state = Physical;
}

/// Fill element with a mode
void SpectralQuad::fill(Mode &v) {
  // cout << "SpectralQuad::fill(Mode &)" << endl;
  dMatrix U(u,qa,qb);
  for (Ordinal i=0; i<qa; i++)
    for (Ordinal j=0; j<qb; j++) {
      // cout << "i, j = " << i << ", " << j << endl;
      U[i][j] = v.a[i] * v.b[j];
    }
  state = Physical;
}

/// Fill a vector with a mode
void SpectralQuad::fill(Mode &v, dVector &f) const {
  // cout << "SpectralQuad::fill(Mode &, dVector &)" << endl;
  dMatrix F(f,qa,qb);
  for (Ordinal i=0; i<qa; i++)
    for (Ordinal j=0; j<qb; j++) {
      F[i][j] = v.a[i] * v.b[j];
    }
}

/// Fill element with a random polynomial
void SpectralQuad::random() {
  // cout << "SpectralQuad::random()" << endl;
  state = Physical;
  for (Ordinal i=0; i<nModes(); i++) uh[i] = Element::random(-one,one);
}

/// Set the modes of an element
void SpectralQuad::set(const dVector &fh, const Ordinal nModes_) {
  // cout << "SpectralQuad::set(const dVector &, const int)" << endl;
  const Ordinal L_ = static_cast<Ordinal>(sqrt(static_cast<Scalar>(nModes_)));
  const Ordinal Lm = min(L(),L_);
  dVector Uh, Fh;
  for (Ordinal i=0, m=0, m_=0; i<Lm; i++) {
    Uh.alias( uh, m, L() );
    Fh.alias( fh, m_, L_ );
    for (Ordinal j=0; j<Lm; j++) Uh[j] = Fh[j];
    m += L();
    m_ += L_;
  }
  state = Transform;
  // cout<<"Eid = "<<id<<", |mode(nModes())| = "<<fabs(uh(nModes()-1))<<endl;
}

/// Compute the inner product with the Basis
void SpectralQuad::inner_product() {
  // cout << "SpectralQuad::inner_product for Eid = " << id << endl;
  inner_product(u, uh);
  state = Transform;
}

/// Computes the inner product of the supplied vector against the Basis
void SpectralQuad::inner_product(dVector &f, dVector &fh) const {
  // cout << "SpectralQuad::inner_product for Eid = " << id << endl;
  const dMatrix &phia = psi->Ba;
  const dMatrix &phib = psi->Bb;
  dMatrix wk(Lwk,L(),qb);
  dMatrix F(f,qa,qb);
  dMatrix Fh(fh,L(),L());
#ifdef DGM_USE_WJ
  const dVector &wJ = geom->wJ;
  dvmul( wJ, f );
#else
  const dVector &wa = psi->wa;
  const dVector &wb = psi->wb;
  const dVector &J = geom->J;
  dvmul( J, f );
  for(Ordinal j=0; j<qb; j++) {
    dSlice column(F.column(j));
    dvmul( wa, column );
  }
  for(Ordinal i=0; i<qa; i++) {
    dVector row(F.row(i));
    dvmul( wb, row );
  }
#endif
  matmult( phia, F, wk);          // wk[La][qb] = Ba[La][qa] * F[qa][qb]
  matmult( wk, 'T', phib, Fh);    // Fh[La][Lb] = wk[La][qb] * (Bb[Lb][qb])^T
}

/// Transform the Element to polynomial space
void SpectralQuad::forward_transform() {
  // cout << "SpectralQuad::forward_transform" << endl;
  if (state == Transform) {
    cerr << "SpectralQuad::transform -- already in transform space"<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  forward_transform(u,uh);
  state = Transform;
}

/// Transform the supplied data to polynomial space
void SpectralQuad::forward_transform(dVector &f, dVector &fh) const {
  // cout << "SpectralQuad::forward_transform" << endl;
  //inner_product(f,fh);
  //solve_mass_matrix(fh);
}

/// Transform using another Elements mass matrix (dangerous)
void SpectralQuad::forward_transform(Element *F, Element *) {
  // cout << "SpectralQuad::forward_transform(*F,*)" << endl;
  DGM_UNDEFINED;
  if (state == Transform) {
    cerr << "SpectralQuad::transform -- already in transform space"<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  inner_product(u,uh);
  F->solve_mass_matrix(uh);  // Use element F's Mass matrix
  state = Transform;
}

/// Return Element to physical space
void SpectralQuad::backward_transform() {
  if (state == Physical) {
    cerr << "SpectralQuad::transform_to_physical -- already in "
      "physical space"<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  //backward_transform( uh, u );
  state = Physical;
}

/// Transform supplied data to physical space on this Element
void SpectralQuad::backward_transform(dVector &fh, dVector &f) const {
#if 1
  return;
#else
  const dMatrix &phia = psi->Ba;
  const dMatrix &phib = psi->Bb;
  dMatrix Fh(fh,L(),L());
  dMatrix F(f,qa,qb);
#if 1
  dMatrix wk(Lwk,qa,L());
  matmult( 'T', phia, Fh, wk);   // wk[qa][Lb] = (Ba[La][qa])^T * Fh[La][Lb]
  matmult(  wk, phib,  F);       //  F[qa][qb] = wk[qa][Lb] * Bb[Lb][qb]
#else
  dMatrix wk(Lwk,L(),qb);
  matmult( Fh, phib, wk);        // wk[La][qb] = Fh[La][Lb] * Bb[Lb][qb]
  matmult( 'T', phia, wk, F);    //  F[qa][qb] = (Ba[La][qa])^T * wk[La][qb]
#endif
#endif
}

/// Transform from physical space to Legendre coefficients
void SpectralQuad::L_forward_transform() {
#if 1
  // This does a linear transform which is what we want
  Minfo &Vi = psi->Vi;
  if (Vi.mat.size()==0) {
    Mode *mode = new Mode[L()*L()]; // setup modal access pointers
    for (Ordinal i=0, m=0; i<L(); i++) {
      for (Ordinal j=0; j<L(); m++, j++) {
        mode[m].a.alias( psi->ga[i] );
        mode[m].b.alias( psi->gbv[j] );
      }
    }
    Vi.mat.resize(nModes(),nModes());
    dVector Vcol(qtot);
    for (Ordinal j=0; j<nModes(); ++j) {
      fill( mode[j], Vcol );
      for (Ordinal i=0; i<qtot; i++) Vi.mat[i][j] = Vcol[i];
    }
    if (LU_factor(Vi.mat, Vi.pivots)!=0)
      DGM::Comm::World->error("SpectralQuad::L_forward_transform -- "
                              "LU_factor of Vandermonde failed.");
    delete[] mode;
  }
  LU_solve(Vi.mat, Vi.pivots, uh);
#else
  // This does an L2 projection which is not really what we want
  const dMatrix &phia = psi->Ga;
  const dMatrix &phib = psi->Gb;
  dMatrix wk(Lwk,L(),qb);
  dMatrix F(u,qa,qb);
  dMatrix Fh(uh,L(),L());
#ifdef DGM_USE_WJ
  const dVector &wJ = geom->wJ;
  dvmul( wJ, u );
#else
  const dVector &wa = psi->wa;
  const dVector &wb = psi->wb;
  const dVector &J = geom->J;
  dvmul( J, u );
  for(Ordinal j=0; j<qb; j++) {
    dSlice column(F.column(j));
    dvmul( wa, column );
  }
  for(Ordinal i=0; i<qa; i++) {
    dVector row(F.row(i));
    dvmul( wb, row );
  }
#endif
  matmult( phia, F, wk);          // wk[La][qb] = Ba[La][qa] * F[qa][qb]
  matmult( wk, 'T', phib, Fh);    // Fh[La][Lb] = wk[La][qb] * (Bb[Lb][qb])^T
#endif
}

/// Transform from Legendre coefficients to physical space
void SpectralQuad::L_backward_transform() {
  const dMatrix &phia = psi->Ga;
  const dMatrix &phib = psi->Gb;
  dMatrix Fh(uh,L(),L());
  dMatrix F(u,qa,qb);
  dMatrix wk(Lwk,qa,L());
  matmult('T', phia, Fh, wk);   // wk[qa][Lb] = (Ba[La][qa])^T * Fh[La][Lb]
  matmult(wk, phib, F);         //  F[qa][qb] = wk[qa][Lb] * Bb[Lb][qb]
}

/// Extracts data onto a specified Side
void SpectralQuad::get_side( const dVector &from, const Ordinal sid,
                             dVector &to ) const {
  // cout<<"SpectralQuad::get_side() Element = "<<id<<" Side = "<<sid<<endl;
  switch(sid) {
  case 0: {
    const Ordinal q = 0;
    for (Ordinal p=0; p<qa; p++) to[p] = from[q + p * qb];
    break;
  }
  case 1: {
    const Ordinal p = qa-1;
    for (Ordinal q=0; q<qb; q++) to[q] = from[q + p * qb];
    break;
  }
  case 2: {
    const Ordinal q = qb-1;
    for (Ordinal p=0; p<qa; p++) to[p] = from[q + p * qb];
    break;
  }
  case 3: {
    const Ordinal p = 0;
    for (Ordinal q=0; q<qb; q++) to[q] = from[q + p * qb];
    break;
  }
  default:
    throw DGM::exception("SpectralQuad::get_side -- unknown side");
  }
}

/// Makes an interpolation matrix
void SpectralQuad::make_interpolation_matrix(const Ordinal q1,
                                             const Ordinal q2,
                                             const Interp::Type interp,
                                             dMatrix &im ) {
  //cout << "SpectralQuad::make_interpolation_matrix" << endl;
  im.resize(q1,q2);
  dVector z1(q1), z2(q2), w1(q1), w2(q2);
  Scalar delta;
  switch(interp){
  case(Interp::GL2G):
    zwgll(z2,w2);         // Gauss-Lobatto-Legendre
    zwgl (z1,w1);         // Gauss-Legendre
    igllm(im,z2,z1);      // Interpolation matrix
    break;
  case(Interp::G2GL):
    zwgl (z2,w2);         // Gauss-Legendre
    zwgll(z1,w1);         // Gauss-Lobatto-Legendre
    iglm(im,z2,z1);       // Interpolation matrix
    break;
  case(Interp::GL2GL):    // This is needed for variable q order on edges
    zwgll(z2,w2);         // Gauss-Lobatto-Legendre
    zwgll(z1,w1);         // Gauss-Lobatto-Legendre
    igllm(im,z2,z1);      // Interpolation matrix
    break;
  case(Interp::GL2U):
    zwgll(z2,w2);
    delta=two/(Scalar)(q1);
    for(Ordinal i=0; i<q1; ++i) z1[i] = i*delta - one + pt5*delta;
    igllm(im,z2,z1);
    break;
  case(Interp::GL2M2GL): {
    const Ordinal L1 = q1;
    const Ordinal L2 = q2;

    dMatrix GL2G (q2,q2);
    dMatrix G2M  (L2,q2);
    dMatrix I    (L1,L2);
    dMatrix M2GL (L1,q1);

    dMatrix GL2L (L1,q2);
    dMatrix GL2M (q2,q2);

    dVector zgll(q2), zgl(q2), wgll(q2), wgl(q2);
    zwgll(zgll,wgll);           // Gauss-Lobatto-Legendre
    zwgl (zgl, wgl);            // Gauss-Legendre
    igllm(GL2G,zgll,zgl);       // Interpolation matrix

    Basis::make_Legendre(0, L2, q2, zgl, G2M);
    for (Ordinal i=0; i<L2; i++) {
      for (Ordinal j=0; j<q2; j++) {
        G2M(i,j) *= wgl(j);
      }
    }

    if (q1 > q2) {
      cerr << "SpectralQuad::make_interpolation_matrix - Invalid "
              "q1,q2 order" << endl;
      DGM::Comm::World->exit(DGM::FAILURE);
    }

    I=0.0;
    for (Ordinal i=0; i<min(L1,L2); i++) I(i,i) = 1.0;

    {
      zwgll(z1,w1);           // Gauss-Lobatto-Legendre
      Basis::make_Legendre(0, L1, q1, z1, M2GL);
    }

    //im = M2GL^T x I x G2M x GL2G
    matmult(G2M,GL2G,GL2M);
    matmult(I,GL2M,GL2L);
    matmult('T', M2GL, GL2L, im);
    break;
    }
  case(Interp::G2M2GL): {
    const Ordinal L1 = q1;
    const Ordinal L2 = q2;

    dMatrix G2M  (L2,q2);
    dMatrix I    (L1,L2);
    dMatrix M2GL (L1,q1);

    dMatrix IG2M (L1,q2);

    dVector zgll(q2), zgl(q2), wgll(q2), wgl(q2);
    zwgll(zgll,wgll);           // Gauss-Lobatto-Legendre
    zwgl (zgl, wgl);            // Gauss-Legendre

    Basis::make_Legendre(0, L2, q2, zgl, G2M);
    for (Ordinal i=0; i<L2; i++) {
      for (Ordinal j=0; j<q2; j++) {
        G2M(i,j) *= wgl(j);
      }
    }

    if (q1 > q2) {
      cerr << "SpectralQuad::make_interpolation_matrix - Invalid "
              "q1,q2 order" << endl;
      DGM::Comm::World->exit(DGM::FAILURE);
    }

    I=0.0;
    for (Ordinal i=0; i<min(L1,L2); i++) I(i,i) = 1.0;

    {
      zwgll(z1,w1);           // Gauss-Lobatto-Legendre
      Basis::make_Legendre(0, L1, q1, z1, M2GL);
    }

    //im = M2GL^T x I x G2M
    matmult(I,G2M,IG2M);
    matmult('T', M2GL, IG2M, im);
    break;
    }
  case(Interp::GL2M): {
    dMatrix GL2G (q1,q1);
    dMatrix G2M  (q1,q1);

    dMatrix GL2M (q1,q1);

    dVector zgll(q1), zgl(q1), wgll(q1), wgl(q1);
    zwgll(zgll,wgll);           // Gauss-Lobatto-Legendre
    zwgl (zgl, wgl);            // Gauss-Legendre
    igllm(GL2G,zgll,zgl);       // Interpolation matrix

    Basis::make_Legendre(0, q1, q1, zgl, G2M);

    for (Ordinal i=0; i<q1; i++) {
      for (Ordinal j=0; j<q1; j++) {
        G2M(i,j) *= wgl(j);
      }
    }

    //im = GL2M = G2M x GL2G
    matmult(G2M,GL2G,im);
    break;
    }
  case(Interp::M2GL): {

    zwgll(z1,w1);           // Gauss-Lobatto-Legendre
    Basis::make_Legendre(0, q1, q1, z1, im);

    break;
    }
  default:
    cerr << "SpectralQuad::make_interpolation_matrix - Invalid "
      "interpolation type" << endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
}

/// Returns an interpolation matrix (making one if needed)
dMatrix* SpectralQuad::get_interpolation_matrix(const Ordinal q1,
                                                const Ordinal q2,
                                                const Interp::Type interp=
                                                Interp::GL2GL) {
  //cout << "SpectralQuad::get_interpolation_matrix" << endl;
  dMatrix* im;
  IMinfo key(interp,q1,q2);                 // make a unique key
  IMDB::iterator p = imdb.entry.find(key);
  if ( p == imdb.entry.end() ) {            // not found, make a interpolation
    im = new dMatrix;
    make_interpolation_matrix(q1,q2,interp,*im);
    imdb.entry[key] = im;
  } else {                                  // found, return the interpolation
    im = p->second;
  }
  return im;
}

/// Interpolate supplied physical space values "f" to the sides.
void SpectralQuad::fill_sides(const dVector &f) {
  // cout << "fill_sides on element " << gid() << endl;
  dVector wka(g1_wk,qa);
  dVector wkb(g2_wk,qb);
  dMatrix *im;

  for (unsigned i=0; i<4; ++i) {
    dVector &wk     = (0==i || 2==i) ? wka : wkb;
    const Ordinal q = (0==i || 2==i) ?  qa :  qb;
    const bool    G = (side[i]->link && !side[i]->link->Gauss_Lobatto()) ||
                     (!side[i]->link &&
                       side[i]->base && !side[i]->base->Gauss_Lobatto());

    if (side[i]->qtot() != q || G) {
      const Interp::Type interp = G ? Interp::GL2G : Interp::GL2GL;
      im = get_interpolation_matrix( side[i]->qtot(), q, interp);
      get_side(f,i,wk);
      mvmult( *im, wk, side[i]->u );
    } else {
      get_side(f,i,side[i]->u);
    }
  }
#ifdef DGM_ALLOW_HANGING_NODES
  push_to_subsides();
#endif
}

/// Interpolate physical space values "f" to a uniform mesh on the sides.
/** \todo Make a load_sides_uniform() that, similar to load_sides() fills a
    supplied side data-structure instead of the current sides. */
void SpectralQuad::fill_sides_uniform(const dVector &f) {
  dVector wka(g1_wk,qa);
  dVector wkb(g2_wk,qb);
  dMatrix *im;
  im = get_interpolation_matrix( side[0]->qtot(), qa, Interp::GL2U);
  get_side(f,0,wka);
  mvmult( *im, wka, side[0]->u );

  im = get_interpolation_matrix( side[1]->qtot(), qb, Interp::GL2U);
  get_side(f,1,wkb);
  mvmult( *im, wkb, side[1]->u );

  im = get_interpolation_matrix( side[2]->qtot(), qa, Interp::GL2U);
  get_side(f,2,wka);
  mvmult( *im, wka, side[2]->u );

  im = get_interpolation_matrix( side[3]->qtot(), qb, Interp::GL2U);
  get_side(f,3,wkb);
  mvmult( *im, wkb, side[3]->u );

#ifdef DGM_ALLOW_HANGING_NODES
  push_to_subsides();
#endif
}

/// Fill Element Sides with a flux vector
void SpectralQuad::fill_sides(const dVector &fx, const dVector &fy) {
  dVector wka(g1_wk,qa);
  dVector wkb(g2_wk,qb);
  dVector wk;
  dMatrix *im;

  Interp::Type interp[4];
  for (unsigned i=0; i<4; ++i) {
    const bool G  = (side[i]->link && !side[i]->link->Gauss_Lobatto()) ||
                   (!side[i]->link &&
                     side[i]->base && !side[i]->base->Gauss_Lobatto());
    interp[i] = G ? Interp::GL2G : Interp::GL2GL;
  }

  im = get_interpolation_matrix( edge[0].qtot(), qa, interp[0]);
  wk.alias(Lwk,edge[0].qtot());
  get_side(fx,0,wka);
  mvmult( *im, wka, edge[0].u );
  get_side(fy,0,wka);
  mvmult( *im, wka, wk );
  dvmul( edge[0].nx(), edge[0].u );
  dvvtvp( edge[0].ny(), wk, edge[0].u, edge[0].u );

  im = get_interpolation_matrix( edge[1].qtot(), qb, interp[1]);
  wk.alias(Lwk,edge[1].qtot());
  get_side(fx,1,wkb);
  mvmult( *im, wkb, edge[1].u );
  get_side(fy,1,wkb);
  mvmult( *im, wkb, wk );
  dvmul( edge[1].nx(), edge[1].u );
  dvvtvp( edge[1].ny(), wk, edge[1].u, edge[1].u );

  im = get_interpolation_matrix( edge[2].qtot(), qa, interp[2]);
  wk.alias(Lwk,edge[2].qtot());
  get_side(fx,2,wka);
  mvmult( *im, wka, edge[2].u );
  get_side(fy,2,wka);
  mvmult( *im, wka, wk );
  dvmul( edge[2].nx(), edge[2].u );
  dvvtvp( edge[2].ny(), wk, edge[2].u, edge[2].u );

  im = get_interpolation_matrix( edge[3].qtot(), qb, interp[3]);
  wk.alias(Lwk,edge[3].qtot());
  get_side(fx,3,wkb);
  mvmult( *im, wkb, edge[3].u );
  get_side(fy,3,wkb);
  mvmult( *im, wkb, wk );
  dvmul( edge[3].nx(), edge[3].u );
  dvvtvp( edge[3].ny(), wk, edge[3].u, edge[3].u );

#ifdef DGM_ALLOW_HANGING_NODES
  push_to_subsides();
#endif
}

/** Interpolate physical space values "f" to the side Gauss Points, but
    store the result in vector g. */
void SpectralQuad::load_side(const dVector &f, const Ordinal side_number,
                             dVector &g) const {
  get_side(f,side_number,g);
}

/// Compute coordinates of quadrature points
void SpectralQuad::get_coordinates() {
  //  cout << "SpectralQuad::get_coordinates for element " << id << endl;
  if (curve.get())
    get_curved_coordinates();
  else
    get_straight_coordinates();
}

/// Compute coordinates for a straight-sided Element
void SpectralQuad::get_straight_coordinates() {
  // cout << "SpectralQuad::get_straight_coordinates for element " << id
  //      << endl;
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
        const Ordinal q = j + i*qb;
        C->x[q] += vert[n]->x * phi[i][j];
        C->y[q] += vert[n]->y * phi[i][j];
      }
    }
  }
}

/// Transform from C^0 modified Jacobi basis to physical space
/** This is primarily used to work with curved elements to transform the
    quadrature points from the reference coordinates to physical space. */
void SpectralQuad::J_backward_transform(dVector &fh, dVector &f) {
  // cout << "SpectralQuad::J_backward_transform for elmt = " << id << endl;
  dMatrix B;
  dMatrix Fh( fh, L(), L() );                     // Fh[Lb,La]
  dMatrix  F( f, qa, qb);                         // F[qa,qb]
  dMatrix wk( Lwk, L(), qa );                     // wk[Lb,qa]
  B.alias( psi->amem, L(), qa );                  // B[La,qa]
  matmult( Fh, B, wk );
  B.alias( psi->bmem, L(), qb );                  // B[Lb,qb]
  matmult( 'T', wk , B, F );
}

/// Computes the curved nodal coordinates
/** \pre Must have a valid and populated Curve datastructure for this
    element. */
void SpectralQuad::get_curved_coordinates() {
  // cout << "SpectralQuad::get_curved_coordinates()" << endl;
  Ordinal i, j, l, m;
  C.reset( new Coord(qtot) ); *C = 0;
  dVector fh(nModes());
  fh = 0;

  // copy xh into fh (lay 'a' modes first -- opposite of Tri's)
  l = m = 0;
  fh[m++] = vert[0]->x;
  fh[m++] = vert[1]->x;
  if (curve->side == 0)
    for (i=0; i<L()-2; i++)
      fh[m++] = curve->xh[i];
  else
    for (i=0; i<L()-2; i++)
      fh[m++] = 0.0;

  fh[m++] = vert[3]->x;
  fh[m++] = vert[2]->x;
  if (curve->side == 2)
    for (i=0; i<L()-2; i++)
      fh[m++] = curve->xh[i];
  else
    for (i=0; i<L()-2; i++)
      fh[m++] = 0.0;

  if (curve->side == 3)
    for (i=0, l=m; i<L()-2; l+=L(), i++)
      fh[l] = curve->xh[i];
  else
    for (i=0, l=m; i<L()-2; l+=L(), i++)
      fh[l] = 0.0;

  m++;
  if (curve->side == 1)
    for (i=0, l=m; i<L()-2; l+=L(), i++)
      fh[l] = curve->xh[i];
  else
    for (i=0, l=m; i<L()-2; l+=L(), i++)
      fh[l] = 0.0;

  m++;
  for (i=0; i<L()-2; m+=L(), i++)
    for (j=0, l=m; j<L()-2; l++, j++)
      fh[l] = 0.0;

  J_backward_transform( fh, C->x );
  fh = 0.0;

  // copy yh into fh (lay 'a' modes first -- opposite of Tri's)
  l = m = 0;
  fh[m++] = vert[0]->y;
  fh[m++] = vert[1]->y;
  if (curve->side == 0)
    for (i=0; i<L()-2; i++)
      fh[m++] = curve->yh[i];
  else
    for (i=0; i<L()-2; i++)
      fh[m++] = 0.0;

  fh[m++] = vert[3]->y;
  fh[m++] = vert[2]->y;
  if (curve->side == 2)
    for (i=0; i<L()-2; i++)
      fh[m++] = curve->yh[i];
  else
    for (i=0; i<L()-2; i++)
      fh[m++] = 0.0;

  if (curve->side == 3)
    for (i=0, l=m; i<L()-2; l+=L(), i++)
      fh[l] = curve->yh[i];
  else
    for (i=0, l=m; i<L()-2; l+=L(), i++)
      fh[l] = 0.0;

  m++;
  if (curve->side == 1)
    for (i=0, l=m; i<L()-2; l+=L(), i++)
      fh[l] = curve->yh[i];
  else
    for (i=0, l=m; i<L()-2; l+=L(), i++)
      fh[l] = 0.0;

  m++;
  for (i=0; i<L()-2; m += L(), i++)
    for (j=0, l=m; j<L()-2; l++, j++)
      fh[l] = 0.0;

  J_backward_transform( fh, C->y );
}

/// Get the coordinates on a side
/** \todo Change the Point* to a Coord. */
void SpectralQuad::get_side_coordinates(const Ordinal nedge, Point *pedge) const {
  dVector px, py;
  px.resize(edge[nedge].qtot());
  py.resize(edge[nedge].qtot());

  if (nedge>3) {
    cerr << "SpectralQuad::get_side_coordinates illegal edge id." << endl;
    DGM::Comm::World->exit();
  }

  const bool G=(side[nedge]->link && !side[nedge]->link->Gauss_Lobatto()) ||
              (!side[nedge]->link &&
                side[nedge]->base && !side[nedge]->base->Gauss_Lobatto());

  Ordinal q = (nedge==0 || nedge==2) ? qa:qb;

  if (edge[nedge].qtot() != q || G) {
    dVector wka;
    dMatrix *im;
    const Interp::Type interp = G ? Interp::GL2G : Interp::GL2GL;
    im = get_interpolation_matrix(edge[nedge].qtot(), q, interp);
    wka.resize(q);

    get_side(C->x,nedge,wka);  // wk is at Gauss-Lobatto points
    mvmult( *im, wka, px);     // interpolate
    get_side(C->y,nedge,wka);
    mvmult( *im, wka, py );
    for(Ordinal i=0; i<edge[nedge].qtot(); i++) pedge[i] = Point(px[i],py[i]);
  } else {
    get_side(C->x,nedge,px);
    get_side(C->y,nedge,py);
    for(Ordinal i=0; i<edge[nedge].qtot(); i++) pedge[i] = Point(px[i],py[i]);
  }
}

/// Compute the geometric factors for the element
void SpectralQuad::compute_geometry() {
  //  cout << "SpectralQuad::compute_geometry for element " << id() << endl;
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

/** Determine, consistent with the tolerances used in compute_straight_geometry
    whether this is an affine element. */
bool SpectralQuad::is_affine() const {
  // cout << "SpectralQuad::is_affine element " << gid() << endl;

  // compute coordinate gradients in mapped space
  const Scalar pt5 = 0.5;
  Scalar xr = (vert[1]->x - vert[0]->x)*pt5;
  Scalar xs = (vert[3]->x - vert[0]->x)*pt5;
  Scalar yr = (vert[1]->y - vert[0]->y)*pt5;
  Scalar ys = (vert[3]->y - vert[0]->y)*pt5;

  using CMC::approx_equal;
  const Scalar ABS = pow(numeric_limits<Scalar>::epsilon(),pt66);
  const Scalar REL = sqrt(numeric_limits<Scalar>::epsilon());
  bool result =
      approx_equal(xr,(vert[2]->x-vert[3]->x)*pt5,REL,ABS) &&
      approx_equal(xs,(vert[2]->x-vert[1]->x)*pt5,REL,ABS) &&
      approx_equal(yr,(vert[2]->y-vert[3]->y)*pt5,REL,ABS) &&
      approx_equal(ys,(vert[2]->y-vert[1]->y)*pt5,REL,ABS);
  return result;
}

/// Compute the geometric factors
/** This version is only correct for affine elements (use curved_geometry
    otherwise). */
void SpectralQuad::compute_straight_geometry() {
  // cout<<"SpectralQuad::compute_straight_geometry for element "<<gid()<<endl;

  // compute coordinate gradients in mapped space
  const Scalar pt5 = 0.5;
  Scalar xr = (vert[1]->x - vert[0]->x)*pt5;
  Scalar xs = (vert[3]->x - vert[0]->x)*pt5;
  Scalar yr = (vert[1]->y - vert[0]->y)*pt5;
  Scalar ys = (vert[3]->y - vert[0]->y)*pt5;

#ifdef DGM_CHECK_CONSTANT_JACOBIAN
  // check to make sure that the Jacobian is constant
  const Scalar ABS = pow(numeric_limits<Scalar>::epsilon(),pt66);
  const Scalar REL = sqrt(numeric_limits<Scalar>::epsilon());
  if ( !CMC::approx_equal(xr,(vert[2]->x - vert[3]->x)*pt5,REL,ABS) ||
       !CMC::approx_equal(xs,(vert[2]->x - vert[1]->x)*pt5,REL,ABS) ||
       !CMC::approx_equal(yr,(vert[2]->y - vert[3]->y)*pt5,REL,ABS) ||
       !CMC::approx_equal(ys,(vert[2]->y - vert[1]->y)*pt5,REL,ABS)  ) {
    cerr << "ERROR:  SpectralQuad::compute_straight_geometry()" << endl
         << "        Jacobian is not constant for Element " << gid() << endl;
    cout << "  xr = " << xr << " : " << xr-(vert[2]->x - vert[3]->x)*pt5<<endl;
    cout << "  xs = " << xs << " : " << xs-(vert[2]->x - vert[1]->x)*pt5<<endl;
    cout << "  yr = " << yr << " : " << yr-(vert[2]->y - vert[3]->y)*pt5<<endl;
    cout << "  ys = " << ys << " : " << ys-(vert[2]->y - vert[1]->y)*pt5<<endl;
    cerr << "This means that you have a non-affine element in your mesh "
        "that you are\n treating as a straight sided parallelogram.  "
        "Revise/correct your mesh for this\n element or declare this "
        "element as a \"Straight\" element in your root.crv\n file."<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
#endif

  // compute determinate of the Jacobian
  Scalar detJ = xr*ys - xs*yr;
  if (detJ <= 0.0) {
    cerr << "Element " << gid() <<" has a nonpositive Jacobian" << endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  geom->J = detJ;
  geom->rx =  ys / detJ;
  geom->ry = -xs / detJ;
  geom->sx = -yr / detJ;
  geom->sy =  xr / detJ;

#ifdef DGM_USE_WJ
  const dVector &wa = psi->wa;
  const dVector &wb = psi->wb;
  dVector &b = geom->wJ;
  dMatrix B(b,qa,qb);
  b = detJ;
  for(Ordinal j=0; j<qb; j++) {
    dSlice column(B.column(j));
    dvmul( wa, column );
  }
  for(Ordinal i=0; i<qa; i++) {
    dVector row(B.row(i));
    dvmul( wb, row );
  }
  dvsqrt( b, geom->srwJ );
  geom->isrwJ = one;
  dvdiv( geom->srwJ, geom->isrwJ );
#endif
#ifdef DGM_STORE_METRICS
  compute_metrics();
#endif
}

/// Compute the geometric factors
/** This version is valid for general curved elements using an isoparametric
    mapping. */
void SpectralQuad::compute_curved_geometry() {
  // cout<<"SpectralQuad::compute_curved_geometry for element "<<gid()<<endl;

  // temporary storage
  dVector xr(qtot), xs(qtot);
  dVector yr(qtot), ys(qtot);

  // compute coordinate gradients in mapped space
  local_gradient( C->x, xr, xs );
  local_gradient( C->y, yr, ys );

  // compute determinate of the Jacobian
  dvmul( xs, yr, geom->J );
  scale( -one, geom->J );
  dvvtvp( xr, ys, geom->J, geom->J);

  for (Ordinal i=0; i<qtot; i++) {
    if(geom->J[i] <= 0.0)
      cerr << "Element " << gid() <<" has a nonpositive Jacobian" << endl;
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
  b = geom->J;
  for(Ordinal j=0; j<qb; j++) {
    dSlice column(B.column(j));
    dvmul( wa, column );
  }
  for(Ordinal i=0; i<qa; i++) {
    dVector row(B.row(i));
    dvmul( wb, row );
  }
  dvsqrt( b, geom->srwJ );
  geom->isrwJ = one;
  dvdiv( geom->srwJ, geom->isrwJ );
#endif
#ifdef DGM_STORE_METRICS
  compute_metrics();
#endif
}

/// Compute the stability metrics for timestep size calucations.
Element::StabMetrics SpectralQuad::compute_metrics() {
  return compute_metrics_2d_tensor_prod();
}

/// Computes geometric factors for the Element Sides
// This is called at startup so we could always use the expensive
// interpolation by default.

void SpectralQuad::compute_side_geometry() {
     //cout << "SpectralQuad::compute_side_geometry(), Eid = "<< gid() << endl;
  sigma(0.0);
  for (Ordinal i=0; i<nEdges(); i++) {
    Edge &e = edge[i];
    const Ordinal qedg = e.qtot();
    // cout << "Edge " << i << ", qedg = " << qedg << endl;
    const Ordinal q = (i==0 || i==2) ? qa : qb;
    dMatrix &Der = (i==0 || i==2) ? D->Da : D->Db;
    dVector wk(q);

    const bool G =  (e.link && !e.Gauss_Lobatto()) ||
                   (!e.link &&
                     e.base && !e.Gauss_Lobatto());

    if (qedg == q && !G) {
      switch(i) {
      case 0:
        get_side(geom->sx,i,edge[i].nx());
        scale( -one, edge[i].nx() );       // negate since on bottom
        get_side(geom->sy,i,edge[i].ny());
        scale( -one, edge[i].ny() );
        break;
      case 1:
        get_side(geom->rx,i,edge[i].nx());
        get_side(geom->ry,i,edge[i].ny());
        break;
      case 2:
        get_side(geom->sx,i,edge[i].nx() );
        get_side(geom->sy,i,edge[i].ny() );
        break;
      case 3:
        get_side(geom->rx,i,edge[i].nx() );
        scale( -one, edge[i].nx() );       // negate since on left
        get_side(geom->ry,i,edge[i].ny() );
        scale( -one, edge[i].ny() );
        break;
      }

      dVector interior_J(qedg);
      get_side(geom->J,i,interior_J);

      // make normals have unit length
      for (Ordinal j=0; j<qedg; j++) {
        Scalar len = sqrt( edge[i].nx(j)*edge[i].nx(j) +
            edge[i].ny(j)*edge[i].ny(j) );
        edge[i].nx(j) /= len;
        edge[i].ny(j) /= len;
  #ifdef DGM_SPECTRALQUAD_DEBUG
        cout << "Element = " << gid() << ", edge = " << i << ", q = " << j
            << ", (nx,ny) = " << edge[i].nx(j) << ", " << edge[i].ny(j)
            << ", int_J = " << interior_J[j] << endl;
  #endif
      }

      // get coordinates along the edge
      dVector x(q);
      dVector y(q);
      get_side(C->x,i,wk);
      mvmult( Der, wk, x );
      get_side(C->y,i,wk);
      mvmult( Der, wk, y );
      dvmul( x, x, x);          // x = x^2
      dvvtvp( y, y, x, x );     // x = x^2 + y^2
      dvsqrt( x, edge[i].J() ); // wk = sqrt(x)

      // Save off interior_Jcoefficients
      edge[i].J_orig() .resize(edge[i].J().size());
      edge[i].J_scale().resize(edge[i].J().size());
      edge[i].J_orig()  = edge[i].J();
      edge[i].J_scale() = interior_J;

      // divide the side Jacobian by the interior Jacobian
      dvdiv( interior_J, edge[i].J() );

      // WARNING: This is done so that you can use an interior integration to
      // perform the surface integration.  For this to work you must use an
      // interior quadrature rule that includes the boundaries and you must
      // divide the edge contributions by the integration weight in the other
      // direction(s).

    } else {
      const Interp::Type interp = G ? Interp::GL2G : Interp::GL2GL;
      dMatrix *im;
      im = get_interpolation_matrix( qedg, q, interp);  // to, from

      switch(i) {
      case 0:
        get_side(geom->sx,i,wk);         // wk is at Gauss-Lobatto points
        mvmult( *im, wk, edge[i].nx() );   // interpolate to Gauss-Lobatto qedg
        scale( -1.0, edge[i].nx() );       // negate since on bottom
        get_side(geom->sy,i,wk);
        mvmult( *im, wk, edge[i].ny() );
        scale( -1.0, edge[i].ny() );
        break;
      case 1:
        get_side(geom->rx,i,wk);
        mvmult( *im, wk, edge[i].nx() );
        get_side(geom->ry,i,wk);
        mvmult( *im, wk, edge[i].ny() );
        break;
      case 2:
        get_side(geom->sx,i,wk);
        mvmult( *im, wk, edge[i].nx() );
        get_side(geom->sy,i,wk);
        mvmult( *im, wk, edge[i].ny() );
        break;
      case 3:
        get_side(geom->rx,i,wk);
        mvmult( *im, wk, edge[i].nx() );
        scale( -1.0, edge[i].nx() );       // negate since on left
        get_side(geom->ry,i,wk);
        mvmult( *im, wk, edge[i].ny() );
        scale( -1.0, edge[i].ny() );
        break;
      }

      dVector interior_J(qedg);
      get_side(geom->J,i,wk);            // interpolate interior J to edge
      mvmult( *im, wk, interior_J );

      // make normals have unit length
      for (Ordinal j=0; j<qedg; j++) {
        Scalar len = sqrt( edge[i].nx(j)*edge[i].nx(j) +
            edge[i].ny(j)*edge[i].ny(j) );
        edge[i].nx(j) /= len;
        edge[i].ny(j) /= len;
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

      // interpolate from q GL to qedg GL points
      mvmult( *im, wk, edge[i].J() );

      // Save off interior_Jcoefficients
      edge[i].J_orig() .resize(edge[i].J().size());
      edge[i].J_scale().resize(edge[i].J().size());
      edge[i].J_orig()  = edge[i].J();
      edge[i].J_scale() = interior_J;

      // divide the side Jacobian by the interior Jacobian
      dvdiv( interior_J, edge[i].J() );

      // WARNING: This is done so that you can use an interior integration to
      // perform the surface integration.  For this to work you must use an
      // interior quadrature rule that includes the boundaries and you must
      // divide the edge contributions by the integration weight in the other
      // direction(s).
    }

    // store the max ratio of side to element Jacobians
    e.h_n_inv(0.0);
    for (Ordinal k=0; k<qedg; ++k) {
      const Scalar Jedge = fabs(edge[i].J(k));
      sigma(max(sigma(), Jedge));
      e.h_n_inv(max(e.h_n_inv(), 0.5*Jedge));
    }

    // compute and store the Edge measure for each Side
    dVector p(qedg); p = one;
    e.measure(compute_side_integral(p,i));
  }
}

/// Transform a vector to the edge basis
void SpectralQuad::forward_transform_side(dVector &f, dVector &fh) {
  // cout << "SpectralQuad::forward_transform_side(), Eid = "<< id << endl;
  Basis *b = psi;
  dVector &wa=b->wa;
  fh.resize(L()-2);
  // subtract off vertices
  daxpy( -f[0], b->vertMode(0).a, f );
  daxpy( -f[qa-1], b->vertMode(1).a, f);
  // inner product
  dvmul( wa, f );
  for (Ordinal i=0; i<L()-2; i++)
    fh[i] = dot( b->edgeMode(0,i).a, f );
  if (L()-2) solve_1d_mass_matrix(fh);
}

/// Solve a 1d (edge) mass matrix for forward_transform_side()
void SpectralQuad::solve_1d_mass_matrix(dVector &fh) const {
  Minfo M1d;
  get_1d_mass_matrix(M1d);
#ifdef DGM_CHOLESKY_MASS_MATRIX
  Cholesky_solve(M1d.mat, fh);
#else
  LU_solve(M1d.mat, M1d.pivots, fh);
#endif
}

/// Compute the 1d mass matrix for curved sides
void SpectralQuad::get_1d_mass_matrix(Minfo &M1d) const {
  dVector &wa=psi->wa;
  dVector w, psi1, psi2, tmp(qa-2);
  M1d.mat.resize(L()-2,L()-2);
  M1d.pivots.resize(L()-2);
  for (Ordinal i=0; i<L()-2; i++) {
    w.alias(wa,1,qa-2);
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

/// Compute a integral of supplied data, f, on specified side
Scalar SpectralQuad::compute_side_integral( dVector &f, Ordinal sid ) const {
  Ordinal qsid = side[sid]->qtot();
  dvmul( side[sid]->J(), f);
  const Ordinal q = (sid==0 || sid==2) ? qa:qb;

  const bool G = (side[sid]->link && !side[sid]->link->Gauss_Lobatto()) ||
                (!side[sid]->link &&
                  side[sid]->base && !side[sid]->base->Gauss_Lobatto());

  if (q != qsid || G) {
    dVector wk(q);
    get_side(geom->J,sid,wk);       // extract interior J on edge
    dVector wks(qsid);  // interior_J

    const Interp::Type interp = G ? Interp::GL2G : Interp::GL2GL;
    const dMatrix *const im = get_interpolation_matrix( qsid, q, interp);
    mvmult( *im, wk, wks );
    dvmul( wks, f );
  } else {
    dVector interior_J(qsid);
    get_side(geom->J,sid,interior_J);
    dvmul( interior_J, f );
  }
  dVector z(qsid), w(qsid);
  if(G) zwgl (z,w);                 // Gauss-Legendre
  else  zwgll(z,w);                 // Gauss-Lobatto-Legendre
  Scalar I = dot( f, w );
  return I;
}

/// Return the measure (parameter in this case) of the elements sides
Scalar SpectralQuad::compute_side_measure() const {
  Scalar result=0.0;
  for (Ordinal sid=0; sid<nSides(); sid++) {
    Ordinal qsid = side[sid]->qtot();
    dVector p(qsid);
    p = 1.0;
    result += compute_side_integral(p,sid);
  }
  return result;
}

/// Add a Dirac delta
/** Add a discrete version of a Dirac delta function at a quadrature point
    with amplitude equal amp.  This is done exactly -- no quadrature. */
void SpectralQuad::add_Dirac_delta(const Ordinal qpt, const Scalar amp) {
  assert( qpt >= 0 && qpt < qtot );
#ifdef DGM_USE_WJ
  u[qpt] += amp/geom->wJ[qpt];
#else
  // recover i and j from qpt=j+i*qb;
  const Ordinal j = qpt % qb;
  const Ordinal i = (qpt-j)/qb;
  const Scalar wght = (psi->wa[i])*(psi->wb[j]);
  u[qpt] += amp/(wght*geom->J[qpt]);
#endif
}

/// Add a Dirac delta
/** Add a discrete version of a Dirac delta function at an arbitrary point
    p with amplitude equal amp. The Point, p, must be within the SpectralQuad
    element. */
void SpectralQuad::add_Dirac_delta(const Point &p, const Scalar amp) {
  Scalar r, s;
  // First get the local coordinate on line
  if(!get_local_coordinates(p,r,s)) {
    DGM::Comm::World->cerr()<<
      "SpectralQuad::Add_Dirac_delta: could not find (r,s)"<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  const Point q(r,s);
  return add_local_Dirac_delta(q,amp);
}

void SpectralQuad::add_local_Dirac_delta(const Point &p, const Scalar amp) {
  const Scalar r=p.x;
  const Scalar s=p.y;
  dMatrix imx, imy;
  dVector za(qa), wa(qa);
  dVector zb(qb), wb(qb);
  // Compute Gauss-Lobatto-Legendre points and weights
  zwgll(zb,wb); // y direction
  zwgll(za,wa); // x direction

  // Form the interpolation matrix from Gauss-Lobatto-Legendre
  imy.resize(1,qb);
  igllm(imy,zb,s);

  imx.resize(1,qa);
  igllm(imx,zb,r);

  // Apply the Dirac delta function operator
  for (Ordinal i=0; i<qa; i++) {
    for (Ordinal j=0; j<qb; j++) {
      const Ordinal qpt = j+i*qb;
      const Scalar im = imx(0,i)*imy(0,j);
#ifdef DGM_USE_WJ
      u[qpt] += im*amp/geom->wJ[qpt];
#else
      const Scalar wght = (psi->wa[i])*(psi->wb[j]);
      u[qpt] += im*amp/(wght*geom->J[qpt]);
#endif
    }
  }
}

void SpectralQuad::add_local_Dirac_delta(const vector<dMatrix> &M,
                                         const Scalar amp) {
  if (2!=M.size())
    error("SpectralQuad::add_local_Dirac_delta: Incorrect matrix size.");
  if (M[0].rows() != M[1].rows())
    error("SpectralQuad::add_local_Dirac_delta: Inconsistant matrix size.");
  if (M[0].cols() != qb || M[1].cols() != qa)
    error("SpectralQuad::add_local_Dirac_delta: Inconsistant matrix size.");

  const dMatrix &imy = M[0];
  const dMatrix &imx = M[1];

  // Apply the Dirac delta function operator
  for (Ordinal i=0; i<qa; i++) {
    for (Ordinal j=0; j<qb; j++) {
      const Ordinal qpt = j+i*qb;
      const Scalar im = imx(0,i)*imy(0,j);
#ifdef DGM_USE_WJ
      u[qpt] += im*amp/geom->wJ[qpt];
#else
      const Scalar wght = (psi->wa[i])*(psi->wb[j]);
      u[qpt] += im*amp/(wght*geom->J[qpt]);
#endif
    }
  }
}

/// Extract the solution at the Point p
Scalar SpectralQuad::interpolate_point(const Point &p) const {
  Scalar r, s;
  // SSC: the get_local_coordinates methods are expensive.  Since the probe
  // points don't move, we could cache this for each probe point so that they
  // don't have to be recomputed every time that Response::probe(...) gets
  // called
  if(!get_local_coordinates(p,r,s)) {
    DGM::Comm::World->cerr()
      <<"SpectralQuad::interpolate_point: could not find (r,s)"<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  const Point q(r,s);
  return interpolate_local_point(q);
}

/// Extract the solution at the Point p
Scalar SpectralQuad::interpolate_local_point(const Point &p) const {

  const Scalar r=p.x;
  const Scalar s=p.y;
  dMatrix im;
  dVector iv;

  // SSC: we should consider building these interpolation operators once and
  // then have a fast apply method to use them.

  // 2D interpolation in the b-direction

  // Form the interpolation matrix (vector) from Gauss-Lobatto-Legendre to s
  iv.resize(qb);
  im.alias(iv,1,qb); // view vector as row matrix
  const dVector &zb=psi->zb; // Gauss-Lobatto-Legendre points
  igllm(im,zb,s);

  // Interpolate to temporary points at y=s at each x location
  dVector tmp(qa);
  dMatrix U(u,qa,qb); // view u vector as matrix
  mvmult( U, iv, tmp);

  // 1D interpolation in the a-direction

  // Form the interpolation matrix from Gauss-Lobatto-Legendre to r
  iv.resize(qa);
  im.alias(iv,1,qa); // view vector as row matrix
  const dVector &za=psi->za; // Gauss-Lobatto-Legendre points
  igllm(im,za,r);

  // interpolate along our temporary y points to get the value at r,s
  const Scalar result = dot(iv, tmp);

  return result; // the interpolated solution is returned
}

void SpectralQuad::calculate_interpolation_matrices(vector<dMatrix> &M,
                                             const vector<Point>& P) const {
  const Ordinal N = numeric_cast<Ordinal>(P.size());

  M.resize(2);
  M[0].resize(N,qb);
  M[1].resize(N,qa);

  dVector z(qb), w(qb);
  zwgll(z, w);
  dVector X(N);

  for (Ordinal i=0; i<N; ++i) X[i] = P[i].y;
  igllm(M[0],z,X);

  if (qa != qb) {
    z.resize(qa); w.resize(qa);
    zwgll(z,w);
  }
  for (Ordinal i=0; i<N; ++i) X[i] = P[i].x;
  igllm(M[1],z,X);
}

void SpectralQuad::apply_interpolation_matrices(dVector &V,
                                         const vector<dMatrix> &M) const {

  if (state != Physical) {
    cerr << "Quad::interpolate_points -- not in physical space"<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  if (2!=M.size())
    error("Quad::apply_interplation_matrices: Incorrect matrix size.");
  if (M[0].rows() != M[1].rows())
    error("Quad::apply_interplation_matrices: Inconsistent matrix size.");
  Ordinal sqb = qb, sqa = qa;
  if (M[0].cols() != sqb || M[1].cols() != sqa)
    error("Quad::apply_interplation_matrices: Inconsistent matrix size.");

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
void SpectralQuad::interpolate_points(const vector<Point> &ps,
                                      dVector &vals) const {
  if (state != Physical) {
    cerr << "SpectralQuad::interpolate_points -- not in physical space"<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }

  vals.resize(numeric_cast<Ordinal>(ps.size()));

  for (size_t ip = 0; ip != ps.size(); ip++) {
    const Point& p = ps[ip];
    const Scalar r = p.x;
    const Scalar s = p.y;

    dVector tmp(qa), result(1);

    // 2D interpolation
    dVector z2(qb), w2(qb);
    // Compute Gauss-Lobatto-Legendre points and weights
    zwgll(z2,w2); // y direction
    // Form the interpolation matrix from Gauss-Lobatto-Legendre to s
    dMatrix im(1,qb);
    igllm(im,z2,s);
    // Interpolate to temporary points at y=s at each x location
    for (Ordinal i=0;i<qa;i++) {
      // Now get the solution values at the appropriate quadrature points.
      // We need to get qb values starting at i*qb
      //tmpy.alias(const_cast<dVector&>(el->u),i*qb,qb);  // watch out
      dVector tmpy;
      tmpy.alias(u,i*qb,qb);  // watch out
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
    // the interpolated solution is stored
    vals(numeric_cast<Ordinal>(ip)) = result[0];
  }
}

namespace {

void subside_lift(dVector       &in,
                  const Element *const U,
                  const Element *const F,
                  const Basis   *psi,
                  const Ordinal  e,
                  const Ordinal  q,
                  const Ordinal  qedg,
                  const char     dir)
{
  const Ordinal  L = psi->Ba.rows();
  const Ordinal qa = psi->Ba.cols();
  const Ordinal qb = psi->Bb.cols();
  const vector<Side::Ptr> &Uss = U->side[e]->subsides();
  const vector<Side::Ptr> &Fss = F->side[e]->subsides();

  unsigned len=0;
  for (size_t s=0; s<Uss.size(); ++s) {
    len += Uss[s]->u.size();
  }
  dVector f(len);
  dVector X(len);
  len = 0;
  // collect up all the integration data for each subside into one long
  // vector and do the integration all at once.  This is just replacing
  // a sum over each subside with a big sum over all the subsides for
  // efficiency.
  //for (size_t s=Uss.size()-1; 0<=s; --s) {
  for (size_t s=Uss.size(); s-- > 0; ) {
    const Side *uss = Uss[s].get();
    const Ordinal sub_len = uss->u.size();
    if (uss->J().size() != sub_len) {
      cerr<<DGM::Comm::World->MyPID() <<" "
        <<__FILE__<<":"<<__LINE__<<" Aborting!"<<endl;
      error("SpectralQuad::subside_lift: bad Jacobi size");
    }
    if (uss->u.size() != sub_len) {
      cerr<<__FILE__<<":"<<__LINE__<<" Aborting!"<<endl;
      cerr<<" uss->u.size()"<<uss->u.size()<<" != sub_len:"<<sub_len<<endl;
      error("SpectralQuad::subside_lift: bad buffer size");
    }
    vector<Scalar> w(sub_len);
    dVector x(sub_len);
    {
      vector<Scalar> t(sub_len);
      zwgll(&t[0],&w[0],sub_len);
    }
    {
      dVector z(qedg);
      dVector t(qedg);
      zwgll(&z[0],&t[0],qedg);
      // Push the Gauss-Lobatto-Legendre subside integration points
      // to the Quad frame of reference so the Legendre
      // Polynomials can be evaluated at these points.
      uss->push_to_subside(z,x);
    }
    if (uss->J_orig().size() < sub_len) {
      cerr<<__FILE__<<":"<<__LINE__<<" Aborting!"<<endl;
      error("SpectralQuad::subside_lift: J_orig buffer size");
    }
    for (Ordinal i=0; i<sub_len; ++i) {
      // The function we want to integrate is the difference in flux
      // across the boundary times the Jacobi weights times the
      // integration weights with an optional dotted to normal vector
      f[len+i]  = Fss[s]->u[i] - uss->u[i];
      if (uss->J()[i] < .000001) {
        cerr<<DGM::Comm::World->MyPID() <<" "
           <<__FILE__<<":"<<__LINE__<<" Aborting!"<<endl;
        cerr<<" uss->J["<<i<<"]:"<<uss->J()[i]<<" <  .000001"<<endl;
        error("SpectralQuad::subside_lift: bad Jacobian");
      }
      if (     w[i] < .000001) {
        cerr<<__FILE__<<":"<<__LINE__<<" Aborting!"<<endl;
        cerr<<" w["<<i<<"]:"<<w[i]<<" <  .000001"<<endl;
        error("SpectralQuad::subside_lift: bad weight");
      }
      if      (dir == 'x') f[len+i] *= uss->nx()[i];
      else if (dir == 'y') f[len+i] *= uss->ny()[i];
      f[len+i] *= w[i];
      f[len+i] *= uss->J_orig()[i];
      // collect up the side integration points w.r.t the owning
      // quad.
      X[len+i] = x[i];
    }
    len += sub_len;
  }

  const dVector &wa = psi->wa;
  const dVector &wb = psi->wb;

  switch (e) {
    case 0: scale( one/wb[0],    f ); break;
    case 1: scale( one/wa[qa-1], f ); break;
    case 2: scale( one/wb[qb-1], f ); break;
    case 3: scale( one/wa[0],    f ); break;
  }


  // So we want to do the integral over the first L Legendre polynomials, P_l
  // over the sum of the subside lengths.  This is how the coefficients of the
  // Legendre modal basis are determined.  There are a total of 'len' Gauss
  // points over the whole of all the subsides and these are defined at the
  // points X_i.  Thus the 'B' matrix is L rows and len columns.
  dVector g(L);
  {
    dMatrix X2M2GL (L,len);
    dMatrix M2GL(L,L);
    dMatrix X2M (L,len);
    Basis::make_Legendre(0,L,len,X,X2M);

    dVector z1(L), w1(L);
    zwgll(z1,w1); 
    Basis::make_Legendre(0, L, L, z1, M2GL);
  
    matmult('T', M2GL, X2M, X2M2GL);
    mvmult (  X2M2GL, f, g);
  }

  dMatrix In(in,L,L);
  switch (e) {
  case 0: { 
      dSlice col(In.column(0));
      dvadd( g, col );
    }
    break;
  case 1: {
      dVector row(In.row(qa-1));
      dvadd( g, row );
    }
    break;
  case 2: {
      dSlice col(In.column(qb-1));
      dvadd( g, col );
    }
    break;
  case 3: {
      dVector row(In.row(0));
      dvadd( g, row );
    }
    break;
  }
}

}  // anonymous namespace

/// Adds the surface contribution for a DG method
/** F->edges holds the upwind flux at the Gauss points
    U->edges holds the interior flux at the Gauss points. */
void SpectralQuad::lift(const Element *const F, dVector &in, const char dir) const {
  // cout << "SpectralQuad::lift for Eid = "<<gid()<<endl;
#ifdef DGM_TIME_QUAD
  static FunctionTimer T("SpectralQuad::lift");
  FunctionSentry sentry(T);
#endif
  const Element *const U = this;
  const dVector &wa = U->psi->wa;
  const dVector &wb = U->psi->wb;
  dMatrix In(in,qa,qb);

  const bool no_subsides[4] = {side[0]->subsides().empty(),
                               side[1]->subsides().empty(),
                               side[2]->subsides().empty(),
                               side[3]->subsides().empty()};
  const Ordinal qedge[4] = {U->edge[0].qtot(),
                            U->edge[1].qtot(),
                            U->edge[2].qtot(),
                            U->edge[3].qtot()};

  for (Ordinal i=0; i<nEdges(); i++) {
  // Edge 0  // Conditional
    Ordinal const q = (0==i || 2==i) ? qa : qb;
    Ordinal const qedg = U->edge[i].qtot();
    dVector f(g1_wk,qedg);
    dvsub( F->edge[i].u, U->edge[i].u, f );
    dvmul( U->edge[i].J(), f);
    if      (dir == 'x') dvmul( U->edge[i].nx(), f );
    else if (dir == 'y') dvmul( U->edge[i].ny(), f );

    const bool G = (edge[i].link && !edge[i].link->Gauss_Lobatto()) ||
                  (!edge[i].link &&
                    edge[i].base && !edge[i].base->Gauss_Lobatto());

    if (qedg != q || G) {
#ifdef DGM_SIDE_FLUX_TO_VOLUME
      const Interp::Type interp = 
         G ?
           ((q<qedg) ? Interp::G2M2GL  : Interp::G2GL ) :
           ((q<qedg) ? Interp::GL2M2GL : Interp::GL2GL);
#else
      const Interp::Type interp = G ? Interp::G2GL : Interp::GL2GL;
#endif
      dMatrix *im = get_interpolation_matrix(q, qedg, interp);
      dVector fi(g2_wk,q);
      mvmult( *im, f, fi );
      f.alias(fi);
    }
    switch(i) {
      case 0: {
        if (no_subsides[i]) {
          scale( one/wb[0], f );
          dSlice column(In.column(0));
          dvadd( f, column );
        } else {
          subside_lift(in,U,F,psi,i,qa,qedge[i],dir);
        }
      }
      break;
      case 1: {
        if (no_subsides[i]) {
          scale( one/wa[qa-1], f );
          dVector row(In.row(qa-1));
          dvadd( f,  row );
        } else {
          subside_lift(in,U,F,psi,i,qa,qedge[i],dir);
        }
      }
      break;
      case 2: {
        if (no_subsides[i]) {
          scale( one/wb[qb-1], f );
          dSlice column(In.column(qb-1));
          dvadd( f,  column );
        } else {
          subside_lift(in,U,F,psi,i,qa,qedge[i],dir);
        }
      }
      break;
      case 3: {
        if (no_subsides[i]) {
          scale( one/wa[0], f );
          dVector row(In.row(0));
          dvadd( f, row );
        } else {
          subside_lift(in,U,F,psi,i,qa,qedge[i],dir);
        }
      }
      break;
    }
  }
}

namespace {
  // SSC: Hmm, what is this stuff?  It breaks building with Teuchos::RCP
  // because for some poor reason, your cannot simply evaluate a Teuchos::RCP
  // as a conditional.  Instead, you have to use the get() method.  This is
  // very bad, in my opinion, and I have let Ross Bartlett know about this but
  // apparently it is not that easy to fix.  boost::shared_ptr does not have
  // this limitation.  I have gone ahead and fixed this code to make it work
  // both with Teuchos::RCP and boost::shared_ptr
  Element::DinfoPtr derivative_matrix_database
  (Basis *psi, Element::DinfoPtr D=Element::DinfoPtr()) {
    typedef map<Basis*,Element::DinfoPtr> DB;
    static DB database;
    if (D.get()) {
      DB::value_type p(psi,D);
      database.insert(p);
    } else {
      const DB::const_iterator p = database.find(psi);
      if (p !=  database.end()) D = p->second;
    }
    return D;
  }
}

/// Collocation derivative matrix
void SpectralQuad::get_derivative_matrix() {
  DinfoPtr db = derivative_matrix_database(psi);
  if (db.get()) {
    D = db;
  } else {
    D.reset( new Dinfo );
    derivative_matrix_database(psi,D);
    D->Da.resize(qa,qa);
    D->Dat.resize(qa,qa);
    D->Db.resize(qb,qb);
    D->Dbt.resize(qb,qb);
    dgll(D->Da,D->Dat,psi->za);
    dgll(D->Db,D->Dbt,psi->zb);
  }
}

/// Compute the gradient of the supplied vector
/** This routine computes the gradient in physical space using the chain rule

    df/dx = df/dr * dr/dx + df/ds * ds/dx
    df/dy = df/dr * dr/dy + df/ds * ds/dy
*/
void SpectralQuad::gradient( const dVector &f, dVector &fx,
                             dVector &fy ) const {
#ifdef DGM_TIME_QUAD
  static FunctionTimer T("SpectralQuad::gradient");
  FunctionSentry sentry(T);
#endif
  dMatrix F(f,qa,qb);      // matrix alias of vector
  dVector fr(g1_wk,qtot);  // use gradient workspace
  dVector fs(g2_wk,qtot);  // use gradient workspace
  dMatrix Fr(fr,qa,qb);    // matrix alias of vector
  dMatrix Fs(fs,qa,qb);    // matrix alias of vector

  matmult( D->Da, F, Fr );
  matmult( F, D->Dbt, Fs );

  dvmul ( geom->rx, fr, fx);       // fx  = rx * fr
  dvvtvp( geom->sx, fs, fx, fx );  // fx += sx * fs
  dvmul ( geom->ry, fr, fy);       // fy  = ry * fr
  dvvtvp( geom->sy, fs, fy, fy );  // fy += sy * fs
}

/// This method computes the gradient in only one direction
void SpectralQuad::gradient( const dVector &f, dVector &df, char dir) const {
  dMatrix F(f,qa,qb);      // matrix alias of vector
  dVector fr(g1_wk,qtot);  // use gradient workspace
  dVector fs(g2_wk,qtot);  // use gradient workspace
  dMatrix Fr(fr,qa,qb);    // matrix alias of vector
  dMatrix Fs(fs,qa,qb);    // matrix alias of vector

  matmult( D->Da, F, Fr );
  matmult( F, D->Dbt, Fs );

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

/// Computes the local gradient in the master element (r,s) coordinates
void SpectralQuad::local_gradient( const dVector &f, dVector &fr,
                                   dVector &fs ) const {
  dMatrix F(f,qa,qb);       // matrix alias of vector
  dMatrix Fr(fr,qa,qb);     // matrix alias of vector
  dMatrix Fs(fs,qa,qb);     // matrix alias of vector

  matmult( D->Da, F, Fr );  // df/da
  matmult( F, D->Dbt, Fs ); // df/db
}

/// Interpolate the element data to a locally uniform mesh (not implemented)
void SpectralQuad::interpolate_to_uniform() {
  cout << "SpectralQuad::interpolate_to_uniform() is not implemented" << endl;
}

/// Output a tecplot representation for this element
void SpectralQuad::tecplot(FILE *fp) {
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
  Ordinal q;
  for (Ordinal j=0; j<qb; j++) {
    for (Ordinal i=0; i<qa; i++) {
      q = j + i * qb;
      fprintf(fp,"%15.8e %15.8e %15.8e %15.8e %15.8e\n",
              C->x[q],C->y[q],u[q],ux[q],uy[q]);
    }
  }
  if (tnsf) forward_transform();
}

/// Output requested element information to a file
void SpectralQuad::binaryOutput(FILE *fp, const OutputType flag) const {
  if (state == Transform)
    throw DGM::exception("SpectralQuad::output called when in transform space");
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
    const uint32_t length = numeric_cast<uint32_t>(4*(qa-1)*(qb-1)*
        sizeof(int32_t));
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
    const uint32_t length = numeric_cast<uint32_t>((qa-1)*(qb-1)*
                                                   sizeof(int32_t));
    fwrite(&length,sizeof(uint32_t),1,fp);
    int32_t q=4;
    for (Ordinal j=0; j<qb-1; j++) {
      for (Ordinal i=0; i<qa-1; i++) {
        fwrite(&q,sizeof(int32_t),1,fp);
        q+=4;
      }
    }
    break;
  }
  case ParaviewTypes: {
    const uint32_t length = numeric_cast<uint32_t>((qa-1)*(qb-1)*
                                                   sizeof(uint8_t));
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
    error("Illegal output type requested in SpectralQuad::binaryOutput");
  }
}

/// Output requested element information to a file
streamoff SpectralQuad::binaryLength(const OutputType flag) const {
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
    error("Illegal output type requested in SpectralQuad::binaryLength");
  }
  error("Fell through case statement in SpectralQuad::binaryLength");
  return 0;
}

/// Dump requested element information to a file
void SpectralQuad::output(FILE *fp, const char flag) const {
  if (state == Transform)
    throw DGM::exception("SpectralQuad::output called when in transform space");
  Ordinal c = 0;
  switch(flag) {
  case 'h':   // Tecplot header
    fprintf(fp,"\nZONE T=\"Element %llu\", ",(unsigned long long)gid());
    fprintf(fp,"I=%llu, J=%llu, F=BLOCK",(unsigned long long)qa,
            (unsigned long long)qb);
    break;
  case 'd':   // solution
    for (Ordinal j=0; j<qb; j++)
      for (Ordinal i=0; i<qa; i++) {
        const Ordinal q = j+i*qb;
        if (c++%5==0) fprintf(fp,"\n");
        fprintf(fp,"%15.8e ",u[q]);
      }
    break;
  case 'x':   // x-coordinates
    for (Ordinal j=0; j<qb; j++)
      for (Ordinal i=0; i<qa; i++) {
        const Ordinal q = j+i*qb;
        if (c++%5==0) fprintf(fp,"\n");
        fprintf(fp,"%15.8e ",C->x[q]);
      }
    break;
  case 'y':   // y-coordinates
    for (Ordinal j=0; j<qb; j++)
      for (Ordinal i=0; i<qa; i++) {
        const Ordinal q = j+i*qb;
        if (c++%5==0) fprintf(fp,"\n");
        fprintf(fp,"%15.8e ",C->y[q]);
      }
    break;
  case 'p':   // points
    for (Ordinal j=0; j<qb; j++)
      for (Ordinal i=0; i<qa; i++) {
        const Ordinal q = j+i*qb;
        fprintf(fp,"\n%15.8e %15.8e %15.8e ",C->x[q],C->y[q],0.0);
    }
    break;
  case 'c':  // connectivity
    for (Ordinal i=0; i<qa-1; i++) {
      for (Ordinal j=0; j<qb-1; j++) {
        const Ordinal qij = j+i*qb;
        const Ordinal qipj = j+(i+1)*qb;
        const Ordinal qijp = j+1+i*qb;
        const Ordinal qipjp = j+1+(i+1)*qb;
        fprintf(fp,"\n%llu %llu %llu %llu",(unsigned long long)qij,
                (unsigned long long)qipj,(unsigned long long)qipjp,
                (unsigned long long)qijp);
      }
    }
    break;
  case 't':  // paraview element type
    for (Ordinal j=0; j<qb-1; j++)
      for (Ordinal i=0; i<qa-1; i++) {
        if (c++%5==0) fprintf(fp,"\n");
        fprintf(fp,"%d ",VTK_QUAD);
      }
    break;
  case 'o':  // paraview offset
    for (Ordinal j=0, q=4; j<qb-1; j++)
      for (Ordinal i=0; i<qa-1; i++) {
        if (c++%5==0) fprintf(fp,"\n");
        fprintf(fp,"%llu ",(unsigned long long)q);
        q+=4;
      }
    break;
  case 'f':  // Tecplot footer
    break;
  default:
    error("Illegal flag in SpectralQuad::output");
  }
}

//============================================================================
//                        Norm and Error routines
//============================================================================

/// Returns the infinity norm over the element
Scalar SpectralQuad::norm_Linf() const {
  return norm_inf(u);
}

/// Computes the L2 norm (squared) and element measure
void SpectralQuad::norm_L2(Scalar *L2, Scalar *area) const {
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
    dvmul( wb, row );
  }
#endif

  dVector f(n2_wk,qtot);
  dvmul( u, u, f );            // f = u^2

  *L2 = dot( b, f );           // integrate
  *area = sum( b );
}

/// Returns the L2 norm divided by the Element measure
Scalar SpectralQuad::norm_L2() const {
  Scalar L2, area;
  norm_L2( &L2, &area );
  return sqrt(L2/area);
}

/// Computes the H1 norm squared on the Element
void SpectralQuad::norm_H1(Scalar *H1, Scalar *area) const {
  dVector ux(n1_wk,qtot), uy(n2_wk,qtot);
  gradient( u, ux, uy );   // compute x and y derivatives
  dvmul( ux, ux );         // ux = ux^2
  dvmul( uy, uy );         // uy = uy^2
  dvadd( uy, ux );         // ux = ux^2 + uy^2
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
    dvmul( wb, row );
  }
#endif
  dVector f(g2_wk,qtot);
  dvmul(  u,  u,  f );     // f  = u^2
  dvadd( ux,  f );         // f  = u^2 + ux^2 + uy^2

  *H1 = dot( b, f );       // integrate
  *area = sum( b );
}

/// Returns the H1 norm divided by the Element measure
Scalar SpectralQuad::norm_H1() const {
  Scalar H1, area;
  norm_H1( &H1, &area );
  return sqrt(H1/area);
}

/// Integrates the data stored in the Element and optionally the volume
Scalar SpectralQuad::integrate( Scalar *area ) const {
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
    dvmul( wb, row );
  }
#endif

  if (area!=NULL) *area = sum( b );        // element area
  return dot( b, u );                      // integrate
}

/// Integrates the supplied data over the element
Scalar SpectralQuad::integrate(const dVector &v, Scalar *area) const {
#ifdef DGM_USE_WJ
  const dVector &b = geom->wJ;
#else
  dVector &wa = psi->wa;
  dVector &wb = psi->wb;
  dVector &J = geom->J;
  dVector b(n1_wk,qtot);
  dMatrix B(b,qa,qb);

  b = J;
  for(Ordinal j=0; j<qb; j++) {
    dSlice column(B.column(j));
    dvmul( wa, column );
  }
  for(Ordinal i=0; i<qa; i++) {
    dVector row(B.row(i));
    dvmul( wb, row );
  }
#endif

  if (area!=NULL) *area = sum( b );        // element area
  return dot( b, v );                      // integrate
}

/// Determine cost (weight) for this element
/** This is a first stop towards having a self tuning, load balancing code
    The data here represents measurements from the MEMS Pentium IV Cluster
    for a simple Navier_Stokes problem.  The first index is polynomial
    order, the second is a flag for curved elements.

    Ideas for improvement:
    1) Have a more flexible database that also tracks the platform
    2) Include a curve-fit to the data -- it looks quadratic so that
       extrapolation to higher orders can be reasonably done.
    3) Adjustments may be required for different problem types.
*/
void SpectralQuad::get_weight_props(Topology::ElementType& e, bool& c, Ordinal& porder) const {
  e = Topology::SpectralQuad;
  c = true;  // assume element is affine
  if (curve.get()) c = false;  // non-affine element
  porder = pOrder();
}

int SpectralQuad::get_weight() const {
  static Ordinal Pmax = 20;
  static int Weight[21][2] = {{100, 100},
                              {108, 108},
                              {132, 132},
                              {138, 138},
                              {160, 160},
                              {177, 177},
                              {196, 196},
                              {211, 211},
                              {239, 239},
                              {246, 246},
                              {291, 291},
                              {295, 295},
                              {326, 326},
                              {317, 317},
                              {347, 347},
                              {353, 353},
                              {382, 382},
                              {424, 424},
                              {450, 450},
                              {453, 453},
                              {487, 487}};
  int cflag = 0;
  if (curve.get()) cflag = 1;
  if (pOrder() > Pmax) {
    if (first_warn) {
      first_warn=false;
      cout << "WARNING - SpectralQuad::get_weight(): "
           << "pOrder (="<<pOrder()<<") > Pmax (="<<Pmax<<")"<< endl;
    }
    return Weight[Pmax][cflag];
  } else
    return Weight[pOrder()][cflag];
}

/// Computes the element measure (area for a SpectralQuad)
Scalar SpectralQuad::compute_measure() const {
#ifdef DGM_USE_WJ
  const dVector &b = geom->wJ;
#else
  dVector &wa = psi->wa;
  dVector &wb = psi->wb;
  dVector &J = geom->J;
  dVector b(n1_wk,qtot);
  dMatrix B(b,qa,qb);

  b = J;
  for(Ordinal j=0; j<qb; j++) {
    dSlice column(B.column(j));
    dvmul( wa, column );
  }
  for(Ordinal i=0; i<qa; i++) {
    dVector row(B.row(i));
    dvmul( wb, row );
  }
#endif
  return sum( b );   // integrate
}

/// Computes the L2 inner product of two elements
Scalar SpectralQuad::L2_inner_product(const Element *el, Scalar *area) const {
#ifdef DGM_USE_WJ
  const dVector &b = geom->wJ;
#else
  dVector &wa = psi->wa;
  dVector &wb = psi->wb;
  dVector &J = geom->J;
  dVector b(n1_wk,qtot);
  dMatrix B(b,qa,qb);

  b = J;
  for(Ordinal j=0; j<qb; j++) {
    dSlice column(B.column(j));
    dvmul( wa, column );
  }
  for(Ordinal i=0; i<qa; i++) {
    dVector row(B.row(i));
    dvmul( wb, row );
  }
#endif
  dVector f(n2_wk,qtot);

  dvmul( el->u, u, f );       // f = u*el->u
  if (area) *area = sum( b ); // element measure
  return dot( b, f );         // integrate
}

/// Computes the L2 inner product over the element of two data vectors
Scalar SpectralQuad::L2_inner_product(const dVector &vh, const dVector &wh,
                              Scalar *area) const {
#ifdef DGM_USE_WJ
  const dVector &b = geom->wJ;
#else
  dVector &wa = psi->wa;
  dVector &wb = psi->wb;
  dVector &J = geom->J;
  dVector b(n1_wk,qtot);
  dMatrix B(b,qa,qb);

  b = J;
  for(Ordinal j=0; j<qb; j++) {
    dSlice column(B.column(j));
    dvmul( wa, column );
  }
  for(Ordinal i=0; i<qa; i++) {
    dVector row(B.row(i));
    dvmul( wb, row );
  }
#endif
  dVector f(n2_wk,qtot);
  dvmul( vh, wh, f );   // f = vh*wh
  if (area) *area = sum( b );
  return dot( b, f );   // integrate
}

/// Compute the side derivatives (need to check this)
void SpectralQuad::get_side_Ds(const int sid, const dVector &dv,
                               dVector &dv_s) const {
  DGM_UNDEFINED;
  Ordinal p,q;
  Ordinal qside = (sid==0 || sid==2) ? qa:qb;
  assert( (dVector::size_type)edge[sid].qtot()==dv.size() );
  dv_s.resize(dv.size());
  dVector wk(qtot);
  dVector tmp1(qside);
  dVector fx(qtot);
  dVector fy(qtot);
  dVector fx_s(dv.size());
  dVector fy_s(dv.size());
  dMatrix *im;
  im = get_interpolation_matrix(qside, dv.size(), Interp::G2GL);
  mvmult( *im,dv,tmp1);

  // form the new temporary volume u : wk
  switch(sid) {
  case 0:
    for(q=0; q<qb; q++)
      for (p=0; p<qa; p++)
        wk[q + p * qb] = tmp1[p];
    break;
  case 1:
    for(p=0;p<qa;p++)
      for (q=0; q<qb; q++)
        wk[q + p * qb] = tmp1[q];
    break;
  case 2:
    for(q=0;q<qb;q++)
      for (p=0; p<qa; p++)
        wk[q + p * qb] = tmp1[p];
    break;
  case 3:
    for(p=0;p<qa;p++)
      for (q=0; q<qb; q++)
        wk[q + p * qb] = tmp1[q];
    break;
  default:
    error("SpectralQuad::Ds -- unknown side");
  }

  gradient(wk,fx,fy);
  load_side(fx,sid,fx_s);
  load_side(fx,sid,fy_s);

  dvmul(edge[sid].ny(),fx_s);
  scale(-one,fx_s);             // -ny * f_x

  dvvtvp(edge[sid].nx(),fy_s,fx_s,dv_s);
}

/// Get the side curvature (x,y)->(r,s)
/** Vertices
    \verbatim
           b
           |             Edge Order:  0) bottom {0,1}
       3-------2                      1) right  {1,2}
       |   |   |                      2) top    {2,3}
       |   +---|-- a                  3) left   {3,0}
       |       |
       0-------1

       s~
       |
       | ---->r
       |

   One thought for the curvature calculation (Approximately) any curve
   including three points (x1,y1) (x2,y2) (x3,y3), assume the curvature
   circle is at (x0,y0) and its radius is R

   (x1-x0)^2+(y1-y0)^2 =R^2
   (x2-x0)^2+(y2-y0)^2 =R^2
   (x3-x0)^2+(y3-y0)^2 =R^2

   1/R = 2(x3*(y2-y1) + x2*(y1-y3) + x1*(y3-y2)) /
   (((x1-x2)^2+(y1-y2)^2)* ((x1-x3)^2+(y1-y3)^2)* (x3-x2)^2+(y3-y2)^2) )

   Second thought
   K = (x,r y,rr -y,r x,rr)/(x,r ^2 + y,r ^2)^1.5
   \endverbatim
*/
void SpectralQuad::get_side_curvature( const int sid, dVector &dcurv) const {
  DGM_UNDEFINED;
  dVector tmp;
  dVector x1r,y1r,x2r,y2r;
  dcurv.resize(qa);
  tmp.resize(qa);
  x1r.resize(qa);
  y1r.resize(qa);
  x2r.resize(qa);
  y2r.resize(qa);

  get_side(C->y,sid,tmp);
  mvmult(D->Da,tmp,y1r);
  mvmult(D->Da,y1r,y2r);  // D^2 y/ D r^2

  get_side(C->x,sid,tmp);
  mvmult(D->Da,tmp,x1r);
  mvmult(D->Da,x1r,x2r);  // D^2 x/ D r^2

  for(Ordinal i=0;i<qa;i++){
    Scalar ds = pow((x1r[i]*x1r[i]+y1r[i]*y1r[i]),1.5);
    Scalar dtheta = -(x1r[i]*y2r[i] - y1r[i]*x2r[i]);
    if ( fabs(ds)<1.0e-6 || fabs(dtheta)>1.0e10 ) {
      throw DGM::exception("SpectralQuad::get_side_curvature -- singular "
                           "curvature radius");
    }
    dcurv[i] = dtheta/ds;
  }
}

/// Get a 1d derivative matrix
/** Memory must be allocated for Matrix dm1 before call get_D1() I haven't
    interpolate Jacobi information from inside to edge, temporarily
    approximate.

    \warning SSC turned this off on 1/9/12 due to memory allocation errors
*/
void SpectralQuad::get_D1( const int sid, dMatrix &dm1) const {
  DGM_UNDEFINED;

  dVector wk, tmp1,tmp2;
  dMatrix *im;

  assert( qa==qb );
  assert( (dMatrix::size_type)edge[sid].qtot() == dm1.rows() );
  assert( (dMatrix::size_type)edge[sid].qtot() == dm1.cols());

  dMatrix wk1(n2_wk,qa,dm1.rows());
  dMatrix wk2(Lwk,dm1.rows(),dm1.rows());
  dMatrix wk3(g2_wk,dm1.rows(),dm1.rows());

  switch(sid) {
  case 0:
  case 2:
    wk.alias(g1_wk,0,qa);
    tmp1.alias(g1_wk,qa,qa);    // ERROR: uses too much memory
    tmp2.alias(g1_wk,2*qa,qa);  // ERROR: uses too much memory

    tmp1 = side[sid]->ny();
    get_side(geom->rx,sid,wk);
    dvmul(wk,tmp1);             // ny*r_x

    tmp2 = side[sid]->nx();
    get_side(geom->ry,sid,wk);
    dvmul(wk,tmp2);             // nx*r_y

    daxpy(-1.0,tmp1,tmp2);      // -ny*r_x + nx*r_y

    // Interpolation matrix from Gauss-Lobatto to interior
    im = get_interpolation_matrix(qa, side[sid]->qtot(), Interp::G2GL);
    matmult(D->Da,*im,wk1);

    // Interpolation matrix from interior to Gauss-Lobatto
    im = get_interpolation_matrix( side[sid]->qtot(), qa, Interp::GL2G);
    matmult(*im,wk1,wk2);

    dm1 = 0.0;
    for(dMatrix::size_type i=0; i<dm1.rows(); ++i) dm1[i][i] = tmp2[i];
    matmult(dm1,wk2,wk3);

    matmult('T',wk3,wk3,dm1);   // Ds^T Ds
    break;
  case 1:
  case 3:
    wk.alias(g1_wk,0,qa);
    tmp1.alias(g1_wk,qa,qa);    // ERROR:  too much memory
    tmp2.alias(g1_wk,2*qa,qa);  // ERROR:  too much memory

    tmp1 = side[sid]->ny();
    get_side(geom->sx,sid,wk);
    dvmul(wk,tmp1);             // ny*s_x

    tmp2 = side[sid]->nx();
    get_side(geom->sy,sid,wk);
    dvmul(wk,tmp2);             // nx*s_y

    daxpy(-1.0,tmp1,tmp2);      // -ny*s_x + nx*s_y

    // Interpolation matrix from Gauss-Lobatto to interior
    im = get_interpolation_matrix(qa, side[sid]->qtot(), Interp::G2GL);
    matmult(D->Db,*im,wk1);

    // Interpolation matrix from interior to Gauss-Lobatto
    im = get_interpolation_matrix( side[sid]->qtot(), qa, Interp::GL2G);
    matmult(*im,wk1,wk2);

    dm1=0.0;
    for(dMatrix::size_type i=0; i<dm1.rows(); ++i) dm1[i][i] = tmp2[i];
    matmult(dm1,wk2,wk3);

    matmult('T',wk3,wk3,dm1);   // Ds^T Ds
    break;
  default:
    error("SpectralQuad::get_D1 -- unknown side");
  }
  return;
}

//=============================================================================

/// Apply an exponential 1d filter in both directions of tensor product
void SpectralQuad::exp_filter(const Scalar eta, const Scalar s) {
  //if (gid()!=18 && gid()!=12 && gid()!=6 && gid()!=24 &&
  //    gid()!=13 && gid()!=19) return;
  if (!curve.get()) return;

  //DGM_VERBOSE;
  //bool needs_transform = false;
  //if (state == Physical) {
  L_forward_transform();
  //needs_transform = true;
  //}
  const Ordinal Nc = numeric_cast<Ordinal>(eta*(L()-1));
#if 1
  const Scalar alpha = -log(epsM);
  static bool firsttime = true;
  static dVector mask;
  if (firsttime) {
    mask.resize(L());
    mask = 1.0;
    for (Ordinal i=Nc; i<L(); i++) {
      const Scalar a = (Scalar)(i-Nc)/(Scalar)(L()-Nc);
      mask[i] = exp(-alpha*pow(a,s));
    }
    firsttime = false;
  }
  // upper left
  for (Ordinal i=0; i<Nc; i++) {
    for (Ordinal j=Nc; j<L(); j++) {
      const Ordinal n = j + i*L();
      uh[n] *= mask[j];
    }
  }
  // lower right
  for (Ordinal j=0; j<Nc; j++) {
    for (Ordinal i=Nc; i<L(); i++) {
      const Ordinal n = j + i*L();
      uh[n] *= mask[i];
    }
  }
  // upper right
  for (Ordinal i=Nc; i<L(); i++) {
    for (Ordinal j=Nc; j<L(); j++) {
      const Ordinal n = j + i*L();
      uh[n] *= mask[i]*mask[j];
    }
  }
#else
  // upper left
  for (Ordinal i=0; i<Nc+1; i++) {
    for (Ordinal j=Nc+1; j<L(); j++) {
      const Ordinal n = j + i*L();
      uh[n] = 0.0;
    }
  }
  // lower right
  for (Ordinal j=0; j<=Nc+1; j++) {
    for (Ordinal i=Nc+1; i<L(); i++) {
      const Ordinal n = j + i*L();
      uh[n] = 0.0;
    }
  }
  // upper right
  for (Ordinal i=Nc+1; i<L(); i++) {
    for (Ordinal j=Nc+1; j<L(); j++) {
      const Ordinal n = j + i*L();
      uh[n] = 0.0;
    }
  }
#endif
  //if (needs_transform)
  L_backward_transform();
}

/// Zero all modes but the constant
void SpectralQuad::make_constant() {
  Ordinal i, j, n;
  //DGM_UNDEFINED;
  //cout << "SpectralQuad::make_constant()" <<endl;
  //bool needs_transform = false;
  //if (state == Physical) {
  //  forward_transform();
  //  needs_transform = true;
  //}

  //nodal_to_modal(u, uh);
  L_forward_transform();

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

  //modal_to_nodal(uh, u);
  L_backward_transform();

  //if (needs_transform)
  //  backward_transform();
}

/// Zero all modes greater than np
void SpectralQuad::low_modes(const Ordinal inp) {
  //cout << "SpectralQuad::low_modes()" << endl;
  const Ordinal np = numeric_cast<Ordinal>(inp);
  if (np>=pOrder()) return;  // nothing to do
  Ordinal i, j, n;

  //DGM_UNDEFINED;
  //bool needs_transform = false;
  //if (state == Physical) {
  //  forward_transform();
  //  needs_transform = true;
  //}

  //nodal_to_modal(u, uh);
  L_forward_transform();

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

  //modal_to_nodal(uh, u);
  L_backward_transform();

  //if (needs_transform)
  //  backward_transform();
}

void SpectralQuad::nodal_to_modal(dVector &f, dVector &fh) {

  //cout << "SpectralQuad::nodal_to_modal()" << endl;

  if (curve.get()) {
    const dVector &J = geom->J;
    dvmul( J, f );
  }

  dMatrix F(f,qa,qb);
  dMatrix Fh(fh,qa,qb);
  dMatrix MF(qa,qb);
  dMatrix *M = get_interpolation_matrix(qa, qb, Interp::GL2M);

  matmult( *M, F, MF );
  matmult( MF, 'T', *M, Fh );
}

void SpectralQuad::modal_to_nodal( dVector &fh, dVector &f) {

  //cout << "SpectralQuad::modal_to_nodal()" << endl;

  dMatrix F(f,qa,qb);
  dMatrix Fh(fh,qa,qb);
  dMatrix MFh(qa,qb);
  dMatrix *M = get_interpolation_matrix(qa, qb, Interp::M2GL);

  matmult( 'T', *M, Fh, MFh );
  matmult( MFh, *M, F );
}

/// Zero the constant mode (only)
void SpectralQuad::kill_constant() {
  DGM_UNDEFINED;
  bool needs_transform = false;
  if (state == Physical) {
    forward_transform();
    needs_transform = true;
  }
  uh[0] = 0.0;
  if (needs_transform) backward_transform();
}

/// Zero all modes greater than p_inc
void SpectralQuad::coarse_scales(const int p_inc) {
  DGM_UNDEFINED;
  //cout << "SpectralQuad::coarse_scales(const int p)" <<endl;
  Ordinal i, j, n;
  bool needs_transform = false;
  if (state == Physical) {
    forward_transform();
    needs_transform = true;
  }
  // upper-left quadrant
  for (i=0; i<L()-p_inc; i++) {
    for (j=L()-p_inc; j<L(); j++) {
      n = j + i*L();
      uh[n] = 0.0;
    }
  }
  // lower-right and upper-right corner quadrants
  for (i=L()-p_inc; i<L(); i++) {
    for (j=0; j<L(); j++) {
      n = j + i*L();
      uh[n] = 0.0;
    }
  }
  if (needs_transform) backward_transform();
}

/// Zero all modes greater then p_inc in supplied vector
void SpectralQuad::coarse_scales(const int p_inc, dVector &vh) {
  //cout << "SpectralQuad::coarse_scales(const int p, dVector &vh)" <<endl;
  Ordinal i, j, n;
  // upper-left quadrant
  for (i=0; i<L()-p_inc; i++) {
    for (j=L()-p_inc; j<L(); j++) {
      n = j + i*L();
      vh[n] = 0.0;
    }
  }
  // lower-right and upper-right corner quadrants
  for (i=L()-p_inc; i<L(); i++) {
    for (j=0; j<L(); j++) {
      n = j + i*L();
      vh[n] = 0.0;
    }
  }
}

/// Zero all modes less then p_inc
void SpectralQuad::fine_scales(const int p_inc) {
  DGM_UNDEFINED;
  //cout << "SpectralQuad::fine_scales(const int p)" <<endl;
  Ordinal i, j, n;
  bool needs_transform = false;
  if (state == Physical) {
    forward_transform();
    needs_transform = true;
  }
  // lower-left quadrant
  for (i=0; i<L()-p_inc; i++) {
    for (j=0; j<L()-p_inc; j++) {
      n = j + i*L();
      uh[n] = 0.0;
    }
  }
  if (needs_transform)
    backward_transform();
}

/// Zero all modes less than p_inc in supplied vector
void SpectralQuad::fine_scales(const int p_inc, dVector &vh) {
  //cout << "SpectralQuad::fine_scales(const int p, dVector &vh)" <<endl;
  Ordinal i, j, n;
  // lower-left quadrant
  for (i=0; i<L()-p_inc; i++) {
    for (j=0; j<L()-p_inc; j++) {
      n = j + i*L();
      vh[n] = 0.0;
    }
  }
}

/// Transform, zero low modes, and backward transform supplied vector
void SpectralQuad::fine_scales_transform(const int p_inc, dVector &vh) const {
  DGM_UNDEFINED;
  //cout << "SpectralQuad::fine_scales_transform(const int p, dVector &vh)"
  //     <<endl;
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

/// SSC:  not sure why this version is needed...?
vector<dMatrix*> SpectralQuad::get_interpolation_matrices() const {
  const Element *U = this;
  vector<dMatrix*> matrices;
  for (size_t i=0; i<4; ++i) {
    const Ordinal    q = i%2 ? qb : qa;
    const Ordinal qedg = U->edge[i].qtot();
    dMatrix* m = get_interpolation_matrix(q, qedg, Interp::G2GL);
    matrices.push_back(m);
  }
  return matrices;
}

void SpectralQuad::fill_basis_shift_matrix(dMatrix &G) const {
  const Ordinal nModes = 4;
  const Ordinal Nvert = 4;
  G.resize(nModes, Nvert);

  const Scalar r0 = 0.5;
  const Scalar r1 = sqrt(3.0)/6.0;
  const Scalar r2 = r1;
  const Scalar r3 = 1.0/6.0;
  G(0,0) =  r0; G(0,1) =  r0; G(0,2) =  r0; G(0,3) =  r0;
  G(1,0) = -r1; G(1,1) = -r1; G(1,2) =  r1; G(1,3) =  r1;
  G(2,0) = -r2; G(2,1) =  r2; G(2,2) =  r2; G(2,3) = -r2;
  G(3,0) =  r3; G(3,1) = -r3; G(3,2) =  r3; G(3,3) = -r3;
}

} // namespace DGM
