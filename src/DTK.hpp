#ifndef DTK_HPP
#define DTK_HPP

/** \file DTK.hpp
    \brief Discretization ToolKit (DTK)
    \author Scott Collis
    \author Bill Spotz
    \copyright 2014 &copy; Sandia National Laboratories
*/

// system includes
#include <string>
#include <typeinfo>
#include <limits>
#include <vector>

#include "DTK_Types.hpp"

/// Discretization Tool Kit namespace
/** The DTK (Discretization ToolKit) namespace largely provides a
    common set of templated, abstract base classes that define
    interfaces for software packages that support the forward and
    inverse solution of discretized partial differential equations
    (PDEs).

    The origin of DTK is DGM, a software package that enabled the
    solution of PDEs using the Discontinuous Galerkin Method.  By
    abstracting DGM concepts such as field, domain, adjoint, etc., and
    placing them in the DTK namespace, DTK now serves as a foundation
    for the development of new packages that support other
    discretization methods.  The first such package is FDM, the Finite
    Difference Method.  An example of the utility of DTK is that DGM
    fields live on unstructured meshes, while FDM fields live on
    structured meshes.  The implementations of these fields are quite
    different, but the DTK concept of field encapsulates both of them.

    This flexibility should enable the future development of other
    discretization packages, as the need arises: finite volume,
    spectral, spectral element, etc.

    Another advantage of DTK is that a variety of solvers, such as
    time integrators, linear solvers, nonlinear solvers, inverters,
    optimizers, etc., can be developed (or new interfaces to existing
    solvers can be developed) that work for multiple discretization
    methods and multiple underlying data structures.

    A final advantage of DTK is that it abstracts fundamental data
    types, using typedefs, such as scalar type, global ordinal type,
    and local ordinal type (where global refers to the global problem
    size across all processors, and local refers to local problem size
    on a single processor).
*/
namespace DTK {

  //************************************************************
  //************************************************************

  /// DTK exception class
  class exception : public std::exception
  {
    std::string message;     ///< error message

  public:

    /// \name Constructors and destructor
    ///@{

    //**********************************************************

    /// Construct on a string error message
    /** \param[in] msg  - Error message
      */
    exception(const std::string msg) :
      message(msg)
    {  }

    //**********************************************************

    /// Destructor
    ~exception() throw() {}

    ///@}

    //**********************************************************

    /// Override std::exception::what()
    virtual const char *what() const throw()
    {
      return message.c_str();
    }

    //**********************************************************

  };

  //************************************************************
  //************************************************************

  /// Base DTK object class
  /** Might be useful one day...
    */
  class Object
  {
  public:

    //**********************************************************

    /// Destructor
    virtual ~Object() {}

    //**********************************************************

  };

  //************************************************************
  //************************************************************

  /// Abstract DTK Problem definition
  class Problem : virtual public Object
  {
  public:

    //**********************************************************

    /// Destructor
    virtual ~Problem() {}

    //**********************************************************

  };

  //************************************************************
  //************************************************************

  /// Abstract DTK Domain definition
  /** \tparam Scalar       - Floating point type for Fields, etc.
      \tparam Ordinal      - Integer type for indexing
      \tparam VectorField  - Container of Fields; should derive from
                             DTK::VectorField

      A Domain refers to a set of Fields that live of the same Mesh,
      and is capable of performing forward time stepping.  A
      DTK::Domain therefore represents a discretized physical
      space-time domain.  Each discretization package (DGM, FDM, etc.)
      will partially implement its own Domain class that inherits from
      DTK::Domain.  These derived Domain classes will then serve as
      base classes for specific physics problems, with concrete
      implementations designed to solve a specific set of discretized
      PDEs.
    */
  template < typename Scalar,
             typename Ordinal,
             typename VectorField >
  class Domain : virtual public Object
  {
  public:

    //**********************************************************

    /// Specify the type of header to use for Domain I/O
    enum HeaderType
    {
      READ_HEADER=0,        ///< Read the Domain restart file header
      SKIP_HEADER=1         ///< Skip over the Domain restart file header
    };

    //**********************************************************

    /// Destructor
    virtual ~Domain() {}

    /// \name Solution methods
    ///@{

    //**********************************************************

    /// Solve method
    /** The solve() method should perform a forward time-stepping
        solve of the set of discretized PDEs.  The discretization
        packages (DGM, FDM, etc.) should leave this method virtual.
        It should be implemented by the concrete physics class.  Time
        stepping parameters can be obtained from other class members.
      */
    virtual int solve() = 0;

    //**********************************************************

    /// Time derivative method
    /** \param[in,out] U  - Solution vector field
        \param[out]    F  - Negative of the time derivative

        If the PDEs to be solved are expressed as dU/dt + F = 0, this
        method computes F at the current state.
      */
    virtual void time_derivative(VectorField & U,
                                 VectorField & F) = 0;

    //**********************************************************

    /// Time derivative method for split schemes
    /** \param[in,out] U     - Solution vector field
        \param[out]    F     - Negative of the time derivative
        \param[in]     step  - Substep number

        If the PDEs to be solved are expressed as dU/dt + F = 0, this
        method computes F at the current state for the given substep
        number.
      */
    virtual void time_derivative(VectorField & U,
                                 VectorField & F,
                                 Ordinal step) = 0;

    ///@}

    /// \name Time step information methods
    ///@{

    //**********************************************************

    /// Timestep get method
    /** Return the size of the time step
      */
    virtual Scalar timeStep() const = 0;

    //**********************************************************

    /// Step number get method
    /** Return the current time step number
      */
    virtual Ordinal stepNumber() const = 0;

    //**********************************************************

    /// Number of substep get method
    /** Return the number of substeps per time step used by the time
        integrator
      */
    virtual Ordinal get_sstep() const = 0;

    //**********************************************************

    /// Time get method
    /** Return the current value of the time
      */
    virtual Scalar time() const = 0;

    //**********************************************************

    /// Time set method
    /** Set the current value of the time
      */
    virtual void time(const Scalar time) = 0;

    //**********************************************************

    /// Get the total number of time steps to solve
    virtual Ordinal get_Nt() const = 0;

    ///@}

    //**********************************************************

    /// \name Time step control methods
    ///@{

    /// Prestep setup
    /** \todo Name and document method parameters
      */
    virtual void prestep(VectorField &,
                         const Ordinal,
                         const Ordinal,
                         const Scalar) = 0;

    //**********************************************************

    /// Poststep setup
    /** \todo Name and document method parameters
      */
    virtual void poststep(VectorField &,
                          const Ordinal,
                          const Ordinal,
                          const Scalar) = 0;

    //**********************************************************

    /// Final setup before calling advance method
    /** \todo Name and document method parameters
      */
    virtual void prepareToAdvance() = 0;

    //**********************************************************

    /// Apply source terms
    /** \param[in]     time  - Current value of the time
        \param[in]     S     - Input state vector field
        \param[in,out] R     - Input/output residual vector field

        Apply all of the sources associated with the Domain at the
        current time and state
      */
    virtual void applySource(const Scalar time,
                             const VectorField & S,
                             VectorField & R) = 0;

    //**********************************************************

    /// Apply boundary conditions
    /** \param[in]     time  - Current value of the time
        \param[in,out] R     - Input/output residual vector field

        Apply all of the boundary conditions associated with the
        Domain at the current time
      */
    virtual void applyBC(const Scalar time,
                         VectorField & R) = 0;

    ///@}

    /// \name Input/output methods
    ///@{

    //**********************************************************

    // These are currently causing Undefined Symbol link errors
    /// Read the local values of a VectorField from a file
    /** \param[in]  fname  - File name
        \param[out] F      - Returned vector field
        \param[in]  ht     - Header type
        \param[in]  saved_as_float - true to use float

        Local read method that should be implemented by the
        discretization package.
      */
    virtual void local_read(const std::string & fname,
                            VectorField & F,
                            const HeaderType ht=READ_HEADER,
                            const bool saved_as_float=false) = 0;

    //**********************************************************

    /// Read the local values of a VectorField from an istream
    /** \param[in]  fs     - Input file stream
        \param[out] F      - Returned vector field
        \param[in]  fname  - File name
        \param[in]  ht     - Header type
        \param[in]  saved_as_float - true to use float

        Local read method that should be implemented by the
        discretization package.
      */
    virtual void local_read(std::istream & fs,
                            VectorField & F,
                            const std::string & fname,
                            const HeaderType ht=READ_HEADER,
                            const bool saved_as_float=false) = 0;

    //**********************************************************

    /// Read the local values of a VectorField from a file
    /** \param[in]  fname  - File name
        \param[out] F      - Returned vector field

        Local read method that should be implemented by the
        discretization package.
      */
    virtual void local_read_field(const std::string & fname,
                                  VectorField & F) const = 0;

    //**********************************************************

    /// Write the local values of a VectorField to a file
    /** \param[in] fname  - File name
        \param[in] F      - Vector field to write
        \param[in] save_as_float - true to save as float

        Local write method that should be implemented by the
        discretization package.
     */
    virtual void local_write(const std::string & fname,
                             const VectorField & F,
                             const bool save_as_float=false) const = 0;

    //**********************************************************

    /// Write the local values of a VectorField to an ostream
    /** \param[in] fs     - Output file stream
        \param[in] F      - Vector field to write
        \param[in] fname  - File name
        \param[in] save_as_float - true to save as float

        Local write method that should be implemented by the
        discretization package.
    */
    virtual void local_write(std::ostream & fs,
                             const VectorField & F,
                             const std::string & fname,
                             const bool save_as_float=false) const =0;
    //@}

    /// \name Accessor methods

    //**********************************************************

    /// Get the root of the input filenames
    virtual std::string getRoot() const = 0;

    //**********************************************************

    /// Get the Domain's communicator.
    //--------------------------------
    // Note: it would be nice to have a virtual method here to force
    // sub-classes to implement it.  But I don't want a DGM object
    // (Comm) inserted into DTK.  For now, DGM::Domain and FDM::Domain
    // just implement this method without a virtual base class method,
    // which should still be OK for templated polymorphism.  Can we
    // move fully implemented Comm classes into DTK?
    //-----------------------------------------
    //const DGM::Comm::Ptr get_comm() const =0;

    //**********************************************************

    /// Get the state vector field
    virtual VectorField & getU() =0;

    ///@}

    //**********************************************************

    /// Generate a filename
    /** \param[in] iter   - Iteration number
        \param[in] istep  - Time step number
        \param[in] sstep  - Substep number
        \param[in] s      - File name base name
      */
    virtual std::string mkname(const Ordinal iter,
                               const Ordinal istep,
                               const Ordinal sstep,
                               const std::string & s) const = 0;

  };

  //************************************************************
  //************************************************************

  /// Abstract DTK Field definition
  /** \tparam Scalar   - Floating point type for Fields, etc.
      \tparam Ordinal  - Integer type for indexing

      \todo Fill out the Field interface a little bit
    */
  template < typename Scalar,
             typename Ordinal >
  class Field : virtual public Object
  {
  public:

    //**********************************************************

    /// Destructor
    virtual ~Field() {}

    //**********************************************************

  };

  //************************************************************
  //************************************************************

  /// Abstract DTK VectorField definition
  /** \tparam Scalar    - Floating point type for Fields, etc.
      \tparam Field     - Class for data on a distributed mesh;
                          should derive from DTK::Field
      \tparam SizeType  - Integer type for size of vector of fields

      \note Also need to define the following friends: add, scale, axpy
      \todo Make the friends members so they are part of design
    */
  template < typename Scalar,
             typename Field,
             typename Sizetype >
  class VectorField : virtual public Object
  {
  public:

    /// \name Public types
    ///@{
    /// Size type for indexing this VectorField
    typedef Sizetype size_type;
    /// Type of Fields held in this VectorField
    typedef Field    FieldType;
    ///@}

    //**********************************************************

    /// Destructor
    virtual ~VectorField() {}

    //**********************************************************

    /// \name Global fill methods
    ///@{

    /// Fill the vector field with zeros
    virtual void zero() = 0;

    //**********************************************************

    /// Set to a scalar constant value
    /** \param[in] a  - Fill value
      */
    virtual void fill(const Scalar a) = 0;

    //**********************************************************

    /// Fill the vector field with random values
    virtual void random() = 0;

    ///@}

    //**********************************************************

    /// Output appropriate norms
    virtual void norm() const = 0;

    //**********************************************************

    /// \name Accessors
    ///@{

    /// Return the size of the vector field
    virtual size_type size() const = 0;

    //**********************************************************

    /// Return lvalue access to the i-th field
    /** \param[in] i  - Field index
      */
    virtual Field * operator[](const size_type i) = 0;

    //**********************************************************

    /// Return the i-th field
    /** \param[in] i  - Field index
      */
    virtual const Field * operator[](const size_type i) const = 0;

    ///@}

  };

  //************************************************************

  /// Abstract DTK Mesh definition
  class Mesh : virtual public Object
  {
  public:
    virtual ~Mesh() {}
  };

  //************************************************************
  //************************************************************

  /// Abstract DTK Control definition
  /** \tparam Scalar        - Floating point type for Fields, etc.
      \tparam Ordinal       - Integer type for indexing
      \tparam VectorField   - Container of Fields; should derive from
                              DTK::VectorField
      \tparam ScalarVector  - Vector type for a local array of Scalars
      \tparam State         - State type; should derive from DTK::State
      \tparam MyControl     - Control type \note Why is this different from
                              the Control class we are defining?
  */
  template < typename Scalar,
             typename Ordinal,
             typename VectorField,
             typename ScalarVector,
             typename State,
             typename MyControl >
  class Control : virtual public Object
  {
  public:

    //**********************************************************

    /// \name Constructors and destructors
    ///@{

    /// Destructor
    virtual ~Control() {}

    //**********************************************************

    /// Return a pointer to a newly constructed copy of this Control object
    virtual Control* clone() const = 0;

    ///@}

    //**********************************************************

    /// \name Accessor methods
    ///@{

    /// Returns the number of entries in the Control database
    virtual size_t num_ctrl() const = 0;

    //**********************************************************

    /// Returns the local length of Control
    virtual size_t size() const = 0;

    //**********************************************************

    /// Returns the global length of phi for this Control
    virtual Ordinal global_size() const = 0;

    //**********************************************************

    /// Call the realizable method on each Ctrl object at each time/sub-step
    /** \param[in] istep  - Time step number
        \param[in] sstep  - Substep number
      */
    virtual bool realizable(const Ordinal istep,
                            const Ordinal sstep=0) = 0;

    //**********************************************************

    /// Call the realizable method on each Ctrl object for all time
    virtual bool realizable() = 0;

    //**********************************************************

    /// If any Control::Entry is unsteady then return false, otherwise true
    virtual bool steady() const = 0;

    //**********************************************************

    /// Accessor for the global (across a parallel processor) control length
    virtual Ordinal get_glen() const = 0;

    //**********************************************************

    /// Accessor that gives access to the State pointer
    virtual State* get_state() = 0;

    //**********************************************************

    /// Accessor for Control vector
    virtual const ScalarVector & get_phi() const = 0;
    ///@}

    /// \name Input/output
    ///@{

    //**********************************************************

    /// Outputs the costs to a supplied output stream
    virtual void output_costs(std::ostream &os) const = 0;

    //**********************************************************

    /// Plot the control
    /** \param[in] ntout  - Output frequency
        \param[in] iter   - Iteration index
        \param[in] ext    - File name extension
    */
    virtual void plot(const Ordinal ntout,
                      const Ordinal iter,
                      const std::string *ext = 0) const = 0;

    //**********************************************************

    /// Output the Control
    /** \param[in] iter  - Iteration
    */
    virtual void output(Ordinal iter) = 0;

    //**********************************************************

    /// Set the data on this Control
    /** \param[in] istep  - Time step number
        \param[in] sstep  - Substep number
    */
    virtual void set_data(const Ordinal istep,
                          const Ordinal sstep=0) = 0;

    //**********************************************************

    /// Load the Control by iterating over all entries
    /** \param[in,out] dcontrol - Control vector to load into
        \param[in] istep - Time step number
        \param[in] sstep - Substep number
    */
    virtual void load(ScalarVector & dcontrol,
                      const Ordinal istep,
                      const Ordinal sstep=0) const = 0;

    //**********************************************************

    /// Store the Control by iterating over all entries
    /** \param[in,out] dcontrol  - Control vector to store
        \param[in] istep   - Time step number
        \param[in] sstep   - Substep number
    */
    virtual void store(ScalarVector & dcontrol,
                       const Ordinal istep,
                       const Ordinal sstep=0) = 0;

    //**********************************************************

    /// Read the control from a file: needed for control restart
    /** \param[in] fname  - File name
        \param[in] skip   - Offset to skip
    */
    virtual std::streamoff read(const std::string & fname,
                                const std::streamoff skip) = 0;

    //**********************************************************

    /// Write the control to a file: needed for control restart
    /** \param[in] fname  - File name
        \param[in] skip   - Offset to skip
    */
    virtual std::streamoff write(const std::string & fname,
                                 const std::streamoff skip) = 0;

    //**********************************************************

    /// Gather control vector from across a parallel machine
    /** \param[in,out] output  - Vector of scalars to be gathered
    */
    virtual void gather(ScalarVector & output) const = 0;

    //**********************************************************

    /// Scatter control vector across parallel machine
    /** \param[in,out] input  - Vector of scalars to be scattered
    */
    virtual void scatter(ScalarVector & input) = 0;

    ///@}

    //**********************************************************

    /// \name Setup methods
    ///@{

    /// \brief Resizes and initializes to zero the individual
    /// observation costs
    virtual void reset_costs() = 0;

    //**********************************************************

    /// Resizes the local length of Control
    /** \param[in] n  - New size
    */
    virtual void resize(Ordinal n) = 0;

    //**********************************************************

    /// Initialize the Control
    virtual void initialize() = 0;

    //**********************************************************

    /// Zero out the Control
    virtual void zero() = 0;

    //**********************************************************

    /// \brief Set an arbitrary direction for finite difference
    /// gradient checks
    /** This is used to call each entries' set_direction() method.
        NOTE that the result is normalized by the norm of the
        resulting Control vector.
    */
    virtual void set_direction() = 0;

    ///@}

    /// \name Mathematical operations
    ///@{

    //**********************************************************

    /// \brief (Deprecated) Compute the total Control cost for one
    /// time-slab for all entries using trapezoid rule
    virtual Scalar cost() const = 0;

    //**********************************************************

    /// \brief Compute the total Control cost for one time-slab for
    /// all entries
    /** \param[in] istep  - Time step number
        \param[in] sstep  - Substep number
      */
    virtual Scalar cost(const Ordinal istep,
                        const Ordinal sstep=0) const = 0;

    //**********************************************************

    /// \brief Call the bound method on each Ctrl object at each
    /// time/sub step
    /** \param[in] istep  - Time step number
        \param[in] sstep  - Substep number
      */
    virtual void bound(const Ordinal istep,
                       const Ordinal sstep=0) = 0;

    //**********************************************************

    /// Call the bound method on each Ctrl object for all time
    virtual void bound() = 0;

    //**********************************************************

    /// Compute the inner-product between two Control objects
    /** \param[in] Y  - Control object for inner product
      */
    virtual Scalar inner_product(const MyControl * Y) const = 0;

    //**********************************************************

    /// Compute the inner-product between two Control objects
    /** \param[in] Y  - Control object for inner product
      */
    virtual Scalar inner_product(const MyControl & Y) const = 0;

    //**********************************************************

    /// Compute contribution to the gradient at one timestep
    /** \param[in]  S      - State vector field
        \param[in]  A      - Adjoint vector field
        \param[out] G      - Gradient Control
        \param[in]  istep  - Time step number
        \param[in]  sstep  - Substep number
      */
    virtual void gradient(const VectorField & S,
                          const VectorField & A,
                          MyControl & G,
                          const Ordinal istep,
                          const Ordinal sstep=0) = 0;

    //**********************************************************

    /// Compute Hessian vector product for the observation term
    /** \param[in]  S      - State vector field
        \param[in]  A      - Adjoint vector field
        \param[in]  x      - x argument
        \param[in]  dx     - dx argument
        \param[out] H_dx   - H_dx argument
        \param[in]  istep  - Time step number
        \param[in]  sstep  - Substep number
      */
    virtual void HessVecProd_obs(const VectorField & S,
                                 const VectorField & A,
                                 const MyControl & x,
                                 const MyControl & dx,
                                 MyControl & H_dx,
                                 const Ordinal istep,
                                 const Ordinal sstep=0) = 0;

    //**********************************************************

    /// Compute Hessian vector product for the regularization term
    /** \param[in]  x      - x argument
        \param[in]  dx     - dx argument
        \param[out] H_dx   - H_dx argument
        \param[in]  istep  - Time step number
        \param[in]  sstep  - Substep number
      */
    virtual void HessVecProd_reg(const MyControl & x,
                                 const MyControl & dx,
                                 MyControl & H_dx,
                                 const Ordinal istep,
                                 const Ordinal sstep=0) = 0;

    //**********************************************************

    /// Return the norm of the Control object
    virtual Scalar norm() const = 0;

    ///@}

    /// \name Preconditioning
    ///@{

    //**********************************************************

    /// \brief Compute a contribution to a diagonal preconditioner at
    /// one timestep
    /** \param[in]  S      - State vector field
        \param[in]  A      - Adjoint vector field
        \param[out] P      - Preconditioner
        \param[in]  istep  - Time step number
        \param[in]  sstep  - Substep number
      */
    virtual void computePreconditioner(const VectorField & S,
                                       const VectorField & A,
                                       MyControl & P,
                                       const Ordinal istep,
                                       const Ordinal sstep=0) = 0;

    //**********************************************************

    /// Apply a preconditioner
    /** \param[in]  G  - Gradient
        \param[out] P  - Preconditioned gradient
      */
    virtual void applyPreconditioner(const MyControl & G,
                                     MyControl & P) = 0;

    ///@}
  };

  //************************************************************
  //************************************************************

  /// Abstract DTK Objective definition
  /** \tparam Scalar        - Floating point type for Fields, etc.
      \tparam Ordinal       - Integer type for indexing
      \tparam VectorField   - Container of Fields; should derive from
                              DTK::VectorField
      \tparam ScalarVector  - Vector type for a local array of Scalars
      \tparam State         - State type; should derive from DTK::State
    */
  template < typename Scalar,
             typename Ordinal,
             typename VectorField,
             typename ScalarVector,
             typename State >
  class Objective : virtual public Object
  {
  public:

    //**********************************************************

    /// Destructor
    virtual ~Objective() {}

    //**********************************************************

    /// \name Accessor methods
    ///@{

    /// Returns the number of observation terms in this objective
    virtual size_t num_obs() const = 0;

    //**********************************************************

    /// Returns the names for each Obs in this Objective
    virtual std::vector<std::string> names() const = 0;

    //**********************************************************

    /// State accessor
    virtual State * get_state() const = 0;

    ///@}

    //**********************************************************

    /// \name Setup methods
    ///@{

    /// Sets the Obs data from the given vField and timestep
    /** \param[in] state  - State vector field
        \param[in] istep  - Time step number
        \param[in] sstep  - Substep number
      */
    virtual void set_data(const VectorField & state,
                          const Ordinal istep,
                          const Ordinal sstep=0) = 0;

    //**********************************************************

    /// Reset individual Obs(ervations) with no prescribed data
    virtual void reset() = 0;

    //**********************************************************

    /// Reset individual Obs(ervations) with a prescribed data message
    /** \param[in] name  - Name of observation to reset
        \param[in] data  - Reset data
      */
    virtual void reset(const std::string name,
                       const ScalarVector & data) = 0;

    ///@}

    //**********************************************************

    /// Applies the end conditions for each Obs
    /** \param[in,out] S  - State vector field
      */
    virtual void end_condition(VectorField & S) = 0;

    //**********************************************************

    /// \name Cost methods
    ///@{

    /// Computes the cost associated with one time-slab
    /** \param[in] S      - State vector field
        \param[in] istep  - Time step number
        \param[in] sstep  - Substep number
      */
    virtual Scalar cost(const VectorField & S,
                        const Ordinal istep,
                        const Ordinal sstep= 0) const = 0;

    //**********************************************************

    /// Computes the time-integrated costs
    virtual Scalar cost() const = 0;

    //**********************************************************

    /// Return the vector of current costs
    virtual ScalarVector get_costs() const = 0;

    //**********************************************************

    /// Compute the terminal cost(s) for this objective
    /** \param[in] S      - State vector field
        \param[in] istep  - Time step number
      */
    virtual Scalar terminal_cost(const VectorField & S,
                                 const Ordinal istep) const = 0;

    //**********************************************************

    /// Resizes and initializes to zero the individual observation costs
    virtual void reset_costs() = 0;

    //**********************************************************

    /// Outputs the current individual costs to an output stream.
    /** \param[in] os  - Output stream
      */
    virtual void output_costs(std::ostream & os) const = 0;

    ///@}

  };

  //************************************************************
  //************************************************************

  /// Abstract DTK Objective Function
  /** \tparam Scalar       - Floating point type for Fields, etc.
      \tparam Ordinal      - Integer type for indexing
      \tparam VectorField  - Container of Fields; should derive from
                             DTK::VectorField
    */
  template < typename Scalar,
             typename Ordinal,
             typename VectorField >
  class ObjFunc : virtual public Object
  {
  public:
    virtual ~ObjFunc() {}

    //**********************************************************

    /// Evaluate the objective function
    /** \param[in] state  - State vector field
        \param[in] istep  - Time step number
        \param[in] sstep  - Substep number
      */
    virtual Scalar evaluate(const VectorField & state,
                            const Ordinal istep,
                            const Ordinal sstep=0) = 0;

    //**********************************************************

    /// Evaluate the terminal condition
    /** \param[in] state  - State vector field
        \param[in] istep  - Time step number
        \param[in] sstep  - Substep number
      */
    virtual Scalar terminal(const VectorField & state,
                            const Ordinal istep,
                            const Ordinal sstep=0) = 0;
  };

  //************************************************************
  //************************************************************

  /// Abstract DTK State definition
  /** \tparam Control       - Control type; should derive from DTK::Control
      \tparam Objective     - Objective type; should derive from DTK::Objective
      \tparam VectorField   - Container of Fields; should derive from
                              DTK::VectorField
      \tparam ScalarVector  - Vector type for a local array of Scalars
      \tparam Scalar        - Floating point type for Fields, etc.
      \tparam Ordinal       - Integer type for indexing
    */
  template < typename Control,
             typename Objective,
             typename VectorField,
             typename ScalarVector,
             typename Scalar,
             typename Ordinal >
  class State : virtual public Object
  {
  protected:

    mutable int testflag;  ///< true indicates that a "test" should be computed
    std::string tag;       ///< Tag for the current state database

  public:

    /// \name Constructors and destructor
    ///@{

    //**********************************************************

    /// Constructor
    State() : testflag(0), tag() {}

    //**********************************************************

    /// Destructor
    virtual ~State() {}

    ///@}

    /// \name State Interface
    ///@{

    //**********************************************************

    /// \name Setup methods
    ///@{

    /// Sets initial condition, scratch and stores in database
    virtual void initialize() = 0;

    //**********************************************************

    /// Initialize to given vector at given time and step
    /** \param[in] data  - New state data
        \param[in] t     - Time
        \param[in] step  - Time step number

        Defaults to undefined, must (if used) be supplied by derived
        class
      */
    virtual void initialize(const ScalarVector & data,
                            const Scalar t=0.0,
                            const Ordinal step=0) = 0;

    //**********************************************************

    /// Calls Domain::set_ic()
    virtual void set_initial_condition() = 0;

    //**********************************************************

    /// Sets the State to data at time t and timestep step
    /** \param[in] data  - New state data
        \param[in] t     - Time
        \param[in] step  - Time step number
      */
    virtual void set_initial_condition(const ScalarVector & data,
                                       const Scalar t=0.0,
                                       const Ordinal step=0) = 0;

    //**********************************************************

    /// Sets the State Control pointer
    /** \param[in] ctrl  - Pointer to Control object
      */
    virtual void set_control(Control *ctrl) = 0;

    //**********************************************************

    /// Sets the State objective pointer
    /** \param[in] obj  - Pointer to Objective object
      */
    virtual void set_objective(Objective *obj) = 0;

    //**********************************************************

    /// Turn off saving every step and substep
    virtual void no_save()
    {
      testflag = 1;
    }

    //**********************************************************

    /// Set the current database tag
    /** \param[in] newtag  - New tag name
      */
    virtual void set_tag(const std::string newtag)
    {
      tag = newtag;
    }

    ///@}

    /// \name State computation methods
    ///@{

    //**********************************************************

    /// Compute state nsteps using control for optimization (iter)ation
    /** \param[in] nsteps   - Number of steps
        \param[in] control  - Pointer to control object
        \param[in] iter     - Iteration number
      */
    virtual Scalar compute(const Ordinal nsteps,
                           typename Control::Ptr control,
                           const Ordinal iter=0) = 0;

    //**********************************************************

    /// Do a test state solution (no storage) for nsteps using supplied control
    /** \param[in] nsteps   - Number of steps
        \param[in] control  - Pointer to control object
      */
    virtual Scalar test(const Ordinal nsteps,
                        typename Control::Ptr control) = 0;

    //**********************************************************

    /// Advance state nsteps using supplied control on outer iteration
    /** \param[in] nsteps   - Number of steps
        \param[in] control  - Pointer to control object
        \param[in] outer    - Outer iteration number
      */
    virtual Scalar advance(const Ordinal nsteps,
                           typename Control::Ptr control,
                           const Ordinal outer=0) = 0;

    ///@}

    /// \name Input/output methods
    ///@{

    //**********************************************************

    /// Store VectorField in the State database
    /** \param[in] F      - Vector field to store
        \param[in] istep  - Time step number
        \param[in] sstep  - Substep number
      */
    virtual void store(VectorField & F,
                       const Ordinal istep,
                       const Ordinal sstep=0) = 0;

    //**********************************************************

    /// Load VectorField from the State database
    /** \param[in] F      - Vector field to load from
        \param[in] istep  - Time step number
        \param[in] sstep  - Substep number
      */
    virtual void load(VectorField & F,
                      const Ordinal istep,
                      const Ordinal sstep=0) = 0;

    //**********************************************************

    /// Load VectorField from the State database but skip the header
    /** \param[in] F      - Vector field to load from
        \param[in] istep  - Time step number
        \param[in] sstep  - Substep number
      */
    virtual void load_field(VectorField & F,
                            const Ordinal istep,
                            const Ordinal sstep=0) const = 0;

    //**********************************************************

    /// Turn on saving every step and substep
    /** \param[in] newtag  - New tag name
      */
    virtual void save(const std::string newtag=std::string(""))
    {
      testflag = 0;
      tag = newtag;
    }

    ///@}

    /// \name Accessor methods
    ///@{

    //**********************************************************

    /// Return the Control for this State
    virtual const Control* get_control() const = 0;

    //**********************************************************

    /// Return the Control for this State
    virtual Control* get_control() = 0;

    //**********************************************************

    /// Return the Objective for this State
    virtual Objective* get_objective() = 0;

    //**********************************************************

    /// Return the Objective for this State
    virtual const Objective* get_objective() const = 0;

    //**********************************************************

    /// Return the current database tag
    virtual std::string get_tag() const
    {
      return tag;
    }

    ///@}

  };

  //************************************************************
  //************************************************************

  /// Abstract DTK Adjoint definition
  /** \tparam Control       - Control type; should derive from DTK::Control
      \tparam Objective     - Objective type; should derive from DTK::Objective
      \tparam VectorField   - Container of Fields; should derive from
                              DTK::VectorField
      \tparam ScalarVector  - Vector type for a local array of Scalars
      \tparam Scalar        - Floating point type for Fields, etc.
      \tparam Ordinal       - Integer type for indexing
      \tparam Domain        - Domain type; should derive from DTK::Domain
    */
  template < typename Control,
             typename Objective,
             typename VectorField,
             typename ScalarVector,
             typename Scalar,
             typename Ordinal,
             typename Domain >
  class Adjoint : virtual public Object
  {
  public:

    //**********************************************************

    /// Destructor
    virtual ~Adjoint() {}

    /// \name Adjoint Interface
    ///@{

    //**********************************************************

    /// \name Setup methods
    ///@{

    /// Initialize the adjoint
    virtual void initialize() = 0;

    //**********************************************************

    /// Set the adjoint end condition
    virtual void set_end_condition() = 0;

    //**********************************************************

    /// Set end condition to a prescribed data at time and timestep
    /** \param[in] X     - Values for the end condition
        \param[in] t     - Time of the end condition
        \param[in] step  - Time step at the end condition
     */
    virtual void set_end_condition(const ScalarVector & X,
                                   const Scalar t=0.0,
                                   const Ordinal step=0) = 0;

    //**********************************************************

    /// Set the objective function for this adjoint
    /** \param[in] obj  - New objective object
      */
    virtual void set_objective(Objective *obj) = 0;

    ///@}

    /// \name Adjoint computation methods
    ///@{

    //**********************************************************

    /// Compute the adjoint nsteps using supplied control and gradient
    /** \param[in] npredict   - define
        \param[in] control    - define
        \param[in] gradient   - define
        \param[in] iteration  - define
      */
    virtual void compute(const Ordinal         npredict,
                         typename Control::Ptr control,
                         typename Control::Ptr gradient,
                         const Ordinal         iteration=0) = 0;

    //**********************************************************

    /// Compute the gradient given the adjoint and state solutions
    /** \param[in] A      - Adjoint solution
        \param[in] S      - State solution
        \param[in] istep  - Current time step
        \param[in] sstep  - Current sub-step (optional)
     */
    virtual void computeGrad(VectorField & A,
                             VectorField & S,
                             Ordinal       istep,
                             Ordinal       sstep) = 0;

    ///@}

    /// \name Input/output methods
    ///@{

    //**********************************************************

    /// Store the adjoint
    /** \param[in] Uf     - Vector field to store
        \param[in] istep  - Time step number
        \param[in] sstep  - Substep number
      */
    virtual void store(VectorField & Uf,
                       const Ordinal istep,
                       const Ordinal sstep=0) = 0;

    //**********************************************************

    /// Load the adjoint
    /** \param[out] Uf     - Vector field to load
        \param[in]  istep  - Time step number
        \param[in]  sstep  - Substep number
      */
    virtual void load(VectorField & Uf,
                      const Ordinal istep,
                      const Ordinal sstep=0) = 0;

    //**********************************************************

    /// Load the adjoint skipping the header
    /** \param[out] Uf     - Vector field to load
        \param[in]  istep  - Time step number
        \param[in]  sstep  - Substep number
      */
    virtual void load_field(VectorField & Uf,
                            const Ordinal istep,
                            const Ordinal sstep=0) const = 0;

    ///@}

    /// \name Accessor methods
    ///@{

    //**********************************************************

    /// Returns the const Domain
    virtual const Domain* domain() const = 0;

    //**********************************************************

    /// Returns the Domain
    virtual Domain* domain() = 0;

    ///@}
  };

  //===========================================================================
  //                        Lower level DTK objects
  //===========================================================================

  //************************************************************
  //************************************************************

  /// Abstract DTK Ctrl definition
  /** \tparam VectorField   - Container of Fields; should derive from
                              DTK::VectorField
      \tparam ScalarVector  - Vector type for a local array of Scalars
      \tparam Scalar        - Floating point type for Fields, etc.
      \tparam Size          - Integer type for container size
      \tparam Ordinal       - Integer type for indexing
      \tparam SizeVector    - Vector type for a local array of Size
      \tparam OrdinalVector - Vector type for a local array of Ordinal

      Abstract template base class for all simulation objects that can act as
      control variables.
   */
  template < typename VectorField,
             typename ScalarVector,
             typename Scalar,
             typename Size,
             typename Ordinal,
             typename SizeVector,
             typename OrdinalVector>
  class Ctrl : virtual public Object
  {
  public:

    //**********************************************************

    /// Destructor
    virtual ~Ctrl() {}

    //**********************************************************

    /// \name Setup methods
    ///@{

    /// Initialize the Ctrl data vector to zero
    virtual void initialize() = 0;

    //**********************************************************

    /// Set the parallel I/O status
    /** \param[in] replicated  - Parallel I/O status
      */
    virtual void replicated(const bool replicated) = 0;

    //**********************************************************

    /// Set the Ctrl storage vector to the input vector
    /** \param[in] in  - Input data
      */
    virtual void set_data(const ScalarVector & in) = 0;

    //**********************************************************

    /// Finalize the Ctrl for use by the simulator
    virtual void finalize() = 0;

    //**********************************************************

    /// Fill the output vector
    /** \param[in]  t    - Time
        \param[out] out  - Output vector
      */
    virtual void fill(const Scalar t,
                      ScalarVector & out) const = 0;

    //**********************************************************

    /// Set whether this processor rank owns this Ctrl
    /** \param[in] owner  - True for ownership
      */
    virtual void owner(const bool owner) = 0;

    //**********************************************************

    /// Sets the size of the data vector
    /** \param[in] size_in  - Data vector size
      */
    virtual void set_size(const Ordinal size_in) = 0;

    //**********************************************************

    /// Set a prescribed direction for use in directional derivative evaluation
    /** \param[out] out  - The returned direction
      */
    virtual void set_direction(ScalarVector & out) = 0;

    ///@}

    /// \name Accessor methods
    ///@{

    //**********************************************************

    /// Determine if this processor rank owns this Ctrl
    virtual bool owner() const = 0;

    //**********************************************************

    /// Determine parallel IO status
    virtual bool replicated() const = 0;

    //**********************************************************

    /// Extract the Ctrl data vector into the output vector
    /** \param[out] out  - Output vector
      */
    virtual void get_data(ScalarVector & out) const = 0;

    //**********************************************************

    /// Returns true if fill is overloaded
    virtual bool has_fill() const = 0;

    //**********************************************************

    /// Returns the size of the Ctrl data vector
    virtual Ordinal data_size() const = 0;

    //**********************************************************

    /// Returns the size or length of the data vector
    virtual Ordinal get_size() const = 0;

    //**********************************************************

    /// Method to return if realizable
    virtual bool realizable()
    {
      return true;
    }

    //**********************************************************

    /// Default to unsteady control
    virtual bool steady() const = 0;

    //**********************************************************

    /// Allows the Ctrl to be self-aware regarding the data layout in parallel
    /** \param[out] glen  - Global length
        \param[out] disp  - Displacement
        \param[out] len   - Lengths

        The default implementation just returns "false" indicating
        that this Ctrl does not know its parallel information yet
     */
    virtual bool get_parallel_info(Size &glen,
                                   SizeVector &disp,
                                   OrdinalVector &len) const
    {
      return false;
    }

    ///@}

    /// \name Mathematical operations
    ///@{

    //**********************************************************

    /// Define the inner product operation for this Ctrl \f$\bX\cdot\bY\f$
    /** \param[in] Y  - Inner product operand
      */
    virtual Scalar inner_product(const ScalarVector & Y) const = 0;

    //**********************************************************

    /// Returns the appropriate norm for this Ctrl
    virtual Scalar norm() const = 0;

    //**********************************************************

    /// Returns the cost of the Ctrl that appears in the objective functional
    virtual Scalar cost() const = 0;

    //**********************************************************

    /// Computes the gradient of the objective functional wrt the Ctrl
    /** \param[in]     S  - The current State
        \param[in]     A  - The current Adjoint
        \param[in]  time  - The current time
        \param[in,out] G  - The gradient
     */
    virtual void objective_function_gradient( const VectorField & S,
                                              const VectorField & A,
                                              const Scalar time,
                                              ScalarVector & G ) const = 0;

    //**********************************************************

    /// Method to specify bounding of the control
    virtual void bound(const ScalarVector &) = 0;

    ///@}

    /// \name Preconditioner methods
    ///@{

    //**********************************************************

    /// Applies a preconditioner to the current Ctrl object
    /** \param[in]  G  - The gradient object to apply the preconditioner too
        \param[out] P  - The preconditioned gradient object

        Default implementation is the identity
     */
    virtual void applyPreconditioner(const ScalarVector &G,
                                     ScalarVector &P) const
    {}

    //**********************************************************

    /// Computes a contribution to a preconditioner
    /** \param[in]  S  - The current State
        \param[in]  A  - The current Adjoint
        \param[out] P  - The preconditioned Ctrl object

        This interface allow one to compute contributions to a
        precondition for a transient problem.  Default implementation
        is the identity.
     */
    virtual void computePreconditioner(const VectorField &S,
                                       const VectorField &A,
                                       ScalarVector &P ) const
    {}

    //**********************************************************

    /// Returns true if compute preconditioner is required
    /** This lets the implementation query whether
        computePreconditioner is needed for this particular Ctrl
        object.  This can be used to reduce both memory and compute
        requirements.
     */
    virtual bool needsComputePreconditioner() const
    {
      return false;
    }

    ///@}

    /// \name Output methods
    ///@{

    //**********************************************************

    /// Output the control to std::cout
    virtual void output() const = 0;

    //**********************************************************

    /// Plot the Ctrl
    /** \param[in] state     - Current state
        \param[in] offset    - Offset
        \param[in] Gphi      - Gphi?
        \param[in] npredict  - Number of predictions?
        \param[in] ntout     - Output frequency
        \param[in] nsstep    - Number of substeps
        \param[in] riter     - riter?
      */
    virtual void plot( const VectorField & state,
                       const Size offset,
                       const ScalarVector & Gphi,
                       const Ordinal npredict,
                       const Ordinal ntout,
                       const Ordinal nsstep,
                       const Ordinal riter) const = 0;

    //**********************************************************

    /// Plot the Ctrl with a different filename
    /** \param[in] state     - Current state
        \param[in] offset    - Offset
        \param[in] Gphi      - Gphi?
        \param[in] npredict  - Number of predictions?
        \param[in] ntout     - Output frequency
        \param[in] nsstep    - Number of substeps
        \param[in] riter     - riter?
        \param[in] fname     - File name
        \param[in] type      - Type of output file
      */
    virtual void plot(const VectorField & state,
                      const Size offset,
                      const ScalarVector & Gphi,
                      const Ordinal npredict,
                      const Ordinal ntout,
                      const Ordinal nsstep,
                      const Ordinal riter,
                      const std::string &fname,
                      const int type=0) const = 0;

    ///@}

  };

  //************************************************************
  //************************************************************

  /// Abstract DTK Observation definition
  /** \tparam VectorField   - Container of Fields; should derive from
                              DTK::VectorField
      \tparam ScalarVector  - Vector type for a local array of Scalars
      \tparam Scalar        - Floating point type for Fields, etc.
      \tparam Ordinal       - Integer type for indexing

      Abstract, templated base class for all objects that can act as
      observation variables.
   */
  template < typename VectorField,
             typename ScalarVector,
             typename Scalar,
             typename Ordinal >
  class Obs : virtual public Object
  {
  public:

    //**********************************************************

    virtual ~Obs() {}

    /// \name Setup methods
    ///@{

    //**********************************************************

    /// Initialize this observation
    virtual void initialize() = 0;

    //**********************************************************

    /// Set the Obs data on a given VectorField at timestep (and substep)
    /** \param[in] U      - State to observe
        \param[in] istep  - Time step number
        \param[in] sstep  - Substep for RK methods (optional)
     */
    virtual void set_data(const VectorField &U,
                          const Ordinal istep,
                          const Ordinal sstep=0) = 0;

    //**********************************************************

    /// Apply the end condition to the Adjoint
    /** \param[in] A - Adjoint VectorField on which to apply the
                       end-condition
      */
    virtual void end_condition(VectorField & A) = 0;

    //**********************************************************

    /// Reset the objective function
    /** This is useful with the data or parameters of the objective
        functional need to be updated during the solution of an
        optimization problem.  The default is a zero operation so this
        needs to be overriden in a derived class to define a useful
        action for that observation.
     */
    virtual void reset_obs() {};

    //**********************************************************

    /// Reset the objective function
    /** This is useful with the data or parameters of the objective
        functional need to be updated during the solution of an
        optimization problem.  The default is a zero operation so this
        needs to be overriden in a derived class to define a useful
        action for that observation.
     */
    virtual void reset_obs( const ScalarVector & ) {};

    ///@}

    /// \name Mathematical operations
    ///@{

    //**********************************************************

    /// Compute the norm of this observation (in space-time)
    virtual Scalar norm() const = 0;

    ///@}

    /// \name Cost methods
    ///@{

    //**********************************************************

    /// Compute cost of this observation
    virtual Scalar cost() const = 0;

    //**********************************************************

    /// Override to provide a terminal observation
    virtual Scalar terminal_cost() const = 0;

    ///@}

    /// \name Accessor methods
    ///@{

    //**********************************************************

    /// Returns the number of observation terms
    /** Normally each Obs object represents one observation term in
        the objective function.  However, it is also useful to have a
        collection of similar observations actually collected and
        treated as a single Obs object with a number of term.  This
        method returns the number of terms (defaults to 1) in this Obs
     */
    virtual Ordinal Nterms() const
    {
      return 1;
    }

    ///@}

  };

  //************************************************************
  //************************************************************

  /// Abstract DTK Boundary Condition (BC) definition
  /** \tparam VectorField   - Container of Fields; should derive from
                              DTK::VectorField
      \tparam ScalarVector  - Vector type for a local array of Scalars
      \tparam Scalar        - Floating point type for Fields, etc.
      \tparam Ordinal       - Integer type for indexing
    */
  template < typename VectorField,
             typename ScalarVector,
             typename Scalar,
             typename Ordinal >
  class BC : virtual public Object
  {
  public:

    //**********************************************************

    typedef typename Shared< BC< VectorField,
                                 ScalarVector,
                                 Scalar,
                                 Ordinal> >::Ptr Ptr;

    //**********************************************************

    /// Destructor
    virtual ~BC() {};

    /// \name Boundary condition computation
    ///@{

    //**********************************************************

    /// Apply the boundary condition at a specific time
    /** \param[in] t  - Time
        \param[in] F  - define
     */
    virtual void apply(const Scalar t,
                       const VectorField & F) = 0;

    //**********************************************************

    /// Apply a flux-type boundary condition
    /** \param[in] t  - Time
        \param[in] F  - define
     */
    virtual void apply_flux(const Scalar t,
                            const VectorField & F) = 0;

    //**********************************************************

    /// Apply a linearized boundary condition
    /** \param[in] t   - Time
        \param[in] Fm  - define
        \param[in] F   - define
     */
    virtual void linear_apply(const Scalar t,
                              const VectorField & Fm,
                              const VectorField & F) = 0;

    //**********************************************************

    /// Apply a linearized boundary condition
    /** \param[in] t   - Time
        \param[in] Fm  - define
        \param[in] F   - define
     */
    virtual void linear_apply_flux(const Scalar t,
                                   const VectorField & Fm,
                                   const VectorField &F) = 0;

    //**********************************************************

    /// Apply the adjoint boundary condition
    /** \param[in] t   - Time
        \param[in] Fm  - define
        \param[in] F   - define
     */
    virtual void adjoint_apply(const Scalar t,
                               const VectorField & Fm,
                               const VectorField & F) = 0;

    //**********************************************************

    /// Apply the adjoint flux-type boundary condition
    /** \param[in] t        - Time
        \param[in] state    - State vector field
        \param[in] adjoint  - Adjoint ector field
     */
    virtual void adjoint_apply_flux(const Scalar t,
                                    const VectorField &state,
                                    const VectorField &adjoint) = 0;

    //**********************************************************

    /// Apply the matrix boundary condition at a specific time
    /** \param[in] t  - Time
        \param[in] F  - define
     */
    virtual void matrix_apply(const Scalar t,
                              const VectorField & F) = 0;

    //**********************************************************

    /// Apply a matirx flux-type boundary condition
    /** \param[in] t  - Time
        \param[in] F  - define
     */
    virtual void matrix_apply_flux(const Scalar t,
                                   const VectorField & F) = 0;

    //**********************************************************

    ///@}
  };

  //************************************************************
  //************************************************************

  /// Abstract DTK Model definition
  /** \tparam VectorField   - Container of Fields; should derive from
                              DTK::VectorField
      \tparam ScalarVector  - Vector type for a local array of Scalars
      \tparam Scalar        - Floating point type for Fields, etc.
      \tparam Ordinal       - Integer type for indexing
    */
  template < typename VectorField,
             typename ScalarVector,
             typename Scalar,
             typename Ordinal >
  class Model : virtual public Object
  {
  public:

    //**********************************************************

    virtual ~Model() {}

    //**********************************************************

  };

  //************************************************************
  //************************************************************

  /// Abstract DTK Source definition
  /** \tparam VectorField   - Container of Fields; should derive from
                              DTK::VectorField
      \tparam ScalarVector  - Vector type for a local array of Scalars
      \tparam Scalar        - Floating point type for Fields, etc.
      \tparam Ordinal       - Integer type for indexing
      \tparam Ctrl          - Ctrl type; should derive from DTK::Ctrl
      \tparam Obs           - Obs type; should derive from DTK::Obs
    */
  template < typename VectorField,
             typename ScalarVector,
             typename Scalar,
             typename Ordinal,
             typename Ctrl,
             typename Obs >
  class Source : virtual public Object
  {
  protected:

    bool _linearized;   ///< True if this source is for a linearized problem

  public:

    std::string type;

    /// \name Constructors and destructor
    ///@{

    //**********************************************************

    /// Constructor
    /** \param[in] t  - Soource type
      */
    Source(const std::string t) :
      _linearized(false),
      type(t)
    {}

    //**********************************************************

    /// Destructor
    virtual ~Source() {}

    ///@}

    /// \name Source computation methods
    ///@{

    //**********************************************************

    /// State apply method
    /** \param[in]     time  - Time
        \param[in]     S - State vector field
        \param[in,out] F - Vector field to apply the source to
      */
    virtual void apply(const Scalar time,
                       const VectorField & S,
                       VectorField & F) = 0;

    //**********************************************************

    /// Adjoint apply method
    /** \param[in]     time  - Time
        \param[in]     state - Current state vector field
        \param[in]     adjoint - Current adjoint vector field
        \param[in,out] F  - Adjoint vector field to apply the source to
      */
    virtual void adjoint_apply(const Scalar time,
                               const VectorField &state,
                               const VectorField &adjoint,
                               VectorField & F) = 0;
    ///@}

    /// \name Setup methods
    ///@{

    //**********************************************************

    /// Provides a modifyable reset method
    /** \param[in] weights  - Relative amplitudes of sources
      */
    virtual void reset_source(const ScalarVector & weights) = 0;

    //**********************************************************

    /// Set the linearized status (and adjust accordingly if overloaded)
    /** \param[in] linearized  - Linearized flag
      */
    virtual void linearized(const bool linearized)
    {
      _linearized = linearized;
    }

    ///@}

    /// \name Accessor methods
    ///@{

    //**********************************************************

    /// Return the number of sources
    virtual Ordinal Nsources() const = 0;

    //**********************************************************

    /// determine if linearized
    virtual bool linearized() const
    {
      return _linearized;
    }

    //**********************************************************

    /// Returns a pointer to a Ctrl object
    virtual Ctrl * ctrl() { return 0; }

    //**********************************************************

    /// Returns a constant pointer to a Ctrl object
    virtual const Ctrl * ctrl() const { return 0; }

    //**********************************************************

    /// Returns a pointer to an Obs object (if applicable)
    virtual Obs * obs() { return 0; }

    //**********************************************************

    /// Returns a constant pointer to an Obs object (if applicable)
    virtual const Obs * obs() const { return 0; }

    ///@}

  };

  //************************************************************
  //************************************************************

  /// Abstract DTK Parameter definition
  /** \tparam VectorField   - Container of Fields; should derive from
                              DTK::VectorField
      \tparam ScalarVector  - Vector type for a local array of Scalars
      \tparam Scalar        - Floating point type for Fields, etc.
      \tparam Ordinal       - Integer type for indexing
    */
  template < typename VectorField,
             typename ScalarVector,
             typename Scalar,
             typename Ordinal >
  class Parameter : virtual public Object
  {
  public:

    //**********************************************************

    /// Destructor
    virtual ~Parameter() { }

    //**********************************************************

  };

  //************************************************************
  //************************************************************

  /// Abstract base class for a term in the governing equations
  /** \tparam VectorField   - Container of Fields; should derive from
                              DTK::VectorField
      \tparam ScalarVector  - Vector type for a local array of Scalars
      \tparam Scalar        - Floating point type for Fields, etc.
      \tparam Ordinal       - Integer type for indexing
    */
  template < typename VectorField,
             typename ScalarVector,
             typename Scalar,
             typename Ordinal >
  class Term : virtual public Object
  {
  public:

    //**********************************************************

    /// Destructor
    virtual ~Term() {}

    //**********************************************************

    /// Apply the operator
    /** \param[in,out] U - Current solution vector field
        \param[in,out] F - Current flux vector field
        \param[in,out] R - Current residual vector field
      */
    virtual void operator()(VectorField & U,
                            VectorField & F,
                            VectorField & R) = 0;

    //**********************************************************

  };

  //************************************************************
  //************************************************************

  /// DTK abstract linear operator
  /** \tparam Scalar        - Floating point type for Fields, etc.
      \tparam ScalarVector  - Vector type for a local array of Scalars
   */
  template < typename Scalar,
             typename ScalarVector >
  class Operator
  {
  public:

    //**********************************************************

    // Allow a derived class to deallocate memory
    virtual ~Operator() {}

    //**********************************************************

    // Basic application
    /** \param[in]  x  - Input scalar vector
        \param[out] y  - Output scalar vector
     */
    virtual void operator()(const ScalarVector & x,
                            ScalarVector & y) const = 0;

  };

  //************************************************************
  //************************************************************

  /// Abstract DTK Regularization
  /** \tparam Scalar          - Floating point type for Fields, etc.
      \tparam ScalarVector    - Vector type for a local array of Scalars
      \tparam ControlDataType - Data type for control object
   */
  template < typename Scalar,
             typename ScalarVector,
             typename ControlDataType=ScalarVector >
  class Regularization
  {
  public:

    //**********************************************************

    /// Allow a derived class to deallocate memory
    virtual ~Regularization() {}

    /// \name Mathematical operations
    ///@{

    //**********************************************************

    /// Computes f(x)
    virtual Scalar operator()(const ControlDataType & x) const = 0;

    //**********************************************************

    /// Computes f(x) where, optionally, return terms within f
    virtual Scalar operator()(const ControlDataType & x,
                              ScalarVector & f) const = 0;

    //**********************************************************

    /// g = grad f(x)
    /** \param[in]  x  - Input control vector
        \param[out] g  - Output gradient of f(x)
    */
    virtual void grad(const ControlDataType & x,
                      ControlDataType & g) const = 0;

    //**********************************************************

    /// H_dx = hess f(x) dx
    /** \param[in]  x     - Input control vector
        \param[in]  dx    - Input control vector of differentials
        \param[out] H_dx  - Hessian vector product of f(x) dx
    */
    virtual void hessvec(const ControlDataType & x,
                         const ControlDataType & dx,
                         ControlDataType & H_dx) const = 0;

    ///@}
  };

  //************************************************************
  //************************************************************

  /// Abstract DTK Checkpoint strategy
  /** \tparam Scalar       - Floating point type for Fields, etc.
      \tparam Ordinal      - Integer type for indexing
      \tparam VectorField  - Container of Fields; should derive from
                             DTK::VectorField
      \tparam Domain       - Domain type; should derive from DTK::Domain
*/
  template < typename Scalar,
             typename Ordinal,
             typename VectorField,
             typename Domain >
  class Checkpoint : virtual public Object
  {
  public:

    //**********************************************************

    typedef typename Shared< Checkpoint< Scalar,
                                         Ordinal,
                                         VectorField,
                                         Domain > >::Ptr Ptr;

    //**********************************************************

    /// Allow a derived class to deallocate memory
    virtual ~Checkpoint() {}

    /// \name Setup methods
    ///@{

    //**********************************************************

    /// Initialize the checkpoint algorithm
    /** \param[in] domain  - Pointer to Domain to be checkpointed
      */
    virtual bool initialize(Domain *domain) = 0;

    //**********************************************************

    /// Reinitialize the checkpoint algorithm
    /** \param[in] domain  - Pointer to Domain to be checkpointed
      */
    virtual void reinitialize(Domain *domain) = 0;

    ///@}

    /// \name Input/output
    ///@{

    //**********************************************************

    /// Write the local values of a vector field
    /** \param[in] istep   - Time step number
        \param[in] sstep   - Substep number
        \param[in] name    - File name
        \param[in] F       - Vector field to write
        \param[in] domain  - Domain of vector field
      */
    virtual void local_write(Ordinal istep,
                             Ordinal sstep,
                             const std::string & name,
                             VectorField & F,
                             Domain * domain) = 0;

    //**********************************************************

    /// Read the local values of a vector field
    /** \param[in]  istep   - Time step number
        \param[in]  sstep   - Substep number
        \param[in]  name    - File name
        \param[out] F       - Vector field to read
        \param[in]  domain  - Domain of vector field
      */
    virtual void local_read(Ordinal istep,
                            Ordinal sstep,
                            const std::string & name,
                            VectorField & F,
                            Domain * domain) = 0;

    //**********************************************************

    /// Write the statistics
    virtual void write_stats() const = 0;

    ///@}

  };

  //************************************************************
  //************************************************************

} // namespace DTK

#endif  // DTK_HPP
