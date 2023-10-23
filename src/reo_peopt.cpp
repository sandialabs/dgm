/*=============================================================================
  Title:      Optimization driver for Reo

  Contacts:   Scott Collis
              sscoll@sandia.gov

  Copyright:  (c)2010-2012 Sandia National Laboratories
=============================================================================*/

/** \file reo_peopt.cpp
    \brief Optimal control solver for Reo
    \author Scott Collis and Joeseph Young
*/

// For the moment, we require parallel builds
#ifndef DGM_PARALLEL
#error derived_code_peopt requires that one build with DGM_PARALLEL=1
#endif

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
#include "ReoInfo.hpp"
#include "ReoOptProblem.hpp"
#include "Partition.tpp"

// peopt includes
#include <memory>
#include "peopt/peopt.h"
#include "peopt/json.h"
#include "PEReo.hpp"

// CMC includes
#include "Stopwatch.hpp"
using CMC::Stopwatch;

// forward declarations

/// Manage command line inputs
void parse_args( DGM::ArgList &args, DGM::Table &params );

/// Printout the correct usage
void showUsage( const string& code );

/// The main derived-code peopt driver program.
/** Manage command line inputs, create the parallel process(es) and
    construct the optimization problem. */
int main(int argc, char *argv[]) {
  try {
#ifdef DGM_PARALLEL
    DGM::Comm::World.reset( new DGM::MpiComm( &argc, &argv ) );
    DGM::Comm::World->cout() << "Running Reo on "
                             << DGM::Comm::World->NumProc()
                             << " processors..." << std::endl;
#else
    DGM::Comm::World.reset( new DGM::SerialComm() );
#endif
    DGM::Comm::Interupt();
    DGM::Comm::Ptr &comm(DGM::Comm::World);
    std::ostream &out(comm->cout());
    Reo::Info info;
    info.name(out);

    // Save the command line arguments
    DGM::ArgList args( &argc, &argv );
    DGM::Table params;

    // By default, we don't print out the peopt parameters and exit
    params["genparams"] = 0;

    // Parse the command line arguments
    parse_args( args, params );

    // Check if we generate parameters
    int genparams = params["genparams"];

    // Setup and solve the optimization problem
    peopt::setupAndSolve
      <Reo::OptProblem,
      peopt::ReoParams,peopt::ReoManipulator<Reo::OptProblem,peopt::ReoParams> >
      (args,params,genparams,args.back());
  }
  catch (int x) {
    return x;
  }
  catch (DGM::exception &e) {
    DGM::Comm::World->cout() << "DGM exception:  " << e.what() << endl;
    return DGM::FAILURE;
  }
  catch (std::exception &e) {
    DGM::Comm::World->cout() << "Standard exception: " << e.what() << endl;
    return DGM::FAILURE;
  }
  catch (...) {
    DGM::Comm::World->cout() << "Unknown exception..." << endl;
    return DGM::FAILURE;
  }
  return DGM::SUCCESS;
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
        showUsage("reo_peopt.exe");
      } else if (name == "-params") {
        li.push_back(a);
        params["genparams"] = 1;
      }
    }
  }

  // remove tagged arguments
  for ( list< DGM::ArgList::iterator >::iterator a=li.begin();
        a!=li.end(); a++) args.erase(*a);

  // make sure that enough arguments remain
  if (args.size() < 2) {
    showUsage("reo_peopt.exe");
    throw DGM::exception("Not enough arguments");
  }
}

/** If there is an error in the input argument list, this routine prints the
    correct usage information. */
void showUsage(const string& code) {
  cerr << "================================================================\n"
       << "DGM/peopt Optimizer\n"
       << "================================================================\n"
       << "Usage:  \t" << code << " [Options] run_name \n"
       << "----------------------------------------------------------------\n"
       << "Options: " << '\t' << "Description\n"
       << "================================================================\n"
       << "-help     " << "\t" << "Detailed help\n"
       << "-params   " << "\t" << "Generate parameters\n"
       << "----------------------------------------------------------------\n";
}
