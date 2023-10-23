/*============================================================================
  Module:     Matrix Assembler

  Author:     Axel Gerstenberger, Scott Collis

  Copyright:  (c)2010 Sandia National Laboratories
============================================================================*/

#ifndef DGM_ASSEMBLER_HPP
#define DGM_ASSEMBLER_HPP

/** \file Assembler.hpp
    \brief Helper functions for DGM matrix and vector assembly
    \author Axel Gerstenberger
    \author Scott Collis
*/

// Reo includes
#include "Types.hpp"

// DGM includes
#include "Comm.hpp"
#include "Domain.hpp"
#include "Element.hpp"
#include "Side.hpp"
#include "Utilities.hpp"

// system includes
#include <boost/array.hpp>
#include <typeinfo>  // for debugging purposes, use typeid(variable).name()

#ifdef DGM_USE_EPETRA

namespace DGM {

/// Discontinuous Galerkin matrix functionality for implicit solutions
namespace Matrix {

#ifdef DGM_USE_ASSEMBLER_TIMERS
  #define TIME_ME() \
    static FunctionTimer timer(__PRETTY_FUNCTION__); \
    FunctionSentry sentry(timer);
#else
  #define TIME_ME()
#endif

/**
 * Lists possible derivatives (order and integer must not matter).
 * Note that random dummy values are given to the enum to avoid that somebody
 * relies on the implicit integer value.
 */
enum Derivative {
  d0 = 12,   ///< no derivative
  dx = 18,   ///< derivative in x-direction
  dy = 7,    ///< derivative in y-direction
  dz = 5,    ///< derivative in z-direction
  dn = 9     ///< derivative in normal direction (to a side)
};

/**
 * Lists all available physical fields (order and integer must not matter).
 * Note that random dummy values are given to the enum to avoid that somebody
 * relies on the implicit integer value. Use PhysField to define your personal
 * field ordering (see Helmholtz.cpp for an example implementation).
 */
enum PhysField {
  ur = 4,    ///< real part of complex valued pressure
  ui = 8,    ///< imaginary part of complex valued pressure
  pres = 13, ///< pressure used in Darcy computation
  u = 3      ///< general solution field (used for example in Poisson problem)
};

/// Field number helper
/**
 * allows you to define the order of your PhysField in a vector field
 * Helmholtz.hpp contains examples on how it is defined and used.\
 * If you forget to define "pos" for your problem, the Assembler classes
 * will not compile, so you are forced to implement it correctly.
 *
 * \tparam field  field, for which the user wants to define a array position
 */
template<PhysField field>
struct FieldNum {
//  static const std::size_t pos = errorPos; ///< dummy array position
};

/// max number of modes for vector field
static int get_Lmax_for_vField(
    const DGM::vField &Uf ///< take Lmax from this vField
    ) {
  int n(0);
  for (vField::size_type ifield = 0; ifield != Uf.size(); ifield++) {
    n += Uf[ifield]->Lmax;
  }
  return n;
}

/**
 * Give me a vector of adjacent sides for a vector of local sides
 *
 * \tparam nfield  dimension of vector field
 * \return vector with adjacent sides
 */
template<int nfield>
static boost::array<Side*,nfield> select_adj(
    boost::array<Side*,nfield> S           ///< vector of local sides
    ) {
  boost::array<Side*,nfield> out;
  if (S[0]->master()) {
    for (int ifield = 0; ifield < nfield; ifield++)
      out[ifield] = S[ifield]->link;
  } else {
    for (int ifield = 0; ifield < nfield; ifield++)
      out[ifield] = S[ifield]->base;
  }
  return out;
}

/// load trial shape function phi and put phi on the side
static void sol_d0(
    const DGM::Side *const s,   ///< side we want to put the shape function on
    const int jtrial,           ///< current trial mode
    DGM::dVector &ws            ///< vector containing shape function
    ) {
  TIME_ME();
  const DGM::Element *const e = s->elink;
  DGM::dVector phi(e->qtot);  // <- todo: this has to be optimized
  e->fill(e->psi->mode[jtrial], phi);
  e->load_side(phi, s->id(), ws);
}

/// load trial shape function phi and put dphi/dnormal on the side
static void sol_dn(
    const DGM::Side *const s,  ///< side we want to put the derivative
    const int jtrial,          ///< current trial mode
    DGM::dVector &ws           ///< vector containing side derivative
    ) {
  TIME_ME();
  const DGM::Element *const e = s->elink;
  DGM::dVector phi(e->qtot);  // <- todo: this has to be optimized
  e->fill(e->psi->mode[jtrial], phi);
  e->normal_times_gradient_side( phi, s->id(), ws );
}

/// get trial shape function or its derivative normal to the side
/**
 *
 * \param s       current side
 * \param jtrial  current trial mode
 * \param ws      resulting vector with trial shape function
 * \tparam dtrial derivative of trial function
 */
template<Matrix::Derivative dtrial>
static void sol(const DGM::Side* const s, const int jtrial,
                DGM::dVector &ws) {
  TIME_ME();
  switch (dtrial) {
  case Matrix::d0:
    sol_d0(s, jtrial, ws);
    break;
  case Matrix::dn:
    sol_dn(s, jtrial, ws);
    break;
  default: cout << "wrong derivative in assembler!" << endl; exit(1); break;
  }
}

/// helper function to test on test shape function
template<Matrix::Derivative dtest>
static void test(const DGM::Side* const s, const DGM::dVector &ws_loc,
                 DGM::dVector &wh) {
  TIME_ME();
  const DGM::Element *const e = s->elink;
  switch (dtest) {
  case Matrix::d0:
    e->test_on_shape_side(ws_loc, s->id(), wh);
    break;
  case Matrix::dn:
    e->test_on_normal_times_gradient_side(ws_loc, s->id(), wh);
    break;
  default:
    throw DGM::exception("wrong derivative in assembler!");
    break;
  }
}

/// This class allows to integrate and assemble a matrix side weak form term
/**
 *
 * Evaluate an tangent/system matrix side integral of the form
 *
 * \f[ \hat{A}_{IJ} += \int_\Gamma \phi_I(x) v(x) \phi_J(x) \mathrm{d} x \f]
 *
 * or, if v is a constant,
 *
 * \f[ \hat{A}_{IJ} += \int_\Gamma \phi_I(x) v \phi_J(x) \mathrm{d} x \f]
 *
 * There are two methods: in locloc test and trial shape functions are from
 * the same element, while in locadj, the test shape function comes from the
 * local element and the trial shape function from the adjacent element.
 * \tparam nfield number of elements in your vector field
 */
template<int nfield>
class MatrixSideAssembler {

  /// contains the maximum number of modes per element max-ed over all
  /// elements
  int                              maxnModes;

  /// do we also work on the adjacent side?
  bool                             have_adj_matrix;

  /// tangent/system element matrix for local element
  DGM::dMatrix                     MATlocloc;

  /// tangent/system element matrix between local and adjacent element
  DGM::dMatrix                     MATlocadj;

  /// vector of local sides, corresponds to your vector field
  boost::array<DGM::Side*,nfield>  Us_loc;

  /// vector of adjacent sides, corresponds to your vector field
  boost::array<DGM::Side*,nfield>  Us_adj;

  /// check for call to setup
  bool                             proper_setup;

public:

#ifdef REO_USE_GETSIDEMAPS
  /// used to match integration point order on local and adjacent side
  DGM::Domain::SideMap             smap;
#endif

  /// distinguish between integration point ordering
  enum LocAdj {
    loc,  ///< a vector uses the local sides integration point ordering
    adj   ///< a vector uses the adjacent sides integration point ordering
  };

  /// constructor
  MatrixSideAssembler(
      const DGM::vField &Uf,
      const bool have_adj_matrix_
  ) :
    maxnModes(get_Lmax_for_vField(Uf)),
    have_adj_matrix(have_adj_matrix_),
    MATlocloc(maxnModes*nfield, maxnModes*nfield, 0.0),
    proper_setup(false)
  {
    if (have_adj_matrix)
      MATlocadj.resize(maxnModes*nfield, maxnModes*nfield);
  }

  /// set the next set of elements to be processed
  void setup(
      const DGM::Domain *const d,
      boost::array<DGM::Side*,nfield> &Us_loc_,
      boost::array<DGM::Side*,nfield> &Us_adj_
      ) {
    TIME_ME();
    if (not have_adj_matrix)
      throw DGM::exception("No adjacent matrix setup! This is a buggy call!");
    Us_loc = Us_loc_;
    Us_adj = Us_adj_;
    MATlocloc = 0.0;
    MATlocadj = 0.0;
#ifdef REO_USE_GETSIDEMAPS
    d->get_side_maps(Us_loc[0], Us_adj[0], smap.idl(), smap.idr());
#endif
    proper_setup = true;
  }

  /// set the next set of elements to be processed
  void setup(
      const DGM::Domain *const d,
      boost::array<DGM::Side*,nfield> &Us_loc_
      ) {
    TIME_ME();
    if (have_adj_matrix)
      throw DGM::exception("Adjacent matrix was setup, but you do not use it?"
                           " This is an inefficient call!!!");
    Us_loc = Us_loc_;
    MATlocloc = 0.0;
    proper_setup = true;
  }

  /// do an tangent/system integral (test from local & trial from
  /// adj. element)
  /**
   * \tparam utest    choose test field
   * \tparam dtest    choose derivative of the test field
   * \tparam utrial   choose trial field
   * \tparam dtrial   choose derivative of the trial field
   * \tparam T        can be a Scalar or a dVector
   */
  template<PhysField utest,  Matrix::Derivative dtest,
           PhysField utrial, Matrix::Derivative dtrial,
           typename T>
  void locadj(
      const T &v,               ///< to be multiplied with test shape function
      const LocAdj locadj = loc ///< Gauss point ordering of input vector v
  ) {
    TIME_ME();
    if (not have_adj_matrix)
      throw DGM::exception("No adjacent Side setup. Use different "
                           "constructor!");
    const std::size_t fieldpostest = FieldNum<utest>::pos;
    const std::size_t fieldpostrial = FieldNum<utrial>::pos;

    const int nModes_test  = Us_loc[fieldpostest ]->nModes();
    const int nModes_trial = Us_adj[fieldpostrial]->nModes();

    DGM::dVector ws_loc(Us_loc[fieldpostest ]->qtot());
    DGM::dVector ws_adj(Us_adj[fieldpostrial]->qtot());

    for (int jtrial=0; jtrial<nModes_trial; jtrial++) {
      sol<dtrial>(Us_adj[fieldpostrial], jtrial, ws_adj);
      if (locadj == adj) {
        ws_adj *= v;
#ifdef REO_USE_GETSIDEMAPS
        smap.renumber(ws_adj, ws_loc);
#else
        const Element* U = Us_loc[0]->elink;
        const Size qstot = ws_loc.size();
        // assume that both sides have the same number of quadrature points
        assert(ws_adj.size() == ws_loc.size());
        for (Size q = 0; q < qstot; ++q) {
          const Ordinal ql = U->sideMap(Us_loc[0], q);
          const Ordinal qr = U->sideMap(Us_adj[0], q);
          ws_loc(ql) = ws_adj(qr);
        }
#endif
      } else {
#ifdef REO_USE_GETSIDEMAPS
        smap.renumber(ws_adj, ws_loc);
#else
        const Element* U = Us_loc[0]->elink;
        const Size qstot = ws_loc.size();
        // assume that both sides have the same number of quadrature points
        assert(ws_adj.size() == ws_loc.size());
        for (Size q = 0; q < qstot; ++q) {
          const Ordinal ql = U->sideMap(Us_loc[0], q);
          const Ordinal qr = U->sideMap(Us_adj[0], q);
          ws_loc(ql) = ws_adj(qr);
        }
#endif
        ws_loc *= v;
      }
      DGM::dVector wh(Us_loc[fieldpostest]->nModes());
      test<dtest>(Us_loc[fieldpostest], ws_loc, wh);
      const int trialpos = nModes_trial*fieldpostrial + jtrial;
      for (int itest=0; itest<nModes_test; itest++) {
        const int testpos = nModes_test*fieldpostest + itest;
        MATlocadj(testpos,trialpos) += wh(itest);
      }
    }
  }

  /// do an tangent/system integral (test and trial side from local element)
  /**
   * \tparam utest    choose test field
   * \tparam dtest    choose derivative of the test field
   * \tparam utrial   choose trial field
   * \tparam dtrial   choose derivative of the trial field
   * \tparam T        can be a Scalar or a dVector
   */
  template<PhysField utest,  Matrix::Derivative dtest,
           PhysField utrial, Matrix::Derivative dtrial,
           typename T>
  void locloc(
      const T &v  ///< to be multiplied with test shape function
  ) {
    TIME_ME();
    const std::size_t fieldpostest  = FieldNum<utest>::pos;
    const std::size_t fieldpostrial = FieldNum<utrial>::pos;

    const int nModes_test  = Us_loc[fieldpostest ]->nModes();
    const int nModes_trial = Us_loc[fieldpostrial]->nModes();

    DGM::dVector ws_loc(Us_loc[fieldpostrial]->qtot());

    for (int jtrial=0; jtrial<nModes_trial; jtrial++) {
      sol<dtrial>(Us_loc[fieldpostrial], jtrial, ws_loc);
      ws_loc *= v;
      DGM::dVector wh(Us_loc[fieldpostest]->nModes());
      test<dtest>(Us_loc[fieldpostest], ws_loc, wh);
      const int trialpos = nModes_trial*fieldpostrial + jtrial;
      for (int itest=0; itest<nModes_test; itest++) {
        const int testpos = nModes_test*fieldpostest + itest;
        MATlocloc(testpos,trialpos) += wh(itest);
      }
    }
  }

  /// scatter local to global
  void scatter(
      const DGM::vField &Uf,  ///< vector field that contains the unknowns
      Epetra_CrsMatrix  &A    ///< global parallel matrix
      ) {
    TIME_ME();
    const vector<int> &indices_loc =
      Uf.get_row_elem_dofs(Us_loc[0]->elink->gid());
    DGM::Domain::scatterMatrix(indices_loc,indices_loc, MATlocloc, A);
    if (have_adj_matrix) {
      const vector<int> &indices_adj =
        Uf.get_col_elem_dofs(Us_adj[0]->elink->gid());
      DGM::Domain::scatterMatrix(indices_loc,indices_adj, MATlocadj, A);
    }
    proper_setup = false;
  }
};


/// This class allows to integrate and assemble a vector side weak form term
/**
 *
 * Evaluate an residual/rhs integral of the form
 *
 * \f[ \hat{b}_I += \int_\Gamma \phi_I(x) v(x) \mathrm{d} x \f]
 *
 * or, if v is a constant,
 *
 * \f[ \hat{b}_I += \int_\Gamma \phi_I(x) v \mathrm{d} x \f]
 *
 * \tparam nfield number of elements in your vector field
 */
template<int nfield>
class VectorSideAssembler {

  /// contains the maximum number of modes per element max-ed over all
  /// elements
  int maxnModes;
  /// residual/rhs element vector
  DGM::dVector bh;
  /// vector of local sides, corresponds to your vector field
  boost::array<DGM::Side*,nfield>  Us_loc;
  /// check for call to setup
  bool proper_setup;

public:
  /// constructor
  VectorSideAssembler(
      const DGM::vField &Uf    ///< field for which we build the residual/rhs
  ) : maxnModes(get_Lmax_for_vField(Uf)),
      bh(maxnModes*nfield, 0.0),
      proper_setup(false){
  }

  /// set the next set of elements to be processed
  void setup(const boost::array<DGM::Side*,nfield> &Us_loc_) {
    Us_loc = Us_loc_;
    bh = 0.0;
    proper_setup = true;
  }

  /// do an residual/rhs integral
  /**
   * \tparam utest    choose test field
   * \tparam dtest    choose derivative of the test field
   * \tparam T        can be a Scalar or a dVector
   */
  template<PhysField utest,  Matrix::Derivative dtest,
           typename T>
  void loc(
    const T &v  ///< to be multiplied with test shape function
  ) {
    const std::size_t fieldpostest = FieldNum<utest>::pos;
    const int nModes_test  = Us_loc[fieldpostest ]->nModes();
    DGM::dVector wh(Us_loc[fieldpostest]->nModes());
    test<dtest>(Us_loc[fieldpostest], v, wh);
    for (int itest=0; itest<nModes_test; itest++) {
      const int testpos = nModes_test*fieldpostest + itest;
      bh(testpos) += wh(itest);
    }
  }

  /// scatter local to global
  void scatter(
      const DGM::vField &Uf,  ///< vector field that contains the unknowns
      Epetra_Vector     &b    ///< global parallel rhs/residual vector
      ) {
    const vector<int> &indexlist =
      Uf.get_row_elem_dofs(Us_loc[0]->elink->gid());
    DGM::Domain::scatterVector( indexlist, bh, b);
    proper_setup = false;
  }

};

/// This class allows to integrate and assemble a matrix domain weak form term
/**
 *
 * Evaluate an tangent/system matrix integral of the form
 *
 * \f[ \hat{A}_{IJ} += \int_\Omega \phi_I(x) v(x) \phi_J(x) \mathrm{d} x \f]
 *
 * or, if v is a constant,
 *
 * \f[ \hat{A}_{IJ} += \int_\Omega \phi_I(x) v \phi_J(x) \mathrm{d} x \f]
 *
 * \tparam nfield number of elements in your vector field
 */
template<int nfield>
class MatrixDomainAssembler {

  /// contains the maximum number of modes per element max-ed over all
  /// elements
  int maxnModes;
  /// tangent/system element matrix for local element
  DGM::dMatrix                       MATlocloc;
  /// vector of elements, corresponds to your vector field
  boost::array<DGM::Element*,nfield> es;
  /// check for call to setup
  bool proper_setup;

public:
  /// constructor
  MatrixDomainAssembler(
      const DGM::vField &Uf
  ) :
    maxnModes(get_Lmax_for_vField(Uf)),
    MATlocloc(maxnModes*nfield, maxnModes*nfield, 0.0),
    proper_setup(false)
  {

  }

  /// set the next set of elements to be processed
  void setup(const boost::array<DGM::Element*,nfield> &es_) {
    es = es_;
    MATlocloc = 0.0;
    proper_setup = true;
  }

  /// do an tangent/system integral
  /**
   * \tparam utest    choose test field
   * \tparam dtest    choose derivative of the test field
   * \tparam utrial   choose trial field
   * \tparam dtrial   choose derivative of the trial field
   * \tparam T        can be a Scalar or a dVector
    */
  template<PhysField utest,  Matrix::Derivative dtest,
           PhysField utrial, Matrix::Derivative dtrial,
           typename T>
  void locloc(
      const T &v  ///< to be multiplied with test shape function
  ) {
    const std::size_t fieldpostest  = FieldNum<utest>::pos;
    const std::size_t fieldpostrial = FieldNum<utrial>::pos;

    const int nModes_test = es[fieldpostest]->nModes();
    const int nModes_trial = es[fieldpostrial]->nModes();
    DGM::dVector psi(es[fieldpostest]->qtot);
    DGM::dVector dpsi(es[fieldpostest]->qtot);
    DGM::dVector fh(nModes_test);
    for (int jtrial=0; jtrial<nModes_trial; jtrial++) {

      es[fieldpostrial]->fill( es[fieldpostrial]->psi->mode[jtrial], psi );
      DGM::dVector ut;
      switch (dtrial) {
      case Matrix::d0:
        ut.alias(psi); break;
      case Matrix::dx:
        es[fieldpostrial]->gradient( psi, dpsi, 'x'); ut.alias(dpsi); break;
      case Matrix::dy:
        es[fieldpostrial]->gradient( psi, dpsi, 'y'); ut.alias(dpsi); break;
      case Matrix::dz:
        es[fieldpostrial]->gradient( psi, dpsi, 'z'); ut.alias(dpsi); break;
      default:
        throw DGM::exception("Wrong option in assembler!");
        break;
      }
      ut *= v;
      switch (dtest) {
      case Matrix::d0:
        es[fieldpostest]->test_on_shape(ut,fh); break;
      case Matrix::dx:
        es[fieldpostest]->test_on_grad_shape(ut,'x',fh); break;
      case Matrix::dy:
        es[fieldpostest]->test_on_grad_shape(ut,'y',fh); break;
      case Matrix::dz:
        es[fieldpostest]->test_on_grad_shape(ut,'z',fh); break;
      default:
        throw DGM::exception("Wrong option in assembler!");
        break;
      }
      const int trialpos = nModes_trial*fieldpostrial + jtrial;
      for (int itest=0; itest<nModes_test; itest++) {
        const int testpos = nModes_test*fieldpostest + itest;
        MATlocloc(testpos, trialpos) += fh[itest];
      }
    }
  }

  /// scatter local to global
  void scatter(
      const DGM::vField &Uf,  ///< vector field that contains the unknowns
      Epetra_CrsMatrix  &A    ///< global parallel matrix
      ) {
    //DGM::Comm::World->cerr()<<"GID = "<<es[0]->gid()<<std::endl;
    const vector<int> &indexlist = Uf.get_row_elem_dofs(es[0]->gid());
#if 0
    for (auto i : indexlist) {
      if (i==1945)
        DGM::Comm::World->cerr()<<i<<", gid = "<<es[0]->gid()<<std::endl;
    }
#endif
    DGM::Domain::scatterMatrix( indexlist, indexlist, MATlocloc, A);
    proper_setup = false;
  }
};

/// Class that allows integrates and assembles a vector domain weak form term
/**
 *
 * Evaluate an residual/rhs integral of the form
 *
 * \f[ \hat{b}_I += \int_\Omega \phi_I(x) v(x) \mathrm{d} x \f]
 *
 * or, if v is a constant,
 *
 * \f[ \hat{b}_I += \int_\Omega \phi_I(x) v \mathrm{d} x \f]
 *
 * \tparam nfield number of elements in your vector field
 */
template<int nfield>
class VectorDomainAssembler {

  /// contains maximum number of modes per element max-ed over all elements
  int maxnModes;

  /// residual/rhs element vector
  DGM::dVector bh;

  /// vector of elements, corresponds to your vector field
  boost::array<DGM::Element*,nfield> es;

  /// check for call to setup
  bool proper_setup;

public:
  /// constructor
  VectorDomainAssembler(
      const DGM::vField &Uf    ///< field for which we build the residual/rhs
  ) : maxnModes(get_Lmax_for_vField(Uf)),
      bh(maxnModes*nfield, 0.0),
      proper_setup(false) {
  }

  /// set the next set of elements to be processed
  void setup(const boost::array<DGM::Element*,nfield> &es_) {
    es = es_;
    bh = 0.0;
    proper_setup = true;
  }

  /// do an residual/rhs integral
  /**
   * \tparam utest    choose test field
   * \tparam dtest    choose derivative of the test field
   * \tparam T        can be a Scalar or a dVector
   */
  template<PhysField utest,  Matrix::Derivative dtest,
           typename T>
  void loc(
      const T &v  ///< to be multiplied with test shape function
  ) {
    const std::size_t fieldpostest = FieldNum<utest>::pos;

    const int nModes_test = es[fieldpostest]->nModes();
    DGM::dVector fh(nModes_test);
    switch (dtest) {
    case Matrix::d0:
      es[fieldpostest]->test_on_shape(v,fh); break;
    case Matrix::dx:
      es[fieldpostest]->test_on_grad_shape(v,'x',fh); break;
    case Matrix::dy:
      es[fieldpostest]->test_on_grad_shape(v,'y',fh); break;
    case Matrix::dz:
      es[fieldpostest]->test_on_grad_shape(v,'z',fh); break;
    default:
      break;
    }
    for (int itest=0; itest<nModes_test; itest++) {
      const int testpos = nModes_test*fieldpostest + itest;
      bh(testpos) += fh[itest];
    }
  }

  /// scatter local to global
  void scatter(
      const DGM::vField &Uf,  ///< vector field that contains the unknowns
      Epetra_Vector     &b    ///< global parallel rhs/residual vector
      ) {
    const vector<int> &indexlist = Uf.get_row_elem_dofs(es[0]->gid());
    DGM::Domain::scatterVector( indexlist, bh, b);
    proper_setup = false;
  }

};

} // namespace Matrix

} // namespace DGM

#endif // DGM_USE_EPETRA

#endif // DGM_MATRIX_ASSEMBLER_HPP
