#ifndef REO_LINBURGERS_STATE_HPP
#define REO_LINBURGERS_STATE_HPP

/** \file  LinBurgers_State.hpp
    \brief State declaration for the linearized Burgers equation. */

// DGM includes
#include "Comm.hpp"
#include "State.hpp"
#include "Control.hpp"

// local includes
#include "LinBurgers.hpp"

namespace Reo {

/// Linearized Burgers State equation
class LinBurgers_State : public LinBurgers, public State {

 public:

  /// Constructor
  LinBurgers_State( DGM::ArgList &args, const State *base_ = NULL,
                    const DGM::Comm::Ptr comm_ = DGM::Comm::World )
    : LinBurgers(args,base_,comm_), State() {

    // initialize parameters
    int p = params["p"];  // polynomial order
    comm->cout() << "LinBurgers_State:  p = "<< p <<endl;

    zero_all_fields();
  }

  // State interface
  const Domain* domain() const { return this; }
  Domain* domain() { return this; }

  // double compute(const int, ControlPtr, const int=0);

  // TimeInt interface
  void prestep(vField &F, const Ordinal istep,
                          const Ordinal sstep, const Scalar time){
    // cout<<"LinBurgers_State:  Loaded Ubase "<<istep<<" "<<sstep<<endl;
    LinBurgers::prestep(F,istep,sstep,time);
    control->set_data(istep,sstep);
  }

  void poststep(vField &F,const Ordinal istep,
                          const Ordinal sstep, const Scalar time){
    LinBurgers::poststep(F,istep,sstep,time);
    store(F,istep,sstep);
  }

};

} // namespace Reo

#endif  // REO_LINBURGERS_STATE_HPP
