#==============================================================================
#   Title:     DGM Common Makefile
#
#   Author:    Scott Collis
#              sscoll@sandia.gov
#
#   Copyright: (C)2011 Sandia National Laboratories
#==============================================================================

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

ifndef PEOPT_HOME
  override CPPFLAGS := $(CPPFLAGS) $(INCS)
else
  override CPPFLAGS := $(CPPFLAGS) $(INCS) -I$(PEOPT_HOME)/include
endif
override LIBS := $(LIBS)
override PROG := $(PROG)

OBJS = $(foreach module, $(ALL) $(SPECIAL), $(module).o)
SRCS = $(foreach module, $(ALL) $(SPECIAL), $(module).cpp)
FSRCS = $(foreach module, $(FALL) $(SPECIAL), $(module).f90)
GOBJS = $(foreach module, $(GALL) $(SPECIAL), $(module).o)

.SUFFIXES: .cpp .c .f90 .cu .d

$(PROG): $(OBJS) $(GOBJS) Parser.tab.cpp lex.yy.cpp
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
	$(LEX) -o lex.yy.cpp $< 

.cpp.o:
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< 

.c.o:
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< 

.cu.o:
	nvcc -O3 -arch sm_35 -std=c++11 $(CPPFLAGS) -c $< 

.f90.o:
	$(FC) -c $< 

#  Automatically make dependencies
include $(INCDIR)/dep.mak

.PHONY: clean
clean :
	rm -r $(OBJS) $(GOBJS)
