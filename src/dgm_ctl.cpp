/*=============================================================================
  Title:      Feedback Control using Discontinuous Galerkin Method

  Author:     S. Scott Collis
              Scalable Algorithms
              Sandia National Laboratories
              Albuquerque, NM 87175-1320
              (505) 284-1123
              sscoll@sandia.gov

  Copyright:  Rice University and Sandia National Laboratories
=============================================================================*/

/** \file dgm_ctl.cpp
    \brief File containing the main program for DGM feedback control. */

// system libraries
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <list>
using namespace std;

// local libraries
#include "Comm.hpp"
#ifdef DGM_PARALLEL
#include "MpiComm.hpp"
#else
#include "SerialComm.hpp"
#endif
#include "Stopwatch.hpp"
using CMC::Stopwatch;
#include "ArgList.hpp"
#include "ControlProblem.hpp"

// forward declarations

/// Manage command line inputs
void parse_args( DGM::ArgList &args, Table &params );

/// Printout the correct usage
void showUsage( const string& code );

/// The main DGM feedback control driver
/** Manage command line inputs, create the parallel process(es) and construct
    the ControlProblem */
int main(int argc, char *argv[]) {

#ifdef DGM_PARALLEL
  DGM::Comm::World.reset( new DGM::MpiComm( &argc, &argv ) );
  DGM::Comm::World->cout() << "Running on " << DGM::Comm::World->NumProc()
         << " processors..." << std::endl;
#else
  DGM::Comm::World.reset( new DGM::SerialComm() );
  DGM::Comm::Interupt();  // catch interupts
#endif

  ArgList args( &argc, &argv );
  Table params;
  parse_args( args, params);

  ControlProblem problem( args, params, DGM::Comm::World );

  Stopwatch cpu;
  cpu.start();

  Ordinal status = problem.solve();

  DGM::Comm::World->cout() << "Total run time:  " << cpu.stop() << std::endl;

#if !((OMPI_MAJOR_VERSION <= 1) && (OMPI_MINOR_VERSION <= 8) && \
    (OMP_RELEASE_VERSION <= 4))
  comm->cout()<<"Explicitly calling World::reset()"<<endl;
  DGM::Comm::World.reset();
#endif
  return status;
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
    showUsage("dgm_ctl");
    DGM::Comm::World->exit(DGM::FAILURE);
  }
}

/** If there is an error in the input argument list, this routine prints the
    correct usage information. */
void showUsage(const string& code) {
  DGM::Comm::World->cout()
    << "================================================================\n"
    << "Discontinuous Galerkin Feedback Control Solver\n"
    << "================================================================\n"
    << "Usage:  \t" << code << " [Options] run_name \n"
    << "----------------------------------------------------------------\n"
    << "Options: " << '\t' << "Description\n"
    << "----------------------------------------------------------------\n"
    << "-help    " << '\t' << "Detailed help\n"
    << "----------------------------------------------------------------\n";
}
