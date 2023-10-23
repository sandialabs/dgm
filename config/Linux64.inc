
# Makefile Flags for Linux with GCC and standard MPICH

DIST = $(HOME)/dist64

COMPATH	= /usr/bin
CXX	= g++
CC	= gcc
FC	= g77

# dependency check flag

DEP = -MM

# parallel 

ifdef DGM_PARALLEL
override ADDONS := $(ADDONS) DGM_PARALLEL
ifdef GM
MPIDIR  = $(DIST)/mpich-gm
else
MPIDIR  = $(DIST)/mpich
endif
CXX	= mpicxx
CC	= mpicc
MPIINC  = 
MPILIB	= 
endif

# math libraries

# ATLAS

ATLASDIR = $(DIST)/atlas
MATHINC  = -I$(ATLASDIR)/include
MATHLIB  = -L$(ATLASDIR)/lib -llapack -lcblas -lf77blas -latlas -lg2c -lm

# Needed when ITL FORTRAN BLAS interface is used
# MATHLIB  = -L$(ATLASDIR)/lib -llapack -lcblas -latlas -lblas -lg2c -lm

# MKL (for everything)

#MKLDIR = /apps/intel/mkl
#override ADDONS := $(ADDONS) CMC_USE_MKL
#override ALL := $(ALL) clapack
#MATHINC = -I$(MKLDIR)/include
#MATHLIB = -L$(MKLDIR)/lib/em64t -lmkl_lapack -lmkl

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

# optimization settings

OPTXX	= -O2 $(MCPU) -ffast-math 
MOPTXX	= -O3 $(MCPU) -ffast-math -funroll-loops -fstrict-aliasing \
          -march=i686 -msse2

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

INCS    = $(MPIINC) $(FFTINC) $(MATHINC) $(BOOSTINC) $(ITLINC) $(GSLINC)
LIBS	= $(MPILIB) $(MATHLIB) $(FFTLIB) $(GSLLIB)

# X stuff

XLIBDIRS = -L/usr/X11/lib
XINCDIRS = -I/usr/include/X11
