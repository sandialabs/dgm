// -*- c++ -*-w
/**
 *  \file  Polylib.tpp
 *  \brief Library routines for polynomial calculus and interpolation
*/

///////////////////////////////////////////////////////////////////////////////
//
// Adapted from Polylib
//
// For more information, please see: http://www.nektar.info
//
// The MIT License
//
// Copyright (c) 2006 Division of Applied Mathematics, Brown University (USA),
// Department of Aeronautics, Imperial College London (UK), and Scientific
// Computing and Imaging Institute, University of Utah (USA).
//
// License for the specific language governing rights and limitations under
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//
///////////////////////////////////////////////////////////////////////////////
/*

  LIBRARY ROUTINES FOR ORTHOGONAL POLYNOMIAL CALCULUS AND INTERPOLATION

  Spencer Sherwin
  Center for Fluid Mechanics
  Division of Applied Mathematics
  Brown University
  Providence
  RI 02912,  USA

  Based on splib.c by Einar Ronquist and Ron Henderson

  Abbreviations
  z    -   Set of collocation/quadrature points
  w    -   Set of quadrature weights
  d    -   Derivative operator
  h    -   Lagrange Interpolant
  i    -   Interpolation operator
  g    -   Gauss
  gr   -   Gauss-Radau
  gl   -   Gauss-Lobatto
  j    -   Jacobi
  l    -   Legendre  (Jacobi with alpha = beta =  0.0)
  c    -   Chebychev (Jacobi with alpha = beta = -0.5)
  m    -   Arbritrary mesh

  -----------------------------------------------------------------------
                         M A I N     R O U T I N E S
  -----------------------------------------------------------------------

  Points and Weights:

  zwgj        Compute Gauss-Jacobi         points and weights
  zwgrj       Compute Gauss-Radau-Jacobi   points and weights
  zwglj       Compute Gauss-Lobatto-Jacobi points and weights

  Derivative Operators:

  dgj         Compute Gauss-Jacobi         derivative matrix
  dgrj        Compute Gauss-Radau-Jacobi   derivative matrix
  dglj        Compute Gauss-Lobatto-Jacobi derivative matrix

  Lagrange Interpolants:

  hgj         Compute Gauss-Jacobi         Lagrange interpolants
  hgrj        Compute Gauss-Radau-Jacobi   Lagrange interpolants
  hglj        Compute Gauss-Lobatto-Jacobi Lagrange interpolants

  Interpolation Operators:

  igjm        Compute interpolation operator gj->m
  igrjm       Compute interpolation operator grj->m
  igljm       Compute interpolation operator glj->m

  -----------------------------------------------------------------------
                     L O C A L      R O U T I N E S
  -----------------------------------------------------------------------

  Polynomial Evaluation:

  jacobf      Returns value of Jacobi polynomial for given points
  jacobd      Returns derivative of Jacobi polynomial for given points
  jacobz      Returns Jacobi polynomial zeros
  jaczfd      Returns value and derivative of Jacobi poly. at point z

  gammaf      Gamma function for integer values and halves

  -----------------------------------------------------------------------
                         M A C R O S
  -----------------------------------------------------------------------

  Legendre  polynomial alpha = beta = 0
  Chebychev polynomial alpha = beta = -0.5

  Points and Weights:

  zwgl        Compute Gauss-Legendre          points and weights
  zwgrl       Compute Gauss-Radau-Legendre    points and weights
  zwgll       Compute Gauss-Lobatto-Legendre  points and weights

  zwgc        Compute Gauss-Chebychev         points and weights
  zwgrc       Compute Gauss-Radau-Chebychev   points and weights
  zwglc       Compute Gauss-Lobatto-Chebychev points and weights

  Derivative Operators:

  dgl         Compute Gauss-Legendre          derivative matrix
  dgrl        Compute Gauss-Radau-Legendre    derivative matrix
  dgll        Compute Gauss-Lobatto-Legendre  derivative matrix

  dgc         Compute Gauss-Chebychev         derivative matrix
  dgrc        Compute Gauss-Radau-Chebychev   derivative matrix
  dglc        Compute Gauss-Lobatto-Chebychev derivative matrix

  Lagrangian Interpolants:

  hgl         Compute Gauss-Legendre          Lagrange interpolants
  hgrl        Compute Gauss-Radau-Legendre    Lagrange interpolants
  hgll        Compute Gauss-Lobatto-Legendre  Lagrange interpolants

  hgc         Compute Gauss-Chebychev         Lagrange interpolants
  hgrc        Compute Gauss-Radau-Chebychev   Lagrange interpolants
  hglc        Compute Gauss-Lobatto-Chebychev Lagrange interpolants

  Interpolation Operators:

  iglm        Compute interpolation operator gl->m
  igrlm       Compute interpolation operator grl->m
  igllm       Compute interpolation operator gll->m

  igcm        Compute interpolation operator gc->m
  igrcm       Compute interpolation operator grc->m
  iglcm       Compute interpolation operator glc->m

  Polynomial functions

  jacobf      Evaluate the Jacobi polynomial at vector of points
  jacobd      Evaluate the derivative of Jacobi poly at vector of points

  ------------------------------------------------------------------------

  Useful references:

  [1] Gabor Szego: Orthogonal Polynomials, American Mathematical Society,
      Providence, Rhode Island, 1939.
  [2] Abramowitz & Stegun: Handbook of Mathematical Functions,
      Dover, New York, 1972.
  [3] Canuto, Hussaini, Quarteroni & Zang: Spectral Methods in Fluid
      Dynamics, Springer-Verlag, 1988.
  [4] Ghizzetti & Ossicini: Quadrature Formulae, Academic Press, 1970.


  NOTES
  -----
  (1) All routines are Scalar precision.
  (2) All array subscripts start from zero, i.e. vector[0..N-1]
  (3) Matrices should be allocated as true 2-dimensional arrays with
      row and column indices starting from 0.

*---------------------------------------------------------------------------*/

// system includes
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <sys/types.h>

// DGM includes
#include "Comm.hpp"
#include "Types.hpp"
#include "Polylib.hpp"

#include "boost/numeric/conversion/cast.hpp"

namespace DGM {

/// maxium iterations
#define STOP 30
//#define STOP 50

/// tolerance
static const double EPS=1.0e-12;
//#define EPS 1.0e-15

/// \name Polylib local functions
//@{

namespace {

//===========================================================================
// Functions needed to calculate nodal triangle/tetrahedra quadrature
//===========================================================================

/// Computes alpha used by warp function enumerated above (N > 0)
template <typename Ordinal>
Scalar alpha_for_warp_tri(const Ordinal N) {
  using boost::numeric_cast;
  static const Scalar warp_alpha_tri[16] = {
         0,      0,      0, 1.4152, 0.1001, 0.2751,
    0.9808, 1.0999, 1.2853, 1.3648, 1.4773, 1.4959,
    1.5743, 1.5770, 1.6223, 1.6258 };
  unsigned int n = numeric_cast<unsigned int>(N);
  if (n > 15) {
    return(Scalar(5)/Scalar(3));
  }
  return warp_alpha_tri[n];
}

/// Computes alpha used by the warp function (N > 0)
template <typename Ordinal>
Scalar alpha_for_warp_tet(const Ordinal N) {
  static const Scalar warp_alpha_tet[16] = {
          0,      0,      0,      0,
     0.1002, 1.1332, 1.5608, 1.3413,
     1.2577, 1.1603, 1.0153, 0.6080,
     0.4523, 0.8856, 0.8717, 0.9655 };
  const Scalar alpha = (N<16) ? warp_alpha_tet[N] : 1;
  return alpha;
}

/// Lagrange polynomials on a uniform mesh
/** Calculates l_j(r), where l_j is the j^th Lagrange
    basis function on an equispaced mesh with Porder+1 nodes.
    It's needed for the warping function to set up quadrature nodes. */
template <typename Scalar, typename Ordinal>
Scalar uniform_lagrange(const Scalar r, const Ordinal j, const Ordinal N) {
  Scalar node, node_j;
  Scalar result;
  result = Scalar(1);
  node_j = Scalar(2*j)/Scalar(N) - Scalar(1);
  for (Ordinal i=0; i<=N; i++) {
    node = Scalar(2*i)/Scalar(N) - Scalar(1);
    if (i!=j) result*=(r-node)/(node_j-node);
  }
  return(result);
}

/// Calculates the warp function w(r) from HW08
/** Actually calculates w-tilde, bottom of page 176: w(r)/(1-r^2))   */
template <typename Scalar, typename Ordinal>
Scalar warp_function(const Scalar* gll, const Scalar* unif,
                     const Scalar r, const Ordinal N) {
  // w(-1) = w(1) = 0
  if (r*r == 1) return(0);
  Scalar result = 0;
  for(Ordinal i=0; i<=N; i++) {
    result += (gll[i]-unif[i])*uniform_lagrange(r,i,N);
  }
  return(result/(1-r*r));
}

//===========================================================================
// Helper functions for Polylib
//===========================================================================

/// Function and derivatives of the Jacobi polynomial
/** This is a function to calculate the value of the n_th order jacobi
    polynomial and it's derivative at a point z for use with jacobz,
    hgj, hgrj and hgrl. (-1 < z < 1). */
template <typename Scalar, typename Ordinal>
void jaczfd(Scalar z, Scalar *poly, Scalar *polyd, Ordinal n,
            Scalar alpha, Scalar beta) {
  Scalar one = 1.0, two = 2.0;
  if(n == 0){
    *poly  = one;
    *polyd = 0.0;
  }
  else if (n == 1){
    *poly  = 0.5*(alpha - beta + (alpha + beta + two)*z);
    *polyd = 0.5*(alpha + beta + two);
  }
  else{
    Ordinal k;
    Scalar   a1,a2,a3,a4;
    Scalar   apb = alpha + beta;
    Scalar   polyn1,polyn2;

    polyn2 = one;
    polyn1 = 0.5*(alpha - beta + (apb + two)*z);

    for(k = 2; k <= n; ++k){
      a1 =  two*k*(k + apb)*(two*k + apb - two);
      a2 = (two*k + apb - one)*(alpha*alpha - beta*beta);
      a3 = (two*k + apb - two)*(two*k + apb - one)*(two*k + apb);
      a4 =  two*(k + alpha - one)*(k + beta - one)*(two*k + apb);

      *poly  = ((a2 + a3*z)*polyn1 - a4*polyn2)/a1;
      polyn2 = polyn1;
      polyn1 = *poly;
    }
    polyn1 = polyn2;
    *polyd  = n*(alpha - beta - (two*n + alpha + beta)*z)*poly[0];
    *polyd += two*(n + alpha)*(n + beta)*polyn1;
    *polyd /= (two*n + alpha + beta)*(one - z*z);
  }
  return;
}

/// Gamma function for integer values and halves
/** Calculate the gamma function for integer values and halves
    i.e. gamma(n) = (n-1)!   gamma(n+1/2) = (n-1/2)*gamma(n-1/2)
    where gamma(1/2) = sqrt(PI). */
double gammaF(double x){
  double gamma = 1.0;
  if (x == -0.5) gamma = -2.0*sqrt(M_PI);
  else if (!x) return gamma;
  else if ((x-(long long)x) == 0.5){
    long long n = (long long) x;
    double tmp = x;
    gamma = sqrt(M_PI);
    while(n--){
      tmp   -= 1.0;
      gamma *= tmp;
    }
  }
  else if ((x-(long long)x) == 0.0){
    long long n = (long long) x;
    double tmp = x;
    while(--n){
      tmp   -= 1.0;
      gamma *= tmp;
    }
  }
  else
    fprintf(stderr,"%f is not of integer of half order\n",x);
  return gamma;
}

/// Zeros of the Jacobi polynomial
/**  Compute zeros z of the n_th order Jacobi  polynomial.
     alpha > -1, beta > -1. */
template <typename Scalar, typename Ordinal>
void jacobz(Ordinal n, Scalar *z, Scalar alpha, Scalar beta){
  if(!n) return;
  Ordinal i,j,k;
  Scalar dth = M_PI/(2.0*(Scalar)n);
  Scalar poly=0.0,pder,rlast=0.0;
  Scalar sum,delr,r;
  Scalar one = 1.0, two = 2.0;
  for(k = 0; k < n; ++k){
    r = -cos((two*(Scalar)k + one) * dth);
    if(k) r = 0.5*(r + rlast);
    for(j = 1; j < STOP; ++j){
      jaczfd(r,&poly, &pder, n, alpha, beta);
      for(i = 0, sum = 0.0; i < k; ++i) sum += one/(r - z[i]);
      delr = -poly / (pder - sum * poly);
      r   += delr;
      if( fabs(delr) < EPS ) break;
    }
    z[k]  = r;
    rlast = r;
  }
  return;
}

}  // anonymous namespace

//@}

/*----------------------------------------------------------------------
  zwgj() - Gauss-Jacobi Points and Weights

  Generate np Gauss Jacobi points (z) and weights (w) associated with
  the Jacobi polynomial P^{alpha,beta}_np (alpha >-1,beta >-1).

  Exact for polynomials of order 2np-1 or less
 -----------------------------------------------------------------------*/

template <typename Scalar, typename Ordinal>
void zwgj (Scalar *z, Scalar *w, Ordinal np, Scalar alpha, Scalar beta){
  Ordinal i;
  Scalar fac, one = 1.0, two = 2.0, apb = alpha + beta;

  jacobz(np,z,alpha,beta);
  jacobd(np,z,w,np,alpha,beta);

  if (alpha || beta) {
    fac  = pow(two,apb + one)*gammaF(alpha + np + one)*gammaF(beta + np + one);
    fac /= gammaF(np + one)*gammaF(apb + np + one);
  } else {
    fac  = 2.0;
  }

  for(i = 0; i < np; ++i) w[i] = fac/(w[i]*w[i]*(one-z[i]*z[i]));

  return;
}

/*----------------------------------------------------------------------
  zwgrj() - Gauss-Radau-Jacobi Points and Weights

  Generate np Gauss-Radau-Jacobi points (z) and weights (w) associated
  with the Jacobi polynomial P^(alpha,beta)_{np-1}.

  Exact for polynomials of order 2np-2 or less
 -----------------------------------------------------------------------*/

template <typename Scalar, typename Ordinal>
void zwgrj(Scalar *z, Scalar *w, Ordinal np, Scalar alpha, Scalar beta){
  if(np == 1){
    z[0] = 0.0;
    w[0] = 2.0;
  } else {
    Ordinal i;
    Scalar fac, one = 1.0, two = 2.0, apb = alpha + beta;

    z[0] = -one;
    jacobz (np-1,z+1,alpha,beta+1);
    jacobf (np,z,w,np-1,alpha,beta);

    if (alpha || beta) {
      fac  = pow(two,apb)*gammaF(alpha + np)*gammaF(beta + np);
      fac /= gammaF(np)*(beta + np)*gammaF(apb + np + 1);
    } else {
      fac  = 1.0/(np*np);
    }

    for(i = 0; i < np; ++i) w[i] = fac*(1-z[i])/(w[i]*w[i]);
    w[0] *= (beta + one);
  }
  return;
}

/*---------------------------------------------------------------------
  Generate np Gauss-Lobatto-Jacobi points (z) and weights (w)
  associated with Jacobi polynomial P^{alpha,beta}_{np-2}
  (alpha>-1,beta>-1).

  Exact for polynomials of order 2np-3 or less
 ---------------------------------------------------------------------*/

template <typename Scalar, typename Ordinal>
void zwglj(Scalar *z, Scalar *w, Ordinal np, Scalar alpha, Scalar beta){
  if( np == 1 ) {
    z[0] = 0.0;
    w[0] = 2.0;
  } else {
    Ordinal i;
    Scalar   fac, one = 1.0, apb = alpha + beta, two = 2.0;

    z[0]    = -one;
    z[np-1] =  one;
    jacobz (np-2,z + 1,alpha + one,beta + one);
    jacobf (np,z,w,np-1,alpha,beta);

    if (alpha || beta) {
      fac  = pow(two,apb + 1)*gammaF(alpha + np)*gammaF(beta + np);
      fac /= (np-1)*gammaF(np)*gammaF(alpha + beta + np + one);
    } else {
      fac  = 2.0/((np*(np-1)));
    }

    for(i = 0; i < np; ++i) w[i] = fac/(w[i]*w[i]);
    w[0]    *= (beta  + one);
    w[np-1] *= (alpha + one);
  }
  return;
}

/*---------------------------------------------------------------------
  zwntri() - Compute nodes for NodalTri on reference triangle:
             vertices at (-1,-1), (1,-1), and (-1,1)

             Based on Hesthaven and Warburton 2008, Ch. 6

           2
   ^       |\
   |       | \
           |  \
   s       |   \
           0----1

            r ->

Use this code to create tecplot file for debug purposes:
void create_tecplot_of_tri_points() {
  const DGM::Ordinal L=11;
  const DGM::Ordinal N=L*(L+1)/2;
  DGM::Scalar r[N]={0};
  DGM::Scalar s[N]={0};
  DGM::zwntri(r,s,L-1);
  unsigned E = 0;
  for (int l=L, k=0; k<N; k+=l, --l) {
    for (int i=k, j=k+l; i<k+l-1; ++i, ++j) {
      ++E;
      if (i!=k+l-2) ++E;
    }
  }
  cout <<"TITLE=\"Triangle Mesh\""<<endl;
  cout <<"VARIABLES=\"x\",\"y\""<<endl;
  cout <<"ZONE NODES="<<N<<", ELEMENTS="<<E
       <<", DATAPACKING=POINT, ZONETYPE=FETRIANGLE"<<endl;

  for (int i=0; i<N; ++i) {
    std::cout << r[i]<<" "<<s[i]<<endl;
    for (int l=L, k=0; k<N; k+=l, --l) {
      for (int i=k, j=k+l; i<k+l-1; ++i, ++j) {
        cout               <<i+1<<" "<<i+2<<" "<<j+1<<endl;
        if (i!=k+l-2) cout <<i+2<<" "<<j+2<<" "<<j+1<<endl;
      }
    }
  }
}

 ---------------------------------------------------------------------*/
template <typename Scalar, typename Ordinal>
void zwntri(Scalar *r, Scalar *s, const Ordinal N) {
  // Step 1: Set up uniform nodes (Porder+1 nodes on [-1,1])
  //         They are needed (along w/ GLL) for the warping function
  Scalar gll_node[N+1], gll_wght[N+1];
  Scalar uniform_node[N+1];
  zwgll(gll_node, gll_wght, N+1);

  for (Ordinal i=0; i<=N; i++) {
    uniform_node[i] = Scalar(2*i)/Scalar(N) - Scalar(1);
  }
  // Step 2: Calculate triangle cubature nodes
  Scalar l0, l1, l2;
  Scalar dx, dy, w[3], b[3], alpha = alpha_for_warp_tri(N);

  for (Ordinal i=0, m=0; i<=N; i++)
    for (Ordinal j=0; i+j<=N; j++, m++) {
      // Step 2a: Start with evenly-spaced (barycentric)
      l0 = Scalar(i)/Scalar(N);
      l1 = Scalar(N-i-j)/Scalar(N);
      l2 = Scalar(j)/Scalar(N);
      r[m] = -l1 + l2 - l0;
      s[m] = -l1 - l2 + l0;

      // Step 2b: Apply warping function
      w[0] = warp_function(gll_node, uniform_node, l2-l1, N);
      w[1] = warp_function(gll_node, uniform_node, l0-l2, N);
      w[2] = warp_function(gll_node, uniform_node, l1-l0, N);

      b[0] = 4*l1*l2;
      b[1] = 4*l2*l0;
      b[2] = 4*l0*l1;

      w[0] = b[0]*w[0]*(1+(alpha*l0)*(alpha*l0));
      w[1] = b[1]*w[1]*(1+(alpha*l1)*(alpha*l1));
      w[2] = b[2]*w[2]*(1+(alpha*l2)*(alpha*l2));

      dx = w[0] - w[1];
      dy = w[1] - w[2];

      r[m] += dx;
      s[m] += dy;
    }
}

//-----------------------------------------------------------------------------

namespace {

template <typename Scalar, typename Ordinal>
void EquiNodes3D(const Ordinal N, Scalar*X, Scalar*Y, Scalar*Z)
{
  // Purpose: compute the equidistributed nodes on the
  //          reference equilateral tetrahedron

  const Scalar t=Scalar(2)/N;
  for (Ordinal     n=0, k=0; n <= N;     ++n) {
    for (Ordinal   m=0;    m+n <= N;     ++m) {
      for (Ordinal q=0;  q+m+n <= N; ++k,++q) {
        X[k] = t*q-1;
        Y[k] = t*m-1;
        Z[k] = t*n-1;
      }
    }
  }
}

template <typename Scalar, typename Ordinal>
Scalar evalwarp(const Ordinal p,
                const Scalar *xnodes,
                const Scalar *xeq,
                const Scalar xout)
{
  // function warp = evalwarp(p, xnodes, xout)
  // Purpose: compute one-dimensional edge warping function

  Scalar warp = 0;

  for (Ordinal i=0; i<p+1; ++i) {
    Scalar d = (xnodes[i]-xeq[i]);
    for (Ordinal j=1; j<p; ++j) {
      if (i!=j) d *= ((xout-xeq[j]) / (xeq[i]-xeq[j]));
    }

    if (i!=0) d /= -(xeq[i]-xeq[0]);
    if (i!=p) d /=  (xeq[i]-xeq[p]);

    warp += d;
  }
  return warp;
}

template <typename Scalar, typename Ordinal>
void WarpShiftFace3D ( const Scalar *gaussX,
                       const Scalar *xeq,
                       const Ordinal p,
                       const Scalar  pval,
                       const Scalar  L2,
                       const Scalar  L3,
                       const Scalar  L4,
                             Scalar& dx,
                             Scalar& dy) {
  // function [dx, dy] = evalshift(p, pval, L2, L3, L4)
  // Purpose: compute two-dimensional Warp & Blend transform

  // 1) gaussX  Gauss-Lobatto-Legendre node distribution

  // 3) compute blending function at each node for each edge
  const Scalar blend1 = L3*L4;
  const Scalar blend2 = L2*L4;
  const Scalar blend3 = L2*L3;

  // 4) amount of warp for each node, for each edge
  const Scalar tv1=L4-L3, tv2=L2-L4, tv3=L3-L2;
  const Scalar warpfactor1 = 4 * evalwarp(p, gaussX, xeq, tv1);
  const Scalar warpfactor2 = 4 * evalwarp(p, gaussX, xeq, tv2);
  const Scalar warpfactor3 = 4 * evalwarp(p, gaussX, xeq, tv3);

  // 5) combine blend & warp
  const Scalar warp1 = blend1*warpfactor1 * (1 + pval*L2*pval*L2);
  const Scalar warp2 = blend2*warpfactor2 * (1 + pval*L3*pval*L3);
  const Scalar warp3 = blend3*warpfactor3 * (1 + pval*L4*pval*L4);

  // 6) evaluate shift in equilateral triangle
  const Scalar sqrt3 = sqrt(Scalar(3));
  dx = 1*warp1 -       warp2/2 -       warp3/2;
  dy = 0*warp1 + sqrt3*warp2/2 - sqrt3*warp3/2;
}

/** \warning SOLVE_EPSILON should come from numeric_limits depending on
    Scalar type. */
template <typename Scalar>
bool invert_3x3(const Scalar A[3][3], Scalar iA[3][3]){
 const Scalar SOLVE_EPSILON = 1.e-10;
 const Scalar det =
       A[0][0] * (A[2][2]*A[1][1] - A[2][1]*A[1][2])
     - A[1][0] * (A[2][2]*A[0][1] - A[2][1]*A[0][2])
     + A[2][0] * (A[1][2]*A[0][1] - A[1][1]*A[0][2]);
 if( fabs(det) < SOLVE_EPSILON ) return true;

 iA[0][0] =  (A[2][2]*A[1][1]-A[2][1]*A[1][2])/det;
 iA[0][1] = -(A[2][2]*A[0][1]-A[2][1]*A[0][2])/det;
 iA[0][2] =  (A[1][2]*A[0][1]-A[1][1]*A[0][2])/det;

 iA[1][0] = -(A[2][2]*A[1][0]-A[2][0]*A[1][2])/det;
 iA[1][1] =  (A[2][2]*A[0][0]-A[2][0]*A[0][2])/det;
 iA[1][2] = -(A[1][2]*A[0][0]-A[1][0]*A[0][2])/det;

 iA[2][0] =  (A[2][1]*A[1][0]-A[2][0]*A[1][1])/det;
 iA[2][1] = -(A[2][1]*A[0][0]-A[2][0]*A[0][1])/det;
 iA[2][2] =  (A[1][1]*A[0][0]-A[1][0]*A[0][1])/det;

 return false;
}

template <typename Scalar>
bool solve_3x3(Scalar x[3], const Scalar A[3][3], const Scalar b[3]){
 Scalar iA[3][3]={{0}};
 if( invert_3x3( A, iA ) ) return true;
 x[0] = iA[0][0]*b[0] + iA[0][1]*b[1] + iA[0][2]*b[2];
 x[1] = iA[1][0]*b[0] + iA[1][1]*b[1] + iA[1][2]*b[2];
 x[2] = iA[2][0]*b[0] + iA[2][1]*b[1] + iA[2][2]*b[2];
 return false;
}

template <typename Scalar>
void xyztorst ( const Scalar  X,
                const Scalar  Y,
                const Scalar  Z,
                      Scalar &r,
                      Scalar &s,
                      Scalar &t)
//---------------------------------------------------------
{
  // function [r,s,t] = xyztorst(x, y, z)
  // Purpose : Transfer from (x,y,z) in equilateral tetrahedron
  //           to (r,s,t) coordinates in standard tetrahedron

  const Scalar sqrt3 = sqrt(Scalar(3));
  const Scalar sqrt6 = sqrt(Scalar(6));

  const Scalar v1[3] = {-1, -1/sqrt3,  -1/sqrt6};
  const Scalar v2[3] = { 1, -1/sqrt3,  -1/sqrt6};
  const Scalar v3[3] = { 0,  2/sqrt3,  -1/sqrt6};
  const Scalar v4[3] = { 0,  0      ,   3/sqrt6};

  Scalar A[3][3];
  for (unsigned j=0; j<3; j++) {
    A[j][0] = (v2[j]-v1[j])/2;
    A[j][1] = (v3[j]-v1[j])/2;
    A[j][2] = (v4[j]-v1[j])/2;
  }

  const Scalar XYZ[3] = {X,Y,Z};
  // back out right tet nodes
  Scalar rhs[3];
  for (unsigned j=0; j<3; j++) rhs[j]=XYZ[j]-(v2[j]+v3[j]+v4[j]-v1[j])/2;

  Scalar rst[3] = {0};

  // \todo A is a constant matrix and somebody should just
  // fire up Mathematica to get the inverse and hard code it.
  // Ai[3][3]={{1,0,0},{-1/sqrt3,2/sqrt3,0},{-1/sqrt6,-1/sqrt6,sqrt6/2}};
  solve_3x3(rst,A,rhs);

  r = rst[0];
  s = rst[1];
  t = rst[2];
}

}  // anonymous namespace

//-----------------------------------------------------------------------------

/*---------------------------------------------------------------------
  zwntet() - Compute nodes for NodalTet on reference tetrahedron:
             vertices at (-1,-1, -1), (1,-1, -1),  (-1, 1, -1),
             and (-1, -1, 1)
             Based on Hesthaven and Warburton 2008, Ch. 10
This can be checked with the following code:

void create_tecplot_of_tet_points() {
  const DGM::Ordinal L=13;
  const DGM::Scalar eps=1.e-10;
  const DGM::Ordinal N=L*(L+1)*(L+2)/6;
  DGM::Scalar r[N]={0};
  DGM::Scalar s[N]={0};
  DGM::Scalar t[N]={0};
  DGM::zwntet(r,s,t,L-1);
  unsigned E = 0;
  for (int m=L, n=0; n<N; n+=m*(m+1)/2, --m) {
    const DGM::Ordinal M = m*(m+1)/2;
    for (int l=m, k=0; k<M; k+=l, --l) {
      for (int i=k, j=k+l; i<k+l-1; ++i, ++j) {
        ++E;
      }
    }
  }
  for (int i=0; i<N; ++i) {
    if (abs(r[i]) < eps) r[i]=0;
    if (abs(s[i]) < eps) s[i]=0;
    if (abs(t[i]) < eps) t[i]=0;
  }
  cout <<"TITLE=\"Tet Mesh\""<<endl;
  cout <<"VARIABLES=\"x\",\"y\",\"z\""<<endl;
  cout <<"ZONE NODES="<<N<<", ELEMENTS="<<E
       <<", DATAPACKING=POINT, ZONETYPE=FETETRAHEDRON"<<endl;

  for (int i=0; i<N; ++i) {
    std::cout << r[i]<<" "<<s[i]<<" "<<t[i]<<endl;
  }
  for (int m=L, n=0, o=1+L*(L+1)/2; n<N; n+=m*(m+1)/2, --m) {
    const DGM::Ordinal M = m*(m+1)/2;
    for (int l=m, k=0; k<M; k+=l, --l) {
      for (int i=k+n, j=k+l+n; i<k+l-1+n; ++i, ++j, ++o) {
        cout <<i+1<<" "<<i+2<<" "<<j+1<<" "<<o<<endl;
      }
    }
  }
}
 ---------------------------------------------------------------------*/
template <typename Scalar, typename Ordinal>
void zwntet(Scalar *r, Scalar *s, Scalar *t, const Ordinal N) {

  const Ordinal Np = (N+1)*(N+2)*(N+3)/6;
  const Scalar  sqrt3 = sqrt(Scalar(3));
  const Scalar  sqrt6 = sqrt(Scalar(6));
  const Scalar    tol = 1e-10;

  const Scalar alpha = alpha_for_warp_tet(N);

  // set vertices of tetrahedron
  const Scalar v1[3]={-1, -1/sqrt3, -1/sqrt6};
  const Scalar v2[3]={ 1, -1/sqrt3, -1/sqrt6};
  const Scalar v3[3]={ 0,  2/sqrt3, -1/sqrt6};
  const Scalar v4[3]={ 0,  0      ,  3/sqrt6};

  // orthogonal axis tangents on faces 1-4
  Scalar t1[4][3] = {{0}};
  Scalar t2[4][3] = {{0}};

  for (Ordinal j=0; j<3; ++j) {
    t1[0][j] = v2[j]-v1[j];
    t1[1][j] = v2[j]-v1[j];
    t1[2][j] = v3[j]-v2[j];
    t1[3][j] = v3[j]-v1[j];
    t2[0][j] = v3[j]-(v1[j]+v2[j])/2;
    t2[1][j] = v4[j]-(v1[j]+v2[j])/2;
    t2[2][j] = v4[j]-(v2[j]+v3[j])/2;
    t2[3][j] = v4[j]-(v1[j]+v3[j])/2;
  }

  for (Ordinal i=0; i<4; ++i) {
    Scalar v1=0, v2=0;
    for (Ordinal j=0; j<3; ++j) v1 += t1[i][j]*t1[i][j];
    for (Ordinal j=0; j<3; ++j) v2 += t2[i][j]*t2[i][j];
    v1 = sqrt(v1); v2 = sqrt(v2);
    for (Ordinal j=0; j<3; ++j) t1[i][j] /= v1;
    for (Ordinal j=0; j<3; ++j) t2[i][j] /= v2;
  }

  Scalar X[Np], Y[Np], Z[Np];
  // Step 1: Set up uniform nodes (Porder+1 nodes on [-1,1])
  //         They are needed (along w/ GLL) for the warping function

  EquiNodes3D(N,X,Y,Z); // create equidistributed nodes

  Scalar gll_node[N+1], gll_wght[N+1];
  Scalar uniform_node[N+1];
  const Scalar twoN=Scalar(2)/N;

  zwgll(gll_node, gll_wght, N+1);
  for (Ordinal i=0; i<=N; i++) uniform_node[i] = i*twoN - 1;

  // Step 2: Calculate tetrahedron cubature nodes
  for (Ordinal     i=0,m=0; i<=N; i++) {
    for (Ordinal   j=0;   j+i<=N; j++) {
      for (Ordinal k=0; k+j+i<=N; k++, m++) {
        // Step 2a: Start with evenly-spaced (barycentric)
        Scalar XYZ[3]={0}, shift[3]={0};

        const Scalar L1 =           (1+Z[m])/2;
        const Scalar L2 =           (1+Y[m])/2;
        const Scalar L3 =-(1+X[m]+Y[m]+Z[m])/2;
        const Scalar L4 =           (1+X[m])/2;

        for (Ordinal j=0; j<3; ++j)
          XYZ[j] = L3*v1[j] + L4*v2[j] + L2*v3[j] + L1*v4[j];


        Scalar La=0, Lb=0, Lc=0, Ld=0;
        for (unsigned face=0; face<4; ++face) {
          if      (0==face) { La = L1; Lb = L2; Lc = L3; Ld = L4; }
          else if (1==face) { La = L2; Lb = L1; Lc = L3; Ld = L4; }
          else if (2==face) { La = L3; Lb = L1; Lc = L4; Ld = L2; }
          else              { La = L4; Lb = L1; Lc = L3; Ld = L2; }

          // compute warp tangential to face
          Scalar warp1=0, warp2=0;
          WarpShiftFace3D(gll_node, uniform_node,
                          N, alpha, Lb, Lc, Ld, warp1, warp2);

          Scalar blend = Lb * Lc * Ld;   // compute volume blending
          const Scalar La2 = La/2;
          const Scalar denom = (Lb+La2)*(Lc+La2)*(Ld+La2);//modify linear blend

          if (denom > tol) {
            const Scalar tv1 = 1+alpha*La*alpha*La;
            const Scalar tv2 = blend / denom;
            blend = tv1 * tv2;
          }

          // fix face warp
          if (La<tol && (Lb<tol || Lc<tol || Ld<tol)) {
            for (Ordinal j=0; j<3; ++j)
              shift[j]  = warp1 * t1[face][j] +
                          warp2 * t2[face][j];
          } else {
            for (Ordinal j=0; j<3; ++j)
              shift[j] += blend * warp1 * t1[face][j] +
                          blend * warp2 * t2[face][j];
          }
        }
        for (Ordinal j=0; j<3; ++j) XYZ[j] += shift[j];
        xyztorst (XYZ[0], XYZ[1], XYZ[2], r[m], s[m], t[m]);
      }
    }
  }
}

/*---------------------------------------------------------------------
  dgj() - Compute the Derivative Matrix

  Compute the derivative matrix d and its transpose dt associated with
  the n_th order Lagrangian interpolants through the np Gauss-Jacobi
  points z.

               du
               --  = D   * u  evaluated at z = z
               dz     ij    j                   i

  NOTE: d and dt are both square matrices. alpha,beta > -1
 ---------------------------------------------------------------------*/

template <typename Matrix, typename Scalar, typename Ordinal>
void dgj(Matrix &d, Matrix &dt, Scalar *z, Ordinal np,
         Scalar alpha, Scalar beta){

  Scalar one = 1.0, two = 2.0;

  if (np <= 0){
    d[0][0] = dt[0][0] = 0.0;
  } else {
    Ordinal i,j;
    Scalar *pd;

    pd = new Scalar[np];
    jacobd(np,z,pd,np,alpha,beta);

    for (i = 0; i < np; i++){
      for (j = 0; j < np; j++){

        if (i != j)
          d[i][j] = pd[i]/(pd[j]*(z[i]-z[j]));
        else
          d[i][j] = (alpha - beta + (alpha + beta + two)*z[i])/
            (two*(one - z[i]*z[i]));

        dt[j][i] = d[i][j];
      }
    }
    delete [] pd;
  }
  return;
}


/*---------------------------------------------------------------------
  dgrj() - Compute the Derivative Matrix

  Compute the derivative matrix d and its transpose dt associated with
  the n_th order Lagrangian interpolants through the np Gauss-Radau
  points z.

               du
               --  = D   * u  evaluated at z = z
               dz     ij    j                   i

  NOTE: d and dt are both square matrices. alpha,beta > -1
 ---------------------------------------------------------------------*/

template <typename Matrix, typename Scalar, typename Ordinal>
void dgrj(Matrix &d, Matrix &dt, Scalar *z, Ordinal np,
          Scalar alpha, Scalar beta){

  if (np <= 0){
    d[0][0] = dt[0][0] = 0.0;
  } else {
    Ordinal i, j;
    Scalar   one = 1.0, two = 2.0;
    Scalar   *pd;

    pd  = new Scalar[np];

    pd[0] = pow(-one,int(np-1))*gammaF(np+beta+one);
    pd[0] /= gammaF(np)*gammaF(beta+two);
    jacobd(np-1,z+1,pd+1,np-1,alpha,beta+1);
    for(i = 1; i < np; ++i) pd[i] *= (1+z[i]);

    for (i = 0; i < np; i++)
      for (j = 0; j < np; j++){
        if (i != j)
          d[i][j] = pd[i]/(pd[j]*(z[i]-z[j]));
        else {
          if(i == 0)
            d[i][j] = -(np + alpha + beta + one)*(np - one)/(two*(beta + two));
          else
            d[i][j] = (alpha - beta + one + (alpha + beta + one)*z[i])/
              (two*(one - z[i]*z[i]));
        }

        dt[j][i] = d[i][j];
      }
    delete [] pd;
  }

  return;
}

/*---------------------------------------------------------------------
  dglj() - Compute the Derivative Matrix

  Compute the derivative matrix d and its transpose dt associated with
  the n_th order Lagrangian interpolants through the np Gauss-Lobatto
  points z.

               du
               --  = D   * u  evaluated at z = z
               dz     ij    j                   i

  NOTE: d and dt are both square matrices. alpha,beta > -1
 ---------------------------------------------------------------------*/

template <typename Matrix, typename Scalar, typename Ordinal>
void dglj(Matrix &d, Matrix &dt, Scalar *z, Ordinal np,
          Scalar alpha, Scalar beta) {
  if (np <= 1){
    d[0][0] = dt[0][0] = 0.0;
  } else {
    if (np<2) throw DGM::exception("Polylib::dglj np < 2");
    Ordinal i, j;
    const Scalar one = 1, two = 2;
    Scalar   *pd;
    pd  = new Scalar[np];
    pd[0]  = two*pow(-one,int(np))*gammaF(np + beta);
    pd[0] /= gammaF(np - one)*gammaF(beta + two);
    jacobd(np-2,z+1,pd+1,np-2,alpha+1,beta+1);
    for(i = 1; i < np-1; ++i) pd[i] *= (one-z[i]*z[i]);
    pd[np-1]  = -two*gammaF(np + alpha);
    pd[np-1] /= gammaF(np - one)*gammaF(alpha + two);
    for (i = 0; i < np; i++)
      for (j = 0; j < np; j++){
        if (i != j)
          d[i][j] = pd[i]/(pd[j]*(z[i]-z[j]));
        else {
          if (i == 0)
            d[i][j] = (alpha - (np - 1)*(np + alpha + beta))/(two*(beta+ two));
          else if (i == np-1)
            d[i][j] =-(beta - (np - 1)*(np + alpha + beta))/(two*(alpha+ two));
          else
            d[i][j] = (alpha - beta + (alpha + beta)*z[i])/
              (two*(one - z[i]*z[i]));
        }
        dt[j][i] = d[i][j];
      }
    delete [] pd;
  }
  return;
}

/*---------------------------------------------------------------------
  dntri() - Compute the Derivative Matrices

  Compute the derivative matrices dr and ds (and their transposes drt
  and dst) associated with the nodal triangular quadrature points and
  the orthonormal basis described in HW08

 ---------------------------------------------------------------------*/
template <typename Matrix, typename Scalar, typename Ordinal>
void dntri(Matrix &Vr, Matrix &Vs,
           Scalar *zr, Scalar *zs, Ordinal L) {

  Ordinal nModes = L*(L+1)/2;
  // Need coordinates in (a,b)
  Scalar aa[nModes], bb[nModes];
  Scalar Pi[nModes], Pj[nModes], dPi[nModes], dPj[nModes];

  // MNL: Same as (1) in Basis::make_nodaltri()... new routine?
  for(Ordinal i=0, m=0; i < L; i++)
    for(Ordinal j=0; i+j < L; j++, m++) {
      bb[m] = zs[m];
      if (zs[m] == Scalar(1))
        aa[m] = -Scalar(1);
      else
        aa[m] = 2*(1+zr[m])/(1-zs[m])-Scalar(1);
    }

  // Want to find d/dr and d/ds of Psi_m(a_n,b_n)
  // Psi = sqrt(2)*Pi(a)*Pj(b)*(1-b)^i
  // dPsi/da = sqrt(2)*dPi(a)*Pj(b)*(1-b)^i
  // dPsi/db = sqrt(2)*Pi(a)*( dPj(b)*(1-b)^i - i*Pj(b)*(1-b)^(i-1) )
  // Vr = dPsi/dr = dPsi/da * da/dr
  //         = ( 2/(1-b) ) * dPsi/da
  // Vs = DPsi/ds = dPsi/da * da/ds + dPsi/db * db/ds
  //         = ( (1+a)/(1-b) )*dPsi/da + dPsi/db
  for(Ordinal i=0, m=0; i<L; i++) {
    for(Ordinal j=0; i+j<L; j++, m++) {
      // Pi and Pj
      jacobf(nModes, aa, Pi, i, 0.0, 0.0);
      jacobf(nModes, bb, Pj, j, Scalar(2*i+1), 0.0);
      // dPi and dPj
      jacobd(nModes, aa, dPi, i, 0.0, 0.0);
      jacobd(nModes, bb, dPj, j, Scalar(2*i+1), 0.0);

      for(Ordinal n=0; n<nModes; n++) {
        if (bb[n] == Scalar(1.0)) {
          if (i!=1) Vr[n][m] = 0.0;
          if (i>1) Vs[n][m] = 0.0;
          if (i==1) {
            Vr[n][m] = sqrt(Scalar(3*(j+2))/Scalar(2))*dPi[n]*Pj[n];
            Vs[n][m] = sqrt(Scalar(3*(j+2))/Scalar(4))*Pj[n]*
              (sqrt((1+aa[n]))*dPi[n]-Pi[n]/sqrt(Scalar(2)));
          }
          if (i==0) Vs[n][m] = sqrt(Scalar(j+1)/Scalar(2)) *
                      Pi[n]*dPj[n];
        } else {
          if (i==0) {
            Vr[n][m] = sqrt(Scalar(j+1)/Scalar(2))*
              (2/(1-bb[n]))*dPi[n]*Pj[n];
            Vs[n][m] = sqrt(Scalar(j+1)/Scalar(2))*
              ( ((aa[n]+1)/(1-bb[n]))*dPi[n]*Pj[n]*pow(1-bb[n],int(i)) +
                Pi[n]*dPj[n] );
          } else {
            Vr[n][m] = sqrt(Scalar((2*i+1)*(i+j+1))/pow(Scalar(2),int(2*i+1))) *
              (2/(1-bb[n]))*dPi[n]*Pj[n]*pow(1-bb[n],int(i));
            Vs[n][m] = sqrt(Scalar((2*i+1)*(i+j+1))/pow(Scalar(2),int(2*i+1))) *
              ( ((aa[n]+1)/(1-bb[n]))*dPi[n]*Pj[n]*pow(1-bb[n],int(i)) +
                Pi[n]*dPj[n]*pow(1-bb[n],int(i)) -
                i*Pi[n]*Pj[n]*pow(1-bb[n],int(i-1)) );
          }
        }
      }
    }
  }
}

//-----------------------------------------------------------------------------

namespace {

  static const double EPSILON=0.0000001;
  /** Purpose: Transfer from (r,s,t) -> (a,b,c) coordinates in tet
      ie: from right tet to equalaterial tet. */
  template <typename Scalar>
  void rsttoabc(Scalar &a,
                Scalar &b,
                Scalar &c,
                const Scalar r,
                const Scalar s,
                const Scalar t) {
    a = EPSILON < abs(s+t) ? -2 * ((1+r)/(s+t)) - 1 : -1;
    b = EPSILON < abs(1-t) ?  2 * ((1+s)/(1-t)) - 1 : -1;
    c = t;
  }

  template <typename Scalar>
  void rsttodabc(Scalar &ar,
                 Scalar &as,
                 Scalar &at,
                 Scalar &bs,
                 Scalar &bt,
                 Scalar &ct,
                 const Scalar r,
                 const Scalar s,
                 const Scalar t) {
    ar = EPSILON < abs(s+t) ? -2/(s+t)                  :-1;
    as = EPSILON < abs(s+t) ?  2 * (1+r)/((s+t)*(s+t))  :-1;
    at = EPSILON < abs(s+t) ?  2 * (1+r)/((s+t)*(s+t))  :-1;

    bs = EPSILON < abs(1-t) ?  2/(1-t)                  :-1;
    bt = EPSILON < abs(1-t) ? -2 * (1+s)/((1-t)*(1-t))  :-1;

    ct = 1;
  }

  template <typename Ordinal>
  Ordinal gamma(const Ordinal n) {
    Ordinal g=1;
    for (Ordinal i=1; i<n; ++i) g *= i;
    return g;
  }
  template <typename Ordinal>
  Ordinal gamma_over_gamma(const Ordinal n, const Ordinal d) {
    Ordinal g=1;
    for (Ordinal i=d; i<n; ++i) g *= i;
    return g;
  }

  /** This is from the Orthogonality section of the Wikipedia
      Jacobi polynomial page which is compilcated.   */
  template <typename Scalar, typename Ordinal>
  Scalar normP(const Ordinal n,
               const Ordinal alpha,
               const Ordinal beta) {
    const Scalar two=2.0;
    const Scalar one=1.0;
    const Scalar a = pow (two,int(alpha+beta+1)) ;
    const Scalar b = two*n + alpha + beta + 1 ;
    //const Ordinal d1= gamma(n+alpha+beta+1);
    //const Ordinal c1= gamma(n+alpha     +1);
    //const Ordinal r1 = d1/c1;
    const Ordinal r1 = gamma_over_gamma(n+alpha+beta+1, n+alpha+1);
    //const Ordinal c2 = gamma(n+beta+1);
    //const Ordinal d2 = gamma(n     +1);
    //const Ordinal r2 = c2/d2;
    const Ordinal r2 = gamma_over_gamma(n+beta+1, n+1);
    return sqrt ( (a/b) * (one/r1) * r2 );
  }

  /** This is from the Orthogonality section of the Wikipedia
      Jacobi polynomial page which is compilcated but assumes
      beta=0 and it simplifies a bunch. */

  template <typename Scalar, typename Ordinal>
  Scalar normP(const Ordinal n, const Ordinal alpha) {
    const Scalar two=2.0;
    return sqrt ( pow(two,int(alpha+1)) / (two*n+alpha+1) );
  }

}  // anonymous namespace

//-----------------------------------------------------------------------------

/*---------------------------------------------------------------------
  dntet() - Compute the Derivative Matrices

  Compute the derivative matrices dr and ds (and their transposes drt
  and dst) associated with the nodal triangular quadrature points and
  the orthonormal basis described in HW08

 ---------------------------------------------------------------------*/
template <typename Matrix, typename Scalar, typename Ordinal>
void dntet(Matrix &Vr,
           Matrix &Vs,
           Matrix &Vt,
           const Scalar *r,
           const Scalar *s,
           const Scalar *t,
           Ordinal L) {

  Ordinal np = L*(L+1)*(L+2)/6;

  // Need coordinates in (a,b,c)
  Scalar a[np], b[np], c[np];
  for(Ordinal i=0; i<np; ++i) rsttoabc(a[i], b[i], c[i], r[i], s[i], t[i]);

  Scalar  Pi[np],  Pj[np],  Pk[np];
  Scalar dPi[np], dPj[np], dPk[np];
  for(Ordinal     i=0, m=0;    i < L; i++) {
    for(Ordinal   j=0;       i+j < L; j++) {
      for(Ordinal k=0;     i+j+k < L; k++, m++) {

        // Pi, Pj, Pk
        jacobf(np, a,  Pi, i,          0.,    0.);
        jacobf(np, b,  Pj, j,      2*i+1.,    0.);
        jacobf(np, c,  Pk, k,  2*(i+j+1.),    0.);
        // dPi, dPj, dPk
        jacobd(np, a, dPi, i,          0.,   0.);
        jacobd(np, b, dPj, j,      2*i+1.,   0.);
        jacobd(np, c, dPk, k,  2*(i+j+1.),   0.);

        const Scalar normPi  = normP<Scalar,Ordinal>(i,         0);
        const Scalar normPj  = normP<Scalar,Ordinal>(j,     2*i+1);
        const Scalar normPk  = normP<Scalar,Ordinal>(k, 2*(i+j+1));

        for(Ordinal n=0; n<np; n++) {
          Pi [n] /= normPi;
          Pj [n] /= normPj;
          Pk [n] /= normPk;
          dPi[n] /= normPi;
          dPj[n] /= normPj;
          dPk[n] /= normPk;
        }
        const Scalar fac = pow(2., 2*i + j + 1.5);
        for(Ordinal n=0; n<np; n++) {
          Vr[n][m] =  dPi[n]*Pj[n]*Pk[n];
          if (i  )  Vr[n][m] *= pow((1-b[n])/2., int(i  -1));
          if (i+j)  Vr[n][m] *= pow((1-c[n])/2., int(i+j-1));

          Vs[n][m] = Vr[n][m] * (1.+a[n])/2.;
          Scalar tmp = dPj[n] * pow((1.-b[n])/2., int(i));
          if (i  ) tmp -=  (i/2.) * Pj[n] * pow((1.-b[n])/2., int(i  -1));
          if (i+j) tmp *=                   pow((1.-c[n])/2., int(i+j-1));
          tmp *= (Pi[n] * Pk[n]);
          Vs[n][m] += tmp;

          Vt[n][m] = Vr[n][m] * (1.+a[n])/2.  + tmp * (1.+b[n])/2.;
          tmp = dPk[n] * pow((1.-c[n])/2., int(i+j));
          if (i+j) tmp -= ((i+j)/2.) * Pk[n] * pow((1.-c[n])/2., int(i+j-1));
          tmp *= (Pi[n] * Pj[n]);
          tmp *= pow((1.-b[n])/2., int(i));
          Vt[n][m] += tmp;

          // normalize
          Vr[n][m] *= fac;
          Vs[n][m] *= fac;
          Vt[n][m] *= fac;

        }
      }
    }
  }
}



/*-------------------------------------------------------------
  Compute the value of the Lagrangian interpolant hglj through
  the np Gauss-Jacobi points zgj at the point z.
  -------------------------------------------------------------*/

template <typename Scalar, typename Ordinal>
Scalar hgj (Ordinal i, Scalar z, Scalar *zgj, Ordinal np,
            Scalar alpha, Scalar beta) {
  Scalar zi, dz, p, pd, h;
  zi  = *(zgj+i);
  dz  = z - zi;
  if (fabs(dz) < EPS) return 1.0;
  jacobd(Ordinal(1), &zi, &pd, np, alpha, beta);
  jacobf(Ordinal(1), &z , &p , np, alpha, beta);
  h = p/(pd*dz);
  return h;
}

/*------------------------------------------------------------
  Compute the value of the Lagrangian interpolant hglj through
  the np Gauss-Radau-Jacobi points zgrj at the point z.
  ------------------------------------------------------------*/

template <typename Scalar, typename Ordinal>
Scalar hgrj (Ordinal i, Scalar z, Scalar *zgrj, Ordinal np,
             Scalar alpha, Scalar beta)
{

  Scalar zi, dz, p, pd, h;

  zi  = *(zgrj+i);
  dz  = z - zi;
  if (fabs(dz) < EPS) return 1.0;

  jacobf(Ordinal(1), &zi, &p , np-1, alpha, beta + 1);
  jacobd(Ordinal(1), &zi, &pd, np-1, alpha, beta + 1);
  h = (1.0 + zi)*pd + p;
  jacobf(Ordinal(1), &z, &p, np-1, alpha, beta + 1);
  h = (1.0 + z )*p/(h*dz);

  return h;
}

/*------------------------------------------------------------
  Compute the value of the Lagrangian interpolant hglj through
  the np Gauss-Lobatto-Jacobi points zjlj at the point z.
  ------------------------------------------------------------*/

template <typename Scalar, typename Ordinal>
Scalar hglj (Ordinal i, Scalar z, const Scalar *zglj, Ordinal np,
             Scalar alpha, Scalar beta)
{
  Scalar one = 1., two = 2.;
  Scalar zi, dz, p, pd, h;

  zi  = *(zglj+i);
  dz  = z - zi;
  if (fabs(dz) < EPS) return 1.0;

  jacobf(Ordinal(1), &zi, &p , np-2, alpha + one, beta + one);
  jacobd(Ordinal(1), &zi, &pd, np-2, alpha + one, beta + one);
  h = (one - zi*zi)*pd - two*zi*p;
  jacobf(Ordinal(1), &z, &p, np-2, alpha + one, beta + one);
  h = (one - z*z)*p/(h*dz);

  return h;
}


/*--------------------------------------------------------------------
  igjm() - Interpolation Operator GJ -> M

  Compute the one-dimensional interpolation operator (matrix) I12 for
  interpolating a function from a Gauss-Jacobi mesh (1) to another
  mesh M (2).
  ---------------------------------------------------------------------*/

template <typename Matrix, typename Scalar, typename Ordinal>
void igjm(Matrix &im12, Scalar *zgj, const Scalar *zm, Ordinal nz, Ordinal mz,
          Scalar alpha, Scalar beta){
  Scalar zp;
  Ordinal i, j;
  for (i = 0; i < mz; ++i) {
    zp = zm[i];
    for (j = 0; j < nz; ++j)
      im12 [i][j] = hgj(j, zp, zgj, nz, alpha, beta);
  }

  return;
}

/*--------------------------------------------------------------------
  igrjm() - Interpolation Operator GRJ -> M

  Compute the one-dimensional interpolation operator (matrix) I12 for
  interpolating a function from a Gauss-Radau-Jacobi mesh (1) to
  another mesh M (2).
  ---------------------------------------------------------------------*/

template <typename Matrix, typename Scalar, typename Ordinal>
void igrjm(Matrix &im12, Scalar *zgrj, const Scalar *zm,
           Ordinal nz, Ordinal mz, Scalar alpha, Scalar beta){
  Scalar zp;
  Ordinal i, j;
  for (i = 0; i < mz; i++) {
    zp = zm[i];
    for (j = 0; j < nz; j++)
      im12 [i][j] = hgrj(j, zp, zgrj, nz, alpha, beta);
  }

  return;
}

/*--------------------------------------------------------------------
  igljm() - Interpolation Operator GRJ -> M

  Compute the one-dimensional interpolation operator (matrix) I12 and
  its transpose IT12 for interpolating a function from a Gauss-Lobatto
  Jacobi mesh (1) to another mesh M (2).
 ----------------------------------------------------------------------*/

template <typename Matrix, typename Scalar, typename Ordinal>
void igljm(Matrix &im12, const Scalar *zglj, const Scalar *zm,
           Ordinal nz, Ordinal mz, Scalar alpha, Scalar beta)
{
  Scalar zp;
  Ordinal i, j;
  for (i = 0; i < mz; i++) {
    zp = zm[i];
    for (j = 0; j < nz; j++)
      im12 [i][j] = hglj(j, zp, zglj, nz, alpha, beta);
  }

  return;
}

/* -----------------------------------------------------------------
   jacobi() - jacobi polynomials

   Get a vector 'poly' of values of the n_th order Jacobi polynomial
   P^(alpha,beta)_n(z) alpha > -1, beta > -1 at the np points in z
   ----------------------------------------------------------------- */
template <typename Scalar, typename Ordinal>
void jacobf(const Ordinal np,
            const Scalar *z,
            Scalar *poly,
            const Ordinal n,
            const Scalar alpha,
            const Scalar beta){
  if (!np) return;
  Ordinal i;
  const Scalar one = 1, two = 2;
  if(n == 0)
    for(i = 0; i < np; ++i)
      poly[i] = one;
  else if (n == 1)
    for(i = 0; i < np; ++i)
      poly[i] = 0.5*(alpha - beta + (alpha + beta + two)*z[i]);
  else {
    Ordinal k;
    Scalar a1,a2,a3,a4;
    const Scalar apb = alpha + beta;
    Scalar *polyn1,*polyn2;
    polyn1 = new Scalar[np];
    polyn2 = new Scalar[np];
    for(i = 0; i < np; ++i){
      polyn2[i] = one;
      polyn1[i] = 0.5*(alpha - beta + (alpha + beta + two)*z[i]);
    }
    for(k = 2; k <= n; ++k){
      a1 =  two*k*(k + apb)*(two*k + apb - two);
      a2 = (two*k + apb - one)*(alpha*alpha - beta*beta);
      a3 = (two*k + apb - two)*(two*k + apb - one)*(two*k + apb);
      a4 =  two*(k + alpha - one)*(k + beta - one)*(two*k + apb);

      a2 /= a1;
      a3 /= a1;
      a4 /= a1;

      for(i = 0; i < np; ++i){
        poly  [i] = (a2 + a3*z[i])*polyn1[i] - a4*polyn2[i];
        polyn2[i] = polyn1[i];
        polyn1[i] = poly  [i];
      }
    }
    delete [] polyn2;
    delete [] polyn1;
  }
  return;
}

/* ----------------------------------------------------------------
  jacobd() - derivative of jacobi polynomials - vector version

  Get a vector 'poly' of values of the derivative of the n_th order
  Jacobi polynomial P^(alpha,beta)_N(z) at the np points z.

  To do this we have used the relation

  d   alpha,beta   1                  alpha+1,beta+1
  -- P (z)       = -(alpha+beta+n+1) P  (z)
  dz  n            2                  n-1
  ----------------------------------------------------------------*/

template <typename Scalar, typename Ordinal>
void jacobd(Ordinal np, const Scalar *z, Scalar *polyd, Ordinal n,
            Scalar alpha, Scalar beta)
{
  Ordinal i;
  const Scalar one = 1;
  if(n == 0)
    for(i = 0; i < np; ++i) polyd[i] = 0.0;
  else{
    jacobf(np,z,polyd,n-1,alpha+one,beta+one);
    for(i = 0; i < np; ++i) polyd[i] *= 0.5*(alpha + beta + (Scalar)n + one);
  }
  return;
}

/* ----------------------------------------------------------------
  jacobd2() - 2nd  derivative of jacobi polynomials - vector version

  Get a vector 'poly' of values of the 2nd derivative of the n_th order
  Jacobi polynomial P^(alpha,beta)_N(z) at the np points z.

  To do this we have used the relation

  d^2   alpha,beta
  --   P (z)       =
  dz^2  n
  ----------------------------------------------------------------*/

template <typename Scalar, typename Ordinal>
void jacobd2(Ordinal np, const Scalar *z, Scalar *polyd, Ordinal n,
             Scalar alpha, Scalar beta)
{
  Ordinal i;
  Scalar one = 1.0, two = 2.0;
  if(n <= 1)
    for(i = 0; i < np; ++i) polyd[i] = 0.0;
  else{
    jacobf(np,z,polyd,n-2,alpha+two,beta+two);
    for(i = 0; i < np; ++i) polyd[i] *= 0.5*(alpha + beta + (Scalar)n + one)*
                              0.5*(alpha + beta + (Scalar)n + two);
  }
  return;
}

/*------------------------------------------------------------
  fntri() -- Nodal Triangle basis functions

  Compute the value of the nModes (L*(L+1)/2) NodalTri basis
  functions through the np points (r,s)
  ------------------------------------------------------------*/
template <typename Matrix, typename Scalar, typename Ordinal>
void fntri (Ordinal L, Ordinal np, Scalar *r, Scalar *s, Matrix &V)
{
  Scalar aa[np], bb[np]; // map (r,s) -> (aa,bb)
  Scalar Pi[np], Pj[np]; // jacobi polynomials
  for(Ordinal m=0; m < np; m++) {
    // 1: coordinate mapping for orthonormal basis
    //    a_m = 2*(1+r_m)/(1-s_m) - 1, b_m = s_m
    //    (Note: if s_m = 1 then a_m = -1)
    bb[m] = s[m];
    if (s[m] == Scalar(1))
      aa[m] = -Scalar(1);
    else
      aa[m] = 2*(1+r[m])/(1-s[m])-Scalar(1);
  }
  for(Ordinal i=0, m=0; i < L; i++) {
    for(Ordinal j=0; i+j < L; j++, m++) {
      // 2: V(n,m) = psi_m(r_n) = sqrt(2)*P_i(a_n)*P_j^(2i+1,0)(b_n)*(1-b_n)^i
      jacobf(np,&(aa[0]),&(Pi[0]),i,(Scalar)0.0,(Scalar)0.0);            // P_i(a_n)
      jacobf(np,&(bb[0]),&(Pj[0]),j,Scalar(2*i+1),(Scalar)0.0);  // P_j^(2i+1,0)(b_n)
      for(Ordinal n=0; n<np; n++) {
        // Note: HW08 normalize jacobi polynomials, jacobf does not
        //  Pi[n] *= sqrt(Scalar(2*i+1)/2);
        //  Pj[n] *= sqrt(Scalar(i+j+1)/pow(2,2*i+1));
        V[n][m] = sqrt(Scalar((2*i+1)*(i+j+1))/pow(Scalar(2),int(2*i+1))) *
                  Pi[n]*Pj[n]*pow(1-bb[n],int(i));
      }
    }
  }
}

/*------------------------------------------------------------
  fntet() -- Nodal Tet basis functions :
    see Hesthaven & Warburton, Nodal Discontinusous Galerkin Methods

  Compute the value of the nModes (L(L+1)(L+2)/6) NodalTet basis
  functions through the np points (r,s,t)
  ------------------------------------------------------------*/
template <typename Matrix, typename Scalar, typename Ordinal>
void fntet (const Ordinal L,
            const Ordinal np,
            const Scalar *r,
            const Scalar *s,
            const Scalar *t,
            Matrix &V)
{
  const Scalar two_sqrt_2 = 2*sqrt(Scalar(2));
  Scalar a[np], b[np], c[np]; // map (r,s) -> (a,b)
  for(Ordinal i=0; i<np; i++) rsttoabc(a[i], b[i], c[i], r[i], s[i], t[i]);

  Scalar Pi[np], Pj[np], Pk[np];         // jacobi polynomials

  for(Ordinal m=0,i=0;     i < L; i++) {
    for(Ordinal   j=0;   i+j < L; j++) {
      for(Ordinal k=0; i+j+k < L; k++, m++) {
        // 2: V(n,m) =
        // 2sqrt(2)* P_i(a) P_j^(2i+1,0)(b) P_k^(2i+2j+2,0) (1-b)^i(1-c)^(i+j)

        jacobf(np, a, Pi, i,         0., 0.);  // P_i(a)
        jacobf(np, b, Pj, j,     2*i+1., 0.);  // P_j^(2i+1,0)(b)
        jacobf(np, c, Pk, k, 2*(i+j+1.), 0.);  // P_k^(2i+2j+2,0)(c)

        const Scalar normPi = normP<Scalar,Ordinal>(i,         0);
        const Scalar normPj = normP<Scalar,Ordinal>(j,     2*i+1);
        const Scalar normPk = normP<Scalar,Ordinal>(k, 2*(i+j+1));

        // Note: HW08 normalize jacobi polynomials, jacobf does not
        const Scalar scale = two_sqrt_2 / (normPi * normPj * normPk);
        for(Ordinal n=0; n<np; n++) {
          V[n][m] = scale * Pi[n] * Pj[n] * Pk[n] *
                            pow(1-b[n],int(i)) * pow(1-c[n],int(i+j));
        }
      }
    }
  }
}

} // namespace DGM
