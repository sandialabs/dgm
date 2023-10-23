#ifndef DGM_OPTIMIZER_HPP
#define DGM_OPTIMIZER_HPP

/** \file Optimizer.hpp
    \brief Base class declaration for all optimization algorithms
    \author Scott Collis
*/

// System includes
#include <string>
#include <iostream>

// DGM includes
#include "Comm.hpp"
#include "Control.hpp"
#include "State.hpp"
#include "Adjoint.hpp"
#include "Preconditioner.hpp"

namespace DGM {

/// Optimizer abstract base class
class Optimizer {

 protected:

  const DGM::Comm::Ptr comm; ///< communicator for this optimizer
  DGM::Comm::Ptr ctl_comm;   ///< communicator for writing ctl (restart) files

  Table params;              ///< parameters Table
  std::string root;          ///< root file name (or run name)

  /// Current directory name (SSC:  why is this needed?)
  std::string current_dir_name;

  Scalar total_j;            ///< objective functional
  Ordinal max_iter;          ///< maximum number of allowable iterations
  Scalar tol_j;              ///< convergence tolerance for the objective func

  Ordinal npredict;          ///< number of prediction steps in time-horizon
  Ordinal nadvance;          ///< number of steps to advance solution

  Ordinal grad_check;        ///< flag to control gradent check logic
  Scalar fd_eps;             ///< gradient check finite difference step size

  FILE *opt_stat;            ///< file handle for the optimization statistics

  Ordinal iter;              ///< Current optimization iteration number

 public:

  /// Shared pointer to Optimizer
  typedef DGM::Shared<Optimizer>::Ptr Ptr;

  State *state;              ///< pointer to the State object
  Adjoint *adjoint;          ///< pointer to the Adjoint object
  Control::Ptr control;      ///< pointer to the Control object
  Control::Ptr gradient;     ///< pointer to the Gradient object
  Control::Ptr dir_control;  ///< storage for the current direction
#ifdef DGM_USE_TIME_REG
  Control::Ptr gt_control;   ///< pointer to the time regularized Gradient
#endif
  Preconditioner::Ptr preconditioner; ///< pointer to a Preconditioner object

  CMC::Stopwatch timer;      ///< cumulative walltime for this optmization

  Json::Value &json;         ///< Json parmeters for this object

  /// Constructor
  Optimizer( State*, Adjoint *, Control::Ptr,
             const DGM::Comm::Ptr = DGM::Comm::World);

  /// Destructor
  virtual ~Optimizer();

  /// Check the gradient against finite difference
  virtual void check_grad() = 0;

  /// Main Optimizer method
  virtual void optimize(const Ordinal=0) = 0;

  /// Advance the forward solution with the current control variables
  virtual Scalar advance(const Ordinal) = 0;

  /// Compute update, step, and apply update to control
  virtual void computeUpdate() {
    DGM_UNDEFINED;
  }

  /// Read a control restart file
  virtual Ordinal readRestart(const string * = NULL) {
    DGM_UNDEFINED;
    return 0;
  }

  /// Read a control restart file
  virtual Ordinal readRestart(streamoff &skip, const string * = NULL) {
    DGM_UNDEFINED;
    return 0;
  }

  /// Write a control restart file
  virtual void writeRestart(const string * = NULL) const { DGM_UNDEFINED; }

  /// Write a control header
  virtual streamoff outputHeader(const string &fname) const {
    DGM_UNDEFINED;
    return 0;
  }

  /// Set communicator used for writing ctl (restart) file
  void set_ctl_comm(DGM::Comm::Ptr comm_) {
    ctl_comm = comm_;
  }

  /// Compute the difference between two control files
  virtual int diff(const string& ctl1, const string& ctl2,
                   const Scalar aeps, const Scalar reps)
  {
    DGM_UNDEFINED;
    return 0;
  }

  /// Compute the sum of control files
  virtual int sum(const double mult,
                  const std::vector<Size> &sub_to_mstr, Optimizer *optimizer)
  {
    DGM_UNDEFINED;
    return 0;
  }
  virtual int sum(const double mult)
  {
    DGM_UNDEFINED;
    return 0;
  }

  /// Extract part of a control file   
  virtual int ext(const std::vector<Size> &sub_to_mstr, Optimizer *optimizer)
  {
    DGM_UNDEFINED;
    return 0;
  }

  /// Plot the control
  virtual void plotControl(const Ordinal ntout=1,
                           const Ordinal riter=0) const {
    DGM_UNDEFINED;
  }

  /// Plot the gradient
  virtual void plotGradient(const Ordinal ntout=1,
                            const Ordinal riter=0) const {
    DGM_UNDEFINED;
  }

  /// return the value of the objective function
  virtual Scalar get_j() const { return total_j; }

  /// set the value of the objective function
  virtual void set_j(const Scalar j) { total_j = j; }

  /// set the value of the gradient norm
  virtual void set_g(const Scalar) { }

  /// set the value of the current working directory
  virtual void set_current_dir(const string& s_) {
    current_dir_name = s_;
  }

  /// get the number of iterations
  virtual Ordinal get_iter() const { return iter; }

  /// set the number of iterations
  virtual void set_iter(const Ordinal i) { iter = i; }

  virtual void prepare_history_file() {
    DGM_UNDEFINED;
  }

  virtual void write_history_file() {
    DGM_UNDEFINED;
  }

  /// Set the maximum number of allowed iterations
  virtual void set_max_iter(const Ordinal i) { max_iter = i; }

  /// Get the number of time steps over which to predict the State
  virtual Ordinal get_npredict() const { return npredict; }

  /// Set the number of time steps over which to predict the State
  virtual void set_npredict(const Ordinal n) { npredict = n; }

#ifndef DGM_USE_TIME_REG
  /// Perform a state solve with a given control and objective
  virtual Scalar computeState( Control::Ptr ctrl, Objective *obj) {
    if( ctl_comm->verbosity()>3 ) {
      ctl_comm->cout() << "Optimizer::computeState" << std::endl;
    }
    state->set_initial_condition();
    state->set_objective(obj);
    return state->compute(npredict, ctrl, iter );
  }
#else
  /// Perform a state solve with a given control and objective
  virtual Scalar computeState( Control::Ptr gt_ctrl, Control::Ptr ctrl,
                               Objective *obj ) {
    state->set_initial_condition();
    state->set_objective(obj);
    return state->compute(npredict, gt_ctrl, ctrl, iter);
  }
#endif

  /// Perform a state test with a given control and objective
  virtual Scalar testState( Control::Ptr ctrl, Objective *obj) {
    if( ctl_comm->verbosity()>3 ) {
      ctl_comm->cout() << "Optimizer::testState" << std::endl;
    }
    state->set_initial_condition();
    state->set_objective(obj);
    return state->test(npredict, ctrl);
  }

#ifndef DGM_USE_TIME_REG
  /// Perform an adjoint solve with a given control and objective
  /** \pre Must computeState first to populate the State database */
  virtual void computeAdjoint( Control::Ptr ctrl, Objective *obj) {
    adjoint->set_end_condition();
    adjoint->set_objective(obj);
    adjoint->compute(npredict, ctrl, gradient, iter );
  }
#else
  /// Perform an adjointsolve with a given control and observation
  /** \pre Must computeState first to populate the State database. */
  virtual void computeAdjoint( Control::Ptr gt_ctrl, Control::Ptr ctrl,
                               Objective *obj ) {
    adjoint->set_end_condition();
    adjoint->set_objective(obj);
    adjoint->compute( npredict, gt_ctrl, ctrl, gradient, iter );
  }
#endif

#ifndef DGM_USE_TIME_REG
  /// Perform an adjoint solve with a given control, objective and gradient
  /** \pre Must computeState first to populate the State database. */
  virtual void computeAdjoint( Control::Ptr ctrl, Objective *obj,
                               Control::Ptr grad) {
    if( ctl_comm->verbosity()>3 ) {
      ctl_comm->cout() << "Optimizer::computeAdjoint" << std::endl;
    }
    adjoint->set_end_condition();
    adjoint->set_objective(obj);
    adjoint->compute(npredict, ctrl, grad, iter );
  }
#else
  /// Perform an adjoint solve with a given control, objective and gradient
  /** \pre Must computeState first to populate the State database. */
  virtual void computeAdjoint( Control::Ptr gt_ctrl, Control::Ptr ctrl,
                               Objective *obj, Control::Ptr grad ) {
    adjoint->set_end_condition();
    adjoint->set_objective(obj);
    adjoint->compute( npredict, gt_ctrl, ctrl, grad, iter );
  }
#endif

  /// Compute the gradient
  /** \pre computeState and computeAdjoint must be done first */
  virtual void computeGradient(Control::Ptr grad) {}

  /// Compute the gradient
  /** \pre computeState and computeAdjoint must be done first */
  virtual void computeGradient() {
    if( ctl_comm->verbosity()>3 ) {
      ctl_comm->cout() << "Optimizer::computeGradient" << std::endl;
    }
    computeGradient(gradient);
  }

  /// Perform a test evaluation of the objective function
  virtual Scalar test(Scalar) {
    DGM_UNDEFINED;
    return 0;
  }

  /// Accessor for control
  Control * getControl() const { return control.get(); }

  /// Accessor for direction control
  Control * getDirControl() const { return dir_control.get(); }

  /// Accessor for gradient
  Control * getGradient() const { return gradient.get(); }

  /// Reset to a new preconditioner
  void resetPreconditioner( Preconditioner::Ptr newPreconditioner ) {
    preconditioner = newPreconditioner;
  }
};

} // namespace DGM

#endif  // DGM_OPTIMIZER_HPP
