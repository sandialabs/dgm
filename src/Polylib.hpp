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

/**
 *  \file  Polylib.hpp
 *  \brief Library routines for polynomial calculus and interpolation
*/

#ifndef DGM_POLYLIB_HPP
#define DGM_POLYLIB_HPP

namespace DGM {

#ifndef M_PI
/// High precision value for \f$\pi\f$
#define M_PI 3.14159265358979323846
#endif

/*-----------------------------------------------------------------------
                         M A I N     R O U T I N E S
  -----------------------------------------------------------------------*/

//! \name Points and weights
//@{
/// Points and weights for Gauss-Jacobi quadrature
template <typename Scalar, typename Ordinal>
void zwgj(Scalar *, Scalar *, Ordinal , Scalar , Scalar);

/// Points and weights for Gauss-Radau-Jacobi quadrature
template <typename Scalar, typename Ordinal>
void zwgrj(Scalar *, Scalar *, Ordinal , Scalar , Scalar);

/// Points and weights for Gauss-Lobatto-Jacobi quadrature
template <typename Scalar, typename Ordinal>
void zwglj(Scalar *, Scalar *, Ordinal , Scalar , Scalar);

/// Points and weights for Gauss-Jacobi quadrature
template <typename Vector, typename Scalar>
void zwgj(Vector &z, Vector &w, Scalar alpha, Scalar beta) {
  assert(z.size()==w.size());
  zwgj(z.ptr(),w.ptr(),z.size(),alpha,beta);
}

/// Points and weights for Gauss-Radau-Jacobi quadrature
template <typename Vector, typename Scalar>
void zwgrj(Vector &z, Vector &w, Scalar alpha, Scalar beta) {
  assert(z.size()==w.size());
  zwgrj(z.ptr(),w.ptr(),z.size(),alpha,beta);
}

/// Points and weights for Gauss-Lobatto-Jacobi quadrature
template <typename Vector, typename Scalar>
void zwglj(Vector &z, Vector &w, Scalar alpha, Scalar beta) {
  assert(z.size()==w.size());
  zwglj(z.ptr(),w.ptr(),z.size(),alpha,beta);
}

/// Points for Nodal triangle quadrature
template <typename Scalar, typename Ordinal>
void zwntri(Scalar *, Scalar *, const Ordinal);

/// Points for Nodal triangle quadrature
template <typename Vector, typename Ordinal>
void zwntri(Vector &r, Vector &s, const Ordinal N) {
  assert((Ordinal)r.size()==(N+2)*(N+1)/2);
  assert(r.size()==s.size());
  zwntri(r.ptr(),s.ptr(),N);
}

/// Points for Nodal tetrahedron quadrature
template <typename Scalar, typename Ordinal>
void zwntet(Scalar *, Scalar *, Scalar *, const Ordinal);

/// Points for Nodal tetrahedron quadrature
template <typename Vector, typename Ordinal>
void zwntet(Vector &r, Vector &s, Vector &t, const Ordinal N) {
  assert(r.size()== typename Vector::size_type((N+3)*(N+2)*(N+1)/6));
  assert(r.size()==s.size());
  assert(r.size()==t.size());
  zwntet(r.ptr(),s.ptr(),t.ptr(),N);
}
//@}

//! \name Derivative operators
//@{
/// Derivative operator for Gauss-Jacobi
template <typename Matrix, typename Vector, typename Scalar>
void dgj(Matrix &d, Matrix &dt, Vector &z, Scalar alpha, Scalar beta);

/// Derivative operator for Gauss-Radau-Jacobi
template <typename Matrix, typename Scalar, typename Ordinal>
void dgrj(Matrix &, Matrix &,  Scalar *, Ordinal, Scalar, Scalar);

/// Derivative operator for Gauss-Lobatto-Jacobi
template <typename Matrix, typename Scalar, typename Ordinal>
void dglj(Matrix &, Matrix &, Scalar *, Ordinal, Scalar, Scalar);

/// Derivative operator for Nodal triangle
template <typename Matrix, typename Scalar, typename Ordinal>
void dntri(Matrix &, Matrix &, Scalar *, Scalar *, Ordinal);

/// Derivative operator for Nodal tet
template <typename Matrix, typename Scalar, typename Ordinal>
void dntri(Matrix &, Matrix &, Matrix &, 
           Scalar *, Scalar *, Scalar *, Ordinal);

/// Derivative operator for Gauss-Radau-Jacobi
template <typename Matrix, typename Vector, typename Scalar>
void dgrj(Matrix &d, Matrix &dt, Vector &z, Scalar alpha, Scalar beta){
  dgrj(d,dt,z.ptr(),z.size(),alpha,beta);
}
/// Derivative operator for Gauss-Lobatto-Jacobi
template <typename Matrix, typename Vector, typename Scalar>
void dglj(Matrix &d, Matrix &dt, Vector &z, Scalar alpha, Scalar beta){
  dglj(d,dt,z.ptr(),z.size(),alpha,beta);
}
//@}

//! \name Lagrangian interpolants
//@{
/// Lagrangian interpolate for Gauss-Jacobi
template <typename Scalar, typename Ordinal>
Scalar hgj(Ordinal, Scalar, Scalar *, Ordinal, Scalar, Scalar);

/// Lagrangian interpolate for Gauss-Radau-Jacobi
template <typename Scalar, typename Ordinal>
Scalar hgrj(Ordinal, Scalar, Scalar *, Ordinal, Scalar, Scalar);

/// Lagrangian interpolate for Gauss-Lobatto-Jacobi
template <typename Scalar, typename Ordinal>
Scalar hglj(Ordinal, Scalar, const Scalar *, Ordinal, Scalar, Scalar);
//@}

//! \name Interpolation operators
//@{
/// Interpolation operator for Gauss-Jacobi
template <typename Matrix, typename Scalar, typename Ordinal>
void igjm(Matrix&, Scalar*, const Scalar*, Ordinal, Ordinal, Scalar, Scalar);

/// Interpolation operator for Gauss-Radau-Jacobi
template <typename Matrix, typename Scalar, typename Ordinal>
void igrjm(Matrix&, Scalar*, const Scalar*, Ordinal, Ordinal, Scalar, Scalar);

/// Interpolation operator for Gauss-Lobatto-Jacobi
template <typename Matrix, typename Scalar, typename Ordinal>
void igljm(Matrix&, const Scalar*, const Scalar*, Ordinal, Ordinal, Scalar, Scalar);

/// Interpolation operator for Gauss-Jacobi
template <typename Matrix, typename Vector, typename Scalar>
void igjm(Matrix &im12, Vector &z1, Vector &z2, Scalar alpha, Scalar beta) {
  igjm(im12,z1.ptr(),z2.ptr(),z1.size(),z2.size(),alpha,beta);
}
/// Interpolation operator for Gauss-Radau-Jacobi
template <typename Matrix, typename Vector, typename Scalar>
void igrjm(Matrix &im12, Vector &z1, Vector &z2, Scalar alpha, Scalar beta) {
  igrjm(im12,z1.ptr(),z2.ptr(),z1.size(),z2.size(),alpha,beta);
}
/// Interpolation operator for Gauss-Lobatto-Jacobi
template <typename Matrix, typename Vector, typename Scalar>
void igljm(Matrix &im12, Vector &z1, Vector &z2, Scalar alpha, Scalar beta) {
  igljm(im12,z1.ptr(),z2.ptr(),z1.size(),z2.size(),alpha,beta);
}
//@}

//! \name Polynomial functions
//@{
/// Jacobi polynomials
template <typename Scalar, typename Ordinal>
void jacobf(const Ordinal, const Scalar *, Scalar *,
            const Ordinal, const Scalar, const Scalar);
/// Jacobi polynomials
template <typename Vector, typename Scalar>
void jacobf(const Vector &z, Scalar *poly, typename Vector::size_type n,
            Scalar alpha, Scalar beta) {
  jacobf(z.size(),z.ptr(),poly,n,alpha,beta);
}
/// Jacobi polynomials
template <typename Vector, typename Scalar>
void jacobf(const Vector &z, Vector &poly, typename Vector::size_type n,
            Scalar alpha, Scalar beta) {
  assert(z.size()==poly.size());
  jacobf(z.size(),z.ptr(),poly.ptr(),n,alpha,beta);
}

/// Derivative of Jacobi polynomials
template <typename Scalar, typename Ordinal>
void jacobd(Ordinal, const Scalar *, Scalar *, Ordinal, Scalar, Scalar);
/// Derivative of Jacobi polynomials
template <typename Vector, typename Scalar>
void jacobd(const Vector &z, Scalar *polyd, typename Vector::size_type n,
            Scalar alpha, Scalar beta) {
  jacobd(z.size(),z.ptr(),polyd,n,alpha,beta);
}
/// Derivative of Jacobi polynomials
template <typename Vector, typename Scalar>
void jacobd(const Vector &z, Vector &polyd, typename Vector::size_type n,
            Scalar alpha, Scalar beta) {
  jacobd(z.size(),z.ptr(),polyd.ptr(),n,alpha,beta);
}

/// Second derivative of Jacobi polynomials
template <typename Scalar, typename Ordinal>
void jacobd2(Ordinal, const Scalar *, Scalar *, Ordinal, Scalar, Scalar);

/// Second derivative of Jacobi polynomials
template <typename Vector, typename Scalar>
void jacobd2(const Vector &z, Scalar *polyd, typename Vector::size_type n,
             Scalar alpha, Scalar beta) {
  jacobd2(z.size(),z.ptr(),polyd,n,alpha,beta);
}

/// Second derivative of Jacobi polynomials
template <typename Vector, typename Scalar>
void jacobd2(const Vector &z, Vector &polyd, typename Vector::size_type n,
             Scalar alpha, Scalar beta) {
  jacobd2(z.size(),z.ptr(),polyd.ptr(),n,alpha,beta);
}

/// Polynomial basis for NodalTri
template <typename Matrix, typename Scalar, typename Ordinal>
void fntri(Ordinal, Ordinal, Scalar *, Scalar *, Matrix &);

/// Polynomial basis for NodalTet
template <typename Matrix, typename Scalar, typename Ordinal>
void fntet(const Ordinal, const Ordinal,
           const Scalar *, const Scalar *, const Scalar *,
           Matrix &);

// Need polynomial basis for NodalTet

//@}

//! \name Points and weights
//@{
/// Compute Gauss-Legendre points and weights
template <typename Scalar, typename Ordinal>
void zwgl(Scalar *z, Scalar *w, Ordinal np) {
  zwgj(z,w,np,(Scalar)0.0,(Scalar)0.0);
}
/// Compute Gauss-Radau-Legendre points and weights
template <typename Scalar, typename Ordinal>
void zwgrl(Scalar *z, Scalar *w, Ordinal np) {
  zwgrj(z,w,np,(Scalar)0.0,(Scalar)0.0);
}
/// Compute Gauss-Lobatto-Legendre points and weights
template <typename Scalar, typename Ordinal>
void zwgll(Scalar *z, Scalar *w, Ordinal np) {
  zwglj(z,w,np,(Scalar)0.0,(Scalar)0.0);
}

/// Compute Gauss-Legendre points and weights
template <typename Vector>
void zwgl(Vector &z, Vector &w) {
  assert(z.size()==w.size());
  zwgj(z.ptr(),w.ptr(),z.size(),(Scalar)0.0,(Scalar)0.0);
}
/// Compute Gauss-Radau-Legendre points and weights
template <typename Vector>
void zwgrl(Vector &z, Vector &w) {
  assert(z.size()==w.size());
  const typename Vector::value_type zero(0);
  zwgrj(z.ptr(),w.ptr(),z.size(),zero,zero);
}
/// Compute Gauss-Lobatto-Legendre points and weights
template <typename Vector>
void zwgll(Vector &z, Vector &w) {
  assert(z.size()==w.size());
  const typename Vector::value_type zero(0);
  zwglj(z.ptr(),w.ptr(),z.size(),zero,zero);
}

/// Compute Gauss-Chebychev points and weights
template <typename Scalar, typename Ordinal>
void zwgc(Scalar *z, Scalar *w, Ordinal np) {
  zwgj( z,w,np,(Scalar)-0.5,(Scalar)-0.5);
}
/// Compute Gauss-Radau-Chebychev points and weights
template <typename Scalar, typename Ordinal>
void zwgrc(Scalar *z, Scalar *w, Ordinal np) {
  zwgrj(z,w,np,(Scalar)-0.5,(Scalar)-0.5);
}
/// Compute Gauss-Lobatto-Chebychev points and weights
template <typename Scalar, typename Ordinal>
void zwglc(Scalar *z, Scalar *w, Ordinal np) {
  zwglj(z,w,np,(Scalar)-0.5,(Scalar)-0.5);
}
//@}

//! \name Derivative operators
//@{
/// Compute Gauss-Legendre derivative matrix
template <typename Matrix, typename Scalar, typename Ordinal>
void dgl(Matrix &d, Matrix &dt, Scalar *z, Ordinal np) {
  dgj( d,dt,z,np,(Scalar)0.0,(Scalar)0.0);
}
/// Compute Gauss-Radau-Legendre derivative matrix
template <typename Matrix, typename Scalar, typename Ordinal>
void dgrl(Matrix &d, Matrix &dt, Scalar *z, Ordinal np) {
  dgrj(d,dt,z,np,(Scalar)0.0,(Scalar)0.0);
}
/// Compute Gauss-Lobatto-Legendre derivative matrix
template <typename Matrix, typename Scalar, typename Ordinal>
void dgll(Matrix &d, Matrix &dt, Scalar *z, Ordinal np) {
  dglj(d,dt,z,np,(Scalar)0.0,(Scalar)0.0);
}

/// Compute Gauss-Lobatto-Legendre derivative matrix
template <typename Matrix, typename Vector>
void dgll(Matrix &d, Matrix &dt, Vector &z) {
  dglj(d,dt,z.ptr(),z.size(),(Scalar)0.0,(Scalar)0.0);
}

/// Compute Gauss-Chebychev derivative matrix
template <typename Matrix, typename Scalar, typename Ordinal>
void dgc(Matrix &d, Matrix &dt, Scalar *z, Ordinal np) {
  dgj( d,dt,z,np,(Scalar)-0.5,(Scalar)-0.5);
}
/// Compute Gauss-Radau-Chebychev derivative matrix
template <typename Matrix, typename Scalar, typename Ordinal>
void dgrc(Matrix &d, Matrix &dt, Scalar *z, Ordinal np) {
  dgrj(d,dt,z,np,(Scalar)-0.5,(Scalar)-0.5);
}
/// Compute Gauss-Lobatto-Chebychev derivative matrix
template <typename Matrix, typename Scalar, typename Ordinal>
void dglc(Matrix &d, Matrix &dt, Scalar *z, Ordinal np) {
  dglj(d,dt,z,np,(Scalar)-0.5,(Scalar)-0.5);
}
//@}

//! \name Lagrangian interpolants
//@{
/// Compute Gauss-Legendre Lagrange interpolants
template <typename Scalar, typename Ordinal>
void hgl(Ordinal i, Scalar z, Scalar *zgj, Ordinal np) {
  hgj(i,z,zgj,np,(Scalar)0.0,(Scalar)0.0);
}
/// Compute Gauss-Radau-Legendre Lagrange interpolants
template <typename Scalar, typename Ordinal>
void hgrl(Ordinal i, Scalar z, Scalar *zgrj, Ordinal np) {
  hgrj(i,z,zgrj,np,(Scalar)0.0,(Scalar)0.0);
}
/// Compute Gauss-Lobatto-Legendre Lagrange interpolants
template <typename Scalar, typename Ordinal>
void hgll(Ordinal i, Scalar z, Scalar *zglj, Ordinal np) {
  hglj(i,z,zglj,np,(Scalar)0.0,(Scalar)0.0);
}

/// Compute Gauss-Chebychev Lagrange interpolants
template <typename Scalar, typename Ordinal>
void hgc(Ordinal i, Scalar z, Scalar *zgj, Ordinal np) {
  hgj( i,z,zgj ,np,-0.5,-0.5);
}
/// Compute Gauss-Radau-Chebychev Lagrange interpolants
template <typename Scalar, typename Ordinal>
void hgrc(Ordinal i, Scalar z, Scalar *zgrj, Ordinal np) {
  hgrj(i,z,zgrj,np,-0.5,-0.5);
}
/// Compute Gauss-Lobatto-Chebychev Lagrange interpolants
template <typename Scalar, typename Ordinal>
void hglc(Ordinal i, Scalar z, Scalar *zglj, Ordinal np) {
  hglj(i,z,zglj,np,-0.5,-0.5);
}
//@}

//! \name Interpolation operators
//@{
/// Interpolate from Gauss-Legendre to a mesh
template <typename Matrix, typename Scalar, typename Ordinal>
void iglm(Matrix &im12, Scalar *zgl, Scalar *zm, Ordinal nz, Ordinal mz) {
  igjm(im12,zgl,zm,nz,mz,(Scalar)0.0,(Scalar)0.0);
}
/// Interpolate from Gauss-Radau-Legendre to a mesh
template <typename Matrix, typename Scalar, typename Ordinal>
void igrlm(Matrix &im12, Scalar *zgrl, Scalar *zm, Ordinal nz, Ordinal mz) {
  igrjm(im12,zgrl,zm,nz,mz,(Scalar)0.0,(Scalar)0.0);
}
/// Interpolate from Gauss-Lobatto-Legendre to a mesh
template <typename Matrix, typename Scalar, typename Ordinal>
void igllm(Matrix &im12, Scalar *zgll, Scalar *zm, Ordinal nz, Ordinal mz) {
  igljm(im12,zgll,zm,nz,mz,(Scalar)0.0,(Scalar)0.0);
}

/// Interpolate from Gauss-Legendre to a mesh
template <typename Matrix, typename Vector>
void iglm(Matrix &im12, Vector &zgl, Vector &zm) {
  igjm(im12,zgl.ptr(),zm.ptr(),zgl.size(),zm.size(),(Scalar)0.0,(Scalar)0.0);
}
/// Interpolate from Gauss-Radau-Legendre to a mesh
template <typename Matrix, typename Vector>
void igrlm(Matrix &im12, Vector &zgrl, Vector &zm) {
  const typename Vector::value_type zero(0);
  igrjm(im12,zgrl.ptr(),zm.ptr(),zgrl.size(),zm.size(),zero,zero);
}
/// Interpolate from Gauss-Lobatto-Legendre to a mesh
template <typename Matrix, typename Vector>
void igllm(Matrix &im12, Vector &zgll, Vector &zm) {
  const typename Vector::value_type zero(0);
  igljm(im12,zgll.ptr(),zm.ptr(),zgll.size(),zm.size(),zero,zero);
}

/// Interpolate from Gauss-Legendre to a mesh
template <typename Matrix, typename Vector, typename Scalar>
void iglm(Matrix &im12, Vector &zgl, Scalar zm) {
  igjm(im12,zgl.ptr(),&zm,zgl.size(),
       typename Vector::size_type(1),(Scalar)0.0,(Scalar)0.0);
}
/// Interpolate from Gauss-Radau-Legendre to a mesh
template <typename Matrix, typename Vector, typename Scalar>
void igrlm(Matrix &im12, Vector &zgrl, Scalar zm) {
  igrjm(im12,zgrl.ptr(),&zm,zgrl.size(),
        typename Vector::size_type(1),(Scalar)0.0,(Scalar)0.0);
}
/// Interpolate from Gauss-Lobatto-Legendre to a mesh
template <typename Matrix, typename Vector, typename Scalar>
void igllm(Matrix &im12, Vector &zgll, Scalar zm) {
  igljm(im12,zgll.ptr(),&zm,zgll.size(),
        typename Vector::size_type(1),(Scalar)0.0,(Scalar)0.0);
}

/// Interpolate from Gauss-Chebychev to a mesh
template <typename Matrix, typename Scalar, typename Ordinal>
void igcm(Matrix &im12, Scalar *zgl, Scalar *zm, Ordinal nz, Ordinal mz) {
  igjm(im12,zgl,zm,nz,mz,-0.5,-0.5);
}
/// Interpolate from Gauss-Radau-Chebychev to a mesh
template <typename Matrix, typename Scalar, typename Ordinal>
void igrcm(Matrix &im12, Scalar *zgrl, Scalar *zm, Ordinal nz, Ordinal mz) {
  igrjm(im12,zgrl,zm,nz,mz,-0.5,-0.5);
}
/// Interpolate from Gauss-Lobatto-Chebychev to a mesh
template <typename Matrix, typename Scalar, typename Ordinal>
void iglcm(Matrix &im12, Scalar *zgll, Scalar *zm, Ordinal nz, Ordinal mz) {
  igljm(im12,zgll,zm,nz,mz,-0.5,-0.5);
}
//@}

} // namespace DGM

#endif  // DGM_POLYLIB_HPP
