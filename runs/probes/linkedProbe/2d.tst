#!/usr/bin/env python
#-------------------------------------------------------------------------------

import sys, os
import string
import optparse
import shutil
from dgm_test_support import *

# ==============================================================================
# Parsing input

desc = '''2d.tst [options]

Test the use of different, multiple responses.'''

dts = dgm_test_support(desc)

#-------------------------------------------------------------------------------
# Problem Parameters

root = '2d'       # root filename for test
aeps = 7.0e-14    # absolute error tolerance
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
  status += dts.call('ndiff.py 2d.d0.prb 2d.d0.prf')
  status += dts.call('ndiff.py 2d.d1.prb 2d.d1.prf')
  status += dts.call('ndiff.py 2d.g0.prb 2d.g0.prf')
  status += dts.call('ndiff.py 2d.g1.prb 2d.g1.prf')
  status += dts.call('ndiff.py 2d.f0.prb 2d.f0.prf')
  status += dts.call('ndiff.py 2d.f1.prb 2d.f1.prf')
  status += dts.call('ndiff.py 2d.f2.prb 2d.f2.prf')
  status += dts.call('ndiff.py 2d.e0.prb 2d.e0.prf')
  status += dts.call('ndiff.py 2d.j0.prb 2d.j0.prf')
  status += dts.call('ndiff.py 2d.j1.prb 2d.j1.prf')
  status += dts.call('ndiff.py 2d.s0.prb 2d.s0.prf')
  status += dts.call('ndiff.py 2d.s1.prb 2d.s1.prf')

# ------------------------------
if dts.opts.baseline and not status:
  if dts.opts.verbose: print '---> Baseline %s' % (root)
  status += dts.call('cp 2d.d0.prb 2d.d0.prf')
  status += dts.call('cp 2d.d1.prb 2d.d1.prf')
  status += dts.call('cp 2d.g0.prb 2d.g0.prf')
  status += dts.call('cp 2d.g1.prb 2d.g1.prf')
  status += dts.call('cp 2d.f0.prb 2d.f0.prf')
  status += dts.call('cp 2d.f1.prb 2d.f1.prf')
  status += dts.call('cp 2d.f2.prb 2d.f2.prf')
  status += dts.call('cp 2d.e0.prb 2d.e0.prf')
  status += dts.call('cp 2d.j0.prb 2d.j0.prf')
  status += dts.call('cp 2d.j1.prb 2d.j1.prf')
  status += dts.call('cp 2d.s0.prb 2d.s0.prf')
  status += dts.call('cp 2d.s1.prb 2d.s1.prf')

# ------------------------------
if dts.opts.graphics and not status:
  if dts.opts.verbose: print '---> Graphics %s' % (root)

# ------------------------------
if dts.opts.clean and not status:
  if dts.opts.verbose: print '---> Clean %s' % (root)
  status += dts.dgm_clean(root)
  status += dts.call('rm -f 2d.*.bin')
  status += dts.call('rm -f *.bdt')
  status += dts.call('rm -f ic.dat out.dat')

# ==============================================================================
if status == 0: print 'Success.'
else:           print 'Failure.'
sys.exit(status)
