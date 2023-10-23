#!/bin/bash
# run multiple tests and summarize the good and bad tests
#
#   Axel Gerstenberger
#   agerste@sandia.gov
#
TESTFILE="testlist.sh"  # file that contains all tests that are executed
OUTFILE="results.sav"   # the extension avoids cleanup by dgm_clean 
                        # (dgm_clean is run after each test)
# remove old file
if [ -f $OUTFILE ]; then
  rm $OUTFILE
fi

# test and store output for parsing
./testlist.sh | tee $OUTFILE
                                         
# analyze result and plot a summary
if [ -f /usr/bin/python ]; then
  python analyze.py $TESTFILE $OUTFILE
else
  echo "Sorry, no python executable found. Can't summarize. :-("
fi

# cleanup
rm $OUTFILE

exit
