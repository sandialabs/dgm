/*=============================================================================
  Title:      Refine2D 

  Contact:    S. Scott Collis
              Sandia National Laboratories
              Albuquerque, NM 87175
              (505) 284-1123
              sscoll@sandia.gov

  Copyright:  (c)2016 Sandia National Laboratories
=============================================================================*/


#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
#include <limits>
#include <vector>
#include <tuple>
#include <array>
#include <ctime>
#include <map>
#include <set>

#include <boost/serialization/vector.hpp>
#include <boost/serialization/array.hpp>
#include <boost/mpi.hpp>
#include <boost/program_options.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

typedef unsigned long long UInt;
typedef double             Real;

typedef std::array<UInt,4>   Connect;
typedef std::array<UInt,2>   Refine;
typedef std::pair<UInt,UInt> EleSide;


std::ostream& operator<< (std::ostream &os, const Connect& c) {
  os <<" Connect:("<<c[0]<<","<<c[1]<<")->("<<c[2]<<","<<c[3]<<")";
  return os;
} 
std::ostream& operator<< (std::ostream &os, const EleSide& e) {
  os <<" Element:"<<e.first<<" Side:"<<e.second;
  return os;
} 


struct options {
  const bool pause;
  const bool sanity_check;
  const bool read_binary;
  const bool write_binary;
  const std::string root;
  options (const bool p,  const bool s, 
           const bool rb, const bool wb, const std::string r) 
    : pause(p), sanity_check(s), read_binary(rb), write_binary(wb), root(r){}
};

struct Point {
  Real X,Y;
  Point (const Real x, const Real y) : X(x), Y(y) {}
  Point () : X(0), Y(0) {}
  template<class Archive>
  void serialize(Archive &ar, const unsigned int) {ar & X & Y;}
};


std::ostream& operator<< (std::ostream &os, const Point& p) {
  os <<" X:"<<p.X<<" Y:"<<p.Y;
  return os;
} 

struct Element {
  enum TYPE{QUAD, SPECTRALQUAD};
  TYPE   type;
  UInt   gid; 
  std::array<Point,4> nodes;
  Element(const TYPE t, const UInt g, const std::array<Point,4> N) : 
     type(t), gid(g), nodes(N) {}
  Element() : type(QUAD), gid(0), nodes() {}
  std::pair<Point,Point> end_points(UInt s) const {
    const std::pair<Point,Point> Ps(nodes[s], nodes[(s+1)%4]);
    return Ps;
  }
  template<class Archive>
  void serialize(Archive &ar, const unsigned int){ar & type & gid & nodes;}
};
std::ostream& operator<< (std::ostream &os, const Element& e) {
  os <<" Gid:"<<e.gid<<" ";
  for (UInt i=0; i<4; ++i) os<<e.nodes[i]<<" ";
  os<<std::endl;
  return os;
} 

namespace boost {
namespace serialization {
  template<class Archive>
  void serialize(Archive &ar, EleSide &e, const unsigned int) {ar & e.first & e.second;}

  template<class Archive>
  void serialize(Archive &ar, std::pair<std::pair<UInt,UInt>,std::vector<std::pair<UInt,UInt>>> &e, const unsigned int) 
    {ar & e.first & e.second;}

  template<class Archive>
  void serialize(Archive &ar, std::pair<Connect,UInt> &e, const unsigned int) 
    {ar & e.first & e.second;}

  template<class Archive>
  void serialize(Archive &ar, std::tuple<char,UInt,UInt> &t, const unsigned int) 
    {ar & std::get<0>(t) & std::get<1>(t) & std::get<2>(t);}

}
namespace mpi {
template<> struct is_mpi_datatype<std::pair<Connect,UInt>> : mpl::true_{};
}
}

BOOST_IS_MPI_DATATYPE(Connect)
BOOST_IS_MPI_DATATYPE(Refine)
BOOST_IS_MPI_DATATYPE(EleSide)
BOOST_IS_MPI_DATATYPE(Point)
BOOST_IS_MPI_DATATYPE(Element)
BOOST_CLASS_TRACKING(Connect, track_never)
BOOST_CLASS_TRACKING(Refine,  track_never)
BOOST_CLASS_TRACKING(EleSide, track_never)
BOOST_CLASS_TRACKING(Point,   track_never)
BOOST_CLASS_TRACKING(Element, track_never)


struct Distribution {
  virtual UInt num_owned()             const = 0;
  virtual UInt num_owned(const UInt p) const = 0;
  virtual UInt nelem()                 const = 0;
  virtual UInt begin()                 const = 0;
  virtual bool owned(const UInt e)     const = 0;
  virtual UInt owner(const UInt e)     const = 0;
  virtual ~Distribution(){}
};

struct UniformDistribution : public Distribution{
  const UInt num_elem;
  const UInt rank;
  const UInt num_proc;
  const UInt start;
  const UInt finish;
  UniformDistribution(const UInt n, const UInt r, const UInt np) : 
    num_elem(n), rank(r), num_proc(np), 
    start ((num_elem*rank    )/num_proc),
    finish((num_elem*(rank+1))/num_proc) {}

  UInt num_owned() const {
    const UInt owned = finish - start;  
    return owned;
  }
  UInt num_owned(const UInt p) const { 
    const UInt p_start ((num_elem*p    )/num_proc);
    const UInt p_finish((num_elem*(p+1))/num_proc);
    const UInt owned = p_finish - p_start;
    return owned;
  }
  UInt nelem()     const {
    return num_elem;
  }
  UInt begin() const {
    return start;
  }

  bool owned(const UInt e) const {
    const bool own = (start <= e && e < finish);
    return own;
  }
  UInt owner(const UInt e) const {
    UInt p = 0;
    for (; p<num_proc; ++p) if (begin(p)<=e && e<begin(p+1)) break;
    return p;
  } 
private :
  UInt begin(const UInt p) const {
    return (num_elem*p)/num_proc;
  }
};

struct NonUniformDistribution : public Distribution{
  const UInt num_elem;
  const std::vector<UInt> first_gids;
  const UInt num_my_gids;
  const UInt rank;
  const UInt num_proc;
  NonUniformDistribution(const std::vector<UInt> gids,  
                         const UInt ngids, const UInt nelem,
                         const UInt r, const UInt np) : 
    first_gids(gids), num_my_gids(ngids), num_elem(nelem), rank(r), num_proc(np)  {}

  UInt num_owned() const {
    return num_my_gids;
  }
  UInt num_owned(const UInt p) const { 
    UInt owned;
    if (p<num_proc-1) owned = first_gids[p+1] - first_gids[p];
    else              owned = num_elem        - first_gids[num_proc-1];
    return owned;
  }

  UInt nelem()     const {
    return num_elem;
  }
  UInt begin() const {
    return first_gids[rank];
  }

  bool owned(const UInt e) const {
    const bool own = (first_gids[rank] <= e && e < first_gids[rank]+num_my_gids);
    return own;
  }

  UInt owner(const UInt e) const {
    static const UInt null = std::numeric_limits<UInt>::max();
    UInt proc = null; 
    for (UInt p=0; p<num_proc && proc==null; ++p) {
      if      (p == num_proc-1)     proc = num_proc-1;
      else if (e < first_gids[p+1]) proc = p; 
    }
    return proc;
  } 
};

namespace {


options parse_command_line(int argc, char *argv[],
                           const boost::mpi::communicator &comm) {
  using namespace boost::program_options;

  options_description desc(std::string("Allowed options"));
  desc.add_options()
    ("help", "product help message")
    ("root", "Base name of mesh files")
    ("pause", "Pause until keyboard input.")
    ("sanity_check", "Extra checks for mesh consistancy.") 
    ("read_binary", "Read binary mesh.grd and mesh.cn.") 
    ("write_binary", "Write binary mesh.grd and mesh.cn ONLY.");
  positional_options_description p;
  p.add("root", -1);

  variables_map vm;
  store(command_line_parser(argc, argv).options(desc).positional(p).run(), vm);
  notify(vm);
  if (vm.count("help") && !comm.rank()) {
    std::cout << desc << std::endl;
    exit(0);
  }
  if (vm.count("sanity_check") && !comm.rank())
   std::cout<<" sanity_check flag set."<<std::endl;

  if (vm.count("read_binary") && !comm.rank())
   std::cout<<" read_binary flag set."<<std::endl;

  if (vm.count("write_binary") && !comm.rank())
   std::cout<<" write_binary flag set."<<std::endl;

  const std::string root = vm.count("root") ? vm["root"].as<std::string>() : "ref";
  options opt(vm.count("pause"), 
              vm.count("sanity_check"), 
              vm.count("read_binary"), 
              vm.count("write_binary"), 
              root);
  return opt;
}

std::string read_header(const std::string &mesh_file) {
  std::ifstream in(mesh_file);
  if (!in)            throw std::logic_error(" 33 -- Error opening Mesh file.");
  if (in.peek()!='{') throw std::logic_error(" 35 -- Can not read Json header.");
  std::string buffer;
  UInt nb=0;
  while ( in.good() ) { 
    const char c = in.get();
    if (c=='{') nb++;
    if (c=='}') nb--;
    buffer += c;
    if (nb==0) break;
  }
  buffer += '\n';
  return buffer;
}

UniformDistribution determine_owned_elements(const options &opt, 
                                             const boost::mpi::communicator &comm) {
  UInt ne;
  if (!comm.rank()) {
    if (opt.read_binary) {
      std::string mesh_file = opt.root+".grd";
      boost::property_tree::ptree pt;
      const std::string buffer = read_header(mesh_file);
      std::istringstream istr(buffer);
      boost::property_tree::json_parser::read_json(istr, pt);
      UInt nsd;
      ne  = pt.get<UInt>("Nel");
      nsd = pt.get<UInt>("Nsd"); 
      if (nsd != 2)  throw std::logic_error(" 20 -- 2D quads only supported.");
    } else {
      std::string mesh_file = opt.root+".msh";
      std::ifstream in(mesh_file);
      if (!in) throw std::logic_error(" 10 -- Error opening Mesh file.");

      std::string buffer; 
      getline(in,buffer); // flush comment

      UInt nsd;
      in >> ne >> nsd;
      getline(in,buffer); // flush comment
      if (nsd != 2)  throw std::logic_error(" 20 -- 2D quads only supported.");
    }
  }
  boost::mpi::broadcast(comm, ne, 0);
  
  UniformDistribution dist(ne, comm.rank(), comm.size());
  return dist; 
}

void read_binary_mesh_connectivity(std::vector<Connect> &connections,
                                   const std::string    &root,
                                   const Distribution   &dist,
                                   const boost::mpi::communicator &comm) {

  UInt header_offset=0;
  const std::string mesh_file = root+".cn";

  if (!comm.rank()) header_offset = read_header(mesh_file).size();
  boost::mpi::broadcast(comm, header_offset, 0);

  const UInt nelem        = dist.nelem();
  const UInt num_owned    = dist.num_owned();
  const UInt num_first    = dist.begin();

  MPI_File fh;
  MPI_Status status;
  MPI_Offset offset = header_offset;
  MPI_Comm mpi_comm = comm;
  {
    char *fname = const_cast<char*>(mesh_file.c_str());
    MPI_File_open(mpi_comm, fname,
                  MPI_MODE_RDONLY,
                  MPI_INFO_NULL, &fh);
  }
  MPI_File_seek (fh, offset, MPI_SEEK_SET);

  std::vector<int> D(num_owned);
  MPI_File_seek (fh, num_first*sizeof(int), MPI_SEEK_CUR);
  MPI_File_read_all(fh, D.data(), D.size(), MPI_INT, &status);
  offset += nelem*sizeof(int);
  MPI_File_seek (fh, offset, MPI_SEEK_SET);

  std::vector<int> L(num_owned);
  MPI_File_seek (fh, num_first*sizeof(int), MPI_SEEK_CUR);
  MPI_File_read_all(fh, L.data(), L.size(), MPI_INT, &status);
  offset += nelem*sizeof(int);
  MPI_File_seek (fh, offset, MPI_SEEK_SET);
  
  MPI_Offset first_connect = D[0];
  UInt num_connect = 0;
  for (const int i : L) num_connect += i;
  if (num_connect + D[0] != D.back()+L.back())
    throw std::logic_error(" 22 -- Displacemnts incorrect.");

  std::vector<std::array<int,5>> C(num_connect);
  MPI_File_seek (fh, 5*first_connect*sizeof(int), MPI_SEEK_CUR);
  MPI_File_read_all(fh, C.data(), 5*C.size(), MPI_INT, &status);

  connections.resize(num_connect);
  for (UInt i=0; i<num_connect; ++i) {
    for (UInt j=0; j<4; ++j) connections[i][j] = C[i][j];
  }
  MPI_File_close(&fh); 

  std::set<UInt> procs;
  for (const Connect &C : connections) 
    if (!dist.owned(C[2])) procs.insert(dist.owner(C[2]));

  std::map<UInt,std::shared_ptr<boost::mpi::packed_oarchive>> send_bufs;
  std::map<UInt,std::shared_ptr<boost::mpi::packed_iarchive>> recv_bufs;
  
  for (const UInt p : procs) {
    send_bufs[p].reset(new boost::mpi::packed_oarchive(comm));
    recv_bufs[p].reset(new boost::mpi::packed_iarchive(comm));
  }

  std::vector<boost::mpi::request> recv_requests;
  for (auto &buf : recv_bufs) 
    recv_requests.push_back(comm.irecv(buf.first, 0, *buf.second));

  std::map<UInt,std::vector<Connect>> to_send;
  for (const Connect &C : connections) 
    if (!dist.owned(C[2])) to_send[dist.owner(C[2])].push_back(C);

  for (const std::pair<UInt,std::vector<Connect>> &S : to_send)
    *send_bufs[S.first] << S.second;
  
  std::vector<boost::mpi::request> send_requests;
  for (auto &buf : send_bufs) 
    send_requests.push_back(comm.isend(buf.first, 0, *buf.second));
  
  boost::mpi::wait_all(recv_requests.begin(), recv_requests.end());
  for (auto &buf : recv_bufs) {
    std::vector<Connect> recv_data;
    *buf.second >> recv_data;
    for (const Connect &C : recv_data) connections.push_back(C);
  }

  boost::mpi::wait_all(send_requests.begin(), send_requests.end());
}
                  
void read_binary_mesh_file(std::vector<Element> &elements,
                           const std::string    &root,
                           const Distribution   &dist,
                           const boost::mpi::communicator &comm) {
  UInt header_offset=0;
  const std::string mesh_file = root+".grd";

  if (!comm.rank()) header_offset = read_header(mesh_file).size();
  boost::mpi::broadcast(comm, header_offset, 0);

  const UInt nelem        = dist.nelem();
  const UInt num_owned    = dist.num_owned();
  const UInt num_first    = dist.begin();
  header_offset += sizeof(int); //skip number of elements
  header_offset += sizeof(int); //skip spatial dimension  
  header_offset += sizeof(int); //skip number of coordinates = 4 * nelem
  
  
  Element::TYPE elem_type;
  if (!comm.rank()) {
    std::ifstream in(mesh_file,std::ifstream::binary);
    in.seekg(header_offset);
    int type;
    in.read(reinterpret_cast<char*>(&type), sizeof(int));
    if      (type == 1 ) elem_type = Element::QUAD;
    else if (type == 13) elem_type = Element::SPECTRALQUAD; 
    else throw std::logic_error(" 22 -- Count not read element type.");
    const std::string name = type==1 ? "QUAD" : "SPECTRALQUAD";
    std::cout<<" Just assumeing that all elements are type:"<<name<<std::endl;
  }
  header_offset += nelem*sizeof(int); //skip elemnet types for now
  header_offset += nelem*sizeof(int); //skup displacements, assume only quads

  MPI_File fh;
  MPI_Status status;
  MPI_Offset offset = header_offset;
  MPI_Comm mpi_comm = comm;
  {
    char *fname = const_cast<char*>(mesh_file.c_str());
    MPI_File_open(mpi_comm, fname,
                  MPI_MODE_RDONLY,
                  MPI_INFO_NULL, &fh);
  }
  MPI_File_seek (fh, offset, MPI_SEEK_SET);

  std::vector<double> X(4*num_owned);
  MPI_File_seek (fh, 4*num_first*sizeof(double), MPI_SEEK_CUR);
  MPI_File_read_all(fh, X.data(), X.size(), MPI_DOUBLE, &status);
  offset += 4*nelem*sizeof(double);
  MPI_File_seek (fh, offset, MPI_SEEK_SET);

  std::vector<double> Y(4*num_owned);
  MPI_File_seek (fh, 4*num_first*sizeof(double), MPI_SEEK_CUR);
  MPI_File_read_all(fh, Y.data(), Y.size(), MPI_DOUBLE, &status);
  
  MPI_File_close(&fh); 

  elements.resize(num_owned);
  for (UInt j=0; j<num_owned; ++j) {
    Element &e = elements[j];
    e.type = elem_type;
    e.gid  = num_first+j;
    for (UInt i=0; i<4; ++i) e.nodes[i].X = X[4*j+i];
    for (UInt i=0; i<4; ++i) e.nodes[i].Y = Y[4*j+i];
  }
}

void read_ascii_mesh_file(std::vector<Element> &elements,
                           const std::string    &root,
                           const Distribution   &dist,
                           const boost::mpi::communicator &comm) {

  std::vector<std::shared_ptr<boost::mpi::packed_oarchive>> send_comm_buffers(comm.size());
  for (std::shared_ptr<boost::mpi::packed_oarchive> &i : send_comm_buffers) 
    i.reset(new boost::mpi::packed_oarchive(comm));

  std::vector<boost::mpi::request> send_requests(send_comm_buffers.size());

  boost::mpi::packed_iarchive recv_comm_buffer(comm);
  boost::mpi::request recv_request = comm.irecv(0, 0, recv_comm_buffer);

  if (!comm.rank()) {
    const std::string mesh_file = root+".msh";
    std::ifstream in(mesh_file);
    if (!in) throw std::logic_error(" 30 -- Error opening Mesh file.");
    std::string flush; 
    getline(in,flush); 
    getline(in,flush); 

    UInt e=0;
    for (UInt p=0; p<comm.size(); ++p) {
      std::string flush, type;
      Element::TYPE prev_t;
      UInt id;
      std::array<Point,4> N;
  
      const UInt owned_by_p = dist.num_owned(p);
      std::vector<Element> send_elements(owned_by_p);  
      for (UInt l=0; l<owned_by_p; ++l,++e) {
        in >> flush >> id >> type;
        getline(in,flush);
        if (type != "QUAD" && type != "SPECTRALQUAD")
          throw std::logic_error(" 40 -- Only quads supproted.");
        const Element::TYPE t = 
          type=="QUAD" ? Element::QUAD : Element::SPECTRALQUAD;
        for (unsigned i=0; i<4; ++i) in >> N[i].X;
        getline(in,flush); 
        for (unsigned i=0; i<4; ++i) in >> N[i].Y;
        getline(in,flush); 
        send_elements[l] = Element(t,e,N);
        if (l && t!=prev_t)
          throw std::logic_error(" 44 -- Homogdnous meshes supported.");
        prev_t = t;
      }
      *send_comm_buffers[p] << send_elements; 
      send_requests[p] = comm.isend(p, 0 , *send_comm_buffers[p]);
    }
  }
  boost::mpi::wait_all(&recv_request, &recv_request+1);
  recv_comm_buffer >> elements;

  if (!comm.rank()) {
    boost::mpi::wait_all(send_requests.begin(), send_requests.end());
  }
}

void read_ascii_mesh_connectivity(std::vector<Connect> &connections,
                                   const std::string    &root,
                                   const Distribution   &dist,
                                   const boost::mpi::communicator &comm) {

  std::vector<std::shared_ptr<boost::mpi::packed_oarchive>> send_comm_buffers(comm.size());
  for (std::shared_ptr<boost::mpi::packed_oarchive> &i : send_comm_buffers) 
    i.reset(new boost::mpi::packed_oarchive(comm));

  std::vector<boost::mpi::request> send_requests(send_comm_buffers.size());

  boost::mpi::packed_iarchive recv_comm_buffer(comm);
  boost::mpi::request recv_request = comm.irecv(0, 0, recv_comm_buffer);

  if (!comm.rank()) {
    std::string mesh_file = root+".con";
    std::ifstream in(mesh_file);
    if (!in) throw std::logic_error(" 50 -- Error opening Mesh file.");

    std::string flush; 
    getline(in,flush); 
    getline(in,flush); 
    Connect C;
    std::vector<std::vector<Connect>> send_connect(comm.size());
    while (true) {
      in >> flush;
      if (!in) break;
      for (unsigned i=0; i<4; ++i) in >> C[i];
      const UInt owner0 = dist.owner(C[0]);
      const UInt owner1 = dist.owner(C[2]);
      send_connect[owner0].push_back(C);
      if (owner1 != owner0) send_connect[owner1].push_back(C);
      getline(in,flush); 
    } 
    for (UInt p=0; p<send_connect.size(); ++p) {
      *send_comm_buffers[p] << send_connect[p];
      send_requests[p] = comm.isend(p, 0 , *send_comm_buffers[p]);
    }
  }
  boost::mpi::wait_all(&recv_request, &recv_request+1);
  recv_comm_buffer >> connections;

  if (!comm.rank()) {
    boost::mpi::wait_all(send_requests.begin(), send_requests.end());
  }
}

void read_refinement_file(std::map<UInt, Refine> &refinements,
                           const std::string      &root,
                           const Distribution     &dist,
                           const boost::mpi::communicator &comm) {

  std::vector<std::shared_ptr<boost::mpi::packed_oarchive>> send_comm_buffers(comm.size());
  for (std::shared_ptr<boost::mpi::packed_oarchive> &i : send_comm_buffers) 
    i.reset(new boost::mpi::packed_oarchive(comm));

  std::vector<boost::mpi::request> send_requests(send_comm_buffers.size());

  boost::mpi::packed_iarchive recv_comm_buffer(comm);
  boost::mpi::request recv_request = comm.irecv(0, 0, recv_comm_buffer);

  std::vector<std::vector<std::array<UInt,3>>> send_refine(comm.size());
  if (!comm.rank()) {
    std::string mesh_file = root+".rfn";
    std::ifstream in(mesh_file);
    if (!in) throw std::logic_error(" 60 -- Error opening Refinement file.");

    std::string flush; 
    getline(in,flush); 
    std::array<UInt,3> R;
    while (true) {
      for (unsigned i=0; i<3; ++i) in >> R[i];
      if (!in) break;
      ++R[1]; ++R[2];
      const UInt owner = dist.owner(R[0]);
      send_refine[owner].push_back(R);
      getline(in,flush); 
    }
    for (UInt p=0; p<send_refine.size(); ++p) {
      *send_comm_buffers[p] << send_refine[p];
      send_requests[p] = comm.isend(p, 0 , *send_comm_buffers[p]);
    }
  }

  boost::mpi::wait_all(&recv_request, &recv_request+1);
  std::vector<std::array<UInt,3>> refine_data;
  recv_comm_buffer >> refine_data;

  UInt gid;
  Refine R;
  std::map<UInt,Refine>::const_iterator hint=refinements.begin();
  for (const std::array<UInt,3> &ref : refine_data){
    gid = ref[0]; R[0] = ref[1]; R[1] = ref[2];
    hint = refinements.insert(hint,std::pair<UInt,Refine>(gid,R));
  }

  if (!comm.rank()) {
    boost::mpi::wait_all(send_requests.begin(), send_requests.end());
  }
}

void write_ascii_mesh_file(const std::vector<Element> &elements,
                           const std::string          &root,
                           const Distribution         &dist,
                           const boost::mpi::communicator &comm) {

  std::vector<std::shared_ptr<boost::mpi::packed_iarchive>> recv_buffers(comm.size());
  for (std::shared_ptr<boost::mpi::packed_iarchive> &i : recv_buffers) 
    i.reset(new boost::mpi::packed_iarchive(comm));
  std::vector<boost::mpi::request> recv_requests(recv_buffers.size());

  if (!comm.rank()) {
    for (UInt p=0; p<comm.size(); ++p)
      recv_requests[p] = comm.irecv(p, 0, *recv_buffers[p]);
  }

  std::vector<Element> owned_elements;
  for (const Element &e : elements) 
    if (dist.owned(e.gid)) owned_elements.push_back(e);
  boost::mpi::packed_oarchive send_buffer(comm);
  send_buffer << owned_elements;
  boost::mpi::request send_request = comm.isend(0, 0, send_buffer);

  if (!comm.rank()) {
    const std::string mesh_file = root+"_ref.msh";
    std::ofstream out(mesh_file);
    if (!out) throw std::logic_error(" 70 -- Error opening Mesh file.");
    out << "**MESH DATA**" <<"\n" 
        << dist.nelem() << " " << 2 << " NE NSD"<<"\n";
    for (UInt p=0; p < comm.size(); ++p) {
      boost::mpi::wait_all(&recv_requests[p], &recv_requests[p]+1);
      std::vector<Element> recv_elements;
      *recv_buffers[p] >> recv_elements;
      for (const Element &e : recv_elements) {
        const std::string t =
          e.type==Element::QUAD ? "QUAD" : "SPECTRALQUAD";
        out.precision(0);
        out<<std::fixed;
        out << "ELEMENT "<<std::setw(3)<<e.gid<<" "<<t<<"\n";
        out.precision(15);
        out<<std::scientific;
        for (unsigned i=0; i<4; ++i) out<<" "<<std::setw(22)<<e.nodes[i].X;
        out <<"\n";
        for (unsigned i=0; i<4; ++i) out<<" "<<std::setw(22)<<e.nodes[i].Y;
        out <<"\n";
      }
    }
  }
  boost::mpi::wait_all(&send_request, &send_request+1);
}

std::string form_header(const std::string  &mesh_file, 
                        const Distribution &dist) { 
  std::time_t rawtime;
  std::time (&rawtime);
  boost::property_tree::ptree pt;
  pt.put("Date", std::ctime(&rawtime));
  pt.put("Name", mesh_file);
  pt.put("Nel", dist.nelem());
  pt.put("Nsd", 2);
  pt.put("Types.ByteOrder",  "LittleEndian");
  pt.put("Types.GlobalSize", "int32");
  pt.put("Types.LocalSize",  "int32");
  pt.put("Types.Scalar",     "float64");
  pt.put("Version", 1.0);
  std::ostringstream ostr;
  boost::property_tree::json_parser::write_json(ostr, pt, true);
  const std::string header = ostr.str(); 
  return header;
}

void determine_side_gids(std::map<Connect,UInt> &side_gids,
                         const std::vector<Connect> &connections,
                         const Distribution         &dist, 
                         const boost::mpi::communicator &comm) {

  UInt cur_gid = 0;
  for (const Connect &C : connections) {
    const UInt min = dist.owner(std::min(C[0],C[2]));
    const UInt max = dist.owner(std::max(C[0],C[2]));

    if (min == comm.rank() && comm.rank() <= max) { 
      // I will write the connection data because I own it and
      // I will set the gid for the side for the higher rank processor.
      if (!side_gids.count(C)) {
        side_gids[C] = cur_gid;
        const Connect T = {C[2], C[3], C[0], C[1]};
        side_gids[T] = cur_gid;
        ++cur_gid;
      }
    }
  }
  const UInt my_first_gid =
     boost::mpi::scan(comm, cur_gid, std::plus<UInt>()) - cur_gid;

  for (std::pair<const Connect,UInt> &G : side_gids) G.second += my_first_gid;

  std::set<UInt> send_to;
  std::set<UInt> recv_fr;
  for (const Connect &C : connections) {
    const UInt min = dist.owner(std::min(C[0],C[2]));
    const UInt max = dist.owner(std::max(C[0],C[2]));
    if (min == comm.rank() && comm.rank() < max) send_to.insert(max);
    if (max == comm.rank() && min < comm.rank()) recv_fr.insert(min);
  } 

  std::map<UInt,std::shared_ptr<boost::mpi::packed_oarchive>> send_buf;
  std::map<UInt,std::shared_ptr<boost::mpi::packed_iarchive>> recv_buf;
  for (UInt i : send_to) send_buf[i].reset(new boost::mpi::packed_oarchive(comm));
  for (UInt i : recv_fr) recv_buf[i].reset(new boost::mpi::packed_iarchive(comm));

  std::vector<boost::mpi::request> recv_requests;
  for (const auto &buf : recv_buf)
    recv_requests.push_back(comm.irecv(buf.first, 0 , *buf.second));

  std::map<UInt,std::vector<std::pair<Connect,UInt>>> send_gids; 
  for (const std::pair<Connect,UInt> &G : side_gids) {
    const UInt min = dist.owner(std::min(G.first[0],G.first[2]));
    const UInt max = dist.owner(std::max(G.first[0],G.first[2]));
    if (min == comm.rank() && comm.rank() < max) 
      send_gids[max].push_back(G);
  } 
  for (UInt i : send_to) *send_buf[i] << send_gids[i];
  std::vector<boost::mpi::request> send_requests;
  for (const auto &buf : send_buf)
    send_requests.push_back(comm.isend(buf.first, 0 , *buf.second));

  boost::mpi::wait_all(recv_requests.begin(), recv_requests.end());
  for (auto &buf : recv_buf) {
    std::vector<std::pair<Connect,UInt>> recv_data;
    *buf.second >> recv_data;
    for (const std::pair<Connect,UInt> &G : recv_data) {
      side_gids.insert(G);
      const Connect T = {G.first[2],G.first[3],G.first[0],G.first[1]};
      side_gids[T] = G.second;
    }
  }
  boost::mpi::wait_all(send_requests.begin(), send_requests.end());
}

void write_binary_mesh_connectivity(const std::vector<Connect> &connections,
                                    const std::string          &root,
                                    const Distribution         &dist, 
                                    const boost::mpi::communicator &comm) {
  const std::string mesh_file = root+"_ref.cn";
  if (!comm.rank()) {
    {
      const std::string header = form_header(mesh_file, dist);
      std::ofstream out(mesh_file);
      out << header; 
      out.close();
    }
  }
  comm.barrier(); // make sure output file is closed.

  MPI_File fh;
  MPI_Status status;
  MPI_Offset offset;
  MPI_Comm mpi_comm = comm;
  {
    char *fname = const_cast<char*>(mesh_file.c_str());
    MPI_File_open(mpi_comm, fname, 
                  MPI_MODE_APPEND | MPI_MODE_WRONLY, 
                  MPI_INFO_NULL, &fh);
  }

  std::vector<int> L(dist.num_owned(),0);
  std::vector<int> D(dist.num_owned(),0);
  for (const Connect &C : connections) 
    if (dist.owned(C[0])) L[C[0]-dist.begin()] += 1;
  for (UInt i=1; i<L.size(); ++i) 
    D[i] = D[i-1] + L[i-1];

  const int my_disp = D.back()+L.back();
  const int begin =
     boost::mpi::scan(comm, my_disp, std::plus<int>()) - my_disp;
  for (int &d : D) d += begin;

  MPI_File_get_position(fh, &offset);

  MPI_File_seek (fh, dist.begin()*sizeof(int), MPI_SEEK_CUR);
  MPI_File_write_all(fh, D.data(), D.size(), MPI_INT, &status);
  offset += dist.nelem()*sizeof(int);
  MPI_File_seek (fh, offset, MPI_SEEK_SET);

  MPI_File_seek (fh, dist.begin()*sizeof(int), MPI_SEEK_CUR);
  MPI_File_write_all(fh, L.data(), L.size(), MPI_INT, &status);
  offset += dist.nelem()*sizeof(int);
  MPI_File_seek (fh, offset, MPI_SEEK_SET);

  std::map<Connect,UInt> side_gids;
  determine_side_gids(side_gids, connections, dist, comm);

  std::vector<std::array<int,5>> to_file;
  for (const Connect &C : connections) {
    if (dist.owned(C[0])) {
      if (!side_gids.count(C)) 
        throw std::logic_error(" 45 -- Error in connectivity.");
      std::array<int,5> T;
      for (UInt i=0; i<4; ++i) T[i] = C[i];
      T[4] = side_gids[C];
      to_file.push_back(T);
    }
  }
  const int disp_offset =
     boost::mpi::scan(comm, to_file.size(), std::plus<UInt>()) - to_file.size();

  MPI_File_seek (fh, 5*disp_offset*sizeof(int), MPI_SEEK_CUR);
  MPI_File_write_all(fh, to_file.data(), 5*to_file.size(), MPI_INT, &status);

  MPI_File_close(&fh);
}

void write_binary_mesh_file(const std::vector<Element> &elements,
                            const std::string          &root,
                            const Distribution         &dist,
                            const boost::mpi::communicator &comm) {
{
  const std::string mesh_file = root+"_ref.grd";
  if (!comm.rank()) {
    {
      const std::string header = form_header(mesh_file, dist);
      std::ofstream out(mesh_file);
      out << header; 
      out.close();
    }
    {
      const int quad         = 1;
      const int spectralquad = 13;
      const int dim          = 2;
      const int nelem        = dist.nelem();
      const int ncoord       = 4*nelem;
      std::ofstream out(mesh_file, 
                        std::ios::out | std::ios::app | std::ios::binary);
      out.write(reinterpret_cast<const char*>(&nelem),  sizeof(int));
      out.write(reinterpret_cast<const char*>(&dim),    sizeof(int));
      out.write(reinterpret_cast<const char*>(&ncoord), sizeof(int));

      const int type = (elements[0].type == Element::QUAD) ? quad : spectralquad;
      for (UInt i=0; i<nelem; ++i) 
        out.write(reinterpret_cast<const char*>(&type), sizeof(int));

      int disp = 0;
      for (UInt i=0; i<nelem; ++i, disp+=4) 
        out.write(reinterpret_cast<const char*>(&disp), sizeof(int));
      out.close();
    }
  }
  comm.barrier(); // make sure output file is closed.

  MPI_File fh;
  MPI_Status status;
  MPI_Offset offset;
  MPI_Comm mpi_comm = comm;
  {
    char *fname = const_cast<char*>(mesh_file.c_str());
    MPI_File_open(mpi_comm, fname, 
                  MPI_MODE_APPEND | MPI_MODE_WRONLY, 
                  MPI_INFO_NULL, &fh);
  }
  std::vector<double> C(4*dist.num_owned());
  for (UInt i=0,k=0; i<elements.size(); ++i) 
    for (UInt j=0; j<4; ++j,++k) 
      if (dist.owned(elements[i].gid))
        C[k] = elements[i].nodes[j].X;

  MPI_File_get_position(fh, &offset);

  MPI_File_seek (fh, 4*dist.begin()*sizeof(double), MPI_SEEK_CUR);
  MPI_File_write_all(fh, C.data(), C.size(), MPI_DOUBLE, &status);
  offset += 4*dist.nelem()*sizeof(double);
  MPI_File_seek (fh, offset, MPI_SEEK_SET);

  for (UInt i=0,k=0; i<elements.size(); ++i) 
    for (UInt j=0; j<4; ++j,++k) 
      if (dist.owned(elements[i].gid))
        C[k] = elements[i].nodes[j].Y;
  MPI_File_seek (fh, 4*dist.begin()*sizeof(double), MPI_SEEK_CUR);
  MPI_File_write_all(fh, C.data(), C.size(), MPI_DOUBLE, &status);

  MPI_File_close(&fh);
}

}


void write_ascii_mesh_connectivity(const std::vector<Connect> &connections,
                                   const std::string          &root,
                                   const Distribution         &dist, 
                                   const boost::mpi::communicator &comm) {
  std::vector<std::shared_ptr<boost::mpi::packed_iarchive>> recv_buffers(comm.size());
  for (std::shared_ptr<boost::mpi::packed_iarchive> &i : recv_buffers) 
    i.reset(new boost::mpi::packed_iarchive(comm));
  std::vector<boost::mpi::request> recv_requests(recv_buffers.size());

  if (!comm.rank()) {
    for (UInt p=0; p<comm.size(); ++p)
      recv_requests[p] = comm.irecv(p, 0, *recv_buffers[p]);
  }

  std::vector<Connect> owned_connections;
  for (const Connect &c : connections) 
    if (dist.owned(c[0])) owned_connections.push_back(c);
  boost::mpi::packed_oarchive send_buffer(comm);
  send_buffer << owned_connections;
  boost::mpi::request send_request = comm.isend(0, 0 , send_buffer);

  if (!comm.rank()) {
    std::string mesh_file = root+"_ref.con";
    std::ofstream out(mesh_file);
    if (!out) throw std::logic_error(" 80 -- Error opening Mesh file.");
    out << "**CONNECTIVITY DATA**" << "\n" << dist.nelem() << " ne"<<"\n";
    for (UInt p=0; p < comm.size(); ++p) {
      boost::mpi::wait_all(&recv_requests[p], &recv_requests[p]+1);
      std::vector<Connect> recv_connections;
      *recv_buffers[p] >> recv_connections;
      for (const Connect &c : recv_connections) {
        out << "E";
        for (unsigned i=0; i<4; ++i) out <<" "<<std::setw(7)<< c[i];
        out <<"\n";
      }
    } 
  }
  boost::mpi::wait_all(&send_request, &send_request+1);
}

std::pair<UInt,UInt> determine_new_gids(const std::vector<Element>     &elements,
                                        const std::map<UInt,Refine>    &refinements,  
                                        const boost::mpi::communicator &comm) {
  UInt num_elem=0;
  const std::map<UInt,Refine>::const_iterator end=refinements.end();
  std::map<UInt,Refine>::const_iterator ref;
  for (const Element &e : elements) {
    if ( (ref = refinements.find(e.gid)) == end) {
      ++num_elem;
    } else {
      const Refine &r = ref->second;
      num_elem += r[0]*r[1];
    }
  }
  const UInt first_gid = 
    boost::mpi::scan(comm, num_elem, std::plus<UInt>()) - num_elem; 

  return std::pair<UInt,UInt>(first_gid, num_elem);
}


template <int i> inline Real phi     (const Real x); 
template      <> inline Real phi <-1>(const Real x) {return   .5*(1-x);}
template      <> inline Real phi < 1>(const Real x) {return   .5*(1+x);}

template <int i, int j> inline Real
   Phi(const Real s, const Real t) {
      return phi<i>(s) * phi<j>(t);
}

std::array<Real, 4> PHI(const std::array<Real,2> &S) {
  std::array<Real, 4> N;
  const Real s=S[0], t=S[1];
  N[0] = Phi<-1,-1>(s,t);
  N[1] = Phi< 1,-1>(s,t);
  N[2] = Phi< 1, 1>(s,t);
  N[3] = Phi<-1, 1>(s,t);
  return N;
}

inline Point AtB(const std::array<Point,4> &A,
                 const std::array<Real, 4> &B) {
  Point P;
  for (UInt k=0; k<4; ++k) {
    P.X  += A[k].X * B[k];
    P.Y  += A[k].Y * B[k];
  }
  return P;

}

std::array<Point,4> elem_nodes(const std::array<Point,4> &C, 
                               const std::array<UInt, 2> &k, 
                               const Refine              &m) {
  std::array<Point,4> y;
  for (unsigned n=0; n<4; ++n) {
    std::array<Real,2> q;
    std::array<UInt,2> i = k;
    if (1==n || 2==n) ++i[0];
    if (2==n || 3==n) ++i[1];
    q[0] = ((2.*i[0])/m[0]) - 1;
    q[1] = ((2.*i[1])/m[1]) - 1;
    const std::array<Real,4> N(::PHI(q));
    const Point P(::AtB(C, N));
    y[n] = P;
  }
  return y;
}

void push_connectivity(std::vector<Connect> &connections,
                       const EleSide &fh,
                       const EleSide &th) {
  const Connect C = {fh.first, fh.second, th.first, th.second};
  connections.push_back(C);
  const Connect R = {th.first, th.second, fh.first, fh.second}; 
  connections.push_back(R);
}

std::vector<Element> refine_element(UInt &cur_gid,
                                    std::map<EleSide,std::vector<EleSide>> &old_to_new_map,
                                    std::vector<Connect>                   &new_connections,
                                    const Element &old_ele, 
                                    const Refine  &ref) {
  std::vector<Element> new_elems;

  const std::array<Point,4> &nodes = old_ele.nodes;
  const Element::TYPE t = old_ele.type;

  std::vector<std::vector<Element>> grid(ref[0],std::vector<Element>(ref[1]));

  std::array<UInt,2> i;
  for (i[0]=0; i[0]<ref[0]; ++i[0]) {
    for (i[1]=0; i[1]<ref[1]; ++i[1]) {
      const std::array<Point,4> new_nodes = elem_nodes(nodes, i, ref);
      const Element e(t, cur_gid, new_nodes);
      new_elems.push_back(e);
      grid[i[0]][i[1]] = e;
      ++cur_gid;
    }
  }
  EleSide F,T;
  const EleSide Old[4]={EleSide(old_ele.gid,0),
                        EleSide(old_ele.gid,1),
                        EleSide(old_ele.gid,2),
                        EleSide(old_ele.gid,3)};
  for (UInt i=0; i<ref[0]; ++i) {
    for (UInt j=0; j<ref[1]; ++j) {
      for (int s = 0; s<4; ++s) {
        if ((s == 0 && j == 0) ||
            (s == 1 && i == ref[0]-1) ||
            (s == 2 && j == ref[1]-1) ||        
            (s == 3 && i == 0)) {
          const EleSide new_ele_side(grid[i][j].gid, s);
          old_to_new_map[Old[s]].push_back(new_ele_side);
        }
      }
      F.first = grid[i][j].gid;
      if (1<j) {
        T.first = grid[i][j-1].gid; 
        F.second = 0;
        T.second = 2;
        push_connectivity(new_connections, F, T);
      }
      if (i<ref[0]-1) {
        T.first = grid[i+1][j].gid; 
        F.second = 1;
        T.second = 3;
        push_connectivity(new_connections, F, T);
      }
      if (j<ref[1]-1) {
        T.first = grid[i][j+1].gid; 
        F.second = 2;
        T.second = 0;
        push_connectivity(new_connections, F, T);
      }
      if (1<i) {
        T.first = grid[i-1][j].gid; 
        F.second = 3;
        T.second = 1;
        push_connectivity(new_connections, F, T);
      }
    }
  }
  return new_elems;
}


void refine_mesh(std::map<EleSide,std::vector<EleSide>>   &old_to_new_map,
                       std::vector<Element>  &new_elements,
                       std::vector<Connect>  &new_connections,
                 const std::vector<Element>  &old_elements,
                 const std::map<UInt,Refine> &refinements,
                 const UInt                  first_gid) {
  UInt cur_gid = first_gid;

  old_to_new_map.clear();

  const std::map<UInt,Refine>::const_iterator end=refinements.end();
  std::map<UInt,Refine>::const_iterator ref;

  for (const Element &old_ele : old_elements) {
    if ( (ref = refinements.find(old_ele.gid)) == end) {
      const Element new_ele(old_ele.type, cur_gid, old_ele.nodes);
      new_elements.push_back(new_ele);
      for (UInt i=0; i<4; ++i) {
        const EleSide old_ele_side(old_ele.gid,i);
        const EleSide new_ele_side(    cur_gid,i);
        old_to_new_map[old_ele_side].push_back(new_ele_side);
      }
      ++cur_gid;
    } else {
      const std::vector<Element> new_elems = 
        refine_element(cur_gid, old_to_new_map, new_connections, old_ele, ref->second);
      new_elements.insert(new_elements.end(), new_elems.begin(), new_elems.end());
    }
  }
}



std::map<EleSide,std::vector<EleSide>> parse(const std::vector<Connect> &connections){
  std::map<EleSide,std::vector<EleSide>> con;
  for (const Connect &c : connections) {
    const EleSide f(c[0], c[1]);
    const EleSide t(c[2], c[3]);
    con[f].push_back(t);
  }
  for (auto c = con.begin(); c != con.end(); ) {
    if (1 == c->second.size()  &&
        con.count(c->second.front()))  
       c = con.erase(c);
    else {
      for (const EleSide &t : c->second) con.erase(t);
      ++c;
    }
  }
  return con;
}

std::vector<std::pair<Point,Point>> get_endpoints(const std::vector<EleSide>   &ess,
                                                  const std::map<UInt,Element> &elem) {
  std::vector<std::pair<Point,Point>> end_points;
  for (const EleSide &es : ess) {
    const UInt gid = es.first;
    const UInt sid = es.second;
    if (!elem.count(gid)) throw std::logic_error(" 90 -- Element not found.");
    if (3<sid)            throw std::logic_error(" 100 -- Side number invalid.");
    const Element &e = elem.find(gid)->second;
    std::pair<Point,Point> Ps = e.end_points(sid);
    end_points.push_back(Ps); 
  }
  return end_points;
}


bool subset (const std::pair<Point,Point> &f, 
             const std::pair<Point,Point> &t) {
  const Point C( (f.first.X+f.second.X)/2,
                 (f.first.Y+f.second.Y)/2 );
  const Point V1(C.X -  t.first.X, C.Y -  t.first.Y);
  const Point V2(C.X - t.second.X, C.Y - t.second.Y);
  const Real dot = V1.X*V2.X + V1.Y*V2.Y;
  const bool subset = dot <= 0;
  return subset;
}
bool overlap(const std::pair<Point,Point> &f, 
             const std::pair<Point,Point> &t) {
  return subset(f,t) || subset(t,f);
}
void new_connectivity(std::vector<Connect>                           &new_connections,
                      const std::vector<Connect>                     &old_connections,
                      const std::map<EleSide,std::vector<EleSide>>   &old_to_new_map,
                      const std::vector<Element>                     &new_elements, 
                      const boost::mpi::communicator                 &comm) {
  std::map<EleSide,std::vector<EleSide>> old_con_map = parse(old_connections);
  std::map<UInt,Element> new_elem_map;
  for (const Element &e : new_elements) new_elem_map[e.gid] = e;

  for (auto &con : old_con_map) {
    const EleSide f = con.first;
    const std::vector<EleSide> t = con.second;

    if (!old_to_new_map.count(f)) {
      std::cout <<"rank:"<<comm.rank()<<" "<<__FILE__<<":"<<__LINE__
                << " Element not found in old mesh connectivity:"<<f<<std::endl  
                << " Communication erroor?"<<std::endl; 
      throw std::logic_error(" 10 -- Connections wroong.");
    }

    const std::vector<EleSide> &fs = old_to_new_map.find(f)->second;

    std::vector<EleSide> ts;
    for (const EleSide &es : t) {
      if (!old_to_new_map.count(es)) throw std::logic_error(" 20 -- Connections wroong.");
      const std::vector<EleSide> &o = old_to_new_map.find(es)->second;
      ts.insert(ts.end(), o.begin(), o.end());
    }
    if (1 == fs.size() && 1 == ts.size()) {
      push_connectivity(new_connections, fs[0], ts[0]);
    } else {
      const std::vector<std::pair<Point,Point>>
        fps = get_endpoints(fs, new_elem_map);
      const std::vector<std::pair<Point,Point>>
        tps = get_endpoints(ts, new_elem_map);
      for (unsigned i=0; i<fps.size(); ++i) {
        for (unsigned j=0; j<tps.size(); ++j) {

          const std::pair<Point,Point> &fp = fps[i];
          const std::pair<Point,Point> &tp = tps[j];
          const bool match = overlap(fp, tp);

          if (match) {
            const EleSide &fh = fs[i];
            const EleSide &th = ts[j];
            push_connectivity(new_connections, fh, th);
          }
        }
      }
    }
  }
  std::sort(new_connections.begin(), new_connections.end());
  auto last_unique = std::unique(new_connections.begin(), new_connections.end());
  new_connections.resize(std::distance(new_connections.begin(),last_unique));
}

void communicate_neighbors(      std::map<EleSide,std::vector<EleSide>> &old_to_new_map,
                                 std::vector<Element>  &elements,
                           const std::vector<Connect>  &old_connections,
                           const Distribution          &old_distribution, 
                           const boost::mpi::communicator &comm) {

  std::map<UInt,Element> new_elem;
  for (const Element &e : elements) new_elem[e.gid] = e;

  std::map<UInt, std::shared_ptr<boost::mpi::packed_oarchive>> send_buffers;
  std::map<UInt, std::shared_ptr<boost::mpi::packed_iarchive>> recv_buffers;

  std::set<UInt> ghost_procs;
  std::map<UInt,std::vector<std::pair<EleSide,std::vector<EleSide>>>> send_data_old_to_new;
  std::map<UInt,std::vector<Element>>                                 send_data_elements_to_ghost;


  std::set<std::pair<UInt,EleSide>> ghosted_to_proc;
  for (const Connect &con : old_connections) {
    if (!old_distribution.owned(con[0])) {
      if (!old_distribution.owned(con[2])) 
        throw std::logic_error(" 05 -- ownership error.");
      const EleSide owned_elem_side(con[2],con[3]);
      const UInt ghost_proc = old_distribution.owner(con[0]);  
      const std::pair<UInt,EleSide> proc_elem_side(ghost_proc, owned_elem_side);
      if (!ghosted_to_proc.count(proc_elem_side)) { 
        ghosted_to_proc.insert(proc_elem_side);
        auto old_to_new = old_to_new_map.find(owned_elem_side);
        if (old_to_new == old_to_new_map.end())
          throw std::logic_error(" 10 -- old_to_new_map wroong.");
        const std::vector<EleSide> &ele_side = old_to_new->second;
        
        ghost_procs.insert(ghost_proc);
        send_data_old_to_new[ghost_proc].push_back(*old_to_new);
        for (const EleSide es : ele_side) 
          send_data_elements_to_ghost[ghost_proc].push_back(new_elem[es.first]);
      } 
    }
  }
  for (const UInt ghost_proc : ghost_procs) {
    send_buffers[ghost_proc].reset(new boost::mpi::packed_oarchive(comm));
    recv_buffers[ghost_proc].reset(new boost::mpi::packed_iarchive(comm));
  }
  std::vector<boost::mpi::request> recv_requests;
  for (const auto &buf : recv_buffers) 
    recv_requests.push_back(comm.irecv(buf.first, 0 , *buf.second));   

  for (const UInt ghost_proc : ghost_procs) {
    const std::vector<std::pair<EleSide,std::vector<EleSide>>> 
      &old_to_new = send_data_old_to_new[ghost_proc];
    const std::vector<Element>                          
      &elements_to_ghost = send_data_elements_to_ghost[ghost_proc];
    *send_buffers[ghost_proc] << old_to_new;
    *send_buffers[ghost_proc] << elements_to_ghost;
  }

  std::vector<boost::mpi::request> send_requests;
  for (const auto &buf : send_buffers) 
    send_requests.push_back(comm.isend(buf.first, 0 , *buf.second));   

  boost::mpi::wait_all(recv_requests.begin(), recv_requests.end());
  for (auto &buf : recv_buffers) {
    std::vector<std::pair<EleSide,std::vector<EleSide>>> receive_old_to_new;
    std::vector<Element>                                 elem;
    *buf.second >> receive_old_to_new;
    *buf.second >> elem;
    for (auto old_to_new : receive_old_to_new) old_to_new_map.insert(old_to_new);
    elements.insert(elements.end(), elem.begin(), elem.end());
  } 

  boost::mpi::wait_all(send_requests.begin(), send_requests.end());
}


void sanity_checks(const std::vector<Element> &elements,
                   const std::vector<Connect> &connections,
                   const Distribution         &dist,
                   const boost::mpi::communicator &comm) {

  std::map<UInt,Element> elem_map;
  for (const Element &e : elements) elem_map[e.gid] = e;
  std::multimap<EleSide,EleSide> con_map;
  for (const Connect &c : connections) 
    con_map.insert(std::pair<EleSide,EleSide>
      (EleSide(c[0],c[1]),EleSide(c[2],c[3])));

  for (const Connect &c : connections) {
    const UInt gid0 = c[0];
    const UInt gid1 = c[2];
    const UInt sid0 = c[1];
    const UInt sid1 = c[3];
    if (dist.owned(gid0) && dist.owned(gid1)) {
      if (!elem_map.count(gid0)) throw std::logic_error(" 10 -- Mesh Insane.");
      if (!elem_map.count(gid1)) throw std::logic_error(" 20 -- Mesh Insane.");
      const Element &e0 = elem_map[gid0];
      const Element &e1 = elem_map[gid1];
      const std::pair<Point,Point> P0 = e0.end_points(sid0);
      const std::pair<Point,Point> P1 = e1.end_points(sid1);
      const bool match = overlap(P0, P1);
      if (!match) throw std::logic_error(" 30 -- Mesh Insane.");
    }
  }
  for (auto con : con_map) {
    const UInt gid0 = con.first.first;
    const UInt gid1 = con.second.first;
    if (dist.owned(gid0) && dist.owned(gid1)) {
      if (1!=con_map.count(con.first) && 1!=con_map.count(con.second))
        throw std::logic_error(" 40 -- Mesh Insane.");
      if (1==con_map.count(con.first) && 0==con_map.count(con.second))
        throw std::logic_error(" 50 -- Mesh Insane.");
    }
  }
  if (1==comm.size()) {
    Point max(std::numeric_limits<Real>::min(),std::numeric_limits<Real>::min());
    Point min(std::numeric_limits<Real>::max(),std::numeric_limits<Real>::max());
    for (const Element &e : elements) {
      for (UInt i=0; i<4; ++i) {
        max.X = std::max(max.X, e.nodes[i].X);
        max.Y = std::max(max.Y, e.nodes[i].X);
        min.X = std::min(min.X, e.nodes[i].X);
        min.Y = std::min(min.Y, e.nodes[i].X);
      }
    }
    for (const Element &e : elements) {
      for (UInt i=0; i<4; ++i) {
        if (e.nodes[i].X != max.X &&
            e.nodes[i].X != min.X &&
            e.nodes[i].Y != max.Y &&
            e.nodes[i].Y != min.Y) {      
          const EleSide elemsid(e.gid,i);
          if (0==con_map.count(elemsid))
            throw std::logic_error(" 60 -- Mesh Insane.");
        }
      }
    }
  }
  if (!comm.rank()) std::cout<<" All Sanity Checks pass.  Mesh is sane."<<std::endl;
}

bool bc_file (const std::string              &root,
              const boost::mpi::communicator &comm) {
  bool found_bc_file = false;
  if (!comm.rank()) {
    std::string bc_file = root+".bc";
    std::ifstream in(bc_file);
    if (in) {
      std::string flush; 
      getline(in,flush); 
      UInt nbc;
      in >> nbc;
      getline(in,flush); 
      if (!nbc) std::cout <<" Found bc file but number of bcs is 0"<<std::endl;
      else {
        std::cout <<" Found bc file, will attempt to update"<<std::endl;
        found_bc_file = true;
      }
    }
  }
  boost::mpi::broadcast(comm, found_bc_file, 0);
  return found_bc_file;
}
void process_bc_file(const std::string          &root,
                     const std::map<EleSide,std::vector<EleSide>> &old_to_new_map,
                     const Distribution             &dist,
                     const boost::mpi::communicator &comm) {

  std::vector<std::shared_ptr<boost::mpi::packed_oarchive>> send_buffers(comm.size());
  for (std::shared_ptr<boost::mpi::packed_oarchive> &i : send_buffers) 
    i.reset(new boost::mpi::packed_oarchive(comm));

  std::vector<boost::mpi::request> send_requests(send_buffers.size());

  boost::mpi::packed_iarchive recv_buffer(comm);
  boost::mpi::request recv_request = comm.irecv(0, 0, recv_buffer);

  if (!comm.rank()) {
    std::string bc_file = root+".bc";
    std::ifstream in(bc_file);
    std::string flush; 
    getline(in,flush); 
    UInt nbc;
    in >> nbc;
    getline(in,flush); 
    std::vector<std::vector<std::tuple<char,UInt,UInt>>> send_bcs(comm.size());
    std::tuple<char,UInt,UInt> bc;
    for (UInt i=0; i<nbc; ++i) {
      in >> std::get<0>(bc) >> std::get<1>(bc) >> std::get<2>(bc);
      if (!in) break;
      const UInt owner = dist.owner(std::get<1>(bc));
      if (comm.size() < owner) 
        throw std::logic_error(" 72 -- Internal error: element owner too large.");
      send_bcs[owner].push_back(bc);
      getline(in,flush); 
    }
    for (UInt p=0; p<send_bcs.size(); ++p) {
      *send_buffers[p] << send_bcs[p];
      send_requests[p] = comm.isend(p, 0 , *send_buffers[p]);
    }
  }

  std::vector<std::tuple<char,UInt,UInt>> bcs;
  boost::mpi::wait_all(&recv_request, &recv_request+1);
  recv_buffer >> bcs;

  if (!comm.rank()) {
    boost::mpi::wait_all(send_requests.begin(), send_requests.end());
  }

  std::vector<std::shared_ptr<boost::mpi::packed_iarchive>> recv_buffers(comm.size());
  for (std::shared_ptr<boost::mpi::packed_iarchive> &i : recv_buffers) 
    i.reset(new boost::mpi::packed_iarchive(comm));
  std::vector<boost::mpi::request> recv_requests(recv_buffers.size());

  std::vector<std::tuple<char,UInt,UInt>> new_bcs;
  for (const std::tuple<char,UInt,UInt> &bc : bcs) {
    const EleSide e(std::get<1>(bc), std::get<2>(bc));
    std::map<EleSide,std::vector<EleSide>>::const_iterator 
      new_bc = old_to_new_map.find(e);
    if (old_to_new_map.end() == new_bc)
       throw std::logic_error(" 75 -- Error determining new bc.");
    for (const EleSide &e : new_bc->second) {
      const std::tuple<char,UInt,UInt> nbc(std::get<0>(bc), e.first, e.second);
      new_bcs.push_back(nbc);
    }
  }
  UInt new_bcs_size = new_bcs.size(), bcs_size; 
  boost::mpi::reduce(comm, new_bcs_size, bcs_size, std::plus<UInt>(), 0);

  if (!comm.rank()) {
    for (UInt p=0; p<comm.size(); ++p)
      recv_requests[p] = comm.irecv(p, 0, *recv_buffers[p]);
  }

  boost::mpi::packed_oarchive send_buffer(comm);
  send_buffer << new_bcs;
  boost::mpi::request send_request = comm.isend(0, 0, send_buffer);

  if (!comm.rank()) {
    const std::string bc_file = root+"_ref.bc";
    std::ofstream out(bc_file);
    if (!out) throw std::logic_error(" 77 -- Error opening new bc file.");
    out << "** Boundary Conditions **" <<"\n" 
        << bcs_size << " nbc"<<"\n";
    for (UInt p=0; p < comm.size(); ++p) {
      boost::mpi::wait_all(&recv_requests[p], &recv_requests[p]+1);
      bcs.clear();
      *recv_buffers[p] >> bcs;
      for (const std::tuple<char,UInt,UInt> &bc : bcs) {
        out << std::get<0>(bc)<<" "
            << std::get<1>(bc)<<" "
            << std::get<2>(bc)<<"\n";
      }
    }
  }
  boost::mpi::wait_all(&send_request, &send_request+1);
}

}

int main(int argc, char *argv[]) {
  
  std::clock_t timer = clock();

  boost::mpi::environment env(argc, argv);
  boost::mpi::communicator world;

  options opt = parse_command_line(argc, argv, world);
  if (!world.rank() && opt.pause) {
    std::cout << "Press enter to continue ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
  }   
  world.barrier();

  UniformDistribution OldDistribution=determine_owned_elements(opt, world);

  if (!world.rank()) std::cout<<"Parsing input files...."<<std::endl;
  std::vector<Element> OldElements;
  std::vector<Connect> OldConnections;
  if (opt.read_binary) {
    read_binary_mesh_file(OldElements, opt.root, OldDistribution, world);
    read_binary_mesh_connectivity(OldConnections, opt.root, OldDistribution, world);
  } else {
    read_ascii_mesh_file(OldElements, opt.root, OldDistribution, world);
    read_ascii_mesh_connectivity(OldConnections, opt.root, OldDistribution, world);
  }

  std::map<UInt,Refine> Refinements;
  read_refinement_file(Refinements, opt.root, OldDistribution, world);

  std::pair<UInt,UInt> GIDs = determine_new_gids(OldElements, Refinements, world);
  const UInt FirsNewGID = GIDs.first; 
  const UInt NumNewGID  = GIDs.second; 

  std::vector<UInt> all_first_gids;
  all_gather(world, FirsNewGID, all_first_gids);
  const UInt num_elem = all_reduce(world, NumNewGID, std::plus<UInt>());
  NonUniformDistribution NewDistribution(all_first_gids, NumNewGID, num_elem, world.rank(), world.size());

  if (!world.rank()) std::cout<<"Refining mesh...."<<std::endl;
  std::map<EleSide,std::vector<EleSide>> OldToNewMap;
  std::vector<Element>                   NewElements;
  std::vector<Connect>                   NewConnections;
  refine_mesh(OldToNewMap, NewElements, NewConnections, OldElements, Refinements, FirsNewGID);

  communicate_neighbors(OldToNewMap, NewElements, OldConnections, OldDistribution, world);

  new_connectivity(NewConnections, OldConnections, OldToNewMap, NewElements, world);

  if (!world.rank()) std::cout<<"Write output files...."<<std::endl;

  if (!opt.write_binary) {
    write_ascii_mesh_connectivity(NewConnections, opt.root, NewDistribution, world);
    write_ascii_mesh_file(NewElements, opt.root, NewDistribution, world);
  }

  write_binary_mesh_connectivity(NewConnections, opt.root, NewDistribution, world);
  write_binary_mesh_file(NewElements, opt.root, NewDistribution, world);

  if (bc_file(opt.root, world))
    process_bc_file(opt.root, OldToNewMap, OldDistribution, world);
  
  if (opt.sanity_check) sanity_checks(NewElements, NewConnections, NewDistribution, world);

  timer = clock() - timer;
  if (!world.rank()) std::cout <<" Total run time in seconds: " 
                               << static_cast<double>(timer)/CLOCKS_PER_SEC << std::endl;
}


