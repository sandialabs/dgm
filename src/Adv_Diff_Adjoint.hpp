#ifndef REO_ADV_DIFF_ADJOINT_HPP
#define REO_ADV_DIFF_ADJOINT_HPP

/** \file Adv_Diff_Adjoint.hpp
    \brief Advection diffusion Adjoint declaration
    \author Scott Collis
*/

// local includes
#include "Comm.hpp"
#include "TimeInt.hpp"
#include "Adjoint.hpp"
#include "Obs.hpp"

// Reo includes
#include "Adv_Diff_State.hpp"
#include "Adv_Diff_Control.hpp"
#include "Adv_Diff_Objective.hpp"

namespace Reo {

/// Adjoint of the Advection Diffusion Equations
class Adv_Diff_Adjoint : public Domain, public Adjoint {

  dVector wk1;           ///< local workspace
  dVector wk2;           ///< local workspace
  dVector wk3;           ///< local workspace

  const Adv_Diff_State *state;   ///< pointer to my State

  vField Uobj;           ///< objective function field

  /// compute absolute value
  static Scalar dfabs( Scalar );

public:

  // Source term declarations
  class Tracking;
  class TerminalTracking;
  class SteadyTracking;
  class SteadyError;
  class UnsteadyError;
  class UnsteadyTracking;
  class AdjFuncSource;

  // data
  Scalar mu;             ///< Viscosity
  Scalar cx;             ///< Wave speed in x
  Scalar cy;             ///< Wave speed in y
  Scalar cz;             ///< Wave speed in z
  int fv;                ///< Non-zero means use finite volume reconstruction
  bool cfield;           ///< Determins if constant coefficient

  vField Uv;             ///< Viscous field
  vField Uc;             ///< Convective field

  /// Constructor
  Adv_Diff_Adjoint( DGM::ArgList &, const State*,
                    const DGM::Comm::Ptr = DGM::Comm::World,
                    const int pinc=0 );

    /// Destructor
  virtual ~Adv_Diff_Adjoint() {
    if(verbosity()) comm->cout() << "~Reo::Adv_Diff_Adjoint()" << endl;
  }

  // local methods
  void parse_args( DGM::ArgList &args );
  void showUsage();

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

  // override Adjoint methods
  void set_end_condition();
  void set_end_condition(const dVector &, const Scalar=0.0, const Ordinal=0);
  void computeGrad(vField&, vField&, Ordinal, Ordinal);

  const Domain* domain() const {return this;}
  Domain* domain() {return this;}

  void set_t_step() {
    t = state->t;
    step = state->step;
    CFL = state->CFL;
  }

private:

  void convection( vField &, vField & );
  void constant_convection( vField &, vField & );
  void diffusion( vField &, vField &, vField & );
  void linear_reconstruction( vField &, vField &, vField & );
  void convective_flux( vField &, vField & );
  void convective_flux( const vField &, vField &, vField &);
  void interior_penalty_flux(const vField &Up, const vField &Us, vField &Uf,
                             const Scalar epsilon);
  void enforce_boundary_penalty(const vField &S, vField &F,
                                const Scalar epsilon);
};

//===========================================================================
//                       Adjoint Function Source
//===========================================================================

/// Defines an adjoint source term for testing purposes
class Adv_Diff_Adjoint::AdjFuncSource : public FuncSource {
public:
  AdjFuncSource( const string t, ifstream &in, int ndof=0)
    : FuncSource(t,in,ndof) {}
  void adjoint_apply(const Scalar t, const vField &Us,
                     const vField &Ua, vField &Ur) {
    //cout<<"AdjFuncSource"<<endl;
    FuncSource::apply(t, Us, Ur);
  }
};

//===========================================================================
//                    Flow Tracking Observation Source
//===========================================================================

/// Flow tracking observation source
class Adv_Diff_Adjoint::Tracking: public Source, public Obs {
  vField Uobj;  // should be built from an Adjoint vField
  Scalar amp;
public:
  Tracking( const string t, ifstream &in, const vField &F) :
    Source(t), Uobj(F.get_comm(),"Uobj") {
    for (vField::size_type i=0; i<F.size(); i++) {
      Uobj.push_back( new Field(F[0]) );
    }
    ndof = 1;
    scan_lb(in);
    if (!(in >> penalty >> amp ))
      error("Tracking::Cannot read penalty and amp");
    scan_rb(in);
    initialize();
  }

  void set_data( const vField &S, const Ordinal istep,
                 const Ordinal sstep=0 ) {
    //assert( S.qtot() == Uobj.qtot() );
    S.project(Uobj); // PROJECT_ADJOINT_TO_STATE
    //Scalar w1 = 1.0;
    Scalar m = 1.0 , Cs = 1.3;
    for (LocalSize e=0; e<Uobj[0]->ne; e++) {
      Element *E = Uobj[0]->el[e];
      for (LocalSize q=0; q<E->qtot; ++q) {
        E->u[q] -= amp*sin(m*pi*tan(Cs*(2.0*E->C->x[q]-1.0))/tan(Cs));
      }
    }
    //axpy(-1.0,Uobj,S,Uobj);
  }

  void apply( const Scalar, const vField &, vField &Ur ) {}

  void adjoint_apply( const Scalar, const vField &,
                      const vField&, vField &Ur ) {
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
    Scalar m = 1.0 , Cs = 1.3;
    for (LocalSize e=0; e<Uobj[0]->ne; e++) {
      Element *E = Uobj[0]->el[e];
      for (LocalSize q=0; q<E->qtot; ++q) {
        E->u[q] = amp*sin(m*pi*tan(Cs*(2.0*E->C->x[q]-1.0))/tan(Cs));
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

/// Terminal tracking observation source
class Adv_Diff_Adjoint::TerminalTracking : public Source, public Obs {
  vField Uobj;       ///< should be built from an Adjoint vField
  Ordinal npredict;  ///< timestep to evaluate the tracking term
  Scalar amp;        ///< gives some modest control over the target function
public:
  TerminalTracking( const string t, ifstream &in, const vField &F,
                    const Ordinal npredict_ )
    : Source(t), Uobj(F.get_comm(),"Obs::Uobj"), npredict(npredict_) {
    for (vField::size_type i=0; i<F.size(); i++)
      Uobj.push_back( new Field(F[0]) );
    ndof = 1;
    scan_lb(in);
    if ( !(in >> penalty >> amp ) )
      error("TerminalTracking::Cannot read penalty, amp");
    scan_rb(in);
    initialize();
  }

  void set_data( const vField &S, const Ordinal istep,
                 const Ordinal sstep=0 ) {
    if (istep == npredict) {
      S.project(Uobj);
      if (amp != 0.0) {
        const Scalar m= 1.0, Cs = 1.3;
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

  void adjoint_apply( const Scalar, const vField &,
                      const vField &, vField &Ur ) {
    // this should not be set for a terminal observation
  }

  inline Obs* obs() { return this; }
  inline const Obs* obs() const { return this; }

  // Obs virtual methods
  void initialize() {
    Uobj.zero();
  }

  void end_condition( vField &F ) {
    //DGM::Comm::World->cout() << "Applying end condition: " << type << endl;
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
//                   Steady Tracking Observation Source
//===========================================================================

/// Steady tracking observtion source
class Adv_Diff_Adjoint::SteadyTracking : public Source, public Obs {
  vField Uobj;      ///< should be built from an Adjoint vField
  Ordinal npredict; ///< timestep to evaluate the tracking term
  Scalar amp;
public:
  SteadyTracking( const string t, ifstream &in, const vField &F,
                  const Ordinal npredict_ ) : Source(t), 
                  Uobj(F.get_comm(),"Uobj"), npredict(npredict_) {
    for (vField::size_type i=0; i<F.size(); i++) {
      Uobj.push_back( new Field(F[0]) );
    }
    ndof = 1;
    scan_lb(in);
    if ( !(in >> penalty >> amp ) )
      error("SteadyTracking::Cannot read penalty, amp");
    scan_rb(in);
    initialize();
  }

  void set_data( const vField &S, const Ordinal istep,
                 const Ordinal sstep=0 ) {
    if (istep==npredict) {
      S.project(Uobj);
      if (amp != 0.0) {
        const Scalar m = 1.0, Cs = 1.3;
        for (LocalSize e=0; e<Uobj[0]->ne; e++) {
          Element *E = Uobj[0]->el[e];
          for (LocalSize q=0; q<E->qtot; ++q) {
            E->u[q] -= amp*sin(m*pi*tan(Cs*(2.0*E->C->x[q]-1.0))/tan(Cs));
          }
        }
      }
    }
  }

  void apply( const Scalar, const vField &, vField &Ur ) {}

  void adjoint_apply( const Scalar, const vField &,
                      const vField &, vField &Ur ) {
    // should PROJECT_STATE_TO_ADJOINT
    axpy( penalty, Uobj, Ur );
  }

  inline Obs* obs() { return this; }
  inline const Obs* obs() const { return this; }

  // Obs virtual methods
  void initialize() {
    Uobj.zero();
  }

  void end_condition( vField &F ) { }

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
//                           Steady Error
//===========================================================================

/// Steady error estimation observation source
class Adv_Diff_Adjoint::SteadyError : public Source, public Obs {
  vField Uobj;  ///< built from State
  vField Uw;    ///< built from Adjoint
  vField Ut;    ///< built from State
  Ordinal npredict; ///< timestep to evaluate the tracking term
  Scalar x_0, y_0, sigma;
  int type;
public:
  SteadyError( const string t, ifstream &in, const Adv_Diff_State *state,
               const vField &F, const Ordinal npredict_ )
    : Source(t), Uobj(F.get_comm(),"Uobj"), Uw(F.get_comm(),"Uw"), 
      Ut(F.get_comm(),"Ut"), npredict(npredict_) 
  {
    for (vField::size_type i=0; i<F.size(); i++) {
      //Uobj.push_back( new Field(F[0]) );
      //Uw.push_back( new Field(F[0]) );
      Uobj.push_back( new Field(state->domain()->U[0]) );
      Ut.push_back( new Field(state->domain()->U[0]) );
      Uw.push_back( new Field(F[0]) );
    }
    ndof = 1;
    scan_lb(in);
    if ( !(in >> penalty >> x_0 >> y_0 >> sigma >> type ) )
      error("SteadyError::Cannot read penalty");
    scan_rb(in);
    initialize();
  }

  void set_data( const vField &S, const Ordinal istep,
                 const Ordinal sstep=0 ) {
    if (istep==npredict) {
      S.project(Uobj);
      for (LocalSize e=0; e<Uobj[0]->ne; e++) {
        Element *E = Uobj[0]->el[e];
        Element *T = Ut[0]->el[e];
        if (type==0)
          for (LocalSize q=0; q<E->qtot; ++q) {
            T->u[q] = 1.0;
          }
        else if (type==1)
          for (LocalSize q=0; q<E->qtot; ++q) {
            T->u[q] = exp( -( pow(T->C->x[q]-x_0,2) +
                              pow(T->C->y[q]-y_0,2) ) / pow(sigma,2) );
          }
        else if (type==2)
          for (LocalSize q=0; q<E->qtot; ++q) {
            T->u[q] = E->u[q];
            E->u[q] *= 0.5;
          }
      }
      //project( Ut );
      for (LocalSize e=0; e<Uobj[0]->ne; e++) {
        Element *E = Uobj[0]->el[e];
        Element *T = Ut[0]->el[e];
        for (LocalSize q=0; q<E->qtot; ++q) E->u[q] *= T->u[q];
      }
      //project( Uobj );
    }
  }

  void apply( const Scalar, const vField &, vField &Ur ) {}

  void adjoint_apply( const Scalar, const vField &,
                      const vField &, vField &Ur ) {
    Ut.project(Uw);
    axpy( -1.0, Uw, Ur );
  }

  inline Obs* obs() { return this; }
  inline const Obs* obs() const { return this; }

  // Obs virtual methods
  void initialize() {
    Uobj.zero();
  }

  void end_condition( vField &F ) { }

  Scalar norm() const {
    return vField::local_L2_norm( Uobj );
  }

  Scalar cost() const {
    return 0.0;
  }

  Scalar terminal_cost() const {
    Scalar result(0), area(0);
    for (LocalSize e=0; e<Uobj[0]->ne; ++e) {
      Element *E = Uobj[0]->el[e];
      result += E->integrate(&area);
    }
    return result;
  }
};

//===========================================================================
//                           Unsteady Error
//===========================================================================

/// Unsteady error estimation observation source
class Adv_Diff_Adjoint::UnsteadyError : public Source, public Obs {
  vField Uobj;  ///< should be built from an Adjoint vField
  vField Uw, Ut;
  Ordinal npredict; ///< timestep to evaluate the tracking term
  Scalar x_0, y_0, sigma;
  int type;
public:
  UnsteadyError( const string t, ifstream &in, const Adv_Diff_State *state,
                 const vField &F, const Ordinal npredict_ )
    : Source(t), Uobj(F.get_comm(),"Uobj"), Uw(F.get_comm(),"Uw"), 
      Ut(F.get_comm(),"Ut"), npredict(npredict_) 
  {
    for (vField::size_type i=0; i<F.size(); i++) {
      Uobj.push_back( new Field(state->domain()->U[0]) );
      Ut.push_back( new Field(state->domain()->U[0]) );
      Uw.push_back( new Field(F[0]) );
    }
    ndof = 1;
    scan_lb(in);
    if ( !(in >> penalty >> x_0 >> y_0 >> sigma >> type ) )
      error("UnsteadyError::Cannot read penalty");
    scan_rb(in);
    initialize();
  }

  void set_data( const vField &S, const Ordinal istep,
                 const Ordinal sstep=0 ) {
    if (istep==npredict) {
      S.project(Uobj);
      for (LocalSize e=0; e<Uobj[0]->ne; e++) {
        Element *E = Uobj[0]->el[e];
        Element *F = Ut[0]->el[e];
        if (type==0)
          for (LocalSize q=0; q<E->qtot; ++q) {
            F->u[q] = 1.0;
            E->u[q] *= F->u[q];
          }
        else if (type==1)
          for (LocalSize q=0; q<E->qtot; ++q) {
            F->u[q] = exp( -( pow(F->C->x[q]-x_0,2) +
                              pow(F->C->y[q]-y_0,2) ) / pow(sigma,2) );
            E->u[q] *= F->u[q];
          }
        else if (type==2)
          for (LocalSize q=0; q<E->qtot; ++q) {
            F->u[q] = E->u[q];
            E->u[q] *= 0.5*F->u[q];
          }
        else if (type==3)
          for (LocalSize q=0; q<E->qtot; ++q) {
            F->u[q] = 1.0 - cos(1.0 * pi * F->C->x[q]);
            E->u[q] *= 0.5*F->u[q];
          }
      }
    }
  }

  void apply( const Scalar, const vField &, vField &Ur ) {}

  void adjoint_apply( const Scalar, const vField &,
                      const vField &, vField &Ur ) {}

  inline Obs* obs() { return this; }
  inline const Obs* obs() const { return this; }

  // Obs virtual methods
  void initialize() {
    Uobj.zero();
  }

  void end_condition( vField &Ur ) {
    //DGM::Comm::World->cout() << "Applying end condition: " << type << endl;
    Ut.project(Uw);
    axpy( -1.0, Uw, Ur );
  }

  Scalar norm() const {
    return vField::local_L2_norm( Uobj );
  }

  Scalar cost() const {
    return 0.0;
  }

  Scalar terminal_cost() const {
    Scalar result(0), area(0);
    for (LocalSize e=0; e<Uobj[0]->ne; ++e) {
      Element *E = Uobj[0]->el[e];
      result += E->integrate(&area);
    }
    return result;
  }
};

//===========================================================================
//           Flow Tracking Observation Source (variable target)
//===========================================================================

/// Unsteady flow tracking observation source with variable target
class Adv_Diff_Adjoint::UnsteadyTracking : public Source, public Obs {
  vField Uobj;  ///< should be built from an Adjoint vField
  vField Utmp;  ///< should be built from an Adjoint vField
  const Adv_Diff_State *state;
  // state is used to get both the root filename and access to the
  // read_field() and time_int->interpolate() methods.
public:
  UnsteadyTracking( const string t, ifstream &in, const vField &F,
                    const Adv_Diff_State *s) 
  : Source(t), Uobj(F.get_comm(),"Uobj"), 
    Utmp(F.get_comm(),"Utmp"), state(s) 
  {
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

  void set_data( const vField &S, const Ordinal istep,
                 const Ordinal sstep=0 ) {
    assert( S.qtot() == Uobj.qtot() );
    // should PROJECT_ADJOINT_TO_STATE
    char tmp[80];
    string objfile;
    sprintf(tmp,".%lld.rst",(long long)istep);
    objfile = "obj/" + state->root + tmp;
    state->read_field(objfile, Uobj);
    if (sstep!=0) {
      sprintf(tmp,".%lld.rst",(long long)(istep+1));
      objfile = "obj/" + state->root + tmp;
      state->read_field(objfile, Utmp);
      state->time_int->interpolate( sstep, Utmp, Uobj );
    }
    axpy(-1.0,Uobj,S,Uobj);
  }

  void apply( const Scalar, const vField &, vField &Ur ) {}

  void adjoint_apply( const Scalar, const vField &,
                      const vField &, vField &Ur ) {
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

#endif  // REO_ADV_DIFF_ADJOINT_HPP
