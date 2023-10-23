#!/bin/csh -f
#TESTING inactive
#TESTING -k Trilinos
#TESTING -n 1
set argv=`getopt n: $*`
if ($? != 0) then
  exit 1
endif
set ncpus = 0
while (1)
  switch($1:q)
  case -n:
    set ncpus = $2:q
    shift; shift
    breaksw
  case --:
    shift
    break
  default:
    echo "Parser error" ; exit 1
  endsw
end
set root = $0:t:r
set aeps = 1.0e-5
set reps = 1.0e-11
set s = 0
if ($ncpus == 0) then
  if ($?PBS_NODEFILE || $?SLURM_JOB_NODELIST) then
    mpiexec pdgm.exe $root | tee $root.log
  else
    dgm.exe $root | tee $root.log
  endif
else
  mpiexec -n $ncpus pdgm.exe $root | tee $root.$ncpus.log
endif
@ s = $s + $status
dgm_diff.exe -aeps $aeps -reps $reps -r1 $root.ref -r2 $root.rst $root
@ s = $s + $status
if ($s == 0) dgm_clean
exit $s
