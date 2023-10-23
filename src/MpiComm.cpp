/** \file MpiComm.cpp
    \brief Covert standard types to MPI_Datatypes
    \author Bill Spotz and Scott Collis
*/

#ifdef DGM_PARALLEL

#include "MpiComm.hpp"
#include "MpiType.hpp"

namespace DGM {

int MpiComm::GatherAll(const iVector&MyVals, const Ordinal SendCount,
                       iVector&AllVals, const intVector&RevCount,
                       const intVector&Displs) const {
  return MPI_Allgatherv(MyVals.ptr(), SendCount, mpiType<iVector::value_type>(),
                        AllVals.ptr(), RevCount.ptr(), Displs.ptr(),
                       mpiType<iVector::value_type>(), mpi_comm);
}

int MpiComm::GatherAll(const dVector&MyVals, const Ordinal SendCount,
                       dVector&AllVals, const intVector&RevCount,
                       const intVector&Displs) const {
  return MPI_Allgatherv(MyVals.ptr(), SendCount, mpiType<dVector::value_type>(),
                        AllVals.ptr(), RevCount.ptr(), Displs.ptr(),
                       mpiType<dVector::value_type>(), mpi_comm);
}

namespace {
#ifdef DGM_MPICOMM_USE_PAIR 
  // If you use std::pair then the resulting use of offsetof requires
  // that you use C++11 whereas a struct is POD (Plain Old Data) and 
  // C++98 requires that offsetof only be used on POD
  typedef std::pair<unsigned long long,int> ULLong_int;
  typedef std::pair<unsigned int,      int> UInt_int;
  typedef std::pair<unsigned long,     int> ULong_int;
#else
  // So, to keep support for C++98 use simple (POD) structs
  struct ULLong_int {
    unsigned long long first;
    int second;
  };
  struct UInt_int {
    unsigned int first;
    int second;
  };
  struct ULong_int {
    unsigned long first;
    int second;
  };
#endif
  void ULLong_int_MinLoc(void *U, void *V, int *len, MPI_Datatype *dptr) {
    ULLong_int *u = static_cast<ULLong_int*>(U);
    ULLong_int *v = static_cast<ULLong_int*>(V);
    for (int i=0; i<*len; ++i, ++u, ++v) {
      if      (u->first <  v->first) v->second = u->second;
      else if (v->first == u->first) v->second = std::min(v->second, u->second);
      v->first = std::min(v->first, u->first); 
    }
  }
  void UInt_int_MinLoc(void *U, void *V, int *len, MPI_Datatype *dptr) {
    UInt_int *u = static_cast<UInt_int*>(U);
    UInt_int *v = static_cast<UInt_int*>(V);
    for (int i=0; i<*len; ++i, ++u, ++v) {
      if      (u->first <  v->first) v->second = u->second;
      else if (v->first == u->first) v->second = std::min(v->second, u->second);
      v->first = std::min(v->first, u->first); 
    }
  }
  void ULong_int_MinLoc(void *U, void *V, int *len, MPI_Datatype *dptr) {
    ULong_int *u = static_cast<ULong_int*>(U);
    ULong_int *v = static_cast<ULong_int*>(V);
    for (int i=0; i<*len; ++i, ++u, ++v) {
      if      (u->first <  v->first) v->second = u->second;
      else if (v->first == u->first) v->second = std::min(v->second, u->second);
      v->first = std::min(v->first, u->first); 
    }
  }
}

int MpiComm::MinLocAll(unsigned long long &GlobalMins) const {
  static MPI_Datatype Unsigned_Long_Long_And_Int;
  static MPI_Op       MIN_LOC;
  static bool struct_defined = false;
  if (!struct_defined) {
    const int offset0 = offsetof(ULLong_int, first);
    const int offset1 = offsetof(ULLong_int, second);
    const int count=2;
    int array_of_blocklengths      [2] = {1,1};
    MPI_Aint array_of_displacements[2] = {offset0, offset1};
    MPI_Datatype array_of_types    [2] = {MPI_UNSIGNED_LONG_LONG, MPI_INT};
    MPI_Type_create_struct(count, 
                           array_of_blocklengths, 
                           array_of_displacements, 
                           array_of_types, 
                           &Unsigned_Long_Long_And_Int);
    MPI_Type_commit(&Unsigned_Long_Long_And_Int);
    struct_defined = true;
    MPI_Op_create(ULLong_int_MinLoc, false, &MIN_LOC);
  }
#ifdef DGM_MPICOMM_USE_PAIR
  ULLong_int out(0,0), in(GlobalMins,MyPID());
#else
  ULLong_int out, in;
  out.first=0; out.second=0;
  in.first=GlobalMins; in.second=MyPID();
#endif
  MPI_Allreduce(&in, &out, 1,
                Unsigned_Long_Long_And_Int, MIN_LOC, mpi_comm );
  GlobalMins = out.first;
  return out.second;
}

int MpiComm::MinLocAll( unsigned int &GlobalMins) const { 
  static MPI_Datatype Unsigned_Int_And_Int;
  static MPI_Op       MIN_LOC;
  static bool struct_defined = false;
  if (!struct_defined) {
    const int offset0 = offsetof(UInt_int, first);
    const int offset1 = offsetof(UInt_int, second);
    const int count=2;
    int array_of_blocklengths      [2] = {1,1};
    MPI_Aint array_of_displacements[2] = {offset0, offset1};
    MPI_Datatype array_of_types    [2] = {MPI_UNSIGNED, MPI_INT};
    MPI_Type_create_struct(count, 
                           array_of_blocklengths, 
                           array_of_displacements, 
                           array_of_types, 
                           &Unsigned_Int_And_Int);
    MPI_Type_commit(&Unsigned_Int_And_Int);
    struct_defined = true;
    MPI_Op_create(UInt_int_MinLoc, false, &MIN_LOC);
  }
#ifdef DGM_MPICOMM_USE_PAIR
  UInt_int out(0,0), in(GlobalMins,MyPID());
#else
  UInt_int out, in;
  out.first=0; out.second=0;
  in.first=GlobalMins; in.second=MyPID();
#endif
  MPI_Allreduce(&in, &out, 1,
                Unsigned_Int_And_Int, MIN_LOC, mpi_comm );
  GlobalMins = out.first;
  return out.second;
}

int MpiComm::MinLocAll( unsigned long &GlobalMins) const {
  static MPI_Datatype Unsigned_Long_And_Int;
  static MPI_Op       MIN_LOC;
  static bool struct_defined = false;
  if (!struct_defined) {
    const int offset0 = offsetof(ULong_int, first);
    const int offset1 = offsetof(ULong_int, second);
    const int count=2;
    int array_of_blocklengths      [2] = {1,1};
    MPI_Aint array_of_displacements[2] = {offset0, offset1};
    MPI_Datatype array_of_types    [2] = {MPI_UNSIGNED_LONG, MPI_INT};
    MPI_Type_create_struct(count, 
                           array_of_blocklengths, 
                           array_of_displacements, 
                           array_of_types, 
                           &Unsigned_Long_And_Int);
    MPI_Type_commit(&Unsigned_Long_And_Int);
    struct_defined = true;
    MPI_Op_create(ULong_int_MinLoc, false, &MIN_LOC);
  }
#ifdef DGM_MPICOMM_USE_PAIR
  ULong_int out(0,0), in(GlobalMins,MyPID());
#else
  ULong_int out, in;
  out.first=0; out.second=0;
  in.first=GlobalMins; in.second=MyPID();
#endif
  MPI_Allreduce(&in, &out, 1,
                Unsigned_Long_And_Int, MIN_LOC, mpi_comm );
  GlobalMins = out.first;
  return out.second;
}

void MpiComm::CommFree() {
  if (mpi_comm != MPI_COMM_WORLD && 
      mpi_comm != MPI_COMM_SELF && 
      mpi_comm != MPI_COMM_NULL)
     MPI_Comm_free(&mpi_comm);
}

} // namespace DGM

#endif  // DGM_PARALLEL
