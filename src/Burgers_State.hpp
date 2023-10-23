#ifndef REO_BURGERS_STATE_HPP
#define REO_BURGERS_STATE_HPP

/** \file Burgers_State.hpp
    \brief Burgers State equation solver
    \author Scott Collis
*/

// DGM includes
#include "Comm.hpp"
#include "State.hpp"
#include "Control.hpp"

// local includes
#include "Burgers.hpp"

namespace Reo {

/// State wrapper for Burgers
class Burgers_State : public Burgers, public State {

 public:

  /// Constructor
  Burgers_State( DGM::ArgList &args,
                 const DGM::Comm::Ptr comm_ = DGM::Comm::World ) :
    Burgers(args,comm_), State() {

    // initialize parameters
    int p = params["p"];
    comm->cout() << "Burgers_State:  p = "<< p <<endl;

    zero_all_fields();
  }

  const Domain* domain() const { return this; }
  Domain* domain() { return this; }

  // Implements TimeInt interface

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

#endif  // REO_BURGERS_STATE_HPP
