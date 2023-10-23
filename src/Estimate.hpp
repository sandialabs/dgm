#ifndef DGM_ERR_EST_HPP
#define DGM_ERR_EST_HPP

/** \file Estimate.hpp
    \brief DGM error estimation problem class declaration
    \author Scott Collis
*/

// DGM includes
#include "State.hpp"
#include "Adjoint.hpp"
#include "Control.hpp"
#include "Objective.hpp"

namespace DGM {

/// An error estimation problem class
class Estimate {

  const DGM::Comm::Ptr comm;

  Table params;          ///< parameter Table

  string root;           ///< root filename
  int p_inc;             ///< increment for adjoint solve
  int p_ref;             ///< increment for refinement
  int npredict;          ///< number of timesteps to predict error
  int refine;            ///< refinement strategy
  bool steady;           ///< steady or unsteady flow
  Scalar J_exact;        ///< Exact value of objective functional

  State *state;          ///< Original State domain
  Adjoint *adjoint;
  Control::Ptr control;
  Control::Ptr gradient;
  Objective *objective;

  State *state2;         ///< State domain in Adjoint space
  Adjoint *adjoint2;
  Control::Ptr control2;
  Control::Ptr gradient2;
  Objective *objective2;

public:

  Estimate(DGM::ArgList &, const Table &,
           const DGM::Comm::Ptr=DGM::Comm::World);

  inline string get_root_name() const { return root; }

  void estimate();

private:

  void pRefine_20(Scalar* err, int len);

  void pRefine_TOL(Scalar* err, int len, Scalar TOL);

};

} // namespace DGM

#endif  // ERR_EST_HPP
