#ifndef DGM_STATE_HPP
#define DGM_STATE_HPP

/** \file State.hpp
    \brief State base class declaration
    \author S. Scott Collis
*/

#include <string>

// DTK includes
#include "DTK.hpp"
#include "DTK_AtomicOps.hpp"
#include "DTK_InCore.hpp"
#include "DTK_Griewank.hpp"
#include "DTK_Composite.hpp"

// DGM includes
#include "Types.hpp"
#include "Domain.hpp"
#include "vField.hpp"
#include "Control.hpp"
#include "ObjFunc.hpp"
#include "AtomicOps.hpp"

namespace DGM {

// forward declaration
class Objective;
class Adjoint;

#ifdef DGM_STATE_USE_DTK_TIMEINTEGRATE
// Make local compositions for data and function
typedef DTK::CompositeData<vField,dVector> CompositeData;
typedef DTK::CompositeFunc<Scalar,Ordinal,vField,dVector,
                           Domain,ObjFunc> CompositeFunc;
#endif

/// Base class for State Domains
/** Any Domain that derives off this class can be used as the State evaluation
    for Adjoint-based optimization, inversion, and error estimation. */
class State : public DTK::State<Control,Objective,vField,dVector,
                                Scalar,Ordinal>,
              public AtomicOps {

  static const int BUFLEN=256;  ///< Size of temporary buffers

  const DGM::Comm::Ptr comm_;   ///< communicator

  mutable Ordinal num_;         ///< The number of function evaluations

#ifdef DGM_STATE_USE_DTK_TIMEINTEGRATE
  typedef DTK::TimeIntegrate<Scalar,Ordinal,CompositeData,CompositeFunc> TI;
  typedef DTK::RungeKutta<Scalar,Ordinal,CompositeData,CompositeFunc> RK;
  Shared<CompositeFunc>::Ptr compositeFunc;
  Shared<TI>::Ptr DTK_ti;
#endif

protected:

  string name;             ///< The name of this State object

  int p_inc;               ///< Increment in polynomial order for this State
  
  bool outputTest_;        ///< True outputs detailed test results

  mutable vField Uf2;      ///< Temporary vector for substep interpolation

  Control *control;        ///< Control for this State

  Objective *objective;    ///< Objectives (i.e. observations) for this State

  vector<Scalar> ss_rtime; ///< Substep relative time

  /// Do not allow copy construction
  State(const State &s);

  /// Do not allow copy construction
  State(const State *s);

public:

#ifdef DGM_USE_GRIEWANK
  /// State storage database
  mutable DTK::Griewank<Scalar,Ordinal,vField,Domain> griewank;
#else
  /// State storage database
  mutable DTK::InCore<Scalar,Ordinal,vField,Domain> in_core_storage;
#endif

  typedef DGM::Shared<State>::Ptr Ptr; ///< Shared pointer to State

  /// Constructor
  State(const int pinc=0, const DGM::Comm::Ptr = DGM::Comm::World);

  /// Destructor
  virtual ~State();

  /// Sets initial condition, scratch and stores in database
  virtual void initialize();

  /// Defaults to undefined, must (if used) be supplied by derived class
  virtual void initialize(const dVector &, const Scalar=0.0,
                          const Ordinal=0) {DGM_UNDEFINED;}

#ifdef DGM_STATE_USE_DTK_TIMEINTEGRATE
  /// Setup the time integration scheme
  virtual void setTimeIntegrate(Control::Ptr, Objective *);
#endif

  /// Calls Domain::set_ic()
  virtual void set_initial_condition();

  /// Sets the State to data at time t and timestep step
  virtual void set_initial_condition(const dVector &data, const Scalar t=0.0,
                                     const Ordinal step=0);

  /// Defaults to undefined, must be supplied by derived class
  virtual void set(const Ordinal, const Ordinal=0) {DGM_UNDEFINED;}

  /// Compute state nsteps using supplied control for optimization iteration
  virtual Scalar compute(const Ordinal nsteps, Control::Ptr,
                         const Ordinal iteration=0);

  /// Do a test state solution (no storage) for nsteps using supplied control
  virtual Scalar test(const Ordinal nsteps, Control::Ptr);

  /// Advance state nsteps using supplied control on outer iteration
  virtual Scalar advance(const Ordinal nsteps, Control::Ptr,
                         const Ordinal outer=0);

  /// Store vField in the State database
  virtual void store(vField &, const Ordinal istep, const Ordinal sstep=0);
  /// Load vField from the State database
  virtual void load(vField &, const Ordinal istep, const Ordinal sstep=0);
  /// Load vField from the State database but skip the header
  virtual void load_field(vField &, const Ordinal istep,
                          const Ordinal sstep=0) const;

  /// Load vField from the State database
  virtual void local_load(vField &, const Ordinal istep,
			  const Ordinal sstep, Domain *) const;

  /// Interpolate vField from the State database
  virtual void interpolate_field(vField &, const Ordinal istep,
				 const Ordinal sstep, Domain *) const;

  //===========================================================================
  //                       Methods for Checkpointing
  //===========================================================================
  ObjFunc::Ptr objfunc;    ///< Objective function (observations & penalties)

  /// Atomic version of initialize
  virtual void atomic_initialize();

  /// Atomic advance (full time horizon)
  virtual Scalar atomic_advance(const Ordinal);

  /// Atomic advance (limited time horizon)
  virtual Scalar atomic_advance(const Ordinal, const Ordinal);

  //===========================================================================

  /// Defaults to undefined, must be supplied by derived class
  virtual void residual( vField &, vField &, const bool source=true ) {
    DGM_UNDEFINED;
  }
  /// Defaults to undefined, must be supplied by derived class
  virtual void steady_residual( vField &, vField &, const bool source=true ) {
    DGM_UNDEFINED;
  }
  /// Defaults to undefined, must be supplied by derived class
  virtual Scalar estimate_error( const Ordinal, Adjoint *, dVector & ) {
    DGM_UNDEFINED;
    return 0.0;
  }
  /// Defaults to undefined, must be supplied by derived class
  virtual Scalar estimate_error_steady( const Ordinal, Adjoint *, dVector & ) {
    DGM_UNDEFINED;
    return 0.0;
  }

#ifdef DGM_USE_TIME_REG
  virtual Scalar compute(const Ordinal, Control::Ptr, Control::Ptr,
                         const Ordinal iteration=0);
  virtual Scalar test(const Ordinal, Control::Ptr, Control::Ptr);
  virtual Scalar advance(const Ordinal, Control::Ptr, Control::Ptr,
                         const Ordinal outer=0);
#endif

  /// Sets the State objective pointer
  virtual void set_objective(Objective *obj) {objective=obj;}
  /// Return the Objective for this State
  virtual Objective* get_objective() { return objective; }
  /// Return the Objective for this State
  virtual const Objective* get_objective() const { return objective; }

  /// Return the Domain for this State
  virtual const Domain* domain() const = 0;
  /// Return the Domain for this State
  virtual Domain* domain() = 0;

  /// Sets the State Control pointer
  virtual void set_control(Control *ctrl) { control=ctrl; }
  /// Return the Control for this State
  virtual const Control* get_control() const { return control; }
  /// Return the Control for this State
  virtual Control* get_control() { return control; }

  /// Accessor for State increment in polynomial order
  int get_p_inc() const {return p_inc;}

  /// Accessor for Domain substep interpolation order
  int get_ssiorder() const {return domain()->get_ssiorder();}
  /// Sets the Domain substep interpolation order
  void set_ssiorder(const int so) {domain()->set_ssiorder(so);}

  /// Turn on saving every step and substep
  void save(const string newtag=string("")) {testflag=0; tag=newtag;}
  /// Turn off saving every step and substep
  void no_save() {testflag=1;}
  /// Set the current database tag
  void set_tag(const string newtag) {tag=newtag;}
  /// Return the current database tag
  string get_tag() const { return tag; }

  /// Get the number of function evaluations
  Ordinal num() const { return num_; }
  /// Set the number of function evaluations
  void num(const Ordinal num) { num_=num; }
  /// Increment the number of function evaluations
  void increment(const Ordinal inc=1) { num_ += inc; }

  /// set the output test flag
  void outputTest(const bool value) {outputTest_=value;}
  /// get the output test flag
  bool outputTest() const {return outputTest_;}

}; // class State

} // namespace DGM

#endif  // DGM_STATE_HPP
