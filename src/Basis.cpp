/** \file Basis.cpp
    \brief Implementation of the DGM Basis
    \author Scott Collis

    The DGM basis supports Lagrange, Legendre and Dubiner bases on tensor
    product elements as well as nodal bases on simplicial elements.

    The modal basis definitions and notation follows that described in:
    George Em Karniadakis and Spencer J. Sherwin, "Spectral/hp element
    methods for CFD", Oxford University Press, 1999.

    The nodal basis definitions follow that described in:
    Jan S. Hesthaven and Tim Warburton, "Nodal Discontinuous Galerkin Methods"
    Springer, 2008.
*/

// system includes
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

// DGM includes
#include "Comm.hpp"
#include "Types.hpp"
#include "Basis.hpp"
#include "Polylib.tpp"
#include "Utilities.hpp"

namespace DGM {

/// Basic constructor for a DGM::Basis
/** The constructor makes sets parameters and allocates memory for the
    Modes. It does not, however, allocate or set the basis on the Modes. */
Basis::Basis(const Ordinal L_, const Ordinal q_a, const Ordinal q_b,
             const Ordinal q_c, const Ordinal N_modes,
             const Ordinal q_nt) :  // q_nt = 0 if unspecified
  L(L_), nModes(N_modes), type(Ortho), qa(q_a), qb(q_b), qc(q_c), qnt(q_nt),
  nVerts(0), nEdges(0), nFaces(0), mFace(0), mIntr(0),
  ba(0), bbv(0), bb(0), bc(0), bnt(0), ga(0), gbv(0), gb(0), gc(0) {
#ifdef DGM_USE_BASIS_TIMERS
  static FunctionTimer timer(__PRETTY_FUNCTION__);
  FunctionSentry sentry(timer);
#endif

  // Each basis stores its weights and zeros
  za.resize(qa);
  if (qb) zb.resize(qb);
  if (qc) zc.resize(qc);
  if (qnt) {
    znt_r.resize(qnt);
    znt_s.resize(qnt);
    znt_t.resize(qnt);
  }

  wa.resize(qa);
  if (qb) wb.resize(qb);
  if (qc) wc.resize(qc);

  // Currently only correct for Line, Quad, and Hex elements
  Ba.resize(L,qa);
  if (qb) Bb.resize(L,qb);
  if (qc) Bc.resize(L,qc);

  // Only correct for NodalTri elements
  if (qnt) Bnt.resize(N_modes,N_modes);
}

//=============================================================================
//                         Basis helper routines
//=============================================================================

/** This is the matrix-vector version. */
void Basis::make_Legendre(const int der, const Ordinal L, const Ordinal,
                          const dVector &z, dMatrix &B) {
  // cout << "make_Legendre(int,Ordinal,Ordinal,dVector,dMatrix)" << endl;
#ifdef DGM_USE_BASIS_TIMERS
  static FunctionTimer timer(__PRETTY_FUNCTION__);
  FunctionSentry sentry(timer);
#endif
  if (der==0) {
    for (Ordinal i=0; i<L; i++) {
      jacobf(z, B[i], i, 0.0, 0.0 );   // P^(0,0)_k(z)
    }
  } else if (der==1) {
    for (Ordinal i=0; i<L; i++) {
      jacobd(z, B[i], i, 0.0, 0.0 );   // d/dz P^(0,0)_k(z)
    }
  } else if (der==2) {
    for (Ordinal i=0; i<L; i++) {
      jacobd2(z, B[i], i, 0.0, 0.0 );  // d^2/dz^2 P^(0,0)_k(z)
    }
  } else {
    DGM::Comm::World->cerr() << "Legendre der > 2 not implemented" << endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
#ifdef DGM_BASIS_NORM
  for (Ordinal i=0; i<L; i++) {
    dVector row(B.row(i));
    scale(sqrt(0.5*(2.0*i+1.0)),row);
  }
#endif
}

/** This is the vector version. */
dVector *Basis::make_Legendre(const int der, const Ordinal L, const Ordinal Q,
                              const dVector &z) {
  // cout << "make_Legendre(int,Ordinal,Ordinal,dVector)" << endl;
#ifdef DGM_USE_BASIS_TIMERS
  static FunctionTimer timer(__PRETTY_FUNCTION__);
  FunctionSentry sentry(timer);
#endif
  dVector *B;
  B = new dVector[L];                  // allocate storage
  dVector mem(L*Q);
  for (Ordinal i=0; i<L; i++) B[i].alias(mem,Q*i,Q);
  if (der==0) {
    for (Ordinal i=0; i<L; i++) {
      jacobf(z, B[i], i, 0.0, 0.0 );   // P^(0,0)_k(z)
    }
  } else if (der==1) {
    for (Ordinal i=0; i<L; i++) {
      jacobd (z, B[i], i, 0.0, 0.0 );  // d/dz P^(0,0)_k(z)
    }
  } else if (der==2) {
    for (Ordinal i=0; i<L; i++) {
      jacobd2(z, B[i], i, 0.0, 0.0 );  // d^2/dz^2 P^(0,0)_k(z)
    }
  } else {
    DGM::Comm::World->cerr() << "Legendre der > 2 not implemented" << endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
#ifdef DGM_BASIS_NORM
  for (Ordinal i=0; i<L; i++) scale(sqrt(pt5*(two*i+one)),B[i]);
#endif
  return B;
}

#ifdef DGM_VECTOR_DUBINER

/** Generate the Dubiner basis for Triangles. */
dVector **Basis::make_Dubiner(const Ordinal L, const Ordinal Q, dVector &z) {
  // cout << "make_Dubiner" << endl;
#ifdef DGM_USE_BASIS_TIMERS
  static FunctionTimer timer(__PRETTY_FUNCTION__);
  FunctionSentry sentry(timer);
#endif

  // allocate storage
  dVector **B;
  B = new dVector*[L];
  B[0] = new dVector[L*(L+1)/2];

  dVector mem(L*(L+1)/2*Q);

  // set the pointers
  for(Ordinal i=0, cnt=0; i<L; cnt+=L-i,++i)
    B[i] = B[0] + cnt;

  for(Ordinal i=0, cnt=0; i<L; ++i)
    for(Ordinal j=0; j<L-i; ++j,++cnt)
      B[i][j].alias( mem, Q*cnt, Q );

  // set the values
  B[0][0] = 1.0;
  for(Ordinal j = 1; j < L; ++j){
    jacobf(z,B[0][j],j,1.0,0.0);
  }

  if(L > 1){
    for(Ordinal k = 0; k < Q; ++k)
      B[1][0][k] = (1.0 - z[k])*0.5;
    for(Ordinal j = 1; j < L-1; ++j){
      jacobf(z,B[1][j],j,3.0,0.0);
      dvmul(B[1][0], B[1][j], B[1][j] );
    }
    for(Ordinal i = 2; i < L; ++i){
      dvmul(B[1][0], B[i-1][0], B[i][0]);
      for(Ordinal j = 1; j < L-i; ++j){
        jacobf(z,B[i][j],j,2.0*i+1.0,0.0);
        dvmul(B[i][0], B[i][j], B[i][j]);
      }
    }
  }

#ifdef DGM_BASIS_NORM
  // makes the basis (when used on a triangle, orthogonal)
  for(Ordinal i = 0; i < L; ++i)
    for(Ordinal j = 0; j < L-i; ++j)
      scale(sqrt((i+j+1.0)),B[i][j]);
#endif

  return B;
}

#else

/** Generate the Dubiner basis for Triangles. */
dMatrix *Basis::make_Dubiner(const Ordinal L, const Ordinal Q, dVector &z) {
  // cout << "make_Dubiner" << endl;
#ifdef DGM_USE_BASIS_TIMERS
  static FunctionTimer timer(__PRETTY_FUNCTION__);
  FunctionSentry sentry(timer);
#endif

  // allocate storage
  dMatrix *B;
  B = new dMatrix[L];

  // make memory contiguous
  dVector mem(L*(L+1)/2*Q);

  // set the matrices
  dVector tmp;
  for(Ordinal i=0, cnt=0; i<L; cnt+=(L-i)*Q, ++i) {
    tmp.alias( mem, cnt, (L-i)*Q );    // get the right chunk of memory
    B[i].alias( tmp, L-i, Q );         // make the matrix alias
  }

  // set the values
  B[0].row(0) = 1.0;
  for(Ordinal j = 1; j < L; ++j){
    jacobf(z,B[0][j],j,1.0,0.0);
  }

  if(L > 1){
    for(Ordinal k = 0; k < Q; ++k)
      B[1][0][k] = (1.0 - z[k])*0.5;
    for(Ordinal j = 1; j < L-1; ++j){
      jacobf(z,B[1][j],j,3.0,0.0);
      dVector B_1_j = B[1].row(j);
      dvmul(B[1].row(0), B[1].row(j), B_1_j );
    }
    for(Ordinal i = 2; i < L; ++i){
      dVector B_i_0 = B[i].row(0);
      dvmul(B[1].row(0), B[i-1].row(0), B_i_0 );
      for(Ordinal j = 1; j < L-i; ++j){
        jacobf(z,B[i][j],j,2.0*i+1.0,0.0);
        dVector B_i_j = B[i].row(j);
        dvmul(B[i].row(0), B[i].row(j), B_i_j );
      }
    }
  }

#ifdef DGM_BASIS_NORM
  // makes the basis (when used on a triangle, orthogonal)
  for(Ordinal i = 0; i < L; ++i)
    for(Ordinal j = 0; j < L-i; ++j) {
      dVector B_i_j = B[i].row(j);
      scale(sqrt((i+j+1.0)),B_i_j);
    }
#endif

  return B;
}

#endif

/** This is the vector version. */
dVector *Basis::make_NodalTri(const Ordinal L, const Ordinal nModes,
                              dVector &r, dVector &s) {
  // cout << "make_NodalTri(int)" << endl;
#ifdef DGM_USE_BASIS_TIMERS
  static FunctionTimer timer(__PRETTY_FUNCTION__);
  FunctionSentry sentry(timer);
#endif
  dVector *B;
  zwntri(r, s, Size(L-1));
  B = new dVector[nModes];
  dVector mem(nModes*nModes);
  dMatrix V(mem,nModes,nModes);
  for(Ordinal i=0; i<nModes; i++) B[i].alias(mem, nModes*i, nModes);
  fntri(L, nModes, r.ptr(), s.ptr(), V);
  return(B);
}

/** This is the vector version. */
dVector *Basis::make_NodalTet(const Ordinal L,
                              const Ordinal nModes,
                              dVector &r,
                              dVector &s,
                              dVector &t) {
  // cout << "make_NodalTet(int)" << endl;
#ifdef DGM_USE_BASIS_TIMERS
  static FunctionTimer timer(__PRETTY_FUNCTION__);
  FunctionSentry sentry(timer);
#endif
  dVector *B;
  Scalar *rp = r.data();
  Scalar *sp = s.data();
  Scalar *tp = t.data();
  zwntet(rp, sp, tp, Size(L-1));
  B = new dVector[nModes];
  dVector V(nModes*nModes);
  dMatrix M(V,nModes,nModes);
  // Note: dVector memory is reference counted and will not be
  // freed when V goes out of scope.
  for (Ordinal i=0; i<nModes; i++) B[i].alias(V, nModes*i, nModes);
  fntet(L, nModes, r.ptr(), s.ptr(), t.ptr(), M);
  return(B);
}

/** Make the trivial, Lagrange interpolator basis. */
dVector *Basis::make_Lagrange(const Ordinal L, dVector &z) {
  // cout << "make_Lagrange(...)" << endl;
#ifdef DGM_USE_BASIS_TIMERS
  static FunctionTimer timer(__PRETTY_FUNCTION__);
  FunctionSentry sentry(timer);
#endif
  dVector *B;
  B = new dVector[L];                  // allocate storage
  dVector mem(L*L);
  mem = zero;
  for (Ordinal i=0, cnt=0; i<L; cnt++, i++)
    B[i].alias(mem,L*cnt,L);
  for (Ordinal i=0; i<L; ++i) {
    B[i][i] = one;
  }
  return B;
}

} // namespace DGM
