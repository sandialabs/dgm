# -*- Makefile -*-
# Makefile Flags for Linux with GCC and standard MPICH

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

DEFINES +=

# dependency check flag

DEP = -MM

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
ifdef DGM_ATLAS_G2C
#
# Older build used G2C so you needed the g2c library
#
MATHLIB  = -L$(ATLASDIR)/lib -latlas_clapack -lcblas -lf77blas -latlas \
-lg2c -lm
else
#
# New build uses gFortran so you now need that library
#
MATHLIB  = -L$(ATLASDIR)/lib -latlas_clapack -lcblas -latlas -lm
endif

# Needed when ITL FORTRAN BLAS interface is used
# MATHLIB  = -L$(ATLASDIR)/lib -latlas_clapack -lcblas -latlas -lblas -lg2c -lm

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

# Include the Posix Real-Time extensions library for asynchronous I/O

ifneq (,$(findstring DGM_STATE_ASYNCHRONOUS_IO,$(DEFINES)))
  IOLIB = -lrt
endif

# Boost includes

BOOSTDIR = $(LOCAL)/boost
LBOOST = $(shell if [ -e $(BOOSTDIR)/include ] ; then echo 1; else echo 0 ; fi)
ifeq ($(LBOOST),1)
  BOOSTINC = -I$(BOOSTDIR)/include
else
  BOOSTINC = -I$(BOOSTDIR)
endif
ifdef USE_BOOST_FS
BOOSTLIBTMP = -L$(BOOSTDIR)/lib -lboost_filesystem -lboost_system

#                                -lboost_serialization
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

# compiler settings

ifdef DGM_SHARED
CXXFLAGS = -fPIC
endif

# optimization settings

OPTXX	= $(CXXFLAGS) -O2 -tp bulldozer -Msmartalloc=huge -Mconcur -Mvect \
-Mipa=fast,inline -Mvect=prefetch -Munroll -Mfprelaxed -Minform=severe $(MCPU)  
MOPTXX	= $(CXXFLAGS) -O3 -Wall -Wuninitialized -Winit-self -Werror $(MCPU) \
          -funroll-loops -fstrict-aliasing -march=core2 -msse -msse2 \
          -msse3 -mmmx 

OPT	= $(OPTXX)
MOPT	= $(MOPTXX)

OPTF	= -O2 $(MCPU) -malign-double 
MOPTF	= -O3 $(MCPU) -malign-double -funroll-loops

DEBUG	= -g -Wall $(MCPU) 
DEBUGF	= -g $(MCPU)

# loader and loader settings

LD	= $(CXX)
SHARED  = -shared
SO      = so
DEBUGLD	= $(DEBUG)
MOPTLD	= $(MOPTXX)
OPTLD	= $(OPTXX)

INCS    = $(MPIINC) $(FFTINC) $(MATHINC) $(BOOSTINC) $(ITLINC) $(GSLINC) \
          $(TRIINC) $(JSONINC)
LIBS	= $(MPILIB) $(TRILIB) $(MATHLIB) $(FFTLIB) $(GSLLIB) $(IOLIB) \
	  $(BOOSTLIB) $(JSONLIB)

# X stuff

XLIBDIRS = -L/usr/X11/lib
XINCDIRS = -I/usr/include/X11

# Library archiver

AR = ar
