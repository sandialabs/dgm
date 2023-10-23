#ifndef DGM_NONLINEAR_CG_HPP
#define DGM_NONLINEAR_CG_HPP

/** \file NonlinearCG.hpp
    \brief Nonlinear CG Optimizater declaration
    \author Scott Collis
*/

// DGM includes
#include "State.hpp"
#include "Adjoint.hpp"
#include "Optimizer.hpp"
#include "LineSearch.hpp"
#include "Preconditioner.hpp"

namespace DGM {

/// Nonlinear Conjugate-Gradient Optimizer
class NonlinearCG: public Optimizer, public Eval<Scalar> {

  /// Supported gradient decent algorithms
  enum CGtype {
    SimpleFixedStepSize=1,       ///< Steepest descent fixed step size
    SimpleLineSearch=2,          ///< Steepest descent with line search
    FletcherReeves=3,            ///< Fletcher-Reeves with line search
    PolakRibiere=4,              ///< Polak-Ribiere with line search
    HestenesStiefel=5,           ///< Hestenes-Stiefel with line search
    ScaledHestenesStiefel=6,     ///< HS with scaled gradients and line search
    RescaledScaledHestenesStiefel=7, ///< Rescaled HS with scaled gradients
    DGKSHestenesStiefel=8,       ///< Hestenes-Stiefel with DGKS correction
    ModifiedHestenesStiefel=9    ///< Globally convergent HS variation
  };

 public:

  Ordinal grad_type;             ///< type of CG gradient update to use
  Ordinal test_count;            ///< number of test solutions computed

  Scalar total_g;                ///< current gradient norm
  Scalar total_g_old;            ///< prior gradient norm
  Scalar total_j_old;            ///< prior objective function
  Scalar total_g_dot_g_old;      ///< inner prod. of current and prior gradient

  Scalar alpha;                  ///< line search step size
  Scalar tol_alpha;              ///< tolerance on line search

  bool norm_alpha;               ///< normalized the stepsize
  bool use_precond;              ///< whether to precondition
  bool stop_on_nan;              ///< whether to stop on a NaN (on Inf)
  bool norm_dir;                 ///< whether to normalize the direction

  Scalar dt;                     ///< time step

  dVector alpha_bar;             ///< history of line search step sizes
  Ordinal max_sub_iter;          ///< maximum number of line search iterations

  Control::Ptr new_control;      ///< storage for new control
  Control::Ptr old_gradient;     ///< storage for old direction
  Control::Ptr pre_gradient;     ///< storage for preconditioned gradient
  Control::Ptr diag_precond;     ///< storage for a diagonal preconditioner

  Ordinal io_type;               ///< IO control parameter

  Ordinal reset_obj;             ///< the frequency resetting the objective
  Ordinal reset_dir;             ///< the frequency to reset the CG direction

  LineSearch lineSearch;         ///< the line search algorithm

  dVector gradient_norms;        ///< partial norms of the objective function
  string objname;                ///< root.ocs file name (with relative path)

  long long adjoint_num;
  int bracket_output;            ///< Whether to output the function values
  bool eval_gradient;            ///< Compute only the gradient

  ///\name Constructors & Destructor
  //@{
  /// Constructor
  NonlinearCG( State*, Adjoint*, Control::Ptr, Preconditioner::Ptr,
               const DGM::Comm::Ptr = DGM::Comm::World,
               const std::string rel_path = "",
               const Table &passed_param = Table());

  virtual ~NonlinearCG() {
    if (comm->verbosity()>1) comm->cout() << "~NonlinearCG()" << endl;
  }

  // non-virtual implementation for use by derived codes
  Scalar test_evaluation(Scalar);
  //@}

 private:

  /// \name Local methods
  //@{
  /// Computes the decent direction
  void computeUpdateDirection();

  /// Solves the line search optimzation problem
  void computeBestStepSize();

  /// Updates the control
  bool updateControl(Scalar alpha, Ordinal finalUpdate=0);
  //@}

 public:

  /// \name Provide DGM::Optimizer interface
  //@{
  void check_grad();
  void optimize(const Ordinal=0);
  Scalar test(Scalar);
  void computeUpdate();
  void prepare_history_file();
  void write_history_file();
  Scalar advance(const Ordinal);
  void set_max_iter(const Ordinal i);
  Ordinal readRestart(const string * = NULL);
  Ordinal readRestart(streamoff &skip, const string * = NULL);
  int diff(const string& ctl1, const string& ctl2,
           const Scalar aeps, const Scalar reps);
  virtual int sum (const double mult,
                   const vector<Size> &sub_to_mstr, Optimizer *optimizer);
  virtual int sum (const double mult);
  virtual int ext (const vector<Size> &sub_to_mstr, Optimizer *optimizer);
  void writeRestart(const string * = NULL) const;
  void plotControl(const Ordinal ntout=1, const Ordinal riter=0) const;
  void plotGradient(const Ordinal ntout=1, const Ordinal riter=0) const;
  virtual void set_g(const Scalar g) { total_g = g; }
  //@}

  /// \name Provide the DGM::Evaluator interface
  //@{
  Scalar operator()(const Scalar &x);
  //@}

 private:

  streamoff readHeader(const string &fname, Ordinal &riter);
  streamoff writeHeader(const string &fname) const;
  streamoff writeJsonHeader(const string &fname) const;
  streamoff readJsonHeader(const string &fname, Ordinal &riter);

};

} // namespace DGM

#endif  // DGM_NONLINEAR_CG_HPP
