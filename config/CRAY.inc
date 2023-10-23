# -*- Makefile -*-
# Makefile Flags for Cray-XT with GCC and MPI

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
# Default is to use native compilers
#
CXX	= CC 
CC	= cc
FC	= ftn 
#
# Check for Trilinos
#
ifdef TRILINOS
# DEFINES += DGM_USE_EPETRA
endif

DEFINES += DGM_DISABLE_DENORMS

# Determine whether we use the Cray Compiler

PRGENV = $(shell modulecmd bash list -l 2>&1 | grep PrgEnv-cray)
ifeq ($(strip $(PRGENV)),)
CRAY =
else
CRAY = 1
endif

# Our default compiler on Cray is GCC

PRGENV = $(shell modulecmd bash list -l 2>&1 | grep PrgEnv-gnu)
ifeq ($(strip $(PRGENV)),)
$(error No supported Cray PrgEnv module is loaded)
else
$(warning Using the GCC programming environment)
endif

# dependency check flag

ifdef CRAY
DEP = -M -E
else
DEP = -MM -E
endif

# setup for MPI

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
  CXX = CC 
  CC = cc
  MPIINC =
  MPILIB =
endif
endif

# math libraries

# ATLAS

ATLASDIR = $(LOCAL)/atlas
MATHINC  = -I$(ATLASDIR)/include
ifdef DGM_ATLAS_G2C
#
# Older build used G2C so you needed the g2c library
#
MATHLIB  = -L$(ATLASDIR)/lib -latlas_clapack -lcblas -latlas -lg2c -lm
else
#
# New build uses gFortran so you now need that library
#
MATHLIB  = -L$(ATLASDIR)/lib -latlas_clapack -lcblas -latlas -lm 
endif

# Enable dgeev on Cray
DEFINES += DGM_DGEEV_UNDERSCORE

# Needed when ITL FORTRAN BLAS interface is used
# MATHLIB  = -L$(ATLASDIR)/lib -latlas_clapack -lcblas -latlas -lblas -lg2c -lm

# CBLAS + LibSci

ifdef USE_LIBSCI
MATHINC = -I$(LOCAL)/cblas/include
MATHLIB = $(LOCAL)/cblas/lib/cblas_CRAY.a clapack.o
endif

# FFTW

ifdef USE_FFTW
FFTDIR  = $(LOCAL)/fftw
FFTINC  = -I$(FFTDIR)/include
FFTLIB  = -L$(FFTDIR)/lib -lrfftw -lfftw
endif

# GSL - GNU Scientific library (note you may have to update LD_LIBRARY_PATH)

ifdef USE_GSL
GSLDIR = $(LOCAL)/gsl
GSLINC = -I$(GSLDIR)/include
GSLLIB = -L$(GSLDIR)/lib -lgsl -lgslcblas -lpthread -lm 
endif

# Hwloc includes
ifdef USE_HWLOC
HWLOCDIR = $(LOCAL)/hwloc
HWLOCINC = -I$(HWLOCDIR)/include
HWLOCLIB = -L$(HWLOCDIR)/lib -lhwloc -lpciaccess -lxml2
endif

# Include the Posix Real-Time extensions library for asynchronous I/O

ifneq (,$(findstring DGM_STATE_ASYNCHRONOUS_IO,$(DEFINES)))
  IOLIB = -lrt
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
  #override TRILIB += /usr/lib64/liblapack.a -lgfortran
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

# BLOSC
ifdef USE_BLOSC
BLOSCINC = -I$(LOCAL)/blosc/include
BLOSCLIB = -L$(LOCAL)/blosc/lib -lblosc -lz
else
BLOSCINC =
BLOSCLIB =
endif

# DGM includes

DGMINC = -I$(HDRDIR)

# compiler settings

ifdef DGM_SHARED
CXXFLAGS = -fPIC
endif

# Cuda

ifdef USE_KOKKOS
CUDALIB = -L/opt/nvidia/cudatoolkit/5.5.20-1.0402.7700.8.1/lib64 -lcudart
else ifdef USE_CUDA
CUDALIB = -L/opt/nvidia/cudatoolkit/5.5.20-1.0402.7700.8.1/lib64 -lcudart
endif

# whether to use C++11

ifdef TRILINOS
CXXSTD = -std=c++11
else
CXXSTD = -std=c++11
endif

# optimization settings

ifdef CRAY
#
# Settings for the CRAY C++ compiler
#
OPTXX = $(CXXFLAGS) -O2 -h list=m -h nomessage=236:1055:10082:10144 $(MCPU)  
MOPTXX	= $(CXXFLAGS) -O3 $(CXXSTD) $(MCPU)
else
#
# Settings for GCC on the Cray XK-6
#
OPTXX = $(CXXFLAGS) -O2 $(CXXSTD) -march=bdver1 -mfpmath=sse \
-mfma4 -mavx -funroll-all-loops -mprefer-avx128 -fprefetch-loop-arrays \
--param prefetch-latency=300 -minline-all-stringops -ffast-math \
-fno-finite-math-only -Wno-deprecated-declarations $(MCPU) 
MOPTXX = $(CXXFLAGS) -O3 -DNDEBUG $(CXXSTD) -march=bdver1 -mfpmath=sse \
-mfma4 -mavx -funroll-all-loops -mprefer-avx128 -fprefetch-loop-arrays \
--param prefetch-latency=300 -minline-all-stringops -ffast-math \
-fno-finite-math-only $(MCPU) 
#
# Using special settings for GCC on Muzia
# 
ifeq ($(SYSTEM),muzia)
OPTXX	= $(CXXFLAGS) -O2 $(CXXSTD) $(MCPU)
MOPTXX	= $(CXXFLAGS) -Ofast $(CXXSTD) $(MCPU)
endif
endif

OPT	= $(OPTXX)
MOPT	= $(MOPTXX)

OPTF	= -O2 $(MCPU) -malign-double 
MOPTF	= -O3 $(MCPU) -malign-double -funroll-loops

DEBUG	= -g $(MCPU) 
DEBUGF	= -g $(MCPU)

# loader and loader settings

LD	= $(CXX)
SHARED  = -shared
SO      = so
ifndef CRAY
LDFLAGS = -Xlinker --allow-multiple-definition
else
LDFLAGS = 
endif
DEBUGLD	= $(DEBUG) $(LDFLAGS) 
MOPTLD  = $(MOPTXX) $(LDFLAGS) 
OPTLD   = $(OPTXX) $(LDFLAGS) 

INCS    = $(MPIINC) $(FFTINC) $(MATHINC) $(BOOSTINC) $(ITLINC) $(GSLINC) \
          $(TRIINC) $(JSONINC) $(DGMINC) $(BLOSCINC) $(HWLOCINC)
LIBS	= $(MPILIB) $(TRILIB) $(MATHLIB) $(FFTLIB) $(GSLLIB) $(IOLIB) \
	  $(BOOSTLIB) $(JSONLIB) $(CUDALIB) $(BLOSCLIB) $(HWLOCLIB)

# X stuff

XLIBDIRS = -L/usr/X11/lib
XINCDIRS = -I/usr/include/X11

# Library archiver

AR = ar
