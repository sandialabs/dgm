/** \file BaseHex.hpp
 *  \brief Has declarations that are common to all Hex Element
 *  \author Scott Collis
*/
#ifndef DGM_BASEHEX_HPP
#define DGM_BASEHEX_HPP

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

namespace DGM {

/// Base Hexahedral Element class
/** Put methods here that are general to all Hexahedral elements. */
class BaseHex : public Element {

protected:

  /// Default constructor is protected so that only derived types can construct
  inline BaseHex() : Element() {}

public:

  /// constructor
  inline BaseHex(const Ordinal ID, const Basis::Type TYPE) : Element(ID,TYPE) {}

  /// destructor
  virtual ~BaseHex() {}

  static void make_basis(Basis *psi, Basis::Type type=Basis::Ortho,
                         const int der=0);

  /// Generate the side mapping accounting for flips
  virtual inline Ordinal sideMap(const Side *s, const Ordinal ql ) const; 
  virtual inline void    sideMap(const Side *s, const Ordinal qt, Ordinal *k ) const; 

  /// Find the local coordinates
  virtual Point get_local_coordinates(const Point &p) const;

  /// Find the local coordinates \f$(r,s)\f$ at the point \f$p\f$
  virtual int get_local_coordinates(const Point &p, 
                                    Scalar &r, Scalar &s, Scalar &t) const;

  vector<Point> get_side_endpoints(const Ordinal s) const;
  virtual void push_to_subsides() const;
  virtual void push_side_geom_to_subside(Side*, const Side*,const Scalar) const;
  virtual Scalar compute_subside_geometry(Side *, const Element &) const;
  virtual Scalar compute_subside_geometry(Side *, const vector<Point> &) const;

  static void triangle_lift (
           dVector   &h,
     const dVector   &f,
     const Ordinal side,
     const Face     *Us,
     const Basis   *psi,
     const bool     GaussLobatto);

  static  void quad_lift (
           dVector   &h,
     const dVector   &f,
     const Ordinal side,
     const Face     *Us,
     const Basis   *psi,
     const bool     GaussLobatto);

  static void non_self_simular_lift (
           dVector   &h,
     const dVector   &f,  
     const Ordinal side,
     const Face     *Us, 
     const Basis   *psi,
     const bool    GaussLobatto);

#ifdef DGM_USE_GENERAL_GHOSTING
  private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
      ar & boost::serialization::base_object<Element>(*this);
    }
#endif

  protected:

    void side_mode(const Ordinal, Mode*, dVector &) const;
    void side_mode(const Ordinal, Mode, dVector &) const;

    /// VertMode for Hex elements with same 1d basis in each direction
    class VertMode : public BaseVertMode {
      Ordinal nVerts;
      Ordinal L;
      Ordinal qa;
      Ordinal qb;
      Ordinal qc;
      dVector amem;
      dVector bmem;
      dVector cmem;
      dVector v1;
      dVector v2;
    public:
      typedef DGM::Shared<VertMode>::Ptr Ptr;
      VertMode(Basis *b) : nVerts(b->nVerts), L(b->L),
      qa(b->qa), qb(b->qb), qc(b->qc),
      amem(b->amem), bmem(b->bmem), cmem(b->cmem) {
        // there are really only two independent vertex modes
        v1.alias(amem,0,qa); v2.alias(amem,qa+qa*(L-2),qa);
        if ( !((qa == qb) && (qa == qc)) )
          throw DGM::exception("BaseHex::VertMap requires that the 1d basis"
              " be the same in each coordinate direction");
      }
      Mode operator()(const Ordinal id) const {
        Mode v;
        assert(id < nVerts);
        switch(id) {
        case 0:
          v.a.alias(v1); v.b.alias(v1); v.c.alias(v1);
          break;
        case 1:
          v.a.alias(v2); v.b.alias(v1); v.c.alias(v1);
          break;
        case 2:
          v.a.alias(v2); v.b.alias(v2); v.c.alias(v1);
          break;
        case 3:
          v.a.alias(v1); v.b.alias(v2); v.c.alias(v1);
          break;
        case 4:
          v.a.alias(v1); v.b.alias(v1); v.c.alias(v2);
          break;
        case 5:
          v.a.alias(v2); v.b.alias(v1); v.c.alias(v2);
          break;
        case 6:
          v.a.alias(v2); v.b.alias(v2); v.c.alias(v2);
          break;
        case 7:
          v.a.alias(v1); v.b.alias(v2); v.c.alias(v2);
          break;
        default:
          throw DGM::exception("BaseHex::VertMap illegal vertex id"+
                               asString(id));
          break;
        }
        return v;
      }
      const dVector &get_v1() const { return v1; }
      const dVector &get_v2() const { return v2; }
    };

    class EdgeMode : public BaseEdgeMode {
      Ordinal nEdges;
      Ordinal L;
      Ordinal qa;
      Ordinal qb;
      Ordinal qc;
      dVector amem;
      dVector bmem;
      dVector cmem;
      VertMode vertMode;
      dVector v1;
      dVector v2;
      dVector ei;
    public:
      EdgeMode(Basis *b, const VertMode *vm) :
        nEdges(b->nEdges), L(b->L), qa(b->qa), qb(b->qb), qc(b->qc),
        amem(b->amem), bmem(b->bmem), cmem(b->cmem), vertMode(*vm),
        v1(vertMode.get_v1()), v2(vertMode.get_v2()) {
        ei.alias(amem,qa,qa*(L-2));
        if ( !((qa == qb) && (qa == qc)) )
          throw DGM::exception("BaseHex::EdgeMap requires that the 1d basis"
              " be the same in each coordinate direction");
      }
      Mode operator()(const Ordinal id, const Ordinal mode) const {
        Mode e;
        assert(id < nEdges);
        dVector ef;
        ef.alias(ei,mode*qa,qa);
        switch (id) {
        case 0:
          e.a.alias(ef); e.b.alias(v1); e.c.alias(v1);
          break;
        case 1:
          e.b.alias(ef); e.a.alias(v2); e.c.alias(v1);
          break;
        case 2:
          e.a.alias(ef); e.b.alias(v2); e.c.alias(v1);
          break;
        case 3:
          e.b.alias(ef); e.a.alias(v1); e.c.alias(v1);
          break;
        case 4:
          e.c.alias(ef); e.a.alias(v1); e.b.alias(v1);
          break;
        case 5:
          e.c.alias(ef); e.a.alias(v2); e.b.alias(v1);
          break;
        case 6:
          e.c.alias(ef); e.a.alias(v2); e.b.alias(v2);
          break;
        case 7:
          e.c.alias(ef); e.a.alias(v1); e.b.alias(v2);
          break;
        case 8:
          e.a.alias(ef); e.b.alias(v1); e.c.alias(v2);
          break;
        case 9:
          e.b.alias(ef); e.a.alias(v2); e.c.alias(v2);
          break;
        case 10:
          e.a.alias(ef); e.b.alias(v2); e.c.alias(v2);
          break;
        case 11:
          e.b.alias(ef); e.a.alias(v1); e.c.alias(v2);
          break;
        default:
          throw DGM::exception("BaseHex::EdgeMode bad id "+asString(id));
        }
        return e;
      }
    };

    class FaceMode : public BaseFaceMode {
      Ordinal nFaces;
      Ordinal L;
      Ordinal qa;
      Ordinal qb;
      Ordinal qc;
      dVector amem;
      dVector bmem;
      dVector cmem;
      VertMode vertMode;
      EdgeMode edgeMode;
      dVector v1;
      dVector v2;
    public:
      FaceMode(Basis *b, const VertMode *vm, const EdgeMode *em) :
        nFaces(b->nFaces), L(b->L), qa(b->qa), qb(b->qb), qc(b->qc),
        amem(b->amem), bmem(b->bmem), cmem(b->cmem),
        vertMode(*vm), edgeMode(*em),
        v1(vertMode.get_v1()), v2(vertMode.get_v2()) {
        if ( !((qa == qb) && (qa == qc)) )
          throw DGM::exception("BaseHex::FaceMap requires that the 1d basis"
              " be the same in each coordinate direction");
      }
      Mode operator()(const Ordinal id, const Ordinal i,
                      const Ordinal j) const {
        Mode f;
        assert(id < nFaces);
        assert( i < L-2 );
        assert( j < L-2 );
        dVector ia( edgeMode(i,i).a );
        dVector ja( edgeMode(0,j).a );
        switch (id) {
        case 0:
          f.a.alias(ja); f.b.alias(ia); f.c.alias(v1);
          break;
        case 1:
          f.a.alias(ja); f.b.alias(v1); f.c.alias(ia);
          break;
        case 2:
          f.a.alias(v2); f.b.alias(ja); f.c.alias(ia);
          break;
        case 3:
          f.a.alias(ja); f.b.alias(v2); f.c.alias(ia);
          break;
        case 4:
          f.a.alias(v1); f.b.alias(ja); f.c.alias(ia);
          break;
        case 5:
          f.a.alias(ja); f.b.alias(ia); f.c.alias(v2);
          break;
        default:
          throw DGM::exception("BaseHex::FaceMode bad id "+asString(id));
        }
        return f;
      }
    };
};

/// Generate the side mapping accounting for rotation and flips
Ordinal BaseHex::sideMap(const Side *s, const Ordinal ql ) const {
  const Ordinal il = ql/s->q2();            // row index
  const Ordinal jl = ql%s->q2();            // column index
  Ordinal i, j;
  if (s->transp()) {
    j = il;
    i = jl;
    if(s->flip_a()) j = (s->q1()-1) - j;    // flip column
    if(s->flip_b()) i = (s->q2()-1) - i;    // flip row
  } else {
    i = il;
    j = jl;
    if(s->flip_a()) i = (s->q1()-1) - i;    // flip row
    if(s->flip_b()) j = (s->q2()-1) - j;    // flip column
  }
  const Ordinal k = j + s->q2()*i;
  return k;
}

/// Generate the side mapping accounting for rotation and flips
void BaseHex::sideMap(const Side *s, const Ordinal qt, Ordinal *k ) const {
  const bool flip_a = s->flip_a();
  const bool flip_b = s->flip_b();
  const Ordinal q1 = s->q1();
  const Ordinal q2 = s->q2();
  if (s->transp()) {
    for (Ordinal ql=0; ql<qt; ++ql) {
      Ordinal j = ql/q2;
      Ordinal i = ql%q2;
      if(flip_a) j = q1 - 1 - j;    // flip column
      if(flip_b) i = q2 - 1 - i;    // flip row
      k[ql] = j + q2*i;
    }
  } else {
    for (Ordinal ql=0; ql<qt; ++ql) {
      Ordinal i = ql/q2;
      Ordinal j = ql%q2;
      if(flip_a) i = q1 - 1 - i;    // flip row
      if(flip_b) j = q2 - 1 - j;    // flip column
      k[ql] = j + q2*i;
    }
  }
}

} // namespace DGM

#endif // DGM_BASEHEX_HPP
