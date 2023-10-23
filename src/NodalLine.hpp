#ifndef DGM_NODAL_LINE_HPP
#define DGM_NODAL_LINE_HPP

/** \file  NodalLine.hpp
    \brief NodalLine element declaration

    This element is implemented based on a Gauss-Lobatto-Legendre node points
    with the number of quadrature points equal to the number of modes.

    The project method for this element simply returns since any sampled
    field on the nodal Lagrange representation is automatically in the
    polynomial space.

    In general, quadrature is not used for the primary solution methods
    although it is used for computing norms and integrals of the solution
    in postprocessing.
*/

// system includes
#include <string>
#include <map>
#include <algorithm>

// DGM includes
#include "Element.hpp"
#include "BaseLine.hpp"

namespace DGM {

//============================================================================
//                        D e c l a r a t i o n
//============================================================================

/// One-dimensional NodalLine Element class
class NodalLine : public BaseLine {

  typedef GeometryDBSetApprox GeometryDB;  ///< Set the type of GeometryDB to be used

  static BasisDB bdb;      ///< Basis database
  static GeometryDB  gdb;      ///< Geom database

  static Ordinal Qmax;     ///< Maximum number of total quadrature points
  static Ordinal Lmax;     ///< Maximum number of total modes

  static dVector g1_wk;    ///< Workspace for gradients
  static dVector g2_wk;    ///< Workspace for gradients
  static dVector g3_wk;    ///< Workspace for gradients
  static dVector g4_wk;    ///< Workspace for gradients
  static dVector g5_wk;    ///< Workspace for gradients
  static dVector Lwk;      ///< Workspace for modal coefficients

 public:
  static void ClearDBs() {
    gdb.clear(); bdb.bases.clear();
  }

  /// Constructor
  NodalLine(const Ordinal, const Ordinal, const vector<Point>&);

  /// Copy constructor
  NodalLine(const NodalLine*);

  /// Destructor
  virtual ~NodalLine();

  // static member functions
  static void make_workspace(const Ordinal, const Ordinal);

  // Override Element virtual methods

  /// \name Initialization
  //@{
  void get_mass_matrix();
  void get_mass_matrix( const dVector & );
  void get_derivative_matrix();
  void fill(string, Operation operation=Equal);
  void fill(Mode &);
  void fill(Mode &, dVector &) const;
  void random();
  void set(const dVector &, const Ordinal);
  //@}

  /// \name Local assembly matrices and residuals
  //@{
  void get_local_mass_matrix(const dVector &);
  void get_local_derivative_matrix();
  void get_local_derivative_matrix(const dVector &);
  void get_local_laplace_matrix();
  void get_local_laplace_matrix(const dVector &);
  void test_on_shape_side(const dVector &, const int, dVector &) const;
  void test_on_grad_shape(const dVector &, char, dVector &) const;
  //@}

  /// \name Transforms methods
  //@{
  Basis* get_basis(const int) const;
  void inner_product();
  void inner_product(dVector &, dVector &) const;
  void forward_transform();
  void forward_transform(dVector &, dVector &) const;
  void forward_transform(Element *, Element *);
  void backward_transform();
  void backward_transform(dVector &, dVector &) const;
  void solve_mass_matrix(dVector &) const;
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
  void coarse_scales(const int p_inc);
  void coarse_scales(const int p_inc, dVector &);
  void fine_scales(const int);
  void fine_scales(const int, dVector &);
  void fine_scales_transform(const int, dVector &) const;
  //@}

  /// \name Derivative methods
  //@{
  void gradient(const dVector &, dVector &) const;
  void gradient(const dVector &, dVector &, dVector &) const;
  void gradient(const dVector &, dVector &, dVector &, dVector &) const
    {DGM_UNDEFINED;}
  void gradient(const dVector &, dVector &, char) const;
  void local_gradient(const dVector &, dVector &, dVector &)
    const {DGM_UNDEFINED;}
  void local_gradient(const dVector &, dVector &, dVector &, dVector &) const
    {DGM_UNDEFINED;}
  //@}

  /// \name Geometry methods
  //@{
  void get_coordinates();
  void compute_geometry();
  StabMetrics compute_metrics();
  void compute_side_geometry();
  void add_Dirac_delta(const Ordinal qpt, const Scalar amp);
  void add_Dirac_delta(const Point &p, const Scalar amp);
  void add_local_Dirac_delta(const Point &p, const Scalar amp);
  void add_local_Dirac_delta(const vector<dMatrix> &M, const Scalar amp);
  Scalar interpolate_local_point(const Point &p) const;
  Scalar interpolate_point(const Point &p) const;
  void interpolate_points(const vector<Point>& ps, dVector &vals) const;
  //@}

  /// \name Side methods
  //@{
  void get_side(const dVector &, const Ordinal, dVector &) const {
    DGM_UNDEFINED;
  }
  void fill_sides(const Scalar, const Operation=Equal);
  void fill_sides(const dVector &);
  void fill_sides(const dVector &, const dVector &);
  void fill_sides(const dVector &, const dVector &,
                  const dVector &) {DGM_UNDEFINED;}
  void load_side(const dVector &, const Ordinal, dVector &) const;
  virtual void lift(const Element *const, dVector &, const char='n') const;
  Scalar compute_side_integral(dVector &, Ordinal) const;
  Scalar compute_side_measure() const;
  //@}

  virtual Topology::ElementType element_type() const 
    {return Topology::NodalLine;}

  /// \name Norm and inner product methods
  //@{
  Scalar norm_Linf() const;
  Scalar norm_L2() const;
  Scalar norm_H1() const;
  void norm_L2(Scalar *, Scalar *) const;
  void norm_H1(Scalar *, Scalar *) const;
  Scalar integrate( Scalar *length=NULL ) const;
  Scalar integrate( const dVector &, Scalar *length=NULL ) const;
  Scalar compute_measure() const;
  Scalar L2_inner_product(const Element *Y, Scalar *length=NULL) const;
  Scalar L2_inner_product(const dVector &x, const dVector &y,
                          Scalar *length=NULL) const;
  void apply_metric();
  void remove_metric();
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
  inline void write_mesh(ostream &, const unsigned prec) const;
  Element* clone() const {return new NodalLine(this);}
  /// update the workspace storage given new information
  virtual void update_workspace(const Ordinal max) const {
    make_workspace(max,max);
  }
  //@}

protected:

  // Default constructor is not allowed
  NodalLine();

};

//============================================================================
//                      I m p l e m e n t a t i o n
//============================================================================

/// Output a Line Element in DGM mesh file format
inline void NodalLine::write_mesh(ostream &f, const unsigned prec) const {
  f << "ELEMENT " << gid() << "  NODALLINE\n";
  f << scientific;
  f.precision(prec);
  for (Ordinal i=0; i<nVerts(); i++)
    f << setw(7+prec) << vert[i]->x << " ";
  f << '\n';
}

/// Allocate memory for the NodalLine workspace
inline void NodalLine::make_workspace(const Ordinal qtot,
                                      const Ordinal nModes) {
  if (qtot > Qmax) {
    Qmax = qtot;
    g1_wk.resize(Qmax);
    g2_wk.resize(Qmax);
    g3_wk.resize(Qmax);
    g4_wk.resize(Qmax);
    g5_wk.resize(Qmax);
  }
  if (qtot*nModes > Lmax) {
    Lmax = nModes*qtot;
    Lwk.resize(Lmax);
  }
}

} // namespace DGM

#endif  // DGM_NODAL_LINE_HPP
