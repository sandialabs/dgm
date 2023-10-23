#!/usr/bin/env python
''' Reo Optimization Python driver

This uses the DGM python interface to solve a Reo optimization problem.

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

# Setup and execute a Reo Optimization problem

if rank==0:
  print \
  "============================================================================"
  print "           R e o   O p t i m i z a t i o n   S o l v e r "
  print \
  "============================================================================"

# Reo optimization problem

problem = dgm.ReoOptProblem(args,params,comm)
problem.solve()

# Explore the interface

print "\nExploring the DGM Python interface\n"
control = dgm.Control(problem.getControl())
print "control.norm() = ",control.norm()
#print "control.cost() = ",control.cost()
objective = dgm.Objective(problem.getObjective())
print "objective.num_obs() =",objective.num_obs()
#print "objective.cost() =",objective.cost()

if rank==0:
  print \
  "============================================================================"
  print "    C o m p l e t e d   R e o   O p t i m i z a t i o n   S o l v e r "
  print \
  "============================================================================"

exit(0)
