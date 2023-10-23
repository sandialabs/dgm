#ifndef DGM_CURVE_HPP
#define DGM_CURVE_HPP

/** \file Curve.hpp
    \brief Curved side declaration
    \author Scott Collis
*/

// system includes
#include "fstream"
#include "string"
using namespace std;

// json includes
#ifdef DGM_USE_JSON
#include "json/reader.h"
#include "json/value.h"
#include "json/writer.h"
#endif

// DGM includes
#include "Types.hpp"
#include "Comm.hpp"
#include "Coordinates.hpp"
#include "Geometry.hpp"
#include "Partition.hpp"

// boost includes
#ifdef DGM_USE_GENERAL_GHOSTING
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/base_object.hpp>
#endif

namespace DGM {

// forward declaration
class Element;

/// Curved Side base class
/** Major upgrade underway to allow for JSON input specification
    \note 3D interface is untested and likely inadequate
    \note The implementation is supposed to be agnostic of element type
          but that is currently not completely true. */
class Curve {

protected:

  DGM::Comm::Ptr comm;                      ///< Communicator

  int verb;                                 ///< Verbose level

public:

  typedef DGM::Shared<Curve>::Ptr Ptr;      ///< Curve shared pointer
  typedef map<string,Curve::Ptr> db_type;   ///< Curve database type
  typedef db_type::iterator CI;             ///< Curve database iterator
  typedef db_type::const_iterator CCI;      ///< Curve database const_iterator

  Ordinal side;                             ///< curved element side id
  dVector xh;                               ///< x modal coefficients
  dVector yh;                               ///< y modal coefficients
  dVector zh;                               ///< z modal coefficients

  // edge modal coefficients for faces in 3d
  dVector xh_e[4];                 ///< arbitrary 4 edges in 1 face for Hex
  dVector yh_e[4];                 ///< arbitrary 4 edges in 1 face for Hex
  dVector zh_e[4];                 ///< arbitrary 4 edges in 1 face for Hex

  /// default constructor
  Curve(DGM::Comm::Ptr comm_ = DGM::Comm::World) :
    comm(comm_), verb(0), side(undefined<Ordinal>()) {
    if (verb>1) comm->cout() << "Curve() constructor " << this << endl;
  }

  /// JSON constructor
  Curve(Json::Value &value, DGM::Comm::Ptr comm_ = DGM::Comm::World) :
    comm(comm_), verb(value.set("Verbosity",0).asInt()),
    side(undefined<Ordinal>()) {
    if (verb>1) comm->cout() << "Curve() JSON constructor " << this << endl;
  }

  /// reference copy constructor
  Curve(const Curve &C) : comm(C.comm), verb(0) {
    // cout << "Curve(const Curve&) constructor " << &C << endl;
    if (this == &C) return;
    side=C.side;
    xh.resize(C.xh.size());
    yh.resize(C.yh.size());
    zh.resize(C.zh.size());
  }

  /// pointer copy constructor
  Curve(const Curve *C) : comm(C->comm), verb(0) {
    // cout << "Curve(const Curve*) constructor " << C << endl;
    if (this == C) return;
    if (C == 0) return;
    side=C->side;
    xh.resize(C->xh.size());
    yh.resize(C->yh.size());
    zh.resize(C->zh.size());
  }

  /// shared pointer copy constructor
  Curve(const Curve::Ptr C) : comm(C->comm), verb(0) {
    // cout << "Curve(const Curve::Ptr) constructor " << C << endl;
    if (this == C.get()) return;
    if (C.get() == 0) return;
    side=C->side;
    xh.resize(C->xh.size());
    yh.resize(C->yh.size());
    zh.resize(C->zh.size());
  }

  /// destructor
  virtual ~Curve() {}

  /// \name methods
  //@{
  /// Clone the current object
  virtual Curve* clone() { return new Curve(*this); }
  /// Generate a 2d curved element
  virtual void generate(const Element*, dVector&, dVector&) const;
  /// Generate a 3d curved element
  virtual void generate(const Element*, dVector&, dVector&, dVector&) const;
  //@}

  virtual std::string type_name() { return "Undefined";} 
  /// output to a stream
  friend std::ostream& operator<<(std::ostream&, const Curve& );

  /// read curve types from a file stream
  static void read(DGM::Comm::Ptr, string &, ifstream &, db_type &);
  /// read curve types and curved sides from a file stream
  static void read(DGM::Comm::Ptr comm,
                   const Partition<Size,Ordinal,Scalar>::Ptr partition,
                   const string &fname, ifstream &in,
                   db_type &ctype, vector<Element*> &el);
  /// read curve types from a file stream in old format
  static void read_old(DGM::Comm::Ptr, const string &, ifstream &, db_type &);
  /// read curve type from a file stream in json format
  static void read_json(DGM::Comm::Ptr, const string &, ifstream &,
                        db_type &, Json::Value &);
  /// make a curve type from a file stream
  static Curve* make(DGM::Comm::Ptr, ifstream &, string &);
  /// make a curve from a JSON value
  static Curve* make_json(DGM::Comm::Ptr, Json::Value &, string &);
  /// read curved sides from a file stream
  static void read_sides(DGM::Comm::Ptr comm,
                         Partition<Size,Ordinal,Scalar>::Ptr partition,
                         const string &fname, ifstream &in,
                         db_type &ctype, vector<Element*> &el);
  /// read curved sides from a json value
  static bool read_sides(DGM::Comm::Ptr comm,
                         Partition<Size,Ordinal,Scalar>::Ptr partition,
                         const string &fname,
                         Json::Value &value, db_type &ctype,
                         vector<Element*> &el);

#ifdef DGM_USE_GENERAL_GHOSTING
 private:
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
    ar & verb & side;
    ar & xh & yh & zh;
    ar & xh_e & yh_e & zh_e;
  }
  /// test serialization process for this class
  // static int test_serialization();
#endif
};

/// output Curve to a stream
inline std::ostream& operator<<(std::ostream &os, const Curve &C) {
  os << "curved side = " << C.side;
  return os;
}

/// Generalized straight Side (non-parallelpiped)
class Straight : public Curve {
public:
  /// constructor
  Straight(DGM::Comm::Ptr comm_ = DGM::Comm::World) : Curve(comm_){
    if (verb>1) comm->cout() << "Straight()" << endl;
  }
  /// Json constructor
  Straight(Json::Value &value, DGM::Comm::Ptr comm_ = DGM::Comm::World) :
    Curve(value,comm_) {}
  /// copy constructor
  Straight(const Straight &C) : Curve(C) {
    if (verb>2)
      comm->cout() << "Straight(const Straight&) constructor " << &C << endl;
    *this = C;
  }
  /// clone this object
  Curve* clone() { return new Straight(*this); }
  /// generate this curve
  void generate( const Element *, dVector &, dVector & ) const;

  virtual std::string type_name() { return "Straight";} 
#ifdef DGM_USE_GENERAL_GHOSTING
private:
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
    ar & boost::serialization::base_object<Curve>(*this);
  }
  /// test serialization process for this class
  // static int test_serialization();
#endif
};

/// Generalized 3D straight Side (non-parallelpiped)
class Straight3D : public Curve {
public:
  /// constructor
  Straight3D(DGM::Comm::Ptr comm_ = DGM::Comm::World) : Curve(comm_) {
  }
  /// Json constructor
  Straight3D(Json::Value &value, DGM::Comm::Ptr comm_ = DGM::Comm::World) :
    Curve(value,comm_) {}
  /// copy constructor
  Straight3D(const Straight3D &C) : Curve(C) {
    *this = C;
  }
  /// clone this object
  Curve* clone() { return new Straight3D(*this); }
  /// generate this curve
  void generate(const Element *, dVector &, dVector &, dVector &) const;

  virtual std::string type_name() { return "Straight3D";} 
#ifdef DGM_USE_GENERAL_GHOSTING
private:
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
    ar & boost::serialization::base_object<Curve>(*this);
  }
  /// test serialization process for this class
  // static int test_serialization();
#endif
};

/// Circular arc curved Side in 2d
class Arc : public Curve {
  Scalar center_x;         ///< x coordinate of the center
  Scalar center_y;         ///< y coordinates of the center
  Scalar radius;           ///< Radius of the curve
  bool check_center;       ///< whether to check the center location
public:
  /// constructor without center location
  Arc(Scalar r, DGM::Comm::Ptr comm_ = DGM::Comm::World) : Curve(comm_),
  center_x(0.0), center_y(0.0), radius(r), check_center(false) {
    if (verb>1) comm->cout() << "Arc("<<radius<<")"<<endl;
  }
  /// Json constructor
  Arc(Json::Value &value, DGM::Comm::Ptr comm_ = DGM::Comm::World) :
    Curve(value, comm_), center_x(0.0), center_y(0.0),
    radius(value.set("Radius",0.0).asDouble()),
    check_center(value.set("Check center",false).asBool()) {
    if (verb>1) comm->cout() << "Arc("<<radius<<") JSON constructor"<<endl;
    if (value.isMember("Center")) {
      if (value["Center"].isArray()) {
        Json::ArrayIndex nsd = value["Center"].size();
        if (nsd>0)
          center_x = value["Center"][0].asDouble();
        if (nsd>1)
          center_y = value["Center"][1].asDouble();
        if (nsd>2)
          comm->error("Arc \"Center\" must have one or two components");
      } else {
        comm->error("Arc \"Center\" must be an array of doubles");
      }
    }
  }
  /// constructor with center
  /**
   * \deprecated This form of the Constructor should no longer be used
   */
  Arc(Scalar x_c, Scalar y_c, Scalar r,
      DGM::Comm::Ptr comm_ = DGM::Comm::World) :
  Curve(comm_), center_x(x_c), center_y(y_c), radius(r), check_center(true) {
    if (verb>1)
      comm->cout() << "Arc("<<center_x<<","<<center_y<<","<<radius<<")"<<endl;
  }
  /// copy constructor
  Arc(const Arc &C) : Curve(C), center_x(0), center_y(0), radius(0),
      check_center(false) {
    if (verb>2) comm->cout() << "Arc(const Arc&) constructor " << &C << endl;
    *this = C;
  };
  /// clone this object
  Curve* clone() { return new Arc(*this); }
  /// generate this arc
  void generate(const Element *, dVector &, dVector &) const;

  virtual std::string type_name() { return "Arc";} 
#ifdef DGM_USE_GENERAL_GHOSTING
private:
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
    ar & boost::serialization::base_object<Curve>(*this);
    ar & center_x & center_y & radius;
  }
  /// test serialization process for this class
  // static int test_serialization();
  /// default constructor for serialization
  Arc(DGM::Comm::Ptr comm_ = DGM::Comm::World) : Curve(comm_) {}
#endif
};

/// Elliptical curved Side in 2d
class Ellipse : public Curve {
  Scalar xc;               ///< x coordinate of the center
  Scalar yc;               ///< y coordinate of the center
  Scalar aa;               ///< semi major axis
  Scalar bb;               ///< semi minor axis
  int    orientation;      ///< 1 for counter clockwise, -1 for clockwise
public:
  /// constructor
  Ellipse(Scalar x_c, Scalar y_c, Scalar a_a,
          Scalar b_b, int s, DGM::Comm::Ptr comm_ = DGM::Comm::World) :
  Curve(comm_) {
    if (verb) comm->cout() << "Ellipse(Scalar,Scalar,Scalar,Scalar)" << endl;
    xc=x_c; yc=y_c; aa=a_a; bb=b_b; orientation=s;
    if (!(orientation==1 || orientation==-1))
      comm->error("Ellipse \"Orientation\" must be either 1 (clockwise) or "
                  "-1 (counter-clockwise)");
  }
  /// constructor (json)
  Ellipse(Json::Value &value, DGM::Comm::Ptr comm_ = DGM::Comm::World);
  /// copy constructor
  Ellipse(const Ellipse &C) : Curve(C) {
    if (verb>2)
      comm->cout() << "Ellipse(const Ellipse&) constructor " << &C << endl;
    *this = C;
  }
  /// clone this object
  Curve* clone() { return new Ellipse(*this); }
  /// generate the ellipse
  void generate(const Element *, dVector &, dVector &) const;

  virtual std::string type_name() { return "Ellipse";} 
private:
  /// compute arc-length
  void arclength(Scalar, Scalar, Scalar &) const;
};

/// Sine wave curved Side in 2d
class Sine : public Curve {
  Scalar  xo, yo;
  Scalar  amp;
  Scalar  wavelength;
public:
  /// constructor
  Sine(Scalar x_o, Scalar y_o, Scalar a, Scalar w,
       DGM::Comm::Ptr comm_ = DGM::Comm::World) :
  Curve(comm_), xo(x_o), yo(y_o), amp(a), wavelength(w) {
    if (verb>1) comm->cout() << "Sine() constructor " << this << endl;
  }
  /// constructor (json)
  Sine(Json::Value &, DGM::Comm::Ptr comm_ = DGM::Comm::World);
  /// copy constructor
  Sine(const Sine &C) : Curve(C) {
    if (verb>2) comm->cout() << "Sine(const Sine &) constructor " << &C << endl;
    *this = C;
  };
  /// clone this object
  Curve* clone() { return new Sine(*this); }
  /// generate the curve
  void generate(const Element *, dVector &, dVector &) const;

  virtual std::string type_name() { return "Sine";} 
};

/// Spherical curved sides in 3d
class Sphere : public Curve {
  Scalar center_x;          ///< x-coordinate of the center
  Scalar center_y;          ///< y-coordinate of the center
  Scalar center_z;          ///< z-coordinate of the center
  Scalar radius;            ///< radius of the curve
public:
  /// constructor
  Sphere(Scalar x_c, Scalar y_c, Scalar z_c, Scalar r,
         DGM::Comm::Ptr comm_ = DGM::Comm::World) :
  Curve(comm_), center_x(x_c), center_y(y_c), center_z(z_c), radius(r) {
    if (verb>1) comm->cout() << "Sphere(Scalar,Scalar,Scalar)" << endl;
  }
  /// constructor (json)
  Sphere(Json::Value &, DGM::Comm::Ptr comm_ = DGM::Comm::World);
  /// copy constructor
  Sphere(const Sphere &C) : Curve(C) {
    if (verb>2) comm->cout() << "Sphere(const Sphere&) constructor "
                             << &C << endl;
    *this = C;
  }
  /// clone current object
  Curve* clone() { return new Sphere(*this); }
  /// generate the sphere
  void generate(const Element *, dVector &, dVector &, dVector &) const;

  virtual std::string type_name() { return "Sphere";} 
};

} // namespace DGM

#endif  // DGM_CURVE_HPP
