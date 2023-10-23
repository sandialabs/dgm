#ifndef ROL_DGM_LINESEARCH_HPP
#define ROL_DGM_LINESEARCH_HPP

/**
  \file   ROL_DGM_LineSearch.hpp
  \brief  Wrapper to allow ROL to call DGM::LineSearch

  A wrapper class which allows ROL to call DGM::LineSearch using
  DGM's bracketing and Brent's method
*/

// ROL includes
#include "ROL_LineSearch.hpp"

// DGM includes
#include "ROL_Interface.hpp"
#include "LineSearch.hpp"
#include "Color.hpp"

namespace DGM { 

namespace ROLinterface {

/// Implement the DGM evaluator interface for ROL
template<class Real> 
class Eval : public DGM::Eval<Real> {
private:
  ROL::ScalarFunction<Real> &f;
public:
  Eval( ROL::ScalarFunction<Real> &f_ ) : DGM::Eval<Real>(), f(f_) {}
  Real operator() (const Real & x) {
    Format sci(8); sci.scientific().width(15); 
    this->increment();
    Real fval = f.value(x);
//   this->comm_->cout() << "eval(" << sci(x)<< ") = " << sci(fval) << std::endl;
    return fval;
  }
};

/// Make the DGM::LineSearch available to ROL
template<class Real>
class LineSearch : public ROL::LineSearch<Real> {
private:
  ROL::Ptr<ROL::Vector<Real> > xnew_; 
  ROL::Ptr<ROL::Vector<Real> > g_;
  const DGM::Comm::Ptr comm_;
  int niter_;
  bool useOriginalBrents_;
  Real dgm_brents_tol_alpha_;


  class Phi : public ROL::ScalarFunction<Real> {
  private:
    const DGM::Comm::Ptr comm_;
    const ROL::Ptr<ROL::Vector<Real> > xnew_;
    const ROL::Ptr<ROL::Vector<Real> > g_;
    const ROL::Ptr<const ROL::Vector<Real> > x_;
    const ROL::Ptr<const ROL::Vector<Real> > s_;
    const ROL::Ptr<ROL::Objective<Real> > obj_;
    const ROL::Ptr<ROL::BoundConstraint<Real> > con_;
    Real ftol_;


    void updateIterate(Real alpha) {
      Format sci(8); sci.scientific().width(15); 
//      comm_->cout() << "ROL_DGM_LineSearch::Phi::updateIterate(" << sci(alpha) << ")" << std::endl;
      xnew_->set(*x_);
      xnew_->axpy(alpha,*s_);
//      comm_->cout() <<   "||x|| = " << sci(x_->norm()) 
//                    << ", ||s|| = " << sci(s_->norm()) 
//                    << ", ||xnew|| = ||x+alpha*s|| = " << sci(xnew_->norm()) << std::endl;
//      comm_->cout() << "Applying control bound to xnew" << std::endl;
//      ((ROL::dynamicPtrCast<ROLinterface::Vector<Real> >(xnew_))->getVector())->bound();
 //     new_control_->bound();
//      comm_->cout() <<   "||xnew|| = " << sci(xnew_->norm()) << std::endl;
      getControl(xnew_)->bound();   
      
      if ( con_->isActivated() ) {
        con_->project(*xnew_);
      }
    }
  public:
    Phi(const DGM::Comm::Ptr comm,
        const ROL::Ptr<ROL::Vector<Real> > &xnew,
        const ROL::Ptr<ROL::Vector<Real> > &g,
        const ROL::Ptr<const ROL::Vector<Real> > &x,
        const ROL::Ptr<const ROL::Vector<Real> > &s,
        const ROL::Ptr<ROL::Objective<Real> > &obj,
        const ROL::Ptr<ROL::BoundConstraint<Real> > &con)
     : comm_(comm), xnew_(xnew), g_(g), x_(x), s_(s), obj_(obj), con_(con),
       ftol_(std::sqrt(ROL::ROL_EPSILON<Real>()))
 {}
    Real value(const Real alpha) {
      updateIterate(alpha);
      obj_->update(*xnew_);
      return obj_->value(*xnew_,ftol_);
    }
    Real deriv(const Real alpha) {
      updateIterate(alpha);
      obj_->update(*xnew_);
      obj_->gradient(*g_,*xnew_,ftol_);
      return s_->dot(g_->dual()); 
    }
  };
public:
  /// Constructor
  LineSearch( ROL::ParameterList &parlist,
    const DGM::Comm::Ptr comm = DGM::Comm::World,
    Real dgm_brents_tol_alpha=1.e-5 )
    : ROL::LineSearch<Real>(parlist), comm_(comm), 
      dgm_brents_tol_alpha_(dgm_brents_tol_alpha) {
    ROL::ParameterList &list0 =
        parlist.sublist("Step").sublist("Line Search");
    ROL::ParameterList &list  = list0.sublist("Line-Search Method");

    niter_ = parlist.sublist("Step").sublist("Line Search").get("Function Evaluation Limit",10);
    
//    static Color yellow(Color::YELLOW);
//    static Color def(Color::DEFAULT);


    if ( list.isParameter("Type") ) {
      std::string lstype = list.get("Type","ROL Brent's");
//      comm->cout() << yellow << lstype << def << endl;
      if( (lstype == "DGM Brent's") || (lstype == "DGM Brents") ) {
        useOriginalBrents_ = true;
        comm->cout() << "Using DGM Brent's tol_alpha=" << dgm_brents_tol_alpha_ << std::endl;
      }
      else {
        useOriginalBrents_ = false;
      }
    }
    else { 
       useOriginalBrents_ = false;
    }   // comm_->cout() << parlist;
  }

  void initialize( const ROL::Vector<Real> &x, const ROL::Vector<Real> &s,
      const ROL::Vector<Real> &g,
      ROL::Objective<Real> &obj, ROL::BoundConstraint<Real> &con ) {
    ROL::LineSearch<Real>::initialize(x,s,g,obj,con);
    xnew_ = x.clone();
    g_    = g.clone();
  }

  /// Find the minimum of phi(alpha) = f(x + alpha*s)  Brent's method
  void run( Real &alpha, Real &fval, int &ls_neval, int &ls_ngrad,
            const Real &gs, const ROL::Vector<Real> &s,
            const ROL::Vector<Real> &x,
            ROL::Objective<Real> &obj, ROL::BoundConstraint<Real> &con ) {
    static Format sci(10); sci.scientific().width(17);
    const DGM::Comm::Ptr comm(comm_);
    const bool bracket_output = false;
    static Color red(Color::RED);
    static Color green(Color::GREEN);
    static Color bold(Color::BOLD);
    static Color def(Color::DEFAULT);

    comm->cout()<<bold<<"ROLinterface::LineSearch::run()"<<def<<endl;

    ls_neval = 0; ls_ngrad = 0;

    // Get initial line search parameter
    alpha = ROL::LineSearch<Real>::getInitialAlpha(ls_neval,ls_ngrad,fval,
                                                   gs,x,s,obj,con);

    // Build ScalarFunction and ScalarMinimizationStatusTest
    ROL::Ptr<const ROL::Vector<Real> > x_ptr = makePtrFromRef(x);
    ROL::Ptr<const ROL::Vector<Real> > s_ptr = makePtrFromRef(s);
    ROL::Ptr<ROL::Objective<Real> > obj_ptr = makePtrFromRef(obj);
    ROL::Ptr<ROL::BoundConstraint<Real> > bnd_ptr=makePtrFromRef(con);

    Phi phi(comm_,xnew_,g_,x_ptr,s_ptr,obj_ptr,bnd_ptr);

    ROL::Ptr<Eval<Real> > eval = ROL::makePtr<ROLinterface::Eval<Real>>(phi);

    DGM::LineSearch lineSearch(*eval, comm_, DGM::LineSearch::TEST_OUTPUT);
    lineSearch.setUseOriginalBrents(useOriginalBrents_);

    Real ax, bx, cx, fa, fb, fc;

    ax = 0.0;
    fa = fval;
    fc = 0.0;
    int nfval = 0;
    bx = alpha; 
    fb = phi.value(bx);
    nfval++;

    // Run DGM Bracketing
    nfval += static_cast<int>( lineSearch.bracket(ax,bx,cx,fa,fb,fc) );

    comm->cout()<<red<<bold<<"Bracketing interval found with "<< nfval
              <<" function evaluations." << endl;
    if (bracket_output) {
      comm->cout()<<"[ xa, xb, xc ] = [ "<<sci(ax)<<", "<<sci(bx)<<", "
                  <<sci(cx)<<"]"<<endl;
      comm->cout()<<"[ fa, fb, fc ] = [ "<<sci(fa)<<", "<<sci(fb)<<", "
                  <<sci(fc)<<"]"<<endl;
    } else {
      comm->cout()<<"[ "<<sci(ax)<<" "<<sci(bx)<<" "<<sci(cx)<<"]"<<endl;
    }
    comm->cout()<<def;

    // Run DGM Brent's
    nfval += static_cast<int>( lineSearch.brents_fmin(ax,bx,cx,fa,fb,fc,
                               dgm_brents_tol_alpha_, niter_) );
    
    alpha = bx;
    fval = fb;
    ls_neval += nfval;

    comm->cout()<<green<<bold;
    comm->cout()<<"Best step size found with "<< nfval 
                <<" function evaluations.\n"<<"Alpha = "<< sci(alpha)
                <<", Total_J = "<< sci(fval) <<endl;
    comm->cout()<<def;

    ROL::LineSearch<Real>::setNextInitialAlpha(alpha); 
  }

}; // class LineSearch

} // namespace ROLinterface

} // namespace DGM

#endif
