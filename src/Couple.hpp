#ifndef REO_COUPLE_HPP
#define REO_COUPLE_HPP

/** \file  Couple.hpp
    \brief Multiphysics coupled domain declaration
    \author Scott Collis
    \author Gouquan Chen
*/

// DGM includes
#include "Comm.hpp"
using namespace DGM;

// local includes
#include "Euler.hpp"
#include "Fluid.hpp"

namespace Reo {

#ifdef DGM_USE_MD_COUPLE

/// Coupled domains
class Couple : public Euler {

  dVector work;

  // Boundary conditions
  class CStateBC;
  class Isothermal_WallBC;
  class Isoflux_WallBC;
  class Isothermal_ControlBC;
  class Isoflux_ControlBC;
  class Isothermal_SteadyControlBC;
  class Isoflux_SteadyControlBC;

  // Source terms
  class Sponge;

public:
  BC::db_type BC_db;              ///< BC database (in addition to Do

  Scalar gamma;                   ///< ratio of specific heats

  Scalar Tref, Pref;              ///< reference temperature and pressure
  Scalar vis;                     ///< reference viscosity
  Scalar Pr;                      ///< Prandtl number

  Fluid * fluid;                  ///< Fluid properties

  vField Uv;                      ///< viscous field
  vField Up;                      ///< Solution field --primitive variables
  vField Um;                      ///< Mean flow field

  /// Constructor
  Couple( DGM::ArgList &args, const DGM::Comm * = NULL );

  // methods

  void set_ic( vField &, string=".ic" );

  void time_derivative( vField &, vField & );

  void convection( vField &, vField & );
  void diffusion( vField &, vField &, vField & );
  void convective_flux( vField &, vField & );

  void enforce_bc( vField & );
  void enforce_flux_bc( vField & );
  void enforce_mean_bc( vField & );

  void setup_BCdb( );
  void read_BCdb( ifstream & );
  BC* make_BC( ifstream &, string & );

  Source::Ptr make_Source( ifstream &, string & );
  void add_source(const vField &, vField & );

  void get_viscosity( dVector & );

  int plot(const int&);
  int plot(const string&);

  // methods for coupling
  Ordinal  solve();
  void zero_all_fields();
  void set_mean(vField &,char );
  void make_U(vField &, const vField &, const vField &);
  void get_Up(vField &, const vField &, const vField &);

  // helpers for computing vorticity and for Navier_Stokes class
  void primitive_sides( vField &);

  /// Need a local average flux
  void average_flux(vField &, vField &, const vField &,char);

private:

  void set_sponge(const vField &,vField &);

  void convert_sides(vector<Side *>, vector<Side *>,
                     const Model::Type, const Model::Type);

  void primitive_sides_c(vector<Side *>, vector<Side *>);

  void conservative_sides(vector<Side *>, vector<Side *>,
                          const Model::Type, const Model::Type);

  void compute_flux(int, Point,vector<Side *>,vector<Side *>,
                    Scalar *,Scalar *);

  void compute_flux1(const iVector ,const dVector& ,
                     const dVector& ,vector<Side *> ,
                     vector<Side *>, dVector& ,dVector& );
};

#endif // DGM_USE_MD_COUPLE

} // namespace Reo

#endif // REO_COUPLE_HPP
