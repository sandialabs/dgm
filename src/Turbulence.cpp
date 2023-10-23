/** \file Turbulence.cpp
    \brief Implementation of sub-grid scale models
    \author Scott Collis
*/

// DGM includes
#include "String.hpp"

// local includes
#include "Turbulence.hpp"

namespace Reo {

/// Constructor
Turbulence::Turbulence( DGM::ArgList &args, const DGM::Comm::Ptr comm_ ) :
  Navier_Stokes(args,comm_) {
}

// turn off for now [ssc]
#if 0
void Turbulence::get_tot_viscosity( const vField &Us, dvector &mu_tot,
                                    const int k ) {
  Element *S[1];
  S[0] = Us[0]->el[k];
  const int qtot = S[0]->qtot;
  for (int i=0; i<qtot; i++) {
    mu_tot(i) = get_eddy_viscosity(i) + get_viscosity(i);
  }
}

Scalar Turbulence::get_eddy_viscosity(const int q) {
  Scalar mu_tau;
  mu_tau = 0.0;
  return mu_tau;
}

#endif

void Turbulence::get_viscosity( dVector &mu) {
  mu = vis;
}

// this should be the same as the Navier--Stokes for now [ssc]
#if 0
//===========================================================================
// Bassi-Rebay viscous flux
//===========================================================================
void Turbulence::diffusion( vField &Us, vField &Uf, vField &Ur ) {
  Element *S[4], *F[4];
  int qtot, n, k;
  dVector u, v, p, e, wk;

  // NOTE: I interpolate conservative vars.  One could also interpolate
  //       primitive it is likely better to interpolate primitive variables
  //       but, it is easier for me to interpolate conservative.

  Us.fill_sides();                   // put solution on the sides
  enforce_bc(Us);                    // update bc side values
  primitive_sides(Us);               // convert sides to primative variables
  Us.share_sides();                  // communicate sides if parallel
  average_flux( Us, Uf, '+' );       // Uf's sides are average state

  for (k=0; k<Us[0]->ne; k++) {

    S[0] = Us[0]->el[k];  // local version of the state
    S[1] = Us[1]->el[k];
    S[2] = Us[2]->el[k];
    S[3] = Us[3]->el[k];

    F[0] = Uf[0]->el[k];  // local version of the flux
    F[1] = Uf[1]->el[k];
    F[2] = Uf[2]->el[k];
    F[3] = Uf[3]->el[k];

    dVector r (S[0]->u);  // rho
    dVector ru(S[1]->u);  // rho u
    dVector rv(S[2]->u);  // rho v
    dVector E (S[3]->u);  // total energy per volume

    qtot = S[0]->qtot;
    dVector u(qtot);
    dVector v(qtot);
    dVector e(qtot);
    dVector wk(qtot);

    dvdiv(ru, r, u);   // u-velocity
    dvdiv(rv, r, v);   // v-velocity
    dvdiv(E,  r, e);   // internal energy + 0.5 |V|^2

    dvmul(u,u,wk);     // wk = u^2
    dvvtvp(v,v,wk,wk); // wk = u^2 + v^2
    daxpy(-0.5,wk,e);  // e  = e - 0.5 * wk = internal energy

    dVector ux(qtot);
    dVector uy(qtot);  dVector tau12(uy);  // note the alias
    dVector vx(qtot);  dVector tau11(vx);  // note the alias
    dVector vy(qtot);  dVector tau22(vy);  // note the alias

    gradient( S[1], F[1], u, ux, uy );
    gradient( S[2], F[2], v, vx, vy );

    //  This is where the viscosity needs to be adjusted
    //    wk = mu;  // constant viscosity for now

    get_tot_viscosity(Us, wk, k);

    // Viscous stress:  tau_{ij} = mu ( 2 S_{ij} - 2\delta_{ij}/3 u_{k,k} )
    dvadd(uy, vx, tau12);
    dvmul(wk, tau12);                // mu ( u_{,y} + v_{,x} )

    daxmy(2.0, ux, vy, tau11);       // 2 u_{,x} - v_{,y}
    scale(2.0/3.0, tau11);           // 2/3 ( 2 u_{,x} - v_{,y} )
    dvmul(wk, tau11);                // 2/3 mu ( 2 u_{,x} - v_{,y} )

    daxmy(2.0, vy, ux, tau22);       // 2 v_{,y} - u_{,x}
    scale(2.0/3.0, tau22);           // 2/3 ( 2 v_{,y} - u_{,x} )
    dvmul(wk, tau22);                // 2/3 mu ( 2 v_{,y} - u_{,x} )

    // x-momentum equation
    S[1]->fill_sides( tau11, tau12 );
    S[1]->gradient(tau11, ux, 'x');  // ux = tau_{11,1}
    S[1]->gradient(tau12, wk, 'y');  // wk = tau_{12,2}
    dvadd( ux, wk, F[1]->u );        // F[1]->u = tau_{11,1} + tau_{12,2}

    // y-momentum equation
    S[2]->fill_sides( tau12, tau22 );
    S[2]->gradient(tau12, ux, 'x');  // ux = tau_{21,1}
    S[2]->gradient(tau22, wk, 'y');  // wk = tau_{22,2}
    dvadd( ux, wk, F[2]->u );        // F[2]->u = tau_{21,1} + tau_{22,2}

    // dissipation: tau_11*u + tau_12*v in ux and tau_12*u + tau_22*v in uy
    dvmul (tau11,u,ux);
    dvvtvp(tau12,v,ux,ux);
    dvmul (tau12,u,uy);
    dvvtvp(tau22,v,uy,uy);

    // add in heat conduction (Note: mu*gamma/Pr = kappa/Cv)
    gradient( S[3], F[3], e, vx, vy );  // vx = e_{,x}, vy = e_{,y}
    daxpy(mu*gamma/Pr,vx,ux);
    daxpy(mu*gamma/Pr,vy,uy);

    // energy equation
    S[3]->fill_sides( ux, uy );
    S[3]->gradient(ux, wk, 'x'); // wk = (tau_{1j} u_j + k/Cv e_{,1})_{,1}
    S[3]->gradient(uy, ux, 'y'); // ux = (tau_{2j} u_j + k/Cv e_{,2})_{,2}
    dvadd( wk, ux, F[3]->u );    // F[3]->u = (tau_{ij} u_j + k/Cv e_{,i})_{,i}
  }

  Us.share_sides();                        // Share sides with your neighbors
  enforce_flux_bc(Us);                     // put flux BC's on bc sides
  average_flux( Us, Uf, '-' );

  // Note there is no contribution to the continuity equation
  for (n=1; n<Us.size(); n++) {
    for (k=0; k<Us[n]->ne; k++) {
      Element *S = Us[n]->el[k];
      Element *F = Uf[n]->el[k];
      S->lift( F, F->u ); // add side fluxes to interior
    }
  }

  // add in viscous contribution
  scale(-1.0,Uf);  // I currrently put everything on the LHS
  for (n=1; n<Uf.size(); n++) add( Uf[n], Ur[n] );
}
#endif

} // namespace Reo
