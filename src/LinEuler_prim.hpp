#ifndef REO_LINEULER_PRIM_HPP
#define REO_LINEULER_PRIM_HPP

/** \file  LinEuler_prim.hpp
    \brief Linearized Euler equations in primative variables */

// DGM includes
#include "Comm.hpp"

// Reo includes
#include "Euler.hpp"

namespace Reo {

/// Linearized Euler equations in primative variables
/** The whole solver is based on the primitive form with the assumption that
    the mean flow is steady
    \f[ U = [\rho, p, u, v ] \f]
    A similar form can be refered in  Harold L. Atkins's paper:
    AIAA Journal, Vol.36 No.5 ,1997 pp. 775-782 and AIAA 99-3309

    Implementation Notes: Several parts need to be changed in future, currently
    only works for no/uniform mean flow
      - set_mean()          : read mean(base) flow information
      - set_mean_state_bc() : set man flow BC (maybe unnecessary)
      - set_state_bc() : set flow state BC, currently it is hardwired for
        plane-wave case
      - compute_vorticity() : needs to be changed [gqchen]
*/
class LinEuler_prim : public Euler {

  dVector wk3, wk4;

 public:

  Scalar Ma;                      // the mean flow reference Mach number
  Scalar gamma;                   // ratio of specific heats

  vField Utmp;                    // Temporary field for mean source
  vField Um;                      // Mean flow field

  // constructor
  LinEuler_prim( DGM::ArgList &args, const DGM::Comm::Ptr = DGM::Comm::World );

  // override virtual Domain methods
  void time_derivative( vField &, vField & );

  void zero_all_fields();
  void set_ic( vField &, string=".ic" );

  void enforce_bc(vField &);
  void enforce_flux_bc(vField &);

  // override public Euler methods
  void convection( vField &, vField & );

 private:

  /// Supported convective numerical fluxes
  enum flux_type {
    Roe,
    vanLeer,
    StegerWarming,
    LaxFriedrichs
  };

  void convective_flux( vField &, vField & );
  void compute_vorticity();

  void enforce_mean_state_bc(vField &);
  void meansource(vField &, vField &, vField &); // source from mean flow
  void set_mean(vField &);
};

} // namespace Reo

#endif  // REO_LINEULER_PRIM_HPP
