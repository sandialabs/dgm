#ifndef DGM_UTILITIES_HPP
#define DGM_UTILITIES_HPP

/** \file Utilities.hpp
    \brief DGM utilities declaration
    \author Scott Collis

    Contains utilities for sensing the byte-order of the current computer,
    for timing functions and for interfacing to the queuing system.
*/

// system includes
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string>

#include <execinfo.h>
#include <unistd.h>
#include <cxxabi.h>

// DGM includes
#include "Comm.hpp"
#include "String.hpp"

// CMC includes
#include "Stopwatch.hpp"

#ifdef DGM_USE_PBS_API
extern "C" {
#include <pbs_error.h>
#include <pbs_ifl.h>
}
#endif

namespace DGM {

  /// Get the time from master and broadcast
  std::string dateTime();

  /// Determines the byte order on the platform
  class ByteOrder {
  public:
    /// Types of byte order supported by DGM
    enum byteOrder {
      BigEndian,       ///< byte-order used on PowerPC and Risc architectures
      LittleEndian,    ///< byte-order used on Intel-type architectures
      UnknownEndian    ///< this would be bad
    };
    /// Constructor
    ByteOrder() {
      union {
        long l;
        char c[4];
      } test;
      test.l = 1;
      if( test.c[3] && !test.c[2] && !test.c[1] && !test.c[0] )
        order = BigEndian;
      else if( !test.c[3] && !test.c[2] && !test.c[1] && test.c[0] )
        order = LittleEndian;
      else
        order = UnknownEndian;
    }
    /// Returns the byte order for the current computer
    byteOrder get() const { return order; }

    /// Returns the byte order as a string
    std::string asString() const {
      std::string result;
      switch(order) {
      case BigEndian:
        result = "BigEndian";
        break;
      case LittleEndian:
        result = "LittleEndian";
        break;
      default:
        result = "Unknown";
      }
      return result;
    }

    // Check if current byte order matches given string
    bool is(const std::string in) const {
      const std::string ord = asString();
      if (lowerCase(ord)==lowerCase(in))
        return true;
      return false;
    }

    /// Output the byte-order
    void print(std::ostream &out=std::cout) const {
      switch(get()) {
      case BigEndian:
        out << "Big Endian " << std::endl;
        break;
      case LittleEndian:
        out << "Little Endian " << std::endl;
        break;
      default:
        out << "Unknown Endian " << std::endl;
        break;
      }
    }
  private:
    byteOrder order;     ///< local value of system byte order
  };

  /// Job status class
  class JobStatus {
    int tolerance, walltime, cputime;  // in seconds
    CMC::Stopwatch cpu;
    void tremain_(int *walltime , int *cputime);
#ifdef DGM_USE_PBS_API
    int connect;
    char *jobid, *server;
    attrl *attrib;
    batch_status *pstat; char *extend;
#endif
  public:
    inline JobStatus(int f=0);
    inline ~JobStatus();
    inline int finished();
    inline int walltime_remaining();
    inline void tremain(int *walltime , int *cputime);
  };

  /// Constructor
  inline JobStatus::JobStatus(int f) : tolerance(f) {
    walltime=-1; cputime=-1;
    cpu.start();
#ifdef DGM_USE_PBS_API
    jobid   = getenv("PBS_JOBID");
    server  = getenv("PBS_O_HOST");
    connect = pbs_connect(server);
    pstat   = NULL;
    extend  = "";
#ifdef PBS_GET_ALL_ATTRIBS
    attrib = NULL;
#else
    // get only the attributes that you want (resources_used, Resource_list)
    attrib = new attrl;
    attrib->name = ATTR_used;
    attrib->resource = "";
    attrib->value = "";
    attrl *pat = attrib->next = new attrl;
    pat->name = ATTR_l;
    pat->resource = "";
    pat->value = "";
    pat->next = NULL;
#endif
#endif
  }

  /// Destructor
  inline JobStatus::~JobStatus() {
#ifdef DGM_USE_PBS_API
    pbs_disconnect(connect);
#endif
  }

  /// Returns the walltime remaining in this allocation
  inline int JobStatus::walltime_remaining() {
    // prevent unnecessarily frequent checks
    if (cpu.read()/2 > (double)tolerance || walltime==-1) {
      cpu.restart();
      tremain(&walltime, &cputime);
    }
    return walltime;
  }

  /// Returns whether the job is finished
  inline int JobStatus::finished() {
    walltime = walltime_remaining();
    if (walltime == -1) return 0;
    return (walltime < tolerance);
  }

  /// The public interface to the private tremain_ routine
  inline void JobStatus::tremain(int *walltime , int *cputime) {
    tremain_(walltime,cputime);
  }

  /// A class that can provide timing for a function call
  class FunctionTimer : public CMC::Stopwatch {
    const std::string S;    ///< Message for this timer
    const int mypid;
  public:
    /// Constructor
    FunctionTimer (const std::string &s) : 
      CMC::Stopwatch(), S(s), mypid(Comm::World->MyPID()) {}
    /// Destructor
    ~FunctionTimer() {
      std::cout << "  Time in " << S << " on rank " << mypid
                << " is " << this->read() << " sec"
                << " for "<< this->count()<< " function calls"
                << std::endl;
    }
  };

  /// A class that serves as an interface to a FunctionTimer
  class FunctionSentry {
    FunctionTimer *T;       ///< The local function timer
  public:
    /// Constructor
    FunctionSentry (FunctionTimer &t): T(&t) {       T->start();}
    FunctionSentry (FunctionTimer *t): T( t) {if (T) T->start();}
    /// Destructor
    ~FunctionSentry() {if (T) T->stop();}
  };

  /// Generate a backtrace
  class BackTrace {
    DGM::Comm::Ptr comm;
  public:
    BackTrace(DGM::Comm::Ptr _comm= DGM::Comm::World) : comm(_comm) {}
    void print() {
      const int SIZE = 100;
      void *array[SIZE];
      char **strings;
      const int size = backtrace(array, SIZE);
      strings = backtrace_symbols(array, (int)size);
      printf("Obtained %d stack frames.\n", size);
      for (int i = 0; i < size; i++) {
#if 1
        int status;
        const char *demangled = abi::__cxa_demangle(strings[i],0,0,&status);
        comm->cout()<<"Level "<<i<<":"<<demangled<<std::endl;
#else
        printf ("%s\n", strings[i]);
#endif
      }
      free(strings);
    }
  };

  bool file_exists(std::string s, bool allow_zero_size = false);
  bool directory_exists(std::string s);

  /// Scan for a left curly bracket, return scanned string
  string scan_lb(std::ifstream &in, string s);

  /// Scan for a right curly bracket
  void scan_rb(std::ifstream &in, string s);

  /// Return code and tag, on error customize message with string
  std::string scan_tag(std::ifstream &in, std::string &code, std::string s);

  /// Read and ignore nested blocks of Json
  void scan_block(std::ifstream &in, std::string s);
  
  /// Find tag in block, prepend prefix to tag's value
  void prepend(std::string& block, std::string tag, std::string prefix);

  /// Find search string value in block, backup to find start of block, 
  /// prepend prefix to each occurence of tag's value in this block
  void prepend(std::string& block, std::string search, std::string tag, 
    std::string prefix);

  /// Convenience method for determining if integer is odd
  inline bool is_odd(unsigned int n) {
    return n % 2;
  }

  /// Convenience method for determining if integer is even
  inline bool is_even(unsigned int n) {
    return !is_odd(n);
  }

  /// log2 function for signed integers
  inline int log2(int v) {
    if (v < 0) v = -v;  // turn off sign bit
    unsigned int n = 0, s = sizeof(int) * 8 - 1; // skip sign bit
    v >>= 1;
    while (n < s && 0 != v) { v >>= 1; ++n; }
    return n;
  }

} // namespace DGM

#endif  // DGM_UTILITIES_HPP
