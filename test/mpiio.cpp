// system includes
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <cassert>
#include <cmath>
#include <vector>
using namespace std;

// MPI includes
#include "mpi.h"

/// MPI-IO Test Program
/** This does a simple test of MPI-IO that looks kind of like what the DGM
    library does.
    How to build:
    \verbatim
    mpicxx -O2 mpiio.cpp -o mpiio
    \endverbatim
    How to run:
    \verbatim
    h-3.2$ mpiexec -n 1 ~/dgm/src/mpiio; od -e mpi.out
    0000000   0.000000000000000e+00   1.000000000000000e+00
    0000020   2.000000000000000e+00   3.000000000000000e+00
    0000040   4.000000000000000e+00   5.000000000000000e+00
    0000060   6.000000000000000e+00   7.000000000000000e+00
    0000100   8.000000000000000e+00   9.000000000000000e+00
    0000120   1.000000000000000e+01   1.100000000000000e+01
    0000140   1.200000000000000e+01   1.300000000000000e+01
    0000160   1.400000000000000e+01   1.500000000000000e+01
    0000200   1.600000000000000e+01   1.700000000000000e+01
    0000220   1.800000000000000e+01   1.900000000000000e+01
    0000240   2.000000000000000e+01   2.100000000000000e+01
    0000260   2.200000000000000e+01   2.300000000000000e+01
    0000300
    \endverbatim
*/
int main(int argc, char *argv[]) {

  size_t gne=200;           // number of global elements
  const int qtot=10*10*10;  // number of data points per element
  double t1, t2;            // mpi timers

  MPI_Comm mpi_comm(MPI_COMM_WORLD);
  MPI_Init(&argc, &argv);

  assert( sizeof(ssize_t) == sizeof(MPI_Aint) );

  t1 = MPI_Wtime();
  if (argc>2) {
    cerr << "Usage:  mpiio [number-elements]" << endl;
    MPI_Abort(mpi_comm,1);
    exit(1);
  }
  if (argc==2) {
    gne = atol(argv[1]);
  }

  int pid, numproc;
  MPI_Comm_rank(mpi_comm, &pid);
  MPI_Comm_size(mpi_comm, &numproc);

  if (pid==0) cout << "Running on " << numproc << " processor(s)..." << endl;

  if (numproc>gne) {
    if (pid==2) cerr << "Error:  number of processors > number of elements" 
                     << endl;
    MPI_Abort(mpi_comm,2);
  }
  
  assert((size_t)numproc<=gne);

  if (pid==0) cout << "Using " << gne << " global elements ";

  size_t start = (size_t)pid * (size_t)gne / (size_t)numproc;
  size_t stop = (size_t)(pid+1)*(size_t)gne / (size_t)numproc;
  int ne = (int)((size_t)stop - (size_t)start);
  if (pid==0) cout << "with " << ne << " local elements per rank" << endl;
  if (ne<0) {
    cerr << pid << ": overflow in number of elements" << endl;
    MPI_Abort(mpi_comm,3);
  }
  vector<size_t> eid(ne); 
  for (int e=0; e<ne; e++) eid[e] = start + e;
#if 0
  vector<int> part(gne);
  for (int i=0; i<numproc; i++) {
    for (size_t k=(size_t)i*(size_t)gne/(size_t)numproc; 
         k<(size_t)(i+1)*(size_t)gne/(size_t)numproc; ++k) {
      part[k] = i;
    }
  }
#endif

#ifdef MPIIO_USE_INDEXED
  vector<size_t> gdisp(gne);
  gdisp[0] = 0;
  for(size_t k=1; k<gne; k++)
    gdisp[k] = gdisp[k-1] + qtot;
  const size_t glen = gdisp[gne-1] + qtot;
  vector<int> disp(ne);
  vector<int> len(ne);
  for (size_t e=0; e<ne; e++) {
    disp[e] = gdisp[eid[e]];
    len[e] = qtot;
  }
#else
#ifdef MPIIO_USE_GLOBAL_DISP
  vector<MPI_Aint> gdisp(gne);
  gdisp[0] = 0;
  for(size_t k=1; k<gne; k++)
    gdisp[k] = gdisp[k-1] + sizeof(double)*qtot;
  const MPI_Aint glen = gdisp[gne-1] + sizeof(double)*qtot;
  vector<MPI_Aint> disp(ne);
  vector<int> len(ne);
  for (size_t e=0; e<ne; e++) {
    disp[e] = gdisp[eid[e]];
    len[e] = qtot;
  }
#else
  const size_t glen = gne*(size_t)qtot*sizeof(double);     // bytes 
  vector<MPI_Aint> disp(ne);
  vector<int> len(ne);
  for (size_t k=start, e=0; k<stop; k++, e++) {
    const size_t gdisp = k*sizeof(double)*qtot;
    disp[e] = gdisp;
    len[e] = qtot;
  }
#endif
#endif
  //if (pid==numproc-1) cout << "disp[ne-1] = " << disp[ne-1] << endl;
  if (disp[ne-1]<0) cout << pid << ": WARNING:  integer overflow" << endl;

  size_t ndof = (size_t)ne*(size_t)qtot;
  size_t bytes = ndof*sizeof(double);
  double gbytes = (double)ndof*(double)sizeof(double)/(double)pow(2.0,30);
  if (pid==0) cout << "Allocating " << ndof << " doubles/rank\n" 
                   << "         = " << bytes << " bytes/rank\n" 
                   << "         = " << gbytes << " GB/rank" << endl;
  vector<double> x(ndof);
  for(size_t e=0; e<ne; ++e) {
    for(size_t q=0; q<qtot; ++q) {
      const size_t i = q + e*qtot;
      x[i] = double(eid[e]); 
    }
  }
  if (pid==0) cout << "Allocated and initialized" << endl;
  gbytes = (double)glen/(double)pow(2.0,30);
  string name="mpi.out";
  if (pid==0) cout << "Writing a total of " << gbytes << " GB to " << name 
                   << endl;

  MPI_Offset headlen = 0;

  // Optionally write out a header
#ifdef MPIIO_ADD_HEADER
  if (pid==0) {
    ofstream fs(name.c_str());
    fs<<"This is the header, please do not overwrite"<<endl;
    headlen = fs.tellp();
    fs.close();
    //cout << "Header length = " << headlen << endl;
  }
  MPI_Bcast( &headlen, 1, MPI_Offset, 0, mpi_comm );
#endif

  // Now for the MPI-IO stuff

  char native[] = "native";
  int stat;

  MPI_File fh;
  MPI_Status status;
  MPI_Datatype filetype;
  MPI_Offset offset = headlen;

#if MPIIO_VERBOSE>0
  cout << pid << ": offset = " << offset << endl; 
#endif

  if (pid==0) cout << "Starting MPI-IO" << endl;

#ifdef MPIIO_USE_INDEXED
  stat = MPI_Type_indexed( ne, &(len[0]), &(disp[0]), MPI_DOUBLE, &filetype);
  if (stat) cout << pid << ":1:stat = " << stat << endl;
#else
  if (pid==0) cout << "Create hindexed filetype" << endl;
  stat = MPI_Type_create_hindexed( ne, &len[0], &disp[0], MPI_DOUBLE, 
                                   &filetype);
  if (stat) cout << pid << ":1:stat = " << stat << endl;
#endif
  stat = MPI_Type_commit( &filetype );
  if (stat) cout << pid << ":2:stat = " << stat << endl;

#ifndef MPIIO_ADD_HEADER
  // Always delete the file so make sure that it is not too big
  MPI_File_delete( const_cast<char *>(name.c_str()), MPI_INFO_NULL );
#endif
  t2 = MPI_Wtime();
  if (pid==0) cout << "Startup time = " << t2-t1 << " sec" << endl;
  if (pid==0) cout << "Starting MPI_File_open" << endl;
  stat = MPI_File_open( mpi_comm, const_cast<char *>(name.c_str()), 
                        MPI_MODE_WRONLY | MPI_MODE_CREATE,
                        MPI_INFO_NULL, &fh );
  if (stat) cout << pid << ":3:stat = " << stat << endl;
  t1 = MPI_Wtime();
  if (pid==0) cout << "MPI_File_open took = " << t1-t2 << " sec" << endl;

  stat = MPI_File_set_view(fh, offset, MPI_DOUBLE, filetype, native, 
                           MPI_INFO_NULL);
  if (stat) cout << pid << ":4:stat = " << stat << endl;

  if (pid==0) cout << "Starting collective write" << endl;
  stat = MPI_File_write_all(fh, &(x[0]), x.size(), MPI_DOUBLE, &status);
  if (stat) cout << pid << ":5:stat = " << stat << endl;

  if (pid==0) cout << "Finished collective write" << endl;
  stat = MPI_File_close(&fh);
  if (stat) cout << pid << ":6:stat = " << stat << endl;
  if (pid==0) cout << "Finished file close" << endl;

  stat = MPI_Type_free( &filetype );
  if (stat) cout << pid << ":7:stat = " << stat << endl;

  t2 = MPI_Wtime();
  if (pid==0) cout << "Write took = " << t2-t1 << " sec"
                   << " at " << gbytes/(t2-t1) << " GB/sec" << endl;

  MPI_Finalize();

  if (pid==0) cout << "Completed MPI-IO test on file " << name << endl;
  if (pid==0) cout << "Use `od -e mpi.out` to view the file contents" << endl;

  return 0;
}
