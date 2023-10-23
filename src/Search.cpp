/** \file Search.cpp
    \brief DGM Search functions
*/

// system includes
#include <cstdio>
#include <string>
#include <algorithm>
#include <map>
#include <limits>

// Trilinos includes
#ifdef DGM_USE_STK_SEARCH
#include <CoarseSearch.hpp>
#endif

// DGM includes
#include "Search.hpp"

namespace DGM {

namespace Search {

/// Find elements within a given radius of a centroid
void field(std::multimap<unsigned, unsigned> &elements,
           const Field *F,
           const dMatrix &centroids,
           const Scalar radius) {

#ifndef DGM_USE_STK_SEARCH

  const size_t nn  = centroids.rows(); 
  const size_t nsd = centroids.cols();
  for (Ordinal e=0; e<F->ne; ++e) {
    for (size_t src=0; src<nn; ++src) {
      Point obs_point;
      const Element* el = F->el[e];
      const Ordinal lsrc = numeric_cast<Ordinal>(src);
      if (0<nsd) obs_point.x = centroids[lsrc][0];
      if (1<nsd) obs_point.y = centroids[lsrc][1];
      if (2<nsd) obs_point.z = centroids[lsrc][2];
      if (el->is_in_element(obs_point, radius)) {
        const Size id = F->partition->eid(e);
        std::pair<size_t, Size> elem(src, id);
        elements.insert(elem);
      }
    }
  }

#else

  /// stk_search uses compile time dimensions.  
  /** Since 2D is a simple case of 3D, hard code everything to 3D. */
  static const int NSD_(3);

  // (ID#,Processor#) Do not use Processor # if everything done on processor 0.
  typedef stk::search::ident::IdentProc<size_t, unsigned>IdentProc; 
  typedef stk::search::box::AxisAlignedBoundingBox
    <IdentProc,float,NSD_>  RangeBoundingVolume; // Boxes around hexes
  typedef stk::search::box::SphereBoundingBox    
    <IdentProc,float,NSD_>  DomainBoundingVolume;// Spheres around points
  std::vector<RangeBoundingVolume>  range; 
  std::vector<DomainBoundingVolume> domain; 
  std::vector<std::pair<DomainBoundingVolume::Key,RangeBoundingVolume::Key> > 
    domain_to_range_keys;
  
  const DGM::Comm *comm = DGM::Comm::World;
  const unsigned np     = comm->NumProc();
  const unsigned my_pid = comm->MyPID();
  if (F->ne < np) {
    if (comm->Master())
      cerr<<"Number of processors exceeds numbers of elements"<<endl;
    comm->exit(DGM::FAILURE);
  }
  
  DGM::Partition::Ptr partition = F->partition;
  
  const size_t nn = centroids.rows(); 
  const size_t ne = partition->ne;
  const size_t gne = partition->gne;
  const iVector &inc = partition->setup_local_id_array();
  const iVector &eid = partition->eid;
  
  range.reserve(ne);
  for (size_t i=0; i<gne; ++i) {
    if (0<=inc[i]) {
      // Set up the boxes that define the mesh: Range
      const std::vector<float> bound = F->box(inc[i]);
      IdentProc id(inc[i],0);
      RangeBoundingVolume box(&bound[0], id); 
      box.expand(radius); // find all boxes bounding a corner or side.
      range.push_back(box);
    }    
  }
  // Set up the points to find in the mesh: Domain
  domain.reserve(nn);
  for(int i=0; i<nn; ++i) {
    const Scalar standard_deviation = 0;
    const unsigned nsd = centroids.cols();
    std::vector<float> obs_point(NSD_,0);
    for (size_t j=0; j<nsd; ++j) obs_point[j] = centroids[i][j];
    IdentProc id(i,0);
    DomainBoundingVolume sphere(&obs_point[0], standard_deviation, id); 
    domain.push_back(sphere);
  }
  
  stk::search::FactoryOrder order;
  order.m_algorithm =  stk::search::FactoryOrder::BIHTREE;
  // Perform search of all points in all boxes with one function call........
  stk::search::coarse_search(domain_to_range_keys, range, domain, order);
  
  // determine if point in box is actually in element contained within box...
  for(size_t i=0; i<domain_to_range_keys.size(); ++i) {
    const unsigned src = domain_to_range_keys[i].first.ident;
    const unsigned dst = domain_to_range_keys[i].second.ident;
    const unsigned nsd = centroids.cols();
    Point obs_point;
    if (0<nsd) obs_point.x = centroids[src][0];
    if (1<nsd) obs_point.y = centroids[src][1];
    if (2<nsd) obs_point.z = centroids[src][2];
    
    const Element* el = F->el[dst];
    if (el->is_in_element(obs_point, radius)) {
      const int id = F->partition->eid[dst];
      std::pair<unsigned, unsigned> elem(src,id);
      elements.insert(elem);
    }
  }
#endif
}
  
} // namespace Search
  
} // namespace DGM
