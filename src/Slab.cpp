/** \file Slab.cpp
    \brief Slab Element implementation

    \warning Slab is not fully implemented or tested
*/

// System includes
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

/// Makes the kernel use the CBLAS routines instead of hand-coded loops
#define SLAB_USE_CBLAS

// DGM includes
#include "Comm.hpp"
#include "Slab.hpp"
#include "BaseLine.hpp"
#include "Polylib.tpp"
#include "FFT.hpp"

namespace DGM {

// define static storage
BasisDB Slab::bdb;

Ordinal Slab::Qmax = 0;
Ordinal Slab::Lmax = 0;
dVector Slab::g1_wk;
dVector Slab::Lwk;

Slab::Slab(const Size ID, const Ordinal P, const Ordinal Q,
           const vector<Point> &X, const Ordinal N_x, const Ordinal N_z,
           const Scalar L_x, const Scalar L_z) : Element(ID) {
  cout << "Slab constructor, eid = " << ID << endl;
  type = Basis::Ortho;
  nVerts(2);
  nEdges(2);
  nFaces(0);
  nSides(2);
  pOrder(P);
  L(P+1);
  nModes(P+1);
  Nx = N_x;
  Nz = N_z;
  Lx = L_x;
  Lz = L_z;

  qa = Q; qb = qc = 0;
  qtot = qa;

  make_workspace(qtot,nModes());

  // construct vertex data-structure
  vert.resize(nVerts());
  for (Ordinal i=0; i<nVerts(); i++) {
    vert[i].reset( new Vertex(i,lid(),X[i]) );
  }

  set_box();

  // Form the interior basis functions
  psi = get_basis(0);

  // setup the FFT
  fft.reset( new FFT(Nx,Nz) );

  // initial state is undefined
  state = Unallocated;

#ifndef DGM_CONTIGUOUS
  // allocate storage for the nodal coefficients
  u.resize(qtot);

  // set storage for the modal coefficients (aliased to nodal storage)
  uh.alias(u,nModes());
#endif

  // construct edge data-structure, only one "quadrature" point on a 1d "edge"
  const int qedg = 1;
  edge.reserve(nEdges());
  for (Ordinal i=0; i<nEdges(); i++) {
    Edge ed(i,this,nModes(),qedg,false);
    edge.push_back(ed);
    side.push_back( &(edge[i]) );
  }

  // collocation derivative matrix
  get_derivative_matrix();



  cout << "Finished slab constructor, eid = " << ID << endl;
}

// This should not allocate new space for P, M, etc.
Slab::Slab(const Slab *E) {
  cout << "Slab copy constructor for Eid = " << E->gid() << endl;

  // allocate storage for solution and derivative at quadrature points
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

// Destructor
Slab::~Slab() {
  // cout << "~Slab: eid= "<<id<<endl;
}

/// Make the basis for the Slab element
void Slab::make_basis(Basis *psi, const Basis::Type type, const int der=0) {
  cout << "Slab::make_basis" << endl;
  const Ordinal L=psi->L, qa=psi->qa;
  dVector &za=psi->za, &wa=psi->wa;

  zwgll(za,wa);                                  // Gauss-Lobatto-Legendre

  switch (type) {
  case Basis::Lagrange:
    psi->ba = Basis::make_Lagrange( L, za );
    psi->Ba.alias( psi->ba[0].data(), L, qa );
    psi->ga = Basis::make_Legendre( der, L, qa, za );
    psi->Ga.alias( psi->ga[0].data(), L, qa );
    break;
  case Basis::Ortho:
    psi->ba = Basis::make_Legendre( der, L, qa, za );
    psi->Ba.alias( psi->ba[0].data(), L, qa );
    psi->ga = Basis::make_Lagrange( L, za );
    psi->Ga.alias( psi->ga[0].data(), L, qa );
    break;
  default:
    throw DGM::exception("BaseLine unsupported basis type "+asString(type));
  }

  // setup modal access pointers to primary basis
  psi->mode.resize(L);
  for (Ordinal i=0; i<L; i++) psi->mode[i].a.alias( psi->ba[i] );

  // setup C^0 modified Jacobi basis
  psi->nVerts = 2;
  psi->nEdges = 1;
  psi->nFaces = 0;
  psi->mFace  = 0;
  psi->mIntr  = 0;

  // make the storage
  psi->amem.resize(qa*L);

  // reset the vert and edge maps for this element type
  BaseLine::VertMode *vm = new BaseLine::VertMode(psi);
  psi->vm.reset( vm );
  psi->em.reset( new BaseLine::EdgeMode(psi, vm) );

  // define polynomials in a-direction
  {
    // vertex modes
    dVector v0(psi->vertMode(0).a);
    dVector v1(psi->vertMode(1).a);
    subtract(1.0, za, v0);
    scale(0.5, v0);
    add(1.0, za, v1);
    scale(0.5, v1);
    // edge modes
    if (L>2) {
      dVector e0(psi->edgeMode(0,0).a);
      dvmul(v0, v1, e0);
      for (Ordinal i=1; i<L-2; i++) {
        dVector ei(psi->edgeMode(0,i).a);
        jacobf(za, ei, i, 1.0, 1.0);
        dvmul(e0, ei, ei);
      }
    }
  }
}

void Slab::get_mass_matrix() {
  cout << "Slab::get_mass_matrix" << endl;
  M.reset( new Minfo );
  M->mat.resize(nModes(),nModes());
  M->pivots.resize(nModes());

  dMatrix &phi = psi->Ba;
  dVector &w = psi->wa;
  dVector &J = geom->J;
  dVector wk(g1_wk,qtot);

#ifdef SLAB_USE_CBLAS
  for (Ordinal i=0; i<nModes(); i++) {
    std::copy( phi[i], phi[i]+phi.cols(), &wk[0] );  // fill wk
    dvmul( J, wk );              // wk *= J
    dvmul( w, wk );              // wk *= w
    dVector row( M->mat.row(i));
    mvmult( phi, wk, row );      // M[i] = phi[i][q] * wk[q]
  }
#else
  for (Ordinal i=0; i<nModes(); i++) {
    for (Ordinal j=0; j<nModes(); j++) {
      M->mat[i][j] = 0.0;
      for (Ordinal q=0; q<qa; q++)
        M->mat[i][j] += phi[i][q] * phi[j][q] * w[q] * J[q];
    }
  }
#endif
#ifdef DGM_CHOLESKY_MASS_MATRIX
  if (Cholesky_factor(M->mat) !=0) {
    cout << "Cholesky_factor() failed." << endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
#else
  if (LU_factor(M->mat, M->pivots) !=0) {
    cout << "LU_factor() failed." << endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
#endif
}

/// Collocation derivative matrix
void Slab::get_derivative_matrix() {
  D.reset( new Dinfo );
  D->Da.resize(qa,qa);
  D->Dat.resize(qa,qa);
  dgll(D->Da,D->Dat,psi->za);
}

/// Parse a function defined in a string an place on element
/** \todo Need to change. */
void Slab::fill(string function_string, Operation operation) {
  cout << "Slab::fill(string)" << endl;
  state = Physical;
  parser_init();
  Parser::VectorFunction f("x", "t", function_string );
  f.evaluate( C->x, u, 0.0, convert(operation) );
}

/// Get the Slab basis
Basis* Slab::get_basis(const int der=0) const {
  Basis* b;
#if 0
  ostringstream key;
  key << L() << "_" << der << "_" << qa << "_" <<
    qb <<  "_" << qc;                       // build the key
  BasisDB::iterator p = bdb.bases.find(key.str());
  if ( p == bdb.bases.end() ) {             // not found, make a new one
    b = new Basis(L(),qa,qb,qc,nModes());
    make_basis(b,der);
    bdb.bases[key.str()] = b;
  } else {                                  // found, return the basis
    b = p->second;
  }
  return b;
#else
  char buf[128];
  sprintf(buf,"%lld_%lld_%lld_%lld_%lld_%lld",
          (long long)type,(long long)L(),(long long)der,
          (long long)qa,(long long)qb,(long long)qc);
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
#endif
}

/// Compute the inner product against the basis
void Slab::inner_product() {
  cout << "Slab::inner_product for Eid = " << gid() << endl;
  inner_product(u, uh);
  state = Transform;
}

/// Compute the inner product agains the basis
void Slab::inner_product(dVector &f, dVector &fh) const {
  dMatrix &phi = psi->Ba;
  dVector &wa = psi->wa;
  dVector &J = geom->J;
  dVector tmp(Lwk,f.size());

  dvmul( J, f, tmp );
  dvmul( wa, tmp );
  mvmult( phi, tmp, fh );
}

void Slab::forward_transform() {
  if (state == Transform) {
    cerr << "Slab::transform -- already in transform space"<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  inner_product(u,uh);
  solve_mass_matrix(uh);
  state = Transform;
}

void Slab::forward_transform(dVector &f, dVector &fh) const {
  inner_product(f,fh);
  solve_mass_matrix(fh);
}

// To do this in-place requires scratch space
void Slab::backward_transform() {
  if (state == Physical) {
    cerr << "Slab::transform_to_physical -- already in physical space"<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  backward_transform(uh, u);
  state = Physical;
}

/** \note To do this in-place requires scratch space. */
void Slab::backward_transform(dVector &fh, dVector &f) const {
  const dMatrix &phi = psi->Ba;
#ifdef SLAB_USE_CBLAS
  dVector tmp(Lwk,fh.size());
  tmp = fh;
  tmvmult( phi, tmp, f );
#else
  for (Ordinal q=0; q<qa; q++) {
    f[q] = 0.0;
    for (Ordinal i=0; i<nModes(); i++) {
      f[q] += fh[i] * phi[i][q];
    }
  }
#endif
}

/// Solve the mass matrix
void Slab::solve_mass_matrix(dVector &fh) const {
  // get_mass_matrix();  // commented out, since this method is not const
  // but it also not called in any other element implementation
  // chances are that this call is not needed
  // 2011/01/24   agerste
#ifdef DGM_CHOLESKY_MASS_MATRIX
  Cholesky_solve(M->mat, fh);
#else
  LU_solve(M->mat, M->pivots, fh);
#endif
}

void Slab::gradient( const dVector &f, dVector &fx, dVector &) const {
  dVector fr(g1_wk,qtot);
  mvmult( D->Da, f, fr );
  dvmul( geom->rx, fr, fx );
}

void Slab::gradient( const dVector &f, dVector &df, char dir) const {
  if (dir != 'x') { df = 0.0; return; }
  dVector fr(g1_wk,qtot);
  mvmult( D->Da, f, fr );
  dvmul( geom->rx, fr, df );
}

/// Compute coordinates of quadrature points
void Slab::get_coordinates() {
  C.reset( new Coord(qa) ); *C = 0;
  for (Ordinal n=0; n<nVerts(); n++) {
    for (Ordinal i=0; i<qa; i++) {
      C->x[i] += vert[n]->x * psi->vertMode(n).a[i];
    }
  }
}

void Slab::compute_geometry() {
  geom.reset( new Geometry( lid(), 1, nVerts(), qtot ) );
  Scalar detJ = pt5 * ( vert[1]->x - vert[0]->x );
  geom->J  = detJ;
  geom->rx = 1.0/detJ;
}

void Slab::compute_side_geometry() {
  //  cout << "Slab::compute_side_geometry(), Eid = "<< gid() << endl;
  for (Ordinal ed=0; ed<nEdges(); ed++) {
    Edge &e = edge[ed];
    switch(ed) {
    case 0:
      e.nx() = -1.0;
      e.ny() = 0.0;
      e.nz() = 0.0;
      break;
    case 1:
      e.nx() = 1.0;
      e.ny() = 0.0;
      e.nz() = 0.0;
      break;
    }
    e.J() = 1.0;
  }
}

/// Fill the sides
/** For the line element, if we use the Gauss-Lobatto over the element then
    the values at the edges are directly available. */
void Slab::fill_sides(const dVector &f) {
  edge[0].u[0] = f[0];
  edge[1].u[0] = f[qa-1];
}

/// Flux version of fill sides
void Slab::fill_sides(const dVector &fx, const dVector &) {
  edge[0].u[0] = fx[0] * edge[0].nx(0);
  edge[1].u[0] = fx[qa-1] * edge[1].nx(0);
}

/// Add in the surface flux contribution
void Slab::lift(const Element *const F, dVector &in, const char dir) const {
  const Element *const U = this;
  const dVector &wa = U->psi->wa;
  const dVector &J  = geom->J;

  if (dir == 'x') {
    in[0]    += edge[0].nx(0) * (F->edge[0].u[0] - U->edge[0].u[0]) /
      ( wa[0] * J[0] );
    in[qa-1] += edge[1].nx(0) * (F->edge[1].u[0] - U->edge[1].u[0]) /
      ( wa[qa-1] * J[qa-1] );
  } else {
    in[0]    += (F->edge[0].u[0] - U->edge[0].u[0]) / ( wa[0] * J[0] );
    in[qa-1] += (F->edge[1].u[0] - U->edge[1].u[0]) / ( wa[qa-1] * J[qa-1] );
  }
}

/// Output element to a Tecplot file
void Slab::tecplot(FILE *fp) {
  int tnsf = 0;
  if (state == Transform) {
    tnsf = 1;
    backward_transform();
  }
  dVector ux(qtot);
  gradient( u, ux, ux );
  for (Ordinal q=0; q<qtot; q++)
    fprintf(fp,"%15.8e %15.8e %15.8e\n",C->x[q],u[q],ux[q]);
  if (tnsf) forward_transform();
}

/** \todo Need to change. */
void Slab::project(PF pf) {
  // cout << "Slab::project(PF)" << endl;
#ifdef SLAB_USE_CBLAS
  state = Physical;
  for (Ordinal q=0; q<qa; q++) u[q] = pf((*C)[q]);
  forward_transform();
#else
  state = Physical;
  for (Ordinal i=0; i<nModes(); i++) {
    uh[i] = 0.0;
    for (Ordinal q=0; q<qa; q++) {
      uh[i] += phi[i][q] * wa[q] * pf((*C)[q]) * J[q];
    }
  }
#ifdef DGM_CHOLESKY_MASS_MATRIX
  Cholesky_solve(M, uh);
#else
  LU_solve(M, M_pivots, uh);
#endif
  state = Transform;
#endif
}

#undef SLAB_USE_CBLAS

} // namespace DGM
