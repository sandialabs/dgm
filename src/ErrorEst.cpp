/** \file ErrorEst.cpp
    \brief DGM error estimation optimizer implementation
    \author Scott Collis
*/

// DGM includes
#include "Comm.hpp"
#include "ErrorEst.hpp"
#include "Format.hpp"

namespace DGM {

/// Constructor
ErrorEst::ErrorEst(State* state_, Adjoint* adjoint_,
                   Control::Ptr control_, const DGM::Comm::Ptr comm_)
  : Optimizer(state_,adjoint_,control_,comm_) {

  cout<<"ErrorEst::ErrorEst(State*, Adjoint*, Control::Ptr)"<<endl;

  gradient.reset(control->clone());
  gradient->control_type(Control::GRADIENT);

  // set default values
  params["npredict"] = 100;

  // read parameters from an input file
  root = control->root;
  params.read( root+".inp" );

  // initialization
  npredict = params["npredict"];
}

/// Solve the error estimation problem
void ErrorEst::optimize(const Ordinal) {
  static Format sci(8); sci.scientific().width(15);

  state->initialize();
  control->initialize();
  adjoint->initialize();

  state->set_initial_condition();
  Scalar J = state->compute(npredict, control);

  cout<<"  J = "<<J<<endl;

  gradient->zero();

  adjoint->set_end_condition();
  adjoint->compute(npredict, control, gradient);

  dVector error;
  cout<<"Error = "<<state->estimate_error(npredict, adjoint, error)<<endl;
}

} // namespace DGM
