#ifndef DGM_ELEMENT_BLOCK_HPP
#define DGM_ELEMENT_BLOCK_HPP

/** \file ElementBlock.hpp
    \brief DGM Element block class declaration
    \author James Overfelt
    \author Scott Collis
*/

// system includes
#include <cstdio>
#include <fstream>
#include <string>
#include <vector>

// DGM includes
#include "Comm.hpp"
#include "Element.hpp"
#include "Types.hpp"
#include "Parser.hpp"

namespace DGM {

/// Element block abstract base class.
/** Note this is not a PURE abstract class */
class ElementBlock {

public:

  /// Type for element block data
  typedef std::vector<Element*> eblock;

  /// Pointer type to derivative information
  typedef Element::DinfoPtr DinfoPtr;

  /// Pointer type for curved side information
  typedef Element::CurvePtr CurvePtr;

  /// List of Elements that are in this block.
  /** It is important that these element are homogeneous, all elements with
   *  the same number of nodes and integration points.  It is also necessary
   *  that the memory associated with these elements in continuous.  This will
   *  allow operations to be performed over all of these elements with a single
   *  BLAS or LAPACK call without having to move the data into a continuous
   *  buffer. */
  eblock eb;

  /// BlockSize for this element block
  const Ordinal BlockSize;

  /// Vector that points to eb[0]->u and has length qtot*eb.size().
  /** This vector contains all of the element data for this element block. */
  dVector u;

  /// The values that define this homogeneous element block are listed below.
  /** These are checked before an element can be added to this block. */
  const Ordinal nVerts;       ///< Number of verticies
  const Ordinal nEdges;       ///< Number of edges (2- and 3-d)
  const Ordinal nFaces;       ///< Number of faces (3-d)
  const Ordinal nModes;       ///< Number of total modes
  const Ordinal pOrder;       ///< Polynomial order
  const Ordinal L     ;       ///< Number of modes in each direction
  const Ordinal qtot  ;       ///< Total number of quadrature points
        Ordinal s_qtot;       ///< Total number of side quadrature points
        bool const_mass;      ///< Set if constant mass matrix
  const Basis * psi   ;       ///< basis data-structure
  const Ordinal qa    ;       ///< Number of quadrature points
  const Ordinal qb    ;       ///< Number of quadrature points
  const Ordinal qc    ;       ///< Number of quadrature points
  const DinfoPtr D     ;      ///< collocation derivative matrix
  const CurvePtr curve ;      ///< curved side structure
  const Geometry::Ptr  geom;  ///< Jacobian matrix
  const Geometry geom_check;  ///< Jacobian matrix
  const Dinfo    dinfo_check; ///< Jacobian matrix

  /// interpolation matrices
  const std::vector<dMatrix*> interpolation_matrices;

  Element *first_element() const;

  /// Check to see if the element can be added to this element block.
  bool compatible(const Element *e) const;

  /// Check that all elements in the block are compatible
  bool checkCompatibility() const;

#if defined(DGM_USE_CUDA) || defined(DGM_USE_KOKKOS)
  /// Allocate Gpu memory and other initialization
  virtual void initialize_gpu() {}
#endif // DGM_USE_CUDA or DGM_USE_KOKKOS

  /// Add element to this element block.
  /** This should be used instead of just pushing ontot the eb vector.
      The return value is true if the push was successful:
      (1) The element is compatable with this element block.
      (2) There is enough room to add it to this element block. */
  bool push_back(Element *e);

  /// Special function that sets the mass for an entire block of elements.
  //  This is done if there is no variable earth model and therefore the
  //  mass matrix is constant.  In this case the solve_mass_matrix() call
  //  can be blocked for more efficiency.
  void set_constant_mass(const bool c) {const_mass=c;}
  void set_constant_mass() {const_mass=true;}
  void reset_constant_mass() {const_mass=false;}

  // only derived classes can construct an element block, therefore no public
  // constructor is provided

  // regular member functions.
  // All of these functions are virtual in the Element base class.  It is the
  // intention that an ElementBlock object can be used in place of an Element
  // object anywhere.  Therefore all of the Element routines are duplicated
  // in the ElementBlock class.  This is not so difficult since most Element

  // side methods
  virtual void get_side(const dVector &, const int, dVector &) const;
  // virtual void fill_sides(const dVector &);
  // virtual void fill_sides(const dVector &, const dVector &);
  // virtual void fill_sides(const dVector &, const dVector &,const dVector &);
  // virtual void fill_sides_uniform(const dVector &);
  virtual void copy_sides( ElementBlock *E ) const;
  // virtual void load_side(const dVector &, const int, dVector &) const;
  virtual void lift(ElementBlock *, dVector &, const char dir='n') const;
  // virtual Scalar compute_side_integral(dVector &, Ordinal) const;
  // virtual Scalar compute_side_measure() const;

  // initilization
  // virtual void get_mass_matrix();
  // virtual void get_mass_matrix( const dVector & );
  // virtual void get_1d_mass_matrix(Minfo &) const;
  // virtual void get_derivative_matrix();
  // void zero();
  // void fill(const Scalar);    // fill is in physical space
  // void fill(PF pf);           // fill from a pointer to function
  // virtual void fill(string);  // fill from an expression
  // virtual void fill(Mode &);
  // virtual void fill(Mode &, dVector &);
  // void fill(const dVector &);
  // void extract(dVector &) const;
  // virtual void set(const dVector &, const int); // set is in transform space

  // derivative local assembly matrices and residuals
  // virtual void get_local_mass_matrix(const dVector &);
  // virtual void get_local_derivative_matrix();
  // virtual void get_local_derivative_matrix(const dVector &);
  // virtual void get_local_laplace_matrix();
  // virtual void get_local_laplace_matrix(const dVector &);
  // virtual void test_on_shape();
  // virtual void test_on_shape(dVector &, dVector &) const;
  // virtual void test_on_grad_shape(const dVector &, char, dVector &) const;

  // transforms methods
  // virtual Basis* get_basis(const int der) const;
  virtual void inner_product();
  virtual void inner_product(dVector &, dVector &) const;

  // virtual void forward_transform();
  // virtual void forward_transform(dVector &, dVector &);
  // virtual void forward_transform(Element *) const;
  virtual void forward_transform(ElementBlock *, ElementBlock *);

  virtual void backward_transform();
  // virtual void backward_transform(dVector &, dVector &);

  // project inplace
  virtual void project() {
    forward_transform(this, this);
    backward_transform();
  }

  virtual void solve_mass_matrix(dVector &) const ;
  //   virtual void interpolate_to_uniform();

  // filter methods
  //   virtual void make_constant();
  //   virtual void low_modes(const Ordinal np);
  //   virtual void kill_constant();
  //   virtual void filter(const dVector &);
  //   virtual void exp_filter(const Scalar Nc, const Scalar s);
  //   virtual void coarse_scales(const int p_inc);
  //   virtual void coarse_scales(const int p_inc, dVector &);
  //   virtual void fine_scales(const int p_inc);
  //   virtual void fine_scales(const int p_inc, dVector &);
  //   virtual void fine_scales_transform(const int p_inc, dVector &) const;
  //   virtual void bound(const Scalar low, const Scalar high);

  //   // VMS methods
  //   virtual void vms_isolate_small();
  //   virtual void vms_isolate_small(dVector &, dVector &);
  //   virtual void vms_isolate_small(dVector &);

  //   // curved side methods
  //   virtual void J_backward_transform(dVector &, dVector &);
  //   virtual void solve_1d_mass_matrix(dVector &) const;

  // derivative methods
  //   virtual void gradient(const dVector &, dVector &) const;
  virtual void gradient(const dVector &, dVector &, dVector &) const;
  virtual void gradient(const dVector &, dVector &, dVector &, dVector &) const;
  virtual void gradient(const dVector &, dVector &, char) const;
  //   virtual void local_gradient(const dVector &, dVector &, dVector &) const;
  //   virtual void local_gradient(const dVector &, dVector &,
  //                               dVector &, dVector &) const;

  //   // geometry methods
  //   virtual void get_coordinates();
  //   virtual void get_straight_coordinates();
  //   virtual void get_curved_coordinates();
  //   virtual void get_side_coordinates(const int, Point *);
  //   virtual void compute_geometry();
  //   virtual void compute_straight_geometry();
  //   virtual void compute_curved_geometry();
  //   virtual void compute_side_geometry();
  //   virtual void forward_transform_side(dVector &, dVector &);
  //   virtual void generate_curve();

  //   virtual void add_Dirac_delta(const int qpt, const Scalar amp);
  //   virtual void add_Dirac_delta(const Point &p, const Scalar amp);

  //   virtual Scalar interpolate_point(const Point &p);
  //   virtual int get_local_coordinates(const Point &p,
  //                                     Scalar *r);
  //   virtual int get_local_coordinates(const Point &p,
  //                                     Scalar *r, Scalar *s);
  //   virtual int get_local_coordinates(const Point &p,
  //                                     Scalar *r, Scalar *s, Scalar *t);

  //   // utilities
  //   virtual void tecplot(FILE *);
  //   virtual void output(FILE *, const char='d') const;
  //   virtual void write_mesh(FILE *) const;
  //   virtual int get_weight() const;
  //   virtual Element* clone() const;

  //   // norms and errors
  //   virtual Scalar norm_Linf() const;
  //   virtual Scalar norm_L2() const;
  //   //virtual Scalar norm_L2(const dVector&) const;
  //   virtual Scalar norm_H1() const;
  //   virtual void norm_L2(Scalar *, Scalar *) const;
  //   //virtual void norm_L2(const dVector&, Scalar *, Scalar *) const;
  //   virtual void norm_H1(Scalar *, Scalar *) const;
  //   virtual Scalar integrate( Scalar * =NULL ) const {
  //     DGM_UNDEFINED; return 0;}
  //   virtual Scalar integrate(const dVector &, Scalar * =NULL) const {
  //     DGM_UNDEFINED; return 0;}
  //   virtual void plane_average() {DGM_UNDEFINED;}

  //   // for spatial regularization g_s
  //   virtual void get_side_Ds(const int, const dVector&, dVector&) const {
  //     DGM_UNDEFINED;}
  //   virtual void get_side_curvature(const int, dVector &) const {
  //     DGM_UNDEFINED;}

  //   virtual void get_D1( const int sid, dMatrix &) const { DGM_UNDEFINED;}

  //   // 3d curved element methods
  //   virtual void forward_transform_side(const Ordinal, dVector &, dVector &,
  //                                       dVector *);
  //   virtual void get_straight_side_coordinates(const Ordinal, dVector &,
  //                                              dVector &, dVector &);
  //   virtual void get_edge(Ordinal q1, Ordinal q2, Scalar *,
  //                         Ordinal edgid, Scalar *);

  //   // accessors

  //   /// return the polynomial order
  //   int get_p() const {return pOrder; }

  //   // helpers
  //   virtual Scalar compute_measure() const;
  //   virtual Scalar L2_inner_product(const Element *Y,
  //                                   Scalar *measure=NULL) const;
  //   virtual std::vector<Scalar>
  //     L2_inner_product(const dVector &x, const dVector &y,
  //                      std::vector<Scalar> *measure=NULL) const;
  void write_connectivity(FILE *) const;
  void read(ifstream &);
  void write(FILE *) const;
  friend std::ostream& operator<<(std::ostream&, const Element&);

  static std::vector<Scalar> L2_inner_product(const ElementBlock *e1,
                                              const ElementBlock *e2,
                                              std::vector<Scalar> *measure=0);
  /// destructor
  virtual ~ElementBlock() {};

protected:

  /// Default constructor
  ElementBlock(Element *e, const Ordinal blocksize) ;

private:

  /// do not allow copy construction
  ElementBlock(const ElementBlock &EB);

  /// do not allow copy construction
  ElementBlock(const ElementBlock *EB);

};


/// read element data to file stream
inline void ElementBlock::read(ifstream &fs) {
  const eblock::const_iterator end = eb.end();
  for (eblock::iterator i=eb.begin(); i!=end; ++i) {
    (*i)->read(fs);
  }
}

/// write element data to file stream
inline void ElementBlock::write(FILE *fp) const {
  const eblock::const_iterator end = eb.end();
  for (eblock::const_iterator i=eb.begin(); i!=end; ++i) {
    (*i)->write(fp);
  }
}

/// Element output to a stream in human readable format
inline std::ostream & operator<<(std::ostream &os, const ElementBlock &E) {
  const ElementBlock::eblock::const_iterator end = E.eb.end();
  for (ElementBlock::eblock::const_iterator i=E.eb.begin(); i!=end; ++i) {
    os<<*i;
  }
  return os;
}

/// write the element side connectivity
inline void ElementBlock::write_connectivity(FILE *fp) const {
  const eblock::const_iterator end = eb.end();
  for (eblock::const_iterator i=eb.begin(); i!=end; ++i) {
    (*i)->write_connectivity(fp);
  }
}

/// $L_2$ inner product of the data on two conforming element blocks
inline std::vector<Scalar>
ElementBlock::L2_inner_product(const ElementBlock *e1,
                               const ElementBlock *e2,
                               std::vector<Scalar> *measure) {
  std::vector<Scalar> result;
  if (measure) measure->clear();
  const eblock::const_iterator end1 = e1->eb.end();
  const eblock::const_iterator end2 = e2->eb.end();
  eblock::const_iterator i1 = e1->eb.begin();
  eblock::const_iterator i2 = e2->eb.begin();
  for (; i1!=end1 && i2!=end2; ++i1, ++i2) {
    Scalar m;
    result.push_back(Element::L2_inner_product(*i1, *i2, &m));
    if (measure) measure->push_back(m);
  }
  return result;
}

} // namespace DGM

#endif  // DGM_ELEMENT_BLOCK_HPP
