#!/bin/bash
#-------------------------------------------------------------------------------
#  
# Prototype script to build DGM
# 
# This script is executed from run_master.sh
#
#-------------------------------------------------------------------------------

#-------------------------------------------------------------------------------
# configure and make dgm
#-------------------------------------------------------------------------------

cd $DGMDIR
if [ ! -d $DGMBUILDDIR ]; then
  mkdir $DGMBUILDDIR
fi
if [ ! -d $DGMOUTDIR ]; then
  echo Why am I here
  mkdir $DGMOUTDIR
fi
cd $DGMBUILDDIR
if [ ! -e Makefile ]; then
  ln -s ../src/Makefile .
fi
make -j `../util/ncpus` all >& $DGMOUTDIR/dgm_build.out
