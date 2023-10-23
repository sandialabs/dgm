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

root = 'hnode3dhextet'      # root filename for test
aeps = 9.0e-11    # absolute error tolerance
reps = 5.0e-11    # relative error tolerance

# These comments are for testing with the runtests.py utility.
#TESTING active
#TESTING -k short
#TESTING -n 4

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
  status += dts.call('cp hnode3dhextet.rst hnode3dhextet.ref')

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

