/** \file ReoOptProblem.cpp
    \brief DGM and Reo optimization problem implementation
    \author S. Collis, J. Young and J. Overfelt
*/

// DGM includes
#include "OptProblem.hpp"
#include "TimeInt.hpp"
#include "Domain.hpp"
#include "ArgList.hpp"

// Reo includes
#include "Reo.hpp"
#include "ReoOptProblem.hpp"

#ifndef DGM_REMOVE_FOR_RELEASE
#include "Shallow.hpp"
#include "ShallowState.hpp"
#include "ShallowAdjoint.hpp"
#include "ShallowControl.hpp"
#endif // DGM_REMOVE_FOR_RELEASE

#include "Adv_Diff.hpp"
#include "Euler.hpp"
#include "Navier_Stokes.hpp"
#include "Turbulence.hpp"
#include "Wave.hpp"
#include "Burgers.hpp"
#include "LinBurgers.hpp"
#include "LinEuler_quasi.hpp"
#include "LinEuler_prim.hpp"
#include "Euler3d.hpp"
#include "Navier_Stokes3d.hpp"

#include "Adv_Diff_State.hpp"
#include "Adv_Diff_Adjoint.hpp"
#include "Adv_Diff_Control.hpp"

#include "Burgers_State.hpp"
#include "Burgers_Adjoint.hpp"
#include "Burgers_Control.hpp"

#include "LinBurgers_State.hpp"
#include "LinBurgers_Adjoint.hpp"

#include "Euler_State.hpp"
#include "Euler_Adjoint.hpp"
#include "Euler_Control.hpp"

#include "NS_State.hpp"
#include "NS_Adjoint.hpp"
#include "NS_Control.hpp"

// DGM Optimizers
#include "BlackBox.hpp"
#include "NonlinearCG.hpp"
#include "ErrorEst.hpp"
#ifdef DGM_USE_ROL 
#include "ROL_Optimizer.hpp"
#endif

namespace Reo {

/// Reo Optimization Problem
/** Optimization Framework based on Discontinuous Galerkin Solver Problem
    framework for optimal control, it provides the interface for the problem
    formulation (Control, state/adjoint solver).
*/
OptProblem::OptProblem( ArgList &args, const Table &table,
                        const DGM::Comm::Ptr comm_ )
  : DGM::OptProblem(args,table,comm_) {

  // set default values
  params["eqntype"] = Reo::EULER;             // default to Euler
  params["p_inc"]   = 0;                      // increment in p-order
  params["inttype"] = TimeInt::RUNGE_KUTTA;   // default to RK-4
  params["Nouter"]  = 1;                      // default to ONE time window
  params["use_aux"] = 0;                      // default to no aux problem
  params["opttype"] = NONLINEARCG;            // default is nonlinear CG
  params["plot_grad"] = plot_grad;            // plot the gradient

  parse_args( args );

  const int eqntype = params["eqntype"];
  const int opttype = (int)params["opttype"];
  const int p_inc = params["p_inc"];
  plot_grad = params["plot_grad"];
  
  // cout << "Reo::OptProblem() params = \n" << params << endl;

  // Note: you could also query the optimizer at this point to tell you if
  // you need the auxiliary problem setup

  switch(eqntype) {
  case Reo::ADV_DIFF: {
    state = new Reo::Adv_Diff_State(args, comm);
    adjoint = new Reo::Adv_Diff_Adjoint(args, state, comm, p_inc);
    control.reset( new Reo::Adv_Diff_Control(args, state, comm) );
    objective = new Reo::Adv_Diff_Objective(args, state, adjoint, comm);
    break;
  }
  case Reo::BURGERS: {
    state = new Reo::Burgers_State(args, comm);
    adjoint = new Reo::Burgers_Adjoint(args, state, comm);
    control.reset( new Reo::Burgers_Control(args, state, comm) );
    objective = new Reo::Burgers_Objective(args, state, adjoint, comm);
    break;
  }
  case Reo::LINBURGERS:
  case Reo::WAVE:
  case Reo::LINEULER_QUASI:
  case Reo::LINEULER_PRIM:
  case Reo::TURBULENCE:
  case Reo::EULER3D:
  case Reo::NAVIER_STOKES3D: {
    comm->cerr()<<"OptProblem: control type is not implemented yet."<<endl;
    comm->exit(DGM::FAILURE);
    break;
  }
#ifndef DGM_REMOVE_FOR_RELEASE
  case Reo::SHALLOW:{
    state = new Reo::ShallowState(args, comm);
    adjoint = new Reo::ShallowAdjoint(args, state, comm);
    control.reset( new Reo::ShallowControl(args, state, comm) );
    objective = new Reo::ShallowObjective(args, state, adjoint, comm);
    break;
  }
#endif // DGM_REMOVE_FOR_RELEASE
  case Reo::EULER:{
    state = new Reo::Euler_State(args, comm);
    adjoint = new Reo::Euler_Adjoint(args, state, comm);
    control.reset( new Reo::Euler_Control(args, state, comm) );
    objective = new Reo::Euler_Objective(args, state, adjoint, comm);
    break;
  }
  case Reo::NAVIER_STOKES:{
    state = new Reo::NS_State(args, comm);
    adjoint = new Reo::NS_Adjoint(args, state, comm);
    control.reset( new Reo::NS_Control(args, state, comm) );
    objective = new Reo::NS_Objective(args, state, adjoint, comm);
    break;
  }
  default:
    comm->cerr()<<"OptProblem:  Unsupported equation type = "<<eqntype<<endl;
    comm->exit(DGM::FAILURE);
  }

#ifdef REO_OPT_PROBLEM_DEBUG
  state->initialize();
  control->initialize();
  state->set_initial_condition();
  double total_j = state->compute(control->get_npredict(), control, 1);
  cout << total_j << endl;
  exit(0);
#endif

  // Construct the appropriate optimal control problem interface
  switch(opttype) {
  case BLACKBOX:
    optimizer = new DGM::BlackBox( state, adjoint, control, comm );
    break;
  case NONLINEARCG:
    optimizer = new DGM::NonlinearCG( state, adjoint, control,
                                      preconditioner, comm );
    break;
  case LBFGS:
    //optimizer = new DGM::LBFGS( state, adjoint, control, comm );
    comm->error("LBFGS is not currently supported");
    break;
  case ERROREST:
    optimizer = new DGM::ErrorEst( state, adjoint, control, comm );
    break;
#ifdef DGM_USE_ROL
  case ROL: {
    optimizer = new DGM::ROL_Optimizer( state, adjoint, control,
                                        preconditioner, comm );
    break;
  }
#endif
  default:
    comm->cout()<< " Unsupported optimization problem type: "<<opttype<<endl;
    comm->error("Unsupported optimization problem type");
  }

#ifdef DGM_STATE_USE_DTK_TIMEINTEGRATE
  // setup the time integration
  state->setTimeIntegrate(control,objective);
  //adjoint->setTimeIntegrate(control,objective);
#endif

  // Final check of argument list
  if ( params.defined("showUsage") ) exit(0);
}

/// Reo Linearized optimal control problem
OptProblem::OptProblem( const OptProblem *base, ArgList &args,
                        const Table &table, const DGM::Comm::Ptr comm_ )
  : DGM::OptProblem(base,args,table,comm_) {

  args.back() = args.back()+".lin";           // change to linearized extension

  // set default values
  params["eqntype"] = Reo::EULER;             // default to Euler
  params["inttype"] = TimeInt::RUNGE_KUTTA;   // default to RK-4
  params["Nouter"]  = 1;                      // default to ONE time window
  params["opttype"] = NONLINEARCG;            // default is nonlinear CG
  params["plot_grad"] = plot_grad;            // plot the gradient

  // comm->cout() << "Before parsing\n" << params << endl;
    
  parse_args( args );

  // comm->cout() << "After parsing\n" << params << endl;

  const int eqntype = (int)params["eqntype"] + 100;  // linearized problem
  const int opttype = (int)params["opttype"];
  plot_grad = params["plot_grad"];

  switch(eqntype) {
  case Reo::LINADV_DIFF: {
    state = new Reo::Adv_Diff_State(args, comm);
    adjoint = new Reo::Adv_Diff_Adjoint(args, state, comm);
    control.reset( new Reo::Adv_Diff_Control(args, state, comm) );
    objective = new Reo::Adv_Diff_Objective(args, state, adjoint, comm);
    break;
  }
  case Reo::LINBURGERS: {
    state = new Reo::LinBurgers_State(args, base->state, comm);
    adjoint = new Reo::LinBurgers_Adjoint(args, state, base->state,
                                          base->adjoint, comm);
    control.reset( new Reo::Burgers_Control(args, state, comm) );
    objective = new Reo::Burgers_Objective(args, state, adjoint, comm);
    break;
  }
  default:
    comm->error("OptProblem: Unsupported linearized equation type: "+
                 asString(eqntype));
  }

  // Construct the appropriate optimal control problem interface
  switch(opttype) {
  case BLACKBOX:
    optimizer = new DGM::BlackBox( state, adjoint, control, comm );
    break;
  case NONLINEARCG:
    optimizer = new DGM::NonlinearCG( state, adjoint, control,
                                      preconditioner, comm );
    break;
  case LBFGS:
    //optimizer = new DGM::LBFGS( state, adjoint, control, comm );
    comm->error("LBFGS is not currently supported");
    break;
#ifdef DGM_USE_ROL
  case ROL: {
    optimizer = new DGM::ROL_Optimizer( base->state, base->adjoint,
                                        base->control, state, adjoint,
                                        preconditioner, comm );
    break;
  }
#endif
  default:
    comm->cout()<< " Unsupported optimization problem type:"<<opttype<<endl;
    comm->error("Unsupported optimization problem type");
  }

  // Final check of argument list
  if ( params.defined("showUsage") ) exit(0);
}

void OptProblem::parse_args( ArgList &args ) {
  string name, value;

  // get basic information from argument list
  code = args.front();
  if (args.size() < 2) {
    showUsage(code);
    exit(1);
  }
  root = args.back();
  params.read(root+".inp");

  list< DGM::ArgList::iterator > li;
  for ( DGM::ArgList::iterator a = args.begin(); a != args.end(); a++ ) {
    if ( (*a)[0] == '-' ) {
      name = *a;
      if (name == "-help") {
        params["showUsage"] = 1;
        showUsage(code);
      } else if (name == "-p_inc") {
        li.push_back(a);
        value = *(++a);
        li.push_back(a);
        params["p_inc"] = atoi(value.c_str());
      } else if (name == "-plot_grad") {
        li.push_back(a);
        li.push_back(a);
        params["plot_grad"] = true;
      } else if (name == "-opttype") {
        li.push_back(a);
        value = *(++a);
        li.push_back(a);
        params["opttype"] = atoi(value.c_str());
      }
    }
  }
#ifdef DGM_REMOVE_ARGUMENTS
  // remove tagged arguments
  for ( list< DGM::ArgList::iterator >::iterator a=li.begin();
        a!=li.end(); a++) args.erase(*a);
#endif
}

void OptProblem::showUsage(const string& code) const {
  comm->cerr()
    << "Reo OptProblem Class Options \n"
    << "---------------------------------------------------------------\n"
    << "-p_inc    " << '\t' << "Increment in p for Adjoint problem     \n"
    << "-plot_grad" << '\t' << "Plot the gradient of the control       \n"
    << "-opttype #" << '\t' << "Type of optimizer to use (see docs)    \n"
    << "---------------------------------------------------------------\n";
}

int OptProblem::solve() {
  const int Nouter =  params["Nouter"];              // number of time windows
  for (int outer=0; outer < Nouter; outer++) {       // Time window loop
    comm->cout()<<"Begin optimal control iteration..."<<endl;
    optimizer->optimize();
    optimizer->advance(outer);
  }
  return 0;
}

} // namespace Reo
