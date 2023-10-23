#!/bin/bash

#-------------------------------------------
#  
# Prototype script to execute regression
# tests
#
# This script is executed from run_master.sh
#
# BvBW  10/06/08
#-------------------------------------------

#-------------------------------------------
# setup and housekeeping
#-------------------------------------------

cd $NIGHTLYDIR

if [ ! -d $DGMOUTDIR ]; then 
  mkdir $DGMOUTDIR
fi

#-------------------------------------------
# run tests in dgm
#-------------------------------------------

cd $DGMDIR/runs
$SCRIPTDIR/dgm_testlist.sh >& $DGMOUTDIR/dgm_runtest.out
