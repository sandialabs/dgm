#ifndef DGM_ELEMENT_HPP
#define DGM_ELEMENT_HPP

/** \file Element.hpp
    \brief Abstract Element base class declaration
    \author S. Scott Collis
*/

// system includes
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <limits>
#include <stdint.h>

// boost includes
#ifdef DGM_USE_GENERAL_GHOSTING
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/shared_ptr.hpp>
#endif
using namespace std;

// DGM includes
#include "Comm.hpp"
#include "Types.hpp"
#include "Coordinates.hpp"
#include "Vertex.hpp"
#include "Side.hpp"
#include "Edge.hpp"
#include "Face.hpp"
#include "Basis.hpp"
#include "Curve.hpp"
#include "Parser.hpp"
#include "String.hpp"
#include "Mesh.hpp"
#include "Topology.hpp"
#include "Vector.hpp"

namespace DGM {

//============================================================================
//                        D e c l a r a t i o n
//============================================================================

/// Element abstract base class. Note this is not a PURE abstract class
/** The Element::Info class provides a means of storing information that is
    common to multiple elements so as to reduce the memory footprint
*/
class Element {

protected:

  bool full_mass;      ///< Indicates if a full element mass matrix is present

private:

  /// \name Private Element data
  //@{
  Ordinal _id;         ///< Local (on this rank) element identification number
  Size _gid;           ///< Unique global element identification number
  //@}

public:

  /// Stability metrics enumeration
  enum stab_metrics {
    DXR,     ///< Metric terms for stability estimates
    DXS,     ///< Metric terms for stability estimates
    DXT,     ///< Metric terms for stability estimates
    DYR,     ///< Metric terms for stability estimates
    DYS,     ///< Metric terms for stability estimates
    DYT,     ///< Metric terms for stability estimates
    DZR,     ///< Metric terms for stability estimates
    DZS,     ///< Metric terms for stability estimates
    DZT,     ///< Metric terms for stability estimates
    IVOL,    ///< Metric terms for stability estimates
    ACOUSTIC ///< Metric terms for stability estimates
  };
  typedef std::map<stab_metrics,CMC::RefVector<Scalar,Ordinal> > StabMetrics;

  /// Visualization output types
  enum OutputType {
    ParaviewBinary,       ///< Paraview binary data
    ParaviewCoordinates,  ///< Paraview coordinate data
    ParaviewConnectivity, ///< Paraview connectivity data
    ParaviewOffsets,      ///< Paraview offset data
    ParaviewTypes         ///< Paraview element types
  };

  /// VTK element types
  /** see http://www.vtk.org/VTK/img/file-formats.pdf. */
  enum VTK_Elements {
    VTK_VERTEX = 1,
    VTK_LINE = 3,
    VTK_TRIANGLE = 5,
    VTK_QUAD = 9,
    VTK_TETRA = 10,
    VTK_HEXAHEDRON = 12
  };

  /// \name Smart pointers to local element data structures
  //@{
  typedef DGM::Shared<Dinfo>::Ptr DinfoPtr;  ///< Derivative matrix info
  typedef DGM::Shared<Minfo>::Ptr MinfoPtr;  ///< Mass matrix info
  typedef DGM::Shared<Coord>::Ptr CoordPtr;  ///< Spatial coordinates
  typedef DGM::Shared<Curve>::Ptr CurvePtr;  ///< Curved side pointer
  typedef DGM::Shared<Side >::Ptr SidePtr;   ///< General side pointer
  //@}

  /// Pointer to function of Point
  typedef Scalar (*PF) (const Point&);

  /// Pointer to function of Edge
  typedef Scalar (*PFE) (const Edge&);

  /// Element state enumeration
  enum States {
    Unallocated,      ///< Element memory is not allocated
    Undefined,        ///< Element state has not been defined
    Physical,         ///< Element is in physical space
    Transform         ///< Element is in transform (Legendre) space
  };

  /// Element fill operations
  enum Operation {
    Equal,         ///< Element set values
    Add,           ///< Element add to values
    Subtract,      ///< Element subtract from values
    Multiply,      ///< Element multiply values
    Divide         ///< Element divide values
  };

  /// Element information storage
  template <typename Scalar, typename Ordinal>
  class Info {
    Ordinal _nVerts;         ///< Number of vertices
    Ordinal _nEdges;         ///< Number of edges (2d and 3d)
    Ordinal _nFaces;         ///< Number of faces (3d)
    Ordinal _nSides;         ///< Number of sides on this elements
    Ordinal _pOrder;         ///< Polynomial order
    Ordinal _L;              ///< Number of modes in each direction
    Ordinal _nModes;         ///< Number of total modes in tensor product
    Ordinal _VMS_Lc;         ///< VMS partition
    Scalar _sigma;           ///< ratio of max side to interior Jacobian
    Scalar _measure;         ///< the length/area/volume of an element
    bool   _skip_element;    ///< skip computations on this element
  public:
    typedef typename DGM::Shared<Info>::Ptr Ptr;
    Info() : _nVerts(0), _nEdges(0), _nFaces(0), _pOrder(0), _L(0),
             _nModes(0), _VMS_Lc(0), _sigma(0), _measure(0),
             _skip_element(false) {}
    Info(const Ordinal nVerts, const Ordinal nEdges, const Ordinal nFaces,
         const Ordinal pOrder) :
    _nVerts(nVerts), _nEdges(nEdges), _nFaces(nFaces), _skip_element(false) {}
    Ordinal nVerts() const { return _nVerts; }
    void nVerts(const Ordinal nVerts) { _nVerts=nVerts; }
    Ordinal nEdges() const { return _nEdges; }
    void nEdges(const Ordinal nEdges) { _nEdges=nEdges; }
    Ordinal nFaces() const { return _nFaces; }
    void nFaces(const Ordinal nFaces) { _nFaces=nFaces; }
    Ordinal nSides() const { return _nSides; }
    void nSides(const Ordinal nSides) { _nSides=nSides; }
    Ordinal pOrder() const { return _pOrder; }
    void pOrder(const Ordinal pOrder) { _pOrder=pOrder; }
    Ordinal L() const { return _L; }
    void L(const Ordinal L) { _L=L; }
    Ordinal nModes() const { return _nModes; }
    void nModes(const Ordinal nModes) { _nModes=nModes; }
    Ordinal VMS_Lc() const { return _VMS_Lc; }
    void VMS_Lc(const Ordinal VMS_Lc) { _VMS_Lc=VMS_Lc; }
    Scalar sigma() const { return _sigma; }
    void sigma(const Scalar sigma) { _sigma=sigma; }
    Scalar measure() const { return _measure; }
    void measure(const Scalar measure) { _measure=measure; }
    bool skip_element() const { return _skip_element; }
    void skip_element(bool skip) { _skip_element=skip; }
#ifdef DGM_USE_GENERAL_GHOSTING
  private:
    friend class boost::serialization::access;
    /// Serialization of Element::Info class
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
      ar & _nVerts & _nEdges & _nFaces & _nSides & _pOrder & _L;
      ar & _nModes & _VMS_Lc;
      ar & _sigma & _measure;
      ar & _skip_element;
    }
#endif
  };

  /// Local element size type
  typedef DGM::Size size_type;

  /// \name Public Element data
  //@{
  Basis::Type type;                 ///< Type of basis on this element

  Info<Scalar,Ordinal>::Ptr info;   ///< Information for this element

  Ordinal nVerts() const { return info->nVerts(); }
  void nVerts(const Ordinal nVerts) { info->nVerts(nVerts); }

  Ordinal nEdges() const { return info->nEdges(); }
  void nEdges(const Ordinal nEdges) { info->nEdges(nEdges); }

  Ordinal nFaces() const { return info->nFaces(); }
  void nFaces(const Ordinal nFaces) { info->nFaces(nFaces); }

  Ordinal nSides() const { return info->nSides(); }
  void nSides(const Ordinal nSides) { info->nSides(nSides); }

  /// Return the number of space dimensions for this element
  Ordinal nsd() const {
    if (nFaces()>1)
      return 3;
    else if (nEdges()>2)
      return 2;
    else if (nVerts())
      return 1;
    else
      throw DGM::exception("Cannot compute number of space dimensions for "
          "element "+asString(gid()));
    return 0;
  }

  Ordinal pOrder() const { return info->pOrder(); }
  void pOrder(const Ordinal pOrder) { info->pOrder(pOrder); }

  Ordinal L() const { return info->L(); }
  void L(const Ordinal L) { info->L(L); }

  Ordinal nModes() const { return info->nModes(); }
  void nModes(const Ordinal nModes) { info->nModes(nModes); }

  Ordinal VMS_Lc() const { return info->VMS_Lc(); }
  void VMS_Lc(const Ordinal VMS_Lc) { info->VMS_Lc(VMS_Lc); }

  Scalar sigma() const { return info->sigma(); }
  void sigma(const Scalar sigma) { info->sigma(sigma); }

  Scalar measure() const { return info->measure(); }
  void measure(const Scalar measure) { info->measure(measure); }

  Point centroid() const {
    Point c(0.0);
    for (Ordinal i=0; i<nVerts(); i++) c += Point(*(vert[i]));
    return c/nVerts();
  }

  void skip_element(bool s) { info->skip_element(s); }
  bool skip_element() const { return info->skip_element(); }

  Ordinal qa;              ///< number of quadrature points in a-direction
  Ordinal qb;              ///< number of quadrature points in b-direction
  Ordinal qc;              ///< number of quadrature points in c-direction
  Ordinal qtot;            ///< total number of quadrature points (in a,b,c)

  vector<Vertex::Ptr> vert;  ///< vector of vertices
  vector<Edge> edge;         ///< vector of edges
  vector<Face> face;         ///< vector of faces
  vector<Side*> side;        ///< vector of sides
  std::pair<Point,Point> box;///< Bounding box(min,max);
#ifdef DGM_USE_GENERAL_GHOSTING
  ///< vector with global ids of neighbor elements same ordering as side vector!
  vector<Size> adj_els;
  /// used in adj_els to indicate that no neighbor is present (usually a BC)
  static const Size invalid_ele_neighbor;
#endif
  Basis *psi;                ///< basis datastructure
  //@}

  /// \name Storage
  //@{
  dVector u;           ///< solution at the quadrature points
  dVector uh;          ///< solution coefficients, aliased to u
  States  state;       ///< state of the solution (physical, transform, etc)
  //@}

  /// \name Matrices
  //@{
  MinfoPtr M;          ///< mass matrix
  MinfoPtr Mbound;     ///< mass matrix at boundary (for nodal flux)
  MinfoPtr Mloc;       ///< local assembly mass matrix
  MinfoPtr Dxloc;      ///< local assembly derivative matrix
  MinfoPtr Dyloc;      ///< local assembly derivative matrix
  MinfoPtr Dzloc;      ///< local assembly derivative matrix

  MinfoPtr Dxtloc;     ///< transpose of the local assembly derivative matrix
  MinfoPtr Dytloc;     ///< transpose of the local assembly derivative matrix
  MinfoPtr Dztloc;     ///< transpose of the local assembly derivative matrix

  MinfoPtr DDloc;      ///< local Laplacian assembly matrix
  DinfoPtr D;          ///< collocation derivative matrix
  MinfoPtr Viloc;      ///< local Vandermonde matrix (NodalTri, NodalTet)
  //@}

  /// \name Element Geometry
  //@{
  CoordPtr C;          ///< quadrature coordinates
  CurvePtr curve;      ///< curved side information
  Geometry::Ptr geom;  ///< geometry information including Jacobian matrix
  //@}

#ifdef DGM_USE_MD_COUPLE
  Model::Type modeltype; ///< physics model type
#endif

  // Only derived classes can construct an element, therefore no public
  // constructor is provided

  /// \name Accessors
  //@{
  /// Get local element id
  inline Ordinal lid() const { return _id; }
  /// Set local element id
  inline void lid( const Ordinal lid ) { _id = lid; }
  /// Get global element id (returns local id if global is not set)
  inline Size gid() const { return ( !gid_defined() ? _id : _gid); }
  /// Set global element id
  inline void gid( const Size gid ) { _gid = gid; }
  /// Undefined id
  template <typename T>
  static T uid() { return numeric_limits<T>::max(); }
  /// Check if global element id is set
  inline bool gid_defined() const { return _gid != uid<Size>(); }
  /// Check if local element id is set
  inline bool id_defined() const { return _id != uid<Ordinal>(); }
  //@}

  /// \name Initialization methods
  //@{
  /// initialize the Element mass matrix
  virtual void get_mass_matrix();
  /// initialize the Element mass matrix with a diagonal matrix
  virtual void get_mass_matrix( const dVector & );
  /// initialize an Edge mass matrix
  virtual void get_1d_mass_matrix(Minfo &) const;
  /// get a derivative matrix
  virtual void get_derivative_matrix();
  /// zero out the Element storage
  virtual void zero();
  /// fill the Element with a constant value in physical space
  virtual void fill(const Scalar, Operation operation=Equal);
  /// fill the Element via a pointer to function
  virtual void fill(PF pf, Operation operation=Equal);
  /// fill the Element with a parsed expression
  virtual void fill(string, Operation operation=Equal);
  /// store non-negative value
  void Abs();
  /// convert from element Operation to VectorFunction Operation
  static Parser::VectorFunction::Operation convert( Operation operation ) {
    switch (operation) {
    case Equal:
      return Parser::VectorFunction::Equal;
      break;
    case Add:
      return Parser::VectorFunction::Add;
      break;
    case Subtract:
      return Parser::VectorFunction::Subtract;
      break;
    case Multiply:
      return Parser::VectorFunction::Multiply;
      break;
    case Divide:
      return Parser::VectorFunction::Divide;
      break;
    default:
      throw DGM::exception("Unsupported Element operation");
    }
    return Parser::VectorFunction::Equal;
  }
  /// fill the Element with a particular Mode of the Basis
  virtual void fill(Mode &);
  /// fill a vector with a mode
  virtual void fill(Mode &, dVector &) const;
  /// fill an Element with a conforming vector of data
  virtual void fill(const dVector &);
  /// fill an Element with a random polynomial
  virtual void random();
  /// extract the Element data into a vector
  virtual void extract(dVector &) const;
  /// set the modes of an Element in transform space
  virtual void set(const dVector &, const Ordinal);
  //@}

  /// \name Local assembly matrices and residuals
  //@{
  virtual void get_local_mass_matrix(const dVector &);
  virtual void get_local_derivative_matrix();
  virtual void get_local_derivative_matrix(const dVector &);
  virtual void get_local_laplace_matrix();
  virtual void get_local_laplace_matrix(const dVector &);
  virtual void test_on_shape();
  virtual void test_on_shape(const dVector &, dVector &) const;
  virtual void test_on_shape_side(const dVector &, const int, dVector &) const;
  virtual void test_on_grad_shape(const dVector &, char, dVector &) const;
  virtual void test_on_normal_times_gradient_side(const dVector &,
                                                  const int sid,
                                                  dVector & ) const;
  virtual void normal_times_gradient_side(const dVector &, const int,
                                          dVector &) const;
  virtual std::vector<dMatrix*> get_interpolation_matrices() const;
  //@}

  /// \name Transform methods
  //@{
  virtual Basis* get_basis(const int der) const;
  virtual void inner_product();
  virtual void inner_product(dVector &, dVector &) const;
  virtual void forward_transform();
  virtual void forward_transform(dVector &, dVector &) const;
  virtual void forward_transform(Element *) const;
  virtual void forward_transform(Element *, Element *);
  virtual void backward_transform();
  virtual void backward_transform(dVector &, dVector &) const;
  virtual void solve_mass_matrix(dVector &) const;
  virtual void solve_mass_matrix(dMatrix &);
  virtual void interpolate_to_uniform();

  bool full_mass_matrix() const {return full_mass;}
  /// Project to polynomial space in place
  virtual void project() {
    forward_transform();
    backward_transform();
  }
  /// Project to polynomial space
  virtual void project(dVector &x) const {
    assert(x.size()==(dVector::size_type)qtot);
    dVector xh(x,this->nModes());
    this->forward_transform(x,xh);
    this->backward_transform(xh,x);
  }
  //@}

  /// \name Filter methods
  //@{
  virtual void make_constant();
  virtual void low_modes(const Ordinal np);
  virtual void kill_constant();
  virtual void filter(const dVector &);
  virtual void exp_filter(const Scalar Nc, const Scalar s);
  virtual void coarse_scales(const int p_inc);
  virtual void coarse_scales(const int p_inc, dVector &);
  virtual void fine_scales(const int p_inc);
  virtual void fine_scales(const int p_inc, dVector &);
  virtual void fine_scales_transform(const int p_inc, dVector &) const;
  virtual void fill_basis_shift_matrix(dMatrix &G) const;
  virtual void plane_average() {DGM_UNDEFINED;}
  virtual void bound(const Scalar low, const Scalar high);
  virtual void vms_isolate_small();
  virtual void vms_isolate_small(dVector &, dVector &);
  virtual void vms_isolate_small(dVector &);
  //@}

  /// \name Derivative methods
  //@{
  virtual void gradient(const dVector &, dVector &) const;
  virtual void gradient(const dVector &, dVector &, dVector &) const;
  virtual void gradient(const dVector &, dVector &,
                        dVector &, dVector &) const;
  virtual void gradient(const dVector &, dVector &, char) const;
  virtual void local_gradient(const dVector &, dVector &, dVector &) const;
  virtual void local_gradient(const dVector &, dVector &,
                              dVector &, dVector &) const;
  virtual void fdotgrad(const dVector &, const dVector &, dVector &) const {
    DGM_UNDEFINED;
  }
  //@}

  /// \name Geometry methods
  //@{
  virtual void get_coordinates();
  virtual void get_straight_coordinates();
  virtual void get_curved_coordinates();
  virtual void get_side_coordinates(const Ordinal, Point *) const;
  virtual void compute_geometry();
  virtual bool is_affine() const { return true; }
  virtual void compute_straight_geometry();
  virtual void compute_curved_geometry();
  virtual StabMetrics compute_metrics();
  StabMetrics compute_metrics_1d();
  StabMetrics compute_metrics_2d_tensor_prod();
  StabMetrics compute_metrics_nodal_tri();
  StabMetrics compute_metrics_3d_tensor_prod();
  virtual void compute_side_geometry();
  virtual void forward_transform_side(dVector &, dVector &);
  virtual void add_Dirac_delta(const Ordinal qpt, const Scalar amp) = 0;
  virtual void add_Dirac_delta(const Point &p, const Scalar amp) = 0;

  virtual void add_local_Dirac_delta(const Point &p, const Scalar amp) = 0;
  virtual void add_local_Dirac_delta(const vector<dMatrix> &M, const Scalar amp)
    {DGM_UNDEFINED;}
  virtual Scalar interpolate_point(const Point &p) const;
  virtual Scalar interpolate_local_point(const Point &p) const = 0;
  /// Extract the solution at point
  virtual void calculate_interpolation_matrices(vector<fMatrix>&,
                                                 const vector<Point>&) const;
  virtual void apply_interpolation_matrices(dVector &vals,
                                             const vector<fMatrix>&) const;
  virtual void calculate_interpolation_matrices(vector<dMatrix>&,
                                                 const vector<Point>&) const;
  virtual void apply_interpolation_matrices(dVector &vals,
                                             const vector<dMatrix>&) const;
  virtual void interpolate_points(const vector<Point> &ps, dVector &vals) const;
  virtual Point get_local_coordinates(const Point &p) const = 0;
  virtual int get_local_coordinates(const Point &p, Scalar &r) const;
  virtual int get_local_coordinates(const Point &p, Scalar &r, Scalar &s) const;
  virtual int get_local_coordinates(const Point &p, Scalar &r, Scalar &s,
                                    Scalar &t) const;
  //@}


  virtual Topology::ElementType element_type() const = 0;
  /// \name Side methods
  //@{
  /// Extract data from interior storage to a given side storage
  virtual void get_side(const dVector &, const Ordinal, dVector &) const = 0;
  /// Fill a prescribed side with given data
  virtual void fill_side(const dVector &, const int side_id, dVector &);

  /// Fill element sides with a vector
  virtual void fill_sides(const dVector &);
  /// Fill 2d element sides with a normal vector
  virtual void fill_sides(const dVector &, const dVector &);
  /// Fill 3d element sides with a normal vector
  virtual void fill_sides(const dVector &, const dVector &, const dVector &);

  /// fill the Element sides with a parsed expression
  virtual void fill_sides(const Scalar, const string,
                          const Operation operation=Equal);
  /// fill the Element with a constant
  virtual void fill_sides(const Scalar, const Operation=Equal);

  /// Interpolate given vector to a uniform mesh on the sides.
  virtual void fill_sides_uniform(const dVector &);
  /// Copies sides of this element to Element E
  virtual inline void copy_sides(Element *E) const;
  /// Interpolate physical values to side quadrature points
  virtual void load_side(const dVector &, const Ordinal, dVector &) const=0;
  /// Lift a flux difference from the element sides to element interior
  /*! This is a generalized lift operation that takes the sides of the
      current element and the element F and lifts the difference from the
      sides to the interior.

      We work with flux terms of the form
      \f[\int_{\Gamma_e}
        \bW_l^T\left(\hat\bF_n(\bU_l,\bU_r)-\bF_n(\bU_l)\right)\;
        d\Gamma_e\f]
      where \f$\bF_n(\bU)\f$ is the real flux normal to the boundary
      and \f$\hat\bF_n(\bU_l,\bU_r)\f$ is the numerical flux normal to the
      boundary.

      \param[in] F - Contains \f$\hat\bF_i(\bU_l,\bU_r)\f$ on sides
      \param[out] R - The lifted result:
                      \f$\left(\hat\bF_i(\bU_l,\bU_r)-\bF_i(\bU_l)\right)\f$
      \param[in] dir - ith direction, either ('x', 'y', 'z', 'n')

      Note that the direction specifies whether we are lifting a flux
      in a single direction (say 'x') or whether we are lifting a normal
      flux ('n').  We often lift fluxes in a single coordinate direction when
      we are computing a jump-savvy gradient.  Lifting in the boundary normal
      direction is done when evaluating a divergence term.

      \pre This element must contain \f$\bF_n(\bU)\f$ on its sides.  On option
           is for the sides to be zero so that this term is not included.
*/
  virtual void lift(const Element *const F, dVector &R,
                    const char dir='n') const=0;
  /// Lift data from the element sides to the element interior
  /** This version is a simplified lifting operation taking the current
   *  element's sides and lifting to the volume with output to
   *  \note that this method is experimental and not yet implemented in all
   *        elements.
   */
  virtual void lift(dVector &R) const { DGM_UNDEFINED; }
  /// Compute integral over all element sides
  Scalar compute_side_integral() const;
  /// Compute integral of given data over given side
  /** \todo Both arguments should be const. */
  virtual Scalar compute_side_integral(dVector &, Ordinal) const;
  /// Computes the measure (length, area) of all sides
  virtual Scalar compute_side_measure() const;
  /// Returns the vertices of the requested side
  virtual vector<Point> get_side_endpoints(const Ordinal) const;
  virtual Scalar compute_subside_geometry(Side *, const Element &) const;
  virtual Scalar compute_subside_geometry(Side *, const vector<Point> &) const;
  virtual void push_to_subsides() const = 0;
  virtual void push_side_geom_to_subside(Side*,const Side*,const Scalar)const;

  virtual Ordinal sideMap(const Side *s, const Ordinal ql) const;
  virtual void    sideMap(const Side *s, const Ordinal qt, Ordinal *k) const;
  virtual Ordinal sideVertMap(const Ordinal lsid, const Ordinal lvid) const;
  /// Returns the dimension(s) of the requested side
  virtual void side2size(const Ordinal side, iVector &q) const;
  /// Returns the total size of requested side
  virtual Ordinal side2size(const Ordinal side) const;
  //@}

  /// \name Curved Side methods
  //@{
  /// Returns information needed for curved side evaluation
  virtual void get_curved_side_info(const Ordinal, vector<Point> &,
                                    dVector &, int &) const;
  /// Transform from C^0 modified Jacobi basis to physical space
  virtual void J_backward_transform(dVector &, dVector &);
  /// Solve a side mass matrix
  /** \todo Change to solve_side_mass_matric. */
  virtual void solve_1d_mass_matrix(dVector &) const;
  /// Given physical coordinates, transform to modal coefficients
  /** \todo Change to J_forward_transform_side. */
  virtual void forward_transform_side(const Ordinal, dVector &,
                                      dVector &, dVector *);
  /// Gets the coordinates of a straight sided element for given side
  virtual void get_straight_side_coordinates(const Ordinal, dVector &,
                                             dVector &, dVector &) const;
  /// Get Edge information from Face (3d-only)
  virtual void get_edge(Ordinal q1, Ordinal q2, Scalar *,
                        Ordinal edgid, Scalar *);
  /// Generate curved sides
  virtual void generate_curve();
  //@}

  /// \name Norm and inner product methods
  //@{
  /// Returns the \f$L_\infty\f$ norm
  virtual Scalar norm_Linf() const;
  /// Returns the \f$L_2\f$ norm
  virtual Scalar norm_L2() const;
  /// Returns the \f$H_1\f$ norm
  virtual Scalar norm_H1() const;
  /// Computes both the \f$L_2\f$ norm and the element measure
  virtual void   norm_L2(Scalar *, Scalar *) const;
  /// Computes both the \f$H_1\f$ norm and the element measure
  virtual void   norm_H1(Scalar *, Scalar *) const;
  /// Integrates the element and optionally returns measure
  virtual Scalar integrate( Scalar * =NULL ) const;
  /// Integrates the element with given data optionally returning measure
  virtual Scalar integrate(const dVector &, Scalar * =NULL) const;
  /// Returns the size of the element (length, area, volume)
  virtual Scalar compute_measure() const;
  /// Returns the \f$L_2\f$ inner product of two elements
  virtual Scalar L2_inner_product(const Element *Y,
                                  Scalar *measure =NULL) const;
  /// Returns the \f$L_2\f$ inner product of two vectors of data on this element
  virtual Scalar L2_inner_product(const dVector &x, const dVector &y,
                                  Scalar *measure =NULL) const;
  /// Applies the element metric to the element data
  virtual void apply_metric();
  /// Removes the element metric from the element data
  virtual void remove_metric();
  //@}

  /// \name Spatial regularization for optimal control
  //@{
  /// Computes derivative on a prescribed side
  virtual void get_side_Ds(const int sid, const dVector &f, dVector &fs)
    const {DGM_UNDEFINED;}
  /// Determines whether a side is curved
  virtual void get_side_curvature(const int, dVector &) const {DGM_UNDEFINED;}
  /// Gets a one-dimensional derivative operator for given side
  virtual void get_D1( const int sid, dMatrix &) const { DGM_UNDEFINED;}
  //@}

  /// \name Utilities
  //@{
  /// Simple point format for mesh diagnostics
  virtual void tecplot(FILE *);
  /// Flexible method for outputing element data
  virtual void output(FILE *, const char='d') const;
  /// Return length of particular binary data
  virtual streamoff binaryLength(const OutputType flag) const;
  /// Output data in binary output for visualization
  virtual void binaryOutput(FILE *, const OutputType flag) const;
  /// Write out the mesh on this element
  virtual void write_mesh(ostream &f, const unsigned prec=15) const;
  /// Gets the properties to help determine the weight (expense) of element
  virtual void get_weight_props(Topology::ElementType &, bool &,
                                Ordinal &) const;
  /// Get the weight (normalized computational cost) for this element
  virtual int get_weight() const;
  /// Clone this element
  virtual Element* clone() const;
  /// Update the workspace for this element
  virtual void update_workspace(const Ordinal max) const = 0;
  /// Returns the number of subcells for vizualizing this element
  /** The default implementation is for tensor-product elements.  Otherwise
      you must override this implementation. */
  inline virtual Ordinal ncells() const {
    if (nsd()==1) {
      return qa-1;
    } else if (nsd()==2) {
      return (qa-1)*(qb-1);
    } else if (nsd()==3) {
      return (qa-1)*(qb-1)*(qc-1);
    } else {
      error("Illegal nsd in Element::ncells():  nsd = "+asString(nsd()));
    }
    return 0;
  }
  //@}

  /// \name Attribute accessors
  //@{
  /// returns the polynomial order
  Ordinal get_p() const {return pOrder(); }

#ifdef DGM_USE_GENERAL_GHOSTING
  /// returns adjacent elements
  const vector<Size> &adjacent_elements() const {return adj_els; }
#endif
  //@}

  /// \name Local (non virtual) Element helpers methods
  //@{
  inline void write_connectivity(FILE *) const;
  inline void write_connectivity(ostream &f) const;
  inline void write_node_connectivity(ostream &f) const;
  inline void read(ifstream &);
  inline void write(FILE *) const;
  /// Determine if any element quadrature point is within radius of point;
  bool is_in_element(const Point &p, const Scalar radius) const;
  bool is_in_element(const Point &, const dMatrix &, const dVector &) const;
  bool is_in_box(const Point &p, const Scalar radius=0) const;
  void set_box();
  //@}

  /// Put an Element into an output stream
  inline friend std::ostream& operator<<(std::ostream&, const Element&);

  /// Helper for computing Element level \f$L_2\f$ inner products
  inline static Scalar L2_inner_product(const Element *e1, const Element *e2,
                                        Scalar *measure=0);

  /// Destructor
  virtual ~Element();

  /// Seed the random number generator
  /** This replaces a simple call to srandom but with the advantage of making
      sure that the elements always use a consistent random number
      generator. */
  inline static void srandom(const unsigned int seed) {
    if (random_state.size()!=random_state_length)
      random_state.resize(random_state_length);
    char *old_state = ::initstate(seed, random_state.ptr(),
                                  random_state_length);
    ::setstate(old_state);
  }

#ifdef DGM_USE_GENERAL_GHOSTING

private:

  /// gives boost access to private data
  friend class boost::serialization::access;

  /*! serialize this class
   *  @tparam Archive boost input or output archive class
   *  @param ar       archive
   *  @param version  (not needed here, see boost documentation)
   */
  template<class Archive>
  void serialize(Archive &ar, const unsigned int version){
    ar & _id;
    ar & _gid;
    ar & type;
    ar & info;
    ar & qa & qb & qc & qtot;
    ar & adj_els;
#ifndef DGM_CONTIGUOUS
    ar & u;     // uh will be aliased later
    ar & state; // state travels with data in share_ghost_element_data()
#endif
    ar & vert;
    ar & edge;
    ar & face;
    boost::serialization::split_member(ar, *this, version);
  }

  /*! write this class to archive
   *
   * @tparam Archive boost input or output archive class
   * @param ar       archive
   * @param version  (not needed here, see boost documentation)
   */
  template<class Archive>
  void save(Archive & ar, const unsigned int version) const {
    // we have to be a little clever about shared pointers
    // boost shared_ptr could be serialized as is, but Teuchos::RCP not.
    // So as a first step, I will just serialize the raw data and create
    // a new copy on deserialization. Since shared Curve object pointers usually
    // have only one reference count anyway, this generates no performance
    // issues.
    // See the boost serialization documentation for the issues around shared
    // pointers.
    bool store_curve;
    if (curve.get() == NULL) { //  store only, if I actually have data
      store_curve = false;
    } else {
      store_curve = true;
    }
    ar & store_curve; // remember, that we have stored a curve
    if (store_curve) {
      Curve* c = curve.get();
      ar & c;  // note: we need to store the pointer; only then boost can
               //       perform serialization of derived class objects like
               //       the Straight class
    }
  }
  /*! load this class from archive
   *
   * @tparam Archive boost input or output archive class
   * @param ar       archive
   * @param version  (not needed here, see boost documentation)
   */
  template<class Archive>
  void load(Archive & ar, const unsigned int version) {
    full_mass = false;
    bool curve_stored;
    ar & curve_stored;
    if (curve_stored) {
      Curve *c;
      ar & c;
      curve.reset( c->clone() );
      delete c;
    }
  }
#endif

protected:

  /// Default constructor is protected so that only derived types can construct
  inline Element(const Ordinal ID=numeric_limits<Ordinal>::max(),
                 const Basis::Type TYPE=Basis::Ortho, const int VMS=0);

  /// Clamp t to be between a and b (inclusive)
  inline static Scalar clamp(const Scalar t, const Scalar a, const Scalar b) {
    return max(min(t,b),a);
  }

/// Save the RAND state for consistency
#define DGM_ELEMENT_SAVE_RAND_STATE

  /// random Scalar between [a,b)
  inline static Scalar random(const Scalar a, const Scalar b) {
#ifdef DGM_ELEMENT_SAVE_RAND_STATE
    if (random_state.size()==0) srandom(1);
    char *old_state = ::setstate(random_state.ptr());
    Scalar r = ((Scalar)::random()/((Scalar)(RAND_MAX)+(Scalar)(1)));
    ::setstate(old_state);
    return (b-a)*r+a;
#else
    Scalar r = ((Scalar)::random()/((Scalar)(RAND_MAX)+(Scalar)(1)));
    return (b-a)*r+a;
#endif
  }

private:

  /// The data length of the random number generator
  static unsigned int random_state_length;

  /// The state of the Element's random number generator
  static CMC::Vector<char,unsigned int> random_state;

  /// Copy construction is not allowed by making this private
  inline Element(const Element&);

  /// Copy construction is not allowed by making this private
  inline Element(const Element*);

};

//============================================================================
//                      I m p l e m e n t a t i o n
//============================================================================

// default constructor
inline Element::Element(const Ordinal ID, const Basis::Type TYPE, const int VMS) :
  full_mass(false), _id(numeric_limits<Ordinal>::max()), _gid(uid<Size>()),
  type(TYPE), info(new Info<Scalar,Ordinal>()), qa(0), qb(0), qc(0), qtot(0),
  box(), psi(0), state(Unallocated)
{
  // cout << "Element::Element()" << endl;
  if (ID <= uid<Ordinal>())
    _id = ID;
  else
    throw DGM::exception("Local element id overflow");
}

// copy constructor (not implemented)
inline Element::Element(const Element &E) :
  full_mass(E.full_mass), _id(E._id), _gid(E._gid), type(E.type),
  info(new Info<Scalar,Ordinal>()), qa(E.qa), qb(E.qb), qc(E.qc), qtot(E.qtot),
  box(E.box)
  {
  throw DGM::exception("Element reference copy constructor not implemented!");
  *this = E;
}

// copy constructor (not implemented)
inline Element::Element(const Element *E) :
  full_mass(E->full_mass), _id(E->_id), _gid(E->_gid), type(E->type),
  info(new Info<Scalar,Ordinal>()), qa(E->qa), qb(E->qb), qc(E->qc),
  qtot(E->qtot), box(E->box) {
  throw DGM::exception("Element pointer copy constructor not implemented!");
  *this = *E;
}

/// Copy the sides from this Element to Element E
inline void Element::copy_sides( Element *E ) const {
  assert(nSides() == E->nSides());
  for (Ordinal i=0; i<nSides(); ++i) {
    // cout<<id<<" "<<i<<" "<<E->side[i]->qtot<<" "<<side[i]->qtot<<endl;
    assert( E->side[i]->qtot() == side[i]->qtot() );
    E->side[i]->u = side[i]->u;
  }
}

/// Read element data from file stream
inline void Element::read(ifstream &fs) {
  fs.read(reinterpret_cast<char*>(u.data()), sizeof(Scalar)*u.size());
}

/// Write element data to file stream
inline void Element::write(FILE *fp) const {
  if ( fwrite( u.data(), sizeof(Scalar), u.size(), fp) !=
       static_cast<size_t>(u.size()) ) {
    DGM::Comm::World->cerr() << "Error writing element " << gid() << endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
}

/// Element output to a stream in human readable format
inline std::ostream & operator<<(std::ostream &os, const Element &E) {
  os << "Element Output" << endl;
  os << " id      = " << E._id << endl;
  os << " gid     = "
     << (defined(E._gid) ? asString(E._gid) : "Undefined") << endl;
  os << " type    = " << E.type << endl;
  os << " nVerts  = " << E.nVerts() << endl;
  os << " nEdges  = " << E.nEdges() << endl;
  os << " nFaces  = " << E.nFaces() << endl;
  os << " nSides  = " << E.nSides() << endl;
  os << " pOrder  = " << E.pOrder() << endl;
  os << " L       = " << E.L() << endl;
  os << " nModes  = " << E.nModes() << endl;
  os << " Sigma   = " << E.sigma() << endl;
  os << " Measure = " << E.measure() << endl;
  os << " State   = " << E.state << endl;
  return os;
}

/// Write the element side connectivity
/** \note Here we up-cast to unsigned long long to prevent any
    loss of precision.  Would be better to switch to a c++ fstream. */
inline void Element::write_connectivity(FILE *fp) const {
#ifdef DGM_SIDE_GID_IN_CONNECTIVITY
  for (int ed=0; ed<nSides(); ed++) {
    if (side[ed]->base)
      if (side[ed]->link)
        fprintf(fp,"%c\t%llu\t%llu\t%llu\t%lu\t%llu\n",'E',
                (unsigned long long)gid(),(unsigned long long)ed,
                (unsigned long long)side[ed]->link->geid(),
                (unsigned long long)side[ed]->link->id(),
                (unsigned long long)side[ed]->link->gid());
      else
        fprintf(fp,"%c\t%llu\t%llu\t%llu\t%llu\t%llu\n",'E',
                (unsigned long long)gid(),(unsigned long long)ed,
                (unsigned long long)side[ed]->base->geid(),
                (unsigned long long)side[ed]->base->id(),
                (unsigned long long)side[ed]->base->gid());
  }
#else
  for (Ordinal ed=0; ed<nSides(); ed++) {
    if (side[ed]->base) {
      if (side[ed]->link) {
        fprintf(fp,"%c\t%llu\t%llu\t%llu\t%llu\n",'E',
                (unsigned long long)gid(),(unsigned long long)ed,
                (unsigned long long)side[ed]->link->geid(),
                (unsigned long long)side[ed]->link->id());
      } else {
        fprintf(fp,"%c\t%llu\t%llu\t%llu\t%llu\n",'E',
                (unsigned long long)gid(),(unsigned long long)ed,
                (unsigned long long)side[ed]->base->geid(),
                (unsigned long long)side[ed]->base->id());
      }
    }
    for (unsigned ss=0; ss<side[ed]->subsides().size(); ++ss) {
      if (side[ed]->subsides()[ss]->base) {
        if (side[ed]->subsides()[ss]->link) {
          fprintf(fp,"%c\t%llu\t%llu\t%llu\t%llu\n",'E',
                  (unsigned long long)gid(),(unsigned long long)ed,
                  (unsigned long long)side[ed]->subsides()[ss]->link->geid(),
                  (unsigned long long)side[ed]->subsides()[ss]->link->id());
        } else {
          fprintf(fp,"%c\t%llu\t%llu\t%llu\t%llu\n",'E',
                  (unsigned long long)gid(),
                  (unsigned long long)ed,
                  (unsigned long long)side[ed]->subsides()[ss]->base->geid(),
                  (unsigned long long)side[ed]->subsides()[ss]->base->id());
        }
      }
    }
  }
#endif
}

/// Write the element side connectivity
inline void Element::write_connectivity(ostream &f) const {
  for (Ordinal ed=0; ed<nSides(); ++ed) {
    if (side[ed]->base) {
      if (side[ed]->link) {
        f << 'E' << '\t'
          << gid() << '\t'
          << ed << '\t'
          << side[ed]->link->geid() << '\t'
          << side[ed]->link->id();
      } else {
        f << 'E' << '\t'
          << gid() << '\t'
          << ed << '\t'
          << side[ed]->base->geid() << '\t'
          << side[ed]->base->id();
      }
#ifdef DGM_SIDE_GID_IN_CONNECTIVITY
      f << '\t' << side[ed]->link->gid();
#endif
      f << '\n';
    }
  }
}

/// Write the nodal element connectivity to an output stream
void Element::write_node_connectivity(ostream &f) const {
  f << std::setw(10) << nVerts();
  for (Ordinal ivert=0; ivert<nVerts(); ivert++) {
    f << std::setw(10) << vert[ivert]->gid;
  }
  f << "\n";
}

/// \f$L_2\f$ inner product of the data on two conforming elements
inline Scalar Element::L2_inner_product(const Element *e1, const Element *e2,
                                        Scalar *measure) {
  Scalar value;
  Scalar result = e1->L2_inner_product(e2, &value);
  if (measure) *measure = value;
  return result;
}

inline bool Element::is_in_box(const Point &p, const Scalar r) const {
  const bool in_box =
    box.first.x-r <= p.x && p.x <= box.second.x+r &&
    box.first.y-r <= p.y && p.y <= box.second.y+r &&
    box.first.z-r <= p.z && p.z <= box.second.z+r;
  return in_box;
}

} // namespace DGM

#endif  // DGM_ELEMENT_HPP
