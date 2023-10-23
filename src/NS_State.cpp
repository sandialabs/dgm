/*=============================================================================
  Module:     NS_State Module

  Author:     Guoquan Chen and S. Scott Collis

  Copyright:  S. Scott Collis
              Department of Mechanical Engineering and Materials Science
              Rice University, MS 321
              Houston, TX 77005-1892
              (713) 348-3617
              collis@rice.edu
=============================================================================*/

/** \file  NS_State.cpp
    \brief State Navier-Stokes equations implementation. */

// system includes
#include <cassert>

// DGM includes
#include "TimeInt.hpp"

// Reo includes
#include "NS_State.hpp"

namespace Reo {

/// Constructor
NS_State::NS_State( DGM::ArgList &args, const DGM::Comm::Ptr comm_) :
  Navier_Stokes(args,comm_), State() {

  // allocate workspace
  wk3.resize(5*max(Lmax(),Qmax()));
  wk4.resize(5*max(Lmax(),Qmax()));

  // Need to check [gqchen]
  Ma = 0.5;             // Reference Ma number  (Why is this needed?) [SSC]
  Re = 1.0;             // To be consistent with the nondimension of the state
  mu = vis;             // dynamic viscosity
  lambda = -2.0/3.0*mu; // Stokes hypothesis

  // Pr from parent class Navier_Stokes

  // Conductivity coefficient K is defined to be consistent with the state and
  // adjoint formulations
  K = mu;

  // Print a warning since these values are hardwired
  comm->cout()<<"[NS_State] WARNING:  Using Ma="<<Ma<<", Re="<<Re
              <<",\n mu="<<mu<<", lambda="<<lambda<<",\n Pr="
              <<Pr<<", K="<<K<<std::endl;

  assert((int)params["inttype"]==TimeInt::RUNGE_KUTTA);
}

} // namespace Reo
