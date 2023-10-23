# Makefile Flags for Linux with PGI C++ compiler 

LOCAL = $(HOME)/local

COMPATH	= /usr/bin
CXX	= pgCC 
CC	= pgcc 
FC	= pgf90 

# dependency check flag

DEP = -MM

# setup MPI

ifdef DGM_PARALLEL
DEFINES += DGM_PARALLEL
ifeq ($(LMPI),1)
  MPIDIR = mpi
  GMDIR = gm
  CXX = $(MPIDIR)/bin/mpicxx
  CC = $(MPIDIR)/bin/mpicc 
  MPIINC = -I$(MPIDIR)/include
  MPILIB = -L$(MPIDIR)/lib -lmpich -L$(GMDIR)/lib -lgm
else
  CXX = mpicxx
  CC = mpicc
  MPIINC =
  MPILIB =
endif
endif

# math libraries

# ATLAS (using ATLAS Fortran BLAS)  This is still the fastest!

ATLASDIR = $(LOCAL)/atlas
MATHINC = -I$(ATLASDIR)/include
MATHLIB = -L$(ATLASDIR)/lib -latlas_clapack -lcblas -lf77blas -latlas -lgfortran

# You must also link in libg2c.a to use the Fortran BLAS

#MATHLIB = -L$(ATLASDIR)/lib -llapack -lcblas -latlas -lf77blas -lg2c

# MKL (for the F77 BLAS)

#MKLDIR = /usr/local/intel/mkl
#override MATHLIB := $(MATHLIB) -L$(MKLDIR)/lib/32 -lmkl

# MKL (for everything)

#MKLDIR = /usr/local/intel/mkl
#DEFINES += CMC_USE_MKL
#override ALL := $(ALL) clapack
#MATHINC = -I$(MKLDIR)/include
#MATHLIB = -L$(MKLDIR)/lib/32 -lmkl_lapack -lmkl_p4

#MATHLIB = $(MKLDIR)/lib/32/libmkl_lapack.a \
#$(MKLDIR)/lib/32/libmkl_p4.a /usr/lib/libpthread.a

# FFTW

FFTDIR  = $(LOCAL)/fftw
FFTINC  = -I$(FFTDIR)/include
FFTLIB  = -L$(FFTDIR)/lib -lrfftw -lfftw

# GSL - GNU Scientific library
# note you may have to update LD_LIBRARY_PATH

GSLDIR = $(HOME)/local/gsl
GSLINC = -I$(GSLDIR)/include
GSLLIB = -L$(GSLDIR)/lib -lgsl -lgslcblas -lpthread -lm

# Boost includes

BOOSTINC = -I$(LOCAL)/boost

# ITL includes

ITLINC = -I$(LOCAL)/itl

# PBS (include this to use the PBS_API)

ifdef PBS_API
DEFINES += PBS_API
PBSDIR  = /usr/local/pbs
PBSINC  = -I$(PBSDIR)/include
PBSLIB  = -L$(PBSDIR)/lib -lpbs
endif

# optimization settings

OPTXX	= -O2 -w $(MCPU)
MOPTXX	= -O3 -fastsse -tp barcelona-64 -w $(MCPU) 

OPT	= $(OPTXX)
MOPT	= $(MOPTXX)

OPTF	= -O2 $(MCPU) -malign-double -ffast-math
MOPTF	= -O2 $(MCPU) -malign-double -ffast-math -funroll-loops

DEBUG	= -g $(MCPU)
DEBUGF	= -g $(MCPU)

# loader and loader settings

LD	= $(CXX)
DEBUGLD	= $(DEBUG)
MOPTLD	= $(MOPTXX)
OPTLD	= $(OPTXX)

INCS    = $(MPIINC) $(FFTINC) $(MATHINC) $(BOOSTINC) $(ITLINC) $(PBSINC) \
          $(GSLINC)
LIBS	= $(MPILIB) $(MATHLIB) $(FFTLIB) $(PBSLIB) $(GSLLIB)

# X stuff

XLIBDIRS = -L/usr/X11/lib
XINCDIRS = -I/usr/include/X11
