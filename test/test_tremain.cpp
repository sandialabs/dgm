/*
  Program to test PBS tremain call

  To compile using ICC:

  icc -o test_tremain test_tremain.cpp ../src/Utilities.cpp \
  -I/usr/local/mpich-1.2.1..7b-intel/include -I/usr/local/pbs/include \
  -L/usr/local/mpich-1.2.1..7b-intel/lib -lmpich -L/usr/local/gm-1.5/lib \
  -lgm -L/usr/local/pbs/lib -lpbs

  g++ -o test_tremain test_tremain.cpp ../src/Utilities.cpp \
  -I/usr/local/mpich-1.2.1..7b-gnu/include -I/usr/local/pbs/include \
  -L/usr/local/mpich-1.2.1..7b-gnu/lib -lmpich -L/usr/local/gm-1.5/lib \
  -lgm -L/usr/local/pbs/lib -lpbs 

  Warning: This code does not work on the cluster (myrinet) if the pthread
  library is included.  The Myicom people say that this is fixed in GM-1.6 but
  not in the GM-1.5 library that we use.

  To compile on prandtl (without PBS-API):

  mpiCC -o test_tremain test_tremain.cpp ../src/Utilities.cpp 
*/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

#include "mpi.h"
#include "mpio.h"

#include "../src/Utilities.h"

int main(int argc, char *argv[]) {
  
  int num, id;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &num);
  MPI_Comm_rank(MPI_COMM_WORLD, &id);
  if (id==0) cout << "Running on " << num << " processors." << endl;

  // create a PBS timer object with a tolerance of 120 sec.
  JobStatus job(120);
  cout << "Time remaining: " << job.walltime_remaining() << endl;
  cout << "Job finished:   " << job.finished() << endl;
 
  MPI_Finalize();
}
