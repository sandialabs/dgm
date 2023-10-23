#ifndef DGM_ROL_MASKED_OBJECTIVE_HPP
#define DGM_ROL_MASKED_OBJECTIVE_HPP

/** \file ROL_MaskedObjective.hpp
    \brief Masked update to the optimization vector
    
    Defines an objective function where the gradient
    and hessVec functions are such that the optimization
    vector is only updated on a subset of entries.

    \author Greg von Winckel
    \copyright 2018(c) Sandia National Laboratories
*/

#ifdef DGM_USE_ROL

// system includes
#include "ROL_Interface.hpp"

// ROL includes
#include "ROL_VectorWorkspace.hpp"

namespace DGM {

/// Contains the DGM interface to ROL
namespace ROLinterface {

/// Define the objective function
template <class Real>
class MaskedObjective : public ObjectiveBase<Real> {
private:

  State*    state_;        ///< DGM State object
  Adjoint*  adjoint_;      ///< DGM Adjoint object
  Ordinal   npredict_;     ///< Number of time steps in time horizon
  Ordinal   reset_obj_;    ///< Reset objective function

  Control::Ptr diag_precond_;  ///< storage for diagonal preconditioner
  Control::Ptr mask_;          ///< Mask vector contains 1s and 0s

  ///< Vector clone container
  mutable ROL::Ptr<ROL::VectorWorkspace<Real>> workspace_;

  Optimizer *optimizer;   ///< Optimizer object

  Real scaleFDstepsize_;  ///< Scale for finite-difference step size
  bool precompute_;       ///< State/Gradient computed before checkGradient

  int iter_;              ///< Major iteration index
  Real val_;              ///< Value of the objective function

  ROL::Ptr<ROLinterface::Vector<Real> > grad_;

  const DGM::Comm::Ptr comm;  ///< DGM communicator
  const int verb;             ///< verbosity level

  void applyMask( ROL::Vector<Real>& x ) {
    auto Mx_p = workspace_->clone(x);
    auto Mx_cp = static_cast<ROLinterface::Vector<Real>&>(*Mx_p).getVector();
    auto x_cp  = static_cast<ROLinterface::Vector<Real>&>(x).getVector(); 
    mask_->applyPreconditioner( x_cp, Mx_cp );    
    x.set(*Mx_p);
  }


public:

  MaskedObjective( State*       state, 
                   Adjoint*     adjoint, 
                   Control::Ptr grad_cp,
                   Table&       params, 
                   Control::Ptr diag_precond, 
                   Control::Ptr mask, 
                   Optimizer*   opt) :
      /* Initializers */
      state_(state), 
      adjoint_(adjoint), 
      npredict_(params["npredict"]),
      reset_obj_(params["reset_obj"]), 
      diag_precond_(diag_precond), 
      mask_(mask),
      optimizer(opt),
      precompute_(true),
      iter_(-1), 
      val_(0), 
      comm(state_->domain()->get_comm()), 
      verb(comm->verbosity()) /* End Initializers */ {

    comm->cout() << "MaskedObjective" << endl;
    comm->cout() << "  scaleFDstepsize = " << scaleFDstepsize_ << endl;

    grad_ = ROL::makePtr<ROLinterface::Vector<Real>>(grad_cp);
  }

  virtual ~MaskedObjective() {}

  void precompute( const bool precompute ) { precompute_ = precompute; }
  bool precompute() const { return precompute_; }

  void reset(const ROL::Vector<Real> &x, int iter ) {
    if ( reset_obj_ && (numeric_cast<Ordinal>(iter)%reset_obj_ == 0 ) ) {
      comm->cout() << "MaskedObjective::reset()" << std::endl;
      state_->get_objective()->reset();
    }
  }

  /// Update the objective function member variables
  void update(const ROL::Vector<Real> &x, bool flag = true, int iter = -1) {
    Format sci(8); sci.scientific().width(15);
    Format hisci(15); hisci.scientific().width(21);

    iter_ = iter;
    const Control::Ptr xp = getControl(x); 
    xp->bound();

    if ( xp->realizable() ) {
      // conform to DGM::Optimizer interface
      if (iter_<0) {
        optimizer->set_iter(iter_);
        optimizer->set_npredict(npredict_);
        val_ = optimizer->testState(xp, state_->get_objective());
        comm->cout()<<"J = "<<sci(val_)<<endl;
      } else {
        optimizer->set_iter(iter_);
        optimizer->set_npredict(npredict_);
        val_ = optimizer->computeState(xp, state_->get_objective());
      }
    } else throw DGM::exception("MaskedObjective::update() control not realizable.");
  }

  /// Compute objective function value
  Real value(const ROL::Vector<Real> &x, Real &tol) {
    if (verb>1) 
      comm->cout() << "iter = " <<iter_ << ", " << "MaskedObjective::value() = " << val_ << endl;
    return val_;
  }

  /// Compute objective function gradient
  void gradient(       ROL::Vector<Real> &g, 
                 const ROL::Vector<Real> &x, 
                       Real &tol ) {

    if (verb>1) comm->cout() << "MaskedObjective::gradient()" << endl;

    // Cast the ROLinterface::Vector to a Control::Pt and set to zero
    auto g_cp = getControl(g); 
    g_cp->zero();

    // Cast the ROLinterface::Vector to a Control::Ptr and chop the control
    /// \warning This is NOT a valid projected method!
    auto x_cp = getControl(x); 

    auto obj_p = state_->get_objective();

    // Return gradient
    if ( x_cp->realizable() ) {
      // make certain state is using the same control object as the adjoint
      state_->set_control(x_cp.get());
      // SSC: use the Optimizer interface which is safer and easier
      optimizer->computeAdjoint(x_cp,obj_p,g_cp);
    } else throw DGM::exception("MaskedObjective::gradient() control not realizable.");

    // Finalize the gradient if needed (default is noop)
    optimizer->computeGradient(g_cp);

    applyMask(g);
    grad_->set(g);

    // output norms of the gradient
    static Format sci(8); sci.scientific().width(15);
    double total_g = grad_->norm();
    comm->cout()<<"||Grad(J)|| = "<<sci(total_g)<<endl;
    dVector gradient_norms(numeric_cast<Ordinal>(g_cp->num_ctrl()));
    gradient_norms = g_cp->norms();
    vector<string> names(g_cp->names());
    for (Ordinal i=0; i<gradient_norms.size(); ++i)
      comm->cout()<<"  ||dJ/d(" << names[i] << ")|| = "
                  <<sci(gradient_norms[i])<<endl;
  }

  /// Apply objective function Hessian to a vector
  void hessVec(       ROL::Vector<Real> &hv, 
                const ROL::Vector<Real> &v,
                const ROL::Vector<Real> &x, 
                      Real &tol) {
    if (verb>1) comm->cout()<<"MaskedObjective::hessVec()"<<endl;

    hv.set(v);
    applyMask(hv); 
    hv.scale(-1.0);
    hv.plus(v);

    auto xn_p = workspace_->clone(x);
    auto xn_cp = getControl(xn_p);

    auto dg_p = workspace_->clone(x);
    auto dg_cp = getControl(dg_p);

    // Set it to maximum ordinal
    Ordinal it = numeric_limits<Ordinal>::max();

    // Get Step Length
    Real h = ( scaleFDstepsize_ > 0.0 )  
           ? scaleFDstepsize_ * 2.0/(v.norm()*v.norm())*tol
           : tol/v.norm();

    // Compute modified iteration x + h*v
    xn_p->set(x);
    xn_p->axpy(h,v);
    // Solve State
    state_->set_initial_condition();
    state_->compute(npredict_, xn_cp, it);
    // Solve Adjoint
    adjoint_->set_end_condition();
    adjoint_->compute(npredict_, xn_cp, dg_cp, it);

    // Apply Mask
    // Use existing gradient to compute Newton quotient
    dg_p->axpy(-1.0,*grad_);
    dg_p->scale(1.0/h);
    hv.plus(*dg_p); 
  }

  // Apply Preconditioner
  void precond(       ROL::Vector<Real>& Pv,
                const ROL::Vector<Real>& v,
                const ROL::Vector<Real>& x, 
                Real& tol ) {
    if (verb>1) comm->cout() << "MaskedObjective::precond()" << endl;
    diag_precond_->applyPreconditioner( getControl(v), getControl(Pv) );
  }


/// Re-implement checkGradient since the ROL version doesn't work for DGM
/** The ROL version has a couple of issues when used with transient problems
 *  in DGM as follows
 *    -# update is call twice when only once is needed (ever?)
 *    -# update is called without setting iter so that test evaluations are
 *       done when the update before the gradient evaluation must be a full
 *       solve
 *    -# In DGM, we call checkGradient *after* already evaluating the gradient
 *       so it is really wasteful (and super expensive for large transient
 *       problems) to call the State, Adjoint and Gradient solves again.  So
 *       This implementation has a `precompute_` flag that tells it not to do
 *       this.
 */
std::vector<std::vector<Real> >
checkGradient( const ROL::Vector<Real> &x, const ROL::Vector<Real> &g,
               const ROL::Vector<Real> &d, const std::vector<Real> &steps,
               const bool printToStream = true,
               std::ostream & outStream = std::cout,
               const int order = 1) {

  //comm->cout()<<"ROL_DGM_Objective::checkGradient()"<<endl;

  TEUCHOS_TEST_FOR_EXCEPTION( order<1 || order>4, std::invalid_argument, 
                              "Error: finite difference order must be "
                              "1,2,3, or 4" );

  using ROL::Finite_Difference_Arrays::shifts;
  using ROL::Finite_Difference_Arrays::weights;

  Real tol = std::sqrt(ROL::ROL_EPSILON<Real>());

  int numSteps = numeric_cast<int>(steps.size());
  int numVals = 4;
  std::vector<Real> tmp(numVals);
  std::vector<std::vector<Real> > gCheck(numSteps, tmp);

  // Save the format state of the original outStream.
  ROL::nullstream oldFormatState;
  oldFormatState.copyfmt(outStream);

  Real val(0);
  ROL::Ptr<ROL::Vector<Real> > gtmp = g.clone();
  if (precompute()) {
    // Evaluating this again can make roundoff a bit less but this is only
    // really noticable for 1st order FD.  I think that it has to do with
    // roundoff in the forward/backward transforms in polylib
    // this->update(x);
    val = this->value(x,tol);
    gtmp->set(g);
  } else {
    // Evaluate objective value at x.
    this->update(x);
    val = this->value(x,tol);
    // Compute gradient at x.
    // this->update(x);
    this->gradient(*gtmp, x, tol);
  }
  Real dtg = d.dot(gtmp->dual());

  // Temporary vectors.
  ROL::Ptr<ROL::Vector<Real> > xnew = x.clone();

  for (int i=0; i<numSteps; i++) {
    Real eta = steps[i];
    xnew->set(x);
    // Compute gradient, finite-difference gradient, and absolute error.
    gCheck[i][0] = eta;
    gCheck[i][1] = dtg;
    gCheck[i][2] = weights[order-1][0] * val;
    for(int j=0; j<order; ++j) {
      // Evaluate at x <- x+eta*c_i*d.
      xnew->axpy(eta*shifts[order-1][j], d);
      // Only evaluate at shifts where the weight is nonzero  
      if( weights[order-1][j+1] != 0 ) {
        this->update(*xnew);
        gCheck[i][2] += weights[order-1][j+1] * this->value(*xnew,tol);
      }
    }
    gCheck[i][2] /= eta;
    gCheck[i][3] = std::abs(gCheck[i][2] - gCheck[i][1]);

    if (printToStream) {
      if (i==0) {
        outStream << std::right
                  << std::setw(20) << "Step size"
                  << std::setw(20) << "grad'*dir"
                  << std::setw(20) << "FD approx"
                  << std::setw(20) << "abs error"
                  << "\n"
                  << std::setw(20) << "---------"
                  << std::setw(20) << "---------"
                  << std::setw(20) << "---------"
                  << std::setw(20) << "---------"
                  << "\n";
      }
      outStream << std::scientific << std::setprecision(11) << std::right
                << std::setw(20) << gCheck[i][0]
                << std::setw(20) << gCheck[i][1]
                << std::setw(20) << gCheck[i][2]
                << std::setw(20) << gCheck[i][3]
                << "\n";
    }
  }
  // Reset format state of outStream.
  outStream.copyfmt(oldFormatState);
  return gCheck;
}

};

} // namespace ROLinterface

} // namespace DGM

#endif // DGM_USE_ROL

#endif // DGM_ROL_MASKED_OBJECTIVE_HPP
