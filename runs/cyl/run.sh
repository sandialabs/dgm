#!/bin/sh
#
export LD_LIBRARY_PATH=$HOME/local/gsl/lib:$LD_LIBRARY_PATH
#
# execute the code
#
mpiexec pdgm.exe cyl
exit
