#!/usr/bin/env python
#-------------------------------------------------------------------------------

import sys, os
import string
import shutil
from dgm_test_support import *

# ==============================================================================
# Parsing input

# No reason to format the description as it will be reformatted by optparse.
desc = '''graph weights test driver
       '''

dts = dgm_test_support(desc)

#-------------------------------------------------------------------------------
# Problem Parameters

root = 'physics'  # root filename for test
aeps = 1.0e-12    # absolute error tolerance
reps = 1.0e-8     # relative error tolerance

# These comments are for testing with the runtest.py utility.
#TESTING inactive
#TESTING -n 1
#TESTING -k long

# ==============================================================================
status = 0

# set number of time steps based on curvature
Nt = [ 5, 5 ]

# loop over physics
# skipping physics 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 18, 22, 24, 27, 30, 49, 50, 72, 74, 100, 106
physics_list = [ 0, 1, 2 ]

# mesh dimensions by p order and curvature
n2d = [
  [ 60, 60, 55, 55, 50, 50, 45, 45, 40, 40, 40, 40, 35, 30, 30, 30, 25, 25, 25, 20, 20 ],
  [  0, 60, 55, 50, 45, 40, 35, 35, 30, 25, 25, 20, 20, 15, 15, 10, 10, 10, 10, 10,  5 ] ]
n3d = [
  [ 10,  9,  8,  8,  7,  7,  7,  6,  5,  5,  5,  4,  4,  4,  4,  3,  3,  3,  3,  3,  3 ],
  [  0,  9,  8,  7,  6,  5,  4,  4,  3,  2,  2,  2,  2,  2,  1,  1,  1,  1,  1,  1,  1 ] ]
for physics in physics_list:

  # loop over element type (modal, spectral, ...)
  etype = ''
  element_types = [ 'modal', 'spectral' ]
  for e in element_types:
    # set argument for dgm_mesh
    if e == 'spectral':
      etype = '-spectral'
    else:
      etype = ''

    # loop over curvature
    curve_index = 0
    curves = [ 'affine', 'nonaffine' ]
    for curve in curves:

      # loop over dimensionality
      dimensions = [ 2, 3 ]
      for nsd in dimensions:

        # skip physics 1 and 2 in 3d, these are 2d physics only
        if nsd == 3 and (physics == 1 or physics == 2 or
             physics == 11 or physics == 30): continue
        # skip physics 8 and 9 in 2d, these are 3d physics only
        if nsd == 2 and (physics == 8 or physics == 9): continue

        # loop over polynomial order
        porder_base = 0
        porders = 21
        if curve == 'nonaffine' or e == 'spectral': porder_base = 1
        for p in xrange(porder_base,porders):

          if nsd == 2:
            # 2d tests
            nd = ndy = n2d[curve_index][p]
            nx   = nd   # number of elements in x direction
            ny   = ndy  # number of elements in y direction
            nz   = 1          # set to one for call to mkcrv
          else:
            # 3d tests
            nd = ndz = n3d[curve_index][p]
            nx   = nd   # number of elements in x direction
            ny   = nd   # number of elements in y direction
            nz   = ndz  # number of elements in z direction
            Lz   = nz * 2.5   # length of domain in z direction

          Lx   = nx * 2.5     # length of domain in x direction
          Ly   = ny * 2.5     # length of domain in y direction

          # remove or create the root.crv file
          if curve == 'affine':
            if os.path.exists('%s.crv'%(root)):
              cmd = 'rm %s.crv' % (root)
              if os.path.exists('%s.cv'%(root)):
                cmd = 'rm %s.cv' % (root)
              status += dts.call(cmd)
          else:
            # non-affine element, generate curve fill
            status += dts.mkcrv(root, nx*ny*nz)

          # generate the mesh
          if nsd == 2:
            cmd = 'dgm_mesh.exe -nsd %i -nx %i -ny %i -Lx %g -Ly %g %s -r %s -binary 1 -ascii 0' \
                  %(nsd, nx, ny, Lx, Ly, etype, root)
            status += dts.call(cmd)
          else:
            cmd = 'dgm_mesh.exe -nsd %i -nx %i -ny %i -nz %i -Lx %g -Ly %g -Lz %g %s -r %s -binary 1 -ascii 0' \
                  %(nsd, nx, ny, nz, Lx, Ly, Lz, etype, root)
            status += dts.call(cmd)

          # make input file
          status += dts.mkinp(root, physics, p, Nt[curve_index])

          flog = '%s.p=%i.log'%(root, p)
          # run each test twice, one to heat cache, once to record timing
          status += dts.call('dgm.exe -timing -noIO %s' %(root), logfile = flog)
          status += dts.call('dgm.exe -timing -noIO %s' %(root), logfile = flog)
          if status != 0: sys.exit(status)

          f = open(flog, 'r')
          lines = f.readlines()
          f.close()
          if lines[-3].find('Average CPU time per step:') != -1:
            times = float(lines[-3].split()[5])
            print '  physics %i, %id %s, %s, porder %d, runtime = %g' \
                  % (physics, nsd, e, curve, p, times)

      # update to nonaffine
      curve_index = curve_index + 1

# ==============================================================================
if status == 0: print 'Success.'
else:           print 'Failure.'
sys.exit(status)
