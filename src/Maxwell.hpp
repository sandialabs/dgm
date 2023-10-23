#ifndef REO_MAXWELL_HPP
#define REO_MAXWELL_HPP

/** \file  Maxwell.hpp
    \brief Declarations for the 2d Maxwell equations
    \author Scott Collis
*/

// DGM includes
#include "Comm.hpp"
#include "Domain.hpp"
#include "Element.hpp"
using namespace DGM;

// Reo includes
#include "ReoConfig.hpp"

namespace Reo {

/// Two-dimensional Maxwell Domain
class Maxwell : public Domain {

  dVector wk1;   ///< local workspace
  dVector wk2;   ///< local workspace

protected:

  static const int NFIELDS = 3; ///< fixed number of fields for static arrays

public:

  // BC declarations
  class WallBC;

  // Source terms
  class Sponge;

  /// Constructor
  Maxwell( DGM::ArgList &args, const DGM::Comm::Ptr = DGM::Comm::World,
           const int pinc=0);

  /// Destructor
  virtual ~Maxwell();

  // override virtual Domain methods
  virtual void parse_args( DGM::ArgList &args );
  virtual void showUsage();

  virtual int plot(const string&);

  virtual void set_material();

  virtual void time_derivative( vField &, vField & );

  virtual Scalar set_time_step( vField & );

  virtual void set_ic( vField &, string=".ic" );

  virtual void setup_BCdb( );
  virtual void read_BCdb( ifstream & );
  virtual BC* make_BC( ifstream &, string & );

  virtual Source::Ptr make_Source( ifstream &, string & );
  virtual void add_source(const vField &, vField & );

  virtual void write_bndry_stats();

protected:

  /// Supported numerical fluxes
  enum flux_type {
    LaxFriedrichs          ///< Lax-Friedrichs flux
  };

  /// Active numerical flux
  flux_type flux;

  // local methods
  void gradient( Element *, Element *, dVector &, dVector &, dVector & );

  void interior( vField &, vField & );
  void surface( vField &, vField & );
};

} // namespace Reo

#endif  // REO_MAXWELL_HPP
