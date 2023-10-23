/** \file  SpectralLine.cpp
    \brief SpectralLine element implementation
    \author Scott Collis
*/

// system includes
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <vector>
#ifdef DGM_USE_GENERAL_GHOSTING
#include <boost/serialization/export.hpp>
#endif
using namespace std;

/// Makes the kernel use the CBLAS routines instead of hand coded loops
#define SPECTRALLINE_USE_CBLAS

// boost includes
#include "boost/numeric/conversion/cast.hpp"
using boost::numeric_cast;

// DGM includes
#include "Comm.hpp"
#include "Polylib.tpp"
#include "SpectralLine.hpp"
#include "String.hpp"

#ifdef DGM_USE_GENERAL_GHOSTING
/// register class for serialization of polymorphic types
BOOST_CLASS_EXPORT_GUID(DGM::SpectralLine, "DGM::SpectralLine");
#endif

namespace DGM {

// Define static storage
BasisDB SpectralLine::bdb;           // define Basis database
SpectralLine::GeometryDB
  SpectralLine::gdb("SpectralLine"); // define Geometry database

Ordinal SpectralLine::Qmax = 0;
Ordinal SpectralLine::Lmax = 0;
dVector SpectralLine::g1_wk;
dVector SpectralLine::g2_wk;
dVector SpectralLine::g3_wk;
dVector SpectralLine::g4_wk;
dVector SpectralLine::g5_wk;
dVector SpectralLine::Lwk;

/// Primary constructor
SpectralLine::SpectralLine(const Ordinal ID, const Ordinal P,
                           const vector<Point> &X) :
  BaseLine(ID,Basis::Lagrange) {
  //cout << "SpectralLine constructor, eid = " << ID << endl;
  nVerts(2);
  nEdges(2);
  nFaces(0);
  nSides(2);
  pOrder(P);
  L(P+1);
  nModes(L());

  if (P==0) throw DGM::exception("Spectral elements must have P>0");

  qa = L(); qb = qc = 0;
  qtot = qa;

  make_workspace(qtot,nModes());

  // construct vertex data-structure
  vert.resize(nVerts());
  for (Ordinal i=0; i<nVerts(); i++){
    vert[i].reset( new Vertex(i,lid(),X[i]) );
  }

  set_box();

  // Form the interior basis functions
  psi = get_basis(0);

  // collocation derivative matrix
  get_derivative_matrix();

  // initial state is undefined
  state = Unallocated;

#ifndef DGM_CONTIGUOUS
  // allocate storage for the nodal coefficients
  u.resize(qtot);
  // set storage for the modal coefficients (aliased to nodal storage)
  uh.alias(u,nModes());
#endif

  // construct edge data-structure there is only one "quadrature" point on a
  // 1d "edge"
  int qedg = 1;
  edge.reserve(nEdges());
  for (Ordinal i=0; i<nEdges(); i++) {
    Edge ed(i,this,nModes(),qedg,true);
    edge.push_back(ed);
    side.push_back( &(edge[i]) );
  }
}

/// Copy constructor -- This should not allocate new space for P, M, etc.
SpectralLine::SpectralLine(const SpectralLine *E) {
  // cout << "SpectralLine copy constructor for Eid = " << E->id << endl;

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

/// Destructor
SpectralLine::~SpectralLine() {
  //cout << "~SpectralLine: eid= "<<id<<endl;
}

Basis* SpectralLine::get_basis(const int der=0) const {
  Basis *b;
  char buf[128];
  sprintf(buf,"%lld_%lld_%lld_%lld_%lld_%lld",
          (long long)type,(long long)L(),(long long)der,
          (long long)qa,(long long)qb,(long long)qc);
  const string key = buf;
  BasisDB::iterator p = bdb.bases.find(key);
  if ( p == bdb.bases.end() ) {             // not found, make a new one
    b = new Basis(L(),qa,qb,qc,nModes());
    make_basis(b,type,der);
    bdb.bases[key] = b;
    //cout << "Added basis with key = " << key << endl;
  } else {                                  // found, return the basis
    b = p->second;
  }
  return b;
}

/** Actually computes the inverse mass matrix. */
void SpectralLine::get_mass_matrix() {
  // cout << "SpectralLine::get_mass_matrix for element " << id << endl;
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
  for (Ordinal j=0; j<nModes(); j++) M->mat[0][j] = 1.0/M->mat[0][j];
}

void SpectralLine::get_mass_matrix(const dVector &x) {
  cout << "SpectralLine::get_mass_matrix(x) for element " << gid() << endl;
  DGM_UNDEFINED;
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
    DGM::Comm::World->error("Cholesky_factor() failed.");
#else
  if (LU_factor(M->mat, M->pivots) !=0)
    DGM::Comm::World->error("LU_factor() failed.");
#endif
  full_mass = true;
}

void SpectralLine::solve_mass_matrix(dVector &fh) const {
  // cout << "SpectralLine::solve_mass_matrix() for element " << gid() << endl;
  if (full_mass) {
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

void SpectralLine::normal_times_gradient_side( const dVector &f,
                                               const int sid,
                                               dVector &fsum ) const {
  DGM_UNDEFINED;
  const Ordinal nsd = 1;
  static const char vdir[1] = {'x'}; // direction vector
  dVector dfs( side[sid]->qtot() );
  dVector df(qtot);
  assert ( f.size() == df.size() );
  fsum = 0.0;
  dVector normal;
  for (Ordinal idim=0; idim<nsd; idim++) {
    if (idim==0) normal.alias(this->side[sid]->nx());
    this->gradient( f, df, vdir[idim]);
    load_side( df, sid, dfs );
    dvmul(normal, dfs);
    fsum += dfs;
  }
}

void SpectralLine::get_local_mass_matrix(const dVector &factor) {
  cout << "SpectralLine::get_local_mass_matrix(x) for element "<<gid()<<endl;
  DGM_UNDEFINED;
  // WARNING:  might be dangerous to reset the mass matrix to this new value
  Mloc.reset( new Minfo );
  Mloc->mat.resize(nModes(),nModes()); // pivots untouched
  dVector f(qtot);
  dVector fh(f,nModes());
  //full mass matrix
  for (Ordinal m=0; m<nModes(); m++) {
    fill( psi->mode[m], f );
    dvmul( factor, f );
    inner_product(f, fh);
    for (Ordinal n=0; n<nModes(); n++) Mloc->mat[m][n] = fh[n];
  }
}

void SpectralLine::get_local_derivative_matrix() {
  cout<<"SpectralLine::get_local_derivative_matrix for element "<<gid()<<endl;
  DGM_UNDEFINED;
  Dxloc.reset( new Minfo );
  Dxtloc.reset( new Minfo );
  Dxloc->mat.resize(nModes(),nModes());  // pivots untouched
  Dxtloc->mat.resize(nModes(),nModes()); // pivots untouched
  //
  // need to add additional work vectors
  dVector wk1(g2_wk,qtot);
  dVector wk2(g3_wk,qtot);
  dVector w3(nModes());
  //
  for (Ordinal j=0; j<nModes(); j++) {
    fill( psi->mode[j], wk1 );
    gradient(wk1,wk2); // grad(wk1) -> wk2
    inner_product(wk2,w3);// wk2 . (all psi's) -> w3
    for (Ordinal i=0; i<nModes(); i++) {
      Dxloc->mat[i][j] = w3[i];   // Dx  = \int (psi[m]) (psi[n])_{,x} dx
      Dxtloc->mat[j][i] = w3[i];  // Dxt = \int (psi[m])_{,x} (psi[n]) dx
    }
  }
}

void SpectralLine::get_local_derivative_matrix(const dVector & factor) {
  cout<<"SpectralLine::get_local_derivative_matrix for element "<<gid()<<endl;
  DGM_UNDEFINED;
  Dxloc.reset( new Minfo );
  Dxtloc.reset( new Minfo );
  Dxloc->mat.resize(nModes(),nModes());  // pivots untouched
  Dxtloc->mat.resize(nModes(),nModes()); // pivots untouched
  //
  // need to add additional work vectors
  dVector wk1(g2_wk,qtot);
  dVector wk2(g3_wk,qtot);
  dVector w3(nModes());
  //
  for (Ordinal j=0; j<nModes(); j++) {
    fill( psi->mode[j], wk1 );
    gradient(wk1,wk2); // grad(wk1) -> wk2
    dvmul( factor, wk2 ); // factor*wk2 -> wk2
    inner_product(wk2,w3);// wk2 . (all psi's) -> w3
    for (Ordinal i=0; i<nModes(); i++) {
      Dxloc->mat[i][j] = w3[i]; // Dx  = \int factor (psi[m]) (psi[n])_{,x} dx
      Dxtloc->mat[j][i] = w3[i]; // Dxt = \int factor (psi[m])_{,x} (psi[n]) dx
    }
  }
}

void SpectralLine::get_local_laplace_matrix() {
  cout<<"SpectralLine::get_local_derivative_matrix for element "<<gid()<<endl;
  DGM_UNDEFINED;
  DDloc.reset( new Minfo );
  DDloc->mat.resize(nModes(),nModes()); // pivots untouched
  // work vectors
  dVector f1(qtot);
  dVector dpsi_i(qtot);
  dVector dpsi_j(qtot);
  // get the geometry first
  dVector &wa = psi->wa;
  dVector &J = geom->J;
  dVector b(qtot);
  b = J;
  dvmul( wa, b );
  for (Ordinal i=0; i<nModes(); i++) {
    fill( psi->mode[i],f1);
    gradient(f1,dpsi_i);
    for (Ordinal j=0; j<nModes(); j++) {
      fill( psi->mode[j],f1);
      gradient(f1,dpsi_j);
      dvmul(dpsi_i,dpsi_j,f1);       // f1 = vh*wh
      DDloc->mat[i][j] = dot(b,f1);
    }
  }
}

void SpectralLine::get_local_laplace_matrix(const dVector & factor) {
  // cout<<"SpectralLine::get_local_derivative_matrix for element "<<id<<endl;
  DGM_UNDEFINED;
  DDloc.reset( new Minfo );
  DDloc->mat.resize(nModes(),nModes()); // pivots untouched
  // work vectors
  dVector f1(qtot);
  dVector dpsi_i(qtot);
  dVector dpsi_j(qtot);
  // get the geometry first
  dVector &wa = psi->wa;
  dVector &J = geom->J;
  dVector b(qtot);
  b = J;
  dvmul( wa, b );
  for (Ordinal i=0; i<nModes(); i++) {
    fill( psi->mode[i],f1);
    gradient(f1,dpsi_i);
    for (Ordinal j=0; j<nModes(); j++) {
      fill( psi->mode[j],f1);
      gradient(f1,dpsi_j);
      dvmul(dpsi_i,dpsi_j,f1);       // f1 = vh*wh
      dvmul(factor,f1);              // factor*f1 -> f1
      DDloc->mat[i][j] = dot(b,f1);
    }
  }
}

//=============================================================================

/// Parse a function defined in a string and place on element
void SpectralLine::fill(string function_string, Operation operation) {
  state = Physical;
  parser_init();
  Parser::VectorFunction f("x", "t", function_string );
  f.evaluate( C->x, u, 0.0, convert(operation) );
}

/// Fill element with a mode
void SpectralLine::fill(Mode &v) {
  // cout << "SpectralLine::fill(Mode &)" << endl;
  for (Ordinal i=0; i<qa; i++)
    u[i] = v.a[i];
  state = Physical;
}

/// Fill a vector with a mode
void SpectralLine::fill(Mode &v, dVector &f) const {
  // cout << "SpectralLine::fill(Mode &, dVector &) const" << endl;
  for (Ordinal i=0; i<qa; i++)
    f[i] = v.a[i];
}

/// Fill element with a random polynomial
void SpectralLine::random() {
  // cout << "SpectralLine::random()" << endl;
  state = Physical;
  for (Ordinal i=0; i<L(); i++) uh[i] = Element::random(-one,one);
}

void SpectralLine::inner_product() {
  // cout << "SpectralLine::inner_product for Eid = " << id << endl;
  inner_product(u, uh);
  state = Transform;
}

void SpectralLine::inner_product(dVector &f, dVector &fh) const {
  dMatrix &phi = psi->Ba;
  // cout << "inner_product with phi = \n" << phi << endl;
  dVector tmp(Lwk,f.size());
#ifdef DGM_USE_WJ
  dvmul( geom->wJ, f, tmp );
#else
  dVector &wa = psi->wa;
  dVector &J = geom->J;
  dvmul( J, f, tmp );
  dvmul( wa, tmp );
#endif
  mvmult( phi, tmp, fh );
}

void SpectralLine::forward_transform() {
  if (state == Transform) {
    cerr<<"SpectralLine::forward_transform -- already in transform space"<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  //forward_transform(u,uh);
  state = Transform;
}

void SpectralLine::forward_transform(dVector &f, dVector &fh) const {
  //inner_product(f,fh);
  //solve_mass_matrix(fh);
}

void SpectralLine::forward_transform(Element *F, Element *) {
  //cout << "SpectralLine::forward_transform(*F,*)" << endl;
  if (state == Transform) {
    cerr << "SpectralLine::transform -- already in transform space"<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  //inner_product(u,uh);
  //F->solve_mass_matrix(uh);  // Use element F's Mass matrix
  state = Transform;
}

/** \note To do this in-place requires scratch space. */
void SpectralLine::backward_transform() {
  if (state == Physical) {
    DGM::Comm::World->cerr()<<"SpectralLine::backward_transform -- already in "
      "physical space"<<endl;
    DGM::Comm::World->exit();
  }
  //backward_transform(uh, u);
  state = Physical;
}

/** \note To do this in-place requires scratch space. */
void SpectralLine::backward_transform(dVector &fh, dVector &f) const {}

// compute coordinates of quadrature points
void SpectralLine::get_coordinates() {
  C.reset( new Coord(qa) ); *C = 0.0;
  for (Ordinal n=0; n<nVerts(); n++) {
    for (Ordinal i=0; i<qa; i++) {
      C->x[i] += vert[n]->x * psi->vertMode(n).a[i];
    }
  }
}

/** For the line element, if we use the Gauss-Lobatto over the element
    then the values at the edges are directly available. */
void SpectralLine::fill_sides(const Scalar f, const Operation operation) {
  switch (operation) {
  case Equal:
    edge[0].u[0] = f;
    edge[1].u[0] = f;
    break;
  case Add:
    edge[0].u[0] += f;
    edge[1].u[0] += f;
    break;
  case Subtract:
    edge[0].u[0] -= f;
    edge[1].u[0] -= f;
    break;
  case Multiply:
    edge[0].u[0] *= f;
    edge[1].u[0] *= f;
    break;
  case Divide:
    edge[0].u[0] /= f;
    edge[1].u[0] /= f;
    break;
  default:
    throw DGM::exception("Illegal operation in SpectralLine::fill_sides");
    break;
  }
}

/** For the line element, if we use the Gauss-Lobatto over the element
    then the values at the edges are directly available. */
void SpectralLine::fill_sides(const dVector &f) {
  edge[0].u[0] = f[0];
  edge[1].u[0] = f[qa-1];
}

// flux version
void SpectralLine::fill_sides(const dVector &f, const dVector &) {
  edge[0].u[0] = f[0] * edge[0].nx(0);
  edge[1].u[0] = f[qa-1] * edge[1].nx(0);
}

/// Interpolate physical space values "f" to the side Gauss Points
/** BUT store the result in vector g. */
void SpectralLine::load_side(const dVector &f, const Ordinal side_number,
                             dVector &g) const {
  if(side_number > 1) {
    DGM::Comm::World->cerr() << "SpectralLine::side number larger than 1"<<endl;
    DGM::Comm::World->exit();
  }
  if(side_number == 0)
    g[0] = f[0];    // f[0] * edge[0].nx(0);
  else
    g[0] = f[qa-1]; // f[qa-1] * edge[1].nx(0);
}

void SpectralLine::compute_geometry() {
  geom.reset( new Geometry( lid(), 1, nVerts(), qtot ) );
  Scalar detJ = pt5 * ( vert[1]->x - vert[0]->x );
  geom->J  = detJ;
  geom->rx = one/detJ;
#ifdef DGM_USE_WJ
  dvmul( psi->wa, geom->J, geom->wJ );
  dvsqrt( geom->wJ, geom->srwJ );
  geom->isrwJ = one;
  dvdiv( geom->srwJ, geom->isrwJ );
#endif
  measure(compute_measure());   // length
#ifdef DGM_USE_GEOM_DB
  gdb.add(geom);
#endif
#ifdef DGM_STORE_METRICS
  // Compute metrics for CFL and timestep size (stability) estimates.
  compute_metrics();
#endif
}

/// Compute the stability metrics for timestep size calculations.
Element::StabMetrics SpectralLine::compute_metrics() {
  return compute_metrics_1d();
}

/// Computes geometric factors for the Element Sides
void SpectralLine::compute_side_geometry() {
  //  cout << "SpectralLine::compute_side_geometry(), Eid = "<< id << endl;
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
    // divide the edge Jacobian (1.0) by the interior Jacobian
    e.J() = 1.0/geom->J[0];

    // This is done so that you can use an interior integration to perform the
    // surface integration.  For this to work you must use an interior
    // quadrature rule that includes the boundaries and you must divide the
    // edge contributions by the integration weight in the other direction(s).

    // store the max ratio of side to element Jacobians
    e.h_n_inv(0.0);
    for (Ordinal q=0; q<e.J().size(); ++q) {
      const Scalar Jedge = fabs(e.J(q));
      sigma(max( sigma(), Jedge ));
      e.h_n_inv(max( e.h_n_inv(), 0.5*Jedge ));
    }
  }
}

/** Add a discrete version of a Dirac delta function at a quadrature point
    with amplitude equal amp */
void SpectralLine::add_Dirac_delta(const Ordinal qpt, const Scalar amp) {
  assert( qpt >= 0 && qpt < qtot );
  u[qpt] += amp/(psi->wa[qpt]*geom->J[qpt]);
}

/** Add a discrete version of a Dirac delta function at an arbitrary point p
    with amplitude equal amp.  p must be within the SpectralLine element. */
void SpectralLine::add_Dirac_delta(const Point &p, const Scalar amp) {
  Scalar r;
  // First get the local coordinate on line
  if(!get_local_coordinates(p,r)) {
    DGM::Comm::World->cerr()<<
      "SpectralLine::Add_Dirac_delta: could not find (r)"<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  const Point q(r);
  return add_local_Dirac_delta(q,amp);
}

void SpectralLine::add_local_Dirac_delta(const Point &p, const Scalar amp) {

  const Scalar r=p.x;

  dMatrix im;

  // 1D interpolation in the a-direction
  dVector z1(qa), w1(qa);
  // Compute Gauss-Lobatto-Legendre points and weights
  zwgll(z1,w1);
  im.resize(1,qa);
  // Form the interpolation matrix from Gauss-Lobatto-Legendre to r
  igllm(im,z1,r);
  for (Ordinal i=0;i<qa;i++) {
    u[i] += im(0,i) * amp/(psi->wa[i]*geom->J[i]);
  }
}

void SpectralLine::add_local_Dirac_delta(const vector<dMatrix> &M,
                                         const Scalar amp) {

  if (1!=M.size())
    error("SpectralLine::add_local_Dirac_delta: Incorrect matrix size.");
  if (M[0].cols() != qa)
    error("SpectralLine::add_local_Dirac_delta: Inconsistant matrix size.");

  const dMatrix &im = M[0];
  for (Ordinal i=0;i<qa;i++) {
    u[i] += im(0,i) * amp/(psi->wa[i]*geom->J[i]);
  }
}

/// Extract the solution at the Point p
Scalar SpectralLine::interpolate_point(const Point &p) const {
  Scalar r;
  // SSC: the get_local_coordinates methods are expensive.  Since the probe
  // points don't move, we could cache this for each probe point so that they
  // don't have to be recomputed every time that Response::probe(...) gets
  // called
  if(!get_local_coordinates(p,r)) {
    DGM::Comm::World->cerr()<<"Interp_point: could not find (r)"<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  const Point q(r);
  return interpolate_local_point(q);
}

/// Extract the solution at the Point p
Scalar SpectralLine::interpolate_local_point(const Point &p) const {

  const Scalar r=p.x;

  dMatrix im;
  dVector tmp(qa), result(1);
  // SSC: we should consider building these interpolation operators once and
  // then have a fast apply method to use them.
  // 1D interpolation in the a-direction
  dVector z1(qa), w1(qa);
  // Compute Gauss-Lobatto-Legendre points and weights
  zwgll(z1,w1); // x direction
  im.resize(1,qa);
  // Form the interpolation matrix from Gauss-Lobatto-Legendre to r
  igllm(im,z1,r);
  // Now interpolate to get the value at r
  tmp.alias(const_cast<dVector&>(u),0,qa);  // watch out
  mvmult(im, tmp, result);
  return result[0]; // the interpolated solution is returned
}

/// Extract the solution at the Points ps
void SpectralLine::interpolate_points(const vector<Point> &ps,
                                      dVector &vals) const {
  if (state != Physical) {
    cerr << "SpectralLine::interpolate_points -- not in physical space"<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  vals.resize(numeric_cast<Ordinal>(ps.size()));
  for (size_t ip = 0; ip != ps.size(); ip++) {
    const Point& p = ps[ip];
    const Scalar r = p.x;
    dMatrix im;
    dVector tmp(qa), result(1);
    // 1D interpolation in the a-direction
    dVector z1(qa), w1(qa);
    // Compute Gauss-Lobatto-Legendre points and weights
    zwgll(z1,w1); // x direction
    im.resize(1,qa);
    // Form the interpolation matrix from Gauss-Lobatto-Legendre to r
    igllm(im,z1,r);
    // Now interpolate to get the value at r
    tmp.alias(u,0,qa);  // watch out
    mvmult(im, tmp, result);
    // the interpolated solution is stored
    vals(numeric_cast<Ordinal>(ip)) = result[0];
  }
}

void SpectralLine::lift(const Element *const F, dVector &in, const char dir) const {
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

// Only one quadrature point per side, no summation required
Scalar SpectralLine::compute_side_integral( dVector &f, Ordinal sid )
  const {return f[0];}
Scalar SpectralLine::compute_side_measure() const { return 1.0; }

// Collocation derivative matrix
void SpectralLine::get_derivative_matrix() {
  D.reset (new Dinfo);
  D->Da.resize(qa,qa);
  D->Dat.resize(qa,qa);
  dgll(D->Da,D->Dat,psi->za);
}

void SpectralLine::gradient( const dVector &f, dVector &fx ) const {
  gradient(f,fx,fx);
}

void SpectralLine::gradient( const dVector &f, dVector &fx, dVector &) const {
  dVector fr(g1_wk,qtot);
  mvmult( D->Da, f, fr );
  dvmul( geom->rx, fr, fx );
}

void SpectralLine::gradient( const dVector &f, dVector &df, char dir) const {
  if (dir != 'x') { df = 0.0; return; }
  dVector fr(g1_wk,qtot);
  mvmult( D->Da, f, fr );
  dvmul( geom->rx, fr, df );
}

void SpectralLine::tecplot(FILE *fp) {
  bool tnsf = false;
  if (state == Transform) {
    tnsf = true;
    backward_transform();
  }
  dVector ux(qtot);
  gradient( u, ux, ux );
  for (Ordinal q=0; q<qtot; q++)
    fprintf(fp,"%15.8e %15.8e %15.8e\n",C->x[q],u[q],ux[q]);
  if (tnsf) forward_transform();
}

void SpectralLine::output(FILE *fp, const char flag) const {
  if (state == Transform)
    throw DGM::exception("SpectralLine::output called when in transform space");
  int c = 0;
  switch(flag) {
  case 'd':  // solution
    for (Ordinal q=0; q<qa; q++) {
      if (c++%5==0) fprintf(fp,"\n");
      fprintf(fp,"%15.8e ",u[q]);
    }
    break;
  case 'x':  // x-coordinate
    for (Ordinal q=0; q<qa; q++) {
      if (c++%5==0) fprintf(fp,"\n");
      fprintf(fp,"%15.8e ",C->x[q]);
    }
    break;
  case 'p':  // points
    for (Ordinal q=0; q<qa; q++) {
      fprintf(fp,"\n%15.8e %15.8e %15.8e ",C->x[q],0.0,0.0);
    }
    break;
  case 'c': // connectivity
    for (Ordinal q=0; q<qa-1; q++) {
      fprintf(fp,"\n%llu %llu",(long long unsigned)q,(long long unsigned)(q+1));
    }
    break;
  case 't': // paraview element type
    for (Ordinal i=0; i<qa-1; i++) {
      if (c++%5==0) fprintf(fp,"\n");
      fprintf(fp,"%d ",VTK_LINE);
    }
    break;
  case 'o': // paraview offset
    for (Ordinal i=0, q=2; i<qa-1; i++) {
      if (c++%5==0) fprintf(fp,"\n");
      fprintf(fp,"%llu ",(long long unsigned)q);
      q+=2;
    }
    break;
  default:
    throw DGM::exception("Illegal flag in SpectralLine::output, flag = "+
                         asString(flag));
  }
}

// norms and errors

Scalar SpectralLine::norm_Linf() const {
  return norm_inf(u);
}

void SpectralLine::norm_L2(Scalar *L2, Scalar *area) const {
  dVector &wa = psi->wa;
  dVector &J = geom->J;
  dVector b(qtot);
  dVector f(qtot);
  b = J;
  dvmul( wa, b );
  dvmul( u, u, f );            // f = u^2
  *L2 = dot( b, f );           // integrate
  *area = sum( b );
}

Scalar SpectralLine::norm_L2() const {
  Scalar L2, area;
  norm_L2( &L2, &area );
  return sqrt(L2/area);
}

#if 0 // SSC:  not sure what these are for?
void SpectralLine::norm_L2(const dVector& lv, Scalar *L2, Scalar *area) const {
  dVector &wa = psi->wa;
  dVector &J = geom->J;
  dVector b(qtot);
  dVector f(qtot);
  b = J;
  dvmul( wa, b );
  dvmul( lv, lv, f );            // f = v^2
  *L2 = dot( b, f );           // integrate
  *area = sum( b );
}
Scalar SpectralLine::norm_L2(const dVector& lv) const {
  Scalar L2, area;
  norm_L2( lv, &L2, &area );
  return sqrt(L2/area);
}
#endif

void SpectralLine::norm_H1(Scalar *H1, Scalar *area) const {
  dVector &wa = psi->wa;
  dVector &J = geom->J;
  dVector ux(qtot);        // cannot use g1 workspace here!
  dVector b(qtot);
  dVector f(qtot);
  b = J;
  dvmul( wa, b );
  gradient( u, ux, ux);    // compute x derivatives
  dvmul( ux, ux, ux );     // ux = ux^2
  dvmul(  u,  u,  f );     // f  = u^2
  dvadd( ux,  f,  f );     // f  = u^2 + ux^2
  *H1 = dot( b, f );       // integrate
  *area = sum( b );
}

Scalar SpectralLine::norm_H1() const {
  Scalar H1, area;
  norm_H1( &H1, &area );
  return sqrt(H1/area);
}

Scalar SpectralLine::integrate(Scalar *area) const {
#ifdef DGM_USE_WJ
  if (area!=NULL) *area = sum( geom->wJ );
  return dot( geom->wJ, u );
#else
  const dVector &wa = psi->wa;
  const dVector &J = geom->J;
  dVector b(qtot);
  b = J;
  dvmul( wa, b );
  if (area!=NULL) *area = sum( b );
  return dot( b, u );
#endif
}

Scalar SpectralLine::integrate(const dVector &v, Scalar *area) const {
#ifdef DGM_USE_WJ
  if (area!=NULL) *area = sum( geom->wJ );
  return dot( geom->wJ, v );
#else
  const dVector &wa = psi->wa;
  const dVector &J = geom->J;
  dVector b(qtot);
  b = J;
  dvmul( wa, b );
  if (area!=NULL) *area = sum( b );
  return dot( b, v );
#endif
}

void SpectralLine::set(const dVector &fh, const Ordinal nModes2) {
  // cout << "SpectralLine::set(const dVector &, const int)" << endl;
  const Ordinal L2 = nModes2;
  const Ordinal Lm = min(L(),L2);
  for (Ordinal j=0; j<Lm; j++) uh[j] = fh[j];
  state = Transform;
}

Scalar SpectralLine::compute_measure() const {
  dVector &wa = psi->wa;
  dVector &J = geom->J;
  dVector b(qtot);
  dVector f(qtot);
  b = J;
  dvmul( wa, b );
  return sum( b );
}

Scalar SpectralLine::L2_inner_product(const Element *el, Scalar *length) const {
  dVector &wa = psi->wa;
  dVector &J = geom->J;
  dVector b(qtot);
  dVector f(qtot);
  b = J;
  dvmul( wa, b );
  dvmul( el->u, u, f );  // f = u*el->u
  if (length) *length = sum( b );
  return dot( b, f );    // integrate
}

Scalar SpectralLine::L2_inner_product(const dVector& vh, const dVector& wh,
                              Scalar *length) const {
  dVector &wa = psi->wa;
  dVector &J = geom->J;
  dVector b(qtot);
  dVector f(qtot);
  b = J;
  dvmul( wa, b );
  dvmul( vh, wh, f );    // f = vh*wh
  if (length) *length = sum( b );
  return dot( b, f );    // integrate
}

void SpectralLine::apply_metric() {
#ifdef DGM_USE_WJ
  dvmul( geom->srwJ, u );
#else
  dVector &wa = psi->wa;
  dVector &J = geom->J;
  dVector b(qtot);
  b = J;
  dvmul( wa, b );
  dvsqrt( b );
  dvmul( b, u );
#endif
}

void SpectralLine::remove_metric() {
#ifdef DGM_USE_WJ
  dvmul( geom->isrwJ, u );
#else
  dVector &wa = psi->wa;
  dVector &J = geom->J;
  dVector b(qtot);
  b = J;
  dvmul( wa, b );
  dvsqrt( b );
  dvdiv( b, u );
#endif
}

void SpectralLine::get_side_Ds(const int, const dVector& , dVector& ) const {
  cerr << "SpectralLine::get_side_Ds(const int, const dVector& ,dVector&) "
    "undefined" << endl;
  DGM::Comm::World->exit(DGM::FAILURE);
}

void SpectralLine::get_side_curvature( const int sid, dVector &dcurv) const {
  cerr << "SpectralLine::get_side_curvature(const int, dVector& ) undefined"
       << endl;
  DGM::Comm::World->exit(DGM::FAILURE);
}

void SpectralLine::make_constant() {
  bool needs_transform = false;
  if (state == Physical) {
    forward_transform();
    needs_transform = true;
  }
  for (Ordinal j=1; j<L(); j++) uh[j] = 0.0;
  if (needs_transform)
    backward_transform();
}

void SpectralLine::low_modes(const Ordinal inp) {
  const Ordinal np = numeric_cast<Ordinal>(inp);
  if (np>=pOrder()) return;  // nothing to do
  bool needs_transform = false;
  if (state == Physical) {
    forward_transform();
    needs_transform = true;
  }
  for (Ordinal j=np+1; j<L(); j++) uh[j] = 0.0;
  if (needs_transform)
    backward_transform();
}

void SpectralLine::kill_constant() {
  bool needs_transform = false;
  if (state == Physical) {
    forward_transform();
    needs_transform = true;
  }
  uh[0] = 0.0;
  if (needs_transform)
    backward_transform();
}

void SpectralLine::coarse_scales(const int p_inc) {
  // cout << "SpectralLine::coarse_scales(const int p)" <<endl;
  bool needs_transform = false;
  if (state == Physical) {
    forward_transform();
    needs_transform = true;
  }
  // zero the high modes
  for (Ordinal i=L()-p_inc; i<L(); i++) uh[i] = 0.0;
  if (needs_transform)
    backward_transform();
}

void SpectralLine::coarse_scales(const int p_inc, dVector &vh) {
  // cout << "SpectralLine::coarse_scales(const int p, dVector &vh)" <<endl;
  for (Ordinal i=L()-p_inc; i<L(); i++) vh[i] = 0.0;  // zero the high modes
}

void SpectralLine::fine_scales(const int p_inc) {
  // cout << "SpectralLine::fine_scales(const int p)" <<endl;
  bool needs_transform = false;
  if (state == Physical) {
    forward_transform();
    needs_transform = true;
  }
  // zero the low modes
  for (Ordinal i=0; i<L()-p_inc; i++) {
    uh[i] = 0.0;
  }
  if (needs_transform)
    backward_transform();
}

void SpectralLine::fine_scales(const int p_inc, dVector &vh) {
  // cout << "SpectralLine::fine_scales(const int p, dVector &vh)" <<endl;
  for (Ordinal i=0; i<L()-p_inc; i++) {
    vh[i] = 0.0;
  }
}

void SpectralLine::fine_scales_transform(const int p_inc, dVector &vh) const {
  // cout<<"SpectralLine::fine_scales_transform(const int p, dVector &vh)"
  //     <<endl;
  forward_transform(vh,vh);
  for (Ordinal i=0; i<L()-p_inc; i++) {
    vh[i] = 0.0;
  }
  backward_transform(vh,vh);
}

void SpectralLine::fill_basis_shift_matrix(dMatrix &G) const {
  const int nModes = 2;
  const int Nvert = 2;
  G.resize(nModes, Nvert);
  const Scalar r0 = 1.0/sqrt(2.0);
  const Scalar r1 = 1.0/sqrt(6.0);
  G(0,0) =  r0; G(0,1) =  r0;
  G(1,0) = -r1; G(1,1) =  r1;
}

#undef SPECTRALLINE_USE_CBLAS

} // namespace DGM
