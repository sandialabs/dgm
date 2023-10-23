
# Makefile Flags for Linux with Intel C++ compiler

DIST = $(HOME)/dist64

COMPATH	= /usr/bin
CXX	= icpc -w
CC	= icc
FC	= g77

# Needed to use ITL interface in IRIX

override ADDONS := $(ADDONS) ICC 

# dependency check flag

DEP = -MM

# parallel 

ifdef DGM_PARALLEL
override ADDONS := $(ADDONS) DGM_PARALLEL
MPIDIR  = $(DIST)/mpich
GMDIR   = $(DIST)/gm
CXX	= mpicxx -w
CC	= mpicc
#MPIINC  = -I$(MPIDIR)/include
#MPILIB	= -L$(MPIDIR)/lib -lmpich -L$(GMDIR)/lib -lgm
endif

# math libraries

# ATLAS (using ATLAS Fortran BLAS)  This is still the fastest!

ATLASDIR = $(DIST)/atlas
MATHINC = -I$(ATLASDIR)/include
#MATHLIB = -L$(ATLASDIR)/lib -llapack -lcblas -latlas

# You must also link in libg2c.a to use the Fortran BLAS

MATHLIB = -L$(ATLASDIR)/lib -llapack -lcblas -latlas -lblas -lg2c
# /usr/lib/gcc-lib/i386-redhat-linux/2.96/libg2c.a

# MKL (for the F77 BLAS)

#MKLDIR = /apps/intel/mkl
#override MATHLIB := $(MATHLIB) -L$(MKLDIR)/lib/em64t -lmkl

# MKL (for everything)

MKLDIR = /apps/intel/mkl
#override ADDONS := $(ADDONS) CMC_USE_MKL
#override ALL := $(ALL) clapack
#MATHINC = -I$(MKLDIR)/include
#MATHLIB = -L$(MKLDIR)/lib/em64t -lmkl_lapack -lmkl

#MATHLIB = $(MKLDIR)/lib/em64t/libmkl_lapack.a \
#$(MKLDIR)/lib/em64t/libmkl_p4.a /usr/lib/libpthread.a

# FFTW

FFTDIR  = $(DIST)/fftw
FFTINC  = -I$(FFTDIR)/include/fftw
FFTLIB  = -L$(FFTDIR)/lib/fftw -lrfftw -lfftw

# GSL - GNU Scientific library
# note you may have to update LD_LIBRARY_PATH

GSLDIR = $(HOME)/local64
GSLINC = -I$(GSLDIR)/include
GSLLIB = -L$(GSLDIR)/lib -lgsl -lgslcblas -lpthread -lm

# Boost includes

BOOSTINC = -I$(DIST)/boost

# ITL includes

ITLINC = -I$(DIST)/itl

# PBS (include this to use the PBS_API)

ifdef PBS_API
override ADDONS := $(ADDONS) PBS_API
PBSDIR  = /usr/local/pbs
PBSINC  = -I$(PBSDIR)/include
PBSLIB  = -L$(PBSDIR)/lib -lpbs
endif

# optimization settings

OPTXX	= -O2 $(MCPU)
MOPTXX	= -O3 -tpp7 -xW $(MCPU) -ipo -fno-alias

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
