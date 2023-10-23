#!/bin/csh -f
set root = barth 
set aeps = 1.0e-12
set reps = 1.0e-8
set s = 0
dgm.exe $root > $root.scn
@ s = $s + $status
dgm_diff.exe -aeps $aeps -reps $reps -r1 $root.ref -r2 $root.rst $root
@ s = $s + $status
dgm_clean
exit $s
