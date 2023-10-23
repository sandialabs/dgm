#ifndef DGM_REGULARIZATION_HPP
#define DGM_REGULARIZATION_HPP

/** \file Regularization.hpp
    \brief Regularization for parameter estimation
    \author Joseph Young
    \author Scott Collis
*/

// system includes
#include <memory>

// DGM includes
#include "Control.hpp"
using DGM::Control;

namespace DGM {

/// Namespace for all DGM regularization stuff
/**
 * This approach to regularization is not implemented at the correct
 * level and as such is of limited utility.  It tried to implement
 * regularization on the DGM::Control which is really a container of
 * DGM::Ctrl.  The implementation of regularization really needs to occur,
 * in general, at the DGM::Ctrl level although one could have basic
 * implementations that could be used in practice.  I've added this comment
 * to help explain this and this file is deprecated and will be removed
 * at some future date.
*/
namespace Regularization {

/// The base class required for regularization.  
/** This is really no different than what's required for optimizing a 
    scalar-valued function. */
template <typename Real>
struct Base {
  typedef DGM::Control::Ptr Vector; 

  /// <- f(x)
  virtual Real operator() (const Vector& x) const = 0;

  /// g = grad f(x)
  virtual void grad(const Vector& x,Vector& g) const = 0;

  /// H_dx = hess f(x) dx
  virtual void hessvec(const Vector& x,const Vector& dx,Vector& H_dx) const = 0;

  /// Allow a derived class to deallocate memory
  virtual ~Base() {}
};
 
/// Different types of regularization
struct Type {
  enum t {
    None,                 ///< No regularization
    Tikhonov,             ///< Tikhonov regularization around zero
    TikhonovWithBase,     ///< Tikhonov regularization around a base point
    Lasso,                ///< LASSO regularization around zero 
    LassoWithBase,        ///< LASSO regularization around a base point 
    TotalVariation,       ///< Total variation regularization 
  };

  /// Converts the problem class to a string
  static std::string to_string(t type) {
    switch(type) {
    case None:
      return "None";
      break;
    case Tikhonov:
      return "Tikhonov";
      break;
    case TikhonovWithBase:
      return "TikhonovWithBase";
      break;
    case Lasso:
      return "Lasso";
      break;
    case LassoWithBase:
      return "LassoWithBase";
      break;
    case TotalVariation:
      return "TotalVariation";
      break;
    default:
      throw;
      break;
    }
    return "Error";
  }

  /// Converts a string to a problem class
  static t from_string(std::string type){
    if(type=="None")
      return None;
    else if(type=="Tikhonov")
      return Tikhonov;
    else if(type=="TikhonovWithBase")
      return TikhonovWithBase;
    else if(type=="Lasso")
      return Lasso;
    else if(type=="LassoWithBase")
      return LassoWithBase;
    else if(type=="TotalVariation")
      return TotalVariation;
    else
      throw;
  }

  /// Checks whether or not a string is valid
  struct is_valid : public std::unary_function<std::string, bool> {
    bool operator () (const std::string& name) const {
      if( name=="None" ||
          name=="Tikhonov" ||
          name=="TikhonovWithBase" ||
          name=="Lasso" ||
          name=="LassoWithBase" ||
          name=="TotalVariation"
      )
        return true;
      else
        return false;
    }
  };

};

/// No regularization at all
template <typename Real>
struct None : public Base <Real> {
public:
  typedef DGM::Control::Ptr Vector; 

  /// Nothing required for construction
  None() {} 

  /// <- 0.
  Real operator () (const Vector& x) const {
    return Real(0.);
  }

  /// g <- 0
  void grad(const Vector& x,Vector& g) const {
    DGM::scale(Real(0.),g);
  }

  /// H_dx <- 0
  void hessvec(const Vector& x,const Vector& dx,Vector& H_dx) const {
    DGM::scale(Real(0.),H_dx);
  }
};

/// A simple specification for a linear operator.
template <typename Real>
struct Operator {
  typedef DGM::Control::Ptr Vector; 

  // Basic application
  virtual void operator () (const Vector& x,Vector &y) const = 0;

  // Allow a derived class to deallocate memory 
  virtual ~Operator() {}
};

/// Identity Operator. 
template <typename Real>
struct Identity : public Operator <Real>{
  typedef DGM::Control::Ptr Vector; 

  // y <- x 
  void operator () (const Vector& x,Vector &y) const {
    DGM::copy(x,y);
  }
};

/// Implements the regularization
/** r(x) = <A (x-xhat),x-xhat>
    r'(x)dx = 2 <A (x-xhat),dx> 
    grad r(x) = 2 A (x-xhat) 
    hess r(x) dx = 2 A dx

    where A is an operator provided by the user and x_hat is the point around
    which we want to regularize. */
template <typename Real>
struct OperatorNormSquared : public Base<Real> {
public:
  typedef DGM::Control::Ptr Vector; 

private:
  /// Point that we regularize around
  Vector xhat;

  /// Operator for the operator norm
  std::unique_ptr<Operator <Real> > A;

public:
  /// On construction, we take a point and an operator
  OperatorNormSquared(Operator <Real>* A_,const Vector& xhat_) {
    A.reset(A_);
    xhat.reset(xhat_->clone());
  }

  /// <- <A (x-xhat),x-xhat>
  Real operator () (const Vector& x) const {
    // x_m_xhat = x-xhat
    Vector x_m_xhat;
    x_m_xhat.reset(x->clone());
    DGM::axpy(Real(-1.),xhat,x_m_xhat);

    // A_xmxhat = A (x-xhat);
    Vector A_xmxhat;
    A_xmxhat.reset(x->clone());
    (*A)(x_m_xhat,A_xmxhat);

    // <- <A (x-xhat),x-xhat>
    return A_xmxhat->inner_product(x_m_xhat.get()); 
  }

  /// g <- 2 A (x-xhat)
  /** \note This is only true if A is self-adjoint. */
  void grad(const Vector& x,Vector& g) const {
    // x_m_xhat = x-xhat
    Vector x_m_xhat;
    x_m_xhat.reset(x->clone());
    DGM::axpy(Real(-1.),xhat,x_m_xhat);

    // g = A (x-xhat)
    (*A)(x_m_xhat,g);

    // g = 2 A (x-xhat); 
    DGM::scale(Real(2.),g);
  }

  /// <- 2 <A (x-xhat),dx>
  Real p(const Vector& x,const Vector& dx) const {
    // x_m_xhat = x-xhat
    Vector x_m_xhat;
    x_m_xhat.reset(x->clone());
    DGM::axpy(Real(-1.),xhat,x_m_xhat);

    // A_xmxhat = A (x-xhat);
    Vector A_xmxhat;
    A_xmxhat.reset(x->clone());
    (*A)(x_m_xhat,A_xmxhat);

    // <- 2 <A (x-xhat),dx>
    return Real(2.)*A_xmxhat->inner_product(dx.get()); 
  }

  /// H_dx <- 2 A dx
  void hessvec(const Vector& x,const Vector& dx,Vector& H_dx) const {
    // H_dx = A dx 
    (*A)(dx,H_dx);

    // H_dx = 2 A dx
    DGM::scale(Real(2.),H_dx);
  }
};

/// Implements Tikhonov regularization,
/** r(x) = <x-xhat,x-xhat>
    grad r(x) = 2 (x-xhat)
    hess r(x) dx = 2 dx
    where x_hat is the point around which we want to regularize. */
template <typename Real>
struct Tikhonov : public OperatorNormSquared<Real> {
  typedef DGM::Control::Ptr Vector; 

  // On construction, we take a point to regularize around
  Tikhonov(const Vector& xhat_)
    : OperatorNormSquared <Real> (new Identity <Real>(),xhat_) { }
};

/// Implements the regularization
/** rtild(x) = sqrt( gamma + r(x) )
    grad rtild(x) = .5/sqrt( gamma + r(x)) grad r(x)
    hess rtild(x) dx = -.25/(gamma + r(x))^(3/2) r'(x)dx grad r(x)
                     + .5/sqrt( gamma + r(x)) hessvec r(x) dx
    where r is the OperatorNormSquared regularization from above.  Essentially,
    we're getting an operator norm rather than an operator norm squared
    regularization where gamma forces differentiability and determines the
    roundness of the regularization.   */
template <typename Real>
struct OperatorNorm : public Base<Real> {
public:
  typedef DGM::Control::Ptr Vector; 

private:
  /// Roundness of the regularization
  const Real gamma;

  /// Operator norm squared regularization
  std::unique_ptr<OperatorNormSquared <Real> > r;

public:
  /// On construction, we take a point and an operator
  OperatorNorm(Operator <Real>* A_,const Vector& xhat_,const Real gamma_)
    : gamma(gamma_) 
  {
    r.reset(new OperatorNormSquared <Real> (A_,xhat_));
  }

  /// <- sqrt( gamma + r(x) )
  Real operator () (const Vector& x) const {
    return sqrt(gamma+(*r)(x));
  }

  /// g <- .5/sqrt( gamma + r(x)) grad r(x)
  void grad(const Vector& x,Vector& g) const {
    // g <- grad r(x)
    r->grad(x,g);

    // g <- .5/sqrt( gamma + r(x)) grad r(x) 
    DGM::scale(Real(.5)/sqrt(gamma+(*r)(x)),g);
  }

  /// H_dx <- -.25/(gamma + r(x))^(3/2) r'(x)dx grad r(x)
  ///         + .5/sqrt( gamma + r(x)) hessvec r(x) dx
  void hessvec(const Vector& x,const Vector& dx,Vector& H_dx) const {
    // rnd_nrm <- sqrt(gamma + r(x))
    Real rnd_nrm = sqrt(gamma+(*r)(x));

    // H_dx <- hessvec r(x) dx 
    r->hessvec(x,dx,H_dx);

    // H_dx <- .5/sqrt( gamma + r(x)) hessvec r(x) dx
    DGM::scale(.5/rnd_nrm,H_dx);

    // g <- grad r(x)
    Vector g;
    g.reset(x->clone());
    r->grad(x,g);

    // g <- -.25/(gamma + r(x))^(3/2) r'(x)dx grad r(x)
    /// H_dx <-  -.25/(gamma + r(x))^(3/2) r'(x)dx grad r(x)
    ///          + .5/sqrt( gamma + r(x)) hessvec r(x) dx
    DGM::axpy(Real(-0.25)/(rnd_nrm*rnd_nrm*rnd_nrm)*r->p(x,dx),g,H_dx);
  }
};

/// Implements the LASSO regularization 
/** r(x) = sqrt(gamma+||x-xhat||^2) ~= ||x-xhat||
    where x_hat is the point around which we want to regularize.  Note,
    this is a rounded version of Tikhonov regularization. */
template <typename Real>
struct Lasso : public OperatorNorm <Real> {
  typedef DGM::Control::Ptr Vector; 

  // On construction, we take a point to regularize around and the roundness
  // of the constraint
  Lasso(const Vector& xhat_,const Real gamma_)
    : OperatorNorm <Real> (new Identity <Real>(),xhat_,gamma_) { }
};

/// Diffusion operator.
/** \note These cannot be implemented at the DGM::Control level, but instead
 *  need to be at the DGM::Ctrl level.  For now, make undefined as the prior
 *  implementation was wrong.
*/
template <typename Real>
struct Diffusion: public Operator <Real>{
  typedef DGM::Control::Ptr Vector; 
  // y <- x 
  void operator () (const Vector& x,Vector &y) const {
    DGM_UNDEFINED;
  }
  /// Compute (stabilized) Bassi and Rebay diffusive term
  void diffusion(vField& Uf,vField& Ff,vField& Rf) const {
    DGM_UNDEFINED;
  }
};

/// Implements TV regularization 
/** r(x) = sqrt(gamma+||grad(x)||^2) ~= ||grad(x)||. */
template <typename Real>
struct TotalVariation : public OperatorNorm<Real> {
  typedef DGM::Control::Ptr Vector; 

  //// On construction, we take a point to regularize around and the roundness
  //// of the constraint
  TotalVariation(const Vector& xhat_,const Real gamma_)
    : OperatorNorm <Real> (new Diffusion<Real>(),xhat_,gamma_) { }
};

} // namespace Regularization

} // namespace DGM

#endif  // DGM_REGULARIZATION_HPP
