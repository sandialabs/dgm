/** \file RecursiveCoordinateBisection.hpp
    \brief Recursive coordinate bisection algorithm
    \author K. Noel Belcourt

   Parallel complexity is function of parallel size
   (nprocs) and scales as the height of binary search
   tree (ht) storing the cut planes: ht = ceil(log2(nprocs)).
   All other algorithms have worst case linear complexity
   in either parallel size, or number of points.

   communication cost (total):
     collectives: 4 * ht (2 all_reduce and 2 all_gather)
     worst case point to point: nprocs * ht
     best case point to point: (nprocs/2) * ht

   memory scaling:

*/

#ifndef DGM_RecursiveCordinateBisection_hpp
#define DGM_RecursiveCordinateBisection_hpp

// standard libraries
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <vector>

#ifndef DGM_PARALLEL
#include <boost/mpi/collectives.hpp>
#include <boost/mpi/communicator.hpp>
#include <boost/mpi/request.hpp>
#endif

// DGM libraries
#include "BinarySearchTree.hpp"
#include "BoundingBox.hpp"
#include "Cartesian.hpp"
#include "CuttingPlanes.hpp"
#include "Utilities.hpp"

namespace DGM {

template <typename Scalar, typename Space>
struct recursive_coordinate_bisection {
  typedef recursive_coordinate_bisection<Scalar,Space> rcb_t;
  typedef cutting_plane<Scalar> CutPlane;
  typedef node<CutPlane>* node_t;

  recursive_coordinate_bisection() : root(0) {}
  ~recursive_coordinate_bisection() {
    if (root) clear(root);
    root = 0;
  }

  void reset() {
    bb.reset();
    if (root) clear(root);
    root = 0;
  }
  template <typename Point>
  const int find_processor_owning(const Point p) const;

  DGM::bounding_box<Scalar,Space> bb;
  node_t root;
};

template <typename PointIter, typename Scalar, typename Space>
void global_bounding_box(PointIter p_it, PointIter p_end
  , DGM::bounding_box<Scalar,Space>& bb, boost::mpi::communicator world)
{
  namespace mpi = boost::mpi;
  // bb is processor local bounding box, add each point
  // on this processor to this bounding box
  for (; p_it != p_end; ++p_it) {
    cout << *p_it << endl;
    add(*p_it, bb);
  }
  // get number of space dimensions
  unsigned int n = n_dimensions(Space());
  Scalar mins[n], maxs[n], global_mins[n], global_maxs[n];
  // local bounding box minimums and maximums into arrays
  minimums(bb, mins, mins+n);
  maximums(bb, maxs, maxs+n);
  // reduce to get globally consistent bounding box minimums and maximums
  mpi::all_reduce(world, mins, n, global_mins, mpi::minimum<Scalar>());
  mpi::all_reduce(world, maxs, n, global_maxs, mpi::maximum<Scalar>());
  // update bounding box with parallel consistent information
  update(bb, global_mins, global_mins+n, global_maxs);
}

// paired send and recv of integral type
template <typename Size>
void recv_from(const int other_rank, Size& n, boost::mpi::communicator world) {
  namespace mpi = boost::mpi;
  mpi::request reqs[1];
  reqs[0] = world.irecv(other_rank, 0, n);
  mpi::wait_all(reqs, reqs+1);
}

template <typename Size>
void send_to(int other_rank, Size s, boost::mpi::communicator world) {
  namespace mpi = boost::mpi;
  mpi::request reqs[1];
  reqs[0] = world.isend(other_rank, 0, s);
  mpi::wait_all(reqs, reqs+1);
}

// paired send and recv of list
template <typename RecvIter, typename Size>
void recv_from(const int other_rank, RecvIter r_it, const Size nr
  , boost::mpi::communicator world)
{
  namespace mpi = boost::mpi;
  mpi::request reqs[1];
  reqs[0] = world.irecv(other_rank, 1, &*r_it, nr);
  mpi::wait_all(reqs, reqs+1);
}

template <typename SendIter, typename Size>
void send_to(const int other_rank, const SendIter s_it, const Size ns
  , boost::mpi::communicator world)
{
  namespace mpi = boost::mpi;
  mpi::request reqs[1];
  reqs[0] = world.isend(other_rank, 1, &*s_it, ns);
  mpi::wait_all(reqs, reqs+1);
}

// function to exchange integers between two ranks
template <typename Size>
Size swap(int other_rank, Size s, boost::mpi::communicator world) {
  namespace mpi = boost::mpi;
  mpi::request reqs[2];
  Size n = 0;
  reqs[0] = world.irecv(other_rank, 2, n);
  reqs[1] = world.isend(other_rank, 2, s);
  mpi::wait_all(reqs, reqs+2);
  return n;
}

// function to exchange list of points between two ranks
template <typename RecvIter, typename RecvSize, typename SendIter
  , typename SendSize>
void swap(const int other_rank, RecvIter r_it, const RecvSize nr
  , const SendIter s_it, const SendSize ns, boost::mpi::communicator world)
{
  namespace mpi = boost::mpi;
  mpi::request reqs[2];
  reqs[0] = world.irecv(other_rank, 3, &*r_it, nr);
  reqs[1] = world.isend(other_rank, 3, &*s_it, ns);
  mpi::wait_all(reqs, reqs+2);
}

template <typename Point, typename PointIter>
boost::mpi::communicator
split_points(std::vector<Point>& points, const PointIter median
  , boost::mpi::communicator world)
{
  namespace mpi = boost::mpi;
  using std::distance;
  using std::iterator_traits;
  using std::vector;
  using DGM::is_odd;

  typedef typename Point::scalar_type Scalar;
  typedef typename iterator_traits<PointIter>::difference_type difference_type;

  int rank = world.rank();
  int nprocs = world.size();

  // split communicator in half, mine (local) and others
  int midrank = nprocs / 2;
  bool is_left = rank < midrank;
  mpi::communicator local = world.split(is_left ? 0 : 1);
  // iterators into list of points
  PointIter p_it = points.begin(), p_end = points.end();
  // split list of points
  if (is_left) {
    // send points in [median, p_end) to processors in right partition
    difference_type n = distance(median, p_end);
    // determine my communicating processor in right partition
    int other_rank = nprocs - rank - 1;
    // swap number of points with right partition rank
    difference_type n_right = swap(other_rank, n, world);
    // allocate vector to hold incoming data
    vector<Point> recv_points(n_right);
    // swap data with right partition rank
    swap(other_rank, recv_points.begin(), n_right, median, n, world);
    // remove points from my list
    points.erase(median, p_end);
    // communication complete, add new points to my list
    points.insert(points.end(), recv_points.begin(), recv_points.end());

    // check if odd number of processors and I'm last on the left
    if (is_odd(nprocs) && midrank == rank+1) {
      // receive from lowest rank in right partition
      recv_from(rank+1, n_right, world);
      // size for incoming data
      recv_points.resize(n_right);
      // receive points
      recv_from(rank+1, recv_points.begin(), n_right, world);
      // insert into my list
      points.insert(points.end(), recv_points.begin(), recv_points.end());
    }
  }
  else {
    // send points in [p_it, median) to processor in left partition
    difference_type n = distance(p_it, median);
    // determine my communicating processor in left partition
    int other_rank = nprocs - rank - 1;
    // if I'm the first rank in the right paritition
    if (rank == other_rank) {
      // send count to highest rank in left partition
      send_to(rank-1, n, world);
      // send points
      send_to(rank-1, p_it, n, world);
      // remove points from my list
      points.erase(p_it, median);
    }
    else {
      // swap number of points with left rank
      difference_type n_left = swap(other_rank, n, world);
      // allocate vector to hold incoming data
      vector<Point> recv_points(n_left);
      // swap points with other rank
      swap(other_rank, recv_points.begin(), n_left, p_it, n, world);
      // remove points from my list
      points.erase(p_it, median);
      // communication completed, add points to my list
      points.insert(points.end(), recv_points.begin(), recv_points.end());
    }
  }
  return local;
}

template <typename PointIter, typename StrictWeakOrdering>
typename std::iterator_traits<PointIter>::value_type
global_median(const PointIter p_it, const PointIter p_end
  , StrictWeakOrdering f, boost::mpi::communicator world)
{
  // globally consistent median
  using std::distance;
  using std::iterator_traits;
  using std::nth_element;
  using std::vector;
  using DGM::is_even;
  namespace mpi = boost::mpi;
  typedef typename iterator_traits<PointIter>::difference_type difference_type;
  typedef typename iterator_traits<PointIter>::value_type Point;
  // number of points on local rank
  difference_type n = distance(p_it, p_end);
  // problem if rank has no points
  assert(0 < n);
  // location of median
  PointIter median = p_it + n / 2;
  // local linear time median along most elongated axis
  nth_element(p_it, median, p_end, f);
  Point p(*median);
  // if n even, average two central medians
  if (is_even(n)) {
    // average two central medians
    nth_element(p_it, --median, p_end, f);
    add(*median, p);
    divide(2, p);
  }
  // prepare to gather medians from each rank
  int size = world.size();
  // if serial
  if (1 == size) return p;
  // gather for parallel answer
  vector<Point> medians(size);
  // gather medians from each rank
  mpi::all_gather(world, p, medians);
  // location of median
  typename vector<Point>::iterator it = medians.begin();
  median = it + size / 2;
  // median of medians
  nth_element(it, median, medians.end(), f);
  p = *median;
  // if parallel size is even
  if (is_even(size)) {
    // average two central medians
    nth_element(p_it, --median, p_end, f);
    add(*median, p);
    divide(2, p);
  }
  return p;
}

// PointIter models ForwardIterator
// Scalar models pod type
template <typename Point, typename Scalar, typename Space>
void partition_impl(std::vector<Point>& points, boost::mpi::communicator local
  , boost::mpi::communicator world
  , recursive_coordinate_bisection<Scalar,Space>& rcb)
{
  namespace mpi = boost::mpi;
  using std::distance;
  using std::iterator_traits;
  using std::lower_bound;
  using std::runtime_error;
  using std::sort;
  using std::unique;
  using std::vector;
  using DGM::strict_weak_ordering;

  typedef typename vector<Point>::iterator PointIter;
  PointIter p_it = points.begin(), p_end = points.end();

  int world_rank = world.rank();
  int world_size = world.size();

  // if nprocs not a power of 2, increase tree depth by 1
  int l2 = log2(world_size);
  if (world_size != pow(2,l2)) ++l2;
  --l2;  // already performed first cut

  int local_rank = local.rank();
  int local_size = local.size();

  typedef cutting_plane<Scalar> CutPlane;
  typedef typename vector<CutPlane>::iterator Iter;
  typename vector<Point>::iterator q_it, q_end;
  vector<CutPlane> all_cuts(world_size);
  vector<Point> all_points;
  PointIter median = p_end;

  while (0 < l2) {
    // parallel consistent global bounding box
    DGM::bounding_box<Scalar,Space> gbb;
    global_bounding_box(p_it, p_end, gbb, local);
    // if my local communicator is size 1, do nothing
    // except participate in gather
    if (1 < local_size) {
      // find most elongated axis
      axis a = most_elongated(gbb);
      // median of all points on this communicator
      Point median = global_median(p_it, p_end, strict_weak_ordering(a), local);
      // now have communicator consistent median, compute cut plane
      CutPlane cp = CutPlane(a, value(median, a));
      // get cut plane from every rank
      mpi::all_gather(world, cp, all_cuts);
    }
    else {
      // participate in gather with known cut plane
      CutPlane& cp = rcb.root->key;
      mpi::all_gather(world, cp, all_cuts);
    }
    // extract new cut planes
    sort(all_cuts.begin(), all_cuts.end());
    all_cuts.erase(unique(all_cuts.begin(), all_cuts.end()), all_cuts.end());
    // insert cuts into tree, check if got new cut planes
    bool new_cuts = false;
    Iter it = all_cuts.begin();
    for (; it != all_cuts.end(); ++it)
      if (0 == tree_search(*it, rcb.root)) {
        insert(*it, &rcb.root);
        new_cuts = true;
      }
    // check if any new cut planes (there should be)
    if (!new_cuts)
      throw runtime_error("Error: expected new cut planes but none generated");
    // split communicator
    if (1 < local_size) local = split_points(points, median, local);
    // update communicator data and point array iterators
    local_rank = local.rank();
    local_size = local.size();
    p_it = points.begin();
    p_end = points.end();
    // another set of cut planes
    --l2;
  }
}

// PointIter models ForwardIterator
// Scalar models pod type
template <typename Point, typename Scalar, typename Space>
void partition(std::vector<Point>& points
  , recursive_coordinate_bisection<Scalar,Space>& rcb
  , boost::mpi::communicator world)
{
  namespace mpi = boost::mpi;
  using std::distance;
  using std::find;
  using std::iterator_traits;
  using std::partition;
  using std::runtime_error;
  using std::vector;
  using DGM::strict_weak_ordering;

  typedef typename vector<Point>::iterator PointIter;
  typedef typename iterator_traits<PointIter>::difference_type difference_type;
  typedef cutting_plane<Scalar> CutPlane;

  // reset rcb object in case contains a previous partitioning
  rcb.reset();

  // don't partition if serial
  int size = world.size();
  int rank = world.rank();

  // now that bounding box is set, return if serial
  if (1 == size) {
    // populate bounding box and return
    return;
  }

  // setup iterators
  PointIter p_it = points.begin(), p_end = points.end();

  // algorithm requires at least one point one each rank
  typedef typename iterator_traits<PointIter>::difference_type difference_type;
  difference_type n = distance(p_it, p_end);

  // gather number of points on each rank
  vector<difference_type> all_points(size);
  typename vector<difference_type>::iterator it = all_points.begin()
    , end = all_points.end();
  mpi::all_gather(world, n, all_points);

  // if empty ranks, spread data
  if (end != find(it, end, 0)) {
    // at least one empty rank, spread data
  }

  // get globally consistent bounding box
  global_bounding_box(p_it, p_end, rcb.bb, world);

  // find most elongated axis x, y, or z
  axis a = most_elongated(rcb.bb);

  // get bottom of most elongated axis
  Scalar bottom = lower_bound(rcb.bb, a);

  // find global median along longest axis
  strict_weak_ordering swo(a);
  Point median = global_median(p_it, p_end, swo, world);
  cout << "median: " << median << endl;

  // generate cutplane at the median value
  Scalar mid_point = value(median, a);
  CutPlane cp(a, mid_point);

  // populate binary tree with this (first) cut plane
  insert(cp, &rcb.root);

  // if 3 or more procs
  if (2 < size) {
    // iterator to median on this rank
    DGM::less_than_point<Scalar> ltp(a, mid_point);
    PointIter middle = partition(p_it, p_end, ltp);
    // split points and the communicator
    mpi::communicator local = split_points(points, middle, world);
    partition_impl(points, local, world, rcb);
  }

  // walk leaves, update rank
  typedef typename recursive_coordinate_bisection<Scalar,Space>::node_t node_t;
  node_t x = tree_minimum(rcb.root);
  rank = 0;
  while (0 != x) {
    x->key.rank = rank;
    x = successor(x);
    ++rank;
  }

  // check if number of cut planes (rank) is expected value (size-1)
  if (rank != size-1)
    throw runtime_error("Error: too few data points for number of processors");
}

// PointIter models ForwardIterator
// Scalar models pod type
template <typename PointIter, typename Scalar, typename Space>
void partition(const PointIter p_it, const PointIter p_end
  , recursive_coordinate_bisection<Scalar, Space>& rcb
  , boost::mpi::communicator world)
{
  using std::iterator_traits;
  using std::vector;
  // can't resize list so make copy of data
  typedef typename iterator_traits<PointIter>::value_type Point;
  vector<Point> points(p_it, p_end);
  partition(points, rcb, world);
}

template <typename Point, typename Scalar, typename Space>
const int find_processor_owning(const Point p
  , const recursive_coordinate_bisection<Scalar,Space> &rcb)
{
  using std::logic_error;
  using std::runtime_error;

  typedef recursive_coordinate_bisection<Scalar,Space> rcb_t;

  // check if point is in bounding_box
  if (!is_point_in_geometry(p, rcb.bb))
    throw runtime_error("Info: Point " + as_string(p)
      + " is not in RCB box: " + as_string(rcb.bb));

  // serial run (rank 0), binary tree empty, point is in geometry
  if (0 == rcb.root) return 0;

  // traverse tree to find owning processor
  typename rcb_t::node_t x = tree_search(p, rcb.root);

  // should never return 0 unless called on empty tree
  if (0 == x)
    throw logic_error("Error: binary search tree returned null node");

  // get rank associated with node, compare to find rank
  // compare cut plane axis of p with tree node
  int rank = x->key.rank+1;
  if (p < x->key) --rank;

  return rank;
}

template <typename Scalar, typename Space>
ostream& operator<<(ostream& ofp
  , const recursive_coordinate_bisection<Scalar,Space>& rcb)
{
  // only output if rcb actually performed
  return ofp << rcb.bb;
}

}  // namespace DGM

#endif
