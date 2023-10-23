// -*- c++ -*-
/** \file Partition.tpp
    \brief Parallel partition template implementation
    \author Scott Collis
    \author James Overfelt
*/

// system includes
#include <iostream>
#include <algorithm>
#include <functional>
#include <numeric>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <iterator>
#include <limits>
using namespace std;

// DGM includes
#include "Element.hpp"
#include "GlobalScan.hpp"
#include "Partition.hpp"
#include "Side.hpp"

// Boost includes
#ifdef DGM_PARALLEL
#include <boost/mpi/communicator.hpp>
#include <boost/mpi/collectives.hpp>
#endif 
#include <boost/numeric/conversion/cast.hpp>

/// Activates code to make sure that global lengths fit in GlobalSize
#define DGM_CHECK_FIT_IN_GLOBALSIZE

namespace DGM {

namespace {

/// Attempt to duplicate the partition first used in DGM
/** Default partition of gne number of objects (numbered 0 to gne-1) on
    np number of processors (numbered 0 to np-1).

    If gne%np = 0 then there are the same number of consecutive objects on
    each processor.

    If gne%np != 0 then the remander is distrubuted to the processors with
    one extra to each nth processor starting at processor 0 where
              n =  (ceil) (1./fmod((double)gne/ne, NULL))

    Example:  gne=103, np=5 then
      p0:( 0, 21)  => 21 objects
      p1:(21, 41)  => 20 objects
      p2:(41, 62)  => 21 objects
      p3:(62, 82)  => 20 objects
      p4:(82,103)  => 21 objects
    Where the number is inclusive of the lower bound but exclusive of the
    upper.
*/
template<typename GlobalSize, typename LocalSize>
class DefaultPartition {
public :
  DefaultPartition(const DGM::Comm::Ptr comm_, GlobalSize gne_) :
    comm(comm_), me(comm->MyPID()), np(comm->NumProc()), gne(gne_),
    first(begin(me)), last(begin(me+1))
  {}

  /// global id to processor number.
  LocalSize proc(const GlobalSize id) const {
    static LocalSize prev_p=0;
    LocalSize p=0;
    if (begin(prev_p)<=id && id<begin(prev_p+1))
      p = prev_p; // optimize for the special case of sequential ids
      // could add in the case of looping from prev_p to np?
    else
      for (; p<np; ++p) if (begin(p)<=id && id<begin(p+1)) break;
    prev_p=p;
    return p;
  }

  /// beginning global id on this processor.
  GlobalSize begin() const { return first; }

  /// beginning global id on next processor, one greater then what is local.
  GlobalSize end() const { return last; }

private:

  /// processor number to first global id on that processor.
  GlobalSize begin(const LocalSize p) const {
    return (size_t)p*(size_t)gne/(size_t)np;
  }
  const DGM::Comm::Ptr comm;  ///< parallel communicator
  const LocalSize me;         ///< my process id
  const LocalSize np;         ///< number of processors
  const GlobalSize gne;       ///< the bulk of the objects, gne/np
  const GlobalSize first;     ///< first on this processor
  const GlobalSize last;      ///< last on this processor
};

} // unnamed namespace

template <typename GlobalSize, typename LocalSize, typename Scalar>
template <typename DVector, typename LVector>
void Partition<GlobalSize,LocalSize,Scalar>::
global_scan(DVector &disp_, const LVector &len_)
{
#ifdef DGM_PARALLEL
  using DGM::global_scan;
  namespace mpi = boost::mpi;
  using std::copy;
  // needs locally owned element ids and corresponding lengths
  // produces globally consistent displacements 
  const DGM::MpiComm &mpicomm = dynamic_cast<const DGM::MpiComm &>(*comm);
  mpi::communicator bcomm(mpicomm.mpi_comm, boost::mpi::comm_attach);
  // reuse disp_, contains lengths on input, global displacements on output
  copy(len_.begin(), len_.end(), disp_.begin());
  global_scan(_eid.begin(), _eid.end(), disp_.begin(), bcomm);
#else
  // serial implementation of global_scan
  using std::partial_sum;
  partial_sum(len_.begin(), len_.end(), disp_.begin());
#endif
}

template <typename GlobalSize, typename LocalSize, typename Scalar>
template <typename myGlobalSize, typename DVector, typename LVector>
void Partition<GlobalSize,LocalSize,Scalar>::
global_scan(myGlobalSize &glen, DVector &disp_, const LVector &len_)
{
  using boost::numeric_cast;
  // new global scan (for both serial and parallel)
  global_scan(disp_, len_);
#ifdef DGM_PARALLEL
  // extra communication to get largest displacement
  namespace mpi = boost::mpi;
  const DGM::MpiComm &mpicomm = dynamic_cast<const DGM::MpiComm &>(*comm);
  mpi::communicator bcomm(mpicomm.mpi_comm, boost::mpi::comm_attach);
  glen = 0;
  myGlobalSize lmax = numeric_cast<myGlobalSize>(disp_.back()+len_.back());
  mpi::all_reduce(bcomm, &lmax, 1, &glen, mpi::maximum<myGlobalSize>());
#else
  // serial implementation of maximum displacement
  glen = numeric_cast<GlobalSize>(disp_.back()+len_.back());
#endif
}

//=============================================================================

/// Default constructor
template<typename GlobalSize, typename LocalSize, typename Scalar>
Partition<GlobalSize,LocalSize,Scalar>::
Partition(const GlobalSize global_ne, const string root,
          const DGM::Comm::Ptr comm_) :
  comm(comm_), _gne(global_ne), _ne(0), _glen(0), _nodal_glen(0)
{
  // cout<<"Partition::Partition(const int, const string)" <<endl;
#ifdef DGM_PARALLEL
  parallel_setup(_gne, root);
#else
  serial_setup(_gne);
#endif
}

/// Default constructor for serial setup (all elements on all processors)
template<typename GlobalSize, typename LocalSize, typename Scalar>
Partition<GlobalSize,LocalSize,Scalar>::
Partition(const GlobalSize global_ne, const DGM::Comm::Ptr comm_) :
  comm(comm_), _gne(global_ne), _ne(0), _glen(0), _nodal_glen(0)
{
  // cout<<"Partition::Partition(const int)" <<endl;
  serial_setup(_gne);
}

/// Copy constructor
template<typename GlobalSize, typename LocalSize, typename Scalar>
Partition<GlobalSize,LocalSize,Scalar>::
Partition(const Partition *p, bool reset_partition) :
  comm(p->comm), _gne(p->_gne), _ne(p->_ne) {
  _eid = p->_eid;
  _inc = p->_inc;
  if (!reset_partition) {
#ifdef DGM_PARALLEL
  disp.resize(p->disp.size());
  disp = p->disp;
  len.resize(p->len.size());
  len = p->len;
  _glen = p->_glen;
  nodal_disp.resize(p->nodal_disp.size());
  nodal_disp = p->nodal_disp;
  nodal_len.resize(p->nodal_len.size());
  nodal_len = p->nodal_len;
  _nodal_glen = p->_nodal_glen;
  cinfo = p->cinfo;
#endif
  }
}

/// Setup partition when running in serial
template<typename GlobalSize, typename LocalSize, typename Scalar>
void Partition<GlobalSize,LocalSize,Scalar>::
serial_setup(const GlobalSize global_ne) {
  if (global_ne < (GlobalSize)numeric_limits<LocalSize>::max() )
    _ne = (LocalSize)global_ne;
  else
     throw DGM::exception("Global number elements overflows LocalSize");
  _eid.resize(_ne);
  for (LocalSize e=0; e<ne(); ++e) _eid[e] = e;
  setup_local_id_array();
}

/// Setup partition either internal or externally defined
/** - eid(local_ne):    the global element id for each local element
    - inc(global_ne):   either the local element id or -1
*/
template<typename GlobalSize, typename LocalSize, typename Scalar>
void Partition<GlobalSize,LocalSize,Scalar>::
parallel_setup(const GlobalSize global_ne, const string root_) {
  const LocalSize me = comm->MyPID();
  root = root_;
  const int verb(comm->verbosity());
  ostringstream ss;
  ss << root << ".part." << comm->NumProc();
  string fname(ss.str());
  if(verb>1) comm->cout()<<"  Opening partition file " << fname << endl;
  ifstream fp(fname.c_str());
  if (!fp) {
    // Internal linear partition puts approximately the same number of
    // elements on each processor
    comm->cout() << "  Partition file " << fname << " not found" << endl
                 << "  Performing internal decomposition algorithm" << endl;
    if ((GlobalSize)comm->NumProc() > global_ne)
      comm->error("Number of processors > Number of elements");
    size_t start = (size_t)me*(size_t)global_ne/
      (size_t)comm->NumProc();
    size_t stop  = (size_t)(me+1)*(size_t)global_ne/
      (size_t)comm->NumProc();
    // cout << "comm->id = " << me << ", start = " << start
    //      << ", stop = " << stop << endl;
    _ne = stop - start;
    _eid.resize(ne());
    for (LocalSize e=0; e<ne(); e++) _eid[e] = start + e;
  } else {
    if (verb) comm->cout() << "  Reading partition file " << fname << endl;
    // Use externally defined partition.  This partition is typically computed
    // by Metis or a similar tool and can incorporate element weighting and
    // techniques for reducing communication overhead.  Ultimate scalability
    // is currently limited by this approach which requires reading a full
    // partition file on each mpi rank.
    /// \todo Work with in-line partitioning
    _ne = 0;
    for (GlobalSize i = 0; i < global_ne; ++i) { // find #elements in partition
      LocalSize p;
      fp >> p;
      if (p==me) _ne++;
    }
    _eid.resize(_ne);
    fp.seekg(0,ios::beg);
    for (GlobalSize i=0,j=0; i<global_ne; ++i) { // make global element index
      LocalSize p;
      fp >> p;
      if (p==me) _eid[j++] = i;
    }
  }
  if (verb>2) comm->cout() << "  setup_local_id_array" << endl;
  setup_local_id_array();
  if (verb>2) comm->cout() << "  finished setup_local_id_array" << endl;
  comm->Barrier();
  if (verb>2) comm->cout() << "  finished partition setup" << endl;
}

template<typename GlobalSize, typename LocalSize, typename Scalar>
void Partition<GlobalSize,LocalSize,Scalar>::
inline_part(const vector<Element *> &el, bool pc) {
  using std::accumulate;
  using std::copy;
  using std::find;
  using std::ostream_iterator;
  using std::sort;
  using std::swap;
  using std::unique;
  using std::vector;

  // first make a list of all the global element ids that you need
  // on this partition and, next, identify the owning processor
  vector<GlobalSize> geids;
  typename vector<GlobalSize>::iterator g_it, g_end;
  for (LocalSize i=0; i<ne(); ++i) {
    Element *E = pc ? el[i] : el[eid(i)];
    for (LocalSize j=0; j<E->nSides(); ++j) {
      if (E->side[j]->base) {                        // not a boundary side
        if (E->side[j]->link) {                      // master side
          const GlobalSize lgeid = E->side[j]->link->geid();
          if (!owns(lgeid)) geids.push_back(lgeid);
        } else {
          const GlobalSize bgeid = E->side[j]->base->geid();
          if (!owns(bgeid)) geids.push_back(bgeid);
        }
      }
    }
  }

  // remove duplicates
  sort(geids.begin(), geids.end());
  geids.erase(unique(geids.begin(), geids.end()), geids.end());

  // have list of geids whose owning processor is unknown
  int rank = comm->MyPID();
  int nprocs = comm->NumProc();

  // get owning processor for unknown gids
  vector<int> sendcounts(nprocs), recvcounts(nprocs);
  sendcounts[rank] = geids.size();
  comm->SumAll(&sendcounts[0], &recvcounts[0], nprocs);

#if 0
  cout << "rank " << rank << " recvcounts ";
  copy(recvcounts.begin(), recvcounts.end(), ostream_iterator<int>(cout, " "));
  cout << endl;
#endif

  typedef typename vector<GlobalSize>::size_type size_type;
  vector<int> displs(nprocs+1);
  for (size_type i=1; i<recvcounts.size(); ++i) {
    displs[i] = displs[i-1] + recvcounts[i-1];
    if (0 == recvcounts[i-1]) ++displs[i];
  }
  displs[nprocs] = displs[nprocs-1] + recvcounts[nprocs-1];

#if 0
  cout << "rank " << rank << " displs ";
  copy(displs.begin(), displs.end(), ostream_iterator<int>(cout, " "));
  cout << endl;
#endif

  int sum = accumulate(recvcounts.begin(), recvcounts.end(), 0);
  vector<GlobalSize> sendbuf(sum), recvbuf(sum);
  copy(geids.begin(), geids.end(), &sendbuf[displs[rank]]);

  comm->GatherAll(&sendbuf[displs[rank]], sendcounts[rank], &recvbuf[0],
                  &recvcounts[0], &displs[0]);

  // eliminate duplicates, parallel consistent buffer
  sort(recvbuf.begin(), recvbuf.end());
  recvbuf.erase(unique(recvbuf.begin(), recvbuf.end()), recvbuf.end());
  swap(sendbuf, recvbuf);

  // replace global eids with owning processor rank
  vector<GlobalSize> tmpbuf(sendbuf);
  typename vector<GlobalSize>::iterator s_it, it = _eid.begin();
  for (g_it = tmpbuf.begin(), g_end = tmpbuf.end(); g_it != g_end; ++g_it) {
    s_it = find(it, _eid.end(), *g_it);
    if (_eid.end() != s_it) {
      // we know who owns this element
      *g_it = rank;
      it = s_it;  // start search from here since data is sorted
    }
    else
      // we don't know who owns this
      *g_it = 0;
  }

  // reduce with max (get owning processor)
  recvbuf.resize(tmpbuf.size());
  // Mpi_Allreduce requires count to be signed int
  comm->MaxAll(&tmpbuf[0], &recvbuf[0], numeric_cast<int>(tmpbuf.size()));

  // update local part list with known processor ids
  typedef typename RangeMap::key_type key_type;
  it = sendbuf.begin();
  g_it = geids.begin(), g_end = geids.end();
  for (; g_it != g_end; ++g_it) {
    it = find(it, sendbuf.end(), *g_it);
    assert(sendbuf.end() != it);
    rank = recvbuf[it-sendbuf.begin()];
    _part.insert(*g_it, rank);
    assert(_part.end() != _part.find(key_type(*g_it,*g_it)));
  }
}

/// Make just the local partition map
/** This version takes an optional argument to indicated that we are doing
    parallel construction.
*/
template<typename GlobalSize, typename LocalSize, typename Scalar>
void Partition<GlobalSize,LocalSize,Scalar>::
make_myPart(const vector<Element *> &el,
            std::map<GlobalSize,LocalSize> &myPart, const bool pc)
{
  int verb(comm->verbosity());
  // if (verb) cout << comm->MyPID() << ": make_myPart" << endl;
  // first make a list of all the global element ids that you need on this
  // partition and store their location on the default partition
  DefaultPartition<GlobalSize,LocalSize> dp(comm,_gne);
  std::map<GlobalSize,LocalSize> glist;
  for (LocalSize i=0; i<ne(); i++) {
    //cout << comm->MyPID() << ": i = " << i << " eid(i) = " << eid(i) << endl;
    Element *E = pc ? el[i] : el[eid(i)];
    for (LocalSize j=0; j<E->nSides(); j++) {
      //cout << comm->MyPID() << ": j = " << j << endl;
      if (E->side[j]->base) {                        // not a boundary side
        if (E->side[j]->link) {                      // master side
          const GlobalSize lgeid = E->side[j]->link->geid();
          //cout << comm->MyPID() << ": lgeid = " << lgeid << endl;
          if (!owns(lgeid)) glist[lgeid]=dp.proc(lgeid);
        } else {
          const GlobalSize bgeid = E->side[j]->base->geid();
          //cout << comm->MyPID() << ": bgeid = " << bgeid << endl;
          if (!owns(bgeid)) glist[bgeid]=dp.proc(bgeid);
        }
      } else {
        for (size_t ss=0; ss<E->side[j]->subsides().size(); ss++) {
          Side *subside = E->side[j]->subsides()[ss].get();
          const GlobalSize sgeid = subside->base->geid();
          if (!owns(sgeid)) glist[sgeid]=dp.proc(sgeid);
        }
      }
    }
  }
  // This should be modified so that only the master reads the file
  ostringstream ss;
  ss << root << ".part." << comm->NumProc();
  string fname(ss.str());
  if(verb>1) comm->cout()<<"  Opening partition file " << fname << endl;
  ifstream fp(fname.c_str());
  if (!fp) {
    if (verb) comm->cout() << "  Partition file " << fname
                           << " not found " << endl;
    myPart = glist;
  } else {
    if (verb) comm->cout() << "  Reading partition file " << fname << endl;
    for(GlobalSize e=0; e<gne(); ++e) {
      GlobalSize p;
      fp >> p;
      typename std::map<GlobalSize,LocalSize>::const_iterator it;
      it = glist.find(e);
      if (it!=glist.end()) myPart[e] = p;
    }
  }
  //if (verb) cout << comm->MyPID() << ": completed make_myPart" << endl;
}

/// Set the partition connectivity, assumes that global side links are in place
/** \note We can use the local element ids here since in serial construction
    we have all the elements in memory on each rank.
*/
template<typename GlobalSize, typename LocalSize, typename Scalar>
void Partition<GlobalSize,LocalSize,Scalar>::
connectivity(const vector<Element*> el, bool use_zoltan) {
  //comm->cout() << "Partition::connectivity" << endl;
  std::map<GlobalSize,LocalSize> myPart;
  if (use_zoltan) {
    // populate myPart map from non-local partition map
    inline_part(el,false);
    typename RangeMap::iterator r_it = _part.begin(), r_end = _part.end();
    for (; r_it != r_end; ++r_it)
      for (typename RangeMap::element_id i=(*r_it).first.first;
           i<=(*r_it).first.second; ++i)
        myPart[i] = (*r_it).second;
    // now insert locally owned elements into _part (not into myPart)
    _part.insert(_eid.begin(), _eid.end(), comm->MyPID());
  }
  else
    make_myPart(el, myPart);

  const LocalSize np = comm->NumProc();
  const LocalSize me = comm->MyPID();
  for (LocalSize n=0; n<np; n++) { // loop over partitions
    vector< Link<GlobalSize,LocalSize> > links;
    Link<GlobalSize,LocalSize> link;
    if (n == me) continue;          // skip your own partition
    LocalSize nsides = 0;
    for (LocalSize i=0; i<ne(); i++) {
      const Element *E = el[eid(i)];
      for (LocalSize j=0; j<E->nSides(); j++) {
        if (E->side[j]->base) {                        // not a boundary side
          if (E->side[j]->link) {                      // master side
            const GlobalSize leid = E->side[j]->link->leid();
            if (!owns(leid)) {
              if (myPart.find(leid)==myPart.end()) {
                throw DGM::exception("Link Element "+asString(leid)+
                                     " on rank "+asString(me)+
                                     " not found in myPart");
              }
              if(myPart[leid] == n) {                   // in partition n
                link.set(i,j,E->side[j]->gid());
                links.push_back( link );
                nsides++;
              }
            }
          } else {                                     // slave side
            const GlobalSize beid = E->side[j]->base->leid();
            if (!owns(beid)) {
              if (myPart.find(beid)==myPart.end())
                throw DGM::exception("Base Element "+asString(beid)+
                                     " on rank "+asString(me)+
                                     " not found in myPart");
              if(myPart[beid] == n) {                   // in partition n
                link.set(i,j,E->side[j]->gid());
                links.push_back( link );
                nsides++;
              }
            }
          }
        } else {
          for (size_t ss=0; ss<E->side[j]->subsides().size(); ss++) {
            Side *subside = E->side[j]->subsides()[ss].get();
            const GlobalSize seid = subside->base->leid();
            if (!owns(seid)) {
              if (myPart.find(seid)==myPart.end())
                throw DGM::exception("c: Base Element "+asString(seid)+
                                     " on rank "+asString(comm->MyPID())+
                                     " not found in myPart.");
              if(myPart[seid] == n) {                   // in partition n
                link.set(i,j,subside->gid());
                links.push_back( link );
                nsides++;
              }
            }
          }
        }
      }
    }
    if (nsides) {  // this processor shares sides with processor n
      Connect<GlobalSize,LocalSize> C;
      cinfo.push_back(C);
      cinfo.back().nsides = nsides;
      cinfo.back().cprocid = n;
      cinfo.back().links.resize(nsides);
      // sort the connections by the global side id.  Since all partitions
      // have the same global numbering, this ensures that the connections are
      // in the same order on each processor.  This makes it easy to pack the
      // side info into a single message to send across the network.
      sort( links.begin(), links.end() );
      cinfo.back().links = links;
    }
  }
}

/// Set the partition connectivity, assumes that global side links are in place
template<typename GlobalSize, typename LocalSize, typename Scalar>
void Partition<GlobalSize,LocalSize,Scalar>::
connectivity_pc(const vector<Element*> el, bool use_zoltan) {
  //comm->cout() << "Partition::connectivity_pc" << endl;
  std::map<GlobalSize,LocalSize> myPart;
  if (use_zoltan) {
    // populate myPart map from non-local partition map
    inline_part(el,true);
    typename RangeMap::iterator r_it = _part.begin(), r_end = _part.end();
    for (; r_it != r_end; ++r_it)
      for (typename RangeMap::element_id i=(*r_it).first.first;
           i<=(*r_it).first.second; ++i)
        myPart[i] = (*r_it).second;
    // now insert locally owned elements into _part (not into myPart)
    _part.insert(_eid.begin(), _eid.end(), comm->MyPID());
  }
  else
    make_myPart(el, myPart, true);

  const LocalSize np = comm->NumProc();
  const LocalSize me = comm->MyPID();
  for (LocalSize n=0; n<np; n++) {              // loop over partitions
    vector< Link<GlobalSize,LocalSize> > links;
    Link<GlobalSize,LocalSize> link;
    if (n == me) continue;                      // skip your partition
    LocalSize nsides = 0;
    for (LocalSize i=0; i<ne(); i++) {
      Element *E = el[i];
      for (LocalSize j=0; j<E->nSides(); j++) {
        if (E->side[j]->base) {                        // not a boundary side
          if (E->side[j]->link) {                      // master side
            const GlobalSize eid = E->side[j]->link->geid();
            if (!owns(eid)) {
              if (myPart.find(eid)==myPart.end()) {
                cout << "rank " << me << " eid " << eid << " not found"
                     << std::endl;
                throw DGM::exception("Link Element not found in myPart");
              }
              if(myPart[eid] == n) {                   // in partition n
                link.set(i,j,E->side[j]->gid());
                links.push_back( link );
                nsides++;
              }
            }
          } else {                                     // slave side
            const GlobalSize eid = E->side[j]->base->geid();
            if (!owns(eid)) {
              if (myPart.find(eid)==myPart.end())
                throw DGM::exception("Base Element not found in myPart");
              if(myPart[eid] == n) {                   // in partition n
                link.set(i,j,E->side[j]->gid());
                links.push_back( link );
                nsides++;
              }
            }
          }
        } else {
          for (size_t ss=0; ss<E->side[j]->subsides().size(); ss++) {
            Side *subside = E->side[j]->subsides()[ss].get();
            const GlobalSize seid = subside->base->geid();
            if (!owns(seid)) {
              if (myPart.find(seid)==myPart.end())
                throw DGM::exception("f: Base Element "+asString(seid)+
                                     " on rank "+asString(comm->MyPID())+
                                     " not found in myPart");
              if(myPart[seid] == n) {                   // in partition n
                link.set(i,j,subside->gid());
                links.push_back( link );
                nsides++;
              }
            }
          }
        }
      }
    }
    if (nsides) {  // this processor shares sides with another
      Connect<GlobalSize,LocalSize> C;
      cinfo.push_back(C);
      cinfo.back().nsides = nsides;
      cinfo.back().cprocid = n;
      cinfo.back().links.resize(nsides);
      // sort the connections by the global side id.  Since all partitions
      // have the same global numbering, this ensures that the connections are
      // in the same order on each processor.  This makes it easy to pack the
      // side info into a single msg to send across the network.
      sort( links.begin(), links.end() );
      cinfo.back().links = links;
    }
  }
}

/// Sets up the local element id data-structure
template<typename GlobalSize, typename LocalSize, typename Scalar>
const typename Partition<GlobalSize,LocalSize,Scalar>::IncType &
Partition<GlobalSize,LocalSize,Scalar>::
setup_local_id_array() {
  if (_inc.empty()) for (LocalSize i=0; i<_ne; ++i) _inc[_eid[i]] = i;
  return _inc;
}

/// Reset the the side links for parallel execution
template<typename GlobalSize, typename LocalSize, typename Scalar>
void Partition<GlobalSize,LocalSize,Scalar>::
reset_side_links(const vector<Element*> &glob_el,
                 vector<Element*> &loc_el,
                 vector< Pcon<GlobalSize,LocalSize,Scalar> *> &pc) {
#ifdef DGM_PARALLEL
  const int verb(comm->verbosity());
  const GlobalSize global_ne = (GlobalSize)glob_el.size();
  const LocalSize local_ne = ne();
  loc_el.resize(local_ne);
  // first clone local elements
  set<LocalSize> loc_eleset;
  for (LocalSize e=0; e<local_ne; e++) {
    Element *E = glob_el[_eid[e]];
    Element *newE = E->clone();   // new element, copy of old
    newE->lid(e);                 // reset local element id
    newE->gid(E->gid());          // retain global element id
    newE->vert = E->vert;
    loc_el[e] = newE;
    for (LocalSize i=0; i<newE->nSides(); i++) {
      Side *s =  newE->side[i];
      s->elink = newE;
      for (size_t ss=0; ss<s->subsides().size(); ss++) {
        Side *subside = s->subsides()[ss].get();
        subside->elink = newE; // same for side
      }
    }
    loc_eleset.insert(newE->gid());
  }

  // reset side links (they are currently based on global mesh) when an side
  // is found that links to a neighboring partition, a new side is created to
  // serve as a buffer storage location. Pointers to these new sides are
  // stored in the pc (partition connectivity) object that is part of the
  // Field class.

  // Note that the link and base still point to the old (global) sides
  for (LocalSize e=0; e<local_ne; e++) {
    for (LocalSize i=0; i<loc_el[e]->nSides(); i++) {
      Side *side = loc_el[e]->side[i];           // shorthand symbol
      if (side->base) {                          // not a boundary side
        if (side->link) {                        // master side
          if ( owns(side->link->leid()) ) {      // local side
            side->base = side;
            const LocalSize local_id = inc(side->link->geid());
            side->link = loc_el[local_id]->side[side->link->id()];
          } else {                               // neighbor's side
            side->link       = side->link->clone();
            side->base       = 0;
            side->link->elink= 0;                // ghost element
            side->link->link = 0;
            side->link->base = side->link;
          }
        } else {                                 // slave side
          if ( owns(side->base->leid()) ) {      // local side
            const LocalSize local_id = inc(side->base->geid());
            side->base = loc_el[local_id]->side[side->base->id()];
            side->link = 0;
          } else {                               // neighbor's side
            side->link = side->base->clone();
            side->base        = 0;
            side->link->elink = 0;               // ghost element
            side->link->link  = 0;
            side->link->base = side->link;
          }
        }
      }
    }
  }
  for (LocalSize e=0; e<local_ne; e++) {
    for (LocalSize i=0; i<loc_el[e]->nSides(); i++) {
      Side *side = loc_el[e]->side[i];           // shorthand symbol
      vector<Side::Ptr> &subsides = side->subsides();
      if (!subsides.empty())  side->base = side->link = 0;
      for (size_t ss=0; ss<subsides.size(); ++ss) {
        Side::Ptr subside = subsides[ss];
        if ( owns(subside->base->geid()) ) {    // local side
          subside->link = 0;
          const LocalSize local_id = inc(subside->base->geid());
          subside->base = loc_el[local_id]->side[subside->base->id()];
          subside->base->link = subside.get();
        } else {
          subside->link = subside->base->clone();
          //subside->link->eid = subside->eid;
          subside->link->id  ( subside->id());
          subside->base       = 0;
          subside->link->link = 0;
          subside->link->base = subside->link;
          subside->link->elink = 0;            // ghost element
          side->base          = 0;
          side->link          = side->clone();
          side->link->u.resize(side->link->qtot());
        }
      }
    }
  }

#ifdef DGM_FIELD_TRANSFORM
  // Assumes that data is stored in transform space
  // loop over global elements and make the displacement vector
#ifdef DGM_CHECK_FIT_IN_GLOBALSIZE
  // SSC:  this really needs to be big
  CMC::Vector<uint64_t,GlobalSize> global_disp(global_ne);
#else
  iVector global_disp(global_ne);
#endif
  global_disp[0] = 0;
  for (GlobalSize e=1; e<global_ne; e++)
    global_disp[e] = global_disp[e-1] + glob_el[e-1]->nModes();
  // global length of data record
#ifdef DGM_CHECK_FIT_IN_GLOBALSIZE
  // SSC:  need to make sure that this can fit in GlobalSize
  uint64_t myGlen = global_disp[global_ne-1] + glob_el[global_ne-1]->nModes();
  if (verb>1) comm->cout()<<"  Modal global dof = "<<myGlen<<endl;
  if (std::numeric_limits<GlobalSize>::max() < myGlen) {
     comm->cout() <<__FILE__<<":"<<__LINE__
      <<" Error: Global sum of modes exceeded GlobalSize."<<std::endl
      <<" Error: Global sum of modes:"<<myGlen            <<std::endl
      <<" Error: GlobalSize:"<<std::numeric_limits<GlobalSize>::max()<<std::endl
      <<" Error: Mesh is too large. Either decrease p-order, "<<std::endl
      <<" Error: mesh size or compile with 64 bit integers.  "<<std::endl;
     comm->cerr() <<__FILE__<<":"<<__LINE__
      <<" Error: Global sum of modes exceeded GlobalSize."<<std::endl
      <<" Error: Global sum of modes:"<<myGlen            <<std::endl
      <<" Error: GlobalSize:"<<std::numeric_limits<GlobalSize>::max()<<std::endl
      <<" Error: Mesh is too large. Either decrease p-order, "<<std::endl
      <<" Error: mesh size or compile with 64 bit integers.  "<<std::endl;
  }
  _glen = numeric_cast<GlobalSize>(myGlen);
#else
  _glen = global_disp[global_ne-1] + glob_el[global_ne-1]->nModes();
#endif
  // localize
  disp.resize(local_ne);
  len.resize(local_ne);
  for (LocalSize e=0; e<local_ne; e++) {  // loop over local elements
    disp[e] = numeric_cast<GlobalSize>(global_disp[_eid[e]]);
    len[e]  = loc_el[e]->nModes();
  }
#else
  // Assumes data is stored in physical space
  // loop over global elements and make the displacement vector
  iVector global_disp(global_ne);
  global_disp[0] = 0;
  for (GlobalSize e=1; e<global_ne; e++)
    global_disp[e] = global_disp[e-1] + glob_el[e-1]->qtot;
  // global length of data record
  _glen = global_disp[global_ne-1] + glob_el[global_ne-1]->qtot;
  // localize
  disp.resize(ne());
  len.resize(ne());
  for (LocalSize e=0; e<ne(); e++) {
    disp[e] = global_disp[_eid[e]];
    len[e]  = loc_el[e]->qtot;
  }
#endif

  // Sometimes one also may need partition information in physical space
  // Assumes data is stored in physical space
  // loop over global elements and make the displacement vector
  global_disp[0] = 0;
  for (GlobalSize e=1; e<global_ne; e++)
    global_disp[e] = global_disp[e-1] + glob_el[e-1]->qtot;
  // global length of data record
#ifdef DGM_CHECK_FIT_IN_GLOBALSIZE
  // SSC:  need to make sure that this can fit in GlobalSize
  uint64_t myNodalGlen = global_disp[global_ne-1] + glob_el[global_ne-1]->qtot;
  if (verb>1) comm->cout()<<"  Nodal global dof = "<<myGlen<<endl;
  if (std::numeric_limits<GlobalSize>::max() < myGlen) {
     comm->cout() <<__FILE__<<":"<<__LINE__
      <<" Error: Global sum of modes exceeded GlobalSize."<<std::endl
      <<" Error: Global sum of modes:"<<myGlen            <<std::endl
      <<" Error: GlobalSize:"<<std::numeric_limits<GlobalSize>::max()<<std::endl
      <<" Error: Mesh is too large. Either decrease p-order, "<<std::endl
      <<" Error: mesh size or compile with 64 bit integers.  "<<std::endl;
     comm->cerr() <<__FILE__<<":"<<__LINE__
      <<" Error: Global sum of modes exceeded GlobalSize."<<std::endl
      <<" Error: Global sum of modes:"<<myGlen            <<std::endl
      <<" Error: GlobalSize:"<<std::numeric_limits<GlobalSize>::max()<<std::endl
      <<" Error: Mesh is too large. Either decrease p-order, "<<std::endl
      <<" Error: mesh size or compile with 64 bit integers.  "<<std::endl;
  }
  _nodal_glen = numeric_cast<GlobalSize>(myNodalGlen);
#else
  _nodal_glen = global_disp[global_ne-1] + glob_el[global_ne-1]->qtot;
#endif
  // localize
  nodal_disp.resize(local_ne);
  nodal_len.resize(local_ne);
  for (LocalSize e=0; e<local_ne; e++) {
    nodal_disp[e] = numeric_cast<GlobalSize>(global_disp[_eid[e]]);
    nodal_len[e]  = loc_el[e]->qtot;
  }

  // delete global element storage
  for (GlobalSize e=0; e<global_ne; e++) delete glob_el[e];

  // Make pc data structure and make side storage contiguous
  pc.clear();
  for (size_t n=0; n<cinfo.size(); n++) {
    pc.push_back( new Pcon<GlobalSize,LocalSize,Scalar> );
    // make sdof uint64_t but check later as it has to fit in LocalSize
    uint64_t sdof = 0;           // side degrees of freedom in connection
    for (LocalSize i=0; i<cinfo[n].nsides; i++) {
      const GlobalSize elmtid = cinfo[n].links[i].elmtid;
      const LocalSize sideid = cinfo[n].links[i].sideid;
      const GlobalSize sidegid= cinfo[n].links[i].sidegid;
      const Side *s=loc_el[elmtid]->side[sideid];
      if (s->subsides().empty()) {
        sdof += s->qtot();
        pc[n]->side.push_back( s->link );
      } else {
        for (size_t j=0; j<s->subsides().size(); ++j) {
          const Side *ss = s->subsides()[j].get();
          if (ss->gid() == sidegid) {
            sdof += ss->qtot();
            pc[n]->side.push_back( ss->link );
            if (!ss->link) comm->error("Communication link NULL.");
            break;
          }
        }
      }
    }
    // make contiguous space for partition sides of size sdof
    // making sure that it fits in LocalSize
    pc[n]->len = numeric_cast<LocalSize>(sdof);
    pc[n]->buf.resize(pc[n]->len);
    pc[n]->sbuf.resize(pc[n]->len);  // the send buffer
    LocalSize start = 0;
    for (LocalSize i=0; i< cinfo[n].nsides; i++) {
      pc[n]->side[i]->u.alias( pc[n]->buf, start, pc[n]->side[i]->qtot() );
      start += pc[n]->side[i]->qtot();
    }
  }
#ifdef DGM_PARTITION_VERBOSE
  cout << "Number of elements: " << loc_el.size() << endl;
  if (comm->Master())
    for (LocalSize e=0; e<local_ne; e++) cout << *(loc_el[e]) << endl;
#endif
  if (verb>2) comm->cout()<<"Finished Partition::reset_side_links()"<<endl;
#endif
}

/// Reset the the side links for parallel execution
template<typename GlobalSize, typename LocalSize, typename Scalar>
void Partition<GlobalSize,LocalSize,Scalar>::
reset_side_links(vector<Element*> &el,
                 vector<Pcon<GlobalSize,LocalSize,Scalar> *> &pc,
                 bool use_zoltan){
#ifdef DGM_PARALLEL
  const int verb(comm->verbosity());
  Element *E;
  vector<Element*> new_el(ne());
  for (LocalSize e=0; e<ne(); e++) {
    E = new_el[e] = el[e]->clone();  // new element is copy of old
    assert( el[e]->lid() == e );
    E->lid( e );                     // set local element id to local eid
    E->gid( el[e]->gid() );          // set global element id
    for (LocalSize i=0; i<E->nSides(); i++) {
      E->side[i]->elink = E; // same for side
      for (size_t ss=0; ss<E->side[i]->subsides().size(); ss++) {
        Side *subside = E->side[i]->subsides()[ss].get();
        subside->elink = E;
      }
    }
  }
  // reset side links (they are currently based on global mesh) when an side
  // is found that links to a neighboring partition, a new side is created to
  // serve as a buffer storage location. Pointers to these new sides are
  // stored in the pc (partition connectivity) object that is part of the
  // Field class.

  // inc is either -1 or the local element id (this is already done)
  // setup_local_id_array();
  for (LocalSize e=0; e<ne(); e++) {
    for (LocalSize i=0; i<new_el[e]->nSides(); i++) {
      Side *side = new_el[e]->side[i];           // shorthand symbol
      if (side->base) {                          // not a boundary side
        if (side->link) {                        // master side
          if ( owns(side->link->geid()) ) {      // local side
            side->base = side;
            const Element * E = new_el[inc(side->link->geid())];
            side->link = E->side[side->link->id()];
          } else {                               // neighbor's side
            side->link       = side->link->clone();
            side->base       = 0;
            side->link->link = 0;
            side->link->base = side->link;
            side->link->elink= new_el[e];
          }
        } else {                                 // slave side
          if ( owns(side->base->geid()) )  {     // local side
            const LocalSize local_id = inc(side->base->geid());
            side->base = new_el[local_id]->side[side->base->id()];
            side->link = 0;
          } else {                               // neighbor's side
            side->link       = side->base->clone();
            side->base       = 0;
            side->link->link = 0;
            side->link->elink= new_el[e];
            side->link->base = side->link;
          }
        }
      } else {
        if (side->link) side->link->elink = 0;
      }
    }
  }
  for (LocalSize e=0; e<ne(); e++) {
    for (LocalSize i=0; i<new_el[e]->nSides(); i++) {
      Side *side = new_el[e]->side[i];           // shorthand symbol
      vector<Side::Ptr> &subsides = side->subsides();
      if (!subsides.empty())  side->base = side->link = 0;
      for (size_t ss=0; ss<subsides.size(); ++ss) {
        Side::Ptr subside = subsides[ss];
        if (subside->base) {
          if ( owns(subside->base->geid()) ) {   // local side
            const LocalSize local_id = inc(subside->base->geid());
            Side *nbrside = new_el[local_id]->side[subside->base->id()];
            subside->link = 0;
            subside->base = nbrside;
            nbrside->link = subside.get();
            nbrside->base = nbrside;
          } else {
            Side *nbrside = subside->base->clone();
            nbrside->geid(subside->geid());
            nbrside->id  ( subside->id());
            nbrside->link = 0;
            nbrside->base = nbrside;
            subside->link = nbrside;
            subside->base = 0;
            subside->link->elink= new_el[e];
            side->base = 0;
            side->link = side->clone();
            side->link->u.resize(side->link->qtot());
          }
        } else {
          if (subside->link) subside->link->elink = 0;
        }
      }
    }
  }

#ifdef DGM_CHECK_FIT_IN_GLOBALSIZE
  // SSC:  This version uses uint64_t for all global displacements and then
  // carefully downcasts this to GlobalSize.  It will throw an exception if
  // things don't fit in GlobalSize.
  CMC::Vector<uint64_t,LocalSize> myDisp(ne());
  disp.resize(ne());
  len.resize(ne());
  disp[0] = 0;
  myDisp[0] = 0;
#ifdef DGM_FIELD_TRANSFORM
  // Assumes that data is stored in transform space. Loop over local elements
  // and make the length vector
  for (LocalSize e=0; e<ne(); e++) len[e] = new_el[e]->nModes();
#else
  // Assumes data is stored in physical space. Loop over global elements and
  // make the length vector
  for (LocalSize e=0; e<ne(); e++) len[e] = new_el[e]->qtot;
#endif
  // Now use global scan to compute global displacements and
  // global length of data record
  if (verb>1) comm->cout()<<"  Global scan for modal displacements"<<endl;
  uint64_t myGlen;
  global_scan(myGlen, myDisp, len);
  if (verb>1) comm->cout()<<"  Modal global dof = "<<myGlen<<endl;
  if (std::numeric_limits<GlobalSize>::max() < myGlen) {
     comm->cout() <<__FILE__<<":"<<__LINE__
      <<" Error: Global sum of modes exceeded GlobalSize."<<std::endl
      <<" Error: Global sum of modes:"<<myGlen            <<std::endl
      <<" Error: GlobalSize:"<<std::numeric_limits<GlobalSize>::max()<<std::endl
      <<" Error: Mesh is too large. Either decrease p-order, "<<std::endl
      <<" Error: mesh size or compile with 64 bit integers.  "<<std::endl;
     comm->cerr() <<__FILE__<<":"<<__LINE__
      <<" Error: Global sum of modes exceeded GlobalSize."<<std::endl
      <<" Error: Global sum of modes:"<<myGlen            <<std::endl
      <<" Error: GlobalSize:"<<std::numeric_limits<GlobalSize>::max()<<std::endl
      <<" Error: Mesh is too large. Either decrease p-order, "<<std::endl
      <<" Error: mesh size or compile with 64 bit integers.  "<<std::endl;
  }
  _glen = numeric_cast<GlobalSize>(myGlen);
  for (LocalSize e=0; e<ne(); ++e)
    disp[e] = numeric_cast<GlobalSize>(myDisp[e]);

  // Sometimes one also may need partition information in physical space
  // Assumes data is stored in physical space loop over global elements and
  // make the length vector
  nodal_disp.resize(ne());
  nodal_len.resize(ne());
  nodal_disp[0] = 0;
  myDisp[0] = 0;
  for (LocalSize e=0; e<ne(); e++) nodal_len[e] = new_el[e]->qtot;
  // Now use global scan to compute the global displacements and
  // global length of data record
  if(verb>1) comm->cout()<<"  Global scan for nodal displacements"<<endl;
  global_scan(myGlen, myDisp, nodal_len);
  if (verb>1) comm->cout()<<"  Nodal global dof = "<<myGlen<<endl;
  _nodal_glen = numeric_cast<GlobalSize>(myGlen);
  for (LocalSize e=0; e<ne(); ++e)
    nodal_disp[e] = numeric_cast<GlobalSize>(myDisp[e]);
#else
  disp.resize(ne());
  len.resize(ne());
  disp[0] = 0;
#ifdef DGM_FIELD_TRANSFORM
  // Assumes that data is stored in transform space. Loop over local elements
  // and make the length vector
  for (LocalSize e=0; e<ne(); e++) len[e] = new_el[e]->nModes();
#else
  // Assumes data is stored in physical space. Loop over global elements and
  // make the length vector
  for (LocalSize e=0; e<ne(); e++) len[e] = new_el[e]->qtot;
#endif
  // Now use global scan to compute global displacements and
  // global length of data record
  if (comm->verbosity()>1)
    comm->cout() << "  Global scan for modal displacements" << endl;
  global_scan(_glen, disp, len);

  // Sometimes one also may need partition information in physical space
  // Assumes data is stored in physical space loop over global elements and
  // make the length vector
  nodal_disp.resize(ne());
  nodal_len.resize(ne());
  nodal_disp[0] = 0;
  for (LocalSize e=0; e<ne(); e++) nodal_len[e] = new_el[e]->qtot;
  // Now use global scan to compute the global displacements and
  // global length of data record
  if(comm->verbosity()>1)
    comm->cout() << "  Global scan for nodal displacements" << endl;
  global_scan(_nodal_glen, nodal_disp, nodal_len);
#endif

  // delete old element storage
  for (LocalSize e=0; e<ne(); e++) delete el[e];

  // replace old Element* vector with the new
  el = new_el;

  // Make pc data-structure and make side storage contiguous
  pc.clear();
  for (size_t n=0; n<cinfo.size(); n++) {
    pc.push_back( new Pcon<GlobalSize,LocalSize,Scalar> );
    // make sdof uint64_t but make sure that it fits in LocalSize later
    uint64_t sdof = 0;         // side degrees of freedom in connection
    for (LocalSize i=0; i< cinfo[n].nsides; i++) {
      const GlobalSize elmtid = cinfo[n].links[i].elmtid;
      const LocalSize  sideid = cinfo[n].links[i].sideid;
      const GlobalSize sidegid = cinfo[n].links[i].sidegid;
      const Side *s = el[elmtid]->side[sideid];
      if (s->subsides().empty()) {
        sdof += s->qtot();
        pc[n]->side.push_back( s->link );
      } else {
        for (size_t j=0; j<s->subsides().size(); ++j) {
          const Side *ss = s->subsides()[j].get();
          if (ss->gid() == sidegid) {
            sdof += ss->qtot();
            pc[n]->side.push_back( ss->link );
            if (!ss->link) comm->error("Communication link NULL.");
            break;
          }
        }
      }
    }
    // make contiguous space for partition sides of size sdof
    pc[n]->len = numeric_cast<LocalSize>(sdof);
    pc[n]->buf.resize(pc[n]->len);
    pc[n]->sbuf.resize(pc[n]->len);  // the send buffer
    LocalSize start = 0;
    for (LocalSize i=0; i< cinfo[n].nsides; i++) {
      pc[n]->side[i]->u.alias( pc[n]->buf, start, pc[n]->side[i]->qtot() );
      start += pc[n]->side[i]->qtot();
    }
  }
#ifdef DGM_PARTITION_VERBOSE
  cout << "Number of elements: " << el.size() << endl;
  if (comm->Master()) for (LocalSize e=0; e<ne; e++) cout << *(el[e]) << endl;
#endif
  if (verb>2) comm->cout()<<"Finished Partition::reset_side_links"<<endl;
#endif
}

#ifdef DGM_USE_ZOLTAN
/// Update the partition using Zoltan
/** \note This appears to be limited to int sized objects so watch out for
 *  large problems.
 */
template <typename GlobalSize, typename LocalSize, typename Scalar>
template <typename Iterator>
void Partition<GlobalSize,LocalSize,Scalar>::update(Iterator it, Iterator end) {
#ifdef DGM_PARALLEL
  using std::accumulate;
  using std::find;
  using std::ostream_iterator;
  using std::pair;
  using std::sort;
  using std::stable_sort;
  using std::unique;
  using std::vector;

  typedef typename iterator_traits<Iterator>::value_type vt;
  typedef vector<vt> container;
  typedef typename container::size_type size_type;
  typedef typename container::iterator iterator;

  int rank = comm->MyPID();
  size_type nprocs = comm->NumProc();

  _part.clear();
  cinfo.clear();

#if 0
  cout << "rank " << rank << " sends to rank(s) ";
  copy(it, end, ostream_iterator<Ordinal>(cout, " "));
  cout << endl;
#endif

  // get counts and ranks of whom I send data to, excluding myself
  container send_ranks(it, end);
  sort(send_ranks.begin(), send_ranks.end());
  send_ranks.erase(unique(send_ranks.begin(), send_ranks.end()),
                   send_ranks.end());
  typename container::iterator ite = find(send_ranks.begin(),
    send_ranks.end(), rank);
  if (ite != send_ranks.end()) send_ranks.erase(ite);

#if 0
  cout << "rank " << rank << " send_ranks ";
  copy(send_ranks.begin(), send_ranks.end(), ostream_iterator<vt>(cout, " "));
  cout << endl;
#endif

  size_type s = send_ranks.size();
  container sendcounts(nprocs);
  sendcounts[rank] = s;

  // get global sum of interprocessor send counts
  vector<typename iterator_traits<Iterator>::value_type> recvcounts(nprocs);
  comm->SumAll(&sendcounts[0], &recvcounts[0], nprocs);

#if 0
  cout << "rank " << rank << " recvcounts ";
  copy(recvcounts.begin(), recvcounts.end(), ostream_iterator<vt>(cout, " "));
  cout << endl;
#endif

  // sum number of exchanges and allocate so get communication pattern
  s = accumulate(recvcounts.begin(), recvcounts.end(), 0);
  container receive_ranks(s < nprocs ? nprocs : s);

  // find my rank's insertion point and copy recipients rank into send buffer
  container rdispls(nprocs+1);
  for (size_type i=1; i<recvcounts.size(); ++i) {
    rdispls[i] = rdispls[i-1] + recvcounts[i-1];
  }
  rdispls[nprocs] = rdispls[nprocs-1] + recvcounts[nprocs-1];

  // get ranks of data senders
  comm->GatherAll(&send_ranks[0], sendcounts[rank], &receive_ranks[0],
                  &recvcounts[0], &rdispls[0]);

#if 0
  cout << "rank " << rank << " receive_ranks ";
  copy(receive_ranks.begin(), receive_ranks.end(),
       ostream_iterator<Ordinal>(cout, " "));
  cout << endl;
#endif

  // group global ids by rank
  vector< pair<GlobalSize,LocalSize> > tmp(_ne);
  Iterator its = it;
  for (LocalSize i=0; i<_ne; ++i, ++its) {
    pair<GlobalSize,LocalSize> pii(*its,_eid[i]);
    tmp[i] = pii;
  }
  stable_sort(tmp.begin(), tmp.end());

  // get number of elements on each processor
  vector<LocalSize> sendcount(nprocs);
  for (; it != end; ++it)
    if (rank != *it) ++sendcount[*it];

#if 0
  cout << "rank " << rank << " rdispls ";
  copy(rdispls.begin(), rdispls.end(), ostream_iterator<Ordinal>(cout, " "));
  cout << endl;
#endif

  // convert send ranks to receive ranks
  iterator rrit = receive_ranks.begin();
  for (size_type i=0,j=0; i<receive_ranks.size(); ++i) {
    if (size_type(rdispls[j+1]) <= i) ++j;
    if (rank == receive_ranks[i] && 0 < recvcounts[j]) {
      *rrit = j;   // i'm receiving from rank j
      ++rrit;
    }
  }
  receive_ranks.erase(rrit, receive_ranks.end());

#if 0
  cout << "rank " << rank << " local receive_ranks ";
  copy(receive_ranks.begin(), receive_ranks.end(),
       ostream_iterator<Ordinal>(cout, " "));
  cout << endl;
#endif

  // send number of elements from each processor
  int tag = 971;
  for (size_type i=0; i<receive_ranks.size(); ++i)
    comm->iReceive(tag, &recvcounts[i], 1, receive_ranks[i]);
  for (int i=0; i<sendcounts[rank]; ++i)
    comm->iSend(tag, &sendcount[send_ranks[i]], 1, send_ranks[i]);
  comm->WaitAll();

  // populate sendbuf with element ids
  vector<LocalSize> sendbuf(_ne);
  for (LocalSize i=0,k=0; i<_ne; ++i)
    for (LocalSize j=0; j<(LocalSize)sendcounts[rank]; ++j)
      if (i<_ne && (LocalSize)send_ranks[j] == tmp[i].first) {
        while (i<_ne && (LocalSize)send_ranks[j] == tmp[i].first) {
          sendbuf[k] = tmp[i].second;
          _eid.erase(find(_eid.begin(), _eid.end(), sendbuf[k]));
          ++k; ++i;
        }
        --i;
      }

  // allocate and send elements to recipient rank
  int sum = accumulate(recvcounts.begin(), recvcounts.begin()+
                       receive_ranks.size(), 0);
  vector<GlobalSize> recvbuf(sum);
  tag = 972;
  for (size_type i=0,j=0; i<receive_ranks.size(); ++i) {
    comm->iReceive(tag, &recvbuf[j], recvcounts[i], receive_ranks[i]);
    j += recvcounts[i];
  }
  for (int i=0,j=0; i<sendcounts[rank]; ++i) {
    comm->iSend(tag, &sendbuf[j], sendcount[send_ranks[i]], send_ranks[i]);
    j += sendcount[send_ranks[i]];
  }
  comm->WaitAll();

  // recvbuf contains global element ids
  _eid.insert(_eid.end(), recvbuf.begin(), recvbuf.end());
  _ne = _eid.size();

  // check if any processor ends up with zero elements
  const int n = boost::numeric_cast<int>(_ne);
  comm->GatherAll(&n, &recvcounts[0], 1);
  for (size_type i=0; i<recvcounts.size(); ++i)
    if (0 == recvcounts[i]) {
      throw DGM::exception("Processor rank "+asString(i)+
                           " ends up with no elements.");
    }

  sort(_eid.begin(), _eid.end());
  // setup local links
  _inc.clear();
  setup_local_id_array();
#endif   // DGM_PARALLEL
}
#endif   // DGM_USE_ZOLTAN

#undef DGM_CHECK_FIT_IN_GLOBALSIZE

} // namespace DGM
