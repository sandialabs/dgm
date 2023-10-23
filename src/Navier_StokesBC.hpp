#ifndef REO_NAVIER_STOKES_BC_HPP
#define REO_NAVIER_STOKES_BC_HPP

/** \file Navier_StokesBC.hpp
    \brief Boundary conditions for the compressible Navier-Stokes equations
*/

// system includes
#include <fstream>
#include <iomanip>

// DGM includes
#include "BC.hpp"
#include "Ctrl.hpp"
using DGM::BC;
using DGM::Ctrl;

namespace Reo {

//===========================================================================
//                        Isothermal Solid Wall
//===========================================================================

/// Isothermal wall boundary condition
class Navier_Stokes::Isothermal_WallBC : public BC {
  Scalar Tw;     // constant wall temperature
  Scalar Eref;   // reference stagnation energy per unit volume
                 // (rho_r*T_r)/(gamma*(gamma-1)*Ma_r^2)
  // Well, in reality Eref = Cv + 0.5 (and this should REALLY be changed to Cv)
public:
  Isothermal_WallBC( const string t, const Scalar Tw_, const Scalar Eref_ ) :
    BC(t), Tw(Tw_), Eref(Eref_) { }
  Isothermal_WallBC( const string t, ifstream &in ) : BC(t), Tw(0), Eref(0) {
    scan_lb(in);
    if (!(in >> Tw >> Eref))
      error("Navier_Stokes::Isothermal_WallBC: Tw, Eref");
    scan_rb(in);
  }
  inline void apply( const Scalar t, const vField & ) ;
  inline void apply_flux( const Scalar t, const vField & ) ;

  inline void adjoint_apply( const Scalar t, const vField &, const vField & );
  inline void adjoint_apply_flux( const Scalar t, const vField &,
                                  const vField & );
};

void Navier_Stokes::Isothermal_WallBC::apply( const Scalar t,
                                              const vField &F ) {
  vector<Side*> S(F.size()), B(F.size());
  for (LocalSize n=0; n<F[0]->nbc; ++n)   // loop over field boundaries
    if (F[0]->bc[n]->type == type ) {
      //dVector &nx = F[0]->bc[n]->S->nx();
      //dVector &ny = F[0]->bc[n]->S->ny();
      for (vField::size_type i=0; i<F.size(); ++i){
        S[i] = F[i]->bc[n]->S;
        B[i] = F[i]->bc[n]->B;
      }
      for (LocalSize i=0; i<S[0]->qtot(); i++) {
        B[0]->u[i] = S[0]->u[i];
        B[1]->u[i] = 0.0;
        B[2]->u[i] = 0.0;
        B[3]->u[i] = (Eref-0.5)*B[0]->u[i]*Tw;//(rho*Tw)/(gamma*(gamma-1)*Ma^2)
      }
    }
}

void Navier_Stokes::Isothermal_WallBC::apply_flux( const Scalar t,
                                                   const vField &F ) {
  vector<Side*> S(F.size()), B(F.size());
  for (LocalSize n=0; n<F[0]->nbc; ++n)   // loop over field boundaries
    if (F[0]->bc[n]->type == type ) {
      //dVector &nx = F[0]->bc[n]->S->nx();
      //dVector &ny = F[0]->bc[n]->S->ny();
      for (vField::size_type i=0; i<F.size(); ++i){
        S[i] = F[i]->bc[n]->S;
        B[i] = F[i]->bc[n]->B;
      }
      for (LocalSize i=0; i<S[0]->qtot(); i++) {
        B[0]->u[i] = -S[0]->u[i];
        B[1]->u[i] = -S[1]->u[i];
        B[2]->u[i] = -S[2]->u[i];
        B[3]->u[i] = -S[3]->u[i];
      }
    }
}

// \lambda_1 = 0;  \lambda_2 = 0;  \lambda_3 = 0
void Navier_Stokes::Isothermal_WallBC::adjoint_apply( const Scalar t,
                                                      const vField &state,
                                                      const vField &adjoint) {
  vector<Side*> S(adjoint.size()), B(adjoint.size());
  for (LocalSize n=0; n<adjoint[0]->nbc; ++n)   // loop over field boundaries
    if (adjoint[0]->bc[n]->type == type ) {
      //dVector &nx = adjoint[0]->bc[n]->S->nx();
      //dVector &ny = adjoint[0]->bc[n]->S->ny();
      for (vField::size_type i=0; i<adjoint.size(); ++i){
        S[i] = adjoint[i]->bc[n]->S;
        B[i] = adjoint[i]->bc[n]->B;
      }
      for (LocalSize i=0; i<S[0]->qtot(); i++) {
        B[0]->u[i] = S[0]->u[i];
        B[1]->u[i] = 0.0;
        B[2]->u[i] = 0.0;
        B[3]->u[i] = 0.0;
      }
    }
}

//  \lambda_1 = 0;  \lambda_2 = 0;  \lambda_3 = 0
void Navier_Stokes::Isothermal_WallBC::
adjoint_apply_flux( const Scalar t, const vField &state,
                    const vField &adjoint ) {
  vector<Side*> S(adjoint.size()), B(adjoint.size());
  for (LocalSize n=0; n<adjoint[0]->nbc; ++n)   // loop over field boundaries
    if (adjoint[0]->bc[n]->type == type ) {
      //dVector &nx = adjoint[0]->bc[n]->S->nx();
      //dVector &ny = adjoint[0]->bc[n]->S->ny();
      for (vField::size_type i=0; i<adjoint.size(); ++i){
        S[i] = adjoint[i]->bc[n]->S;
        B[i] = adjoint[i]->bc[n]->B;
      }
      for (LocalSize i=0; i<S[0]->qtot(); i++) {
        B[0]->u[i] = -S[0]->u[i];
        B[1]->u[i] = -S[1]->u[i];
        B[2]->u[i] = -S[2]->u[i];
        B[3]->u[i] = -S[3]->u[i];
      }
    }
}

//===========================================================================
//                     Constant Heat Flux Solid Wall
//===========================================================================

/// Constant flux wall boundary condition
class Navier_Stokes::Isoflux_WallBC : public BC {
  Scalar qw;     ///< constant heat flux
  Scalar gamma, Ma, Re, Pr, K, mu, lambda;
public:
  //Isoflux_WallBC( const string t, const Scalar qw_ ) : BC(t), qw(qw_) { }
  Isoflux_WallBC( const string t, ifstream &in , const Scalar gamma_,
                  const Scalar mu_, const Scalar Pr_):
    BC(t), qw(0), gamma(gamma_),
    Ma(1.0), Re(1.0), Pr(Pr_), K(mu_), mu(mu_), lambda(-2.0/3.0*mu)
  {
    scan_lb(in);
    if (!(in >> qw )) error("Navier_Stokes::Isoflux_WallBC: qw");
    Ma = 1.0;             // Ma is not explicitly needed
    scan_rb(in);
    Re     = 1.0;         // Set so that Re=1/mu
    lambda = -2.0/3.0*mu; // Stokes hypothesis
    K      = mu;          // To match CNS2D normalization
  }

  inline void apply( const Scalar t, const vField & );
  inline void apply_flux( const Scalar t, const vField & );

  inline void adjoint_apply( const Scalar t, const vField &, const vField & );
  inline void adjoint_apply_flux( const Scalar t, const vField &,
                                  const vField & );
};

void Navier_Stokes::Isoflux_WallBC::apply( const Scalar t, const vField &F ) {
  vector<Side*> S(F.size()), B(F.size());
  for (LocalSize n=0; n<F[0]->nbc; ++n)   // loop over field boundaries
    if (F[0]->bc[n]->type == type ) {
      //dVector &nx = F[0]->bc[n]->S->nx();
      //dVector &ny = F[0]->bc[n]->S->ny();
      for (vField::size_type i=0; i<F.size(); ++i){
        S[i] = F[i]->bc[n]->S;
        B[i] = F[i]->bc[n]->B;
      }
      for (LocalSize i=0; i<S[0]->qtot(); i++) {
        B[0]->u[i] = S[0]->u[i];
        B[1]->u[i] = 0.0;
        B[2]->u[i] = 0.0;
        B[3]->u[i] = S[3]->u[i]
          - 0.5*(S[1]->u[i]*S[1]->u[i] + S[2]->u[i]*S[2]->u[i])/S[0]->u[i]
          + 0.5*(B[1]->u[i]*B[1]->u[i] + B[2]->u[i]*B[2]->u[i])/B[0]->u[i];
      }
    }
}

void Navier_Stokes::Isoflux_WallBC::apply_flux( const Scalar t,
                                                const vField &F ) {
  vector<Side*> S(F.size()), B(F.size());
  for (LocalSize n=0; n<F[0]->nbc; ++n)   // loop over field boundaries
    if (F[0]->bc[n]->type == type ) {
      //dVector &nx = F[0]->bc[n]->S->nx();
      //dVector &ny = F[0]->bc[n]->S->ny();
      for (vField::size_type i=0; i<F.size(); ++i){
        S[i] = F[i]->bc[n]->S;
        B[i] = F[i]->bc[n]->B;
      }
      for (LocalSize i=0; i<S[0]->qtot(); i++) {
        B[0]->u[i] = -S[0]->u[i];
        B[1]->u[i] = -S[1]->u[i];
        B[2]->u[i] = -S[2]->u[i];
        B[3]->u[i] = -qw;
      }
    }
}

// \lambda_1 =0;  \lambda_2 =0;  \lambda_{3,n} =0
void Navier_Stokes::Isoflux_WallBC::adjoint_apply
( const Scalar t, const vField &state, const vField &adjoint ) {
  vector<Side*> S(adjoint.size()), B(adjoint.size());
  for (LocalSize n=0; n<adjoint[0]->nbc; ++n)   // loop over field boundaries
    if (adjoint[0]->bc[n]->type == type ) {
      //dVector &nx = adjoint[0]->bc[n]->S->nx();
      //dVector &ny = adjoint[0]->bc[n]->S->ny();
      for (vField::size_type i=0; i<adjoint.size(); ++i){
        S[i] = adjoint[i]->bc[n]->S;
        B[i] = adjoint[i]->bc[n]->B;
      }
      for (LocalSize i=0; i<S[0]->qtot(); i++) {
        B[0]->u[i] = S[0]->u[i];
        B[1]->u[i] = 0.0;
        B[2]->u[i] = 0.0;
        B[3]->u[i] = S[3]->u[i];
      }
    }
}

// \lambda_{3,n} =0
void Navier_Stokes::Isoflux_WallBC::adjoint_apply_flux
( const Scalar t, const vField &state, const vField &adjoint ) {
  LocalSize Nfields = adjoint.size();
  vector<Side*> S(Nfields), B(Nfields), SS(Nfields);
  Scalar rho, m, n, E;
  dVector Fvx(Nfields), Fvy(Nfields);
  //int offset=0;
  for (LocalSize nb=0; nb<state[0]->nbc; ++nb)   // loop over field boundaries
    if (state[0]->bc[nb]->type == type ) {
      dVector &nx = state[0]->bc[nb]->S->nx();
      dVector &ny = state[0]->bc[nb]->S->ny();
      const LocalSize sid = adjoint[0]->bc[nb]->sid;
      //const Size eid = adjoint[0]->bc[nb]->elmt->id;
      for (LocalSize i=0; i<Nfields; ++i) {
        S[i] = adjoint[i]->bc[nb]->S;
        B[i] = adjoint[i]->bc[nb]->B;
        SS[i]= state[i]->bc[nb]->B;
      }

      assert(SS[0]->qtot() == S[0]->qtot() );
      // Project the State side => Adjoint side
      // do some projection here,two ways to project [gqchen]
      // 1) use the G->G interpolate
      // 2) base on the edge modes

      Ordinal vqtot = adjoint[0]->bc[nb]->elmt->qtot;
      Ordinal bqtot = S[0]->qtot();

      dVector ru(bqtot);  ru = SS[1]->u;
      dVector rv(bqtot);  rv = SS[2]->u;

      dVector lamv_x[4], lamv_y[4];
      dVector lamb_x[4], lamb_y[4];

      dVector tmp1(bqtot), tmp2(bqtot);

      for(LocalSize i=0; i<Nfields; i++) {
        lamv_x[i].resize(vqtot);
        lamv_y[i].resize(vqtot);
        lamb_x[i].resize(bqtot);
        lamb_y[i].resize(bqtot);
      }
#ifndef REO_JUMP1
      for(LocalSize i=0;i<Nfields;i++){
        adjoint[i]->bc[nb]->elmt->gradient(adjoint[i]->bc[nb]->elmt->u,
                                           lamv_x[i],lamv_y[i]);
        adjoint[i]->bc[nb]->elmt->load_side(lamv_x[i],sid,lamb_x[i]);
        adjoint[i]->bc[nb]->elmt->load_side(lamv_y[i],sid,lamb_y[i]);
      }
#endif

      // Here two constraints:
      //  lam3_n = 0.0
      //  lam3_s = lam3_s(inside)
      tmp2 =0;
      dvvtvm(ny,lamb_x[3],tmp2,tmp2);      // -lam3,x *ny
      dvvtvp(nx,lamb_y[3],tmp2,tmp2);      // lam3,s=-ny*lam3,x+nx*lam3,y

      tmp1 =0; // lam3,n

      lamb_x[3] =0;
      dvvtvm(ny,tmp2,lamb_x[3],lamb_x[3]);
      dvvtvp(nx,tmp1,lamb_x[3],lamb_x[3]); // lam3_x @bc

      lamb_y[3] =0;
      dvvtvp(ny,tmp1,lamb_y[3],lamb_y[3]);
      dvvtvp(nx,tmp2,lamb_y[3],lamb_y[3]); // lam3_y @bc

      for (LocalSize q=0; q<bqtot; q++) {
        rho = SS[0]->u[q];
        m   = SS[1]->u[q];
        n   = SS[2]->u[q];
        E   = SS[3]->u[q];

        Fvx[0] = -(2.0*mu+lambda)*m/(rho*rho)/Re*lamb_x[1][q]
          -n/(rho*rho)*mu/Re*lamb_x[2][q]
          +(-(2.0*mu+lambda)*m*m/(rho*rho*rho)/Re-n*n/(rho*rho*rho)*mu/Re
            +(gamma*(gamma-1.0)*(m*m+n*n)/(rho*rho*rho)/2.0
              -gamma*(gamma-1.0)*(E-(m*m+n*n)/rho/2.0)/(rho*rho))
            *K/Re/Pr/(gamma-1.0))*lamb_x[3][q]-n/(rho*rho)*mu/Re
          *lamb_y[1][q]-lambda/(rho*rho)/Re*m*lamb_y[2][q]
          +(-lambda*n/(rho*rho*rho)/Re*m-m/(rho*rho*rho)*mu/Re*n)*lamb_y[3][q];
        Fvx[1] = (2.0*mu+lambda)/rho/Re*lamb_x[1][q]
          +((2.0*mu+lambda)*m/(rho*rho)/Re
            -gamma*m/(rho*rho)*K/Re/Pr)*lamb_x[3][q]
          +lambda/rho/Re*lamb_y[2][q]+lambda*n/(rho*rho)/Re*lamb_y[3][q];
        Fvx[2] = 1/rho*mu/Re*lamb_x[2][q]
          +(n/(rho*rho)*mu/Re-gamma*n/(rho*rho)*K/Re/Pr)*lamb_x[3][q]
          +1/rho*mu/Re*lamb_y[1][q]+m/(rho*rho)*mu/Re*lamb_y[3][q];
        Fvx[3] = gamma/rho*K/Re/Pr*lamb_x[3][q];

        Fvy[0] = -lambda*n/(rho*rho)/Re*lamb_x[1][q]
          -m/(rho*rho)*mu/Re*lamb_x[2][q]
          +(-lambda*n/(rho*rho*rho)/Re*m-m/(rho*rho*rho)*mu/Re*n)*lamb_x[3][q]
          -m/(rho*rho)*mu/Re*lamb_y[1][q]
          -(2.0*mu+lambda)*n/(rho*rho)/Re*lamb_y[2][q]
          +(-m*m/(rho*rho*rho)*mu/Re-(2.0*mu+lambda)*n*n/(rho*rho*rho)/Re
            +(gamma*(gamma-1.0)*(m*m+n*n)/(rho*rho*rho)/2.0
              -gamma*(gamma-1.0)*(E-(m*m+n*n)/rho/2.0)/(rho*rho))
            *K/Re/Pr/(gamma-1.0))*lamb_y[3][q];
        Fvy[1] = 1/rho*mu/Re*lamb_x[2][q]+n/(rho*rho)*mu/Re*lamb_x[3][q]
          +1/rho*mu/Re*lamb_y[1][q]+(m/(rho*rho)*mu/Re
                                     -gamma*m/(rho*rho)*K/Re/Pr)*lamb_y[3][q];
        Fvy[2] = lambda/rho/Re*lamb_x[1][q]+lambda/(rho*rho)/Re*m*lamb_x[3][q]
          +(2.0*mu+lambda)/rho/Re*lamb_y[2][q]
          +((2.0*mu+lambda)*n/(rho*rho)/Re
            -gamma*n/(rho*rho)*K/Re/Pr)*lamb_y[3][q];
        Fvy[3] = gamma/rho*K/Re/Pr*lamb_y[3][q];

        B[0]->u[q] = -(nx[q]*Fvx[0] + ny[q]*Fvy[0]);
        B[1]->u[q] = -(nx[q]*Fvx[1] + ny[q]*Fvy[1]);
        B[2]->u[q] = -(nx[q]*Fvx[2] + ny[q]*Fvy[2]);
        B[3]->u[q] = -(nx[q]*Fvx[3] + ny[q]*Fvy[3]);
      }
    }
}

//===========================================================================
//                            Slip  Walls
//===========================================================================

//===========================================================================
//                        Isothermal Slip Wall
//===========================================================================

/// Isothermal slip wall boundary condition
class Navier_Stokes::Isothermal_SlipWallBC : public BC {
  Scalar Tw;     // constant wall temperature
  Scalar Eref;   // reference stagnation energy per unit volume
                 // (rho_r*T_r)/(gamma*(gamma-1)*Ma_r^2)
public:
  Isothermal_SlipWallBC( const string t, const Scalar Tw_,
                         const Scalar Eref_ ) : BC(t), Tw(Tw_), Eref(Eref_) { }
  Isothermal_SlipWallBC( const string t, ifstream &in ) : BC(t), Tw(0), Eref(0)
  {
    scan_lb(in);
    if (!(in >> Tw >> Eref))
      error("Navier_Stokes::Isothermal_SlipWallBC: Tw, Eref");
    scan_rb(in);
  }
  inline void apply( const Scalar t, const vField & ) ;
  inline void apply_flux( const Scalar t, const vField & ) ;

  inline void adjoint_apply( const Scalar t, const vField &, const vField & ) ;
  inline void adjoint_apply_flux( const Scalar t, const vField &,
                                  const vField & ) ;
};

void Navier_Stokes::Isothermal_SlipWallBC::apply( const Scalar t,
                                                  const vField &F ) {
  vector<Side*> S(F.size()), B(F.size());
  for (LocalSize n=0; n<F[0]->nbc; ++n)   // loop over field boundaries
    if (F[0]->bc[n]->type == type ) {
      dVector &nx = F[0]->bc[n]->S->nx();
      dVector &ny = F[0]->bc[n]->S->ny();
      for (vField::size_type i=0; i<F.size(); ++i) {
        S[i] = F[i]->bc[n]->S;
        B[i] = F[i]->bc[n]->B;
      }
      for (LocalSize i=0; i<S[0]->qtot(); i++) {
        B[0]->u[i] = S[0]->u[i];
        B[1]->u[i] = (S[1]->u[i]*ny[i] - S[2]->u[i]*nx[i])*ny[i];
        B[2]->u[i] = (S[2]->u[i]*nx[i] - S[1]->u[i]*ny[i])*nx[i];
        B[3]->u[i] = (Eref-0.5)*B[0]->u[i]*Tw
          + 0.5*(B[1]->u[i]*B[1]->u[i] + B[2]->u[i]*B[2]->u[i])/B[0]->u[i];
      }
    }
}

void Navier_Stokes::Isothermal_SlipWallBC::apply_flux( const Scalar t,
                                                       const vField &F ) {
  vector<Side*> S(F.size()), B(F.size());
  for (LocalSize n=0; n<F[0]->nbc; ++n)   // loop over field boundaries
    if (F[0]->bc[n]->type == type ) {
      //dVector &nx = F[0]->bc[n]->S->nx();
      //dVector &ny = F[0]->bc[n]->S->ny();
      for (vField::size_type i=0; i<F.size(); ++i) {
        S[i] = F[i]->bc[n]->S;
        B[i] = F[i]->bc[n]->B;
      }
      for (LocalSize i=0; i<S[0]->qtot(); i++) {
        B[0]->u[i] = -S[0]->u[i];
        B[1]->u[i] = -S[1]->u[i];
        B[2]->u[i] = -S[2]->u[i];
        B[3]->u[i] = -S[3]->u[i];
      }
    }
}
// lambda_1 =0, lambda_2 =0, lambda_3 =0
void Navier_Stokes::Isothermal_SlipWallBC::
adjoint_apply( const Scalar t, const vField &state, const vField &adjoint) {
  vector<Side*> S(adjoint.size()), B(adjoint.size());
  for (LocalSize n=0; n<adjoint[0]->nbc; ++n)   // loop over field boundaries
    if (adjoint[0]->bc[n]->type == type ) {
      //dVector &nx = adjoint[0]->bc[n]->S->nx();
      //dVector &ny = adjoint[0]->bc[n]->S->ny();
      for (vField::size_type i=0; i<adjoint.size(); ++i){
        S[i] = adjoint[i]->bc[n]->S;
        B[i] = adjoint[i]->bc[n]->B;
      }
      for (LocalSize i=0; i<S[0]->qtot(); i++) {
        B[0]->u[i] = S[0]->u[i];
        B[1]->u[i] = 0.0;
        B[2]->u[i] = 0.0;
        B[3]->u[i] = 0.0;
      }
    }
}

void Navier_Stokes::Isothermal_SlipWallBC::adjoint_apply_flux
(const Scalar t, const vField &state, const vField &adjoint) {
  vector<Side*> S(adjoint.size()), B(adjoint.size());
  for (LocalSize n=0; n<adjoint[0]->nbc; ++n)   // loop over field boundaries
    if (adjoint[0]->bc[n]->type == type ) {
      //dVector &nx = adjoint[0]->bc[n]->S->nx();
      //dVector &ny = adjoint[0]->bc[n]->S->ny();
      for (vField::size_type i=0; i<adjoint.size(); ++i){
        S[i] = adjoint[i]->bc[n]->S;
        B[i] = adjoint[i]->bc[n]->B;
      }
      for (LocalSize i=0; i<S[0]->qtot(); i++) {
        B[0]->u[i] = -S[0]->u[i];
        B[1]->u[i] = -S[1]->u[i];
        B[2]->u[i] = -S[2]->u[i];
        B[3]->u[i] = -S[3]->u[i];
      }
    }
}

//===========================================================================
//                     Constant Heat Flux Slip Wall
//===========================================================================

/// Constant flux slip wall boundary condition
class Navier_Stokes::Isoflux_SlipWallBC : public BC {
  Scalar qw;     // constant heat flux
  Scalar gamma, Ma, Re, Pr, K, mu, lambda;
public:
  Isoflux_SlipWallBC( const string t, const Scalar qw_ ) : BC(t), qw(qw_) { }
  Isoflux_SlipWallBC( const string t, ifstream &in , const Scalar gamma_,
                      const Scalar mu_, const Scalar Pr_):
    BC(t), gamma(gamma_), Pr(Pr_), mu(mu_) {
    scan_lb(in);
    if (!(in >> qw )) error("Navier_Stokes::Isoflux_SlipWallBC: qw");
    scan_rb(in);
    Ma     = 1.0;         // Ma is not explicitly needed
    Re     = 1.0;         // Set so that Re=1/mu
    lambda = -2.0/3.0*mu; // Stokes hypothesis
    K      = mu;          // To match CNS2D normalization
  }

  inline void apply( const Scalar t, const vField & ) ;
  inline void apply_flux( const Scalar t, const vField & ) ;

  inline void adjoint_apply( const Scalar t, const vField &, const vField & ) ;
  inline void adjoint_apply_flux( const Scalar t, const vField &,
                                  const vField & ) ;
};

void Navier_Stokes::Isoflux_SlipWallBC::apply( const Scalar t,
                                               const vField &F ) {
  vector<Side*> S(F.size()), B(F.size());
  for (LocalSize n=0; n<F[0]->nbc; ++n)   // loop over field boundaries
    if (F[0]->bc[n]->type == type ) {
      dVector &nx = F[0]->bc[n]->S->nx();
      dVector &ny = F[0]->bc[n]->S->ny();
      for (vField::size_type i=0; i<F.size(); ++i) {
        S[i] = F[i]->bc[n]->S;
        B[i] = F[i]->bc[n]->B;
      }
      for (LocalSize i=0; i<S[0]->qtot(); i++) {
        B[0]->u[i] = S[0]->u[i];
        B[1]->u[i] = (S[1]->u[i]*ny[i] - S[2]->u[i]*nx[i])*ny[i];
        B[2]->u[i] = (S[2]->u[i]*nx[i] - S[1]->u[i]*ny[i])*nx[i];
        B[3]->u[i] = S[3]->u[i]
          - 0.5*(S[1]->u[i]*S[1]->u[i] + S[2]->u[i]*S[2]->u[i])/S[0]->u[i]
          + 0.5*(B[1]->u[i]*B[1]->u[i] + B[2]->u[i]*B[2]->u[i])/B[0]->u[i];
      }
    }
}

void Navier_Stokes::Isoflux_SlipWallBC::apply_flux( const Scalar t,
                                                    const vField &F ) {
  vector<Side*> S(F.size()), B(F.size());
  for (LocalSize n=0; n<F[0]->nbc; ++n)   // loop over field boundaries
    if (F[0]->bc[n]->type == type) {
      //dVector &nx = F[0]->bc[n]->S->nx();
      //dVector &ny = F[0]->bc[n]->S->ny();
      for (vField::size_type i=0; i<F.size(); ++i) {
        S[i] = F[i]->bc[n]->S;
        B[i] = F[i]->bc[n]->B;
      }
      for (LocalSize i=0; i<S[0]->qtot(); i++) {
        B[0]->u[i] = -S[0]->u[i];
        B[1]->u[i] = -S[1]->u[i];
        B[2]->u[i] = -S[2]->u[i];
        B[3]->u[i] = -qw;
      }
    }
}

// \lambda_1 =0, \lambda_2 = 0.0, \lambda_3 = 0.0
void Navier_Stokes::Isoflux_SlipWallBC::adjoint_apply( const Scalar t,
                                                       const vField &state,
                                                       const vField &adjoint) {
  LocalSize Nfields = adjoint.size();
  vector<Side*> S(Nfields), B(Nfields),SS(Nfields);
  for (LocalSize n=0; n<state[0]->nbc; ++n)   // loop over field boundaries
    if (state[0]->bc[n]->type == type ) {
      //dVector &nx = state[0]->bc[n]->S->nx();
      //dVector &ny = state[0]->bc[n]->S->ny();
      for (LocalSize i=0; i<Nfields; ++i){
        S[i] = adjoint[i]->bc[n]->S;
        B[i] = adjoint[i]->bc[n]->B;
        SS[i] = state[i]->bc[n]->S;
      }

      assert(SS[0]->qtot() == S[0]->qtot() );
      // Project the State side => Adjoint side
      // do some projection here,two ways to project [gqchen]
      // 1) use the G->G interpolate
      // 2) base on the edge modes

      const LocalSize qtot = S[0]->qtot();
      for (LocalSize i=0; i<qtot; i++) {
        B[0]->u[i] = S[0]->u[i];
        B[3]->u[i] = 0.0;
        B[1]->u[i] = 0.0;
        B[2]->u[i] = 0.0;
      }
    }
}

// \lambda_3_n =0.0
void Navier_Stokes::Isoflux_SlipWallBC::
adjoint_apply_flux( const Scalar t, const vField &state,
                    const vField &adjoint) {
  LocalSize Nfields = adjoint.size();
  vector<Side*> S(Nfields), B(Nfields),SS(Nfields);
  Scalar rho,m,n,E;
  dVector Fvx(Nfields),Fvy(Nfields);

  //Size offset=0;
  for (LocalSize nb=0; nb<state[0]->nbc; ++nb)   // loop over field boundaries
    if (state[0]->bc[nb]->type == type ) {
      dVector &nx = state[0]->bc[nb]->S->nx();
      dVector &ny = state[0]->bc[nb]->S->ny();
      const LocalSize sid = adjoint[0]->bc[nb]->sid;
      //const Size eid = adjoint[0]->bc[nb]->elmt->id;
      for (LocalSize i=0; i<Nfields; ++i) {
        S[i] = adjoint[i]->bc[nb]->S;
        B[i] = adjoint[i]->bc[nb]->B;
        SS[i]= state[i]->bc[nb]->B;
      }

      assert(SS[0]->qtot() == S[0]->qtot() );
      // Project the State side => Adjoint side
      // do some projection here,two ways to project [gqchen]
      // 1) use the G->G interpolate
      // 2) base on the edge modes

      const Ordinal vqtot = adjoint[0]->bc[nb]->elmt->qtot;
      const Ordinal bqtot = S[0]->qtot();

      dVector ru(bqtot);  ru = SS[1]->u;
      dVector rv(bqtot);  rv = SS[2]->u;

      dVector lamv_x[4], lamv_y[4];
      dVector lamb_x[4], lamb_y[4];

      dVector tmp1(bqtot), tmp2(bqtot);

      for(LocalSize i=0; i<Nfields; i++) {
        lamv_x[i].resize(vqtot);
        lamv_y[i].resize(vqtot);
        lamb_x[i].resize(bqtot);
        lamb_y[i].resize(bqtot);
      }
#ifdef REO_JUMP1
#else
      for(LocalSize i=0;i<Nfields;i++){
        adjoint[i]->bc[nb]->elmt->gradient(adjoint[i]->bc[nb]->elmt->u,
                                           lamv_x[i],lamv_y[i]);
        adjoint[i]->bc[nb]->elmt->load_side(lamv_x[i],sid,lamb_x[i]);
        adjoint[i]->bc[nb]->elmt->load_side(lamv_y[i],sid,lamb_y[i]);
      }
#endif

      // Here two constraints:
      //   lam3_n = 0.0
      //   lam3_s = lam3_s(inside)
      tmp2 =0;
      dvvtvm(ny,lamb_x[3],tmp2,tmp2);   // -lam3,x *ny
      dvvtvp(nx,lamb_y[3],tmp2,tmp2);   // lam3,s=-ny*lam3,x+nx*lam3,y

      tmp1 =0; // lam3,n

      lamb_x[3] =0;
      dvvtvm(ny,tmp2,lamb_x[3],lamb_x[3]);
      dvvtvp(nx,tmp1,lamb_x[3],lamb_x[3]); // lam3_x @bc

      lamb_y[3] =0;
      dvvtvp(ny,tmp1,lamb_y[3],lamb_y[3]);
      dvvtvp(nx,tmp2,lamb_y[3],lamb_y[3]); // lam3_y @bc

      for (LocalSize q=0; q<bqtot; q++) {
        rho = SS[0]->u[q];
        m   = SS[1]->u[q];
        n   = SS[2]->u[q];
        E   = SS[3]->u[q];

        Fvx[0] = -(2.0*mu+lambda)*m/(rho*rho)/Re*lamb_x[1][q]
          -n/(rho*rho)*mu/Re*lamb_x[2][q]
          +(-(2.0*mu+lambda)*m*m/(rho*rho*rho)/Re-n*n/(rho*rho*rho)*mu/Re
            +(gamma*(gamma-1.0)*(m*m+n*n)/(rho*rho*rho)/2.0
              -gamma*(gamma-1.0)*(E-(m*m+n*n)/rho/2.0)/(rho*rho))
            *K/Re/Pr/(gamma-1.0))*lamb_x[3][q]-n/(rho*rho)*mu/Re
          *lamb_y[1][q]-lambda/(rho*rho)/Re*m*lamb_y[2][q]
          +(-lambda*n/(rho*rho*rho)/Re*m-m/(rho*rho*rho)*mu/Re*n)*lamb_y[3][q];
        Fvx[1] = (2.0*mu+lambda)/rho/Re*lamb_x[1][q]
          +((2.0*mu+lambda)*m/(rho*rho)/Re
            -gamma*m/(rho*rho)*K/Re/Pr)*lamb_x[3][q]
          +lambda/rho/Re*lamb_y[2][q]+lambda*n/(rho*rho)/Re*lamb_y[3][q];
        Fvx[2] = 1/rho*mu/Re*lamb_x[2][q]
          +(n/(rho*rho)*mu/Re-gamma*n/(rho*rho)*K/Re/Pr)*lamb_x[3][q]
          +1/rho*mu/Re*lamb_y[1][q]+m/(rho*rho)*mu/Re*lamb_y[3][q];
        Fvx[3] = gamma/rho*K/Re/Pr*lamb_x[3][q];

        Fvy[0] = -lambda*n/(rho*rho)/Re*lamb_x[1][q]
          -m/(rho*rho)*mu/Re*lamb_x[2][q]
          +(-lambda*n/(rho*rho*rho)/Re*m-m/(rho*rho*rho)*mu/Re*n)*lamb_x[3][q]
          -m/(rho*rho)*mu/Re*lamb_y[1][q]
          -(2.0*mu+lambda)*n/(rho*rho)/Re*lamb_y[2][q]
          +(-m*m/(rho*rho*rho)*mu/Re-(2.0*mu+lambda)*n*n/(rho*rho*rho)/Re
            +(gamma*(gamma-1.0)*(m*m+n*n)/(rho*rho*rho)/2.0
              -gamma*(gamma-1.0)*(E-(m*m+n*n)/rho/2.0)/(rho*rho))
            *K/Re/Pr/(gamma-1.0))*lamb_y[3][q];
        Fvy[1] = 1/rho*mu/Re*lamb_x[2][q]+n/(rho*rho)*mu/Re*lamb_x[3][q]
          +1/rho*mu/Re*lamb_y[1][q]+(m/(rho*rho)*mu/Re
                                     -gamma*m/(rho*rho)*K/Re/Pr)*lamb_y[3][q];
        Fvy[2] = lambda/rho/Re*lamb_x[1][q]+lambda/(rho*rho)/Re*m*lamb_x[3][q]
          +(2.0*mu+lambda)/rho/Re*lamb_y[2][q]
          +((2.0*mu+lambda)*n/(rho*rho)/Re
            -gamma*n/(rho*rho)*K/Re/Pr)*lamb_y[3][q];
        Fvy[3] = gamma/rho*K/Re/Pr*lamb_y[3][q];

        B[0]->u[q] = -(nx[q]*Fvx[0] + ny[q]*Fvy[0]);
        B[1]->u[q] = -(nx[q]*Fvx[1] + ny[q]*Fvy[1]);
        B[2]->u[q] = -(nx[q]*Fvx[2] + ny[q]*Fvy[2]);
        B[3]->u[q] = -(nx[q]*Fvx[3] + ny[q]*Fvy[3]);
      }
    }
}

/////////////////////////////////////////////////////////////////////////////
//
//                    B O U N D A R Y   C O N T R O L S
//
/////////////////////////////////////////////////////////////////////////////

//===========================================================================
//                        Isothermal Control Wall
//===========================================================================

/// Isothermal boundary control
class Navier_Stokes::Isothermal_ControlBC : public BC, public Ctrl {
  Scalar value;  // default control value
  Scalar Tw;     // constant wall temperature
  Scalar Eref;   // reference stagnation energy per unit volume
                 // (rho_r*T_r)/(gamma*(gamma-1)*Ma_r^2)
  vField *Fphi;  // internal copy for geometry operations [gqchen]
  // Scalar gamma, Pr;
  Scalar Ma, Re, K, mu, lambda;
  // Scalar rho_r, T_r, U_r;
public:
  Isothermal_ControlBC( const string tag, ifstream &in, vField *F,
                        const Scalar gamma_, const Scalar mu_,
                        const Scalar Pr_ ) :
    BC(tag), Fphi(F),
    //gamma(gamma_), Pr(Pr_),
    mu(mu_)
    {
      DGM:: Comm::World->cout()<<"NavierStokes::IsothermalControlBC()"<<endl;
      scan_lb(in);
      if (!(in >> penalty >> Tw >> Eref ))
        error("Navier_Stokes::IsofluxControlWallBC: error reading parms");
      scan_rb(in);
      value  = 0.0;         // zero control is default
      Ma     = 1.0;         // Ma is not explicitly needed
      Re     = 1.0;         // Set so that Re=1/mu
      lambda = -2.0/3.0*mu; // Stokes hypothesis
      K      = mu;          // To match CNS2D normalization
    }

  inline void apply( const Scalar, const vField & ) ;
  inline void apply_flux( const Scalar, const vField & ) ;

  inline void adjoint_apply( const Scalar, const vField &, const vField & ) ;
  inline void adjoint_apply_flux( const Scalar, const vField &,
                                  const vField & ) ;

  inline Ctrl* ctrl() { return this; }
  inline const Ctrl* ctrl() const { return this; }

  // Ctrl methods
  void initialize() { Ctrl::initialize(); data=value; }
  inline Scalar inner_product(const dVector &) const;
  inline void set_direction( dVector & );
  inline void objective_function_gradient( const vField &, const vField &,
      const Scalar time, dVector & ) const;
  inline void plot( const vField &, const Size, const dVector & ,
                    const Ordinal, const Ordinal, const Ordinal,
                    const Ordinal) const;
};

void Navier_Stokes::Isothermal_ControlBC::apply( const Scalar t,
                                                 const vField &F ) {
  vector<Side*> S(F.size()), B(F.size());
  if (data.size()==0) {
    // WARNING:: this assumes that the uncontrolled flow is no-slip
    for (LocalSize n=0; n<F[0]->nbc; ++n)   // loop over field boundaries
      if (F[0]->bc[n]->type == type ) {
        //dVector &nx = F[0]->bc[n]->S->nx();
        //dVector &ny = F[0]->bc[n]->S->ny();
        for (vField::size_type i=0; i<F.size(); ++i){
          S[i] = F[i]->bc[n]->S;
          B[i] = F[i]->bc[n]->B;
        }
#ifdef NO_CONTROL_BC
        for (LocalSize i=0; i<S[0]->qtot(); ++i) {
          B[0]->u[i] = S[0]->u[i];
          B[1]->u[i] = 0.0;
          B[2]->u[i] = 0.0;
          B[3]->u[i] = (Eref-0.5)*B[0]->u[i]*Tw
            + 0.5*(B[1]->u[i]*B[1]->u[i] + B[2]->u[i]*B[2]->u[i])/B[0]->u[i];
        }
#else
        for (LocalSize i=0; i<S[0]->qtot(); i++) {
          B[0]->u[i] = S[0]->u[i];
          B[1]->u[i] = 0.0;
          B[2]->u[i] = 0.0;
          B[3]->u[i] = (Eref-0.5)*B[0]->u[i]*Tw;
        }
#endif
      }
  } else {
    LocalSize offset=0;
    dVector g;
    for (LocalSize n=0; n<F[0]->nbc; ++n)   // loop over field boundaries
      if (F[0]->bc[n]->type == type ) {
        dVector &nx = F[0]->bc[n]->S->nx();
        dVector &ny = F[0]->bc[n]->S->ny();
        for (vField::size_type i=0; i<F.size(); ++i){
          S[i] = F[i]->bc[n]->S;
          B[i] = F[i]->bc[n]->B;
        }
        g.alias( *(const_cast<dVector*>(&data)), offset, S[0]->qtot());

        assert(g.size() == S[0]->qtot() );
        // do projection here, two ways to project [gqchen]
        // 1) use the G->G interpolate
        // 2) base on the edge modes

        for (LocalSize i=0; i<S[0]->qtot(); i++) {
          B[0]->u[i] = S[0]->u[i];
          B[1]->u[i] = B[0]->u[i]*g[i]*nx[i];
          B[2]->u[i] = B[0]->u[i]*g[i]*ny[i];
          B[3]->u[i] = (Eref-0.5)*B[0]->u[i]*Tw +
            0.5*( B[1]->u[i]*B[1]->u[i] + B[2]->u[i]*B[2]->u[i] ) / B[0]->u[i];
        }
        offset += S[0]->qtot();
      }
  }
}

void Navier_Stokes::Isothermal_ControlBC::apply_flux( const Scalar t,
                                                      const vField &F ) {
  vector<Side*> S(F.size()), B(F.size());
  for (LocalSize n=0; n<F[0]->nbc; ++n)   // loop over field boundaries
    if (F[0]->bc[n]->type == type ) {
      //dVector &nx = F[0]->bc[n]->S->nx();
      //dVector &ny = F[0]->bc[n]->S->ny();
      for (vField::size_type i=0; i<F.size(); ++i) {
        S[i] = F[i]->bc[n]->S;
        B[i] = F[i]->bc[n]->B;
      }
      for (LocalSize i=0; i<S[0]->qtot(); i++) {
        B[0]->u[i] = -S[0]->u[i];
        B[1]->u[i] = -S[1]->u[i];
        B[2]->u[i] = -S[2]->u[i];
        B[3]->u[i] = -S[3]->u[i];
      }
    }
}

// \lambda_0 =0, \lambda_1 =0,\lambda_2 =0,\lambda_3 =0,
void Navier_Stokes::Isothermal_ControlBC::adjoint_apply
( const Scalar t, const vField &state, const vField &adjoint) {

  LocalSize Nfields = adjoint.size();
  vector<Side*> S(Nfields), B(Nfields),SS(Nfields);

  //Size offset=0;
  for (LocalSize n=0; n<state[0]->nbc; ++n)   // loop over field boundaries
    if (state[0]->bc[n]->type == type ){
      //dVector &nx = state[0]->bc[n]->S->nx();
      //dVector &ny = state[0]->bc[n]->S->ny();

      for (LocalSize i=0; i<Nfields; ++i){
        S[i] = adjoint[i]->bc[n]->S;
        B[i] = adjoint[i]->bc[n]->B;
        SS[i]= state[i]->bc[n]->B;
      }

      assert(SS[0]->qtot() == S[0]->qtot() );
      // Project the State side => Adjoint side
      // do some projection here,two ways to project [gqchen]
      // 1) use the G->G interpolate
      // 2) base on the edge modes

      const LocalSize qtot = S[0]->qtot();
      for (LocalSize i=0; i<qtot; i++) {
        B[0]->u[i] = 0.0;
        B[1]->u[i] = 0.0;
        B[2]->u[i] = 0.0;
        B[3]->u[i] = 0.0;
      }
    }
}


void Navier_Stokes::Isothermal_ControlBC::adjoint_apply_flux
( const Scalar t, const vField &state, const vField &adjoint ) {
  vector<Side*> S(adjoint.size()), B(adjoint.size());
  for (LocalSize n=0; n<adjoint[0]->nbc; ++n)   // loop over field boundaries
    if (adjoint[0]->bc[n]->type == type ) {
      //dVector &nx = adjoint[0]->bc[n]->S->nx();
      //dVector &ny = adjoint[0]->bc[n]->S->ny();
      for (vField::size_type i=0; i<adjoint.size(); ++i){
        S[i] = adjoint[i]->bc[n]->S;
        B[i] = adjoint[i]->bc[n]->B;
      }
      for (LocalSize i=0; i<S[0]->qtot(); i++) {
        B[0]->u[i] = -S[0]->u[i];
        B[1]->u[i] = -S[1]->u[i];
        B[2]->u[i] = -S[2]->u[i];
        B[3]->u[i] = -S[3]->u[i];
      }
    }
}

Scalar Navier_Stokes::Isothermal_ControlBC::inner_product( const dVector &Y )
  const {
  Ordinal qtot,sid;
  dVector ta,tb,tab;
  LocalSize offset=0;
  Scalar sum=0.0;
  for (LocalSize n=0; n<(*Fphi)[0]->nbc; ++n)   // loop over field boundaries
    if ((*Fphi)[0]->bc[n]->type == type ) {
      qtot = (*Fphi)[0]->bc[n]->S->qtot();
      sid = (*Fphi)[0]->bc[n]->sid;
      ta.alias(data,offset,qtot);
      tb.alias(Y,offset,qtot);
      tab.resize(qtot);
      dvmul(ta, tb, tab);
      offset += qtot;
      sum +=(*Fphi)[0]->bc[n]->elmt->compute_side_integral(tab,sid);
    }
  return sum;
}


void  Navier_Stokes::Isothermal_ControlBC::set_direction( dVector &out ) {
  if (data.size()==0) return;
  assert( data_size() == out.size() );
  out = data = 1.0;
}

// WARNING: does NOT support the general curvature!! [gqchen]
void Navier_Stokes::Isothermal_ControlBC::objective_function_gradient(
    const vField &state, const vField &adjoint, const Scalar time,
    dVector &grad ) const
{
  LocalSize Nfields = adjoint.size();
  vector<Side*> S(Nfields), B(Nfields),SS(Nfields);
  Scalar r,ru,rv;
  //Scalar Vn,Vs,Lambn,Lambs,lamb4_s,lamb4_n,Lambs_s,Lambn_n;
  Scalar Vn,lamb4_n,Lambn_n;

  LocalSize offset=0;
  dVector dv, gv;

  dVector lamb[4],stab[4];
  dVector lamb_x[4],lamb_y[4];

  for (LocalSize nb=0; nb<state[0]->nbc; ++nb)   // loop over field boundaries
    if (state[0]->bc[nb]->type == type ) {

      dVector &nx = state[0]->bc[nb]->S->nx();
      dVector &ny = state[0]->bc[nb]->S->ny();

      const LocalSize sid = adjoint[0]->bc[nb]->sid;

      for (LocalSize i=0; i<Nfields; ++i) {
        S[i] = adjoint[i]->bc[nb]->S;
        B[i] = adjoint[i]->bc[nb]->B;
        SS[i]= state[i]->bc[nb]->B;
      }

      assert(SS[0]->qtot() == S[0]->qtot() );
      // Project the State side => Adjoint side
      // do some projection here,two ways to project [gqchen]
      // 1) use the G->G interpolate
      // 2) base on the edge modes

      const Ordinal vqtot = adjoint[0]->bc[nb]->elmt->qtot;
      const Ordinal bqtot = S[0]->qtot();

      dv.alias( *(const_cast<dVector*>(&data)), offset,
                state[0]->bc[nb]->S->qtot() );
      gv.alias( *(const_cast<dVector*>(&grad)), offset,
                state[0]->bc[nb]->S->qtot() );

      dVector tmpx(vqtot),tmpy(vqtot);

      for(LocalSize i=0;i<Nfields;i++) {
        lamb_x[i].resize(bqtot);
        lamb_y[i].resize(bqtot);
        lamb[i].resize(bqtot);
        stab[i].resize(bqtot);
      }

      for(LocalSize i=0;i<Nfields;i++)
        state[i]->bc[nb]->elmt->load_side( state[i]->bc[nb]->elmt->u,sid,
                                           stab[i]);

      // get the adjoint and its gradient @ control boundary
      for(LocalSize i=0;i<Nfields;i++){
        adjoint[i]->bc[nb]->elmt->load_side( adjoint[i]->bc[nb]->elmt->u,sid,
                                             lamb[i]);
        adjoint[i]->bc[nb]->elmt->gradient(adjoint[i]->bc[nb]->elmt->u,
                                           tmpx,tmpy);
        adjoint[i]->bc[nb]->elmt->load_side(tmpx,sid,lamb_x[i]);
        adjoint[i]->bc[nb]->elmt->load_side(tmpy,sid,lamb_y[i]);
      }

      for(LocalSize q=0;q<bqtot;q++) {
        r = stab[0][q];
        ru = stab[1][q];
        rv = stab[2][q];
        //E = stab[3][q];

        //Vs = (ru*(-ny[q])+rv*nx[q])/r;
        // Here Vn should be g [gqchen]
        Vn = (ru*nx[q]+rv*ny[q])/r;

        lamb4_n = lamb_x[3][q]*nx[q] + lamb_y[3][q]*ny[q];

        // nomal vector in the cylinder (nx,ny)= (-x,-y)
        // nx_x =-1,nx_y=0,ny_x=0,ny_y=-1
        // curvature of circle is 1/R = 2.0
        Lambn_n = lamb_x[1][q]*nx[q]*nx[q] + lamb_x[2][q]*nx[q]*ny[q]
          +lamb_y[1][q]*nx[q]*ny[q] + lamb_y[2][q]*ny[q]*ny[q]
          -nx[q]*lamb[1][q] - ny[q]*lamb[2][q];

        // Gradient
        gv[q] = penalty*dv[q]
          + 1.0/Re*(lambda+2*mu)*(Lambn_n+Vn*lamb4_n);
      }
      offset+=bqtot;
    }
}

void Navier_Stokes::Isothermal_ControlBC::plot( const vField &state,
                                                const Size goffset,
                                                const dVector &Gphi,
                                                const Ordinal npredict,
                                                const Ordinal ntout,
                                                const Ordinal nsstep,
                                                const Ordinal riter) const {
  const Ordinal offset = numeric_cast<Ordinal>(goffset);
  dVector dv;
  char tmp[30];
  string fname;
  Ordinal np;
  for(Ordinal i=0;i<=npredict;i+=ntout){ //4 is nsstep for RK4
    fname="ns_isothermal_control";
    sprintf(tmp,"%lld_%lld.dat",(long long)i,(long long)riter);
    fname = fname + tmp;
    FILE *opt_stat = fopen(fname.c_str(),"w");
    fprintf(opt_stat, "Navier_Stokes Isothermal Control  @ %lld step\n",
            (long long)i);
    dv.alias( *(const_cast<dVector*>(&Gphi)),
              offset+(nsstep*i)*data_size(), data_size() );
    np=0;
    for (LocalSize n=0; n<state[0]->nbc; n++) {  // loop over state boundaries
      if (state[0]->bc[n]->type == type ) {

        const LocalSize sid = state[0]->bc[n]->sid;
        const LocalSize qtot = state[0]->bc[n]->S->qtot();
        Point* pside = new Point[state[0]->bc[n]->elmt->side[sid]->qtot()];
        state[0]->bc[n]->elmt->get_side_coordinates(sid,pside);
        for(LocalSize q=0;q<qtot;q++)
          fprintf(opt_stat,"%11.4e %11.4e %11.4e\n",pside[q].x,
                  pside[q].y,dv[np++]);
        delete[] pside;
      }
    }
    fclose(opt_stat);
  }
}

//===========================================================================
//                     Constant Heat Flux Control Wall
//===========================================================================

/// Constant heat flux boundary control
class Navier_Stokes::Isoflux_ControlBC : public BC, public Ctrl {
  Scalar value;  // default control
  Scalar qw;     // constant heat flux
  vField *Fphi;  // internal copy for the geometry operation [gqchen]
  Scalar gamma, Ma, Re, Pr, K, mu, lambda;
  // Scalar rho_r, T_r, U_r;
  Scalar curv;   // curvature of surface, assumed constant for now
public:
  // In the future, we should just pass in a Fluid object
  Isoflux_ControlBC( const string tag, ifstream &in, vField *F,
                     const Scalar gamma_, const Scalar mu_,
                     const Scalar Pr_ ) :
    BC(tag), Fphi(F), gamma(gamma_), Pr(Pr_), mu(mu_)
    {
      DGM::Comm::World->cout()<<"NavierStokes::IsofluxControlBC()"<<endl;
      scan_lb(in);
#ifndef DGM_USE_TIME_REG
      if (!(in >> penalty >> qw >> curv))
        error("Navier_Stokes::IsofluxControlWallBC: error reading parms");
#else
      if (!(in >> penalty >> penalty_t >> qw >> curv))
        error("Navier_Stokes::IsofluxControlWallBC: error reading parms");
#endif
      scan_rb(in);
      value  = 0.0;         // zero control is default
      Ma     = 1.0;         // Ma is not explicitly needed
      Re     = 1.0;         // Set so that Re=1/mu
      lambda = -2.0/3.0*mu; // Stokes hypothesis
      K      = mu;          // To match CNS2D normalization
    }

  inline void apply( const Scalar, const vField & ) ;
  inline void apply_flux( const Scalar, const vField & ) ;

  inline void adjoint_apply( const Scalar, const vField &, const vField & ) ;
  inline void adjoint_apply_flux( const Scalar, const vField &,
                                  const vField & ) ;

  inline Ctrl* ctrl() { return this; }
  inline const Ctrl* ctrl() const { return this; }

  // Ctrl methods
  void initialize() { Ctrl::initialize(); data=value; }
  inline Scalar inner_product(const dVector &) const;
  inline void set_direction( dVector & );
  inline void objective_function_gradient( const vField &, const vField &,
      const Scalar time, dVector & ) const;
  inline void plot( const vField &, const Size, const dVector & ,
                    const Ordinal, const Ordinal, const Ordinal,
                    const Ordinal) const;

  void output() const {
    vField &F = *Fphi;
    vector<Side*> S(Fphi->size());
    LocalSize offset=0;
    dVector g;
    for (LocalSize n=0; n<(*Fphi)[0]->nbc; ++n)   // loop over field boundaries
      if ((*Fphi)[0]->bc[n]->type == type ) {
        for (vField::size_type i=0; i<Fphi->size(); ++i) S[i] = (*Fphi)[i]->bc[n]->S;
        g.alias( *(const_cast<dVector*>(&data)), offset, S[0]->qtot());
#ifdef DGM_PARALLEL
        if (DGM::Comm::World->MyPID()==1) {
          ofstream temp("node1.out", ios::app);
          // write out using the global element id
          temp<<"Element "
              << F[0]->partition->eid(F[0]->bc[n]->eid)
              <<" Side " <<F[0]->bc[n]->sid << endl
              << g << endl;
        }
        if (DGM::Comm::World->MyPID()==0) {
          ofstream temp("node0.out", ios::app);
          // write out using the global element id
          temp<<"Element "
              << F[0]->partition->eid(F[0]->bc[n]->eid)
              <<" Side " <<F[0]->bc[n]->sid << endl
              << g << endl;
        }
#else
        DGM::Comm::World->cout()<<"Element "
                                << F[0]->bc[n]->eid
                                <<" Side " <<F[0]->bc[n]->sid << endl
                                << g << endl;
#endif
        offset += S[0]->qtot();
      }
  }
};

void Navier_Stokes::Isoflux_ControlBC::apply( const Scalar t,
                                              const vField &F ) {
  vector<Side*> S(F.size()), B(F.size());
  if (data.size()==0) {
    // WARNING:: this assumes that the uncontrolled flow is no-slip
    for (LocalSize n=0; n<F[0]->nbc; ++n)   // loop over field boundaries
      if (F[0]->bc[n]->type == type ) {
        //dVector &nx = F[0]->bc[n]->S->nx();
        //dVector &ny = F[0]->bc[n]->S->ny();
        for (vField::size_type i=0; i<F.size(); ++i){
          S[i] = F[i]->bc[n]->S;
          B[i] = F[i]->bc[n]->B;
        }
#ifdef NO_CONTROL_BC
        for (LocalSize i=0; i<S[0]->qtot(); ++i) {
          B[0]->u[i] = S[0]->u[i];
          B[1]->u[i] = 0.0;
          B[2]->u[i] = 0.0;
          B[3]->u[i] = S[3]->u[i]
            - 0.5*(S[1]->u[i]*S[1]->u[i] + S[2]->u[i]*S[2]->u[i])/S[0]->u[i]
            + 0.5*(B[1]->u[i]*B[1]->u[i] + B[2]->u[i]*B[2]->u[i])/B[0]->u[i];
        }
#else
        for (LocalSize i=0; i<S[0]->qtot(); i++) {
          B[0]->u[i] = S[0]->u[i];
          B[1]->u[i] = 0.0;
          B[2]->u[i] = 0.0;
          B[3]->u[i] = S[3]->u[i]
            - 0.5*(S[1]->u[i]*S[1]->u[i] + S[2]->u[i]*S[2]->u[i])/S[0]->u[i]
            + 0.5*(B[1]->u[i]*B[1]->u[i] + B[2]->u[i]*B[2]->u[i])/B[0]->u[i];
        }
#endif
      }
  } else {
    LocalSize offset=0;
    dVector g;
    for (LocalSize n=0; n<F[0]->nbc; ++n)   // loop over field boundaries
      if (F[0]->bc[n]->type == type ) {
        dVector &nx = F[0]->bc[n]->S->nx();
        dVector &ny = F[0]->bc[n]->S->ny();
        for (vField::size_type i=0; i<F.size(); ++i) {
          S[i] = F[i]->bc[n]->S;
          B[i] = F[i]->bc[n]->B;
        }
        g.alias( *(const_cast<dVector*>(&data)), offset, S[0]->qtot());

// dVector curv( F[0]->bc[n]->S->qtot());
// F[0]->bc[n]->elmt->get_side_curvature(F[0]->bc[n]->sid,curv);
// for(int i=0;i< F[0]->bc[n]->S->qtot();i++)
//   cout<<"i= "<<i<<" curv="<<curv[i];
// cout<<endl;
// DGM::Comm::World::exit(DGM::FAILURE);

        assert(g.size() == S[0]->qtot() );
        // do some projection here,two ways to project [gqchen]
        // 1) use the G->G interpolate
        // 2) base on the edge modes

        for (LocalSize i=0; i<S[0]->qtot(); i++) {
          B[0]->u[i] = S[0]->u[i];
          B[1]->u[i] = B[0]->u[i]*g[i]*nx[i];
          B[2]->u[i] = B[0]->u[i]*g[i]*ny[i];
          B[3]->u[i] = S[3]->u[i]
            - 0.5*(S[1]->u[i]*S[1]->u[i] + S[2]->u[i]*S[2]->u[i])/S[0]->u[i]
            + 0.5*( B[1]->u[i]*B[1]->u[i]+ B[2]->u[i]*B[2]->u[i])/B[0]->u[i];
        }
        offset += S[0]->qtot();
      }
  }
}

void Navier_Stokes::Isoflux_ControlBC::apply_flux( const Scalar t,
                                                   const vField &F ) {
  vector<Side*> S(F.size()), B(F.size());
  for (LocalSize n=0; n<F[0]->nbc; ++n)   // loop over field boundaries
    if (F[0]->bc[n]->type == type ) {
      //dVector &nx = F[0]->bc[n]->S->nx();
      //dVector &ny = F[0]->bc[n]->S->ny();
      for (vField::size_type i=0; i<F.size(); ++i){
        S[i] = F[i]->bc[n]->S;
        B[i] = F[i]->bc[n]->B;
      }
      for (LocalSize i=0; i<S[0]->qtot(); i++) {
        B[0]->u[i] = -S[0]->u[i];
        B[1]->u[i] = -S[1]->u[i];
        B[2]->u[i] = -S[2]->u[i];
        B[3]->u[i] = -qw;
      }
    }
}

void Navier_Stokes::Isoflux_ControlBC::adjoint_apply( const Scalar t,
                                                      const vField &state,
                                                      const vField &adjoint) {
  LocalSize Nfields = adjoint.size();
  vector<Side*> S(Nfields), B(Nfields),SS(Nfields);

  Scalar Vn,Vs,T;

  //Size offset=0;
  for (LocalSize n=0; n<state[0]->nbc; ++n)   // loop over field boundaries
    if (state[0]->bc[n]->type == type ) {
      dVector &nx = state[0]->bc[n]->S->nx();
      dVector &ny = state[0]->bc[n]->S->ny();

      for (LocalSize i=0; i<Nfields; ++i) {
        S[i] = adjoint[i]->bc[n]->S;
        B[i] = adjoint[i]->bc[n]->B;
        SS[i]= state[i]->bc[n]->B;
      }

      assert(SS[0]->qtot() == S[0]->qtot() );
      // Project the State side => Adjoint side
      // do some projection here,two ways to project [gqchen]
      // 1) use the G->G interpolate
      // 2) base on the edge modes

      const LocalSize qtot = S[0]->qtot();
      for (LocalSize i=0; i<qtot; i++) {
        // At the ControlBC, Vs=0, Vn=g (control),
        // do I really need to compute it??
        Vn = ( SS[1]->u[i]*nx[i] + SS[2]->u[i]*ny[i])/SS[0]->u[i];
        Vs = (-SS[1]->u[i]*ny[i] + SS[2]->u[i]*nx[i])/SS[0]->u[i];

        T = gamma*(gamma-1.0)/SS[0]->u[i]
          *(SS[3]->u[i]-0.5*SS[0]->u[i]*(Vn*Vn+Vs*Vs) );

        B[0]->u[i] = -S[3]->u[i]*(T/(gamma*(gamma-1.0))
                                  -0.5*(Vn*Vn+Vs*Vs));
        B[1]->u[i] = -Vn*S[3]->u[i]*nx[i] + Vs*S[3]->u[i]*ny[i];
        B[2]->u[i] = -Vn*S[3]->u[i]*ny[i] - Vs*S[3]->u[i]*nx[i];
        B[3]->u[i] = S[3]->u[i];
      }
    }
}


void Navier_Stokes::Isoflux_ControlBC::adjoint_apply_flux
(const Scalar t, const vField &state, const vField &adjoint) {

  LocalSize Nfields = adjoint.size();
  vector<Side*> S(Nfields), B(Nfields),SS(Nfields);
  Scalar rho,m,n,E;
  dVector Fvx(Nfields),Fvy(Nfields);

  //Size offset=0;
  for (LocalSize nb=0; nb<state[0]->nbc; ++nb)   // loop over field boundaries
    if (state[0]->bc[nb]->type == type ) {
      dVector &nx = state[0]->bc[nb]->S->nx();
      dVector &ny = state[0]->bc[nb]->S->ny();
      const LocalSize sid = adjoint[0]->bc[nb]->sid;
      //const LocalSize eid = adjoint[0]->bc[nb]->elmt->id;
      for (LocalSize i=0; i<Nfields; ++i) {
        S[i] = adjoint[i]->bc[nb]->S;
        B[i] = adjoint[i]->bc[nb]->B;
        SS[i]= state[i]->bc[nb]->B;
      }

      assert(SS[0]->qtot() == S[0]->qtot() );
      // Project the State side => Adjoint side
      // do some projection here,two ways to project [gqchen]
      // 1) use the G->G interpolate
      // 2) base on the edge modes

      const LocalSize vqtot = adjoint[0]->bc[nb]->elmt->qtot;
      const LocalSize bqtot = S[0]->qtot();

      dVector ru(bqtot);  ru = SS[1]->u;
      dVector rv(bqtot);  rv = SS[2]->u;
      dVector lamv_x[4], lamv_y[4];
      dVector lamb_x[4], lamb_y[4];
      dVector lamb4(bqtot), tmp1(bqtot), tmp2(bqtot);

      for(LocalSize i=0; i<Nfields; i++) {
        lamv_x[i].resize(vqtot);
        lamv_y[i].resize(vqtot);
        lamb_x[i].resize(bqtot);
        lamb_y[i].resize(bqtot);
      }
#ifndef REO_JUMP1
      for(LocalSize i=0;i<Nfields;i++) {
        adjoint[i]->bc[nb]->elmt->gradient(adjoint[i]->bc[nb]->elmt->u,
                                           lamv_x[i],lamv_y[i]);
        adjoint[i]->bc[nb]->elmt->load_side(lamv_x[i],sid,lamb_x[i]);
        adjoint[i]->bc[nb]->elmt->load_side(lamv_y[i],sid,lamb_y[i]);
      }
#endif
      adjoint[3]->bc[nb]->elmt->load_side(adjoint[3]->bc[nb]->elmt->u,
                                          sid,lamb4);

      // Here two constraints:
      //      lam4_n = -rho*Vn*lam4*(Pr*Re/(gamma*K))
      //      lam4_s = lam4_s(inside)
      tmp2 =0;
      dvvtvm(ny,lamb_x[3],tmp2,tmp2);      // -lam4,x *ny
      dvvtvp(nx,lamb_y[3],tmp2,tmp2);      // lam4,s=-ny*lam4,x+nx*lam4,y

      tmp1 =0;
      dvmul(nx,ru);                        // ru*nx
      dvmul(ny,rv);                        // rv*ny
      dvadd(ru,rv,tmp1);                   // rVn
      dvmul(lamb4,tmp1);                   // rVn*lam4
      scale(-Pr*Re/(gamma*K),tmp1);        // lam4,n

      lamb_x[3] =0;
      dvvtvm(ny,tmp2,lamb_x[3],lamb_x[3]);
      dvvtvp(nx,tmp1,lamb_x[3],lamb_x[3]); // lam4_x @bc

      lamb_y[3] =0;
      dvvtvp(ny,tmp1,lamb_y[3],lamb_y[3]);
      dvvtvp(nx,tmp2,lamb_y[3],lamb_y[3]); // lam4_y @bc

      for (LocalSize q=0; q<bqtot; q++) {
        rho = SS[0]->u[q];
        m   = SS[1]->u[q];
        n   = SS[2]->u[q];
        E   = SS[3]->u[q];

        Fvx[0] = -(2.0*mu+lambda)*m/(rho*rho)/Re*lamb_x[1][q]
          -n/(rho*rho)*mu/Re*lamb_x[2][q]
          +(-(2.0*mu+lambda)*m*m/(rho*rho*rho)/Re-n*n/(rho*rho*rho)*mu/Re
            +(gamma*(gamma-1.0)*(m*m+n*n)/(rho*rho*rho)/2.0
              -gamma*(gamma-1.0)*(E-(m*m+n*n)/rho/2.0)/(rho*rho))
            *K/Re/Pr/(gamma-1.0))*lamb_x[3][q]-n/(rho*rho)*mu/Re
          *lamb_y[1][q]-lambda/(rho*rho)/Re*m*lamb_y[2][q]
          +(-lambda*n/(rho*rho*rho)/Re*m-m/(rho*rho*rho)*mu/Re*n)*lamb_y[3][q];
        Fvx[1] = (2.0*mu+lambda)/rho/Re*lamb_x[1][q]
          +((2.0*mu+lambda)*m/(rho*rho)/Re
            -gamma*m/(rho*rho)*K/Re/Pr)*lamb_x[3][q]
          +lambda/rho/Re*lamb_y[2][q]+lambda*n/(rho*rho)/Re*lamb_y[3][q];
        Fvx[2] = 1/rho*mu/Re*lamb_x[2][q]
          +(n/(rho*rho)*mu/Re-gamma*n/(rho*rho)*K/Re/Pr)*lamb_x[3][q]
          +1/rho*mu/Re*lamb_y[1][q]+m/(rho*rho)*mu/Re*lamb_y[3][q];
        Fvx[3] = gamma/rho*K/Re/Pr*lamb_x[3][q];

        Fvy[0] = -lambda*n/(rho*rho)/Re*lamb_x[1][q]
          -m/(rho*rho)*mu/Re*lamb_x[2][q]
          +(-lambda*n/(rho*rho*rho)/Re*m-m/(rho*rho*rho)*mu/Re*n)*lamb_x[3][q]
          -m/(rho*rho)*mu/Re*lamb_y[1][q]
          -(2.0*mu+lambda)*n/(rho*rho)/Re*lamb_y[2][q]
          +(-m*m/(rho*rho*rho)*mu/Re-(2.0*mu+lambda)*n*n/(rho*rho*rho)/Re
            +(gamma*(gamma-1.0)*(m*m+n*n)/(rho*rho*rho)/2.0
              -gamma*(gamma-1.0)*(E-(m*m+n*n)/rho/2.0)/(rho*rho))
            *K/Re/Pr/(gamma-1.0))*lamb_y[3][q];
        Fvy[1] = 1/rho*mu/Re*lamb_x[2][q]+n/(rho*rho)*mu/Re*lamb_x[3][q]
          +1/rho*mu/Re*lamb_y[1][q]+(m/(rho*rho)*mu/Re
                                     -gamma*m/(rho*rho)*K/Re/Pr)*lamb_y[3][q];
        Fvy[2] = lambda/rho/Re*lamb_x[1][q]+lambda/(rho*rho)/Re*m*lamb_x[3][q]
          +(2.0*mu+lambda)/rho/Re*lamb_y[2][q]
          +((2.0*mu+lambda)*n/(rho*rho)/Re
            -gamma*n/(rho*rho)*K/Re/Pr)*lamb_y[3][q];
        Fvy[3] = gamma/rho*K/Re/Pr*lamb_y[3][q];

        B[0]->u[q] = -(nx[q]*Fvx[0] + ny[q]*Fvy[0]);
        B[1]->u[q] = -(nx[q]*Fvx[1] + ny[q]*Fvy[1]);
        B[2]->u[q] = -(nx[q]*Fvx[2] + ny[q]*Fvy[2]);
        B[3]->u[q] = -(nx[q]*Fvx[3] + ny[q]*Fvy[3]);
      }
    }
}

// I have to get a local copy of State vField to compute L2 norm[gqchen]
Scalar Navier_Stokes::Isoflux_ControlBC::inner_product( const dVector &Y )
  const {
  LocalSize qtot,sid;
  dVector ta,tb,tab;
  LocalSize offset=0;
  Scalar sum=0.0;
  for (LocalSize n=0; n<(*Fphi)[0]->nbc; ++n)   // loop over field boundaries
    if ((*Fphi)[0]->bc[n]->type == type ){
      qtot = (*Fphi)[0]->bc[n]->S->qtot();
      sid = (*Fphi)[0]->bc[n]->sid;
      ta.alias(data,offset,qtot);
      tb.alias(Y,offset,qtot);
      tab.resize(qtot);
      dvmul(ta, tb, tab);
      offset += qtot;
      sum +=(*Fphi)[0]->bc[n]->elmt->compute_side_integral(tab,sid);
    }
  return sum;
}


void  Navier_Stokes::Isoflux_ControlBC::set_direction( dVector &out ) {
  if (data.size()==0) return;
  assert( data_size() == out.size() );
  out = data = 1.0;
}

// WARNING: does NOT support general curvature!! [gqchen]
void Navier_Stokes::Isoflux_ControlBC::objective_function_gradient(
    const vField &state, const vField &adjoint, const Scalar time,
    dVector &grad ) const
{
  LocalSize Nfields = adjoint.size();
  vector<Side*> S(Nfields), B(Nfields),SS(Nfields);
  Scalar r,ru,rv,E,p;
  Scalar u_x,u_y,v_x,v_y;
  Scalar tau11,tau12,tau22,tau_nn;
  Scalar Vn,Vs, Lambn,Lambs,lamb4_s,lamb4_n,Lambs_s,Lambn_n;

  LocalSize offset=0;
  dVector dv, gv;
  dVector lamb[4],stab[4];       // boundary adjoint/state vector
  dVector lamb_x[4],lamb_y[4];   // boundary adjoint_x/state_x vector
  dVector  stab_x[4],stab_y[4];  // boundary adjoint_y/state_y vector
  for (LocalSize nb=0; nb<state[0]->nbc; ++nb)   // loop over field boundaries
    if (state[0]->bc[nb]->type == type ) {

      dVector &nx = state[0]->bc[nb]->S->nx();
      dVector &ny = state[0]->bc[nb]->S->ny();

      LocalSize sid = adjoint[0]->bc[nb]->sid;

      for (LocalSize i=0; i<Nfields; ++i) {
        S[i] = adjoint[i]->bc[nb]->S;
        B[i] = adjoint[i]->bc[nb]->B;
        SS[i]= state[i]->bc[nb]->B;
      }

      assert(SS[0]->qtot() == S[0]->qtot() );
      // Project the State side => Adjoint side
      // do some projection here,two ways to project [gqchen]
      // 1) use the G->G interpolate
      // 2) base on the edge modes

      // Number of quadrature points in the Element related with Control B.C.
      LocalSize vqtot = adjoint[0]->bc[nb]->elmt->qtot;
      // Number of quadrature points along the Control boundary
      LocalSize bqtot = S[0]->qtot();

      dv.alias( *(const_cast<dVector*>(&data)), offset,
                state[0]->bc[nb]->S->qtot() );
      gv.alias( *(const_cast<dVector*>(&grad)), offset,
                state[0]->bc[nb]->S->qtot() );

      dVector tmpx(vqtot), tmpy(vqtot);

      for(LocalSize i=0;i<Nfields;i++) {
        lamb_x[i].resize(bqtot);
        lamb_y[i].resize(bqtot);
        stab_x[i].resize(bqtot);
        stab_y[i].resize(bqtot);
        lamb[i].resize(bqtot);
        stab[i].resize(bqtot);
      }

      // get the state and its gradient @ control boundary
      for(LocalSize i=0;i<Nfields;i++) {
        state[i]->bc[nb]->elmt->load_side( state[i]->bc[nb]->elmt->u,sid,
                                           stab[i]);
        state[i]->bc[nb]->elmt->gradient(state[i]->bc[nb]->elmt->u,
                                         tmpx,tmpy);
        state[i]->bc[nb]->elmt->load_side(tmpx,sid,stab_x[i]);
        state[i]->bc[nb]->elmt->load_side(tmpy,sid,stab_y[i]);
      }

      // get the adjoint and its gradient @ control boundary
      for(LocalSize i=0;i<Nfields;i++){
        adjoint[i]->bc[nb]->elmt->load_side( adjoint[i]->bc[nb]->elmt->u,sid,
                                             lamb[i]);
        adjoint[i]->bc[nb]->elmt->gradient(adjoint[i]->bc[nb]->elmt->u,
                                           tmpx,tmpy);
        adjoint[i]->bc[nb]->elmt->load_side(tmpx,sid,lamb_x[i]);
        adjoint[i]->bc[nb]->elmt->load_side(tmpy,sid,lamb_y[i]);
      }

      for(LocalSize q=0; q<bqtot; q++) {
        r = stab[0][q];
        ru = stab[1][q];
        rv = stab[2][q];
        E = stab[3][q];

        Vs = (ru*(-ny[q])+rv*nx[q])/r;    // tangential velocity
        // Here Vn should be g [gqchen]
        Vn = (ru*nx[q]+rv*ny[q])/r;       // normal velocity
        p  = (gamma-1.0)*(E - 0.5*(ru*ru+rv*rv)/r); //pressure

        // D()/D(n) = ()_{,x}*n1 + ()_{,y}*n2
        // D()/D(s) = -()_{,x}*n2 + ()_{,y}*n1

        // \lambda_n = \lambda_1*n1 + \lambda_2*n2
        Lambn = lamb[1][q]*nx[q] + lamb[2][q]*ny[q];
        // \lambda_s = - \lambda_1*n2 + \lambda_2*n1
        Lambs = -lamb[1][q]*ny[q] + lamb[2][q]*nx[q];
        // D(\lambda_4)/D(s)
        lamb4_s = -lamb_x[3][q]*ny[q] + lamb_y[3][q]*nx[q];
        // D(\lambda_4)/D(n)
        lamb4_n = lamb_x[3][q]*nx[q] + lamb_y[3][q]*ny[q];

        // Calculate the shear stress
        u_x = stab_x[1][q]/r -ru*stab_x[0][q]/(r*r);
        u_y = stab_y[1][q]/r -ru*stab_y[0][q]/(r*r);
        v_x = stab_x[2][q]/r -rv*stab_x[0][q]/(r*r);
        v_y = stab_y[2][q]/r -rv*stab_y[0][q]/(r*r);

        tau11 = 2.0*mu*u_x + lambda*(u_x+v_y);
        tau12 = mu*(u_y+v_x);
        tau22 = 2.0*mu*v_y + lambda*(u_x+v_y);

        tau_nn = nx[q]*nx[q]*tau11 + 2*nx[q]*ny[q]*tau12 + ny[q]*ny[q]*tau22;

        // nomal vector for the flat wall (nx,ny)= (0,-1)
        // nx_x =0,nx_y=0,ny_x=0,ny_y=0
        // curvature of flat wall is -1/R = 0

        // nomal vector in the cylinder (nx,ny)= (-x,-y)
        // nx_x =-1,nx_y=0,ny_x=0,ny_y=-1
        // curvature of circle is -1/R = -1/0.5 =-2.0

        // hardwired for the cylinder(radius =0.5)
        //   curv = -2.0;
        // flat wall
        //   curv = 0.0;

        // D(Lambs)/D(s) = D(-\lambda_1*n2 + \lambda_2*n1)/D(s)
        Lambs_s = lamb_x[1][q]*ny[q]*ny[q] - lamb_x[2][q]*nx[q]*ny[q]
          -lamb_y[1][q]*nx[q]*ny[q] + lamb_y[2][q]*nx[q]*nx[q]
          +ny[q]*lamb[2][q] +nx[q]*lamb[1][q];

        // D(Lambn)/D(n) = D (\lambda_1*n1 + \lambda_2*n2)/D(n)
        Lambn_n = lamb_x[1][q]*nx[q]*nx[q] + lamb_x[2][q]*nx[q]*ny[q]
          +lamb_y[1][q]*nx[q]*ny[q] + lamb_y[2][q]*ny[q]*ny[q]
          -nx[q]*lamb[1][q] - ny[q]*lamb[2][q];

        // Gradient
        gv[q] = penalty*dv[q]
          +(r*lamb[0][q] + r*Vs*Lambs + 2*r*Vn*Lambn+(p+E+r*Vn*Vn)*lamb[3][q])
          + 1.0/Re*(lambda*(Lambs_s + curv*Lambn + Vs*lamb4_s)
                    + (lambda+2*mu)*(Lambn_n+Vn*lamb4_n) - tau_nn*lamb[3][q]);
      }
      offset+=bqtot;
    }
}


void Navier_Stokes::Isoflux_ControlBC::plot( const vField &state,
                                             const Size goffset,
                                             const dVector &Gphi,
                                             const Ordinal npredict,
                                             const Ordinal ntout,
                                             const Ordinal nsstep,
                                             const Ordinal riter) const {
  const Ordinal offset = numeric_cast<Ordinal>(goffset);
  dVector dv;
  char tmp[30];
  string fname;
  Ordinal np;
  for(Ordinal i=0;i<=npredict;i+=ntout){ //4 is nsstep for RK4
    fname="ns_isoflux_control";
    sprintf(tmp,"%lld_%lld.dat",(long long)i,(long long)riter);
    fname = fname + tmp;
    FILE *opt_stat = fopen(fname.c_str(),"w");
    fprintf(opt_stat, "Navier_Stokes Isoflux Control  @ %lld step\n",
            (long long)i);
    dv.alias( *(const_cast<dVector*>(&Gphi)),
              offset+(nsstep*i)*data_size(), data_size() );
    np=0;
    for (LocalSize n=0; n<state[0]->nbc; n++) {  // loop over state boundaries
      if (state[0]->bc[n]->type == type ) {
        LocalSize sid = state[0]->bc[n]->sid;
        LocalSize qtot = state[0]->bc[n]->S->qtot();
        Point* pside = new Point[state[0]->bc[n]->elmt->side[sid]->qtot()];
        state[0]->bc[n]->elmt->get_side_coordinates(sid,pside);
        for(LocalSize q=0;q<qtot;q++)
          fprintf(opt_stat,"%11.4e %11.4e %11.4e\n",pside[q].x,
                  pside[q].y,dv[np++]);
        delete[] pside;
      }
    }
    fclose(opt_stat);
  }
}

//===========================================================================

/// Isotermal steady control boundary condition
class Navier_Stokes::Isothermal_SteadyControlBC : public Isothermal_ControlBC{
public:
  Isothermal_SteadyControlBC( const string tag, ifstream &in, vField *F,
                              const Scalar gamma_, const Scalar mu_,
                              const Scalar Pr_ ) :
    Isothermal_ControlBC(tag,in,F,gamma_,mu_,Pr_) { }

  bool steady() const {return true;}

  void plot( const vField &state, const Size goffset, const dVector &Gphi,
             const Ordinal npredict, const Ordinal ntout, const Ordinal nsstep,
             const Ordinal riter) const {
    const Ordinal offset = numeric_cast<Ordinal>(goffset);
    dVector dv;
    string fname;
    char tmp[30];
    fname="ns_isothermal_steady_control";
    sprintf(tmp,"_%lld.dat",(long long)riter);
    fname = fname + tmp;
    FILE *opt_stat = fopen(fname.c_str(),"w");
    fprintf(opt_stat, "Navier_Stokes Isothermal Seady Control \n");
    dv.alias( *(const_cast<dVector*>(&Gphi)), offset+(0)*data_size(),
              data_size() );
    int np=0;
    for (LocalSize n=0; n<state[0]->nbc; ++n) {  // loop over state boundaries
      if (state[0]->bc[n]->type == type ) {
        LocalSize sid = state[0]->bc[n]->sid;
        LocalSize qtot = state[0]->bc[n]->S->qtot();
        Point* pside = new Point[state[0]->bc[n]->elmt->side[sid]->qtot()];
        state[0]->bc[n]->elmt->get_side_coordinates(sid,pside);
        for(LocalSize q=0;q<qtot;q++)
          fprintf(opt_stat,"%11.4e %11.4e %11.4e\n",pside[q].x,
                  pside[q].y,dv[np++]);
        delete[] pside;
      }
    }
    fclose(opt_stat);
  }

};

//===========================================================================

/// Isoflux steady control boundary condition
class Navier_Stokes::Isoflux_SteadyControlBC :public Isoflux_ControlBC{
public:
  Isoflux_SteadyControlBC( const string tag, ifstream &in, vField *F,
                           const Scalar gamma_, const Scalar mu_,
                           const Scalar Pr_ )
    : Isoflux_ControlBC(tag,in,F,gamma_,mu_,Pr_) { }

  bool steady() const {return true;}

  void plot( const vField &state,const Size goffset, const dVector &Gphi,
             const Ordinal npredict, const Ordinal ntout, const Ordinal nsstep,
             const Ordinal riter) const {
    const Ordinal offset = numeric_cast<Ordinal>(goffset);
    dVector dv;
    string fname;
    char tmp[256];
    fname="ns_isoflux_steady_control";
    sprintf(tmp,"_%lld.dat",(long long)riter);
    fname = fname + tmp;
    FILE *opt_stat = fopen(fname.c_str(),"w");
    // fprintf(opt_stat, "Navier_Stokes Isoflux Seady Control \n");
    dv.alias( *(const_cast<dVector*>(&Gphi)),
              offset+(0)*data_size(), data_size() );
    int np=0;
    for (LocalSize n=0; n<state[0]->nbc; n++) {  // loop over state boundaries
      if (state[0]->bc[n]->type == type ) {
        LocalSize sid = state[0]->bc[n]->sid;
        LocalSize qtot = state[0]->bc[n]->S->qtot();
        Point* pside = new Point[state[0]->bc[n]->elmt->side[sid]->qtot()];
        state[0]->bc[n]->elmt->get_side_coordinates(sid,pside);
        for(LocalSize q=0;q<qtot;q++){
#if 0
          fprintf(opt_stat,"%11.4e %11.4e %11.4e\n",pside[q].x,
                  pside[q].y,dv[np++]);
#else     // for cylinder problem, produce the polar plot
          Scalar angle=0;
          if(pside[q].x>=0 && pside[q].y>=0)
            angle = atan(pside[q].y/pside[q].x);
          else if(pside[q].x<0 && pside[q].y>=0)
            angle = pi+atan(pside[q].y/pside[q].x);
          else if(pside[q].x>0 && pside[q].y<0)
            angle = two*pi+atan(pside[q].y/pside[q].x);
          else if(pside[q].x<0 && pside[q].y<0)
            angle = pi+atan(pside[q].y/pside[q].x);
          fprintf(opt_stat,"%11.4e %11.4e \n",angle,dv[np++]);
#endif
        }
        delete[] pside;
      }
    }
    fclose(opt_stat);
  }

};

//===========================================================================
//      Constant Heat Flux Control Wall with shear stress minimization
//===========================================================================

/// Isoflux stress control boundary condition
class Navier_Stokes::Isoflux_stress_ControlBC : public BC, public Ctrl {
  Scalar value;  // default control
  Scalar qw;     // constant heat flux
  vField *Fphi;  // internal copy for the geometry operation [gqchen]
  Scalar gamma, Ma, Re, Pr, K, mu, lambda;
  Scalar curv;   // curvature of surface, assumed constant for now
public:
  // In the future, we should just pass in a Fluid object
  Isoflux_stress_ControlBC( const string tag, ifstream &in, vField *F,
                            const Scalar gamma_, const Scalar mu_,
                            const Scalar Pr_ ) :
    BC(tag), Fphi(F), gamma(gamma_), Pr(Pr_), mu(mu_) {
    DGM::Comm::World->cout()<<"NavierStokes::IsofluxControlBC()"<<endl;
    scan_lb(in);
#ifndef DGM_USE_TIME_REG
    if (!(in >> penalty >> qw >> curv))
      error("Navier_Stokes::IsofluxControlWallBC: error reading parms");
#else
    if (!(in >> penalty >> penalty_t>>qw >> curv))
      error("Navier_Stokes::IsofluxControlWallBC: error reading parms");
#endif
    scan_rb(in);
    value  = 0.0;         // zero control is default
    Ma     = 1.0;         // Ma is not explicitly needed
    Re     = 1.0;         // Set so that Re=1/mu
    lambda = -2.0/3.0*mu; // Stokes hypothesis
    K      = mu;          // To match CNS2D normalization
  }

  inline void apply( const Scalar, const vField & ) ;
  inline void apply_flux( const Scalar, const vField & ) ;

  inline void adjoint_apply( const Scalar, const vField &, const vField & ) ;
  inline void adjoint_apply_flux( const Scalar, const vField &,
                                  const vField & ) ;

  inline Ctrl* ctrl() { return this; }
  inline const Ctrl* ctrl() const { return this; }

  // Ctrl methods
  void initialize() { Ctrl::initialize(); data=value; }
  inline Scalar inner_product(const dVector &) const;
  inline void set_direction( dVector & );
  inline void objective_function_gradient( const vField &, const vField &,
      const Scalar time, dVector & ) const;
  inline void plot( const vField &, const Size, const dVector & ,
                    const Ordinal, const Ordinal, const Ordinal,
                    const Ordinal) const;

  void output() const {
    vField &F = *Fphi;
    vector<Side*> S(Fphi->size());
    LocalSize offset=0;
    dVector g;
    for (LocalSize n=0; n<(*Fphi)[0]->nbc; ++n)   // loop over field boundaries
      if ((*Fphi)[0]->bc[n]->type == type ) {
        for (vField::size_type i=0; i<Fphi->size(); ++i)
          S[i] = (*Fphi)[i]->bc[n]->S;
        g.alias( *(const_cast<dVector*>(&data)), offset, S[0]->qtot());
#ifdef DGM_PARALLEL
        if (DGM::Comm::World->MyPID()==1) {
          ofstream temp("node1.out", ios::app);
          // write out using the global element id
          temp<<"Element "
              << F[0]->partition->eid(F[0]->bc[n]->eid)
              <<" Side " <<F[0]->bc[n]->sid << endl
              << g << endl;
        }
        if (DGM::Comm::World->MyPID()==0) {
          ofstream temp("node0.out", ios::app);
          // write out using the global element id
          temp<<"Element "
              << F[0]->partition->eid(F[0]->bc[n]->eid)
              <<" Side " <<F[0]->bc[n]->sid << endl
              << g << endl;
        }
#else
        DGM::Comm::World->cout()<<"Element "
                                << F[0]->bc[n]->eid
                                <<" Side " <<F[0]->bc[n]->sid << endl
                                << g << endl;
#endif
        offset += S[0]->qtot();
      }
  }
};

void Navier_Stokes::Isoflux_stress_ControlBC::apply( const Scalar t,
                                                     const vField &F ) {
  vector<Side*> S(F.size()), B(F.size());
  if (data.size()==0) {
    // WARNING:: this assumes that the uncontrolled flow is no-slip
    for (LocalSize n=0; n<F[0]->nbc; ++n)   // loop over field boundaries
      if (F[0]->bc[n]->type == type ) {
        //dVector &nx = F[0]->bc[n]->S->nx();
        //dVector &ny = F[0]->bc[n]->S->ny();
        for (vField::size_type i=0; i<F.size(); ++i){
          S[i] = F[i]->bc[n]->S;
          B[i] = F[i]->bc[n]->B;
        }
#ifdef NO_CONTROL_BC
        for (LocalSize i=0; i<S[0]->qtot(); ++i) {
          B[0]->u[i] = S[0]->u[i];
          B[1]->u[i] = 0.0;
          B[2]->u[i] = 0.0;
          B[3]->u[i] = S[3]->u[i]
            - 0.5*(S[1]->u[i]*S[1]->u[i] + S[2]->u[i]*S[2]->u[i])/S[0]->u[i]
            + 0.5*(B[1]->u[i]*B[1]->u[i] + B[2]->u[i]*B[2]->u[i])/B[0]->u[i];
        }
#else
        for (LocalSize i=0; i<S[0]->qtot(); i++) {
          B[0]->u[i] = S[0]->u[i];
          B[1]->u[i] = 0.0;
          B[2]->u[i] = 0.0;
          B[3]->u[i] = S[3]->u[i]
            - 0.5*(S[1]->u[i]*S[1]->u[i] + S[2]->u[i]*S[2]->u[i])/S[0]->u[i]
            + 0.5*(B[1]->u[i]*B[1]->u[i] + B[2]->u[i]*B[2]->u[i])/B[0]->u[i];
        }
#endif
      }
  } else {
    LocalSize offset=0;
    dVector g;
    for (LocalSize n=0; n<F[0]->nbc; ++n)   // loop over field boundaries
      if (F[0]->bc[n]->type == type ) {
        dVector &nx = F[0]->bc[n]->S->nx();
        dVector &ny = F[0]->bc[n]->S->ny();
        for (vField::size_type i=0; i<F.size(); ++i) {
          S[i] = F[i]->bc[n]->S;
          B[i] = F[i]->bc[n]->B;
        }
        g.alias( *(const_cast<dVector*>(&data)), offset, S[0]->qtot());

        assert(g.size() == S[0]->qtot() );
        // do some projection here,two ways to project [gqchen]
        // 1) use the G->G interpolate
        // 2) base on the edge modes

        for (LocalSize i=0; i<S[0]->qtot(); i++) {
          B[0]->u[i] = S[0]->u[i];
          B[1]->u[i] = B[0]->u[i]*g[i]*nx[i];
          B[2]->u[i] = B[0]->u[i]*g[i]*ny[i];
          B[3]->u[i] = S[3]->u[i]
            - 0.5*(S[1]->u[i]*S[1]->u[i] + S[2]->u[i]*S[2]->u[i])/S[0]->u[i]
            + 0.5*( B[1]->u[i]*B[1]->u[i]+ B[2]->u[i]*B[2]->u[i])/B[0]->u[i];
        }
        offset += S[0]->qtot();
      }
  }
}

void Navier_Stokes::Isoflux_stress_ControlBC::apply_flux( const Scalar t,
                                                          const vField &F ) {
  vector<Side*> S(F.size()), B(F.size());
  for (LocalSize n=0; n<F[0]->nbc; ++n)   // loop over field boundaries
    if (F[0]->bc[n]->type == type ) {
      //dVector &nx = F[0]->bc[n]->S->nx();
      //dVector &ny = F[0]->bc[n]->S->ny();
      for (vField::size_type i=0; i<F.size(); ++i){
        S[i] = F[i]->bc[n]->S;
        B[i] = F[i]->bc[n]->B;
      }
      for (LocalSize i=0; i<S[0]->qtot(); i++) {
        B[0]->u[i] = -S[0]->u[i];
        B[1]->u[i] = -S[1]->u[i];
        B[2]->u[i] = -S[2]->u[i];
        B[3]->u[i] = -qw;
      }
    }
}

void Navier_Stokes::Isoflux_stress_ControlBC::adjoint_apply
(const Scalar t, const vField &state, const vField &adjoint) {
  LocalSize Nfields = adjoint.size();
  vector<Side*> S(Nfields), B(Nfields),SS(Nfields);

  Scalar Vn,Vs,T;
  dVector u_x,u_y,v_x,v_y;

  //Size offset=0;
  for (LocalSize n=0; n<state[0]->nbc; ++n)   // loop over field boundaries
    if (state[0]->bc[n]->type == type ) {
      dVector &nx = state[0]->bc[n]->S->nx();
      dVector &ny = state[0]->bc[n]->S->ny();
      LocalSize sid = adjoint[0]->bc[n]->sid;
      for (LocalSize i=0; i<Nfields; ++i) {
        S[i] = adjoint[i]->bc[n]->S;
        B[i] = adjoint[i]->bc[n]->B;
        SS[i]= state[i]->bc[n]->B;
      }
      assert(SS[0]->qtot() == S[0]->qtot() );
      // Project the State side => Adjoint side
      // do some projection here,two ways to project [gqchen]
      // 1) use the G->G interpolate
      // 2) base on the edge modes

      LocalSize bqtot = S[0]->qtot();
      LocalSize vqtot = state[0]->bc[n]->elmt->qtot;
      u_x.resize(bqtot);
      u_y.resize(bqtot);
      v_x.resize(bqtot);
      v_y.resize(bqtot);

      dVector r(state[0]->bc[n]->elmt->u);
      dVector ru(state[1]->bc[n]->elmt->u);
      dVector rv(state[2]->bc[n]->elmt->u);
      dVector u(vqtot),v(vqtot);
      dVector ux_v(vqtot),uy_v(vqtot),vx_v(vqtot),vy_v(vqtot);
#ifndef REO_JUMP1
      dvdiv(ru,r,u);
      dvdiv(rv,r,v);

      state[0]->bc[n]->elmt->gradient(u,ux_v,uy_v);
      state[0]->bc[n]->elmt->gradient(v,vx_v,vy_v);

      state[0]->bc[n]->elmt->load_side(ux_v,sid,u_x);
      state[0]->bc[n]->elmt->load_side(uy_v,sid,u_y);
      state[0]->bc[n]->elmt->load_side(vx_v,sid,v_x);
      state[0]->bc[n]->elmt->load_side(vy_v,sid,v_y);
#endif

      for (LocalSize i=0; i<bqtot; i++) {
        // At the ControlBC, Vs=0, Vn=g (control),
        Scalar n1 = nx[i];
        Scalar n2 = ny[i];

        Vn = ( SS[1]->u[i]*n1 + SS[2]->u[i]*n2)/SS[0]->u[i];
        Vs = (-SS[1]->u[i]*n2 + SS[2]->u[i]*n1)/SS[0]->u[i];

        Scalar tau_w = (-2.*n1*n2*u_x[i]+(n1*n1-n2*n2)*(u_y[i]+v_x[i])
                        +n1*n2*v_y[i])*mu;

        T = gamma*(gamma-1.0)/SS[0]->u[i]
          *(SS[3]->u[i]-0.5*SS[0]->u[i]*(Vn*Vn+Vs*Vs) );

        B[0]->u[i] = -S[3]->u[i]*(T/(gamma*(gamma-1.0))
                                  -0.5*(Vn*Vn+Vs*Vs));
        B[1]->u[i] = -Vn*S[3]->u[i]*n1 + Vs*S[3]->u[i]*n2 - Re*tau_w*n2;
        B[2]->u[i] = -Vn*S[3]->u[i]*n2 - Vs*S[3]->u[i]*n1 + Re*tau_w*n1;
        B[3]->u[i] = S[3]->u[i];
      }
    }
}


void Navier_Stokes::Isoflux_stress_ControlBC::adjoint_apply_flux
(const Scalar t, const vField &state, const vField &adjoint) {

  LocalSize Nfields = adjoint.size();
  vector<Side*> S(Nfields), B(Nfields),SS(Nfields);
  Scalar rho,m,n,E;
  dVector Fvx(Nfields),Fvy(Nfields);

  for (LocalSize nb=0; nb<state[0]->nbc; ++nb)   // loop over field boundaries
    if (state[0]->bc[nb]->type == type ) {
      dVector &nx = state[0]->bc[nb]->S->nx();
      dVector &ny = state[0]->bc[nb]->S->ny();
      const LocalSize sid = adjoint[0]->bc[nb]->sid;
      for (LocalSize i=0; i<Nfields; ++i) {
        S[i] = adjoint[i]->bc[nb]->S;
        B[i] = adjoint[i]->bc[nb]->B;
        SS[i]= state[i]->bc[nb]->B;
      }

      assert(SS[0]->qtot() == S[0]->qtot() );
      // Project the State side => Adjoint side
      // do some projection here,two ways to project [gqchen]
      // 1) use the G->G interpolate
      // 2) base on the edge modes

      LocalSize vqtot = adjoint[0]->bc[nb]->elmt->qtot;
      LocalSize bqtot = S[0]->qtot();

      dVector ru(bqtot);  ru = SS[1]->u;
      dVector rv(bqtot);  rv = SS[2]->u;

      dVector lamv_x[4], lamv_y[4];
      dVector lamb_x[4], lamb_y[4];

      dVector lamb4(bqtot), tmp1(bqtot), tmp2(bqtot);

      for(LocalSize i=0; i<Nfields; i++) {
        lamv_x[i].resize(vqtot);
        lamv_y[i].resize(vqtot);
        lamb_x[i].resize(bqtot);
        lamb_y[i].resize(bqtot);
      }
#ifndef REO_JUMP1
      for(LocalSize i=0;i<Nfields;i++) {
        adjoint[i]->bc[nb]->elmt->gradient(adjoint[i]->bc[nb]->elmt->u,
                                           lamv_x[i],lamv_y[i]);
        adjoint[i]->bc[nb]->elmt->load_side(lamv_x[i],sid,lamb_x[i]);
        adjoint[i]->bc[nb]->elmt->load_side(lamv_y[i],sid,lamb_y[i]);
      }
#endif
      adjoint[3]->bc[nb]->elmt->load_side(adjoint[3]->bc[nb]->elmt->u,
                                          sid,lamb4);

      // Here two constraints:
      //      lam4_n = -rho*Vn*lam4*(Pr*Re/(gamma*K))
      //      lam4_s = lam4_s(inside)
      tmp2 =0;
      dvvtvm(ny,lamb_x[3],tmp2,tmp2);      // -lam4,x *ny
      dvvtvp(nx,lamb_y[3],tmp2,tmp2);      // lam4,s=-ny*lam4,x+nx*lam4,y

      tmp1 =0;
      dvmul(nx,ru);                        // ru*nx
      dvmul(ny,rv);                        // rv*ny
      dvadd(ru,rv,tmp1);                   // rVn
      dvmul(lamb4,tmp1);                   // rVn*lam4
      scale(-Pr*Re/(gamma*K),tmp1);        // lam4,n

      lamb_x[3] =0;
      dvvtvm(ny,tmp2,lamb_x[3],lamb_x[3]);
      dvvtvp(nx,tmp1,lamb_x[3],lamb_x[3]); // lam4_x @bc

      lamb_y[3] =0;
      dvvtvp(ny,tmp1,lamb_y[3],lamb_y[3]);
      dvvtvp(nx,tmp2,lamb_y[3],lamb_y[3]); // lam4_y @bc

      for (LocalSize q=0; q<bqtot; q++) {
        rho = SS[0]->u[q];
        m   = SS[1]->u[q];
        n   = SS[2]->u[q];
        E   = SS[3]->u[q];

        Fvx[0] = -(2.0*mu+lambda)*m/(rho*rho)/Re*lamb_x[1][q]
          -n/(rho*rho)*mu/Re*lamb_x[2][q]
          +(-(2.0*mu+lambda)*m*m/(rho*rho*rho)/Re-n*n/(rho*rho*rho)*mu/Re
            +(gamma*(gamma-1.0)*(m*m+n*n)/(rho*rho*rho)/2.0
              -gamma*(gamma-1.0)*(E-(m*m+n*n)/rho/2.0)/(rho*rho))
            *K/Re/Pr/(gamma-1.0))*lamb_x[3][q]-n/(rho*rho)*mu/Re
          *lamb_y[1][q]-lambda/(rho*rho)/Re*m*lamb_y[2][q]
          +(-lambda*n/(rho*rho*rho)/Re*m-m/(rho*rho*rho)*mu/Re*n)*lamb_y[3][q];
        Fvx[1] = (2.0*mu+lambda)/rho/Re*lamb_x[1][q]
          +((2.0*mu+lambda)*m/(rho*rho)/Re
            -gamma*m/(rho*rho)*K/Re/Pr)*lamb_x[3][q]
          +lambda/rho/Re*lamb_y[2][q]+lambda*n/(rho*rho)/Re*lamb_y[3][q];
        Fvx[2] = 1/rho*mu/Re*lamb_x[2][q]
          +(n/(rho*rho)*mu/Re-gamma*n/(rho*rho)*K/Re/Pr)*lamb_x[3][q]
          +1/rho*mu/Re*lamb_y[1][q]+m/(rho*rho)*mu/Re*lamb_y[3][q];
        Fvx[3] = gamma/rho*K/Re/Pr*lamb_x[3][q];

        Fvy[0] = -lambda*n/(rho*rho)/Re*lamb_x[1][q]
          -m/(rho*rho)*mu/Re*lamb_x[2][q]
          +(-lambda*n/(rho*rho*rho)/Re*m-m/(rho*rho*rho)*mu/Re*n)*lamb_x[3][q]
          -m/(rho*rho)*mu/Re*lamb_y[1][q]
          -(2.0*mu+lambda)*n/(rho*rho)/Re*lamb_y[2][q]
          +(-m*m/(rho*rho*rho)*mu/Re-(2.0*mu+lambda)*n*n/(rho*rho*rho)/Re
            +(gamma*(gamma-1.0)*(m*m+n*n)/(rho*rho*rho)/2.0
              -gamma*(gamma-1.0)*(E-(m*m+n*n)/rho/2.0)/(rho*rho))
            *K/Re/Pr/(gamma-1.0))*lamb_y[3][q];
        Fvy[1] = 1/rho*mu/Re*lamb_x[2][q]+n/(rho*rho)*mu/Re*lamb_x[3][q]
          +1/rho*mu/Re*lamb_y[1][q]+(m/(rho*rho)*mu/Re
                                     -gamma*m/(rho*rho)*K/Re/Pr)*lamb_y[3][q];
        Fvy[2] = lambda/rho/Re*lamb_x[1][q]+lambda/(rho*rho)/Re*m*lamb_x[3][q]
          +(2.0*mu+lambda)/rho/Re*lamb_y[2][q]
          +((2.0*mu+lambda)*n/(rho*rho)/Re
            -gamma*n/(rho*rho)*K/Re/Pr)*lamb_y[3][q];
        Fvy[3] = gamma/rho*K/Re/Pr*lamb_y[3][q];

        B[0]->u[q] = -(nx[q]*Fvx[0] + ny[q]*Fvy[0]);
        B[1]->u[q] = -(nx[q]*Fvx[1] + ny[q]*Fvy[1]);
        B[2]->u[q] = -(nx[q]*Fvx[2] + ny[q]*Fvy[2]);
        B[3]->u[q] = -(nx[q]*Fvx[3] + ny[q]*Fvy[3]);
      }
    }
}

// I have to get a local copy of State vField to compute L2 norm[gqchen]
Scalar Navier_Stokes::Isoflux_stress_ControlBC::inner_product
( const dVector &Y ) const {
  LocalSize qtot, sid;
  dVector ta,tb,tab;
  LocalSize offset=0;
  Scalar sum=0.0;
  for (LocalSize n=0; n<(*Fphi)[0]->nbc; ++n)   // loop over field boundaries
    if ((*Fphi)[0]->bc[n]->type == type ){
      qtot = (*Fphi)[0]->bc[n]->S->qtot();
      sid = (*Fphi)[0]->bc[n]->sid;
      ta.alias(data,offset,qtot);
      tb.alias(Y,offset,qtot);
      tab.resize(qtot);
      dvmul(ta, tb, tab);
      offset += qtot;
      sum +=(*Fphi)[0]->bc[n]->elmt->compute_side_integral(tab,sid);
    }
  return sum;
}


void  Navier_Stokes::Isoflux_stress_ControlBC::set_direction( dVector &out ) {
  if (data.size()==0) return;
  assert( data_size() == out.size() );
  out = data = 1.0;
}

// WARNING: does NOT support general curvature!! [gqchen]
void Navier_Stokes::Isoflux_stress_ControlBC::objective_function_gradient(
    const vField &state, const vField &adjoint, const Scalar time,
    dVector &grad ) const
{
  LocalSize Nfields = adjoint.size();
  vector<Side*> S(Nfields), B(Nfields),SS(Nfields);
  Scalar r,ru,rv,E,p;
  Scalar u_x,u_y,v_x,v_y;
  Scalar tau11,tau12,tau22,tau_nn;
  Scalar Vn,Vs, Lambn,Lambs,lamb4_s,lamb4_n,Lambs_s,Lambn_n;

  LocalSize offset=0;
  dVector dv, gv;
  dVector lamb[4],stab[4];       // boundary adjoint/state vector
  dVector lamb_x[4],lamb_y[4];   // boundary adjoint_x/state_x vector
  dVector  stab_x[4],stab_y[4];  // boundary adjoint_y/state_y vector
  for (LocalSize nb=0; nb<state[0]->nbc; ++nb)   // loop over field boundaries
    if (state[0]->bc[nb]->type == type ) {

      dVector &nx = state[0]->bc[nb]->S->nx();
      dVector &ny = state[0]->bc[nb]->S->ny();

      LocalSize sid = adjoint[0]->bc[nb]->sid;

      for (LocalSize i=0; i<Nfields; ++i) {
        S[i] = adjoint[i]->bc[nb]->S;
        B[i] = adjoint[i]->bc[nb]->B;
        SS[i]= state[i]->bc[nb]->B;
      }

      assert(SS[0]->qtot() == S[0]->qtot() );
      // Project the State side => Adjoint side
      // do some projection here,two ways to project [gqchen]
      // 1) use the G->G interpolate
      // 2) base on the edge modes

      // Number of quadrature points in the Element related with Control B.C.
      LocalSize vqtot = adjoint[0]->bc[nb]->elmt->qtot;
      // Number of quadrature points along the Control boundary
      LocalSize bqtot = S[0]->qtot();

      dv.alias( *(const_cast<dVector*>(&data)), offset,
                state[0]->bc[nb]->S->qtot() );
      gv.alias( *(const_cast<dVector*>(&grad)), offset,
                state[0]->bc[nb]->S->qtot() );

      dVector tmpx(vqtot), tmpy(vqtot);

      for(LocalSize i=0;i<Nfields;i++) {
        lamb_x[i].resize(bqtot);
        lamb_y[i].resize(bqtot);
        stab_x[i].resize(bqtot);
        stab_y[i].resize(bqtot);
        lamb[i].resize(bqtot);
        stab[i].resize(bqtot);
      }

      // get the state and its gradient @ control boundary
      for(LocalSize i=0;i<Nfields;i++) {
        state[i]->bc[nb]->elmt->load_side( state[i]->bc[nb]->elmt->u,sid,
                                           stab[i]);
        state[i]->bc[nb]->elmt->gradient(state[i]->bc[nb]->elmt->u,
                                         tmpx,tmpy);
        state[i]->bc[nb]->elmt->load_side(tmpx,sid,stab_x[i]);
        state[i]->bc[nb]->elmt->load_side(tmpy,sid,stab_y[i]);
      }

      // get the adjoint and its gradient @ control boundary
      for(LocalSize i=0;i<Nfields;i++){
        adjoint[i]->bc[nb]->elmt->load_side( adjoint[i]->bc[nb]->elmt->u,sid,
                                             lamb[i]);
        adjoint[i]->bc[nb]->elmt->gradient(adjoint[i]->bc[nb]->elmt->u,
                                           tmpx,tmpy);
        adjoint[i]->bc[nb]->elmt->load_side(tmpx,sid,lamb_x[i]);
        adjoint[i]->bc[nb]->elmt->load_side(tmpy,sid,lamb_y[i]);
      }

      for(LocalSize q=0; q<bqtot; q++) {
        r = stab[0][q];
        ru = stab[1][q];
        rv = stab[2][q];
        E = stab[3][q];

        Vs = (ru*(-ny[q])+rv*nx[q])/r;    // tangential velocity
        // Here Vn should be g [gqchen]
        Vn = (ru*nx[q]+rv*ny[q])/r;       // normal velocity
        p  = (gamma-1.0)*(E - 0.5*(ru*ru+rv*rv)/r); //pressure

        // D()/D(n) = ()_{,x}*n1 + ()_{,y}*n2
        // D()/D(s) = -()_{,x}*n2 + ()_{,y}*n1

        // \lambda_n = \lambda_1*n1 + \lambda_2*n2
        Lambn = lamb[1][q]*nx[q] + lamb[2][q]*ny[q];
        // \lambda_s = - \lambda_1*n2 + \lambda_2*n1
        Lambs = -lamb[1][q]*ny[q] + lamb[2][q]*nx[q];
        // D(\lambda_4)/D(s)
        lamb4_s = -lamb_x[3][q]*ny[q] + lamb_y[3][q]*nx[q];
        // D(\lambda_4)/D(n)
        lamb4_n = lamb_x[3][q]*nx[q] + lamb_y[3][q]*ny[q];

        // Calculate the shear stress
        u_x = stab_x[1][q]/r -ru*stab_x[0][q]/(r*r);
        u_y = stab_y[1][q]/r -ru*stab_y[0][q]/(r*r);
        v_x = stab_x[2][q]/r -rv*stab_x[0][q]/(r*r);
        v_y = stab_y[2][q]/r -rv*stab_y[0][q]/(r*r);

        tau11 = 2.0*mu*u_x + lambda*(u_x+v_y);
        tau12 = mu*(u_y+v_x);
        tau22 = 2.0*mu*v_y + lambda*(u_x+v_y);

        tau_nn = nx[q]*nx[q]*tau11 + 2*nx[q]*ny[q]*tau12 + ny[q]*ny[q]*tau22;

        // nomal vector for the flat wall (nx,ny)= (0,-1)
        // nx_x =0,nx_y=0,ny_x=0,ny_y=0
        // curvature of flat wall is -1/R = 0

        // nomal vector in the cylinder (nx,ny)= (-x,-y)
        // nx_x =-1,nx_y=0,ny_x=0,ny_y=-1
        // curvature of circle is -1/R = -1/0.5 =-2.0

        // hardwired for the cylinder(radius =0.5)
        //   curv = -2.0;
        // flat wall
        //   curv = 0.0;

        // D(Lambs)/D(s) = D(-\lambda_1*n2 + \lambda_2*n1)/D(s)
        Lambs_s = lamb_x[1][q]*ny[q]*ny[q] - lamb_x[2][q]*nx[q]*ny[q]
          -lamb_y[1][q]*nx[q]*ny[q] + lamb_y[2][q]*nx[q]*nx[q]
          +ny[q]*lamb[2][q] +nx[q]*lamb[1][q];

        // D(Lambn)/D(n) = D (\lambda_1*n1 + \lambda_2*n2)/D(n)
        Lambn_n = lamb_x[1][q]*nx[q]*nx[q] + lamb_x[2][q]*nx[q]*ny[q]
          +lamb_y[1][q]*nx[q]*ny[q] + lamb_y[2][q]*ny[q]*ny[q]
          -nx[q]*lamb[1][q] - ny[q]*lamb[2][q];

        // Gradient
        gv[q] = penalty*dv[q]
          +(r*lamb[0][q] + r*Vs*Lambs + 2*r*Vn*Lambn+(p+E+r*Vn*Vn)*lamb[3][q])
          + 1.0/Re*(lambda*(Lambs_s + curv*Lambn + Vs*lamb4_s)
                    + (lambda+2*mu)*(Lambn_n+Vn*lamb4_n) - tau_nn*lamb[3][q]);
      }
      offset+=bqtot;
    }
}


void Navier_Stokes::Isoflux_stress_ControlBC::plot( const vField &state,
                                                    const Size goffset,
                                                    const dVector &Gphi,
                                                    const Ordinal npredict,
                                                    const Ordinal ntout,
                                                    const Ordinal nsstep,
                                                    const Ordinal riter) const {
  const Ordinal offset = numeric_cast<Ordinal>(goffset);
  dVector dv;
  char tmp[256];
  for(LocalSize i=0; i<=npredict; i+=ntout){    // 4 is nsstep for RK4
    string fname="ns_isoflux_control";
    sprintf(tmp,"%lld_%lld.dat",(long long)i,(long long)riter);
    fname = fname + tmp;
    FILE *opt_stat = fopen(fname.c_str(),"w");
    fprintf(opt_stat, "Navier_Stokes Isoflux Control  @ %llu step\n",
            (long long unsigned)i);
    dv.alias( *(const_cast<dVector*>(&Gphi)),
              offset+(nsstep*i)*data_size(), data_size() );
    int np=0;
    for (LocalSize n=0; n<state[0]->nbc; n++) {  // loop over state boundaries
      if (state[0]->bc[n]->type == type ) {
        LocalSize sid = state[0]->bc[n]->sid;
        LocalSize qtot = state[0]->bc[n]->S->qtot();
        Point* pside = new Point[state[0]->bc[n]->elmt->side[sid]->qtot()];
        state[0]->bc[n]->elmt->get_side_coordinates(sid,pside);
        for(LocalSize q=0; q<qtot; q++)
          fprintf(opt_stat,"%11.4e %11.4e %11.4e\n",pside[q].x,
                  pside[q].y,dv[np++]);
        delete[] pside;
      }
    }
    fclose(opt_stat);
  }
}

//===========================================================================
//                             Jet Control
//===========================================================================

/// Jet control boundary condition
class Navier_Stokes::Jet_ControlBC : public BC, public Ctrl {
  //Scalar rhoj, ruj, rvj, rEj;
  Scalar mdot, theta;
  //vField *Fphi;  // internal copy for geometry operations [gqchen]
  //Scalar gamma, Pr;
  Scalar Ma, Re, K, mu, lambda;
  Scalar d2r;
public:
  Jet_ControlBC( const string tag, ifstream &in, vField *F,
                 const Scalar gamma_, const Scalar mu_,
                 const Scalar Pr_ ) :
    BC(tag), mdot(0), theta(0),
    //Fphi(F), gamma(gamma_), Pr(Pr_),
    Ma(0), Re(0), K(0), mu(mu_), lambda(0), d2r(0)
    {
      DGM:: Comm::World->cout()<<"NavierStokes::JetControlBC()"<<endl;
      scan_lb(in);
      if (!(in >> penalty >> mdot >> theta ))
        error("Navier_Stokes::JetControlBC: error reading parms");
      scan_rb(in);
      Ma     = 1.0;         // Ma is not explicitly needed
      Re     = 1.0;         // Set so that Re=1/mu
      lambda = -2.0/3.0*mu; // Stokes hypothesis
      K      = mu;          // To match CNS2D normalization
      d2r    = pi/180.0;    // convert degrees to radians
    }

  inline void apply( const Scalar, const vField & ) ;
  inline void apply_flux( const Scalar, const vField & ) ;

  inline void adjoint_apply( const Scalar, const vField &, const vField & ) ;
  inline void adjoint_apply_flux( const Scalar, const vField &,
                                  const vField & ) ;

  inline Ctrl* ctrl() { return this; }
  inline const Ctrl* ctrl() const { return this; }

  // Ctrl methods
  void initialize() { Ctrl::initialize(); data=theta; }
  inline Scalar inner_product(const dVector &) const;
  inline Scalar norm() const;
  inline void set_direction( dVector & );
  inline void objective_function_gradient( const vField &, const vField &,
      const Scalar time, dVector & ) const;
  inline void plot( const vField &, const Size, const dVector & ,
                    const Ordinal, const Ordinal, const Ordinal,
                    const Ordinal) const;
};

void Navier_Stokes::Jet_ControlBC::apply( const Scalar t, const vField &F ) {
  vector<Side*> S(F.size()), B(F.size());
  if (data.size()==0) {
    for (LocalSize n=0; n<F[0]->nbc; ++n)   // loop over field boundaries
      if (F[0]->bc[n]->type == type ) {
        dVector &nx = F[0]->bc[n]->S->nx();
        dVector &ny = F[0]->bc[n]->S->ny();
        for (vField::size_type i=0; i<F.size(); ++i) {
          S[i] = F[i]->bc[n]->S;
          B[i] = F[i]->bc[n]->B;
        }
        for (LocalSize i=0; i<S[0]->qtot(); i++) {
          Scalar alpha = atan2( -ny[i], -nx[i] ) + d2r*theta;
#if 1
          // this looks like an Isoflux_Wall_ControlBC and works better
          B[0]->u[i] = S[0]->u[i];
          B[1]->u[i] = mdot*cos(alpha);
          B[2]->u[i] = mdot*sin(alpha);
          B[3]->u[i] = S[3]->u[i]
            - 0.5*(S[1]->u[i]*S[1]->u[i] + S[2]->u[i]*S[2]->u[i])/S[0]->u[i]
            + 0.5*(B[1]->u[i]*B[1]->u[i]+ B[2]->u[i]*B[2]->u[i])/B[0]->u[i];
#else
          // this looks like a StateBC
          B[0]->u[i] = rhoj;
          B[1]->u[i] = mdot*cos(alpha);
          B[2]->u[i] = mdot*sin(alpha);
          B[3]->u[i] = rEj;
#endif
        }
      }
  } else {
    LocalSize offset=0;
    dVector g;
    for (LocalSize n=0; n<F[0]->nbc; ++n)   // loop over field boundaries
      if (F[0]->bc[n]->type == type ) {
        dVector &nx = F[0]->bc[n]->S->nx();
        dVector &ny = F[0]->bc[n]->S->ny();
        for (vField::size_type i=0; i<F.size(); ++i){
          S[i] = F[i]->bc[n]->S;
          B[i] = F[i]->bc[n]->B;
        }
        g.alias( *(const_cast<dVector*>(&data)), offset, S[0]->qtot());
        assert(g.size() == S[0]->qtot() );
        for (LocalSize i=0; i<S[0]->qtot(); i++) {
          Scalar alpha = atan2( -ny[i], -nx[i] ) + d2r*g[i];
#if 1
          B[0]->u[i] = S[0]->u[i];
          B[1]->u[i] = mdot*cos(alpha);
          B[2]->u[i] = mdot*sin(alpha);
          B[3]->u[i] = S[3]->u[i]
            - 0.5*(S[1]->u[i]*S[1]->u[i] + S[2]->u[i]*S[2]->u[i])/S[0]->u[i]
            + 0.5*(B[1]->u[i]*B[1]->u[i]+ B[2]->u[i]*B[2]->u[i])/B[0]->u[i];
#else
          B[0]->u[i] = rhoj;
          B[1]->u[i] = mdot*cos(alpha);
          B[2]->u[i] = mdot*sin(alpha);
          B[3]->u[i] = rEj;
#endif
        }
        offset += S[0]->qtot();
      }
  }
}

void Navier_Stokes::Jet_ControlBC::apply_flux( const Scalar t,
                                               const vField &F ) {
  vector<Side*> S(F.size()), B(F.size());
  for (LocalSize n=0; n<F[0]->nbc; ++n)   // loop over field boundaries
    if (F[0]->bc[n]->type == type ) {
      //dVector &nx = F[0]->bc[n]->S->nx();
      //dVector &ny = F[0]->bc[n]->S->ny();
      for (vField::size_type i=0; i<F.size(); ++i) {
        S[i] = F[i]->bc[n]->S;
        B[i] = F[i]->bc[n]->B;
      }
      for (LocalSize i=0; i<S[0]->qtot(); i++) {
        B[0]->u[i] = 0.0; //-S[0]->u[i];
        B[1]->u[i] = 0.0; //-S[1]->u[i];
        B[2]->u[i] = 0.0; //-S[2]->u[i];
        B[3]->u[i] = 0.0; //-S[3]->u[i];
      }
    }
}

void Navier_Stokes::Jet_ControlBC::adjoint_apply
( const Scalar t, const vField &state, const vField &adjoint) {
  LocalSize Nfields = adjoint.size();
  vector<Side*> S(Nfields), B(Nfields),SS(Nfields);
  //Scalar Vn;
  //Size offset=0;
  for (LocalSize n=0; n<state[0]->nbc; ++n)   // loop over field boundaries
    if (state[0]->bc[n]->type == type ){
      //dVector &nx = state[0]->bc[n]->S->nx();
      //dVector &ny = state[0]->bc[n]->S->ny();
      for (LocalSize i=0; i<Nfields; ++i){
        S[i] = adjoint[i]->bc[n]->S;
        B[i] = adjoint[i]->bc[n]->B;
        SS[i]= state[i]->bc[n]->B;
      }
      assert(SS[0]->qtot() == S[0]->qtot() );
      for (LocalSize i=0; i<S[0]->qtot(); i++) {
        B[0]->u[i] = 0.0;
        B[1]->u[i] = 0.0;
        B[2]->u[i] = 0.0;
        B[3]->u[i] = 0.0;
      }
    }
}

void Navier_Stokes::Jet_ControlBC::adjoint_apply_flux
( const Scalar t, const vField &state, const vField &adjoint ) {
  vector<Side*> S(adjoint.size()), B(adjoint.size());
  for (LocalSize n=0; n<adjoint[0]->nbc; ++n)   // loop over field boundaries
    if (adjoint[0]->bc[n]->type == type ) {
      //dVector &nx = adjoint[0]->bc[n]->S->nx();
      //dVector &ny = adjoint[0]->bc[n]->S->ny();
      for (vField::size_type i=0; i<adjoint.size(); ++i){
        S[i] = adjoint[i]->bc[n]->S;
        B[i] = adjoint[i]->bc[n]->B;
      }
      for (LocalSize i=0; i<S[0]->qtot(); i++) {
        B[0]->u[i] = 0.0; //-S[0]->u[i];
        B[1]->u[i] = 0.0; //-S[1]->u[i];
        B[2]->u[i] = 0.0; //-S[2]->u[i];
        B[3]->u[i] = 0.0; //-S[3]->u[i];
      }
    }
}

// This is appropriate for Dakota
Scalar Navier_Stokes::Jet_ControlBC::norm() const {
  return mdot*mdot;
}

Scalar Navier_Stokes::Jet_ControlBC::inner_product( const dVector &Y ) const {
#if 1
  error("NS::Jet_ControlBC::inner_product(...) not implemented");
  return 0.0;
#else
  int qtot, sid;
  dVector ta, tb;
  Size offset = 0;
  Scalar sum = 0.0;
  for (int n=0; n<(*Fphi)[0]->nbc; ++n)   // loop over field boundaries
    if ( (*Fphi)[0]->bc[n]->type == type ) {
      qtot = (*Fphi)[0]->bc[n]->S->qtot();
      sid = (*Fphi)[0]->bc[n]->sid;
      ta.alias(data,offset,qtot);
      tb.alias(Y,offset,qtot);
      for (LocalSize i=0; i<qtot; ++i) sum += ta[i]*tb[i];
      offset += qtot;
    }
  return sum;
#endif
}

void  Navier_Stokes::Jet_ControlBC::set_direction( dVector &out ) {
  if (data.size()==0) return;
  assert( data_size() == out.size() );
  out = data = 1.0;
}

void Navier_Stokes::Jet_ControlBC::objective_function_gradient(
  const vField &state, const vField &adjoint, const Scalar time,
  dVector &grad ) const
{
  error("NS::Jet_ControlBC::gradient(...) not implemented");
}

void Navier_Stokes::Jet_ControlBC::plot( const vField &state,
                                         const Size offset,
                                         const dVector &Gphi,
                                         const Ordinal npredict,
                                         const Ordinal ntout,
                                         const Ordinal nsstep,
                                         const Ordinal riter) const {
  error("NS::Jet_ControlBC::plot(...) not implemented");
}

//===========================================================================
//                   Sondhaus Wall Boundary Condition
//===========================================================================

/// Sondhaus wall boundary condition
class Navier_Stokes::SondhausWallBC : public BC {
  Scalar L;      // period of temperature variation
  Scalar Ts;     // uniform wall temperature
  Scalar DeltaT; // temperature variation
  Scalar lambda; // sharpness parameter (default is 3)
  Scalar Rgas;   // Gas constant
  Scalar gamma;  // ratio of specific heats
public:
  SondhausWallBC( const string t, ifstream &in, Scalar g ) : BC(t), gamma(g) {
    scan_lb(in);
    if (!(in >> L >> lambda >> DeltaT >> Ts >> Rgas))
      error("Navier_Stokes::SondhausWallBC: L, lambda, DeltaT, Ts, Rgas");
    scan_rb(in);
  }
  inline void apply( const Scalar t, const vField & ) ;
  inline void apply_flux( const Scalar t, const vField & ) ;

  inline void adjoint_apply( const Scalar t, const vField &, const vField & );
  inline void adjoint_apply_flux( const Scalar t, const vField &,
                                  const vField & );
};

void Navier_Stokes::SondhausWallBC::apply( const Scalar t, const vField &F ) {
  vector<Side*> S(F.size()), B(F.size());
  for (LocalSize n=0; n<F[0]->nbc; ++n)   // loop over field boundaries
    if (F[0]->bc[n]->type == type ) {
      //dVector &nx = F[0]->bc[n]->S->nx();
      //dVector &ny = F[0]->bc[n]->S->ny();
      for (vField::size_type i=0; i<F.size(); ++i) {
        S[i] = F[i]->bc[n]->S;
        B[i] = F[i]->bc[n]->B;
      }
      const LocalSize qtot(B[0]->qtot());
      Point *pside = new Point[qtot];
      F[0]->el[B[0]->leid()]->get_side_coordinates( B[0]->id(), pside );
      for (LocalSize i=0; i<S[0]->qtot(); i++) {
        B[0]->u[i] = S[0]->u[i];
        B[1]->u[i] = 0.0;
        B[2]->u[i] = 0.0;
        Scalar Tw = Ts + DeltaT*(1.0+tanh(lambda*cos(4.0*pi*pside[i].x/L)))/
          (1.0+tanh(lambda));
        B[3]->u[i] = B[0]->u[i]*Tw*Rgas/(gamma-1.0);
      }
      delete[] pside;
    }
}

void Navier_Stokes::SondhausWallBC::apply_flux( const Scalar t,
                                                const vField &F ) {
  vector<Side*> S(F.size()), B(F.size());
  for (LocalSize n=0; n<F[0]->nbc; ++n)   // loop over field boundaries
    if (F[0]->bc[n]->type == type ) {
      //dVector &nx = F[0]->bc[n]->S->nx();
      //dVector &ny = F[0]->bc[n]->S->ny();
      for (vField::size_type i=0; i<F.size(); ++i){
        S[i] = F[i]->bc[n]->S;
        B[i] = F[i]->bc[n]->B;
      }
      for (LocalSize i=0; i<S[0]->qtot(); i++) {
        B[0]->u[i] = -S[0]->u[i];
        B[1]->u[i] = -S[1]->u[i];
        B[2]->u[i] = -S[2]->u[i];
        B[3]->u[i] = -S[3]->u[i];
      }
    }
}

// \lambda_1 = 0;  \lambda_2 = 0;  \lambda_3 = 0
void Navier_Stokes::SondhausWallBC::adjoint_apply( const Scalar t,
                                                   const vField &state,
                                                   const vField &adjoint) {
  vector<Side*> S(adjoint.size()), B(adjoint.size());
  for (LocalSize n=0; n<adjoint[0]->nbc; ++n)   // loop over field boundaries
    if (adjoint[0]->bc[n]->type == type ) {
      //dVector &nx = adjoint[0]->bc[n]->S->nx();
      //dVector &ny = adjoint[0]->bc[n]->S->ny();
      for (vField::size_type i=0; i<adjoint.size(); ++i) {
        S[i] = adjoint[i]->bc[n]->S;
        B[i] = adjoint[i]->bc[n]->B;
      }
      for (LocalSize i=0; i<S[0]->qtot(); i++) {
        B[0]->u[i] = S[0]->u[i];
        B[1]->u[i] = 0.0;
        B[2]->u[i] = 0.0;
        B[3]->u[i] = 0.0;
      }
    }
}

//  \lambda_1 = 0;  \lambda_2 = 0;  \lambda_3 = 0
void Navier_Stokes::SondhausWallBC::
adjoint_apply_flux( const Scalar t, const vField &state,
                    const vField &adjoint ) {
  vector<Side*> S(adjoint.size()), B(adjoint.size());
  for (LocalSize n=0; n<adjoint[0]->nbc; ++n)   // loop over field boundaries
    if (adjoint[0]->bc[n]->type == type ) {
      //dVector &nx = adjoint[0]->bc[n]->S->nx();
      //dVector &ny = adjoint[0]->bc[n]->S->ny();
      for (vField::size_type i=0; i<adjoint.size(); ++i){
        S[i] = adjoint[i]->bc[n]->S;
        B[i] = adjoint[i]->bc[n]->B;
      }
      for (LocalSize i=0; i<S[0]->qtot(); i++) {
        B[0]->u[i] = -S[0]->u[i];
        B[1]->u[i] = -S[1]->u[i];
        B[2]->u[i] = -S[2]->u[i];
        B[3]->u[i] = -S[3]->u[i];
      }
    }
}

} // namespace Reo

#endif  // REO_NAVIER_STOKES_BC_HPP
