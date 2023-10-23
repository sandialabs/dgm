#==============================================================================
#   Title:     DGM Information Makefile
#
#   Author:    Scott Collis
#              sscoll@sandia.gov
#
#   Copyright: (C)2011 Sandia National Laboratories
#==============================================================================
#
# DGM objects
#
include $(INCDIR)/dgm.inc
#
# Filter out Info from the list of dependancies
#
override ALL := $(ALL) $(EXTRAS)
override ALL := $(filter-out Info Parser.tab lex.yy, $(ALL))
SRCS = $(foreach module, $(ALL), $(module).cpp)

.SUFFIXES: .cpp .c .f90 .d

Info.cpp: Info.ver.cpp $(SRCS) Parser.y Parser.hpp Parser.l revision
	@echo Setting build time and revision number in $@ 
	../util/add_revision.sh revision $(SRCDIR)/Info.ver.cpp Info.cpp

.PHONY: clean
clean :
	rm -r $(OBJS)
