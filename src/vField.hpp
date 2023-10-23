#ifndef DGM_VFIELD_HPP
#define DGM_VFIELD_HPP

/** \file vField.hpp
    \brief Provides a vector of Field objects
    \author Scott Collis

    Think of this as a container of Fields.  It is NOT a Field of vectors.
*/

// Trilinos includes
#ifdef DGM_USE_EPETRA
#ifdef DGM_PARALLEL
#include "Epetra_MpiComm.h"
#else
#include "Epetra_SerialComm.h"
#endif
#include "Epetra_Map.h"
#include "Epetra_BlockMap.h"
#include "Epetra_Vector.h"
#include "Epetra_CrsGraph.h"
#include "Epetra_LinearProblem.h"
#include "AztecOO.h"
#include "Amesos.h"
#include "Amesos_BaseSolver.h"
#include "Amesos_ConfigDefs.h"
#include "EpetraExt_OperatorOut.h"
#include "EpetraExt_RowMatrixOut.h"
#include "EpetraExt_VectorOut.h"
#include "EpetraExt_MultiVectorOut.h"
#include "EpetraExt_CrsMatrixIn.h"
#include <EpetraExt_MatrixMatrix.h>
#include "Teuchos_RCP.hpp"
#endif

// Boost includes
#ifdef DGM_USE_GENERAL_GHOSTING
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#endif

// DTK includes
#include "DTK.hpp"

// DGM includes
#ifdef DGM_PARALLEL
#include "MpiComm.hpp"
#endif
#include "Field.hpp"
#include "Partition.hpp"

// forward declarations
#ifdef DGM_USE_EPETRA
class Epetra_Comm;
class Epetra_BlockMap;
class Epetra_Vector;
#endif

namespace DGM {

/// A vector of Field
/** There are two ways that you can make a "vector field" class.
    -# a vector of Field
    -# a Field of vectors

    The following vField class uses the first option which gives the
    greatest flexibility, although it may be less efficient in memory
    accesses.  Since this a wrapper class, I can change the representation
    to the first option at a later date if that is desirable.   */
class vField : public DTK::VectorField<Scalar,Field,Ordinal> {

 public:

  typedef Ordinal size_type; ///< size_type for this vector of Fields

 private:

  vector<Field::Ptr> F;      ///< Vector of smart pointers to Fields

  const DGM::Comm::Ptr comm; ///< Communicator for this vField

  mutable Scalar sigma;      ///< Maximum side to interior Jacobian ratio

  string name;               ///< Name of this vField

  bool contiguous;           ///< True if the vField storage is contiguous
  bool use_epetra;           ///< False if too large for Epetra_BlockMap

#ifdef DGM_PARALLEL
  vector<dVector> pcbuf;     ///< Partition side buffer
  vector<dVector> pcsbuf;    ///< Partition send side buffer
#endif

 public:

  /// Domain partition for parallel execution
  /** \note This partition should be the vField partition.  Right now it is the
      partition of the first Field within the vField -- this is bad and
      should be changed. */
  Partition<Size,Ordinal,Scalar>::Ptr partition;

  typedef Size GlobalSize;                    ///< Size type for global storage
  typedef Ordinal LocalSize;                  ///< Size type for local storage

  /// Contiguous storage for element interior data
  dVector elmt_data;
  /// Contiguous storage for side data
  dVector side_data;

#ifdef DGM_USE_EPETRA
  DGM::Shared<Epetra_Comm>::Ptr eComm;           ///< Epetra communicator
  DGM::Shared<Epetra_BlockMap>::Ptr nodal_map;   ///< Map on quadrature points
  DGM::Shared<Epetra_Vector>::Ptr nodal_vec;     ///< Vector on quadrature data
  DGM::Shared<Epetra_BlockMap>::Ptr modal_map;   ///< Modal data map
  DGM::Shared<Epetra_Vector>::Ptr modal_vec;     ///< Vector of modal data
  DGM::Shared<Epetra_Vector>::Ptr nodal_pnt_vec; ///< Nodal vector
 private:
  Teuchos::RCP<Epetra_Map> rdofmap;          ///< non-overlapping row DOF map
  Teuchos::RCP<Epetra_Map> nodal_pnt_map;    ///< Map on quadrature points

  map<int,vector<int> > rdof_per_ele;        ///< global DOF id per global eid
  map<int,vector<int> > cdof_per_ele;        ///< global DOF id per global eid

  /// global DOF id per field and global element id (own and ghost elements)
  map<int,vector< vector<int> > > dof_per_fieldele;

  /// \name Epetra support methods
  //@{
  /// give read only access to dof_per_fieldele
  const map<int,vector< vector<int> > >& DofPerFieldEle() const {
    return dof_per_fieldele;
  }

  /// give read only access to dof_per_fieldele
  const vector<int>& DofPerFieldEle(const int &elegid,
                                    const int &ifield) const{
    return DofPerFieldEle().find(elegid)->second[ifield];
  }

 public:
  /// give read only access to row dof map
  const Epetra_Map* RowDofMapPtr() const { return &(*rdofmap); }

  /// select adjacent side depending on whether I am master or not
  static const Side* select_adj(const Side * const S) {
    return S->master() ? S->link : S->base;
  }

  void pack(Epetra_Vector& x) const;
  void unpack(const Epetra_Vector& x);

  /// returns list of DOF GIDs for row element
  const vector<int>& get_row_elem_dofs(const int egid) const;
  /// returns list of DOF GIDs for col element
  const vector<int>& get_col_elem_dofs(const int egid) const;

  /// Helper function taken from Epetra_VbrMatrix.
  /**  Shouldn't be needed once Epetra supports an Epetra_BlockOperator
    *  interface.
    *  @return point map
    */
  static Teuchos::RCP<Epetra_Map> BlockMap2PointMap(
      const Epetra_BlockMap &BlockMap ///< source map
      );
  //@}

  /// \name Element ghosting methods
  //@{
 private:
  /// create initial element row and col maps, fill ghost element array
  void init_redistribution_framework(const Epetra_Comm& Comm);
  /// ghost one layer of elements around my own row elements
  void ghost_aura();
  /// Gather DOFs of all (owned and ghost) elements
  void gather_column_dofs();
 public:
  /// ghost one layer of elements and set up appropriate dof maps
  void ghost(const string& root="root", const Scalar z_offset = 1.0);
  /// transfer data from row to column layout (experimental)
  void share_ghost_element_data() const;
  //@}
#endif // DGM_USE_EPETRA

  /// \name Constructors and Destructor
  //@{
  vField( const DGM::Comm::Ptr, string="vField" );
  ~vField();
  vField( const vField & );
  //@}

  ///\name Accessors and operators
  //@{

  /// Indexes into the vField to return the ith Field component
  Field * operator[](size_type i) { return F[i].get(); }

  /// Indexes into the vField to return the ith Field component
  const Field * operator[](size_type i) const { return F[i].get(); }

  /// Sets two vField to be equal (shallow copy)
  /** This just sets the Field pointers to be equal. No new memory is
      allocated. Not currently updated to work with Epetra datastructures
      so it generates an error under those conditions. */
  vField & operator= (const vField &In) {
    //cerr<<"vField& operator= (const vField &In)"<<endl;
    F.resize(In.size());
    for (size_t i=0; i<F.size(); i++) F[i] = In.F[i]; // equate smart ptrs
    partition = In.partition;
    const_cast<DGM::Comm::Ptr&>(comm) = In.comm;
    sigma = In.sigma;
    //name = In.name;
    contiguous = In.contiguous;
    partition = In.partition;
    if (contiguous) {
      elmt_data.alias(In.elmt_data);
      side_data.alias(In.side_data);
#ifdef DGM_USE_EPETRA
      eComm = In.eComm;
      nodal_map = In.nodal_map;
      nodal_vec = In.nodal_vec;
      modal_map = In.modal_map;
      modal_vec = In.modal_vec;
#endif
#ifdef DGM_PARALLEL
      pcbuf.resize(In.pcbuf.size());
      pcsbuf.resize(In.pcsbuf.size());
      for (size_t n=0; n<In.pcbuf.size(); n++) {
        pcbuf[n].alias( In.pcbuf[n] );
        pcsbuf[n].alias( In.pcsbuf[n] );
      }
#endif
    }
    return *this;
  }

  /// Sets two vField to be equal (hard copy)
  /** \note Added an error if clone is used with Trilinos::Epetra. */
  void clone(const vField &In) {
    for (size_type i=0; i<In.size(); i++)
      F.push_back(Field::Ptr(new Field(In.F[i].get())));
    partition = Partition<Size,Ordinal,Scalar>::Ptr
      (new Partition<Size,Ordinal,Scalar>(In.partition.get()));
    const_cast<DGM::Comm::Ptr&>(comm) = In.comm;
    sigma = In.sigma;
    name = In.name;
    if (!contiguous && In.contiguous) reset_storage();
    contiguous = In.contiguous;
    if (contiguous) {
      elmt_data.Copy(In.elmt_data);
      side_data.Copy(In.side_data);
#ifdef DGM_USE_EPETRA
      //DGM::Comm::World->error("Trilinos Epetra code in the clone method"
      //                        " of the vField class must be fixed");
      eComm = In.eComm;
      nodal_map = In.nodal_map;
      nodal_vec = In.nodal_vec;
      modal_map = In.modal_map;
      modal_vec = In.modal_vec;
#endif
#ifdef DGM_PARALLEL
      pcbuf.resize(In.pcbuf.size());
      pcsbuf.resize(In.pcsbuf.size());
      for (size_t n=0; n<In.pcbuf.size(); n++) {
        pcbuf[n].Copy( In.pcbuf[n] );
        pcsbuf[n].Copy( In.pcsbuf[n] );
      }
#endif
    }
  }

  /// Push a new Field pointer onto the end of the vField
  void push_back( Field *U ) {
    //cout << "vField::push_back(Field *)"<<endl;
    F.push_back(Field::Ptr(U));
    if (partition.get())
      if (partition != U->partition) {
        DGM::Comm::World->cerr()<<"Illegal partition in vField::push_back():"
                                <<" partition = " << partition.get()
                                <<" U->partition = " << U->partition.get()
                                << endl;
        DGM::Comm::World->exit();
      }
    partition = U->partition;
    if (!comm.get()) {
      cout<<"Undefined vField communicator"<<endl;
      DGM::Comm::World->error("Undefined vField communicator");
    }
    // vField inherits the communicator of the first Field that fills it
    // note that this requires the const_cast as, in general, the vField::comm
    // should be const.  If the pointer is already set and they match, then
    // no reason to change things.
    if ( F.size()==1 && comm.get() != U->get_comm().get() ) {
      const_cast<DGM::Comm::Ptr&>(comm) = U->get_comm();
#ifdef DGM_VFIELD_VERBOSE
      cout <<"  comm = " << comm.get() << endl
        <<"  U->comm = " << U->get_comm().get() << endl
        <<"  DGM::Comm::World = " << DGM::Comm::World.get() << endl;
#endif
    }
    // If the pointer set and this is not the first Field, then it is an error
    if (comm.get() != U->get_comm().get()) {
      DGM::Comm::World->cerr()
        <<"Illegal communicator in vField::push_back():"<<endl
        <<"  comm = " << comm.get() << endl
        <<"  U->comm = " << U->get_comm().get() << endl
        <<"  DGM::Comm::World = " << DGM::Comm::World.get() << endl;
      DGM::Comm::World->exit();
    }
  }

  /// Allows you to change the vField name
  void set_name(const string s) { name = s; }

  /// Accessor for the vField name
  string get_name() const { return name; }

  /// Set the names for the individual Fields
  void set_Field_names( const vector<string> field_names ) {
    assert(size()==static_cast<size_type>(field_names.size()));
    for (size_type i=0; i<size(); i++) F[i]->set_name( field_names[i] );
  }

  /// Accessor for the Field names
  vector<string> get_Field_names() const {
    vector<string> field_names(size());
    for (size_type i=0; i<size(); i++) field_names[i]=F[i]->get_name();
    return field_names;
  }

  /// the number of Fields in this vField
  size_type size() const { return numeric_cast<size_type>(F.size()); }

  /// Total number of quadrature points (for all Fields)
  LocalSize qtot() const {
    uint64_t result=0;
    for (size_type i=0; i<size(); i++) result += F[i]->qtot();
    if (result > numeric_cast<uint64_t>(numeric_limits<LocalSize>::max())) {
      comm->error("vField ("+name+") qtot exceeds addressable index space.\n"
                  "You will need to compile with a larger type for Ordinal.");
    }
    return numeric_cast<LocalSize>(result);
  }

  /// Total number of modes for all Fields
  LocalSize nmodes() const {
    uint64_t result=0;
    for (size_type i=0; i<size(); i++) result += F[i]->ndof();
    if (result > numeric_cast<uint64_t>(numeric_limits<LocalSize>::max())) {
      comm->error("vField ("+name+") nmodes exceeds addressable index space.\n"
                  "You will need to compile with a larger type for Ordinal.");
    }
    return numeric_cast<LocalSize>(result);
  }

  /// Total number of degrees of freedom (modes for all Fields)
  /** \note This should work for both Modal and Nodal bases */
  LocalSize ndof() const {
    return nmodes(); // currently only support modal bases
  }

  /// Total number of side quadrature points (for all Fields)
  LocalSize sdof() const {
    uint64_t result=0;
    for (size_type i=0; i<size(); i++) result += F[i]->sdof();
    if (result > numeric_cast<uint64_t>(numeric_limits<LocalSize>::max())) {
      comm->error("vField ("+name+") sdof exceeds addressable index space.\n"
                  "You will need to compile with a larger type for Ordinal.");
    }
    return numeric_cast<LocalSize>(result);
  }

  /// Tells you if the vField storage is contiguous in memory
  bool is_contiguous() const { return contiguous; }

  /// Number of space dimensions
  LocalSize nsd() const { return F[0]->nsd(); }

  /// Return the parallel communicator
  const DGM::Comm::Ptr get_comm() const { return comm; }

  /// Returns the maximum element quadrature order for all fields
  LocalSize Qmax() const {
    LocalSize result=0;
    for (size_type i=0; i<size(); ++i) result = max(result,F[i]->Qmax);
    return result;
  }

  /// Returns the maximum element modal order for all fields
  LocalSize Lmax() const {
    LocalSize result=0;
    for (size_type i=0; i<size(); ++i) result = max(result,F[i]->Lmax);
    return result;
  }
  //@}

  /// \name Element methods
  //@{
  inline void abs();
  inline void zero();
  inline void forward_transform();
  inline void backward_transform();
  inline void interpolate_to_uniform();
  inline void make_constant();
  inline void low_modes(const Ordinal);
  inline void low_modes(const Ordinal, const Ordinal);
  inline void low_modes(const Scalar,  const Ordinal);
  inline void low_modes(const std::map<Size,Ordinal> &);
  inline void kill_constant();
  inline void coarse_scales(const int p_inc);
  inline void fine_scales(const int p_inc);
  inline void set_state(const Element::States);
  inline void exp_filter(const Scalar eta, const Scalar s);
  //@}

  /// \name Side methods
  //@{
  inline void fill_sides();
  inline void fill_sides_of_ghost_elements();
  inline void fill_sides(const Scalar);
  inline void fill_sides(const vector<Scalar> &);
  inline void fill_bc_sides();
  inline void fill_bc_sides(const Scalar);
  inline void share_sides();
  void begin_share_sides();
  void end_share_sides() const;
  inline void write_side_stats(const size_type index=
                               undefined<size_type>()) const;
  inline Scalar get_max_sigma() const;
  //@}

  /// \name IO methods
  //@{
  streamoff read (const string &fname, const streamoff offset=0);
  streamoff read (const string &fname, const string &global_size,
                  const string &local_size, const string &scalar_size,
                  const streamoff offset);
  streamoff write(const string &fname, const streamoff offset=0) const;
  //@}

  /// \name Utility methods
  //@{
  void tecplot(const string fname, const string title) const;
  void paraview(const string name, const string title) const;
  void paraview_combined(std::string, std::string) const;
  void paraview_vtu(const string fname, const string title) const;
  void paraview_pvtu(const string fname, const string name,
                     const int Npieces) const;
  void suplot(const string root,const string fname) const;
  void plot3d_x(const string fname) const;
  void plot3d_q(const string fname,
                const Scalar mach=1.0, const Scalar alpha=0.0,
                const Scalar reyn=0.0, const Scalar time=0.0) const;
#ifdef DGM_PARALLEL
  void MPI_plot3d_x(const string fname, const MPI_Offset skip=0) const;
  void MPI_plot3d_x2d(const string fname, const MPI_Offset skip=0) const;
  void MPI_plot3d_q(const string fname,
                    const Scalar mach=1.0, const Scalar alpha=0.0,
                    const Scalar reyn=0.0, const Scalar time=0.0) const;
#endif
  /// Pack the vField to minimal storage
  inline void pack();
  /// Unpack the vField storage
  inline void unpack();

  inline void apply_metric();
  inline void remove_metric();

  /// copy contents (interiors and sides) of one vField to another
  inline void copy(const vField &F);

  /// copy names of one vField to another
  inline void copy_names(const vField &F);

  inline void fill( const dVector & );      ///< fill vField with values
  inline void fill( const Scalar );         ///< fill vField with a Scalar
  inline void fill( const vector<Scalar>&); ///< fill vField with a Scalar
  /// fill vField with given string
  void fill( ifstream &in, const string fname=string(),
             const bool fill_sides=false,
             vField::size_type start=0,
             vField::size_type end=0 );
  inline void random();                     ///< fill vField with random numbers
  inline void extract( dVector & ) const;   ///< extract vField to a vector
  inline void plane_average();

  void reset_storage();              ///< makes vField storage contiguous
  void setup_epetra();               ///< sets up Epetra views if enabled

  inline void project();
  inline void project(vField &) const;
  //@}

  /// \name Norm and error methods
  //@{
  inline void norm() const;
  inline void norm( const vector<string> names ) const;
  inline void norm(dVector &Linf, dVector &L2, dVector &H1) const;
  inline void relative_max_error(const vField& Ut, dVector& Linf,
    dVector& L2, dVector& H1) const;
  inline void min_elements(dVector &min, gVector &elems) const;
  inline void max_elements(dVector &max, gVector &elems) const;
  inline void range() const;
  inline void rangeSide() const;
  //@}

  /// \name Local I/O methods
  //@{
  bool local_exists(const string &) const;
  streamoff local_read(istream &, const bool saved_as_float=false);
  streamoff local_read(const string &, const streamoff=0,
                       const bool saved_as_float=false);
  streamoff local_write(ostream &, const bool save_as_float=false) const;
  streamoff local_write(const string &, const streamoff=0,
                        const bool save_as_float=false) const;

  template <typename fileScalar>
  streamoff compressed_local_read(istream &fs,
                                  const Json::Value &traits);
  template <typename fileScalar>
  streamoff compressed_local_write(ostream &fs,
                                   const Json::Value &traits) const;
  //@}

  /// \name Norm static methods
  //@{
  static inline Scalar L2_inner_product( const vField &, const vField &,
                                         Scalar *measure=0);
  static inline Scalar local_L2_inner_product( const vField &, const vField &,
                                               Scalar *measure=0);
  static inline Scalar local_L2_norm( const vField &, Scalar *measure=0 );
  static inline Scalar L2_norm( const vField &, Scalar *measure=0 );
  //@}

  /// \name Experimental methods
  //@{
  /// Save the serialized vField
  void save(ostream &os) const {
    local_write(os);
  }
  /// Restore the serialized vField
  void restore(istream &is) {
    local_read(is);
  }
  //@}

private:

  /// Implementation for reading a vField templated on datatypes
  template <typename fileGlobal, typename fileLocal, typename fileScalar>
  streamoff read_impl(const string &fname, const streamoff offset);

  /// \name Serialization methods
  //@{
  friend class boost::serialization::access;
  template<typename Archive>
  void serialize(Archive &ar, const unsigned int version) {
    ar & sigma;
    ar & name;
    ar & contiguous;
    // put more stuff here
  }
  //@}

  /// Don't allow copy construction from a pointer
  explicit vField( const vField * ) {
    DGM_UNDEFINED;
  }

  void paraview_vtu_modified(std::string, std::string) const;
  void paraview_vtu_modified_ascii(std::string, std::string) const;
  void paraview_vtu_modified_binary(std::string, std::string) const;

};

//=============================================================================
//                   vField Static member functions
//=============================================================================

/// Compute the local L_2 inner_product of two vFields
inline Scalar vField::local_L2_inner_product(const vField &X,
                                             const vField &Y,
                                             Scalar *measure){
  assert( X.size() == Y.size() );
  Scalar result = 0;
  for (size_type i=0; i<X.size(); i++)
    result += Field::local_L2_inner_product( X[i], Y[i], measure );
  return result;
}

/// Compute the local L_2 norm of a vField
inline Scalar vField::local_L2_norm(const vField &X, Scalar *measure) {
  return local_L2_inner_product( X, X, measure );
}

/// Compute the L_2 inner_product of two vFields
inline Scalar vField::L2_inner_product(const vField &X, const vField &Y,
                                       Scalar *measure) {
  assert( X.size() == Y.size() );
  Scalar result = 0;
  for (size_type i=0; i<X.size(); i++)
    result += Field::L2_inner_product( X[i], Y[i], measure );
  return result;
}

/// Compute the L_2 norm of a vField
inline Scalar vField::L2_norm(const vField &X, Scalar *measure) {
  return L2_inner_product( X, X, measure );
}

/// \name vField helper functions
//@{
inline void project(vField &) ;
inline void filter_project(vField &, vector<Filter*> );
inline void copy_sides(const vField &, vField &);
inline void copy( const vField &, vField & );
inline void copy_names( const vField &, vField & );
//@}

/// \name Linear algebra on vFields
//@{
inline void add(const vField &, vField &);
inline void axpy( const Scalar, const vField &, vField & );
inline void axpy( const Scalar, const vField &, const vField &, vField & );
inline void axpby( const Scalar, const vField &, const Scalar,
                   const vField &, vField & );
inline void scale( const Scalar, vField &);
inline void axpy( const dVector &, const vField &, vField & );
inline void axpy( const dVector &, const vField &, const vField &, vField & );
inline void scale( const dVector &, vField &);
inline void scale( const vField &, vField &);
inline Scalar dot( const vField &, const vField & );
//@}

// implementation of vField methods

/// absolute value
inline void vField::abs() {
  for (size_type i=0; i<size(); i++) F[i]->Abs();
}

/// zero all the Field components
inline void vField::zero() {
  for (size_type i=0; i<size(); i++) F[i]->zero();
}

/// transform all Field components to polynomial space
inline void vField::forward_transform() {
  for (size_type i=0; i<size(); i++) F[i]->forward_transform();
}

/// transform all Field components to physical space
inline void vField::backward_transform() {
  for (size_type i=0; i<size(); i++) F[i]->backward_transform();
}

/// interpolate for each element to a uniform mesh in physical space
inline void vField::interpolate_to_uniform() {
  for (size_type i=0; i<size(); i++) F[i]->interpolate_to_uniform();
}

/// fill the sides for each Field using the data on the Elements
inline void vField::fill_sides() {
  for (size_type i=0; i<size(); i++) F[i]->fill_sides();
}

/// fill the sides for each Field using the data on the Elements
inline void vField::fill_sides_of_ghost_elements() {
  for (size_type i=0; i<size(); i++) F[i]->fill_sides_of_ghost_elements();
}

/// fill the sides for each Field with a Scalar
inline void vField::fill_sides(const Scalar u) {
  for (size_type i=0; i<size(); i++) F[i]->fill_sides(u);
}

/// fill the sides for each Field with a Scalar
inline void vField::fill_sides(const vector<Scalar> &u) {
  for (size_type i=0; i<size(); i++) F[i]->fill_sides(u[i]);
}

/// fill just the Field sides that are boundary sides
inline void vField::fill_bc_sides() {
  for (size_type i=0; i<size(); i++) F[i]->fill_bc_sides();
}

/// fill just the boundary sides with a constant
inline void vField::fill_bc_sides(const Scalar x) {
  for (size_type i=0; i<size(); i++) F[i]->fill_bc_sides(x);
}

/// share each Field's sides across a DGM::Comm
inline void vField::share_sides() {
#if 1
  // the non-blocking communication is typically faster
  begin_share_sides();
  end_share_sides();
#else
  // blocking communication can be slower
  for (size_type i=0; i<size(); i++) F[i]->share_sides();
#endif
}

/// write out statistics for the Field sides
inline void vField::write_side_stats(const size_type index) const {
  for (size_type i=0; i<size(); i++) F[i]->write_side_stats(index);
}

/// set each Element to its constant value (elementwise constant)
inline void vField::make_constant() {
  for (size_type i=0; i<size(); i++) F[i]->make_constant();
}

/// For all Fields, set the Element representation to have just Np modes
inline void vField::low_modes(const Ordinal Np) {
  for (size_type i=0; i<size(); i++) F[i]->low_modes(Np);
}
/// Zero all modes greater than Np but always retain at least pmin modes
inline void vField::low_modes(const Ordinal Np,
                              const Ordinal pmin) {
  for (size_type i=0; i<size(); i++) F[i]->low_modes(Np, pmin);
}
/// Zero modes greater than frac*p but always retain at least pmin modes
inline void vField::low_modes(const Scalar frac,
                              const Ordinal pmin) {
  for (size_type i=0; i<size(); i++) F[i]->low_modes(frac, pmin);
}
/// zero high modes above order specified in map
inline void vField::low_modes(const std::map<Size,Ordinal> &order) {
  for (size_type i=0; i<size(); i++) F[i]->low_modes(order);
}

/// remove (zero) the constant mode on all Fields and Elements
inline void vField::kill_constant() {
  for (size_type i=0; i<size(); i++) F[i]->kill_constant();
}

/// zero out the fine scales on each Element
inline void vField::coarse_scales(const int p_inc) {
  for (size_type i=0; i<size(); i++) F[i]->coarse_scales(p_inc);
}

/// zero out the coarse scales on each Elements
inline void vField::fine_scales(const int p_inc) {
  for (size_type i=0; i<size(); i++) F[i]->fine_scales(p_inc);
}

/// apply the exponential filter to all Fields
inline void vField::exp_filter( const Scalar eta, const Scalar s ) {
  for (size_type i=0; i<size(); i++) F[i]->exp_filter(eta, s);
}

/// sets the Element::State for every Field component to a prescribed value
inline void vField::set_state(const Element::States s) {
  for (size_type i=0; i<size(); i++) F[i]->set_state(s);
}

/// return the maximum side to interior Jacobian ratio
inline Scalar vField::get_max_sigma() const {
  if (sigma==0)
    for (size_type i=0; i<size(); i++)
      sigma = max( sigma, F[i]->get_max_sigma() );
  return sigma;
}

/// fill the vField storage with a vector
inline void vField::fill( const dVector &X ) {
  assert( qtot() == X.size() );
  dVector x;
  LocalSize start=0;
  for (size_type i=0; i<size(); ++i) {
    x.alias( *(const_cast<dVector*>(&X)), start, F[i]->qtot() );
    F[i]->fill(x);
    start += F[i]->qtot();
  }
}

/// fill the vField storage with a constant Scalar
inline void vField::fill( const Scalar x ) {
  for (size_type i=0; i<size(); ++i) F[i]->fill(x);
}

/// fill the vField storage with a constant Scalar
inline void vField::fill( const vector<Scalar> &x) {
  for (size_type i=0; i<size(); ++i) F[i]->fill(x[i]);
}

/// fill the vField storage s random solution
inline void vField::random() {
  for (size_type i=0; i<size(); ++i) F[i]->random();
}

/// extract the vField storage into a vector
inline void vField::extract( dVector &X ) const {
  if (qtot() != (LocalSize)X.size()) X.resize(qtot());
  dVector x;
  LocalSize start=0;
  for (size_type i=0; i<size(); ++i) {
    x.alias( X, start, F[i]->qtot() );
    F[i]->extract(x);
    start += F[i]->qtot();
  }
}

/// performs a component-wise average over a prescribed plane (in x, y, or z)
inline void vField::plane_average() {
  cout << "Starting Planar Average" << endl;
  for (size_type i=0; i<size(); i++) F[i]->plane_average();
  cout << "Finished Planar Average" << endl;
}

/// Packs the vector field storage
/** \pre The vector field must be contiguous and in transformed space

    This method is used to pack the vector field storage so that the data
    is completely contiguous with no gaps.  This allows the element data to
    be conformal with a Trilinos::Epetra vector.

    \warning This is alot of memory movement -- consider revision. */
inline void vField::pack() {
  assert( contiguous );
  for (size_type i=0; i<size(); i++) F[i]->pack();
  LocalSize cnt=0;
  for (size_type i=0; i<size(); i++) {
    for (LocalSize k=0; k<F[i]->ndof(); k++ )
      elmt_data[cnt++] = F[i]->elmt_data[k];
  }
}

/// Unpack the vector field storage
/** \pre \li \c The vector field must have been pack()ed.
    \li \c The vector field must be contiguous
    \li \c The data must be in transformed space

    This method returns a previously pack()ed vField to its original
    condition.

    \warning This is alot of memory movement -- consider revision. */
inline void vField::unpack() {
  assert( contiguous );
  LocalSize cnt = ndof();
  for (LocalSize i=size() ; i-- > 0 ; ) {
    for (LocalSize k=F[i]->ndof() ; k-- > 0 ; )
      F[i]->elmt_data[k] = elmt_data[--cnt];
  }
  for (size_type i=0; i<size(); i++) F[i]->unpack();
}

/// This applies the metric of integration (Gauss weights and |J|)
inline void vField::apply_metric() {
  for (size_type i=0; i<size(); i++) F[i]->apply_metric();
}

/// This removes the metric of integration (Gauss weights and |J|)
inline void vField::remove_metric() {
  for (size_type i=0; i<size(); i++) F[i]->remove_metric();
}

/// Copy one vField to another (both interiors and sides)
inline void vField::copy(const vField &F) {
  DGM::copy_names(F,*this);
  DGM::copy(F,*this);
  DGM::copy_sides(F,*this);
}

/// Copy the names from one vField to another
inline void vField::copy_names(const vField &F) {
  DGM::copy_names(F,*this);
}

/// project the vField to the polynomial space
inline void vField::project() {
  for (size_type i=0; i<size(); i++) F[i]->project();
}

/// project one vField to another (Field by Field)
inline void vField::project(vField &G) const {
  assert( size() == G.size() );
  for (size_type i=0; i<size(); i++) F[i]->project(G[i]);
}

/// compute relative maximum error
inline void vField::relative_max_error(const vField& Ut,
  dVector &Linf, dVector &L2, dVector &H1) const
{
  assert(size() == Ut.size());
  Linf.resize(size()); L2.resize(size()); H1.resize(size());
  Linf = 0.0; L2 = 0.0; H1 = 0.0;
  for (size_type i=0; i<size(); ++i)
    F[i]->relative_max_error( *Ut.F[i], Linf[i], L2[i], H1[i] );
}

/// computes and output to stdout the Linf, L2, H1 norms for each component
inline void vField::norm() const {
  for (size_type i=0; i<size(); i++) F[i]->norm();
}

/// computes and output with given name to stdout the norms for each component
inline void vField::norm( const vector<string> names ) const {
  assert( names.size() <= (size_t)size() );
  for (size_type i=0; i<static_cast<size_type>(names.size()); i++)
    F[i]->norm( names[i] );
}

/// same as norm() but returns vectors that contain the norm values
inline void vField::norm(dVector &Linf, dVector &L2, dVector &H1) const {
  Linf.resize(size()); L2.resize(size()); H1.resize(size());
  Linf = 0.0; L2 = 0.0; H1 = 0.0;
  for (size_type i=0; i<size(); i++) F[i]->norm( Linf[i], L2[i], H1[i] );
}

/// Returns the min value and which element it occurs for each Field
inline void vField::min_elements(dVector &min, gVector &elems) const
{
  min.resize(size()); elems.resize(size());
  min = 0.0; elems = 0;
  for (size_type i=0; i<size(); ++i) min[i] = F[i]->min(elems[i]);
}

/// Returns the max value and which element it occurs for each Field
inline void vField::max_elements(dVector &max, gVector &elems) const
{
  max.resize(size()); elems.resize(size());
  max = 0.0; elems = 0;
  for (size_type i=0; i<size(); ++i) max[i] = F[i]->max(elems[i]);
}

/// Output the range (minimum and maximum) values for each Field
inline void vField::range() const {
  ostream &out = comm->cout();
  out << "  Ranges for " << name << ":\n";
  out << "  -----------------------------------------------------\n";
  for (size_t i=0; i<F.size(); i++) F[i]->range();
  out << "  -----------------------------------------------------" << endl;
}

/// Output the side range (minimum and maximum) values for each Field
inline void vField::rangeSide() const {
  ostream &out = comm->cout();
  out << "  Side Ranges for " << name << ":\n";
  out << "  -----------------------------------------------------\n";
  for (size_t i=0; i<F.size(); i++) F[i]->rangeSide();
  out << "  -----------------------------------------------------" << endl;
}

//=============================================================================
//                    v F i e l d   H e l p e r s
//=============================================================================

/// project a vField against the Basis and transform to physical space
inline void project( vField &vF) {
#if 1
  vF.project();
#else
  for (vField::size_type i=0; i<vF.size(); i++) vF[i]->project();
#endif
}

/// project and filter a vField
inline void filter_project( vField &vF, vector<Filter*> filtr ) {
  for (vField::size_type i=0; i<vF.size(); i++) filter_project(vF[i], filtr);
}

/// copy sides from one vField to another
inline void copy_sides(const vField &U, vField &V) {
  assert(U.size() == V.size());
  for (vField::size_type i=0;i<U.size();i++) copy_sides(U[i],V[i]);
}

/// Copy the Field data from X to Y
inline void copy( const vField &X, vField &Y) {
  assert(X.size()==Y.size());
  for (vField::size_type i=0; i<X.size(); i++) copy( X[i], Y[i] );
}

/// Copy the Field names from X to Y
inline void copy_names( const vField &X, vField &Y) {
  assert(X.size()==Y.size());
  for (vField::size_type i=0; i<X.size(); i++) Y[i]->set_name(X[i]->get_name());
}

/// add two vFields
inline void add( const vField &vUf, vField &vFf ) {
  assert(vUf.size() == vFf.size());
  for (vField::size_type i=0; i<vUf.size(); i++) add( vUf[i], vFf[i] );
}

/// add two vFields
inline void add( const vField &vUf,
                 const std::vector<Size>&vUf_to_vFf,
                       vField &vFf ) {
  assert(vUf.size() == vFf.size());
  for (vField::size_type i=0; i<vUf.size(); i++) add(vUf[i],vUf_to_vFf,vFf[i]);
}

/// extract a vField
inline void extract(vField &vUf,
                 const std::vector<Size>&vUf_to_vFf,
                 const vField &vFf ) {
  assert(vUf.size() == vFf.size());
  for (vField::size_type i=0; i<vUf.size(); i++) extract(vUf[i],vUf_to_vFf,vFf[i]);
}

/// Scale and add two vFields
inline void axpy( const Scalar a, const vField &X, vField &Y ) {
  assert(X.size() == Y.size());
  for (vField::size_type i=0; i<X.size(); i++) axpy( a, X[i], Y[i] );
}

/// Scale and add two vFields
inline void axpy( const Scalar a, const vField &X,
    const vField &Y, vField &Z ) {
  assert(X.size()==Y.size() && X.size()==Z.size());
  for (vField::size_type i=0; i<X.size(); i++) axpy( a, X[i], Y[i], Z[i] );
}

/// Scale a vField
inline void scale( const Scalar a, vField &X) {
  for (vField::size_type i=0; i<X.size(); i++) scale( a, X[i] );
}

/// Vector scale and add two vFields
inline void axpy( const dVector &a, const vField &X, vField &Y ) {
  assert(X.size()==Y.size());
  for (vField::size_type i=0; i<X.size(); i++) axpy( a[i], X[i], Y[i] );
}

/// Vector scale and add two vFields
inline void axpy( const dVector &a, const vField &X,
    const vField &Y, vField &Z ) {
  assert(X.size()==Y.size() && X.size()==Z.size());
  for (vField::size_type i=0; i<X.size(); i++) axpy( a[i], X[i], Y[i], Z[i] );
}

/// Scale-scale and add:  z = a*x + b*y  (Y and Z can share the same storage)
inline void axpby( const Scalar a, const vField &X,
                   const Scalar b, const vField &Y, vField &Z ) {
  assert(X.size()==Y.size() && X.size()==Z.size());
  for (vField::size_type i=0; i<X.size(); i++) axpby( a, X[i], b, Y[i], Z[i] );
}

/// Vector scale a vField
inline void scale( const dVector &a, vField &X) {
  if ( static_cast<vField::size_type>(a.size()) != X.size() )
    DGM::Comm::World->error("Scaled a vField by incompatible dVector");
  for (vField::size_type i=0; i<X.size(); i++) scale( a[i], X[i] );
}

/// Scale a vField by another vField
inline void scale( const vField &A, vField &X) {
  if (A.size() != X.size() )
    DGM::Comm::World->error("Tried to scale incompatible vFields");
  for (vField::size_type i=0; i<X.size(); i++) scale( A[i], X[i] );
}

/// Compute the dot product of two vFields
inline Scalar dot( const vField &X, const vField &Y) {
  assert(X.size()==Y.size());
  Scalar result = 0;
  for (vField::size_type i=0; i<X.size(); i++) result += dot( X[i], Y[i] );
  return result;
}

#ifdef DGM_ITL_INTERFACE
/// Provides interface to ITL
namespace itl {
  /// Make interface for ITL using vField (not currently using)
  inline Scalar itl::dot(const vField & VecA, const vField &VecB) {
    return ::dot(VecA, VecB);  // use dot in global namespace
  }
}  // namespace itl
#endif

} // namespace DGM

#endif  // DGM_VFIELD_HPP
