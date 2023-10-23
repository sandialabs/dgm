Unsteady optimal boundary control using a Robin boundary condition on the 
righthand side.  This version is designed to run using the DGM builtin CG
optimizer.

Running this example should be as easy as typing "run.csh" in this directory.

Compare the output to the reference output stored in screen.ref and opt.ref.

The target solution is:

  sin(pi*tan(1.3*(2.0*x-1.0))/tan(1.3))

To plot the solution do:

> gnuplot
load "plot.com"

Scott Collis
Thu Jun 16 19:07:12 MDT 2011
