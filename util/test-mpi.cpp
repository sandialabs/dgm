/** \file   test-mpi.cpp
    \brief  A simple MPI test program
    \author Scott Collis
**/

#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <mpi.h>

using namespace std;

namespace {
void error (const char *m, const int stat) {
   cerr<<"Error returned from "<<m<<":"<<stat<<endl;
   abort();
}
}

int main ( int argc, char *argv[]) {

  char nname[] = "Test_File";
  {
    ofstream F(nname);
    F<<"01234567890123456789";
    F.close();
  }

  const int ne=2;
  vector<int> L(ne);
  vector<int> D(ne);

  // Make it easy to switch
#if 1
  D[0] = 5; L[0] = 3;
  D[1] = 0; L[1] = 5;
#else
  D[0] = 0; L[0] = 5;
  D[1] = 5; L[1] = 3;
#endif

  int s=0; for (size_t j=0; j<L.size(); j++) s+=L[j];
  vector<char> C(s,'X');

  char native[] = "native";
  MPI_File     fh;
  MPI_Info     info;
  MPI_Status   status;
  MPI_Datatype filetype;
  const MPI_Offset disp = 0;

  if (int stat = MPI_Init(&argc, &argv))
    error("MPI_Init",        stat);
  if (int stat = MPI_Info_create(&info))
    error("MPI_Info_create", stat);
  if (int stat = MPI_File_open(MPI_COMM_WORLD,
                               nname,
                               MPI_MODE_RDWR|MPI_MODE_CREATE,
                               info,
                               &fh))
    error("MPI_File_open",   stat);
  if (int stat = MPI_Type_indexed(ne,
                                  &*L.begin(),
                                  &*D.begin(),
                                  MPI_CHAR,
                                  &filetype))
    error("MPI_Type_indexed", stat);
  if (int stat = MPI_Type_commit(&filetype))
    error("MPI_Type_commit",  stat);
  if (int stat = MPI_File_set_view(fh,
                                   disp,
                                   MPI_CHAR,
                                   filetype,
                                   native,
                                   info))
    error("MPI_File_set_view",stat);
  if (int stat = MPI_File_read_all(fh,
                                   &*C.begin(),
                                   s,
                                   MPI_CHAR,
                                   &status))
    error("MPI_File_read_all",stat);
  if (int stat = MPI_Type_free(&filetype))
    error("MPI_Type_free",    stat);
  if (int stat = MPI_File_close(&fh))
    error("MPI_File_close",   stat);
  if (int stat = MPI_Info_free(&info))
    error("MPI_Info_free",    stat);
  if (int stat = MPI_Finalize())
    error("MPI_Finalize",     stat);

  cout <<" Result of read:'";
  for (size_t j=0; j<C.size(); j++) cout << C[j];
  cout << "'" << endl;
  return 0;
}
