/** \file QuadBlock.cpp
    \brief QuadBlock implementation
    \author James Overfelt
    \author Scott Collis
*/

// system includes
#include <cstdio>
#include <fstream>
#include <string>
#include <vector>

// DGM includes
#include "Comm.hpp"
#include "Quad.hpp"
#include "QuadBlock.hpp"
#include "Types.hpp"
#include "Parser.hpp"
#include "Utils.hpp"
#include "Utilities.hpp"

// This removes warning 192 on the Intel compiler
#ifdef DGM_USE_ELEMENT_BLOCKS
#define DGM_QUAD_BLOCK DGM_USE_ELEMENT_BLOCKS
#else
#define DGM_QUAD_BLOCK 0
#endif

namespace DGM {

/// computes the gradient of a block of Quad Elements
void QuadBlock::gradient(const dVector &f, dVector &fx,
                         dVector &fy) const {
  static FunctionTimer T("QuadBlock::gradient(dVector&,dVector&,dVector&)");
  FunctionSentry sentry(T);
  const Ordinal size = numeric_cast<Ordinal>(eb.size());
#ifdef DGM_QUADBLOCK_DEBUG
  if (!checkCompatibility()) {
    cout <<__FILE__<<":"<<__LINE__<<":Compatibiltiy Check failed"<<endl;
    error ("Compatibiltiy Check failed in QuadBlock::gradient.",1);
  }
#endif
  if (1==size) {
    (*eb.begin())->gradient(f, fx, fy);
#if (DGM_QUAD_BLOCK >= 3)
  } else if (4 < pOrder) {
    const eblock::const_iterator end = eb.end();
    const Ordinal qtot  = this->qtot;
    Scalar *f_data  = f .data();
    Scalar *fx_data = fx.data();
    Scalar *fy_data = fy.data();
    Ordinal j=0;
    for (eblock::const_iterator i=eb.begin(); i!=end; ++i, ++j) {
      const dVector f_t (&f_data [j*qtot], qtot);
      dVector       fx_t(&fx_data[j*qtot], qtot);
      dVector       fy_t(&fy_data[j*qtot], qtot);
      (*i)->gradient(f_t, fx_t, fy_t);
    }
#endif
  } else if (size) {
    const dMatrix &Da   = this->D->Da ;
    const dMatrix &Dbt  = this->D->Dbt;
    const Geometry::Ptr &geom  = this->geom;
    const Ordinal qa    = this->qa  ;
    const Ordinal qb    = this->qb  ;
    const Ordinal qtot  = this->qtot;
    const Ordinal nqtot = size*qtot;

    if (scratcha.size()<nqtot) scratcha.resize(nqtot);
    if (scratchb.size()<nqtot) scratchb.resize(nqtot);

    dVector fr(scratcha,nqtot);
    dVector fs(scratchb,nqtot);

    dMatrix F, Fr, Fs;
    for (Ordinal i=0; i<size; ++i) {
      static FunctionTimer T("QuadBlock::gradient::a");
      FunctionSentry sentry(T);
      const Ordinal offset = i*qtot;
      F.alias(const_cast<dVector&>(f), offset, qa, qb);
      Fr.alias(fr, offset, qa, qb);
      matmult( Da, F, Fr );
    }
    {
      static FunctionTimer T("QuadBlock::gradient::b");
      FunctionSentry sentry(T);
      const Ordinal nqa = size*qa  ;
      F.alias(const_cast<dVector&>(f), nqa, qb);
      Fs.alias(fs,nqa, qb);
      matmult( F, Dbt, Fs );
    }

    {
      static FunctionTimer T("QuadBlock::gradient::trans");
      FunctionSentry sentry(T);
      dVector::size_type stride = size;
#if 0
      dvmul ( geom->rx, fr, fx,     stride );  // fx  = rx * fr
      dvvtvp( geom->sx, fs, fx, fx, stride );  // fx += sx * fs
      dvmul ( geom->ry, fr, fy,     stride );  // fy  = ry * fr
      dvvtvp( geom->sy, fs, fy, fy, stride );  // fy += sy * fs
#else
      const dVector::size_type N = geom->rx.size();
      dVector::size_type k=0;
      for (dVector::size_type j=0; j<stride; ++j) {
        for (dVector::size_type i=0; i<N; ++i, ++k) {
          fx[k] = geom->rx[i] * fr[k] + geom->sx[i] * fs[k];
          fy[k] = geom->ry[i] * fr[k] + geom->sy[i] * fs[k];
        }
      }
#endif
    }
  }
}

/// computes the gradient of a block of Quad Elements
void QuadBlock::gradient(const dVector &f, dVector &df, char dir) const {
  static FunctionTimer T("QuadBlock::gradient(dVector&,dVector&,char dir)");
  FunctionSentry sentry(T);
  const Ordinal size = numeric_cast<Ordinal>(eb.size());
#ifdef DGM_QUADBLOCK_DEBUG
  if (!checkCompatibility()) {
    cout <<__FILE__<<":"<<__LINE__<<":Compatibiltiy Check failed"<<endl;
    error ("Compatibiltiy Check failed in QuadBlock::gradient.",1);
  }
#endif
  if (1==size) {
    (*eb.begin())->gradient(f, df, dir);
#if (DGM_QUAD_BLOCK >= 3)
  } else if (4 < pOrder) {
    const eblock::const_iterator end = eb.end();
    const Ordinal qtot  = this->qtot;
    Scalar *f_data  = f .data();
    Scalar *df_data = df.data();
    Ordinal j=0;
    for (eblock::const_iterator i=eb.begin(); i!=end; ++i, ++j) {
      const dVector f_t (&f_data [j*qtot], qtot);
      dVector       df_t(&df_data[j*qtot], qtot);
      (*i)->gradient(f_t, df_t, dir);
    }
#endif
  } else if (size) {
    const dMatrix &Da   = this->D->Da;
    const dMatrix &Dbt  = this->D->Dbt;
    const Geometry::Ptr &geom  = this->geom;
    const Ordinal qa    = this->qa;
    const Ordinal qb    = this->qb;
    const Ordinal qtot  = this->qtot;
    const Ordinal nqtot = size*qtot;

    if (scratcha.size()<nqtot) scratcha.resize(nqtot);
    if (scratchb.size()<nqtot) scratchb.resize(nqtot);

    dVector fr(scratcha,nqtot);
    dVector fs(scratchb,nqtot);

    dMatrix F, Fr, Fs;
    for (Ordinal i=0; size != i; ++i) {
      const Ordinal offset = i*qtot;
      F.alias(const_cast<dVector&>(f), offset, qa, qb);
      Fr.alias(fr, offset, qa, qb);
      matmult( Da, F, Fr );        // Fr[qa][qb] = Da[qa][qa] F[qa][qb]
    }
    {
      const Ordinal nqa = size*qa;
      F.alias(const_cast<dVector&>(f), nqa, qb);
      Fs.alias(fs,nqa, qb);
      matmult( F, Dbt, Fs );       // Fs[nqa][qb] = F[nqa][qb] Dbt[qb][qb]
    }

    const dVector::size_type stride = size;
    switch (dir) {
    case 'x':
#if 1
      {
        const dVector::size_type N = geom->rx.size();
        dVector::size_type k=0;
        for (dVector::size_type j=0; j<stride; ++j) {
          for (dVector::size_type i=0; i<N; ++i, ++k) {
            df[k] = geom->rx[i] * fr[k] + geom->sx[i] * fs[k];
          }
        }
      }
#else
      dvmul ( geom->rx, fr, df,     stride );  // df  = rx * fr
      dvvtvp( geom->sx, fs, df, df, stride );  // df += sx * fs
#endif
      break;
    case 'y':
#if 1
      {
        const dVector::size_type N = geom->rx.size();
        dVector::size_type k=0;
        for (dVector::size_type j=0; j<stride; ++j) {
          for (dVector::size_type i=0; i<N; ++i, ++k) {
            df[k] = geom->ry[i] * fr[k] + geom->sy[i] * fs[k];
          }
        }
      }
#else
      dvmul ( geom->ry, fr, df,     stride );  // df  = ry * fr
      dvvtvp( geom->sy, fs, df, df, stride );  // df += sy * fs
#endif
      break;
    }
  }
}

/// Return a flux vector
dVector QuadBlock::flux_vector( const ElementBlock *Fb,
                                const char dir,
                                const Ordinal qtot_edges,
                                const Ordinal edge) const {
  static FunctionTimer T("QuadBlock::flux_vector");
  FunctionSentry sentry(T);

  const ElementBlock *Ub = this;
  const Ordinal size = numeric_cast<Ordinal>(eb.size());
  const dMatrix *im = interpolation_matrices[edge];

  const Ordinal qedg = im->cols();
  const Ordinal q    = im->rows();
  const Element *ef = Fb->eb.front();
  const Element *eu = Ub->eb.front();
  const Edge &Fedge = ef->edge[edge];
  const Edge &Uedge = eu->edge[edge];

  const dMatrix Fm(Fedge.u, size, qtot_edges);
  const dMatrix Um(Uedge.u, size, qtot_edges);

  if (scratcha.size()<size*qedg) scratcha.resize(size*qedg);
  dMatrix f(scratcha, size, qedg);

  subtract(Fm, Um,  f);
  scale(Uedge.J(), f);

  if      (dir == 'x') scale(Uedge.nx(), f);
  else if (dir == 'y') scale(Uedge.ny(), f);

  if (scratchb.size()<size*q) scratchb.resize(size*q);
  dMatrix fi(scratchb, q, size);
  matmult( *im, 'T', f, fi );

  if (scratcha.size()<size*q) scratcha.resize(size*q);
  dVector r(scratcha, size*q);

  dMatrix tr(r,size,q);
  for (Ordinal i=0; i<q; ++i)
    for (Ordinal j=0; j<size; ++j)
      tr[j][i] = fi[i][j];

  return r;
}

/// add flux contribution for a block of Quad Elements
void QuadBlock::lift(ElementBlock *Fb, dVector &in, const char dir) const {
  static FunctionTimer T("QuadBlock::lift");
  FunctionSentry sentry(T);
  //  cout << "Quad::lift for Eid = " << id << endl;
  const ElementBlock *const Ub = this;
  const Ordinal size = numeric_cast<Ordinal>(eb.size());
  dMatrix In(in, qa*size, qb);
  Ordinal qtot_edges=0;
  for (size_t i=0; i<4; ++i) qtot_edges+=interpolation_matrices[i]->cols();
  { // Edge 0
    const Ordinal edge=0;
    dVector fv = QuadBlock::flux_vector(Fb, dir, qtot_edges, edge);
    const dVector &wb = Ub->psi->wb;
    fv *= 1/wb[0];
    dvadd( fv, In.column(0) );
  }
  { // Edge 1
    const Ordinal edge=1;
    dVector fv = QuadBlock::flux_vector(Fb, dir, qtot_edges, edge);
    const dVector &wa = Ub->psi->wa;
    fv *= 1/wa[qa-1];
    dMatrix fm(fv,size,qb);
    for (Ordinal i=0; i<size; ++i) {
      dVector fm_row(fm.row(i));
      dVector In_row(In.row(qa*(i+1) - 1));
      dvadd( fm_row, In_row);
    }
  }
  { // Edge 2
    const Ordinal edge=2;
    dVector fv = QuadBlock::flux_vector(Fb, dir, qtot_edges, edge);
    const dVector &wb = Ub->psi->wb;
    fv *= 1/wb[qb-1];
    dvadd( fv, In.column(qb - 1));
  }
  { // Edge 3
    const Ordinal edge=3;
    dVector fv = QuadBlock::flux_vector(Fb, dir, qtot_edges, edge);
    const dVector &wa = Ub->psi->wa;
    fv *= 1/wa[0];
    dMatrix fm(fv,size,qb);
    for (Ordinal i=0; i<size; ++i) {
      dVector fm_row(fm.row(i));
      dVector In_row(In.row(qa*i));
      dvadd( fm_row, In_row);
    }
  }
}

void QuadBlock::inner_product(dVector &f, dVector &fh) const {
  static FunctionTimer T("QuadBlock::inner_product(dVector&,dVector&)");
  FunctionSentry sentry(T);

  const Ordinal size = numeric_cast<Ordinal>(eb.size());

  const dMatrix &phia = psi->Ba;
  const dMatrix &phib = psi->Bb;

  {
    dMatrix F(f,size,qa*qb);
    const dVector &wJ = geom->wJ;
    scale( wJ, F );
  }

  if (scratcha.size() < L*size*qb) scratcha.resize(L*size*qb);

  for (Ordinal i=0; size != i; ++i) {
    dVector o(f,        i*qa*qb, qa*qb);
    dVector p(scratcha, i* L*qb,  L*qb);
    const dMatrix F (o, qa, qb);    // matrix alias of vector
    dMatrix       wk(p,  L, qb);    // matrix alias of vector
    matmult( phia,  F, wk );
  }

  dMatrix Fh(fh,       size*L,  L);
  dMatrix wk(scratcha, size*L, qb);

  matmult( wk, 'T', phib, Fh);    // Fh[La][Lb] = wk[La][qb] * (Bb[Lb][qb])^T
}

void QuadBlock::solve_mass_matrix(dVector &fh) const {
  static FunctionTimer T("QuadBlock::solve_mass_matrix(dVector&)");
  FunctionSentry sentry(T);
#ifdef DGM_TEST_FOR_NORMAL
  if (!fh.isNormal())cout<<"QuadBlock::solve_mass_matrix not normal"<<endl;
#endif
  if (const_mass) {
    const Ordinal size = numeric_cast<Ordinal>(eb.size());
    if (eb.front()->curve.get() || eb.front()->full_mass_matrix()) {
      dMatrix Fh(fh, size, L*L);
#ifdef DGM_CHOLESKY_MASS_MATRIX
      Cholesky_solve(eb.front()->M->mat, Fh);
#else
      LU_solve( eb.front()->M->mat, eb.front()->M->pivots, Fh);
#endif
    } else {
      dMatrix Fh(fh, size, L*L);
      const dVector X = eb.front()->M->mat.row(0);
      scale(X,Fh);
    }
  } else {
    unsigned int j=0;
    for (eblock::const_iterator i=eb.begin();
         i!=eb.end() && j!=eb.size(); ++i, ++j){
      dVector Fh(fh, j*L*L, L*L);
      (*i)->solve_mass_matrix(Fh);  // Use element F's Mass matrix
    }
  }
#ifdef DGM_TEST_FOR_NORMAL
  fh.makeNormal();
  if (!fh.isNormal())cout<<"QuadBlock::solve_mass_matrix not normal"<<endl;
#endif
}

/// Transform using another Elements mass matrix (dangerous)
void QuadBlock::forward_transform(ElementBlock *F, ElementBlock *) {
  static FunctionTimer T("QuadBlock::forward_transform(ElementBlock*,"
      "ElementBlock*)");
  FunctionSentry sentry(T);
  if (eb.front()->state == Element::Transform) {
    cerr << "QuadBlock::forward_transform -- already in transform space"
         <<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }

  const Ordinal size = numeric_cast<Ordinal>(F->eb.size());

  if (scratcha.size()<size*L*L) scratcha.resize(size*L*L);
  dVector  Uh(scratcha,size*L*L);

  inner_product(u, Uh);
  F->solve_mass_matrix(Uh);  // Use element F's Mass matrix

  dMatrix UH(Uh,size,L*L);
  unsigned j=0;
  for (eblock::const_iterator i=eb.begin(); i!=eb.end(); ++i,++j){
    (*i)->uh = UH.row(j);
    (*i)->state = Element::Transform;
  }
}


} // namespace DGM
