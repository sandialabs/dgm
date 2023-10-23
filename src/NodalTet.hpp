#ifndef DGM_NODAL_TET_HPP
#define DGM_NODAL_TET_HPP

/** \file  NodalTet.hpp
    \brief Nodal tetrahedral element declaration. */

// system includes
#include <string>
#include <map>
#include <algorithm>

// DGM includes
#include "Element.hpp"

namespace DGM {

//============================================================================
//                        D e c l a r a t i o n
//============================================================================

/// NodalTetangle Element class
class NodalTet : public Element {

  typedef GeometryDBSetApprox GeometryDB;  ///< Set the type of GeometryDB to be used

  static BasisDB bdb;        ///< Basis database
  static GeometryDB  gdb;        ///< Geom database
  static IMDB imdb;          ///< Interpolation database
  static DerivDB ddb;        ///< Derivative matrix database
  static VandermondeDB vdb;  ///< Vandermonde matrix database

  static Ordinal Qmax;       ///< Maximum number of total quadrature points
  static Ordinal Lmax;       ///< Maximum number of total modes

  static dVector g1_wk;      ///< Workspace for gradients
  static dVector g2_wk;      ///< Workspace for gradients
  static dVector g3_wk;      ///< Workspace for gradients

  static dVector n1_wk;      ///< Workspace for norms
  static dVector n2_wk;      ///< Workspace for norms
  static dVector n3_wk;      ///< Workspace for norms
  static dVector n4_wk;      ///< Workspace for norms
  static dVector n5_wk;      ///< Workspace for norms
  static dVector Lwk;        ///< Workspace for modal coefficients

 public:
 static void ClearDBs() {
   gdb.clear(); bdb.bases.clear(); imdb.entry.clear();
 }

#ifdef DGM_USE_MD_COUPLE
  /// Constructor
 NodalTet(const Size, const Ordinal, const vector<Point>&,
          const Model::Type = Model::EULER);
#else
  /// Constructor
  NodalTet(const Size, const Ordinal, const vector<Point>&);
#endif
  /// Copy constructor
  NodalTet(const NodalTet*);

  /// Destructor
  ~NodalTet();

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
  /// Project to polynomial space in place is a null-op for nodal
  void project() {}
  /// Project to polynomial space is a null-op for nodal
  void project(dVector &x) const {}
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
  void fine_scales_transform(const int p_inc, dVector &) const {DGM_UNDEFINED;}
  //@}

  /// \name Derivative methods
  //@{
  void gradient(const dVector &, dVector &) const {DGM_UNDEFINED;}
  void gradient(const dVector &, dVector &, dVector &) const
    {DGM_UNDEFINED;}
  void gradient(const dVector &, dVector &, dVector &, dVector &) const;
  void gradient(const dVector &, dVector &, char) const;
  void local_gradient(const dVector &, dVector &, dVector &) const
    {DGM_UNDEFINED;}
  void local_gradient(const dVector &, dVector &, dVector &, dVector &) const;
  //@}

  /// \name Geometry methods
  //@{
  void get_coordinates();
  void get_straight_coordinates();
  void get_curved_coordinates();
  void get_side_coordinates(const Ordinal, Point *) const;
  void compute_geometry();
  void compute_straight_geometry();
  void compute_curved_geometry();
  StabMetrics compute_metrics();
  Scalar tet_volume(Ordinal v0, Ordinal v1, Ordinal v2, Ordinal v3);
  void compute_side_geometry();
  void forward_transform_side(dVector &, dVector &);
  void add_Dirac_delta(const Ordinal qpt, const Scalar amp);
  void add_Dirac_delta(const Point &p, const Scalar amp);
  void add_local_Dirac_delta(const Point &p, const Scalar amp);
  Scalar interpolate_local_point(const Point &p) const;
  Scalar interpolate_point(const Point &p) const;
  void interpolate_points(const vector<Point>& ps, dVector &vals) const;
  vector<Point> get_side_endpoints(const Ordinal s) const;
  Point get_local_coordinates(const Point &p) const;
  int get_local_coordinates(const Point &p, Scalar &r, Scalar &s, 
                            Scalar &t) const;
  static void nodal_tet_quadrature(Scalar X[], Scalar Y[], Scalar Z[],
                                   const std::vector<DGM::Vertex::Ptr> &vert, 
                                   const Ordinal N);
  static void nodal_tet_quadrature(std::vector<Point> &Q,
                                   const std::vector<Point> &P, 
                                   const Ordinal N);


  //@}

  /// \name Side methods
  //@{
  void interpolate_to_side(const dVector &from, dVector &to) const;

  void get_side(const dVector &, const Ordinal, dVector &) const;
  void fill_sides(const dVector &);
  void fill_sides(const dVector &, const dVector &)
    {DGM_UNDEFINED;}
  void fill_sides(const dVector &, const dVector &, const dVector&);
  void fill_sides_uniform(const dVector &);
  void load_side(const dVector &, const Ordinal, dVector &) const;
  virtual void lift(const Element *const, dVector &, const char='n') const;
  Scalar compute_side_integral( dVector &, Ordinal ) const;
  Ordinal sideMap(const Side *s, const Ordinal ql ) const ;
  //@}

  static Ordinal vertex_num(const Ordinal i, const Ordinal j);
  virtual Ordinal sideVertMap(const Ordinal lsid, const Ordinal lvid) const {
    return vertex_num(lsid, lvid);
  }

  static const dMatrix& side_vandermond(const Ordinal p);
  static const dMatrix& side_interpolation(const Ordinal p, const Ordinal q);

  virtual Topology::ElementType element_type() const 
    {return Topology::NodalTet;}

  virtual void push_to_subsides() const {DGM_UNDEFINED;}

  /// \name Curved side methods
  //@{
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
  Scalar integrate( Scalar *volume=NULL ) const;
  Scalar integrate( const dVector &, Scalar *volume=NULL) const;
  Scalar compute_measure() const;
  Scalar L2_inner_product(const Element*, Scalar *volume=NULL) const;
  Scalar L2_inner_product(const dVector &x, const dVector &y,
                          Scalar *volume=NULL) const;
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
  int get_weight() const;
  /// Clone this element
  Element* clone() const {return new NodalTet(this);}
  /// update the workspace storage given new information
  virtual void update_workspace(const Ordinal max) const {
    make_workspace(max,max);
  }
  /// Returns the number of subcells for vizualizing this element
  inline virtual Ordinal ncells() const {
    Ordinal E = 0;
    const Ordinal N = L();
    for (Ordinal i=0; i<N-1; ++i) {
      for (Ordinal j=0; j+i<N-1; ++j) {
        for (Ordinal k=0; k+j+i<N-1; ++k) {
          ++E;
          if (i<N-2 && j+i<N-2 && k+j+i<N-2) E+=4;
          if (0<j && 0<k) ++E;
        }
      }
    }
    return E;
  }
  //@}

 protected:

  /// Default constructor -- not allowed
  NodalTet();
};

//============================================================================
//                      I m p l e m e n t a t i o n
//============================================================================

/// Output a NodalTet Element in DGM mesh file format
inline void NodalTet::write_mesh(ostream &f, const unsigned prec) const {
  f << "ELEMENT " << gid() << "  NODALTET\n";
  f << scientific;
  f.precision(prec);
  for (Ordinal i=0; i<nVerts(); i++)
    f << setw(7+prec) << vert[i]->x << " ";
  f << '\n';
  for (Ordinal i=0; i<nVerts(); i++)
    f << setw(7+prec) << vert[i]->y << " ";
  f << '\n';
  for (Ordinal i=0; i<nVerts(); i++)
    f << setw(7+prec) << vert[i]->z << " ";
  f << '\n';
}

/// allocate memory for the workspace
inline void NodalTet::make_workspace(const Ordinal qtot, const Ordinal nModes) {
  if (qtot > Qmax) {
    Qmax = qtot;
    g1_wk.resize(Qmax);
    g2_wk.resize(Qmax);
    g3_wk.resize(Qmax);
    n1_wk.resize(Qmax);
    n2_wk.resize(Qmax);
    n3_wk.resize(Qmax);
    n4_wk.resize(Qmax);
    n5_wk.resize(Qmax);
  }
  if (qtot*nModes > Lmax) {
    Lmax = nModes*qtot;
    Lwk.resize(Lmax);
  }
}

} // namespace DGM

#endif  // DGM_NODAL_TRI_HPP
