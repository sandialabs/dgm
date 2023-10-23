#!/usr/bin/env python
# ------------------------------------------------------------------------------

import sys, os
import optparse
import numpy as np
import select

# ------------------------------------------------------------------------------
# parsing input

description = '''Numerical difference of two files.

Example:
Two ASCII files, a.txt and b.txt, in row/column format with relative and
absolute tolerances, and the difference written to ab-diff.txt.

  ndiff.py -r 1.0e-6 -a 1.0e-12 -o ab-diff.txt a.txt b.txt

Lines starting with "#" are comments, and are ignored.

For binary files, use the -b option such as:

  ndiff.py -b -r 1.0e-6 -a 1.0e-12 a.bin b.bin

In this case, the files are treated as flat binary files with the exact
same number of double precision values.  Note that endian and double
representations must be the same to get valid results.  The byteswap
option, "-s", can be used to change Endianess of the datasets, and
make the tolerances useful.'''

p = optparse.OptionParser(description)


p.add_option("-a", dest="absTol", action="store", type="float", \
                 help="Absolute tolerance. Default is 1.0e-08. Optional.")

p.add_option("-b", dest="binary", action="store_true", \
                 help="Treat files as binary. Optional.")

p.add_option("-r", dest="relTol", action="store", type="float", \
                 help="Relative tolerance. Default is 1.0e-08. Optional.")

p.add_option("-s", dest="byteswap", action="store_true", \
                 help="flag to byteswap both datasets. (Big Endian to Little Endian or visa-versa)")

p.add_option("-o", dest="ofile", action="store", type="string", \
                 help="Output file of numerical difference, e.g., a-b. Optional.")

p.set_defaults(absTol = 1.0e-08,
               relTol = 1.0e-08,
               binary = False,
               byteswap = False,
               ofile  = None)


opts, args = p.parse_args()

if len(args) != 2:
  p.print_help()
  sys.exit(1)
afile = args[0]
bfile = args[1]

# Not sure how to read in two files from stdin.
#afile = "stdin"
#bfile = "stdin"
#if len(args) > 2 or len(args) == 1:
#  p.print_help()
#  sys.exit(1)
#elif len(args) == 2:
#  afile = args[0]
#  bfile = args[1]
#elif not select.select([sys.stdin,],[],[],0.0)[0]:
#  print '\nNo stdin provided!\n'
#  sys.exit(1)


# ------------------------------------------------------------------------------
status = 0

a=np.array( [0] )
if (opts.binary):
  a=np.fromfile(afile, float, -1, '')
else:
  a=np.loadtxt(afile)

if opts.byteswap:
  a = a.byteswap()

#a=np.genfromtxt(afile)
#if ifile == "stdin":
#  a=np.fromfile(sys.stdin, dtype=opts.informat)
#else:
#  a=np.fromfile(ifile, dtype=opts.informat)
#print a

b=np.array( [0] )
if (opts.binary):
  b=np.fromfile(bfile, float, -1, '')
else:
  b=np.loadtxt(bfile)
#print b

if opts.byteswap:
  b = b.byteswap()

if a.shape != b.shape:
  print 'Files are not the same size!'
  print '  %s is %s'%(afile, a.shape)
  print '  %s is %s'%(bfile, b.shape)
  sys.exit(1)

if opts.ofile != None:
  np.savetxt(opts.ofile, a-b)

a=a.ravel()
b=b.ravel()
abdiff = a-b
Linf   = np.linalg.norm(abdiff,ord=np.inf)
L1     = np.linalg.norm(abdiff,ord=1)
L2     = np.linalg.norm(abdiff,ord=2)

# Relative Norms of difference
rLinf = Linf/np.linalg.norm(a,ord=np.inf)
rL1   = L1  /np.linalg.norm(a,ord=1)
rL2   = L2  /np.linalg.norm(a,ord=2)

# Norms of relative difference
#rabdiff = np.divide(abdiff,np.abs(a))
#rLinf = np.linalg.norm(rabdiff,ord=np.inf)/np.linalg.norm(a,ord=np.inf)
#rL1   = np.linalg.norm(rabdiff,ord=1)     /np.linalg.norm(a,ord=1)
#rL2   = np.linalg.norm(rabdiff,ord=2)     /np.linalg.norm(a,ord=2)

if opts.ofile != None:
  print 'Absolute Tolerance: %g'%(opts.absTol)
  print '   Linf,  L1,  L2 = %12.8g, %12.8g, %12.8g' %(Linf,L1,L2)
  print 'Relative Tolerance: %g'%(opts.relTol)
  print '  rLinf, rL1, rL2 = %12.8g, %12.8g, %12.8g' %(rLinf,rL1,rL2)

if Linf>opts.absTol or rLinf>opts.relTol :
  print "Fail!"
  print 'Absolute Tolerance: %g'%(opts.absTol)
  print '   Linf,  L1,  L2 = %12.8g, %12.8g, %12.8g' %(Linf,L1,L2)
  print 'Relative Tolerance: %g'%(opts.relTol)
  print '  rLinf, rL1, rL2 = %12.8g, %12.8g, %12.8g' %(rLinf,rL1,rL2)
  sys.exit(1)
else :
  # print "Pass!"
  sys.exit(0)
