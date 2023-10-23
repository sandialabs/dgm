#ifndef DGM_FACE_HPP
#define DGM_FACE_HPP

/** \file Face.hpp
    \brief DGM Face declaration
    \author Scott Collis
*/

// system includes
#include <string>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

// DGM includes
#include "Vertex.hpp"
#include "Side.hpp"
#include "Coordinates.hpp"
#include "Basis.hpp"

namespace DGM {

/// Two-dimensional side of a three-dimensional Element
class Face : public Side {
 public:

  //dVector sx, sy, tz;       // components of first unit tangent vector
  //dVector tx, ty, tz;       // components of second unit tangent vector

  /// Constructor
  Face( const Ordinal, Element *, const Ordinal, 
        const Ordinal, const Ordinal, const bool);
  /// Copy constructor
  Face( const Face& );
  /// Copy constructor
  Face( const Face* );

  /// Destructor
  virtual ~Face();

  // local methods
  virtual Side* clone() const {return new Face(this);}
  virtual Side* deep_copy () const;
  Face& operator=(const Face& );
  void print() const { cout<<"Face"<<endl; }

  virtual bool has_subsides() const {
    return interpolate_from_side_to_subside_x.size();
  }
  bool subside_self_simular_to_side() const { return self_simular; }
  virtual void push_to_subsides();
  /// Push values from vector to owned vector u where "this" is a subside.
  virtual void push_to_subside(const dVector &);
  /// Pull values from vector to another vector where "this" is a subside.
  virtual void push_to_subside(const dVector &, dVector &) const;
  void push_to_subside_x(const dVector &s, dVector &u) const;
  void push_to_subside_y(const dVector &s, dVector &u) const;

  /// create a matrix to project values from a side to subside.
  bool quad_parametric_coord_3d(Point &para,
                                const Point &P, 
                                const vector<Point> &C);
  virtual Scalar make_interpolation_matrix(const Ordinal,
                                           const Ordinal,
                                           const vector<Point>&,
                                           const vector<Point>&);

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
    ar & boost::serialization::base_object<Side>(*this);
  }
 public:
  Face();            ///< default constructor, used for deserialization
#else
 protected:

  /// Do not allow default constructor
  Face();

#endif
 private :
  dMatrix interpolate_from_side_to_subside_x;
  dMatrix interpolate_from_side_to_subside_y;
  bool    self_simular;
 public:
  DGM::Shared<Basis>::Ptr psi;  // Lift Vandermond matrix for variable p
                                // spectral elements. 
};

} // namespace DGM

#endif  // DGM_FACE_HPP
