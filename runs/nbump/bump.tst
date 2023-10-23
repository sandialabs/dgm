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

root = 'bump'     # root filename for test
aeps = 5.0e-12    # absolute error tolerance
reps = 5.0e-12    # relative error tolerance

# These comments are for testing with the runtests.py utility.
#TESTING active
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
  status += dts.call('cp bump.rst bump.ref')

# ------------------------------
if dts.opts.graphics and not status:
  if dts.opts.verbose: print '---> Graphics %s' % (root)
  print 'Graphics not currently implemented'

# ------------------------------
if dts.opts.clean and not status:
  if dts.opts.verbose: print '---> Clean %s' % (root)
  status += dts.dgm_clean(root)

# ==============================================================================
if status == 0: print 'Success.'
else:           print 'Failure.'
sys.exit(status)
