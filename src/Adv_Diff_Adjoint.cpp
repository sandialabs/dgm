/** \file Adv_Diff_Adjoint.cpp
    \brief Advection diffusion Adjoint implementation
    \author Scott Collis
    \author Guoquan Chen
*/

// system includes
#include <cmath>

// local includes
#include "Reo.hpp"
#include "Adv_Diff_Adjoint.hpp"
#include "Adv_Diff_State.hpp"

// DTK includes
#include "DTK_TimeIntegrate.hpp"

// DGM includes
#include "Format.hpp"
#include "TimeInt.hpp"
#include "Partition.tpp"
#include "Trilinos.hpp"

namespace Reo {

/// if defined then perform a projection to when computing the diffusive flux
#define REO_PROJECT_DIFF_FLUX

// constructor
Adv_Diff_Adjoint::Adv_Diff_Adjoint(DGM::ArgList &args, const State* S,
                                   const DGM::Comm::Ptr comm_,
                                   const int pinc ) :
  Domain(args,comm_), 
  Adjoint(S,pinc), Uobj(comm_,"Uobj"), Uv(comm_,"Uv"), Uc(comm_,"Uc") {
  if(comm->verbosity()) comm->cout() << "Adv_Diff_Adjoint(...)" << endl;

  // setup local pointer to State
  state = dynamic_cast<const Adv_Diff_State*>(state_);

  // set the number of fields in the domain
  Nfields = 1;                         // = 1 for a scalar problem

  // read arguments (overrides defaults and input file)
  parse_args( args );

  npredict = params.get("npredict",0);
  cfield = params.get("cfield", false);
  cx = params.get("cx",1.0);               // x wave speed
  cy = params.get("cy",0.0);               // y wave speed
  cz = params.get("cz",0.0);               // z wave speed
  mu = params.get("vis",0.0);              // viscosity
  fv = params.get("fv",0);               // finite volume reconstruction

  // initialize parameters
  Ordinal p, q;
  p = params["p"];                     // polynomial order
  p += p_inc;                          // increment polynomial order if needed
  comm->cout() << "Adv_Diff_Adjoint:  p = "<< p <<endl;
  if ( !(q=params["q"]) ) q = p + 2;   // number of quadrature points
  nsd = params["nsd"];                 // number of space dimensions


  // build a Field of Elements and Sides
  if (params["imesh"]) {
    comm->error("Adv_Diff_Adjoint internal mesh not supported");
  } else if (params["bmesh"]) {
    U.push_back( new Field(p, q, root, "u", partition, 1, Reo::NumEqntype,
                 p2i(ADV_DIFF), comm, p_inc ) );
  } else {
    U.push_back( new Field(p, q, root, "u", partition, comm, p_inc ) );
  }

  // set some additional domain parameters
  ne = U[0]->ne;
  nsd = U[0]->nsd();

  // make auxiliary Fields using copy constructor
  Ut.push_back( new Field(U[0], root, U[0]->name) );
  Uv.push_back( new Field(U[0], root, U[0]->name) );

  // use state boundary conditions on these fields
  Ustate.push_back( new Field(U[0], root, U[0]->name) );
  Uobj.push_back( new Field(U[0], root, U[0]->name) );

  // setup vField names
  U.set_name("U");
  Ut.set_name("Ut");
  Uv.set_name("Uv");
  Uc.set_name("Uc");
  Ustate.set_name("Ustate");
  Uobj.set_name("Uobj");
  Uc.set_name("Uc");

  // convective field
  if (cfield) {
    Uc.push_back( new Field(U[0], root, "Cx") );
    if (nsd>1) Uc.push_back( new Field(U[0], root, "Cy") );
    if (nsd>2) Uc.push_back( new Field(U[0], root, "Cz") );
    set_ic( Uc, ".cfd" );
    Uc.fill_sides();
    Uc.share_sides();
    Uc.fill_bc_sides();  // make sure that boundary sides are valid
  }

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

// Parse parameters from the argument list
void Adv_Diff_Adjoint::parse_args( DGM::ArgList &args ) {
  string name, value;
  list< DGM::ArgList::iterator > li;
  for ( DGM::ArgList::iterator a = args.begin(); a != args.end(); a++ ) {
    if ( (*a)[0] == '-' ) {
      name = *a;
      if (name == "-cx") {
        li.push_back(a);
        value = *(++a);
        li.push_back(a);
        params["cx"] = atof(value.c_str());
      } else if (name == "-cy") {
        li.push_back(a);
        value = *(++a);
        li.push_back(a);
        params["cy"] = atof(value.c_str());
      } else if (name == "-cz") {
        li.push_back(a);
        value = *(++a);
        li.push_back(a);
        params["cz"] = atof(value.c_str());
      } else if (name == "-fv") {
        li.push_back(a);
        value = *(++a);
        li.push_back(a);
        params["fv"] = atoi(value.c_str());
      } else if (name == "-cfield") {
        li.push_back(a);
        params["cfield"] = true;
      } else if (name == "-npredict") {
        li.push_back(a);
        value = *(++a);
        li.push_back(a);
        params["npredict"] = atoi(value.c_str());
      } else if (name == "-help") {
        params["showUsage"] = 1;
        showUsage();
      }
    }
  }
#ifdef DGM_REMOVE_ARGUMENTS
  // remove tagged arguments
  for ( list< DGM::ArgList::iterator >::iterator a=li.begin();
        a!=li.end(); a++) args.erase(*a);
#endif
}

void Adv_Diff_Adjoint::showUsage() {
  comm->cout()
    << "Adv_Diff_Adjoint Class Options \n"
    << "----------------------------------------------------------------\n"
    << "-cx       " << '\t' << "Wave speed in x-direction\n"
    << "-cy       " << '\t' << "Wave speed in y-direction\n"
    << "-cz       " << '\t' << "Wave speed in z-direction\n"
    << "-fv       " << '\t' << "Finite volume reconstuction (0=none)\n"
    << "-cfield   " << '\t' << "File name for convective field\n"
    << "-npredict " << '\t' << "Number of time steps for opt prediction\n"
    << "----------------------------------------------------------------\n";
}

/** Need to override the default from Domain to use adjoint methods
 *  - In general, the adjoint may need different solver setting which is
 *    why we instantiate another TimeInt
 *  - But this is wasteful in terms of memory and should be made an option
 *  - Linear cases, likely can/should use the same solver settings
 * */
void Adv_Diff_Adjoint::set_TimeInt( Ordinal ) {
  int inttype = params["inttype"];
  switch(inttype) {
  case TimeInt::FORWARD_EULER: {
    comm->cout() << "Adv_Diff_Adjoint:: using Forward Euler" << endl;
    time_int = new ForwardEuler( this );
    break; }
  case TimeInt::TVD_RK: {
    comm->cout() << "Adv_Diff_Adjoint:: using TVD RK" << endl;
    time_int = new TVD( this );
    break; }
  case TimeInt::RUNGE_KUTTA: {
    comm->cout() << "Adv_Diff_Adjoint:: using Runge-Kutta-4" << endl;
    time_int = new RungeKutta( this );
    break; }
  case TimeInt::SSPRK: {
    comm->cout() << "Adv_Diff_Adjoint:: using SSPRK" << endl;
    time_int = new SSPRK( this );
    break; }
  case TimeInt::LSRK14: {
    comm->cout() << "Adv_Diff_Adjoint:: using Low Storage RK14" << endl;
    time_int = new LSRK14( this );
    break; }
#ifdef DGM_USE_ITL
  case TimeInt::BACKWARD_EULER: {
    comm->cout() << "Adv_Diff_Adjoint:: using Backward-Euler" << endl;
    time_int = new BackwardEuler( this, ".adj" );
    break; }
#endif
#ifdef DGM_USE_EPETRA
  case DGM::Trilinos::BackwardEuler::id : {
    if (!U.is_contiguous()) make_contiguous();
    time_int = new DGM::Trilinos::BackwardEuler( this );
    break; }
  case DGM::Trilinos::Trapezoidal::id : {
    if (!U.is_contiguous()) make_contiguous();
    time_int = new DGM::Trilinos::Trapezoidal( this );
    break; }
#ifdef DGM_USE_RYTHMOS
  case DGM::Trilinos::Rythmos::id : {
    if (!U.is_contiguous()) make_contiguous();
    time_int = new DGM::Trilinos::Rythmos( this );
    break; }
#endif
#endif
  default:
    comm->error("Adv_Diff_Adjoint::set_TimeInt() Unsupported time "
                "integration type");
    break;
  }
  // Optionally try out DTK::TimeIntegrate
  if (!json_domain.isMember("Time")) json_domain.set("Time",Json::objectValue);
  const string integrator =
      json_domain["Time"].set("Integrator","DGM::TimeInt").asString();
  if (integrator == "DTK::TimeIntegrate") {
    comm->cout() << "Domain is using DTK::TimeIntegrate" << endl;
    const string method = json_domain["Time"].set("Method","RK4").asString();
    if (method=="RK4")
      timeIntegrate.reset(new
          DTK::RungeKutta<Scalar,Ordinal,vField,Domain>(this));
    else
      throw DGM::exception("Unsupported time integrator method "+method);
  } else if (integrator == "DGM::TimeInt") {
  } else {
    throw DGM::exception("Unsupported time integrator "+integrator);
  }
  const int verb = json_domain["Time"].get("Verbosity",0).asInt();
  if (verb) {
    Json::StyledWriter writer;
    string output = writer.write(json_domain["Time"]);
    comm->cout() << "Domain Time parameters:\n" << output;
  }
}

void Adv_Diff_Adjoint::zero_all_fields() {
  Domain::zero_all_fields();
  Uv.zero();
  Ustate.zero();
  Uobj.zero();
}

void Adv_Diff_Adjoint::time_derivative( vField &Us, vField &Uf ) {
  if (fv) {  // finite volume reconstruction
    Us.make_constant();
    //Us.tecplot("constant.adj.dat","Constant");
    linear_reconstruction( Us, Uv, Uf );
    //Us.tecplot("linear.adj.dat","Linear");
  }
  if (cfield)
    convection( Us, Uf );
  else
    constant_convection( Us, Uf );
  diffusion( Us, Uv, Uf );
  add_source(Us, Uf);
  project( Uf );
  if (fv) {  // finite volume reconstruction
    Uf.make_constant();
    Us.make_constant();
  }
}

void Adv_Diff_Adjoint::set_end_condition() {
  Adjoint::set_end_condition();
  if (fv!=0) U.make_constant();
  store(U, npredict, 0);
}

void Adv_Diff_Adjoint::set_end_condition(const dVector &X,
                                         const Scalar t_,
                                         const Ordinal step_) {
  Adjoint::set_end_condition(X, t_, step_);
  if (fv!=0) U.make_constant();
  store(U, npredict, 0);
}

void Adv_Diff_Adjoint::prestep( vField &F, const Ordinal istep,
                                const Ordinal sstep, const Scalar time) {
  state->load_field( Ustate, istep, sstep);
  control->set_data( istep, sstep );
  objective->set_data( Ustate, istep, sstep );
  if (time_int->is_explicit()) {
    store(F, istep, sstep);
    computeGrad( F, Ustate, istep, sstep );
  }
}

void Adv_Diff_Adjoint::poststep( vField &F, const Ordinal istep,
                                 const Ordinal sstep, const Scalar time) {
  if (time_int->is_implicit()) {
    store(F,istep,sstep);
    computeGrad( F, Ustate, istep, sstep );
  }
}

void Adv_Diff_Adjoint::convection( vField &Uf, vField &Ff ) {
  Uf.fill_sides();                        // put adjoint soln on the sides
  Uf.share_sides();
  enforce_bc(Uf);                         // update adjoint bc side values
  convective_flux( Uc, Uf, Ff );          // compute surface fluxes on sides
  if (nsd == 1) {
    for (LocalSize e=0; e<Uf[0]->ne; e++) {
      Element *U = Uf[0]->el[e];          // adjoint
      Element *F = Ff[0]->el[e];          // flux
      Element *Cx = Uc[0]->el[e];         // convective velocity
      U->gradient( U->u, F->u );          // compute gradient of adjoint
      dvmul( Cx->u, F->u );
      U->lift( F, F->u );                 // add side fluxes to interior
    }
  } else if (nsd == 2) {
    for (LocalSize e=0; e<Uf[0]->ne; e++) {
      Element *U = Uf[0]->el[e];          // adjoint
      Element *F = Ff[0]->el[e];          // flux
      Element *Cx = Uc[0]->el[e];         // convective velocity
      Element *Cy = Uc[1]->el[e];         // convective velocity
      dVector uy(wk1,U->qtot);
      U->gradient( U->u, F->u, uy );      // compute F->u=ux, uy
      dvmul( Cx->u, F->u );
      dvmul( Cy->u, uy );
      dvadd( uy, F->u );                  // F->u = cx ux + cy uy
      U->lift( F, F->u );                 // add side fluxes to interior
    }
  } else if (nsd == 3) {
    for (LocalSize e=0; e<Uf[0]->ne; e++) {
      Element *U = Uf[0]->el[e];          // adjoint
      Element *F = Ff[0]->el[e];          // flux
      Element *Cx = Uc[0]->el[e];         // convective velocity
      Element *Cy = Uc[1]->el[e];         // convective velocity
      Element *Cz = Uc[2]->el[e];         // convective velocity
      dVector uy(wk1,U->qtot);
      dVector uz(wk2,U->qtot);
      U->gradient( U->u, F->u, uy, uz );
      dvmul( Cx->u, F->u );
      dvmul( Cy->u, uy );
      dvmul( Cz->u, uz );
      dvadd( uy, F->u );
      dvadd( uz, F->u );                  // F->u = cx ux + cy uy + cz uz
      U->lift( F, F->u );                 // add side fluxes to interior
    }
  } else {
    comm->error("Adv_Diff_Adjoint:convection -- illegal nsd");
  }
}

void Adv_Diff_Adjoint::constant_convection( vField &Uf, vField &Ff ) {
  Uf.fill_sides();                        // put adjoint soln on the sides
  Uf.share_sides();
  enforce_bc(Uf);                         // update adjoint bc side values
  convective_flux( Uf, Ff );              // compute surface fluxes on sides
  if (nsd == 1) {
    for (LocalSize e=0; e<Uf[0]->ne; e++) {
      Element *U = Uf[0]->el[e];          // adjoint
      Element *F = Ff[0]->el[e];          // flux
      U->gradient( U->u, F->u );          // compute gradient of adjoint
      scale( cx, F->u );
      U->lift( F, F->u );                 // add side fluxes to interior
    }
  } else if (nsd == 2) {
    for (LocalSize e=0; e<Uf[0]->ne; e++) {
      Element *U = Uf[0]->el[e];          // adjoint
      Element *F = Ff[0]->el[e];          // flux
      dVector uy(wk1,U->qtot);
      U->gradient( U->u, F->u, uy );      // compute F->u=ux, uy
      scale( cx, F->u );
      daxpy( cy, uy, F->u );              // F->u = cx ux + cy uy
      U->lift( F, F->u );                 // add side fluxes to interior
    }
  } else if (nsd == 3) {
    for (LocalSize e=0; e<Uf[0]->ne; e++) {
      Element *U = Uf[0]->el[e];          // adjoint
      Element *F = Ff[0]->el[e];          // flux
      dVector uy(wk1,U->qtot);
      dVector uz(wk2,U->qtot);
      U->gradient( U->u, F->u, uy, uz );
      scale( cx, F->u );
      daxpy( cy, uy, F->u );
      daxpy( cz, uz, F->u );              // F->u = cx ux + cy uy + cz uz
      U->lift( F, F->u );                 // add side fluxes to interior
    }
  } else {
    comm->error("Adv_Diff_Adjoint:constant_convection -- illegal nsd");
  }
}

void Adv_Diff_Adjoint::convective_flux(vField &Uf, vField &Ff) {
  Scalar un, nx, ny, nz;
  Side *Sfl, *Sfr, *Sul, *Sur;
  LocalSize qtot;
#ifdef REO_USE_GETSIDEMAPS
  iVector mapl, mapr;
#endif
  for (LocalSize e=0; e<Uf[0]->ne; e++) {
    Element *U = Uf[0]->el[e];
    Element *F = Ff[0]->el[e];
    for (LocalSize i=0; i<U->nSides(); i++) {
      if (U->side[i]->master()) {
        Sfl = F->side[i];
        Sfr = F->side[i]->link;
        Sul = U->side[i];
        Sur = U->side[i]->link;
        qtot = Sul->qtot();
#ifdef REO_USE_GETSIDEMAPS
        get_side_maps( Sul, Sur, mapl, mapr );
#endif
        for (LocalSize q=0; q<qtot; q++) {
#ifdef REO_USE_GETSIDEMAPS
          const Ordinal ql = mapl[q];
          const Ordinal qr = mapr[q];
#else
          const Ordinal ql = U->sideMap(Sul,q);
          const Ordinal qr = U->sideMap(Sur,q);
#endif
          nx = Sul->nx(ql);
          ny = Sul->ny(ql);
          nz = Sul->nz(ql);
          // switch the sign for the adjoint
          if ( (un = (cx*nx + cy*ny + cz*nz)) > 0 ) {
            Sfl->u[ql] =  un * Sur->u[qr];
            Sfr->u[qr] = -un * Sur->u[qr];
          } else {
            Sfl->u[ql] =  un * Sul->u[ql];
            Sfr->u[qr] = -un * Sul->u[ql];
          }
          // put interior flux on the U field sides
          Sul->u[ql] *=  un;
          Sur->u[qr] *= -un;
        }
      }
    }
  }
}

Scalar Adv_Diff_Adjoint::dfabs( const Scalar x ) {
  if (x > 0.0)
    return 1.0;
  else if (x < 0.0)
    return -1.0;
  else
    return 0.0;
}

// adoint Lax-Friedrichs flux
void Adv_Diff_Adjoint::convective_flux(const vField &, vField &Uf, vField &Ff) {
  // cout << "Adv_Diff_Adjoint::convective_flux(...)" << endl;
  Scalar sl, cxl, cyl, cl;
  Scalar sr, cxr, cyr, cr;
  Side *Sfl, *Sfr, *Sul, *Sur;
#ifdef REO_USE_GETSIDEMAPS
  iVector mapl, mapr;
#endif
  for (LocalSize e=0; e<Uf[0]->ne; e++) {
    Element *U = Uf[0]->el[e];
    Element *F = Ff[0]->el[e];
    for (LocalSize i=0; i<U->nSides(); i++) {
      if (U->side[i]->master()) {
        Sfl = F->side[i];
        Sfr = F->side[i]->link;
        Sul = U->side[i];
        Sur = U->side[i]->link;
        const LocalSize qtot = Sul->qtot();
#ifdef REO_USE_GETSIDEMAPS
        get_side_maps( Sul, Sur, mapl, mapr );
#endif
        for (LocalSize q=0; q<qtot; q++) {
#ifdef REO_USE_GETSIDEMAPS
          const Ordinal ql = mapl[q];
          const Ordinal qr = mapr[q];
#else
          const Ordinal ql = U->sideMap(Sul,q);
          const Ordinal qr = U->sideMap(Sur,q);
#endif
          const Scalar nx = Sul->nx(ql);
          const Scalar ny = Sul->ny(ql);
          //const Scalar nz = Sul->nz(ql);

          sl  = Sul->u[ql];
          cxl = Uc[0]->el[e]->side[i]->u[ql];
          cyl = (nsd>1 ? Uc[1]->el[e]->side[i]->u[ql] : 0.0 );
          //czl = (nsd>2 ? Uc[2]->el[e]->side[i]->u[ql] : 0.0 );
          cl  = cxl*nx + cyl*ny; // + czl*nz;
          //const Scalar s_loc = cl*sl;

          sr  = Sur->u[qr];
          cxr = Uc[0]->el[e]->side[i]->link->u[qr];
          cyr = (nsd>1 ? Uc[1]->el[e]->side[i]->link->u[qr] : 0.0 );
          //czr = (nsd>2 ? Uc[2]->el[e]->side[i]->link->u[qr] : 0.0 );
          cr = cxr*nx + cyr*ny; // + czr*nz;
          //const Scalar s_adj = cl*sr;

          const Scalar lmax = max(fabs(cl),fabs(cr));

          // Note that the adjoint flux is not conservative!
          const Scalar lf_flux_l = -0.5*( cl*sl - cl*sr + lmax*(sl - sr) );
          const Scalar lf_flux_r = -0.5*( cr*sl - cr*sr + lmax*(sr - sl) );

          // put numerical flux on the F field sides
          Sfl->u[ql] =  lf_flux_l;
          Sfr->u[qr] =  lf_flux_r;

          // put interior flux on the U field sides
          Sul->u[ql] =  0.0;
          Sur->u[qr] =  0.0;
#if 0
          if (e==60 && i==2)
            cout<<"Element: "<<e<<", side: "<<i<<", (nx,ny)= ("
                <<nx<<","<<ny<<"), (fl,fr)= ("<<lf_flux_l
                <<","<<lf_flux_r<<"), (cl,cr)= ("<<cl<<","<<cr<<")"<<endl;
#endif
        }
      }
    }
  }
}

/// Linear reconstruction is used for finite volume methods
void Adv_Diff_Adjoint::linear_reconstruction( vField &Uf, vField &Ff,
                                              vField &Rf ) {
  LocalSize nsd = Uf[0]->nsd();
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
    } else if (nsd==1) {
      U->gradient(U->u, ux, ux);
      U->lift( F, ux, 'x' );
#ifdef REO_PROJECT_DIFF_FLUX
      U->project(ux);
#endif
    } else {
      comm->error("Adv_Diff_Adjoint:reconstruction -- illegal value of nsd");
    }
  }
}

///  Compute the Bassi and Rebay diffusive flux
void Adv_Diff_Adjoint::diffusion( vField &Uf, vField &Ff, vField &Rf ) {
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
      U->gradient(ux, F->u, 'x');             // ux = u_,{xx}
    } else {
      comm->error("Adv_Diff:diffusion -- illegal value of nsd");
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
    U->lift( F, F->u );                       // add side fluxes to interior
  }
  // switch sign for adjoint
  add( Ff, Rf );                              // add in viscous contribution
}

void Adv_Diff_Adjoint::interior_penalty_flux(const vField &Up,
                                             const vField &Us,
                                             vField &Uf, const Scalar sigma) {
#ifdef REO_USE_GETSIDEMAPS
  iVector mapl, mapr;
#endif
  for (vField::size_type n=0; n<Us.size(); n++) {
    for (LocalSize e=0; e<Us[n]->ne; e++) {
      const Element *P = Up[n]->el[e];
      const Element *S = Us[n]->el[e];
      Element *F = Uf[n]->el[e];
      for (LocalSize i=0; i<S->nSides(); i++) {
        if (S->side[i]->master()) {
#ifdef REO_USE_GETSIDEMAPS
          get_side_maps( S->side[i], S->side[i]->link, mapl, mapr );
#endif
          const LocalSize qtot = S->side[i]->qtot();
          for (LocalSize q=0; q<qtot; q++) {
#ifdef REO_USE_GETSIDEMAPS
            const Ordinal ql = mapl[q];
            const Ordinal qr = mapr[q];
#else
            const Ordinal ql = F->sideMap(S->side[i],q);
            const Ordinal qr = F->sideMap(S->side[i]->link,q);
#endif
            F->side[i]->u[ql] = pt5 *(S->side[i]->u[ql] -
                                      S->side[i]->link->u[qr]) +
              sigma*(P->side[i]->link->u[qr] -
                     P->side[i]->u[ql]);
            F->side[i]->link->u[ql] = -F->side[i]->u[ql];
          }
        }
      }
    }
  }
}


void Adv_Diff_Adjoint::enforce_boundary_penalty(const vField &S, vField &F,
                                                const Scalar sigma) {
  // cout << "Adv_Diff::enforce_boundary_penalty()" << endl;
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
void Adv_Diff_Adjoint::setup_BCdb( ) {
  BC_db = state->BC_db;
}


void Adv_Diff_Adjoint::enforce_bc(vField &F) {
  for (BC::db_citr i=BC_db.begin(); i!= BC_db.end(); ++i){
    i->second->adjoint_apply( t, Ustate, F );
  }
}


void Adv_Diff_Adjoint::enforce_flux_bc(vField &F) {
  for (BC::db_citr i=BC_db.begin(); i!= BC_db.end(); ++i)
    i->second->adjoint_apply_flux( t, Ustate, F);
}

//===========================================================================
//                        Source database management
//===========================================================================

/// Load up the available Source types
void Adv_Diff_Adjoint::setup_Sourcedb( ) {
  // cout << "Adv_Diff_Adjoint::setup_Sourcedb" << endl;
  Source_db = state->Source_db;
  string fname = root+".obj";
  ifstream in(fname.c_str());
  if (in) read_Sourcedb( in );   // database of active Source types
}

/// make the Adjoint Source(s)
Source::Ptr Adv_Diff_Adjoint::make_Source( ifstream &in, string &tag ) {
  // cout << "Adv_Diff_Adjoint::make_Source" << endl;
  string code;
  Source::Ptr p;
  if (!(in >> code)) return p;
  while (code[0]=='#') {  // eat comment lines
    string buffer;
    getline(in,buffer);
    if (!(in >> code)) return p;
  }
  if (lowerCase(code) == "tracking") {
    if (!(in >> tag))
      comm->error("Adv_Diff_Adjoint::Cannot read Tracking tag");
    p.reset( new Tracking(tag,in,U) );
  } else if (lowerCase(code) == "terminaltracking") {
    if (!(in >> tag))
      comm->error("Adv_Diff_Adjoint::Cannot read TerminalTracking tag");
    p.reset( new TerminalTracking(tag,in,U,npredict) );
  } else if (lowerCase(code) == "steadytracking") {
    if (!(in >> tag))
      comm->error("Adv_Diff_Adjoint::Cannot read SteadyTracking tag");
    p.reset( new SteadyTracking(tag,in,U,npredict) );
  } else if (lowerCase(code) == "steadyerror") {
    if (!(in >> tag))
      comm->error("Adv_Diff_Adjoint::Cannot read SteadyError tag");
    p.reset( new SteadyError(tag,in,state,U,npredict) );
  } else if (lowerCase(code) == "unsteadyerror") {
    if (!(in >> tag))
      comm->error("Adv_Diff_Adjoint::Cannot read UnsteadyError tag");
    p.reset( new UnsteadyError(tag,in,state,U,npredict) );
  } else if (lowerCase(code) == "unsteadytracking") {
    if (!(in >> tag))
      comm->error("Adv_Diff_Adjoint::Cannot read TerminalTracking tag");
    p.reset( new UnsteadyTracking(tag,in,U,state) );
  } else if (lowerCase(code) == "function") {
    if (!(in >> tag))
      comm->error("Adv_Diff_Adjoint::Cannot read FuncSource tag");
    p.reset( new AdjFuncSource(tag,in,1) );
  } else {
    comm->error("Adv_Diff_Adjoint::make_Source() Illegal Source type");
  }
  return p;
}

/// Add the Source terms
void Adv_Diff_Adjoint::add_source(const vField &Us, vField &Ur) {
  // cout << "Adv_Diff_Adjoint::add_source(vField &)" << endl;
  for (Source::db_citr i=Source_db.begin(); i!= Source_db.end(); ++i) {
    // cout << "Adding source: " << i->first << endl;
    i->second->adjoint_apply( t, Ustate, Us, Ur );
  }
}

void Adv_Diff_Adjoint::computeGrad(vField& Ua, vField& Us, Ordinal istep,
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
      U->project(ux);
      U->lift( F, uy, 'y' );
      U->project(uy);
      U->lift( F, uz, 'z' );
      U->project(uz);
      scale( mu, ux );
      scale( mu, uy );
      scale( mu, uz );
      U->fill_sides( ux, uy, uz );
    } else if (nsd==2) {
      dVector uy(wk2,qtot);
      dVector uyh(uy,nModes);
      U->gradient(U->u, ux, uy);
      U->lift( F, ux, 'x' );
      U->project(ux);
      U->lift( F, uy, 'y' );
      U->project(uy);
      scale( mu, ux );
      scale( mu, uy );
      U->fill_sides( ux, uy );
    } else if (nsd==1) {
      U->gradient( U->u, ux, 'x');
      U->lift( F, ux, 'x' );
      U->project(ux);
      scale( mu, ux );
      U->fill_sides( ux, ux );
    } else {
      comm->error("Adv_Diff_Adjoint:computeGrad -- illegal value of nsd");
    }
    Ua[0]->bc[n]->B->u = Ua[0]->bc[n]->S->u;
    scale( -1.0, Ua[0]->bc[n]->B->u );        // put (\hat F^v_n) in B
    U->fill_sides( U->u );                    // put adjoint in S
  }
  // use the adjoint field and sides to build gradient
  control->gradient( Us, Ua, g_control, istep, sstep );
}

/// set the solution from a file
void Adv_Diff_Adjoint::set_ic(vField &F, string ext) {
  t = 0.0; step = 0;
  string fname = root+ext;
  ifstream in(fname.c_str());
  if (!in) {
    F.zero(); // default to zero initial condition
    return;
  }
  string buffer, code;
  getline(in,buffer);
  if (!(in>>code)) comm->error("Cannot read IC code");
  getline(in,buffer);
  if (lowerCase(code) == "given") {
    F.fill(in);
  } else if (lowerCase(code) == "restart") {
    string rstfile;
    if (!(in>>rstfile)) {
      stringstream msg("Cannot read restart file name from ");
      msg << fname;
      comm->error(msg);
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
