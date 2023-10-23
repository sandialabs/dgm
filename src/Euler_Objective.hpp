#ifndef REO_EULER_OBJECTIVE_HPP
#define REO_EULER_OBJECTIVE_HPP

/** \file  Euler_Objective.hpp
    \brief Objective class declaration for the 2d Euler equations
    \author Scott Collis
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

/// Objective for Euler Domain
class Euler_Objective : public Objective {

 public:

  Euler_Objective(DGM::ArgList &args, State *state_, Adjoint *adjoint_,
                  const DGM::Comm::Ptr comm_ ) :
    Objective(args,state_,adjoint_,comm_) {

    comm->cout() << "Building Euler_Objective..." << std::endl;
  }

};

} // namespace Reo

#endif  // REO_EULER_OBJECTIVE_HPP
