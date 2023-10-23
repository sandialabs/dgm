#ifndef ROL_SPLITUPDATE_LINESEARCHSTEP_HPP
#define ROL_SPLITUPDATE_LINESEARCHSTEP_HPP

/**
  \file  ROL_SplitUpdateLineSearchStep.hpp
  \brief An alternative Linesearch step which splits the update into separate stages  

*/
 
// ROL includes
#include "ROL_Types.hpp"
#include "ROL_Step.hpp"
#include "ROL_LineSearch.hpp"

// Unconstrained Methods
#include "ROL_GradientStep.hpp"
#include "ROL_NonlinearCGStep.hpp"
#include "ROL_SecantStep.hpp"
#include "ROL_NewtonStep.hpp"
#include "ROL_NewtonKrylovStep.hpp"

// Bound Constrained Methods
#include "ROL_ProjectedSecantStep.hpp"
#include "ROL_ProjectedNewtonStep.hpp"
#include "ROL_ProjectedNewtonKrylovStep.hpp"

#include <sstream>
#include <iomanip>

#include "Comm.hpp"

namespace DGM {

template<class Real> 
class SplitUpdateLineSearchStep : public ROL::Step<Real> {

private:

  const DGM::Comm::Ptr comm_;

  // RCPs to ROL objects
  ROL::Ptr<ROL::Step<Real> >        desc_;       ///< Unglobalized step object
  ROL::Ptr<ROL::Secant<Real> >      secant_;     ///< Secant object (used for quasi-Newton)
  ROL::Ptr<ROL::Krylov<Real> >      krylov_;     ///< Krylov solver object (used for inexact Newton)
  ROL::Ptr<ROL::NonlinearCG<Real> > nlcg_;       ///< Nonlinear CG object (used for nonlinear CG)
  ROL::Ptr<ROL::LineSearch<Real> >  lineSearch_; ///< Line-search object

  ROL::Ptr<ROL::Vector<Real> > d_;
  ROL::Ptr<ROL::Vector<Real> > gp_;

  // Strings
  std::string descName_;         ///< Name of the descent direction. Currently supports "Steepest Descent" and "Newton-Krylov"
  std::string krylovName_;       ///< Name of Krylov solver
  std::string lineSearchName_;   ///< Name of line search method
  std::string secantName_;       ///< Name of secant solver

  // Enumations
  ROL::EDescent            edesc_;  ///< Type of descent direction. Currently supports 
                                    ///< DESCENT_STEEPEST and DESCENT_NEWTONKRYLOV
  ROL::EKrylov             ekv_;    ///< Krylov solver type
  ROL::ESecant             esec_;   ///< Secant method type                               
  ROL::ELineSearch         els_;    ///< type of line search
  ROL::ECurvatureCondition econd_;  ///< type of curvature condition

  // Integers
  int iterKrylov_; ///< Number of Krylov iterations (used for inexact Newton)
  int flagKrylov_; ///< Termination flag for Krylov method (used for inexact Newton)
  int verbosity_;

  // Booleans
  bool acceptLastAlpha_;  ///< For backwards compatibility. When max function evaluations are reached take last step
  bool usePreviousAlpha_; ///< If true, use the previously accepted step length (if any) as the new initial step length
  bool useSecantPrecond_; ///< Whether or not a secant approximation is used for preconditioning inexact Newton
  bool computeObj_;

  Real fval_;  ///< Store objective value between compute and update

  ROL::ParameterList parlist_;


  class HessianNK : public ROL::LinearOperator<Real> {
  private:
    const ROL::Ptr<ROL::Objective<Real> > obj_;
    const ROL::Ptr<ROL::Vector<Real> > x_;
  public:
    HessianNK(const ROL::Ptr<ROL::Objective<Real> > &obj,
              const ROL::Ptr<ROL::Vector<Real> > &x) : obj_(obj), x_(x) {}
    void apply(ROL::Vector<Real> &Hv, const ROL::Vector<Real> &v, Real &tol) const {
      obj_->hessVec(Hv,v,*x_,tol);
    } 
  };

  class PrecondNK : public ROL::LinearOperator<Real> {
  private:
    const ROL::Ptr<ROL::Objective<Real> > obj_;
    const ROL::Ptr<ROL::Vector<Real> > x_;
  public:
    PrecondNK(const ROL::Ptr<ROL::Objective<Real> > &obj,
              const ROL::Ptr<ROL::Vector<Real> > &x) : obj_(obj), x_(x) {}
    void apply(ROL::Vector<Real> &Hv, const ROL::Vector<Real> &v, Real &tol) const {
      Hv.set(v.dual());
    }
    void applyInverse(ROL::Vector<Real> &Hv, const ROL::Vector<Real> &v, Real &tol) const {
      obj_->precond(Hv,v,*x_,tol);
    } 
  };


  Real GradDotStep(const ROL::Vector<Real> &g, const ROL::Vector<Real> &s,
                   const ROL::Vector<Real> &x,
                   ROL::BoundConstraint<Real> &bnd, Real eps = 0) {
    Real gs(0), one(1);
    if (!bnd.isActivated()) {
      gs = s.dot(g.dual());
    }
    else {
      d_->set(s);
      bnd.pruneActive(*d_,g,x,eps);
      gs = d_->dot(g.dual());
      d_->set(x);
      d_->axpy(-one,g.dual());
      bnd.project(*d_);
      d_->scale(-one);
      d_->plus(x);
      bnd.pruneInactive(*d_,g,x,eps);
      gs -= d_->dot(g.dual());
    }
    return gs;
  }  

public:

  using ROL::Step<Real>::initialize;
  using ROL::Step<Real>::compute;
  using ROL::Step<Real>::update;


  SplitUpdateLineSearchStep(DGM::Comm::Ptr comm, ROL::ParameterList &parlist,
                            const ROL::Ptr<ROL::LineSearch<Real> > &lineSearch = ROL::nullPtr,
                            const ROL::Ptr<ROL::Secant<Real> > &secant = ROL::nullPtr,
                            const ROL::Ptr<ROL::Krylov<Real> > &krylov = ROL::nullPtr,
                            const ROL::Ptr<ROL::NonlinearCG<Real> > &nlcg = ROL::nullPtr ) : 
    ROL::Step<Real>(), comm_(comm), desc_(ROL::nullPtr), secant_(secant),
      krylov_(krylov), nlcg_(nlcg), lineSearch_(lineSearch), d_(ROL::nullPtr), gp_(ROL::nullPtr), 
      edesc_(ROL::DESCENT_STEEPEST), ekv_(ROL::KRYLOV_CG), esec_(ROL::SECANT_LBFGS), 
      els_(ROL::LINESEARCH_USERDEFINED), econd_(ROL::CURVATURECONDITION_WOLFE),
      iterKrylov_(0), flagKrylov_(0), verbosity_(0), acceptLastAlpha_(true),
      usePreviousAlpha_(true), useSecantPrecond_(false), computeObj_(true), fval_(0), parlist_(parlist)  {

    // Parse parameter list
    ROL::ParameterList& Llist = parlist.sublist("Step").sublist("Line Search");
    ROL::ParameterList& Glist = parlist.sublist("General");

    verbosity_ = Glist.get("Print Verbosity",0);

    econd_ = ROL::StringToECurvatureCondition(Llist.sublist("Curvature Condition").get("Type","Strong Wolfe Conditions") );

    descName_ = Llist.sublist("Descent Method").get("Type","Steepest Descent");
    edesc_ = ROL::StringToEDescent(descName_);

    acceptLastAlpha_ = Llist.get("Accept Last Alpha", false); 
    verbosity_ = Glist.get("Print Verbosity",0);
    computeObj_ = Glist.get("Recompute Objective Function",false);

    if( edesc_ == ROL::DESCENT_NEWTONKRYLOV ) {
      // Initialize Krylov object
      krylovName_ = Glist.sublist("Krylov").get("Type","Conjugate Gradients");
      ekv_ = ROL::StringToEKrylov(krylovName_);
      krylov_ = ROL::KrylovFactory<Real>(parlist);

      secantName_ = Glist.sublist("Secant").get("Type","Limited-Memory BFGS");
      esec_ = ROL::StringToESecant(secantName_);

      useSecantPrecond_ = Glist.sublist("Secant").get("Use as Preconditioner", false);

      if ( useSecantPrecond_ ) {
        secant_ = ROL::SecantFactory<Real>(parlist);
      }

    }

    // Initialize Line Search
    if (lineSearch_ == ROL::nullPtr) {
      lineSearchName_ = Llist.sublist("Line-Search Method").get("Type","Cubic Interpolation"); 
      els_ = ROL::StringToELineSearch(lineSearchName_);
      lineSearch_ = ROL::LineSearchFactory<Real>(parlist);
    } 
    else { // User-defined linesearch provided
      lineSearchName_ = Llist.sublist("Line-Search Method").get("User Defined Line-Search Name",
                                                                "Unspecified User Defined Line-Search");
    }
    computeObj_ = parlist.sublist("General").get("Recompute Objective Function",false);
  }




  void initialize(ROL::Vector<Real> &x, const ROL::Vector<Real> &s, const ROL::Vector<Real> &g,
                  ROL::Objective<Real> &obj, ROL::BoundConstraint<Real> &bnd,
                  ROL::AlgorithmState<Real> &algo_state ) {

    ROL::Step<Real>::initialize(x,s,g,obj,bnd,algo_state);

    comm_->cout() << "SplitUpdateLineSearchStep::initialize()" << std::endl;

    if( edesc_ == ROL::DESCENT_NEWTONKRYLOV ) {
      desc_ = ROL::makePtr<ROL::NewtonKrylovStep<Real>>(parlist_,computeObj_);
    }
    else {
      desc_ = ROL::makePtr<ROL::GradientStep<Real>>(parlist_,computeObj_);
      d_ = x.clone();
    }

    lineSearch_->initialize(x,s,g,obj,bnd);
  }





  void compute(ROL::Vector<Real> &s, const ROL::Vector<Real> &x,
               ROL::Objective<Real> &obj, ROL::BoundConstraint<Real> &bnd,
               ROL::AlgorithmState<Real> &algo_state ) {
    comm_->cout() << "SplitUpdateLineSearchStep::compute()" << std::endl;
    Real zero(0), one(1);

    ROL::Ptr<ROL::StepState<Real> > step_state = ROL::Step<Real>::getState(); 

    if( edesc_ == ROL::DESCENT_NEWTONKRYLOV ) {
    // Build Hessian and Preconditioner object
      ROL::Ptr<ROL::Objective<Real> > obj_ptr = ROL::makePtrFromRef(obj);
      ROL::Ptr<ROL::LinearOperator<Real> > hessian
        = ROL::makePtr<HessianNK>(obj_ptr,algo_state.iterateVec);
      ROL::Ptr<ROL::LinearOperator<Real> > precond;
      if ( useSecantPrecond_ ) {
        precond = secant_;
      }
      else {
        precond = ROL::makePtr<PrecondNK>(obj_ptr,algo_state.iterateVec);
      }

      // Run Krylov method
      flagKrylov_ = 0;
      krylov_->run(s,*hessian,*(step_state->gradientVec),*precond,iterKrylov_,flagKrylov_);

      // Check Krylov flags
      if ( flagKrylov_ == 2 && iterKrylov_ <= 1 ) {
        s.set((step_state->gradientVec)->dual());
      }
    }
    else { // Steepest Descent
    
      s.set((step_state->gradientVec)->dual());

    } 

    s.scale(-one);

    // Ensure that s is a descent direction
    // ---> If not, then default to steepest descent
    Real gs = GradDotStep(*(step_state->gradientVec),s,x,bnd,algo_state.gnorm);
    if (gs >= zero) {
      s.set((step_state->gradientVec)->dual());
      s.scale(-one);
      gs = GradDotStep(*(step_state->gradientVec),s,x,bnd,algo_state.gnorm);
    }


    // Perform line search
    fval_ = algo_state.value;
    step_state->nfval = 0; step_state->ngrad = 0;


    lineSearch_->setData(algo_state.gnorm,*(step_state->gradientVec));
    lineSearch_->run(step_state->searchSize,fval_,step_state->nfval,step_state->ngrad,gs,s,x,obj,bnd);


    algo_state.value = fval_;

    // Make correction if maximum function evaluations reached
    if(!acceptLastAlpha_) {
      lineSearch_->setMaxitUpdate(step_state->searchSize,fval_,algo_state.value);
    }

    // Compute scaled descent direction
    s.scale(step_state->searchSize);
    if ( bnd.isActivated() ) {
      s.plus(x);
      bnd.project(s);
      s.axpy(static_cast<Real>(-1),x);
    }

    algo_state.snorm = s.norm();

 }

   void update( ROL::Vector<Real> &x, const ROL::Vector<Real> &s,
                ROL::Objective<Real> &obj, ROL::BoundConstraint<Real> &bnd,
                ROL::AlgorithmState<Real> &algo_state ) {

    Scalar tol = ROL::ROL_EPSILON<Scalar>();
    comm_->cout() << "SplitUpdateLineSearchStep::update()" << std::endl;
    ROL::Ptr<ROL::StepState<Real> > step_state = ROL::Step<Real>::getState();
    algo_state.nfval += step_state->nfval;
    algo_state.ngrad += step_state->ngrad;

    // If we have already computed a step vector
    algo_state.iter++;
    x.plus(s);
    (step_state->descentVec)->set(s);
    algo_state.snorm = s.norm();

    dynamic_cast<ROLinterface::Objective<Real>&>(obj).reset(x,algo_state.iter);

    // Compute new objective and gradient
    obj.update(x,true,algo_state.iter);
    algo_state.value = obj.value(x,tol);      
    algo_state.value = fval_;
    algo_state.nfval++;
    obj.gradient(*(step_state->gradientVec),x,tol);
    algo_state.ngrad++;

    
    if( edesc_ == ROL::DESCENT_NEWTONKRYLOV && useSecantPrecond_ ) {
     
      // Update Secant Information
      secant_->updateStorage(x,*(step_state->gradientVec),*gp_,s,algo_state.snorm,algo_state.iter+1);
    }

    (algo_state.iterateVec)->set(x);
    algo_state.gnorm = (step_state->gradientVec)->norm();

  }



  void updateVector( ROL::Vector<Real> &x, const ROL::Vector<Real> &s,
                     ROL::Objective<Real> &obj, ROL::BoundConstraint<Real> &bnd,
                     ROL::AlgorithmState<Real> &algo_state ) {
    comm_->cout() << "SplitUpdateLineSearchStep::updateVector()" << std::endl;
    ROL::Ptr<ROL::StepState<Real> > step_state = ROL::Step<Real>::getState();

    algo_state.iter++;
    x.plus(s);
    (step_state->descentVec)->set(s);
    algo_state.snorm = s.norm();
  }

  void updateObjective( ROL::Vector<Real> &x, const ROL::Vector<Real> &s,
                        ROL::Objective<Real> &obj, ROL::BoundConstraint<Real> &bnd,
                        ROL::AlgorithmState<Real> &algo_state ) {
    
    comm_->cout() << "SplitUpdateLineSearchStep::updateObjective()" << std::endl;

    Scalar tol = ROL::ROL_EPSILON<Scalar>();
    obj.update(x,true,algo_state.iter);
    algo_state.value = obj.value(x,tol);
    algo_state.nfval++;
    (algo_state.iterateVec)->set(x);
 
    ROL::Ptr<ROL::StepState<Real> > step_state = ROL::Step<Real>::getState();
    obj.gradient(*(step_state->gradientVec),x,tol);

    if( edesc_ == ROL::DESCENT_NEWTONKRYLOV && useSecantPrecond_ ) {
     
      // Update Secant Information
      secant_->updateStorage(x,*(step_state->gradientVec),*gp_,s,algo_state.snorm,algo_state.iter+1);
    }

    algo_state.ngrad++;      
    algo_state.gnorm = (step_state->gradientVec)->norm();
    
  }

  /** \brief Print iterate header.

      This function produces a string containing header information.
  */
  std::string printHeader( void ) const {
    std::string head = desc_->printHeader();
    head.erase(std::remove(head.end()-3,head.end(),'\n'), head.end());
    std::stringstream hist;
    hist.write(head.c_str(),head.length());
    hist << std::setw(10) << std::left << "ls_#fval";
    hist << std::setw(10) << std::left << "ls_#grad";
    hist << "\n";
    return hist.str();
}
  
  /** \brief Print step name.

      This function produces a string containing the algorithmic step information.
  */
  std::string printName( void ) const {
    std::string name = desc_->printName();
    std::stringstream hist;
    hist << name;
    hist << "Line Search: " << lineSearchName_;
    hist << " satisfying " << ROL::ECurvatureConditionToString(econd_) << "\n";
    return hist.str();
  }

  /** \brief Print iterate status.

      This function prints the iteration status.

      @param[in]     algo_state    is the current state of the algorithm
      @param[in]     printHeader   if ste to true will print the header at each iteration
  */
  std::string print( ROL::AlgorithmState<Real> &algo_state, bool print_header = false ) const {
    std::stringstream hist;
    hist << std::scientific << std::setprecision(6);
    if ( algo_state.iter == 0 ) {
      hist << printName();
    }
    if ( print_header ) {
      hist << printHeader();
    }
    if ( algo_state.iter == 0 ) {
      hist << "  ";
      hist << std::setw(6) << std::left << algo_state.iter;
      hist << std::setw(15) << std::left << algo_state.value;
      hist << std::setw(15) << std::left << algo_state.gnorm;
      hist << "\n";
    }
    else {
      hist << "  ";
      hist << std::setw(6)  << std::left << algo_state.iter;
      hist << std::setw(15) << std::left << algo_state.value;
      hist << std::setw(15) << std::left << algo_state.gnorm;
      hist << std::setw(15) << std::left << algo_state.snorm;
      hist << std::setw(10) << std::left << algo_state.nfval;
      hist << std::setw(10) << std::left << algo_state.ngrad;
      if(  edesc_ == ROL::DESCENT_NEWTONKRYLOV ) {
        hist << std::setw(10) << std::left << iterKrylov_;
        hist << std::setw(10) << std::left << flagKrylov_;
        hist << "\n";
      }
    }
    return hist.str();
  }
  


}; // class SplitUpdateLineSearchStep

} // namespace DGM

#endif // ROL_SPLITUPDATE_LINESEARCHSTEP_HPP
