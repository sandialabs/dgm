#ifndef DGM_FIELD_HPP
#define DGM_FIELD_HPP

/** \file Field.hpp
    \brief Field declaration as a container for DGM elements
    \author S. Scott Collis
*/

// System includes
#include <algorithm>
#include <fstream>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>
#include <set>

// boost includes
#include <boost/unordered_map.hpp>

// DTK includes
#include "DTK.hpp"

// DGM includes
#include "BoundingBox.hpp"
#include "Comm.hpp"
#include "Types.hpp"
#include "Partition.hpp"
#include "Mesh.hpp"
#include "Element.hpp"
#include "ElementBlock.hpp"
#include "Boundary.hpp"
#include "BndryStats.hpp"
#include "Filter.hpp"
#include "SideLoop.hpp"

// Trilinos includes
#ifdef DGM_USE_EPETRA
#include "Teuchos_RCP.hpp"
#include "Epetra_Map.h"
#endif

namespace DGM {

#ifdef DGM_DOXYGEN
/// define to save fields in transform space
#define DGM_FIELD_TRANSFORM
#endif

/// A collection of elements, sides, and boundaries that lives on a Domain
/** This is a concrete Field class for a scalar Scalar field.  The idea is
    that this can be turned into a template class for a field that can hold
    any type such as Scalar, complex, or even a std::vector<Scalar>.

    Some options for the future include:
    - A field should know about it's boundary conditions (DONE)
    - Instead of using the constructor, I could supply a default constructor
    that would make an empty field.  Then I could have a method that
    adds_elements to the field.  This might be a more natural and convenient
    way of doing it.
    - I currently have a private ne variable that holds the number of elements
    in the field.  This is really not needed, but it prevents me from having to
    always call the size() method for the std::vector. */
class Field : public DTK::Field<DGM::Scalar,DGM::Ordinal> {

  const DGM::Comm::Ptr comm;   ///< Communicator for this field

  /// Default blocksize
  static const Ordinal BlkSize=500;

public:

  /// Shared pointer to Field
  typedef DGM::Shared<Field>::Ptr Ptr;

  /// Global size type
  typedef DGM::Size GlobalSize;

  /// Local size type
  typedef DGM::Ordinal LocalSize;

  /// Map for type Size used for element maps
  typedef boost::unordered_multimap<GlobalSize,GlobalSize> SizeMap;

  /// Map for type int use for p and q order maps
  typedef boost::unordered_map<GlobalSize,LocalSize> OrderMap;

  /// Pair for working with MultiSides
  typedef std::pair<GlobalSize,LocalSize> MultiSidePair;

  /// Set for holding MultiSides
  typedef std::set<MultiSidePair> MultiSideSet;

  /// Tells how thoroughly to construct the Field
  enum Construction {
    FULL,                   ///< Full construction (sets elements, allocates)
    MINIMAL                 ///< Minimum construction (just sets the elements)
  };

private:

  LocalSize _qtot;          ///< Number of quadrature point in field
  LocalSize _ndof;          ///< Number of modes in field
  LocalSize _sdof;          ///< Number of side degrees of freedom (qpts)
  LocalSize _nsd;           ///< Number of space dimensions

public:

  GlobalSize gne;           ///< Global number of elements in field
  LocalSize  ne;            ///< Local number of elements in field
  LocalSize nbc;            ///< Number of boundary conditions in field
  LocalSize Qmax;           ///< Maximum number of quad pts for all elements
  LocalSize Lmax;           ///< Maximum number of modes for field elements
  LocalSize BlockSize;      ///< Maximum number of elements in a block
  const string root;        ///< Root input file name
  string name;              ///< Name of the variable stored in the field
  std::vector<Element*> el; ///< Element vector (local owned by this proc.)
private:
  std::map<int,Element*> ghost_el; ///< Element vector (not owned by this proc.)
public:
#ifdef DGM_USE_ELEMENT_BLOCKS
  std::vector<ElementBlock*> eb;   ///< Element block vector
#endif
  std::vector<Boundary*> bc;       ///< Boundary vector
  std::vector<std::string> bc_types;  ///< List of boundary types in bc
  std::map<std::string, std::vector<Boundary*> > bc_by_type;
                                       ///< bc array sorted by type.

  /// Partition connectivity for this field
  std::vector<Pcon<GlobalSize,LocalSize,Scalar>*> pc;

  /// Partition for parallel computing
  typedef Partition<GlobalSize,LocalSize,Scalar>::Ptr PartitionPtr;
  PartitionPtr partition;

  BndryStats *bndry_stats; ///< Boundary statistics

  /// Contiguous storage for element interior data
  dVector elmt_data;
  /// Contiguous storage for side data
  dVector side_data;

  int verb;                     ///< Verbosity
  std::string weight_database;  ///< empty or name of weight file from input
  bool write_partition;         ///< True writes the partition to root.part.#
  bool use_zoltan;              ///< True uses Zoltan inline partitioning

  bool have_my_bbox;            ///< True if (local) bounding box is defined
  BoundingBox my_bbox;          ///< My (local) bounding box

  /// \name Accessors
  //@{
  /// Total number of quadrature points
  const LocalSize & qtot() const { return _qtot; }
  /// Set the total number of quadrature points
  void qtot(const LocalSize qtot) { _qtot=qtot; }
  /// Total number of degrees of freedom
  const LocalSize & ndof() const { return _ndof; }
  /// Set the total number of degrees of freedom
  void ndof(const LocalSize ndof) { _ndof=ndof; }
  /// Total number of side degrees of freedom
  const LocalSize & sdof() const { return _sdof; }
  /// Set the total number of side degrees of freedome
  void sdof(const LocalSize sdof) { _sdof=sdof; }
  /// Number of space dimensions
  const LocalSize & nsd() const { return _nsd; }
  //@}

  /// \name Constructors and Destructor
  //@{
  /// Construct from a mesh file
  Field(const Ordinal p, const Ordinal q, const string &root_,
        const string &name_,
        Partition<Size,Ordinal,Scalar>::Ptr &domain_partition,
        const DGM::Comm::Ptr = DGM::Comm::World, const int p_inc=0,
        const Ordinal blocksize=BlkSize );

  /// Construct from a mesh file (new parallel construction)
  Field(const Ordinal p, const Ordinal q, const string &root_,
        const string &field_name,
        Partition<Size,Ordinal,Scalar>::Ptr &domain_partition,
        const int parallel, const unsigned numeqns, const int physics,
        const DGM::Comm::Ptr = DGM::Comm::World,
        const int p_inc=0, const Ordinal blocksize=BlkSize );

  /// Construct from a Mesh data-structure
  Field(const Ordinal p, const Ordinal q, Mesh &grid,
        const string &root_="grid",
        const string &name_="", const Construction=FULL,
        const DGM::Comm::Ptr = DGM::Comm::World,
        const Ordinal blocksize=BlkSize );

  /// Copy constructor
  Field(const Field *, const string &root="", const string &name="");

  /// destructor
  ~Field();
  //@}

  /// \name Boundary condition methods
  //@{
private:
  static bool sort_bc(const Boundary *i, const Boundary *j) {
    std::pair<const Element *, const Side *> first (i->elmt, i->S);
    std::pair<const Element *, const Side *> second(i->elmt, i->S);
    return first < second;
  }
  static bool cmp_bc (const Boundary *i,
               const std::pair<const Element*,const Side*> &second) {
    std::pair<const Element*,const Side*> first(i->elmt, i->S);
    return first < second;
  }
public:
  void initialize_bc(const string &root="mesh", const string &ext=".bc");
  const Boundary *find_bc(const Element *e, const Side *s) const {
    const std::pair<const Element*,const Side*> B(e,s);
    auto b = std::lower_bound(bc.begin(), bc.end(), B, cmp_bc);
    if (b != bc.end() && e == (*b)->elmt && s == (*b)->S) return *b;
    return NULL;
  }
  const std::vector<std::string> &bc_types_vec() const { return bc_types; }
  const std::vector<Boundary*> &bc_for_type(const std::string &t) const {
    static const std::vector<Boundary*> empty_vector;
    const std::map<std::string, std::vector<Boundary*> >::const_iterator i =
      bc_by_type.find(t);
    if (i == bc_by_type.end()) return empty_vector;
    else return i->second;
  }

  void read_bc(ifstream &);
  void write_bc(const string &) const;
  //@}

  /// \name Element methods
  //@{
  inline void Abs();
  inline void zero();
  inline void forward_transform();
  inline void backward_transform();
  void set(const string &);
  void read_ic(ifstream &);
  inline void fill( const Scalar );
  inline void fill( const dVector & );
  inline void extract( dVector & ) const;
  void compute_geometry();
  void compute_geometry(const std::map<int,Element*>&);
  inline void interpolate_to_uniform();
  inline void make_constant();
  inline void low_modes(const Ordinal);
  inline void low_modes(const Ordinal, const Ordinal);
  inline void low_modes(const Scalar, const Ordinal);
  inline void low_modes(const std::map<Size,Ordinal> &order);
  inline void kill_constant();
  inline void coarse_scales(const int p_inc);
  inline void fine_scales(const int p_inc);
  inline void exp_filter(const Scalar eta, const Scalar s);
  inline void set_state(const Element::States);
  inline void project();
  inline void project(Field *) const;
  inline void project(Field::Ptr) const;
  void mass_project(Field *, Field *) const;
#ifdef DGM_USE_ELEMENT_BLOCKS
  void initialize_element_blocks();
#endif
  //@}

  /// \name Side methods
  //@{
  void set_side_links(const string &root="");
  void set_side_links(const Field *);
  void set_side_links(const Mesh &);
  void set_side_links_pc(const Mesh &, const std::vector<int>&,
                         const std::vector<int>&);
  void set_side_links_pc(const Mesh &, const OrderMap &, const OrderMap &);
  void read_curve(const string &);
  void read_curve_pc(const string &);
  void read_connectivity(ifstream &,
                         const std::set<std::pair<GlobalSize,LocalSize> >&);
  void write_connectivity(const string &) const;
  inline void fill_sides();
  void fill_sides_of_ghost_elements();
  inline void fill_sides(const Scalar);
  inline void fill_bc_sides();
  inline void fill_bc_sides(const Scalar);

  typedef std::pair<size_t, std::pair<Ordinal,Size> > key;
  typedef std::vector<Point> value;
  typedef std::map<key,value> side_coord_map;
  side_coord_map share_side_coord() const;
  void share_normals() ;
  void share_sides();
  void begin_share_sides();
  void end_share_sides() const;
  void adjust_side_order();
  void adjust_side_order_pc();
  void compute_side_geometry();
  void compute_subside_geometry();
  void compute_side_geometry(const std::map<int,Element*> &elements);
  void print_side_links() const;
  void write_graph(const string&) const;
  void set_flip(const bool pc=false);
  void set_global_side_id();
  void set_global_side_id_pc();
  inline void write_side_stats(const LocalSize index=
                               undefined<LocalSize>()) const;
  inline Scalar get_max_sigma() const;
  //@}

  /// \name Utility methods
  //@{

  /// Get the communicator for this Field
  const DGM::Comm::Ptr get_comm() const {return comm;}
  void write_mesh(const string &, const string &s=string()) const;
  void write_weights(const string &) const;
  void tecplot(const string &, const string &) const;
  void read(const string &);
  void read(ifstream &);
  void write(ofstream &) const;
  void make_storage();
  void reset_storage(dVector &, dVector &);
  void make_partition(const string &);
  void make_partition();
  bool use_zoltan_partitioning();
  void zoltan2(const Mesh&, Ordinal*, Ordinal*) const;
  void read_elements(Mesh &, const Ordinal p, const Ordinal q,
                     string fname, const int p_inc, OrderMap &pm,
                     OrderMap &qm);
  void make_partition_sides(const Field *);
  void clear_partition_sides();
  void pack();
  void unpack();
  void apply_metric();
  void remove_metric();
  /// Compute the spatial average of the Field
  Scalar average() const;
  void plane_average();
  bool finite() const;
  void bound(const Scalar min, const Scalar max);
  Scalar min() const;
  Scalar min(GlobalSize &elem) const;
  Scalar max() const;
  Scalar max(GlobalSize &elem) const;
  Scalar minSide() const;
  Scalar maxSide() const;
  void relative_max_error(const Field& f, Scalar& rLinf,
                          Scalar& rL2, Scalar& rH1) const;
  void range() const;
  void rangeSide() const;
  void random();
  /// Set the name of this field
  void set_name(const string s) { name = s; }
  /// get the name of this field
  string get_name() const { return name; }
  void set_vertex_gid(std::vector<std::vector<int> > &nglob);
  void read_node_connectivity(const string &root="mesh",
                              const string &ext=".cgc");
  void write_node_connectivity(const string &) const;
  // The following two methods are not implemented
  // int find_source_elem(Point pnode, int * elemindex) const;
  // void check_bounds(Scalar coord, Scalar *min, Scalar *max) const;
  //@}

  /// \name Norm and Error methods
  //@{
 
  /// Output the infinity, L2 and H1 norms of a Field
  void norm(const string &Name="") const;
  /// Compute the infinity, L2 and H1 norms of a Field
  void norm(Scalar &, Scalar &, Scalar &) const;
  /// Compute the infinity, L2 and H1 norms of an Element
  void norm( GlobalSize, Scalar &, Scalar &, Scalar &) const;
  //@}

  /// \name Methods for locatcing Elements within a Field
  //@{
  
  void boxes(std::vector<std::vector<float> > &bounds) const;
  std::vector<float> box(const Ordinal element_number) const;
  BoundingBox box() const;
  const BoundingBox & my_box() const;
  bool is_in_element(const Point &point,
                     const Ordinal element_number,
                     const Scalar epsilon=1.0e-10) const;
  //@}

 protected:

  /// Hidden copy constructor
  inline Field(Field &);

  /// Connectivity map in 2d is simple and can be defined statically
  static const int con2d[4][4];

 public:

  // Seed the random number generator
  inline void srandom(unsigned int seed) {
    if (comm->Master()) if (seed==0) seed = (unsigned int)::time(NULL);
    comm->Broadcast(&seed,1,0);
    Element::srandom(seed);
  }

  static inline Scalar local_L2_inner_product( const Field *, const Field *,
                                               Scalar *measure=0 );
  static inline Scalar L2_inner_product( const Field *, const Field *,
                                         Scalar *measure=0 );

  static inline Scalar local_L2_inner_product( const Field::Ptr,
                                               const Field::Ptr,
                                               Scalar *measure=0 );
  static inline Scalar L2_inner_product( const Field::Ptr,
                                         const Field::Ptr,
                                         Scalar *measure=0 );

  /// \name Read-only access methods to ghost element data
  //@{
  /// get full ghost element map
  const std::map<int,Element*>& GhostElementMap() const {return ghost_el;};
  /// get a particular ghost element
  Element* GetGhostElement(int gid) const {return ghost_el.find(gid)->second;};
  /// check, whether ghost element exists
  bool GhostElementExists(int gid) const {
    return ghost_el.find(gid) != ghost_el.end();
  };
  //@}

#ifdef DGM_USE_EPETRA
 private:
  Teuchos::RCP<Epetra_Map> ele_rmap;  ///< unique element map
  Teuchos::RCP<Epetra_Map> ele_cmap;  ///< overlapping element map w/ ghosts
 public:
  /// \name Epetra support methods
  //@{
  /// const access to element row map
  const Epetra_Map * row_element_map() const {
    if (ele_rmap == Teuchos::null) {
      comm->error("Field::row_element_map(): ele_rmap not allocated");
    }
    return ele_rmap.get();
  };
  /// const access to element column map
  const Epetra_Map * col_element_map() const {
    if (ele_cmap == Teuchos::null) {
      comm->error("Field::col_element_map(): ele_cmap not allocated");
    }
    return ele_cmap.get();
  };
  //@}
  /// \name Element ghosting methods
  //@{
  void init_redistribution_framework(const Epetra_Comm& Comm);
  void ghost_aura();
  void test_element_serialization();
 private:
  void reset_side_links();
  //@}
#endif
};

/// \name Field helper functions
//@{
inline void project(Field *);
inline void block_project(Field *);
inline void mass_project(Field *, Field *);
inline void filter_project(Field *, std::vector<Filter*>& );
inline void copy_sides(const Field *, Field *);
inline void copy( const Field *X, Field *Y, const bool check_names=true);
//@}

/// \name Algebra on Fields
//@{
inline void add(const Field *, Field *);
       void add( const Field *X, const std::vector<Size>&X_to_Y, Field *Y);
       void extract(Field *X, const std::vector<Size>&X_to_Y, const Field *Y);
inline void add( const Scalar a, Field *);
inline void add( const dVector &a, Field *);
inline void subtract( const Scalar a, Field *);
inline void subtract( const dVector &a, Field *);
inline void subtract( const Field *X, Field *Y);
inline void axpy( const Scalar a, const Field *X, Field *Y );
inline void axpy( const Scalar a, const Field *X, const Field *Y, Field *Z );
inline void axpy( const dVector &a, const Field *X, Field *Y );
inline void axpy( const dVector &a, const Field *X, const Field *Y, Field *Z );
inline void axpby( const Scalar a, const Field *X, const Scalar b,
                   const Field *Y, Field *Z );
inline void scale( const Scalar a, Field *X );
inline void scale( const dVector &a, Field *X );
inline void scale ( const Field *X, Field *Y );
inline Scalar dot( const Field *X, const Field *Y );
inline void invert( Field *X );
inline void multiply( const Field *X, Field *Y );
inline void Sqrt( Field *X );
//@}

//============================================================================
//                      I m p l e m e n t a t i o n
//============================================================================

/// Zero the element and bc storage for this Field
inline void Field::zero() {
  for (LocalSize e=0; e<ne; e++) el[e]->zero();
  for (LocalSize b=0; b<nbc; b++) bc[b]->zero();
}

/// Absolute value
inline void Field::Abs() {
  for (LocalSize e=0; e<ne; e++) el[e]->Abs();
  for (LocalSize b=0; b<nbc; b++) bc[b]->Abs();
}

/// Check to make sure that a Field is finite
inline bool Field::finite() const {
  using std::isfinite;
  bool result=true;
#ifdef DGM_CONTIGUOUS
  // check internal values
  for (LocalSize i=0; i<elmt_data.size(); ++i)
    result = result && (bool)isfinite(elmt_data[i]);
  // check side values
  for (LocalSize i=0; i<side_data.size(); ++i)
    result = result && (bool)isfinite(side_data[i]);
#else
  for (size_t iele = 0; iele != el.size(); iele++) {
    for (int i = 0; i != el[iele]->u.size(); i++) {
      result = result && (bool)isfinite(el[iele]->u[i]);
    }
    for (size_t iside = 0; iside != el[iele]->side.size(); iside++) {
      for (int i = 0; i != el[iele]->u.size(); i++) {
        result = result && (bool)isfinite(el[iele]->side[iside]->u[i]);
      }
    }
  }
#endif
  return result;
}

/// Fill the Field's element storage with a Scalar
inline void Field::fill(const Scalar x) {
  for (LocalSize e=0; e<ne; e++) el[e]->fill(x);
}

/// Fill the Field element storage with a vector.  Lengths must be compatible
inline void Field::fill(const dVector &x) {
#ifdef DGM_CONTIGUOUS
  elmt_data = x;
#else
  LocalSize i = 0;
  dVector px;
  for (LocalSize e=0; e<ne; e++) {
    px.alias( x, i, el[e]->qtot );
    el[e]->fill(px);
    i += el[e]->qtot;
  }
#endif
}

/// Extract the Field element storage to a vector
inline void Field::extract(dVector &x) const {
#ifdef DGM_CONTIGUOUS
  x = elmt_data;
#else
  LocalSize i = 0;
  dVector px;
  for (LocalSize e=0; e<ne; e++) {
    px.alias( x, i, el[e]->qtot );
    el[e]->extract(px);
    i += el[e]->qtot;
  }
#endif
}

/// Transform from physical space to polynomial space
inline void Field::forward_transform() {
  for (LocalSize e=0; e<ne; e++) el[e]->forward_transform();
}

/// Transform from polynomial to physical space
inline void Field::backward_transform() {
  for (LocalSize e=0; e<ne; e++) el[e]->backward_transform();
}

/// Project the field to the polynomial space
inline void Field::project() {
#ifdef DGM_USE_ELEMENT_BLOCKS
  vector<ElementBlock*>::iterator it = eb.begin();
  vector<ElementBlock*>::iterator end = eb.end();
  for (; it != end; ++it) {
    (*it)->project();
  }
#else
  for (LocalSize e=0; e<ne; e++) el[e]->project();
#endif
}

/// Project one Field to another Field
inline void Field::project(Field *F) const {
  for (LocalSize e=0; e<ne; e++) el[e]->forward_transform(F->el[e]);
  F->backward_transform();
}

/// Project one Field to another Field
inline void Field::project(Field::Ptr F) const {
  project(F.get());
}

/// Project one Field to another Field using Mass from another Field
inline void Field::mass_project(Field *M, Field *F) const {
  for (LocalSize e=0; e<ne; e++) el[e]->forward_transform(M->el[e], F->el[e]);
  F->backward_transform();
}

/// Interpolate the Field's element storage to a uniform mesh
inline void Field::interpolate_to_uniform() {
  for (LocalSize e=0; e<ne; e++) {
    el[e]->forward_transform();
    el[e]->interpolate_to_uniform();
  }
}

/// Fill Element Sides (inter-element skeleton) using Element data
inline void Field::fill_sides() {
  for (LocalSize e=0; e<ne; e++)
    el[e]->fill_sides(el[e]->u);
}

/// Fill Element Sides (inter-element skeleton) using Element data
inline void Field::fill_sides_of_ghost_elements() {
  using std::map;
#ifdef DGM_USE_GENERAL_GHOSTING
  if (not GhostElementMap().empty()) {
    for (map<int,Element*>::const_iterator iter = GhostElementMap().begin();
        iter != GhostElementMap().end(); iter++) {
      Element *const ele = iter->second;
      assert(ele != NULL);
      for (LocalSize iside=0; iside<ele->nSides(); iside++) {
        Side *s = ele->side[iside];
        if (s->u.size() != (LocalSize)s->qtot())
          throw DGM::exception("Sides do not match in size");
      }
      assert(ele->state == Element::Physical);
      // shouldn't above state check also happen for normal elements?
      ele->fill_sides(ele->u);
    }
  }
#endif
}

/// Fill Element Sides (inter-element skeleton) with a Scalar
inline void Field::fill_sides(const Scalar u) {
  for (LocalSize e=0; e<ne; e++)
    el[e]->fill_sides(u);
}

/// Fill BC sides with element data
inline void Field::fill_bc_sides() {
  for (LocalSize n=0; n<nbc; ++n) bc[n]->B->u = bc[n]->S->u;
}

/// Fill BC sides with element data
inline void Field::fill_bc_sides(const Scalar x) {
  for (LocalSize n=0; n<nbc; ++n) bc[n]->B->u = x;
}

/// Make the solution on each Element constant
inline void Field::make_constant() {
  for (LocalSize e=0; e<ne; e++) el[e]->make_constant();
}

/// Low-pass filter in polynomial space.  Zeros modes for p>Np
inline void Field::low_modes(const Ordinal Np) {
  for (LocalSize e=0; e<ne; e++) el[e]->low_modes(Np);
}
/// Low-pass filter in polynomial space.  Zeros modes for p-Np
/** Filters down to a minimum of min_mode. */
inline void Field::low_modes(const Ordinal Np,
                             const Ordinal min_mode) {
#if 0
  // SSC:  This is what I think it should do
  const int Pmin = numeric_cast<int>(min_mode);
  const int Pinc = numeric_cast<int>(Np);
  for (LocalSize e=0; e<ne; e++) {
    const int Pold = numeric_cast<int>(el[e]->pOrder());
    const int Pnew = max(Pold-Pinc, Pmin);
    el[e]->low_modes(Pnew);
  }
#else
  const Ordinal min_Np = min_mode+Np;
  for (LocalSize e=0; e<ne; e++) {
    const Ordinal p_order = el[e]->pOrder();
    if (p_order <= min_Np) el[e]->low_modes(min_mode);
    else                   el[e]->low_modes(p_order-Np);
  }
#endif
}

/// Low-pass filter in polynomial space
inline void Field::low_modes(const Scalar frac,
                             const Ordinal min_mode) {
  for (LocalSize e=0; e<ne; e++) {
    const Ordinal p_order = el[e]->pOrder();
    const Ordinal p       = numeric_cast<Ordinal>(floor((1.0-frac)*p_order));
    const Ordinal Np      = p<min_mode ? min_mode : p;
    el[e]->low_modes(Np);
  }
}

/// Low-pass filter in polynomial space
inline void Field::low_modes(const std::map<Size,Ordinal> &orders){
  for (LocalSize e=0; e<ne; e++) {
    const std::map<Size,Ordinal>::const_iterator Np=orders.find(el[e]->gid());
    if (orders.end() != Np) el[e]->low_modes(Np->second);
  }
}

/// High-pass filter that only zeros the constant mode
inline void Field::kill_constant() {
  for (LocalSize e=0; e<ne; e++) el[e]->kill_constant();
}

/// Low-pass filter that zeros modes from p-p_inc and above
inline void Field::coarse_scales(const int p_inc) {
  for (LocalSize e=0; e<ne; e++) el[e]->coarse_scales(p_inc);
}

/// High-pass filter that zeros modes from 0 to p-p_inc
inline void Field::fine_scales(const int p_inc) {
  for (LocalSize e=0; e<ne; e++) el[e]->fine_scales(p_inc);
}

/// Apply exponential filter in transform space
inline void Field::exp_filter(const Scalar eta, const Scalar s) {
  for (LocalSize e=0; e<ne; e++) el[e]->exp_filter(eta,s);
}

/// Bound the solution on each element and does not include sides.
inline void Field::bound(const Scalar low, const Scalar high) {
  for (LocalSize e=0; e<ne; e++) {
    Element *E = el[e];
    E->bound(low,high);
  }
}

/// Compute maximum absolute value over element
inline void Field::relative_max_error(const Field& f, Scalar& Linf,
  Scalar& L2, Scalar& H1) const
{
  using std::max;
  assert( el.size() == f.el.size() );
  // compute maximum absolute value of each element
  Scalar lresult=0, max_rel=0;
  for (LocalSize e=0; e<ne; ++e) {
    lresult = max(el[e]->u.MaxAbs(),lresult);
    lresult = max(f.el[e]->u.MaxAbs(),lresult);
#ifdef DGM_FIELD_MINMAX_INCLUDE_SIDES
    // now do the inter-element boundary
    // Assumes the element and side parameters are synchronized.
    const Element *E = el[e];
    for (SideLoop S(E); !S.end(); ++S) {
      if (S.master_side()) {
        lresult = max(S.side(E)->u.MaxAbs(),lresult);
        lresult = max(S.link(E)->u.MaxAbs(),lresult);
      }
    }
    // now for the other Field
    E = f.el[e];
    for (SideLoop S(E); !S.end(); ++S) {
      if (S.master_side()) {
        lresult = max(S.side(E)->u.MaxAbs(),lresult);
        lresult = max(S.link(E)->u.MaxAbs(),lresult);
      }
    }
#endif
    for (Ordinal i=0; i<el[e]->u.size(); ++i) {
      L2 = max(L2, (el[e]->u[i] - f.el[e]->u[i]) / lresult);
    }
  }
  comm->MaxAll( &L2, &max_rel, 1 );
  L2 = max_rel;
}

/// Compute the minimum value for the Elements in this Field
/** \pre You must make sure that sides are filled before calling
    \todo This should really call an Element::min() method that would make
    sure that the element is in physical space. */
inline Scalar Field::min() const {
  Scalar lresult = ne ? el[0]->u.Min() : std::numeric_limits<Scalar>::max();
  Scalar result=0;
  for (LocalSize e=1; e<ne; e++) lresult = std::min(el[e]->u.Min(),lresult);
#ifdef DGM_FIELD_MINMAX_INCLUDE_SIDES
  // now do the inter-element boundary
  // Assumes the element and side parameters are synchronized.
  for (LocalSize e=0; e<ne; ++e) {
    const Element *E = el[e];
    for (SideLoop S(E); !S.end(); ++S) {
      if (S.master_side()) {
        lresult = std::min(S.side(E)->u.Min(),lresult);
        lresult = std::min(S.link(E)->u.Min(),lresult);
      }
    }
  }
#endif
  comm->MinAll( &lresult, &result, 1 );
  return result;
}

/// Compute the minimum side value for the Elements in this Field
/** \pre You must make sure that sides are filled before calling
    \todo This should really call an Element::min() method that would make
    sure that the element is in physical space. */
inline Scalar Field::minSide() const {
  Scalar lresult = std::numeric_limits<Scalar>::max();
  Scalar result=0;
  for (LocalSize e=0; e<ne; ++e) {
    const Element *E = el[e];
    for (SideLoop S(E); !S.end(); ++S) {
      if (S.master_side()) {
        lresult = std::min(S.side(E)->u.Min(),lresult);
        lresult = std::min(S.link(E)->u.Min(),lresult);
      }
    }
  }
  comm->MinAll( &lresult, &result, 1 );
  return result;
}

/// Possibly combine with min()
inline Scalar Field::min(GlobalSize &elem) const {
  using std::min_element;
  using std::vector;
  GlobalSize lelmt = ne ? el[0]->gid() : 0;
  Scalar lresult = ne ? el[0]->u.Min() : std::numeric_limits<Scalar>::max();
  for (LocalSize e=1; e<ne; ++e)
    if (el[e]->u.Min() < lresult) {
      lresult = el[e]->u.Min();
      lelmt = el[e]->gid();
    }
  // determine rank with minimum result from this rank broadcast
  // corresponding element gid
  vector<Scalar> results(comm->NumProc());
  comm->GatherAll( &lresult, &results[0], 1 );
  vector<Scalar>::iterator it = min_element(results.begin(), results.end());
  const int rank = numeric_cast<int>(it - results.begin());
  comm->Broadcast( &lelmt, 1, rank);
  elem = lelmt;
  return *it;
}

/// Compute the maximum value for the Elements in this Field
/** \pre You must make sure that sides are filled before calling
    \todo This should really call an Element::max() method that would make
    sure that the element is in physical space. */
inline Scalar Field::max() const {
  Scalar lresult = ne ? el[0]->u.Max() : -std::numeric_limits<Scalar>::max();
  Scalar result=0;
  for (LocalSize e=1; e<ne; e++) lresult = std::max(el[e]->u.Max(),lresult);
#ifdef DGM_FIELD_MINMAX_INCLUDE_SIDES
  // now do the inter-element boundary
  // Assumes the element and side parameters are synchronized.
  for (LocalSize e=0; e<ne; ++e) {
    const Element *E = el[e];
    for (SideLoop S(E); !S.end(); ++S) {
      if (S.master_side()) {
        lresult = std::max(S.side(E)->u.Max(),lresult);
        lresult = std::max(S.link(E)->u.Max(),lresult);
      }
    }
  }
#endif

  comm->MaxAll( &lresult, &result, 1 );
  return result;
}

/// Compute the maximum side value for the Elements in this Field
/** \pre You must make sure that sides are filled before calling
    \todo This should really call an Element::max() method that would make
    sure that the element is in physical space. */
inline Scalar Field::maxSide() const {
  Scalar lresult = -std::numeric_limits<Scalar>::max();
  Scalar result=0;
  for (LocalSize e=0; e<ne; ++e) {
    const Element *E = el[e];
    for (SideLoop S(E); !S.end(); ++S) {
      if (S.master_side()) {
        lresult = std::max(S.side(E)->u.Max(),lresult);
        lresult = std::max(S.link(E)->u.Max(),lresult);
      }
    }
  }

  comm->MaxAll( &lresult, &result, 1 );
  return result;
}

/// Possibly combine with max()
inline Scalar Field::max(GlobalSize &elem) const {
  using std::max_element;
  using std::vector;
  GlobalSize lelmt = ne ? el[0]->gid() : 0;
  Scalar lresult = ne ? el[0]->u.Max() : -std::numeric_limits<Scalar>::max();
  for (LocalSize e=1; e<ne; ++e)
    if (lresult < el[e]->u.Max()) {
      lresult = el[e]->u.Max();
      lelmt = el[e]->gid();
    }
  // determine rank with minimum result from this rank broadcast
  // corresponding element gid
  vector<Scalar> results(comm->NumProc());
  comm->GatherAll( &lresult, &results[0], 1 );
  vector<Scalar>::iterator it = max_element(results.begin(), results.end());
  const int rank = numeric_cast<int>(it - results.begin());
  comm->Broadcast( &lelmt, 1, rank);
  elem = lelmt;
  return *it;
}

/// Fill elements with random solution in polynomial space
inline void Field::random() {
  for (LocalSize e=0; e<ne; e++) el[e]->random();
}

/// Sets the Element::State for each element in this Field
inline void Field::set_state(const Element::States s) {
  for (LocalSize e=0; e<ne; e++) el[e]->state=s;
}

/// Outputs the Boundary stats for Field
inline void Field::write_side_stats(const LocalSize index) const {
  string fname(name);
  if (index!=undefined<LocalSize>()) {
    char buf[128];
    sprintf(buf,".%lld",(long long)index);
    fname = name + buf;
  }
  bndry_stats->write(fname);
}

/// Return the maximum side to interior Jacobian ratio
inline Scalar Field::get_max_sigma() const {
  Scalar sigma=0.0;
  for (LocalSize e=0; e<ne; e++) sigma = std::max( sigma, el[e]->sigma() );
#ifdef DGM_PARALLEL
  const Scalar localsigma = sigma;
  comm->MaxAll( &localsigma, &sigma, 1 );
#endif
  return sigma;
}

/// Error out if you try to use the copy-constructor
inline Field::Field(Field &F) : BlockSize(F.BlockSize) {
  DGM::Comm::World->cerr()<<"Field::Field(Field&) constructor not implemented"
      <<std::endl;
  DGM::Comm::World->exit(DGM::FAILURE);
}

//=============================================================================
//                       F i e l d   H e l p e r s
//=============================================================================

/// Project Field w.r.t. the basis and transform to physical space
void project(Field *F) {
  for (Field::LocalSize e=0; e<F->ne; e++) F->el[e]->project();
}

/// Blocked version of project
/** \todo Fill in blocking */
void block_project(Field *F) {
  for (Field::LocalSize e=0; e<F->ne; e++) F->el[e]->project();
}

/// Project Field w.r.t. basis and transform to physical using different mass
void mass_project(Field *M, Field *F) {
  using std::vector;
#ifdef DGM_USE_ELEMENT_BLOCKS
  vector<ElementBlock*>::const_iterator j=M->eb.begin();
  vector<ElementBlock*>::iterator       i=F->eb.begin();
  for (; F->eb.end()!=i && M->eb.end()!=j; ++i, ++j) {
    (*i)->forward_transform(*j, *i);
    (*i)->backward_transform();
  }
#else
  for (Field::LocalSize e=0; e<F->ne; e++) {
    F->el[e]->forward_transform(M->el[e], F->el[e]);
    F->el[e]->backward_transform();
  }
#endif
}

/// Apply filter in transform space
void filter_project(Field *F, std::vector<Filter*> &filter) {
  // cout<<"Field::filter_project()"<<endl;
  for (Field::LocalSize e=0; e<F->ne; e++) {
    F->el[e]->forward_transform();
    F->el[e]->filter(filter[e]->kernel);
    F->el[e]->backward_transform();
  }
}

/// Copy the sides from U to F
inline void copy_sides(const Field *U, Field *F) {
  assert( U->ne == F->ne );
  for (Field::LocalSize e=0; e<F->ne; e++)
    U->el[e]->copy_sides( F->el[e] );
}

//============================================================================
//                     Basic linear algebra on Fields
//============================================================================

/// Add two Fields
inline void add( const Field *X, Field *Y) {
  using std::endl;
#ifdef DGM_CONTIGUOUS
  if (X->elmt_data.size() != Y->elmt_data.size()) {
    DGM::Comm::World->cerr() << "X " <<  X->elmt_data.size() << endl;
    DGM::Comm::World->cerr() << "Y " <<  Y->elmt_data.size() << endl;
    DGM::Comm::World->cerr() << "Attempted to add incompatible Fields" << endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  dvadd( X->elmt_data, Y->elmt_data );
#else
  for (Field::LocalSize e=0; e<X->ne; e++) {
    Element *x = X->el[e];
    Element *y = Y->el[e];
    dvadd( x->u, y->u );
  }
#endif
}

/// Subtract two Fields
inline void subtract( const Field *X, Field *Y) {
#ifdef DGM_CONTIGUOUS
  for (DGM::Ordinal i=0; i<Y->elmt_data.size(); ++i)
    Y->elmt_data[i] -= X->elmt_data[i];
#else
  for (Field::LocalSize e=0; e<Y->ne; e++) {
    Element *x = X->el[e];
    Element *y = Y->el[e];
    for (DGM::Ordinal i=0; i<y->u.size(); ++i) y->u[i] -= x->u[i];
  }
#endif
}

/// Add scalar to a Field
inline void add( const Scalar a, Field *Y) {
#ifdef DGM_CONTIGUOUS
  for (DGM::Ordinal i=0; i<Y->elmt_data.size(); ++i) Y->elmt_data[i] += a;
#else
  for (Field::LocalSize e=0; e<Y->ne; e++) {
    Element *y = Y->el[e];
    for (DGM::Ordinal i=0; i<y->u.size(); ++i) y->u[i] += a;
  }
#endif
}

/// Subtract scalar from a Field
inline void subtract( const Scalar a, Field *Y) {
#ifdef DGM_CONTIGUOUS
  for (DGM::Ordinal i=0; i<Y->elmt_data.size(); ++i) Y->elmt_data[i] -= a;
#else
  for (Field::LocalSize e=0; e<Y->ne; e++) {
    Element *y = Y->el[e];
    for (DGM::Ordinal i=0; i<y->u.size(); ++i) y->u[i] -= a;
  }
#endif
}

/// Add dVector to a Field
inline void add( const dVector &a, Field *Y) {
  assert( a.size() == Y->qtot() );
#ifdef DGM_CONTIGUOUS
  for (DGM::Ordinal i=0; i<Y->elmt_data.size(); ++i) Y->elmt_data[i] += a[i];
#else
  DGM::Ordinal j=0;
  for (Field::LocalSize e=0; e<Y->ne; e++) {
    Element *y = Y->el[e];
    for (DGM::Ordinal i=0; i<y->u.size(); ++i) y->u[i] += a[j++];
  }
#endif
}

/// Subtract dVector from a Field
inline void subtract( const dVector &a, Field *Y) {
  assert( a.size() == Y->qtot() );
#ifdef DGM_CONTIGUOUS
  for (DGM::Ordinal i=0; i<Y->elmt_data.size(); ++i) Y->elmt_data[i] -= a[i];
#else
  DGM::Ordinal j=0;
  for (Field::LocalSize e=0; e<Y->ne; e++) {
    Element *y = Y->el[e];
    for (DGM::Ordinal i=0; i<y->u.size(); ++i) y->u[i] -= a[j++];
  }
#endif
}

/// Perform axpy operation on two Fields \f$Y = a X + Y\f$
inline void axpy( const Scalar a, const Field *X, Field *Y ) {
#ifdef DGM_CONTIGUOUS
  if (X->elmt_data.size() != Y->elmt_data.size()) {
    DGM::Comm::World->cerr() << "Attempted to axpy incompatible Fields"
        << std::endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  daxpy( a, X->elmt_data, Y->elmt_data );
#else
  for (Field::LocalSize e=0; e<X->ne; e++)
    daxpy( a, X->el[e]->u, Y->el[e]->u );
#endif
}

/// Perform a "vector" axpy on two Fields \f$Y = a X + Y\f$
/** \pre Vectors \f$a\f$ and \f$X\f$ must be conformal. */
inline void axpy( const dVector &a, const Field *X, Field *Y ) {
  if (a.size() != (DGM::Ordinal)X->ne) {
    DGM::Comm::World->cerr() << "Incompatible element scaling factor"
                             << std::endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  for (Field::LocalSize e=0; e<X->ne; e++)
    daxpy( a[e], X->el[e]->u, Y->el[e]->u );
}

/// Perform an axpy on Fields \f$Z = a X + Y\f$
inline void axpy( const Scalar a, const Field *X, const Field *Y, Field *Z ) {
#ifdef DGM_CONTIGUOUS
  if (X->elmt_data.size() != Y->elmt_data.size() ||
      X->elmt_data.size() != Z->elmt_data.size()) {
    DGM::Comm::World->cerr() << "Attempted to axpy incompatible Fields"
        << std::endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  daxpy( a, X->elmt_data, Y->elmt_data, Z->elmt_data );
#else
  for (Field::LocalSize e=0; e<X->ne; e++)
    for (DGM::Ordinal i=0; i<X->el[e]->qtot; i++)
      Z->el[e]->u[i] = a * X->el[e]->u[i] + Y->el[e]->u[i];
#endif
}

/// Perform a "vector" axpy on Fields \f$Z = a X + Y\f$
/** \pre Vectors \f$a\f$ and \f$X\f$ must be conformal. */
inline void axpy( const dVector &a, const Field *X, const Field *Y, Field *Z) {
  if (a.size() != (DGM::Ordinal)X->ne) {
    DGM::Comm::World->cerr() << "Incompatible element scaling factor"
                             << std::endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  for (Field::LocalSize e=0; e<X->ne; e++)
    for (DGM::Ordinal i=0; i<X->el[e]->qtot; i++)
      Z->el[e]->u[i] = a[e] * X->el[e]->u[i] + Y->el[e]->u[i];
}

/// Perform an axpby on Fields \f$Z = a X + b Y\f$
inline void axpby( const Scalar a, const Field *X, const Scalar b,
                   const Field *Y, Field *Z ) {
#ifdef DGM_CONTIGUOUS
  if (X->elmt_data.size() != Y->elmt_data.size() ||
      X->elmt_data.size() != Z->elmt_data.size()) {
    DGM::Comm::World->cerr() << "Attempted to axpby incompatible Fields"
        << std::endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  multiply( b, Y->elmt_data, Z->elmt_data );
  daxpy( a, X->elmt_data, Z->elmt_data );
#else
  for (Field::LocalSize e=0; e<X->ne; e++)
    for (DGM::Ordinal i=0; i<X->el[e]->qtot; i++)
      Z->el[e]->u[i] = a * X->el[e]->u[i] + b * Y->el[e]->u[i];
#endif
}

/// Scale by a constant over the Field
inline void scale( const Scalar a, Field *X ) {
#ifdef DGM_CONTIGUOUS
  scale( a, X->elmt_data );
#else
  for (Field::LocalSize e=0; e<X->ne; e++) scale( a, X->el[e]->u );
#endif
}

/// Scale by a constant on each element
inline void scale( const dVector &a, Field *X ) {
  if ( a.size() != (DGM::Ordinal)X->ne )
    DGM::Comm::World->error("Scale with incorrectly sized element vector");
  for (Field::LocalSize e=0; e<X->ne; e++) scale( a[e], X->el[e]->u );
}

/// Scale by a Field
inline void scale( const Field *A, Field *X ) {
  //#ifdef DGM_CONTIGUOUS
  //  if ( A->elmt_data.size() != X->elmt_data.size() )
  //    DGM::Comm::World->error("Scale with incompatible Fields");
  //  dvmul( A->elmt_data, X->elmt_data );
  //#else
  for (Field::LocalSize e=0; e<X->ne; e++) dvmul( A->el[e]->u, X->el[e]->u );
  //#endif
}

/// Compute the Euclidean dot product
inline Scalar dot( const Field *X, const Field *Y ) {
#ifdef DGM_CONTIGUOUS
  if (X->elmt_data.size() != Y->elmt_data.size()) {
    DGM::Comm::World->cerr() << "Attempted to dot incompatible Fields"
                             << std::endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  return dot( X->elmt_data, Y->elmt_data );
#else
  Scalar result = 0;
  for (Field::LocalSize e=0; e<X->ne; e++)
    result += dot( X->el[e]->u, Y->el[e]->u );
  return result;
#endif
}

/// Multiply two fields
inline void multiply( const Field *X, Field *Y ) {
#ifdef DGM_CONTIGUOUS
  if (X->elmt_data.size() != Y->elmt_data.size()) {
    DGM::Comm::World->cerr() << "Attempted to multiply incompatible Fields"

                             << std::endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  multiply( X->elmt_data, Y->elmt_data );
#else
  for (Field::LocalSize e=0; e<X->ne; ++e)
    multiply( X->el[e]->u, Y->el[e]->u );
#endif
}

/// Take the reciprocal of a Field
inline void invert( Field *X ) {
#ifdef DGM_CONTIGUOUS
  invert(X->elmt_data);
#else
  for (Field::LocalSize e=0; e<X->ne; ++e)
    invert(X->el[e]->u);
#endif
}

/// Take the square root of a Field
inline void Sqrt( Field *X ) {
#ifdef DGM_CONTIGUOUS
  X->elmt_data.Sqrt();
#else
  for (Field::LocalSize e=0; e<X->ne; ++e)
    X->el[e]->u.Sqrt();
#endif
}

/// Copy one Field into another
inline void copy( const Field *X, Field *Y, const bool check_names) {
  if (check_names) {
#if 1
    if (X->get_name() != Y->get_name()) {
      DGM::Comm::World->cerr() << "Attempted to copy incompatible Fields with "
                               << "X.get_name() = " << X->get_name() << ", "
                               << "Y.get_name() = " << Y->get_name()
                               << std::endl;
      DGM::Comm::World->exit(DGM::FAILURE);
    }
#else
    if (X->verb && (X->get_name() != Y->get_name()))
      DGM::Comm::World->cout() << "WARNING -- Fields have incompatible names\n"
                               << "X.get_name() = " << X->get_name() << ", \n"
                               << "Y.get_name() = " << Y->get_name() << ".\n"
                               << "Setting to " << X->get_name() << std::endl;
    Y->set_name(X->get_name());
#endif
  }
#ifdef DGM_CONTIGUOUS
  if (X->elmt_data.size() != Y->elmt_data.size()) {
    DGM::Comm::World->cerr() << "Attempted to copy incompatible Fields with "
                             << "X.size() = " << X->elmt_data.size() << ", "
                             << "Y.size() = " << Y->elmt_data.size()
                             << std::endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
#if 0
  Y->elmt_data = X->elmt_data;
#else
  copy(X->elmt_data,Y->elmt_data);
#endif
#else
  for (Field::LocalSize e=0; e<X->ne; e++) {
    Element *x = X->el[e];
    Element *y = Y->el[e];
    y->u = x->u;
  }
#endif
}

/// Compute the L_2 inner_product for the entire field
/** This version does parallel communication */
inline Scalar Field::L2_inner_product( const Field *X,
                                       const Field *Y,
                                       Scalar *measure ) {
  Scalar L2(0), result(0), elmeas(0), fmeas(0);
  for(Field::LocalSize e=0; e<X->ne; e++) {
    result += X->el[e]->L2_inner_product(Y->el[e], &elmeas);
    fmeas += elmeas;
  }
  X->comm->SumAll( &result, &L2, 1);
  if (measure) X->comm->SumAll( &fmeas, measure, 1);
  return L2;
}

/// Compute the L_2 inner_product on the local partition
/** This is needed in the Ctrl and Obs classes because they do the parallel
    communication at a higher level */
inline Scalar Field::local_L2_inner_product( const Field *X,
                                             const Field *Y,
                                             Scalar *measure ) {
  Scalar result(0);
  for(Field::LocalSize e=0; e<X->ne; e++) {
    result += X->el[e]->L2_inner_product(Y->el[e], measure);
  }
  return result;
}

/// Shared pointer version just call raw pointer implementation
inline Scalar Field::L2_inner_product( const Field::Ptr X,
                                       const Field::Ptr Y,
                                       Scalar *measure ) {
  return Field::L2_inner_product( X.get(), Y.get(), measure);
}

/// Shared pointer version just calls raw pointer implementation
inline Scalar Field::local_L2_inner_product( const Field::Ptr X,
                                             const Field::Ptr Y,
                                             Scalar *measure ) {
  return Field::local_L2_inner_product( X.get(), Y.get(), measure);
}

} // namespace DGM

#endif  // DGM_FIELD_HPP
