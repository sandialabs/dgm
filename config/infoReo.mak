#==============================================================================
#   Title:     Reo Information Makefile
#
#   Author:    Scott Collis
#              sscoll@sandia.gov
#
#   Copyright: (C)2011 Sandia National Laboratories
#==============================================================================
#
# DGM & Reo objects
#
include $(INCDIR)/dgm.inc
include $(INCDIR)/reo.inc
#
# Filter out Info from the list of dependancies
#
override ALL := $(ALL) $(REO_ALL) $(EXTRAS)
override ALL := $(filter-out ReoInfo Info Parser.tab lex.yy, $(ALL))
SRCS = $(foreach module, $(ALL), $(module).cpp)

.SUFFIXES: .cpp .c .f90 .d

ReoInfo.cpp: ReoInfo.ver.cpp $(SRCS) Info.cpp Parser.y Parser.hpp \
	Parser.l revision
	@echo Setting build time and revision number in $@ 
	../util/add_revision.sh revision $(SRCDIR)/ReoInfo.cpp ReoInfo.cpp
#touch $(SRCDIR)/ReoInfo.cpp

.PHONY: clean
clean :
	rm -r $(OBJS)
