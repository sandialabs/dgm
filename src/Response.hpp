#ifndef DGM_RESPONSE_HPP
#define DGM_RESPONSE_HPP

/** \file Response.hpp
    \brief Response extracts information from a solution
    \author Scott Collis
    \author James Overfelt
    \author Curtis Ober
    \copyright (c)2014 Sandia National Laboratories
*/

// System includes
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <sstream>
using namespace std;

// boost includes
#include <boost/lexical_cast.hpp>

// DTK include
#include "DTK.hpp"

// DGM includes
#include "Comm.hpp"
#include "Kernel.hpp"
#include "Element.hpp"
#include "Field.hpp"
#include "vField.hpp"
#include "Types.hpp"
#include "Constants.hpp"
#include "BndryStats.hpp"

#ifdef DGM_PARALLEL
#include "MpiComm.hpp"
#endif

#ifdef DGM_USE_JSON
#include "json/json.h"
#endif

namespace DGM {

  // forward declarations
  class Domain;
  class TimeInt;

  /// Compute a response from the solution
  /** \section DGM_Response DGM Response
      The Response provides a versatile way to extract values of the solution
      using a generalized concept of a probe.  The Response outputs this
      information in a variety of different formats.  Likewise, the Response
      is also able to read the output of a prior Response format output and
      use that to construct a misfit between the current simulation and the
      prior output.

      Note that the prior output can be from a prior simulation or even
      external data from an experiment or external analysis as long as it
      is in a file format supported by the Response.

      The probe data can be either \c ASCII, \c DOUBLE, or \c FLOAT

      The probe file format can be:
      \verbatim
      SEPARATE   Each probe is in a separate file in the form:
                 time, component 0, component 1, ..., component N

      COMBINED   Each component is in a separate file with all probes:
                 time, probe 0, probe 1, ..., probe N
      \endverbatim
   */
  class Response {

    bool valid;                  ///< Is this Response object valid

  public:

    /// Output file format for probes
    enum ProbeFormat {
      ASCII,                 ///< Probe format is ASCII
      DOUBLE,                ///< Probe format is Binary, double precision
      FLOAT                  ///< Probe format is Binary, single precision
    };

    /// Output file format for probes
    enum ProbeFiles  {
      SEPARATE,              ///< Probes are in separate files
      COMBINED               ///< Probe data in one huge file
    };

    /// Probe Type
    enum ProbeType {
      DELTA,                 ///< Delta function
      GAUSSIAN,              ///< Gaussian ball with radius
      LINE,                  ///< Line integral
      SIDESET,               ///< SideSet defined by BndryStats
      GAUSSIANELLIPSE,       ///< Gaussian ellipse with three radii
      GAUSSIANLINESEGMENT    ///< Gaussian line segment
    };

    /// The way that a probe's storage is distributed across the ranks
    enum StorageType {
      WHERE_NEEDED,           ///< Probe data is only on ranks that need it
      PROC_WITH_CENTER,       ///< Probe data is on rank that owns center
      EVENLY_DISTRIBUTED      ///< Probe data is distributed on all ranks
    };

    /// Converts a string to a ProbeType enumeration
    ProbeType stringToProbeType(const string &type) const {
      ProbeType P = DELTA;
      const string n = lowerCase(type);
      if      (n == "delta"   )            P = DELTA;
      else if (n == "gaussian")            P = GAUSSIAN;
      else if (n == "line"    )            P = LINE;
      else if (n == "sideset" )            P = SIDESET;
      else if (n == "gaussianellipse")     P = GAUSSIANELLIPSE;
      else if (n == "gaussianlinesegment") P = GAUSSIANLINESEGMENT;
      else
        comm->error(_name+": String passed to Response::stringToProbeType() "
                    "is invalid: "+type);
      return P;
    }

    /// Converts and ProbeType enumeration to a string
    static string ProbeTypeToString(const ProbeType & P) {
      string name = "Delta";
      switch (P) {
        case DELTA              : name = "Delta";               break;
        case GAUSSIAN           : name = "Gaussian";            break;
        case LINE               : name = "Line";                break;
        case SIDESET            : name = "Sideset";             break;
        case GAUSSIANELLIPSE    : name = "GaussianEllipse";     break;
        case GAUSSIANLINESEGMENT: name = "GaussianLineSegment"; break;
        default:
          DGM::exception(" Enum passed to ProbeTypeToString is invalid: "
                          +asString(P));
      }
      return name;
    }

    /// Converts an integer to a ProbeType enumeration
    ProbeType intToProbeType(const int n) const {
      using boost::lexical_cast;
      using std::string;
      ProbeType P = DELTA;
      if      (n == 0) P = DELTA;
      else if (n == 1) P = GAUSSIAN;
      else if (n == 2) P = LINE;
      else if (n == 3) P = SIDESET;
      else if (n == 4) P = GAUSSIANELLIPSE;
      else if (n == 5) P = GAUSSIANLINESEGMENT;
      else
        comm->error(" Integer passed to intToProbeType is invalid: "+
                    lexical_cast<string>(n));
      return P;
    }

    /// Shared pointer to Response
    typedef DGM::Shared<Response>::Ptr Ptr;

    const DGM::Comm::Ptr comm;   ///< Parallel communicator

    Ordinal nsd;                 ///< Number of space dimensions

  private:

    int verb;                    ///< Verbosity level

  public:

    /// Average probes touching multiple elements
    /** For delta probes, average over all elements containing the
        receiver default is 'true' which means to average over all
        elements. 'false' means to take just the first element found and
        ignore the rest. */
    struct Probe {
      typedef DGM::Shared<Probe>::Ptr Ptr;
      FILE                 *file;
      ProbeType            probetype;
      KernelResponse::Ptr  kernel;
#if defined(DGM_PARALLEL) && defined(DGM_USE_MPI_IREDUCE)
      mutable MPI_Request  mpi_request;
#endif
      vector<std::pair<Point, unsigned> > line_points;
      /// Constructor
      Probe() : file(NULL),
                probetype(GAUSSIAN),
                kernel()
#if defined(DGM_PARALLEL) && defined(DGM_USE_MPI_IREDUCE)
              , mpi_request(MPI_REQUEST_NULL)
#endif
      {}
      /// Destructor
      virtual ~Probe(){
        if (file) fclose(file);
      }
      /// Copy constructor
      Probe (const Probe &p) :
        file               (p.file),
        probetype          (p.probetype),
        kernel             (p.kernel)
#if defined(DGM_PARALLEL) && defined(DGM_USE_MPI_IREDUCE)
        , mpi_request      (p.mpi_request)
#endif
      { }
      /// Equality operator
      Probe operator=(const Probe &p) {
        file               =  p.file;
        probetype          =  p.probetype;
        kernel             =  p.kernel;
#if defined(DGM_PARALLEL) && defined(DGM_USE_MPI_IREDUCE)
        mpi_request        =  p.mpi_request;
#endif
        return *this;
      }
      virtual Scalar apply(const Field *F) const;
      string allocate_file(const DGM::Comm::Ptr comm, const string &root,
                           const ProbeFormat f);
      static streamoff file_size(const DGM::Comm::Ptr comm,
                                 const string &root,
                                 const ProbeFormat f);
      string open_file(const DGM::Comm::Ptr comm, const string &root,
                       const ProbeFormat f);
      void close_file();
      void print(const Scalar x, const ProbeFormat f) const;
      void print_newline(const ProbeFormat f) const;
      Scalar read(const ProbeFormat f) const;
      void reduce_multi_processor(dVector &partial_sums) const;
      void reduce_multi_processor(std::vector<Scalar> &partial_sums) const;
      Scalar reduce_multi_processor(const Scalar partial_sum) const;
      std::streamoff write_json_header(const std::string &fname,
                                       const std::string &hname,
                                       std::ostream &fs) const;
    };

    /// Probe over a set of sides
    /** For SideSetProbes, the average quantity is returned over the
        set of sides defined. */
    struct SideSetProbe : public Probe {
      BndryStats* bstat;
      /// Constructor
      SideSetProbe(const Field *F,
                   const vector<Size> &elem,
                   const vector<Ordinal> &side) {
        probetype = SIDESET;
        bstat = new BndryStats( const_cast<Field *>(F), elem, side );
      }
      /// Destructor
      virtual ~SideSetProbe() {
        if (bstat) delete bstat;
      }
      /// Copy constructor
      SideSetProbe (const SideSetProbe &p) : bstat(0) { DGM_UNDEFINED; }
      /// Equality operator
      SideSetProbe operator=(const SideSetProbe &p) { DGM_UNDEFINED; }
      Scalar apply(const Field *F) const;
    };

    /// I/O class for probes
    struct ProbeIO {
      vector<Probe*>       probes;
      string               root;
      const DGM::Comm::Ptr comm;
      const ProbeFormat    probeFormat;
      const ProbeFiles     probeFiles;
      const bool           probeTrans;
      const bool           probeTimeTrace;
      Ordinal              nsd;
      vector<char>         native;
      bool                 init_files;
      const bool           use_mpi_io;
      const bool           flush_on_write;
      const unsigned       blocked_io_size;
      vector<unsigned>     blocked_io;
      vector<DGM::Shared<std::ostringstream>::Ptr> file_buf;
      Ordinal              num_probes;
      Ordinal              num_centers_on_proc;
#ifdef DGM_PARALLEL
      MPI_Info info;
      MPI_Datatype ioType;
      MPI_Offset disp;
      MPI_Comm ioComm;
      vector<MPI_File> mpi_files;
      vector<FILE*> c_files;
      vector<MPI_Request> requests;
      vector<int> all_offsets;
      vector<int> counts;
      vector<int> displacements;
#else
      vector<FILE *> files;
      unsigned disp;
#endif
      /// Constructor
      ProbeIO(const DGM::Comm::Ptr c,
              const ProbeFormat f,
              const ProbeFiles s,
              const unsigned n,
              const bool r,
              const bool t,
              const bool u);
      /// Destructor
     ~ProbeIO();
      void initialize_probes(vector<Probe::Ptr> p,
                             const Ordinal n,
                             const Ordinal g);
      void initialize_root(const string &r);
      void print(const vField &F, const Scalar time, const bool) ;
      void output (const Field *F, dVector &data) const ;
      void initFiles(const vField &);
      template<typename data_type> void WriteTime
        (Scalar, vector<DGM::Shared<std::ostringstream>::Ptr>&);
      template<typename data_type> void WriteVal
        (const vField&, const bool,
         vector<DGM::Shared<std::ostringstream>::Ptr>&);
      std::streamoff write_json_header(const std::string &fname,
                                       const std::string &hname,
                                       std::ostream &fs) const;
    };

#ifdef DGM_PARALLEL
    class AllReduce {
    public :
        typedef Size PROBE_GID;
        typedef unsigned PID;
        typedef std::vector<std::pair<PROBE_GID,DGM::Comm::Ptr> > COMM_VECTOR;
        typedef std::vector<PID> PROC_IDS;
        typedef std::map<PROBE_GID, PROC_IDS> PIDS;
        typedef std::pair<unsigned, std::vector<Scalar> > INDEXED_BUF;
        typedef std::map<PID, INDEXED_BUF> BUF;
        AllReduce();
        void init(const Ordinal, const COMM_VECTOR &, const DGM::Comm::Ptr);
        void post_receives();
        void all_reduce(dVector&, const PROBE_GID);
        void wait_all();
    private :
        DGM::Comm::Ptr dgm_comm;
        MPI_Comm comm_world;
        std::vector<MPI_Request> send_requests;
        std::vector<MPI_Request> recv_requests;
        PIDS msg_pids;
        BUF  send_buffer;
        BUF  recv_buffer;
        std::map<PROBE_GID, dVector> reduce_to;
        AllReduce(const AllReduce&);
    };
#else
    class AllReduce {
    public :
        typedef Size PROBE_GID;
        typedef std::vector<std::pair<PROBE_GID,DGM::Comm::Ptr> > COMM_VECTOR;

        AllReduce(){};
        void init(const Size, const COMM_VECTOR &, const DGM::Comm::Ptr){};
        void post_receives(){};
        void all_reduce(dVector&, const PROBE_GID) {}
        void wait_all(){};
    private :
        AllReduce(const AllReduce&);
    };
#endif

    typedef Probe::Ptr ProbePtr;         ///< Backwards compatibility

    vector<Probe::Ptr> probes;           ///< vector of probes
    ProbeIO probe_io;                    ///< probe IO object
    AllReduce reduce;                    ///< non-blocking all-reduce
    bool initialize_probe_files;         ///< true to initialize probe files
    vector<Point> xpt;                   ///< local coordinates of xyz in pid
    vector<Point> xyz;                   ///< location of centroids
    dVector data;                        ///< data
    vector<string> pid;                  ///< probe ids
    dVector values;                      ///< probe data

    const ProbeFormat probeFormat;       ///< Data format for probe file
    const ProbeFiles  probeFiles;        ///< File format for probe file
    const bool        probeTrans;        ///< Transpose the data with time first
    const bool        probeTimeTrace;    ///< The files contain the time trace
    const unsigned    maxOpenFiles;      ///< Maximum # of open files to allow

    const Scalar      deltaTime;         ///< Simulation time step
    const Scalar      probeDeltaTime;    ///< Sample increment for probe
          Ordinal     probeDataLength;   ///< Length of probe data
    const Ordinal     probeNumSamples;   ///< Number of samples in probe data

    Ordinal           nRealizations;     ///< Number of realizations
    const Ordinal     nComponents;       ///< Number of components
    Ordinal           ComponentsToApply;
    Ordinal           ComponentsOffset;

    Ordinal           nProbes;           ///< Total number of probes
    Ordinal           nPtProbes;         ///< Number of point probes
    Ordinal           nSsProbes;         ///< Number of sideset probes
    Ordinal           nFileProbes;       ///< Number of probes from file
    Ordinal           nEllipseProbes;    ///< Number of ellipse probes
    Ordinal           nLineSegProbes;    ///< Number of line segment probes

    /// How probe data is stored
    const StorageType probe_memory_storage;

    /// Utility constructor: from file using a DGM parameter table
    static Response* factory(const vField &F,
                             const string &fname_node,
                             Table &params,
                             const DGM::Comm::Ptr = DGM::Comm::World);
#ifdef DGM_USE_JSON

    /// Utility constructor for standard Domain use
    static Response* factory(const vField &F, 
                             Domain *const domain);

    /// General utility constructor
    static Response* factory(const vField &F, 
                             const Domain *const domain,
                             Json::Value &resp);

    /// Utility constructor: from a matrix of xyz coordinates with JSON root
    static Response* factory(const vField &F,
                             const dMatrix &xyz,
                             Json::Value &resp,
                             const Domain *const domain);
#endif

    /// Destructor
    ~Response();

    /// Output the solution
    void output(const Field *, const string & = "solution.dat");

    /// Hot-wire-type probe
    void probe(const vField &, const string &, const Scalar, const bool);

    /// Accessor for valid
    bool isValid() const { return valid; }

    void component_offset(const Ordinal offset) {ComponentsOffset = offset;}

    /// Accessor for verbosity
    int verbosity() const { return verb; }

    /// Useful info for sizing arrays.
    size_t probes_on_proc() const;
    bool probe_on_proc(const Ordinal n) const;

    /// Send communication data-structure
    /** This information will be used to construct a single MPI_Isend call. */
    struct Send {
      Ordinal         to;     ///< Send to this processor
      vector<Size>    gid;    ///< probes to send
      vector<Ordinal> lid;    ///< local index in probe_trace_data array
      dMatrix         buf;    ///< communication buffer
      Send(const Ordinal t,
          const Ordinal nc,
          const vector<Size> &g,
          const vector<Ordinal> &l) :
        to(t), gid(g), lid(l),
        buf(numeric_cast<Ordinal>(g.size()),numeric_cast<Ordinal>(nc)) {}
      Send &operator=(Send const &s) {
        to=s.to;
        gid=s.gid;
        lid=s.lid;
        buf.resize(s.buf);
        buf=s.buf;
        return *this;
      }
    };

    /// Receive communication data-structure
    /** This information will be used to construct a single MPI_Irecv call. */
    struct Recv {
      Ordinal         from;  ///< Receive from this processor
      vector<Size>    gid;   ///< probes to receive
      vector<Ordinal> lid;   ///< local index in probes array
      dMatrix         buf;   ///< communication buffer
      Recv(const Ordinal f,
          const Ordinal  nc,
          const vector<Size> &g,
          const vector<Ordinal> &l) :
        from(f), gid(g), lid(l),
        buf(numeric_cast<Ordinal>(g.size()),numeric_cast<Ordinal>(nc)) {}
      Recv &operator=(Recv const &s) {
         from=s.from;
         gid=s.gid;
         lid=s.lid;
         buf.resize(s.buf);
         buf=s.buf;
         return *this;
       }
    };

#ifdef DGM_PARALLEL
    /// Vector of requests for nonblocking sends
    vector<MPI_Request> send_requests;
    /// Vector of requests for nonblocking receives
    vector<MPI_Request> recv_requests;
#endif
    /// Vectors of send message info.
    /** Each entry in the vector is the information for a single send
     *  or a single MPI receive call.
     */
    vector<Send> send_info;
    /// Vectors of receive message info.
    vector<Recv> recv_info;
    /// Map from gid to lid for the probe_trace_data.
    /** This is used to help pack up and send the data that
        needs to be be packed and sent.  The unpacking can use
        the information already available in the probes array
        of Probe structures. */
    map<Size,Ordinal> gid_to_lid;

    /// Fill in send_info and recv_info vectors.
    void initialize_communication_pattern(const Ordinal glen);

    /// Get some information in order to set up memory for read_probe
    bool get_interpolation_info(Ordinal &probe_num_time_steps,
                                const vector<string> &component_names,
                                Scalar &probe_data_dt,
                                const unsigned num_probes,
                                const string &state_root,
                                const string &run_file_base );

    /// Read binary response data
    void read_probe(vector<dArray> &trace,
                    const string &state_root,
                    const string &shot_file_base,
                    const vector<string> &component_names,
                    const int chop=-1);

    /// Time interpolator interface
    class Interpolator {
    public:
      Interpolator(){};
      virtual ~Interpolator(){};
      virtual dMatrix operator()(const double, const dArray&) const=0;
      virtual fMatrix operator()(const float,  const fArray&) const=0;
    };

    Ordinal time_steps_from_file(const string &state_root,
                              const string &run_file_base,
                              const vector<string> &component_names) const;
    Ordinal init_probe_data(const string &state_root,
                         const string &run_file_base,
                         const vector<string> &component_names,
                         const Ordinal Nrealizations,
                         const Ordinal Nt);
    bool isFloat() const { return probeFormat == FLOAT;}
    Ordinal LocalNumProbeData() const;
    Ordinal LocalNumRealizations() const;
    Ordinal LocalNumComponents() const;
    Ordinal LocalNumTimeValues() const;
    Ordinal ProbeDataSize() const;
    Scalar ProbeData(const Ordinal,
                     const Ordinal,
                     const Ordinal,
                     const Ordinal) const;

    Ordinal size_objective_function(dMatrix &data, const Ordinal components) {
      const Ordinal Nreceivers = numeric_cast<Ordinal>(probes_on_proc());
      if (Nreceivers) data.resize(Nreceivers, components);
      data = 0;
      return Nreceivers;
    }

    Scalar weighted_norm(const dVector &,
                         const Scalar,
                         const Interpolator *);

    bool subtract_weighted_traces(dMatrix &data,
                                  const dVector &ws,
                                  const TimeInt *time_int,
                                  const Interpolator *interp,
                                  const Scalar   dt,
                                  const Ordinal istep,
                                  const Ordinal sstep);

    template <typename scalar>
    bool subtract_weighted_traces(dMatrix &data,
                                  const vector<CMC::Array<scalar,Ordinal> > &,
                                  const dVector &ws,
                                  const TimeInt *time_int,
                                  const Interpolator *interp,
                                  const Scalar   dt,
                                  const Ordinal istep,
                                  const Ordinal sstep);

    void interpolate_weights(const dArray &weights,
                             TimeInt *time_int,
                             const Scalar time,
                             const Ordinal istep,
                             const Ordinal sstep,
                             dMatrix &now) const;

    void multiply_by_weights(dMatrix &data,
                             const dArray &weights,
                                   TimeInt *time_int,
                             const Ordinal istep,
                             const Ordinal sstep) const;

    void addScaled(vField &U,
                   const dMatrix &data,
                   const Scalar  penalty) const {
      FunctionTimer *timer=0;
      if (verbosity()>1) {
        static FunctionTimer Timer("Response::addScaled"); timer=&Timer;
      }
      FunctionSentry sentry(timer);
      for (Ordinal p=0; p<data.rows(); ++p)
        for (Ordinal i=0; i<data.cols(); i++)
          probes[p]->kernel->addScaled( U[i+ComponentsOffset], 
                                        penalty * data[p][i] );
    }

    void addWeightedScaled(vField &U,
                           const dMatrix &data,
                           const dMatrix &now,
                           const Scalar  penalty) const {
      FunctionTimer *timer=0;
      if (verbosity()>1) {
        static FunctionTimer Timer("Response::addWeightedScaled"); timer=&Timer;
      }
      FunctionSentry sentry(timer);
      for (Ordinal p=0; p<data.rows(); ++p)
        for (Ordinal i=0; i<data.cols(); i++)
          probes[p]->kernel->addScaled( U[i+ComponentsOffset],
                                        penalty * data[p][i] * now[p][i] );
    }

    void integrate_probes(dMatrix &data,
                          const vField &U) {
      FunctionTimer *timer=0,*ctimer=0;
      if (verbosity()>1) {
        static FunctionTimer Timer("Response::integrate_probes"); timer=&Timer;
      }
      FunctionSentry sentry(timer);
#ifndef DGM_RESPONSE_USE_BLOCKING_ALLREDUCE
      reduce.post_receives();
#endif
      data = 0;
      for (Ordinal p=0; p<data.rows(); ++p) {
        dVector row (data.row(p));
        for (Ordinal i=0; i<data.cols(); i++) {
          row[i] = probes[p]->kernel->integrate_probes(U[i+ComponentsOffset]);
        }
        {
          if (verbosity()>1) {
            static FunctionTimer
              Ctimer("Response::integrate_probes:communication start");
            ctimer=&Ctimer;
          }
          FunctionSentry sentry(ctimer);
#ifdef DGM_RESPONSE_USE_BLOCKING_ALLREDUCE
          probes[p]->reduce_multi_processor(row);
#else
          reduce.all_reduce(row, probes[p]->kernel->global_id());
#endif
        }
      }
#ifndef DGM_RESPONSE_USE_BLOCKING_ALLREDUCE
      {
        FunctionTimer *ntimer=0;
        if (verbosity()>1) {
          static FunctionTimer
            Ntimer("Response::integrate_probes:communication end");
          ntimer=&Ntimer;
        }
        FunctionSentry sentry(ntimer);
        reduce.wait_all();
      }
#endif
    }

    void average_probes_across_fields(dMatrix &data, const Ordinal cols = 0) {
      FunctionTimer *timer=0;
      if (verbosity()>1) {
        static FunctionTimer Timer("Response::average_probes_across_fields"); 
        timer=&Timer;
      }
      FunctionSentry sentry(timer);
      const Ordinal col = cols ? cols : data.cols();
      for (Ordinal p=0; p<data.rows(); ++p) {
        Scalar avg_row_sum = 0;
        for (Ordinal i=0; i<col; i++) avg_row_sum += data(p,i);
        avg_row_sum /= col;
        for (Ordinal i=0; i<col; i++) data(p,i)  = avg_row_sum;
      }
    }

    void average_deltas_on_element_boundaries(dMatrix &data) {
      for (Ordinal p=0; p<data.rows(); ++p) {
        if (probes[p]->kernel->divide_for_average() &&
            probes[p]->kernel->divide_for_average() != 1) {
          for (Ordinal nc=0; nc<data.cols(); nc++)
            data[p][nc] /= probes[p]->kernel->divide_for_average();
        }
      }
    }

    Scalar Norm(const dMatrix &data) const {
      Scalar result=0.0;
      for (Ordinal nr=0; nr<data.rows(); nr++) {
        if (probes[nr]->kernel->owned_by_this_proc()) {
          for (Ordinal i=0; i<data.cols(); i++) {
            result += data[nr][i] * data[nr][i];
          }
        }
      }
      return result;
    }

    // compute a metric norm (squared) given dta
    Scalar metricNorm(const dMatrix &data, const dMatrix &metric) const {
      Scalar result=0.0;
      for (Ordinal nr=0; nr<data.rows(); nr++) {
        if (probes[nr]->kernel->owned_by_this_proc()) {
          for (Ordinal i=0; i<data.cols(); i++) {
            result += data[nr][i] * metric[nr][i] * data[nr][i];
          }
        }
      }
      return result;
    }

    template<class Filter>
    void apply_filter_to_probe_data(const Filter &F) {
      if (isFloat()) {
        const Ordinal I=numeric_cast<Ordinal>(fprobe_trace_data.size());
        if (I) {
          const Ordinal J=fprobe_trace_data[0].dim1();
          const Ordinal K=fprobe_trace_data[0].dim2();
          const Ordinal L=fprobe_trace_data[0].dim3();
          for (Ordinal i=0; i<I; ++i)
            for (Ordinal j=0; j<J; ++j)
              F.apply(fprobe_trace_data[i][j], K, L);
        }
      } else {
        const Ordinal I=numeric_cast<Ordinal>(dprobe_trace_data.size());
        if (I) {
          const Ordinal J=dprobe_trace_data[0].dim1();
          const Ordinal K=dprobe_trace_data[0].dim2();
          const Ordinal L=dprobe_trace_data[0].dim3();
          for (Ordinal i=0; i<I; ++i)
            for (Ordinal j=0; j<J; ++j)
              F.apply(dprobe_trace_data[i][j], K, L);
        }
      }
    }

    void apply_scaling_to_probe_data(const Real S) {
      if (isFloat()) {
        const Ordinal I=numeric_cast<Ordinal>(fprobe_trace_data.size());
        if (I) {
          const Ordinal J=fprobe_trace_data[0].dim1();
          const Ordinal K=fprobe_trace_data[0].dim2();
          const Ordinal L=fprobe_trace_data[0].dim3();
          for (Ordinal i=0; i<I; ++i)
            for (Ordinal j=0; j<J; ++j)
              for (Ordinal k=0; k<K; ++k)
                for (Ordinal l=0; l<L; ++l)
                  fprobe_trace_data[i][j][k][l] *= S;
        }
      } else {
        const Ordinal I=numeric_cast<Ordinal>(dprobe_trace_data.size());
        if (I) {
          const Ordinal J=dprobe_trace_data[0].dim1();
          const Ordinal K=dprobe_trace_data[0].dim2();
          const Ordinal L=dprobe_trace_data[0].dim3();
          for (Ordinal i=0; i<I; ++i)
            for (Ordinal j=0; j<J; ++j)
              for (Ordinal k=0; k<K; ++k)
                for (Ordinal l=0; l<L; ++l)
                  dprobe_trace_data[i][j][k][l] *= S;
        }
      }
    }

  private:

    vector<dArray> dprobe_trace_data;  ///< trace data in double

    vector<fArray> fprobe_trace_data;  ///< trace data in float

    string _name;                      ///< name of this response
    string _root;                      ///< root of this problem

    /// Constructor from an response file
    Response(const vField &,
             const string &,
             const DGM::Comm::Ptr = DGM::Comm::World,
             const ProbeFormat = ASCII,
             const ProbeFiles = SEPARATE,
             const unsigned blocking_size = 1,
             const bool FlushOnWrite = false,
             const bool FilesTransposed = false,
             const bool TimeTrace = true,
             const unsigned Max_Open_files = 1,
             const Scalar   Delta_Time     = 0,
             const Scalar   Probe_Delta_Time = 0,
             const Ordinal  Probe_Num_Samples = 0,
             const StorageType probe_memory_storage = WHERE_NEEDED,
             const int Verbosity = 0);

    /// Constructor from a list of xyz locations
    Response(const vField &,
             const dMatrix &,
             const DGM::Comm::Ptr = DGM::Comm::World,
             const ProbeFormat = ASCII,
             const ProbeFiles = SEPARATE,
             const unsigned blocking_size = 1,
             const bool FlushOnWrite = false,
             const bool FilesTransposed = false,
             const bool TimeTrace = true,
             const unsigned Max_Open_files = 1,
             const Scalar   Delta_Time     = 0,
             const Scalar   Probe_Delta_Time = 0,
             const Ordinal  Probe_Num_Samples = 0,
             const StorageType probe_memory_storage = WHERE_NEEDED,
             const int Verbosity = 0);

#ifdef DGM_USE_JSON
    /// Constructor from a Json specification
    Response(const vField &,
             const Json::Value &,
             const DGM::Comm::Ptr = DGM::Comm::World,
             const ProbeFormat = ASCII,
             const ProbeFiles = SEPARATE,
             const unsigned blocking_size = 1,
             const bool FlushOnWrite = false,
             const bool FilesTransposed = false,
             const bool TimeTrace = true,
             const unsigned Max_Open_files = 1,
             const Scalar   Delta_Time     = 0,
             const Scalar   Probe_Delta_Time = 0,
             const Ordinal  Probe_Num_Samples = 0,
             const StorageType probe_memory_storage = WHERE_NEEDED,
             const int Verbosity = 0);
#endif

    dMatrix interpolate_in_time(const Scalar, const int) const;

    void initialize_point_response_probes(const string &probeName,
                                          const vField &,
                                          const dMatrix &,
                                          const vector<vector<Size> > &,
                                          const vector<string>&,
                                          const Json::Value &,
                                          const Ordinal);

    void initialize_ellipse_response_probes(const string &probeName,
                                            const vField &,
                                            const dMatrix &,
                                            const dMatrix &,
                                            const iMatrix &,
                                            const vector<dMatrix> &,
                                            const vector<string>&,
                                            const Json::Value &,
                                            const Ordinal);

    void initialize_linesegment_response_probes(
        const string                         &probeName,
        const vField                         &F,
        std::vector<GaussianLineSegment2d *> &gls,
        const Ordinal                        &nsd,
        const Ordinal                        nProbes
    );

    void setup_communication_pattern();

    template<typename datatype>
    void write_norms(const vector<CMC::Array<datatype,Ordinal> > &trace,
                     const vector<string> &component_names);

    template<typename scalar, typename datatype>
    void read_probe(vector<CMC::Array<datatype,Ordinal> > &trace,
                    const vector<int> &D,
                    const vector<string> &component_names,
                    const string &state_root,
                    const string &shot_file_base);

    template <typename scalar, typename datatype>
    void read_probe_separate_serial(vector<CMC::Array<datatype,Ordinal> > &,
                                    const string &,
                                    const string &);

    template <typename scalar, typename datatype>
    void read_probe_combined_serial(vector<CMC::Array<datatype,Ordinal> > &,
                                    const vector<string> &,
                                    const string &,
                                    const string &);

    template<typename scalar, typename datatype>
    void read_probe_combined_parallel(vector<CMC::Array<datatype,Ordinal> > &,
                                      const vector<int> &,
                                      const vector<string> &,
                                      const string &,
                                      const string &);

    /// Gather to one processor
    dVector gather_data(const Field *F);
    dVector gather() const;
    void write_to_file(const dVector, const string &fname_solver) const;

    static void convert_strings_to_enums(ProbeFormat &,
                                         ProbeFiles  &,
                                         StorageType  &,
                                         const string &,
                                         const string &,
                                         const string &,
                                         const DGM::Comm::Ptr);

    bool parse_json( const Json::Value &jss,           ///< parameters
                     const vField &F,                  ///< vector field
                     dMatrix &xyz,                     ///< xyz storage
                     vector<string> &nid,              ///< probe (node) IDs
                     vector< vector<Size> > &elem,     ///< element IDs
                     vector< vector<Ordinal> > &side,  ///< side IDs
                     Scalar &stddev,                   ///< standard deviation
                     const DGM::Comm::Ptr comm,        ///< communicator
                     const unsigned verb               ///< verbosity level
                     );

    void initialize_sideset_probes( const vField &F,
                                    const dMatrix &xyz_,
                                    const vector<string> &nid,
                                    const vector< vector<Size> > &elem,
                                    const vector< vector<Ordinal> > &side,
                                    const Scalar stddev );

    static bool read_optional_response_file(unsigned &,
                                            unsigned &,
                                            Scalar   &,
                                            bool     &,
                                            const string &,
                                            const DGM::Comm::Ptr);
    /// Scan for a left curly bracket
    static void scan_lb(ifstream &in ) {
      string token;
      if (!(in >> token)) error("Cannot read Response type");
      if ( token != "{" ) error("Response syntax error:  Expected a \"{\"");
    }

    /// Scan for a right curly bracket
    static void scan_rb(ifstream &in ) {
      string token;
      while (token != "}" )
        if (!(in >> token)) error("Response syntax error:  Cannot find \"}\"");
    }

  };  // Response class

} // namespace DGM

#endif  // DGM_RESPONSE_HPP
