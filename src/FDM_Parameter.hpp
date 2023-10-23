#ifndef FDM_PARAMETER_HPP
#define FDM_PARAMETER_HPP

/** \file FDM_Parameter.hpp
    \brief FDM::Parameter interface
    \author Scott Collis
    \author Bill Spotz
*/

#include "DTK.hpp"

// FDM includes
#include "FDM_Types.hpp"
#include "FDM_Source.hpp"

namespace FDM
{

#if 1

class Parameter : public Source,
                  public DTK::Parameter< VectorField,
                                         ScalarVector,
                                         Scalar,
                                         Ordinal > {
public:

  typedef Teuchos::RCP<Parameter> Ptr;   ///< Shared pointer to Parameter

  /// Constructor
  Parameter(const string t) : Source(t) { }

  /// Destructor
  virtual ~Parameter() { }

  ///\name Overload Source apply methods
  //@{

  /// State apply method
  /** This is a null operation for a parameter, but not necessarily for a
                                               linearized paramter. */
  virtual void apply (const Scalar, const VectorField &, VectorField &) { }

  /// Adjoint apply method
  /** This is a null operation for a parameter. */
  virtual void adjoint_apply( const Scalar, const VectorField &, const VectorField &,
                              VectorField & ) { }

  /// Provides a modifiable reset method, default is null-op
  virtual void reset_source(const ScalarVector &data) {}

  /// Return the number of sources
  virtual Ordinal Nsources() const { return 1; }
  //@}

};

#else

//! FDM Parameter class
typedef DTK::Parameter< VectorField,
                        ScalarVector,
                        Scalar,
                        Ordinal > Parameter;
#endif

}  // namespace FDM

#endif
