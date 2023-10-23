/*=============================================================================
  Discontinuous Galerkin Statistics Post Processor

  Author:  S. Scott Collis

  Copyright:  Rice University and Sandia National Laboratories
=============================================================================*/

/** \file dgm_stats.cpp
    \brief File containing the main program for DGM Statistics. */

// system libraries
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <list>
using namespace std;

// CMC libraries
#include "Stopwatch.hpp"
using CMC::Stopwatch;

// DGM libraries
#include "ArgList.hpp"
#include "Comm.hpp"
#ifdef DGM_PARALLEL
#include "MpiComm.hpp"
#else
#include "SerialComm.hpp"
#endif
using namespace DGM;

// Reo libraries
#include "ReoProblem.hpp"

// forward declarations

/// Manage command line inputs
void parse_args( DGM::ArgList &args, DGM::Table &params );

/// Printout the correct usage
void showUsage( const string& code );

/// The main DGM statistics driver program.
/** Manage command line inputs, create the parallel process(es) and
    construct the DGM::Problem and then compute statistics */
int main(int argc, char *argv[]) {
  int status = 0;
  try {
#ifdef DGM_PARALLEL
    DGM::Comm::World.reset( new DGM::MpiComm( &argc, &argv ) );
#else
    DGM::Comm::World.reset( new DGM::SerialComm() );
#endif
    DGM::ArgList args( &argc, &argv );
    DGM::Table params;

    // set default values
    string rst = "rst";
    params["rst"] = rst;

    parse_args( args, params );

    Reo::Problem flow( args, params );

    Stopwatch cpu;
    cpu.start();

    int istart, iend, inc;
    cout << "Enter starting index "; cin >> istart;
    cout << "Enter ending index "; cin >> iend;
    cout << "Enter increment "; cin >> inc;

    char buf[128];
    //int status = 0;
    int samples = 0;
    string root = params["root"];
    for (int i=istart; i<=iend; i+=inc) {
      sprintf(buf,"%s.%d.rst",root.c_str(),i);
      rst = buf;
      cout << "Processing file " << rst << endl;
      flow.Omega->compute_stats(rst);
      samples++;
    }
    cout << "samples = " << samples << endl;
    flow.Omega->plot_stats( samples );

    DGM::Comm::World->cout() << "Total run time:  " << cpu.stop() << endl;
  }
  catch (int x) {
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
void parse_args( DGM::ArgList &args, Table &params ) {
  string name, value;
  list< DGM::ArgList::iterator > li;
  for ( DGM::ArgList::iterator a = args.begin(); a != args.end(); a++ ) {
    if ( (*a)[0] == '-' ) {
      name = *a;
      if (name == "-r") {
        li.push_back(a);
        value = *(++a);
        params["rst"] = value;
        li.push_back(a);
      } else if (name == "-help") {
        params["showUsage"] = 1;
        showUsage("dgm_stats.exe");
      }
    }
  }
  // remove tagged arguments
  for ( list< DGM::ArgList::iterator >::iterator a=li.begin();
        a!=li.end(); a++) args.erase(*a);
  // make sure that enough arguments remain
  if (args.size() < 2) {
    showUsage("stats");
    throw DGM::exception("Not enough arguments");
  }
  string root = args.back();
  params["root"] = root;
}

/** If there is an error in the input argument list, this routine prints the
    correct usage information. */
void showUsage(const string& code) {
  cerr << "================================================================\n"
       << "Discontinuous Galerkin Statistics Processor\n"
       << "================================================================\n"
       << "Usage: \t\t" << code << " [Options] -r <rst file> run_name      \n"
       << "----------------------------------------------------------------\n"
       << "Options: " << '\t' << "Description\n"
       << "================================================================\n"
       << "-help    " << '\t' << "Detailed help\n"
       << "----------------------------------------------------------------\n";
}
