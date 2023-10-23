#
# Makefile include for linking DGM with Dakota
#
# Author:    S. Scott Collis
# Copyright: (c)2010 Sandia National Laboratories
# 
# Thu Oct 29 09:52:14 MDT 2009

ifdef DAKOTA
  DAKOTA_HOME = $(DAKOTA)
else
  DAKOTA_HOME = $(HOME)/local/dakota
endif

DAKOTA_INCL = -I$(DAKOTA_HOME)/include

DAKOTA_LIB_PATH = -L$(DAKOTA_HOME)/lib

DAKOTA_LIBS = -ldakota -lpecos -llhs -lsurfpack -lconmin -lddace -lfsudace \
-ljega -lopt -lpsuade -lnewmat -lncsuopt -lsparsegrid -lcoliny -lcolin	   \
-lpebbl -lutilib -l3po -lnappspack -lappspack -lconveyor -lshared -lcdd	   \
-lcport -lamplsolver -lnidr -lthyratpetra -lthyraepetraext -lthyraepetra   \
-lthyra -lepetraext -ltpetrainout -ltpetra -ltriutils -lzoltan -lepetra	   \
-lkokkoslinalg -lkokkosnodeapi -lkokkos -lrtop -ltpi -lteuchos

ifeq ($(ARCH),ICC)
F90_LIB_PATH = -L/projects/global/x86_64/compilers/intel/intel-10.1-fce-015/lib
F90_LIBS = -lifport -lifcore
else
F90_LIB_PATH = -L/usr/local/lib
F90_LIBS = -lgfortran
endif

ifeq ($(ARCH),Darwin-i386)
DAKOTA_MATH_LIBS = 
else
DAKOTA_MATH_LIBS = -L/usr/lib64 -llapack -lblas
endif

# Modify for DAKOTA
override INCS := $(INCS) $(DAKOTA_INCL)
override LIBS := $(DAKOTA_LIB_PATH) $(DAKOTA_LIBS) \
$(DAKOTA_MATH_LIBS) $(F90_LIB_PATH) $(F90_LIBS) \
$(LIBS) 

override CPPFLAGS := $(CPPFLAGS)
