#ifndef REO_NAVIER_STOKES_HPP
#define REO_NAVIER_STOKES_HPP

/** \file  Navier_Stokes.hpp
    \brief Declarations for the 2d Navier-Stokes equations   */

// system includes
#include <fstream>

// DGM includes
#include "Comm.hpp"
#include "Domain.hpp"
#include "Element.hpp"
using namespace DGM;

// local includes
#include "ReoConfig.hpp"
#include "Euler.hpp"

namespace Reo {

// forward declarations
class IdealGas;

/// two-dimensional, compressible Navier-Stokes equations
class Navier_Stokes : public Euler {

  dVector work;                   ///< local work vector

  // BC declarations (definitions included below)
  class Isothermal_WallBC;
  class Isoflux_WallBC;
  class Isothermal_SlipWallBC;
  class Isoflux_SlipWallBC;
  class Isothermal_ControlBC;
  class Isoflux_ControlBC;
  class Isothermal_SteadyControlBC;
  class Isoflux_SteadyControlBC;
  class Isoflux_stress_ControlBC;
  class Jet_ControlBC;
  class SondhausWallBC;

 public:

  BC::db_type BC_db;              ///< BC database (in addition to Domain's)

  Scalar Tref;                    ///< reference temperature and pressure
  Scalar Pref;                    ///< reference pressure
  Scalar vis;                     ///< reference viscosity
  Scalar Pr;                      ///< Prandtl number

  vField Uv;                      ///< Viscous field

  /// Constructor
  Navier_Stokes( DGM::ArgList &args, const DGM::Comm::Ptr = DGM::Comm::World );

  /// Destructor
  virtual ~Navier_Stokes();

  // local methods
  void parse_args( DGM::ArgList &args );
  void showUsage();

  // override virtual Domain methods

  void set_material();

  void time_derivative( vField &, vField & );

  void zero_all_fields();

  void setup_BCdb( );
  void read_BCdb( ifstream & );
  BC* make_BC( ifstream &, string & );

  void write_bndry_stats();

  void enforce_bc(vField &);
  void enforce_flux_bc(vField &);

  void add_source(const vField &, vField &);

protected:

  // local methods

  void get_viscosity( dVector & );
  void diffusion( vField &, vField &, vField & );
};

} // namespace Reo

#endif  // REO_NAVIER_STOKES_HPP
