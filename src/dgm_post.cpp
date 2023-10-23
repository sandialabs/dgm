/*=============================================================================
  Title:      Discontinuous Galerkin Post Processor

  Author:     S. Scott Collis
              Scalable Algorithms (1416)
              Sandia National Laboratories
              Albuquerque, NM 87175-1320
              (505) 284-1123
              sscoll@sandia.gov

  Copyright:  (c)2003 Rice University and (c)2010 Sandia National Laboratories
=============================================================================*/

/** \file dgm_post.cpp
    \brief File containing the main program for DGM post processor. */

// system libraries
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <list>
using namespace std;

#include "boost/numeric/conversion/cast.hpp"
using boost::numeric_cast;

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

// Reo libraries
#include "ReoInfo.hpp"
#include "ReoProblem.hpp"

// forward declarations

/// Manage command line inputs
void parse_args( DGM::ArgList &args, DGM::Table &params );

/// Printout the correct usage
void showUsage( const string& code );

/// The main DGM postprocessor driver program
/** Manage command line inputs, create the parallel process(es) and
    construct the DGM::Problem. */
int main(int argc, char *argv[]) {
  using namespace DGM;
  int status = 0;
  try {
#ifdef DGM_PARALLEL
    DGM::Comm::World.reset( new MpiComm( &argc, &argv ) );
#else
    DGM::Comm::World.reset( new SerialComm() );
#endif
    DGM::Comm::Interupt();
    DGM::Comm::Ptr &comm(DGM::Comm::World);
    std::ostream &out(comm->cout());
    {
      Reo::Info info;
      info.name(out);
      comm->cout()<< "Started Reo Post Processor on "
                  << DGM::dateTime() << endl;
      comm->cout()<<"  Running on: "<<info.hostname()<<endl;
      comm->cout()<<"  Compiled with: "<<info.compiler()<<endl;
      comm->cout()<<"  System set to: "<<info.system()<<endl;
    }

    ArgList args( &argc, &argv );
    Table params;

    // set default values
    string rst;
    params["rst"] = rst;

    int start = 0;
    params["start"] = start;
    int end = 0;
    params["end"] = end;
    int inc = 0;
    params["inc"] = inc;

    parse_args( args, params );

    Reo::Problem problem( args, params );

    const string root = problem.Omega->root;

    Stopwatch cpu;
    cpu.start();

    // loop over restart files from start to end
    start = params["start"];
    end   = params["end"];
    inc   = params["inc"];
    if (inc != 0) {     // loop over restart files
      for (int n=start; n<end+1; n=n+inc) {
        stringstream name;
        name << root << "." << n << ".rst";
        comm->cout() << "Processing " << name.str() << endl;
        status = numeric_cast<int>(problem.plot(name.str()));
      }
    }

    // process a single given restart file
    rst = (string)params["rst"];
    if (!rst.empty()) {
      comm->cout() << "Processing " << rst << endl;
      status = numeric_cast<int>(problem.plot(rst));
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
  DGM::Comm::World->cout()<<"Explicitly calling World::reset()"<<endl;
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
      if (name == "-r") {
        li.push_back(a);
        value = *(++a);
        params["rst"] = value;
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
        showUsage("dgm_post.exe");
      }
    }
  }
  // remove tagged arguments
  for ( list< DGM::ArgList::iterator >::iterator a=li.begin();
        a!=li.end(); a++) args.erase(*a);

  // make sure that enough arguments remain
  if (args.size() < 2) {
    showUsage("dgm_post.exe");
    throw DGM::exception("Not enough arguments");
  }
}

/** If there is an error in the input argument list, this routine prints the
    correct usage information. */
void showUsage(const string& code) {
  cerr << "================================================================\n"
       << "Discontinuous Galerkin Post Processor\n"
       << "================================================================\n"
       << "Usage: \t\t" << code << " [Options] -r <file.rst> run_name      \n"
       << "----------------------------------------------------------------\n"
       << "Options: " << '\t' << "Description\n"
       << "================================================================\n"
       << "-r     <string>" << '\t' << "Restart (rst) file to processes\n"
       << "-start <int>   " << '\t' << "Starting index\n"
       << "-end   <int>   " << '\t' << "Ending index\n"
       << "-inc   <int>   " << '\t' << "Index increment\n"
       << "-help          " << '\t' << "This help\n"
       << "----------------------------------------------------------------\n";
}
