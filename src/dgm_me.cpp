/*=============================================================================
  Title:      Model Evaluator Discontinuous Galerkin Solver

  Author:     S. Scott Collis
              Scalable Algorithms
              Sandia National Laboratories
              Albuquerque, NM 87175-1320
              (505) 284-1123
              sscoll@sandia.gov

  Copyright:  Sandia National Laboratories
=============================================================================*/

/** \file dgm_me.cpp
    \brief File containing the main driver for the DGM Model Evaluator. */

// system libraries
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <list>
using namespace std;

// CMC includes
#include "Stopwatch.hpp"
using CMC::Stopwatch;

// DGM includes
#ifdef DGM_PARALLEL
#include "MpiComm.hpp"
#else
#include "SerialComm.hpp"
#endif
#include "ArgList.hpp"
#include "OptProblem.hpp"
#include "ModelEval.hpp"
#include "BlackBox.hpp"
using namespace DGM;

// Trilinos includes
#include "Thyra_ModelEvaluatorHelpers.hpp"
#include "Thyra_VectorStdOps.hpp"
#include "Thyra_DefaultSpmdVectorSpace.hpp"
#include "Thyra_DetachedSpmdVectorView.hpp"
#include "OptiPack_NonlinearCG.hpp"
#include "GlobiPack_BrentsLineSearch.hpp"

// forward declarations

/// Manage command line inputs
void parse_args( DGM::ArgList &args, Table &params );

/// Printout the correct usage
void showUsage( const string& code );

/// The main DGM::ModelEvaluator driver program.
/** Manage command line inputs, create the parallel process(es) and
    construct the DGM::ModelEvaluator */
int main(int argc, char *argv[]) {
  try {
#ifndef DGM_USE_EPETRA
    throw DGM::exception("dgm_me.exe requires Trilinos");
#else
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
    using GlobiPack::BrentsLineSearch;
    using GlobiPack::brentsLineSearch;
    using OptiPack::NonlinearCG;
    using OptiPack::nonlinearCG;
    typedef ScalarTraits<double> ST;

#ifdef DGM_PARALLEL
    DGM::Comm::World.reset( new DGM::MpiComm( &argc, &argv ) );
#else
    DGM::Comm::World.reset( new DGM::SerialComm() );
    DGM::Comm::Interupt();  // catch interrupts
#endif

    ArgList args( &argc, &argv );
    Table params;
    parse_args( args, params );

    // make a dgm optimal control problem with ModelEvaluator interface
    DGM::Comm::World->cout()
      << "================================================================\n"
      << "Making DGM Model Evaluator...\n"
      << "================================================================\n";
    Reo::OptProblem ocp( args, params, DGM::Comm::World );

    // check to make sure that the optimizer is Blackbox since that is the
    // only one that works with the ModelEvaluator
    if (!dynamic_cast<BlackBox*>(ocp.optimizer)) {
      DGM::Comm::World->cerr()
        << "ModelEvaulator must use BlackBox Optimizer (opttype="
        << OptProblem::BLACKBOX << ")" << std::endl;
      throw DGM::exception("Wrong unsupported Optimizer");
    }

    Stopwatch cpu;
    cpu.start();

    Teuchos::RCP<DGM::ModelEval> model(new DGM::ModelEval( &ocp ));

    Teuchos::RCP<Thyra::VectorBase<double> > p_init =
      Thyra::createMember<double>(model->get_p_space(0));

    // Try out Globipack LineSearch

    const RCP<BrentsLineSearch<double> >
      linesearch = brentsLineSearch<double>();
    const RCP<ParameterList> lsPL = parameterList();
    lsPL->sublist("Minimize").set("Max Iterations", 10);
    lsPL->sublist("Minimize").set("Relative Tol", 1.0e-3);
    linesearch->setParameterList(lsPL);
#if DGM_MODELEVAL_VERBOSE >= 1
    std::cout << "\nCurrent LineSearch parameters" << std::endl;
    lsPL->print(std::cout);
#endif
#if DGM_MODELEVAL_VERBOSE >= 2
    std::cout << "\nAvailable LineSearch parameters" << std::endl;
    linesearch->getValidParameters()->print(std::cout);
#endif

    // Try out OptiPack nonlinearCG optimization solver

    const RCP<OptiPack::NonlinearCG<double> > cgSolver =
      nonlinearCG<double>(model, 0, 0, linesearch);

    const RCP<VectorBase<double> > p = createMember(model->get_p_space(0));
    V_S( p.ptr(), ST::zero() );
    {
      // copy initial DGM control values into OptiPack solution vector
      Thyra::DetachedSpmdVectorView<double> my_p(p);
      for (int i = 0; i < my_p.subDim(); ++i) {
        my_p[i] = ocp.optimizer->control->phi[i];
#if DGM_MODELEVAL_VERBOSE >= 3
        std::cout << "i = " << i << " my_p[i] = " << my_p[i]
                  << " phi[i] = "<< ocp.optimizer->control->phi[i]
                  << std::endl;
#endif
      }
    }

    const double tol = as<double>(1.0e-2);
    const double alpha_init = as<double>(1.0e-3);
    const RCP<ParameterList> pl = parameterList();
    pl->set("Initial Linesearch Step Length", alpha_init);
    pl->set("Reinitlaize Linesearch Step Length", false);
    pl->set("Max Num Iterations", 10);
    pl->set("Min Num Iterations", 0);
    pl->set("Objective Reduction Tol", tol);
    pl->set("Objective Gradient Tol", tol);
    cgSolver->setParameterList(pl);

#if DGM_MODELEVAL_VERBOSE >= 1
    std::cout << "\nCurrent nonlinearCG parameters" << std::endl;
    pl->print(std::cout);
#endif
#if DGM_MODELEVAL_VERBOSE >= 2
    std::cout << "\nAvailable nonlinearCG parameters" << std::endl;
    cgSolver->getValidParameters()->print(std::cout);
#endif

    double g_opt;  // optimal value of the response
    int numIters;  // number of iteration taken
    const OptiPack::NonlinearCGUtils::ESolveReturn solveResult =
      cgSolver->doSolve( p.ptr(), outArg(g_opt),
                         null, null, null, outArg(numIters) );
    {
      // copy final solution back into DGM control datastructure
      Thyra::DetachedSpmdVectorView<double> my_p(p);
      for (int i = 0; i < my_p.subDim(); ++i) {
        ocp.optimizer->control->phi[i] = my_p[i];
      }
    }

    // plot the file control distribution
    ocp.optimizer->control->plot(1,numIters);

#if DGM_MODELEVAL_VERBOSE >= 1
    lsPL->print(std::cout);
#endif
    DGM::Comm::World->cout() << "Total run time:  " << cpu.stop() << endl;
#endif
  }
  catch (int x) {
    //DGM::Comm::World->cout() << "Caught integer exception: " << x << endl;
    return x;
  }
  catch (DGM::exception &e) {
    DGM::Comm::World->cout() << "DGM exception:  " << e.what() << endl;
    return e.error_code;
  }
  catch (std::exception &e) {
    DGM::Comm::World->cout() << "Standard exception: " << e.what() << endl;
    return DGM::FAILURE;
  }
  catch (...) {
    DGM::Comm::World->cout() << "Unknown exception..." << endl;
    return DGM::FAILURE;
  }
  DGM::Comm::World.reset();
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
    throw DGM::exception("Not enough arguments");
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
