/** \file SpectralHex.cpp
    \brief Spectral Hex Element implementation
    \author Scott Collis
    \author Thomas M. Smith
    \author James Overfelt

    Spectral Hex is a eight node hexahedral element that supports both affine
    and curved sided isoparametric mappings from the master element to the
    physical space element.

    \todo Implement and test curved faces for Spectral Hex elements
*/

// System includes
#include <iostream>
#include <cstdio>
#include <cstdlib>
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
#include "SpectralHex.hpp"
#include "Polylib.tpp"
#include "String.hpp"
#include "Utilities.hpp"
#include "BaseQuad.hpp"

#ifdef DGM_USE_GENERAL_GHOSTING
/// register class for serialization of polymorphic types
BOOST_CLASS_EXPORT_GUID(DGM::SpectralHex, "DGM::SpectralHex");
#endif

namespace DGM {

// define static storage

BasisDB SpectralHex::bdb;         // define Basis database
SpectralHex::GeometryDB SpectralHex::gdb("SpectralHex "); // Geometry database
IMDB SpectralHex::imdb;           // define Interpolation Matrix database
DerivDB SpectralHex::ddb;         // define Derivative Matrix database

Ordinal SpectralHex::Qmax = 0;
Ordinal SpectralHex::Lmax = 0;
dVector SpectralHex::g1_wk;
dVector SpectralHex::g2_wk;
dVector SpectralHex::g3_wk;

dVector SpectralHex::n1_wk;
dVector SpectralHex::n2_wk;
dVector SpectralHex::n3_wk;
dVector SpectralHex::Lwk;
dVector SpectralHex::Lwk2;

bool SpectralHex::first_warn(true);

const int SpectralHex::v_num[6][4] = {{0,1,2,3},{0,1,5,4},{1,2,6,5},
                                      {3,2,6,7},{0,3,7,4},{4,5,6,7}};

const int SpectralHex::e_num[6][4] = {{0,1,2,3},{0,5,8,4},{1,6,9,5},
                                      {2,6,10,7},{3,7,11,4},{8,9,10,11}};

/// Primary Constructor
/*! \param[in] ID    - Local element id
    \param[in] P     - Polynomial order
    \param[in] X     - Vector of points defining the vertices */
SpectralHex::SpectralHex(const Ordinal ID, const Ordinal P,
                         const vector<Point> &X) : BaseHex(ID,Basis::Lagrange) {
  //cout << "SpectralHex::SpectralHex, eid = " << ID << endl;
  nVerts(8);
  nEdges(12);
  nFaces(6);
  nSides(6);
  pOrder(P);
  L(P+1);
  nModes(L()*L()*L());

  if (P==0) throw DGM::exception("Spectral elements must have P>0");

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
  face.reserve(nFaces());
  for (Ordinal i=0; i<nFaces(); i++) {
    Face fac(i,this,nModes(),qa,qa,true);  //TMS // make qedg1=qedg2 for now
    face.push_back(fac);
    side.push_back(&(face[i]));
  }
}

/// Copy constructor -- This should not allocate new space for P, M, etc.
SpectralHex::SpectralHex(const SpectralHex *E) {
  // cout << "SpectralHex copy constructor for Eid = " << E->gid() << endl;

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
SpectralHex::~SpectralHex() {
  // cout << DGM::Comm::World->MyPID() << " ~SpectralHex: eid= "
  //      << gid() << endl;
}

/// Retrieves a basis from the basis database
/** If the basis is not in the database, makes a new basis and adds to
    database
    \todo Switch to a non-string key like the interpolation matrix. */
Basis* SpectralHex::get_basis(const int der=0) const {
   //cout << "SpectralHex::get_basis" << endl;
  Basis* b;
  char buf[128];
  sprintf(buf,"%llu_%llu_%d_%llu_%llu_%llu",
      (long long unsigned)type,(long long unsigned)L(),der,
      (long long unsigned)qa,(long long unsigned)qb,(long long unsigned)qc);
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

/// Gets the mass matrix for this SpectralHex
/** \note For spectral elements the mass matrix is always diagonal and this
    routine actually computes the inverse of the mass matrix. */
void SpectralHex::get_mass_matrix() { //TMS
  //  cout << "SpectralHex::get_mass_matrix for element " << gid() << endl;
    M.reset( new Minfo );
    M->mat.resize(1,nModes());
    dVector f(qtot);
    for (Ordinal m=0; m<nModes(); m++) {
      fill( psi->mode[m], f );
      M->mat[0][m] = inner_product(f,m);
    }
    // cout << "Mass matrix for elmt " << gid() << endl << M->mat << endl;
    for (Ordinal j=0; j<nModes(); j++) M->mat[0][j] = one/M->mat[0][j];
}

/// Resets the mass matrixing using a weighted mass matrix
/** \warning Might be dangerous to reset the mass matrix to this new value. */
void SpectralHex::get_mass_matrix(const dVector &x) {
  DGM_UNDEFINED;
}

/// Solves (LU factors) the mass matrix
void SpectralHex::solve_mass_matrix(dVector &fh) const {
    for (Ordinal i=0; i<nModes(); i++) fh[i] *= M->mat[0][i];
}

/// Solves (LU factors) the mass matrix
void SpectralHex::solve_mass_matrix(dMatrix &fh) {
  DGM_UNDEFINED;
//  for (dMatrix::size_type j=0; j<fh.rows(); ++j) {
//    for (Ordinal i=0; i<nModes(); ++i) {
//      fh[j][i] *= M->mat[0][i];
//    }
//  }
}

//=============================================================================

/// Computes the normal gradient on a supplied side //TMS
void SpectralHex::normal_times_gradient_side(const dVector &f, const int sid,
                                      dVector &fssum ) const {
  DGM_UNDEFINED;
}

/// Computes a mass matrix but does not factor it //TMS
void SpectralHex::get_local_mass_matrix(const dVector &factor) {
  DGM_UNDEFINED;
}

/// Computes the local derivative matrix //TMS
void SpectralHex::get_local_derivative_matrix() {
  DGM_UNDEFINED;
}

/// Computes the local derivative matrix //TMS
void SpectralHex::get_local_derivative_matrix(const dVector &factor) {
  DGM_UNDEFINED;
}

/// Computes the local Laplace matrix //TMS
void SpectralHex::get_local_laplace_matrix() {
  DGM_UNDEFINED;
}

/// Computes the local Laplace matrix //TMS
void SpectralHex::get_local_laplace_matrix(const dVector &factor) {
  DGM_UNDEFINED;
}

//=============================================================================

/// Fill element with a function string
void SpectralHex::fill(string function_string, Operation operation) {
  //  cout << "SpectralHex::fill(string function_string)" << endl;
  state = Physical;
  parser_init();
  Parser::VectorFunction f("x", "y", "z", "t", function_string );
  f.evaluate( C->x, C->y, C->z, u, 0.0, convert(operation) );
  state = Physical;
}

/// Fill element with a mode
void SpectralHex::fill(Mode &v) {
  // cout << "SpectralHex::fill(Mode &)" << endl;
  dArray U(u,qa,qb,qc);
  for (Ordinal i=0; i<qa; i++)
    for (Ordinal j=0; j<qb; j++)
      for (Ordinal k=0; k<qc; k++)
        U[i][j][k] = v.a[i] * v.b[j] * v.c[k];
  state = Physical;
}

/// Fill a vector with a mode
void SpectralHex::fill(Mode &v, dVector &f) const {
  //  cout << "SpectralSpectralHex::fill(Mode &, dVector &) const" << endl;
  dArray F(f,qa,qb,qc);
  for (Ordinal i=0; i<qa; i++) {
    const Scalar I = v.a[i];
    Scalar   **F_i =   F[i];
    for (Ordinal j=0; j<qb; j++) {
      const Scalar IJ = I*v.b[j];
      Scalar    *F_ij =   F_i[j];
      for (Ordinal k=0; k<qc; k++) {
        F_ij[k] = IJ * v.c[k];
      }
    }
  }
}

/// Fill element with a random polynomial
void SpectralHex::random() {
  //cout << "SpectralHex::random()" << endl;
  state = Physical;
  for (Ordinal i=0; i<nModes(); i++) uh[i] = Element::random(-one,one);
}

/// Set the modes of an element
void SpectralHex::set(const dVector &fh, const Ordinal nModes2) {
  // cout << "SpectralHex::set(const dVector &, const int)" << endl;
  Ordinal L2 = static_cast<Ordinal>(round(pow(static_cast<Scalar>(nModes2),
                                    1.0/3.0)));
  if ( L2*L2*L2 != nModes2 ) {
    cout << "SpectralHex::set L2 = " << L2 << ", L = " << L() << ", nModes2 = "
         << nModes2 << ", nModes = " << nModes() << endl;
    throw DGM::exception("There is a logic error in SpectralHex::set(...)");
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
void SpectralHex::inner_product() {
  inner_product(u, uh);
  state = Transform;
}

/// Computes the inner product of the supplied vector against the Basis
Scalar SpectralHex::inner_product(dVector &f, const Ordinal m) const {
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
void SpectralHex::inner_product(dVector &f, dVector &fh) const {
  // cout<<"SpectralHex::inner_product(dVector &f, dVector &fh) for "
  // "Eid = "<<id<<endl;
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
void SpectralHex::forward_transform() {
#ifdef DGM_SPECTRALHEX_TIMERS
  static FunctionTimer T("SpectralHex::forward_transform");
  FunctionSentry sentry(T);
#endif
  if (state == Transform) {
    cerr << "SpectralHex::transform -- already in transform space"<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  forward_transform(u,uh);
  state = Transform;
}

/// Transform the supplied data to polynomial space
/** Since this is a Lagrange element, it is already in polynomial space. */
void SpectralHex::forward_transform(dVector &f, dVector &fh) const {
  // cout << "SpectralHex::forward_transform(dVector &f, dVector &fh)" << endl;
  // inner_product(f,fh);
  // solve_mass_matrix(fh);
}

/// Transform using another Elements mass matrix (dangerous)
void SpectralHex::forward_transform(Element *F, Element *) {
  //cout << "SpectralHex::forward_transform(*F,*)" << endl;
  if (state == Transform) {
    cerr << "SpectralHex::transform -- already in transform space"<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  inner_product(u,uh);
  F->solve_mass_matrix(uh);  // Use element F's Mass matrix
  state = Transform;
}

/// Return Element to physical space
/** Again a null operation since it is always in physical space. */
void SpectralHex::backward_transform() {
#ifdef DGM_SPECTRALHEX_TIMERS
  static FunctionTimer T("SpectralHex::backward_transform");
  FunctionSentry sentry(T);
#endif
  if (state == Physical) {
    cerr << "SpectralHex::transform_to_physical -- already in physical space"
         <<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  // backward_transform( uh, u );
  state = Physical;
}

/// Transform supplied data to physical space on this Element //TMS
void SpectralHex::backward_transform(dVector &fh, dVector &f) const {
  // cout << "SpectralHex::backward_transform(dVector &f, dVector &fh)"<<endl;
#if 1
  return;
#else
  // This has not been changed yet!  //TMS
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
#endif
}

/// Transform from physical space to Legendre coefficients
void SpectralHex::L_forward_transform() {
  // This does a linear transform which is what we want
  Minfo &Vi = psi->Vi;

  if (Vi.mat.size()==0) {
    // setup modal access pointers
    Mode *mode = new Mode[L()*L()*L()];
    for (Ordinal i=0, m=0; i<L(); i++) {
      for (Ordinal j=0; j<L(); j++) {
        for (Ordinal k=0; k<L(); m++, k++) {
          mode[m].a.alias( psi->ga[i] );
          mode[m].b.alias( psi->gbv[j] );
          mode[m].c.alias( psi->gc[k] );
        }
      }
    }
    Vi.mat.resize(nModes(),nModes());
    dVector Vcol(qtot);
    for (Ordinal j=0; j<nModes(); ++j) {
      fill( mode[j], Vcol );
      for (Ordinal i=0; i<qtot; i++) Vi.mat[i][j] = Vcol[i];
    }
    if (LU_factor(Vi.mat, Vi.pivots)!=0)
      DGM::Comm::World->error("SpectralHex::L_forward_transform -- "
                              "LU_factor of Vandermonde failed.");
    delete[] mode;
  }
  LU_solve(Vi.mat, Vi.pivots, uh);
}

void SpectralHex::L_backward_transform() {
  const dMatrix &phia = psi->Ga;
  const dMatrix &phib = psi->Gb;
  const dMatrix &phic = psi->Gc;
  dMatrix H( Lwk, qa, L()*L() );
  dMatrix Ha;
  dMatrix Fh( uh, L(), L()*L() );
  matmult( 'T', phia, Fh, H );
  for (Ordinal i=0; i<qa; ++i) {
    H.alias( Lwk, i*L()*L(), L(), L() );
    Ha.alias( Lwk2, i*qb*L(), qb, L() );
    matmult( 'T', phib, H, Ha );
  }
  dMatrix F( u, qa*qb, qc );
  Ha.alias( Lwk2, qa*qb, L());
  matmult( Ha, phic, F );
}

/// Extracts data onto a specified Side
void SpectralHex::get_side( const dVector &from, const Ordinal sid,
                            dVector &to ) const {
  //  cout<<"SpectralHex::get_side() Element = "<<id<<" Side = "<<sid<<endl;
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
    cerr << "SpectralHex::get_side -- unknown edge" << endl;
    DGM::Comm::World->exit(DGM::FAILURE);
    break;
  }
}

/// Makes an interpolation matrix
void SpectralHex::make_interpolation_matrix(const Ordinal q1, const Ordinal q2,
                                            const Interp::Type interp,
                                            dMatrix &im ) {
  //  cout << "SpectralHex::make_interpolation_matrix" << endl;
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
  case(Interp::GL2GL):
    zwgll(z2,w2);           // Gauss-Lobatto-Legendre
    zwgll(z1,w1);           // Gauss-Lobatto-Legendre
    igllm(im,z2,z1);        // Interpolation matrix
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
      cerr << "SpectralHex::make_interpolation_matrix - Invalid "
              "q1,q2 order" << endl;
      DGM::Comm::World->exit(DGM::FAILURE);
    }

    I=0.0;
    for (Ordinal i=0; i<L1; i++) I(i,i) = 1.0;

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
    cerr << "SpectralHex::make_interpolation_matrix - Invalid "
            "interpolation type" << endl;
    DGM::Comm::World->exit(DGM::FAILURE);
    break;
  }
}

/// Returns an interpolation matrix (making one if needed)
dMatrix* SpectralHex::get_interpolation_matrix(const Ordinal q1,
                                               const Ordinal q2,
                                               const Interp::Type interp=
                                                 Interp::GL2GL) {
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
void SpectralHex::load_side(const dVector &f, const Ordinal side_id,
                            dVector &f_side) const {
  get_side(f, side_id, f_side);

  //  cout << "SpectralHex::load_side(const dVector &f, const int side_id,
  //                        dVector &f_side) const" << endl;
  //dVector wkab, wkac, wkbc, tmp, wk[6];
  //wkab.alias(g1_wk,qa*qb);
  //wkac.alias(g2_wk,qa*qc);
  //wkbc.alias(g3_wk,qb*qc);
  //wk[0].alias(wkab); wk[1].alias(wkac); wk[2].alias(wkbc);
  //wk[3].alias(wkac); wk[4].alias(wkbc); wk[5].alias(wkab);

  // check that the number of quadrature points on this side match
  //assert( (dVector::size_type)side[side_id]->qtot() == f_side.size() );

  //tmp.alias(Lwk,side[side_id]->qtot());
  //get_side(f, side_id, wk[side_id]);
  //interpolate_to_side(side_id, wk[side_id], f_side );
}

/// Interpolate supplied physical space values to the Side Gauss points. //TMS
void SpectralHex::fill_sides(const dVector &f) {
  //  cout << "SpectralHex::fill_sides(dVector &f)" << endl;
  Ordinal q1=0, q2=0;
  dVector wkab, wkac, wkbc, wk[6];
  wkab.alias(g1_wk,qa*qb);
  wkac.alias(g2_wk,qa*qc);
  wkbc.alias(g3_wk,qb*qc);
  wk[0].alias(wkab); wk[1].alias(wkac); wk[2].alias(wkbc);
  wk[3].alias(wkac); wk[4].alias(wkbc); wk[5].alias(wkab);
  for (Ordinal i=0; i<nSides(); i++) {
    side_to_size(q1, q2, i);
    if (side[i]->qtot() != q1*q2) {
      get_side(f, i, wk[i]);
      interpolate_to_side(i, wk[i], side[i]->u );
    } else {
      get_side(f, i, side[i]->u);
    }
  }
#ifdef DGM_ALLOW_HANGING_NODES
  push_to_subsides();
#endif
}

/// Fill Element Sides with a flux vector (3-d flux version) //TMS
void SpectralHex::fill_sides(const dVector &fx, const dVector &fy,
                             const dVector &fz) {
  // cout << "SpectralHex::fill_sides(const dVector &fx, const dVector &fy, "
  //      << "const dVector &fz)" << endl;
  Ordinal q1=0, q2=0;
  dVector wkab, wkac, wkbc, tmp, wk[6];
  wkab.alias(g1_wk,qa*qb);
  wkac.alias(g2_wk,qa*qc);
  wkbc.alias(g3_wk,qb*qc);
  wk[0].alias(wkab); wk[1].alias(wkac); wk[2].alias(wkbc);
  wk[3].alias(wkac); wk[4].alias(wkbc); wk[5].alias(wkab);
  for (Ordinal i=0; i<nSides(); i++) {
    side_to_size(q1, q2, i);
    if (side[i]->qtot() != q1*q2) {
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
    } else {
      tmp.alias(Lwk,side[i]->qtot());
      get_side(fx, i, side[i]->u);
      dvmul( side[i]->nx(), side[i]->u );
      get_side(fy, i, tmp);
      dvvtvp( side[i]->ny(), tmp, side[i]->u, side[i]->u );
      get_side(fz, i, tmp);
      dvvtvp( side[i]->nz(), tmp, side[i]->u, side[i]->u );
    }
  }
#ifdef DGM_ALLOW_HANGING_NODES
  push_to_subsides();
#endif
}

/// Compute coordinates of quadrature points
void SpectralHex::get_coordinates() {
  // cout << "SpectralHex::get_coordinates for element " << gid() << endl;
  if (curve.get()) {
    // Only straight edge affine and non-affine elements are supported.  In
    // both cases, get_straight_coordinates() can be used.
    // get_curved_coordinates();
    get_straight_coordinates();
  } else {
    get_straight_coordinates();
  }
}

//#define DGM_HEX_USE_MATRIX_STORAGE

/// Compute coordinates for a straight-sided Element
void SpectralHex::get_straight_coordinates() {
  // cout << "SpectralHex::get_straight_coordinates for element "
  //      << gid() << endl;
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
void SpectralHex::compute_geometry() {
  // cout << "SpectralHex::compute_geometry for element " << gid() << endl;
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
bool SpectralHex::is_affine() const {
  // cout << "SpectralHex::is_affine for element " << gid() << endl;

  // compute coordinate differences in mapped space
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
/** \warning This is only correct for parallelograms. */
void SpectralHex::compute_straight_geometry() {
  //cout << "SpectralHex::compute_straight_geometry for element "
  //     << gid() << endl;

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
    cerr << "ERROR:  SpectralHex::compute_straight_geometry()" << endl
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

/// Compute the stability metrics for timestep size calculations.
Element::StabMetrics SpectralHex::compute_metrics() {
  return compute_metrics_3d_tensor_prod();
}

/// Returns the side quadrature orders
void SpectralHex::side_to_size(Ordinal &q1, Ordinal &q2,
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
void SpectralHex::side2size(const Ordinal side, iVector &q) const {
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
Ordinal SpectralHex::side2size(const Ordinal side) const {
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
void SpectralHex::interpolate_to_side( const Ordinal sid, const dVector &from,
                                       dVector &to) const {
  //  cout << "SpectralHex::interpolate_to_side(), sid = " << sid << endl;
  Ordinal q1=0, q2=0;

  // to
  const Ordinal q1g = face[sid].q1();
  const Ordinal q2g = face[sid].q2();

  // from
  side_to_size(q1, q2, sid);

  const dMatrix *const im1 =
    get_interpolation_matrix( q1g, q1, Interp::GL2GL);  // to, from
  const dMatrix *const im2 =
    get_interpolation_matrix( q2g, q2, Interp::GL2GL);  // to, from

  dMatrix From, To, wk;
  wk.exclusive_alias(n1_wk,q1g,q2);
  From.alias( const_cast<dVector&>(from), q1, q2 );
  To.alias( to, q1g, q2g );

  matmult( *im1, From, wk );
  matmult( wk, 'T', *im2, To );
}

namespace {
void var_p_lift(const Ordinal q1,
                const Ordinal q2,
                const Face    &face,
                const dVector &from,
                dVector &n1_wk,
                dVector &n2_wk,
                dVector &to) {
  Ordinal q1g = face.q1();
  Ordinal q2g = face.q2();
  DGM::Shared<Basis>::Ptr &fpsi = const_cast<Face*>(&face)->psi;
  if (!fpsi) {
    // Initialization done only once.
    const Ordinal nmodes = q1g*q2g;
    const Ordinal qtot   = q1g*q2g;
    fpsi = DGM::Shared<Basis>::Ptr(new Basis(q1g,q1g,q2g,0,nmodes));
    BaseQuad::make_basis(fpsi.get(),Basis::Lagrange,0);

    std::vector<Mode> mode(q1g*q2g); // setup modal access pointers
    for (Ordinal i=0, m=0; i<q1g; i++) {
      for (Ordinal j=0; j<q2g; m++, j++) {
        mode[m].a.alias( fpsi->ga[i] );
        mode[m].b.alias( fpsi->gbv[j] );
      }
    }
    Minfo &Vi = fpsi->Vi;
    Vi.mat.resize(nmodes,nmodes);
    dVector Vcol(qtot);
    dMatrix F(Vcol,q1g,q2g);
    for (Ordinal j=0; j<nmodes; ++j) {
      for (Ordinal i=0; i<q1g; i++) {
        for (Ordinal k=0; k<q2g; k++) {
          F[i][k] = mode[j].a[i] * mode[j].b[k];
        }
      }
      for (Ordinal i=0; i<qtot; i++) Vi.mat[i][j] = Vcol[i];
    }
    if (LU_factor(Vi.mat, Vi.pivots)!=0)
      DGM::Comm::World->error("SpectralQuad::L_forward_transform -- "
                              "LU_factor of Vandermonde failed.");
    Minfo Vi_tmp;
    Vi_tmp.mat.   resize(Vi.mat);
    Vi_tmp.pivots.resize(Vi.pivots);
    Vi_tmp.mat    = Vi.mat;
    Vi_tmp.pivots = Vi.pivots;

    fpsi = DGM::Shared<Basis>::Ptr(new Basis(q1,q2,q2,0,q1*q2));
    BaseQuad::make_basis(fpsi.get(),Basis::Lagrange,0);

    fpsi->Vi.mat.   resize(Vi_tmp.mat);
    fpsi->Vi.pivots.resize(Vi_tmp.pivots);
    fpsi->Vi.mat    = Vi_tmp.mat;
    fpsi->Vi.pivots = Vi_tmp.pivots;

  }
  Minfo &Vi = fpsi->Vi;
  dVector uh(n1_wk, q1g*q2g);
  uh = from;
  // In-place transform from nodal to modal on the side.
  LU_solve(Vi.mat, Vi.pivots, uh);

  // Filter higher order modal coefficients by copying only lower order.
  dMatrix Fh(   uh,q1g,q2g);
  dMatrix  U(n2_wk,q1, q2 );
  for (Ordinal i=0; i<q1; i++) {
    for (Ordinal j=0; j<q2; j++) {
      U[i][j] = Fh[i][j];
    }
  }

  // In-place transform from reduced modal to modal on the side.
  const dMatrix &phia = fpsi->Ga;
  const dMatrix &phib = fpsi->Gb;
  dMatrix F (   to, q1,q2);
  dMatrix wk(n1_wk, q1,q2);
  matmult('T', phia, U, wk);   // wk[qa][Lb] = (Ba[La][qa])^T * Fh[La][Lb]
  matmult(wk, phib, F);         //  F[qa][qb] = wk[qa][Lb] * Bb[Lb][qb]
}
}

/// Interpolate from side to interior quadrature
void SpectralHex::interpolate_from_side(const Ordinal sid,
                                        const dVector &from,
                                        dVector &to) const {
#ifdef DGM_SIDE_FLUX_TO_VOLUME
  static const bool sum_to_volume=true;
#else
  static const bool sum_to_volume=false;
#endif

  //  cout << "SpectralHex::interpolate_from_side(), sid = " << sid << endl;
  Ordinal q1=0, q2=0;

  // from
  Ordinal q1g = face[sid].q1();
  Ordinal q2g = face[sid].q2();

  // to
  side_to_size(q1, q2, sid);

  dMatrix *im1, *im2;

  if (sum_to_volume && q1*q2 < q1g*q2g) {
    var_p_lift(q1, q2, face[sid], from, n1_wk, n2_wk, to);
  } else { 
    im1 = get_interpolation_matrix(q1, q1g, Interp::GL2GL);    // to, from
    im2 = get_interpolation_matrix(q2, q2g, Interp::GL2GL);    // to, from
    dMatrix wk;
    wk.exclusive_alias(n1_wk,q1,q2g);             // use n1_wk storage here
    dMatrix From( const_cast<dVector&>(from), q1g, q2g );
    dMatrix To( to, q1, q2 );
    matmult( *im1, From, wk );
    matmult( wk, 'T', *im2, To );
  }
}

/// Computes geometric factors for the Element Sides
/** Done once at startup so it is ok to interpolate every face once. */
void SpectralHex::compute_side_geometry() {
  // cout << "SpectralHex::compute_side_geometry(), Eid = "<< gid() << endl;
  Ordinal q1=0, q2=0;
  sigma(0.0);
  for (Ordinal i=0; i<nFaces(); i++) {
    side_to_size(q1, q2, i);
    dVector wk;
    wk.exclusive_alias(n2_wk,q1*q2);
#if 1
    switch(i) {
    case 0:
      get_side(geom->tx,i,wk);                   // wk at Gauss-Lobatto points
      interpolate_to_side( i, wk, side[i]->nx());// interpolate to Gauss-Lobatto
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
      interpolate_to_side( i, wk, side[i]->nx());// interpolate to Gauss-Lobatto
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
      interpolate_to_side( i, wk, side[i]->nx());// interpolate to Gauss-Lobatto
      get_side(geom->ry,i,wk);
      interpolate_to_side( i, wk, side[i]->ny());
      get_side(geom->rz,i,wk);
      interpolate_to_side( i, wk, side[i]->nz());
      break;
    case 3:
      get_side(geom->sx,i,wk);                   // wk at Gauss-Lobatto points
      interpolate_to_side( i, wk, side[i]->nx());// interpolate to Gauss-Lobatto
      get_side(geom->sy,i,wk);
      interpolate_to_side( i, wk, side[i]->ny());
      get_side(geom->sz,i,wk);
      interpolate_to_side( i, wk, side[i]->nz());
      break;
    case 4:
      get_side(geom->rx,i,wk);                   // wk at Gauss-Lobatto points
      interpolate_to_side( i, wk, side[i]->nx());// interpolate to Gauss-Lobatto
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
      interpolate_to_side( i, wk, side[i]->nx());// interpolate to Gauss-Lobatto
      get_side(geom->ty,i,wk);
      interpolate_to_side( i, wk, side[i]->ny());
      get_side(geom->tz,i,wk);
      interpolate_to_side( i, wk, side[i]->nz());
      break;
    }

    dVector interior_J(side[i]->qtot());         // Gauss-Lobatto points
    get_side(geom->J,i,wk);
    interpolate_to_side( i, wk, interior_J );    // Gauss-Lobatto points

#else // Constant P requires no interpolation

    switch(i) {
    case 0:
      get_side(geom->tx,i,side[i]->nx());
      scale( -1.0, side[i]->nx());
      get_side(geom->ty,i,side[i]->ny());
      scale( -1.0, side[i]->ny());
      get_side(geom->tz,i,side[i]->nz());
      scale( -1.0, side[i]->nz());
      break;
    case 1:
      get_side(geom->sx,i,side[i]->nx());
      scale( -1.0, side[i]->nx());
      get_side(geom->sy,i,side[i]->ny());
      scale( -1.0, side[i]->ny());
      get_side(geom->sz,i,side[i]->nz());
      scale( -1.0, side[i]->nz());
      break;
    case 2:
      get_side(geom->rx,i,side[i]->nx());
      get_side(geom->ry,i,side[i]->ny());
      get_side(geom->rz,i,side[i]->nz());
      break;
    case 3:
      get_side(geom->sx,i,side[i]->nx());
      get_side(geom->sy,i,side[i]->ny());
      get_side(geom->sz,i,side[i]->nz());
      break;
    case 4:
      get_side(geom->rx,i,side[i]->nx());
      scale( -1.0, side[i]->nx());
      get_side(geom->ry,i,side[i]->ny());
      scale( -1.0, side[i]->ny());
      get_side(geom->rz,i,side[i]->nz());
      scale( -1.0, side[i]->nz());
      break;
    case 5:
      get_side(geom->tx,i,side[i]->nx());
      get_side(geom->ty,i,side[i]->ny());
      get_side(geom->tz,i,side[i]->nz());
      break;
    }

    dVector interior_J(side[i]->qtot());         // Gauss points
    get_side(geom->J,i,interior_J);

#endif

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
#if 1
    dvsqrt(wk,wk);
    // interpolate to Gauss points
    interpolate_to_side( i, wk, side[i]->J() );
#else
    // Constant p
    dvsqrt(wk,side[i]->J()); // TMS
#endif

    // Save off interior_Jcoefficients
    side[i]->J_orig().resize(side[i]->J().size());
    side[i]->J_orig()      = side[i]->J();
    side[i]->J_scale().resize(side[i]->qtot());
    side[i]->J_scale() = interior_J;

    // divide the surface Jacobian by the interior Jacobian
    dvdiv( interior_J, side[i]->J() );

    // WARNING: This is done so that you can use an interior integration to
    // perform the surface integration.  For this to work you must use an
    // interior quadrature rule that includes the boundaries and you must
    // divide the side contributions by the integration weight in the other
    // direction(s).

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

/// Get the coordinates on a specified side //TMS
void SpectralHex::get_side_coordinates( const Ordinal sid, Point *pside )
const {
  //cout << "SpectralHex::get_side_coordinates()!" << endl;
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
#if 1
    get_side(C->x,sid,wk);
    interpolate_to_side( sid, wk, px );
    get_side(C->y,sid,wk);
    interpolate_to_side( sid, wk, py );
    get_side(C->z,sid,wk);
    interpolate_to_side( sid, wk, pz );
#else
    get_side(C->x,sid,px);
    get_side(C->y,sid,py);
    get_side(C->z,sid,pz);
#endif
    for(Ordinal i=0; i<face[sid].qtot(); i++)
      pside[i] = Point(px[i],py[i],pz[i]);
    break;
  default:
    cerr << "SpectralHex::_side_coordinates illegal edge id." << endl;
    DGM::Comm::World->exit();
    break;
  }
}

// not ok
void SpectralHex::forward_transform_side(dVector &f, dVector &fh) {
  DGM_UNDEFINED;
//  dVector &wa=psi->wa;
//  fh.resize(L()-2);
//  // subtract off vertices
//  daxpy( -f[0], psi->vertMode(0).a, f );
//  daxpy( -f[qa-1], psi->vertMode(1).a, f);
//  // inner product
//  dvmul( wa, f );
//  for (Ordinal i=0; i<L()-2; i++)
//    fh[i] = dot( psi->edgeMode(0,1).a, f );
//
//  if (L()-2) solve_1d_mass_matrix(fh);
}

// not ok
void SpectralHex::solve_1d_mass_matrix(dVector &fh) const {
  //  cout << "SpectralHex::solve_1d_mass_matrix(dVector &fh) const" << endl;
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
void SpectralHex::get_1d_mass_matrix(Minfo &M1d) const {
    cout << "SpectralHex::get_1d_mass_matrix(Minfo &M1d) const" << endl;
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

/// Compute a integral of supplied data, f, on specified side //TMS
Scalar SpectralHex::compute_side_integral( dVector &f, Ordinal sid ) const {
  // cout << "SpectralHex::compute_side_integral(dVector &, int) for Eid = "
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
  // dvmul( wk, f ); // TMS (Constant P)
  // cout << " J * f = " << endl << f << endl;
  static dVector w;
  if (w.size() != (Ordinal)qsid) {
    w.resize(qsid);
    w = 1.0;
    dMatrix W(w,q1g,q2g);
    dVector wa(q1g);
    dVector za(wk,q1g);
    zwgll(za,wa);
    for(Ordinal j=0; j<q2g; j++) {
      dSlice column(W.column(j));
      dvmul( wa, column );
    }
    dVector wb(q2g);
    dVector zb(wk,q2g);
    zwgll(zb,wb);
    for(Ordinal i=0; i<q1g; i++) {
      dVector row(W.row(i));
      dvmul( wb, row );
    }
  }
  const Scalar I = dot( f, w );
  // cout<<"Eid = " << this->id << ", Sid = " << sid << ", I = " << I << endl;
  return I;
}

/// Computes the side measure (total side area for a SpectralHex)
Scalar SpectralHex::compute_side_measure() const {
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


void transform_backward(dVector &fh, dVector &f, const Basis *psi) {
  // This has not been changed yet!  //TMS
  const dMatrix &phia = psi->Ga;
  const dMatrix &phib = psi->Gb;
  const dMatrix &phic = psi->Gc;
  const Ordinal L  = phia.rows();
  const Ordinal qa = phia.cols();
  const Ordinal qb = phib.cols();
  const Ordinal qc = phic.cols();

  dVector Lwk (qa*L*L);
  dVector Lwk2(qa*qb*L);

  dMatrix H( Lwk, qa, L*L );
  dMatrix Ha;
  dMatrix Fh( fh, L, L*L );
  matmult( 'T', phia, Fh, H );
  for (Ordinal i=0; i<qa; ++i) {
    H.alias( Lwk, i*L*L, L, L );
    Ha.alias( Lwk2, i*qb*L, qb, L );
    matmult( 'T', phib, H, Ha );
  }
  dMatrix F( f, qa*qb, qc );
  Ha.alias( Lwk2, qa*qb, L);
  matmult( Ha, phic, F );
}

void subside_lift (dVector       &in,
                   const Element *const el_U,
                   const Element *const el_F,
                   const Ordinal side,
                   const char     dir) {
  const Basis  *psi = el_U->psi;
  const Ordinal L  = psi->Ga.rows();
  const Ordinal qa = psi->Ga.cols();
  const Ordinal qb = psi->Gb.cols();
  const Ordinal qc = psi->Gc.cols();
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

    dVector h(L* L* L); h=0;
    if (1!=q1 && 1==q2) BaseHex::triangle_lift( h, f, side, Us, psi, true);
    else if (Us->subside_self_simular_to_side())
                            BaseHex::quad_lift( h, f, side, Us, psi, true);
    else        BaseHex::non_self_simular_lift( h, f, side, Us, psi, true);


    for (Ordinal i=0; i<L*L*L; ++i) fh(i) += h(i);
  }
  dVector In(qa*qb*qc); In=0;
  transform_backward(fh, In, psi);
  for (Ordinal i=0; i<qa*qb*qc; ++i) in[i] += In[i];
}
}  // anonymous namespace

void SpectralHex::local_lift(dVector &in,
                             const Element *const F, 
                             const Ordinal side,
                             const Scalar *W,
                             const char dir) const {

  const Element *const U = this;

  dVector f, fi;
  dMatrix In, Fi;

  f.alias(g1_wk, U->side[side]->qtot());
  if (F)
    dvsub( F->side[side]->u, U->side[side]->u, f );
  else
    f = U->side[side]->u;
  dvmul( U->side[side]->J(), f);
  if      (dir == 'x') dvmul( U->side[side]->nx(), f );
  else if (dir == 'y') dvmul( U->side[side]->ny(), f );
  else if (dir == 'z') dvmul( U->side[side]->nz(), f );

  switch (side) {
  // Side 0
  case 0: {
    if (U->side[side]->qtot() != qa*qb) {
      fi.alias(g2_wk, qa*qb );
      interpolate_from_side( side, f, fi );
      In.alias(in,qa*qb,qc);
      daxpy( W[0], fi, In.column(0) );
    } else {
      In.alias(in,qa*qb,qc);
      daxpy( W[0], f, In.column(0) );
    }
  }
  break;

  // Side 1
  case 1: {
    if (U->side[side]->qtot() != qa*qc) {
      fi.alias(g2_wk, qa*qc );
      interpolate_from_side( side, f, fi );
      Fi.alias(fi, qa, qc);
      for (Ordinal i=0; i<qa; i++) {
        In.alias(in, i*qb*qc, qb, qc);
        dVector Fi_row(Fi.row(i));
        dVector In_row(In.row(0));
        daxpy( W[1], Fi_row, In_row );
      }
    } else {
      Fi.alias(f, qa, qc);
      for (Ordinal i=0; i<qa; i++) {
        In.alias(in, i*qb*qc, qb, qc);
        dVector Fi_row(Fi.row(i));
        dVector In_row(In.row(0));
        daxpy( W[1], Fi_row, In_row );
      }
    }
  }
  break;

  // Side 2
  case 2: {
    if (U->side[side]->qtot() != qb*qc) {
      fi.alias(g2_wk, qb*qc );
      interpolate_from_side( side, f, fi );
      In.alias(in,qa,qb*qc);
      dVector In_row_qa(In.row(qa-1));
      daxpy( W[2], fi, In_row_qa );
    } else {
      In.alias(in,qa,qb*qc);
      dVector In_row_qa(In.row(qa-1));
      daxpy( W[2], f, In_row_qa );
    }
  }
  break;

  // Side 3
  case 3: {
    if (U->side[side]->qtot() != qa*qc) {
      fi.alias(g2_wk, qa*qc );
      interpolate_from_side( side, f, fi );
      Fi.alias(fi, qa, qc);
      for (Ordinal i=0; i<qa; i++) {
        In.alias(in, i*qb*qc, qb, qc);
        dVector Fi_row(Fi.row(i));
        dVector In_row(In.row(qb-1));
        daxpy( W[3], Fi_row, In_row );
      }
    } else {
      Fi.alias(f, qa, qc);
      for (Ordinal i=0; i<qa; i++) {
        In.alias(in, i*qb*qc, qb, qc);
        dVector Fi_row(Fi.row(i));
        dVector In_row(In.row(qb-1));
        daxpy( W[3], Fi_row, In_row );
      }
    }
  }
  break;

  // Side 4
  case 4: {
    if (U->side[side]->qtot() != qa*qc) {
      fi.alias(g2_wk, qb*qc );
      interpolate_from_side( side, f, fi );
      In.alias(in,qa,qb*qc);
      dVector In_row_0(In.row(0));
      daxpy( W[4], fi, In_row_0 );
    } else {
      In.alias(in,qa,qb*qc);
      dVector In_row_0(In.row(0));
      daxpy( W[4], f, In_row_0 );
    }
  }
  break;

  // Side 5
  case 5: {
    if (U->side[side]->qtot() != qa*qb) {
      fi.alias(g2_wk, qa*qb );
      interpolate_from_side( side, f, fi );
      In.alias(in,qa*qb,qc);
      daxpy( W[5], fi, In.column(qc-1) );
    } else {
      In.alias(in,qa*qb,qc);
      daxpy( W[5], f, In.column(qc-1) );
    }
  }
  break;
  }
}

/// Computes the surface term (lifted) for a DG method
void SpectralHex::lift(const Element *const F, dVector &in, const char dir) const {
  // cout << "SpectralHex::lift for Eid = " << gid() << endl;

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
void SpectralHex::get_derivative_matrix() {
  Dentry key(qa,qb,qc);
  DerivDB::iterator p = ddb.entry.find(key);
  if ( p == ddb.entry.end() ) {
    D.reset(new Dinfo);
    //cout << "SpectralHex::make_derivative_matrix()" << endl;
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
void SpectralHex::gradient( const dVector &f, dVector &fx, dVector &fy,
                            dVector &fz ) const {
  // cout << "SpectralHex::gradient( const dVector &, dVector &, dVector &, "
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
void SpectralHex::gradient( const dVector &f, dVector &df, char dir) const {
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
    cerr << "SpectralHex::gradient:  illegal direction " << dir << "." << endl;
    DGM::Comm::World->exit(DGM::FAILURE);
    break;
  }
}

/// Compute the local gradient on the master element
void SpectralHex::local_gradient( const dVector &f, dVector &fr, dVector &fs,
                                  dVector &ft) const {
  // cout << "SpectralHex::local_gradient()" << endl;

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
void SpectralHex::tecplot(FILE *fp) {
  //  cout << "SpectralHex::tecplot for element = " << gid() << endl;
  int tnsf = 0;
  if (state == Transform) {
    tnsf = 1;
    backward_transform();
  }
  fprintf(fp,"ZONE T=\"Zone%llu\", ",(unsigned long long)gid());
  fprintf(fp,"I=%llu, J=%llu, K=%llu,  F=POINT\n",(unsigned long long)qa,
          (unsigned long long)qb,(unsigned long long)qc);
  for (Ordinal k=0; k<qc; k++) {
    for (Ordinal j=0; j<qb; j++) {
      for (Ordinal i=0; i<qa; i++) {
        const Ordinal q = k + j * qc + i*qc*qb;
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

}

/// Output requested element information to a file
void SpectralHex::binaryOutput(FILE *fp, const OutputType flag) const {
  const Ordinal Nel = (qa-1)*(qb-1)*(qc-1);  // Number of sub-elements
  if (state == Transform)
    throw DGM::exception("SpectralHex::output called when in transform space");
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
    error("Illegal output type requested in SpectralHex::binaryOutput");
    break;
  }
}

/// Output requested element information to a file
streamoff SpectralHex::binaryLength(const OutputType flag) const {
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
    error("Illegal output type requested in SpectralHex::binaryLength");
    break;
  }
  error("Fell through case statement in SpectralHex::binaryLength");
  return 0;
}

/// Dump the Element storage to a file
void SpectralHex::output(FILE *fp, const char flag) const {
  if (state == Transform)
    error("SpectralHex::output called when in transform space");
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
    for (Ordinal k=0, q=8; k<qc-1; k++)
      for (Ordinal i=0; i<qa-1; i++)
        for (Ordinal j=0; j<qb-1; j++) {
          if (c++%5==0) fprintf(fp,"\n");
          fprintf(fp,"%llu ",(unsigned long long)q);
          q+=8;
        }
    break;
  default:
    error("Illegal flag in SpectralHex::output(), flag = "+asString(flag));
    break;
  }
}

//============================================================================
//                        Norm and Error routines
//============================================================================

/// Compute the infinity norm (maximum of the absolute value)
Scalar SpectralHex::norm_Linf() const {
  return norm_inf(u);
}

/// Compute the L2 norm squared
void SpectralHex::norm_L2(Scalar *L2, Scalar *volume) const {
  //  cout << "SpectralHex::norm_L2" << endl;
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
Scalar SpectralHex::norm_L2() const {
  Scalar L2, volume;
  norm_L2( &L2, &volume );
  return sqrt(L2/volume);
}

/// Computes the H1 norm squared on the Element
void SpectralHex::norm_H1(Scalar *H1, Scalar *volume) const {
  // cout << "SpectralHex::norm_H1" << endl;

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
Scalar SpectralHex::norm_H1() const {
  Scalar H1, volume;
  norm_H1( &H1, &volume );
  return sqrt(H1/volume);
}

/// Integrates the data stored in the Element and optionally the volume
Scalar SpectralHex::integrate( Scalar *vol ) const {
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
Scalar SpectralHex::integrate(const dVector &v, Scalar *vol) const {
  //  cout << "SpectralHex::integrate(...)" << endl;
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
void SpectralHex::plane_average() {
  DGM_UNDEFINED;
//#if 1
//  Ordinal i;
//  forward_transform();
//  for (i=1; i<L(); i++) {
//    for (Ordinal j=0; j<L(); j++) {
//      for (Ordinal k=0; k<L(); k++) {
//        Ordinal n = k + j*L() + i*L()*L();
//        uh[n] = 0;
//      }
//    }
//  }
//  i=0;
//  for (Ordinal j=1; j<L(); j++) {
//    for (Ordinal k=0; k<L(); k++) {
//      Ordinal n = k + j*L() + i*L()*L();
//      uh[n] = 0;
//    }
//  }
//  backward_transform();
//#else
//  // This is wrong since the variable quadrature mesh is not accounted for!
//  dVector avg(qc, 0.0);
//  dArray U(u,qa,qb,qc);
//  for(Ordinal i=0; i<qa; i++) {
//    for (Ordinal j=0; j<qb; j++) {
//      for (Ordinal k=0; k<qc; k++) {
//        avg[k] += U[i][j][k];
//      }
//    }
//  }
//  scale( 1.0/(qa*qb), avg);
//  for(Ordinal i=0; i<qa; i++) {
//    for (Ordinal j=0; j<qb; j++) {
//      for (Ordinal k=0; k<qc; k++) {
//        U[i][j][k] = avg[k];
//      }
//    }
//  }
//#endif
}

void SpectralHex::get_weight_props(Topology::ElementType& e, bool& c,
                                   Ordinal& porder) const {
  e = Topology::SpectralHex;
  c = true;                    // assume element is affine
  if (curve.get()) c = false;  // non-affine element
  porder = pOrder();
}

/// Returns the relative cost of this element's computations
/** This is a first step towards having a self tuning, load balancing
    code. See the more detailed comments in Quad.cpp. */
int SpectralHex::get_weight() const {
#ifdef HEX_NS_WEIGHTS
  // Weights for Navier-Stokes
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
#elif HEX_DERIVED_REDSKY_WEIGHTS
  // Weights for RedSky for derived physics
  static Ordinal Pmax = 10;
  static int Weight[11][2] = { {100,  104},
                               {139,  153},
                               {194,  243},
                               {297,  416},
                               {436,  955},
                               {643,  2291},
                               {902,  5397},
                               {1284,  13846},
                               {1764,  19153},
                               {2374,  43765},
                               {3102,  58424} };
#else
  // Weights for Curie (Cray-XK6) for derived physics
  static Ordinal Pmax = 20;
  static int Weight[21][2] =
    { {100,   100},
      {13824, 13594},
      {16397, 16604},
      {20172, 20174},
      {25315, 25554},
      {31175, 31435},
      {39675, 40510},
      {46162, 48165},
      {59974, 61426},
      {72914, 76204},
      {94572, 98270},
      {106280, 111290},
      {142005, 148900},
      {164095, 170614},
      {202947, 214020},
      {239394, 250525},
      {277225, 293976},
      {351535, 370215},
      {437227, 460280},
      {473205, 486974},
      {564839, 591540} };
#endif
  int cflag = 0;
  if (curve.get()) cflag = 1;
  if (pOrder() > Pmax) {
    if (first_warn) {
      cout << "WARNING - SpectralHex::get_weight(): "
           << "pOrder (="<<pOrder()<<") > Pmax (="<<Pmax<<")"<< endl;
      first_warn = false;
    }
    return Weight[Pmax][cflag];
  } else
    return Weight[pOrder()][cflag];
}

/// Returns the Element measure (volume of a SpectralHex)
Scalar SpectralHex::compute_measure() const {
  //cout << "SpectralHex::compute_measure()" << endl;
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
Scalar SpectralHex::L2_inner_product(const Element *el, Scalar *vol) const {
  //cout << "SpectralHex::L2_inner_product" << endl;
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

/// Returns the L2 inner product between two prescribed data vectors
Scalar SpectralHex::L2_inner_product(const dVector& vh, const dVector& wh,
                                     Scalar *vol) const {
  // cout << "SpectralHex::L2_inner_product" << endl;
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
void SpectralHex::filter(const dVector &mask) {
  if (state == Physical) {
    DGM::Comm::World->cerr()
      << "SpectralHex::filter -- must be in transform space"<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  // apply filter transfer function to the modal storage of the element
  // cout<<"SpectralHex applying filter"<<endl;
  dvmul(mask,uh);
}

/// Isolate the small scales of the element's field
void SpectralHex::vms_isolate_small() {
  DGM_UNDEFINED;
//  forward_transform();
//  // zero the low modes
//  for (Ordinal i=0; i<VMS_Lc(); i++) {
//    for (Ordinal j=0; j<L(); j++) {
//      for (Ordinal k=0; k<L(); k++) {
//        Ordinal n = k + j*L() + i*L()*L();
//        uh[n] = 0.0;
//      }
//    }
//  }
//  // zero the low modes
//  for (Ordinal i=VMS_Lc(); i<L(); i++) {
//    for (Ordinal j=0; j<VMS_Lc(); j++) {
//      for (Ordinal k=0; k<L(); k++) {
//        Ordinal n = k + j*L() + i*L()*L();
//        uh[n] = 0.0;
//      }
//    }
//    for (Ordinal j=VMS_Lc();j<L();j++){
//      for (Ordinal k=0; k<VMS_Lc(); k++) {
//        Ordinal n = k + j*L() + i*L()*L();
//        uh[n] = 0.0;
//      }
//    }
//  }
//  backward_transform();
}

/// Isolate the small scales in transform space (to another field)
void SpectralHex::vms_isolate_small(dVector &full, dVector &small) {
  DGM_UNDEFINED;
//  forward_transform(full, full);
//  // full  == complete field,  small == small scale field
//  small=0.0;
//  // transfer the high modes
//  for (Ordinal i=VMS_Lc(); i<L(); i++) {
//    for (Ordinal j=VMS_Lc(); j<L(); j++) {
//      for (Ordinal k=VMS_Lc(); k<L(); k++) {
//        Ordinal n = k + j*L() + i*L()*L();
//        small[n] = full[n];
//      }
//    }
//  }
//  backward_transform(small,small);
//  backward_transform(full,full);
}

/// Isolate the small scales in transform space (inplace)
void SpectralHex::vms_isolate_small(dVector &small) {
  DGM_UNDEFINED;
//  forward_transform(small,small);
//  // small == small-scale field
//  // zero the low modes
//  for (Ordinal i=0; i<VMS_Lc(); i++) {
//    for (Ordinal j=0; j<L(); j++) {
//      for (Ordinal k=0; k<L(); k++) {
//        Ordinal n = k + j*L() + i*L()*L();
//        small[n] = 0.0;
//      }
//    }
//  }
//  // zero the low modes
//  for (Ordinal i=VMS_Lc(); i<L(); i++) {
//    for (Ordinal j=0; j<VMS_Lc(); j++) {
//      for (Ordinal k=0; k<L(); k++) {
//        Ordinal n = k + j*L() + i*L()*L();
//        small[n] = 0.0;
//      }
//    }
//    for (Ordinal j=VMS_Lc();j<L();j++){
//      for (Ordinal k=0; k<VMS_Lc(); k++) {
//        Ordinal n = k + j*L() + i*L()*L();
//        small[n] = 0.0;
//      }
//    }
//  }
//  backward_transform(small,small);
}

/// Zero modes less than p_inc
void SpectralHex::fine_scales(const int p_inc) {
  DGM_UNDEFINED;
  //cout << "SpectralHex::fine_scales(const int p)" <<endl;
//  Ordinal i, j, k, n;
//  bool needs_transform = false;
//  if (state == Physical) {
//    forward_transform();
//    needs_transform = true;
//  }
//  // lower-left Octant
//  for (i=0; i<L()-p_inc; i++) {
//    for (j=0; j<L()-p_inc; j++) {
//      for (k=0; k<L()-p_inc; k++) {
//        n = k + j*L() + i*L()*L();
//        uh[n] = 0.0;
//      }
//    }
//  }
//  if (needs_transform)
//    backward_transform();
}

/// Zero modes less than p_inc in supplied vector
void SpectralHex::fine_scales(const int p_inc, dVector &vh) {
  //cout << "SpectralHex::fine_scales(const int p, dVector &vh)" <<endl;
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
void SpectralHex::fine_scales_transform(const int p_inc, dVector &vh) const {
  DGM_UNDEFINED;
  //cout<<"SpectralHex::fine_scales_transform(const int p, dVector &vh)"<<endl;
//  Ordinal i, j, k, n;
//  forward_transform(vh,vh);
//  // lower-left Octant
//  for (i=0; i<L()-p_inc; i++) {
//    for (j=0; j<L()-p_inc; j++) {
//      for (k=0; k<L()-p_inc; k++) {
//        n = k + j*L() + i*L()*L();
//        vh[n] = 0.0;
//      }
//    }
//  }
//  backward_transform(vh,vh);
}

/// Set all modes except constant to zero
void SpectralHex::make_constant() {
  //DGM_UNDEFINED;
  //bool needs_transform = false;
  //if (state == Physical) {
  //  forward_transform();
  //  needs_transform = true;
  //}

  //nodal_to_modal(u, uh);
  L_forward_transform();

  Scalar uh0 = uh[0];
  uh = 0.0;
  uh[0] = uh0;

  //modal_to_nodal(uh, u);
  L_backward_transform();

  //if (needs_transform)
  //  backward_transform();
}

/// Zero all modes greater than np
void SpectralHex::low_modes(const Ordinal inp) {
  const Ordinal np = numeric_cast<Ordinal>(inp);
  if (np>=pOrder()) return;
  //DGM_UNDEFINED;

  Ordinal i, j, k, n;

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

  //modal_to_nodal(uh, u);
  L_backward_transform();


  //if (needs_transform)
  //  backward_transform();
}

void SpectralHex::nodal_to_modal(dVector &f, dVector &fh) {

  //cout << "SpectralHex::nodal_to_modal()" << endl;

  if (curve.get()) {
    const dVector &J = geom->J;
    dvmul( J, f );
  }

  dMatrix F(f,qa,qb*qc);
  dMatrix Fh(fh,qa*qb,qc);
  dMatrix MF(qa,qb*qc);
  dMatrix MMF(qa,qb*qc);
  dMatrix *M = get_interpolation_matrix(qa, qb, Interp::GL2M);

  matmult( *M, F, MF );

  for (Ordinal r=0; r<qa; ++r) {
    dMatrix mf( MF.row(r), qb, qc );
    dMatrix mmf( MMF.row(r), qb, qc );
    matmult( *M, mf, mmf );
  }

  dMatrix RHS( MMF.data(), qa*qb, qc );
  matmult( RHS, 'T', *M, Fh );
}

void SpectralHex::modal_to_nodal( dVector &fh, dVector &f) {

  //cout << "SpectralHex::modal_to_nodal()" << endl;

  dMatrix F(f,qa*qb,qc);
  dMatrix Fh(fh,qa,qb*qc);
  dMatrix MFh(qa,qb*qc);
  dMatrix MMFh(qa,qb*qc);
  dMatrix *M = get_interpolation_matrix(qa, qb, Interp::M2GL);

  matmult( 'T', *M, Fh, MFh );

  for (Ordinal r=0; r<qa; ++r) {
    dMatrix mf( MFh.row(r), qb, qc );
    dMatrix mmf( MMFh.row(r), qb, qc );
    matmult( 'T', *M, mf, mmf );
  }

  dMatrix RHS( MMFh.data(), qa*qb, qc );
  matmult( RHS, *M, F );
}

void SpectralHex::get_side_Ds(const int, const dVector& , dVector& ) const {
  error("SpectralHex::get_side_Ds(const int, const dVector& ,"
        "dVector&) undefined");
}

void SpectralHex::get_side_curvature(const int sid, dVector &dcurv) const {
  error("SpectralHex::get_side_curvature(const int, dVector& ) undefined");
}

/// Get the coordinates of straight side
void SpectralHex::get_straight_side_coordinates(const Ordinal face_id,
                                                dVector &x, dVector &y,
                                                dVector &z) const {
  const Ordinal q = side2size(face_id);
  x.resize(q); y.resize(q); z.resize(q);
  x = 0.0; y = 0.0; z = 0.0;
  dVector f(q);
  for (Ordinal i = 0; i < 4; ++i) {
    const Ordinal vn = vertex_num(face_id,i);
    side_mode(face_id,psi->vertMode(vn),f);
    daxpy(vert[vn]->x,f,x);
    daxpy(vert[vn]->y,f,y);
    daxpy(vert[vn]->z,f,z);
  }
  if(face_id >= 6)
    throw DGM::exception("SpectralHex: Illegal face ID = "+asString(face_id));
}

Ordinal SpectralHex::vertex_num(const Ordinal i, const Ordinal j) const {
  return v_num[i][j];
}

Ordinal SpectralHex::edge_num(const Ordinal i, const Ordinal j) const {
  return e_num[i][j];
}

/// Generate curved surface coordinates
/** \todo Implement generalized curvature. */
void SpectralHex::generate_curve() {
  // cout << "SpectralHex::generate_curve() for " << gid() << endl;
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
void SpectralHex::forward_transform_side(const Ordinal face_id,
                                         dVector &f, dVector &fh,
                                         dVector * fh_e) {
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
  for(j=0;j<4;++j) {
    for( dVector::size_type i = 0; i < fh_e[j].size(); ++i){
      side_mode(face_id, psi->edgeMode(e_num[face_id][j],i), tmp);
      daxpy(-fh_e[j][i], tmp, f);
    }
  }

  // finally take inner product
  for(i = 0; i < Le; ++i)
    for(j = 0; j < Le; ++j){
      side_mode(face_id, psi->faceMode(face_id,i,j), tmp);

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
void SpectralHex::add_Dirac_delta(const Ordinal qpt, const Scalar amp) {
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
    with amplitude equal amp.  The Point, p, must be within the SpectralHex
    element. */
void SpectralHex::add_Dirac_delta(const Point &p, const Scalar amp) {
  Scalar r, s, t;
  // First get the local coordinate on line
  if(!get_local_coordinates(p,r,s,t)) {
    DGM::Comm::World->cerr()<<
      "SpectralHex::Add_Dirac_delta: could not find (r,s,t)"<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  const Point q(r,s, t);
  return add_local_Dirac_delta(q,amp);
}

void SpectralHex::add_local_Dirac_delta(const Point &p, const Scalar amp) {
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
void SpectralHex::add_local_Dirac_delta(const vector<dMatrix> &M,
                                        const Scalar amp) {
  if (3!=M.size())
    error("SpectralHex::add_local_Dirac_delta: Incorrect matrix size.");
  if (M[0].rows() != M[1].rows() || M[0].rows() != M[2].rows())
    error("SpectralHex::add_local_Dirac_delta: Inconsistant matrix size.");
  if (M[0].cols() != qc || M[1].cols() != qb || M[2].cols() != qa)
    error("SpectralHex::add_local_Dirac_delta: Inconsistant matrix size.");

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
Scalar SpectralHex::interpolate_point(const Point &p) const {
  if (state != Physical) {
    cerr << "SpectralHex::interpolate_points -- not in physical space"<<endl;
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
Scalar SpectralHex::interpolate_local_point(const Point &p) const {
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

void SpectralHex::calculate_interpolation_matrices
 (vector<dMatrix> &M, const vector<Point>&ps) const {
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

void SpectralHex::apply_interpolation_matrices(dVector &V,
                                        const vector<dMatrix> &M) const{
  if (3!=M.size())
    error("SpectralHex::apply_interplation_matrices: Incorrect matrix size.");
  if (M[0].rows() != M[1].rows() || M[0].rows() != M[2].rows())
    error("SpectralHex::apply_interplation_matrices: Inconsistant matrix size.");
  Ordinal sqa = qa, sqb = qb, sqc = qc;
  if (M[0].cols() != sqc || M[1].cols() != sqb || M[2].cols() != sqa)
    error("SpectralHex::apply_interplation_matrices: Inconsistant matrix size.");

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
void SpectralHex::interpolate_points(const vector<Point> &ps,
                                     dVector &vals) const {
  if (state != Physical) {
    cerr << "SpectralHex::interpolate_points -- not in physical space"<<endl;
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
void SpectralHex::get_edge(Ordinal q1, Ordinal q2, Scalar *from,
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
    DGM::Comm::World->cerr() << "Illegal Edge id for SpectralHex element"
                             << endl;
    DGM::Comm::World->exit(DGM::FAILURE);
    break;
  }
}

/// \warning Use the Edge[0] basis information, possible problem [gqchen]
void SpectralHex::forward_transform_edge(dVector &f, dVector &fh) {
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
    // fh[i] += psi->edgeMode(edge_id,i).a[j+1]*f[j+1];
  }
  solve_1d_mass_matrix(fh); // for Edge modal
}

/// Side mass matrix for curved face modal
void SpectralHex::solve_2d_mass_matrix(dVector &fh) const {
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
void SpectralHex::get_2d_mass_matrix(Minfo &M2d) const {
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
void SpectralHex::J_backward_transform(dVector &fh, dVector &f) {
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
void SpectralHex::get_curved_coordinates() {
  cerr << "SpectralHex::get_curved_coordinates() is not implemented" << endl;
  DGM::Comm::World->exit(DGM::FAILURE);

  const Ordinal Le = L() - 2;
  C.reset( new Coord(qtot) );
  *C = 0;

  // it is very important to declare these in the correct order [SSC]
  dVector fh(nModes()), tmp;
  fh = 0;

  // SpectralHex map

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

  Ordinal n = 0;
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

  // SpectralHex map

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

  // SpectralHex map

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

void SpectralHex::compute_curved_geometry() {
  // cout << "SpectralHex::compute_curved_geometry() for element "
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

vector<dMatrix*> SpectralHex::get_interpolation_matrices() const {
  //cout << "SpectralHex::get_interpolation_matrices()" << endl;
  const Element *U = this;
  vector<dMatrix*> matrices;
  for (Ordinal i=0; i<6; ++i) {
    Ordinal q1(0), q2(0);
    side_to_size(q1, q2, i);
    const Ordinal q1g = U->face[i].q1();
    const Ordinal q2g = U->face[i].q2();
    dMatrix *im1, *im2;
    im1 = get_interpolation_matrix( q1, q1g, Interp::GL2GL);  // to, from
    im2 = get_interpolation_matrix( q2, q2g, Interp::GL2GL);  // to, from
    matrices.push_back(im1);
    matrices.push_back(im2);
  }
  return matrices;
}

void SpectralHex::fill_basis_shift_matrix(dMatrix &G) const {
  const Ordinal nModes = 8;
  const Ordinal Nvert = 8;
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
