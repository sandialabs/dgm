#==============================================================================
#   Title:     DGM Makefile
#
#   Author:    Scott Collis
#              sscoll@sandia.gov
#
#   Copyright: (C)2010 Sandia National Laboratories
#==============================================================================
ROOT = dgm

ifdef DGM_PARALLEL
  PROG = p$(ROOT).exe
else
  PROG = $(ROOT).exe
endif
#
# Setup the installation destination
#
ifdef DGM_DEST
  DEST = $(DGM_DEST)
else
  ifndef DGM_HOME
    DGM_HOME=$(HOME)/local/dgm
  endif
  ifdef DGM_PARALLEL
  BUILD_TYPE = mpi
  else
  BUILD_TYPE = serial
  endif
  ifeq ($(LTYPE),g)
    OPT_TYPE = debug
  else
  ifeq ($(LTYPE),mopt)
    OPT_TYPE = mopt
  else
  ifeq ($(LTYPE),opt)
    OPT_TYPE = opt
  endif
  endif
  endif
  ifdef TRILINOS
    DEST = $(DGM_HOME)/trilinos/$(BUILD_TYPE)/$(OPT_TYPE)
  else
    DEST = $(DGM_HOME)/$(BUILD_TYPE)/$(OPT_TYPE)
  endif
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

include $(INCDIR)/common.mak

fastinstall : 
	@echo Performing Fast DGM Install to $(DEST)
	mkdir -p $(DEST)/bin
	mkdir -p $(DEST)/python
	if test -e dgm_mesh.exe; then \
rsync -t dgm_mesh.exe $(DEST)/bin; fi
	if test -e dgm_n2e.exe; then \
rsync -t dgm_n2e.exe $(DEST)/bin; fi
	rsync -lt ../util/dgm2tec ../util/dgm2dat ../util/dgm_clean \
../util/dgm_test ../util/ctl2tec ../util/ctl2aux ../util/dgm2p3d \
../util/ncpus ../util/reo_* ../util/dgm2aux ../util/dgm2par \
../util/dgm_head ../util/dgm_clean_all ../util/ndiff.py $(DEST)/bin
	if test -e $(DEST)/bin/dgm.exe; then \
ln -sf $(DEST)/bin/dgm.exe $(DEST)/bin/reo.exe; fi
	if test -e $(DEST)/bin/dgm_post.exe; then \
ln -sf $(DEST)/bin/dgm_post.exe $(DEST)/bin/reo_post.exe; fi
	if test -e $(DEST)/bin/dgm_cpost.exe; then \
ln -sf $(DEST)/bin/dgm_cpost.exe $(DEST)/bin/reo_cpost.exe; fi
	if test -e $(DEST)/bin/dgm_diff.exe; then \
ln -sf $(DEST)/bin/dgm_diff.exe $(DEST)/bin/reo_diff.exe; fi
	rsync -lt ../regression/jenkins/runtests.py ../util/bc.py \
../util/refine.py ../util/select_layers.py ../regression/dgm_test_support.py \
../util/ndiff.py ../util/d2f.py $(DEST)/python
	if test -e ../util/refine2D; then \
rsync -lt ../util/refine2D $(DEST)/bin; fi
	if test -e ../util/exo2ien; then \
rsync -lt ../util/exo2ien $(DEST)/bin; fi
	if test -e ../util/zoltan2; then \
rsync -lt ../util/zoltan2 $(DEST)/bin; fi

install : $(PROG) 
	@echo Installing DGM executable to $(DEST)
	mkdir -p $(DEST)/bin
	mkdir -p $(DEST)/python
	rsync -t *.exe $(DEST)/bin
	rsync -lt ../util/dgm2tec ../util/dgm2dat ../util/dgm_clean \
../util/dgm_test ../util/ctl2tec ../util/ctl2aux ../util/dgm2p3d \
../util/ncpus ../util/reo_* ../util/dgm2aux ../util/dgm2par \
../util/dgm_head ../util/dgm_clean_all ../util/ndiff.py $(DEST)/bin
	if test -e $(DEST)/bin/dgm.exe; then \
ln -sf $(DEST)/bin/dgm.exe $(DEST)/bin/reo.exe; fi
	if test -e $(DEST)/bin/dgm_post.exe; then \
ln -sf $(DEST)/bin/dgm_post.exe $(DEST)/bin/reo_post.exe; fi
	if test -e $(DEST)/bin/dgm_cpost.exe; then \
ln -sf $(DEST)/bin/dgm_cpost.exe $(DEST)/bin/reo_cpost.exe; fi
	if test -e $(DEST)/bin/dgm_diff.exe; then \
ln -sf $(DEST)/bin/dgm_diff.exe $(DEST)/bin/reo_diff.exe; fi
	rsync -lt ../regression/jenkins/runtests.py ../util/bc.py \
../util/refine.py ../util/select_layers.py ../regression/dgm_test_support.py \
../util/ndiff.py ../util/d2f.py $(DEST)/python
	if test -e ../util/refine2D; then \
rsync -lt ../util/refine2D $(DEST)/bin; fi
	if test -e ../util/exo2ien; then \
rsync -lt ../util/exo2ien $(DEST)/bin; fi
	if test -e ../util/zoltan2; then \
rsync -lt ../util/zoltan2 $(DEST)/bin; fi
