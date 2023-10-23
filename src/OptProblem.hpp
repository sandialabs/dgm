#ifndef DGM_OPT_PROBLEM_HPP
#define DGM_OPT_PROBLEM_HPP

/** \file OptProblem.hpp
    \brief DGM optimization problem declaration
*/

// System includes
#include <iostream>
#include <string>
#include <list>
using namespace std;

// Boost includes
#ifdef DGM_USE_BOOST_FS
#include <boost/filesystem/operations.hpp>
#endif

// DGM includes
#include "Comm.hpp"
#include "ArgList.hpp"
#include "Table.hpp"
#include "Domain.hpp"
#include "State.hpp"
#include "Adjoint.hpp"
#include "Control.hpp"
#include "Objective.hpp"
#include "Optimizer.hpp"
#include "Preconditioner.hpp"

namespace DGM {

/// Optimization Problem base class
/** Determines run parameters and sets up an optimization problem on a Domain.
    This class plays the role of a "virtual constructor" in that it holds a
    generic Domain, but constructs a specific Domain depending on prescribed
    parameters.

    This class has the ability to build both regular and linearized
    optimization problems (if supported for the selected Domain) for use in
    first and second order optimization algorithms.  The type of problem
    constructed depends on the constructor used.

    \note The default Preconditioner is always the IdentityPreconditioner
*/
class OptProblem : public DTK::Problem {

 protected:

  const DGM::Comm::Ptr comm;    ///< Parallel communicator

  bool plot_grad;               ///< Plot the gradient of the Problem's control

 public:

  /// Shared pointer to OptProblem
  typedef DGM::Shared<OptProblem>::Ptr Ptr;

  /// Supported optimization algorithms
  enum OptType {
    BLACKBOX=0,                 ///< Black-box (DAKOTA style) interface
    NONLINEARCG=1,              ///< Generalized nonlinear CG
    LBFGS=2,                    ///< Limited memory BFGS
    ERROREST=3                  ///< Error estimation interface
#ifdef DGM_USE_ROL
    , ROL=4,                    ///< Rapid Optimization Library
    ROL_PRECOND=5               ///< Use ROL with diagonal preconditioner + mask
#endif
  };

  /// \name Basic parameters
  //@{
  string code;                  ///< Name of executable
  string root;                  ///< Root file name for run
  Table params;                 ///< Input parameters
  //@}

  /// \name Primary optimization problem
  //@{
  State        *state;          ///< State for this problem
  Adjoint      *adjoint;        ///< Adjoint for this problem
  Control::Ptr  control;        ///< Control for this problem
  Objective    *objective;      ///< Objective for this problem
  Optimizer    *optimizer;      ///< Optimizer for this problem
  Preconditioner::Ptr  preconditioner; ///< Preconditioner for this problem
  //@}

  /// \name Secondary optimization problem (for linearized operators)
  //@{
  State       *aux_state;       ///< Auxilary State for this problem
  Adjoint     *aux_adjoint;     ///< Auxilary Adjoint for this problem
  Objective   *aux_objective;   ///< Auxilary Objective for this problem
  Preconditioner::Ptr aux_preconditioner; ///< Auxilary preconditioner
  //@}

  /// Constructor for regular optimization problems
  OptProblem( ArgList &args, const Table &table = Table(),
              const DGM::Comm::Ptr comm_ = DGM::Comm::World )
    : comm(comm_), plot_grad(false), params(table),
      state(NULL), adjoint(NULL), control(), objective(NULL), optimizer(NULL),
      preconditioner(new IdentityPreconditioner()),
      aux_state(NULL), aux_adjoint(NULL),
      aux_objective(NULL), aux_preconditioner(new IdentityPreconditioner()) { }

  /// Constructor for linearized optimization problems
  OptProblem( const OptProblem *base, ArgList &args,
              const Table &table = Table(),
              const DGM::Comm::Ptr comm_ = DGM::Comm::World )
    : comm(comm_), plot_grad(false), params(table),
      state(NULL), adjoint(NULL), control(), objective(NULL), optimizer(NULL),
      preconditioner(new IdentityPreconditioner()),
      aux_state(NULL), aux_adjoint(NULL),
      aux_objective(NULL), aux_preconditioner(new IdentityPreconditioner()) { }

  /// Destructor
  virtual ~OptProblem() {
    if (comm->verbosity()>1) comm->cout() << "~OptProblem()" << endl;
    if (optimizer) delete optimizer;
    if (comm->verbosity()>2) comm->cout() << "  deleted optimizer" << endl;
    if (objective) delete objective;
    if (comm->verbosity()>2) comm->cout() << "  deleted objective" << endl;
    if (adjoint) delete adjoint;
    if (comm->verbosity()>2) comm->cout() << "  deleted adjoint" << endl;
    if (state) delete state;
    if (comm->verbosity()>2) comm->cout() << "  deleted state" << endl;
    if (aux_state) delete aux_state;
    if (comm->verbosity()>2) comm->cout() << "  deleted aux_state" << endl;
    if (aux_adjoint) delete aux_adjoint;
    if (comm->verbosity()>2) comm->cout() << "  deleted aux_adjoint" << endl;
    if (aux_objective) delete aux_objective;
    if (comm->verbosity()>2) comm->cout() << "  deleted aux_objective" << endl;
  }

  /// Get the parallel communicator
  const DGM::Comm::Ptr get_comm() const {return comm;}

  /// Extract arguments
  virtual void parse_args( ArgList &args ) = 0;

  /// Show supported commandline arguments
  virtual void showUsage(const string &) const = 0;

  /// Primary optimization problem solve interface
  virtual int solve() = 0;

  /// solve for given number of steps
  //virtual int solve(const int);

  /// Compute the difference between two control files
  virtual int diff(const string& ctl1, const string& ctl2,
                   const Scalar aeps, const Scalar reps) {
    return optimizer->diff(ctl1, ctl2, aeps, reps);
  }

  /// Compute the difference between two control files
  virtual int sum(const double mult,
                  const vector<Size> &sub_to_mstr, OptProblem &sum_from) {
    return optimizer->sum(mult, sub_to_mstr, sum_from.optimizer);
  }
  virtual int sum(const double mult) {
    return optimizer->sum(mult);
  }

  /// Extract part of a control file.
  virtual int ext(const vector<Size> &sub_to_mstr, OptProblem &ext_to) {
    return optimizer->ext(sub_to_mstr, ext_to.optimizer);
  }

  /// Plot the optimization solution
  virtual int plot(const string &ctl) {
#ifdef DGM_USE_BOOST_FS
    if (!boost::filesystem::exists(ctl))
      throw DGM::exception("Control restart file "+ctl+" does not exist");
#endif
    Ordinal iter = optimizer->readRestart(&ctl);
    comm->cout() << "  Plotting control at iter = " << iter << endl;
    optimizer->plotControl( state->domain()->ntout, iter );
    if (plot_grad) {
      comm->cout() << "  Plotting gradient of control at iter = "
                   << iter << endl;
      optimizer->plotGradient( state->domain()->ntout, iter );
    }
    return 0;
  }

  /// \name Accessors
  //@{
  State * getState() const { return state; }
  Adjoint * getAdjoint() const { return adjoint; }
  Control * getControl() const { return control.get(); }
  Objective * getObjective() const { return objective; }
  Optimizer * getOptimizer() const { return optimizer; }
  Preconditioner * getPreconditioner() const { return preconditioner.get(); }
  //@}

  /// \name Simplified interface
  //@{
  /// Perform a state solve with internal control and objective
  /** \returns Scalar objective function value. */
  virtual Scalar computeState() {
    return optimizer->computeState( control, objective );
  }

  /// Perform a state solve with a given control and objective
  /** \returns Scalar objective function value. */
  virtual Scalar computeState( Control::Ptr ctrl, Objective *obj ) {
    return optimizer->computeState( ctrl, obj );
  }

  /// Perform a adjoint solve with internal control and objective
  /** \pre State have been already computed. */
  virtual void computeAdjoint() {
    optimizer->computeAdjoint( control, objective );
  }

  /// Perform a adjoint solve with a given control and objective
  /** \pre State have been already computed
      \note This fills the optimizer's gradient. */
  virtual void computeAdjoint( Control::Ptr ctrl, Objective *obj ) {
    optimizer->computeAdjoint( ctrl, obj );
  }

  /// Access the gradient
  Control * getGradient() const { return optimizer->getGradient(); }

  /// Apply the Preconditioner to a control
  void applyPreconditioner( const Control::Ptr grad,
                            Control::Ptr pre_grad) const {
    preconditioner->apply(grad,pre_grad);
  }
  //@}
};

} // namespace DGM

#endif // DGM_OPT_PROBLEM_HPP
