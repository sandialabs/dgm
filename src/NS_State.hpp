#ifndef REO_NS_STATE_HPP
#define REO_NS_STATE_HPP

/** \file  NS_State.hpp
    \brief State Navier-Stokes equations declaration */

// DGM includes
#include "Comm.hpp"
#include "State.hpp"
#include "Control.hpp"

// Reo includes
#include "Navier_Stokes.hpp"

namespace Reo {

/// State wrapper for Navier--Stokes
/**
   Things must be done
   \todo Generalize BC implementation for NS_State

   \note Do we really need to treat STATE B.C. different in convection()
   and diffusion()? If this is the case, we have to do it similarly for its
   adjoint (i.e. adjoint::convection() and adjoint::diffusion())
   Dr. Collis's suggestion: use the two dbBC, each of them does it
   different when called.

   \note A better design for NS_Adjoint might be to derive from Euler_Adjoint
*/
class NS_State : public Navier_Stokes, public State {

  dVector wk3;    ///< local workspace
  dVector wk4;    ///< local worksapce

public:

  // some reference physics parameter, the formulation for the solver
  // (governing equation) is from old CNS2D [gqchen]    
  Scalar Ma;      ///< Mach number
  Scalar Re;      ///< Reynolds number
  Scalar mu;      ///< Viscosity
  Scalar lambda;  ///< viscosity of the second kind
  Scalar K;       ///< thermal conductivity
  // Scalar Pr;   ///< Prandtl number

public:
  /// Constructor
  NS_State(DGM::ArgList &args, const DGM::Comm::Ptr = DGM::Comm::World );

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

#endif  // REO_NS_STATE_HPP
