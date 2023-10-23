#ifndef REO_INS_BC_HPP
#define REO_INS_BC_HPP

/** \file iNSBC.hpp
    \brief Declares the boundary conditions for incompressible Navier-Stokes
    \author Scott Collis
*/

// system includes
#include <fstream>
#include <iomanip>
using namespace std;

// DGM includes
#include "BC.hpp"
#include "Source.hpp"
#include "Ctrl.hpp"
using namespace DGM;

// Reo includes
#include "ReoConfig.hpp"

namespace Reo {

//===========================================================================
//                              No-Slip Wall
//===========================================================================

/// Wall boundary condition
class iNS::WallBC : public BC {
public:
  WallBC( const string t ) : BC(t) { }
  WallBC( const string t, ifstream &in ) : BC(t) {
    scan_lb(in);
    scan_rb(in);
  }
  inline void apply( const Scalar t, const vField & ) ;
  inline void apply_flux( const Scalar t, const vField & ) ;

  inline void adjoint_apply( const Scalar t, const vField &, const vField & );
  inline void adjoint_apply_flux( const Scalar t, const vField &,
                                  const vField & );
};

void iNS::WallBC::apply( const Scalar t, const vField &F ) {
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
        B[0]->u[i] = 0.0;
        B[1]->u[i] = 0.0;
      }
    }
}

void iNS::WallBC::apply_flux( const Scalar t,
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
      }
    }
}

// \lambda_1 = 0;  \lambda_2 = 0;  \lambda_3 = 0
void iNS::WallBC::adjoint_apply( const Scalar t,
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
        B[0]->u[i] = 0.0;
        B[1]->u[i] = 0.0;
      }
    }
}

//  \lambda_1 = 0;  \lambda_2 = 0;  \lambda_3 = 0
void iNS::WallBC::adjoint_apply_flux( const Scalar t,
                                      const vField &state,
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
      }
    }
}

} // namespace Reo

#endif  // REO_INS_BC_HPP
