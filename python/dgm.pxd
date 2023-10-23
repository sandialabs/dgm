###############################################################################
#
#  Cython declarations for the DGM library
#
#  Author:       S. Scott Collis, sscoll@sandia.gov
#  Modified by:  William F. Spotz, wfspotz@sandia.gov
#
#  Copyright:    (c)2011 Sandia National Laboratories
#
###############################################################################

# Configuration
include "config.pxi"

# System imports
from libcpp cimport bool

# MPI imports
IF DGM_PARALLEL == 1:
  from mpi4py.mpi_c cimport MPI_Comm

###############################################################################
cdef extern from "Comm.hpp" namespace 'DGM':
  cdef int DGM_SUCCESS "DGM::SUCCESS"
  cdef int DGM_FAILURE "DGM::FAILURE"
  cdef cppclass DGM_Comm "DGM::Comm":
    DGM_Comm()

cdef class Comm:
  cdef DGM_Comm *baseptr
  cdef bool Master(self)

###############################################################################
cdef extern from "SerialComm.hpp" namespace 'DGM':
  cdef cppclass DGM_SerialComm "DGM::SerialComm":
    DGM_SerialComm()
    int MyPID()

cdef class SerialComm(Comm):
  cdef DGM_SerialComm *thisptr

###############################################################################
IF DGM_PARALLEL == 1:
  cdef extern from "MpiComm.hpp" namespace 'DGM':
    cdef cppclass DGM_MpiComm "DGM::MpiComm":
      DGM_MpiComm(MPI_Comm &)
      int MyPID()

  cdef class MpiComm(Comm):
    cdef DGM_MpiComm *thisptr

###############################################################################
cdef extern from "Table.hpp" namespace 'DGM':
  cdef cppclass DGM_Table "DGM::Table":
    DGM_Table()
    int size()

cdef class Table:
  cdef DGM_Table *thisptr

###############################################################################
cdef extern from "ArgList.hpp" namespace 'DGM':
  cdef cppclass DGM_ArgList "DGM::ArgList":
    DGM_ArgList( int *argc, char ***argv )
    int size()

cdef class ArgList:
  cdef DGM_ArgList *thisptr

###############################################################################
cdef extern from "Control.hpp" namespace 'DGM':
  cdef cppclass DGM_Control "DGM::Control":
    int num_ctrl()
    int size()
    void zero()
    double * get_phi_ptr()
    void bound()
    double norm()
    double cost()
    double inner_product(DGM_Control *)
    int read(char *, int)
    int write(char *, int)
    DGM_Control * clone()

  void axpy(double a, DGM_Control *, DGM_Control *)
  void scale(double a, DGM_Control *)
  void copy(DGM_Control *, DGM_Control *)
  void fill(double a, DGM_Control *)

cdef class Control:
  cdef DGM_Control *thisptr
