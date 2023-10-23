#ifndef DGM_ROL_OPTIMIZER_HPP
#define DGM_ROL_OPTIMIZER_HPP

/** \file ROL_Optimizer.hpp
    \brief ROL Optimizer declaration
    \author Drew Kouri
    \author Denis Ridzal
    \author Bart van Bloemen Waanders
*/

#ifdef DGM_USE_ROL

// DGM includes
#include "State.hpp"
#include "Adjoint.hpp"
#include "Optimizer.hpp"
#include "OptProblem.hpp"
#include "Preconditioner.hpp"

// ROL includes
#include "ROL_Objective.hpp"
#include "ROL_LineSearchStep.hpp"
#include "ROL_TrustRegionStep.hpp"
#include "ROL_StatusTest.hpp"

// ROL DGM includes
#include "ROL_Interface.hpp"
#include "ROL_SplitUpdateLineSearchStep.hpp"
#include "FivePointLineSearch.hpp"

#define DGM_USE_ROL_HEIRARCHICAL_PARAMETERS 1

#ifdef DGM_USE_ROL_HEIRARCHICAL_PARAMETERS
#include "ROL_ParameterListConverters.hpp"
#endif

namespace DGM {

/// ROL Optimizer
class ROL_Optimizer : public DGM::Optimizer {

private:
  // Private member variables
  ROL::Ptr<ROL::AlgorithmState<Scalar> >          algo_state_;
  ROL::Ptr<ROLinterface::ObjectiveBase<Scalar> >  obj_;
  ROL::Ptr<ROL::Step<Scalar> >                    step_;
  ROL::Ptr<ROL::StatusTest<Scalar> >              status_;
  ROL::Ptr<ROL::LineSearch<Scalar> >              lineSearch_;

  // const OptProblem* base_;
  State*   aux_state_;             ///< Auxiliary state for sensitivity
  Adjoint* aux_adjoint_;           ///< Auxiliary adjoint for sensitivity

  int output_type_;                ///< the ocs output style
  bool print_header_;              ///< print header at each iteration
  bool screen_print_;              ///< print ROL info to screen

  ROL::ParameterList parlist_;     ///< ROL input parameter list
  ROL::ParameterList gclist_;      ///< Gradient check parameters


#ifdef DGM_USE_ROL_HEIRARCHICAL_PARAMETERS
  ROL::ParameterList tieredparlist_;
#endif

  bool useTrustRegion_;            ///< use trust region or line search
  Scalar alpha_;                   ///< restart line search parameter value
  Scalar gtol_;                    ///< Global tolerance for status test
  Scalar stol_;

  Scalar gnorm_old_;               ///< prior gradient norm
  Scalar fval_old_;                ///< prior objective function

  std::vector<int> fdorders_;      ///< Order(s) of finite difference to use

  bool use_precond;                ///< whether to precondition

  Control::Ptr diag_precond;       ///< storage for a diagonal preconditioner
  Control::Ptr mask;               ///< storage for mask

  Ordinal reset_obj;               ///< the frequency resetting the objective

  dVector gradient_norms;          ///< partial norms of the objective function

  int verb;                        ///< local verbosity level
  bool skip_update;                ///< hack, skip update for derived code

  const string root;               ///< root filename for this run

  Json::Value &json;               ///< root Json for this run

  Control::Ptr old_gradient;
  Scalar total_g, total_j_old, total_g_old;
  Scalar alpha;

  bool split_update_;             ///< Manually update the LS step instead of calling
                                  ///< Step::update
  bool compute_obj_;

  // Private member functions

  /// Print ROL formatted output to file
  void rol_style_output(bool printHeader=false, string ext=".ocs");
  /// Print DGM formatted output to file
  void dgm_style_output(bool printHeader=false, string ext=".ocs");
  /// Print PEopt formmated output to file
  void peopt_style_output(bool printHeader=false, string ext=".ocs");
  /// Print iteration history and write restart files
  void print_output(bool printHeader = false);

  /// Reads header from ctl file
  streamoff readHeader(const string &fname, Ordinal &riter);
  /// Writes header to ctl file
  streamoff writeHeader(const string &fname) const;
  /// Reads a Json header from ctl file
  streamoff readJsonHeader(const string &fname, Ordinal &riter);
  /// Writes a Json header to ctl file
  streamoff writeJsonHeader(const string &fname) const;

  /// Setup the parameters
  void setupParameters();

  void printBanner() const;

public:

  ///\name Constructors & Destructor
  //@{
  /// Constructor for first-order algorithms
  ROL_Optimizer(State*, Adjoint*, Control::Ptr, Preconditioner::Ptr,
                const DGM::Comm::Ptr = DGM::Comm::World);

  /// Constructor for first-order algorithms that takes a mask "preconditioner"
  ROL_Optimizer(State*, Adjoint*, Control::Ptr, Control::Ptr, Control::Ptr,
                const DGM::Comm::Ptr = DGM::Comm::World );

  /// Constructor for second-order algorithms
  ROL_Optimizer(State*, Adjoint*, Control::Ptr, State*, Adjoint*,
                Preconditioner::Ptr, const DGM::Comm::Ptr = DGM::Comm::World);


  /// Destructor
  virtual ~ROL_Optimizer() {
    if (comm->verbosity()>1) comm->cout() << "~ROL_Optimizer()" << endl;
  }
  //@}

  /// Test the vector implementation
  void test_vector();

  /// \name Provide DGM::Optimizer interface
  //@{
  void check_grad() override;

  void optimize(const Ordinal=0) override;
  Scalar advance(const Ordinal) override;
  Ordinal readRestart(const string * = NULL) override;
  Ordinal readRestart(streamoff &skip, const string * = NULL) override;
  void writeRestart(const string * = NULL) const override;
  void plotControl(const Ordinal ntout=1, const Ordinal riter=0) const override;
  void plotGradient(const Ordinal ntout=1, const Ordinal riter=0) const override;
  void set_max_iter(const Ordinal) override;

  virtual int diff(const string& ctl1, const string& ctl2,
                   const Scalar aeps, const Scalar reps) override;

  /// Compute the sum of control files
  virtual int sum(const double mult,
                  const vector<Size> &sub_to_mstr, Optimizer *optimizer) override;
  virtual int sum(const double mult) override;
  //@}

  /// Extract part of a control file.   
  virtual int ext(const vector<Size> &sub_to_mstr, Optimizer *optimizer) override;
  //@}
};

} // namespace DGM

#endif // DGM_USE_ROL

#endif  // DGM_ROL_OPTIMIZER_HPP
