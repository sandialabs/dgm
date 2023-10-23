/*=============================================================================
  Module:     Euler3d Module

  Contact:    S. Scott Collis
              sscoll@sandia.gov

  Copyright:  (c) 2003 Rice University
              (c) 2008 Sandia National Laboratories
=============================================================================*/

/** \file Euler3d.cpp
    \brief Implementation of the 3d Euler equations
    \author Scott Collis
*/

// system includes
#include <ctime>

// local includes
#include "Reo.hpp"
#include "Euler3d.hpp"
#include "EulerIC.hpp"

namespace Reo {

using namespace DGM;

// Print out detailed flux information
// #define DGM_VERBOSE_FLUX

// static definitions for initial conditions
#ifdef DGM_USE_BOOST_RANDOM
TurbulentChannel::random_number_generator TurbulentChannel::generator(42u);
TurbulentChannel::random_distribution
  TurbulentChannel::urand(TurbulentChannel::generator);
#endif

#if defined(DGM_USE_BOOST_RANDOM)
// static definitions for initial conditions
IsotropicTurbulence::random_number_generator
  IsotropicTurbulence::generator(42u);
IsotropicTurbulence::random_distribution
  IsotropicTurbulence::urand(IsotropicTurbulence::generator);
#endif

/// Constructor
Euler3d::Euler3d( DGM::ArgList &args, const DGM::Comm::Ptr comm_) :
Domain(args,comm_), S(comm_), St(comm_) {

  const int verb(comm->verbosity());
  Stopwatch cpu; cpu.start();
  if (verb) comm->cout() << "Building Euler3d domain..." << endl;

  Ordinal p, q;
  p = params["p"];                       // polynomial order
  if ( !(q=params["q"]) ) q = p + 2;     // number of quadrature points
  nsd = params["nsd"];                   // number of space dimensions

  params["auxtec"] = 0;                  // Compute derivative quantities
  params["plot3d"]  = 0;                 // Generate plot3d files
  params["plot3d_x"]  = 1;               // plot3d grid file
  params["plot3d_q"]  = 1;               // plot3d mesh file
  params["plane_avg"]  = 0;              // planar average

  // read arguments (overrides defaults and input file)
  parse_args( args );

  gamma = params["gamma"];               // ratio of specific heats

  if (!stats)
    stats = new DGM::Statistics(root+".sts");
  else
    throw DGM::exception("DGM::Statistics was already setup?");

  if ( Channel::exists(root) ) {
    channel.reset( new Channel(root, stats, comm) );
  }

  vector<string> field_names;
  field_names.push_back("r");

  // build a Field of Elements and Sides
  if (params["imesh"]) {
    Mesh mesh(params);
    U.push_back( new Field(p, q, mesh, root, field_names[0],
                           Field::FULL, comm ) );
    partition = U[0]->partition;
  } else if (params["bmesh"]) {
    U.push_back( new Field(p, q, root, field_names[0], partition, 1,
                           Reo::NumEqntype, p2i(EULER3D), comm ) );
  } else {
    U.push_back( new Field(p, q, root, field_names[0], partition, comm ) );
  }

  // set some additional domain parameters
  ne = U[0]->ne;
  nsd = U[0]->nsd();

#ifdef REO_USE_GETSIDEMAPS
  setup_side_maps();
#endif

  if (nsd == 1) {
    comm->error("Euler3d:  nsd must be 3");
  } else if (nsd == 2) {
    comm->error("Euler3d:  nsd must be 3");
  } else if (nsd == 3) {
    Nfields = 5;  // is equal to NFIELDS in Euler3d.hpp
    field_names.push_back("ru");
    field_names.push_back("rv");
    field_names.push_back("rw");
    field_names.push_back("rE");
  } else {
    stringstream msg;
    msg<< "Illegal value for nsd = " << nsd << " in Euler3d::Euler3d"<< endl;
    comm->error(msg.str());
  }

  // build the rest of the vector field
  for (vField::size_type i=1; i<Nfields; i++)
    U.push_back( new Field( U[0], root, field_names[i] ) );

  // make auxiliary Fields using copy constructor
  for (vField::size_type i=0; i<Nfields; i++) {
    Ut.push_back( new Field( U[0], root, field_names[i]) );
  }

  // allocate workspace
  wk1.resize(7*max(Lmax(),Qmax()));

  // make sure that storage is initialized
  zero_all_fields();

  response = Response::factory(U, this);

  setup_BCdb();

  setup_Sourcedb();

  set_TimeInt();
}

/// Parse parameters from the argument list
void Euler3d::parse_args( DGM::ArgList &args ) {
  string name, value;
  list< DGM::ArgList::iterator > li;
  for ( DGM::ArgList::iterator a = args.begin(); a != args.end(); a++ ) {
    if ( (*a)[0] == '-' ) {
      name = *a;
      if (name == "-nox") {
        li.push_back(a);
        params["plot3d_x"] = 0;
      } else if (name == "-noq") {
        li.push_back(a);
        params["plot3d_q"] = 0;
      } else if (name == "-aux") {
        li.push_back(a);
        params["auxtec"] = 1;
      } else if (name == "-pavg") {
        li.push_back(a);
        params["plane_avg"] = 1;
      } else if (name == "-help") {
        params["showUsage"] = 1;
        showUsage();
      }
    }
  }
  // remove tagged arguments
  for ( list< DGM::ArgList::iterator >::iterator a=li.begin();
      a!=li.end(); a++) args.erase(*a);
}

/// Show command line arguments
void Euler3d::showUsage() {
  comm->cout()
    << "Euler3d Class Options \n"
    << "----------------------------------------------------------------\n"
    << "-nox     " << '\t' << "No grid file                             \n"
    << "-noq     " << '\t' << "No solution file                         \n"
    << "-aux     " << '\t' << "Auxiliary Tecplot file                    \n"
    << "-pavg    " << '\t' << "Planar average                           \n"
    << "----------------------------------------------------------------\n";
}

/// Compute statistices including mean and rms values
void Euler3d::compute_stats(const string &rst) {
  cout << "Euler3d::compute_stats("<<rst<<")" << endl;
  string fname, name(rst), caption;

  static FILE* out = NULL;
  static FILE* wall = NULL;

  if ( !out  ) out = fopen("time.dat","w");
  if ( !wall ) wall = fopen("wall.dat","w");

  read( rst, Ut );

  // compute mean

#ifdef VELOCITY
  // switch to velocities
  for (LocalSize e=0; e<Ut[0]->ne; e++) {
    dvdiv( Ut[1]->el[e]->u, Ut[0]->el[e]->u, Ut[1]->el[e]->u );
    dvdiv( Ut[2]->el[e]->u, Ut[0]->el[e]->u, Ut[2]->el[e]->u );
    dvdiv( Ut[3]->el[e]->u, Ut[0]->el[e]->u, Ut[3]->el[e]->u );
  }
#endif

  if (params["plane_avg"]) {
    if (channel.get())
      channel->plane_average( Ut );
    else
      Ut.plane_average();
  }
  if (channel.get()) {
    // time-history of wall values
    if (wall) {
      fprintf(out, "%18.11e %18.11e %18.11e %18.11e %18.11e %18.11e\n", t,
              Ut[0]->el[0]->u[0], Ut[1]->el[0]->u[0], Ut[2]->el[0]->u[0],
              Ut[3]->el[0]->u[0], Ut[4]->el[0]->u[0]);
      // fflush(out);
    }
  }

  add( Ut, U );

  // compute RMS

  if (S.size()==0) {
    // make an auxiliary vField
    cout << "Euler3d::compute_stats is making temporary vField" << endl;
    for (vField::size_type i=0; i<Nfields; i++) {
      S.push_back( new Field( U[i], root, U[i]->name ) );
      St.push_back( new Field( U[i], root, U[i]->name ) );
    }
    S.zero();
    St.zero();
  }

  read( rst, St );

  for (vField::size_type n=0; n<Nfields; ++n) {
    for (LocalSize e=0; e<St[0]->ne; e++) {
      dvsub( St[n]->el[e]->u, Ut[n]->el[e]->u, St[n]->el[e]->u );
      dvmul( St[n]->el[e]->u, St[n]->el[e]->u );
    }
  }

  // Note that due to aliasing errors, it is possible for the result of
  // plane_averge to no longer be positive.  This can be avoided by computing
  // rms stats with more polynomial modes
  if (params["plane_avg"]) {
    if (channel.get())
      channel->plane_average( St );
    else
      St.plane_average();
  }
  add( St, S );

  if (channel.get()) {
    // compute average massflow rate, TKE, and bulk velocity
    Scalar mdot = 0, vol = 0, rhobar = 0, q2 = 0, Ubar = 0;
    dVector lvol(Ut[1]->ne);
    for (LocalSize k=0; k<Ut[1]->ne; k++) {
      rhobar += Ut[0]->el[k]->integrate( &lvol[k] );
      mdot   += Ut[1]->el[k]->integrate( &lvol[k] );
      q2     += St[1]->el[k]->integrate( &lvol[k] );
      q2     += St[2]->el[k]->integrate( &lvol[k] );
      q2     += St[3]->el[k]->integrate( &lvol[k] );
      vol    += lvol[k];
    }
    mdot /= vol;
    rhobar /= vol;
    Ubar = mdot/rhobar;
    q2 = q2/vol/rhobar/rhobar;

    // output time-history statistics
    if (out) {
      fprintf(out,"%18.11e %18.11e %18.11e %18.11e %18.11e %18.11e ",
              t, Ut[0]->el[0]->u[0], Ut[1]->el[0]->u[0], Ut[2]->el[0]->u[0],
              Ut[3]->el[0]->u[0], Ut[4]->el[0]->u[0] );
      fprintf(out,"%18.11e %18.11e %18.11e %18.11e\n", mdot, rhobar, Ubar, q2);
      fflush(out);
    }
  } else {
    Scalar vol = 0, rhobar = 0, q2 = 0;
    dVector lvol(Ut[1]->ne);
    for (LocalSize k=0; k<Ut[1]->ne; k++) {
      rhobar += Ut[0]->el[k]->integrate( &lvol[k] );
      q2     += U[1]->el[k]->integrate( &lvol[k] );
      q2     += U[2]->el[k]->integrate( &lvol[k] );
      q2     += U[3]->el[k]->integrate( &lvol[k] );
      vol    += lvol[k];
    }
    q2 = q2/vol/rhobar/rhobar;

    // output time-history statistics
    if (out) {
      fprintf(out,"%18.11e %18.11e %18.11e\n", t, rhobar, q2);
      fflush(out);
    }
  }
}

/// Generate tecplot and/or plot3d files for statistics
/** Currently includes the mean and RMS statistics. */
void Euler3d::plot_stats(const int samples) {
  cout << "Euler3d::plot_stats()" << endl;
  string fname, name(root), caption;
  char buf[80];

  // Mean

  scale( one/(Scalar)samples, U );
  sprintf(buf,"%s.dat",name.c_str()); fname = buf;
  sprintf(buf,"State variables at:  t =%12.4e, step = %lld",t,(long long)step);
  caption = buf;
  if (params["tecplot"])
    if (comm->Master()) U.tecplot(fname,caption);
  if (params["paraview"]) U.paraview(name,caption);
  if (params["plot3d"]) {
    if (params["plot3d_x"]) {
      sprintf(buf,"%s.xyz",name.c_str()); fname = buf;
      if (comm->Master()) U.plot3d_x(fname);
    }
    if (params["plot3d_q"]) {
      sprintf(buf,"%s.q",name.c_str()); fname = buf;
      if (comm->Master()) U.plot3d_q(fname);
    }
  }
  if (params["auxtec"]) {
    compute_vorticity();   // puts vorticity in Ut
    sprintf(buf,"%s.aux.dat",name.c_str()); fname = buf;
    sprintf(buf,"Auxiliary variables at:  t =%11.4e, step   %lld",t,
            (long long)step);
    caption = buf;
    if (comm->Master()) Ut.tecplot(fname,caption);
  }

  // Planar average

  if (channel.get()) {
    string f_name = "mean.dat";
    FILE *os = fopen(f_name.c_str(), "w");;
    const Ordinal Nx(channel->Nx);
    const Ordinal Ny(channel->Ny);
    const Ordinal Nz(channel->Nz);
    cout << "WARNING: Euler3d::plot_stats() is using a "
         <<Nx<<"x"<<Ny<<"x"<<Nz<<" mesh\n";
    for(Ordinal i=0;i<Nz;i++){
      Ordinal els=i*Nx*Ny;
      for(Ordinal j=0;j<U[0]->el[els]->qc;j++){
        for(Ordinal k=0;k<U[0]->el[els]->qb;k++){
          for(Ordinal l=0;l<U[0]->el[els]->qa;l++){
            Ordinal wns=j + k*U[0]->el[els]->qc +
              l*U[0]->el[els]->qc*U[0]->el[els]->qb;
            Scalar irho = 1.0/U[0]->el[els]->u[wns];
            fprintf(os,"%18.11e %18.11e %18.11e %18.11e %18.11e %18.11e\n",
                    U[0]->el[els]->C->z[wns], U[0]->el[els]->u[wns],
                    U[1]->el[els]->u[wns]*irho, U[2]->el[els]->u[wns]*irho,
                    U[3]->el[els]->u[wns]*irho, U[4]->el[els]->u[wns]*irho);
          }
        }
      }
    }
    fclose(os);
  }

  // RMS

  scale( one/(Scalar)samples, S );
  for (vField::size_type n=0; n<Nfields; ++n)
    for (LocalSize e=0; e<S[n]->ne; e++)
      dvsqrt(S[n]->el[e]->u, S[n]->el[e]->u);

  // Project the nonlinear stats to polynomial space.
  project(S);

  // For Favre average replace <rho'^2> with \bar rho
  for (LocalSize e=0; e<S[0]->ne; e++)
    S[0]->el[e]->u = U[0]->el[e]->u;
  if (params["plot3d"]) {
    if (params["plot3d_q"]) {
      sprintf(buf,"%s.r",name.c_str()); fname = buf;
      if (comm->Master()) S.plot3d_q(fname);
    }
  }
  if (channel.get()) {
    string f_name = "rms.dat";
    FILE *os = fopen(f_name.c_str(), "w");
    const Ordinal Nx(channel->Nx); // NX;
    const Ordinal Ny(channel->Ny); // NY;
    const Ordinal Nz(channel->Nz); // NZ;
    for(Ordinal i=0;i<Nz;i++){
      Ordinal els=i*Nx*Ny;
      for(Ordinal j=0;j<U[0]->el[els]->qc;j++){
        for(Ordinal k=0;k<U[0]->el[els]->qb;k++){
          for(Ordinal l=0;l<U[0]->el[els]->qa;l++){
            Ordinal wns=j + k*U[0]->el[els]->qc +
              l*U[0]->el[els]->qc*U[0]->el[els]->qb;
            Scalar irho = 1.0/S[0]->el[els]->u[wns];
            fprintf(os,"%18.11e %18.11e %18.11e %18.11e %18.11e %18.11e\n",
                    S[0]->el[els]->C->z[wns], S[0]->el[els]->u[wns],
                    S[1]->el[els]->u[wns]*irho,S[2]->el[els]->u[wns]*irho,
                    S[3]->el[els]->u[wns]*irho,S[4]->el[els]->u[wns]*irho);
          }
        }
      }
    }
    fclose(os);
  }
}

/// Generate plot output
int Euler3d::plot(const string &rst) {
  string fname, name(rst), caption;
  char buf[80];
  read( rst, U );
  if (params["plane_avg"]) {
    if (channel.get())
      channel->plane_average( U );
    else
      U.plane_average();
  }
  size_t loc = name.find(".rst");
  if ( loc != string::npos ) name.erase(loc);  // erase extension
  sprintf(buf,"%s.dat",name.c_str()); fname = buf;
  sprintf(buf,"State variables at:  t =%12.4e, step = %lld",t,(long long)step);
  caption = buf;
  if (params["tecplot"])
    if (comm->Master()) U.tecplot(fname,caption);
  if (params["paraview"]) U.paraview(name,caption);
  if (params["plot3d"]) {
    if (params["plot3d_x"]) {
      sprintf(buf,"%s.xyz",name.c_str()); fname = buf;
      U.plot3d_x(fname);
    }
    if (params["plot3d_q"]) {
      sprintf(buf,"%s.q",name.c_str()); fname = buf;
      U.plot3d_q(fname);
    }
  }
  if (params["auxtec"]) {
    compute_vorticity();   // puts vorticity in Ut
    sprintf(buf,"%s.aux.dat",name.c_str()); fname = buf;
    sprintf(buf,"Auxiliary variables at:  t =%11.4e, step   %lld",t,
            (long long)step);
    caption = buf;
    if (comm->Master()) Ut.tecplot(fname,caption);
  }
  return 0;
}

/// Evaluate the time_derivative (i.e. the right-hand-side)
void Euler3d::time_derivative( vField &Us, vField &Uf ) {
  convection( Us, Uf );
  project( Uf );
}

/// Set the time step based on a CFL-type condition
/** \todo Need to implement Euler3d::set_time_step() */
Scalar Euler3d::set_time_step(vField &U) {
  Scalar cfl = dt;
  return cfl;
}

/// Evalutate the convection terms in the RHS
void Euler3d::convection( vField &Us, vField &Uf ) {
  Element *U[NFIELDS], *F[NFIELDS];
  dVector u, v, w, p, d, d1;
  dVector r, ru, rv, rw, rE;
  const Scalar gm1 = gamma-one;
  const Scalar mpt5gm1 = -pt5*gm1;

  Us.fill_sides();
  Euler3d::enforce_bc(Us);
  Us.begin_share_sides();

  // Add the interior contribution
  for (LocalSize e=0; e<Us[0]->ne; e++) {
    U[0] = Us[0]->el[e];  // local version of the state
    U[1] = Us[1]->el[e];
    U[2] = Us[2]->el[e];
    U[3] = Us[3]->el[e];
    U[4] = Us[4]->el[e];

    F[0] = Uf[0]->el[e];  // local version of the flux
    F[1] = Uf[1]->el[e];
    F[2] = Uf[2]->el[e];
    F[3] = Uf[3]->el[e];
    F[4] = Uf[4]->el[e];

    const Ordinal qtot = U[0]->qtot;

    r.alias (U[0]->u);  // rho
    ru.alias(U[1]->u);  // rho u
    rv.alias(U[2]->u);  // rho v
    rw.alias(U[3]->u);  // rho w
    rE.alias (U[4]->u); // total Energy density

    u.alias(wk1,0,qtot);
    v.alias(wk1,qtot,qtot);
    w.alias(wk1,2*qtot,qtot);
    p.alias(wk1,3*qtot,qtot);
    d.alias(wk1,4*qtot,qtot);
    d1.alias(wk1,5*qtot,qtot);

    dvdiv(ru, r, u);  // compute u
    dvdiv(rv, r, v);  // compute v
    dvdiv(rw, r, w);  // compute w

    // p = (gamma-1.0)*(rE-0.5*(r*u*u + r*v*v + r*w*w))
    dvmul(u, ru, p);
    dvvtvp(v, rv, p, p);
    dvvtvp(w, rw, p, p);
    scale(mpt5gm1, p);
    daxpy(gm1, rE, p);

    // F[0] = (ru),x + (rv),y + (rw),z
    U[0]->gradient(ru, F[0]->u, 'x');
    U[0]->gradient(rv, d, 'y');
    dvadd(d, F[0]->u);
    U[0]->gradient(rw, d, 'z');
    dvadd(d, F[0]->u);

    // F[1] = (ru*u+p),x + (ru*v),y + (ru*w),z
    dvvtvp(ru, u, p, d);
    U[1]->gradient(d, F[1]->u, 'x');
    dvmul(ru, v, d);
    U[1]->gradient(d, d1, 'y');
    dvadd(d1, F[1]->u);
    dvmul(ru, w, d);
    U[1]->gradient(d, d1, 'z');
    dvadd(d1, F[1]->u);

    // F[2] = (rv*u),x + (rv*v+p),y + (rv*w),z
    dvmul(rv, u, d);
    U[2]->gradient(d, F[2]->u, 'x');
    dvvtvp(rv, v, p, d);
    U[2]->gradient(d, d1, 'y');
    dvadd( d1, F[2]->u );
    dvmul(rv, w, d);
    U[2]->gradient(d, d1, 'z');
    dvadd(d1, F[2]->u);

    // F[3] = (rw*u),x + (rw*v),y + (rw*w+p),z
    dvmul(rw, u, d);
    U[3]->gradient(d, F[3]->u, 'x');
    dvmul(rw, v, d);
    U[3]->gradient(d, d1, 'y');
    dvadd( d1, F[3]->u );
    dvvtvp(rw, w, p, d);
    U[3]->gradient(d, d1, 'z');
    dvadd(d1, F[3]->u);

    // F[4] = (u*(rE+p)),x + (v*(rE+p)),y + (w*(rE+p)),z
    dvadd(rE, p);
    dvmul(u, p, d);
    U[4]->gradient(d, F[4]->u, 'x');
    dvmul(v, p, d);
    U[4]->gradient(d, d1, 'y');
    dvadd( d1, F[4]->u );
    dvmul(w, p, d);
    U[4]->gradient(d, d1, 'z');
    dvadd( d1, F[4]->u );
  }
  Us.end_share_sides();
  convective_flux( Us, Uf );
  for (LocalSize e=0; e<Us[0]->ne; e++) {
    for (vField::size_type n=0; n<Nfields; n++) {
      F[n] = Uf[n]->el[e];
      Us[n]->el[e]->lift( F[n], F[n]->u );
    }
  }
}

/// Compute the Euler flux
/** For descriptions of the numerical fluxes See: E.F. Toro, "Riemann
    Solvers and Numerical Methods for Fluid Dynamics," 2nd Edition,
    Springer, 1999. In particular, see section 3.2 for the
    multi-dimensional Euler equations, Chapter 8 for flux vector splitting
    methods such as Steger-Warming and van Leer, and Chapter 11 for the Roe
    method. */
void Euler3d::convective_flux(vField &Us, vField &Uf) {
  flux_type flux = LaxFriedrichs;
#ifdef REO_USE_GETSIDEMAPS
  iVector mapl, mapr;
#endif
  Scalar sx, sy, sz;
  Scalar tx, ty, tz;
  Scalar Ul[NFIELDS], Ur[NFIELDS];
  Scalar Fh[NFIELDS], Fpl[NFIELDS], Fmr[NFIELDS];
  Scalar lambda[NFIELDS];
  Scalar rl, rul, rvl, rwl, rEl, ul, vl, wl, pl, Hl;
  Scalar rr, rur, rvr, rwr, rEr, ur, vr, wr, pr, Hr;
  vector<Side *> sl(Nfields), sr(Nfields);
  vector<Side *> fl(Nfields), fr(Nfields);

  const Scalar gm1=gamma-one;

  for (LocalSize e=0; e<Us[0]->ne; e++) {               // loop over elements
    Element* U = Us[0]->el[e];
    for (Ordinal i=0; i<Us[0]->el[e]->nSides(); i++) {  // loop over sides
      if (Us[0]->el[e]->side[i]->master()) {            // if master side
        for (vField::size_type ni=0; ni<Nfields; ni++) {
          sl[ni] = Us[ni]->el[e]->side[i];        // local state side
          sr[ni] = Us[ni]->el[e]->side[i]->link;  // adjacent state side
          fl[ni] = Uf[ni]->el[e]->side[i];        // local flux side
          fr[ni] = Uf[ni]->el[e]->side[i]->link;  // adjacent flux side
        }
#ifdef REO_USE_GETSIDEMAPS
        get_side_maps( sl[0], sr[0], mapl, mapr );
#endif

        const Ordinal qtot = sl[0]->qtot();       // number of quad pts on side
        for (Ordinal q=0; q<qtot; ++q) {          // loop over side quad-pts

#ifdef REO_USE_GETSIDEMAPS
          const Ordinal ql = mapl[q];
          const Ordinal qr = mapr[q];
#else
          const Ordinal ql = U->sideMap(sl[0], q);
          const Ordinal qr = U->sideMap(sr[0], q);
#endif
          const Scalar nx = Us[0]->el[e]->side[i]->nx(ql);  // side normal
          const Scalar ny = Us[0]->el[e]->side[i]->ny(ql);  // side normal
          const Scalar nz = Us[0]->el[e]->side[i]->nz(ql);  // side normal

          // make a tangent vectors
          sx = ny;
          sy = nz;
          sz = nx;
          // orthogonalize (knowing that n is normalized)
          const Scalar sdn = nx*sx + ny*sy + nz*sz;
          sx -= sdn*nx;
          sy -= sdn*ny;
          sz -= sdn*nz;
          // normalize
          const Scalar snrm_inv = one/sqrt(sx*sx + sy*sy + sz*sz);
          sx *= snrm_inv;
          sy *= snrm_inv;
          sz *= snrm_inv;
          // make other tangent vector via cross product
          tx = ny*sz - sy*nz;
          ty = nz*sx - sz*nx;
          tz = nx*sy - sx*ny;
          // normalize
          const Scalar tnrm_inv = one/sqrt(tx*tx + ty*ty + tz*tz);
          tx *= tnrm_inv;
          ty *= tnrm_inv;
          tz *= tnrm_inv;
#if 0
          if (e==0 && i==2) {
            cout << "n = " << nx << ", " << ny << ", " << nz << endl;
            cout << "s = " << sx << ", " << sy << ", " << sz << endl;
            cout << "t = " << tx << ", " << ty << ", " << tz << endl;
          }
#endif
          // inverse of rotation matrix
          const Scalar detA = (nx*sy*tz + sx*ty*nz + tx*sz*ny) -
              (nz*sy*tx + sz*ty*nx + tz*sx*ny);
          if (detA<0) cout << "detA < 0:  eid = " << e << ", side = " << i
              << ", q = " << q << endl;
          const Scalar idetA = one/detA;
          const Scalar xn =  (sy*tz - sz*ty)*idetA;
          const Scalar yn = -(sx*tz - sz*tx)*idetA;
          const Scalar zn =  (sx*ty - sy*tx)*idetA;
          const Scalar xs = -(ny*tz - nz*ty)*idetA;
          const Scalar ys =  (nx*tz - nz*tx)*idetA;
          const Scalar zs = -(nx*ty - ny*tx)*idetA;
          const Scalar xt =  (ny*sz - nz*sy)*idetA;
          const Scalar yt = -(nx*sz - nz*sx)*idetA;
          const Scalar zt =  (nx*sy - ny*sx)*idetA;
#if 0
          if (e==0 && i==2) {
            cout << "xn = " << xn << ", xs = " << xs << ", xt = " << xt <<endl;
            cout << "yn = " << yn << ", yn = " << ys << ", yt = " << yt <<endl;
            cout << "zn = " << zn << ", zn = " << zs << ", zt = " << zt <<endl;
          }
#endif
          // compute normal flux from interior (left)

          // left state
          Ul[0] = sl[0]->u[ql];  // rho
          Ul[1] = sl[1]->u[ql];  // rho u
          Ul[2] = sl[2]->u[ql];  // rho v
          Ul[3] = sl[3]->u[ql];  // rho w
          Ul[4] = sl[4]->u[ql];  // E

          // left state projected to the normal
          rl  = Ul[0];                            // density
          rul = Ul[1]*nx + Ul[2]*ny + Ul[3]*nz;   // normal momentum
          rvl = Ul[1]*sx + Ul[2]*sy + Ul[3]*sz;   // tangent_1 momentum
          rwl = Ul[1]*tx + Ul[2]*ty + Ul[3]*tz;   // tangent_2 momentum
          rEl = Ul[4];                            // total energy per volume

          // left primative variables (projected to left normal)
          const Scalar irl = one/rl;
          ul = irl*rul;                                   // normal velocity
          vl = irl*rvl;                                   // tangent_1 velocity
          wl = irl*rwl;                                   // tangent_2 velocity
          pl = gm1*(rEl-pt5*(rul*ul+rvl*vl+rwl*wl));      // pressure
          Hl = irl*(rEl + pl);                            // total enthalpy

          // make sure that density and pressure are realizable
          if (rl < aepsM) {
            stringstream msg;
            msg<<"Element: "<<partition->eid(e)<<", Side: "<<i
               <<", Density(l): "<<rl<<endl;
            comm->error(msg.str());
          }
          if (pl < aepsM) {
            stringstream msg;
            msg<<"Element: "<<partition->eid(e)<<", Side: "<<i
               <<", Pressure(l): "<<pl<<endl;
            comm->error(msg.str());
          }

          // put the left flux on the left state sides
          sl[0]->u[ql] = Fpl[0] = rl*ul;
          sl[1]->u[ql] = Fpl[1] = (rul*ul+pl)*xn + (rvl*ul)*xs + (rwl*ul)*xt;
          sl[2]->u[ql] = Fpl[2] = (rul*ul+pl)*yn + (rvl*ul)*ys + (rwl*ul)*yt;
          sl[3]->u[ql] = Fpl[3] = (rul*ul+pl)*zn + (rvl*ul)*zs + (rwl*ul)*zt;
          sl[4]->u[ql] = Fpl[4] = ul*(rEl + pl);

          // compute normal flux from exterior (right)

          // adjacent state
          Ur[0] = sr[0]->u[qr];
          Ur[1] = sr[1]->u[qr];
          Ur[2] = sr[2]->u[qr];
          Ur[3] = sr[3]->u[qr];
          Ur[4] = sr[4]->u[qr];

          // normal adjacent state (note that local normal is used!)
          rr  = Ur[0];
          rur = Ur[1]*nx + Ur[2]*ny + Ur[3]*nz;
          rvr = Ur[1]*sx + Ur[2]*sy + Ur[3]*sz;
          rwr = Ur[1]*tx + Ur[2]*ty + Ur[3]*tz;
          rEr = Ur[4];

          // right primative variables (projected to left normal)
          const Scalar irr = one/rr;
          ur = irr*rur;
          vr = irr*rvr;
          wr = irr*rwr;
          pr = gm1*(rEr - pt5*(rur*ur + rvr*vr + rwr*wr));
          Hr = irr*(rEr + pr);

          // make sure that density and pressure are realizable
          if (rr < aepsM) {
            stringstream msg;
            msg<<"Element: "<<partition->eid(e)<<", Side: "<<i
               <<", Density(r): "<<rr<<endl;
            comm->error(msg.str());
          }
          if (pr < aepsM) {
            stringstream msg;
            msg<<"Element: "<<partition->eid(e)<<", Side: "<<i
               <<", Pressure(r): "<<pr<<endl;
            comm->error(msg.str());
          }

          // put the right flux on the right state sides
          sr[0]->u[qr] = Fmr[0] = rr*ur;
          sr[1]->u[qr] = Fmr[1] = (rur*ur+pr)*xn + (rvr*ur)*xs + (rwr*ur)*xt;
          sr[2]->u[qr] = Fmr[2] = (rur*ur+pr)*yn + (rvr*ur)*ys + (rwr*ur)*yt;
          sr[3]->u[qr] = Fmr[3] = (rur*ur+pr)*zn + (rvr*ur)*zs + (rwr*ur)*zt;
          sr[4]->u[qr] = Fmr[4] = ur*(rEr + pr);

          switch (flux) {
          case LaxFriedrichs: {
            Scalar lmax = zero;
            const Scalar al = sqrt(gm1*(Hl - pt5*(ul*ul + vl*vl + wl*wl)));
            lambda[0] = ul-al;
            lambda[1] = ul;
            lambda[2] = ul;
            lambda[3] = ul;
            lambda[4] = ul+al;
            for(vField::size_type j=0; j<Nfields; ++j)
              lmax=max(lmax,fabs(lambda[j]));
            const Scalar ar = sqrt(gm1*(Hr - pt5*(ur*ur + vr*vr + wr*wr)));
            lambda[0] = ur-ar;
            lambda[1] = ur;
            lambda[2] = ur;
            lambda[3] = ur;
            lambda[4] = ur+ar;
            for(vField::size_type j=0; j<Nfields; ++j)
              lmax=max(lmax,fabs(lambda[j]));
            // Lax-Friedrichs flux
            Fh[0] = pt5 * ( Fpl[0] + Fmr[0] + lmax * ( Ul[0] - Ur[0] ) );
            Fh[1] = pt5 * ( Fpl[1] + Fmr[1] + lmax * ( Ul[1] - Ur[1] ) );
            Fh[2] = pt5 * ( Fpl[2] + Fmr[2] + lmax * ( Ul[2] - Ur[2] ) );
            Fh[3] = pt5 * ( Fpl[3] + Fmr[3] + lmax * ( Ul[3] - Ur[3] ) );
            Fh[4] = pt5 * ( Fpl[4] + Fmr[4] + lmax * ( Ul[4] - Ur[4] ) );
#ifdef DGM_VERBOSE_FLUX
            cout << "Lax-Friedrichs: Element " << e << ", Side " << i << endl;
            cout << Fh[0] << ", " << Fh[1] << ", " << Fh[2] << ", "<< Fh[3]
                          << ", " << Fh[4] << endl;
#endif
            break;
          }
          default:
            comm->error("Euler3d: Illegal value of flux type");
            break;
          }
          // put fluxes on flux field sides
          for (vField::size_type n=0; n<Nfields; ++n) {
            sr[n]->u[qr] *= -one;         // correct for normal
            fl[n]->u[ql]  =  Fh[n];       // upwind flux
            fr[n]->u[qr]  = -Fh[n];       // correct for normal
          }
        }
      }
    }
  }
}

//===========================================================================
//                        BC database management
//===========================================================================

// Load up the available BC types
void Euler3d::setup_BCdb( ) {
  // cout << "Euler3d::setup_BCdb()" << endl;

  // set default BC types
  dVector ub(5);
  ub[0] = 1.0;
  ub[1] = 1.0;
  ub[2] = 0.0;
  ub[3] = 0.0;
  ub[4] = 20.34126984126985;  // Ma = 0.3
  BC_db["S"].reset( new StateBC("S", ub) );
  BC_db["W"].reset( new WallBC("W", 5) );

  // read new BC types from file
  string fname = root+".bct";
  ifstream in(fname.c_str());
  if (in) Euler3d::read_BCdb( in );   // database of active BC types
}

void Euler3d::read_BCdb( ifstream &in ) {
  // cout << "Euler3d::read_BCdb( ifstream &in )" << endl;
  string tag;
  BC *pbc;
  while ( (pbc = Euler3d::make_BC(in,tag)) ) {
    if ( BC_db.find(tag) != BC_db.end() )
      comm->cerr()<< "WARNING in Euler3d::read_BCdb:  Overriding BC type \""
      << tag << "\"." << endl;
    BC_db[tag].reset( pbc );
  }
}

BC* Euler3d::make_BC( ifstream &in, string &tag ) {
  // cout << "Euler3d::make_BC(ifstream &in, string &tag)" << endl;
  string code;
  if (!(in >> code)) return NULL;
  code = lowerCase(code);
  if (code == "state") {
    if (!(in >> tag)) error("Euler3d::make_BC: Cannot read State tag",1);
    return new StateBC(tag,in,5);
  } else if ( code.find("wall") != code.npos ) {
    if (!(in >>tag)) error("Euler3d::make_BC:  Cannot read Wall tag",1);
    return new WallBC(tag,in);
  } else {
    error("Euler3d::make_BC:  Illegal BC type:  "+code,1);
  }
  return NULL;
}

//===========================================================================
//                           Solid Wall
//===========================================================================

void Euler3d::WallBC::apply( const Scalar t, const vField &F ) {
  // cout << "Euler3d::WallBC::apply" << endl;
  vector<Side*> S(F.size()), B(F.size());
  for (LocalSize n=0; n<F[0]->nbc; ++n) {   // loop over field boundaries
    if (F[0]->bc[n]->type == type ) {
      for (vField::size_type i=0; i<F.size(); ++i) {
        S[i] = F[i]->bc[n]->S;
        B[i] = F[i]->bc[n]->B;
      }
      dVector &nx = S[0]->nx();
      dVector &ny = S[0]->ny();
      dVector &nz = S[0]->nz();
      for (LocalSize i=0; i<S[0]->qtot(); i++) {
        Scalar up, vp, wp, dot;
        up  = S[1]->u[i];
        vp  = S[2]->u[i];
        wp  = S[3]->u[i];
        dot = up*nx[i] + vp*ny[i] + wp*nz[i];
        up  = up - dot*nx[i];           // Get normal substract from vector
        vp  = vp - dot*ny[i];
        wp  = wp - dot*nz[i];
        B[0]->u[i] = S[0]->u[i];
        B[1]->u[i] = up;
        B[2]->u[i] = vp;
        B[3]->u[i] = wp;
        B[4]->u[i] = S[4]->u[i]
              - 0.5*(S[1]->u[i]*S[1]->u[i] + S[2]->u[i]*S[2]->u[i] +
                     S[3]->u[i]*S[3]->u[i])/S[0]->u[i]
              + 0.5*(B[1]->u[i]*B[1]->u[i] + B[2]->u[i]*B[2]->u[i] +
                     B[3]->u[i]*B[3]->u[i])/B[0]->u[i];
      }
    }
  }
}

void Euler3d::WallBC::apply_flux( const Scalar t, const vField &F ) {
  error("Euler3d::WallBC::apply_flux() not implemented.");
}


void Euler3d::WallBC::adjoint_apply( const Scalar t, const vField &state,
                                     const vField &adjoint) {
  error("Euler3d::WallBC::adjoint_apply() not implemented.");
  // will use the adjoint suction (g=0) based on isoentropic/zero-vorticity
  // constraints [gqchen]
}

void Euler3d::WallBC::adjoint_apply_flux( const Scalar t, const vField &state,
                                          const vField &adjoint) {
  error("Euler3d::WallBC::adjoint_apply_flux() not implemented.");
}

//===========================================================================

void Euler3d::enforce_bc(vField &F) {
  for (BC::db_citr i=BC_db.begin(); i!= BC_db.end(); ++i)
    i->second->apply( t, F );
}

void Euler3d::enforce_flux_bc(vField &F) {
  stringstream msg;
  msg<<"Euler3d::enforce_flux_bc(vField &) not implemented."<<endl;
  comm->error(msg.str());
}

// set the initial condition
void Euler3d::set_ic(vField &F, string ext) {
  string fname = root+ext;
  ifstream in(fname.c_str());
  if (!in) {
    stringstream msg;
    msg << "Could not open initial condition " << fname << endl;
    comm->error(msg.str());
  }
  string buffer, code;
  getline(in,buffer);
  if (!(in>>code)) error("Cannot read IC code",1);
  getline(in,buffer);
  //  cout << "IC code = " << code << endl;
  if (lowerCase(code) == "given") {
    F.fill(in);
  } else if (lowerCase(code) == "restart") {
    string rstfile;
    if (!(in>>rstfile)) {
      stringstream msg;
      msg<< "Cannot read restart file name from " << fname << endl;
      comm->error(msg.str());
    }
    read(rstfile, F);
    if (comm->Master()) cout << "Restarting from: " << rstfile << endl;
  } else if (lowerCase(code) == "restart_p") {
    string rstfile;
    if (!(in>>rstfile)) {
      stringstream msg;
      msg<< "Cannot read restart file name from " << fname << endl;
      comm->error(msg.str());
    }
    GlobalSize eid;
    LocalSize dof;
    Scalar eps;
    in >> eid >> dof >> eps;
    read(rstfile, F);
    if (partition->owns(eid)) F[dof]->el[partition->inc(eid)]->u += eps;
    if (comm->Master()) cout << "Restarting from: " << rstfile
        << " with added perturbations." << endl;
  } else if (lowerCase(code) == "vortex") {
    int nVorts;
    Scalar x0, y0, radius, amp, Ma;
    in>>nVorts;
    for (int nv=0; nv<nVorts; nv++) {
      in >> x0 >> y0 >> radius >> amp >> Ma;
      OseenVortex vortex(x0, y0, radius, amp, Ma, gamma);
      for (LocalSize e=0; e<ne; e++) {
        for (LocalSize q=0; q<F[0]->el[e]->qtot; q++) {
          F[0]->el[e]->u[q] += vortex.R( (*F[0]->el[e]->C)[q] );
          F[1]->el[e]->u[q] += vortex.U( (*F[1]->el[e]->C)[q] );
          F[2]->el[e]->u[q] += vortex.V( (*F[2]->el[e]->C)[q] );
          F[3]->el[e]->u[q] += vortex.W( (*F[3]->el[e]->C)[q] );
          F[4]->el[e]->u[q] += vortex.E( (*F[4]->el[e]->C)[q] );
        }
      }
    }
  } else if (lowerCase(code) == "acousticpulse") {
    AcousticPulse wave(in, gamma);
    dVector s(Nfields);
    for (LocalSize e=0; e<ne; e++) {
      for (LocalSize q=0; q<F[0]->el[e]->qtot; q++) {
        for (vField::size_type n=0; n<Nfields; n++) s[n] = F[n]->el[e]->u[q];
        wave.evaluate( (*F[0]->el[e]->C)[q], s );
        for (vField::size_type n=0; n<Nfields; n++) F[n]->el[e]->u[q] = s[n];
      }
    }
    if (comm->Master()) cout << "Built AcousticPulse" << endl;
#ifdef DGM_USE_BOOST_RANDOM
  } else if (lowerCase(code) == "turbulentchannel") {
    TurbulentChannel ic(in, gamma);
    dVector s(Nfields);
    for (LocalSize e=0; e<ne; e++) {
      for (LocalSize q=0; q<F[0]->el[e]->qtot; q++) {
        for (vField::size_type n=0; n<Nfields; n++) s[n] = F[n]->el[e]->u[q];
        ic.evaluate( (*F[0]->el[e]->C)[q], s );
        for (vField::size_type n=0; n<Nfields; n++) F[n]->el[e]->u[q] = s[n];
      }
    }
    if (comm->Master()) cout << "Built TurbulentChannel" << endl;
#endif
#if defined(DGM_USE_BOOST_RANDOM)
  } else if (lowerCase(code) == "isotropicturbulence") {
    IsotropicTurbulence ic(in, gamma);
    dVector s(Nfields);
    for (LocalSize e=0; e<ne; e++) {
      for (LocalSize q=0; q<F[0]->el[e]->qtot; q++) {
        for (LocalSize n=0; n<Nfields; n++) s[n] = F[n]->el[e]->u[q];
        ic.evaluate( (*F[0]->el[e]->C)[q], s );
        for (LocalSize n=0; n<Nfields; n++) F[n]->el[e]->u[q] = s[n];
      }
    }
    if (comm->Master()) cout << "Built IsotropicTurbulence" << endl;
#endif
  } else {
    comm->error("Euler3d::set_ic()  Unsupported IC type");
  }
#ifdef DGM_NO_PROJECT_IC
  if (comm->Master())
    cout << "WARNING:  No projection of Initial condition" << endl;
  for (LocalSize i=0; i<Nfields; i++)
    for (LocalSize e=0; e<ne; e++)
      F[i]->el[e]->state = Element::Physical;
#else
  project( F ); // project fields to the polynomial space just to make sure
#endif
}

/// If defined than the side jumps are used in computing vorticity
#define EULER3D_VORTICITY_JUMP

/// Compute the vorticity and divergence
void Euler3d::compute_vorticity() {
  Element *S[NFIELDS], *F[NFIELDS];
  dVector u, v, w, p, e, wk;
  dVector r, ru, rv, rw, rE;

#ifdef EULER3D_VORTICITY_JUMP
  U.fill_sides();
  enforce_bc( U );
  U.share_sides();
  primitive_sides( U );
  average_flux( U, Ut, '+' );
#endif

  for (LocalSize i=0; i<U[0]->ne; i++) {
    // local version of the state
    S[0] = U[0]->el[i];
    S[1] = U[1]->el[i];
    S[2] = U[2]->el[i];
    S[3] = U[3]->el[i];
    S[4] = U[4]->el[i];

    // local version of the state
    F[0] = Ut[0]->el[i];
    F[1] = Ut[1]->el[i];
    F[2] = Ut[2]->el[i];
    F[3] = Ut[3]->el[i];
    F[4] = Ut[4]->el[i];

    const Ordinal qtot = U[0]->el[i]->qtot;

    r.alias (S[0]->u);  // rho
    ru.alias(S[1]->u);  // rho u
    rv.alias(S[2]->u);  // rho v
    rw.alias(S[3]->u);  // rho w
    rE.alias (S[4]->u); // total energy density

    u.alias(wk1,0,qtot);
    v.alias(wk1,qtot,qtot);
    w.alias(wk1,2*qtot,qtot);
    p.alias(wk1,3*qtot,qtot);
    e.alias(wk1,4*qtot,qtot);
    wk.alias(wk1,5*qtot,qtot);

    dvdiv(ru, r, u);   // compute u
    dvdiv(rv, r, v);   // compute v
    dvdiv(rw, r, w);   // compute w
    dvdiv(rE, r, e);   // internal energy + 0.5 |V|^2

    dvmul(u,u,wk);     // wk = u^2
    dvvtvp(v,v,wk,wk); // wk = u^2 + v^2
    dvvtvp(w,w,wk,wk); // wk = u^2 + v^2 + w^2
    daxpy(-pt5,wk,e);  // e  = e - 0.5 * wk = internal energy

    // p = (gamma-1.0)*(rE-0.5*(r*u*u + r*v*v + r*w*w))
    dvmul(u, ru, p);
    dvvtvp(v, rv, p, p);
    dvvtvp(w, rw, p, p);
    scale(-pt5*(gamma-1.0), p);
    daxpy(gamma-1.0, rE, p);

    dVector ux(qtot);
    dVector uy(qtot);
    dVector uz(qtot);
    dVector vx(qtot);
    dVector vy(qtot);
    dVector vz(qtot);
    dVector wx(qtot);
    dVector wy(qtot);
    dVector wz(qtot);

#ifdef EULER3D_VORTICITY_JUMP
    gradient( S[1], F[1], u, ux, uy, uz );
    gradient( S[2], F[2], v, vx, vy, vz );
    gradient( S[3], F[3], w, wx, wy, wz );
#else
    F[0]->gradient(u, ux, uy, uz);
    F[0]->gradient(v, vx, vy, vz);
    F[0]->gradient(w, wx, wy, wz);
#endif
    dvadd(ux, vy, F[0]->u);              // divergence
    daxpy( -one, vz, wy, F[1]->u );      // omega_x
    daxpy( -one, wx, uz, F[2]->u );      // omega_y
    daxpy( -one, uy, vx, F[3]->u );      // omega_z
    F[4]->fill(p);                       // pressure
  }
}

/// If defined then perform a projection (lift) to compute diffusive flux
#define EULER3D_GRADIENT_PROJECT

/// Compute a lifted gradient
void Euler3d::gradient( Element *S, Element *F, dVector &u,
                        dVector &ux, dVector &uy, dVector &uz ) {
    S->gradient( u, ux, uy, uz );
    S->lift( F, ux, 'x' );
#ifdef EULER3D_GRADIENT_PROJECT
    S->project(ux);
#endif
    S->lift( F, uy, 'y' );
#ifdef EULER3D_GRADIENT_PROJECT
    S->project(uy);
#endif
    S->lift( F, uz, 'z' );
#ifdef EULER3D_GRADIENT_PROJECT
    S->project(uz);
#endif
}

/// Convert edge values from conservative to primitive variables
void Euler3d::primitive_sides( vField &Us ) {
  // loop over all sides including boundary sides
  for (LocalSize k=0; k<Us[0]->ne; k++) {
    for (LocalSize i=0; i<Us[0]->el[k]->nSides(); i++) {
      if (Us[0]->el[k]->side[i]->master()) {
        dVector wk(Us[0]->el[k]->side[i]->qtot());// WARNING: making new memory
        // left side
        dVector  r(Us[0]->el[k]->side[i]->u);     // rho
        dVector  u(Us[1]->el[k]->side[i]->u);     // rho u
        dVector  v(Us[2]->el[k]->side[i]->u);     // rho v
        dVector  w(Us[3]->el[k]->side[i]->u);     // rho w
        dVector  e(Us[4]->el[k]->side[i]->u);     // total energy per volume
        dvdiv(u, r, u);       // u-velocity
        dvdiv(v, r, v);       // v-velocity
        dvdiv(w, r, w);       // w-velocity
        dvdiv(e, r, e);       // internal energy + 0.5 |V|^2
        dvmul(u, u, wk);      // wk = u^2
        dvvtvp(v, v, wk, wk); // wk = u^2 + v^2
        dvvtvp(w, w, wk, wk); // wk = u^2 + v^2 + w^2
        daxpy(-pt5, wk, e);   // e  = e - 0.5 * wk = internal energy
        // right side
        r.alias(Us[0]->el[k]->side[i]->link->u);  // rho
        u.alias(Us[1]->el[k]->side[i]->link->u);  // rho u
        v.alias(Us[2]->el[k]->side[i]->link->u);  // rho v
        w.alias(Us[3]->el[k]->side[i]->link->u);  // rho w
        e.alias(Us[4]->el[k]->side[i]->link->u);  // total energy per volume
        dvdiv(u, r, u);       // u-velocity
        dvdiv(v, r, v);       // v-velocity
        dvdiv(w, r, w);       // w-velocity
        dvdiv(e, r, e);       // internal energy + 0.5 |V|^2
        dvmul(u, u, wk);      // wk = u^2
        dvvtvp(v, v, wk, wk); // wk = u^2 + v^2
        dvvtvp(w, w, wk, wk); // wk = u^2 + v^2 + w^2
        daxpy(-pt5, wk, e);   // e  = e - 0.5 * wk = internal energy
      }
    }
  }
}

void Euler3d::write_bndry_stats() {
  if (!U[0]->bndry_stats->valid) return;

  Coord C;
  dVector r, ru, rv, rw, rE;
  U[0]->bndry_stats->get_coordinates( C );
  U[0]->bndry_stats->get_solution( r );
  U[1]->bndry_stats->get_solution( ru );
  U[2]->bndry_stats->get_solution( rv );
  U[3]->bndry_stats->get_solution( rw );
  U[4]->bndry_stats->get_solution( rE );

  const Ordinal qtot = r.size();
  dVector u(qtot), v(qtot), w(qtot), p(qtot), e(qtot), wk(qtot);

  dvdiv(ru, r, u);   // compute u
  dvdiv(rv, r, v);   // compute v
  dvdiv(rw, r, w);   // compute w
  dvdiv(rE, r, e);   // internal energy + 0.5 |V|^2

  dvmul(u,u,wk);     // wk = u^2
  dvvtvp(v,v,wk,wk); // wk = u^2 + v^2
  dvvtvp(w,w,wk,wk); // wk = u^2 + v^2 + w^2
  daxpy(-pt5,wk,e);  // e  = e - 0.5 * wk = internal energy

  // p = (gamma-1.0)*(rE-0.5*(r*u*u + r*v*v + r*w*w))
  dvmul(u, ru, p);
  dvvtvp(v, rv, p, p);
  dvvtvp(w, rw, p, p);
  scale(-pt5*(gamma-1.0), p);
  daxpy(gamma-1.0, rE, p);

  // Scalar Pref = (gamma-1.0)*(1.0/(gamma*(gamma-1.0)*0.3*0.3));

#ifdef DGM_PARALLEL
  // gather data to the master
  int np = comm->NumProc();
  intVector recvcounts(np);
  intVector displs(np);

  {
    const int i = static_cast<int>(qtot);
    comm->GatherAll(&i, recvcounts.data(), 1);
  }

  // make displacements (this does not preserve ordering, should improve)
  for(int i=0; i<np; i++) {
    displs[i] = 0;
    for(int j=0; j<i; j++)
      displs[i] += recvcounts[j];
  }

  Ordinal glen=0;
  comm->SumAll( &qtot, &glen, 1 );

  dVector gx(glen), gy(glen), gdata(glen);

  comm->GatherAll(C.x, qtot,    gx, recvcounts, displs);
  comm->GatherAll(C.y, qtot,    gy, recvcounts, displs);
  comm->GatherAll(p,   qtot, gdata, recvcounts, displs);

  if (comm->Master()) {
    string fname;
    char buf[80];
    sprintf(buf, "%s.%lld.cp", root.c_str(), (long long)step);
    fname = buf;
    FILE *out = fopen(fname.c_str(),"w");
    for (Ordinal q=0; q<gdata.size(); ++q )
      fprintf(out," %14.7e %14.7e %14.7e\n", gx[q], gy[q], gdata[q]);
    fclose(out);
  }
#else
  string fname;
  char buf[80];
  sprintf(buf,"%s.%lld.bdt",root.c_str(), (long long)step);
  fname = buf;
  FILE *out = fopen(fname.c_str(),"w");
  for (Ordinal q=0; q<qtot; ++q )
    fprintf(out,
        "%14.7e %14.7e %14.7e %14.7e %14.7e %14.7e %14.7e %14.7e %14.7e\n",
        C.x[q], C.y[q], r[q], ru[q], rv[q], rw[q], rE[q], p[q], e[q]);
  fclose(out);

  sprintf(buf,"%s.%lld.cp",root.c_str(), (long long)step);
  fname = buf;
  out = fopen(fname.c_str(),"w");
  fprintf(out,"#%14.7e %14.7e\n", U[0]->bndry_stats->liftcalc(p),
      U[0]->bndry_stats->dragcalc(p));
  for (Ordinal q=0; q<qtot; ++q )
    fprintf(out," %14.7e %14.7e %14.7e\n", C.x[q], C.y[q], p[q]);
  fclose(out);
#endif  // DGM_PARALLEL
}

} // namespace Reo
