#ifndef FDM_ADJOINT_HPP
#define FDM_ADJOINT_HPP

/** \file FDM_Adjoint.hpp
    \brief FDM::Adjoint interface
    \author Scott Collis
    \author Bill Spotz
*/

// FDM includes
#include "FDM_Types.hpp"
#include "FDM_Control.hpp"
#include "FDM_VectorField.hpp"

namespace FDM
{

// Forward declarations
class Control;
class Objective;
class VectorField;
class Domain;

//! FDM Adjoint
class Adjoint : public DTK::Adjoint< Control,
                                     Objective,
                                     VectorField,
                                     ScalarVector,
                                     Scalar,
                                     Ordinal,
                                     Domain >
{
protected:
  Control *control;
  Control *g_control;
  Objective *objective;
  VectorField Ustate;

public:
  /// shared pointer to Adjoint
  typedef Teuchos::RCP< Adjoint > Ptr;

  /// destructor
  virtual ~Adjoint();

  /// Set the objective function for this adjoint
  virtual void set_objective(Objective *obj);

};

}  // namespace FDM

#endif
