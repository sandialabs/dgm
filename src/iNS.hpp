#ifndef REO_INS_HPP
#define REO_INS_HPP

/** \file iNS.hpp
    \brief Incompressible Navier-Stokes equations. */

// system includes
#include <fstream>

// local includes
#include "ReoConfig.hpp"
#include "iEuler.hpp"

namespace Reo {

/// 2-d incompressible Navier-Stokes Domain
class iNS: public iEuler {

  dVector work;

  // BC declarations (definitions included below)
  class WallBC;

 public:

  BC::db_type BC_db;              // BC database (in addition to Domain)

  Scalar vis;                     // reference viscosity

  vField Uv;                      // Viscous field

  // constructor
  iNS( DGM::ArgList &args, const DGM::Comm::Ptr = DGM::Comm::World );

  // override virtual Domain methods
  void set_material();

  void time_derivative( vField &, vField & );

  void zero_all_fields();

  void setup_BCdb( );
  void read_BCdb( ifstream & );
  BC* make_BC( ifstream &, string & );

  //void write_bndry_stats();

  void enforce_bc(vField &);
  void enforce_flux_bc(vField &);

  void add_source(const vField &, vField &);

  // local methods

  void get_viscosity( dVector & );
  void diffusion( vField &, vField &, vField & );
};

} // namespace Reo

#endif  // REO_INS_HPP
