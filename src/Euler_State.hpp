#ifndef REO_EULER_STATE_HPP
#define REO_EULER_STATE_HPP

/** \file  Euler_State.hpp
    \brief State class declaration for the 2d Euler equations
    \author Scott Collis
*/

// DGM includes
#include "Comm.hpp"
#include "State.hpp"
#include "Control.hpp"

// local includes
#include "Euler.hpp"
#include "EulerBC.hpp"

namespace Reo {

/// State wrapper for 2-d Euler
class Euler_State : public Euler, public State {

  dVector wk3;       ///< local workspace
  dVector wk4;       ///< local workspace

  dVector area;      ///< local storage for element areas

public:

  /// Constructor
  Euler_State(DGM::ArgList &args, const DGM::Comm::Ptr = DGM::Comm::World,
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

#endif  // REO_EULER_STATE_HPP
