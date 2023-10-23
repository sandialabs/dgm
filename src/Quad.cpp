/** \file Quad.cpp
    \brief Quad Element implementation
    \author S. Scott Collis

    Quad is a four node quadrilateral element that supports both affine and
    curved sided isoparametric mappings from the master element to the
    physical space element.
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
#include "Quad.hpp"
#include "Polylib.tpp"
#include "Utilities.hpp"

#ifdef DGM_USE_GENERAL_GHOSTING
/// register class for serialization of polymorphic types
BOOST_CLASS_EXPORT_GUID(DGM::Quad, "DGM::Quad");
#endif

/// Turn an argument into a string literal constant
#define STRING(x) #x

namespace DGM {

// define static storage

BasisDB Quad::bdb;                     // define Basis database
Quad::GeometryDB Quad::gdb("Quad");    // define Geom database
IMDB Quad::imdb;                       // define Interpolation Matrix database

Ordinal Quad::Qmax = 0;
Ordinal Quad::Lmax = 0;
dVector Quad::g1_wk;
dVector Quad::g2_wk;

dVector Quad::n1_wk;
dVector Quad::n2_wk;
dVector Quad::Lwk;

bool Quad::first_warn(true);

#ifdef DGM_USE_GTEST
TEST(QuadTest, True) {
  EXPECT_EQ(true, Quad::test());
}
#endif

#ifdef DGM_USE_MD_COUPLE

/// Constructor for coupled physics
/*! \param[in] ID    - Local element id
    \param[in] P     - Polynomial order
    \param[in] Q     - Quadrature order
    \param[in] X     - Vector of points defining the vertices
    \param[in] model - Model type */
Quad::Quad(const Size ID, const Ordinal P, const Ordinal Q,
           const vector<Point> &X, const Model::Type model)
  : BaseQuad(ID,Basis::Ortho) {
  nVerts(4);
  nEdges(4);
  nFaces(1);
  nSides(4);
  pOrder(P);
  L(P+1);
  nModes(L()*L());
  modeltype = model;

  // you might want to use different quadrature order in a and b
  qa = qb = Q; qc = 0;
  qtot = qa * qb;

  make_workspace(qtot,nModes);

  // construct vertex data-structure
  for (Ordinal i = 0; i < nVerts(); i++){
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

  // The convergence analysis of Cockburn & Shu (JCP 141, p.203 1998) requires
  // that the edge integrals be exact for polynomials of order (2p+1).  Since
  // we use Gauss-Legendre quadrature which is exact for polynomials of order
  // (2q-1) we must use q=p+1.  But, since qa=p+2, we can also set qedg=qa-1.
  edge.reserve(nEdges());
  for (Ordinal i=0; i<nEdges(); i++) {
    Ordinal qedg = (i==0 || i==2) ? qa-1 : qb-1;
    // cout << "Element = " << id << "qedg = " << qedg << endl;
    Edge ed(i,id,nModes,qedg,modeltype);
    edge.push_back(ed);
    side.push_back(&(edge[i]));
  }
}

#else  // !DGM_USE_MD_COUPLE

/// Constructor
/*! \param[in] ID    - Local element id
    \param[in] P     - Polynomial order
    \param[in] Q     - Quadrature order
    \param[in] X     - Vector of points defining the vertices */
Quad::Quad(const Ordinal ID, const Ordinal P, const Ordinal Q,
           const vector<Point> &X) : BaseQuad(ID,Basis::Ortho) {
  nVerts(4);
  nEdges(4);
  nFaces(1);
  nSides(4);
  pOrder(P);
  L(P+1);
  nModes(L()*L());

  if (Q<=1) throw DGM::exception("Quad::Quad modal q must be greater than 1 "
                                 "but q = "+asString(Q)+" for element "
                                 "global id = "+asString(ID));

  // you might want to use different quadrature order in a and b
  qa = qb = Q; qc = 0;
  qtot = qa * qb;

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
    Ordinal qedg = (i==0 || i==2) ? qa-1 : qb-1;
    // cout << "Element = " << id << "qedg = " << qedg << endl;
    Edge ed(i,this,nModes(),qedg,false);
    edge.push_back(ed);
    side.push_back( &(edge[i]) );
  }
}

#endif  // DGM_USE_MD_COUPLE

/// Copy constructor -- This should not allocate new space for P, M, etc.
Quad::Quad(const Quad *E) {
  // cout << "Quad copy constructor for Eid = " << E->gid() << endl;

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
Quad::~Quad() {}

/// Retrieves a basis from the basis database
/** If the basis is not in the database, makes a new basis and adds to
    database \todo Switch to a non-string key like the interpolation
    matrix. */
Basis* Quad::get_basis(const int der=0) const {
  // cout << "Quad::get_basis" << endl;
  Basis* b;
  char buf[128]={'\0'};
  sprintf(buf,"%lld_%lld_%lld_%lld_%lld_%lld",
      (long long)type,(long long)L(),(long long)der,
      (long long)qa,(long long)qb,(long long)qc);  // this still can be slow
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

/// Gets the mass matrix for this Quad
void Quad::get_mass_matrix() {
  //  cout << "Quad::get_mass_matrix for element " << id << endl;
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
    //cout << "Cholesky: 1" << endl;
    if (Cholesky_factor(M->mat) != 0) {
      DGM::Comm::World->cerr()<< "Quad: Cholesky_factor() failed." << endl;
      DGM::Comm::World->exit(DGM::FAILURE);
    }
#else
    if (LU_factor(M->mat, M->pivots) != 0) {
      DGM::Comm::World->cerr()<< "Quad: LU_factor() failed." << endl;
      DGM::Comm::World->exit(DGM::FAILURE);
    }
#endif
  }  else {
#ifdef DGM_BASIS_NORM
    // This only works when the Jacobian is constant
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
    // cout << "Mass matrix for elmt " << id << endl << M->mat << endl;
    for (Ordinal j=0; j<nModes(); j++) M->mat[0][j] = 1.0/M->mat[0][j];
#endif
  }
}

/// Resets the mass matrixing using a weighted mass matrix
/** \warning Might be dangerous to reset the mass matrix to this new value */
void Quad::get_mass_matrix(const dVector &x) {
  //cout << "Quad::get_mass_matrix(x) for element " << id << endl;
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

/// Solves (LU factors) the mass matrix (should use Cholesky)
void Quad::solve_mass_matrix(dVector &fh) const {
#ifdef DGM_TIME_QUAD
  static FunctionTimer T("Quad::solve_mass_matrix(dVector&)");
  FunctionSentry sentry(T);
#endif
#ifdef DGM_TEST_FOR_NORMAL
  if (!fh.isNormal())
    cout<<"Quad::solve_mass_matrix input not normal eid = " << gid() << endl;
#endif
  if (curve.get() || full_mass) {
    // cout << "Quad::solve_mass_matrix(...) for eid = " << gid() << endl;
#ifdef DGM_CHOLESKY_MASS_MATRIX
    Cholesky_solve(M->mat, fh);
#else
    LU_solve( M->mat, M->pivots, fh);
#endif
  } else {
    for (Ordinal i=0; i<nModes(); i++) fh[i] *= M->mat[0][i];
  }
#ifdef DGM_TEST_FOR_NORMAL
  fh.makeNormal();
  if (!fh.isNormal())
    cout<<"Quad::solve_mass_matrix output not normal eid = "<<gid()<<endl;
#endif
}

//=============================================================================

/// Computes the normal gradient on a supplied side
/** \note Be careful as we use n1_wk and n2_wk here. */
void Quad::normal_times_gradient_side(const dVector &f, const int sid,
                                      dVector &fssum ) const {
  dVector dfx( n1_wk, qtot );
  dVector dfy( n2_wk, qtot );
  gradient( f, dfx, dfy );
  load_side( dfx, sid, fssum );
  dvmul( side[sid]->nx(), fssum );
  dVector dfs( n1_wk, side[sid]->qtot() );
  load_side( dfy, sid, dfs );
  dvmul( side[sid]->ny(), dfs );
  dvadd( dfs, fssum );
}

/// Computes a mass matrix but does not factor it
/** \warning might be dangerous to reset the mass matrix to this new value. */
void Quad::get_local_mass_matrix(const dVector &factor) {
  // cout << "Quad::get_local_mass_matrix(x) for element " << id << endl;
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

/// Computes the local derivative matrix
/** \warning This implementation is very inefficient. */
void Quad::get_local_derivative_matrix() {
  // cout << "Quad::get_local_derivative_matrix for element " << id << endl;
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

/// Computes the local derivative matrix
/** \warning This implementation is very inefficient. */
void Quad::get_local_derivative_matrix(const dVector &factor) {
  // cout << "Quad::get_local_derivative_matrix for element " << id << endl;
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

/// Computes the local Laplace matrix
void Quad::get_local_laplace_matrix() {
  // cout << "Quad::get_local_laplace_matrix for element " << id << endl;
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

/// Computes the local Laplace matrix
void Quad::get_local_laplace_matrix(const dVector & factor) {
  // cout << "Quad::get_local_laplace_matrix for element " << id << endl;
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
void Quad::fill(string function_string, Operation operation) {
  state = Physical;
  //cout<<"Calling parser_init()"<<endl;
  parser_init();
  //cout<<"Calling VectorFunction"<<endl;
  Parser::VectorFunction f("x", "y", "t", function_string );
  //cout<<"Constructed VectorFunction"<<endl;
  f.evaluate( C->x, C->y, u, 0.0, convert(operation) );
  state = Physical;
}

/// Fill element with a mode
void Quad::fill(Mode &v) {
  //cout << "Quad::fill(Mode &)" << endl;
  dMatrix U(u,qa,qb);
  for (Ordinal i=0; i<qa; i++)
    for (Ordinal j=0; j<qb; j++) {
      //cout << "i, j = " << i << ", " << j << endl;
      U[i][j] = v.a[i] * v.b[j];
    }
  state = Physical;
}

/// Fill a vector with a mode
void Quad::fill(Mode &v, dVector &f) const {
  //cout << "Quad::fill(Mode &, dVector &)" << endl;
  dMatrix F(f,qa,qb);
  for (Ordinal i=0; i<qa; i++)
    for (Ordinal j=0; j<qb; j++) {
      F[i][j] = v.a[i] * v.b[j];
    }
}

/// Fill element with a random polynomial
void Quad::random() {
  // cout << "Quad::random()" << endl;
  state = Transform;
  for (Ordinal i=0; i<nModes(); i++) uh[i] = Element::random(-one,one);
  backward_transform();
}

/// Set the modes of an element
void Quad::set(const dVector &fh, const Ordinal nModes_) {
  // cout << "Quad::set(const dVector &, const int)" << endl;
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
void Quad::inner_product() {
  // cout << "Quad::inner_product for Eid = " << id << endl;
  inner_product(u, uh);
  state = Transform;
}

/// Computes the inner product of the supplied vector against the Basis
void Quad::inner_product(dVector &f, dVector &fh) const {
  // cout << "Quad::inner_product for Eid = " << id << endl;
#ifdef DGM_TIME_QUAD
  static FunctionTimer T("Quad::inner_product(dVector&,dVector&)");
  FunctionSentry sentry(T);
#endif
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
void Quad::forward_transform() {
  // cout << "Quad::forward_transform" << endl;
#ifdef DGM_TIME_QUAD
  static FunctionTimer T("Quad::forward_transform()");
  FunctionSentry sentry(T);
#endif
  if (state == Transform) {
    cerr << "Quad::transform -- already in transform space"<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  forward_transform(u,uh);
  state = Transform;
}

/// Transform the supplied data to polynomial space
/** This performs an L2 projection against the polynomial basis. */
void Quad::forward_transform(dVector &f, dVector &fh) const {
  // cout << "Quad::forward_transform" << endl;
#ifdef DGM_TIME_QUAD
  static FunctionTimer T("Quad::forward_transform(dVector&,dVector&)");
  FunctionSentry sentry(T);
#endif
#ifdef DGM_MAKE_NORMAL
  f.makeNormal();
#endif
#ifdef DGM_TEST_FOR_NORMAL
  if (!f.isNormal())
    cout << "Quad::forward_transform input is not normal number eid  = "
         << gid() << endl;;
#endif
  inner_product(f,fh);
#ifdef DGM_MAKE_NORMAL
  f.makeNormal();
#endif
#ifdef DGM_TEST_FOR_NORMAL
  if (!fh.isNormal())
    cout << "Quad::forward_transform inner prod is not normal number eid  = "
         << gid() << endl;;
#endif
  solve_mass_matrix(fh);
#ifdef DGM_TEST_FOR_NORMAL
  if (!fh.isNormal())
    cout << "Quad::forward_transform result is not normal number eid  = "
         << gid() << endl;;
#endif
#ifdef DGM_MAKE_NORMAL
  fh.makeNormal();
#endif
}

/// Transform using another Elements mass matrix (dangerous)
void Quad::forward_transform(Element *F, Element *) {
  // cout << "Quad::forward_transform(*F,*)" << endl;
#ifdef DGM_TIME_QUAD
  static FunctionTimer T("Quad::forward_transform(Element*,Element*)");
  FunctionSentry sentry(T);
#endif
  if (state == Transform) {
    cerr << "Quad::transform -- already in transform space"<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  inner_product(u,uh);
  F->solve_mass_matrix(uh);  // Use element F's Mass matrix
  state = Transform;
}

/// Return Element to physical space
void Quad::backward_transform() {
#ifdef DGM_TIME_QUAD
  static FunctionTimer T("Quad::backward_transform()");
  FunctionSentry sentry(T);
#endif
  if (state == Physical) {
    cerr << "Quad::transform_to_physical -- already in physical space"<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  backward_transform( uh, u );
  state = Physical;
}

/// Transform supplied data to physical space on this Element
void Quad::backward_transform(dVector &fh, dVector &f) const {
#ifdef DGM_TIME_QUAD
  static FunctionTimer T("Quad::backward_transform(dVector&,dVector&)");
  FunctionSentry sentry(T);
#endif
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
}

/// Extracts data onto a specified Side
void Quad::get_side(const dVector &from, const Ordinal sid, dVector &to) const {
  // cout<<"Quad::get_side() Element = "<<id<<" Side = "<<sid<<endl<<to<<endl;
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
    throw DGM::exception("Quad::get_side -- unknown side");
  }
}

/// Makes an interpolation matrix
void Quad::make_interpolation_matrix(const Ordinal q1, const Ordinal q2,
                                     const Interp::Type interp,
                                     dMatrix &im ) {
  //  cout << "Quad::make_interpolation_matrix" << endl;
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
    cerr << "Quad::make_interpolation_matrix - Invalid interpolation type"
         << endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
}

/// Returns an interpolation matrix (making one if needed)
dMatrix* Quad::get_interpolation_matrix(const Ordinal q1, const Ordinal q2,
                                        const Interp::Type interp=
                                        Interp::GL2G) {
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

/// Interpolate supplied physical space values "f" to the side Gauss points.
void Quad::fill_sides(const dVector &f) {
  dVector wka(g1_wk,qa);
  dVector wkb(g2_wk,qb);
  dMatrix *im;

  im = get_interpolation_matrix( side[0]->qtot(), qa, Interp::GL2G);
  get_side(f,0,wka);
  mvmult( *im, wka, side[0]->u );

  im = get_interpolation_matrix( side[1]->qtot(), qb, Interp::GL2G);
  get_side(f,1,wkb);
  mvmult( *im, wkb, side[1]->u );

  im = get_interpolation_matrix( side[2]->qtot(), qa, Interp::GL2G);
  get_side(f,2,wka);
  mvmult( *im, wka, side[2]->u );

  im = get_interpolation_matrix( side[3]->qtot(), qb, Interp::GL2G);
  get_side(f,3,wkb);
  mvmult( *im, wkb, side[3]->u );

#ifdef DGM_ALLOW_HANGING_NODES
  push_to_subsides();
#endif
}

/// Interpolate physical space values "f" to a uniform mesh on the sides.
/** \todo Make a load_sides_uniform() that, similar to load_sides() fills a
    supplied side data-structure instead of the current sides. */
void Quad::fill_sides_uniform(const dVector &f) {
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
void Quad::fill_sides(const dVector &fx, const dVector &fy) {
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

  im = get_interpolation_matrix( edge[1].qtot(), qb, Interp::GL2G);
  wk.alias(Lwk,edge[1].qtot());
  get_side(fx,1,wkb);
  mvmult( *im, wkb, edge[1].u );
  get_side(fy,1,wkb);
  mvmult( *im, wkb, wk );
  dvmul( edge[1].nx(), edge[1].u );
  dvvtvp( edge[1].ny(), wk, edge[1].u, edge[1].u );

  im = get_interpolation_matrix( edge[2].qtot(), qa, Interp::GL2G);
  wk.alias(Lwk,edge[2].qtot());
  get_side(fx,2,wka);
  mvmult( *im, wka, edge[2].u );
  get_side(fy,2,wka);
  mvmult( *im, wka, wk );
  dvmul( edge[2].nx(), edge[2].u );
  dvvtvp( edge[2].ny(), wk, edge[2].u, edge[2].u );

  im = get_interpolation_matrix( edge[3].qtot(), qb, Interp::GL2G);
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
void Quad::load_side(const dVector &f, const Ordinal side_number, dVector &g)
  const {
  dVector wka(g1_wk,qa);
  dVector wkb(g2_wk,qb);
  dMatrix *im;
  switch(side_number) {
  case 0:
    im = get_interpolation_matrix( side[side_number]->qtot(), qa, Interp::GL2G);
    get_side(f,side_number,wka);
    mvmult( *im, wka, g );
    break;
  case 1:
    im = get_interpolation_matrix( side[side_number]->qtot(), qb, Interp::GL2G);
    get_side(f,side_number,wkb);
    mvmult( *im, wkb, g );
    break;
  case 2:
    im = get_interpolation_matrix( side[side_number]->qtot(), qa, Interp::GL2G);
    get_side(f,side_number,wka);
    mvmult( *im, wka, g );
    break;
  case 3:
    im = get_interpolation_matrix( side[side_number]->qtot(), qb, Interp::GL2G);
    get_side(f,side_number,wkb);
    mvmult( *im, wkb, g );
    break;
  default:
    cerr << "Quad::load_side():invalid side number. Should be one of 0,1,2,3"
         << endl;
    DGM::Comm::World->exit(DGM::FAILURE);;
  }
}

/// Compute coordinates of quadrature points
void Quad::get_coordinates() {
  //  cout << "Quad::get_coordinates for element " << id << endl;
  if (curve.get())
    get_curved_coordinates();
  else
    get_straight_coordinates();
}

/// Compute coordinates for a straight-sided Element
void Quad::get_straight_coordinates() {
  // cout << "Quad::get_straight_coordinates for element " << id << endl;
  // C.resize(qtot); C = 0.0;
  C.reset( new Coord(qtot) ); *C = 0;
  dMatrix phi(qa,qb);
  for (Ordinal n = 0; n<nVerts(); n++) {
    for (Ordinal i=0; i<qa; i++) {        // fill basis matrix
      for (Ordinal j=0; j<qb; j++) {
        //phi[i][j] = psi->vert[n].a[i] * psi->vert[n].b[j];
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
void Quad::J_backward_transform(dVector &fh, dVector &f) {
  // cout << "Quad::J_backward_transform for elmt = " << id << endl;
  dMatrix B;
  dMatrix Fh( fh, L(), L() );                 // Fh[Lb,La]
  dMatrix  F( f, qa, qb);                     // F[qa,qb]
  dMatrix wk( Lwk, L(), qa );                 // wk[Lb,qa]
  B.alias( psi->amem, L(), qa );              // B[La,qa]
  matmult( Fh, B, wk );                       // Fh[Lb,La] B[La,qa] = wk[Lb,qa]
  B.alias( psi->bmem, L(), qb );              // B[Lb,qb]
  matmult( 'T', wk , B, F );                  // wk[qa,Lb] B[Lb,qb] = F[qa,qb]
  // We could have done
  // wk[La,qb] = Fh[La,Lb] B[Lb,qb];
  // F[qa,qb] = wk[qb,La] B[La,qa];
  // and this would have matched Tri better since it is better to do the
  // b-modes first for Tri's.  Of course, for Quads, since we do a tensor
  // product and current qa = qb then it really doesn't matter.
}

/// Computes the curved nodal coordinates using the Modified-Jacobi basis
/** \pre Must have a valid and populated Curve data-structure
    \pre Must have already called get_basis() and have the modifed-Jacobi
         basis available
    \verbatim
      Fh = { v0 v1 e0 e0 e0 }
           { v3 v2 e2 e2 e2 }
           { e3 e1          }
           { e3 e1          }
           { e3 e1          }
   \endverbatim
*/
void Quad::get_curved_coordinates() {
  // cout << "Quad::get_curved_coordinates()" << endl;
  Ordinal i, j, l, m;
  C.reset( new Coord(qtot) ); *C = 0;
  dVector fh(nModes());
  fh = 0;
  // copy xh into fh (lay 'a' modes first)
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

  // copy yh into fh (lay 'a' modes first)
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
void Quad::get_side_coordinates(const Ordinal nedge, Point *pedge) const {
  dVector wka, px, py;
  dMatrix *im;
  Ordinal q = (nedge==0 || nedge==2) ? qa:qb;
  im = get_interpolation_matrix(edge[nedge].qtot(), q, Interp::GL2G); // to,from
  wka.resize(q);
  px.resize(edge[nedge].qtot());
  py.resize(edge[nedge].qtot());
  switch(nedge) {
  case 0: case 1: case 2: case 3:
    get_side(C->x,nedge,wka);  // wk is at Gauss-Lobatto points
    mvmult( *im, wka, px);     // interpolate to Gauss
    get_side(C->y,nedge,wka);
    mvmult( *im, wka, py );
    for(Ordinal i=0; i<edge[nedge].qtot(); i++) pedge[i] = Point(px[i],py[i]);
    break;
  default:
    cerr << "Quad::get_side_coordinates illegal edge id." << endl;
    DGM::Comm::World->exit();
  }
}

/// Compute the geometric factors for the element
Element::StabMetrics Quad::compute_metrics() {
  return compute_metrics_2d_tensor_prod();
}

/// Compute the geometry of the element
void Quad::compute_geometry() {
  // cout << "Quad::compute_geometry for element " << id() << endl;
  geom.reset( new Geometry( lid(), 2, nVerts(), qtot ) );
  if (curve.get()) {
    compute_curved_geometry();
  } else {
    compute_straight_geometry();
  }
  measure(compute_measure());  // area
#ifdef DGM_USE_GEOM_DB
  gdb.add(geom);
#endif
}

/// Determine whether an element is affine
/** Determine, consistent with the tolerances used in compute_straight_geometry
    whether this is an affine element. */
bool Quad::is_affine() const {
  // cout << "Quad::is_affine element " << gid() << endl;

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
    otherwise).  It now throws an error if you try to use this method on a
    nonaffine element.

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
    This particular version takes advantage of the fact that the Jacobian
    matrix is constant for an affine element.
*/
void Quad::compute_straight_geometry() {
  //  cout << "Quad::compute_straight_geometry for element " << gid() << endl;
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
    cerr << "ERROR:  Quad::compute_straight_geometry()" << endl
         << "  Jacobian is not constant for Element " << gid() << endl;
    cout << "  xr = " << xr << " : " << xr-(vert[2]->x - vert[3]->x)*pt5<<endl;
    cout << "  xs = " << xs << " : " << xs-(vert[2]->x - vert[1]->x)*pt5<<endl;
    cout << "  yr = " << yr << " : " << yr-(vert[2]->y - vert[3]->y)*pt5<<endl;
    cout << "  ys = " << ys << " : " << ys-(vert[2]->y - vert[1]->y)*pt5<<endl;
    cerr << "This means that you have a non-affine element in your mesh "
        "that you are\ntreating as a straight sided parallelogram.  "
        "Revise/correct your mesh for this\nelement or declare this "
        "element as a \"Straight\" element in your root.crv file."<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
#endif

  // compute determinate of the Jacobian
  Scalar detJ = xr*ys - xs*yr;
  if(detJ <= 0.0)
    cerr << "Element " << gid() <<" has a non-positive Jacobian" << endl;
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
void Quad::compute_curved_geometry() {
  //  cout << "Quad::compute_curved_geometry for element " << id << endl;

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
  // Compute metrics for CFL and timestep size (stability) estimates.
  compute_metrics();
#endif // DGM_STORE_METRICS
}

/// Compute the stability metrics for timestep size calucations.
/// Computes geometric factors for the Element Sides
void Quad::compute_side_geometry() {
  // cout << "Quad::compute_side_geometry(), Eid = "<< id << endl;
  sigma(0.0);
  for (Ordinal i=0; i<nEdges(); i++) {
    Edge &e = edge[i];
    Ordinal qedg = e.qtot();
    // cout << "Edge " << i << ", qedg = " << qedg << endl;
    Ordinal q = (i==0 || i==2) ? qa:qb;
    dMatrix &Der = (i==0 || i==2) ? D->Da : D->Db;
    dMatrix *im;
    im = get_interpolation_matrix( qedg, q, Interp::GL2G);  // to, from
    {
      dVector wkx(q), wky(q);
      const dVector &X = (i==0 || i==2) ? geom->sx : geom->rx ;
      const dVector &Y = (i==0 || i==2) ? geom->sy : geom->ry ;
      get_side(X,i,wkx);
      get_side(Y,i,wky);
#ifdef DGM_INTERPOLATE_UNIT_NORMALS
      for (int j=0; j<q; j++) {
        const Scalar len = 1.0/sqrt( wkx[j]*wkx[j] + wky[j]*wky[j] );
        wkx[j] *= len;
        wky[j] *= len;
      }
#endif
      mvmult( *im, wkx, edge[i].nx() );   // interpolate to Gauss
      mvmult( *im, wky, edge[i].ny() );
      if (i==0 || i==3) {
        scale( -1.0, edge[i].nx() );       // negate since on bottom
        scale( -1.0, edge[i].ny() );
      }
    }
    dVector wk(q);
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

    // interpolate to Gauss points
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
void Quad::forward_transform_side(dVector &f, dVector &fh) {
  //  cout << "Quad::forward_transform_side(), Eid = "<< id << endl;
  const dVector &wa=psi->wa;
  fh.resize(L()-2);
  // subtract off vertices
#if 0
  daxpy( -f[0], psi->vert[0].a, f );
  daxpy( -f[qa-1], psi->vert[1].a, f);
#else
  daxpy( -f[0], psi->vertMode(0).a, f );
  daxpy( -f[qa-1], psi->vertMode(1).a, f);
#endif
  dvmul( wa, f );
  dVector edge;
  for (Ordinal i=0; i<L()-2; i++) {
    fh[i] = dot(psi->edgeMode(0,i).a, f);
  }
  if (L()-2) solve_1d_mass_matrix(fh);
}

/// Solve a 1d (edge) mass matrix for forward_transform_side()
void Quad::solve_1d_mass_matrix(dVector &fh) const {
  Minfo M1d;
  get_1d_mass_matrix(M1d);
#ifdef DGM_CHOLESKY_MASS_MATRIX
  Cholesky_solve(M1d.mat, fh);
#else
  LU_solve(M1d.mat, M1d.pivots, fh);
#endif
}

/// Compute the 1d mass matrix for curved sides
void Quad::get_1d_mass_matrix(Minfo &M1d) const {
  const dVector &wa=psi->wa;
  dVector w, psi1, psi2, tmp(qa-2);
  M1d.mat.resize(L()-2,L()-2);
  M1d.pivots.resize(L()-2);
  dVector edge;
  for (Ordinal i=0; i<L()-2; i++) {
    w.alias(wa,1,qa-2);
    psi1.alias(psi->edgeMode(0,i).a,1,qa-2);
    dvmul(w, psi1, tmp);
    for (Ordinal j=0; j<L()-2; j++) {
      psi2.alias(psi->edgeMode(0,j).a,1,qa-2);
      M1d.mat[i][j] = dot(tmp, psi2);
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
Scalar Quad::compute_side_integral( dVector &f, Ordinal sid ) const {
  // cout << "Quad::compute_side_integral(dVector &, int) for Eid = "
  //      << this->id << ", Sid = " << sid << endl;
  // cout << " f = " << endl << f << endl;
  dvmul( side[sid]->J(), f);
  // cout << " J/interior_J * f = " << endl << f << endl;
  const Ordinal qsid = side[sid]->qtot();
  const Ordinal q = (sid==0 || sid==2) ? qa:qb;
  dVector wk(q);
  get_side(geom->J,sid,wk);       // extract interior J on edge
  dVector wks(qsid);  // interior_J
  const dMatrix *const im
    = get_interpolation_matrix( qsid, q, Interp::GL2G);  // to, from
  mvmult( *im, wk, wks );
  dvmul( wks, f );
  // cout << " J * f = " << endl << f << endl;
  static dVector w;
  if (w.size() != (Ordinal)qsid) {
    w.resize(qsid);
    zwgl(wks,w);                 // Gauss-Legendre
  }
  const Scalar I = dot( f, w );
  // cout<<"Eid = " << this->id << ", Sid = " << sid << ", I = " << I << endl;
  return I;
}

/// Return the measure (parameter in this case) of the elements sides
Scalar Quad::compute_side_measure() const {
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
void Quad::add_Dirac_delta(const Ordinal qpt, const Scalar amp) {
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
    p with amplitude equal amp. The Point, p, must be within the Quad
    element. */
void Quad::add_Dirac_delta(const Point &p, const Scalar amp) {
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

/// Add a Dirac delta given local element coordinates
void Quad::add_local_Dirac_delta(const Point &p, const Scalar amp) {
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

/// Add multiple Dirac deltas simultaneous specified in local coordinates
void Quad::add_local_Dirac_delta(const vector<dMatrix> &M, const Scalar amp) {
  if (2!=M.size())
    error("Quad::add_local_Dirac_delta: Incorrect matrix size.");
  if (M[0].rows() != M[1].rows())
    error("Quad::add_local_Dirac_delta: Inconsistant matrix size.");
  if (M[0].cols() != qb || M[1].cols() != qa)
    error("Quad::add_local_Dirac_delta: Inconsistant matrix size.");

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

/// Extract the solution at the Point p in global coordinates
Scalar Quad::interpolate_point(const Point &p) const {
  Scalar r, s;
  // SSC: the get_local_coordinates methods are expensive.  Since the probe
  // points don't move, we could cache this for each probe point so that they
  // don't have to be recomputed every time that Response::probe(...) gets
  // called
  if(!get_local_coordinates(p,r,s)) {
    DGM::Comm::World->cerr()
      <<"Quad::interpolate_point: could not find (r,s)"<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  const Point q(r,s);
  return interpolate_local_point(q);
}

/// Extract the solution at the Point p given in local element coordinates
Scalar Quad::interpolate_local_point(const Point &p) const {
  const Scalar r=p.x;
  const Scalar s=p.y;
  dMatrix im;
  dVector iv;

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

/// Calculate interpolation matrices (float version)
void Quad::calculate_interpolation_matrices(vector<fMatrix> &M,
                                            const vector<Point>& P) const {
  const Ordinal N = numeric_cast<Ordinal>(P.size());

  M.resize(2);
  M[0].resize(N,qb);
  M[1].resize(N,qa);

  fVector z(qb), w(qb);
  zwgll(z, w);
  fVector X(N);

  for (Ordinal i=0; i<N; ++i) X[i] = P[i].y;
  igllm(M[0],z,X);

  if (qa != qb) {
    z.resize(qa); w.resize(qa);
    zwgll(z,w);
  }
  for (Ordinal i=0; i<N; ++i) X[i] = P[i].x;
  igllm(M[1],z,X);
}

/// Apply interpolation matrices to a vector (float version)
void Quad::apply_interpolation_matrices(dVector &V,
                                        const vector<fMatrix> &M) const {
  if (state != Physical) {
    cerr << "Quad::apply_interpolation_matrices -- not in physical space"<<endl;
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

/// Compute interpolation matrices (double version)
void Quad::calculate_interpolation_matrices(vector<dMatrix> &M,
                                            const vector<Point> &P) const {
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

/// Apply interpolation matrices (double version)
void Quad::apply_interpolation_matrices(dVector &V,
                                        const vector<dMatrix> &M) const {
  if (state != Physical) {
    cerr << "Quad::apply_interpolation_matrices -- not in physical space"<<endl;
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

/// Extract the solution at the vector of Points
/** This is a vectorized version of Quad::interpolate_points. */
void Quad::interpolate_points(const vector<Point>& ps, dVector &vals) const {
  if (state != Physical) {
    cerr << "Quad::interpolate_points -- not in physical space"<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }

  const Ordinal N = numeric_cast<Ordinal>(ps.size());

  // 2D interpolation
  dVector z(qb), w(qb);
  // Compute Gauss-Lobatto-Legendre points and weights
  zwgll(z, w); // y direction
  dMatrix M(N,qb);
  dVector X(N);
  for (Ordinal i=0; i<N; ++i) X[i] = ps[i].y;

  // Form the interpolation matrix from Gauss-Lobatto-Legendre to X
  igllm(M,z,X);

  dMatrix T(N,qa);
  dMatrix U(u,qa,qb);
  matmult(M, 'T', U, T);

  // 1D interpolation in the a-direction
  if (qa != qb) {
    z.resize(qa); w.resize(qa);
    zwgll(z,w);
    M.resize(N,qa);
  }
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

namespace {

void var_p_lift(dVector       &in,
                const Element *const U,
                const Side    *const Fs,
                const Basis   *psi,
                const Ordinal e,
                const char    dir)
{
  cout<<"Quad::var_p_lift for eid = "<<U->gid()<<endl;
  const Scalar SmallJacobian(0.000001);
  const int L = numeric_cast<int>(psi->Ba.rows());
  const Ordinal qa = psi->Ba.cols();
  const Ordinal qb = psi->Bb.cols();
  const Side *Us = U->side[e];
  const Ordinal len = numeric_cast<Ordinal>(Us->u.size());

  if (Us->J().size() != len) {
    cerr<<DGM::Comm::World->MyPID() <<" "
      <<__FILE__<<":"<<__LINE__<<" Aborting!"<<endl;
    error("Quad::var_p_lift: bad Jacobian size");
  }
#ifdef DGM_SIDE_FLUX_TO_VOLUME
  if (Us->J_orig().size() < len) {
    cerr<<__FILE__<<":"<<__LINE__<<" Aborting!"<<endl;
    error("Quad::var_p_lift: J_orig buffer size");
  }
#endif
  for (Ordinal i=0; i<len; ++i) {
    if (Us->J(i) < SmallJacobian) {
      cerr<<DGM::Comm::World->MyPID() <<" "
         <<__FILE__<<":"<<__LINE__<<" Aborting!"<<endl;
      cerr<<" Us->J["<<i<<"]:"<<Us->J(i)<<" < "<<SmallJacobian<<endl;
      error("Quad::var_p_lift: bad Jacobian");
    }
#ifdef DGM_SIDE_FLUX_TO_VOLUME
    if (Us->J_orig()[i] < SmallJacobian) {
      cerr<<DGM::Comm::World->MyPID() <<" "
         <<__FILE__<<":"<<__LINE__<<" Aborting!"<<endl;
      cerr<<" Us->J["<<i<<"]:"<<Us->J(i)<<" <  "<<SmallJacobian<<endl;
      error("Quad::var_p_lift: bad Jacobian");
    }
#endif
  }

  dVector f(len);
  dVector z(len);
  dVector w(len);
  zwgl(&z[0],&w[0],Ordinal(len));
  // The function we want to integrate is the difference in flux
  // across the boundary times the Jacobi weights times the
  // integration weights with an optional dotted to normal vector
  for (Ordinal i=0; i<len; ++i) f[i] = (Fs->u[i] - Us->u[i]) * w[i] * Us->J(i);
#ifdef DGM_MAKE_NORMAL
  f.makeNormal();
#endif
  if (dir == 'x')
    for (Ordinal i=0; i<len; ++i) f[i] *= Us->nx(i);
  else if (dir == 'y')
    for (Ordinal i=0; i<len; ++i) f[i] *= Us->ny(i);

  dVector fh(L*L);
  dMatrix FH(fh,L,L);
  dMatrix B(L,len);

  Basis::make_Legendre(0,L,len,z,B);
  switch (e) {
  case 0: {
    dMatrix wk(L,qb); wk=0;
    dSlice col(wk.column(0));
    // Multiply B by f will integrate in 1D the Legendre polynomials times the
    // flux function over the whole side of the element.
    mvmult (  B, f, col);
    // Since this is a 2D element, there is still one more integral over the
    // element to get the 2D Legendre polynomial coefficients.
    matmult( wk, 'T',  psi->Bb, FH);
    break;
  }
  case 1: {
    dMatrix wk(qa,L); wk=0;
    dMatrix row(wk.row(qa-1),1,L);
    dMatrix F(f,1,len);
    matmult( F, 'T',  B, row);
    matmult( psi->Ba, wk, FH);
    break;
  }
  case 2: {
    dMatrix wk(L,qb); wk=0;
    dSlice col(wk.column(qb-1));
    mvmult (  B, f, col);
    matmult( wk, 'T',  psi->Bb, FH);
    break;
  }
  case 3: {
    dMatrix wk(qa,L); wk=0;
    dMatrix row(wk.row(0),1,L);
    dMatrix F(f,1,len);
    matmult( F, 'T',  B, row);
    matmult( psi->Ba, wk, FH);
    break;
  }
  default:
    throw DGM::exception("Invalid case " __FILE__ " at line " STRING(__LINE__));
  }
  // The result up to now is an L by L matrix of Legendre polynomial
  // modal coefficients defined over the whole quad that is the
  // transformation of the Lagrange basis over the side to the Legendre
  // basis.  Now transform back to the Lagrange basis.  This is just
  // how DGM implements the flux and source contributions: first add
  // them into the Lagrange nodal basis and later there will a transformation
  // back to the Legendre polynomial modal basis.  Seems inefficient
  // but is easier to implement and seems to work fine.
  dVector In(qa*qb); In=0;
  U->backward_transform(fh, In);
  for (Ordinal i=0; i<qa*qb; ++i) in[i] += In[i];
}

} // anonymous namespace

void Quad::local_lift(dVector &in,
                      const Element *const F,
                      const Ordinal e,
                      const Ordinal q,
                      const Ordinal qedg,
                      const char dir) const
{
#ifdef DGM_SIDE_FLUX_TO_VOLUME
  static const bool no_sum_to_volume=false;
#else
  static const bool no_sum_to_volume=true;
#endif
  const Element *const U = this;
  dMatrix In(in,qa,qb);
  dVector f (g1_wk,qedg);
  dVector fi(g2_wk,   q);
  dvsub( F->edge[e].u, U->edge[e].u, f );
  dvmul( U->edge[e].J(), f);
  if      (dir == 'x') dvmul( U->edge[e].nx(), f );
  else if (dir == 'y') dvmul( U->edge[e].ny(), f );
  const dMatrix *im = get_interpolation_matrix(q, qedg, Interp::G2GL);
  mvmult( *im, f, fi );
#ifdef DGM_MAKE_NORMAL
  fi.makeNormal();
#endif
  switch (e) {
  case 0:
    if (U->edge[0].qtot() <= qa-1 || no_sum_to_volume) {
      const dVector &wb = U->psi->wb;
      scale( one/wb[0], fi );
      dSlice column(In.column(0));
      dvadd( fi, column );
    } else {
      var_p_lift(in, U, F->side[0], psi, 0, dir);
    }
    break;
  case 1:
    if (U->edge[1].qtot() <= qb-1 || no_sum_to_volume) {
      const dVector &wa = U->psi->wa;
      scale( one/wa[qa-1], fi );
      dVector row(In.row(qa-1));
      dvadd( fi,  row );
    } else {
      var_p_lift(in, U, F->side[1], psi, 1, dir);
    }
    break;
  case 2:
    if (U->edge[2].qtot() <= qa-1 || no_sum_to_volume) {
      const dVector &wb = U->psi->wb;
      scale( one/wb[qb-1], fi );
      dSlice column(In.column(qb-1));
      dvadd( fi,  column );
    } else {
      var_p_lift(in, U, F->side[2], psi, 2, dir);
    }
    break;
  case 3:
    if (U->edge[3].qtot() <= qb-1 || no_sum_to_volume) {
      const dVector &wa = U->psi->wa;
      scale( one/wa[0], fi );
      dVector row(In.row(0));
      dvadd( fi, row );
    } else {
      var_p_lift(in, U, F->side[3], psi, 3, dir);
    }
    break;
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
      error("Quad::subside_lift: bad Jacobi size");
    }
    if (uss->u.size() != sub_len) {
      cerr<<__FILE__<<":"<<__LINE__<<" Aborting!"<<endl;
      cerr<<" uss->u.size()"<<uss->u.size()<<" != sub_len:"<<sub_len<<endl;
      error("Quad::subside_lift: bad buffer size");
    }
    vector<Scalar> w(sub_len);
    dVector x(sub_len);
    {
      vector<Scalar> t(sub_len);
      zwgl(&t[0],&w[0],sub_len);
    }
    {
      dVector z(qedg);
      dVector t(qedg);
      zwgl(&z[0],&t[0],qedg);
      // Push the Gauss-Legendre subside integration points
      // to the Quad frame of reference so the Legendre
      // Polynomials can be evaluated at these points.
      uss->push_to_subside(z,x);
    }
    if (uss->J_orig().size() < sub_len) {
      cerr<<__FILE__<<":"<<__LINE__<<" Aborting!"<<endl;
      error("Quad::subside_lift: J_orig buffer size");
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
        error("Quad::subside_lift: bad Jacobian");
      }
      if (     w[i] < .000001) {
        cerr<<__FILE__<<":"<<__LINE__<<" Aborting!"<<endl;
        cerr<<" w["<<i<<"]:"<<w[i]<<" <  .000001"<<endl;
        error("Quad::subside_lift: bad weight");
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
  dVector fh(L*L);
  dMatrix FH(fh,L,L);

  // So we want to do the integral over the first L Legendre polynomials, P_l
  // over the sum of the subside lengths.  This is how the coefficients of the
  // Legendre modal basis are determined.  There are a total of 'len' Gauss
  // points over the whole of all the subsides and these are defined at the
  // points X_i.  Thus the 'B' matrix is L rows and len columns.
  dMatrix B(L,len);
  Basis::make_Legendre(0,L,len,X,B);
  switch (e) {
  case 0: {
      dMatrix wk(L,qb); wk=0;
      dSlice col(wk.column(0));
      // Multiply B by f will integrate in 1D the Legendre polynomials times the
      // flux function over the whole side of the element.
      mvmult (  B, f, col);
      // Since this is a 2D element, there is still one more integral over the
      // element to get the 2D Legendre polynomial coefficients.
      matmult( wk, 'T',  psi->Bb, FH);
    }
    break;
  case 1: {
      dMatrix wk(qa,L); wk=0;
      dMatrix row(wk.row(qa-1),1,L);
      dMatrix F(f,1,len);
      matmult( F, 'T',  B, row);
      matmult( psi->Ba, wk, FH);
    }
    break;
  case 2: {
      dMatrix wk(L,qb); wk=0;
      dSlice col(wk.column(qb-1));
      mvmult (  B, f, col);
      matmult( wk, 'T',  psi->Bb, FH);
    }
    break;
  case 3: {
      dMatrix wk(qa,L); wk=0;
      dMatrix row(wk.row(0),1,L);
      dMatrix F(f,1,len);
      matmult( F, 'T',  B, row);
      matmult( psi->Ba, wk, FH);
    }
    break;
  }
  // The result up to now is an L by L matrix of Legendre polynomial
  // modal coefficients defined over the whole quad that is the
  // transformation of the Lagrange basis over the side to the Legendre
  // basis.  Now transform back to the Lagrange basis.  This is just
  // how DGM implements the flux and source contributions: first add
  // them into the Lagrange nodal basis and later there will a transformation
  // back to the Legendre polynomial modal basis.  Seems inefficient
  // but is easier to implement and seems to work fine.
  dVector In(qa*qb); In=0;
  U->backward_transform(fh, In);
  for (Ordinal i=0; i<qa*qb; ++i) in[i] += In[i];
}

}  // anonymous namespace

/// Adds the surface contribution for a DG method
void Quad::lift(const Element *const F, dVector &in, const char dir) const {
#ifdef DGM_TIME_QUAD
  static FunctionTimer T("Quad::lift");
  FunctionSentry sentry(T);
#endif
  //  cout << "Quad::lift for Eid = " << id << endl;

  // F->edges holds the numerical flux at the Gauss pts
  // U->edges holds the interior flux at the Gauss pts

  // option 1: interpolate to the Gauss-Lobatto pts and add to the interior
  // h.  In this way, you can do the surface integral against the regular
  // basis as long as you have properly scaled the weighting factors to
  // make sure that the integrals are correct!

  // option 2: Actually perform the surface integrals and then add the
  // result to the modal coefficients.  This is the way that I did it in
  // 1-d.  However, this requires that I have the basis functions on the
  // edges.  The advantage of option 1 is that you do NOT have to even
  // store the edge basis!  However, if you do have the edge basis, then
  // perhaps this approach is a little clearer.

  // Let's try option 1 first, since I currently do not have the edge basis in
  // 2-d

  // option 1

  // do subsides
  const Element *const U = this;
  const bool no_subsides[4] = {side[0]->subsides().empty(),
                               side[1]->subsides().empty(),
                               side[2]->subsides().empty(),
                               side[3]->subsides().empty()};
  const Ordinal qedge[4] = {U->edge[0].qtot(),
                            U->edge[1].qtot(),
                            U->edge[2].qtot(),
                            U->edge[3].qtot()};
  for (Ordinal i=0; i<4; ++i) {
    if (no_subsides[i])
      local_lift(in,F,i,qa,qedge[i],dir);
    else
      subside_lift(in,U,F,psi,i,qa,qedge[i],dir);
  }
}

namespace {

  /// Setup derivative matrix database
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

}  // anonymous namespace

/// Collocation derivative matrix
void Quad::get_derivative_matrix() {
  // cout<<"Quad::get_derivative_matrix()"<<endl;
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
  // cout<<"Finished Quad::get_derivative_matrix()"<<endl;
}

/// Compute the gradient of the supplied vector
/** This routine computes the gradient in physical space using the chain rule
    \f[ \frac{\partial f}{\partial x} =
        \frac{\partial f}{\partial r} \frac{\partial r}{\partial x} +
        \frac{\partial f}{\partial s} \frac{\partial s}{\partial x} \f]
    \f[ \frac{\partial f}{\partial y} =
        \frac{\partial f}{\partial r} \frac{\partial r}{\partial y} +
        \frac{\partial f}{\partial s} \frac{\partial s}{\partial y} \f]
*/
void Quad::gradient( const dVector &f, dVector &fx, dVector &fy ) const {
#ifdef DGM_TIME_QUAD
  static FunctionTimer T("Quad::gradient(dVector&,dVector&,dVector&)");
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

/// Compute the dot product of \f$(\vec f \cdot \nabla)\f$
void Quad::fdotgrad( const dVector &fx, const dVector &fy,
                     dVector &fdg ) const {
  DGM_UNDEFINED;
}

/// This method computes the gradient in only one direction
void Quad::gradient( const dVector &f, dVector &df, char dir) const {
#ifdef DGM_TIME_QUAD
  static FunctionTimer T("Quad::gradient(dVector&,dVector&,char)");
  FunctionSentry sentry(T);
#endif
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
void Quad::local_gradient( const dVector &f, dVector &fr, dVector &fs ) const {
  dMatrix F(f,qa,qb);       // matrix alias of vector
  dMatrix Fr(fr,qa,qb);     // matrix alias of vector
  dMatrix Fs(fs,qa,qb);     // matrix alias of vector
  matmult( D->Da, F, Fr );  // df/da
  matmult( F, D->Dbt, Fs ); // df/db
}

/// Interpolate the element data to a locally uniform mesh (not implemented)
void Quad::interpolate_to_uniform() {
  cout << "Quad::interpolate_to_uniform() is not implemented" << endl;
}

/// Output a tecplot representation for this element
void Quad::tecplot(FILE *fp) {
  int tnsf = 0;
  if (state == Transform) {
    tnsf = 1;
    backward_transform();
  }
  dVector ux(qa*qb);
  dVector uy(qa*qb);
  gradient( u, ux, uy );
  fprintf(fp,"ZONE T=\"Zone%lld\", I=%lld, J=%lld,  F=POINT\n",
          (long long)gid(),(long long)qa,(long long)qb);
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
void Quad::binaryOutput(FILE *fp, const OutputType flag) const {
  if (state == Transform)
    throw DGM::exception("Quad::output called when in transform space");
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
    error("Illegal output type requested in Quad::binaryOutput");
  }
}

/// Output requested element information to a file
streamoff Quad::binaryLength(const OutputType flag) const {
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
    error("Illegal output type requested in Quad::binaryLength");
  }
  error("Fell through case statement in Quad::binaryLength");
  return 0;
}

/// Dump requested element information to a file
void Quad::output(FILE *fp, const char flag) const {
  if (state == Transform)
    throw DGM::exception("Quad::output called when in transform space");
  size_t c = 0;
  switch(flag) {
  case 'h':   // Tecplot header
    fprintf(fp,"\nZONE T=\"Element %lld\", I=%lld, J=%lld, F=BLOCK",
            (long long)gid(),(long long)qa,(long long)qb);
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
        fprintf(fp,"\n%lld %lld %lld %lld",(long long)qij,(long long)qipj,
                (long long)qipjp,(long long)qijp);
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
    for (Ordinal j=0, off=4; j<qb-1; j++)
      for (Ordinal i=0; i<qa-1; i++) {
        if (c++%5==0) fprintf(fp,"\n");
        fprintf(fp,"%lld ",(long long)off);
        off+=4;
      }
    break;
  case 'f':  // Tecplot footer
    break;
  default:
    error("Illegal flag in Quad::output");
  }
}

//============================================================================
//                        Norm and Error routines
//============================================================================

/// Returns the infinity norm over the element
Scalar Quad::norm_Linf() const {
  return norm_inf(u);
}

/// Computes the L2 norm (squared) and element measure
void Quad::norm_L2(Scalar *L2, Scalar *area) const {
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
Scalar Quad::norm_L2() const {
  Scalar L2, area;
  norm_L2( &L2, &area );
  return sqrt(L2/area);
}

/// Computes the H1 norm squared on the Element
void Quad::norm_H1(Scalar *H1, Scalar *area) const {
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
Scalar Quad::norm_H1() const {
  Scalar H1, area;
  norm_H1( &H1, &area );
  return sqrt(H1/area);
}

/// Integrates the data stored in the Element and optionally the volume
Scalar Quad::integrate( Scalar *area ) const {
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
Scalar Quad::integrate(const dVector &v, Scalar *area) const {
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
  if (area!=NULL) *area = sum( b );        // element area
  return dot( b, v );                      // integrate
}

void Quad::get_weight_props(Topology::ElementType& e, bool& c,
                            Ordinal& porder) const {
  e = Topology::Quad;
  c = true;                    // assume affine by default
  if (curve.get()) c = false;  // non-affine element
  porder = pOrder();
}

/// Determine cost (weight) for this element
/** This is a first stop towards having a self tuning, load balancing code
    The data here represents measurements from the MEMS Pentium IV Cluster
    for a simple Navier_Stokes problem.  The first index is polynomial
    order, the second is a flag for curved elements.

    \note That there shouldn't be any physics at this level so this must be
    refactored.

    Ideas for improvement:
    1) Have a more flexible database that also tracks the platform
    2) Include a curve-fit to the data -- it looks quadratic so that
       extrapolation to higher orders can be reasonably done.
    3) Adjustments may be required for different problem types.
*/
int Quad::get_weight() const {
#ifdef QUAD_NS_WEIGHTS
  static Ordinal Pmax = 11;
  static int Weight[Pmax][2] = {{100, 100},
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
#elif QUAD_OTHER_REDSKY_WEIGHTS
  // Weights for RedSky.
  static Ordinal Pmax = 11;
  static int Weight[Pmax][2] = { {100,  106},
                                 {122,  130},
                                 {134,  160},
                                 {163,  196},
                                 {197,  317},
                                 {259,  343},
                                 {268,  662},
                                 {329,  712},
                                 {399,  1024},
                                 {475,  1385},
                                 {551,  1961} };
#else
  // Weights for Cray (note curved numbers are wrong!!!!)
  static Ordinal Pmax = 21;
  static int Weight[22][2]     = { {100,  105},
                                   {112,  126},
                                   {123,  149},
                                   {142,  184},
                                   {156,  233},
                                   {185,  316},
                                   {197,  431},
                                   {229,  545},
                                   {260,  703},
                                   {314,  893},
                                   {332,  893},
                                   {379,  893},
                                   {441,  893},
                                   {519,  893},
                                   {563,  893},
                                   {596,  893},
                                   {690,  893},
                                   {777,  893},
                                   {823,  893},
                                   {885,  893},
                                   {1016, 893},
                                   {1140, 1148} };
#endif
  int cflag = 0;
  if (curve.get()) cflag = 1;
  if (pOrder() > Pmax) {
    if (first_warn) {
      first_warn=false;
      cout << "WARNING - Quad::get_weight(): "
           << "pOrder (="<<pOrder()<<") > Pmax (="<<Pmax<<")"<< endl;
    }
    return Weight[Pmax][cflag];
  } else
    return Weight[pOrder()][cflag];
}

/// Computes the element measure (area for a Quad)
Scalar Quad::compute_measure() const {
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
  return sum( b );   // integrate
}

/// Computes the L2 inner product of two elements
Scalar Quad::L2_inner_product(const Element *el, Scalar *area) const {
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

  dvmul( el->u, u, f );       // f = u*el->u
  if (area) *area = sum( b ); // element measure
  return dot( b, f );         // integrate
}

/// Computes the L2 inner product over the element of two data vectors
Scalar Quad::L2_inner_product(const dVector &vh, const dVector &wh,
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
    dvmul( wb, row );
  }
#endif
  dVector f(n2_wk,qtot);
  dvmul( vh, wh, f );   // f = vh*wh
  if (area) *area = sum( b );
  return dot( b, f );   // integrate
}

/// Compute the side derivatives (need to check this)
void Quad::get_side_Ds(const int sid, const dVector &dv, dVector &dv_s) const {
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
  im = get_interpolation_matrix(qside, (Ordinal)dv.size(), Interp::G2GL);
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
    error("Quad::Ds -- unknown side");
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
void Quad::get_side_curvature( const int sid, dVector &dcurv) const {
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
      throw DGM::exception("Quad::get_side_curvature -- singular "
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
void Quad::get_D1( const int sid, dMatrix &dm1) const {
  DGM_UNDEFINED;
//  dVector wk, tmp1,tmp2;
//  dMatrix *im;
//
//  assert( qa==qb );
//  assert( (dMatrix::size_type)edge[sid].qtot() == dm1.rows() );
//  assert( (dMatrix::size_type)edge[sid].qtot() == dm1.cols());
//
//  dMatrix wk1(n2_wk,qa,dm1.rows());
//  dMatrix wk2(Lwk,dm1.rows(),dm1.rows());
//  dMatrix wk3(g2_wk,dm1.rows(),dm1.rows());
//
//  switch(sid) {
//  case 0:
//  case 2:
//    wk.alias(g1_wk,0,qa);
//    tmp1.alias(g1_wk,qa,qa);   // ERROR: uses too much memory
//    tmp2.alias(g1_wk,2*qa,qa); // ERROR: uses too much memory
//
//    tmp1 = side[sid]->ny();
//    get_side(geom->rx,sid,wk);
//    dvmul(wk,tmp1); // ny*r_x
//
//    tmp2 = side[sid]->nx();
//    get_side(geom->ry,sid,wk);
//    dvmul(wk,tmp2); // nx*r_y
//
//    daxpy(-1.0,tmp1,tmp2); // -ny*r_x + nx*r_y
//
//    //Interpolation matrix from Gauss-Lobatto to interior
//    im = get_interpolation_matrix(qa, side[sid]->qtot(), Interp::G2GL);
//    matmult(D->Da,*im,wk1);
//
//    //Interpolation matrix from interior to Gauss-Lobatto
//    im = get_interpolation_matrix( side[sid]->qtot(), qa, Interp::GL2G);
//    matmult(*im,wk1,wk2);
//
//    dm1 = 0.0;
//    for(dMatrix::size_type i=0; i<dm1.rows(); ++i) dm1[i][i] = tmp2[i];
//    matmult(dm1,wk2,wk3);
//
//    matmult('T',wk3,wk3,dm1); // Ds^T Ds
//    break;
//  case 1:
//  case 3:
//    wk.alias(g1_wk,0,qa);
//    tmp1.alias(g1_wk,qa,qa);    // ERROR:  too much memory
//    tmp2.alias(g1_wk,2*qa,qa);  // ERROR:  too much memory
//
//    tmp1 = side[sid]->ny();
//    get_side(geom->sx,sid,wk);
//    dvmul(wk,tmp1); // ny*s_x
//
//    tmp2 = side[sid]->nx();
//    get_side(geom->sy,sid,wk);
//    dvmul(wk,tmp2); // nx*s_y
//
//    daxpy(-1.0,tmp1,tmp2); //-ny*s_x + nx*s_y
//
//    //Interpolation matrix from Gauss-Lobatto to interior
//    im = get_interpolation_matrix(qa, side[sid]->qtot(), Interp::G2GL);
//    matmult(D->Db,*im,wk1);
//
//    //Interpolation matrix from interior to Gauss-Lobatto
//    im = get_interpolation_matrix( side[sid]->qtot(), qa, Interp::GL2G);
//    matmult(*im,wk1,wk2);
//
//    dm1=0.0;
//    for(dMatrix::size_type i=0; i<dm1.rows(); ++i) dm1[i][i] = tmp2[i];
//    matmult(dm1,wk2,wk3);
//
//    matmult('T',wk3,wk3,dm1); // Ds^T Ds
//    break;
//  default:
//    error("Quad::get_D1 -- unknown side");
//  }
//  return;
}

//=============================================================================

#if 0

// Warning:
// 1) Memory must be allocated for dMatrix dm before calling it
// 2) dm1 is defined for the inside Gauss quadruture points,
//    for the Gauss-Lobatto, or Gauss-Rato, we still need introduce the
//    interpolation Matrix for the side
// 3) We assume that mesh is orthogonal

// g_s
void Quad::get_D1( const int sid, dMatrix &dm1) const {

  dVector wk;
  dVector tmp1,tmp2;

  dMatrix *im;
  dMatrix wk1(Lwk,qa,qa);
  dMatrix wk2(Lwk,qb,qb);

  switch(sid) {
  case 0:
  case 2:
    dm1.resize(qa,qa);
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

#if 0
    //Interpolation matrix from Gauss-Lobatto to interior
    im = get_interpolation_matrix(qa, side[sid]->qtot, Interp::G2GL);
    matmult(dm1,*im,wk1);
    //Interpolation matrix from interior to Gauss-Lobatto
    im = get_interpolation_matrix( side[sid]->qtot, qa, Interp::GL2G);
    matmult(*im,wk1,dm1);
#endif

    break;
  case 1:
  case 3:
    dm1.resize(qb,qb);
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
#if 0
    //Interpolation matrix from Gauss-Lobatto to interior
    im = get_interpolation_matrix(qb, side[sid]->qtot, Interp::G2GL);
    matmult(dm1,*im,wk2);
    //Interpolation matrix from interior to Gauss-Lobatto
    im = get_interpolation_matrix( side[sid]->qtot, qb, Interp::GL2G);
    matmult(*im,wk2,dm1);
#endif
    break;

  default:
    cerr << "Quad::get_D1 -- unknown side" << endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  return ;
}

/// One-dimensional second derivative matrix on
void Quad::get_D2( const int sid, dMatrix &dm2) const {

  dVector* dcurv = get_side_curvature(sid);

  switch(sid) {
  case 0,2:

    dVector tmp1(qa),tmp2(qa),r2x(qa),r2y(qa),rxy(qa),rx(qa),ry(qa);

    dm2.resize(qa,qa);

    matmult(D->Da,D->Da,dm2);

    get_side(geom->rx,sid,rx); //rx
    get_side(geom->ry,sid,ry); //ry

    mvmult(D->Da,rx,tmp1); //rx_r
    dvmul(rx,tmp1,r2x);    //rx_r*rx
    mvmult(D->Db,rx,tmp2); //rx_s
    get_side(geom->sx,0,tmp1); //sx
    dvmul(tmp1,tmp2);        //sx*rx_s
    dvadd(tmp2,r2x);     //r2x = rx_r*rx + rx_s*sx

    mvmult(D->Da,rx,tmp1); //rx_r
    dvmul(ry,tmp1,rxy);    //rx_r*ry
    mvmult(D->Db,ry,tmp2); //rx_s
    get_side(geom->sy,0,tmp1); //sy
    dvmul(tmp1,tmp2);        //sy*rx_s
    dvadd(tmp2,rxy);      //rxy = rx_r*ry + rx_s*sy

    mvmult(D->Da,ry,tmp1); //ry_r
    dvmul(ry,tmp1,r2y);    //ry_r*ry
    mvmult(D->Db,ry,tmp2); //ry_s
    get_side(geom->sy,0,tmp1); //sy
    dvmul(tmp1,tmp2);        //sy*ry_s
    dvadd(tmp2,r2y);      //r2y = ry_r*ry + ry_s*sy

    dvmul(side[sid]->nx(),r2x);
    dvmul(side[sid]->nx(),r2x);

    dvmul(side[sid]->nx(),rxy);
    dvmul(side[sid]->ny(),rxy);
    scale(-2.0,rxy);

    dvmul(side[sid]->ny(),r2y);
    dvmul(side[sid]->ny(),r2y);

    dvmul(side[sid]->nx(),rx,tmp1);
    dvmul(side[sid]->ny(),ry,tmp2);
    dvadd(tmp1,tmp2);
    dvmul(dcurv,tmp2);

    daxpy(1.0,r2x,rxy,tmp2);
    daxpy(1.0,r2y,tmp2,tmp1);  //t1


    dvmul(side[sid]->ny(),rx); // ny*r_x
    dvmul(side[sid]->nx(),ry); // nx*r_y
    daxpy(-1.0,rx,ry,tmp2);  //t0

    for(Ordinal i=0;i<qa;i++)
      for(Ordinal j=0;j<qa;j++)
        dm2[i][j] = dm2[i][j]*tmp2[j]*tmp2[j] + D->Da[i][j]*tmp1[j];

    break;
  case 1,3:

    dVector tmp1(qb),tmp2(qb),s2x(qb),s2y(qb),sxy(qb),sx(qb),sy(qb);

    dm2.resize(qb,qb);

    matmult(D->Db,D->Db,dm2);

    get_side(geom->sx,sid,sx); //sx
    get_side(geom->sy,sid,sy); //sy

    mvmult(D->Da,sx,tmp1); //sx_r
    get_side(geom->rx,sid,tmp2); //rx
    dvmul(tmp1,tmp2,s2x);    //sx_r*rx
    mvmult(D->Db,sx,tmp2); //sx_s
    dvmul(sx,tmp2);        //sx*sx_s
    dvadd(tmp2,s2x);     //s2x = sx_r*rx + sx_s*sx

    mvmult(D->Db,sx,tmp1); //sx_s
    dvmul(sy,tmp1,sxy);    //sx_s*sy
    mvmult(D->Da,sx,tmp2); //sx_r
    get_side(geom->ry,sid,tmp1); //ry
    dvmul(tmp1,tmp2);        //ry*sx_r
    dvadd(tmp2,sxy);      //sxy = sx_r*ry + sx_s*sy

    mvmult(D->Db,sy,tmp1); //sy_s
    dvmul(sy,tmp1,s2y);    //sy_s*sy
    mvmult(D->Da,sy,tmp2); //sy_r
    get_side(geom->ry,sid,tmp1); //ry
    dvmul(tmp1,tmp2);            //ry*sy_r
    dvadd(tmp2,s2y);         //s2y = sy_r*ry + sy_s*sy

    dvmul(side[sid]->nx(),s2x);
    dvmul(side[sid]->nx(),s2x);

    dvmul(side[sid]->nx(),sxy);
    dvmul(side[sid]->ny(),sxy);
    scale(-2.0,sxy);

    dvmul(side[sid]->ny(),s2y);
    dvmul(side[sid]->ny(),s2y);

    dvmul(side[sid]->nx(),sx,tmp1);
    dvmul(side[sid]->ny(),sy,tmp2);
    dvadd(tmp1,tmp2);
    dvmul(dcurv,tmp2);

    daxpy(1.0,s2x,sxy,tmp2);
    daxpy(1.0,s2y,tmp2,tmp1);  // t1


    dvmul(side[sid]->ny(),sx); // ny*s_x
    dvmul(side[sid]->nx(),sy); // nx*s_y
    daxpy(-1.0,sx,sy,tmp2);  // t0

    for(Ordinal i=0;i<qa;i++)
      for(Ordinal j=0;j<qa;j++)
        dm2[i][j] = dm2[i][j]*tmp2[j]*tmp2[j] + D->Db[i][j]*tmp1[j];
    break;
  default:
    cerr << "Quad::get_D1 -- unknown side" << endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  return;
}

#endif

//=============================================================================

/// Apply an exponential 1d filter in both directions of tensor product
void Quad::exp_filter(const Scalar eta, const Scalar s) {
  bool needs_transform = false;
  if (state == Physical) {
    forward_transform();
    needs_transform = true;
  }
  Ordinal i, j, n;
  const Scalar alpha = -log(epsM);
  const Ordinal Nc = Ordinal(eta*L());
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

/// Zero all modes but the constant
void Quad::make_constant() {
  // cout << "Quad::make_constant()" <<endl;
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
void Quad::low_modes(const Ordinal np) {
  if (np>=pOrder()) return;
  bool needs_transform = false;
  if (state == Physical) {
    forward_transform();
    needs_transform = true;
  }
  // upper left
  for (Ordinal i=0, n=0; i<np+1; i++) {
    for (Ordinal j=np+1; j<L(); j++) {
      n = j + i*L();
      uh[n] = 0.0;
    }
  }
  // lower right
  for (Ordinal j=0, n=0; j<=np+1; j++) {
    for (Ordinal i=np+1; i<L(); i++) {
      n = j + i*L();
      uh[n] = 0.0;
    }
  }
  // upper right
  for (Ordinal i=np+1, n=0; i<L(); i++) {
    for (Ordinal j=np+1; j<L(); j++) {
      n = j + i*L();
      uh[n] = 0.0;
    }
  }
  if (needs_transform)
    backward_transform();
}

/// Zero the constant mode (only)
void Quad::kill_constant() {
  bool needs_transform = false;
  if (state == Physical) {
    forward_transform();
    needs_transform = true;
  }
  uh[0] = 0.0;
  if (needs_transform) backward_transform();
}

/// Zero all modes greater than p_inc
void Quad::coarse_scales(const int p_inc) {
  //cout << "Quad::coarse_scales(const int p)" <<endl;
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
void Quad::coarse_scales(const int p_inc, dVector &vh) {
  //cout << "Quad::coarse_scales(const int p, dVector &vh)" <<endl;
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
void Quad::fine_scales(const int p_inc) {
  //cout << "Quad::fine_scales(const int p)" <<endl;
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
void Quad::fine_scales(const int p_inc, dVector &vh) {
  //cout << "Quad::fine_scales(const int p, dVector &vh)" <<endl;
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
void Quad::fine_scales_transform(const int p_inc, dVector &vh) const {
  //cout << "Quad::fine_scales_transform(const int p, dVector &vh)" <<endl;
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

/// This version is needed for ElementBlocks
vector<dMatrix*> Quad::get_interpolation_matrices() const {
  //cout << "Quad::get_interpolation_matrices() for eid "<<gid()<< endl;
  const Element *U = this;
  vector<dMatrix*> matrices;
  for (Ordinal i=0; i<4; ++i) {
    const Ordinal q = i%2 ? qb : qa;
    const Ordinal qedg = U->edge[i].qtot();
    //cout << "get_nterpolation_matrix("<<q<<","<<qedg<<","
    //     <<Interp::G2GL<<")"<<endl;
    dMatrix* m = get_interpolation_matrix(q, qedg, Interp::G2GL);
    matrices.push_back(m);
  }
  return matrices;
}

void Quad::fill_basis_shift_matrix(dMatrix &G) const {
  const int nModes = 4;
  const int Nvert = 4;
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
