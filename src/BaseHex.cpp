/** \file BaseHex.cpp
 *  \brief Base method implementations for all Hex elements
 *  \author Scott Collis
 */

// DGM includes
#include "Basis.hpp"
#include "BaseHex.hpp"
#include "NodalTriCub.hpp"
#include "NodalTet.hpp"

namespace DGM {

/// Makes the Basis (orthogonal, interpolatory and C^0 continuous)
/** \verbatim
    Vertices

        b
        |
        |                 Face order:  0) back   {0,1,2,3}
        3-------2                      1) bottom {0,1,5,4}
       /.      /|                      2) right  {1,2,6,5}
      / .     / |                      3) top    {3,2,6,7}
     7------ 6  |                      4) left   {0,3,7,4}
     |  0....|..1 --- a                5) front  {4,5,6,7}
     | .     | /          Edge order: {{0,1}, {1,2}, {3,2}, {0,3},
     |.      |/                        {0,4}, {1,5}, {2,6}, {3,7},
     4-------5                         {4,5}, {5,6}, {7,6}, {4,7}};
    /
   c
   \endverbatim
*/
void BaseHex::make_basis(Basis *psi, const Basis::Type type, const int der) {
  // cout << "Hex::make_basis" << endl;
  Ordinal i, j, k, m;
  const Ordinal L=psi->L, qa=psi->qa, qb=psi->qb, qc=psi->qc;
  dVector &za=psi->za, &wa=psi->wa, &zb=psi->zb, &wb=psi->wb,
          &zc=psi->zc, &wc=psi->wc;
  psi->type = type;

  zwgll(za,wa);  // Gauss-Lobatto-Legendre points and weights
  zwgll(zb,wb);  // Gauss-Lobatto-Legendre points and weights
  zwgll(zc,wc);  // Gauss-Lobatto-Legendre points and weights

  switch (type) {
  case (Basis::Ortho): {
    // Legendre orthogonal basis (primary)
    psi->ba = Basis::make_Legendre( der, L, qa, za );
    psi->Ba.alias( psi->ba[0].data(), L, qa );       // unsafe alias
    psi->bbv = Basis::make_Legendre( der, L, qb, zb );
    psi->Bb.alias( psi->bbv[0].data(), L, qb );      // unsafe alias
    psi->bc = Basis::make_Legendre( der, L, qc, zc );
    psi->Bc.alias( psi->bc[0].data(), L, qc );       // unsafe alias

    // Lagrange interpolatory basis (secondary)
    psi->ga = Basis::make_Lagrange( L, za );
    psi->Ga.alias( psi->ga[0].data(), L, qa );
    psi->gbv = Basis::make_Lagrange( L, zb );
    psi->Gb.alias( psi->gbv[0].data(), L, qb );
    psi->gc = Basis::make_Lagrange( L, zc );
    psi->Gc.alias( psi->gc[0].data(), L, qc );
    break;
  }
  case (Basis::Lagrange): {
    // Lagrange interpolatory basis (primary)
    psi->ba = Basis::make_Lagrange( L, za );
    psi->Ba.alias( psi->ba[0].data(), L, qa );
    psi->bbv = Basis::make_Lagrange( L, zb );
    psi->Bb.alias( psi->bbv[0].data(), L, qb );
    psi->bc = Basis::make_Lagrange( L, zc );
    psi->Bc.alias( psi->bc[0].data(), L, qc );

    // Legendre orthogonal basis (secondary)
    psi->ga = Basis::make_Legendre( der, L, qa, za );
    psi->Ga.alias( psi->ga[0].data(), L, qa );       // unsafe alias
    psi->gbv = Basis::make_Legendre( der, L, qb, zb );
    psi->Gb.alias( psi->gbv[0].data(), L, qb );      // unsafe alias
    psi->gc = Basis::make_Legendre( der, L, qc, zc );
    psi->Gc.alias( psi->gc[0].data(), L, qc );       // unsafe alias
    break;
  }
  default:
    throw DGM::exception("BaseHex unsupported basis type "+asString(type));
  }

  // setup modal access pointers
  psi->mode.resize(L*L*L);
  for (i=0, m=0; i<L; i++) {
    for (j=0; j<L; j++) {
      for (k=0; k<L; m++, k++) {
        psi->mode[m].a.alias( psi->ba[i] );
        psi->mode[m].b.alias( psi->bbv[j] );
        psi->mode[m].c.alias( psi->bc[k] );
      }
    }
  }

  // setup C^0 modified Jacobi basis as tensor products of 1d polynomials
  // in directions a and b respectively
  psi->nVerts = 8;
  psi->nEdges = 12;
  psi->nFaces = 6;
  psi->mFace  = (L>2) ? L-2 : 0;
  psi->mIntr  = (L>2) ? L-2 : 0;

  // To conserve space, currently assume that qa = qb = qc
  assert( (qa == qb) && (qa == qc) );
  psi->amem.resize(qa*max((Ordinal)2,L));
  psi->bmem.alias(psi->amem,qb*max((Ordinal)2,L));  // alias of amem
  psi->cmem.alias(psi->amem,qc*max((Ordinal)2,L));  // alias of amem

  VertMode *vm = new VertMode(psi);
  psi->vm.reset( vm );
  EdgeMode *em = new EdgeMode(psi, vm);
  psi->em.reset( em );
  psi->fm.reset( new FaceMode(psi, vm, em) );

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
    for (i=1; i<L-2; i++) {
      dVector ei(psi->edgeMode(0,i).a);
      jacobf(za, ei, i, 1.0, 1.0 );
      dvmul(e0, ei, ei);
    }
  }

  // face and interior modes are now set
}

/// Find the local coordinates (r,s,t) at the point p
Point BaseHex::get_local_coordinates(const Point &p) const {
  Scalar r=0, s=0, t=0;
  if(!get_local_coordinates(p,r,s,t)) {
    DGM::Comm::World->cerr()<<
      "Hex::get_local_coordinates: could not find (r,s,t)"<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  const Point q(r,s,t);
  return q;
}

/// Find the local coordinates (r,s,t) at the point p
/*! This uses a simple Newton-Raphson iteration of the nonlinear mapping from 
    (x,y,z) -> (r,s,t) */
int BaseHex::get_local_coordinates(const Point &p,
                                   Scalar &r, Scalar &s, Scalar &t) const {
  const Scalar EPSILON = 1.0e-6;   ///< tolerance on updates
  const int MAXITER = 100;         ///< maximum Newton iterations allowed 
  const Scalar TOL = 1.001;        ///< Tolerance on whether inside element 
  const Scalar DIV = 1.5;          ///< Allowable divergence outside element

  Scalar  drdx, drdy, drdz;
  Scalar  dsdx, dsdy, dsdz;
  Scalar  dtdx, dtdy, dtdz;
  Scalar  dx, dy, dz;
  Scalar  xp, yp, zp;
  Scalar  rr, ss, tt;
  Scalar  x, y, z;
  int     converged(0), iter(0);

  r    = 0.0;       s    = 0.0;     t    = 0.0;  // Safest to start from (0,0,0)
  xp   = 0.0;       yp   = 0.0;     zp   = 0.0;
  drdx = 0.0;       drdy = 0.0;     drdz = 0.0;
  dsdx = 0.0;       dsdy = 0.0;     dsdz = 0.0;
  dtdx = 0.0;       dtdy = 0.0;     dtdz = 0.0;
  x  = p.x;         y  = p.y;       z  = p.z;
  dx = 1.0;         dy = 1.0;       dz = 1.0;

  Scalar length = sqrt(x*x + y*y + z*z) + pow(measure(),one/3.0)*EPSILON;

  rr = clamp(r, -1.0, 1.0);  // make sure inside element (not really needed)
  ss = clamp(s, -1.0, 1.0);
  tt = clamp(t, -1.0, 1.0);

  // All this memory allocation may make this slow [SSC]
  dVector z1(qa), z2(qb), z3(qc);
  dVector w1(qa), w2(qb), w3(qc);
  Ordinal Qmax = max(max(qa,qb),qc);
  dVector tmp(Qmax);
  dMatrix im;
  dVector vxp(qa),   vyp(qa),   vzp(qa),
          vdrdx(qa), vdrdy(qa), vdrdz(qa),
          vdsdx(qa), vdsdy(qa), vdsdz(qa),
          vdtdx(qa), vdtdy(qa), vdtdz(qa),
          tmpy(qb),  tmpz(qc),  tmp1(1);

  dVector tmpvxp(qa*qb),   tmpvyp(qa*qb),   tmpvzp(qa*qb),
          tmpvdrdx(qa*qb), tmpvdrdy(qa*qb), tmpvdrdz(qa*qb),
          tmpvdsdx(qa*qb), tmpvdsdy(qa*qb), tmpvdsdz(qa*qb),
          tmpvdtdx(qa*qb), tmpvdtdy(qa*qb), tmpvdtdz(qa*qb);

  zwgll(z1,w1);
  zwgll(z2,w2);
  zwgll(z3,w3);
  
  // Perform a simple Newton iteration to find the local coordinates
  while (!converged && iter++ <= MAXITER) {
    xp   = 0.0;        yp   = 0.0;      zp   = 0.0;
    drdx = 0.0;        drdy = 0.0;      drdz = 0.0;
    dsdx = 0.0;        dsdy = 0.0;      dsdz = 0.0;
    dtdx = 0.0;        dtdy = 0.0;      dtdz = 0.0;

    // Form the interpolation matrix from Gauss-Lobatto-Legendre
    im.alias(tmp,1,qc);
    igllm(im,z3,tt);
    // Generate temporary arrays (of length qa*qb)
    for(Ordinal i=0;i<qa;i++) {
      for(Ordinal j=0;j<qb;j++) {
        // In 3D, we need to get qc values starting at j*qc + i*qc*qb
        // int q = k + j*qc + i*qc*qb;
        Ordinal offset = j*qc + i*qc*qb;
        tmpz.alias(C->x,offset,qc);
        mvmult( im, tmpz, tmp1 );
        tmpvxp[i*qb+j]=tmp1[0];
        tmpz.alias(C->y,offset,qc);
        mvmult( im, tmpz, tmp1 );
        tmpvyp[i*qb+j]=tmp1[0];
        tmpz.alias(C->z,offset,qc );
        mvmult( im, tmpz, tmp1);
        tmpvzp[i*qb+j]=tmp1[0];

        tmpz.alias(geom->rx,offset,qc);
        mvmult( im, tmpz, tmp1);
        tmpvdrdx[i*qb+j]=tmp1[0];
        tmpz.alias(geom->ry,offset,qc);
        mvmult( im, tmpz, tmp1);
        tmpvdrdy[i*qb+j]=tmp1[0];
        tmpz.alias(geom->rz,offset,qc);
        mvmult( im, tmpz, tmp1);
        tmpvdrdz[i*qb+j]=tmp1[0];

        tmpz.alias(geom->sx,offset,qc);
        mvmult( im, tmpz, tmp1);
        tmpvdsdx[i*qb+j]=tmp1[0];
        tmpz.alias(geom->sy,offset,qc);
        mvmult( im, tmpz, tmp1);
        tmpvdsdy[i*qb+j]=tmp1[0];
        tmpz.alias(geom->sz,offset,qc);
        mvmult( im, tmpz, tmp1);
        tmpvdsdz[i*qb+j]=tmp1[0];

        tmpz.alias(geom->tx,offset,qc);
        mvmult( im, tmpz, tmp1);
        tmpvdtdx[i*qb+j]=tmp1[0];
        tmpz.alias(geom->ty,offset,qc);
        mvmult( im, tmpz, tmp1);
        tmpvdtdy[i*qb+j]=tmp1[0];
        tmpz.alias(geom->tz,offset,qc);
        mvmult( im, tmpz, tmp1);
        tmpvdtdz[i*qb+j]=tmp1[0];
      }
    }

    // Form the interpolation matrix
    im.alias(tmp,1,qb);
    igllm(im,z2,ss);

    // Interpolate to temporary points at y=s at each x location
    for(Ordinal i=0;i<qa;i++) {
      tmpy.alias(tmpvxp,i*qb,qb);
      mvmult( im, tmpy, tmp1);
      vxp[i]=tmp1[0];
      tmpy.alias(tmpvyp,i*qb,qb);
      mvmult( im, tmpy, tmp1);
      vyp[i]=tmp1[0];
      tmpy.alias(tmpvzp,i*qb,qb);
      mvmult( im, tmpy, tmp1);
      vzp[i]=tmp1[0];

      tmpy.alias(tmpvdrdx,i*qb,qb);
      mvmult( im, tmpy, tmp1);
      vdrdx[i]=tmp1[0];
      tmpy.alias(tmpvdrdy,i*qb,qb);
      mvmult( im, tmpy, tmp1);
      vdrdy[i]=tmp1[0];
      tmpy.alias(tmpvdrdz,i*qb,qb);
      mvmult( im, tmpy, tmp1);
      vdrdz[i]=tmp1[0];

      tmpy.alias(tmpvdsdx,i*qb,qb);
      mvmult( im, tmpy, tmp1);
      vdsdx[i]=tmp1[0];
      tmpy.alias(tmpvdsdy,i*qb,qb);
      mvmult( im, tmpy, tmp1);
      vdsdy[i]=tmp1[0];
      tmpy.alias(tmpvdsdz,i*qb,qb);
      mvmult( im, tmpy, tmp1);
      vdsdz[i]=tmp1[0];

      tmpy.alias(tmpvdtdx,i*qb,qb);
      mvmult( im, tmpy, tmp1);
      vdtdx[i]=tmp1[0];
      tmpy.alias(tmpvdtdy,i*qb,qb);
      mvmult( im, tmpy, tmp1);
      vdtdy[i]=tmp1[0];
      tmpy.alias(tmpvdtdz,i*qb,qb);
      mvmult( im, tmpy, tmp1);
      vdtdz[i]=tmp1[0];
    }

    // Form the interpolation matrix 
    im.alias(tmp,1,qa);
    igllm(im,z1,rr);

    mvmult( im, vxp, tmp1);
    xp = tmp1[0];
    mvmult( im, vyp, tmp1);
    yp = tmp1[0];
    mvmult( im, vzp, tmp1);
    zp = tmp1[0];

    mvmult( im, vdrdx, tmp1);
    drdx = tmp1[0];
    mvmult( im, vdrdy, tmp1);
    drdy = tmp1[0];
    mvmult( im, vdrdz, tmp1);
    drdz = tmp1[0];

    mvmult( im, vdsdx, tmp1);
    dsdx = tmp1[0];
    mvmult( im, vdsdy, tmp1);
    dsdy = tmp1[0];
    mvmult( im, vdsdz, tmp1);
    dsdz = tmp1[0];

    mvmult( im, vdtdx, tmp1);
    dtdx = tmp1[0];
    mvmult( im, vdtdy, tmp1);
    dtdy = tmp1[0];
    mvmult( im, vdtdz, tmp1);
    dtdz = tmp1[0];

    dx = x - xp;  // Distance from the point (x,y,z)
    dy = y - yp;
    dz = z - zp;

    rr += (drdx * dx + drdy * dy + drdz * dz);  // Newton update 
    ss += (dsdx * dx + dsdy * dy + dsdz * dz);
    tt += (dtdx * dx + dtdy * dy + dtdz * dz);

    // Convergence test
    if (sqrt(dx*dx + dy*dy + dz*dz)/length < EPSILON)
      converged = iter;
    if (fabs(rr) > DIV || fabs(ss) > DIV || fabs(tt) > DIV)
      converged = -iter;
  }

  if(iter > MAXITER){
    DGM::Comm::World->cerr()<<__FILE__<<":"<<__LINE__<<endl
        <<"BaseHex::get_local_coordinates: did not converge after "
        <<iter<<" iterations."<<endl
        << setiosflags(ios::fixed) << setprecision(8)
        <<"Searching for point : "<< p <<endl
        <<"Last determined location : ( "<<xp<<", "<<yp<<", "<<zp<<" )"<<endl
        << *this;
    DGM::Comm::World->cerr()<<"Vertices:"<<endl;
    for(Ordinal i=0;i<nVerts();i++) {
      DGM::Comm::World->cerr()<<" ( "<<vert[i]->x
                              <<", " <<vert[i]->y
                              <<", " <<vert[i]->z<<" )"<<endl;
    }
    return 0;
  }
  if (fabs(rr) > TOL || fabs(ss) > TOL || fabs(tt) > TOL ) {
    if (DGM::Comm::World->verbosity()>4) {
      DGM::Comm::World->cerr()<<__FILE__<<":"<<__LINE__
          <<"BaseHex::get_local_coordinates: point outside element" <<endl
          <<"    "<< fabs(rr) <<" > " << TOL
          <<" || "<< fabs(ss) <<" > " << TOL
          <<" || "<< fabs(tt) <<" > " << TOL << endl
          << setiosflags(ios::fixed) << setprecision(8)
          <<"Searching for point : "<< p <<endl
          <<"Last determined location : ( "<<xp<<", "<<yp<<", "<<zp<<" )"<<endl
          << *this;
      DGM::Comm::World->cerr()<<"Vertices:"<<endl;
      for(Ordinal i=0;i<nVerts();i++) {
        DGM::Comm::World->cerr()<<" ( "<<vert[i]->x
                                <<", " <<vert[i]->y
                                <<", " <<vert[i]->z<<" )"<<endl;
      }
    }
    return 0;
  }
  r = rr;
  s = ss;
  t = tt;
  return 1;
}

void BaseHex::side_mode(const Ordinal face_id, Mode v, dVector &f) const {
  Ordinal i,j;
  switch (face_id){
  case 5: case 0:
    for(i = 0; i < qb; ++i)
      for(j = 0; j < qa; ++j)
        f[i*qa+j] = v.a[j];
    for(i = 0; i < qa; ++i)
      for(j = 0; j < qb; ++j)
        f[j*qa+i] = v.b[j] * f[j*qa+i];
    break;
  case 3: case 1:
    for(i = 0; i < qc; ++i)
       for(j = 0; j < qa; ++j)
         f[i*qa+j] = v.a[j];
    for(i = 0; i < qa; ++i)
      for(j = 0; j < qc; ++j)
        f[j*qa+i] = v.c[j] * f[j*qa+i];
    break;
  case 4: case 2:
    for(i = 0; i < qc; ++i)
        for(j = 0; j < qb; ++j)
          f[i*qb+j] = v.b[j];
    for(i = 0; i < qb; ++i)
      for(j = 0; j<qc; ++j)
        f[j*qb+i] = v.c[j] * f[j*qb+i];
    break;
  default:
    DGM::Comm::World->cerr() << "Illegal Face id for Hex element" <<face_id
                             << endl;
    DGM::Comm::World->exit(DGM::FAILURE);
    break;
  }
}

void BaseHex::side_mode(const Ordinal face_id, Mode *v, dVector &f) const {
  Ordinal i,j;
  switch (face_id){
  case 5: case 0:
    for(i = 0; i < qb; ++i)
      for(j = 0; j < qa; ++j)
        f[i*qa+j] = v->a[j];
    for(i = 0; i < qa; ++i)
      for(j = 0; j < qb; ++j)
        f[j*qa+i] = v->b[j] * f[j*qa+i];
    break;
  case 3: case 1:
    for(i = 0; i < qc; ++i)
       for(j = 0; j < qa; ++j)
         f[i*qa+j] = v->a[j];
    for(i = 0; i < qa; ++i)
      for(j = 0; j < qc; ++j)
        f[j*qa+i] = v->c[j] * f[j*qa+i];
    break;
  case 4: case 2:
    for(i = 0; i < qc; ++i)
        for(j = 0; j < qb; ++j)
          f[i*qb+j] = v->b[j];
    for(i = 0; i < qb; ++i)
      for(j = 0; j<qc; ++j)
        f[j*qb+i] = v->c[j] * f[j*qb+i];
    break;
  default:
    DGM::Comm::World->cerr() << "Illegal Face id for Hex element" <<face_id
                             << endl;
    DGM::Comm::World->exit(DGM::FAILURE);
    break;
  }
}

void BaseHex::push_to_subsides() const {
  for (Ordinal s=0; s<nSides(); ++s) {
    side[s]->push_to_subsides();
  }
}

void BaseHex::push_side_geom_to_subside(Side *ss, const Side *s,
                                        const Scalar J) const {
  // Push normals:
  ss->push_to_subside(s->nx(), ss->nx());
  ss->push_to_subside(s->ny(), ss->ny());
  ss->push_to_subside(s->nz(), ss->nz());
  // normalize
  for (Ordinal i=0; i<ss->nx().size(); ++i) {
    dVector &X=ss->nx(), &Y=ss->ny(), &Z=ss->nz();
    const Scalar l = std::sqrt(X[i]*X[i] + Y[i]*Y[i] + Z[i]*Z[i]);
    if (l) {X[i]/=l; Y[i]/=l; Z[i]/=l;}
  }
  ss->push_to_subside(s->J(),        ss->J());
  ss->push_to_subside(s->J_orig(),   ss->J_orig());
  ss->push_to_subside(s->J_scale(),  ss->J_scale());
  ss->J()      *= J;
  ss->J_orig() *= J;

  Scalar tot = 0; 
  for (Ordinal i=0; i<s->J().size();++i) tot += fabs(s->J()[0] - s->J()[i]);
  if (curve.get() && .000001 < tot) {
    DGM::Comm::World->cerr()<<
      "Hex::push_side_geom_to_subside: do no support curved elements with "
      "hanging nodes across processor boundaries.  Check Sum: "<<tot<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
}

vector<Point> BaseHex::get_side_endpoints(const Ordinal s) const {
  vector<Point>  v(4);
  const Ordinal q1 = (s==2 || s==4) ? qb : qa;
  const Ordinal q2 = (s==0 || s==5) ? qb : qc;
  dVector wkx(q1*q2), wky(q1*q2), wkz(q1*q2);
  get_side(C->x, s, wkx);
  get_side(C->y, s, wky);
  get_side(C->z, s, wkz);
  v[0].x = wkx[      0];  
  v[0].y = wky[      0];  
  v[0].z = wkz[      0];  
  v[1].x = wkx[   q2-1];
  v[1].y = wky[   q2-1];
  v[1].z = wkz[   q2-1];
  v[2].x = wkx[q1*q2-q2];
  v[2].y = wky[q1*q2-q2];
  v[2].z = wkz[q1*q2-q2];
  v[3].x = wkx[q1*q2-1];
  v[3].y = wky[q1*q2-1];
  v[3].z = wkz[q1*q2-1];
  return v;
}

Scalar BaseHex::compute_subside_geometry(Side *ss, const Element &N) const {
  const Ordinal n = ss->base ? ss->base->id() : ss->link->id();
  const vector<Point> nv = (&N)->get_side_endpoints(n);
  const Scalar J = compute_subside_geometry(ss, nv); 
  return J;
}

/** \todo Fix the computation of periodicity */
Scalar BaseHex::compute_subside_geometry(Side *ss, 
                                         const vector<Point> &P) const {
  const Ordinal s = ss->id();

  vector<Point> sv = get_side_endpoints(s);

  /* I simply do not know how to check for periodic BC.
     The coordinates need to be projected from one side to
     the other in the domain, but I don't know the size of the
     domain or what sides are on a periodic boundary.
     The following is a guess. I assume that if the points
     are on a vertical line then since these sides are supposed
     to be shared, they should all be on the same vertical line.
     The same for the horizontal coordinate.  In the standard case
     if s1.x==s2.x then all x coordinates will be the same and no harm
     done.  This logic will fail for non-rectangular periodic domains.
     The real solution is to examine the shared sides that do not have
     hanging nodes to see if the coordinates of the nodes are the same
     and if not deduce the periodicity of the mesh from the difference. */
  bool px = true, py = true, pz = true;
  for (std::size_t i=0;i<P.size()-1;++i) {
    px = (px && sv[i].x==sv[i+1].x && P[i].x==P[i+1].x);
    py = (py && sv[i].y==sv[i+1].y && P[i].y==P[i+1].y);
    pz = (pz && sv[i].z==sv[i+1].z && P[i].z==P[i+1].z);
  }
  if (px) for (Ordinal i=0;i<4;++i) sv[i].x = P[0].x;
  if (py) for (Ordinal i=0;i<4;++i) sv[i].y = P[0].y;
  if (pz) for (Ordinal i=0;i<4;++i) sv[i].z = P[0].z;

  Scalar J;
  J = ss->make_interpolation_matrix(side[s]->q1(), side[s]->q2(), sv, P);
  return J;
}

#ifndef DGM_USE_NODAL_TRI_CUB
void BaseHex::triangle_lift (dVector &h,
                       const dVector &f,  
                       const Ordinal side,
                       const Face    *Us, 
                       const Basis   *psi,
                       const bool    GaussLobatto) {
  throw DGM::exception("SpectralHex:: triangle_lift requires DGM_USE_NODAL_TRI_CUB");
}

#else

namespace {
const dMatrix& side_interpolation(const std::vector< std::array<double,3> > &C,
                                  const Ordinal N) {
  const Ordinal q = (N*(N+1))/2;
  const Ordinal K = numeric_cast<Ordinal>(C.size());

  static map<pair<Ordinal,Ordinal>, dMatrix> WMatrix;
  dMatrix &W = WMatrix[pair<Ordinal,Ordinal>(K,q)];

  if (0==W.size()) {
    W.resize(K, q);
    CMC::Matrix<long double, Ordinal> LW(K,q);
    std::vector<long double> r(K), s(K);
    for (Ordinal i=0; i<K; i++) r[i] = C[i][0];
    for (Ordinal i=0; i<K; i++) s[i] = C[i][1];
    fntri(N, K, r.data(), s.data(), LW);
    for (Ordinal i=0; i<K; ++i)
      for (Ordinal j=0; j<q; ++j)
        W[i][j] = LW[i][j];
  }
  return W;
}
}

void BaseHex::triangle_lift (dVector         &h,
                       const dVector   &f,  
                       const Ordinal side,
                       const Face     *Us, 
                       const Basis   *psi,
                       const bool     GaussLobatto) {
  const Ordinal q1 = Us->q1();
  const Ordinal L  = GaussLobatto ? psi->Ga.rows() : psi->Ba.rows();
  const Ordinal qa = GaussLobatto ? psi->Ga.cols() : psi->Ba.cols();
  const Ordinal qb = GaussLobatto ? psi->Gb.cols() : psi->Bb.cols();
  const Ordinal qc = GaussLobatto ? psi->Gc.cols() : psi->Bc.cols();

  Ordinal N;
  for (N=0; N<100 && q1!=(N*(N+1))/2; ++N);

  if (q1 != N*(N+1)/2) 
    error("SpectralHex::triangle_lift inconsistant dimensions");

  const std::vector< std::array<double,3> > &C = NodalTriCub(L+L+N);

  const dMatrix &V = NodalTet::side_vandermond(N);
  const dMatrix &W = side_interpolation(C,N);

  const Ordinal K = W.rows();

  dVector U (K); 
  dVector T (q1);
  
  mvmult  (V, f, T);
  mvmult  (W, T, U);

  dMatrix Mx(L, K), My(L, K);
  {
    dVector x1(q1);
    dVector x2(q1);

    dVector    Xa(L*L),   Xb(L*L);
    dMatrix XA(Xa,L,L),XB(Xb,L,L);
    dVector xa(L), xb(L), ta(L), tb(L);
    if (GaussLobatto) {
      zwgll(xa,ta);
      zwgll(xb,tb);
    } else {
      zwgl(xa,ta);
      zwgl(xb,tb);
    }
    for (Ordinal i=0; i<L; ++i) 
      for (Ordinal j=0; j<L; ++j) 
        XA(i,j) = xa(i);
    for (Ordinal i=0; i<L; ++i) 
      for (Ordinal j=0; j<L; ++j) 
        XB(i,j) = xb(j);
    Us->push_to_subside(Xa,x1);
    Us->push_to_subside(Xb,x2);

    dVector X1(K), X2(K);
    mvmult  (V,     x1,   T);  
    mvmult  (W,      T,  X1); 
    mvmult  (V,     x2,   T);  
    mvmult  (W,      T,  X2); 
    Basis::make_Legendre(0,L,K,X1,Mx);
    Basis::make_Legendre(0,L,K,X2,My);
  }

  dMatrix G(L,L);    G=0; 
  h.resize(L* L* L); h=0; 
  dArray  H(h, L, L, L);

  for (Ordinal i=0;i<L;++i)
    for (Ordinal j=0;j<L;++j) 
      for (Ordinal k=0;k<K;++k) 
        G(i,j) += Mx(i,k)*My(j,k)*U[k]*C[k][2];
  
  for (Ordinal i=0; i<L; ++i)
    for (Ordinal j=0; j<L; ++j)
      if (N<i+j) G(i,j) = 0;

  switch (side) {
  case 0 : {
    const dMatrix B = GaussLobatto ? psi->Gc : psi->Bc;
    for (Ordinal i=0;i<L;++i)
      for (Ordinal j=0;j<L;++j)
        for (Ordinal k=0;k<L;++k)
          H(i,j,k) += G(i,j)*B(k,0);
    }
    break;
  case 1 : {
    const dMatrix B = GaussLobatto ? psi->Gb : psi->Bb;
    for (Ordinal i=0;i<L;++i)
      for (Ordinal j=0;j<L;++j)
        for (Ordinal k=0;k<L;++k)
          H(i,j,k) += G(i,k)*B(j,0);
    }
    break;
  case 2 : {
    const dMatrix B = GaussLobatto ? psi->Ga : psi->Ba;
    for (Ordinal i=0;i<L;++i)
      for (Ordinal j=0;j<L;++j)
        for (Ordinal k=0;k<L;++k)
          H(i,j,k) += G(j,k)*B(i,qa-1);
    }
    break;
  case 3 : {
    const dMatrix B = GaussLobatto ? psi->Gb : psi->Bb;
    for (Ordinal i=0;i<L;++i)
      for (Ordinal j=0;j<L;++j)
        for (Ordinal k=0;k<L;++k)
          H(i,j,k) += G(i,k)*B(j,qb-1);
    }
    break;
  case 4 : {
    const dMatrix B = GaussLobatto ? psi->Ga : psi->Ba;
    for (Ordinal i=0;i<L;++i)
      for (Ordinal j=0;j<L;++j)
        for (Ordinal k=0;k<L;++k)
          H(i,j,k) += G(j,k)*B(i,0);
    }
    break;
  case 5 : {
    const dMatrix B = GaussLobatto ? psi->Gc : psi->Bc;
    for (Ordinal i=0;i<L;++i)
      for (Ordinal j=0;j<L;++j)
        for (Ordinal k=0;k<L;++k)
          H(i,j,k) += G(i,j)*B(k,qc-1);
    }
    break;
  }
}

#endif

namespace impl {
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
}

void BaseHex::quad_lift (
                      dVector   &h,
                const dVector   &f,  
                const Ordinal side,
                const Face     *Us, 
                const Basis   *psi,
                const bool  GaussLobatto) {
  const Ordinal q1 = Us->q1();
  const Ordinal q2 = Us->q2();
  const Ordinal L  = GaussLobatto ? psi->Ga.rows() : psi->Ba.rows();
  const Ordinal qa = GaussLobatto ? psi->Ga.cols() : psi->Ba.cols();
  const Ordinal qb = GaussLobatto ? psi->Gb.cols() : psi->Bb.cols();
  const Ordinal qc = GaussLobatto ? psi->Gc.cols() : psi->Bc.cols();

  dMatrix F(f,q1,q2);
  {
    dVector w1(q1), w2(q2), t1(q1), t2(q2);
    if (GaussLobatto) {
      zwgll(t1,w1);
      zwgll(t2,w2);
    } else {
      zwgl(t1,w1);
      zwgl(t2,w2);
    }    
    for (Ordinal i=0; i<q1; i++) 
      for (Ordinal j=0; j<q2; j++) 
        F(i,j) *= w1(i)*w2(j);
  }

  dMatrix B1(L,q1); B1=0;
  dMatrix B2(L,q2); B2=0;
  {    
    dVector xa(L), xb(L), ta(L), tb(L);
    if (GaussLobatto) {
      zwgll(xa,ta);
      zwgll(xb,tb);
    } else {
      zwgl(xa,ta);
      zwgl(xb,tb);
    }    

    dVector x1(q1), x2(q2);
    Us->push_to_subside_x(xa,x1);
    Us->push_to_subside_y(xb,x2);
    Basis::make_Legendre(0,L,q1,x1,B1);
    Basis::make_Legendre(0,L,q2,x2,B2);
  }    

  dArray  G;
  const dMatrix *Ba=0, *Bb=0, *Bc=0;
  switch (side) {
  case 0 :
//  dVector w2(L*L); w2=0;
//  dMatrix wk(w2,L,L);
//  dMatrix T (L,q2); T=0;
//  matmult(B2,      F,  T);
//  matmult(B1, 'T', T, wk);
//  for (Ordinal i=0;i<L*L;++i)
//    for (Ordinal j=0;j<L;++j)
//      Fh(i,j) += w2(i) * psi->Bc(j,0);
    G.resize(q1,q2,qc); G=0; 
    for (Ordinal i=0;i<q1;++i)
      for (Ordinal j=0;j<q2;++j) G(i,j,0) = F(i,j);
    Ba = &B2; Bb = &B1; Bc = GaussLobatto ? &psi->Gc : &psi->Bc;
    break;
  case 1 :
    G.resize(q1,qb,q2); G=0; 
    for (Ordinal i=0;i<q1;++i)
      for (Ordinal j=0;j<q2;++j) G(i,0,j) = F(i,j);
    Ba = &B2; Bb = GaussLobatto ? &psi->Gb : &psi->Bb; Bc = &B1;
    break;
  case 2 :
    G.resize(qa,q1,q2); G=0;
    for (Ordinal i=0;i<q1;++i)
      for (Ordinal j=0;j<q2;++j) G(qa-1,i,j) = F(i,j);
    Ba = GaussLobatto ? &psi->Ga : &psi->Ba; Bb = &B2; Bc = &B1;
    break;
  case 3 :
    G.resize(q1,qb,q2); G=0;
    for (Ordinal i=0;i<q1;++i)
      for (Ordinal j=0;j<q2;++j) G(i,qb-1,j) = F(i,j);
    Ba = &B2; Bb = GaussLobatto ? &psi->Gb : &psi->Bb; Bc = &B1;
    break;
  case 4 :
    G.resize(qa,q1,q2); G=0;
    for (Ordinal i=0;i<q1;++i)
      for (Ordinal j=0;j<q2;++j) G(0,i,j) = F(i,j);
    Ba = GaussLobatto ? &psi->Ga : &psi->Ba; Bb = &B2; Bc = &B1;
    break;
  case 5 :
    G.resize(q1,q2,qc); G=0;
    for (Ordinal i=0;i<q1;++i)
      for (Ordinal j=0;j<q2;++j) G(i,j,qc-1) = F(i,j);
    Ba = &B2; Bb = &B1; Bc = GaussLobatto ? &psi->Gc : &psi->Bc;
    break;
  }
  h.resize(L* L* L); h=0;
  dArray  H(h, L, L, L);
  impl::inner_product(H, G, *Ba, *Bb, *Bc);
}

void BaseHex::non_self_simular_lift (
                          dVector   &h,
                    const dVector   &f,  
                    const Ordinal side,
                    const Face     *Us, 
                    const Basis   *psi,
                    const bool    GaussLobatto) {

  const Ordinal q1 = Us->q1();
  const Ordinal q2 = Us->q2();
  const Ordinal L  = GaussLobatto ? psi->Ga.rows() : psi->Ba.rows();
  const Ordinal qa = GaussLobatto ? psi->Ga.cols() : psi->Ba.cols();
  const Ordinal qb = GaussLobatto ? psi->Gb.cols() : psi->Bb.cols();
  const Ordinal qc = GaussLobatto ? psi->Gc.cols() : psi->Bc.cols();
  Ordinal K = q1*q2;

  {
    dMatrix F(f,q1,q2);
    dVector w1(q1), w2(q2), t1(q1), t2(q2);
    if (GaussLobatto) {
      zwgll(t1,w1);
      zwgll(t2,w2);
    } else {
      zwgl(t1,w1);
      zwgl(t2,w2);
    }    
    for (Ordinal i=0; i<q1; i++) 
      for (Ordinal j=0; j<q2; j++) 
        F(i,j) *= w1(i)*w2(j);
  }

  dMatrix Mx(L, K), My(L, K);
  {
    dVector x1(K);
    dVector x2(K);

    dVector    Xa(L*L),   Xb(L*L);
    dMatrix XA(Xa,L,L),XB(Xb,L,L);
    dVector xa(L), xb(L), ta(L), tb(L);
    zwgl(xa,ta);
    zwgl(xb,tb);
    for (Ordinal i=0; i<L; ++i) 
      for (Ordinal j=0; j<L; ++j) 
        XA(i,j) = xa(i);
    for (Ordinal i=0; i<L; ++i) 
      for (Ordinal j=0; j<L; ++j) 
        XB(i,j) = xb(j);
    Us->push_to_subside(Xa,x1);
    Us->push_to_subside(Xb,x2);

    Basis::make_Legendre(0,L,K,x1,Mx);
    Basis::make_Legendre(0,L,K,x2,My);
  }

  dMatrix G(L,L);    G=0; 
  h.resize(L* L* L); h=0; 
  dArray  H(h, L, L, L);
  for (Ordinal i=0;i<L;++i)
    for (Ordinal j=0;j<L;++j) 
      for (Ordinal k=0;k<K;++k)
        G(i,j) += Mx(i,k)*My(j,k)*f(k);
  
  switch (side) {
  case 0 : {
    const dMatrix B=psi->Bc;
    for (Ordinal i=0;i<L;++i)
      for (Ordinal j=0;j<L;++j) 
        for (Ordinal k=0;k<L;++k) 
          H(i,j,k) += G(i,j)*B(k,0);
    }    
    break;
  case 1 : {
    const dMatrix B=psi->Bb;
    for (Ordinal i=0;i<L;++i)
      for (Ordinal j=0;j<L;++j) 
        for (Ordinal k=0;k<L;++k) 
          H(i,j,k) += G(i,k)*B(j,0);
    }    
    break;
  case 2 : {
    const dMatrix B=psi->Ba;
    for (Ordinal i=0;i<L;++i)
      for (Ordinal j=0;j<L;++j)
        for (Ordinal k=0;k<L;++k)
          H(i,j,k) += G(j,k)*B(i,qa-1);
    }
    break;
  case 3 : {
    const dMatrix B=psi->Bb;
    for (Ordinal i=0;i<L;++i)
      for (Ordinal j=0;j<L;++j)
        for (Ordinal k=0;k<L;++k)
          H(i,j,k) += G(i,k)*B(j,qb-1);
    }
    break;
  case 4 : {
    const dMatrix B=psi->Ba;
    for (Ordinal i=0;i<L;++i)
      for (Ordinal j=0;j<L;++j)
        for (Ordinal k=0;k<L;++k)
          H(i,j,k) += G(j,k)*B(i,0);
    }
    break;
  case 5 : {
    const dMatrix B=psi->Bc;
    for (Ordinal i=0;i<L;++i)
      for (Ordinal j=0;j<L;++j)
        for (Ordinal k=0;k<L;++k)
          H(i,j,k) += G(i,j)*B(k,qc-1);
    }
    break;
  }
}

} // namespace DGM
