#!/bin/bash
#
# This is a handy way to extract the hostname
#
echo Completed DGM testing on ${HOST%%.*${HOST: -1}} at `date`
#
# Send the email 
#
mail -s "`echo $HOSTNAME: dgm nightly testing`" "sscoll@me.com" < \
$DGMOUTDIR/dgm_email.out
