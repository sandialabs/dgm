#ifndef FDM_OBJFUNC_HPP
#define FDM_OBJFUNC_HPP

/** \file FDM_ObjFunc.hpp
    \brief FDM::ObjFunc interface
    \author Scott Collis
    \author Bill Spotz
*/

// FDM includes
#include "FDM_Types.hpp"
#include "FDM_VectorField.hpp"
#include "FDM_Control.hpp"
#include "FDM_Objective.hpp"

namespace FDM
{

//! FDM ObjFunc
class ObjFunc : public DTK::ObjFunc< Scalar,
                                     Ordinal,
                                     VectorField >
{
private:
  Control::Ptr   _control;
  Objective::Ptr _objective;

  // Ordinal        _npredict;     ///< number of steps to optimize over
  size_t         _nterms;       ///< number of terms in this objective function
  Scalar         _value;        ///< value of the objective function


  /// Initializer helper method for constructors
  void initialize();

public:
  typedef Teuchos::RCP< ObjFunc > Ptr;

  ObjFunc(Control::Ptr   c,
          Objective::Ptr o);

  /// Evaluate the objective function
  virtual Scalar evaluate(const VectorField & S,
                          const Ordinal istep,
                          const Ordinal sstep=0);

  /// Evaluate the terminal condition
  /** \todo Fix this. */
  virtual Scalar terminal(const VectorField &,
                          const Ordinal,
                          const Ordinal=0);

  /// Value accessor
  Scalar & value();

  /// Const value accessor
  const Scalar & value() const;

  void value(const Scalar v) { _value = v; }

};

}  // namespace FDM

#endif
