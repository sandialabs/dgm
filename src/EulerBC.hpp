#ifndef REO_EULERBC_HPP
#define REO_EULERBC_HPP

/** \file  EulerBC.hpp
    \brief Euler equation boundary conditions
    \author Scott Collis
*/

// DGM includes
#include "BC.hpp"
#include "Source.hpp"
#include "Ctrl.hpp"
#include "Ctrl.hpp"

using DGM::BC;
using DGM::Source;
using DGM::Ctrl;

namespace Reo {

//===========================================================================
//                              Solid Wall
//===========================================================================

/// Wall boundary condition for 2d Euler flows
class Euler::WallBC : public BC {
public:
  /// default constructor
  WallBC( const string t ) : BC(t) { }
  /// construct from an input file stream
  WallBC( const string t, ifstream &in) : BC(t) {
    scan_lb(in);
    scan_rb(in);
  }
  inline void apply( const Scalar, const vField & ) ;
  inline void apply_flux( const Scalar, const vField & ) ;

  inline void adjoint_apply( const Scalar, const vField &, const vField & ) ;
  inline void adjoint_apply_flux( const Scalar, const vField &,
                                  const vField & ) ;
};

void Euler::WallBC::apply( const Scalar t, const vField &F ) {
  vector<Side*> S(F.size()), B(F.size());
  for (LocalSize n=0; n<F[0]->nbc; ++n)   // loop over field boundaries
    if (F[0]->bc[n]->type == type ) {
      dVector &nx = F[0]->bc[n]->S->nx();
      dVector &ny = F[0]->bc[n]->S->ny();
      for (vField::size_type i=0; i<F.size(); ++i){
        S[i] = F[i]->bc[n]->S;
        B[i] = F[i]->bc[n]->B;
      }
      for (LocalSize i=0; i<S[0]->qtot(); ++i) {
        B[0]->u[i] = S[0]->u[i];
        B[1]->u[i] = (S[1]->u[i]*ny[i] - S[2]->u[i]*nx[i])*ny[i];
        B[2]->u[i] = (S[2]->u[i]*nx[i] - S[1]->u[i]*ny[i])*nx[i];
        B[3]->u[i] = S[3]->u[i]
          - 0.5*(S[1]->u[i]*S[1]->u[i] + S[2]->u[i]*S[2]->u[i])/S[0]->u[i]
          + 0.5*(B[1]->u[i]*B[1]->u[i] + B[2]->u[i]*B[2]->u[i])/B[0]->u[i];
      }
    }
}

/// this should not be called for pure Euler but is needed for EulerDC
void Euler::WallBC::apply_flux( const Scalar t, const vField &F ) {
  //cout << "Euler::WallBC::apply_flux(...)" << endl;
  for (LocalSize n=0; n<F[0]->nbc; ++n) {
    if (F[0]->bc[n]->type == type ) {
      for (vField::size_type i=0; i<F.size(); ++i) {
        for (LocalSize q=0; q<F[i]->bc[n]->S->qtot(); ++q)
          F[i]->bc[n]->B->u[q] = -F[i]->bc[n]->S->u[q];
      }
    }
  }
}


/// Implements \f$\lambda_n = \lambda_1 * nx + \lambda_2 * ny = 0 \f$
void Euler::WallBC::adjoint_apply( const Scalar t, const vField &state,
                                   const vField &adjoint) {
  vector<Side*> S(adjoint.size()), B(adjoint.size());
  for (LocalSize n=0; n<adjoint[0]->nbc; ++n)   // loop over field boundaries
    if (adjoint[0]->bc[n]->type == type) {
      dVector &nx = adjoint[0]->bc[n]->S->nx();
      dVector &ny = adjoint[0]->bc[n]->S->ny();
      for (vField::size_type i=0; i<adjoint.size(); ++i) {
        S[i] = adjoint[i]->bc[n]->S;
        B[i] = adjoint[i]->bc[n]->B;
      }
      for (LocalSize i=0; i<S[0]->qtot(); ++i) {
        B[0]->u[i] = S[0]->u[i];
        B[1]->u[i] = (S[1]->u[i]*ny[i] - S[2]->u[i]*nx[i])*ny[i];
        B[2]->u[i] = (S[2]->u[i]*nx[i] - S[1]->u[i]*ny[i])*nx[i];
        B[3]->u[i] = S[3]->u[i];
      }
    }
}


void Euler::WallBC::adjoint_apply_flux( const Scalar t, const vField &state,
                                        const vField &adjoint) {
  error("Euler::WallBC::adjoint_apply_flux() not implemented.");
}


//===========================================================================
//                        Subsonic Outflow BC
//===========================================================================

/// Subsonic outflow boundary condition
/** \todo Make gamma variable
    \todo Change to JSON input format
**/
class Euler::SubsonicOutflowBC : public BC {
public:
  SubsonicOutflowBC( const string t ) : BC(t), Mref(0.6) {
    Eref = one/(gamma*(gamma-one)*pow(Mref,2)) + pt5;
  }
  SubsonicOutflowBC( const string t, ifstream &in) : BC(t), Mref(0.6) {
    scan_lb(in);
    if ( !(in >>Mref) ) 
      error("Euler::SubsonicOutflowBC::Cannot read reference Mach value");
    scan_rb(in);
    Eref = one/(gamma*(gamma-one)*pow(Mref,2)) + pt5;
  }
  inline void apply( const Scalar, const vField & ) ;
  inline void apply_flux( const Scalar, const vField & ) ;

  inline void adjoint_apply( const Scalar, const vField &, const vField & ) ;
  inline void adjoint_apply_flux( const Scalar, const vField &,
                                  const vField & ) ;
private:
  const Scalar gamma = 1.4;  ///< Set value for ratio of specific heats
  Scalar Mref;               ///< Reference Mach number
  Scalar Eref;               ///< Reference Total Stagnation energy
};

void Euler::SubsonicOutflowBC::apply( const Scalar t, const vField &F ) {
  vector<Side*> S(F.size()), B(F.size());
  for (LocalSize n=0; n<F[0]->nbc; ++n)   // loop over field boundaries
    if (F[0]->bc[n]->type == type ) {
      //dVector &nx = F[0]->bc[n]->S->nx();
      //dVector &ny = F[0]->bc[n]->S->ny();
      for (vField::size_type i=0; i<F.size(); ++i) {
        S[i] = F[i]->bc[n]->S;
        B[i] = F[i]->bc[n]->B;
      }
      for (LocalSize i=0; i<S[0]->qtot(); ++i) {
        // const Scalar gamma = 1.4;
        // Eref = 1/(gamma*(gamma-1.0)*Ma**2) + 0.5
        // const Scalar Eref = 179.0714285714286;// SSC:added 9/17/21; Ma = 0.1
        // const Scalar Eref = 5.46031746031746; // SSC:original; Ma = 0.6
        const Scalar pref = (gamma-one)*(Eref - pt5*(one-zero));
        Scalar rl = S[0]->u[i];
        Scalar ml = S[1]->u[i];
        Scalar nl = S[2]->u[i];
        Scalar ul = ml/rl;
        Scalar vl = nl/rl;
        Scalar El = pref/(gamma-one)+pt5*(ml*ul+nl*vl);
        B[0]->u[i] = rl;
        B[1]->u[i] = ml;
        B[2]->u[i] = nl;
        B[3]->u[i] = El;
      }
    }
}

// this should not be called for pure Euler but is needed for EulerDC
void Euler::SubsonicOutflowBC::apply_flux( const Scalar t, const vField &F ) {
  //cout << "Euler::SubsonicOutflowBC::apply_flux(...)" << endl;
  for (LocalSize n=0; n<F[0]->nbc; ++n) {
    if (F[0]->bc[n]->type == type ) {
      for (vField::size_type i=0; i<F.size(); ++i) {
        for (LocalSize q=0; q<F[i]->bc[n]->S->qtot(); ++q)
          F[i]->bc[n]->B->u[q] = -F[i]->bc[n]->S->u[q];
      }
    }
  }
}

void Euler::SubsonicOutflowBC::adjoint_apply( const Scalar t,
                                              const vField &state,
                                              const vField &adjoint) {
  error("Euler::SubsonicOutflowBC::adjoint_apply(...) not implemented.");
}


void Euler::SubsonicOutflowBC::adjoint_apply_flux( const Scalar t,
                                                   const vField &state,
                                                   const vField &adjoint) {
  error("Euler::SubsonicOutflowBC::adjoint_apply_flux() not implemented.");
}

//===========================================================================
//                        Supersonic Outflow BC
//===========================================================================

/// Supersonic outflow boundary condition
class Euler::SupersonicOutflowBC : public BC {
public:
  SupersonicOutflowBC( const string t ) : BC(t) { }
  SupersonicOutflowBC( const string t, ifstream &in) : BC(t) {
    scan_lb(in);
    scan_rb(in);
  }
  inline void apply( const Scalar, const vField & ) ;
  inline void apply_flux( const Scalar, const vField & ) ;

  inline void adjoint_apply( const Scalar, const vField &, const vField & ) ;
  inline void adjoint_apply_flux( const Scalar, const vField &,
                                  const vField & ) ;
};

void Euler::SupersonicOutflowBC::apply( const Scalar t, const vField &F ) {
  vector<Side*> S(F.size()), B(F.size());
  for (LocalSize n=0; n<F[0]->nbc; ++n)   // loop over field boundaries
    if (F[0]->bc[n]->type == type ) {
      //dVector &nx = F[0]->bc[n]->S->nx();
      //dVector &ny = F[0]->bc[n]->S->ny();
      for (vField::size_type i=0; i<F.size(); ++i) {
        S[i] = F[i]->bc[n]->S;
        B[i] = F[i]->bc[n]->B;
      }
      for (LocalSize i=0; i<S[0]->qtot(); ++i) {
        //Scalar gamma = 1.4;
        //Scalar Eref = 5.46031746031746;  // Ma = 0.6
        //Scalar pref = (gamma-one)*(Eref - pt5*(one-zero));
        //Scalar rl = S[0]->u[i];
        //Scalar ml = S[1]->u[i];
        //Scalar nl = S[2]->u[i];
        //Scalar ul = ml/rl;
        //Scalar vl = nl/rl;
        //Scalar El = pref/(gamma-one)+pt5*(ml*ul+nl*vl);
        B[0]->u[i] = S[0]->u[i];
        B[1]->u[i] = S[1]->u[i];
        B[2]->u[i] = S[2]->u[i];
        B[3]->u[i] = S[3]->u[i];
      }
    }
}

// this should not be called for pure Euler but is needed for EulerDC
void Euler::SupersonicOutflowBC::apply_flux( const Scalar t,
                                             const vField &F ) {
  //cout << "Euler::SupersonicOutflowBC::apply_flux(...)" << endl;
  for (LocalSize n=0; n<F[0]->nbc; ++n) {
    if (F[0]->bc[n]->type == type ) {
      for (vField::size_type i=0; i<F.size(); ++i) {
        for (LocalSize q=0; q<F[i]->bc[n]->S->qtot(); ++q)
          F[i]->bc[n]->B->u[q] = -F[i]->bc[n]->S->u[q];
      }
    }
  }
}

void Euler::SupersonicOutflowBC::adjoint_apply( const Scalar t,
                                              const vField &state,
                                              const vField &adjoint) {
  error("Euler::SupersonicOutflowBC::adjoint_apply(...) not implemented.");
}


void Euler::SupersonicOutflowBC::adjoint_apply_flux( const Scalar t,
                                                   const vField &state,
                                                   const vField &adjoint) {
  error("Euler::SupersonicOutflowBC::adjoint_apply_flux() not implemented.");
}

//===========================================================================
//                       Wall-Normal Linear Control
//===========================================================================

/// linear control boundary condition
class Euler::LinearControlBC : public BC, public Ctrl {
  Scalar value;
  Scalar Ma_r, rho_r, T_r, U_r, E_r, p_r, c_r, gamma;
  vField *Fphi;  // internal copy for the geometry operation [gqchen]
public:
  LinearControlBC( const string t, ifstream &in, vField *F,
                   const Scalar gamma_)
    : BC(t), gamma(gamma_), Fphi(F) {
    DGM::Comm::World->cout()<<"Euler::LinearControlBC()"<<endl;
    scan_lb(in);
#ifndef DGM_USE_TIME_REG
    if (!(in >> penalty >> Ma_r >> rho_r >> T_r >> U_r))
      error("Euler::LinearControlBC: Ma_r, rho_r, T_r, U_r");
#else
    if (!(in >> penalty >> penalty_t >> Ma_r >> rho_r >> T_r >> U_r))
      error("Euler::LinearControlBC: penalty,penalty_t,Ma_r,rho_r,T_r,U_r");
#endif
    scan_rb(in);
    value = 0; // default control
    E_r = (rho_r*T_r/(gamma*(gamma-1.0)*Ma_r*Ma_r) - 0.5*rho_r*(U_r*U_r));
    p_r = E_r*(gamma-1.0);
    c_r = 1.0/Ma_r;
  }

  inline void apply( const Scalar t, const vField & ) ;
  inline void apply_flux( const Scalar t, const vField & );

  inline void adjoint_apply( const Scalar t, const vField &, const vField & );
  inline void adjoint_apply_flux( const Scalar t, const vField &,
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

// The following boundary enforcement is based on the isentropic and
// iso-vorticity blowing/suction and linearized Euler boundary (zero mean flow)
// [gqchen]
void Euler::LinearControlBC::apply( const Scalar t, const vField &F ) {
  vector<Side*> S(F.size()), B(F.size());
  if (data.size()==0) {
    // WARNING:: this assumes that the uncontrolled flow has v_n=0
    for (LocalSize n=0; n<F[0]->nbc; ++n)   // loop over field boundaries
      if (F[0]->bc[n]->type == type ) {
        dVector &nx = F[0]->bc[n]->S->nx();
        dVector &ny = F[0]->bc[n]->S->ny();
        for (vField::size_type i=0; i<F.size(); ++i){
          S[i] = F[i]->bc[n]->S;
          B[i] = F[i]->bc[n]->B;
        }
        for (LocalSize i=0; i<S[0]->qtot(); ++i) {
          B[0]->u[i] = S[0]->u[i];
          B[1]->u[i] = (S[1]->u[i]*ny[i] - S[2]->u[i]*nx[i])*ny[i];
          B[2]->u[i] = (S[2]->u[i]*nx[i] - S[1]->u[i]*ny[i])*nx[i];
          B[3]->u[i] = S[3]->u[i]
            - 0.5*(S[1]->u[i]*S[1]->u[i] + S[2]->u[i]*S[2]->u[i])/S[0]->u[i]
            + 0.5*(B[1]->u[i]*B[1]->u[i] + B[2]->u[i]*B[2]->u[i])/B[0]->u[i];
        }
      }
  } else {
    Scalar rho, p, u[2], phi_in[4];
    int offset=0;
    dVector g;
    for (LocalSize n=0; n<F[0]->nbc; ++n) {  // loop over field boundaries
      if (F[0]->bc[n]->type == type ){
        dVector &nx = F[0]->bc[n]->S->nx();
        dVector &ny = F[0]->bc[n]->S->ny();
        for (vField::size_type i=0; i<F.size(); ++i) {
          S[i] = F[i]->bc[n]->S;
          B[i] = F[i]->bc[n]->B;
        }
        g.alias( *(const_cast<dVector*>(&data)), offset, S[0]->qtot());

        if ( g.size() != S[0]->qtot() )
#if 1
          error("Euler::LinearControlBC::apply() control data wrong size");
#else
        // do some projection here,two ways to project [gqchen]
        // 1) use the G->G interpolate
        // 2) base on the edge modes
#endif
        for (LocalSize i=0; i<S[0]->qtot(); i++) {

            if(g[i]<0){                                   // blowing
            rho  = S[0]->u[i] - rho_r;                  // rho'
            u[0] = S[1]->u[i]/S[0]->u[i] - U_r*nx[i];   // u'
            u[1] = S[2]->u[i]/S[0]->u[i] - U_r*ny[i];   // v'
            p = (S[3]->u[i]-0.5*(u[0]*u[0]+u[1]*u[1])
                 *S[0]->u[i])*(gamma-1.0)-p_r;          // p'

            phi_in[0] =  nx[i]*rho_r*c_r*u[0] + ny[i]*rho_r*c_r*u[1] + p;
            phi_in[1] = -nx[i]*rho_r*c_r*u[0] - ny[i]*rho_r*c_r*u[1] + p;
            phi_in[2] =  rho - p/(c_r*c_r);
            phi_in[3] = -ny[i]*u[0] + nx[i]*u[1];

            p    = phi_in[0] - rho_r*c_r*g[i];
            rho  = p/(c_r*c_r);
            u[0] = g[i] * nx[i];
            u[1] = g[i] * ny[i];

            B[0]->u[i] = rho + rho_r;
            B[1]->u[i] = B[0]->u[i] * u[0];
            B[2]->u[i] = B[0]->u[i] * u[1];
            B[3]->u[i] = (p + p_r)/(gamma-1.0)
              + 0.5*( B[1]->u[i]*B[1]->u[i] + B[2]->u[i]*B[2]->u[i] )
              / B[0]->u[i];
          } else {                                       // suction
            B[0]->u[i] = S[0]->u[i];
            B[1]->u[i] = B[0]->u[i]*g[i] * nx[i]
              +(S[1]->u[i]*ny[i] - S[2]->u[i]*nx[i])*ny[i];
            B[2]->u[i] = B[0]->u[i]*g[i] * ny[i]
              +(S[2]->u[i]*nx[i] - S[1]->u[i]*ny[i])*nx[i];
            B[3]->u[i] = S[3]->u[i]
              - 0.5*(S[1]->u[i]*S[1]->u[i]+S[2]->u[i]*S[2]->u[i] )/S[0]->u[i]
              + 0.5*(B[1]->u[i]*B[1]->u[i]+B[2]->u[i]*B[2]->u[i] )/B[0]->u[i];
          }
        }
        offset += S[0]->qtot();
      }
    }
  }
}

void Euler::LinearControlBC::apply_flux( const Scalar t, const vField &F ) {
  error("Euler::LinearControlBC::apply_flux() not implemented.");
}

// needs work [gqchen]
void Euler::LinearControlBC::adjoint_apply( const Scalar t,
                                            const vField &state,
                                            const vField &adjoint) {
  const LocalSize Nfields = adjoint.size();
  vector<Side*> S(Nfields), B(Nfields),SS(Nfields);
  Scalar rho,u[2],T,H;
  dVector lam(4),phi_in(4),phi_bc(4);
  Scalar n1,n2;
  Scalar s1,s2;

  //int offset=0;
  // dVector g;
  Scalar g;
  for (LocalSize n=0; n<state[0]->nbc; ++n)   // loop over field boundaries
    if (state[0]->bc[n]->type == type ){
      dVector &nx = state[0]->bc[n]->S->nx();
      dVector &ny = state[0]->bc[n]->S->ny();

      for (LocalSize i=0; i<Nfields; ++i){
        S[i] = adjoint[i]->bc[n]->S;
        B[i] = adjoint[i]->bc[n]->B;
        SS[i]= state[i]->bc[n]->S;
      }
#if 0
      g.alias( *(const_cast<dVector*>(&data)), offset,
               adjoint[0]->bc[n]->S->qtot() );

      if (g.size() != S[0]->qtot() )
#if 1
        error("Euler::LinearControlBC::apply() control data wrong size");
#else
      // do some projection here,two ways to project [gqchen]
      // 1) use the G->G interpolate
      // 2) base on the edge modes
#endif
#endif
      if (SS[0]->qtot() != S[0]->qtot() )
#if 1
        error("Euler::LinearControlBC::apply() state adjoint side size Wrong");
#else
      // Project the State side => Adjoint side
      // do some projection here,two ways to project [gqchen]
      // 1) use the G->G interpolate
      // 2) base on the edge modes
#endif
      const LocalSize qtot = S[0]->qtot();
      // here c_r seem to use the local sound instead of the mean flow sound??
      for (LocalSize i=0; i<qtot; i++) {
        g = (SS[1]->u[i]*nx[i] + SS[2]->u[i]*ny[i])/SS[0]->u[i];

        rho    = SS[0]->u[i];     // rho
        u[0]   = SS[1]->u[i]/rho; // u
        u[1]   = SS[2]->u[i]/rho; // v
        T      = (SS[3]->u[i]/rho-0.5*(u[0]*u[0]+u[1]*u[1])) *
                 (gamma-1.0)*gamma*Ma_r*Ma_r;
        H = SS[3]->u[i]/rho + T/(gamma*Ma_r*Ma_r);

        n1 = nx[i]; n2 = ny[i];

        for(int j=0;j<4;j++)
          lam[j] = S[j]->u[i];

        phi_in[0] = lam[0]+u[0]*lam[1]+u[1]*lam[2]+lam[3]*u[0]*u[0]/2.0
          +lam[3]*u[1]*u[1]/2.0;
        phi_in[1] = rho*n2*lam[1]-rho*n1*lam[2]+rho*lam[3]*u[0]*n2
          -rho*lam[3]*u[1]*n1;
        phi_in[2] = rho*(lam[0]+u[0]*lam[1]+lam[1]*c_r*n1+u[1]*lam[2]
                         +lam[2]*c_r*n2+lam[3]*H +lam[3]*c_r*u[0]*n1
                         +lam[3]*c_r*u[1]*n2)/c_r/2.0;
        phi_in[3] = -rho*(-lam[0]-u[0]*lam[1]+lam[1]*c_r*n1-u[1]*lam[2]
                          +lam[2]*c_r*n2-lam[3]*H + lam[3]*c_r*u[0]*n1
                          +lam[3]*c_r*u[1]*n2)/c_r/2.0;

        if(g<0) { // blowing
          phi_bc[0] = phi_in[0];
          phi_bc[1] = 0.0;
          phi_bc[3] = phi_in[3];
          phi_bc[2] = (c_r-g)*phi_bc[3]/(g+c_r);

        }
        else { // suction
          phi_bc[0] =0.0;
          phi_bc[1] =0.0;
          phi_bc[3] = phi_in[3];
          phi_bc[2] = (c_r-g)*phi_bc[3]/(g+c_r);
        }

        s2 = phi_bc[1]*u[0]*u[0]*u[0]*n2+n1*phi_bc[2]*u[0]*u[0]*u[0]
          +phi_bc[2]*u[0]*u[0]*n2*u[1]-n1*phi_bc[1]*u[1]*u[1]*u[1]
          +2.0*n1*H*phi_bc[1]*u[1]+n1*phi_bc[2]*u[0]*u[1]*u[1]
          -2.0*n1*H*phi_bc[2]*u[0]-n1*phi_bc[3]*u[0]*u[1]*u[1]
          +n1*n1*phi_bc[2]*c_r*u[0]*u[0] + phi_bc[3]*u[0]*u[0]*n2*n2*c_r
          -2.0*phi_bc[0]*rho*n2*n2*u[1]*u[1]-phi_bc[3]*u[0]*u[0]*n2*u[1]
          +2.0*H*phi_bc[0]*rho*n2*n2+2.0*H*phi_bc[3]*n2*u[1]
          -2.0*n1*n1*phi_bc[0]*rho*u[1]*u[1]
          -2.0*n1*n1*phi_bc[0]*rho*u[0]*u[0];
        s1 = s2+2.0*n1*n1*H*phi_bc[0]*rho-n1*phi_bc[1]*u[1]*u[0]*u[0]
          +2.0*n1*H*phi_bc[3]*u[0] + n1*n1*phi_bc[2]*c_r*u[1]*u[1]
          +n1*n1*phi_bc[3]*c_r*u[0]*u[0]+phi_bc[1]*u[0]*n2*u[1]*u[1]
          +phi_bc[2]*u[0]*u[0]*n2*n2*c_r-2.0*phi_bc[0]*rho*n2*n2*u[0]*u[0]
          +phi_bc[2]*c_r*n2*n2*u[1]*u[1] - 2.0*H*phi_bc[1]*u[0]*n2
          +phi_bc[2]*u[1]*u[1]*u[1]*n2-phi_bc[3]*n2*u[1]*u[1]*u[1]
          +n1*n1*phi_bc[3]*c_r*u[1]*u[1] - 2.0*H*phi_bc[2]*u[1]*n2
          +phi_bc[3]*u[1]*u[1]*n2*n2*c_r-n1*phi_bc[3]*u[0]*u[0]*u[0];
        s2 = 1/rho/(-u[1]*u[1]*n2*n2+2.0*n2*n2*H-u[0]*u[0]*n1*n1
                    -u[0]*u[0]*n2*n2+2.0*n1*n1*H-u[1]*u[1]*n1*n1);
        B[0]->u[i] = s1*s2;
        B[1]->u[i] = -(2.0*n1*n1*phi_bc[3]*c_r*u[0]
                       -2.0*n1*n1*u[0]*phi_bc[0]*rho
                       +2.0*n1*n1*phi_bc[2]*c_r*u[0] - 2.0*n1*H*phi_bc[2]
                       +2.0*n1*H*phi_bc[3]+n1*phi_bc[2]*u[0]*u[0]
                       -n1*phi_bc[3]*u[0]*u[0] - n1*phi_bc[3]*u[1]*u[1]
                       +n1*phi_bc[2]*u[1]*u[1]-2.0*u[0]*phi_bc[0]*rho*n2*n2
                       +n2*phi_bc[1]*u[0]*u[0]-2.0*H*n2*phi_bc[1]
                       +n2*phi_bc[1]*u[1]*u[1]+2.0*phi_bc[2]*c_r*u[0]*n2*n2
                       +2.0*phi_bc[3]*c_r*u[0]*n2*n2)/rho
          /(-u[1]*u[1]*n2*n2 +2.0*n2*n2*H-u[0]*u[0]*n1*n1-u[0]*u[0]*n2*n2
            +2.0*n1*n1*H-u[1]*u[1]*n1*n1);
        B[2]->u[i] = -(2.0*n1*n1*phi_bc[3]*c_r*u[1]
                       +2.0*n1*n1*phi_bc[2]*u[1]*c_r
                       -2.0*n1*n1*u[1]*phi_bc[0]*rho+2.0*n1*H*phi_bc[1]
                       -n1*phi_bc[1]*u[1]*u[1]-n1*phi_bc[1]*u[0]*u[0]
                       +2.0*H*phi_bc[3]*n2-2.0*u[1]*phi_bc[0]*rho*n2*n2
                       -2.0*H*n2*phi_bc[2] + phi_bc[2]*n2*u[0]*u[0]
                       +n2*phi_bc[2]*u[1]*u[1]-phi_bc[3]*n2*u[0]*u[0]
                       +2.0*phi_bc[3]*c_r*u[1]*n2*n2 - phi_bc[3]*n2*u[1]*u[1]
                       +2.0*phi_bc[2]*c_r*u[1]*n2*n2)/rho
          /(-u[1]*u[1]*n2*n2 +2.0*n2*n2*H-u[0]*u[0]*n1*n1-u[0]*u[0]*n2*n2
            +2.0*n1*n1*H -u[1]*u[1]*n1*n1);
        B[3]->u[i] = 2.0*(-phi_bc[0]*rho+phi_bc[2]*c_r
                          +phi_bc[3]*c_r)/(-u[0]*u[0]+2.0*H-u[1]*u[1])/rho;
      }
      // offset += qtot;
    }
}

void Euler::LinearControlBC::adjoint_apply_flux( const Scalar t,
                                                 const vField &state,
                                                 const vField &adjoint ) {
  error("Euler::LinearControlBC::adjoint_apply_flux() not implemented.");
}

// I have to get a local copy of State vField to compute L2 norm [gqchen]
Scalar Euler::LinearControlBC::inner_product( const dVector &Y ) const {
  dVector ta,tb,tab;
  LocalSize offset=0;
  Scalar sum=0.0;
  for (LocalSize n=0; n<(*Fphi)[0]->nbc; ++n)   // loop over field boundaries
    if ((*Fphi)[0]->bc[n]->type == type ){
      const LocalSize qtot = (*Fphi)[0]->bc[n]->S->qtot();
      const LocalSize sid = (*Fphi)[0]->bc[n]->sid;
      ta.alias(data,offset,qtot);
      tb.alias(Y,offset,qtot);
      tab.resize(qtot);
      dvmul(ta, tb, tab);
      offset += qtot;
      sum +=(*Fphi)[0]->bc[n]->elmt->compute_side_integral(tab,sid);
      // cout<<"n="<<n<<" "<<sum<<endl;
    }
  // cout<<"sum="<<sum<<endl;
  return sum;
}


void Euler::LinearControlBC::set_direction( dVector &out ) {
  if (data.size()==0) return;
  assert( data_size() == out.size() );
  out = data = 1.0;
}


void Euler::LinearControlBC::objective_function_gradient(
    const vField &state, const vField &adjoint, const Scalar time,
    dVector &grad ) const
{
  if (data.size()==0) return;
  Scalar r, u, v, un, T, H;
  Scalar lam[4], phi[4];
  Ordinal offset=0;
  dVector dv, gv;
  for (LocalSize n=0; n<state[0]->nbc; ++n)   // loop over field boundaries
    if (state[0]->bc[n]->type == type) {

      // state and adjoint must have compatible sides
      assert( state[0]->bc[n]->S->qtot() == adjoint[0]->bc[n]->S->qtot() );

      dv.alias( *(const_cast<dVector*>(&data)), offset,
                state[0]->bc[n]->S->qtot() );

      gv.alias( *(const_cast<dVector*>(&grad)), offset,
                state[0]->bc[n]->S->qtot() );

      const LocalSize qtot = state[0]->bc[n]->S->qtot();
      const LocalSize sid = state[0]->bc[n]->sid;

      // Temporary fix for Euler [gqchen]
      for (vField::size_type j=0; j<state.size(); j++) {
        state[j]->bc[n]->elmt->fill_sides(state[j]->bc[n]->elmt->u);
        adjoint[j]->bc[n]->elmt->fill_sides(adjoint[j]->bc[n]->elmt->u);
      }

      dVector &nx = state[0]->bc[n]->elmt->side[sid]->nx();
      dVector &ny = state[0]->bc[n]->elmt->side[sid]->ny();

      for (LocalSize j=0; j<qtot; j++) {
        r = state[0]->bc[n]->S->u[j];
        u = state[1]->bc[n]->S->u[j]/r;
        v = state[2]->bc[n]->S->u[j]/r;
        T = ( state[3]->bc[n]->S->u[j]/r -
              0.5*(u*u+v*v) ) * (gamma-1.0)*gamma*Ma_r*Ma_r;
        un = u*nx[j] + v*ny[j];
        H = state[3]->bc[n]->S->u[j]/r + T/(gamma*Ma_r*Ma_r);

        for(int k=0; k<4; k++) lam[k] = adjoint[k]->bc[n]->S->u[j];

        phi[2] = r*(lam[0]+u*lam[1]+lam[1]*c_r*nx[j]+v*lam[2]+lam[2]*c_r*ny[j]
                    +lam[3]*H + lam[3]*c_r*u*nx[j]+lam[3]*c_r*v*ny[j])/c_r/2.0;
        phi[3] = -r*(-lam[0]-u*lam[1] + lam[1]*c_r*nx[j]-v*lam[2]
                     + lam[2]*c_r*ny[j]-lam[3]*H + lam[3]*c_r*u*nx[j]
                     +lam[3]*c_r*v*ny[j])/c_r/2.0;

        gv[j] = penalty*dv[j] - (un-c_r)*phi[3] + (un+c_r)*phi[2];
        // cout<<"n ="<<n<<"q ="<<j<<" grad "<<gv[j]<<endl;
      }
      offset+=qtot;
    }
}

void Euler::LinearControlBC::plot( const vField &state, const Size goffset,
                                   const dVector &Gphi,
                                   const Ordinal npredict,
                                   const Ordinal ntout,
                                   const Ordinal nsstep,
                                   const Ordinal riter) const {
  const Ordinal offset = numeric_cast<Ordinal>(goffset);
  dVector dv;
  char tmp[30];
  string fname;
  for(Ordinal i=0; i<=npredict; i+=ntout){ //4 is nsstep for RK4
    fname="euler_linear_control";
    sprintf(tmp,"%lld_%lld.dat",(long long)i,(long long)riter);
    fname = fname + tmp;
    FILE *opt_stat = fopen(fname.c_str(),"w");
    fprintf(opt_stat, "Euler Linear Control  @ %lld step\n",(long long)i);
    dv.alias( *(const_cast<dVector*>(&Gphi)),
              offset+(nsstep*i)*data_size(), data_size() );
    LocalSize np = 0;
    for (LocalSize n=0; n<state[0]->nbc; n++) {  // loop over state boundaries
      if (state[0]->bc[n]->type == type ) {
        const LocalSize sid = state[0]->bc[n]->sid;
        const LocalSize qtot = state[0]->bc[n]->S->qtot();
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

/// Steady linear control boundary condition
class Euler::SteadyLinearControlBC : public LinearControlBC {
 public:
  SteadyLinearControlBC(const string t, ifstream &in, vField *F,
                  const Scalar gamma_) : LinearControlBC(t,in,F,gamma_)  { }
  bool steady() const {return true;}
};

//===========================================================================
//                      Wall-Normal General Control
//===========================================================================

/// Wall-normal control boundary condition
/*! \todo This needs to be updated to DGM v1.0 standard */
class Euler::ControlBC : public BC, public Ctrl {
  Scalar value;    ///< data value
  //Scalar gamma;  ///< ratio of specific heats
  Scalar Ma;       ///< reference Mach number
  //vField *Fphi;  ///< internal copy for the geometry operation [gqchen]
public:
  ControlBC( const string t, ifstream &in, vField *F, const Scalar gamma_) :
    BC(t),
    value(0),
    //gamma(gamma_),
    Ma(0.0)
    //Fphi(F)
  {
    DGM::Comm::World->cout()<<"Euler::ControlBC()"<<endl;
    scan_lb(in);
    if (!(in >> penalty >> Ma)) error("Euler::ControlBC: Ma");
    scan_rb(in);
    value = 0.0;
  }

  inline void apply( const Scalar t, const vField & ) ;
  inline void apply_flux( const Scalar t, const vField & );

  inline void adjoint_apply( const Scalar t, const vField &, const vField & );
  inline void adjoint_apply_flux( const Scalar t, const vField &,
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

void Euler::ControlBC::apply( const Scalar t, const vField &F ) {
#if 1
  error("Euler::ControlBC:::apply() not implemented.");
#else
  vector<Side*> S(F.size()), B(F.size());
  if (data.size()==0) {
    vector<Side*> S(F.size()), B(F.size());
    for (int n=0; n<F[0]->nbc; ++n)   // loop over field boundaries
      if (F[0]->bc[n]->type == type ) {
        dVector &nx = F[0]->bc[n]->S->nx();
        dVector &ny = F[0]->bc[n]->S->ny();
        for (int i=0; i<F.size(); ++i){
          S[i] = F[i]->bc[n]->S;
          B[i] = F[i]->bc[n]->B;
        }
        for (int i=0; i<S[0]->qtot(); ++i) {
          B[0]->u[i] = S[0]->u[i];
          B[1]->u[i] = (S[1]->u[i]*ny[i] - S[2]->u[i]*nx[i])*ny[i];
          B[2]->u[i] = (S[2]->u[i]*nx[i] - S[1]->u[i]*ny[i])*nx[i];
          B[3]->u[i] = S[3]->u[i]
            - 0.5*(S[1]->u[i]*S[1]->u[i] + S[2]->u[i]*S[2]->u[i])/S[0]->u[i]
            + 0.5*(B[1]->u[i]*B[1]->u[i] + B[2]->u[i]*B[2]->u[i])/B[0]->u[i];
        }
      }
  } else {
    int offset=0;
    dVector g;
    for (int n=0; n<F[0]->nbc; ++n) {  // loop over field boundaries
      if (F[0]->bc[n]->type == type ){
        dVector &nx = F[0]->bc[n]->S->nx();
        dVector &ny = F[0]->bc[n]->S->ny();
        for (int i=0; i<F.size(); ++i) {
          S[i] = F[i]->bc[n]->S;
          B[i] = F[i]->bc[n]->B;
        }
        g.alias( *(const_cast<dVector*>(&data)), offset, S[0]->qtot());

        if (g.size() != S[0]->qtot() )
          error("Euler::ControlBC::apply() control data wrong size");

        for (int i=0; i<S[0]->qtot(); i++) {
          if(g[i]>=0){        //suction
            B[0]->u[i] = S[0]->u[i];
            B[1]->u[i] = ( S[1]->u[i]*ny[i] - S[2]->u[i]*nx[i])*ny[i]
              + S[0]->u[i]*g[i]*nx[i];
            B[2]->u[i] = ( S[2]->u[i]*nx[i] - S[1]->u[i]*ny[i])*nx[i]
              + S[0]->u[i]*g[i]*ny[i] ;
            B[3]->u[i] = S[3]->u[i]
              - 0.5*(S[1]->u[i]*S[1]->u[i] + S[2]->u[i]*S[2]->u[i])/S[0]->u[i]
              + 0.5*(B[1]->u[i]*B[1]->u[i] + B[2]->u[i]*B[2]->u[i])/B[0]->u[i];
          }
          else{  //blowing with mean flow information rho_m =1.0,T_m=1.0
            B[0]->u[i] = 1.0;
            B[1]->u[i] = ( S[1]->u[i]*ny[i] - S[2]->u[i]*nx[i])*ny[i]
              + S[0]->u[i]*g[i]*nx[i];
            B[2]->u[i] = ( S[2]->u[i]*nx[i] - S[1]->u[i]*ny[i])*nx[i]
              + S[0]->u[i]*g[i]*ny[i] ;
            B[3]->u[i] = 1.0*1.0/(gamma*(gamma-1.0)*Ma*Ma)
              + 0.5*(B[1]->u[i]*B[1]->u[i] + B[2]->u[i]*B[2]->u[i])/B[0]->u[i];

          }
        }
        offset += S[0]->qtot();
      }
    }
  }
#endif
}

void Euler::ControlBC::apply_flux( const Scalar t, const vField &F ) {
  error("Euler::ControlBC:::apply_flux() not implemented.");
}

void Euler::ControlBC::adjoint_apply( const Scalar t, const vField &state,
                                      const vField &adjoint) {
#if 1
  error("Euler::ControlBC:::adjoint_apply() not implemented.");
#else
  int Nfields = adjoint.size();
  vector<Side*> S(Nfields), B(Nfields),SS(Nfields);
  Scalar r,ru,rv,E,Vn,Vs;
  dVector lamb(Nfields);

  int offset=0;
  for (int n=0; n<state[0]->nbc; ++n)   // loop over field boundaries
    if (state[0]->bc[n]->type == type ){
      dVector &nx = state[0]->bc[n]->S->nx();
      dVector &ny = state[0]->bc[n]->S->ny();

      for (int i=0; i<Nfields; ++i){
        S[i] = adjoint[i]->bc[n]->S;
        B[i] = adjoint[i]->bc[n]->B;
        SS[i]= state[i]->bc[n]->S;
      }
      if (SS[0]->qtot() != S[0]->qtot() )
        error("Euler::ControlBC::apply() state adjoint side size Wrong");

      int qtot = S[0]->qtot();
      for (int q=0; q<qtot; q++) {
        r = state[0]->bc[n]->S->u[q];
        ru = state[1]->bc[n]->S->u[q];
        rv = state[2]->bc[n]->S->u[q];
        E = state[3]->bc[n]->S->u[q];

        for(int j=0;j<4;j++)
          lamb[j] = S[j]->u[q];

        Vs = (ru*(-ny[q])+rv*nx[q])/r;    // tangential velocity
        Vn = (ru*nx[q]+rv*ny[q])/r;       // normal velocity


        //\lambda_n = \lambda_1 * nx + \lambda_2 * ny = 0
        if(Vn<=0) { // blowing
          B[0]->u[q] = S[0]->u[q];
          B[1]->u[q] = (S[1]->u[q]*ny[q] - S[2]->u[q]*nx[q])*ny[q];
          B[2]->u[q] = (S[2]->u[q]*nx[q] - S[1]->u[q]*ny[q])*nx[q];
          B[3]->u[q] = S[3]->u[q];
        }
        // Two constraints: \rho, T
        else { // suction
          Scalar Lambn = -gamma/(gamma-1.0)*lamb[3]*Vn;
          Scalar Lambs = -lamb[3]*Vs;
          B[0]->u[q] = 0.5*lamb[3]*(Vs*Vs+(gamma+1.0)/(gamma-1.0)*Vn*Vn);
          B[1]->u[q] = nx[q]*Lambn - ny[q]*Lambs;
          B[2]->u[q] = nx[q]*Lambs + ny[q]*Lambn;
          B[3]->u[q] = lamb[3];

        }
      }
    }

#endif
}

void Euler::ControlBC::adjoint_apply_flux( const Scalar t, const vField &state,
                                           const vField &adjoint) {
  error("Euler::ControlBC::adjoint_apply_flux(...) not implemented.");
}

Scalar Euler::ControlBC::inner_product( const dVector &Y ) const {
#if 1
  error("Euler::ControlBC:::inner_product(...) not implemented.");
  return 0;
#else
  int qtot,sid;
  dVector ta,tb,tab;
  int offset=0;
  Scalar sum=0.0;
  for (int n=0; n<(*Fphi)[0]->nbc; ++n)   // loop over field boundaries
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
#endif
}


void Euler::ControlBC::set_direction( dVector &out ) {
#if 1
  error("Euler::ControlBC:::set_direction() not implemented.");
#else
  if (data.size()==0) return;
  assert( data_size() == out.size() );
  out = data = 1.0;
#endif
}


void Euler::ControlBC::objective_function_gradient( const vField &state,
  const vField &adjoint, const Scalar time,  dVector &grad ) const
{
#if 1
  error("Euler::ControlBC:::gradient() not implemented.");
#else
  if (data.size()==0) return;
  Scalar r,ru,rv,E,Vn,Vs,p;
  Scalar Lambn,Lambs;
  dVector lamb(state.size());
  int qtot,sid;
  int offset=0;
  dVector dv, gv;
  for (int n=0; n<state[0]->nbc; ++n)   // loop over field boundaries
    if (state[0]->bc[n]->type == type) {

      // state and adjoint must have compatible sides
      assert( state[0]->bc[n]->S->qtot() == adjoint[0]->bc[n]->S->qtot() );

      dv.alias( *(const_cast<dVector*>(&data)), offset,
                state[0]->bc[n]->S->qtot() );

      gv.alias( *(const_cast<dVector*>(&grad)), offset,
                state[0]->bc[n]->S->qtot() );

      qtot = state[0]->bc[n]->S->qtot();
      sid = state[0]->bc[n]->sid;

      // Temporary fix for Euler [gqchen]
      for (int j=0; j<state.size(); j++) {
        state[j]->bc[n]->elmt->fill_sides(state[j]->bc[n]->elmt->u);
        adjoint[j]->bc[n]->elmt->fill_sides(adjoint[j]->bc[n]->elmt->u);
      }

      dVector &nx = state[0]->bc[n]->elmt->side[sid]->nx();
      dVector &ny = state[0]->bc[n]->elmt->side[sid]->ny();

      for (int q=0; q<qtot; q++) {
        r = state[0]->bc[n]->S->u[q];
        ru = state[1]->bc[n]->S->u[q];
        rv = state[2]->bc[n]->S->u[q];
        E = state[3]->bc[n]->S->u[q];

        for(int k=0;k<adjoint.size();k++) lamb[k] = adjoint[k]->bc[n]->S->u[q];

        Vs = (ru*(-ny[q])+rv*nx[q])/r;    // tangential velocity
        Vn = (ru*nx[q]+rv*ny[q])/r;       // normal velocity
        p  = (gamma-1.0)*(E - 0.5*(ru*ru+rv*rv)/r); //pressure

        // D()/D(n) = ()_{,x}*n1 + ()_{,y}*n2
        // D()/D(s) = -()_{,x}*n2 + ()_{,y}*n1

        // \lambda_n = \lambda_1*n1 + \lambda_2*n2
        Lambn = lamb[1]*nx[q] + lamb[2]*ny[q];
        // \lambda_s = - \lambda_1*n2 + \lambda_2*n1
        Lambs = -lamb[1]*ny[q] + lamb[2]*nx[q];

        // Gradient
        gv[q] = penalty*dv[q]
          +(r*lamb[0] + r*Vs*Lambs + 2*r*Vn*Lambn+(p+E+r*Vn*Vn)*lamb[3]);

      }
      offset+=qtot;
    }
#endif
}

void Euler::ControlBC::plot( const vField &state, const Size goffset,
                             const dVector &Gphi,
                             const Ordinal npredict,
                             const Ordinal ntout,
                             const Ordinal nsstep,
                             const Ordinal riter) const {
  const Ordinal offset = numeric_cast<Ordinal>(goffset);
  dVector dv;
  char tmp[30];
  string fname;
  for(Ordinal i=0; i<=npredict; i+=ntout){ //4 is nsstep for RK4
    fname="euler_control";
    sprintf(tmp,"%lld_%lld.dat",(long long)i,(long long)riter);
    fname = fname + tmp;
    FILE *opt_stat = fopen(fname.c_str(),"w");
    fprintf(opt_stat, "Euler Linear Control  @ %lld step\n",(long long)i);
    dv.alias( *(const_cast<dVector*>(&Gphi)),
              offset+(nsstep*i)*data_size(), data_size() );
    LocalSize np = 0;
    for (LocalSize n=0; n<state[0]->nbc; n++) {  // loop over state boundaries
      if (state[0]->bc[n]->type == type ) {
        const LocalSize sid = state[0]->bc[n]->sid;
        const LocalSize qtot = state[0]->bc[n]->S->qtot();
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

/// Steady control boundary condition
class Euler::SteadyControlBC : public ControlBC {
 public:
  SteadyControlBC(const string t, ifstream &in, vField *F,
                  const Scalar gamma_) : ControlBC(t,in,F,gamma_)  { }
  bool steady() const {return true;}
};

//===========================================================================
//                              Sponge Source
//===========================================================================

/// Sponge boundary treatment is implemented as a body source
class Euler::Sponge: public Source {
  int N;
  Scalar As;
  Scalar xs_b, xt_b, xs_t, xt_t, xs_l, xt_l, xs_r, xt_r;
  Scalar Ma_r, rho_r, T_r, U_r, V_r,E_r, p_r, c_r, gamma;
 public:
  Sponge( const string t, ifstream &in ) : Source(t,SPONGE) {
    // cout<<"Sponge( const string t, ifstream &in, "<<qtot<<")"<<endl;
    scan_lb(in);
    if (!(in >>N >> As >>xs_b>>xt_b>>xs_t>>xt_t>>xs_l>>xt_l>>xs_r>>xt_r
          >>Ma_r>>rho_r>>U_r>>V_r>>T_r))
      error("Sponge::Cannot read penalty and default value");
    scan_rb(in);
    gamma=1.4;
    E_r = (rho_r*T_r/(gamma*(gamma-1.0)*Ma_r*Ma_r) +
           0.5*rho_r*(U_r*U_r + V_r*V_r));
    p_r = E_r*(gamma-1.0);
    c_r = 1.0/Ma_r;
  }

  inline void apply(const Scalar, const vField &, vField & );

  inline void adjoint_apply(const Scalar, const vField &, const vField &,
                            vField &);
};

void Euler::Sponge::apply(const Scalar t, const vField &Us, vField &Ur ) {
  Element *S[4], *R[4];
  Scalar taus, x, y;
  Scalar spg[4];

  // form the conservative_variable
  spg[0] = rho_r;//rho;
  spg[1] = U_r*rho_r;//u[0]*rho;
  spg[2] = V_r*rho_r;//u[1]*rho;
  spg[3] = E_r;

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

    for (Ordinal i=0;i<qtot;i++){
      x=S[0]->C->x[i];
      y=S[0]->C->y[i];

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

void Euler::Sponge::adjoint_apply(const Scalar t, const vField &state,
                                  const vField &adjoint, vField &Ur ) {
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

    for(LocalSize i=0; i<qtot; i++){
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

#endif  // REO_EULERBC_HPP
