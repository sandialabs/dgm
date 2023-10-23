#!/usr/bin/env python

# System imports
import os
import sys

# Import DGM
try:
    import pdgm as dgm
    print "Successfully imported parallel version of DGM"
    parallel = True
except ImportError:
    try:
        import dgm
        print "Imported serial version of DGM"
        parallel = False
    except ImportError:
        print "Neither pdgm nor dgm are built"

# Build a communicator
if parallel:
    comm = dgm.MpiComm(dgm.MPI.COMM_WORLD)
else:
    comm = dgm.SerialComm()
print comm

params = dgm.Table()
args = dgm.ArgList(sys.argv[1:])

#print "args.size() = ",args.size()

# simple tests

#foo = dgm.Foo(args)
#foo2 = dgm.Foo(args)

#test = dgm.Test(args,params,comm)

#rect = dgm.Rectangle(0,0,1,2)
#goo = dgm.Goo(rect)

# Forward problem

problem = dgm.ReoProblem(args,params,comm)
#problem.solve()

# Optimization problem

ocp = dgm.ReoOptProblem(args,params,comm)
#ocp.solve()

J = ocp.computeState()
print "Objective function = ", J

ocp.computeAdjoint()

# grab out the control
control = dgm.Control(ocp.getControl())
control.zero()
print "control =", control
print "control.size() =", control.size()
print "control.num_ctrl() =", control.num_ctrl()
print "control.norm() =", control.norm()

print "Fill control with 1"
control.fill(1)
print "control.norm() =", control.norm()

# make a new direction
direction = dgm.Control(control)
print "direction =",direction

# extract the gradient from the OCP
gradient = dgm.Control(ocp.getGradient())
print "gradient =", gradient
print "gradient.size() =", gradient.size()
print "gradient.norm() =", gradient.norm()
print "Fill gradient with 3"
gradient.fill(3)
print "control.inner_product(gradient) =", control.inner_product(gradient)

#print ocp.getGradient()
#gradient.reset(ocp.getGradient())
#print "norm of real gradient = ", gradient.norm()

control.scale(10);
print "Scaled control.norm() =", control.norm()

del problem
del args
del params
del comm
