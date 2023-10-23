#!/usr/bin/env python
''' Reo Python driver

This uses the DGM python interface to build and solve a Reo forward problem.

Copyright:  (c)2011 Scott Collis
'''

import os, sys
import dgm

# start up DGM with or without MPI

try:
  dgm.MPI
  world = dgm.MPI.COMM_WORLD
  rank = world.Get_rank()
  size = world.Get_size()
  comm = dgm.MpiComm(world)
  if rank==0: print "Running Reo on", size, "processors..."
except AttributeError:
  rank = 0
  comm = dgm.SerialComm()
  print "Running Reo in serial..."

params = dgm.Table()
args = dgm.ArgList(sys.argv[1:])

if args.size() < 2: 
  print "dgm: not enough arguments" 
  exit()

# Setup and execute a Reo problem

if rank==0:
  print \
  "============================================================================"
  print "                     R e o   F l o w   S o l v e r "
  print \
  "============================================================================"

# Reo forward problem

problem = dgm.ReoProblem(args,params,comm)
problem.solve()

if rank==0:
  print \
  "============================================================================"
  print "           C o m p l e t e d   R e o   F l o w   S o l v e r "
  print \
  "============================================================================"

exit(0)
