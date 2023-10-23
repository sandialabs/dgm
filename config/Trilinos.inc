# -*- Makefile -*-
# 
# Makefile include for linking DGM with Trilinos
#
# S. Scott Collis
# Sandia National Laboratories
# 
# Thu Oct 29 09:52:14 MDT 2009
#
ifdef TRILINOS
  TRILINOS_HOME = $(TRILINOS)
else
  TRILINOS_HOME = /usr/local/trilinos
endif
#
# Make sure that Trilinos is on
#
TRILINOS=1
#
# If Trilinos is enabled, always use Epetra and Teuchos::Comm
#
DEFINES += DGM_USE_TRILINOS DGM_USE_EPETRA DGM_USE_TEUCHOS_COMM \
DGM_USE_GENERAL_GHOSTING
#
# Set Trilinos includes path
#
TRILINOS_INCL = -I$(TRILINOS_HOME)/include
#
# Determine if Rythmos is needed
#
ifneq (,$(findstring DGM_USE_RYTHMOS,$(DEFINES)))
  USE_RYTHMOS = 1
endif
#
# Determine if STK is needed
#
ifneq (,$(findstring DGM_USE_STK_SEARCH,$(DEFINES)))
  USE_STK_SEARCH = 1
endif
#
# Attempt to get all Trilinos libraries
#
include $(TRILINOS_HOME)/include/Makefile.export.Trilinos
TRILINOS_LIB = -L$(TRILINOS_HOME)/lib $(Trilinos_LIBRARIES) \
$(Trilinos_TPL_LIBRARIES)
#
# Set includes and libs for Trilinos
#
TRIINC := $(TRILINOS_INCL)
override CPPFLAGS := $(CPPFLAGS)
TRILIB := $(TRILINOS_LIB)
