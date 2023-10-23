#ifndef DGM_COMM_HPP
#define DGM_COMM_HPP

/** \file Comm.hpp
    \brief Base class declaration for the DGM communicator
    \author Scott Collis

*/

// system includes
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <csignal>
#include <string>
#include <vector>
#include <sstream>
#include <typeinfo>
#include <stdint.h>
#include <ctime>
//#include <cxxabi.h>  // This is not standard

// Trilinos includes
#ifdef DGM_USE_TEUCHOS_COMM
#include "Teuchos_Comm.hpp"
#endif

// DGM includes
#include "Types.hpp"

// This is needed to turn on underflow exceptions in IEEE math.  I do not do
// this as a matter of routine since sometimes underflow is not necessarily a
// bad thing.  However, excessive underflows can really slow down the code and
// you may want to know about this under those circumstances.  Also, I am not
// sure just how portable this is (it works on Linux for sure).
#ifdef DGM_CATCH_UNDERFLOW
#include <fenv.h>
#endif

/// Discontinuous Galerkin Method namespace
/** This namespace contains all the Namespaces, Classes, Variables and
    Functions for the DGM Toolkit for discontinuous Galerkin methods
    supporting large-scale optimization, error estimation, and
    inversion. DGM is designed so that it does not make use of any global
    namespace objects. */
namespace DGM {

  class Info;

  static const int FAILURE=-1;   ///< DGM code for failure on exit
  static const int SUCCESS= 0;   ///< DGM code for successful exit

  /// DGM exception class
  class exception : public std::exception {
    std::string message;         ///< error message
    const size_t length;         ///< max first line length
  public:
    int error_code;
    /// Construct on a string error message
    explicit exception(const std::string msg) : message(), length(60),
        error_code(FAILURE)
    {
      if (msg.size() < length)
        message = msg;
      else
        message = "\n  "+msg;
    }
    /// Construct on an integer error code
    explicit exception(const int code) : message(), length(60),
        error_code(code)
    {
      using std::string;
      using std::stringstream;
      stringstream ss;
      if (code == FAILURE) {
        ss << "caught DGM::FAILURE";
      } else if (code == SUCCESS) {
        ss << "successful termination";
      } else {
        ss << "caught unknown integer exception: " << code;
      }
      string msg=ss.str();
      if (msg.size() < length)
        message = msg;
      else
        message = "\n  "+msg;
    }
    /// Destructor
    ~exception() throw() {}
    /// Override std::exception::what()
    virtual const char *what() const throw() {
      return message.c_str();
    }
  };

  /// DGM base parallel communicator class
  class Comm {

    std::string name;            ///< Symbolic name of this Comm

  protected:

    static bool firstComm;       ///< print status only for first Comm

    std::ostream *out;           ///< Local output stream
    std::ostream *err;           ///< Local error output stream

    bool noScratch;              ///< True deactivates scratch storage
    bool keepScratch;            ///< True prevents removal of scratch storage

    mutable std::string path;    ///< Path to scratch directory
    mutable std::string scratch; ///< Scratch space directory name

    int verb;                    ///< verbosity level

  public:

    static sig_atomic_t fatal_error_in_progress;  ///< error indicator

    static Info information;             ///< DGM Info object

    static const int master=0;           ///< Rank of the master process

    typedef DGM::Shared<Comm>::Ptr Ptr;  ///< Comm pointer type
    static Ptr World;                    ///< World communicator

    enum ScratchType { NO_SCRATCH };

    /// Default constructor
    Comm() : name(), out(&std::cout), err(&std::cerr),
             noScratch(false), keepScratch(false), path(), scratch(), verb(0) {}

    /// Standard constructor
    Comm(const std::string &name_, std::ostream &out_=std::cout,
         std::ostream &err_=std::cerr) :
      name(name_), out(&out_), err(&err_), noScratch(false), keepScratch(false),
      path(), scratch(), verb(0) {}

    /// Copy constructor
    Comm(const Comm &in) : name(in.name), out(in.out), err(&std::cerr),
                           noScratch(in.noScratch), keepScratch(in.keepScratch),
                           path(in.path), scratch(in.scratch), verb(in.verb) {}
    /// Clone
    virtual Comm *Clone() const = 0;

    /// Destructor
    virtual ~Comm() {
      if (verb>3) std::cout<<"~Comm()"<<std::endl;
    }

    /// \name DGM::Comm interface
    //@{
    /// Exit execution with an error status
    virtual void exit(const int code=DGM::FAILURE) const = 0;
    /// Exit execution with a message and error status
    virtual void error(const std::string &msg,
                       const int code=DGM::FAILURE) const = 0;
    /// Output a warning message
    virtual void warning(const std::string &msg) const = 0;
    /// Exit execution with a string stream message and error status
    virtual void error(const std::stringstream &msg,
                       const int code=DGM::FAILURE) const {
      error(msg.str(),code);
    }
    /// Get verbosity level
    int verbosity() const { return verb; }
    bool no_scratch() const { return noScratch; }
    /// Abort
    virtual void abort(const int code=DGM::FAILURE) const {
      exit(code);
    }
    /// Return true if you are the master process
    virtual bool Master() const = 0;
    virtual bool Main() const { return Master(); }
    /// Blocking send
    virtual void Send(int tag, double *buf, int len, int dest) const =0;
    /// Receive
    virtual void Receive(int tag, double *buf, int len, int source) const =0;
    /// Blocking send
    virtual void Send(int tag, int *buf, int len, int dest) const =0;
    /// Receive
    virtual void Receive(int tag, int *buf, int len, int source) const =0;
    /// Nonblocking send
    virtual void iSend(int tag, double *buf, int len, int dest) const =0;
    /// Nonblocking receive
    virtual void iReceive(int tag, double *buf, int len, int source) const =0;
    /// Nonblocking send
    virtual void iSend(int tag, int *buf, int len, int dest) const =0;
    virtual void iSend(int tag, long *buf, int len, int dest) const =0;
    virtual void iSend(int tag, unsigned *buf, int len, int dest) const =0;
    virtual void iSend(int tag, long long *buf, int len, int dest) const =0;
    virtual void iSend(int tag, long unsigned *buf, int len, int dest) const =0;
    /// Nonblocking receive
    virtual void iReceive(int tag, int *buf, int len, int source) const =0;
    virtual void iReceive(int tag, long *buf, int len, int source) const =0;
    virtual void iReceive(int tag, unsigned *buf, int len, int source) const =0;
    virtual void iReceive(int tag, long long *buf, int len,
                          int source) const =0;
    virtual void iReceive(int tag, long unsigned *buf, int len,
                          int source) const =0;
    /// Wait for all active nonblocking communication
    virtual void WaitAll() const =0;
    /// Combined send and receive
    virtual void SendReceive(int stag, double *sbuf, int slen, int dest,
                             int rtag, double *rbuf, int rlen,
                             int source) const =0;
    /// Combined send and receive to the same buffer
    virtual void SendReceiveReplace(double *sbuf, int len, int dest,
                                    int stag, int source, int rtag) const =0;
    /// Setup scratch space for temporary out-of-core storage
    virtual void CreateScratch() const =0;
    /// Check file system space size
    unsigned long ScratchSize() const;
    /// Remove scratch space
    virtual void RemoveScratch() const =0;
    /// Toggle whether to remove scratch space on termination of execution
    void KeepScratch(const bool value=true) {keepScratch=value;}
    /// Return local process id or rank within this communicator
    virtual int MyPID() const = 0;
    /// Return local process id of rank as string
    std::string MyPIDstr() const;
    /// Return the total number of processes within this communicator
    virtual int NumProc()const = 0;
    /// Implements a barrier appropriate to this communicator
    virtual void Barrier() const = 0;
    /// Broadcast to all processes within this communicator
    virtual int Broadcast( double *Values, int Count=1, int Root=0 ) const = 0;
    /// Broadcast to all processes within this communicator
    virtual int Broadcast( int *Values, int Count=1, int Root=0 ) const = 0;
    /// Broadcast to all processes within this communicator
    virtual int Broadcast( unsigned int *Values, int Count=1, int Root=0 )
      const = 0;
    /// Broadcast to all processes within this communicator
    virtual int Broadcast( unsigned long *Values, int Count=1, int Root=0 )
      const = 0;
    /// Broadcast to all processes within this communicator
    virtual int Broadcast( long *Values, int Count=1, int Root=0 ) const = 0;
    /// Broadcast to all processes within this communicator
    virtual int Broadcast( unsigned long long *Values, int Count=1,
                           int Root=0 ) const = 0;
    /// Broadcast to all processes within this communicator
    virtual int Broadcast( long long *Values, int Count=1, int Root=0 )
      const = 0;
    /// Broadcast to all processes within this communicator
    virtual int Broadcast( bool *Values, int Count=1, int Root=0 )
      const = 0;
    /// Broadcast to all processes within this communicator
    virtual int Broadcast( char *Values, int Count=1, int Root=0 ) const = 0;
    /// Gather
    virtual int Gather(const unsigned *sendbuf, const int sendcount,
                       unsigned *recvbuf, const int recvcount,
                       const int root=0) const = 0;
    virtual int Gather(const int      *sendbuf, const int sendcount,
                       int      *recvbuf, const int recvcount,
                       const int root=0) const = 0;
    /// Vector gather
    virtual int GatherV(DTK::Ordinal_t *sendbuf, const size_t sendcount,
                        DTK::Ordinal_t *recvbuf, int *recvcounts,
                        int *displs, const int root=0) const = 0;

    virtual int GatherV(unsigned *sendbuf, const int sendcount,
                        unsigned *recvbuf, int *recvcounts,
                        int *displs, const int root=0) const = 0;
    /// Vector gather
    virtual int GatherV(int *sendbuf, const int sendcount,
                        int *recvbuf, int *recvcounts,
                        int *displs, const int root=0) const = 0;
    /// Scan
    virtual int Scan(const int *MyVals, int *AllVals, int Count=1) const = 0;

    /// Scan
    virtual int Scan(const unsigned long *MyVals, unsigned long *AllVals,
                     int Count=1) const = 0;
    virtual int Scan(const unsigned long long *MyVals,
                     unsigned long long *AllVals,
                     int Count=1) const = 0;

    /// simple constant all-to-all
    virtual int Alltoall(const int *sendbuf, const int sendcount,
                         int *recvbuf, const int recvcount) const =0;

    /// simple constant all-to-all
    virtual int Alltoall(const unsigned long *sendbuf, const int sendcount,
                         unsigned long *recvbuf, const int recvcount) const =0;

    /// complicated variable all-to-all
    virtual int Alltoallv(const double *sendbuf, const int *sendcount,
                          const int *senddisp, double *recvbuf,
                          const int *recvcount, const int *recvdisp) const =0;

    /// complicated variable all-to-all
    virtual int Alltoallv(const float  *sendbuf, const int *sendcount,
                          const int *senddisp, float  *recvbuf,
                          const int *recvcount, const int *recvdisp) const =0;

    /// complicated variable all-to-all
    virtual int Alltoallv(const unsigned *sendbuf, const int *sendcount,
                          const int *senddisp, unsigned *recvbuf,
                          const int *recvcount, const int *recvdisp) const =0;

    /// complicated variable all-to-all
    virtual int Alltoallv(const int *sendbuf, const int *sendcount,
                          const int *senddisp, int *recvbuf,
                          const int *recvcount, const int *recvdisp) const =0;

    /// complicated variable all-to-all
    virtual int Alltoallv(const unsigned long *sendbuf, const int *sendcount,
                          const int *senddisp, unsigned long *recvbuf,
                          const int *recvcount, const int *recvdisp) const =0;

    /// complicated variable all-to-all
    virtual int Alltoallv(const long *sendbuf,
                          const int *sendcount, const int *senddisp,
                          long *recvbuf,
                          const int *recvcount, const int *recvdisp) const =0;

    /// complicated variable all-to-all
    virtual int Alltoallv(const long long *sendbuf, const int *sendcount,
                          const int *senddisp, long long *recvbuf,
                          const int *recvcount, const int *recvdisp) const =0;

    /// complicated variable all-to-all
    virtual int Alltoallv(const unsigned long long *sendbuf,
                          const int *sendcount, const int *senddisp,
                          unsigned long long *recvbuf,
                          const int *recvcount, const int *recvdisp) const =0;

   /// Gather to all
    virtual int GatherAll( const double *MyVals, double *AllVals,
                           int Count) const =0;
    /// Gather to all
    virtual int GatherAll( const int *MyVals, int *AllVals, int Count)
      const = 0;
    virtual int GatherAll( const int *MyVals, unsigned long *AllVals,
                           int Count)
      const = 0;
    virtual int GatherAll( const unsigned long *MyVals, unsigned long *AllVals
        , int Count) const = 0;
    /// Gather to all
    virtual int GatherAll(const iVector&, const Ordinal,
                          iVector&,
                          const intVector&, const intVector&) const = 0;
    virtual int GatherAll(const dVector&, const Ordinal,
                          dVector&,
                          const intVector&, const intVector&) const = 0;

    virtual int GatherAll( const double *MyVals, int MyCount, double *AllVals,
                           int *RevCount, int *Displs) const =0;
    /// Gather to all
    virtual int GatherAll( const int *MyVals, int MyCount, int *AllVals,
                           int *RevCount, int *Displs) const =0;
    virtual int GatherAll(const long *MyVals, int SendCount,
                          long *AllVals, int *RecvCount,
                          int *Displs) const = 0;
    virtual int GatherAll(const unsigned *MyVals, int SendCount,
                          unsigned *AllVals, int *RecvCount,
                          int *Displs) const = 0;
    virtual int GatherAll(const unsigned long *MyVals, int SendCount,
                          unsigned long *AllVals, int *RecvCount,
                          int *Displs) const = 0;
    virtual int GatherAll(const unsigned long long *MyVals, int SendCount,
                          unsigned long long *AllVals, int *RecvCount,
                          int *Displs) const = 0;
    virtual int GatherAll(const long long *MyVals, int SendCount,
                          long long *AllVals, int *RecvCount,
                          int *Displs) const = 0;
    /// Gather to all
    virtual int GatherAll(const std::vector<std::string> &MyVals,
                          std::vector<std::string> &AllVals,
                          int *RevCount, int *Displs) const =0;
    /// Vector scatter
    virtual int Scatterv(double *AllVals, int* Sendlen, int *Displs,
                        double *MyVals, int RevCount, int root) const =0;
    /// Sum all double
    virtual int SumAll(const double *PartialSums, double *GlobalSums,
                      int Count) const =0;
    /// Sum all int
    virtual int SumAll(const int *PartialSums, int *GlobalSums,
                       int Count) const =0;
    virtual int SumAll(const long *PartialSums, long *GlobalSums,
                       int Count) const =0;
    /// Sum all unsigned
    virtual int SumAll(const unsigned *PartialSums, unsigned *GlobalSums,
                       int Count) const =0;
    virtual int SumAll(const long long *PartialSums,
                       long long *GlobalSums,
                       int Count) const =0;
    /// Sum all unsigned long
    virtual int SumAll(const unsigned long *PartialSums,
                       unsigned long *GlobalSums,
                       int Count) const =0;
    /// Sum all unsigned long
    virtual int SumAll(const unsigned long long *PartialSums,
                       unsigned long long *GlobalSums,
                       int Count) const =0;

    virtual long int SumAll(const long int PartialSums) const =0;
    /// Sum all unsigned
    virtual unsigned SumAll(const unsigned PartialSums) const =0;
    /// Sum all unsigned long
    virtual unsigned long SumAll(const unsigned long PartialSums) const =0;
    /// Sum all unsigned long long
    virtual unsigned long long SumAll(const unsigned long long PartialSums)
      const =0;

    // Max on p0 only
    virtual int Max(const int *PartialMaxs, int *GlobalMaxs,
                    int Count) const = 0;
    virtual int Max(const long *PartialMaxs, long *GlobalMaxs,
                    int Count) const = 0;
    virtual int Max(const unsigned *PartialMaxs, unsigned *GlobalMaxs,
                    int Count) const = 0;
    virtual int Max(const long long *PartialMaxs, long long *GlobalMaxs,
                    int Count) const = 0;
    virtual int Max(const long unsigned *PartialMaxs, long unsigned *GlobalMaxs,
                    int Count) const = 0;

    /// Max all double
    virtual int MaxAll(const double *PartialMaxs, double *GlobalMaxs,
                       int Count) const =0;
    /// Max all int
    virtual int MaxAll(const int *PartialMaxs, int *GlobalMaxs,
                       int Count) const =0;
    virtual int MaxAll(const long int *PartialMaxs,
                       long int *GlobalMaxs, int Count) const =0;
    /// Max all unsigned int
    virtual int MaxAll(const unsigned int *PartialMaxs,
                       unsigned int *GlobalMaxs, int Count) const =0;
    /// Max all unsigned long
    virtual int MaxAll(const long long *PartialMaxs,
                       long long *GlobalMaxs, int Count) const =0;
    virtual int MaxAll(const unsigned long *PartialMaxs,
                       unsigned long *GlobalMaxs, int Count) const =0;
    /// Max all unsigned long long
    virtual int MaxAll(const unsigned long long *PartialMaxs,
                       unsigned long long *GlobalMaxs, int Count) const =0;
    /// Max all unsigned int
    virtual int MaxAll(unsigned &GlobalMaxs) const =0;

    /// Max all int64_t
    virtual int MaxAll(int64_t &GlobalMaxs) const =0;

    /// Max all uint64_t
    virtual int MaxAll(uint64_t &GlobalMaxs) const =0;

    /// Min all double
    virtual int MinAll(const double *PartialMins, double *GlobalMins,
                       int Count) const =0;
    /// Min all int
    virtual int MinAll(const int *PartialMins, int *GlobalMins,
                       int Count) const =0;
    /// Min all unsigned int
    virtual int MinAll(const unsigned *PartialMins, unsigned *GlobalMins,
                       int Count) const =0;

    /// Min all long long
    virtual int MinAll(const long long *PartialMins,
                       long long *GlobalMins,
                       int Count) const =0;
    /// Min all unsigned long
    virtual int MinAll(const unsigned long *PartialMins,
                       unsigned long *GlobalMins,
                       int Count) const =0;
    virtual int MinAll(const unsigned long long *PartialMins,
                       unsigned long long *GlobalMins,
                       int Count) const =0;

    /// Min all unsigned long
    virtual int MinAll( int &GlobalMins) const=0;
    virtual int MinAll( unsigned int &GlobalMins) const=0;
    virtual int MinAll( long long &GlobalMins) const=0;
    virtual int MinAll( unsigned long &GlobalMins) const=0;
    virtual int MinAll( unsigned long long &GlobalMins) const=0;
    virtual int MinLocAll( int &GlobalMins) const=0;
    virtual int MinLocAll( unsigned int &GlobalMins) const=0;
    virtual int MinLocAll( unsigned long &GlobalMins) const=0;
    virtual int MinLocAll( unsigned long long &GlobalMins) const=0;

    /// MaxLoc all double int
    virtual int MaxLocAll( const double *PartialMaxs, const int *PartialLocs,
                           double *GlobalMaxs, int *GlobalLocs,
                           int Count) const=0;
    /// MinLoc all double int
    virtual int MinLocAll( const double *PartialMins, const int *PartialLocs,
                           double *GlobalMins, int *GlobalLocs,
                           int Count) const=0;

    /// Computes an append to a file
    virtual void append_data(const std::string& fname,
                             const std::string& data) const = 0;

    /// Returns the scratch space directory and name
    virtual const std::string& Scratch() const { return scratch; }
    /// Returns the symbolic name of this communicator
    virtual const std::string& Name() const {return name;}
    /// Returns the scratch directory path
    virtual const std::string& Path() const {return path;}

    /// Provides a character output stream
    virtual std::ostream& cout() const {return *out;}
    /// Provides a character error stream
    virtual std::ostream& cerr() const {return *err;}

    /// Creates a new group based on the given ids and returns the communicator
    virtual Comm* CreateSubComm(std::vector <int>& ids,
                                const std::string& name="",
                                std::ostream& out=std::cout,
                                std::ostream& err=std::cerr,
                                const bool makeScratch=false) const {
      error("DGM::Comm:  Cannot create a sub-communicator in this mode!");
      return 0;
    }
    virtual void CommFree() = 0;

#ifdef DGM_USE_TEUCHOS_COMM
    /// Return an equivalent Teuchos communicator
    virtual Teuchos::RCP< const Teuchos::Comm< int > > getTeuchosComm() = 0;
#endif
    /// Get the time from master and broadcast
    std::string dateTime() const {
      const int buflen = 256;
      char now[buflen] = "Time is not available";
      if (Master()) {
        time_t tp = ::time(0);
        strftime(now,buflen,"%a %b %d %Y at %H:%M:%S", localtime(&tp));
      }
      Broadcast(now, buflen);
      return now;
    }
    //@}

    /// \name Posix signal handling
    //@{
    /// Catches interupts
    static void Interupt();

    /// Interrupt handler
    static void Handler(int);
    //@}

    /// \name I/O routines on generic data
    //@{
    enum IODataFormat {
      ASCII,              ///< ASCII characters
      FORTRAN_BINARY,     ///< FORTRAN binary with 4byte record delimiters
      C_BINARY            ///< Flat C-binary with no record delimiters
    };

    /// Read a multi-dimensional binary file
    virtual void read_3d( dVector &f,
                          const std::vector<unsigned> &fn,
                          const std::vector<unsigned> &n,
                          const std::vector<unsigned> &imin,
                          const std::string &fname,
                          const IODataFormat format) const {
      error("DGM::Comm: read_3d not implemented!");
    }
    //@}
  };

  //===========================================================================
  //                            Implementation
  //===========================================================================

  /// \name Utilities
  //@{

  /// Simple DGM error message at the Comm::World level
  /** This provides an easy way to generate an error and exit from the code
      at the DGM::Comm::World level. */
  inline void error(std::string msg, int code=DGM::FAILURE) {
    DGM::Comm::World->error(msg,code);
  }

  /// Simple DGM error message at the Comm::World level
  /** This provides an easy way to generate an error and exit from the code
      at the DGM::Comm::World level. */
  inline void error(std::stringstream &msg, int code=DGM::FAILURE) {
    DGM::Comm::World->error(msg,code);
  }

#ifdef HAVE_CXA_DEMANGLE
  /// Return a demangled typeid.name() if demangling is supported
  /** GCC does support C++ name demangling through the abi. */
  inline const std::string demangle(const char *name) {
    using std::string;
    int size=1024;
    char buf[size];
    int status;
    char *res = abi::__cxa_demangle(name,buf,&size,&status);
    string result(res);
    return result ;
  }
#else
  /// Return a demangled typeid.name() if demangling is supported
  /** The default implementation just returns the name as is. */
  inline const std::string demangle(const char *name) {
    std::string result(name);
    return result;
  }
#endif

  //@}

} // namespace DGM

//===========================================================================
//                                Macros
//===========================================================================

#ifdef DGM_NO_PRETTY_FUNCTION

/// Macro used to stub in a unimplemented method
#define DGM_UNDEFINED DGM::Comm::World->cerr()<<demangle(typeid(*this).name())\
<<": Undefined function."<<std::endl;DGM::Comm::World->exit(DGM::FAILURE);

/// Macro use to make methods noisy
#define DGM_NOISY DGM::Comm::World->cout()<<demangle(typeid(*this).name())\
<<std::endl;

#else

/// Macro used to stub in a unimplemented method (might not be portable)
#define DGM_UNDEFINED DGM::Comm::World->cerr()<<\
"Undefined function:  "<<__PRETTY_FUNCTION__<<\
std::endl;throw DGM::exception("Undefined function");

/// Macro use to make methods noisy
#define DGM_NOISY DGM::Comm::World->cout()<<__PRETTY_FUNCTION__<<std::endl;

#endif  // DGM_NO_PRETTY_FUNCTION

#endif  // DGM_COMM_HPP
