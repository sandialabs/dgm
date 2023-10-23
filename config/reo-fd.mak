# -*- Makefile -*-
ROOT = reo-fd

ifdef DGM_PARALLEL
  ifeq ($(LTYPE),g)	# turn on debug flag 
    PROG = pd$(ROOT).exe
  else			# 
    PROG = p$(ROOT).exe
  endif
else
  ifeq ($(LTYPE),g)	# turn on debug flag 
    PROG = d$(ROOT).exe
  else			# 
    PROG = $(ROOT).exe
  endif
endif
#
# DGM objects
#
include $(INCDIR)/dgm.inc
#
# Reo objects
#
# set the list of all object files
override ALL := $(ROOT) $(ALL) AdvDiff2dFD ReoInfo

# Trilinos
ifdef TRILINOS
  include $(INCDIR)/Trilinos.inc
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

override CPPFLAGS := $(CPPFLAGS) $(INCS) 
override LIBS := $(LIBS)
override PROG := $(PROG)

OBJS = $(foreach module, $(ALL) $(SPECIAL), $(module).o)
GOBJS = $(foreach module, $(GALL) $(SPECIAL), $(module).o)
SRCS = $(foreach module, $(ALL) $(SPECIAL), $(module).cpp)
FSRCS = $(foreach module, $(FALL) $(SPECIAL), $(module).f90)

.SUFFIXES: .cpp .c .f90 .d

$(PROG): $(OBJS) $(GOBJS) $(DGMDEP)
	$(LD) $(LDFLAGS) -o $(PROG).tmp $(OBJS) $(GOBJS) $(LIBS)
	mv $(PROG).tmp ./$(PROG)

include $(SRCS:.cpp=.d)

install : $(PROG)
	@echo Installing Reo executable to $(DEST)
	@echo DGMDEP = $(DGMDEP)
	@echo DGM_PARALLEL = $(DGM_PARALLEL)
	if test -e $(DEST)/bin; then rm -rf $(DEST)/bin; fi
	mkdir -p $(DEST)/bin
	rsync -t *.exe $(DEST)/bin

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
	$(LEX) -olex.yy.cpp $< 

.cpp.o:
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< 

.c.o:
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< 

.f90.o:
	gfortran -c $< 

#  Automatically make dependencies
include $(INCDIR)/dep.mak

.PHONY: clean
clean :
	rm -r $(OBJS) $(GOBJS)
