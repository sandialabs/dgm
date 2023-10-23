# Makefile Flags for Darwin (i386) with GCC and standard MPICH

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
# Default is Apple native compilers
#
COMPATH	= /usr/bin
CXX = g++
CC = gcc
FC = g77
#
# Compilers used for Trilinos,
# These need to be the same or you get an annoying bus error?
#
ifdef TRILINOS
  #COMPATH = $(LOCAL)/gcc/bin
  CXX = $(COMPATH)/g++
  CC = $(COMPATH)/gcc
  FC = $(COMPATH)/gfortran
endif
#
# Uncomment for Intel Compilers
#
#CXX = icpc
#CC  = icc
#FC  = ifort

OSVER = $(shell uname -r)
ifeq ($(firstword $(subst ., ,$(OSVER))),8)
else
  USE_NEW_BISON := 1
endif

#override CCWOFF := $(CCWOFF)

DEFINES +=

# dependency check flag

DEP = -MM -E

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
#
# Uses Atlas Cblas (typicall faster for DGM) but must use TIME_INT_CBLAS
#
#MATHLIB = -L$(ATLASDIR)/lib -latlas_core -latlas_clapack -latlas_cblas
#
# Add in the Fortran BLAS (needed when ITL Fortran BLAS interface is used)
#
#MATHLIB = -L$(ATLASDIR)/lib -latlas_core -latlas_clapack -latlas_cblas -lblas
#
# This works with static Atlas when you use -search_paths_first
# This is a touch faster on cyl
#
MATHLIB = -L$(ATLASDIR)/lib -lclapack -lcblas -latlas -lblas -llapack
#
# Try out the Goto BLAS (slower on my iMAC)
#
#MATHLIB  = -L$(ATLASDIR)/lib -latlas -latlas_clapack -lcblas \
#  -L$(HOME)/Desktop/GotoBLAS -lgoto
#
# This uses vecLib Cblas (used to be a factor of two slower on my MacBook Pro)
#
#MATHLIB  = -L$(ATLASDIR)/lib -latlas -latlas_clapack -framework accelerate
#
# This pulls the default system cblas and blas (which also comes from vecLib)
# On my new Core i7 MacBook Pro, this is 13% faster on 3d
#
#MATHLIB  = -L$(ATLASDIR)/lib -latlas_clapack -latlas -lblas

# FFTW

ifdef USE_FFTW
FFTDIR  = $(LOCAL)/fftw
FFTINC  = -I$(FFTDIR)/include
FFTLIB  = -L$(FFTDIR)/lib -lrfftw -lfftw
endif

# GSL - GNU Scientific library (note you may have to update DYLD_LIBRARY_PATH)

ifdef USE_GSL
GSLDIR = $(LOCAL)/gsl
GSLINC = -I$(GSLDIR)/include
GSLLIB = -L$(GSLDIR)/lib -lgsl -lpthread -lm
#GSLLIB = -L$(GSLDIR)/lib -lgsl -lgslcblas -lpthread -lm
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
  override TRILIB += -framework Accelerate
  #override TRILIB += -lgfortran
endif

# JSON parser

JSONDIR = ../json
ifdef USE_JSON
  JSONINC = -I$(JSONDIR)/include/
  JSONLIB =
else
  JSONINC =
  JSONLIB =
endif

# GTEST

ifdef USE_GTEST
  GTESTINC = -I$(HOME)/dist/gtest-1.7.0/include
  GTESTLIB = -L$(HOME)/dist/gtest-1.7.0 -lgtest
else
  GETSTINC =
  GTESTLIB =
endif

# compiler settings

CXXFLAGS =

# optimization settings

OPTXX	= -O2 -Wall -Wno-uninitialized -Winit-self \
-Wno-unknown-pragmas -Werror $(MCPU)
MOPTXX  = -fast -Wall -Wno-uninitialized -Winit-self -Wno-unknown-pragmas \
-Werror -mfpmath=sse -march=core2 -msse3 -msse4 -w $(MCPU)
#MOPTXX  = -fast -fcreate-profile -w $(MCPU)
#MOPTXX  = -fast -fuse-profile -w $(MCPU)

OPT	= $(OPTXX)
MOPT	= $(MOPTXX)

OPTF	= -O2 $(MCPU)
MOPTF	= -fomit-frame-pointer -mfpmath=sse -msse3 -O2 $(MCPU)

DEBUG	= -g -Wall $(MCPU)
DEBUGF	= -g $(MCPU)

# loader and loader settings (-Xlinker -t gives linker details)

LD	= $(CXX)
#
# -Xlinker -search_paths_first -Xlinker -t
#
SHARED  = -dynamiclib
SO      = so
INSTALL_NAME = -install_name
DEBUGLD	= $(DEBUG)
MOPTLD	= $(MOPTXX)
OPTLD	= $(OPTXX)

INCS    = $(MPIINC) $(FFTINC) $(MATHINC) $(BOOSTINC) $(ITLINC) $(GSLINC) \
	  $(TRIINC) $(JSONINC) $(GTESTINC)
LIBS	= $(MPILIB) $(TRILIB) $(MATHLIB) $(FFTLIB) $(GSLLIB) $(BOOSTLIB) \
	  $(JSONLIB) $(GTESTLIB)

# X stuff

XLIBDIRS = -L/usr/X11/lib
XINCDIRS = -I/usr/include/X11

# Library archiver

AR = ar
RANLIB = ranlib
