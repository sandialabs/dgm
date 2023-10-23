#ifndef REO_LINBURGERS_HPP
#define REO_LINBURGERS_HPP

/** \file LinBurgers.hpp
    \brief Linearized Burgers declarations
    \author Scott Collis
*/

// DGM includes
#include "Comm.hpp"

// Reo includes
#include "ReoConfig.hpp"
#include "Burgers.hpp"
#include "Burgers_State.hpp"

namespace Reo {

/// Linearized Burgers Domain
class LinBurgers : public Burgers {

  const Burgers_State *base_state;   ///< base flow database

  static Scalar dfabs( Scalar );

public:

  vField Ubase;  ///< base flow field

  /// Constructor
  LinBurgers( DGM::ArgList &args, const State *base_ = NULL,
              const DGM::Comm::Ptr = DGM::Comm::World );

  // override virtual Domain methods
  void time_derivative( vField &, vField & );
  void prestep(vField &F, const Ordinal istep, 
                          const Ordinal sstep, const Scalar time);
  void poststep(vField &F,const Ordinal istep, 
                          const Ordinal sstep, const Scalar time);

  void zero_all_fields();
  void set_ic( vField &, string=".ic" );

#if 0
  void setup_BCdb( );
  void read_BCdb( ifstream & );
  BC* make_BC( ifstream &, string & );

  Source* make_Source( ifstream &, string & );
  void add_source(const vField &, vField &);
#endif

protected:

  void convection( vField &, vField & );
  void convective_flux( const vField &, vField &, vField & );

};

} // namespace Reo

#endif  // REO_LINBURGERS_HPP
