/*=============================================================================
  Title:      Discontinuous Galerkin Solver DAKOTA driver

  Author:     S. Scott Collis
              Scalable Algorithms
              Sandia National Laboratories
              Albuquerque, NM 87175-1320
              (505) 284-1123
              sscoll@sandia.gov

  Copyright:  Rice University and Sandia National Laboratories
=============================================================================*/

/** \file dgm_dak.cpp
    \brief File containing the main program for DGM-DAKOTA driver. */

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
#endif
#include "SerialComm.hpp"
#include "ArgList.hpp"
#include "OptProblem.hpp"

// CMC libraries
#include "Stopwatch.hpp"
using CMC::Stopwatch;

// DAKOTA includes
#include "system_defs.h"
#include "ParallelLibrary.H"
#include "CommandLineHandler.H" // might not be needed
#include "ProblemDescDB.H"
#include "DakotaStrategy.H"
#include "DakotaModel.H"

// DGM includes
#include "Dakota.hpp"

using namespace DGM;

// DAKOTA requires that this be defined in the global scope...why?
int write_precision = 10;

// forward declarations

/// Manage command line inputs
void parse_args( DGM::ArgList &args, Table &params );

/// Printout the correct usage
void showUsage( const string& code );

/// The main DGM-DAKOTA program
/** Manage command line inputs, create the parallel process(es) and construct
    the DAKOTA Direct Application Interface */
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

  ArgList args( &argc, &argv );
  Table params;
  parse_args( args, params );

  // put Dakota in it's own scope so that Dakota::ParallelLibrary is deleted
  // before DGM::Comm::World
  {

  // =========================================================================
  // start of DAKOTA stuff
  // =========================================================================

  //DGM::Comm::World->cout() << "MPI_COMM_WORLD = " << MPI_COMM_WORLD << endl;
  //DGM::Comm::World->cout() << "MPI_COMM_NULL = " << MPI_COMM_NULL << endl;

  Dakota::ParallelLibrary parallelLib;

  Dakota::ProblemDescDB probDescDB(parallelLib);

  // the last argument is the Dakota input file
  string name = args.back();
  const char* dakotaInput=name.c_str();
  const char* dakotaReadRestart = NULL;
  const char* dakotaWriteRestart = NULL;
  int         dakotaStopRestart = 0;

  probDescDB.manage_inputs(dakotaInput);

  parallelLib.specify_outputs_restart(NULL, NULL, dakotaReadRestart,
                                      dakotaWriteRestart, dakotaStopRestart);

  Dakota::Strategy selectedStrategy(probDescDB);

  Dakota::ModelList& models = probDescDB.model_list();

  for (Dakota::ModelLIter ml_iter = models.begin();
       ml_iter!=models.end(); ml_iter++) {

    Dakota::Interface& interface = ml_iter->interface();

    if (interface.interface_type() == "direct" &&
        contains(interface.analysis_drivers(), "dgm") ) {

      probDescDB.set_db_model_nodes(ml_iter->model_id());

      // make a DGM parallel communicated based on DAKOTA parallel config
      DGM::Comm *comm;
#ifdef DGM_PARALLEL
      const Dakota::ParallelLevel &ea_pl =
        ml_iter->parallel_configuration_iterator()->ea_parallel_level();
      // DAKOTA used to generate null communicators so make sure to build
      // a serial comm if that happens.
      if ( ea_pl.server_intra_communicator() != MPI_COMM_NULL ) {
        comm = new DGM::MpiComm( ea_pl.server_intra_communicator(),"dgm");
        comm->cout() << "Made new DGM::MpiComm" << endl;
      } else {
        comm = new DGM::SerialComm( "dgm" );
        comm->cout() << "Made new DGM::SerialComm" << endl;
      }
#else
      comm = new DGM::SerialComm( "dgm" );
#endif

      interface.assign_rep(new DGM::DirectApplicInterface
                           ( probDescDB, ml_iter->num_functions(),
                             args, params, comm), false);
    }
  }

  // Execute the strategy
  probDescDB.lock();
  selectedStrategy.run_strategy();

  // =========================================================================
  // end of DAKOTA stuff
  // =========================================================================

  }
#ifdef OPEN_MPI
#if !((OMPI_MAJOR_VERSION <= 1) && (OMPI_MINOR_VERSION <= 8) && \
    (OMP_RELEASE_VERSION <= 4))
  comm->cout()<<"Explicitly calling World::reset()"<<endl;
  DGM::Comm::World.reset();
#endif
#endif
  return DGM::SUCCESS;
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
    showUsage("dgm");
    DGM::Comm::World->exit(DGM::FAILURE);
  }
}

/** If there is an error in the input argument list, this routine prints the
    correct usage information. */
void showUsage(const string& code) {
  DGM::Comm::World->cout()
    << "================================================================\n"
    << "Discontinuous Galerkin Solver Interface to DAKOTA\n"
    << "================================================================\n"
    << "Usage:  \t" << code << " [Options] run_name \n"
    << "----------------------------------------------------------------\n"
    << "Options: " << '\t' << "Description\n"
    << "----------------------------------------------------------------\n"
    << "-help    " << '\t' << "Detailed help\n"
    << "----------------------------------------------------------------\n";
}
