#ifndef DGM_VERTEX_HPP
#define DGM_VERTEX_HPP

/** \file Vertex.hpp
    \brief DGM element vertex class declaration
    \author S. Scott Collis
    \author Axel Gerstenberger
*/

// DGM includes
#include "Point.hpp"

// system includes
#ifdef DGM_USE_GENERAL_GHOSTING
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/base_object.hpp>
#endif

namespace DGM {

/// Vertex class
class Vertex : public Point {
public:

  typedef DGM::Shared<Vertex>::Ptr Ptr;  ///< shared pointer

  Size id;            ///< vertex id
  Size gid;           ///< global vertex id
  Size eid;           ///< local element id

  Vertex( const Size ID, const Size EID, const Point &X );

  Vertex( const Vertex &v) : Point(v), id(v.id), gid(v.gid), eid(v.eid) {
    cout << "Vertex copy constructor for id="<<id<<", gid="<<gid
         <<", eid="<<eid << endl;
  }

  friend std::ostream& operator<<(std::ostream&, const Vertex &);

#ifdef DGM_USE_GENERAL_GHOSTING
  /// gives boost access to private data
  friend class boost::serialization::access;

  /*! serialize this class
   *
   * @tparam Archive boost input or output archive class
   * @param ar       archive
   * @param version  (not needed here, see boost documentation)
   */
  template<class Archive>
  void serialize(Archive &ar, const unsigned int version) {
    ar & boost::serialization::base_object<Point>(*this);
    ar & id & gid & eid;
  }
  /// test serialization process for this class
  static int test_serialization();
  Vertex() {};               ///< Default used for deserialization
#else
private:
  Vertex();                  ///< not implemented
#endif
private:
  Vertex( const Vertex * );  ///< not implemented
};

/// constructor
inline Vertex::Vertex(const Size ID, const Size EID, const Point &X ) 
: Point(X) {
  id = ID;
  gid = numeric_limits<Size>::max();
  eid = EID;
}

/// output helper for Vert
inline std::ostream& operator<<(std::ostream &os, const Vertex &v) {
  os << "Vertex: id = " << v.id <<", gid = " << v.gid << ", eid = " << v.eid;
  os << ", x, y, z = " << v.x << ", " << v.y << ", " << v.z;
  return os;
}

} // namespace

#endif  // DGM_VERTEX_HPP
