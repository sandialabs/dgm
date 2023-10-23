# Makefile Flags for Intel C++ compiler 

ifdef DGM_TPL 
  LOCAL = $(DGM_TPL)
else
  LLOCAL = $(shell if [ -e local ] ; then echo 1; else echo 0 ; fi)
  ifeq ($(LLOCAL),1)
    LOCAL = local
  else
    LOCAL = $(HOME)/local
  endif
endif
#
# Use Intel compilers
#
COMPATH	= /usr/bin
CXX	= icpc
CC	= icc
FC	= ifort 

# Needed to use ITL interface

DEFINES += ICC 
#NO_SYSTEM CLEAN_SCRATCH_PPN=2

# dependency check flag

DEP = -MM

# setup MPI

ifdef DGM_PARALLEL
DEFINES += DGM_PARALLEL
LMPI = $(shell if [ -e mpi ] ; then echo 1; else echo 0 ; fi)
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

UNAME = $(shell uname)

# math libraries

# ATLAS (using ATLAS Fortran BLAS)  This is still the fastest!

ATLASDIR = $(LOCAL)/atlas
MATHINC = -I$(ATLASDIR)/include
MATHLIB = -L$(ATLASDIR)/lib -latlas_clapack -lcblas -lf77blas -latlas -lg2c

# On Darwin, the following works

ifeq ($(UNAME),Darwin)
  #MATHLIB = -L$(ATLASDIR)/lib -lclapack -lcblas -latlas
  MATHLIB = -framework Accelerate -L$(ATLASDIR)/lib -lclapack -lcblas -latlas -lblas
endif

# Sometimes you must also link in libg2c.a by hand to use the Fortran BLAS

#MATHLIB = -L$(ATLASDIR)/lib -llapack -lcblas -latlas \
#-lblas /usr/lib/gcc-lib/i386-redhat-linux/2.96/libg2c.a

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

ifdef USE_FFTW
FFTDIR  = $(LOCAL)/fftw
FFTINC  = -I$(FFTDIR)/include
FFTLIB  = -L$(FFTDIR)/lib -lrfftw -lfftw
endif

# GSL - GNU Scientific library (note you may have to update LD_LIBRARY_PATH)

ifdef USE_GSL
GSLDIR = $(HOME)/local/gsl
GSLINC = -I$(GSLDIR)/include
GSLLIB = -L$(GSLDIR)/lib -lgsl -lgslcblas -lpthread -limf -lm
endif

# Boost includes

ifeq ($(BOOSTDIR),)
BOOSTDIR = $(LOCAL)/boost
endif
LBOOST = $(shell if [ -e $(BOOSTDIR)/include ] ; then echo 1; else echo 0 ; fi)
ifeq ($(LBOOST),1)
  BOOSTINC = -I$(BOOSTDIR)/include
else
  BOOSTINC = -I$(BOOSTDIR)
endif
ifdef USE_BOOST_FS
BOOSTLIBTMP = -L$(BOOSTDIR)/lib -lboost_filesystem -lboost_system \
                                -lboost_serialization
ifdef DGM_PARALLEL
BOOSTLIB = $(BOOSTLIBTMP) -lboost_mpi
else
BOOSTLIB = $(BOOSTLIBTMP)
endif
else
BOOSTLIB = 
endif

# ITL includes

ifdef USE_ITL
ITLINC = -I$(LOCAL)/itl
endif

# Trilinos

ifdef TRILINOS
  include $(INCDIR)/Trilinos.inc
  override TRILIB := $(TRILIB) /usr/lib64/liblapack.a
# DEFINES += DGM_USE_EPETRA
endif

# PBS (include this to use the PBS_API)

ifdef PBS_API
DEFINES += PBS_API
PBSDIR  = /usr/local/pbs
PBSINC  = -I$(PBSDIR)/include
PBSLIB  = -L$(PBSDIR)/lib -lpbs
endif

# JSON parser

JSONDIR = ../json
ifdef USE_JSON
JSONINC = -I$(JSONDIR)/include/
JSONLIB  =
else
JSONINC =
JSONLIB =
endif

DGMINC = -I$(HDRDIR)

# compiler flags

ifdef DGM_SHARED
CXXFLAGS = -fPIC
endif

# optimization settings

#OPTXX	= $(CXXFLAGS) -O2 -vec -diag-enable=vec -qopt-report -qopt-report-file=stdout -qopt-report-phase=vec -std=c++11 -axCORE-AVX2 -w $(MCPU)
OPTXX	= $(CXXFLAGS) -O2 -vec -diag-enable=vec -std=c++11 -axCORE-AVX2 -w $(MCPU)
MOPTXX	= $(CXXFLAGS) -O3 -tpp7 -xW $(MCPU) -ipo -fno-alias

OPT	= $(OPTXX)
MOPT	= $(MOPTXX)

OPTF	= -O2 $(MCPU) -malign-double -ffast-math
MOPTF	= -O2 $(MCPU) -malign-double -ffast-math -funroll-loops

DEBUG	= -g -Wall -diag-disable 654 -diag-disable 981 -diag-disable 869 \
          -diag-disable 1572 -diag-disable 1418 -diag-disable 383 \
          -diag-disable 1419 -diag-disable 810 -diag-disable 193 $(MCPU)
#DEBUG	= -g -diag-disable 654 -diag-disable 2215 $(MCPU)
DEBUGF	= -g $(MCPU)

# loader and loader settings

LD	= $(CXX)
SHARED  = -Bdynamic
SO      = so
DEBUGLD	= $(DEBUG)
MOPTLD	= $(MOPTXX)
OPTLD	= $(OPTXX)

INCS    = $(MPIINC) $(FFTINC) $(MATHINC) $(BOOSTINC) $(ITLINC) $(PBSINC) \
          $(GSLINC) $(TRIINC) $(JSONINC) $(DGMINC)
LIBS	= $(MPILIB) $(TRILIB) $(MATHLIB) $(FFTLIB) $(PBSLIB) $(GSLLIB) \
	  $(BOOSTLIB) $(JSONLIB)

# X11 stuff

XLIBDIRS = -L/usr/X11/lib
XINCDIRS = -I/usr/include/X11

# Library archiver

AR = ar
