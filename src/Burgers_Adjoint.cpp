/*=============================================================================
  Module:     Reo Adjoint Burgers Module

  Contact:    Scott Collis

  Copyright:  (c)2003 Rice University
              (c)2008 Sandia National Laboratories
=============================================================================*/

/** \file Burgers_Adjoint.cpp
    \brief Burgers Adjoint equation solver
    \author Scott Collis
*/

// local includes
#include "ReoConfig.hpp"
#include "Reo.hpp"
#include "Burgers_State.hpp"
#include "Burgers_Adjoint.hpp"

// DGM includes
#include "Format.hpp"
#include "TimeInt.hpp"

namespace Reo {

// if defined then perform a projection to when computing the diffusive flux
#define REO_PROJECT_DIFF_FLUX

// constructor
Burgers_Adjoint::Burgers_Adjoint(DGM::ArgList &args, const State* S,
                                 const DGM::Comm::Ptr comm_)
  : Domain(args,comm_), Adjoint(S), Uobj(comm_), Uv(comm_) {

  // cout << "Burgers_Adjoint(...)" << endl;

  // setup local pointer to State
  state = dynamic_cast<const Burgers_State*>(state_);

  // set the number of fields in the domain
  Nfields = 1;                         // = 1 for a scalar problem

  npredict = params.get("npredict",0);

  // initialize parameters
  Ordinal p, q;
  p = params["p"];                     // polynomial order
  comm->cout() << "Burgers_Adjoint:  p = "<< p <<endl;
  if ( !(q=params["q"]) ) q = p + 2;   // number of quadrature points
  nsd = params["nsd"];                 // number of space dimensions

  // read arguments (overrides defaults and input file)
  parse_args( args );

  mu = params["vis"];                  // viscosity

  // build a Field of Elements and Sides
  if (params["imesh"]) {
    error("Burgers_Adjoint internal mesh not supported");
  } else if (params["bmesh"]) {
    U.push_back( new Field(p, q, root, "u", partition, 1, Reo::NumEqntype,
                           p2i(BURGERS), comm ) );
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

  // allocate local workspace
  wk1.resize(max(Lmax(),Qmax()));
  wk2.resize(max(Lmax(),Qmax()));
  wk3.resize(max(Lmax(),Qmax()));

  // make sure that storage is initialized
  zero_all_fields();

  // make analysis object
  response = Response::factory(U, this);

  setup_BCdb();

  setup_Sourcedb();

  set_TimeInt();
}


/// Need to override the default from Domain to use adjoint methods
void Burgers_Adjoint::set_TimeInt( Ordinal ) {
  int inttype = params["inttype"];
  switch(inttype) {
  case TimeInt::FORWARD_EULER: {
    comm->cout() << "Burgers_Adjoint:: using Forward Euler" << endl;
    time_int = new ForwardEuler( this );
    break; }
  case TimeInt::TVD_RK: {
    comm->cout() << "Burgers_Adjoint:: using TVD RK" << endl;
    time_int = new TVD( this );
    break; }
  case TimeInt::RUNGE_KUTTA: {
    comm->cout() << "Burgers_Adjoint:: using Runge-Kutta-4" << endl;
    time_int = new RungeKutta( this );
    break; }
  case TimeInt::SSPRK: {
    comm->cout() << "Burgers_Adjoint:: using SSPRK" << endl;
    time_int = new SSPRK( this );
    break; }
#ifdef DGM_USE_ITL
  case TimeInt::BACKWARD_EULER: {
    comm->cout() << "Burgers_Adjoint:: using Backward-Euler" << endl;
    time_int = new BackwardEuler( this, ".adj" );
    break; }
#endif
  case TimeInt::LSRK14: {
    comm->cout() << "Burgers_Adjoint:: using LSRK14" << endl;
    time_int = new LSRK14( this );
    break; }
  default:
    comm->error("Burgers_Adjoint::set_TimeInt() "
                "Unsupported time integration type");
    break;
  }
}


void Burgers_Adjoint::zero_all_fields() {
  Domain::zero_all_fields();
  Uv.zero();
  Ustate.zero();
}


void Burgers_Adjoint::time_derivative( vField &Us, vField &Uf ) {
#ifdef REO_BURGERS_NO_CONVECTION
  Uf.zero();
#else
  convection( Us, Uf );
#endif
  diffusion( Us, Uv, Uf );
  add_source(Us, Uf);
  project( Uf );
}


void Burgers_Adjoint::prestep( vField &F, const Ordinal istep,
                               const Ordinal sstep, const Scalar time) {
  state->load_field( Ustate, istep, sstep); //Ustate[0]->elmt_data=1.0;
  control->set_data( istep, sstep );
  objective->set_data( Ustate, istep, sstep );
  if (time_int->is_explicit()) computeGrad( F, Ustate, istep, sstep );
}


void Burgers_Adjoint::poststep( vField &F, const Ordinal istep,
                                const Ordinal sstep, const Scalar time) {
  //cout << "Storing adjoint at " << istep << " " << sstep << endl;
  store(F,istep,sstep);
  if (time_int->is_implicit()) computeGrad( F, Ustate, istep, sstep );
}

void Burgers_Adjoint::convection( vField &Uf, vField &Ff ) {
  Ustate.fill_sides();                  // put state soln on the sides
  Ustate.share_sides();
  const_cast<Burgers_State*>(state)->enforce_bc(Ustate);

  Uf.fill_sides();                      // put adjoint soln on the sides
  Uf.share_sides();
  enforce_bc(Uf);                       // update adjoint bc side values

  convective_flux( Ustate, Uf, Ff );        // compute surface fluxes on sides

  for (LocalSize e=0; e<Uf[0]->ne; e++) {
    Element *U = Uf[0]->el[e];          // adjoint
    Element *F = Ff[0]->el[e];          // flux
    Element *S = Ustate[0]->el[e];      // base state
    U->gradient( U->u, F->u );
    dvmul( S->u, F->u );
    U->lift( F, F->u );// add side fluxes to interior
  }
}

Scalar Burgers_Adjoint::dfabs( Scalar x ) {
  if (x > 0.0)
    return 1.0;
  else if (x < 0.0)
    return -1.0;
  else
    return 0.0;
}

/// adoint Lax-Friedrichs flux
/*! \warning This will not work with general side orientations */
void Burgers_Adjoint::convective_flux(const vField &Ub, vField &Uf, vField &Ff) {
  // cout << "Burgers_Adjoint::convective_flux(...)" << endl;
  Scalar nx;
  Scalar sl, sr, lmax, dlmax;
  // Scalar lf_flux;
  Scalar bl, br;

  for (LocalSize e=0; e<Uf[0]->ne; e++) {
    Element *U = Uf[0]->el[e];
    Element *F = Ff[0]->el[e];
    const Element *B = Ub[0]->el[e];
    //if (e==0) cout<<e<<": "<<B->side[0]->u[0]<<", "<<B->side[1]->u[0]<<endl;
    for (LocalSize i=0; i<U->nSides(); i++) {
      if (U->side[i]->link) {
        for (LocalSize q=0; q<U->side[i]->qtot(); q++) {
          nx = U->side[i]->nx(q);

          sl = U->side[i]->u[q];            // adjoint
          bl = B->side[i]->u[q];            // state
          //const Scalar s_loc = bl*nx*sl;

          sr = U->side[i]->link->u[q];      // adjoint
          br = B->side[i]->link->u[q];      // state
          //const Scalar s_adj = bl*nx*sr;  // note bl used here [ssc]

#ifdef REO_BURGERS_HACK_FLUX
          lmax = 0.5;
          dlmax = 0.0;
#else
#ifdef REO_BURGERS_AVG_FLUX
          lmax = 0.5*(fabs(bl)+fabs(br));
          dlmax = 0.5;
#else
#ifdef REO_BURGERS_CENTRAL_FLUX
          lmax = 0.0;
          dlmax = 0.0;
#else
          // this is the actual LF flux
          lmax = max(fabs(bl),fabs(br));
          dlmax = 0.0;
#endif
#endif
#endif
          // Note that the adjoint flux is not conservative!
          Scalar lf_flux_l = -0.5*( bl*nx*sl - bl*nx*sr + lmax*(sl - sr)
                                    + dlmax*dfabs(bl)*(sl-sr)*(bl-br) );
          Scalar lf_flux_r = -0.5*( br*nx*sl - br*nx*sr + lmax*(sr - sl)
                                    + dlmax*dfabs(br)*(sr-sl)*(br-bl) );

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

//  Compute the (stabilized) Bassi and Rebay diffusive flux
void Burgers_Adjoint::diffusion( vField &Uf, vField &Ff, vField &Rf ) {
  if (mu == 0) return;
  //  cout << "Diffusion for Field = " << Uf[0]->name << endl;
  Uf.fill_sides();                   // put solution on the sidess
  Uf.share_sides();
  enforce_bc(Uf);                    // update bc side values
  average_flux( Uf, Ff, '+' );       // F's sides are average of the solution
  if (stab!=0 || bstab!=0) {
    copy_sides(Uf,Rf);               // Put the Uf sides on Rf
    Rf.share_sides();
    enforce_bc(Rf);
  }
  for (LocalSize e=0; e<Uf[0]->ne; e++) {
    Element *U = Uf[0]->el[e];
    Element *F = Ff[0]->el[e];
    const LocalSize qtot = U->qtot;
    const LocalSize nModes = U->nModes();
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
      U->gradient(ux, F->u, 'x');             // ux = u_,{xx}
    } else {
      comm->cerr()<< "Burgers_Adjoint::diffusion "
                  << "-- illegal value of nsd" << endl;
      comm->exit(DGM::FAILURE);
    }
  }
  Uf.share_sides();
  enforce_flux_bc(Uf);                        // put flux BC's on bc sides
  if (stab!=0)
    interior_penalty_flux( Rf, Uf, Ff, stab*Uf.get_max_sigma() );
  else
    average_flux( Uf, Ff, '-' );
  if (bstab!=0)
    enforce_boundary_penalty( Rf, Ff, bstab*Uf.get_max_sigma() );
  for (LocalSize e=0; e<Uf[0]->ne; e++) {
    Element *U = Uf[0]->el[e];
    Element *F = Ff[0]->el[e];
    U->lift( F, F->u );      // add side fluxes to interior
  }
  // switch sign for adjoint
  add( Ff, Rf );                              // add in viscous contribution
}

/// put the interior penalty flux on the sides
void Burgers_Adjoint::interior_penalty_flux(const vField &Up, const vField &Us,
                                            vField &Uf, const Scalar sigma) {
#ifdef REO_USE_GETSIDEMAPS
            iVector mapl, mapr;
#endif
  for (vField::size_type n=0; n<Us.size(); n++) {
    for (LocalSize e=0; e<Us[n]->ne; e++) {
      const Element *P = Up[n]->el[e];
      const Element *S = Us[n]->el[e];
      Element *F = Uf[n]->el[e];
      for (SideLoop i(F); !i.end(); ++i) {
        if (i.master_side()) {
          const Side * const sl = i.side(S);
          const Side * const sr = i.link(S);
          const Side * const pl = i.side(P);
          const Side * const pr = i.link(P);
          Side * const fl = i.side(F);
          Side * const fr = i.link(F);
          const Ordinal qtot = i.qtot();
#ifdef REO_USE_GETSIDEMAPS
          get_side_maps(sl, sr, mapl, mapr);
#endif
          for (Ordinal q=0; q<qtot; q++) {
#ifdef REO_USE_GETSIDEMAPS
            const Ordinal ql = mapl[q];
            const Ordinal qr = mapr[q];
            fl->u[ql] = pt5 * (sl->u[ql] - sr->u[qr]) +
                        sigma*(pr->u[qr] - pl->u[ql]);
            fr->u[qr] = -fl->u[ql];
#else
            const Ordinal ql = F->sideMap(sl, q);
            const Ordinal qr = F->sideMap(sr, q);
            fl->u[ql] = pt5 * (sl->u[ql] - sr->u[qr]) +
                        sigma*(pr->u[qr] - pl->u[ql]);
            fr->u[qr] = -fl->u[ql];
#endif
          }
        }
      }
    }
  }
}

/*! \warning Does this work with general side orientations */
void Burgers_Adjoint::enforce_boundary_penalty(const vField &S, vField &F,
                                               const Scalar sigma) {
  // cout << "Burgers_Adjoint::enforce_boundary_penalty()" << endl;
  for (LocalSize n=0; n<S[0]->nbc; ++n) {
    for(LocalSize i=0; i<S[0]->bc[n]->S->qtot(); ++i) {
      F[0]->bc[n]->S->u[i] += sigma*( S[0]->bc[n]->S->link->u[i] -
                                      S[0]->bc[n]->S->u[i] );
      F[0]->bc[n]->S->link->u[i] = -F[0]->bc[n]->S->u[i];
    }
  }
}

//===========================================================================
//                        BC database management
//===========================================================================

// Load up the available BC types
void Burgers_Adjoint::setup_BCdb( ) {
  BC_db = state->BC_db;
}

void Burgers_Adjoint::enforce_bc(vField &F) {
  for (BC::db_citr i=BC_db.begin(); i!= BC_db.end(); ++i){
    i->second->adjoint_apply( t, Ustate, F );
  }
}

void Burgers_Adjoint::enforce_flux_bc(vField &F) {
  for (BC::db_citr i=BC_db.begin(); i!= BC_db.end(); ++i)
    i->second->adjoint_apply_flux( t, Ustate, F);
}

//===========================================================================
//                        Source database management
//===========================================================================

/// Load up the available Source types
void Burgers_Adjoint::setup_Sourcedb( ) {
  // cout << "Burgers_Adjoint::setup_Sourcedb" << endl;
  Source_db = state->Source_db;
  string fname = root+".obj";
  ifstream in(fname.c_str());
  if (in) read_Sourcedb( in );   // database of active Source types
}

/// make the Source terms
Source::Ptr Burgers_Adjoint::make_Source( ifstream &in, string &tag ) {
  string code;
  Source::Ptr p;
  // cout << "Burgers_Adjoint::make_Source" << endl;
  if (!(in >> code)) return p;
  while (code[0]=='#') {  // eat comment lines
    string buffer;
    getline(in,buffer);
    if (!(in >> code)) return p;
  }
  if (lowerCase(code) == "tracking") {
    if (!(in >> tag)) error("Burgers_Adjoint::Cannot read Tracking tag",1);
    p.reset( new Tracking(tag,in,U) );
  } else if (lowerCase(code) == "terminaltracking") {
    if (!(in >> tag))
      error("Burgers_Adjoint::Cannot read TerminalTracking tag",1);;
    p.reset( new TerminalTracking(tag,in,U,npredict) );
  } else if (lowerCase(code) == "unsteadytracking") {
    if (!(in >> tag))
      error("Burgers_Adjoint::Cannot read TerminalTracking tag",1);;
    p.reset( new UnsteadyTracking(tag,in,U,state) );
  } else {
    error("Burgers_Adjoint::make_Source() Illegal Source type",1);
  }
  return p;
}


/// Add Source terms
void Burgers_Adjoint::add_source(const vField &Us, vField &Ur) {
  // cout << "Burgers_Adjoint::add_source(vField &)" << endl;
  for (Source::db_citr i=Source_db.begin(); i!= Source_db.end(); ++i) {
    // cout << "Adding source: " << i->first << endl;
    i->second->adjoint_apply( t, Ustate, Us, Ur );
  }
}


void Burgers_Adjoint::computeGrad(vField& Ua, vField& Us, Ordinal istep,
                                  Ordinal sstep) {
  //cout << "computeGrad:: istep = "<<istep<<", sstep = "<<sstep<<endl;

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


/// Set the field from a file
void Burgers_Adjoint::set_ic(vField &F, string ext) {
  string fname = root+ext;
  ifstream in(fname.c_str());
  if (!in) {
    F.zero(); // default to zero initial condition
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
