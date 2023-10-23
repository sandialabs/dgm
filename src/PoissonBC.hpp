#ifndef REO_POISSON_BC_HPP
#define REO_POISSON_BC_HPP

/** \file PoissonBC.hpp
    \brief Poisson flow boundary conditions
*/

// DGM includes
#include "BC.hpp"
#include "Source.hpp"
#include "Ctrl.hpp"
using namespace DGM;

namespace Reo {

//===========================================================================
//                            Dirichlet BC
//===========================================================================

/// Constant valued Dirichlet boundary condition
class Poisson::DirichletBC : public BC {
protected:
  Scalar value;
public:
  DirichletBC(const string t, const Scalar v=0) : BC(t), value(v) { }
  DirichletBC(const string t, ifstream &in) : BC(t) {
    scan_lb(in);
    if (!(in >> value))
      error("Poisson::DirichletBC: could not read value",-1);
    scan_rb(in);
  }
  inline void apply( const Scalar, const vField & ) ;
  inline void apply_flux( const Scalar, const vField & ) ;
  inline void matrix_apply( const Scalar, const vField & ) ;
  inline void matrix_apply_flux( const Scalar, const vField & ) ;

};
void Poisson::DirichletBC::apply( const Scalar t, const vField &F ) {
  for (LocalSize n=0; n<F[0]->nbc; ++n)   // loop over field boundaries
    if (F[0]->bc[n]->type == type )
      for (vField::size_type i=0; i<F.size(); ++i) {
        F[i]->bc[n]->B->u = value;
        scale( 2.0, F[i]->bc[n]->B->u );
        F[i]->bc[n]->B->u.Sub(F[i]->bc[n]->S->u);
      }
}
void Poisson::DirichletBC::apply_flux( const Scalar t, const vField &F ) {
  for (LocalSize n=0; n<F[0]->nbc; ++n)   // loop over field boundaries
    if (F[0]->bc[n]->type == type )
      for (vField::size_type i=0; i<F.size(); ++i) {
        F[i]->bc[n]->B->u = F[i]->bc[n]->S->u;
        scale(-1.0, F[i]->bc[n]->B->u );
      }
}
void Poisson::DirichletBC::matrix_apply( const Scalar t, const vField &F ) {
  for (LocalSize n=0; n<F[0]->nbc; ++n)   // loop over field boundaries
    if (F[0]->bc[n]->type == type )
      for (vField::size_type i=0; i<F.size(); ++i) {
        F[i]->bc[n]->B->u = value;
      }
}
void Poisson::DirichletBC::matrix_apply_flux( const Scalar t,
                                              const vField &F ) {
  for (LocalSize n=0; n<F[0]->nbc; ++n)   // loop over field boundaries
    if (F[0]->bc[n]->type == type )
      for (vField::size_type i=0; i<F.size(); ++i) {
        F[i]->bc[n]->B->u = F[i]->bc[n]->S->u;
      }
}

} // namespace Reo

#endif // REO_POISSON_BC_HPP

