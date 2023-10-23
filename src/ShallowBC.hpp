#ifndef DGM_REMOVE_FOR_RELEASE

#ifndef REO_SHALLOWBC_HPP
#define REO_SHALLOWBC_HPP

/** \file  ShallowBC.hpp
    \brief Shallow equation boundary conditions
    \author Vince Mousseau
    \author Scott Collis
*/

// DGM includes
#include "BC.hpp"
#include "Source.hpp"
#include "Ctrl.hpp"

using DGM::BC;
using DGM::Source;
using DGM::Ctrl;

namespace Reo {

//===========================================================================
//                              Solid Wall
//===========================================================================

/// Wall boundary condition for 2d Shallow flows
class Shallow::WallBC : public BC {
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

void Shallow::WallBC::apply( const Scalar t, const vField &F ) {
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
      }
    }
}

/// this should not be called for pure Shallow but is needed for ShallowDC
void Shallow::WallBC::apply_flux( const Scalar t, const vField &F ) {
  //cout << "Shallow::WallBC::apply_flux(...)" << endl;
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
void Shallow::WallBC::adjoint_apply( const Scalar t, const vField &state,
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
      }
    }
}

void Shallow::WallBC::adjoint_apply_flux( const Scalar t, const vField &state,
                                          const vField &adjoint) {
  error("Shallow::WallBC::adjoint_apply_flux() not implemented.");
}

//===========================================================================
//                     Distributed Control Source
//===========================================================================

/// Distributed control source term
class Shallow::DistributedControl : public Source, public Ctrl {
  Scalar value;            ///< default value
public:
  DistributedControl(const string t, ifstream &in, const vField &S)
    : Source(t)
  {
    for (vField::size_type i=0; i<S.size(); i++) {
      F.push_back( new Field(S[i]) );
      G.push_back( new Field(S[i]) );  // make temporary vectory field
    }
    scan_lb(in);
#ifndef DGM_USE_TIME_REG
    if (!(in >> penalty >> value))
      error("Shallow::DistributedControl: Cannot read penalty and value");
#else
    if (!(in >> penalty >> penalty_t >> value))
      error("Shallow::DistributedControl: penalty, penalty_t and value");
#endif
    scan_rb(in);
    size(F.qtot());
    initialize();
  }

  inline void apply( const Scalar, const vField &, vField & );
  inline void adjoint_apply( const Scalar, const vField &, const vField &,
                             vField & ) {}

  inline Ctrl* ctrl() { return this; }
  inline const Ctrl* ctrl() const { return this; }

  // Ctrl virtual methods

  void initialize() { Ctrl::initialize(); data=value; }  // set default value
  inline Scalar inner_product(const dVector &) const;

  inline void set_direction( dVector & );
  inline void objective_function_gradient( const vField &, const vField &,
                                           const Scalar time, dVector & ) const;

  inline void plot( const vField &, const Size, const dVector & ,
                    const Ordinal, const Ordinal, const Ordinal,
                    const Ordinal) const;
};

void Shallow::DistributedControl::apply( const Scalar, const vField &,
                                         vField &U) {
  assert( data_size() == U.qtot() );
  subtract( data, U[0] );
}

Scalar Shallow::DistributedControl::inner_product( const dVector &Y ) const {
  F.fill( data );
  G.fill( Y );
  return vField::local_L2_inner_product( F, G );
}

void Shallow::DistributedControl::set_direction( dVector &out ) {
  assert( data_size() == out.size() );
  out = data = 1.0;
}

void Shallow::DistributedControl::objective_function_gradient(
  const vField &state, const vField &adjoint, const Scalar time,
  dVector &grad ) const
{
  assert( data.size() == grad.size() );
#if 1 // def PROJECT_ADJOINT_TO_CONTROL
  adjoint.project(G);
  F.fill( data );
  axpy( penalty, F, G, G );
  G.extract( grad );
#else
  assert( data.size() == adjoint.qtot() );
  F.fill( data );
  axpy( penalty, F, adjoint, G );
  G.extract( grad );
#endif
}

void Shallow::DistributedControl::plot( const vField &state, const Size offset,
                                        const dVector &Gphi,
                                        const Ordinal npredict,
                                        const Ordinal ntout,
                                        const Ordinal nsstep,
                                        const Ordinal riter) const {
  dVector dv;
  char tmp[80];
  string fname;
  for(Ordinal i=0; i<=npredict; i+=ntout) {
    sprintf(tmp,"%s.%lld_%lld.dat",type.c_str(),(long long)i,(long long)riter);
    fname = tmp;
    dv.alias( *(const_cast<dVector*>(&Gphi)),
              numeric_cast<Ordinal>(offset+(nsstep*i)*data_size()),data_size());
    F.fill(dv);
    F.tecplot(fname,"Distributed Control");
  }
}

} // namespace Reo

#endif  // REO_SHALLOWBC_HPP

#else // DGM_REMOVE_FOR_RELEASE
// This capability is under development.
#endif // DGM_REMOVE_FOR_RELEASE
