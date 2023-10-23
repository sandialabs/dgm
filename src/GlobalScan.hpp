/** \file GlobalScan.hpp (aka, ParallelPrefix)
    \brief Provides an implementation of GlobalScan for parallel setup
    \author K. Noel Belcourt
*/

#ifndef DGM_GlobalScan_hpp
#define DGM_GlobalScan_hpp

// system includes
#include <algorithm>
#include <iterator>
#include <numeric>
#include <vector>

#ifdef DGM_PARALLEL

// Boost includes
#include <boost/mpi/collectives.hpp>
#include <boost/mpi/communicator.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include "Comm.hpp"

/// DGM namespace
namespace DGM {

template <typename Value>
struct disjoint_ranges {
  std::vector<Value>& ids;

  disjoint_ranges(std::vector<Value>& s, Value v) : ids(s) {
    ids.push_back(v);
  }

  Value operator()(Value first, Value second) {
    if (second != first + 1)
      ids.push_back(second);
    else if (second <= first)
      throw DGM::exception("Element ids are improperly ordered, "
                           "expected monotonicly increasing element ids.");
    return second;
  }
};

/// Compute global displacement
/** Compute global displacements given an element id and an
    associated data size, store the global displacements back
    into the size list (overwriting the element data size).
    This algorithm is also known as computing the parallel prefix.

    The global displacement is the byte offset into a global
    vector where that element's data is stored.  Because the
    data size can vary by element, and because the elements are
    globally distributed over the communicator, this algorithm
    computes an element's global displacement without having to
    construct the global vector of data.  The algorithm requires
    3 MPI collectives, one gather and two reductions.

    [ Input ]

    [it, end) -- Iterators to sorted contiguous list of locally
                 owned global element ids.  Each element id should 
                 occur on only one rank in the global communicator.
                 That is, each element should be owned by only one
                 rank.

    s_it -- Iterator to beginning of list of data sizes
            associated with each global element id.  List is the 
            same length as global element id list.  The data size 
            associated with each element must be non-negative.  
            When this function returns, this list is overwritten 
            with each element's global displacement.

    world -- Communicator for MPI collectives.

    [ Output ]

    s_it -- Element data sizes have been replaced with their global
            displacements.
*/

template <typename IdIter, typename SizeIter>
void global_scan(IdIter it, const IdIter end, SizeIter s_it,
                 boost::mpi::communicator world)
{
  using boost::numeric_cast;
  using std::accumulate;
  using std::copy;
  using std::distance;
  using std::fill;
  using std::iterator_traits;
  using std::lower_bound;
  using std::partial_sum;
  using std::plus;
  using std::streamoff;
  using std::vector;
  namespace mpi = boost::mpi;

  // use numeric_cast to store into s_it to check that there's no overflow
  typedef streamoff id_vt;
  typedef vector<id_vt> vec;
  typedef vec::iterator v_it;
  typedef typename iterator_traits<IdIter>::value_type i_vt;
  typedef typename iterator_traits<SizeIter>::value_type size_vt;

  // count number of contiguous element id subranges
  // store first element id of each contiguous subrange
  vec local_ids;
  disjoint_ranges<id_vt> dr(local_ids, *it);
  accumulate(it+1, end, *it, dr);

  // get number of contiguous subranges from each rank
  vec v1(world.size());
  mpi::all_gather(world, static_cast<id_vt>(local_ids.size()), v1);

  // find my insertion point and total number of contiguous subranges
  id_vt rank = world.rank();
  id_vt local_sum = accumulate(v1.begin(), v1.begin()+rank, 0);
  id_vt global_sum = accumulate(v1.begin()+rank, v1.end(), local_sum);

  // zero before resize, copy locally owned element ids into right location
  fill(v1.begin(), v1.end(), 0);
  v1.resize(global_sum);
  copy(local_ids.begin(), local_ids.end(), &v1[local_sum]);

  // global element id of each contiguous subrange across processors
  vec v2(global_sum);
  mpi::all_reduce(world, &v1[0], global_sum, &v2[0], mpi::maximum<id_vt>());

  // store local offsets (into v1) for each global element id (in v2)
  id_vt ne = distance(it, end);
  vec sizes(ne+1);
  partial_sum(s_it, s_it+ne, sizes.begin()+1);
  sizes[0] = 0;
  v_it g_it = v2.begin(), g_end = v2.end(), l_it = v1.begin();
  for (; g_it != g_end; ++g_it, ++l_it) {
    IdIter lb = lower_bound(it, end, *g_it);
    *l_it = sizes[lb-it];
  }

  // reduce local offsets by suming to get global offsets (into v2)
  mpi::all_reduce(world, &v1[0], global_sum, &v2[0], plus<id_vt>());

  // reuse size array to store updated global displacements
  id_vt sum = 0, lsum = 0;
  l_it = local_ids.begin();
  g_it = v2.begin() + local_sum;
  for (; it != end; ++it, ++s_it) {
    if (l_it != local_ids.end() && *it == numeric_cast<i_vt>(*l_it))
      sum = *g_it++, ++l_it;
    lsum = *s_it;
    *s_it = numeric_cast<size_vt>(sum);
    sum += lsum;
  }
}

} // namespace DGM

#endif  // DGM_PARALLEL

#endif  // DGM_GlobalScan_hpp
