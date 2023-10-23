This is a steady, Robin optimal boundary control using Dakota with the 
file system interface and the new builtin NonlinearCG solver.

Running this example should be as easy as typing "run" in this directory as
long as dakota, dprepro, and dgm_opt.exe are in your path.

Compare the output to the reference output stored in screen.ref and opt.ref.

Note that this uses the fork interface instead of the system.  With the
system interface, you must make sure that all result.out.iter files are
removed between subsequent runs as all it does is look for file existance
are you will get bogus answers.

Scott Collis
1/20/2009
