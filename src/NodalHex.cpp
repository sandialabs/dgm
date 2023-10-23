/** \file NodalHex.cpp
    \brief NodalHex Element implementation

    NodalHex is a eight node hexahedral element that supports both affine and
    curved sided isoparametric mappings from the master element to the
    physical space element.

    \todo Need to complete this element
*/

// System includes
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
using namespace std;

// Boost includes
#include "boost/numeric/conversion/cast.hpp"
using boost::numeric_cast;

// DGM includes
#include "Comm.hpp"
#include "NodalHex.hpp"
#include "Polylib.tpp"
#include "String.hpp"

namespace DGM {

// define static storage

BasisDB NodalHex::bdb;                           // define Basis database
NodalHex::GeometryDB NodalHex::gdb("NodalHex "); // define Geom database
IMDB NodalHex::imdb;                             // Interpolation Matrix db
DerivDB NodalHex::ddb;                           // Derivative Matrix database

Ordinal NodalHex::Qmax = 0;
Ordinal NodalHex::Lmax = 0;
dVector NodalHex::g1_wk;
dVector NodalHex::g2_wk;
dVector NodalHex::g3_wk;

dVector NodalHex::n1_wk;
dVector NodalHex::n2_wk;
dVector NodalHex::n3_wk;
dVector NodalHex::Lwk;
dVector NodalHex::Lwk2;

const int NodalHex::v_num[6][4] = {{0,1,2,3},{0,1,5,4},{1,2,6,5},
                                   {3,2,6,7},{0,3,7,4},{4,5,6,7}};

const int NodalHex::e_num[6][4] = {{0,1,2,3},{0,5,8,4},{1,6,9,5},
                                   {2,6,10,7},{3,7,11,4},{8,9,10,11}};

/// Primary Constructor
/*! \param[in] ID    - Local element id
    \param[in] P     - Polynomial order
    \param[in] X     - Vector of points defining the vertices */
NodalHex::NodalHex(const Ordinal ID, const Ordinal P, const vector<Point> &X)
  : BaseHex(ID,Basis::Ortho) {
  // cout << "NodalHex::NodalHex, eid = " << ID << endl;

#ifndef DGM_NODALHEX_TEST
  throw DGM::exception("NodalHex elements are not yet implemented!");
#endif

  nVerts(8);
  nEdges(12);
  nFaces(6);
  nSides(6);
  pOrder(P);
  L(P+1);
  nModes(L()*L()*L());

  // you might want to use different quadrature order in a, b, and c
  qa = qb = qc = L();
  qtot = qa * qb * qc;

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

  // construct side data-structure
  // The convergence analysis of Cockburn & Shu (JCP 141, p.203 1998) requires
  // that the edge integrals be exact for polynomials of order (2p+1).  Since
  // we use Gauss-Legendre quadrature which is exact for polynomials of order
  // (2q-1) we must use q=p+1.  But, since qa=p+2, we can also set qedg=qa-1.
  face.reserve(nFaces());
  for (Ordinal i=0; i<nFaces(); i++) {
    Face fac(i,this,nModes(),qa,qa,false);  // make qedg1=qedg2 for now
    face.push_back(fac);
    side.push_back(&(face[i]));
  }
}

/// Copy constructor -- This should not allocate new space for P, M, etc.
NodalHex::NodalHex(const NodalHex *E) {
  // cout << "NodalHex copy constructor for Eid = " << E->gid() << endl;

  // allocate storage for solution at quadrature points
  u.resize(E->u.size());

  // allocate modal coefficients
  uh.alias(u,E->uh.size());

  *this = *E;  // only copies pointers -- be careful -- use shared_ptr

  // Note that stl:vectors drop their content and are replaced by new copies

  // allocate storage for faces
  for (Ordinal i=0; i<nFaces(); i++) {
    // cout << "Face = " << i << ", qtot = " <<  face[i].qtot() << endl;
#ifndef DGM_CONTIGUOUS
    face[i].u.resize(face[i].qtot());
    face[i].u = 0.0;
#endif
    side[i] = &(face[i]);
  }

  // initialize values
  state = Undefined;
  u = 0.0;
}

/// Destructor
NodalHex::~NodalHex() {
  // cout << DGM::Comm::World->MyPID() << " ~NodalHex: eid= " << gid() << endl;
}

// Need to switch to a non-string key like the interpolation matrix
Basis* NodalHex::get_basis(const int der=0) const {
  // cout << "NodalHex::get_basis" << endl;
  Basis* b;
  char buf[128];
  sprintf(buf,"%lld_%lld_%lld_%lld_%lld_%lld",
      (long long)type,(long long)L(),(long long)der,
      (long long)qa,(long long)qb,(long long)qc);  // this still can be slow
  string key = buf;
  BasisDB::iterator p = bdb.bases.find(key);
  if ( p == bdb.bases.end() ) {             // not found, make a new one
    b = new Basis(L(),qa,qb,qc,nModes());
    make_basis(b,type,der);
    bdb.bases[key] = b;
  } else {                                  // found, return the basis
    b = p->second;
  }
  return b;
}

/// Gets the mass matrix for this NodalHex
void NodalHex::get_mass_matrix() {
  // cout << "NodalHex::get_mass_matrix for element " << gid() << endl;
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
      M->mat[i][j] /= geom->J[0];        // only works for constant Jacobian
#ifdef DGM_NODALHEX_SPARSE_LIFT
  // SSC: turned off as it goes out of bounds as currently implemented
  // Also build mass matrix with columns on edges only (Used for sparse lift)
  // TMS: This needs work!
  Mbound.reset( new Minfo );
  Mbound->mat.resize(qa*qb*qc,4*qa+4*qb+4*qc-8);
  Ordinal j=0;
  for (Ordinal i=0; i<qa*qb*qc; i++) {
    if ((i<qa) || (i>qa*(qb-1)) || (i%qa==0) || (i%qa==(qa-1))) {
      for (Ordinal k=0; k<qa*qb*qc; k++) {
        Mbound->mat[k][j] = M->mat[k][i];
      }
      j++;
    }
  }
#endif
}

/// Resets the mass matrixing using a weighted mass matrix
/** WARNING:  might be dangerous to reset the mass matrix to this new value */
void NodalHex::get_mass_matrix(const dVector &x) {
  //cout << "NodalHex::get_mass_matrix(x) for element " << gid() << endl;
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
void NodalHex::solve_mass_matrix(dVector &fh) const {
  if (curve.get() || full_mass) {
    //cout << "NodalHex::solve_mass_matrix(...)" << endl;
#ifdef DGM_CHOLESKY_MASS_MATRIX
    Cholesky_solve(M->mat, fh);
#else
    LU_solve( M->mat, M->pivots, fh);
#endif
  } else {
    for (Ordinal i=0; i<nModes(); i++) fh[i] *= M->mat[0][i];
  }
}

/// Solves (LU factors) the mass matrix (should use Cholesky)
void NodalHex::solve_mass_matrix(dMatrix &fh) {
  if (curve.get() || full_mass) {
    //cout << "NodalHex::solve_mass_matrix(...)" << endl;
#ifdef DGM_CHOLESKY_MASS_MATRIX
    Cholesky_solve(M->mat, fh);
#else
    LU_solve( M->mat, M->pivots, fh);
#endif
  } else {
    for (dMatrix::size_type j=0; j<fh.rows(); ++j) {
      for (Ordinal i=0; i<nModes(); ++i) {
        fh[j][i] *= M->mat[0][i];
      }
    }
  }
}

//=============================================================================

/// Computes a mass matrix but does not factor it
void NodalHex::get_local_mass_matrix(const dVector &factor) {
  //cout << "NodalHex::get_local_mass_matrix(x) for element " << gid() << endl;
  // WARNING:  might be dangerous to reset the mass matrix to this new value
  Mloc.reset( new Minfo );
  Mloc->mat.resize(nModes(),nModes()); // pivots untouched
  dVector f(qtot);
  dVector fh(f,nModes());
  for (Ordinal m=0; m<nModes(); m++) {
    fill( psi->mode[m], f );
    dvmul( factor, f );
    inner_product(f, fh);
    for (Ordinal n=0; n<nModes(); n++) Mloc->mat[m][n] = fh[n];
  }
}

void NodalHex::get_local_derivative_matrix() {
  //  cout << "NodalHex::get_local_derivative_matrix for element "
  //       << gid() << endl;
  Dxloc.reset( new Minfo );
  Dyloc.reset( new Minfo );
  Dzloc.reset( new Minfo );
  Dxtloc.reset( new Minfo );
  Dytloc.reset( new Minfo );
  Dztloc.reset( new Minfo );

  Dxloc->mat.resize(nModes(),nModes());   // pivots untouched
  Dyloc->mat.resize(nModes(),nModes());   // pivots untouched
  Dzloc->mat.resize(nModes(),nModes());   // pivots untouched
  Dxtloc->mat.resize(nModes(),nModes());  // pivots untouched
  Dytloc->mat.resize(nModes(),nModes());  // pivots untouched
  Dztloc->mat.resize(nModes(),nModes());  // pivots untouched

  dVector f(qtot);
  dVector fx(qtot);
  dVector fy(qtot);
  dVector fz(qtot);
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
    gradient(f,fz,'z');
    inner_product(fz, fh);
    for (Ordinal i=0; i<nModes(); i++) {
       Dzloc->mat[i][j] = fh[i];
      Dztloc->mat[j][i] = fh[i];
    }
  }
}

void NodalHex::get_local_derivative_matrix(const dVector &factor) {
  //  cout << "NodalHex::get_local_derivative_matrix for element "
  //       << gid() << endl;
  Dxloc.reset( new Minfo );
  Dyloc.reset( new Minfo );
  Dzloc.reset( new Minfo );
  Dxtloc.reset( new Minfo );
  Dytloc.reset( new Minfo );
  Dztloc.reset( new Minfo );

  Dxloc->mat.resize(nModes(),nModes());   // pivots untouched
  Dyloc->mat.resize(nModes(),nModes());   // pivots untouched
  Dzloc->mat.resize(nModes(),nModes());   // pivots untouched
  Dxtloc->mat.resize(nModes(),nModes());  // pivots untouched
  Dytloc->mat.resize(nModes(),nModes());  // pivots untouched
  Dztloc->mat.resize(nModes(),nModes());  // pivots untouched

  dVector f(qtot);
  dVector fx(qtot);
  dVector fy(qtot);
  dVector fz(qtot);
  dVector fh(nModes());

  for (Ordinal j=0; j<nModes(); j++) {
    fill( psi->mode[j], f );
    gradient(f,fx,'x');
    dvmul(factor,fx); // factor*fx -> fx
    inner_product(fx, fh);
    for (Ordinal i=0; i<nModes(); i++) {
       Dxloc->mat[i][j] = fh[i];
      Dxtloc->mat[j][i] = fh[i];
    }
    gradient(f,fy,'y');
    dvmul(factor,fy); // factor*fy -> fy
    inner_product(fy, fh);
    for (Ordinal i=0; i<nModes(); i++) {
       Dyloc->mat[i][j] = fh[i];
      Dytloc->mat[j][i] = fh[i];
    }
    gradient(f,fz,'z');
    dvmul(factor,fz); // factor*fz -> fz
    inner_product(fz, fh);
    for (Ordinal i=0; i<nModes(); i++) {
       Dzloc->mat[i][j] = fh[i];
      Dztloc->mat[j][i] = fh[i];
    }
  }
}

void NodalHex::get_local_laplace_matrix() {
  // cout << "NodalHex::get_local_laplace_matrix for element " << gid()<<endl;
  DDloc.reset( new Minfo );
  DDloc->mat.resize(nModes(),nModes());
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
  const dVector &wc = psi->wc;
  dVector b(qtot);
  b = geom->J;  // load in the Jacobian
  // apply integration weights
  dMatrix B;
  for(Ordinal i=0; i<qa; i++) {
    B.alias( b, i*qb*qc, qb, qc );
    for(Ordinal k=0; k<qc; k++) {
      dSlice column(B.column(k));
      dvmul( wb, column );
    }
    for(Ordinal j=0; j<qb; j++) {
      dVector row(B.row(j));
      dvmul( wc, row );
    }
  }
  B.alias( b, qa, qb*qc );
  for(Ordinal jk=0; jk<qb*qc; jk++) {
    dSlice column(B.column(jk));
    dvmul( wa, column );
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
    gradient(f1,dpsi_i,'z');
    for (Ordinal j=0; j<nModes(); j++) {
      fill( psi->mode[j],f2);
      gradient(f2,dpsi_j,'z');
      dvmul(dpsi_i,dpsi_j,f2);   // f2 = vh*wh
      DDloc->mat[i][j] += dot(b,f2);
    }
  }
}

void NodalHex::get_local_laplace_matrix(const dVector &factor) {
  // cout << "NodalHex::get_local_laplace_matrix for element " << gid()<<endl;
  DDloc.reset( new Minfo );
  DDloc->mat.resize(nModes(),nModes());
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
  const dVector &wc = psi->wc;
  dVector b(qtot);
  b = geom->J;  // load in the Jacobian
  // apply integration weights
  dMatrix B;
  for(Ordinal i=0; i<qa; i++) {
    B.alias( b, i*qb*qc, qb, qc );
    for(Ordinal k=0; k<qc; k++) {
      dSlice column(B.column(k));
      dvmul( wb, column );
    }
    for(Ordinal j=0; j<qb; j++) {
      dVector row(B.row(j));
      dvmul( wc, row );
    }
  }
  B.alias( b, qa, qb*qc );
  for(Ordinal jk=0; jk<qb*qc; jk++) {
    dSlice column(B.column(jk));
    dvmul( wa, column );
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
    gradient(f1,dpsi_i,'z');
    for (Ordinal j=0; j<nModes(); j++) {
      fill( psi->mode[j],f2);
      gradient(f2,dpsi_j,'z');
      dvmul(dpsi_i,dpsi_j,f2);   // f2 = vh*wh
      dvmul(factor,f2);          // factor*f2 -> f2
      DDloc->mat[i][j] += dot(b,f2);
    }
  }
}

//=============================================================================

/// Fill element with a function string
void NodalHex::fill(string function_string, Operation operation) {
  //  cout << "NodalHex::fill(string function_string)" << endl;
  state = Physical;
  parser_init();
  Parser::VectorFunction f("x", "y", "z", "t", function_string );
  f.evaluate( C->x, C->y, C->z, u, 0.0, convert(operation) );
  state = Physical;
}

/// Fill element with a mode
void NodalHex::fill(Mode &v) {
  // cout << "NodalHex::fill(Mode &)" << endl;
  dArray U(u,qa,qb,qc);
  for (Ordinal i=0; i<qa; i++)
    for (Ordinal j=0; j<qb; j++)
      for (Ordinal k=0; k<qc; k++)
        U[i][j][k] = v.a[i] * v.b[j] * v.c[k];
  state = Physical;
}

/// Fill a vector with a mode
void NodalHex::fill(Mode &v, dVector &f) const {
  //  cout << "NodalHex::fill(Mode &, dVector &) const" << endl;
  dArray F(f,qa,qb,qc);
  for (Ordinal i=0; i<qa; i++)
    for (Ordinal j=0; j<qb; j++)
      for (Ordinal k=0; k<qc; k++)
        F[i][j][k] = v.a[i] * v.b[j] * v.c[k];
}

/// Fill element with a random polynomial
void NodalHex::random() {
  // cout << "NodalHex::random()" << endl;
  state = Physical;
  for (Ordinal i=0; i<nModes(); i++) uh[i] = Element::random(-one,one);
}

/// Set the modes of an element
void NodalHex::set(const dVector &fh, const Ordinal nModes2) {
  // cout << "NodalHex::set(const dVector &, const int)" << endl;
  Ordinal L2 = static_cast<int>(round(pow(static_cast<Scalar>(nModes2),
                                      1.0/3.0)));
  if ( L2*L2*L2 != nModes2 ) {
    cout << "Hex::set L2 = " << L2 << ", L = " << L() << ", nModes2 = "
         << nModes2 << ", nModes = " << nModes() << endl;
    throw DGM::exception("There is a logic error in NodalHex::set(...)");
  }
  Ordinal Lm = min(L(),L2);
  Ordinal n, n2;
  for (Ordinal i=0; i<Lm; i++)
    for (Ordinal j=0; j<Lm; j++)
      for (Ordinal k=0; k<Lm; k++) {
        n  = k + j*L() + i*L()*L();
        n2 = k + j*L2 + i*L2*L2;
        uh[n] = fh[n2];
      }
  state = Transform;
}

/// Compute the inner product with the Basis
void NodalHex::inner_product() {
  inner_product(u, uh);
  state = Transform;
}

/// Computes the inner product of the supplied vector against the Basis
void NodalHex::inner_product(dVector &f, dVector &fh) const {
  //  cout<<"NodalHex::inner_product(dVector &f, dVector &fh) for Eid = "
  //      <<id<<endl;
  const dMatrix &Ba = psi->Ba;
  const dMatrix &Bb = psi->Bb;
  const dMatrix &Bc = psi->Bc;
  dMatrix F;
#ifdef DGM_USE_WJ
  const dVector &wJ = geom->wJ;
  dvmul( wJ, f );
#else
  const dVector &wa = psi->wa;
  const dVector &wb = psi->wb;
  const dVector &wc = psi->wc;
  const dVector &J  = geom->J;

  dvmul( J, f );
  for(Ordinal i=0; i<qa; i++) { // apply integration weights
    F.alias( f, i*qb*qc, qb, qc );
    for(Ordinal k=0; k<qc; k++) {
      dSlice column(F.column(k));
      dvmul( wb, column );
    }
    for(Ordinal j=0; j<qb; j++) {
      dVector row(F.row(j));
      dvmul( wc, row );
    }
  }
  F.alias( f, qa, qb*qc );
  for(Ordinal jk=0; jk<qb*qc; jk++) {
    dSlice column(F.column(jk));
    dvmul( wa, column );
  }
#endif
  dMatrix Fh, H, Ha;
  H.alias( Lwk, L(), qb*qc );
  F.alias( f, qa, qb*qc );
  matmult( Ba, F, H );
  for (Ordinal a=0; a<L(); ++a) {
    H.alias( Lwk, a*qb*qc, qb, qc );
    Ha.alias( Lwk2, a*L()*qc, L(), qc );
    matmult( Bb, H, Ha );
  }
  Fh.alias( fh, L()*L(), L() );
  Ha.alias( Lwk2, L()*L(), qc );
  matmult( Ha, 'T', Bc, Fh );
}

/// Transform the Element to polynomial space
void NodalHex::forward_transform() {
  if (state == Transform) {
    cerr << "NodalHex::transform -- already in transform space"<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  forward_transform(u,uh);
  state = Transform;
}

/// Transform the supplied data to polynomial space
void NodalHex::forward_transform(dVector &f, dVector &fh) const {
  //  cout << "NodalHex::forward_transform(dVector &f, dVector &fh)" << endl;
  inner_product(f,fh);
  solve_mass_matrix(fh);
}

/// Transform using another Elements mass matrix (dangerous)
void NodalHex::forward_transform(Element *F, Element *) {
  //cout << "NodalHex::forward_transform(*F,*)" << endl;
  if (state == Transform) {
    cerr << "NodalHex::transform -- already in transform space"<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  inner_product(u,uh);
  F->solve_mass_matrix(uh);  // Use element F's Mass matrix
  state = Transform;
}

/// Return Element to physical space
void NodalHex::backward_transform() {
  if (state == Physical) {
    cerr << "NodalHex::transform_to_physical -- already in physical space"
         << endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  backward_transform( uh, u );
  state = Physical;
}

/// Transform supplied data to physical space on this Element
void NodalHex::backward_transform(dVector &fh, dVector &f) const {
  //  cout << "NodalHex::backward_transform(dVector &f, dVector &fh)" << endl;
  const dMatrix &Ba = psi->Ba;
  const dMatrix &Bb = psi->Bb;
  const dMatrix &Bc = psi->Bc;
  dMatrix F, Fh, H, Ha;
  H.alias( Lwk, qa, L()*L() );
  Fh.alias( fh, L(), L()*L() );
  matmult( 'T', Ba, Fh, H );
  for (Ordinal i=0; i<qa; ++i) {
    H.alias( Lwk, i*L()*L(), L(), L() );
    Ha.alias( Lwk2, i*qb*L(), qb, L() );
    matmult( 'T', Bb, H, Ha );
  }
  F.alias( f, qa*qb, qc );
  Ha.alias( Lwk2, qa*qb, L());
  matmult( Ha, Bc, F );
}

/// Extracts data onto a specified Side
void NodalHex::get_side( const dVector &from, const Ordinal sid,
                         dVector &to ) const {
  //  cout<<"NodalHex::get_side() Element = "<<id<<" Side = "<<sid<<endl;
  Ordinal i, j, k, p, q;
  switch(sid) {
  case 0:
    k = 0;
    for (i=0; i<qa; i++)
      for (j=0; j<qb; j++) {
        p = j + i*qb;
        q = k + j*qc + i*qb*qc;
        to[p] = from[q];
      }
    break;
  case 1:
    j = 0;
    for (i=0; i<qa; i++)
      for (k=0; k<qc; k++) {
        p = k + i*qc;
        q = k + j*qc + i*qb*qc;
        to[p] = from[q];
      }
    break;
  case 2:
    i = qa-1;
    for (j=0; j<qb; j++)
      for (k=0; k<qc; k++) {
        p = k + j*qc;
        q = k + j*qc + i*qb*qc;
        to[p] = from[q];
      }
    break;
  case 3:
    j = qb-1;
    for (i=0; i<qa; i++)
      for (k=0; k<qc; k++) {
        p = k + i*qc;
        q = k + j*qc + i*qb*qc;
        to[p] = from[q];
      }
    break;
  case 4:
    i = 0;
    for (j=0; j<qb; j++)
      for (k=0; k<qc; k++) {
        p = k + j*qc;
        q = k + j*qc + i*qb*qc;
        to[p] = from[q];
      }
    break;
  case 5:
    k = qc-1;
    for (i=0; i<qa; i++)
      for (j=0; j<qb; j++) {
        p = j + i*qb;
        q = k + j*qc + i*qb*qc;
        to[p] = from[q];
      }
    break;
  default:
    cerr << "NodalHex::get_side -- unknown edge" << endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
}

/// Makes an interpolation matrix
void NodalHex::make_interpolation_matrix(const Ordinal q1,
                                         const Ordinal q2,
                                         const Interp::Type interp,
                                         dMatrix &im ) {
  //  cout << "NodalHex::make_interpolation_matrix" << endl;
  im.resize(q1,q2);
  dVector z1(q1), z2(q2), w1(q1), w2(q2);
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
  default:
    cerr << "NodalHex::make_interpolation_matrix - Invalid interpolation type"
         << endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
}

/// Returns an interpolation matrix (making one if needed)
dMatrix* NodalHex::get_interpolation_matrix(const Ordinal q1,
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

/// Interpolate supplied physical space values to the side Gauss points.
void NodalHex::load_side(const dVector &f, const Ordinal side_id,
                         dVector &f_side) const
{
  //  cout << "NodalHex::load_sides(dVector &f)" << endl;
  dVector wkab, wkac, wkbc, tmp, wk[6];
  wkab.alias(g1_wk,qa*qb);
  wkac.alias(g2_wk,qa*qc);
  wkbc.alias(g3_wk,qb*qc);
  wk[0].alias(wkab); wk[1].alias(wkac); wk[2].alias(wkbc);
  wk[3].alias(wkac); wk[4].alias(wkbc); wk[5].alias(wkab);

  // check that the number of quadrature points on this side match
  assert( (dVector::size_type)side[side_id]->qtot() == f_side.size() );

  tmp.alias(Lwk,side[side_id]->qtot());
  get_side(f, side_id, wk[side_id]);
  interpolate_to_side(side_id, wk[side_id], f_side );
}

/// Interpolate supplied physical space values to the Side Gauss points.
void NodalHex::fill_sides(const dVector &f) {
  //  cout << "NodalHex::fill_sides(dVector &f)" << endl;
  dVector wkab, wkac, wkbc, tmp, wk[6];
  wkab.alias(g1_wk,qa*qb);
  wkac.alias(g2_wk,qa*qc);
  wkbc.alias(g3_wk,qb*qc);
  wk[0].alias(wkab); wk[1].alias(wkac); wk[2].alias(wkbc);
  wk[3].alias(wkac); wk[4].alias(wkbc); wk[5].alias(wkab);
  for (Ordinal i=0; i<nSides(); i++) {
    tmp.alias(Lwk,side[i]->qtot());
    get_side(f, i, wk[i]);
    interpolate_to_side(i, wk[i], side[i]->u );
  }
}

/// Fill Element Sides with a flux vector (3-d flux version)
void NodalHex::fill_sides(const dVector &fx, const dVector &fy,
                          const dVector &fz) {
  //  cout << "NodalHex::fill_sides(const dVector &fx, const dVector &fy, "
  //       << "const dVector &fz)" << endl;
  dVector wkab, wkac, wkbc, tmp, wk[6];
  wkab.alias(g1_wk,qa*qb);
  wkac.alias(g2_wk,qa*qc);
  wkbc.alias(g3_wk,qb*qc);
  wk[0].alias(wkab); wk[1].alias(wkac); wk[2].alias(wkbc);
  wk[3].alias(wkac); wk[4].alias(wkbc); wk[5].alias(wkab);
  for (Ordinal i=0; i<nSides(); i++) {
    tmp.alias(Lwk,side[i]->qtot());
    get_side(fx, i, wk[i]);
    interpolate_to_side(i, wk[i], side[i]->u );
    dvmul( side[i]->nx(), side[i]->u );
    get_side(fy, i, wk[i]);
    interpolate_to_side(i, wk[i], tmp );
    dvvtvp( side[i]->ny(), tmp, side[i]->u, side[i]->u );
    get_side(fz, i, wk[i]);
    interpolate_to_side(i, wk[i], tmp );
    dvvtvp( side[i]->nz(), tmp, side[i]->u, side[i]->u );
  }
}

/// Compute coordinates of quadrature points
void NodalHex::get_coordinates() {
  //  cout << "NodalHex::get_coordinates for element " << gid() << endl;
  if (curve.get())
    get_curved_coordinates();
  else
    get_straight_coordinates();
}

/// Compute coordinates for a straight-sided Element
void NodalHex::get_straight_coordinates() {
  //  cout << "NodalHex::get_straight_coordinates for element " << gid()<<endl;
  C.reset( new Coord(qtot) ); *C = 0;
#ifdef DGM_NODALHEX_USE_MATRIX_STORAGE
  vector< dMatrix > phi(qc);
  cout << "contructed phi" << endl;
  for (Ordinal k=0; k<qc; k++) {
    cout << k << endl;
    phi[k].resize(qa,qb);
  }
#else
  Scalar ***phi = new Scalar**[qa];
  for (Ordinal i=0; i<qa; i++) {
    phi[i] = new Scalar*[qb];
    for (Ordinal j=0; j<qb; j++)
      phi[i][j] = new Scalar[qc];
  }
#endif
  for (Ordinal n = 0; n<nVerts(); n++) {
    for (Ordinal i=0; i<qa; i++) {        // fill basis matrix
      for (Ordinal j=0; j<qb; j++) {
        for (Ordinal k=0; k<qc; k++) {
          // cout << i << " " << j << " " << k << endl;
          phi[i][j][k] = psi->vertMode(n).a[i] * psi->vertMode(n).b[j] *
                         psi->vertMode(n).c[k];
        }
      }
    }
    for (Ordinal i=0; i<qa; i++) {
      for (Ordinal j=0; j<qb; j++) {
        for (Ordinal k=0; k<qc; k++) {
          Ordinal q = k + j * qc + i*qc*qb;
          C->x[q] += vert[n]->x * phi[i][j][k];
          C->y[q] += vert[n]->y * phi[i][j][k];
          C->z[q] += vert[n]->z * phi[i][j][k];
        }
      }
    }
  }
#ifndef DGM_NODALHEX_USE_MATRIX_STORAGE
  // make sure to delete tmp storage
  for (Ordinal i=0; i<qa; i++) {
    for (Ordinal j=0; j<qb; j++)
      delete[] phi[i][j];
    delete[] phi[i];
  }
  delete[] phi;
#endif
}

/// Compute the geometric factors
void NodalHex::compute_geometry() {
  // cout << "NodalHex::compute_geometry for element " << gid() << endl;
  geom.reset( new Geometry( lid(), 3, nVerts(), qtot ) );
  if (curve.get())
    compute_curved_geometry();
  else
    compute_straight_geometry();
  measure(compute_measure());   // volume
#ifdef DGM_USE_GEOM_DB
  gdb.add(geom);
#endif
}

/// Determine if the element is affine
bool NodalHex::is_affine() const {
  // cout << "NodalHex::is_affine for element " << gid() << endl;

  // compute coordinate gradients in mapped space
  Scalar xr = (vert[1]->x - vert[0]->x);
  Scalar xs = (vert[3]->x - vert[0]->x);
  Scalar xt = (vert[4]->x - vert[0]->x);
  Scalar yr = (vert[1]->y - vert[0]->y);
  Scalar ys = (vert[3]->y - vert[0]->y);
  Scalar yt = (vert[4]->y - vert[0]->y);
  Scalar zr = (vert[1]->z - vert[0]->z);
  Scalar zs = (vert[3]->z - vert[0]->z);
  Scalar zt = (vert[4]->z - vert[0]->z);

  using CMC::approx_equal;

  // check to make sure that the Jacobian is constant
  const Scalar ABS = pow(numeric_limits<Scalar>::epsilon(),pt66);
  const Scalar REL = sqrt(numeric_limits<Scalar>::epsilon());
  bool result = (
      approx_equal(xr,(vert[6]->x - vert[7]->x),REL,ABS) &&
      approx_equal(xs,(vert[6]->x - vert[5]->x),REL,ABS) &&
      approx_equal(xt,(vert[6]->x - vert[2]->x),REL,ABS) &&
      approx_equal(yr,(vert[6]->y - vert[7]->y),REL,ABS) &&
      approx_equal(ys,(vert[6]->y - vert[5]->y),REL,ABS) &&
      approx_equal(yt,(vert[6]->y - vert[2]->y),REL,ABS) &&
      approx_equal(zr,(vert[6]->z - vert[7]->z),REL,ABS) &&
      approx_equal(zs,(vert[6]->z - vert[5]->z),REL,ABS) &&
      approx_equal(zt,(vert[6]->z - vert[2]->z),REL,ABS) &&
      approx_equal(xs,(vert[7]->x - vert[4]->x),REL,ABS) &&
      approx_equal(xt,(vert[7]->x - vert[3]->x),REL,ABS) &&
      approx_equal(ys,(vert[7]->y - vert[4]->y),REL,ABS) &&
      approx_equal(yt,(vert[7]->y - vert[3]->y),REL,ABS) &&
      approx_equal(zs,(vert[7]->z - vert[4]->z),REL,ABS) &&
      approx_equal(zt,(vert[7]->z - vert[3]->z),REL,ABS) &&
      approx_equal(xs,(vert[2]->x - vert[1]->x),REL,ABS) &&
      approx_equal(xt,(vert[5]->x - vert[1]->x),REL,ABS) &&
      approx_equal(ys,(vert[2]->y - vert[1]->y),REL,ABS) &&
      approx_equal(yt,(vert[5]->y - vert[1]->y),REL,ABS) &&
      approx_equal(zs,(vert[2]->z - vert[1]->z),REL,ABS) &&
      approx_equal(zt,(vert[5]->z - vert[1]->z),REL,ABS) );
  return result;
}

/// Compute the geometric factors
/** WARNING:  This is only correct for parallelograms */
void NodalHex::compute_straight_geometry() {
  //  cout << "NodalHex::compute_straight_geometry for element "
  //       << gid() << endl;

  // compute coordinate gradients in mapped space
  const Scalar pt5 = 0.5;
  Scalar xr = (vert[1]->x - vert[0]->x)*pt5;
  Scalar xs = (vert[3]->x - vert[0]->x)*pt5;
  Scalar xt = (vert[4]->x - vert[0]->x)*pt5;
  Scalar yr = (vert[1]->y - vert[0]->y)*pt5;
  Scalar ys = (vert[3]->y - vert[0]->y)*pt5;
  Scalar yt = (vert[4]->y - vert[0]->y)*pt5;
  Scalar zr = (vert[1]->z - vert[0]->z)*pt5;
  Scalar zs = (vert[3]->z - vert[0]->z)*pt5;
  Scalar zt = (vert[4]->z - vert[0]->z)*pt5;

#ifdef DGM_CHECK_CONSTANT_JACOBIAN
  // check to make sure that the Jacobian is constant
  const Scalar ABS = pow(numeric_limits<Scalar>::epsilon(),pt66);
  const Scalar REL = sqrt(numeric_limits<Scalar>::epsilon());
  if (!CMC::approx_equal(xr,(vert[6]->x - vert[7]->x)*pt5,REL,ABS) ||
      !CMC::approx_equal(xs,(vert[6]->x - vert[5]->x)*pt5,REL,ABS) ||
      !CMC::approx_equal(xt,(vert[6]->x - vert[2]->x)*pt5,REL,ABS) ||
      !CMC::approx_equal(yr,(vert[6]->y - vert[7]->y)*pt5,REL,ABS) ||
      !CMC::approx_equal(ys,(vert[6]->y - vert[5]->y)*pt5,REL,ABS) ||
      !CMC::approx_equal(yt,(vert[6]->y - vert[2]->y)*pt5,REL,ABS) ||
      !CMC::approx_equal(zr,(vert[6]->z - vert[7]->z)*pt5,REL,ABS) ||
      !CMC::approx_equal(zs,(vert[6]->z - vert[5]->z)*pt5,REL,ABS) ||
      !CMC::approx_equal(zt,(vert[6]->z - vert[2]->z)*pt5,REL,ABS) ||
      !CMC::approx_equal(xs,(vert[7]->x - vert[4]->x)*pt5,REL,ABS) ||
      !CMC::approx_equal(xt,(vert[7]->x - vert[3]->x)*pt5,REL,ABS) ||
      !CMC::approx_equal(ys,(vert[7]->y - vert[4]->y)*pt5,REL,ABS) ||
      !CMC::approx_equal(yt,(vert[7]->y - vert[3]->y)*pt5,REL,ABS) ||
      !CMC::approx_equal(zs,(vert[7]->z - vert[4]->z)*pt5,REL,ABS) ||
      !CMC::approx_equal(zt,(vert[7]->z - vert[3]->z)*pt5,REL,ABS) ||
      !CMC::approx_equal(xs,(vert[2]->x - vert[1]->x)*pt5,REL,ABS) ||
      !CMC::approx_equal(xt,(vert[5]->x - vert[1]->x)*pt5,REL,ABS) ||
      !CMC::approx_equal(ys,(vert[2]->y - vert[1]->y)*pt5,REL,ABS) ||
      !CMC::approx_equal(yt,(vert[5]->y - vert[1]->y)*pt5,REL,ABS) ||
      !CMC::approx_equal(zs,(vert[2]->z - vert[1]->z)*pt5,REL,ABS) ||
      !CMC::approx_equal(zt,(vert[5]->z - vert[1]->z)*pt5,REL,ABS) ) {
    cerr << "ERROR:  NodalHex::compute_straight_geometry()" << endl
         << "  Jacobian is not constant for Element " << gid() << endl;
    cout << "  xr = " << xr << " : " << xr-(vert[6]->x - vert[7]->x)*pt5<<endl;
    cout << "  xs = " << xs << " : " << xs-(vert[6]->x - vert[5]->x)*pt5<<endl;
    cout << "  xt = " << xt << " : " << xt-(vert[6]->x - vert[2]->x)*pt5<<endl;
    cout << "  yr = " << yr << " : " << yr-(vert[6]->y - vert[7]->y)*pt5<<endl;
    cout << "  ys = " << ys << " : " << ys-(vert[6]->y - vert[5]->y)*pt5<<endl;
    cout << "  yt = " << yt << " : " << yt-(vert[6]->y - vert[2]->y)*pt5<<endl;
    cout << "  zr = " << zr << " : " << zr-(vert[6]->z - vert[7]->z)*pt5<<endl;
    cout << "  zs = " << zs << " : " << zs-(vert[6]->z - vert[5]->z)*pt5<<endl;
    cout << "  zt = " << zt << " : " << zt-(vert[6]->z - vert[2]->z)*pt5<<endl;
    cout << "  xr = " << xr << " : " << xr-(vert[6]->x - vert[7]->x)*pt5<<endl;
    cout << "  xs = " << xs << " : " << xs-(vert[7]->x - vert[4]->x)*pt5<<endl;
    cout << "  xt = " << xt << " : " << xt-(vert[7]->x - vert[3]->x)*pt5<<endl;
    cout << "  yr = " << yr << " : " << yr-(vert[6]->y - vert[7]->y)*pt5<<endl;
    cout << "  ys = " << ys << " : " << ys-(vert[7]->y - vert[4]->y)*pt5<<endl;
    cout << "  yt = " << yt << " : " << yt-(vert[7]->y - vert[3]->y)*pt5<<endl;
    cout << "  zr = " << zr << " : " << zr-(vert[6]->z - vert[7]->z)*pt5<<endl;
    cout << "  zs = " << zs << " : " << zs-(vert[7]->z - vert[4]->z)*pt5<<endl;
    cout << "  zt = " << zt << " : " << zt-(vert[7]->z - vert[3]->z)*pt5<<endl;
    cout << "  xr = " << xr << " : " << xr-(vert[1]->x - vert[0]->x)*pt5<<endl;
    cout << "  xs = " << xs << " : " << xs-(vert[2]->x - vert[1]->x)*pt5<<endl;
    cout << "  xt = " << xt << " : " << xt-(vert[5]->x - vert[1]->x)*pt5<<endl;
    cout << "  yr = " << yr << " : " << yr-(vert[1]->y - vert[0]->y)*pt5<<endl;
    cout << "  ys = " << ys << " : " << ys-(vert[2]->y - vert[1]->y)*pt5<<endl;
    cout << "  yt = " << yt << " : " << yt-(vert[5]->y - vert[1]->y)*pt5<<endl;
    cout << "  zr = " << zr << " : " << zr-(vert[1]->z - vert[0]->z)*pt5<<endl;
    cout << "  zs = " << zs << " : " << zs-(vert[2]->z - vert[1]->z)*pt5<<endl;
    cout << "  zt = " << zt << " : " << zt-(vert[5]->z - vert[1]->z)*pt5<<endl;
    cerr << "This means that you have a non-affine element in your mesh "
        "that you are\ntreating as a straight sided parallelogram.  "
        "Revise/correct your mesh for this\nelement or declare this "
        "element as a \"Straight\" element in your root.crv file."<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
#endif

  // compute determinate of the Jacobian
  Scalar detJ = xr*ys*zt + yr*zs*xt + zr*xs*yt -
                xt*ys*zr - zt*xs*yr - xr*zs*yt;
  if(detJ <= 0.0) {
    cerr << "Element " << gid() <<" has a nonpositive Jacobian" << endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  geom->J = detJ;

  geom->rx =  (ys*zt - yt*zs) / detJ;
  geom->ry = -(xs*zt - xt*zs) / detJ;
  geom->rz =  (xs*yt - xt*ys) / detJ;
  geom->sx = -(yr*zt - yt*zr) / detJ;
  geom->sy =  (xr*zt - xt*zr) / detJ;
  geom->sz = -(xr*yt - xt*yr) / detJ;
  geom->tx =  (yr*zs - ys*zr) / detJ;
  geom->ty = -(xr*zs - xs*zr) / detJ;
  geom->tz =  (xr*ys - xs*yr) / detJ;

#ifdef DGM_USE_WJ
  const dVector &wa = psi->wa;
  const dVector &wb = psi->wb;
  const dVector &wc = psi->wc;
  dVector &b =  geom->wJ;
  b = detJ;  // load in the Jacobian
  // apply integration weights

  dMatrix B;
  for(Ordinal i=0; i<qa; i++) {
    B.alias( b, i*qb*qc, qb, qc );
    for(Ordinal k=0; k<qc; k++) {
      dSlice column(B.column(k));
      dvmul( wb, column );
    }
    for(Ordinal j=0; j<qb; j++) {
      dVector row(B.row(j));
      dvmul( wc, row );
    }
  }
  B.alias( b, qa, qb*qc );
  for(Ordinal jk=0; jk<qb*qc; jk++) {
    dSlice column(B.column(jk));
    dvmul( wa, column );
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

/// Compute the stability metrics for time-step size calculations.
Element::StabMetrics NodalHex::compute_metrics() {
  return compute_metrics_3d_tensor_prod();
}

void NodalHex::side_to_size(Ordinal &q1, Ordinal &q2,
                            const Ordinal side) const {
  switch(side) {
  case 0: case 5:
    q1 = qa; q2 = qb; break;
  case 1: case 3:
    q1 = qa; q2 = qc; break;
  case 2: case 4:
    q1 = qb; q2 = qc; break;
  default:            break;
  }
}

/// Returns the side quadrature orders
void NodalHex::side2size(const Ordinal side, iVector &q) const {
  q.resize(2);
  switch(side) {
  case 0: case 5:
    q[0] = qa; q[1] = qb; break;
  case 1: case 3:
    q[0] = qa; q[1] = qc; break;
  case 2: case 4:
    q[0] = qb; q[1] = qc; break;
  default:                break;
  }
}

/// Returns the total number of quadrature points on a side
Ordinal NodalHex::side2size(const Ordinal side) const {
  Ordinal q;
  if (side == 0 || side == 5)
    q = qa*qb;
  else if (side == 1 || side == 3)
    q = qa*qc;
  else
    q = qb*qc;
  return q;
}

/// Interpolate data from interior to side quadrature
void NodalHex::interpolate_to_side( const Ordinal sid, const dVector &from,
                                    dVector &to) const {
  //  cout << "NodalHex::interpolate_to_side(), sid = " << sid << endl;
  Ordinal q1=0, q2=0;

  // to
  Ordinal q1g = face[sid].q1();
  Ordinal q2g = face[sid].q2();

  // from
  side_to_size(q1, q2, sid);

  dMatrix *im1, *im2;
  im1 = get_interpolation_matrix( q1g, q1, Interp::GL2G);  // to, from
  im2 = get_interpolation_matrix( q2g, q2, Interp::GL2G);  // to, from

  dMatrix From, To, wk;
  wk.exclusive_alias(n1_wk,q1g,q2);
  From.alias( const_cast<dVector&>(from), q1, q2 );
  To.alias( to, q1g, q2g );

  matmult( *im1, From, wk );
  matmult( wk, 'T', *im2, To );
}

/// Interpolate from side to interior quadrature
void NodalHex::interpolate_from_side( const Ordinal sid, const dVector &from,
                                      dVector &to) const {
  //  cout << "NodalHex::interpolate_from_side(), sid = " << sid << endl;
  Ordinal q1=0, q2=0;

  // from
  Ordinal q1g = face[sid].q1();
  Ordinal q2g = face[sid].q2();

  // to
  side_to_size(q1, q2, sid);

  dMatrix *im1, *im2;
  im1 = get_interpolation_matrix( q1, q1g, Interp::G2GL);  // to, from
  im2 = get_interpolation_matrix( q2, q2g, Interp::G2GL);  // to, from

  dMatrix From, To, wk;
  wk.exclusive_alias(n1_wk,q1,q2g);             // use n1_wk storage here
  From.alias( const_cast<dVector&>(from), q1g, q2g );
  To.alias( to, q1, q2 );

  matmult( *im1, From, wk );
  matmult( wk, 'T', *im2, To );
}

/// Computes geometric factors for the Element Sides
void NodalHex::compute_side_geometry() {
  //  cout << "NodalHex::compute_side_geometry(), Eid = "<< gid() << endl;
  Ordinal q1=0, q2=0;
  sigma(0.0);

  for (Ordinal i=0; i<nFaces(); i++) {

    side_to_size(q1, q2, i);
    dVector wk;
    wk.exclusive_alias(n2_wk,q1*q2);

    switch(i) {
    case 0:
      get_side(geom->tx,i,wk);                   // wk at Gauss-Lobatto points
      interpolate_to_side( i, wk, side[i]->nx()); // interpolate to Gauss
      scale( -1.0, side[i]->nx());
      get_side(geom->ty,i,wk);
      interpolate_to_side( i, wk, side[i]->ny());
      scale( -1.0, side[i]->ny());
      get_side(geom->tz,i,wk);
      interpolate_to_side( i, wk, side[i]->nz());
      scale( -1.0, side[i]->nz());
      break;
    case 1:
      get_side(geom->sx,i,wk);                   // wk is Gauss-Lobatto points
      interpolate_to_side( i, wk, side[i]->nx()); // interpolate to Gauss
      scale( -1.0, side[i]->nx());
      get_side(geom->sy,i,wk);
      interpolate_to_side( i, wk, side[i]->ny());
      scale( -1.0, side[i]->ny());
      get_side(geom->sz,i,wk);
      interpolate_to_side( i, wk, side[i]->nz());
      scale( -1.0, side[i]->nz());
      break;
    case 2:
      get_side(geom->rx,i,wk);                   // wk is Gauss-Lobatto points
      interpolate_to_side( i, wk, side[i]->nx()); // interpolate to Gauss
      get_side(geom->ry,i,wk);
      interpolate_to_side( i, wk, side[i]->ny());
      get_side(geom->rz,i,wk);
      interpolate_to_side( i, wk, side[i]->nz());
      break;
    case 3:
      get_side(geom->sx,i,wk);                   // wk at Gauss-Lobatto points
      interpolate_to_side( i, wk, side[i]->nx()); // interpolate to Gauss
      get_side(geom->sy,i,wk);
      interpolate_to_side( i, wk, side[i]->ny());
      get_side(geom->sz,i,wk);
      interpolate_to_side( i, wk, side[i]->nz());
      break;
    case 4:
      get_side(geom->rx,i,wk);                   // wk at Gauss-Lobatto points
      interpolate_to_side( i, wk, side[i]->nx()); // interpolate to Gauss
      scale( -1.0, side[i]->nx());
      get_side(geom->ry,i,wk);
      interpolate_to_side( i, wk, side[i]->ny());
      scale( -1.0, side[i]->ny());
      get_side(geom->rz,i,wk);
      interpolate_to_side( i, wk, side[i]->nz());
      scale( -1.0, side[i]->nz());
      break;
    case 5:
      get_side(geom->tx,i,wk);                   // wk at Gauss-Lobatto points
      interpolate_to_side( i, wk, side[i]->nx()); // interpolate to Gauss
      get_side(geom->ty,i,wk);
      interpolate_to_side( i, wk, side[i]->ny());
      get_side(geom->tz,i,wk);
      interpolate_to_side( i, wk, side[i]->nz());
      break;
    }

    dVector interior_J(side[i]->qtot());         // Gauss points
    get_side(geom->J,i,wk);
    interpolate_to_side( i, wk, interior_J );

    // normalize outward pointing normal vectors
    dVector tmp(side[i]->qtot());
    dvmul ( side[i]->nx(), side[i]->nx(), tmp );
    dvvtvp( side[i]->ny(), side[i]->ny(), tmp, tmp );
    dvvtvp( side[i]->nz(), side[i]->nz(), tmp, tmp );
    dvsqrt( tmp, tmp );
    dvdiv ( side[i]->nx(), tmp, side[i]->nx());
    dvdiv ( side[i]->ny(), tmp, side[i]->ny());
    dvdiv ( side[i]->nz(), tmp, side[i]->nz());

    // compute surface Jacobian (Gauss-Lobatto)
    dVector x(q1*q2), xr(q1*q2), xs(q1*q2);
    dVector y(q1*q2), yr(q1*q2), ys(q1*q2);
    dVector z(q1*q2), zr(q1*q2), zs(q1*q2);
    get_side(C->x,i,x);
    get_side(C->y,i,y);
    get_side(C->z,i,z);

    dMatrix X, XR, XS, Y, YR, YS, Z, ZR, ZS;
    X.alias( x, q1, q2 ); XR.alias( xr, q1, q2 ); XS.alias( xs, q1, q2 );
    Y.alias( y, q1, q2 ); YR.alias( yr, q1, q2 ); YS.alias( ys, q1, q2 );
    Z.alias( z, q1, q2 ); ZR.alias( zr, q1, q2 ); ZS.alias( zs, q1, q2 );

    // watch out if qa != qb != qc
    matmult( D->Da, X, XR );
    matmult( X, 'T', D->Db, XS );
    matmult( D->Da, Y, YR );
    matmult( Y, 'T', D->Db, YS );
    matmult( D->Da, Z, ZR );
    matmult( Z, 'T', D->Db, ZS );

    // x = yr*zs - zr*ys
    dvmul (yr,zs,x);
    dvvtvm(zr,ys,x,x);

    // y = zr*xs - xr*zs
    dvmul (zr,xs,y);
    dvvtvm(xr,zs,y,y);

    // z = xr*ys - xs*yr
    dvmul (xr,ys,z);
    dvvtvm(xs,yr,z,z);

    dvmul (x,x,wk);
    dvvtvp(y,y,wk,wk);
    dvvtvp(z,z,wk,wk);
    dvsqrt(wk,wk);

    // interpolate to Gauss points
    interpolate_to_side( i, wk, side[i]->J() );

    // divide the surface Jacobian by the interior Jacobian
    dvdiv( interior_J, side[i]->J() );
    // This is done so that you can use an interior integration to perform the
    // surface integration.  For this to work you must use an interior
    // quadrature rule that includes the boundaries and you must divide the
    // side contributions by the integration weight in the other direction(s).

    // store the max ratio of side to element Jacobians
    side[i]->h_n_inv(0.0);
    for (Ordinal k=0; k<side[i]->J().size(); ++k) {
      const Scalar Jface = fabs(side[i]->J(k));
      sigma(max( sigma(), Jface ));
      side[i]->h_n_inv( max( side[i]->h_n_inv(), pt5*Jface ) );
    }
#if 0
    // compute and store the Face measure for each side
    dVector p(side[i]->qtot); p = one;
    side[i]->measure = compute_side_integral(p,i);
#endif
  }
}

void NodalHex::get_side_coordinates( const Ordinal sid, Point *pside ) const {
  dVector px, py, pz;
  px.resize(face[sid].qtot());
  py.resize(face[sid].qtot());
  pz.resize(face[sid].qtot());

  Ordinal q1=0, q2=0;
  side_to_size(q1, q2, sid);
  dVector wk;
  wk.exclusive_alias(n2_wk,q1*q2);

  switch(sid) {
  case 0: case 1: case 2: case 3: case 4: case 5:
    get_side(C->x,sid,wk);
    interpolate_to_side( sid, wk, px );
    get_side(C->y,sid,wk);
    interpolate_to_side( sid, wk, py );
    get_side(C->z,sid,wk);
    interpolate_to_side( sid, wk, pz );
    for(Ordinal i=0; i<face[sid].qtot(); i++)
      pside[i] = Point(px[i],py[i],pz[i]);
    break;
  default:
    cerr << "NodalHex::_side_coordinates illegal edge id." << endl;
    DGM::Comm::World->exit();
  }
}

// not ok
void NodalHex::forward_transform_side(dVector &f, dVector &fh) {
  cout << "NodalHex::forward_transform_side(), Eid = "<< gid() << endl;
  DGM::Comm::World->exit(DGM::FAILURE);
  dVector &wa=psi->wa;
  fh.resize(L()-2);
  // subtract off vertices
  daxpy(-f[0], psi->vertMode(0).a, f );
  daxpy(-f[qa-1], psi->vertMode(0).a, f);
  // inner product
  dvmul( wa, f );
  for (Ordinal i=0; i<L()-2; i++)
    fh[i] = dot(psi->edgeMode(0,i).a, f );
  if (L()-2) solve_1d_mass_matrix(fh);
}

// not ok
void NodalHex::solve_1d_mass_matrix(dVector &fh) const {
//  cout << "NodalHex::solve_1d_mass_matrix(dVector &fh) const" << endl;
//  DGM::Comm::World->exit(DGM::FAILURE);
  Minfo M1d;
  get_1d_mass_matrix(M1d);
#ifdef DGM_CHOLESKY_MASS_MATRIX
  Cholesky_solve(M1d.mat, fh);
#else
  LU_solve(M1d.mat, M1d.pivots, fh);
#endif
}

// not ok
void NodalHex::get_1d_mass_matrix(Minfo &M1d) const {
//  cout << "NodalHex::get_1d_mass_matrix(Minfo &M1d) const" << endl;
//  DGM::Comm::World->exit(DGM::FAILURE);
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

Scalar NodalHex::compute_side_integral( dVector &f, Ordinal sid ) const {
  // cout << "NodalHex::compute_side_integral(dVector &, int) for Eid = "
  //      << this->gid() << ", Sid = " << sid << endl;
  DGM_UNDEFINED;
  return 0;
}

Scalar NodalHex::compute_side_measure() const {
  Scalar result=0.0;
  for (Ordinal sid=0; sid<nSides(); sid++) {
    Ordinal qsid = side[sid]->qtot();
    dVector p(qsid);
    p = 1.0;
    result += compute_side_integral(p,sid);
  }
  return result;
}

// ok
void NodalHex::lift(const Element *const F, dVector &in, const char dir) const {
  // cout << "NodalHex::lift for Eid = " << gid() << endl;
  const dVector &wa = psi->wa;
  const dVector &wb = psi->wb;
  const dVector &wc = psi->wc;

  int sid;
  dVector f, fi;
  dMatrix In, Fi;

  // Side 0
  sid = 0;
  f.alias(g1_wk, side[sid]->qtot());
  fi.alias(g2_wk, qa*qb );
  if (F)
    dvsub( F->side[sid]->u, side[sid]->u, f );
  else
    f = side[sid]->u;
  dvmul( side[sid]->J(), f);
  if (dir == 'x')
    dvmul( side[sid]->nx(), f );
  else if (dir == 'y')
    dvmul( side[sid]->ny(), f );
  else if (dir == 'z')
    dvmul( side[sid]->nz(), f );
  interpolate_from_side( sid, f, fi );
  In.alias(in,qa*qb,qc);
  daxpy( 1/wc[0], fi, In.column(0) );

  // Side 1
  sid = 1;
  f.alias(g1_wk, side[sid]->qtot());
  fi.alias(g2_wk, qa*qc );
  if (F)
    dvsub( F->side[sid]->u, side[sid]->u, f );
  else
    f = side[sid]->u;
  dvmul( side[sid]->J(), f);
  if (dir == 'x')
    dvmul( side[sid]->nx(), f );
  else if (dir == 'y')
    dvmul( side[sid]->ny(), f );
  else if (dir == 'z')
    dvmul( side[sid]->nz(), f );
  interpolate_from_side( sid, f, fi );
  Fi.alias(fi, qa, qc);
  for (Ordinal i=0; i<qa; i++) {
    In.alias(in, i*qb*qc, qb, qc);
    dVector Fi_row(Fi.row(i));
    dVector In_row(In.row(0));
    daxpy( 1/wb[0], Fi_row, In_row );
  }

  // Side 2
  sid = 2;
  f.alias(g1_wk, side[sid]->qtot());
  fi.alias(g2_wk, qb*qc );
  if (F)
    dvsub( F->side[sid]->u, side[sid]->u, f );
  else
    f = side[sid]->u;
  dvmul( side[sid]->J(), f);
  if (dir == 'x')
    dvmul( side[sid]->nx(), f );
  else if (dir == 'y')
    dvmul( side[sid]->ny(), f );
  else if (dir == 'z')
    dvmul( side[sid]->nz(), f );
  interpolate_from_side( sid, f, fi );
  In.alias(in,qa,qb*qc);
  dVector In_row_qa(In.row(qa-1));
  daxpy( 1/wa[qa-1], fi, In_row_qa );

  // Side 3
  sid = 3;
  f.alias(g1_wk, side[sid]->qtot());
  fi.alias(g2_wk, qa*qc );
  if (F)
    dvsub( F->side[sid]->u, side[sid]->u, f );
  else
    f = side[sid]->u;
  dvmul( side[sid]->J(), f);
  if (dir == 'x')
    dvmul( side[sid]->nx(), f );
  else if (dir == 'y')
    dvmul( side[sid]->ny(), f );
  else if (dir == 'z')
    dvmul( side[sid]->nz(), f );
  interpolate_from_side( sid, f, fi );
  Fi.alias(fi, qa, qc);
  for (Ordinal i=0; i<qa; i++) {
    In.alias(in, i*qb*qc, qb, qc);
    dVector Fi_row(Fi.row(i));
    dVector In_row(In.row(qb-1));
    daxpy( 1/wb[qb-1], Fi_row, In_row );
  }

  // Side 4
  sid = 4;
  f.alias(g1_wk, side[sid]->qtot());
  fi.alias(g2_wk, qb*qc );
  if (F)
    dvsub( F->side[sid]->u, side[sid]->u, f );
  else
    f = side[sid]->u;
  dvmul( side[sid]->J(), f);
  if (dir == 'x')
    dvmul( side[sid]->nx(), f );
  else if (dir == 'y')
    dvmul( side[sid]->ny(), f );
  else if (dir == 'z')
    dvmul( side[sid]->nz(), f );
  interpolate_from_side( sid, f, fi );
  In.alias(in,qa,qb*qc);
  dVector In_row_0(In.row(0));
  daxpy( 1/wa[0], fi, In_row_0 );

  // Side 5
  sid = 5;
  f.alias(g1_wk, side[sid]->qtot());
  fi.alias(g2_wk, qa*qb );
  if (F)
    dvsub( F->side[sid]->u, side[sid]->u, f );
  else
    f = side[sid]->u;
  dvmul( side[sid]->J(), f);
  if (dir == 'x')
    dvmul( side[sid]->nx(), f );
  else if (dir == 'y')
    dvmul( side[sid]->ny(), f );
  else if (dir == 'z')
    dvmul( side[sid]->nz(), f );
  interpolate_from_side( sid, f, fi );
  In.alias(in,qa*qb,qc);
  daxpy( 1/wc[qc-1], fi, In.column(qc-1) );
}

/// build the collocation derivative matrix
void NodalHex::get_derivative_matrix() {
  Dentry key(qa,qb,qc);
  DerivDB::iterator p = ddb.entry.find(key);
  if ( p == ddb.entry.end() ) {
    D.reset(new Dinfo);
    //cout << "NodalHex::make_derivative_matrix()" << endl;
    D->Da.resize(qa,qa);
    D->Dat.resize(qa,qa);
    D->Db.resize(qb,qb);
    D->Dbt.resize(qb,qb);
    D->Dc.resize(qc,qc);
    D->Dct.resize(qc,qc);
    dgll(D->Da,D->Dat,psi->za);
    dgll(D->Db,D->Dbt,psi->zb);
    dgll(D->Dc,D->Dct,psi->zc);
    ddb.entry[key] = D;
  } else {
    D = p->second;
  }
}

/// Compute the gradient in all spatial directions on the Element
/** df/dx = df/dr * dr/dx + df/ds * ds/dx + df/dt * dt/dx
 *  df/dy = df/dr * dr/dy + df/ds * ds/dy + df/dt * dt/dy
 *  df/dz = df/dr * dr/dz + df/ds * ds/dz + df/dt * dt/dz
*/
void NodalHex::gradient( const dVector &f, dVector &fx, dVector &fy,
                         dVector &fz ) const {
  // cout << "NodalHex::gradient( const dVector &, dVector &, dVector &, "
  //      << "dVector & ) const" << endl;
  dVector fr(g1_wk,qtot);  // use gradient workspace
  dVector fs(g2_wk,qtot);  // use gradient workspace
  dVector ft(g3_wk,qtot);  // use gradient workspace
  dMatrix F, Fr, Fs, Ft;

  // Fr[qa][qb*qc] = Da[qa][qa] F[qa][qb*qc]
  F.alias( const_cast<dVector&>(f), qa, qb*qc ); Fr.alias( fr, qa, qb*qc );
  matmult( D->Da, F, Fr );

  // Fs[i][qb][qc] = Db[qb][qb] F[i][qb][qc]
  for (Ordinal i=0; i<qa; i++) {
    F.alias( const_cast<dVector&>(f), i*qb*qc, qb, qc );
    Fs.alias( fs, i*qb*qc, qb, qc);
    matmult( D->Db, F, Fs );
  }

  // Ft[qa*qb][qc] = F[qa(qb][qc] (Dc[qc][qc])^T
  F.alias( const_cast<dVector&>(f), qa*qb, qc ); Ft.alias( ft, qa*qb, qc );
  matmult( F, D->Dct, Ft );

  dvmul ( geom->rx, fr, fx);       // fx  = rx * fr
  dvvtvp( geom->sx, fs, fx, fx );  // fx += sx * fs
  dvvtvp( geom->tx, ft, fx, fx );  // fx += tx * ft

  dvmul ( geom->ry, fr, fy);       // fy  = ry * fr
  dvvtvp( geom->sy, fs, fy, fy );  // fy += sy * fs
  dvvtvp( geom->ty, ft, fy, fy );  // fy += ty * ft

  dvmul ( geom->rz, fr, fz);       // fz  = rz * fr
  dvvtvp( geom->sz, fs, fz, fz );  // fz += sz * fs
  dvvtvp( geom->tz, ft, fz, fz );  // fz += tz * ft
}

/// Compute the gradient in only one spatial direction
void NodalHex::gradient( const dVector &f, dVector &df, char dir) const {
  dVector fr(g1_wk,qtot);  // use gradient workspace
  dVector fs(g2_wk,qtot);  // use gradient workspace
  dVector ft(g3_wk,qtot);  // use gradient workspace
  dMatrix F, Fr, Fs, Ft;

  // Fr[qa][qb*qc] = Da[qa][qa] F[qa][qb*qc]
  F.alias( const_cast<dVector&>(f), qa, qb*qc ); Fr.alias( fr, qa, qb*qc );
  matmult( D->Da, F, Fr );

  // Fs[i][qb][qc] = Db[qb][qb] F[i][qb][qc]
  for (Ordinal i=0; i<qa; i++) {
    F.alias( const_cast<dVector&>(f), i*qb*qc, qb, qc );
    Fs.alias( fs, i*qb*qc, qb, qc);
    matmult( D->Db, F, Fs );
  }

  // Ft[qa*qb][qc] = F[qa(qb][qc] (Dc[qc][qc])^T
  F.alias( const_cast<dVector&>(f), qa*qb, qc ); Ft.alias( ft, qa*qb, qc );
  matmult( F, D->Dct, Ft );

  switch(dir) {
  case 'x':
    dvmul ( geom->rx, fr, df);       // fx  = rx * fr
    dvvtvp( geom->sx, fs, df, df );  // fx += sx * fs
    dvvtvp( geom->tx, ft, df, df );  // fx += tx * ft
    break;
  case 'y':
    dvmul ( geom->ry, fr, df);       // fy  = ry * fr
    dvvtvp( geom->sy, fs, df, df );  // fy += sy * fs
    dvvtvp( geom->ty, ft, df, df );  // fy += ty * ft
    break;
  case 'z':
    dvmul ( geom->rz, fr, df);       // fz  = rz * fr
    dvvtvp( geom->sz, fs, df, df );  // fz += sz * fs
    dvvtvp( geom->tz, ft, df, df );  // fz += tz * ft
    break;
  default:
    cerr << "NodalHex::gradient:  illegal direction " << dir << "." << endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
}

/// Compute the local gradient on the master element
void NodalHex::local_gradient( const dVector &f, dVector &fr, dVector &fs,
                               dVector &ft) const {
  // cout << "NodalHex::local_gradient()" << endl;

  dMatrix F, Fr, Fs, Ft;

  // Fr[qa][qb*qc] = Da[qa][qa] F[qa][qb*qc]
  F.alias( const_cast<dVector&>(f), qa, qb*qc ); Fr.alias( fr, qa, qb*qc );
  matmult( D->Da, F, Fr );

  // Fs[i][qb][qc] = Db[qb][qb] F[i][qb][qc]
  for (Ordinal i=0; i<qa; i++) {
    F.alias( const_cast<dVector&>(f), i*qb*qc, qb, qc );
    Fs.alias( fs, i*qb*qc, qb, qc);
    matmult( D->Db, F, Fs );
  }

  // Ft[qa*qb][qc] = F[qa(qb][qc] (Dc[qc][qc])^T
  F.alias( const_cast<dVector&>(f), qa*qb, qc ); Ft.alias( ft, qa*qb, qc );
  matmult( F, D->Dct, Ft );
}

/// Generate a Tecplot output file (only ASCII supported)
void NodalHex::tecplot(FILE *fp) {
  //  cout << "NodalHex::tecplot for element = " << gid() << endl;
  bool tnsf = false;
  if (state == Transform) {
    tnsf = true;
    backward_transform();
  }
  fprintf(fp,"ZONE T=\"Zone%llu\", ",(unsigned long long)gid());
  fprintf(fp,"I=%llu, J=%llu, K=%llu,  F=POINT\n",(unsigned long long)qa,
          (unsigned long long)qb,(unsigned long long)qc);
  for (Ordinal k=0; k<qc; k++) {
    for (Ordinal j=0; j<qb; j++) {
      for (Ordinal i=0; i<qa; i++) {
        Ordinal q = k + j * qc + i*qc*qb;
        fprintf(fp, "%15.8e %15.8e %15.8e %15.8e\n",
                C->x[q], C->y[q], C->z[q], u[q]);
      }
    }
  }
  if (tnsf) forward_transform();
}

namespace {

  /// Functor to compute the local index given i,j,k
  class Index {
    const Ordinal qa, qb, qc;
  public:
    Index(const Ordinal qa_, const Ordinal qb_, const Ordinal qc_) :
      qa(qa_), qb(qb_), qc(qc_) {}
    Ordinal operator()(Ordinal i, Ordinal j, Ordinal k) const {
      return k+j*qc+i*qc*qb;
    }
    inline Ordinal get_qa() const { return qa; }
    inline Ordinal get_qb() const { return qb; }
    inline Ordinal get_qc() const { return qc; }
  };

}

/// Dump the Element storage to a file
void NodalHex::output(FILE *fp, const char flag) const {
  if (state == Transform)
    error("Hex::output called when in transform space");
  Index Q(qa,qb,qc);
  Ordinal c = 0;
  switch(flag) {
  case 'h':  // header
    fprintf(fp,"\nZONE T=\"Element %lld\", I=%lld, J=%lld, K=%lld, F=BLOCK",
        (long long)gid(), (long long)qa,(long long)qb, (long long)qc);
    break;
  case 'f':  // footer
    break;
  case 'd':  // solution
    for (Ordinal k=0; k<qc; k++)
      for (Ordinal j=0; j<qb; j++)
        for (Ordinal i=0; i<qa; i++) {
          const Ordinal q = k+j*qc+i*qc*qb;
          if (c++%5==0) fprintf(fp,"\n");
          fprintf(fp,"%15.8e ",u[q]);
        }
    break;
  case 'x':  // x-coordinates
    for (Ordinal k=0; k<qc; k++)
      for (Ordinal j=0; j<qb; j++)
        for (Ordinal i=0; i<qa; i++) {
          const Ordinal q = k+j*qc+i*qc*qb;
          if (c++%5==0) fprintf(fp,"\n");
          fprintf(fp,"%15.8e ",C->x[q]);
        }
    break;
  case 'y':  // y-coordinates
    for (Ordinal k=0; k<qc; k++)
      for (Ordinal j=0; j<qb; j++)
        for (Ordinal i=0; i<qa; i++) {
          const Ordinal q = k+j*qc+i*qc*qb;
          if (c++%5==0) fprintf(fp,"\n");
          fprintf(fp,"%15.8e ",C->y[q]);
        }
    break;
  case 'z':  // z-coordinates
    for (Ordinal k=0; k<qc; k++)
      for (Ordinal j=0; j<qb; j++)
        for (Ordinal i=0; i<qa; i++) {
          const Ordinal q = k+j*qc+i*qc*qb;
          if (c++%5==0) fprintf(fp,"\n");
          fprintf(fp,"%15.8e ",C->z[q]);
        }
    break;
  case 'p':  // points
    for (Ordinal k=0; k<qc; k++)
      for (Ordinal j=0; j<qb; j++)
        for (Ordinal i=0; i<qa; i++) {
          const Ordinal q = k+j*qc+i*qc*qb;
          fprintf(fp,"\n%15.8e %15.8e %15.8e ",C->x[q],C->y[q],C->z[q]);
    }
    break;
  case 'c': // connectivity
    for (Ordinal k=0; k<qc-1; k++)
      for (Ordinal i=0; i<qa-1; i++)
        for (Ordinal j=0; j<qa-1; j++) {
          fprintf(fp,"\n%llu %llu %llu %llu\n%llu %llu %llu %llu",
                  (unsigned long long)Q(i,j,k),
                  (unsigned long long)Q(i+1,j,k),
                  (unsigned long long)Q(i+1,j,k+1),
                  (unsigned long long)Q(i,j,k+1),
                  (unsigned long long)Q(i,j+1,k),
                  (unsigned long long)Q(i+1,j+1,k),
                  (unsigned long long)Q(i+1,j+1,k+1),
                  (unsigned long long)Q(i,j+1,k+1));
        }
    break;
  case 't': // paraview element type
    for (Ordinal k=0; k<qc-1; k++)
      for (Ordinal i=0; i<qa-1; i++)
        for (Ordinal j=0; j<qa-1; j++) {
          if (c++%5==0) fprintf(fp,"\n");
          fprintf(fp,"%d ",VTK_HEXAHEDRON);
        }
    break;
  case 'o': // paraview offset
    for (Ordinal k=0, q=8; k<qc-1; k++)
      for (Ordinal i=0; i<qa-1; i++)
        for (Ordinal j=0; j<qb-1; j++) {
          if (c++%5==0) fprintf(fp,"\n");
          fprintf(fp,"%llu ",(unsigned long long)q);
          q+=8;
        }
    break;
  default:
    error("Illegal flag in NodalHex::output(), flag = "+asString(flag));
  }
}

//============================================================================
//                        Norm and Error routines
//============================================================================

/// Compute the infinity norm (maximum of the absolute value)
Scalar NodalHex::norm_Linf() const {
  return norm_inf(u);
}

/// Compute the L2 norm squared
void NodalHex::norm_L2(Scalar *L2, Scalar *volume) const {
  //  cout << "NodalHex::norm_L2" << endl;
#ifdef DGM_USE_WJ
  const dVector &b = geom->wJ;
#else
  const dVector &wa = psi->wa;
  const dVector &wb = psi->wb;
  const dVector &wc = psi->wc;
  dVector b(n1_wk,qtot);

  b = geom->J;  // load in the Jacobian

  // apply integration weights
  dMatrix B;
  for(Ordinal i=0; i<qa; i++) {
    B.alias( b, i*qb*qc, qb, qc );
    for(Ordinal k=0; k<qc; k++) {
      dSlice column(B.column(k));
      dvmul( wb, column );
    }
    for(Ordinal j=0; j<qb; j++) {
      dVector row(B.row(j));
      dvmul( wc, row );
    }
  }
  B.alias( b, qa, qb*qc );
  for(Ordinal jk=0; jk<qb*qc; jk++) {
    dSlice column(B.column(jk));
    dvmul( wa, column );
  }
#endif

  dVector f(n2_wk,qtot);
  dvmul( u, u, f );            // f = u^2

  *L2 = dot( b, f );           // integrate
  *volume = sum( b );          // the volume of this element
}

/// Returns the L2 norm divided by the Element measure
Scalar NodalHex::norm_L2() const {
  Scalar L2, volume;
  norm_L2( &L2, &volume );
  return sqrt(L2/volume);
}

/// Computes the H1 norm squared on the Element
void NodalHex::norm_H1(Scalar *H1, Scalar *volume) const {
  //  cout << "NodalHex::norm_H1" << endl;

  dVector ux(n1_wk,qtot), uy(n2_wk,qtot), uz(n3_wk,qtot);
  gradient( u, ux, uy, uz );   // compute gradient
  dvmul ( ux, ux );            // ux =  ux^2
  dvvtvp( uy, uy, ux, ux );    // ux += uy^2
  dvvtvp( uz, uz, ux, ux );    // ux += uz^2

#ifdef DGM_USE_WJ
  const dVector &b = geom->wJ;
#else
  const dVector &wa = psi->wa;
  const dVector &wb = psi->wb;
  const dVector &wc = psi->wc;
  dVector b(g1_wk,qtot);

  b = geom->J;  // load in the Jacobian

  // apply integration weights
  dMatrix B;
  for(Ordinal i=0; i<qa; i++) {
    B.alias( b, i*qb*qc, qb, qc );
    for(Ordinal k=0; k<qc; k++) {
      dSlice column(B.column(k));
      dvmul( wb, column );
    }
    for(Ordinal j=0; j<qb; j++) {
      dVector row(B.row(j));
      dvmul( wc, row );
    }
  }
  B.alias( b, qa, qb*qc );
  for(Ordinal jk=0; jk<qb*qc; jk++) {
    dSlice column(B.column(jk));
    dvmul( wa, column );
  }
#endif
  dVector f(g2_wk,qtot);
  dvmul(  u,  u,  f );     // f  = u^2
  dvadd( ux,  f,  f );     // f  = u^2 + ux^2 + uy^2 + uz^2

  *H1 = dot( b, f );       // integrate
  *volume = sum( b );
}

/// Returns the H1 norm divided by the Element measure
Scalar NodalHex::norm_H1() const {
  Scalar H1, volume;
  norm_H1( &H1, &volume );
  return sqrt(H1/volume);
}

/// Integrates the data stored in the Element and optionally the volume
Scalar NodalHex::integrate( Scalar *vol ) const {
#ifdef DGM_USE_WJ
  const dVector &b = geom->wJ;
#else
  const dVector &wa = psi->wa;
  const dVector &wb = psi->wb;
  const dVector &wc = psi->wc;
  dVector b(n1_wk,qtot);

  b = geom->J;  // load in the Jacobian

  // apply integration weights
  dMatrix B;
  for(Ordinal i=0; i<qa; i++) {
    B.alias( b, i*qb*qc, qb, qc );
    for(Ordinal k=0; k<qc; k++) {
      dSlice column(B.column(k));
      dvmul( wb, column );
    }
    for(Ordinal j=0; j<qb; j++) {
      dVector row(B.row(j));
      dvmul( wc, row );
    }
  }
  B.alias( b, qa, qb*qc );
  for(Ordinal jk=0; jk<qb*qc; jk++) {
    dSlice column(B.column(jk));
    dvmul( wa, column );
  }
#endif
  dVector f(n2_wk,qtot);
  f = u;

  if (vol!=NULL) *vol = sum( b );         // element volume
  return dot( b, f );                     // integrate
}

/// Integrates the supplied vector of data over the Element
Scalar NodalHex::integrate(const dVector &v, Scalar *vol) const {
  //  cout << "NodalHex::integrate(...)" << endl;
#ifdef DGM_USE_WJ
  const dVector &b = geom->wJ;
#else
  const dVector &wa = psi->wa;
  const dVector &wb = psi->wb;
  const dVector &wc = psi->wc;
  dVector b(n1_wk,qtot);

  b = geom->J;  // load in the Jacobian

  // apply integration weights
  dMatrix B;
  for(Ordinal i=0; i<qa; i++) {
    B.alias( b, i*qb*qc, qb, qc );
    for(Ordinal k=0; k<qc; k++) {
      dSlice column(B.column(k));
      dvmul( wb, column );
    }
    for(Ordinal j=0; j<qb; j++) {
      dVector row(B.row(j));
      dvmul( wc, row );
    }
  }
  B.alias( b, qa, qb*qc );
  for(Ordinal jk=0; jk<qb*qc; jk++) {
    dSlice column(B.column(jk));
    dvmul( wa, column );
  }
#endif
  if (vol!=NULL) *vol = sum( b );         // element volume
  return dot( b, v );                     // integrate
}

/// Compute a planar average of the solution (x-z plane)
/** Note: Since we use a projection to compute the planar average, it is
    necessary to perform this computation using a higher value of p than is
    used to represent the solution to ensure that nonlinear quantities, such
    as RMS are computed correctly. */
void NodalHex::plane_average() {
  DGM_UNDEFINED;
#if 1
  Ordinal i;
  forward_transform();
  for (i=1; i<L(); i++) {
    for (Ordinal j=0; j<L(); j++) {
      for (Ordinal k=0; k<L(); k++) {
        Ordinal n = k + j*L() + i*L()*L();
        uh[n] = 0;
      }
    }
  }
  i=0;
  for (Ordinal j=1; j<L(); j++) {
    for (Ordinal k=0; k<L(); k++) {
      Ordinal n = k + j*L() + i*L()*L();
      uh[n] = 0;
    }
  }
  backward_transform();
#else
  // This is wrong since the variable quadrature mesh is not accounted for!
  dVector avg(qc, 0.0);
  dArray U(u,qa,qb,qc);
  for(Ordinal i=0; i<qa; i++) {
    for (Ordinal j=0; j<qb; j++) {
      for (Ordinal k=0; k<qc; k++) {
        avg[k] += U[i][j][k];
      }
    }
  }
  scale( 1.0/(qa*qb), avg);
  for(Ordinal i=0; i<qa; i++) {
    for (Ordinal j=0; j<qb; j++) {
      for (Ordinal k=0; k<qc; k++) {
        U[i][j][k] = avg[k];
      }
    }
  }
#endif
}

/// Returns the relative cost of this element's computations
/** WARNING: these weights are okay for Navier_Stokes but not for curved
    elements. */
int NodalHex::get_weight() const {
  static bool first_warn(true);
  static Ordinal Pmax = 10;
  static int Weight[11][2] = {{100, 100},
                              {129, 129},
                              {169, 169},
                              {232, 232},
                              {331, 331},
                              {452, 452},
                              {657, 657},
                              {869, 869},
                              {1215, 1215},
                              {1552, 1552},
                              {1989, 1989}};
  int cflag = 0;
  if (curve.get()) cflag = 1;
  if (pOrder() > Pmax) {
    if (first_warn) {
      cout << "WARNING - NodalHex::get_weight(): "
           << "pOrder (="<<pOrder()<<") > Pmax (="<<Pmax<<")"<< endl;
      first_warn = false;
    }
    return Weight[Pmax][cflag];
  } else
    return Weight[pOrder()][cflag];
}

/// Returns the Element measure (volume of a NodalHex)
Scalar NodalHex::compute_measure() const {
  //cout << "NodalHex::compute_measure()" << endl;
#ifdef DGM_USE_WJ
  const dVector &b = geom->wJ;
#else
  const dVector &wa = psi->wa;
  const dVector &wb = psi->wb;
  const dVector &wc = psi->wc;
  dVector b(g1_wk,qtot);

  b = geom->J;  // load in the Jacobian

  // apply integration weights
  dMatrix B;
  for(Ordinal i=0; i<qa; i++) {
    B.alias( b, i*qb*qc, qb, qc );
    for(Ordinal k=0; k<qc; k++) {
      dSlice column(B.column(k));
      dvmul( wb, column );
    }
    for(Ordinal j=0; j<qb; j++) {
      dVector row(B.row(j));
      dvmul( wc, row );
    }
  }
  B.alias( b, qa, qb*qc );
  for(Ordinal jk=0; jk<qb*qc; jk++) {
    dSlice column(B.column(jk));
    dvmul( wa, column );
  }
#endif
  return sum( b );     // integrate
}

Scalar NodalHex::L2_inner_product(const Element *el, Scalar *vol) const {
  //cout << "NodalHex::L2_inner_product" << endl;
#ifdef DGM_USE_WJ
  const dVector &b = geom->wJ;
#else
  const dVector &wa = psi->wa;
  const dVector &wb = psi->wb;
  const dVector &wc = psi->wc;
  dVector b(g1_wk,qtot);

  b = geom->J;  // load in the Jacobian

  // apply integration weights
  dMatrix B;
  for(Ordinal i=0; i<qa; i++) {
    B.alias( b, i*qb*qc, qb, qc );
    for(Ordinal k=0; k<qc; k++) {
      dSlice column(B.column(k));
      dvmul( wb, column );
    }
    for(Ordinal j=0; j<qb; j++) {
      dVector row(B.row(j));
      dvmul( wc, row );
    }
  }
  B.alias( b, qa, qb*qc );
  for(Ordinal jk=0; jk<qb*qc; jk++) {
    dSlice column(B.column(jk));
    dvmul( wa, column );
  }
#endif
  dVector f(g2_wk,qtot);
  dvmul(  el->u,  u,  f );    // f  = u^2

  if (vol) *vol = sum( b );
  return dot( b, f );     // integrate
}

Scalar NodalHex::L2_inner_product(const dVector& vh, const dVector& wh,
                             Scalar *vol) const {
  //cout << "NodalHex::L2_inner_product" << endl;
#ifdef DGM_USE_WJ
  const dVector &b = geom->wJ;
#else
  const dVector &wa = psi->wa;
  const dVector &wb = psi->wb;
  const dVector &wc = psi->wc;
  dVector b(g1_wk,qtot);

  b = geom->J;  // load in the Jacobian

  // apply integration weights
  dMatrix B;
  for(Ordinal i=0; i<qa; i++) {
    B.alias( b, i*qb*qc, qb, qc );
    for(Ordinal k=0; k<qc; k++) {
      dSlice column(B.column(k));
      dvmul( wb, column );
    }
    for(Ordinal j=0; j<qb; j++) {
      dVector row(B.row(j));
      dvmul( wc, row );
    }
  }
  B.alias( b, qa, qb*qc );
  for(Ordinal jk=0; jk<qb*qc; jk++) {
    dSlice column(B.column(jk));
    dvmul( wa, column );
  }
#endif
  dVector f(g2_wk,qtot);
  dvmul(  vh,  wh,  f );    // f  = vh*wh

  if (vol) *vol = sum( b );
  return dot( b, f );     // integrate
}

/// Apply filter mask
void NodalHex::filter(const dVector &mask) {
  if (state == Physical) {
    DGM::Comm::World->cerr()
      << "NodalHex::filter -- must be in transform space"<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  // apply filter transfer function to the modal storage of the element
  // cout<<"NodalHex applying filter"<<endl;
  dvmul(mask,uh);
}

/// Isolate the small scales of the element's field
void NodalHex::vms_isolate_small() {
  DGM_UNDEFINED;
  forward_transform();
  // zero the low modes
  for (Ordinal i=0; i<VMS_Lc(); i++) {
    for (Ordinal j=0; j<L(); j++) {
      for (Ordinal k=0; k<L(); k++) {
        Ordinal n = k + j*L() + i*L()*L();
        uh[n] = 0.0;
      }
    }
  }
  // zero the low modes
  for (Ordinal i=VMS_Lc(); i<L(); i++) {
    for (Ordinal j=0; j<VMS_Lc(); j++) {
      for (Ordinal k=0; k<L(); k++) {
        Ordinal n = k + j*L() + i*L()*L();
        uh[n] = 0.0;
      }
    }
    for (Ordinal j=VMS_Lc();j<L();j++){
      for (Ordinal k=0; k<VMS_Lc(); k++) {
        Ordinal n = k + j*L() + i*L()*L();
        uh[n] = 0.0;
      }
    }
  }
  backward_transform();
}

/// Isolate the small scales in transform space (to another field)
void NodalHex::vms_isolate_small(dVector &full, dVector &small) {
  DGM_UNDEFINED;
  forward_transform(full, full);
  // full  == complete field,  small == small scale field
  small=0.0;
  // transfer the high modes
  for (Ordinal i=VMS_Lc(); i<L(); i++) {
    for (Ordinal j=VMS_Lc(); j<L(); j++) {
      for (Ordinal k=VMS_Lc(); k<L(); k++) {
        Ordinal n = k + j*L() + i*L()*L();
        small[n] = full[n];
      }
    }
  }
  backward_transform(small,small);
  backward_transform(full,full);
}

/// Isolate the small scales in transform space (inplace)
void NodalHex::vms_isolate_small(dVector &small) {
  DGM_UNDEFINED;
  forward_transform(small,small);
  // small == small-scale field
  // zero the low modes
  for (Ordinal i=0; i<VMS_Lc(); i++) {
    for (Ordinal j=0; j<L(); j++) {
      for (Ordinal k=0; k<L(); k++) {
        Ordinal n = k + j*L() + i*L()*L();
        small[n] = 0.0;
      }
    }
  }
  // zero the low modes
  for (Ordinal i=VMS_Lc(); i<L(); i++) {
    for (Ordinal j=0; j<VMS_Lc(); j++) {
      for (Ordinal k=0; k<L(); k++) {
        Ordinal n = k + j*L() + i*L()*L();
        small[n] = 0.0;
      }
    }
    for (Ordinal j=VMS_Lc();j<L();j++){
      for (Ordinal k=0; k<VMS_Lc(); k++) {
        Ordinal n = k + j*L() + i*L()*L();
        small[n] = 0.0;
      }
    }
  }
  backward_transform(small,small);
}

void NodalHex::fine_scales(const int p_inc) {
  DGM_UNDEFINED;
  //cout << "NodalHex::fine_scales(const int p)" <<endl;
  Ordinal i, j, k, n;
  bool needs_transform = false;
  if (state == Physical) {
    forward_transform();
    needs_transform = true;
  }
  // lower-left Octant
  for (i=0; i<L()-p_inc; i++) {
    for (j=0; j<L()-p_inc; j++) {
      for (k=0; k<L()-p_inc; k++) {
        n = k + j*L() + i*L()*L();
        uh[n] = 0.0;
      }
    }
  }
  if (needs_transform)
    backward_transform();
}

void NodalHex::fine_scales(const int p_inc, dVector &vh) {
  //cout << "NodalHex::fine_scales(const int p, dVector &vh)" <<endl;
  Ordinal i, j, k, n;
  // lower-left Octant
  for (i=0; i<L()-p_inc; i++) {
    for (j=0; j<L()-p_inc; j++) {
      for (k=0; k<L()-p_inc; k++) {
        n = k + j*L() + i*L()*L();
        vh[n] = 0.0;
      }
    }
  }
}

void NodalHex::fine_scales_transform(const int p_inc, dVector &vh) const {
  DGM_UNDEFINED;
  //cout << "NodalHex::fine_scales_transform(const int p, dVector &vh)" <<endl;
  Ordinal i, j, k, n;
  forward_transform(vh,vh);
  // lower-left Octant
  for (i=0; i<L()-p_inc; i++) {
    for (j=0; j<L()-p_inc; j++) {
      for (k=0; k<L()-p_inc; k++) {
        n = k + j*L() + i*L()*L();
        vh[n] = 0.0;
      }
    }
  }
  backward_transform(vh,vh);
}

void NodalHex::make_constant() {
  DGM_UNDEFINED;
  bool needs_transform = false;
  if (state == Physical) {
    forward_transform();
    needs_transform = true;
  }
  Scalar uh0 = uh[0];
  uh = 0.0;
  uh[0] = uh0;
  if (needs_transform)
    backward_transform();
}

void NodalHex::low_modes(const Ordinal inp) {
  const Ordinal np = numeric_cast<Ordinal>(inp);
  if (np>=pOrder()) return;  // nothing to do
  DGM_UNDEFINED;
  Ordinal i, j, k, n;
  bool needs_transform = false;
  if (state == Physical) {
    forward_transform();
    needs_transform = true;
  }
  // upper left
  for (i=0; i<np+1; i++) {
    for (j=np+1; j<L(); j++) {
      for (k=np+1; k<L(); k++) {
        n = k + j*L() + i*L()*L();
        uh[n] = 0.0;
      }
    }
  }
  // lower right
  for (j=0; j<=np+1; j++) {
    for (i=np+1; i<L(); i++) {
      for (k=np+1; k<L(); k++) {
        n = k + j*L() + i*L()*L();
        uh[n] = 0.0;
      }
    }
  }
  // upper right
  for (i=np+1; i<L(); i++) {
    for (j=np+1; j<L(); j++) {
      for (k=np+1; k<L(); k++) {
        n = k + j*L() + i*L()*L();
        uh[n] = 0.0;
      }
    }
  }
  // lower back
  for (i=0; i<np+1; i++) {
    for (j=0; j<np+1; j++) {
      for (k=np+1; k<L(); k++) {
        n = k + j*L() + i*L()*L();
        uh[n] = 0.0;
      }
    }
  }
  if (needs_transform)
    backward_transform();
}


void NodalHex::get_side_Ds(const int, const dVector& , dVector& ) const {
  cerr << "NodalHex::get_side_Ds(const int, const dVector& ,dVector&) "
    "undefined" << endl;
  DGM::Comm::World->exit(DGM::FAILURE);
}

void NodalHex::get_side_curvature(const int sid, dVector &dcurv) const {
  cerr << "NodalHex::get_side_curvature(const int, dVector& ) undefined"
       << endl;
  DGM::Comm::World->exit(DGM::FAILURE);
}

/// Get the coordinates of straight-side
void NodalHex::get_straight_side_coordinates(const Ordinal face_id, dVector &x,
                                             dVector &y, dVector &z) const {
  const Ordinal q = side2size(face_id);
  x.resize(q); y.resize(q); z.resize(q);
  x = 0.0; y = 0.0; z = 0.0;
  dVector f(q);
  for(Ordinal i = 0; i < 4; ++i){
    const Ordinal vn = vertex_num(face_id,i);
    side_mode(face_id,psi->vertMode(vn),f);
    daxpy(vert[vn]->x,f,x);
    daxpy(vert[vn]->y,f,y);
    daxpy(vert[vn]->z,f,z);
  }
  if(face_id >= 6){
    DGM::Comm::World->cerr() << "Illegal face ID value" <<face_id<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
}

Ordinal NodalHex::vertex_num(const Ordinal i, const Ordinal j) const {
  return v_num[i][j];
}

Ordinal NodalHex::edge_num(const Ordinal i, const Ordinal j) const {
  return e_num[i][j];
}

// f Coordinates => fh   modal coefficients for Curve face
//                + fh_e modal coefficients for Curve edges
void NodalHex::forward_transform_side(const Ordinal face_id, dVector &f,
                                      dVector &fh, dVector *fh_e) {
  Ordinal i, j, k, l;
  Ordinal Le = L()-2;

  dVector tmp(qa*qb),tmp1(qa*qb),tmp2(qa);  //assume
  dVector vertc(4);

  // set vertices (top vertex already)
  vertc[0] = f[0];
  vertc[1] = f[qa-1];
  vertc[2] = f[qa*qb-1];
  vertc[3] = f[qa*(qb-1)];

  // Assume X, make sure the correct match
  //  assert(vertc[0] == vert[v_num[face_id][0]]->x &&
  //   vertc[1] == vert[v_num[face_id][1]]->x &&
  //   vertc[2] == vert[v_num[face_id][2]]->x &&
  //   vertc[3] == vert[v_num[face_id][3]]->x);
  //  assert(fh_e.size() == 4);

  fh.resize(Le*Le);

  for(i=0;i<4;i++)
    fh_e[i].resize(Le); //allocate the space for the edge modal

  tmp = f;  //temporary copy as backup

  // remove vertex modes from face
  for(j=0;j<4;++j){
    side_mode(face_id, psi->vertMode(j), tmp1);
    daxpy( -vertc[j],tmp1, f);
    // side_mode(face_id, psi->vertMode(v_num[face_id][j]), tmp1);
    // daxpy( -vert[v_num[fac][j]]->x, tmp1, f);
  }

  // transform edges
  for(j=0;j<4;++j){
    get_edge(qa,qb,f.ptr(), j, tmp2.ptr());
    forward_transform_edge(tmp2,fh_e[j]);
  }

  // transform interior

  // remove the edge modes from face
  for(j=0;j<4;++j)
    for(dVector::size_type i = 0; i < fh_e[j].size(); ++i){
      side_mode(face_id, psi->edgeMode(e_num[face_id][j],i), tmp);
      daxpy(-fh_e[j][i], tmp, f);
    }

  // finally take inner product
  for(i = 0; i < Le; ++i)
    for(j = 0; j < Le; ++j){
      side_mode( face_id, psi->faceMode(face_id,i,j), tmp);

      for(k = 0; k < qb; ++k)
        for(l=0; l< qa; ++l)
          tmp[k*qa+l] *= psi->wa[l];

      for(k = 0; k < qb; ++k)
        for(l=0; l< qa; ++l)
          tmp[k*qa+l] *= psi->wb[k];

      fh[i*Le+j] =0;
      for(k = 0; k < qa*qb; ++k)
        fh[i*Le+j] += tmp[k]*f[k];
    }

  solve_2d_mass_matrix(fh); // for face modal
}

/** Add a discrete version of a Dirac delta function at a quadrature point
    with amplitude equal amp */
void NodalHex::add_Dirac_delta(const Ordinal qpt, const Scalar amp) {
  assert( qpt >= 0 && qpt < qtot );
  // recover i, j and k from qpt =  k + j*qc + i*qc*qb
  const Ordinal tmp = qpt % (qc*qb);  // = k + j*qc
  const Ordinal k = tmp % qc;
  const Ordinal j = (tmp-k)/qc ;
  const Ordinal i = (qpt-tmp)/(qc*qb);
  const Scalar wght = (psi->wa[i])*(psi->wb[j])*(psi->wc[k]);
  u[qpt] += amp/(wght*geom->J[qpt]);
}

/** Add a discrete version of a Dirac delta function at an arbitrary point p
    with amplitude equal amp.  The Point, p, must be within the NodalHex
    element. */
void NodalHex::add_Dirac_delta(const Point &p, const Scalar amp) {
  Scalar r, s, t;
  // First get the local coordinate on line
  if(!get_local_coordinates(p,r,s,t)) {
    DGM::Comm::World->cerr()<<
      "NodalHex::Add_Dirac_delta: could not find (r,s,t)"<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  const Point q(r,s, t);
  return add_local_Dirac_delta(q,amp);
}

void NodalHex::add_local_Dirac_delta(const Point &p, const Scalar amp) {

  const Scalar r=p.x;
  const Scalar s=p.y;
  const Scalar t=p.z;

  dMatrix imx, imy, imz;
  dVector za(qa), wa(qa);
  dVector zb(qb), wb(qb);
  dVector zc(qc), wc(qc);

  // Compute Gauss-Lobatto-Legendre points and weights
  zwgll(zc,wc); // z direction
  zwgll(zb,wb); // y direction
  zwgll(za,wa); // x direction

  // Form the interpolation matrix from Gauss-Lobatto-Legendre
  imz.resize(1,qc);
  igllm(imz,zc,t);

  imy.resize(1,qb);
  igllm(imy,zb,s);

  imx.resize(1,qa);
  igllm(imx,za,r);

  // Apply the Dirac delta function operator
  for (Ordinal i=0; i<qa; i++) {
    for (Ordinal j=0; j<qb; j++) {
      for (Ordinal k=0; k<qc; k++) {
        const Ordinal qpt = k + j*qc + i*qc*qb;
        const Scalar im = imx(0,i)*imy(0,j)*imz(0,k);
        const Scalar wght = (psi->wa[i])*(psi->wb[j])*(psi->wc[k]);
        u[qpt] += im*amp/(wght*geom->J[qpt]);
      }
    }
  }
}
void NodalHex::add_local_Dirac_delta(const vector<dMatrix> &M,
    const Scalar amp)
{
  if (3!=M.size())
    error("NodalHex::add_local_Dirac_delta: Incorrect matrix size.");
  if (M[0].rows() != M[1].rows() || M[0].rows() != M[2].rows())
    error("NodalHex::add_local_Dirac_delta: Inconsistant matrix size.");
  if (M[0].cols() != qc || M[1].cols() != qb || M[2].cols() != qa)
    error("NodalHex::add_local_Dirac_delta: Inconsistant matrix size.");
  const dMatrix &imz = M[0];
  const dMatrix &imy = M[1];
  const dMatrix &imx = M[2];


  // Apply the Dirac delta function operator
  for (Ordinal i=0; i<qa; i++) {
    for (Ordinal j=0; j<qb; j++) {
      for (Ordinal k=0; k<qc; k++) {
        const Ordinal qpt = k + j*qc + i*qc*qb;
        const Scalar im = imx(0,i)*imy(0,j)*imz(0,k);
        const Scalar wght = (psi->wa[i])*(psi->wb[j])*(psi->wc[k]);
        u[qpt] += im*amp/(wght*geom->J[qpt]);
      }
    }
  }
}

/// Extract the solution at the Point p
Scalar NodalHex::interpolate_point(const Point &p) const {
  if (state != Physical) {
    cerr << "NodalHex::interpolate_points -- not in physical space"<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  Scalar r, s, t;
  // SSC: the get_local_coordinates methods are expensive.  Since the probe
  // points don't move, we could cache this for each probe point so that they
  // don't have to be recomputed every time that Response::probe(...) gets
  // called
  if(!get_local_coordinates(p,r,s,t)) {
    DGM::Comm::World->cerr()<<"Interp_point: could not find (r,s,t)"<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  const Point q(r,s,t);
  return interpolate_local_point(q);
}

/// Extract the solution at the Point p
Scalar NodalHex::interpolate_local_point(const Point &p) const {

  const Scalar r=p.x;
  const Scalar s=p.y;
  const Scalar t=p.z;

  // SSC: we should consider building these interpolation operators once and
  // then have a fast apply method to use them.

  dVector im(qc), z(qc), w(qc);
  // 3D interpolation
  // Compute Gauss-Lobatto-Legendre points and weights along z
  zwgll(z,w); // z direction
  // Form the interpolation matrix from Gauss-Lobatto-Legendre to t
  dMatrix M(im,1,qc);
  igllm(M,z,t);
  // Generate a temporary array (of length qa*qb) of points at z=t
  dVector tmpxy(qa*qb);
  {
    dMatrix U(u,qa*qb,qc);
    mvmult(U, im, tmpxy);
  }

  Ordinal sqb = qb, sqa = qa;
  if (im.size() != sqb) {
    im.resize(qb);
    z.resize(qb);
    w.resize(qb);
    // 2D interpolation
    // Compute Gauss-Lobatto-Legendre points and weights
    zwgll(z,w); // y direction
    M.alias(im,1,qb);
  }
  // Form the interpolation matrix from Gauss-Lobatto-Legendre to s
  igllm(M,z,s);
  // Interpolate to temporary points at y=s at each x location
  dVector tmp(qa);
  {
    dMatrix U(tmpxy,qa,qb);
    mvmult(U, im, tmp);
  }

  if (im.size() != sqa) {
    im.resize(qa);
    z .resize(qa);
    w .resize(qa);
    // 1D interpolation in the a-direction
    // Compute Gauss-Lobatto-Legendre points and weights
    zwgll(z,w); // x direction
    M.alias(im,1,qa);
  }
  // Form the interpolation matrix from Gauss-Lobatto-Legendre to r
  igllm(M,z,r);
  // Now interpolate along our temporary y points to get the value at r,s
  const Scalar result = dot(im,tmp);

  return result; // the interpolated solution is returned

}

void NodalHex::calculate_interpolation_matrices(vector<dMatrix>    &M,
                                            const vector<Point>&ps) const{
  const Ordinal N = numeric_cast<Ordinal>(ps.size());

  M.resize(3);
  M[0].resize(N,qc);
  M[1].resize(N,qb);
  M[2].resize(N,qa);

  dVector Z(qc), W(qc);
  dVector X(N);
  zwgll(Z,W);

  for (Ordinal i=0; i<N; ++i) X[i] = ps[i].z;
  igllm(M[0],Z,X);

  if (qb!=qc) {
    Z.resize(qb); W.resize(qb);
    zwgll(Z,W);
  }
  for (Ordinal i=0; i<N; ++i) X[i] = ps[i].y;
  igllm(M[1],Z,X);

  if (qa!=qb) {
    Z.resize(qa); W.resize(qa);
    zwgll(Z,W);
  }
  for (Ordinal i=0; i<N; ++i) X[i] = ps[i].x;
  igllm(M[2],Z,X);
}

void NodalHex::apply_interpolation_matrices(dVector &V,
                                        const vector<dMatrix> &M) const{
  if (3!=M.size())
    error("NodalHex::apply_interplation_matrices: Incorrect matrix size.");
  if (M[0].rows() != M[1].rows() || M[0].rows() != M[2].rows())
    error("NodalHex::apply_interplation_matrices: Inconsistant matrix size.");
  Ordinal sqa = qa, sqb = qb, sqc = qc;
  if (M[0].cols() != sqc || M[1].cols() != sqb || M[2].cols() != sqa)
    error("NodalHex::apply_interplation_matrices: Inconsistant matrix size.");

  const Ordinal N = M[0].rows();

  dMatrix T,S;
  if (N<qc) T.alias (g1_wk,N,qa*qb);
  else      T.resize(      N,qa*qb);

  if (N<qb*qc) S.alias (g2_wk,N,qa);
  else         S.resize(      N,qa);

  const dMatrix U(u,qa*qb,qc);
  matmult(M[0], 'T', U, T);

  for (Ordinal i=0; i<N; ++i) {
    const dMatrix m ( T[i],qa,qb  );
    const dVector v ( M[1].row(i) );
    dVector       s (    S.row(i) );
    mvmult (m,v,s);
  }

  V.resize(N);
  for (Ordinal i=0; i<N; ++i) {
    const dVector r1 ( M[2].row(i) );
    const dVector r2 (    S.row(i) );
    V[i] = dot(r1,r2);
  }
}

/// Extract the solution at the Points ps
void NodalHex::interpolate_points(const vector<Point>& ps,
                                  dVector &vals) const {
  if (state != Physical) {
    cerr << "NodalHex::interpolate_points -- not in physical space"<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }

  vals.resize(numeric_cast<Ordinal>(ps.size()));

  for (size_t ip = 0; ip != ps.size(); ip++) {
    const Point& p = ps[ip];
    const Scalar r = p.x;
    const Scalar s = p.y;
    const Scalar t = p.z;

    dMatrix im;
    dVector tmp(qa), result(1), tmpxy;

    // SSC: we should consider building these interpolation operators once and
    // then have a fast apply method to use them.

    // 3D interpolation
    dVector tmpz;
    dVector z3(qc), w3(qc);
    tmpxy.resize(qa*qb);
    // Compute Gauss-Lobatto-Legendre points and weights along z
    im.resize(1,qc);
    zwgll(z3,w3); // z direction
    // Form the interpolation matrix from Gauss-Lobatto-Legendre to t
    igllm(im,z3,t);
    // Generate a temporary array (of length qa*qb) of points at z=t
    for (Ordinal i=0;i<qa;i++) {
      for (Ordinal j=0;j<qb;j++) {
        // Now get the solution values at the appropriate quadrature points.
        // In 3D, we need to get qc values starting at j*qc + i*qc*qb
        Ordinal offset = j*qc + i*qc*qb;
        tmpz.alias(u,offset,qc);
        mvmult( im, tmpz, result);
        tmpxy[j+i*qb] = result[0];
      }
    }
    // 2D interpolation
    dVector tmpy;
    dVector z2(qb), w2(qb);
    // Compute Gauss-Lobatto-Legendre points and weights
    zwgll(z2,w2); // y direction
    // Form the interpolation matrix from Gauss-Lobatto-Legendre to s
    im.resize(1,qb);
    igllm(im,z2,s);
    // Interpolate to temporary points at y=s at each x location
    for (Ordinal i=0;i<qa;i++) {
      // Now get the solution values at the appropriate quadrature points.
      // Use the temporary array calculated above for this
      // particular z value
      tmpy.alias(tmpxy,i*qb,qb);
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

/// Get Edge information from Face
void NodalHex::get_edge(Ordinal q1, Ordinal q2, Scalar *from,
                        Ordinal edge_id, Scalar *to){
  switch(edge_id){
  case 0:
    for(Ordinal i=0;i<q1;i++)
      to[i] = from[i];
    break;
  case 1:
    for(Ordinal i=0;i<q2;i++)
      to[i] = from[(i+1)*q1-1];
    break;
  case 2:
    for(Ordinal i=0;i<q1;i++)
      to[i] = from[(q2-1)*q1+i];
    break;
  case 3:
    for(Ordinal i=0;i<q2;i++)
      to[i] = from[i*q2];
    break;
  default:
    DGM::Comm::World->cerr() << "Illegal Edge id for NodalHex element" << endl;
    DGM::Comm::World->exit(DGM::FAILURE);
    break;
  }
}

// Warning: use the Edge[0] basis information, possible problem [gqchen]
void NodalHex::forward_transform_edge(dVector &f, dVector &fh) {
  Ordinal i,q;
  Ordinal Le = L()-2; // edge modal number
  dVector  &wa = psi->wa;
  if(!Le) return;
  // calculate inner product with basis
  q = qa-2;
  for(i=0;i<q;i++)
    f[i+1] *= wa[i+1]; // excluding the vertex modes
  for(i = 0; i < Le; ++i){
    fh[i] = 0;
    for(Ordinal j=0;j<q;j++) // excluding the vertex
      fh[i] += psi->edgeMode(0,i).a[j+1]*f[j+1];
  }
  solve_1d_mass_matrix(fh); // for Edge modal
}

// for curved face modal
void NodalHex::solve_2d_mass_matrix(dVector &fh) const {
  Minfo M2d;
  get_2d_mass_matrix(M2d);
#ifdef DGM_CHOLESKY_MASS_MATRIX
  Cholesky_solve(M2d.mat, fh);
#else
  LU_solve(M2d.mat, M2d.pivots, fh);
#endif
}

// not ok
/// For the face modal transformation
void NodalHex::get_2d_mass_matrix(Minfo &M2d) const {
  const Ordinal Le = L()-2;
  dVector tmp1(qa-2),tmp2(qb-2),w1,w2,psi1,psi2;
  dVector &wa = psi->wa;
  dVector &wb = psi->wb;
  const Ordinal fid = 0;        // implement for face 0
  const Ordinal ll = Le*Le;
  M2d.mat.resize(ll,ll);
  // It is symmetric, should take advantage of it [gqchen]
  for (Ordinal i = 0; i < Le; ++i) {
    for (Ordinal j = 0; j < Le; ++j) {
      w1.alias(wa,1,qa-2);
      psi1.alias(psi->faceMode(fid,i,j).a,1,qa-2);
      dvmul(w1,psi1,tmp1);
      w2.alias(wb,1,qb-2);
      psi2.alias(psi->faceMode(fid,i,j).b,1,qb-2);
      dvmul(w2,psi2,tmp2);
      for (Ordinal k = 0; k < Le; ++k) {
        for (Ordinal l = 0; l < Le; ++l) {
          psi1.alias(psi->faceMode(fid,k,l).a,1,qa-2);
          M2d.mat[i*Le+j][k*Le+l] = dot(tmp1, psi1);
          psi2.alias(psi->faceMode(fid,k,l).b,1,qb-2);
          M2d.mat[i*Le+j][k*Le+l] *= dot(tmp2, psi2);
        }
      }
    }
  }
#ifdef DGM_CHOLESKY_MASS_MATRIX
  if (Cholesky_factor(M2d.mat) !=0) {
    DGM::Comm::World->cerr() << "Cholesky_factor() failed." << endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
#else
  if (LU_factor(M2d.mat, M2d.pivots) !=0) {
    DGM::Comm::World->cerr() << "LU_factor() failed." << endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
#endif
}

// not ok
void NodalHex::J_backward_transform(dVector &fh, dVector &f) {
  dMatrix &Ba = psi->Ba;
  dMatrix &Bb = psi->Bb;
  dMatrix &Bc = psi->Bc;
#if 1
  dMatrix F, Fh, H, Ha;
  H.alias( Lwk, qa, L()*L() );
  Fh.alias( fh, L(), L()*L() );
  matmult( 'T', Ba, Fh, H );
  for (Ordinal i=0; i<qa; ++i) {
    H.alias( Lwk, i*L()*L(), L(), L() );
    Ha.alias( Lwk2, i*qb*L(), qb, L() );
    matmult( 'T', Bb, H, Ha );
  }
  F.alias( f, qa*qb, qc );
  Ha.alias( Lwk2, qa*qb, L());
  matmult( Ha, Bc, F );
#else
  dMatrix H(Lwk, L()*L(), qa);
  dMatrix Fh( fh, L(), L()*L() );  // Fh[Lb,La]
  dMatrix F,Ha;
  matmult('T', Ba,Fh, H );

  for(Ordinal i=0;i<L();i++){
    wk.alias(Lwk, i*qa*L(), qa, L());
    Ha.alias(Lwk2, i*qa*qb, qa, qb );
    matmult(H, Bb, Ha);
  }

  F.alias( f, qa*qb, qc );
  Ha.alias( Lwk2, qa*qb, L() );
  matmult( Ha, Bc, F );
#endif
}

// not ok
void NodalHex::get_curved_coordinates() {
  // cerr << "NodalHex::get_curved_coordinates() is not implemented" << endl;
  // DGM::Comm::World->exit(DGM::FAILURE);
  const Ordinal L = this->L();
  const Ordinal Le = L-2;
  C.reset( new Coord(qtot) );
  *C = 0;

  // it is very important to declare these in the correct order [SSC]
  dVector fh(nModes()), tmp;
  fh = 0;

  // NodalHex map

  // x

  // vertex modal
  fh[0]       = vert[0]->x;
  fh[L-1]     = vert[1]->x;
  fh[L*L-1]   = vert[2]->x;
  fh[L*(L-1)] = vert[3]->x;

  fh[L*L*(L-1)+0]         = vert[4]->x;
  fh[L*L*(L-1)+L-1]       = vert[5]->x;
  fh[L*L*(L-1)+L*L-1]     = vert[6]->x;
  fh[L*L*(L-1)+L*(L-1)]   = vert[7]->x;

  // edge modal
  for(Ordinal i=0;i<4;i++){
    switch(e_num[curve->side][i]){
    case 0:
      tmp.alias(fh,L+1,Le);
      tmp = curve->xh_e[i];
      break;
    case 1:
      for(Ordinal j=0;j<Le;j++)
        fh[L+L-1+j*L] = curve->xh_e[i][j];
      break;
    case 2:
      tmp.alias(fh,L*(L-1)+1,Le);
      tmp = curve->xh_e[i];
      break;
    case 3:
      for(Ordinal j=0;j<Le;j++)
        fh[L+j*L] = curve->xh_e[i][j];
      break;
    case 4:
      for(Ordinal j=0;j<Le;j++)
        fh[L*L+j*L*L] = curve->xh_e[i][j];
      break;
    case 5:
      for(Ordinal j=0;j<Le;j++)
        fh[L*L+L-1+j*L*L] = curve->xh_e[i][j];
      break;
    case 6:
      for(Ordinal j=0;j<Le;j++)
        fh[L*L+L*L-1+j*L*L] = curve->xh_e[i][j];
      break;
    case 7:
      for(Ordinal j=0;j<Le;j++)
        fh[L*L+L*(L-1)+j*L*L] = curve->xh_e[i][j];
      break;
    case 8:
      tmp.alias(fh,L*L*(L-1)+1,Le);
      tmp = curve->xh_e[i];
      break;
    case 9:
      for(Ordinal j=0;j<Le;j++)
        fh[L*L*(L-1)+L+L-1+j*L] = curve->xh_e[i][j];
      break;
    case 10:
      tmp.alias(fh,L*L*(L-1)+L*(L-1)+1,Le);
      tmp = curve->xh_e[i];
      break;
    case 11:
      for(Ordinal j=0;j<Le;j++)
        fh[L*L*(L-1)+L+j*L] = curve->xh_e[i][j];
      break;
    }
  }

  int n = 0;
  // face modal
  switch(curve->side){
  case 0:
    for(Ordinal i=0;i<Le;i++)
      for(Ordinal j=0;j<Le;j++)
        fh[L+1+i*L+j] = curve->xh[n++];
    break;
  case 1:
    for(Ordinal i=0;i<Le;i++)
      for(Ordinal j=0;j<Le;j++)
        fh[L*L+1+i*L*L+j] = curve->xh[n++];
    break;
  case 2:
    for(Ordinal i=0;i<Le;i++)
      for(Ordinal j=0;j<Le;j++)
        fh[L*L+L+L-1+i*L*L+j*L] = curve->xh[n++];
    break;
  case 3:
    for(Ordinal i=0;i<Le;i++)
      for(Ordinal j=0;j<Le;j++)
        fh[L*L+L*(L-1)+1+i*L*L+j] = curve->xh[n++];
    break;
  case 4:
    for(Ordinal i=0;i<Le;i++)
      for(Ordinal j=0;j<Le;j++)
        fh[L*L+L+i*L*L+j*L] = curve->xh[n++];
    break;
  case 5:
    for(Ordinal i=0;i<Le;i++)
      for(Ordinal j=0;j<Le;j++)
        fh[L*L*(L-1)+L+1+i*L+j] = curve->xh[n++];
    break;
  }

  J_backward_transform( fh, C->x );

  // NodalHex map

  // y
  fh = 0;
  // vertex modal
  fh[0]       = vert[0]->y;
  fh[L-1]     = vert[1]->y;
  fh[L*L-1]   = vert[2]->y;
  fh[L*(L-1)] = vert[3]->y;

  fh[L*L*(L-1)+0]         = vert[4]->y;
  fh[L*L*(L-1)+L-1]       = vert[5]->y;
  fh[L*L*(L-1)+L*L-1]     = vert[6]->y;
  fh[L*L*(L-1)+L*(L-1)]   = vert[7]->y;

  // edge modal
  for(Ordinal i=0;i<4;i++){
    switch(e_num[curve->side][i]){
    case 0:
      tmp.alias(fh,L+1,Le);
      tmp = curve->yh_e[i];
      break;
    case 1:
      for(Ordinal j=0;j<Le;j++)
        fh[L+L-1+j*L] = curve->yh_e[i][j];
      break;
    case 2:
      tmp.alias(fh,L*(L-1)+1,Le);
      tmp = curve->yh_e[i];
      break;
    case 3:
      for(Ordinal j=0;j<Le;j++)
        fh[L+j*L] = curve->yh_e[i][j];
      break;
    case 4:
      for(Ordinal j=0;j<Le;j++)
        fh[L*L+j*L*L] = curve->yh_e[i][j];
      break;
    case 5:
      for(Ordinal j=0;j<Le;j++)
        fh[L*L+L-1+j*L*L] = curve->yh_e[i][j];
      break;
    case 6:
      for(Ordinal j=0;j<Le;j++)
        fh[L*L+L*L-1+j*L*L] = curve->yh_e[i][j];
      break;
    case 7:
      for(Ordinal j=0;j<Le;j++)
        fh[L*L+L*(L-1)+j*L*L] = curve->yh_e[i][j];
      break;
    case 8:
      tmp.alias(fh,L*L*(L-1)+1,Le);
      tmp = curve->yh_e[i];
      break;
    case 9:
      for(Ordinal j=0;j<Le;j++)
        fh[L*L*(L-1)+L+L-1+j*L] = curve->yh_e[i][j];
      break;
    case 10:
      tmp.alias(fh,L*L*(L-1)+L*(L-1)+1,Le);
      tmp = curve->yh_e[i];
      break;
    case 11:
      for(Ordinal j=0;j<Le;j++)
        fh[L*L*(L-1)+L+j*L] = curve->yh_e[i][j];
      break;
    }
  }

  n = 0;
  // face modal
  switch(curve->side){
  case 0:
    for(Ordinal i=0;i<Le;i++)
      for(Ordinal j=0;j<Le;j++)
        fh[L+1+i*L+j] = curve->yh[n++];
    break;
  case 1:
    for(Ordinal i=0;i<Le;i++)
      for(Ordinal j=0;j<Le;j++)
        fh[L*L+1+i*L*L+j] = curve->yh[n++];
    break;
  case 2:
    for(Ordinal i=0;i<Le;i++)
      for(Ordinal j=0;j<Le;j++)
        fh[L*L+L+L-1+i*L*L+j*L] = curve->yh[n++];
    break;
  case 3:
    for(Ordinal i=0;i<Le;i++)
      for(Ordinal j=0;j<Le;j++)
        fh[L*L+L*(L-1)+1+i*L*L+j] = curve->yh[n++];
    break;
  case 4:
    for(Ordinal i=0;i<Le;i++)
      for(Ordinal j=0;j<Le;j++)
        fh[L*L+L+i*L*L+j*L] = curve->yh[n++];
    break;
  case 5:
    for(Ordinal i=0;i<Le;i++)
      for(Ordinal j=0;j<Le;j++)
        fh[L*L*(L-1)+L+1+i*L+j] = curve->yh[n++];
    break;
  }

  J_backward_transform( fh, C->y );

  // NodalHex map

  // z
  fh = 0;
  // vertex modal
  fh[0]       = vert[0]->z;
  fh[L-1]     = vert[1]->z;
  fh[L*L-1]   = vert[2]->z;
  fh[L*(L-1)] = vert[3]->z;

  fh[L*L*(L-1)+0]         = vert[4]->z;
  fh[L*L*(L-1)+L-1]       = vert[5]->z;
  fh[L*L*(L-1)+L*L-1]     = vert[6]->z;
  fh[L*L*(L-1)+L*(L-1)]   = vert[7]->z;

  // edge modal
  for(Ordinal i=0;i<4;i++){
    switch(e_num[curve->side][i]){
    case 0:
      tmp.alias(fh,L+1,Le);
      tmp = curve->zh_e[i];
      break;
    case 1:
      for(Ordinal j=0;j<Le;j++)
        fh[L+L-1+j*L] = curve->zh_e[i][j];
      break;
    case 2:
      tmp.alias(fh,L*(L-1)+1,Le);
      tmp = curve->zh_e[i];
      break;
    case 3:
      for(Ordinal j=0;j<Le;j++)
        fh[L+j*L] = curve->zh_e[i][j];
      break;
    case 4:
      for(Ordinal j=0;j<Le;j++)
        fh[L*L+j*L*L] = curve->zh_e[i][j];
      break;
    case 5:
      for(Ordinal j=0;j<Le;j++)
        fh[L*L+L-1+j*L*L] = curve->zh_e[i][j];
      break;
    case 6:
      for(Ordinal j=0;j<Le;j++)
        fh[L*L+L*L-1+j*L*L] = curve->zh_e[i][j];
      break;
    case 7:
      for(Ordinal j=0;j<Le;j++)
        fh[L*L+L*(L-1)+j*L*L] = curve->zh_e[i][j];
      break;
    case 8:
      tmp.alias(fh,L*L*(L-1)+1,Le);
      tmp = curve->zh_e[i];
      break;
    case 9:
      for(Ordinal j=0;j<Le;j++)
        fh[L*L*(L-1)+L+L-1+j*L] = curve->zh_e[i][j];
      break;
    case 10:
      tmp.alias(fh,L*L*(L-1)+L*(L-1)+1,Le);
      tmp = curve->zh_e[i];
      break;
    case 11:
      for(Ordinal j=0;j<Le;j++)
        fh[L*L*(L-1)+L+j*L] = curve->zh_e[i][j];
      break;
    }
  }

  n = 0;
  // face modal
  switch(curve->side){
  case 0:
    for(Ordinal i=0;i<Le;i++)
      for(Ordinal j=0;j<Le;j++)
        fh[L+1+i*L+j] = curve->zh[n++];
    break;
  case 1:
    for(Ordinal i=0;i<Le;i++)
      for(Ordinal j=0;j<Le;j++)
        fh[L*L+1+i*L*L+j] = curve->zh[n++];
    break;
  case 2:
    for(Ordinal i=0;i<Le;i++)
      for(Ordinal j=0;j<Le;j++)
        fh[L*L+L+L-1+i*L*L+j*L] = curve->zh[n++];
    break;
  case 3:
    for(Ordinal i=0;i<Le;i++)
      for(Ordinal j=0;j<Le;j++)
        fh[L*L+L*(L-1)+1+i*L*L+j] = curve->zh[n++];
    break;
  case 4:
    for(Ordinal i=0;i<Le;i++)
      for(Ordinal j=0;j<Le;j++)
        fh[L*L+L+i*L*L+j*L] = curve->zh[n++];
    break;
  case 5:
    for(Ordinal i=0;i<Le;i++)
      for(Ordinal j=0;j<Le;j++)
        fh[L*L*(L-1)+L+1+i*L+j] = curve->zh[n++];
    break;
  }
  J_backward_transform( fh, C->z );
}


void NodalHex::compute_curved_geometry() {
  // cout << "NodalHex::compute_curved_geometry() for element "
  //      << gid() << endl;

  // temporary storage
  dVector xr(qtot), xs(qtot), xt(qtot);
  dVector yr(qtot), ys(qtot), yt(qtot);
  dVector zr(qtot), zs(qtot), zt(qtot);
  dVector tmp1(qtot),tmp2(qtot);

  // compute coordinate gradients in mapped space
  local_gradient( C->x, xr, xs, xt );
  local_gradient( C->y, yr, ys, yt );
  local_gradient( C->z, zr, zs, zt );

  // compute determinate of the Jacobian
  //  Scalar detJ = xr*ys*zt + yr*zs*xt + zr*xs*yt -
  //                xt*ys*zr - zt*xs*yr - xr*zs*yt;

  dvmul(xr,ys,tmp1);
  dvmul(tmp1,zt,tmp1);

  dvmul(yr,zs,tmp2);
  dvvtvp(xt,tmp2,tmp1,tmp1);

  dvmul(zr,xs,tmp2);
  dvvtvp(yt,tmp2,tmp1,tmp1);

  dvmul(xt,ys,tmp2);
  dvvtvm(zr,tmp2,tmp1,tmp1);

  dvmul(zt,xs,tmp2);
  dvvtvm(yr,tmp2,tmp1,tmp1);

  dvmul(xr,zs,tmp2);
  dvvtvm(yt,tmp2,tmp1,geom->J);

  for (Ordinal i=0; i<qtot; i++) {
    if(geom->J[i] <= 0.0) {
      cerr << "Element: " << gid() <<" has a nonpositive Jacobian" << endl;
      DGM::Comm::World->exit(DGM::FAILURE);
    }
  }

  dvmul(ys,zt,tmp1);
  dvvtvm(yt,zs,tmp1,geom->rx);

  dvmul(xs,zt,tmp1);
  dvvtvm(xt,zs,tmp1,geom->ry);
  scale(-1.0,geom->ry);

  dvmul(xs,yt,tmp1);
  dvvtvm(xt,ys,tmp1,geom->rz);

  dvmul(yr,zt,tmp1);
  dvvtvm(yt,zr,tmp1,geom->sx);
  scale(-1.0,geom->sx);

  dvmul(xr,zt,tmp1);
  dvvtvm(xt,zr,tmp1,geom->sy);

  dvmul(xr,yt,tmp1);
  dvvtvm(xt,yr,tmp1,geom->sz);
  scale(-1.0,geom->sz);

  dvmul(yr,zs,tmp1);
  dvvtvm(ys,zr,tmp1,geom->tx);

  dvmul(xr,zs,tmp1);
  dvvtvm(xs,zr,tmp1,geom->ty);
  scale(-1.0,geom->ty);

  dvmul(xr,zs,tmp1);
  dvvtvm(xs,zr,tmp1,geom->tz);

  dvdiv(geom->J,geom->rx);
  dvdiv(geom->J,geom->ry);
  dvdiv(geom->J,geom->rz);

  dvdiv(geom->J,geom->sx);
  dvdiv(geom->J,geom->sy);
  dvdiv(geom->J,geom->sz);

  dvdiv(geom->J,geom->tx);
  dvdiv(geom->J,geom->ty);
  dvdiv(geom->J,geom->tz);

#ifdef DGM_USE_WJ
  const dVector &wa = psi->wa;
  const dVector &wb = psi->wb;
  const dVector &wc = psi->wc;
  dVector &b =  geom->wJ;
  b = geom->J;  // load in the Jacobian

  // apply integration weights
  dMatrix B;
  for(Ordinal i=0; i<qa; i++) {
    B.alias( b, i*qb*qc, qb, qc );
    for(Ordinal k=0; k<qc; k++) {
      dSlice column(B.column(k));
      dvmul( wb, column );
    }
    for(Ordinal j=0; j<qb; j++) {
      dVector row(B.row(j));
      dvmul( wc, row );
    }
  }
  B.alias( b, qa, qb*qc );
  for(Ordinal jk=0; jk<qb*qc; jk++) {
    dSlice column(B.column(jk));
    dvmul( wa, column );
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

vector<dMatrix*> NodalHex::get_interpolation_matrices() const {
  const Element *U = this;
  vector<dMatrix*> matrices;
  for (Ordinal i=0; i<6; ++i) {
    Ordinal q1(0), q2(0);
    side_to_size(q1, q2, i);
    const Ordinal q1g = U->face[i].q1();
    const Ordinal q2g = U->face[i].q2();
    dMatrix *im1, *im2;
    im1 = get_interpolation_matrix( q1, q1g, Interp::G2GL);  // to, from
    im2 = get_interpolation_matrix( q2, q2g, Interp::G2GL);  // to, from
    matrices.push_back(im1);
    matrices.push_back(im2);
  }
  return matrices;
}

} // namespace DGM
