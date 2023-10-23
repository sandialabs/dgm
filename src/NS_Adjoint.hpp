#ifndef REO_NS_ADJOINT_HPP
#define REO_NS_ADJOINT_HPP

/** \file  NS_Adjoint.hpp
    \brief Adjoint Navier-Stokes equations declaration. */

// DGM includes
#include "Comm.hpp"
#include "Adjoint.hpp"
#include "Obs.hpp"

// local includes
#include "NS_Control.hpp"
#include "NS_State.hpp"
#include "NS_Objective.hpp"

namespace Reo {

// forward declarations
class Fluid;

/// Adjoint of the 2d compressible Navier--Stokes equations
class NS_Adjoint : public Domain, public Adjoint {

  dVector wk3;           ///< local workspace
  dVector wk4;           ///< local workspace

  const NS_State *state;

  vField Ustate_x;       ///< State_x
  vField Ustate_y;       ///< State_y

  /// \name Physical parameters
  //@{
  Scalar vis;    ///< Viscosity
  Scalar Ma;     ///< Mach number
  Scalar Re;     ///< Reynolds number
  Scalar mu;     ///< viscosity
  Scalar lambda; ///< viscosity
  Scalar K;      ///< conductivity
  Scalar Pr;     ///< Prandtl number
  Scalar gamma;  ///< ratio of specific heats
  //@}

public:

  // Source term declarations
  class FlowTracking;
  class TerminalKineticEnergy;
  class ShearStressReduction;

  vField Uv;             ///< viscous field
  Fluid *fluid;          ///< Fluid properties

  /// Constructor
  NS_Adjoint(DGM::ArgList &,const State*,
             const DGM::Comm::Ptr = DGM::Comm::World );

  // override virtual Domain methods
  void zero_all_fields();

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
    Roe,                 ///< Roe flux
    vanLeer,             ///< van Leer flux
    StegerWarming,       ///< Steger-Warming flux
    LaxFriedrichs        ///< Lax-Friedrics flux
  };

  void set_ic( vField &, string=".ic" );

private:

  void gradient( Element *, Element *, dVector &, dVector &, dVector & );

  /// Get the current viscosity
  void get_viscosity( dVector & );

  /// Compute the convection term
  void convection( vField &, vField & );

  /// Compute the upwind flux term
  void convective_flux( vField &, vField & );

  /// Compute the diffusion term
  void diffusion( vField &, vField &, vField & );

  /// Source from the inviscid flux
  void conv_source(vField &, vField &);

  /// Viscous convection term
  /** We transform the viscous Jacobian with the state to the flux
      formulation, so have to introduce the source term. */
  void viscous_convection(vField &,vField &,vField &);

  /// Actually central flux
  void viscous_convective_flux( vField &, vField & );

  /// Source term from viscous flux
  void viscous_conv_source( vField &, vField &, vField &);

  /// Enforce the State state derivate boundary,
  void enforce_state_derivate_bc(vField &);
};

//===========================================================================
//                    Distributed Observations
//===========================================================================

/// General full-domain flow-field tracking
class NS_Adjoint::FlowTracking : public Source, public Obs {
public:
  enum ObsType { Full, Momentum, Velocity, Energy, Pressure };
private:
  vField Uobj, Usrc;     // should be built from an Adjoint vField
  string target;         // filename for the target flow field
  Scalar gamma;          // ratio of specific heats
  const NS_State *state; // the State
  ObsType obstype;       // type of observation term
public:
  FlowTracking( const string tag, ifstream &in, const vField &F,
                const NS_State *s, const ObsType obstype_=Full )
    : Source(tag), Uobj(F.get_comm()), Usrc(F.get_comm()), 
      state(s), obstype(obstype_) {
    gamma = state->gamma;
    for (vField::size_type i=0; i<F.size(); i++) {
      Uobj.push_back( new Field(F[0]) );
      Usrc.push_back( new Field(F[0]) );
    }
    ndof = 1;
    scan_lb(in);
    if ( !(in >> penalty >> target) )
      error("FlowTracking::Cannot read penalty and tracking element list",-1);
    scan_rb(in);
    initialize();
  }

  // full flow-field observation term
  void set_data( const vField &Ustate, const Ordinal istep,
                 const Ordinal sstep=0 ) {
    Ordinal qtot;
    Scalar rho, rho_obj, ru, ru_obj, rv, rv_obj, E, E_obj;
    Element *State[4], *Sobj[4], *Ssrc[4];

    assert( Ustate.qtot() == Uobj.qtot() );
    // Ustate.project(Uobj); // PROJECT_ADJOINT_TO_STATE

    for (LocalSize e=0; e<Uobj[0]->ne; e++) {
      Sobj[0] = Uobj[0]->el[e];     // local version of the Objective state
      Sobj[1] = Uobj[1]->el[e];
      Sobj[2] = Uobj[2]->el[e];
      Sobj[3] = Uobj[3]->el[e];

      Ssrc[0] = Usrc[0]->el[e];     // local version of the source
      Ssrc[1] = Usrc[1]->el[e];
      Ssrc[2] = Usrc[2]->el[e];
      Ssrc[3] = Usrc[3]->el[e];

      State[0] = Ustate[0]->el[e];  // local version of the state
      State[1] = Ustate[1]->el[e];
      State[2] = Ustate[2]->el[e];
      State[3] = Ustate[3]->el[e];

      qtot = Sobj[0]->qtot;

      switch (obstype) {
      case Full:
        for(LocalSize q=0;q<qtot;q++) {
          rho = State[0]->u[q];
          ru  = State[1]->u[q];
          rv  = State[2]->u[q];
          E   = State[3]->u[q];
          rho_obj = Sobj[0]->u[q];
          ru_obj  = Sobj[1]->u[q];
          rv_obj  = Sobj[2]->u[q];
          E_obj   = Sobj[3]->u[q];
          Ssrc[0]->u[q]  = rho_obj - rho;
          Ssrc[1]->u[q]  = ru_obj  - ru;
          Ssrc[2]->u[q]  = rv_obj  - rv;
          Ssrc[3]->u[q]  = E_obj   - E;
        }
        break;
      case Momentum:
        for(LocalSize q=0;q<qtot;q++) {
          ru     = State[1]->u[q];
          rv     = State[2]->u[q];
          ru_obj = Sobj[1]->u[q];
          rv_obj = Sobj[2]->u[q];
          Ssrc[0]->u[q]  = 0;
          Ssrc[1]->u[q]  = ru_obj - ru;
          Ssrc[2]->u[q]  = rv_obj - rv;
          Ssrc[3]->u[q]  = 0;
        }
        break;
      case Pressure:
        error("NS_Adjoint::FlowTracking::set_data() ObsTyp Pressure.");
        break;
      default:
        error("NS_Adjoint::FlowTracking::set_data() Undefined ObsType.");
      }
    }
  }

  void apply( const Scalar, const vField &, vField &Ur ) { }

  void adjoint_apply( const Scalar, const vField &state,
                      const vField &adjoint, vField & Ur) {
    // should PROJECT_STATE_TO_ADJOINT
    // project_add( Uobj, Ur );
    axpy( penalty, Usrc, Ur );
  }

  inline Obs* obs() { return this; }
  inline const Obs* obs() const { return this; }

  // Obs virtual methods
  void initialize() {
    state->read_field(target, Uobj);  // load target flow field
  }

  void end_condition( vField &F ) {}

  Scalar norm() const {
    return vField::local_L2_norm( Usrc );
  }
};

/// Shear Stress reduction
class NS_Adjoint::ShearStressReduction : public Source, public Obs {
public:

private:
  string fobs;           // filename for Observation region
  Scalar gamma;          // ratio of specific heats
  const NS_State *state; // the State
  // local element and side list for observation region
  std::vector<Ordinal> eobs, sobs;
  Scalar obj_norm;
public:
  ShearStressReduction( const string tag, ifstream &in, const vField &F,
                        const NS_State *s)
    : Source(tag), state(s){
    gamma = state->gamma;

    obj_norm =0;
    ndof = 1;
    scan_lb(in);
    if ( !(in >> penalty >> fobs) )
      error("FlowTracking::Cannot read penalty and tracking element list",-1);
    scan_rb(in);

    // get Observation element and side list
    ifstream obsfile(fobs.c_str());
    string buffer;
    Ordinal nobs;
    iVector global_eobs, global_sobs;
    if(obsfile) {
      getline(obsfile,buffer);
      if(!(obsfile>>nobs))
        error("Cannot read # of elements and sides for Observation Region");
      getline(obsfile,buffer);
      global_eobs.resize(nobs);
      global_sobs.resize(nobs);
      for(Ordinal i=0;i<nobs;i++) {
        obsfile>>global_eobs[i]>>global_sobs[i];//get elements in \Omega_{obs}
        getline(obsfile,buffer);
      }
    }
    // Distribute the observation region elements
    for(Ordinal i=0; i<global_eobs.size(); i++)
      if (F[0]->partition->owns(global_eobs[i])){
        eobs.push_back(F[0]->partition->inc(global_eobs[i]));
        sobs.push_back(global_sobs[i]);
      }
    initialize();
  }

  // full flow-field observation term
  void set_data( const vField &Ustate, const Ordinal istep,
                 const Ordinal sstep=0 ) {
    Scalar mu = state->mu;
    dVector u_x,u_y,v_x,v_y, tau_w2;
    obj_norm =0;
    for (size_t n=0; n<eobs.size(); ++n){   // loop over field boundaries
      const Ordinal eid = eobs[n];
      const Ordinal sid = sobs[n];
      dVector &nx = Ustate[0]->el[eid]->side[sid]->nx();
      dVector &ny = Ustate[0]->el[eid]->side[sid]->ny();

      Ordinal bqtot = Ustate[0]->el[eid]->side[sid]->qtot();
      Ordinal vqtot = Ustate[0]->el[eid]->qtot;

      u_x.resize(bqtot);
      u_y.resize(bqtot);
      v_x.resize(bqtot);
      v_y.resize(bqtot);
      tau_w2.resize(bqtot);

      dVector r(Ustate[0]->el[eid]->u);
      dVector ru(Ustate[1]->el[eid]->u);
      dVector rv(Ustate[2]->el[eid]->u);
      dVector u(vqtot),v(vqtot);
      dVector ux_v(vqtot),uy_v(vqtot),vx_v(vqtot),vy_v(vqtot);
#ifndef REO_JUMP1
      dvdiv(ru,r,u);
      dvdiv(rv,r,v);

      Ustate[0]->el[eid]->gradient(u,ux_v,uy_v);
      Ustate[0]->el[eid]->gradient(v,vx_v,vy_v);

      Ustate[0]->el[eid]->load_side(ux_v,sid,u_x);
      Ustate[0]->el[eid]->load_side(uy_v,sid,u_y);
      Ustate[0]->el[eid]->load_side(vx_v,sid,v_x);
      Ustate[0]->el[eid]->load_side(vy_v,sid,v_y);
#endif
      for (LocalSize i=0; i<bqtot; i++) {
        Scalar n1 = nx[i];
        Scalar n2 = ny[i];
        Scalar tau_w = (-2.*n1*n2*u_x[i]+(n1*n1-n2*n2)*(u_y[i]+v_x[i])
                        +n1*n2*v_y[i])*mu;
        tau_w2[i] = tau_w*tau_w;
      }
      obj_norm += Ustate[0]->el[eid]->compute_side_integral(tau_w2,sid);
    }
  }

  void apply( const Scalar, const vField &, vField &Ur ) { }

  void adjoint_apply( const Scalar, const vField &state,
                      const vField &adjoint, vField & Ur) {
  }

  inline Obs* obs() { return this; }
  inline const Obs* obs() const { return this; }

  // Obs virtual methods
  void initialize() {}

  void end_condition( vField &F ) {}

  Scalar norm() const {
    return obj_norm;
  }
};

//===========================================================================
//                        Terminal Observations
//===========================================================================

/// Terminal Kinetic Energy (TKE) observation source
class NS_Adjoint::TerminalKineticEnergy : public Source, public Obs {
  vField Uobj;               ///< should be built from an Adjoint vField
  string fobs;               ///< filename for Observation region
  std::vector<Ordinal> eobs; ///< local element list for observation region
  Scalar gamma;              ///< ratio of specific heats
  const NS_State *state;     ///< the state
  Ordinal npredict;          ///< local time step to evaluate at
  Scalar Jobs;               ///< value of observation term
public:
  TerminalKineticEnergy( const string tag, ifstream &in, const vField &F,
                         const NS_State *s, const Ordinal npredict_) :
    Source(tag), Uobj(F.get_comm()), state(s), npredict(npredict_)
    {
      gamma = state->gamma;
      for (vField::size_type i=0; i<F.size(); ++i)
        Uobj.push_back( new Field(F[0]) );
      Jobs = 0.0;
      ndof = 1;
      scan_lb(in);
      if ( !(in >> penalty >> fobs) )
        error("Tracking::Cannot read penalty and Obs region filename.");
      scan_rb(in);

      // get Observation element list
      ifstream obsfile(fobs.c_str());
      string buffer;
      int nobs;
      iVector global_eobs;
      if(obsfile) {
        getline(obsfile,buffer);
        if(!(obsfile>>nobs))
          error("Cannot read number of elements for Observation Region");
        getline(obsfile,buffer);
        global_eobs.resize(nobs);
        for(int i=0;i<nobs;i++) {
          obsfile >> global_eobs[i];// get elements in \Omega_{obs}, 1/line
          getline(obsfile,buffer);
        }
      }
      // Distribute the observation region elements
      for(Ordinal i=0; i<global_eobs.size(); i++)
        if (Uobj[0]->partition->owns(global_eobs[i]))
          eobs.push_back(Uobj[0]->partition->inc(global_eobs[i]));
      initialize();
    }

  // TKE observation
  void set_data( const vField &Us, const Ordinal istep,
                 const Ordinal sstep=0 ) {
    Jobs = 0.0;
    Scalar area;
    if( istep==npredict && sstep==0 ) {
      Element *S[4], *Sm[4];
      Uobj.zero();
      for(size_t i=0; i<eobs.size(); i++) {
        const Ordinal e = eobs[i];

        S[0] = Uobj[0]->el[e]; // local version of the adjoint
        S[1] = Uobj[1]->el[e];
        S[2] = Uobj[2]->el[e];
        S[3] = Uobj[3]->el[e];

        Sm[0] = Us[0]->el[e];  // local version of the state
        Sm[1] = Us[1]->el[e];
        Sm[2] = Us[2]->el[e];
        Sm[3] = Us[3]->el[e];

        dVector r(Sm[0]->u);
        dVector ru(Sm[1]->u);
        dVector rv(Sm[2]->u);
        dVector En(Sm[3]->u);

        const Ordinal qtot = S[0]->qtot;

        dVector wk(qtot), tmp(qtot);

        // compute the kinetic energy per unit volume
        dvmul(ru, ru, wk);
        dvmul(rv, rv, tmp);
        dvadd(tmp, wk);
        dvdiv(wk, r, wk);
        S[0]->fill(wk);
        Jobs += S[0]->integrate(&area);
        // cout << "Element_i = " << i << ", J_{TKE} = " << Value << endl;

        // why is this computed twice? [SSC]
        dvmul(ru, ru, wk);      // (m)^2
        dvvtvp(rv, rv, wk, wk); // (m)^2 + (n)^2
        dvdiv(wk, r, tmp);      // rho |v|^2
        dvdiv(tmp, r, S[0]->u); // |v|^2
        scale(0.5, S[0]->u);    // lam1 = 0.5*(m^2+n^2)/rho^2
        dvdiv(ru, r, S[1]->u);
        scale(-1.0, S[1]->u);   // lam2 = -m/rho
        dvdiv(rv, r, S[2]->u);
        scale(-1.0, S[2]->u);   // lam3 = -n/rho
        scale(0.0, S[3]->u);    // lam4 = 0
      }
    }
  }

  void apply( const Scalar, const vField &, vField &Ur ) { }

  void adjoint_apply( const Scalar, const vField &,
                      const vField &, vField &Ur ) { }

  inline Obs* obs() { return this; }
  inline const Obs* obs() const { return this; }

  // Obs virtual methods
  void initialize() {
    Uobj.zero();
  }

  void end_condition( vField &F ) {
    // DGM::Comm::World->cout() << "Applying end condition:  " << type << endl;
    axpy( penalty, Uobj, F );
  }

  Scalar norm() const {
    return 0.0;
  }

  Scalar cost() const {
    return 0.0;
  }

  Scalar terminal_cost() const {
    // cout << "J_{TKE} = " << Jobs << endl;
    return pt5*penalty*Jobs;
  }

};

} // namespace Reo

#endif   // REO_NS_ADJOINT_HPP
