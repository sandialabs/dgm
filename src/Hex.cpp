/** \file Hex.cpp
    \brief Hex Element implementation
    \author Scott Collis

    Hex is a eight node hexahedral element that supports both affine and
    curved sided isoparametric mappings from the master element to the
    physical space element.

    Currently, the only non-affine elements that are supported are straight-
    sided.

    \todo Implement and test curved faces for Hex elements
*/

// System includes
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
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
#include "Hex.hpp"
#include "Comm.hpp"
#include "Utils.hpp"
#include "String.hpp"
#include "Array.hpp"
#include "Polylib.tpp"
#include "Utilities.hpp"

#ifdef DGM_USE_GENERAL_GHOSTING
/// register class for serialization of polymorphic types
BOOST_CLASS_EXPORT_GUID(DGM::Hex, "DGM::Hex");
#endif

namespace DGM {

// define static storage

BasisDB Hex::bdb;                 // define Basis database
Hex::GeometryDB Hex::gdb("Hex "); // define Geometry database
IMDB Hex::imdb;                   // define Interpolation Matrix database
DerivDB Hex::ddb;                 // define Derivative Matrix database

Ordinal Hex::Qmax = 0;
Ordinal Hex::Lmax = 0;
dVector Hex::g1_wk;
dVector Hex::g2_wk;
dVector Hex::g3_wk;

dVector Hex::n1_wk;
dVector Hex::n2_wk;
dVector Hex::n3_wk;
dVector Hex::Lwk;
dVector Hex::Lwk2;

bool Hex::first_warn(true);

const int Hex::v_num[6][4] = {{0,1,2,3},{0,1,5,4},{1,2,6,5},
                              {3,2,6,7},{0,3,7,4},{4,5,6,7}};

const int Hex::e_num[6][4] = {{0,1,2,3},{0,5,8,4},{1,6,9,5},
                              {2,6,10,7},{3,7,11,4},{8,9,10,11}};

/// Primary Constructor
/*! \param[in] ID    - Local element id
    \param[in] P     - Polynomial order
    \param[in] Q     - Quadrature order
    \param[in] X     - Vector of points defining the vertices
    \todo Need to add a way to turn on VMS */
Hex::Hex(const Ordinal ID, const Ordinal P, const Ordinal Q,
         const vector<Point> &X) : BaseHex(ID,Basis::Ortho) {
  nVerts(8);
  nEdges(12);
  nFaces(6);
  nSides(6);
  pOrder(P);
  L(P+1);
  nModes(L()*L()*L());

  // Setup VMS method (this should not be here! [SSC])
  if (VMS_Lc() != 0) {
    string fname, buffer;
    fname = "vms.info";
    //cout << "fname ==> " << fname <<endl;
    ifstream vms(fname.c_str());
    if (vms) {
      int lcl;
      getline(vms,buffer);
      if (!(vms>>lcl)) error("Cannot read VMS partition information");
      VMS_Lc(lcl);
      // DGM::Comm::World->cout() << "VMS_Lc = " << VMS_Lc() <<endl;
      if ( VMS_Lc() >= L() ) {
        DGM::Comm::World->cerr() << "Illegal VMS partition value" << endl;
        DGM::Comm::World->exit(DGM::FAILURE);
      }
    }
  }

  // you might want to use different quadrature order in a, b, and c
  qa = qb = qc = Q;
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
  u.resize(qtot);  u=0;
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
    Face fac(i,this,nModes(),qa-1,qa-1,false);  // make qedg1=qedg2 for now
    face.push_back(fac);
    side.push_back(&(face[i]));
  }
}

/// Copy constructor -- This should not allocate new space for P, M, etc.
Hex::Hex(const Hex *E) {
  // cout << "Hex copy constructor for Eid = " << E->gid() << endl;

  // allocate storage for solution at quadrature points
  u.resize(E->u.size()); u=0;

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
Hex::~Hex() { }

/// Retrieves a basis from the basis database
/** If the basis is not in the database, makes a new basis and adds to
    database \todo Switch to a non-string key like the interpolation
    matrix. */
Basis* Hex::get_basis(const int der=0) const {
  // cout << "Hex::get_basis" << endl;
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

/// Gets the mass matrix for this Hex
void Hex::get_mass_matrix() {
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
      DGM::Comm::World->cerr()<< "Hex: Cholesky_factor() failed." << endl;
      DGM::Comm::World->exit(DGM::FAILURE);
    }
#else
    if (LU_factor(M->mat, M->pivots) !=0) {
      DGM::Comm::World->cerr()<< "Hex: LU_factor() failed." << endl;
      DGM::Comm::World->exit(DGM::FAILURE);
    }
#endif
  }  else {
#ifdef DGM_BASIS_NORM
    // This only works when the Jacobian is constant
    MinfoPtr t(new Minfo);
    M.reset( new Minfo );
    M->mat.resize(1,nModes());
    for (Ordinal j=0; j<nModes(); j++) M->mat[0][j] = 1.0/geom->J[0];
#else
    M.reset( new Minfo );
    M->mat.resize(1,nModes());
    dVector f(qtot);
    for (Ordinal m=0; m<nModes(); m++) {
      fill( psi->mode[m], f );
      M->mat[0][m] = inner_product(f,m);
    }
    // cout << "Mass matrix for elmt " << gid() << endl << M->mat << endl;
    for (Ordinal j=0; j<nModes(); j++) M->mat[0][j] = 1.0/M->mat[0][j];
#endif
  }
}

/// Resets the mass matrix using a weighted mass matrix
/** \warning Might be dangerous to reset the mass matrix to this new value. */
void Hex::get_mass_matrix(const dVector &x) {
  //cout << "Hex::get_mass_matrix(x) for element " << gid() << endl;
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

/// Solves (LU factors) the mass matrix for a single RHS
void Hex::solve_mass_matrix(dVector &fh) const {
  if (curve.get() || full_mass) {
    // cout << "Hex::solve_mass_matrix(dVector)" << endl;
#ifdef DGM_CHOLESKY_MASS_MATRIX
    Cholesky_solve(M->mat, fh);
#else
    LU_solve( M->mat, M->pivots, fh);
#endif
  } else {
    for (Ordinal i=0; i<nModes(); i++) fh[i] *= M->mat[0][i];
  }
}

/// Solves (LU factors) the mass matrix for multiple RHS
void Hex::solve_mass_matrix(dMatrix &fh) {
  if (curve.get() || full_mass) {
    // cout << "Hex::solve_mass_matrix(dMatrix)" << endl;
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

/// Computes the normal gradient on a supplied side
void Hex::normal_times_gradient_side(const dVector &f, const int sid,
                                     dVector &fssum ) const {
  dVector dfs( side[sid]->qtot() );
  dVector dfx(qtot);
  dVector dfy(qtot);
  dVector dfz(qtot);
  assert ( f.size() == dfx.size() );
  assert ( fssum.size() == (dVector::size_type)side[sid]->qtot() );

  gradient( f, dfx, dfy, dfz);
  load_side( dfx, sid, dfs );
  dvmul(this->side[sid]->nx(), dfs);
  fssum = dfs;
  load_side( dfy, sid, dfs );
  dvmul(this->side[sid]->ny(), dfs);
  fssum += dfs;
  load_side( dfz, sid, dfs );
  dvmul(this->side[sid]->nz(), dfs);
  fssum += dfs;
}

/// Computes a mass matrix but does not factor it
void Hex::get_local_mass_matrix(const dVector &factor) {
  //cout << "Hex::get_local_mass_matrix(x) for element " << gid() << endl;
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

/// Computes the local derivative matrix
void Hex::get_local_derivative_matrix() {
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

/// Computes the local derivative matrix
void Hex::get_local_derivative_matrix(const dVector &factor) {
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

/// Computes the local Laplace matrix
void Hex::get_local_laplace_matrix() {
  // cout << "Hex::get_local_laplace_matrix for element " << gid() << endl;
  DDloc.reset( new Minfo );
  DDloc->mat.resize(nModes(),nModes());
  //DDloc->pivots.resize(nModes()); // not needed
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

/// Computes the local Laplace matrix
void Hex::get_local_laplace_matrix(const dVector &factor) {
  // cout << "Hex::get_local_laplace_matrix for element " << gid() << endl;
  DDloc.reset( new Minfo );
  DDloc->mat.resize(nModes(),nModes());
  //DDloc->pivots.resize(nModes()); // not needed
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
void Hex::fill(string function_string, Operation operation) {
  state = Physical;
  parser_init();
  Parser::VectorFunction f("x", "y", "z", "t", function_string );
  f.evaluate( C->x, C->y, C->z, u, 0.0, convert(operation) );
  state = Physical;
}

/// Fill element with a mode
void Hex::fill(Mode &v) {
  // cout << "Hex::fill(Mode &)" << endl;
  dArray U(u,qa,qb,qc);
  for (Ordinal i=0; i<qa; i++)
    for (Ordinal j=0; j<qb; j++)
      for (Ordinal k=0; k<qc; k++)
        U[i][j][k] = v.a[i] * v.b[j] * v.c[k];
  state = Physical;
}

/// Fill a vector with a mode
void Hex::fill(Mode &v, dVector &f) const {
  dArray F(f,qa,qb,qc);
  for (Ordinal i=0; i<qa; i++)
    for (Ordinal j=0; j<qb; j++)
      for (Ordinal k=0; k<qc; k++)
        F[i][j][k] = v.a[i] * v.b[j] * v.c[k];
}

/// Fill element with a random polynomial
void Hex::random() {
  //cout << "Hex::random()" << endl;
  state = Transform;
  for (Ordinal i=0; i<nModes(); i++) uh[i] = Element::random(-one,one);
  backward_transform();
}

/// Set the modes of an element
void Hex::set(const dVector &fh, const Ordinal nModes2) {
  // cout << "Hex::set(const dVector &, const int)" << endl;
  Ordinal L2 = static_cast<Ordinal>(round(pow(static_cast<Scalar>(nModes2),
                                    1.0/3.0)));
  if ( L2*L2*L2 != nModes2 ) {
    cout << "Hex::set L2 = " << L2 << ", L = " << L() << ", nModes2 = "
         << nModes2 << ", nModes = " << nModes() << endl;
    throw DGM::exception("There is a logic error in Hex::set(...)");
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
void Hex::inner_product() {
  inner_product(u, uh);
  state = Transform;
}

/// Computes the inner product of the supplied vector against the Basis
Scalar Hex::inner_product(dVector &f, const Ordinal m) const {
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
  const Ordinal row = m/qc;
  const Ordinal col = m%L();
  const Ordinal   a = row/L();
  const Ordinal   b = row%L();
  F.alias (f,  qa,  qb*qc );
  dVector V ( Lwk,  qb*qc );
  dMatrix H ( Lwk,  qb, qc); 
  dVector Ha( Lwk2, qc); 

  tmvmult (F, Ba.row(a), V ); 
  tmvmult (H, Bb.row(b), Ha); 
  const Scalar M = dot(Bc.row(col), Ha); 
  return M;
}

/// Computes the inner product of the supplied vector against the Basis
void Hex::inner_product(dVector &f, dVector &fh) const {
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
  const dMatrix &Ba = psi->Ba;
  const dMatrix &Bb = psi->Bb;
  const dMatrix &Bc = psi->Bc;
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
void Hex::forward_transform() {
#ifdef DGM_HEX_TIMERS
  static FunctionTimer T("Hex::forward_transform");
  FunctionSentry sentry(T);
#endif
  if (state == Transform) {
    cerr << "Hex::transform -- already in transform space"<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  forward_transform(u,uh);
  state = Transform;
}

/// Transform the supplied data to polynomial space
void Hex::forward_transform(dVector &f, dVector &fh) const {
  inner_product(f,fh);
  solve_mass_matrix(fh);
}

/// Transform using another Elements mass matrix (dangerous)
void Hex::forward_transform(Element *F, Element *) {
  // cout << "Hex::forward_transform(*F,*)" << endl;
  if (state == Transform) {
    cerr << "Hex::transform -- already in transform space"<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  inner_product(u,uh);
  F->solve_mass_matrix(uh);  // Use element F's Mass matrix
  state = Transform;
}

/// Return Element to physical space
void Hex::backward_transform() {
#ifdef DGM_HEX_TIMERS
  static FunctionTimer T("Hex::backward_transform");
  FunctionSentry sentry(T);
#endif
  if (state == Physical) {
    cerr << "Hex::transform_to_physical -- already in physical space"<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  backward_transform( uh, u );
  state = Physical;
}

/// Transform supplied data to physical space on this Element
void Hex::backward_transform(dVector &fh, dVector &f) const {
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
void Hex::get_side(const dVector &from, const Ordinal sid,
                   dVector &to ) const {
  const dArray F(from,qa,qb,qc);
  switch(sid) {
  case 0: {
    dMatrix T(to, qa, qb);
    const Ordinal k = 0;
    for (Ordinal i=0; i<qa; i++)
      for (Ordinal j=0; j<qb; j++)
        T(i,j) = F(i,j,k);
    }
    break;
  case 1: {
    dMatrix T(to, qa, qc);
    const Ordinal j = 0;
    for (Ordinal i=0; i<qa; i++)
      for (Ordinal k=0; k<qc; k++)
        T(i,k) = F(i,j,k);
    }
    break;
  case 2: {
    dMatrix T(to, qb, qc);
    const Ordinal i = qa-1;
    for (Ordinal j=0; j<qb; j++)
      for (Ordinal k=0; k<qc; k++)
        T(j,k)= F(i,j,k);
    }
    break;
  case 3: {
    dMatrix T(to, qa, qc);
    const Ordinal j = qb-1;
    for (Ordinal i=0; i<qa; i++)
      for (Ordinal k=0; k<qc; k++)
        T(i,k) = F(i,j,k);
    }
    break;
  case 4: {
    dMatrix T(to, qb, qc);
    const Ordinal i = 0;
    for (Ordinal j=0; j<qb; j++)
      for (Ordinal k=0; k<qc; k++)
        T(j,k) = F(i,j,k);
    }
    break;
  case 5: {
    dMatrix T(to, qa, qb);
    const Ordinal k = qc-1;
    for (Ordinal i=0; i<qa; i++)
      for (Ordinal j=0; j<qb; j++)
        T(i,j) = F(i,j,k);
    }
    break;
  default:
    cerr << "Hex::get_side -- unknown edge" << endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
}

/// Makes an interpolation matrix
void Hex::make_interpolation_matrix( const Ordinal q1, const Ordinal q2,
                                     const Interp::Type interp,
                                     dMatrix &im ) {
  im.resize(q1,q2);
  dVector z1(q1), z2(q2), w1(q1), w2(q2);
  switch(interp){
  case(Interp::GL2G):
    zwgll(z2,w2);              // Gauss-Lobatto-Legendre
    zwgl (z1,w1);              // Gauss-Legendre
    igllm(im,z2,z1);           // Interpolation matrix
    break;
  case(Interp::G2GL):
    zwgl (z2,w2);              // Gauss-Legendre
    zwgll(z1,w1);              // Gauss-Lobatto-Legendre
    iglm(im,z2,z1);            // Interpolation matrix
    break;
  default:
    cerr << "Hex::make_interpolation_matrix - Invalid interpolation type"
         << endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
}

/// Returns an interpolation matrix (making one if needed)
dMatrix* Hex::get_interpolation_matrix( const Ordinal q1, const Ordinal q2,
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
void Hex::load_side(const dVector &f, const Ordinal side_id,
                    dVector &f_side) const {
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
void Hex::fill_sides(const dVector &f) {
  dVector wkab, wkac, wkbc, wk[6];
  wkab.alias(g1_wk,qa*qb);
  wkac.alias(g2_wk,qa*qc);
  wkbc.alias(g3_wk,qb*qc);
  wk[0].alias(wkab); wk[1].alias(wkac); wk[2].alias(wkbc);
  wk[3].alias(wkac); wk[4].alias(wkbc); wk[5].alias(wkab);
  for (Ordinal i=0; i<nSides(); i++) {
    get_side(f, i, wk[i]);
    interpolate_to_side(i, wk[i], side[i]->u );
  }
#ifdef DGM_ALLOW_HANGING_NODES
  push_to_subsides();
#endif
}

/// Fill Element Sides with a flux vector (3-d flux version)
void Hex::fill_sides(const dVector &fx, const dVector &fy, const dVector &fz) {
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
#ifdef DGM_ALLOW_HANGING_NODES
  push_to_subsides();
#endif
}

/// Compute coordinates of quadrature points
void Hex::get_coordinates() {
  // cout << "Hex::get_coordinates for element " << gid() << endl;
  if (curve.get()) {
    // Only straight edge affine and non-affine elements are supported.
    // In both cases, get_straight_coordinates() can be used.
    // get_curved_coordinates();
    get_straight_coordinates();
  }
  else {
    get_straight_coordinates();
  }
}
//#define DGM_HEX_USE_MATRIX_STORAGE

/// Compute coordinates for a straight-sided Element
void Hex::get_straight_coordinates() {
  C.reset( new Coord(qtot) ); *C = 0;
#ifdef DGM_HEX_USE_MATRIX_STORAGE
  vector< dMatrix > phi(qc);
  cout << "contructed phi" << endl;
  for (Ordinal k=0; k<qc; k++) {
    cout << k << endl;
    phi[k].resize(qa,qb);
  }
#else
  Scalar ***phi;
  phi = new Scalar**[qa];
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
#ifndef DGM_HEX_USE_MATRIX_STORAGE
  // make sure to delete tmp storage
  for (Ordinal i=0; i<qa; i++) {
    for (Ordinal j=0; j<qb; j++)
      delete[] phi[i][j];
    delete[] phi[i];
  }
  delete[] phi;
#endif
}

//#undef DGM_HEX_USE_MATRIX_STORAGE

/// Compute the geometric factors
void Hex::compute_geometry() {
  // cout << "Hex::compute_geometry for element " << gid() << endl;
  geom.reset( new Geometry( lid(), 3, nVerts(), qtot ) );
  if (curve.get())
    compute_curved_geometry();
  else
    compute_straight_geometry();
  measure(compute_measure());
#ifdef DGM_USE_GEOM_DB
  gdb.add(geom);
#endif
}

/// Determine if the element is affine
bool Hex::is_affine() const {
  // cout << "Hex::is_affine for element " << gid() << endl;

  // compute coordinate differences
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
   // approx_equal(xr,(vert[6]->x - vert[7]->x),REL,ABS) &&
      approx_equal(xs,(vert[7]->x - vert[4]->x),REL,ABS) &&
      approx_equal(xt,(vert[7]->x - vert[3]->x),REL,ABS) &&
   // approx_equal(yr,(vert[6]->y - vert[7]->y),REL,ABS) &&
      approx_equal(ys,(vert[7]->y - vert[4]->y),REL,ABS) &&
      approx_equal(yt,(vert[7]->y - vert[3]->y),REL,ABS) &&
   // approx_equal(zr,(vert[6]->z - vert[7]->z),REL,ABS) &&
      approx_equal(zs,(vert[7]->z - vert[4]->z),REL,ABS) &&
      approx_equal(zt,(vert[7]->z - vert[3]->z),REL,ABS) &&
   // approx_equal(xr,(vert[1]->x - vert[0]->x),REL,ABS) &&
      approx_equal(xs,(vert[2]->x - vert[1]->x),REL,ABS) &&
      approx_equal(xt,(vert[5]->x - vert[1]->x),REL,ABS) &&
   // approx_equal(yr,(vert[1]->y - vert[0]->y),REL,ABS) &&
      approx_equal(ys,(vert[2]->y - vert[1]->y),REL,ABS) &&
      approx_equal(yt,(vert[5]->y - vert[1]->y),REL,ABS) &&
   // approx_equal(zr,(vert[1]->z - vert[0]->z),REL,ABS) &&
      approx_equal(zs,(vert[2]->z - vert[1]->z),REL,ABS) &&
      approx_equal(zt,(vert[5]->z - vert[1]->z),REL,ABS) );
  return result;
}

/// Compute the geometric factors
/** This version is only correct for affine elements (use curved_geometry
    otherwise).  It now throws an error if you try to use this method on a
    nonaffine element.

    The Jacobian matrix is given by
    \f[\boldsymbol{J} =
       \begin{bmatrix}
         x_{,r} && x_{,s} && x_{,t} \\
         y_{,r} && y_{,s} && y_{,t} \\
         z_{,r} && z_{,s} && z_{,t} \\
       \end{bmatrix}
    \f]
    This particular version takes advantage of the fact that the Jacobian
    matrix is constant for an affine element.
*/
void Hex::compute_straight_geometry() {
  // cout << "Hex::compute_straight_geometry for element " << gid() << endl;

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
   // !CMC::approx_equal(xr,(vert[6]->x - vert[7]->x)*pt5,REL,ABS) ||
      !CMC::approx_equal(xs,(vert[7]->x - vert[4]->x)*pt5,REL,ABS) ||
      !CMC::approx_equal(xt,(vert[7]->x - vert[3]->x)*pt5,REL,ABS) ||
   // !CMC::approx_equal(yr,(vert[6]->y - vert[7]->y)*pt5,REL,ABS) ||
      !CMC::approx_equal(ys,(vert[7]->y - vert[4]->y)*pt5,REL,ABS) ||
      !CMC::approx_equal(yt,(vert[7]->y - vert[3]->y)*pt5,REL,ABS) ||
   // !CMC::approx_equal(zr,(vert[6]->z - vert[7]->z)*pt5,REL,ABS) ||
      !CMC::approx_equal(zs,(vert[7]->z - vert[4]->z)*pt5,REL,ABS) ||
      !CMC::approx_equal(zt,(vert[7]->z - vert[3]->z)*pt5,REL,ABS) ||
   // !CMC::approx_equal(xr,(vert[1]->x - vert[0]->x)*pt5,REL,ABS) ||
      !CMC::approx_equal(xs,(vert[2]->x - vert[1]->x)*pt5,REL,ABS) ||
      !CMC::approx_equal(xt,(vert[5]->x - vert[1]->x)*pt5,REL,ABS) ||
   // !CMC::approx_equal(yr,(vert[1]->y - vert[0]->y)*pt5,REL,ABS) ||
      !CMC::approx_equal(ys,(vert[2]->y - vert[1]->y)*pt5,REL,ABS) ||
      !CMC::approx_equal(yt,(vert[5]->y - vert[1]->y)*pt5,REL,ABS) ||
   // !CMC::approx_equal(zr,(vert[1]->z - vert[0]->z)*pt5,REL,ABS) ||
      !CMC::approx_equal(zs,(vert[2]->z - vert[1]->z)*pt5,REL,ABS) ||
      !CMC::approx_equal(zt,(vert[5]->z - vert[1]->z)*pt5,REL,ABS) ) {
    cerr << "ERROR:  Hex::compute_straight_geometry()" << endl
         << "  Jacobian is not constant for Element " << gid() << endl;
    cout << "  xr = " << xr << " : " << (vert[6]->x - vert[7]->x)*pt5 << " : "
         <<CMC::approx_equal(xr,(vert[6]->x - vert[7]->x)*pt5,REL,ABS)<<endl;
    cout << "  xs = " << xs << " : " << (vert[6]->x - vert[5]->x)*pt5 << " : "
         <<CMC::approx_equal(xs,(vert[6]->x - vert[5]->x)*pt5,REL,ABS) <<endl;
    cout << "  xt = " << xt << " : " << (vert[6]->x - vert[2]->x)*pt5 << " : "
         <<CMC::approx_equal(xt,(vert[6]->x - vert[2]->x)*pt5,REL,ABS)<<endl;
    cout << "  yr = " << yr << " : " << (vert[6]->y - vert[7]->y)*pt5 << " : "
         <<CMC::approx_equal(yr,(vert[6]->y - vert[7]->y)*pt5,REL,ABS)<<endl;
    cout << "  ys = " << ys << " : " << (vert[6]->y - vert[5]->y)*pt5 << " : "
         <<CMC::approx_equal(ys,(vert[6]->y - vert[5]->y)*pt5,REL,ABS)<<endl;
    cout << "  yt = " << yt << " : " << (vert[6]->y - vert[2]->y)*pt5 << " : "
         <<CMC::approx_equal(yt,(vert[6]->y - vert[2]->y)*pt5,REL,ABS)<<endl;
    cout << "  zr = " << zr << " : " << (vert[6]->z - vert[7]->z)*pt5 << " : "
       <<endl;
    cout << "  zs = " << zs << " : " << (vert[6]->z - vert[5]->z)*pt5 << " : "
         <<endl;
    cout << "  zt = " << zt << " : " << (vert[6]->z - vert[2]->z)*pt5 << " : "
         <<endl;
    cout << "  xr = " << xr << " : " << (vert[6]->x - vert[7]->x)*pt5 << " : "
         <<endl;
    cout << "  xs = " << xs << " : " << (vert[7]->x - vert[4]->x)*pt5 << " : "
         <<endl;
    cout << "  xt = " << xt << " : " << (vert[7]->x - vert[3]->x)*pt5 << " : "
         <<endl;
    cout << "  yr = " << yr << " : " << (vert[6]->y - vert[7]->y)*pt5 << " : "
         <<endl;
    cout << "  ys = " << ys << " : " << (vert[7]->y - vert[4]->y)*pt5 << " : "
         <<endl;
    cout << "  yt = " << yt << " : " << (vert[7]->y - vert[3]->y)*pt5 << " : "
         <<endl;
    cout << "  zr = " << zr << " : " << (vert[6]->z - vert[7]->z)*pt5 << " : "
         <<endl;
    cout << "  zs = " << zs << " : " << (vert[7]->z - vert[4]->z)*pt5 << " : "
         <<endl;
    cout << "  zt = " << zt << " : " << (vert[7]->z - vert[3]->z)*pt5 << " : "
         <<endl;
    cout << "  xr = " << xr << " : " << (vert[1]->x - vert[0]->x)*pt5 << " : "
         <<endl;
    cout << "  xs = " << xs << " : " << (vert[2]->x - vert[1]->x)*pt5 << " : "
         <<endl;
    cout << "  xt = " << xt << " : " << (vert[5]->x - vert[1]->x)*pt5 << " : "
         <<endl;
    cout << "  yr = " << yr << " : " << (vert[1]->y - vert[0]->y)*pt5 << " : "
         <<endl;
    cout << "  ys = " << ys << " : " << (vert[2]->y - vert[1]->y)*pt5 << " : "
         <<endl;
    cout << "  yt = " << yt << " : " << (vert[5]->y - vert[1]->y)*pt5 << " : "
         <<endl;
    cout << "  zr = " << zr << " : " << (vert[1]->z - vert[0]->z)*pt5 << " : "
         <<endl;
    cout << "  zs = " << zs << " : " << (vert[2]->z - vert[1]->z)*pt5 << " : "
         <<endl;
    cout << "  zt = " << zt << " : " << (vert[5]->z - vert[1]->z)*pt5 << " : "
         <<endl;
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

/// Compute the stability metrics for timestep size calculations.
Element::StabMetrics Hex::compute_metrics() {
  return compute_metrics_3d_tensor_prod();
}

/// Returns the side quadrature orders
void Hex::side_to_size(Ordinal &q1, Ordinal &q2, const Ordinal side) const {
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
void Hex::side2size(const Ordinal side, iVector &q) const {
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
Ordinal Hex::side2size(const Ordinal side) const {
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
void Hex::interpolate_to_side( const Ordinal sid, const dVector &from,
                               dVector &to) const {
  Ordinal q1=0, q2=0;

  // to
  const Ordinal q1g = face[sid].q1();
  const Ordinal q2g = face[sid].q2();

  // from
  side_to_size(q1, q2, sid);

  const dMatrix *const im1 =
      get_interpolation_matrix( q1g, q1, Interp::GL2G);  // to, from
  const dMatrix *const im2 =
      get_interpolation_matrix( q2g, q2, Interp::GL2G);  // to, from

  dMatrix From, To, wk;
  wk.exclusive_alias(n1_wk,q1g,q2);
  From.alias( const_cast<dVector&>(from), q1, q2 );
  To.alias( to, q1g, q2g );

  matmult( *im1, From, wk );
  matmult( wk, 'T', *im2, To );
}

/// Interpolate from side to interior quadrature
void Hex::interpolate_from_side( const Ordinal sid, const dVector &from,
                                 dVector &to) const {
  Ordinal q1=0, q2=0;

  // from
  Ordinal q1g = face[sid].q1();
  Ordinal q2g = face[sid].q2();

  // to
  side_to_size(q1, q2, sid);

  const dMatrix *const im1 =
        get_interpolation_matrix( q1, q1g, Interp::G2GL);  // to, from
  const dMatrix *const im2 =
        get_interpolation_matrix( q2, q2g, Interp::G2GL);  // to, from

  dMatrix From, To, wk;
  wk.exclusive_alias(n1_wk,q1,q2g);             // use n1_wk storage here
  From.alias( const_cast<dVector&>(from), q1g, q2g );
  To.alias( to, q1, q2 );

  matmult( *im1, From, wk );
  matmult( wk, 'T', *im2, To );
}

/// Computes geometric factors for the Element Sides
void Hex::compute_side_geometry() {
  Ordinal q1=0, q2=0;
  sigma(0.0);

  for (Ordinal i=0; i<nFaces(); i++) {

    side_to_size(q1, q2, i);
    dVector wk;
    wk.exclusive_alias(n2_wk,q1*q2);

    const dVector *NX=0, *NY=0, *NZ=0;

    if      (0==i || 5==i) { NX = &geom->tx; NY = &geom->ty; NZ = &geom->tz; }
    else if (1==i || 3==i) { NX = &geom->sx; NY = &geom->sy; NZ = &geom->sz; }
    else if (2==i || 4==i) { NX = &geom->rx; NY = &geom->ry; NZ = &geom->rz; }
    else    error("Internal error in Hex::compute_side_geometry, bad nFaces");
    get_side(*NX,i,wk);                          // wk at Gauss-Lobatto points
    interpolate_to_side( i, wk, side[i]->nx() ); // interpolate to Gauss
    get_side(*NY,i,wk);
    interpolate_to_side( i, wk, side[i]->ny() );
    get_side(*NZ,i,wk);
    interpolate_to_side( i, wk, side[i]->nz() );
    if (0==i || 1==i || 4==i) {
      scale( -1.0, side[i]->nx() );
      scale( -1.0, side[i]->ny() );
      scale( -1.0, side[i]->nz() );
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

    // Save off interior_Jcoefficients
    side[i]->J_orig().resize(side[i]->J().size());
    side[i]->J_orig()      = side[i]->J();
    side[i]->J_scale().resize(side[i]->qtot());
    side[i]->J_scale() = interior_J;

    // divide the surface Jacobian by the interior Jacobian
    dvdiv( interior_J, side[i]->J() );
    // This is done so that you can use an interior integration to perform the
    // surface integration.  For this to work you must use an interior
    // quadrature rule that includes the boundaries and you must divide the
    // side contributions by the integration weight in the other direction(s).

    // store the max ratio of side to element Jacobians
    side[i]->h_n_inv(0.0);
    for (Ordinal k=0; k<side[i]->qtot(); ++k) {
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

/// Get the coordinates on a specified side
void Hex::get_side_coordinates( const Ordinal sid, Point *pside )const {
  //cout << "Hex::get_side_coordinates()!" << endl;
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
    for(Ordinal i=0; i<face[sid].qtot(); i++) pside[i] = Point(px[i],py[i],pz[i]);
    break;
  default:
    cerr << "Hex::_side_coordinates illegal edge id." << endl;
    DGM::Comm::World->exit();
  }
}

// not ok
void Hex::forward_transform_side(dVector &f, dVector &fh) {
  cout << "Hex::forward_transform_side" << endl;
  DGM::Comm::World->exit(DGM::FAILURE);
  dVector &wa=psi->wa;
  fh.resize(L()-2);
  // subtract off vertices
  daxpy( -f[0], psi->vertMode(0).a, f );
  daxpy( -f[qa-1], psi->vertMode(1).a, f);
  // inner product
  dvmul( wa, f );
  for (Ordinal i=0; i<L()-2; i++)
    fh[i] = dot( psi->edgeMode(0,i).a, f );
  if (L()-2) solve_1d_mass_matrix(fh);
}

// not ok
void Hex::solve_1d_mass_matrix(dVector &fh) const {
  // DGM::Comm::World->exit(DGM::FAILURE);
  Minfo M1d;
  get_1d_mass_matrix(M1d);
#ifdef DGM_CHOLESKY_MASS_MATRIX
  Cholesky_solve(M1d.mat, fh);
#else
  LU_solve(M1d.mat, M1d.pivots, fh);
#endif
}

// not ok
void Hex::get_1d_mass_matrix(Minfo &M1d) const {
  cout << "Hex::get_1d_mass_matrix(Minfo &M1d) const" << endl;
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

/// Compute a integral of supplied data, f, on specified side
Scalar Hex::compute_side_integral( dVector &f, Ordinal sid ) const {
  // cout << "Hex::compute_side_integral(dVector &, int) for Eid = "
  //      << gid() << ", Sid = " << sid << endl;
  dvmul( side[sid]->J(), f);

  // cout << " J/interior_J * f = " << endl << f << endl;

  Ordinal q1=0, q2=0;
  side_to_size(q1, q2, sid);
  const Ordinal q = q1*q2;

  dVector wk(q);
  get_side(geom->J,sid,wk);       // extract interior J on edge

  const Ordinal q1g = face[sid].q1();
  const Ordinal q2g = face[sid].q2();
  const Ordinal qsid = q1g*q2g;
  assert(qsid == face[sid].qtot());
  dVector wks(qsid);  // interior_J
  interpolate_to_side( sid, wk, wks);
  dvmul( wks, f );
  // cout << " J * f = " << endl << f << endl;

  static dVector w;
  if (w.size() != (Ordinal)qsid) {
    w.resize(qsid);
    w = 1.0;
    dMatrix W(w,q1g,q2g);
    dVector wa(q1g);
    dVector za(wks,q1g);
    zwgl(za,wa);
    for(Ordinal j=0; j<q2g; j++) {
      dSlice column(W.column(j));
      dvmul(wa, column );
    }
    dVector wb(q2g);
    dVector zb(wks,q2g);
    zwgl(zb,wb);
    for(Ordinal i=0; i<q1g; i++) {
      dVector row(W.row(i));
      dvmul(wb, row );
    }
  }
  const Scalar I = dot( f, w );
  // cout<<"Eid = " << this->id << ", Sid = " << sid << ", I = " << I << endl;
  return I;
}

/// Computes the side measure (total side area for a Hex)
Scalar Hex::compute_side_measure() const {
  Scalar result=0.0;
  for (Ordinal sid=0; sid<nSides(); sid++) {
    Ordinal qsid = side[sid]->qtot();
    dVector p(qsid);
    p = 1.0;
    result += compute_side_integral(p,sid);
  }
  return result;
}

namespace {

void inner_product (dArray h,
                    const dArray &f,
                    const dMatrix &B1,
                    const dMatrix &B2,
                    const dMatrix &B3) {
  const Ordinal f1 = f.dim1();
  const Ordinal f2 = f.dim2();
  const Ordinal f3 = f.dim3();
  const Ordinal h1 = h.dim1();
  const Ordinal h2 = h.dim2();
  const Ordinal h3 = h.dim3();
  if (static_cast<Ordinal>(B1.dim1()) != h1) abort();
  if (static_cast<Ordinal>(B1.dim2()) != f1) abort();
  if (static_cast<Ordinal>(B2.dim1()) != h2) abort();
  if (static_cast<Ordinal>(B2.dim2()) != f2) abort();
  if (static_cast<Ordinal>(B3.dim1()) != h3) abort();
  if (static_cast<Ordinal>(B3.dim2()) != f3) abort();
  for (Ordinal i1=0; i1<h1; ++i1)
    for (Ordinal i2=0; i2<h2; ++i2)
      for (Ordinal i3=0; i3<h3; ++i3)
        for (Ordinal j1=0; j1<f1; ++j1)
          for (Ordinal j2=0; j2<f2; ++j2)
            for (Ordinal j3=0; j3<f3; ++j3)
              h(i1,i2,i3) += f(j1,j2,j3)*B1(i1,j1)*B2(i2,j2)*B3(i3,j3);
}

void var_p_lift(dVector       &in,
                const Element *const U,
                const Side    *const S,
                const Basis   *psi,
                const Ordinal e,
                const char     dir)
{
  const Ordinal L = psi->Ba.rows();
  const Ordinal qa = psi->Ba.cols();
  const Ordinal qb = psi->Bb.cols();
  const Ordinal qc = psi->Bc.cols();
  dVector fh(L*L*L); fh=0;
  dMatrix Fh(fh,L*L,L);
  dArray  FH(fh,L,L,L);
  const Side* Us = U->side[e];
  const Face* Fs = dynamic_cast<const Face*>(S);
  if (!Fs&&S)error("dynamic_cast failed in Hex::var_p_lift");
  const Ordinal q1 = Us->q1();
  const Ordinal q2 = Us->q2();
  if (Us->J().size()!=((Ordinal)(q1*q2)))
    error("Error 1 Hex::var_p_lift");
  if (Us->u.size()!=((Ordinal)(q1*q2)))
    error("Error 2 Hex::var_p_lift");
  dVector w1(  q1);
  dVector w2(  q2);
  dMatrix B1(L,q2);
  dMatrix B2(L,q1);
  {
    dVector t1(q1);
    dVector t2(q2);
    zwgl(t1,w1);
    zwgl(t2,w2);
    Basis::make_Legendre(0,L,q1,t1,B1);
    Basis::make_Legendre(0,L,q2,t2,B2);
  }
  for (Ordinal i=0; i<q1*q2; ++i) if (Us->J()[i]<.000001) abort();
  for (Ordinal i=0; i<q1   ; ++i) if (     w1[i]<.000001) abort();
  for (Ordinal i=0; i<q2   ; ++i) if (     w2[i]<.000001) abort();

  dVector f(q1*q2);
  dMatrix F(f,q1,q2);
  if (Fs) dvsub (Fs->u, Us->u, f);
  else              f = Us->u;
  if      (dir == 'x') dvmul (Us->nx(), f);
  else if (dir == 'y') dvmul (Us->ny(), f);
  else if (dir == 'z') dvmul (Us->nz(), f);
  for (Ordinal i=0; i<q1; i++)
    for (Ordinal j=0; j<q2; j++)
      F(i,j) *= w1(i)*w2(j);
#ifdef DGM_SIDE_FLUX_TO_VOLUME
  dvmul (Us->J_orig(), f);
#endif
  dArray  G;
  const dMatrix *Ba=0, *Bb=0, *Bc=0;
  switch (e) {
  case 0 :
    G.resize(q1,q2,qc); G=0;
    for (Ordinal i=0;i<q1;++i) for (Ordinal j=0;j<q2;++j) G(i,j,0) = F(i,j);
    Ba = &B2; Bb = &B1; Bc = &psi->Bc;
    break;
  case 1 :
    G.resize(q1,qb,q2); G=0;
    for (Ordinal i=0;i<q1;++i) for (Ordinal j=0;j<q2;++j) G(i,0,j) = F(i,j);
    Ba = &B2; Bb = &psi->Bb; Bc = &B1;
    break;
  case 2 :
    G.resize(qa,q1,q2); G=0;
    for (Ordinal i=0;i<q1;++i) for (Ordinal j=0;j<q2;++j) G(qa-1,i,j) = F(i,j);
    Ba = &psi->Ba; Bb = &B2; Bc = &B1;
    break;
  case 3 :
    G.resize(q1,qb,q2); G=0;
    for (Ordinal i=0;i<q1;++i) for (Ordinal j=0;j<q2;++j) G(i,qb-1,j) = F(i,j);
    Ba = &B2; Bb = &psi->Bb; Bc = &B1;
    break;
  case 4 :
    G.resize(qa,q1,q2); G=0;
    for (Ordinal i=0;i<q1;++i) for (Ordinal j=0;j<q2;++j) G(0,i,j) = F(i,j);
    Ba = &psi->Ba; Bb = &B2; Bc = &B1;
    break;
  case 5 :
    G.resize(q1,q2,qc); G=0;
    for (Ordinal i=0;i<q1;++i) for (Ordinal j=0;j<q2;++j) G(i,j,qc-1) = F(i,j);
    Ba = &B2; Bb = &B1; Bc = &psi->Bc;
    break;
  }
  dVector h(   L* L* L); h=0;
  dArray  H(h, L, L, L);
  inner_product(H, G, *Ba, *Bb, *Bc);
  for (Ordinal i=0; i<L*L*L; ++i) fh(i) += h(i);

  dVector In(qa*qb*qc); In=0;
  U->backward_transform(fh, In);
  for (Ordinal i=0; i<qa*qb*qc; ++i) in[i] += In[i];
}

}  // anonymous namespace

void Hex::get_flux(dVector &fi,
                   const int sid,
                   const Ordinal qabc,
                   const Element *const F,
                   const char dir) const {
    dVector f;
    f. alias(g1_wk, side[sid]->qtot());
    fi.alias(g2_wk, qabc);
    if (F) dvsub( F->side[sid]->u, side[sid]->u, f );
    else         f = side[sid]->u;
    dvmul( side[sid]->J(), f);
    if      (dir == 'x') dvmul( side[sid]->nx(), f );
    else if (dir == 'y') dvmul( side[sid]->ny(), f );
    else if (dir == 'z') dvmul( side[sid]->nz(), f );
    interpolate_from_side( sid, f, fi );
}

/// Computes the surface term (lifted) for a DG method
void Hex::local_lift(dVector &in,
                     const Element *const F,
                     const Ordinal side,
                     const Scalar *W,
                     const char dir) const {
#ifdef DGM_SIDE_FLUX_TO_VOLUME
  static const bool sum_to_volume=true;
#else
  static const bool sum_to_volume=false;
#endif
  const Element *const U = this;

  dVector fi;
  dMatrix In;
  switch (side) {
  case 0: {
    if (qa*qb < U->side[side]->qtot() && sum_to_volume) {
      const Side *s = F ?  F->side[side] : 0 ;
      var_p_lift(in, U, s, psi, side, dir);
    } else {
      get_flux(fi, 0, qa*qb, F, dir);
      In.alias(in,qa*qb,qc);
      daxpy( W[0], fi, In.column(0) );
    }
  }
  break;
  case 1: {
    if (qa*qb < F->side[side]->qtot() && sum_to_volume) {
      const Side *s = F ?  F->side[side] : 0 ;
      var_p_lift(in, F, s, psi, side, dir);
    } else {
      get_flux(fi, 1, qa*qc, F, dir);
      dMatrix Fi; Fi.alias(fi, qa, qc);
      for (Ordinal i=0; i<qa; i++) {
        In.alias(in, i*qb*qc, qb, qc);
        dVector Fi_row(Fi.row(i));
        dVector In_row(In.row(0));
        daxpy( W[1], Fi_row, In_row );
      }
    }
  }
  break;
  case 2: {
    if (qa*qb < F->side[side]->qtot() && sum_to_volume) {
      const Side *s = F ?  F->side[side] : 0 ;
      var_p_lift(in, F, s, psi, side, dir);
    } else {
      get_flux(fi, 2, qb*qc, F, dir);
      In.alias(in,qa,qb*qc);
      dVector In_row_qa(In.row(qa-1));
      daxpy( W[2], fi, In_row_qa );
    }
  }
  break;
  case 3: {
    if (qa*qb < F->side[side]->qtot() && sum_to_volume) {
      const Side *s = F ?  F->side[side] : 0 ;
      var_p_lift(in, F, s, psi, side, dir);
    } else {
      get_flux(fi, 3, qa*qc, F, dir);
      dMatrix Fi; Fi.alias(fi, qa, qc);
      for (Ordinal i=0; i<qa; i++) {
        In.alias(in, i*qb*qc, qb, qc);
        dVector Fi_row(Fi.row(i));
        dVector In_row(In.row(qb-1));
        daxpy( W[3], Fi_row, In_row );
      }
    }
  }
  break;
  case 4: {
    if (qa*qb < F->side[side]->qtot() && sum_to_volume) {
      const Side *s = F ?  F->side[side] : 0 ;
      var_p_lift(in, F, s, psi, side, dir);
    } else {
      get_flux(fi, 4, qb*qc, F, dir);
      In.alias(in,qa,qb*qc);
      dVector In_row_0(In.row(0));
      daxpy( W[4], fi, In_row_0 );
    }
  }
  break;
  case 5: {
    if (qa*qb < F->side[side]->qtot() && sum_to_volume) {
      const Side *s = F ?  F->side[side] : 0 ;
      var_p_lift(in, F, s, psi, side, dir);
    } else {
      get_flux(fi, 5, qa*qb, F, dir);
      In.alias(in,qa*qb,qc);
      daxpy( W[5], fi, In.column(qc-1) );
    }
  }
  break;
  }
}

namespace {

void subside_lift (dVector       &in,
                   const Element *const el_U,
                   const Element *const el_F,
                   const Ordinal side,
                   const char     dir) {
  const Basis  *psi = el_U->psi;
  const Ordinal L  = psi->Ba.rows();
  const Ordinal qa = psi->Ba.cols();
  const Ordinal qb = psi->Bb.cols();
  const Ordinal qc = psi->Bc.cols();
  const vector<Side::Ptr> &Uss =         el_U->side[side]->subsides();
  const vector<Side::Ptr> &Fss = (el_F ? el_F->side[side]->subsides()
                                       : vector<Side::Ptr>());
  if (el_F && Uss.size() != Fss.size()) abort();
  dVector fh(L*L*L); fh=0;

  for (size_t ss=0; ss<Uss.size(); ++ss) {
    const Face* Us = dynamic_cast<Face*>(Uss[ss].get());
    if (!Us) abort();
    const Ordinal q1 = Us->q1();
    const Ordinal q2 = Us->q2();
    if (Us->J().size() != q1*q2) abort();
    if (Us->u.size()   != q1*q2) abort();
    for (Ordinal i=0; i<q1*q2; ++i) if (Us->J()[i]<.000001) abort();

    dVector f(q1*q2); f=0;
    if (el_F) dvsub (Fss[ss]->u, Us->u, f);
    else                     f = Us->u;

    if      (dir == 'x') dvmul (Us->nx(), f);
    else if (dir == 'y') dvmul (Us->ny(), f);
    else if (dir == 'z') dvmul (Us->nz(), f);

    dvmul (Uss[ss]->J_orig(), f);

    dVector h(L*L*L); h=0;
    if (1!=q1 && 1==q2) BaseHex::triangle_lift( h, f, side, Us, psi, false);
    else if (Us->subside_self_simular_to_side())   
                            BaseHex::quad_lift( h, f, side, Us, psi, false);
    else        BaseHex::non_self_simular_lift( h, f, side, Us, psi, false);
    for (Ordinal i=0; i<L*L*L; ++i) fh(i) += h(i);
  }
  dVector In(qa*qb*qc); In=0;
  el_U->backward_transform(fh, In);
  for (Ordinal i=0; i<qa*qb*qc; ++i) in[i] += In[i];
}

}  // anonymous namespace

/// Adds the surface contribution for a DG method
void Hex::lift(const Element *const F, dVector &in, const char dir) const {
  const Element *const U = this;
  const bool no_subsides[6] = {side[0]->subsides().empty(),
                               side[1]->subsides().empty(),
                               side[2]->subsides().empty(),
                               side[3]->subsides().empty(),
                               side[4]->subsides().empty(),
                               side[5]->subsides().empty()};
  const Scalar W[6] = {1.0/psi->wc[0],
                       1.0/psi->wb[0],
                       1.0/psi->wa[qa-1],
                       1.0/psi->wb[qb-1],
                       1.0/psi->wa[0],
                       1.0/psi->wc[qc-1]};
  for (Ordinal i=0; i<6; ++i) {
    if (no_subsides[i]) local_lift  (in,  F,i,W,dir);
    else                subside_lift(in,U,F,i,  dir);
  }
}

/// Build the collocation derivative matrix
void Hex::get_derivative_matrix() {
  Dentry key(qa,qb,qc);
  DerivDB::iterator p = ddb.entry.find(key);
  if ( p == ddb.entry.end() ) {
    D.reset(new Dinfo);
    //cout << "Hex::make_derivative_matrix()" << endl;
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
/** \verbatim
    df/dx = df/dr * dr/dx + df/ds * ds/dx + df/dt * dt/dx
    df/dy = df/dr * dr/dy + df/ds * ds/dy + df/dt * dt/dy
    df/dz = df/dr * dr/dz + df/ds * ds/dz + df/dt * dt/dz
    \endverbatim
*/
void Hex::gradient( const dVector &f, dVector &fx, dVector &fy,
                    dVector &fz ) const {
  // cout << "Hex::gradient( const dVector &, dVector &, dVector &, "
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

#if 0
  const Ordinal N=fr.size();
  for (Ordinal i=0; i<N; ++i) {
    fx[i] = geom->rx[i]*fr[i] + geom->sx[i]*fs[i] + geom->tx[i]*ft[i];
    fy[i] = geom->ry[i]*fr[i] + geom->sy[i]*fs[i] + geom->ty[i]*ft[i];
    fz[i] = geom->rz[i]*fr[i] + geom->sz[i]*fs[i] + geom->tz[i]*ft[i];
  }
#else
  dvmul ( geom->rx, fr, fx);       // fx  = rx * fr
  dvvtvp( geom->sx, fs, fx, fx );  // fx += sx * fs
  dvvtvp( geom->tx, ft, fx, fx );  // fx += tx * ft

  dvmul ( geom->ry, fr, fy);       // fy  = ry * fr
  dvvtvp( geom->sy, fs, fy, fy );  // fy += sy * fs
  dvvtvp( geom->ty, ft, fy, fy );  // fy += ty * ft

  dvmul ( geom->rz, fr, fz);       // fz  = rz * fr
  dvvtvp( geom->sz, fs, fz, fz );  // fz += sz * fs
  dvvtvp( geom->tz, ft, fz, fz );  // fz += tz * ft
#endif
}

/// Compute the gradient in only one spatial direction
void Hex::gradient( const dVector &f, dVector &df, char dir) const {
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
    cerr << "Hex::gradient:  illegal direction " << dir << "." << endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
}

/// Compute the local gradient on the master element
void Hex::local_gradient( const dVector &f, dVector &fr, dVector &fs,
                          dVector &ft) const {
  // cout << "Hex::local_gradient()" << endl;

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
/** This is mainly useful for mesh diagnostics. */
void Hex::tecplot(FILE *fp) {
  int tnsf = 0;
  if (state == Transform) {
    tnsf = 1;
    backward_transform();
  }
  fprintf(fp,"ZONE T=\"Zone%lld\", I=%lld, J=%lld, K=%lld,  F=POINT\n",
          (long long)gid(),(long long)qa,(long long)qb,(long long)qc);
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
    inline Ordinal operator()(Ordinal i, Ordinal j, Ordinal k) const {
      return k+j*qc+i*qc*qb;
    }
    inline Ordinal get_qa() const { return qa; }
    inline Ordinal get_qb() const { return qb; }
    inline Ordinal get_qc() const { return qc; }
  };

}  // anonymous namespace

/// Output requested element information to a file
void Hex::binaryOutput(FILE *fp, const OutputType flag) const {
  const Ordinal Nel = (qa-1)*(qb-1)*(qc-1);  // Number of sub-elements
  if (state == Transform)
    throw DGM::exception("Hex::output called when in transform space");
  Index Q(qa,qb,qc);
  switch(flag) {
  case ParaviewBinary: {
    const uint32_t length = numeric_cast<uint32_t>(qa*qb*qc*sizeof(float));
    fwrite(&length,sizeof(uint32_t),1,fp);
    for (Ordinal k=0; k<qc; ++k) {
      for (Ordinal j=0; j<qb; ++j) {
        for (Ordinal i=0; i<qa; ++i) {
          const float tmp = u[Q(i,j,k)];
          fwrite(&tmp,sizeof(float),1,fp);
        }
      }
    }
    break;
  }
  case ParaviewCoordinates: {
    const uint32_t length = numeric_cast<uint32_t>(3*qa*qb*qc*sizeof(float));
    fwrite(&length,sizeof(uint32_t),1,fp);
    CMC::Vector<float,int> xyz(3);
    for (Ordinal k=0; k<qc; ++k) {
      for (Ordinal j=0; j<qb; ++j) {
        for (Ordinal i=0; i<qa; ++i) {
          const Ordinal q = Q(i,j,k);
          xyz[0] = C->x[q];
          xyz[1] = C->y[q];
          xyz[2] = C->z[q];
          fwrite(xyz.ptr(),sizeof(float),3,fp);
        }
      }
    }
    break;
  }
  case ParaviewConnectivity: {
    const uint32_t length = numeric_cast<uint32_t>(8*Nel*sizeof(int32_t));
    fwrite(&length,sizeof(uint32_t),1,fp);
    CMC::Vector<int32_t,int> con(8);
    for (Ordinal k=0; k<qc-1; ++k) {
      for (Ordinal i=0; i<qa-1; ++i) {
        for (Ordinal j=0; j<qb-1; ++j) {
          con[0] = numeric_cast<uint32_t>(Q(i,j,k));
          con[1] = numeric_cast<uint32_t>(Q(i+1,j,k));
          con[2] = numeric_cast<uint32_t>(Q(i+1,j,k+1));
          con[3] = numeric_cast<uint32_t>(Q(i,j,k+1));
          con[4] = numeric_cast<uint32_t>(Q(i,j+1,k));
          con[5] = numeric_cast<uint32_t>(Q(i+1,j+1,k));
          con[6] = numeric_cast<uint32_t>(Q(i+1,j+1,k+1));
          con[7] = numeric_cast<uint32_t>(Q(i,j+1,k+1));
          fwrite(con.ptr(),sizeof(int32_t),8,fp);
        }
      }
    }
    break;
  }
  case ParaviewOffsets: {
    const uint32_t length = numeric_cast<uint32_t>(Nel*sizeof(int32_t));
    fwrite(&length,sizeof(uint32_t),1,fp);
    int32_t q=8;
    for (Ordinal k=0; k<qc-1; ++k) {
      for (Ordinal j=0; j<qb-1; ++j) {
        for (Ordinal i=0; i<qa-1; ++i) {
          fwrite(&q,sizeof(int32_t),1,fp);
          q+=8;
        }
      }
    }
    break;
  }
  case ParaviewTypes: {
    const uint32_t length = numeric_cast<uint32_t>(Nel*sizeof(uint8_t));
    fwrite(&length,sizeof(uint32_t),1,fp);
    const uint8_t t=VTK_HEXAHEDRON;
    for (Ordinal k=0; k<qc-1; ++k) {
      for (Ordinal j=0; j<qb-1; ++j) {
        for (Ordinal i=0; i<qa-1; ++i) {
          fwrite(&t,sizeof(uint8_t),1,fp);
        }
      }
    }
    break;
  }
  default:
    error("Illegal output type requested in Hex::binaryOutput");
  }
}

/// Output requested element information to a file
streamoff Hex::binaryLength(const OutputType flag) const {
  const Ordinal Nel = (qa-1)*(qb-1)*(qc-1);  // Number of sub-elements
  switch(flag) {
  case ParaviewBinary: {
    return sizeof(uint32_t)+qa*qb*qc*sizeof(float);
    break;
  }
  case ParaviewCoordinates: {
    return sizeof(uint32_t)+3*qa*qb*qc*sizeof(float);
    break;
  }
  case ParaviewConnectivity: {
    return sizeof(uint32_t)+8*Nel*sizeof(int32_t);
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
    error("Illegal output type requested in Hex::binaryLength");
  }
  error("Fell through case statement in Hex::binaryLength");
  return 0;
}

/// Dump the Element storage to a file
void Hex::output(FILE *fp, const char flag) const {
  if (state == Transform)
    error("Hex::output called when in transform space");
  Index Q(qa,qb,qc);
  int c = 0;
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
        for (Ordinal j=0; j<qb-1; j++) {
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
        for (Ordinal j=0; j<qb-1; j++) {
          if (c++%5==0) fprintf(fp,"\n");
          fprintf(fp,"%d ",VTK_HEXAHEDRON);
        }
    break;
  case 'o': // paraview offset
    for (Ordinal k=0, off=8; k<qc-1; k++)
      for (Ordinal i=0; i<qa-1; i++)
        for (Ordinal j=0; j<qb-1; j++) {
          if (c++%5==0) fprintf(fp,"\n");
          fprintf(fp,"%llu ",(unsigned long long)off);
          off+=8;
        }
    break;
  default:
    error("Illegal flag in Hex::output(), flag = "+asString(flag));
  }
}

//============================================================================
//                        Norm and Error routines
//============================================================================

/// Compute the infinity norm (maximum of the absolute value)
Scalar Hex::norm_Linf() const {
  return norm_inf(u);
}

/// Compute the L2 norm squared
void Hex::norm_L2(Scalar *L2, Scalar *volume) const {
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
Scalar Hex::norm_L2() const {
  Scalar L2, volume;
  norm_L2( &L2, &volume );
  return sqrt(L2/volume);
}

/// Computes the H1 norm squared on the Element
void Hex::norm_H1(Scalar *H1, Scalar *volume) const {

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
Scalar Hex::norm_H1() const {
  Scalar H1, volume;
  norm_H1( &H1, &volume );
  return sqrt(H1/volume);
}

/// Integrates the data stored in the Element and optionally the volume
Scalar Hex::integrate( Scalar *vol ) const {
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
Scalar Hex::integrate(const dVector &v, Scalar *vol) const {
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
void Hex::plane_average() {
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

void Hex::get_weight_props(Topology::ElementType& e, bool& c,
                           Ordinal& porder) const {
  e = Topology::Hex;
  c = true;  // assume affine element
  if (curve.get()) c = false;  // non-affine element
  porder = pOrder();
}

/// Returns the relative cost of this element's computations
/** This is a first step towards having a self tuning, load balancing
    code. See the more detailed comments in Quad.cpp.

    \note That there shouldn't be any physics at this level so this must be
    refactored.
*/
int Hex::get_weight() const {
#ifdef HEX_NS_WEIGHTS
  // Weights for Odin for Navier-Stokes physics
  static Ordinal Pmax = 10;
  static int Weight[11][2] = {
      {100, 100},
      {129, 129},
      {169, 169},
      {232, 232},
      {331, 331},
      {452, 452},
      {657, 657},
      {869, 869},
      {1215, 1215},
      {1552, 1552},
      {1989, 1989}
  };
#elif HEX_DERIVED_REDSKY_WEIGHTS
  // Weights for RedSky for derived physics
  static Ordinal Pmax = 10;
  static int Weight[11][2] = {
      {100,  104},
      {139,  153},
      {194,  243},
      {297,  416},
      {436,  955},
      {643,  2291},
      {902,  5397},
      {1284,  13846},
      {1764,  19153},
      {2374,  43765},
      {3102,  58424}
  };
#else
  // Weights for Curie (Cray-XK6) for derived physics
  static Ordinal Pmax = 20;
  static int Weight[21][2] = {
      {100, 100},
      {116, 121},
      {138, 149},
      {167, 206},
      {206, 324},
      {261, 667},
      {305, 1292},
      {380, 2921},
      {487, 5806},
      {634, 10704},
      {736, 18563},
      {933, 31133},
      {1134, 49034},
      {1439, 77140},
      {1712, 115331},
      {2024, 184577},
      {2590, 262335},
      {3187, 374665},
      {3599, 507574},
      {4171, 719038},
      {4923, 959593}
  };
#endif
  int cflag = 0;
  if (curve.get()) cflag = 1;
  if (pOrder() > Pmax) {
    if (first_warn) {
      cout << "WARNING - Hex::get_weight(): "
           << "pOrder (="<<pOrder()<<") > Pmax (="<<Pmax<<")"<< endl;
      first_warn = false;
    }
    return Weight[Pmax][cflag];
  } else
    return Weight[pOrder()][cflag];
}

/// Returns the Element measure (volume of a Hex)
Scalar Hex::compute_measure() const {
  // cout << "Hex::compute_measure()" << endl;
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

/// Returns the L2 inner product between two elements
Scalar Hex::L2_inner_product(const Element *el, Scalar *vol) const {
  // cout << "Hex::L2_inner_product" << endl;
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
  return dot( b, f );         // integrate
}

/// Returns the L2 inner product between two prescribed data vectors
Scalar Hex::L2_inner_product(const dVector& vh, const dVector& wh,
                             Scalar *vol) const {
  // cout << "Hex::L2_inner_product" << endl;
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
void Hex::filter(const dVector &mask) {
  if (state == Physical) {
    DGM::Comm::World->cerr()
      << "Hex::filter -- must be in transform space"<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  // apply filter transfer function to the modal storage of the element
  // cout<<"Hex applying filter"<<endl;
  dvmul(mask,uh);
}

/// Isolate the small scales of the element's field
void Hex::vms_isolate_small() {
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
void Hex::vms_isolate_small(dVector &full, dVector &small) {
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
void Hex::vms_isolate_small(dVector &small) {
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

/// Zero modes less than p_inc
void Hex::fine_scales(const int p_inc) {
  //cout << "Hex::fine_scales(const int p)" <<endl;
  Ordinal i, j, k;
  bool needs_transform = false;
  if (state == Physical) {
    forward_transform();
    needs_transform = true;
  }
  // lower-left Octant
  for (i=0; i<L()-p_inc; i++) {
    for (j=0; j<L()-p_inc; j++) {
      for (k=0; k<L()-p_inc; k++) {
        Ordinal n = k + j*L() + i*L()*L();
        uh[n] = 0.0;
      }
    }
  }
  if (needs_transform)
    backward_transform();
}

/// Zero modes less than p_inc in supplied vector
void Hex::fine_scales(const int p_inc, dVector &vh) {
  //cout << "Hex::fine_scales(const int p, dVector &vh)" <<endl;
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

/// Forward transform, zero coarse scales, and backward transform
void Hex::fine_scales_transform(const int p_inc, dVector &vh) const {
  //cout << "Hex::fine_scales_transform(const int p, dVector &vh)" <<endl;
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

/// Set all modes except constant to zero
void Hex::make_constant() {
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

/// Zero all modes greater than np
void Hex::low_modes(const Ordinal inp) {
  const Ordinal np = numeric_cast<Ordinal>(inp);
  if (np>=pOrder()) return;
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

void Hex::get_side_Ds(const int, const dVector& , dVector& ) const {
  error("Hex::get_side_Ds(const int, const dVector& ,dVector&) undefined");
}

void Hex::get_side_curvature(const int sid, dVector &dcurv) const {
  error("Hex::get_side_curvature(const int, dVector& ) undefined");
}

Ordinal Hex::vertex_num(const Ordinal i, const Ordinal j) const {
  return v_num[i][j];
}

Ordinal Hex::edge_num(const Ordinal i, const Ordinal j) const {
  return e_num[i][j];
}

/// Get the coordinates of straight-side (a face for a Hex element)
void Hex::get_straight_side_coordinates(const Ordinal face_id, dVector &x,
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
    DGM::Comm::World->cerr() << "Hex: Illegal face ID value" <<face_id<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
}

/// Generate curved surface coordinates
/** \todo Implement generalized curvature. */
void Hex::generate_curve() {
  // cout << "Hex::generate_curve() for " << gid() << endl;
  // Only straight edge element faces are currently supported.
  // For the case where the edges are straight but the element is non-affine,
  // only the vertex coordinates are necessary to define the quadrature
  // coordinates, therefore,
  //   (1) it is not necessary to define the face coordinates separately,
  //   (2) no forward_transform_side() is needed, and
  //   (3) get_straight_coordinates() can be used just like in the affine case.
  // So there is nothing to do!
}

// f Coordinates => fh   modal coefficients for Curve face
//                + fh_e modal coefficients for Curve edges
void Hex::forward_transform_side(const Ordinal face_id, dVector &f,
                                 dVector &fh, dVector * fh_e) {
  Ordinal i,j,k,l;
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
    fh_e[i].resize(Le); // allocate the space for the edge modal

  tmp = f;  //temporary copy as backup

  // remove vertex modes from face
  for(j=0;j<4;++j){
    side_mode(face_id, psi->vertMode(j), tmp1);
    daxpy( -vertc[j],tmp1, f);
    // side_mode(face_id, psi->vert+v_num[face_id][j], tmp1);
    // daxpy( -vert[v_num[fac][j]]->x, tmp1, f);
  }

  // transform edges
  for(j=0;j<4;++j){
    get_edge(qa, qb, f.ptr(), j, tmp2.ptr());
    forward_transform_edge(tmp2,fh_e[j]);
  }

  // transform interior

  // remove the edge modes from face
  for(j=0;j<4;++j) {
    for( dVector::size_type i = 0; i < fh_e[j].size(); ++i){
      side_mode(face_id, psi->edgeMode(e_num[face_id][j],i), tmp);
      daxpy(-fh_e[j][i], tmp, f);
    }
  }

  // finally take inner product
  for(i = 0; i < Le; ++i)
    for(j = 0; j < Le; ++j) {
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
void Hex::add_Dirac_delta(const Ordinal qpt, const Scalar amp) {
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
    with amplitude equal amp.  The Point, p, must be within the Hex element. */
void Hex::add_Dirac_delta(const Point &p, const Scalar amp) {
  Scalar r, s, t;
  // First get the local coordinate on line
  if(!get_local_coordinates(p,r,s,t)) {
    DGM::Comm::World->cerr()<<
      "Hex::Add_Dirac_delta: could not find (r,s,t)"<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  const Point q(r,s, t);
  return add_local_Dirac_delta(q,amp);
}

void Hex::add_local_Dirac_delta(const Point &p, const Scalar amp) {
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

void Hex::add_local_Dirac_delta(const vector<dMatrix> &M, const Scalar amp) {

  if (3!=M.size())
    error("Hex::add_local_Dirac_delta: Incorrect matrix size.");
  if (M[0].rows() != M[1].rows() || M[0].rows() != M[2].rows())
    error("Hex::add_local_Dirac_delta: Inconsistant matrix size.");
  if (M[0].cols() != qc || M[1].cols() != qb || M[2].cols() != qa)
    error("Hex::add_local_Dirac_delta: Inconsistant matrix size.");

  const dMatrix &imz = M[0];
  const dMatrix &imy = M[1];
  const dMatrix &imx = M[2];
  // Apply the Dirac delta function operator
  for (Ordinal i=0, qpt=0; i<qa; i++) {
    const Scalar im = amp*imx(0,i)/psi->wa[i];
    for (Ordinal j=0; j<qb; j++) {
      const Scalar jm = im*imy(0,j)/psi->wb[j];
      for (Ordinal k=0; k<qc; k++,qpt++) {
        const Scalar km = jm*imz(0,k)/psi->wc[k];
        u[qpt] += km/geom->J[qpt];
      }
    }
  }
}

/// Extract the solution at the Point p
Scalar Hex::interpolate_point(const Point &p) const {
  if (state != Physical) {
    cerr << "Hex::interpolate_point -- not in physical space"<<endl;
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
Scalar Hex::interpolate_local_point(const Point &p) const {
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

void Hex::calculate_interpolation_matrices(vector<fMatrix>    &M,
                                           const vector<Point>&ps) const{
  const Ordinal N = numeric_cast<Ordinal>(ps.size());

  M.resize(3);
  M[0].resize(N,qc);
  M[1].resize(N,qb);
  M[2].resize(N,qa);

  fVector Z(qc), W(qc);
  fVector X(N);
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

void Hex::apply_interpolation_matrices(dVector &V,
                                       const vector<fMatrix> &M) const{
  if (3!=M.size())
    error("Hex::apply_interplation_matrices: Incorrect matrix size.");
  if (M[0].rows() != M[1].rows() || M[0].rows() != M[2].rows())
    error("Hex::apply_interplation_matrices: Inconsistant matrix size.");
  if (M[0].cols() != qc || M[1].cols() != qb || M[2].cols() != qa)
    error("Hex::apply_interplation_matrices: Inconsistant matrix size.");

  const Ordinal N = M[0].rows();

  fMatrix T(N,qa*qb);
  fVector F(qa*qb*qc);
  for (Ordinal i=0; i<qa*qb*qc; ++i) F[i] = u[i];
  fMatrix U(F,qa*qb,qc);
  matmult(M[0], 'T', U, T);

  fMatrix S(N,qa);
  for (Ordinal i=0; i<N; ++i) {
    const fMatrix m(T[i],qa,qb);
    const fVector v ( M[1].row(i) );
    fVector       s ( S.row(i) );
    mvmult (m,v,s);
  }

  V.resize(N);
  for (Ordinal i=0; i<N; ++i) {
    const fVector r1 ( M[2].row(i) );
    const fVector r2 ( S.row(i) );
    V[i] = dot(r1,r2);
  }
}

void Hex::calculate_interpolation_matrices(vector<dMatrix>    &M,
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

void Hex::apply_interpolation_matrices(dVector &V,
                                       const vector<dMatrix> &M) const{
  if (3!=M.size())
    error("Hex::apply_interplation_matrices: Incorrect matrix size.");
  if (M[0].rows() != M[1].rows() || M[0].rows() != M[2].rows())
    error("Hex::apply_interplation_matrices: Inconsistant matrix size.");
  if (M[0].cols() != qc || M[1].cols() != qb || M[2].cols() != qa)
    error("Hex::apply_interplation_matrices: Inconsistant matrix size.");

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
void Hex::interpolate_points(
    const vector<Point>& ps,
    dVector&             vals
    ) const {

  if (state != Physical) {
    cerr << "Hex::interpolate_points -- not in physical space"<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }

/* Equivalent code would be:
  const Ordinal N = ps.size();
  dMatrix Mx(N,qa);
  dMatrix My(N,qb);
  dMatrix Mz(N,qc);
  dVector X(N);
  dVector Y(N);
  dVector Z(N);
  for (Ordinal n=0; n<N; ++n) {
    X[n] = ps[n].x;
    Y[n] = ps[n].y;
    Z[n] = ps[n].z;
    vals[n] = 0;
  }
  dVector Zx(qa), Wx(qa);
  dVector Zy(qb), Wy(qb);
  dVector Zz(qc), Wz(qc);
  zwgll(Zx,Wx);
  zwgll(Zy,Wy);
  zwgll(Zz,Wz);
  igllm(Mx,Zx,X);
  igllm(My,Zy,Y);
  igllm(Mz,Zz,Z);
  dArray U(u,qa,qb,qc);
  for (Ordinal n=0; n<N; ++n)
    for (Ordinal i=0; i<qa; ++i)
      for (Ordinal j=0; j<qb; ++j)
        for (Ordinal k=0; k<qc; ++k)
          vals[n] += Mx[n][i]*
                     My[n][j]*
                     Mz[n][k]*
                     U[i][j][k];
which simplifies a bit for qa=qb=qc
*/
  const Ordinal N = numeric_cast<Ordinal>(ps.size());

  dMatrix M(N,qc);
  dVector Z(qc), W(qc);
  dVector X(N);

  // SSC: we should consider building these interpolation operators once and
  // then have a fast apply method to use them.

  // 3D interpolation
  zwgll(Z,W);
  // Form the interpolation matrix from Gauss-Lobatto-Legendre to t
  for (Ordinal i=0; i<N; ++i) X[i] = ps[i].z;
  igllm(M,Z,X);

  dMatrix T(N,qa*qb);
  dMatrix U(u,qa*qb,qc);
  matmult(M, 'T', U, T);

  // 2D interpolation
  if (qb!=qc) {
    Z.resize(qb); W.resize(qb);
    zwgll(Z,W);
    M.resize(N,qb);
  }
  for (Ordinal i=0; i<N; ++i) X[i] = ps[i].y;
  igllm(M,Z,X);

  dMatrix S(N,qa);
  for (Ordinal i=0; i<N; ++i) {
    const dMatrix m(T[i],qa,qb);
    const dVector v = M.row(i);
    dVector       s = S.row(i);
    mvmult (m,v,s);
  }

  // 1D interpolation in the a-direction
  if (qa!=qb) {
    Z.resize(qa); W.resize(qa);
    zwgll(Z,W);
    M.resize(N,qa);
  }
  for (Ordinal i=0; i<N; ++i) X[i] = ps[i].x;
  igllm(M,Z,X);

  vals.resize(N);
  for (Ordinal i=0; i<N; ++i) {
    const dVector r1 = M.row(i);
    const dVector r2 = S.row(i);
    vals[i] = dot(r1,r2);
  }
}

/// Get Edge information from Face
void Hex::get_edge(Ordinal q1, Ordinal q2, Scalar *from,
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
    DGM::Comm::World->cerr() << "Illegal Edge id for Hex element" << endl;
    DGM::Comm::World->exit(DGM::FAILURE);
    break;
  }
}

/// \warning Use the Edge[0] basis information, possible problem [gqchen]
void Hex::forward_transform_edge(dVector &f, dVector &fh) {
  Ordinal i,q;
  Ordinal Le = L()-2;        // edge modal number
  dVector  &wa = psi->wa;
  if(!Le) return;
  // calculate inner product with basis
  q = qa-2;
  for(i=0;i<q;i++)
    f[i+1] *= wa[i+1];       // excluding the vertex modes
  for(i = 0; i < Le; ++i){
    fh[i] = 0;
    for(Ordinal j=0;j<q;j++) // excluding the vertex
      fh[i] += psi->edgeMode(0,i).a[j+1]*f[j+1];
  }
  solve_1d_mass_matrix(fh); // for Edge modal
}

/// Side mass matrix for curved face modal
void Hex::solve_2d_mass_matrix(dVector &fh) const {
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
void Hex::get_2d_mass_matrix(Minfo &M2d) const {
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
void Hex::J_backward_transform(dVector &fh, dVector &f) {
  //cout << "J_backward_transform()!" << endl;
  const dMatrix &Ba = psi->Ba;
  const dMatrix &Bb = psi->Bb;
  const dMatrix &Bc = psi->Bc;
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
/// Computes the element coordinates
/** This version lays in the modes associated with the issoparametric mapping
    of the element to the the reference space.  It then does a backward
    transform to return physical space values for the coordinates. */
void Hex::get_curved_coordinates() {
  cerr << "Hex::get_curved_coordinates() is not implemented" << endl;
  DGM::Comm::World->exit(DGM::FAILURE);

  const Ordinal Le = L() - 2;
  C.reset( new Coord(qtot) );
  *C = 0;

  // it is very important to declare these in the correct order [SSC]
  dVector fh(nModes()), tmp;
  fh = 0;

  // Hex map

  // x

  // vertex modal
  fh[0]       = vert[0]->x;
  fh[L()-1]     = vert[1]->x;
  fh[L()*L()-1]   = vert[2]->x;
  fh[L()*(L()-1)] = vert[3]->x;

  fh[L()*L()*(L()-1)+0]         = vert[4]->x;
  fh[L()*L()*(L()-1)+L()-1]       = vert[5]->x;
  fh[L()*L()*(L()-1)+L()*L()-1]     = vert[6]->x;
  fh[L()*L()*(L()-1)+L()*(L()-1)]   = vert[7]->x;

  // edge modal
  for(Ordinal i=0;i<4;i++){
    switch(e_num[curve->side][i]){
    case 0:
      tmp.alias(fh,L()+1,Le);
      tmp = curve->xh_e[i];
      break;
    case 1:
      for(Ordinal j=0;j<Le;j++)
        fh[L()+L()-1+j*L()] = curve->xh_e[i][j];
      break;
    case 2:
      tmp.alias(fh,L()*(L()-1)+1,Le);
      tmp = curve->xh_e[i];
      break;
    case 3:
      for(Ordinal j=0;j<Le;j++)
        fh[L()+j*L()] = curve->xh_e[i][j];
      break;
    case 4:
      for(Ordinal j=0;j<Le;j++)
        fh[L()*L()+j*L()*L()] = curve->xh_e[i][j];
      break;
    case 5:
      for(Ordinal j=0;j<Le;j++)
        fh[L()*L()+L()-1+j*L()*L()] = curve->xh_e[i][j];
      break;
    case 6:
      for(Ordinal j=0;j<Le;j++)
        fh[L()*L()+L()*L()-1+j*L()*L()] = curve->xh_e[i][j];
      break;
    case 7:
      for(Ordinal j=0;j<Le;j++)
        fh[L()*L()+L()*(L()-1)+j*L()*L()] = curve->xh_e[i][j];
      break;
    case 8:
      tmp.alias(fh,L()*L()*(L()-1)+1,Le);
      tmp = curve->xh_e[i];
      break;
    case 9:
      for(Ordinal j=0;j<Le;j++)
        fh[L()*L()*(L()-1)+L()+L()-1+j*L()] = curve->xh_e[i][j];
      break;
    case 10:
      tmp.alias(fh,L()*L()*(L()-1)+L()*(L()-1)+1,Le);
      tmp = curve->xh_e[i];
      break;
    case 11:
      for(Ordinal j=0;j<Le;j++)
        fh[L()*L()*(L()-1)+L()+j*L()] = curve->xh_e[i][j];
      break;
    }
  }

  int n = 0;
  // face modal
  switch(curve->side){
  case 0:
    for(Ordinal i=0;i<Le;i++)
      for(Ordinal j=0;j<Le;j++)
        fh[L()+1+i*L()+j] = curve->xh[n++];
    break;
  case 1:
    for(Ordinal i=0;i<Le;i++)
      for(Ordinal j=0;j<Le;j++)
        fh[L()*L()+1+i*L()*L()+j] = curve->xh[n++];
    break;
  case 2:
    for(Ordinal i=0;i<Le;i++)
      for(Ordinal j=0;j<Le;j++)
        fh[L()*L()+L()+L()-1+i*L()*L()+j*L()] = curve->xh[n++];
    break;
  case 3:
    for(Ordinal i=0;i<Le;i++)
      for(Ordinal j=0;j<Le;j++)
        fh[L()*L()+L()*(L()-1)+1+i*L()*L()+j] = curve->xh[n++];
    break;
  case 4:
    for(Ordinal i=0;i<Le;i++)
      for(Ordinal j=0;j<Le;j++)
        fh[L()*L()+L()+i*L()*L()+j*L()] = curve->xh[n++];
    break;
  case 5:
    for(Ordinal i=0;i<Le;i++)
      for(Ordinal j=0;j<Le;j++)
        fh[L()*L()*(L()-1)+L()+1+i*L()+j] = curve->xh[n++];
    break;
  }

  J_backward_transform( fh, C->x );

  // Hex map

  // y
  fh = 0;
  // vertex modal
  fh[0]       = vert[0]->y;
  fh[L()-1]     = vert[1]->y;
  fh[L()*L()-1]   = vert[2]->y;
  fh[L()*(L()-1)] = vert[3]->y;

  fh[L()*L()*(L()-1)+0]         = vert[4]->y;
  fh[L()*L()*(L()-1)+L()-1]       = vert[5]->y;
  fh[L()*L()*(L()-1)+L()*L()-1]     = vert[6]->y;
  fh[L()*L()*(L()-1)+L()*(L()-1)]   = vert[7]->y;

  // edge modal
  for(Ordinal i=0;i<4;i++){
    switch(e_num[curve->side][i]){
    case 0:
      tmp.alias(fh,L()+1,Le);
      tmp = curve->yh_e[i];
      break;
    case 1:
      for(Ordinal j=0;j<Le;j++)
        fh[L()+L()-1+j*L()] = curve->yh_e[i][j];
      break;
    case 2:
      tmp.alias(fh,L()*(L()-1)+1,Le);
      tmp = curve->yh_e[i];
      break;
    case 3:
      for(Ordinal j=0;j<Le;j++)
        fh[L()+j*L()] = curve->yh_e[i][j];
      break;
    case 4:
      for(Ordinal j=0;j<Le;j++)
        fh[L()*L()+j*L()*L()] = curve->yh_e[i][j];
      break;
    case 5:
      for(Ordinal j=0;j<Le;j++)
        fh[L()*L()+L()-1+j*L()*L()] = curve->yh_e[i][j];
      break;
    case 6:
      for(Ordinal j=0;j<Le;j++)
        fh[L()*L()+L()*L()-1+j*L()*L()] = curve->yh_e[i][j];
      break;
    case 7:
      for(Ordinal j=0;j<Le;j++)
        fh[L()*L()+L()*(L()-1)+j*L()*L()] = curve->yh_e[i][j];
      break;
    case 8:
      tmp.alias(fh,L()*L()*(L()-1)+1,Le);
      tmp = curve->yh_e[i];
      break;
    case 9:
      for(Ordinal j=0;j<Le;j++)
        fh[L()*L()*(L()-1)+L()+L()-1+j*L()] = curve->yh_e[i][j];
      break;
    case 10:
      tmp.alias(fh,L()*L()*(L()-1)+L()*(L()-1)+1,Le);
      tmp = curve->yh_e[i];
      break;
    case 11:
      for(Ordinal j=0;j<Le;j++)
        fh[L()*L()*(L()-1)+L()+j*L()] = curve->yh_e[i][j];
      break;
    }
  }

  n = 0;
  // face modal
  switch(curve->side){
  case 0:
    for(Ordinal i=0;i<Le;i++)
      for(Ordinal j=0;j<Le;j++)
        fh[L()+1+i*L()+j] = curve->yh[n++];
    break;
  case 1:
    for(Ordinal i=0;i<Le;i++)
      for(Ordinal j=0;j<Le;j++)
        fh[L()*L()+1+i*L()*L()+j] = curve->yh[n++];
    break;
  case 2:
    for(Ordinal i=0;i<Le;i++)
      for(Ordinal j=0;j<Le;j++)
        fh[L()*L()+L()+L()-1+i*L()*L()+j*L()] = curve->yh[n++];
    break;
  case 3:
    for(Ordinal i=0;i<Le;i++)
      for(Ordinal j=0;j<Le;j++)
        fh[L()*L()+L()*(L()-1)+1+i*L()*L()+j] = curve->yh[n++];
    break;
  case 4:
    for(Ordinal i=0;i<Le;i++)
      for(Ordinal j=0;j<Le;j++)
        fh[L()*L()+L()+i*L()*L()+j*L()] = curve->yh[n++];
    break;
  case 5:
    for(Ordinal i=0;i<Le;i++)
      for(Ordinal j=0;j<Le;j++)
        fh[L()*L()*(L()-1)+L()+1+i*L()+j] = curve->yh[n++];
    break;
  }

  J_backward_transform( fh, C->y );

  // Hex map

  // z
  fh = 0;
  // vertex modal
  fh[0]       = vert[0]->z;
  fh[L()-1]     = vert[1]->z;
  fh[L()*L()-1]   = vert[2]->z;
  fh[L()*(L()-1)] = vert[3]->z;

  fh[L()*L()*(L()-1)+0]         = vert[4]->z;
  fh[L()*L()*(L()-1)+L()-1]       = vert[5]->z;
  fh[L()*L()*(L()-1)+L()*L()-1]     = vert[6]->z;
  fh[L()*L()*(L()-1)+L()*(L()-1)]   = vert[7]->z;

  // edge modal
  for(Ordinal i=0;i<4;i++){
    switch(e_num[curve->side][i]){
    case 0:
      tmp.alias(fh,L()+1,Le);
      tmp = curve->zh_e[i];
      break;
    case 1:
      for(Ordinal j=0;j<Le;j++)
        fh[L()+L()-1+j*L()] = curve->zh_e[i][j];
      break;
    case 2:
      tmp.alias(fh,L()*(L()-1)+1,Le);
      tmp = curve->zh_e[i];
      break;
    case 3:
      for(Ordinal j=0;j<Le;j++)
        fh[L()+j*L()] = curve->zh_e[i][j];
      break;
    case 4:
      for(Ordinal j=0;j<Le;j++)
        fh[L()*L()+j*L()*L()] = curve->zh_e[i][j];
      break;
    case 5:
      for(Ordinal j=0;j<Le;j++)
        fh[L()*L()+L()-1+j*L()*L()] = curve->zh_e[i][j];
      break;
    case 6:
      for(Ordinal j=0;j<Le;j++)
        fh[L()*L()+L()*L()-1+j*L()*L()] = curve->zh_e[i][j];
      break;
    case 7:
      for(Ordinal j=0;j<Le;j++)
        fh[L()*L()+L()*(L()-1)+j*L()*L()] = curve->zh_e[i][j];
      break;
    case 8:
      tmp.alias(fh,L()*L()*(L()-1)+1,Le);
      tmp = curve->zh_e[i];
      break;
    case 9:
      for(Ordinal j=0;j<Le;j++)
        fh[L()*L()*(L()-1)+L()+L()-1+j*L()] = curve->zh_e[i][j];
      break;
    case 10:
      tmp.alias(fh,L()*L()*(L()-1)+L()*(L()-1)+1,Le);
      tmp = curve->zh_e[i];
      break;
    case 11:
      for(Ordinal j=0;j<Le;j++)
        fh[L()*L()*(L()-1)+L()+j*L()] = curve->zh_e[i][j];
      break;
    }
  }

  n = 0;
  // face modal
  switch(curve->side){
  case 0:
    for(Ordinal i=0;i<Le;i++)
      for(Ordinal j=0;j<Le;j++)
        fh[L()+1+i*L()+j] = curve->zh[n++];
    break;
  case 1:
    for(Ordinal i=0;i<Le;i++)
      for(Ordinal j=0;j<Le;j++)
        fh[L()*L()+1+i*L()*L()+j] = curve->zh[n++];
    break;
  case 2:
    for(Ordinal i=0;i<Le;i++)
      for(Ordinal j=0;j<Le;j++)
        fh[L()*L()+L()+L()-1+i*L()*L()+j*L()] = curve->zh[n++];
    break;
  case 3:
    for(Ordinal i=0;i<Le;i++)
      for(Ordinal j=0;j<Le;j++)
        fh[L()*L()+L()*(L()-1)+1+i*L()*L()+j] = curve->zh[n++];
    break;
  case 4:
    for(Ordinal i=0;i<Le;i++)
      for(Ordinal j=0;j<Le;j++)
        fh[L()*L()+L()+i*L()*L()+j*L()] = curve->zh[n++];
    break;
  case 5:
    for(Ordinal i=0;i<Le;i++)
      for(Ordinal j=0;j<Le;j++)
        fh[L()*L()*(L()-1)+L()+1+i*L()+j] = curve->zh[n++];
    break;
  }
  J_backward_transform( fh, C->z );

}

/// Compute the geometric factors
/** This version computes the Jacobian for a general curved element using
    an isoparametric mapping.  As such, this Jacobian varies over the element.

    The Jacobian matrix is given by
    \f[\boldsymbol{J} =
       \begin{bmatrix}
         x_{,r} && x_{,s} && x_{,t} \\
         y_{,r} && y_{,s} && y_{,t} \\
         z_{,r} && z_{,s} && z_{,t} \\
       \end{bmatrix}
    \f]
*/
void Hex::compute_curved_geometry() {
  // cout << "Hex::compute_curved_geometry() for element " << gid() << endl;

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
  // Scalar detJ = xr*ys*zt + yr*zs*xt + zr*xs*yt -
  //               xt*ys*zr - zt*xs*yr - xr*zs*yt;

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

  dvmul(xr,ys,tmp1);
  dvvtvm(xs,yr,tmp1,geom->tz);

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

vector<dMatrix*> Hex::get_interpolation_matrices() const {
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

void Hex::fill_basis_shift_matrix(dMatrix &G) const {
  const int nModes = 8;
  const int Nvert = 8;
  G.resize(nModes, Nvert);

  const Scalar r0 = 1.0/sqrt(8.0);
  const Scalar r1 = 1.0/sqrt(24.0);
  const Scalar r2 = r1;
  const Scalar r3 = 1.0/sqrt(72.0);
  const Scalar r4 = r1;
  const Scalar r5 = r3;
  const Scalar r6 = r3;
  const Scalar r7 = 1.0/sqrt(216.0);
  G(0,0) =  r0; G(0,1) =  r0; G(0,2) =  r0; G(0,3) =  r0;
  G(1,0) = -r1; G(1,1) = -r1; G(1,2) = -r1; G(1,3) = -r1;
  G(2,0) = -r2; G(2,1) = -r2; G(2,2) =  r2; G(2,3) =  r2;
  G(3,0) =  r3; G(3,1) =  r3; G(3,2) = -r3; G(3,3) = -r3;
  G(4,0) = -r4; G(4,1) =  r4; G(4,2) =  r4; G(4,3) = -r4;
  G(5,0) =  r5; G(5,1) = -r5; G(5,2) = -r5; G(5,3) =  r5;
  G(6,0) =  r6; G(6,1) = -r6; G(6,2) =  r6; G(6,3) = -r6;
  G(7,0) = -r7; G(7,1) =  r7; G(7,2) = -r7; G(7,3) =  r7;

  G(0,4) =  r0; G(0,5) =  r0; G(0,6) =  r0; G(0,7) =  r0;
  G(1,4) =  r1; G(1,5) =  r1; G(1,6) =  r1; G(1,7) =  r1;
  G(2,4) = -r2; G(2,5) = -r2; G(2,6) =  r2; G(2,7) =  r2;
  G(3,4) = -r3; G(3,5) = -r3; G(3,6) =  r3; G(3,7) =  r3;
  G(4,4) = -r4; G(4,5) =  r4; G(4,6) =  r4; G(4,7) = -r4;
  G(5,4) = -r5; G(5,5) =  r5; G(5,6) =  r5; G(5,7) = -r5;
  G(6,4) =  r6; G(6,5) = -r6; G(6,6) =  r6; G(6,7) = -r6;
  G(7,4) =  r7; G(7,5) = -r7; G(7,6) =  r7; G(7,7) = -r7;
}

} // namespace DGM
