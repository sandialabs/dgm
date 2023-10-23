#ifndef DGM_LOCAL_TV_HPP
#define DGM_LOCAL_TV_HPP

/** \file   LocalTV.hpp
 *  \brief  DG approximation of the (local) smoothed total variation operator
 *  \author Greg von Winckel
 *  \author Scott Collis
 */

// DGM includes
#include "RegularizationElement.hpp"

namespace DGM {

/// Local Total Variation Evaluation
/** Compute approximate Total Variation functional value and, if desired, the
 *  gradient \f$J(u)=\mu\int\sqrt{(\nabla u)^2+\gamma}\,\mathrm{d}\Omega\f$
 *
 *  The local, smoothed TV objective is
 *
 *  \f[ J[u] = \mu \sum\limits_k \int\limits_{\Omega_k}
 *             \sqrt{|\nabla u|^2+\gamma} \,d\Omega \f]
 *
 *  The gradient is obtained by taking variations
 *
 *  \f[ (v,\nabla J[u]) = \mu\sum\limits_{k} (\nabla v\cdot \nabla u ) w(u) 
 *                        \, d\Omega \f]
 *
 *  where \f$ w(u) = (|\nabla u|^2 + \gamma)^{-1/2} \f$
 *
 *  Integrating by parts, we get
 *
 *  \f[ (v,\nabla J[u]) = \sum\limits_{k} \int\limits_{\Omega_k}
 *                      - v\nabla \cdot[w(u)\nabla u] \,d\Omega
 *                      + \int\limits_{\Gamma_k} v \hat n \cdot
 *                        [w(u)\nabla u]\,d\Gamma \f]
 *
 *   As with the LocalH1 regularization, the surface term must
 *   be lifted to the volume.
*/
class LocalTV : public RegularizationElement {

  const DGM::Comm::Ptr comm;    ///< Communicator for this domain

  const int verb;       ///< verbosity level

  dVector mu;           ///< constant "diffusivity"

  double gamma;         ///< broadening parameter in approx. of \f$|[[u]]|\f$

  dVector wk1;          ///< local workspace
  dVector wk2;          ///< local workspace
  dVector wk3;          ///< local workspace
  dVector wk4;          ///< local workspace
  dVector wk5;          ///< local workspace
  dVector wk6;          ///< local workspace
  dVector wk7;          ///< local workspace

  vField Sf;            ///< vector Field for scratch computation

  vector<Size> unmasked;

public:

  /// Constructor
  LocalTV(vField &S, const dVector &mu_, const double &gam_,
          const DGM::Comm::Ptr comm_ = DGM::Comm::World )
  : comm(comm_), verb(0), mu(mu_), gamma(gam_), Sf(comm_)
  {
    if (verb) comm->cout() << "LocalTV::LocalTV(...)"  << endl;

    // set the local scratch space
    Sf = S;

    // allocate local workspace
    wk1.resize(max(S.Lmax(),S.Qmax()));
    wk2.resize(max(S.Lmax(),S.Qmax()));
    wk3.resize(max(S.Lmax(),S.Qmax()));
    wk4.resize(max(S.Lmax(),S.Qmax()));
    wk5.resize(max(S.Lmax(),S.Qmax()));
    wk6.resize(max(S.Lmax(),S.Qmax()));
    wk7.resize(max(S.Lmax(),S.Qmax()));
  }

  /// JSON Constructor
  LocalTV(vField &S, const Json::Value& json,
          const DGM::Comm::Ptr comm_ = DGM::Comm::World ) 
  : comm(comm_), verb(0), Sf(comm_), unmasked(0)
  {
    if (verb) comm->cout() << "LocalTV::LocalTV(...)" << endl;

    // set the local scratch space
    Sf = S;

    // allocate local workspace
    wk1.resize(max(S.Lmax(),S.Qmax()));
    wk2.resize(max(S.Lmax(),S.Qmax()));
    wk3.resize(max(S.Lmax(),S.Qmax()));
    wk4.resize(max(S.Lmax(),S.Qmax()));
    wk5.resize(max(S.Lmax(),S.Qmax()));
    wk6.resize(max(S.Lmax(),S.Qmax()));
    wk7.resize(max(S.Lmax(),S.Qmax()));

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
          throw DGM::exception("LocalTV:  mu must have same size as vField");
        }
      } else {
        throw DGM::exception("LocalTV: Json mu must be an array"); 
      }
    } else { // Backward compatibility if mu is not given - set to all ones
      mu.Set(one);
    }
    if(json.isMember("gamma")) {
      Json::Value gammaval = json.get("gamma",0);
      gamma = gammaval.asDouble();
    } else {
      throw DGM::exception("LocalTV: Json gamma must be defined");  
    }

    // Check if there are elements to mask and store their indices   
    readMaskElements(json);
    isMaskEmpty = mask.empty(); 

  }

  /// Destructor
  virtual ~LocalTV() {

#ifdef TEST_REGULARIZATION_MASK
    ofstream maskFile;
    maskFile.open("localtv.mask");

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
    return const_cast<LocalTV*>(this)->evaluate(xl,result);
  }

  /// Compute the gradient
  virtual void grad(const vField &x, vField &g) const {
    assert (x.size() == Sf.size());
    vField &xl = const_cast<vField&>(x);
    vField &fl = const_cast<vField&>(Sf);
    // it would be nice to remove the need for the scratch field but this
    // requires the addition of a new, simple lift operator to the Element
    const_cast<LocalTV*>(this)->gradient(xl,fl,g);
  }

  /// Compute the Hessian-vector product
  virtual void hessvec(const vField &x, const vField &dx, vField &H_dx) const {
    DGM_UNDEFINED;
  }
  //@}

private:

  /// Evaluate the contributions to the smoothed local TV term
  /** \f$ J[u] = \mu \sum\limits_k \int\limits_{\Omega_k}
                   \sqrt{|grad(u)|^2+\gamma}\,d\Omega_k\f$ 
   */
  Scalar evaluate(vField &Uf, dVector &result) {

    if (verb) comm->cout() << "LocalTV::evaluate() for vField = "
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

        // Total number of quadrature points
        const Ordinal qtot = U->qtot;

        dVector integrand(wk4,qtot);

        switch(nsd) {

        case 1: // One spatial dimension
        {
          dVector ux(wk1,qtot);         // Place to store ux on quad points
          U->gradient(U->u,ux);         // Differentiate u store in ux
          dvmul(ux,ux,integrand);       // integrand = u_x^2
          break;
        }

        case 2: // Two spatial dimensions
        {
          dVector ux(wk1,qtot);
          dVector uy(wk2,qtot);
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
        } // End switch statement

        integrand += gamma; // Shift the vector by gamma

        integrand.Sqrt();   // Take square root

        // Add integral on this element for this field component to result
        result[n] += mu[n] * U->integrate(integrand);

      }  // End element loop
    }  // End field component loop

    return result.Sum();

  } // End cost function

  /// Evaluate the contribution to the gradient for Total Variation term
  void gradient(vField &Uf, vField &Ff, vField &Rf) {

    if (verb) comm->cout() << "LocalTV::gradient() for vField = "
                           << Uf.get_name() << endl;

    // Get number of spatial dimensions
    const Ordinal nsd = Uf[0]->nsd();

    // Fill the sides for each Field with zero
    Uf.fill_sides(zero);

    // Fill the sides that are domain boundary sides with zero
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

        // make a local workspace to hold intermediate results
        dVector w(wk7,qtot);

        switch(nsd) {

        case 1: // One spatial dimension
        {
          dVector ux(wk1,qtot);         // Place to store ux on quad points

          U->gradient(U->u,ux);         // Differentiate u store in ux

          dvmul(ux,ux,w);               // w = u_x^2
          w += gamma;                   // w = u_x^2+gamma
          w.Sqrt();                     // w = sqrt(u_x^2+gamma)
          w.Recip(one);                 // w = 1/sqrt(u_x^2+gamma)

          dvmul(w,ux);                  // Scale gradient by w

          F->fill_sides(ux);            // Store scaled gradient in sides of F

          dVector uxx(wk4,qtot);
          U->gradient(ux,uxx,'x');

          scale(-one,uxx);

          U->lift(F,uxx,'x');           // Lift scaled edge normal to interior

          F->u = uxx;

          break;
        }

        case 2: // Two spatial dimensions
        {
          dVector ux(wk1,qtot);
          dVector uy(wk2,qtot);
          dVector uy2(wk4,qtot);
          
          U->gradient(U->u,ux,uy);

          dvmul(ux,ux,w);              // w = u_x^2
          dvmul(uy,uy,uy2);
          daxpy(one,uy2,w);            // w = u_x^2+u_y^2
          w += gamma;                  // w = u_x^2+u_y^2+gamma
          w.Sqrt();                    // w = sqrt(u_x^2+u_y^2+gamma)
          w.Recip(one);                // w = 1/sqrt(u_x^2+u_y^2+gamma)

          dvmul(w,ux);                 // Scale gradient by w
          dvmul(w,uy);

          F->fill_sides(ux,uy);        // Store scaled gradient in sides of F

          dVector uxx(wk4,qtot);       // reuse workspace is okay
          dVector uyy(wk5,qtot);

          U->gradient(ux,uxx,'x');
          U->gradient(uy,uyy,'y');

          scale(-one,uxx);
          scale(-one,uyy);

          U->lift(F,uxx,'x');           // Lift scaled edge normal to interior
          U->lift(F,uyy,'y');

          F->u = uxx;
          dvadd(uyy,F->u);

          break;
        }

        case 3: // Three spatial dimensions
        {
          dVector ux(wk1,qtot);
          dVector uy(wk2,qtot);
          dVector uz(wk3,qtot);
          dVector uy2(wk4,qtot);
          dVector uz2(wk5,qtot);

          U->gradient(U->u,ux,uy,uz);

          dvmul(ux,ux,w);              // w = u_x^2
          dvmul(uy,uy,uy2);
          daxpy(one,uy2,w);            // w = u_x^2+u_y^2
          dvmul(uz,uz,uz2);
          daxpy(one,uz2,w);            // w = u_x^2+u_y^2+u_z^2

          w += gamma;                  // w = u_x^2+u_y^2+u_z^2+gamma
          w.Sqrt();                    // w = sqrt(u_x^2+u_y^2+u_z^2+gamma)
          w.Recip(one);                // w = 1/sqrt(u_x^2+u_y^2+u_z^2+gamma)

          dvmul(w,ux);                 // Scale gradient by w
          dvmul(w,uy);
          dvmul(w,uz);

          F->fill_sides(ux,uy,uz);     // Store scaled gradient in sides of F

          dVector uxx(wk4,qtot);       // reuse workspace is okay
          dVector uyy(wk5,qtot);       // reuse workspace is okay
          dVector uzz(wk6,qtot);

          U->gradient(ux,uxx,'x');
          U->gradient(uy,uyy,'y');
          U->gradient(uz,uzz,'z');

          scale(-one,uxx);
          scale(-one,uyy);
          scale(-one,uzz);

          U->lift(F,uxx,'x');           // Lift scaled edge normal to interior
          U->lift(F,uyy,'y');
          U->lift(F,uzz,'z');

          F->u = uxx;
          dvadd(uyy,F->u);
          dvadd(uzz,F->u);

          break;
        }
        default:
        {
          throw DGM::exception("Unsupported value of nsd = "+asString(nsd));
          break;
        }
        } // End switch statement

        scale(mu[n],F->u);

      }  // End element loop
    }  // End field component loop

    add( Ff, Rf ); // Add contribution to result

  }  // End gradient function
         
}; // class LocalTV     

} // namespace DGM

#endif  // DGM_LOCAL_TV_HPP
