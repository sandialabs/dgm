/*=============================================================================
  Title:      Discontinuous Galerkin Solver with Error Estimates

  Authors:    S. Scott Collis and Matt Gamel
              Scalable Algorithms (1416)
              Sandia National Laboratories
              Albuquerque, NM 87175-1320
              (505) 284-1123
              sscoll@sandia.gov

  Copyright:  Rice University and Sandia National Laboratories
=============================================================================*/

/** \file dgm_err.cpp
    \brief File containing the main program for DGM for error estimation. */

// system libraries
#include <iostream>
#include <cstdio>
#include <string>
#include <sstream>
using namespace std;

// DGM libraries
#include "Comm.hpp"
#ifdef DGM_PARALLEL
#include "MpiComm.hpp"
#else
#include "SerialComm.hpp"
#endif
#include "ArgList.hpp"
#include "ErrProblem.hpp"

// CMC libraries
#include "Stopwatch.hpp"
using CMC::Stopwatch;

// forward declarations

/// Manage command line inputs
void parse_args( DGM::ArgList &args, DGM::Table &params );

/// Printout the correct usage
void showUsage( const string& code );

/// The main DGM Error Estimation driver
/** Manage command line inputs, create the parallel process(es) and construct
    the problem */
int main(int argc, char *argv[]) {
  ofstream null("/dev/null");
#ifdef DGM_PARALLEL
  DGM::Comm::World.reset( new DGM::MpiComm( &argc, &argv ) );
  DGM::Comm::World->cout() << "Running on " << DGM::Comm::World->NumProc()
                           << " processors..." << std::endl;
#else
  DGM::Comm::World.reset( new DGM::SerialComm() );
  DGM::Comm::Interupt();  // catch interupts (only works for serial)
#endif
  DGM::ArgList args( &argc, &argv );
  DGM::Table params;
  parse_args( args, params );

  DGM::ErrProblem problem(args, params, DGM::Comm::World);
  Stopwatch cpu;
  cpu.start();
  Ordinal status = problem.solve();
  DGM::Comm::World->cout() << "Total run time:  " << cpu.stop() << endl;

#ifdef OPEN_MPI
#if !((OMPI_MAJOR_VERSION <= 1) && (OMPI_MINOR_VERSION <= 8) && \
    (OMP_RELEASE_VERSION <= 4))
  comm->cout()<<"Explicitly calling World::reset()"<<endl;
  DGM::Comm::World.reset();
#endif
#endif
  return status;
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
        showUsage("dgm_err.exe");
      }
    }
  }
  // remove tagged arguments
  for ( list< DGM::ArgList::iterator >::iterator a=li.begin();
        a!=li.end(); a++) args.erase(*a);

  // make sure that enough arguments remain
  if (args.size() < 2) {
    showUsage("dgm_err.exe");
    DGM::Comm::World->exit(DGM::FAILURE);
  }
}

/** If there is an error in the input argument list, this routine prints the
    correct usage information. */
void showUsage(const string& code) {
  DGM::Comm::World->cout()
    << "================================================================\n"
    << "Discontinuous Galerkin Solver with Error Estimates\n"
    << "================================================================\n"
    << "Usage:  \t" << code << " [Options] run_name \n"
    << "----------------------------------------------------------------\n"
    << "Options: " << '\t' << "Description\n"
    << "----------------------------------------------------------------\n"
    << "-help    " << '\t' << "Detailed help\n"
    << "----------------------------------------------------------------\n";
}
