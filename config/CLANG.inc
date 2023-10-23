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
# Default is Apple native compilers
#
COMPATH = /usr/bin
CXX     = clang++
CC      = clang
FC      = gfortran
#
# Compilers used for Trilinos,
# These need to be the same or you get an annoying bus error?
#
ifdef TRILINOS
  #COMPATH = $(LOCAL)/gcc/bin
  CXX = $(COMPATH)/clang++
  CC = $(COMPATH)/clang
  FC = $(COMPATH)/gfortran
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

#$(info USE_CMC_LAPACK: $(USE_CMC_LAPACK))
ifdef USE_TEUCHOS_LAPACK
#$(info USE_TEUCHOS_LAPACK: $(USE_TEUCHOS_LAPACK))
# Use Trilinos::Teuchos::LAPACK interface to LAPACK
ifndef TRILINOS
#$(info TRILINOS: $(TRILINOS))
ifndef CLEAN
#$(info CLEAN: $(CLEAN))
$(warning USE_TEUCHOS_LAPACK requires that TRILINOS be set)
endif
endif
MATHINC  = -I$(SDKROOT)/System/Library/Frameworks/Accelerate.framework/Versions/Current/Frameworks/vecLib.framework/Headers
MATHLIB = -framework Accelerate
else ifdef USE_OPENBLAS
# Use OpenBLAS and LAPACKE
OPENBLAS_DIR = $(LOCAL)/OpenBLAS
MATHINC  = -I$(OPENBLAS_DIR)/include
MATHLIB = -L$(OPENBLAS_DIR)/lib -lopenblas
else ifdef USE_CMC_LAPACK
#$(info USE_CMC_LAPACK: $(USE_CMC_LAPACK))
# Use the native BLAS and LAPACK with CMC interface
MATHINC  = -I$(SDKROOT)/System/Library/Frameworks/Accelerate.framework/Versions/Current/Frameworks/vecLib.framework/Headers
MATHLIB = -framework Accelerate
else
# Use BLAS and incomplete CLAPACK from ATLAS
ATLASDIR = $(LOCAL)/atlas
#$(info ATLASDIR: $(ATLASDIR))
MATHINC  = -I$(ATLASDIR)/include
MATHLIB = -framework Accelerate -Wl,-rpath $(ATLASDIR)/lib \
-L$(ATLASDIR)/lib -lclapack -lcblas -latlas -lblas
endif

#$(info MATHINC: $(MATHINC))

#
# The following are experimental Math Libs options retained for reference
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

#$(info INIT_BOOSTDIR: $(BOOSTDIR))
ifeq ($(BOOSTDIR),)
BOOSTDIR = $(LOCAL)/boost
#$(info LOCAL_BOOSTDIR: $(BOOSTDIR))
endif
LBOOST = $(shell if [ -e $(BOOSTDIR)/include ] ; then echo 1; else echo 0 ; fi)
ifeq ($(LBOOST),1)
  BOOSTINC = -I$(BOOSTDIR)/include
else
  BOOSTINC = -I$(BOOSTDIR)
endif
#$(info USE_BOOST_FS: $(USE_BOOST_FS))
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
#$(info BOOSTDIR: $(BOOSTDIR))

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

# Cuda

ifdef USE_CUDA
  CUDALIB = -Wl,-rpath $(CUDA_HOME)/lib -L$(CUDA_HOME)/lib \
  -lcudart -stdlib=libstdc++ -lc++
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

OPTXX = -O2 -std=c++14 -DDGM_DISABLE_DENORMS -ftemplate-depth=256 \
-Wall \
-Wno-uninitialized \
-Wno-init-self \
-Wno-unneeded-internal-declaration \
-Wno-unused-function \
-Wno-c++11-extensions \
-Wno-unused-private-field \
-Wno-unknown-pragmas \
-Wno-tautological-compare \
-Wno-deprecated-register \
-Wno-ambiguous-member-template \
-Wno-unused-variable \
-Wno-return-type-c-linkage \
-Wno-inconsistent-missing-override \
-Wno-c++11-long-long \
-Wno-deprecated-declarations \
-Wno-mismatched-tags \
$(MCPU)

#-Wno-self-assign-overloaded \
#-Wno-uninitialized -Winit-self \
#-Wno-unneeded-internal-declaration -Wno-unused-function -Wno-c++11-extensions \
#-Wno-unused-private-field -Wno-unknown-pragmas -Wno-tautological-compare \
#-Wno-ambiguous-member-template -Wno-unused-variable \
#-Wno-inconsistent-missing-override -Wno-return-type-c-linkage \
#-Wno-c++11-long-long -Wno-mismatched-tags

#
# Poll Mac hardware to see if AVX2 and FMA instructions are supported
#
AVX2 = $(shell ../config/mac-feature.sh AVX2)
FMA = $(shell ../config/mac-feature.sh FMA)
ifeq ($(AVX2),1)
  override MEXTRAS += -mavx2
  #$(info AVX2 = $(AVX2))
endif
ifeq ($(FMA),1)
  override MEXTRAS += -mfma
  #$(info FMA = $(FMA))
endif
#$(info MCPU = $(MCPU), MEXTRAS = $(MEXTRAS), AVX2 = $(AVX2), FMA = $(FMA))

MOPTXX = -O3 -DNDEBUG -std=c++14 -DDGM_DISABLE_DENORMS -ftemplate-depth=256 \
-fomit-frame-pointer -fPIC -arch x86_64 -fasm-blocks -fstrict-aliasing \
-fmessage-length=0 -fdiagnostics-show-note-include-stack \
-fmacro-backtrace-limit=0 -Wall -Werror -Wno-uninitialized -Winit-self \
-Wno-unneeded-internal-declaration -Wno-unused-function -Wno-c++11-extensions \
-Wno-unused-private-field -Wno-unknown-pragmas -Wno-tautological-compare \
-Wno-deprecated-register -Wno-ambiguous-member-template \
-Wno-inconsistent-missing-override \
-Wno-return-type-c-linkage \
-Wno-c++11-long-long  -Wno-deprecated-declarations -Wno-mismatched-tags \
-mfpmath=sse -msse3 $(MEXTRAS) $(MCPU)
#
# Max Optimization Extras...
#
#-Wno-self-assign-overloaded \
#-mfpmath=sse -msse3 -mavx2 $(MCPU)
#-mfma $(MCPU)
#
# Works on Early 2013 MacBook Pro but is about the same at OPT with Xcode 7
# Note that AVX2 and FMA are not supported on older macs 
#   `sysctl -a | grep "machdep.cpu.*features.*"` 
# Will show AVX2 if it is supported
#
#-mfpmath=sse -msse3 -msse4.2 -mavx $(MCPU)
#
# Works on Late 2014 iMac Retina 5k and is noticibly faster with Xcode 8
#
#-mfpmath=sse -msse3 -mavx2 -mfma $(MCPU)
#
# To use a compile time profile (doesn't seem to improve things)
#
#MOPTXX  = -fast -fcreate-profile -w $(MCPU)
#MOPTXX  = -fast -fuse-profile -w $(MCPU)

OPT   = $(OPTXX)
MOPT  = $(MOPTXX)

OPTF  = -O2 $(MCPU)
MOPTF = -fomit-frame-pointer -mfpmath=sse -msse3 -O2 $(MCPU)

DEBUG= -g -O0 -std=c++14 -D DGM_DISABLE_DENORMS -ftemplate-depth=256 \
-Wall -Wno-deprecated-register -Wno-deprecated-declarations \
-Wno-mismatched-tags -Wno-inconsistent-missing-override \
-Wno-unused-function -Wno-unused-variable \
-Wno-unused-local-typedef \
#-Wno-self-assign-overloaded  \
-Werror $(MCPU) 
DEBUGF= -g -O0 $(MCPU)

# clang 7.0.0 and beyond needs to turn off an additional warning
ifeq ($(shell test $(firstword $(subst ., ,$(CLANG_VER))) -ge 7; echo $$?),0)
override OPTXX := $(OPTXX) -Wno-unused-local-typedef 
#-mmacosx-version-min=11.6
override MOPTXX := $(MOPTXX) -Wno-unused-local-typedef 
#-mmacosx-version-min=11.6
override DEBUG := $(DEBUG) -Wno-unused-local-typedef 
#-mmacosx-version-min=11.6
endif

# loader and loader settings (-Xlinker -t gives linker details)

LD= $(CXX) 
# -mmacosx-version-min=11.6 
# -Xlinker -search_paths_first -Xlinker -t

SHARED  = -dynamiclib
SO      = so
INSTALL_NAME = -install_name
DEBUGLD= $(DEBUG)
MOPTLD= $(MOPTXX)
OPTLD= $(OPTXX)

INCS = $(MPIINC) $(DGMINC) \
       $(FFTINC) $(MATHINC) $(JSONINC) $(ITLINC) $(GSLINC) \
       $(TRIINC) $(BOOSTINC) $(BLOSCINC) $(HWLOCINC)
LIBS = $(MPILIB) \
       $(TRILIB) $(MATHLIB) $(FFTLIB) $(GSLLIB) $(BOOSTLIB) \
       $(JSONLIB) $(CUDALIB) $(BLOSCLIB) $(HWLOCLIB) 

# X stuff

XLIBDIRS = -L/usr/X11/lib
XINCDIRS = -I/usr/include/X11

# Library archiver

AR = ar
