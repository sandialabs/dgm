#ifndef DGM_REMOVE_FOR_RELEASE

#ifndef REO_SHALLOW_STATE_HPP
#define REO_SHALLOW_STATE_HPP

/** \file  ShallowState.hpp
    \brief State class declaration for the 2d Shallow equations
    \author Vincent Mousseau
    \author S. Scott Collis
*/

// DGM includes
#include "Comm.hpp"
#include "State.hpp"
#include "Control.hpp"

// local includes
#include "Shallow.hpp"
#include "ShallowBC.hpp"

namespace Reo {

/// State wrapper for 2-d Shallow
class ShallowState : public Shallow, public State {

  dVector wk3;       ///< local workspace
  dVector wk4;       ///< local workspace

  dVector area;      ///< local storage for element areas

public:

  /// Constructor
  ShallowState(DGM::ArgList &args, const DGM::Comm::Ptr = DGM::Comm::World,
              const int p_inc=0);

  void residual( vField &, vField &, const bool source=true );
  void steady_residual( vField &, vField &, const bool source=true );

  Scalar estimate_error( const Ordinal npredict, Adjoint *adjoint,
                         dVector &error);

  Scalar estimate_error_steady(const Ordinal npredict, Adjoint *adjoint,
                               dVector &error);

  const Domain* domain() const { return this; }
  Domain* domain() { return this; }

  // TimeInt interface
  void prestep(vField &F, const Ordinal istep,
                          const Ordinal sstep, const Scalar time){
    control->set_data(istep,sstep);
  }

  void poststep(vField &F,const Ordinal istep,
                          const Ordinal sstep, const Scalar time){
    store(F,istep,sstep);
  }

};

} // namespace Reo

#endif  // REO_SHALLOW_STATE_HPP

#else // DGM_REMOVE_FOR_RELEASE
// This capability is under development.
#endif // DGM_REMOVE_FOR_RELEASE
