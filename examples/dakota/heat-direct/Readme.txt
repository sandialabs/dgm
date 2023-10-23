This is a steady, Robin boundary control example with the Dakota direct 
interface using explicit RK4.  

You can run the test simply by typing run.csh # where # is the number of 
processors for the parallel run.  # can = 1.  If # is omitted, the script
will try to execute a serial version of dgm_dak.exe which requires a serial
build of the DAKOTA library.

Compare the output to screen.ref and opt.ref.

Scott Collis
1/20/2009
