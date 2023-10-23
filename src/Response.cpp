/** \file Response.cpp
    \brief Response implementation:  extracts quantities from a vField
    \author James Overfelt
    \author Scott Collis
    \author Curtis Ober
    \copyright (c)2014 Sandia National Laboratories
    \todo Extend to extract the solution on lines, curves and planes
*/

// system includes
#include <limits>
#include <sstream>
#include <fstream>

#include <boost/lexical_cast.hpp>
#if defined(DGM_PARALLEL) && defined(DGM_USE_GENERAL_GHOSTING)
// boost serialization
#include <boost/mpi.hpp>
#include <boost/mpi/environment.hpp>
#include <boost/mpi/communicator.hpp>
#include <boost/mpi/collectives.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/vector.hpp>
#include "boost/serialization/map.hpp"
#include "boost/serialization/string.hpp"
#include "boost/serialization/set.hpp"
#include "boost/archive/binary_iarchive.hpp"
#include "boost/archive/binary_oarchive.hpp"
#endif

// DGM includes
#include "Constants.hpp"
#include "Response.hpp"
#include "Format.hpp"
#include "String.hpp"
#include "Utilities.hpp"
#include "Stopwatch.hpp"
#include "TimeInt.hpp"
#include "Memory.hpp"

// set the default verbosity
#ifndef DGM_RESPONSE_VERBOSE
#define DGM_RESPONSE_VERBOSE 0
#endif

namespace DGM {

namespace {

static const char *ASCII_FORMAT="%18.11e ";

unsigned printval(FILE *file, const Scalar x,
                  const DGM::Response::ProbeFormat format){
  switch (format) {
  case DGM::Response::ASCII :
    fprintf( file, ASCII_FORMAT, x ); break;
  case DGM::Response::DOUBLE : {
    const double y = x;
    fwrite( &y, sizeof(double),1, file ); break;
  }
  default :
    const float y = numeric_cast<float>(x);
    fwrite( &y, sizeof(float),1, file ); break;
  }
  switch (format) {
  case DGM::Response::ASCII  : return 0;
  case DGM::Response::DOUBLE : return sizeof(double);
  default                    : return sizeof(float);
  }
}

Scalar readval(FILE *file, const DGM::Response::ProbeFormat format){
  Scalar x = 0;
  switch (format) {
  case DGM::Response::ASCII : {
    const char *format = (sizeof(x) == sizeof(double)) ? "%le": "%e";
    fscanf( file, format, &x ); break;
  }
  case DGM::Response::DOUBLE : {
    double y;
    fread( &y, sizeof(double),1, file );
    x =  numeric_cast<Scalar>(y);
    break;
  }
  default :
    float y;
    fread( &y, sizeof(float),1, file );
    x = y;
    break;
  }
  return x;
}

std::string probe_format(const  DGM::Response::ProbeFormat format) {
  std::string f;
  switch (format) {
    case   DGM::Response::ASCII  : f = "ASCII"  ; break;
    case   DGM::Response::DOUBLE : f = "DOUBLE" ; break;
    default                      : f = "FLOAT"  ; break;
  }
  return f;
}

#if 0

bool is_inside( const Point &p, const std::pair<Point,Point> &box,
                const Scalar epsilon=0.0 ) {
  return p.x >= box.first.x-epsilon &&
      p.y >= box.first.y-epsilon &&
      p.z >= box.first.z-epsilon &&
      p.x <= box.second.x+epsilon &&
      p.y <= box.second.y+epsilon &&
      p.z <= box.second.z+epsilon;
}

#endif

} // anonymous namespace

//=============================================================================
//                     Response Probe Implementation
//=============================================================================

Scalar Response::Probe::apply(const Field *F) const {
  Scalar tempval = kernel->evaluate(F);
  if (kernel->multiple_processor()) {
    const Scalar x = tempval;
    if (kernel->locally_evaluated()) kernel->comm()->SumAll(&x, &tempval, 1);
  }
  if (kernel->divide_for_average()) tempval /= kernel->divide_for_average();
  return tempval;
}

/// Write a Json header with useful metadata
std::streamoff Response::Probe::write_json_header(const std::string &fname,
                                                  const std::string &hname,
                                                  std::ostream &fs) const {
  streamoff disp=0;
  char now[BUFLEN] = "Time is not available";
#if !defined(DGM_REDSTORM) && !defined(DGM_NO_TIME)
#ifdef DGM_BROADCAST_TIME
  // Only get the time from rank 0 and broadcast
  if (comm->Master()) {
    // get the current date and time from <time.h>
    time_t tp = ::time(0);
    strftime(now,buflen,"%a %b %d %H:%M:%S %Y", localtime(&tp));
  }
  if (all) comm->Broadcast(now, buflen);
#else
  // all ranks get the current date and time from <time.h>
  time_t tp = ::time(0);
  strftime(now,BUFLEN,"%a %b %d %H:%M:%S %Y", localtime(&tp));
#endif
#endif
  Json::Value header;
  header["File created"] = now;
  header["File name"] = fname;
  header["Header file name"] = hname;
  header["Probe type"] = ProbeTypeToString(probetype);
  header["Kernel"] = Json::Value(Json::objectValue);
  kernel->json_output(header["Kernel"]);
  header["Types"] = Json::Value(Json::objectValue);
  header["Types"]["GlobalSize"] = type<DGM::Size>();
  header["Types"]["LocalSize"] = type<DGM::Ordinal>();
  header["Types"]["Scalar"] = type<DGM::Scalar>();
  DGM::ByteOrder byteOrder;
  header["Types"]["ByteOrder"] = byteOrder.asString();
  Json::StyledWriter writer;
  string output = writer.write(header);
  if (!fs)
    throw DGM::exception("Response::Probe::write_json_header file "
                         "stream in bad state for probe file " + fname);
  fs << output;
  if (!fs)
    throw DGM::exception("Response::Probe::write_json_header could not write header to probe file " + fname);
  disp = fs.tellp();
  return disp;
}

string Response::Probe::allocate_file(const DGM::Comm::Ptr comm,
                                      const string &root,
                                      const ProbeFormat f) {
  string fname;
  if (kernel->owned_by_this_proc()) {
    char tmp[80];
    sprintf(tmp,".%s",kernel->name().c_str());
    fname = root + tmp + ".prb";
    const char *mode= (f==ASCII)?"w":"wb";
    file = fopen(fname.c_str(),mode);
    if (!file) {
      comm->cerr()
        << "Response::Probe::allocate_file: Failed to open probe file - "
        << fname << endl;
      comm->exit(DGM::FAILURE);
    }
/// define to control the output of header information
#define DGM_RESPONSE_PROBE_USE_HEADER
#ifdef DGM_RESPONSE_PROBE_USE_HEADER
    // optionally write out a header
    const string hname = root + tmp + ".hdr";
    //comm->cout() << "Writing probe metadata in " << hname << endl;
    ofstream fs(hname.c_str());
    if (!fs) {
      stringstream msg;
      msg << "Response::Probe::allocate_file: Could not open header file - "
          << hname << endl;
      comm->error(msg.str());
    }
    //streamoff disp =
      write_json_header(fname, hname, fs);
    fs.close();
    //comm->cout() << "Displacement of " << hname << " is " << disp << endl;
#endif
  }
  return fname;
}

streamoff Response::Probe::file_size(const DGM::Comm::Ptr comm,
                                     const string &root,
                                     const ProbeFormat f) {
  const string fname = root + ".prb";
  ifstream pfile(fname.c_str(),ios::binary);
  if (pfile.fail()) {
    comm->cerr()
       << "Response::Probe::file_size: Failed to open probe file - "
       << fname << endl;
    comm->exit(DGM::FAILURE);
  }
  pfile.seekg(0,ios::end);
  return pfile.tellg();
}

string Response::Probe::open_file(const DGM::Comm::Ptr comm,
                                  const string &root,
                                  const ProbeFormat f) {
  string fname;
  char tmp[80];
  sprintf(tmp,".%s",kernel->name().c_str());
  fname = root + tmp + ".prb";
  const char *mode= (f==ASCII)?"r":"rb";
  file = fopen(fname.c_str(),mode);
  if (!file) {
    comm->cerr()
       << "Response::Probe::open_file: Failed to open probe file - "
       << fname << endl;
    comm->exit(DGM::FAILURE);
  }
  return fname;
}

void Response::Probe::close_file(){
  if (file) fclose(file);
  file = NULL;
}

void Response::Probe::print(const Scalar x, const ProbeFormat format) const {
  if (kernel->owned_by_this_proc()) printval(file, x, format);
}

Scalar Response::Probe::read(const ProbeFormat format) const {
  if (kernel->owned_by_this_proc()) return readval(file, format);
  else return 0;
}

void Response::Probe::print_newline(const ProbeFormat f) const {
  if (kernel->owned_by_this_proc() && f==ASCII) {
    fprintf( file, "\n" );
    fflush( file );
  }
}

void Response::Probe::reduce_multi_processor
(dVector &partial_sums) const {
  if (kernel->multiple_processor() && kernel->locally_evaluated()) {
    int nc = numeric_cast<int>(partial_sums.size());
    dVector temp(nc);
    temp = partial_sums;
#if defined(DGM_PARALLEL) && defined(DGM_USE_MPI_IREDUCE)
    MPI_Comm comm =dynamic_cast<const MpiComm*>(kernel->comm().get())->mpi_comm;
    MPI_Ireduce(&temp[0], &partial_sums[0], nc,
                mpiType<Scalar>(), MPI_SUM, 0, comm, &mpi_request);
#else
    kernel->comm()->SumAll(&temp[0], &partial_sums[0], nc);
#endif
  }
}

void Response::Probe::reduce_multi_processor(std::vector<Scalar> &partial_sums)
  const {
  if (kernel->multiple_processor() && kernel->locally_evaluated()) {
    std::vector<Scalar> temp(partial_sums);
    int nc = numeric_cast<int>(partial_sums.size());
#if defined(DGM_PARALLEL) && defined(DGM_USE_MPI_IREDUCE)
    MPI_Comm comm =dynamic_cast<const MpiComm*>(kernel->comm().get())->mpi_comm;
    MPI_Ireduce(&temp[0], &partial_sums[0], nc,
                mpiType<Scalar>(), MPI_SUM, 0, comm, &mpi_request);
#else
    kernel->comm()->SumAll(&temp[0], &partial_sums[0], nc);
#endif
  }
}

Scalar Response::Probe::reduce_multi_processor(const Scalar partial_sum)
const {
  Scalar r = partial_sum;
  if (kernel->multiple_processor() && kernel->locally_evaluated()) {
    Scalar x = partial_sum;
#if defined(DGM_PARALLEL) && defined(DGM_USE_MPI_IREDUCE)
    MPI_Comm comm =dynamic_cast<const MpiComm*>(kernel->comm().get())->mpi_comm;
    MPI_Ireduce(&x, &r, 1, mpiType<Scalar>(), MPI_SUM, 0, comm, &mpi_request);
#else
    kernel->comm()->SumAll(&x, &r, 1);
#endif
  }
  return r;
}

Scalar Response::SideSetProbe::apply(const Field *F) const {
  bstat->fill_sides(const_cast<Field *>(F));
  Scalar intgrl = bstat->integrate(F);
  Scalar x = intgrl;
  if (!bstat->sides.empty()) kernel->comm()->SumAll(&x, &intgrl, 1);

  Scalar area = bstat->area();
  x = area;
  if (!bstat->sides.empty()) kernel->comm()->SumAll(&x, &area, 1);
  return intgrl/area;
}

//=============================================================================
//                     Response ProbeIO Implementation
//=============================================================================

void Response::ProbeIO::initFiles(const vField &F) {
  const vector<string> &names = F.get_Field_names();
#ifdef DGM_PARALLEL
  mpi_files.resize(F.size(), MPI_FILE_NULL);
  c_files  .resize(F.size(), 0);
  requests .resize(F.size(), MPI_REQUEST_NULL);
  int stat = MPI_Info_create(&info);

  num_centers_on_proc=0;
  for (size_t i=0; i<probes.size(); ++i) {
    if (probes[i]->kernel->owned_by_this_proc()) ++num_centers_on_proc;
  }

  ioComm = MPI_COMM_NULL;
  const int membershipKey = num_centers_on_proc ? 1 : MPI_UNDEFINED;
  MPI_Comm mpi_comm=dynamic_cast<const DGM::MpiComm*>(comm.get())->mpi_comm;
  stat = MPI_Comm_split(mpi_comm, membershipKey, 0, &ioComm);
  if (stat) comm->error("MPI_Comm_split", stat);

  // ioType = MPI_TYPE_NULL;  Bummer, can't do this so can't free type.
  if (num_centers_on_proc) {
    std::vector<int> offsets(num_centers_on_proc,0);
    for (size_t i=0, n=0; i<probes.size(); ++i) {
      if (probes[i]->kernel->owned_by_this_proc())
        offsets[n++]=probes[i]->kernel->global_id();
    }
    const int block_length = 1;
    const MPI_Datatype size_type = FLOAT==probeFormat?MPI_FLOAT:MPI_DOUBLE;
    stat = MPI_Type_create_indexed_block(offsets.size(), block_length,
                                  &offsets[0], size_type, &ioType);
    if (stat) comm->error("MPI_Type_create_indexed_block", stat);
    stat = MPI_Type_commit(&ioType);
    if (stat) comm->error("MPI_Type_commit", stat);

    for (vField::size_type i=0; i<F.size(); ++i) {
      string fname = root+"."+names[i]+".prb";
      if (use_mpi_io) {
        stat = MPI_File_open(ioComm,
                             const_cast<char*>(fname.c_str()),
                             MPI_MODE_WRONLY | MPI_MODE_CREATE,
                             info, &mpi_files[i]);
        if (stat != MPI_SUCCESS) {
          vector<char> str(MPI_MAX_ERROR_STRING,0);
          int resultlen;
          MPI_Error_string(stat, &str[0], &resultlen);
          comm->error((string)"MPI_File_open:"+&str[0], stat);
        }
        //MPI_File_set_atomicity(mpi_files[i],1);
      } else {
        c_files[i] = fopen(fname.c_str(),"wb");
        if (!c_files[i]) {
          comm->cerr() << "Response::ProbeIO::initFiles(): Failed to open "
                          "probe file - " << fname << endl;
          comm->exit(DGM::FAILURE);
        }
        int np=0; int rank=0;
        MPI_Comm_rank (ioComm, &rank);
        MPI_Comm_size (ioComm, &np );
        counts.resize(np,0), displacements.resize(np,0);
        int num = num_centers_on_proc;
        stat = MPI_Allgather(&num,       1, MPI_INT,
                             &counts[0], 1, MPI_INT, ioComm);
        if (stat != MPI_SUCCESS) comm->error("MPI_Allgather", stat);
        for (int i=1; i<np; ++i)
            displacements[i] = displacements[i-1]+counts[i-1];

        if (displacements.back() + counts.back() !=
            numeric_cast<int>(num_probes)) {
          comm->cerr()
            << "Response::ProbeIO::initFiles(): "
            << "displacements.back() + counts.back() != (int)num_probes)\n"
            << "displacements.back() + counts.back() = "
            << displacements.back() + counts.back()
            << "\n(int)num_probes) = "
            << numeric_cast<int>(num_probes) << endl;
          comm->error("Response error",1);
        }

        all_offsets.resize(num_probes,0);
        stat = MPI_Gatherv ( &offsets[0],     num,          MPI_INT,
                             &all_offsets[0],
                             &counts[0], &displacements[0], MPI_INT,
                              0, ioComm );
        if (stat != MPI_SUCCESS) comm->error("MPI_Gatherv", stat);

        if (!rank) {
          for (Ordinal i=0; i<num_probes; ++i)
            for (Ordinal j=i+1; j<num_probes; ++j)
              if (all_offsets[i] == all_offsets[j]) {
                comm->cerr()
                  << "Response::ProbeIO::initFiles(): "
                  << "all_offsets[i] == all_offsets[j] \n"
                  << "all_offsets[i="<<i<<"] == " << all_offsets[i]
                  << "\nall_offsets[j="<<j<<"] == " << all_offsets[j]
                  << endl;
                comm->error("Response error");
              }
        }
      }
    }
  }
#else
  files.resize(F.size());
  //cout << "files.size() = " << files.size() << endl;
  for (size_t i=0; i<files.size(); ++i) {
    //char tmp[80];
    //sprintf(tmp,".%d",(int)i);
    string fname = root+"."+names[i]+ ".prb";
    //cout << "Opening file " << fname << endl;
    files[i] = fopen(fname.c_str(),"wb");
    if (!files[i]) {
      comm->cerr() << "Response::ProbeIO::initFiles(): Failed to open "
                      "probe file - " << fname << endl;
      comm->exit(DGM::FAILURE);
    }
    // SSC:  write the metadata for head file here
  }
#endif
}

template<typename datatype>
void Response::ProbeIO::WriteTime
(Scalar time,
 vector<DGM::Shared<std::ostringstream>::Ptr>&file_buf) {
#ifdef DGM_PARALLEL
  MPI_Status status;
  if (num_centers_on_proc) {
    const MPI_Datatype size_type =
      sizeof(datatype)==sizeof(float) ? MPI_FLOAT : MPI_DOUBLE;
    for (size_t i=0; i<mpi_files.size(); ++i) {
      if (use_mpi_io) {
        int stat = MPI_File_set_view(mpi_files[i], disp, size_type,
                                     size_type, &native[0], info);
        if (stat) comm->error("MPI_File_set_view", stat);
        datatype t=time;
        stat = MPI_File_write_all(mpi_files[i], &t, 1, size_type, &status);
        if (stat) comm->error("MPI_File_write_all", stat);
      } else {
        int rank=0;
        MPI_Comm_rank(ioComm, &rank);
        if (!rank) {
          if (1==blocked_io_size || ASCII==probeFormat) {
            printval(c_files[i], time, probeFormat);
          } else {
            datatype t=time;
            file_buf[i]->write(reinterpret_cast<const char*>(&t),
                               sizeof(datatype));
          }
        }
      }
    }
  }
  disp+=sizeof(datatype);
#else
  unsigned data_size = 0;
  for (size_t i=0; i<files.size(); ++i) {
    data_size = printval(files[i], time, probeFormat);
  }
  disp+=data_size;
#endif
}

template<typename datatype>
void Response::ProbeIO::WriteVal
  (const vField &F, const bool last_time,
   vector<DGM::Shared<std::ostringstream>::Ptr>&file_buf) {
#ifdef DGM_PARALLEL
  if (probes.size()) {
    vector<vector<datatype> >
      write_buffer(F.size(), vector<datatype>(num_centers_on_proc,0));
    const MPI_Datatype size_type =
      sizeof(datatype)==sizeof(float) ? MPI_FLOAT : MPI_DOUBLE;
    for(size_t n=0; n<mpi_files.size(); n++) {
      for(size_t p=0, o=0; p<probes.size(); ++p) {
        const Scalar tmp = probes[p]->apply(F[n]);
        if (probes[p]->kernel->owned_by_this_proc()) write_buffer[n][o++] = tmp;
      }
      if (num_centers_on_proc) {
        if (use_mpi_io) {
          //MPI_Barrier(ioComm);
          int stat = MPI_File_set_view(mpi_files[n], disp, size_type, ioType,
                                       &native[0], info);
          if (stat) comm->error("MPI_File_set_view", stat);
          MPI_Status status;
          stat = MPI_File_write_all(mpi_files[n], &write_buffer[n][0],
                                    num_centers_on_proc, size_type,
                                    &status);
          if (stat) comm->error("MPI_File_write_all", stat);
          // flush the IO
          stat = MPI_File_sync(mpi_files[n]);
        } else {
          vector<datatype> probe_data(num_probes);
          vector<datatype> buf(num_probes);
          int stat = MPI_Gatherv( &write_buffer[n][0], write_buffer[n].size(),
                                  size_type,
                                  &probe_data[0],
                                  &counts[0], &displacements[0], size_type,
                                  0, ioComm );
          if (stat != MPI_SUCCESS) comm->error("MPI_Gatherv", stat);
          for(Ordinal i=0; i<num_probes; ++i)
            buf[all_offsets[i]]=probe_data[i];
          int rank=0;
          MPI_Comm_rank(ioComm, &rank);
          if (!rank) {
            if (ASCII==probeFormat) {
              for (Ordinal i=0; i<num_probes; ++i)
                fprintf( c_files[n], ASCII_FORMAT, buf[i]);
              fprintf( c_files[n], "\n");
            } else {
              file_buf[n]->write(reinterpret_cast<const char*>(&buf[0]),
                                 num_probes*sizeof(datatype));
              ++blocked_io[n];
              if (last_time || blocked_io_size==blocked_io[n]) {
                fwrite(file_buf[n]->str().data(), sizeof(char),
                       file_buf[n]->str().size(), c_files[n]);
                file_buf[n]->str(string());
                blocked_io[n] = 0;
                if (flush_on_write) fflush(c_files[n]);
              }
            }
          }
          // flush the IO
          //if (!rank) fflush( c_files[n]);
        }
      }
    }
  }
  disp += num_probes*sizeof(datatype);
#else
  const unsigned data_size = sizeof(datatype);
  for(Ordinal n=0; n<numeric_cast<Ordinal>(files.size()); n++) {
    for(size_t p=0; p<probes.size(); ++p) {
      const Scalar x = probes[p]->apply(F[n]);
      if (ASCII!=probeFormat) {
        fseek (files[n],disp+data_size*probes[p]->kernel->global_id(),SEEK_SET);
      }
      printval(files[n], x, probeFormat);
    }
    if (ASCII==probeFormat) fprintf( files[n], "\n" );
  }
  disp += num_probes*data_size;
#endif
}

Response::ProbeIO::~ProbeIO() {
#ifdef DGM_PARALLEL
 for (size_t i=0; i<mpi_files.size(); ++i) {
   if (mpi_files[i] != MPI_FILE_NULL) {
     if (int stat=MPI_File_close(&mpi_files[i]))  {
       error("8; MPI_File_close ",stat);
     }
     mpi_files[i] = MPI_FILE_NULL;
   }
 }
 for (size_t i=0; i<c_files.size(); ++i) {
   if (c_files[i]) fclose(c_files[i]);
   c_files[i] = 0;
 }
 if (ioComm != MPI_COMM_NULL &&
     ioComm != MPI_COMM_SELF && 
     ioComm != MPI_COMM_WORLD) 
   MPI_Comm_free(&ioComm);
#else
 for (size_t i=0; i<files.size(); ++i) {
   if (files[i]) fclose(files[i]);
   files[i] = 0;
 }
#endif
}

Response::ProbeIO::ProbeIO(const DGM::Comm::Ptr c,
                           const ProbeFormat f,
                           const ProbeFiles s,
                           const unsigned b,
                           const bool r,
                           const bool t,
                           const bool u)
  : probes(),
    root(),
    comm(c),
    probeFormat(f),
    probeFiles(s),
    probeTrans(t),
    probeTimeTrace(u),
    //stddev(0),
    nsd(0),
    native(),
    init_files(true),
    use_mpi_io(false),
    flush_on_write(r),
    blocked_io_size(std::max(1u,b)),
    blocked_io(),
    file_buf(),
    num_probes(0),
    num_centers_on_proc(0),
#ifdef DGM_PARALLEL
    info(),
    ioType(),
    disp(0),
    ioComm(MPI_COMM_NULL),
    mpi_files(),
    c_files(),
    requests(),
    all_offsets(),
    counts(),
    displacements()
#else
    files(),
    disp(0)
#endif
{
  const char n[]="native\0";
  native.assign(&n[0], &n[sizeof(n)]);
  if (probeTimeTrace && probeTrans)
    comm->error(
      "Response::ProbeIO::ProbeIO: Cannot both Transpose and Time Trace.");
}

void Response::ProbeIO::initialize_probes(vector<Probe::Ptr> p,
                                          const Ordinal n,
                                          const Ordinal g) {
  probes.clear();
  for (size_t i=0; i<p.size(); ++i) probes.push_back(&(*p[i]));
  nsd       = n;
  num_probes= numeric_cast<Ordinal>(g);
}

void Response::ProbeIO::initialize_root(const string &r) {
  root=r;
  if (COMBINED != probeFiles) {
    for (size_t p=0;p<probes.size();++p) {
      probes[p]->allocate_file(comm, root, probeFormat);
    }
  }
}

void Response::ProbeIO::print(const vField &F,
                              const Scalar time,
                              const bool last_time) {
  if (init_files && COMBINED == probeFiles) {
    initFiles(F);
    init_files=false;
    blocked_io.resize(F.size(),0);
    file_buf.resize(F.size());
    for (Ordinal i=0; i<F.size(); ++i)
      file_buf[i].reset(new std::ostringstream);
  }
#ifndef DGM_NO_TIME_PROBE
  if (COMBINED == probeFiles) {
    if (FLOAT==probeFormat) WriteTime<float>(time, file_buf);
    else                    WriteTime<double>(time, file_buf);
  } else {
    for(size_t p=0; p<probes.size(); ++p) {  // loop over probe points
      probes[p]->print(time, probeFormat);
    }
  }
#endif
  if (COMBINED == probeFiles) {
    if (FLOAT==probeFormat) WriteVal<float>(F, last_time, file_buf);
    else                    WriteVal<double>(F,last_time, file_buf);
  } else {
    for(size_t p=0; p<probes.size(); ++p) {  // loop over probe points
      for(vField::size_type n=0; n<F.size(); n++) {
        const Scalar tempval = probes[p]->apply(F[n]);
        probes[p]->print(tempval, probeFormat);
      }
      probes[p]->print_newline(probeFormat);
    }
  }
}

void Response::ProbeIO::output(const Field *F, dVector &data) const {
  for(size_t p=0, i=0; p<probes.size(); ++p) {
    const Scalar tmpval = probes[p]->apply(F);
    if (probes[p]->kernel->owned_by_this_proc()) {
      data[numeric_cast<Ordinal>(i)] = tmpval;
      ++i;
    }
  }
}

//=============================================================================
//                     Response AllReduce Implementation
//=============================================================================

#ifdef DGM_PARALLEL

Response::AllReduce::AllReduce() : comm_world(MPI_COMM_NULL),
                                   send_requests( ),
                                   recv_requests( ),
                                   msg_pids( ),
                                   send_buffer( ),
                                   recv_buffer( ),
                                   reduce_to( ) {}

void Response::AllReduce::init(const Ordinal num_components,
                               const COMM_VECTOR &comms,
                               const DGM::Comm::Ptr global_comm) {
  dgm_comm   = global_comm;
  comm_world = dynamic_cast<const DGM::MpiComm*>(global_comm.get())->mpi_comm;

  std::vector<int> group_pids, global_pids;
  typedef std::map<unsigned,unsigned> SIZES;
  SIZES msg_size;
  MPI_Group global_group;
  MPI_Comm_group(comm_world, &global_group);

  for (COMM_VECTOR::const_iterator i=comms.begin(); i!=comms.end(); ++i) {
    MPI_Group group;
    const MpiComm* subcomm = dynamic_cast<const MpiComm*>(i->second.get());
    if (!subcomm)
      dgm_comm->error("Response::AllReduce::init: Dynamic cast failed.");
    MPI_Comm comm = subcomm->mpi_comm;
    MPI_Comm_group(comm, &group);
    int np;
    MPI_Group_size(group, &np);
    if (numeric_cast<int>(group_pids.size()) < np) {
      group_pids.resize(np);
      global_pids.resize(np);
      for (int j=0; j<np; ++j) group_pids[j]=j;
    }
    MPI_Group_translate_ranks(group, np,    &group_pids[0],
                              global_group, &global_pids[0]);
    const PROBE_GID gid = i->first;
    for (int j=0; j<np; ++j) {
      msg_size[global_pids[j]] += num_components;
      msg_pids[gid].push_back(global_pids[j]);
      if (MPI_UNDEFINED==global_pids[j])
        dgm_comm->error("Response::AllReduce::init: Invalid PID.");
    }
  }

  send_requests.resize(msg_size.size(), MPI_REQUEST_NULL);
  recv_requests.resize(msg_size.size(), MPI_REQUEST_NULL);
  for (SIZES::const_iterator s=msg_size.begin(); s!=msg_size.end(); ++s) {
      send_buffer[s->first].second.resize(s->second,0);
      recv_buffer[s->first].second.resize(s->second,0);
  }
}

void Response::AllReduce::post_receives(){
  unsigned ind = 0;
  for (BUF::iterator i=recv_buffer.begin(); i!=recv_buffer.end(); ++i,++ind){
    INDEXED_BUF &r_buf = i->second;
    r_buf.first = 0;
    std::vector<Scalar> &buf = r_buf.second;

    const int proc = numeric_cast<int>(i->first);
    const int len  = numeric_cast<int>(buf.size());

    MPI_Irecv(&buf[0], len, mpiType<Scalar>(),
              proc, 0, comm_world, &recv_requests[ind]);
  }
  for (BUF::iterator i=send_buffer.begin(); i!=send_buffer.end(); ++i)
    i->second.first = 0;
}

void Response::AllReduce::all_reduce(dVector &x, const PROBE_GID gid){
  if (msg_pids.count(gid)) {
    const PROC_IDS &to = msg_pids[gid];
    for (PROC_IDS::const_iterator i=to.begin(); i!=to.end(); ++i){
      INDEXED_BUF &s_buf = send_buffer[*i];
      std::vector<Scalar> &buf = s_buf.second;

      if (buf.size() < s_buf.first + x.size())
        dgm_comm->error(" Response::AllReduce::all_reduce: buffer "
                        "size mismatch.");
      for (Ordinal j=0; j<x.size(); ++j) {
        buf[s_buf.first++] = x[j];
      }
      if (s_buf.first == buf.size()) {
        const int len = numeric_cast<int>(buf.size());
        const BUF::difference_type j=std::distance(send_buffer.begin(),
                                                   send_buffer.find(*i));
        MPI_Isend(&buf[0], len, mpiType<Scalar>(),
                  *i, 0, comm_world, &send_requests[j]);
      }
    }
    reduce_to[gid].alias(x);
  }
}

void Response::AllReduce::wait_all(){
  const int r_len = numeric_cast<int>(recv_requests.size());
  const int s_len = numeric_cast<int>(send_requests.size());
  if (r_len) MPI_Waitall(r_len, &recv_requests[0], MPI_STATUS_IGNORE);
  if (s_len) MPI_Waitall(s_len, &send_requests[0], MPI_STATUS_IGNORE);
  for (int i=0; i<r_len; ++i) recv_requests[i] = MPI_REQUEST_NULL;
  for (int i=0; i<s_len; ++i) send_requests[i] = MPI_REQUEST_NULL;

  for (PIDS::const_iterator i=msg_pids.begin(); i!=msg_pids.end(); ++i) {
    const PROBE_GID gid = i->first;
    dVector &y = reduce_to[gid];
    y = 0;
    const PROC_IDS &from = i->second;
    for (PROC_IDS::const_iterator j=from.begin(); j!=from.end(); ++j) {
      INDEXED_BUF &r_buf = recv_buffer[*j];
      const std::vector<Scalar> &buf = r_buf.second;
      for (Ordinal k=0; k<y.size(); ++k) {
        y[k] += buf[r_buf.first++];
      }
    }
  }
  for (BUF::const_iterator i=recv_buffer.begin(); i!=recv_buffer.end(); ++i) {
    const INDEXED_BUF &r_buf = i->second;
    const std::vector<Scalar> &buf = r_buf.second;
    if (buf.size() != r_buf.first) {
      cout<<__FILE__<<":"<<__LINE__
          <<" recv buffer size mismatch. "
          <<" Expected to use "<<buf.size()
          <<" but used "<<r_buf.first
          <<". Probably need to rethink the communication trigger logic."
          <<" Maybe nComponents is messing this up." <<endl;
      dgm_comm->error(" Response::AllReduce::wait_all: recv buffer "
                      "size mismatch.");
    }
  }
  for (BUF::const_iterator i=send_buffer.begin(); i!=send_buffer.end(); ++i) {
    const INDEXED_BUF &s_buf = i->second;
    const std::vector<Scalar> &buf = s_buf.second;
    if (buf.size() != s_buf.first) {
      cout<<__FILE__<<":"<<__LINE__
          <<" send buffer size mismatch. "
          <<" Expected to use "<<buf.size()
          <<" but used "<<s_buf.first
          <<". Probably need to rethink the communication trigger logic."
          <<" Maybe nComponents is messing this up." <<endl;
      dgm_comm->error(" Response::AllReduce::wait_all: send buffer "
                      "size mismatch.");
    }
  }
}
#endif

//=============================================================================
//                     Response Implementation
//=============================================================================

/// Convert string inputs to enumeration values
void Response::convert_strings_to_enums(ProbeFormat &format,
                                        ProbeFiles  &filetype,
                                        StorageType &probe_mem,
                                        const string &prbfmt,
                                        const string &prbfls,
                                        const string &storage,
                                        const DGM::Comm::Ptr comm) {
  format   = ASCII;
  filetype = SEPARATE;
  const string fmt = lowerCase(prbfmt);
  const string fls = lowerCase(prbfls);
  const string pms = lowerCase(storage);
  if      ( fmt.empty()            ) { format = ASCII;  filetype = SEPARATE; }
  else if (!fmt.compare("ascii")   ) { format = ASCII;  filetype = SEPARATE; }
  else if (!fmt.compare("binary")  ) { format = DOUBLE; filetype = SEPARATE; }
  else if (!fmt.compare("combined")) { format = DOUBLE; filetype = COMBINED; }
  else if (!fmt.compare("double")  ) { format = DOUBLE; filetype = COMBINED; }
  else if (!fmt.compare("float")   ) { format = FLOAT;  filetype = COMBINED; }
  else {
    comm->cout() << "Requested Response probe format = " << prbfmt << endl;
    comm->error("Unknown Response probe format. Use ascii, double or float");
  }
  if (!fls.empty() && fls.compare("default")) {
    if     (!fls.compare("separate")) filetype = SEPARATE;
    else if(!fls.compare("combined")) filetype = COMBINED;
    else {
      comm->cout() << "Requested Response probe files = " << prbfls << endl;
      comm->error("Unknown Response probe format. Use separate or combined");
    }
  }
  if      ( pms.empty())                       probe_mem = WHERE_NEEDED;
  else if (!pms.compare("where_needed") ||
           !pms.compare("where needed"))       probe_mem = WHERE_NEEDED;
  else if (!pms.compare("proc_with_center") ||
           !pms.compare("proc with center"))   probe_mem = PROC_WITH_CENTER;
  else if (!pms.compare("evenly_distributed") ||
           !pms.compare("evenly distributed")) probe_mem = EVENLY_DISTRIBUTED;
  else {
    comm->cout() << "Requested Response probe memory storage = "
                 << storage << endl;
    comm->error("Unknown Response probe format. Use 'WHERE_NEEDED', "
               "'PROC_WITH_CENTER' or 'EVENLY_DISTRIBUTED'",1);
  }
}

/// Old style factory based on DGM parameter list
Response* Response::factory(const vField &F,
                            const string &fname_node,
                            Table &params,
                            const DGM::Comm::Ptr comm) {
  string prbfmt, prbfls, storage;
  bool prbtrn = false;
  bool prbffl = false;
  bool prbtrc = true;
  unsigned prbblk = 1;
  unsigned opnfls = 1;
  Scalar   time_s = 0;
  Scalar   time_p = 0;
  Ordinal  time_n = 0;
  int      verb   = 0;
  const string fmt("prbfmt");
  const string fls("prbfls");
  const string blk("prbblocksize");
  const string pdt("prbdt");
  const string pln("prblen");
  const string trn("prbtrans");
  const string ffl("prbfflush");
  const string trc("prbtimetrace");
  const string opn("prbopenfiles");
  const string pms("prbmemorystorage");
  const string vrb("prbverbosity");
  const string dt("dt");

  if (!params.defined("root"))
    throw DGM::exception("root not defined in params");

  const string root = (string)params["root"];

  // set the defaults in the parameter table
  params[fmt] = "ASCII";               // format for probe outputs
  params[fls] = "DEFAULT";             // format for probe outputs
  params[blk] = 1;                     // Block size for I/O
  params[pdt] = 0.0;                   // probe time step
  params[pln] = 0;                     // probe length
  params[trn] = 0;                     // transpose output
  params[ffl] = 0;                     // flush output on write
  params[trc] = 1;                     // include time trace on input
  params[opn] = 1;                     // number of open files
  params[pms] = "WHERE_NEEDED";        // memory layout
  params[vrb] = 0;                     // verbosity

  // update values from input file
  params.read( root+".inp", fmt );
  params.read( root+".inp", fls );
  params.read( root+".inp", blk );
  params.read( root+".inp", pdt );
  params.read( root+".inp", pln );
  params.read( root+".inp", trn );
  params.read( root+".inp", ffl );
  params.read( root+".inp", trc );
  params.read( root+".inp", opn );
  params.read( root+".inp", pms );
  params.read( root+".inp", vrb );

  if (params.defined(fmt)) prbfmt = (string)params.get(fmt);
  if (params.defined(fls)) prbfls = (string)params.get(fls);
  if (params.defined(blk)) prbblk = (unsigned)params.get(blk);
  if (params.defined(pms)) storage = (string)params.get(pms);
  if (params.defined(trn)) prbtrn = (bool)params.get(trn);
  if (params.defined(ffl)) prbffl = (bool)params.get(ffl);
  if (params.defined(trc)) prbtrc = (bool)params.get(trc);
  if (params.defined(opn)) opnfls = (unsigned)params.get(opn);
  if (params.defined(dt))  time_s = (Scalar)params.get(dt);
  if (params.defined(pdt)) time_p = (Scalar)params.get(pdt);
  if (params.defined(pln)) time_n = (Ordinal)params.get(pln);
  if (params.defined(vrb)) verb   = (int)params.get(vrb);
  if (prbtrn && !params.defined(trc)) prbtrc = false;

  ProbeFormat format;
  ProbeFiles  filetype;
  StorageType stortype;
  convert_strings_to_enums(format, filetype,stortype, prbfmt, prbfls,
                           storage, comm);

  Response *response = new Response( F, fname_node, comm, format, filetype,
                                     prbblk, prbffl, prbtrn, prbtrc, opnfls,
                                     time_s, time_p, time_n,
                                     stortype, verb );
  return response;
}

#ifdef DGM_USE_JSON

/** This version requires a Response block in the Domain or defaults to
    root.anl file. */
Response* Response::factory(const vField &F,
                            Domain *const domain) {
  // fall back to the old-style approach if there is no Response block
  if (!domain->json_domain.isMember("Response"))
    return factory(F, domain->root+".anl", domain->params, domain->get_comm());
  Json::Value &resp = domain->json_domain["Response"];
  return factory(F, domain, resp);
}

// experimental code that could be added to Json
namespace {

/// Determine if it is a string (file) or an object
/** If the value is an object just return.  If the value is a string then
 *  read and parse json from that file into the object and return.
 */
Json::Value & jsonObjectOrFile(Json::Value &json, const DGM::Comm::Ptr comm) {
  if (json.isString()) {
    const string name = json.asString();
    // if file exist, read from the file pointed to by the string, parse into
    // a Json::Value and return
    if (comm->Master()) {
      comm->cout()<<"  Reading from "<<name<<endl;
      ifstream in(name.c_str());
      if (!in) comm->error("Cannot read Json block from "+name);
      Json::Reader reader;
      bool parsingSuccessful = reader.parse(in,json,true);
      if (!parsingSuccessful)
        comm->error("Could not parse input from "+name+"\n"+
                    reader.getFormatedErrorMessages());
    }
    Json::broadcast(comm,json);
  } else if (!json.isObject()) {
    comm->error("Json block must be either an object or a string");
  }
  return json;
}

} // anonymous namespace

/** Attempt to do this better by passing the Domain that this Response
    observes.  If needed, all parameters from the Domain can be accessed. */
Response* Response::factory(const vField &F,
                            const Domain *const domain,
                            Json::Value &resp) {
  const DGM::Comm::Ptr comm = domain->get_comm();

  // if resp is a string then read and parse json from a file with that name
  jsonObjectOrFile(resp,comm);

  // Set default values
  const int      verb    = resp.get("Verbosity", 1).asInt();
  const string   prbfmt  = resp.get("Format", "ascii").asString();
  const string   prbfls  = resp.get("Type", "default").asString();
  const unsigned prbblk  = resp.get("Write block size" ,1).asUInt();
  const string   storage = resp.get("Memory storage","where needed").asString();
  const bool     prbffl  = resp.get("Flush on write", false).asBool();
  const bool     prbtrn  = resp.get("Transposed", false).asBool();
  const bool     prbtrc  = resp.get("Time trace", true).asBool();
  const unsigned opnfls  = resp.get("Max open files", 1).asUInt();
  const Scalar   time_p  = resp.get("Time sample increment",0.0).asDouble()!=0 ?
                           resp.get("Time sample increment",0.0).asDouble()    :
                           resp.get("Time step", 0.0).asDouble();
  const Ordinal  time_n  = resp.get("Number of samples", 0).asUInt();

  if (resp.isMember("Time step")) {
    comm->cout() << "Response parameter: \"Time step\" is deprecated.\n"
                 << "Use: \"Time sample increment\" instead." << endl;
  }
  Scalar time_s = domain->get_dt();
  if (resp.isMember("Simulation time step")) {   // deprecated syntax
    line(comm->cout());
    comm->cout() << "WARNING:  Response::factory: \"Simulation time step\" in "
                    "the Response block\nof the Json input file is deprecated "
                    "and will be ignored."<<endl;
    line(comm->cout());
  }
  if (verb>1) {
    Json::StyledWriter writer;
    string output = writer.write(resp);
    comm->cout() << "Response parameters:\n" << output;
  }
  ProbeFormat format;
  ProbeFiles filetype;
  StorageType pms;
  convert_strings_to_enums(format,filetype,pms,prbfmt,prbfls,storage,comm);
  Response *response=0;
  if ( resp.isMember("Filename") && resp.isMember("Probes") )
    comm->error("Response::factor: \"Filename\" and \"Probes\" cannot both "
                "be present in the Json \"Response\" block");
  if ( resp.isMember("Filename") ) {
    const string fname = resp["Filename"].asString();
    response = new Response( F, fname, comm, format, filetype,
                             prbblk, prbffl, prbtrn, prbtrc, opnfls,
                             time_s, time_p, time_n, pms, verb );
  } else if ( resp.isMember("Probes") ) {
    response = new Response( F, resp, comm, format, filetype,
                             prbblk, prbffl, prbtrn, prbtrc, opnfls, time_s,
                             time_p, time_n, pms, verb );
  } else {
    comm->error("Response::factory: either \"Probes\" or \"Filename\" must "
        "be present in the \"Response\" Json block");
  }
  return response;
}

Response* Response::factory(const vField &F,
                            const dMatrix &xyz,
                            Json::Value &resp,
                            const Domain *const domain) {
  const DGM::Comm::Ptr comm = domain->get_comm();

  string prbfmt, prbfls, storage;
  bool prbtrn = false;
  bool prbffl = false;
  bool prbtrc = true;
  unsigned prbblk = 1;
  unsigned opnfls = 1;
  Scalar   time_s = 0;
  Scalar   time_p = 0;
  Ordinal  time_n = 0;

  const string fmt("Format");
  const string fls("Type");
  const string trn("Transposed");
  const string ffl("Flush on write");
  const string trc("Time trace");
  const string blk("Write block size");
  const string opn("Max open files");
  const string sdt("Simulation time step");
  const string tsi("Time sample increment");
  const string  ts("Time step");
  const string pln("Number of samples");
  const string pms("Memory storage");

  prbfmt = resp.get(fmt,"ascii").asString();
  prbfls = resp.get(fls,"default").asString();
  storage= resp.get(pms,"where needed").asString();
  prbtrn = resp.get(trn,prbtrn).asBool();
  prbffl = resp.get(ffl,prbffl).asBool();
  prbtrc = resp.get(trc,prbtrc).asBool();
  prbblk = resp.get(blk,prbblk).asUInt();
  opnfls = resp.get(opn,opnfls).asUInt();
  time_s = domain->get_dt();
  if (resp.isMember("Simulation time step")) {   // deprecated syntax
    line(comm->cout());
    comm->cout() << "WARNING:  Response::factory: \"Simulation time step\" in "
                    "the Response block\nof the Json input file is deprecated "
                    "and will be ignored."<<endl;
    line(comm->cout());
  }
  time_p = resp.get(tsi,time_p).asDouble()!=0 ?
           resp.get(tsi,time_p).asDouble()    :
           resp.get(ts,time_s).asDouble();
  time_n = resp.get(pln,time_n).asUInt();

  if (resp.isMember(ts)) {
    comm->cout() << "Response parameter: \"Time step\" is deprecated.\n"
                 << "  Use: \"Time sample increment\" instead." << endl;
  }
  const int verb = resp.get("Verbosity",0).asInt();
  if (verb) {
    Json::StyledWriter writer;
    string output = writer.write(resp);
    comm->cout() << "Response parameters:\n" << output;
  }

  ProbeFormat format;
  ProbeFiles  filetype;
  StorageType storagetype;
  convert_strings_to_enums(format, filetype, storagetype,
                           prbfmt, prbfls, storage, comm);

  Response *response = new Response( F, xyz, comm, format, filetype,
                                     prbblk, prbffl, prbtrn, prbtrc, opnfls,
                                     time_s, time_p, time_n,
                                     storagetype, verb );
  return response;
}
#endif  // DGM_USE_JSON

namespace {

string nameOrEmpty(const string&name) {
  return name.empty() ? "<unnamed>" : name;
}

string quoted(const string &str) {
  return "\""+str+"\"";
}

#ifdef DGM_PARALLEL

/// Archive for Response file data to make broadcast easier
class ResponseArchive {
  dMatrix &xyz;
  vector< vector<Size> > &elem;
  vector<string> &nid;
public:
  ResponseArchive(dMatrix &xyz_,
                  vector< vector<Size> > &elem_,
                  vector<string> &nid_
                  ) : xyz(xyz_), elem(elem_), nid(nid_) { }
  friend class boost::serialization::access;
  template<class Archive>
  void serialize(Archive &ar, const unsigned int version) {
    ar & xyz & elem & nid;
  }
};

/// Read the Response file (typically root.anl)
/** This version uses MPI communication so that only the master rank
 *  reads and then the data is serialized and broadcast.
 */
bool read_response_file(const string &fname_node,
                        dMatrix &xyz,
                        vector< vector<Size> > &elem,
                        vector<string> &nid,
                        Ordinal &nFileProbes,
                        const Ordinal &nsd,
                        const DGM::Comm::Ptr comm,
                        const int verb)  {
  Ordinal glen = 0;
  Ordinal lnsd = nsd;

  // Read node information
  ifstream nodes(fname_node.c_str());
  if (!nodes) return false;
  string buffer;
  if (comm->Master()) {
    getline(nodes, buffer);       // eat the comment
    nodes>>glen>>lnsd;
  }
  comm->Broadcast(&glen);
  comm->Broadcast(&lnsd);

  if (lnsd != nsd)
    comm->error("Inconsistent value of nsd = "+asString(lnsd)+" in "+
                fname_node+" when problem has nsd = "+asString(nsd));

  nFileProbes += glen;

  if (verb>1)
    comm->cout() << "  Response:: Number of point probes = " << glen
                 <<", Dimension = " << nsd << endl;
  xyz.resize(glen,nsd);
  elem.resize(glen);
  nid.resize(glen);
  if (comm->Master()) {
    getline(nodes, buffer);       // Reads column identifier line
    getline(nodes, buffer);       // First line of probe point info
    Ordinal nelmts;
    for (Ordinal i=0; i<glen; i++) {
      nodes >> nid[i];            // nodal ID
      if (nodes.eof())
        comm->error("Response::read_response_file: found end of root.anl \n"
                    "before specified number of probes were read:"+
                    asString(glen));
      for (Ordinal j=0; j<nsd; j++) {
        nodes >> xyz[i][j];
      }
      nodes >> nelmts;            // number of elements that this node is in
      elem[i].resize(nelmts);
      for (Ordinal j=0; j<nelmts; ++j) nodes >> elem[i][j];
      getline(nodes, buffer);     // eat the rest of the line
    }
#ifdef DGM_RESPONSE_DEBUG
    for (int i=0; i<glen; i++) {
      cout << nid[i] << " " <<xyz[i][0] << " "
          << xyz[i][1] << " " << xyz[i][2];
      for (int j=0; j<elem[i].size(); j++)
        cout << " " << elem[i][j];
      cout << endl;
    }
#endif
  }
  CMC::Stopwatch cpu; cpu.start();
  if (verb) comm->cout() << "  Starting serialization..." << endl;
#ifdef DGM_RESPONSE_USE_BOOST_SERIALIZATION
  if (verb) comm->cout() << "    Using Boost serialization..." << endl;
  boost::mpi::communicator bcomm
    (dynamic_cast<const DGM::MpiComm*>(comm.get())->mpi_comm,
     boost::mpi::comm_attach);
  ResponseArchive data(xyz,elem,nid);
  broadcast(bcomm, data, 0);
#else
  comm->Barrier();

  vector<size_t> slen(glen);
  string sstr;
  if (comm->Master()) {
    for (Ordinal i=0; i<glen; i++) {
      sstr  += nid[i];
      slen[i] = nid[i].size();
    }
  }
  comm->Broadcast(&slen[0], glen);

  size_t sstr_len = 0;
  for (Ordinal i=0; i<glen; i++) sstr_len += slen[i];
  char *sbuf = new char[sstr_len];
  if (comm->Master())
        sstr.copy(sbuf, sstr_len);
  comm->Broadcast(sbuf, sstr_len);
  sstr.assign    (sbuf, sstr_len);
  delete[] sbuf;
  size_t pos = 0;
  for (Ordinal i=0; i<glen; i++) {
    nid[i] = sstr.substr(pos,slen[i]);
    pos += slen[i];
  }
  vector<Ordinal> elem_len(glen);
  for (Ordinal i=0; i<glen; i++) elem_len[i] = elem[i].size();
  comm->Broadcast(&elem_len[0], glen);

  Ordinal tot_len = 0;
  for (Ordinal i=0; i<glen; i++) tot_len += elem_len[i];
  vector<Size> ebuf(tot_len);
  if (comm->Master()) {
    for (Ordinal i=0,k=0; i<glen; ++i)
      for (Ordinal j=0; j<elem_len[i]; ++j)
        ebuf[k++] = elem[i][j];
  }
  comm->Broadcast(&ebuf[0], tot_len);
  for (Ordinal i=0,k=0; i<glen; ++i) {
    elem[i].resize(elem_len[i]);
    for (Ordinal j=0; j<elem_len[i]; ++j)
      elem[i][j] = ebuf[k++];
  }
  comm->Broadcast(xyz.data(), xyz.size());
#endif
  if (verb) comm->cout() << "  Finished serialization " << cpu.stop()
                         << " seconds." << endl;
  return true;
}

#else

/// Read the Response file (typically root.anl) old serial version
/** This can be really slow in parallel since all ranks read the ASCII file
 *  simultaneously.  This version is now deprecated in terms of the parallel
 *  and serialized broadcast version above.
 */
bool read_response_file(const string &fname_node,
                        dMatrix &xyz,
                        vector< vector<Size> > &elem,
                        vector<string> &nid,
                        Ordinal &nFileProbes,
                        const Ordinal &nsd,
                        const DGM::Comm::Ptr comm,
                        const int verb)  {
  // Read node information
  Ordinal glen = 0;
  ifstream nodes(fname_node.c_str());
  if (!nodes) return false;
  string buffer;
  getline(nodes, buffer);       // eat the comment
  Ordinal lnsd=0;
  nodes>>glen>>lnsd;
  if (lnsd != nsd) comm->error("Illegal value of nsd in file "+fname_node);
  nFileProbes += glen;
  if (verb>1)
    comm->cout() << "  Response:: Number of nodes = " << glen
                 <<", Dimension = " << nsd << endl;
  const Ordinal lglen = numeric_cast<Ordinal>(glen);
  xyz.resize(lglen,nsd);
  elem.resize(numeric_cast<size_t>(glen));
  nid.resize(lglen);
  getline(nodes, buffer);       // Reads column identifier line
  getline(nodes, buffer);       // First line of probe point info
  Ordinal nelmts;
  for (Ordinal i=0; i<lglen; i++) {
    nodes >> nid[i];            // nodal ID
    if (nodes.eof())
      comm->error("Response::read_response_file: "
                  "found end of root.anl before specified number of "
                  "probes were read:"+asString(glen));
    for (Ordinal j=0; j<nsd; j++) {
      nodes >> xyz[i][j];
    }
    nodes >> nelmts;            // number of elements that this node is in
    elem[i].resize(nelmts);
    for (Ordinal j=0; j<nelmts; ++j) nodes >> elem[i][j];
    getline(nodes, buffer);     // eat the rest of the line
  }
#ifdef DGM_RESPONSE_DEBUG
  for (int i=0; i<glen; i++) {
    cout << nid[i] << " " <<xyz[i][0] << " "
        << xyz[i][1] << " " << xyz[i][2];
    for (int j=0; j<elem[i].size(); j++)
      cout << " " << elem[i][j];
    cout << endl;
  }
#endif
  return true;
}

#endif // DGM_PARALLEL

/// Parse a json value for point probes
bool parse_json_point_parameters(const Json::Value &json,
                                 const string &probeName,
                                 dMatrix &xyz,
                                 vector< vector<Size> > &elem,
                                 vector<string> &nid,
                                 Ordinal &nFileProbes,
                                 const Ordinal &nsd,
                                 const DGM::Comm::Ptr comm,
                                 const int verb) {
  // setup locations
  if (!json.isMember("Locations"))
    comm->error("Json file must have \"Locations\"");
  if (!json["Locations"].isArray())
    comm->error("\"Locations\" must be an array");
  Ordinal glen = numeric_cast<Ordinal>(json["Locations"].size());
  nFileProbes += glen;
  xyz.resize(glen,nsd);
  elem.resize(glen);
  nid.resize(glen);
  for (Ordinal i=0; i<glen; ++i) {
    if (json["Locations"][i].size() != numeric_cast<Json::ArrayIndex>(nsd))
      comm->error("\"Locations\" at index "+asString(i)+" not of length "
                  "nsd = "+asString(nsd));
    for (Ordinal j=0; j<nsd; ++j)
      xyz[i][j] = json["Locations"][i][j].asDouble();
  }
  // setup names
  if (json.isMember("Names")) {
    Json::Value names = json.get("Names", 0);
    if  (!names.isArray())
      comm->error("Response::parse_json_point_parameters: "
                  "'Names' is not an ARRAY of names "
                  " (in square brackets).");
    if (glen != static_cast<Ordinal>(names.size()))
      comm->error("Response::parse_json_point_parameters: "
                  "'Names' is not the same length as 'Xs'.");
    size_t n=0;
    for (Json::ValueIterator name=names.begin(); name!=names.end(); ++name,++n)
      nid[n] = probeName+(*name).asString();
  } else {
    for (Ordinal n=0; n<glen; ++n) nid[n] = probeName+asString(n);
  }
  // setup element ids
  if (json.isMember("Elements")) {
    Json::Value elements = json.get("Elements", 0);
    if  (!elements.isArray())
      comm->error("Response::parse_json_point_parameters: "
                  "'Elements' is not an ARRAY of ARRAYS of element numbers."
                  " (square brackets in square brackets)");
    if (glen != static_cast<Ordinal>(elements.size()))
      comm->error("Response::parse_json_point_parameters: "
                  "'Elements' is not the same length as 'Xs'.");
    Ordinal n=0;
    for (Json::ValueIterator el=elements.begin();el!=elements.end();++el,++n) {
      const Json::Value elm = *el;
      if (!elm.isArray())
        comm->error("Response::parse_json_point_parameters: "
                    "'Elements' is not an ARRAY of ARRAYS of element numbers."
                    " (square brackets in square brackets)");
      const Ordinal nelmts = static_cast<Ordinal>(elm.size());
      elem[n].resize(nelmts);
      Ordinal i=0;
      for (Json::ValueIterator e=elm.begin(); e!=elm.end(); ++e,++i)
        elem[n][i] = numeric_cast<Size>((*e).asLargestUInt());
    }
  }
  return true;
}

// Read point parameters from various file formats
bool read_file_point_parameters(Json::Value            &json,
                                const string           &probeName,
                                dMatrix                &xyz,
                                vector< vector<Size> > &elem,
                                vector<string>         &nid,
                                Ordinal                &nFileProbes,
                                const Ordinal          &nsd,
                                const DGM::Comm::Ptr   comm,
                                const int              verb)
{
  bool valid=true;
  const string fname = json.get("File", "").asString();
  const string format = json.get("Format","Text").asString();
  if (lowerCase(format) == "text") {
    CMC::Stopwatch cpu; cpu.start();
    valid = read_response_file(fname, xyz, elem, nid, nFileProbes,
                               nsd, comm, verb);
    if (!valid) comm->error("  Failed to read response file = "+fname);
    for (size_t n=0; n<nid.size(); ++n) nid[n] = probeName+asString(n);
    if (verb>1)
      comm->cout()<<"  Read response file in "<<cpu.stop()
                  <<" seconds."<<endl;
  } else if (lowerCase(format) == "json") {
    Json::Value anl;
    if (comm->Master()) {
      ifstream in(fname.c_str());
      if (in) {
        Json::Reader reader;
        if (!reader.parse(in,anl,true)) {
          comm->error("Failed to parse the json input file " + fname +
                      ":  " + reader.getFormattedErrorMessages());
        }
      }
    }
    Json::broadcast(comm,anl);
    valid = parse_json_point_parameters(anl, probeName, xyz, elem, nid,
                                        nFileProbes, nsd, comm, verb);
  } else {
    comm->error("Response::Response(json): probe file \"Format\" "+
                quoted(format)+" not supported.");
  }
  return valid;
}

// Read json point parameters
bool read_json_point_parameters(Json::Value            &parameters,
                                dMatrix                &xyz,
                                vector< vector<Size> > &elem,
                                vector<string>         &nid,
                                Ordinal                &glen,
                                const Ordinal          &nsd,
                                const DGM::Comm::Ptr   comm,
                                const int              verb) {
  if (!parameters.isMember("Xs"))
    comm->error("Response::read_json_point_parameters: "
                "'Xs' is not present in Probe block.");
  const Json::Value xs = parameters.get("Xs", 0);
  if  (!xs.isArray())
    comm->error("Response::read_json_point_parameters: "
                "'Xs' is not an ARRAY of coordinates "
                " (in square brackets).");
  glen = static_cast<Ordinal>(xs.size());
  const Ordinal lglen = numeric_cast<Ordinal>(glen);

  if (verb>1) comm->cout()<<"  Response:: Number of nodes = "<<glen<<endl;
  xyz.resize(lglen, nsd);
  elem.resize(lglen);
  nid.resize(lglen);

  Ordinal n=0;
  for (Json::ValueIterator x=xs.begin(); x!=xs.end(); ++x,++n)
    xyz[n][0] = (*x).asDouble();

  if (1 < nsd) {
    if (!parameters.isMember("Ys"))
      comm->error("Response::read_json_point_parameters: "
                  "'Ys' is not present in Probe block.");
    Json::Value ys = parameters.get("Ys", 0);
    if  (!ys.isArray())
      comm->error("Response::read_json_point_parameters: "
                  "'Ys' is not an ARRAY of coordinates "
                  " (in square brackets).");
    if (glen != static_cast<Ordinal>(ys.size()))
      comm->error("Response::read_json_point_parameters: "
                  "'Ys' is not the same length as 'Xs'.");

    Ordinal n=0;
    for (Json::ValueIterator y=ys.begin(); y!=ys.end(); ++y,++n)
      xyz[n][1] = (*y).asDouble();
  }
  if (2 < nsd) {
    if (!parameters.isMember("Zs"))
      comm->error("Response::read_json_point_parameters: "
                  "'Zs' is not present in Probe block.");
    Json::Value zs = parameters.get("Zs", 0);
    if  (!zs.isArray())
      comm->error("Response::read_json_point_parameters: "
                  "'Zs' is not an ARRAY of coordinates "
                  " (in square brackets).");
    if (glen != static_cast<Ordinal>(zs.size()))
      comm->error("Response::read_json_point_parameters: "
                  "'Zs' is not the same length as 'Xs'.");

    Ordinal n=0;
    for (Json::ValueIterator z=zs.begin(); z!=zs.end(); ++z,++n)
      xyz[n][2] = (*z).asDouble();
  }

  string probeName = "";
  if (parameters.isMember("Name")) {
    if (!parameters["Name"].isString())
      comm->error("Response::Probe::Name must be a string");
     probeName = parameters["Name"].asString();
  }
  if (parameters.isMember("Names")) {
    Json::Value names = parameters.get("Names", 0);
    if  (!names.isArray())
      comm->error("Response::read_json_point_parameters: "
                  "'Names' is not an ARRAY of names "
                  " (in square brackets).");
    if (glen != static_cast<Ordinal>(names.size()))
      comm->error("Response::read_json_point_parameters: "
                  "'Names' is not the same length as 'Xs'.");

    size_t n=0;
    for (Json::ValueIterator name=names.begin(); name!=names.end(); ++name,++n)
      nid[n] = probeName+(*name).asString();

  } else {
    for (Ordinal n=0; n<glen; ++n) nid[n] = probeName+asString(n);
  }

  if (parameters.isMember("Elements")) {
    Json::Value elements = parameters.get("Elements", 0);
    if  (!elements.isArray())
      comm->error("Response::read_json_point_parameters: "
                  "'Elements' is not an ARRAY of ARRAYS of element numbers."
                  " (square brackets in square brackets)");
    if (glen != static_cast<Ordinal>(elements.size()))
      comm->error("Response::read_json_point_parameters: "
                  "'Elements' is not the same length as 'Xs'.");
    Ordinal n=0;
    for (Json::ValueIterator el=elements.begin();
         el!=elements.end(); ++el,++n) {
      const Json::Value elm = *el;
      if  (!elm.isArray())
        comm->error("Response::read_json_point_parameters: "
                    "'Elements' is not an ARRAY of ARRAYS of element numbers."
                    " (square brackets in square brackets)");
      const Ordinal nelmts = static_cast<Ordinal>(elm.size()) ;
      elem[n].resize(nelmts);

      Ordinal i=0;
      for (Json::ValueIterator e=elm.begin(); e!=elm.end(); ++e,++i)
        elem[n][i] = numeric_cast<Size>((*e).asLargestUInt());
    }
  }
#ifdef DGM_RESPONSE_DEBUG
  for (int i=0; i<glen; i++) {
    cout << nid[i] << " " <<xyz[i][0] << " "
        << xyz[i][1] << " " << xyz[i][2];
    for (int j=0; j<elem[i].size(); j++)
      cout << " " << elem[i][j];
    cout << endl;
  }
#endif
  return true;
}

bool read_json_ellipse_parameters(Json::Value            &parameters,
                                  dMatrix                &xyz,
                                  dMatrix                &sigma,
                                  iMatrix                &der,
                                  vector<dMatrix>        &dir,
                                  vector<string>         &nid,
                                  Ordinal                &glen,
                                  const Json::Value      &kernel,
                                  const Ordinal          &nsd,
                                  const DGM::Comm::Ptr   comm,
                                  const int              verb)
{
  vector<Scalar>  X(3,numeric_limits<Scalar>::max());
  vector<Scalar> DX(3,numeric_limits<Scalar>::max());

  if (parameters.isMember("X0") && !parameters.isMember("DX"))
      comm->error("Response::read_json_ellipse_parameters: "
                  "'X0' is present in Probe block but no DX.");

  if (parameters.isMember("X0") && !parameters.isMember("Number of Receivers"))
      comm->error("Response::read_json_ellipse_parameters: "
                  "'X0' is present in Probe block but no "
                  "'Number of Receivers'.");

  if (parameters.isMember("Y0") && !parameters.isMember("DY"))
      comm->error("Response::read_json_ellipse_parameters: "
                  "'Y0' is present in Probe block but no DY.");

  if (1<nsd && parameters.isMember("X0") && !parameters.isMember("Y0"))
      comm->error("Response::read_json_ellipse_parameters: 'X0' is present "
                  "'Y0' is not present in Probe block and 1 < nsd.");

  if (parameters.isMember("Z0") && !parameters.isMember("DZ"))
      comm->error("Response::read_json_ellipse_parameters: "
                  "'Z0' is present in Probe block but no DZ.");

  if (2<nsd && parameters.isMember("X0") && !parameters.isMember("Z0"))
      comm->error("Response::read_json_ellipse_parameters: 'X0' is present "
                  "'Z0' is not present in Probe block and 2 < nsd.");

  if (parameters.isMember("X0") && parameters.isMember("Xs"))
      comm->error("Response::read_json_ellipse_parameters: "
                  "'X0' is present in Probe block but so is Xs."
                  " Can not have both.");

  if (!parameters.isMember("Xs") && !parameters.isMember("Number of Receivers"))
    comm->error("Response::read_json_ellipse_parameters: "
                "'Xs' or 'Number of Receivers' must be specified "
                "in Probe block.");

  if (parameters.isMember("X0")) {
    X[0] = parameters.get("X0",0).asDouble();
    if (parameters.isMember("Y0")) {
      X[1] = parameters.get("Y0",0).asDouble();
      if (parameters.isMember("Z0")) {
        X[2] = parameters.get("Z0",0).asDouble();
      }
    }
  }
  if (parameters.isMember("DX")) {
    DX[0] = parameters.get("DX",0).asDouble();
    if (parameters.isMember("DY")) {
      DX[1] = parameters.get("DY",0).asDouble();
      if (parameters.isMember("DZ")) {
        DX[2] = parameters.get("DZ",0).asDouble();
      }
    }
  }

  if (parameters.isMember("Xs")) {
    const Json::Value xs = parameters.get("Xs", 0);
    if  (!xs.isArray())
      comm->error("Response::read_json_ellipse_parameters: "
                  "'Xs' is not an ARRAY of coordinates "
                  " (in square brackets).");
    glen = static_cast<Ordinal>(xs.size());
    if (!glen)
      comm->error("Response::read_json_ellipse_parameters: "
                  "'Xs' is a zero length array.");
  } else {
    const Json::Value n = parameters.get("Number of Receivers", 0);
    glen = static_cast<Ordinal>(n.asUInt());
    if (!glen)
      comm->error("Response::read_json_ellipse_parameters: "
                  "'Number of Receivers' is zero.");
  }

  if (verb>1) comm->cout()<<"  Response:: Number of nodes = "<<glen<<endl;
  const Ordinal lglen = numeric_cast<Ordinal>(glen);
  xyz.resize(lglen, nsd);
  der.resize(lglen, nsd);
  sigma.resize(lglen, nsd);
  nid.resize(numeric_cast<size_t>(glen));
  dir.resize(numeric_cast<size_t>(glen));
  xyz = numeric_limits<Scalar>::max();
  der = 0;
  sigma = 0;
  for (Ordinal i=0; i<lglen; ++i) dir[i].resize(3,3);
  for (Ordinal i=0; i<lglen; ++i) dir[i] = 0;

  if (parameters.isMember("Xs")) {
    const Json::Value xs = parameters.get("Xs", 0);
    if  (!xs.isArray())
      comm->error("Response::read_json_ellipse_parameters: "
                  "'Xs' is not an ARRAY of coordinates "
                  " (in square brackets).");
    Ordinal n=0;
    for (Json::ValueIterator x=xs.begin(); x!=xs.end(); ++x,++n)
      xyz[n][0] = (*x).asDouble();
    if (1 < nsd) {
      if (!parameters.isMember("Ys"))
        comm->error("Response::read_json_ellipse_parameters: "
                    "'Ys' is not present in Probe block.");
      Json::Value ys = parameters.get("Ys", 0);
      if  (!ys.isArray())
        comm->error("Response::read_json_ellipse_parameters: "
                    "'Ys' is not an ARRAY of coordinates "
                    " (in square brackets).");
      if (glen != static_cast<Ordinal>(ys.size()))
        comm->error("Response::read_json_ellipse_parameters: "
                    "'Ys' is not the same length as 'Xs'.");

      Ordinal n=0;
      for (Json::ValueIterator y=ys.begin(); y!=ys.end(); ++y,++n)
        xyz[n][1] = (*y).asDouble();
    }
    if (2 < nsd) {
      if (!parameters.isMember("Zs"))
        comm->error("Response::read_json_ellipse_parameters: "
                      "'Zs' is not present in Probe block.");
      Json::Value zs = parameters.get("Zs", 0);
      if  (!zs.isArray())
        comm->error("Response::read_json_ellipse_parameters: "
                    "'Zs' is not an ARRAY of coordinates "
                    " (in square brackets).");
      if (glen != static_cast<Ordinal>(zs.size()))
        comm->error("Response::read_json_ellipse_parameters: "
                    "'Zs' is not the same length as 'Xs'.");

      Ordinal n=0;
      for (Json::ValueIterator z=zs.begin(); z!=zs.end(); ++z,++n)
        xyz[n][2] = (*z).asDouble();
    }
  } else {
    for (Ordinal n=0; n<lglen; ++n)
      for (Ordinal i=0; i<nsd; ++i)
        xyz[n][i]=X[i]+n*DX[i];
  }

  string type = parameters["Type"].asString();

  string probeName = "";
  if (parameters.isMember("Name")) {
    if (!parameters["Name"].isString())
      comm->error("Response::Probe::Name must be a string");
     probeName = parameters["Name"].asString();
  }
  if (parameters.isMember("Names")) {
    Json::Value names = parameters.get("Names", 0);
    if  (!names.isArray())
      comm->error("Response::read_json_ellipse_parameters: "
                  "'Names' is not an ARRAY of names "
                  " (in square brackets).");
    if (glen != static_cast<Ordinal>(names.size()))
      comm->error("Response::read_json_ellipse_parameters: "
                  "'Names' is not the same as the number of probes:"
                  +asString(glen));
    Ordinal n=0;
    for (Json::ValueIterator name=names.begin(); name!=names.end(); ++name,++n)
      nid[n] = (*name).asString();
  } else {
    for (Ordinal n=0; n<glen; ++n) nid[n] = probeName+asString(n);
  }

  bool haveValidDefaultSigma(false);
  if (kernel.isMember("Default sigma"))
    if (kernel["Default sigma"].size() == numeric_cast<Json::ArrayIndex>(nsd))
      haveValidDefaultSigma = true;

  if (0<nsd && !parameters.isMember("Sigma1")) {
    if (haveValidDefaultSigma) {
      parameters["Sigma1"] = kernel["Default sigma"][0];
    } else {
      comm->error("Response::read_json_ellipse_parameters: "
                  "\"Sigma1\" is not specified and no valid default sigma.");
    }
  }
  if (1<nsd && !parameters.isMember("Sigma2")) {
    if (haveValidDefaultSigma) {
      parameters["Sigma2"] = kernel["Default sigma"][1];
    } else {
      comm->error("Response::read_json_ellipse_parameters: "
                  "\"Sigma2\" is not specified and no valid default sigma.");
    }
  }
  if (2<nsd && !parameters.isMember("Sigma3")) {
    if (haveValidDefaultSigma) {
      parameters["Sigma3"] = kernel["Default sigma"][2];
    } else {
      comm->error("Response::read_json_ellipse_parameters: "
                  "\"Sigma3\" is not specified and no valid default sigma.");
    }
  }
  if (0<nsd) {
    Json::Value sigma1 = parameters["Sigma1"];
    if (sigma1.isDouble()) {
      for (Ordinal n=0; n<glen; ++n) sigma[n][0] = sigma1.asDouble();
    } else if (sigma1.isArray()) {
      if (glen != static_cast<Ordinal>(sigma1.size()))
        comm->error("Response::read_json_ellipse_parameters: "
                    "\"Sigma1\" is not the same as the number of probes: "
                    +asString(glen));
      Ordinal n=0;
      for (Json::ValueIterator sig=sigma1.begin(); sig!=sigma1.end(); ++sig,++n)
        sigma[n][0] = (*sig).asDouble();
    } else
      comm->error("Response::read_json_ellipse_parameters: "
                  "\"Sigma1\" is not an ARRAY of doubles "
                  " (in square brackets) or a double.");
  }
  if (1<nsd) {
    Json::Value sigma2 = parameters["Sigma2"];
    if (sigma2.isDouble()) {
      for (Ordinal n=0; n<glen; ++n) sigma[n][1] = sigma2.asDouble();
    } else if (sigma2.isArray()) {
      if (glen != static_cast<Ordinal>(sigma2.size()))
        comm->error("Response::read_json_ellipse_parameters: "
                    "\"Sigma2\" is not the same as the number of probes: "
                    +asString(glen));
      Ordinal n=0;
      for (Json::ValueIterator sig=sigma2.begin(); sig!=sigma2.end(); ++sig,++n)
        sigma[n][1] = (*sig).asDouble();
    } else
      comm->error("Response::read_json_ellipse_parameters: "
                  "\"Sigma2\" is not an ARRAY of doubles "
                  " (in square brackets) or a double.");
  }
  if (2<nsd) {
    Json::Value sigma3 = parameters["Sigma3"];
    if (sigma3.isDouble()) {
      for (Ordinal n=0; n<glen; ++n) sigma[n][2] = sigma3.asDouble();
    } else if (sigma3.isArray()) {
      if (glen != static_cast<Ordinal>(sigma3.size()))
        comm->error("Response::read_json_ellipse_parameters: "
                    "\"Sigma3\" is not the same as the number of probes: "
                    +asString(glen));
      Ordinal n=0;
      for (Json::ValueIterator sig=sigma3.begin(); sig!=sigma3.end(); ++sig,++n)
        sigma[n][2] = (*sig).asDouble();
    } else
      comm->error("Response::read_json_ellipse_parameters: "
                  "\"Sigma3\" is not an ARRAY of doubles "
                  " (in square brackets) or a double.");
  }

#if 1
  // Setup derivative
  bool haveValidDefaultDer(false);
  if (kernel.isMember("Default derivative")) {
    if (kernel["Default derivative"].size() !=
        numeric_cast<Json::ArrayIndex>(nsd))
      comm->error("Response::Ellipse::Default Derivative wrong size");
    else
      haveValidDefaultDer = true;
  }
  if (parameters.isMember("Derivative")) {
    const Json::Value &jder = parameters["Derivative"];
    if (!jder.isArray())
      comm->error("Response::Probe::Ellipse::Derivative must be an array");
    if (glen != numeric_cast<Ordinal>(jder.size()))
          comm->error("Response::read_json_ellipse_parameters: "
                      "\"Derivative\" is not the same as the number of probes:"
                      +asString(glen));
    if (jder[0].size() != numeric_cast<Json::ArrayIndex>(nsd))
      comm->error("Response::Probe::Ellipse::Derivative elements must be "
                  "an array of size nsd = "+asString(nsd));
    Ordinal n=0;
    for (Json::ValueIterator d=jder.begin(); d!=jder.end(); ++d,++n)
      for (Ordinal i=0; i<nsd; i++)
        der[n][i] = (*d)[i].asUInt();
  } else if (haveValidDefaultDer) {
    for (Ordinal n=0; n<glen; n++)
      for (Ordinal i=0; i<nsd; i++)
        der[n][i] = kernel["Default derivative"][i].asInt();
  }
#else
  // Setup derivative (Old way)
  comm->cout()<<"Starting derivative definitions"<<endl;
  if (0<nsd && parameters.isMember("DerivativeOrder1")) {
    Json::Value der1 = parameters.get("DerivativeOrder1", 0);
    if  (!der1.isArray())
      comm->error("Response::read_json_ellipse_parameters: "
                  "'DerivativeOrder1' is not an ARRAY of integers "
                  " (in square brackets).");
    if (glen != static_cast<Ordinal>(der1.size()))
      comm->error("Response::read_json_ellipse_parameters: "
                  "'DerivativeOrder1' is not the same as the number of probes:"
                  +asString(glen));
    Ordinal n=0;
    for (Json::ValueIterator d=der1.begin(); d!=der1.end(); ++d,++n)
      der[n][0] = (*d).asUInt();
  }
  if (0<nsd && parameters.isMember("DerivativeOrder2")) {
    Json::Value der2 = parameters.get("DerivativeOrder2", 0);
    if  (!der2.isArray())
      comm->error("Response::read_json_ellipse_parameters: "
                  "'DerivativeOrder2' is not an ARRAY of integers "
                  " (in square brackets).");
    if (glen != static_cast<Ordinal>(der2.size()))
      comm->error("Response::read_json_ellipse_parameters: "
                  "'DerivativeOrder2' is not the same as the number of probes:"
                  +asString(glen));
    Ordinal n=0;
    for (Json::ValueIterator d=der2.begin(); d!=der2.end(); ++d,++n)
      der[n][1] = (*d).asUInt();
  }
  if (0<nsd && parameters.isMember("DerivativeOrder3")) {
    Json::Value der3 = parameters.get("DerivativeOrder3", 0);
    if  (!der3.isArray())
      comm->error("Response::read_json_ellipse_parameters: "
                  "'DerivativeOrder3' is not an ARRAY of integers "
                  " (in square brackets).");
    if (glen != static_cast<Ordinal>(der3.size()))
      comm->error("Response::read_json_ellipse_parameters: "
                  "'DerivativeOrder3' is not the same as the number of probes:"
                  +asString(glen));
    Ordinal n=0;
    for (Json::ValueIterator d=der3.begin(); d!=der3.end(); ++d,++n)
      der[n][2] = (*d).asUInt();
  }
#endif

#if 1
  // direction definition (new way)
  bool haveValidDefaultDir(false);
  if (kernel.isMember("Default direction")) {
    if (kernel["Default direction"].size() !=
        numeric_cast<Json::ArrayIndex>(nsd)) {
      comm->error("Default direction wrong size");
    } else {
      for (Ordinal i=0; i<nsd; i++) {
        if (kernel["Default direction"][i].size() !=
            numeric_cast<Json::ArrayIndex>(nsd)) {
          comm->error("Default direction vector wrong size for direction "+
                      asString(i));
        }
      }
      haveValidDefaultDir = true;
    }
  }
  if (parameters.isMember("Direction")) {
    const Json::Value &jdir = parameters["Direction"];
    if (!jdir.isArray())
      comm->error("Response::Probe::Ellipse::Direction must be an array");
    if (numeric_cast<Ordinal>(jdir.size()) != glen)
      comm->error("Response::read_json_ellipse_parameters: "
                  "\"Direction\" is not the same size as the number of probes:"+
                  asString(glen));
    for (Ordinal n=0; n<glen; n++) {
      if (jdir[n].size() != numeric_cast<Json::ArrayIndex>(nsd))
        comm->error("Response::Probe::Ellipse::Direction element "+
                    asString(n)+" must be an array of arrays of size nsd = "+
                    asString(nsd));
      for (Ordinal i=0; i<nsd; i++) {
        if (jdir[n][i].size() != numeric_cast<Json::ArrayIndex>(nsd))
          comm->error("Response::Probe::Ellipse::Direction element "+
                      asString(n)+" for direction "+asString(i)+
                      " must be an array of size nsd = "+asString(nsd));
      }
    }
    Ordinal n=0;
    for (Json::ValueIterator d=jdir.begin(); d!=jdir.end(); ++d, ++n)
      for (Ordinal i=0; i<nsd; i++)
        for (Ordinal j=0; j<nsd; j++)
          dir[n][i][j] = (*d)[i][j].asDouble();
  } else if (haveValidDefaultDir) {
    for (Ordinal n=0; n<glen; n++)
      for (Ordinal i=0; i<nsd; i++)
        for (Ordinal j=0; j<nsd; j++)
          dir[n][i][j] = kernel["Default direction"][i][j].asDouble();
  }
#else
  // direction definition (old way)
  comm->cout()<<"Starting direction definitions"<<endl;
  if (0<nsd && parameters.isMember("Direction1x")) {
    Json::Value dir1x = parameters.get("Direction1x", 0);
    if  (!dir1x.isArray())
      comm->error("Response::read_json_ellipse_parameters: "
                  "'Direction1x' is not an ARRAY of doubles "
                  " (in square brackets).");
    if (glen != static_cast<Ordinal>(dir1x.size()))
      comm->error("Response::read_json_ellipse_parameters: "
                  "'Direction1x' is not the same as the number of probes:"
                  +asString(glen));
    Ordinal n=0;
    for (Json::ValueIterator d=dir1x.begin(); d!=dir1x.end(); ++d,++n)
      dir[n][0][0] = (*d).asDouble();
  }
  if (0<nsd && parameters.isMember("Direction1y")) {
    Json::Value dir1y = parameters.get("Direction1y", 0);
    if  (!dir1y.isArray())
      comm->error("Response::read_json_ellipse_parameters: "
                  "'Direction1y' is not an ARRAY of doubles "
                  " (in square brackets).");
    if (glen != static_cast<Ordinal>(dir1y.size()))
      comm->error("Response::read_json_ellipse_parameters: "
                  "'Direction1y' is not the same as the number of probes:"
                  +asString(glen));
    Ordinal n=0;
    for (Json::ValueIterator d=dir1y.begin(); d!=dir1y.end(); ++d,++n)
      dir[n][0][1] = (*d).asDouble();
  }
  if (0<nsd && parameters.isMember("Direction1z")) {
    Json::Value dir1z = parameters.get("Direction1z", 0);
    if  (!dir1z.isArray())
      comm->error("Response::read_json_ellipse_parameters: "
                  "'Direction1z' is not an ARRAY of doubles "
                  " (in square brackets).");
    if (glen != static_cast<Ordinal>(dir1z.size()))
      comm->error("Response::read_json_ellipse_parameters: "
                  "'Direction1z' is not the same as the number of probes:"
                  +asString(glen));
    Ordinal n=0;
    for (Json::ValueIterator d=dir1z.begin(); d!=dir1z.end(); ++d,++n)
      dir[n][0][2] = (*d).asDouble();
  }

  if (1<nsd && parameters.isMember("Direction2x")) {
    Json::Value dir2x = parameters.get("Direction2x", 0);
    if  (!dir2x.isArray())
      comm->error("Response::read_json_ellipse_parameters: "
                  "'Direction2x' is not an ARRAY of doubles "
                  " (in square brackets).");
    if (glen != static_cast<Ordinal>(dir2x.size()))
      comm->error("Response::read_json_ellipse_parameters: "
                  "'Direction2x' is not the same as the number of probes:"
                  +asString(glen));
    Ordinal n=0;
    for (Json::ValueIterator d=dir2x.begin(); d!=dir2x.end(); ++d,++n)
      dir[n][1][0] = (*d).asDouble();
  }
  if (1<nsd && parameters.isMember("Direction2y")) {
    Json::Value dir2y = parameters.get("Direction2y", 0);
    if  (!dir2y.isArray())
      comm->error("Response::read_json_ellipse_parameters: "
                  "'Direction2y' is not an ARRAY of doubles "
                  " (in square brackets).");
    if (glen != static_cast<Ordinal>(dir2y.size()))
      comm->error("Response::read_json_ellipse_parameters: "
                  "'Direction2y' is not the same as the number of probes:"
                  +asString(glen));
    Ordinal n=0;
    for (Json::ValueIterator d=dir2y.begin(); d!=dir2y.end(); ++d,++n)
      dir[n][1][1] = (*d).asDouble();
  }
  if (1<nsd && parameters.isMember("Direction2z")) {
    Json::Value dir2z = parameters.get("Direction2z", 0);
    if  (!dir2z.isArray())
      comm->error("Response::read_json_ellipse_parameters: "
                  "'Direction2z' is not an ARRAY of doubles "
                  " (in square brackets).");
    if (glen != static_cast<Ordinal>(dir2z.size()))
      comm->error("Response::read_json_ellipse_parameters: "
                  "'Direction2z' is not the same as the number of probes:"
                  +asString(glen));
    Ordinal n=0;
    for (Json::ValueIterator d=dir2z.begin(); d!=dir2z.end(); ++d,++n)
      dir[n][1][2] = (*d).asDouble();
  }

  if (2<nsd && parameters.isMember("Direction3x")) {
    Json::Value dir3x = parameters.get("Direction3x", 0);
    if  (!dir3x.isArray())
      comm->error("Response::read_json_ellipse_parameters: "
                  "'Direction3x' is not an ARRAY of doubles "
                  " (in square brackets).");
    if (glen != static_cast<Ordinal>(dir3x.size()))
      comm->error("Response::read_json_ellipse_parameters: "
                  "'Direction3x' is not the same as the number of probes:"
                  +asString(glen));
    Ordinal n=0;
    for (Json::ValueIterator d=dir3x.begin(); d!=dir3x.end(); ++d,++n)
      dir[n][2][0] = (*d).asDouble();
  }
  if (2<nsd && parameters.isMember("Direction3y")) {
    Json::Value dir3y = parameters.get("Direction3y", 0);
    if  (!dir3y.isArray())
      comm->error("Response::read_json_ellipse_parameters: "
                  "'Direction3y' is not an ARRAY of doubles "
                  " (in square brackets).");
    if (glen != static_cast<Ordinal>(dir3y.size()))
      comm->error("Response::read_json_ellipse_parameters: "
                  "'Direction3y' is not the same as the number of probes:"
                  +asString(glen));
    Ordinal n=0;
    for (Json::ValueIterator d=dir3y.begin(); d!=dir3y.end(); ++d,++n)
      dir[n][2][1] = (*d).asDouble();
  }
  if (2<nsd && parameters.isMember("Direction3z")) {
    Json::Value dir3z = parameters.get("Direction3z", 0);
    if  (!dir3z.isArray())
      comm->error("Response::read_json_ellipse_parameters: "
                  "'Direction3z' is not an ARRAY of doubles "
                  " (in square brackets).");
    if (glen != static_cast<Ordinal>(dir3z.size()))
      comm->error("Response::read_json_ellipse_parameters: "
                  "'Direction3z' is not the same as the number of probes:"
                  +asString(glen));
    Ordinal n=0;
    for (Json::ValueIterator d=dir3z.begin(); d!=dir3z.end(); ++d,++n)
      dir[n][2][2] = (*d).asDouble();
  }
  comm->cout()<<"Finished direction definitions"<<endl;
#endif
  for (Ordinal i=0; i<lglen; ++i)
    for (Ordinal j=0; j<nsd; ++j)
      if (xyz[i][j] == numeric_limits<Scalar>::max())
        comm->error("Response::read_json_ellipse_parameters: "
                    "Error in specification of probe centers."
                    " Probe coordinate unspecified.");

#ifdef DGM_RESPONSE_DEBUG
  for (Ordinal i=0; i<lglen; i++) {
    cout << nid[i] << " " <<xyz[i][0] << " "
        << xyz[i][1] << " " << xyz[i][2];
    cout << endl;
  }
#endif
  return true;
}

bool read_json_linesegment_parameters
(
    Json::Value                          &parameters,
    Json::Value                          &kernel,
    std::vector<GaussianLineSegment2d *> &gls,
    const Ordinal                        &nsd,
    const DGM::Comm::Ptr                 comm,
    const int                            verb
) {
  // Add the kernel parameters in
  if (!kernel.isObject())
    comm->error("read_json_linesegment_parameters \"Kernel\" is not an "
                "json object");
  Json::Value::Members members = kernel.getMemberNames();
  for (size_t i=0; i<members.size(); ++i) {
    parameters[members[i]] = kernel[members[i]];
  }
  if (nsd!=2)
    comm->error("  GaussianLineSegment probe unsupported \n"
                "  number of space dimensions: "+asString(nsd));
  gls = GaussianLineSegment2d::reader(parameters, nsd, comm, verb);
  return true;
}

}  // anonymous namespace

bool Response::read_optional_response_file(unsigned &num_std_dev,
                                           unsigned &num_pts,
                                           Scalar   &stddev,
                                           bool     &average,
                                           const string &fname,
                                           const DGM::Comm::Ptr comm) {
  bool found_file=false;
  // read the optional response type file
  ifstream in(fname.c_str());
  if (in) {
    comm->cout() << "  Using optional Response file " << fname << endl;
    found_file = true;
    string tag;
    if (!(in >> tag)) error("Response:  Cannot read types tag");
    Response::scan_lb(in);
    if (lowerCase(tag) == "gaussian" ) {
      if (!(in >> stddev)) error("Response:  Cannot read standard deviation");
      while (' '==in.get());
      in.unget();
      if ('}' != in.peek()) in >> num_std_dev;
    } else if (lowerCase(tag) == "line" ) {
      while (' '==in.get());
      in.unget();
      if ('}' != in.peek()) in >> num_pts;
    } else if (lowerCase(tag) == "average" ) {
      average = true;
    } else
      error("Response: unsupported type");
    Response::scan_rb(in);
    in.close();
  }
  return found_file;
}

void Response::initialize_communication_pattern(const Ordinal glen) {
  const Ordinal np = comm->NumProc();
  const Ordinal me = comm->MyPID();
#ifdef DGM_RESPONSE_USE_NCORES
  const Memory M;
#endif
  vector<Size> gid;
  vector<Ordinal> lid;
  for (size_t i=1; i<probes.size(); ++i)
    if (probes[i]->kernel->global_id() <= probes[i-1]->kernel->global_id())
      comm->error(" Global probe numbers not monotonic.");
  gid_to_lid.clear();

  if (WHERE_NEEDED == probe_memory_storage) {
    if (verb) comm->cout()<<"  Response:  Using memory where needed to store "
        "probe data"<<endl;
    for (size_t i=0; i<probes.size(); ++i)
      gid_to_lid[probes[i]->kernel->global_id()] = numeric_cast<Ordinal>(i);
  } else if (PROC_WITH_CENTER == probe_memory_storage) {
    if (verb) comm->cout()<<"  Response:  Using process with center to store "
        "probe data"<<endl;
    for (size_t i=0, k=0; i<probes.size(); ++i)
      if (probes[i]->kernel->owned_by_this_proc())
        gid_to_lid[probes[i]->kernel->global_id()]= numeric_cast<Ordinal>(k++);
  } else if (EVENLY_DISTRIBUTED == probe_memory_storage) {
    if (verb) comm->cout()<<"  Response:  Using even distribution of "
                            "probe data "
        "in memory"<<endl;
    for (Ordinal i=0; i<glen; ++i) {
      if (i%np == me)
        gid_to_lid[i] = i/np;
#ifdef DGM_RESPONSE_USE_NCORES
      const Ordinal p = boost::numeric_cast<Ordinal>(M.ncores());
      const Ordinal g = (np+p-1)/p;
      const Ordinal c = i%g;
      const Ordinal r = (i/g)%p;
      const Ordinal k = (p*c + r)%np;
      if (k == me) gid_to_lid[i] = i/np;
#endif
    }
  } else {
    throw DGM::exception("Illegal value for prbmemorystorage");
  }

  if (WHERE_NEEDED == probe_memory_storage) {
    // Simple case: Data read multiple times on all the processors
    // that need it.  So there is a single send and a single receive
    // with me as both the sending and the receiving processor number
    // and all my probes as the probes to read.
    for (size_t i=0; i<probes.size(); ++i) {
      gid.push_back(probes[i]->kernel->global_id());
      lid.push_back(numeric_cast<Ordinal>(i));
    }
    if (!probes.empty()) {
      const Send s(me, nComponents, gid, lid);
      const Recv r(me, nComponents, gid, lid);
      send_info.push_back(s);
      recv_info.push_back(r);
    }
  } else {
    typedef map<Ordinal, vector<Ordinal> > PIDS;
    // Map from global processor number to local probe index.
    // NOTE:  This MUST be consistant with the gid_to_lid
    // map computed above.  gid_to_lid is the map from global
    // probe numbers that this processor with read the
    // data for  own to local array index where the data is stored.
    PIDS pids;

    for (size_t i=0; i<probes.size(); ++i) {
      // Which processor will own the data for this probe?
      // Depends if it is the processor with the probe center
      // or if it is the evenly distributed case when it will
      // be based on the global id number of the probe.
      const Ordinal lpid = boost::numeric_cast<Ordinal>(i);
      if (PROC_WITH_CENTER == probe_memory_storage) {
        pids[probes[i]->kernel->owning_processor()].push_back(lpid);
      } else {
        pids[probes[i]->kernel->global_id()%np].push_back(lpid);
#ifdef DGM_RESPONSE_USE_NCORES
        const Ordinal gid = probes[i]->kernel->global_id();
        const Ordinal p = boost::numeric_cast<Ordinal>(M.ncores());
        const Ordinal g = (np+p-1)/p;
        const Ordinal c = gid%g;
        const Ordinal r = (gid/g)%p;
        const Ordinal k = (p*c + r)%np;
        pids[k].push_back(lpid);
#endif
      }
    }
    for (PIDS::const_iterator p=pids.begin(); p!=pids.end(); ++p) {
      lid = p->second;
      gid.clear();
      for (size_t i=0; i<lid.size(); ++i) {
        gid.push_back(probes[lid[i]]->kernel->global_id());
      }
      const Recv r(p->first, nComponents, gid, lid);
      recv_info.push_back(r);
    }

    // So recv_info has been set up.  It contains all of the
    // information on what messages will be received ie. all
    // that is needed for MPI_Irecv.

    // NOW: Need to set us the send_info vector.  This is all
    // the messages that will be sent. To do this, send all
    // of the information in recv_info to the proper processors.
    vector<int> sendcount(np,0);
    vector<int> recvcount(np,0);
    for (vector<Recv>::const_iterator i=recv_info.begin();
        i!=recv_info.end(); ++i) {
      sendcount[i->from] = numeric_cast<int>(i->gid.size());
    }
    comm->Alltoall(&sendcount[0], 1, &recvcount[0], 1);
    size_t num_send = 0;
    size_t num_recv = 0;
    for (size_t i=0; i<sendcount.size(); ++i) num_send+=sendcount[i];
    for (size_t i=0; i<recvcount.size(); ++i) num_recv+=recvcount[i];
    vector<Size> sendbuf(num_send,0);
    vector<Size> recvbuf(num_recv,0);

    for (size_t i=0, k=0; i<recv_info.size(); ++i) {
      for (size_t j=0; j<recv_info[i].gid.size(); ++j)
        sendbuf[k++] = recv_info[i].gid[j];
    }
    vector<int> senddisp(np,0);
    vector<int> recvdisp(np,0);
    for (Ordinal i=1; i<np; ++i) senddisp[i] = senddisp[i-1]+sendcount[i-1];
    for (Ordinal i=1; i<np; ++i) recvdisp[i] = recvdisp[i-1]+recvcount[i-1];
    comm->Alltoallv(&sendbuf[0], &sendcount[0], &senddisp[0],
                    &recvbuf[0], &recvcount[0], &recvdisp[0]);
    for (Ordinal p=0, k=0; p<np; ++p) {
      gid.clear();
      lid.clear();
      for (int j=0; j<recvcount[p]; ++j) {
        const Size g = recvbuf[k++];
        if (!gid_to_lid.count(g)) {
          cout <<__FILE__<<":"<<__LINE__
               <<" On processor "<<comm->MyPID()
               <<" probe number "<<g<<" demanded by processor "<<p
               <<" does not exist on this processor."<<endl;
          cout <<" Probes on this processor: ";
          for (map<Size,Ordinal>::const_iterator i=gid_to_lid.begin();
               i!=gid_to_lid.end();++i) cout <<i->first<<" ";
          cout <<endl;
          comm->error("Response::initialize_communication_pattern: "
                      "unexpected probe number.");
        }
        gid.push_back(g);
        lid.push_back(gid_to_lid[g]);
      }
      if (recvcount[p]) {
        const Send s(p, nComponents, gid, lid);
        send_info.push_back(s);
      }
    }
  }
#ifdef DGM_PARALLEL
  send_requests.resize(send_info.size(), MPI_REQUEST_NULL);
  recv_requests.resize(recv_info.size(), MPI_REQUEST_NULL);
#endif
}

void Response::initialize_point_response_probes(
    const string &probeName,
    const vField &F,
    const dMatrix &xyz_,
    const vector< vector<Size> > &elem,
    const vector<string> &nid,
    const Json::Value &kernel,
    const Ordinal nProbes
) {
  const Ordinal glen = xyz_.dim1();
  const Ordinal nsd = numeric_cast<Ordinal>(xyz_.dim2());

  // Distribute nodes among processors
  Ordinal npop = 0;
  for (size_t i=0; i<probes.size(); ++i)
    if (probes[i]->kernel->owned_by_this_proc()) npop++;
  CMC::Stopwatch cpu; cpu.start();
  if (verb) comm->cout()<<"  Distributing "<<quoted(nameOrEmpty(probeName))
                        <<" point probes across all ranks"<<endl;
  for(Ordinal i=0; i<glen; i++) {   // Response node
    Point x;
    if (0<nsd) x.x = xyz_[i][0];
    if (1<nsd) x.y = xyz_[i][1];
    if (2<nsd) x.z = xyz_[i][2];
    if (3<nsd) comm->error("Response:: Illegal value of nsd");
    Probe::Ptr probe(new Probe());
    probe->probetype = stringToProbeType(kernel["Type"].asString());
    if (GAUSSIAN == probe->probetype) {
      const Scalar stddev = kernel.get("Standard deviation",0.0).asDouble();
      const Scalar num_std_dev =
          kernel.get("Number of standard deviations",3.0).asDouble();
      probe->kernel.reset(
        new GaussianResponse(nProbes+i, nid[i], x, F[0], elem[i],
                             stddev, num_std_dev));
    } else {
      const bool average = kernel.get("Average",false).asBool();
      probe->kernel.reset(
       new DeltaResponse(nProbes+i, nid[i], x, F[0], elem[i], average));
    }
    if (probe->kernel->locally_evaluated()) {
#if DGM_RESPONSE_VERBOSE>=2
      cout << comm->MyPID()<<": Probe = "
           << probe.kernel->name() << ": element =";
      for (Ordinal j=0; j<probe.kernel->size(); j++)
        cout << " " << F.partition->eid(probe.kernel->element_index(j));
      cout << endl;
#endif
      probes.push_back(probe);
      if(probe->kernel->owned_by_this_proc()) {
        pid.push_back(probe->kernel->name());
        xyz.push_back(probe->kernel->center_of_kernel());
      }
    }
  }
  Ordinal nPts = 0;
  for (size_t i=0; i<probes.size(); ++i)
    if (probes[i]->kernel->owned_by_this_proc()) nPts++;
  nPts -= npop;
  Ordinal nPts_tot = 0;
  comm->SumAll(&nPts, &nPts_tot, 1);
  if ( nPts_tot != glen ) {
    ostringstream oss;
    oss << "Response::initialize_point_response_probes: Error \n"
        << "  The total number of point probes created: "<<nPts_tot<<"\n"
        << "  Does not equal the number of probes in response file: "
        << glen;
    comm->error(oss.str());
  }
  if (verb>1)
    comm->cout() << "  Created " << glen << " point probes." << endl;
  if (verb)
    comm->cout()<<"  Completed "<<quoted(nameOrEmpty(probeName))
                <<" point probe distribution in "<<cpu.stop()
                <<" seconds."<<endl;
}

void Response::initialize_ellipse_response_probes
(const string                 &probeName,
 const vField                 &F,
 const dMatrix                &xyz_,
 const dMatrix                &sigma,
 const iMatrix                &der,
 const vector<dMatrix>        &dir,
 const vector<string>         &nid,
 const Json::Value            &kernel,
 const Ordinal                 nProbes)
{
  const Ordinal glen = xyz_.dim1();
  const Ordinal nsd = numeric_cast<Ordinal>(xyz_.dim2());

  // Distribute nodes among processors
  Ordinal npop = 0;
  for (size_t i=0; i<probes.size(); ++i)
    if (probes[i]->kernel->owned_by_this_proc()) npop++;
  CMC::Stopwatch cpu; cpu.start();
  if (verb)
    comm->cout()<<"  Distributing "<<quoted(nameOrEmpty(probeName))
                <<" ellipse response probes across all ranks"<<endl;
  for(Ordinal i=0; i<glen; i++) {   // Response node
    Point x;
    Ordinal D[3] = {0,0,0};
    Scalar  S[3] = {0,0,0};
    if (0<nsd) x.x = xyz_[i][0];
    if (1<nsd) x.y = xyz_[i][1];
    if (2<nsd) x.z = xyz_[i][2];
    if (0<nsd) D[0] = der[i][0];
    if (1<nsd) D[1] = der[i][1];
    if (2<nsd) D[2] = der[i][2];
    if (0<nsd) S[0] = sigma[i][0];
    if (1<nsd) S[1] = sigma[i][1];
    if (2<nsd) S[2] = sigma[i][2];
    if (3<nsd) comm->error("Response:: Illegal value of nsd");
    Probe::Ptr probe(new Probe());
    probe->probetype = GAUSSIANELLIPSE;
    //const Scalar stddev = kernel.get("Standard deviation",0.0).asDouble();
    const Scalar num_std_dev =
        kernel.get("Number of standard deviations",3.0).asDouble();
    probe->kernel.reset(
      new GaussianEllipseResponse(nProbes+i, nid[i], x, F[0], dir[i], D,
                                  S, num_std_dev));
    if (probe->kernel->locally_evaluated()) {
      probes.push_back(probe);
      if(probe->kernel->owned_by_this_proc()) {
        pid.push_back(probe->kernel->name());
        xyz.push_back(probe->kernel->center_of_kernel());
      }
    }
  }
  Ordinal nPts = 0;
  for (size_t i=0; i<probes.size(); ++i)
    if (probes[i]->kernel->owned_by_this_proc()) nPts++;
  nPts -= npop;
  Ordinal nPts_tot = 0;
  comm->SumAll(&nPts, &nPts_tot, 1);
  if ( nPts_tot != glen ) {
    ostringstream oss;
    oss << "Response::initialize_ellipse_response_probes: Error \n"
        << "  The total number of ellipse probes created: "<<nPts_tot<<"\n"
        << "  Does not equal the number of probes in response file: "
        << glen;
    comm->error(oss.str());
  }
  if (verb>1)
    comm->cout() << "  Created " << nPtProbes << " ellipse probes." << endl;
  if (verb) comm->cout()<<"  Completed "<<quoted(nameOrEmpty(probeName))
                        <<" ellipse probe distribution in "
                        <<cpu.stop() <<" seconds."<<endl;
}

void Response::initialize_linesegment_response_probes(
    const string                         &probeName,
    const vField                         &F,
    std::vector<GaussianLineSegment2d *> &gls,
    const Ordinal                        &nsd,
    const Ordinal                        nProbes
) {
  // Distribute nodes among processors
  Ordinal npop = 0;
  for (size_t i=0; i<probes.size(); ++i)
    if (probes[i]->kernel->owned_by_this_proc()) npop++;
  CMC::Stopwatch cpu; cpu.start();
  if (verb)
    comm->cout()<<"  Distributing "<<quoted(nameOrEmpty(probeName))
                <<" line-segment response segments across all ranks"<<endl;
  for(Ordinal i=0; i<numeric_cast<Ordinal>(gls.size()); i++) {// Response node
    Probe::Ptr probe(new Probe());
    probe->probetype = GAUSSIANLINESEGMENT;
    probe->kernel.reset( new GaussianLineSegment2dResponse(nProbes+i,
                         probeName+asString(i), F[0], gls[i]) );
    if (probe->kernel->locally_evaluated()) {
      probes.push_back(probe);
      if(probe->kernel->owned_by_this_proc()) {
        pid.push_back(probe->kernel->name());
        xyz.push_back(probe->kernel->center_of_kernel());
      }
    }
  }
  Ordinal nPts = 0;
  for (size_t i=0; i<probes.size(); ++i)
    if (probes[i]->kernel->owned_by_this_proc()) nPts++;
  nPts -= npop;
  Ordinal nPts_tot = 0;
  comm->SumAll(&nPts, &nPts_tot, 1);
  if ( nPts_tot != numeric_cast<Ordinal>(gls.size()) ) {
    ostringstream oss;
    oss << "  Response::initialize_linesegment_response_probes: Error \n"
        << "  The total number of point probes created: "<<nPts_tot<<"\n"
        << "  Does not equal the number of response segments created: "
        << gls.size();
    comm->error(oss.str());
  }
  if (verb>1)
    comm->cout() << "  Created " << gls.size() << " line segment probes."
                 << endl;
  if (verb) comm->cout()<<"  Completed "<<quoted(nameOrEmpty(probeName))
                        <<" probe distribution in "<<cpu.stop()
                        <<" seconds."<<endl;
}

void Response::setup_communication_pattern() {
  Ordinal on_proc=0, tot=0;
  for (unsigned i=0; i<probes.size(); ++i) {
    if (probes[i]->kernel->owned_by_this_proc()) ++on_proc;
  }
  comm->SumAll(&on_proc, &tot, 1);
  if (tot != nProbes) {
    const unsigned np = comm->NumProc();
    const unsigned me = comm->MyPID();

    if (!me) comm->cerr()
      <<"  Response::setup_communication_pattern: Error \n"
      <<"  The number of probes assigned to all of the processors: "<<tot<<"\n"
      <<"  Does not equal the total number of probes: "<<nProbes<<"\n"
      <<"  It could be that some of the probe centers are not found in \n"
      <<"  any element in the mesh."<<endl;

    for(Ordinal i=0; i<nProbes; i++) {          // Response node
      vector<unsigned> owned_by(np,0);
      vector<unsigned> owners  (np,0);
      for (unsigned p=0; p<probes.size(); ++p) {
        if (probes[p]->kernel->global_id() == i &&
            probes[p]->kernel->owned_by_this_proc()) owned_by[me]=1;
      }
      comm->SumAll(&owned_by[0], &owners[0], np);
      Ordinal k=0;
      for (unsigned p=0; p<np; ++p) k += owners[p];
      if (k==0 && !me) {
        cerr
          <<"  Probe number " << i << " is in error.\n"
          <<"  This probe was never assigned to a mesh element.\n"
          <<"  Could be that the coordinates are bad?"<<endl;
        cerr
          <<"  The coordinate for this point is:";
        if (0<nsd) cerr << probes[i]->kernel->center_of_kernel().x;
        if (1<nsd) cerr << ", "<< probes[i]->kernel->center_of_kernel().y;
        if (2<nsd) cerr << ", "<< probes[i]->kernel->center_of_kernel().z;
        cerr<<endl;
      }
      if (1<k && !me) {
        cerr
          <<"  Probe number " << i << " is in error.\n"
          <<"  This probe was assigned to multiple mesh elements.\n"
          <<"  Could be that the coordinates are bad?"<<endl;
        cerr
          <<"  The coordinate for this point is:";
        if (0<nsd) cerr << probes[i]->kernel->center_of_kernel().x;
        if (1<nsd) cerr << ", "<< probes[i]->kernel->center_of_kernel().y;
        if (2<nsd) cerr << ", "<< probes[i]->kernel->center_of_kernel().z;
        cerr<<endl;
      }
    }
    comm->error("Response:: Error in assigning probes to processors.");
  }
  Size max_id=0;
  for (unsigned i=0; i<probes.size(); ++i) {
    if (max_id<probes[i]->kernel->global_id())
      max_id = probes[i]->kernel->global_id();
  }
  uint64_t m_id = max_id;
  comm->MaxAll(m_id);
  max_id = numeric_cast<Size>(m_id);
  if (nProbes && max_id+1 != nProbes) {
    const int me = comm->MyPID();
    if (!me) comm->cerr()
     <<"  Response::setup_communication_pattern: Error \n"
     <<"  The maximum probe global id over over all processors:"<<max_id<<"\n"
     <<"  Does not equal 1 less than the total number of probes:"<<nProbes<<"\n"
     <<"  It could be that the global numbering is messed up."<<endl;
    comm->error("Response:: Error in assigning probes to processors.");
  }
  Size sum_id=0, tot_sum_id;
  for (unsigned i=0; i<probes.size(); ++i)
    if (probes[i]->kernel->owned_by_this_proc())
      sum_id += probes[i]->kernel->global_id();
  comm->SumAll(&sum_id, &tot_sum_id, 1);
  if (nProbes && tot_sum_id != nProbes*(nProbes-1)/2) {
    const unsigned me = comm->MyPID();
    if (!me) comm->cerr()
      <<"  Response::setup_communication_pattern: Error \n"
      <<"  Check for sequentiall increasing global ids failed. "<<max_id<<"\n"
      <<"  The sum of all of the global ids:"<<tot_sum_id<<"\n"
      <<"  Does not equal  nProbes*(nProbes-1)/2 for nProbes: "<<nProbes<<"\n"
      <<"  It could be that the global numbering is messed up."<<endl;
    comm->error("Response:: Error in assigning probes to processors.");
  }

  CMC::Stopwatch cpu; cpu.start();
  if (verb) comm->cout() << "  Setting up communication pattern..." << endl;
  initialize_communication_pattern(nProbes);
  if (verb) comm->cout() << "  Completed communication pattern setup in "
      << cpu.stop() << " seconds." << endl;

  //probe_io.initialize_probes(probes, stddev, nsd, nProbes);
  probe_io.initialize_probes(probes, nsd, nProbes);

  data.resize(numeric_cast<Ordinal>(pid.size()));

  AllReduce::COMM_VECTOR comms;
  for (size_t i=0; i<probes.size(); ++i) {
    const Probe &p = *(probes[i]);
    if (p.kernel->multiple_processor() && p.kernel->locally_evaluated()) {
      AllReduce::COMM_VECTOR::value_type t(p.kernel->global_id(),
                                           p.kernel->comm());
      comms.push_back(t);
    }
  }
  reduce.init(nComponents, comms, comm);
}

/// Constructor from the original node file (version 0 input specification)
Response::Response(const vField         &F,
                   const string         &fname_node,
                   const DGM::Comm::Ptr comm_,
                   const ProbeFormat    prbfmt,
                   const ProbeFiles     prbfls,
                   const unsigned       prbblocks,
                   const bool           prbfflush,
                   const bool           prbtran,
                   const bool           prbttrc,
                   const unsigned       maxopen,
                   const Scalar         dt,
                   const Scalar         pdt,
                   const Ordinal        plen,
                   const StorageType    pms,
                   const int            verbosity) :
  valid(false),
  comm(comm_),
  nsd(F.nsd()),
  verb(verbosity),
  probes(),
  probe_io(comm_, prbfmt, prbfls, prbblocks, prbfflush, prbtran, prbttrc),
  reduce(),
  initialize_probe_files(true),
  pid(),
  probeFormat(prbfmt),
  probeFiles(prbfls),
  probeTrans(prbtran),
  probeTimeTrace(prbttrc),
  maxOpenFiles(max(static_cast<unsigned>(1),maxopen)),
  deltaTime(dt),
  probeDeltaTime(pdt),
  probeNumSamples(plen),
  nRealizations(0),
  nComponents(F.size()),
  ComponentsToApply(0),
  ComponentsOffset(0),
  nProbes(0),
  nPtProbes(0),
  nSsProbes(0),
  nFileProbes(0),
  nEllipseProbes(0),
  nLineSegProbes(0),
  probe_memory_storage(pms),
#ifdef DGM_PARALLEL
  send_requests(),
  recv_requests(),
#endif
  send_info(),
  recv_info(),
  gid_to_lid(),
  dprobe_trace_data(),
  fprobe_trace_data(),
  _name(F[0]->root),
  _root(F[0]->root)
{
  verb = max(verbosity, comm->verbosity());
  FunctionTimer *t=0;
  if (verb>2) {static FunctionTimer T("Response::Response(file)"); t=&T;}
  FunctionSentry sentry(t);
  if (verb) comm->cout()<<"Constructing Response from "<<fname_node<<endl;
  if (probeTimeTrace && probeTrans)
    throw DGM::exception("Response::Response: Cannot both use both Transpose "
                         "and Time Trace.");
  vector< vector<Size> > elem;     // element IDs
  vector<string> nid;              // probe (node) IDs
  dMatrix xyz;                     // temporary xyz storage
  CMC::Stopwatch cpu; cpu.start();
  valid = read_response_file(fname_node,xyz,elem,nid,nPtProbes,nsd,comm,verb);
  nProbes += nPtProbes;
  if (!valid) return;
  if (verb)
    comm->cout()<<"  Read response file in "<<cpu.stop()<<" seconds."<<endl;
  cpu.restart();
  if (verb) comm->cout()<<"  Starting to initialize response probes..."<<endl;
  Scalar stddev=0.0;
  unsigned num_std_dev=3;
  bool average=false;
  unsigned num_pts=10;
  read_optional_response_file(num_std_dev, num_pts, stddev, average,
                              _root+".ant", comm);
  Json::Value kernel(Json::objectValue);
  if (stddev==0.0)
    kernel["Type"] = "Delta";
  else
    kernel["Type"] = "Gaussian";
  kernel["Standard deviation"] = stddev;
  kernel["Number of standard deviations"] = num_std_dev;
  kernel["Average"] = average;
  initialize_point_response_probes(fname_node, F, xyz, elem, nid, kernel, 0);
  setup_communication_pattern();
  if (verb)
    comm->cout()<<"  Completed response probe initialization in " << cpu.stop()
                << " seconds." << endl;
}

/// Construct from a set of points (only reads root.ant file if available)
Response::Response(const vField         &F,
                   const dMatrix        &xyz,
                   const DGM::Comm::Ptr comm_,
                   const ProbeFormat    prbfmt,
                   const ProbeFiles     prbfls,
                   const unsigned       prbblk,
                   const bool           prbfflush,
                   const bool           prbtran,
                   const bool           prbttrc,
                   const unsigned       maxopen,
                   const Scalar         dt,
                   const Scalar         pdt,
                   const Ordinal        plen,
                   const StorageType    pms,
                   const int            verbosity) :
  valid(true),
  comm(comm_),
  nsd(F.nsd()),
  verb(verbosity),
  probes(),
  probe_io(comm_, prbfmt, prbfls, prbblk, prbfflush, prbtran, prbttrc),
  reduce(),
  initialize_probe_files(true),
  pid(),
  probeFormat(prbfmt),
  probeFiles(prbfls),
  probeTrans(prbtran),
  probeTimeTrace(prbttrc),
  maxOpenFiles(max(static_cast<unsigned>(1),maxopen)),
  deltaTime(dt),
  probeDeltaTime(pdt),
  probeNumSamples(plen),
  nRealizations(0),
  nComponents(F.size()),
  ComponentsToApply(0),
  ComponentsOffset(0),
  nProbes(xyz.dim1()),
  nPtProbes(xyz.dim1()),
  nSsProbes(0),
  probe_memory_storage(pms),
#ifdef DGM_PARALLEL
  send_requests(),
  recv_requests(),
#endif
  send_info(),
  recv_info(),
  gid_to_lid(),
  dprobe_trace_data(),
  fprobe_trace_data(),
  _name(F[0]->root),
  _root(F[0]->root)
{
  verb = max(verb, comm->verbosity());
  FunctionTimer *t=0;
  if (verb>2) {static FunctionTimer T("Response::Response(points)"); t=&T;}
  FunctionSentry sentry(t);

  if (verb) comm->cout()<<"Constructing Response from a list of points"<<endl;
  if (probeTimeTrace && probeTrans)
    comm->error("Response::Response: Cannot both Transpose and Time Trace.");
  nsd = numeric_cast<Ordinal>(xyz.dim2());
  vector< vector<Size> > elem(nProbes);     // element IDs
  vector<string> nid(nProbes);              // nodal IDs
  for (Ordinal i=0; i<nProbes;++i) {
    stringstream ss;
    ss << i;
    nid[i] = ss.str();
  }
  Scalar stddev=0.0;
  unsigned num_std_dev=3;
  bool average=false;
  unsigned num_pts=10;
  read_optional_response_file(num_std_dev, num_pts, stddev, average,
                              _root+".ant", comm);
  Json::Value kernel(Json::objectValue);
  if (stddev==0.0)
    kernel["Type"] = "Delta";
  else
    kernel["Type"] = "Gaussian";
  kernel["Standard deviation"] = stddev;
  kernel["Number of standard deviations"] = num_std_dev;
  kernel["Average"] = average;
  initialize_point_response_probes(_root+"-xyz", F, xyz, elem, nid, kernel, 0);
  setup_communication_pattern();
}

#ifdef DGM_USE_JSON

/// Construct from a Json specification (this is the version 1 specification)
Response::Response(const vField         &F,
                   const Json::Value    &json,
                   const DGM::Comm::Ptr comm_,
                   const ProbeFormat    prbfmt,
                   const ProbeFiles     prbfls,
                   const unsigned       prbblocks,
                   const bool           prbfflh,
                   const bool           prbtran,
                   const bool           prbttrc,
                   const unsigned       maxopen,
                   const Scalar         dt,
                   const Scalar         pdt,
                   const Ordinal        plen,
                   const StorageType    pms,
                   const int            verbosity) :
  valid(false), comm(comm_), nsd(F.nsd()), verb(verbosity), probes(),
  probe_io(comm_, prbfmt, prbfls, prbblocks, prbfflh, prbtran, prbttrc),
  reduce(), initialize_probe_files(true), pid(),
  probeFormat(prbfmt), probeFiles(prbfls), probeTrans(prbtran),
  probeTimeTrace(prbttrc), maxOpenFiles(max(static_cast<unsigned>(1),maxopen)),
  deltaTime(dt), probeDeltaTime(pdt), probeNumSamples(plen), nRealizations(0),
  nComponents(F.size()), ComponentsToApply(0), ComponentsOffset(0),
  nProbes(0), nPtProbes(0), nSsProbes(0), nFileProbes(0), nEllipseProbes(0),
  nLineSegProbes(0), probe_memory_storage(pms),
#ifdef DGM_PARALLEL
  send_requests(), recv_requests(),
#endif
  send_info(), recv_info(), gid_to_lid(), dprobe_trace_data(),
  fprobe_trace_data(), _name(F[0]->root), _root(F[0]->root)
{
  verb = max(verbosity, comm->verbosity());
#if 0
  FunctionTimer *t=0;
  if (verb>2) {static FunctionTimer T("Response::Response(json)"); t=&T;}
  FunctionSentry sentry(t);
#endif

  if (verb) comm->cout()<<"Constructing Response from Json input ..."<<endl;
  if (probeTimeTrace && probeTrans)
    throw DGM::exception("Response::Response: Cannot both use both Transpose "
                         "and Time Trace.");

  _name = json.get("Name",_name).asString();

  if (!json.isMember("Probes"))
    comm->error("Response::Response(json): \"Probes\" is not present in "
                "Response.");

  Json::Value probe_definitions = json["Probes"];

  if  (!probe_definitions.isArray())
    comm->error("Response::Response(json): \"Probes\" is not an array type in "
                "response.");

  // read the Kernel definitions
  if (!json.isMember("Kernels"))
    comm->error("Response::Response(json): \"Kernels\" is not present in "
                "Response.");

  Json::Value kernels = json["Kernels"];

  CMC::Stopwatch cpu; cpu.start();
  if (verb>1) comm->cout()<<"  Starting to initialize response probes..."<<endl;

  for (Json::ValueIterator probe_iter = probe_definitions.begin();
       probe_iter != probe_definitions.end(); ++probe_iter ) {

    Json::Value probe_def = *probe_iter;

    if(!probe_def.isMember("Kernel"))
      comm->error("Probe Json block must have a \"Kernel\"");

    if (!kernels.isMember(probe_def["Kernel"].asString()))
      comm->error("Response::Probe::Kernel unknown kernel named: "+
                  probe_def["Kernel"].asString());
    Json::Value kernel = kernels[probe_def["Kernel"].asString()];

    string probeName;
    if (probe_def.isMember("Name")) {
      if (!probe_def["Name"].isString())
        comm->error("Response::Probe::Name must be a string");
       probeName = probe_def["Name"].asString();
    }

    if (verb>1) comm->cout()<<"  Read Probe \""
        << (!probeName.empty() ? probeName : "<no name>")
        <<"\" with kernel \""<<probe_def["Kernel"].asString()
        <<"\" of type \""<<kernel["Type"].asString()<<"\""<<endl;

    ProbeType probe_type = stringToProbeType(kernel["Type"].asString());

    if (probe_def.isMember("File") && probe_type == GAUSSIANELLIPSE ) {
      comm->error("Response::Response(json): probe \"File\" "
                  "parameter is not valid for \"GaussianEllipse\" probes."
                  " Need to define a valid ASCII file format for these.");
    }
    dMatrix xyz_;                      // temporary xyz storage
    vector<string> nid;                // probe (node) IDs
    vector< vector<Size> > elem;       // element IDs
    if ( probe_type == SIDESET ) {
      vector< vector<Ordinal> > side;  // side IDs
      Scalar stddev = 0.0;             // standard deviation
      CMC::Stopwatch cpu; cpu.start();
      valid = parse_json(json, F, xyz_, nid, elem, side, stddev,
                         comm, verbosity);
      if (!valid) comm->error("  Failed to parse JSON Sideset!");
      if (verb>1)
        comm->cout()<<"  Parse JSON Sideset in "<<cpu.stop()<<" seconds."<<endl;
      cpu.restart();
      if (verb>1)
          comm->cout()<<"  Starting to initialize Sideset probes..." << endl;
      initialize_sideset_probes(F, xyz_, nid, elem, side, stddev);
      nProbes += nSsProbes;
      if (verb>1)
        comm->cout()<<"  Completed Sideset probe initialization in "
                    << cpu.stop() << " seconds." << endl;
    } else if ( probe_type == GAUSSIAN || probe_type == DELTA ) {
      if (probe_def.isMember("File")) {
        valid = read_file_point_parameters(probe_def, probeName, xyz_, elem,
                                           nid, nFileProbes, nsd, comm, verb);
      } else {
        valid = read_json_point_parameters(probe_def, xyz_, elem, nid,
                                           nPtProbes, nsd, comm, verb);
      }
      if (!valid)
        comm->error("Response::Response(json) Error reading point "
                    "probe parameters.");
      initialize_point_response_probes(probeName, F, xyz_, elem, nid,
                                       kernel, nProbes);
      nProbes += nid.size();
    } else if ( probe_type == GAUSSIANELLIPSE) {
      dMatrix sigma;
      iMatrix der;
      vector<dMatrix> dir;
      valid = read_json_ellipse_parameters(probe_def,xyz_,sigma,der,dir,nid,
                                           nEllipseProbes, kernel, nsd,
                                           comm, verb);
      initialize_ellipse_response_probes(probeName, F, xyz_, sigma, der,
                                         dir, nid, kernel, nProbes);
      nProbes += nid.size();
    } else if ( probe_type == GAUSSIANLINESEGMENT) {
      std::vector<GaussianLineSegment2d *> gls;
      valid = read_json_linesegment_parameters(probe_def, kernel, gls, nsd,
                                               comm, verb);
      initialize_linesegment_response_probes(probeName,F,gls,nsd,nProbes);
      nProbes += gls.size();
      nLineSegProbes += gls.size();
    } else {
      comm->error("Response::Response(json) unknown probe type "+
                  probe_def["Kernel"].asString());
    }
  }
  if (verb>1)
    comm->cout()<<"  Completed response probe initialization in "
                << cpu.stop() << " seconds." << endl;

  setup_communication_pattern();

  if (verb>1) {
    comm->cout() << "  Response::Response(json) for : " << _name << "\n"
                 << "    Number of space dimensions = " << nsd  << "\n"
                 << "    Number of points           = " << nPtProbes << "\n"
                 << "    Number of sidesets         = " << nSsProbes  << "\n"
                 << "    Number of points from file = " << nFileProbes << "\n"
                 << "    Number of ellipses         = " << nEllipseProbes <<"\n"
                 << "    Number of line segments    = " << nLineSegProbes <<"\n"
                 << "    Total number of probes     = " << nProbes << endl;
  }
}

/// Parse the JSON input for this response
/** This has really evolved to just parsing the Sideset information. */
bool Response::parse_json( const Json::Value &json,
                           const vField &F,
                           dMatrix &xyz_,                   // temp xyz storage
                           vector<string> &nid,             // probe (node) IDs
                           vector< vector<Size> > &elem,    // element IDs
                           vector< vector<Ordinal> > &side, // side IDs
                           Scalar &stddev,
                           const DGM::Comm::Ptr comm,
                           const unsigned verb )
{
  Json::Value jprbs = json["Probes"];
  for (Json::ValueIterator j_it = jprbs.begin(); j_it != jprbs.end(); j_it++) {

    Json::Value jprb = *j_it;

    ProbeType probe_type =
      stringToProbeType(jprb.get("Type","Gaussian").asString());

    // This should be in the Kernel
    stddev = jprb.get("Standard deviation",0.0).asDouble();

    if ( probe_type == SIDESET ) {
      nSsProbes++;

      // Read sideset information
      unsigned ssid = 0;
      if (jprb.isMember("Sideset ID")) {
         ssid = jprb["Sideset ID"].asUInt();
         nid.push_back(asString(ssid));
      } else {
        ostringstream oss;
        oss << "    Sideset ID is undefined for\n"
            << "      response      = " << _name << "\n"
            << "      Sideset probe = " << nSsProbes;
        comm->error(oss.str());
      }
      string fname = jprb.get("Sideset file", _root+".ss").asString();
      if (comm->Master()) {
        ifstream sfile(fname.c_str());
        if (!sfile) {
          ostringstream oss;
          oss << "    Unable to open sideset file = " << fname;
          comm->error(oss.str());
        }
        unsigned id    = 0;
        Size    elem_  = 0;
        Ordinal side_  = 0;
        vector<Size> temp_elem;
        vector<Ordinal> temp_side;
        while ( sfile >> id >> elem_ >> side_ ) {
          if ( id == ssid ) {
            temp_elem.push_back(elem_);
            temp_side.push_back(side_);
          }
        }
        elem.push_back(temp_elem);
        side.push_back(temp_side);
        if ( (elem.back()).size() == 0 ) {
          ostringstream oss;
          oss << "    For Sideset probe = " << nSsProbes << "\n"
              << "    Did not find any Sideset IDs = " << ssid << " in "<<fname;
          comm->error(oss.str());
        }
      }
    }
  }

  size_t nssprbs = elem.size();
  comm->Broadcast(&nssprbs);
  if (nssprbs != boost::numeric_cast<size_t>(nSsProbes)) {
    ostringstream oss;
    oss << "    Number of sideset probes constructed "
        << "    (=" << nssprbs << ") does not match number of" << "\n"
        << "    items in Sideset block (=" << nSsProbes << ")";
    comm->error(oss.str());
  }

  if (verb>1)
    comm->cout() << "Response:: Number of sideset probes = "
                 << boost::numeric_cast<unsigned>(nSsProbes)
                 <<", Dimension = " << nsd << endl;

  CMC::Stopwatch cpu; cpu.start();
  if (verb) comm->cout() << "  Starting boost serialization..." << endl;
  comm->Barrier();

  // Communicate the elements - elem
  if (verb>1) comm->cout() << "    Communicating elements ..." << endl;
  vector<Ordinal> elem_len(nSsProbes);
  if (comm->Master())
    for (Ordinal i=0; i<nSsProbes; i++)
      elem_len[i] = numeric_cast<Ordinal>(elem[i].size());
  comm->Broadcast(&elem_len[0], numeric_cast<int>(nSsProbes));

  if (!comm->Master()) {
    elem.resize(nSsProbes);
    side.resize(nSsProbes);
    for (Ordinal i=0; i<nSsProbes; i++) {
      elem[i].resize(elem_len[i]);
      side[i].resize(elem_len[i]);
    }
  }

  Ordinal tot_len = 0;
  for (Ordinal i=0; i<nSsProbes; i++) tot_len += elem_len[i];
  vector<Size> ebuf(tot_len);
  if (comm->Master()) {
    for (Ordinal i=0,k=0; i<nSsProbes; ++i)
      for (Ordinal j=0; j<elem_len[i]; ++j)
        ebuf[k++] = elem[i][j];
  }
  comm->Broadcast(&ebuf[0], numeric_cast<int>(tot_len));
  for (Ordinal i=0,k=0; i<nSsProbes; ++i) {
    elem[i].resize(elem_len[i]);
    for (Ordinal j=0; j<elem_len[i]; ++j)
      elem[i][j] = ebuf[k++];
  }

  // Communicate the sides - side
  if (verb>1) comm->cout() << "    Communicating sides ..." << endl;
  vector<Ordinal> sbuf(tot_len);
  if (comm->Master()) {
    for (Ordinal i=0,k=0; i<nSsProbes; ++i)
      for (Ordinal j=0; j<elem_len[i]; ++j)
        sbuf[k++] = side[i][j];
  }
  comm->Broadcast(&sbuf[0], numeric_cast<int>(tot_len));
  for (Ordinal i=0,k=0; i<nSsProbes; ++i) {
    side[i].resize(elem_len[i]);
    for (Ordinal j=0; j<elem_len[i]; ++j)
      side[i][j] = sbuf[k++];
  }

  // Communicate the xyz location
  if (verb>1) comm->cout() << "    Communicating xyz ..." << endl;
  const Ordinal lnSsProbes = numeric_cast<Ordinal>(nSsProbes);
  xyz_.resize(lnSsProbes,nsd);
  dVector temp; temp.resize(nsd);
  for (Ordinal i=0; i<lnSsProbes; ++i) {
    int pid = numeric_limits<int>::max();
    temp = 0.0;
    for (Ordinal k=0; k<F[0]->partition->ne(); k++) {
      if(elem[i][0]==numeric_cast<Size>(F[0]->partition->eid(k))) {
        // Use first element centroid as probe xyz.
        Point c = F[0]->el[k]->centroid();
        if (0<nsd) temp[0] = c.x;
        if (1<nsd) temp[1] = c.y;
        if (2<nsd) temp[2] = c.z;
        pid = comm->MyPID();
        break;
      }
    }
    int spid = numeric_limits<int>::max();
    comm->MinAll(&pid, &spid, 1);
    comm->Broadcast(temp.data(), numeric_cast<int>(temp.size()), spid);
    if (0<nsd) xyz_[i][0] = temp[0];
    if (1<nsd) xyz_[i][1] = temp[1];
    if (2<nsd) xyz_[i][2] = temp[2];
  }
  if (verb) comm->cout() << "  Finished parsing Sideset probes in "
                         << cpu.stop() << " seconds." << endl;
  return true;
}

#endif  // DGM_USE_JSON

void Response::initialize_sideset_probes(
    const vField &F,
    const dMatrix &xyz_,
    const vector<string> &nid,
    const vector< vector<Size> > &elem,
    const vector< vector<Ordinal> > &side,
    const Scalar stddev
) {
  // Distribute nodes among processors
  CMC::Stopwatch cpu; cpu.start();
  if (verb)
    comm->cout()<<"  Distributing sideset probes across all ranks"<<endl;
  Ordinal probe_offset = 0;
  Ordinal temp = 0;
  for (size_t i=0; i<probes.size(); i++)
    if (probes[i]->kernel->owned_by_this_proc()) ++temp;
  comm->SumAll(&temp, &probe_offset, 1);
  const Ordinal lnSsProbes = numeric_cast<Ordinal>(nSsProbes);
  for(Ordinal i=0; i<lnSsProbes; i++) {   // Response node
    Point x;
    if (0<nsd) x.x = xyz_[i][0];
    if (1<nsd) x.y = xyz_[i][1];
    if (2<nsd) x.z = xyz_[i][2];
    if (3<nsd) comm->error("Response:: Illegal value of nsd");
    Probe::Ptr probe(new SideSetProbe(F[0], elem[i], side[i]));
    probe->probetype = SIDESET;
    probe->kernel.reset(
      new GaussianResponse(i+probe_offset,nid[i],x,F[0],elem[i],0.0,stddev));
    if (probe->kernel->locally_evaluated()) {
#if DGM_RESPONSE_VERBOSE>=2
      cout << comm->MyPID()<<" Probe = " << probe.pid << ": element =";
      for (unsigned j=0; j<probe.eidx.size(); j++)
        cout << " " << F.partition->eid(probe.eidx[j]);
      cout << endl;
#endif
      probes.push_back(probe);
      if(probe->kernel->owned_by_this_proc()) {
        pid.push_back(probe->kernel->name());
        xyz.push_back(probe->kernel->center_of_kernel());
      }
    }
  }
  if (verb) comm->cout()<<"  Completed sideset probe distribution in "
                        <<cpu.stop()<<" seconds."<<endl;
}

/// Destructor
Response::~Response() { }

size_t Response::probes_on_proc() const {
  size_t Nprobes = probes.size();
  return Nprobes;
}

bool Response::probe_on_proc(const Ordinal n) const {
  bool i_have = false;
  for (size_t i=0; i<probes.size(); ++i) {
    if ((Size)n == probes[i]->kernel->global_id()) i_have = true;
  }
  return i_have;
}

/** A virtual "hotwire" probe that outputs a file with extension .prb for
    each response point and this gets called to give a time history of the
    solution.  The default is to write ASCII format files, but with the
    option to write C-binary files if desired. */
void Response::probe(const vField &F, const string &root,
                     const Scalar time, const bool last_time) {
  if (!valid) return;
  if (initialize_probe_files) {
    initialize_probe_files = false;
    probe_io.initialize_root(root);
    values.resize(F.size());
  }
  probe_io.print(F, time, last_time);
}

/// output to a file
void Response::output(const Field *F, const string &fname_solver) {
  if (!valid) return;
  const dVector gdata = gather_data(F);
  write_to_file(gdata, fname_solver);
}

dVector Response::gather_data(const Field *F) {
  if (!valid) return dVector(Ordinal(0));
  probe_io.output(F, data);
  const dVector gdata = gather();
  return gdata;
}

/** Gather data from different processors. */
dVector Response::gather() const {
#ifdef DGM_PARALLEL
  const int len = data.size();
  const int np = comm->NumProc();
  std::vector<int> rcounts(np);
  std::vector<int> displs(np);

  comm->GatherAll(&len, rcounts.data(), 1);

  // make displacements
  for(int i=0; i<np; i++) {
    displs[i] = 0;
    for(int j=0; j<i; j++) displs[i] += rcounts[j];
  }
  dVector gdata(nProbes);
  gdata = 0;

  comm->GatherAll(data.ptr(), len, gdata.ptr(), rcounts.data(), displs.data());

  return gdata;
#else  // !DGM_PARALLEL
  return data;
#endif  // DGM_PARALLEL
}


void Response::write_to_file(const dVector gdata, const string &fname_solver) const {
  vector<Point> gxyz(nProbes);
  vector<string> gpid(nProbes);
#ifdef DGM_PARALLEL
  if(comm->Master())
#endif  // DGM_PARALLEL
  {
    for (Ordinal i=0; i<std::min(nProbes,(Ordinal)pid.size()); ++i)
      gpid[i] = pid[i];
    for (Ordinal i=0; i<std::min(nProbes,(Ordinal)xyz.size()); ++i)
      gxyz[i] = xyz[i];
    Format sci(11); sci.scientific().width(18);
    ofstream fout(fname_solver.c_str());
    if (nsd==1)
      fout<<"NodeID   NodeX   Value "<<endl;
    else if (nsd==2)
      fout<<"NodeID   NodeX   NodeY   Value"<<endl;
    else if (nsd==3)
      fout<<"NodeID   NodeX   NodeY   NodeZ   Value"<<endl;
    const Ordinal lnProbes = numeric_cast<Ordinal>(nProbes);
    for (Ordinal i=0; i<lnProbes; i++) {
      fout << gpid[i] << " ";
      for (Ordinal j=0; j<nsd; j++) fout << sci(gxyz[i][j]) << " ";
      fout << sci(gdata[i]) << endl;
    }
  }
}

/** Reads probe trace data in flat binary format using either MPI-IO or plain
    C-binary I/O in serial

    \note This shouldn't split MPI_COMM_WORLD -- it must split the DGM::Comm
*/
template <typename scalar, typename datatype>
void Response::read_probe_separate_serial
  (vector<CMC::Array<datatype,Ordinal> > &trace,
   const string &state_root,
   const string &run_file_base)
{
  const size_t num_probes   = trace.size();
  const Ordinal number_of_runs  = trace.empty() ? 0 : trace.front().dim1();
  const Ordinal num_components  = trace.empty() ? 0 : trace.front().dim2();
  const Ordinal num_time_steps  = trace.empty() ? 0 : trace.front().dim3();
  if (probes.size() != num_probes) {
     comm->cout()<<"Error reading probe files."<<endl;
     comm->cout()<<"  Number of probes:"<<probes.size()<<endl;
     comm->cout()<<"  != Number of expected probes"<<num_probes<<endl;
     comm->error("Response::read_probe");
  }
  if (!probeTimeTrace)
     comm->error(
     "Response::read_probe: Can not turn off time trace for separate "
     "probe files. Simply not supported as yet.");
  for (int ns=0; ns<(int)number_of_runs; ns++) {
    char runnumber[128]; sprintf(runnumber,".%d",ns);
    const string pathname = run_file_base + runnumber + "/";
    for (size_t nr=0;nr<num_probes;++nr) {
      const string filename = pathname+state_root;
      Probe::Ptr probe = probes[nr];
      probe->open_file(comm, filename, probeFormat);
      for (int nt=0; nt<(int)num_time_steps; nt++) {
        probe->read(probeFormat); // flush time
        for (Ordinal nc=0; nc<num_components; ++nc) {
          const Scalar x = probe->read(probeFormat);
          trace[nr][ns][nc][nt] = x;
        }
        if (ASCII==probeFormat) {
          char str[2048];
          fgets ( str, sizeof(str), probe->file );
        }
      }
      probe->close_file();
    }
  }
  for (size_t nr=0; nr<num_probes; ++nr) {
    Probe::Ptr probe = probes[nr];
    vector<Scalar> sum(number_of_runs*num_time_steps*num_components,0);
    for (Ordinal ns=0; ns<number_of_runs; ns++)
      for (Ordinal nt=0; nt<num_time_steps; ++nt)
        for (Ordinal i=0; i<num_components; i++)
          sum[i+nt*num_components+ns*num_components*num_time_steps] =
            trace[nr][ns][i][nt];
    probe->reduce_multi_processor(sum);
    if (probe->kernel->locally_evaluated()) {
      for (Ordinal ns=0; ns<number_of_runs; ns++)
        for (Ordinal nt=0; nt<num_time_steps; ++nt)
          for (Ordinal i=0; i<num_components; i++)
            trace[nr][ns][i][nt] = sum[i+nt*num_components+ns*
                                       num_components*num_time_steps];
    }
  }
}

template <typename scalar,  typename datatype>
void Response::read_probe_combined_serial(
    vector<CMC::Array<datatype,Ordinal> > &trace,
    const vector<string> &component_names,
    const string &state_root,
    const string &run_file_base)
{
  const Ordinal num_probes = numeric_cast<Ordinal>(trace.size());
  const Ordinal number_of_runs = trace.empty() ? 0 : trace.front().dim1();
  const Ordinal num_components = trace.empty() ? 0 : trace.front().dim2();
  const Ordinal num_time_steps = trace.empty() ? 0 : trace.front().dim3();
  if (!probeTimeTrace)
     comm->error(
     "Response::read_probe: Can not turn off time trace for serial "
     "runs files. Simply not supported as yet.",1);
  for (Ordinal ns=0; ns<number_of_runs; ns++) {
    char runnumber[128]; sprintf(runnumber,".%llu",(long long unsigned)ns);
    const string pathname = run_file_base + runnumber + "/";
    for (Ordinal nc=0; nc<num_components; ++nc) {
      const string filename = pathname+state_root+"."+
        component_names[nc]+".prb";
      const char *mode=(probeFormat==ASCII)?"r":"rb";
      FILE *fp = fopen(filename.c_str(),mode);
      if (!fp) {
        string msg("Response::read_probe::fopen failed on:");
        msg += filename;
        comm->error(msg);
      }
      if (probeTrans) {
        CMC::Matrix< scalar, Ordinal > v(num_probes, num_time_steps);
        if (ASCII==probeFormat) {
          for (Ordinal j=0; j<num_probes; ++j) {
            for (Ordinal i=0; i<num_time_steps; ++i) {
              Scalar x;
              const char *format = (sizeof(x) == sizeof(double)) ? "%le": "%e";
              const int r = fscanf ( fp, format, &x) ;
              v[j][i] = x;
              if (r != 1) {
                comm->cout()<<"Error reading file: "<<filename<<endl;
                comm->cout()<<"  Elements read: "<<r<<" expected: "<<1<<endl;
                comm->error("Response::read_probe::fscanf");
              }
            }
          }
        } else {
          const size_t c = v.size();
          const size_t r = fread(v.data(), sizeof(scalar), c, fp);
          if (r != c) {
            comm->cout()<<"Error reading file: "<<filename<<endl;
            comm->cout()<<"  Read: "<<r<<" data points, expected: "<<c<<endl;
            comm->error("Response::read_probe::fread");
          }
        }
        for (Ordinal nr=0; nr<num_probes; nr++) {
          for (Ordinal nt=0; nt<num_time_steps; nt++) {
            trace[nr][ns][nc][nt] = v[nr][nt];
          }
        }
      } else {
        CMC::Matrix< scalar, Ordinal > v(num_time_steps, num_probes+1);
        if (ASCII==probeFormat) {
          for (Ordinal i=0; i<num_time_steps; ++i) {
            for (Ordinal j=0; j<num_probes+1; ++j) {
              Scalar x;
              const char *format = (sizeof(x) == sizeof(double)) ? "%le": "%e";
              const int r = fscanf ( fp, format, &x);
              v[i][j] = x;
              if (r != 1) {
                comm->cout()<<"Error reading file: "<<filename<<endl;
                comm->cout()<<"  Elements read: "<<r<<" expected: "<<1<<endl;
                comm->error("Response::read_probe::fscanf");
              }
            }
          }
        } else {
          const size_t c = v.size();
          const size_t r = fread(v.data(), sizeof(scalar), c, fp);
          if (r != c) {
            comm->cout()<<"Error reading file: "<<filename<<endl;
            comm->cout()<<"  Read: "<<r<<" data points, expected: "<<c<<endl;
            comm->error("Response::read_probe::fread");
          }
        }
        for (Ordinal nr=0; nr<num_probes; nr++) {
          for (Ordinal nt=0; nt<num_time_steps; nt++) {
            trace[nr][ns][nc][nt] = v[nt][nr+1];
          }
        }
      }
      fclose(fp);
    }
  }
}

#ifdef DGM_PARALLEL

template <typename scalar,  typename datatype>
void Response::read_probe_combined_parallel
(vector<CMC::Array<datatype,Ordinal> > &trace,
 const vector<int> &D,
 const vector<string> &component_names,
 const string &state_root,
 const string &run_file_base)
{
  const size_t num_probes     = trace.size();
  const size_t number_of_runs = trace.empty() ? 0 : trace.front().dim1();
  const size_t num_components = trace.empty() ? 0 : trace.front().dim2();
  const size_t num_time_steps = trace.empty() ? 0 : trace.front().dim3();
  const MPI_Datatype size_type =
    sizeof(scalar)==sizeof(double) ? MPI_DOUBLE : MPI_FLOAT;
  MPI_Comm ioComm = MPI_COMM_NULL;
  MPI_Comm mpi_comm=dynamic_cast<const DGM::MpiComm*>(comm.get())->mpi_comm;
  const int membershipKey = num_probes ? 1 : MPI_UNDEFINED;
  if (int stat = MPI_Comm_split(mpi_comm, membershipKey, 0, &ioComm) )
    comm->error("Response::read_probe:MPI_Comm_split", stat);

  if (membershipKey == 1) {
    DGM::MpiComm dgm_ioComm(ioComm,"Response::ioComm");
    MPI_Datatype wholefile=MPI_DATATYPE_NULL;
    if (probeTrans) {
      MPI_Datatype filetype=MPI_DATATYPE_NULL;
      if (probeTimeTrace)
        comm->error(
          "Response::read_probe: Cannot both Transpose and Time Trace.");

      if (int stat = MPI_Type_contiguous(num_time_steps, size_type, &filetype))
        comm->error("Response::read_probe::MPI_Type_create_indexed_block",stat);

      if (int stat = MPI_Type_commit(&filetype))
        comm->error("Response::read_probe_datread_probe::MPI_Type_commit",stat);

      vector<int> displacements(D);
      for (size_t z=0; z<D.size(); ++z) --displacements[z];
      if (int stat = MPI_Type_create_indexed_block(num_probes, 1,
                                                   &displacements[0],
                                                   filetype, &wholefile))
        comm->error("Response::read_probe::MPI_Type_create_indexed_block",stat);
      MPI_Type_free(&filetype);
    } else {
      MPI_Datatype filetype=MPI_DATATYPE_NULL;
      vector<int> displacements(D);
      if (int stat = MPI_Type_create_indexed_block(num_probes, 1,
                                                   &displacements[0],
                                                   size_type, &filetype))
      comm->error("Response::read_probe::MPI_Type_create_indexed_block",stat);

      if (int stat = MPI_Type_commit(&filetype))
        comm->error("Response::read_probe_datread_probe::MPI_Type_commit",stat);

      vector<int> lengths(num_time_steps,1);
      vector<MPI_Aint> disp(num_time_steps);
      const unsigned number_of_time_traces = probeTimeTrace ? 1 : 0;
      const unsigned record_len =
          sizeof(scalar)*(number_of_time_traces+nProbes);
      for (size_t i=0;i<num_time_steps;++i) disp[i] = i*record_len;
      if (int stat = MPI_Type_create_hindexed(num_time_steps,
                                              &lengths[0],
                                              &disp[0],
                                              filetype,
                                              &wholefile ))
      comm->error("Response::read_probe::MPI_Type_create_hindexed",stat);
      MPI_Type_free(&filetype);
    }
    if (int stat = MPI_Type_commit(&wholefile))
      comm->error("Response::read_probe::MPI_Type_commit_II", stat);

    const char *cnative="native";
    char *native = const_cast<char*>(cnative);

    const size_t dim1 = probeTrans ? num_probes : num_time_steps;
    const size_t dim2 = probeTrans ? num_time_steps: num_probes;
    CMC::Matrix< scalar, Size > v(dim1, dim2);
    MPI_File fh = MPI_FILE_NULL;
    CMC::Stopwatch cpu;
    for (unsigned nc=0; nc<num_components; ++nc) {
      for (unsigned ns=0; ns<number_of_runs; ++ns) {
          char runnumber[128]; sprintf(runnumber,".%d",ns);
          const string pathname = run_file_base + runnumber + "/";
          const string filename = pathname + state_root + "." +
            component_names[nc]+".prb";
          if (verb>1)
            dgm_ioComm.cout() << "  Read probe file " << filename;
          if (dgm_ioComm.Master()) cpu.start();
          if (int stat = MPI_File_open(ioComm,
                                       const_cast<char*>(filename.c_str()),
                                       MPI_MODE_RDONLY, MPI_INFO_NULL,
                                       &fh)) {
            char err_buffer[MPI_MAX_ERROR_STRING];
            int resultlen;
            MPI_Error_string(stat,err_buffer,&resultlen);
            dgm_ioComm.cout()<<" Error opening file: "<<filename<<endl;
            dgm_ioComm.cout()<<" Error returned from MPI_File_open: "
                             << err_buffer << endl;
            string msg("Response::read_probe::MPI_File_open failed on: ");
            msg += filename;
            dgm_ioComm.error(msg, stat);
          }
          MPI_File_set_errhandler(fh,MPI_ERRORS_ARE_FATAL);
          if (int stat = MPI_File_set_view(fh, 0, size_type,
                                           wholefile, native, MPI_INFO_NULL))
            dgm_ioComm.error("Response::read_probe::MPI_File_set_view", stat);
          MPI_Status status;
          if (int stat =  MPI_File_read_all(fh, v[0],
                                            num_probes*num_time_steps,
                                            size_type, &status)) {
            char err_buffer[MPI_MAX_ERROR_STRING];
            int resultlen;
            MPI_Error_string(stat,err_buffer,&resultlen);
            dgm_ioComm.cout()<<" Error reading file:"<<filename<<endl;
            dgm_ioComm.cout()<<" Error returned from MPI_File_read_all_end:"
                             <<err_buffer<<endl;
            dgm_ioComm.error("Response::read_probe::MPI_File_read_all_end",
                stat);
          }
          if (probeTrans) {
            for (size_t nr=0; nr<num_probes; nr++) {
              for (size_t nt=0; nt<num_time_steps; nt++) {
                trace[nr][ns][nc][nt] = v[nr][nt];
              }
            }
          } else {
            for (size_t nr=0; nr<num_probes; nr++) {
              for (size_t nt=0; nt<num_time_steps; nt++) {
                trace[nr][ns][nc][nt] = v[nt][nr];
              }
            }
          }
          MPI_File_close(&fh);
          fh = MPI_FILE_NULL;
          if (verb>1) {
            dgm_ioComm.cout() << " in " << cpu.stop() << " sec" << endl;
          }
          cpu.reset();
      }  // number of runs
    }  // number of components
    MPI_Type_free(&wholefile);
  }  // membershipkey
  if (ioComm != MPI_COMM_NULL &&
      ioComm != MPI_COMM_SELF && 
      ioComm != MPI_COMM_WORLD) 
    MPI_Comm_free(&ioComm);
}

#endif  // DGM_PARALLEL

template <typename scalar, typename datatype>
void Response::read_probe(vector<CMC::Array<datatype,Ordinal> > &trace,
                          const vector<int> &D,
                          const vector<string> &component_names,
                          const string &state_root,
                          const string &run_file_base) {
#ifdef DGM_PARALLEL
  if (ASCII!=probeFormat && COMBINED==probeFiles) {
    read_probe_combined_parallel<scalar, datatype>(trace, D, component_names,
                                           state_root, run_file_base);
    return;
  }
#endif
  if (COMBINED == probeFiles) {
    read_probe_combined_serial<scalar, datatype>(trace, component_names,
                                       state_root, run_file_base);
  } else {
    read_probe_separate_serial<scalar, datatype>(trace, state_root,
                                                 run_file_base);
  }
}

template <typename datatype>
void Response::write_norms(const vector<CMC::Array<datatype,Ordinal> > &trace,
                           const vector<string> &component_names) {
  const size_t num_probes     = trace.size();
  const size_t number_of_runs = trace.empty() ? 0 : trace.front().dim1();
  const size_t num_components = trace.empty() ? 0 : trace.front().dim2();
  const size_t num_time_steps = trace.empty() ? 0 : trace.front().dim3();

  CMC::Array<datatype,size_t> Norms(num_probes, number_of_runs, num_components);
  for (size_t p = 0; p < num_probes; p++) {
    for (size_t ns = 0; ns < number_of_runs; ns++) {
      for (size_t nc = 0; nc < num_components; nc++) {
        datatype norm=0;
        for (size_t istep = 0; istep < num_time_steps; istep++) {
          const Ordinal lns = numeric_cast<Ordinal>(ns);
          const datatype t = trace[p][lns][nc][istep];
          norm += t*t;
        }
        Norms[p][ns][nc] = sqrt(norm);
      }
    }
  }
  const ios_base::fmtflags flags = cout.flags();
  if (comm->Master()) {
    cout <<"  Response Information:  Norms of component data read."<<endl
         <<"    Columns are instances, rows are local probe number."<<endl;
  }
  for (int np=0; np<comm->NumProc(); ++np) {
    if (comm->MyPID() == np) {
      for (size_t nc = 0; nc < num_components; nc++) {
        cout << "Norms for component "<<component_names[nc]
             << " on processor "<<np<<endl;
        for (size_t p = 0; p < num_probes; p++) {
          cout << setw(3) << p <<"  ";
          for (size_t ns = 0; ns < number_of_runs; ns++) {
            if (ns && !(ns%10)) cout << endl <<"     ";
            cout << setw(9) << setprecision(2) << scientific
                         << Norms[p][ns][nc];
          }
          cout <<endl;
        }
      }
    }
    cout <<flush;
    comm->Barrier();
  }
  cout.flags(flags);
}

bool Response::get_interpolation_info(Ordinal &probe_num_time_steps,
                                      const vector<string> &component_names,
                                      Scalar &probe_data_dt,
                                      const unsigned num_probes,
                                      const string &state_root,
                                      const string &run_file_base )
{
  const bool interpolate_in_time =
      deltaTime != probeDeltaTime && deltaTime && probeDeltaTime;
  probe_data_dt = deltaTime;
  if (interpolate_in_time && !probes.empty()) {
    probe_data_dt = probeDeltaTime;
    Probe::Ptr probe = probes[0];
    char runnumber[128]; sprintf(runnumber,".%d",0);
    const string var_name =
          COMBINED==probeFiles ? component_names[0]
                               : probe->kernel->name().c_str();
    const string pathname = run_file_base + runnumber + "/";
    const string filename = pathname+state_root+"."+var_name;
    streamoff fsize = probe->file_size(comm, filename, probeFormat);
    fsize /= (FLOAT==probeFormat) ? sizeof(float) : sizeof(double);
    probe_num_time_steps = numeric_cast<Ordinal>(fsize / num_probes);
  }
  return interpolate_in_time;
}

/** This chops one character off the component names. */
void Response::read_probe(vector<dArray> &trace,
                          const string &state_root,
                          const string &run_file_base,
                          const vector<string> &component_names,
                          const int chop) {
  vector<string> chopped_names(component_names);
  if (chop) {
    for (unsigned i=0; i<chopped_names.size(); ++i)
      chopped_names[i].erase(chopped_names[i].end()-chop);
  }
  const Ordinal num_probes=trace.empty()?0:numeric_cast<Ordinal>(trace.size());
  vector<int> D(num_probes,0);
  Ordinal d=0;
  for (vector<Probe>::size_type k=0; k< probes.size() && d<num_probes; ++k) {
    const Probe::Ptr probe = probes[k];
    if (probe->kernel->locally_evaluated()) {
      D[d++] = numeric_cast<int>(probe->kernel->global_id()+1);
    }
  }
  if (FLOAT==probeFormat)
    read_probe<float, Scalar>(trace, D, chopped_names, state_root,
                              run_file_base);
  else
    read_probe<double, Scalar>(trace, D, chopped_names, state_root,
                               run_file_base);
}

Ordinal Response::time_steps_from_file(
    const string &state_root,
    const string &run_file_base,
    const vector<string> &component_names) const
{
  if (!probeNumSamples) {
    comm->cout() << " ******  Response parameter warning ***** : \n"
    "  Number of samples not specified in the Response Json input.  This will\n"
    "  be inferred from the size of the response input file, file type (float\n"
    "  or double), the number of traces and if there is a time trace or not,\n"
    "  but it would be better to specify it yourself."<< endl;
  }
  if (probes.empty() && COMBINED!=probeFiles) {
    if (probeNumSamples) return probeNumSamples;
    else
      comm->error(" Response::time_steps_from_file: No probe available to \n"
        "determine number of probe time steps. Must set the number of \n"
        "samples in probe file in the input.");
  }
  char runnumber[128]; sprintf(runnumber,".%d",0);
  const string var_name =
        COMBINED==probeFiles ? component_names[0]
                             : probes[0]->kernel->name().c_str();
  const string pathname = run_file_base + runnumber + "/";
  const string filename = pathname+state_root+"."+var_name;
  if (verb>1)
    comm->cout()<<"  Function Response::time_steps_from_file:"<<endl
                <<"    filename = "<<filename<<endl
                <<"    var_name = "<<var_name
                <<" probeFormat = "<<probe_format(probeFormat)
                << endl;
  const streamoff filesize = Probe::file_size(comm, filename, probeFormat);

  const int sizeof_scalar = (FLOAT==probeFormat)?sizeof(float):sizeof(double);
  const streamoff fsize = filesize / sizeof_scalar;
  const streamoff n1 = probeTimeTrace ? nProbes+1 : nProbes;
  const streamoff num_samples = fsize / n1;
  if (numeric_cast<streamoff>(num_samples * n1) != fsize)
    comm->cout() << " ******  Response parameter warning ***** : "
       <<"      It appears that the response file size is not a"
       <<" multiple of the number of probes in the file."<<endl
       <<"      Given that the file is "<<filesize
       <<" bytes with "<<probe_format(probeFormat)
       <<" data with each sample "<<sizeof_scalar
       <<" bytes, there are "<<fsize<<" samples in the file."<<endl
       <<"      There are "<<nProbes<<" probes and there"
       << (probeTimeTrace?" is ":" is no ")<<"probe times for"
       <<" a total of "<<n1<<" probes which does not divide evenly."
       <<endl
       <<"      It is possible to get this warning if not using all"
       <<" of the probes in the response file."
       <<endl;
  if (probeNumSamples) {
    if (numeric_cast<streamoff>(probeNumSamples * n1) != fsize)
      comm->cout() << " ******  Response parameter warning ***** : "
         <<"      The response file size is not the number of probes"
         <<" times the number of the time steps in the file."<<endl
         <<"      Given that the file is "<<filesize
         <<" bytes with "<<probe_format(probeFormat)
         <<" data with each sample "<<sizeof_scalar
         <<" bytes, there are "<<fsize<<" samples in the file."<<endl
         <<"      There are "<<nProbes<<" probes and there"
         << (probeTimeTrace?" is ":" is no ")<<"probe times for"
         <<" a total of "<<n1<<" probes."<<endl
         <<"      There are "<<probeNumSamples<<" time steps for"
         <<" total of "<<probeNumSamples*n1<<" samples which is"
         <<" not equal to the file size."
         <<endl;
    const streamoff nprobe = fsize / probeNumSamples;
    if (numeric_cast<streamoff>(nprobe * probeNumSamples) != fsize)
      comm->cout() << " ******  Response parameter warning ***** : "
         <<"      It appears that the response file size is not a"
         <<" multiple of the number of the time steps in the file."<<endl
         <<"      Given that the file is "<<filesize
         <<" bytes with "<<probe_format(probeFormat)
         <<" data with each sample "<<sizeof_scalar
         <<" bytes, there are "<<fsize<<" samples in the file."<<endl
         <<"      There are "<<probeNumSamples<<" time steps for"
         <<" a total of "<<nprobe<<" probes which does not divide evenly."
         <<endl;
  }
  return probeNumSamples ? probeNumSamples : numeric_cast<Ordinal>(num_samples);
}

Ordinal Response::init_probe_data(const string &state_root,
                               const string &run_file_base,
                               const vector<string> &component_names,
                               const Ordinal Nrealizations,
                               const Ordinal Nt) {
  FunctionTimer *t=0;
  if (verb>2) {static FunctionTimer T("Response::init_probe_data"); t=&T;}
  FunctionSentry sentry(t);
  comm->cout()<<"Starting read of probe data: "<<comm->dateTime()<<std::endl;

  nRealizations = Nrealizations;
  ComponentsToApply = numeric_cast<Ordinal>(component_names.size());
  fprobe_trace_data.clear();
  dprobe_trace_data.clear();
  const bool interpolate_in_time =
    deltaTime != probeDeltaTime && deltaTime && probeDeltaTime;
  if (interpolate_in_time)
    comm->cout()<<"  Response is using Interpolation:\n"
                <<"    Simulation time step = "<<deltaTime<<"\n"
                <<"    Probe time step      = "<<probeDeltaTime<<endl;
  else
    comm->cout()<<"  Response is *NOT* using Interpolation:\n"
                <<"    Simulation time step = "<<deltaTime<<"\n"
                <<"    Probe time step      = "<<probeDeltaTime<<endl;
  if (verb>1)
    comm->cout()<<"  Response::init_probe_data: interp = "<<interpolate_in_time
                <<", deltaTime = "<<deltaTime<<", probeDeltaTime = "
                <<probeDeltaTime<<endl;
  // The trace needs to allocate Nt+1 so that it can hold both the
  // initial condition sample and the final solution sample.
  probeDataLength = interpolate_in_time ?
      time_steps_from_file(state_root,run_file_base,component_names) : Nt+1;
  if (verb>1)
    comm->cout()<<"  probeDataLength  = "<<probeDataLength<<endl;
  const Ordinal lprobeDataLength   = numeric_cast<Ordinal>(probeDataLength);
  const Ordinal lComponentsToApply = numeric_cast<Ordinal>(ComponentsToApply);
  const Ordinal lnRealizations     = numeric_cast<Ordinal>(nRealizations);
  if (FLOAT==probeFormat) {
    if (nRealizations && probeDataLength && ComponentsToApply) {
      for (size_t nr=0; nr<gid_to_lid.size(); nr++) {
        fprobe_trace_data.push_back(
            fArray(lnRealizations,lComponentsToApply,lprobeDataLength));
      }
    }
  } else {
    if (nRealizations && probeDataLength && ComponentsToApply) {
      for (unsigned nr=0; nr<gid_to_lid.size(); nr++) {
        dprobe_trace_data.push_back(
            dArray(lnRealizations,lComponentsToApply,lprobeDataLength));
      }
    }
  }
  vector<int> D(gid_to_lid.size(), numeric_limits<int>::max());
  for (map<Size,Ordinal>::const_iterator i=gid_to_lid.begin();
       i!=gid_to_lid.end(); ++i) {
    D[i->second] = numeric_cast<int>(i->first + 1);
  }

  for (size_t i=0; i<D.size(); ++i)
    if (numeric_limits<int>::max() == D[i])
      comm->error(" Response::init_probe_data: Error in setting probe "
                  "D(isplacements).");

  if (FLOAT==probeFormat)
    read_probe<float, float>(fprobe_trace_data, D, component_names,
        state_root, run_file_base);
  else
    read_probe<double, double>(dprobe_trace_data, D, component_names,
        state_root, run_file_base);
  if (verb>2) {
    if (FLOAT==probeFormat)
      write_norms<float> (fprobe_trace_data, component_names);
    else
      write_norms<double>(dprobe_trace_data, component_names);
  }

  comm->cout()<<"Finished read of probe data: "<<comm->dateTime()<<std::endl;
  return probeDataLength;
}

Ordinal Response::LocalNumProbeData() const {
  return numeric_cast<Ordinal>(isFloat() ? fprobe_trace_data.size() :
                            dprobe_trace_data.size());
}
Ordinal Response::LocalNumRealizations() const {
  return LocalNumProbeData() ?  (isFloat() ? fprobe_trace_data[0].dim1() :
                                 dprobe_trace_data[0].dim1()) : 0;
}
Ordinal Response::LocalNumComponents() const {
  return LocalNumProbeData() ? (isFloat() ? fprobe_trace_data[0].dim2() :
                                dprobe_trace_data[0].dim2()) : 0;
}
Ordinal Response::LocalNumTimeValues() const {
  return LocalNumProbeData() ?  (isFloat() ? fprobe_trace_data[0].dim3() :
                                 dprobe_trace_data[0].dim3()) : 0;
}
Ordinal Response::ProbeDataSize() const {
  return LocalNumProbeData() *
         LocalNumRealizations() *
         LocalNumComponents() *
         LocalNumTimeValues() *
         ( isFloat() ?  sizeof(float) : sizeof(double)) ;
}

Scalar Response::ProbeData(const Ordinal p,
                           const Ordinal r,
                           const Ordinal c,
                           const Ordinal t) const {
  return isFloat() ? fprobe_trace_data[p][r][c][t]
                   : dprobe_trace_data[p][r][c][t] ;
}

// Interpolate the weights correctly in time
void Response::interpolate_weights(const dArray &weights,
                                   TimeInt *time_int,
                                   const Scalar time,
                                   const Ordinal istep,
                                   const Ordinal sstep,
                                   dMatrix &now) const {
  if (sstep) {
    for (Ordinal p=0; p<now.rows(); ++p) {
      for (Ordinal nc=0; nc<now.cols(); nc++) {
        Scalar iweight = weights[p][istep][nc];
        time_int->interpolate(sstep,weights[p][istep+1][nc], iweight);
        now[p][nc] = iweight;
      }
    }
  } else {
    for (Ordinal p=0; p<now.rows(); ++p) {
      for (Ordinal nc=0; nc<now.cols(); nc++) {
        now[p][nc] = weights[p][istep][nc];
      }
    }
  }
}

// SSC:  this really interpolates the weights in time and multiplies the data
// by the square root of the weights
void Response::multiply_by_weights(dMatrix &data,
                                   const dArray &weights,
                                   TimeInt *time_int,
                                   const Ordinal istep,
                                   const Ordinal sstep) const{
  if (sstep) {
    for (Ordinal p=0; p<data.rows(); ++p) {
      for (Ordinal nc=0; nc<data.cols(); nc++) {
        Scalar iweight = weights[p][istep][nc];
        time_int->interpolate(sstep,weights[p][istep+1][nc], iweight);
        data[p][nc] *= sqrt(iweight);
      }
    }
  } else {
    for (Ordinal p=0; p<data.rows(); ++p) {
      for (Ordinal nc=0; nc<data.cols(); nc++) {
        data[p][nc] *= sqrt(weights[p][istep][nc]);
      }
    }
  }
}

bool
Response::subtract_weighted_traces(dMatrix &data,
                                   const dVector &ws,
                                   const TimeInt *time_int,
                                   const Interpolator *time_interpolate,
                                   const Scalar  dt,
                                   const Ordinal istep,
                                   const Ordinal sstep) {
  if (isFloat())
    return subtract_weighted_traces(data,
                                    fprobe_trace_data,
                                    ws,
                                    time_int,
                                    time_interpolate,
                                    dt,
                                    istep,
                                    sstep);
  else
    return subtract_weighted_traces(data,
                                    dprobe_trace_data,
                                    ws,
                                    time_int,
                                    time_interpolate,
                                    dt,
                                    istep,
                                    sstep);
}

template <typename scalar> bool
Response::subtract_weighted_traces(
    dMatrix &obj,
    const vector<CMC::Array<scalar,Ordinal> > &trace_data,
    const dVector &ws,
    const TimeInt *time_int,
    const Interpolator *time_interpolate,
    const Scalar  dt,
    const Ordinal istep,
    const Ordinal sstep)
{
  //comm->cout()<<"Response::subtract_weighted_traces"<<endl;
  FunctionTimer *t=0;
  if (verb>2) {
    static FunctionTimer T("Response::subtract_weighted_traces"); t=&T;
  }
  FunctionSentry sentry(t);
  typedef CMC::Matrix<scalar, Ordinal> xMatrix;
#ifdef DGM_PARALLEL
  // Post receive calls...
  MPI_Comm mpi_comm = (dynamic_cast<MpiComm*>(comm.get()))->mpi_comm;
  for (unsigned i=0; i<recv_info.size(); ++i) {
    dMatrix   &buf = recv_info[i].buf;
    buf = numeric_limits<Scalar>::max();
    const int from = recv_info[i].from;
    const int len = buf.size();
    const int tag = 99;
    const int stat = MPI_Irecv(buf.data(), len, MPI_DOUBLE, from, tag,
                               mpi_comm, &recv_requests[i]);
    if (stat) comm->error("MPI_Irecv  #1 ", stat);
  }
#endif
  const Ordinal data_probes = LocalNumProbeData();
  const Ordinal nProbes = numeric_cast<Ordinal>(probes.size());
  const bool interpolate_probe_data =
      deltaTime != probeDeltaTime && deltaTime && probeDeltaTime;

  if (interpolate_probe_data && !time_interpolate)
    throw DGM::exception("Interpolation is required and no Interpolator is "
                         "defined in Response::subtract_weighted_traces");

  //comm->cout()<<"Response::subtract_weighted_traces: data_probes = "
  //            <<data_probes <<", nProbes = " << nProbes <<", interpolate = "
  //            <<interpolate_probe_data<<endl;

  if (numeric_cast<Ordinal>(obj.dim1()) != nProbes)
    comm->error("Response::subtract_weighted_traces: Probe data wrong size.");
  if (probes.size() &&  ComponentsToApply != 1 &&
      numeric_cast<Ordinal>(obj.dim2()) != ComponentsToApply)
    comm->error((string)"Response::subtract_weighted_traces:"+
                "Components data wrong size.  "+
                asString(obj.dim2())+" vs. "+asString(ComponentsToApply));
  if (nRealizations==0)
    throw logic_error("Response: nRealizations = 0 on rank "+
        asString(comm->MyPID()));
  if (ComponentsToApply==0)
    throw logic_error("Response: ComponentsToApply = 0 on rank "+
        asString(comm->MyPID()));
  dMatrix OBJ;
  //
  // James:  can you please check this.  Sometimes data_probes=0 (when
  // there is no local probe on this rank.  The old code would try to
  // allocate OBJ with a zero size in the first dimension which would
  // trigger an assert when CMC_BOUNDS_CHECK is on.  The current approach
  // "fixes" this, but OBJ is still used unallocated which is OK, I guess,
  // but seems like a segfault waiting to happen.
  //
  // Also, if there is zero data to communicate from this rank, do we need
  // to use a subcommunicator instead of the full comm?
  //
  const Ordinal ldata_probes = numeric_cast<Ordinal>(data_probes);
  const Ordinal lComponentsToApply = numeric_cast<Ordinal>(ComponentsToApply);
  const Ordinal lnRealizations = numeric_cast<Ordinal>(nRealizations);

  if (ldata_probes!=0) OBJ.resize(ldata_probes, lComponentsToApply);
  OBJ = 0;
  if (interpolate_probe_data) {
    if (sstep) {
      xMatrix Interp(lnRealizations, lComponentsToApply);
      xMatrix Jnterp(lnRealizations, lComponentsToApply);
      for (Ordinal p = 0; p < ldata_probes; p++) {
        Interp = time_interpolate->operator()(dt*istep,    trace_data[p]);
        Jnterp = time_interpolate->operator()(dt*(istep+1),trace_data[p]);
        for (Ordinal ns = 0; ns < lnRealizations; ns++) {
          for (Ordinal nc = 0; nc < lComponentsToApply; nc++) {
            const Scalar x = Interp[ns][nc];
            const Scalar y = Jnterp[ns][nc];
            const Scalar t = time_int->interpolate(x, y, sstep);
            OBJ[p][nc] += t*ws[ns];
          }
        }
      }
    } else {
      xMatrix Interp(lnRealizations, lComponentsToApply);
      for (Ordinal p = 0; p < ldata_probes; p++) {
        Interp = time_interpolate->operator()(dt*istep, trace_data[p]);
        for (Ordinal ns = 0; ns < lnRealizations; ns++) {
          for (Ordinal nc = 0; nc < lComponentsToApply; nc++) {
            const Scalar t = Interp[ns][nc];
            OBJ[p][nc] += t*ws[ns];
          }
        }
      }
    }
  } else {             // no interpolation other that substeps
    if (sstep) {
      for (Ordinal p = 0; p < ldata_probes; p++) {
        for (Ordinal ns = 0; ns < lnRealizations; ns++) {
          for (Ordinal nc = 0; nc < lComponentsToApply; nc++) {
            const Scalar x = trace_data[p][ns][nc][istep  ];
            const Scalar y = trace_data[p][ns][nc][istep+1];
            const Scalar t = time_int->interpolate( x, y, sstep );
            OBJ[p][nc] += t*ws[ns];
          }
        }
      }
    } else {
      for (Ordinal p = 0; p < ldata_probes; p++) {
        for (Ordinal ns = 0; ns < lnRealizations; ns++) {
          for (Ordinal nc = 0; nc < lComponentsToApply; nc++) {
            const scalar t = trace_data[p][ns][nc][istep];
            OBJ[p][nc] += t*ws[ns];
          }
        }
      }
    }
  }
  //comm->cout()<<istep<<" "<<sstep<<" "<<OBJ[0][0]<<endl;
  //comm->cout()<<"Response::subtract_weighted_traces 2"<<endl;
#ifdef DGM_PARALLEL
  {
    // Free up send buffers....
    const int count = send_requests.size();
    vector<MPI_Status> statuses(count);
    const int stat = MPI_Waitall(count, &send_requests[0], &statuses[0]);
    if (stat) comm->error("MPI_Waitall  #2 ", stat);
  }
  // Post send calls...
  for (unsigned i=0; i<send_info.size(); ++i) {
    dMatrix &buf = send_info[i].buf;
    buf = numeric_limits<Scalar>::max();
    const int to = send_info[i].to;
    const int len = buf.size();
    const vector<Ordinal> &lid = send_info[i].lid;
    const int tag = 99;
    for (unsigned p = 0; p<lid.size(); ++p) {
      if (data_probes < lid[p]) comm->error(" Subscript out of range.");
      for (Ordinal nc = 0; nc < ComponentsToApply; nc++) {
        buf[p][nc] = OBJ[lid[p]][nc];
      }
    }
    const int stat = MPI_Isend(buf.data(), len, MPI_DOUBLE, to, tag,
                               mpi_comm, &send_requests[i]);
    if (stat) comm->error("MPI_Isend  #3 ", stat);
  }
  {
    // Fill up receive buffers...
    const int count = recv_requests.size();
    vector<MPI_Status> statuses(count);
    const int stat = MPI_Waitall(count, &recv_requests[0], &statuses[0]);
    if (stat) comm->error("MPI_Waitall  #4 ", stat);
  }
  OBJ.resize(nProbes, ComponentsToApply);
  OBJ = numeric_limits<Scalar>::max();
  // copy received data...
  vector<unsigned> filled_row(nProbes,0);
  for (unsigned i=0; i<recv_info.size(); ++i) {
    const vector<Ordinal> &lid = recv_info[i].lid;
    dMatrix &buf = recv_info[i].buf;
    for (unsigned p = 0; p<lid.size(); ++p) {
      if (nProbes < lid[p]) comm->error(" Subscript out of range.");
      if (filled_row[lid[p]]) comm->error(" Filling row twice.");
      filled_row[lid[p]] = 1;
      for (Ordinal nc = 0; nc < ComponentsToApply; nc++) {
        OBJ[lid[p]][nc] = buf[p][nc];
      }
    }
  }
  for (Ordinal i=0; i<nProbes; ++i)
    if (!filled_row[i]) comm->error(" Did not fill row.");
#endif

  for (Ordinal p=0; p<obj.dim1(); ++p)
    for (Ordinal nc=0; 
         nc<min(numeric_cast<Ordinal>(obj.dim2()), ComponentsToApply);
         ++nc)
      obj[p][nc] -= OBJ[p][nc];

  if (verb>2) {
    static Scalar Norm = 0;
    Scalar norm = 0;
    for (Ordinal p=0; p<obj.dim1(); ++p) {
      for (Ordinal nc=0;
           nc<min(numeric_cast<Ordinal>(obj.dim2()),ComponentsToApply);
           ++nc) {
        norm += OBJ[p][nc]*OBJ[p][nc];
      }
    }
    const Scalar x = norm;
    comm->SumAll(&x, &norm, 1);

    if (sstep) {
      Norm += norm;
    } else if (istep) {
      Norm = sqrt(Norm);
      if (comm->Master()) {
        cout <<" Norm of Response data subtracted during step "<<istep-1
             <<" is "<<setprecision(12)<<Norm<<endl;
      }
      Norm = norm;
    }
  }
  const bool data_needed = nProbes && nRealizations && ComponentsToApply;
  return data_needed;
}

/** \warning SSC This should not use trapezoidal integration. */
Scalar Response::weighted_norm(const dVector &ws, const Scalar dt,
                               const Interpolator *time_interpolate)  {
  comm->cout()<<"Response::weighted_norm (deprecated)"<<endl;
  FunctionTimer *t=0;
  if (verb>2) {static FunctionTimer T("Response::weighted_norm"); t=&T;}
  FunctionSentry sentry(t);

#ifdef DGM_PARALLEL
  // Post receive calls...
  MPI_Comm mpi_comm = (dynamic_cast<MpiComm*>(comm.get()))->mpi_comm;
  for (unsigned i=0; i<recv_info.size(); ++i) {
    dMatrix   &buf = recv_info[i].buf;
    buf = numeric_limits<Scalar>::max();
    const int from = recv_info[i].from;
    const int  len = recv_info[i].gid.size();
    const int  tag = 999;
    const int stat = MPI_Irecv(buf.data(), len, MPI_DOUBLE, from, tag,
                               mpi_comm, &recv_requests[i]);
    if (stat) comm->error("MPI_Irecv  #5 ", stat);
  }
#endif
  // SSC:  doesn't make sense that these are Size (i.e. GlobalSize)?
  const Ordinal Nprobes  = LocalNumProbeData();
  const Ordinal Nt       = LocalNumTimeValues();

  // compute ||ws data||^2
  const bool interpolate_probe_data =
      deltaTime != probeDeltaTime && deltaTime && probeDeltaTime;

  // SSC: these types should really be redefined as Ordinal and not Size
  const Ordinal lComponentsToApply = numeric_cast<Ordinal>(ComponentsToApply);
  const Ordinal lnRealizations = numeric_cast<Ordinal>(nRealizations);

  vector<Scalar> result(Nprobes, 0);
  for (Ordinal p=0; p<Nprobes; p++) {
    for (Ordinal t=0; t<Nt; t++) {
      Scalar integrand = 0;
      if (isFloat()) {
        if (interpolate_probe_data) {
          dMatrix Interp(time_interpolate->
              operator()(dt*t,dprobe_trace_data[p]));
          for (Ordinal nr=0; nr<lnRealizations; nr++) {
            for (Ordinal nc=0; nc<lComponentsToApply; nc++) {
              integrand += ws[nr]* Interp[nr][nc];
            }
          }
        } else {
          for (Ordinal nr=0; nr<lnRealizations; nr++) {
            for (Ordinal nc=0; nc<lComponentsToApply; nc++) {
              const Scalar itrace = dprobe_trace_data[p][nr][nc][t];
              integrand += ws[nr]*itrace;
            }
          }
        }
      } else {
        if (interpolate_probe_data) {
          fMatrix Interp (time_interpolate->
              operator()(dt*t,fprobe_trace_data[p]));
          for (Ordinal nr=0; nr<lnRealizations; nr++) {
            for (Ordinal nc=0; nc<lComponentsToApply; nc++) {
              integrand += ws[nr]* Interp[nr][nc];
            }
          }
        } else {
          for (Ordinal nr=0; nr<lnRealizations; nr++) {
            for (Ordinal nc=0; nc<lComponentsToApply; nc++) {
              const float itrace = fprobe_trace_data[p][nr][nc][t];
              integrand += ws[nr]*itrace;
            }
          }
        }
      }
      // trapezoid integration in time
      const Scalar fact = (t==0 || t==Nt-1) ? pt5*dt : dt;
      result[p] += fact * pow(integrand,2);
    }
  }
#ifdef DGM_PARALLEL
  {
    // Free up send buffers....
    const int count = send_requests.size();
    vector<MPI_Status> statuses(count);
    const int stat = MPI_Waitall(count, &send_requests[0], &statuses[0]);
    if (stat) comm->error("MPI_Waitall  #6 ", stat);
  }
  // Post send calls...
  for (unsigned i=0; i<send_info.size(); ++i) {
    dMatrix   &buf = send_info[i].buf;
    buf = numeric_limits<Scalar>::max();
    const int   to = send_info[i].to;
    const int  len = send_info[i].gid.size();
    const vector<Ordinal> &lid = send_info[i].lid;
    const int  tag = 999;
    for (unsigned p = 0; p<lid.size(); ++p) {
      if (Nprobes < lid[p]) comm->error(" Subscript out of range.");
      buf[p][0] = result[lid[p]];
    }
    const int stat = MPI_Isend(buf.data(), len, MPI_DOUBLE, to, tag,
                               mpi_comm, &send_requests[i]);
    if (stat) comm->error("MPI_Isend   #7 ", stat);
  }
  {
    // Fill up receive buffers...
    const int count = recv_requests.size();
    vector<MPI_Status> statuses(count);
    const int stat = MPI_Waitall(count, &recv_requests[0], &statuses[0]);
    if (stat) comm->error("MPI_Waitall   #8 ", stat);
  }
  result.resize(probes.size());
  for (unsigned i=0; i<result.size(); ++i)
    result[i] = numeric_limits<Scalar>::max();

  // copy received data...
  vector<unsigned> filled_row(result.size(),0);
  for (unsigned i=0; i<recv_info.size(); ++i) {
    const vector<Ordinal> &lid = recv_info[i].lid;
    dMatrix &buf = recv_info[i].buf;
    for (unsigned p = 0; p<lid.size(); ++p) {
      if (result.size() < static_cast<vector<Scalar>::size_type>(lid[p]))
        comm->error("Subscript out of range");
      if (filled_row[lid[p]]) comm->error(" Filling row twice.");
      filled_row[lid[p]] = 1;
      result[lid[p]] = buf[p][0];
    }
  }
  for (Ordinal i=0; i<nProbes; ++i)
    if (!filled_row[i]) comm->error(" Did not fill row.");
#endif
  Scalar total = 0;
  for (unsigned p=0; p<probes.size(); ++p) total += result[p];
  return total;
}

} // namespace DGM
