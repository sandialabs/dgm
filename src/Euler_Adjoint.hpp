#ifndef REO_EULER_ADJOINT_HPP
#define REO_EULER_ADJOINT_HPP

/** \file  Euler_Adjoint.hpp
    \brief Adjoint for the 2d Euler equations
    \author Scott Collis
*/

// DGM includes
#include "Comm.hpp"
#include "Adjoint.hpp"

// Reo includes
#include "Euler_Control.hpp"
#include "Euler_State.hpp"
#include "Euler_Objective.hpp"
#include "Obs.hpp"

namespace Reo {

/// Continuous Adjoint of the 2-d compressible Euler Equations
class Euler_Adjoint : public Domain, public Adjoint {

  dVector wk1;               ///< local workspace
  dVector wk2;               ///< local workspace

  const Euler_State *state;  ///< Pointer to my State

  vField Utmp;               ///< Temporary vField

  Scalar gamma;              ///< ratio of specific heats

 public:

  // Source term declarations
  class PressureTracking;
  class SteadyError;
#ifdef EULER_TERMINAL_TRACKING
  class TerminalTracking;
#endif

  /// Constructor
  Euler_Adjoint(DGM::ArgList &, const State*,
                const DGM::Comm::Ptr = DGM::Comm::World, const int p_inc=0 );

  // override virtual Domain methods
  void zero_all_fields();

  void set_TimeInt( Ordinal=0 );

  // provide TimeInt interface
  void prestep( vField&, const Ordinal, const Ordinal, const Scalar );
  void poststep( vField&, const Ordinal, const Ordinal, const Scalar );
  void time_derivative( vField &, vField & );

  void setup_BCdb( );

  void setup_Sourcedb( );
  Source::Ptr make_Source( ifstream &, string & );
  void add_source(const vField &, vField &);

  void enforce_bc(vField &);
  void enforce_flux_bc(vField &);

  // override Adjoint methods
  void set_end_condition();
  void set_end_condition(const dVector &, const Scalar=0.0, const Ordinal=0);
  void computeGrad(vField&, vField&, Ordinal, Ordinal);

  const Domain* domain() const {return this;}
  Domain* domain() {return this;}

  void set_t_step(){
    t = state->t;
    step = state->step;
    CFL = state->CFL;
  }

  /// supported numerical fluxes
  enum flux_type {
    Roe,                       ///< Roe flux
    vanLeer,                   ///< van Leer flux
    StegerWarming,             ///< Steger-Warming flux
    LaxFriedrichs              ///< Lax-Friedrichs flux
  };

  void set_ic(vField &, string=".ic");

 private:

  // override Euler methods
  void convection( vField &, vField & );
  void convective_flux( vField &, vField & );

  // local methods
  void conv_source(vField &, vField &); // source from inviscid flux
};

//===========================================================================
//                    Flow Tracking Observation Source
//===========================================================================

/// Pressure tracking observation source
class Euler_Adjoint::PressureTracking : public Source, public Obs {
  vField Uobj;           // should be built from an Adjoint vField
  string fobs;           // filename for Observation region
  std::vector<Ordinal> eobs; // local element list for observation region
  Scalar p_r;            // reference pressure
  Scalar gamma;          // ratio of specific heats
public:
  PressureTracking( const string tag, ifstream &in, const vField &F,
                    const Scalar gamma_ ) : Source(tag), Uobj(F.get_comm()), 
                    gamma(gamma_)
  {
    for (vField::size_type i=0; i<F.size(); i++) Uobj.push_back( new Field(F[0]) );
    ndof = 1;
    scan_lb(in);
    if ( !(in >> penalty >> p_r >> fobs) )
      error("Tracking::Cannot read penalty and tracking element list",-1);
    scan_rb(in);
    DGM::Comm::World->cout() << "PressureTracking("<<type<<") penalty = "
                             << penalty << ", p_r = " << p_r << endl;
    // get Observation element list
    ifstream obsfile(fobs.c_str());
    string buffer;
    GlobalSize nobs;
    CMC::Vector<GlobalSize,GlobalSize> global_eobs;
    if(obsfile) {
      getline(obsfile,buffer);
      if(!(obsfile>>nobs))
        error("Cannot read number of elements for Observation Region");
      getline(obsfile,buffer);
      global_eobs.resize(nobs);
      global_eobs = undefined<GlobalSize>();
      for(GlobalSize i=0; i<nobs; i++) {
        obsfile >> global_eobs[i]; // get elements in \Omega_{obs}, 1/line
        getline(obsfile,buffer);
      }
    }
    // Distribute the observation region elements
    for(Size i=0; i<global_eobs.size(); i++)
      if (Uobj[0]->partition->owns(global_eobs[i]))
        eobs.push_back(Uobj[0]->partition->inc(global_eobs[i]));
    initialize();
  }

  void set_data( const vField &Ustate, const Ordinal istep,
                 const Ordinal sstep=0 ) {
    Element *State[4], *E[4];
    assert( Ustate.qtot() == Uobj.qtot() );
    // Ustate.project(Uobj); // PROJECT_ADJOINT_TO_STATE
    Uobj.zero();
    for (size_t i=0; i<eobs.size(); i++) {
      const Ordinal e = eobs[i];
      E[0] = Uobj[0]->el[e];        // local version of the state
      E[1] = Uobj[1]->el[e];
      E[2] = Uobj[2]->el[e];
      E[3] = Uobj[3]->el[e];
      State[0] = Ustate[0]->el[e];  // local version of the state
      State[1] = Ustate[1]->el[e];
      State[2] = Ustate[2]->el[e];
      State[3] = Ustate[3]->el[e];
      const Ordinal qtot = E[0]->qtot;
      for(Ordinal q=0; q<qtot; q++) {
        const Scalar rho = State[0]->u[q];
        // const Scalar u0 = State[1]->u[q]/rho;
        // const Scalar u1 = State[2]->u[q]/rho;
        const Scalar p =
          (gamma-one) * ( State[3]->u[q] -
                          pt5*( State[1]->u[q]*State[1]->u[q] +
                                State[2]->u[q]*State[2]->u[q] ) / rho );
        E[0]->u[q] = p - p_r;
      }
    }
  }

  void apply( const Scalar, const vField &, vField &Ur ) { }

  void adjoint_apply( const Scalar, const vField &state,
                      const vField &adjoint, vField & Ur) {
    Scalar factor, rho, u[2], p;
    Element *State[4], *R[4];
    assert( state.qtot() == Ur.qtot());
    gamma = 1.4;
    p_r = 2.85714285714285714284; // @ Ma=0.5
    for (size_t i=0; i<eobs.size(); i++) {
      const Ordinal e = eobs[i];

      State[0] = state[0]->el[e];  // local version of the state
      State[1] = state[1]->el[e];
      State[2] = state[2]->el[e];
      State[3] = state[3]->el[e];

      R[0] = Ur[0]->el[e];  // local version of the state
      R[1] = Ur[1]->el[e];
      R[2] = Ur[2]->el[e];
      R[3] = Ur[3]->el[e];

      const Ordinal qtot = State[0]->qtot;

      for (Ordinal q=0; q<qtot; q++) {

        rho  = State[0]->u[q];
        u[0] = State[1]->u[q]/rho;
        u[1] = State[2]->u[q]/rho;

        p =(gamma-1.0)*(State[3]->u[q] -0.5*rho*(u[0]*u[0]+u[1]*u[1]));

        factor = -penalty*(p-p_r);

        R[0]->u[q] += (u[0]*u[0]*gamma-u[0]*u[0] +
                       u[1]*u[1]*gamma-u[1]*u[1])/2.0*factor;
        R[1]->u[q] += -(u[0]*gamma-u[0])*factor;
        R[2]->u[q] += -(u[1]*gamma-u[1])*factor;
        R[3]->u[q] += (gamma-1.0)*factor;
      }
    }
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

};

//===========================================================================
//                               Steady Error
//===========================================================================

/// Steady error estimation observation source
class Euler_Adjoint::SteadyError : public Source, public Obs {
  vField Uobj;  // built from State
  vField Uw;    // built from Adjoint
  vField Ut;    // built from State
  Ordinal npredict; // timestep to evaluate the tracking term
  Scalar x_0, y_0, sigma;
  int type;
 public:
  SteadyError( const string t, ifstream &in, const Euler_State *state,
               const vField &F, const Ordinal npredict_ )
    : Source(t), Uobj(F.get_comm()), Uw(F.get_comm()), Ut(F.get_comm()),
      npredict(npredict_) {
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
      Ut.zero();
      for (LocalSize i=0; i<1; ++i) {
        for (LocalSize e=0; e<Uobj[i]->ne; e++) {
          Element *E = Uobj[i]->el[e];
          Element *T = Ut[i]->el[e];
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
      }
      //project( Ut );
      for (vField::size_type i=0; i<Uobj.size(); ++i) {
        for (LocalSize e=0; e<Uobj[i]->ne; e++) {
          Element *E = Uobj[i]->el[e];
          Element *T = Ut[i]->el[e];
          for (LocalSize q=0; q<E->qtot; ++q) E->u[q] *= T->u[q];
        }
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

#ifdef EULER_TERMINAL_TRACKING

//===========================================================================
//               Terminal Flow Tracking Observation Source
//===========================================================================

/// Terminal tracking observation source
class Euler_Adjoint::TerminalTracking : public Source, public Obs {
  vField Uobj;  // should be built from an Adjoint vField
  int npredict;
 public:
  TerminalTracking( const string t, ifstream &in, const vField &F) :
    Source(t), Uobj(F.get_comm()) {
    for (int i=0; i<F.size(); i++) {
      Uobj.push_back( new Field(F[0]) );
    }
    ndof = 1;
    scan_lb(in);
    if (!(in >> penalty >> npredict))
      error("TerminalTracking::Cannot read penalty or npredict",-1);
    scan_rb(in);
    initialize();
  }

  void set_data( const vField &S, const Ordinal istep, const Ordinal sstep=0 ) {
    if (istep == npredict) {
      //assert( S.qtot() == Uobj.qtot() );
      S.project(Uobj);    // PROJECT_ADJOINT_TO_STATE
      Scalar w1 = 1.0, m= 1.0 , Cs = 1.3;
      for (int e=0; e<Uobj[0]->ne; e++) {
        Element *E = Uobj[0]->el[e];
        for (int q=0; q<E->qtot; ++q) {
          E->u[q] -= sin(m*pi*tan(Cs*(2.0*E->C->x[q]-1.0))/tan(Cs));
        }
      }
      //axpy(-1.0,Uobj,S,Uobj);
    } else {
      Uobj.zero();
    }
  }

  void apply( const Scalar, const vField &, vField &Ur ) {}

  void adjoint_apply( const Scalar, const vField &,
                      const vField &, vField &Ur ) {
    // PROJECT_STATE_TO_ADJOINT
    add( Uobj, Ur );
  }

  inline Obs* obs() { return this; }
  inline const Obs* obs() const { return this; }

  // Obs virtual methods
  void initialize() {
    Uobj.zero();
    Scalar w1 = 1.0, m= 1.0 , Cs = 1.3;
    for (int e=0; e<Uobj[0]->ne; e++) {
      Element *E = Uobj[0]->el[e];
      for (int q=0; q<E->qtot; ++q) {
        E->u[q] = sin(m*pi*tan(Cs*(2.0*E->C->x[q]-1.0))/tan(Cs));
      }
    }
  }

  void end_condition( vField &F ) {
    // DGM::Comm::World->cout() << "Applying end condition:  " << type << endl;
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
#endif  //  EULER_TERMINAL_TRACKING

} // namespace Reo

#endif  //  REO_EULER_ADJOINT_HPP
