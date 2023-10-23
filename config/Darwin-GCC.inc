#
# Makefile Flags for Darwin (i386) with CLANG and MPI
#
CLANG_VER = $(word 4,$(shell clang --version))
#
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
# Use GCC installed compilers 
#
ifndef GCCVER
  GCCVER  = 10 
endif
COMPATH	= /usr/local/bin
CXX     = g++-$(GCCVER)
CC      = gcc-$(GCCVER)
FC      = gfortran-$(GCCVER)
#
# Compilers used for Trilinos,
# These need to be the same or you get an annoying bus error?
#
ifdef TRILINOS
  #COMPATH = $(LOCAL)/gcc/bin
  CXX = $(COMPATH)/clang++
  CC = $(COMPATH)/clang
  # FC = $(COMPATH)/gfortran
endif

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

# Check for version of MacOS >= 16 which is SIERRA
MAJOR_OSVER = $(firstword $(subst ., ,$(OSVER)))
ifeq ($(shell test $(MAJOR_OSVER) -ge 16; echo $$?),0)
SDKROOT = /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk
else
SDKROOT =
endif

ifdef USE_TEUCHOS_LAPACK
# Use Trilinos::Teuchos::LAPACK interface to LAPACK
ifndef TRILINOS
ifndef CLEAN
$(warning USE_TEUCHOS_LAPACK requires that TRILINOS be set)
endif
endif
MATHINC  = -I$(SDKROOT)/System/Library/Frameworks/Accelerate.framework/Versions/Current/Frameworks/vecLib.framework/Headers
MATHLIB = -framework Accelerate
else ifdef USE_CMC_LAPACK
# Use the native BLAS and LAPACK with CMC interface
MATHINC  = -I$(SDKROOT)/System/Library/Frameworks/Accelerate.framework/Versions/Current/Frameworks/vecLib.framework/Headers
MATHLIB = -framework Accelerate
else
# ATLAS
ATLASDIR = $(LOCAL)/atlas
MATHINC  = -I$(ATLASDIR)/include
MATHLIB = -framework Accelerate -Wl,-rpath $(ATLASDIR)/lib \
-L$(ATLASDIR)/lib -lclapack -lcblas -latlas -lblas
endif
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

# Hwloc - Hardware locality library
ifdef USE_HWLOC
HWLOCDIR = $(LOCAL)/hwloc
HWLOCINC = -I$(HWLOCDIR)/include
HWLOCLIB = -L$(HWLOCDIR)/lib -lhwloc
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
BOOSTLIBTMP = -Wl,-rpath $(BOOSTDIR)/lib -L$(BOOSTDIR)/lib \
-lboost_filesystem -lboost_system -lboost_serialization
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

# CUDA 

ifdef USE_CUDA 
CUDALIB = -Wl,-rpath $(CUDA_HOME)/lib -L$(CUDA_HOME)/lib -lcudart -stdlib=libstdc++ -lc++
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

# BLOSC 

ifdef USE_BLOSC
BLOSCINC = -I$(LOCAL)/blosc/include
BLOSCLIB = -L$(LOCAL)/blosc/lib -lblosc
else
BLOSCINC =
BLOSCLIB =
endif

# DGM includes

DGMINC = -I$(HDRDIR)

# compiler settings

CXXFLAGS = 

# optimization settings

OPTXX = -O2 -std=c++11 -D DGM_DISABLE_DENORMS -Wno-deprecated-declarations \
-mfpmath=sse -msse3 -mavx2 -mfma
MOPTXX = -Ofast -std=c++11 -fopenmp -D DGM_DISABLE_DENORMS \
-Wno-deprecated-declarations -mfpmath=sse -msse3 -mavx2 -mfma

OPT	= $(OPTXX)
MOPT	= $(MOPTXX)

OPTF	= -O2 $(MCPU)
MOPTF	= -fomit-frame-pointer -mfpmath=sse -msse3 -O2 $(MCPU)

DEBUG	= -Og -g -std=c++11 -D DGM_DISABLE_DENORMS \
-Wall -Wno-deprecated-register -Wno-deprecated-declarations -Wno-mismatched-tags -Werror $(MCPU) 
DEBUGF	= -Og -g $(MCPU)

# loader and loader settings (-Xlinker -t gives linker details)

LD	= $(CXX) 
# -Xlinker -search_paths_first -Xlinker -t

SHARED  = -dynamiclib
SO      = so
INSTALL_NAME = -install_name
DEBUGLD	= $(DEBUG)
MOPTLD	= $(MOPTXX)
OPTLD	= $(OPTXX)

INCS    = $(MPIINC) $(FFTINC) $(MATHINC) $(BOOSTINC) $(ITLINC) $(GSLINC) \
          $(TRIINC) $(JSONINC) $(DGMINC) $(BLOSCINC) $(HWLOCINC)
LIBS	= $(MPILIB) $(TRILIB) $(MATHLIB) $(FFTLIB) $(GSLLIB) $(BOOSTLIB) \
          $(JSONLIB) $(CUDALIB) $(BLOSCLIB) $(HWLOCLIB) 

# X stuff

XLIBDIRS = -L/usr/X11/lib
XINCDIRS = -I/usr/include/X11

# Library archiver

AR = ar
