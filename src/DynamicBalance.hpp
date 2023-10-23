/** \file DynamicBalance.hpp
    \brief Algorithm for dynamically load balancing
    \author K. Noel Belcourt

    Algorithm for dynamically load balancing problem based
    on node allocation from the cluster scheduler. This
    implementation is Cray specific and extracted from
    prototype code from Vitus Leung.
*/

#ifndef DGM_DynamicBalance_hpp
#define DGM_DynamicBalance_hpp

// standard libraries
#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <utility>
#include <vector>

// Boost includes
#include <boost/mpi/collectives.hpp>
#include <boost/mpi/communicator.hpp>
#include <boost/mpi/environment.hpp>
#include <boost/mpi/nonblocking.hpp>

#ifdef __CRAYXE
extern "C" {
  #include <rca_lib.h>
}
#endif

// DGM libraries
#include "Point.hpp"
#include "RecursiveCoordinateBisection.hpp"

namespace DGM {

namespace {
  typedef std::pair<int, int> new_ranks_t;
  typedef std::vector<int> rank_list_t;
  rank_list_t::iterator r_it, r_end;
}

struct rca_node {
  rank_list_t ranks;  // multiple ranks share same rca node
  unsigned int nid, slot, cage, row, cabinet, link, mod_comp;
  uint32_t id;
  int x, y, z;
  // constructors
  rca_node() : id(0), x(0), y(0), z(0) {}
  rca_node(uint32_t i, int rank) : id(i)
    , x(0), y(0), z(0) {
    ranks.push_back(rank);
  }
  rca_node(const rca_node& rca) {
    if (this != &rca) {
      ranks = rca.ranks;
      id = rca.id;
      x = rca.x;
      y = rca.y;
      z = rca.z;
    }
  }
};

std::ostream& operator<<(std::ostream& os, const rca_node& r) {
  using std::copy;
  using std::ostream_iterator;
  os << "id: " << r.id << " coords: " << r.x << " " << r.y << " " << r.z
     << " ranks: ";
  copy(r.ranks.begin(), r.ranks.end(), ostream_iterator<int>(os, " "));
  return os;
}

typedef std::vector<rca_node> rca_nodes_t;

// order by rca node id
bool operator<(const rca_node& p, const rca_node& q) {
  return p.id < q.id;
}

// nrvo
template <typename Point>
rca_nodes_t rca_balance_impl(Point c, boost::mpi::communicator world)
{
  using std::accumulate;
  using std::copy;
  using std::cout;
  using std::distance;
  using std::endl;
  using std::ostream_iterator;
  using std::sort;
  using std::unique;
  using std::vector;

  namespace mpi = boost::mpi;

  // So we have something (empty) to return
  rca_nodes_t rca_nodes;
  int verb = 1;

  // Mpi
  int nprocs = world.size();
  int rank = world.rank();

  // gather coordinates by rank
  typedef vector<Point> coord_list_t;
  coord_list_t coords(nprocs);
  mpi::all_gather(world, c, coords);


#ifdef __CRAYXE
  // get node id from Cray RCA subsystem
  rs_node_t node_info;
  rca_get_nodeid(&node_info);
  unsigned int nid = node_info.rs_node_s._node_id;
  unsigned int slot = node_info.rs_node_s._node_slot;
  unsigned int cage = node_info.rs_node_s._node_cage;
  unsigned int row = node_info.rs_node_s._node_row;
  unsigned int cabinet = node_info.rs_node_s._node_x;
  unsigned int link = node_info.rs_node_s._node_link; // gemini index
  unsigned int mod_comp = node_info.rs_node_s._node_modcomp; // compute node
  // get mesh coordinates
  rca_mesh_coord_t coord;
  rca_get_meshcoord(nid, &coord);
  unsigned int x = coord.mesh_x;
  unsigned int y = coord.mesh_y;
  unsigned int z = coord.mesh_z;
  if (0 < verb) {
    cout << "rank: " << rank << " nid: " << nid
      << " name: c" << cabinet << "-" << row
      << "c" << cage << "s" << slot << "n" << mod_comp << endl;
    cout << "rank: " << rank << " nid: " << nid
      << " coord: " << x << y << z << endl;
  }

#if 0
  // gather node ids from all ranks
  typedef vector<unsigned int> node_list_t;
  node_list_t node_ids(nprocs);
  node_list_t::iterator it, end;
  mpi::all_gather(world, nid, node_ids);

  // copy off node id and rank
  rca_nodes_t::iterator n_it = rca_nodes.begin(), n_end;
  it = node_ids.begin(), end = node_ids.end();
  int my_nid = nid;
  nid = -1;
  for (int i=0; it != end; ++i, ++it) {
    if (nid != *it) {
      // advance to next rca_node
      nid = *it;
      rca_nodes.push_back(rca_node(*it, i));
      n_it = rca_nodes.end();
      --n_it;
    }
    else {
      (*n_it).id = *it;
      (*n_it).ranks.push_back(i);
    }
  }

  // get node coordinates from Cray RCA subsystem
  rca_mesh_coord_t coord;
  n_it = rca_nodes.begin();
  it = node_ids.begin(), end = node_ids.end();
  nid = -1;
  for (; it != end; ++it) {
    rca_get_meshcoord(static_cast<uint32_t>(*it), &coord);
    // check that node ids match
    while ((*n_it).id != *it) {
      ++n_it;
      assert(n_it != rca_nodes.end());
    }
    (*n_it).x = coord.mesh_x;
    (*n_it).y = coord.mesh_y;
    (*n_it).z = coord.mesh_z;
  }
#endif // __CRAYXE

  // sort node list by id
  sort(rca_nodes.begin(), rca_nodes.end());
#endif
  return rca_nodes;
}

// Pass ranks' coordinate (centroid of elements
// on this rank), list of ranks we communicate
// with, and a weight associated with each adjacent
// rank (rank list and weight list must be the same
// length).  Each rank in world must call this method.

// interface with just coordinate of calling rank
template <typename Point>
new_ranks_t rca_balance(Point c, boost::mpi::communicator world)
{
  // partition with rcb
  typedef typename point_traits<Point>::scalar_type Scalar;
  typedef typename point_traits<Point>::space_type Space;

  rca_nodes_t rca_nodes = rca_balance_impl(c, world);

  recursive_coordinate_bisection<Scalar, Space> rcb;
  Point* p = &c, *p_end = p+1;
  partition(p, p_end, rcb, world);
}

// interface with adjacent ranks but equal weights
template <typename Coord, typename RankIter>
new_ranks_t rca_balance(Coord c, RankIter r_it, RankIter r_end,
  boost::mpi::communicator world)
{
  // partition with rcb after assigning coords based on adjacency
  using std::accumulate;
  using std::copy;
  using std::cout;
  using std::distance;
  using std::endl;
  using std::ostream_iterator;
  using std::sort;
  using std::unique;
  using std::vector;

  namespace mpi = boost::mpi;

  // Mpi
  int nprocs = world.size();
  int rank = world.rank();

  // get rca node list (move into place with nrvo)
  rca_nodes_t rca_nodes = rca_balance_impl(c, world);

  return new_ranks_t();
}

// interface with non-constant weights
template <typename Coord, typename RankIter, typename WeightIter>
new_ranks_t rca_balance(Coord c, RankIter r_it, RankIter r_end,
  WeightIter w_it, boost::mpi::communicator world)
{
  using std::accumulate;
  using std::copy;
  using std::cout;
  using std::distance;
  using std::endl;
  using std::iterator_traits;
  using std::ostream_iterator;
  using std::sort;
  using std::unique;
  using std::vector;

  namespace mpi = boost::mpi;

  // Mpi
  int nprocs = world.size();
  int rank = world.rank();

  // get rca node list (move into place with nrvo)
  rca_nodes_t rca_nodes = rca_balance_impl(c, world);

  // ensure weight list is correct size (by accessing last weight)
  // list of insufficient length will (should) trigger seg fault
  WeightIter w_end = w_it + distance(r_it, r_end);
  typename iterator_traits<WeightIter>::value_type w = *--w_end;

  // Build graph with ranks as vertices and communication cost between
  // those ranks as the edge weights.

  return new_ranks_t(0, 0);
}

// get node coordinates from rca subsystem
// get task coordinates from the application
// get communication weights between each rank
// Algorithm returns two integers, first is
// rank I'm moving to, second is rank that is
// moving here.

}  // namespace DGM

#endif
