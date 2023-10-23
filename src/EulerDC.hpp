#ifndef REO_EULERDC_HPP
#define REO_EULERDC_HPP

/** \file  EulerDC.hpp
    \brief Euler equations (2d) with discontinuity capturing.
    \author Scott Collis
*/

// system includes
#include <fstream>

// Reo includes
#include "Euler.hpp"

namespace Reo {

// forward declarations
class IdealGas;

/// two-dimensional, compressible Navier--Stokes equations
class EulerDC : public Euler {

  dVector work;

 public:

  Scalar Tref, Pref;  ///< reference temperature and pressure
  Scalar vis;         ///< reference viscosity
  Scalar Pr;          ///< Prandtl number

  Scalar C_epsi0;     ///< artificial viscosity coefficient
  Scalar kappa_dc;    ///< artificial viscosity wave number bound
  int    L_fs;        ///< fine scale polynomial order bound
  Scalar C_s0;        ///< artificial viscosity decay parameter

  vField Uv;          ///< Viscous field
  vField Nu;          ///< artificial viscosity

  // constructor
  EulerDC( DGM::ArgList &args, const DGM::Comm::Ptr = DGM::Comm::World );

  // override virtual Domain methods
  void time_derivative( vField &, vField & );

  // local methods
  void parse_args( DGM::ArgList &args );
  void showUsage();

  void zero_all_fields();
  void enforce_flux_bc(vField &);

private:

  // local methods
  void get_viscosity( const Element *, dVector &, dVector & );
  void diffusion( vField &, vField &, vField & );
};

} // namespace Reo

#endif  // REO_EULERDC_HPP
