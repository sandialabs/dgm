#ifndef DGM_TIKHONOV_HPP
#define DGM_TIKHONOV_HPP

/** \file   Tikhonov.hpp
 *  \brief  Tikhonov regularization
 *  \author S. Scott Collis
 *  \author Greg von Winckel
 */

// DGM includes
#include "RegularizationElement.hpp"

namespace DGM {

/**
 *  \class DGM::Tikhonov
 *  \brief Tikhonov regularization of a DGM::vField
 *
 *  \f[ J[u] = \mu \sum\limits_k \int\limits_{\Omega_k}
 *             |u|^2 \, d\Omega \f]
 *
 *  The gradient is determined by taking variations
 *
 *  \f[ (v,\nabla J[u]) = 2 \mu \sum\limits_k\int\limits_{\Omega_k}
 *                        v \cdot u \, d\Omega \f]
 */
class Tikhonov : public RegularizationElement {

  const DGM::Comm::Ptr comm;    ///< Communicator for this domain
  const int verb;               ///< verbosity level
  dVector mu;                   ///< scalings for each component
  dVector wk1;                  ///< local workspace

public:

  /// Constructor (scalar mu)
  explicit Tikhonov(const vField &S, const Scalar mu_,
                    const DGM::Comm::Ptr comm_ = DGM::Comm::World )
  : comm(comm_), verb(comm_->verbosity()), mu(S.size(),mu_)
  {
    if (verb) comm->cout() << "Tikhonov::Tikhonov(vField&,Scalar)" << endl;
    assert(mu.size()==S.size());
    wk1.resize(max(S.Lmax(),S.Qmax()));
  }

  /// Constructor (vector mu)
  explicit Tikhonov(const vField &S, const dVector &mu_,
                    const DGM::Comm::Ptr comm_ = DGM::Comm::World )
  : comm(comm_), verb(comm_->verbosity()), mu(mu_)
  {
    if (verb) comm->cout() << "Tikhonov::Tikhonov(vField&,dVector&)"<<endl;
    assert(mu.size()==S.size());
    wk1.resize(max(S.Lmax(),S.Qmax()));
  }

  // JSON Constructor
  explicit Tikhonov(const vField &S, const Json::Value &json,
                    const DGM::Comm::Ptr comm_ = DGM::Comm::World)
  : comm(comm_), verb(comm_->verbosity())
  {
    if (verb) comm->cout() << "Tikhonov::Tikhonov(vField&,Json::Value&)"<<endl;
    // allocate local workspace
    wk1.resize(max(S.Lmax(),S.Qmax()));
    // The block must contain a key "mu" with corresponding value of 
    // array type and the array must have the correct number of elements
    mu.resize(S.size());
    if(json.isMember("mu")) {
      Json::Value muval = json.get("mu",0);
      if(muval.isArray()) {
        Ordinal n = S.size();
        if(n == static_cast<Ordinal>(muval.size())) {
          // Copy JSON values into mu
          for(Ordinal i=0; i<n; ++i) {
            mu[i] = muval[i].asDouble();
          }
        } else { // JSON mu has incompatible size
          throw DGM::exception("Tikhonov: Json mu must have same "
                               "size as vField");
        }
      } else { // JSON mu is not an array
        throw DGM::exception("Tikhonov: Json mu must be an array"); 
      }
    } else { // Backward compatibility if mu is not given - set to all ones
      mu.Set(one);
    }

    readMaskElements(json);
    isMaskEmpty = mask.empty();

  }

  /// Destructor
  virtual ~Tikhonov() {

#ifdef TEST_REGULARIZATION_MASK
    ofstream maskFile;
    maskFile.open("tikhonov.mask");

    for(unsigned i=0;i<mask.size();++i) {
      maskFile  << mask[i] << std::endl;  
    }

    maskFile.close();
#endif

  }

  /// \name Provide the DTK::Regularization interface
  //@{
  virtual Scalar operator()(const vField &x) const {
    dVector result(x.size());
    return operator()(x,result);
  }

  /// Evaluate the regularization term
  virtual Scalar operator()(const vField &x, dVector &result) const {
    vField &xl = const_cast<vField&>(x);
    return const_cast<Tikhonov*>(this)->evaluate(xl,result);
  }

  /// Compute the gradient
  virtual void grad(const vField &x, vField &g) const {
    vField &xl = const_cast<vField&>(x);
    const_cast<Tikhonov*>(this)->gradient(xl,g);
  }

  /// Compute the Hessian-vector product
  virtual void hessvec(const vField &x, const vField &dx, vField &H_dx) const {
    DGM_UNDEFINED;
  }
  //@}

private:

  /// Evaluate the contributions to the Tikhonov term
  /** Compute the following using only interior information
   *  \f$ J[u] = \mu \sum\limits_k
   *             \int\limits_{\Omega_k} |u|^2 \, d\Omega_k \f$
   */
  Scalar evaluate(vField &Uf, dVector &result) {
    if (verb) comm->cout() << "Tikhonov::evaluate() for vField = "
                           << Uf.get_name() << endl;
    result.resize(Uf.size());
    result = zero;
    for (Ordinal n=0; n<Uf.size(); ++n) {
      for (Ordinal e=0; e<Uf[n]->ne; ++e) {

        // Skip this element if it appears in the mask 
        if(inMask(e)) {
           break;   
        } 

        Element *U = Uf[n]->el[e];
        const Ordinal qtot = U->qtot;
        dVector integrand(wk1,qtot);
        integrand = U->u;
        dvmul(U->u,integrand);
        result[n] += mu[n] * U->integrate(integrand);
      }
    }
    return result.Sum();
  }

  /// Evaluate the contribution to the gradient
  /** \param[in]     Uf - Vector field to apply operator
   *  \param[in,out] Rf - Result vector field
   *
   *  \f[ (v,\nabla J[u]) =
   *      2 \mu \sum\limits_k \int\limits_{\Gamma_k} v \cdot u\,d\Gamma \f]
   */
  void gradient(vField &Uf, vField &Rf) {
    if (verb) comm->cout() << "Tikhonov::gradient() for vField = "
                           << Uf.get_name() << endl;
    for (Ordinal n=0; n<Uf.size(); ++n) {
      for (Ordinal e=0; e<Uf[n]->ne; ++e) {

        // Skip this element if it appears in the mask 
        if(inMask(e)) {
           break;   
        } 

        Element *const U = Uf[n]->el[e];
        Element *const R = Rf[n]->el[e];
        daxpy(two*mu[n],U->u,R->u);
      }
    }
  }
         
};

} // namespace DGM

#endif // DGM_TIKHONOV_HPP 
