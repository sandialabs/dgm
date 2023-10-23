/** \file FDM_ObjFunc.cpp
    \brief FDM::ObjFunc interface
    \author Scott Collis
    \author Bill Spotz
*/

// FDM includes
#include "FDM_ObjFunc.hpp"

namespace FDM
{

// Initializer helper method for constructors
void ObjFunc::initialize()
{
  _nterms = _control->num_ctrl() + _objective->num_obs();
  _objective->reset_costs();
  //_control->reset_costs();
  //_npredict = _control->get_npredict();
}

ObjFunc::ObjFunc(Control::Ptr   c,
                 Objective::Ptr o) :
  _control(c),
  _objective(o),
  _value(0.0)
{
  initialize();
}

// Evaluate the objective function
Scalar ObjFunc::evaluate(const VectorField & S,
                         const Ordinal istep,
                         const Ordinal sstep)
{
  Scalar result(0);
  result += _objective->cost(S, istep, sstep);
  return result;
}

// Evaluate the terminal condition
/** \todo Fix this. */
Scalar ObjFunc::terminal(const VectorField &,
                         const Ordinal,
                         const Ordinal)
{
  return 0;
}

/// Value accessor
Scalar & ObjFunc::value()
{
  return _value;
}

/// Const value accessor
const Scalar & ObjFunc::value() const
{
  return _value;
}

}  // namespace FDM
