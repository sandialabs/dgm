/** \file Zoltan.cpp
    \brief Implementation of DGM interface to Zoltan and Zoltan2
    \author K. Noel Belcourt
*/

// system includes
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <vector>
#include <sys/stat.h>
#include <unistd.h>

#ifdef DGM_PARALLEL

#ifdef DGM_USE_EPETRA

// boost includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/mpi/collectives.hpp>
#include <boost/mpi/communicator.hpp>
#include <boost/mpi/environment.hpp>
#include <boost/mpi/nonblocking.hpp>
#include <boost/serialization/map.hpp>
#include <boost/tuple/tuple.hpp>

// Zoltan includes
#include <zoltan.h>

// DGM includes
#include "AsciiFileIO.hpp"
#include "BinaryFileIO.hpp"
#include "CaseInsensitiveString.hpp"
#include "Comm.hpp"
#include "Reo.hpp"
#include "Topology.hpp"
#include "String.hpp"
#include "WeightsDatabase.hpp"
#include "Utilities.hpp"
#include "Zoltan.hpp"

using std::copy;
using std::count;
using std::distance;
using std::endl;
using std::for_each;
using std::ifstream;
using std::iterator_traits;
using std::map;
using std::max_element;
using std::min_element;
using std::ofstream;
using std::ostream;
using std::pair;
using std::string;
using std::sort;
using std::swap;
using std::vector;
using std::ws;

using boost::adjacency_list;
using boost::default_bfs_visitor;
using boost::directedS;
using boost::graph_traits;
using boost::lexical_cast;
using boost::no_property;
using boost::property;
using boost::property_map;
using boost::tie;
using boost::vecS;
using boost::vertex_rank;
using boost::vertex_rank_t;

namespace mpi = boost::mpi;

namespace Topology = DGM::Topology;
using DGM::file_exists;

namespace {
  struct use_boost {};
  struct use_zoltan {};

  // local path for more detailed output on
  // where partition file is written
  string local_path;
  // for outputg only on global p0
  int global_rank = 0;
  // stream for output
  ostream *ofp = 0;
  // number of parts, as string, root file name
  string root, part_string;
  // grd and cn are binary mesh and connectivity, resp.
  // msh and con are ascii mesh and connectivity
  // crv, cv, ord, and od are element curvature and element p order
  string grd, msh, cn, con, od, ord, cv, crv;
  string wgt_db, inp, wgt;
  int part = 1;
  bool debug = false, use_ascii = true, using_boost = false;
}

namespace DGM {

// generalize input parsing so it's not DGM specific
bool process_options(int argc, char **argv, string product, ostream& os)
{
  if (argc < 3) {
    os << "Requires two arguments, test root name an partition size" << endl;
    return false;
  }

  // set the stream for output
  ofp = &os;

  // get value of root and parallel partition size
  root = argv[1];
  // binary files
  grd = root + ".grd";
  cn = root + ".cn";
  cv = root + ".cv";
  od = root + ".od";
  // ascii files
  msh = root + ".msh";
  con = root + ".con";
  crv = root + ".crv";
  ord = root + ".ord";
  wgt = root + ".wgt";
  inp = root + ".inp";

  part_string = argv[2];
  part = lexical_cast<int>(part_string);
  if (part < 2) {
    os << "Error: parallel partition size must be greater than 1" << endl;
    return false;
  }

  // hidden option --boost to use boost hypergraph
  if (4 <= argc) {
    if (!strcmp("--boost", argv[3])) {
      // if (0 == rank) ofp << "Dumping debug output by request" << endl;
      using_boost = true;
    }
    else {
      os << "Error: unknown command line argument: " << argv[3] << endl;
      return false;
    }
  }

  // hidden option --ascii to use .msh and .con even if binary files present
  if (5 <= argc) {
    if (!strcmp("--ascii", argv[4])) {
      // if (0 == rank) ofp << "Using ascii files by request" << endl;
      use_ascii = true;
    }
    else {
      os << "Error: unknown command line argument: " << argv[4] << endl;
      return false;
    }
  }

  // hidden option --debug to dump debug output
  if (6 == argc) {
    if (!strcmp("--debug", argv[5])) {
      // if (0 == rank) ofp << "Dumping debug output by request" << endl;
      debug = true;
    }
    else {
      os << "Error: unknown command line argument: " << argv[5] << endl;
      return false;
    }
  }

#if 0
  // Declare the supported options.
  po::options_description desc("dgm_zoltan options");
  desc.add_options()
    ("help,h", "produce help message")
    ("debug,d", "Turn on debug output")
    ("root,r", po::value<string>(&root), "Test root filename")
    ("size,s", po::value<int>(&part), "Parallel partition size")
  ;

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);

  if (vm.count("h") || vm.count("help")) {
    ofp << desc << endl;
    return false;
  }

  // check if got required arguments
  if (!(vm.count("root") && vm.count("size"))) {
    // didn't get required options
    ofp << desc << endl;
    return false;
  }

  if (part < 2) {
    ofp << "Error: number of parts passed to -s must be greater than 1"
         << endl;
    ofp << "\n" << desc << endl;
    return false;
  }
  part_string = lexical_cast<string>(part);

  // check if want debug output
  if (vm.count("d") || vm.count("debug")) debug = 1;
#endif

  // get default location of weight file
  string tpl_dir = "./";
  string product_uc = DGM::upperCase(product.c_str());
  product_uc += "_HOME";
  const char *tmp = getenv(product_uc.c_str());
  if (tmp != NULL) tpl_dir = tmp;
  struct stat buf;
  string dirpath = tpl_dir.c_str();
  // check if directory exists
  int rc = stat(dirpath.c_str(), &buf);
  if (!rc && (buf.st_mode & S_IFDIR) && (buf.st_mode & S_IWUSR) ) {
  // check if performance directory exists
    dirpath += "/performance";
    rc = stat(dirpath.c_str(), &buf);
    if (!rc && (buf.st_mode & S_IFDIR) && (buf.st_mode & S_IWUSR)) {
      // check if weight file exists
      dirpath += "/";
      string product_lc = DGM::lowerCase(product.c_str());
      dirpath += product_lc.c_str();
      dirpath += "_weights.txt";
      rc = stat(dirpath.c_str(), &buf);
      if (!rc && (buf.st_mode & S_IFREG) && (buf.st_mode & S_IWUSR))
        wgt_db = dirpath;
    }
  }

  // didn't find graph weights where expected, check local directory
  if (wgt_db.empty()) {
    // check for weight database in pwd
    string product_lc = DGM::lowerCase(product.c_str());
    product_lc += "_weights.txt";
    ifstream ifp(product_lc.c_str());
    if (ifp.good() && !ifp.eof()) {
      wgt_db= product_lc;
    }
  }

  return true;
}

template <typename Size>
void get_number_space_dimensions(Size& nsd, mpi::communicator world) {
  if (!use_ascii && file_exists(grd)) {
    DGM::grd_file gf(grd, world);
    get_number_space_dimensions(nsd, gf);
  }
  else if (file_exists(msh)) {
    DGM::msh_file mf(msh, world);
    get_number_space_dimensions(nsd, mf);
  }
  else {
    using DGM::exception;
    string s("Error: missing both binary "+grd+" and ascii "+msh+" mesh files");
    throw exception(s);
  }
}

template <typename Size>
void get_global_number_elements(Size& gne, mpi::communicator world) {
  if (!use_ascii && file_exists(grd)) {
    DGM::grd_file gf(grd, world);
    get_global_number_elements(gne, gf);
  }
  else if (file_exists(msh)) {
    DGM::msh_file mf(msh, world);
    get_global_number_elements(gne, mf);
  }
  else {
    using DGM::exception;
    string s("Error: missing both binary "+grd+" and ascii "+msh+" mesh files");
    throw exception(s);
  }
}

template <typename ElemIter>
vector<Topology::ElementType> get_element_types(ElemIter g_it, ElemIter g_end
  , mpi::communicator world)
{
  vector<Topology::ElementType> et(distance(g_it, g_end));
  if (!use_ascii && file_exists(grd)) {
    if (0 == global_rank) *ofp << "Reading mesh from binary " << grd << endl;
    DGM::grd_file gf(grd, world);
    get_element_types(g_it, g_end, et.begin(), gf);
  }
  else if (file_exists(msh)) {
    if (0 == global_rank) *ofp << "Reading mesh from " << msh << endl;
    DGM::msh_file mf(msh, world);
    get_element_types(g_it, g_end, et.begin(), mf);
  }
  return et;
}

template <typename ElemIter, typename ElemTypeIter, typename Size>
vector<int> get_element_curvature(const ElemIter g_it, const ElemIter g_end,
                                  const ElemTypeIter e_it, Size gne,
                                  mpi::communicator world) {
  using DGM::Topology::num_sides;
  // construct assuming all elements are affine (is_affine true)
  vector<int> ct(distance(g_it, g_end), 1);
#if 0
  if (!use_ascii && file_exists(cv)) {
    if (0 == world.rank())
      ofp << "Reading curvature from binary " << cv << endl;
    DGM::cv_file cf(cv, world);
    // update ct with number of (potentially curved) sides for each element
    // used to compute global displacements into binary cv file
    typename vector<int>::iterator it = ct.begin();
    for (int i=0; it != ct.end(); ++it, ++i) ct[i] = num_sides(*e_it);
    // contents of ct will be replace with int (is_affine)
    get_element_curvature(g_it, g_end, gne, ct.begin(), cf);
  }
#endif
  // always read ascii curve file, update only elements listed in file
  if (file_exists(crv)) {
    if (0 == global_rank) *ofp << "Reading curvature from " << crv << endl;
    DGM::crv_file cf(crv, world);
    get_element_curvature(g_it, g_end, ct.begin(), gne, cf);
  }
  return ct;
}

template <typename ElemIter, typename Size>
vector<int> get_element_porder(ElemIter g_it, ElemIter g_end, int porder
  , Size gne, mpi::communicator world)
{
  // default porder from input file
  vector<int> po(distance(g_it, g_end), porder);
  if (!use_ascii && file_exists(od)) {
    if (0 == global_rank)
      *ofp << "Reading porder from binary " << od << endl;
    DGM::od_file of(od, world);
    read_porder(g_it, g_end, po.begin(), of);
  }
  // always read ascii order file
  if (file_exists(ord)) {
    if (0 == global_rank) *ofp << "Updating porder from " << ord << endl;
    DGM::ord_file of(ord, world);
    get_element_porder(g_it, g_end, po.begin(), gne, of);
  }
  return po;
}

template <typename ElemIter, typename Size>
vector<int> get_weights(ElemIter g_it, ElemIter g_end, int num_physics
  , Size gne, int(*physics_index)(int), mpi::communicator world)
{
  using DGM::exception;
  // get number of elements on this rank
  int ne = distance(g_it, g_end);
  // set weights to 1 by default
  vector<int> wgts(ne, 1);
  // check for weights database
  if (file_exists(wgt_db)) {
    // can't use graph weights without physics
    if (!file_exists(inp)) {
      string s("Graph weights requires " + inp + ", missing");
      throw exception(s);
    }
    // get physics and default porder from root.inp
    int physics = 0, porder = 0;
    {
      if (0 == global_rank) *ofp << "Reading input from " << inp << endl;
      DGM::inp_file inf(inp, world);
      get_physics(physics, inf);
      get_porder(porder, inf);
      if (0 == global_rank && 0 < porder)
        *ofp << "  using default porder "  << porder << endl;
    }
    // ensure good physics, convert to zero-based index
    if (physics <= 0)
      throw exception(string("Incorrect or missing eqntype in "+inp));
    physics = (*physics_index)(physics);
    // read element type
    vector<Topology::ElementType> et = get_element_types(g_it, g_end, world);
    // read curve file (1 or true means is affine, 0 or false is nonaffine)
    vector<int> of = get_element_curvature(g_it, g_end, et.begin(), gne, world);
    // read porder file(s)
    vector<int> po = get_element_porder(g_it, g_end, porder, gne, world);
    // get element names
    vector<string> enames;
    DGM::Topology::names(enames);
    // count number of unique locally owned elements types
    vector<int> net(DGM::Topology::NumElementTypes);
    for (int i=0; i<ne; ++i) ++net[et[i]];
    // now ready to get weights from database
    DGM::WeightsDatabase db(wgt_db.c_str(), num_physics, physics);
    if (0 == global_rank) *ofp << "Getting graph weights from " << wgt_db << endl;
    for (int i=0; i<ne; ++i) {
      wgts[i] = db.get_weight(et[i], of[i], po[i]);
      if (debug) {
        *ofp << "elem " << i;
        if (0 == of[i]) *ofp << " nonaffine ";
        else *ofp << " affine ";
        *ofp << enames[et[i]] << " p " << po[i] << " weight "
             << wgts[i] << endl;
      }
    }
  }
  else if (file_exists(wgt)) {
    *ofp << "Reading weights from " << wgt << endl;
    DGM::wgt_file wf(wgt, world);
    get_element_weights(g_it, g_end, wgts.begin(), wf);
  }
  else {
    // no weight file, assume all weights are equal
    if (0 == global_rank)
      *ofp << wgt << " file is missing, weights all set to 1" << endl;
  }
  // if any weights are zero, tell user
  int zw = count(wgts.begin(), wgts.end(), 0);
  if (0 < zw)
    *ofp << "Warning: " << zw << " elements have zero weight." << endl;
  // set all zero weights to 1 so Zoltan will do something
  for (int i=0; i<ne; ++i)
    if (wgts[i] <= 0) wgts[i] = 1;

  return wgts;
}

template <typename ElemIter, typename Size>
vector< pair<Size,Size> > get_connectivity(ElemIter e_it, ElemIter e_end
  , Size gne, mpi::communicator world)
{
  vector< pair<Size,Size> > conn;
  if (!use_ascii && file_exists(cn)) {
    if (0 == global_rank) *ofp << "Reading connectivity from binary " << cn << endl;
    // when ready to add dependency on Mesh.hpp, uncomment next two lines
    // typedef Mesh::Con<mySize,myOrdinal> myCon;
    // const unsigned ConSize = sizeof(myCon);
    Size cs = 5; // MyCon::size() == 5 // magic number!
    DGM::cn_file cf(cn, world);
    vector<Size> connectivity = get_connectivity(e_it, e_end, gne, cs, cf);
    // number of connectivity records for locally owned elements
    int ncon = connectivity.size() / cs;
    conn.resize(ncon);
    for (int i=0,j=0; i<ncon; ++i, j+=cs) {
      conn[i].first = connectivity[j];
      conn[i].second = connectivity[j+2];
    }
  }
  else if (file_exists(con)) {
    if (0 == global_rank) *ofp << "Reading connectivity from " << con << endl;
    // want number of space dimensions to minimize heap allocation
    Size nsd = 0;
    get_number_space_dimensions(nsd, world);
    DGM::con_file cf(con, world);
    conn = get_connectivity(e_it, e_end, gne, nsd, cf);
  }
  else {
    using DGM::exception;
    string s("Error: missing both binary " + cn
      + " and ascii " + con + " connectivity files");
    throw exception(s);
  }
  return conn;
}

template <typename WeightIter, typename ConnIter, typename Size>
int partition(WeightIter w_it, WeightIter w_end, ConnIter c_it,
              ConnIter c_end, Size gne, mpi::communicator world, use_boost);

template <typename WeightIter, typename ConnIter, typename Size>
int partition(WeightIter w_it, WeightIter w_end, ConnIter c_it,
              ConnIter c_end, Size gne, mpi::communicator world, use_zoltan);

int partition(mpi::communicator world, string product,
              DGM::physics_index get_physics_index,
              DGM::number_physics get_number_physics,
              string path)
{
  local_path = path;
  global_rank = world.rank();
  int nprocs = world.size();

  // output root and partition size
  if (0 == global_rank) {
    *ofp << "Root filename = " << root << endl;
    *ofp << "Parallel partition size = " << part << endl;
  }

  // 32 or 64 bit, keyed off this type
  typedef unsigned long Size;

  // get global number of elements
  Size gne = 0;
  get_global_number_elements(gne, world);
  if (0 == global_rank && debug) *ofp << "global number elements = " << gne << endl;

  Size num_parts = lexical_cast<Size>(part_string);
  if (gne < num_parts) {
    using DGM::exception;
    string s("Error: more partitions than elements.");
    throw exception(s);
  }

  // generate element ids owned by this rank
  vector<Size> gids = DGM::assign_global_ids(gne, nprocs, global_rank);

  // weights from either database or root.wgt file
  int num_physics = (*get_number_physics)();
  vector<int> wgts = get_weights(gids.begin(), gids.end()
    , num_physics, gne, get_physics_index, world);

  // connectivity from either binary or ascii input file (rvo into place)
  vector< pair<Size,Size> > conn = get_connectivity(gids.begin(), gids.end()
    , gne, world);

  if (debug) {
    *ofp << "rank " << global_rank << " weights : ";
    copy(wgts.begin(), wgts.end(), ostream_iterator<int>(*ofp, " "));
    *ofp << endl;

    *ofp << "rank " << global_rank << " connectivity" << endl;
    for (unsigned int i=0; i<conn.size(); ++i)
      *ofp << conn[i].first << " " << conn[i].second << endl;
  }

  // output element weight histogram
  map<int, unsigned int> wgt_count;
  vector<int> wh(wgts.begin(), wgts.end());
  sort(wh.begin(), wh.end());
  vector<int>::iterator t_it = wh.begin(), t_end = wh.end();
  while (t_it != t_end) {
    unsigned int n = count(t_it, t_end, *t_it);
    wgt_count[*t_it] = n;
    wh.erase(t_it, t_it+n);
    t_it = wh.begin();
    t_end = wh.end();
  }

  if (0 == global_rank) {
    map<int, unsigned int>::iterator m_it, m_end;
    for (int i=1; i<nprocs; ++i) {
      map<int, unsigned int> rnk;
      world.recv(i, 0, rnk);
      m_it = rnk.begin(), m_end = rnk.end();
      for (; m_it != m_end; ++m_it)
        wgt_count[(*m_it).first] += (*m_it).second;
    }
  }
  else {
    world.send(0, 0, wgt_count);
  }

  if (0 == global_rank) {
    map<int, unsigned int>::iterator m_it = wgt_count.begin()
      , m_end = wgt_count.end();
    *ofp << "Element Weight Histogram" << endl;
    *ofp << "Weights #Elements" << endl;
    for (; m_it != m_end; ++m_it)
      *ofp << "  " << (*m_it).first << "     " << (*m_it).second << endl;
  }

  if (using_boost) {
    // Boost algorithm
    if (nprocs != 1) {
      *ofp << "Error: can't use Boost if running in parallel for now" << endl;
      return -1;
    }
    return partition(wgts.begin(), wgts.end(), conn.begin(), conn.end()
      , gne, world, use_boost());
  }
  else {
    // default is to use Zoltan
    return partition(wgts.begin(), wgts.end(), conn.begin(), conn.end()
      , gne, world, use_zoltan());
  }
}

} // namespace DGM

struct c_visitor : default_bfs_visitor {
  vector<unsigned long>& e_ids;
  unsigned long i;

  // accumulate bfs traversal order of element ids
  c_visitor(vector<unsigned long>& v) : e_ids(v), i(0) {
  }

  template <typename Vertex, typename Graph>
  void discover_vertex(Vertex v, Graph&) {
    // vertex just popped, store element (vertex) id
    e_ids[i] = v;
    ++i;
  }
};

struct printing_visitor : default_bfs_visitor {
  int rank;
  printing_visitor(int r) : rank(r) {
  }
  template <typename Vertex, typename Graph>
  void discover_vertex(Vertex v, Graph&) {
  }
};

namespace boost {
  enum vertex_info_t { vertex_info = 113};
  BOOST_INSTALL_PROPERTY(vertex, info);
}
using boost::vertex_info;
using boost::vertex_info_t;

struct rank_info {
  rank_info() : weight(0) {}
  unsigned long weight;  // total computational weight on this rank
  vector<unsigned long> eids;  // elements assigned to this rank
};

bool operator<(const rank_info& r1, const rank_info& r2) {
  return r1.weight < r2.weight;
}

struct sortem {
  template <typename T>
  bool operator()(const T& s, const T& t) {
    return s.first > t.first;
  }
};

namespace DGM {

// Two pass algorithm: first achieve as uniform a load as possible
// on each rank, second minimize communication volume by minimizing
// global number of boundary cuts based on the hyperedge connectivity.
template <typename WeightIter, typename ConnIter, typename Size>
int partition(WeightIter w_it, WeightIter w_end, ConnIter c_it
  , ConnIter c_end, Size gne, mpi::communicator world, use_boost)
{
  typedef typename iterator_traits<WeightIter>::difference_type difference_type;
  typedef typename iterator_traits<WeightIter>::value_type weight_vt;
  int comm_rank = world.rank();

  // Construct two graphs, one based on mesh connectivity,
  // second is output partition graph (vertices are ranks,
  // edges are boundary cuts, each vertex has list of mesh
  // elements it owns).  Run BFS on first graph with custom
  // buffer to evenly spread load on each rank, once second
  // (rank) graph is populated, minimize communication volume
  // while improving load balance, if possible.  The minimization
  // will not significantly alter the load on each rank, but
  // will reduce overall (global) number of interdependencies
  // thereby achieving the desired minimal communication
  // volume (as measured by global number of boundary cuts).
  difference_type ne = distance(w_it, w_end);

  // output average weight per rank (if we had perfect load balance)
  unsigned long num_parts = lexical_cast<unsigned long>(part_string);
  unsigned long w_sum = accumulate(w_it, w_end, static_cast<unsigned long>(0));
  unsigned long avg_wgt = w_sum / num_parts;
  *ofp << "Avg wgt/rank = " << avg_wgt
       << " (Total wgt " << w_sum << "/ Nprocs " << num_parts << ")" << endl;

  if (0 == comm_rank) *ofp << "Setup Boost algorithm" << endl;

  // construct and populate connectivity graph
  typedef property<vertex_rank_t, unsigned long> vertex_properties;
  typedef adjacency_list<vecS, vecS, directedS, vertex_properties, no_property>
    directed_graph;
  typedef typename graph_traits<directed_graph>::vertex_descriptor Vertex;
  // typedef typename graph_traits<directed_graph>::vertex_iterator VertexIter;
  // typedef typename graph_traits<directed_graph>::out_edge_iterator EdgeIter;

  if (0 == comm_rank) *ofp << "Populating graph" << endl;

  // instantiate and populate graph using mesh connectivity
  Vertex u, v;
  directed_graph g;
  for (; c_it != c_end; ++c_it) {
    u = vertex((*c_it).first, g);
    v = vertex((*c_it).second, g);
    add_edge(u, v, g);
  }

  if (0 == comm_rank) *ofp << "Running BFS algorithm" << endl;

  // run bfs on connectivity graph to get bfs ordered element ids
  vector<unsigned long> eids(gne);  // adjacency order element ids
  c_visitor vis(eids);
  breadth_first_search(g, vertex(0, g), visitor(vis));

  property_map<directed_graph, vertex_rank_t>::type
    rank_map = get(vertex_rank, g);

  if (0 == comm_rank) *ofp << "Running assignment algorithm" << endl;

  // have bfs traversal (connectivity or adjacency) element id order
  // now assign elements to ranks based on target weight
  // and the sum of weights already on that rank by running bfs again
  // this time searching entire set of weights for optimal load balance
  unsigned long rank = 0, current = 0;
  vector<rank_info> ranks(num_parts);
  vector<unsigned long>::iterator it = eids.begin(), end = eids.end();
  for (; it != end;) {
    if (current + w_it[*it] <= avg_wgt) {
      current += w_it[*it];
      ranks[rank].weight = current;
      ranks[rank].eids.push_back(*it);
      // store assigned rank in connectivity graph
      rank_map[*it] = rank;
      ++it;
    }
    else if (avg_wgt < current + w_it[*it]) {
      // advance to next rank
      current = 0;
      ++rank;
      if (num_parts <= rank) break;
    }
  }

  // clear out assigned elements leaving only
  // those that are still unassigned
  eids.erase(eids.begin(), it);

  // check if every rank has at least one element
  // If not, use a different partitioning algorithm
  // round-robin as Jerry has suggested several times.
  vector<rank_info>::iterator r_it, r_end = ranks.end();
  for (r_it = ranks.begin(); r_it != r_end; ++r_it) {
    if (0 == (*r_it).weight || 0 == (*r_it).eids.size()) {
      if (0 == comm_rank)
        *ofp << "Checking each rank has at least one element" << endl;
      // at least one rank has no elements, we're in a
      // small number of elements assigned to each rank
      // regime, use different partitioning algorithm
      // for this case
      // sort elements by weight, largest to smallest
      typedef vector< pair<weight_vt, Size> > container;
      container weight_ids(gne);
      WeightIter lw_it = w_it;
      for (unsigned long i=0; lw_it != w_end; ++lw_it, ++i)
        weight_ids[i] = make_pair(*lw_it, i);
      sort(weight_ids.begin(), weight_ids.end(), sortem());
      // assign elements to rank in weighted order
      r_it = ranks.begin();
      for (unsigned long i=0; r_it != r_end; ++r_it, ++i) {
        (*r_it).weight = weight_ids[i].first;
        (*r_it).eids.clear();
        (*r_it).eids.push_back(weight_ids[i].second);
      }
      // erase elements we've already assigned
      weight_ids.erase(weight_ids.begin(), weight_ids.begin() + num_parts);
      // distribute remaining elements to achieve load balance
      // assign largest element weight to smallest rank
      typename container::iterator c_it = weight_ids.begin()
        , c_end = weight_ids.end();
      while (c_it != c_end) {
        // initially fill best we can (check against target avg_wgt)
        r_it = --ranks.end();
        r_end = --ranks.begin();
        while (r_it != r_end) {
          // only sum if below avg_wgt
          while (c_it != c_end && (*r_it).weight + (*c_it).first <= avg_wgt) {
            (*r_it).weight += (*c_it).first;
            (*r_it).eids.push_back((*c_it).second);
            ++c_it;
          }
          --r_it;
        }
        // check if any left
        if (c_it == c_end) break;
        // assign 1 per rank until gone
        r_it = --ranks.end();
        r_end = --ranks.begin();
        while (c_it != c_end && r_it != r_end) {
          (*r_it).weight += (*c_it).first;
          (*r_it).eids.push_back((*c_it).second);
          ++c_it;
          --r_it;
        }
      }
      // should have assigned all the remaining elements
      assert(c_it == c_end);
      // remove remaining elements as algorithm is finished
      eids.clear();
      break;
    }
  }

  // check for elements not assigned to a rank
  if (0 < eids.size()) {
    if (0 == comm_rank)
      *ofp << "Checking for unassigned elements" << endl;
    // sort the remaining elements by weight
    typedef vector< pair<weight_vt, Size> > container;
    container weight_ids(eids.size());
    WeightIter lw_it = w_it;
    for (unsigned long i=0; i<eids.size(); ++lw_it, ++i)
      weight_ids[i] = make_pair(*lw_it, eids[i]);
    sort(weight_ids.begin(), weight_ids.end(), sortem());
    // sort the ranks by weight, smallest to largest
    sort(ranks.begin(), ranks.end());
    // fill ranks with smallest computational weight
    // before those with larger total weights
    r_it = ranks.begin();
    r_end = ranks.end();
    // This is a rank agnostic algorithm, don't really
    // care what rank r_it points at, just that we
    // produce a very smooth computational load .  That's
    // why sorting the rank list by weight is acceptable.
    for (unsigned long i=0; i<eids.size(); ++i) {
      // *r_it is the rank with the smallest total weight
      // add this element and it's weight to this rank
      (*r_it).weight += weight_ids[i].first;
      (*r_it).eids.push_back(weight_ids[i].second);
      // advance to next smallest rank if current rank weight
      // is larger than next rank's weight in sorted list
      if ((*(r_it+1)).weight < (*r_it).weight) ++r_it;
      // check that we never exceed available ranks
      if (r_it == r_end) {
        // resort ranks by weight and continue element assignment
        sort(ranks.begin(), ranks.end());
        r_it = ranks.begin();
        r_end = ranks.end();
      }
    }
    eids.clear();
  }

#if 0
  if (0 == comm_rank)
    *ofp << "Setup for Hypergraph communication volume minimization" << endl;

  // construct rank graph, one vertex per rank
  // rank graph vertex properties are rank's total weight,
  // list of elements and their weights
  typedef property<vertex_rank_t, unsigned long
    , property<vertex_info_t, rank_info> > vertex_rank_properties;
  typedef adjacency_list<vecS, vecS, directedS, vertex_rank_properties
    ,  no_property> rank_graph;
  rank_graph rg;
  typedef typename graph_traits<rank_graph>::vertex_descriptor RG_vertex;
  property_map<rank_graph, vertex_rank_t>::type
    pm_vertex_rank = get(vertex_rank, rg);
  property_map<rank_graph, vertex_info_t>::type
    pm_vertex_info = get(vertex_info, rg);
  r_it = ranks.begin(), r_end = ranks.end();
  RG_vertex w;
  for (unsigned long i=0; i<num_parts; ++i) {
    // copy data into property map
    w = add_vertex(rg);
    // use vertex to get property out of graph
    pm_vertex_rank[w] = i;
    // copy rank_info for now, inefficient but it's a work in progress
    pm_vertex_info[w] = *r_it;
  }

  // add rank connectivity to other ranks
  VertexIter v_it, v_end;
  EdgeIter e_it, e_end;
  for (tie(v_it, v_end) = vertices(g); v_it != v_end; ++v_it) {
    unsigned long source_rank = rank_map[*v_it];
    for (tie(e_it, e_end) = out_edges(*v_it, g); e_it != e_end; ++e_it) {
      // add edge between ranks that exchange data
      unsigned long target_rank = rank_map[target(*e_it, g)];
      add_edge(source_rank, target_rank, rg);
    }
  }

  // minimize rank graph edges (edge reduction algorithm)
  // Identify max and min weight so algorithm never increases
  // max or decreases the minimum rank weight.  Perform bfs
  // traversal of rank graph: at each rank we examine neighbors
  // looking to move elements of the same weight from one rank
  // to another but eliminating rank connectivity in the process.
  // This algorithm achieves the hypergraph objective of minimizing
  // communication voiume while constraining changes so that the
  // computational load imbalance ratio never increases.  A simple
  // metric of the communication volume is the number of edges in
  // the rank graph, so our algorithm's objective is to minimize
  // the number of rank graph edges while not increasing the
  // imbalance ratio.

  if (0 == comm_rank)
    *ofp << "Running BFS on rank graph" << endl;

  printing_visitor pvis(comm_rank);
  breadth_first_search(rg, vertex(0, rg), visitor(pvis));

  if (0 == comm_rank)
    *ofp << "Minimizing Hypergraph communication volume" << endl;
#endif

  if (0 == comm_rank) *ofp << "Completed Boost partitioning" << endl;

  // output partition and statistics
  vector<unsigned long> part(ne);
  r_it = ranks.begin(), r_end = ranks.end();
  unsigned long min_p = 0, max_p = 0;
  double min_v = (*r_it).weight, max_v = 0;
  for (; r_it != r_end; ++r_it) {
    // assign the rank here (we've sorted ranks several times before this)
    rank = r_it - ranks.begin();
    it = (*r_it).eids.begin();
    end = (*r_it).eids.end();
    for (; it != end; ++it) {
      part[*it] = rank;
    }
    if ((*r_it).weight < min_v) {
      min_v = (*r_it).weight;
      min_p = rank;
    }
    if (max_v < (*r_it).weight) {
      max_v = (*r_it).weight;
      max_p = rank;
    }
  }

  *ofp << "Max/min compute loads " << max_v << "/" << min_v
       << " are on ranks " << max_p << "/" << min_p << endl;
  *ofp << "Ratio (max/min) = " << max_v/min_v << endl;

  // write partition
  *ofp << "Writing "
       << string(local_path + "/" + root + ".part." + lexical_cast<string>(num_parts))
       << endl;
  string part_file(string(root + ".part." + lexical_cast<string>(num_parts)).c_str());
  remove(part_file.c_str());
  ofstream parts_file(part_file.c_str());
  for (difference_type i=0; i<ne; ++i)
    parts_file << part[i] << "\n";
  parts_file.close();

  return 0;
}

template <typename WeightIter, typename ConnIter, typename Size>
int partition(WeightIter w_it, WeightIter w_end, ConnIter c_it
  , ConnIter c_end, Size gne, mpi::communicator world, use_zoltan)
{
  using DGM::exception;

  ConnIter conn_it = c_it;

  int nprocs = world.size();
  int ne = distance(w_it, w_end);
  int nhe = distance(c_it, c_end);

  if (0 == global_rank) *ofp << "Setup Zoltan data structures" << endl;

  // Zoltan
  DGM::HyperGraphData hg;
  hg.wgt_it = &*w_it;
  // hypergraph vertices 1-1 w/mesh elements
  hg.numMyVertices = ne;
  // hypergraph edges are number of shared faces, one edge for each direction
  hg.numMyHEdges = ne;
  // total number of hyperedge vertices
  hg.numAllNbors = nhe+ne;
  // global id of vertices (elements)
  hg.vtxGID = new ZOLTAN_ID_TYPE[hg.numMyVertices];
  // global id of each hyperedge, since one edge per element
  // use global element id
  hg.edgeGID = new ZOLTAN_ID_TYPE[hg.numMyVertices];
  // base of indexing is gid in first connectivity record
  for (int i=0; i<hg.numMyVertices; ++i)
    hg.edgeGID[i] = hg.vtxGID[i] = (*c_it).first + i;
  // index into nborGID array of hyperedge's vertices (elements)
  hg.nborIndex = new int[hg.numMyHEdges];
  hg.nborIndex[0] = 0;
  // Vertices of edge edgeGID[i] begin at nborGID[nborIndex[i]]
  hg.nborGID = new ZOLTAN_ID_TYPE[hg.numAllNbors];
  // basically just con array (if con array is ordered by local element id)
  hg.nborGID[0] = (*c_it).first;
  hg.nborGID[1] = (*c_it).second;
  int k=1;
  ConnIter prev = c_it;
  for (int i=1,j=2; i<nhe; ++i,++j,++c_it) {
    assert(k <= hg.numAllNbors);
    if ((*c_it).first == (*c_it).second) {
      *ofp << "Error: element " << i << " side connected to itself" << endl;
      return -2;
    }
    if ((*prev).first != (*c_it).first) {
      hg.nborIndex[k] = j;
      ++k;
      hg.nborGID[j] = (*c_it).first;
      ++j;
    }
    hg.nborGID[j] = (*c_it).second;
    prev = c_it;
  }

  struct Zoltan_Struct *zz = Zoltan_Create(world);

  // set phg parameters (no user setable parameters just yet)
  Zoltan_Set_Param(zz, "DEBUG_LEVEL", "0");
  Zoltan_Set_Param(zz, "LB_METHOD", "HYPERGRAPH");   // partitioning method
  Zoltan_Set_Param(zz, "HYPERGRAPH_PACKAGE", "PHG"); // version of method
  Zoltan_Set_Param(zz, "NUM_GID_ENTRIES", "1");   // global IDs are integers
  Zoltan_Set_Param(zz, "NUM_LID_ENTRIES", "1");   // local IDs are integers
  Zoltan_Set_Param(zz, "RETURN_LISTS", "EXPORT"); // export AND import lists
  // vertex weight is elmt wgt
  Zoltan_Set_Param(zz, "OBJ_WEIGHT_DIM", "1");  // default vertex weights
  Zoltan_Set_Param(zz, "EDGE_WEIGHT_DIM", "0"); // default hyperedge weights
  Zoltan_Set_Param(zz, "LB_APPROACH", "PARTITION");
  Zoltan_Set_Param(zz, "IMBALANCE_TOL", "1.0");
  Zoltan_Set_Param(zz, "NUM_GLOBAL_PARTS", part_string.c_str());
  Zoltan_Set_Param(zz, "PHG_REFINEMENT_QUALITY", "10.0");

  // to ensure we get same random number everytime we run.
  unsigned int idum = 123456789u;
  idum = (1664525u*idum + 1013904223u) >> 1;
  string seed = lexical_cast<string>(idum);
  Zoltan_Set_Param(zz, "Seed", seed.c_str());

  // query functions
  Zoltan_Set_Num_Obj_Fn(zz, DGM::get_number_of_vertices, &hg);
  Zoltan_Set_Obj_List_Fn(zz, DGM::get_vertex_list, &hg);
  Zoltan_Set_HG_Size_CS_Fn(zz, DGM::get_hypergraph_size, &hg);
  Zoltan_Set_HG_CS_Fn(zz, DGM::get_hypergraph, &hg);

  int changes, numGidEntries, numLidEntries, numImport, numExport;
  int *importProcs = 0, *importToPart = 0;
  int *exportProcs = 0, *exportToPart = 0;
  ZOLTAN_ID_PTR importGlobalGids = 0, importLocalGids = 0;
  ZOLTAN_ID_PTR exportGlobalGids = 0, exportLocalGids = 0;

  if (0 == global_rank) *ofp << "Begin Zoltan partitioning" << endl;

  int rc = Zoltan_LB_Partition(zz, // input (remaining fields are output)
  &changes,          // 1 if partitioning was changed, 0 otherwise
  &numGidEntries,    // Number of integers used for a global ID
  &numLidEntries,    // Number of integers used for a local ID
  &numImport,        // Number of vertices to be sent to me
  &importGlobalGids, // Global IDs of vertices to be sent to me
  &importLocalGids,  // Local IDs of vertices to be sent to me
  &importProcs,      // Process rank for source of each incoming vertex
  &importToPart,     // New partition for each incoming vertex
  &numExport,        // Number of vertices I must send to other processes
  &exportGlobalGids, // Global IDs of the vertices I must send
  &exportLocalGids,  // Local IDs of the vertices I must send
  &exportProcs,      // Process to which I send each of the vertices
  &exportToPart);    // Partition to which each vertex will belong
  if (rc != ZOLTAN_OK)
    throw exception("Zoltan failed to partition mesh");

  // partition after calling zoltan
  vector<int> parts(hg.numMyVertices, global_rank);
  for (int i=0; i<numExport; ++i) {
    parts[exportLocalGids[i]] = exportToPart[i];
  }

  if (1 < nprocs) {
    if (debug) {
      *ofp << "rank = " << global_rank << " parts: ";
      copy(parts.begin(), parts.end(), ostream_iterator<int>(*ofp, " "));
      *ofp << endl;
    }
    if (0 == global_rank)
      *ofp << "Gathering partitioned mesh to p0 for output" << endl;
    if (0 == global_rank) {
      // receive parts from non-root ranks
      // single vector of length gne to hold all parts
      vector<int> gparts(gne);
      vector<int>::iterator g_it = gparts.begin();
      // copy my data in first
      copy(parts.begin(), parts.end(), g_it);
      g_it += ne;
      // receive from each non-root rank
      int nreqs = nprocs - 1;
      std::vector<mpi::request> rreqs(nreqs);
      // number of elements on other ranks
      int rne = (gne - ne) / nreqs;
      // each non-zero rank sends same amount of data
      for (int i=1; i<nprocs; ++i, g_it+=rne)
        rreqs[i-1] = world.irecv(i, 3, &*g_it, rne);
      // wait for communication to complete
      mpi::wait_all(rreqs.begin(), rreqs.end());
      // rotate global partition into place
      swap(parts, gparts);
    }
    else {
      mpi::request sreqs[1];
      sreqs[0] = world.isend(0, 3, &parts[0], ne);
      mpi::wait_all(sreqs, sreqs+1);
    }
  }

  if (debug && 0 == global_rank) {
    *ofp << "global parts: ";
    copy(parts.begin(), parts.end(), ostream_iterator<int>(*ofp, " "));
    *ofp << endl;
  }

  // acquire / release semantics (LIFO)
  Zoltan_LB_Free_Part(&importGlobalGids, &importLocalGids
    , &importProcs, &importToPart);
  Zoltan_LB_Free_Part(&exportGlobalGids, &exportLocalGids
    , &exportProcs, &exportToPart);
  Zoltan_Destroy(&zz);
  delete [] hg.nborGID;
  delete [] hg.nborIndex;
  delete [] hg.edgeGID;
  delete [] hg.vtxGID;

  // check that each core ended up with at least one element
  bool decomp_is_good = false;
  if (0 == global_rank) {
    unsigned int nparts = lexical_cast<unsigned int>(part);
    vector<int> all_parts(parts);
    sort(all_parts.begin(), all_parts.end());
    all_parts.erase(unique(all_parts.begin(), all_parts.end()),
    		        all_parts.end());
    decomp_is_good = all_parts.size() == nparts;
    if (!decomp_is_good) {
      // Zoltan failed to produce a good decomposition
      if (nprocs != 1) {
        *ofp << "Error: can't use Boost if running in parallel for now" << endl;
        return -1;
      }
      *ofp << "Zoltan failed, partitioning using Boost algorithm" << endl;
      // rerun using new partitioning algorithm instead
      return partition(w_it, w_end, conn_it, c_end, gne, world, use_boost());
    }
  }

  if (0 == global_rank)
    *ofp << "Completed Zoltan hypergraph partitioning" << endl;

  if (1 == nprocs && decomp_is_good) {
    // only output if running serially, otherwise have to gather
    // weights to compute min/max metrics
    assert(static_cast<unsigned int>(gne) == parts.size());
    assert(static_cast<int>(gne) == distance(w_it, w_end));
    // find rank with maximum compute load
    typename vector<Size>::iterator min_it, max_it;
    int num_parts = lexical_cast<int>(part_string);
    vector<Size> rank_sum(num_parts, 0);
    int w_sum = accumulate(w_it, w_end, 0);
    for (Size i=0; i<gne; ++i)
      rank_sum[parts[i]] += w_it[i];
    *ofp << "Avg wgt/rank = " << w_sum/num_parts
        << " (Total wgt " << w_sum << "/ Nprocs " << num_parts << ")" << endl;
    min_it = min_element(rank_sum.begin(), rank_sum.end());
    max_it = max_element(rank_sum.begin(), rank_sum.end());
    *ofp << "Max/min compute loads " << *max_it << "/" << *min_it
        << " are on ranks " << min_it - rank_sum.begin()
        << "/" << max_it - rank_sum.begin() << endl;
    *ofp << "Ratio (max/min) = " << static_cast<double>(*max_it)/(*min_it)
         << endl;
  }

  // write solution if at least one element per core
  if (0 == global_rank && decomp_is_good) {
    // write decomposition to partition file (root.part.parallel_size)
    *ofp << "Writing "
      << string(local_path + "/" + root + ".part." + lexical_cast<string>(part))
      << endl;
    string part_file(string(root + ".part."
      + lexical_cast<string>(part)).c_str());
    remove(part_file.c_str());
    ofstream parts_file(part_file.c_str());
    if (!parts_file.good()) {
      *ofp << "  Failed to open part file:" << part_file << endl;
      return -1;
    }
    for (Size i=0; i<gne; ++i) {
      parts_file << parts[i] << endl;
    }
    parts_file.close();
  }

  return 0;
}

} // namespace DGM

#endif // DGM_USE_EPETRA

#endif // DGM_PARALLEL
