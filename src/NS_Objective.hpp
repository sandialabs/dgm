#ifndef REO_NS_OBJECTIVE_HPP
#define REO_NS_OBJECTIVE_HPP

/** \file  NS_Objective.hpp
    \brief Navier-Stokes Objective class. */

// system includes
#include <list>

// DGM includes
#include "Domain.hpp"
#include "State.hpp"
#include "Adjoint.hpp"
#include "Objective.hpp"
#include "Obs.hpp"

namespace Reo {

/// Objective for Navier_Stokes Domain
class NS_Objective : public Objective {

 public:

  /// Constructor
  NS_Objective(DGM::ArgList &args, State *state_, Adjoint *adjoint_,
               const DGM::Comm::Ptr comm_ ) :
    Objective(args,state_,adjoint_,comm_) {

    comm->cout() << "Building NS_Objective..." << std::endl;
  }

};

} // namespace Reo

#endif  // REO_NS_OBJECTIVE_HPP
