#ifndef DGM_SLAB_HPP
#define DGM_SLAB_HPP

/** \file Slab.hpp
    \brief DGM slab element class declaration
    \author Scott Collis
*/
 
// system includes
#include <string>
#include <map>
#include <algorithm>

// DGM includes
#include "Element.hpp"
#include "FFT.hpp"

namespace DGM {

/// Slab Element class
class Slab : public Element {

  static BasisDB bdb;      ///< Basis database

  static Ordinal Qmax;     ///< Maximum number of total quadrature points
  static Ordinal Lmax;     ///< Maximum number of total modes

  static dVector g1_wk;    ///< Workspace for gradients
  static dVector Lwk;      ///< Workspace for modal coefficients

  Ordinal Nx;              ///< Number of Fourier modes in x
  Ordinal Nz;              ///< Number of Fourier modes in z
  Scalar Lx;               ///< Length of slab
  Scalar Lz;               ///< Width of slab

  vector<Scalar> Kx;       ///< wavenumbers for Fourier modes in x
  vector<Scalar> Kz;       ///< wavenumbers for Fourier modes in z

  FFT::Ptr fft;            ///< Interface to DGM::FFT

 public:
  
  /// Constructor
  Slab(const Size, const Ordinal, const Ordinal,
       const vector<Point>&, const Ordinal, const Ordinal,
       const Scalar, const Scalar);

  /// Copy constructor
  Slab(const Slab*);

  /// Destructor
  virtual ~Slab();

  // static member functions
  static void make_workspace(const Ordinal, const Ordinal);
  static void make_basis(Basis *, const Basis::Type, const int der);

  // Override Element virtual methods

  virtual void push_to_subsides() const {DGM_UNDEFINED;}

  /// \name Initialization
  //@{
  void get_mass_matrix();
  void get_mass_matrix( const dVector & ) {DGM_UNDEFINED;}
  void get_derivative_matrix();
  void fill(string, Operation operation=Equal);
  void fill(Mode &) {DGM_UNDEFINED;} 
  void fill(Mode &, dVector &) const {DGM_UNDEFINED;}
  void random() {DGM_UNDEFINED;}
  void set(const dVector &, const Ordinal) {DGM_UNDEFINED;}
  //@}

  /// \name Local assembly matrices and residuals
  //@{
  void get_local_mass_matrix(const dVector &) {DGM_UNDEFINED;}
  void get_local_derivative_matrix() {DGM_UNDEFINED;}
  void get_local_derivative_matrix(const dVector &) {DGM_UNDEFINED;}
  void get_local_laplace_matrix() {DGM_UNDEFINED;}
  void get_local_laplace_matrix(const dVector &) {DGM_UNDEFINED;}
  void test_on_shape() {DGM_UNDEFINED;}
  void test_on_shape(const dVector &, dVector &) const {DGM_UNDEFINED;}
  void test_on_shape_side(const dVector &, const int, dVector &) const {
    DGM_UNDEFINED;
  }
  void test_on_grad_shape(const dVector &, char, dVector &) const {
    DGM_UNDEFINED;
  }
  //@}

  virtual Topology::ElementType element_type() const {return Topology::Slab;}

  /// \name Transforms methods
  //@{
  Basis* get_basis(const int der) const;
  void inner_product();
  void inner_product(dVector &, dVector &) const;
  void forward_transform();
  void forward_transform(dVector &, dVector &) const;
  void forward_transform(Element *) const {DGM_UNDEFINED;}
  void forward_transform(Element *, Element *) {DGM_UNDEFINED;}
  void backward_transform();
  void backward_transform(dVector &, dVector &) const;
  void solve_mass_matrix(dVector &) const;
  //@}

  /// \name Filter methods
  //@{
  void make_constant() {DGM_UNDEFINED;}
  void low_modes(const Ordinal np) {DGM_UNDEFINED;}
  void kill_constant() {DGM_UNDEFINED;}
  void coarse_scales(const int p_inc) {DGM_UNDEFINED;}
  void coarse_scales(const int p_inc, dVector &) {DGM_UNDEFINED;}
  void fine_scales(const int) {DGM_UNDEFINED;}
  void fine_scales(const int, dVector &) {DGM_UNDEFINED;}
  void fine_scales_transform(const int, dVector &) const {DGM_UNDEFINED;}
  //@}

  /// \name Derivative methods
  //@{
  void gradient(const dVector &, dVector &) const {DGM_UNDEFINED;}
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
  void compute_side_geometry();
  void add_Dirac_delta(const Ordinal qpt, const Scalar amp) {DGM_UNDEFINED;}
  void add_Dirac_delta(const Point &p, const Scalar amp) {DGM_UNDEFINED;}
  void add_local_Dirac_delta(const Point &p, const Scalar amp) {DGM_UNDEFINED;}
  Scalar interpolate_local_point(const Point &p) const {
    DGM_UNDEFINED; 
    return 0;
  }
  Scalar interpolate_point(const Point &p) const {DGM_UNDEFINED; return 0;}
  void interpolate_points(const vector<Point>& ps, dVector &vals) const 
    {DGM_UNDEFINED;}
  int get_local_coordinates(const Point &p, Scalar &r) const
    {DGM_UNDEFINED; return 0;}
  Point get_local_coordinates(const Point &p) const 
    {DGM_UNDEFINED; return Point();}
  //@}

  /// \name Side methods
  //@{
  void get_side(const dVector &, const Ordinal, dVector &) const {
    DGM_UNDEFINED;
  }
  void fill_sides(const Scalar, const Operation=Equal) {DGM_UNDEFINED;}
  void fill_sides(const dVector &);
  void fill_sides(const dVector &, const dVector &);
  void fill_sides(const dVector &, const dVector &, 
                  const dVector &) {DGM_UNDEFINED;}
  void load_side(const dVector &, const Ordinal, dVector &) const {
    DGM_UNDEFINED;
  }
  virtual void lift(const Element *const, dVector &, const char='n') const;
  Scalar compute_side_integral(dVector &, Ordinal) const {
    DGM_UNDEFINED; return 0;}
  Scalar compute_side_measure() const {DGM_UNDEFINED; return 0;}
  /// Generate the side mapping accounting for flips
  virtual Ordinal sideMap(const Side *s, const Ordinal ql ) const {
    return ql;
  }
  //@}

  /// \name Norm and inner product methods
  //@{
  Scalar norm_Linf() const  {DGM_UNDEFINED; return 0;}
  Scalar norm_L2() const {DGM_UNDEFINED; return 0;}
  Scalar norm_H1() const {DGM_UNDEFINED; return 0;}
  void norm_L2(Scalar *, Scalar *) const {DGM_UNDEFINED;}
  void norm_H1(Scalar *, Scalar *) const {DGM_UNDEFINED;}
  Scalar integrate( Scalar *length=NULL ) const {DGM_UNDEFINED; return 0;}
  Scalar integrate( const dVector &, Scalar *length=NULL ) const 
  {DGM_UNDEFINED; return 0;}
  Scalar compute_measure() const {DGM_UNDEFINED; return 0;}
  Scalar L2_inner_product(const Element *Y, Scalar *length=NULL) const 
  {DGM_UNDEFINED; return 0;}
  Scalar L2_inner_product(const dVector &x, const dVector &y, 
                          Scalar *length=NULL) const {DGM_UNDEFINED; return 0;}
  void apply_metric() {DGM_UNDEFINED;}
  void remove_metric() {DGM_UNDEFINED;}
  //@} 

  /// \name Spatial regularization for optimal control
  //@{
  void get_side_Ds(const int, const dVector&, dVector&) const {DGM_UNDEFINED;}
  void get_side_curvature(const int, dVector &) const {DGM_UNDEFINED;}
  void get_D1( const int sid, dMatrix &) const { DGM_UNDEFINED;}
  //@}

  /// \name Utilities
  //@{
  void tecplot(FILE *);
  void output(FILE *, const char='d') const {DGM_UNDEFINED;}
#if 0
  inline void write_mesh(FILE *, const string format) const;
#else
  inline void write_mesh(ostream &, const unsigned prec) const;
#endif
  Element* clone() const {return new Slab(this);}
  /// update the workspace storage given new information
  virtual void update_workspace(const Ordinal max) const {
    make_workspace(max,max);
  }
 //@}

  // make sure that base project is also available (since we have a local
  // project method with a different signature)
  using Element::project;

 protected:

  /// Default constructor -- not allowed
  Slab();

  /// Local projection method (in addition to Element base project methods)
  void project(PF pf);

};

//============================================================================
//                      I m p l e m e n t a t i o n
//============================================================================

#if 0
/// Output a Slab element in DGM mesh file format
inline void Slab::write_mesh(FILE *fp, const string format) const {
  fprintf(fp,"ELEMENT %d  SLAB\n",gid());
  for (int i=0; i<nVerts(); i++) fprintf(fp,format.c_str(),vert[i]->x);
  fprintf(fp,"\n");
}
#else
/// Output a Slab element in DGM mesh file format
inline void Slab::write_mesh(ostream &f, const unsigned prec) const {
  f << "ELEMENT " << gid() << "  SLAB\n";
  f << scientific; 
  f.precision(prec);
  for (Ordinal i=0; i<nVerts(); i++)
    f << setw(7+prec) << vert[i]->x << " ";
  f << '\n';
}
#endif

/// Allocate memory for the Slab workspace
inline void Slab::make_workspace(const Ordinal qtot, const Ordinal nModes) {
  if (qtot > Qmax) {
    Qmax = qtot;
    g1_wk.resize(Qmax);
  }
  if (qtot*nModes > Lmax) {
    Lmax = nModes*qtot;
    Lwk.resize(Lmax);
  }
}

} // namespace DGM

#endif  // DGM_SLAB_HPP
