/*=============================================================================
  Title:      Dakota via Model Evaluator Discontinuous Galerkin Solver

  Author:     S. Scott Collis
              Scalable Algorithms
              Sandia National Laboratories
              Albuquerque, NM 87175-1320
              (505) 284-1123
              sscoll@sandia.gov

  Copyright:  Sandia National Laboratories
=============================================================================*/

/** \file dgm_trikota.cpp
    \brief File containing the main driver for DGM Dakota via ModelEvaluator
*/

// system libraries
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <list>
using namespace std;

// local includes
#ifdef DGM_PARALLEL
#include "MpiComm.hpp"
#else
#include "SerialComm.hpp"
#endif
#include "Stopwatch.hpp"
using CMC::Stopwatch;
#include "ArgList.hpp"
#include "OptProblem.hpp"
#include "ModelEval.hpp"
using namespace DGM;

// Trilinos includes
#include "Thyra_ModelEvaluatorHelpers.hpp"
#include "Thyra_VectorStdOps.hpp"
#include "Thyra_DefaultSpmdVectorSpace.hpp"
#include "Thyra_DetachedSpmdVectorView.hpp"

#include "TriKota_Driver.hpp"
#include "TriKota_ThyraDirectApplicInterface.hpp"

// forward declarations

/// Manage command line inputs
void parse_args( DGM::ArgList &args, Table &params );

/// Printout the correct usage
void showUsage( const string& code );

/// The main DGM::ModelEvaluator driver program.
/** Manage command line inputs, create the parallel process(es) and
    construct the DGM::ModelEvaluator. */
int main(int argc, char *argv[]) {

  // use a bunch of Trilinos stuff to prevent carpal-tunnel syndrome
  using Teuchos::as;
  using Teuchos::null;
  using Teuchos::RCP;
  using Teuchos::Ptr;
  using Teuchos::rcpFromRef;
  using Teuchos::rcp_dynamic_cast;
  using Teuchos::ArrayView;
  using Teuchos::outArg;
  using Teuchos::ParameterList;
  using Teuchos::parameterList;
  using Teuchos::ScalarTraits;
  using Teuchos::FancyOStream;
  using Thyra::createMember;
  typedef Thyra::Ordinal Ordinal;
  using Thyra::VectorSpaceBase;
  using Thyra::VectorBase;
  typedef ScalarTraits<double> ST;

#ifdef DGM_PARALLEL
  DGM::Comm::World.reset( new DGM::MpiComm( &argc, &argv ) );
#else
  DGM::Comm::World.reset( new DGM::SerialComm() );
  DGM::Comm::Interupt();
#endif

  ArgList args( &argc, &argv );
  Table params;
  parse_args( args, params );

  // make a dgm optimal control problem
  DGM::Comm::World->cout()
    << "================================================================\n"
    << "Making dgm_ocp...\n"
    << "================================================================\n";
  Reo::OptProblem ocp( args, params, DGM::Comm::World );

  Stopwatch cpu;
  cpu.start();

  //==========================================================================

  Teuchos::RCP<DGM::ModelEval> model(new DGM::ModelEval( &ocp ));

  Teuchos::RCP<Thyra::VectorBase<double> > p_init =
    Thyra::createMember<double>(model->get_p_space(0));

  // Try out TriKota

  TriKota::Driver dakota;

  RCP<Thyra::ModelEvaluatorDefaultBase<double> > baseModel =
    rcp_dynamic_cast<Thyra::ModelEvaluatorDefaultBase<double> >(model);
  if (model==Teuchos::null)
    std::cout << "dgm_trikota Error: model is null" << std::endl;
  if (baseModel==Teuchos::null)
    std::cout << "dgm_trikota Error: baseModel is null" << std::endl;

  // Construct a concrete Dakota interface from a ModelEval
  Teuchos::RCP<TriKota::ThyraDirectApplicInterface> trikota_interface =
     Teuchos::rcp(new TriKota::ThyraDirectApplicInterface
             (dakota.getProblemDescDB(), baseModel), false);

  dakota.run(trikota_interface.get());

  Dakota::RealVector finalValues =
    dakota.getFinalSolution().all_continuous_variables();

  // Broadcast array of final values to all procs
  int length = finalValues.length();
  DGM::Comm::World->Broadcast(&length, 1, 0);
  if (DGM::Comm::World->MyPID() != 0) finalValues.size(length);
  DGM::Comm::World->Broadcast(&finalValues[0], length, 0);

  {
    // Scatter final solution into parallel datastructure
    {
      Thyra::DetachedVectorView<double> global_p(p_init);
      //for (int i = 0; i < global_p.subDim(); ++i) {
      for (int i = 0; i < finalValues.length(); ++i) {
        global_p[i] = finalValues[i];
      }
    } // Scatter into p_init occurs here as global_p destructs

    // Parallel copy back into DGM control datastructure
    Thyra::DetachedSpmdVectorView<double> my_p(p_init);
    for (int i = 0; i < my_p.subDim(); ++i) {
      ocp.optimizer->control->phi[i] = my_p[i];
    }
  }

  // plot the file control distribution
  ocp.optimizer->control->plot(1,DGM::Comm::World->MyPID());
  //ocp.optimizer->control->plot(1,1);

#if DGM_MODELEVAL_VERBOSE >= 1
  lsPL->print(std::cout);
#endif

  //==========================================================================

  DGM::Comm::World->cout() << "Total run time:  " << cpu.stop() << endl;

  return DGM::SUCCESS;
}

/** Creates a parameter Table of the input arguments. */
void parse_args( DGM::ArgList &args, Table &params ) {
  string name, value;
  list< DGM::ArgList::iterator > li;
  for ( DGM::ArgList::iterator a = args.begin(); a != args.end(); a++ ) {
    if ( (*a)[0] == '-' ) {
      name = *a;
      if (name == "-help") {
        params["showUsage"] = 1;
        showUsage("dgm");
      }
    }
  }
  // remove tagged arguments
  for ( list< DGM::ArgList::iterator >::iterator a=li.begin();
        a!=li.end(); a++) args.erase(*a);

  // make sure that enough arguments remain
  if (args.size() < 2) {
    showUsage("dgm");
    DGM::Comm::World->exit(DGM::FAILURE);
  }
}

/** If there is an error in the input argument list, this routine prints the
    correct usage information. */
void showUsage(const string& code) {
  cerr << "================================================================\n"
       << "Discontinuous Galerkin ModelEvaluator Solver\n"
       << "================================================================\n"
       << "Usage:  \t" << code << " [Options] run_name \n"
       << "----------------------------------------------------------------\n"
       << "Options: " << '\t' << "Description\n"
       << "================================================================\n"
       << "-help    " << '\t' << "Detailed help\n"
       << "----------------------------------------------------------------\n";
}
