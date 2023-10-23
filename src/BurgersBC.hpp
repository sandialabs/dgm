#ifndef REO_BURGERS_BC_HPP
#define REO_BURGERS_BC_HPP

/** \file BurgersBC.hpp
    \brief Burgers equation boundary conditions
    \author Scott Collis
*/

// local includes
#include "ReoConfig.hpp"

// DGM includes
#include "BC.hpp"
#include "Source.hpp"
#include "Ctrl.hpp"
using DGM::BC;
using DGM::Source;
using DGM::Ctrl;

namespace Reo {

//===========================================================================
//                            Dirichlet BC
//===========================================================================

/// Dirichlet boundary condition
class Burgers::DirichletBC : public BC {
  Scalar value;
public:
  DirichletBC(const string t, const Scalar v) : BC(t), value(v) { }
  DirichletBC(const string t, ifstream &in) : BC(t) {
    scan_lb(in);
    if (!(in >> value))
      error("Burgers::DirichletBC: could not read value",-1);
    scan_rb(in);
  }
  inline void apply( const Scalar, const vField & ) ;
  inline void apply_flux( const Scalar, const vField & ) ;

  inline void adjoint_apply( const Scalar, const vField &, const vField & ) ;
  inline void adjoint_apply_flux( const Scalar, const vField &,
                                  const vField & ) ;
};

void Burgers::DirichletBC::apply( const Scalar t, const vField &F ) {
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

void Burgers::DirichletBC::apply_flux( const Scalar t, const vField &F ) {
  for (LocalSize n=0; n<F[0]->nbc; ++n)   // loop over field boundaries
    if (F[0]->bc[n]->type == type )
      for (vField::size_type i=0; i<F.size(); ++i) {
        F[i]->bc[n]->B->u = F[i]->bc[n]->S->u;
        scale(-1.0, F[i]->bc[n]->B->u );
      }
}

/// Adjoint boundary term \f$<u^* U u' + \sigma^* u' - \sigma' u^*>_\Gamma\f$
void Burgers::DirichletBC::adjoint_apply( const Scalar t,
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

void Burgers::DirichletBC::adjoint_apply_flux( const Scalar t,
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

/// Neumann boundary condition
class Burgers::NeumannBC : public BC {
  Scalar value;
public:
  NeumannBC(const string t, const Scalar v=0) : BC(t), value(v) { }
  NeumannBC(const string t, ifstream &in) : BC(t) {
    scan_lb(in);
    if (!(in >> value))
      error("Burgers::NeumannBC: could not read value",-1);
    scan_rb(in);
  }
  inline void apply( const Scalar t, const vField & ) ;
  inline void apply_flux( const Scalar t, const vField & ) ;

  inline void adjoint_apply( const Scalar t, const vField &,
                             const vField & ) ;
  inline void adjoint_apply_flux( const Scalar t, const vField &,
                                  const vField & ) ;
};

// Adjoint boundary term < u^* U u' + \sigma^* u' - \sigma' u^* >_\Gamma

void Burgers::NeumannBC::apply( const Scalar t, const vField &F ) {
  for (LocalSize n=0; n<F[0]->nbc; ++n)   // loop over field boundaries
    if (F[0]->bc[n]->type == type )
      for (vField::size_type i=0; i<F.size(); ++i)
        F[i]->bc[n]->B->u = F[i]->bc[n]->S->u;
}

void Burgers::NeumannBC::apply_flux( const Scalar t, const vField &F ) {
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

void Burgers::NeumannBC::adjoint_apply( const Scalar t,
                                        const vField &state,
                                        const vField &adjoint) {
  for (LocalSize n=0; n<adjoint[0]->nbc; ++n)   // loop over field boundaries
    if (adjoint[0]->bc[n]->type == type )
      for (vField::size_type i=0; i<adjoint.size(); ++i)
        adjoint[i]->bc[n]->B->u = adjoint[i]->bc[n]->S->u;
}

/// This is a Robin BC for the adjoint:  \f$\sigma^* = -u^* U {\vec n}\f$
void Burgers::NeumannBC::adjoint_apply_flux( const Scalar t,
                                             const vField &state,
                                             const vField &adjoint) {
  for (LocalSize n=0; n<adjoint[0]->nbc; ++n)   // loop over field boundaries
    if (adjoint[0]->bc[n]->type == type )
      for (vField::size_type i=0; i<adjoint.size(); ++i) {
        const LocalSize sid = adjoint[i]->bc[n]->sid;
        dVector av(adjoint[i]->bc[n]->S->qtot());
#ifdef REO_BURGERS_NO_CONVECTION
        adjoint[i]->bc[n]->B->u = -0.0;
#else
        adjoint[i]->bc[n]->elmt->load_side(adjoint[i]->bc[n]->elmt->u,sid,av);
        dvmul(state[i]->bc[n]->S->u, av, adjoint[i]->bc[n]->B->u);
        dvmul(adjoint[i]->bc[n]->elmt->side[sid]->nx(),
              adjoint[i]->bc[n]->B->u);
#endif
#ifdef REO_CONSISTENT_BC
        scale( 2.0, adjoint[i]->bc[n]->B->u );
        adjoint[i]->bc[n]->B->u.Add(adjoint[i]->bc[n]->S->u);
#endif
      }
}

//===========================================================================
//                            Robin BC
//===========================================================================

/// Robin boundary in the form: \f$\mu u_{,n} - F_n(u) = \phi_R\f$
class Burgers::RobinBC : public BC {
  Scalar theta;
  Scalar value;
public:
  RobinBC(const string t, const Scalar theta_ = 1.0, const Scalar v=0.0)
    : BC(t), theta(theta_),value(v) { }
  RobinBC(const string t, ifstream &in) : BC(t) {
    scan_lb(in);
    if (!(in >> value >> theta))
      error("Burgers::RobinBC: could not read theta and value",-1);
    scan_rb(in);
  }
  inline void apply( const Scalar t, const vField & );
  inline void apply_flux( const Scalar t, const vField &);

  inline void adjoint_apply( const Scalar t, const vField &,
                             const vField & ) ;
  inline void adjoint_apply_flux( const Scalar t, const vField &,
                                  const vField & ) ;
};

void Burgers::RobinBC::apply( const Scalar t, const vField &F ) {
  for (LocalSize n=0; n<F[0]->nbc; ++n)   // loop over field boundaries
    if (F[0]->bc[n]->type == type )
      for (vField::size_type i=0; i<F.size(); ++i)
        F[i]->bc[n]->B->u = F[i]->bc[n]->S->u;
}

/// \f$\mu u_{,n} = \phi_R - n \dot \theta u\f$
void Burgers::RobinBC::apply_flux( const Scalar t, const vField &F ) {
  LocalSize sid, qtot;
  dVector dv;
  for (LocalSize n=0; n<F[0]->nbc; ++n)   // loop over field boundaries
    if (F[0]->bc[n]->type == type )
      for (vField::size_type i=0; i<F.size(); ++i){
        sid = F[i]->bc[n]->sid;
        qtot = F[i]->bc[n]->elmt->side[sid]->qtot();
        dv.resize(qtot); dv = value;
        dVector sv(F[i]->bc[n]->S->qtot());
        F[i]->bc[n]->elmt->load_side(F[i]->bc[n]->elmt->u, sid, sv);
        multiply( theta, sv, F[i]->bc[n]->B->u );
        dvmul( F[i]->bc[n]->elmt->side[sid]->nx(), F[i]->bc[n]->B->u );
        scale(-1.0, F[i]->bc[n]->B->u );
        daxpy( 1.0, dv, F[i]->bc[n]->B->u );
        scale(-1.0, F[i]->bc[n]->B->u );   // since normal is reversed
#ifdef REO_CONSISTENT_BC
        scale( 2.0, F[i]->bc[n]->B->u );
        F[i]->bc[n]->B->u.Add(F[i]->bc[n]->S->u);
#endif
      }
}

void Burgers::RobinBC::adjoint_apply( const Scalar t, const vField &state,
                                      const vField &adjoint) {
  for (LocalSize n=0; n<adjoint[0]->nbc; ++n)   // loop over field boundaries
    if (adjoint[0]->bc[n]->type == type )
      for (vField::size_type i=0; i<adjoint.size(); ++i)
        adjoint[i]->bc[n]->B->u = adjoint[i]->bc[n]->S->u;
}

/// \f$\mu u^*_n = 0\f$
void Burgers::RobinBC::adjoint_apply_flux( const Scalar t, const vField &state,
                                           const vField &adjoint) {
  for (LocalSize n=0; n<adjoint[0]->nbc; ++n) {  // loop over field boundaries
    if (adjoint[0]->bc[n]->type == type ) {
      for (vField::size_type i=0; i<adjoint.size(); ++i){
        const LocalSize sid = adjoint[i]->bc[n]->sid;
        dVector av(adjoint[i]->bc[n]->S->qtot());
        dVector sv(state[i]->bc[n]->S->qtot());
#ifdef REO_BURGERS_NO_CONVECTION
        sv = 0.0;
#else
        sv = state[i]->bc[n]->B->u;
#endif
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
  }
}

//===========================================================================
//                            Outflow BC
//===========================================================================

/// Outflow boundary condition
class Burgers::OutflowBC : public BC {
public:
  OutflowBC( const string t) : BC(t) { }
  OutflowBC( const string t, ifstream &in ) : BC(t) {
    scan_lb(in);
    scan_rb(in);
  }
  inline void apply( const Scalar t, const vField & ) ;
  inline void apply_flux( const Scalar t, const vField & ) ;

  inline void adjoint_apply( const Scalar t, const vField &, const vField & );
  inline void adjoint_apply_flux( const Scalar t, const vField &,
                                  const vField & ) ;
};

/// Adjoint boundary term \f$(u^* U u' + \sigma^* u' - \sigma' u^*)_\Gamma\f$
void Burgers::OutflowBC::apply( const Scalar t, const vField &F ) {
  for (LocalSize n=0; n<F[0]->nbc; ++n)   // loop over field boundaries
    if (F[0]->bc[n]->type == type )
      for (vField::size_type i=0; i<F.size(); ++i)
        F[i]->bc[n]->B->u = F[i]->bc[n]->S->u;
}

/// Apply flux
void Burgers::OutflowBC::apply_flux( const Scalar t, const vField &F ) {
  for (LocalSize n=0; n<F[0]->nbc; ++n)   // loop over field boundaries
    if (F[0]->bc[n]->type == type )
      for (vField::size_type i=0; i<F.size(); ++i) {
        F[i]->bc[n]->B->u = F[i]->bc[n]->S->u;
        scale(-1.0, F[i]->bc[0]->B->u );  // switch sign due to normal vector
      }
}

/// Adjoint apply
void Burgers::OutflowBC::adjoint_apply( const Scalar t, const vField &state,
                                        const vField &adjoint) {
  for (LocalSize n=0; n<adjoint[0]->nbc; ++n)   // loop over field boundaries
    if (adjoint[0]->bc[n]->type == type )
      for (vField::size_type i=0; i<adjoint.size(); ++i)
        adjoint[i]->bc[n]->B->u = 0.0;
}

/// Adjoint boundary term \f$< u^* U {\vec n} >_\Gamma\f$
void Burgers::OutflowBC::adjoint_apply_flux( const Scalar t,
                                             const vField &state,
                                             const vField &adjoint) {
  for (LocalSize n=0; n<adjoint[0]->nbc; ++n)   // loop over field boundaries
    if (adjoint[0]->bc[n]->type == type )
      for (vField::size_type i=0; i<adjoint.size(); ++i) {
        adjoint[i]->bc[n]->B->u = 0.0;
        scale(-1.0, adjoint[i]->bc[0]->B->u);//switch sign due to normal vector
      }
}

//===========================================================================
//                         Dirichlet Control BC
//===========================================================================

/// Dirichlet control boundary condition
class Burgers::DirichletControlBC : public BC , public Ctrl {
  Scalar value;
public:
  DirichletControlBC( const string t, ifstream &in ) : BC(t) {
    scan_lb(in);
#ifndef DGM_USE_TIME_REG
    if (!(in >> penalty >> value))
      error("Burgers::DirichletControlBC: penalty, value.",-1);
#else
    if (!(in >> penalty >> penalty_t >> value))
      error("Burgers::DirichletControlBC: penalty, penalty_t and value.",-1);
#endif
    scan_rb(in);

  }

  // BC methods
  inline void apply( const Scalar t, const vField & );
  inline void apply_flux( const Scalar t, const vField & );

  inline void adjoint_apply( const Scalar t, const vField &, const vField & );
  inline void adjoint_apply_flux( const Scalar t, const vField &,
                                  const vField & );

  inline Ctrl* ctrl() { return this; }
  inline const Ctrl* ctrl() const { return this; }

  // Ctrl methods
  void initialize() { Ctrl::initialize(); data=value; }  // set default value
  inline Scalar inner_product(const dVector &) const;
#ifdef DGM_DEBUG_CTRL
  inline Scalar cost() const {
    Scalar result = Ctrl::cost();
    cout<<"Cost("<<type<<") = "<<result<<endl;
    return result;
  }
#endif
  inline void set_direction( dVector & );
  inline void objective_function_gradient( const vField &, const vField &,
      const Scalar time, dVector & ) const;

  inline void plot( const vField &, const Size, const dVector & ,
                    const Ordinal, const Ordinal, const Ordinal,
                    const Ordinal) const;
};

void Burgers::DirichletControlBC::apply( const Scalar t, const vField &F ) {
  if (data.size()==0) {
    for (LocalSize n=0; n<F[0]->nbc; ++n)   // loop over field boundaries
      if (F[0]->bc[n]->type == type )
        for (vField::size_type i=0; i<F.size(); ++i)
          F[i]->bc[n]->B->u = value;
  } else {
    LocalSize offset=0;
    dVector dv;
    for (LocalSize n=0; n<F[0]->nbc; ++n) {   // loop over field boundaries
      if (F[0]->bc[n]->type == type ) {
        for (vField::size_type i=0; i<F.size(); ++i) {
          dv.alias(*(const_cast<dVector*>(&data)), offset,
                   F[i]->bc[n]->B->qtot());
          F[i]->bc[n]->B->u = dv;
          offset += F[i]->bc[n]->B->qtot();
        }
      }
    }
  }
}

void Burgers::DirichletControlBC::apply_flux( const Scalar t,
                                              const vField &F ) {
  for (LocalSize n=0; n<F[0]->nbc; ++n)   // loop over field boundaries
    if (F[0]->bc[n]->type == type )
      for (vField::size_type i=0; i<F.size(); ++i) {
        F[i]->bc[n]->B->u = F[i]->bc[n]->S->u;
        scale(-1.0, F[i]->bc[n]->B->u );
      }
}

// Adjoint boundary term (u^* U u' n + \sigma_n^* u' - \sigma_n' u^*)_\Gamma

void Burgers::DirichletControlBC::adjoint_apply( const Scalar t,
                                                 const vField &state,
                                                 const vField &adjoint) {
  for (LocalSize n=0; n<adjoint[0]->nbc; ++n)   // loop over field boundaries
    if (adjoint[0]->bc[n]->type == type )
      for (vField::size_type i=0; i<adjoint.size(); ++i)
        adjoint[i]->bc[n]->B->u = 0.0;
}

void Burgers::DirichletControlBC::adjoint_apply_flux( const Scalar t,
                                                      const vField &state,
                                                      const vField &adjoint) {
  for (LocalSize n=0; n<adjoint[0]->nbc; ++n)   // loop over field boundaries
    if (adjoint[0]->bc[n]->type == type )
      for (vField::size_type i=0; i<adjoint.size(); ++i) {
        adjoint[i]->bc[n]->B->u = adjoint[i]->bc[n]->S->u;
        scale(-1.0, adjoint[i]->bc[n]->B->u );
      }
}

Scalar Burgers::DirichletControlBC::inner_product( const dVector &Y ) const {
  assert( Y.size() == data.size() );
  if (data.size() == 0) return 0.0;
  return dot( data, Y );
}

void Burgers::DirichletControlBC::set_direction( dVector &out ) {
  if (data.size()==0) return;
  assert( data_size() == out.size() );
  out = data = 1.0;
}

void Burgers::DirichletControlBC::objective_function_gradient(
  const vField &state, const vField &adjoint, const Scalar time,
  dVector &grad ) const
{
  if (data.size()==0) return;
  LocalSize offset=0;
  dVector dv, gv;
  for (LocalSize n=0; n<state[0]->nbc; n++) {  // loop over state boundaries
    if (state[0]->bc[n]->type == type ) {
      // state and adjoint must have compatible sides
      assert( state[0]->bc[n]->S->qtot() == adjoint[0]->bc[n]->S->qtot() );
      dv.alias( *(const_cast<dVector*>(&data)), offset,
                state[0]->bc[n]->S->qtot() );
      gv.alias( *(const_cast<dVector*>(&grad)), offset,
                state[0]->bc[n]->S->qtot() );
      // use B side here to get sign correct
      daxpy( penalty, dv, adjoint[0]->bc[n]->B->u, gv );
      offset += state[0]->bc[n]->S->qtot();
    }
  }
}

void Burgers::DirichletControlBC::plot( const vField &state, const Size goffset,
                                        const dVector &Gphi,
                                        const Ordinal npredict,
                                        const Ordinal ntout,
                                        const Ordinal nsstep,
                                        const Ordinal riter) const {
  const Ordinal offset = numeric_cast<Ordinal>(goffset);
  dVector dv;
  Ordinal ncontrol = 0;
  char tmp[80];
  string fname;
  for (LocalSize n=0; n<state[0]->nbc; n++) {  // loop over state boundaries
    if (state[0]->bc[n]->type == type ) {
      sprintf(tmp,"%s.%lld.dat",type.c_str(),(long long)riter);
      fname = fname + tmp;
      FILE *opt_stat = fopen(fname.c_str(),"w");
      const LocalSize sid = state[0]->bc[n]->sid;
      Scalar x;
#if 0
      Point* pside = new Point[state[0]->bc[n]->elmt->side[sid]->qtot()];
      state[0]->bc[n]->elmt->get_side_coordinates(sid,pside);
      x = pside[0].x;
      delete pside;
#else
      if(sid ==0)
        x = (*state[0]->bc[n]->elmt->C)[0].x;
      else
        x = (*state[0]->bc[n]->elmt->C)[state[0]->bc[n]->elmt->qtot-1].x;
#endif
      fprintf(opt_stat, "# Dirichlet Control at %11.4e @ %lld steps\n",
              x, (long long)npredict);
      for(Ordinal i=0; i<=npredict; i+=ntout){ // nsstep is nsstep for RK4
        dv.alias( *(const_cast<dVector*>(&Gphi)),
                  offset+(nsstep*i)*data_size(), data_size() );
        fprintf(opt_stat,"%5lld %11.4e\n",(long long)i,dv[ncontrol]);
      }
      fclose(opt_stat);
      ncontrol++;
    }
  }
}

//===========================================================================
//                         Neumann Control BC
//===========================================================================

/// Neumann Control boundary condition
class Burgers::NeumannControlBC : public BC , public Ctrl {
  Scalar value;
public:
  NeumannControlBC( const string t, ifstream &in ) : BC(t) {
    scan_lb(in);
#ifndef DGM_USE_TIME_REG
    if (!(in >> penalty >> value))
      error("Burgers::NeumannControlBC: penalty, value",-1);
#else
    if (!(in >> penalty >> penalty_t >> value))
      error("Burgers::NeumannControlBC: penalty, penalty_t and value.",-1);
#endif
    scan_rb(in);
  }

  inline void apply( const Scalar t, const vField & ) ;
  inline void apply_flux( const Scalar t, const vField & ) ;

  inline void adjoint_apply( const Scalar t, const vField &, const vField & );
  inline void adjoint_apply_flux( const Scalar t, const vField &,
                                  const vField & );

  inline Ctrl* ctrl() { return this; }
  inline const Ctrl* ctrl() const { return this; }

  // Ctrl methods
  void initialize() { Ctrl::initialize(); data=value; }  // set default value
  inline Scalar inner_product(const dVector &) const;
  inline void set_direction( dVector & );
  inline void objective_function_gradient( const vField &, const vField &,
      const Scalar time, dVector & ) const;
  inline void plot( const vField &, const Size, const dVector & ,
                    const Ordinal, const Ordinal, const Ordinal,
                    const Ordinal) const;
};

void Burgers::NeumannControlBC::apply( const Scalar t, const vField &F ) {
  for (LocalSize n=0; n<F[0]->nbc; ++n)   // loop over field boundaries
    if (F[0]->bc[n]->type == type )
      for (vField::size_type i=0; i<F.size(); ++i)
        F[i]->bc[n]->B->u = F[i]->bc[n]->S->u;
}

void Burgers::NeumannControlBC::apply_flux( const Scalar t, const vField &F ) {
  if (data.size()==0) {
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
  } else {
    LocalSize offset=0;
    dVector dv;
    for (LocalSize n=0; n<F[0]->nbc; ++n) {  // loop over field boundaries
      if (F[0]->bc[n]->type == type ) {
        for (vField::size_type i=0; i<F.size(); ++i) {
          dv.alias(*(const_cast<dVector*>(&data)), offset,
                   F[i]->bc[n]->B->qtot());
#ifdef REO_CONSISTENT_BC
          daxpy( -2.0, dv, F[i]->bc[n]->S->u, F[i]->bc[n]->B->u );
#else
          F[i]->bc[n]->B->u = dv;
          scale(-1.0, F[i]->bc[n]->B->u);
#endif
          offset += F[i]->bc[n]->B->qtot();
        }
      }
    }
  }
}

// Adjoint boundary term ( u^* U u' + \sigma^* u' - \sigma' u^* )_\Gamma

void Burgers::NeumannControlBC::adjoint_apply( const Scalar t,
                                               const vField &state,
                                               const vField &adjoint) {
  for (LocalSize n=0; n<adjoint[0]->nbc; ++n)   // loop over field boundaries
    if (adjoint[0]->bc[n]->type == type )
      for (vField::size_type i=0; i<adjoint.size(); ++i)
        adjoint[i]->bc[n]->B->u = adjoint[i]->bc[n]->S->u;
}

// \sigma^* = -u^* U {\vec n} (this is a Robin BC for the adjoint)
void Burgers::NeumannControlBC::adjoint_apply_flux( const Scalar t,
                                                    const vField &state,
                                                    const vField &adjoint) {
  for (LocalSize n=0; n<adjoint[0]->nbc; ++n)   // loop over field boundaries
    if (adjoint[0]->bc[n]->type == type )
      for (vField::size_type i=0; i<adjoint.size(); ++i) {
        const LocalSize sid = adjoint[i]->bc[n]->sid;
        dVector av(adjoint[i]->bc[n]->S->qtot());
#ifdef REO_BURGERS_NO_CONVECTION
        adjoint[i]->bc[n]->B->u = -0.0;
#else
        adjoint[i]->bc[n]->elmt->load_side(adjoint[i]->bc[n]->elmt->u,sid,av);
        dvmul(state[i]->bc[n]->S->u, av, adjoint[i]->bc[n]->B->u);
        dvmul(adjoint[i]->bc[n]->elmt->side[sid]->nx(),
              adjoint[i]->bc[n]->B->u);
#endif
#ifdef REO_CONSISTENT_BC
        scale( 2.0, adjoint[i]->bc[n]->B->u );
        adjoint[i]->bc[n]->B->u.Add(adjoint[i]->bc[n]->S->u);
#endif
      }
}

Scalar Burgers::NeumannControlBC::inner_product( const dVector &Y ) const {
  assert( Y.size() == data.size() );
  if (data.size() == 0) return 0.0;
  return dot( data, Y );
}

void Burgers::NeumannControlBC::set_direction( dVector &out ) {
  if (data.size()==0) return;
  assert( data_size() == out.size() );
  out = data = 1.0;
}

void Burgers::NeumannControlBC::objective_function_gradient(
 const vField &state, const vField &adjoint, const Scalar time,
 dVector &grad ) const
{
  if (data.size()==0) return;
  LocalSize offset=0;
  dVector dv, gv;
  for (LocalSize n=0; n<state[0]->nbc; n++) {  // loop over state boundaries
    if (state[0]->bc[n]->type == type ) {
      // state and adjoint must have compatible sides
      assert( state[0]->bc[n]->S->qtot() == adjoint[0]->bc[n]->S->qtot() );
      const LocalSize qtot = state[0]->bc[n]->S->qtot();
      const LocalSize sid  = adjoint[0]->bc[n]->sid;
      dv.alias( *(const_cast<dVector*>(&data)), offset, qtot );
      gv.alias( *(const_cast<dVector*>(&grad)), offset, qtot );
      // J_{,g} = penalty * g' + u^*
      multiply( penalty, dv, gv );
#if 1
      dVector av(qtot);
      adjoint[0]->bc[n]->elmt->load_side(adjoint[0]->bc[n]->elmt->u,sid,av);
      daxpy( 1.0, av, gv );
#else
      daxpy( 1.0, adjoint[0]->bc[n]->S->u, gv);
#endif
      offset += state[0]->bc[n]->S->qtot();
    }
  }
}

void Burgers::NeumannControlBC::plot( const vField &state, const Size goffset,
                                      const dVector &Gphi,
                                      const Ordinal npredict,
                                      const Ordinal ntout,
                                      const Ordinal nsstep,
                                      const Ordinal riter) const {
  const Ordinal offset = numeric_cast<Ordinal>(goffset);
  dVector dv;
  int ncontrol =0;
  char tmp[80];
  string fname;
  for (LocalSize n=0; n<state[0]->nbc; n++) {  // loop over state boundaries
    if (state[0]->bc[n]->type == type ) {
      sprintf(tmp,"%s.%lld.dat",type.c_str(),(long long)riter);
      fname = fname + tmp;
      FILE *opt_stat = fopen(fname.c_str(),"w");
      const LocalSize sid = state[0]->bc[n]->sid;
      Scalar x;
#if 0
      Point* pside = new Point[state[0]->bc[n]->elmt->side[sid]->qtot()];
      state[0]->bc[n]->elmt->get_side_coordinates(sid,pside);
      x = pside[0].x;
      delete pside;
#else
      if(sid ==0)
        x =  (*state[0]->bc[n]->elmt->C)[0].x;
      else
        x =  (*state[0]->bc[n]->elmt->C)[state[0]->bc[n]->elmt->qtot-1].x;
#endif
      fprintf(opt_stat, "# Neumann Control at %11.4e @ %llu steps\n",
              x, (unsigned long long)npredict);

      for(Ordinal i=0; i<=npredict; i+=ntout){     // nsstep is nsstep for RK4
        dv.alias( *(const_cast<dVector*>(&Gphi)),
                  offset+(nsstep*i)*data_size(), data_size() );
        fprintf(opt_stat,"%5llu %11.4e\n",(unsigned long long)i,dv[ncontrol]);
      }
      fclose(opt_stat);
      ncontrol++;

    }
  }
}

//===========================================================================
//                         Robin Control BC
//===========================================================================

/// Robin control form:  \f$\mu u_{,n} + n \theta u  = \phi_R\f$
class Burgers::RobinControlBC : public BC , public Ctrl {
  Scalar theta;
  Scalar value;
public:
  RobinControlBC( const string t, ifstream &in ) : BC(t) {
    scan_lb(in);
#ifndef DGM_USE_TIME_REG
    if (!(in >> penalty >> value >> theta))
      error("Burgers::RobinControlBC: penalty, value, theta");
#else
    if (!(in >> penalty >> penalty_t >> value >> theta))
      error("Burgers::RobinControlBC: penalty, penalty_t, value, theta.");
#endif
    scan_rb(in);
  }
  inline void apply( const Scalar t, const vField & ) ;
  inline void apply_flux( const Scalar t, const vField & ) ;

  inline void adjoint_apply( const Scalar t, const vField &, const vField & );
  inline void adjoint_apply_flux( const Scalar t, const vField &,
                                  const vField & ) ;

  inline Ctrl* ctrl() { return this; }
  inline const Ctrl* ctrl() const { return this; }

  // Ctrl methods
  void initialize() { Ctrl::initialize(); data=value; }  // set default value
  inline Scalar inner_product(const dVector &) const;
  inline void set_direction( dVector & );
  inline void objective_function_gradient( const vField &, const vField &,
      const Scalar time, dVector & ) const;
  inline void plot( const vField &, const Size, const dVector & ,
                    const Ordinal, const Ordinal, const Ordinal,
                    const Ordinal) const;
};

void Burgers::RobinControlBC::apply( const Scalar t, const vField &F ) {
  for (LocalSize n=0; n<F[0]->nbc; ++n)   // loop over field boundaries
    if (F[0]->bc[n]->type == type )
      for (vField::size_type i=0; i<F.size(); ++i)
        F[i]->bc[n]->B->u = F[i]->bc[n]->S->u;
}

/// \f$\mu u_{,n} = \phi_R - \theta n u\f$
void Burgers::RobinControlBC::apply_flux( const Scalar t, const vField &F ) {
  dVector dv;
  if (data.size()==0) {
    for (LocalSize n=0; n<F[0]->nbc; ++n) {  // loop over field boundaries
      if (F[0]->bc[n]->type == type) {
        for (vField::size_type i=0; i<F.size(); ++i) {
          const LocalSize sid = F[i]->bc[n]->sid;
          const LocalSize qtot = F[i]->bc[n]->elmt->side[sid]->qtot();
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
    }
  } else {
    LocalSize offset=0;
    for (LocalSize n=0; n<F[0]->nbc; ++n) {  // loop over field boundaries
      if (F[0]->bc[n]->type == type ) {
        for (vField::size_type i=0; i<F.size(); ++i) {
          const LocalSize sid = F[i]->bc[n]->sid;
          dv.alias(*(const_cast<dVector*>(&data)), offset,
                   F[i]->bc[n]->B->qtot());
          dVector sv(F[i]->bc[n]->S->qtot());
          F[i]->bc[n]->elmt->load_side(F[i]->bc[n]->elmt->u,sid,sv);
          multiply( theta, sv, F[i]->bc[n]->B->u);
          dvmul( F[i]->bc[n]->elmt->side[sid]->nx(), F[i]->bc[n]->B->u);
          scale(-1.0, F[i]->bc[n]->B->u );
          daxpy( 1.0, dv, F[i]->bc[n]->B->u );
          scale(-1.0, F[i]->bc[n]->B->u );  // since normal is reversed
          offset += F[i]->bc[n]->B->qtot();
#ifdef REO_CONSISTENT_BC
          scale( 2.0, F[i]->bc[n]->B->u );
          F[i]->bc[n]->B->u.Add(F[i]->bc[n]->S->u);
#endif
        }
      }
    }
  }
}

/// Adjoint boundary term \f$<u^* U u' + \sigma^* u' - \sigma' u^*>_\Gamma\f$

void Burgers::RobinControlBC::adjoint_apply( const Scalar t,
                                             const vField &state,
                                             const vField &adjoint) {
  for (LocalSize n=0; n<adjoint[0]->nbc; ++n)   // loop over field boundaries
    if (adjoint[0]->bc[n]->type == type )
      for (vField::size_type i=0; i<adjoint.size(); ++i)
        adjoint[i]->bc[n]->B->u = adjoint[i]->bc[n]->S->u ;
}

void Burgers::RobinControlBC::adjoint_apply_flux( const Scalar t,
                                                  const vField &state,
                                                  const vField &adjoint) {
  for (LocalSize n=0; n<adjoint[0]->nbc; ++n)   // loop over field boundaries
    if (adjoint[0]->bc[n]->type == type )
      for (vField::size_type i=0; i<adjoint.size(); ++i) {
        const LocalSize sid = adjoint[i]->bc[n]->sid;
        dVector av(adjoint[i]->bc[n]->S->qtot());
        dVector sv(state[i]->bc[n]->S->qtot());
#ifdef REO_BURGERS_NO_CONVECTION
        sv = 0.0;
#else
        sv = state[i]->bc[n]->B->u;
#endif
        sv += theta;  // + since normal is reversed
        adjoint[i]->bc[n]->elmt->load_side(adjoint[i]->bc[n]->elmt->u,sid,av);
        dvmul(adjoint[i]->bc[n]->elmt->side[sid]->nx(), av,
              adjoint[i]->bc[n]->B->u);
        dvmul(sv, adjoint[i]->bc[n]->B->u); // reversed normal accounted above
#ifdef REO_CONSISTENT_BC
        scale( 2.0, adjoint[i]->bc[n]->B->u );
        adjoint[i]->bc[n]->B->u.Add(adjoint[i]->bc[n]->S->u);
#endif
      }
}

Scalar Burgers::RobinControlBC::inner_product( const dVector &Y ) const {
  assert( Y.size() == data.size() );
  if (data.size() == 0) return 0.0;
  return dot( data, Y );
}

void Burgers::RobinControlBC::set_direction( dVector &out ) {
  if (data.size()==0) return;
  assert( data_size() == out.size() );
  out = data = 1.0;
}

void Burgers::RobinControlBC::objective_function_gradient( const vField &state,
  const vField &adjoint, const Scalar time, dVector &grad ) const
{
  if (data.size()==0) return;
  LocalSize offset=0;
  dVector dv, gv;
  // loop over state boundaries
  for (LocalSize n=0; n<state[0]->nbc; n++) {
    if (state[0]->bc[n]->type == type ) {
      // state and adjoint must have compatible sides
      assert( state[0]->bc[n]->S->qtot() == adjoint[0]->bc[n]->S->qtot() );
      const LocalSize qtot = adjoint[0]->bc[n]->S->qtot();
      const LocalSize sid  = adjoint[0]->bc[n]->sid;
      dv.alias( *(const_cast<dVector*>(&data)), offset, qtot );
      gv.alias( *(const_cast<dVector*>(&grad)), offset, qtot );
      // grad(J) = penalty * control + \lambda_{bc}
      multiply( penalty, dv, gv );
      dVector av(qtot);
      adjoint[0]->bc[n]->elmt->load_side(adjoint[0]->bc[n]->elmt->u,sid,av);
      daxpy( 1.0, av, gv );
      offset += qtot;
    }
  }
}

void Burgers::RobinControlBC::plot( const vField &state, const Size goffset,
                                    const dVector &Gphi,
                                    const Ordinal npredict,
                                    const Ordinal ntout,
                                    const Ordinal nsstep,
                                    const Ordinal riter) const {
  const Ordinal offset = numeric_cast<Ordinal>(goffset);
  dVector dv;
  int ncontrol =0;
  char tmp[80];
  string fname;
  for (LocalSize n=0; n<state[0]->nbc; n++) {  // loop over state boundaries
    if (state[0]->bc[n]->type == type ) {
      sprintf(tmp,"%s.%lld.dat",type.c_str(),(long long)riter);
      fname = fname + tmp;
      FILE *opt_stat = fopen(fname.c_str(),"w");
      const LocalSize sid = state[0]->bc[n]->sid;
      Scalar x;
#if 0
      Point* pside = new Point[state[0]->bc[n]->elmt->side[sid]->qtot()];
      state[0]->bc[n]->elmt->get_side_coordinates(sid,pside);
      x = pside[0].x;
      delete pside;
#else
      if(sid ==0)
        x =  (*state[0]->bc[n]->elmt->C)[0].x;
      else
        x =  (*state[0]->bc[n]->elmt->C)[state[0]->bc[n]->elmt->qtot-1].x;
#endif
      fprintf(opt_stat, "# Robin Control at %11.4e @ %lld steps\n",
              x, (long long)npredict);

      // this should be independent of the TimeInt method [ssc]
      for(Ordinal i=0; i<=npredict; i+=ntout){ // nsstep is nsstep for RK4
        dv.alias( *(const_cast<dVector*>(&Gphi)),
                  offset+(nsstep*i)*data_size(), data_size() );
        fprintf(opt_stat,"%5lld %17.10e\n",(long long)i,dv[ncontrol]);
      }
      fclose(opt_stat);
      ncontrol++;
    }
  }
}

//===========================================================================
//                     Distributed Control Source
//===========================================================================

/// Distributed control source term
class Burgers::DistributedControl : public Source, public Ctrl {
  Scalar value;            ///< default value
  //mutable vField F, G;   ///< local scratch space
public:
  DistributedControl( const string t, ifstream &in, const vField &S)
    : Source(t) {
    // cout<<"DistributedControl( ifstream &in, "<<qtot<<")"<<endl;
    for (vField::size_type i=0; i<S.size(); i++) {
      F.push_back( new Field(S[i]) );
      G.push_back( new Field(S[i]) );  // make temporary vectory field
    }
    scan_lb(in);
#ifndef DGM_USE_TIME_REG
    if (!(in >> penalty >> value))
      error("Burgers::DistributedControl: Cannot read penalty and value");
#else
    if (!(in >> penalty >> penalty_t >> value))
      error("Burgers::DistributedControl: penalty, penalty_t and value");
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
#ifdef DGM_DEBUG_CTRL
  inline Scalar cost() const {
    Scalar result = Ctrl::cost();
    cout<<"Cost("<<type<<") = "<<result<<endl;
    return result;
  }
#endif
  inline void set_direction( dVector & );
  inline void objective_function_gradient( const vField &, const vField &,
      const Scalar time, dVector & ) const;

  inline void plot( const vField &, const Size, const dVector & ,
                    const Ordinal, const Ordinal, const Ordinal,
                    const Ordinal) const;
};

void Burgers::DistributedControl::apply( const Scalar, const vField &,
                                         vField &U) {
  assert( data_size() == U.qtot() );
  // PROJECT_CONTROL_TO_STATE
  // F.fill(data);
  // F.project(scratch);
  // axpy( -1.0, scratch, U );
  subtract( data, U[0] );
}

Scalar Burgers::DistributedControl::inner_product( const dVector &Y ) const {
  F.fill( data );
  G.fill( Y );
  return vField::local_L2_inner_product( F, G );
}

void Burgers::DistributedControl::set_direction( dVector &out ) {
  assert( data_size() == out.size() );
  const vField &phi_d = F;
  LocalSize i = 0;
  for(LocalSize j=0; j<phi_d[0]->ne; ++j)
    for(LocalSize k=0; k<phi_d[0]->el[j]->qtot; ++k, ++i)
      out[i] = data[i] = sin( 2.0 * pi * phi_d[0]->el[j]->C->x[k] );
}

void Burgers::DistributedControl::objective_function_gradient(
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

void Burgers::DistributedControl::plot( const vField &state, const Size goffset,
                                        const dVector &Gphi,
                                        const Ordinal npredict,
                                        const Ordinal ntout,
                                        const Ordinal nsstep,
                                        const Ordinal riter) const {
  const Ordinal offset = numeric_cast<Ordinal>(goffset);
  dVector dv;
  char tmp[80];
  string fname;
  for(Ordinal i=0; i<=npredict; i+=ntout) {
    sprintf(tmp,"%s.%lld_%lld.dat",type.c_str(),(long long)i,(long long)riter);
    fname = tmp;
    dv.alias( *(const_cast<dVector*>(&Gphi)),
              offset+(nsstep*i)*data_size(), data_size() );
    F.fill(dv);
    F.tecplot(fname,"Distributed Control");
  }
}

//===========================================================================
//                     Steady Control Variants
//===========================================================================

/// Steady Dirichlet control boundary condition
class Burgers::SteadyDirichletControlBC : public DirichletControlBC{
public:
  SteadyDirichletControlBC( const string t, ifstream &in)
    : DirichletControlBC(t,in) {
  }
  bool steady() const {return true;}
};

/// Steady Neumann control boundary condition
class Burgers::SteadyNeumannControlBC : public NeumannControlBC {
public:
  SteadyNeumannControlBC( const string t, ifstream &in )
    : NeumannControlBC(t,in)  {
  }
  bool steady() const {return true;}
};

/// Steady Robin control boundary condition
class Burgers::SteadyRobinControlBC : public RobinControlBC {
public:
  SteadyRobinControlBC( const string t, ifstream &in )
    : RobinControlBC(t,in)  {
  }
  bool steady() const {return true;}
};

/// Steady distributed (in space) source control
class Burgers::SteadyDistributedControl : public DistributedControl{
public:
  SteadyDistributedControl( const string t, ifstream &in, const vField &S)
    : DistributedControl(t,in,S) {
  }
  bool steady() const {return true;}
};

} // namespace Reo

#endif  // REO_BURGERS_BC_HPP
