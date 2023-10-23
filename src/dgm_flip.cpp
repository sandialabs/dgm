/*=============================================================================
  Title:      Discontinuous Galerkin Trace Flipper

  Author:     S. Scott Collis
              Scalable Algorithms
              Sandia National Laboratories
              Albuquerque, NM 87175-1320
              (505) 284-1123
              sscoll@sandia.gov

  Copyright:  Sandia National Laboratories
=============================================================================*/

/** \file dgm_flip.cpp
    \brief File containing the main program for DGM flip. */

// system libraries
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <list>
using namespace std;

// CMC libraries
#include "Stopwatch.hpp"
#include "Vector.hpp"
using CMC::Stopwatch;

// DGM libraries
#include "Comm.hpp"
#ifdef DGM_PARALLEL
#include "MpiComm.hpp"
#else
#include "SerialComm.hpp"
#endif
#include "ArgList.hpp"
#include "Table.hpp"
using namespace DGM;

// forward declarations
void parse_args( DGM::ArgList &args, Table &params );
void showUsage( const string& code );

int main(int argc, char *argv[]) {
  int status = 0;
  try {
#ifdef DGM_PARALLEL
    DGM::Comm::World.reset( new DGM::MpiComm( &argc, &argv ) );
#else
    DGM::Comm::World.reset( new DGM::SerialComm() );
#endif

    ArgList args( &argc, &argv );
    Table params;

    // set default values
    int n1(0), n2(0);
    params["n1"] = n1;
    params["n2"] = n2;

    parse_args( args, params );

    Stopwatch cpu;
    cpu.start();

    n1 = params["n1"];
    n2 = params["n2"];

    cout << "transp n1="<<n1<<" n2="<<n2<<" "<< endl;

    // now read in the trace.bin and flip it
    CMC::Vector<float,size_t> f(n1*n2);
    ifstream bin;
    bin.open("trace.bin", ifstream::in);
    bin.read(reinterpret_cast<char*>(f.data()), sizeof(float)*f.size());
    bin.close();
    CMC::Vector<float,size_t> r(n1*n2);
    for (size_t j=0; j<(size_t)n2; j++) {
      for (size_t i=0; i<(size_t)n1; i++) {
        const size_t er=i+j*n1;
        const size_t ef=n1-(i+1)+j*n1;
        cout << er << " " << ef << endl;
        r[er] = f[ef];
      }
    }
    ofstream bout;
    bout.open("t.bin", ofstream::out);
    bout.write(reinterpret_cast<const char*>(r.data()), sizeof(float)*r.size());
    bout.close();

    DGM::Comm::World->cout() << "Total run time:  " << cpu.stop() << endl;
  }
  catch (int x) {
    //DGM::Comm::World->cout() << "Caught integer exception: " << x << endl;
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

/// Parse the arguments for this driver
void parse_args( DGM::ArgList &args, Table &params ) {
  string name, value;
  list< DGM::ArgList::iterator > li;
  for ( DGM::ArgList::iterator a = args.begin(); a != args.end(); a++ ) {
    if ( (*a)[0] == '-' ) {
      name = *a;
      if (name == "-n1") {
        li.push_back(a);
        value = *(++a);
        params["n1"] = value;
        li.push_back(a);
      } else if (name == "-n2") {
        li.push_back(a);
        value = *(++a);
        params["n2"] = value;
        li.push_back(a);
      } else if (name == "-help") {
        params["showUsage"] = 1;
        showUsage("dgm_flip.exe");
      }
    }
  }
  // remove tagged arguments
  for ( list< DGM::ArgList::iterator >::iterator a=li.begin();
        a!=li.end(); a++) args.erase(*a);

  // make sure that enough arguments remain
  if (args.size() < 1) {
    showUsage("dgm_flip.exe");
    throw DGM::exception("Not enough arguments");
  }
}

/// Show the program usage
void showUsage(const string& code) {
  cerr << "================================================================\n"
       << "Discontinuous Galerkin trace flipper\n"
       << "================================================================\n"
       << "Usage: \t\t" << code << " [Options] -n1 int -n2 int             \n"
       << "----------------------------------------------------------------\n"
       << "Options: " << '\t' << "Description\n"
       << "================================================================\n"
       << "-help    " << '\t' << "Detailed help\n"
       << "----------------------------------------------------------------\n";
}
