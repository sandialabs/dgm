/** \file FieldSlice.cpp
    \brief Database for FieldSlice algorithm storage
    \author James Overfelt
    \author Scott Collis
*/

// system includes
#include <vector>
#include <cmath>

// boost includes
#include "boost/numeric/conversion/cast.hpp"
using boost::numeric_cast;

// DGM includes
#include "Comm.hpp"
#ifdef DGM_PARALLEL
#include "MpiComm.hpp"
#endif
#include "Types.hpp"
#include "FieldSlice.hpp"
#include "Field.hpp"
#include "CaseInsensitiveString.hpp"

// JSON includes
#ifdef DGM_USE_JSON
#include "json/json.h"
#include "json/serialization.h"
#endif

using namespace std;
using namespace DGM;

namespace {

// The whole DefaultPartition class was copied complete and unchanged from the
// Partition.tpp file.  Since it was hidden in an anonmous namespace it could
// not be used and it seemed easier to copy this small class here.
template<typename GlobalSize, typename LocalSize>
class DefaultPartition {
public :
  DefaultPartition(const DGM::Comm::Ptr comm_, GlobalSize gne_) :
    comm(comm_), me(comm->MyPID()), np(comm->NumProc()), gne(gne_),
    first(begin(me)), last(begin(me+1))
  {}

  /// global id to processor number.
  LocalSize proc(const GlobalSize id) const {
    static LocalSize prev_p=0;
    LocalSize p=0;
    if (begin(prev_p)<=id && id<begin(prev_p+1))
      p = prev_p; // optimize for the special case of sequential ids
      // could add in the case of looping from prev_p to np?
    else
      for (; p<np; ++p) if (begin(p)<=id && id<begin(p+1)) break;
    prev_p=p;
    return p;
  }

  /// beginning global id on this processor.
  GlobalSize begin() const { return first; }

  /// beginning global id on next processor, one greater then what is local.
  GlobalSize end() const { return last; }

private:

  /// processor number to first global id on that processor.
  GlobalSize begin(const LocalSize p) const {
    return numeric_cast<GlobalSize>((size_t)p*((size_t)gne)/((size_t)np));
  }
  const DGM::Comm::Ptr comm;  ///< parallel communicator
  const LocalSize me;         ///< my process id
  const LocalSize np;         ///< number of processors
  const GlobalSize gne;       ///< the bulk of the objects, gne/np
  const GlobalSize first;     ///< first on this processor
  const GlobalSize last;      ///< last on this processor
};

} // anonymous namespace

namespace DGM {

// SliceData is the parsed up Json input.  It is not used after
// initialization.  All the data within this class has a direct equivalent in
// the Json definition of the "Field Slice" syntax.  This class is only used
// internal to this source file.
struct SliceData {
  enum FORMAT {FLOAT, DOUBLE};
  struct Output {
    Output() : Field(), File(), Default(0) {}
    Output(const Output &s):
      Field  (s.Field  ),
      File   (s.File   ),
      Default(s.Default){}
    Output operator=(const Output &s) {
      Field   =s.Field  ;
      File    =s.File   ;
      Default =s.Default;
      return *this;
    }
    std::string Field;
    std::string File ;
    Scalar      Default;
  };
  SliceData() :
    SCALAR_DEF  (std::numeric_limits<Scalar>::max()),
    ORDINAL_DEF (std::numeric_limits<Ordinal>::max()),
    CacheInterpolationData(false),
    Outputs     (),
    Origin      (SCALAR_DEF,SCALAR_DEF,SCALAR_DEF),
    Lattice     (),
    Dimensions  (),
    Format      (FLOAT),
    Frequency   (1),
    Intervals   (),
    Verbosity   (0)
  {}
  SliceData(const Ordinal nsd) :
    SCALAR_DEF  (std::numeric_limits<Scalar>::max()),
    ORDINAL_DEF (std::numeric_limits<Ordinal>::max()),
    CacheInterpolationData(false),
    Outputs     (),
    Origin      (SCALAR_DEF,SCALAR_DEF,SCALAR_DEF),
    Lattice     (),
    Dimensions  (),
    Format      (FLOAT),
    Frequency   (1),
    Intervals   (),
    Verbosity   (0)
  {set_nsd(nsd);}

  void set_nsd(const Ordinal nsd)
  {
    Lattice.resize(nsd,nsd);
    Lattice = 0;
    if      (3==nsd) Lattice[0][2]=Lattice[1][0]=Lattice[2][1]=1;
    else if (2==nsd) Lattice[0][0]=Lattice[1][1]=1;
    else if (1==nsd) Lattice[0][0]=1;
    Dimensions.resize(nsd);
    if (0<nsd) Dimensions[0] = ORDINAL_DEF;
    if (1<nsd) Dimensions[1] = ORDINAL_DEF;
    if (2<nsd) Dimensions[2] = ORDINAL_DEF;
  }
  SliceData(const SliceData &s)  :
    SCALAR_DEF (std::numeric_limits<Scalar>::max()),
    ORDINAL_DEF(std::numeric_limits<Ordinal>::max()),
    CacheInterpolationData(s.CacheInterpolationData),
    Outputs    (s.Outputs    ),
    Origin     (s.Origin     ),
    Lattice    (s.Lattice    ),
    Dimensions (s.Dimensions ),
    Format     (s.Format     ),
    Frequency  (s.Frequency  ),
    Intervals  (s.Intervals  ),
    Verbosity  (s.Verbosity  )
  {}
  SliceData operator=(const SliceData &s) {
    CacheInterpolationData = s.CacheInterpolationData;
    Outputs    = s.Outputs    ;
    Origin     = s.Origin     ;
    Lattice.resize(s.Lattice);
    Lattice    = s.Lattice    ;
    Dimensions = s.Dimensions ;
    Format     = s.Format     ;
    Frequency  = s.Frequency  ;
    Intervals  = s.Intervals  ;
    Verbosity  = s.Verbosity  ;
    return *this;
  }

  // Since thare are very few instances of this class
  // make the default scalar and ordinal values
  // member data initialized in the constructor.
  const Scalar                   SCALAR_DEF;
  const Ordinal                  ORDINAL_DEF;
  bool                           CacheInterpolationData;
  std::vector<Output>            Outputs;
  Point                          Origin;
  dMatrix                        Lattice;
  std::vector<Ordinal>           Dimensions;
  FORMAT                         Format;
  int                            Frequency;
  set<int>                       Intervals;
  Ordinal                        Verbosity;
};

}  // namespace DGM

namespace {

  // Start parsing the input and stuffing the whole thing into a vector of
  // SliceData classes.  At the time the input is parsed, default parameters
  // will also be set for unspecified parameters. A change in default
  // parameters will need to be done in this block of code.
  //
  // Hmmmmm... Maybe this should be a member of the SliceData class?
  void parse_into_slice_data_struct(vector<SliceData> &slice_data,
                                    const Field *F,
                                    const Json::Value &slice_params,
                                    const Ordinal nsd,
                                    const DGM::Comm::Ptr comm)
  {
    const Json::ArrayIndex n = slice_params.size();
    for (Json::ArrayIndex p=0; p<n; ++p) {
      Json::Value params = slice_params[p];
      if (!params.isMember("Outputs")) {
        comm->error("Outputs not specified in Field Slices block.");
      }
      if (!params["Outputs"].size()) {
        comm->error("Outputs zero length in Field Slices block.");
      }
      SliceData data(nsd);
      {
        const Json::Value outputs = params["Outputs"];
        const Json::ArrayIndex m = outputs.size();
        for (Json::ArrayIndex j=0; j<m; ++j) {
          Json::Value output = outputs[j];
          if (!output.isMember("Field")) {
            comm->error("Field not specified in Output block.");
          }
          SliceData::Output out;
          out.Field = output["Field"].asString();
          if (output.isMember("File"))
            out.File = output["File" ].asString();
          else
            out.File = out.Field;
          if (output.isMember("Default"))
            out.Default = output["Default"].asDouble();
          data.Outputs.push_back(out);
        }
      }
      if (params.isMember("Cache Interpolation Data")) {
        data.CacheInterpolationData =
           params["Cache Interpolation Data"].asBool();
      }
      if (params.isMember("Origin")) {
        const Json::Value origin = params["Origin"];
        const Json::ArrayIndex m = origin.size();
        if (0<m) data.Origin.x = origin[0].asDouble();
        if (1<m) data.Origin.y = origin[1].asDouble();
        if (2<m) data.Origin.z = origin[2].asDouble();
      }
      if (0<nsd) params["Origin"][0] = data.Origin.x;
      if (1<nsd) params["Origin"][1] = data.Origin.y;
      if (2<nsd) params["Origin"][2] = data.Origin.z;
      if (params.isMember("Lattice")) {
        const Json::Value lattice  = params["Lattice"];
        const Json::ArrayIndex m = lattice.size();
        const Json::ArrayIndex sd = static_cast<Json::ArrayIndex>(nsd);
        for (Json::ArrayIndex j=0; j<m && j<sd; ++j) {
          const Json::Value row  = lattice[j];
          const Json::ArrayIndex n = row.size();
          for (Json::ArrayIndex i=0; i<n && i<sd; ++i) {
            const double x = row[i].asDouble();
            data.Lattice[j][i] = x;
          }
        }
      }
      if (params.isMember("Frequency")) {
        data.Frequency = params["Frequency"].asInt();
      }
      if (params.isMember("Intervals")) {
        const Json::Value intervals = params["Intervals"];
        const Json::ArrayIndex m = intervals.size();
        for (Json::ArrayIndex j=0; j<m; ++j) {
          const int interval = intervals[j].asUInt();
          data.Intervals.insert(interval);
        }
      }
      if (params.isMember("Verbosity")) {
        data.Verbosity = params["Verbosity"].asInt();
      }
      if (params.isMember("Dimensions")) {
        const Json::Value dimensions = params["Dimensions"];
        const Json::ArrayIndex m = dimensions.size();
        for (Json::ArrayIndex j=0; j<m && j<Json::ArrayIndex(nsd); ++j) {
          data.Dimensions[j] = dimensions[j].asUInt();
        }
      }
      if (params.isMember("Format")) {
        const string format = params["Format"].asString();
        const case_insensitive_string Float ="float";
        const case_insensitive_string Double="double";
        if      (format==Float)  data.Format = SliceData::FLOAT;
        else if (format==Double) data.Format = SliceData::DOUBLE;
        else comm->error("Format must be float or double.");
      }
      if (data.CacheInterpolationData && SliceData::DOUBLE == data.Format)
        comm->cout()<<"FieldSlice WARNING: Using "
           "'Cache Interpolation Data' "
           "forces interpolation to be done using 'float' precision. "
           "Writing the result in 'double' precision results in a "
           "loss of precision."<<endl;
      // Fill in missing default values
      bool need_box = false;
      for (Ordinal i=0; i<nsd; ++i) {
        if (data.Origin[i] == data.SCALAR_DEF ||
            data.Dimensions[i] == data.ORDINAL_DEF) need_box=true;
      }

      // Some of the default values depends on the extent of
      // the mesh.  If that is the case, call box() on the field
      // to compute the bounding box of the mesh.
      if (need_box) {
        BoundingBox box = F->box();
        Point ll = lower_left(box);
        Point ur = upper_right(box);
        if (0<nsd && data.Origin[0] == data.SCALAR_DEF)
            data.Origin.x = ll.x;
        if (1<nsd && data.Origin[1] == data.SCALAR_DEF)
            data.Origin.y = ll.y;
        if (2<nsd && data.Origin[2] == data.SCALAR_DEF)
            data.Origin.z = ll.z;
        if (nsd<3) data.Origin.z = 0;
        if (nsd<2) data.Origin.y = 0;
        if (nsd<1) data.Origin.x = 0;
        for (Ordinal i=0; i<nsd; ++i) {
          if (data.Dimensions[i] == data.ORDINAL_DEF) {
            const Scalar norm = data.Lattice.row(i).Norm();
            if (norm) {
              // Be a little sloppy with the bounding box calculation so that
              // points on the very edge of the mesh are included.
              data.Dimensions[i] = numeric_cast<Ordinal>
                (lround(.5 + (ur[i]-data.Origin[i])/norm));
            } else {
              data.Dimensions[i] = 1;
            }
          }
        }
      }
      slice_data.push_back(data);
    }
  }

  // Now the slice_data vector has been stuffed with all of the Json
  // parameters and all of the default values for missing parameters. Now
  // stuff all of the data from slice_data BACK into the Json structure,
  // overwriting ALL of the original parameters. This will then be echoed to
  // the output also.
  //
  // A change in the Json specification will cause a change in this block of
  // code so that the names and such remain valid.
  void echo_data_back_as_json(const vector<SliceData> &slice_data,
                              const Ordinal nsd,
                              const DGM::Comm::Ptr comm)
  {
    Json::Value slice_params = Json::Value();
    slice_params["Field Slice"] = Json::Value(Json::arrayValue);
    slice_params["Field Slice"].resize(numeric_cast<Json::ArrayIndex>
                                       (slice_data.size()));
    Ordinal max_Verbosity = 0;
    for (size_t d=0; d<slice_data.size(); ++d) {
      const SliceData data = slice_data[d];
      const Json::ArrayIndex m = numeric_cast<Json::ArrayIndex>(d);
      {
        slice_params["Field Slice"][m]["Outputs"] =
                   Json::Value(Json::arrayValue);
        const std::vector<SliceData::Output> outputs = data.Outputs;
        slice_params["Field Slice"][m]["Outputs"].
          resize(numeric_cast<Json::ArrayIndex>(outputs.size()));
        for (size_t o=0; o<outputs.size(); ++o) {
          const SliceData::Output output = outputs[o];
          const Json::ArrayIndex n = numeric_cast<Json::ArrayIndex>(o);
          slice_params["Field Slice"][m]["Outputs"][n]["Field"] =
                                                          output.Field;
          slice_params["Field Slice"][m]["Outputs"][n]["File"] =
                                                          output.File;
          slice_params["Field Slice"][m]["Outputs"][n]["Default"] =
                                                          output.Default;
          if (data.Verbosity)
            comm->cout()<<"Slice: "<<output.Field
                        <<" (n1="  <<data.Dimensions[0]
                        <<" n2="   <<data.Dimensions[1]
                        <<")"      <<endl;
        }
      }
      slice_params["Field Slice"][m]["Cache Interpolation Data"]
        = data.CacheInterpolationData;
      slice_params["Field Slice"][m]["Frequency"] = data.Frequency;
      {
        Json::Value V(Json::arrayValue);
        V.resize(numeric_cast<Json::ArrayIndex>(data.Intervals.size()));
        Ordinal j=0;
        for (set<int>::const_iterator i=data.Intervals.begin();
             i!=data.Intervals.end(); ++i,++j) V[Json::ArrayIndex(j)]=*i;
        slice_params["Field Slice"][m]["Intervals"] = V;
      }
      slice_params["Field Slice"][m]["Verbosity"] = data.Verbosity;
      if (max_Verbosity < data.Verbosity) max_Verbosity = data.Verbosity;
      {
        Json::Value V(Json::arrayValue);
        V.resize(numeric_cast<Json::ArrayIndex>(nsd));
        if (0<nsd) V[Json::ArrayIndex(0)]=data.Origin.x;
        if (1<nsd) V[Json::ArrayIndex(1)]=data.Origin.y;
        if (2<nsd) V[Json::ArrayIndex(2)]=data.Origin.z;
        slice_params["Field Slice"][m]["Origin"] = V;
      }
      {
        Json::Value V(Json::arrayValue);
        V.resize(numeric_cast<Json::ArrayIndex>(nsd));
        for (Ordinal i=0; i<nsd; ++i) {
          const Json::ArrayIndex n = numeric_cast<Json::ArrayIndex>(i);
          V[n]=Json::Value(Json::arrayValue);
          V[n].resize(numeric_cast<Json::ArrayIndex>(nsd));
          for (Ordinal j=0; j<nsd && i<nsd; ++j) {
            const Json::ArrayIndex m = numeric_cast<Json::ArrayIndex>(j);
            V[n][m] = data.Lattice[i][j];
          }
        }
        slice_params["Field Slice"][m]["Lattice"] = V;
      }
      {
        Json::Value V(Json::arrayValue);
        V.resize(numeric_cast<Json::ArrayIndex>(nsd));
        if (0<nsd) V[Json::ArrayIndex(0)]=data.Dimensions[0];
        if (1<nsd) V[Json::ArrayIndex(1)]=data.Dimensions[1];
        if (2<nsd) V[Json::ArrayIndex(2)]=data.Dimensions[2];
        slice_params["Field Slice"][m]["Dimensions"] = V;
      }
      if (SliceData::FLOAT == data.Format)
        slice_params["Field Slice"][m]["Format"] = "FLOAT";
      else
        slice_params["Field Slice"][m]["Format"] = "DOUBLE";
    }
    if (comm->verbosity()>1 || max_Verbosity>1) {
      Json::StyledWriter writer;
      const std::string echo_params = writer.write(slice_params);
      comm->cout()<<"Slice setup after default insertion:\n"
           <<echo_params;
    }
  }

  // Parse up the input file.
  // The root of the Json file is taken from the Field class. This might have
  // to be changed in the future if the field to be sliced does not have it's
  // own mesh file.  The file name extension is fixed to ".json".
  vector<SliceData> parse_json_file(Ordinal &max_verbosity,
                                    const Field *F,
                                    const string &name,
                                    const DGM::Comm::Ptr comm)
  {
    vector<SliceData> slice_data;

    const Ordinal nsd = F->nsd();
    Json::Value slice_params;

#ifndef DGM_FIELDSLICE_USE_JSON_BROADCAST
    // Read on all processors until Json::broadcast can be fixed to
    // compile without warnings
    const string fname = F->root + ".json";
    ifstream file(fname.c_str());
    if (file) {
      Json::Reader reader;
      Json::Value value;
      reader.parse(file, value, true);
      slice_params = value[name];
    }
#else
    if (comm->Master()) {
      const string fname = F->root + ".json";
      ifstream file(fname.c_str());
      if (file) {
        Json::Reader reader;
        Json::Value value;
        reader.parse(file, value, true);
        slice_params = value[name];
      }
    }
    Json::broadcast(comm,slice_params);
#endif

    if (slice_params.size())
      parse_into_slice_data_struct(slice_data, F, slice_params, nsd, comm);

    for (size_t d=0; d<slice_data.size(); ++d) {
      const SliceData data = slice_data[d];
      max_verbosity = max(max_verbosity, data.Verbosity);
    }
    if (2<max_verbosity) {
      Json::StyledWriter writer;
      Json::Value root;
      root[name] = slice_params;
      const std::string echo_params = writer.write(root);
      comm->cout()<<"Slice as read from file:\n"<<echo_params;
    }
    if (!slice_data.empty()) echo_data_back_as_json(slice_data, nsd, comm);
    return slice_data;
  }


// Evaluate the field data at the lattice points on this processor.  The input
// vector to be filled, buf, should be exactly the correct size to store all
// of the interpolated lattice points.
template <typename DATATYPE>
void interpolate_to_lattice(vector<DATATYPE> &buf,
                            const Field      *F,
                            const map<Size,vector<Point> > &elem_to_lattice) {
  dVector vals;
  size_t k=0;
  for (map<Size,vector<Point> >::const_iterator
        e=elem_to_lattice.begin(); e!=elem_to_lattice.end(); ++e) {
    const Size i = e->first;
    const vector<Point>& ps = e->second;
    // A single call to interpolate to all points in this element.
    // Note that interpolate_points sizes vals as needed.
    F->el[i]->interpolate_points(ps, vals);
    for (Ordinal j=0; j<vals.size(); ++j) 
      buf[k++] = numeric_cast<DATATYPE>(vals[j]);
    if (buf.size() < k)
      F->get_comm()->error(" Buffer short in interpolate_to_lattice");
  }
}

void calculate_interpolation_matrices(
  map<Size,vector<fMatrix> >     &elem_to_matrix,
  const Field                    *F,
  const map<Size,vector<Point> > &elem_to_lattice) {
  for (map<Size,vector<Point> >::const_iterator
       e=elem_to_lattice.begin(); e!=elem_to_lattice.end(); ++e) {
    const Size i = e->first;
    const vector<Point>& ps = e->second;
    elem_to_matrix[i] = vector<fMatrix>();
    F->el[i]->calculate_interpolation_matrices(elem_to_matrix[i],ps);
  }
}

template <typename DATATYPE>
void apply_interpolation_matrices(
  vector<DATATYPE> &buf,
  const Field      *F,
  const map<Size,vector<fMatrix> > &elem_to_matrix){
  dVector vals;
  size_t k=0;
  for (map<Size,vector<fMatrix> >::const_iterator
       e=elem_to_matrix.begin(); e!=elem_to_matrix.end(); ++e) {
    const Size i = e->first;
    const vector<fMatrix>& M = e->second;
    // A single call to interpolate to all points in this element.
    // Note that interpolate_points sizes vals as needed.
    F->el[i]->apply_interpolation_matrices(vals, M);
    for (Ordinal j=0; j<vals.size(); ++j) 
      buf[k++] = numeric_cast<DATATYPE>(vals[j]);
    if (buf.size() < k)
      F->get_comm()->error(" Buffer short in apply_interpolation_matrices");
  }
}

// Sort the evaluated lattice points into the communication buffer in global
// id order.  This is needed to then send each continuous part of the vector
// to the correct processor since the evaluation buffer has lattice points in
// the order they are found in elements and the lattice points in a single
// element might have to be sent to multiple processors.  The evaluation
// buffer, buf, and the communication buffer, send_buf, should be the same
// size.  send_index has been set up already as the mapping between the two
// and it is an invarient that send_buf is a 1-1 and onto mapping between
// these two buffers.
template <typename DATATYPE>
void scatter_to_send_buf(vector<DATATYPE>       &send_buf,
                         const vector<DATATYPE> &buf,
                         const vector<Size>     &send_index,
                         const Comm::Ptr         comm) {
  if (send_buf.size() != buf.size())
    comm->error(" Buffer size mismatch in scatter_to_send_buf. ");
  if (send_buf.size() != send_index.size())
    comm->error(" Buffer size mismatch in scatter_to_send_buf..");
  for (size_t i=0; i<send_buf.size(); ++i) send_buf[send_index[i]] = buf[i];
}

// Fill the write buffer with the default before filling
// with the data received from the other processors. This
// takes care of the fact that there might be lattice points
// outside the mesh that do not get set to anything otherwise.
template <typename DATATYPE>
void initialize_write_buf(vector<DATATYPE>  &buf,
                          const DATATYPE       x) {
  for (size_t i=0; i<buf.size(); ++i) buf[i] = x;
}

// Sort the data received from the other processors into sequential
// order based on global id into the write buffer.  Then the write
// buffer can be written to disk on one big continuous vector of
// data.
template <typename DATATYPE>
void scatter_to_write_buf(vector<DATATYPE>      &write_buf,
                         const vector<DATATYPE> &buf,
                         const vector<Size>     &write_index,
                         const Comm::Ptr         comm) {
  if (buf.size() != write_index.size())
    comm->error(" Buffer size mismatch in scatter_to_write_buf. ");
  for (size_t i=0; i<buf.size(); ++i) write_buf[write_index[i]] = buf[i];
}

#ifdef DGM_PARALLEL
template<typename TYPE>
MPI_Datatype mpi_size_type() {
  const MPI_Datatype type =sizeof(TYPE)==sizeof(float) ? MPI_FLOAT : MPI_DOUBLE;
  return type;
}
#endif

// Write the data to the file.  The data has been sorted based on
// the order defined in the GeneralPartition class.  Mainly that processor
// 0 gets the first continuous chunck of data followed by processor 1
// and so on.  Also each processor writes about the same amount of
// data.  So setting up the write displacements for all the processors
// is pretty easy.
template<typename DATATYPE>
void write_to_file (vector<DATATYPE> &write_buf,
                    const size_t    disp,
                    const string   &name,
                    const Comm::Ptr comm) {
  size_t count = write_buf.size();
#ifdef DGM_PARALLEL
  const MPI_Datatype size_type = mpi_size_type<DATATYPE>();
  MPI_File fh;
  MPI_Info info;
  MPI_Info_create(&info);
  MPI_Status status;
  const char *cnative="native";
  char *native = const_cast<char*>(cnative);
  int stat =
     MPI_File_open(dynamic_cast<const DGM::MpiComm*>(comm.get())->mpi_comm,
                   const_cast<char*>(name.c_str()),
                   MPI_MODE_WRONLY | MPI_MODE_CREATE, info, &fh);
  if (stat) {
    char err[MPI_MAX_ERROR_STRING];
    int len;
    MPI_Error_string(stat, err, &len);
    string error="FieldSlice can not create file. "
      " MPI_File_open error:"+string(err, len)+" Filename:"+name;
    comm->error(error, stat);
  }
  //MPI_File_set_size(fh, MPI_Offset(0));
  const MPI_Offset file_disp = disp;
  const MPI_Offset byte_disp = file_disp * sizeof(DATATYPE);
  stat = MPI_File_set_view(fh, byte_disp, size_type, size_type, native, info);
  if (stat) comm->error("MPI_File_set_view", stat  );
  MPI_File_write_all(fh, &(write_buf.front()), count, size_type, &status);
  MPI_File_close(&fh);
  MPI_Info_free(&info);
#else
  ofstream fs(name.c_str(), ofstream::binary|ios::out|ios::trunc);
  const streampos file_disp = disp;
  fs.seekp(file_disp*sizeof(DATATYPE));
  fs.write(reinterpret_cast<const char*>(&write_buf.front()),
           count*sizeof(DATATYPE));
#endif
}

}  // anonymous namespace

namespace DGM {

  // The FSlice class contains all of the information needed
  // to evaluate the lattice points on this processor, communicate
  // the result to the other processors for writing and then
  // actually writing the data.  As such it contains a bunch of
  // evaluation, communication and write buffers along with
  // various offset buffers.
  class FieldSlice::FSlice {
  public:
    FSlice(const Field *F, const SliceData &data);
    ~FSlice(){};

    const SliceData Data;
    void setup_communication_buffers(
      const map<Size,vector<Size> >  &elem_to_GID,
      const DGM::Comm::Ptr            comm);


    // Map of all the lattice points in each element.
    map<Size,vector<Point> >  elem_to_lattice;
    map<Size,vector<fMatrix> > elem_to_matrix;

    // After all the lattice points are evaluated, need to
    // reorder them from elem_to_lattice ordering to the
    // send_buf communication ordering.  send_index is
    // this mapping. It should be the same size as send_buf.
    vector<Size> send_index;

    // How many evaluated lattice points to send to each processor.
    // Length number of processors.
    vector<int> send_count;

    // Displacements for the MPI_AllToAllV call, a scan of send_count.
    // Length number of processors.
    vector<int> send_disp;

    // How many evaluated lattice points to receive from each processor.
    // Length number of processors.
    vector<int> recv_count;

    // Displacements for the MPI_AllToAllV call, a scan of recv_count.
    // Length number of processors.
    vector<int> recv_disp;

    // Once data is received into recv_buf, it must be scattered into
    // the write_buf in the proper order in order to write the data
    // in global id order.  write_index is the mapping from the recv_buf
    // into the write_buf. It should be the length of recv_buf.
    vector<Size>    write_index;

    // Each processor needs to know where to write it's data into
    // the global file.
    size_t          write_disp;
    Size            write_buf;

    Size send_buf_size() const {
      Size n = 0;
      for (size_t i=0; i<send_count.size(); ++i) n += send_count[i];
      return n;
    }
    Size recv_buf_size() const {
      Size n = 0;
      for (size_t i=0; i<recv_count.size(); ++i) n += recv_count[i];
      return n;
    }
    Size write_buf_size() const {return write_buf;}
    // Unimplemented functions
    FSlice();
    FSlice(const FieldSlice::FSlice&);
    FSlice operator=(const FieldSlice::FSlice &);
  };


  // Initialize parses up the Json file and creates
  // the SliceData that has all of the lattice evaluation
  // and processor communication needed in it.
  // OK to call multiple times, will just return on second
  // and subsequent calls.
  void FieldSlice::initialize(const Field *F) {
    if (Initialized) return;
    Initialized = true;
    const Comm::Ptr comm = F->get_comm();
    const vector<SliceData> data=parse_json_file(MaxVerbosity, F, Name, comm);
    if (data.empty()) return;
    for (vector<SliceData>::const_iterator
            i=data.begin();
            i!=data.end();++i){
      Slices.push_back(Ptr(new FSlice(F, *i)));
    }
  }

  namespace {
  void output_slices_timer(const bool start=true) {
    static FunctionTimer T("FieldSlice:output_slices");
    if (start) T.start();
    else       T.stop();
  }
  }
  // Called to evaluate the vField at all of the lattice points and
  // write a binary file of the result.  Will loop over all the
  // fields in vF to see if the names match any in the Json setup
  // file.
  // NOTE:  output_slices should be called with a vField based on
  //        the field passed to initialize.  Since all fields in
  //        DGM look alike and are usually based on a single master
  //        field this should be acceptable.
  void FieldSlice::first_output_check(const vField &vF) const {
    if (FirstOutputCheck) {
      const Comm::Ptr comm = vF[0]->get_comm();
      for (vector<Ptr>::const_iterator i=Slices.begin(); i!=Slices.end();++i){
        const FSlice &S = **i;
        for (std::vector<SliceData::Output>::const_iterator
             j =S.Data.Outputs.begin();
             j!=S.Data.Outputs.end(); ++j) {
          const case_insensitive_string n = j->Field.c_str();
          bool found = false;
          for (vField::size_type f=0; f<vF.size() && !found; f++) {
            const string &m = vF[f]->get_name();
            if (m.size() == j->Field.size() && m == n) found = true;
          }
          if (!found) {
            comm->cout()<<"FieldSlice WARNING: output "
               <<"field name not found in VectorField to output."<<endl
               <<"Was supposed to do a FieldSlice on variable '"<<j->Field
               <<"' but only found fields named ";
            for (vField::size_type f=0; f<vF.size(); f++)
               comm->cout()<<"'"<<vF[f]->get_name()<<"'  ";
            comm->cout()<<endl;
          }
        }
      }
    }
  }
  template <typename DATATYPE>
  void FieldSlice::output_slices(FSlice &S,
                                 const Field *F,
                                 const Ordinal step,
                                 const bool TimeStepInFileName,
                                 const string &ext) {
    const Comm::Ptr comm = F->get_comm();
    // Buffer to communicate evaluated lattice points to
    // the write processor. Length is the sum of all the
    // vectors in the elem_to_lattice map above.
    vector<DATATYPE> send_buf(S.send_buf_size());
    // Receive buffer for the other side of the send_buf.
    vector<DATATYPE> recv_buf(S.recv_buf_size());

    for (std::vector<SliceData::Output>::const_iterator
         j =S.Data.Outputs.begin();
         j!=S.Data.Outputs.end(); ++j) {
      const case_insensitive_string n = j->Field.c_str();
      if ( F->get_name() == n) {
        if (3<S.Data.Verbosity) output_slices_timer();
        {
          vector<DATATYPE> buf(send_buf.size());;
          if (S.Data.CacheInterpolationData)
            apply_interpolation_matrices(buf, F, S.elem_to_matrix);
          else
            interpolate_to_lattice(buf, F, S.elem_to_lattice);
          scatter_to_send_buf(send_buf, buf, S.send_index, comm);
        }
        comm->Alltoallv(&send_buf[0],&S.send_count[0],&S.send_disp[0],
                        &recv_buf[0],&S.recv_count[0],&S.recv_disp[0]);
        {
          // Write buffer. This is at least as long as recv_buf since
          // recv_buf has to be stuffed into it for writing.  But since
          // there might be lattice values outside the mesh that never
          // get evaluated, write_buf could be longer than recv_buf.
          vector<DATATYPE>  write_buf(S.write_buf_size());
          const DATATYPE def = j->Default;
          initialize_write_buf(write_buf, def);
          scatter_to_write_buf(write_buf,recv_buf,S.write_index,comm);
          const string &name = TimeStepInFileName ?
            j->File+"."+asString(step)+ext+".bin" : j->File+ext+".bin" ;
          if (0<S.Data.Verbosity) 
            comm->cout()<<" FieldSlice::output_slices: output file, "
                     <<name<<std::endl;
          write_to_file(write_buf,S.write_disp,name,comm);
        }
        if (3<S.Data.Verbosity) output_slices_timer(false);
      }
    }
  }

  void FieldSlice::output_slices(const vField &vF,
                                 const Ordinal step,
                                 const bool alwaysOutput,
                                 const bool TimeStepInFileName,
                                 const string &ext) {

    // This maybe should be an error.
    if (!vF.size()) return;

    // initialize can be called multiple times since it
    // has a quick return check.
    initialize(vF[0]);

    // Quick return if nothing to do.
    if (Slices.empty()) return;

    const Comm::Ptr comm = vF[0]->get_comm();

    first_output_check(vF);
    FirstOutputCheck = false;

    for (vField::size_type f=0; f<vF.size(); f++) {
      const Field *F = vF[f];
      for (vector<Ptr>::const_iterator
           i=Slices.begin();
           i!=Slices.end();++i){
        FSlice &S = **i;
        if (step%S.Data.Frequency==0 ||
            S.Data.Intervals.count(numeric_cast<int>(step)) ||
            alwaysOutput) {
          if (SliceData::DOUBLE ==  S.Data.Format) {
            output_slices<Scalar>(S, F, step, TimeStepInFileName, ext);
          } else {
            output_slices<float> (S, F, step, TimeStepInFileName, ext);
          }
        }
      }
    }
  }
} // namespace DGM

namespace {

// Utility to invert a 2x2 or 3x3 matrix. Maybe better to
// call a Lapack routine instead.
dMatrix invert(const dMatrix lattice, const DGM::Comm::Ptr comm) {
  const dMatrix &L=lattice;
  dMatrix inv;
  inv.resize(L);
  if        (1 == inv.size()) {
    inv[0][0] = 1/L[0][0];
  } else if (4 == inv.size()) {
    const double det = L[0][0]*L[1][1]-L[0][1]*L[1][0];
    if (!det) comm->error("Lattice matrix has zero determinant");
    inv[0][0] =  L[1][1]/det;
    inv[1][1] =  L[0][0]/det;
    inv[1][0] = -L[1][0]/det;
    inv[0][1] = -L[0][1]/det;
  } else if (9==inv.size()) {
    const double det =   L[0][0]*(L[2][2]*L[1][1]-L[2][1]*L[1][2]) -
                         L[1][0]*(L[2][2]*L[0][1]-L[2][1]*L[0][2]) +
                         L[2][0]*(L[1][2]*L[0][1]-L[1][1]*L[0][2]) ;
    if (!det) comm->error("Lattice matrix has zero determinant");
    inv[0][0] =  (L[2][2]*L[1][1] - L[2][1]*L[1][2])/det ;
    inv[0][1] = -(L[2][2]*L[0][1] - L[2][1]*L[0][2])/det ;
    inv[0][2] =  (L[1][2]*L[0][1] - L[1][1]*L[0][2])/det ;
    inv[1][0] = -(L[2][2]*L[1][0] - L[2][0]*L[1][2])/det ;
    inv[1][1] =  (L[2][2]*L[0][0] - L[2][0]*L[0][2])/det ;
    inv[1][2] = -(L[1][2]*L[0][0] - L[1][0]*L[0][2])/det ;
    inv[2][0] =  (L[2][1]*L[1][0] - L[2][0]*L[1][1])/det ;
    inv[2][1] = -(L[2][1]*L[0][0] - L[2][0]*L[0][1])/det ;
    inv[2][2] =  (L[1][1]*L[0][0] - L[1][0]*L[0][1])/det ;
  } else comm->error("Invalid spatial dimension in invert");
  return inv;
}

// Lattice triple to linear map. This takes an i,j,k integer lattice
// node to a GID. This defines how the mesh will be written to the
// data file.  As can be seen it is i the fastest changing followed
// by j and k.  This is Fortran ordering, not C.
Size GID(const Ordinal *V, const vector<Ordinal> &D) {
  Size gid=0;
  const Ordinal nsd = numeric_cast<Ordinal>(D.size());
  if (0<nsd) gid  = V[0];
  if (1<nsd) gid += V[1]*D[0];
  if (2<nsd) gid += V[2]*D[0]*D[1];
  return gid;
}
  
vector<Size> lattice_index(Size gid, const std::vector<Ordinal> &D) {
  const Ordinal nsd = numeric_cast<Ordinal>(D.size());
  vector<Size> p(nsd,0);
  if (2<nsd) {
    p[2] = gid/D[0]/D[1];
    gid -= p[2]*D[0]*D[1];
  }
  if (1<nsd) {
    p[1] = gid/D[0];
    gid -= p[1]*D[0];
  }
  if (0<nsd) p[0] = gid;
  return p;
}

void find_lattice_points_in_elements_timer(const bool start=true) {
  static FunctionTimer T("FieldSlice:find_lattice_points_in_elements");
  if (start) T.start();
  else       T.stop();
}

// This is the big search function.  The Algorithm:
//    1. Find an axis aligned box around the element.
//    2. Given the corners of the box, C,
//             the Lattice Matrix, L,
//             the origin vector, O solve
//                  O + KL = C
//       for K.  This is just the tranformation from
//       a standard orthogonal basis to the lattice basis.
//    3. Convert the K vector from step 2 to integers.
//    4. Limit the K vector from step 3 by the input Dimensions.
//    5. All the integers in K are the lattice nodes
//       that are in the box from 1.
//    6. Multiply the inteeger vectors from 4 by the lattice
//       matrix L and add back the Origin vector to get the
//       real lattice points in the box from 1.
//    7. Test each real vector from 5 to see if is actaully in the
//       element.  Discard the ones outside the actual element.
// Note: Some points might be on element boundaries.  In that case
//       just evaluate once in one of the elements and ignore the
//       other results.
void find_lattice_points_in_elements(map<Size,vector<Point> > &elem_to_lattice,
                                     map<Size,vector<Size> > &elem_to_GID,
                                     const Field *F,
                                     const Point &origin,
                                     const dMatrix &lattice,
                                     const vector<Ordinal> &dimensions,
                                     const Ordinal verbosity) {
  if (3<verbosity) find_lattice_points_in_elements_timer();

  const DGM::Comm::Ptr comm = F->get_comm();
  const Ordinal nsd = F->nsd();
  const dMatrix Inv(invert(lattice, comm));
  Ordinal         L[3] = {0};  // length fixed at maximum nsd
  Ordinal         U[3] = {0};  // length fixed at maximum nsd
  Ordinal         V[3] = {0};  // length fixed at maximum nsd
  dVector         O(nsd);
  dVector        Vt(nsd);
  dVector        Pt(nsd);
  dMatrix       C(2,nsd);
  dMatrix      TC(2,nsd);
  vector<Point> Pts;
  vector<Size>  Gids;
  set<Size> duplicates;
  const double EPSILON = .00001;

  if (0<nsd) O[0] = origin.x;
  if (1<nsd) O[1] = origin.y;
  if (2<nsd) O[2] = origin.z;
  for (Ordinal e=0; e<F->ne; ++e) {
    // Step 1
    const vector<float> box = F->box(e);
    for (Ordinal i=0; i<nsd; ++i) {
      C[0][i] = box[i  ];
      C[1][i] = box[i+3];
    }

    // Step 2
    C.row(0) -= O;
    C.row(1) -= O;
    matmult(C,Inv,TC);
    TC += .5;
    // Step 3.  Be a little sloppy when converting to integers in
    // order to not miss any points close to an integer.
    Size num_lattice_pt=1;
    for (Ordinal i=0; i<nsd; ++i) {
      // Step 4. Limit lower to 0 and upper to dimensions
      L[i] = numeric_cast<Ordinal>(lround(max(0.,TC[0][i] - EPSILON)));
      U[i] = numeric_cast<Ordinal>(lround(max(0.,TC[1][i] + EPSILON)));
      U[i] = min(U[i],dimensions[i]);
      if (L[i] <= U[i]) num_lattice_pt *= U[i]-L[i];
      else              num_lattice_pt  = 0;
    }

    Pts.clear();
    Gids.clear();
    if (num_lattice_pt) {
      if (2<nsd) {

        // Nested loops are Step 5
        for (V[0]=L[0]; V[0]<U[0]; ++V[0]) {
          for (V[1]=L[1]; V[1]<U[1]; ++V[1]) {
            for (V[2]=L[2]; V[2]<U[2]; ++V[2]) {
              const Size gid = GID(V,dimensions);

              // Check for duplicates.  See Note: above.
              if (!duplicates.count(gid)) {
                Vt[0]=V[0];
                Vt[1]=V[1];
                Vt[2]=V[2];

                // Step 6
                tmvmult(lattice,Vt,Pt);
                Pt += O;
                const Point P(Pt[0], Pt[1], Pt[2]);

                // Step 7
                if (F->is_in_element(P,e)) {
                  const Point Q = F->el[e]->get_local_coordinates(P);
                  Pts. push_back(Q);
                  Gids.push_back(gid);
                  duplicates.insert(gid);
                }
              }
            }
          }
        }
      } else if (1<nsd) {

        // Nested loops are Step 4
        for (V[0]=L[0]; V[0]<U[0]; ++V[0]) {
          for (V[1]=L[1]; V[1]<U[1]; ++V[1]) {
            const Size gid = GID(V,dimensions);

            // Check for duplicates.  See Note: above.
            if (!duplicates.count(gid)) {
              Vt[0]=V[0];
              Vt[1]=V[1];

              // Step 6
              tmvmult(lattice,Vt,Pt);
              Pt += O;
              const Point P(Pt[0], Pt[1]);

              // Step 7
              if (F->is_in_element(P,e)) {
                const Point Q = F->el[e]->get_local_coordinates(P);
                Pts.push_back(Q);
                Gids.push_back(gid);
                duplicates.insert(gid);
              }
            }
          }
        }
      } else if (0<nsd) {

        // Nested loops are Step 4
        for (V[0]=L[0]; V[0]<U[0]; ++V[0]) {
          const Size gid = GID(V,dimensions);

          // Check for duplicates.  See Note: above.
          if (!duplicates.count(gid)) {
            Vt[0]=V[0];

            // Step 6
            tmvmult(lattice,Vt,Pt);
            Pt += O;
            const Point P(Pt[0]);

            // Step 7
            if (F->is_in_element(P,e)) {
              const Point Q = F->el[e]->get_local_coordinates(P);
              Pts.push_back(Q);
              Gids.push_back(gid);
              duplicates.insert(gid);
            }
          }
        }
      } else comm->error("invalid spacial dimension");
    }
    if (!Pts.empty()) {
      elem_to_lattice[e] = Pts;
      elem_to_GID[e]     = Gids;
    }
  }
  if (3<verbosity) find_lattice_points_in_elements_timer(false);
}


}  // anonymous namespace

FieldSlice::FSlice::FSlice(const Field *F, const SliceData &data)
  : Data(data),
    elem_to_lattice(),
    elem_to_matrix(),
    send_index(),
    send_count(),
    send_disp(),
    recv_count(),
    recv_disp(),
    write_index(),
    write_disp(0)
 {
  const DGM::Comm::Ptr comm = F->get_comm();
  const Point               origin(Data.Origin);
  const dMatrix           lattice (data.Lattice);
  const vector<Ordinal> dimensions(data.Dimensions);
  const Ordinal          verbosity(data.Verbosity);
  map<Size,vector<Size> > elem_to_GID;
  find_lattice_points_in_elements(elem_to_lattice, elem_to_GID, F,
                                  origin, lattice, dimensions, verbosity);

  setup_communication_buffers(elem_to_GID, comm);
  if (Data.CacheInterpolationData) {
    calculate_interpolation_matrices(elem_to_matrix, F, elem_to_lattice);
  }
}

// Somewhat complicated function to determine the
// sizes of all of the communication and write
// buffers.  Tricky because this is an all-to-all
// communication pattern.
namespace {
  void setup_communication_buffers_timer(const bool start=true) {
    static FunctionTimer T("FieldSlice:setup_communication_buffers");
    if (start) T.start();
    else       T.stop();
  }
}

void FieldSlice::FSlice::setup_communication_buffers
(const map<Size,vector<Size> >  &elem_to_GID,
 const DGM::Comm::Ptr            comm) {

  if (3<Data.Verbosity) setup_communication_buffers_timer();

  const vector<Ordinal> dimensions(Data.Dimensions);
  const Ordinal nsd = numeric_cast<Ordinal>(dimensions.size());
  const Ordinal np = comm->NumProc();

  size_t gne=1;
  for (Ordinal i=0; i<nsd; ++i) gne *= dimensions[i];
  DefaultPartition<size_t,Ordinal> partition(comm, gne);

  // Collect all global IDs of all the lattice points to
  // compute on this processor into buffer send_gid.  Note
  // that by construction this list is unique.
  typedef pair<Size,Size> gid_ind;
  vector<gid_ind> gid_index;
  {
    Ordinal n = 0;
    for (map<Size,vector<Size> >::const_iterator i=elem_to_GID.begin();
          i!=elem_to_GID.end(); ++i) {
      const vector<Size> &gids = i->second;
      n += gids.size();
    }
    gid_index.resize(n);
    n = 0;
    for (map<Size,vector<Size> >::const_iterator i=elem_to_GID.begin();
          i!=elem_to_GID.end(); ++i) {
      const vector<Size> &gids = i->second;
      for (size_t j=0; j<gids.size(); ++j, ++n)
        gid_index[n] = gid_ind(gids[j],n);
    }
    sort(gid_index.begin(), gid_index.end());
  }

  // Set up the map from the element order in which the lattice elements
  // are computed into global ID order. This will groupd all of the
  // values by processor to communicate to so that all of the values
  // to communicate to each processor are grouped together.
  vector<Size> send_gid;
  {
    const Size n = numeric_cast<Size>(gid_index.size());
    send_index.resize(n);
    send_gid.resize(n);
    for (Size i=0; i<n; ++i) {
      send_index[gid_index[i].second] = i;
      send_gid[i] = gid_index[i].first;
    }
  }

  send_count.resize(np,0);
  recv_count.resize(np,0);
  for (vector<Size>::const_iterator i=send_gid.begin(); i!=send_gid.end();++i){
    ++send_count[partition.proc(*i)];
  }

  comm->Alltoall(&send_count[0], 1, &recv_count[0], 1);

  if (send_buf_size() != numeric_cast<Size>(send_gid.size()))
    comm->error("Error in buffer sizes in "
                "FieldSlice::FSlice::setup_communication_buffers");

  write_buf = numeric_cast<Size>(partition.end()-partition.begin());
  write_disp = numeric_cast<size_t>(partition.begin());

  send_disp.resize(np,0);
  recv_disp.resize(np,0);
  for (Ordinal i=0; i<np-1; ++i) {
    send_disp[i+1] = send_disp[i]+send_count[i];
    recv_disp[i+1] = recv_disp[i]+recv_count[i];
  }

  // Collect all global ids received from each processor into
  // one big vector called write_index.  In general write_index
  // should then contain all the global ids from partition.begin()
  // partition.end() which are all the values this processor
  // will be writing to the file.  But in some cases there are
  // lattice points ouside the mesh so there might be global ids
  // missing.
  write_index.resize(recv_buf_size());
  comm->Alltoallv(&send_gid[0], &send_count[0], &send_disp[0],
                  &write_index[0], &recv_count[0], &recv_disp[0]);

  for (size_t i=0; i<write_index.size(); ++i) {
    if (write_index[i] < numeric_cast<Size>(partition.begin()) ||
        numeric_cast<Size>(partition.end()) <= write_index[i])
      comm->error(" Received unexpted gid of lattice point");
  }

  if (5<Data.Verbosity) {
    vector<Size> sorted(write_index);
    sort(sorted.begin(), sorted.end());
#if 0
    // SSC debugging
    if (comm->Master()) {
      for (size_t i=0; i<sorted.size(); ++i) {
        cout << i << ": " << sorted[i] << endl;
      }
    }
#endif
    Size partialsum = 0, globalsum=0;
    for (size_t i=1; i<sorted.size(); ++i) {
      if (sorted[i] != sorted[i-1])  // SSC: added to get globalsum correct
        partialsum += (sorted[i] - sorted[i-1] - 1);
    }
    // cout<<comm->MyPID()<<": partialsum = "<<partialsum<<endl;
    comm->SumAll(&partialsum, &globalsum, 1);
    if (globalsum) {
      comm->cout()<<"FieldSlice::FSlice::setup_communication_buffers:\n"
                  <<" There are " << globalsum
                  <<" lattice points outside of mesh."<<endl;
      if (6<Data.Verbosity) {
        const Ordinal me = comm->MyPID();
        const Ordinal np = comm->NumProc();
        for (Ordinal p=0; p<np; ++p) {
          if (p==me) {
            cout <<" Outside lattice ids on processor "<<me<<":";
            for (size_t i=1; i<sorted.size(); ++i)  {
              for (Size j=sorted[i-1]+1; j < sorted[i]; ++j) {
                cout <<" "<<j;
                if (7<Data.Verbosity) {
                  vector<Size> l = lattice_index(j,dimensions);
                  cout <<"=(";
                  for (size_t k=0; k<l.size(); ++k)
                    cout <<l[k] <<(k+1==l.size()?")":",");
                  if (8<Data.Verbosity) {
                    dVector Vt(nsd);
                    dVector Pt(nsd);
                    if (0<nsd) Vt[0]=l[0];
                    if (1<nsd) Vt[1]=l[1];
                    if (2<nsd) Vt[2]=l[2];
                    tmvmult(Data.Lattice,Vt,Pt);
                    if (0<nsd) Pt[0] += Data.Origin.x;
                    if (1<nsd) Pt[1] += Data.Origin.y;
                    if (2<nsd) Pt[2] += Data.Origin.z;
                    cout <<"=(";
                    const Ordinal l_size = numeric_cast<Ordinal>(l.size());
                    for (Ordinal k=0; k<l_size; ++k) {
                      cout <<Pt[k] <<(k+1==l_size?")":",");
                    }
                  }
                }
              }
            }
            cout <<endl;
          }
          cout.flush();
          comm->Barrier();
        }
      }
    }
  }

  // Setting up the map from the receive buffer to the write buffer just means
  // subtracting the beginning global id from each of the global ids
  // received. The write_index should then have integers from 0 to the number
  // of global ids received.
  for (size_t i=0; i<write_index.size(); ++i)write_index[i]-=partition.begin();
  if (3<Data.Verbosity) setup_communication_buffers_timer(false);
}
