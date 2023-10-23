#ifndef DGM_PARAMETER_HPP
#define DGM_PARAMETER_HPP

/** \file Parameter.hpp
    \brief DGM Parameter base class declaration

    \note This derives off of Source and just makes the apply methods
    null-ops.

    \note This is currently implemented as a Source so that there is an
    easily available way to declare this in the root.src input file.  The
    next step would be to declare Parameters in a root.par file.  This
    isn't hard, but didn't seem necessary for this first stab at parameter
    inversion.
*/

// System includes
#include <map>
#include <string>
#include <vector>
using namespace std;

// DGM includes
#include "Types.hpp"
#include "vField.hpp"
#include "Source.hpp"

namespace DGM {

/// Abstraction of a Parameter term
/** This is a thin wrapper for a Source that can be used to hold a general
    DGM parameter that can then be either a Ctrl or an Obs as appropriate. */
class Parameter : public Source,
                  public DTK::Parameter<vField,dVector,Scalar,Ordinal> {
public:

  typedef DGM::Shared<Parameter>::Ptr Ptr;  ///< Shared pointer to Parameter
#if 0
  // these are currently inhereted from Source
  typedef map<string,Ptr> db_type;          ///< database
  typedef db_type::iterator db_itr;         ///< database iterator
  typedef db_type::const_iterator db_citr;  ///< database const iterator
#endif

  /// Constructor
  Parameter(const string t) : Source(t) { }

  /// Destructor
  virtual ~Parameter() { }

  ///\name Overload Source apply methods
  //@{

  /// State apply method
  /** This is a null operation for a parameter, but not necessarily for a
      linearized paramter. */
  virtual void apply (const Scalar, const vField &, vField &) { }

  /// Adjoint apply method
  /** This is a null operation for a parameter. */
  virtual void adjoint_apply( const Scalar, const vField &, const vField &,
                              vField & ) { }
  //@}

};

} // namespace DGM

#endif  // DGM_PARAMETER_HPP
