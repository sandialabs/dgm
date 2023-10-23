#!/bin/bash

DIR=hnode3d

for a in `ls -v *.rst`; do echo $a; { dgm_post.exe -r $a  $DIR > /dev/null & } ; done; 
wait
cd tec; rm *.dat; 
mv ../$DIR.[0-9]*.dat .; 
for a in `ls -v *.dat`; do echo $a; ./format.pl < $a >>  $DIR.dat; done; 
scp  $DIR.dat face:tec; cd ..; 
#rm $DIR.[0-9]*.rst

