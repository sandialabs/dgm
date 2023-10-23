/** \file BaseLine.cpp
 *  \brief Base method implementations for all Line elements
 *  \author Scott Collis
*/

// DGM includes
#include "BaseLine.hpp"

namespace DGM {

void BaseLine::make_basis(Basis *psi, const Basis::Type type, const int der) {
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
  psi->amem.resize(qa*max((Ordinal)2,L));

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
}

/// Find the local coordinates (r,s,t) at the point p
Point BaseLine::get_local_coordinates(const Point &p) const {
  Scalar r=0;
  if(!get_local_coordinates(p,r)) {
    DGM::Comm::World->cerr()<<
      "Line::get_local_coordinates: could not find (r,s)"<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  const Point q(r);
  return q;
}

/// Find the local coordinates (r,s,t) at the point p
/*! \note Seems kinda stupid to do a Newton iteration here...? */
int BaseLine::get_local_coordinates(const Point &p, Scalar &r) const {
  const Scalar EPSILON = 1.0e-6;   // tolerance on updates
  const int MAXITER = 100;         // maximum iterations allowed 
  const Scalar TOL = 1.001;        // Tolerance on whether inside element 
  const Scalar DIV = 1.5;          // Allowable divergence for outside element 

  Scalar  drdx;
  Scalar  dx;
  Scalar  xp=0.0;
  Scalar  rr;
  Scalar  x;
  int     converged(0), iter(0);

  r = 0.0;
  x = p.x;
  Scalar length = fabs(x) + measure()*EPSILON;

  dx = 1.0;

  rr = clamp(r, -1.0, 1.0);   // make sure inside element 

  dVector z1(qa);
  dVector w1(qa);
  dMatrix im(1,qa);
  dVector vxp(qa), vdrdx(qa), tmp1(1);

  // Get Gauss-Lobatto-Legendre points and weights
  zwgll(z1,w1);

  while (!converged && iter++ <= MAXITER) {

    xp   = 0.0;
    drdx = 0.0;

    // Form the interpolation matrix
    igllm(im,z1,rr);

    mvmult( im, C->x, tmp1);  // Interpolate the quadrature coordinate of x
    xp = tmp1[0];

    // interpolating mapping metrics
    mvmult( im, geom->rx, tmp1);
    drdx = tmp1[0];

    dx = x - xp;        // Distance from the point (x)
    rr += (drdx * dx);  // Newton update 

    // Convergence test
    if (fabs(dx)/length  < EPSILON) converged = iter;
    if (fabs(rr) > DIV ) converged = -iter;
  }

  if(iter > MAXITER){
    DGM::Comm::World->cerr()<<__FILE__<<":"<<__LINE__<<endl
        <<"BaseLine::get_local_coordinates: did not converge after "
        <<iter<<" iterations."<<endl
        << setiosflags(ios::fixed) << setprecision(8)
        <<"Searching for point : "<< p <<endl
        <<"Last determined location : ( "<<xp<<" )"<<endl
        << *this;
    DGM::Comm::World->cerr()<<"Vertices:"<<endl;
    for(Ordinal i=0;i<nVerts();i++) {
      DGM::Comm::World->cerr()<<" ( "<<vert[i]->x<<" )"<<endl;
    }
    return 0;
  }
  if (fabs(rr) > TOL ) {
    if (DGM::Comm::World->verbosity()>4) {
      DGM::Comm::World->cerr()<<__FILE__<<":"<<__LINE__
          <<"BaseLine::get_local_coordinates: point outside element"<<endl
          <<"    "<< fabs(rr) <<" > " << TOL << endl
          << setiosflags(ios::fixed) << setprecision(8)
          <<"Searching for point : "<< p <<endl
          <<"Last determined location : ( "<<xp<<" )"<<endl
          << *this;
      DGM::Comm::World->cerr()<<"Vertices:"<<endl;
      for(Ordinal i=0;i<nVerts();i++) {
        DGM::Comm::World->cerr()<<" ( "<<vert[i]->x<<" )"<<endl;
      }
    }
    return 0;
  }
  r = rr;
  return 1;
}

} // namespace DGM
