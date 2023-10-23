/*=============================================================================
  Title:      Refine2D 

  Contact:    S. Scott Collis
              Sandia National Laboratories
              Albuquerque, NM 87175
              (505) 284-1123
              sscoll@sandia.gov

  Copyright:  (c)2016 Sandia National Laboratories
=============================================================================*/


#include <algorithm>
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

#include <boost/mpi.hpp>
#include <boost/program_options.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/array.hpp>

typedef unsigned long long UInt;
typedef long double        Real;

using Connect =  std::array<UInt,4>;
using EleSide =  std::pair<UInt,UInt>;
template <UInt N> using Refine  =  std::array<UInt,N>;
template <UInt N> using Point   =  std::array<Real,N>;


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
  const bool heal;
  const bool read_binary;
  const bool write_binary;
  const std::string root;
  options (const bool p,  
           const bool s, 
           const bool h,
           const bool rb, const bool wb, const std::string r) 
    : pause(p), sanity_check(s), heal(h), read_binary(rb), write_binary(wb), root(r){}
};

std::ostream& operator<< (std::ostream &os, const Point<3>& p) {
  os <<" X:"<<p[0]<<" Y:"<<p[1] <<" Z:"<<p[2];
  return os;
} 
std::ostream& operator<< (std::ostream &os, const Point<2>& p) {
  os <<" X:"<<p[0]<<" Y:"<<p[1];
  return os;
} 

template <UInt N> constexpr UInt N_NODE(){return 1<<N;}
template <UInt N> constexpr UInt N_SIDE(){return N==2?4:6;}
template <UInt N> constexpr UInt S_NODE(){return 1<<(N-1);}

template <UInt N>
struct Element {
  enum TYPE{QUAD, SPECTRALQUAD, HEX, SPECTRALHEX};
  enum {N_NODE = N_NODE<N>()};
  enum {N_SIDE = N_SIDE<N>()};
  enum {S_NODE = S_NODE<N>()};
  TYPE   type;
  UInt   gid; 
  std::array<Point<N>,N_NODE> nodes;

  Element(const TYPE t, const UInt g, const std::array<Point<N>,N_NODE> n) : 
     type(t), gid(g), nodes(n) {}
  Element() : type(QUAD), gid(0), nodes() {}

  std::array<Point<N>,S_NODE> side_nodes(const UInt s) const {
    const UInt S_NODE = Element<N>::S_NODE;
    std::array<Point<N>,S_NODE> Ps;
    for (UInt i=0; i<S_NODE; ++i) Ps[i] = nodes[Element<N>::side_index(s,i)];
    return Ps;
  }

  template<class Archive>
  void serialize(Archive &ar, const unsigned int){ar & type & gid & nodes;}

  static UInt side_index(const UInt s, const UInt i);
};

template<>
UInt Element<2>::side_index(const UInt s, const UInt i) {
  static const UInt v[4][S_NODE] = {{0,1},{1,2},{2,3},{3,0}};
  return v[s][i];
}

template<>
UInt Element<3>::side_index(const UInt s, const UInt i) {
  static const UInt v[6][S_NODE] = {{0,1,2,3},{0,4,5,1},{1,5,6,2},
                                    {3,2,6,7},{0,3,7,4},{4,7,6,5}};
  return v[s][i];
}

template <UInt N>
std::ostream& operator<< (std::ostream &os, const Element<N>& e) {
  os <<" Gid:"<<e.gid<<" ";
  for (UInt i=0; i<e.N_NODE; ++i) os<<e.nodes[i]<<" ";
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
BOOST_IS_MPI_DATATYPE(EleSide)
BOOST_IS_MPI_DATATYPE(Refine <2>)
BOOST_IS_MPI_DATATYPE(Refine <3>)
BOOST_IS_MPI_DATATYPE(Point  <2>)
BOOST_IS_MPI_DATATYPE(Point  <3>)
BOOST_IS_MPI_DATATYPE(Element<2>)
BOOST_IS_MPI_DATATYPE(Element<3>)
BOOST_CLASS_TRACKING(Connect, track_never)
BOOST_CLASS_TRACKING(EleSide, track_never)
BOOST_CLASS_TRACKING(Refine <2>, track_never)
BOOST_CLASS_TRACKING(Refine <3>, track_never)
BOOST_CLASS_TRACKING(Point  <2>, track_never)
BOOST_CLASS_TRACKING(Point  <3>, track_never)
BOOST_CLASS_TRACKING(Element<2>, track_never)
BOOST_CLASS_TRACKING(Element<3>, track_never)


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
    ("heal", "Attempt to fix common mesh errors.") 
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

  if (vm.count("heal") && !comm.rank())
   std::cout<<" heal flag set."<<std::endl;

  if (vm.count("read_binary") && !comm.rank())
   std::cout<<" read_binary flag set."<<std::endl;

  if (vm.count("write_binary") && !comm.rank())
   std::cout<<" write_binary flag set."<<std::endl;

  const std::string root = vm.count("root") ? vm["root"].as<std::string>() : "ref";
  options opt(vm.count("pause"), 
              vm.count("sanity_check"), 
              vm.count("heal"), 
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
      ne  = pt.get<UInt>("Nel");
    } else {
      std::string mesh_file = opt.root+".msh";
      std::ifstream in(mesh_file);
      if (!in) throw std::logic_error(" 10 -- Error opening Mesh file.");

      std::string buffer; 
      getline(in,buffer); // flush comment

      in >> ne ;
      getline(in,buffer); // flush comment
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
                  
template <UInt N>
void read_binary_mesh_file(std::vector<Element<N>> &elements,
                           const std::string    &root,
                           const Distribution   &dist,
                           const boost::mpi::communicator &comm) {

  const UInt N_NODE = Element<N>::N_NODE;

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
  
  
  typename Element<N>::TYPE elem_type;
  if (!comm.rank()) {
    std::ifstream in(mesh_file,std::ifstream::binary);
    in.seekg(header_offset);
    int type;
    in.read(reinterpret_cast<char*>(&type), sizeof(int));
    if      (N==2 && type ==  1) elem_type = Element<N>::QUAD;
    else if (N==3 && type ==  3) elem_type = Element<N>::HEX; 
    else if (N==2 && type == 12) elem_type = Element<N>::SPECTRALQUAD; 
    else if (N==3 && type == 13) elem_type = Element<N>::SPECTRALHEX; 
    else throw std::logic_error(" 22 -- Count not read element type.");
    std::string name;
    if      (type== 1) name =  "QUAD";
    else if (type== 3) name =  "HEX";
    else if (type==12) name =  "SPECTRALQUAD";
    else if (type==13) name =  "SPECTRALHEX";
    std::cout<<" Just assumeing that all elements are type:"<<name<<std::endl;
  }
  boost::mpi::broadcast(comm, elem_type, 0);

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

  std::array<std::vector<double>,N> X;
  for (UInt i=0; i<N; ++i) X[i].resize(N_NODE*num_owned);

  for (UInt i=0; i<N; ++i) {
    MPI_File_seek (fh, offset, MPI_SEEK_SET);
    MPI_File_seek (fh, N_NODE*num_first*sizeof(double), MPI_SEEK_CUR);
    MPI_File_read_all(fh, X[i].data(), X[i].size(), MPI_DOUBLE, &status);
    offset += N_NODE*nelem*sizeof(double);
  }

  MPI_File_close(&fh); 

  elements.resize(num_owned);
  for (UInt j=0; j<num_owned; ++j) {
    Element<N> &e = elements[j];
    e.type = elem_type;
    e.gid  = num_first+j;
    for (UInt k=0; k<N; ++k)
      for (UInt i=0; i<N_NODE; ++i) 
        e.nodes[i][k] = X[k][N_NODE*j+i];
  }
}

template <UInt N>
void read_ascii_mesh_file(std::vector<Element<N>> &elements,
                           const std::string    &root,
                           const Distribution   &dist,
                           const boost::mpi::communicator &comm) {

  const UInt N_NODE = Element<N>::N_NODE;

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
      typename Element<N>::TYPE prev_t;
      UInt id;
      std::array<Point<N>,N_NODE> nodes;
  
      const UInt owned_by_p = dist.num_owned(p);
      std::vector<Element<N>> send_elements(owned_by_p);  
      for (UInt l=0; l<owned_by_p; ++l,++e) {
        in >> flush >> id >> type;
        getline(in,flush);
        if (N==2 && type != "QUAD" && type != "SPECTRALQUAD")
          throw std::logic_error(" 40 -- Only quads supproted in 2d.");
        if (N==3 && type != "HEX" && type != "SPECTRALHEX")
          throw std::logic_error(" 40 -- Only hex supproted in 3d.");
        const typename Element<N>::TYPE t = (N==2) ? 
           ( type=="QUAD" ? Element<N>::QUAD : Element<N>::SPECTRALQUAD ):
           ( type=="HEX"  ? Element<N>::HEX  : Element<N>::SPECTRALHEX  );
        for (UInt k=0; k<N; ++k) {
          for (unsigned i=0; i<N_NODE; ++i) in >> nodes[i][k];
          getline(in,flush); 
        }
        send_elements[l] = Element<N>(t,e,nodes);
        if (l && t!=prev_t)
          throw std::logic_error(" 44 -- only homogenous meshes supported.");
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

template<UInt N>
void read_refinement_file(std::map<UInt, Refine<N>> &refinements,
                           const std::string      &root,
                           const Distribution     &dist,
                           const boost::mpi::communicator &comm) {

  std::vector<std::shared_ptr<boost::mpi::packed_oarchive>> send_comm_buffers(comm.size());
  for (std::shared_ptr<boost::mpi::packed_oarchive> &i : send_comm_buffers) 
    i.reset(new boost::mpi::packed_oarchive(comm));

  std::vector<boost::mpi::request> send_requests(send_comm_buffers.size());

  boost::mpi::packed_iarchive recv_comm_buffer(comm);
  boost::mpi::request recv_request = comm.irecv(0, 0, recv_comm_buffer);

  std::vector<std::vector<std::array<UInt,N+1>>> send_refine(comm.size());
  if (!comm.rank()) {
    std::string mesh_file = root+".rfn";
    std::ifstream in(mesh_file);
    if (!in) throw std::logic_error(" 60 -- Error opening Refinement file.");

    std::string flush; 
    getline(in,flush); 
    std::array<UInt,N+1> R;
    while (true) {
      for (UInt i=0; i<N+1; ++i) in >> R[i];
      if (!in) break;
      for (UInt i=1; i<N+1; ++i) ++R[i];
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
  std::vector<std::array<UInt,N+1>> refine_data;
  recv_comm_buffer >> refine_data;

  UInt gid;
  Refine<N> R;
  typename std::map<UInt,Refine<N>>::const_iterator hint=refinements.begin();
  for (const std::array<UInt,N+1> &ref : refine_data){
    gid = ref[0]; 
    for(UInt i=0; i<N; ++i) R[i] = ref[i+1];
    hint = refinements.insert(hint,std::pair<UInt,Refine<N>>(gid,R));
  }

  if (!comm.rank()) {
    boost::mpi::wait_all(send_requests.begin(), send_requests.end());
  }
}

template <UInt N>
void write_ascii_mesh_file(const std::vector<Element<N>> &elements,
                           const std::string          &root,
                           const Distribution         &dist,
                           const boost::mpi::communicator &comm) {

  const UInt N_NODE = Element<N>::N_NODE;
  std::vector<std::shared_ptr<boost::mpi::packed_iarchive>> recv_buffers(comm.size());
  for (std::shared_ptr<boost::mpi::packed_iarchive> &i : recv_buffers) 
    i.reset(new boost::mpi::packed_iarchive(comm));
  std::vector<boost::mpi::request> recv_requests(recv_buffers.size());

  if (!comm.rank()) {
    for (UInt p=0; p<comm.size(); ++p)
      recv_requests[p] = comm.irecv(p, 0, *recv_buffers[p]);
  }

  std::vector<Element<N>> owned_elements;
  for (const Element<N> &e : elements) 
    if (dist.owned(e.gid)) owned_elements.push_back(e);
  boost::mpi::packed_oarchive send_buffer(comm);
  send_buffer << owned_elements;
  boost::mpi::request send_request = comm.isend(0, 0, send_buffer);

  if (!comm.rank()) {
    const std::string mesh_file = root+"_ref.msh";
    std::ofstream out(mesh_file);
    if (!out) throw std::logic_error(" 70 -- Error opening Mesh file.");
    out << "**MESH DATA**" <<"\n" 
        << dist.nelem() << " " << N << " NE NSD"<<"\n";
    for (UInt p=0; p < comm.size(); ++p) {
      boost::mpi::wait_all(&recv_requests[p], &recv_requests[p]+1);
      std::vector<Element<N>> recv_elements;
      *recv_buffers[p] >> recv_elements;
      for (const Element<N> &e : recv_elements) {
        const std::string t = (N==2) ?
          (e.type==Element<N>::QUAD ? "QUAD" : "SPECTRALQUAD"):
          (e.type==Element<N>::HEX  ? "HEX"  : "SPECTRALHEX" );
        out.precision(0);
        out<<std::fixed;
        out << "ELEMENT "<<std::setw(3)<<e.gid<<" "<<t<<"\n";
        out.precision(15);
        out<<std::scientific;
        for (UInt k=0; k<N; ++k) {
          for (UInt i=0; i<N_NODE; ++i) out<<" "<<std::setw(22)<<e.nodes[i][k];
          out <<"\n";
        }
      }
    }
  }
  boost::mpi::wait_all(&send_request, &send_request+1);
}

template <UInt N>
std::string form_header(const std::string  &mesh_file, 
                        const Distribution &dist) { 
  std::time_t rawtime;
  std::time (&rawtime);
  boost::property_tree::ptree pt;
  pt.put("Date", std::ctime(&rawtime));
  pt.put("Name", mesh_file);
  pt.put("Nel", dist.nelem());
  pt.put("Nsd", N);
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

UInt determine_side_gids(std::map<Connect,UInt> &side_gids,
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
  return side_gids.size();
}

template <UInt N>
void write_binary_mesh_connectivity(const std::vector<Connect> &connections,
                                    const std::string          &root,
                                    const Distribution         &dist, 
                                    const boost::mpi::communicator &comm) {
  const std::string mesh_file = root+"_ref.cn";
  if (!comm.rank()) {
    {
      const std::string header = form_header<N>(mesh_file, dist);
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

template <UInt N>
void write_binary_mesh_file(const std::vector<Element<N>> &elements,
                            const std::string          &root,
                            const Distribution         &dist,
                            const boost::mpi::communicator &comm) {
{
  const UInt N_NODE = Element<N>::N_NODE;
  const std::string mesh_file = root+"_ref.grd";
  if (!comm.rank()) {
    {
      const std::string header = form_header<N>(mesh_file, dist);
      std::ofstream out(mesh_file);
      out << header; 
      out.close();
    }
    {
      const int quad         = 1;
      const int hex          = 3;
      const int spectralquad = 12;
      const int spectralhex  = 13;
      const int dim          = N;
      const int nelem        = dist.nelem();
      const int ncoord       = N_NODE*nelem;
      std::ofstream out(mesh_file, 
                        std::ios::out | std::ios::app | std::ios::binary);
      out.write(reinterpret_cast<const char*>(&nelem),  sizeof(int));
      out.write(reinterpret_cast<const char*>(&dim),    sizeof(int));
      out.write(reinterpret_cast<const char*>(&ncoord), sizeof(int));

      const int type = (N==2) ?
        ((elements[0].type == Element<N>::QUAD) ? quad : spectralquad):
        ((elements[0].type == Element<N>::HEX ) ? hex  : spectralhex );
      for (UInt i=0; i<nelem; ++i) 
        out.write(reinterpret_cast<const char*>(&type), sizeof(int));

      int disp = 0;
      for (UInt i=0; i<nelem; ++i, disp+=N_NODE) 
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

  std::vector<double> C(N_NODE*dist.num_owned());
  MPI_File_get_position(fh, &offset);


  for (UInt n=0; n<N; ++n) {
    MPI_File_seek (fh, offset, MPI_SEEK_SET);
    for (UInt i=0,k=0; i<elements.size(); ++i) 
      for (UInt j=0; j<N_NODE; ++j,++k) 
        if (dist.owned(elements[i].gid))
          C[k] = elements[i].nodes[j][n];
    MPI_File_seek (fh, N_NODE*dist.begin()*sizeof(double), MPI_SEEK_CUR);
    MPI_File_write_all(fh, C.data(), C.size(), MPI_DOUBLE, &status);
    offset += N_NODE*dist.nelem()*sizeof(double);
  }


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

template<UInt N>
std::pair<UInt,UInt> determine_new_gids(const std::vector<Element<N>>     &elements,
                                        const std::map<UInt,Refine<N>>    &refinements,  
                                        const boost::mpi::communicator &comm) {
  UInt num_elem=0;
  const typename std::map<UInt,Refine<N>>::const_iterator end=refinements.end();
  typename std::map<UInt,Refine<N>>::const_iterator ref;
  for (const Element<N> &e : elements) {
    if ( (ref = refinements.find(e.gid)) == end) {
      ++num_elem;
    } else {
      const Refine<N> &r = ref->second;
      UInt s = 1;
      for (UInt i=0; i<r.size(); ++i) s *= r[i];
      num_elem += s;
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

template <int i, int j, int k> inline Real
   Phi(const Real s, const Real t, const Real u) {
      return phi<i>(s) * phi<j>(t) * phi<k>(u);
}

template <UInt N>
std::array<Real, N_NODE<N>()> PHI(const std::array<Real,N> &S);

template<>
std::array<Real, 4> PHI<2>(const std::array<Real,2> &S) {
  std::array<Real, 4> N;
  const Real s=S[0], t=S[1];
  N[0] = Phi<-1,-1>(s,t);
  N[1] = Phi< 1,-1>(s,t);
  N[2] = Phi< 1, 1>(s,t);
  N[3] = Phi<-1, 1>(s,t);
  return N;
}

template<>
std::array<Real, 8> PHI<3>(const std::array<Real,3> &S) {
  std::array<Real, 8> N;
  const Real s=S[0], t=S[1], u=S[2];
  N[0] = Phi<-1,-1,-1>(s,t,u);
  N[1] = Phi< 1,-1,-1>(s,t,u);
  N[2] = Phi< 1, 1,-1>(s,t,u);
  N[3] = Phi<-1, 1,-1>(s,t,u);
  N[4] = Phi<-1,-1, 1>(s,t,u);
  N[5] = Phi< 1,-1, 1>(s,t,u);
  N[6] = Phi< 1, 1, 1>(s,t,u);
  N[7] = Phi<-1, 1, 1>(s,t,u);
  return N;
}


template <UInt N>
inline Point<N> AtB(const std::array<Point<N>, N_NODE<N>()> &A,
                    const std::array<Real,     N_NODE<N>()> &B) {
  Point<N> P={0};
  for (UInt k=0; k<N_NODE<N>(); ++k)  
    for (UInt i=0; i<N; ++i) 
      P[i] += A[k][i] * B[k];
  return P;

}

template <UInt N>
std::array<Point<N>,N_NODE<N>()> elem_nodes(const std::array<Point<N>,N_NODE<N>()> &C, 
                                            const std::array<UInt, N>              &k, 
                                            const Refine<N>                        &m) {
  const Real two = 2;
  const UInt NODE = N_NODE<N>();
  std::array<Point<N>,NODE> y;
  for (unsigned n=0; n<NODE; ++n) {
    std::array<Real,N> q;
    std::array<UInt,N> i = k;
    if (1==(n%4) || 2==(n%4)) ++i[0];
    if (1<(n%4))              ++i[1];
    if (3<n)                  ++i[2];
    for (UInt n=0; n<N; ++n) 
      q[n] = ((two*i[n])/m[n]) - 1;
    const std::array<Real,NODE> M(::PHI<N>(q));
    const Point<N> P(::AtB<N>(C, M));
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

template<UInt N>
std::vector<Element<N>> refine_element(UInt &cur_gid,
                                    std::map<EleSide,std::vector<EleSide>> &old_to_new_map,
                                    std::vector<Connect>                   &new_connections,
                                    const Element<N> &old_ele, 
                                    const Refine<N>  &ref);

template<>
std::vector<Element<2>> refine_element<2>(UInt &cur_gid,
                                          std::map<EleSide,std::vector<EleSide>> &old_to_new_map,
                                          std::vector<Connect>                   &new_connections,
                                          const Element<2> &old_ele, 
                                          const Refine<2>  &ref) {
  std::vector<Element<2>> new_elems;

  const std::array<Point<2>,4> &nodes = old_ele.nodes;
  const typename Element<2>::TYPE t = old_ele.type;

  std::vector<std::vector<Element<2>>> grid(ref[0],std::vector<Element<2>>(ref[1]));

  std::array<UInt,2> i;
  for (i[0]=0; i[0]<ref[0]; ++i[0]) {
    for (i[1]=0; i[1]<ref[1]; ++i[1]) {
      const std::array<Point<2>,4> new_nodes = elem_nodes<2>(nodes, i, ref);
      const Element<2> e(t, cur_gid, new_nodes);
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


template<>
std::vector<Element<3>> refine_element<3>(UInt &cur_gid,
                                          std::map<EleSide,std::vector<EleSide>> &old_to_new_map,
                                          std::vector<Connect>                   &new_connections,
                                          const Element<3> &old_ele, 
                                          const Refine<3>  &ref) {
  std::vector<Element<3>> new_elems;

  const std::array<Point<3>,8> &nodes = old_ele.nodes;
  const typename Element<3>::TYPE t = old_ele.type;

  std::vector<std::vector<std::vector<Element<3>>>> 
    grid(                                     ref[0],
         std::vector<std::vector<Element<3>>>(ref[1],
                     std::vector<Element<3>> (ref[2])));

  std::array<UInt,3> i;
  for (i[0]=0; i[0]<ref[0]; ++i[0]) {
    for (i[1]=0; i[1]<ref[1]; ++i[1]) {
       for (i[2]=0; i[2]<ref[2]; ++i[2]) {
         const std::array<Point<3>,8> new_nodes = elem_nodes<3>(nodes, i, ref);
         const Element<3> e(t, cur_gid, new_nodes);
         new_elems.push_back(e);
         grid[i[0]][i[1]][i[2]] = e;
         ++cur_gid;
       }
    }
  }
  EleSide F,T;
  const EleSide Old[6]={EleSide(old_ele.gid,0),
                        EleSide(old_ele.gid,1),
                        EleSide(old_ele.gid,2),
                        EleSide(old_ele.gid,3),
                        EleSide(old_ele.gid,4),
                        EleSide(old_ele.gid,5)};
  for (UInt i=0; i<ref[0]; ++i) {
    for (UInt j=0; j<ref[1]; ++j) {
      for (UInt k=0; k<ref[2]; ++k) {
        for (int s = 0; s<6; ++s) {
          if ((s == 0 && k == 0) ||
              (s == 1 && j == 0) ||
              (s == 2 && i == ref[0]-1) ||
              (s == 3 && j == ref[1]-1) ||        
              (s == 4 && i == 0) || 
              (s == 5 && k == ref[2]-1)) {        
            const EleSide new_ele_side(grid[i][j][k].gid, s);
            old_to_new_map[Old[s]].push_back(new_ele_side);
          }
        }
        F.first = grid[i][j][k].gid;
        if (1<k) {
          T.first = grid[i][j][k-1].gid; 
          F.second = 0;
          T.second = 5;
          push_connectivity(new_connections, F, T);
        }
        if (1<j) {
          T.first = grid[i][j-1][k].gid; 
          F.second = 1;
          T.second = 3;
          push_connectivity(new_connections, F, T);
        }
        if (i<ref[0]-1) {
          T.first = grid[i+1][j][k].gid; 
          F.second = 2;
          T.second = 4;
          push_connectivity(new_connections, F, T);
        }
        if (j<ref[1]-1) {
          T.first = grid[i][j+1][k].gid; 
          F.second = 3;
          T.second = 1;
          push_connectivity(new_connections, F, T);
        }
        if (1<i) {
          T.first = grid[i-1][j][k].gid; 
          F.second = 4;
          T.second = 2;
          push_connectivity(new_connections, F, T);
        }
        if (k<ref[2]-1) {
          T.first = grid[i][j][k+1].gid; 
          F.second = 5;
          T.second = 0;
          push_connectivity(new_connections, F, T);
        }
      }
    }
  }
  return new_elems;
}


template <UInt N>
void refine_mesh(std::map<EleSide,std::vector<EleSide>>   &old_to_new_map,
                       std::vector<Element<N>>  &new_elements,
                       std::vector<Connect>     &new_connections,
                 const std::vector<Element<N>>  &old_elements,
                 const std::map<UInt,Refine<N>> &refinements,
                 const UInt                      first_gid) {

  const UInt N_SIDE = Element<N>::N_SIDE;
  UInt cur_gid = first_gid;
  old_to_new_map.clear();

  const typename std::map<UInt,Refine<N>>::const_iterator end=refinements.end();
  typename std::map<UInt,Refine<N>>::const_iterator ref;

  for (const Element<N> &old_ele : old_elements) {
    if ( (ref = refinements.find(old_ele.gid)) == end) {
      const Element<N> new_ele(old_ele.type, cur_gid, old_ele.nodes);
      new_elements.push_back(new_ele);
      for (UInt i=0; i<N_SIDE; ++i) {
        const EleSide old_ele_side(old_ele.gid,i);
        const EleSide new_ele_side(    cur_gid,i);
        old_to_new_map[old_ele_side].push_back(new_ele_side);
      }
      ++cur_gid;
    } else {
      const std::vector<Element<N>> new_elems = 
        refine_element<N>(cur_gid, old_to_new_map, new_connections, old_ele, ref->second);
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

std::vector<std::array<Point<2>,2>> get_endpoints(const std::vector<EleSide>   &ess,
                                                        const std::map<UInt,Element<2>> &elem) {
  std::vector<std::array<Point<2>,2>> side_nodes;
  for (const EleSide &es : ess) {
    const UInt gid = es.first;
    const UInt sid = es.second;
    if (!elem.count(gid)) throw std::logic_error(" 90 -- Element not found.");
    if (3<sid)            throw std::logic_error(" 100 -- Side number invalid.");
    const Element<2> &e = elem.find(gid)->second;
    std::array<Point<2>,2> Ps = e.side_nodes(sid);
    side_nodes.push_back(Ps); 
  }
  return side_nodes;
}

std::vector<std::array<Point<3>,4>> get_endpoints(const std::vector<EleSide>   &ess,
                                                  const std::map<UInt,Element<3>> &elem) {
  std::vector<std::array<Point<3>,4>> side_nodes;
  for (const EleSide &es : ess) {
    const UInt gid = es.first;
    const UInt sid = es.second;
    if (!elem.count(gid)) throw std::logic_error(" 91 -- Element not found.");
    if (5<sid)            throw std::logic_error(" 101 -- Side number invalid.");
    const Element<3> &e = elem.find(gid)->second;
    std::array<Point<3>,4> Ps = e.side_nodes(sid);
    side_nodes.push_back(Ps); 
  }
  return side_nodes;
}



template <UInt N, UInt P>
bool subset (const std::array<Point<N>,P> &f, 
             const std::array<Point<N>,P> &t);

template<>
bool subset<2,2> (const std::array<Point<2>,2> &f, 
                  const std::array<Point<2>,2> &t) {
  
  const Point<2> C = {(f[0][0]+f[1][0])/2, (f[0][1]+f[1][1])/2};

  const Point<2> V1= {C[0] - t[0][0], C[1] - t[0][1]};
  const Point<2> V2= {C[0] - t[1][0], C[1] - t[1][1]};
  const Real dot = V1[0]*V2[0] + V1[1]*V2[1];
  const bool subset = dot <= 0;
  return subset;
}

const Point<3> cross(const Point<3> &P,
                     const Point<3> &Q) {
  const Point<3> C = 
    { (P[1]*Q[2] - P[2]*Q[1]),
     -(P[0]*Q[2] - P[2]*Q[0]),
      (P[0]*Q[1] - P[1]*Q[0])};
  return C;
}

template<>
bool subset<3,4> (const std::array<Point<3>,4> &f, 
                  const std::array<Point<3>,4> &t) {
  
  Point<3> C = {0,0,0};
  for (UInt i=0; i<3; ++i) 
    for (UInt j=0; j<4; ++j) 
      C[i] += f[j][i];
  for (UInt i=0; i<3; ++i) C[i] /= 4;

  bool subset = true;
  for (UInt i=0; i<4 && subset; ++i) {
    const Point<3> e1 = {t[(i+1)%4][0]-t[i][0], 
                         t[(i+1)%4][1]-t[i][1], 
                         t[(i+1)%4][2]-t[i][2]};
    const Point<3> e2 = {t[(i-1)%4][0]-t[i][0], 
                         t[(i-1)%4][1]-t[i][1], 
                         t[(i-1)%4][2]-t[i][2]};
    const Point<3>  c = {         C[0]-t[i][0], 
                                  C[1]-t[i][1], 
                                  C[2]-t[i][2]};
    const Point<3> V = cross(cross(e1, e2), e1);
    const Real dot = V[0]*c[0] + V[1]*c[1] + V[2]*c[2];
    subset = subset && 0 <= dot;
  }
  return subset;
}

template <UInt N, UInt P>
bool overlap(const std::array<Point<N>,P> &f, 
             const std::array<Point<N>,P> &t) {
  return subset<N,P>(f,t) || subset<N,P>(t,f);
}

template <UInt N>
void new_connectivity(std::vector<Connect>                           &new_connections,
                      const std::vector<Connect>                     &old_connections,
                      const std::map<EleSide,std::vector<EleSide>>   &old_to_new_map,
                      const std::vector<Element<N>>                  &new_elements, 
                      const boost::mpi::communicator                 &comm) {
  std::map<EleSide,std::vector<EleSide>> old_con_map = parse(old_connections);
  std::map<UInt,Element<N>> new_elem_map;
  for (const Element<N> &e : new_elements) new_elem_map[e.gid] = e;

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
      const UInt S_NODE = Element<N>::S_NODE; 
      const std::vector<std::array<Point<N>,S_NODE>>
        fps = get_endpoints(fs, new_elem_map);
      const std::vector<std::array<Point<N>,S_NODE>>
        tps = get_endpoints(ts, new_elem_map);
      for (unsigned i=0; i<fps.size(); ++i) {
        for (unsigned j=0; j<tps.size(); ++j) {

          const std::array<Point<N>,S_NODE> &fp = fps[i];
          const std::array<Point<N>,S_NODE> &tp = tps[j];
          const bool match = overlap<N,S_NODE>(fp, tp);

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

template <UInt N>
void communicate_neighbors(      std::map<EleSide,std::vector<EleSide>> &old_to_new_map,
                                 std::vector<Element<N>>  &elements,
                           const std::vector<Connect>  &old_connections,
                           const Distribution          &old_distribution, 
                           const boost::mpi::communicator &comm) {

  std::map<UInt,Element<N>> new_elem;
  for (const Element<N> &e : elements) new_elem[e.gid] = e;

  std::map<UInt, std::shared_ptr<boost::mpi::packed_oarchive>> send_buffers;
  std::map<UInt, std::shared_ptr<boost::mpi::packed_iarchive>> recv_buffers;

  std::set<UInt> ghost_procs;
  std::map<UInt,std::vector<std::pair<EleSide,std::vector<EleSide>>>> send_data_old_to_new;
  std::map<UInt,std::vector<Element<N>>>                                 send_data_elements_to_ghost;


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
    const std::vector<Element<N>>                          
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
    std::vector<Element<N>>                                 elem;
    *buf.second >> receive_old_to_new;
    *buf.second >> elem;
    for (auto old_to_new : receive_old_to_new) old_to_new_map.insert(old_to_new);
    elements.insert(elements.end(), elem.begin(), elem.end());
  } 

  boost::mpi::wait_all(send_requests.begin(), send_requests.end());
}

int to_int(const Real x) {
  const int i = 100*x;
  return i;
}

template <UInt N>
std::pair<Point<N>,Point<N>> bounding_box(const std::vector<Element<N>> &elements) {
  std::pair<Point<N>,Point<N>> bbox;
  for (UInt k=0; k<N; ++k) bbox.first [k] =  std::numeric_limits<float>::max();
  for (UInt k=0; k<N; ++k) bbox.second[k] = -std::numeric_limits<float>::max();
  for (const Element<N> &e : elements) {
    for (UInt i=0; i<e.N_NODE; ++i) {
      for (UInt k=0; k<N; ++k) {
       bbox.first [k] = std::min(bbox.first [k], e.nodes[i][k]);
       bbox.second[k] = std::max(bbox.second[k], e.nodes[i][k]);
      }
    }
  }
  return bbox;
}

template <UInt N>
bool external_side(const std::pair<Point<N>,Point<N>> &bbox, 
                   const Element<N> &e, 
                   const UInt s) {
  bool external = false;
  constexpr UInt s_node = S_NODE<N>();
  for (UInt k=0; k<N && !external; ++k) {
    Real min =  std::numeric_limits<float>::max();
    Real max = -std::numeric_limits<float>::max();
    std::array<Real,s_node> x;
    for (UInt n=0; n<s_node; ++n) x[n] = e.nodes[e.side_index(s,n)][k];
    for (UInt n=0; n<s_node; ++n) min = std::min(min,x[n]);
    for (UInt n=0; n<s_node; ++n) max = std::max(max,x[n]);

    if (min==max && min == bbox.first [k]) external = true;
    if (min==max && min == bbox.second[k]) external = true;
  }
  return external;
}

template <UInt N>
void heal(const std::vector<Element<N>>  &elements,
          std::vector<Connect>           &connections,
          const boost::mpi::communicator &comm) {

  std::multimap<EleSide,EleSide> con_map;
  for (const Connect &c : connections) 
    con_map.insert(std::pair<EleSide,EleSide>
      (EleSide(c[0],c[1]),EleSide(c[2],c[3])));

  std::vector<std::pair<UInt,UInt>> mismatch;
  if (1==comm.size()) {
    const std::pair<Point<N>,Point<N>> bbox = bounding_box<N>(elements);
    for (size_t j=0; j<elements.size(); ++j) {
      const Element<N> &e = elements[j];
      for (UInt s=0; s<e.N_SIDE; ++s) {
        if (!external_side<N>(bbox, e, s)) {      
          const EleSide elemsid(e.gid,s);
          if (0==con_map.count(elemsid)) 
            mismatch.push_back(std::pair<UInt,UInt>(j,s));        
        }
      }
    }
  } else 
    throw std::logic_error(" 200 -- Heal option only works in serial. Bummer.");
  using CtoGID = std::map<std::array<int,N>,UInt>;
  using GIDtoC = std::vector<std::array<int,N>>  ;
  using GtoS   = std::multimap<std::array<UInt,Element<N>::S_NODE>,std::pair<UInt,UInt>>;
  CtoGID coord_to_gid;
  GIDtoC gid_to_coord;
  std::vector<std::array<std::array<UInt,Element<N>::S_NODE>,Element<N>::N_SIDE>> side_to_gids;
  GtoS gids_to_side;
  side_to_gids.resize(elements.size());
  for (size_t l=0; l<elements.size(); ++l) {
    const Element<N> &e = elements[l];
    constexpr UInt s_node = S_NODE<N>();
    for (UInt s=0; s<e.N_SIDE; ++s) {
      std::array<UInt,s_node> gids_for_side;
      for (UInt n=0; n<s_node; ++n) {
        const UInt i = e.side_index(s,n);
        std::array<int,N> int_coord;
        for (UInt k=0; k<N; ++k) int_coord[k] = to_int(e.nodes[i][k]);
        const std::pair<typename CtoGID::const_iterator,bool> 
          I = coord_to_gid.insert(std::pair<std::array<int,N>,UInt>(int_coord, gid_to_coord.size()));
        gids_for_side[n] = I.first->second;
        if (I.second) gid_to_coord.push_back(int_coord);
      }
      std::sort(gids_for_side.begin(), gids_for_side.end());
      side_to_gids[l][s] = gids_for_side;
      gids_to_side.insert(std::pair<std::array<UInt,s_node>,std::pair<UInt,UInt>>(gids_for_side,std::pair<UInt,UInt>(l,s)));
    }
  }
  for (const std::pair<UInt,UInt> &m : mismatch) {
    const Element<N> &e = elements[m.first];
    constexpr UInt s_node = S_NODE<N>();
    const UInt        s = m.second;
    const std::array<UInt,s_node> gids_for_side = side_to_gids[m.first][m.second];
    const std::pair<typename GtoS::const_iterator,typename GtoS::const_iterator> 
      sides = gids_to_side.equal_range(gids_for_side);
    std::pair<UInt,UInt> f; 
    bool found = false;
    for (typename GtoS::const_iterator side = sides.first; side!=sides.second; ++side) {
      if (side->second.first != m.first && side->second.second != m.second) {
        found = true;
        f = side->second; 
      }
    }
    if (!found) throw std::logic_error(" 100 -- Mesh not healable.");
    const Connect c={m.first,m.second,f.first,f.second};
    connections.push_back(c);
  } 
}


template <UInt N>
void sanity_checks(const std::vector<Element<N>> &elements,
                   const std::vector<Connect> &connections,
                   const Distribution         &dist,
                   const boost::mpi::communicator &comm) {

  std::ostringstream ss; ss << std::endl;
  bool mesh_insane = false;
  std::map<UInt,Element<N>> elem_map;
  for (const Element<N> &e : elements) elem_map[e.gid] = e;
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
      const UInt S_NODE = Element<N>::S_NODE; 
      if (!elem_map.count(gid0)) {
        mesh_insane = true;
        ss <<" gid0:"<<gid0
           <<" gid1:"<<gid1
           <<" owned but not in element map."<<std::endl 
           <<" 10 -- Mesh Insane."<<std::endl;
      }
      if (!elem_map.count(gid1)) {
        mesh_insane = true;
        ss <<" gid0:"<<gid0
           <<" gid1:"<<gid1
           <<" owned but not in element map."<<std::endl 
           <<" 20 -- Mesh Insane."<<std::endl;
      }
      const Element<N> &e0 = elem_map[gid0];
      const Element<N> &e1 = elem_map[gid1];
      const std::array<Point<N>,S_NODE> P0 = e0.side_nodes(sid0);
      const std::array<Point<N>,S_NODE> P1 = e1.side_nodes(sid1);
      const bool match = overlap<N,S_NODE>(P0, P1);
      if (!match) {
        mesh_insane = true;
        ss <<" gid0:"<<gid0
           <<" gid1:"<<gid1
           <<" P0:";
        for (int i=0; i<S_NODE; ++i) ss << P0[i] <<", ";
        ss <<" P1:";
        for (int i=0; i<S_NODE; ++i) ss << P1[i] <<", ";
        ss <<" Don't overlap when they should."<<std::endl
           <<" 30 -- Mesh Insane."<<std::endl;
      }
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
    const std::pair<Point<N>,Point<N>> bbox = bounding_box<N>(elements);
    for (const Element<N> &e : elements) {
      for (UInt s=0; s<e.N_SIDE; ++s) {
        if (!external_side<N>(bbox, e, s)) {      
          const EleSide elemsid(e.gid,s);
          if (0==con_map.count(elemsid)) {
            mesh_insane = true;
            ss<<" element:"<<e.gid
              <<" side:"<<s
              <<" is not boundary and has no neighbor."<<std::endl
              <<"   60 -- Mesh Insane" << std::endl;
          }
        }
      }
    }
  }
  if (mesh_insane)  throw std::logic_error(ss.str());
  else 
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
      if (comm.size() <= owner) 
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


template <UInt N>
void mesh_refiner(const options &opt, 
                      const boost::mpi::communicator &world) {

  UniformDistribution OldDistribution=determine_owned_elements(opt, world);

  if (!world.rank()) std::cout<<"Parsing input files...."<<std::endl;
  std::vector<Element<N>> OldElements;
  std::vector<Connect> OldConnections;
  if (opt.read_binary) {
    read_binary_mesh_file<N>(OldElements, opt.root, OldDistribution, world);
    read_binary_mesh_connectivity(OldConnections, opt.root, OldDistribution, world);
  } else {
    read_ascii_mesh_file<N>(OldElements, opt.root, OldDistribution, world);
    read_ascii_mesh_connectivity(OldConnections, opt.root, OldDistribution, world);
  }

  if (opt.heal)                  heal<N>(OldElements, OldConnections, world);

  std::map<UInt,Refine<N>> Refinements;
  read_refinement_file<N>(Refinements, opt.root, OldDistribution, world);

  std::pair<UInt,UInt> GIDs = determine_new_gids<N>(OldElements, Refinements, world);
  const UInt FirsNewGID = GIDs.first; 
  const UInt NumNewGID  = GIDs.second; 

  std::vector<UInt> all_first_gids;
  all_gather(world, FirsNewGID, all_first_gids);
  const UInt num_elem = all_reduce(world, NumNewGID, std::plus<UInt>());
  NonUniformDistribution NewDistribution(all_first_gids, NumNewGID, num_elem, world.rank(), world.size());

  if (!world.rank()) std::cout<<"Refining mesh...."<<std::endl;
  std::map<EleSide,std::vector<EleSide>> OldToNewMap;
  std::vector<Element<N>>                NewElements;
  std::vector<Connect>                   NewConnections;
  refine_mesh<N>(OldToNewMap, NewElements, NewConnections, OldElements, Refinements, FirsNewGID);

  communicate_neighbors<N>(OldToNewMap, NewElements, OldConnections, OldDistribution, world);

  new_connectivity<N>(NewConnections, OldConnections, OldToNewMap, NewElements, world);

  if (!world.rank()) std::cout<<"Write output files...."<<std::endl;

  if (!opt.write_binary) {
    write_ascii_mesh_connectivity(NewConnections, opt.root, NewDistribution, world);
    write_ascii_mesh_file<N>(NewElements, opt.root, NewDistribution, world);
  }

  write_binary_mesh_connectivity<N>(NewConnections, opt.root, NewDistribution, world);
  write_binary_mesh_file<N>(NewElements, opt.root, NewDistribution, world);

  if (bc_file(opt.root, world))
    process_bc_file(opt.root, OldToNewMap, OldDistribution, world);
  
  if (opt.sanity_check) sanity_checks<N>(NewElements, NewConnections, NewDistribution, world);
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

  UInt nsd;
  if (!world.rank()) {
    if (opt.read_binary) {
      std::string mesh_file = opt.root+".grd";
      boost::property_tree::ptree pt;
      std::istringstream istr(read_header(mesh_file));
      boost::property_tree::json_parser::read_json(istr, pt);
      nsd = pt.get<UInt>("Nsd"); 
    } else {
      std::string mesh_file = opt.root+".msh";
      std::ifstream in(mesh_file);
      if (!in) throw std::logic_error(" 10 -- Error opening Mesh file.");
      UInt ne;
      std::string buffer; 
      getline(in,buffer); // flush comment
      in >> ne >> nsd;
    }
  }
  boost::mpi::broadcast(world, nsd, 0);
  if (2==nsd) mesh_refiner<2>(opt, world);
  else        mesh_refiner<3>(opt, world);

  timer = clock() - timer;
  if (!world.rank()) std::cout <<" Total run time in seconds: " 
                               << static_cast<Real>(timer)/CLOCKS_PER_SEC << std::endl;
}


