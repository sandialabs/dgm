/*=============================================================================
  Discontinuous Galerkin Control Post Processor

  Author:     S. Scott Collis
              Scalable Algorithms
              Sandia National Laboratories
              Albuquerque, NM 87175-1320
              (505) 284-1123
              sscoll@sandia.gov

  Copyright:  (c)2003 Rice University and (c)2010 Sandia National Laboratories
=============================================================================*/

/** \file dgm_cpost.cpp
    \brief File containing the main program for DGM Control Post Processor. */

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
#include "Comm.hpp"
#ifdef DGM_PARALLEL
#include "MpiComm.hpp"
#else
#include "SerialComm.hpp"
#endif
#include "ArgList.hpp"

// Reo includes
#include "ReoInfo.hpp"
#include "ReoOptProblem.hpp"

// forward declarations

/// Manage command line inputs
void parse_args( DGM::ArgList &args, DGM::Table &params );

/// Printout the correct usage
void showUsage( const string& code );

/// The main DGM control postprocessor driver program.
/** Manage command line inputs, create the parallel process(es) and
    construct the DGM::Problem */
int main(int argc, char *argv[]) {
  using namespace DGM;
  int status = 0;
  try {
#ifdef DGM_PARALLEL
    Comm::World.reset( new MpiComm( &argc, &argv ) );
#else
    Comm::World.reset( new SerialComm() );
#endif
    DGM::Comm::Interupt();
    DGM::Comm::Ptr &comm(DGM::Comm::World);
    std::ostream &out(comm->cout());
    {
      Reo::Info info;
      info.name(out);
      comm->cout()<< "Started Reo Control Post Processor on "
                  << DGM::dateTime() << endl;
      comm->cout()<<"  Running on: "<<info.hostname()<<endl;
      comm->cout()<<"  Compiled with: "<<info.compiler()<<endl;
      comm->cout()<<"  System set to: "<<info.system()<<endl;
    }

    ArgList args( &argc, &argv );
    Table params;

    // set default values
    string ctl;
    params["ctl"] = ctl;
    int start = 0;
    params["start"] = start;
    int end = 0;
    params["end"] = end;
    int inc = 0;
    params["inc"] = inc;

    parse_args( args, params );

    Reo::OptProblem ocp( args, params, DGM::Comm::World );

    const string root = ocp.state->domain()->root;

    Stopwatch cpu;
    cpu.start();

    // loop over ctl files from start to end
    start = params["start"];
    end   = params["end"];
    inc   = params["inc"];
    if (inc != 0) {     // loop over restart files
      for (int n=start; n<end+1; n=n+inc) {
        stringstream name;
        name << root << "." << n << ".ctl";
        comm->cout() << "Processing " << name.str() << endl;
        status = ocp.plot(name.str());
      }
    }

    // process a single ctl file
    ctl = (string)params["ctl"];
    if (!ctl.empty()) {
      comm->cout() << "Processing " << ctl << endl;
      status = ocp.plot(ctl);
    }

    DGM::Comm::World->cout() << "Total run time:  " << cpu.stop() << endl;
  }
  catch (int x) {
    cout << DGM::Comm::World->MyPID() << ": Integer exception: " << x << endl;
    if (DGM::Comm::World->NumProc()>1) DGM::Comm::World->abort(x);
    return x;
  }
  catch (DGM::exception &e) {
    if (e.error_code!=0) {
      cout << DGM::Comm::World->MyPID() << ": DGM exception:  "
          << e.what() << endl;
      if (DGM::Comm::World->NumProc()>1) DGM::Comm::World->abort(DGM::FAILURE);
    }
    return e.error_code;
  }
  catch (std::exception &e) {
    cout << DGM::Comm::World->MyPID() << ": Standard exception: "
        << e.what() << endl;
    if (DGM::Comm::World->NumProc()>1) DGM::Comm::World->abort(DGM::FAILURE);
    return DGM::FAILURE;
  }
  catch (...) {
    cout << DGM::Comm::World->MyPID() << ": Unknown exception..." << endl;
    if (DGM::Comm::World->NumProc()>1) DGM::Comm::World->abort(DGM::FAILURE);
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
void parse_args( DGM::ArgList &args, DGM::Table &params ) {
  string name, value;
  list< DGM::ArgList::iterator > li;
  for ( DGM::ArgList::iterator a = args.begin(); a != args.end(); a++ ) {
    if ( (*a)[0] == '-' ) {
      name = *a;
      if (name == "-c") {
        li.push_back(a);
        value = *(++a);
        params["ctl"] = value;
        li.push_back(a);
      } else if (name == "-start") {
        li.push_back(a);
        value = *(++a);
        li.push_back(a);
        params["start"] = atoi(value.c_str());
      } else if (name == "-end") {
        li.push_back(a);
        value = *(++a);
        li.push_back(a);
        params["end"] = atoi(value.c_str());
      } else if (name == "-inc") {
        li.push_back(a);
        value = *(++a);
        li.push_back(a);
        params["inc"] = atoi(value.c_str());
       } else if (name == "-help") {
        params["showUsage"] = 1;
        showUsage("dgm_cpost.exe");
      }
    }
  }
  // remove tagged arguments
  for ( list< DGM::ArgList::iterator >::iterator a=li.begin();
        a!=li.end(); a++) args.erase(*a);

  // make sure that enough arguments remain
  if (args.size() < 2) {
    showUsage("dgm_cpost.exe");
    throw DGM::exception("Not enough arguments");
  }
}

/** If there is an error in the input argument list, this routine prints the
    correct usage information. */
void showUsage(const string& code) {
  cerr << "================================================================\n"
       << "Discontinuous Galerkin Control Post Processor\n"
       << "================================================================\n"
       << "Usage:\t\t" << code << " [Options] -c <file.ctl> run_name\n"
       << "----------------------------------------------------------------\n"
       << "Options: " << '\t' << "Description\n"
       << "================================================================\n"
       << "-c     <string>" << '\t' << "Control (ctl) file to processes\n"
       << "-start <int>   " << '\t' << "Starting index\n"
       << "-end   <int>   " << '\t' << "Ending index\n"
       << "-inc   <int>   " << '\t' << "Index increment\n"
       << "-help          " << '\t' << "This help\n"
       << "----------------------------------------------------------------\n";
}
