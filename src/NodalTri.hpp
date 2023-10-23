#ifndef DGM_NODAL_TRI_HPP
#define DGM_NODAL_TRI_HPP

/** \file  NodalTri.hpp
    \brief Nodal triangular element declaration. 
    \author Scott Collis
    \author Mike Levy
*/

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

/// NodalTriangle Element class
class NodalTri : public Element {

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

 public:
  static void ClearDBs() {
    gdb.clear(); bdb.bases.clear(); imdb.entry.clear();
  }

#ifdef DGM_USE_MD_COUPLE
  /// Constructor
 NodalTri(const Size, const Ordinal,
          const vector<Point>&, const Model::Type = Model::EULER);
#else
  /// Constructor
  NodalTri(const Size, const Ordinal, const vector<Point>&);
#endif
  /// Copy constructor
  NodalTri(const NodalTri*);

  /// Destructor
  ~NodalTri();

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
  void gradient(const dVector &, dVector &, dVector &) const;
  void gradient(const dVector &, dVector &, dVector &, dVector &) const
    {DGM_UNDEFINED;}
  void gradient(const dVector &, dVector &, char) const;
  void local_gradient(const dVector &, dVector &, dVector &) const;
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
  Scalar interpolate_local_point(const Point &p) const;
  Scalar interpolate_point(const Point &p) const;
  void interpolate_points(const vector<Point>& ps, dVector &vals) const;
  Point get_local_coordinates(const Point &p) const;
  int get_local_coordinates(const Point &p, Scalar &r, Scalar &s) const;
  //@}

  /// \name Side methods
  //@{
  void get_side(const dVector &, const Ordinal, dVector &) const;

  void fill_sides(const dVector &);
  void fill_sides(const dVector &, const dVector &);
  void fill_sides(const dVector &, const dVector &, const dVector&)
    {DGM_UNDEFINED;}
  void fill_sides_uniform(const dVector &);
  void load_side(const dVector &, const Ordinal, dVector &) const;
  virtual void lift(const Element *const, dVector &, const char='n') const;
  Scalar compute_side_integral( dVector &, Ordinal ) const;
  /// Generate the side mapping accounting for rotation and flips
  virtual Ordinal sideMap(const Side *s, const Ordinal ql ) const {
    if(s->flip_a())
      return (s->q1()-1) - ql;  // flip the side
    return ql;
  }
  //@}

  virtual void push_to_subsides() const {DGM_UNDEFINED;}

  virtual Topology::ElementType element_type() const 
    {return Topology::NodalTri;}

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
  int get_weight() const;
  /// Clone this element
  Element* clone() const {return new NodalTri(this);}
  /// update the workspace storage given new information
  virtual void update_workspace(const Ordinal max) const {
    make_workspace(max,max);
  }
  //@}

 protected:

  /// Default constructor -- not allowed
  NodalTri();
};

//============================================================================
//                      I m p l e m e n t a t i o n
//============================================================================

/// Output a NodalTri Element in DGM mesh file format
inline void NodalTri::write_mesh(ostream &f, const unsigned prec) const {
  f << "ELEMENT " << gid() << "  NODALTRI\n";
  f << scientific;
  f.precision(prec);
  for (Ordinal i=0; i<nVerts(); i++)
    f << setw(7+prec) << vert[i]->x << " ";
  f << '\n';
  for (Ordinal i=0; i<nVerts(); i++)
    f << setw(7+prec) << vert[i]->y << " ";
  f << '\n';
}

/// allocate memory for the workspace
inline void NodalTri::make_workspace(const Ordinal qtot, const Ordinal nModes) {
  if (qtot > Qmax) {
    Qmax = qtot;
    g1_wk.resize(Qmax);
    g2_wk.resize(Qmax);
    n1_wk.resize(Qmax);
    n2_wk.resize(Qmax);
    n3_wk.resize(Qmax);
  }
  if (qtot*nModes > Lmax) {
    Lmax = nModes*qtot;
    Lwk.resize(Lmax);
  }
}

} // namespace DGM

#endif  // DGM_NODAL_TRI_HPP
