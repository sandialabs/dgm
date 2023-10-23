#!/bin/bash
DGM_NO_SCRATCH=1
DGM_VERBOSE=2
OPTIONS=
if [ "$SYSTEM" == "redsky" ]; then
  export OPTIONS="numa_wrapper --ppn 8"
fi
env | sort | tee 2D_bore.log
dgm_clean
#mpiexec $OPTIONS pdgm.exe 2D_bore | tee 2D_bore.log
mpiexec -n 16 pdgm.exe 2D_bore | tee 2D_bore.log
#/home/vamouss/local/dgm/serial/debug/bin/dgm.exe 2D_bore | tee 2D_bore.log
#totalview /home/vamouss/local/dgm/serial/debug/bin/dgm.exe -a 2D_bore 
#totalview /home/vamouss/local/dgm/trilinos/serial/opt/bin/dgm.exe -a 2D_bore 
#/home/vamouss/local/dgm/trilinos/serial/opt/bin/dgm.exe 2D_bore 
exit
