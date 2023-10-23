#ifndef DGM_MPICOMM_HPP
#define DGM_MPICOMM_HPP

/** \file MpiComm.hpp
    \brief MPI implementation of the DGM communicator
    \author Scott Collis
*/

// MPI includes
#include "mpi.h"
#ifndef OPEN_MPI
#include "mpio.h"
#endif

// system includes
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <csignal>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <sys/wait.h>
#include <utility>
#include <vector>

// Trilinos includes
#ifdef DGM_USE_TEUCHOS_COMM
#include "Teuchos_RCP.hpp"
#include "Teuchos_DefaultMpiComm.hpp"
#endif

// boost includes
#include "boost/lexical_cast.hpp"
#include "boost/numeric/conversion/cast.hpp"

#ifdef DGM_USE_BOOST_FS
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#endif

// DGM includes
#include "Comm.hpp"
#include "Info.hpp"

#ifdef DGM_DOXYGEN
/// Print out detailed MPI comm information
#define DGM_MPICOMM_VERBOSE
/// Define if the system call is not supported
#define DGM_NO_SYSTEM
#endif

namespace DGM {

  /// Template function for converting standard data types to MPI_Datatype. */
  template< class T > MPI_Datatype mpiType();

  /// DGM MPI parallel communicator class
  class MpiComm : public Comm {

    static int NumWorld;   ///< Number of World communicators

    mutable std::vector<MPI_Request> requests;  ///< vector of active requests

  protected:

    int pid;                  ///< Process id
    int numproc;              ///< Number of processors in the Comm

#ifdef DGM_USE_TEUCHOS_COMM
    /// Equivalent Teuchos communicator
    Teuchos::RCP< const Teuchos::Comm< int > > teuchosComm;
#endif

  public:

    MPI_Comm mpi_comm;        ///< MPI communicator for this Comm

    // Constructors
    inline explicit MpiComm(int *argc, char ***argv);
    inline explicit MpiComm(const MPI_Comm &, const std::string & = "",
                            std::ostream & = std::cout,
                            std::ostream & = std::cerr,
                            const bool no_stratch=true);
    inline MpiComm(const MpiComm &);
    inline Comm * Clone() const { return new MpiComm(*this); }

    // Destructor
    inline virtual ~MpiComm();

    /// \name DGM::Comm Interface
    //@{
    inline void exit(const int code=DGM::FAILURE) const;
    inline void abort(const int code=DGM::FAILURE) const;
    inline void error(const std::string &msg, int code=DGM::FAILURE) const;
    inline void warning(const std::string &msg) const;

    inline bool Master() const { return (pid==master) ? true : false; }

    inline void Send(int tag, double *buf, int len, int dest) const;
    inline void Receive(int tag, double *buf, int len, int source) const;

    inline void Send(int tag, int *buf, int len, int dest) const;
    inline void Receive(int tag, int *buf, int len, int source) const;

    inline void iSend(int tag, double *buf, int len, int dest) const;
    inline void iReceive(int tag, double *buf, int len, int source) const;
    inline void iSend(int tag, int *buf, int len, int dest) const;
    inline void iSend(int tag, long *buf, int len, int dest) const;
    inline void iSend(int tag, unsigned *buf, int len, int dest) const;
    inline void iSend(int tag, long long *buf, int len, int dest) const;
    inline void iSend(int tag, long unsigned *buf, int len, int dest) const;
    inline void iReceive(int tag, int *buf, int len, int source) const;
    inline void iReceive(int tag, long *buf, int len, int source) const;
    inline void iReceive(int tag, unsigned *buf, int len, int source) const;
    inline void iReceive(int tag, long long *buf, int len, int source) const;
    inline void iReceive(int tag, long unsigned *buf, int len, int source) const;
    inline void WaitAll() const;

    inline void SendReceive(int stag, double *sbuf, int slen, int dest,
                            int rtag, double *rbuf, int rlen,
                            int source) const;
    inline void SendReceiveReplace(double *sbuf, int len, int dest,
                                   int stag, int source, int rtag) const;

    // setup scratch space for temporary out-of-core storage
    inline void CreateScratch() const;
    inline void RemoveScratch() const;

    // methods that mimic Epetra_Comm
    inline int MyPID() const { return pid; }
    inline int NumProc() const { return numproc; }

    inline void Barrier() const;

    inline int Gather(const unsigned  *sendbuf,
                      const int  sendcount,
                      unsigned  *recvbuf,
                      const int  recvcount,
                      const int  root=0) const ;

    inline int Gather(const int       *sendbuf,
                      const int  sendcount,
                      int       *recvbuf,
                      const int  recvcount,
                      const int  root=0) const ;

    inline int GatherV(DTK::Ordinal_t *sendbuf,
                       const size_t sendcount,
                       DTK::Ordinal_t *recvbuf,
                       int *recvcounts,
                       int *displs,
                       const int root=0) const ;

    inline int GatherV(unsigned *sendbuf,
                       const int sendcount,
                       unsigned *recvbuf,
                       int *recvcounts,
                       int *displs,
                       const int root=0) const ;

    inline int GatherV(int *sendbuf,
                       const int sendcount,
                       int *recvbuf,
                       int *recvcounts,
                       int *displs,
                       const int root=0) const ;

    inline int Scan( const int *MyVals, int *AllVals, int Count=1) const;
    inline int Scan( const unsigned long *MyVals, unsigned long *AllVals,
                     int Count=1) const;
    inline int Scan( const unsigned long long *MyVals,
                     unsigned long long *AllVals,
                     int Count=1) const;

    inline int Alltoall(const int *sendbuf, const int sendcount,
                        int *recvbuf, const int recvcount) const;

    inline int Alltoall(const unsigned long *sendbuf, const int sendcount,
                        unsigned long *recvbuf, const int recvcount) const;

    inline int Alltoallv(const double *sendbuf, const int *sendcount,
                         const int *senddisp, double *recvbuf,
                         const int *recvcount, const int *recvdisp) const;

    inline int Alltoallv(const float  *sendbuf, const int *sendcount,
                         const int *senddisp, float  *recvbuf,
                         const int *recvcount, const int *recvdisp) const;

    inline int Alltoallv(const unsigned *sendbuf, const int *sendcount,
                         const int *senddisp, unsigned *recvbuf,
                         const int *recvcount, const int *recvdisp) const;

    inline int Alltoallv(const int *sendbuf, const int *sendcount,
                         const int *senddisp, int *recvbuf,
                         const int *recvcount, const int *recvdisp) const;

    inline int Alltoallv(const unsigned long *sendbuf, const int *sendcount,
                         const int *senddisp, unsigned long *recvbuf,
                         const int *recvcount, const int *recvdisp) const;

    inline int Alltoallv(const long long *sendbuf, const int *sendcount,
                         const int *senddisp, long long *recvbuf,
                         const int *recvcount, const int *recvdisp) const;

    inline int Alltoallv(const long *sendbuf,
                         const int *sendcount, const int *senddisp,
                         long *recvbuf,
                         const int *recvcount, const int *recvdisp) const;

    inline int Alltoallv(const unsigned long long *sendbuf,
                         const int *sendcount, const int *senddisp,
                         unsigned long long *recvbuf,
                         const int *recvcount, const int *recvdisp) const;

    inline int Broadcast(double *Values, int Count=1, int Root=0 ) const;
    inline int Broadcast(int *Values, int Count=1, int Root=0 ) const;
    inline int Broadcast(bool *Values, int Count=1, int Root=0 ) const;
    inline int Broadcast(unsigned int *Values, int Count=1, int Root=0 ) const;
    inline int Broadcast(unsigned long *Values, int Count=1,
                         int Root=0 ) const;
    inline int Broadcast(long *Values, int Count=1, int Root=0 ) const;
    inline int Broadcast(long long *Values, int Count=1, int Root=0 ) const;
    inline int Broadcast(unsigned long long *Values, int Count=1,
                         int Root=0 ) const;
    inline int Broadcast(char *Values, int Count=1,
                         int Root=0 ) const;

    inline int GatherAll( const double *MyVals, double *AllVals,
                          int Count) const;
    inline int GatherAll( const int *MyVals, int *AllVals, int Count) const;
    inline int GatherAll( const int *MyVals, unsigned long *AllVals,
                          int Count) const;
    inline int GatherAll( const unsigned long *MyVals,
                          unsigned long *AllVals, int Count) const;
    int GatherAll(const iVector&, const Ordinal,
                        iVector&,
                  const intVector&, const intVector&) const;
    int GatherAll(const dVector&, const Ordinal,
                        dVector&,
                  const intVector&, const intVector&) const;
    inline int GatherAll( const double *MyVals, int MyCount, double *AllVals,
                          int *RevCount, int *Displs) const;
    inline int GatherAll( const int *MyVals, int MyCount, int *AllVals,
                          int *RevCount, int *Displs) const;
    inline int GatherAll( const long *MyVals, int MyCount
        , long *AllVals, int *RevCount, int *Displs) const;
    inline int GatherAll( const unsigned *MyVals, int MyCount
        , unsigned *AllVals, int *RevCount, int *Displs) const;
    inline int GatherAll( const unsigned long *MyVals, int MyCount
        , unsigned long *AllVals, int *RevCount, int *Displs) const;
    inline int GatherAll( const unsigned long long *MyVals, int MyCount
        , unsigned long long *AllVals, int *RevCount, int *Displs) const;
    inline int GatherAll( const long long *MyVals, int MyCount
        , long long *AllVals, int *RevCount, int *Displs) const;

    inline int GatherAll( const std::vector<std::string> &MyVals,
                          std::vector<std::string> &AllVals,
                          int *RevCount, int *Displs) const;

    inline int Scatterv( double *AllVals, int* Sendlen, int *Displs,
                         double *MyVals, int RevCount, int root) const;

    inline int SumAll(const double *PartialSums, double *GlobalSums,
                      int Count) const;
    inline int SumAll(const int *PartialSums, int *GlobalSums,
                      int Count) const;
    inline int SumAll(const long *PartialSums, long *GlobalSums,
                      int Count) const;
    inline int SumAll(const unsigned *PartialSums, unsigned *GlobalSums,
                      int Count) const;
    inline int SumAll(const long long *PartialSums,
                      long long *GlobalSums,
                      int Count) const;
    inline int SumAll(const unsigned long *PartialSums,
                      unsigned long *GlobalSums,
                      int Count) const;
    inline int SumAll(const unsigned long long *PartialSums,
                      unsigned long long *GlobalSums,
                      int Count) const;
    inline unsigned SumAll(const unsigned PartialSum) const;
    inline long int SumAll(const long int PartialSum) const;
    inline unsigned long SumAll(const unsigned long PartialSum) const;
    inline unsigned long long SumAll(const unsigned long long PartialSum) const;

    inline int Max( const int *PartialMaxs, int *GlobalMaxs,
                    int Count) const;
    inline int Max( const long *PartialMaxs, long *GlobalMaxs,
                    int Count) const;
    inline int Max( const unsigned *PartialMaxs, unsigned *GlobalMaxs,
                    int Count) const;
    inline int Max( const long long *PartialMaxs, long long *GlobalMaxs,
                    int Count) const;
    inline int Max( const long unsigned *PartialMaxs, long unsigned *GlobalMaxs,
                    int Count) const;
    inline int MaxAll( const double *PartialMaxs, double *GlobalMaxs,
                       int Count) const;
    inline int MaxAll( const int *PartialMaxs, int *GlobalMaxs,
                       int Count) const;
    inline int MaxAll( const long int *PartialMaxs,
                       long int *GlobalMaxs, int Count) const;
    inline int MaxAll( const unsigned int *PartialMaxs,
                       unsigned int *GlobalMaxs, int Count) const;
    inline int MaxAll( const long long *PartialMaxs,
                       long long *GlobalMaxs, int Count) const;
    inline int MaxAll( const unsigned long *PartialMaxs,
                       unsigned long *GlobalMaxs, int Count) const;
    inline int MaxAll( const unsigned long long *PartialMaxs,
                       unsigned long long *GlobalMaxs, int Count) const;
    inline int MaxAll( unsigned &GlobalMaxs) const;
    inline int MaxAll( int64_t &GlobalMaxs) const;
    inline int MaxAll( uint64_t &GlobalMaxs) const;

    inline int MinAll( const double *PartialMins, double *GlobalMins,
                       int Count) const;
    inline int MinAll( const int *PartialMins, int *GlobalMins,
                       int Count) const;
    inline int MinAll(const unsigned *PartialMins, unsigned *GlobalMins,
                      int Count) const;
    inline int MinAll(const long long *PartialMins,
                      long long *GlobalMins,
                      int Count) const;
    inline int MinAll(const unsigned long *PartialMins,
                      unsigned long *GlobalMins,
                      int Count) const;
    inline int MinAll(const unsigned long long *PartialMins,
                      unsigned long long *GlobalMins,
                      int Count) const;
    inline int MinAll( int &GlobalMins) const;
    inline int MinAll( unsigned int &GlobalMins) const;
    inline int MinAll( long long &GlobalMins) const;
    inline int MinAll( unsigned long &GlobalMins) const;
    inline int MinAll( unsigned long long &GlobalMins) const;
    inline int MinLocAll( int &GlobalMins) const;
    inline int MinLocAll( unsigned int &GlobalMins) const;
    inline int MinLocAll( unsigned long &GlobalMins) const;
    inline int MinLocAll( unsigned long long &GlobalMins) const;

    inline int MaxLocAll( const double *PartialMaxs, const int *PartialLocs,
                          double *GlobalMaxs, int *GlobalLocs,
                          int Count) const;

    inline int MinLocAll( const double *PartialMins, const int *PartialLocs,
                          double *GlobalMins, int *GlobalLocs,
                          int Count) const;

    inline void append_data(const std::string& fname,
                            const std::string& data) const;

    // provide local ostreams
    inline std::ostream & cout() const {return *out;}
    inline std::ostream & cerr() const {return (*err)<<MyPID()<<": ";}

    /// Returns the underlying MPI_Comm
    inline MPI_Comm mpicomm() const {return mpi_comm;}

    /// Creates a new group based on the given ids and returns the communicator
    inline Comm * CreateSubComm(std::vector <int>& ids,
                                const std::string& name="",
                                std::ostream& out=std::cout,
                                std::ostream& err=std::cerr,
                                const bool makeScratch=false) const;

    virtual void CommFree();
#ifdef DGM_USE_TEUCHOS_COMM
    inline Teuchos::RCP< const Teuchos::Comm< int > > getTeuchosComm();
#endif
    //@}

    /// \name I/O routines on generic data
    //@{
    /// Read a multi-dimensional binary file using MPI-IO
    inline void read_3d( dVector &f,
                         const std::vector<unsigned> &fn,
                         const std::vector<unsigned> &n,
                         const std::vector<unsigned> &imin,
                         const std::string &fname,
                         const IODataFormat format) const;
    //@}
  };

  //===========================================================================
  //                            Implementation
  //===========================================================================

  /// Constructor
  MpiComm::MpiComm(int *argc, char ***argv)
    : Comm("World"), mpi_comm(MPI_COMM_WORLD) {
    MPI_Init(argc, argv);
    MPI_Barrier(mpi_comm);
    NumWorld++;
    MPI_Comm_rank(mpi_comm, &pid);
    MPI_Comm_size(mpi_comm, &numproc);
    // set output stream
    if (!Master()) out = new ofstream("/dev/null");  // send to bit bucket
#ifdef DGM_USE_MONITOR
    if(Master()) out = new ofstream("monitor.txt");
    if(Master()) err = out;
#endif
    {
      char *tmp = getenv("DGM_VERBOSE");
      if (tmp != NULL) verb = atoi(tmp);
      if (verb>3) cout() << "DGM_VERBOSE = " << verb << std::endl;
    }
    {
      char *tmp = getenv("DGM_NO_SCRATCH");
      if (tmp != NULL) noScratch = true;
      if (verb>3) cout() << "DGM_NO_SCRATCH = " << noScratch << std::endl;
    }
    CreateScratch();
    {
      char *tmp = getenv("DGM_KEEP_SCRATCH");
      if (tmp != NULL) keepScratch = true;
      if (verb>3) cout() << "DGM_KEEP_SCRATCH = " << keepScratch << std::endl;
    }
    if (verb>2)
      cout()<<Name()<<" running on "<<numproc<<" processors."<<std::endl;
    if (firstComm) {
      DGM::Comm::information.banner(*out);
      firstComm=false;
    }
  }

  /// Constructor
  MpiComm::MpiComm(const MPI_Comm &mpi_comm_,
                   const std::string &name_,
                   std::ostream &out_,
                   std::ostream &err_,
                   const bool no_scratch) :
    Comm(name_,out_,err_), mpi_comm(mpi_comm_) {
    noScratch = no_scratch;
    if (mpi_comm==MPI_COMM_WORLD) NumWorld++;
    MPI_Comm_rank(mpi_comm, &pid);
    MPI_Comm_size(mpi_comm, &numproc);
    if (!Master()) out = new ofstream("/dev/null");  // send to bit bucket
#ifdef DGM_USE_MONITOR
    if(Master()) out = new ofstream("monitor.txt");
    if(Master()) err = out;
#endif
    {
      char *tmp = getenv("DGM_VERBOSE");
      if (tmp != NULL) verb = atoi(tmp);
      if (verb>3) cout() << "DGM_VERBOSE = " << verb << std::endl;
    }
    {
      char *tmp = getenv("DGM_NO_SCRATCH");
      if (tmp != NULL) noScratch = true;
      if (verb>3) cout() << "DGM_NO_SCRATCH = " << noScratch << std::endl;
    }
    CreateScratch();
    {
      char *tmp = getenv("DGM_KEEP_SCRATCH");
      if (tmp != NULL) keepScratch = true;
      if (verb>3) cout() << "DGM_KEEP_SCRATCH = " << keepScratch << std::endl;
    }
    if (verb>2)
      cout()<<Name()<<" running on "<<numproc<<" processors."<<std::endl;
    if (firstComm) {
      DGM::Comm::information.banner(*out);
      firstComm=false;
    }
  }

  /// Copy Constructor
  MpiComm::MpiComm(const MpiComm &in) :
    Comm(in),
    pid(in.pid),
    numproc(in.numproc),
    mpi_comm(in.mpi_comm) {
    if (mpi_comm==MPI_COMM_WORLD) NumWorld++;
  }

  /// Destructor
  MpiComm::~MpiComm() {
    if (verb>3) cout() << "MpiComm::~MpiComm() for " << Name() << std::endl;
    RemoveScratch();
    if (!Master()) delete out;
    if (mpi_comm == MPI_COMM_WORLD) {
      if (verb>3)
        if (Master()) std::cout << "NumWorld = " << NumWorld << std::endl;
      NumWorld--;
      if (NumWorld==0) {
        if (verb>3)
          if (Master()) std::cout << "Calling MPI_Finalize()" << std::endl;
        MPI_Finalize();
      }
    }
  }

  // The send_receive approach seems to work best on Cplant
  // Must be smaller than 2048.  A value of 2035 seems to be the critical
  // value on the cluster, but I have made it smaller to play it safe.
#ifdef DGM_OPT_FOR_MYRINET
  const int BUF_SIZE = 1024;  // MEMS Cluster
#endif

  // This is a terrible hack.  Marek thinks that MPI_Send switches from
  // buffered to synchronous (which must have a recieve waiting to succeed).
  // I bet this is true.  By breaking the message up into smaller chunks, I
  // basically force the use of the internally buffered Send.  To fix, I would
  // either have to Uuse the MPI_Bsend routine and attach my own buffer, or
  // instead just simply use the MPI_Sendrecv(_replace) function.

  void MpiComm::Send(int tag, double *buf, int len, int dest) const {
#ifdef DGM_OPT_FOR_MYRINET
    int n_msgs = len / BUF_SIZE;
    int last_msg_len = 0;
    if (n_msgs * BUF_SIZE < len) last_msg_len = len - n_msgs * BUF_SIZE;
    //cout << "Send:  len = " << len << ", n_msgs = " << n_msgs
    //     << ", last_msg_len = " << last_msg_len << std::endl;
    for (int i=0; i<n_msgs; i++) {
      //cout << "sending msg " << i << std::endl;
      if ( MPI_Send(buf+i*BUF_SIZE, BUF_SIZE, MPI_DOUBLE, dest, i,
                    mpi_comm) ) {
        cerr() << "MPI_Send error" << std::endl;
        exit(DGM::FAILURE);
      }
    }
    if (last_msg_len) {
      //cout << "sending last msg" << std::endl;
      if ( MPI_Send(buf+n_msgs*BUF_SIZE, last_msg_len, MPI_DOUBLE, dest,
                    n_msgs, mpi_comm) ) {
        cerr() << "MPI_Send error" << std::endl;
        exit(DGM::FAILURE);
      }
    }
#else
    // just send one big message
    if ( MPI_Send(buf, len, MPI_DOUBLE, dest, tag, mpi_comm) ) {
      cerr() << "MPI_Send error" << std::endl;
      exit(DGM::FAILURE);
    }
#endif
  }

  void MpiComm::Receive(int tag, double *buf, int len, int source) const {
    MPI_Status status;
#ifdef DGM_OPT_FOR_MYRINET
    int n_msgs = len / BUF_SIZE;
    int last_msg_len = 0;
    if (n_msgs * BUF_SIZE < len) last_msg_len = len - n_msgs * BUF_SIZE;
    //cout << "Recv:  len = " << len << ", n_msgs = " << n_msgs
    //     << ", last_msg_len = " << last_msg_len << std::endl;
    if (last_msg_len) {
      //cout << "receiving last msg" << std::endl;
      if ( MPI_Recv(buf+n_msgs*BUF_SIZE, last_msg_len, MPI_DOUBLE, source,
                    n_msgs, mpi_comm, &status) ) {
        cerr() << "MPI_Recv error" << std::endl;
        exit(DGM::FAILURE);
      }
    }
    for (int i=n_msgs-1; i>-1; i--) {
      //cout << "receiving msg " << i << std::endl;
      if ( MPI_Recv(buf+i*BUF_SIZE, BUF_SIZE, MPI_DOUBLE, source, i,
                    mpi_comm, &status) ) {
        cerr() << "MPI_Recv error" << std::endl;
        exit(DGM::FAILURE);
      }
    }
#else
    // just receive one big message
    if (MPI_Recv(buf, len, MPI_DOUBLE, source, tag, mpi_comm, &status)) {
      cerr() << "MPI_Recv error" << std::endl;
      exit(DGM::FAILURE);
    }
#endif
  }

  // blocking send
  void MpiComm::Send(int tag, int *buf, int len, int dest) const {
    if ( MPI_Send(buf, len, MPI_INT, dest, tag, mpi_comm) ) {
      cerr() << "MPI_Send error" << std::endl;
      exit(DGM::FAILURE);
    }
  }

  // blocking send
  void MpiComm::Receive(int tag, int *buf, int len, int source) const {
    MPI_Status status;
    if (MPI_Recv(buf, len, MPI_INT, source, tag, mpi_comm, &status)) {
      cerr() << "MPI_Recv error" << std::endl;
      exit(DGM::FAILURE);
    }
  }

  // nonblocking send
  void MpiComm::iSend(int tag, double *buf, int len, int dest) const {
    MPI_Request request;
    if ( MPI_Isend(buf, len, MPI_DOUBLE, dest, tag, mpi_comm, &request) ) {
      cerr() << "MPI_Send error" << std::endl;
      exit(DGM::FAILURE);
    }
    requests.push_back(request);
  }

  // nonblocking receive
  void MpiComm::iReceive(int tag, double *buf, int len, int source) const {
    MPI_Request request;
    if (MPI_Irecv(buf, len, MPI_DOUBLE, source, tag, mpi_comm, &request)) {
      cerr() << "MPI_Recv error" << std::endl;
      exit(DGM::FAILURE);
    }
    requests.push_back(request);
  }

  // nonblocking send
  void MpiComm::iSend(int tag, int *buf, int len, int dest) const {
    MPI_Request request;
    if ( MPI_Isend(buf, len, MPI_INT, dest, tag, mpi_comm, &request) ) {
      cerr() << "MPI_Send error" << std::endl;
      exit(DGM::FAILURE);
    }
    requests.push_back(request);
  }
  void MpiComm::iSend(int tag, long *buf, int len, int dest) const {
    MPI_Request request;
    if ( MPI_Isend(buf, len, MPI_LONG, dest, tag, mpi_comm, &request) ) {
      cerr() << "MPI_Send error" << std::endl;
      exit(DGM::FAILURE);
    }
    requests.push_back(request);
  }
  void MpiComm::iSend(int tag, unsigned *buf, int len, int dest) const {
    MPI_Request request;
    if ( MPI_Isend(buf, len, MPI_UNSIGNED, dest, tag, mpi_comm, &request) ) {
      cerr() << "MPI_Send error" << std::endl;
      exit(DGM::FAILURE);
    }
    requests.push_back(request);
  }
  void MpiComm::iSend(int tag, long long *buf, int len, int dest) const {
    MPI_Request request;
    if ( MPI_Isend(buf, len, MPI_LONG_LONG, dest, tag, mpi_comm, &request) ) {
      cerr() << "MPI_Send error" << std::endl;
      exit(DGM::FAILURE);
    }
    requests.push_back(request);
  }
  void MpiComm::iSend(int tag, long unsigned *buf, int len, int dest) const {
    MPI_Request request;
    if ( MPI_Isend(buf, len, MPI_UNSIGNED_LONG, dest, tag, mpi_comm, &request) ) {
      cerr() << "MPI_Send error" << std::endl;
      exit(DGM::FAILURE);
    }
    requests.push_back(request);
  }

  // nonblocking receive
  void MpiComm::iReceive(int tag, int *buf, int len, int source) const {
    MPI_Request request;
    if (MPI_Irecv(buf, len, MPI_INT, source, tag, mpi_comm, &request)) {
      cerr() << "MPI_Recv error" << std::endl;
      exit(DGM::FAILURE);
    }
    requests.push_back(request);
  }
  void MpiComm::iReceive(int tag, long *buf, int len, int source) const {
    MPI_Request request;
    if (MPI_Irecv(buf, len, MPI_LONG, source, tag, mpi_comm, &request)) {
      cerr() << "MPI_Recv error" << std::endl;
      exit(DGM::FAILURE);
    }
    requests.push_back(request);
  }
  void MpiComm::iReceive(int tag, unsigned *buf, int len, int source) const {
    MPI_Request request;
    if (MPI_Irecv(buf, len, MPI_UNSIGNED, source, tag, mpi_comm, &request)) {
      cerr() << "MPI_Recv error" << std::endl;
      exit(DGM::FAILURE);
    }
    requests.push_back(request);
  }
  void MpiComm::iReceive(int tag, long long *buf, int len, int source) const {
    MPI_Request request;
    if (MPI_Irecv(buf, len, MPI_LONG_LONG, source, tag, mpi_comm, &request)) {
      cerr() << "MPI_Recv error" << std::endl;
      exit(DGM::FAILURE);
    }
    requests.push_back(request);
  }
  void MpiComm::iReceive(int tag, long unsigned *buf, int len, int source) const {
    MPI_Request request;
    if (MPI_Irecv(buf, len, MPI_UNSIGNED_LONG, source, tag, mpi_comm, &request)) {
      cerr() << "MPI_Recv error" << std::endl;
      exit(DGM::FAILURE);
    }
    requests.push_back(request);
  }

  /// Wait for all outstanding nonblocking communication
  /** This waits for all requests that are in the current requests vector on
      this communicator */
  void MpiComm::WaitAll() const {
    using boost::numeric_cast;
    std::vector<MPI_Status> status(requests.size());
    if (MPI_Waitall( numeric_cast<int>(requests.size()),
                                     &(requests[0]), &(status[0]) )) {
      cerr() << "MpiComm::WaitAll error" << std::endl;
      exit(DGM::FAILURE);
    }
    requests.clear();
  }

  // buffers must be distinct
  void MpiComm::SendReceive(int stag, double *sbuf, int slen, int dest,
                            int rtag, double *rbuf, int rlen,
                            int source) const {
    MPI_Status status;
    if ( MPI_Sendrecv(sbuf, slen, MPI_DOUBLE, dest, stag,
                      rbuf, rlen, MPI_DOUBLE, source, rtag, mpi_comm,
                      &status) ) {
      cerr() << "MPI_Sendrecv error" << std::endl;
      exit(DGM::FAILURE);
    }
  }

  // buffers can share the same storage
  void MpiComm::SendReceiveReplace(double *buf, int len, int dest,
                                   int stag, int source, int rtag) const {
    MPI_Status status;
    if ( MPI_Sendrecv_replace(buf, len, MPI_DOUBLE, dest, stag,
                              source, rtag, mpi_comm, &status) ) {
      cerr() << "MPI_Sendrecv_replace error" << std::endl;
      exit(DGM::FAILURE);
    }
  }

// Check to see if the system call, mkdtemp, is available
#if defined(CPLANT) || defined(CYGWIN)
#define DGM_NO_MKDTEMP
#endif

  /// Make scratch file space
  void MpiComm::CreateScratch() const {
    using std::string;
    if (noScratch) return;
    string dir, user;
    char *tmp;
    tmp = getenv("DGM_SCRATCH");          // override default from environment
    if (tmp != NULL) dir = tmp;
#ifdef DGM_USE_SCRATCH_TMPDIR
    // default is system temporary directory
    if ( dir.size() == 0 ) dir = "/tmp";
#else
    // default is the current working directory
    if ( dir.size() == 0 ) {
      char *tmp_dir = 0;
      tmp_dir = getcwd(tmp_dir, 0);
      dir = tmp_dir;
      free(tmp_dir);
    }
#endif
    const char *u = getenv("USER");
    if (u != NULL) 
      user = string(u);
    else
      user = string("user");
    char node[80];
    sprintf(node,"%d",MyPID());
#ifdef DGM_NO_MKDTEMP
    string command ="/bin/mkdir -m u=rwx,go-rwx ";
    scratch = dir + "/" + "dgm-" + user + "_" + node + "/";
    command = command + scratch;
    if ( int status=system(command.c_str()) ) {
      if ( WEXITSTATUS(status) != 1 ) {  // status==1 is a warning for mkdir
        cerr() << "Error making scratch space." << std::endl;
        exit(DGM::FAILURE);
      }
    }
#else  // !DGM_NO_MKDTEMP
#ifdef DGM_CLEAN_SCRATCH_PPN
#if !defined(DGM_NO_SYSTEM)
    // The system call is not supported on Tbird or RedStorm
    string command ="/bin/rm -r "+dir+"/"+"dgm-"+user+"-*";
    if ( MyPID()%DGM_CLEAN_SCRATCH_PPN==0 ) {
      if ( int status=system(command.c_str()) ) {
        std::cout << MyPID() << ": Error #" << WEXITSTATUS(status)<<std::endl;
      }
    }
    Barrier();
#endif
#endif // DGM_CLEAN_SCRATCH_PPN
    scratch = dir + "/" + "dgm-" + user + "-" + node + "-XXXXXX";
    char dirname[512]; strncpy(dirname,scratch.c_str(),511);
    if (mkdtemp(dirname) == NULL) {
      cerr() << "Error creating scratch directory:" <<dirname<< std::endl;
      exit(DGM::FAILURE);
    }
    scratch = dirname;
    scratch += "/";
#endif // DGM_NO_MKDTEMP
    path = dir;  // save the path to the scratch directory
#ifdef DGM_MPICOMM_VERBOSE
    std::cout<<MyPID()<< ": Created scratch directory "<<scratch<<std::endl;
#endif
  }

  /// Remove scratch file space
  void MpiComm::RemoveScratch() const {
    using std::string;
    if (noScratch) return;
#ifdef DGM_MPICOMM_VERBOSE
    std::cout<<MyPID() << ": MpiComm::RemoveScratch("<<scratch<<")"<<std::endl;
#endif
#ifdef DGM_MPICOMM_ONEBYONE
    int m;
    if (!Master()) Receive(0,&m,1,0);
    if (Master()) {
      for (int n=1; n<NumProc(); n++) {
        Send(0,&n,1,n);     // give the go-ahead
        Receive(0,&m,1,n);   // wait till done
      }
    }
#endif
    if (keepScratch) {
      //cout() <<"Moving scratch..."<<std::endl;
      string command = "/bin/mv ";
      char node[80];
      sprintf(node,"%d",MyPID());
      command = command + scratch + " " + path + "/obj-" + node;
#ifdef DGM_MPICOMM_VERBOSE
      cout() << command << std::endl;
#endif
#if !defined(DGM_NO_SYSTEM)
      if (int status=system(command.c_str()))
        cerr()<<"MpiComm:: Non-zero status = "<<status
              <<" in removing scratch space."<<std::endl;
#endif
    }
#ifdef DGM_USE_BOOST_FS
    try {
      boost::filesystem::path p(scratch);
      //std::cout<<MyPID()<<": Boost remove_all("<<p<<")"<<std::endl;
      //std::cout<<MyPID()<<": Status of "<<p<<" is "
      //         <<boost::filesystem::exists(p)<<endl;
      boost::filesystem::remove_all(p);
      //std::cout<<MyPID()<<": Status of "<<p<<" is "
      //         <<boost::filesystem::exists(p)<<endl;
      scratch="";
    }
    catch (boost::filesystem::filesystem_error &e) {
      std::cout<<MyPID()<<": Boost filesystem error "<<e.what()<<std::endl;
      throw DGM::exception("Boost filesystem error");
    }
#else
#ifdef DGM_USE_SYSTEM_RM
    // this version uses the system function and /bin/rm
    string command ="/bin/rm -rf ";  // make sure that remove is forced
    command = command + scratch;
#if !defined(DGM_NO_SYSTEM)
#ifdef DGM_MPICOMM_VERBOSE
    std::cout<<MyPID()<<": Removing scratch directory "<<scratch<<std::endl;
#endif
    const int status = system(command.c_str());
    if ( status != 0 )
      cerr()<<"MpiComm:: Non-zero status = "<<WEXITSTATUS(status)
            <<" in "<<command<<std::endl;
    scratch="";
#endif
#else
   // this version uses the cstdio remove function
#ifdef DGM_MPICOMM_VERBOSE
    std::cout<<MyPID()<<": Removing scratch directory "<<scratch<<std::endl;
#endif
    const int status = remove(scratch.c_str());
    if ( status != 0 ) {
      cerr()<<"MpiComm:: Non-zero status = "<<WEXITSTATUS(status)
            <<" in removing "<<scratch<<std::endl;
      perror( "Error deleting scratch directory ");
    }
    scratch="";
#endif
#endif
#ifdef DGM_MPICOMM_ONEBYONE
    if (!Master()) Send(0,&m,1,0);
    Barrier();
#endif
    //std::cout<<MyPID() << ": MpiComm::RemoveScratch() completed"<<std::endl;
  }

  // Epetra_Comm like interface

  void MpiComm::Barrier() const {
    MPI_Barrier(mpi_comm);
  }

  int MpiComm::Broadcast(double *Values, int Count, int Root) const {
    return MPI_Bcast( Values, Count, MPI_DOUBLE, Root, mpi_comm );
  }

  int MpiComm::Broadcast(int *Values, int Count, int Root) const {
    return MPI_Bcast( Values, Count, MPI_INT, Root, mpi_comm );
  }

  int MpiComm::Broadcast(bool *Values, int Count, int Root) const {
    return MPI_Bcast( Values, Count, MPI_BYTE, Root, mpi_comm );
  }

  int MpiComm::Broadcast(unsigned int *Values, int Count, int Root) const {
    return MPI_Bcast( Values, Count, MPI_UNSIGNED, Root, mpi_comm );
  }

  int MpiComm::Broadcast(unsigned long *Values, int Count, int Root) const {
    return MPI_Bcast( Values, Count, MPI_UNSIGNED_LONG, Root, mpi_comm );
  }

  int MpiComm::Broadcast(long *Values, int Count, int Root) const {
    return MPI_Bcast( Values, Count, MPI_LONG, Root, mpi_comm );
  }

  int MpiComm::Broadcast(unsigned long long *Values, int Count,
                         int Root) const {
    return MPI_Bcast( Values, Count, MPI_UNSIGNED_LONG_LONG, Root, mpi_comm );
  }

  int MpiComm::Broadcast(long long *Values, int Count, int Root) const {
    return MPI_Bcast( Values, Count, MPI_LONG_LONG, Root, mpi_comm );
  }

  int MpiComm::Broadcast(char *Values, int Count, int Root) const {
    return MPI_Bcast( Values, Count, MPI_CHAR, Root, mpi_comm );
  }

  int MpiComm::Gather(const unsigned *sendbuf, const int sendcount,
                      unsigned *recvbuf, const int recvcount,
                      const int root) const {
    return MPI_Gather(const_cast<unsigned *>(sendbuf),
                      sendcount, MPI_UNSIGNED,
                      const_cast<unsigned *>(recvbuf),
                      recvcount, MPI_UNSIGNED,
                      root, mpi_comm);
  }
  int MpiComm::Gather(const int      *sendbuf, const int sendcount,
                      int      *recvbuf, const int recvcount,
                      const int root) const {
    return MPI_Gather(const_cast<int *>(sendbuf),
                      sendcount, MPI_INT,
                      const_cast<int *>(recvbuf),
                      recvcount, MPI_INT,
                      root, mpi_comm);
  }

  int MpiComm::GatherV(DTK::Ordinal_t *sendbuf, const size_t sendcount,
                       DTK::Ordinal_t *recvbuf, int *recvcounts,
                       int *displs, const int  root) const {
    return MPI_Gatherv(sendbuf, sendcount, MPI_UNSIGNED,
                       recvbuf, recvcounts, displs, MPI_UNSIGNED,
                       root, mpi_comm);
  }

  int MpiComm::GatherV(unsigned *sendbuf, const int sendcount,
                       unsigned *recvbuf, int *recvcounts,
                       int *displs, const int  root) const {
    return MPI_Gatherv(sendbuf, sendcount, MPI_UNSIGNED,
                       recvbuf, recvcounts, displs, MPI_UNSIGNED,
                       root, mpi_comm);
  }

  int MpiComm::GatherV(int *sendbuf, const int sendcount,
                       int *recvbuf, int *recvcounts,
                       int *displs, const int  root) const {
    return MPI_Gatherv(sendbuf, sendcount, MPI_INT,
                       recvbuf, recvcounts, displs, MPI_INT,
                       root, mpi_comm);
  }

  int MpiComm::Scan( const int *MyVals, int *AllVals, int Count) const {
    return MPI_Scan(const_cast<int*>(MyVals), AllVals,
                    Count, MPI_INT, MPI_SUM, mpi_comm);
  }

  int MpiComm::Scan( const unsigned long *MyVals, unsigned long *AllVals,
                     int Count) const {
    return MPI_Scan(const_cast<unsigned long*>(MyVals), AllVals,
                    Count, MPI_UNSIGNED_LONG, MPI_SUM, mpi_comm);
  }
  int MpiComm::Scan( const unsigned long long *MyVals,
                     unsigned long long *AllVals,
                     int Count) const {
    return MPI_Scan(const_cast<unsigned long long*>(MyVals), AllVals,
                    Count, MPI_UNSIGNED_LONG_LONG, MPI_SUM, mpi_comm);
  }

  int MpiComm::Alltoall(const int *sendbuf, const int sendcount,
                        int *recvbuf, const int recvcount) const {
    return MPI_Alltoall(const_cast<int *>(sendbuf),
                        sendcount,
                        MPI_INT,
                        recvbuf,
                        recvcount ,
                        MPI_INT,
                        mpi_comm);
  }

  int MpiComm::Alltoall(const unsigned long *sendbuf, const int sendcount,
                        unsigned long *recvbuf, const int recvcount) const {
    return MPI_Alltoall(const_cast<unsigned long*>(sendbuf),
                        sendcount,
                        MPI_UNSIGNED_LONG,
                        recvbuf,
                        recvcount ,
                        MPI_UNSIGNED_LONG,
                        mpi_comm);
  }

  int MpiComm::Alltoallv(const double *sendbuf, const int *sendcount,
                         const int *senddisp, double *recvbuf,
                         const int *recvcount, const int *recvdisp) const {
    return MPI_Alltoallv(const_cast<double *>  (sendbuf),
                         const_cast<int *>     (sendcount),
                         const_cast<int *>     (senddisp),
                         MPI_DOUBLE,
                         recvbuf,
                         const_cast<int *>     (recvcount),
                         const_cast<int *>     (recvdisp),
                         MPI_DOUBLE,
                         mpi_comm);
  }

  int MpiComm::Alltoallv(const float  *sendbuf, const int *sendcount,
                         const int *senddisp, float  *recvbuf,
                         const int *recvcount, const int *recvdisp) const {
    return MPI_Alltoallv(const_cast<float  *>  (sendbuf),
                         const_cast<int *>     (sendcount),
                         const_cast<int *>     (senddisp),
                         MPI_FLOAT,
                         recvbuf,
                         const_cast<int *>     (recvcount),
                         const_cast<int *>     (recvdisp),
                         MPI_FLOAT,
                         mpi_comm);
  }

  int MpiComm::Alltoallv(const unsigned *sendbuf, const int *sendcount,
                         const int *senddisp, unsigned *recvbuf,
                         const int *recvcount, const int *recvdisp) const {
    return MPI_Alltoallv(const_cast<unsigned *>(sendbuf),
                         const_cast<int *>     (sendcount),
                         const_cast<int *>     (senddisp),
                         MPI_UNSIGNED,
                         recvbuf,
                         const_cast<int *>     (recvcount),
                         const_cast<int *>     (recvdisp),
                         MPI_UNSIGNED,
                         mpi_comm);
  }

  int MpiComm::Alltoallv(const int *sendbuf, const int *sendcount,
                         const int *senddisp, int *recvbuf,
                         const int *recvcount, const int *recvdisp) const {
#ifdef DGM_USE_MPI_ALLTOALLV
/*  
 *  This seems to allocate and hold a huge amount of memory on 
 *  Redsky even when the buffers are small.  Replace with the simple
 *  non-blocking point-to-point below.
*/
    return MPI_Alltoallv(const_cast<int *>(sendbuf),
                         const_cast<int *>(sendcount),
                         const_cast<int *>(senddisp),
                         MPI_INT,
                         recvbuf,
                         const_cast<int *>(recvcount),
                         const_cast<int *>(recvdisp),
                         MPI_INT,
                         mpi_comm);
#else
    const int n   = NumProc();
    const int tag = 123436;
    for (int i=0; i<n; ++i) 
      if (sendcount[i]) 
        iSend(tag, const_cast<int *>(&sendbuf[senddisp[i]]), sendcount[i], i);
    for (int i=0; i<n; ++i) 
      if (recvcount[i]) 
        iReceive(tag,                &recvbuf[recvdisp[i]] , recvcount[i], i);
    WaitAll();
    return 0;
#endif
  }

  int MpiComm::Alltoallv(const unsigned long *sendbuf, const int *sendcount,
                         const int *senddisp, unsigned long *recvbuf,
                         const int *recvcount, const int *recvdisp) const {
    return MPI_Alltoallv(const_cast<unsigned long*>(sendbuf),
                         const_cast<int *>     (sendcount),
                         const_cast<int *>     (senddisp),
                         MPI_UNSIGNED_LONG,
                         recvbuf,
                         const_cast<int *>     (recvcount),
                         const_cast<int *>     (recvdisp),
                         MPI_UNSIGNED_LONG,
                         mpi_comm);
  }

  int MpiComm::Alltoallv(const long long *sendbuf, const int *sendcount,
                         const int *senddisp, long long *recvbuf,
                         const int *recvcount, const int *recvdisp) const {
    return MPI_Alltoallv(const_cast<long long*>(sendbuf),
                         const_cast<int *>     (sendcount),
                         const_cast<int *>     (senddisp),
                         MPI_LONG_LONG,
                         recvbuf,
                         const_cast<int *>     (recvcount),
                         const_cast<int *>     (recvdisp),
                         MPI_LONG_LONG,
                         mpi_comm);
  }

  int MpiComm::Alltoallv(const long *sendbuf,
                         const int *sendcount,
                         const int *senddisp, long *recvbuf,
                         const int *recvcount, const int *recvdisp) const {
    return MPI_Alltoallv(const_cast<long *>(sendbuf),
                         const_cast<int *>     (sendcount),
                         const_cast<int *>     (senddisp),
                         MPI_LONG,
                         recvbuf,
                         const_cast<int *>     (recvcount),
                         const_cast<int *>     (recvdisp),
                         MPI_LONG,
                         mpi_comm);
  }

  int MpiComm::Alltoallv(const unsigned long long *sendbuf,
                         const int *sendcount,
                         const int *senddisp, unsigned long long *recvbuf,
                         const int *recvcount, const int *recvdisp) const {
    return MPI_Alltoallv(const_cast<unsigned long long *>(sendbuf),
                         const_cast<int *>     (sendcount),
                         const_cast<int *>     (senddisp),
                         MPI_UNSIGNED_LONG_LONG,
                         recvbuf,
                         const_cast<int *>     (recvcount),
                         const_cast<int *>     (recvdisp),
                         MPI_UNSIGNED_LONG_LONG,
                         mpi_comm);
  }

  int MpiComm::GatherAll(const double *MyVals, double *AllVals,
                         int Count) const {
    return MPI_Allgather(const_cast<double*>(MyVals), Count, MPI_DOUBLE,
                         AllVals, Count, MPI_DOUBLE, mpi_comm);
  }

  int MpiComm::GatherAll(const int *MyVals, int *AllVals, int Count) const {
    return MPI_Allgather(const_cast<int*>(MyVals), Count, MPI_INT, AllVals,
                         Count, MPI_INT, mpi_comm);
  }

  int MpiComm::GatherAll(const int *MyVals, unsigned long *AllVals,
                         int Count) const
  {
    return MPI_Allgather(const_cast<int *>(MyVals), Count, MPI_UNSIGNED_LONG,
    AllVals, Count, MPI_UNSIGNED_LONG, mpi_comm);
  }

  int MpiComm::GatherAll(const unsigned long *MyVals, unsigned long *AllVals,
                         int Count) const
  {
    return MPI_Allgather(const_cast<unsigned long *>(MyVals), Count,
    MPI_UNSIGNED_LONG, AllVals, Count, MPI_UNSIGNED_LONG, mpi_comm);
  }

  int MpiComm::GatherAll(const double *MyVals, int SendCount, double *AllVals,
                         int *RevCount, int *Displs) const {
    return MPI_Allgatherv(const_cast<double*>(MyVals), SendCount, MPI_DOUBLE,
                          AllVals, RevCount, Displs, MPI_DOUBLE, mpi_comm);
  }

  int MpiComm::GatherAll(const int *MyVals, int SendCount, int *AllVals,
                         int *RevCount, int *Displs) const {
    return MPI_Allgatherv(const_cast<int*>(MyVals), SendCount, MPI_INT,
                          AllVals, RevCount, Displs, MPI_INT, mpi_comm);
  }

  int MpiComm::GatherAll(const long *MyVals, int SendCount,
                         long *AllVals, int *RecvCount,
                         int *Displs) const {
    return MPI_Allgatherv(const_cast<long *>(MyVals), SendCount,
    MPI_LONG, AllVals, RecvCount, Displs, MPI_LONG, mpi_comm);
  }

  int MpiComm::GatherAll(const unsigned *MyVals, int SendCount,
                         unsigned *AllVals, int *RecvCount,
                         int *Displs) const {
    return MPI_Allgatherv(const_cast<unsigned *>(MyVals), SendCount,
    MPI_UNSIGNED, AllVals, RecvCount, Displs, MPI_UNSIGNED, mpi_comm);
  }

  int MpiComm::GatherAll(const unsigned long *MyVals, int SendCount,
                         unsigned long *AllVals, int *RecvCount,
                         int *Displs) const {
    return MPI_Allgatherv(const_cast<unsigned long *>(MyVals), SendCount,
    MPI_UNSIGNED_LONG, AllVals, RecvCount, Displs, MPI_UNSIGNED_LONG, mpi_comm);
  }

  int MpiComm::GatherAll(const unsigned long long *MyVals, int SendCount,
                         unsigned long long *AllVals, int *RecvCount,
                         int *Displs) const {
    return MPI_Allgatherv(const_cast<unsigned long long *>(MyVals), SendCount,
    MPI_UNSIGNED_LONG_LONG, AllVals, RecvCount, Displs,
    MPI_UNSIGNED_LONG_LONG, mpi_comm);
  }
  int MpiComm::GatherAll(const long long *MyVals, int SendCount,
                         long long *AllVals, int *RecvCount,
                         int *Displs) const {
    return MPI_Allgatherv(const_cast<long long *>(MyVals), SendCount,
    MPI_LONG_LONG, AllVals, RecvCount, Displs,
    MPI_LONG_LONG, mpi_comm);
  }

  int MpiComm::GatherAll( const std::vector<std::string> &MyVals,
                          std::vector<std::string> &AllVals,
                          int *RevCount, int *Displs) const {
    using boost::numeric_cast;
    using std::vector;
    int status=0, len=0;
    for (size_t i=0; i<MyVals.size(); ++i) len += MyVals[i].length();
    int np = NumProc();
    vector<int> rcounts(np,0);
    vector<int> displs (np,0);
    status = GatherAll(&len, &rcounts[0], 1);
    int glen=0;
    for (int i=0; i<np; ++i) {
      glen += rcounts[i];
      displs[i] = 0;
      for (int j=0; j<i; j++) displs[i] += rcounts[j];
    }
    vector<char> buf(len);
    for (size_t i=0, k=0; i<MyVals.size(); ++i)
      for (size_t j=0; j<MyVals[i].length(); ++j)
        buf[k++] = MyVals[i][j];
    vector<char> gbuf(glen);
    status = MPI_Allgatherv(&buf[0], len, MPI_CHAR,
                            &gbuf[0], &rcounts[0], &displs[0],
                            MPI_CHAR, mpi_comm);
    iVector num ( MyVals.size());
    iVector gnum(AllVals.size());
    for (size_t i=0; i<MyVals.size(); ++i) num[i]=MyVals[i].length();
    status = GatherAll(num.ptr(), numeric_cast<int>(MyVals.size()),
                      gnum.ptr(), RevCount, Displs );
    for (size_t i=0, k=0; i<AllVals.size(); ++i) {
      AllVals[i].clear();
      for (Ordinal j=0; j<gnum[i]; ++j) AllVals[i] += gbuf[k++];
    }
    return status;
  }

  int MpiComm::Scatterv( double *AllVals, int* Sendlen, int *Displs,
                         double *MyVals, int RevCount, int root) const {
    return MPI_Scatterv(AllVals, Sendlen, Displs, MPI_DOUBLE,
                        MyVals, RevCount, MPI_DOUBLE, root,mpi_comm);
  }

  int MpiComm::SumAll( const double *PartialSums, double *GlobalSums,
                       int Count) const {
    return MPI_Allreduce( const_cast<double*>(PartialSums), GlobalSums, Count,
                          MPI_DOUBLE, MPI_SUM, mpi_comm );
  }

  int MpiComm::SumAll( const int *PartialSums, int *GlobalSums,
                       int Count) const {
    return MPI_Allreduce( const_cast<int*>(PartialSums), GlobalSums, Count,
                          MPI_INT, MPI_SUM, mpi_comm );
  }
  int MpiComm::SumAll( const long *PartialSums, long *GlobalSums,
                       int Count) const {
    return MPI_Allreduce( const_cast<long*>(PartialSums), GlobalSums, Count,
                          MPI_LONG, MPI_SUM, mpi_comm );
  }

  int MpiComm::SumAll( const unsigned *PartialSums, unsigned *GlobalSums,
                       int Count) const {
    return MPI_Allreduce(const_cast<unsigned*>(PartialSums), GlobalSums, Count,
                         MPI_UNSIGNED, MPI_SUM, mpi_comm );
  }

  unsigned MpiComm::SumAll( const unsigned PartialSum) const {
    unsigned GlobalSum;
    const int Count = 1;
    MPI_Allreduce(const_cast<unsigned*>(&PartialSum), &GlobalSum, Count,
                         MPI_UNSIGNED, MPI_SUM, mpi_comm );
    return GlobalSum;
  }

  int MpiComm::SumAll(const long long *PartialSums,
                      long long *GlobalSums,
                      int Count) const {
    return MPI_Allreduce(const_cast<long long*>(PartialSums),
                         GlobalSums, Count, MPI_LONG_LONG,
                         MPI_SUM, mpi_comm );
  }
  int MpiComm::SumAll(const unsigned long *PartialSums,
                      unsigned long *GlobalSums,
                      int Count) const {
    return MPI_Allreduce(const_cast<unsigned long*>(PartialSums),
                         GlobalSums, Count, MPI_UNSIGNED_LONG,
                         MPI_SUM, mpi_comm );
  }

  long int MpiComm::SumAll(const long int PartialSum ) const {
    long int GlobalSum;
    const int Count = 1;
    MPI_Allreduce(const_cast<long int*>(&PartialSum), &GlobalSum, Count,
                  MPI_LONG, MPI_SUM, mpi_comm );
    return GlobalSum;
  }
  unsigned long MpiComm::SumAll( const unsigned long PartialSum ) const {
    unsigned long GlobalSum;
    const int Count = 1;
    MPI_Allreduce(const_cast<unsigned long*>(&PartialSum), &GlobalSum, Count,
                  MPI_UNSIGNED_LONG, MPI_SUM, mpi_comm );
    return GlobalSum;
  }

  int MpiComm::SumAll(const unsigned long long *PartialSums,
                      unsigned long long *GlobalSums,
                      int Count) const {
    return MPI_Allreduce(const_cast<unsigned long long*>(PartialSums),
                         GlobalSums, Count, MPI_UNSIGNED_LONG_LONG,
                         MPI_SUM, mpi_comm );
  }

  unsigned long long MpiComm::SumAll( const unsigned long long PartialSum )
  const {
    unsigned long long GlobalSum;
    const int Count = 1;
    MPI_Allreduce(const_cast<unsigned long long*>(&PartialSum), &GlobalSum,
                  Count, MPI_UNSIGNED_LONG_LONG, MPI_SUM, mpi_comm );
    return GlobalSum;
  }

  int MpiComm::Max( const int *PartialMaxs, int *GlobalMaxs,
                    int Count) const {
    return MPI_Reduce(const_cast<int*>(PartialMaxs), GlobalMaxs, Count,
                         MPI_INT, MPI_MAX, 0, mpi_comm );
  }
  int MpiComm::Max( const long *PartialMaxs, long *GlobalMaxs,
                    int Count) const {
    return MPI_Reduce(const_cast<long*>(PartialMaxs), GlobalMaxs, Count,
                         MPI_LONG, MPI_MAX, 0, mpi_comm );
  }
  int MpiComm::Max( const unsigned *PartialMaxs, unsigned *GlobalMaxs,
                    int Count) const {
    return MPI_Reduce(const_cast<unsigned*>(PartialMaxs), GlobalMaxs, Count,
                         MPI_UNSIGNED, MPI_MAX, 0, mpi_comm );
  }
  int MpiComm::Max( const long long *PartialMaxs, long long *GlobalMaxs,
                    int Count) const {
    return MPI_Reduce(const_cast<long long*>(PartialMaxs), GlobalMaxs, Count,
                         MPI_LONG_LONG, MPI_MAX, 0, mpi_comm );
  }
  int MpiComm::Max( const long unsigned *PartialMaxs, long unsigned *GlobalMaxs,
                    int Count) const {
    return MPI_Reduce(const_cast<long unsigned*>(PartialMaxs), GlobalMaxs, Count,
                         MPI_UNSIGNED_LONG, MPI_MAX, 0, mpi_comm );
  }

  int MpiComm::MaxAll( const double *PartialMaxs, double *GlobalMaxs,
                       int Count) const {
    return MPI_Allreduce(const_cast<double*>(PartialMaxs), GlobalMaxs, Count,
                         MPI_DOUBLE, MPI_MAX, mpi_comm );
  }

  int MpiComm::MaxAll( const int *PartialMaxs, int *GlobalMaxs,
                       int Count) const {
    return MPI_Allreduce(const_cast<int*>(PartialMaxs), GlobalMaxs, Count,
                         MPI_INT, MPI_MAX, mpi_comm );
  }

  int MpiComm::MaxAll( const long int *PartialMaxs,
                       long int *GlobalMaxs,
                       int Count) const {
    return MPI_Allreduce(const_cast<long*>(PartialMaxs), GlobalMaxs, Count,
                         MPI_LONG, MPI_MAX, mpi_comm );
  }
  int MpiComm::MaxAll( const unsigned int *PartialMaxs,
                       unsigned int *GlobalMaxs,
                       int Count) const {
    return MPI_Allreduce(const_cast<unsigned*>(PartialMaxs), GlobalMaxs, Count,
                         MPI_UNSIGNED, MPI_MAX, mpi_comm );
  }

  int MpiComm::MaxAll( const long long *PartialMaxs,
                       long long *GlobalMaxs,
                       int Count) const {
    return MPI_Allreduce(const_cast<long long*>(PartialMaxs),
                         GlobalMaxs, Count,
                         MPI_LONG_LONG, MPI_MAX, mpi_comm );
  }
  int MpiComm::MaxAll( const unsigned long *PartialMaxs,
                       unsigned long *GlobalMaxs,
                       int Count) const {
    return MPI_Allreduce(const_cast<unsigned long*>(PartialMaxs),
                         GlobalMaxs, Count,
                         MPI_UNSIGNED_LONG, MPI_MAX, mpi_comm );
  }
  int MpiComm::MaxAll( const unsigned long long *PartialMaxs,
                       unsigned long long *GlobalMaxs,
                       int Count) const {
    return MPI_Allreduce(const_cast<unsigned long long*>(PartialMaxs),
                         GlobalMaxs, Count,
                         MPI_UNSIGNED_LONG_LONG, MPI_MAX, mpi_comm );
  }

  int MpiComm::MaxAll( unsigned &GlobalMaxs) const {
    unsigned t=GlobalMaxs;
    return MPI_Allreduce(&t, &GlobalMaxs, 1, MPI_UNSIGNED, MPI_MAX, mpi_comm);
  }

  int MpiComm::MaxAll( int64_t &GlobalMaxs) const {
    int64_t t=GlobalMaxs;
    return MPI_Allreduce(&t, &GlobalMaxs, 1, MPI_LONG_LONG, MPI_MAX, mpi_comm);
  }

  int MpiComm::MaxAll( uint64_t &GlobalMaxs) const {
    uint64_t temp = GlobalMaxs;
    return MPI_Allreduce(&temp, &GlobalMaxs, 1, MPI_UNSIGNED_LONG_LONG,
                         MPI_MAX, mpi_comm);
  }

  int MpiComm::MinAll( const double *PartialMins, double *GlobalMins,
                       int Count) const {
    return MPI_Allreduce(const_cast<double*>(PartialMins), GlobalMins, Count,
                         MPI_DOUBLE, MPI_MIN, mpi_comm );
  }

  int MpiComm::MinAll( const int *PartialMins, int *GlobalMins,
                       int Count) const {
    return MPI_Allreduce(const_cast<int*>(PartialMins), GlobalMins, Count,
                         MPI_INT, MPI_MIN, mpi_comm );
  }

  int MpiComm::MinAll( const unsigned *PartialMins, unsigned *GlobalMins,
                       int Count) const {
    return MPI_Allreduce(const_cast<unsigned*>(PartialMins), GlobalMins, Count,
                         MPI_UNSIGNED, MPI_MIN, mpi_comm );
  }

  int MpiComm::MinAll(const long long *PartialMins,
                      long long *GlobalMins,
                      int Count) const {
    return MPI_Allreduce(const_cast<long long*>(PartialMins),
                         GlobalMins, Count, MPI_LONG_LONG,
                         MPI_MIN, mpi_comm );
  }
  int MpiComm::MinAll(const unsigned long *PartialMins,
                      unsigned long *GlobalMins,
                      int Count) const {
    return MPI_Allreduce(const_cast<unsigned long*>(PartialMins),
                         GlobalMins, Count, MPI_UNSIGNED_LONG,
                         MPI_MIN, mpi_comm );
  }
  int MpiComm::MinAll(const unsigned long long *PartialMins,
                      unsigned long long *GlobalMins,
                      int Count) const {
    return MPI_Allreduce(const_cast<unsigned long long*>(PartialMins),
                         GlobalMins, Count, MPI_UNSIGNED_LONG_LONG,
                         MPI_MIN, mpi_comm );
  }

  int MpiComm::MinAll( int &GlobalMins) const {
    int t=GlobalMins;
    return MPI_Allreduce(&t, &GlobalMins, 1,
                         MPI_INT, MPI_MIN, mpi_comm );
  }
  int MpiComm::MinAll( unsigned int &GlobalMins) const {
    unsigned int t=GlobalMins;
    return MPI_Allreduce(&t, &GlobalMins, 1,
                         MPI_UNSIGNED, MPI_MIN, mpi_comm );
  }
  int MpiComm::MinAll( long long &GlobalMins) const {
    long long t=GlobalMins;
    return MPI_Allreduce(&t, &GlobalMins, 1,
                         MPI_LONG_LONG, MPI_MIN, mpi_comm );
  }
  int MpiComm::MinAll( unsigned long &GlobalMins) const {
    unsigned long t=GlobalMins;
    return MPI_Allreduce(&t, &GlobalMins, 1,
                         MPI_UNSIGNED_LONG, MPI_MIN, mpi_comm );
  }
  int MpiComm::MinAll( unsigned long long &GlobalMins) const {
    unsigned long long t=GlobalMins;
    return MPI_Allreduce(&t, &GlobalMins, 1,
                         MPI_UNSIGNED_LONG_LONG, MPI_MIN, mpi_comm );
  }

  int MpiComm::MinLocAll( int &GlobalMins) const {
    std::pair<int,int> out(0,0), in(GlobalMins,MyPID());
    MPI_Allreduce(&in, &out, 1,
                   MPI_2INT, MPI_MINLOC, mpi_comm );
    GlobalMins = out.first;
    return out.second;
  }
  int MpiComm::MaxLocAll( const double *PartialMaxs, const int *PartialLocs,
                          double *GlobalMaxs, int *GlobalLocs,
                          int Count) const {
    using std::make_pair;
    using std::pair;
    using std::vector;
    vector<pair<double,int> > partial;
    vector<pair<double,int> > global;
    for (int i=0; i<Count; ++i) {
      partial.push_back(make_pair( PartialMaxs[i], PartialLocs[i] ));
      global.push_back(make_pair( PartialMaxs[i], PartialLocs[i] ));
    }

    int status = MPI_Allreduce(&partial[0], &global[0], Count,
                               MPI_DOUBLE_INT, MPI_MAXLOC, mpi_comm );

    for (int i=0; i<Count; ++i) {
      GlobalMaxs[i] = global[i].first;
      GlobalLocs[i] = global[i].second;
    }
    return status;
  }

  int MpiComm::MinLocAll( const double *PartialMins, const int *PartialLocs,
                          double *GlobalMins, int *GlobalLocs,
                          int Count) const {
    using std::make_pair;
    using std::pair;
    using std::vector;
    vector<pair<double,int> > partial;
    vector<pair<double,int> > global;
    for (int i=0; i<Count; ++i) {
      partial.push_back(make_pair( PartialMins[i], PartialLocs[i] ));
      global.push_back(make_pair( PartialMins[i], PartialLocs[i] ));
    }

    int status = MPI_Allreduce(&partial[0], &global[0], Count,
                  MPI_DOUBLE_INT, MPI_MINLOC, mpi_comm );

    for (int i=0; i<Count; ++i) {
      GlobalMins[i] = global[i].first;
      GlobalLocs[i] = global[i].second;
    }
    return status;
  }

  /// Performs a parallel append to a file
  void MpiComm::append_data(const std::string& fname,
                            const std::string& data) const{
    using boost::numeric_cast;
    // Determine how much data is in the buffer
    char native[] = "native";
    int my_ndata=numeric_cast<int>(data.length());

    // Share the amount of data in the buffer with the other processors
    int np;
    MPI_Comm_size(mpi_comm,&np);
    int ndata[np];
    MPI_Allgather(&my_ndata,1,MPI_INT,ndata,1,MPI_INT,mpi_comm);

    // Find the offset for this processor
    int rank;
    MPI_Comm_rank(mpi_comm,&rank);
    MPI_Offset offset=0;
    for(int i=0;i<rank;i++) offset += ndata[i];

    // Open the file for writing
    MPI_File file;
    if (MPI_File_open(mpi_comm,const_cast <char*> (fname.c_str()),
                  MPI_MODE_WRONLY | MPI_MODE_APPEND,MPI_INFO_NULL,&file)) {
      throw exception(string("MPI_File_open failed to open file " + fname));
    }
    MPI_Offset end;
    MPI_File_get_position(file,&end);
    MPI_Barrier(mpi_comm);
    const MPI_Offset disp = end + offset*sizeof(char);
    MPI_File_set_view(file, disp, MPI_CHAR,MPI_CHAR, native,MPI_INFO_NULL);

    // Write the data
    MPI_File_write(file,const_cast <char*> (data.c_str()),my_ndata,
                   MPI_CHAR,MPI_STATUS_IGNORE);

    // Close the file
    MPI_File_close(&file);
  }

  /// Creates a new group based on the given ids and returns the communicator
  Comm* MpiComm::CreateSubComm(std::vector <int>& ids,
    const std::string& name,std::ostream& out, std::ostream& err,
    const bool makeScratch) const {
    using boost::numeric_cast;

    // Create a group that corresponds to this communicator
    MPI_Group current;
    MPI_Comm_group(mpi_comm,&current);

    // Create a group that corresponds to the subgroup
    MPI_Group sub;
    MPI_Group_incl(current,numeric_cast<int>(ids.size()),&(ids[0]),&sub);

    // Create an MPI communicator for this group
    MPI_Comm sub_comm;
    MPI_Comm_create(mpi_comm,sub,&sub_comm);

    return new MpiComm(sub_comm,name,out,err,!makeScratch);
  }

  /// Read a multi-dimensional binary file in parallel
  /** Only read the data that my process specifically needs.

      \note This assumes that the data-file is in float and the data is
      cast to double

      \param[out] f read data
      \param[in] fn array of sizes
      \param[in] n array of subsizes
      \param[in] imin array of starts
      \param[in] fname file name
      \param[in] format Whether C or FORTRAN binary format
  */
  void MpiComm::read_3d(dVector &f,
                        const std::vector<unsigned> &fn,
                        const std::vector<unsigned> &n,
                        const std::vector<unsigned> &imin,
                        const std::string &fname,
                        const IODataFormat format) const {
    using boost::lexical_cast;
    using boost::numeric_cast;
    MPI_File fh;
    MPI_Datatype filetype=MPI_DATATYPE_NULL;
    MPI_Info info;
    MPI_Info_create(&info);
    // check to make sure that the input arrays are 3d (only 3d is
    // currently supported)
    assert( fn.size() == 3 );
    assert( n.size() == 3 );
    assert( imin.size() == 3);
    // array_of_sizes:    size of array in data file
    // array_of_subsizes: size of array needed to be read
    // array_of_starts:   where array_of_subsizes begins in data file
    // All of these sizes are in sizeof(float), NOT bytes.  These have to
    // be non-const int, hence the copy.
    int array_of_sizes[3];
    int array_of_subsizes[3];
    int array_of_starts[3];
    try {
        for(size_t i=0;i<=2;i++) {
            array_of_sizes[i] = boost::numeric_cast <int> (fn[i]);
            array_of_subsizes[i]= boost::numeric_cast <int> (n[i]);
            array_of_starts[i] = boost::numeric_cast <int> (imin[i]);
            if (0 == fn[i] || 0 == n[i]) {
              string s("MpiComm::read_3d error: size or subsize is zero\n");
              s += "  size: " + lexical_cast<string>(fn[0]);
              s += " " + lexical_cast<string>(fn[1]);
              s += " " + lexical_cast<string>(fn[2]) + "\n";
              s += "  subsize: " + lexical_cast<string>(n[0]);
              s += " " + lexical_cast<string>(n[1]);
              s += " " + lexical_cast<string>(n[2]) + "\n";
              throw DGM::exception(s);
            }
        }
    } catch(boost::numeric::positive_overflow& e) {
        std::stringstream sin;
        sin << "Overflow in read_3d: " << e.what();
        error(sin.str());
    }
#if DGM_TEST_READ_3D>=2
    cout << "fn = " << fn[0] << " " << fn[1] << " " << fn[2] << endl;
    cout << "n = " << n[0] << " " << n[1] << " " << n[2] << endl;
    cout << "imin = " << imin[0] << " " << imin[1] << " " << imin[2] << endl;
#endif
    const int ndims=3;
    // This is specific to 3D, but making a 2D version would be simple and
    // a general version not much harder.
    if (int stat = MPI_Type_create_subarray(ndims,
                                            array_of_sizes,
                                            array_of_subsizes,
                                            array_of_starts,
                                            MPI_ORDER_FORTRAN, MPI_FLOAT,
                                            &filetype))
      error("MPI_Type_create_subarray", stat);
    if (int stat = MPI_Type_commit( &filetype ))
      error("1: MPI_Type_commit", stat);
    if (!mpi_comm)
      error("2: Error in dynamic casting to get an MPI Comm.",1);
    MPI_Comm comm = mpi_comm;
#ifdef DGM_MPI_IO_HINTS
    // Try out the ROMIO Info "hints"
    MPI_Info_set(info, "cb_nodes","1");
    MPI_Info_set(info, "romio_no_indep_rw","true");
    if (int stat = MPI_File_open(comm, const_cast<char *>(fname.c_str()),
                                 MPI_MODE_RDONLY, info, &fh) ) {
      throw exception(string("MPI_File_open failed to open file " + fname));
    }
#else
    if (MPI_File_open(comm, const_cast<char *>(fname.c_str()),
                      MPI_MODE_RDONLY, MPI_INFO_NULL, &fh) ) {
      throw exception(string("MPI_File_open failed to open file " + fname));
    }
#endif
    // Fortran files have 4 bytes at the beginning of the file that must be
    // skipped, the length of one float.  If it is C, then do not skip at
    // the start.
    const int disp = (format == C_BINARY) ? 0 : 1;
    const char *native = "native";
    MPI_Barrier(comm);
    if (int stat = MPI_File_set_view(fh, disp, MPI_FLOAT, filetype,
                                     const_cast<char*>(native), info))
      error("5: MPI_File_set_view", stat);
    if ( (unsigned)f.size() != n[0]*n[1]*n[2] ) error("6: Error in sizing f");
    // make a temporary vector of floats
    CMC::Vector<float,Ordinal> fl(f.size());
    MPI_Status status;
    if (int stat = MPI_File_read_all(fh, fl.data(),
                                     numeric_cast<int>(fl.size()),
                                     MPI_FLOAT, &status))
      error("7: MPI_File_read_all",stat);
    // convert float to double
    for (Ordinal i=0; i<f.size(); i++)
      f[i]=boost::numeric_cast<dVector::value_type>(fl[i]);
    if (int stat = MPI_File_close(&fh)) error("8: MPI_File_close",stat);
    if (int stat = MPI_Type_free(&filetype)) error("9: MPI_Type_free",stat);
    if (int stat = MPI_Info_free(&info)) error("10: MPI_Info_free",stat);
  }

/// Define to make DGM use exceptions
#define DGM_USE_EXCEPTIONS

  void MpiComm::exit(const int code) const {
    //cout() << "MpiComm::exit("<<code<<")"<<std::endl;
    //cout() << "MpiComm::NumWorld = "<<NumWorld<<std::endl;
    cout() << "Shutting down MPI..." << endl;
#ifdef DGM_USE_EXCEPTIONS
    throw DGM::exception(code);
#else
    std::exit(code);
#endif
  }

  void MpiComm::abort(const int code) const {
    MPI_Abort(mpi_comm,code);
  }

  void MpiComm::error(const std::string &msg, int code) const {
    //cerr() << msg << ": " << hex << showbase << code << endl;
#ifdef DGM_USE_EXCEPTIONS
    throw DGM::exception(msg);
#else
    cerr() << msg << endl;
    MPI_Abort(mpi_comm,code);
#endif
  }

  void MpiComm::warning(const std::string &msg) const {
    cout() << msg << endl;
  }

#ifdef DGM_USE_TEUCHOS_COMM
  Teuchos::RCP< const Teuchos::Comm< int > > MpiComm::getTeuchosComm() {
    if (teuchosComm.is_null()) {
      teuchosComm =
        Teuchos::rcp(new Teuchos::MpiComm< int >
        (Teuchos::rcp(new Teuchos::OpaqueWrapper< MPI_Comm >(mpi_comm))));
    }
    return teuchosComm;
  }
#endif

} // namespace DGM

// turn off local defines
#ifdef DGM_USE_EXCEPTIONS
#undef DGM_USE_EXCEPTIONS
#endif

#ifdef DGM_MPICOMM_VERBOSE
#undef DGM_MPICOMM_VERBOSE
#endif

#endif  // DGM_MPICOMM_HPP
