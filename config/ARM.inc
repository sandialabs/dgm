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
# Use GCC compilers
#
COMPATH	= /usr/bin
CXX	= g++
CC	= gcc 
FC	= gfortran 

# Needed to use ITL interface

DEFINES += DGM_DISABLE_RUNTIME_CONTROL
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

# BLAS and LAPACK 

MATHINC = -I$(OPENBLAS_DIR)/include
MATHLIB = -L$(OPENBLAS_DIR)/lib -lopenblas

# Fortran mangle dgeev symbol
DEFINES += DGM_DGEEV_UNDERSCORE
ifndef TRILINOS
MATHLIB += /usr/lib64/liblapack.so
endif

# FFTW

ifdef USE_FFTW
FFTDIR  = $(LOCAL)/fftw
FFTINC  = -I$(FFTDIR)/include
FFTLIB  = -L$(FFTDIR)/lib -lrfftw -lfftw
endif

# Hwloc - Hardware locality library

ifdef USE_HWLOC
HWLOCDIR = $(LOCAL)/hwloc
HWLOCINC = -I$(HWLOCDIR)/include
HWLOCLIB = -L$(HWLOCDIR)/lib -lhwloc
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

# DGM includes

DGMINC = -I$(HDRDIR)

# ITL includes

ifdef USE_ITL
ITLINC = -I$(LOCAL)/itl
endif

# Trilinos

ifdef TRILINOS
  include $(INCDIR)/Trilinos.inc
  override TRILIB := $(TRILIB) /usr/lib64/liblapack.so
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

# compiler flags

ifdef DGM_SHARED
CXXFLAGS = -fPIC
endif

# optimization settings

OPTXX	= $(CXXFLAGS) -O2 -std=c++11 -w $(MCPU)
MOPTXX	= $(CXXFLAGS) -O3 -std=c++11 -mtune=thunderx2t99 -mcpu=thunderx2t99 \
$(MCPU)

OPT	= $(OPTXX)
MOPT	= $(MOPTXX)

OPTF	= -O2 -std=c++11 $(MCPU) -malign-double -ffast-math
MOPTF	= -O2 -std=c++11 $(MCPU) -malign-double -ffast-math -funroll-loops

DEBUG	= -g -std=c++11 -Wall -diag-disable 654 -diag-disable 981 -diag-disable 869 \
          -diag-disable 1572 -diag-disable 1418 -diag-disable 383 \
          -diag-disable 1419 -diag-disable 810 -diag-disable 193 $(MCPU)
#DEBUG	= -g -diag-disable 654 -diag-disable 2215 $(MCPU)
DEBUGF	= -g -std=c++11 $(MCPU)

# loader and loader settings

LD	= $(CXX)
SHARED  = -Bdynamic
SO      = so
DEBUGLD	= $(DEBUG)
MOPTLD	= $(MOPTXX)
OPTLD	= $(OPTXX)

INCS    = $(MPIINC) $(FFTINC) $(MATHINC) $(BOOSTINC) $(ITLINC) $(PBSINC) \
          $(GSLINC) $(TRIINC) $(JSONINC) $(DGMINC) $(HWLOCINC)
LIBS	= $(MPILIB) $(TRILIB) $(MATHLIB) $(FFTLIB) $(PBSLIB) $(GSLLIB) \
	  $(BOOSTLIB) $(JSONLIB) $(HWLOCLIB)

# X11 stuff

XLIBDIRS = -L/usr/X11/lib
XINCDIRS = -I/usr/include/X11

# Library archiver

AR = ar
