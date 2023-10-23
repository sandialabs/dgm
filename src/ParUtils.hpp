#ifndef DGM_EXPORTER_HPP
#define DGM_EXPORTER_HPP

/** \file ParUtils.hpp
    \brief Export data from source to target layout
    \author Axel Gerstenberger
*/

// system includes
#include <vector>
#include <map>
#include <set>

#ifdef DGM_USE_GENERAL_GHOSTING
#ifdef DGM_USE_EPETRA
#include <Epetra_Map.h>
#include <Epetra_Comm.h>
#include <Teuchos_RCP.hpp>

// DGM includes
#include "Comm.hpp"
#ifdef DGM_PARALLEL
#include "MpiComm.hpp"
#else
#include "SerialComm.hpp"
#endif

// boost serialization
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/vector.hpp>
#include "boost/serialization/map.hpp"
#include "boost/serialization/string.hpp"
#include "boost/serialization/set.hpp"
#include "boost/archive/binary_iarchive.hpp"
#include "boost/archive/binary_oarchive.hpp"
#include "boost/static_assert.hpp"

#ifdef DGM_PARALLEL
// boost mpi
#include <boost/mpi/environment.hpp>
#include <boost/mpi/communicator.hpp>
#include <boost/mpi/collectives.hpp>
#endif

namespace DGM {

/// attach a boost::mpi::communicator view on existing DGM::Comm
#ifdef DGM_PARALLEL
static boost::mpi::communicator attach_boost_communicator(
    const DGM::Comm& dgm_comm ///< existing DGM::Comm communicator
    ) {
  const DGM::MpiComm &dgm_mpicomm =
    dynamic_cast<const DGM::MpiComm &>(dgm_comm);
  boost::mpi::communicator bcomm(dgm_mpicomm.mpi_comm,
                                 boost::mpi::comm_attach);
  return bcomm;
};
#endif

/*!
 * \brief Export data from source to target layout
 *
 * This class takes a source and a target map as input and computes a
 * communication pattern, how data has to be send from source to target procs.
 * The Export method can then redistribute anything serializable that has some
 * kind of global id (for instance elements, vertices, sides, etc. ).
 */
class Exporter {
public:
  /// Standard Constructor
  Exporter(
      const Epetra_Map& sourcemapIn, ///< The source map to be exported from
      const Epetra_Map& targetmapIn, ///< The target map to be exported to
      const DGM::Comm& dgm_comm_In   ///< Input DGM::Comm
  ) :
    sourcemap(sourcemapIn),
    targetmap(targetmapIn),
    dgm_comm(dgm_comm_In)
#ifdef DGM_PARALLEL
  , boost_comm(attach_boost_communicator(dgm_comm_In))
#endif
  {
    construct_exporter();
    return;
  };

  /// Copy Constructor
  Exporter(const DGM::Exporter& old) :
    sourcemap(old.sourcemap),
    targetmap(old.targetmap),
    dgm_comm(old.dgm_comm),
#ifdef DGM_PARALLEL
    boost_comm(old.boost_comm),
#endif
    sendpattern(old.sendpattern) {
    return;
  };

  /// Destructor
  ~Exporter()
  {
    return;
  };

  //! @name Communication methods

  /** export map of things (includes POD, pointers, STL container)
   *
   * @warning This method does not work for objects that don't have a proper
   * copy constructor, because all data omitted in the copy constructor
   * -- or where only a shallow copy or reference to data is copied -- is lost,
   *  when putting the objects into the std::map.
   *
   * @tparam Ordinal global ordinal type
   */
  template <class Ordinal, class Data>
  void Export(
      std::map<Ordinal,Data>& datamap
      ) const {
    if (sendpattern.size()==0) return;

    typedef std::map<Ordinal,Data> mymap;
    using namespace std;

    // the send/recv loop
    for (int iproc=0; iproc<get_Epetra_Comm().NumProc()-1; ++iproc) {
      const int tproc = get_target_proc(iproc);

      // gather all objects to be send
      mymap senddata;
      for (set<int>::const_iterator i=sendpattern[tproc].begin();
          i!=sendpattern[tproc].end(); ++i) {
        const int gid = *i;
        typename mymap::const_iterator curr = datamap.find(gid);
        if (curr!=datamap.end()) {
          senddata[gid] = curr->second;
        }
      }

      // transfer data using MPI
      mymap recvdata;
#ifdef DGM_PARALLEL
      namespace mpi = boost::mpi;
      // send (Boost magic: we serialize the map directly before send!!!)
      mpi::request sendrequest = get_boost_comm().isend(tproc, 1, senddata);
      // receive
      mpi::status p = get_boost_comm().probe(boost::mpi::any_source, 1);
      //mpi::status r = get_boost_comm().recv(p.source(), p.tag(), recvdata);
      get_boost_comm().recv(p.source(), p.tag(), recvdata);
      // wait until the communication associated with this request has completed
      sendrequest.wait();
      // make sure we don't get mixed up messages (we use wild card receives)
      get_boost_comm().barrier();
#else
      recvdata = senddata;
#endif

      // put datamap back into map, if they don't exists
      for (typename mymap::const_iterator i=recvdata.begin();
          i!=recvdata.end(); ++i) {
        const int gid = i->first;
        // sanity check of sendplan: if gid is already present, it should not
        // have been send at all
        assert(datamap.find(gid) == datamap.end());
        datamap[gid] = i->second;
      }
    }

    // cleanup entries that are not in my target map
    for (typename mymap::const_iterator i=datamap.begin();
        i != datamap.end(); ++i) {
      const int gid = i->first;
      if (TargetMap().MyGID(gid) == false) {
        datamap.erase(gid);
        // at the moment, we just add more data, we don't erase them
        dgm_comm.exit(-1);
      }
    }
    return;
  }

  /** export map of things, serialize to string and send string via MPI
   *
   * @note Some classes, the major candidate being the DGM::Element, give weird
   * errors, if directly serialized to an MPI stream. The most likely reason for
   * that behavior is that there are subtle differences between the boost
   * binary archive and boost MPI archive. This methods first serializes the
   * objects to a string (char array) and then sends this string via boost::mpi.
   * The observed behavior is identical to Exporter::Export.
   *
   * @warning This method does not work for objects that don't have a proper
   * copy constructor, because all data omitted in the copy constructor
   * -- or where only a shallow copy or reference to data is copied -- is lost,
   *  when putting the objects into the std::map.
   *
   * @tparam Ordinal global ordinal type
   */
  template <class Ordinal, class Data>
  void ExportViaStrings(std::map<Ordinal,Data>& datamap) const {
    if (sendpattern.size()==0) return;

    typedef std::map<Ordinal,Data> mymap;
    using namespace std;

    // the send/recv loop
    for (int iproc=0; iproc<get_Epetra_Comm().NumProc()-1; ++iproc) {
      const int tproc = get_target_proc(iproc);

      // gather all objects to be send
      mymap senddata;
      for (set<int>::const_iterator i=sendpattern[tproc].begin();
          i!=sendpattern[tproc].end(); ++i) {
        const int gid = *i;
        typename mymap::const_iterator curr = datamap.find(gid);
        if (curr!=datamap.end()) {
          assert(curr->second != NULL);
          senddata[gid] = curr->second;
        }
      }

      // serialize
      std::ostringstream sendstream;
      {
        boost::archive::binary_oarchive oar(sendstream);
        oar << senddata;
      }

      // transfer data using MPI
      string recvstring;
      send_and_receive(sendstream.str(), tproc, recvstring);

      // deserialize
      mymap recvdata;
      {
        std::istringstream recvstream(recvstring);
        boost::archive::binary_iarchive iar(recvstream);
        iar >> recvdata;
      }

      // put elements back into map, if they don't exists
      for (typename mymap::const_iterator i=recvdata.begin();
          i!=recvdata.end(); ++i) {
        const int gid = i->first;
        // sanity check of sendplan: if gid is already present, it should not
        // have been send at all
        assert(datamap.find(gid) == datamap.end());
        datamap[gid] = i->second;
      }
    }

    // cleanup stuff that is not in my target map
    typename mymap::const_iterator eleiter;
    for (eleiter=datamap.begin(); eleiter != datamap.end(); ++eleiter) {
      if (TargetMap().MyGID(eleiter->first) == false) {
        datamap.erase(eleiter->first);
        cout << eleiter->first;
        dgm_comm.error(
            "at the moment, we just add more elements, we don't erase them");
      }
    }
    return;
  }

private:

  //! @name Access methods

  /// get const view on source map
  const Epetra_Map& SourceMap() const { return sourcemap; }
  /// get const view on target map
  const Epetra_Map& TargetMap() const { return targetmap; }
  /// get const view on a Epetra_Comm
  const Epetra_Comm& get_Epetra_Comm() const { return sourcemap.Comm(); }
#ifdef DGM_PARALLEL
  /// get const view on boost communicator
  const boost::mpi::communicator& get_boost_comm() const { return boost_comm; }
#endif
  //@}

  /// non-blocking communication of data
  void send_and_receive(
      const string& sendblock,
      const int tproc,
      string& recvblock
  ) const {
#ifdef DGM_PARALLEL
    namespace mpi = boost::mpi;

    // send
    mpi::request sendrequest = get_boost_comm().isend(tproc, 1, sendblock);

    // receive
    mpi::status p = get_boost_comm().probe(boost::mpi::any_source, 1);
    //mpi::status r = get_boost_comm().recv(p.source(), p.tag(), recvblock);
    get_boost_comm().recv(p.source(), p.tag(), recvblock);

    // wait for messages to tproc to leave
    sendrequest.wait();

    // make sure we don't get mixed up messages (we use wild card receives)
    get_boost_comm().barrier();
#else
    recvblock = sendblock;
#endif
  }

  //@}

  /// construct parallel send receive plan based on source and target maps
  void construct_exporter();

  /// give me the target processor, when looping over all other processors
  int get_target_proc(const int iproc) const {
    int tproc = get_Epetra_Comm().MyPID()+1+iproc;
    if (tproc<0)
      tproc += get_Epetra_Comm().NumProc();
    if (tproc>get_Epetra_Comm().NumProc()-1)
      tproc -= get_Epetra_Comm().NumProc();
    return tproc;
  }

  /// give me the source processor, when looping over all other processors
  int get_source_proc(const int iproc) const {
    int sproc = get_Epetra_Comm().MyPID()-1-iproc;
    if (sproc<0)
      sproc += get_Epetra_Comm().NumProc();
    if (sproc>get_Epetra_Comm().NumProc()-1)
      sproc -= get_Epetra_Comm().NumProc();
    return sproc;
  }

  const Epetra_Map&  sourcemap; ///< const view on given source map
  const Epetra_Map&  targetmap; ///< const view on given target map
  const DGM::Comm&   dgm_comm;  ///< const view on existing DGM communicator
#ifdef DGM_PARALLEL
  /// const view on existing DGM::Comm
  const boost::mpi::communicator boost_comm;
#endif

  /** \brief For each processor p, sendpattern has a list of owned GIDs
   *  that he wants to send to p.
   *
   *  @note I never sends stuff to myself, e.g. if I am processor 3
   *  (the 4th proc), then sendpattern[3] should be an empty set
   *  (this condition is enforced using std::assert)!
    */
  std::vector<std::set<int> >  sendpattern;

};

/** \brief make sets of overlapping GIDs unique
 *
 * @tparam Ordinal ordinal type used for global ids
 * @note there could be a balancing issue
*/
template<typename Ordinal>
void make_unique(
    const DGM::Comm&   dgm_comm,  ///< Input DGM::Comm
    std::set<Ordinal>& gidset     ///< global IDs per processor
) {
#ifdef DGM_PARALLEL
  namespace mpi = boost::mpi;

  mpi::communicator boostComm = DGM::attach_boost_communicator(dgm_comm);

  // the send/recv loop
  for (int iproc=0; iproc<dgm_comm.NumProc(); ++iproc) {

    // transfer data using MPI
    std::set<int> recvgidset;
    if (iproc == dgm_comm.MyPID()) {
      recvgidset = gidset;
    }
    mpi::broadcast(boostComm, recvgidset, iproc);

    // delete GIDs, if the broadcasting iproc owns them
    for (std::set<int>::const_iterator i=recvgidset.begin();
        i!=recvgidset.end(); ++i) {
      const int gid = *i;
      if (gidset.find(gid) != gidset.end() and iproc != dgm_comm.MyPID()) {
        gidset.erase(gid);
      }
    }
  }
#else
  return;
#endif
}

}  // namespace DGM

#endif // DGM_USE_EPETRA
#endif // DGM_USE_GENERAL_GHOSTING
#endif // DGM_EXPORTER_HPP
