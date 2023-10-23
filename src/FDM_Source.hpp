#ifndef FDM_SOURCE_HPP
#define FDM_SOURCE_HPP

/** \file FDM_Source.hpp
    \brief FDM::Source interface
    \author Scott Collis
    \author Bill Spotz
*/

// FDM includes
#include "FDM_Types.hpp"
#include "FDM_VectorField.hpp"
#include "FDM_Ctrl.hpp"
#include "FDM_Objective.hpp"

namespace FDM
{

//! FDM Source
class Source : public DTK::Source< FDM::VectorField,
                                   FDM::ScalarVector,
                                   FDM::Scalar,
                                   FDM::Ordinal,
                                   FDM::Ctrl,
                                   FDM::Obs >
{
public:
  typedef Teuchos::RCP< Source > Ptr;
  typedef map<std::string,Ptr> db_type;     ///< source database
  typedef db_type::iterator db_itr;         ///< source database iterator
  typedef db_type::const_iterator db_citr;  ///< source database const iterator

  /// Constructor
  Source(const std::string t);

  /// Destructor
  virtual ~Source();
};

}  // namespace FDM

#endif
