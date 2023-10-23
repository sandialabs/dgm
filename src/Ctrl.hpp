#ifndef DGM_CTRL_HPP
#define DGM_CTRL_HPP

/** \file Ctrl.hpp
    \brief Ctrl base class declaration
*/
#include <limits>

// DTK includes
#include "DTK.hpp"

// DGM includes
#include "Types.hpp"
#include "vField.hpp"

namespace DGM {

/// Define to initialize Ctrl size to zero
#define DGM_CTRL_SIZE_ZERO

/// Abstraction for the concept of a control variable
/** The basic idea is that the Ctrl class is the interface to the
    implementation of a controlled object in DGM.  Any object that you
    would like to serve as an optimization variable should derive off of
    the Ctrl class.  For example, a boundary control would derive off of
    both BC (for boundary condition) and Ctrl (for control variable).

    The Control class serves as a container of Ctrl and specifically uses
    the Ctrl interface to communicate with the Ctrl objects.

    In general, a Ctrl should know and/or provide the following:
    \li penalty factor to compute the cost of this Ctrl
    \li should know whether it is steady or unsteady?
    \li should know how to compute its own inner_product and norm?
    \li size (this is the size for one instance in space, the Entry class
        keeps track of multiple instances in time for an unsteady Ctrl)
    \li data (this is the current control data that is a view into the global
        Control data, called \f$\phi\f$ in the Control class.
    \li how to compute the gradient of an objective functional given State
        and Adjoint vFields
    \li how to bound itself between given upper and lower bounds
    \li how to output and plot itself
    \li how to apply a preconditioner
    \li determine whether realizable

    The Ctrl class is designed to provide this functionality, and in
    general, any DGM class that provides this interface can serve as an
    optimization or control variable.

    \todo Make a penalty object that can hold multiple values for
          multi-objective optimization
    \todo Integrate in the temporal regularization stuff
*/
class Ctrl : public DTK::Ctrl< vField,dVector,Scalar,Size,Ordinal,
                               CMC::Vector<Size,Ordinal>,
                               CMC::Vector<Ordinal,Ordinal> > {
protected:

  Scalar penalty;       ///< Penalty for this Ctrl, controls regularization
#ifdef DGM_USE_TIME_REG
  Scalar penalty_t;     ///< Penalty factor for time derivative
  Scalar penalty_s;     ///< Penalty factor in space
#endif
  dVector data;         ///< Vector storage (flattened) for Ctrl
  bool _owner;          ///< True if Ctrl owns part of global control vector
  bool _replicated;     ///< True if Ctrl is replicated across ranks
  Scalar _time;         ///< local value of time (use with care)
  Ordinal _size;        ///< Size of the data stored in this Ctrl
  bool _linear;         ///< Whether I should behave in a "linear" way

 public:

  mutable vField F;     ///< Possible vField storage (holds primary data)
  mutable vField G;     ///< Possible vField storage (holds temporary data)

  dVector rLinf, rL2, rH1;
  dVector Linf, L2, H1;

#ifndef DGM_USE_TIME_REG
  /// Constructor
  /** @param[in] p penalty value \n
      @param[in] n number of degrees of freedom
   */
  Ctrl(const Scalar p=0, const Ordinal n=0) : penalty(p), _owner(true),
      _replicated(false), _time(0), _size(0), _linear(false),
      F(DGM::Comm::World,"Ctrl:F"), G(DGM::Comm::World,"Ctrl:G") {}
#else
  /// Constructor when using time regularization
  /** @param[in] p penalty value \n
      @param[in] p_t time penalty value \n
      @param[in] p_s spatial penalty value \n
      @param[in] n number of degrees of freedom
   */
  Ctrl(const Scalar p=0, Scalar p_t=0, Scalar p_s=0, const Ordinal n=0)
    : penalty(p), penalty_t(p_t), penalty_s(p_s), _owner(true),
      _replicated(false), _time(0), _size(0), _linear(false),
      F(DGM::Comm::World,"Ctrl:F"), G(DGM::Comm::World,"Ctrl:G") {}
#endif
  /// Destructor
  virtual ~Ctrl() {};

  /// Initialize the Ctrl data vector to zero
  virtual void initialize() {
    if ( _size==0 )
      throw DGM::exception("Logic error:  Ctrl::initialize,"
        " you must set the size of each Ctrl object by calling\n"
        "size(Ordinal) or set_size(Ordinal) before calling initialize()");
    data.resize(_size); data=0.0;
  }

  /// const access for size
  const Ordinal & size() const { return _size; }

  /// set the size
  void size(const Ordinal size) { _size = size; }

  /// determine if rank owns this Ctrl
  virtual bool owner() const { return _owner; }

  /// set whether rank owns this Ctrl
  virtual void owner(const bool owner) { _owner = owner; }

  /// determine parallel IO status
  virtual bool replicated() const { return _replicated; }

  /// set the parallel IO status
  virtual void replicated(const bool replicated) { _replicated = replicated; }

  /// Gather control vector from across a parallel machine
  virtual void gather( dVector & ) const {
    throw DGM::exception("Ctrl::gather is unimplemented");
  }

  /// Scatter control vector across parallel machine
  virtual void scatter( dVector & ) {
    throw DGM::exception("Ctrl::scatter is unimplemented");
  }

  /// Set the Ctrl storage vector to the input vector
  virtual void set_data( const dVector &in) {
    assert( data.size() == in.size() );
    data = in;
  }

  /// Finalize the Ctrl for use by the simulator.
  /** Default to a null-op */
  virtual void finalize() { }

  /// Set the Ctrl storage vector
  virtual void set_data_no_transform( const dVector &in) { set_data(in); }

  /// Extract the Ctrl data vector into the output vector
  virtual void get_data( dVector &out ) const {
    assert( out.size() == data.size() );
    out = data;
  }
  /// Returns true if fill is overloaded
  virtual bool has_fill() const { return false; }
  /// Fill the output vector
  virtual void fill( const Scalar t, dVector &out ) const {
    assert( out.size() == data.size() );
    out = data;
  }
  /// Returns the size of the Ctrl data vector
  virtual Ordinal data_size() const {
    assert( size() == data.size() );
    return data.size();
  }
  /// Sets the size of the data vector
  virtual void set_size(const Ordinal size_in) { _size = size_in; }
  /// Returns the size or length of the data vector
  virtual Ordinal get_size() const { return _size; }
  /// Define the inner product operation for this Ctrl \f$\bX\cdot\bY\f$
  virtual Scalar inner_product(const dVector &Y) const = 0;
  /// Returns the norm of Ctrl where the default is defined by the inner product
  virtual Scalar norm() const { return inner_product(data); }
  /// Returns the cost of the Ctrl that appears in the objective functional
  virtual Scalar cost() const { return pt5*penalty*norm(); }
  /// Computes the gradient of the objective functional wrt the Ctrl (required)
  /** \param[in] S The current State
      \param[in] A The current Adjoint
      \param[in] time The current time
      \param[in,out] G The gradient contribution at this time
   */
  virtual void objective_function_gradient( const vField &S, const vField &A,
                                            const Scalar time,
                                            dVector &G ) const = 0;
  /// Set a prescribed direction for use in directional derivative evaluation
  virtual void set_direction( dVector & ) = 0;
  /// Method to specify bounding of the control, default is just set_data
  /** \note Bound is responsible for setting the data as appropriate
   *  \warning bound should not depend on time. */
  virtual void bound(const dVector &in) { set_data(in); }
  /// Method to return if realizable, default is true
  /** \warning realizable should not depend on time. */
  virtual bool realizable() { return true; }
  /// Default to unsteady control
  virtual bool steady() const { return false; }

  /// \name Preconditioner methods
  //@{
  /// Applies a preconditioner to the current Ctrl object
  /** Default implementation is the identity
      \param[in]  G The gradient object to apply the preconditioner too
      \param[out] P The preconditioned gradient object */
  virtual void applyPreconditioner( const dVector &G, dVector &P ) const {
    P = G;
  }

  /// Computes a contribution to a preconditioner
  /** This interface allow one to compute contributions to a precondition
      for a transient problem.  Default implementation is the identity
      \param[in] S The current State
      \param[in] A The current Adjoint
      \param[out] P The preconditioned Ctrl object */
  virtual void computePreconditioner( const vField &S, const vField &A,
                                      dVector &P ) const {}

  /// Returns true if compute preconditioner is required
  /** This lets the implementation query whether computePreconditioner is
      needed for this particular Ctrl object.  This can be used to reduce both
      memory and compute requirements. */
  virtual bool needsComputePreconditioner() const { return false; }
  //@}

  /// \name Control output methods
  //@{
  /// Output the control to std::cout
  virtual void output() const { std::cout << data << std::endl; }

  /// Read the Ctrl restart file
  /** The Control::Entry::read(...) method could call this if it was important
      to use custom I/O for different Ctrl types.
      Currently this is not used. */
  virtual streamoff read( const string &fname, const streamoff skip,
                          dVector &out ) {
    // this just reads the Ctrl's data as a flat dVector
    ifstream fs(fname.c_str());
    fs.seekg(skip); // position file pointer at offset
    fs.read(reinterpret_cast<char*>(out.data()),sizeof(Scalar)*size());
    return fs.tellg();
  }

  /// Write the Ctrl restart file
  /** The Control::Entry::write(...) method could call this if it was
      important to use custom I/O for different Ctrl types.
      Currently this is not used. */
  virtual streamoff write( const string &fname, const streamoff skip,
                           const dVector &in ) const {
    // this just writes the Ctrl's data out as a flat vector
    ofstream fs(fname.c_str(), ios::in|ios::out);
    fs.seekp(skip); // position file pointer at offset
    fs.write(reinterpret_cast<const char*>(in.data()),sizeof(Scalar)*size());
    return fs.tellp();
  }

  /// Diff two control files (X-Y) given header offsets where X=this
  /** Returns updated offsets for continued reading.
      \param[in] Yctrl  The Ctrl object for the second (Y) control
      \param[in] Ydata  The data vector for the second, Y, control
      \pre Ydata must be already loaded with the correct view of the 
           global control data vector.  This is reaquired as we cannot 
           assume that Yctrl->data has been set for all Ctrl types.
      \todo It would be good to refactor this so that Ydata was no longer needed
   */
  virtual void diff(const Ctrl& Yctrl, const dVector& Ydata) {
    std::cout << "Missing diff method in " << typeid(*this).name() << std::endl;
    DGM_UNDEFINED;
  }

  /// Sum two control files (X-Y) given header offsets where X=this
  /** Returns updated offsets for continued reading.
      \param[in] Yctrl  The Ctrl object for the second (Y) control
      \param[in] Ydata  The data vector for the second, Y, control
      \param[in] sum_unsteady  This needs to be documented
      \param[in] sub_to_mstr  This needs to be documented
      \pre Ydata must be already loaded with the correct view of the 
           global control data vector.  This is reaquired as we cannot 
           assume that Yctrl->data has been set for all Ctrl types.
      \todo It would be good to refactor this so that Ydata was no longer needed
   */
  virtual void sum(const Ctrl& Yctrl, dVector& Ydata, const bool sum_unsteady,
                const std::vector<Size>&sub_to_mstr, 
                const int /*Xctrl_type*/,
                const int /*Yctrl_type*/) {
    if (this->steady()) {
      Yctrl.G.fill(Ydata);
      add (Yctrl.G, sub_to_mstr, F);
      F.extract(Ydata);
    } else {
      if (sum_unsteady) data += Ydata;
      else              data  = Ydata;
    }
  }

  /// Extract into a control.
  /** Returns updated offsets for continued reading.
      \param[in] Yctrl  The Ctrl object for the second (Y) control
      \param[in] Ydata  The data vector for the second, Y, control
      \param[in] sub_to_mstr  This needs to be documented
      \pre Ydata must be already loaded with the correct view of the 
           global control data vector.  This is reaquired as we cannot 
           assume that Yctrl->data has been set for all Ctrl types.
      \todo It would be good to refactor this so that Ydata was no longer needed
   */
  virtual void ext(Ctrl& Yctrl, dVector& Ydata, 
                   const std::vector<Size>&sub_to_mstr) {
    if (this->steady()) {
      Yctrl.G.fill(Ydata);
      extract (Yctrl.G,sub_to_mstr,F);
      Yctrl.G.extract(Ydata);
    } else {
      Ydata = data;
    }
  }

  /// Output the range of the control variable
  virtual void range() const {}

  /// Plot the Ctrl (required)
  virtual void plot( const vField &, const Size, const dVector &,
                     const Ordinal, const Ordinal, const Ordinal,
                     const Ordinal ) const = 0;

  /// Plot the Ctrl with a different filename
  /** Defaults to undefined for now as this is optional. */
  virtual void plot( const vField &, const Size, const dVector &,
                     const Ordinal, const Ordinal,
                     const Ordinal, const Ordinal,
                     const string &ext, const int ControlType=0) const 
   { DGM_UNDEFINED; }

  /// Type for Ctrl information object
  typedef std::map<std::string,std::string> InfoType;

  /// A virtual function that will return a string to be output
  /** This goes in the control file header and can be used for 
      debugging.
  */
  virtual Ctrl::InfoType info() const {
    return Ctrl::InfoType();
  }

  virtual void set_parameter(const std::string &, const std::string &) {}
  /// Allows the Ctrl to be self-aware regarding the data layout in parallel
  /** The default implementation just returns "false" indicating that this
      Ctrl does not know its parallel information yet. */
  virtual bool get_parallel_info( Size &glen, CMC::Vector<Size,Ordinal> &disp,
                                  CMC::Vector<Ordinal,Ordinal> &len) const {
    return false;
  }

  /// Update the internal time for this Ctrl
  void time(const Scalar time) { _time=time; }
  /// Get the internal time for this Ctrl
  Scalar time() const { return _time; }

  // Experimental methods
  void beLinear() { _linear = true; }
  bool amLinear() const { return _linear; }
  void beNormal() { _linear = false; }

  //@}

#ifdef DGM_USE_TIME_REG
  virtual Scalar cost_t() const { return pt5*penalty_t*norm(); }
  virtual Scalar cost_s() const { return pt5*penalty_s*norm(); }
  Scalar get_p() const {return penalty;}
  Scalar get_pt() const {return penalty_t;}
  Scalar get_ps() const {return penalty_s;}
#endif

};

} // namespace DGM

#endif  // DGM_CYRL_HPP
