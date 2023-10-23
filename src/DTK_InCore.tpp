#ifndef DTK_INCORE_TPP
#define DTK_INCORE_TPP

/** \file DTK_InCore.tpp
    \brief Database for mixed incore/out-of-core storage
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
#include <iostream>
#include <sstream>
#include <fstream>
#include <limits>
#include <cstdio>
#include <cmath>
using namespace std;

// Need MPI if in parallel
#ifdef DGM_PARALLEL
#include "mpi.h"
#endif

// Boost includes
#ifdef DGM_INCORE_USE_UNORDERED_MAP
#include "boost/unordered_map.hpp"
#endif

// DTK includes
#include "DTK.hpp"
#include "DTK_InCore.hpp"

// JSON includes
#ifdef DGM_USE_JSON
#include "json/json.h"
#endif

// These DGM includes are general utilities not real DGM dependencies
#include "Format.hpp"
#include "Table.hpp"
#include "Memory.hpp"
#include "Utilities.hpp"

// Asynchronous I/O includes
#ifdef DGM_INCORE_ASYNCHRONOUS_IO
#include <unistd.h>
#ifdef _POSIX_ASYNCHRONOUS_IO
#include <aio.h>
#endif
#endif

namespace DTK {

#define STRINGIFY(x) #x
#define STRING(x) STRINGIFY(x)

namespace {
  struct io_stats {
    unsigned open;
    unsigned close;
    unsigned read;
    unsigned write;
    unsigned wait;
    io_stats() : open(0), close(0), read(0), write(0), wait(0)  {}
  };
  inline io_stats &stats() {
    static io_stats s;
    return s;
  }
}

//===========================================================================
//                         Asynchronous I/O Class
//===========================================================================

#ifdef DGM_INCORE_ASYNCHRONOUS_IO
#ifdef DGM_PARALLEL
template < typename Scalar,
           typename Ordinal,
           typename VectorField,
           typename Domain >
class InCore<Scalar,Ordinal,VectorField,Domain>::
    asynchronous_io_mpi :
      public InCore<Scalar,Ordinal,VectorField,Domain>::
        asynchronous_io<MPI_Request>
{
private :
  string      ptr;
  MPI_File    fh;
  MPI_Request req;
public :
  asynchronous_io_mpi() : ptr(), fh(MPI_FILE_NULL),
                          req(MPI_REQUEST_NULL) {}
  virtual ~asynchronous_io_mpi() {}
  virtual MPI_Request request() { return req; }
  virtual void set_buffer (const string &s) {
    // Hate to do this, but const_cast the string buffer pointer so the
    // asynchronous I/O routines can use the same buffers as the stringstream
    // routines.  This seems preferable than keeping separate buffers for the
    // asynchronous I/O functions and the stringstream functions.
    ptr = s;
  }
  virtual bool write(const string &name) {
    MPI_Info info;
    MPI_Info_create(&info);
#ifdef DGM_MPI_IO_HINTS
    MPI_Info_set(info,"cb_nodes","1");
#endif
    char s[1+name.size()];
    name.copy (s, name.size());
    s[name.size()] = '\0';
    {
      if (const int stat = MPI_File_open
          (MPI_COMM_SELF, s, MPI_MODE_WRONLY | MPI_MODE_CREATE, info, &fh))
        DGM::Comm::World->error("MPI_File_open", stat);
      ++stats().open;
    }
    {
      char *p = const_cast<char*>(ptr.data());
      if (const int stat = MPI_File_iwrite
          (fh, p, ptr.size(), MPI_CHAR, &req))
        DGM::Comm::World->error("MPI_File_iwrite",stat);
      ++stats().write;
    }
    MPI_Info_free(&info);
    return true;
  }
  virtual bool io_in_progress() {
    if (req != MPI_REQUEST_NULL) {
      int completed = 0;
      if (const int stat = MPI_Test(&req, &completed, MPI_STATUS_IGNORE))
        DGM::Comm::World->error("MPI_Test",stat);
      return !completed;
    }
    return false;
  }
  virtual void wait() {
    MPI_Status status;
    if (req != MPI_REQUEST_NULL) {
      if (const int stat = MPI_Wait(&req, MPI_STATUS_IGNORE))
        DGM::Comm::World->error("MPI_Wait",stat);
      ++stats().wait;
    }
  }
  virtual bool free() {
    const bool fclose_called = (fh != MPI_FILE_NULL);
    if (fh != MPI_FILE_NULL) {
      if (const int stat = MPI_File_close(&fh))
        DGM::Comm::World->error("MPI_File_close",stat);
      ++stats().close;
    }
    fh  = MPI_FILE_NULL;
    req = MPI_REQUEST_NULL;
    return fclose_called;
  }
  virtual const string &Ptr() const { return ptr;}
};
namespace {
void wait_any(vector<MPI_Request> &list) {
  int index = 0;
  MPI_Status status;
  if (const int stat = MPI_Waitany(list.size(), &list[0], &index, &status))
    DGM::Comm::World->error("MPI_Waitany",stat);
}
}
#elif defined _POSIX_ASYNCHRONOUS_IO
template < typename Scalar,
           typename Ordinal,
           typename VectorField,
           typename Domain >
class InCore<Scalar,Ordinal,VectorField,Domain>::
    asynchronous_io_serial :
        public InCore<Scalar,Ordinal,VectorField,Domain>::
            asynchronous_io<aiocb*>
{
private :
  string ptr;
  FILE *file;
  aiocb CB;
public :
  aiocb *request() { return &CB; }
  asynchronous_io_serial() : ptr(), file(NULL) {
    memset (&CB, 0, sizeof(CB));
  }
  virtual ~asynchronous_io_serial() {}
  virtual void set_buffer (const string &s) {
    // Hate to do this, but const_cast the string buffer pointer so the
    // asynchronous I/O routines can use the same buffers as the stringstream
    // routintes.  This seems preferable than keeping separate buffers for the
    // asynchronous I/O functions and the stringstream functions.
    ptr = s;
    CB.aio_buf = const_cast<char*>(ptr.data());
    CB.aio_nbytes = ptr.size();
  }
  virtual bool write(const string &name) {
    file = fopen(name.c_str(), "w" );
    ++stats().open;
    if (!file) {
      string error = "Could not open file ";
      error += name +  " in file " __FILE__ " at line " STRING(__LINE__);
      DGM::Comm::World->error(error);
    }
    CB.aio_fildes = fileno(file);
    const int ret = aio_write (&CB);
    if (ret) {
      DGM::Comm::World->error("Asynchronous write failed in file"
                              __FILE__ " at line " STRING(__LINE__));
    }
    ++stats().write;
    return true;
  }
  virtual bool io_in_progress() {
    return (file && aio_error(&CB) == EINPROGRESS);
  }
  virtual void wait() {
    struct aiocb *aio_list[1] = {&CB};
    const int ret = aio_suspend(aio_list, 1, NULL);
    if (ret) {
      DGM::Comm::World->error("Asynchronous wait failed in file"
                              __FILE__ " at line " STRING(__LINE__));
    }
    ++stats().wait;
  }
  virtual bool free() {
    const bool fclose_called = file;
    if (file) {
      fclose(file); file = NULL;
      CB.aio_fildes = 0;
      ++stats().close;
    }
    return fclose_called;
  }
  virtual const string &Ptr() const { return ptr;}
};
namespace {
void wait_any(const vector<aiocb*> &list) {
  const int ret = aio_suspend(&list[0], list.size(), NULL);
  if (ret) {
    DGM::Comm::World->error("Asynchronous wait failed in file"
                            __FILE__ " at line " STRING(__LINE__));
  }
}
}
#else
#error The DGM_INCORE_ASYNCHRONOUS_IO macro was specified but platform   \
  does not support Posix I/O and MPI has been turned off.
#endif
#else  // !DGM_INCORE_ASYNCHRONOUS_IO
#ifdef DGM_PARALLEL
/// Manages synchronous I/O with MPI
template < typename Scalar,
           typename Ordinal,
           typename VectorField,
           typename Domain >
class InCore<Scalar,Ordinal,VectorField,Domain>::
    asynchronous_io_mpi_off :
        public InCore<Scalar,Ordinal,VectorField,Domain>::template
            asynchronous_io<int>
{
private :
  string ptr;
public :
  asynchronous_io_mpi_off() : ptr() {}
  virtual ~asynchronous_io_mpi_off(){}
  virtual int request() { return 0; }
  virtual void set_buffer (const string &s) {
    // Hate to do this, but const_cast the string buffer pointer so the
    // asynchronous I/O routines can use the same buffers as the stringstream
    // routines.  This seems preferable than keeping separate buffers for the
    // asynchronous I/O functions and the stringstream functions.
    ptr = s;
  }
  virtual bool write(const string &name) {
    if (!ptr.empty()) {
      MPI_File   fh;
      MPI_Info   info;
      MPI_Status status;
      MPI_Info_create(&info);
#ifdef DGM_MPI_IO_HINTS
      MPI_Info_set(info,"cb_nodes","1");
#endif
      char s[1+name.size()];
      name.copy (s, name.size());
      s[name.size()] = '\0';
      if (const int stat = MPI_File_open
          (MPI_COMM_SELF, s,
           MPI_MODE_WRONLY | MPI_MODE_CREATE, info, &fh))
        DGM::Comm::World->error("MPI_File_open", stat);
      ++stats().open;

      char *p = const_cast<char*>(ptr.data());
      if (const int stat = MPI_File_write
          (fh, p, ptr.size(), MPI_CHAR, &status))
        DGM::Comm::World->error("MPI_File_iwrite",stat);
      ++stats().write;

      if (const int stat = MPI_File_close(&fh))
        DGM::Comm::World->error("MPI_File_close",stat);
      ++stats().close;
    }
    return false;
  }
  virtual bool io_in_progress()     { return false;}
  virtual void wait()               {}
  virtual bool free()               { return false; }
  virtual const string &Ptr() const { return ptr;}
};
namespace {
inline void wait_any(const vector<int> &) {}
}
#else  // !DGM_PARALLEL
/// Synchronous, serial I/O
template < typename Scalar,
           typename Ordinal,
           typename VectorField,
           typename Domain >
class InCore<Scalar,Ordinal,VectorField,Domain>::
    asynchronous_io_off :
        public InCore<Scalar,Ordinal,VectorField,Domain>::template
            asynchronous_io<int>
{
private :
  string ptr;
public :
  asynchronous_io_off() : ptr() {}
  virtual ~asynchronous_io_off(){}
  virtual int request() { return 0; }
  virtual void set_buffer (const string &s) {
    // Hate to do this, but const_cast the string buffer pointer so the
    // asynchronoud I/O routines can use the same buffers as the stringstream
    // routintes.  This seems preferable than keeping separate buffers for the
    // asynchronous I/O functions and the stringstream functions.
    ptr = s;
  }
  virtual bool write(const string &name) {
    if (!ptr.empty()) {
      ofstream fs(name.c_str(), ios::out);
      ++stats().open;
      fs.write ( ptr.data() , ptr.size() );
      ++stats().write;
      fs.close();
      ++stats().close;
    }
    return false;
  }
  virtual bool io_in_progress()     { return false;}
  virtual void wait()               {}
  virtual bool free()               { return false; }
  virtual const string &Ptr() const { return ptr;}
};
namespace {
inline void wait_any(const vector<int> &) {}
}
#endif  // DGM_PARALLEL
#endif  // DGM_INCORE_ASYNCHRONOUS

template < typename Scalar,
           typename Ordinal,
           typename VectorField,
           typename Domain >
void InCore<Scalar,Ordinal,VectorField,Domain>::
dump_database(const string &name, const Op op, const int pid) const
{
  if (LOCAL_WRITE == op) {
    cout <<"pid:"<<pid
         <<" Attempting to add key, '"<<name<<"' to database."<<endl;
    cout <<"pid:"<<pid
         <<" The size of the database, "<<database.size()
         <<", is already at maximum size, "<<max_number_of_records
         <<", so new records can not be added."<<endl;
    cout <<"pid:"<<pid
         <<" Failed to find key name '"<<name<<"' in database "
         <<" so can not replace a current record with an updated one."<<endl;
  }
  if (LOCAL_READ == op) {
    cout <<"pid:"<<pid
         <<" Attempting to read key, '"<<name<<"' from database."<<endl;
    cout <<"pid:"<<pid
         <<" The size of the database, "<<database.size()
         <<", but record not found."<<endl;
    cout <<"pid:"<<pid
         <<" Failed to find key name '"<<name<<"' in database."<<endl;
  }
  if (ERASE == op) {
    cout <<"pid:"<<pid
         <<" Attempting to erase key, '"<<name<<"' from database."<<endl;
    cout <<"pid:"<<pid
         <<" Failed to find key name '"<<name<<"' in database "
         <<" so can not erase a current record."<<endl;
  }
  cout <<"pid:"<<pid
       <<" ******** InCore will now fail ********"<<endl;
  cout <<"pid:"<<pid
       <<" The record keys currently in the database are:";
  for ( typename Map::const_iterator i=database.begin();
        i!=database.end(); ++i) cout <<"'"<<i->first<<"', ";
  cout <<endl;
}

//===========================================================================
//                         InCore Record Class
//===========================================================================

template < typename Scalar,
           typename Ordinal,
           typename VectorField,
           typename Domain >
InCore<Scalar,Ordinal,VectorField,Domain>::Record::
Record() :
  aio(new io_type()),
  write_VectorField(0)
{}

template < typename Scalar,
           typename Ordinal,
           typename VectorField,
           typename Domain >
InCore<Scalar,Ordinal,VectorField,Domain>::Record::
~Record() {}

template < typename Scalar,
           typename Ordinal,
           typename VectorField,
           typename Domain >
const string &InCore<Scalar,Ordinal,VectorField,Domain>::Record::
Ptr() const
{
  return aio->Ptr();
}

template < typename Scalar,
           typename Ordinal,
           typename VectorField,
           typename Domain >
typename InCore<Scalar,Ordinal,VectorField,Domain>::Record &
InCore<Scalar,Ordinal,VectorField,Domain>::Record::
operator=(const string &s)
{
  aio->set_buffer(s);
  return *this;
}

template < typename Scalar,
           typename Ordinal,
           typename VectorField,
           typename Domain >
bool InCore<Scalar,Ordinal,VectorField,Domain>::Record::
sync()
{
  if (aio->io_in_progress()) { aio->wait(); }
  return aio->free();
}

template < typename Scalar,
           typename Ordinal,
           typename VectorField,
           typename Domain >
bool InCore<Scalar,Ordinal,VectorField,Domain>::Record::
write(const string &name)
{
  return aio->write(name);
}

template < typename Scalar,
           typename Ordinal,
           typename VectorField,
           typename Domain >
int InCore<Scalar,Ordinal,VectorField,Domain>::Record::
write(const bool asynchronous,
      const string &name,
      VectorField &U,
      Domain *domain,
      const bool save_as_float,
      const Json::Value &compression)
{
#ifdef DGM_INCORE_TIMERS
  static FunctionTimer T("InCore::Record::write");
  FunctionSentry sentry(T);
#endif
  int file_descriptors_used = 0;
  if (sync()) --file_descriptors_used;
  // bool fopen_called = false;
  ostringstream fs(Ptr(), ios::binary|ios::out);
#ifdef DGM_INCORE_USE_SERIALIZATION
  // SSC: experimental code using boost::serialization
  domain->save(fs);
  U->save(fs);
#else
  if (compression.get("Method","None").asString() != "None") {
    domain->comp_write(fs, U, name, compression);
  } else
    domain->local_write(fs, U, name, save_as_float);
#endif
  *this = fs.str();
  if (asynchronous && write(name)) ++file_descriptors_used;
  return file_descriptors_used;
}

//===========================================================================
//                         In-Core Storage Class
//===========================================================================

/// Constructor
template < typename Scalar,
           typename Ordinal,
           typename VectorField,
           typename Domain >
InCore<Scalar,Ordinal,VectorField,Domain>::
InCore() :
  database(),
  out_of_core_files(),
  asynchronous(false),
  outcore(true),
  save_as_float(false),
  debug_level(0),
  procs_per_node(0),
  bytes_to_use(0),
  record_size(0),
  max_number_of_records(0),
  file_descriptors_used(0),
  file_descriptor_limit(numeric_limits<unsigned>::max())
{ }

template < typename Scalar,
           typename Ordinal,
           typename VectorField,
           typename Domain >
void InCore<Scalar,Ordinal,VectorField,Domain>::
write_stats() const
{
  const unsigned num_counts=5;
  const unsigned loc_counts[num_counts] = {
    stats().open, stats().close, stats().read, stats().write, stats().wait};
  unsigned counts[num_counts] = {0};
  DGM::Comm::World->SumAll( loc_counts, counts, num_counts );
  if (DGM::Comm::World->Master()) {
    cout << endl;
    cout <<"I/O counts for Database file storage: " << endl
         <<"  Number of file opens:  "<<counts[0] << endl
         <<"  Number of file closes: "<<counts[1] << endl
         <<"  Number of file reads:  "<<counts[2] << endl
         <<"  Number of file writes: "<<counts[3] << endl
         <<"  Number of file waits:  "<<counts[4] << endl;
    cout << endl;

    cout <<"Number of disk files still in use: "
         <<out_of_core_files.size()<<endl;
    if (out_of_core_files.size()) {
      cout <<"  List of disk files still in use (first 10):";
      unsigned j=0;
      for (set<string>::const_iterator
             i =out_of_core_files.begin();
             i!=out_of_core_files.end() && j<10; ++i,++j) {
        cout << *i<<", ";
      }
      cout << endl;
    }
  }
}

/// Destructor
template < typename Scalar,
           typename Ordinal,
           typename VectorField,
           typename Domain >
InCore<Scalar,Ordinal,VectorField,Domain>::
~InCore()
{
  if (debug_level>2) write_stats();
  int finalized = 0;
#ifdef DGM_PARALLEL
  MPI_Finalized(&finalized);
#endif
  if (!finalized) {
    typename Map::iterator i=database.begin(), e=database.end();
    for (; i!=e; ++i) if (i->second.sync()) --file_descriptors_used;
    stats().open=stats().close=stats().read=stats().write=stats().wait=0;
  }
}

/// Inserts an empty record in the database
template < typename Scalar,
           typename Ordinal,
           typename VectorField,
           typename Domain >
void InCore<Scalar,Ordinal,VectorField,Domain>::
create_record_in_database(const string &name)
{
  database[name] = string(record_size,'\0');
}

/// Inserts a given record in the database
template < typename Scalar,
           typename Ordinal,
           typename VectorField,
           typename Domain >
void InCore<Scalar,Ordinal,VectorField,Domain>::
create_record_in_database(const string &name,
                          const string &record)
{
  database[name] = record;
}

namespace {

/// Parse parameters from a Json::Value
inline void parse_json(unsigned &debug_level,
                       unsigned &procs_per_node,
                       bool     &outcore,
                       bool     &save_as_float,
                       bool     &asynchronous,
                       bool     &percent,
                       unsigned &mb,
                       bool     &limit_by_avail,
                       Json::Value &compression,
                       const Json::Value &json)
{
  if (json.isMember("Statistics")) 
    debug_level = json["Statistics"].asUInt();

  if (json.isMember("Processors Per Node")) 
    procs_per_node = json["Processors Per Node"].asUInt();
  if (json.isMember("Processors per node"))
    procs_per_node = json["Processors per node"].asUInt();

  if (json.isMember("Use Out-of-Core Memory")) 
    outcore = json["Use Out-of-Core Memory"].asBool();
  if (json.isMember("Use out-of-core memory"))
    outcore = json["Use out-of-core memory"].asBool();

  if (json.isMember("Save as Single Precision")) 
    save_as_float = json["Save as Single Precision"].asBool();
  if (json.isMember("Save as single precision"))
    save_as_float = json["Save as single precision"].asBool();

  if (json.isMember("Use Asynchronous I/O")) 
    asynchronous = json["Use Asynchronous I/O"].asBool();
  if (json.isMember("Use asynchronous I/O"))
    asynchronous = json["Use asynchronous I/O"].asBool();

  if (json.isMember("Percent of Memory to Use")) {
    percent = true;
    mb = json["Percent of Memory to Use"].asUInt();
  }
  if (json.isMember("Percent of memory to use")) {
    percent = true;
    mb = json["Percent of memory to use"].asUInt();
  }

  if (json.isMember("Megabytes of Memory to Use")) {
    percent = false;
    mb = json["Megabytes of Memory to Use"].asUInt();
  }
  if (json.isMember("Megabytes of memory to use")) {
    percent = false;
    mb = json["Megabytes of memory to use"].asUInt();
  }

  if (json.isMember("Limit by Available Memory")) 
    limit_by_avail = json["Limit by Available Memory"].asBool();
  if (json.isMember("Limit by available memory"))
    limit_by_avail = json["Limit by available memory"].asBool();
  
#ifdef DGM_USE_JSON
#ifndef DGM_USE_BLOSC
  // Default is no compression
  if (!json.isMember("Compression"))
    compression = Json::Value(Json::objectValue);
  else
    compression = json["Compression"];
  if (!compression.isObject())
    throw std::logic_error("Compression must be a Json object");
  if (compression.set("Method","None").asString() != "None")
    compression["Method"] = "None";
#else
  // This block activates compression of the stored data using the BLOSC
  // library of meta-compressor.
  if (json.isMember("Compression")) {
    compression = json["Compression"];
    if (!compression.isObject())
      throw std::logic_error("Compression must be a Json object");
    compression.set("Method","None"); // blosclz, lz4, lz4hc, snappy, zlib
    compression.set("Verbosity",0);   // 0 is no verbosity
    compression.set("Shuffle",1);     // 1 activates shuffle
    compression.set("Level",9);       // Number between 0 and 9
    // include the double -> float compression
    compression.set("Save as single precision",save_as_float);
  }
#endif
#endif
}

/// Parse parameters from a DGM::Table
inline void parse_tabl(unsigned &debug_level,
                       unsigned &procs_per_node,
                       bool     &outcore,
                       bool     &save_as_float,
                       bool     &asynchronous,
                       bool     &percent,
                       unsigned &mb,
                       bool     &incore,
                       DGM::Table &params,
                       const std::string &root) {
  {
    params["incore-stats"] = "XXX";
    const string  p  = params.read(root, "incore-stats" );
    if (p != "XXX") {
      istringstream s(p);
      s >> debug_level;
    }
  }
  {
    params["procs-per-node"] = "XXX";
    const string p = params.read( root, "procs-per-node" );
    if (p != "XXX") {
      istringstream s(p);
      s >> procs_per_node;
    } else {
      params["ppn"] = "XXX";
      const string pl = params.read( root, "ppn" );
      if (pl != "XXX") {
        istringstream s(pl);
        s >> procs_per_node;
      } 
    }
  }
  {
    params["outcore"] = "XXX";
    const string  p  = params.read( root, "outcore" );
    if (p != "XXX") outcore = (p != "0");
  }
  {
    params["save-as-float"] = "XXX";
    const string  p  = params.read( root, "save-as-float" );
    save_as_float = !(p == "XXX" || p == "0");
  }
  {
    params["asynchronous"] = 0;
    asynchronous = params.read( root, "asynchronous" );
  }
  {
    params["incore"] = "XXX";
    const string  p  = params.read( root, "incore" );
    incore = (p != "XXX" && p != "0");
    istringstream s(p);
    s >> mb ;
    percent = (string::npos != p.find('%'));
    if (!percent && 1==mb) mb = numeric_limits<unsigned>::max()/(1024*1024);
  }
}

}  // anonymous namespace

/// Initializes the in-core storage
/** Determines if incore strorage is to be used. */
template < typename Scalar,
           typename Ordinal,
           typename VectorField,
           typename Domain >
streamoff InCore<Scalar,Ordinal,VectorField,Domain>::
initialize(Domain *domain, const bool griewank)
{
  const DGM::Comm::Ptr comm(domain->get_comm());

  Json::Value json = domain->json_root;

  bool    incore         = false;
  bool    percent        = false;
  bool    limit_by_avail = true;
  unsigned mb            = numeric_limits<unsigned>::max()/(1024*1024);

  if (json.isMember("InCore")) {
    comm->cout()<<"  Reading InCore options from Json file."<<std::endl;
    parse_json(debug_level,
               procs_per_node,
               outcore,
               save_as_float,
               asynchronous,
               percent,
               mb,
               limit_by_avail,
               compression,
               json["InCore"]);
    incore = mb;
    if (!procs_per_node) {
      // Possible this parameter is specified in root.inp file:
      DGM::Table &params(domain->params);
      const std::string root=domain->getRoot()+".inp";
      params["ppn"] = "XXX";
      const string p = params.read( root, "ppn" );
      if (p != "XXX") {
        istringstream s(p);
        s >> procs_per_node;
      }
    }   
  } else {
    DGM::Table &params(domain->params);
    const std::string root=domain->getRoot()+".inp";
    parse_tabl(debug_level,
               procs_per_node,
               outcore,
               save_as_float,
               asynchronous,
               percent,
               mb,
               incore,
               params,root);
    if (incore)
      comm->cout()<<"Reading InCore options from "<<root<<" file."<<std::endl;
  }

  if (!procs_per_node) {
    DGM::Memory M;
    procs_per_node = (unsigned int)M.ncores();
  }
  if (!procs_per_node) procs_per_node=1;

  DGM::Memory mem;
  const uint64_t debug_proc_mem = mem.avail();
  uint64_t total_proc_mem = debug_proc_mem;
  const int id_proc_mem = domain->get_comm()->MinLocAll(total_proc_mem);
  const uint64_t avail_mem = total_proc_mem/procs_per_node;
  const uint64_t requested_size = 
    percent ? mb*avail_mem/100 : static_cast<uint64_t>(mb)*1024*1024;
  bytes_to_use = requested_size;

  if (2<debug_level) {
    const DGM::Comm::Ptr comm(domain->get_comm());
    if (comm->Master())
      cout <<"Extended Memory Stats for InCore:"<<endl;
    cout.flush();
    comm->Barrier();
    // Try to print these in order.  Slow, but this is not used much.
    for (int i=0; i<comm->NumProc(); ++i) {
      if (comm->MyPID() == i) {
        ostringstream s;
        s << "  PID:"<<i<<"/"<<comm->NumProc()<<": "
          << "Memory available:"<<debug_proc_mem/procs_per_node
          <<" ("<<DGM::toXBytes(debug_proc_mem/procs_per_node)<<")";
        if (percent) {
          s<< " times "<<mb<<" percent\n  is "
           << bytes_to_use
           <<" ("<<DGM::toXBytes(bytes_to_use)<<")"
           <<" bytes to use for storage."<<endl;
        } else if (2<=mb) {
          s<<" verses " << mb
           <<" maximum Mb from input file (smallest will be used)."
           <<endl;
        } else s << endl;
        cout << s.str();
      }
      cout.flush();
      comm->Barrier();
    }
  }

  if (limit_by_avail) bytes_to_use = min(bytes_to_use, avail_mem);
  domain->get_comm()->MinAll(bytes_to_use);

  if (griewank) {
    asynchronous = false;  // no file I/O needed.
  } else {
    if (asynchronous) {
      const rlim_t files_to_reserve = 20;
      rlimit rlim;
      getrlimit(RLIMIT_NOFILE, &rlim);
      if (RLIM_INFINITY != rlim.rlim_max) {
        if (files_to_reserve < rlim.rlim_max)
          file_descriptor_limit = rlim.rlim_max - files_to_reserve;
        else
          asynchronous = false;
      }
    }
  }

  if (incore) {
    const DGM::Comm::Ptr comm(domain->get_comm());
    {
      const streamoff safety_factor = 2000;
      if (comm->verbosity()) comm->cout()
         <<"InCore writing a record to determine the size"<<endl;
      ostringstream fs;
      domain->local_write(fs, domain->getU(), domain->mkname(0,0,0), 
                          save_as_float);
      record_size = safety_factor + fs.seekp(0,ios::end).tellp();
      comm->MaxAll(record_size);
    }
    max_number_of_records = bytes_to_use/record_size;
    const uint64_t num_time_steps = domain->get_Nt() + 1;
    const uint64_t num_sub_steps  = domain->get_sstep();
    const uint64_t num_records_to_store = num_time_steps * num_sub_steps;
    const uint64_t tot_mem = num_time_steps*num_sub_steps*record_size;
    const bool enough_memory       =
      num_records_to_store <= max_number_of_records;
    const bool abort_lack_of_mem   =
      !griewank && !enough_memory && !outcore;
    if (enough_memory) asynchronous = false;  // no file I/O needed.
    if ( (abort_lack_of_mem || debug_level>1) && comm->Master()) {
      comm->cout()<<"============================"
                  <<" InCore memory Report "
                  <<"============================"<<endl<<
        "  Number of procs per node        : "<<procs_per_node<<endl<<
        "  Memory available/node (min all) : "<<total_proc_mem
                  <<" ("<<DGM::toXBytes(total_proc_mem)<<")"<<endl<<
        "  Memory available/proc (min all) : "<<avail_mem
                  <<" ("<<avail_mem/(1ULL<<20)<<" MB)"
                  <<" (PID "<<id_proc_mem<<")"<<endl<<
        "  Memory requested/proc           : "
                  <<(mb==1?avail_mem:requested_size);
      if (percent)
        comm->cout()     <<" ("<<mb<<"%)"<<endl;
      else {
        if (1==mb)
          comm->cout()     <<" ( incore=1 => all avail)"<<endl;
        else
          comm->cout()     <<" ("<<requested_size/(1ULL<<20)<<" MB)"<<endl;
      }
      comm->cout() <<
        "  Record size (bytes)             : "<<record_size
          <<" ("<<DGM::toXBytes(record_size)<<")"<<endl<<
        "  Number that fit in memory       : "<<max_number_of_records<<endl<<
        "  Number of time steps            : "<<num_time_steps<<endl<<
        "  Number of sub steps             : "<<num_sub_steps<<endl<<
        "  Number of records to store      : "<<num_records_to_store<<endl<<
        "  Memory required to store all    : "<<tot_mem
                                              <<" ("<<tot_mem/(1ULL<<20)
                                              <<" MB)"<<endl<<
        "  Outcore flag                    : "<<(outcore?"true":"false")
                                              <<endl<<
        "  Save as float flag              : "<<(save_as_float?"true":"false")
                                              <<endl<<
        "  Griewank flag                   : "<<(griewank?"true":"false")
                                              <<endl<<
        "  Asynchronous flag               : "<<(asynchronous?"true":"false")
                                              <<endl<<
        "  InCore Stats flag               : "<<debug_level
                                              <<endl<<
        "  Compression                     : "<<compression["Method"];
      if (compression["Method"]!="None") {
        comm->cout()<<
        "    Level                         : "<<compression["Level"]<<
        "    Shuffle                       : "<<compression["Shuffle"]<<
        "    Verbosity                     : "<<compression["Verbosity"];
      }
      comm->cout()<<"=========================="
                  <<" End InCore memory Report "
                  <<"=========================="<<endl;
    }
    if (abort_lack_of_mem) {
      if (comm->Master()) {
        comm->cout() <<
          "Error: Not enough memory to store entire database incore and "
          "`outcore` \n   flag was specified as 0 in the input file.  Turn "
          "on outcore (by \n   outcore=1 in the *.inp file) and specify "
          "a limit on the amount of \n   incore memory or use a percentage "
          "by using the % sign (by incore=80% \n   in the *.inp file).\n\n";
      }
      comm->error("Not enough memory to keep all snapshots in core.");
    }
    unsigned num_records_created = 0;
    const string empty_record = string(record_size,'\0');
    for (unsigned i=0,k=0; i<num_time_steps && k<max_number_of_records; ++i) {
      for (unsigned j=0; j<num_sub_steps && k<max_number_of_records; ++j,++k) {
        const string &name = domain->mkname(0,i,j);
        create_record_in_database(name,empty_record);
        ++num_records_created;
      }
    }
    if (comm->Master() && debug_level) {
      DGM::Format sci(2,4,'f');
      if (num_records_to_store < num_records_created)
        comm->cout() <<"Using in core storage with "
                     <<sci(num_records_created*record_size/pow(2.0,20))
                     <<" Mb of memory per core \n  for a maximum of "
                     <<num_records_created <<" out of a desired "
                     << num_records_to_store <<" records."
                     <<endl;
      else
        comm->cout() <<"Using in core storage with "
                     <<sci(num_records_created*record_size/pow(2.0,20))
                     <<" Mb of memory per core \n to store the required "
                     << num_records_to_store <<" records."
                     <<endl;
    }
  }
  const streamoff return_val = incore ? max_number_of_records
                                     : numeric_limits<streamoff>::max();
  return return_val;
}

template < typename Scalar,
           typename Ordinal,
           typename VectorField,
           typename Domain >
int InCore<Scalar,Ordinal,VectorField,Domain>::
replace_record_in_database(const string &name)
{
  string key_to_replace;
  vector<typename io_type::io_request> wait_list;
  typename Map::iterator i=database.begin(), e=database.end();
  for (; i!=e && key_to_replace.empty(); ++i) {
    if (!i->second.aio->io_in_progress()) {
      key_to_replace = i->first;
    } else {
      wait_list.push_back(i->second.aio->request());
    }
  }
  if (key_to_replace.empty()) {
    wait_any(wait_list);
    for (i = database.begin(); i!=e && key_to_replace.empty(); ++i) {
      if (!i->second.aio->io_in_progress()) {
        key_to_replace = i->first;
      }
    }
  }
  Record &r = database[key_to_replace];
  bool fclose_called = r.sync();
  database.erase(key_to_replace);
  create_record_in_database(name);
  return fclose_called ? -1 : 0;
}

template < typename Scalar,
           typename Ordinal,
           typename VectorField,
           typename Domain >
unsigned InCore<Scalar,Ordinal,VectorField,Domain>::
free_up_file_descriptors()
{
  unsigned freed_up_descriptors = 0;
  vector<typename io_type::io_request> wait_list;
  typename Map::iterator i=database.begin(), e=database.end();
  for (; i!=e; ++i) {
    if (!i->second.aio->io_in_progress() && i->second.sync()) {
      ++freed_up_descriptors;
    } else {
      wait_list.push_back(i->second.aio->request());
    }
  }
  if (!freed_up_descriptors) {
    wait_any(wait_list);
    for (i = database.begin(); i!=e; ++i) {
      if ( !i->second.aio->io_in_progress() && i->second.sync()) {
        ++freed_up_descriptors;
      }
    }
    if (!freed_up_descriptors) {
      DGM::Comm::World->error("Failed to free file descriptor in file "
                              __FILE__ " at line " STRING(__LINE__));
    }
  }
  return freed_up_descriptors;
}

/// Parallel write to in-core storage
template < typename Scalar,
           typename Ordinal,
           typename VectorField,
           typename Domain >
void InCore<Scalar,Ordinal,VectorField,Domain>::
local_write(const string &name,
            VectorField &U,
            Domain *domain)
{
  DGM::Comm::Ptr comm = domain->get_comm();
  if (database.count(name) ||
      database.size() < max_number_of_records) {
    file_descriptors_used +=
      database[name].write(asynchronous,name,U,domain,
                           save_as_float,compression);
    if (4<debug_level) database[name].write_VectorField = &U;
  } else if (asynchronous) {
    file_descriptors_used += replace_record_in_database(name);
    file_descriptors_used +=
      database[name].write(asynchronous,name,U,domain,
                           save_as_float,compression);
    if (4<debug_level) database[name].write_VectorField = &U;
  } else {
    if (!outcore) {
      if (5<debug_level) dump_database(name, LOCAL_WRITE, comm->MyPID());
      comm->error("Out of memory in InCore and the 'outcore' "
                  "flag was set to false \n so no disk files "
                  "could be created. \n"
                  " Terminating at "
                  __FILE__ " at line " STRING(__LINE__));
    } else {
      if (compression.get("Method","None").asString() != "None") {
        domain->comp_write(name, U, compression);
      } else
        domain->local_write(name, U, save_as_float);
      out_of_core_files.insert(name);
    }
  }
  if (file_descriptor_limit < file_descriptors_used) {
    file_descriptors_used -= free_up_file_descriptors();
  }
#if 0
  if (4<debug_level) {
    const double L2_norm = U.L2_norm(U);
    if (comm->Master())
      cout <<" InCore::local_write: Wrote record "<<name
           <<" from VectorField named "<<U.get_name()
           <<" with L2 norm "<<L2_norm<<endl;
    if (isnan(L2_norm))
      cout << comm->MyPID() << ": InCore::local_write: ************* "
           <<" writing NaN data.    ************* "<<endl;
  }
#endif
}

template < typename Scalar,
           typename Ordinal,
           typename VectorField,
           typename Domain >
bool InCore<Scalar,Ordinal,VectorField,Domain>::
local_room(const string &name) const
{
  if (database.count(name) ||
      database.size() < max_number_of_records) {
    return true;
  } else if (asynchronous) {
    return true;
  } else if (!outcore) {
    return false;
  } else {
    return true;
  }
}

/// Parallel read from in-core storage
template < typename Scalar,
           typename Ordinal,
           typename VectorField,
           typename Domain >
void InCore<Scalar,Ordinal,VectorField,Domain>::
local_read(const string &name,
           VectorField &U,
           Domain *domain)
{
  DGM::Comm::Ptr comm = domain->get_comm();
  if (database.count(name)) {
    istringstream fs(database[name].Ptr(), ios::binary|ios::in);
    if (compression.get("Method","None").asString() != "None") {
      domain->comp_read(fs, U, name, Domain::READ_HEADER, compression);
    } else
      domain->local_read(fs, U, name, Domain::READ_HEADER, save_as_float);
#if 0
    if (4<debug_level) {
      bool all_checks_pass = true;
      if (comm->Master())
        cout <<" InCore::local_read 4<debug_level check of read/write Fields"
             <<endl;
      if(database[name].write_VectorField) {
        const VectorField &W = *database[name].write_VectorField;
        if (comm->Master()) {
          cout <<" InCore::local_read: with 4<debug_level comparison "
               <<" of write VectorField with read VectorField:"<<endl
               <<"     write name: "<<W.get_name()
               <<"     read name: "<<U.get_name()<<endl
               <<"     write size: "<<W.size()
               <<"     read size: "<<U.size()<<endl
               <<"     write qtot: "<<W.qtot()
               <<"     read qtot: "<<U.qtot()<<endl
               <<"     write nmodes: "<<W.nmodes()
               <<"     read nmodes: "<<U.nmodes()<<endl
               <<"     write ndof: "<<W.ndof()
               <<"     read ndof: "<<U.ndof()<<endl
               <<"     write sdof: "<<W.sdof()
               <<"     read sdof: "<<U.sdof()<<endl
               <<"     write Qmax: "<<W.Qmax()
               <<"     read Qmax: "<<U.Qmax()<<endl
               <<"     write Lmax: "<<W.Lmax()
               <<"     read Lmax: "<<U.Lmax()<<endl;
        }
        if ( W.qtot()     !=  U.qtot()   ||
             W.nmodes()   !=  U.nmodes() ||
             W.ndof()     !=  U.ndof()   ||
             W.sdof()     !=  U.sdof()   ||
             W.Qmax()     !=  U.Qmax()   ||
             W.Lmax()     !=  U.Lmax()   ) {
          cout <<" ************* ERROR ******************"
               <<" Mismatch in Writing and Reading VectorField."
               <<endl;
          all_checks_pass = false;
        }
        if (W.size() == U.size()) {
          for (typename VectorField::size_type i=0; i<W.size(); ++i) {
            if (W[i]->gne != U[i]->gne ||
                W[i]->ne  != U[i]->ne  ||
                W[i]->nbc != U[i]->nbc ||
                W[i]->Qmax!= U[i]->Qmax||
                W[i]->Lmax!= U[i]->Lmax||
                W[i]->el.size()!= U[i]->el.size()) {
              cout <<" ************* ERROR ******************"
                   <<" Mismatch in Writing and Reading Fields."
                   <<endl;
              all_checks_pass = false;
            }
            if (W[i]->el.size()== U[i]->el.size()) {
              for (size_t e=0; e<W[i]->el.size(); ++e) {
                if (W[i]->el[e]->qa != U[i]->el[e]->qa ||
                    W[i]->el[e]->qb != U[i]->el[e]->qb ||
                    W[i]->el[e]->qc != U[i]->el[e]->qc ||
                    W[i]->el[e]->qtot != U[i]->el[e]->qtot) {
                  cout <<" ************* ERROR ******************"
                       <<" Mismatch in Writing and Reading Elements."
                       <<endl;
                  all_checks_pass = false;
                }
              }
            }
          }
        }
      } else {
        if (comm->Master())
          cout <<" InCore::local_read: with 4<debug_level expected "
               <<" to find a saved write VectorField for comparison to "
               <<" read VectorField but found NULL pointer instead."
               <<endl;
      }
      if (all_checks_pass && comm->Master())
        cout <<" All checks pass on processor 0"<<endl;
    }
#endif
  } else {
    if (!outcore) {
      if (5<debug_level) dump_database(name, LOCAL_READ, comm->MyPID());
      ostringstream s;
       s << "Internal error: InCore running with "
         << " outcore flag set to false and record not found in memory.\n"
         << " Record key '"<<name
         <<"' should previously have been saved in memory.\n"
         << "Will terminate now.\n Terminating in "
         << __FILE__ <<" at line " <<__LINE__<<endl;
      comm->error(s.str());
    } else {
      if (compression.get("Method","None").asString() != "None") {
        domain->comp_read(name, U, Domain::READ_HEADER, compression);
      } else
        domain->local_read(name, U, Domain::READ_HEADER, save_as_float);
      if (4<debug_level) {
        if (comm->Master())
          cout <<" InCore::local_read: with 4<debug_level local read from disk "
               <<" file named:"<<name<<endl;
      }
    }
  }
#if 0
  if (4<debug_level) {
    const double L2_norm = U.L2_norm(U);
    if (comm->Master())
      cout <<" InCore::local_read: Read record "<<name
           <<" into VectorField named "<<U.get_name()
           <<" with L2 norm "<<L2_norm<<endl;
    if (isnan(L2_norm)) {
      cout << comm->MyPID() <<": InCore::local_read: ************* "
           <<" reading NaN data.   ************* "<<endl;
      // Time to go local
      static bool found_nan = false;
      const double local_L2 = U.local_L2_inner_product(U,U);
      if (isnan(local_L2) && !found_nan) {
        for (typename VectorField::size_type i=0;
             i<U.size() && !found_nan; i++) {
          const double field_L2 =
            VectorField::FieldType::local_L2_inner_product(U[i],U[i]);
          if (isnan(field_L2)) {
            for (typename VectorField::FieldType::LocalSize e=0;
                 e<U[i]->ne && !found_nan; e++)
            {
              const double elem_L2 = U[i]->el[e]->L2_inner_product(U[i]->el[e]);
              if (isnan(elem_L2)) {
                cout << " On processor "<<comm->MyPID()
                     << " local element number:"<<e
                     << " is first with NaNs. "
                     << " The element values are:"<<U[i]->el[e]->u<<endl;
                found_nan = true;
              }
            }
          }
        }
      }
    }
  }
#endif
}

/// Parallel read from in-core storage
template < typename Scalar,
           typename Ordinal,
           typename VectorField,
           typename Domain >
bool InCore<Scalar,Ordinal,VectorField,Domain>::
local_exists(const string &name,
             const VectorField &U,
             const Domain *domain) const
{
  if (database.count(name)){
    return true;
  } else if (!outcore) {
    return false;
  } else {
    return ifstream(name.c_str()).good();
  }
}

/// Remove record from in-core storage
template < typename Scalar,
           typename Ordinal,
           typename VectorField,
           typename Domain >
void InCore<Scalar,Ordinal,VectorField,Domain>::
erase(const string &name, const int pid)
{
  if (5<debug_level && !database.count(name)) {
    dump_database(name, ERASE, pid);
  }
  database.erase(name);
  if (outcore && out_of_core_files.erase(name)) remove(name.c_str());
}

/// Remove all records from in-core storage
template < typename Scalar,
           typename Ordinal,
           typename VectorField,
           typename Domain >
void InCore<Scalar,Ordinal,VectorField,Domain>::
clear()
{
  typename Map::iterator i=database.begin(), e=database.end();
  if (outcore) {
    for (; i!=e; ++i) {
      const string &name = i->first;
      if (out_of_core_files.erase(name)) remove( name.c_str() );
    }
  }
  database.clear();
}

template < typename Scalar,
           typename Ordinal,
           typename VectorField,
           typename Domain >
vector<string> InCore<Scalar,Ordinal,VectorField,Domain>::
database_keys() const
{
  vector<string> keys;
  keys.reserve(database.size());
  typename Map::const_iterator i=database.begin(), e=database.end();
  for (; i!=e; ++i) keys.push_back(i->first);
  return keys;
}

} // namespace DTK

#endif  // DTK_INCORE_TPP
