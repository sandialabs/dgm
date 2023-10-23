#!/bin/bash
DGM_NO_SCRATCH=1
DGM_VERBOSE=2
OPTIONS=
if [ "$SYSTEM" == "redsky" ]; then
  export OPTIONS="numa_wrapper --ppn 8"
fi
env | sort | tee Source.log
dgm_clean
dgm.exe Source | tee Source.log
exit
