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

Performs a test of Reo physics.'''

dts = dgm_test_support(desc)

#-------------------------------------------------------------------------------
# Problem Parameters

root = 'ex9'       # root filename for test
aeps = 1.0e-12    # absolute error tolerance
reps = 1.0e-12    # relative error tolerance

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
  status += dts.call('cp ex9.rst ex9.ref')

# ------------------------------
if dts.opts.graphics and not status:
  if dts.opts.verbose: print '---> Graphics %s' % (root)
  status += dts.call('dgm_post.exe -paraview -notec -start 0 -end 1000 -inc 10 ex9')

# ------------------------------
if dts.opts.clean and not status:
  if dts.opts.verbose: print '---> Clean %s' % (root)
  status += dts.call('dgm_clean')
  status += dts.call('rm -f ex9.*.bin')

# ==============================================================================
if status == 0: print 'Success.'
else:           print 'Failure.'
sys.exit(status)
