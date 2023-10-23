#==============================================================================
#   Title:     DGM Flip Makefile
#
#   Author:    Scott Collis
#              sscoll@sandia.gov
#
#   Copyright: (C)2011 Sandia National Laboratories
#==============================================================================
ROOT = dgm_flip

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