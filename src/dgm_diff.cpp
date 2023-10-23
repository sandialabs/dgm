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

/** \file dgm_diff.cpp
    \brief File containing the main program for DGM difference. */

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

#if defined(DGM_USE_KOKKOS)
#include "GpGpu.hpp"
#endif

// Reo libraries
#include "ReoProblem.hpp"
#include "ReoInfo.hpp"

// forward declarations

/// Manage command line inputs
void parse_args( DGM::ArgList &args, DGM::Table &params );

/// Printout the correct usage
void showUsage( const string& code );

/// The main DGM difference driver program.
/** Manage command line inputs, create the parallel process(es) and
    construct the DGM::Problem */
int main(int argc, char *argv[]) {
  using namespace DGM;
  int status;
  try {
#ifdef DGM_USE_KOKKOS
    // initialize kokkos
    DGM::GpGpu::initialize_gpu gpu;
#endif
#ifdef DGM_PARALLEL
    DGM::Comm::World.reset( new MpiComm( &argc, &argv ) );
    string suffix(""); if (DGM::Comm::World->NumProc()!=1) suffix="s";
    DGM::Comm::World->cout() << "Running DGM on "
                             << DGM::Comm::World->NumProc()
                             << " processor"<<suffix<<"..." << std::endl;
#else
    DGM::Comm::World.reset( new SerialComm() );
#endif
    DGM::Comm::Interupt();
    DGM::Comm::Ptr &comm(DGM::Comm::World);
    std::ostream &out(comm->cout());
    Reo::Info info;
    info.name(out);
    comm->cout()<< "Started Reo Diff(erence) on " << DGM::dateTime() << endl;
    comm->cout()<<"  Running on: "<<info.hostname()<<endl;
    comm->cout()<<"  Compiled with: "<<info.compiler()<<endl;
    comm->cout()<<"  System set to: "<<info.system()<<endl;

    ArgList args( &argc, &argv );
    Table params;

    // set default values
    string rst1 = "rst1";
    string rst2 = "rst2";
    double aeps = 1.0e-12;
    double reps = 1.0e-8;
    double meps = 0.0;
    params["rst1"] = rst1;
    params["rst2"] = rst2;
    params["aeps"] = aeps;
    params["reps"] = reps;
    params["meps"] = meps;

    parse_args( args, params );

    comm->cout() << "Starting Reo::Diff on " << DGM::dateTime() << endl;
    Reo::Problem problem( args, params );

    Stopwatch cpu;
    cpu.start();

    rst1 = (string)params["rst1"];
    rst2 = (string)params["rst2"];
    aeps = params["aeps"];
    reps = params["reps"];
    meps = params["meps"];

    comm->cout() << "DGM_diff:  " << rst1 << " - " << rst2 << endl;
    status = numeric_cast<int>(problem.diff(rst1,rst2,aeps,reps,meps));

    if (comm->Master()) {
      //cout << "Total run time:  " << cpu.stop() << endl;
      if (status)
        cout << "Found differences. status = "
             << hex << showbase << status << endl;
      else
        cout << "No differences found." << endl;
    }

    // explicitly invoke Mpi destructor via shared_ptr
#ifdef DGM_EXPLICIT_COMM_DESTRUCT
    DGM::Comm::World->Barrier();
#ifdef DGM_USE_TEUCHOS_RCP
    DGM::Comm::World.Teuchos::RCP<Comm>::~Teuchos::RCP();
#else
    DGM::Comm::World.boost::shared_ptr<DGM::Comm>::~shared_ptr();
#endif
#endif
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
#ifndef DGM_EXPLICIT_COMM_DESTRUCT
#ifdef OPEN_MPI
#if !((OMPI_MAJOR_VERSION <= 1) && (OMPI_MINOR_VERSION <= 8) && \
    (OMP_RELEASE_VERSION <= 4))
  DGM::Comm::World->cout()<<"Explicitly calling World::reset()"<<endl;
  DGM::Comm::World.reset();
#endif
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
      if (name == "-r1") {
        li.push_back(a);
        value = *(++a);
        params["rst1"] = value;
        li.push_back(a);
      } else if (name == "-r2") {
        li.push_back(a);
        value = *(++a);
        params["rst2"] = value;
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
      } else if (name == "-meps") {
        li.push_back(a);
        value = *(++a);
        params["meps"] = atof(value.c_str());
        li.push_back(a);
      } else if (name == "-help") {
        params["showUsage"] = 1;
        showUsage("dgm_diff.exe");
      }
    }
  }
  // remove tagged arguments
  for ( list< DGM::ArgList::iterator >::iterator a=li.begin();
        a!=li.end(); a++) args.erase(*a);

  // make sure that enough arguments remain
  if (args.size() < 2) {
    showUsage("dgm_diff.exe");
    throw DGM::exception("Insufficient number of arguments");
  }
}

/** If there is an error in the input argument list, this routine prints the
    correct usage information. */
void showUsage(const string& code) {
  cerr << "================================================================\n"
       << "Discontinuous Galerkin Diff\n"
       << "================================================================\n"
       << "Usage: \t\t" << code << " -r1 <rst1> -r2 <rst2> run_name\n"
       << "----------------------------------------------------------------\n"
       << "Options: " << '\t' << "Description\n"
       << "================================================================\n"
       << "-r1      " << '\t' << "First restart file (.rst)\n"
       << "-r2      " << '\t' << "Second restart file (.rst)\n"
       << "-aeps    " << '\t' << "Absolute tolerance\n"
       << "-reps    " << '\t' << "Relative tolerance\n"
       << "-meps    " << '\t' << "Maximum element relative tolerance\n"
       << "-help    " << '\t' << "Detailed help\n"
       << "----------------------------------------------------------------\n";
}
