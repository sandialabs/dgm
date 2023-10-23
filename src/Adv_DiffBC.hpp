#ifndef REO_ADV_DIFF_BC_HPP
#define REO_ADV_DIFF_BC_HPP

/** \file Adv_DiffBC.hpp
    \brief Advection diffusion boundary conditions
    \author Scott Collis
*/

// system includes
#include <limits>
#include <sstream>

// DGM includes
#include "BC.hpp"
#include "Source.hpp"
#include "Ctrl.hpp"
using namespace DGM;

// Reo includes
#include "ReoConfig.hpp"

namespace Reo {

//===========================================================================
//                            Dirichlet BC
//===========================================================================

/// Constant valued Dirichlet boundary condition
class Adv_Diff::DirichletBC : public BC {
protected:
  Scalar value;
public:
  DirichletBC(const string t, const Scalar v=0) : BC(t), value(v) { }
  DirichletBC(const string t, ifstream &in) : BC(t), value(0) {
    scan_lb(in);
    if (!(in >> value))
      error("Adv_Diff::DirichletBC: could not read value");
    scan_rb(in);
  }
  inline void apply( const Scalar, const vField & );
  inline void apply_flux( const Scalar, const vField & );

  inline void adjoint_apply( const Scalar, const vField &, const vField & );
  inline void adjoint_apply_flux( const Scalar, const vField &,
                                  const vField & );
};

void Adv_Diff::DirichletBC::apply( const Scalar t, const vField &F ) {
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

void Adv_Diff::DirichletBC::apply_flux( const Scalar t, const vField &F ) {
  for (LocalSize n=0; n<F[0]->nbc; ++n) { // loop over field boundaries
    if (F[0]->bc[n]->type == type ) {
      for (vField::size_type i=0; i<F.size(); ++i) {
        F[i]->bc[n]->B->u = F[i]->bc[n]->S->u;
        scale(-1.0, F[i]->bc[n]->B->u );
      }
    }
  }
}

// Adjoint boundary term <u^* U u' + \sigma^* u' - \sigma' u^*>_\Gamma
void Adv_Diff::DirichletBC::adjoint_apply(const Scalar t,
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

void Adv_Diff::DirichletBC::adjoint_apply_flux( const Scalar t,
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
//                       Unsteady Dirichlet BC
//===========================================================================

/// Single frequency transient Dirichlet boundary condition
class Adv_Diff::UnsteadyDirichletBC : public DirichletBC {
  Scalar freq;   ///< frequency
  Scalar t0;     ///< reference time
public:
  UnsteadyDirichletBC(const string t, ifstream &in) :
    DirichletBC(t), freq(0), t0(0)
  {
    scan_lb(in);
    if (!(in >> value >> freq >> t0))
      error("Adv_Diff::UnsteadyDirichletBC: could not read value, freq, t0");
    scan_rb(in);
  }
  inline void apply( const Scalar t, const vField &F ) {
    for (LocalSize n=0; n<F[0]->nbc; ++n)   // loop over field boundaries
      if (F[0]->bc[n]->type == type )
        for (vField::size_type i=0; i<F.size(); ++i) {
          F[i]->bc[n]->B->u = value*sin(two*pi*freq*(t-t0));
#ifdef REO_CONSISTENT_BC
          scale( 2.0, F[i]->bc[n]->B->u );
          F[i]->bc[n]->B->u.Sub(F[i]->bc[n]->S->u);
#endif
        }
  }
};

//===========================================================================
//                            Neumann BC
//===========================================================================

/// Constant valued Neumann boundary condition
/*! \todo Generalize to arbitrary convective velocities */
class Adv_Diff::NeumannBC : public BC {
  Scalar value;
  Scalar cx, cy, cz;
public:
  NeumannBC(const string t, const Scalar v=0, const Scalar c_x=0,
            const Scalar c_y=0, const Scalar c_z=0)
    : BC(t), value(v), cx(c_x), cy(c_y), cz(c_z)
  {
    if (cy!=0.0)
      DGM::Comm::World->cout()<<"WARNING: Adv_Diff::NeumannBC non-zero "
      "cy detected,\n  adjoint_apply_flux likely incorrect."<<endl;
    if (cz!=0.0)
      DGM::Comm::World->cout()<<"WARNING: Adv_Diff::NeumannBC non-zero "
      "cz detected,\n  adjoint_apply_flux likely incorrect."<<endl;
  }
  NeumannBC(const string t, ifstream &in,
            Scalar c_x, Scalar c_y, Scalar c_z)
    : BC(t), value(0), cx(c_x), cy(c_y), cz(c_z) {
    scan_lb(in);
    if (!(in >> value)) error("Adv_Diff::NeumannBC: could not read value");
    scan_rb(in);
    if (cy!=0.0)
      DGM::Comm::World->cout()<<"WARNING: Adv_Diff::NeumannBC non-zero "
      "cy detected,\n  adjoint_apply_flux likely incorrect."<<endl;
    if (cz!=0.0)
      DGM::Comm::World->cout()<<"WARNING: Adv_Diff::NeumannBC non-zero "
      "cz detected,\n  adjoint_apply_flux likely incorrect."<<endl;  }
  inline void apply( const Scalar, const vField & );
  inline void apply_flux( const Scalar, const vField & );

  inline void adjoint_apply( const Scalar, const vField &, const vField & );
  inline void adjoint_apply_flux( const Scalar, const vField &,
                                  const vField & );
};

void Adv_Diff::NeumannBC::apply( const Scalar t, const vField &F ) {
  for (LocalSize n=0; n<F[0]->nbc; ++n)
    if (F[0]->bc[n]->type == type )
      for (vField::size_type i=0; i<F.size(); ++i)
        F[i]->bc[n]->B->u = F[i]->bc[n]->S->u;
}

void Adv_Diff::NeumannBC::apply_flux( const Scalar t, const vField &F ) {
  for (LocalSize n=0; n<F[0]->nbc; ++n) {
    if (F[0]->bc[n]->type == type ) {
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
  }
}

// Adjoint boundary term < u^* U u' + \sigma^* u' - \sigma' u^* >_\Gamma
void Adv_Diff::NeumannBC::adjoint_apply( const Scalar t,
                                         const vField &state,
                                         const vField &adjoint) {
  for (LocalSize n=0; n<adjoint[0]->nbc; ++n)
    if (adjoint[0]->bc[n]->type == type )
      for (vField::size_type i=0; i<adjoint.size(); ++i)
        adjoint[i]->bc[n]->B->u = adjoint[i]->bc[n]->S->u;
}

void Adv_Diff::NeumannBC::adjoint_apply_flux( const Scalar t,
                                              const vField &state,
                                              const vField &adjoint) {
  for (LocalSize n=0; n<adjoint[0]->nbc; ++n)
    if (adjoint[0]->bc[n]->type == type )
      for (vField::size_type i=0; i<adjoint.size(); ++i) {
        const LocalSize sid = adjoint[i]->bc[n]->sid;
        dVector av(adjoint[i]->bc[n]->S->qtot());
        adjoint[i]->bc[n]->elmt->load_side(adjoint[i]->bc[n]->elmt->u,sid,av);
        scale( cx, av );
        adjoint[i]->bc[n]->B->u = av;
        dvmul(adjoint[i]->bc[n]->elmt->side[sid]->nx(),adjoint[i]->bc[n]->B->u);
#ifdef REO_CONSISTENT_BC
        scale( 2.0, adjoint[i]->bc[n]->B->u );
        adjoint[i]->bc[n]->B->u.Add(adjoint[i]->bc[n]->S->u);
#endif
      }
}

//===========================================================================
//                            Robin BC
//===========================================================================

/// Constant valued Robin boundary condition
/*! \todo Generalize to arbitrary convective velocities */
class Adv_Diff::RobinBC : public BC {
  Scalar theta;
  Scalar value;
  Scalar cx, cy, cz;
public:
  /// Default constructor
  RobinBC(const string t, const Scalar value_=0.0, const Scalar theta_=1.0,
          const Scalar c_x=0, const Scalar c_y=0, const Scalar c_z=0 )
    : BC(t), theta(theta_), value(value_), cx(c_x), cy(c_y), cz(c_z)
  {
    if (cy!=0.0)
      DGM::Comm::World->cout()<<"WARNING: Adv_Diff::RobinBC non-zero "
      "cy detected,\n  adjoint_apply_flux likely incorrect."<<endl;
    if (cz!=0.0)
      DGM::Comm::World->cout()<<"WARNING: Adv_Diff::RobinBC non-zero "
      "cz detected,\n  adjoint_apply_flux likely incorrect."<<endl;
  }
  /// Construct from a file stream
  RobinBC(const string t, ifstream &in,
          Scalar c_x, Scalar c_y, Scalar c_z)
    : BC(t), theta(0), value(0), cx(c_x), cy(c_y), cz(c_z) {
    scan_lb(in);
    if (!(in >> value >> theta))
      error("Adv_Diff::RobinBC: could not read theta and value");
    scan_rb(in);
    if (cy!=0.0)
      DGM::Comm::World->cout()<<"WARNING: Adv_Diff::RobinBC non-zero "
      "cy detected,\n  adjoint_apply_flux likely incorrect."<<endl;
    if (cz!=0.0)
      DGM::Comm::World->cout()<<"WARNING: Adv_Diff::RobinBC non-zero "
      "cz detected,\n  adjoint_apply_flux likely incorrect."<<endl;
  }
  inline void apply( const Scalar, const vField & );
  inline void apply_flux( const Scalar, const vField &);

  inline void adjoint_apply( const Scalar, const vField &, const vField & );
  inline void adjoint_apply_flux( const Scalar, const vField &,
                                  const vField & );
};

/// Apply the state boundary condition
void Adv_Diff::RobinBC::apply( const Scalar t, const vField &F ) {
  for (LocalSize n=0; n<F[0]->nbc; ++n)   // loop over field boundaries
    if (F[0]->bc[n]->type == type )
      for (vField::size_type i=0; i<F.size(); ++i)
        F[i]->bc[n]->B->u = F[i]->bc[n]->S->u;
}

/// Apply the flux boundary condition
/** \f[ \mu u_{,n} = \phi_R - + n \dot \theta u \f] */
void Adv_Diff::RobinBC::apply_flux( const Scalar t, const vField &F ) {
  LocalSize sid, qtot;
  dVector dv;
  for (LocalSize n=0; n<F[0]->nbc; ++n) {  // loop over field boundaries
    if (F[0]->bc[n]->type == type) {
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
  }
}

/// Apply adjoint boundary condition
/** Adjoint boundary term
    \f[ <u^* U u' + \sigma^* u' - \sigma' u^* >_\Gamma\f]
*/
void Adv_Diff::RobinBC::adjoint_apply( const Scalar t,
                                       const vField &state,
                                       const vField &adjoint) {
  for (LocalSize n=0; n<adjoint[0]->nbc; ++n)   // loop over field boundaries
    if (adjoint[0]->bc[n]->type == type )
      for (vField::size_type i=0; i<adjoint.size(); ++i)
        adjoint[i]->bc[n]->B->u = adjoint[i]->bc[n]->S->u;
}

/// Apply adjoint flux boundary condition
/** \f[ \mu u^*_n = 0 \f]. */
void Adv_Diff::RobinBC::adjoint_apply_flux( const Scalar t,
                                            const vField &state,
                                            const vField &adjoint) {
  for (LocalSize n=0; n<adjoint[0]->nbc; ++n)   // loop over field boundaries
    if (adjoint[0]->bc[n]->type == type )
      for (vField::size_type i=0; i<adjoint.size(); ++i){
        const LocalSize sid = adjoint[i]->bc[n]->sid;
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

/// Outflow boundary condition
class Adv_Diff::OutflowBC : public BC {
public:
  OutflowBC( const string t) : BC(t) { }
  OutflowBC( const string t, ifstream &in ) : BC(t) {
    scan_lb(in);
    scan_rb(in);
  }
  inline void apply( const Scalar, const vField & );
  inline void apply_flux( const Scalar, const vField & );

  inline void adjoint_apply( const Scalar, const vField &, const vField & );
  inline void adjoint_apply_flux( const Scalar, const vField &,
                                  const vField & );
};

/// Apply adjoint boundary
/** \f[ < u^* U u' + \sigma^* u' - \sigma' u^* >_\Gamma \f] */
void Adv_Diff::OutflowBC::apply( const Scalar t, const vField &F ) {
  for (LocalSize n=0; n<F[0]->nbc; ++n)         // loop over field boundaries
    if (F[0]->bc[n]->type == type )
      for (vField::size_type i=0; i<F.size(); ++i)
        F[i]->bc[n]->B->u = F[i]->bc[n]->S->u;
}

void Adv_Diff::OutflowBC::apply_flux( const Scalar t, const vField &F ) {
  for (LocalSize n=0; n<F[0]->nbc; ++n) {       // loop over field boundaries
    if (F[0]->bc[n]->type == type ) {
      for (vField::size_type i=0; i<F.size(); ++i) {
        F[i]->bc[n]->B->u = F[i]->bc[n]->S->u;
        scale(-1.0, F[i]->bc[n]->B->u );  // switch sign due to normal vector
      }
    }
  }
}

void Adv_Diff::OutflowBC::adjoint_apply( const Scalar t,
                                         const vField &state,
                                         const vField &adjoint ) {
  for (LocalSize n=0; n<adjoint[0]->nbc; ++n)   // loop over field boundaries
    if (adjoint[0]->bc[n]->type == type )
      for (vField::size_type i=0; i<adjoint.size(); ++i)
        adjoint[i]->bc[n]->B->u = 0.0;
}

/// Adjoint boundary term
/** \f[ < u^* U {\vec n} >_\Gamma \f] */
void Adv_Diff::OutflowBC::adjoint_apply_flux( const Scalar t,
                                              const vField &state,
                                              const vField &adjoint ) {
  for (LocalSize n=0; n<adjoint[0]->nbc; ++n)   // loop over field boundaries
    if (adjoint[0]->bc[n]->type == type )
      for (vField::size_type i=0; i<adjoint.size(); ++i) {
        adjoint[i]->bc[n]->B->u = 0.0;
        scale(-1.0, adjoint[i]->bc[n]->B->u);//switch sign due to normal vector
      }
}

//===========================================================================
//                         Dirichlet Control BC
//===========================================================================

/// Unsteady Dirichlet boundary control
class Adv_Diff::DirichletControlBC : public BC , public Ctrl {
  Scalar value;
public:
  DirichletControlBC( const string t, ifstream &in ) : BC(t), value(0) {
    scan_lb(in);
#ifndef DGM_USE_TIME_REG
    if (!(in >> penalty >> value))
      error("Adv_Diff::DirichletControlBC could not read data.");
#else
    if (!(in >> penalty >> penalty_t >> value))
      error("Adv_Diff::DirichletControlBC could not read data.");
#endif
    scan_rb(in);

  }
  inline void apply( const Scalar, const vField & );
  inline void apply_flux( const Scalar, const vField & );

  inline void adjoint_apply( const Scalar, const vField &, const vField & );
  inline void adjoint_apply_flux( const Scalar, const vField &,
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

void Adv_Diff::DirichletControlBC::apply( const Scalar t, const vField &F ) {
  if (data.size()==0) {
    for (LocalSize n=0; n<F[0]->nbc; ++n)   // loop over field boundaries
      if (F[0]->bc[n]->type == type )
        for (vField::size_type i=0; i<F.size(); ++i) {
          F[i]->bc[n]->B->u = value;
#ifdef REO_CONSISTENT_BC
          scale( 2.0, F[i]->bc[n]->B->u );
          F[i]->bc[n]->B->u.Sub(F[i]->bc[n]->S->u);
#endif
        }
  } else {
    LocalSize offset=0;
    dVector dv;
    for (LocalSize n=0; n<F[0]->nbc; ++n) {   // loop over field boundaries
      if (F[0]->bc[n]->type == type ) {
        for (vField::size_type i=0; i<F.size(); ++i) {
          dv.alias( data, offset, F[i]->bc[n]->B->qtot());
          F[i]->bc[n]->B->u = dv;
#ifdef REO_CONSISTENT_BC
          scale( 2.0, F[i]->bc[n]->B->u );
          F[i]->bc[n]->B->u.Sub(F[i]->bc[n]->S->u);
#endif
          offset += F[i]->bc[n]->B->qtot();
        }
      }
    }
  }
}

void Adv_Diff::DirichletControlBC::apply_flux( const Scalar t,
                                               const vField &F ) {
  for (LocalSize n=0; n<F[0]->nbc; ++n)   // loop over field boundaries
    if (F[0]->bc[n]->type == type )
      for (vField::size_type i=0; i<F.size(); ++i) {
        F[i]->bc[n]->B->u = F[i]->bc[n]->S->u;
        scale(-1.0, F[i]->bc[n]->B->u );
      }
}

/// Adjoint boundary term
/** \f[ < u^* U u' + \sigma^* u' - \sigma' u^* >_\Gamma \f] */
void Adv_Diff::DirichletControlBC::adjoint_apply( const Scalar t,
                                                  const vField &state,
                                                  const vField &adjoint) {
  for (LocalSize n=0; n<adjoint[0]->nbc; ++n)   // loop over field boundaries
    if (adjoint[0]->bc[n]->type == type )
      for (vField::size_type i=0; i<adjoint.size(); ++i) {
        adjoint[i]->bc[n]->B->u = 0.0;
#ifdef REO_CONSISTENT_BC
        scale( 2.0, adjoint[i]->bc[n]->B->u );
        adjoint[i]->bc[n]->B->u.Sub(adjoint[i]->bc[n]->S->u);
#endif
      }
}

void Adv_Diff::DirichletControlBC::adjoint_apply_flux( const Scalar t,
                                                       const vField &state,
                                                       const vField &adjoint) {
  for (LocalSize n=0; n<adjoint[0]->nbc; ++n)   // loop over field boundaries
    if (adjoint[0]->bc[n]->type == type )
      for (vField::size_type i=0; i<adjoint.size(); ++i) {
        adjoint[i]->bc[n]->B->u = adjoint[i]->bc[n]->S->u;
        scale(-1.0, adjoint[i]->bc[n]->B->u );
      }
}

Scalar Adv_Diff::DirichletControlBC::inner_product( const dVector &Y ) const {
  assert( Y.size() == data.size() );
  if (data.size() == 0) return 0.0;
  return dot( data, Y );
}

void Adv_Diff::DirichletControlBC::set_direction( dVector &out ) {
  if (data.size()==0) return;
  assert( data_size() == out.size() );
  out = data = 1.0;
}

void Adv_Diff::DirichletControlBC::objective_function_gradient(
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
      dv.alias( data, offset, state[0]->bc[n]->S->qtot() );
      gv.alias( grad, offset, state[0]->bc[n]->S->qtot() );
      // use B side here to get sign correct
      daxpy( penalty, dv, adjoint[0]->bc[n]->B->u, gv );
      offset += state[0]->bc[n]->S->qtot();
    }
  }
}

void Adv_Diff::DirichletControlBC::plot( const vField &state,
                                         const Size goffset,
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
      LocalSize sid = state[0]->bc[n]->sid;
      Scalar x;
      if(sid ==0)
        x =  (*state[0]->bc[n]->elmt->C)[0].x;
      else
        x =  (*state[0]->bc[n]->elmt->C)[state[0]->bc[n]->elmt->qtot-1].x;
      fprintf(opt_stat, "# Dirichlet Control at %11.4e @ %lld steps\n",
              x, (long long)npredict);
      for(Ordinal i=0;i<=npredict;i+=ntout){ // nsstep is nsstep for RK4
        dv.alias( Gphi, offset+(nsstep*i)*data_size(), data_size() );
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

/// Unsteady Neumann boundary control
class Adv_Diff::NeumannControlBC : public BC , public Ctrl {
  Scalar cx, cy, cz;
  Scalar value;
public:
  NeumannControlBC( const string t, ifstream &in,
                    Scalar c_x, Scalar c_y, Scalar c_z )
    : BC(t), cx(c_x), cy(c_y), cz(c_z), value(0) {
    scan_lb(in);
#ifndef DGM_USE_TIME_REG
    if (!(in >> penalty >> value))
      error("Adv_Diff::NeumannControlBC could not read data.");
#else
    if (!(in >> penalty >> penalty_t >> value))
      error("Adv_Diff::NeumannControlBC could not read data.");
#endif
    scan_rb(in);
    if (cy!=0.0) error("Adv_Diff::NeumannControlBC non-zero cy detected");
    if (cz!=0.0) error("Adv_Diff::NeumannControlBC non-zero cz detected");
  }

  inline void apply( const Scalar, const vField & );
  inline void apply_flux( const Scalar, const vField & );

  inline void adjoint_apply( const Scalar, const vField &, const vField & );
  inline void adjoint_apply_flux( const Scalar, const vField &,
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

void Adv_Diff::NeumannControlBC::apply( const Scalar t, const vField &F ) {
  for (LocalSize n=0; n<F[0]->nbc; ++n)   // loop over field boundaries
    if (F[0]->bc[n]->type == type )
      for (vField::size_type i=0; i<F.size(); ++i)
        F[i]->bc[n]->B->u = F[i]->bc[n]->S->u;
}

void Adv_Diff::NeumannControlBC::apply_flux( const Scalar t,
                                             const vField &F ) {
  if (data.size()==0) {
    for (LocalSize n=0; n<F[0]->nbc; ++n)         // loop over field boundaries
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
    for (LocalSize n=0; n<F[0]->nbc; ++n) {       // loop over field boundaries
      if (F[0]->bc[n]->type == type ) {
        for (vField::size_type i=0; i<F.size(); ++i) {
          dv.alias( data, offset, F[i]->bc[n]->B->qtot());
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

/// Adjoint boundary term
/** \f[ < u^* U u' + \sigma^* u' - \sigma' u^* >_\Gamma \f] */
void Adv_Diff::NeumannControlBC::adjoint_apply( const Scalar t,
                                                const vField &state,
                                                const vField &adjoint) {
  for (LocalSize n=0; n<adjoint[0]->nbc; ++n)   // loop over field boundaries
    if (adjoint[0]->bc[n]->type == type )
      for (vField::size_type i=0; i<adjoint.size(); ++i)
        adjoint[i]->bc[n]->B->u = adjoint[i]->bc[n]->S->u;
}

void Adv_Diff::NeumannControlBC::adjoint_apply_flux( const Scalar t,
                                                     const vField &state,
                                                     const vField &adjoint) {
  for (LocalSize n=0; n<adjoint[0]->nbc; ++n)   // loop over field boundaries
    if (adjoint[0]->bc[n]->type == type )
      for (vField::size_type i=0; i<adjoint.size(); ++i) {
        const LocalSize sid = adjoint[i]->bc[n]->sid;
        dVector av(adjoint[i]->bc[n]->S->qtot());
        dVector sv(state[i]->bc[n]->S->qtot());
        sv = -cx;
        adjoint[i]->bc[n]->elmt->load_side(adjoint[i]->bc[n]->elmt->u,sid,av);
        dvmul(adjoint[i]->bc[n]->elmt->side[sid]->nx(), av,
              adjoint[i]->bc[n]->B->u);
        dvmul(sv,adjoint[i]->bc[n]->B->u);
        scale(-1.0, adjoint[i]->bc[n]->B->u);  // since normal is reversed
#ifdef REO_CONSISTENT_BC
        scale( 2.0, adjoint[i]->bc[n]->B->u );
        adjoint[i]->bc[n]->B->u.Add(adjoint[i]->bc[n]->S->u);
#endif
      }
}

Scalar Adv_Diff::NeumannControlBC::inner_product( const dVector &Y ) const {
  assert( Y.size() == data.size() );
  if (data.size() == 0) return 0.0;
  return dot( data, Y );
}

void Adv_Diff::NeumannControlBC::set_direction( dVector &out ) {
  if (data.size()==0) return;
  assert( data_size() == out.size() );
  out = data = 1.0;
}

void Adv_Diff::NeumannControlBC::objective_function_gradient(
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
      const LocalSize sid = adjoint[0]->bc[n]->sid;
      dv.alias( data, offset, qtot );
      gv.alias( grad, offset, qtot );
      // grad(J) = penalty * control - \lambda_{bc}
      multiply( penalty, dv, gv );
      dVector av(qtot);
      adjoint[0]->bc[n]->elmt->load_side(adjoint[0]->bc[n]->elmt->u,sid,av);
      daxpy( 1.0, av, gv );
      offset += state[0]->bc[n]->S->qtot();
    }
  }
}

void Adv_Diff::NeumannControlBC::plot( const vField &state,
                                       const Size goffset,
                                       const dVector &Gphi,
                                       const Ordinal npredict,
                                       const Ordinal ntout,
                                       const Ordinal nsstep,
                                       const Ordinal riter) const {
  const Ordinal offset = numeric_cast<Ordinal>(goffset);
  dVector dv;
  int ncontrol=0;
  char tmp[80];
  string fname;
  for (LocalSize n=0; n<state[0]->nbc; n++) {  // loop over state boundaries
    if (state[0]->bc[n]->type == type ) {
      sprintf(tmp,"%s.%lld.dat",type.c_str(),(long long)riter);
      fname = fname + tmp;
      FILE *opt_stat = fopen(fname.c_str(),"w");
      LocalSize sid = state[0]->bc[n]->sid;
      Scalar x;
      if(sid ==0)
        x =  (*state[0]->bc[n]->elmt->C)[0].x;
      else
        x =  (*state[0]->bc[n]->elmt->C)[state[0]->bc[n]->elmt->qtot-1].x;
      fprintf(opt_stat, "# Neumann Control at %11.4e @ %lld steps\n",
              x, (long long)npredict);
      // this should be independent of the TimeInt method [ssc]
      for(Ordinal i=0;i<=npredict;i+=ntout){ // nsstep is nsstep for RK4
        dv.alias( Gphi, offset+(nsstep*i)*data_size(), data_size() );
        fprintf(opt_stat,"%5lld %17.10e\n", (long long)i, dv[ncontrol]);
      }
      fclose(opt_stat);
      ncontrol++;
    }
  }
}

//===========================================================================
//                         Robin Control BC
//===========================================================================

/// Unsteady Robin boundary control
class Adv_Diff::RobinControlBC : public BC, public Ctrl {
  const DGM::Comm::Ptr comm;        ///< Parallel communicator
  Scalar cx, cy, cz;
  Scalar theta;
  Scalar value;
public:
  RobinControlBC( const string t, ifstream &in, const DGM::Comm::Ptr comm_,
                  Scalar c_x, Scalar c_y, Scalar c_z )
    : BC(t), comm(comm_), cx(c_x), cy(c_y), cz(c_z), theta(0), value(0) {
    scan_lb(in);
#ifndef DGM_USE_TIME_REG
    if (!(in >> penalty >> value >> theta))
      error("Adv_Diff::RobinControlBC: penalty, value, theta.");
#else
    if (!(in >> penalty >> penalty_t >> value >> theta))
      error("Adv_Diff::RobinControlBC: penalty, penalty_t, value, theta.");
#endif
    scan_rb(in);
    if (cy!=0.0) error("Adv_Diff::RobinControlBC non-zero cy detected");
    if (cz!=0.0) error("Adv_Diff::RobinControlBC non-zero cz detected");
    // comm->cout()<<"Finished building RobinControlBC"<<endl;
  }
  inline void apply( const Scalar, const vField & );
  inline void apply_flux( const Scalar, const vField & );

  inline void adjoint_apply( const Scalar, const vField &, const vField & );
  inline void adjoint_apply_flux( const Scalar, const vField &,
                                  const vField & );

  inline Ctrl* ctrl() { return this; }
  inline const Ctrl* ctrl() const { return this; }

  // Ctrl methods
  void initialize() { Ctrl::initialize(); data=value; }  // set default value
  inline Scalar inner_product(const dVector &) const;
  inline void set_direction(dVector &);
  inline void objective_function_gradient( const vField &, const vField &,
      const Scalar time, dVector & ) const;
  inline void plot( const vField &, const Size, const dVector & ,
                    const Ordinal, const Ordinal, const Ordinal,
                    const Ordinal) const;

  // debugging output for Ctrl
  Ctrl::InfoType info() const {
    Ctrl::InfoType i;
    std::stringstream msg;
    msg << "(" << cx << "," << cy << "," << cz << ")";
    i["Convective velocity"] = msg.str();
    msg.str(""); msg << theta;
    i["Theta"] = msg.str(); msg.str("");
    msg << value;
    i["Initial value"] = msg.str(); msg.str("");
    return i;
  }

};

void Adv_Diff::RobinControlBC::apply( const Scalar t, const vField &F ) {
  for (LocalSize n=0; n<F[0]->nbc; ++n)   // loop over field boundaries
    if (F[0]->bc[n]->type == type )
      for (vField::size_type i=0; i<F.size(); ++i)
        F[i]->bc[n]->B->u = F[i]->bc[n]->S->u;
}

void Adv_Diff::RobinControlBC::apply_flux( const Scalar t, const vField &F ) {
  LocalSize sid, qtot;
  if (data.size()==0) {
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
          scale(-1.0, F[i]->bc[n]->B->u);   // since normal is reversed
#ifdef REO_CONSISTENT_BC
          scale( 2.0, F[i]->bc[n]->B->u );
          F[i]->bc[n]->B->u.Add(F[i]->bc[n]->S->u);
#endif
        }
  } else {
    LocalSize offset=0;
    dVector dv;
    for (LocalSize n=0; n<F[0]->nbc; ++n) {  // loop over field boundaries
      if (F[0]->bc[n]->type == type) {
        for (vField::size_type i=0; i<F.size(); ++i) {
          sid = F[i]->bc[n]->sid;
          dv.alias( data, offset, F[i]->bc[n]->B->qtot());
          dVector sv(F[i]->bc[n]->S->qtot());
          F[i]->bc[n]->elmt->load_side(F[i]->bc[n]->elmt->u,sid,sv);
          multiply( theta, sv, F[i]->bc[n]->B->u );
          dvmul( F[i]->bc[n]->elmt->side[sid]->nx(), F[i]->bc[n]->B->u );
          scale(-1.0, F[i]->bc[n]->B->u );
          daxpy( 1.0, dv, F[i]->bc[n]->B->u );
          scale(-1.0, F[i]->bc[n]->B->u);   // since normal is reversed
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

/// Adjoint boundary term
/** \f[ < u^* U u' + \sigma^* u' - \sigma' u^* >_\Gamma \f] */
void Adv_Diff::RobinControlBC::adjoint_apply( const Scalar t,
                                              const vField &state,
                                              const vField &adjoint) {
  for (LocalSize n=0; n<adjoint[0]->nbc; ++n)   // loop over field boundaries
    if (adjoint[0]->bc[n]->type == type )
      for (vField::size_type i=0; i<adjoint.size(); ++i)
        adjoint[i]->bc[n]->B->u = adjoint[i]->bc[n]->S->u ;
}

void Adv_Diff::RobinControlBC::adjoint_apply_flux( const Scalar t,
                                                   const vField &state,
                                                   const vField &adjoint) {
  for (LocalSize n=0; n<adjoint[0]->nbc; ++n)   // loop over field boundaries
    if (adjoint[0]->bc[n]->type == type )
      for (vField::size_type i=0; i<adjoint.size(); ++i) {
        LocalSize sid = adjoint[i]->bc[n]->sid;
        dVector av(adjoint[i]->bc[n]->S->qtot());
        dVector sv(state[i]->bc[n]->S->qtot());
        sv = -(cx + theta);
        adjoint[i]->bc[n]->elmt->load_side(adjoint[i]->bc[n]->elmt->u,sid,av);
        dvmul(adjoint[i]->bc[n]->elmt->side[sid]->nx(), av,
              adjoint[i]->bc[n]->B->u);
        dvmul(sv, adjoint[i]->bc[n]->B->u);
        scale(-1.0, adjoint[i]->bc[n]->B->u);  // since normal is reversed
#ifdef REO_CONSISTENT_BC
        scale( 2.0, adjoint[i]->bc[n]->B->u );
        adjoint[i]->bc[n]->B->u.Add(adjoint[i]->bc[n]->S->u);
#endif
      }
}

Scalar Adv_Diff::RobinControlBC::inner_product( const dVector &Y ) const {
  assert( Y.size() == data.size() );
  if (data.size() == 0) return 0.0;
  return dot( data, Y );
}

void Adv_Diff::RobinControlBC::set_direction(dVector &out) {
  if (data.size()==0) return;
  assert( data.size() == out.size() );
  out = data = 1.0;
}

/// Adjoint boundary term
/** \f[ < u^* U u' + \sigma^* u' - \sigma' u^* >_\Gamma \f] */
void Adv_Diff::RobinControlBC::objective_function_gradient(
    const vField &state, const vField &adjoint, const Scalar time,
    dVector &grad ) const
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
      dv.alias( data, offset, qtot );
      gv.alias( grad, offset, qtot );
      // grad(J) = penalty * control + \lambda_{bc}
      multiply( penalty, dv, gv );
      dVector av(qtot);
      adjoint[0]->bc[n]->elmt->load_side(adjoint[0]->bc[n]->elmt->u,sid,av);
      daxpy( 1.0, av, gv );
      offset += qtot;
    }
  }
}

void Adv_Diff::RobinControlBC::plot( const vField &state,
                                     const Size goffset,
                                     const dVector &Gphi,
                                     const Ordinal npredict,
                                     const Ordinal ntout,
                                     const Ordinal nsstep,
                                     const Ordinal riter) const {
  const Ordinal offset = numeric_cast<Ordinal>(goffset);
  dVector dv;
  int ncontrol=0;
  char tmp[80];
  string fname;
  for (LocalSize n=0; n<state[0]->nbc; n++) {  // loop over state boundaries
    if (state[0]->bc[n]->type == type ) {
      sprintf(tmp,"%s.%lld.dat",type.c_str(),(long long)riter);
      fname = fname + tmp;
      FILE *opt_stat = fopen(fname.c_str(),"w");
      const LocalSize sid = state[0]->bc[n]->sid;
      Scalar x;
      if(sid ==0)
        x = (*state[0]->bc[n]->elmt->C)[0].x;
      else
        x = (*state[0]->bc[n]->elmt->C)[state[0]->bc[n]->elmt->qtot-1].x;
      if (steady()) {
        fprintf(opt_stat, "# Steady Robin Control at x = %11.4e\n",x);
        dv.alias( Gphi, data_size() );
        fprintf(opt_stat,"%17.10e\n", dv[ncontrol]);
      } else {
        fprintf(opt_stat, "# Robin Control at x = %11.4e for %lld steps\n",
                x, (long long)npredict);
        // this should be independent of the TimeInt method [ssc]
        for(Ordinal i=0; i<=npredict; i+=ntout){ // nsstep is nsstep for RK4
          dv.alias( Gphi, offset+(nsstep*i)*data_size(), data_size() );
          fprintf(opt_stat,"%5lld %17.10e\n", (long long)i, dv[ncontrol]);
        }
      }
      fclose(opt_stat);
      ncontrol++;
    }
  }
}

//===========================================================================
//                     Distributed Control Source
//===========================================================================

/// Unsteady distributed source control
class Adv_Diff::DistributedControl : public Source, public Ctrl {
  Scalar value;            // default value
  //mutable vField F, G;   // local scratch space
public:
  DistributedControl( const string t, ifstream &in, const vField &S)
    : Source(t) {
    // cout<<"DistributedControl( ifstream &in, "<<qtot<<")"<<endl;
    for (vField::size_type i=0; i<S.size(); i++) {
      F.push_back( new Field(S[i]) );
      G.push_back( new Field(S[i]) );  // make temporary vector field
    }
    scan_lb(in);
#ifndef DGM_USE_TIME_REG
    if (!(in >> penalty >> value))
      error("Adv_Diff::DistributedControl::Cannot read data.");
#else
    if (!(in >> penalty >> penalty_t >> value))
      error("Adv_Diff::DistributedControl::Cannot read data.");
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

void Adv_Diff::DistributedControl::apply( const Scalar, const vField &,
                                          vField &U) {
  assert( data_size() == U.qtot() );
  // PROJECT_CONTROL_TO_STATE
  // F.fill(data);
  // F.project(scratch);
  // axpy( -1.0, scratch, U );
  subtract( data, U[0] );
}

Scalar Adv_Diff::DistributedControl::inner_product( const dVector &Y ) const {
  F.fill( data );
  G.fill( Y );
  return vField::local_L2_inner_product( F, G );
}

void Adv_Diff::DistributedControl::set_direction( dVector &out ) {
  assert( data_size() == out.size() );
  const vField &phi_d = F;
  LocalSize i = 0;
  for(LocalSize j=0; j<phi_d[0]->ne; ++j)
    for(Ordinal k=0; k<phi_d[0]->el[j]->qtot; ++k, ++i)
      out[i] = data[i] = sin( 2.0 * pi * phi_d[0]->el[j]->C->x[k] );
}

void Adv_Diff::DistributedControl::objective_function_gradient(
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

void Adv_Diff::DistributedControl::plot( const vField &state,
                                         const Size goffset,
                                         const dVector &Gphi,
                                         const Ordinal npredict,
                                         const Ordinal ntout,
                                         const Ordinal nsstep,
                                         const Ordinal riter ) const {
  const Ordinal offset = numeric_cast<Ordinal>(goffset);
  dVector dv;
  char tmp[80];
  string fname;
  for(Ordinal i=0;i<=npredict;i+=ntout) {
    sprintf(tmp,"%s.%lld_%lld.dat",type.c_str(),(long long)i,(long long)riter);
    fname = tmp;
    dv.alias( Gphi, offset+(nsstep*i)*data_size(), data_size() );
    F.fill(dv);
    F.tecplot(fname,"Distributed Control");
  }
}

// ===========================================================================
//                      Unsteady Gaussian Source Term
// ===========================================================================

/// This is a spatial Gaussian source that moves
class Adv_Diff::TransientGaussian : public Source {
public:
  TransientGaussian(const string tag, ifstream &in) : Source(tag),
  x0(0), y0(0), t0(0), sigma(0), amp(0), cx(0), cy(0) {
    scan_lb(in);
    if (!(in >> x0 >> y0 >> t0 >> sigma >> amp >> cx >> cy))
      error("Adv_Diff::TransientGaussian::Cannot read data.");
    sigma_inv = 1.0/sigma;
    scan_rb(in);
  }

  void apply(const Scalar time, const vField &, vField &F) {
    //cout<<"time = "<<time<<endl;
    for (LocalSize e = 0; e < F[0]->ne; e++) { // Loop over elements
      Element* E = F[0] -> el[e];
      for (Ordinal q = 0; q < E->qtot; q++)    // Loop over quadrature pts
        E->u[q] -= gaussian( (*E->C)[q], time );
    }
  }

  void adjoint_apply(const Scalar, const vField &, const vField &, vField &) {}

private:
  Scalar x0, y0, t0, sigma, amp, cx, cy;
  Scalar sigma_inv;
  Scalar gaussian(const Point &C, const Scalar t) {
    return amp*exp(-(pow(C.x-x0-cx*(t-t0),2)+
                     pow(C.y-y0-cy*(t-t0),2))*sigma_inv);
  }
};

// ===========================================================================
//                       DiracRicker Source Term
// ===========================================================================

/// Dirac source in space with a Ricker wavelet signature in time
/**
 * This class places a source term that is a Dirac delta function on a given
 * elements quadrature point with a Ricker wavelet in time.
*/
class Adv_Diff::DiracRicker : public Source {
  GlobalSize eid;  ///< element id
  LocalSize qpt;   ///< quadrature point within element
  Point p;         ///< source location;
  Scalar amp;      ///< source amplitude
  Scalar fp;       ///< Ricker peak frequency
  Scalar t0;       ///< Ricker delay time
public:
  /// Constructor
  DiracRicker(const string tag, ifstream &in) : Source(tag),
    eid(numeric_limits<Size>::max()), qpt(0), amp(1.0), fp(0), t0(0) {
    scan_lb(in);
#ifdef DGM_USE_NEW_DELTA
    if (!(in >> eid >> p >> amp >> fp ))
      error("Adv_Diff::DiracRicker::Cannot read: eid, x, y, z, amp, fp");
#else
    if (!(in >> eid >> qpt >> amp >> fp ))
      error("Adv_Diff::DiracRicker::Cannot read: eid, qpt, amp, fp");
#endif
    t0 = 1.5/fp; // this is a good value for the delay time
    scan_rb(in);
  }
  /// Source apply method
  void apply(const Scalar time, const vField &, vField &F) {
    Element *E;
    if (F.partition->owns(eid)) {
      E = F[0]->el[F.partition->inc(eid)];
    } else {
      return;  // element is not in my partition
    }
#ifdef DGM_USE_NEW_DELTA
    E->add_Dirac_delta(p, -amp*ricker(time));
#else
    E->add_Dirac_delta(qpt, -amp*ricker(time));
    // this needs to be replaced with an element method
    // assert(qpt >= 0 && qpt < E->qtot);  // make sure that qpt is valid
    // assert( F.nsd() == 1);  // this really only works for the Line element
    // E->u[qpt] -= amp/(E->psi->wa[qpt]*E->geom->J[qpt])*ricker(time);
#endif
  }
  /// Adjoint apply method
  void adjoint_apply(const Scalar, const vField &, const vField &, vField &) {}
private:
  /// Compute a Ricker wavelet in time
  Scalar ricker(const Scalar time) const {
    const Scalar T = pow(pi*fp*(time-t0),2);
    return (one-two*T)*exp(-T);
  }
};

//===========================================================================
//                       Steady Control Varients
//===========================================================================

/// Steady version of the Dirichlet boundary control
class Adv_Diff::SteadyDirichletControlBC : public DirichletControlBC {
public:
  SteadyDirichletControlBC( const string t, ifstream &in)
    : DirichletControlBC(t,in) {
  }
  bool steady() const {return true;}
};

/// Steady version of the Neumann boundary control
class Adv_Diff::SteadyNeumannControlBC : public NeumannControlBC {
public:
  SteadyNeumannControlBC( const string t, ifstream &in,
                          Scalar c_x, Scalar c_y, Scalar c_z  )
    : NeumannControlBC(t,in,c_x,c_y,c_z)  {
  }
  bool steady() const {return true;}
};

/// Steady version of the Robin boundary control
class Adv_Diff::SteadyRobinControlBC : public RobinControlBC {
public:
  SteadyRobinControlBC( const string t, ifstream &in,
                        const DGM::Comm::Ptr comm,
                        Scalar c_x, Scalar c_y, Scalar c_z )
    : RobinControlBC(t,in,comm,c_x,c_y,c_z)  {
  }
  bool steady() const {return true;}
};

/// Steady version of the Distributed source control
class Adv_Diff::SteadyDistributedControl : public DistributedControl {
public:
  SteadyDistributedControl( const string t, ifstream &in, const vField &S)
    : DistributedControl(t,in,S) {
  }
  bool steady() const {return true;}
};

} // namespace Reo

#endif // REO_ADV_DIFF_BC_HPP
