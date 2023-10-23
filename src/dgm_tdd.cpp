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

/** \file dgm_tdd.cpp
    \brief File containing the main program DGM time domain decomposition. */

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

/// The main DGM-TDD program.
/** Manage command line inputs, create the parallel process(es) and construct
    the TDD optimal control problem */
int main(int argc, char *argv[]) {

#ifdef DGM_PARALLEL
  DGM::Comm::World.reset( new DGM::MpiComm( &argc, &argv ) );
  Epetra_MpiComm Comm( MPI_COMM_WORLD );
#else
  DGM::Comm::World.reset( new DGM::SerialComm() );
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
      int      np_max_iter        = 10;
      bool     print_sol          = false;
      bool     compute_ic         = false;

      CommandLineProcessor clProcessor(false); // Don't throw exceptions
      clProcessor.setOption( "t_0", &t_0, "Initial time" );
      clProcessor.setOption( "t_N", &t_N, "Final time" );
      clProcessor.setOption( "N", &N, "Number of time domain blocks" );

      // Setup other object's parameters
      TDD::DTOCPBlockIter<Scalar>        a_dtocp_block;
      TDD::DTOCP<Scalar>                 dtocp;
      TSFCore::Nonlin::NPDTOCP<Scalar>   np;
      a_dtocp_block.setupCommandLineProcessor( &clProcessor );
      dtocp.setupCommandLineProcessor( &clProcessor );
      np.setupCommandLineProcessor( &clProcessor );

      // Setup other parameters
      clProcessor.setOption( "print-level", &print_level_in,
                             (std::string("print level (") +
                              TDD::printLevelOptionsStr+")").c_str() );
      clProcessor.setOption( "do-tests", "no-do-tests", &do_tests,
                             "Do testing or not." );
      clProcessor.setOption( "np-sol-tol", &np_sol_tol,
                             "Nonlinear solve tolerance." );
      clProcessor.setOption( "np-max-iter", &np_max_iter,
                             "Nonlinear solver maximum iterations." );
      clProcessor.setOption( "print-sol", "no-print-sol", &print_sol,
                             "Print the solution or not." );
      clProcessor.setOption( "compute-ic", "no-compute-ic", &compute_ic,
                             "Compute and IC before NP solve." );
      // Parse the command line arguments

      argc--; // remove the last argument
      CommandLineProcessor::EParseCommandLineReturn parse_return =
        clProcessor.parse(argc,argv);
      if( parse_return != CommandLineProcessor::PARSE_SUCCESSFUL ) {
        cout<<"Warning:  undefined command arguments"<<endl;
        // return parse_return;  // not for dgm code
      }
      TDD::EPrintLevel print_level = TDD::convert_print_level(print_level_in);
      np.print_level(print_level);
      Teuchos::RefCountPtr<std::ostream> summaryOut =
        Teuchos::rcp(new std::ofstream("Summary.out"));
      np.set_summaryOut(summaryOut);
      np.leadingSummaryOutputStr("  ");
      np.set_trace_out(Teuchos::rcp(&std::cout,false));
      a_dtocp_block.set_trace_out(Teuchos::rcp(&std::cout,false));

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

      //
      // Setup the CTOCP and DTOCPBlock objects for each time block
      //

      const Scalar delta_t = (t_N - t_0) / N;

      std::vector<Teuchos::RefCountPtr<TDD::DTOCPBlock<Scalar> > >
        dtocp_blocks(N);

      Scalar t_i = t_0, t_ip1 = t_i + delta_t;
      int n_i = 0;
      for( int i = 0; i < N; ++i, t_i += delta_t, t_ip1 += delta_t ) {
        cout<<"Building CTOCP for time domain "<<i<<", t_i = "<<t_i
            <<", t_ip1 = "<<t_ip1<<endl;
        Teuchos::RefCountPtr<TDD::CTOCPdgm > tmp_ctocp =
          Teuchos::rcp(new TDD::CTOCPdgm(i,n_i,t_i,t_ip1,Comm,&ocp,&locp));
        n_i += ocp.control->get_npredict();
        Teuchos::RefCountPtr<TDD::DTOCPBlockIter<Scalar> >
          dtocp_block = Teuchos::rcp(new TDD::DTOCPBlockIter<Scalar>());
        dtocp_block->copyOptions(a_dtocp_block);
        dtocp_block->initialize(tmp_ctocp);
        dtocp_blocks[i] = dtocp_block;
      }

      //
      // Setup DTOCP
      //

      dtocp.initialize(
        MPI_COMM_NULL                    // mpiComm
        ,N                               // numTotalTimeBlocks
        ,N                               // numMyTimeBlocks
        ,0                               // iStart
        ,N-1                             // iEnd
        ,&dtocp_blocks[0]                // myDTOCPBlocks
        );

      //
      // Setup the initial point for the blocks
      //

      Teuchos::RefCountPtr<TSFCore::Vector<Scalar> >
        np_y0 = dtocp.space_x()->createMember();
      for( int i = 0; i < N; ++i, t_i += delta_t, t_ip1 += delta_t ) {
        if(i < N-1 ) dtocp.set_y_bar_ip1( i, *y_bar_ip1, &*np_y0 );
        dtocp.set_u_bar_i( i, *u_bar_i, &*np_y0 );
        if(i > 0 ) dtocp.set_lambda_bar_i( i, *lambda_bar_i, &*np_y0 );
      }

      //
      // Setup the nonlinear problem
      //

      np.initialize( Teuchos::rcp(&dtocp,false), *np_y0 );

      //
      // Solve the nonlinear problem
      //

      TSFCore::Nonlin::SimpleNewtonSolver<Scalar> newtonSolver;
      Teuchos::RefCountPtr<TSFCore::Vector<Scalar> >
        np_y = np.space_y()->createMember();
      assign( &*np_y, np.y0() );

      //
      // Solve State and Adjoint in serial to get an initial condition
      //
      if (compute_ic) {
        std::cout << "\n*** Solve for an initial condition ...\n";
        dtocp.setPoint(*np_y);
        std::ifstream u_in("u.in");  // this is needed for interface
        dtocp.readControl(u_in);
        dtocp.computeState();
        cout << "Objective function = " << dtocp.computeObjective() << endl;
        dtocp.computeAdjoint();
        dtocp.getPoint(&*np_y);
      }

      std::cout << "\n*** Solve the equations ...\n";

      newtonSolver.tol(np_sol_tol);
      newtonSolver.maxNewtonIter(np_max_iter);
      newtonSolver.set_summaryOut(summaryOut);
      newtonSolver.solve( &np, &*np_y, &std::cout,
                          print_level==TDD::PRINT_EVERYTHING );

      //
      // Get statistics for the number of total time steps
      //

      std::cout << "\n*** Time step statistics:\n";
      dtocp.printStepStats( &std::cout );

      std::cout<<"\n*** Printing control ...\n\n";
      std::ofstream u_out("u.out");
      dtocp.printControl(u_out);
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
#ifdef OPEN_MPI
#if !((OMPI_MAJOR_VERSION <= 1) && (OMPI_MINOR_VERSION <= 8) && \
    (OMP_RELEASE_VERSION <= 4))
  comm->cout()<<"Explicitly calling World::reset()"<<endl;
  DGM::Comm::World.reset();
#endif
#endif
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
       << "Discontinuous Galerkin TDD Optimal Control Solver\n"
       << "================================================================\n"
       << "Usage:  \t" << code << " [Options] run_name \n"
       << "----------------------------------------------------------------\n"
       << "Options: " << '\t' << "Description\n"
       << "================================================================\n"
       << "-help    " << '\t' << "Detailed help\n"
       << "----------------------------------------------------------------\n";
}
