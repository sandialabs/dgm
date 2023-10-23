#==============================================================================
#   Title:     DGM Objects
#
#   Author:    Scott Collis
#              sscoll@sandia.gov
#
#   Copyright: (C)2003-2012 Sandia National Laboratories
#==============================================================================
#
# DGM objects
#
ALL = Comm Domain Element Line Quad QuadBlock ElementBlock NodalQuad Boundary \
NodalLine Tri HexBlock Hex NodalTet Face Edge Basis Polylib Partition Field \
Mesh Slab Curve vField Utilities Search Response BndryStats Side TimeInt BC \
ArgList Parser.tab lex.yy Control State Adjoint Optimizer NonlinearCG \
SpectralFilter BlackBox Source ErrorEst Trilinos LineSearch NodalTri \
NodalHex SolverML Info ParUtils Vertex SpectralLine SpectralQuad SpectralHex \
MultiOptProblem CaseInsensitiveString FieldSlice Objective WeightsDatabase \
Topology Zoltan BaseQuad ROL_Optimizer BaseHex BaseLine Kernel NodalTriCub
#
# MPI Parallel
#
ifdef DGM_PARALLEL
override ALL := $(ALL) MpiComm MpiType
endif
#
# GPU 
#
ifdef USE_KOKKOS 
GALL = GpGpu
else ifdef USE_CUDA
GALL = GpGpu
else
GALL = 
endif
#
# List of DGM peopt objects
#
ifdef PEOPT_HOME
ALL_PEOPT = PEDgm
else
ALL_PEOPT = 
endif
#
# FDM objects
#
ifdef USE_FDM
override ALL := $(ALL) Epetra_MDMap Xpetra_EpetraMDMap Epetra_MDVector	\
 Xpetra_EpetraMDVector FDM_mpiType FDM_Mesh FDM_CartesianMesh FDM_Field	\
 FDM_VectorField FDM_Domain FDM_State FDM_Adjoint FDM_Ctrl FDM_Control	\
 FDM_Objective FDM_ObjFunc FDM_Source FDM_Kernel
endif
#
# JSON objects
#
ifdef USE_JSON
override ALL := $(ALL) json_value json_reader json_writer
endif
#
# Use CMC CLAPACK interface
#
ifdef USE_CMC_LAPACK
override ALL := $(ALL) clapack
endif
#
# Fortran objects
#
FALL =
