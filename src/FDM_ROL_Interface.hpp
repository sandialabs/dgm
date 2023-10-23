#ifndef FDM_ROL_HPP
#define FDM_ROL_HPP

/** \file FDM_ROL_Interface.hpp
    \brief Provides FDM specific functionality to ROL.
    \author Bill Spotz

    Based on fdm_ROL.hpp by Drew Kouri, Denis Ridzal, and Bart van
    Bloemen Waanders.
**/

#ifdef DGM_USE_ROL

// system includes
#include <iostream>
#include <limits>

// boost includes
#include <boost/numeric/conversion/cast.hpp>

// FDM includes
// #include "Comm.hpp"
#include "FDM_Control.hpp"
// #include "Format.hpp"
// #include "MultiOptProblem.hpp"
#include "FDM_Optimizer.hpp"
// #include "Regularization.hpp"
// #include "ReoOptProblem.hpp"
// #include "String.hpp"

// ROL includes
#include "ROL_Objective.hpp"

namespace FDM {

/// FDM interface to the ROL vector class
template <class Real>
class ROL_FDM_Vector :
    public ROL::Vector<Real>
{
  Control::Ptr vec_;       ///< wrapped FDM::Control pointer
  int verb;                ///< local verbosity level

public:

  ROL_FDM_Vector(Control::Ptr vec) :
    vec_(vec),
    verb(0)
  {
  }

  void scale(const Real alpha)
  {
    FDM::scale(alpha,vec_);
  }

  void plus(const ROL::Vector<Real> &x)
  {
    const Control::Ptr ex = (Teuchos::dyn_cast<ROL_FDM_Vector>
      (const_cast <ROL::Vector<Real> &>(x))).getVector();
    FDM::add(ex,vec_);
  }

  void axpy(const Real alpha, const ROL::Vector<Real> &x)
  {
    const Control::Ptr ex = (Teuchos::dyn_cast<ROL_FDM_Vector>
      (const_cast <ROL::Vector<Real> &>(x))).getVector();
    FDM::axpy(alpha,ex,vec_);
  }

  void zero()
  {
    (vec_)->zero();
  }

  Real dot(const ROL::Vector<Real> &x) const
  {
    const Control::Ptr ex = (Teuchos::dyn_cast<ROL_FDM_Vector>
      (const_cast <ROL::Vector<Real> &>(x))).getVector();
    return (vec_)->inner_product(ex.get());
  }

  Real norm() const
  {
    return (vec_)->norm();
  }

  Teuchos::RCP<ROL::Vector<Real> > clone() const
  {
    Control::Ptr tmp;
    tmp.reset(vec_->clone());
    return Teuchos::rcp( new ROL_FDM_Vector( tmp ) );
  }

  const Control::Ptr getVector() const
  {
    return vec_;
  }

};

/// FDM interface to the ROL objective class
template <class Real>
class ROL_FDM_Objective :
    public ROL::Objective<Real>
{

  State*   state_;        ///< FDM State object
  Adjoint* adjoint_;      ///< FDM Adjoint object
  State*   stateSens_;    ///< FDM State object for state sensitivity
  Adjoint* adjointSens_;  ///< FDM Adjoint object for adjoint sensitivity
  Ordinal  npredict_;     ///< Number of time steps in time horizon
  Ordinal  reset_obj_;    ///< Reset objective function
  Optimizer *optimizer;   ///< Optimizer object

  bool         use_precond_;   ///< use diagonal preconditioner
  Control::Ptr diag_precond_;  ///< storage for diagonal preconditioner

  bool secondOrderInfo_;  ///< Use Gauss-Newton hessvec
  int  useFDhessvec_;     ///< Use finite-difference hessvec
  Real scaleFDstepsize_;  ///< Scale for finite-difference step size

  int iter_;              ///< Major iteration index
  Real val_;              ///< Value of the objective function

  Teuchos::RCP<ROL_FDM_Vector<Real> > grad_;

public:

  /// Construct first order algorithms
  ROL_FDM_Objective( State* state,
                     Adjoint* adjoint,
                     Control::Ptr x,
                     Ordinal npredict,
                     Ordinal reset_obj,
                     bool use_precond,
                     Control::Ptr diag_precond,
                     Optimizer *opt,
                     int useFDhessvec = 0,
                     Real scaleFDstepsize = 1.0 ) :
    state_(state),
    adjoint_(adjoint),
    npredict_(npredict),
    reset_obj_(reset_obj),
    optimizer(opt),
    use_precond_(use_precond),
    diag_precond_(diag_precond),
    secondOrderInfo_(false),
    useFDhessvec_(useFDhessvec),
    scaleFDstepsize_(scaleFDstepsize),
    iter_(-1)
  {
    grad_ = Teuchos::rcp( new ROL_FDM_Vector<Real>(x) );
  }

  /// Construct second order algorithms
  ROL_FDM_Objective( State* state,
                     Adjoint* adjoint,
                     Control::Ptr x,
                     State* stateSens,
                     Adjoint* adjointSens,
                     Ordinal npredict,
                     Ordinal reset_obj,
                     bool use_precond,
                     Control::Ptr diag_precond,
                     Optimizer *opt,
                     int useFDhessvec = 0,
                     Real scaleFDstepsize = 1.0 ) :
    state_(state),
    adjoint_(adjoint),
    stateSens_(stateSens),
    adjointSens_(adjointSens),
    npredict_(npredict),
    reset_obj_(reset_obj),
    optimizer(opt),
    use_precond_(use_precond),
    diag_precond_(diag_precond),
    secondOrderInfo_(true),
    useFDhessvec_(useFDhessvec),
    scaleFDstepsize_(scaleFDstepsize),
    iter_(-1)
  {
    grad_ = Teuchos::rcp( new ROL_FDM_Vector<Real>(x) );
  }

  /// Update the objective function member variables
  void update(const ROL::Vector<Real> &x,
              bool flag = true,
              int iter = -1)
  {
    // Store current optimization iteration -- if iter = -1,
    //   then this is a linesearch iteration and we MAY not
    //   need to store the state
    iter_ = iter;

    // reset the objective function
    if ( flag && (iter_ > -1) )
    {
      if ( reset_obj_ )
      {
        if ( numeric_cast<Ordinal>(iter_)%reset_obj_ == 0 )
        {
          state_->get_objective()->reset();
          if ( secondOrderInfo_ && !useFDhessvec_ ) {
            stateSens_->get_objective()->reset();
          }
        }
      }

      // Cast the ROL_FDM_Vector to a Control::Ptr and chop the
      //   control -- This is NOT a valid projected method!
      const Control::Ptr xp = (Teuchos::dyn_cast<ROL_FDM_Vector<Real> >
        (const_cast<ROL::Vector<Real> &>(x))).getVector();
      xp->bound();

      // Solve the state at the new control and compute objective
      //   function value
      if ( xp->realizable() )
      {
        // conform to FDM::Optimizer interface
        optimizer->set_iter(iter_);
        val_ = optimizer->computeState(xp, state_->get_objective());
      }
      else
      {
        val_ = numeric_limits<Real>::max();
      }
    }
  }

  /// Compute objective function value
  Real value(const ROL::Vector<Real> &x, Real &tol) {
    if ( iter_ < 0 ) {  // This is a minor iteration
      // Cast the ROL_FDM_Vector to a Control::Ptr and chop the
      //   control -- This is NOT a valid projected method!
      const Control::Ptr xp = (Teuchos::dyn_cast<ROL_FDM_Vector<Real> >
        (const_cast<ROL::Vector<Real> &>(x))).getVector();
      xp->bound();

      // Return function value
      if ( xp->realizable() ) {
        state_->set_initial_condition();
        return state_->test(npredict_, xp);
      } else {
        return numeric_limits<Real>::max();
      }
    } else { // This is a major iteration, objective already computed
      return val_;
    }
  }

  //// Compute objective function gradient
  void gradient(ROL::Vector<Real> &g, const ROL::Vector<Real> &x, Real &tol) {

    // Cast the ROL_FDM_Vector to a Control::Pt and set to zero
    Control::Ptr gp = (Teuchos::dyn_cast<ROL_FDM_Vector<Real> >(g)).getVector();
    gp->zero();

    // Cast the ROL_FDM_Vector to a Control::Ptr and chop the
    //   control -- This is NOT a valid projected method!
    const Control::Ptr xp = (Teuchos::dyn_cast<ROL_FDM_Vector<Real> >
                            (const_cast<ROL::Vector<Real> &>(x)) ).getVector();
    xp->bound();

    Objective *obj = state_->get_objective();

    // Return gradient
    if ( xp->realizable() ) {
      Ordinal it = 0;
      if ( iter_ < 0 ) { // Not a major iteration
        it = numeric_limits<Ordinal>::max();
        // Solve State
        optimizer->set_iter(it);
        optimizer->set_npredict(npredict_);
        optimizer->computeState(xp, obj);
      } else {
        it = numeric_cast<Ordinal>(iter_);
      }
      // make certain state is using the same control object as the adjoint
      state_->set_control(xp.get());
#if 0
      // Solve adjoint:  original method which doesn't use optimizer
      adjoint_->set_end_condition();
      adjoint_->compute(npredict_, xp, gp, it);
#else
      // SSC: use the Optimizer interface which is safer and easier
      optimizer->computeAdjoint(xp,obj,gp);
#endif
    } else {
      // Do something if control is not realizable
      throw DTK::exception("FDM::ROL::gradient control not realizable.");
    }

    // Finalize the gradient if needed (default is noop)
    optimizer->computeGradient(gp);

    // Apply scaling to gradient
    if ( use_precond_ ) {
      Teuchos::RCP<ROL::Vector<Real> > pg = g.clone();
      Control::Ptr pgp =
          (Teuchos::dyn_cast<ROL_FDM_Vector<Real> >(*pg)).getVector();
      diag_precond_->applyPreconditioner(*gp,*pgp);
      g.set(*pg);
      grad_->set(*pg);
    } else {
      grad_->set(g);
    }

    // Copy updated gradient back into ROL data structures
    /** \note SSC: this is a memory copy -- why is this needed */
    g.set(*grad_);
  }

  /// Apply objective function Hessian to a vector
  void hessVec(ROL::Vector<Real> &hv, const ROL::Vector<Real> &v,
               const ROL::Vector<Real> &x, Real &tol) {
    if ( useFDhessvec_ ) {
      // Create new storage
      Teuchos::RCP<ROL::Vector<Real> > xnew = x.clone();
      Control::Ptr xnewp =
        (Teuchos::dyn_cast<ROL_FDM_Vector<Real> >(*xnew)).getVector();
      // Set it to maximum ordinal
      Ordinal it = numeric_limits<Ordinal>::max();
      // Cast hv down to a FDM::Control::Ptr
      Control::Ptr hvp =
        (Teuchos::dyn_cast<ROL_FDM_Vector<Real> >(hv)).getVector();
      hv.zero();
      // Compute Newton quotient
      if ( useFDhessvec_ == 1 ) { // One sided finite differences
        // Get Step Length
        Real h = tol/v.norm();
        if ( scaleFDstepsize_ > 0.0 ) {
          h = scaleFDstepsize_ * 2.0/(v.norm()*v.norm())*tol;
        }
        // Compute modified iteration x + h*v
        xnew->set(x);
        xnew->axpy(h,v);
        // Solve State
        state_->set_initial_condition();
        state_->compute(npredict_, xnewp, it);
        // Solve Adjoint
        adjoint_->set_end_condition();
        adjoint_->compute(npredict_, xnewp, hvp, it);
        // Use existing gradient to compute Newton quotient
        hv.axpy(-1.0,*grad_);
        hv.scale(1.0/h);
      } else if ( useFDhessvec_ == 2 ) { // Central finite differences
        // Get Step Length
        Real h = std::sqrt(tol)/v.norm();
        if ( scaleFDstepsize_ > 0.0 ) {
          h = scaleFDstepsize_ * 2.0/(v.norm()*v.norm())*tol;
        }
        // Compute modified iteration x + ||x||*h*v
        xnew->set(x);
        xnew->axpy(x.norm()*h,v);
        // Solve State
        state_->set_initial_condition();
        state_->compute(npredict_, xnewp, it);
        // Solve Adjoint
        adjoint_->set_end_condition();
        adjoint_->compute(npredict_, xnewp, hvp, it);
        // Create new storage
        Teuchos::RCP<ROL::Vector<Scalar> > gnew = x.clone();
        Control::Ptr gnewp =
          (Teuchos::dyn_cast<ROL_FDM_Vector<Real> >(*gnew)).getVector();
        gnew->zero();
        // Compute modified iteration x - ||x||*h*v
        xnew->set(x);
        xnew->axpy(-x.norm()*h,v);
        // Solve State
        state_->set_initial_condition();
        state_->compute(npredict_, xnewp, it);
        // Solve Adjoint
        adjoint_->set_end_condition();
        adjoint_->compute(npredict_, xnewp, gnewp, it);
        // Use left and right gradients to compute Newton quotient
        hv.axpy(-1.0,*gnew);
        hv.scale(1.0/(2.0*h));
      }
    } else if ( secondOrderInfo_ && !useFDhessvec_ ) {
      // Cast hv container from ROL_FDM_Vector to Control::Ptr and set to zero
      Control::Ptr hvp =
        (Teuchos::dyn_cast<ROL_FDM_Vector<Real> >(hv)).getVector();
      hvp->zero();
      // Cast vector v from ROL_FDM_Vector to Control::Ptr
      const Control::Ptr vp = (Teuchos::dyn_cast<ROL_FDM_Vector<Real> >
                              (const_cast<ROL::Vector<Real> &>(v))).getVector();
      // Cast vector x from ROL_FDM_Vector to Control::Ptr and
      //   chop values -- this is NOT a valid projected method
      const Control::Ptr xp = (Teuchos::dyn_cast<ROL_FDM_Vector<Real> >
                              (const_cast<ROL::Vector<Real> &>(x))).getVector();
      xp->bound();

      // Apply Gauss-Newton Hessian approximation
      if ( xp->realizable() ) {
        Ordinal it = 0;
        if ( iter_ < 0 ) {
          it = numeric_limits<Ordinal>::max();
          state_->set_initial_condition();
          state_->compute(npredict_, xp, it);
        } else {
          it = numeric_cast<Ordinal>(iter_);
          //state_->griewank.reinitialize(state_->domain());
        }

        state_->set_control(xp.get());
        stateSens_->set_control(vp.get());

        stateSens_->set_initial_condition();
        stateSens_->compute(npredict_, vp, it);
        adjointSens_->set_end_condition();
        adjointSens_->compute(npredict_, xp, hvp, it);
      } else {
        // Do something if control is invalid
      }
    } else {  // default to identity Hessian approximation
      hv.set(v);
    }

    // Apply scaling to Hessian-times-a-vector
    if ( use_precond_ ) {
      Control::Ptr hvp =
        (Teuchos::dyn_cast<ROL_FDM_Vector<Real> >(hv)).getVector();
      Teuchos::RCP<ROL::Vector<Real> > phv = hv.clone();
      Control::Ptr phvp =
        (Teuchos::dyn_cast<ROL_FDM_Vector<Real> >(*phv)).getVector();
      diag_precond_->applyPreconditioner(*hvp,*phvp);
      hv.set(*phv);
    }
  }

};

} // namespace FDM

#endif // FDM_USE_ROL

#endif // FDM_ROL_HPP
