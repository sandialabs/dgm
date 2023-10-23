#include <stdio.h>
#include <stdlib.h>

#include "Checkpoint.hpp"

// Test for the Griewank CheckPoint class
//
// g++ -I../src ../src/Checkpoint.cpp checktest.cpp -o checktest

int main(int argc, char *argv[]) {
  int check, capo, fine, steps, snaps;
  int info;
  enum Checkpoint::action whatodo;
  capo = 0;
  snaps = 0;
  printf("** Checkpoint Driver **\n");
  printf("ENTER: STEPS, SNAPS, INFO => ");
  scanf("%i",&steps);
  scanf("%i",&snaps);
  scanf("%i",&info);
  printf("STEPS=%d, SNAPS=%d, INFO=%d\n",steps,snaps,info);
  Checkpoint chp(steps,snaps);
  fine = steps + capo;
  check = -1;   /* Neccessary for first call */
  do {
    whatodo = chp.revolve(&check, &capo, &fine, snaps, &info);
    if ((whatodo == Checkpoint::takeshot) && (info > 1))
      printf(" takeshot at %6d \n",capo);
    if ((whatodo == Checkpoint::advance) && (info > 2))
      printf(" advance to %7d \n",capo);
    if ((whatodo == Checkpoint::firsturn) && (info > 2)) 
      printf(" firsturn at %6d \n",capo);
    if ((whatodo == Checkpoint::youturn) && (info > 2))
      printf(" youturn at %7d \n",capo);
    if ((whatodo == Checkpoint::restore) && (info > 2)) 
      printf(" restore at %7d \n",capo);
    if (whatodo == Checkpoint::error) {
      printf(" irregular termination of revolve \n");
      switch(info) {
      case 10: 
        printf(" number of checkpoints stored exceeds checkup, \n");
        printf(" increase constant 'checkup' and recompile \n");
        break;
      case 11: 
        printf(" number of checkpoints stored = %d exceeds snaps = %d, \n"
               ,check+1,snaps);
        printf(" ensure 'snaps' > 0 and increase initial 'fine' \n");
        break;
      case 12: 
        printf(" error occurs in numforw \n");
        break;
      case 13: 
        printf(" enhancement of 'fine', 'snaps' checkpoints stored, \n");
        printf(" increase 'snaps'\n");
        break;
      case 14: 
        printf(" number of snaps exceeds snapsup, ");
        printf(" increase constant 'checkup' and recompile \n");
        break;
      case 15: 
        printf(" number of reps exceeds repsup, ");
        printf(" increase constant 'repsup' and recompile \n");
      }
    }
  } while((whatodo != Checkpoint::terminate) && (whatodo != Checkpoint::error));
  return info;
}
