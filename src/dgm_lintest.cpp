/*=============================================================================
  Title:      Linearized solve tester

  Copyright:  (c)2010 Sandia National Laboratories
=============================================================================*/

/** \file dgm_lintest.cpp
    \brief Test program for linearized solves. */

// system libraries
#include <iostream>
#include <cstdio>
#include <string>
#include <list>
using namespace std;

// DGM includes
#ifdef DGM_PARALLEL
#include "MpiComm.hpp"
#else
#include "SerialComm.hpp"
#endif
#include "ArgList.hpp"
#include "LinTest.hpp"

// Reo includes
#include "ReoOptProblem.hpp"

// CMC includes
#include "Stopwatch.hpp"
using CMC::Stopwatch;

// forward declarations

/// Manage command line inputs
void parse_args( DGM::ArgList &args, DGM::Table &params );

/// Printout the correct usage
void showUsage( const string &code );

int main(int argc, char *argv[]) {
  try {
#ifdef DGM_PARALLEL
    DGM::Comm::World.reset( new DGM::MpiComm( &argc, &argv ) );
#else
    DGM::Comm::World.reset( new DGM::SerialComm() );
    DGM::Comm::Interupt();  // catch interupts
#endif

    // Save the command line arguments
    DGM::ArgList args( &argc, &argv );
    DGM::Table params;

    // Parse the command line arguments
    parse_args( args, params );

    // Create the optimization objects
    DGM::Comm::World->cout()
      << "================================================================\n"
      << "Computing a finite difference test of the linearized state solve"
      << "================================================================\n";

    // Start a clock on the solve
    Stopwatch cpu;
    cpu.start();

    // Compute the finite difference test on the state
    DGM::lin_state_test<Reo::OptProblem>(args,params,DGM::Comm::World);

    // Write out the timing information
    static DGM::Format sci(4,10,'e');
    DGM::Comm::World->cout() << "Total run time: " << sci(cpu.stop())
                             << " sec = " << sci(cpu.stop()/3600.0)
                             << " hr " << endl;
    DGM::Comm::World.reset();
    return DGM::SUCCESS;
  } catch (...) {
    return DGM::FAILURE;
  }
}

/** Creates a parameter Table of the input arguments. */
void parse_args( DGM::ArgList &args, DGM::Table &params ) {
  string name, value;
  list< DGM::ArgList::iterator > li;
  for ( DGM::ArgList::iterator a = args.begin(); a != args.end(); a++ ) {
    if ( (*a)[0] == '-' ) {
      name = *a;
      if (name == "-help") {
        params["showUsage"] = 1;
        showUsage("lintest");
      }
    }
  }

  // remove tagged arguments
  for ( list< DGM::ArgList::iterator >::iterator a=li.begin();
        a!=li.end(); a++) args.erase(*a);

  // make sure that enough arguments remain
  if (args.size() < 3) {
    showUsage("lintest");
    DGM::Comm::World->exit(DGM::FAILURE);
  }
}

/** If there is an error in the input argument list, this routine prints the
    correct usage information. */
void showUsage(const string &code) {
  cerr << "================================================================\n"
       << "DGM Linerized Solve Test\n"
       << "================================================================\n"
       << "Usage:  \t" << code << " step run_name \n"
       << "----------------------------------------------------------------\n"
       << "Options: " << '\t' << "Description\n"
       << "================================================================\n"
       << "-help     " << "\t" << "Detailed help\n"
       << "----------------------------------------------------------------\n";
}
