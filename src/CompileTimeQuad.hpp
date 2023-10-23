#ifndef DGM_COMPILETIMEQUAD_HPP
#define DGM_COMPILETIMEQUAD_HPP

/** \file CompileTimeQuad.hpp
    \brief Quad Element declaration
    \author N. Belcourt, S. Collis

    Parameterized version of the Quad element.
*/

// DGM includes
#include "MatrixOperations.hpp"
#include "Quad.hpp"

namespace DGM {

  template <int N, int M, typename Iterator>
  void initialize(Iterator it, const Iterator c_it) {
    for (int j=0; j<M; ++j) {
      for (int i=0; i<N; ++i, ++it) {
        *it = *(c_it + i * M + j);
      }
    }
  }
  
  // P order and Q
  template <int P, int Q>
  struct CompileTimeQuad : public Quad {
    // Ba_T and Bb_T are row major tranposes, align to start at beginning of
    // cache line
#if defined(__AVX__) || defined(__AVX2__)
    // alignas(64)
#endif
    mutable std::array<DGM::Scalar, (P+1)*Q> Ba_T, Bb_T;

    template <typename ...Args>
    CompileTimeQuad(Args&... args) : Quad(args...) {
    }

    virtual Basis* get_basis(const int der) const {
      // invoke base class to create new Basis
      Basis* psi = Quad::get_basis(der);
      // construct transposes from the basis
      initialize<P+1,Q>(Ba_T.begin(), psi->ba[0].data());
      initialize<P+1,Q>(Bb_T.begin(), psi->bbv[0].data());
      // return new basis
      return psi;
    }

    virtual void inner_product(dVector &f, dVector &fh) const {
      // dot product: f *= wJ
      multiply<(P+1)*Q>(f.begin(), f.end(), geom->wJ.begin());
      // matmul: Lwk = Ba * f
      multiply<P+1,Q,Q>(Lwk.begin(), psi->ba->begin(), f.begin());
      // matmul: fh = Lwk * Bb_T
      multiply<P+1,Q,P+1>(fh.begin(), Lwk.begin(), begin(Bb_T));
    }

    virtual void backward_transform(dVector &fh, dVector &f) const {
      // matmul: Lwk = BaT * fh
      multiply<Q,P+1,P+1>(Lwk.begin(), begin(Ba_T), fh.begin());
      // matmul: f = Lwk * Bb
      multiply<Q,P+1,Q>(f.begin(), Lwk.begin(), psi->bbv->begin());
    }
  };

} // namespace DGM

#endif  // DGM_QUAD_HPP
