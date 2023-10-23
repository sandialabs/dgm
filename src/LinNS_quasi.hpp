#ifndef REO_LINNS_QUASI_HPP
#define REO_LINNS_QUASI_HPP

/** \file  LinNS_quasi.hpp
    \brief Linearized Navier-Stokes equations in quasi-conservative variables
    \author Scott Collis
*/

// Reo includes
#include "Navier_Stokes.hpp"

namespace Reo {

/// Linearized 2d compressible Navier-Stokes in quasi-conservative variables
class LinNS_quasi : public Navier_Stokes {

  dVector wk3;    ///< Workspace
  dVector wk4;    ///< Workspace

 public:

  Scalar Ma;      ///< Mach number
  Scalar Re;      ///< Reynolds number
  Scalar mu;      ///< Molecular viscosity
  Scalar lambda;  ///< Second coefficient of viscosity
  Scalar Pr;      ///< Prandlt number
  Scalar K;       ///< Thermal conductivity

  vField Up;      ///< Solution field -- primitive variables
  vField Um;      ///< Mean flow field
  vField Um_x;    ///< x-gradient of mean flow
  vField Um_y;    ///< y-gradient of mean flow

  // constructor
  LinNS_quasi( DGM::ArgList &args, const DGM::Comm::Ptr = DGM::Comm::World );

  // override virtual Domain methods
  virtual int solve();
  virtual int plot(const string &);
  virtual void time_derivative( vField &, vField & );

  void zero_all_fields();

  void enforce_bc(vField &);
  void enforce_flux_bc(vField &);

  // override public Euler methods
  void convection( vField &, vField & );
  void convective_flux( vField &, vField & );

  // override public Navier_Stokes methods
  void diffusion( vField &, vField &, vField & );

 private:

  /// Supported convective numerical fluxes
  enum flux_type {
    Roe,
    vanLeer,
    StegerWarming,
    LaxFriedrichs
  };

  void viscous_convection( vField &, vField &, vField & );
  void viscous_convective_flux( vField &, vField & );

  void enforce_mean_state_bc(vField &);
  void enforce_mean_derivate_bc(vField &);

  /// Setup the mean (base) flow solution
  void set_mean(vField &);
  /// Make the conservative variables
  void make_U(vField &, const vField &, const vField &);
  /// Get primitive variables
  void get_Up(vField &, const vField &, const vField &);
};

} // namespace Reo

#endif  // REO_LINNS_QUASI_HPP
