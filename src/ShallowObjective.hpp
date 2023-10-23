#ifndef DGM_REMOVE_FOR_RELEASE

#ifndef REO_SHALLOW_OBJECTIVE_HPP
#define REO_SHALLOW_OBJECTIVE_HPP

/** \file  ShallowObjective.hpp
    \brief Objective class declaration for the 2d Shallow equations
    \author Vincent Mousseau
    \author S. Scott Collis
*/

// system includes
#include <list>

// DGM includes
#include "Domain.hpp"
#include "State.hpp"
#include "Adjoint.hpp"
#include "Objective.hpp"
#include "Obs.hpp"

namespace Reo {

/// Objective for Shallow Domain
class ShallowObjective : public Objective {

 public:

  ShallowObjective(DGM::ArgList &args, State *state_, Adjoint *adjoint_,
                    const DGM::Comm::Ptr comm_ ) :
    Objective(args,state_,adjoint_,comm_) {

    comm->cout() << "Building ShallowObjective..." << std::endl;
  }
};

} // namespace Reo

#endif  // REO_SHALLOW_OBJECTIVE_HPP

#else // DGM_REMOVE_FOR_RELEASE
// This capability is under development.
#endif // DGM_REMOVE_FOR_RELEASE
