#ifndef REO_NAVIER_STOKES3D_HPP
#define REO_NAVIER_STOKES3D_HPP

/** \file Navier_Stokes3d.hpp
    \brief Declarations for the 3d Navier-Stokes equations. */

// DGM includes
#include "Comm.hpp"
#include "SpectralFilter.hpp"

// Reo includes
#include "Fluid.hpp"
#include "Euler3d.hpp"

namespace Reo {

/// Three-dimensional compressible Navier--Stokes Domain
class Navier_Stokes3d : public Euler3d {

  dVector wk2;           ///< local work space

  static FilterDB fdb;   ///< Filter database

  /// Iso-thermal wall boundary condition
  class Isothermal_WallBC : public BC {
    const int ndof;      ///< number of degrees of freedom
    Scalar Tw;           ///< constant wall temperature
    Scalar Eref;         ///< reference stagnation energy per unit volume
                         ///< (rho_r*T_r)/(gamma*(gamma-1)*Ma_r^2)
  public:
    Isothermal_WallBC( const string t, const int ndof_, const Scalar Tw_,
                       const Scalar Eref_ ) :
      BC(t), ndof(ndof_), Tw(Tw_), Eref(Eref_) {}
    Isothermal_WallBC( const string t, ifstream &in, const int ndof_) :
      BC(t), ndof(ndof_), Tw(0), Eref(0)
    {
      scan_lb(in);
      if (!(in >> Tw >> Eref))
        error("Navier_Stokes3d::Isothermal_WallBC: Tw, Eref");
      scan_rb(in);
      if (ndof!=5) error("Navier_Stokes3d::Isothermal_WallBC requires ndof=5");
    }
    void apply( const Scalar, const vField & ) ;
    void apply_flux( const Scalar, const vField & ) ;

    void adjoint_apply( const Scalar, const vField &, const vField & ) ;
    void adjoint_apply_flux( const Scalar, const vField &, const vField & ) ;
   };

  /// Iso-heat-flux wall boundary condition
  class Isoflux_WallBC : public BC {
    const int ndof;    ///< number of degrees of freedom
    Scalar qw;         ///< constant heat flux
  public:
    Isoflux_WallBC( const string t, const int ndof_, const Scalar qw_ ) :
      BC(t), ndof(ndof_), qw(qw_) {}
    Isoflux_WallBC( const string t, ifstream &in, const int ndof_) :
      BC(t), ndof(ndof_), qw(0)
    {
      scan_lb(in);
      if (!(in >> qw)) error("Navier_Stokes3d::Isoflux_WallBC: Tw, Eref");
      scan_rb(in);
      if (ndof!=5) error("Navier_Stokes3d::Isoflux_WallBC requires ndof=5");
    }
    void apply( const Scalar, const vField & ) ;
    void apply_flux( const Scalar, const vField & ) ;

    void adjoint_apply( const Scalar, const vField &, const vField & ) ;
    void adjoint_apply_flux( const Scalar, const vField &, const vField & ) ;
  };

  /// Iso-thermal wall boundary condition
  class Periodic_WallBC : public Isothermal_WallBC {
  public:
    Periodic_WallBC( const string t, const int ndof_, const Scalar Tw_,
        const Scalar Eref_ ) : Isothermal_WallBC(t, ndof_, Tw_, Eref_) {}
    Periodic_WallBC( const string t, ifstream &in, const int ndof_) :
      Isothermal_WallBC(t, in, ndof_) {}
   };

 public:

  BC::db_type BC_db;              ///< BC database (in addition to Domain)

  Scalar Tref;                    ///< Reference temperature
  Scalar Pref;                    ///< Reference pressure
  Scalar vis;                     ///< Reference viscosity
  Scalar Pr;                      ///< Prandtl number

  vField Uv;                      ///< Viscous field

  Fluid *fluid;                   ///< Fluid properties

  /// Type of spatial filter
  enum FilterType {
    NOFILTER = 0,                 ///< do not filter
    APPLYFILTER = 1               ///< use default filter
  };

  /// Type of turbulence model
  enum ModelType {
    DNS=0,                        ///< Direct Numerical Simulation
    LES=1                         ///< Large Eddy Simulation
  };

  int filter;                     ///< Filter switch
  int filter_freq;                ///< Filter frequency
  vector<Filter*> efilter;        ///< Element filter vector

  int model;                      ///< Simulation type
  Scalar Cs;                      ///< Smagorinsky Coefficient
  Scalar Delta2;                  ///< Model Length scale

  /// Constructor
  Navier_Stokes3d( DGM::ArgList &args,
                   const DGM::Comm::Ptr = DGM::Comm::World );

  /// Destructor
  virtual ~Navier_Stokes3d() {
    if (fluid) delete fluid;
    for (size_t i=0; i<efilter.size(); i++) delete efilter[i];
  }

  // Provide Domain interface

  void time_derivative( vField &, vField & );

  void zero_all_fields();

  void setup_BCdb( );
  void read_BCdb( ifstream & );
  BC* make_BC( ifstream &, string & );

  void enforce_bc(vField &);
  void enforce_flux_bc(vField &);

  void write_bndry_stats();

protected:

  // Local methods

  Filter* get_filter(const Ordinal);
  void get_viscosity( dVector & );
  void diffusion( vField &, vField &, vField & );

};

} // namespace Reo

#endif  // REO_NAVIER_STOKES3D_HPP
