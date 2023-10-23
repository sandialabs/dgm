#==============================================================================
#   Title:     DGM revision Makefile
#
#   Author:    Scott Collis
#              sscoll@sandia.gov
#
#   Copyright: (c)2014 Sandia National Laboratories
#==============================================================================
#
all:
	@echo Making revision file
	../util/mk_revision.sh $(SRCDIR) 
