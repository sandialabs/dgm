#ifndef REO_BURGERS_OBJECTIVE_HPP
#define REO_BURGERS_OBJECTIVE_HPP

/** \file Burgers_Objective.hpp
    \brief Burgers Objective function declaration and implementation
    \author Scott Collis
*/

// system includes
#include <list>

// local includes
#include "Objective.hpp"
#include "State.hpp"
#include "Adjoint.hpp"
#include "Domain.hpp"
#include "Obs.hpp"

namespace Reo {

/// Objective for Burgers Domain
class Burgers_Objective : public Objective {

 public:

  /// Constructor
  Burgers_Objective(DGM::ArgList &args, State *state_, Adjoint *adjoint_,
                    const DGM::Comm::Ptr comm_ ) :
    Objective(args,state_,adjoint_,comm_) {
    comm->cout() << "Building Burgers_Objective..." << std::endl;
  }

};

} // namespace Reo

#endif  // REO_BURGERS_OBJECTIVE_HPP
