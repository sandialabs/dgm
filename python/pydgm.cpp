// System libraries
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <list>
#include <exception>
using namespace std;

// DGM libraries
#include "DGM/Comm.hpp"
#include "DGM/SerialComm.hpp"
#ifdef DGM_PARALLEL
#include "DGM/MpiComm.hpp"
#endif
using namespace DGM;

#ifdef DGM_PARALLEL
//#warning "MPI enabled build..."
static void * dgm_makeMpiCommWorld(MPI_Comm comm) {
  DGM::Comm::World.reset( new DGM::MpiComm(comm) );
  return ((void *) (DGM::Comm::World.get()));
}
#endif

static void * dgm_makeSerialCommWorld() {
  DGM::Comm::World.reset( new DGM::SerialComm() );
  return ((void *) (DGM::Comm::World.get()));
}

// Returns a pointer to a shared pointer
static void * dgm_makeCommWorld(int *argc, char ***argv) {
#ifdef DGM_PARALLEL
  DGM::Comm::World.reset( new DGM::MpiComm(argc,argv) );
#else
  DGM::Comm::World.reset( new DGM::SerialComm() );
#endif
  return ((void *) (DGM::Comm::World.get()));
}
