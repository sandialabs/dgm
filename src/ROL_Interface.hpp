#ifndef DGM_ROL_INTERFACE_HPP
#define DGM_ROL_INTERFACE_HPP

/** \file ROL_Interface.hpp
    \brief Provides DGM specific functionality to ROL.
    \author Drew Kouri
    \author Denis Ridzal
    \author Bart van Bloemen Waanders
    \author Scott Collis
    \copyright 2014(c) Sandia National Laboratories
*/

#ifdef DGM_USE_ROL

// system includes
#include <iostream>
#include <limits>

// boost includes
#include <boost/numeric/conversion/cast.hpp>

// DGM includes
#include "Comm.hpp"
#include "Format.hpp"
#include "MultiOptProblem.hpp"
#include "Optimizer.hpp"
#include "Regularization.hpp"
#include "ReoOptProblem.hpp"
#include "String.hpp"

// ROL includes
#include "ROL_Objective.hpp"

namespace DGM {

/// Contains the DGM interface to ROL
namespace ROLinterface {

// Forward declaration of getControl(Vector) methods
template<typename Real> inline 
Control::Ptr getControl( ROL::Vector<Real>& );

template<typename Real> inline 
Control::Ptr getControl( const ROL::Ptr<ROL::Vector<Real>>& );

template<typename Real> inline 
const Control::Ptr getControl( const ROL::Vector<Real>& );

template<typename Real> inline 
const Control::Ptr getControl( const ROL::Ptr<const ROL::Vector<Real>>& );


/// DGM interface to the ROL vector class
template <class Real>
class Vector : public ROL::Vector<Real> {

  Control::Ptr vec_;       ///< wrapped DGM::Control pointer
  int verb;                ///< local verbosity level

public:

  Vector(Control::Ptr vec) : vec_(vec), verb(0) {}

  void scale(const Real alpha) {
    DGM::scale(alpha,vec_);
  }

  void plus(const ROL::Vector<Real> &x) {
    DGM::add( getControl(x) ,vec_ );
  }

  void axpy(const Real alpha, const ROL::Vector<Real> &x) {
    DGM::axpy( alpha, getControl(x), vec_ );
  }

  void zero(){
    (vec_)->zero();
  }

  Real dot(const ROL::Vector<Real> &x) const {
    return (vec_)->inner_product( getControl(x) );
  }

  Real norm() const {
    return (vec_)->norm();
  }

  ROL::Ptr<ROL::Vector<Real> > clone() const {
    Control::Ptr tmp;
    tmp.reset(vec_->clone());
    return ROL::makePtr<Vector>( tmp );
  }

  Control::Ptr getVector() {
    return vec_;
  }

  const Control::Ptr getVector() const {
    return vec_;
  }
};


template<typename Real> inline 
Control::Ptr getControl( ROL::Vector<Real>& x ) {
  return static_cast<Vector<Real>&>(x).getVector();
}

template<typename Real> inline 
const Control::Ptr getControl( const ROL::Vector<Real>& x ) {
  return static_cast<const Vector<Real>&>(x).getVector();
}

template<typename Real> inline 
Control::Ptr getControl( const ROL::Ptr<ROL::Vector<Real>>& x ) {
  return (ROL::dynamicPtrCast<Vector<Real>>(x))->getVector();
}

template<typename Real> inline 
const Control::Ptr getControl( const ROL::Ptr<const ROL::Vector<Real>>& x ) {
  return (ROL::dynamicPtrCast<const Vector<Real>>(x))->getVector();
}


template<class Real> 
class ObjectiveBase : public ROL::Objective<Real> {
public:
  virtual void precompute(const bool precompute) = 0;
  virtual bool precompute() const = 0;

  virtual void reset(const ROL::Vector<Real> &x, int iter ) = 0;

};

/// Define the objective function
template <class Real>
class Objective : public ObjectiveBase<Real> {

  State*   state_;        ///< DGM State object
  Adjoint* adjoint_;      ///< DGM Adjoint object
  State*   stateSens_;    ///< DGM State object for state sensitivity
  Adjoint* adjointSens_;  ///< DGM Adjoint object for adjoint sensitivity
  Ordinal  npredict_;     ///< Number of time steps in time horizon
  Ordinal  reset_obj_;    ///< Reset objective function
  Optimizer *optimizer;   ///< Optimizer object

  bool         use_precond_;   ///< use diagonal preconditioner
  Control::Ptr diag_precond_;  ///< storage for diagonal preconditioner

  bool secondOrderInfo_;  ///< Use Gauss-Newton hessvec
  int  useFDhessvec_;     ///< Use finite-difference hessvec
  Real scaleFDstepsize_;  ///< Scale for finite-difference step size
  bool precompute_;       ///< State/Gradient computed before checkGradient

  int iter_;              ///< Major iteration index
  Real val_;              ///< Value of the objective function

  ROL::Ptr<ROLinterface::Vector<Real> > grad_;

  const DGM::Comm::Ptr comm;  ///< DGM communicator
  const int verb;             ///< verbosity level

public:

  /// Construct first order algorithms
  Objective( State* state, Adjoint* adjoint, Control::Ptr x,
             Table &params, Control::Ptr diag_precond, Optimizer *opt)
  : state_(state), adjoint_(adjoint), npredict_(params["npredict"]),
    reset_obj_(params["reset_obj"]), optimizer(opt),
    use_precond_(params["use_precond"]),
    diag_precond_(diag_precond), secondOrderInfo_(false),
    useFDhessvec_(params["useFDhessvec"]),
    scaleFDstepsize_(params["scaleFDstepsize"]), precompute_(true),
    iter_(-1), val_(0), comm(state_->domain()->get_comm()), verb(comm->verbosity())
  {
    comm->cout() << "Constructing DGM::ROLinterface::Objective" << endl;
    comm->cout() << "  useFDhessvec = " << useFDhessvec_ << endl;
    comm->cout() << "  scaleFDstepsize = " << scaleFDstepsize_ << endl;
    grad_ = ROL::makePtr<ROLinterface::Vector<Real>>(x);
  }

  /// Construct second order algorithms
  Objective( State* state, Adjoint* adjoint, Control::Ptr x,
             State* stateSens, Adjoint* adjointSens,
             Table &params, Control::Ptr diag_precond,
             Optimizer *opt  )
  : state_(state), adjoint_(adjoint), stateSens_(stateSens),
    adjointSens_(adjointSens), npredict_(params["npredict"]),
    reset_obj_(params["reset_obj"]),
    optimizer(opt), use_precond_(params["use_precond"]),
    diag_precond_(diag_precond),
    secondOrderInfo_(true), useFDhessvec_(params["useFDhessvec"]),
    scaleFDstepsize_(params["scaleFDstepsize"]), precompute_(true),
    iter_(-1), val_(0), comm(state_->domain()->get_comm()), verb(comm->verbosity())
  {
    grad_ = ROL::makePtr<ROLinterface::Vector<Real>>(x);
  }

  virtual ~Objective() {}

  void precompute(const bool precompute) { precompute_ = precompute; }
  bool precompute() const { return precompute_; }

  void reset(const ROL::Vector<Real> &x, int iter ) {
    if ( reset_obj_ ) {
      if ( numeric_cast<Ordinal>(iter)%reset_obj_ == 0 ) {
        comm->cout() << "ROLinterface::Objective::reset()" << std::endl;
        state_->get_objective()->reset();
        if ( secondOrderInfo_ && !useFDhessvec_ ) {
          stateSens_->get_objective()->reset();
        }
      }
    }
//    update( x, true, iter);
  }

  /// Update the objective function member variables
  void update(const ROL::Vector<Real> &x, bool flag = true, int iter = -1) {
    Format sci(8); sci.scientific().width(15);
    Format hisci(15); hisci.scientific().width(21);

//    if (verb>1) comm->cout()<<"ROL::update(iter="<<iter<<")"<<endl;
    // Store current optimization iteration -- if iter = -1,
    //   then this is a linesearch iteration and we MAY not
    //   need to store the state
    // iter_ = iter>0 ?  iter+1 : iter;
    iter_ = iter;

    // Redundant - already done by optimizer->testState()
//    state_->set_initial_condition();

    // Cast the Vector to a Control::Ptr and chop the
    //   control -- This is NOT a valid projected method!
    const Control::Ptr xp = getControl(x); 

    // Solve the state at the new control and compute objective
    //   function value
    xp->bound();

    if ( xp->realizable() ) {
      // conform to DGM::Optimizer interface
      if (iter_<0) {
//        comm->cout() << "Minor iterate" << std::endl;
        optimizer->set_iter(iter_);
        optimizer->set_npredict(npredict_);
        //state_->outputTest(true);
        val_ = optimizer->testState(xp, state_->get_objective());
        //comm->cout()<<"J = "<<hisci(val_)<<endl;
        comm->cout()<<"J = "<<sci(val_)<<endl;
      } else {
//        comm->cout() << "Major iterate" << std::endl;
        optimizer->set_iter(iter_);
        optimizer->set_npredict(npredict_);
        val_ = optimizer->computeState(xp, state_->get_objective());
        //comm->cout()<<"J = "<<hisci(val_)<<endl;
        //val_ = optimizer->testState(xp, state_->get_objective());
        //comm->cout()<<"J = "<<hisci(val_)<<endl;
        //val_ = optimizer->computeState(xp, state_->get_objective());
        //comm->cout()<<"J = "<<hisci(val_)<<endl;
        //val_ = optimizer->testState(xp, state_->get_objective());
        //comm->cout()<<"J = "<<hisci(val_)<<endl;
      }
    } else {
      throw DGM::exception("DGM::ROL::update control not realizable.");
    }
  }

  /// Compute objective function value
  Real value(const ROL::Vector<Real> &x, Real &tol) {
    if (verb>1) 
      comm->cout()<<"iter = "<<iter_<<", "<<"RoL::value() = "<<val_<<endl;
    return val_;
  }

  /// Compute objective function gradient
  void gradient(ROL::Vector<Real> &g, const ROL::Vector<Real> &x, Real &tol) {
    if (verb>1) comm->cout()<<"RoL::gradient()"<<endl;

    // Cast the ROLinterface::Vector to a Control::Pt and set to zero
    Control::Ptr gp = getControl(g); 
    gp->zero();

    // Cast the ROLinterface::Vector to a Control::Ptr and chop the control
    /// \warning This is NOT a valid projected method!
    const Control::Ptr xp = getControl(x); 

#ifdef SCOTT_TURNED_OFF
    // SSC:  Why in the world would you ever do this here?
    xp->bound();
#endif

    DGM::Objective *obj = state_->get_objective();

    // Return gradient
    if ( xp->realizable() ) {
      // make certain state is using the same control object as the adjoint
      state_->set_control(xp.get());
      // SSC: use the Optimizer interface which is safer and easier
      optimizer->computeAdjoint(xp,obj,gp);
    } else {
      // Do something if control is not realizable
      throw DGM::exception("DGM::ROL::gradient control not realizable.");
    }

    // Finalize the gradient if needed (default is noop)
    optimizer->computeGradient(gp);

    // Apply scaling to gradient
    if ( use_precond_ ) {
      ROL::Ptr<ROL::Vector<Real> > pg = g.clone();
      Control::Ptr pgp = getControl(*pg);

      diag_precond_->applyPreconditioner(gp,pgp);
      g.set(*pg);
      grad_->set(*pg);
    } else {
      grad_->set(g);
    }

    // Copy updated gradient back into ROL data structures
    /** \note SSC: this is a memory copy -- why is this needed */
    g.set(*grad_);

    // output norms of the gradient
    static Format sci(8); sci.scientific().width(15);
    double total_g = gp->norm();
    comm->cout()<<"||Grad(J)|| = "<<sci(total_g)<<endl;
    dVector gradient_norms(numeric_cast<Ordinal>(gp->num_ctrl()));
    gradient_norms = gp->norms();
    vector<string> names(gp->names());
    for (Ordinal i=0; i<gradient_norms.size(); ++i)
      comm->cout()<<"  ||dJ/d(" << names[i] << ")|| = "
                  <<sci(gradient_norms[i])<<endl;
  }

  /// Apply objective function Hessian to a vector
  void hessVec(ROL::Vector<Real> &hv, const ROL::Vector<Real> &v,
               const ROL::Vector<Real> &x, Real &tol) {
    if (verb>1) comm->cout()<<"RoL::hessVec()"<<endl;
    if ( useFDhessvec_ ) {
      if( comm->verbosity()>3 ) {
        comm->cout()<<"useFDhessvec = " << useFDhessvec_ << endl;
      }

      // Create new storage
      ROL::Ptr<ROL::Vector<Real> > xnew = x.clone();

      Control::Ptr xnewp = getControl(*xnew);
      // Set it to maximum ordinal
      Ordinal it = numeric_limits<Ordinal>::max();
      // Cast hv down to a DGM::Control::Ptr
      Control::Ptr hvp = getControl(hv);
      hv.zero();
      // Compute Newton quotient
      if ( useFDhessvec_ == 1 ) { // One sided finite differences
        if( comm->verbosity()>3 ) {
          comm->cout() << "Using one-sided differences" << endl;
        }
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
        comm->cout()<<"Using centered differences"<<endl;
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
        ROL::Ptr<ROL::Vector<Scalar> > gnew = x.clone();
        Control::Ptr gnewp = getControl(*gnew);
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
      comm->cout()<<"Using second order information (not implemented!)"<<endl;
      // Cast hv container from ROLinterface::Vector to Control::Ptr and set to zero
      Control::Ptr hvp = getControl(hv);
      hvp->zero();
      // Cast vector v from ROLinterface::Vector to Control::Ptr
      const Control::Ptr vp = getControl(v);
      // Cast vector x from ROLinterface::Vector to Control::Ptr and
      //   chop values -- this is NOT a valid projected method
      const Control::Ptr xp = getControl(x);
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
          state_->griewank.reinitialize(state_->domain());
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
      comm->cout()<<"Treating Hessian as identity"<<endl;
      hv.set(v);
    }

    // Apply scaling to Hessian-times-a-vector
    if ( use_precond_ ) {
      Control::Ptr hvp = getControl(hv);
      ROL::Ptr<ROL::Vector<Real> > phv = hv.clone();
      Control::Ptr phvp = getControl(*phv);
      diag_precond_->applyPreconditioner(hvp,phvp);
      hv.set(*phv);
    }
  }

  // Apply "inverse Hessian" to a vector
  // In reality, we will never have an inverse Hessian available, however, we
  // can use a supplied "preconditioner" to rescale the gradient and produce
  // something like a Newton method
  void invHessVec( ROL::Vector<Real> &hv, const ROL::Vector<Real> &v,
      const ROL::Vector<Real> &x, Real &tol ) {
    if (verb>1) comm->cout()<<"RoL::invHessVec()"<<endl;
    if(use_precond_) {
       Control::Ptr hvp = getControl(hv);
      ROL::Ptr<ROL::Vector<Real> > phv = hv.clone();
      Control::Ptr phvp = getControl(*phv);
      diag_precond_->applyPreconditioner(hvp,phvp);
      hv.set(*phv);
    } else {
      hv.set(v);
    }
  }

  // Apply Preconditioner
//  void precond(       ROL::Vector<Real>& Pv,
//                const ROL::Vector<Real>& v,
//                const ROL::Vector<Real>& x, 
//                Real& tol ) {
//    if (verb>1) comm->cout()<<"ROL::precond()"<<endl;
//    if(use_precond_) {
//       diag_precond_->applyPreconditioner( getControl(v), getControl(Pv) );
//    } else {
//      Pv.set(v);
//    }
//  }


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

#endif // DGM_ROL_INTERFACE_HPP
