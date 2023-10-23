ROOT = dgm_err

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

.SUFFIXES: .cpp .d

$(PROG): $(OBJS) Parser.tab.cpp lex.yy.cpp
	$(LD) $(LDFLAGS) -o $(PROG).tmp $(OBJS) $(LIBS)
	mv $(PROG).tmp ./$(PROG)

include $(SRCS:.cpp=.d)

Parser.tab.cpp Parser.tab.hpp: Parser.y Parser.hpp
	$(YACC) Parser.y
	mv Parser.tab.c Parser.tab.cpp
	mv Parser.tab.h Parser.tab.hpp

lex.yy.cpp: Parser.l Parser.tab.hpp
	$(LEX) -olex.yy.cpp Parser.l
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
