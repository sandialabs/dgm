===============================================================================
Discontinuous Galerkin Test Case         S. Scott Collis                 Sandia
===============================================================================
This is a test case for two-dimensional, inviscid, compressible flow over
a circular cylinder solved using the discontinuous Galerkin Method with Lax
Friedrichs flux on a quadrilateral mesh composed of a mix of 6th and 3rd order
tensor product elements.

The two executables have been built using GCC v2.96 under RedHat 7.1.  The
parallel executable (dgm.p) is compiled using the Myrinet enabled 
MPICH-1.2.1..7b.  The code uses MPI-IO (ROMIO) to perform all parallel IO.

To run on a single processor:

  dgm.s cyl

To run in parallel, you can either use the two PBS scripts included, or, 
depending on your configuration, you may be able to run directly using

  mpirun.ch_gm -np 16 dgm.p cyl

or from an interactive PBS job 

  qsub -I -l walltime=0:15:00,nodes=8:ppn=2
  mpiexec dgm.p cyl

As the code runs it outputs the time step, simulation time, and cpu time. 
At the end of the run, the total computation time is also displayed.

On our 1.7GHz Pentium IV Xeon I get the following performance:

CPUS     avg time/step    Speed-up
===================================
1           0.20656         1.00        
2	    0.12809         1.61
4           0.077187        2.68
8           0.043985        4.70
16          0.022762        9.07
32          0.013445        15.36
64          0.008971        23.03

NOTE:  The poor scaling is due to the small problem size and the poor load
balancing.

This code and all files included in this package are NOT to be distributed
without written permission of the author, Scott Collis.

Copyright:  S. Scott Collis
            Rice University, MS 321
            Houston, TX 77005-1892
            (713) 348-3617
            collis@rice.edu
===============================================================================

6-11-2003:  Timings using ICC compiler with non-weighted Metis partitions.

CPUS     avg time/step    Speed-up
===================================
1           0.18350        1.00        
2	    0.11381        1.61
4           0.05390        3.40
8           0.03865        4.75

6-11-2003:  Timings using ICC compiler with weighted Metis partitions.

CPUS     avg time/step    Speed-up
===================================
1           0.18350        1.00
2           0.09524        1.93
4           0.04980        3.68
8           0.02661        6.90

11-29-2004:  Spirit (IA64 cluster, GCC with MKL)

CPUS     avg time/step    Speed-up
===================================
1           0.11139	    1.0
2           0.061218	    1.82
4           0.029603	    3.76
8           0.016293        6.84
16          0.0092219       12.08
32	    0.0062175	    17.92

11-29-2004:  Spirit (IA64 cluster, GCC with ATLAS)

Cpus     avg time/step    Speed-up
===================================
1           0.098658	   1.00
2           0.053664	   1.84
4           0.028712	   3.44
8           0.013699	   7.20
16          0.0086419	   11.42
32	    0.0060334	   16.35

04-210-2006:  Odin (Opteron, GCC with ATLAS)

CPUS     avg time/step    Speed-up
===================================
1	   8.0566e-02       1.00
2          3.9525e-02	    2.04
4          2.0091e-02	    4.01
8          9.9096e-03	    8.13
16         5.1875e-03	    15.53
32	   3.3662e-03	    23.93
64	   2.6731e-03	    30.14

