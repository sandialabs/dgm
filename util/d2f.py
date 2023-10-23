#!/usr/bin/env python
# ------------------------------------------------------------------------------

import sys, os
import optparse
import numpy
from numpy import linalg as LA
import select

# ------------------------------------------------------------------------------

status = 0

# ------------------------------------------------------------------------------
# parsing input

description = '''Convert binary file with doubles to binary file with floats.

                 Example:
                 90 columns + one for time, each with 4001 rows;
                 removing the time data; and transposing it.

                 d2f.py --n1 91 --n2 4001 --c1 1 -t -o p.mod.bin p.bin

                 If "-o" is not specified, the output is directed to stdout.
                 If the input argument is not specified, the input is
                 assumed to be from stdin.  For example,

                 d2f.py --n1 200 --n2 200 < p.1000.bin |
                    ximage style=normal n1=200 n2=200 hbox=550 cmap=hsv2 '''

p = optparse.OptionParser(description)


p.add_option("--c1", dest="c1", action="store", type="int", \
  help="number of columns to remove from the left.  Only works if n1 and n2 are set.  Default is set to 0.")

p.add_option("--c2", dest="c2", action="store", type="int", \
  help="number of columns to retain from the left.  Only works if n1 and n2 are set.  Default is set to n1.")

p.add_option("-d", dest="depth", action="store", type="int", \
  help="depth to project up, e.g., '-d 200' would indicate the index depth.  Only works if n1 and n2 are set.")

p.add_option("--fill", dest="fill", action="store", type="float", \
  help="set all values to FILL.")

p.add_option("--informat", dest="informat", action="store", type="string", \
  help="the format size of the input file, e.g., 'float32' and 'float64'.  Default 'float64'.")

p.add_option("--norm", dest="norm", action="store", type="float", \
  help="use following to calcuate norm: sum(abs(x)**NORM)**(1./NORM).")

p.add_option("--n1", dest="n1", action="store", type="int", \
  help="number of samples in the 1st dimension (columns)")

p.add_option("--n2", dest="n2", action="store", type="int", \
  help="number of samples in the 2nd dimension (rows)")

p.add_option("-o", dest="ofile", action="store", type="string", \
  help="output binary filename.  If not specified, output is directed to stdout.")

p.add_option("--outformat", dest="outformat", action="store", type="string", \
  help="the format size of the output file, e.g., 'float32' and 'float64'.  Default 'float32'.")

p.add_option("--r1", dest="r1", action="store", type="int", \
  help="number of rows to remove from the top.  Only works if n1 and n2 are set.  Default is set to 0.")

p.add_option("--r2", dest="r2", action="store", type="int", \
  help="number of rows to retain from the top.  Only works if n1 and n2 are set.  Default is set to n2.")

p.add_option("--reciprocal", dest="reciprocal", action="store_true", \
  help="flag to take the element-wise reciprocal, e.g., 1/a_ij.")

p.add_option("-s", dest="byteswap", action="store_true", \
  help="flag to byteswap the matrix. (Big Endian to Little Endian or visa-versa)  This is done prior to any other options.")

p.add_option("--scale", dest="scale", action="store", type="float", \
  help="value to scale input. Default is 1.0.")

p.add_option("-t", dest="transpose", action="store_true", \
  help="flag to transpose the matrix. Only works if n1 and n2 are set, and is performed AFTER r1, r2, c1 and c2 are applied.")

p.add_option("--threshold_min", dest="threshold_min", action="store", type="float", \
  help="reset values below threshold_min to threshold_min. Default is None.")

p.add_option("--threshold_max", dest="threshold_max", action="store", type="float", \
  help="reset values above threshold_max to threshold_max. Default is None.")

p.set_defaults(ofile='stdout',
               depth = -1,
               fill=None,
               norm=None,
               n1 = -1,
               n2 = -1,
               c1 = -1,
               c2 = -1,
               informat='float64',
               outformat='float32',
               r1 = -1,
               r2 = -1,
               reciprocal=False,
               byteswap=False,
               scale = 1.0,
               transpose=False,
               threshold_min=None,
               threshold_max=None)


opts, args = p.parse_args()

if opts.n1 > 0 and opts.n2 > 0:
  if opts.c1 < 0 or opts.c2 > opts.n1: opts.c1 = 0
  if opts.c2 < 0 or opts.c2 > opts.n1: opts.c2 = opts.n1
  if opts.r1 < 0 or opts.r2 > opts.n2: opts.r1 = 0
  if opts.r2 < 0 or opts.r2 > opts.n2: opts.r2 = opts.n2

ifile = "stdin"
if len(args) > 1:
  p.print_help()
  sys.exit(1)
elif len(args) == 1:
  ifile = args[0]
elif not select.select([sys.stdin,],[],[],0.0)[0]:
  print '\nNo stdin provided!\n'
  sys.exit(1)

# Does not seem to work.  Need to investigate.
#if opts.ofile == "stdout":
#  if not select.select([sys.stdout,],[],[],0.0)[0]:
#    print '\nNo stdout provided!\n'
#    sys.exit(1)

# ------------------------------------------------------------------------------
status = 0

a=numpy.array( [0] )
if ifile == "stdin":
  a=numpy.fromfile(sys.stdin, dtype=opts.informat)
else:
  a=numpy.fromfile(ifile, dtype=opts.informat)

if opts.byteswap:
  a = a.byteswap()

if opts.norm != None:
  Norm = LA.norm(a,opts.norm)
  print '----------------------------------'
  print 'The L%d-norm is %g'%(opts.norm,Norm)
  print '----------------------------------'

if opts.n1 > 0 and opts.n2 > 0:

  if opts.n1*opts.n2 != a.size:
    print '\nSize of input array does not match n1*n2:'
    print '  array size = %i' % (a.size)
    print '  n1*n2      = %i   = %i * %i\n' % (opts.n1*opts.n2,opts.n1,opts.n2)
    if opts.n1*opts.n2 > a.size:
      print '  Not enough data.'
      sys.exit(1)
    else:
      print '  Using truncated array of size:'
      print '  n1*n2 = %i = %i * %i\n' % (opts.n1*opts.n2,opts.n1,opts.n2)
      a=a[:opts.n1*opts.n2]

  a=a.reshape((opts.n2,opts.n1))
  a=a[opts.r1:opts.r2,opts.c1:opts.c2]
  if opts.transpose:
    a = a.transpose()

  if opts.depth > -1:
    for x in xrange(a.shape[1]):
      value = a[opts.depth, x]
      for y in xrange(0,opts.depth):
        a[y,x] = value

if opts.fill != None:
  a.fill(opts.fill)

if opts.scale != 1.0:
  a *= opts.scale

if opts.reciprocal:
  a = numpy.reciprocal(a)

if opts.threshold_min != None:
  super_threshold_indices = a < opts.threshold_min
  a[super_threshold_indices] = opts.threshold_min

if opts.threshold_max != None:
  super_threshold_indices = a > opts.threshold_max
  a[super_threshold_indices] = opts.threshold_max

if opts.ofile == "stdout":
  a.astype(opts.outformat).tofile(sys.stdout)
else:
  a.astype(opts.outformat).tofile(opts.ofile)

sys.exit(status)
