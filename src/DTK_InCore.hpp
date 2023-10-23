#ifndef DTK_INCORE_HPP
#define DTK_INCORE_HPP

/** \file DTK_InCore.hpp
    \brief Database for mixed in-core and out-of-core storage
    \author James Overfelt
    \author Scott Collis
    \author Bill Spotz
*/

// System includes
#include <map>
#include <set>
#include <string>
#include <sys/resource.h>
#include <sys/time.h>
#include <sstream>
#include <fstream>
#include <limits>
#include <cstdio>
#include <cmath>

// Boost includes
#ifdef DGM_INCORE_USE_UNORDERED_MAP
#include "boost/unordered_map.hpp"
#endif

// JSON includes
#ifdef DGM_USE_JSON
#include "json/json.h"
#endif

// DTK includes
#include "DTK.hpp"

// Asynchronous I/O includes
#ifdef DGM_INCORE_ASYNCHRONOUS_IO
#include <unistd.h>
#ifdef _POSIX_ASYNCHRONOUS_IO
#include <aio.h>
#endif
#endif

namespace DTK {

/// Manages in-core storage of the Record database
/** This class allows the Record class to, optionally, store the Record
    database to memory instead of to disk.  For small to medium sized
    problems, this should make things faster, especially for parallel
    execution where out-of-core storage to a shared disk can be very slow
    due to contention. */
template < typename Scalar,
           typename Ordinal,
           typename VectorField,
           typename Domain >
class InCore : public DTK::Checkpoint<Scalar,Ordinal,VectorField,Domain>
{

  /// Manages asynchronous I/O
  template <typename T>
  class asynchronous_io {
  public :
    typedef T io_request;
    asynchronous_io() {};
    virtual ~asynchronous_io(){};
    virtual io_request request() =0;
    virtual void set_buffer (const std::string &buffer) =0;
    virtual bool write(const std::string &name) =0;
    virtual bool io_in_progress() =0;
    virtual void wait() =0;
    virtual bool free() =0;
    virtual const std::string &Ptr() const =0;
  };

  /// Asynchronous I/O using MPI
  class asynchronous_io_mpi;
  /// Asynchronous I/O in serial
  class asynchronous_io_serial;
  /// Asynchronous I/O off with MPI
  class asynchronous_io_mpi_off;
  /// Asynchronous I/O off in serial
  class asynchronous_io_off;

#ifdef DGM_INCORE_ASYNCHRONOUS_IO
#ifdef DGM_PARALLEL
  typedef asynchronous_io_mpi     io_type;
#elif defined _POSIX_ASYNCHRONOUS_IO
  typedef asynchronous_io_serial  io_type;
#else
#error The DGM_INCORE_ASYNCHRONOUS_io macro was specified but platform \
  does not support Posix I/O and MPI has been turned off.
#endif
#else
#ifdef DGM_PARALLEL
  typedef asynchronous_io_mpi_off io_type;
#else
  typedef asynchronous_io_off     io_type;
#endif
#endif

  /// Record class for InCore I/O
  class Record {
  public :
    typedef typename DTK::Shared<io_type>::Ptr Pointer;
    Record();
    ~Record();
    const std::string &Ptr() const;
    Record &operator=(const std::string &s);
    bool sync();
    bool write(const std::string &name);
    int write(const bool asynchronous, const std::string &name,
              VectorField &U, Domain *domain, const bool save_as_float,
              const Json::Value &compression);
    Pointer aio;
    const VectorField *write_VectorField;
  };

public:

  InCore();
  virtual ~InCore();
  std::streamoff initialize(Domain *domain, const bool griewank);
  void local_write(const std::string &name, VectorField &U, Domain *domain);
  void local_read (const std::string &name, VectorField &U, Domain *domain);
  bool local_exists(const std::string &name, const VectorField &U,
                    const Domain *domain) const;
  bool local_room(const std::string &) const;
  void erase(const std::string &name, const int pid=0);
  void clear();
  size_t database_size() const {return database.size();}

  /// \name Checkpoint interface
  //@{
  virtual bool initialize(Domain *domain) {
    initialize(domain,false);
    return false;
  }
  virtual void reinitialize(Domain *domain) {};
  virtual void local_write(Ordinal, Ordinal, const std::string &name,
                           VectorField &U, Domain *domain) {
    local_write(name,U,domain);
  }
  virtual void local_read(Ordinal, Ordinal, const std::string &name,
                          VectorField &U, Domain *domain) {
    local_read(name,U,domain);
  }
  virtual void write_stats() const;
  //@}

  std::vector<std::string> database_keys() const;
  uint64_t size_of_memory()  const { return bytes_to_use; }
  uint64_t size_of_record()  const { return record_size; }
  uint64_t size_of_adjoint() const { return record_size; }

private:

#ifdef DGM_INCORE_USE_UNORDERED_MAP
  typedef boost::unordered_map<std::string, Record> Map;
#else
  typedef std::map<std::string, Record> Map;
#endif
  Map database;                       ///< In-core Record database
  std::set<std::string>
    out_of_core_files;                ///< Out-of-core Record database
  bool asynchronous;                  ///< True if asynchronous IO is used
  bool outcore;                       ///< True if storage is out-of-core
  bool save_as_float;                 ///< True if storage is in floating point
  unsigned debug_level;               ///< Defines debug information output
  unsigned procs_per_node;            ///< Number of processors per node
  uint64_t bytes_to_use;              ///< Amount of memory to use for storage
  uint64_t record_size;               ///< Size of each record in the database
  uint64_t max_number_of_records;     ///< Max number of records you can store
  unsigned file_descriptors_used;     ///< Number of file descriptors used
  rlim_t file_descriptor_limit;       ///< Maximum number of file descriptors
#ifdef DGM_USE_JSON
  Json::Value compression;            ///< Parameters for compression
#endif

  /// Copy construction not allowed
  InCore(const InCore &);
  
  /// Copy construction not allowed
  InCore &operator=(const InCore &);

  int replace_record_in_database(const std::string &name);
  void create_record_in_database(const std::string &name);
  void create_record_in_database(const std::string &name,
                                 const std::string &record);
  unsigned free_up_file_descriptors();
  enum Op {LOCAL_WRITE, LOCAL_READ, ERASE};
  void dump_database(const std::string &name, const Op op, 
                     const int pid=0) const;
};

} // namespace DTK

#endif // DTK_INCORE_HPP
