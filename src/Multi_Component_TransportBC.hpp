#ifndef REO_MULTI_COMPONENT_TRANSPORT_BC_HPP
#define REO_MULTI_COMPONENT_TRANSPORT_BC_HPP

/** \file Multi_Component_TransportBC.hpp
    \brief Boundary conditions for multi-component transport
*/

#include "ReoConfig.hpp"
// DGM includes
#include "BC.hpp"
#include "Source.hpp"
#include "Ctrl.hpp"
using namespace DGM;

namespace Reo {

//===========================================================================
//                            Dirichlet BC
//===========================================================================

void Multi_Comp_Trans::DirichletBC::apply( const Scalar t, const vField &F ) {
  for (LocalSize n=0; n<F[0]->nbc; ++n)   // loop over field boundaries
    if (F[0]->bc[n]->type == type )
      for (vField::size_type i=0; i<F.size(); ++i) {
        F[i]->bc[n]->B->u = value;
#ifdef REO_CONSISTENT_BC
        scale( 2.0, F[i]->bc[n]->B->u );
        F[i]->bc[n]->B->u.Sub(F[i]->bc[n]->S->u);
#endif
      }
}

void Multi_Comp_Trans::DirichletBC::apply_flux( const Scalar t,
                                                  const vField &F ) {
  for (LocalSize n=0; n<F[0]->nbc; ++n)   // loop over field boundaries
    if (F[0]->bc[n]->type == type )
      for (vField::size_type i=0; i<F.size(); ++i) {
        F[i]->bc[n]->B->u = F[i]->bc[n]->S->u;
        scale(-1.0, F[i]->bc[n]->B->u );
      }
}

// Adjoint boundary term <u^* U u' + \sigma^* u' - \sigma' u^*>_\Gamma
void Multi_Comp_Trans::DirichletBC::adjoint_apply( const Scalar t,
                                           const vField &state,
                                           const vField &adjoint) {
  for (LocalSize n=0; n<adjoint[0]->nbc; ++n)   // loop over field boundaries
    if (adjoint[0]->bc[n]->type == type )
      for (vField::size_type i=0; i<adjoint.size(); ++i) {
        adjoint[i]->bc[n]->B->u = 0;
#ifdef REO_CONSISTENT_BC
        scale( 2.0, adjoint[i]->bc[n]->B->u );
        adjoint[i]->bc[n]->B->u.Sub(adjoint[i]->bc[n]->S->u);
#endif
      }
}

void Multi_Comp_Trans::DirichletBC::adjoint_apply_flux( const Scalar t,
                                                const vField &state,
                                                const vField &adjoint) {
  for (LocalSize n=0; n<adjoint[0]->nbc; ++n)   // loop over field boundaries
    if (adjoint[0]->bc[n]->type == type )
      for (vField::size_type i=0; i<adjoint.size(); ++i) {
        adjoint[i]->bc[n]->B->u = adjoint[i]->bc[n]->S->u;
        scale(-1.0, adjoint[i]->bc[n]->side->u );
      }
}

//===========================================================================
//                            Neumann BC
//===========================================================================

void Multi_Comp_Trans::NeumannBC::apply( const Scalar t, const vField &F ) {
  for (LocalSize n=0; n<F[0]->nbc; ++n)   // loop over field boundaries
    if (F[0]->bc[n]->type == type )
      for (vField::size_type i=0; i<F.size(); ++i)
        F[i]->bc[n]->B->u = F[i]->bc[n]->S->u;
}

void Multi_Comp_Trans::NeumannBC::apply_flux( const Scalar t, const vField &F ) {
  for (LocalSize n=0; n<F[0]->nbc; ++n)   // loop over field boundaries
    if (F[0]->bc[n]->type == type )
      for (vField::size_type i=0; i<F.size(); ++i) {
#ifdef REO_CONSISTENT_BC
        F[i]->bc[n]->B->u = -2*value;
        F[i]->bc[n]->B->u.Add(F[i]->bc[n]->S->u);
#else
        F[i]->bc[n]->B->u = value;
        scale(-1.0, F[i]->bc[n]->B->u );  // switch sign due to normal vector
#endif
      }
}

// Adjoint boundary term < u^* U u' + \sigma^* u' - \sigma' u^* >_\Gamma

void Multi_Comp_Trans::NeumannBC::adjoint_apply( const Scalar t,
                                         const vField &state,
                                         const vField &adjoint) {
  for (LocalSize n=0; n<adjoint[0]->nbc; ++n)   // loop over field boundaries
    if (adjoint[0]->bc[n]->type == type )
      for (vField::size_type i=0; i<adjoint.size(); ++i)
        adjoint[i]->bc[n]->B->u = adjoint[i]->bc[n]->S->u;
}

void Multi_Comp_Trans::NeumannBC::adjoint_apply_flux( const Scalar t,
                                              const vField &state,
                                              const vField &adjoint) {
  for (LocalSize n=0; n<adjoint[0]->nbc; ++n)   // loop over field boundaries
    if (adjoint[0]->bc[n]->type == type )
      for (vField::size_type i=0; i<adjoint.size(); ++i) {
        const LocalSize sid = adjoint[i]->bc[n]->sid;
        dVector av(adjoint[i]->bc[n]->S->qtot());
        adjoint[i]->bc[n]->elmt->load_side(adjoint[i]->bc[n]->elmt->u,sid,av);
        scale( cx, av );
        adjoint[i]->bc[n]->B->u = av;
        dvmul(adjoint[i]->bc[n]->elmt->side[sid]->nx(), adjoint[i]->bc[n]->B->u);
#ifdef REO_CONSISTENT_BC
        scale( 2.0, adjoint[i]->bc[n]->B->u );
        adjoint[i]->bc[n]->B->u.Add(adjoint[i]->bc[n]->S->u);
#endif
      }
}

//===========================================================================
//                            Robin BC
//===========================================================================

/// Apply the state boundary condition
void Multi_Comp_Trans::RobinBC::apply( const Scalar t, const vField &F ) {
  for (LocalSize n=0; n<F[0]->nbc; ++n)   // loop over field boundaries
    if (F[0]->bc[n]->type == type )
      for (vField::size_type i=0; i<F.size(); ++i)
        F[i]->bc[n]->B->u = F[i]->bc[n]->S->u;
}

/// Apply the flux boundary condition
/** \f[ \mu u_{,n} = \phi_R - + n \dot \theta u \f] */
void Multi_Comp_Trans::RobinBC::apply_flux( const Scalar t, const vField &F ) {
  LocalSize sid, qtot;
  dVector dv;
  for (LocalSize n=0; n<F[0]->nbc; ++n)   // loop over field boundaries
    if (F[0]->bc[n]->type == type)
      for (vField::size_type i=0; i<F.size(); ++i) {
        sid = F[i]->bc[n]->sid;
        qtot = F[i]->bc[n]->elmt->side[sid]->qtot();
        dv.resize(qtot); dv = value;
        dVector sv(F[i]->bc[n]->S->qtot());
        F[i]->bc[n]->elmt->load_side(F[i]->bc[n]->elmt->u, sid, sv);
        multiply( theta, sv, F[i]->bc[n]->B->u );
        dvmul( F[i]->bc[n]->elmt->side[sid]->nx(), F[i]->bc[n]->B->u );
        scale(-1.0, F[i]->bc[n]->B->u );
        daxpy( 1.0, dv, F[i]->bc[n]->B->u );
        scale(-1.0, F[i]->bc[n]->B->u);    // since normal is reversed
#ifdef REO_CONSISTENT_BC
        scale( 2.0, F[i]->bc[n]->B->u );
        F[i]->bc[n]->B->u.Add(F[i]->bc[n]->S->u);
#endif
      }
}

/// Apply adjoint boundary condition
/** Adjoint boundary term 
    \f[ <u^* U u' + \sigma^* u' - \sigma' u^* >_\Gamma\f]
*/
void Multi_Comp_Trans::RobinBC::adjoint_apply( const Scalar t,
                                       const vField &state,
                                       const vField &adjoint) {
  for (LocalSize n=0; n<adjoint[0]->nbc; ++n)   // loop over field boundaries
    if (adjoint[0]->bc[n]->type == type )
      for (vField::size_type i=0; i<adjoint.size(); ++i)
        adjoint[i]->bc[n]->B->u = adjoint[i]->bc[n]->S->u;
}

/// Apply adjoint flux boundary condition
/** \f[ \mu u^*_n = 0 \f] */
void Multi_Comp_Trans::RobinBC::adjoint_apply_flux( const Scalar t,
                                                      const vField &state,
                                                      const vField &adjoint) {
  for (LocalSize n=0; n<adjoint[0]->nbc; ++n)   // loop over field boundaries
    if (adjoint[0]->bc[n]->type == type )
      for (vField::size_type i=0; i<adjoint.size(); ++i){
        LocalSize sid = adjoint[i]->bc[n]->sid;
        dVector av(adjoint[i]->bc[n]->S->qtot());
        dVector sv(state[i]->bc[n]->S->qtot());
        sv = cx;
        sv += theta;
        adjoint[i]->bc[n]->elmt->load_side(adjoint[i]->bc[n]->elmt->u,sid,av);
        dvmul(adjoint[i]->bc[n]->elmt->side[sid]->nx(), av,
              adjoint[i]->bc[n]->B->u);
        dvmul(sv, adjoint[i]->bc[n]->B->u);
#ifdef REO_CONSISTENT_BC
        scale( 2.0, adjoint[i]->bc[n]->B->u );
        adjoint[i]->bc[n]->B->u.Add(adjoint[i]->bc[n]->S->u);
#endif
     }
}

//===========================================================================
//                            Outflow BC
//===========================================================================

/// Apply adjoint boundary 
/** \f[ < u^* U u' + \sigma^* u' - \sigma' u^* >_\Gamma \f] */
void Multi_Comp_Trans::OutflowBC::apply( const Scalar t, const vField &F ) {
  for (LocalSize n=0; n<F[0]->nbc; ++n)         // loop over field boundaries
    if (F[0]->bc[n]->type == type )
      for (vField::size_type i=0; i<F.size(); ++i)
        F[i]->bc[n]->B->u = F[i]->bc[n]->S->u;
}

void Multi_Comp_Trans::OutflowBC::apply_flux(
    const Scalar t, const vField &F ) {
  for (LocalSize n=0; n<F[0]->nbc; ++n)         // loop over field boundaries
    if (F[0]->bc[n]->type == type )
      for (vField::size_type i=0; i<F.size(); ++i) {
        F[i]->bc[n]->B->u = F[i]->bc[n]->S->u;
        scale(-1.0, F[i]->bc[0]->B->u );  // switch sign due to normal vector
      }
}

void Multi_Comp_Trans::OutflowBC::adjoint_apply( const Scalar t,
                                                   const vField &state,
                                                   const vField &adjoint ) {
  for (LocalSize n=0; n<adjoint[0]->nbc; ++n)   // loop over field boundaries
    if (adjoint[0]->bc[n]->type == type )
      for (vField::size_type i=0; i<adjoint.size(); ++i)
        adjoint[i]->bc[n]->B->u = 0.0;
}

/// Adjoint boundary term 
/** \f[ < u^* U {\vec n} >_\Gamma \f] */
void Multi_Comp_Trans::OutflowBC::adjoint_apply_flux( const Scalar t,
                                              const vField &state,
                                              const vField &adjoint ) {
  for (LocalSize n=0; n<adjoint[0]->nbc; ++n)   // loop over field boundaries
    if (adjoint[0]->bc[n]->type == type )
      for (vField::size_type i=0; i<adjoint.size(); ++i) {
        adjoint[i]->bc[n]->B->u = 0.0;
        scale(-1.0, adjoint[i]->bc[0]->B->u);//switch sign due to normal vector
      }
}

} // namespace Reo

#endif // REO_MULTI_COMPONENT_TRANSPORT_BC_HPP

