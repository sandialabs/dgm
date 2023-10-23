#ifndef REO_LINBURGERS_ADJOINT_HPP
#define REO_LINBURGERS_ADJOINT_HPP

/** \file  LinBurgers_Adjoint.hpp
    \brief Adjoint declaration for the linearized Burgers equation. */

// DGM includes
#include "Comm.hpp"
#include "TimeInt.hpp"
#include "Adjoint.hpp"
#include "Obs.hpp"

// local includes
#include "LinBurgers_State.hpp"
#include "Burgers_State.hpp"
#include "Burgers_Adjoint.hpp"
#include "Burgers_Control.hpp"
#include "Burgers_Objective.hpp"

namespace Reo {

/// Adjoint of the linearized Burgers equation
class LinBurgers_Adjoint : public Domain, public Adjoint {

  dVector wk1;               ///< local workspace
  dVector wk2;               ///< local workspace
  dVector wk3;               ///< local workspace

  const LinBurgers_State *state;       ///< state for which this is adjoint
  const Burgers_State *base_state;     ///< base state for linearized state
  const Burgers_Adjoint *base_adjoint; ///< base adjoint for linearized Adjoint

  /// compute the absolute value
  static Scalar dfabs(Scalar);

 public:

  // Source term declarations
  class Tracking;
  class TerminalTracking;
  class UnsteadyTracking;

  // data
  Scalar mu;             ///< viscosity
  vField Ubase;          ///< base state flow field
  vField Uadj;           ///< base adjoint flow field
  vField Uv;             ///< viscous field

  /// Constructor
  LinBurgers_Adjoint( DGM::ArgList &, const State*,
                      const State*, const Adjoint*,
                      const DGM::Comm::Ptr = DGM::Comm::World );

  // override virtual Domain methods
  void zero_all_fields();
  void set_ic(vField &, string=".ic");

  void set_TimeInt( Ordinal=0 );

  // provide TimeInt interface
  void prestep( vField&, const Ordinal, const Ordinal, const Scalar );
  void poststep( vField&, const Ordinal, const Ordinal, const Scalar );
  void time_derivative( vField &, vField & );

  void setup_BCdb( );
  void enforce_bc(vField &);
  void enforce_flux_bc(vField &);

  void setup_Sourcedb( );
  Source::Ptr make_Source( ifstream &, string & );
  void add_source(const vField &, vField &);

  void computeGrad(vField&, vField&, Ordinal, Ordinal);

  const Domain* domain() const {return this;}
  Domain* domain() {return this;}

  void set_t_step(){
    t = state->t;
    step = state->step;
    CFL = state->CFL;
  }

  void set_end_condition();
  void set_end_condition(const dVector &, const Scalar, const Ordinal);

 private:

  /// Evaluate the convection term
  void convection( vField &, vField & );
  /// Evaluate the diffusion term
  void diffusion( vField &, vField &, vField & );
  /// Compute the upwind-flux contribution
  void convective_flux( const vField &, const vField &,
                    vField &, vField &, const bool=true );
};

//===========================================================================
//                    Flow Tracking Observation Source
//===========================================================================

/// Flow tracking observation source
class LinBurgers_Adjoint::Tracking: public Source, public Obs {
  vField Uobj;  // should be built from an Adjoint vField
 public:
  Tracking( const string t, ifstream &in, const vField &F) :
    Source(t), Uobj(F.get_comm()) {
    for (vField::size_type i=0; i<F.size(); i++) {
      Uobj.push_back( new Field(F[0]) );
    }
    ndof = 1;
    scan_lb(in);
    if (!(in >> penalty))
      error("Tracking::Cannot read penalty",-1);
    scan_rb(in);
    initialize();
  }

  void set_data( const vField &S, const Ordinal istep, const Ordinal sstep=0 ) {
    //assert( S.qtot() == Uobj.qtot() );
    S.project(Uobj); // PROJECT_ADJOINT_TO_STATE
    //Scalar w1 = 1.0;
    Scalar m= 1.0 , Cs = 1.3;
    for (LocalSize e=0; e<Uobj[0]->ne; e++) {
      Element *E = Uobj[0]->el[e];
      for (LocalSize q=0; q<E->qtot; ++q) {
        E->u[q] -= sin(m*pi*tan(Cs*(2.0*E->C->x[q]-1.0))/tan(Cs));
      }
    }
    //axpy(-1.0,Uobj,S,Uobj);
  }

  void apply( const Scalar, const vField &, vField &Ur ) {}

  void adjoint_apply( const Scalar, const vField &, const vField&,
                      vField &Ur ) {
    // should PROJECT_STATE_TO_ADJOINT
    // project_add( Uobj, Ur );
    axpy( penalty, Uobj, Ur );
  }

  inline Obs* obs() { return this; }
  inline const Obs* obs() const { return this; }

  // Obs virtual methods
  void initialize() {
    Uobj.zero();
    //Scalar w1 = 1.0;
    Scalar m= 1.0 , Cs = 1.3;
    for (LocalSize e=0; e<Uobj[0]->ne; e++) {
      Element *E = Uobj[0]->el[e];
      for (LocalSize q=0; q<E->qtot; ++q) {
        E->u[q] = sin(m*pi*tan(Cs*(2.0*E->C->x[q]-1.0))/tan(Cs));
      }
    }
  }

  void end_condition( vField &F ) {}

  Scalar norm() const {
    return vField::local_L2_norm( Uobj );
  }

};

//===========================================================================
//               Terminal Flow Tracking Observation Source
//===========================================================================

/// Terminal Tracking observation source
class LinBurgers_Adjoint::TerminalTracking : public Source, public Obs {
  vField Uobj;      ///< should be built from an Adjoint vField
  Ordinal npredict; ///< timestep to evaluate the tracking term
  Scalar amp;       ///< gives some modest control over the target function
 public:
  TerminalTracking( const string t, ifstream &in, const vField &F,
                    const Ordinal npredict_ ) : Source(t), Uobj(F.get_comm()), 
                    npredict(npredict_) {
    for (vField::size_type i=0; i<F.size(); i++)
      Uobj.push_back( new Field(F[0]) );
    ndof = 1;
    scan_lb(in);
    if ( !(in >> penalty >> amp) )
      error("TerminalTracking::Cannot read penalty, amp");
    scan_rb(in);
    initialize();
  }

  void set_data( const vField &S, const Ordinal istep, const Ordinal sstep=0 ) {
    if (istep == npredict) {
      S.project(Uobj);    // PROJECT_ADJOINT_TO_STATE
      if (amp != 0.0) {
        // Scalar w1 = 1.0;
        Scalar m= 1.0 , Cs = 1.3;
        for (LocalSize e=0; e<Uobj[0]->ne; e++) {
          Element *E = Uobj[0]->el[e];
          for (LocalSize q=0; q<E->qtot; ++q)
            E->u[q] -= amp*sin(m*pi*tan(Cs*(2.0*E->C->x[q]-1.0))/tan(Cs));
        }
      }
    } else {
      Uobj.zero();
    }
  }

  void apply( const Scalar, const vField &, vField &Ur ) {}

  void adjoint_apply( const Scalar, const vField &, const vField &,
                      vField &Ur ) {
    // this should not be set for a terminal observation
  }

  inline Obs* obs() { return this; }
  inline const Obs* obs() const { return this; }

  // Obs virtual methods
  void initialize() {
    Uobj.zero();
  }

  void end_condition( vField &F ) {
    DGM::Comm::World->cout() << "Applying end condition: " << type << endl;
    // should PROJECT_STATE_TO_ADJOINT
    axpy( penalty, Uobj, F );
  }

  Scalar norm() const {
    return vField::local_L2_norm( Uobj );
  }

  Scalar cost() const {
    return 0.0;
  }

  Scalar terminal_cost() const {
    return pt5*penalty*norm();
  }
};

//===========================================================================
//          Flow Tracking Observation Source (variable target)
//===========================================================================

/// Unsteady tracking observation source
class LinBurgers_Adjoint::UnsteadyTracking : public Source, public Obs {
  vField Uobj;  // should be built from an Adjoint vField
  vField Utmp;  // should be built from an Adjoint vField
  const LinBurgers_State *state;
 public:
  UnsteadyTracking( const string t, ifstream &in, const vField &F,
                    const LinBurgers_State *s) : Source(t), Uobj(F.get_comm()),
                    Utmp(F.get_comm()), state(s) {
    for (vField::size_type i=0; i<F.size(); i++) {
      Uobj.push_back( new Field(F[0]) );
      Utmp.push_back( new Field(F[0]) );
    }
    ndof = 1;
    scan_lb(in);
    if (!(in >> penalty))
      error("Tracking::Cannot read penalty",-1);
    scan_rb(in);
    initialize();
  }

  void set_data( const vField &S, const Ordinal istep, const Ordinal sstep=0 ) {
    assert( S.qtot() == Uobj.qtot() );
    // should PROJECT_ADJOINT_TO_STATE
    char tmp[80];
    string objfile;
    sprintf(tmp,".%lld.rst",(long long)istep);
    objfile = state->root + ".obj" + tmp;
    state->read_field(objfile, Uobj);
    if (sstep!=0) {
      sprintf(tmp,".%lld.rst",(long long)(istep+1));
      objfile = state->root + ".obj" + tmp;
      state->read_field(objfile, Utmp);
      state->time_int->interpolate( sstep, Utmp, Uobj );
    }
    axpy(-1.0,Uobj,S,Uobj);
  }

  void apply( const Scalar, const vField &, vField &Ur ) {}

  void adjoint_apply( const Scalar, const vField &, const vField&,
                      vField &Ur ) {
    // should PROJECT_STATE_TO_ADJOINT
    // project_add( Uobj, Ur );
    axpy( penalty, Uobj, Ur );
  }

  inline Obs* obs() { return this; }
  inline const Obs* obs() const { return this; }

  // Obs virtual methods
  void initialize() {
    Uobj.zero();
  }

  void end_condition( vField &F ) {}

  Scalar norm() const {
    return vField::local_L2_norm( Uobj );
  }

};

} // namespace Reo

#endif  // REO_LINBURGERS_ADJOINT_HPP
