/** \file Zoltan.hpp
    \brief DGM interface to Zoltan and Zoltan2
    \author K. Noel Belcourt
*/

#ifndef DGM_ZOLTAN_HPP
#define DGM_ZOLTAN_HPP

// system includes
#include <fstream>
#include <ostream>
#include <string>

// DGM includes
#include "Comm.hpp"
#include "Config.hpp"
#include "Types.hpp"
#include "CaseInsensitiveString.hpp"

#ifdef DGM_PARALLEL

#include "MpiComm.hpp"

#ifdef DGM_USE_EPETRA

// Zoltan includes
#include <zoltan.h>

// MPI includes
#include <boost/mpi/communicator.hpp>

namespace DGM {

  /// note: input value (i) is unchanged if parameter not found
  void find_inp_value(std::ifstream &ifp, DGM::case_insensitive_string s,
                      int &i);

  /// generalize input parsing so it's not DGM specific
  bool process_options(int argc, char **argv, std::string product,
                       std::ostream&);

  /// implementation specific pointers
  typedef int(*physics_index)(int);

  /// implementation specific pointers
  typedef int(*number_physics)();

  /// Main partition routine
  int partition(boost::mpi::communicator world, std::string product,
                physics_index, number_physics, std::string path);

/// HyperGraph data for DGM to Zoltan interface
/** For DGM, easiest to assume elements are vertices in hypergraph, then
    hyperedges are simply adjacent elements (we don't have the requisite
    vertex ownership and global numbering plus the implementation is already
    optimal for moving elements, not vertices). */
struct HyperGraphData {
  int numMyVertices;        ///< number of vertices that I own initially
  ZOLTAN_ID_TYPE *vtxGID;   ///< global ID of these vertices
  int numMyHEdges;          ///< number of my hyperedges
  int numAllNbors;          ///< total number of vertices in my hyperedges
  ZOLTAN_ID_TYPE *edgeGID;  ///< global ID of each of my hyperedges
  int *nborIndex;           ///< index into nborGID array of edge's vertices
  /// vertices of edgeGID[i] begin at nborGID[nborIndex[i]]
  ZOLTAN_ID_TYPE *nborGID;
  int *wgt_it;
};

// required query functions for zoltan
inline static int get_number_of_vertices(void *data, int *ierr) {
  HyperGraphData *hg = static_cast<HyperGraphData*>(data);
  *ierr = ZOLTAN_OK;
  return hg->numMyVertices;
}

inline static void get_vertex_list(void *data, int sizeGID, int sizeLID,
                                   ZOLTAN_ID_PTR globalID,
                                   ZOLTAN_ID_PTR localID, int wgt_dim,
                                   float *obj_wgts, int *ierr) {
  HyperGraphData *hg = static_cast<HyperGraphData*>(data);
  assert(wgt_dim == 1);
  int *it = hg->wgt_it;
  for (int i=0; i<hg->numMyVertices; ++i, ++it) {
    globalID[i] = hg->vtxGID[i];
    localID[i] = i;
    obj_wgts[i] = *it;
  }
  *ierr = ZOLTAN_OK;
}

inline static void get_hypergraph_size(void *data, int *num_lists,
                                       int *num_nonzeroes, int *format,
                                       int *ierr) {
  HyperGraphData *hg = static_cast<HyperGraphData*>(data);

  *num_lists = hg->numMyHEdges;
  *num_nonzeroes = hg->numAllNbors;

  // We will provide compressed hyperedge (row) format.  The alternative is
  // is compressed vertex (column) format: ZOLTAN_COMPRESSED_VERTEX.
  *format = ZOLTAN_COMPRESSED_EDGE;
  *ierr = ZOLTAN_OK;
}

inline static void get_hypergraph(void *data, int sizeGID, int num_edges,
		                          int num_nonzeroes, int format,
                                  ZOLTAN_ID_PTR edgeGID, int *vtxPtr,
                                  ZOLTAN_ID_PTR vtxGID, int *ierr) {
  HyperGraphData *hg = static_cast<HyperGraphData*>(data);

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

}  // namespace DGM

#endif  // DGM_USE_EPETRA

#endif  // DGM_PARALLEL

#endif  // DGM_ZOLTAN_HPP
