/*=============================================================================
  Title:      Time Domain Decomposition using Discontinuous Galerkin Solve

  Author:     S. Scott Collis
              Scalable Algorithms
              Sandia National Laboratories
              Albuquerque, NM 87175-1320
              (505) 284-1123
              sscoll@sandia.gov

  Copyright:  Rice University and Sandia National Laboratories
=============================================================================*/

/** \file dgm_tdd_test.cpp
    \brief File containing the main program for DGM time domain decomposition
    testing *
*/

// system libraries
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <list>
using namespace std;

// local libraries
#ifdef DGM_PARALLEL
#include "MpiComm.hpp"
#else
#include "SerialComm.hpp"
#endif
#include "Stopwatch.hpp"
using CMC::Stopwatch;
#include "ArgList.hpp"
#include "OptProblem.hpp"

// Trilinos
#ifdef DGM_PARALLEL
#include "Epetra_MpiComm.h"
#else
#include "Epetra_SerialComm.h"
#endif
#include "Epetra_Map.h"
#include "Epetra_Vector.h"
#include "Epetra_Time.h"

// TDD development
#include "Teuchos_CommandLineProcessor.hpp"
#include "CTOCPdgm.hpp"
#include "CTOCPMOAT.hpp"
#include "DTOCP.hpp"
#include "DTOCPBlockIter.hpp"
#include "NPDTOCP.hpp"
#include "TSFCoreNonlinSimpleNewtonSolver.hpp"

// forward declarations

/// Manage command line inputs
void parse_args( DGM::ArgList &args, Table &params );

/// Printout the correct usage
void showUsage( const string& code );

/// The main DGM_TDD program.

/** Manage command line inputs, create the parallel process(es) and construct
    the TDD optimal control problem */
int main(int argc, char *argv[]) {

#ifdef DGM_PARALLEL
  DGM::Comm::World = new DGM::MpiComm( &argc, &argv );
  Epetra_MpiComm Comm( MPI_COMM_WORLD );
#else
  DGM::Comm::World = new DGM::SerialComm();
  Epetra_SerialComm Comm;
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

  // make a dgm LINEARIZED optimal control problem
  DGM::Comm::World->cout()
    << "================================================================\n"
    << "Making dgm_linear_ocp...\n"
    << "================================================================\n";
  Reo::OptProblem locp( &ocp, args, params, DGM::Comm::World );

  Stopwatch cpu;
  cpu.start();

  //======================================================================
  {

    // Get the process ID and the total number of processors
    int MyPID = Comm.MyPID();
    int NumProc = Comm.NumProc();
    DGM::Comm::World->cout() << "I am processor " << MyPID << " out of " <<
      NumProc << "." << endl;

    typedef double Scalar;
    using Teuchos::CommandLineProcessor;

    bool success = true;

    try {

      // setup parameters...

      double   t_0                = 0.0;
      double   t_N                = 1.0;
      int      N                  = 4;

      // Other parameters
      int      print_level_in     = 0;
      bool     do_tests           = false;
      double   np_sol_tol         = 1e-6;
      bool     print_sol          = false;

      CommandLineProcessor clProcessor(false); // Don't throw exceptions
      clProcessor.setOption( "t_0", &t_0, "Initial time" );
      clProcessor.setOption( "t_N", &t_N, "Final time" );
      clProcessor.setOption( "N", &N, "Number of time domain blocks" );

      // Setup other object's parameters
      TDD::CTOCPMOAT<Scalar> ctocp_moat;
      ctocp_moat.dtocp_tester().h_y_bar_i(0.001);
      ctocp_moat.dtocp_tester().h_u_bar_i(0.001);
      ctocp_moat.dtocp_tester().h_lambda_bar_ip1(0.001);
      ctocp_moat.dtocp_tester().lin_state_tol(1e-2);
      ctocp_moat.dtocp_tester().lin_adjoint_tol(1e-2);
      ctocp_moat.dtocp_tester().lin_grad_tol(1e-2);
      ctocp_moat.dtocp_tester().lin_state_sol_tol(1e-2);
      ctocp_moat.dtocp_tester().lin_adjoint_sol_tol(1e-2);
      ctocp_moat.dtocp_tester().lin_grad_sol_tol(1e-2);
      ctocp_moat.dtocp().lin_solve_tol(1e-3);
      ctocp_moat.setupCommandLineProcessor( &clProcessor );

      // Setup other parameters
      clProcessor.setOption( "print-level", &print_level_in,
                             (std::string("print level (") +
                              TDD::printLevelOptionsStr+")").c_str() );
      clProcessor.setOption( "do-tests", "no-do-tests", &do_tests,
                             "Do testing or not." );
      clProcessor.setOption( "np-sol-tol", &np_sol_tol,
                             "Nonlinear solve tolerance." );
      clProcessor.setOption( "print-sol", "no-print-sol", &print_sol,
                             "Print the solution or not." );
      // Parse the command line arguments

      argc--; // remove the last argument
      CommandLineProcessor::EParseCommandLineReturn parse_return =
        clProcessor.parse(argc,argv);
      if( parse_return != CommandLineProcessor::PARSE_SUCCESSFUL ) {
        cout<<"Warning:  undefined command arguments"<<endl;
        // return parse_return;  // not for dgm code
      }
      TDD::EPrintLevel print_level = TDD::convert_print_level(print_level_in);

      //
      // Create a CTOCP object (just for the vector spaces)
      //

      DGM::Comm::World->cout()
        << "===============================================================\n"
        << "Making TDD system...\n"
        << "===============================================================\n";

      TDD::CTOCPdgm ctocp(0, 0, t_0, t_N, Comm, &ocp, &locp);

      Teuchos::RefCountPtr< TSFCore::Vector<Scalar> >
        y_bar_i        = ctocp.space_y_bar_i()->createMember(),
        y_bar_ip1      = ctocp.space_y_bar_i()->createMember(),
        u_bar_i        = ctocp.space_u_bar_i()->createMember(),
        lambda_bar_i   = ctocp.space_y_bar_i()->createMember(),
        lambda_bar_ip1 = ctocp.space_y_bar_i()->createMember();

      assign( y_bar_i.get(), 0.0 );
      assign( y_bar_ip1.get(), 0.0 );
      assign( u_bar_i.get(), 0.0 );
      assign( lambda_bar_i.get(), 0.0 );
      assign( lambda_bar_ip1.get(), 0.0 );

      ctocp_moat.dtocp().set_trace_out(Teuchos::rcp(&std::cout,false));

      bool result = ctocp_moat.test(
        &ctocp
        ,*y_bar_i
        ,*y_bar_ip1
        ,*u_bar_i
        ,*lambda_bar_i
        ,*lambda_bar_ip1
        ,&std::cout
        );
      if(!result) success = false;
    }
    catch (const std::exception& excpt ) {
      std::cout.flush();
      std::cerr << "\nCaught a std::exception: " << excpt.what() << std::endl;
      success = false;
    }
    catch(...) {
      std::cout.flush();
      std::cerr << "\nCaught an unknown exception!\n";
      success = false;
    }
    if(success)
      std::cout << "\nFinal: Congratulations! No errors reported!\n\n";
    else
      std::cout << "\nFinal: Oh no! Something went wrong!\n\n";
  }

  //======================================================================

  if (DGM::Comm::World->Master())
    cout << "Total run time:  " << cpu.stop() << endl;

  delete DGM::Comm::World;

  return 0;
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
       << "Discontinuous Galerkin TDD_Test Optimal Control Solver\n"
       << "================================================================\n"
       << "Usage:  \t" << code << " [Options] run_name \n"
       << "----------------------------------------------------------------\n"
       << "Options: " << '\t' << "Description\n"
       << "================================================================\n"
       << "-help    " << '\t' << "Detailed help\n"
       << "----------------------------------------------------------------\n";
}
