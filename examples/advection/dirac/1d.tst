#!/bin/csh -f
set root = 1d 
set aeps = 5.0e-13
set reps = 5.0e-14
set s = 0
if ($# == 0) then
  # mpiexec pdgm.exe $root | tee $root.log
  dgm.exe $root | tee $root.log
else
  mpiexec -n $1 pdgm.exe $root | tee $root.$1.log
endif
@ s = $s + $status
dgm_diff.exe -aeps $aeps -reps $reps -r1 $root.ref -r2 $root.rst $root
@ s = $s + $status
#dgm_clean
exit $s
