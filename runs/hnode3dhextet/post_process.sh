#!/bin/bash

set -x 
DIR=hnode3dhextet

ls *.rst | xargs -I'{}' --max-args=1 --max-procs=0 dgm_post.exe -r '{}' $DIR > /dev/null

wait
cd tec; rm *.dat; 
mv ../$DIR.[0-9]*.dat .; 
for a in `ls -v *.dat`; do echo $a; ./format.pl < $a >>  $DIR.dat; done; 
scp  $DIR.dat face:tec; cd ..; 
#rm $DIR.[0-9]*.rst

