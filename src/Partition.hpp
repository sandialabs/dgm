#ifndef DGM_PARTITION_HPP
#define DGM_PARTITION_HPP

/** \file  Partition.hpp
    \brief Classes for managing parallel partitions.
    \author Scott Collis
*/

// System includes
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <limits>
using namespace std;

// boost include
#include "boost/numeric/conversion/cast.hpp"
using boost::numeric_cast;

// DGM includes
#include "Comm.hpp"
#include "RangeMap.hpp"
#include "Types.hpp"
#include "String.hpp"
#include "Utilities.hpp"

namespace DGM {

// forward declarations
class Element;
class Side;

/// Helper class for Partition linkages
template <typename GlobalSize, typename LocalSize>
class Link {
 public:
  GlobalSize elmtid;  ///< Element id
  LocalSize  sideid;  ///< Side id
  GlobalSize sidegid; ///< Global side id

  template <typename T>
  static T undefined() { return numeric_limits<T>::max(); }

  /// Constructor
  Link() : elmtid(undefined<GlobalSize>()), sideid(undefined<LocalSize>()),
           sidegid(undefined<GlobalSize>()) { }

  /// Set new values
  void set(GlobalSize eid, LocalSize id, GlobalSize gid) {
    elmtid=eid; sideid=id; sidegid=gid;
  }

  /// Links are sorted based on the global side id
  inline bool operator<(const Link &other) const {
    return sidegid < other.sidegid;
  }

  /// Links are sorted based on the global side id
  inline bool operator>(const Link &other) const {
    return sidegid > other.sidegid;
  }

  /// Links are equal if the global side id is equal
  inline bool operator==(const Link &other) const {
    return sidegid == other.sidegid;
  }

  /// Links are equal if the global side id is equal
  inline bool operator!=(const Link &other) const {
    return (!(*this == other));
  }
};

/// Partition connectivity class
template <typename GlobalSize, typename LocalSize, typename Scalar>
class Pcon {
 public:
  LocalSize pid;                               ///< partition id
  LocalSize len;                               ///< length
  CMC::Vector<Scalar,LocalSize> buf;           ///< storage for shared sides
  CMC::Vector<Scalar,LocalSize> sbuf;          ///< the send buffer
  vector< Link<GlobalSize,LocalSize> >  links; ///< vector of links
  vector<Side*> side;                          ///< vector of ghost sides
  /// constructor
  Pcon() : pid(0), len(0) {}
};

/// Process connectivity class
template <typename GlobalSize, typename LocalSize>
class Connect {
 public:
  LocalSize cprocid;                           ///< pid for connected partition
  LocalSize datalen;                           ///< length of data to transmit
  LocalSize nsides;                            ///< number of shared sides
  vector< Link<GlobalSize,LocalSize> > links;  ///< vector of links
};

/// Parallel partition class
/**
    - eid(local_ne):    the global element id for each local element
    - part(global_ne):  the process id for each global element
    - inc(global_ne):   the global to local id map
*/
template <typename GlobalSize, typename LocalSize, typename Scalar>
class Partition {

public:

  const DGM::Comm::Ptr comm;       ///< communicator for this partition

  /// Type for the local to global element map
  typedef std::vector<GlobalSize> EidType;

  /// Type for the global to local element map
  typedef std::map<GlobalSize,LocalSize> IncType;

  /// Type for the global element id to partition id map
  typedef std::map<GlobalSize,LocalSize> PartType;

  /// Type for the global partition map
  typedef range_map<GlobalSize,GlobalSize> RangeMap;

  /// shared pointer to Partition
  typedef typename DGM::Shared<Partition>::Ptr Ptr;

private:

  const GlobalSize _gne;         ///< global number of elements
  LocalSize _ne;                 ///< number of elements in partition

  EidType  _eid;                 ///< global element ids:     eid(local_ne)
  IncType  _inc;                 ///< local element id array: inc(global_ne)
  RangeMap _part;                ///< owning processor map:

  string root;                   ///< root for this run

  GlobalSize _glen;              ///< global length of data record
  GlobalSize _nodal_glen;        ///< global length of nodal data record

public:

  /// Undefined id
  template <typename T>
  static T undefined() { return numeric_limits<T>::max(); }

  /// Part accessor
  GlobalSize eid(const LocalSize lid) const { return _eid[lid]; }

  /// Get eid array (const version)
  const GlobalSize *eid_data() const { return &(_eid.front()); }

  /// Get eid array
  GlobalSize *eid_data() { return &(_eid.front()); }

  /// Use a function interface
  LocalSize inc(const GlobalSize gid) const {
    typename IncType::const_iterator it = _inc.find(gid);
    if (it==_inc.end()) {
      BackTrace bt; bt.print();
      throw DGM::exception("Could not find global element id = "+asString(gid)
                           +" on rank "+asString(comm->MyPID()));
    }
    return it->second;
  }

  /// Use a method to determine ownership
  bool owns(const GlobalSize gid) const {
    typename IncType::const_iterator it = _inc.find(gid);
    return (it==_inc.end() ? false : true );
  }

  /// Number of global elements
  GlobalSize gne() const { return _gne; }

  /// Number of local elements on this partition
  LocalSize ne() const { return _ne; }

  /// Return the number of connected processors
  LocalSize ncprocs() const { return numeric_cast<LocalSize>(cinfo.size()); }

  // information for parallel IO on Modal

  /// global data displacement for local element
  CMC::Vector<GlobalSize,LocalSize> disp;
  /// length of data for each local element
  CMC::Vector<LocalSize,LocalSize> len;

  // Same information, but using the Nodal representation

  /// global nodal displacement for local element
  CMC::Vector<GlobalSize,LocalSize> nodal_disp;
  /// length of nodal data for each local element
  CMC::Vector<LocalSize,LocalSize> nodal_len;

  /// partition connectivity information
  std::vector< Connect<GlobalSize,LocalSize> > cinfo;

  /// Constructor
  Partition(const GlobalSize, const string,
            const DGM::Comm::Ptr = DGM::Comm::World);

  /// Serial Constructor
  Partition(const GlobalSize, const DGM::Comm::Ptr = DGM::Comm::World);

  /// Copy constructor
  Partition(const Partition *, bool reset_partition = false);

#ifdef DGM_USE_ZOLTAN
  /// interface used by zoltan2 to update the partition with new decomposition
  template <typename Iterator>
  void update(Iterator it, Iterator end);
#endif

  void connectivity(const vector<Element*>, bool);
  void connectivity_pc(const vector<Element*>, bool);

  void reset_side_links(const vector<Element *> &, vector<Element *> &,
                        vector< Pcon<GlobalSize,LocalSize,Scalar> * > & );
  void reset_side_links(vector<Element *> &,
                        vector< Pcon<GlobalSize,LocalSize,Scalar> * > &,
                        bool use_zoltan);

  const IncType & setup_local_id_array();

  template <typename DVector, typename LVector>
  void global_scan(DVector&, const LVector&);

  // use this interface if you need the maximum displacement (glen)
  template <typename myGlobalSize, typename DVector, typename LVector>
  void global_scan(myGlobalSize& glen, DVector&, const LVector&);

  GlobalSize & nodal_glen() { return _nodal_glen; }
  GlobalSize & glen() { return _glen; }
  const GlobalSize & nodal_glen() const { return _nodal_glen; }
  const GlobalSize & glen() const { return _glen; }

  void inline_part(const std::vector<Element*>&, bool);

private:
  void serial_setup(const GlobalSize);
  void parallel_setup(const GlobalSize, const string);
  void make_myPart(const vector<Element *> &el, PartType &myPart,
                   const bool pc=false);

  //template <typename DVector, typename LVector, typename Partition>
  //GlobalSize global_scan_impl(DVector &disp, const LVector&, const Partition&);

};

} // namespace DGM

#endif   // DGM_PARTITION_HPP
