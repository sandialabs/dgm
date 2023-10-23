#==============================================================================
#   Title:     DGM Difference Makefile
#
#   Author:    Scott Collis
#              sscoll@sandia.gov
#
#   Copyright: (C)2011 Sandia National Laboratories
#==============================================================================

ROOT = dgm_cdiff

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

override ALL := $(ROOT) $(ALL) $(REO_ALL) $(ALL_OPT) $(ALL_PEOPT) $(EXTRAS)

include $(INCDIR)/common.mak

override CPPFLAGS := $(CPPFLAGS) $(INCS) -I $(PEOPT_HOME)/include
override LIBS := $(LIBS)
override PROG := $(PROG)

OBJS = $(foreach module, $(ALL) $(SPECIAL), $(module).o)                         
SRCS = $(foreach module, $(ALL) $(SPECIAL), $(module).cpp)                       

