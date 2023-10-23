#!/bin/csh -f
#
# Simple run script
#
set echo
set root = heat
if ($# == 0) then
  dgm_dak.exe $root $root.dak | tee $root.log
else
  mpiexec -n $1 pdgm_dak.exe $root $root.dak | tee $root.$1.log
endif
exit
