#ifndef DGM_LINE_HPP
#define DGM_LINE_HPP

/** \file  Line.hpp
    \brief Line element declaration
    \author Scott Collis
*/

// system includes
#include <string>
#include <map>
#include <algorithm>

// boost includes
#ifdef DGM_USE_GENERAL_GHOSTING
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/split_member.hpp>
#endif

// DGM includes
#include "Element.hpp"
#include "BaseLine.hpp"

namespace DGM {

//============================================================================
//                        D e c l a r a t i o n
//============================================================================

/// One-dimensional Line Element class
class Line : public BaseLine {

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
  Line(const Ordinal, const Ordinal, const Ordinal, const vector<Point>&);

  /// Copy constructor
  Line(const Line*);

  /// Destructor
  virtual ~Line();

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
  void normal_times_gradient_side(const dVector &, const int, dVector &) const;
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
  void fill_basis_shift_matrix(dMatrix &G) const;
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
  void get_side_coordinates(const Ordinal, Point *) const;
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
  virtual void lift(const Element *const F, dVector &R,
                    const char dir='n') const;
  virtual void lift(dVector &R) const;
  Scalar compute_side_integral(dVector &, Ordinal) const;
  Scalar compute_side_measure() const;
  //@}

  virtual Topology::ElementType element_type() const {return Topology::Line;}

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
  void fdotgrad(const dVector &, const dVector &, dVector &) const;
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
  Element* clone() const {return new Line(this);}
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
    ar & boost::serialization::base_object<BaseLine>(*this);
  }
  /*! load this class from archive
   *
   * @tparam Archive boost input or output archive class
   * @param ar       archive
   * @param version  (not needed here, see boost documentation)
   */
  template<class Archive>
  void load(Archive & ar, const unsigned int version) {
    ar & boost::serialization::base_object<BaseLine>(*this);
    side.resize(nEdges());
    for (Ordinal i=0; i<nEdges(); i++) {
      side[i] = &(edge[i]);
      side[i]->elink = this;
      side[i]->geid(gid()); // should be true by serialization?
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
  Line() {};
#else
protected:

  /// Default constructor -- not allowed
  Line();
#endif
};

//============================================================================
//                      I m p l e m e n t a t i o n
//============================================================================

/// Output a Line Element in DGM mesh file format
inline void Line::write_mesh(ostream &f, const unsigned prec) const {
  f << "ELEMENT " << gid() << "  LINE\n";
  f << scientific;
  f.precision(prec);
  for (Ordinal i=0; i<nVerts(); i++)
    f << setw(7+prec) << vert[i]->x << " ";
  f << '\n';
}

/// Allocate memory for the Line workspace
inline void Line::make_workspace(const Ordinal qtot, const Ordinal nModes) {
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

#endif  // DGM_LINE_HPP
