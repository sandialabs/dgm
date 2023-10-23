#ifndef DGM_SERIALCOMM_HPP
#define DGM_SERIALCOMM_HPP

/** \file SerialComm.hpp
    \brief Serial implementation of the DGM communicator
    \author Scott Collis
*/

// system includes
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <csignal>
#include <sys/wait.h>

// DGM includes
#include "Comm.hpp"
#include "Info.hpp"

#ifdef DGM_USE_TEUCHOS_COMM
#include "Teuchos_RCP.hpp"
#include "Teuchos_DefaultSerialComm.hpp"
#endif

// boost includes
#ifdef DGM_USE_BOOST_FS
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#endif

#ifdef DGM_DOXYGEN
/// Print out detailed Serial omm information
#define DGM_SERIALCOMM_VERBOSE
/// Define if the system call is not supported
#define DGM_NO_SYSTEM
#endif

namespace DGM {

  /// DGM Serial communicator
  class SerialComm : public Comm {

  protected:

#ifdef DGM_USE_TEUCHOS_COMM
    /// Equivalent Teuchos communicator
    Teuchos::RCP< const Teuchos::Comm< int > > teuchosComm;
#endif

  public:

    /// Constructor
    inline explicit
    SerialComm(const std::string & = "World",
               std::ostream & = std::cout,
               std::ostream & = std::cerr);
    /// Constructor with option to not built a scratch directory
    inline explicit
    SerialComm(const std::string &, const ScratchType,
               std::ostream & = std::cout,
               std::ostream & = std::cerr);
    inline SerialComm(const SerialComm &);
    inline Comm * Clone() const { return new SerialComm(*this); }

    /// Destructor
    inline ~SerialComm();

    virtual void CommFree() {}; 

    /// \name DGM::Comm Interface
    //@{
    inline void exit(const int code=DGM::FAILURE) const;
    inline void error(const std::string &msg, int code=DGM::FAILURE) const;
    inline void warning(const std::string &msg) const;

    inline bool Master() const { return true;}

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
    inline int MyPID() const { return 0; }
    inline int NumProc() const { return 1; }

    inline void Barrier() const;

    inline int Broadcast(double *Values, int Count=1, int Root=0 ) const;
    inline int Broadcast(int *Values, int Count=1, int Root=0 ) const;
    inline int Broadcast(bool *Values, int Count=1, int Root=0 ) const;
    inline int Broadcast(unsigned int *Values, int Count=1, int Root=0 ) const;
    inline int Broadcast(unsigned long *Values, int Count=1,
                         int Root=0 ) const;
    inline int Broadcast(long *Values, int Count=1, int Root=0 ) const;
    inline int Broadcast(unsigned long long *Values, int Count=1,
                         int Root=0 ) const;
    inline int Broadcast(long long *Values, int Count=1, int Root=0 ) const;
    inline int Broadcast(char *Values, int Count=1, int Root=0 ) const;

    inline int Gather(const unsigned *sendbuf, const int sendcount,
                      unsigned *recvbuf, const int recvcount,
                      const int root) const;
    inline int Gather(const int      *sendbuf, const int sendcount,
                      int      *recvbuf, const int recvcount,
                      const int root) const;

    inline int GatherV(DTK::Ordinal_t *sendbuf, const size_t sendcount,
                       DTK::Ordinal_t *recvbuf, int *recvcounts,
                       int *displs, const int root=0) const;
    inline int GatherV(unsigned *sendbuf, const int sendcount,
                       unsigned *recvbuf, int *recvcounts,
                       int *displs, const int root) const;
    inline int GatherV(int *sendbuf, const int sendcount,
                       int *recvbuf, int *recvcounts,
                       int *displs, const int root) const;

    inline int Scan( const int *MyVals, int *AllVals, int Count) const ;

    inline int Scan( const unsigned long *MyVals, unsigned long *AllVals,
                     int Count) const ;
    inline int Scan( const unsigned long long *MyVals, unsigned long long *AllVals,
                     int Count) const ;

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

    inline int Alltoallv(const long *sendbuf,
                         const int *sendcount, const int *senddisp,
                         long *recvbuf,
                         const int *recvcount, const int *recvdisp) const;

    inline int Alltoallv(const long long *sendbuf,
                         const int *sendcount, const int *senddisp,
                         long long *recvbuf,
                         const int *recvcount, const int *recvdisp) const;

    inline int Alltoallv(const unsigned long long *sendbuf,
                         const int *sendcount, const int *senddisp,
                         unsigned long long *recvbuf,
                         const int *recvcount, const int *recvdisp) const;

    inline int GatherAll(const double *MyVals, double *AllVals,
                         int Count) const ;
    inline int GatherAll(const int *MyVals, int *AllVals, int Count) const ;
    inline int GatherAll(const int *MyVals, unsigned long *AllVals, int Count) const;
    inline int GatherAll(const unsigned long *MyVals,
                         unsigned long *AllVals, int Count) const;
    inline int GatherAll(const unsigned long long *MyVals,
                         unsigned long long *AllVals, int Count) const;
    inline int GatherAll(const iVector&, const Ordinal,
                         iVector&,
                         const intVector&, const intVector&) const;
    inline int GatherAll(const dVector&, const Ordinal,
                         dVector&,
                         const intVector&, const intVector&) const;
    inline int GatherAll(const double *MyVals, int MyCount, double *AllVals,
                         int *RevCount, int *Displs) const ;
    inline int GatherAll(const int *MyVals, int MyCount, int *AllVals,
                         int *RevCount, int *Displs) const ;
    inline int GatherAll(const long *MyVals, int SendCount,
                         long *AllVals, int *RecvCount,
                         int *Displs) const;
    inline int GatherAll(const unsigned *MyVals, int SendCount,
                         unsigned *AllVals, int *RecvCount,
                         int *Displs) const;
    inline int GatherAll(const unsigned long *MyVals, int SendCount,
                         unsigned long *AllVals, int *RecvCount,
                         int *Displs) const;
    inline int GatherAll(const unsigned long long *MyVals, int SendCount,
                         unsigned long long *AllVals, int *RecvCount,
                         int *Displs) const;
    inline int GatherAll(const long long *MyVals, int SendCount,
                         long long *AllVals, int *RecvCount,
                         int *Displs) const;

    inline int GatherAll(const std::vector<std::string> &MyVals,
                         std::vector<std::string> &AllVals,
                         int *RevCount, int *Displs) const;

    inline int Scatterv(double *AllVals, int* Sendlen, int *Displs,
                        double *MyVals, int RevCount, int root) const;

    inline int SumAll(const double *PartialSums, double *GlobalSums,
                      int Count) const;
    inline int SumAll(const int *PartialSums, int *GlobalSums,
                      int Count) const ;
    inline int SumAll(const long *PartialSums, long *GlobalSums,
                      int Count) const ;
    inline int SumAll(const unsigned *PartialSums, unsigned *GlobalSums,
                      int Count) const ;
    inline int SumAll(const long long *PartialSums,
                      long long *GlobalSums,
                      int Count) const ;
    inline int SumAll(const unsigned long *PartialSums,
                      unsigned long *GlobalSums,
                      int Count) const ;
    inline int SumAll(const unsigned long long *PartialSums,
                      unsigned long long *GlobalSums,
                      int Count) const ;

    inline long int SumAll(const long int PartialSum) const;
    inline unsigned SumAll(const unsigned PartialSum) const;
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
                       int Count) const ;
    inline int MaxAll( const int *PartialMaxs, int *GlobalMaxs,
                       int Count) const ;
    inline int MaxAll( const long int *PartialMaxs,
                       long int *GlobalMaxs,
                       int Count) const ;
    inline int MaxAll( const unsigned int *PartialMaxs,
                       unsigned int *GlobalMaxs,
                       int Count) const ;
    inline int MaxAll( const long long *PartialMaxs,
                       long long *GlobalMaxs,
                       int Count) const ;
    inline int MaxAll( const unsigned long *PartialMaxs,
                       unsigned long *GlobalMaxs,
                       int Count) const ;
    inline int MaxAll( const unsigned long long *PartialMaxs,
                       unsigned long long *GlobalMaxs,
                       int Count) const ;
    inline int MaxAll( unsigned &GlobalMaxs) const ;
    inline int MaxAll( int64_t &GlobalMaxs) const ;
    inline int MaxAll( uint64_t &GlobalMaxs) const ;

    inline int MinAll( const double *PartialMins, double *GlobalMins,
                       int Count) const ;
    inline int MinAll( const int *PartialMins, int *GlobalMins,
                       int Count) const ;
    inline int MinAll( const unsigned *PartialMins, unsigned *GlobalMins,
                       int Count) const ;
    inline int MinAll(const long long *PartialMins,
                      long long *GlobalMins,
                      int Count) const ;
    inline int MinAll(const unsigned long *PartialMins,
                      unsigned long *GlobalMins,
                      int Count) const ;
    inline int MinAll(const unsigned long long *PartialMins,
                      unsigned long long *GlobalMins,
                      int Count) const ;

    inline int MinAll   ( int                &GlobalMins) const ;
    inline int MinAll   ( unsigned int       &GlobalMins) const ;
    inline int MinAll   ( long long          &GlobalMins) const ;
    inline int MinAll   ( unsigned long      &GlobalMins) const ;
    inline int MinAll   ( unsigned long long &GlobalMins) const ;
    inline int MinLocAll( int                &GlobalMins) const ;
    inline int MinLocAll( unsigned int       &GlobalMins) const ;
    inline int MinLocAll( unsigned long      &GlobalMins) const ;
    inline int MinLocAll( unsigned long long &GlobalMins) const ;

    inline int MaxLocAll( const double *PartialMaxs, const int *PartialLocs,
                          double *GlobalMaxs, int *GlobalLocs,
                          int Count) const;
    inline int MinLocAll( const double *PartialMins, const int *PartialLocs,
                          double *GlobalMins, int *GlobalLocs,
                          int Count) const;

    inline void append_data(const std::string& fname,
                            const std::string& data) const;

#ifdef DGM_USE_TEUCHOS_COMM
    inline Teuchos::RCP< const Teuchos::Comm< int > > getTeuchosComm();
#endif
    //@}
  };

  //===========================================================================
  //                            Implementation
  //===========================================================================

  /// Constructor
  SerialComm::SerialComm(const std::string &name_, std::ostream &out_,
                         std::ostream &err_ ) : Comm(name_, out_, err_ ) {
    {
      const char *tmp = getenv("DGM_VERBOSE");
      if (tmp != NULL) verb = atoi(tmp);
      if (verb>4) cout() << "DGM_VERBOSE = " << verb << std::endl;
    }
    {
      const char *tmp = getenv("DGM_NO_SCRATCH");
      if (tmp != NULL) noScratch = true;
      if (verb>4) cout() << "DGM_NO_SCRATCH = " << noScratch << std::endl;
    }
    CreateScratch();
    {
      const char *tmp = getenv("DGM_KEEP_SCRATCH");
      if (tmp != NULL) keepScratch = true;
      if (verb>4) cout() << "DGM_KEEP_SCRATCH = " << keepScratch << std::endl;
    }
    if (verb>3)
      cout()<<Name()<<" running in serial."<<std::endl;
    if (firstComm) {
      DGM::Comm::information.banner(*out);
      firstComm=false;
    }
  }

  /// Constructor
  SerialComm::SerialComm(const std::string &name_, const Comm::ScratchType st,
                         std::ostream &out_, std::ostream &err_ )
    : Comm(name_, out_, err_ )
  {
    {
      const char *tmp = getenv("DGM_VERBOSE");
      if (tmp != NULL) verb = atoi(tmp);
      if (verb>3) cout() << "DGM_VERBOSE = " << verb << std::endl;
    }
    {
      const char *tmp = getenv("DGM_NO_SCRATCH");
      if (tmp != NULL) noScratch = true;
      // override the environment
      if (st == Comm::NO_SCRATCH) noScratch = true;
      if (verb>3) cout() << "DGM_NO_SCRATCH = " << noScratch << std::endl;
    }
    CreateScratch();
    {
      const char *tmp = getenv("DGM_KEEP_SCRATCH");
      if (tmp != NULL) keepScratch = true;
      if (verb>3) cout() << "DGM_KEEP_SCRATCH = " << keepScratch << std::endl;
    }
    if (verb>2)
      cout()<<Name()<<" running in serial with "
                    <<(noScratch?"no scratch.":"with scratch.")<<std::endl;
    if (firstComm) {
      DGM::Comm::information.banner(*out);
      firstComm=false;
    }
  }

  /// Copy constructor
  SerialComm::SerialComm(const SerialComm &in) : Comm(in) {}

  /// Destructor
  SerialComm::~SerialComm() {
    if (verb>3) std::cout << "~SerialComm() for " << Name()
                          << std::endl;
#ifndef DGM_SAVE_SCRATCH
    RemoveScratch();
#endif
  }

  void SerialComm::Send(int tag, double *buf, int len, int dest) const {}

  void SerialComm::Receive(int tag, double *buf, int len, int source) const {}

  void SerialComm::Send(int tag, int *buf, int len, int dest) const {}

  void SerialComm::Receive(int tag, int *buf, int len, int source) const {}

  void SerialComm::iSend(int tag, double *buf, int len, int dest) const {}

  void SerialComm::iReceive(int tag, double *buf, int len, int source) const {}

  void SerialComm::iSend(int tag, int *buf, int len, int dest) const {}
  void SerialComm::iSend(int tag, long *buf, int len, int dest) const {}
  void SerialComm::iSend(int tag, unsigned *buf, int len, int dest) const {}
  void SerialComm::iSend(int tag, long long *buf, int len, int dest) const {}
  void SerialComm::iSend(int tag, long unsigned *buf, int len, int dest) const {}

  void SerialComm::iReceive(int tag, int *buf, int len, int source) const {}
  void SerialComm::iReceive(int tag, long *buf, int len, int source) const {}
  void SerialComm::iReceive(int tag, unsigned *buf, int len, int source) const {}
  void SerialComm::iReceive(int tag, long long *buf, int len, int source) const {}
  void SerialComm::iReceive(int tag, long unsigned *buf, int len, int source) const {}

  void SerialComm::WaitAll() const {}

  void SerialComm::SendReceive(int stag, double *sbuf, int slen, int dest,
                               int rtag, double *rbuf,
                               int rlen, int source) const {}

  void SerialComm::SendReceiveReplace(double *buf, int len, int dest,
                                      int stag, int source, int rtag) const {}

  /// Make scratch file space
  void SerialComm::CreateScratch() const {
    if (noScratch) return;
    std::string dir, user;
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
    if ( u != NULL) 
      user = string(u);
    else
      user = "user";
    char node[80];
    sprintf(node,"%d",MyPID());
#ifdef DGM_NO_MKDTEMP
    std::string command ="/bin/mkdir -m u=rwx,go-rwx ";
    scratch = dir + "/" + "dgm-" + user + "_" + node + "/";
    command = command + scratch;
    //std::cout<<"Making system call: "<<command<<std::endl;
    if ( int status=system(command.c_str()) ) {
      if ( WEXITSTATUS(status) != 1 ) {  // status==1 is a warning for mkdir
        cerr() << "Error making scratch space." << std::endl;
        exit(DGM::FAILURE);
      }
    }
    //std::cout<<"Finished system call: "<<command<<std::endl;
#else
    scratch = dir + "/" + "dgm-" + user + "-" + node + "-XXXXXX";
    char dirname[512]; strncpy(dirname,scratch.c_str(),511);
    if (mkdtemp(dirname) == NULL) {
      cerr() << "Error creating scratch directory: " << dirname<<std::endl;
      exit(DGM::FAILURE);
    }
    scratch = dirname;
    scratch += "/";
#endif
    path = dir;  // save the path to the scratch directory
#ifdef DGM_SERIALCOMM_VERBOSE
    std::cout << "Created scratch directory " << scratch << std::endl;
#endif
  }

  /// Used to remove scratch file space
  void SerialComm::RemoveScratch() const {
    if (noScratch) return;
#ifdef DGM_SERIALCOMM_VERBOSE
    cout()<<"SerialComm::RemoveScratch(): "<<scratch<<std::endl;
#endif
    if (keepScratch) {
      //std::cout<<"Moving scratch..."<<std::endl;
      std::string command = "/bin/mv ";
      char node[80];
      sprintf(node,"%d",MyPID());
      // command = command + scratch + " " + path + "/obj-" + node;
      command = command + scratch + " " + path + "/obj";
#ifdef DGM_SERIALCOMM_VERBOSE
      std::cout << command << std::endl;
#endif
#if !defined(DGM_NO_SYSTEM)
      //std::cout << "executing system command" << std::endl;
      if (int status=system(command.c_str()))
        cerr()<<"SerialComm:: Non-zero status = "<<status
              <<" in removing scratch space."<<std::endl;
#endif
    } else {
      std::string command ="/bin/rm -rf ";  // make sure that remove is forced
      command = command + scratch;
#ifdef DGM_SERIALCOMM_VERBOSE
      std::cout << "Removing scratch directory " << scratch << std::endl;
#endif
#ifdef DGM_USE_BOOST_FS
      try {
        boost::filesystem::path p(scratch);
        //std::cout << "Boost remove_all("<<p<<")"<<std::endl;
        boost::filesystem::remove_all(p);
      }
      catch (boost::filesystem::filesystem_error &e) {
        std::cout << "Boost filesystem error " << e.what()<<std::endl;
        throw DGM::exception("Boost filesystem error");
      }
#else
#if !defined(DGM_NO_SYSTEM)
      if ( int status=system(command.c_str()) )
        cerr()<<"SerialComm:: Non-zero status = "<<status
              <<" in removing scratch space."<<std::endl;
#endif
#endif
    }
    scratch="";
    //cout()<<"SerialComm::RemoveScratch() completed"<<std::endl;
  }

  void SerialComm::Barrier() const {
  }

  int SerialComm::Broadcast(double *Values, int Count, int Root) const {
    return 0;
  }

  int SerialComm::Broadcast(int *Values, int Count, int Root) const {
    return 0;
  }

  int SerialComm::Broadcast(bool *Values, int Count, int Root) const {
    return 0;
  }

  int SerialComm::Broadcast(unsigned int *Values, int Count, int Root) const {
    return 0;
  }

  int SerialComm::Broadcast(unsigned long *Values, int Count, int Root) const {
    return 0;
  }

  int SerialComm::Broadcast(long *Values, int Count, int Root) const {
    return 0;
  }

  int SerialComm::Broadcast(unsigned long long *Values, int Count,
                            int Root) const {
    return 0;
  }

  int SerialComm::Broadcast(long long *Values, int Count, int Root) const {
    return 0;
  }

  int SerialComm::Broadcast(char *Values, int Count, int Root) const {
    return 0;
  }

  int SerialComm::Gather(const unsigned  *sendbuf,
                         const int  sendcount,
                         unsigned  *recvbuf,
                         const int  recvcount,
                         const int  root) const

  {
    using std::copy;
    using std::min;
    copy(sendbuf, sendbuf+min(sendcount,recvcount), recvbuf);
    return 0;
  }

  int SerialComm::Gather(const int *sendbuf,
                         const int  sendcount,
                         int       *recvbuf,
                         const int  recvcount,
                         const int  root) const

  {
    using std::copy;
    using std::min;
    copy(sendbuf, sendbuf+min(sendcount,recvcount), recvbuf);
    return 0;
  }

  int SerialComm::GatherV(DTK::Ordinal_t *sendbuf,
                          const size_t sendcount,
                          DTK::Ordinal_t *recvbuf,
                          int       *recvcounts,
                          int       *displs,
                          const int  root) const
  {
    for (size_t i=0; i<sendcount && i<size_t(*recvcounts); ++i)
      recvbuf[*displs+i] = sendbuf[i];
    return 0;
  }

  int SerialComm::GatherV(unsigned  *sendbuf,
                          const int  sendcount,
                          unsigned  *recvbuf,
                          int       *recvcounts,
                          int       *displs,
                          const int  root) const
  {
    for (int i=0; i<sendcount && i<*recvcounts; ++i)
      recvbuf[*displs+i] = sendbuf[i];
    return 0;
  }

  int SerialComm::GatherV(int *sendbuf,
                          const int sendcount,
                          int *recvbuf,
                          int *recvcounts,
                          int *displs,
                          const int root) const
  {
    for (int i=0; i<sendcount && i<*recvcounts; ++i)
      recvbuf[*displs+i] = sendbuf[i];
    return 0;
  }

  int SerialComm::Scan( const int *MyVals, int *AllVals, int Count) const {
    using std::copy;
    copy(MyVals, MyVals+Count, AllVals);
    return 0;
  }

  int SerialComm::Scan( const unsigned long *MyVals, unsigned long *AllVals,
                        int Count) const {
    using std::copy;
    copy(MyVals, MyVals+Count, AllVals);
    return 0;
  }
  int SerialComm::Scan( const unsigned long long *MyVals, unsigned long long *AllVals,
                        int Count) const {
    using std::copy;
    copy(MyVals, MyVals+Count, AllVals);
    return 0;
  }
  int SerialComm::Alltoall(const int *sendbuf, const int sendcount,
                           int *recvbuf, const int )const{
    using std::copy;
    copy(sendbuf, sendbuf+sendcount, recvbuf);
    return 0;
  }

  int SerialComm::Alltoall(const unsigned long *sendbuf, const int sendcount,
                           unsigned long *recvbuf, const int )const{
    using std::copy;
    copy(sendbuf, sendbuf+sendcount, recvbuf);
    return 0;
  }

  int SerialComm::Alltoallv(const double *sendbuf, const int *sendcount,
                            const int *senddisp, double *recvbuf,
                            const int *recvcount, const int *recvdisp)const{
    for (int i=0; i<*sendcount; ++i)recvbuf[i+*senddisp]=sendbuf[i+*recvdisp];
    return 0;
  }

  int SerialComm::Alltoallv(const float  *sendbuf, const int *sendcount,
                            const int *senddisp, float  *recvbuf,
                            const int *recvcount, const int *recvdisp)const{
    for (int i=0; i<*sendcount; ++i)recvbuf[i+*senddisp]=sendbuf[i+*recvdisp];
    return 0;
  }

  int SerialComm::Alltoallv(const unsigned *sendbuf, const int *sendcount,
                            const int *senddisp, unsigned *recvbuf,
                            const int *recvcount, const int *recvdisp)const{
    for (int i=0; i<*sendcount; ++i)recvbuf[i+*senddisp]=sendbuf[i+*recvdisp];
    return 0;
  }

  int SerialComm::Alltoallv(const int *sendbuf, const int *sendcount,
                            const int *senddisp, int *recvbuf,
                            const int *recvcount, const int *recvdisp) const {
    for (int i=0; i<*sendcount; ++i)recvbuf[i+*senddisp]=sendbuf[i+*recvdisp];
    return 0;
  }

  int SerialComm::Alltoallv(const unsigned long *sendbuf, const int *sendcount,
                            const int *senddisp,
                            unsigned long *recvbuf, const int *recvcount,
                            const int *recvdisp) const {
    for (int i=0; i<*sendcount; ++i)recvbuf[i+*senddisp]=sendbuf[i+*recvdisp];
    return 0;
  }

  int SerialComm::Alltoallv(const long long *sendbuf, const int *sendcount,
                            const int *senddisp,
                            long long *recvbuf, const int *recvcount,
                            const int *recvdisp) const {
    for (int i=0; i<*sendcount; ++i)recvbuf[i+*senddisp]=sendbuf[i+*recvdisp];
    return 0;
  }

  int SerialComm::Alltoallv(const long *sendbuf,
                            const int *sendcount, const int *senddisp,
                            long *recvbuf,
                            const int *recvcount, const int *recvdisp) const {
    for (int i=0; i<*sendcount; ++i)recvbuf[i+*senddisp]=sendbuf[i+*recvdisp];
    return 0;
  }

  int SerialComm::Alltoallv(const unsigned long long *sendbuf,
                            const int *sendcount, const int *senddisp,
                            unsigned long long *recvbuf,
                            const int *recvcount, const int *recvdisp) const {
    for (int i=0; i<*sendcount; ++i)recvbuf[i+*senddisp]=sendbuf[i+*recvdisp];
    return 0;
  }

  int SerialComm::GatherAll(const double *MyVals, double *AllVals,
                            int Count) const  {
    using std::copy;
    copy(MyVals, MyVals+Count, AllVals);
    return 0;
  }

  int SerialComm::GatherAll(const int *MyVals, int *AllVals, int Count) const {
    using std::copy;
    copy(MyVals, MyVals+Count, AllVals);
    return 0;
  }

  int SerialComm::GatherAll(const int *MyVals, unsigned long *AllVals,
      int Count) const
  {
    using std::copy;
    copy(MyVals, MyVals+Count, AllVals);
    return 0;
  }

  int SerialComm::GatherAll(const unsigned long *MyVals, unsigned long *AllVals,
                            int Count) const
  {
    using std::copy;
    copy(MyVals, MyVals+Count, AllVals);
    return 0;
  }
  int SerialComm::GatherAll(const unsigned long long *MyVals, unsigned long long *AllVals,
                            int Count) const
  {
    using std::copy;
    copy(MyVals, MyVals+Count, AllVals);
    return 0;
  }

  int SerialComm::GatherAll( const double *MyVals, int SendCount,
                             double *AllVals, int *RevCount,
                             int *Displs) const {
    using std::copy;
    copy(MyVals, MyVals+SendCount, &AllVals[Displs[0]]);
    return 0;
  }

  int SerialComm::GatherAll(const iVector&MyVals, const Ordinal SendCount,
                                  iVector&AllVals,
                            const intVector&, const intVector&Displs) const {
    using std::copy;
    copy(MyVals.ptr(), MyVals.ptr()+SendCount,
        &AllVals[static_cast<intVector::size_type>(Displs[0])]);
    return 0;
  }
  int SerialComm::GatherAll(const dVector&MyVals, const Ordinal SendCount,
                                  dVector&AllVals,
                            const intVector&, const intVector&Displs) const {
    using std::copy;
    copy(MyVals.ptr(), MyVals.ptr()+SendCount,
       &AllVals[static_cast<intVector::size_type>(Displs[0])]);
    return 0;
  }
  int SerialComm::GatherAll( const int *MyVals, int SendCount, int *AllVals,
                             int *RevCount, int *Displs) const {
    using std::copy;
    copy(MyVals, MyVals+SendCount, &AllVals[Displs[0]]);
    return 0;
  }

  int SerialComm::GatherAll(const long *MyVals, int SendCount,
    long *AllVals, int *RecvCount, int *Displs) const {
    using std::copy;
    copy(MyVals, MyVals+SendCount, &AllVals[Displs[0]]);
    return 0;
  }
  int SerialComm::GatherAll(const unsigned *MyVals, int SendCount,
    unsigned *AllVals, int *RecvCount, int *Displs) const {
    using std::copy;
    copy(MyVals, MyVals+SendCount, &AllVals[Displs[0]]);
    return 0;
  }
  int SerialComm::GatherAll(const unsigned long *MyVals, int SendCount,
    unsigned long *AllVals, int *RecvCount, int *Displs) const {
    using std::copy;
    copy(MyVals, MyVals+SendCount, &AllVals[Displs[0]]);
    return 0;
  }

  int SerialComm::GatherAll(const unsigned long long *MyVals, int SendCount,
    unsigned long long *AllVals, int *RecvCount, int *Displs) const {
    using std::copy;
    copy(MyVals, MyVals+SendCount, &AllVals[Displs[0]]);
    return 0;
  }
  int SerialComm::GatherAll(const long long *MyVals, int SendCount,
    long long *AllVals, int *RecvCount, int *Displs) const {
    using std::copy;
    copy(MyVals, MyVals+SendCount, &AllVals[Displs[0]]);
    return 0;
  }

  int SerialComm::GatherAll( const std::vector<std::string> &MyVals,
                             std::vector<std::string> &AllVals,
                             int *RevCount, int *Displs) const {
    using std::copy;
    copy(MyVals.begin(), MyVals.end(), &AllVals[Displs[0]]);
    return 0;
  }

  int SerialComm::Scatterv( double *AllVals, int *SendCount, int *Displs,
                            double *MyVals, int RevCount, int root) const {
    using std::copy;
    copy(&AllVals[Displs[0]], &AllVals[Displs[0]]+RevCount, MyVals);
    return 0;
  }

  int SerialComm::SumAll( const double *PartialSums, double *GlobalSums,
                          int Count) const {
    using std::copy;
    copy(PartialSums, PartialSums+Count, GlobalSums);
    return 0;
  }

  int SerialComm::SumAll( const int *PartialSums, int *GlobalSums,
                          int Count) const {
    using std::copy;
    copy(PartialSums, PartialSums+Count, GlobalSums);
    return 0;
  }

  int SerialComm::SumAll( const long *PartialSums, long *GlobalSums,
                          int Count) const {
    using std::copy;
    copy(PartialSums, PartialSums+Count, GlobalSums);
    return 0;
  }
  int SerialComm::SumAll( const unsigned *PartialSums, unsigned *GlobalSums,
                          int Count) const {
    using std::copy;
    copy(PartialSums, PartialSums+Count, GlobalSums);
    return 0;
  }

  int SerialComm::SumAll(const long long *PartialSums,
                         long long *GlobalSums,
                         int Count) const {
    using std::copy;
    copy(PartialSums, PartialSums+Count, GlobalSums);
    return 0;
  }
  int SerialComm::SumAll(const unsigned long *PartialSums,
                         unsigned long *GlobalSums,
                         int Count) const {
    using std::copy;
    copy(PartialSums, PartialSums+Count, GlobalSums);
    return 0;
  }

  int SerialComm::SumAll(const unsigned long long *PartialSums,
                         unsigned long long *GlobalSums,
                         int Count) const {
    using std::copy;
    copy(PartialSums, PartialSums+Count, GlobalSums);
    return 0;
  }

  long int SerialComm::SumAll(const long int PartialSum) const {
    return PartialSum;
  }
  unsigned SerialComm::SumAll(const unsigned PartialSum) const {
    return PartialSum;
  }
  unsigned long SerialComm::SumAll(const unsigned long PartialSum) const {
    return PartialSum;
  }
  unsigned long long SerialComm::SumAll(const unsigned long long PartialSum)
  const {
    return PartialSum;
  }

  int SerialComm::Max( const int *PartialMaxs, int *GlobalMaxs,
                       int Count) const {
    using std::copy;
    copy(PartialMaxs, PartialMaxs+Count, GlobalMaxs);
    return 0;
  }
  int SerialComm::Max( const long *PartialMaxs, long *GlobalMaxs,
                       int Count) const {
    using std::copy;
    copy(PartialMaxs, PartialMaxs+Count, GlobalMaxs);
    return 0;
  }
  int SerialComm::Max( const unsigned *PartialMaxs, unsigned *GlobalMaxs,
                       int Count) const {
    using std::copy;
    copy(PartialMaxs, PartialMaxs+Count, GlobalMaxs);
    return 0;
  }
  int SerialComm::Max( const long long *PartialMaxs, long long *GlobalMaxs,
                       int Count) const {
    using std::copy;
    copy(PartialMaxs, PartialMaxs+Count, GlobalMaxs);
    return 0;
  }
  int SerialComm::Max( const long unsigned *PartialMaxs, 
                       long unsigned *GlobalMaxs,
                       int Count) const {
    using std::copy;
    copy(PartialMaxs, PartialMaxs+Count, GlobalMaxs);
    return 0;
  }

  int SerialComm::MaxAll( const double *PartialMaxs, double *GlobalMaxs,
                          int Count) const {
    using std::copy;
    copy(PartialMaxs, PartialMaxs+Count, GlobalMaxs);
    return 0;
  }

  int SerialComm::MaxAll( const int *PartialMaxs, int *GlobalMaxs,
                          int Count) const {
    using std::copy;
    copy(PartialMaxs, PartialMaxs+Count, GlobalMaxs);
    return 0;
  }

  int SerialComm::MaxAll( const long int *PartialMaxs,
                          long int *GlobalMaxs,
                          int Count) const {
    using std::copy;
    copy(PartialMaxs, PartialMaxs+Count, GlobalMaxs);
    return 0;
  }
  int SerialComm::MaxAll( const unsigned int *PartialMaxs,
                          unsigned int *GlobalMaxs,
                          int Count) const {
    using std::copy;
    copy(PartialMaxs, PartialMaxs+Count, GlobalMaxs);
    return 0;
  }

  int SerialComm::MaxAll( const long long *PartialMaxs,
                          long long *GlobalMaxs,
                          int Count) const {
    using std::copy;
    copy(PartialMaxs, PartialMaxs+Count, GlobalMaxs);
    return 0;
  }
  int SerialComm::MaxAll( const unsigned long *PartialMaxs,
                          unsigned long *GlobalMaxs,
                          int Count) const {
    using std::copy;
    copy(PartialMaxs, PartialMaxs+Count, GlobalMaxs);
    return 0;
  }

  int SerialComm::MaxAll( const unsigned long long *PartialMaxs,
                          unsigned long long *GlobalMaxs,
                          int Count) const {
    using std::copy;
    copy(PartialMaxs, PartialMaxs+Count, GlobalMaxs);
    return 0;
  }

  int SerialComm::MaxAll( unsigned &GlobalMaxs) const {
    return 0;
  }

  int SerialComm::MaxAll( int64_t &GlobalMaxs) const {
    return 0;
  }

  int SerialComm::MaxAll( uint64_t &GlobalMaxs) const {
    return 0;
  }

  int SerialComm::MinAll( const double *PartialMins, double *GlobalMins,
                          int Count) const {
    using std::copy;
    copy(PartialMins, PartialMins+Count, GlobalMins);
    return 0;
  }

  int SerialComm::MinAll( const int *PartialMins, int *GlobalMins,
                          int Count) const {
    using std::copy;
    copy(PartialMins, PartialMins+Count, GlobalMins);
    return 0;
  }

  int SerialComm::MinAll( const unsigned *PartialMins, unsigned *GlobalMins,
                          int Count) const {
    using std::copy;
    copy(PartialMins, PartialMins+Count, GlobalMins);
    return 0;
  }

  int SerialComm::MinAll(const long long *PartialMins,
                         long long *GlobalMins,
                         int Count) const {
    using std::copy;
    copy(PartialMins, PartialMins+Count, GlobalMins);
    return 0;
  }
  int SerialComm::MinAll(const unsigned long *PartialMins,
                         unsigned long *GlobalMins,
                         int Count) const {
    using std::copy;
    copy(PartialMins, PartialMins+Count, GlobalMins);
    return 0;
  }
  int SerialComm::MinAll(const unsigned long long *PartialMins,
                         unsigned long long *GlobalMins,
                         int Count) const {
    using std::copy;
    copy(PartialMins, PartialMins+Count, GlobalMins);
    return 0;
  }

  int SerialComm::MinAll   ( int                &GlobalMins) const {return 0;}
  int SerialComm::MinAll   ( unsigned int       &GlobalMins) const {return 0;}
  int SerialComm::MinAll   ( long long          &GlobalMins) const {return 0;}
  int SerialComm::MinAll   ( unsigned long      &GlobalMins) const {return 0;}
  int SerialComm::MinAll   ( unsigned long long &GlobalMins) const {return 0;}
  int SerialComm::MinLocAll( int                &GlobalMins) const {return 0;}
  int SerialComm::MinLocAll( unsigned int       &GlobalMins) const {return 0;}
  int SerialComm::MinLocAll( unsigned long      &GlobalMins) const {return 0;}
  int SerialComm::MinLocAll( unsigned long long &GlobalMins) const {return 0;}

  int SerialComm::MaxLocAll( const double *PartialMaxs, const int *PartialLocs,
                             double *GlobalMaxs, int *GlobalLocs,
                             int Count) const {
    using std::copy;
    copy(PartialMaxs, PartialMaxs+Count, GlobalMaxs);
    copy(PartialLocs, PartialLocs+Count, GlobalLocs);
    return 0;
  }

  int SerialComm::MinLocAll( const double *PartialMins, const int *PartialLocs,
                             double *GlobalMins, int *GlobalLocs,
                             int Count) const {
    using std::copy;
    copy(PartialMins, PartialMins+Count, GlobalMins);
    copy(PartialLocs, PartialLocs+Count, GlobalLocs);
    return 0;
  }

  /// Performs a serial append to a file
  void SerialComm::append_data(const std::string& fname,const std::string& data) const{
    // Open the file for writing
    std::ofstream fout(fname.c_str(),ios::app | ios::out);

    // Write out the information
    fout << data.c_str();

    // Close the file
    fout.close();
  }

/// Makes DGM use exceptions
#define DGM_USE_EXCEPTIONS

  void SerialComm::exit(const int code) const {
    //std::cout << "SerialComm::exit("<<code<<")"<<std::endl;
#ifdef DGM_USE_EXCEPTIONS
    throw DGM::exception(code);
#else
    std::exit(code);
#endif
  }

  void SerialComm::error(const std::string &msg, int code) const {
    //cerr() << msg << ": " << hex << showbase << code << endl;
#ifdef DGM_USE_EXCEPTIONS
    throw DGM::exception(msg);
#else
    cerr() << msg << endl;
    SerialComm::exit(code);
#endif
  }

  void SerialComm::warning(const std::string &msg) const {
    cout() << msg << endl;
  }

#ifdef DGM_USE_TEUCHOS_COMM
  Teuchos::RCP< const Teuchos::Comm< int > > SerialComm::getTeuchosComm() {
    if (teuchosComm.is_null()) {
      teuchosComm = Teuchos::rcp(new Teuchos::SerialComm<int>());
    }
    return teuchosComm;
}
#endif

// turn off local defines
#ifdef DGM_USE_EXCEPTIONS
#undef DGM_USE_EXCEPTIONS
#endif

} // namespace DGM

#endif  // DGM_SERIALCOMM_HPP
