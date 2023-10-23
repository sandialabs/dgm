#ifndef DGM_TRI_HPP
#define DGM_TRI_HPP

/** \file  Tri.hpp
    \brief Modal triangular element declaration
    \author Scott Collis
*/

// system includes
#include <string>
#include <map>
#include <algorithm>
#ifdef DGM_USE_GENERAL_GHOSTING
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/split_member.hpp>
#endif

// DGM includes
#include "Element.hpp"

namespace DGM {

//============================================================================
//                        D e c l a r a t i o n
//============================================================================

/// Triangle Element class
class Tri : public Element {

  typedef GeometryDBSetApprox GeometryDB;  ///< Set the type of GeometryDB to be used

  static BasisDB bdb;      ///< Basis database
  static GeometryDB  gdb;      ///< Geom database
  static IMDB imdb;        ///< Interpolation database

  static Ordinal Qmax;     ///< Maximum number of total quadrature points
  static Ordinal Lmax;     ///< Maximum number of total modes

  static dVector g1_wk;    ///< Workspace for gradients
  static dVector g2_wk;    ///< Workspace for gradients

  static dVector n1_wk;    ///< Workspace for norms
  static dVector n2_wk;    ///< Workspace for norms
  static dVector n3_wk;    ///< Workspace for norms
  static dVector Lwk;      ///< Workspace for modal coefficients

  static bool first_warn;  ///< Ensures that only one warning is generated

 public:
  static void ClearDBs() {
    gdb.clear(); bdb.bases.clear(); imdb.entry.clear();
  }

#ifdef DGM_USE_MD_COUPLE
  /// Constructor
 Tri(const Size, const Ordinal, const Ordinal,
     const vector<Point>&, const Model::Type = Model::EULER);
#else
  /// Constructor
  Tri(const Size, const Ordinal, const Ordinal,
      const vector<Point>&);
#endif
  /// Copy constructor
  Tri(const Tri*);

  /// Destructor
  virtual ~Tri();

  // static member functions
  static void make_workspace(const Ordinal, const Ordinal);
  static void make_basis(Basis*, const int);
  static void make_interpolation_matrix(const Ordinal, const Ordinal,
                                        const Interp::Type, dMatrix &);
  static dMatrix* get_interpolation_matrix(const Ordinal, const Ordinal,
                                           const Interp::Type);

  // Override Element methods

  /// \name Initialization
  //@{
  void get_mass_matrix();
  void get_mass_matrix(const dVector &);
  void get_1d_mass_matrix(Minfo &) const;
  void get_derivative_matrix();
  void fill(string, Operation operation=Equal);
  void fill(Mode &);
  void fill(Mode &, dVector &) const;
  void random();
  void set(const dVector &, const Ordinal);
  //@}

  /// \name Local assembly methods
  //@{
  void normal_times_gradient_side(const dVector &, const int, dVector &) const;
  //@}

  /// \name Transforms methods
  //@{
  Basis* get_basis(const int der) const;
  void inner_product();
  void inner_product(dVector &, dVector &) const;
  void forward_transform();
  void forward_transform(dVector &, dVector &) const;
  void forward_transform(Element *, Element *);
  void backward_transform();
  void backward_transform(dVector &, dVector &) const;
  void solve_mass_matrix(dVector &) const;
  void interpolate_to_uniform();
  //@}

  /// \name Filter methods
  //@{
  void make_constant();
  void low_modes(const Ordinal np);
  void kill_constant();
  void filter(const dVector &) {DGM_UNDEFINED;}
  void coarse_scales(const int) {DGM_UNDEFINED;}
  void coarse_scales(const int, dVector &) {DGM_UNDEFINED;}
  void fine_scales(const int) {DGM_UNDEFINED;}
  void fine_scales(const int p_inc, dVector &) {DGM_UNDEFINED;}
  void fine_scales_transform(const int p_inc, dVector &) const;
  //@}

  /// \name Derivative methods
  //@{
  /// 1d gradient not defined for Tri
  void gradient(const dVector &, dVector &) const {DGM_UNDEFINED;}
  void gradient(const dVector &, dVector &, dVector &) const;
  /// 3d gradient not defined for Tri
  void gradient(const dVector &, dVector &, dVector &, dVector &) const
    {DGM_UNDEFINED;}
  void gradient(const dVector &, dVector &, char) const;
  void local_gradient(const dVector &, dVector &, dVector &) const;
  /// 3d local gradient not defined for Tri
  void local_gradient(const dVector &, dVector &, dVector &, dVector &) const
    {DGM_UNDEFINED;}
  //@}

  /// \name Geometry methods
  //@{
  void get_coordinates();
  void get_straight_coordinates();
  void get_curved_coordinates();
  void get_side_coordinates(const Ordinal, Point *)const;
  void compute_geometry();
  void compute_straight_geometry();
  void compute_curved_geometry();
  StabMetrics compute_metrics();
  void compute_side_geometry();
  void forward_transform_side(dVector &, dVector &);
  void add_Dirac_delta(const Ordinal qpt, const Scalar amp);
  void add_Dirac_delta(const Point &p, const Scalar amp);
  void add_local_Dirac_delta(const Point &p, const Scalar amp);

  virtual void push_to_subsides() const {DGM_UNDEFINED;}

  Scalar interpolate_point(const Point &p) const;
  Scalar interpolate_local_point(const Point &p) const;
  virtual void calculate_interpolation_matrices(vector<fMatrix>&,
                                                const vector<Point>&) const;
  virtual void apply_interpolation_matrices(dVector &vals,
                                            const vector<fMatrix>&) const;
  virtual void calculate_interpolation_matrices(vector<dMatrix>&,
                                                const vector<Point>&) const;
  virtual void apply_interpolation_matrices(dVector &vals,
                                            const vector<dMatrix>&) const;
  void interpolate_points(const vector<Point>& ps, dVector &vals) const;
  Point get_local_coordinates(const Point &p) const;
  int get_local_coordinates(const Point &p, Scalar &r, Scalar &s) const;
  //@}

  virtual Topology::ElementType element_type() const {return Topology::Tri;}

  /// \name Side methods
  //@{
  void get_side(const dVector &, const Ordinal, dVector &) const;
  void fill_sides(const dVector &);
  void fill_sides(const dVector &, const dVector &);
  /// 3d version is undefined
  void fill_sides(const dVector &, const dVector &, const dVector&)
    {DGM_UNDEFINED;}
  void fill_sides_uniform(const dVector &);
  void load_side(const dVector &, const Ordinal, dVector &) const;
  virtual void lift(const Element *const, dVector &, const char='n') const;
  Scalar compute_side_integral( dVector &, Ordinal ) const;
  /// Generate the side mapping accounting flips
  virtual Ordinal sideMap(const Side *s, const Ordinal ql ) const {
    if(s->flip_a())
      return (s->q1()-1) - ql;  // flip the side
    return ql;
  }
  //@}

  /// \name Curved side methods
  //@{
  virtual void get_curved_side_info(const Ordinal, vector<Point> &,
                                    dVector &, int &) const;
  void J_backward_transform(dVector &, dVector &);
  void solve_1d_mass_matrix(dVector &) const;
  //@}

  /// \name Norm and inner product methods
  //@{
  Scalar norm_Linf() const;
  Scalar norm_L2() const;
  Scalar norm_H1() const;
  void norm_L2(Scalar *, Scalar *) const;
  void norm_H1(Scalar *, Scalar *) const;
  Scalar integrate( Scalar *area=NULL ) const;
  Scalar integrate( const dVector &, Scalar *area=NULL) const;
  Scalar compute_measure() const;
  Scalar L2_inner_product(const Element*, Scalar *area=NULL) const;
  Scalar L2_inner_product(const dVector &x, const dVector &y,
                          Scalar *area=NULL) const;
  //@}

  /// \name Spatial regularization for optimal control
  //@{
  void get_side_Ds(const int, const dVector&, dVector&) const;
  void get_side_curvature(const int, dVector &) const;
  //@}

  /// \name Utilities
  //@{
  void tecplot(FILE *);
  void output(FILE *, const char='d') const;
  streamoff binaryLength(const OutputType flag) const;
  void binaryOutput(FILE *, const OutputType flag) const;
  inline void write_mesh(ostream &, const unsigned prec) const;
  void get_weight_props(Topology::ElementType&, bool&, Ordinal&) const;
  int get_weight() const;
  /// Clone this element
  Element* clone() const {return new Tri(this);}
  /// update the workspace storage given new information
  virtual void update_workspace(const Ordinal max) const {
    make_workspace(max,max);
  }
  //@}

#ifdef DGM_USE_GENERAL_GHOSTING

 private:
  /// gives boost access to private data
  friend class boost::serialization::access;

  /*! write this class to archive
   *
   * @tparam Archive boost input or output archive class
   * @param ar       archive
   * @param version  (not needed here, see boost documentation)
   */
  template<class Archive>
  void save(Archive & ar, const unsigned int version) const {
    ar & boost::serialization::base_object<Element>(*this);
  }
  /*! load this class from archive
   *
   * @tparam Archive boost input or output archive class
   * @param ar       archive
   * @param version  (not needed here, see boost documentation)
   */
  template<class Archive>
  void load(Archive & ar, const unsigned int version) {
    ar & boost::serialization::base_object<Element>(*this);
    side.resize(nEdges());
    for (Ordinal i=0; i<nEdges(); i++) {
      side[i] = &(edge[i]);
      side[i]->elink = this;
      side[i]->geid(gid());  // should be true by serialization?
      for (size_t j=0; j<side[i]->subsides().size(); j++) {
        side[i]->subsides()[j]->elink = this;
      }
    }

    // Form the basis functions
    psi = get_basis(0);

    // collocation derivative matrix
    get_derivative_matrix();
  }
  BOOST_SERIALIZATION_SPLIT_MEMBER()
protected:
  /// Default constructor -- allowed only for deserialization
  /// Note: we have to update all data or pointers, which were not serialized.
  /// this can not be done in this constructor, since the data is not there yet.
  Tri() {};
#else
 protected:
  /// Default constructor -- not allowed
  Tri();
#endif

 private:

  class VertMode : public BaseVertMode {
    Ordinal nVerts, qa, qb;
    dVector amem, bmem;
  public:
    typedef DGM::Shared<VertMode>::Ptr Ptr;
    VertMode(Basis *b) : nVerts(b->nVerts), qa(b->qa), qb(b->qb),
        amem(b->amem), bmem(b->bmem) {}
    Mode operator()(const Ordinal id) const {
      Mode v;
      assert(id < nVerts);
      switch (id) {
      case 0:
        v.a.alias(amem,2*qa,qa);
        v.b.alias(bmem,qb,qb);
        break;
      case 1:
        v.a.alias(amem,qa,qa);
        v.b.alias(bmem,qb,qb);
        break;
      case 2:
        v.a.alias(amem,0,qa);
        v.b.alias(bmem,0,qb);
        break;
      default:
        throw DGM::exception("Tri::VertMode illegal vertex id = "+asString(id));
      }
      return v;
    }
  };

  class EdgeMode : public BaseEdgeMode {
    Ordinal nEdges, L, qa, qb;
    dVector amem, bmem;
    VertMode vertMode;
  public:
    /// compute variable factor in Tri mode mapping
    Ordinal fact(const Ordinal i) const {
      Ordinal r=i;
      if (L > 3) for (Ordinal j=0; j<i; j++) r += L-3-j;
      return r;
    }
    EdgeMode(Basis *b, const VertMode *vm) :
      nEdges(b->nEdges), L(b->L), qa(b->qa), qb(b->qb),
      amem(b->amem), bmem(b->bmem), vertMode(*vm) {}
    Mode operator()(const Ordinal id, const Ordinal i) const {
      Mode e;
      if (L <= 2)
        throw DGM::exception("Tri::EdgeMode no edge modes when L <= 2");
      assert(id < nEdges);
      assert(i + 2 < L);
      const Ordinal aoff = 3*qa + i*qa;
      const Ordinal boff = 2*qb + i*qb;
      //const Ordinal inc = L > 3 ? L-3-(i-1) : 0;
      //const Ordinal boff0 = 2*qb + (L-2)*qb + i*(qb+inc*qb);
      const Ordinal boff0 = 2*qb + (L-2)*qb + fact(i)*qb;
      switch (id) {
      case 0:
        e.a.alias(amem,aoff,qa);
        e.b.alias(bmem,boff0,qb);
        break;
      case 1:
        e.a.alias(vertMode(1).a);
        e.b.alias(bmem,boff,qb);
        break;
      case 2:
        e.a.alias(vertMode(0).a);
        e.b.alias(bmem,boff,qb);
        break;
      default:
        throw DGM::exception("Tri::edge bad id "+asString(id));
      }
      return e;
    }
  };

  class FaceMode : public BaseFaceMode {
    Ordinal nFaces, L, qb;
    dVector amem, bmem;
    VertMode vertMode;
    EdgeMode edgeMode;
  public:
    FaceMode(Basis *b, const VertMode *vm, const EdgeMode *em) :
      nFaces(b->nFaces), L(b->L), qb(b->qb), amem(b->amem), bmem(b->bmem),
      vertMode(*vm), edgeMode(*em) {}
    Mode operator()(const Ordinal id, const Ordinal i, const Ordinal j) const {
        Mode f;
        if (L <= 3)
          throw DGM::exception("Tri::FaceMode no face modes when L <= 3");
        assert(id < nFaces);
        assert(i < L-3 );
        assert(j < L-3-i);
        const Ordinal boff = 2*qb + (L-2)*qb + edgeMode.fact(i)*qb + qb + j*qb;
        f.a.alias( edgeMode(0,i).a );
        f.b.alias( bmem, boff, qb );
        return f;
    }
  };

};

//============================================================================
//                      I m p l e m e n t a t i o n
//============================================================================

/// Output a Tri Element in DGM mesh file format
inline void Tri::write_mesh(ostream &f, const unsigned prec) const {
  f << "ELEMENT " << gid() << "  TRI\n";
  f << scientific;
  f.precision(prec);
  for (Ordinal i=0; i<nVerts(); i++)
    f << setw(7+prec) << vert[i]->x << " ";
  f << '\n';
  for (Ordinal i=0; i<nVerts(); i++)
    f << setw(7+prec) << vert[i]->y << " ";
  f << '\n';
}

/// Allocate memory for the Tri workspace
inline void Tri::make_workspace(const Ordinal qtot, const Ordinal nModes) {
  if (qtot > Qmax) {
    Qmax = qtot;
    g1_wk.resize(Qmax); g1_wk = 0;
    g2_wk.resize(Qmax); g2_wk = 0;
    n1_wk.resize(Qmax); n1_wk = 0;
    n2_wk.resize(Qmax); n2_wk = 0;
    n3_wk.resize(Qmax); n3_wk = 0;
  }
  if (qtot*nModes > Lmax) {
    Lmax = nModes*qtot;
    Lwk.resize(Lmax); Lwk = 0;
  }
}

} // namespace DGM

#endif  // DGM_TRI_HPP
