#ifndef DGM_RUNTIME_CONTROL_HPP
#define DGM_RUNTIME_CONTROL_HPP

/** \file RuntimeControl.hpp
    \brief Provides a mechanism to alter some parameters during runtime
    \author Scott Collis
*/

// system libraries
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <string>
#include <cmath>
#include <ctime>
using namespace std;

// boost includes
// boost serialization
#if defined(DGM_PARALLEL)
#include <boost/mpi/environment.hpp>
#include <boost/mpi/communicator.hpp>
#include <boost/mpi/collectives.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/vector.hpp>
#include "boost/serialization/map.hpp"
#include "boost/serialization/string.hpp"
#include "boost/serialization/set.hpp"
#include "boost/archive/binary_iarchive.hpp"
#include "boost/archive/binary_oarchive.hpp"
#endif

#ifdef DGM_USE_BOOST_FS
#include "boost/filesystem.hpp"
#endif

// DGM libraries
#include "Domain.hpp"
#include "Utilities.hpp"
#include "Info.hpp"

// Json includes
#ifdef DGM_USE_JSON
#include "json/json.h"
#include "json/serialization.h"
#endif

namespace DGM {

#ifndef DGM_USE_BOOST_FS
#warning "DGM::RuntimeControl requires that DGM_USE_BOOST_FS is defined.\n\
Using trivial implementation of RuntimeControl that provides no features."
class RuntimeControl {
public:
  RuntimeControl(const string rname_, Ordinal &Nt_,
                 Ordinal &Ntout_, Ordinal &ntout_,
                 const DGM::Comm::Ptr comm_=DGM::Comm::World) {}
  void check() {}
  bool restart() const { return false; }
};
#else
/// Provides a means of controlling the simulation at runtime
/** Runtime control works quite well in serial and smaller MPI runs but
    on larger, capability runs we have observed a loss of performance so
    only use on large runs with caution **/
class RuntimeControl {
  const string rname;              ///< root filename
  Ordinal &Nt;                     ///< Number of timesteps
  Ordinal &Ntout;                  ///< major output interval
  Ordinal &ntout;                  ///< minor output interval
  time_t lasttime;                 ///< last time rtc was changed
  bool restart_;                   ///< restart flag
  const DGM::Comm::Ptr comm;       ///< DGM communicator
#ifdef DGM_PARALLEL
  boost::mpi::communicator bcomm;  ///< Boost parallel communicator
#endif
public:
  friend class boost::serialization::access;
  template<class Archive>
  void serialize(Archive &ar, const unsigned int version) {
    ar & Nt & Ntout & ntout & lasttime & restart_;
  }
  /// constructor
  RuntimeControl(const string rname_, Ordinal &Nt_,
                 Ordinal &Ntout_, Ordinal &ntout_,
                 const DGM::Comm::Ptr comm_=DGM::Comm::World) :
    rname(rname_), Nt(Nt_), Ntout(Ntout_), ntout(ntout_), restart_(false),
    comm(comm_)
#ifdef DGM_PARALLEL
    , bcomm(dynamic_cast<const DGM::MpiComm*>(comm.get())->
            mpi_comm,boost::mpi::comm_attach)
#endif
  {
    using namespace boost::filesystem;
    if (comm->Master()) {
      path p(rname+".rtc");
      if (exists(p) && is_regular_file(p)) {
        lasttime = last_write_time(p);
      } else {
        time(&lasttime);
      }
    }
#ifdef DGM_PARALLEL
    broadcast(bcomm,*this,0);
#endif
  }
  /// Checks to see if the rtc file has been updated
  void check() {
#ifdef DGM_DISABLE_RUNTIME_CONTROL
    return;
#else
    using namespace boost::filesystem;
    if (comm->Master()) {
      path p(rname+".rtc");
      if (exists(p)) {
        if (is_regular_file(p)) {
          time_t rawtime = last_write_time(p);
          if (difftime(lasttime,rawtime)) {
            //std::cout << p << " size is " << file_size(p) << endl;
            //std::cout << "File modified on " << ctime(&rawtime);
            Json::Value root;
            Json::Reader reader;
            std::ifstream file(p.c_str(), std::ifstream::in);
            bool parsingSuccessful = reader.parse(file, root, true);
            if (!parsingSuccessful) {
              cout << "Failed to parse " << p << endl;
            }
            if (root.isMember("Problem")) {
              restart_ = root["Problem"].get("Restart",restart_).asBool();
            }
            if (root.isMember("Domain")) {
              Json::Value domain = root["Domain"];
              if (domain.isMember("Nt")) Nt = domain["Nt"].asInt();
              if (domain.isMember("Ntout")) Ntout = domain["Ntout"].asInt();
              if (domain.isMember("ntout")) ntout = domain["ntout"].asInt();
            }
            lasttime = rawtime;
          }
        } else if (is_directory(p)) {
          throw DGM::exception(p.native()+" cannot be a directory");
        } else {
          throw DGM::exception(p.native()+" exists, but is not a valid file");
        }
      }
    }
#ifdef DGM_PARALLEL
    broadcast(bcomm,*this,0);
#endif
#endif
  }
  /// triggers a restart
  bool restart() const { return restart_; }
};
#endif

} // namespace DGM

#endif // DGM_RUNTIME_CONTROL_HPP

