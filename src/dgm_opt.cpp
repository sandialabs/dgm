/*=============================================================================
  Title:      Optimal Control Solver using Discontinuous Galerkin Method

  Author:     S. Scott Collis
              Scalable Algorithms (1416)
              Sandia National Laboratories
              Albuquerque, NM 87175-1320
              (505) 284-1123
              sscoll@sandia.gov

  Copyright:  (c)2003 Rice University and
              (c)2008 Sandia National Laboratories
              (c)2014 Sandia National Laboratories
=============================================================================*/

/** \file dgm_opt.cpp
    \brief File containing the main program for DGM Optimization solver

    This is the DGM optimimization solver supporting hybrid, two- and
    three-dimensional discretizations for: advection-diffusion, Burgers,
    Euler, Linearized Euler, Navier-Stokes and Linearized Navier-Stokes
    equations.

    Copyright:  (c)2003 Rice University and
                (c)2008, 2014 Sandia National Laboratories

    Author:     Scott Collis,
                Scalable Algorithms,
                Sandia National Laboratories,
                Albuquerque, NM 87175-1320,
                (505) 284,1123,
                sscoll@sandia.gov
*/

// system libraries
#if defined(DGM_USE_FENV) || defined(DGM_DISABLE_DENORMS)
#include <fenv.h>
#if defined(__x86_64__) && !defined(__APPLE__)
// These are needed to turn off denormals on x86 processors when not APPLE
#include <xmmintrin.h>
#include <pmmintrin.h>
#endif
#endif
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <list>
#include <exception>
using namespace std;

// boost libraries
#include "boost/numeric/conversion/cast.hpp"
using boost::numeric_cast;

// DGM libraries
#include "Comm.hpp"
#ifdef DGM_PARALLEL
#include "MpiComm.hpp"
#else
#include "SerialComm.hpp"
#endif
#include "Format.hpp"
#include "Memory.hpp"
#include "ArgList.hpp"
#include "Utilities.hpp"
using namespace DGM;

// Reo libraries
#include "ReoInfo.hpp"
#include "ReoOptProblem.hpp"

// CMC libraries
#include "Stopwatch.hpp"
using CMC::Stopwatch;

#ifdef DGM_USE_KOKKOS
#include "GpGpu.hpp"
#endif

// Forward declarations

/// Manage command line inputs
void parse_args( DGM::ArgList &args, DGM::Table &params );

/// Printout the correct usage
void showUsage( const string& code );

/// The main DGM Optimization driver
/** Manage command line inputs, create the parallel process(es) and construct
    the flow problem */
int main(int argc, char *argv[]) {
  int status(0);
  try {
    DGM::Format sci(4,10,'e');
#ifdef DGM_USE_KOKKOS
    // initialize kokkos
    DGM::GpGpu::initialize_gpu gpu;
#endif
#ifdef DGM_PARALLEL
    Comm::World.reset( new MpiComm(&argc,&argv) );
    Comm::World->cout() << "Running on " << Comm::World->NumProc()
                        << " processors..." << std::endl;
#else
    Comm::World.reset( new SerialComm() );
#endif
    Comm::Interupt();
    const DGM::Comm::Ptr &comm(Comm::World);
    std::ostream &out(comm->cout());
    Reo::Info info;
    info.name(out);

    comm->cout() << "Started Reo Optimal Control Solver on "
                 << DGM::dateTime() << endl;

    //
    // Output additional information about the system
    //
    comm->cout()<<"  Running on: "<<info.hostname()<<endl;
    comm->cout()<<"  Compiled with: "<<info.compiler()<<endl;
    comm->cout()<<"  System set to: "<<info.system()<<endl;
    //
    // Flush denormals to zero if requested
    //
#if defined(DGM_USE_FENV) || defined(DGM_DISABLE_DENORMS)
    comm->cout()<<"  Flushing denormals to zero..."<<endl;
#ifdef __APPLE__
    if (fesetenv(&_FE_DFL_DISABLE_SSE_DENORMS_ENV)) {
      comm->cout()<<"ERROR setting FE environrment to disable subnormals"<<endl;
      comm->abort();
    }
#elif defined(__x86_64__)
    _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
    _MM_SET_DENORMALS_ZERO_MODE(_MM_DENORMALS_ZERO_ON);
#else
    comm->cout()<<"WARNING: Unable to flush denormals to zero for "
                  "this architecture..."<<endl;
#endif
#endif
    ArgList args( &argc, &argv );
    Table params;
    parse_args( args, params);

    params["pause"] = false;
    parse_args( args, params );
    const bool pause = params["pause"];
    if (comm->Master() && pause) {
      cout << "Press enter to continue ";
      cin.ignore(numeric_limits<streamsize>::max(),'\n');
    }
    comm->Barrier();

#ifdef DGM_TEST_MEMORY
    // Test the DGM::Memory class
    DGM::Memory mem("Mb");
    out<<mem<<endl;
    // Determine the largest chuck of memory that you can allocate
    int ex = (int) log2(mem.avail()) - (int) log2(sizeof(size_t));
    out<<"Attempting to allocate 2^"<<ex<<" bytes"<<endl;
    // test memory allocation and exceptions
    size_t n = (size_t) pow(2.0,ex);
    size_t *myarray = new size_t[n];
    out<<"Memory allocated, now initializing..."<<endl;
    for (size_t i=0; i<n; i++) myarray[i]=i;
    out << "Allocated " << n*sizeof(size_t)/pow(2.0,30) << " Gb = "
        << sizeof(size_t)*myarray[n-1] << " bytes" << endl;
    out<<mem<<endl;
#endif

#ifdef DGM_TEST_LOCP
    // Test the DGM Linearized Optimal Control Problem
    out<<"===============================================================\n"
       <<"Making dgm_ocp...\n"
       <<"===============================================================\n";
    Reo::OptProblem ocp( args, params, DGM::Comm::World );
    out<<"===============================================================\n"
       <<"Making dgm_linear_ocp...\n"
       <<"===============================================================\n";
    Reo::OptProblem locp( &ocp, args, params, DGM::Comm::World );
    out<<"===============================================================\n";
    out<<"Performing forward solve"<<std::endl;
    out<<"===============================================================\n";
    double J = ocp.computeState( ocp.control, ocp.objective );
    out<<"===============================================================\n";
    out<<"Performing adjoint solve"<<std::endl;
    out<<"===============================================================\n";
    ocp.computeAdjoint( ocp.control, ocp.objective );
    out<<"===============================================================\n";
    out<<"Performing linearized forward solve"<<endl;
    out<<"===============================================================\n";
    double lJ = locp.computeState( locp.control, locp.objective );
#if 0
    out<<"===============================================================\n";
    out<<"Performing linearized adjoint solve"<<endl;
    out<<"===============================================================\n";
    locp.computeAdjoint( locp.control, locp.objective );
#endif
    out << "You have tested the linearized "
      "optimal control problem, now exiting..." << std::endl;
#else
    // Normal execution
    Reo::OptProblem ocp( args, params, Comm::World );
    Stopwatch cpu;
    cpu.start();
    status = numeric_cast<int>(ocp.solve());
    out << "Total run time: " << sci(cpu.stop())
                              << " sec = " << sci(cpu.stop()/3600.0)
                              << " hr " << endl;
#endif
    out << "Completed Reo_opt on " << DGM::dateTime() << endl;
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
      if (name == "-help") {
        params["showUsage"] = 1;
        showUsage("dgm_opt.exe");
      } else if (name == "-defines") {
        if (DGM::Comm::World->Master()) {
          std::ofstream def("defines.out");
          DGM::Comm::information.defines(def);
        }
      } else if (name == "-pause") {
        params["pause"] = true;
      }
    }
  }
  // remove tagged arguments
  for ( list< DGM::ArgList::iterator >::iterator a=li.begin();
        a!=li.end(); a++) args.erase(*a);

  // make sure that enough arguments remain
  if (args.size() < 2) {
    showUsage("dgm_opt.exe");
    throw DGM::exception("Not enough arguments");
  }
}

/** If there is an error in the input argument list, this routine prints the
    correct usage information. */
void showUsage(const string& code) {
  DGM::Comm::World->cout()
    << "================================================================\n"
    << "Discontinuous Galerkin Optimal Control Solver                   \n"
    << "================================================================\n"
    << "Usage:  \t" << code << " [Options] run_name                     \n"
    << "----------------------------------------------------------------\n"
    << "Options: " << '\t' << "Description                              \n"
    << "----------------------------------------------------------------\n"
    << "-help    " << '\t' << "Detailed help                            \n"
    << "-pause   " << '\t' << "Pause execution for debugging            \n"
    << "-defines " << '\t' << "Show compile-time defines                \n"
    << "----------------------------------------------------------------\n";
}
