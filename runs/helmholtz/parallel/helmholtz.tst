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

root = 'helmholtz'     # root filename for test
aeps = 1.0e-07    # absolute error tolerance
reps = 1.0e-07    # relative error tolerance

# These comments are for testing with the runtests.py utility.
#TESTING active
#TESTING -k Trilinos

# ==============================================================================
status = 0

# ------------------------------
if dts.opts.preprocess and not status:
  if dts.opts.verbose: print '---> Preprocessing %s' % (root)

# ------------------------------
if dts.opts.execute and not status:
  if dts.opts.verbose: print '---> Execute %s' % (root)
  status += dts.dgm(root, '-ghosting')

# ------------------------------
if dts.opts.diff and not status:
  if dts.opts.verbose: print '---> Diff %s' % (root)
  # Axel's test only checked if it doesn't crash.
  # So no diff, just check the status of the runs.
  # Here's the original (serial) logic
  #  dgm.exe -ghosting $root >! $root.scn
  #  set mycrashs = $?
  #  echo $mycrashs
  #  cp $root.scn output.log
  #  python determine_failure.py
  #  set pys = $?

  # cmd = 'dgm_diff.exe -aeps %g -reps %g -r1 %s.ref -r2 %s.rst %s' \
  #       %(aeps, reps, root, root, root)
  # status += dts.call(cmd)

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
