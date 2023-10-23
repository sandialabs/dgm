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

root = 'chan'     # root filename for test
aeps = 5.0e-10    # absolute error tolerance
reps = 1.0e-08    # relative error tolerance

# These comments are for testing with the runtests.py utility.
#TESTING active
#TESTING -n 2
#TESTING -k medium

# arguments for generating binary mesh similar to existing ascii mesh
# dgm_mesh.exe -nsd 3 -nx 8 -ny 8 -nz 8 -Lx 12.56637062 -Ly 4.188790205 -Lz 2.0 -tecplot 0 -ascii 0 -binary 1 -nograph -Cz 1.75 -r chan

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
  status += dts.call('rm -f chan.sts ru.*.bin rE.*.bin')

# ==============================================================================
if status == 0: print 'Success.'
else:           print 'Failure.'
sys.exit(status)
