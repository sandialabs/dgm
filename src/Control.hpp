#ifndef DGM_CONTROL_HPP
#define DGM_CONTROL_HPP

/** \file Control.hpp
    \brief Control base class declaration
    \author Scott Collis

    For Steady control, the Control::Entry defines temporary storage,
    Grad_data, to store transient gradient information, at the last time slab,
    it does a time integral over the transient storage to get the correct
    gradient.  Note: I believe that a simple sum/accumulation is all that is
    needed. [ssc]

    I can't understand. One of the way to make it simple and clean is not to
    differentiate steady and unsteady control except when we load/save the
    same control profile at different time levels (including the sub-levels)
    for the steady control since it is constant in time. [gqchen]

    Let me try to be more explicit.  Right now, the only thing that prevents
    the Steady control implementation from being "ideal" is in the gradient
    computation.  The way you do that right now is to make a big temporary
    storage location, Grad_data, and put all store all unsteady the gradient
    information.  In the end, however, all you do is sum that information
    using Trapezoidal integration to get the "complete" gradient.  All I am
    suggesting that you do is perform the sum "on the fly."  There is no need
    to store all the unsteady data, just accumulate it in a single storage
    location of size ctrl_size() using the correct integration weights. Right
    now, you (arbitrarily) use Trapezoidal integration, but you could, in fact
    using any method including the same method as is used to integration the
    state and adjoint equations (RK4 in our case).  Now, if we setup the
    adjoint of RK4 (or any method that we use) in an appropriate way, then we
    can ensure that the appropriate weights (i.e. \f$ b[k] dt\f$) are
    automatically included in the adjoint field so that a simple sum of the
    gradient is equivalent to RK4 integration.  It is straightforward to do
    this, but it does involve care in formulating the discrete adjoint of the
    time advancement method.  Is this more clear?  I have a document in the
    dgm/docs directory called rk4.tex which is an incomplete attempt to work
    this out.  I had hoped that you would be able to complete it... [ssc]

    BTW, Dr. Collis, you are right for the definition of the Control cost \f[
    J_\mathrm{cost} = \frac{\alpha T}{2} \int_{\Gamma} {g^2} d\Gamma \f] makes
    everything consistent. [gqchen]

    Possible enhancement: It is possible to read/write the phi vector directly
    instead of looping through the entries in the phi_db.  All that is needed
    is to form phi_disp and phi_len iVectors using the cdisp and clen
    information in the Entry objects.  Of course, one will need to add the
    Entry::offset to the cdisp to get the phi_disp. [ssc]
*/

// standard libraries
#include <iostream>
#include <string>
#include <vector>
#include <list>
using namespace std;

// boost includes
#include "boost/numeric/conversion/cast.hpp"
using boost::numeric_cast;

// DTK includes
#include "DTK.hpp"

// DGM includes
#include "Comm.hpp"
#include "Types.hpp"
#include "Table.hpp"
#include "Ctrl.hpp"
#include "ArgList.hpp"

namespace DGM {

// forward declarations
class Control;
class State;
class Adjoint;

/// DGM::Control class which is the primary DGM interface to Optimizers
/** The Control class is a high-level view of the data and associated
    methods for manipulating variables that participate in an optimization
    process.  Control provides a single vector view (actually a product
    vector) of all controlled variables in a vector called \f$\phi\f$.
    Control supports simple linear algebra-type methods that act on
    \f$\phi\f$ and this makes it easier to build optimization algorithms
    that work with a Control object.  All DGM::Optimizer classes are
    designed to work with Control objects.  The real power of the Control
    object is that not only does it provide a simple vector view of the
    optimization variables, but it also manages a database of all the
    instantiated Ctrl objects.

    While Control objects provide the interface to the Optimizer classes,
    Ctrl objects are lower-level classes that provide the detailed
    implementation of particular types of optimization variables.  For
    example, if you want to define a boundary-condition control class, you
    would derive off of both the BC and Ctrl classes.  By supplying the
    Ctrl interface, you ensure that the object supports all the
    functionality needed by the Control class for it to be used as an
    optimization variable.  Please see DGM::Ctrl for more details on this
    interface.

    In order to streamline the communication between a Control and its
    multiple Ctrl objects, the Control class contains a database of
    Control:Entry where each Entry contains a pointer to a Ctrl.  The
    advantage of the Entry class is that it has additional information and
    methods, not needed at the Ctrl level, that show how the Ctrl class is to
    be used relative to the full Control object.  In particular, the Entry
    class manages the communication and data sharing between the global
    \f$\phi\f$ vector and the local storage on each Ctrl.

    \image html Control.jpg

    The figure shown above, gives an example of a Control object that holds
    three separate Ctrl objects, all agglomerated into the single
    \f$\phi\f$ vector, but each with its own Entry in the Control database.
    In this example, the first Ctrl is a steady boundary control, the
    second is a steady medium (or source) control (which is larger in size
    than the boundary control since it may live over the entire spatial
    domain), and the third is an unsteady source control where there are 7
    time slabs which each contain a spatially varying source term.  Note
    that each Ctrl makes its own contribution to the global \f$\phi\f$
    vector making an overall product vector for the total control.

    The job of the Control class is to manage the interface between an
    optimizer (which generally likes to work in an abstract vector space)
    and the detailed implementation of the Ctrl objects.  The Control class
    also has the important task of managing parallel communication, for
    example, accumulations associated with Control::inner_product().
    Otherwise, most of the Control methods are simply iterations over the
    Entry object database where the analogous method is called on the
    underlying Ctrl object.

    In this way, the Entry class is an intermediary that manages the data
    communication between the global \f$\phi\f$ vector at the Control level
    and the individual storage of each Ctrl objects that are held in the
    Control::Entry database.  For example, in the case of an unsteady Ctrl,
    the Entry class is responsible for loading the correct portion of the
    global \f$\phi\f$ vector for the time-slab under consideration, into
    the Ctrl's local storage so that the Ctrl class can perform the
    requested operation.
*/
class Control : public DTK::Control<Scalar,Ordinal,vField,dVector,
                                    State,Control> {
public:

  /// supported types of control object
  enum Control_Type {
    CONTROL,             ///< default type for a control variable
    GRADIENT,            ///< gradient wrt control of a scalar function
    STEP                 ///< perturbation in the control, small step
  };

protected:

  Table params;           ///< Parameter table

  Scalar dt;              ///< Constant time-step
  Ordinal npredict;       ///< Number of time-steps
  Ordinal nsstep;         ///< Number of sub-steps
  Ordinal npp;            ///< Number of time-step * number of sub_steps

  /// \name Parallel processing data-structures
  /** Data-structures for parallel communication of Control information. */
  //@{
  Ordinal gnum;           ///< Global number of controls across parallel procs
  Ordinal glen;           ///< Global control length across parallel procs
  intVector global_len;   ///< Global lengths for parallel gather/scatter
  intVector global_disp;  ///< Global displacements for parallel gather/scatter
  //@}

  State *state;               ///< This Control controls this State

  const DGM::Comm::Ptr comm;  ///< Communicator for this Control

  Control_Type controlType;   ///< type of control object

private:

  const int verb;             ///< Verbosity level

public:

  /// Global size type
  typedef DGM::Size GlobalSize;

  /// Local size type
  typedef DGM::Ordinal LocalSize;

  /// Shared pointer to Control
  typedef DGM::Shared<Control>::Ptr Ptr;

  // Control database entry (defined below)
  class Entry;

  /// Database Entry type
  typedef DGM::Shared<Entry>::Ptr dbEntry_t;

  /// Database type
  typedef std::list<dbEntry_t> db_t;

  string code;              ///< Executable code name
  string root;              ///< Root filename

  dVector phi;              ///< Control vector \f$\phi\f$ (the actual storage)

  db_t phi_db;              ///< Control Entry database

  mutable dVector costs;    ///< Work vector for individual entries costs

  /// Setup the control database
  virtual void setup();

  /// Constructor
  Control(DGM::ArgList &args, State *,
          const DGM::Comm::Ptr = DGM::Comm::World);

  /// Destructor
  virtual ~Control();

  /// Clone method must be implemented for all classes derived from Control
  virtual Control* clone() const =0;

  /// Parses the argument list
  virtual void parse_args( DGM::ArgList &args );

  /// Returns the number of entries in the Control database
  virtual size_t num_ctrl() const { return phi_db.size(); }

  /// Resets the vector of costs for each Entry to be zero
  virtual void reset_costs() {
    costs.resize( numeric_cast<Ordinal>(phi_db.size()) );
    costs=0;
  }

  /// Outputs the costs to a supplied output stream
  virtual void output_costs(ostream &os) const;

  /// Returns a vector of the current costs
  dVector get_costs() const { return costs; }

  /// Returns the local length of phi for this Control
  virtual size_t size() const { return phi.size(); }

  /// Resizes the local length of phi for this Control
  virtual void resize(Ordinal n) { phi.resize(n); }

  /// Returns the global length of phi for this Control
  virtual Ordinal global_size() const { return glen; }

  /// Plot the control
  virtual void plot(const Ordinal ntout, const Ordinal iter,
                    const string *ext=0) const;

  virtual void set_parameter(const std::string&, const std::string&);
  /// Number of substeps (assumed fixed) for this Control object
  Ordinal get_nsstep() const {return nsstep;}
  
  /// Number of timesteps (assumed fixed) to predict the solution
  Ordinal get_npredict() const {return npredict;}
  
  /// Return the timestep (assumed fixed) for this Control object
  Scalar get_dt() const {return dt;}

  // Generic member functions: same for derived classes
  virtual void initialize();
  virtual void zero();
  virtual void output(Ordinal);

  virtual void set_data(const Ordinal, const Ordinal=0);
  virtual void finalize(const Ordinal, const Ordinal=0);
  virtual void load(dVector&, const Ordinal, const Ordinal=0) const;
  virtual void store(dVector&, const Ordinal, const Ordinal=0);
  virtual void set_direction();

  virtual Scalar cost() const;
  virtual Scalar cost(const Ordinal, const Ordinal=0) const;

  /// Call the bound method on each Ctrl at each time/sub step
  virtual void bound(const Ordinal, const Ordinal=0);

  /// Call the bound method over all Ctrl's and all time
  virtual void bound();

  /// Call the realizable method on each Ctrl at each time/sub step
  virtual bool realizable(const Ordinal, const Ordinal=0);

  /// Call the realizable  method over all Ctrl's and all time
  virtual bool realizable();

  /// Compute the individual Ctrl inner products between two Controls
  dVector inner_products(const Control *Y) const;

  /// Compute the inner-product between two Control objects
  virtual Scalar inner_product(const Control *Y) const;

  /// Compute the inner-product between two Control objects
  virtual Scalar inner_product(const Control &Y) const {
    return inner_product(&Y);
  }

  /// Compute the inner-product between two Control objects
  virtual Scalar inner_product(const Control::Ptr Y) const;

  /// Compute the norm of all ctrl's
  virtual Scalar norm() const;

  /// Compute the norms for each Ctrl
  dVector norms() const {
    const Ordinal numCtrl = numeric_cast<Ordinal>(num_ctrl());
    dVector result(numCtrl,0.0);
    dVector inprod(numCtrl,0.0);
    inprod = inner_products(this);
    for (Ordinal i=0; i<numCtrl; ++i) {
      result[i] = sqrt(inprod[i]);
    }
    return result;
  }

  /// Return a vector with the names of each Ctrl
  vector<string> names() const;

  /// Compute a contribution to the gradient
  virtual void gradient( const vField &S, const vField &A, Control::Ptr G,
                         const Ordinal istep, const Ordinal sstep=0 );

  /// Compute a contribution to the gradient
  virtual void gradient( const vField &S, const vField &A, Control &G,
                         const Ordinal istep, const Ordinal sstep=0 );

  /// Compute Hessian vector product for the observation term
  virtual void HessVecProd_obs( const vField &S,
                                const vField &A,
                                const Control &x,
                                const Control &dx,
                                Control &H_dx,
                                const Ordinal istep,
                                const Ordinal sstep=0 ) {
    DGM_UNDEFINED;
  }

  /// Compute Hessian vector product for the regularization term
  virtual void HessVecProd_reg( const Control &x,
                                const Control &dx,
                                Control &H_dx,
                                const Ordinal istep,
                                const Ordinal sstep=0 );

  /// Compute a contribution to a diagonal preconditioner at one timestep
  virtual void computePreconditioner( const vField &S, const vField &A,
                                      Control::Ptr P, const Ordinal istep,
                                      const Ordinal sstep=0 );

  /// Compute a contribution to a diagonal preconditioner at one timestep
  virtual void computePreconditioner( const vField &S, const vField &A,
                                      Control &P, const Ordinal istep,
                                      const Ordinal sstep=0 ) {
    DGM_UNDEFINED;
  }

  /// Apply a preconditioner
  virtual void applyPreconditioner(const Control::Ptr G, Control::Ptr P);

  /// Apply a preconditioner
  virtual void applyPreconditioner(const Control &G, Control &P) {
    DGM_UNDEFINED;
  }

  /// Read the control from a file:  needed for control restart
  virtual streamoff read(const string &, const streamoff);

  /// Write the control to a file:  needed for control restart
  virtual streamoff write(const string &, const streamoff);

  /// Diff two control files given header offsets, return
  /// updated offsets for continued reading
  virtual int diff(const Control& control, const Scalar aeps,
                   const Scalar reps);

  /// sum control into this control.
  virtual int sum(const Control& control, const double mult,  
                  const std::vector<Size>&sub_to_mstr);

  /// Extract out from this control.
  virtual int ext(Control& control,const std::vector<Size>&sub_to_mstr) const;

  /// If any Control::Entry is unsteady then return false, otherwise true
  virtual bool steady() const;

  /// Gather control vector from across a parallel machine
  virtual void gather( dVector & ) const;

  /// Scatter control vector across parallel machine
  virtual void scatter( dVector & );

  /// Accessor for the global (across a parallel processor) control length
  virtual Ordinal get_glen() const { return glen; }

  /// Accessor that gives access to the State pointer
  virtual State* get_state() {
    if (!state) error("Control::state undefined");
    return state;
  }

  /// Accessor for Control vector
  virtual const dVector & get_phi() const { return phi; }

  /// Accessor to Control vector as a raw pointer
  virtual const Scalar * get_phi_ptr() const { return phi.data(); }

  /// Accessor to get control type (used by Optimizer)
  Control_Type control_type() const { return controlType; } 

  /// Accessor to set control type
  void control_type(const Control_Type t) { controlType=t; } 
 
#ifdef DGM_USE_TIME_REG
  void axpy(const Scalar a, const Ordinal, const Control *X,
            const Ordinal, const Ordinal);

  /// Return time slab length, only for the full unsteady control
  Ordinal get_slablen() { assert(npp != npp); return phi.size()/npp;}

  void reg_load(dVector&, const Ordinal, const Ordinal=0) const;

  Scalar cost_t(const Ordinal, const Ordinal=0) const;
#endif

  // Experimental methods
  void beLinear();
  void beNormal();

protected:

  /// Copy constructor only allowed in derived classes
  Control(const Control*);

  friend inline void add( const Control::Ptr, Control::Ptr);
  friend inline void axpy( const Scalar a, const Control::Ptr X,
                           Control::Ptr Y );
  friend inline void axpy( const Scalar a, const Control *,
                           Control * );
  friend inline void axpy( const Scalar a, const Control::Ptr X,
                           const Control::Ptr Y, Control::Ptr Z );
  friend inline void axpy( const dVector &a, const Control::Ptr X,
                           Control::Ptr Y );
  friend inline void axpy( const dVector &a, const Control::Ptr X,
                           const Control::Ptr Y, Control::Ptr Z );
  friend inline void scale( const Scalar a, Control::Ptr X);
  friend inline void scale( const Scalar a, Control *);
  friend inline void scale( const dVector &a, Control::Ptr X);
  friend inline void copy( const Control::Ptr, Control::Ptr );
  friend inline void copy( const Control *, Control * );
  friend inline void fill( const Scalar a, Control::Ptr X );
  friend inline void fill( const Scalar a, Control * );

  friend inline void hadamard_multiply( const Control::Ptr, Control::Ptr );
};

//============================================================================
//                 Basic linear algebra on Controls
//============================================================================

/// \name Linear algebra on Controls
//@{

/// Add two Controls
inline void add( const Control::Ptr X, Control::Ptr Y) {
  if (X->phi.size() != Y->phi.size()) {
    X->comm->cerr()<< "Attempted to add incompatible Controls" << endl;
    X->comm->exit(DGM::FAILURE);
  }
  dvadd( X->phi, Y->phi);
}

/// Scale and add Controls
inline void axpy( const Scalar a, const Control::Ptr X, Control::Ptr Y ) {
  if (X->phi.size() != Y->phi.size()) {
    X->comm->cerr()<< "Attempted to axpy incompatible Controls" << endl;
    X->comm->exit(DGM::FAILURE);
  }
  daxpy( a, X->phi, Y->phi );
}

/// Scale and add Controls
inline void axpy( const Scalar a, const Control *X, Control *Y ) {
  if (X->phi.size() != Y->phi.size()) {
    X->comm->cerr()<< "Attempted to axpy incompatible Controls" << endl;
    X->comm->exit(DGM::FAILURE);
  }
  daxpy( a, X->phi, Y->phi );
}

/// Scale and add Controls
inline void axpy( const dVector &a, const Control::Ptr X, Control::Ptr Y ) {
  if (a.size()!=X->phi.size()) {
    X->comm->cerr()<< "Incompatible element scaling factor" << endl;
    X->comm->exit(DGM::FAILURE);
  }
  dvmul(a, X->phi, Y->phi );
}

/// Scale and add Controls
inline void axpy( const Scalar a, const Control::Ptr X, const Control::Ptr Y,
                  Control::Ptr Z ) {
  if (X->phi.size() != Y->phi.size() ||
      X->phi.size() != Z->phi.size()) {
    X->comm->cerr()<< "Attempted to axpy incompatible Controls" << endl;
    X->comm->exit(DGM::FAILURE);
  }
  daxpy( a, X->phi, Y->phi, Z->phi );
}

/// Scale and add Controls
inline void axpy( const dVector &a, const Control::Ptr X, const Control::Ptr Y,
                  Control::Ptr Z) {
  if (a.size()!=X->phi.size()) {
    X->comm->cerr()<< "Incompatible element scaling factor" << endl;
    X->comm->exit(DGM::FAILURE);
  }
  dvvtvp(a,X->phi,Y->phi,Z->phi);
}

/// Scale a Control with a scalar
inline void scale( const Scalar a, Control::Ptr X ) {
  scale( a, X->phi );
}

/// Scale a Control with a scalar
inline void scale( const Scalar a, Control *X ) {
  scale( a, X->phi );
}

/// Scale a Control with a vector
inline void scale( const dVector &a, Control::Ptr X ) {
  dvmul(a,X->phi,X->phi);
}

/// Copy one Control to another
inline void copy( const Control::Ptr X, Control::Ptr Y) {
  Y->phi = X->phi;
}

/// Copy one Control to another
inline void copy( const Control *X, Control *Y) {
  Y->phi = X->phi;
}

/// Set the control to a scalar value
inline void fill( const Scalar a, Control *X ) {
  X->phi = a;
}

/// Set the control to a scalar value
inline void fill( const Scalar a, Control::Ptr X ) {
  X->phi = a;
}

/// Hadamard multiplication of two controls
inline void hadamard_multiply( const Control::Ptr X, Control::Ptr Y) {
  if (X->phi.size() != Y->phi.size()) {
    X->comm->cerr()<< "Attempted to perform Hadamard multiplication between incompatible Controls" << endl;
    X->comm->exit(DGM::FAILURE);
  }
  dvhmult( X->phi, Y->phi);
}
//@}

//============================================================================
//                       Control Database Entry
//============================================================================

/// Class defining an entry for the Control database
/** This is basically a smart data structure that holds a Ctrl object with
    additional information and methods that show how that Ctrl is to be used
    relative to the full Control object.

    In particular, the Entry class manages the sharing of data between the
    global \f$\phi\f$ vector and the Ctrl implementation including the case
    where the Ctrl is unsteady so that there are multiple instances of Ctrl
    data in the global \f$\phi\f$ vector, one for each time-slab.

    Managing this data transfer in the unsteady case is the primary role of
    the Entry class.  Of course, it also functions in the steady case and
    in most methods, the implementation is trivial for this case.
*/
class Control::Entry {

  const int verb;         ///< Verbosity level

  Control *control;       ///< Control database that owns this entry
                          //   NOTE: Entries are SHARED by multiple
                          //         Control objects and this will point to
                          //         the original creator NOT the actual owner!

  dVector Grad_data;      ///< Gradient storage for steady control
  dVector Prec_data;      ///< Preconditioner storage for steady control

  bool _filled;           ///< whether the Entry has been filled

public:

  Ctrl *ctrl;             ///< Abstract control object

  /// Shared pointer to Entry
  typedef DGM::Shared<Entry>::Ptr Ptr;

  string name;                        ///< Name of this control
  Ordinal offset;                     ///< Offset to start of Entry's phi data
  Ordinal length;                     ///< Total length of Entry's data in phi
  Ordinal ntime;                      ///< Number of time slabs

  // Following needed for control restart
  Size cglen;                         ///< Global data length
  CMC::Vector<Size,Ordinal> cdisp;    ///< Global data displacement
  CMC::Vector<Ordinal,Ordinal> clen;  ///< Data length

  const DGM::Comm::Ptr comm;          ///< Communicator for this Control

  /// Length of each slab
  Ordinal ctrl_size() const {
    return ctrl->data_size();
  }

  /// Get a pointer to Ctrl for this Entry
  Ctrl* get_ctrl() {return ctrl;}

  /// Get a constant pointer to Ctrl for this Entry
  const Ctrl* get_ctrl() const {return ctrl;}

  /// Constructor
  Entry(Control *C, const string n, const Ordinal off, const Ordinal nt,
        Ctrl *c, const Scalar dt_, const CMC::Vector<Size,Ordinal> &cdisp_,
        const CMC::Vector<Ordinal,Ordinal> &clen_, const Size glen,
        const DGM::Comm::Ptr comm_);

  //===========================================================================
  /// \name Define a new Entry interface using Control pointers
  //@{
  /// Puts the data in global_phi into the ctrl's data
  void set_data(const Ordinal index, const Control *c) {
    if (ctrl->steady() && index>0) return;
    if (verb)
      comm->cout() << "Control::Entry::set_data(" << index << ") for "
                   << name << endl;
    const Ordinal i = (ctrl->steady()) ? 0 : index;
    if (ntime<=i) {
      comm->cerr() <<__FILE__<<":"<<__LINE__
       <<" Error ntime is less than i.  ntime:"<<ntime<<" i:"<<i
       <<" Calling abort......"<<endl;
    }
    assert( i < ntime );
  #ifdef DGM_CONTROL_DETAILS
    cout<<comm->MyPID()<<": global_phi.size() = "<<global_phi.size()<<endl;
  #endif
    dVector view;
    if (ctrl->owner())
      view.alias( *(const_cast<dVector*>(&c->phi)),
                  offset+i*ctrl_size(), ctrl_size() );
    if (Control::CONTROL==c->control_type())
      ctrl->set_data( view );
    else
      ctrl->set_data_no_transform( view );
  }
  /// Send the finalize message to the Ctrl to prepare for simulator
  void finalize(const Ordinal index) {
    if (ctrl->steady() && index>0) return;
    if (verb) comm->cout()<<"Control::Entry::finalize("<<index<<") for "
                          <<name<<endl;
    ctrl->finalize();
  }
  /// Gets the data from Ctrl objects and puts in global_phi
  void get_data(const Ordinal index, Control *c) {
    get_data(index,c->phi);
  }
  /// Gets the data from Ctrl objects and puts in global_phi
  void fill( const Ordinal index, const Scalar time, Control *c ) {
    fill(index,time,c->phi);
  }
  /// Sets the correct view into the global control and sets the direction
  void set_direction(const Ordinal index, Control *c) {
    set_direction(index, c->phi);
  }
  /// Load a vector with the global control data
  void load( const Ordinal index, const Control *c, dVector &out ) const {
    load(index,c->phi,out);
  }
  void store( dVector &in, const Ordinal index, Control *c ) {
    store(in,index,c->phi);
  }
  /// Take the Ctrl inner product of two controls
  Scalar inner_product(const Ordinal index, const Control *X,
                       const Control *Y) {
    if (verb)
      comm->cout() << "Control::Entry::inner_product() for " << name << endl;
    dVector Ydata;
    set_data(index, X);
    load(index, Y, Ydata);
    if ( !ctrl->owner() ) return 0.0;
    return ctrl->inner_product(Ydata);
  }
  /// Compute the contribution to the total cost for this Ctrl and time-slice
  Scalar cost(const Ordinal index, const Control *C) {
    /// \warning The following line was commented out
    //if (ctrl->steady() && index>0) return 0.0;
    if (verb) comm->cout() << "Control::Entry::cost() for " << name
                           << " of type " << C->control_type() << endl;
    set_data(index, C);
    if ( !ctrl->owner() ) return 0.0;
    return ctrl->cost();
  }
  /// Bound the Ctrl data for timeslice=index
  void bound(const Ordinal index, Control *c) {
    bound(index,c->phi);
  }
  /// Determine realizability for timeslice=index
  bool realizable( const Ordinal index, Control *c) {
    if (ctrl->steady() && index>0) return true;
    if (verb) comm->cout() << "Control::Entry::realizable()" << endl;
    set_data(index, c);
    bool result = ctrl->realizable();
    return result;
  }
  void gradient( const Ordinal istep, const Ordinal sstep, Control *c,
                 const vField &S, const vField &A, Control *g) {
    gradient(istep,sstep,c->phi,S,A,g->phi,c->control_type());
  }
  void HessVecProd_reg(const Ordinal istep, const Ordinal sstep,
                       const Control *x, const Control *dx, Control *H_dx) {
    HessVecProd_reg(istep,sstep,x->phi,dx->phi,H_dx->phi);
  }
  void computePreconditioner( const Ordinal istep, const Ordinal sstep,
                              const Control *c, const vField &S,
                              const vField &A, Control *p ) {
    computePreconditioner(istep,sstep,c->phi,S,A,p->phi,c->control_type());
  }
  void applyPreconditioner( const Control *c, const Control *g, Control *p) {
    applyPreconditioner(c->phi,g->phi,p->phi,c->control_type());
  }
  streamoff read(const string &fname, const streamoff skip, Control *G ) {
    return read(fname,skip,G->phi);
  }
  streamoff write(const string &fname, const streamoff skip, const Control*G){
    return write(fname,skip,G->phi);
  }
  void plot(const vField &S, const Control *C, const Ordinal npredict,
            const Ordinal ntout, const Ordinal nsstep, const Ordinal riter,
            const string *ext=0) const {
    const int control_type = static_cast<int>(C->control_type());
    plot(S,C->phi,npredict,ntout,nsstep,riter,ext,control_type);
  }
  //@}
  //===========================================================================

  /// query whether the fill method is overloaded
  bool has_fill() const { return ctrl->has_fill(); }

  /// check whether Entry is filled
  bool filled() const { return _filled; }

  /// set whether Entry is filled
  void filled(const bool filled) { _filled=filled; }

  /// Simply calls the Ctrl::output() method
  void output() const {
    if (verb) comm->cout() << "Control::Entry::output() for " << name << endl;
    ctrl->output();
  }

  /// set the time for this Ctrl
  void time(const Scalar time) { ctrl->time(time); }

  /// get the time for this Ctrl
  Scalar time() const { return ctrl->time(); }

  void set_parameter(const std::string&, const std::string&);

private:

  /// Puts the data in global_phi into the ctrl's
  void set_data(const Ordinal index, const dVector &global_phi,
                const Control::Control_Type type);

  /// Gets the data from Ctrl objects and puts in global_phi
  void get_data(const Ordinal index, dVector &global_phi ) {
    if (verb) comm->cout() << "Control::Entry::get_data("<<index<<") for "
                           <<name<<endl;
    const Ordinal i = (ctrl->steady()) ? 0 : index;
    assert( i < ntime );
    if ( !ctrl->owner() ) return;
    dVector view;
    view.alias( global_phi, offset+i*ctrl_size(), ctrl_size() );
    ctrl->get_data( view );
  }

  /// Gets the data from Ctrl objects and puts in global_phi
  void fill( const Ordinal index, const Scalar time, dVector &global_phi ) {
    if (verb) comm->cout() << "Control::Entry::fill() for " << name << endl;
    const Ordinal i = (ctrl->steady()) ? 0 : index;
    assert( i < ntime );
    dVector view;
    if ( ctrl->owner() )
      view.alias( global_phi, offset+i*ctrl_size(), ctrl_size() );
    ctrl->fill( time, view );
  }

  /// Sets the correct view into the global control and sets the direction
  void set_direction( const Ordinal index, dVector &global_phi ) {
    if (verb)
      comm->cout() << "Control::Entry::set_direction() for " << name << endl;
    assert( (Ordinal)index < ntime );
    dVector view;
    if ( ctrl->owner() )
      view.alias( global_phi, offset+index*ctrl_size(), ctrl_size() );
    ctrl->set_direction( view );
  }

  /// Load a vector with the global control data
  void load( const Ordinal index, const dVector &global_phi,
             dVector &out ) const {
    if (verb) comm->cout() << "Control::Entry::load() for " << name << endl;
    const Ordinal i = (ctrl->steady()) ? 0 : index;
    assert( i < ntime );
    if ( !ctrl->owner() ) return;
    dVector view;
    view.alias( *(const_cast<dVector*>(&global_phi)),
                offset+i*ctrl_size(), ctrl_size() );
    if (out.size() != view.size()) out.resize(view.size());
    out = view;
  }

  /// Store a vector into the global control data
  void store( dVector &in, const Ordinal index, dVector &global_phi ) {
    if (verb) comm->cout() << "Control::Entry::store() for " << name << endl;
    const Ordinal i = (ctrl->steady()) ? 0 : index;
    assert( i < ntime );
    assert( in.size() == ctrl_size() );
    if ( !ctrl->owner() ) return;
    dVector view;
    view.alias( global_phi, offset+i*ctrl_size(), ctrl_size() );
    view = in;
  }

#if 0
  /// Diff two control files given header offsets, return
  /// updated offsets for continued reading
  Ordinal diff(const Ctrl &c, const Scalar aeps, const Scalar reps) {
    return ctrl->diff(c, aeps, reps);
  }
#endif

  /// Take the Ctrl inner product of two control vectors.
  /** Does so on a particular time slice given the index. */
  Scalar inner_product( const Ordinal index, const dVector &Xphi,
                        const dVector &Yphi, const Control::Control_Type type) {
    if (verb)
      comm->cout() << "Control::Entry::inner_product() for " << name << endl;
    dVector Ydata;
    set_data( index, Xphi, type);
    load( index, Yphi, Ydata );
    if ( !ctrl->owner() ) return 0.0;
    return ctrl->inner_product( Ydata );
  }

  /// Compute the contribution to the total cost for this Ctrl and time-slice
  Scalar cost( const Ordinal index, const dVector &phi, 
               const Control::Control_Type type) {
    //if (ctrl->steady() && index>0) return 0.0;
    if (verb) comm->cout() << "Control::Entry::cost() for " << name << endl;
    set_data( index, phi, type);
    if ( !ctrl->owner() ) return 0.0;
    return ctrl->cost();
  }

  /// Bound the Ctrl data for timeslice=index
  void bound( const Ordinal index, dVector &phi) {
    if (ctrl->steady() && index>0) return;
    if (verb) comm->cout() << "Control::Entry::bound()" << endl;
    const Ordinal i = (ctrl->steady()) ? 0 : index;
    assert( i < ntime );
    dVector view;
    if (ctrl->owner())
      view.alias(phi, offset+i*ctrl_size(), ctrl_size() );
    ctrl->bound( view );
    get_data( index, phi);
  }

  /// Determine realizability for timeslice=index
  bool realizable( const Ordinal index, dVector &phi, 
                   const Control::Control_Type type) {
    if (ctrl->steady() && index>0) return true;
    if (verb) comm->cout() << "Control::Entry::realizable()" << endl;
    set_data( index, phi, type);
    bool result = ctrl->realizable();
    get_data( index, phi);
    return result;
  }

  // The following Entry methods are implemented in Control.cpp

  void gradient( const Ordinal istep, const Ordinal sstep, const dVector &phi,
                 const vField &S, const vField &A, dVector &Gphi, 
                 const Control::Control_Type type);

  void HessVecProd_reg(const Ordinal istep, const Ordinal sstep,
                       const dVector &x, const dVector &dx, dVector &H_dx);

  void computePreconditioner( const Ordinal istep, const Ordinal sstep,
                              const dVector &phi, const vField &S,
                              const vField &A, dVector &Gphi,
                              const Control::Control_Type type);

  void applyPreconditioner( const dVector &phi, const dVector &Gphi,
                            dVector &Pphi, const Control::Control_Type type);

  streamoff read(const string &fname, const streamoff skip, dVector &Gphi );

  streamoff write(const string &fname, const streamoff skip,
                  const dVector &Gphi);

  void plot(const vField&, const dVector &Gphi, const Ordinal, const Ordinal,
            const Ordinal, const Ordinal, 
            const string *ext=0, const int type=0) const;

  streamoff serial_read(const string &fname, const streamoff skip,
                        dVector &Gphi );

  streamoff serial_write(const string & fname, const streamoff skip,
                         const dVector &Gphi);

#ifdef DGM_PARALLEL
  streamoff mpi_read(const string &fname, const streamoff skip, dVector &Gphi );

  streamoff mpi_write(const string & fname, const streamoff skip,
                      const dVector &Gphi);
#endif

private:

};

} // namespace DGM

#endif  // DGM_CONTROL_HPP
