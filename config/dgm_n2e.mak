#==============================================================================
#   Title:     DGM Node-to-Edge Makefile
#
#   Author:    Scott Collis
#              sscoll@sandia.gov
#
#   Copyright: (C)2011 Sandia National Laboratories
#==============================================================================
ROOT = dgm_n2e

ifdef DGM_PARALLEL
  PROG = p$(ROOT).exe
else
  PROG = $(ROOT).exe
endif
#
# DGM objects
#
include $(INCDIR)/dgm.inc

override ALL := $(ROOT) $(ALL) $(EXTRAS)

include $(INCDIR)/common.mak