#!/bin/bash

# Dump a binary mesh file, usually names file.grd
# to a text file called file.txt using only the 
# octal dump program, od.  This is just a fast
# way to dump the contents of the file into a readable
# form for debugging purposes.

F=$1
N=8          # number of nodes per element, only a guess and will not fail if wrong
echo "Converting file" $F.grd "to text file" $F.txt

E=`od   --address-radix=d  --format=dI --output-duplicates --skip-bytes=0 --read-bytes=4 $F.grd | head -1 | sed -e"s/0000000//"`
echo "Binary mesh file with" $E "elements"

echo "Number of Elements:"   >  $F.txt
od   --width=64 --address-radix=d  --format=dI --output-duplicates --skip-bytes=0 --read-bytes=4 $F.grd  >> $F.txt

echo "Spatial Dimension:"  >>  $F.txt
od   --width=64 --address-radix=d  --format=dI --output-duplicates --skip-bytes=4 --read-bytes=4 $F.grd  >> $F.txt

echo "Number of Nodes:"  >>  $F.txt
od   --width=64 --address-radix=d  --format=dI --output-duplicates --skip-bytes=8 --read-bytes=4 $F.grd  >> $F.txt

echo "Element Types:"  >>  $F.txt
B=$(($E*4))     # four byte integers
od   --width=64 --address-radix=d  --format=dI --output-duplicates --skip-bytes=12 --read-bytes=$B $F.grd  >> $F.txt

echo "Displacements:"  >>  $F.txt
D=$(($B+12))     # four byte integers
od   --width=64 --address-radix=d  --format=dI --output-duplicates --skip-bytes=$D --read-bytes=$B $F.grd  >> $F.txt

echo "All X than all Y then all Z Coordinates:"  >>  $F.txt
N=$(($N*8))     # eight bypes per coordinate
D=$(($D+$B))
od  --width=$N  --address-radix=d  --format=fD --output-duplicates --skip-bytes=$D  $F.grd >> $F.txt 

