#ifndef DGM_SIDE_HPP
#define DGM_SIDE_HPP

/** \file Side.hpp
    \brief DGM element side class declaration
    \author Scott Collis
    \author James Overfelt
*/

// system includes
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

// boost includes
#ifdef DGM_USE_GENERAL_GHOSTING
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/shared_ptr.hpp>
#endif

// DGM includes
#include "Types.hpp"
#include "Vertex.hpp"
#include "Coordinates.hpp"
#include "Types.hpp"
#include "Vector.hpp"

namespace DGM {

class Element;

/// Generic concept of an element side
class Side {

public:

  typedef Size GlobalSize;
  typedef Ordinal LocalSize;

private:

  void resize( const LocalSize );       ///< hide the resize method

public:

  /// shared pointer to side
  typedef DGM::Shared< Side >::Ptr Ptr;

  /// Side information class
  template<typename GlobalSize, typename LocalSize, typename Scalar>
  class Info {
  public:
    typedef dVector vec;
  private:
    LocalSize _id;                     ///< local side id
    GlobalSize _gid;                   ///< global side id
    GlobalSize _geid;                  ///< global element id
    LocalSize _nModes;                 ///< number of modes on side
    LocalSize _q1;                     ///< quadrature order on side 1
    LocalSize _q2;                     ///< quadrature order on side 2
    bool _flip_a;                      ///< connectivity flip flag for a-axis
    bool _flip_b;                      ///< connectivity flip flag for b-axis
    bool _transp;                      ///< connectivity transpose flag
    bool _bc;                          ///< true if on the real boundary
    bool _Gauss_Lobatto;               ///< false means Gauss Legendre
    Scalar _measure;                   ///< side measure (length/area)
    Scalar _h_n_inv;                   ///< 1.0 / length normal to the Side
    vec _nx;                           ///< component of normal vector in x
    vec _ny;                           ///< component of normal vector in y
    vec _nz;                           ///< component of normal vector in z
    vec _J;                            ///< side Jacobian
    vec _J_scale;                      ///< determinant of Jacobian
    vec _J_orig;

  public:
    /// shared pointer to side info
    typedef typename
    DGM::Shared< Info<GlobalSize,LocalSize,Scalar> >::Ptr Ptr;
    /// default constructor
    Info() : _id(uid<LocalSize>()), _gid(uid<GlobalSize>()),
             _geid(uid<GlobalSize>()), _nModes(0),
             _q1(0), _q2(0), _flip_a(false), _flip_b(false), _transp(false),
             _bc(false), _Gauss_Lobatto(false),
             _measure(0), _h_n_inv(0), _J_scale(), _J_orig() {}
    /// constructor
    Info(const LocalSize id, const GlobalSize gid, const GlobalSize geid,
         const LocalSize nModes, const LocalSize q1, const LocalSize q2,
         const bool GLL) :
      _id(id), _gid(gid), _geid(geid), _nModes(nModes),
      _q1(q1), _q2(q2), _flip_a(false), _flip_b(false), _transp(false),
      _bc(false), _Gauss_Lobatto(GLL),
      _measure(0.0), _h_n_inv(0.0) {
      _nx.resize(qtot()); _nx=0.0;
      _ny.resize(qtot()); _ny=0.0;
      _nz.resize(qtot()); _nz=0.0;
      _J.resize(qtot()),  _J =0.0;
      _J_scale.resize(qtot()),  _J_scale =0.0;
      _J_orig.resize(qtot()),   _J_orig =0.0;
    }
    /// copy constructor
    Info(const Info &info) :
      _id(info._id), _gid(info._gid), _geid(info._geid),
      _nModes(info._nModes), _q1(info._q1), _q2(info._q2),
      _flip_a(info._flip_a), _flip_b(info._flip_b), _transp(info._transp),
      _bc(info._bc), _Gauss_Lobatto(info._Gauss_Lobatto),
      _measure(info._measure), _h_n_inv(info._h_n_inv) {
      _nx.alias(const_cast<vec &>(info._nx));
      _ny.alias(const_cast<vec &>(info._ny));
      _nz.alias(const_cast<vec &>(info._nz));
      _J.alias(const_cast<vec &>(info._J));
      _J_scale.resize(info._J_scale.size());
      _J_orig.resize(info._J_orig.size());
      _J_scale=info._J_scale;
      _J_orig=info._J_orig;
    }
    Info & operator=(const Info &info) {
      _id           =info._id;
      _gid          =info._gid;
      _geid         =info._geid;
      _nModes       =info._nModes;
      _q1           =info._q1;
      _q2           =info._q2;
      _flip_a       =info._flip_a;
      _flip_b       =info._flip_b;
      _transp       =info._transp;
      _bc           =info._bc;
      _Gauss_Lobatto=info._Gauss_Lobatto;
      _measure      =info._measure;
      _h_n_inv      =info._h_n_inv;
      _nx.resize(info._nx.size());
      _ny.resize(info._ny.size());
      _nz.resize(info._nz.size());
      _nx           =info._nx;
      _ny           =info._ny;
      _nz           =info._nz;
      _J      .resize(info._J      .size());
      _J_scale.resize(info._J_scale.size());
      _J_orig .resize(info._J_orig .size());
      _J            =info._J;
      _J_scale      =info._J_scale;
      _J_orig       =info._J_orig;
      return *this;
    }
    /// copy constructor
    Info(const Info *info) :
      _id(info->_id), _gid(info->_gid), _geid(info->_geid),
      _nModes(info->_nModes), _q1(info->_q1), _q2(info->_q2),
      _flip_a(info->_flip_a), _flip_b(info->_flip_b), _transp(info->_transp),
      _bc(info->_bc), _Gauss_Lobatto(info->_Gauss_Lobatto),
      _measure(info->_measure), _h_n_inv(info->_h_n_inv) {
      _nx.alias(const_cast<vec &>(info->_nx));
      _ny.alias(const_cast<vec &>(info->_ny));
      _nz.alias(const_cast<vec &>(info->_nz));
      _J.alias(const_cast<vec &>(info->_J));
      _J_scale.resize(info->_J_scale.size());
      _J_orig.resize(info->_J_orig.size());
      _J_scale=info->_J_scale;
      _J_orig=info->_J_orig;
    }
    /// resize the normals and Jacobian
    void resize(const LocalSize q) {
      if (q == _nx.size()) return;
      _nx.resize(q); _nx=0.0;
      _ny.resize(q); _ny=0.0;
      _nz.resize(q); _nz=0.0;
      _J.resize(q);  _J =0.0;
      _J_scale.resize(q);  _J_scale =0.0;
      _J_orig.resize(q);  _J_orig =0.0;
    }
    /// \name Accessors
    //@{
    /// Set local side id
    void id(const LocalSize id) { _id = id; }
    /// Return local side id
    LocalSize id() const { return _id; }

    /// Set global side id
    void gid(const GlobalSize gid) { _gid = gid; }
    /// Return global side id
    GlobalSize gid() const { return _gid; }

    /// Set global element id
    void geid(const GlobalSize geid) { _geid = geid; }
    /// Return global element id
    GlobalSize geid() const { return _geid; }

    /// Set number of side modes
    void nModes(const LocalSize nModes) { _nModes = nModes; }
    /// Return number of side modes
    LocalSize nModes() const { return _nModes; }

    /// Set the number of points in the a-direction
    void q1(const LocalSize q1) { _q1 = q1; }
    /// Get the number of points in the a-direction
    LocalSize q1() const { return _q1; }

    /// Set the number of points in the a-direction
    void q2(const LocalSize q2) { _q2 = q2; }
    /// Get the number of points in the a-direction
    LocalSize q2() const { return _q2; }

    /// Number of quad points
    LocalSize qtot() const { return q1()*(q2() ? q2() : 1); }

    /// Set the side flip in the a-direction
    void flip_a(const bool flip_a) { _flip_a = flip_a; }
    /// Get the side flip in the a-direction
    bool flip_a() const { return _flip_a; }

    /// Set the side flip in the b-direction
    void flip_b(const bool flip_b) { _flip_b = flip_b; }
    /// Get the side flip in the b-direction
    bool flip_b() const { return _flip_b; }

    /// Set the side transpose
    void transp(const bool transp) { _transp = transp; }
    /// Get the side transpose
    bool transp() const { return _transp; }

    /// Set whether on boundary
    void bc(const bool bc) { _bc = bc; }
    /// Get whether on boundary
    bool bc() const { return _bc; }

    /// Set the side integration method
    void Gauss_Lobatto(const bool GL) { _Gauss_Lobatto = GL; }
    /// Get the side integration method
    bool Gauss_Lobatto() const { return _Gauss_Lobatto; }

    /// Set the side measure
    void measure(const Scalar measure) { _measure = measure; }
    /// Get the side measure
    Scalar measure() const { return _measure; }

    /// Set the side inverse normal length
    void h_n_inv(const Scalar h_n_inv) { _h_n_inv = h_n_inv; }
    /// Get the side inverse normal length
    Scalar h_n_inv() const { return _h_n_inv; }

    /// Returned the value for an undefined id
    template <typename T>
    static T uid() { return numeric_limits<T>::max(); }
    /// Evaluate whether an id is defined
    template <typename T>
    static bool undefined(const T id) { return id==uid<T>(); }

    // Try out for normals and Jacobian
    vec & nx() { return _nx; }
    Scalar & nx(const LocalSize i) { return _nx[i]; }
    const vec & nx() const { return _nx; }
    Scalar nx(const LocalSize i) const { return _nx[i]; }

    vec & ny() { return _ny; }
    Scalar & ny(const LocalSize i) { return _ny[i]; }
    const vec & ny() const { return _ny; }
    Scalar ny(const LocalSize i) const { return _ny[i]; }

    vec & nz() { return _nz; }
    Scalar & nz(const LocalSize i) { return _nz[i]; }
    const vec & nz() const { return _nz; }
    Scalar nz(const LocalSize i) const { return _nz[i]; }

    vec & J() { return _J; }
    Scalar & J(const LocalSize i) { return _J[i]; }
    const vec & J() const { return _J; }
    Scalar J(const LocalSize i) const { return _J[i]; }

    vec & J_scale() { return _J_scale; }
    const vec & J_scale() const { return _J_scale; }
    Scalar & J_scale(const LocalSize i) { return _J_scale[i]; }
    vec & J_orig() { return _J_orig; }
    const vec & J_orig() const { return _J_orig; }
    Scalar & J_orig(const LocalSize i) { return _J_orig[i]; }
    //@}
#ifdef DGM_USE_GENERAL_GHOSTING
  private:
    friend class boost::serialization::access;
    /*!
     * \brief Serialization of Side::Info class
     */
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
      ar & _id & _gid & _geid;
      ar & _nModes & _q1 & _q2;
      ar & _flip_a & _flip_b & _transp & _bc;
      ar & _measure & _h_n_inv;
      ar & _nx & _ny & _nz & _J;
    }
#endif
  };

protected:

  typedef Info<GlobalSize,LocalSize,Scalar> MyInfo;

  MyInfo::Ptr info;    ///< Side info pointer

public:

  Element *elink;                 ///< element for this side
  Side *link;                     ///< adjacent side link
  Side *base;                     ///< link to base (i.e. master) side
  vector<Ptr> subside;

  dVector u;                      ///< solution storage on the side

#ifdef DGM_USE_MD_COUPLE
  Model::Type modeltype;          ///< physics model type

  /// Normal constructor (with multi-domain coupling)
  Side( const LocalSize, Element*, const LocalSize,
        const LocalSize, const LocalSize=0,
        const Model::Type = Model::EULER);
#else
  /// Normal constructor
  Side( const LocalSize, Element*, const LocalSize,
        const LocalSize, const bool, const LocalSize=0 );
#endif
  /// Destructor
  virtual ~Side();

  /// Clone a Side
  virtual Side *clone() const {
    DGM_UNDEFINED;
    return 0;
  }

  /// Matches quadrature points on two sides
  virtual void match(Side *);

  /// Equate two Sides
  Side & operator=(const Side &);

  /// Output a side to a stream
  friend std::ostream & operator<<(std::ostream &os, const Side &sid);

  /// Print out a side
  virtual void print() const {cout<<"Side"<<endl;}

  /// Determine if a master side
  bool master() const { return (link != NULL); }

  /// Determine if a bc side
  bool is_bc() const { return bc(); }

  /// Clone a Side
  virtual Side* deep_copy () const { DGM_UNDEFINED; return 0; }

  virtual bool has_subsides() const {
    cout << "Side::has_subsides()" << endl;
    DGM_UNDEFINED;
    return false;
  }
  /// Get global id of my element (used currently for ghosting and adaptivity)
  //GlobalSize egid() const { return geid(); }

  /// Get a pointer to my element
  Element * el() const { return elink; }

  virtual void push_to_subsides()   = 0;
  virtual void push_to_subside(const dVector &) = 0;
  virtual void push_to_subside(const dVector &, dVector &) const = 0;

  /// set the local side id
  void id(const LocalSize id) { info->id(id); }
  /// return the local side id
  LocalSize id() const { return info->id(); }

  /// set the global side id
  void gid(const GlobalSize gid) { info->gid(gid); }
  /// return the global side id
  GlobalSize gid() const { return info->gid(); }

  /// set the global element id linked to this side
  void geid(const GlobalSize geid) { info->geid(geid); }
  /// return the global element id linked to this side
  GlobalSize geid() const { return info->geid(); }

  /// Get local element id
  Size leid() const;

  /// set the number of element modes that influence this side
  void nModes(const LocalSize nModes) { info->nModes(nModes); }
  /// return the number of element modes that influence this side
  LocalSize nModes() const { return info->nModes(); }

  /// Set the number of points in the a-direction
  void q1(const LocalSize q1) { info->q1(q1); }
  /// Get the number of points in the a-direction
  LocalSize q1() const { return info->q1(); }

  /// Set the number of points in the b-direction
  void q2(const LocalSize q2) { info->q2(q2); }
  /// Get the number of points in the b-direction
  LocalSize q2() const { return info->q2(); }

  /// Number of quad points
  LocalSize qtot() const { return q1()*(q2() ? q2() : 1); }

  /// Set the side flip in the a-direction
  void flip(const bool flip_a) { info->flip_a(flip_a); }
  /// Get the side flip in the a-direction
  bool flip() const { return info->flip_a(); }

  /// Set the side flip in the a-direction
  void flip_a(const bool flip_a) { info->flip_a(flip_a); }
  /// Get the side flip in the a-direction
  bool flip_a() const { return info->flip_a(); }

  /// Set the side flip in the b-direction
  void flip_b(const bool flip_b) { info->flip_b(flip_b); }
  /// Get the side flip in the b-direction
  bool flip_b() const { return info->flip_b(); }

  /// Set the side transpose
  void transp(const bool transp) { info->transp(transp); }
  /// Get the side transpose
  bool transp() const { return info->transp(); }

  /// Set whether on boundary
  void bc(const bool bc) { info->bc(bc); }
  /// Get whether on boundary
  bool bc() const { return info->bc(); }

  /// Set the side integration method
  void Gauss_Lobatto(const bool GL) { info->Gauss_Lobatto(GL); }
  /// Get the side integration method
  bool Gauss_Lobatto() const { return info->Gauss_Lobatto(); }

  /// set the measure
  void measure(const Scalar measure) { info->measure(measure); }
  /// get the measure
  Scalar measure() const { return info->measure(); }

  /// set the inverse normal length
  void h_n_inv(const Scalar h_n_inv) { info->h_n_inv(h_n_inv); }
  /// get the inverse normal length
  Scalar h_n_inv() const { return info->h_n_inv(); }

  /// make an interpolation matrix for this side
  virtual Scalar make_interpolation_matrix(const Ordinal ,
                                           const Ordinal ,
                                           const vector<Point>&,
                                           const vector<Point>&) = 0;

  /// determine if an id is undefined
  template <typename T>
  static bool undefined(const T i) {
    return MyInfo::undefined(i);
  }
  /// determine if an id is defined
  template <typename T>
  static bool defined(const T i) {
    return !MyInfo::undefined(i);
  }

  /// \name Accessors for normals and Jacobian
  //@{
  MyInfo::vec & nx() { return info->nx(); }
  Scalar & nx(const LocalSize i) { return info->nx(i); }
  const MyInfo::vec & nx() const { return info->nx(); }
  const Scalar & nx(const LocalSize i) const { return info->nx(i); }

  MyInfo::vec & ny() { return info->ny(); }
  Scalar & ny(const LocalSize i) { return info->ny(i); }
  const MyInfo::vec & ny() const { return info->ny(); }
  const Scalar & ny(const LocalSize i) const { return info->ny(i); }

  MyInfo::vec & nz() { return info->nz(); }
  Scalar & nz(const LocalSize i) { return info->nz(i); }
  const MyInfo::vec & nz() const { return info->nz(); }
  const Scalar & nz(const LocalSize i) const { return info->nz(i); }

  MyInfo::vec & J() { return info->J(); }
  Scalar & J(const LocalSize i) { return info->J(i); }
  const MyInfo::vec & J() const { return info->J(); }
  const Scalar & J(const LocalSize i) const { return info->J(i); }

  const vector<Ptr> &subsides() const { return subside; }
  vector<Ptr> &subsides()             { return subside; }

  MyInfo::vec & J_orig() { return info->J_orig(); }
  const MyInfo::vec & J_orig() const { return info->J_orig(); }
  Scalar & J_orig(const LocalSize i) { return info->J_orig(i); }
  MyInfo::vec & J_scale() { return info->J_scale(); }
  const MyInfo::vec & J_scale() const { return info->J_scale(); }
  Scalar & J_scale(const LocalSize i) { return info->J_scale(i); }
  //@}

protected :
  Side & deep_copy_info(const Side & );
#ifdef DGM_USE_MD_COUPLE
  Side( const Side * );
#else
protected:
  Side( const Side * );
#endif
#ifdef DGM_USE_GENERAL_GHOSTING
private:
    friend class boost::serialization::access;
  /*!
   * \brief Serialization of Side class
   *
   * - Vectors are serialized, so geometry information travels along with the
   *   element
   * - We don't serialize pointers to other objects here.  These connections
   *   are rebuilt on the target processor
   */
  template<class Archive>
  void serialize(Archive &ar, const unsigned int version) {
    ar & info;
#ifndef DGM_CONTIGUOUS
    ar & u;
#endif
  }
public:
  Side();            ///< default constructor, used for deserialization
#else
protected:
  Side();
#endif
  Side( const Side & );
};

} // namespace DGM

#endif  // DGM_SIDE_HPP
