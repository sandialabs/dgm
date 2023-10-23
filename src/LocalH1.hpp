#ifndef DGM_LOCAL_H1_HPP
#define DGM_LOCAL_H1_HPP

/** \file   LocalH1.hpp
 *  \brief  DG approximation of the Local H1 Seminorm penalty
 *  \author S. Scott Collis and Greg von Winckel
*/   

// DGM includes
#include "RegularizationElement.hpp"

namespace DGM {

/**
 *  \class DGM::LocalH1
 *  \brief Evaluate the broken H1 semi-norm and its gradient for multiple
 *         component fields
 *
 *  The H1 semi-norm for a given component u is
 *
 *  \f[ J[u] = \mu \sum\limits_k \int\limits_{\Omega_k}
 *             |\nabla u|^2 \,d\Omega \f]
 *
 *  The gradient is determined by taking variations
 *
 *  \f[ (v,\nabla J[u]) = \frac{d}{d\epsilon} J[u+\epsilon v]
 *                        \big|_{\epsilon=0} \f]
 *  \f[ (v,\nabla J[u]) = \mu \sum\limits_k\int\limits_{\Omega_k}
 *                        \lim_{\epsilon\rightarrow 0} \frac{d}{d\epsilon}  
 *                        |\nabla u+\epsilon\nabla v|^2\,d\Omega \f]
 *  \f[ (v,\nabla J[u]) = 2 \mu \sum\limits_k\int\limits_{\Omega_k}
 *                        \nabla v\cdot \nabla u\,d\Omega\f]
 *
 *  Integrating by parts
 *
 *  \f[ (v,\nabla J[u]) = 2 \mu \sum\limits_k
 *     \int\limits_{\Gamma_k} v \hat n\cdot\nabla u\,d\Gamma -
 *     \int\limits_{\Omega_k} v \Delta u\,d\Omega \f]
 */
class LocalH1 : public RegularizationElement {

  const DGM::Comm::Ptr comm;    ///< Communicator for this domain

  const int verb;               ///< verbosity level

  dVector mu;                   ///< scalings for each component

  dVector wk1;                  ///< local workspace
  dVector wk2;                  ///< local workspace
  dVector wk3;                  ///< local workspace
  dVector wk4;                  ///< local workspace

  vField Sf;                    ///< vector Field for scratch computation

public:

  /// Constructor
  LocalH1(vField &S, const dVector &mu_,
                  const DGM::Comm::Ptr comm_ = DGM::Comm::World )
  : comm(comm_), verb(comm_->verbosity()), mu(mu_), Sf(comm_)
  {
    if (verb) comm->cout() << "LocalH1::LocalH1(...)" << endl;

    // set the local scratch space
    Sf = S;

    // allocate local workspace
    wk1.resize(max(S.Lmax(),S.Qmax()));
    wk2.resize(max(S.Lmax(),S.Qmax()));
    wk3.resize(max(S.Lmax(),S.Qmax()));
    wk4.resize(max(S.Lmax(),S.Qmax()));
  }

   /// JSON Constructor
  LocalH1(vField &S, const Json::Value& json,
                     const DGM::Comm::Ptr comm_ = DGM::Comm::World )
  : comm(comm_), verb(comm_->verbosity()), Sf(comm_)
  {
    if (verb) comm->cout() << "LocalH1::LocalH1(...)" << endl;

    // set the local scratch space
    Sf = S;

    // allocate local workspace
    wk1.resize(max(S.Lmax(),S.Qmax()));
    wk2.resize(max(S.Lmax(),S.Qmax()));
    wk3.resize(max(S.Lmax(),S.Qmax()));
    wk4.resize(max(S.Lmax(),S.Qmax()));

   // The block must contain a key "mu" with corresponding value of 
   // array type and the array must have the correct number of elements

    mu.resize(S.size());
    if(json.isMember("mu")) {
      Json::Value muval = json.get("mu",0);
      if(muval.isArray()) {
        Ordinal n = S.size();
        if(n == static_cast<Ordinal>(muval.size())) {
          for(Ordinal i=0; i<n; ++i) {
            mu[i] = muval[i].asDouble();
          }
        } else {
          throw DGM::exception("LocalH1: mu must have same size as vField");
        }
      } else {
        throw DGM::exception("LocalH1: Json mu must be an array"); 
      }
    } else { // Backward compatibility if mu is not given - set to all ones
      mu.Set(one);
    }

    readMaskElements(json);
    isMaskEmpty = mask.empty();

  }

  /// Destructor
  virtual ~LocalH1() {

#ifdef TEST_REGULARIZATION_MASK
    ofstream maskFile;
    maskFile.open("localh1.mask");

    for(unsigned i=0;i<mask.size();++i) {
      maskFile  << mask[i] << std::endl;  
    }

    maskFile.close();
#endif

  }

  /// set the scratch vector field used for generalized lift
  void setScratchSpace(vField &S) { Sf = S; }

  /// \name Provide the DTK::Regularization interface
  //@{
  virtual Scalar operator()(const vField &x) const {
    dVector result(x.size());
    return operator()(x,result);
  }

  /// Evaluate the regularization term
  virtual Scalar operator()(const vField &x, dVector &result) const {
    vField &xl = const_cast<vField&>(x);
    return const_cast<LocalH1*>(this)->evaluate(xl,result);
  }

  /// Compute the gradient
  virtual void grad(const vField &x, vField &g) const {
    assert (x.size() == Sf.size());
    vField &xl = const_cast<vField&>(x);
    vField &fl = const_cast<vField&>(Sf);
    // it would be nice to remove the need for the scratch field but this
    // requires the addition of a new, simple lift operator to the Element
    const_cast<LocalH1*>(this)->gradient(xl,fl,g);
  }

  /// Compute the Hessian-vector product
  virtual void hessvec(const vField &x, const vField &dx, vField &H_dx) const {
    DGM_UNDEFINED;
  }
  //@}

private:

  /// Evaluate the contributions to the local H1 seminorm term
  /** Compute the following using only interior information
   *  \f$ J[u] = \mu \sum\limits_k
   *             \int\limits_{\Omega_k} |grad(u)|^2\,d\Omega_k\f$
   */
  Scalar evaluate(vField &Uf, dVector &result) {

    if (verb) comm->cout() << "LocalH1::evaluate() for vField = "
                           << Uf.get_name() << endl;

    // initialize the result vector
    result.resize(Uf.size());
    result = zero;

    // Get number of spatial dimensions
    const Ordinal nsd = Uf[0]->nsd();

    // Loop over vector field components
    for (Ordinal n=0; n<Uf.size(); ++n) {

      // Loop over elements
      for (Ordinal e=0; e<Uf[n]->ne; ++e) {

        // Skip this element if it appears in the mask 
        if(inMask(e)) {
           break;   
        } 

        // Pointer to current element of current field component
        Element *U = Uf[n]->el[e];

        const Ordinal qtot = U->qtot;

        dVector integrand(wk4,qtot);

        switch(nsd) {

        case 1: // One spatial dimension
        {
          dVector ux(wk1,qtot);    // Place to store ux on quad points

          U->gradient(U->u,ux);    // Differentiate u store in ux

          integrand = ux;
          dvmul(ux,integrand);

          break;
        }

        case 2: // Two spatial dimensions
        {
          dVector ux(wk1,qtot);
          dVector uy(wk2,qtot);

          // Differentiate u w.r.t x,y and store in ux, uy
          U->gradient(U->u,ux,uy);

          dvmul(ux,ux,integrand);
          dvmul(uy,uy);
          daxpy(one,uy,integrand);  // integrand = u_x^2 + u_y^2

          break;
        }

        case 3: // Three spatial dimensions
        {
          dVector ux(wk1,qtot);
          dVector uy(wk2,qtot);
          dVector uz(wk3,qtot);
          U->gradient(U->u,ux,uy,uz);

          dvmul(ux,ux,integrand);
          dvmul(uy,uy);
          daxpy(one,uy,integrand);  // integrand = u_x^2 + u_y^2
          dvmul(uz,uz);
          daxpy(one,uz,integrand);  // integrand += u_z^2

          break;
        }
        default:
        {
          throw DGM::exception("Unsupported value of nsd = "+asString(nsd));
          break;
        }

        }  // End switch statement

        // Add integral over this element for field component n to J
        result[n] += mu[n] * U->integrate(integrand);

      }  // End element loop

    }  // End field component loop

    return result.Sum();

  } // End evaluate

  /// Evaluate the contribution to the gradient for local H1 semi-norm term
  /** \param[in]     Uf - Vector field to apply operator
   *  \param[in]     Ff - Scratch vector field
   *  \param[in,out] Rf - Result vector field
   *
   *  \f[ (v,\nabla J[u]) = 2 \mu \sum\limits_k
   *        \int\limits_{\Gamma_k} v \hat n\cdot\nabla u\,d\Gamma -
   *        \int\limits_{\Omega_k} v \Delta u\,d\Omega \f]
   *
   */
  void gradient(vField &Uf, vField &Ff, vField &Rf) {

    if (verb) comm->cout() << "LocalH1::gradient() for vField = "
        << Uf.get_name() << endl;

    // Get number of spatial dimensions
    const Ordinal nsd = Uf[0]->nsd();

    // Fill the sides for each Field using the data on the Elements
    Uf.fill_sides(zero);

    // Fill the sides that are domain boundary sides
    Uf.fill_bc_sides(zero);

    // Share sides in parallel
    Uf.share_sides();

    // Loop over vector field components
    for (Ordinal n=0; n<Uf.size(); ++n) {

      // Loop over elements
      for (Ordinal e=0; e<Uf[n]->ne; ++e) {

        // Skip this element if it appears in the mask 
        if(inMask(e)) {
           break;   
        } 

        // Pointer to current element of current field component
        Element *U = Uf[n]->el[e];

        // Element field storage
        Element *F = Ff[n]->el[e];

        // Total number of quadrature points
        const Ordinal qtot = U->qtot;

        switch(nsd) {

        case 1: // One spatial dimension
        {
          dVector ux(wk1,qtot);       // Place to store ux on quad points

          U->gradient(U->u,ux);       // Differentiate u store in ux

          F->fill_sides(ux);          // Store gradient in sides of F

          U->gradient(ux,ux,'x');     // Second derivative, store in ux

          scale(-one,ux);

          U->lift(F,ux,'x');          // Lift into ux (additive)

          // may need to do a U->project(ux) here

          F->u = ux;

          break;
        }

        case 2: // Two spatial dimensions
        {
          dVector ux(wk1,qtot);
          dVector uy(wk2,qtot);

          U->gradient(U->u,ux,uy);     // Differentiate u store in ux, uy

          F->fill_sides(ux,uy);        // Store normal gradient in sides of F

          U->gradient(ux,ux,'x');      // Compute second derivative, store in ux
          U->gradient(uy,uy,'y');      // Compute second derivative, store in uy

          scale(-one,ux);
          scale(-one,uy);

          F->u = ux;
          dvadd(uy,F->u);
          U->lift(F,F->u);              // Lift the normal gradient

          // may need to do a U->project(F->u) here;

          break;
        }

        case 3: // Three spatial dimensions
        {
          dVector ux(wk1,qtot);
          dVector uy(wk2,qtot);
          dVector uz(wk3,qtot);

          U->gradient(U->u,ux,uy,uz);  // Differentiate u store in ux, uy, uz

          F->fill_sides(ux,uy,uz);     // Store gradient in sides of F

          U->gradient(ux,ux,'x');      // Compute second derivative, store in ux
          U->gradient(uy,uy,'y');      // Compute second derivative, store in uy
          U->gradient(uz,uz,'z');      // Compute second derivative, store in uz

          scale(-one,ux);
          scale(-one,uy);
          scale(-one,uz);

          F->u = ux;
          dvadd(uy,F->u);
          dvadd(uz,F->u);
          U->lift(F,F->u);

          // may need to do a U->project(F->u) here

          break;
        }
        default:
        {
          throw DGM::exception("Unsupported value of nsd = "+asString(nsd));
          break;
        }
        } // End switch statement

        scale(two*mu[n],F->u);

      }  // End element loop

    }  // End field component loop

    add( Ff, Rf );  // Add contribution to result

  }  // End gradient function
         
}; // class LocalH1     

} // namespace DGM

#endif  // DGM_LOCAL_H1_SEMINORM_HPP
