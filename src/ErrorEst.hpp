#ifndef DGM_ERROREST_HPP
#define DGM_ERROREST_HPP

/** \file ErrorEst.hpp
    \brief DGM error estimation optimizer declaration
    \author Scott Collis
*/

// DGM includes
#include "Comm.hpp"
#include "State.hpp"
#include "Adjoint.hpp"
#include "Optimizer.hpp"
#include "Control.hpp"

namespace DGM {

/// Error estimation abstract base class
class ErrorEst : public Optimizer {

  Table params;           ///< Parameter table
  Ordinal npredict;       ///< Number of time steps

public:

  ErrorEst(State* state_, Adjoint* adjoint_,
           Control::Ptr control_, const DGM::Comm::Ptr comm_);

  virtual void check_grad() {DGM_UNDEFINED;}
  virtual void optimize(const Ordinal=0);
  virtual Scalar advance(const Ordinal) { return 0; }
  virtual Ordinal readRestart(const string * = NULL) {
    DGM_UNDEFINED; return 0;}
  virtual void writeRestart(const string * = NULL) const {DGM_UNDEFINED;}
  virtual void plotControl(const Ordinal ntout=1, const Ordinal riter=0) const {
    DGM_UNDEFINED;
  }

};

} // namespace DGM

#endif  // DGM_ERROREST_HPP
