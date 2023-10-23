#ifndef REO_IEULERBC_HPP
#define REO_IEULERBC_HPP

/** \file iEulerBC.hpp
    \brief Declares the boundary conditions for incompressible Euler
    \author Scott Collis
*/

// DGM includes
#include "BC.hpp"
#include "Source.hpp"
#include "Ctrl.hpp"
using namespace DGM;

// Reo includes
#include "ReoConfig.hpp"

namespace Reo {

//===========================================================================
//                           Solid Wall
//===========================================================================

/// Wall boundary condition
class iEuler::WallBC : public BC {
public:
  WallBC( const string t ) : BC(t) { }
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

void iEuler::WallBC::apply( const Scalar t, const vField &F ) {
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
        B[0]->u[i] = (S[0]->u[i]*ny[i] - S[1]->u[i]*nx[i])*ny[i];
        B[1]->u[i] = (S[1]->u[i]*nx[i] - S[0]->u[i]*ny[i])*nx[i];
      }
    }
}

void iEuler::WallBC::apply_flux( const Scalar t, const vField &F ) {
  error("iEuler::WallBC::apply_flux(...) not implemented.");
}

// \lambda_n = \lambda_1 * nx + \lambda_2 * ny = 0
void iEuler::WallBC::adjoint_apply( const Scalar t, const vField &state,
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
        B[0]->u[i] = (S[0]->u[i]*ny[i] - S[1]->u[i]*nx[i])*ny[i];
        B[1]->u[i] = (S[1]->u[i]*nx[i] - S[0]->u[i]*ny[i])*nx[i];
      }
    }
}

void iEuler::WallBC::adjoint_apply_flux( const Scalar t, const vField &state,
                                         const vField &adjoint) {
  error("iEuler::WallBC::adjoint_apply_flux() not implemented.");
}

} // namespace Reo

#endif  // REO_IEULERBC_HPP
