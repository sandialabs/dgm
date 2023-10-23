#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

#include "mpi.h"
#include "mpio.h"

int main(int argc, char *argv[]) {
  
  int num, id;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &num);
  MPI_Comm_rank(MPI_COMM_WORLD, &id);
  cout << "Running on " << num << " processors." << endl;

  char *jobid, *run_cmd;
  char buffer[BUFSIZ];
  FILE *ptr;
 
  run_cmd = (char *)malloc(100 * sizeof(char));

  //  sprintf(run_cmd,"/bin/ls");
  jobid = getenv("PBS_JOBID");
  fprintf(stdout,"jobid = %s\n",jobid);

  sprintf(run_cmd,"/usr/local/pbs/bin/qstat -f %s\n",jobid);

  fprintf(stderr,"Running: %s\n",run_cmd);

  ptr = popen( run_cmd, "r" );

  while (fgets(buffer, BUFSIZ, ptr) != NULL) {
    buffer[strlen(buffer)-1] = '\0';
    fprintf(stderr,"Process: (%d), Buffer line: (%s)\n",id,buffer);
  }
  pclose(ptr);
 
  MPI_Finalize();
}
