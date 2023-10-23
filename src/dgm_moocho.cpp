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

/** \file dgm_moocho.cpp
    \brief File containing the main driver for DGM Moocho via ModelEvaluator
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

#include "MoochoPack_MoochoThyraSolver.hpp"

// forward declarations

/// Manage command line inputs
void parse_args( DGM::ArgList &args, Table &params );

/// Printout the correct usage
void showUsage( const string& code );

/// The main DGM::ModelEvaluator driver program.
/** Manage command line inputs, create the parallel process(es) and
    construct the DGM::ModelEvaluator */
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
  DGM::Comm::Interupt();  // catch interupts
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

  // Try out Moocho
  using MoochoPack::MoochoSolver;
  using MoochoPack::MoochoThyraSolver;
  MoochoThyraSolver solver;

  // Set the model
  solver.setModel(model);

  // Solve the NLP
  cout << "DGM_Moocho: Calling solver.solve()" << endl;
  const MoochoSolver::ESolutionStatus solution_status = solver.solve();

  // Extract the final solution
  Teuchos::RCP<const Thyra::VectorBase<double> > p_final =
     solver.getFinalPoint().get_p(0);

  {
    // copy final solution back into DGM control datastructure
    Thyra::ConstDetachedSpmdVectorView<double> final_p(p_final);
    for (int i = 0; i < final_p.subDim(); ++i) {
      ocp.optimizer->control->phi[i] = final_p[i];
    }
  }

  // plot the file control distribution
  ocp.optimizer->control->plot(1,1);

#if DGM_MODELEVAL_VERBOSE >= 1
  lsPL->print(std::cout);
#endif

  //==========================================================================

  DGM::Comm::World->cout() << "Total run time:  " << cpu.stop() << endl;
#ifdef OPEN_MPI
#if !((OMPI_MAJOR_VERSION <= 1) && (OMPI_MINOR_VERSION <= 8) && \
    (OMP_RELEASE_VERSION <= 4))
  comm->cout()<<"Explicitly calling World::reset()"<<endl;
  DGM::Comm::World.reset();
#endif
#endif
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
