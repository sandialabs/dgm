#ifndef DGM_REMOVE_FOR_RELEASE

#ifndef REO_SHALLOW_ADJOINT_HPP
#define REO_SHALLOW_ADJOINT_HPP

/** \file  ShallowAdjoint.hpp
    \brief Adjoint for the 2d Shallow equations
    \author Vincent Mousseau
    \author S. Scott Collis
*/

// system includes
#include <vector>

// DGM includes
#include "Comm.hpp"
#include "Adjoint.hpp"

// Reo includes
#include "ShallowControl.hpp"
#include "ShallowState.hpp"
#include "ShallowObjective.hpp"

namespace Reo {

/// Continuous Adjoint of the 2-d Shallow Equations
class ShallowAdjoint : public Domain, public Adjoint {

  dVector wk1;                 ///< local workspace
  dVector wk2;                 ///< local workspace

  const ShallowState *state;   ///< Pointer to my State

  vField Utmp;                 ///< Temporary vField

 public:

  // Source term declarations
  class PhiTracking;

  /// Constructor
  ShallowAdjoint(DGM::ArgList &, const State*,
                 const DGM::Comm::Ptr = DGM::Comm::World,
                 const int p_inc=0 );

  // override virtual Domain methods
  void zero_all_fields();

  void set_TimeInt( Ordinal=0 );

  // provide TimeInt interface
  void prestep( vField&, const Ordinal, const Ordinal, const Scalar );
  void poststep( vField&, const Ordinal, const Ordinal, const Scalar );
  void time_derivative( vField &, vField & );

  void setup_BCdb( );

  void setup_Sourcedb( );
  Source::Ptr make_Source( ifstream &, string & );
  void add_source(const vField &, vField &);

  void enforce_bc(vField &);
  void enforce_flux_bc(vField &);

  // override Adjoint methods
  void set_end_condition();
  void set_end_condition(const dVector &, const Scalar=0.0, const Ordinal=0);
  void computeGrad(vField&, vField&, Ordinal, Ordinal);

  const Domain* domain() const {return this;}
  Domain* domain() {return this;}

  void set_t_step(){
    t = state->t;
    step = state->step;
  }

  /// supported numerical fluxes
  enum flux_type {
    Roe,                       ///< Roe flux
    vanLeer,                   ///< van Leer flux
    StegerWarming,             ///< Steger-Warming flux
    LaxFriedrichs              ///< Lax-Friedrichs flux
  };

  void set_ic(vField &, string=".ic");

 private:

  /// \name local methods
  //@{
  void convection( vField &, vField & );
  void convective_flux( vField &, vField & );

  /// source from inviscid flux
  void conv_source(vField &, vField &);
  //@}
};

} // namespace Reo

#endif  //  REO_SHALLOW_ADJOINT_HPP

#else // DGM_REMOVE_FOR_RELEASE
// This capability is under development.
#endif // DGM_REMOVE_FOR_RELEASE
