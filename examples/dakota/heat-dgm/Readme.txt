This is a steady, Robin optimal boundary control using DGM built-in 
nonlinear CG.

Running this example should be as easy as typing "run.csh" in this directory.

Compare the output to the reference output stored in screen.ref and opt.ref.

The target solution is:

  sin(pi*tan(1.3*(2.0*x-1.0))/tan(1.3))

To plot the solution do:

> gnuplot
load "plot.com"

Scott Collis
Thu Jun 16 19:04:37 MDT 2011
