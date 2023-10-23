#ifndef REO_TURBULENCE_HPP
#define REO_TURBULENCE_HPP

/** \file Turbulence.hpp
    \brief Declarations for sub-grid scale models
    \author Scott Collis
*/

// DGM includes
#include "Domain.hpp"

// Reo includes
#include "Euler.hpp"
#include "Navier_Stokes.hpp"

namespace Reo {

/// Navier-Stokes with Turbulence models
class Turbulence : public Navier_Stokes {
 public:
  Scalar mu_tau;                  // Eddy viscosity

  // constructor
  Turbulence( DGM::ArgList &args, const DGM::Comm::Ptr = DGM::Comm::World );

  // void diffusion( vField &, vField &, vField & );

  void get_viscosity( dVector & );

  // void get_tot_viscosity( const vField &, dVector &, const int );
  // Scalar get_eddy_viscosity( const int );
};

} // namespace Reo

#endif  // REO_TURBULENCE_HPP
