/*
  Program to test PBS-API

  To compile using ICC:

  icc -o test_pbs test_pbs.cpp -I/usr/local/mpich-1.2.1..7b-intel/include \
  -I/usr/local/pbs/include -L/usr/local/mpich-1.2.1..7b-intel/lib -lmpich \
  -L/usr/local/gm-1.5/lib -lgm -L/usr/local/pbs/lib -lpbs

  To compile using GCC:

  g++ -o test_pbs test_pbs.cpp -I/usr/local/mpich-1.2.1..7b-gnu/include \
  -I/usr/local/pbs/include -L/usr/local/mpich-1.2.1..7b-gnu/lib -lmpich \
  -L/usr/local/gm-1.5/lib -lgm -L/usr/local/pbs/lib -lpbs

  Warning: This code does not work on the cluster (myrinet) if the pthread
  library is included.
*/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

#include "mpi.h"
#include "mpio.h"

extern "C" {
#include <pbs_error.h>
#include <pbs_ifl.h>
}

#include "../src/Utilities.h"

int main(int argc, char *argv[]) {
  
  int num, id;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &num);
  MPI_Comm_rank(MPI_COMM_WORLD, &id);
  if (id==0) cout << "Running on " << num << " processors." << endl;

#if 0
  string command="ls -C /scratch";
  cout << system( command.c_str() ) << endl;
#else
  if (id==0) {
    char *server;
    server = getenv("PBS_O_HOST");
    if (server==NULL) {
      cerr << "Cannot get PBS_O_HOST from the environment" << endl;
      exit(-1);
    }
    //cout << "PBS_SERVER = " << server << endl;
    
    char *jobid;
    jobid = getenv("PBS_JOBID");
    if (jobid==NULL) {
      cerr << "Cannot get PBS_JOBID from the environment" << endl;
      exit(-1);
    }
    //cout << "PBS_JOBID = " << jobid << endl;
  
    int asked_walltime=0, used_walltime=0, asked_cputime=0, used_cputime=0;
    int connect = pbs_connect(server);
    //cout << "Process " << id << ": pbs_connect = " << connect << endl;
    batch_status *pstat=NULL; char *extend=NULL; attrl *attrib=NULL;
    pstat = pbs_statjob(connect, jobid, attrib, extend);
    while (pstat) {
      attrl *pat = pstat->attribs;
      while (pat) {
	if ( strcmp(pat->name,ATTR_used) == 0 ) {
	  if (strcmp(pat->resource, "walltime") == 0) {
	    used_walltime = 0;
	    used_walltime += 3600 * atoi(strtok(pat->value,":"));
	    used_walltime += 60 * atoi(strtok(NULL,":"));
	    used_walltime += atoi(strtok(NULL,":"));
	  } else if (strcmp(pat->resource, "cput") == 0) {
	    used_cputime = 0;
	    used_cputime += 3600 * atoi(strtok(pat->value,":"));
	    used_cputime += 60 * atoi(strtok(NULL,":"));
	    used_cputime += atoi(strtok(NULL,":"));
	  }
	} else if ( strcmp(pat->name,ATTR_l) == 0 ) {
	  if (strcmp(pat->resource, "walltime") == 0) {
	    asked_walltime = 0;
	    asked_walltime += 3600 * atoi(strtok(pat->value,":"));
	    asked_walltime += 60 * atoi(strtok(NULL,":"));
	    asked_walltime += atoi(strtok(NULL,":"));
	  } else if (strcmp(pat->resource, "cput") == 0) {
	    asked_cputime = 0;
	    asked_cputime += 3600 * atoi(strtok(pat->value,":"));
	    asked_cputime += 60 * atoi(strtok(NULL,":"));
	    asked_cputime += atoi(strtok(NULL,":"));
	  }
	}
	pat = pat->next;
      }
      pstat = pstat->next;
    }
    pbs_statfree(pstat);
    pbs_disconnect(connect);
    cout << "Time remaining: " << asked_walltime - used_walltime << endl;
  }
#endif

  MPI_Finalize();
}
