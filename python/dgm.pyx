"""
Cython binding for DGM/Reo.

These bindings allow you to drive DGM/Reo from Python

Author:  S. Scott Collis, sscoll@sandia.gov

Copyright: (c)2011 Sandia National Laboratories
"""

from libc.stdlib     cimport *
from libcpp          cimport bool
from cython.operator cimport dereference as deref

# retrieve the configuration from the setup.py
include "config.pxi"

# Numerical Python
# I currently get a warning when I compile -- I think it is related to the
# PY_ARRAY_UNIQUE_SYMBOL issue
#import  numpy
#cimport numpy

# System imports
import os
import sys

# MPI imports
IF DGM_PARALLEL == 1:
  cimport mpi4py.MPI as MPI
  import  mpi4py.MPI as MPI
  #from mpi4py.mpi_c cimport MPI_Comm
  from mpi4py.mpi_c cimport *

# DGM import
cimport dgm

# ###############################################################################
# cdef extern from *:
#   cdef void print_debug_beg "#if defined(DEBUG) //" ()
#   cdef void print_debug_end "#endif //" ()

###############################################################################
cdef extern from "string.h":
  size_t strlen(char * s)
  void * memcpy(void * dest, void * src, size_t n)

# ###############################################################################
# cdef extern from "string" namespace "std":
#     cdef cppclass string:
#         char* c_str()

###############################################################################
cdef extern from "Python.h":
  object PyCObject_FromVoidPtr(void * cobj, void (*destr) (void *))
  object PyCObject_FromVoidPtrAndDesc(void * cobj, void * desc,
                                      void (*destr) (void *, void *))
  void * PyCObject_AsVoidPtr(object self)
  void * PyCObject_GetDesc(object self)
  object PyString_FromString(char * c_string)
  object PyString_FromStringAndSize(char * c_string, int length)

###############################################################################
cdef class Comm:
  """
  Abstract base class for DGM Communicators
  """

  # Clone
  def Clone(self):
    raise NotImplementedError, "Method Clone() not implemented in derived class"

  # Exit execution with an error status
  def exit(self, int code=DGM_SUCCESS):
    raise NotImplementedError, "Method exit() not implemented in derived class"

  # Exit execution with a message and error status
  def error(self, str msg, int code=DGM_SUCCESS):
    raise NotImplementedError, "Method error() not implemented in derived class"

  # Return true if you are the master process
  cdef bool Master(self):
    raise NotImplementedError, "Method Master() not implemented in derived class"

  # Blocking send
  #def Send(self, int tag, numpy.ndarray buf, int dest):
  #  raise NotImplementedError, "Method Send() not implemented in derived class"

  # Receive
  #def Receive(self, int tag, numpy.ndarray buf, int source):
  #  raise NotImplementedError, "Method Receive() not implemented in derived class"

  # Nonblocking send
  #def iSend(self, int tag, numpy.ndarray buf, int dest):
  #  raise NotImplementedError, "Method iSend() not implemented in derived class"

  # Nonblocking receive 
  #def iReceive(self, int tag, numpy.ndarray buf, int source):
  #  raise NotImplementedError, "Method iReceive() not implemented in derived class"

  # Wait for all active nonblocking communication
  def WaitAll(self):
    raise NotImplementedError, "Method WaitAll() not implemented in derived class"

  # Combined send and receive
  #def SendReceive(self, int stag, numpy.ndarray sbuf, int dest,
  #                int rtag, numpy.ndarray rbuf, int source):
  #  raise NotImplementedError, "Method SendReceive() not implemented in derived class"

  # Combined send and receive to the same buffer
  #def SendReceiveReplace(self, numpy.ndarray sbuf, int dest, int stag,
  #                       int source, int rtag):
  #  raise NotImplementedError, "Method SendReceiveReplace() not implemented in derived class"

  #def get(self):
  #  return PyCObject_FromVoidPtr(<void *>self.thisptr,NULL)

###############################################################################
cdef class SerialComm(Comm):
  def __cinit__(self):
    #self.thisptr = new DGM_SerialComm()
    self.thisptr = \
    <DGM_SerialComm *>PyCObject_AsVoidPtr(makeSerialCommWorld());
  def __dealloc__(self):
    pass
    #print "Destroying SerialComm"
    #del self.thisptr
  def MyPID(self):
    return self.thisptr.MyPID()
  def get(self):
    return PyCObject_FromVoidPtr(<void *>self.thisptr,NULL)

###############################################################################
IF DGM_PARALLEL == 1:
  cdef class MpiComm(Comm):
    def __cinit__(self, MPI.Comm comm):
      # grab out the native MPI_Comm
      cdef MPI_Comm mpi_comm = comm.ob_mpi
      # make DGM comm on this MPI comm
      self.thisptr = new DGM_MpiComm(mpi_comm)
      # make sure that DGM::Comm::World
      makeMpiCommWorld(comm)
    def __init__(self, MPI.Comm comm):
      pass
    def __dealloc__(self):
      pass
      #print "Destroying MpiComm"
      #del self.thisptr
    def MyPID(self):
      return self.thisptr.MyPID()
    def get(self):
      return PyCObject_FromVoidPtr(<void *>self.thisptr,NULL)

###############################################################################
cdef class Table:
  def __cinit__(self):
    self.thisptr = new DGM_Table()
  def __dealloc__(self):
    del self.thisptr
  def size(self):
    #print "Destroying Table"
    return self.thisptr.size()
  def get(self):
    return PyCObject_FromVoidPtr(<void *>self.thisptr,NULL)
  def set(self):
    pass
    # do something here...

###############################################################################
cdef class ArgList:
  def __cinit__(self, arg):
    cdef char **argv
    arg = ['dgm.exe'] + arg
    argv = <char **> malloc(len(arg)*sizeof(char *))
    for i, tstr in enumerate(arg):
      n = strlen(tstr)
      argv[i] = <char *> malloc((n+1)*sizeof(char))
      memcpy(argv[i],<char *>tstr,n)
      argv[i][n] = '\0'
    cdef int argc = len(arg)
    self.thisptr = new DGM_ArgList( &argc, &argv )
  def __dealloc__(self):
    #print "Destroying ArgList"
    del self.thisptr
  def size(self):
    return self.thisptr.size()
  def get(self):
    return PyCObject_FromVoidPtr(<void *>self.thisptr,NULL)

###############################################################################
cdef extern from "ReoProblem.hpp" namespace 'Reo':
  cpdef cppclass Reo_Problem "Reo::Problem":
    Reo_Problem(DGM_ArgList *, DGM_Table *, DGM_Comm *) except +
    Reo_Problem(DGM_ArgList &, DGM_Table &) except +
    int solve() except +

cdef class ReoProblem:
  cdef Reo_Problem *thisptr
  def __cinit__(self, ArgList args, Table table, Comm comm):
    self.thisptr = new Reo_Problem( deref(args.thisptr),
                                    deref(table.thisptr) )
  def __dealloc__(self):
    #print "Destroying ReoProblem"
    del self.thisptr
  def solve(self):
    return self.thisptr.solve()

###############################################################################
cdef class Control:
  def __cinit__(self,data):
    #print "Building Control with:"
    #print "  data = ", data
    if isinstance(data, Control):
      #print " data is a Control"
      #c = <Control?>data
      #print "c =", c
      #self.thisptr = c.thisptr;
      self.thisptr = \
      <DGM_Control*>PyCObject_AsVoidPtr(data.clone())
    else:
      self.thisptr = \
      <DGM_Control*>PyCObject_AsVoidPtr(data)
  def __dealloc__(self):
    pass
    #print "Destroying Control"
  def num_ctrl(self):
    return self.thisptr.num_ctrl()
  def size(self):
    return self.thisptr.size()
  def zero(self):
    self.thisptr.zero()
  def bound(self):
    self.thisptr.bound()
  def norm(self):
    return self.thisptr.norm()
  def cost(self):
    return self.thisptr.cost()
  def clone(self):
    return PyCObject_FromVoidPtr(self.thisptr.clone(),NULL)
  def get(self):
    return PyCObject_FromVoidPtr(self.thisptr,NULL)
  def inner_product(self, Control b):
    return self.thisptr.inner_product(b.thisptr)
  def axpy(self, double a, Control y):
    axpy(a, self.thisptr, y.thisptr)
  def scale(self, double a):
    scale(a,self.thisptr)
  def copy(self, Control out):
    copy(self.thisptr, out.thisptr)
  def fill(self, double a):
    fill(a,self.thisptr)
  def reset(self, ptr):
    self.thisptr = \
    <DGM_Control*>PyCObject_AsVoidPtr(ptr)

###############################################################################
#
# Interface to the DGM::State
#
cdef extern from "State.hpp" namespace 'DGM':
  cpdef cppclass DGM_State "DGM::State":
    DGM_State()
    void set_initial_condition()
    void save()
    void no_save()
    int get_iter()

###############################################################################
#
# Interface to DGM::Objective 
#
cdef extern from "Objective.hpp" namespace 'DGM':
  cpdef cppclass DGM_Objective "DGM::Objective":
    int num_obs()
    double cost()
    void reset()
    DGM_State *get_state()

cdef class Objective:
  cdef DGM_Objective *thisptr
  def __cinit__(self,ptr):
    #print "Constructing Objective"
    self.thisptr = <DGM_Objective*>PyCObject_AsVoidPtr(ptr)
  def num_obs(self):
    return self.thisptr.num_obs()
  def cost(self):
    return self.thisptr.cost()
  def reset(self):
    self.thisptr.reset()
  def get_state(self):
    return PyCObject_FromVoidPtr(self.thisptr.get_state(),NULL) 

###############################################################################
#
# Interface to the DGM::vField
#
cdef extern from "vField.hpp" namespace 'DGM':
  cpdef cppclass DGM_vField "DGM::vField":
    DGM_vField(DGM_vField *) except +
    int get_iter()
    void clone(DGM_vField &) except +
    int size()
    int qtot()
    int nmodes()
    int ndof()
    int sdof()
    int nsd()
    void zero()
    void forward_transform()
    void backward_transform()
    void fill_sides()
    void share_sides()
    void begin_share_sides()
    void end_shared_sides()

cdef class vField:
  cdef DGM_vField *thisptr
  def __cinit__(self):
    print "Constructing vField"

###############################################################################
cdef extern from "ReoOptProblem.hpp" namespace 'Reo':
  cpdef cppclass Reo_OptProblem "Reo::OptProblem":
    Reo_OptProblem(DGM_ArgList &, DGM_Table &) except +
    int solve() except +
    double computeState() except +
    void computeAdjoint() except +
    DGM_State *getState() except +
    DGM_Control *getControl() except +
    DGM_Control *getGradient() except +
    DGM_Objective *getObjective() except +

cdef class ReoOptProblem:
  cdef Reo_OptProblem *thisptr
  def __cinit__(self, ArgList args, Table table, Comm comm):
    self.thisptr = new Reo_OptProblem( deref(args.thisptr),
                                       deref(table.thisptr) )
  def __dealloc__(self):
    #print "Destroying ReoOptProblem"
    del self.thisptr
  def solve(self):
    return self.thisptr.solve()
  cpdef double computeState(self):
    return self.thisptr.computeState()
  def computeAdjoint(self):
    self.thisptr.computeAdjoint()
  def getState(self):
    return PyCObject_FromVoidPtr(self.thisptr.getState(),NULL)
  def getObjective(self):
    return PyCObject_FromVoidPtr(self.thisptr.getObjective(),NULL)
  def getControl(self):
    return PyCObject_FromVoidPtr(self.thisptr.getControl(),NULL)
  def getGradient(self):
    return PyCObject_FromVoidPtr(self.thisptr.getGradient(),NULL)

###############################################################################
cdef extern from "pydgm.cpp":
# void *dgm_makeCommWorld(int *argc, char ***argv)
  void *dgm_makeSerialCommWorld()
  IF DGM_PARALLEL==1:
    void *dgm_makeMpiCommWorld(MPI_Comm comm)

###############################################################################
#
# You would use this one if you want DGM to own MPI_Comm_World
#
#def makeCommWorld():
#  return PyCObject_FromVoidPtr(dgm_makeCommWorld(), NULL)

def makeSerialCommWorld():
  return PyCObject_FromVoidPtr(dgm_makeSerialCommWorld(), NULL)

IF DGM_PARALLEL==1:
  def makeMpiCommWorld(MPI.Comm comm):
    cdef MPI_Comm mpi_comm = comm.ob_mpi
    return PyCObject_FromVoidPtr(dgm_makeMpiCommWorld(mpi_comm), NULL)
