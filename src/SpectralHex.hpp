#ifndef DGM_SPECTRALHEX_HPP
#define DGM_SPECTRALHEX_HPP

/** \file  SpectralHex.hpp
    \brief Spectral Hexahedral element declaration
    \author Scott Collis and Thomas Smith
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
#include "BaseHex.hpp"

namespace DGM {

//============================================================================
//                        D e c l a r a t i o n
//============================================================================

/// Spectral Hexahedral Element class
class SpectralHex : public BaseHex {

  typedef GeometryDBSetApprox GeometryDB;  ///< Set the type of GeometryDB to be used

  static BasisDB bdb;      ///< Basis database
  static GeometryDB  gdb;      ///< Geom database
  static IMDB imdb;        ///< Interpolation database
  static DerivDB ddb;      ///< Derivative matrix database

  static Ordinal Qmax;     ///< Maximum number of total quadrature points
  static Ordinal Lmax;     ///< Maximum number of total modes

  static dVector g1_wk;    ///< Workspace for gradients
  static dVector g2_wk;    ///< Workspace for gradients
  static dVector g3_wk;    ///< Workspace for gradients

  static dVector n1_wk;    ///< Workspace for norms
  static dVector n2_wk;    ///< Workspace for norms
  static dVector n3_wk;    ///< Workspace for norms

  static dVector Lwk;      ///< Workspace for modal coefficients
  static dVector Lwk2;     ///< Workspace for modal coefficients

  static bool first_warn;  ///< Ensures that only one warning is generated

  static const int v_num[6][4];  ///< vertex numbering
  static const int e_num[6][4];  ///< edge numbering

public:
  static void ClearDBs() {
    gdb.clear(); bdb.bases.clear(); imdb.entry.clear();
  }

  /// Constructor
  SpectralHex(const Ordinal, const Ordinal, const vector<Point>&);

  /// Copy constructor
  SpectralHex(const SpectralHex*);

  /// Destructor
  virtual ~SpectralHex();

  // static member functions
  inline static void make_workspace(const Ordinal, const Ordinal);
  static void make_interpolation_matrix(const Ordinal, const Ordinal,
                                        const Interp::Type, dMatrix &);
  static dMatrix* get_interpolation_matrix(const Ordinal, const Ordinal,
                                           const Interp::Type);

  // Override Element virtual methods

  /// \name Initialization
  //@{
  void get_mass_matrix();
  void get_mass_matrix( const dVector & );
  void get_1d_mass_matrix(Minfo &) const;
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
  std::vector<dMatrix*> get_interpolation_matrices() const;
  //@}

  /// \name Transforms methods
  //@{
  Basis* get_basis(const int der) const;
  void inner_product();
  void inner_product(dVector &, dVector &) const;
  Scalar inner_product(dVector &f, const Ordinal m) const;
  void forward_transform();
  void forward_transform(dVector &, dVector &) const;
  void forward_transform(Element *, Element *);
  void backward_transform();
  void backward_transform(dVector &, dVector &) const;
  void solve_mass_matrix(dVector &) const;
  void solve_mass_matrix(dMatrix &);

  void L_forward_transform();
  void L_backward_transform();
  //@}

  /// \name Filter methods
  //@{
  void make_constant();
  void low_modes(const Ordinal np);
  void nodal_to_modal(dVector &f, dVector &fh);
  void modal_to_nodal( dVector &fh, dVector &f);
  void filter(const dVector &);
  void fine_scales(const int);
  void fine_scales(const int, dVector &);
  void fine_scales_transform(const int, dVector &) const;
  void fill_basis_shift_matrix(DGM::dMatrix &G) const;
  void plane_average();
  void vms_isolate_small();
  void vms_isolate_small(dVector &, dVector &);
  void vms_isolate_small(dVector &);
  //@}

  /// \name Derivative methods
  //@{
  /// 1d gradient undefined for SpectralHex
  void gradient(const dVector &, dVector &) const {DGM_UNDEFINED;}
  /// 2d gradient undefined for SpectralHex
  void gradient(const dVector &, dVector &, dVector & ) const {DGM_UNDEFINED;}
  void gradient(const dVector &, dVector &, dVector &, dVector &) const;
  void gradient(const dVector &, dVector &, char) const;
  /// 2d local gradient undefined for SpectralHex
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
  bool is_affine() const;
  void compute_straight_geometry();
  void compute_curved_geometry();
  StabMetrics compute_metrics();
  void compute_side_geometry();
  void forward_transform_side(dVector &, dVector &);

  void add_Dirac_delta(const Ordinal qpt, const Scalar amp);
  void add_Dirac_delta(const Point &p, const Scalar amp);
  void add_local_Dirac_delta(const Point &p, const Scalar amp);
  void add_local_Dirac_delta(const vector<dMatrix> &M, const Scalar amp);


  Scalar interpolate_local_point(const Point &p) const;
  virtual void calculate_interpolation_matrices(vector<dMatrix>&,
                                                 const vector<Point>&) const;
  virtual void apply_interpolation_matrices(dVector &vals,
                                            const vector<dMatrix>&) const;
  Scalar interpolate_point(const Point &p) const;
  void interpolate_points(const vector<Point> &ps, dVector &vals) const;
  //@}

  /// \name Side methods
  //@{
  void get_side(const dVector &, const Ordinal, dVector &) const;
  void fill_sides(const dVector &);
  /// Undefined
  void fill_sides(const dVector &, const dVector &) {DGM_UNDEFINED;}
  void fill_sides(const dVector &, const dVector &, const dVector &);
  void load_side(const dVector &, const Ordinal, dVector &) const;
  virtual void lift(const Element *const, dVector &, const char='n') const;
  Scalar compute_side_integral(dVector &, Ordinal) const;
  Scalar compute_side_measure() const;
  virtual Ordinal sideVertMap(const Ordinal lsid, const Ordinal lvid) const {
    return v_num[lsid][lvid];
  }
  virtual void side2size(const Ordinal side, iVector &q) const;
  virtual Ordinal side2size(const Ordinal side) const;
  //@}

  virtual Topology::ElementType element_type() const 
    {return Topology::SpectralHex;}

  /// \name Curved side methods
  //@{
  void J_backward_transform(dVector &, dVector &);
  void solve_1d_mass_matrix(dVector &) const;
  void forward_transform_side(const Ordinal, dVector &,
                              dVector &, dVector *);
  void get_straight_side_coordinates(const Ordinal, dVector &,
                                     dVector &, dVector &) const;
  void get_edge(Ordinal q1, Ordinal q2, Scalar *, Ordinal edgid, Scalar *);
  void generate_curve();
  //@}

  /// \name Norm and inner product methods
  //@{
  Scalar norm_Linf() const;
  Scalar norm_L2() const;
  Scalar norm_H1() const;
  void norm_L2(Scalar *, Scalar *) const;
  void norm_H1(Scalar *, Scalar *) const;
  Scalar integrate( Scalar *vol=NULL ) const;
  Scalar integrate( const dVector &, Scalar *vol=NULL ) const;
  Scalar compute_measure() const;
  Scalar L2_inner_product(const Element*, Scalar *vol=NULL) const;
  Scalar L2_inner_product(const dVector&, const dVector&,
                          Scalar *vol=NULL) const;
  //@}

  /// \name Spatial regularization g_s
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
  /// Clone the current element
  Element* clone() const { return new SpectralHex(this); }
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
    ar & boost::serialization::base_object<BaseHex>(*this);
  }
  /*! load this class from archive
   *
   * @tparam Archive boost input or output archive class
   * @param ar       archive
   * @param version  (not needed here, see boost documentation)
   */
  template<class Archive>
  void load(Archive & ar, const unsigned int version) {
    ar & boost::serialization::base_object<BaseHex>(*this);
    side.resize(nSides());
    for (Ordinal i=0; i<nSides(); i++) {
      side[i] = &(face[i]);
      side[i]->elink = this;
      side[i]->geid(gid());   // should be true by serialization?
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
  SpectralHex() {};
#else
protected:

  /// Default constructor -- not allowed
  SpectralHex();
#endif

private:

  /// \name Local SpectralHex methods
  //@{
  Ordinal vertex_num(const Ordinal, const Ordinal) const;
  Ordinal edge_num(const Ordinal, const Ordinal) const;
  void forward_transform_edge(dVector & , dVector &  );
  void solve_2d_mass_matrix(dVector &) const;
  void get_2d_mass_matrix(Minfo &) const;
  void side_to_size(Ordinal &, Ordinal &, const Ordinal) const;
  void local_lift(dVector&,const Element *const,
                  const Ordinal, const Scalar *, const char) const;
  void interpolate_to_side( const Ordinal, const dVector &, dVector &) const;
  void interpolate_from_side( const Ordinal, const dVector &, dVector &) const;
  //@}

};

//============================================================================
//                      I m p l e m e n t a t i o n
//============================================================================

/// output a SpectralHex Element in DGM mesh file format
inline void SpectralHex::write_mesh(ostream &f, const unsigned prec) const {
  f << "ELEMENT " << gid() << "  SPECTRALHEX\n";
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

/// allocate memory for the SpectralHex workspace
inline void SpectralHex::make_workspace(const Ordinal qtot,
                                        const Ordinal nModes) {
  if (qtot > Qmax) {
    Qmax = qtot;
    g1_wk.resize(Qmax); g1_wk = 0;
    g2_wk.resize(Qmax); g2_wk = 0;
    g3_wk.resize(Qmax); g3_wk = 0;
    n1_wk.resize(Qmax); n1_wk = 0;
    n2_wk.resize(Qmax); n2_wk = 0;
    n3_wk.resize(Qmax); n3_wk = 0;
   }
  if (qtot > Lmax) {
    Lmax = qtot;
    Lwk.resize(Lmax); Lwk = 0;
    Lwk2.resize(Lmax); Lwk2 = 0;
  }
}

} // namespace DGM

#endif  // DGM_SPECTRALHEX_HPP
