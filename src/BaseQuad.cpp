/** \file BaseQuad.cpp
 *  \brief Base method implementations for all Quad elements
 *  \author Scott Collis
*/

// system includes
#include <memory>

// DGM includes
#include "Basis.hpp"
#include "BaseQuad.hpp"

namespace DGM {

/// Makes the Basis (orthogonal, interpolatory and C^0 continuous)
/** /verbatim
    Vertices:

           b
           |             Edge Order:  0) bottom {0,1}
       3-------2                      1) right  {1,2}
       |   |   |                      2) top    {2,3}
       |   +---|-- a                  3) left   {3,0}
       |       |
       0-------1

    /endverbatim
*/
void BaseQuad::make_basis(Basis *psi, const Basis::Type type, const int der) {
  // cout << "BaseQuad::make_basis" << endl;

  const Ordinal L=psi->L, qa=psi->qa, qb=psi->qb;
  dVector &za=psi->za, &wa=psi->wa, &zb=psi->zb, &wb=psi->wb;
  psi->type = type;

  zwgll(za,wa);  // Gauss-Lobatto-Legendre points and weights
  zwgll(zb,wb);  // Gauss-Lobatto-Legendre points and weights

  switch (type) {
  case (Basis::Lagrange): {
    // Lagrange interpolatory basis (primary)
    psi->ba = Basis::make_Lagrange( L, za );
    psi->Ba.alias( psi->ba[0].data(), L, qa );
    psi->bbv = Basis::make_Lagrange( L, zb );
    psi->Bb.alias( psi->bbv[0].data(), L, qb );
    // Legendre orthogonal basis (secondary)
    psi->ga = Basis::make_Legendre( der, L, qa, za );
    psi->Ga.alias( psi->ga[0].data(), L, qa );
    psi->gbv = Basis::make_Legendre( der, L, qb, zb );
    psi->Gb.alias( psi->gbv[0].data(), L, qb );
    break;
  }
  case (Basis::Ortho): {
    // Legendre orthogonal basis (primary)
    psi->ba = Basis::make_Legendre( der, L, qa, za );
    psi->Ba.alias( psi->ba[0].data(), L, qa );
    psi->bbv = Basis::make_Legendre( der, L, qb, zb );
    psi->Bb.alias( psi->bbv[0].data(), L, qb );
    // Lagrange interpolatory basis (secondart)
    psi->ga = Basis::make_Lagrange( L, za );
    psi->Ga.alias( psi->ga[0].data(), L, qa );
    psi->gbv = Basis::make_Lagrange( L, zb );
    psi->Gb.alias( psi->gbv[0].data(), L, qb );
    break;
  }
  default:
    throw DGM::exception("BaseQuad::unsupported basis type "+asString(type));
  }
  // setup modal access pointers for primary basis
  psi->mode.resize(L*L);
  for (Ordinal i=0, m=0; i<L; i++) {
    for (Ordinal j=0; j<L; m++, j++) {
      psi->mode[m].a.alias(psi->ba[i]);
      psi->mode[m].b.alias(psi->bbv[j]);
    }
  }

  // setup C^0 modified Jacobi basis as tensor products of 1d polynomials
  // in directions a and b respectively
  psi->nVerts = 4;
  psi->nEdges = 4;
  psi->nFaces = 1;
  psi->mFace  = (L>2) ? L-2 : 0;
  psi->mIntr  = 0;

  // make the storage for the a and b modes
  const Ordinal m2L = max(Ordinal(2),L);
  psi->amem.resize(qa*m2L);
  psi->bmem.resize(qb*m2L);

  // reset the vert and edge maps for this element type
  VertMode *vm = new VertMode(psi);
  psi->vm.reset( vm );
  psi->em.reset( new EdgeMode(psi, vm) );

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
  // define polynomials in b-direction
  {
    // vertex modes
    dVector v0(psi->vertMode(0).b);
    dVector v3(psi->vertMode(3).b);
    subtract(1.0, zb, v0);
    scale(0.5, v0);
    add(1.0, zb, v3);
    scale(0.5, v3);
    // edge modes
    if (L>2) {
      dVector e3(psi->edgeMode(3,0).b);
      dvmul(v0, v3, e3);
      for (Ordinal i=1; i<L-2; i++) {
        dVector ei(psi->edgeMode(3,i).b);
        jacobf(zb, ei, i, 1.0, 1.0);
        dvmul(e3, ei, ei);
      }
    }
  }
}

/// Returns the side vertices and quadrature points
void BaseQuad::get_curved_side_info(const Ordinal sid, vector<Point> &p,
                                    dVector &z, int &orientation) const {
  orientation = (sid==0 || sid==1) ? 1 : -1;
  const Ordinal q = (sid==0 || sid==2) ? qa : qb;
  dVector w(q);
  z.resize(q);
  zwgll(z,w);
  p.resize(2);
  p[0].x = vert[sid]->x;
  p[0].y = vert[sid]->y;
  p[1].x = vert[(sid+1)%nVerts()]->x;
  p[1].y = vert[(sid+1)%nVerts()]->y;
}

/// Get coordinates in local \f$(r,s)\f$ space
Point BaseQuad::get_local_coordinates(const Point &p) const {
  Scalar r=0, s=0;
  if(!get_local_coordinates(p,r,s)) {
    DGM::Comm::World->cerr()<<
      "BaseQuad::get_local_coordinates: could not find (r,s)"<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  const Point q(r,s);
  return q;
}

/// Find the local coordinates \f$(r,s)\f$ at the point \f$p\f$
/*! This uses a simple Newton-Raphson iteration of the nonlinear mapping from 
    (x,y) -> (r,s) */
int BaseQuad::get_local_coordinates(const Point &p, Scalar &r,
                                    Scalar &s) const {
  const Scalar EPSILON = 1.0e-6;   // tolerance on updates
  const int MAXITER = 100;         // maximum Newton iterations allowed
  const Scalar TOL = 1.001;        // Tolerance on whether inside element
  const Scalar DIV = 1.5;          // Allowable divergence for outside element 

  Scalar  drdx, drdy;
  Scalar  dsdx, dsdy;
  Scalar  dx, dy;
  Scalar  xp, yp;
  Scalar  rr, ss;
  Scalar  x, y;
  int     converged(0), iter(0);

  r = 0.0;    // Seems safest to always start from 0
  s = 0.0; 
  x = p.x;
  y = p.y;
  Scalar length = sqrt(x*x + y*y) + sqrt(measure())*EPSILON;

  dx = 1.0;  dy = 1.0;
  xp = 0.0;  yp = 0.0;

  rr = clamp(r, -1.0, 1.0);  // make sure initially inside element 
  ss = clamp(s, -1.0, 1.0); 

  dVector z1(qa), z2(qb);
  dVector w1(qa), w2(qb);
  dVector im(qb);
  dVector vxp(qa),   vyp(qa),
          vdrdx(qa), vdrdy(qa),
          vdsdx(qa), vdsdy(qa);

  dMatrix mim(im,1,qb);
  const dMatrix X (    C->x, qa, qb);
  const dMatrix Y (    C->y, qa, qb);
  const dMatrix RX(geom->rx, qa, qb);
  const dMatrix RY(geom->ry, qa, qb);
  const dMatrix SX(geom->sx, qa, qb);
  const dMatrix SY(geom->sy, qa, qb);

  zwgll(z1,w1);
  if (qa != qb) zwgll(z2,w2);
  else          z2 = z1;

  // Perform a simple Newton iteration to find the local coordinates
  while (!converged && iter++ <= MAXITER) {
    xp   = 0.0;
    yp   = 0.0;
    drdx = 0.0;
    drdy = 0.0;
    dsdx = 0.0;
    dsdy = 0.0;

    // Form the interpolation matrix
    igllm(mim,z2,ss);

    // Interpolate to temporary points at y=s at each x location
    mvmult ( X, im,   vxp);
    mvmult ( Y, im,   vyp);
    mvmult (RX, im, vdrdx);
    mvmult (RY, im, vdrdy);
    mvmult (SX, im, vdsdx);
    mvmult (SY, im, vdsdy);

    // Form the interpolation matrix 
    igllm(mim,z1,rr);

    xp   =   vxp.Dot(im);
    yp   =   vyp.Dot(im);
    drdx = vdrdx.Dot(im);
    drdy = vdrdy.Dot(im);
    dsdx = vdsdx.Dot(im);
    dsdy = vdsdy.Dot(im);

    dx = x - xp;                    // Distance from the point (x,y,z)
    dy = y - yp;

    rr += (drdx * dx + drdy * dy);  // Newton update  
    ss += (dsdx * dx + dsdy * dy);

    // Convergence test
    if (sqrt(dx*dx + dy*dy )/length < EPSILON) converged = iter;
    if (fabs(rr) > DIV || fabs(ss) > DIV ) converged = -iter;
  }

  if(iter > MAXITER){
    DGM::Comm::World->cerr()<<__FILE__<<":"<<__LINE__<<endl
        <<"BaseQuad::get_local_coordinates: did not converge after "
        <<iter<<" iterations."<<endl
        << setiosflags(ios::fixed) << setprecision(8)
        <<"Searching for point : "<< p <<endl
        <<"Last determined location : ( "<<xp<<", "<<yp<<" )"<<endl
        << *this;
    DGM::Comm::World->cerr()<<"Vertices:"<<endl;
    for(Ordinal i=0;i<nVerts();i++) {
      DGM::Comm::World->cerr()<<" ( "<<vert[i]->x<<", "
                              <<vert[i]->y<<" )"<<endl;
    }
    return 0;
  }
  if (fabs(rr) > TOL || fabs(ss) > TOL ) {
    if (DGM::Comm::World->verbosity()>4) {
      DGM::Comm::World->cerr()<<__FILE__<<":"<<__LINE__<<endl
          <<"BaseQuad::get_local_coordinates: point outside element " <<endl
          <<"    "<< fabs(rr) <<" > " << TOL
          <<" || "<< fabs(ss) <<" > " << TOL <<endl
          << setiosflags(ios::fixed) << setprecision(8)
          <<"Searching for point : "<< p <<endl
          <<"Last determined location : ( "<<xp<<", "<<yp<<" )"<<endl
          << *this;
      DGM::Comm::World->cerr()<<"Vertices:"<<endl;
      for(Ordinal i=0;i<nVerts();i++) {
        DGM::Comm::World->cerr()<<" ( "<<vert[i]->x<<", "
                                <<vert[i]->y<<" )"<<endl;
      }
    }
    return 0;
  }
  r = rr;
  s = ss;
  return 1;
}


/// Push the side information to subsides (if present)
void BaseQuad::push_to_subsides() const {
  for (Ordinal s=0; s<nSides(); ++s) {
    side[s]->push_to_subsides();
  }
}


/// Get the end points of a side
vector<Point> BaseQuad::get_side_endpoints(const Ordinal n) const {
  Point n1, n2;
  const Ordinal q = (n==0 || n==2) ? qa : qb;
  dVector wkx(q), wky(q);
  get_side(C->x, n, wkx);
  get_side(C->y, n, wky);
  n1.x = wkx[0];
  n1.y = wky[0];
  n2.x = wkx[q-1];
  n2.y = wky[q-1];
  vector <Point> p(2);
  p[0] = n1;
  p[1] = n2;
  return p;
}

/// Compute the geometry for the subsides
Scalar BaseQuad::compute_subside_geometry(Side *ss, const Element &N) const {
  const Ordinal n = ss->base ? ss->base->id() : ss->link->id();
  vector<Point> nv = (&N)->get_side_endpoints(n);
  const Scalar J = compute_subside_geometry(ss, nv);
  return J;
}


/// Compute the geometry of the subsides
/** \warning This will may fail for periodic meshes. */
Scalar BaseQuad::compute_subside_geometry(Side *ss,
                                          const vector<Point> &P) const {
  if (2!=P.size()) error(__FILE__" BaseQuad::compute_subside_geometry "
                         "P.size()!=2.");
  vector<Point>  sv(2);
  const Ordinal s = ss->id();
  const Ordinal q = (s==0 || s==2) ? qa:qb;
  {
    dVector wkx(q), wky(q);
    get_side(C->x, s, wkx);
    get_side(C->y, s, wky);
    sv[0].x = wkx[  0];
    sv[0].y = wky[  0];
    sv[1].x = wkx[q-1];
    sv[1].y = wky[q-1];
  }
  /* I simply do not know how to check for periodic BC.
     The coordinates need to be projected from one side to
     the other in the domain, but I don't know the size of the
     domain or what sides are on a periodic boundary.
     The following is a guess. I assume that if the points
     are on a verticle line then since these sides are supposed
     to be shared, they should all be on the same vertical line.
     The same for the horizontal coordinate.  In the standard case
     if sv[0].x==sv[1].x then all x coordinates will be the same and no harm
     done.  This logic will fail for non-rectangular periodic domains.
     The real solution is to examine the shared sides that do not have
     hanging nodes to see if the coordines of the nodes are the same
     and if not deduce the periodicity of the mesh from the difference. */
  if (sv[0].x == sv[1].x && P[0].x == P[1].x) sv[0].x = sv[1].x = P[0].x;
  if (sv[0].y == sv[1].y && P[0].y == P[1].y) sv[0].y = sv[1].y = P[0].y;

  const Scalar J = ss->make_interpolation_matrix(side[s]->q1(),0,sv,P);
  return J;
}

/// Push the side geometry to subsides
void BaseQuad::push_side_geom_to_subside(Side *ss, const Side *s,
                                     const Scalar J) const {
  // Push normals:
  ss->push_to_subside(s->nx(), ss->nx());
  ss->push_to_subside(s->ny(), ss->ny());
  // normalize
  for (Ordinal i=0; i<ss->nx().size(); ++i) {
    dVector &X=ss->nx(), &Y=ss->ny();
    const Scalar l = std::sqrt(X[i]*X[i] + Y[i]*Y[i]);
    if (l) {X[i]/=l; Y[i]/=l;}
  }

  ss->push_to_subside(s->J(),       ss->J());
  ss->push_to_subside(s->J_orig(),  ss->J_orig());
  ss->push_to_subside(s->J_scale(), ss->J_scale());
  ss->J()      *=  J;
  ss->J_orig() *=  J;


  bool non_const_J = false;
  for (Ordinal i=0; i<s->J().size();++i)
    if (s->J()[0]!=s->J()[i]) non_const_J=true;
  if (curve.get() &&
      curve.get()->type_name().find("Straight")==std::string::npos &&
      non_const_J) {
    DGM::Comm::World->cerr()<<
      "Quad::push_side_geom_to_subside: do no support curved elements "
      "with hanging nodes across processor boundaries."<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
}

} // namespace DGM
