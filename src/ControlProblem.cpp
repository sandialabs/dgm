/** \file  ControlProblem.cpp
    \brief Feedback control problem implementation
    \todo This should really be the Reo_ControlProblem.cpp
    \author Scott Collis
*/

// DGM includes
#include "ControlProblem.hpp"
#include "TimeInt.hpp"
#include "Domain.hpp"
#include "ArgList.hpp"

// Reo includes
#include "Reo.hpp"
#include "Adv_Diff.hpp"
#include "Euler.hpp"
#include "Navier_Stokes.hpp"
#include "Turbulence.hpp"
#include "Wave.hpp"
#include "Burgers.hpp"
#include "LinEuler_quasi.hpp"
#include "LinEuler_prim.hpp"
#include "Euler3d.hpp"
#include "Navier_Stokes3d.hpp"
#include "iEuler.hpp"
#include "iNS.hpp"
#ifdef DGM_USE_MD_COUPLE
#include "Couple.hpp"
#endif
#include "Adv_Diff_State.hpp"
#include "Adv_Diff_Adjoint.hpp"
#include "Adv_Diff_Control.hpp"

namespace DGM {

/// Constructor for feedback control problems
ControlProblem::ControlProblem( DGM::ArgList &args, Table &table_in,
                                const DGM::Comm::Ptr comm_in )
  : Problem( args, table_in, comm_in ) {

  comm->cout() << "DGM::ControlProblem(...)" << endl;

  // set default values
  params["eqntype"] = Reo::EULER;       // default to Reo::Euler equations
  params["inttype"] = TimeInt::TVD_RK;  // default to TVD-RK

  parse_args( args );

  int eqntype = params["eqntype"];

  switch(eqntype) {
  case Reo::ADV_DIFF: {
    // make control problem
    state.reset( new Reo::Adv_Diff_State(args, comm) );
    adjoint.reset( new Reo::Adv_Diff_Adjoint(args, state.get(), comm) );
    control.reset( new Reo::Adv_Diff_Control(args, state.get(), comm) );
    objective.reset( new Reo::Adv_Diff_Objective(args, state.get(),
                                                 adjoint.get(), comm) );
    controller.reset( new Controller( state, control, comm ) );
    // make forward problem
    Omega = new Reo::Adv_Diff( args, comm );
    break; }
  case Reo::EULER: {
    Omega = new Reo::Euler( args, comm );
    break; }
  case Reo::NAVIER_STOKES: {
    Omega = new Reo::Navier_Stokes( args, comm );
    break; }
  case Reo::TURBULENCE: {
    Omega = new Reo::Turbulence( args, comm );
    break; }
  case Reo::WAVE: {
    Omega = new Reo::Wave( args, comm );
    break; }
  case Reo::BURGERS: {
    Omega = new Reo::Burgers( args, comm );
    break; }
  case Reo::IEULER: {
    Omega = new Reo::iEuler( args, comm );
    break; }
  case Reo::INS: {
    Omega = new Reo::iNS( args, comm );
    break; }
  case Reo::LINEULER_QUASI: {
    Omega = new Reo::LinEuler_quasi( args, comm );
    break; }
  case Reo::LINEULER_PRIM: {
    Omega = new Reo::LinEuler_prim( args, comm );
    break; }
  case Reo::EULER3D: {
    Omega = new Reo::Euler3d( args, comm );
    break; }
  case Reo::NAVIER_STOKES3D: {
    Omega = new Reo::Navier_Stokes3d( args, comm );
    break; }
#ifdef DGM_USE_MD_COUPLE
  case Reo::COUPLE: {
    Omega = new Reo::Couple( args, comm );
    break; }
#endif
  default:
    comm->cerr() << "ControlProblem:  Unsupported equation type: "<<eqntype << endl;
    comm->exit(DGM::FAILURE);
  }

  // set the material properties
  Omega->set_material();

  // final check of argument list
  if ( params.defined("showUsage") ) comm->exit(0);
#ifdef DGM_REMOVE_ARGUMENTS
  if ( args.size() != 2 ) {
    comm->cout() << "WARNING:  " << args.size() << " unused arguments:  ";
    print( args );
  }
#endif

}

/// Solve method for feedback control problem
int ControlProblem::solve() {
  comm->cout()<<"Begin feedback control simulation..."<<endl;
  controller->advance();
  return 0;
}

} // namespace DGM
