
# Makefile Flags for Darwin (PowerPC) with GCC and standard MPICH

LOCAL = $(HOME)/local

COMPATH	= /usr/bin
CXX	= g++ 
CC	= gcc 
FC	= g77
#
# Compilers used for Trilinos,
# These need to be the same or you get an annoying bus error?
#
ifdef TRILINOS
COMPATH = /usr/local/bin
CXX	= $(COMPATH)/g++
CC	= $(COMPATH)/gcc
FC	= $(COMPATH)/gfortran
endif
#
# Uncomment for Intel Compilers
#
#CXX    = icpc
#CC	= icc

## set the Bison behavior based on the version of Mac OS X
#ifeq ($(firstword $(subst ., ,$(OSVER))),8) 
## do nothing for Tiger
#else
#  USE_NEW_BISON := 1
#endif

#override CCWOFF += -Wno-long-double

DEFINES +=

# dependency check flag

DEP = -MM -E

# parallel 

ifdef DGM_PARALLEL
DEFINES += DGM_PARALLEL MPICH_IGNORE_CXX_SEEK
LMPI = $(shell if [ -e mpi ] ; then echo 1; else echo 0 ; fi)
ifeq ($(LMPI),1)
  MPIDIR = mpi
  CXX = $(MPIDIR)/bin/mpicxx
  CC = $(MPIDIR)/bin/mpicc
  MPIINC =
  MPILIB =
else
  CXX = mpicxx
  CC = mpicc
  MPIINC =
  MPILIB =
endif
endif

# math libraries

# ATLAS

ATLASDIR = $(LOCAL)/atlas
MATHINC  = -I$(ATLASDIR)/include
# MATHLIB  = -L$(ATLASDIR)/lib -llapack -lcblas -lf77blas -latlas -lg2c -lm

# Needed when ITL FORTRAN BLAS interface is used
#
# Uses Atlas Cblas (faster for DGM)
#
MATHLIB  = -L$(ATLASDIR)/lib -llapack -lcblas -latlas -framework Accelerate \
-llapack
#
# Try out the Goto BLAS (slower on my iMAC)
#
#MATHLIB  = -L$(ATLASDIR)/lib -llapack -lcblas -L$(HOME)/Desktop/GotoBLAS \
#-lgoto -latlas
#
# This uses altvec Cblas
#
#MATHLIB  = -L$(ATLASDIR)/lib -llapack -latlas -framework accelerate

# FFTW

FFTDIR  = $(LOCAL)/fftw
FFTINC  = -I$(FFTDIR)/include
FFTLIB  = -L$(FFTDIR)/lib -lrfftw -lfftw

# GSL - GNU Scientific library
# note you may have to update LD_LIBRARY_PATH

GSLDIR = $(LOCAL)/gsl
GSLINC = -I$(GSLDIR)/include
GSLLIB = -L$(GSLDIR)/lib -lgsl -lgslcblas -lpthread -lm

# Boost includes

BOOSTINC = -I$(LOCAL)/boost

# ITL includes

ITLINC = -I$(LOCAL)/itl

# Trilinos

ifdef TRILINOS
  include $(INCDIR)/Trilinos.inc
  override TRILIB := $(TRIINC) -lgfortran
endif

# optimization settings

OPTXX	= -O2 $(MCPU) 
#-arch ppc -mpowerpc -malign-power -faltivec
MOPTXX  = -O3 -arch ppc -mpowerpc -malign-power -faltivec -mdynamic-no-pic

#MOPTXX	= -O3 -funroll-loops -fstrict-aliasing -fsched-interblock \
#          -falign-loops=16 -falign-jumps=16 -falign-functions=16 \
#          -falign-jumps-max-skip=15 -falign-loops-max-skip=15 \
#          -malign-natural -ffast-math

OPT	= $(OPTXX)
MOPT	= $(MOPTXX)

OPTF	= -O2 $(MCPU) -malign-double -ffast-math
MOPTF	= -O3 $(MCPU) -malign-double -ffast-math -funroll-loops

DEBUG	= -g $(MCPU) 
DEBUGF	= -g $(MCPU)

# loader and loader settings

LD	= $(CXX) 
DEBUGLD	= $(DEBUG)
MOPTLD	= $(MOPTXX)
OPTLD	= $(OPTXX)

INCS    = $(MPIINC) $(FFTINC) $(MATHINC) $(BOOSTINC) $(ITLINC) $(GSLINC) \
	  $(TRIINC)
LIBS	= $(MPILIB) $(TRILIB) $(MATHLIB) $(FFTLIB) $(GSLLIB)

# X stuff

XLIBDIRS = -L/usr/X11/lib
XINCDIRS = -I/usr/include/X11

# Library archiver

AR       = ar
