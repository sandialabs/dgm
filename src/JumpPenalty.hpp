#ifndef DGM_JUMP_PENALTY_HPP
#define DGM_JUMP_PENALTY_HPP

/** \file   JumpPenalty.hpp
 *  \brief  DG jump penalty and gradient
 *  \author S. Scott Collis
 *  \author Greg von Winckel
*/   

// DGM includes
#include "RegularizationSide.hpp"

/**
 *  \class DGM::JumpPenalty
 *  \brief Regularization term to penalize jumps over elemental boundaries
 *
 *  The objective is
 *  \f[ J[u] = \sum\limits_{\Gamma_k} [[u]]^2\,d\Gamma \f]
 *  This can be evaluated as a volume integral using the lift operator
 *  The gradient is
 *  \f[ (v,\nabla J[u]) = 2 \sum\limits_{\Gamma_k} [[u]] [[v]] \,d\Gamma \f]
 *
 *  \note It would be helpful to write the gradient without the jump
 *        on \f$[[v]]\f$.
*/ 
namespace DGM {

class JumpPenalty : public RegularizationSide {

  const DGM::Comm::Ptr comm;    ///< Communicator for this domain
  const int verb;               ///< verbosity level
  dVector mu;                   ///< scalings for each component

  dVector wk;                   ///< local workspace

  vField Sf;                    ///< vector Field for scratch computation

public:

  /// Constructor
  JumpPenalty(vField &S, const dVector &mu_,
              const DGM::Comm::Ptr comm_ = DGM::Comm::World )
  : comm(comm_),verb(comm_->verbosity()), mu(mu_), Sf(comm_)
  {
    if (verb) comm->cout() << "JumpPenalty::JumpPenalty(...)" << endl;

    // set the local scratch space
    Sf = S;

    // allocate local workspace
    wk.resize(max(S.Lmax(),S.Qmax()));
  }
        

  /// JSON Constructor
  JumpPenalty(vField &S, const Json::Value& json,
              const DGM::Comm::Ptr comm_ = DGM::Comm::World)
  : comm(comm_), verb(comm_->verbosity()), Sf(comm_)
  {
    if (verb) comm->cout() << "JumpPenalty::JumpPenalty(...)" << endl;

    // set the local scratch space
    Sf = S;

    // allocate local workspace
    wk.resize(max(S.Lmax(),S.Qmax()));

    mu.resize(S.size());

    // The block must contain a key "mu" with corresponding value of 
    // array type and the array must have the correct number of elements
    if(json.isMember("mu")) {
      Json::Value muval = json.get("mu",0);
      if(muval.isArray()) {
        Ordinal n = S.size();
        if(n == static_cast<Ordinal>(muval.size())) {
          for(Ordinal i=0; i<n; ++i) {
            mu[i] = muval[i].asDouble();
          }
        } else { // JSON mu has incompatible size
          throw DGM::exception("JumpPenalty: Json mu must have same "
                               "size as vField");
        }
      } else { // Backward compatibility if mu is not given - set to all ones
        mu.Set(one);
      }
    } else {
      throw DGM::exception("JumpPenalty: Json mu must be defined");  
    }

    readMaskSides(json);
    isMaskEmpty = mask.empty();
 
  }

  /// Destructor
  virtual ~JumpPenalty() {

#ifdef TEST_REGULARIZATION_MASK
    ofstream maskFile;
    maskFile.open("jumppenalty.mask");

    for(unsigned i=0;i<mask.size();++i) {
      maskFile  << std::get<0>(mask[i]) << "," << std::get<1>(mask[i]) << std::endl;     }

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
    return const_cast<JumpPenalty*>(this)->evaluate(xl,fl,result);
  }

  /// Compute the gradient
  virtual void grad(const vField &x, vField &g) const {
    assert (x.size() == Sf.size());
    vField &xl = const_cast<vField&>(x);
    vField &fl = const_cast<vField &>(Sf);
    const_cast<JumpPenalty*>(this)->gradient(xl,fl,g);
  }

  /// Compute the Hessian-vector product
  virtual void hessvec(const vField &x, const vField &dx, vField &H_dx) const {
    DGM_UNDEFINED;
  }
  //@}

private:

  /// Evaluate the contributions to the jump penalty term
  Scalar evaluate(vField &Uf, vField &Ff, dVector &result) {
    if (verb) comm->cout() << "JumpPenalty::evaluate() for vField = "
                           << Uf.get_name() << endl;

    // initialize the result vector
    result.resize(Uf.size());
    result = zero;

    Ff.zero();

    Uf.fill_sides();
    Uf.fill_bc_sides();
    Uf.share_sides();

    // F should have the jump on its sides
    jumpSquared(Uf,Ff);
    
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

  /// Evaluate a jump term
  /** \param[in]  Uf   Solution field
      \param[out] Ff   Jump
  */
  void jump(const vField &Uf, vField &Ff) const {
    for (Ordinal n=0; n<Uf.size(); n++) {
      for (Ordinal e=0; e<Uf[n]->ne; e++) {
        const Element* const U = Uf[n]->el[e];
        for (Ordinal i=0; i<Uf[n]->el[e]->nSides(); i++) {

          // Skip this (element,side) if it appears in the mask
          if(inMask(e,i)) {
            break;
          }
 
          const Side* const Us = Uf[n]->el[e]->side[i];
          Side* Fs = Ff[n]->el[e]->side[i];
          if (Us->master()) {
            for (Ordinal q=0; q<Us->qtot(); q++) {
              const Ordinal ql = U->sideMap(Us, q);
              const Ordinal qr = U->sideMap(Us->link, q);
              Fs->u[ql] = ( Us->u[ql] - Us->link->u[qr] );
              Fs->link->u[qr] = -Fs->u[ql];
            }
          }
#ifdef DGM_ALLOW_HANGING_NODES
          for (size_t j=0; j<Fs->subsides().size(); j++) {
            const Side* const Uss = Us->subsides()[j].get();
            Side* Fss = Fs->subsides()[j].get();
            if (Fss->master()) {
              for (Ordinal q=0; q<Uss->qtot(); q++) {
                const Ordinal ql = U->sideMap(Uss, q);
                const Ordinal qr = U->sideMap(Uss->link, q);
                Fss->u[ql] = ( Uss->u[ql] - Uss->link->u[qr] );
                Fss->link->u[qr] = -Fss->u[ql];
              }
            }
          }
#endif
        } // End side loop
      } // End element loop 
    } // End field component loop
  }

  /// Evaluate the jump squared term
  /** \param[in]  Uf   Solution field
      \param[out] Ff   Jump squared
  */
  void jumpSquared(const vField &Uf, vField &Ff) const {
    for (Ordinal n=0; n<Uf.size(); n++) {
      for (Ordinal e=0; e<Uf[n]->ne; e++) {
        const Element* const U = Uf[n]->el[e];
        for (Ordinal i=0; i<Uf[n]->el[e]->nSides(); i++) {

          // Skip this (element,side) if it appears in the mask
          if(inMask(e,i)) {
            break;
          }

          const Side* const Us = Uf[n]->el[e]->side[i];
          Side* Fs = Ff[n]->el[e]->side[i];
          if (Us->master()) {
            for (Ordinal q=0; q<Us->qtot(); q++) {
              const Ordinal ql = U->sideMap(Us, q);
              const Ordinal qr = U->sideMap(Us->link, q);
              Fs->u[ql] = ( Us->u[ql] - Us->link->u[qr] );
              Fs->u[ql] *= Fs->u[ql];
              Fs->link->u[qr] = Fs->u[ql];
            }
          }
#ifdef DGM_ALLOW_HANGING_NODES
          for (size_t j=0; j<Fs->subsides().size(); j++) {
            const Side* const Uss = Us->subsides()[j].get();
            Side* Fss = Fs->subsides()[j].get();
            if (Fss->master()) {
              for (Ordinal q=0; q<Uss->qtot(); q++) {
                const Ordinal ql = U->sideMap(Uss, q);
                const Ordinal qr = U->sideMap(Uss->link, q);
                Fss->u[ql] = ( Uss->u[ql] - Uss->link->u[qr] );
                Fss->u[ql] *= Fss->u[ql];
                Fss->link->u[qr] = Fss->u[ql];
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

    if (verb) comm->cout() << "JumpPenalty::gradient() for vField = "
                           << Uf.get_name() << endl;

    // Share sides in parallel
    Uf.fill_sides();
    Uf.fill_bc_sides();
    Uf.share_sides();

    Ff.zero();

    // F should have the jump on its sides
    jump(Uf,Ff);

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

        daxpy(four*mu[n],F->u,R->u);

      }  // End element loop

    }  // End field component loop

  }  // End gradient method
         
}; // JumpPenalty class

} // namespace DGM

#endif  // DGM_JUMP_PENALTY_HPP
