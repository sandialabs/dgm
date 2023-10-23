#==============================================================================
#   Title:     DGM TDD Makefile
#
#   Author:    Scott Collis
#              sscoll@sandia.gov
#
#   Copyright: (C)2011 Sandia National Laboratories
#==============================================================================
ROOT = dgm_tdd

ifdef DGM_PARALLEL
  PROG = p$(ROOT).exe
else
  PROG = $(ROOT).exe
endif
#
# DGM objects
#
include $(INCDIR)/dgm.inc
#
# Reo objects
#
include $(INCDIR)/reo.inc
#
# TDD objects
#
TDD = CTOCPdgm

override ALL := $(ROOT) $(ALL) $(REO_ALL) $(TDD) $(EXTRAS)

# Include TDD specific defines
override CPPFLAGS :=  $(CPPFLAGS) \
-DTDD_NO_OBJECTIVE_UPDATE_POINT
#-DTDD_UNIT_DELTA_U_BAR

# Parser generator
#LEX = flex -I
#YACC = bison -d

# set the compile flags
ifeq ($(LTYPE),g)	# turn on debug flag 
CXXFLAGS := $(DEBUG) $(CCWOFF)
CFLAGS := $(DEBUG) $(CWOFF)
FFLAGS := $(DEBUGF) $(FWOFF)
LDFLAGS	:= $(DEBUGLD)
else			# Maximal optimization flags
ifeq ($(LTYPE),mopt)
CXXFLAGS := $(MOPTXX) $(CCWOFF)
CFLAGS := $(MOPT) $(CWOFF)
FFLAGS := $(MOPTF) $(FWOFF)
LDFLAGS	:= $(MOPTLD)
else			# Regular optimization flags
ifeq ($(LTYPE),opt)
CXXFLAGS := $(OPTXX) $(CCWOFF)
CFLAGS := $(OPT) $(CWOFF)
FFLAGS := $(OPTF) $(FWOFF)
LDFLAGS	:= $(OPTLD)
endif
endif
endif

override CPPFLAGS := $(CPPFLAGS) $(INCS)
override LIBS := $(LIBS)
override PROG := $(PROG)

OBJS = $(foreach module, $(ALL) $(SPECIAL), $(module).o)
SRCS = $(foreach module, $(ALL) $(SPECIAL), $(module).cpp)

.SUFFIXES: .cpp .d

$(PROG): $(OBJS)
	$(LD) $(LDFLAGS) -o $(PROG).tmp $(OBJS) $(LIBS)
	mv $(PROG).tmp ./$(PROG)

include $(SRCS:.cpp=.d)

Parser.tab.cpp Parser.tab.hpp: Parser.y Parser.hpp
	$(YACC) $< 
	mv Parser.tab.c Parser.tab.cpp
	mv Parser.tab.h Parser.tab.hpp

lex.yy.cpp: Parser.l Parser.tab.hpp
	$(LEX) $< 
	mv lex.yy.c lex.yy.cpp

.cpp.o:
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< 

.c.o:
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $<

#  Automatically make dependencies
include $(INCDIR)/dep.mak

.PHONY: clean
clean :
	rm -r $(OBJS)
