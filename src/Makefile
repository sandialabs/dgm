#==============================================================================
#   Title:     DGM Main Makefile
#
#   Author:    Scott Collis
#              sscoll@sandia.gov
#
#   Copyright: (C)2012 Sandia National Laboratories
#==============================================================================

# Sense the architecture from the system
ARCH = $(shell uname)-$(shell uname -p)

# Override the uname value with a local ARCHitecture file
LARCH = $(shell if [ -e ARCH ] ; then echo 1; else echo 0 ; fi)
ifeq ($(LARCH),1)
  ARCH = $(shell cat ARCH)
endif

# Get the build path
BUILD = $(shell pwd)

# Sense the version of the operating system
OSVER = $(shell uname -r)

# Check to see which version of Bison you are using
BISON = $(wordlist 4,4,$(shell bison --version ))
ifeq ($(firstword $(subst ., ,$(BISON))),1)
ifeq ($(wordlist 2,2,$(subst ., ,$(BISON))),28)
else
USE_NEW_BISON := 1
endif
else
USE_NEW_BISON := 1
endif

# Turn on the use of Boost filesystem
USE_BOOST_FS := 1

# Turn on the use of Hwloc hardware locality
# USE_HWLOC := 1

# Turn on the JSON parser
USE_JSON := 1

# Set all paths to be in src right now (may want to change in the future)
VPATH    = ../src:../json/src
SRCDIR   = ../src
LIBDIR   = ../src
HDRDIR   = ../src
INCDIR   = ../config

# Default defines are set in src/Config.hpp or set on the compile line
DEFINES =
#
# Determine whether to use the boost::filesystem
#
ifdef USE_BOOST_FS
  DEFINES += DGM_USE_BOOST_FS
endif
#
# Determine whether to use the JSON parser
#
ifdef USE_JSON
  DEFINES += DGM_USE_JSON
endif
#
# Determine whether to use the hwloc library
#
ifdef ADDONS
  ifneq ($(findstring USE_HWLOC,$(ADDONS)),)
    USE_HWLOC = 1
  endif
endif
ifdef USE_HWLOC
  DEFINES += DGM_USE_HWLOC
endif
#
# Determine whether to use the BLOSC compressor
#
ifdef USE_BLOSC
  DEFINES += DGM_USE_BLOSC DGM_VERBOSE_COMPRESSION
endif
#
# If using OpenBLAS use CMC_CLAPACK interface to LAPACK
#
ifdef USE_OPENBLAS
  USE_CMC_LAPACK = 1
endif
#
# Determine whether to use internal CMC CLAPACK interface
#
ifdef USE_CMC_LAPACK
  DEFINES += CMC_USE_INTERNAL_CLAPACK
endif
#
# Determine whether to use OpenBLAS LAPACKE interface 
#
ifdef USE_LAPACKE
  DEFINES += CMC_USE_LAPACKE
endif
#
# Determine whether to use Teuchos LAPACK interface
#
ifdef USE_TEUCHOS_LAPACK
  DEFINES += CMC_USE_TEUCHOS_LAPACK
endif
#
# Determine whether to build with CUDA enabled
#
ifdef ADDONS
  ifneq ($(findstring USE_CUDA,$(ADDONS)),)
    USE_CUDA = 1
  endif
endif
#
# Determine whether to build with GTEST enabled
#
ifdef ADDONS
  ifneq ($(findstring USE_GTEST,$(ADDONS)),)
    USE_GTEST = 1
  endif
endif
#
# Determine whether to use ROL and FDM if Trilinos is enabled
#
ifdef TRILINOS
  DEFINES += DGM_USE_ROL
  USE_FDM = 1
  DEFINES += DGM_USE_FDM
  ifdef ADDONS
    ifneq ($(findstring KOKKOS,$(ADDONS)),)
      USE_KOKKOS = 1
    endif
  endif
endif
#
# Determine whether to use ITL
#
ifdef USE_ITL
  DEFINES += DGM_USE_ITL
endif
#
# Determine whether to use FFTW
# NOTE:  if you use FFTW make sure that you are using a commerically 
# licensed version (Cray LibSci or Intel MKL) or else you may be linking
# to GPL software!
#
ifdef USE_FFTW
  DEFINES += DGM_USE_FFTW
endif
#
# Initialized CPPFLAGS to null
#
CPPFLAGS =
#
# Parser generator
#
YY = dgm_yy
LEX = flex -I -P$(YY)
ifdef USE_YACC
  YACC = yacc -d -p$(YY)
else
  YACC = bison -d -p$(YY)
endif
#
# OS specific settings
#
ifeq ($(ARCH),Linux)                    # Linux
include $(INCDIR)/Linux.inc
endif

ifeq ($(ARCH),Ubuntu)                   # Ubuntu Linux (Docker container)
include $(INCDIR)/Ubuntu.inc
endif

ifeq ($(ARCH),Linux-x86_64)             # Linux-x86_64
include $(INCDIR)/Linux.inc
endif

ifeq ($(ARCH),Linux-i686)               # Linux with Intel processor
include $(INCDIR)/Linux-i686.inc
endif

ifeq ($(ARCH),Linux-ppc64le)            # Linux on IBM Power8
include $(INCDIR)/Linux-ppc64le.inc
endif

ifeq ($(ARCH),GCC)                      # Generic GCC compiler
include $(INCDIR)/GCC.inc
endif

ifeq ($(ARCH),PGI)                      # PGI CC compiler
include $(INCDIR)/PGI.inc
endif

ifeq ($(ARCH),ICC)                      # Intel CC compiler
include $(INCDIR)/ICC.inc
endif

ifeq ($(ARCH),ICC-p4)                   # Intel CC compiler with MPICH-p4
include $(INCDIR)/ICC-p4.inc
endif

ifeq ($(ARCH),ICC64)                    # Intel CC compiler on IA64
include $(INCDIR)/ICC64.inc
endif

ifeq ($(ARCH),Linux64)                  # Intel CC compiler on IA64
include $(INCDIR)/Linux64.inc
endif

ifeq ($(ARCH),Darwin)                   # GCC compiler on Apple Darwin
include $(INCDIR)/Darwin.inc
endif

ifeq ($(ARCH),Darwin-x86)               # GCC compiler on Apple Darwin x86
include $(INCDIR)/Darwin-x86.inc
endif

ifeq ($(ARCH),Darwin-i386)              # GCC compiler on Apple Darwin x86
include $(INCDIR)/Darwin-i386.inc
endif

ifeq ($(ARCH),Darwin-x86_64)            # GCC compiler on Apple Darwin x86-64
include $(INCDIR)/Darwin-x86_64.inc
endif

ifeq ($(ARCH),Darwin-powerpc)           # GCC compiler on Apple Darwin
include $(INCDIR)/Darwin.inc
endif

ifeq ($(ARCH),MacOSX)                   # CLANG compiler on Apple Darwin
include $(INCDIR)/MacOSX.inc
endif

ifeq ($(ARCH),CLANG)                    # CLANG compiler on Apple Darwin
include $(INCDIR)/CLANG.inc
endif

ifeq ($(ARCH),Darwin-GCC)               # GCC compiler on Apple Darwin
include $(INCDIR)/Darwin-GCC.inc
endif

ifeq ($(ARCH),Darwin-GCC-SEMS)          # SEMS GCC compiler on Apple Darwin
include $(INCDIR)/Darwin-GCC-SEMS.inc
endif

ifeq ($(ARCH),TLCC)                     # TLCC MPP
include $(INCDIR)/TLCC.inc
endif

ifeq ($(ARCH),TLCC2)                    # TLCC-2 MPP
include $(INCDIR)/TLCC2.inc
endif

ifeq ($(ARCH),CTS1)                     # CTS-1 MPP
include $(INCDIR)/CTS1.inc
endif

ifeq ($(ARCH),ARM)                      # ARM Astra
include $(INCDIR)/ARM.inc
endif

ifeq ($(ARCH),CRAY)                     # Cray XT using Cray C++
include $(INCDIR)/CRAY.inc
endif

ifeq ($(ARCH),CrayCuda)                 # Cray XT using Cray with Cuda
include $(INCDIR)/CrayCuda.inc
endif

ifeq ($(ARCH),CrayGCC)                  # Cray XT using GCC
include $(INCDIR)/CrayGCC.inc
endif

ifeq ($(ARCH),CrayPGI)                  # Cray XT using PGI
include $(INCDIR)/CrayPGI.inc
endif

ifeq ($(ARCH),CrayXC)                   # Cray XC
include $(INCDIR)/CrayXC.inc
endif

override DEFINES := $(DEFINES) $(ADDONS)
DEF := $(foreach def, $(DEFINES), -D$(def))
override CPPFLAGS := $(DEF) $(CPPFLAGS)

# make variables available for next make
export

OBJS = $(foreach module, $(ALL) $(SPECIAL), $(module).o)

help:
	@echo ''
	@echo ' DGM Makefiles:'
	@echo ''
	@echo ' Run make with one of the following options:'
	@echo ' dgm........dgm optimized solver'
	@echo ' pdgm.......dgm parallel optimized solver'
	@echo ' mdgm.......dgm maximally optimized solver'
	@echo ' pmdgm......dgm parallel maximally optimized solver'
	@echo ' ddgm.......dgm debug solver'
	@echo ' mesh.......simple mesh generator'
	@echo ' n2e........pre processor'
	@echo ' post.......post processor'
	@echo ' stats......statistics post processor'
	@echo ' clean......remove all objects'
	@echo ' distclean..remove all objects + flex files'
	@echo ' docs.......make Doxygen documentation'
	@echo ' opt........DGM with optimal control'
	@echo ' popt.......parallel DGM with optimal control'
	@echo ' dopt.......debug DGM with optimal control'
	@echo ' tdd........time-domain decomposition'
	@echo ' cpost......post processor for control output'
	@echo ' diff.......norm of the difference of two rst files'
	@echo ' all........make all dgm serial codes'
	@echo ' pall.......make all dgm parallel codes'
	@echo ''
	@echo ' ARCH = '$(ARCH)', OSVER = '$(OSVER)', BISON = '$(BISON)
#	@echo ' USE_NEW_BISON = '$(USE_NEW_BISON)
info:
	@echo Writing DGM defines to file dgm.def
	@echo $(DEFINES) > dgm.def
	$(MAKE) -f $(INCDIR)/rev.mak
	$(MAKE) -f $(INCDIR)/info.mak
reo: info
	$(MAKE) -f $(INCDIR)/infoReo.mak
	$(MAKE) LTYPE=opt -f $(INCDIR)/reo.mak
dgm: info
	$(MAKE) -f $(INCDIR)/infoReo.mak
	$(MAKE) LTYPE=opt -f $(INCDIR)/dgm.mak
pdgm:
	$(MAKE) dgm DGM_PARALLEL=1
pddgm:
	$(MAKE) ddgm DGM_PARALLEL=1
mdgm: info
	$(MAKE) -f $(INCDIR)/infoReo.mak
	$(MAKE) LTYPE=mopt -f $(INCDIR)/dgm.mak
pmdgm:
	$(MAKE) mdgm DGM_PARALLEL=1
ddgm: info
	$(MAKE) -f $(INCDIR)/infoReo.mak
	$(MAKE) LTYPE=g -f $(INCDIR)/dgm.mak
lib: info
	$(MAKE) LTYPE=opt -f $(INCDIR)/lib.mak
plib:
	$(MAKE) lib DGM_PARALLEL=1
pmlib:
	$(MAKE) mlib DGM_PARALLEL=1
pdlib:
	$(MAKE) dlib DGM_PARALLEL=1
dlib: info
	$(MAKE) LTYPE=g -f $(INCDIR)/lib.mak
mlib: info
	$(MAKE) LTYPE=mopt -f $(INCDIR)/lib.mak
shared:
	$(MAKE) lib DGM_SHARED=1
mesh: info
	$(MAKE) LTYPE=opt -f $(INCDIR)/dgm_mesh.mak
dmesh: info
	$(MAKE) LTYPE=g -f $(INCDIR)/dgm_mesh.mak
mmesh: info
	$(MAKE) LTYPE=mopt -f $(INCDIR)/dgm_mesh.mak
post: info
	$(MAKE) LTYPE=opt -f $(INCDIR)/dgm_post.mak
ppost:
	$(MAKE) post DGM_PARALLEL=1
pdpost:
	$(MAKE) dpost DGM_PARALLEL=1
dpost: info
	$(MAKE) LTYPE=g -f $(INCDIR)/dgm_post.mak
mpost: info
	$(MAKE) LTYPE=mopt -f $(INCDIR)/dgm_post.mak
mppost:
	$(MAKE) mpost DGM_PARALLEL=1
n2e: info
	$(MAKE) LTYPE=opt -f $(INCDIR)/dgm_n2e.mak
dn2e: info
	$(MAKE) LTYPE=g -f $(INCDIR)/dgm_n2e.mak
loc: info
	$(MAKE) LTYPE=opt -f $(INCDIR)/dgm_loc.mak
mloc: info
	$(MAKE) LTYPE=mopt -f $(INCDIR)/dgm_loc.mak
dloc: info
	$(MAKE) LTYPE=g -f $(INCDIR)/dgm_loc.mak
opt: info
	$(MAKE) LTYPE=opt -f $(INCDIR)/dgm_opt.mak
mopt: info
	$(MAKE) LTYPE=mopt -f $(INCDIR)/dgm_opt.mak
popt:
	$(MAKE) opt DGM_PARALLEL=1
pmopt:
	$(MAKE) mopt DGM_PARALLEL=1
pdopt:
	$(MAKE) dopt DGM_PARALLEL=1
dopt: info
	$(MAKE) LTYPE=g -f $(INCDIR)/dgm_opt.mak
lfd:
ifdef USE_FDM
	$(MAKE) -f $(INCDIR)/reo-fd.mak
endif
fd: info
	$(MAKE) LTYPE=opt lfd
mfd: info
	$(MAKE) LTYPE=mopt lfd
dfd: info
	$(MAKE) LTYPE=g lfd
pfd:
	$(MAKE) fd DGM_PARALLEL=1
pmfd:
	$(MAKE) mfd DGM_PARALLEL=1
pdfd:
	$(MAKE) dfd DGM_PARALLEL=1
ctl: info
	$(MAKE) LTYPE=opt -f $(INCDIR)/dgm_ctl.mak
pctl:
	$(MAKE) ctl DGM_PARALLEL=1
dctl: info
	$(MAKE) LTYPE=g -f $(INCDIR)/dgm_ctl.mak
tdd: info
	$(MAKE) LTYPE=opt -f $(INCDIR)/dgm_tdd.mak
dtdd: info
	$(MAKE) LTYPE=g -f $(INCDIR)/dgm_tdd.mak
ptdd:
	$(MAKE) tdd DGM_PARALLEL=1
tddtest: info
	$(MAKE) LTYPE=opt -f $(INCDIR)/dgm_tdd_test.mak
dtddtest: info
	$(MAKE) LTYPE=g -f $(INCDIR)/dgm_tdd_test.mak
ptddtest:
	$(MAKE) tddtest DGM_PARALLEL=1
me: info
	$(MAKE) LTYPE=opt -f $(INCDIR)/dgm_me.mak
dme: info
	$(MAKE) LTYPE=g -f $(INCDIR)/dgm_me.mak
pme:
	$(MAKE) me DGM_PARALLEL=1
stats: info
	$(MAKE) LTYPE=opt -f $(INCDIR)/dgm_stats.mak
dstats: info
	$(MAKE) LTYPE=g -f $(INCDIR)/dgm_stats.mak
cpost: info
	$(MAKE) LTYPE=opt -f $(INCDIR)/dgm_cpost.mak
mcpost: info
	$(MAKE) LTYPE=mopt -f $(INCDIR)/dgm_cpost.mak
dcpost: info
	$(MAKE) LTYPE=g -f $(INCDIR)/dgm_cpost.mak
pcpost:
	$(MAKE) cpost DGM_PARALLE=1
pdcpost:
	$(MAKE) dcpost DGM_PARALLEL=1
err: info
	$(MAKE) LTYPE=opt -f $(INCDIR)/dgm_err.mak
derr: info
	$(MAKE) LTYPE=g -f $(INCDIR)/dgm_err.mak
perr:
	$(MAKE) err DGM_PARALLEL=1
docs:
	doxygen $(INCDIR)/dgm.dox
user:
	doxygen user.dox
dak: info
	$(MAKE) LTYPE=opt -f $(INCDIR)/dgm_dak.mak
ddak: info
	$(MAKE) LTYPE=g -f $(INCDIR)/dgm_dak.mak
pdak:
	$(MAKE) dak DGM_PARALLEL=1
trikota: info
	$(MAKE) LTYPE=opt -f $(INCDIR)/dgm_trikota.mak
dtrikota: info
	$(MAKE) LTYPE=g -f $(INCDIR)/dgm_trikota.mak
ptrikota: info
	$(MAKE) trikota DGM_PARALLEL=1
moocho: info
	$(MAKE) LTYPE=opt -f $(INCDIR)/dgm_moocho.mak
dmoocho: info
	$(MAKE) LTYPE=g -f $(INCDIR)/dgm_moocho.mak
pmoocho:
	$(MAKE) moocho DGM_PARALLEL=1
diff: info
	$(MAKE) LTYPE=opt -f $(INCDIR)/dgm_diff.mak
mdiff: info
	$(MAKE) LTYPE=mopt -f $(INCDIR)/dgm_diff.mak
ddiff: info
	$(MAKE) LTYPE=g -f $(INCDIR)/dgm_diff.mak
pdiff:
	$(MAKE) diff DGM_PARALLEL=1
pmdiff:
	$(MAKE) mdiff DGM_PARALLEL=1
pddiff:
	$(MAKE) ddiff DGM_PARALLEL=1
cdiff: info
	$(MAKE) LTYPE=opt -f $(INCDIR)/dgm_cdiff.mak
dcdiff: info
	$(MAKE) LTYPE=g -f $(INCDIR)/dgm_cdiff.mak
pcdiff:
	$(MAKE) cdiff DGM_PARALLEL=1
pdcdiff:
	$(MAKE) dcdiff DGM_PARALLEL=1
flip: info
	$(MAKE) LTYPE=opt -f $(INCDIR)/dgm_flip.mak
dflip: info
	$(MAKE) LTYPE=g -f $(INCDIR)/dgm_flip.mak
pflip:
	$(MAKE) flip DGM_PARALLEL=1
peopt: info
ifdef DGM_PARALLEL
ifdef PEOPT_HOME
	$(MAKE) LTYPE=opt lpeopt
else
	@echo Must define PEOPT_HOME to build reo_peopt
endif
else
	@echo reo_peopt requires DGM_PARALLEL=1
endif
lpeopt: info
	$(MAKE) -f $(INCDIR)/reo_peopt.mak
ppeopt:
	$(MAKE) peopt DGM_PARALLEL=1
dpeopt:
ifdef DGM_PARALLEL
ifdef PEOPT_HOME
	$(MAKE) LTYPE=g lpeopt
else
	@echo Must define PEOPT_HOME to build reo_peopt
endif
else
	@echo reo_peopt requires DGM_PARALLEL=1
endif
pdpeopt:
	$(MAKE) dpeopt DGM_PARALLEL=1
fastall: lib
	$(MAKE) n2e
	$(MAKE) mesh
dfastall: dlib
	$(MAKE) dn2e
	$(MAKE) dmesh
pfastall: plib
pdfastall: pdlib
all: lib
	$(MAKE) dgm
	$(MAKE) opt
	$(MAKE) fd
	$(MAKE) stats
	$(MAKE) mesh
	$(MAKE) post
	$(MAKE) n2e
	$(MAKE) loc
	$(MAKE) cpost
	$(MAKE) diff
	$(MAKE) flip
mall: mlib
	$(MAKE) mdgm
	$(MAKE) mopt
	$(MAKE) mfd
	$(MAKE) mmesh
	$(MAKE) mpost
	$(MAKE) mloc
	$(MAKE) mcpost
	$(MAKE) mdiff
pmall: pmlib
	$(MAKE) pmdgm
	$(MAKE) pmopt
	$(MAKE) pmfd
	$(MAKE) ppost
	$(MAKE) pmdiff
dall: dlib
	$(MAKE) ddgm
	$(MAKE) dopt
	$(MAKE) dfd
	$(MAKE) dstats
	$(MAKE) dmesh
	$(MAKE) dpost
	$(MAKE) dn2e
	$(MAKE) dloc
	$(MAKE) dcpost
	$(MAKE) dflip
pall: plib
	$(MAKE) pdgm
	$(MAKE) popt
	$(MAKE) pfd
	$(MAKE) ppost
	$(MAKE) pdiff
ifdef PEOPT_HOME
	$(MAKE) ppeopt
	$(MAKE) pcdiff
endif
pdall: pdlib
	$(MAKE) pddgm
	$(MAKE) pdopt
	$(MAKE) pdfd
	$(MAKE) pdpost
	$(MAKE) pddiff
ifdef PEOPT_HOME
	$(MAKE) pdpeopt
	$(MAKE) pdcdiff
endif
fastinst:
	$(MAKE) install -f $(INCDIR)/lib.mak
	$(MAKE) fastinstall -f $(INCDIR)/dgm.mak
inst:
	$(MAKE) install -f $(INCDIR)/lib.mak
	$(MAKE) install -f $(INCDIR)/dgm.mak
instlib:
	$(MAKE) install -f $(INCDIR)/lib.mak
clean:
	@echo Cleaning the build directory
	rm -rf *.o *.d *.exe *.a *.$(SO)
	rm -rf lex.yy.cpp Parser.tab.[ch]pp Info.cpp revision
distclean:
	$(MAKE) clean
	@echo Making the distribution src directory clean
	rm -rf $(SRCDIR)/lex.yy.cpp $(SRCDIR)/Parser.tab.[ch]pp
fastinstall : fastall
	$(MAKE) LTYPE=opt fastinst
install : all
	$(MAKE) LTYPE=opt inst
minstall : mall
	$(MAKE) LTYPE=mopt inst
dfastinstall : dfastall
	$(MAKE) LTYPE=g fastinst
dinstall : dall
	$(MAKE) LTYPE=g inst
pfastinstall : pfastall
	$(MAKE) LTYPE=opt DGM_PARALLEL=1 fastinst
pinstall : pall
	$(MAKE) LTYPE=opt DGM_PARALLEL=1 inst
pminstall : pmall
	$(MAKE) LTYPE=mopt DGM_PARALLEL=1 inst
pdfastinstall : pdfastall
	$(MAKE) LTYPE=g DGM_PARALLEL=1 fastinst
pdinstall : pdall
	$(MAKE) LTYPE=g DGM_PARALLEL=1 inst
installlib : lib
	$(MAKE) LTYPE=opt instlib
dinstalllib : lib
	$(MAKE) LTYPE=g instlib
pinstalllib : plib
	$(MAKE) LTYPE=opt DGM_PARALLEL=1 instlib
pdinstalllib : plib
	$(MAKE) LTYPE=g DGM_PARALLEL=1 instlib
