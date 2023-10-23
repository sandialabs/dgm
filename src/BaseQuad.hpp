/** \file BaseQuad.hpp
 *  \brief Has declarations that are common to all Quad Element
 *  \author Scott Collis
*/
#ifndef DGM_BASEQUAD_HPP
#define DGM_BASEQUAD_HPP

// system includes

// boost includes
#ifdef DGM_USE_GENERAL_GHOSTING
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/singleton.hpp>
#include <boost/serialization/shared_ptr.hpp>
#endif

// DGM includes
#include "Element.hpp"
#include "Basis.hpp"

namespace DGM {

/// Base Quadrilateral Element class
/** Put methods here that are general to all Quadrilateral elements. */
class BaseQuad : public Element {

protected:

  /// Default constructor is protected so that only derived types can construct
  inline BaseQuad() : Element() {}

public:

  /// constructor
  inline BaseQuad(const Ordinal ID, const Basis::Type TYPE) 
  : Element(ID,TYPE) {}

  /// destructor
  virtual ~BaseQuad() {}

  /// make the basis for BaseQuad elements
  static void make_basis(Basis *psi, const Basis::Type type=Basis::Ortho,
                         const int der=0);

  /// \name Curved side methods
  //@{
  virtual void get_curved_side_info(const Ordinal, vector<Point> &,
                                    dVector &, int &) const;
  //@}

  /// Generate the side mapping accounting for flips
  virtual Ordinal sideMap(const Side *s, const Ordinal ql ) const {
    if(s->flip_a())
      return (s->q1()-1) - ql;  // flip the side
    return ql;
  }
  /// Find the local coordinates
  Point get_local_coordinates(const Point &p) const;

  /// Find the local coordinates \f$(r,s)\f$ at the point \f$p\f$
  virtual int get_local_coordinates(const Point &p, Scalar &r, Scalar &s) const;

  virtual void push_to_subsides() const;
  virtual vector<Point> get_side_endpoints(const Ordinal) const;
  virtual Scalar compute_subside_geometry(Side *, const Element &) const;
  virtual Scalar compute_subside_geometry(Side *, const vector<Point> &) const;
  virtual void push_side_geom_to_subside(Side*,const Side*,const Scalar) const;

#ifdef DGM_USE_GENERAL_GHOSTING
  private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
      ar & boost::serialization::base_object<Element>(*this);
    }
#endif

  protected:

    /**
      \verbatim
      a modes
      v0(Ordinal q) = amem(q);
      v1(Ordinal q) = amem(qa+q);
      v2(Ordinal q) = v1(a);
      v3(Ordinal q) = v0(q);
      b modes
      v0(Ordinal q) = bmem(q);
      v1(Ordinal q) = v0(q)
      v2(Ordinal q) = v3(q)
      v3(Ordinal q) = bmem(qb+q);
      \endverbatim
      */
    class VertMode : public BaseVertMode {
      Ordinal nVerts;
      Ordinal qa;
      Ordinal qb;
      dVector amem;
      dVector bmem;
    public:
      typedef DGM::Shared<VertMode>::Ptr Ptr;
      VertMode(Basis *b) : nVerts(b->nVerts), qa(b->qa), qb(b->qb),
          amem(b->amem), bmem(b->bmem) {}
      virtual ~VertMode(){}
      Mode operator()(const Ordinal id) const {
        Mode v;
        //cout << "Id = " << id << ", nVerts = " << nVerts << endl;
        assert(id < nVerts);
        const Ordinal aoff = (id==0 || id==3) ? 0 : qa;
        const Ordinal boff = (id==0 || id==1) ? 0 : qb;
        v.a.alias(amem,aoff,qa);
        v.b.alias(bmem,boff,qb);
        return v;
      }
      VertMode operator=(const VertMode &vm) {
        if (this==&vm) return *this;
        nVerts = vm.nVerts;
        qa = vm.qa;
        qb = vm.qb;
        amem.alias(vm.amem);
        bmem.alias(vm.bmem);
        return *this;
      }
      Ordinal get_nVerts() const { return nVerts; }
    };

    /**
      \verbatim
      a modes
      e0(mode,q) = amem(2*qa+mode*qa+q);
      e1(mode,q) = v1(q);
      e2(mode,q) = e0(mode,q);
      e3(mode,q) = v0(q);
      b modes
      e0(mode,q) = v0(q)
      e1(mode,q) = e3(mode,q)
      e2(mode,q) = v3(q)
      e3(mode,q) = bmem(2*qb+mode*qb+q);
      \endverbatim
      */
    class EdgeMode : public BaseEdgeMode {
      Ordinal nEdges;
      Ordinal qa;
      Ordinal qb;
      dVector amem;
      dVector bmem;
      VertMode vertMode;
    public:
      EdgeMode(Basis *b, const VertMode *vm) :
        nEdges(b->nEdges), qa(b->qa), qb(b->qb),
        amem(b->amem), bmem(b->bmem), vertMode(*vm) {}
      Mode operator()(const Ordinal id, const Ordinal mode) const {
        Mode e;
        assert(id < nEdges);
        const Ordinal aoff = 2*qa + mode*qa;
        const Ordinal boff = 2*qb + mode*qb;
        switch (id) {
        case 0:
          e.a.alias(amem,aoff,qa);
          e.b.alias(vertMode(0).b);
          break;
        case 1:
          e.a.alias(vertMode(1).a);
          e.b.alias(bmem,boff,qb);
          break;
        case 2:
          e.a.alias(amem,aoff,qa);
          e.b.alias(vertMode(3).b);
          break;
        case 3:
          e.a.alias(vertMode(0).a);
          e.b.alias(bmem,boff,qb);
          break;
        default:
          throw DGM::exception("BaseQuad::edge bad id "+asString(id));
        }
        return e;
      }
    };

};

} // namespace DGM

#endif // DGM_BASEQUAD_HPP
