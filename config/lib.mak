#==============================================================================
#   Title:     DGM library Makefile
#
#   Author:    Scott Collis
#              sscoll@sandia.gov
#
#   Copyright: (C)2010 Sandia National Laboratories
#==============================================================================
ifdef DGM_PARALLEL
  TARGET = libpdgm
  REO = libpreo
else
  TARGET = libdgm
  REO = libreo
endif
#
# DGM objects
#
include $(INCDIR)/dgm.inc
#
# Reo objects
#
include $(INCDIR)/reo.inc

ifdef DGM_PARALLEL
override ALL := $(ALL) $(ALL_PEOPT) $(EXTRAS)
else
override ALL := $(ALL) $(EXTRAS)
endif

# set the compile flags
ifeq ($(LTYPE),g)	# turn on debug flag 
CXXFLAGS := $(DEBUG) $(CCWOFF)
CFLAGS := $(DEBUG) $(CWOFF)
FFLAGS := $(DEBUGF) $(FWOFF)
LDFLAGS	:= $(DEBUGLD)
else			# Maximal optimization flags
ifeq ($(LTYPE),mopt)
CXXFLAGS := $(MOPTXX) $(CCWOFF)
CFLAGS := $(MOPT)
FFLAGS := $(MOPTF)
LDFLAGS	:= $(MOPTLD)
else			# Regular optimization flags
ifeq ($(LTYPE),opt)
CXXFLAGS := $(OPTXX) $(CCWOFF)
CFLAGS := $(OPT)
FFLAGS := $(OPTF)
LDFLAGS	:= $(OPTLD)
endif
endif
endif
#
# Setup the installation destination
#
OPT_TYPE=$(LTYPE)
ifdef DGM_DEST
  DEST = $(DGM_DEST)
else
  ifndef DGM_HOME
    DGM_HOME=$(HOME)/local/dgm
  endif
  ifdef DGM_PARALLEL
  BUILD_TYPE = mpi
  else
  BUILD_TYPE = serial
  endif
  ifeq ($(LTYPE),g)
    OPT_TYPE = debug
  else
  ifeq ($(LTYPE),mopt)
    OPT_TYPE = mopt
  else
  ifeq ($(LTYPE),opt)
    OPT_TYPE = opt
  endif
  endif
  endif
  ifdef TRILINOS
    DEST = $(DGM_HOME)/trilinos/$(BUILD_TYPE)/$(OPT_TYPE)
  else
    DEST = $(DGM_HOME)/$(BUILD_TYPE)/$(OPT_TYPE)
  endif
endif

ifndef PEOPT_HOME
  override CPPFLAGS := $(CPPFLAGS) $(INCS)
else
  override CPPFLAGS := $(CPPFLAGS) $(INCS) -I$(PEOPT_HOME)/include
endif
override LIBS := $(LIBS)
override TARGET := $(TARGET)

OBJS = $(foreach module, $(ALL) $(SPECIAL), $(module).o)
SRCS = $(foreach module, $(ALL) $(SPECIAL), $(module).cpp)
FSRCS = $(foreach module, $(FALL) $(SPECIAL), $(module).f90)
GOBJS = $(foreach module, $(GALL) $(SPECIAL), $(module).o)
GSRCS = $(foreach module, $(GALL) $(SPECIAL), $(module).cu)

REO_SRCS = $(foreach module, $(REO_ALL) $(SPECIAL), $(module).cpp)
REO_OBJS = $(foreach module, $(REO_ALL) $(SPECIAL), $(module).o)

.SUFFIXES: .cpp .c .f90 .d .cu

ifdef DGM_SHARED
  lib: $(TARGET).a $(TARGET).$(SO) $(REO).a $(REO).$(SO)
else
  lib: $(TARGET).a
endif

$(TARGET).a: $(OBJS) $(GOBJS) Parser.tab.cpp lex.yy.cpp
	$(AR) $(ARFLAGS) $(TARGET).a $(OBJS) $(GOBJS)
	ranlib $(TARGET).a

$(TARGET).$(SO): $(OBJS) $(GOBJS) Parser.tab.cpp lex.yy.cpp
ifdef INSTALL_NAME
	$(LD) $(SHARED) $(INSTALL_NAME) $(DEST)/lib/$(TARGET).$(SO) \
$(OBJS) $(GOBJS) $(LIBS) -o $(TARGET).$(SO)
else
	$(LD) $(SHARED) $(OBJS) $(GOBJS) $(LIBS) -o $(TARGET).$(SO)
endif

$(REO).a: $(REO_OBJS) $(OBJS)
	$(AR) $(ARFLAGS) $(REO).a $(REO_OBJS)
	ranlib $(REO).a

$(REO).$(SO): $(TARGET).$(SO) $(REO_OBJS)
ifdef INSTALL_NAME
	$(LD) $(SHARED) $(INSTALL_NAME) $(DEST)/lib/$(REO).$(SO) \
$(REO_OBJS) $(LIBS) $(TARGET).$(SO) -o $(REO).$(SO)
else
	$(LD) $(SHARED) $(REO_OBJS) $(LIBS) $(TARGET).$(SO) -o $(REO).$(SO)
endif

include $(SRCS:.cpp=.d)
include $(REO_SRCS:.cpp=.d)

install : lib 
	@echo Installing DGM library to $(DEST)
	mkdir -p $(DEST)
	mkdir -p $(DEST)/lib
	mkdir -p $(DEST)/include
	rsync -t $(SRCDIR)/*.hpp $(SRCDIR)/*.h $(SRCDIR)/*.tpp $(DEST)/include
	cd $(DEST)
	ln -sfn . $(DEST)/include/DGM
	cd $(BUILD)
	rsync -t *.a $(DEST)/lib
ifdef DGM_SHARED
	rsync -t *.so $(DEST)/lib
	rsync -t $(SRCDIR)/../python/dgm.pxd $(DEST)/include
else
  # Makes sure to remove any stale shared libs
	rm -f $(DEST)/lib/*dgm.so $(DEST)/lib/*reo.so
endif
ifdef USE_JSON
	mkdir -p $(DEST)/include/json
	rsync -t ../json/include/json/* $(DEST)/include/json
endif

Parser.tab.cpp : Parser.tab.hpp

Parser.tab.hpp : Parser.y Parser.hpp
	$(YACC) $< 
ifndef USE_YACC
ifdef USE_NEW_BISON
	mv Parser.tab.c Parser.tab.cpp
	mv Parser.tab.h Parser.tab.hpp
else
	mv Parser.tab.c Parser.tab.cpp
	mv Parser.tab.h Parser.tab.hpp
endif
else
	mv y.tab.c Parser.tab.cpp
	mv y.tab.h Parser.tab.hpp
endif

lex.yy.cpp: Parser.l Parser.tab.hpp
	$(LEX) -o lex.yy.cpp $< 

.cu.o:
	nvcc -O3 -arch sm_35 -std=c++11 --expt-extended-lambda $(CPPFLAGS) -c $< 

.cpp.o:
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< 

.c.o:
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< 

.f90.o:
	$(FC) -c $< 

# Automatically make dependencies
include $(INCDIR)/dep.mak

.PHONY: clean
clean :
	rm -r $(OBJS) $(GOBJS)
