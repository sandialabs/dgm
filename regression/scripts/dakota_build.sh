#!/bin/bash
#-------------------------------------------------------------------------------
#  
# Prototype script to checkout, compile Dakota
# 
#
# BvBW  10/06/08
#-------------------------------------------------------------------------------

#-------------------------------------------------------------------------------
# setup and housekeeping
#-------------------------------------------------------------------------------

if [ -a $NIGHTLYDIR/Dakota_votd.src.tar ]; then \rm Dakota_votd.src.tar
\rm -rf $DAKDIR

if [ -a $DAKOUTDIR ]; then \rm -rf $DAKOUTDIR
fi

cd $NIGHTLYDIR

#-------------------------------------------------------------------------------
# copy, configure, build, install Dakota 
#-------------------------------------------------------------------------------

scp $DAKVOTD/Dakota_votd.src.tar .
tar -zxf Dakota_votd.src.tar
cd $DAKDIR
./configure
make > $DAKOUTDIR/dakota_build.out 2>&1

fi
