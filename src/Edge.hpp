#ifndef DGM_EDGE_HPP
#define DGM_EDGE_HPP

/** \file Edge.hpp
    \brief Edge declaration
    \author Scott Collis
*/

// system includes
#include <vector>

// DGM includes
#include "Vertex.hpp"
#include "Side.hpp"
#include "Coordinates.hpp"

namespace DGM {

/// One-dimensional side of a two-dimensional Element
class Edge : public Side {
 public:
#ifdef DGM_USE_MD_COUPLE
  /// Constructor for multi-domain problems
  Edge( const Ordinal, Element*, const Ordinal, const Ordinal,
        const Model::Type=Model::EULER);
#else
  /// Single domain constructor
  Edge( const Ordinal, Element*, const Ordinal, const Ordinal, const bool);
#endif
  /// Copy constructor
  Edge( const Edge& );
  /// Copy constructor
  Edge( const Edge* );

  /// Destructor
  virtual ~Edge();

  // local methods
  virtual Side* clone() const {return new Edge(this);}
  virtual Side* deep_copy() const;
  Edge& operator=(const Edge& );
  void print() const {cout<<"Edge "<<endl;}
  /// returns whether this side has subsides
  virtual bool has_subsides() const {
    return interpolate_from_side_to_subside.size();
  }
  /// Push values from sides to all subsides, interpolating as needed.
  virtual void push_to_subsides();
  /// Push values from vector to owned vector u where "this" is a subside.
  virtual void push_to_subside(const dVector &);
  /// Push values from vector to another vector where "this" is a subside.
  virtual void push_to_subside(const dVector &, dVector &) const;
  /// create a matrix to project values from a side to subside.
  virtual Scalar make_interpolation_matrix(const Ordinal q2,
                                           const Ordinal,
                                           const std::vector<Point>&,
                                           const std::vector<Point>&);
  /// helper to make a 1d interpolation matrix
  static void make_1d_interpolation_matrix(dMatrix &,
                                           const Ordinal,
                                           const Ordinal,
                                           const Scalar,
                                           const Scalar,
                                           const bool);
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
  /// test serialization process for this class
  static int test_serialization();
  Edge();            ///< default constructor, used for deserialization
#else
 protected:

  /// Do not allow default constructor
  Edge();
#endif

 private:

  dMatrix interpolate_from_side_to_subside;

};

} // namespace DGM

#endif  // DGM_EDGE_HPP
