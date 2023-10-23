#!/bin/tcsh
#SBATCH --time=00:15:00
#SBATCH --account=FY104026 
#SBATCH -N 4
#SBATCH --job-name cyl
set nodes=$SLURM_JOB_NUM_NODES
set cores=16
@ n = $nodes * $cores
#
# To use OpenMPI (faster)
#
#module switch mpi mpi/openmpi-1.2.8_gcc-4.1.2
#mpiexec /apps/contrib/numa_wrapper-16ppn ~/chamisa/GCCp/pdgm.exe cyl
#
# To use OpenMPI with maximal optimization (faster)
#
module switch mpi mpi/openmpi-1.2.8_gcc-4.1.2
mpiexec /apps/contrib/numa_wrapper-16ppn ~/chamisa/GCCpm/pdgm.exe cyl
#
# To use Mvapich
#
#module switch mpi mpi/mvapich-1.1_gcc-4.1.2
#srun -N $nodes -n $n /apps/contrib/numa_wrapper-16ppn \
# ~/chamisa/GCCmva/pdgm.exe cyl
exit 0
