
# Makefile Flags for generic GCC

DIST = $(HOME)/dist

COMPATH	= /usr/bin
CXX	= g++
CC	= gcc
FC	= g77

# Needed to use ITL interface in IRIX

override ADDONS := $(ADDONS) MPI_NO_CPPBIND CLEAN_SCRATCH_PPN=2
override CPPFLAGS := 

# dependency check flag

DEP = -MM

# parallel 

ifdef DGM_PARALLEL
override ADDONS := $(ADDONS) DGM_PARALLEL
MPIDIR  = $(DIST)/mpi
CXX	= g++
CC	= gcc
MPIINC  = -I$(MPIDIR)/include
MPILIB	= -L$(MPIDIR)/lib32 -lmpi
endif

# math libraries

ATLASDIR = $(DIST)/atlas/lib32
ATLASINC = -I$(ATLASDIR)

LLAPACK	= -L$(ATLASDIR) -llapack -lcblas -latlas 
LBLAS	= -lblas -lg2c -lm

FFTDIR  = $(DIST)/fftw
FFTINC  = -I$(FFTDIR)/include
FFTLIB  = -L$(FFTDIR)/lib -lrfftw -lfftw

# Boost includes

BOOSTINC = -I$(DIST)/boost

# ITL includes

ITLINC = -I$(DIST)/itl

# optimization settings

OPTXX	= -O2 $(MCPU) -ffast-math 
MOPTXX	= -O3 $(MCPU) -ffast-math -funroll-loops -fstrict-aliasing

OPT	= $(OPTXX)
MOPT	= $(MOPTXX)

OPTF	= -O2 $(MCPU) -malign-double -ffast-math
MOPTF	= -O3 $(MCPU) -malign-double -ffast-math -funroll-loops

DEBUG	= -g 
DEBUGF	= -g

# loader and loader settings

LD	= $(CXX)
DEBUGLD	= $(DEBUG)
MOPTLD	= $(MOPTXX)
OPTLD	= $(OPTXX)

INCS    = $(MPIINC) $(FFTINC) $(ATLASINC) $(BOOSTINC) $(ITLINC)
LIBS	= $(MPILIB) $(LLAPACK) $(LBLAS) $(FFTLIB)

# X stuff

XLIBDIRS = -L/usr/X11/lib
XINCDIRS = -I/usr/include/X11
