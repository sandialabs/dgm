#ifndef REO_ADV_DIFF_OBJECTIVE_HPP
#define REO_ADV_DIFF_OBJECTIVE_HPP

/** \file Adv_Diff_Objective.hpp
    \brief Advection diffusion Objective declaration and implementation
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

/// Objective for Adv_Diff Domain
class Adv_Diff_Objective : public DGM::Objective {
public:
  /// Constructor
  Adv_Diff_Objective(DGM::ArgList &args, State *state_, Adjoint *adjoint_,
                     const DGM::Comm::Ptr comm_ ) :
    Objective(args,state_,adjoint_,comm_) {
    comm->cout() << "Building Adv_Diff_Objective..." << std::endl;
  }
};

} // namespace Reo

#endif  // REO_ADV_DIFF_OBJECTIVE_HPP
