/** \file NodalQuad.cpp
    \brief NodalQuad Element implementation
    \author Scott Collis

    NodalQuad is a four node quadrilateral element that supports affine
    isoparametric mappings from the master element to the physical space
    element.

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
using namespace std;

// boost includes
#include "boost/numeric/conversion/cast.hpp"
using boost::numeric_cast;

// DGM includes
#include "Comm.hpp"
#include "NodalQuad.hpp"
#include "Polylib.tpp"
#include "Utilities.hpp"
#include "String.hpp"

namespace DGM {

// define static storage
BasisDB NodalQuad::bdb;                           // Basis database
NodalQuad::GeometryDB  NodalQuad::gdb("NodalQuad");   // Geom database
IMDB NodalQuad::imdb;                             // Interpolation database

Ordinal NodalQuad::Qmax = 0;
Ordinal NodalQuad::Lmax = 0;
dVector NodalQuad::g1_wk;
dVector NodalQuad::g2_wk;

dVector NodalQuad::n1_wk;
dVector NodalQuad::n2_wk;
dVector NodalQuad::Lwk;

bool NodalQuad::first_warn(true);

#ifdef DGM_USE_MD_COUPLE

/// Constructor
/*! \param[in] ID    - Local element id
    \param[in] P     - Polynomial order
    \param[in] X     - Vector of points defining the vertices
    \param[in] model - Model type */
NodalQuad::NodalQuad(const Ordinal ID, const Ordinal P,
                     const vector<Point> &X, const Model::Type model) :
  BaseQuad(ID, Basis::Ortho) {
  // cout << "NodalQuad::NodalQuad constructor for element " << ID << endl;
  nVerts(4);
  nEdges(4);
  nFaces(1);
  nSides(4);
  pOrder(P);
  L(P+1);
  nModes(L()*L());

  modeltype = model;

  // you might want to use different quadrature order in a and b
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
  uh.alias(u,nModes);
#endif

  // construct edge data-structure
  edge.reserve(nEdges);
  for (Ordinal i=0; i<nEdges; ++i) {
    const int qedg = (i==0 || i==2) ? qa : qb;
    Edge ed(i,id,nModes,qedg,modeltype);
    edge.push_back(ed);
    side.push_back( &(edge[i]) );
  }
}

#else  // !DGM_USE_MD_COUPLE

/// Constructor
/*! \param[in] ID    - Local element id
    \param[in] P     - Polynomial order
    \param[in] X     - Vector of points defining the vertices */
NodalQuad::NodalQuad(const Ordinal ID, const Ordinal P,
                     const vector<Point> &X) : BaseQuad(ID,Basis::Ortho) {
  // cout << "NodalQuad::NodalQuad constructor for element " << ID << endl;
  nVerts(4);
  nEdges(4);
  nFaces(1);
  nSides(4);
  pOrder(P);
  L(P+1);
  nModes(L()*L());

  // you might want to use different quadrature order in a and b
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
  uh.alias(u,nModes);
#endif

  // construct edge data-structure
  edge.reserve(nEdges());
  for (Ordinal i=0; i<nEdges(); ++i) {
    const Ordinal qedg = (i==0 || i==2) ? qa : qb;
    Edge ed(i,this,nModes(),qedg,false);
    edge.push_back(ed);
    side.push_back( &(edge[i]) );
  }
}

#endif  // DGM_USE_MD_COUPLE

/// Copy constructor -- This should not allocate new space for P, M, etc.
NodalQuad::NodalQuad(const NodalQuad *E) {
  // cout << "NodalQuad copy constructor for Eid = " << E->id << endl;

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
  }

  // initialize values
  state = Undefined;
  u = 0.0;
}

/// Destructor
NodalQuad::~NodalQuad() {
  // cout << DGM::Comm::World->MyPID() << " ~NodalQuad: eid= " << id << endl;
}

/// Retrieves a basis from the basis database
/** If the basis is not in the database, makes a new basis and adds to
    database
    \todo Switch to a non-string key like the interpolation matrix. */
Basis* NodalQuad::get_basis(const int der=0) const {
  // cout << "NodalQuad::get_basis" << endl;
  Basis* b;
  char buf[128];
  sprintf(buf,"%lld_%lld_%lld_%lld_%lld_%lld",
      (long long)type,(long long)L(),(long long)der,
      (long long)qa,(long long)qb,(long long)qc);
  const string key = buf;
  BasisDB::iterator p = bdb.bases.find(key);
  if ( p == bdb.bases.end() ) {                  // not found, make a new one
    b = new Basis(L(),qa,qb,qc,nModes());
    make_basis(b,type,der);
    bdb.bases[key] = b;
  } else {                                       // found, return the basis
    b = p->second;
  }
  return b;
}

/// Gets the mass matrix for this NodalQuad
/** This really computes the inverse mass matrix directly. */
void NodalQuad::get_mass_matrix() {
  // cout << "NodalQuad::get_mass_matrix for element " << id << endl;
  M.reset( new Minfo );
  M->mat.resize(nModes(),nModes());
  M->pivots.resize(nModes());
  // build Vandermonde matrix
  dMatrix V(nModes(),nModes());
  dVector Vcol(nModes());
  for (Ordinal j=0; j<nModes(); j++) {
    fill( psi->mode[j], Vcol );
    for (Ordinal i=0; i<nModes(); i++) V[i][j] = Vcol[i];
  }
  matmult( V, 'T', V, M->mat );
  for (Ordinal i=0; i<nModes(); i++)
    for (Ordinal j=0; j<nModes(); j++)
      M->mat[i][j] /= geom->J[0];  // only works for constant Jacobian

  // Also build mass matrix with columns on edges only
  // (Used for sparse lift)
  Mbound.reset( new Minfo );
  Mbound->mat.resize(qa*qb,2*qa+2*qb-4);
  int j=0;
  for(Ordinal i=0; i<qa*qb; i++)
    if ((i<qa) || (i>qa*(qb-1)) || (i%qa==0) || (i%qa==(qa-1))) {
      for(Ordinal k=0; k<qa*qb; k++)
        Mbound->mat[k][j] = M->mat[k][i];
      j++;
    }
}

/// Resets the mass matrixing using a weighted mass matrix
/** WARNING:  might be dangerous to reset the mass matrix to this new value */
void NodalQuad::get_mass_matrix(const dVector &x) {
  cout << "NodalQuad::get_mass_matrix(x) for element " << gid() << endl;
  DGM_UNDEFINED;
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
  //cout << "Cholesky: 2" << endl;
  if (Cholesky_factor(M->mat) !=0)
    DGM::Comm::World->error("Cholesky_factor() failed.");
#else
  if (LU_factor(M->mat, M->pivots) !=0)
    DGM::Comm::World->error("LU_factor() failed.");
#endif
  full_mass = true;
}

/// Solves the mass matrix
void NodalQuad::solve_mass_matrix(dVector &fh) const {
  return;
}

//=============================================================================

void NodalQuad::test_on_shape_side(const dVector &v, const int sid, dVector &vh)
const {
  cout << "NodalQuad::test_on_shape_side()" << endl;
  DGM_UNDEFINED;
  dVector f( side[sid]->qtot() );
  dVector fh( qtot );
  assert ( f.size() == v.size() );
  for (Ordinal m=0; m<nModes(); m++) {
    fill( psi->mode[m], fh );
    load_side( fh, sid, f );
    dvmul(v,f);
    vh[m] = compute_side_integral(f,sid);
  }
}

/// Inner product over the element against the derivative of the Basis
/** This is a very bad implementation that is tremendously slow.  Instead,
    one should use the local derivative operators and replace this with
    BLAS Level 3 operations.
    \todo This MUST be re-written (it is an order of magnitude too slow)   */
void NodalQuad::test_on_grad_shape(const dVector &v, char dir, dVector &vh)
const {
  cout << "NodalQuad::test_on_grad_shape()" << endl;
  DGM_UNDEFINED;
  dVector f(qtot);
  dVector df(qtot);
  for (Ordinal m=0; m<nModes(); m++) {
    fill( psi->mode[m], f );
    gradient( f, df, dir);
    vh[m]=L2_inner_product(df,v);
  }
}

/// Computes a mass matrix but does not factor it
void NodalQuad::get_local_mass_matrix(const dVector &factor) {
  cout << "NodalQuad::get_local_mass_matrix(x) for element " << gid() <<endl;
  // WARNING:  might be dangerous to reset the mass matrix to this new value
  DGM_UNDEFINED;
  Mloc.reset( new Minfo );
  Mloc->mat.resize(nModes(),nModes()); // pivots untouched
  dVector f(qtot);
  dVector fh(f,nModes());
  // full mass matrix
  for (Ordinal m=0; m<nModes(); m++) {
    fill( psi->mode[m], f );
    dvmul( factor, f );
    inner_product(f, fh);
    for (Ordinal n=0; n<nModes(); n++) Mloc->mat[m][n] = fh[n];
  }
}

void NodalQuad::get_local_derivative_matrix() {
  cout << "NodalQuad::get_mass_matrix for element " << gid() << endl;
  DGM_UNDEFINED;
  Dxloc.reset( new Minfo );
  Dyloc.reset( new Minfo );
  Dxtloc.reset( new Minfo );
  Dytloc.reset( new Minfo );
  Dxloc->mat.resize(nModes(),nModes());  // pivots untouched
  Dyloc->mat.resize(nModes(),nModes());  // pivots untouched
  Dxtloc->mat.resize(nModes(),nModes()); // pivots untouched
  Dytloc->mat.resize(nModes(),nModes()); // pivots untouched
  dVector f(qtot);
  dVector fx(qtot);
  dVector fy(qtot);
  dVector fh(nModes());
  for (Ordinal j=0; j<nModes(); j++) {
    fill( psi->mode[j], f );
    gradient(f,fx,'x');
    inner_product(fx, fh);
    for (Ordinal i=0; i<nModes(); i++) {
       Dxloc->mat[i][j] = fh[i];
      Dxtloc->mat[j][i] = fh[i];
    }
    gradient(f,fy,'y');
    inner_product(fy, fh);
    for (Ordinal i=0; i<nModes(); i++) {
       Dyloc->mat[i][j] = fh[i];
      Dytloc->mat[j][i] = fh[i];
    }
  }
}

void NodalQuad::get_local_derivative_matrix(const dVector &factor) {
  cout << "NodalQuad::get_local_derivative_matrix for element "
       << gid() << endl;
  DGM_UNDEFINED;
  Dxloc.reset( new Minfo );
  Dyloc.reset( new Minfo );
  Dxtloc.reset( new Minfo );
  Dytloc.reset( new Minfo );
  Dxloc->mat.resize(nModes(),nModes());   // pivots untouched
  Dyloc->mat.resize(nModes(),nModes());   // pivots untouched
  Dxtloc->mat.resize(nModes(),nModes());  // pivots untouched
  Dytloc->mat.resize(nModes(),nModes());  // pivots untouched
  dVector f(qtot);
  dVector fx(qtot);
  dVector fy(qtot);
  dVector fh(nModes());
  for (Ordinal j=0; j<nModes(); j++) {
    fill( psi->mode[j], f );
    gradient(f,fx,'x');
    dvmul(factor,fx);
    inner_product(fx, fh);
    for (Ordinal i=0; i<nModes(); i++) {
       Dxloc->mat[i][j] = fh[i];
      Dxtloc->mat[j][i] = fh[i];
    }
    gradient(f,fy,'y');
    dvmul(factor,fy);
    inner_product(fy, fh);
    for (Ordinal i=0; i<nModes(); i++) {
       Dyloc->mat[i][j] = fh[i];
      Dytloc->mat[j][i] = fh[i];
    }
  }
}

void NodalQuad::get_local_laplace_matrix() {
  cout << "NodalQuad::get_local_laplace_matrix for element "
       << gid() << endl;
  DGM_UNDEFINED;
  DDloc.reset( new Minfo );
  DDloc->mat.resize(nModes(),nModes()); // pivots untouched
  // work vectors
  dVector f1(qtot);
  dVector f2(qtot);
  dVector dpsi_i(qtot);
  dVector dpsi_j(qtot);
  // get geometry first
#ifdef DGM_USE_WJ
  const dVector &b = geom->wJ;
#else
  const dVector &wa = psi->wa;
  const dVector &wb = psi->wb;
  const dVector &J  = geom->J;
  dVector b(qtot);
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
  DDloc->mat = 0; //initialize
  for (Ordinal i=0; i<nModes(); i++) {
    fill( psi->mode[i],f1);
    gradient(f1,dpsi_i,'x');
    for (Ordinal j=0; j<nModes(); j++) {
      fill( psi->mode[j],f2);
      gradient(f2,dpsi_j,'x');
      dvmul(dpsi_i,dpsi_j,f2);   // f2 = vh*wh
      DDloc->mat[i][j] += dot(b,f2);
    }
    gradient(f1,dpsi_i,'y');
    for (Ordinal j=0; j<nModes(); j++) {
      fill( psi->mode[j],f2);
      gradient(f2,dpsi_j,'y');
      dvmul(dpsi_i,dpsi_j,f2);   // f2 = vh*wh
      DDloc->mat[i][j] += dot(b,f2);
    }
  }
}

void NodalQuad::get_local_laplace_matrix(const dVector & factor) {
  cout << "NodalQuad::get_local_laplace_matrix for element "
       << gid() << endl;
  DGM_UNDEFINED;
  DDloc.reset( new Minfo );
  DDloc->mat.resize(nModes(),nModes()); // pivots untouched
  // work vectors
  dVector f1(qtot);
  dVector f2(qtot);
  dVector dpsi_i(qtot);
  dVector dpsi_j(qtot);
  // get geometry first
#ifdef DGM_USE_WJ
  const dVector &b = geom->wJ;
#else
  const dVector &wa = psi->wa;
  const dVector &wb = psi->wb;
  const dVector &J  = geom->J;
  dVector b(qtot);
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
  DDloc->mat = 0; // initialize
  for (Ordinal i=0; i<nModes(); i++) {
    fill( psi->mode[i],f1);
    gradient(f1,dpsi_i,'x');
    for (Ordinal j=0; j<nModes(); j++) {
      fill( psi->mode[j],f2);
      gradient(f2,dpsi_j,'x');
      dvmul(dpsi_i,dpsi_j,f2);   // f2 = vh*wh
      dvmul(factor,f2);          // factor*f2 -> f2
      DDloc->mat[i][j] += dot(b,f2);
    }
    gradient(f1,dpsi_i,'y');
    for (Ordinal j=0; j<nModes(); j++) {
      fill( psi->mode[j],f2);
      gradient(f2,dpsi_j,'y');
      dvmul(dpsi_i,dpsi_j,f2);   // f2 = vh*wh
      dvmul(factor,f2);          // factor*f2 -> f2
      DDloc->mat[i][j] += dot(b,f2);
    }
  }
}

//=============================================================================

/// Fill element with a function string
void NodalQuad::fill(string function_string, Operation operation) {
  state = Physical;
  parser_init();
  Parser::VectorFunction f("x", "y", "t", function_string );
  f.evaluate( C->x, C->y, u, 0.0, convert(operation) );
  state = Physical;
}

/// Fill element with a mode
void NodalQuad::fill(Mode &v) {
  //cout << "NodalQuad::fill(Mode &)" << endl;
  dMatrix U(u,qa,qb);
  for (Ordinal i=0; i<qa; i++)
    for (Ordinal j=0; j<qb; j++) {
      //cout << "i, j = " << i << ", " << j << endl;
      U[i][j] = v.a[i] * v.b[j];
    }
  state = Physical;
}

/// Fill a vector with a mode
void NodalQuad::fill(Mode &v, dVector &f) const {
  //cout << "NodalQuad::fill(Mode &, dVector &)" << endl;
  dMatrix F(f,qa,qb);
  for (Ordinal i=0; i<qa; i++)
    for (Ordinal j=0; j<qb; j++) {
      F[i][j] = v.a[i] * v.b[j];
    }
}

/// Fill element with a random polynomial
void NodalQuad::random() {
  // cout << "NodalQuad::random()" << endl;
  state = Physical;
  for (Ordinal i=0; i<nModes(); i++) uh[i] = Element::random(-one,one);
}

/// Set the modes of an element
void NodalQuad::set(const dVector &fh, const Ordinal nModes2) {
  //cout << "NodalQuad::set(const dVector &, const int)" << endl;
  const Ordinal L2 = static_cast<int>(sqrt(static_cast<Scalar>(nModes2)));
  const Ordinal Lm = min(L(),L2);
  dVector Uh, Fh;
  for (Ordinal i=0, m=0, m2=0; i<Lm; i++) {
    Uh.alias( uh, m, L() );
    Fh.alias( fh, m2, L2 );
    for (Ordinal j=0; j<Lm; j++) Uh[j] = Fh[j];
    m += L();
    m2 += L2;
  }
  state = Transform;
  // cout<<"Eid = "<<id<<", |mode(nModes())| = "<<fabs(uh(nModes()-1))<<endl;
}

/// Compute the inner product with the Basis
void NodalQuad::inner_product() {
  cout << "NodalQuad::inner_product for Eid = " << gid() << endl;
  DGM_UNDEFINED;
  inner_product(u, uh);
  state = Transform;
}

/// Computes the inner product of the supplied vector against the Basis
void NodalQuad::inner_product(dVector &f, dVector &fh) const {
  cout << "NodalQuad::inner_product for Eid = " << gid() << endl;
  DGM_UNDEFINED;
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
  matmult( wk, 'T', phib, Fh);    // Fh[La][Lb] = wk[La][qb] * (Bb[La][qb])^T
}

/// Transform the Element to polynomial space
void NodalQuad::forward_transform() {
  //cout << "NodalQuad::forward_transform()" << endl;
  if (state == Transform) {
    cerr << "NodalQuad::transform -- already in transform space"<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  forward_transform(u,uh);
  state = Transform;
}

/// Transform the supplied data to polynomial space
/** \todo Need to cache the Vandermonde inverse as part of the basis. */
void NodalQuad::forward_transform(dVector &f, dVector &fh) const {
  // cout << "NodalQuad::forward_transform(f,fh)" << endl;
  assert(static_cast<Ordinal>(qtot)==nModes());
  Minfo Vi;
  Vi.mat.resize(qtot,nModes());  // build inverse Vandermonde matrix
  dVector Vcol(qtot);
  for (Ordinal j=0; j<nModes(); j++) {
    fill( psi->mode[j], Vcol );
    for (Ordinal i=0; i<qtot; i++) Vi.mat[i][j] = Vcol[i];
  }
  if (LU_factor(Vi.mat, Vi.pivots)!=0)
    DGM::Comm::World->error("NodalQuad::forward_transform -- LU_factor of "
                            "Vandermonde failed.");
  fh = f;
  LU_solve(Vi.mat, Vi.pivots, fh);
}

/// Transform using another Elements mass matrix (dangerous)
void NodalQuad::forward_transform(Element *F, Element *) {
  cout << "NodalQuad::forward_transform(*F,*)" << endl;
  DGM_UNDEFINED;
}

/// Return Element to physical space
void NodalQuad::backward_transform() {
  // cout << "NodalQuad::backward_transform()" << endl;
  if (state == Physical) {
    cerr << "NodalQuad::transform_to_physical -- already in physical "
      "space"<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  backward_transform( uh, u );
  state = Physical;
}

/// Transform supplied data to physical space on this Element
/** \todo Need to cache the Vandermonde matrix part of the basis. */
void NodalQuad::backward_transform(dVector &fh, dVector &f) const {
  // cout << "NodalQuad::backward_transform(fh,f)" << endl;
  Minfo V;
  assert(static_cast<Ordinal>(qtot)==nModes());
  V.mat.resize(nModes(),qtot); // build Vandermonde matrix
  dVector Vcol(qtot);
  for (Ordinal j=0; j<nModes(); j++) {
    fill( psi->mode[j], Vcol );
    for (Ordinal i=0; i<qtot; i++) V.mat[i][j] = Vcol[i];
  }
  dVector wk(Lwk,qtot);      // Needed for case that fh is alias of f
  wk = fh;
#if 1
  mvmult(V.mat,wk,f);        // f[qtot] = V[qtot][nModes()] * fh[nModes()]
#else
  // hand unrolled mvmult
  f = 0;
  for (Ordinal i=0; i<qtot; i++) {
    for (Ordinal j=0; j<nModes(); j++) {
      fill(psi->mode[j], Vcol);
      f[i] += wk[j] * Vcol[i];
    }
  }
#endif
}

/// Extracts data onto a specified Side
void NodalQuad::get_side( const dVector &from, const Ordinal sid,
                          dVector &to ) const {
  // cout<<"NodalQuad::get_side() Element = "<<id<<" Side = "<<sid<<endl<<to<<endl;
  Ordinal p, q;
  switch(sid) {
  case 0:
    q = 0;
    for (p=0; p<qa; p++) to[p] = from[q + p * qb];
    break;
  case 1:
    p = qa-1;
    for (q=0; q<qb; q++) to[q] = from[q + p * qb];
    break;
  case 2:
    q = qb-1;
    for (p=0; p<qa; p++) to[p] = from[q + p * qb];
    break;
  case 3:
    p = 0;
    for (q=0; q<qb; q++) to[q] = from[q + p * qb];
    break;
  default:
    cerr << "NodalQuad::get_side -- unknown side" << endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
}

/// Makes an interpolation matrix
void NodalQuad::make_interpolation_matrix(const Ordinal q1, const Ordinal q2,
                                          const Interp::Type interp,
                                          dMatrix &im ) {
  // cout << "NodalQuad::make_interpolation_matrix" << endl;
  im.resize(q1,q2);
  dVector z1(q1), z2(q2), w1(q1), w2(q2);
  Scalar delta;
  switch(interp){
  case(Interp::GL2G):
    zwgll(z2,w2);           // Gauss-Lobatto-Legendre
    zwgl (z1,w1);           // Gauss-Legendre
    igllm(im,z2,z1);        // Interpolation matrix
    break;
  case(Interp::G2GL):
    zwgl (z2,w2);           // Gauss-Legendre
    zwgll(z1,w1);           // Gauss-Lobatto-Legendre
    iglm(im,z2,z1);         // Interpolation matrix
    break;
  case(Interp::GL2U):
    zwgll(z2,w2);
    delta=two/(Scalar)(q1);
    for(Ordinal i=0; i<q1; ++i) z1[i] = i*delta - one + pt5*delta;
    igllm(im,z2,z1);
    break;
  default:
    cerr << "NodalQuad::make_interpolation_matrix - Invalid interpolation type"
         << endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
}

/// Returns an interpolation matrix (making one if needed)
dMatrix* NodalQuad::get_interpolation_matrix(const Ordinal q1,
                                             const Ordinal q2,
                                             const Interp::Type interp=
                                             Interp::GL2G) {
  dMatrix* im;
  IMinfo key(interp,q1,q2);                 // make a key
  IMDB::iterator p = imdb.entry.find(key);
  if ( p == imdb.entry.end() ) {            // not found, make a new one
    im = new dMatrix;
    make_interpolation_matrix(q1,q2,interp,*im);
    imdb.entry[key] = im;
  } else {                                  // found, return the IM
    im = p->second;
  }
  return im;
}

// Interpolate supplied physical space values "f" to the sides
void NodalQuad::fill_sides(const dVector &f) {
  get_side(f,0,side[0]->u );
  get_side(f,1,side[1]->u );
  get_side(f,2,side[2]->u );
  get_side(f,3,side[3]->u );
}

// Interpolate physical space values "f" to a uniform mesh on the sides.
void NodalQuad::fill_sides_uniform(const dVector &f) {
  // cout<<"NodalQuad::fill_sides_uniform(f)"<<endl;
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
}

/// Fill Element Sides with a flux vector
void NodalQuad::fill_sides(const dVector &fx, const dVector &fy) {
  // cout << "NodalQuad::fill_sides flux version" << endl;
  dVector wka(g1_wk,qa);
  dVector wkb(g2_wk,qb);

  get_side(fx,0,edge[0].u );
  get_side(fy,0,wka);
  dvmul( edge[0].nx(), edge[0].u );
  dvvtvp( edge[0].ny(), wka, edge[0].u, edge[0].u );

  get_side(fx,1,edge[1].u);
  get_side(fy,1,wkb);
  dvmul( edge[1].nx(), edge[1].u );
  dvvtvp( edge[1].ny(), wkb, edge[1].u, edge[1].u );

  get_side(fx,2,edge[2].u);
  get_side(fy,2,wka);
  dvmul( edge[2].nx(), edge[2].u );
  dvvtvp( edge[2].ny(), wka, edge[2].u, edge[2].u );

  get_side(fx,3,edge[3].u );
  get_side(fy,3,wkb);
  dvmul( edge[3].nx(), edge[3].u );
  dvvtvp( edge[3].ny(), wkb, edge[3].u, edge[3].u );
}

// Interpolate physical space values "f" to the side Gauss Points
// BUT store the result in vector g.
void NodalQuad::load_side(const dVector &f, const Ordinal side_number,
                          dVector &g) const {
  get_side(f,side_number,g);
}

/// Compute coordinates of quadrature points
void NodalQuad::get_coordinates() {
  // cout << "NodalQuad::get_coordinates for element " << gid() << endl;
  if (curve.get())
    cout << "Curved NodalQuad not currently allowed" << endl;
  else
    get_straight_coordinates();
}

/// Compute coordinates for a straight-sided Element
void NodalQuad::get_straight_coordinates() {
  // cout << "NodalQuad::get_straight_coordinates for element "
  //      << gid() << endl;
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

void NodalQuad::J_backward_transform(dVector &fh, dVector &f) {
  cout << "NodalQuad::J_backward_transform for elmt = " << gid() << endl;
  DGM::Comm::World->error("Curved elements not supported in NodalQuad");
}

void NodalQuad::get_curved_coordinates() {
  DGM::Comm::World->error("Curved elements not supported in NodalQuad");
}

/** \todo Change from Point* to a Coord. */
void NodalQuad::get_side_coordinates(const Ordinal nedge, Point *pedge)const {
  dVector wka, px, py;
  px.resize(edge[nedge].qtot());
  py.resize(edge[nedge].qtot());
  switch(nedge) {
  case 0: case 1: case 2: case 3:
    get_side(C->x,nedge,px);
    get_side(C->y,nedge,py);
    for(Ordinal i=0; i<edge[nedge].qtot(); i++) pedge[i] = Point(px[i],py[i]);
    break;
  default:
    cerr << "NodalQuad::get_side_coordinates illegal edge id." << endl;
    DGM::Comm::World->exit();
  }
}

/// Compute the geometric factors
void NodalQuad::compute_geometry() {
  // cout << "NodalQuad::compute_geometry for element " << gid() << endl;
  geom.reset( new Geometry( lid(), 2, nVerts(), qtot ) );
  if (curve.get())
    DGM::Comm::World->error("Curved elements not supported in NodalQuad");
  else
    compute_straight_geometry();
  measure(compute_measure());   // area
#ifdef DGM_USE_GEOM_DB
  gdb.add(geom);
#endif
}

/** Determine, consistent with the tolerances used in compute_straight_geometry
    whether this is an affine element. */
bool NodalQuad::is_affine() const {
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
/** \note This is only correct for affine elements. */
void NodalQuad::compute_straight_geometry() {
  // cout << "NodalQuad::compute_straight_geometry for element "
  //      << gid() << endl;
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
    cerr << "ERROR:  NodalQuad::compute_straight_geometry()" << endl
         << "        Jacobian is not constant for Element " << gid() << endl;
    cerr << "This means that you have a non-affine element in your mesh "
        "that you are\n treating as a straight sided parallelogram.  "
        "Revise/correct your mesh for this\n element or declare this "
        "element as a \"Straight\" element in your root.crv\n file."<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
#endif

  // compute determinate of the Jacobian
  const Scalar detJ = xr*ys - xs*yr;
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
  // Compute metrics for CFL and timestep size (stability) estimates.
  compute_metrics();
#endif
}

void NodalQuad::compute_curved_geometry() {
  DGM::Comm::World->error("Curved elements not supported in NodalQuad");
}

/// Compute the stability metrics for timestep size calucations.
Element::StabMetrics NodalQuad::compute_metrics() {
  return compute_metrics_2d_tensor_prod();
}

/// Computes geometric factors for the Element Sides
void NodalQuad::compute_side_geometry() {
  // cout << "NodalQuad::compute_side_geometry(), Eid = "<< gid() << endl;
  sigma(0.0);
  for (Ordinal i=0; i<nEdges(); i++) {
    Edge &e = edge[i];
    Ordinal qedg = e.qtot();
    // cout << "Edge " << i << ", qedg = " << qedg << endl;
    Ordinal q = (i==0 || i==2) ? qa : qb;
    dMatrix &Der = (i==0 || i==2) ? D->Da : D->Db;
    switch(i) {
    case 0:
      get_side(geom->sx,i,edge[i].nx());
      scale( -1.0, edge[i].nx() );       // negate since on bottom
      get_side(geom->sy,i,edge[i].ny());
      scale( -1.0, edge[i].ny() );
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
      scale( -1.0, edge[i].nx() );       // negate since on left
      get_side(geom->ry,i,edge[i].ny() );
      scale( -1.0, edge[i].ny() );
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
#if 0
      cout << "Element = " << gid() << ", edge = " << i << ", q = " << j
          << ", (nx,ny) = " << edge[i].nx(j) << ", " << edge[i].ny(j)
          << ", int_J = " << interior_J[j] << endl;
#endif
    }

    // get coordinates along the edge
    dVector wk(q);
    dVector x(q);
    dVector y(q);
    get_side(C->x,i,wk);
    mvmult( Der, wk, x );
    get_side(C->y,i,wk);
    mvmult( Der, wk, y );
    dvmul( x, x, x);          // x = x^2
    dvvtvp( y, y, x, x );     // x = x^2 + y^2
    dvsqrt( x, edge[i].J() ); // wk = sqrt(x)

    // store the max ratio of side to element Jacobians
    dVector lsigma(qedg);
    lsigma = edge[i].J();
    dvdiv( interior_J, lsigma );
    for (Ordinal k=0; k<qedg; ++k)
      sigma(max(sigma(), fabs(lsigma[k])));
    // compute and store the measure for each Side
    dVector p(qedg); p = one;
    e.measure(compute_side_integral(p,i));
  }
}

void NodalQuad::forward_transform_side(dVector &f, dVector &fh) {
  cout << "NodalQuad::forward_transform_side(f,fh), Eid = "<< gid() << endl;
  DGM_UNDEFINED;
}

void NodalQuad::solve_1d_mass_matrix(dVector &fh) const {
  cout << "NodalQuad::solve_1d_mass_matrix(fh), Eid = "<< gid() << endl;
  DGM_UNDEFINED;
}

void NodalQuad::get_1d_mass_matrix(Minfo &M1d) const {
  cout << "NodalQuad::get_1d_mass_matrix(M), Eid = "<< gid() << endl;
  DGM_UNDEFINED;
}

/** \note This uses the implied side quadrature which may not be accurate. */
Scalar NodalQuad::compute_side_integral(dVector &f, Ordinal sid) const {
  // cout << "NodalQuad::compute_side_integral(dVector &, int) for Eid = "
  //      << this->gid() << ", Sid = " << sid << endl;
  const Ordinal qsid = side[sid]->qtot();
  dVector z(qsid), w(qsid);
  zwgll(z,w);                 // Gauss-Lobatto-Legendre
  // cout << " f = " << endl << f << endl;
  dvmul( side[sid]->J(), f);
  // cout << " J/interior_J * f = " << endl << f << endl;
  //int q = (sid==0 || sid==2) ? qa : qb;
  dVector interior_J(qsid);
  get_side(geom->J,sid,interior_J);
  dvmul( interior_J, f );
  // cout << " J * f = " << endl << f << endl;
  Scalar I = dot( f, w );
  // cout<<"Eid = " << this->gid() << ", Sid = " << sid << ", I = "
  //     << I << endl;
  return I;
}

Scalar NodalQuad::compute_side_measure() const {
  cout << "NodalQuad::compute_side_measure(), Eid = "<< gid() << endl;
  Scalar result=0.0;
  for (Ordinal sid=0; sid<nSides(); sid++) {
    Ordinal qsid = side[sid]->qtot();
    dVector p(qsid);
    p = 1.0;
    result += compute_side_integral(p,sid);
  }
  return result;
}

/** Add a discrete version of a Dirac delta function at a quadrature point
    with amplitude equal amp. */
void NodalQuad::add_Dirac_delta(const Ordinal qpt, const Scalar amp) {
  //cout << "NodalQuad::add_Dirac_Delta(int,Scalar) not available" << endl;
  assert( qpt >= 0 && qpt < qtot );
#if 1
  for (Ordinal i=0; i<qtot; i++) {
    u[i] += M->mat[i][qpt]*amp;
  }
#else
  mvmult( M->mat, tmp, ans );
  dvadd( ans, u );
#endif
}

/** Add a discrete version of a Dirac delta function at an arbitrary point
    p with amplitude equal amp. The Point, p, must be within the NodalQuad
    element. */
void NodalQuad::add_Dirac_delta(const Point &p, const Scalar amp) {
  //cout << "NodalQuad::add_Dirac_Delta(Point,Scalar) not available" << endl;
#ifdef DGM_TIME_NODALQUAD
  static FunctionTimer T("NodalQuad::add_Dirac_delta");
  FunctionSentry sentry(T);
#endif
  Scalar r, s;
  // First get the local coordinate on line
  if(!get_local_coordinates(p,r,s)) {
    DGM::Comm::World->cerr()<<
      "Quad::Add_Dirac_delta: could not find (r,s)"<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }

  const Point q(r,s);
  return add_local_Dirac_delta(q,amp);
}

void NodalQuad::add_local_Dirac_delta(const Point &p, const Scalar amp) {

  const Scalar r=p.x;
  const Scalar s=p.y;

  dMatrix imx, imy;
  dVector za(qa), wa(qa);
  dVector zb(qb), wb(qb);

  // Compute Gauss-Lobatto-Legendre points and weights
  zwgll(zb,wb); // y direction
  zwgll(za,wa); // x direction

  // Form the interpolation matrices
  imy.resize(1,qb);
  igllm(imy,zb,s);

  imx.resize(1,qa);
  igllm(imx,zb,r);

  // Apply the Dirac delta function operator
  dVector tmp(qtot); tmp=0;
  dVector ans(qtot); ans=0;
  vector<Ordinal> ind;
  for (Ordinal i=0; i<qa; i++) {
    for (Ordinal j=0; j<qb; j++) {
      const Ordinal qpt = j+i*qb;
      const Scalar im = imx(0,i)*imy(0,j);
      // cout << qpt << " " << im << " " << geom->J[qpt] << endl;
      if ( im!=0 ) {
        tmp[qpt] += im*amp;
        ind.push_back(qpt);
      }
    }
  }
  if ((Ordinal)ind.size()==qtot) {  // use dense matrix vector add into
    mvmult( M->mat, tmp, ans );
    dvadd(ans, u );
  } else {                          // use sparse matrix vector add into
    for (Ordinal i=0; i<qtot; i++) {
      vector<Ordinal>::iterator j = ind.begin();
      while( j != ind.end() ) {
        u[i] += M->mat[i][*j]*tmp[*j];
        ++j;
      }
    }
  }
}

void NodalQuad::add_local_Dirac_delta(const vector<dMatrix> &M_,
                                      const Scalar amp) {

  if (2!=M_.size())
    error("NodalQuad::add_local_Dirac_delta: Incorrect matrix size.");
  if (M_[0].rows() != M_[1].rows())
    error("NodalQuad::add_local_Dirac_delta: Inconsistant matrix size.");
  if (M_[0].cols() != qb || M_[1].cols() != qa)
    error("NodalQuad::add_local_Dirac_delta: Inconsistant matrix size.");

  const dMatrix &imy = M_[0];
  const dMatrix &imx = M_[1];


  // Apply the Dirac delta function operator
  dVector tmp(qtot); tmp=0;
  dVector ans(qtot); ans=0;
  vector<Ordinal> ind;
  for (Ordinal i=0; i<qa; i++) {
    for (Ordinal j=0; j<qb; j++) {
      const Ordinal qpt = j+i*qb;
      const Scalar im = imx(0,i)*imy(0,j);
      // cout << qpt << " " << im << " " << geom->J[qpt] << endl;
      if ( im!=0 ) {
        tmp[qpt] += im*amp;
        ind.push_back(qpt);
      }
    }
  }
  if ((Ordinal)ind.size()==qtot) {  // use dense matrix vector add into
    mvmult( M->mat, tmp, ans );
    dvadd(ans, u );
  } else {                          // use sparse matrix vector add into
    for (Ordinal i=0; i<qtot; i++) {
      vector<Ordinal>::iterator j = ind.begin();
      while( j != ind.end() ) {
        u[i] += M->mat[i][*j]*tmp[*j];
        ++j;
      }
    }
  }
}

/// Extract the solution at the Point p
Scalar NodalQuad::interpolate_point(const Point &p) const {
  Scalar r, s;
  // SSC: the get_local_coordinates methods are expensive.  Since the probe
  // points don't move, we could cache this for each probe point so that they
  // don't have to be recomputed every time that Response::probe(...) gets
  // called
  if(!get_local_coordinates(p,r,s)) {
    DGM::Comm::World->cerr()
      <<"NodalQuad::interpolate_point: could not find (r,s)"<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }

  const Point q(r,s);
  return interpolate_local_point(q);
}

/// Extract the solution at the Point p
Scalar NodalQuad::interpolate_local_point(const Point &p) const {

  const Scalar r=p.x;
  const Scalar s=p.y;
  dMatrix im;
  dVector iv;

  // SSC: we should consider building these interpolation operators once and
  // then have a fast apply method to use them.

  // 2D interpolation in the b-direction

  // Form the interpolation matrix (vector) from Gauss-Lobatto-Legendre to s
  iv.resize(qb);
  im.alias(iv,1,qb);         // view vector as row matrix
  const dVector &zb=psi->zb; // Gauss-Lobatto-Legendre points
  igllm(im,zb,s);

  // Interpolate to temporary points at y=s at each x location
  dVector tmp(qa);
  dMatrix U(u,qa,qb);        // view u vector as matrix
  mvmult( U, iv, tmp);

  // 1D interpolation in the a-direction

  // Form the interpolation matrix from Gauss-Lobatto-Legendre to r
  iv.resize(qa);
  im.alias(iv,1,qa);         // view vector as row matrix
  const dVector &za=psi->za; // Gauss-Lobatto-Legendre points
  igllm(im,za,r);

  // interpolate along our temporary y points to get the value at r,s
  const Scalar result = dot(iv, tmp);

  return result;            // the interpolated solution is returned

}

void NodalQuad::calculate_interpolation_matrices(vector<dMatrix> &M,
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

void NodalQuad::apply_interpolation_matrices(dVector &V,
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
void NodalQuad::interpolate_points(const vector<Point> &ps,
                                   dVector &vals) const {
  if (state != Physical) {
    cerr << "NodalQuad::interpolate_points -- not in physical space"<<endl;
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

/// Use sparse local-global lift
#define USE_SPARSE_LIFT

/// Used to limit the number of times the side mass matrix is formed
#define DO_IT_ONCE

/// Select LU factorization over Cholesky
#define USE_LU

/** F->edges holds the upwind flux at the Gauss pts
    U->edges holds the interior flux at the Gauss pts   */
void NodalQuad::lift(const Element *const F, dVector &in, const char dir)const{
  //cout << "NodalQuad::lift for Eid = " << gid() << endl;
#ifdef DGM_TIME_NODAL_QUAD
  static FunctionTimer T("NodalQuad::lift");
  FunctionSentry sentry(T);
#endif
  const Element *const U = this;

  dMatrix In(in,qa,qb);
  dVector tmp(qa*qb);
  tmp = 0.0;
  dMatrix Tmp(tmp,qa,qb);

#ifdef DO_IT_ONCE
  static bool firsttime=true;
  //int const q = qa;
  Ordinal qedg = U->edge[0].qtot();
  static dMatrix V(qedg,qedg);
  static dVector Vcol(qedg);
  static dMatrix M1(qedg,qedg);
  static intVector pivots(qedg);
  if (firsttime) {
    // get the edge Vandermonde matrix
    for (Ordinal j=0; j<qedg; j++) {
      Vcol = psi->ba[j];
      for (Ordinal i=0; i<qedg; i++) V[i][j] = Vcol[i];
    }
    // get the edge mass matrix and factor
    matmult( V, 'T', V, M1 );
#ifdef USE_LU
    if (LU_factor(M1, pivots) !=0)
      DGM::Comm::World->error("LU_factor() failed.");
#else
    if (Cholesky_factor(M1) !=0)
      DGM::Comm::World->error("Cholesky_factor() failed.");
#endif
    firsttime = false;
  }
#endif

  // Edge 0
  {
    //int const q = qa;
    qedg = U->edge[0].qtot();
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
#ifdef USE_LU
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
#ifdef USE_LU
    LU_solve(M1, pivots, f);
#else
    Cholesky_solve(M1, f);
#endif
    // assemble into element storage
    dSlice column(Tmp.column(0));
    dvadd( f, column );
  }
  // Edge 1
  {
    //int const q = qb;
    qedg = U->edge[1].qtot();
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
#ifdef USE_LU
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
#ifdef USE_LU
    LU_solve(M1, pivots, f);
#else
    Cholesky_solve(M1, f);
#endif
    dVector row(Tmp.row(qa-1));
    dvadd( f, row );
  }
  // Edge 2
  {
    //int const q = qa;
    qedg = U->edge[2].qtot();
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
#ifdef USE_LU
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
#ifdef USE_LU
    LU_solve(M1, pivots, f);
#else
    Cholesky_solve(M1, f);
#endif
    dSlice column(Tmp.column(qb-1));
    dvadd( f, column );
  }
  // Edge 3
  {
    //int const q = qb;
    qedg = U->edge[3].qtot();
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
#ifdef USE_LU
    if (LU_factor(M1, pivots) !=0)
      DGM::Comm::World->error("LU_factor() failed.");
#else
    if (Cholesky_factor(M1) !=0)
      DGM::Comm::World->error("Cholesky_factor() failed.");
#endif
#endif
    dVector f(g1_wk,qedg);
    dvsub( F->edge[3].u, U->edge[3].u, f );
    dvmul( U->edge[3].J(), f);
    if (dir == 'x')
      dvmul( U->edge[3].nx(), f );
    else if (dir == 'y')
      dvmul( U->edge[3].ny(), f );
#ifdef USE_LU
    LU_solve(M1, pivots, f);
#else
    Cholesky_solve(M1, f);
#endif
    dVector row(Tmp.row(0));
    dvadd( f, row );
  }
  // Lift
  dVector ans(qa*qb);
  ans = 0.0;
#ifdef USE_SPARSE_LIFT
  // tmp2 = tmp with values on boundary
  static dVector tmp2(2*qa+2*qb-4);
  int j=0;
  for(Ordinal i=0; i<qa*qb; i++)
    if ((i<qa) || (i>qa*(qb-1)) || (i%qa==0) || (i%qa==(qa-1))) {
      tmp2[j] = tmp[i];
      j++;
    }
  mvmult(Mbound->mat, tmp2, ans);
#else
  // this is the old matrix-vector multiply (includes flux at interior)
  mvmult(M->mat, tmp, ans);
#endif
  dvadd( ans, in );
}

namespace {

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

}  // namespace

// collocation derivative matrix
void NodalQuad::get_derivative_matrix() {
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

/** This routine computes the gradient in physical space using the chain rule
    df/dx = df/dr * dr/dx + df/ds * ds/dx
    df/dy = df/dr * dr/dy + df/ds * ds/dy   */
void NodalQuad::gradient( const dVector &f, dVector &fx, dVector &fy ) const {
#ifdef DGM_TIME_NODAL_QUAD
  static FunctionTimer T("NodalQuad::gradient");
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

/** This method computes the gradient in only one direction */
void NodalQuad::gradient( const dVector &f, dVector &df, char dir) const {
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

/** Computes the local gradient in the master element (r,s) coordinates */
void NodalQuad::local_gradient( const dVector &f, dVector &fr, dVector &fs )
  const {
  dMatrix F(f,qa,qb);       // matrix alias of vector
  dMatrix Fr(fr,qa,qb);     // matrix alias of vector
  dMatrix Fs(fs,qa,qb);     // matrix alias of vector

  matmult( D->Da, F, Fr );  // df/da
  matmult( F, D->Dbt, Fs ); // df/db
}

void NodalQuad::interpolate_to_uniform() {
  cout << "NodalQuad::interpolate_to_uniform() is not implemented" << endl;
}

void NodalQuad::tecplot(FILE *fp) {
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
void NodalQuad::binaryOutput(FILE *fp, const OutputType flag) const {
  if (state == Transform)
    throw DGM::exception("NodalQuad::output called when in transform space");
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
    error("Illegal output type requested in NodalQuad::binaryOutput");
  }
}

/// Output requested element information to a file
streamoff NodalQuad::binaryLength(const OutputType flag) const {
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
    error("Illegal output type requested in NodalQuad::binaryLength");
  }
  error("Fell through case statement in NodalQuad::binaryLength");
  return 0;
}

void NodalQuad::output(FILE *fp, const char flag) const {
  if (state == Transform) {
    cerr << "NodalQuad::output in transform space" << endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  Ordinal q, c = 0;
  switch(flag) {
  case 'h':   // Tecplot header
    fprintf(fp,"\nZONE T=\"Element %llu\", ", (unsigned long long)gid());
    fprintf(fp,"I=%llu, J=%llu, F=BLOCK",(unsigned long long)qa,
            (unsigned long long)qb);
    break;
  case 'd':  // solution
    for (Ordinal j=0; j<qb; j++)
      for (Ordinal i=0; i<qa; i++) {
        q = j+i*qb;
        if (c++%5==0) fprintf(fp,"\n");
        fprintf(fp,"%15.8e ",u[q]);
      }
    break;
  case 'x':  // x-coordinates
    for (Ordinal j=0; j<qb; j++)
      for (Ordinal i=0; i<qa; i++) {
        q = j+i*qb;
        if (c++%5==0) fprintf(fp,"\n");
        fprintf(fp,"%15.8e ",C->x[q]);
      }
    break;
  case 'y':  // y-coordinates
    for (Ordinal j=0; j<qb; j++)
      for (Ordinal i=0; i<qa; i++) {
        q = j+i*qb;
        if (c++%5==0) fprintf(fp,"\n");
        fprintf(fp,"%15.8e ",C->y[q]);
      }
    break;
  case 'p':  // points
    for (Ordinal j=0; j<qb; j++)
      for (Ordinal i=0; i<qa; i++) {
        q = j+i*qb;
        fprintf(fp,"\n%15.8e %15.8e %15.8e ",C->x[q],C->y[q],0.0);
    }
    break;
  case 'c': // connectivity
    for (Ordinal i=0; i<qa-1; i++)
      for (Ordinal j=0; j<qa-1; j++) {
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
      for (Ordinal j=0; j<qa-1; j++) {
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
  case 'f':  // Tecplot footer
    break;
  default:
    throw DGM::exception("Illegal flag in NodalQuad::output value = "
                         +asString(flag));
  }
}

//============================================================================
//                        Norm and Error routines
//============================================================================

Scalar NodalQuad::norm_Linf() const {
  return norm_inf(u);
}

/** \warning This quadrature should be replace with local mass matrix. */
void NodalQuad::norm_L2(Scalar *L2, Scalar *area) const {
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
Scalar NodalQuad::norm_L2() const {
  Scalar L2, area;
  norm_L2( &L2, &area );
  return sqrt(L2/area);
}

/// Computes the H1 norm squared on the Element
/** \warning This quadrature should be replace with local mass matrix. */
void NodalQuad::norm_H1(Scalar *H1, Scalar *area) const {
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
Scalar NodalQuad::norm_H1() const {
  Scalar H1, area;
  norm_H1( &H1, &area );
  return sqrt(H1/area);
}

/// Integrates the data stored in the Element and optionally the volume
Scalar NodalQuad::integrate( Scalar *area ) const {
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

Scalar NodalQuad::integrate(const dVector &v, Scalar *area) const {
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

// This is a first stop towards having a self tuning, load balancing code The
// data here represents measurements from the MEMS Pentium IV Cluster for a
// simple Navier_Stokes problem.  The first index is polynomial order, the
// second is a flag for curved elmts.

// Ideas for improvement:
//   1) Have a more flexible database that also tracks the platform
//   2) Include a curve-fit to the data -- it looks quadratic so that
//      extrapolation to higher orders can be reasonably done.
//   3) Adjustments may be required for different problem types.
//
int NodalQuad::get_weight() const {
  static Ordinal Pmax = 10;
  static int Weight[11][2] = {{100, 100},
                              {109, 110},
                              {124, 134},
                              {153, 169},
                              {186, 212},
                              {202, 248},
                              {238, 308},
                              {267, 399},
                              {319, 572},
                              {362, 754},
                              {405, 1029}};
  int cflag = 0;
  if (curve.get()) cflag = 1;
  if (pOrder() > Pmax) {
    if (first_warn) {
      first_warn=false;
      cout << "WARNING - NodalQuad::get_weight(): "
           << "pOrder (="<<pOrder()<<") > Pmax (="<<Pmax<<")"<< endl;
    }
    return Weight[Pmax][cflag];
  } else
    return Weight[pOrder()][cflag];
}

Scalar NodalQuad::compute_measure() const {
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

/** \warning This quadrature should be replace with local mass matrix. */
Scalar NodalQuad::L2_inner_product(const Element *el, Scalar *area) const {
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

/** \warning This quadrature should be replace with local mass matrix. */
Scalar NodalQuad::L2_inner_product(const dVector& vh, const dVector& wh,
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

/** \warning Not implmented. */
void NodalQuad::get_side_Ds(const int sid, const dVector& dv,
                            dVector& dv_s) const {
  cout << "NodalQuad::get_side_Ds not implemented" << endl;
  DGM_UNDEFINED;
  Ordinal p, q;
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

  // form the new temporary volume u: wk
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
    cerr << "NodalQuad::Ds -- unknown side" << endl;
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

/*=============================================================================
   Vertices

           b
           |             Edge Order:  0) bottom {0,1}
       3-------2                      1) right  {1,2}
       |   |   |                      2) top    {2,3}
       |   +---|-- a                  3) left   {3,0}
       |       |
       0-------1

       s
       ^
       |
       |------>r

   One thought for the curvature calculation (Approximately) any curve
   including three points (x1,y1) (x2,y2) (x3,y3), assume the curvature
   circle is at (x0,y0) and its radius is R

   (x1-x0)^2+(y1-y0)^2 = R^2
   (x2-x0)^2+(y2-y0)^2 = R^2
   (x3-x0)^2+(y3-y0)^2 = R^2

   1/R = 2(x3*(y2-y1) + x2*(y1-y3) + x1*(y3-y2)) /
   (((x1-x2)^2+(y1-y2)^2)* ((x1-x3)^2+(y1-y3)^2)* (x3-x2)^2+(y3-y2)^2) )

   Second thought
   K = (x,r y,rr -y,r x,rr)/(x,r ^2 + y,r ^2)^1.5
=============================================================================*/

// Get the side curvature (x,y)->(r,s)
void NodalQuad::get_side_curvature( const int sid, dVector &dcurv) const {
  cout << "NodalQuad::get_side_curvature not available" << endl;
  DGM::Comm::World->exit(DGM::FAILURE);
}

void NodalQuad::get_D1( const int sid, dMatrix &dm1) const {
  cout << "NodalQuad::get_D1 not available" << endl;
  DGM::Comm::World->exit(DGM::FAILURE);
}

/// Apply and exponential 1d filter in both directions of tensor product
void NodalQuad::exp_filter(const Scalar eta, const Scalar s) {
  DGM_UNDEFINED;
  cout << "NodalQuad::exp_filter" << endl;
  bool needs_transform = false;
  if (state == Physical) {
    forward_transform();
    needs_transform = true;
  }
  Ordinal i, j, n;
  const Scalar alpha = -log(epsM);
  const Ordinal Nc = (Ordinal)(eta*L());
  // upper left
  for (i=0; i<Nc-1; i++) {
    for (j=Nc; j<L(); j++) {
      n = j + i*L();
      uh[n] *= exp(-alpha*pow((j-Nc+1)/(L()-Nc),s));
    }
  }
  // lower right
  for (j=0; j<Nc-1; j++) {
    for (i=Nc; i<L(); i++) {
      n = j + i*L();
      uh[n] *= exp(-alpha*pow((i-Nc+1)/(L()-Nc),s));;
    }
  }
  // upper right
  for (i=Nc; i<L(); i++) {
    for (j=Nc; j<L(); j++) {
      n = j + i*L();
      uh[n] *= exp(-alpha*pow((i-Nc+1)/(L()-Nc),s)) *
        exp(-alpha*pow((j-Nc+1)/(L()-Nc),s));
    }
  }
  if (needs_transform)
    backward_transform();
}

void NodalQuad::make_constant() {
  DGM_UNDEFINED;
  cout << "NodalQuad::make_constant()" <<endl;
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
  if (needs_transform) backward_transform();
}

void NodalQuad::low_modes(const Ordinal inp) {
  const Ordinal np = numeric_cast<Ordinal>(inp);
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
  if (needs_transform) backward_transform();
}

void NodalQuad::kill_constant() {
  DGM_UNDEFINED;
  bool needs_transform = false;
  if (state == Physical) {
    forward_transform();
    needs_transform = true;
  }
  uh[0] = 0.0;
  if (needs_transform) backward_transform();
}

void NodalQuad::coarse_scales(const int p_inc) {
  DGM_UNDEFINED;
  cout << "NodalQuad::coarse_scales(const int p)" <<endl;
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

void NodalQuad::coarse_scales(const int p_inc, dVector &vh) {
  cout << "NodalQuad::coarse_scales(const int p, dVector &vh)" <<endl;
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

void NodalQuad::fine_scales(const int p_inc) {
  DGM_UNDEFINED;
  cout << "NodalQuad::fine_scales(const int p)" <<endl;
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
  if (needs_transform) backward_transform();
}

void NodalQuad::fine_scales(const int p_inc, dVector &vh) {
  DGM_UNDEFINED;
  cout << "NodalQuad::fine_scales(const int p, dVector &vh)" <<endl;
  Ordinal i, j, n;
  // lower-left quadrant
  for (i=0; i<L()-p_inc; i++) {
    for (j=0; j<L()-p_inc; j++) {
      n = j + i*L();
      vh[n] = 0.0;
    }
  }
}

void NodalQuad::fine_scales_transform(const int p_inc, dVector &vh) const {
  DGM_UNDEFINED;
  cout << "NodalQuad::fine_scales_transform(const int p, dVector &vh)" <<endl;
  Ordinal i, j, n;
  forward_transform(vh,vh);
  // lower-left quadrant
  for (i=0; i<L()-p_inc; i++) {
    for (j=0; j<L()-p_inc; j++) {
      n = j + i*L();
      vh[n] = 0.0;
    }
  }
  backward_transform(vh,vh);
}

vector<dMatrix*> NodalQuad::get_interpolation_matrices() const {
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

} // namespace DGM
