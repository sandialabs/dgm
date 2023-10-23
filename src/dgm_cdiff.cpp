/*=============================================================================
  Title:      Discontinuous Galerkin Diff(erence)

  Author:     S. Scott Collis
              Scalable Algorithms
              Sandia National Laboratories
              Albuquerque, NM 87175-1320
              (505) 284-1123
              sscoll@sandia.gov

  Copyright:  (c)2009 Sandia National Laboratories
=============================================================================*/

/** \file dgm_cdiff.cpp
    \brief File containing the main program for DGM Ctrl difference. */

// system libraries
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <list>
using namespace std;

#include "boost/numeric/conversion/cast.hpp"
using boost::numeric_cast;

// local libraries
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
#include "MultiOptProblem.hpp"
#include "Partition.tpp"
#include "PEReo.hpp"
#include "ReoOptProblem.hpp"

// forward declarations

/// Manage command line inputs
void parse_args( DGM::ArgList &args, DGM::Table &params );

/// Printout the correct usage
void showUsage( const string& code );

/// The main DGM Control file difference driver program.
/** Manage command line inputs, create the parallel process(es) and
    construct the DGM::Problem */
int main(int argc, char *argv[]) {
  using namespace DGM;
  int status = 0;
  try {
#ifdef DGM_PARALLEL
    DGM::Comm::World.reset( new MpiComm( &argc, &argv ) );
#else
    DGM::Comm::World.reset( new SerialComm() );
#endif

    ArgList args( &argc, &argv );
    Table params;

    // set default values
    string ctl1 = "ctl1";
    string ctl2 = "ctl2";
    double aeps = 1.0e-12;
    double reps = 1.0e-8;
    params["ctl1"] = ctl1;
    params["ctl2"] = ctl2;
    params["aeps"] = aeps;
    params["reps"] = reps;

    parse_args( args, params );

    Stopwatch cpu;
    cpu.start();

    ctl1 = (string)params["ctl1"];
    ctl2 = (string)params["ctl2"];
    aeps = params["aeps"];
    reps = params["reps"];

    try {
      Reo::OptProblem problem( args, params );
      Comm::World->cout() << "dgm_cdiff:  " << ctl1 << " - " << ctl2 << endl;
      status = numeric_cast<int>(problem.diff(ctl1,ctl2,aeps,reps));
    }
    catch(...) {
      try {
        // see if Peopt problem
        params["genparams"] = 0;
        int genparams = params["genparams"];
        peopt::setupAndSolve<Reo::OptProblem, peopt::ReoParams,
          peopt::ReoManipulator<Reo::OptProblem, peopt::ReoParams> >
          p(args,params,genparams,args.back(), true);
          DGM::MultiOptProblem<Reo::OptProblem> problem = p.problem();
          Comm::World->cout() << "dgm_cdiff:  "<<ctl1<<" - "<<ctl2<< endl;
          status = problem.diff(ctl1, ctl2, aeps, reps);
      }
      catch (...) {
        assert(0 /* unknown problem type */);
      }
    }

    if (Comm::World->Master()) {
      //cout << "Total run time:  " << cpu.stop() << endl;
      if (status)
        cout << "Found differences. status = "
             << hex << showbase << status << endl;
      else
        cout << "No differences found." << endl;
    }
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
      if (name == "-c1") {
        li.push_back(a);
        value = *(++a);
        params["ctl1"] = value;
        li.push_back(a);
      } else if (name == "-c2") {
        li.push_back(a);
        value = *(++a);
        params["ctl2"] = value;
        li.push_back(a);
      } else if (name == "-aeps") {
        li.push_back(a);
        value = *(++a);
        params["aeps"] = atof(value.c_str());
        li.push_back(a);
      } else if (name == "-reps") {
        li.push_back(a);
        value = *(++a);
        params["reps"] = atof(value.c_str());
        li.push_back(a);
      } else if (name == "-help") {
        params["showUsage"] = 1;
        showUsage("dgm_cdiff.exe");
      }
    }
  }
  // remove tagged arguments
  for ( list< DGM::ArgList::iterator >::iterator a=li.begin();
        a!=li.end(); a++) args.erase(*a);

  // make sure that enough arguments remain
  if (args.size() < 2) {
    showUsage("dgm_cdiff.exe");
    throw DGM::exception("Insufficient number of arguments");
  }
}

/** If there is an error in the input argument list, this routine prints the
    correct usage information. */
void showUsage(const string& code) {
  cerr << "================================================================\n"
       << "Discontinuous Galerkin Control Diff\n"
       << "================================================================\n"
       << "Usage: \t\t" << code << " -c1 <ctl1> -c2 <ctl2> run_name\n"
       << "----------------------------------------------------------------\n"
       << "Options: " << '\t' << "Description\n"
       << "================================================================\n"
       << "-c1      " << '\t' << "First control file (.ctl)\n"
       << "-c2      " << '\t' << "Second control file (.ctl)\n"
       << "-aeps    " << '\t' << "Absolute tolerance\n"
       << "-reps    " << '\t' << "Relative tolerance\n"
       << "-help    " << '\t' << "Detailed help\n"
       << "----------------------------------------------------------------\n";
}
