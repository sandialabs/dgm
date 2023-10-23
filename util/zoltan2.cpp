/** \file   zoltan2.cpp
    \brief  Zoltan example to partition a hypergraph
    \author K. Noel Belcourt

    Basic example of using Zoltan to partition a hypergraph.

    We think a hypergraph as a matrix, where the hyperedges are
    the rows, and the vertices are the columns.  If (i,j) is
    non-zero, this indicates that vertex j is in hyperedge i.

    In some Zoltan documentation, the non-zeroes in hypergraph
    matrices are called "pins".
**/

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <stdexcept>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <boost/lexical_cast.hpp>
#include <boost/mpi/collectives.hpp>
#include <boost/mpi/communicator.hpp>
#include <boost/mpi/environment.hpp>
#include <boost/mpi/nonblocking.hpp>

#include <zoltan.h>

#include "CaseInsensitiveString.hpp"

using std::copy;
using std::cout;
using std::distance;
using std::endl;
using std::fill;
using std::ifstream;
using std::make_pair;
using std::min_element;
using std::ofstream;
using std::ostream_iterator;
using std::pair;
using std::runtime_error;
using std::string;
using std::swap;
using std::vector;
using std::ws;

using boost::lexical_cast;
namespace mpi = boost::mpi;

typedef struct {
  int numMyVertices;        ///< number of vertices that I own initially
  ZOLTAN_ID_TYPE *vtxGID;   ///< global ID of these vertices
  int numMyHEdges;          ///< number of my hyperedges
  int numAllNbors;          ///< total number of vertices in my hyperedges
  ZOLTAN_ID_TYPE *edgeGID;  ///< global ID of each of my hyperedges
  int *nborIndex;           ///< index into nborGID array of edge's vertices
  /// vertices of edgeGID[i] begin at nborGID[nborIndex[i]]
  ZOLTAN_ID_TYPE *nborGID;
  int *wgt_it;
} hg_data;

// required query functions for zoltan
static int get_number_of_vertices(void *data, int *ierr) {
  hg_data *hg = static_cast<hg_data*>(data);
  *ierr = ZOLTAN_OK;
  return hg->numMyVertices;
}

static void get_vertex_list(void *data, int sizeGID, int sizeLID
  , ZOLTAN_ID_PTR globalID, ZOLTAN_ID_PTR localID, int wgt_dim
  , float *obj_wgts, int *ierr)
{
  hg_data *hg = static_cast<hg_data*>(data);
  assert(wgt_dim == 1);
  int *it = hg->wgt_it;
  for (int i=0; i<hg->numMyVertices; ++i, ++it) {
    globalID[i] = hg->vtxGID[i];
    localID[i] = i;
    obj_wgts[i] = *it;
  }
  *ierr = ZOLTAN_OK;
}

static void get_hypergraph_size(void *data, int *num_lists
  , int *num_nonzeroes, int *format, int *ierr)
{
  hg_data *hg = static_cast<hg_data*>(data);

  *num_lists = hg->numMyHEdges;
  *num_nonzeroes = hg->numAllNbors;

  // We will provide compressed hyperedge (row) format.  The
  // alternative is is compressed vertex (column) format:
  // ZOLTAN_COMPRESSED_VERTEX.
  *format = ZOLTAN_COMPRESSED_EDGE;
  *ierr = ZOLTAN_OK;
}

static void get_hypergraph(void *data, int sizeGID, int num_edges
  , int num_nonzeroes, int format, ZOLTAN_ID_PTR edgeGID
  , int *vtxPtr, ZOLTAN_ID_PTR vtxGID, int *ierr)
{
  hg_data *hg = static_cast<hg_data*>(data);

  if (num_edges != hg->numMyHEdges || num_nonzeroes != hg->numAllNbors
      || format != ZOLTAN_COMPRESSED_EDGE)
  {
    *ierr = ZOLTAN_FATAL;
    return;
  }

  for (int i=0; i<num_edges; ++i) {
    edgeGID[i] = hg->edgeGID[i];
    vtxPtr[i] = hg->nborIndex[i];
  }

  for (int i=0; i<num_nonzeroes; ++i)
    vtxGID[i] = hg->nborGID[i];

  *ierr = ZOLTAN_OK;
}

// only two (required) command line arguments
// first is test root name (both root.msh and root.con must be present)
// second is number of processors to decompose for
// weight file will be used if present, otherwise not

int main(int argc, char** argv) {

  mpi::environment env(argc, argv);
  mpi::communicator world;

  int rank = world.rank();
  int nprocs = world.size();

  if (3 != argc) {
    cout << "  Invalid number of arguments, should be 3." << endl;
    cout << "  Number of args = " << argc << endl;
    cout << "  Expected (1) test root name and (2) parallel partition size."
         << endl;
    cout << "    Looking for mesh file named root.msh" << endl;
    return -1;
  }

  string root = argv[1];
  string part = argv[2];

  int gne = 0, nsd = 0;
  int save_base_ne = 0, base_ne = 0, ne = 0, lne = 0, nhe = 0;
  vector<int> wgts;
  vector< pair<int,int> > conn;
  // [start,end] indices into conn for ith rank
  vector< pair<int,int> > nhes(nprocs);

  if (0 == rank) {

    // read coordinates
    ifstream msh(string(root + ".msh").c_str());
    if (!msh.good()) {
      cout << "  Failed to open mesh file: "
                << string(root+".msh") << endl;
      return -1;
    }

    const int buf_len = 80;
    char buffer[buf_len];
    size_t dummy;
    msh.getline(buffer, buf_len);
    msh >> gne >> nsd;
    msh.close();

    // read weights separately as there may not be a weights file
    ifstream wgt(string(root + ".wgt").c_str());
    wgts.resize(gne);
    if (wgt.good()) {
      wgt >> dummy;
      for (int i=0,j=0; i<gne; ++i) {
        wgt >> wgts[i];
      }
    }
    else {
      // no weight file, assume all weights are equal
      fill(wgts.begin(), wgts.end(), 1);
    }
    wgt.close();

    // read connectivity (root.con)
    ifstream con(string(root + ".con").c_str());
    if (!con.good()) {
      cout << "  Failed to open connectivity file: "
        << string(root+".con") << endl;
      return -1;
    }

    char c;
    int first = 0, second = 0;
    con.getline(buffer, buf_len);
    con.getline(buffer, buf_len);
    while (con.good() && !con.eof()) {
      con >> c >> first >> dummy >> second >> dummy >> ws;
      conn.push_back(make_pair(first,second));
    }
    con.close();

    // number of hyperedges
    nhe = conn.size();

    lne = gne / nprocs;
    assert(lne * nprocs <= gne);
    base_ne = gne - lne * nprocs;
    ne = lne + base_ne;

    // get exact count of hyperedges for each processor
    int base = ne, start = 1;
    for (int i=0,j=0; i<nprocs; ++i) {
      while (conn[j].first < base && j < conn.size()) ++j;
      nhes[i] = make_pair(start,j);
      base += lne;
      start = ++j;
    }
  }

  if (1 < nprocs) {

    // spread data
    mpi::broadcast(world, ne, 0);       // rank 0 number of elements
    mpi::broadcast(world, nsd, 0);      // number of spatial dimensions
    mpi::broadcast(world, lne, 0);      // number of elements for non-root
                                        // processors
    mpi::broadcast(world, base_ne, 0);  // difference in number of
                                        // elements between root and
                                        // non-root processors

    // split and send based on counts
    if (0 != rank) {

      // nonblocking communication
      mpi::request rreqs[2];

      // receive number of hyperedges
      rreqs[0] = world.irecv(0, 0, nhe);
      mpi::wait_all(rreqs, rreqs + 1);

      // receive weights and hyperedges
      wgts.resize(lne);
      conn.resize(nhe);

      rreqs[0] = world.irecv(0, 1, &wgts[0], lne);
      rreqs[1] = world.irecv(0, 2, &conn[0], nhe);
      mpi::wait_all(rreqs, rreqs + 2);

      ne = lne;
    }
    else {
      int nreqs = 2 * (nprocs - 1);
      mpi::request *sreqs = new mpi::request[nreqs];

      // send number of hyperedges on each rank
      for (int i=1; i<nprocs; ++i) {
        nhe = nhes[i].second - nhes[i].first + 1;
        sreqs[i-1] = world.isend(i, 0, nhe);
      }
      mpi::wait_all(sreqs, sreqs + nprocs-1);

      // send weights and hyperedges
      int *wgt_it = &wgts[0] + ne;
      int lnhe = nhe = nhes[0].second - nhes[0].first + 1;
      pair<int,int> *conn_it = &conn[0] + nhe;
      for (int i=1,j=0; i<nprocs; ++i,j+=2) {
        nhe = nhes[i].second - nhes[i].first + 1;
        sreqs[j] = world.isend(i, 1, wgt_it, lne);
        sreqs[j+1] = world.isend(i, 2, conn_it, nhe);
        wgt_it += lne;
        conn_it += nhe;
      }
      mpi::wait_all(sreqs, sreqs + nreqs);
      nhe = lnhe;

      // data is sent, truncate data structures keep just our data
      if (1 < nprocs) {
        wgts.erase(wgts.begin() + ne, wgts.end());
        conn.erase(conn.begin() + nhe, conn.end());
      }

      save_base_ne = base_ne;
      base_ne = 0;
      delete [] sreqs;
    }
  }

  hg_data hg;
  hg.wgt_it = &wgts[0];
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
  int base = base_ne + rank * ne;
  for (int i=0; i<hg.numMyVertices; ++i)
    hg.edgeGID[i] = hg.vtxGID[i] = base + i;
  // index into nborGID array of hyperedge's vertices (elements)
  hg.nborIndex = new int[hg.numMyHEdges];
  hg.nborIndex[0] = 0;
  // Vertices of edge edgeGID[i] begin at nborGID[nborIndex[i]]
  hg.nborGID = new ZOLTAN_ID_TYPE[hg.numAllNbors];
  // basically just con array (if con array is ordered by local element id)
  hg.nborGID[0] = conn[0].first;
  hg.nborGID[1] = conn[0].second;
  int k=1;
  for (unsigned int i=1,j=2; i<nhe; ++i,++j) {
    assert(k <= hg.numAllNbors);
    assert(conn[i].first != conn[i].second);
    if (conn[i-1].first != conn[i].first) {
      hg.nborIndex[k] = j;
      ++k;
      hg.nborGID[j] = conn[i].first;
      ++j;
    }
    hg.nborGID[j] = conn[i].second;
  }

  struct Zoltan_Struct *zz = Zoltan_Create(MPI_COMM_WORLD);

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
  Zoltan_Set_Param(zz, "NUM_GLOBAL_PARTS", part.c_str());

  // query functions
  Zoltan_Set_Num_Obj_Fn(zz, get_number_of_vertices, &hg);
  Zoltan_Set_Obj_List_Fn(zz, get_vertex_list, &hg);
  Zoltan_Set_HG_Size_CS_Fn(zz, get_hypergraph_size, &hg);
  Zoltan_Set_HG_CS_Fn(zz, get_hypergraph, &hg);

  int changes, numGidEntries, numLidEntries, numImport, numExport;
  int *importProcs = 0, *importToPart = 0;
  int *exportProcs = 0, *exportToPart = 0;
  ZOLTAN_ID_PTR importGlobalGids, importLocalGids;
  ZOLTAN_ID_PTR exportGlobalGids, exportLocalGids;

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
    throw runtime_error("Zoltan failed to partition mesh");

  // partition after calling zoltan
  vector<int> parts(hg.numMyVertices, rank);
  for (int i=0; i<numExport; ++i) {
    parts[exportLocalGids[i]] = exportToPart[i];
  }

  if (1 < nprocs) {
    // receive parts from non-root ranks
    if (0 == rank) {
      vector<int> gparts(gne);
      // copy my data in first
      copy(parts.begin(), parts.end(), gparts.begin());

      int nreqs = nprocs - 1;
      mpi::request *rreqs = new mpi::request[nreqs];
      ne -= save_base_ne;
      for (int i=1; i<nprocs; ++i) {
        rreqs[i-1] = world.irecv(i, 3, &gparts[save_base_ne+i*ne], ne);
      }
      mpi::wait_all(rreqs, rreqs + nreqs);
      swap(parts, gparts);
      delete [] rreqs;
    }
    else {
      mpi::request sreqs[2];
      sreqs[0] = world.isend(0, 3, &parts[0], ne);
      mpi::wait_all(sreqs, sreqs + 1);
    }
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
  int nparts = lexical_cast<int>(part);
  vector<int> in_parts(nparts), out_parts(nparts);
  for (int i=0; i<parts.size(); ++i) in_parts[parts[i]] = parts[i];
  mpi::all_reduce(world, &in_parts[0], nparts, &out_parts[0],
                  mpi::minimum<int>());
  sort(out_parts.begin(), out_parts.end());
  out_parts.erase(unique(out_parts.begin(), out_parts.end()), out_parts.end());
  bool decomp_is_good = out_parts.size() == nparts;
  if (!decomp_is_good) {
    if (0 == rank) {
      cout << "Error: not writing partition file as some cores have no "
        "elements." << endl;
      cout << "       Suggest partitioning this mesh onto fewer cores." << endl;
    }
  }

  // write solution if at least one element per core
  if (0 == rank && decomp_is_good) {
    // write decomposition to partition file (root.part.parallel_size)
    cout << "writing " << string(root + ".part." + part) << endl;
    string part_file(string(root + ".part." + part).c_str());
    remove(part_file.c_str());
    ofstream parts_file(part_file.c_str());
    if (!parts_file.good()) {
      cout << "  Failed to open part file:" << part_file << endl;
      return -1;
    }
    for (int i=0; i<gne; ++i) {
      parts_file << parts[i] << endl;
    }
    parts_file.close();
  }

  return 0;
}
