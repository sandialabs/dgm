#ifndef json_serialization_h
#define json_serialization_h

/** \file serialization.h
    \author K. Noel Belcourt
    \brief Provides serialization for Json value
**/

#ifdef DGM_PARALLEL

// system includes
#include <sstream>

// boost includes
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/mpi.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/string.hpp>

// Json includes
#include "json/json.h"

namespace boost {

  namespace serialization {

    template<class Archive>
    void serialize(Archive& ar, Json::Value::CZString& c, const unsigned int)
    {
      if (typename Archive::is_saving()) {
        std::string s;
        if (c.cstr_)
          s = c.cstr_;
        else
          s = "";
        ar & s & c.index_;
      } else if (typename Archive::is_loading()) {
        std::string s;
        Json::Value::ArrayIndex index;
        ar & s & index;
        if (s != "")
          c = Json::Value::CZString(s.c_str(),
                                    Json::Value::CZString::duplicate);
        else
          c = Json::Value::CZString(index);
      }
    }

    template <typename Archive>
    void load(Archive& ar, Json::Value& v, const unsigned int)
    {
      ar >> v.type_;
#ifdef JSON_VALUE_USE_INTERNAL_MAP
      ar >> v.itemIsUsed_;
      ar >> v.memberNameIsStatic_;
#endif
      switch (v.type_) {
      case Json::nullValue:
        break;
      case Json::intValue:
      case Json::uintValue:
        ar >> v.value_.int_;
        break;
      case Json::realValue:
        ar >> v.value_.real_;
        break;
      case Json::stringValue: {
        std::string s;
        ar >> s >> v.allocated_;
        if (v.allocated_ && !s.empty()) v.value_.string_ = strdup(s.c_str());
        break;
      }
#ifndef JSON_VALUE_USE_INTERNAL_MAP
      case Json::arrayValue:
      case Json::objectValue: {
        ar >> v.value_.map_;
        break;
      }
#else
      case Json::arrayValue:
        ar >> v.value_.array_;
        break;
      case Json::objectValue:
        ar >> v.value_.map_;
        break;
#endif
      case Json::booleanValue:
        ar >> v.value_.bool_;
        break;
      }
    }

    template <typename Archive>
    void save(Archive& ar, const Json::Value& v, const unsigned int)
    {
      ar << v.type_;
#ifdef JSON_VALUE_USE_INTERNAL_MAP
      ar << v.itemIsUsed_;
      ar << v.memberNameIsStatic_;
#endif
      switch (v.type_) {
      case Json::nullValue:
        break;
      case Json::intValue:
      case Json::uintValue:
        ar << v.value_.int_;
        break;
      case Json::realValue:
        ar << v.value_.real_;
        break;
      case Json::stringValue: {
        std::string s;
        if (v.allocated_) s = v.value_.string_;
        ar << s << v.allocated_;
        break;
      }
#ifndef JSON_VALUE_USE_INTERNAL_MAP
      case Json::arrayValue:
      case Json::objectValue: {
        ar << v.value_.map_;
        break;
      }
#else
      case Json::arrayValue:
        ar << v.value_.array_;
        break;
      case Json::objectValue:
        ar << v.value_.map_;
        break;
#endif
      case Json::booleanValue:
        ar << v.value_.bool_;
        break;
      }
    }

    template<class Archive>
    void serialize(Archive &ar, Json::Value &v,
                   const unsigned int file_version) {
      boost::serialization::split_free(ar, v, file_version);
    }

  } // namespace serialization

} // namespace boost

// eliminate object tracking (even if serialized through a pointer)
// at the risk of a programming error creating duplicate objects.
// This is done to avoid warnings that are currently generated with this on
BOOST_CLASS_TRACKING(Json::Value, boost::serialization::track_never)

namespace Json {

/*! Note that this does depend on DGM::Comm so that you need to make sure
 *  that this header is included before this one -- likely should fix this.
 */
inline void broadcast(DGM::Comm::Ptr DGM_comm, Json::Value& v) {
  using boost::mpi::broadcast;
  using boost::mpi::communicator;
  const int verb(0);
#ifdef DGM_JSON_USE_MPI_WORLD
  communicator comm;
#else
  communicator comm(dynamic_cast<const DGM::MpiComm*>
    (DGM_comm.get())->mpi_comm,boost::mpi::comm_attach);
#endif
  if (0 == comm.rank()) {
    std::stringstream ss(std::stringstream::out);
    boost::archive::text_oarchive oa(ss);
    oa << v;
    std::string s = ss.str();
    if (verb) std::cout<<"Sending "<<s<<" on rank 0"<<std::endl;
    broadcast(comm, s, 0);
  } else {
    std::string t;
    broadcast(comm, t, 0);
    if (verb) std::cout<<"Received "<<t<<" on rank "<<comm.rank()<<std::endl;
    std::stringstream ss(t, std::stringstream::in);
    boost::archive::text_iarchive ia(ss);
    ia >> v;
  }
}

} // namespace Json

#else   // DGM_PARALLEL

namespace Json {

class Value;

inline void broadcast(DGM::Comm::Ptr DGM_comm, Json::Value& v) {}

} // namespace Json

#endif  // DGM_PARALLEL

#endif  // json_serialization_h
