/*=============================================================================
  Module:     Reo Adjoint LinBurgers Module

  Author:     Guoquan Chen and S. Scott Collis

  Copyright:  S. Scott Collis
              Department of Mechanical Engineering and Materials Science
              Rice University, MS 321
              Houston, TX 77005-1892
              (713) 348-3617
              collis@rice.edu
=============================================================================*/

/** \file  LinBurgers_Adjoint.cpp
    \brief Adjoint implementation for the linearized Burgers equation. */

// DGM includes
#include "Format.hpp"
#include "TimeInt.hpp"

// Reo includes
#include "ReoConfig.hpp"
#include "Reo.hpp"
#include "Burgers_State.hpp"
#include "Burgers_Adjoint.hpp"
#include "LinBurgers_State.hpp"
#include "LinBurgers_Adjoint.hpp"

namespace Reo {

// if defined then perform a projection to when computing the diffusive flux
#define REO_PROJECT_DIFF_FLUX

/// Constructor
LinBurgers_Adjoint::LinBurgers_Adjoint(DGM::ArgList &args,
                                       const State *S,
                                       const State *B,
                                       const Adjoint *A,
                                       const DGM::Comm::Ptr comm_)
  : Domain(args,comm_), Adjoint(S), Ubase(comm_),
    Uadj(comm_), Uv(comm_) {

  // cout << "LinBurgers_Adjoint(...)" << endl;

  // setup local pointer to State
  state = dynamic_cast<const LinBurgers_State*>(state_);

  // setup local pointer to Base State and Adjoint
  base_state = dynamic_cast<const Burgers_State*>(B);
  base_adjoint = dynamic_cast<const Burgers_Adjoint*>(A);

  // set the number of fields in the domain
  Nfields = 1;                         // = 1 for a scalar problem

  // read arguments (overrides defaults and input file)
  parse_args( args );

  npredict = params.get("npredict", 0);

  // initialize parameters
  Ordinal p, q;
  p = params["p"];                     // polynomial order
  comm->cout() << "LinBurgers_Adjoint:  p = "<< p <<endl;
  if ( !(q=params["q"]) ) q = p + 2;   // number of quadrature points
  nsd = params["nsd"];                 // number of space dimensions


  mu = params["vis"];                  // viscosity

  // build a Field of Elements and Sides
  if (params["imesh"]) {
    error("LinBurgers_Adjoint internal mesh not supported",-1);
  } else if (params["bmesh"]) {
    U.push_back( new Field(p, q, root, "u", partition, 1, Reo::NumEqntype,
                           p2i(LINBURGERS), comm ) );
  } else {
    U.push_back( new Field(p, q, root, "u", partition, comm ) );
  }

  // set some additional domain parameters
  ne = U[0]->ne;
  nsd = U[0]->nsd();

#ifdef REO_USE_GETSIDEMAPS
  setup_side_maps();
#endif

  // make auxiliary Fields using copy constructor
  Ut.push_back( new Field(U[0], root, U[0]->name) );
  Uv.push_back( new Field(U[0], root, U[0]->name) );

  // use state boundary conditions on these fields
  Ustate.push_back( new Field(U[0], root, U[0]->name) );
  Ubase.push_back( new Field(U[0], root, U[0]->name) );
  Uadj.push_back( new Field(U[0], root, U[0]->name) );

  // allocate local workspace
  wk1.resize(max(Lmax(),Qmax()));
  wk2.resize(max(Lmax(),Qmax()));
  wk3.resize(max(Lmax(),Qmax()));

  zero_all_fields();

  response = Response::factory(U, this);

  setup_BCdb();

  setup_Sourcedb();

  set_TimeInt();
}


// Need to override the default from Domain to use adjoint methods
void LinBurgers_Adjoint::set_TimeInt( Ordinal ) {
  int inttype = params["inttype"];
  switch(inttype) {
  case TimeInt::FORWARD_EULER: {
    comm->cout() << "LinBurgers_Adjoint:: using Forward Euler" << endl;
    time_int = new ForwardEuler( this );
    break; }
  case TimeInt::TVD_RK: {
    comm->cout() << "LinBurgers_Adjoint:: using TVD RK" << endl;
    time_int = new TVD( this );
    break; }
  case TimeInt::RUNGE_KUTTA: {
    comm->cout() << "LinBurgers_Adjoint:: using Runge-Kutta-4" << endl;
    time_int = new RungeKutta( this );
    break; }
  case TimeInt::SSPRK: {
    comm->cout() << "LinBurgers_Adjoint:: using SSPRK" << endl;
    time_int = new SSPRK( this );
    break; }
#ifdef DGM_USE_ITL
  case TimeInt::BACKWARD_EULER: {
    comm->cout() << "LinBurgers_Adjoint:: using Backward-Euler" << endl;
    time_int = new BackwardEuler( this, ".adj" );
    break; }
#endif
  case TimeInt::LSRK14: {
    comm->cout() << "LinBurgers_Adjoint:: using LSRK14" << endl;
    time_int = new LSRK14( this );
    break; }
  default:
    comm->cerr() << "LinBurgers_Adjoint::set_TimeInt() "
                 << "Unsupported time integration type" << endl;
    comm->exit(DGM::FAILURE);
  }
}


void LinBurgers_Adjoint::zero_all_fields() {
  Domain::zero_all_fields();
  Uv.zero();
  Ustate.zero();
  Ubase.zero();
  Uadj.zero();
}

//===========================================================================
//                             Solve Methods
//===========================================================================

void LinBurgers_Adjoint::time_derivative( vField &Us, vField &Uf ) {
#ifdef REO_BURGERS_NO_CONVECTION
  Uf.zero();
#else
  convection( Us, Uf );
#endif
  diffusion( Us, Uv, Uf );
  add_source(Us, Uf);
  project( Uf );
}

void LinBurgers_Adjoint::prestep( vField &F, const Ordinal istep,
                                  const Ordinal sstep, const Scalar time) {
  //cout<<"LinBurgers_Adjoint::prestep("<<&F<<","<<istep<<","<<sstep<<","
  //    <<time<<")"<<endl;
  base_state->load_field( Ubase, istep, sstep ); //Ubase[0]->elmt_data=1.0;
  const_cast<Control*>(base_state->get_control())->set_data(istep, sstep);
  const_cast<Objective*>(base_adjoint->get_objective())->
    set_data( Ubase, istep, sstep);

  //cout << "Reading adjoint at " << istep << " " << sstep << endl;

  base_adjoint->load_field( Uadj, istep, sstep );

  state->load_field( Ustate, istep, sstep ); //Ustate.zero();
  control->set_data( istep, sstep );
  objective->set_data( Ustate, istep, sstep );

  if (time_int->is_explicit()) computeGrad( F, Ustate, istep, sstep );
}


void LinBurgers_Adjoint::poststep( vField &F, const Ordinal istep,
                                   const Ordinal sstep, const Scalar time) {
  store(F,istep,sstep);
  if (time_int->is_implicit()) computeGrad( F, Ustate, istep, sstep );
}

void LinBurgers_Adjoint::set_end_condition() {
  base_state->load_field(Ubase,npredict,0);
  const_cast<Control*>(base_state->get_control())->set_data(npredict,0);
  const_cast<Objective*>(base_adjoint->get_objective())->
    set_data(Ubase,npredict,0);

  //  cout<<"base_adjoint->load_field("<<npredict<<","<<0<<")\n";
  //  base_adjoint->load_field( Uadj, npredict, 0);

  Adjoint::set_end_condition();
}

void LinBurgers_Adjoint::set_end_condition(const dVector &X,
                                           const Scalar t_, const Ordinal step_) {
  base_state->load_field(Ubase,npredict,0);
  const_cast<Control*>(base_state->get_control())->set_data(npredict,0);
  const_cast<Objective*>(base_adjoint->get_objective())->
    set_data(Ubase,npredict,0);

  //  cout<<"base_adjoint->load_field("<<npredict<<","<<0<<")\n";
  //  base_adjoint->load_field( Uadj, npredict, 0);

  Adjoint::set_end_condition(X, t_, step_);
}

// Compute the linearized adjoint convection term
void LinBurgers_Adjoint::convection( vField &Uf, vField &Ff ) {

  // nonlinear state
  Ubase.fill_sides();
  Ubase.share_sides();
  const_cast<Burgers_State*>(base_state)->enforce_bc(Ubase);

  // linearized adjoint
  Uf.fill_sides();
  Uf.share_sides();
  enforce_bc(Uf);

  convective_flux( Ubase, Ubase, Uf, Ff );

  for (LocalSize e=0; e<Uf[0]->ne; e++) {
    Element *U = Uf[0]->el[e];          // linearized adjoint
    Element *F = Ff[0]->el[e];          // rhs and numerical flux on sides
    Element *S = Ubase[0]->el[e];       // nonlinear state
    U->gradient( U->u, F->u );
    dvmul( S->u, F->u );
    U->lift( F, F->u );// add side fluxes to interior
  }

  // linearized state
  Ustate.fill_sides();
  Ustate.share_sides();
  const_cast<LinBurgers_State*>(state)->enforce_bc(Ustate);

  // adjoint
  Uadj.fill_sides();
  Uadj.share_sides();
  const_cast<Burgers_Adjoint*>(base_adjoint)->enforce_bc(Uadj);

  convective_flux( Ustate, Ubase, Uadj, Ff, false );

  for (LocalSize e=0; e<Uadj[0]->ne; e++) {
    Element *U = Uadj[0]->el[e];        // adjoint
    Element *F = Ff[0]->el[e];          // flux
    Element *S = Ustate[0]->el[e];      // linearized state
    dVector wk(wk1, U->qtot);           // temp workspace
    U->gradient( U->u, wk );
    dvmul( S->u, wk );
    dvadd( wk, F->u );
    U->lift( F, F->u );// add side fluxes to interior
  }

}

Scalar LinBurgers_Adjoint::dfabs( Scalar x ) {
  if (x > 0.0)
    return 1.0;
  else if (x < 0.0)
    return -1.0;
  else
    return 0.0;
}

// linearized adjoint Lax-Friedrichs flux The linear_adjoint should be false
// when evaluating (linearized state, adjoint) term
void LinBurgers_Adjoint::convective_flux(const vField &Ub, const vField &Us,
                                     vField &Uf, vField &Ff,
                                     const bool linear_adjoint) {
  Scalar nx;
  Scalar sl, sr, lmax, dlmax;
  Scalar bl, br;

  for (LocalSize e=0; e<Uf[0]->ne; e++) {
    Element *U = Uf[0]->el[e];
    Element *F = Ff[0]->el[e];
    const Element *B = Ub[0]->el[e];   // base
    const Element *S = Us[0]->el[e];   // state
    for (LocalSize i=0; i<U->nSides(); i++) {
      if (U->side[i]->master()) {
        for (LocalSize q=0; q<U->side[i]->qtot(); q++) {
          nx = U->side[i]->nx(q);

          sl = U->side[i]->u[q];       // adjoint
          bl = B->side[i]->u[q];       // base

          sr = U->side[i]->link->u[q]; // adjoint
          br = B->side[i]->link->u[q]; // base

#ifdef REO_BURGERS_HACK_FLUX // this is correct
          if (linear_adjoint)
            lmax = 0.5;
          else
            lmax = 0.0;
          dlmax = 0.0;
          Scalar lf_flux_l = -0.5*( bl*nx*sl - bl*nx*sr + lmax*(sl - sr)
                                    + dlmax*dfabs(bl)*(sl-sr)*(bl-br) );
          Scalar lf_flux_r = -0.5*( br*nx*sl - br*nx*sr + lmax*(sr - sl)
                                    + dlmax*dfabs(br)*(sr-sl)*(br-bl) );
#else
#ifdef REO_BURGERS_AVG_FLUX  // this is not yet correct
          if (linear_adjoint) {
            lmax = 0.5*(fabs(bl)+fabs(br));
            dlmax = 0.5;
          } else {
            lmax = 0.5*(dfabs(S->side[i]->u[q])*bl +
                        dfabs(S->side[i]->link->u[q])*br);
            dlmax = 0.5;
          }
          Scalar lf_flux_l = -0.5*( bl*nx*sl - bl*nx*sr + lmax*(sl - sr)
                                    + dlmax*dfabs(S->side[i]->u[q])*
                                    (sl-sr)*(bl-br) );
          Scalar lf_flux_r = -0.5*( br*nx*sl - br*nx*sr + lmax*(sr - sl)
                                    + dlmax*dfabs(S->side[i]->link->u[q])*
                                    (sr-sl)*(br-bl) );
#else
#ifdef REO_BURGERS_CENTRAL_FLUX  // this is correct
          lmax = 0.0;
          dlmax = 0.0;
          Scalar lf_flux_l = -0.5*( bl*nx*sl - bl*nx*sr + lmax*(sl - sr)
                                    + dlmax*dfabs(bl)*(sl-sr)*(bl-br) );
          Scalar lf_flux_r = -0.5*( br*nx*sl - br*nx*sr + lmax*(sr - sl)
                                    + dlmax*dfabs(br)*(sr-sl)*(br-bl) );
#else
          // this is the actual LF flux
          lmax = max(fabs(bl),fabs(br));
          dlmax = 0.0;
          Scalar lf_flux_l = -0.5*( bl*nx*sl - bl*nx*sr + lmax*(sl - sr)
                                    + dlmax*dfabs(bl)*(sl-sr)*(bl-br) );
          Scalar lf_flux_r = -0.5*( br*nx*sl - br*nx*sr + lmax*(sr - sl)
                                    + dlmax*dfabs(br)*(sr-sl)*(br-bl) );
#endif
#endif
#endif
          // put numerical flux on the F field sides
          F->side[i]->u[q]       =  lf_flux_l;
          F->side[i]->link->u[q] =  lf_flux_r;

          // put interior flux on the U field sides
          U->side[i]->u[q]       =  0.0;
          U->side[i]->link->u[q] =  0.0;
        }
      }
    }
  }
}

//  Compute the Bassi and Rebay diffusive flux
void LinBurgers_Adjoint::diffusion( vField &Uf, vField &Ff, vField &Rf ) {
  if (mu == 0) return;
  //  cout << "Diffusion for Field = " << Uf[0]->name << endl;
  const LocalSize nsd = Uf[0]->nsd();
  Uf.fill_sides();                   // put solution on the sidess
  Uf.share_sides();
  enforce_bc(Uf);                    // update bc side values
  average_flux( Uf, Ff, '+' );       // F's sides are average of the solution

  for (LocalSize e=0; e<Uf[0]->ne; e++) {
    Element *U = Uf[0]->el[e];
    Element *F = Ff[0]->el[e];
    const Ordinal qtot = U->qtot;
    const Ordinal nModes = U->nModes();
    dVector ux(wk1,qtot);
    dVector uxh(ux,nModes);
    if (nsd==3) {
      dVector uy(wk2,qtot);
      dVector uyh(uy,nModes);
      dVector uz(wk3,qtot);
      dVector uzh(uz,nModes);
      U->gradient(U->u, ux, uy, uz);
      U->lift( F, ux, 'x' );
#ifdef REO_PROJECT_DIFF_FLUX
      U->project(ux);
#endif
      U->lift( F, uy, 'y' );
#ifdef REO_PROJECT_DIFF_FLUX
      U->project(uy);
#endif
      U->lift( F, uz, 'z' );
#ifdef REO_PROJECT_DIFF_FLUX
      U->project(uz);
#endif
      scale( mu, ux );
      scale( mu, uy );
      scale( mu, uz );
      U->fill_sides( ux, uy, uz );            // normal viscous flux on sides

      U->gradient(ux, ux, 'x');               // ux = u_{,xx}
      U->gradient(uy, uy, 'y');               // uy = u_{,yy}
      U->gradient(uz, uz, 'z');               // uz = u_{,zz}
      dvadd( ux, uy, F->u );                  // F->u = u_{,xx} + u_{,yy}
      dvadd( uz, F->u );                      // F->u += u_{,zz}
    } else if (nsd==2) {
      dVector uy(wk2,qtot);
      dVector uyh(uy,nModes);
      U->gradient(U->u, ux, uy);
      U->lift( F, ux, 'x' );
#ifdef REO_PROJECT_DIFF_FLUX
      U->project(ux);
#endif
      U->lift( F, uy, 'y' );
#ifdef REO_PROJECT_DIFF_FLUX
      U->project(uy);
#endif
      scale( mu, ux );
      scale( mu, uy );
      U->fill_sides( ux, uy );                // normal viscous flux on sides

      U->gradient(ux, ux, 'x');               // ux = u_{,xx}
      U->gradient(uy, uy, 'y');               // uy = u_{,yy}
      dvadd( ux, uy, F->u );                  // F->u = u_{,xx} + u_{,yy}
    } else if (nsd==1) {
      U->gradient(U->u, ux, ux);
      U->lift( F, ux, 'x' );
#ifdef REO_PROJECT_DIFF_FLUX
      U->project(ux);
#endif
      scale( mu, ux );
      U->fill_sides( ux, ux );                // normal viscous flux on sides
      U->gradient(ux, F->u, 'x');             // ux = uxx
    } else {
      comm->cerr()<< "Burgers:diffusion -- illegal value of nsd" << endl;
      comm->exit(DGM::FAILURE);
    }
  }
  Uf.share_sides();
  enforce_flux_bc(Uf);                        // put flux BC's on bc sides
  average_flux( Uf, Ff, '-' );
  for (LocalSize e=0; e<Uf[0]->ne; e++) {
    Element *U = Uf[0]->el[e];
    Element *F = Ff[0]->el[e];
    U->lift( F, F->u );      // add side fluxes to interior
  }
  // switch sign for adjoint
  add( Ff, Rf );                              // add in viscous contribution
}

//===========================================================================
//                        BC database management
//===========================================================================

// Load up the available BC types
void LinBurgers_Adjoint::setup_BCdb( ) {
  BC_db = state->BC_db;
}

void LinBurgers_Adjoint::enforce_bc(vField &F) {
  for (BC::db_citr i=BC_db.begin(); i!= BC_db.end(); ++i){
    i->second->adjoint_apply( t, Ubase, F );
  }
}

void LinBurgers_Adjoint::enforce_flux_bc(vField &F) {
  for (BC::db_citr i=BC_db.begin(); i!= BC_db.end(); ++i)
    i->second->adjoint_apply_flux( t, Ubase, F);
}

//===========================================================================
//                        Source database management
//===========================================================================

/// Load up the available Source types
void LinBurgers_Adjoint::setup_Sourcedb( ) {
  // cout << "LinBurgers_Adjoint::setup_Sourcedb" << endl;
  Source_db = state->Source_db;
  string fname = root+".obj";
  ifstream in(fname.c_str());
  if (in) read_Sourcedb( in );   // database of active Source types
}

/// make the Adjoint source terms
Source::Ptr LinBurgers_Adjoint::make_Source( ifstream &in, string &tag ) {
  // cout << "LinBurgers_Adjoint::make_Source" << endl;
  string code;
  Source::Ptr p;
  if (!(in >> code)) return p;
  while (code[0]=='#') {  // eat comment lines
    string buffer;
    getline(in,buffer);
    if (!(in >> code)) return p;
  }
  if (lowerCase(code) == "tracking") {
    if (!(in >> tag)) error("LinBurgers_Adjoint::Cannot read Tracking tag",1);
    p.reset( new Tracking(tag,in,U) );
  } else if (lowerCase(code) == "terminaltracking") {
    if (!(in >> tag))
      error("LinBurgers_Adjoint::Cannot read TerminalTracking tag",1);;
    p.reset( new TerminalTracking(tag,in,U,npredict) );
  } else if (lowerCase(code) == "unsteadytracking") {
    if (!(in >> tag))
      error("LinBurgers_Adjoint::Cannot read TerminalTracking tag",1);;
    p.reset( new UnsteadyTracking(tag,in,U,state) );
  } else {
    error("LinBurgers_Adjoint::make_Source() Illegal Source type",1);
  }
  return p;
}

/// Add Source terms
void LinBurgers_Adjoint::add_source(const vField &Us, vField &Ur) {
  // cout << "LinBurgers_Adjoint::add_source(vField &)" << endl;
  for (Source::db_citr i=Source_db.begin(); i!= Source_db.end(); ++i) {
    // cout << "Adding source: " << i->first << endl;
    i->second->adjoint_apply(t, Ustate, Us, Ur );
  }
}

void LinBurgers_Adjoint::computeGrad( vField& Ua, vField& Us,
                                      Ordinal istep, Ordinal sstep ) {
  // cout << "computeGrad:: istep = "<<istep<<", sstep = "<<sstep<<endl;
  // setup Adjoint side info
  Ua.fill_sides();              // put solution on the sides
  Ua.share_sides();
  enforce_bc(Ua);               // update bc side values
  average_flux( Ua, Uv, '+' );  // Uv's sides are average of the solution
  for (LocalSize n=0; n<Ua[0]->nbc; ++n) {
    Element *U = Ua[0]->bc[n]->elmt;
    Element *F = Uv[0]->bc[n]->elmt;
    dVector ux(wk1,U->qtot);
    dVector uxh(ux,U->nModes());
    U->gradient( U->u, ux, 'x');
    U->lift( F, ux, 'x' );
    U->project(ux);
    scale( mu, ux );
    U->fill_sides( ux, ux );
    Ua[0]->bc[n]->B->u = Ua[0]->bc[n]->S->u;
    scale( -1.0, Ua[0]->bc[n]->B->u );        // put (\hat F^v_n) in B
    U->fill_sides( U->u );                    // put adjoint in S
  }
  // use the adjoint field and sides to build gradient
  control->gradient( Us, Ua, g_control, istep, sstep );
}

//===========================================================================
//                        Initial Conditions
//===========================================================================

// set the field from a file
void LinBurgers_Adjoint::set_ic(vField &F, string ext) {
  string fname = root+ext;
  ifstream in(fname.c_str());
  if (!in) {
    F.zero();
    return;
  }
  string buffer, code;
  getline(in,buffer);
  if (!(in>>code)) error("Cannot read IC code",1);
  getline(in,buffer);
  if (lowerCase(code) == "given") {
    F.fill(in);
  } else if (lowerCase(code) == "restart") {
    string rstfile;
    if (!(in>>rstfile)) {
      comm->cerr() << "Cannot read restart file name from " << fname << endl;
      comm->exit(DGM::FAILURE);
    }
    read(rstfile,F);
  }
#ifdef DGM_NO_PROJECT_IC
  cout << "WARNING:  No projection of Initial condition" << endl;
  for (LocalSize i=0; i<Nfields; i++)
    for (LocalSize e=0; e<ne; e++)
      F[i]->el[e]->state = Element::Physical;
#else
  project( F ); // project field to the polynomial space
#endif
}

} // namespace Reo
