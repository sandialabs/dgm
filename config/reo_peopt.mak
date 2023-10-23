#==============================================================================
#   Title:     Reo-peopt Optimization Makefile
#
#   Author:    Scott Collis
#              sscoll@sandia.gov
#              Joseph Young
#              josyoun@sandia.gov
#
#   Copyright: (C)2012 Sandia National Laboratories
#==============================================================================
ROOT = reo
SUFFIX = _peopt

ifndef USE_JSON
  $(error peopt requires json)
endif

ifdef DGM_PARALLEL
  ifeq ($(LTYPE),g)	# turn on debug flag 
    PROG = pd$(ROOT)_peopt.exe
  else
    PROG = p$(ROOT)_peopt.exe
  endif
else
  ifeq ($(LTYPE),g)	# turn on debug flag 
    PROG = d$(ROOT)_peopt.exe
  else
    PROG = $(ROOT)_peopt.exe
  endif
endif
#
# DGM objects
#
include $(INCDIR)/dgm.inc
#
# Reo objects
#
include $(INCDIR)/reo.inc

override ALL := $(ROOT)$(SUFFIX) $(ALL) $(REO_ALL) $(ALL_OPT) \
$(ALL_PEOPT) $(EXTRAS)

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

override CPPFLAGS := $(CPPFLAGS) $(INCS) -I $(PEOPT_HOME)/include
override LIBS := $(LIBS)
override PROG := $(PROG)

OBJS = $(foreach module, $(ALL) $(SPECIAL), $(module).o)
SRCS = $(foreach module, $(ALL) $(SPECIAL), $(module).cpp)
GOBJS = $(foreach module, $(GALL) $(SPECIAL), $(module).o)

.SUFFIXES: .cpp .c .f90 .d

$(PROG): $(OBJS) $(GOBJS) $(DGMDEP)
	$(LD) $(LDFLAGS) -o $(PROG).tmp $(OBJS) $(GOBJS) $(LIBS)
	mv $(PROG).tmp ./$(PROG)

include $(SRCS:.cpp=.d)

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

#  Automatically make dependencies
include $(INCDIR)/dep.mak

.PHONY: clean
clean :
	rm -r $(OBJS) $(GOBJS)
