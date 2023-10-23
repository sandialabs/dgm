#!/bin/bash
#-------------------------------------------
# Platform specific environment variables  
# BvBW  10/06/08
#-------------------------------------------

if [ -e $HOME/.bash_profile ]; then
  source $HOME/.bash_profile
fi

SCRIPTDIR=$DGM_DIST/regression/scripts

NIGHTLYDIR=$HOME/testing
#
# Setup Trilinos
#
TRILDIR=$NIGHTLYDIR/Trilinos
TRILBUILDDIR=$TRILDIR/SERIAL
TRILINSTALLDIR=$NIGHTLYDIR/local
TRILOUTDIR=$NIGHTLYDIR/Trilinos_out
TRILREPOSITORY=:ext:sscoll@software.sandia.gov:/space/CVS
#
# Setup DGM
#
DGMDIR=$NIGHTLYDIR/dgm
DGMBUILDDIR=$DGMDIR/SERIAL
DGMUTILDIR=$DGMDIR/util
DGMOUTDIR=$NIGHTLYDIR/dgm_out
DGMREPOSITORY=:ext:sscoll@software.sandia.gov:/home/sscoll/cvsroot
#
# Setup DAKOTA
#
DAKDIR=$NIGHTLYDIR/Dakota
DAKOUTDIR=$NIGHTLYDIR/Dakota_out
DAKVOTD=sscoll@development.sandia.gov:/var/www/html/DAKOTA/licensing/votd
#
# Setup paths
#
export PATH=$DGMBUILDDIR:$PATH:/usr/local/bin/:/usr/bin:/usr/local/lib:\
/usr/local:/usr/local/mpi/lib:$DGMBUILDDIR:$DGMUTILDIR
export LD_LIBRARY_PATH=/usr/lib64:/usr/local/mpi/lib:$LD_LIBRARY_PATH
