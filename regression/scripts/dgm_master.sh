#!/bin/bash
#-------------------------------------------------------------------------------
# Prototype script to checkout, compile Trilinos dgm, Dakota, in addition to 
# performing "runtest" for dgm
# 
# This scripts calls various subscripts
#-------------------------------------------------------------------------------

echo Starting DGM testing at `date`

#-------------------------------------------------------------------------------
# Location of scripts
#-------------------------------------------------------------------------------

SCRIPTDIR=$DGM_DIST/regression/scripts

#-------------------------------------------------------------------------------
# Specify platform dependencies
#-------------------------------------------------------------------------------

source $SCRIPTDIR/dgm_setup.sh

#-------------------------------------------------------------------------------
# Execute scripts
#-------------------------------------------------------------------------------

source $SCRIPTDIR/dgm_checkout.sh
#source $SCRIPTDIR/trilinos_build.sh
#source $SCRIPTDIR/dakota_build.sh
source $SCRIPTDIR/dgm_build.sh
source $SCRIPTDIR/dgm_runtest.sh

#-------------------------------------------------------------------------------
# Execute parse output and send email scripts
#-------------------------------------------------------------------------------

cd $DGMOUTDIR
$SCRIPTDIR/dgm_parse.py
source $SCRIPTDIR/dgm_email.sh

exit 0
