/** \file test_mpiio.cpp
    \brief Models and tests the MPI-IO routines used by DGM

    Simple test of MPI-IO for a DGM restart file format

    To build do something like:
    
    mpicxx -I$HOME/local/atlas/include test_mpiio.cpp -I$HOME/dgm/src \
    -L$HOME/local/atlas/lib -llapack -lcblas -latlas -o test_mpiio -D GCC4
    
    Run a test like:
    
    mpiexec -n 1  test_mpiio
    mpiexec -n 16 test_mpiio; 
    diff restart.1 restart.16;
    
    Author:     S. Scott Collis
    Copyright:  (c)2011 Sandia National Laboratories
    License:    See Licence.txt in the main distribution directory
**/

// system includes
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

// include MPI
#include "mpi.h"

// include CMC
#include "Vector.hpp"
#include "Matrix.hpp"

typedef CMC::Vector<double,int> dVector;
typedef CMC::Vector<int,int> iVector;
using namespace CMC;

int main( int argc, char *argv[]) {
  int ncpus, pid;

  MPI_Init( &argc, &argv);
  MPI_Comm mpi_comm(MPI_COMM_WORLD);
  MPI_Comm_size(MPI_COMM_WORLD, &ncpus);
  MPI_Comm_rank(MPI_COMM_WORLD, &pid);
  if (pid==0) cout << "Running on " << ncpus << " processors." << endl;

  int global_ne = 441;  // total number of elements

  if (argc>2) {
    cerr << "Usage: test_mpiio [number-elements]" << endl;
    MPI_Abort(mpi_comm,1);
    exit(1);
  }
  if (argc==2) {
    global_ne = atoi(argv[1]);
  }

 if (pid==0) cout << "Using " << global_ne << " global elements" << endl;

  stringstream buffer;
  buffer << "restart." << ncpus;
  string fname(buffer.str().c_str());

  int ne;                     // local number of elements
  int start, stop;
  start = pid * global_ne / ncpus;
  stop  = (pid+1) * global_ne / ncpus;
  ne = stop - start;
  iVector proc_eid(ne);
  for (int e=0; e<ne; e++) proc_eid[e] = start + e;

  const int qtot = 81;        // element size (doubles)
  iVector global_disp(global_ne);
  global_disp[0] = 0;
  for (int e=1; e<global_ne; e++)
    global_disp[e] = global_disp[e-1] + qtot;
  int glen = global_disp[global_ne-1] + qtot;
  
  iVector proc_len(ne), proc_disp(ne);
  for (int e=0; e<ne; e++) {    
    proc_disp[e] = global_disp[proc_eid[e]];
    proc_len[e]  = qtot;
  }
  
  cout << pid << ", proc_disp[0] = " << proc_disp[0] << endl;

  dVector data(ne*qtot);  // local element data
  for (int i=0; i<data.size(); i++) data[i] = double(i);

  for (int e=0; e<ne; ++e) {
    for (int q=0; q<qtot; ++q) {
      const int i = q + e*qtot;
      data[i] = double( proc_eid[e] );
    }
  }

  int stat;
  char native[] = "native";
  MPI_File fh;
  MPI_Status status;
  MPI_Datatype filetype, inttype;
  MPI_Offset disp=0, offset;
  
  MPI_Type_indexed( ne, proc_len.data(), proc_disp.data(), 
		    MPI_DOUBLE, &filetype);
  MPI_Type_commit( &filetype );

  iVector ilen(ne); ilen = 1;
  MPI_Type_indexed( ne, ilen.data(), proc_eid.data(), MPI_INT, &inttype );
  MPI_Type_commit( &inttype );

  if (stat = MPI_File_open(MPI_COMM_WORLD, const_cast<char *>(fname.c_str()), 
                           MPI_MODE_WRONLY | MPI_MODE_CREATE, 
                           MPI_INFO_NULL, &fh)) {
    cout << pid << " error " << stat << " in opening file = " << fname << endl;
    MPI_Abort(MPI_COMM_WORLD,stat);
  }

  // write global length
  MPI_File_set_view(fh, disp, MPI_INT, MPI_INT, native, MPI_INFO_NULL);
  if(stat = MPI_File_write_all(fh, &glen, 1, MPI_INT, &status)) {
    cout << pid << " error " << stat << " in writing global length" << endl;
    MPI_Abort(MPI_COMM_WORLD,stat);
  }
  disp += sizeof(int);

  // write partition data lengths
  MPI_File_set_view(fh, disp, MPI_INT, inttype, native, MPI_INFO_NULL);
  if (stat = MPI_File_write_all(fh, proc_len.data(), ne, MPI_INT, &status)) {
    cout << pid << " error " << stat << " in writing data lengths" << endl;
    MPI_Abort(MPI_COMM_WORLD,stat);
  }
  disp += global_ne*sizeof(int);
  
  // write partition data displacements
  MPI_File_set_view(fh, disp, MPI_INT, inttype, native, MPI_INFO_NULL);
  if (stat = MPI_File_write_all(fh, proc_disp.data(), ne, MPI_INT, &status)) {
    cout << pid << " error " << stat << " in writing data displacements"<<endl;
    MPI_Abort(MPI_COMM_WORLD,stat);
  }
  disp += global_ne*sizeof(int);
  
  // write the data
  MPI_File_set_view(fh, disp, MPI_DOUBLE, filetype, native, MPI_INFO_NULL);
  if (stat = MPI_File_write_all(fh, data.data(), data.size(), 
                                MPI_DOUBLE, &status)) {
    cout << pid << " error " << stat << " in writing data "<<endl;
    MPI_Abort(MPI_COMM_WORLD,stat);
  }
  disp += glen*sizeof(double);
  
  // get current position
  MPI_File_get_position(fh, &offset);
  MPI_File_get_byte_offset(fh, offset, &disp);
  
  cout << pid <<", offset in extent (double) = " << offset 
       << ", absolute displacement in bytes = "<< disp << endl;
  
  MPI_File_close(&fh);
  
  MPI_Finalize();
}

