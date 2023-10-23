#!/bin/bash
#-------------------------------------------------------------------------------
#  
# Prototype script to checkout, compile DGM
# 
# This script is executed from run_master.sh
#
#-------------------------------------------------------------------------------

#-------------------------------------------------------------------------------
# setup and housekeeping
#-------------------------------------------------------------------------------

if [ ! -e $NIGHTLYDIR ]; then
  echo Making the nightly testing directory:  $NIGHTLYDIR
  mkdir $NIGHTLYDIR
fi
cd $NIGHTLYDIR
#
# Cleanup any old output
#
if [ -e $DGMOUTDIR ]; then 
  rm -rf $DGMOUTDIR
fi
#
# Make space for new output
#
if [ ! -e $DGMOUTDIR ]; then
  echo Making output directory $DGMOUTDIR
  mkdir $DGMOUTDIR
fi

#-------------------------------------------------------------------------------
# dgm
#-------------------------------------------------------------------------------

svn checkout $DGMREPOSITORY dgm >& $DGMOUTDIR/dgm_checkout.out 2>&1
