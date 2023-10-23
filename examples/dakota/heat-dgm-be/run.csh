#!/bin/csh -f
#
# Simple run script
#
#set echo
dgm_clean
set root = heat
if ($# == 0) then
  dgm_opt.exe $root | tee $root.log
else
  mpiexec -n $1 pdgm_opt.exe $root | tee $root.$1.log
endif
exit
