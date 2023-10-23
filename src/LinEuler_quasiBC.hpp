#ifndef REO_LINEULER_QUASI_BC_HPP
#define REO_LINEULER_QUASI_BC_HPP

/** \file  LinEuler_quasiBC.hpp
    \brief Linearized Euler equations BCs in quasi-conservative variables
    \author S. Scott Collis
*/

// DGM includes
#include "BC.hpp"
#include "Source.hpp"
#include "Ctrl.hpp"
#include "Source.hpp"

using namespace DGM;

namespace Reo {

//===========================================================================
//                           Linearized State BC
//===========================================================================

/// State boundary condition
class LinEuler_quasi::LinStateBC : public BC {
  dVector values;
public:
  LinStateBC( const string t, dVector &d) : BC(t) {
    values.resize( d.size() );
    values = d;
  }
  LinStateBC( const string t, ifstream &in,int ndof =0) : BC(t) {
    scan_lb(in);
    if (ndof==0)
      if (!(in >> ndof)) error("LinEuler_quasi::LinStateBC::Cannot read ndof");
    values.resize(ndof);
    for (int n=0; n<ndof; n++)
      if (!(in >> values[n]))
        error("LinEuler_quasi::LinStateBC::Cannot read values");
    scan_rb(in);
  }

  inline void linear_apply( const Scalar, const vField &, const vField & ) ;
  inline void apply_flux( const Scalar, const vField & ) ;

  inline void adjoint_apply( const Scalar, const vField &, const vField & ) ;
  inline void adjoint_apply_flux( const Scalar, const vField &,
                                  const vField & ) ;
};


// Zero fluctuation
void LinEuler_quasi::LinStateBC::linear_apply(const Scalar t,
                                              const vField &Fm,
                                              const vField &F ) {
  vector<Side*> S(F.size()), B(F.size()), Sm(F.size());
  //Scalar rho, u[2], T;
  //Scalar rhop, up, vp, Tp, w[4];
  //Scalar tmp;
  for (LocalSize n=0; n<F[0]->nbc; ++n)   // loop over field boundaries
    if (F[0]->bc[n]->type == type ) {
      //dVector &nx = F[0]->bc[n]->S->nx();
      //dVector &ny = F[0]->bc[n]->S->ny();
      for (vField::size_type i=0; i<F.size(); ++i){
        Sm[i] = F[i]->bc[n]->S;
        S[i] = F[i]->bc[n]->S;
        B[i] = F[i]->bc[n]->B;
      }
      for (LocalSize i=0; i<S[0]->qtot(); ++i) { // Form Quasi U = M*Up
        B[0]->u[i] = 0;
        B[1]->u[i] = 0;
        B[2]->u[i] = 0;
        B[3]->u[i] = 0;
      }
    }
}

void LinEuler_quasi::LinStateBC::apply_flux( const Scalar t, const vField & ) {
  error("LinEuler_quasi::LinStateBC::apply_flux() not implemented.");
}

void LinEuler_quasi::LinStateBC::adjoint_apply( const Scalar t,
                                                const vField &state,
                                                const vField &adjoint) {
  error("LinEuler_quasi::LinStateBC::adjoint_apply() not implemented.");
}

void LinEuler_quasi::LinStateBC::adjoint_apply_flux( const Scalar t,
                                                     const vField &state,
                                                     const vField &adjoint) {
  error("LinEuler_quasi::LinStateBC::adjoint_apply_flux() not implemented.");
}

//===========================================================================
//                       Linearized Solid Wall BC
//===========================================================================

/// Wall boundary condition
class LinEuler_quasi::LinWallBC : public BC {
  Scalar gamma;
public:
  LinWallBC( const string t ) : BC(t) { }
  LinWallBC( const string t, ifstream &in, const Scalar gamma_)
    : BC(t), gamma(gamma_) {
    scan_lb(in);
    scan_rb(in);
  }

  inline void linear_apply( const Scalar, const vField &, const vField & ) ;
  inline void apply_flux( const Scalar, const vField & ) ;

  inline void adjoint_apply( const Scalar, const vField &, const vField & ) ;
  inline void adjoint_apply_flux( const Scalar, const vField &,
                                  const vField & );
};

void LinEuler_quasi::LinWallBC::linear_apply(const Scalar t,
                                             const vField &Fm,
                                             const vField &F ) {
  vector<Side*> S(F.size()), B(F.size()),Sm(F.size());
  Scalar rho, u[2], T;
  Scalar rhop, up, vp, Tp, w[4];
  Scalar tmp;
  for (LocalSize n=0; n<F[0]->nbc; ++n)   // loop over field boundaries
    if (F[0]->bc[n]->type == type ) {
      dVector &nx = F[0]->bc[n]->S->nx();
      dVector &ny = F[0]->bc[n]->S->ny();
      for (vField::size_type i=0; i<F.size(); ++i){
        Sm[i] = F[i]->bc[n]->S;
        S[i] = F[i]->bc[n]->S;
        B[i] = F[i]->bc[n]->B;
      }
      for (LocalSize i=0; i<S[0]->qtot(); ++i) {
        for(LocalSize m=0; m<4; m++) w[m] = S[m]->u[i];
        rho  = Sm[0]->u[i];
        u[0] = Sm[1]->u[i];
        u[1] = Sm[2]->u[i];
        T    = Sm[3]->u[i];

        // Get Up
        rhop = w[0];
        up = -u[0]/rho*w[0]+1/rho*w[1];
        vp = -u[1]/rho*w[0]+1/rho*w[2];
        Tp = 1/rho*(u[0]*u[0]*gamma*gamma - u[0]*u[0]*gamma +
                    u[1]*u[1]*gamma*gamma-u[1]*u[1]*gamma-2.0*T)*w[0]/2.0
          -1/rho*u[0]*gamma*(gamma-1.0)*w[1]-1/rho*u[1]*gamma*(gamma-1.0)*w[2]
          +1/rho*gamma*(gamma-1.0)*w[3];

        // Form the new Up
        // rhop = rhop;
        tmp = (up*ny[i] - vp*nx[i])*ny[i];
        vp  = (vp*nx[i] - up*ny[i])*nx[i];
        up = tmp;
        // Tp = Tp;

        // Form Quasi U = M*Up
        B[0]->u[i] = rhop;
        B[1]->u[i] = u[0]*rhop+rho*up;
        B[2]->u[i] = u[1]*rhop+rho*vp;
        B[3]->u[i] = (T/gamma/(gamma-1.0) + u[0]*u[0]/2.0+u[1]*u[1]/2.0)*rhop
          + rho*u[0]*up + rho*u[1]*vp + rho/gamma/(gamma-1.0)*Tp;

      }
    }
}

void LinEuler_quasi::LinWallBC::apply_flux( const Scalar t, const vField &F ) {
  error("LinEuler_quasi::LinWallBC::apply_flux(...) not implemented.");
}

void LinEuler_quasi::LinWallBC::adjoint_apply( const Scalar t,
                                               const vField &state,
                                               const vField &adjoint) {
  error("LinEuler_quasi::LinWallBC::adjoint_apply(...) not implemented.");
}

void LinEuler_quasi::LinWallBC::adjoint_apply_flux( const Scalar t,
                                                    const vField &state,
                                                    const vField &adjoint) {
  error("LinEuler_quasi::LinWallBC::adjoint_apply_flux(...) not implemented.");
}

//===========================================================================
//                              Sponge Source
//===========================================================================

/// Sponge boundary condition
class LinEuler_quasi::Sponge: public Source {
  int N;
  Scalar As;
  Scalar xs_b,xt_b,xs_t,xt_t,xs_l,xt_l,xs_r,xt_r;
  Scalar Ma_r, rho_r, T_r, U_r, V_r,E_r, p_r, c_r, gamma;
 public:
  Sponge( const string t, ifstream &in ) : Source(t,SPONGE) {
    // cout<<"Sponge( const string t, ifstream &in, "<<qtot<<")"<<endl;
    scan_lb(in);
    if (!(in >>N >> As >>xs_b>>xt_b>>xs_t>>xt_t>>xs_l>>xt_l>>xs_r>>xt_r
          >>Ma_r>>rho_r>>U_r>>V_r>>T_r))
      error("Sponge::Cannot read penalty and default value",-1);
    scan_rb(in);
    gamma=1.4;
    E_r = (rho_r*T_r/(gamma*(gamma-1.0)*Ma_r*Ma_r)
           + 0.5*rho_r*(U_r*U_r + V_r*V_r));
    p_r = E_r*(gamma-1.0);
    c_r = 1.0/Ma_r;
  }

  inline void apply(const Scalar, const vField &, vField & );
  inline void adjoint_apply(const Scalar, const vField &, const vField &,
                            vField &);
};

void LinEuler_quasi::Sponge::apply(const Scalar t, const vField &Us,
                                   vField &Ur ) {
  Element *S[4], *R[4];
  Scalar taus, x, y;
  Scalar spg[4];

  for (LocalSize e=0; e<Us[0]->ne; e++) {
    S[0] = Us[0]->el[e];  // local version of the state
    S[1] = Us[1]->el[e];
    S[2] = Us[2]->el[e];
    S[3] = Us[3]->el[e];

    R[0] = Ur[0]->el[e];  // local version of the LHS
    R[1] = Ur[1]->el[e];
    R[2] = Ur[2]->el[e];
    R[3] = Ur[3]->el[e];

    const Ordinal qtot = S[0]->qtot;

    for(LocalSize i=0;i<qtot;i++){
      x=S[0]->C->x[i];
      y=S[0]->C->y[i];

      // form the conservative_variable
      spg[0] = rho_r;//rho;
      spg[1] = U_r*rho_r;//u[0]*rho;
      spg[2] = V_r*rho_r;//u[1]*rho;
      spg[3] = E_r;

      // left
      if(xs_l<xt_l&& x<=xt_l){
        taus = As*pow((xt_l-x)/(xt_l-xs_l),N);
        R[0]->u[i]=R[0]->u[i] + taus*(S[0]->u[i]-spg[0]);
        R[1]->u[i]=R[1]->u[i] + taus*(S[1]->u[i]-spg[1]);
        R[2]->u[i]=R[2]->u[i] + taus*(S[2]->u[i]-spg[2]);
        R[3]->u[i]=R[3]->u[i] + taus*(S[3]->u[i]-spg[3]);
      }
      // right
      if(xs_r<xt_r&& x>=xs_l){
        taus = As*pow((x-xs_r)/(xt_r-xs_r),N);
        R[0]->u[i]=R[0]->u[i] + taus*(S[0]->u[i]-spg[0]);
        R[1]->u[i]=R[1]->u[i] + taus*(S[1]->u[i]-spg[1]);
        R[2]->u[i]=R[2]->u[i] + taus*(S[2]->u[i]-spg[2]);
        R[3]->u[i]=R[3]->u[i] + taus*(S[3]->u[i]-spg[3]);
      }
      // bottom
      if(xs_b<xt_b&& y<=xt_b){
        taus = As*pow((xt_b-y)/(xt_b-xs_b),N);
        R[0]->u[i]=R[0]->u[i] + taus*(S[0]->u[i]-spg[0]);
        R[1]->u[i]=R[1]->u[i] + taus*(S[1]->u[i]-spg[1]);
        R[2]->u[i]=R[2]->u[i] + taus*(S[2]->u[i]-spg[2]);
        R[3]->u[i]=R[3]->u[i] + taus*(S[3]->u[i]-spg[3]);
      }
      // top
      if(xs_t<xt_t&& y>=xs_t){
        taus = As*pow((y-xs_t)/(xt_t-xs_t),N);
        R[0]->u[i]=R[0]->u[i] + taus*(S[0]->u[i]-spg[0]);
        R[1]->u[i]=R[1]->u[i] + taus*(S[1]->u[i]-spg[1]);
        R[2]->u[i]=R[2]->u[i] + taus*(S[2]->u[i]-spg[2]);
        R[3]->u[i]=R[3]->u[i] + taus*(S[3]->u[i]-spg[3]);
      }
    }
  }
}

void LinEuler_quasi::Sponge::adjoint_apply(const Scalar t,
                                           const vField &state,
                                           const vField & adjoint,
                                           vField &Ur ) {
  Element *S[4], *R[4];
  Scalar taus, x, y;
  Scalar spg[4];

  for (LocalSize e=0; e<state[0]->ne; e++) {

    S[0] = adjoint[0]->el[e];  // local version of the state
    S[1] = adjoint[1]->el[e];
    S[2] = adjoint[2]->el[e];
    S[3] = adjoint[3]->el[e];

    R[0] = Ur[0]->el[e];  // local version of the LHS
    R[1] = Ur[1]->el[e];
    R[2] = Ur[2]->el[e];
    R[3] = Ur[3]->el[e];

    const Ordinal qtot = S[0]->qtot;

    for(LocalSize i=0;i<qtot;i++){
      x=S[0]->C->x[i];
      y=S[0]->C->y[i];

      // form the conservative_variable
      spg[0] = 0.0;
      spg[1] = 0.0;
      spg[2] = 0.0;
      spg[3] = 0.0;

      // left
      if(xs_l<xt_l&& x<=xt_l){
        taus = As*pow((xt_l-x)/(xt_l-xs_l),N);
        R[0]->u[i]=R[0]->u[i] - taus*(S[0]->u[i]-spg[0]);
        R[1]->u[i]=R[1]->u[i] - taus*(S[1]->u[i]-spg[1]);
        R[2]->u[i]=R[2]->u[i] - taus*(S[2]->u[i]-spg[2]);
        R[3]->u[i]=R[3]->u[i] - taus*(S[3]->u[i]-spg[3]);
      }
      // right
      if(xs_r<xt_r&& x>=xs_l){
        taus = As*pow((x-xs_r)/(xt_r-xs_r),N);
        R[0]->u[i]=R[0]->u[i] - taus*(S[0]->u[i]-spg[0]);
        R[1]->u[i]=R[1]->u[i] - taus*(S[1]->u[i]-spg[1]);
        R[2]->u[i]=R[2]->u[i] - taus*(S[2]->u[i]-spg[2]);
        R[3]->u[i]=R[3]->u[i] - taus*(S[3]->u[i]-spg[3]);
      }
      // bottom
      if(xs_b<xt_b&& y<=xt_b){
        taus = As*pow((xt_b-y)/(xt_b-xs_b),N);
        R[0]->u[i]=R[0]->u[i] - taus*(S[0]->u[i]-spg[0]);
        R[1]->u[i]=R[1]->u[i] - taus*(S[1]->u[i]-spg[1]);
        R[2]->u[i]=R[2]->u[i] - taus*(S[2]->u[i]-spg[2]);
        R[3]->u[i]=R[3]->u[i] - taus*(S[3]->u[i]-spg[3]);
      }
      // top
      if(xs_t<xt_t&& y>=xs_t){
        taus = As*pow((y-xs_t)/(xt_t-xs_t),N);
        R[0]->u[i]=R[0]->u[i] - taus*(S[0]->u[i]-spg[0]);
        R[1]->u[i]=R[1]->u[i] - taus*(S[1]->u[i]-spg[1]);
        R[2]->u[i]=R[2]->u[i] - taus*(S[2]->u[i]-spg[2]);
        R[3]->u[i]=R[3]->u[i] - taus*(S[3]->u[i]-spg[3]);
      }
    }
  }
}

} // namespace Reo

#endif  // REO_LINEULER_QUASI_BC_HPP
