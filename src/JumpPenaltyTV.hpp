#ifndef DGM_JUMP_PENALTY_TV_HPP
#define DGM_JUMP_PENALTY_TV_HPP

/** \file   JumpPenaltyTV.hpp
 *  \brief  DG jump penalty for total variation and gradient
 *  \author S. Scott Collis
 *  \author Greg von Winckel
*/   

// DGM includes
#include "RegularizationSide.hpp"

/**
 *  \class DGM::JumpPenaltyTV
 *  \brief Regularization term to penalize jumps over elemental boundaries
 *         that would appear in a TV penalty
 *
 *  The exact boundary term would be \f$|[[u]]|\f$ but is approximated
 *  by the smoothed function \f$\sqrt{[[u]]^2+\gamma}\f$
 *
 *  The objective is
 *  \f[ J[u] = \sum\limits_{\Gamma_k} \sqrt{[[u]]^2 + \gamma} \,d\Gamma \f]
 *  This can be evaluated as a volume integral using the lift operator.
 *  The gradient is
 *  \f[ (v,\nabla J[u]) = 2 \sum\limits_{\Gamma_k}
 *      \frac{[[u]] [[v]]}{\sqrt{[[u]]^2+\gamma}} \,d\Gamma \f]
 *
 *  \note It would be helpful to write the gradient without the jump
 *        on \f$[[v]]\f$.
 */
namespace DGM {

class JumpPenaltyTV : public RegularizationSide {

  const DGM::Comm::Ptr comm;    ///< Communicator for this domain
  const int verb;               ///< verbosity level
  dVector mu;                   ///< scalings for each component
  double gamma;                 ///< Absolute value broadening factor

  vField Sf;                    ///< vector Field for scratch computation

public:

  /// Constructor
  JumpPenaltyTV(vField &S, const dVector &mu_, const double &gam_,
              const DGM::Comm::Ptr comm_ = DGM::Comm::World )
  : comm(comm_), verb(0), mu(mu_), gamma(gam_), Sf(comm_)
  {
    if (verb) comm->cout() << "JumpPenaltyTV::JumpPenaltyTV(...)" << endl;
    // set the local scratch space
    Sf = S;
  }
   
  /// JSON Constructor
  JumpPenaltyTV(vField &S, const Json::Value& json, 
                const DGM::Comm::Ptr comm_ = DGM::Comm::World )
  : comm(comm_), verb(0), Sf(comm_) 
  {
    if (verb) comm->cout() << "JumpPenaltyTV::JumpPenaltyTV(...)" << endl;
    // set the local scratch space
    Sf = S;
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
          throw DGM::exception("JumpPenaltyTV: Json mu must have same "
                               "size as vField");
        }
      } else {
        throw DGM::exception("JumpPenaltyTV: Json mu must be an array"); 
      }
    } else {
      // Backward compatibility if mu is not given - set to all ones
      mu.Set(one);
    }
    if(json.isMember("gamma")) {
      Json::Value gammaval = json.get("gamma",0);
      gamma = gammaval.asDouble();
    } else {
      throw DGM::exception("JumpPenaltyTV: Json gamma must be defined");  
    }

    readMaskSides(json);
    isMaskEmpty = mask.empty();
  
  }
                  
  /// Destructor
  virtual ~JumpPenaltyTV() {
#ifdef TEST_REGULARIZATION_MASK
    ofstream maskFile;
    maskFile.open("jumppenaltytv.mask");

    for(unsigned i=0;i<mask.size();++i) {
      maskFile  << std::get<0>(mask[i]) << "," << std::get<1>(mask[i]) << std::endl;  
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
    assert (x.size() == Sf.size());
    vField &xl = const_cast<vField &>(x);
    vField &fl = const_cast<vField &>(Sf);
    return const_cast<JumpPenaltyTV*>(this)->evaluate(xl,fl,result);
  }

  /// Compute the gradient
  virtual void grad(const vField &x, vField &g) const {
    assert (x.size() == Sf.size());
    vField &xl = const_cast<vField&>(x);
    vField &fl = const_cast<vField &>(Sf);
    const_cast<JumpPenaltyTV*>(this)->gradient(xl,fl,g);
  }

  /// Compute the Hessian-vector product
  virtual void hessvec(const vField &x, const vField &dx, vField &H_dx) const {
    DGM_UNDEFINED;
  }
  //@}

private:

  /// Evaluate the contributions to the TV jump penalty term
  Scalar evaluate(vField &Uf, vField &Ff, dVector &result) {
    if (verb) comm->cout() << "JumpPenaltyTV::evaluate() for vField = "
                           << Uf.get_name() << endl;

    // initialize the result vector
    result.resize(Uf.size());
    result = zero;

    Ff.zero();

    Uf.fill_sides();
    Uf.fill_bc_sides();
    Uf.share_sides();

    // F should have the jump on its sides
    jumpAbs(Uf,Ff);
    
    Uf.fill_sides(zero);
    Uf.fill_bc_sides(zero);
    Uf.share_sides();

    // Loop over vector field components
    for (Ordinal n=0; n<Uf.size(); ++n) {

      // Loop over elements
      for (Ordinal e=0; e<Uf[n]->ne; ++e) {

        // Pointer to current element of current field component
        Element *U = Uf[n]->el[e];
        Element *F = Ff[n]->el[e];

        // Lift the side jumps to the interior 
        U->lift(F,F->u);

        // Add integral over this element for field component n to J
        result[n] += mu[n] * U->integrate(F->u);

      }  // End element loop

    }  // End field component loop

    return result.Sum();

  } // End evaluate method

  /// Evaluate smoothed absolute value of jump term
  /** \param[in]  Uf   Solution field
      \param[out] Ff   Jump
  */
  void jumpAbs(const vField &Uf, vField &Ff) const {
    for (Ordinal n=0; n<Uf.size(); n++) {   // Loop over field components
      for (Ordinal e=0; e<Uf[n]->ne; e++) { // Loop over elements
        const Element* const U = Uf[n]->el[e];
        for (Ordinal i=0; i<Uf[n]->el[e]->nSides(); i++) { // Loop over sides
    
          // Skip this (element,side) if it appears in the mask
          if(inMask(e,i)) {
            break;
          }

          const Side* const Us = Uf[n]->el[e]->side[i];
          Side* Fs = Ff[n]->el[e]->side[i];
          if (Us->master()) {
            // Loop over side degrees of freedom
            for (Ordinal q=0; q<Us->qtot(); q++) {
              const Ordinal ql = U->sideMap(Us, q);
              const Ordinal qr = U->sideMap(Us->link, q);
              const double jump = Us->u[ql] - Us->link->u[qr];
              const double jabs = sqrt(gamma+jump*jump);
              Fs->u[ql] = jabs;
              Fs->link->u[qr] = jabs;
            }
          }
#ifdef DGM_ALLOW_HANGING_NODES
          for (size_t j=0; j<Fs->subsides().size(); j++) { // Loop over sides
            const Side* const Uss = Us->subsides()[j].get();
            Side* Fss = Fs->subsides()[j].get();
            if (Fss->master()) {
              // Loop over side degrees of freedom
              for (Ordinal q=0; q<Uss->qtot(); q++) {
                const Ordinal ql = U->sideMap(Uss, q);
                const Ordinal qr = U->sideMap(Uss->link, q);
                const double jump = Uss->u[ql] - Uss->link->u[qr];
                const double jabs = sqrt(gamma+jump*jump);
                Fss->u[ql] = jabs;
                Fss->link->u[qr] = jabs;
              }
            }
          }
#endif
        }
      }
    }
  }

  /// Evaluate the jump scaled by \f$(\gamma+[[u]])^{-1/2}\f$ term
  /** \param[in]  Uf   Solution field
      \param[out] Ff   Jump approximate absolute value
  */
  void jumpScaled(const vField &Uf, vField &Ff ) const {
    for (Ordinal n=0; n<Uf.size(); n++) { // Loop over field components
      for (Ordinal e=0; e<Uf[n]->ne; e++) { // Loop over elements
        const Element* const U = Uf[n]->el[e];
        for (Ordinal i=0; i<Uf[n]->el[e]->nSides(); i++) { // Loop over sides

          // Skip this (element,side) if it appears in the mask
          if(inMask(e,i)) {
            break;
          }

          const Side* const Us = Uf[n]->el[e]->side[i];
          Side* Fs = Ff[n]->el[e]->side[i];
          if (Us->master()) {
            // Loop over side degrees of freedom
            for (Ordinal q=0; q<Us->qtot(); q++) {
              const Ordinal ql = U->sideMap(Us, q);
              const Ordinal qr = U->sideMap(Us->link, q);
              double jump = Us->u[ql] - Us->link->u[qr];
              jump /= sqrt(gamma + jump*jump);
              Fs->u[ql] = jump;
              Fs->link->u[qr] = -jump;
            }
          }
#ifdef DGM_ALLOW_HANGING_NODES
          for (size_t j=0; j<Fs->subsides().size(); j++) { // Loop over sides
            const Side* const Uss = Us->subsides()[j].get();
            Side* Fss = Fs->subsides()[j].get();
            if (Fss->master()) {
              // Loop over side degrees of freedom
              for (Ordinal q=0; q<Uss->qtot(); q++) {
                const Ordinal ql = U->sideMap(Uss, q);
                const Ordinal qr = U->sideMap(Uss->link, q);
                double jump = Us->u[ql] - Us->link->u[qr];
                jump /= sqrt(gamma + jump*jump);
                Fss->u[ql] = jump;
                Fss->link->u[qr] = -jump;
              }
            }
          }
#endif
        }
      }
    }
  }

  /// Evaluate the contributions to the gradient for the jump penalty term
  /** \param[in]     Uf - Vector field to apply operator
   *  \param[in]     Ff - Scratch vector field
   *  \param[in,out] Rf - Result vector field
   */
  void gradient(vField &Uf, vField &Ff, vField &Rf) {

    if (verb) comm->cout() << "JumpPenaltyTV::gradient() for vField = "
                           << Uf.get_name() << endl;

    // Share sides in parallel
    Uf.fill_sides();
    Uf.fill_bc_sides();
    Uf.share_sides();

    Ff.zero();

    // S should have the scaled jump  on its sides
    jumpScaled(Uf,Ff);    

    Uf.fill_sides(zero);
    Uf.fill_bc_sides(zero);
    Uf.share_sides();

    // Loop over vector field components
    for (Ordinal n=0; n<Uf.size(); ++n) {

      // Loop over elements
      for (Ordinal e=0; e<Uf[n]->ne; ++e) {

        // Element field storage
        Element *U = Uf[n]->el[e];
        Element *F = Ff[n]->el[e];
        Element *R = Rf[n]->el[e];

        // Lift the side jumps to the interior 
        U->lift(F,F->u);

        daxpy(two*mu[n],F->u,R->u);

      }  // End element loop

    }  // End field component loop

  }  // End gradient method
         
}; // JumpPenaltyTV class

} // namespace DGM

#endif  // DGM_JUMP_PENALTY_TV_HPP
