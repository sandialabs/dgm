/** \file ElementBlock.cpp
    \brief DGM Element block class implementation
    \author James Overfelt
    \author Scott Collis
*/

// system includes
#include <cstdio>
#include <fstream>
#include <string>
#include <vector>
#include <limits>

// DGM includes
#include "Comm.hpp"
#include "ElementBlock.hpp"
#include "Types.hpp"
#include "Parser.hpp"

namespace DGM {

void ElementBlock::inner_product() {DGM_UNDEFINED;}

void ElementBlock::inner_product(dVector &, dVector &) const {DGM_UNDEFINED;}

void ElementBlock::solve_mass_matrix(dVector &) const {DGM_UNDEFINED;}

void ElementBlock::get_side(const dVector &from, const int sid,
                            dVector &to) const {
  const eblock::const_iterator end = eb.end();
  const Element * const elem = first_element();
  const Ordinal qtot = elem ? 0 : elem->qtot;
  const Ordinal qa   = elem ? 0 : elem->qa;
  Scalar *v_from = from.data();
  Scalar *v_to   = to  .data();
  unsigned j=0;
  for (eblock::const_iterator i=eb.begin(); i!=end; ++i, ++j) {
    const dVector v(&v_from[j*qtot], qtot);
    dVector       x(&v_to  [j*qa  ], qa);
    (*i)->get_side(v,sid,x);
  }
}

void ElementBlock::copy_sides( ElementBlock *E ) const {
  const eblock::const_iterator end = eb.end();
  const eblock::const_iterator eend = E->eb.end();
  eblock::const_iterator i=eb.begin();
  eblock::const_iterator e=E->eb.begin();
  for (; i!=end && e!=eend; ++i,++e) {
    (*i)->copy_sides(*e);
  }
}

void ElementBlock::gradient(const dVector &f, dVector &fx, dVector &fy) const {
  static FunctionTimer T("ElementBlock::gradient(dVector&,dVector&,dVector&)");
  FunctionSentry sentry(T);
  const eblock::const_iterator end = eb.end();
  const Ordinal qtot  = this->qtot;
  Scalar *f_data  = f .data();
  Scalar *fx_data = fx.data();
  Scalar *fy_data = fy.data();
  unsigned j=0;
  for (eblock::const_iterator i=eb.begin(); i!=end; ++i, ++j) {
    const dVector f_t (&f_data [j*qtot], qtot);
    dVector       fx_t(&fx_data[j*qtot], qtot);
    dVector       fy_t(&fy_data[j*qtot], qtot);
    (*i)->gradient(f_t, fx_t, fy_t);
  }
}

void ElementBlock::gradient(const dVector &f,  dVector &fx,
                            dVector &fy, dVector &fz) const {
  static FunctionTimer T("ElementBlock::gradient(dVector&,dVector&,"
      "dVector&,dVector&)");
  FunctionSentry sentry(T);
  const eblock::const_iterator end = eb.end();
  const Ordinal qtot  = this->qtot;
  Scalar *f_data  = f .data();
  Scalar *fx_data = fx.data();
  Scalar *fy_data = fy.data();
  Scalar *fz_data = fz.data();
  unsigned j=0;
  for (eblock::const_iterator i=eb.begin(); i!=end; ++i, ++j) {
    const dVector f_t (&f_data [j*qtot], qtot);
    dVector       fx_t(&fx_data[j*qtot], qtot);
    dVector       fy_t(&fy_data[j*qtot], qtot);
    dVector       fz_t(&fz_data[j*qtot], qtot);
    (*i)->gradient(f_t, fx_t, fy_t, fz_t);
  }
}

void ElementBlock::gradient(const dVector &f, dVector &df, char dir) const {
  static FunctionTimer T("ElementBlock::gradient(dVector&,dVector&,char)");
  FunctionSentry sentry(T);
  const eblock::const_iterator end = eb.end();
  const Ordinal qtot  = this->qtot;
  Scalar *f_data  = f .data();
  Scalar *df_data = df.data();
  unsigned j=0;
  for (eblock::const_iterator i=eb.begin(); i!=end; ++i, ++j) {
    const dVector f_t (&f_data [j*qtot], qtot);
    dVector       df_t(&df_data[j*qtot], qtot);
    (*i)->gradient(f_t, df_t, dir);
  }
}

void ElementBlock::lift(ElementBlock *F, dVector &in, const char dir) const {
  static FunctionTimer T("ElementBlock::lift");
  FunctionSentry sentry(T);
  const eblock::const_iterator end = eb.end();
  const Ordinal qtot  = this->qtot;
  Scalar *in_data  = in.data();
  unsigned j=0;
  for (eblock::const_iterator i=eb.begin();
       i!=end && j!=F->eb.size(); ++i, ++j){
    dVector in_t(&in_data[j*qtot], qtot);
    Element *E = F->eb[j];
    (*i)->lift(E, in_t, dir);
  }
}

/// Transform using another Elements mass matrix (dangerous)
void ElementBlock::forward_transform(ElementBlock *F, ElementBlock *) {
  static FunctionTimer T("ElementBlock::forward_transform(ElementBlock*,"
      "ElementBlock*)");
  FunctionSentry sentry(T);
  if (eb.front()-> state == eb.front()->Transform) {
    cerr << "ElementBlock::forward_transform -- already in transform space"
         <<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  const eblock::const_iterator end = eb.end();
  unsigned j=0;
  for (eblock::const_iterator i=eb.begin();
       i!=end && j!=F->eb.size(); ++i, ++j){
    Element *I = *i;
    I->inner_product(I->u,I->uh);
    F->eb[j]->solve_mass_matrix(I->uh);  // Use element F's Mass matrix
    I->state = I->Transform;
  }
}

/// Return Element to physical space
void ElementBlock::backward_transform() {
  static FunctionTimer T("ElementBlock::backward_transform");
  FunctionSentry sentry(T);
  if (eb.front()->state == eb.front()->Physical) {
    cerr << "ElementBlock::transform_to_physical -- already in physical space"
         <<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  const eblock::const_iterator end = eb.end();
  for (eblock::const_iterator i=eb.begin(); i!=end; ++i){
    Element *I = *i;
    I->backward_transform( I->uh, I->u );
    I->state = I->Physical;
  }
}

namespace {

  Ordinal number_of_side_links(const Element *e) {
    Ordinal num_links = 0;
    for (Ordinal i=0; i != e->nSides(); i++) {  // loop over sides
      const Side *s=e->side[i];
      if (s->link) {                      // only compute if link is defined
        num_links += s->qtot();           // number of quad. pts on side
      }
    }
    return num_links;
  }

}  // anonymous namespace

ElementBlock::ElementBlock(Element *e, const Ordinal blocksize) :
    eb(1,e),
    BlockSize(blocksize),
    u(e->u),
    nVerts(e->nVerts()),
    nEdges(e->nEdges()),
    nFaces(e->nFaces()),
    nModes(e->nModes()),
    pOrder(e->pOrder()),
    L     (e->L()),
    qtot  (e->qtot),
    s_qtot(number_of_side_links(e)),
    const_mass(false),
    psi   (e->psi),
    qa    (e->qa),
    qb    (e->qb),
    qc    (e->qc),
    D     (e->D),
    curve (e->curve),
    geom  (e->geom),
    geom_check(*e->geom),
    dinfo_check(*e->D),
    interpolation_matrices(e->get_interpolation_matrices())
    {}

Element * ElementBlock::first_element() const {
  Element * elem = eb.empty() ? 0 : *eb.begin();
  return elem;
}

// This removes warning 192 on the Intel compiler
#ifdef DGM_USE_ELEMENT_BLOCKS
#define LOCAL_DGM_ELEMENT_BLOCK DGM_USE_ELEMENT_BLOCKS
#else
#define LOCAL_DGM_ELEMENT_BLOCK 0
#endif

/** \note The casts to int are required to remove warnings on comparisons
    between signed and unsigned.   */
bool ElementBlock::compatible(const Element *e) const {
  const bool i =
    (e )                    &&  // check before dereference
    (e->nVerts() == nVerts) &&  // Number of verticies
    (e->nEdges() == nEdges) &&  // Number of edges (2- and 3-d)
    (e->nFaces() == nFaces) &&  // Number of faces (3-d)
    (e->nModes() == nModes) &&  // Number of total modes
    (e->pOrder() == pOrder) &&  // Polynomial order
    (e->L()      == L     ) &&  // Number of modes in each direction
    (e->qtot   == qtot  )   &&  // Total number of quadrature points
    (e->psi    == psi   )   &&  // basis datastructure
    (e->qa     == qa    )   &&  // Number of quadrature points
    (e->qb     == qb    )   &&  // Number of quadrature points
    (e->qc     == qc    )   &&  // Number of quadrature points
    (e->D      == D     )       &&   // collocation derivative matrix
    (e->curve  == curve )       &&   // curved side structure
    (e->geom   == geom  )       &&   // Jacobian matrix
    (*e->geom  == geom_check  ) &&   //
    (*e->D     == dinfo_check  )&&   //
    (e->get_interpolation_matrices() == interpolation_matrices  );
#if LOCAL_DGM_ELEMENT_BLOCK >= 3
  if (!i) {
     if (!(e)) {
        std::cout <<"Element not compatible with element block because ";
        std::cout << " element is a Null pointer "<< std::endl;
     }
     else {
        std::cout <<"Element "<< e->id <<
          " not compatible with element block because ";
        if (e->nVerts() != nVerts)
          std::cout << ", (e->nVerts != nVerts):"<<e->nVerts<<" vs. "<<nVerts;
        if (e->nEdges() != nEdges)
          std::cout << ", (e->nEdges != nEdges):"<<e->nEdges<<" vs. "<<nEdges;
        if (e->nFaces() != nFaces)
          std::cout << ", (e->nFaces != nFaces):"<<e->nFaces<<" vs. "<<nFaces;
        if (e->nModes() != nModes)
          std::cout << ", (e->nModes != nModes):"<<e->nModes<<" vs. "<<nModes;
        if (e->pOrder() != pOrder)
          std::cout << ", (e->pOrder != pOrder):"<<e->pOrder<<" vs. "<<pOrder;
        if (e->L()    != L     )
          std::cout << ", (e->L      != L     ):" <<e->L     <<" vs. "<<L    ;
        if (e->qtot   != qtot  )
          std::cout << ", (e->qtot   != qtot  ):"<<e->qtot  <<" vs. "<<qtot  ;
        if (e->psi    != psi   )
          std::cout << ", (e->psi    != psi   ):"<<e->psi   <<" vs. "<<psi   ;
        if (e->qa     != qa    )
          std::cout << ", (e->qa     != qa    ):"<<e->qa    <<" vs. "<<qa    ;
        if (e->qb     != qb    )
          std::cout << ", (e->qb     != qb    ):"<<e->qb    <<" vs. "<<qb    ;
        if (e->qc     != qc    )
          std::cout << ", (e->qc     != qc    ):"<<e->qc    <<" vs. "<<qc    ;
        if (e->D      != D     )
          std::cout << ", (e->D      != D     ):"<<e->D     <<" vs. "<<D     ;
        if (e->curve  != curve )
          std::cout << ", (e->curve  != curve ):"<<e->curve <<" vs. "<<curve ;
        if (e->geom   != geom  )
          std::cout << ", (e->geom   != geom  ):"<<e->geom  <<" vs. "<<geom  ;
        if (*e->geom  != geom_check ) std::cout << ", geom_check failed.";
        if (*e->D     != dinfo_check ) std::cout << ", dinfo_check failed.";
        if (e->get_interpolation_matrices() == interpolation_matrices  )
          std::cout <<", interpolation_matrices check failed.";
        std::cout<<endl;
     }
  }
#endif
  return i;
}

bool ElementBlock::checkCompatibility() const {
  const eblock::const_iterator end = eb.end();
  for (eblock::const_iterator i=eb.begin(); end != i; ++i) {
    if (!compatible(*i)) return false;
  }
  return true;
}

bool ElementBlock::push_back(Element *e) {
  const bool compat = compatible(e);
  const Ordinal side_links = number_of_side_links(e);
  const bool push_back =
      compat && (eb.size() < numeric_cast<size_t>(BlockSize));
  if (push_back) {
    eb.push_back(e);
    s_qtot += side_links;
    u.alias(u.data(), numeric_cast<Ordinal>(eb.size())*qtot);
  }
  return push_back;
}

} // namespace DGM
