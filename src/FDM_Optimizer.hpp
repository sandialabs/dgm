#ifndef FDM_OPTIMIZER_HPP
#define FDM_OPTIMIZER_HPP

/** \file FDM_Optimizer.hpp
    \brief Base class declaration for all FDM optimization algorithms
    \author Bill Spotz
**/

// System includes
#include <string>
#include <iostream>

// FDM includes
//#include "Comm.hpp"
#include "FDM_Control.hpp"
#include "FDM_State.hpp"
#include "FDM_Adjoint.hpp"
//#include "FDM_Preconditioner.hpp"

namespace FDM
{

/// Optimizer abstract base class
class Optimizer
{
protected:

  const CommPtr comm;      ///< communicator for this optimizer
  CommPtr ctl_comm;        ///< communicator for writing ctl (restart) files

  //Table params;            ///< parameters Table
  std::string root;        ///< root file name (or run name)
  std::string current_dir_name;

  Scalar total_j;          ///< objective functional
  Ordinal max_iter;        ///< maximum number of allowable iterations
  Scalar tol_j;            ///< convergence tolerance for the objective function

  Ordinal npredict;        ///< number of prediction steps in time-horizon
  Ordinal nadvance;        ///< number of steps to advance solution

  Ordinal grad_check;      ///< flag to control gradent check logic
  Scalar fd_eps;           ///< gradient check finite difference step size

  FILE *opt_stat;          ///< file handle for the optimization statistics

  CMC::Stopwatch timer;    ///< cumulative walltime for this optmization

  Ordinal iter;            ///< Current optimization iteration number

public:

  /// Shared pointer to Optimizer
  typedef DTK::Shared< Optimizer >::Ptr Ptr;

  State *state;            ///< pointer to the State object
  Adjoint *adjoint;        ///< pointer to the Adjoint object
  Control::Ptr control;    ///< pointer to the Control object
  Control::Ptr gradient;   ///< pointer to the Gradient object
#ifdef DGM_USE_TIME_REG
  Control::Ptr gt_control; ///< pointer to the time regularized Gradient object
#endif
  //Preconditioner::Ptr preconditioner; ///< pointer to a Preconditioner object

  /// Constructor
  Optimizer(State*,
            Adjoint *,
            Control::Ptr,
            const DGM::Comm::Ptr = DGM::Comm::World);

  /// Destructor
  virtual ~Optimizer();

  /// Check the gradient against finite difference
  virtual void check_grad() = 0;

  /// Main Optimizer method
  virtual void optimize(const Ordinal=0) = 0;

  /// Advance the forward solution with the current control variables
  virtual Scalar advance(const Ordinal) = 0;

  /// Read a control restart file
  virtual Ordinal readRestart(const string * = NULL)
  {
    DGM_UNDEFINED;
    return 0;
  }

  /// Read a control restart file
  virtual Ordinal readRestart(streamoff &skip,
                              const string * = NULL)
  {
    DGM_UNDEFINED;
    return 0;
  }

  /// Write a control restart file
  virtual void writeRestart(const string * = NULL) const
  {
    DGM_UNDEFINED;
  }

  /// Write a control header
  virtual streamoff outputHeader(const string &fname) const
  {
    DGM_UNDEFINED;
    return 0;
  }

  /// Set communicator used for writing ctl (restart) file
  void set_ctl_comm(FDM::CommPtr comm_)
  {
    ctl_comm = comm_;
  }

  /// Compute the difference between two control files
  virtual int diff(const string& ctl1,
                   const string& ctl2,
                   const Scalar aeps,
                   const Scalar reps)
  {
    DGM_UNDEFINED;
    return 0;
  }

  /// Plot the control
  virtual void plotControl(const Ordinal ntout=1,
                           const Ordinal riter=0) const
  {
    DGM_UNDEFINED;
  }

  /// Plot the gradient
  virtual void plotGradient(const Ordinal ntout=1,
                            const Ordinal riter=0) const
  {
    DGM_UNDEFINED;
  }

  /// return the value of the objective function
  virtual Scalar get_j() const
  {
    return total_j;
  }

  /// set the value of the objective function
  virtual void set_j(const Scalar j)
  {
    total_j = j;
  }

  /// set the value of the gradient norm
  virtual void set_g(const Scalar)
  {
  };

  /// set the value of the current working directory
  virtual void set_current_dir(const string& s_)
  {
    current_dir_name = s_;
  };

  virtual Ordinal get_iter() const
  {
    return iter;
  }

  virtual void set_iter(const Ordinal i)
  {
    iter = i;
  }

  virtual void adjustWorkingDirectory()
  {
  }

  virtual void set_max_iter(const Ordinal i)
  {
    max_iter = i;
  }

  /// return the value of the objective function
  virtual Ordinal get_npredict() const
  {
    return npredict;
  }

  virtual void set_npredict(const Ordinal n)
  {
    npredict = n;
  }

#ifndef DGM_USE_TIME_REG
  /// Perform a state solve with a given control and objective
  virtual Scalar computeState(Control::Ptr ctrl,
                              Objective *obj)
  {
    state->set_initial_condition();
    state->set_objective(obj);
    return state->compute(npredict, ctrl, iter );
  }
#else
  /// Perform a state solve with a given control and objective
  virtual Scalar computeState(Control::Ptr gt_ctrl,
                              Control::Ptr ctrl,
                              Objective *obj )
  {
    state->set_initial_condition();
    state->set_objective(obj);
    return state->compute(npredict, gt_ctrl, ctrl, iter);
  }
#endif

#ifndef DGM_USE_TIME_REG
  /// Perform an adjoint solve with a given control and objective
  virtual void computeAdjoint(Control::Ptr ctrl,
                              Objective *obj)
  {
    adjoint->set_end_condition();
    adjoint->set_objective(obj);
    adjoint->compute(npredict, ctrl, gradient, iter );
  }
#else
  /// Perform an adjointsolve with a given control and observation
  /** \pre Must computeState first **/
  virtual void computeAdjoint(Control::Ptr gt_ctrl,
                              Control::Ptr ctrl,
                              Objective *obj)
  {
    adjoint->set_end_condition();
    adjoint->set_objective(obj);
    adjoint->compute( npredict, gt_ctrl, ctrl, gradient, iter );
  }
#endif

#ifndef DGM_USE_TIME_REG
  /// Perform an adjoint solve with a given control, objective and gradient
  virtual void computeAdjoint(Control::Ptr ctrl,
                              Objective *obj,
                              Control::Ptr grad)
  {
    adjoint->set_end_condition();
    adjoint->set_objective(obj);
    adjoint->compute(npredict, ctrl, grad, iter );
  }
#else
  /// Perform an adjoint solve with a given control, objective and gradient
  /** \pre Must computeState first **/
  virtual void computeAdjoint(Control::Ptr gt_ctrl,
                              Control::Ptr ctrl,
                              Objective *obj,
                              Control::Ptr grad)
  {
    adjoint->set_end_condition();
    adjoint->set_objective(obj);
    adjoint->compute( npredict, gt_ctrl, ctrl, grad, iter );
  }
#endif

  /// Compute the gradient
  /** \pre computeState and computeAdjoint must be done first */
  virtual void computeGradient(Control::Ptr grad)
  {
  }

  /// Compute the gradient
  /** \pre computeState and computeAdjoint must be done first */
  virtual void computeGradient()
  {
    computeGradient(gradient);
  }

  /// Accessor for control
  Control * getControl() const
  {
    return control.get();
  }

  /// Accessor for gradient
  Control * getGradient() const
  {
    return gradient.get();
  }

  /// Reset to a new preconditioner
  // void resetPreconditioner(Preconditioner::Ptr newPreconditioner)
  // {
  //   preconditioner = newPreconditioner;
  // }
};

} // namespace DGM

#endif  // DGM_OPTIMIZER_HPP
