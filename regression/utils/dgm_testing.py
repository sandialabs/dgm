#!/usr/bin/env python
#-------------------------------------------------------------------------------


# ==============================================================================
def parse_processing( description = 'DGM testing script.' ):

  import optparse

  p = optparse.OptionParser(description)
  
  p.add_option("-n", dest="nprocs", default=1, \
                   action="store", type="int", metavar="nprocs", \
                   help="number of processors")
  
  p.add_option("-r", "--run", dest="run", default=False, \
                   action="store_true", \
                   help='''run the test (same as -pedc). This is the
                           default option if none are given.''')
  p.add_option("-p", "--preprocess", dest="preprocess", default=False, \
                   action="store_true", help="run preprocess for this test")
  p.add_option("-e", "--execute", dest="execute", default=False, \
                   action="store_true", help="execute this test")
  p.add_option("-d", "--diff", dest="diff", default=False, \
                   action="store_true", help="run the difference test")
  p.add_option("-b", "--baseline", dest="baseline", default=False, \
                   action="store_true", help="baseline the test")
  p.add_option("-g", "--graphics", dest="graphics", default=False, \
                   action="store_true", help="generate graphics for test")
  p.add_option("-c", "--clean", dest="clean", default=False, \
                   action="store_true", \
                   help="clean up test, if there are no failures")
  #p.add_option("-v", "--verbose", dest="verbose", default='brief', \
  #                 action="store", type="choice", \
  #                 choices=["none","brief","all"], \
  #                 help='''level of output; current choices are 'none',
  #                         'brief' (default), and 'all'.''')

  
  opts, args = p.parse_args()
  
  found_proc = False
  if opts.preprocess: found_proc = True
  if opts.execute:    found_proc = True
  if opts.diff:       found_proc = True
  if opts.baseline:   found_proc = True
  if opts.graphics:   found_proc = True
  if opts.clean:      found_proc = True
  if opts.run or not found_proc:
     found_proc = True
     opts.preprocess = True
     opts.execute    = True
     opts.diff       = True
     opts.clean      = True
  
  return opts, args


def shcall(cmd):
  import subprocess as sp
  status = sp.call(cmd, shell=True)
  return status
