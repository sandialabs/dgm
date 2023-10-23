#==============================================================================
#   Title:     DGM Utilities Makefile
#
#   Author:    Curtis Ober        ccober@sandia.gov
#              Scott Collis       sscoll@sandia.gov
#
#   Copyright: (C)2012 Sandia National Laboratories
#==============================================================================

# Use .ARCH to help determine build architecture
# Set default architecture.
ARCH = GCC

# Override the uname value with a local ARCHitecture file
LARCH = $(shell if [ -e ../.ARCH ] ; then echo 1; else echo 0 ; fi)
ifeq ($(LARCH),1)
  ARCH = $(shell cat ../.ARCH)
endif

# ==============================================================================
# If you have netcdf, atlas and boost installed in $DGM_TPL and 
# $TRILINOS_HOME is defined, then you should not need to change
# things in this section.
#
# You likely have exodus installed in one of two ways: a separate
# installation of exodus, or exodus installed with Trilinos.
# We assume use have installed exodus with Trilinos for the default.
# 
# Default settings
ifdef DGM_TPL
TPL = $(DGM_TPL)
else
TPL = $(HOME)/local
endif

ifdef TRILINOS_HOME
TRILINOS_TPL = $(TRILINOS_HOME)
EXODUS_HOME = $(TRILINOS_HOME)/serial/opt
EXODUS = exodus
else
TRILINOS_TPL = $(TPL)/trilinos
EXODUS_HOME = $(TPL)/exodusii
EXODUS = exoIIv2c
endif

refine2D_TPL_INCLUDE_DIRS = -I$(TPL)/boost/include
refine2D_TPL_LIBRARY_DIRS = -L$(TPL)/boost/lib
refine2D_TPL_LIBRARIES    = -lboost_mpi -lboost_program_options -lboost_serialization

hex_mesh_TPL_INCLUDE_DIRS = -I$(TPL)/boost/include
hex_mesh_TPL_LIBRARY_DIRS = -L$(TPL)/boost/lib
hex_mesh_TPL_LIBRARIES    = -lboost_program_options

# If the libraries are in another location, then set them explicitly below.
#TPL = $(HOME)/local
#EXODUS_HOME = $(HOME)/local/exodus              # Separate exodus installation
#EXODUS_HOME = $(HOME)/local/trilinos/serial/opt # Installed with Trilinos
# ==============================================================================

# Libs for individual executables
EXO2IEN_INCDIR = -I../src -I$(TPL)/atlas/include -I$(TPL)/netcdf/serial/opt/include -I$(TPL)/boost/include -I$(EXODUS_HOME)/include
EXO2IEN_LIBDIR = -L$(EXODUS_HOME)/lib -L$(TPL)/atlas/lib -L$(TPL)/netcdf/serial/opt/lib -L$(TPL)/hdf5/serial/opt/lib -l$(EXODUS) -lnetcdf -lhdf5 -lhdf5_hl
EXO2IEN_LIBS = -lcurl -lz -lm

include $(TRILINOS_TPL)/mpi/opt/include/Makefile.export.Zoltan
Zoltan2_TPL_INCLUDE_DIRS = -I$(TPL)/atlas/include -I$(TPL)/netcdf/mpi/opt/include -I$(TPL)/boost/include
Zoltan2_TPL_LIBRARY_DIRS = -L$(TPL)/atlas/lib -L$(TPL)/netcdf/mpi/opt/lib -L$(TPL)/hdf5/mpi/opt/lib -L$(TPL)/boost/lib 
Zoltan2_TPL_LIBRARIES = -lboost_mpi -lblas

#
# OS specific settings
#
ifeq ($(ARCH),Linux)                    # Linux
  CXX = g++
  CC  = gcc
  FC  = g77
  MPICXX = mpicxx
  MPICC  = mpicc
  ifdef SEMS_ATLAS_INCLUDE_PATH
   EXO2IEN_INCDIR = -I../src -I$(SEMS_ATLAS_INCLUDE_PATH) -I$(SEMS_NETCDF_INCLUDE_PATH) -I$(BOOST_INC) -I$(EXODUS_HOME)/include
   EXO2IEN_LIBDIR = -L$(EXODUS_HOME)/lib -L$(SEMS_ATLAS_LIBRARY_PATH) -L$(SEMS_NETCDF_LIBRARY_PATH) -L$(SEMS_HDF5_LIBRARY_PATH) -l$(EXODUS) -lnetcdf -lhdf5 -lhdf5_hl
   EXO2IEN_LIBS = -lcurl -lz -lm /projects/sems/install/rhel7-x86_64/sems/tpl/netcdf/4.7.3/gcc/7.3.0/openmpi/1.10.1/parallel/lib/libpnetcdf.a
  endif
endif

ifeq ($(ARCH),Linux-x86_64)             # Linux-x86_64
  CXX = g++
  CC  = gcc
  FC  = g77
  MPICXX = mpicxx
  MPICC  = mpicc
endif

ifeq ($(ARCH),GCC)                      # Generic GCC compiler
  CXX = g++
  CC  = gcc
  FC  = g77
  MPICXX = mpicxx
  MPICC  = mpicc
endif

ifeq ($(ARCH),CLANG)                   # Generic CLANG compiler
  CXX = clang++
  CC  = clang
  MPICXX = mpicxx
  MPICC  = mpicc
  OSVER = $(shell uname -r)
  # Check for version of MacOS >= 16 which is SIERRA
  MAJOR_OSVER = $(firstword $(subst ., ,$(OSVER)))
  ifeq ($(shell test $(MAJOR_OSVER) -ge 16; echo $$?),0)
  SDKROOT = /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk
  else
  SDKROOT =
  endif
  # Use the native BLAS and LAPACK with CMC interface
  MATHINC  = $(SDKROOT)/System/Library/Frameworks/Accelerate.framework/Versions/Current/Frameworks/vecLib.framework/Headers
  MATHLIB = -framework Accelerate
  EXO2IEN_INCDIR = -I../src -I$(MATHINC) -I$(TPL)/netcdf/serial/opt/include -I$(TPL)/boost/include -I$(EXODUS_HOME)/include
  EXO2IEN_LIBDIR = -L$(EXODUS_HOME)/lib $(MATHLIB) -L$(TPL)/netcdf/serial/opt/lib -L$(TPL)/hdf5/serial/opt/lib -l$(EXODUS) -lnetcdf -lhdf5 -lhdf5_hl
  EXO2IEN_LIBS = -lcurl -lz -lm
endif

ifeq ($(ARCH),ICC)                      # Intel CC compiler
  CXX = icpc
  CC  = icc
  FC  = ifort 
  MPICXX = mpicxx
  MPICC  = mpicc
endif

ifeq ($(ARCH),Linux64)                  # Intel CC compiler on IA64
  CXX = g++
  CC  = gcc
  FC  = g77
  MPICXX = mpicxx
  MPICC  = mpicc
endif

ifeq ($(ARCH),Darwin)                   # GCC compiler on Apple Darwin
  CXX = g++ 
  CC  = gcc 
  FC  = g77
  MPICXX = mpicxx
  MPICC  = mpicc
endif

ifeq ($(ARCH),Darwin-x86_64)            # GCC compiler on Apple Darwin x86-64
  CXX = g++ 
  CC  = gcc 
  FC  = g77
  MPICXX = mpicxx
  MPICC  = mpicc
endif

ifeq ($(ARCH),TLCC)                     # TLCC MPP 
  CXX = icpc
  CC  = icc
  FC  = ifort 
  MPICXX = mpicxx
  MPICC  = mpicc
endif

ifeq ($(ARCH),TLCC2)                     # TLCC2 MPP 
  CXX = icpc
  CC  = icc
  FC  = ifort 
  MPICXX = mpicxx
  MPICC  = mpicc
endif

ifeq ($(ARCH),CRAY)                     # Cray XT system
  CXX = CC 
  CC  = cc
  FC  = ftn 
  MPICXX = CC 
  MPICC = cc
  ifeq ($(SYSTEM),curie) 
    # Local system
    EXO2IEN_INCDIR = -I../src -I$(TPL)/atlas/include -I$(TPL)/boost/include -I$(EXODUS_HOME)/include -I/opt/cray/netcdf-hdf5parallel/4.3.3.1/GNU/49/include
    EXO2IEN_LIBDIR = -L/opt/cray/netcdf-hdf5parallel/4.3.3.1/GNU/49/lib -L$(EXODUS_HOME)/lib -L$(TPL)/atlas/lib -l$(EXODUS) -lnetcdf -L/opt/cray/netcdf-hdf5parallel/4.3.3.1/GNU/49/lib -lhdf5 -lhdf5_hl -l hdf5_parallel -ldl
  else ifeq ($(SYSTEM),muzia) 
    # Local system
    EXO2IEN_INCDIR = -I../src -I$(TPL)/atlas/include -I$(TPL)/boost/include -I$(EXODUS_HOME)/include -I/opt/cray/netcdf/default/cray/83/include
    EXO2IEN_LIBDIR = -L/opt/cray/netcdf/default/cray/31/lib -L$(EXODUS_HOME)/lib -L$(TPL)/atlas/lib -l$(EXODUS) -lnetcdf -lhdf5 -lhdf5_hl
  else
    # Generic system
    EXO2IEN_INCDIR = -I../src -I$(TPL)/atlas/include -I$(TPL)/boost/include -I$(EXODUS_HOME)/include 
    EXO2IEN_LIBDIR = -L$(EXODUS_HOME)/lib -L$(TPL)/atlas/lib -l$(EXODUS) -lnetcdf -lhdf5 -lhdf5_hl -lhdf5_parallel -ldl
  endif
  EXO2IEN_LIBS = -lz -lm
  Zoltan2_TPL_LIBRARIES = -lboost_mpi
endif

ifeq ($(ARCH),CrayXC)                     # Cray XC system
  CXX = CC
  CC  = cc
  FC  = ftn
  MPICXX = CC
  MPICC = cc
  EXO2IEN_INCDIR = -I../src -I$(TPL)/atlas/include -I$(TPL)/boost/include -I$(EXODUS_HOME)/include
  EXO2IEN_LIBDIR = -L$(EXODUS_HOME)/lib -L$(TPL)/atlas/lib -l$(EXODUS) -lnetcdf -lhdf5 -lhdf5_hl -lhdf5_parallel -ldl
  EXO2IEN_LIBS = -lz -lm
  Zoltan2_TPL_LIBRARIES = -lboost_mpi
endif

ifdef TRILINOS_HOME
all: exo2ien zoltan2

# exo2ien converts standard finite element mesh files to DGM format
exo2ien: exo2ien.cpp ../src/Vector.hpp ../src/Matrix.hpp ../src/Types.hpp
	@echo '----------------------------------------------------'
	@echo 'Building exo2ien with Trilinos and ARCH = '$(ARCH)
	@echo '----------------------------------------------------'
	$(CXX) -std=c++11 -O2 exo2ien.cpp -DGCC4 $(EXO2IEN_INCDIR) $(EXO2IEN_LIBDIR) $(EXO2IEN_LIBS) -o exo2ien

zoltan2: zoltan2.cpp 
	@echo '----------------------------------------------------'
	@echo 'Building zoltan2 with Trilinos and ARCH = '$(ARCH)
	@echo '----------------------------------------------------'
	$(MPICXX) -std=c++11 -O2 zoltan2.cpp -I ../src ../src/CaseInsensitiveString.cpp -DGCC4 $(Zoltan2_TPL_INCLUDE_DIRS) $(Zoltan_INCLUDE_DIRS) $(Zoltan_LIBRARY_DIRS) $(Zoltan_LIBRARIES) $(Zoltan2_TPL_LIBRARY_DIRS) $(Zoltan2_TPL_LIBRARIES) -o zoltan2

else
# exo2ien converts standard finite element mesh files to DGM format
exo2ien: exo2ien.cpp ../src/Vector.hpp ../src/Matrix.hpp ../src/Types.hpp
	@echo '----------------------------------------------------'
	@echo 'Building exo2ien with Exodus and ARCH = '$(ARCH)
	@echo '----------------------------------------------------'
	$(CXX) exo2ien.cpp -DGCC4 $(EXO2IEN_INCDIR) $(EXO2IEN_LIBDIR) $(EXO2IEN_LIBS) -o exo2ien
endif

# refine2D does hanging node refinement on quad meshes 
refine2D: refine2D.cpp 
	@echo '----------------------------------------------------'
	@echo 'Building refine2D with ARCH = '$(ARCH)
	@echo '----------------------------------------------------'
	$(MPICXX) -std=c++11 -O3 $(refine2D_TPL_INCLUDE_DIRS) refine2D.cpp $(refine2D_TPL_LIBRARY_DIRS) $(refine2D_TPL_LIBRARIES) -o refine2D 

# refine3D does hanging node refinement on quad meshes 
refine3D: refine3D.cpp 
	@echo '----------------------------------------------------'
	@echo 'Building refine3D with ARCH = '$(ARCH)
	@echo '----------------------------------------------------'
	$(MPICXX) -std=c++11 -O3 $(refine2D_TPL_INCLUDE_DIRS) refine3D.cpp $(refine2D_TPL_LIBRARY_DIRS) $(refine2D_TPL_LIBRARIES) -o refine3D 

# hex_mesh  does 3d meshing 
hex_mesh: hex_mesh.cpp 
	@echo '----------------------------------------------------'
	@echo 'Building hex_mesh with ARCH = '$(ARCH)
	@echo '----------------------------------------------------'
	$(CXX) -std=c++11 -O3 $(hex_mesh_TPL_INCLUDE_DIRS) hex_mesh.cpp $(hex_mesh_TPL_LIBRARY_DIRS) $(hex_mesh_TPL_LIBRARIES) -o hex_mesh 

docs:
	doxygen exo2ien.cfg

clean:
	rm -f exo2ien zoltan2 refine2D
