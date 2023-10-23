/** \file BaseLine.hpp
 *  \brief Has declarations that are common to all Line Element
 *  \author Scott Collis
*/
#ifndef DGM_BASELINE_HPP
#define DGM_BASELINE_HPP

// system includes

// boost includes
#ifdef DGM_USE_GENERAL_GHOSTING
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/singleton.hpp>
#include <boost/serialization/extended_type_info.hpp>
#include <boost/serialization/shared_ptr.hpp>
#endif

// DGM includes
#include "Element.hpp"

namespace DGM {

/// Base Line Element class
/** Put methods here that are general to all Line elements. */
class BaseLine : public Element {

protected:

  /// Default constructor is protected so that only derived types can construct
  inline BaseLine() : Element() {}

public:

  /** v0(Ordinal q) = amem(q)
      v1(Ordinal q) = amem(qa+q). */
  class VertMode : public BaseVertMode {
    Ordinal nVerts;
    Ordinal qa;
    dVector amem;
  public:
    typedef DGM::Shared<VertMode>::Ptr Ptr;
    VertMode(Basis *b) : nVerts(b->nVerts), qa(b->qa), amem(b->amem) {}
    Mode operator()(const Ordinal id) const {
      Mode v;
      assert(id < nVerts);
      const Ordinal aoff = (id==0) ? 0 : qa;
      v.a.alias(amem,aoff,qa);
      return v;
    }
    Ordinal get_nVerts() const { return nVerts; }
  };

  /** e0(mode,q) = amem(2*qa+mode*qa+q). */
  class EdgeMode : public BaseEdgeMode {
    Ordinal nEdges;
    Ordinal qa;
    dVector amem;
    VertMode vertMode;
  public:
    EdgeMode(Basis *b, const VertMode *vm) :
      nEdges(b->nEdges), qa(b->qa), amem(b->amem), vertMode(*vm) {}
    Mode operator()(const Ordinal id, const Ordinal mode) const {
      Mode e;
      assert(id < nEdges);
      const Ordinal aoff = 2*qa + mode*qa;
      e.a.alias(amem,aoff,qa);
      return e;
    }
  };

  /// constructor
  inline BaseLine(const Ordinal ID, const Basis::Type TYPE) : 
    Element(ID,TYPE) {}

  /// destructor
  virtual ~BaseLine() {}

  /// make the basis for Line elements
  static void make_basis(Basis *psi, const Basis::Type type=Basis::Ortho,
                         const int der=0);

  /// Generate the side mapping accounting for flips
  virtual Ordinal sideMap(const Side *s, const Ordinal ql ) const {
    return ql;
  }

  /// Find the local coordinates
  Point get_local_coordinates(const Point &p) const;

  /// Find the local coordinates \f$(r)\f$ at the point \f$p\f$
  virtual int get_local_coordinates(const Point &p, Scalar &r) const;

  virtual void push_to_subsides() const {DGM_UNDEFINED;}
#ifdef DGM_USE_GENERAL_GHOSTING
  private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
      ar & boost::serialization::base_object<Element>(*this);
    }
#endif

};

} // namespace DGM

#endif // DGM_BASELINE_HPP
