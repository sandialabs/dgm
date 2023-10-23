// Author: K. Noel Belcourt

// Test driver for Cray RCA balancing algorithm for
// dynamically load balancing problem based on node
// allocation from the cluster scheduler. This
// implementation is Cray specific and extracted from
// prototype code from Vitus Leung.

#if 0
// Linux
RCAHOME=/Users/kbelco/Projects
mpicxx -g -I$RCAHOME/local/dgm/trilinos/mpi/opt/include -I$RCAHOME/local/atlas/include -I$RCAHOME/local/boost/include  util/rca_test.cpp -L$RCAHOME/local/boost/lib -lboost_mpi -lboost_serialization

// Cray
CC -g -I/home/kbelco/local/dgm/trilinos/mpi/opt/include -I/home/kbelco/local/boost/include -I/opt/cray/rca/1.0.0-2.0402.47290.7.1.gem/include -I/opt/cray-hss-devel/7.1.0/include -I/opt/cray/krca/1.0.0-2.0402.46083.4.47.gem/include util/rca_test.cpp -L/opt/cray-hss-devel/7.1.0/lib/snos64/static -lrsmsevent -L/opt/cray/rca/1.0.0-2.0402.47290.7.1.gem/lib64 -lrca -L/home/kbelco/local/boost/lib -lboost_mpi -lboost_serialization -lglib-2.0

CRAY_LD_LIBRARY_PATH=/opt/cray/netcdf/4.3.0/GNU/48/lib:/opt/cray/hdf5/1.8.11/GNU/48/lib:/opt/cray/pmi/4.0.1-1.0000.9753.86.3.gem/lib64:/opt/cray/libsci/12.1.2/GNU/48/x86_64/lib:/opt/cray/mpt/6.1.1/gni/mpich2-cray/81/lib:/opt/cray/xpmem/0.1-2.0402.45248.1.5.gem/lib64:/opt/cray/dmapp/4.0.1-1.0402.7784.4.1.gem/lib64:/opt/cray/ugni/5.0-1.0402.7551.1.10.gem/lib64:/opt/cray/udreg/2.3.2-1.0402.7546.1.5.gem/lib64
#endif

#include <iostream>
#include <utility>
#include <vector>

#include <boost/mpi/communicator.hpp>
#include <boost/mpi/environment.hpp>

#include "Point.hpp"
#include "DynamicBalance.hpp"

// get node coordinates from rca subsystem
// get task coordinates from the application
// get communication weights between each rank
// Algorithm returns two integers, first is
// rank I'm moving to, second is rank that is
// moving here.
int main(int argc, char** argv) {
  using std::cout;
  using std::endl;
  using std::pair;
  using std::vector;
  using DGM::point;

  namespace mpi = boost::mpi;

  // setup parallel environment
  mpi::environment env(argc, argv);
  mpi::communicator world;
  int rank = world.rank();
  int nprocs = world.size();

  // centroid of elements on this rank
  int m = rank % 4;
  int xc = m == 0 || m == 3 ? 0 : 1;
  int yc = rank < 4 ? 0 : 1;
  int zc = m < 2 ? 0 : 1;
  point<int, XYZ> coord(xc, yc, zc);
  // cout << "rank: " << rank << " coords: " << x(coord) << " " << y(coord) << " " << z(coord) << endl;

  // 3 interfaces to rca_balance
  // 1) have only coordinate of my rank
  new_ranks_t new_ranks = rca_balance(coord, world);

#if 0
  // list of adjacent ranks I communicate with
  int adj[][3] = {
    { 1, 3, 4 },
    { 0, 2, 5 },
    { 1, 3, 6 },
    { 0, 2, 7 },
    { 0, 5, 7 },
    { 1, 4, 6 },
    { 2, 5, 7 },
    { 3, 4, 6 }
  };
  vector<int> adj_ranks(adj[rank], adj[rank]+3);

  // 2) have coordinate and list of adjacent ranks
  new_ranks = rca_balance(coord, adj_ranks.begin(), adj_ranks.end(), world);

  // check if I'm moving to new rank (someone else moving here)
  if (new_ranks.first != rank) {
    cout << "Constant weights: rank " << rank << " is moving to rank " << new_ranks.first << endl;
  }

  // communication weights associated with adjacent ranks
  int wgt[][3] = {
    { 1, 3, 4 },
    { 0, 2, 5 },
    { 1, 3, 6 },
    { 0, 2, 7 },
    { 0, 5, 7 },
    { 1, 4, 6 },
    { 2, 5, 7 },
    { 3, 4, 6 }
  };
  vector<int> weights(wgt[rank], wgt[rank]+3);

  // 3) have coordinate, list of adjacent ranks and weights
  new_ranks = rca_balance(coord, adj_ranks.begin(), adj_ranks.end(), weights.begin(), world);

  // check if I'm moving to new rank (someone else moving here)
  if (new_ranks.first != rank) {
    cout << "Non-const weights: rank " << rank << " is moving to rank " << new_ranks.first << endl;
  }
#endif

  return 0;
}
