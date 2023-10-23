#ifndef REO_ADV_DIFF_STATE_HPP
#define REO_ADV_DIFF_STATE_HPP

/** \file Adv_Diff_State.hpp
    \brief Advection diffusion State declaration
    \author Scott Collis
*/

// local includes
#include "Comm.hpp"
#include "Adv_Diff.hpp"
#include "State.hpp"
#include "Control.hpp"

namespace Reo {

/// State wrapper for Adv_Diff Domain
class Adv_Diff_State : public Adv_Diff, public State  {

  dVector wk4;            ///< local workspace
  dVector wk5;            ///< local workspace
  dVector wk6;            ///< local workspace
  dVector wk7;            ///< local workspace

  dVector area;           ///< local storage for element areas

public:

  /// Constructor
  Adv_Diff_State( DGM::ArgList &args, const DGM::Comm::Ptr = DGM::Comm::World,
                  const int p_inc=0 );

  void residual( vField &, vField &, const bool source=true );
  void steady_residual( vField &, vField &, const bool source=true );

  Scalar estimate_error( const Ordinal npredict, Adjoint *adjoint,
                         dVector &error);

  Scalar estimate_error_steady(const Ordinal npredict, Adjoint *adjoint,
                               dVector &error);

  const Domain* domain() const { return this; }
  Domain* domain() { return this; }

#ifdef DGM_STATE_USE_DTK_TIMEINTEGRATE
  virtual void set_TimeInt( Ordinal=0 );
#endif

  /// TimeInt interface
  void prestep(vField &F, const Ordinal istep,
                          const Ordinal sstep, const Scalar time){
    control->set_data(istep,sstep);
  }

  /// TimeInt interface
  void poststep(vField &F,const Ordinal istep,
                          const Ordinal sstep, const Scalar time){
    store(F,istep,sstep);
  }

private:

  void local_diffusion( vField &, vField &, vField &);

};

} // namespace Reo

#endif  // REO_ADV_DIFF_STATE_HPP
