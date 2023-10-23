#!/bin/bash
#-----------------------------------------------------------------------------
# Prototype script to checkout, compile Trilinos
#
# This script is executed from run_master.sh
# 
# This script is being run at 1:01 am every night on s878144.sandia.gov
#
#-----------------------------------------------------------------------------

#-----------------------------------------------------------------------------
# setup and housekeeping
#-----------------------------------------------------------------------------

#if [ -a $TRILDIR ]; then \rm -rf $TRILDIR
#fi

if [ -a $TRILOUTDIR ]; then \rm -rf $TRILOUTDIR
fi

cd $NIGHTLYDIR
mkdir $TRILOUTDIR

#-----------------------------------------------------------------------------
# checkout Trilinos
#-----------------------------------------------------------------------------

#cvs -d $TRILREPOSITORY co Trilinos > $TRILOUTDIR/trilinos_checkout.out 2>&1

#-----------------------------------------------------------------------------
# configure, build, install Trilinos
#-----------------------------------------------------------------------------

cd $TRILDIR
mkdir $TRILINSTALLDIR
mkdir $TRILBUILDDIR

cd $TRILBUILDDIR
cp $DGMUTILDIR/do-cmake-trilinos-serial .

./do-cmake-trilinos-serial $TRILINSTALLDIR > \
$TRILOUTDIR/trilinos_configure.out 2>&1
make -j `$DGMUTILDIR/ncpus` > $TRILOUTDIR/trilinos_make.out 2>&1
make install > $TRILOUTDIR/trilinos_make_install.out 2>&1
