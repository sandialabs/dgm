#!/usr/bin/env python
#-------------------------------------------------------------------------------

import sys, os
import string
import optparse
import shutil
from dgm_test_support import *

# ==============================================================================
# Parsing input

desc = '''reo.tst [options]

# p=2 next to p=10 on two cores with p=2 all on one core and p=10 on the other
# This tests the ability to have very large p differences spread across ranks which 
# was an known issue on or about 2/20/2013 that was fixed on that day.

Performs a test of Reo physics.'''

dts = dgm_test_support(desc)

#-------------------------------------------------------------------------------
# Problem Parameters

root = '2n10'     # root filename for test
aeps = 1.0e-13    # absolute error tolerance
reps = 5.0e-14    # relative error tolerance

# These comments are for testing with the runtests.py utility.
#TESTING active
#TESTING -n 2
#TESTING -k short

# ==============================================================================
status = 0

# ------------------------------
if dts.opts.preprocess and not status:
  if dts.opts.verbose: print '---> Preprocessing %s' % (root)

# ------------------------------
if dts.opts.execute and not status:
  if dts.opts.verbose: print '---> Execute %s' % (root)
  status += dts.dgm(root)

# ------------------------------
if dts.opts.diff and not status:
  if dts.opts.verbose: print '---> Diff %s' % (root)
  status += dts.dgm_diff(aeps, reps, root, root, root)

# ------------------------------
if dts.opts.baseline and not status:
  if dts.opts.verbose: print '---> Baseline %s' % (root)

# ------------------------------
if dts.opts.graphics and not status:
  if dts.opts.verbose: print '---> Graphics %s' % (root)

# ------------------------------
if dts.opts.clean and not status:
  if dts.opts.verbose: print '---> Clean %s' % (root)
  status += dts.call('dgm_clean')

# ==============================================================================
if status == 0: print 'Success.'
else:           print 'Failure.'
sys.exit(status)
