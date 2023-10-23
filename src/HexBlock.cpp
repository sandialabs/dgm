/** \file HexBlock.cpp
    \brief HexBlock implementation
    \author James Overfelt
    \author Scott Collis
    \author Noel Belcourt
    \author Pedro Bello-Maldonado
*/

// system includes
#include <cstdio>
#include <fstream>
#include <string>
#include <vector>

// DGM includes
#include "Comm.hpp"
#include "Hex.hpp"
#include "HexBlock.hpp"
#include "Types.hpp"
#include "Parser.hpp"
#include "Utils.hpp"
#include "Utilities.hpp"

// Kokkos
#if defined(DGM_USE_KOKKOS)
#include <Kokkos_Core.hpp>
#endif

namespace DGM {

HexBlock::HexBlock(Element *e, const Ordinal blocksize) :
  ElementBlock(e, blocksize) {
}

#if defined(DGM_USE_CUDA) || defined(DGM_USE_KOKKOS)
void HexBlock::initialize_gpu() {
  // number of elements, p order, quad pts and modes in each direction
  gpu_hex.initialize(eb.size(), L, qa, qb, qc);

  // copy in basis functions, only need one since identical for affine
  dMatrix& Ba = eb.front()->psi->Ba;
  dMatrix& Bb = eb.front()->psi->Bb;
  dMatrix& Bc = eb.front()->psi->Bc;

  gpu_hex.Basis(Ba.data(), Bb.data(), Bc.data());

  // copy weighted Jacobian into cuda memory
  dVector& wJ = eb.front()->geom->wJ;
  gpu_hex.wJ(wJ.begin());
}
#endif // DGM_USE_CUDA or DGM_USE_KOKKOS

/// Transform using another Elements mass matrix (dangerous)
void HexBlock::forward_transform(ElementBlock *F, ElementBlock *) {
  const size_t size = eb.size();

  if (eb.front()-> state == eb.front()->Transform) {
    cerr << "HexBlock::forward_transform -- already in transform space"<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }

  if (1 == size) {
    (eb.front())->forward_transform(F->eb.front(), F->eb.front());
  }
  else if (size) {
#if defined(DGM_USE_CUDA) || defined(DGM_USE_KOKKOS)
    // copy in u
    Element *I = *eb.begin();
    dVector& u = I->u;

    // invoke inner_product kernel on gpu
    gpu_hex.inner_product(u.begin());

    // set transform on each element in block
    eblock::const_iterator i = eb.begin(), end = eb.end();
    for (; i != end; ++i) {
      Element *I = *i;
      I->state = I->Transform;
    }
#else
    eblock::const_iterator i = eb.begin(), end = eb.end();
    for (; i != end; ++i) {
      Element *I = *i;
      I->inner_product(I->u, I->uh);
      I->state = I->Transform;
    }
#endif // DGM_USE_CUDA or DGM_USE_KOKKOS

    dMatrix Uh(F->eb.front()->uh, numeric_cast<Ordinal>(size), nModes);
    F->eb.front()->solve_mass_matrix(Uh);  // Use element F's Mass matrix
  }
}

// Transforms supplied data to physical space on this Element
void HexBlock::backward_transform()
{
  static FunctionTimer T("HexBlock::backward_transform");
  FunctionSentry sentry(T);
  
  if (eb.front()->state == eb.front()->Physical)
  {
    cerr << "ElementBlock::transform_to_physical -- already in physical space" << endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }

#if defined(DGM_USE_CUDA) || defined(DGM_USE_KOKKOS)
  const eblock::const_iterator end = eb.end();

  // Get first element
  Element* I = *eb.begin(); 
  dVector& u = I->u;

  // Call function on the GPU
  gpu_hex.backward_transform(u.begin());

  for (eblock::const_iterator i = eb.begin(); i != end; ++i)
  {
    Element* I = *i;
    I->state = I->Physical;
  }
#else
  const eblock::const_iterator end = eb.end();

  for (eblock::const_iterator i = eb.begin(); i != end; ++i)
  {
    Element* I = *i;
    I->backward_transform(I->uh, I->u);
    I->state = I->Physical;
  }
#endif // DGM_USE_CUDA or DGM_USE_KOKKOS
}

/// computes the gradient of a block of Hex Elements
void HexBlock::gradient(const dVector &f,  dVector &fx,
                              dVector &fy, dVector &fz) const {
  static FunctionTimer T("HexBlock::gradient"); FunctionSentry sentry(T);

  const Ordinal size = numeric_cast<Ordinal>(eb.size());
  if (!checkCompatibility()) {
    cout <<__FILE__<<":"<<__LINE__<<":Compatibiltiy Check failed"<<endl;
    error ("Compatibiltiy Check failed in HexBlock::gradient.",1);
  }
  if (1==size) {
    (eb.front())->gradient(f, fx, fy, fz);
  } else if (size) {
    const dMatrix &Da    = this->D->Da ;
    const dMatrix &Db    = this->D->Db ;
    const dMatrix &Dct   = this->D->Dct;
    const Geometry::Ptr &geom  = this->geom;
    const Ordinal qa    = this->qa  ;
    const Ordinal qb    = this->qb  ;
    const Ordinal qc    = this->qc  ;
    const Ordinal qtot  = this->qtot;
    const Ordinal nqtot = size*qtot;

    dVector fr(nqtot);        // use gradient workspace
    dVector fs(nqtot);        // use gradient workspace
    dVector ft(nqtot);        // use gradient workspace

    for (Ordinal i=0; size != i; ++i) {
      const Ordinal offset = i*qtot;
      dVector o; o.alias(f,offset,qtot);
      const dMatrix F (o, qa, qb*qc);  // matrix alias of vector
      dMatrix Fr(&fr[offset], qa, qb*qc);  // matrix alias of vector
      matmult(Da, F, Fr );
    }
    const Ordinal nqa = size*qa  ;
    for (Ordinal i=0; i<nqa; i++) {
      const Ordinal offset = i*qb*qc;
      dVector o; o.alias(f, offset, qb*qc);
      dVector p; p.alias(fs,offset, qb*qc);
      const dMatrix F (o, qb,qc);  // matrix alias of vector
      dMatrix Fs(p, qb,qc);        // matrix alias of vector
      matmult(Db, F, Fs );
    }
    {
     dMatrix F(f, qa*qb*size, qc);
     dMatrix Ft(ft, qa*qb*size, qc);
     matmult(F, Dct, Ft);
    }

    dVector::size_type stride(size);
    dvmul ( geom->rx, fr, fx,     stride );
    dvvtvp( geom->sx, fs, fx, fx, stride );
    dvvtvp( geom->tx, ft, fx, fx, stride );
    dvmul ( geom->ry, fr, fy,     stride );
    dvvtvp( geom->sy, fs, fy, fy, stride );
    dvvtvp( geom->ty, ft, fy, fy, stride );
    dvmul ( geom->rz, fr, fz,     stride );
    dvvtvp( geom->sz, fs, fz, fz, stride );
    dvvtvp( geom->tz, ft, fz, fz, stride );
  }
}

/// Return a flux vector
dVector HexBlock::flux_vector( const ElementBlock *Fb,
                               const char dir,
                               const Ordinal qtot_sides,
                               const Ordinal side) const {
  static FunctionTimer T("HexBlock::flux_vector"); FunctionSentry sentry(T);

  const ElementBlock  *Ub = this;
  const Ordinal size  = numeric_cast<Ordinal>(eb.size());
  const dMatrix *im1 = interpolation_matrices[2*side];
  const dMatrix *im2 = interpolation_matrices[2*side+1];
  const Ordinal q1  = (Ordinal)im1->rows();
  const Ordinal q2  = (Ordinal)im2->rows();
  const Ordinal q1g = (Ordinal)im1->cols();
  const Ordinal q2g = (Ordinal)im2->cols();
  const Ordinal qtot = q1g*q2g;
  const Element *ef = Fb ? Fb->eb.front(): NULL;
  const Element *eu =      Ub->eb.front();
  const Side *Fside = ef ? ef->side[side]: NULL;
  const Side *Uside =      eu->side[side];

  const dMatrix Um(Uside->u, size, qtot_sides);
  dMatrix from(size, qtot);
  dMatrix wk(size, q1*q2g);

  if (Fside) {
    const dMatrix Fm(Fside->u, size, qtot_sides);
    subtract(Fm, Um, from);
  }
  else {
    for (Ordinal i=0; i<size; ++i)
      for (Ordinal j=0; j<qtot; ++j)
        from[i][j] = Um[i][j];
  }
  for (Ordinal i=0; i<size; ++i) {
    dVector row(from.row(i));
    dvmul( Uside->J(), row);
    if      (dir == 'x')
      dvmul (Uside->nx(), row);
    else if (dir == 'y')
      dvmul (Uside->ny(), row);
    else if (dir == 'z')
      dvmul (Uside->nz(), row);
  }

  for (Ordinal i=0; i<size; i++) {
#ifdef CMC_USE_MATRIX_ROW_SLICE
    dSlice &o = from.row(i);
    const dMatrix From(&o[0], q1g, q2g);        // matrix alias of vector
    dSlice &p = wk.row(i);
    dMatrix Wk(&p[0],  q1, q2g);                // matrix alias of vector
#else
    const dMatrix From (from.row(i), q1g,q2g);  // matrix alias of vector
    dMatrix Wk   (wk.  row(i), q1, q2g);        // matrix alias of vector
#endif
    matmult( *im1, From, Wk );
  }
  dVector to(size*q1*q2);
  dMatrix To(to, size*q1, q2);
  dMatrix Wk(&wk[0][0], size*q1, q2g);
  matmult( Wk, 'T', *im2, To );
  return to;
}

/// add flux contribution for a block of Hex Elements
void HexBlock::lift(ElementBlock *Fb, dVector &in, const char dir) const {
  static FunctionTimer T("HexBlock::lift");
  FunctionSentry sentry(T);
  const Ordinal size = numeric_cast<Ordinal>(eb.size());
  if (1==size) {
    Element *ef = Fb ? Fb->eb.front() : NULL;
    (eb.front())->lift(ef, in, dir);
    return;
  } else if (!size) {
    return;
  }
  const ElementBlock *const Ub = this;
  Ordinal qtot_sides=0;
  for (size_t i=0; i<6; ++i) qtot_sides+=interpolation_matrices[i]->cols();

  const Scalar w[6] = {1/Ub->psi->wc[0]     ,
                       1/Ub->psi->wb[0]     ,
                       1/Ub->psi->wa[qa-1]  ,
                       1/Ub->psi->wb[qb-1]  ,
                       1/Ub->psi->wa[0]     ,
                       1/Ub->psi->wc[qc-1]  };
  { // Side 0
    dVector fv = HexBlock::flux_vector(Fb, dir, qtot_sides, 0);
    fv *= w[0];
    dMatrix In(in, size*qa*qb, qc);
    dvadd( fv, In.column(0) );
  }
  { // Side 1
    dVector fv = HexBlock::flux_vector(Fb, dir, qtot_sides, 1);
    fv *= w[1];
    dMatrix Fv(fv,size*qa,    qc);
    dMatrix In(in,size*qa*qb, qc);
    for (Ordinal i=0; i<size*qa; ++i) {
      dVector Fv_row(Fv.row(i));
      dVector In_row(In.row(i*qb));
      dvadd( Fv_row, In_row );
    }
  }
  { // Side 2
    dVector fv = HexBlock::flux_vector(Fb, dir, qtot_sides, 2);
    fv *= w[2];
    dMatrix In(in, size*qa, qb*qc);
    for (Ordinal i=1; i<=size; ++i) {
      dVector In_row(In.row(i*qa-1));
      dvadd( fv, In_row);
    }
  }
  { // Side 3
    dVector fv = HexBlock::flux_vector(Fb, dir, qtot_sides, 3);
    fv *= w[3];
    dMatrix Fv(fv, size*qa,    qc);
    dMatrix In(in, size*qa*qb, qc);
    for (Ordinal j=0; j<size; ++j) {
      for (Ordinal i=0; i<qa; i++) {
        dVector Fv_row(Fv. row(j*qa    + i));
        dVector In_row(In. row(j*qa*qb + (i+1)*qb - 1));
        dvadd( Fv_row, In_row );
      }
    }
  }
  { // Side 4
    dVector fv = HexBlock::flux_vector(Fb, dir, qtot_sides, 4);
    fv *= w[4];
    dMatrix In(in, size*qa, qb*qc);
    for (Ordinal i=0; i<size; ++i) {
      dVector In_row(In.row(i*qa));
      dvadd( fv, In_row);
    }
  }
  { // Side 5
    dVector fv = HexBlock::flux_vector(Fb, dir, qtot_sides, 5);
    fv *= w[5];
    dMatrix In(in, size*qa*qb, qc);
    dvadd( fv, In.column(qc-1) );
  }
}

} // namespace DGM
