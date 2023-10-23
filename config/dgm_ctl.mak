ROOT = dgm_ctl

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

override ALL := $(ROOT) $(ALL) $(REO_ALL) $(EXTRAS)

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

override CPPFLAGS := $(CPPFLAGS) $(INCS)
override LIBS := $(LIBS)
override PROG := $(PROG)

OBJS = $(foreach module, $(ALL) $(SPECIAL), $(module).o)
SRCS = $(foreach module, $(ALL) $(SPECIAL), $(module).cpp)

.SUFFIXES: .cpp .c .d

$(PROG): $(OBJS) Parser.tab.cpp lex.yy.cpp
	$(LD) $(LDFLAGS) -o $(PROG).tmp $(OBJS) $(LIBS)
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
	$(LEX) -olex.yy.cpp Parser.l 

.cpp.o:
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $<

.c.o:
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $<

#  Automatically make dependencies
include $(INCDIR)/dep.mak

.PHONY: clean
clean :
	rm -r $(OBJS)
