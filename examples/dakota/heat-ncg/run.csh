#!/bin/csh -f
#
# Simple run script
#
set echo
set root = heat
if ($# == 0) then
  dakota $root.dak | tee $root.log
else
  mpiexec -n $1 dakota $root.dak | tee $root.$1.log
endif
exit
