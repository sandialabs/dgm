/** \file NodalTet.cpp
    \brief Nodal tetrahedron Element implementation
    \author Scott Collis and Mike Levy

    NodalTet is a four node tetrahedral element that supports affine
    mappings from the master element to the physical space element.

    \verbatim
    1. All of the code is based on Chapter 10 of
         Nodal Discontinuous Galerkin Methods
         Jan S. Hesthaven and Tim Warburton
         Springer, 2008
       Referred to as "HW08" in pretty much all of my notes
       (NodalTri class is based on Chapter 6 of the same)
    2. Tickets under Nodal Tet milestone lay out necessary tasks
      a. Generate Nodes for nodal basis (see HW08 pg 415 -- Nodes3D.m)
      b. Build Vandermonde matrix (pg 417)
         -- This will require updating Polylib and Basis. See
            Basis::make_NodalTet() for guidance, but will want
            to write Basis::make_NodalTet()
      c. Build Derivative Matrix (pg 421)
      d. Hard part: update flux => sides are faces, not edges
                    also, the side orientation needs to be set up for Tets
      e. Update Nodaltet::output() output routines
      f. Update dgm_n2e (and possibly exo2ien?) to handle cubit tetmeshs.
    3. Tips and tricks
      a. for looping through the nodes, some routines use
           for(Ordinal m=0; m<nModes(); m++) {}
         or
           for(Ordinal m=0; m<qtot; m++) {}
         which are great. But when you need the (x,y,z) tensor-ish form, e.g.
         in Polylib::zwntet() and Polylib::dntet(), you will want to use
          for(Ordinal i=0,m=0; i<=L; i++)
            for(Ordinal j=0; i+j<=L; j++)
              for(Ordinal k=0; i+j+k<=L; k++, m++) {}
        where m is the global index
      b. for debugging, I found it very useful to compare against nudg, Matlab
         code written by one of the HW08 authors. It's available at
            http://www.caam.rice.edu/~timwar/NUDG/Software/Download.html
      c. I believe $DGM/runs/ntet.msh is set up properly as a 12-element test,
         so it might be useful to get the nodes correct and then focus on output
         to make sure everything looks okay before continuing.
    4. I'm sure other issues will crop up; I'm happy to answer any DGM questions
       and can be reached at mike.levy.work@gmail.com -- once I get a real work
       email address / phone number, I'll let Scott know
     \endverbatim
*/

// system includes
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

// boost includes
#include "boost/numeric/conversion/cast.hpp"
using boost::numeric_cast;

// DGM includes
#include "Comm.hpp"
#include "Types.hpp"
#include "NodalTet.hpp"
#include "Polylib.tpp"
#include "String.hpp"

namespace DGM {

// anonymous namespace

/// Map nodal tetrahedron quadrature points from ref tet to element
void NodalTet::nodal_tet_quadrature(Scalar X[], Scalar Y[], Scalar Z[],
                                    const std::vector<DGM::Vertex::Ptr> &vert, 
                                    const Ordinal N) {
  const Ordinal Nmode = (N+3)*(N+2)*(N+1)/6;
  std::vector<long double> r(Nmode), s(Nmode), t(Nmode);
  DGM::zwntet(r.data(), s.data(), t.data(), N);
  for(Ordinal m=0; m<Nmode; m++) {
    const Scalar l1 =  (              t[m] + 1)/2;
    const Scalar l2 =  (       s[m]        + 1)/2;
    const Scalar l3 = -(r[m] + s[m] + t[m] + 1)/2;
    const Scalar l4 =  (r[m]               + 1)/2;
    X[m] = l3*vert[0]->x + l4*vert[1]->x + l2*vert[2]->x + l1*vert[3]->x;
    Y[m] = l3*vert[0]->y + l4*vert[1]->y + l2*vert[2]->y + l1*vert[3]->y;
    Z[m] = l3*vert[0]->z + l4*vert[1]->z + l2*vert[2]->z + l1*vert[3]->z;
  }
}

namespace {
// SSC turned off as these are currently unused so turn off to avoid a warning
#if 0

/// Find max p such that (p+1)(p+2)(p+3)/6 <= i
Ordinal lower_i (const Ordinal i) {
  // Bummer, cube roots....
  if (!i) return 0;
  const Scalar z = 27*i + sqrt(729*i*i-3);
  const Scalar y = pow(z, 1/3.);
  const Scalar x = -2 + pow(3,-2/3.)*y + pow(2,-1/3.)/y;
  const Ordinal p = static_cast<Ordinal>(floor(x+.0000001));
  return p;
}

/// Find max p such that p(p+1)/2 <= j
Ordinal lower_j (const Ordinal j) {
  if (!j) return 0;
  const Scalar y = sqrt(1.+8*j);
  const Scalar x = (y-1)/2;
  const Ordinal p = static_cast<Ordinal>(floor(x+.0000001));
  return p;
}

#endif

Ordinal ijk2m(const Ordinal i,
              const Ordinal j,
              const Ordinal k,
              const Ordinal N) {
 const Ordinal m = k + j*(2*N+1-j)/2 +
                   i*( (i-2*(N+1))*(i-(N+1)) + N*(N+2))/6 - i*j;
 return m;
}

Ordinal ij2m(const Ordinal i,
             const Ordinal j,
             const Ordinal N) {
 const Ordinal m = j + N*i - i*(i-1)/2;
 return m;
}

pair<Ordinal,Ordinal> m2ij(const Ordinal m,
                           const Ordinal N) {
  const Ordinal k = N*(N+1)/2 - m -1;
  const Ordinal i = N - 1 - static_cast<Ordinal>(floor(sqrt(1.+8*k)+
                    0.000001)-1)/2;
  const Ordinal j = m - N*i + i*(i-1)/2;
  const pair<Ordinal,Ordinal> r(i,j);
  return r;
}

// turned off by default to prevent unused function warning
#ifdef DGM_NODALTET_USE_IS_ON_FACE
/** lift needs a fast way to determine if
    a quadrature node i is on the face of an element of size
    qtot = qa*(qa+1)/2. direct_left/right_face() computes this
    exactly, while is_on_face() store information in a table.
*/
Ordinal is_on_face(const Ordinal m, const Ordinal Q) {
  static std::vector< std::vector<int> > on_face;
  for (Ordinal p=on_face.size(); p<Q; p++) {
    std::vector<int> on( (p+1)*(p+2)*(p+3)/6 );
    for (Ordinal     i=0, m=0;  i<=p; ++i)
      for (Ordinal   j=0;     i+j<=p; ++j)
        for (Ordinal k=0;   i+j+k<=p; ++k,++m)
          on[m] = ( !i || !j || !k || i+j+k==p );
    on_face.push_back(on);
  }
  return(on_face[Q-1][m]);
}
#endif

} // anonymous namespace

/// Use Gauss-Legendre quadrature instead of Gauss-Lobatto-Legendre
#define DGM_TET_GAUSS_LEGENDRE

// define static storage
BasisDB NodalTet::bdb;                         // define Basis database
NodalTet::GeometryDB NodalTet::gdb("NodalTet ");   // define Geom database
IMDB NodalTet::imdb;                           // define Interpolation database
DerivDB NodalTet::ddb;                         // define Derivative Matrix db
VandermondeDB NodalTet::vdb;                   // define Vandermond Matrix db

Ordinal NodalTet::Qmax = 0;
Ordinal NodalTet::Lmax = 0;
dVector NodalTet::g1_wk;
dVector NodalTet::g2_wk;
dVector NodalTet::g3_wk;

dVector NodalTet::n1_wk;
dVector NodalTet::n2_wk;
dVector NodalTet::n3_wk;
dVector NodalTet::n4_wk;
dVector NodalTet::n5_wk;
dVector NodalTet::Lwk;

#ifdef DGM_USE_MD_COUPLE
/// Constructor
/*! \param[in] ID    - Local element id
    \param[in] P     - Polynomial order
    \param[in] X     - Vector of points defining the vertices
    \param[in] model - Model type */
NodalTet::NodalTet(const Size ID, const Ordinal P,
                   const vector<Point> &X, const Model::Type model)
#else
/// Constructor
/*! \param[in] ID    - Local element id
    \param[in] P     - Polynomial order
    \param[in] X     - Vector of points defining the vertices */
NodalTet::NodalTet(const Size ID, const Ordinal P, const vector<Point> &X)
#endif
  : Element(ID) {
  // cout << "NodalTet::NodalTet, eid = " << ID << endl;
  type   = Basis::Ortho;
  nVerts(4);
  nEdges(6);
  nFaces(4);
  nSides(4);
  pOrder(P);
  L(P+1);
  nModes((P+1)*(P+2)*(P+3)/6);
#ifdef DGM_USE_MD_COUPLE
  modeltype = model;
#endif

  // Nodal tets must use the same number of points in a, b, and c
  qa = L(); qb = L(); qc = L();
  qtot = nModes();

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

  // construct face data-structure
  face.reserve(nFaces());
  for (Ordinal i=0; i<nFaces(); i++) {
    const Ordinal qedg = L()*(L()+1)/2;
    // cout << "Element = " << gid() << "qedg = " << qedg << endl;
#ifdef DGM_USE_MD_COUPLE
    Face fac(i,id,nModes(),qedg,1,modeltype);
#else
    Face fac(i,this,nModes(),qedg,1,true);
#endif
    face.push_back(fac);
    side.push_back( &(face[i]) );
  }
}

/** \note This should not allocate new space for P, M, etc. */
NodalTet::NodalTet(const NodalTet *E) {
  // cout << "NodalTet copy constructor for Eid = " << E->gid() << endl;

  // allocate storage for solution at quadrature points
  u.resize(E->u.size());

  // allocate modal coefficients
  uh.alias(u,E->uh.size());

  *this = *E;  // only copies pointers -- be careful -- use shared_ptr

  // allocate storage for faces
  for (Ordinal i=0; i<nFaces(); i++) {
    // cout << "face = " << i << ", qtot = " <<  face[i].qtot() << endl;
    face[i].u.resize(face[i].qtot());
    face[i].u = 0.0;
    side[i] = &(face[i]);
  }

  // initialize values
  state = Undefined;
  u = 0.0;
}

NodalTet::~NodalTet() {
  // cout << "~NodalTet: eid= "<<id<<endl;
}

Basis* NodalTet::get_basis(const int der=0) const {
  Basis* b;
  char buf[128];
  sprintf(buf,"%lld_%lld_%lld_%lld_%lld",(long long)L(),(long long)der,
          (long long)qa,(long long)qb,(long long)qc);
  string key = buf;
  BasisDB::iterator p = bdb.bases.find(key);
  if ( p == bdb.bases.end() ) {              // not found, make a new one
    b = new Basis(L(),qa,qb,qc,nModes(),nModes());
    make_basis(b,der);
    bdb.bases[key] = b;
  } else {                                   // found, return the basis
    b = p->second;
  }
  return b;
}

void NodalTet::make_basis(Basis *psi, const int der=0) {
  // cout << "NodalTet::make_basis" << endl;
  // static FunctionTimer timer(__PRETTY_FUNCTION__);
  // FunctionSentry sentry(timer);
  const Ordinal L = psi->L, nModes = psi->nModes, qa = psi->qa;
  dVector &r = psi->znt_r;
  dVector &s = psi->znt_s;
  dVector &t = psi->znt_t;
  dVector &za= psi->za;
  dVector &wa= psi->wa;
  zwgll(za, wa);

  psi->bnt = Basis::make_NodalTet(L, nModes, r, s, t);
  // setup modal access points
  psi->mode.resize(nModes);
  for (Ordinal m=0; m<nModes; m++) {
    psi->mode[m].nt.alias(psi->bnt[m]);
  }
  dVector tr(L*(L+1)/2);
  dVector ts(L*(L+1)/2);
  {
    const Ordinal Nmode = (L+2)*(L+1)*L/6;
    std::vector<long double> R(Nmode), S(Nmode), T(Nmode);
    zwntet(R.data(), S.data(), T.data(), L-1);
    for (Ordinal i=0; i<tr.size(); ++i) tr[i] = R[i];
    for (Ordinal i=0; i<ts.size(); ++i) ts[i] = S[i];
  }
  psi->ba = Basis::make_NodalTri(L, L*(L+1)/2, tr, ts);
  psi->Ba.alias( psi->ba[0].data(), L, qa);
}

namespace {

void get_side_from_volume(dVector &to, const dVector &from,
                          const Ordinal face, const Ordinal p) {
  switch(face) {
  case 0:
    // bottom of tet is first qa nodes
    for (Ordinal     i=0, m=0, n=0;  i<p; ++i)
      for (Ordinal   j=0;          i+j<p; ++j)
        for (Ordinal k=0;        i+j+k<p; ++k,++m)
          if (!i) to[n++] = from[m];
    break;
  case 1:
    for (Ordinal     i=0, m=0, n=0;  i<p; ++i)
      for (Ordinal   j=0;          i+j<p; ++j)
        for (Ordinal k=0;        i+j+k<p; ++k,++m)
          if (!j) to[n++] = from[m];
    break;
  case 2:
    for (Ordinal     i=0, m=0, n=0;  i<p; ++i)
      for (Ordinal   j=0;          i+j<p; ++j)
        for (Ordinal k=0;        i+j+k<p; ++k,++m)
          if (i+j+k+1==p) to[n++] = from[m];
    break;
  case 3:
    for (Ordinal     i=0, m=0, n=0;  i<p; ++i)
      for (Ordinal   j=0;          i+j<p; ++j)
        for (Ordinal k=0;        i+j+k<p; ++k,++m)
          if (!k) to[n++] = from[m];
    break;
  default:
    cerr << "NodalTet::get_side_from_volume -- unknown face" << endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
}

typedef map<Ordinal,dMatrix> DB;
static DB NodalTet_Lifts;
static DB NodalTet_MassMatrix;

const dMatrix &lift_matrix(const Ordinal  p) {
  DB::const_iterator Lift = NodalTet_Lifts.find(p);
  if (NodalTet_Lifts.end() == Lift)
    DGM::Comm::World->error("NodalTet::lift_matrix() failed.");
  const dMatrix &r = Lift->second;
  return r;
}

const dMatrix &mass_matrix(const Ordinal  p) {
  DB::const_iterator Mass = NodalTet_MassMatrix.find(p);
  if (NodalTet_MassMatrix.end() == Mass)
    DGM::Comm::World->error("NodalTet::mass_matrix() failed.");
  const dMatrix &m = Mass->second;
  return m;
}

void lift_matrix(const Ordinal  p,
                 const Basis   *psi,
                 const dMatrix  &MM) {

  if (NodalTet_Lifts.end() != NodalTet_Lifts.find(p)) return;

  // Build lift matrix.  Since this is done only once for
  // each p-order, do it the long hard way.
  const Ordinal qtot = MM.rows();
  const Ordinal    N = (p*(p+1))/2;
  dMatrix M(4*N,4*N, 0);
  for (Ordinal face=0; face<4; ++face)
  {
    dVector r_edge(N);
    dVector s_edge(N);
    dMatrix      V(N,N);
    dMatrix      T(N,N);
    const dVector *r=0, *s=0;
    switch (face) {
      case 0: r = &psi->znt_r; s = &psi->znt_s; break;
      case 1: r = &psi->znt_r; s = &psi->znt_t; break;
      case 2: r = &psi->znt_s; s = &psi->znt_t; break;
      case 3: r = &psi->znt_s; s = &psi->znt_t; break;
      default: DGM::Comm::World->error("NodalTet::lift_matrix bad index.");
    }
    get_side_from_volume(r_edge, *r, face, p);
    get_side_from_volume(s_edge, *s, face, p);
    fntri(p, N, r_edge.ptr(), s_edge.ptr(), V);
    matmult( V, 'T', V, T );
    iVector pivots(N);
    if (LU_factor(T, pivots) || LU_inverse(T, pivots))
      DGM::Comm::World->error("NodalTet::lift_matrix LU_factor || LU_inverse");

    for (Ordinal i=0,k=face*N; i<N; ++i,++k)
      for (Ordinal j=0,l=face*N; j<N; ++j,++l) 
        M[k][l] = T[i][j];
  }
  dMatrix G(qtot,4*N,0);
  for (Ordinal     i=0, m=0, r=0, s=0, t=0, u=0;  i<p; ++i) {
    for (Ordinal   j=0;                         i+j<p; ++j) {
      for (Ordinal k=0;                       i+j+k<p; ++k,++m) {
        if (!i)         G[m][0*N + r++] = 1;
        if (!j)         G[m][1*N + s++] = 1;
        if (i+j+k+1==p) G[m][2*N + u++] = 1;
        if (!k)         G[m][3*N + t++] = 1;
      }
    }
  }
  dMatrix T(qtot,4*N);
  dMatrix L(qtot,4*N);
  matmult(G,M,T);
  matmult(MM,T,L);
  dMatrix &Lift = NodalTet_Lifts[p];
  Lift.resize(L);
  Lift=L;
}

void mass_matrix(const Ordinal  q,
                 const Basis   *psi) {

  if (NodalTet_MassMatrix.end() != NodalTet_MassMatrix.find(q)) return;

  // Build mass matrix.  Since this is done only once for
  // each q-order, do it the long hard way.
  dMatrix M(q,q,0);

  // build Vandermonde matrix
  dMatrix V(q,q);
  for (Ordinal i=0; i<q; i++) V.row(i) = psi->mode[i].nt;
  matmult( V, 'T', V, M );

  dMatrix &Mass = NodalTet_MassMatrix[q];
  Mass.resize(M);
  Mass=M;
}

}  // anonymous namespace

/// Map nodal tetrahedron quadrature points from ref tet to element
void NodalTet::nodal_tet_quadrature(vector<Point> &Q,
                                    const std::vector<Point> &P, 
                                    const Ordinal N) {
  std::vector<DGM::Vertex::Ptr> V(4);
  for (Ordinal i=0; i<3; i++) 
    V[i].reset(new Vertex(0,0,P[i]));
  V[3].reset(new Vertex(0,0,Point()));
  const Ordinal Nmode = (N+3)*(N+2)*(N+1)/6;
  const Ordinal     q =       (N+2)*(N+1)/2;
  Scalar X[Nmode], Y[Nmode], Z[Nmode];
  NodalTet::nodal_tet_quadrature(X,Y,Z,V,N);
  dVector sX(q), sY(q), sZ(q);
  {
    dVector vX(X,Nmode), vY(Y,Nmode), vZ(Z,Nmode);
    get_side_from_volume(sX, vX, 0, N+1);
    get_side_from_volume(sY, vY, 0, N+1);
    get_side_from_volume(sZ, vZ, 0, N+1);
  }
  Q.resize(q);
  for (Ordinal i=0; i<q; ++i) {Q[i].x=sX[i]; Q[i].y=sY[i]; Q[i].z=sZ[i];}
}

// Gets the mass matrix for NodalTet
/** \note This really computes the inverse mass matrix directly. */
void NodalTet::get_mass_matrix() {
  if (curve.get())
    DGM::Comm::World->error("Curved elements not supported in NodalTet");
  // cout << "NodalTet::get_mass_matrix for element " << gid() << endl;

  const Ordinal qtot = nModes();
  mass_matrix(qtot, psi);

  const dMatrix &M = mass_matrix(qtot);
  const Ordinal p = L();
  lift_matrix(p, psi, M);
}

// Resets the mass matrixing using a weighted mass matrix
/** \warning Might be dangerous to reset the mass matrix to this new value. */
void NodalTet::get_mass_matrix(const dVector &x) {
  DGM_UNDEFINED;
}

void NodalTet::solve_mass_matrix(dVector &fh) const {
  dVector tmp(qtot);
  tmp = fh;
  tmp *= (1./geom->J[0]); // only works for constant Jacobian
  // benefit of storing inverse mass matrix!
  const dMatrix &M=mass_matrix(nModes());
  mvmult(M, tmp, fh);
}

//=============================================================================
//
//=============================================================================

/// fill element with a function string
void NodalTet::fill(string function_string, Operation operation) {
  state = Physical;
  parser_init();
  Parser::VectorFunction f("x", "y", "z", "t", function_string );
  f.evaluate( C->x, C->y, C->z, u, 0.0, convert(operation) );
  state = Physical;
}

/// fill element with a mode
void NodalTet::fill(Mode &v) {
  DGM_UNDEFINED;
  // cout << "NodalTet::fill(Mode &)" << endl;
  dMatrix U(u,qa,qb);
  for (Ordinal i=0; i<qa; i++)
    for (Ordinal j=0; j<qb; j++)
      U[i][j] = v.a[i] * v.b[j];
  state = Physical;
}

/// fill a vector with a mode
void NodalTet::fill(Mode &v, dVector &f) const {
  // cout << "NodalTet::fill(Mode &, dVector &)" << endl;
  for(Ordinal m=0; m<nModes(); m++) f[m] = v.nt[m];
}

/// Fill element with a random polynomial
void NodalTet::random() {
  DGM_UNDEFINED;
  // cout << "NodalTet::random()" << endl;
  state = Physical;
  for (Ordinal i=0; i<nModes(); i++) uh[i] = Element::random(-one,one);
}

void NodalTet::set(const dVector &fh, const Ordinal nModes2) {
  //cout << "NodalTet::set(const dVector &, const int)" << endl;
  if ( qtot != nModes2 ) {
    cout << "NodalTet::set qtot = " << qtot
         << ", nModes2 = " << nModes2 << endl;
    throw DGM::exception("There is a logic error in NodalTet::set(...)");
  }
  uh = fh;
  state = Transform;
}

void NodalTet::inner_product() {
  DGM_UNDEFINED;
  // cout << "NodalTet::inner_product() for Eid = " << gid() << endl;
  dMatrix WK(Lwk,L(),qb);
  dMatrix U(u,qa,qb);
#ifdef DGM_USE_WJ
  const dVector &wJ = geom->wJ;
  dvmul( wJ, u );
  matmult( psi->Ba, U, WK);          // wk[La][qb] = Ba[La][qa] * U[qa][qb]
  dVector Uh, wk;
  int mode = 0;
  for (Ordinal i = 0; i < L(); ++i) {
    Uh.alias( uh, mode, L()-i );
    wk.alias( Lwk, i*qb, qb );
    mvmult( psi->bb[i], wk, Uh );
    mode += L()-i;
  }
#else
  const dVector &wb = psi->wb;
  const dVector &wa = psi->wa;
  const dVector &J = geom->J;
  if (curve.get())
    dvmul( J, u );
  else
    scale( J[0], u );

  for(Ordinal j=0; j<qb; j++) {
    dSlice column(U.column(j));
    dvmul( wa, column );
  }
  //  for(Ordinal i=0; i<qa; i++) dvmul( wb, U.row(i) );  // more expensive
  matmult( psi->Ba, U, WK);

  dVector Uh, wk;
  int mode = 0;
  for (Ordinal i = 0; i < L(); ++i){
    Uh.alias( uh, mode, L()-i );
    wk.alias( Lwk, i*qb, qb );
    dvmul( wb, wk );                                  // less expensive
    mvmult( psi->bb[i], wk, Uh );
    mode += L()-i;
  }
#endif
  state = Transform;
}

void NodalTet::inner_product(dVector &f, dVector &fh) const {
  DGM_UNDEFINED;
  // cout<<"NodalTet::inner_product(dVector&, dVector&) for Eid = "<<id<<endl;
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
  //  for(Ordinal i=0; i<qa; i++) dvmul( wb, F.row(i) );  // more expensive
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

void NodalTet::forward_transform() {
  // cout << "NodalTet::forward_transform()" << endl;
  if (state == Transform) {
    cerr << "NodalTet::transform -- already in transform space"<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  forward_transform(u,uh);
  state = Transform;
}

void NodalTet::forward_transform(dVector &f, dVector &fh) const {
  //cout << "NodalTet::forward_transform(f,fh)" << endl;
  assert(qtot==nModes());
  // Need to make a local copy of f so that mvmult doesn't break
  dVector floc(nModes());
  floc = f;
  mvmult(Viloc->mat, floc, fh);
}

void NodalTet::forward_transform(Element *F, Element *) {
  DGM_UNDEFINED;
  //cout << "NodalTet::forward_transform(*F,*)" << endl;
  if (state == Transform) {
    cerr << "NodalTet::transform -- already in transform space"<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  inner_product(u,uh);
  F->solve_mass_matrix(uh);  // Use element F's Mass matrix
  state = Transform;
}

void NodalTet::backward_transform() {
  if (state == Physical) {
    cerr<<"NodalTet::transform_to_physical -- already in physical space"<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  backward_transform(uh, u);
  state = Physical;
}

void NodalTet::backward_transform(dVector &fh, dVector &f) const {
  //cout << "NodalTet::backward_transform(fh,f)" << endl;
  assert(qtot==nModes());
  dMatrix V(qtot,qtot);
  // build Vandermonde matrix
  for (Ordinal i=0; i<qtot; i++) V.row(i) = psi->mode[i].nt;
  dVector wk(Lwk,qtot);      // Needed for case that fh is alias of f
  wk = fh;
  mvmult(V,wk,f);            // f[qtot] = V[qtot][nModes()] * fh[nModes()]
}

void NodalTet::get_side(const dVector &from, const Ordinal face,
                        dVector &to) const {
  if (state == Transform) {
    cerr << "NodalTet::get_side -- must be in physical space"<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  const Ordinal p=L();
  get_side_from_volume(to, from, face, p);
}

// Interpolation matrix
void NodalTet::make_interpolation_matrix( const Ordinal q1, const Ordinal q2,
                                          const Interp::Type interp,
                                          dMatrix &im ) {
  DGM_UNDEFINED;
  //  cout << "NodalTet::make_interpolation_matrix" << endl;
  im.resize(q1,q2);
  dVector z1(q1), z2(q2), w1(q1), w2(q2);
  Scalar delta;
  switch(interp){
  case(Interp::GL2G):
    zwgll(z2,w2);            // Gauss-Lobatto-Legendre
    zwgl (z1,w1);            // Gauss-Legendre
    igllm(im,z2,z1);         // Interpolation matrix
    break;
  case(Interp::G2GL):
    zwgl (z2,w2);            // Gauss-Legendre
    zwgll(z1,w1);            // Gauss-Lobatto-Legendre
    iglm(im,z2,z1);          // Interpolation matrix
    break;
  case(Interp::GL2U):
    zwgll(z2,w2);
    delta=two/(Scalar)(q1);
    for(Ordinal i=0; i<q1; ++i) z1[i] = i*delta - one + pt5*delta;
    igllm(im,z2,z1);
    break;
  case(Interp::GRJ2G):
#ifdef DGM_TET_GAUSS_LEGENDRE
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
#ifdef DGM_TET_GAUSS_LEGENDRE
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
#ifdef DGM_TET_GAUSS_LEGENDRE
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
    cerr << "NodalTet::make_interpolation_matrix - Invalid interpolation type"
    << endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
}

dMatrix* NodalTet::get_interpolation_matrix( const Ordinal q1, const Ordinal q2,
                                             const Interp::Type interp=
                                             Interp::GL2G) {
  DGM_UNDEFINED;
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

const dMatrix& NodalTet::side_vandermond(const Ordinal p) {
  static map<Ordinal, dMatrix> VMatrix;
  dMatrix &V = VMatrix[p];
  if (0==V.size()) {
    // build Vandermonde matrix
    const Ordinal N = (p*(p+1))/2;
    const Ordinal O = (p*(p+1)*(p+2))/6;
    V.resize(N,N);
    {    
      CMC::Matrix<long double, Ordinal> LV(N,N);
      std::vector<long double> r(N), s(N);
      std::vector<long double> R(O), S(O), T(O);
      zwntet(R.data(), S.data(), T.data(), p-1);
      for (Ordinal i=0; i<N; ++i) r[i] = R[i];
      for (Ordinal i=0; i<N; ++i) s[i] = S[i];
      fntri(p, N, r.data(), s.data(), LV);
      for (Ordinal i=0; i<N; ++i) 
        for (Ordinal j=0; j<N; ++j) 
          V[i][j] = LV[i][j];
      
      iVector P;
      if (LU_factor(V, P)!=0)
        error("NodalTri::side_vandermond_matrix -- LU_factor of "
              "Vandermonde failed.");
      if (LU_inverse(V, P)!=0)
        error("NodalTri::side_vandermond_matrix -- LU_inverse of "
              "Vandermonde failed.");
    }    
  }
  return V;
} 

const dMatrix& NodalTet::side_interpolation(const Ordinal p,
                                            const Ordinal q) {
  static map<pair<Ordinal,Ordinal>, dMatrix> WMatrix;
  dMatrix &W = WMatrix[pair<Ordinal,Ordinal>(p,q)];
  if (0==W.size()) {
    const Ordinal Np = (p*(p+1))/2;
    const Ordinal Nq = (q*(q+1))/2;
    const Ordinal Op = (p*(p+1)*(p+2))/6;
    W.resize(Np,Nq);
    CMC::Matrix<long double, Ordinal> LW(Np,Nq);
    std::vector<long double> r(Np), s(Np);
    std::vector<long double> R(Op), S(Op), T(Op);
    zwntet(R.data(), S.data(), T.data(), p-1);
    for (Ordinal i=0; i<Np; ++i) r[i] = R[i];
    for (Ordinal i=0; i<Np; ++i) s[i] = S[i];
    fntri(q, Np, r.data(), s.data(), LW);
    for (Ordinal i=0; i<Np; ++i) 
      for (Ordinal j=0; j<Nq; ++j) 
        W[i][j] = LW[i][j];
  }
  return W;
}

/// Interpolate data from interior to side quadrature
/** \note Could we make it an option to use long double or is that always
          required?  This seems like it could be very slow */
void NodalTet::interpolate_to_side(const dVector &from,
                                   dVector &to) const {
  // to
  const Ordinal qt = to.size();
  const Ordinal qf = from.size();

  Ordinal Nf, Nt; 
  for (Nf=0; Nf<100 && qf!=((Nf*(Nf+1))/2); ++Nf);
  for (Nt=0; Nt<100 && qt!=((Nt*(Nt+1))/2); ++Nt);

  // build Vandermonde matrix
  const dMatrix &V = side_vandermond(Nf);
  const dMatrix &W = side_interpolation(Nt, Nf);
   
  dVector X(qf);
  mvmult  (V,  from,   X);
  mvmult  (W,     X,  to);
}

// Fill physical space values "f" in the side GLL points.
void NodalTet::fill_sides(const dVector &f) {
  const Ordinal sOrder = (L()*(L()+1))/2;
  for(Ordinal s=0; s<4; s++) {
    if (side[s]->qtot() != sOrder) {
      dVector wk(sOrder);
      get_side(f, s, wk);
      interpolate_to_side(wk, face[s].u );
    } else {
      get_side(f, s, face[s].u);
    }
  }
}

// Interpolate physical space values "f" to a uniform mesh on the sides.
void NodalTet::fill_sides_uniform(const dVector &f) {
  DGM_UNDEFINED;
  dVector wk(g1_wk,pOrder()+1);
  dMatrix *im;
  for(Ordinal eid=0; eid<3; eid++) {
    im = get_interpolation_matrix( face[eid].qtot(), pOrder()+1, Interp::GL2U);
    get_side(f,eid,wk);
    mvmult( *im, wk, face[eid].u );
  }
}

// flux version
void NodalTet::fill_sides(const dVector &fx,
                          const dVector &fy,
                          const dVector &fz) {
  const Ordinal N = (L()*(L()+1))/2;
  dVector wka(g1_wk, N);
  for(Ordinal s=0; s<4; s++) {
    if(face[s].u.size()==N) {
      get_side(fx, s, face[s].u);
      dvmul(face[s].nx(), face[s].u);

      get_side(fy, s, wka);
      dvvtvp(face[s].ny(), wka, face[s].u, face[s].u );

      get_side(fz, s, wka);
      dvvtvp(face[s].nz(), wka, face[s].u, face[s].u );
    } else {
      dVector wk(face[s].u.size());
      get_side(fx, s, wka);
      interpolate_to_side(wka, wk);
      face[s].u = wk;
      dvmul(face[s].nx(), face[s].u);

      get_side(fy, s, wka);
      interpolate_to_side(wka, wk);
      dvvtvp(face[s].ny(), wk, face[s].u, face[s].u );

      get_side(fz, s, wka);
      interpolate_to_side(wka, wk);
      dvvtvp(face[s].nz(), wk, face[s].u, face[s].u );
    }
  }
}

// Interpolate physical space values "f" to the face Gauss points.  But store
// the result in vector g
void NodalTet::load_side(const dVector &f, const Ordinal side_number,
                         dVector &g) const {
  DGM_UNDEFINED;
  dVector wk(g1_wk,pOrder()+1);
  dMatrix *im;
  im = get_interpolation_matrix( face[side_number].qtot(), pOrder()+1,
                                 Interp::GL2G);
  get_side(f,side_number,wk);
  mvmult( *im, wk, g );
}

// compute coordinates of quadrature points
void NodalTet::get_coordinates() {
  if (curve.get())
    get_curved_coordinates();
  else
    get_straight_coordinates();
}

void NodalTet::get_straight_coordinates() {
  //  cout << "NodalTet::get_straight_coordinates for element " <<gid()<<endl;
  C.reset( new Coord(qtot) );
  *C = 0;
  nodal_tet_quadrature(C->x.ptr(), C->y.ptr(), C->z.ptr(), vert, pOrder());
}

void NodalTet::J_backward_transform(dVector &fh, dVector &f) {
  cout << "NodalTet::J_backward_transform for elmt = " << gid() << endl;
  DGM::Comm::World->error("Curved elements not supported in NodalTet");
}

void NodalTet::get_curved_coordinates() {
  DGM_UNDEFINED;
}

void NodalTet::get_side_coordinates(const Ordinal nface, Point *pface) const {
  if (qa*(qa+1)/2 != face[nface].q1())
    DGM::Comm::World->error("NodalTet::get_side_coordinates: variable p order not supported");
  dVector px, py, pz;
  px.resize(face[nface].qtot());
  py.resize(face[nface].qtot());
  pz.resize(face[nface].qtot());

  get_side(C->x,nface,px);
  get_side(C->y,nface,py);
  get_side(C->z,nface,pz);
  for(Ordinal i=0; i<face[nface].qtot(); i++) pface[i] = Point(px[i],py[i],pz[i]);
}

vector<Point> NodalTet::get_side_endpoints(const Ordinal s) const {
  vector<Point>  v(3);
  const Ordinal p = L();
  const Ordinal q = p*(p+1)/2;
  dVector wkx(q), wky(q), wkz(q);
  get_side(C->x, s, wkx);
  get_side(C->y, s, wky);
  get_side(C->z, s, wkz);

  v[0].x = wkx[      0];  
  v[1].x = wkx[    p-1];
  v[2].x = wkx[    q-1];
  v[0].y = wky[      0];  
  v[1].y = wky[    p-1];
  v[2].y = wky[    q-1];
  v[0].z = wkz[      0];  
  v[1].z = wkz[    p-1];
  v[2].z = wkz[    q-1];

  return v;
}


void NodalTet::compute_geometry() {
  //cout << "NodalTet::compute_geometry for element " << gid() << endl;
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

void NodalTet::compute_straight_geometry() {
  // cout << "NodalTet::compute_straight_geometry for element "
  //      << gid() << endl;

  // compute coordinate gradients in mapped space
  const Scalar xr = (vert[1]->x - vert[0]->x)/2;
  const Scalar yr = (vert[1]->y - vert[0]->y)/2;
  const Scalar zr = (vert[1]->z - vert[0]->z)/2;
  const Scalar xs = (vert[2]->x - vert[0]->x)/2;
  const Scalar ys = (vert[2]->y - vert[0]->y)/2;
  const Scalar zs = (vert[2]->z - vert[0]->z)/2;
  const Scalar xt = (vert[3]->x - vert[0]->x)/2;
  const Scalar yt = (vert[3]->y - vert[0]->y)/2;
  const Scalar zt = (vert[3]->z - vert[0]->z)/2;

  // compute determinate of the Jacobian
  const Scalar detJ =  xr*ys*zt + yr*zs*xt + zr*xs*yt -
                       xt*ys*zr - zt*xs*yr - xr*zs*yt;

  if(detJ <= 0.0) {
    cerr << "Element " << gid() <<" has a nonpositive Jacobian = "
         << detJ << endl;
    DGM::Comm::World->error("NodalTet::compute_straight_geometry -- "
                            "Nonpositive Jacobian.");
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

  dMatrix I(3,3); I=0;
  I(0,0) = xr*geom->rx[0] + xs*geom->sx[0] + xt*geom->tx[0];
  I(0,1) = xr*geom->ry[0] + xs*geom->sy[0] + xt*geom->ty[0];
  I(0,2) = xr*geom->rz[0] + xs*geom->sz[0] + xt*geom->tz[0];

  I(1,0) = yr*geom->rx[0] + ys*geom->sx[0] + yt*geom->tx[0];
  I(1,1) = yr*geom->ry[0] + ys*geom->sy[0] + yt*geom->ty[0];
  I(1,2) = yr*geom->rz[0] + ys*geom->sz[0] + yt*geom->tz[0];

  I(2,0) = zr*geom->rx[0] + zs*geom->sx[0] + zt*geom->tx[0];
  I(2,1) = zr*geom->ry[0] + zs*geom->sy[0] + zt*geom->ty[0];
  I(2,2) = zr*geom->rz[0] + zs*geom->sz[0] + zt*geom->tz[0];
  for (unsigned i=0; i<3; ++i) I(i,i) -= 1;
  Scalar N=0;
  for (unsigned i=0; i<3; ++i)
    for (unsigned j=0; j<3; ++j) N += I(i,j)*I(i,j);
  if (.00001 < N) {
    cout <<" ERROR ERROR ERROR ERROR ERROR ERROR"<<endl;
    DGM::Comm::World->error("NodalTet::compute_straight_geometry -- "
                            " Matrx invert failed.");
  }

#ifdef DGM_STORE_METRICS
  // Compute metrics for CFL and timestep size (stability) estimates.
  compute_metrics();
#endif
}

void NodalTet::compute_curved_geometry() {
  DGM_UNDEFINED;
#if 0
  //  cout << "NodalTet::compute_curved_geometry for element " << gid() << endl;
  for (Ordinal i=1; i<nVerts(); i++) {
    geom->dx[i-1] = vert[i]->x - vert[0]->x;
    geom->dy[i-1] = vert[i]->y - vert[0]->y;
  }

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
      geom->J[i] = fabs(geom->J[i]);
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
#endif

#endif
}

/// Compute the stability metrics for timestep size calucations.
Element::StabMetrics NodalTet::compute_metrics() {
#ifdef DGM_STORE_METRICS
  dVector &dxr = geom->dxr;
  dVector &dyr = geom->dyr;
  dVector &dzr = geom->dyr;
  dVector &dxs = geom->dxs;
  dVector &dys = geom->dys;
  dVector &dzs = geom->dzs;
  dVector &dxt = geom->dxt;
  dVector &dyt = geom->dyt;
  dVector &dzt = geom->dzt;
  dVector &ivol = geom->ivol;
  dVector &acoustic = geom->acoustic;
#else
  dVector dxr(qtot,0);
  dVector dyr(qtot,0);
  dVector dzr(qtot,0);
  dVector dxs(qtot,0);
  dVector dys(qtot,0);
  dVector dzs(qtot,0);
  dVector dxt(qtot,0);
  dVector dyt(qtot,0);
  dVector dzt(qtot,0);
  dVector ivol(qtot,0);
  dVector acoustic(qtot,0);
#endif

  // temporary storage
  dVector xr(qtot), xs(qtot), xt(qtot);
  dVector yr(qtot), ys(qtot), yt(qtot);
  dVector zr(qtot), zs(qtot), zt(qtot);

  // compute coordinate gradients in mapped space
  local_gradient( C->x, xr, xs, xt );
  local_gradient( C->y, yr, ys, xt );
  local_gradient( C->z, zr, zs, xt );

  dxr = 0; dxs = 0; dxt = 0;
  dyr = 0; dys = 0; dyt = 0;
  dzr = 0; dzs = 0; dzt = 0;
  Scalar dr=0, ds=0, dt=0;
  const Ordinal p = L();
  for (Ordinal     i=0, q=0;  i<p; ++i) {
    for (Ordinal   j=0;     i+j<p; ++j) {
      for (Ordinal k=0;   i+j+k<p; ++k,++q) {
        if (!i) ds = (psi->znt_s[q+qa*(qa+1)/2] - psi->znt_s[q]);
        else if (q==qtot-1) { // Top node
          ds = (psi->znt_s[q] - psi->znt_s[q-2]);
          dr = ds; // by symmetry (I hope)
          dt = ds; // by symmetry (I hope)
        } else
          ds = pt5*(psi->znt_s[q] - psi->znt_s[q-1]);

        if (q<qtot-1) { // ignore top point for dr
          if (!j) {
            dr = (psi->znt_r[q+1] - psi->znt_r[q]);
          } else if (0<k)
            dr = (psi->znt_r[q] - psi->znt_r[q-1]);
          else
            dr = pt5 * (psi->znt_r[q+1] - psi->znt_r[q-1]);
        }

        if (q<qtot-1) { // ignore top point for dr
          if (!k) {
            dr = (psi->znt_t[q+1] - psi->znt_t[q]);
          } else if (0<j)
            dr = (psi->znt_t[q] - psi->znt_t[q-1]);
          else
            dr = pt5 * (psi->znt_t[q+1] - psi->znt_t[q-1]);
        }

        dxr[q] = xr[q] * dr;
        dxs[q] = xs[q] * ds;
        dxt[q] = xt[q] * dt;
        dyr[q] = yr[q] * dr;
        dys[q] = ys[q] * ds;
        dyt[q] = yt[q] * dt;
        dzr[q] = zr[q] * dr;
        dzs[q] = zs[q] * ds;
        dzt[q] = zt[q] * dt;
        //if (0<dr*ds*dt) ivol[q] =  one / ( dr * ds * dt * geom->J[q] );
        acoustic[q] = sqrt( (dxr[q]+dyr[q]+dzr[q])*(dxr[q]+dyr[q]+dzr[q]) +
                            (dxs[q]+dys[q]+dzs[q])*(dxs[q]+dys[q]+dzs[q]) +
                            (dxt[q]+dyt[q]+dzt[q])*(dxt[q]+dyt[q]+dzt[q]));
      }
    }
  }

  const Ordinal N = L();
  dVector n(qtot);
  n = 0.0;
  ivol = 0.0;
  double vol;
  for (Ordinal i=0; i<N-1; ++i) {
    for (Ordinal j=0; j+i<N-1; ++j) {
      for (Ordinal k=0; k+j+i<N-1; ++k) {
        Ordinal v0 = ijk2m(   i,   j,   k,N);
        Ordinal v1 = ijk2m(   i,   j, 1+k,N);
        Ordinal v2 = ijk2m(   i, 1+j,   k,N);
        Ordinal v3 = ijk2m( 1+i,   j,   k,N);
        vol = tet_volume( v0, v1, v2, v3 );
        ivol[v0] += vol;  n[v0]++;
        ivol[v1] += vol;  n[v1]++;
        ivol[v2] += vol;  n[v2]++;
        ivol[v3] += vol;  n[v3]++;
        if (i<N-2 && j+i<N-2 && k+j+i<N-2) {
          Ordinal v4 = ijk2m(   i, 1+j, 1+k,N);
          Ordinal v5 = ijk2m( 1+i,   j, 1+k,N);
          Ordinal v6 = ijk2m( 1+i, 1+j,   k,N);
          vol = tet_volume( v1, v2, v4, v6 );
          ivol[v1] += vol;  n[v1]++;
          ivol[v2] += vol;  n[v2]++;
          ivol[v4] += vol;  n[v4]++;
          ivol[v6] += vol;  n[v6]++;
          vol = tet_volume( v1, v4, v5, v6 );
          ivol[v1] += vol;  n[v1]++;
          ivol[v4] += vol;  n[v4]++;
          ivol[v5] += vol;  n[v5]++;
          ivol[v6] += vol;  n[v6]++;
          vol = tet_volume( v1, v5, v3, v6 );
          ivol[v1] += vol;  n[v1]++;
          ivol[v5] += vol;  n[v5]++;
          ivol[v3] += vol;  n[v3]++;
          ivol[v6] += vol;  n[v6]++;
          vol = tet_volume( v1, v3, v2, v6 );
          ivol[v1] += vol;  n[v1]++;
          ivol[v3] += vol;  n[v3]++;
          ivol[v2] += vol;  n[v2]++;
          ivol[v6] += vol;  n[v6]++;
        }
        if (0<j && 0<k) {
          Ordinal v7 = ijk2m( 1+i,   j,-1+k,N);
          Ordinal v8 = ijk2m( 1+i,-1+j,   k,N);
          vol = tet_volume( v3, v7, v8, v0 );
          ivol[v3] += vol;  n[v3]++;
          ivol[v7] += vol;  n[v7]++;
          ivol[v8] += vol;  n[v8]++;
          ivol[v0] += vol;  n[v0]++;
        }
      }
    }
  }
  // Get the average "cube" volume for quadrature point.
  // Since ivol is used to determine a characteristic length, via
  // the cube root (a cube volume), we should multiple by six
  // to get the parallelpiped volume, and use that to obtain
  // the characteristic length.  This explains why the CFL was
  // off by ~2 (i.e., pow(6,1/3)=1.817).
  for (Ordinal q=0; q<qtot; ++q) {
    ivol[q] =  n[q] / ( 6.0*ivol[q] * geom->J[q] );
  }

  StabMetrics metrics;
#ifndef DGM_STORE_METRICS
  // Need to use an insert instead of copy constructor, because
  // dVector's copy constructor does not resize to the RHS dVector.
  //metrics[DXR]      = dxr;
  //metrics[DYR]      = dyr;
  //metrics[DXS]      = dxs;
  //metrics[DYS]      = dys;
  //metrics[IVOL]     = ivol;
  //metrics[ACOUSTIC] = acoustic;
  metrics.insert(StabMetrics::value_type( DXR,  dxr  ));
  metrics.insert(StabMetrics::value_type( DYR,  dyr  ));
  metrics.insert(StabMetrics::value_type( DZR,  dzr  ));
  metrics.insert(StabMetrics::value_type( DXS,  dxs  ));
  metrics.insert(StabMetrics::value_type( DYS,  dys  ));
  metrics.insert(StabMetrics::value_type( DZS,  dzs  ));
  metrics.insert(StabMetrics::value_type( DXT,  dxt  ));
  metrics.insert(StabMetrics::value_type( DYT,  dyt  ));
  metrics.insert(StabMetrics::value_type( DZT,  dzt  ));
  metrics.insert(StabMetrics::value_type( IVOL, ivol ));
  metrics.insert(StabMetrics::value_type( ACOUSTIC, acoustic ));
#endif
  return metrics;
}

/// Calculate the volume of a tetra given the four vertices.
/** V = |(a-d).((b-d)x(c-d))|/6. */
Scalar NodalTet::tet_volume(Ordinal v0, Ordinal v1, Ordinal v2, Ordinal v3) {
  dVector a(3), b(3), c(3), d(3), ta(3), tb(3), tc(3), td(3);
  a[0] = psi->znt_r[v0]; a[1] = psi->znt_s[v0]; a[2] = psi->znt_t[v0];
  b[0] = psi->znt_r[v1]; b[1] = psi->znt_s[v1]; b[2] = psi->znt_t[v1];
  c[0] = psi->znt_r[v2]; c[1] = psi->znt_s[v2]; c[2] = psi->znt_t[v2];
  d[0] = psi->znt_r[v3]; d[1] = psi->znt_s[v3]; d[2] = psi->znt_t[v3];

  dvsub(a, d, ta);
  dvsub(b, d, tb);
  dvsub(c, d, tc);

  td[0] = tb[1]*tc[2] - tb[2]*tc[1];
  td[1] = tb[2]*tc[0] - tb[0]*tc[2];
  td[2] = tb[0]*tc[1] - tb[1]*tc[0];

  Scalar vol = std::fabs(dot(ta,td))/6.0;

  return vol;
}

/// Generate the side mapping accounting for rotation and flips
Ordinal NodalTet::sideMap(const Side *s, const Ordinal q ) const {
  Ordinal p = q;
  const Ordinal nModes = s->q1();
  const Ordinal N =  static_cast<Ordinal>(lround((sqrt(1+8*nModes)-1)/2));
  if (nModes != N*(N+1)/2)
    DGM::Comm::World->error("NodalTet::sideMap: Could not find side order."
                            " Found order "+asString(N)+
                            " does not give "+asString(nModes));
  const pair<Ordinal,Ordinal> ij = m2ij (q, N);
  const Ordinal i = ij.first;
  const Ordinal j = ij.second;
  const bool t = s->transp();
  const bool a = s->flip_a();
  const bool b = s->flip_b();
  // flip about Node 0 => exchange i and j
  // flip about Node 2 => reverse j
  // rotate clock      => flip i and j, reverse both
  // rotate counter    => flip i and j, reverse j
  // flip about 1      => reverse i
  const Ordinal k = N-j-i-1; // flip
  if      (!t &&  a && !b)   p = ij2m(j, i, N);
  else if (!t &&  a &&  b)   p = ij2m(i, k, N);
  else if ( t && !a &&  b)   p = ij2m(k, i, N);
  else if ( t &&  a && !b)   p = ij2m(j, k, N);
  else if (!t && !a &&  b)   p = ij2m(k, j, N);
  if (s->qtot() <= p) {
    cerr <<__FILE__<<":"<<__LINE__<<" NodalTet::sideMap:"
         <<" Bad return value:"<<p
         <<" Max return value:"<<s->qtot()-1
         <<" i:"<<i
         <<" j:"<<j
         <<" N:"<<N
         <<" p:"<<p
         <<" 1:"<<q
         <<" t:"<<t
         <<" a:"<<a
         <<" b:"<<b
         <<endl;
    DGM::Comm::World->error("NodalTet::sideMap: Index out of range.");
  }
  return p;
}

namespace {

Scalar compute_side_area( const Ordinal sid,
                          const vector<Vertex::Ptr> &vert ) {
  dMatrix face_coords(3,3);
  dVector a(3), b(3), a_cross_b(3);

  for (Ordinal i=0; i<3; ++i) {
    const Ordinal j = NodalTet::vertex_num(sid, i);
    face_coords[i][0] = vert[j]->x;
    face_coords[i][1] = vert[j]->y;
    face_coords[i][2] = vert[j]->z;
  }
  for (Ordinal j=0; j<3; ++j) {
    a[j] = face_coords[1][j] - face_coords[0][j];
    b[j] = face_coords[2][j] - face_coords[0][j];
  }

  a_cross_b[0] = a[1]*b[2] - a[2]*b[1];
  a_cross_b[1] = a[2]*b[0] - a[0]*b[2];
  a_cross_b[2] = a[0]*b[1] - a[1]*b[0];

  const Scalar area = a_cross_b.Norm()/2;
  return area;
}

} // anonymous namespace

void NodalTet::compute_side_geometry() {
  // cout << "NodalTet::compute_side_geometry(), Eid = "<< gid() << endl;
  sigma(0.0);
  for (Ordinal i=0; i<nFaces(); i++) {
    Face &f = face[i];
    Ordinal qedg = f.qtot();
    const Ordinal N = (L()*(L()+1))/2;
    dVector nx_edge(N);
    dVector ny_edge(N);
    dVector nz_edge(N);
    dVector  r_edge(N);
    dVector  s_edge(N);
    switch(i) {
    case 0:
      get_side(geom->tx,i,nx_edge); // wk is at Gauss-Lobatto points
      get_side(geom->ty,i,ny_edge);
      get_side(geom->tz,i,nz_edge);
      scale( -1.0, nx_edge );       // negate since on bottom
      scale( -1.0, ny_edge );
      scale( -1.0, nz_edge );
      get_side(psi->znt_r, i, r_edge);
      get_side(psi->znt_s, i, s_edge);
      break;
    case 1:
      get_side(geom->sx,i,nx_edge);
      get_side(geom->sy,i,ny_edge);
      get_side(geom->sz,i,nz_edge);
      scale( -1.0, nx_edge );
      scale( -1.0, ny_edge );
      scale( -1.0, nz_edge );
      get_side(psi->znt_r, i, r_edge);
      get_side(psi->znt_t, i, s_edge);
      break;
    case 2: {
      dVector s(N),t(N) ;
      get_side(geom->rx,i,nx_edge);
      get_side(geom->sx,i,s);
      get_side(geom->tx,i,t);
      dvadd(s,nx_edge);
      dvadd(t,nx_edge);

      get_side(geom->ry,i,ny_edge);
      get_side(geom->sy,i,s);
      get_side(geom->ty,i,t);
      dvadd(s,ny_edge);
      dvadd(t,ny_edge);

      get_side(geom->rz,i,nz_edge);
      get_side(geom->sz,i,s);
      get_side(geom->tz,i,t);
      dvadd(s,nz_edge);
      dvadd(t,nz_edge);

      get_side(psi->znt_s, i, r_edge);
      get_side(psi->znt_t, i, s_edge);
      break;
    }
    case 3:
      get_side(geom->rx,i,nx_edge);
      get_side(geom->ry,i,ny_edge);
      get_side(geom->rz,i,nz_edge);
      scale( -1.0, nx_edge );
      scale( -1.0, ny_edge );
      scale( -1.0, nz_edge );
      get_side(psi->znt_s, i, r_edge);
      get_side(psi->znt_t, i, s_edge);
      break;
    }
    if(qedg!=N) {
      interpolate_to_side(nx_edge, face[i].nx());
      interpolate_to_side(ny_edge, face[i].ny());
      interpolate_to_side(nz_edge, face[i].nz());
    } else {
      face[i].nx() = nx_edge;
      face[i].ny() = ny_edge;
      face[i].nz() = nz_edge;
    }

    dVector J_edge(N), interior_J(qedg);
    get_side(geom->J,i,J_edge);    // interpolate interior J to face
    if(qedg!=N) 
      interpolate_to_side(J_edge, interior_J);
    else
      interior_J = J_edge; 

    // make normals have unit length
    for (Ordinal j=0; j<qedg; j++) {
      Scalar len = sqrt( 
      face[i].nx(j)*face[i].nx(j) +
      face[i].ny(j)*face[i].ny(j) +
      face[i].nz(j)*face[i].nz(j) );
      face[i].nx(j) /= len;
      face[i].ny(j) /= len;
      face[i].nz(j) /= len;
    }

    Ordinal o=0;
    switch (i) {
    case 0 : o=3; break;
    case 1 : o=2; break;
    case 2 : o=0; break;
    case 3 : o=1; break;
    }
    for (unsigned j=0; j<4; ++j) {
      const Scalar dot =
                 (vert[j]->x - vert[o]->x)*face[i].nx()[0] +
                 (vert[j]->y - vert[o]->y)*face[i].ny()[0] +
                 (vert[j]->z - vert[o]->z)*face[i].nz()[0];
      if(i!=o && dot<0 ) {
        cout <<" ERROR ERROR ERROR ERROR ERROR ERROR"<<endl;
        cout <<__FILE__<<":"<<__LINE__<<" Face Normal Error "
            <<" face:"<<i <<" o:"<<o <<" i:"<<i <<" dot:"<<dot <<endl;
        DGM::Comm::World->error("NodalTet::compute_side_geometry -- "
                            " Face Normal points into element.");
      }
    }

    // compute and store the face measure for each Side
    f.measure(compute_side_area(i, vert));

    dMatrix V (N,N);
    dMatrix Vr(N,N);
    dMatrix Vs(N,N);
    iVector Pivots(N);
    fntri(L(), N, r_edge.ptr(), s_edge.ptr(), V);
    //  dMatrix MM(qedg,qedg);
    //  matmult( V, 'T', V, MM );
    //  MM *= 1/e.measure();

    if (LU_factor(V, Pivots)!=0)
      DGM::Comm::World->error("NodalTet::compute_side_geometry -- "
                              "LU_factor of Vandermonde failed.");
    if (LU_inverse(V, Pivots)!=0)
      DGM::Comm::World->error("NodalTet::compute_side_geometry -- "
                              "LU_inverse of Vandermonde failed.");

    dntri(Vr, Vs, r_edge.ptr(), s_edge.ptr(), L());
    dMatrix Dr(N,N);
    dMatrix Ds(N,N);
    matmult(Vr, V, Dr);
    matmult(Vs, V, Ds);

    // get coordinates along the face  (Gauss-Lobatto)
    dVector xr(N);
    dVector yr(N);
    dVector zr(N);
    dVector xs(N);
    dVector ys(N);
    dVector zs(N);
    dVector wk(N);
    dVector sq(N);

    get_side(C->x,i,wk);
    mvmult( Dr, wk, xr);
    mvmult( Ds, wk, xs);
    get_side(C->y,i,wk);
    mvmult( Dr, wk, yr);
    mvmult( Ds, wk, ys);
    get_side(C->z,i,wk);
    mvmult( Dr, wk, zr);
    mvmult( Ds, wk, zs);

    dVector cx(N);
    dVector cy(N);
    dVector cz(N);
    dvmul( ys, zr, cx);
    cx *= -1;
    dvvtvp(zs, yr, cx, cx);

    dvmul( xs, zr, cy);
    cy *= -1;
    dvvtvp(zs, xr, cy, cy);

    dvmul( ys, xr, cz);
    cz *= -1;
    dvvtvp(xs, yr, cz, cz);

    dvmul( cx, cx, wk);           // x = x^2
    dvvtvp(cy, cy, wk, wk );      // x = x^2 + y^2
    dvvtvp(cz, cz, wk, wk );      // x = x^2 + y^2 + z^2
    dvsqrt(wk, sq );     // face.J = sqrt(x)
    if(qedg!=N) 
      interpolate_to_side(sq, face[i].J());     // face.J = sqrt(x)
    else
      face[i].J() = sq;

    for (Ordinal j=0; j<qedg; ++j) {
      if ( !CMC::approx_equal(f.measure(),2*face[i].J()[j]))
         cout <<__FILE__<<":"<<__LINE__<<" ERROR "
              <<" area:"    <<f.measure()
              <<" Jacobian:"<<face[i].J()[j]<<endl;
    }

    // Save off interior_Jcoefficients
    side[i]->J_orig().resize(side[i]->J().size());
    side[i]->J_orig()      = side[i]->J();
    side[i]->J_scale().resize(side[i]->qtot());
    side[i]->J_scale() = interior_J;

    // store the max ratio of side to element Jacobians
    for (Ordinal k=0; k<qedg; ++k)
      sigma(max(sigma(), fabs( face[i].J(k) ) ));
  }
}

void NodalTet::forward_transform_side(dVector &f, dVector &fh) {
  DGM_UNDEFINED;
}

void NodalTet::solve_1d_mass_matrix(dVector &fh) const {
  DGM_UNDEFINED;
}

void NodalTet::get_1d_mass_matrix(Minfo &M1d) const {
  DGM_UNDEFINED;
}

Scalar NodalTet::compute_side_integral( dVector &f, Ordinal sid ) const {
  DGM_UNDEFINED;
  const Ordinal qsid = this->side[sid]->qtot();

  dVector z(qsid), w(qsid);
  zwgl(z,w);                      // Gauss-Legendre

  dvmul( side[sid]->J(), f);

  dMatrix *im;
  im = get_interpolation_matrix( qsid, qa, Interp::GL2G );   // to, from
  dVector wk(qa);

  dVector interior_J(qsid);
  get_side(geom->J,sid,wk);       // interpolate interior J to edge
  mvmult( *im, wk, interior_J );

  dvmul( interior_J, f );
  return dot( f, w );
}

/** Add a discrete version of a Dirac delta function at a quadrature point
    with amplitude equal amp */
void NodalTet::add_Dirac_delta(const Ordinal qpt, const Scalar amp) {
  DGM_UNDEFINED;
  assert( qpt >= 0 && qpt < qtot );
  Ordinal i, j;
  // recover i and j from qpt =  j  + i*qb;
  j = qpt % qb;
  i = (qpt-j)/qb;
  Scalar wght = (psi->wa[i])*(psi->wb[j]);
  u[qpt] += amp/(wght*geom->J[qpt]);
}

/** Add a discrete version of a Dirac delta function at an arbitrary point p
    with amplitude equal amp.  The Point, p, must be within the NodalTet
    element. */
void NodalTet::add_Dirac_delta(const Point &p, const Scalar amp) {
  Scalar r,s,t;
  if(!get_local_coordinates(p,r,s,t)) {
    DGM::Comm::World->cerr()<<
      "NodalTet::Add_Dirac_delta: could not find (r,s)"<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  const Point q(r,s,t);
  return add_local_Dirac_delta(q,amp);
}

void NodalTet::add_local_Dirac_delta(const Point &p, const Scalar amp) {
  DGM_UNDEFINED;
  Scalar r = p.x;
  Scalar s = p.y;
  dMatrix delta(nModes(),1);
  dMatrix P(1,nModes());
  fntri(qa, (Ordinal)1, &r, &s, P);
  dMatrix V(nModes(),nModes());  // build Vandermonde matrix
  dVector Vrow(nModes());
  for (Ordinal i=0; i<nModes(); i++) {
    fill( psi->mode[i], Vrow );
    for (Ordinal j=0; j<nModes(); j++) V[i][j] = Vrow[j];
  }
  matmult(V, 'T', P, delta);
  Scalar wgt = one/geom->J[0];
  for(Ordinal q=0; q<qtot; ++q)
    u(q) += delta(q,0)*amp*wgt;
}

/// Extract the solution at the Point p
Scalar NodalTet::interpolate_point(const Point &p) const {
  Scalar r,s,t;
  if(!get_local_coordinates(p,r,s,t)) {
    DGM::Comm::World->cerr()
      <<"NodalTet::interpolate_point: could not find (r,s)"<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  const Point q(r,s,t);
  return interpolate_local_point(q);
}

/// Extract the solution at the Point p
Scalar NodalTet::interpolate_local_point(const Point &p) const {
  assert(qtot==nModes());

  const Scalar r = p.x;
  const Scalar s = p.y;
  const Scalar t = p.z;
  dMatrix P(1, nModes());
  fntet(qa, (Ordinal)1, &r, &s, &t, P);
  dVector uh(qtot);
  dVector U(qtot);
  U = u;
  // Forward Transform
  forward_transform(U, uh);
  Scalar result=0;
  for(Ordinal m=0; m < nModes(); m++) result += uh(m)*P(0,m);

  return(result);
}

/// Extract the solution at the Points ps
/** \todo Need to vectorize this for efficiency. */
void NodalTet::interpolate_points( const vector<Point> &ps,
                                   dVector &vals) const {
  if (state != Physical) {
    cerr << "NodalTet::interpolate_points -- not in physical space"<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  vals.resize(numeric_cast<Ordinal>(ps.size()));
  for (size_t ip = 0; ip != ps.size(); ip++) {
    const Point &p = ps[ip];
    // Should copy / paste interpolate_local_points here
    // but change r,s,a,b,Pi, and Pj to vectors of length ps.size
    vals(numeric_cast<Ordinal>(ip)) = interpolate_local_point(p);
  }
}

/// Find the local coordinates \f$(r,s,t)\f$ at the point \f$p\f$
Point NodalTet::get_local_coordinates(const Point &p) const {
  Scalar r=0, s=0, t=0;
  if(!get_local_coordinates(p,r,s,t)) {
    DGM::Comm::World->cerr()<<
      "NodalTet::get_local_coordinates: could not find (r,s,t)"<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  const Point q(r,s,t);
  return q;
}

/// Find the local coordinates \f$(r,s,t)\f$ at the point \f$p\f$
int NodalTet::get_local_coordinates(const Point &p,
                                    Scalar &r, Scalar &s, Scalar &t) const {
  dMatrix V(3,3);
  iVector Pivots(3);

  for (Ordinal i=0; i<3; ++i)
    for (Ordinal j=0; j<3; ++j)
      V[i][j] = (*vert[j+1])[i] - (*vert[0])[i];

  if (LU_factor(V, Pivots)!=0)
    DGM::Comm::World->error("NodalTet::compute_side_geometry -- "
                            "LU_factor of Vandermonde failed.");
  if (LU_inverse(V, Pivots)!=0)
    DGM::Comm::World->error("NodalTet::compute_side_geometry -- "
                            "LU_inverse of Vandermonde failed.");

  dVector   P(3);
  dVector rst(3);
  for (Ordinal i=0; i<3; ++i) P[i] = p[i] - (*vert[0])[i];

  mvmult(V,P,rst);
  r = rst[0];
  s = rst[1];
  t = rst[2];

  r = 2.0*r-1.0;
  s = 2.0*s-1.0;
  t = 2.0*t-1.0;

  const Scalar TOL = 1.001;   ///< |r,s,t| < TOL inside an element?
  if (r<-TOL || s<-TOL || t<-TOL || TOL<r+s+t) return 0;

  r = clamp(r, -1.0, 1.0);
  s = clamp(s, -1.0, 1.0);
  t = clamp(t, -1.0, 1.0);

  return 1;
}

/** F->faces holds the upwind flux at the Gauss pts
    U->faces holds the interior flux at the Gauss pts   */
void NodalTet::lift(const Element *const F, dVector &in, const char dir)const{
  // cout << "NodalTet::lift for Eid = " << gid() << endl;

  const Element *const U = this;

  // F->faces holds the upwind flux at the Gauss pts
  // U->faces holds the interior flux at the Gauss pts

  for (Ordinal f=0; f<4; ++f) {
    const Ordinal qedg = U->face[f].qtot();
    for (Ordinal i=0; i<qedg; ++i) if (U->face[f].J()[i]<=.0)
      DGM::Comm::World->error("NodalTet::lift -- "
                              " Face Jacobi nonpositive.");
  }
  const Ordinal T_len = (L()*(L()+1))/2;

  dVector T(4*T_len,0);
  for (Ordinal face=0; face<4; ++face) {
    const Ordinal qedg = U->face[face].qtot();
    dVector f(qedg);
    if (F) dvsub( F->face[face].u, U->face[face].u, f );
    else      f = U->face[face].u;
    dvmul( U->face[face].J(), f);
    if      (dir == 'x') dvmul( U->face[face].nx(), f );
    else if (dir == 'y') dvmul( U->face[face].ny(), f );
    else if (dir == 'z') dvmul( U->face[face].nz(), f );

    if (qedg == T_len) {
      for (Ordinal i=0; i<T_len; ++i) T[face*T_len+i] = f[i];
    } else {
      dVector t(T_len);
      interpolate_to_side(f, t);
      for (Ordinal i=0; i<T_len; ++i) T[face*T_len+i] = t[i];
    }
  }
  T *= (1./geom->J[0]);

  const Ordinal p=L();
  const dMatrix &Lift = lift_matrix(p);
  dVector t(in.size());
  dgemv(1, Lift, T, 1, t);
  in += t;
  //dgemv(1, Lift, T, 1, in);
}

/// Collocation derivative matrix
void NodalTet::get_derivative_matrix() {
  // static FunctionTimer timer(__PRETTY_FUNCTION__);
  // FunctionSentry sentry(timer);
  // cout << "NodalTet::get_derivative_matrix()" << endl;
  // Build inverse Vandermonde Matrix
  VandermondeEntry vkey(nModes());
  VandermondeDB::iterator v = vdb.entry.find(vkey);
  if (v == vdb.entry.end() ) {
    Viloc.reset(new Minfo);
    Viloc->mat.resize(nModes(),nModes());
    Viloc->pivots.resize(nModes());
    for (Ordinal i=0; i<nModes(); i++) {
      dVector Vrow(nModes());
      fill(psi->mode[i], Vrow);
      Viloc->mat.row(i) = Vrow;
    }
    if (LU_factor(Viloc->mat, Viloc->pivots)!=0)
      DGM::Comm::World->error("NodalTet::get_derivative_matrix "
                              "-- LU_factor of Vandermonde failed.");
    if (LU_inverse(Viloc->mat, Viloc->pivots)!=0)
      DGM::Comm::World->error("NodalTet::get_derivative_matrix -- "
                              "LU_inverse of Vandermonde failed.");
    vdb.entry[vkey] = Viloc;
  } else {
    Viloc = v->second;
  }
  // Build Derivative Matrix
  Dentry key(qa,qb,qc);
  DerivDB::iterator p = ddb.entry.find(key);
  if (p == ddb.entry.end() ) {
    D.reset(new Dinfo);
    D->Dr.resize(qtot,qtot);
    D->Ds.resize(qtot,qtot);
    D->Dt.resize(qtot,qtot);
    D->Drt.resize(qtot,qtot);
    D->Dst.resize(qtot,qtot);
    D->Dtt.resize(qtot,qtot);
    dMatrix Vr(qtot,qtot), Vs(qtot,qtot), Vt(qtot,qtot);
    dntet(Vr, Vs, Vt, psi->znt_r.ptr(),
          psi->znt_s.ptr(), psi->znt_t.ptr(), L());
    matmult(Vr, Viloc->mat, D->Dr);
    matmult(Vs, Viloc->mat, D->Ds);
    matmult(Vt, Viloc->mat, D->Dt);
    // Store transposes of D->Dr and D->Ds!
    for (Ordinal i=0; i<qtot; i++)
      for (Ordinal j=0; j<qtot; j++) {
        D->Drt(i,j) = D->Dr(j,i);
        D->Dst(i,j) = D->Ds(j,i);
        D->Dtt(i,j) = D->Dt(j,i);
      }
    D->Da.resize (qa,qa);
    D->Dat.resize(qa,qa);
    dgll(D->Da, D->Dat, psi->za);
    ddb.entry[key] = D;
  } else {
    D = p->second;
  }
}

/** df/dx = df/dr * dr/dx + df/ds * ds/dx
    df/dy = df/dr * dr/dy + df/ds * ds/dy. */
void NodalTet::gradient( const dVector &f,
                               dVector &dfdx,
                               dVector &dfdy,
                               dVector &dfdz ) const {
  dVector dfdr(g1_wk,qtot);   // use gradient workspace
  dVector dfds(g2_wk,qtot);   // use gradient workspace
  dVector dfdt(g3_wk,qtot);   // use gradient workspace
  mvmult(D->Dr, f, dfdr);     // df/dr
  mvmult(D->Ds, f, dfds);     // df/ds
  mvmult(D->Dt, f, dfdt);     // df/dt
  if (!curve.get()) {         // straight sided element
    const Scalar drdx = geom->rx[0];
    const Scalar drdy = geom->ry[0];
    const Scalar drdz = geom->rz[0];
    const Scalar dsdx = geom->sx[0];
    const Scalar dsdy = geom->sy[0];
    const Scalar dsdz = geom->sz[0];
    const Scalar dtdx = geom->tx[0];
    const Scalar dtdy = geom->ty[0];
    const Scalar dtdz = geom->tz[0];
    dfdx = 0; dfdy = 0; dfdz = 0;
    if (drdx) daxpy( drdx, dfdr, dfdx );
    if (dsdx) daxpy( dsdx, dfds, dfdx );
    if (dtdx) daxpy( dtdx, dfdt, dfdx );

    if (drdy) daxpy( drdy, dfdr, dfdy );
    if (dsdy) daxpy( dsdy, dfds, dfdy );
    if (dtdy) daxpy( dtdy, dfdt, dfdy );

    if (drdz) daxpy( drdz, dfdr, dfdz );
    if (dsdz) daxpy( dsdz, dfds, dfdz );
    if (dtdz) daxpy( dtdz, dfdt, dfdz );
  } else {
    DGM::Comm::World->error("NodalTet::gradient -- no curved elements!");
  }
}

void NodalTet::gradient( const dVector &f, dVector &df, char dir) const {
  dVector dfdr(g1_wk,qtot);   // use gradient workspace
  dVector dfds(g2_wk,qtot);   // use gradient workspace
  dVector dfdt(g3_wk,qtot);   // use gradient workspace
  mvmult(D->Dr, f, dfdr);     // df/dr
  mvmult(D->Ds, f, dfds);     // df/ds
  mvmult(D->Dt, f, dfdt);     // df/dt
  if (!curve.get()) {         // straight sided element
    const Scalar rx = geom->rx[0];
    const Scalar ry = geom->ry[0];
    const Scalar rz = geom->rz[0];

    const Scalar sx = geom->sx[0];
    const Scalar sy = geom->sy[0];
    const Scalar sz = geom->sz[0];

    const Scalar tx = geom->tx[0];
    const Scalar ty = geom->ty[0];
    const Scalar tz = geom->tz[0];
    df = 0;
    switch(dir) {
    case 'x':
      if (rx) daxpy( rx, dfdr, df );
      if (sx) daxpy( sx, dfds, df );
      if (tx) daxpy( tx, dfdt, df );
      break;
    case 'y':
      if (ry) daxpy( ry, dfdr, df );
      if (sy) daxpy( sy, dfds, df );
      if (ty) daxpy( ty, dfdt, df );
      break;
    case 'z':
      if (rz) daxpy( rz, dfdr, df );
      if (sz) daxpy( sz, dfds, df );
      if (tz) daxpy( tz, dfdt, df );
      break;
    default:
      throw DGM::exception("Illegal direction in NodalTet::gradient value = "
                           +asString(dir));
      break;
    }
  } else {
    DGM::Comm::World->error("NodalTet::gradient -- no curved elements!");
  }
}

void NodalTet::local_gradient( const dVector &f, dVector &fr,
                               dVector &fs, dVector &ft ) const {
  mvmult(D->Dr, f, fr); // df/dr
  mvmult(D->Ds, f, fs); // df/ds
  mvmult(D->Dt, f, ft); // df/ds
}

void NodalTet::interpolate_to_uniform() {
  DGM_UNDEFINED;
  cout << "NodalTet::interpolate_to_uniform()" << endl;
}

void NodalTet::tecplot(FILE *fp) {
  DGM_UNDEFINED;
}

/// Output requested element information to a file
void NodalTet::binaryOutput(FILE *fp, const OutputType flag) const {
  const Ordinal Nel = ncells();
  if (state == Transform)
    throw DGM::exception("NodalTet::output called when in transform space");
  switch(flag) {
  case ParaviewBinary: {
    const uint32_t length = numeric_cast<uint32_t>(qtot*sizeof(float));
    fwrite(&length,sizeof(uint32_t),1,fp);
    for (Ordinal q=0; q<qtot; q++) {
        const float tmp = u[q];
        fwrite(&tmp,sizeof(float),1,fp);
    }
    break;
  }
  case ParaviewCoordinates: {
    const uint32_t length = numeric_cast<uint32_t>(3*qtot*sizeof(float));
    fwrite(&length,sizeof(uint32_t),1,fp);
    CMC::Vector<float,int> xyz(3);
    for (Ordinal q=0; q<qtot; q++) {
      xyz[0] = C->x[q];
      xyz[1] = C->y[q];
      xyz[2] = C->z[q];
      fwrite(xyz.ptr(),sizeof(float),3,fp);
    }
    break;
  }
  case ParaviewConnectivity: {
    const uint32_t length = numeric_cast<uint32_t>(4*Nel*sizeof(int32_t));
    fwrite(&length,sizeof(uint32_t),1,fp);
    CMC::Vector<int32_t,int> con(4);
    const Ordinal N = L();
    for (Ordinal i=0; i<N-1; ++i) {
      for (Ordinal j=0; j+i<N-1; ++j) {
        for (Ordinal k=0; k+j+i<N-1; ++k) {
          const Ordinal v0 = ijk2m(   i,   j,   k,N);
          const Ordinal v1 = ijk2m(   i,   j, 1+k,N);
          const Ordinal v2 = ijk2m(   i, 1+j,   k,N);
          const Ordinal v3 = ijk2m( 1+i,   j,   k,N);
          con[0] = numeric_cast<uint32_t>(v0);
          con[1] = numeric_cast<uint32_t>(v1);
          con[2] = numeric_cast<uint32_t>(v2);
          con[3] = numeric_cast<uint32_t>(v3);
          fwrite(con.ptr(),sizeof(int32_t),4,fp);
          if (i<N-2 && j+i<N-2 && k+j+i<N-2) {
            const Ordinal v4 = ijk2m(   i, 1+j, 1+k,N);
            const Ordinal v5 = ijk2m( 1+i,   j, 1+k,N);
            const Ordinal v6 = ijk2m( 1+i, 1+j,   k,N);
            con[0] = numeric_cast<uint32_t>(v1);
            con[1] = numeric_cast<uint32_t>(v2);
            con[2] = numeric_cast<uint32_t>(v4);
            con[3] = numeric_cast<uint32_t>(v6);
            fwrite(con.ptr(),sizeof(int32_t),4,fp);
            con[0] = numeric_cast<uint32_t>(v1);
            con[1] = numeric_cast<uint32_t>(v4);
            con[2] = numeric_cast<uint32_t>(v5);
            con[3] = numeric_cast<uint32_t>(v6);
            fwrite(con.ptr(),sizeof(int32_t),4,fp);
            con[0] = numeric_cast<uint32_t>(v1);
            con[1] = numeric_cast<uint32_t>(v5);
            con[2] = numeric_cast<uint32_t>(v3);
            con[3] = numeric_cast<uint32_t>(v6);
            fwrite(con.ptr(),sizeof(int32_t),4,fp);
            con[0] = numeric_cast<uint32_t>(v1);
            con[1] = numeric_cast<uint32_t>(v3);
            con[2] = numeric_cast<uint32_t>(v2);
            con[3] = numeric_cast<uint32_t>(v6);
            fwrite(con.ptr(),sizeof(int32_t),4,fp);
          }
          if (0<j && 0<k) {
            const Ordinal v7 = ijk2m( 1+i,   j,-1+k,N);
            const Ordinal v8 = ijk2m( 1+i,-1+j,   k,N);
            con[0] = numeric_cast<uint32_t>(v3);
            con[1] = numeric_cast<uint32_t>(v7);
            con[2] = numeric_cast<uint32_t>(v8);
            con[3] = numeric_cast<uint32_t>(v0);
            fwrite(con.ptr(),sizeof(int32_t),4,fp);
          }
        }
      }
    }
    break;
  }
  case ParaviewOffsets: {
    const uint32_t length = numeric_cast<uint32_t>(Nel*sizeof(int32_t));
    fwrite(&length,sizeof(uint32_t),1,fp);
    int32_t q=4;
    for (Ordinal e=0; e<Nel; e++) {
      fwrite(&q,sizeof(int32_t),1,fp);
      q+=4;
    }
    break;
  }
  case ParaviewTypes: {
    const uint32_t length = numeric_cast<uint32_t>(Nel*sizeof(uint8_t));
    fwrite(&length,sizeof(uint32_t),1,fp);
    const uint8_t t=VTK_TETRA;
    for (Ordinal e=0; e<Nel; e++) {
      fwrite(&t,sizeof(uint8_t),1,fp);
    }
    break;
  }
  default:
    error("Illegal output type requested in NodalTet::binaryOutput");
  }
}

/// Output requested element information to a file
streamoff NodalTet::binaryLength(const OutputType flag) const {
  const Ordinal Nel = ncells();
  switch(flag) {
  case ParaviewBinary: {
    return sizeof(uint32_t)+qtot*sizeof(float);
    break;
  }
  case ParaviewCoordinates: {
    return sizeof(uint32_t)+3*qtot*sizeof(float);
    break;
  }
  case ParaviewConnectivity: {
    return sizeof(uint32_t)+4*Nel*sizeof(int32_t);
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
    error("Illegal output type requested in NodalTet::binaryLength");
  }
  error("Fell through case statement in NodalTet::binaryLength");
  return 0;
}

/// Dump requested element information to a file
void NodalTet::output(FILE *fp, const char flag) const {
  if (state == Transform)
    throw DGM::exception("NodalTet::output called when in transform space");
  const Ordinal Nel = ncells();
  int c = 0;
  switch(flag) {
  case 'h':  // Tecplot header
    fprintf(fp,"\nZONE T=\"Element %llu\", ",(unsigned long long)gid());
    fprintf(fp,"n=%llu, e=%llu",(unsigned long long)nModes(),
            (unsigned long long)Nel);
    fprintf(fp,", DATAPACKING=BLOCK, ZONETYPE=FETETRAHEDRON");
    break;
  case 'd':  // solution
    for (Ordinal q=0; q<qtot; q++) {
      if (c++%5==0) fprintf(fp,"\n");
      fprintf(fp,"%15.8e ",u[q]);
    }
    break;
  case 'x':  // x-coordinates
    for (Ordinal q=0; q<qtot; q++) {
      if (c++%5==0) fprintf(fp,"\n");
      fprintf(fp,"%15.8e ",C->x[q]);
    }
    break;
  case 'y':  // y-coordinates
    for (Ordinal q=0; q<qtot; q++) {
      if (c++%5==0) fprintf(fp,"\n");
      fprintf(fp,"%15.8e ",C->y[q]);
    }
    break;
  case 'z':  // z-coordinates
    for (Ordinal q=0; q<qtot; q++) {
      if (c++%5==0) fprintf(fp,"\n");
      fprintf(fp,"%15.8e ",C->z[q]);
    }
    break;
  case 'p':  // points
    for (Ordinal q=0; q<qtot; q++) {
      fprintf(fp,"\n%15.8e %15.8e %15.8e ",C->x[q],C->y[q],C->z[q]);
    }
    break;
  case 'c': {  // connectivity
    const Ordinal N = L();
    for (Ordinal i=0; i<N-1; ++i) {
      for (Ordinal j=0; j+i<N-1; ++j) {
        for (Ordinal k=0; k+j+i<N-1; ++k) {
          const unsigned long long v0 = ijk2m(   i,   j,   k,N);
          const unsigned long long v1 = ijk2m(   i,   j, 1+k,N);
          const unsigned long long v2 = ijk2m(   i, 1+j,   k,N);
          const unsigned long long v3 = ijk2m( 1+i,   j,   k,N);
          fprintf(fp,"\n%llu %llu %llu %llu", v0,v1,v2,v3);
          if (i<N-2 && j+i<N-2 && k+j+i<N-2) {
            const unsigned long long v4 = ijk2m(   i, 1+j, 1+k,N);
            const unsigned long long v5 = ijk2m( 1+i,   j, 1+k,N);
            const unsigned long long v6 = ijk2m( 1+i, 1+j,   k,N);
            fprintf(fp,"\n%llu %llu %llu %llu", v1,v2,v4,v6);
            fprintf(fp,"\n%llu %llu %llu %llu", v1,v4,v5,v6);
            fprintf(fp,"\n%llu %llu %llu %llu", v1,v5,v3,v6);
            fprintf(fp,"\n%llu %llu %llu %llu", v1,v3,v2,v6);
          }
          if (0<j && 0<k) {
            const unsigned long long v7 = ijk2m( 1+i,   j,-1+k,N);
            const unsigned long long v8 = ijk2m( 1+i,-1+j,   k,N);
            fprintf(fp,"\n%llu %llu %llu %llu", v3,v7,v8,v0);
          }
        }
      }
    }
    break;
  }
  case 'f': {  // Tecplot footer (connectivity with 1 offset)
    const Ordinal N = L();
    for (Ordinal i=0; i<N-1; ++i) {
      for (Ordinal j=0; j+i<N-1; ++j) {
        for (Ordinal k=0; k+j+i<N-1; ++k) {
          const unsigned long long v0 = 1+ijk2m(   i,   j,   k,N);
          const unsigned long long v1 = 1+ijk2m(   i,   j, 1+k,N);
          const unsigned long long v2 = 1+ijk2m(   i, 1+j,   k,N);
          const unsigned long long v3 = 1+ijk2m( 1+i,   j,   k,N);
          fprintf(fp,"\n%llu %llu %llu %llu", v0,v1,v2,v3);
          if (i<N-2 && j+i<N-2 && k+j+i<N-2) {
            const unsigned long long v4 = 1+ijk2m(   i, 1+j, 1+k,N);
            const unsigned long long v5 = 1+ijk2m( 1+i,   j, 1+k,N);
            const unsigned long long v6 = 1+ijk2m( 1+i, 1+j,   k,N);
            fprintf(fp,"\n%llu %llu %llu %llu", v1,v2,v4,v6);
            fprintf(fp,"\n%llu %llu %llu %llu", v1,v4,v5,v6);
            fprintf(fp,"\n%llu %llu %llu %llu", v1,v5,v3,v6);
            fprintf(fp,"\n%llu %llu %llu %llu", v1,v3,v2,v6);
          }
          if (0<j && 0<k) {
            const unsigned long long v7 = 1+ijk2m( 1+i,   j,-1+k,N);
            const unsigned long long v8 = 1+ijk2m( 1+i,-1+j,   k,N);
            fprintf(fp,"\n%llu %llu %llu %llu", v3,v7,v8,v0);
          }
        }
      }
    }
    break;
  }
  case 't': // paraview element type
    for (Ordinal e=0; e<Nel; e++) {
      if (c++%5==0) fprintf(fp,"\n");
      fprintf(fp,"%d ",VTK_TETRA);
    }
    break;
  case 'o': // paraview offset
    for (Ordinal e=0, off=4; e<Nel; e++) {
      if (c++%5==0) fprintf(fp,"\n");
      fprintf(fp,"%llu ",(long long unsigned)off);
      off+=4;
    }
    break;
  default:
    throw DGM::exception("Illegal flag in NodalTet::output value = "
                         +asString(flag));
  }
}

//============================================================================
//                       Norm and Error routines
//============================================================================

Scalar NodalTet::norm_Linf() const {
  return norm_inf(u);
}

void NodalTet::norm_L2(Scalar *L2, Scalar *volume) const {
  // volume ?
  dVector f(qtot);
  // integral of u*u
  dvmul(u, u, f);
  *L2 = integrate(f, volume);
}

Scalar NodalTet::norm_L2() const {
  DGM_UNDEFINED;
  Scalar L2, volume;
  norm_L2( &L2, &volume );
  return sqrt(L2/volume);
}

void NodalTet::norm_H1(Scalar *H1, Scalar *volume) const {
  dVector ux(n1_wk,qtot), uy(n2_wk,qtot), uz(n3_wk,qtot), du2(n4_wk,qtot);
  dVector f(n5_wk,qtot);

  gradient( u, ux, uy, uz );   // compute x and y derivatives
  dvmul( ux, ux, ux );     // ux = ux^2
  dvmul( uy, uy, uy );     // uy = uy^2
  dvmul( uz, uz, uz);      // uz = uz^2
  dvadd( ux, uy, uy);      // uy = ux^2 + uy^2
  dvadd( uy, uz, du2);     // ux = ux^2 + uz^2

  dvmul(  u,  u,  f );     // f  = u^2
  dvadd(du2,  f,  f );     // f  = u^2 + ux^2 + uy^2 + uz^2

  // integral of u^2 + ux^2 + uy^2 + uz^2
  *H1 = integrate(f, volume);
}

Scalar NodalTet::norm_H1() const {
  Scalar H1, volume;
  norm_H1( &H1, &volume );
  return sqrt(H1/volume);
}

Scalar NodalTet::integrate( Scalar *volume ) const {
#ifdef DGM_USE_WJ
  DGM_UNDEFINED;
  const dVector &b = geom->wJ;
#else
  DGM_UNDEFINED;
  const dVector &wa = psi->wa;
  const dVector &wb = psi->wb;
  const dVector &wc = psi->wc;

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
  if (volume!=NULL) *volume = sum( b );    // element volume
  return dot( b, u );                      // integrate
}

/** Calculate integral of function stored in v using mass matrix
    useful for calculating various norms. */
Scalar NodalTet::integrate( const dVector &v, Scalar *volume ) const {
  dVector f(qtot), fint(qtot);
  fint = 0;
  f    = 0;
  if (volume!=NULL) {
    // Note: should be able to do both multiplies at once
    // with dMatrix(qtot,2)... but matmult(Vi,'T',v) transposes
    // v, not Vi

    // Equivalent of f = Vt*V*ones:
    const dVector ones(qtot, 1);
    mvmult(Viloc->mat, ones, fint);
    tmvmult(Viloc->mat, fint, f);

    // Sum f (be smart, don't add small positive and negative numbers!)
    Scalar pos = 0;
    Scalar neg = 0;
    for(Ordinal j=0; j<qtot; j++) {
      if (f(j) > 0) pos += f(j);
      if (f(j) < 0) neg -= f(j);
    }
    *volume = geom->J[0]*(pos-neg);
  }

  // Equivalent of f = Vt*V*v:
  mvmult(Viloc->mat, v, fint);
  tmvmult(Viloc->mat, fint, f);

  // Sum f (be smart, don't add small positive and negative numbers!)
  Scalar pos = 0;
  Scalar neg = 0;
  for(Ordinal j=0; j<qtot; j++) {
    if (f(j) > 0) pos += f(j);
    if (f(j) < 0) neg -= f(j);
  }
  const Scalar r = geom->J[0]*(pos-neg);
  return r;
}

/** This is a first stop towards having a self tuning, load balancing
    code. See the more detailed comments in Quad.cpp. */
int NodalTet::get_weight() const {
  static Ordinal Pmax = 10;
  static int Weight[11][2] = {
      { 89,  91},
      {108, 107},
      {133, 134},
      {157, 169},
      {194, 207},
      {231, 255},
      {263, 298},
      {313, 372},
      {373, 457},
      {437, 562},
      {480, 658}};
  int cflag = 0;
  if (curve.get()) cflag = 1;
  if (pOrder() > Pmax) {
    cout << "WARNING - NodalTet::get_weight(): "
         << "pOrder (="<<pOrder()<<") > Pmax (="<<Pmax<<")"<< endl;
    return Weight[Pmax][cflag];
  } else
    return Weight[pOrder()][cflag];
}

Scalar NodalTet::compute_measure() const {
  const dVector &J = geom->J;
  return ( integrate(J) );
}

Scalar NodalTet::L2_inner_product(const Element *el, Scalar *volume) const {
 DGM_UNDEFINED;
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
  dvmul( el->u, u, f );  // f = u*el->u
  if (volume) *volume = sum( b );
  return dot( b, f );    // integrate
}

Scalar NodalTet::L2_inner_product(const dVector& vh, const dVector& wh,
                                  Scalar *volume) const {
 DGM_UNDEFINED;
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
  dvmul( vh, wh, f );    // f = vh*wh
  if (volume) *volume = sum( b );
  return dot( b, f );    // integrate
}

Ordinal NodalTet::vertex_num(const Ordinal i, const Ordinal j) {
  static const Ordinal v_num[4][3] = {{0,1,2},
                                      {0,1,3},
                                      {1,2,3},
                                      {0,2,3}};
  return v_num[i][j];
}

void NodalTet::get_side_Ds(const int sid, const dVector& dv,
                           dVector& dv_s) const {
  DGM_UNDEFINED;
  Ordinal p,q;
  assert( (dVector::size_type)face[sid].qtot() == dv.size() );
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
    im = get_interpolation_matrix(qb, dv.size(), Interp::G2GL);
    mvmult( *im,dv,tmp1);
    for(q=0; q<qb; q++)
      for (p=0; p<qa; p++)
        wk[q + p * qb] = tmp1[p];
    break;
  case 1:
    tmp1.resize(qb);
    im = get_interpolation_matrix(qb, dv.size(), Interp::G2GRJ);
    mvmult( *im,dv,tmp1);
    for(p=0;p<qa;p++)
      for (q=0; q<qb; q++)
        wk[q + p * qb] = tmp1[q];
    break;
  case 2:
    tmp1.resize(qb);
    im = get_interpolation_matrix(qb, dv.size(), Interp::G2GRJ);
    mvmult( *im,dv,tmp1);
    for(p=0;p<qa;p++)
      for (q=0; q<qb; q++)
        wk[q + p * qb] = tmp1[q];
    break;
  default:
    cerr << "Tet::Ds -- unknown side" << endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  gradient(wk,fx,fy);
  load_side(fx,sid,fx_s);
  load_side(fx,sid,fy_s);
  dvmul(face[sid].ny(),fx_s);
  scale(-1.0,fx_s);        // -ny * f_x
  dvvtvp(face[sid].nx(),fy_s,fx_s,dv_s);
  return;
}

void NodalTet::get_side_curvature( const int sid, dVector &dcurv) const {
  DGM_UNDEFINED;
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
    mvmult(D->Da,y1r,y2r);  // D^2 y/ D r^2

    get_side(C->x,sid,tmp);
    mvmult(D->Da,tmp,x1r);
    mvmult(D->Da,x1r,x2r);  // D^2 x/ D r^2

    for(Ordinal i=0;i<qa;i++){
      Scalar ds = pow((x1r[i]*x1r[i]+y1r[i]*y1r[i]),1.5);
      Scalar dtheta = -(x1r[i]*y2r[i] - y1r[i]*x2r[i]);
      if(fabs(ds)<1.0e-6||fabs(dtheta)>1.0e10){
        cerr << "NodalTet::get_side_curvature -- singular curvature radius"
             <<endl;
        DGM::Comm::World->exit(DGM::FAILURE);
      }
      dcurv[i] = dtheta/ds;
    }
  } else  // straight side
    dcurv = 0.0;
}

void NodalTet::make_constant() {
  DGM_UNDEFINED;
  // cout << "NodalTet::make_constant()" <<endl;
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

void NodalTet::low_modes(const Ordinal inp) {
  return;
}

void NodalTet::kill_constant() {
  bool needs_transform = false;
  if (state == Physical) {
    forward_transform();
    needs_transform = true;
  }
  uh[0] = 0.0;
  if (needs_transform)
    backward_transform();
}

} // namespace DGM
