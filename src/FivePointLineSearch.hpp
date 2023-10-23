/** 
 * \file FivePointLineSearch.hpp
 * \brief Provides interface to ROL::LineSearch implementing a
 *        five-point line search.
 */
#ifndef DGM_FIVE_POINT_LINESEARCH_HPP
#define DGM_FIVE_POINT_LINESEARCH_HPP

/// RoL includes
#include "ROL_LineSearch.hpp"

namespace DGM {

/// Provides the interface to compute optimization steps with line search.
template <class Real>
class FivePointLineSearch : public ROL::LineSearch<Real> {
private:

  Teuchos::RCP<ROL::Vector<Real> > xnew_;

  // Information for five point linesearch
  Real alpha0_;
  Real alphaMax_;
  bool normalize_step_;
  bool reuse_linesearch_;

public:

  virtual ~FivePointLineSearch() {}

  FivePointLineSearch( Teuchos::ParameterList &parlist ) 
    : ROL::LineSearch<Real>(parlist) {
    // Five Point Line Search Information
    alphaMax_         = parlist.get("Maximum Linesearch Size", 1.e10);
    normalize_step_   = parlist.get("Normalize Step", false);
    reuse_linesearch_ = parlist.get("Reuse Previous Linesearch Parameter", false);
    alpha0_           = parlist.get( "Initial Linesearch Parameter", 1.0 );
  }

  /** \brief Initialize five point line search.
*/
  void initialize(const ROL::Vector<Real> &x, const ROL::Vector<Real> &s,
                  const ROL::Vector<Real> &g, ROL::Objective<Real> &obj,
                  ROL::BoundConstraint<Real> &con) {
    ROL::LineSearch<Real>::initialize(x,s,g,obj,con);
    xnew_ = x.clone();
  }

  /** \brief Approximately solve the line search subproblem.
*/
  void run(Real &alpha, Real &fval, int &ls_neval, int &ls_ngrad,
           const Real &gs, const ROL::Vector<Real> &s,
           const ROL::Vector<Real> &x, ROL::Objective<Real> &obj,
           ROL::BoundConstraint<Real> &con) {
    Real ftol = std::sqrt(ROL::ROL_EPSILON<Real>());  // Function eval tolerance
    // Perform line search
    ls_neval = 0;
    ls_ngrad = 0;
    if ( !reuse_linesearch_ ) {
      ROL::LineSearch<Real>::
      getInitialAlpha(ls_neval,ls_ngrad,fval,gs,x,s,obj,con);
    }
    // Initialize
    bool declining = false;         // Was linesearch declining?
    Real stepinc  = alpha0_/4.0;    // Linesearch increment
    if ( normalize_step_ ) {
      stepinc /= s.norm();
    }
    Real fcurrent = fval;      // Current step's function value storage
    Real fprev    = fval;      // Previous step's function value storage
    // Perform First Linesearch Step
    int istep = 1;
    while (!declining) {
      // Compute x + istep stepinc s
      ROL::LineSearch<Real>::updateIterate(*xnew_,x,s,istep*stepinc,con);
      // Compute f(x + istep stepinc s)
      obj.update(*xnew_);
      fcurrent = obj.value(*xnew_,ftol);
      ls_neval++;

      // Check to see if f(x + stepinc s) < f(x)
      if ( fcurrent < fprev ) {
        declining = true;
      }  
      else {
        alpha0_ *= 0.10;
        stepinc  = alpha0_/4.0;    // Linesearch increment
        if ( normalize_step_ ) {
          stepinc /= s.norm();
        }
        DGM::Comm::World->cout() 
          << "In five point line search the first step was increasing. " 
          << "Decreasing alpha0 to " << alpha0_ << endl;
      }
    }
    // Perform Linesearch
    while ( declining and (istep<4)) {
      istep++;
      fprev = fcurrent;
      // Compute x + istep stepinc s
      ROL::LineSearch<Real>::updateIterate(*xnew_,x,s,istep*stepinc,con);
      // Compute f(x + istep stepinc s)
      obj.update(*xnew_);
      fcurrent = obj.value(*xnew_,ftol);
      ls_neval++;

      // Check to see if f(x + stepinc s) < f(x)
      if ( fcurrent > fprev ) {
        declining = false;
      }  
    }
    // Set final searchSize
    if (declining) {
      alpha    = istep*stepinc;
      alpha0_ *= 0.5*istep;
      alpha0_  = std::min(alpha0_, alphaMax_);
      DGM::Comm::World->cout() << 
        "In five point line search the percent decline in objective was " << 
        100.0*abs(fcurrent-fval)/fval << endl;
      fval = fcurrent;
    }
    else {
      alpha    = (istep-1)*stepinc;
      alpha0_ *= 0.5*(istep-1);
      alpha0_  = std::min(alpha0_, alphaMax_);
      DGM::Comm::World->cout() << 
        "In five point line search the percent decline in objective was " << 
        100.0*abs(fprev-fval)/fval << endl;
      fval = fprev;
    }
  }
}; // class FivePointLineSearch

} // namespace DGM

#endif
