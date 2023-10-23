/*=============================================================================
  Module:    Reo Burgers Module

  Contact:   S. Scott Collis

  Copyright: (c)2003 Rice University
             (c)2008 Sandia National Laboratories
=============================================================================*/

/** \file Burgers.cpp
    \brief Burgers equation solver implementation
    \author S. Scott Collis

    This version supports both 1d and 2d Burgers.  For 2d Burgers, several
    forms of the convective term are implemented with the default being a
    skew symmetric form that removes first-order aliasing effects
*/

// DGM includes
#include "Domain.hpp"
#include "TimeInt.hpp"
#include "Field.hpp"
#include "vField.hpp"
using namespace DGM;

// local includes
#include "Reo.hpp"
#include "Burgers.hpp"
#include "BurgersIC.hpp"
#include "BurgersBC.hpp"

namespace Reo {

/// if defined then perform a projection when computing the diffusive flux
#define REO_PROJECT_DIFF_FLUX

/// Constructor
Burgers::Burgers( DGM::ArgList &args, const DGM::Comm::Ptr comm_) :
  Domain(args,comm_), limit(0), mu(0.0), Uv(comm_)
{
  comm->cout() << "Burgers::Burgers()" << endl;

  // initialize parameters
  Ordinal p, q;
  p = params["p"];                     // polynomial order
  if ( !(q=params["q"]) ) q = p + 2;   // number of quadrature points
  nsd = params["nsd"];                 // number of space dimensions
  if (verbosity())
    comm->cout()<<"  Using p = "<<p<<", q = "<<q<<endl;

  // read arguments (overrides defaults and input file)
  parse_args( args );

  limit = params.get("limit",limit);   // limiter type
  mu = params.get("vis",mu);           // viscosity

  vector<string> field_names;          // Field names
  field_names.push_back("u");

  // build a Field of Elements and Sides
  if (params["imesh"]) {
    Mesh mesh(params);
    U.push_back( new Field(p, q, mesh, root, field_names[0],
                           Field::FULL, comm ) );
    partition = U[0]->partition;
  } else if (params["bmesh"]) {
    U.push_back( new Field(p, q, root, field_names[0], partition, 1,
                           Reo::NumEqntype, p2i(BURGERS), comm ) );
  } else {
    U.push_back( new Field(p, q, root, field_names[0], partition, comm ) );
  }

  // set some additional domain parameters
  ne = U[0]->ne;
  nsd = U[0]->nsd();

#ifdef REO_USE_GETSIDEMAPS
  setup_side_maps();
#endif

  // set the number of fields in the domain
  Nfields = nsd;                       // = 1 for a scalar problem

  //comm->cout()<<"nsd     = "<<nsd<<endl;
  //comm->cout()<<"Nfields = "<<Nfields<<endl;

  if (nsd==2) {
    field_names.push_back("v");
  } else if (nsd==3) {
    field_names.push_back("v");
    field_names.push_back("w");
  } else if (nsd!=1) {
    throw DGM::exception("Invalid nsd="+asString(nsd));
  }

  for (vField::size_type i=1; i<Nfields; ++i)
    U.push_back( new Field( U[0], root, field_names[i] ) );

  // make auxiliary Fields using copy constructor
  for (vField::size_type i=0; i<Nfields; ++i) {
    Ut.push_back( new Field(U[i], root, field_names[i]) );
    Uv.push_back( new Field(U[i], root, field_names[i]) );
  }

  // setup vField names
  U.set_name("U");
  Ut.set_name("Ut");
  Uv.set_name("Uv");

  // workspace
  wk1.resize(20*max(Lmax(),Qmax()));
  wk2.resize(20*max(Lmax(),Qmax()));
  wk3.resize(20*max(Lmax(),Qmax()));

  // make sure that storage is initialized
  zero_all_fields();

  // make analysis object
  response = Response::factory(U, this);

  setup_BCdb();

  setup_Sourcedb();

  set_TimeInt();

  //comm->cout()<<"Burgers completed construction"<<endl;
}

// Parse parameters from the argument list
void Burgers::parse_args( DGM::ArgList &args ) {
  string name, value;
  list< DGM::ArgList::iterator > li;
  for ( DGM::ArgList::iterator a = args.begin(); a != args.end(); a++ ) {
    if ( (*a)[0] == '-' ) {
      name = *a;
      if (name == "-help") {
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

void Burgers::showUsage() {
  comm->cout()
    << "Burgers Class Options \n"
    << "----------------------------------------------------------------\n"
    << "----------------------------------------------------------------\n";
}

/// \warning Not all plotters work in parallel
int Burgers::plot(const string &rst) {
  string fname, name(rst), caption;
  char buf[80];
  read( rst, U );
  size_t loc = name.find(".rst");
  if ( loc != string::npos ) name.erase(loc);
  sprintf(buf,"%s.dat",name.c_str()); fname = buf;
  sprintf(buf,"State variables at t =%11.4e, step = %lld",t,(long long)step);
  caption = buf;
  if (comm->Master()) U.tecplot(fname,caption);
  if (nsd>1) U.paraview(fname,caption);
  return 0;
}

void Burgers::zero_all_fields() {
  Domain::zero_all_fields();
  Uv.zero();
}

Scalar Burgers::set_time_step(vField &U) {
  Scalar cfl = 0;
  return cfl;
}

/// A simple limiter for shocks
void Burgers::limiter(vField &Uf) {
  if (limit==0) return;
  Scalar delta, m_delta_sq;
  Scalar sl, sr, sm, a1, a2, a3, tmp;
  Field *U= Uf[0];
  const LocalSize ne = U->ne;
  const LocalSize nm = U->el[0]->nModes();
  U->forward_transform();
  for (LocalSize e=0; e<ne; e++) { // loop over the elements
    delta = 1.0/40.0; // U->el[e]->delta_min();  Hacked out [SSC]
    if (e==0) {
      sl = U->el[e+1]->uh[0];       // U_i-1
      sr = sl;                      // U_i+1  U->el[e+1]->y[0]
      sm = U->el[e]->uh[0];         // U_i
      a1 = U->el[e]->uh[1];
      a2 = sr-sm;
      a3 = a2;
    } else if (e==ne-1) {
      sl = U->el[e-1]->uh[0];        // U_i-1
      //sr = sl;                       // U_i+1  U->el[e+1]->y[0];
      sm = U->el[e]->uh[0];          // U_i
      a1 = U->el[e]->uh[1];
      a3 = sm-sl ;
      a2 = a3;
    } else {
      sl = U->el[e-1]->uh[0];        // U_i-1
      sr = U->el[e+1]->uh[0];        // U_i+1
      sm = U->el[e]->uh[0];          // U_i
      a1 = U->el[e]->uh[1];
      a2 = sr-sm;
      a3 = sm-sl;
    }
    m_delta_sq = 50*delta*delta; // 20*delta*delta;  // 20 limits too much
    if ( fabs(a1) <= m_delta_sq ) {
      U->el[e]->uh[1] =  a1;
    } else {
      // chop off the solution for higher modes
      for (LocalSize m=1; m<nm; m++) U->el[e]->uh[m] = 0.0;
      cout << "Limiting on element " << e << endl;
      if (a1 >= 0.0 && a2 >= 0.0 && a3 >= 0.0) {
        tmp = min(a1,a2);
        U->el[e]->uh[1] = min(tmp,a3);
        //  s*min_i(|a_i|) = min(a_i) V a_i>=0
      } else if(a1 <= 0.0 && a2 <= 0.0 && a3 <= 0.0) {
        tmp = min(fabs(a1),fabs(a2));
        U->el[e]->uh[1] = -min(tmp,fabs(a3));
        //  s*min_i(|a_i|) = max(a_i) V a_i<=0
      } else {
        U->el[e]->uh[1] = 0.0;
      }
    }
  }
  U->backward_transform();
}

void Burgers::time_derivative( vField &Us, vField &Uf ) {
  if (nsd==1) {
    limiter( Us );
#ifdef REO_BURGERS_NO_CONVECTION
    Uf.zero();
#else
    convection( Us, Uf );
#endif
  } else if (nsd==2) {
    convection2d( Us, Uf );
  } else {
    throw DGM::exception("Illegal value of nsd="+asString(nsd));
  }
  diffusion( Us, Uv, Uf );
  add_source( Us, Uf );
  project( Uf );
}

/// Computes 1d Burgers equation
/**
   \f[ \int_{\Omega_e} w u_{,t} + w F_{,i} - w F^v_{,i} d\Omega +
   \int_{\Gamma_e} w ( \hat F_n - F_n - \hat F^v_n + F^v_n ) d\Gamma = 0 \f]
*/
void Burgers::convection( vField &Uf, vField &Ff ) {
  Uf.fill_sides();                      // put interior soln on the sides
  Uf.share_sides();
  enforce_bc(Uf);                       // update bc side values
  convective_flux( Uf, Ff );                // compute surface fluxes on sides
  for (LocalSize e=0; e<Uf[0]->ne; e++) {
    Element *U = Uf[0]->el[e];
    Element *F = Ff[0]->el[e];
    dvmul( U->u, U->u, F->u );
    scale( pt5, F->u );
    U->gradient( F->u, F->u );
    U->lift( F, F->u ); // add side fluxes to interior
  }
}

#if defined(REO_BURGERS_STRONG_FORM)

/// Computes 2d Burgers equation
/** u_j u_{i,j} = (u_j u_i)_{,j} - u_{j,j} u_i

   - We implement the first form in the convection term
   - We implement the flux shown in the second term in convective_flux_2d

   = 1/2 (u_j u_i)_{,j} + 1/2 (u_j u_i)_{,j} - u_{j,j} u_i
   = 1/2 (u_j u_i)_{,j} + 1/2 u_{j,j} u_i + 1/2 u_j u_{i,j} - u_{j,j} u_i
   = 1/2 (u_j u_i)_{,j} + 1/2 u_j u_{i,j} - 1/2 u_{j,j} u_i
   = 1/2 (u_j u_i)_{,j} + 1/2 ( u_j u_{i,j} - u_{j,j} u_i )
   = 1/2 u_j u_{i,j} + 1/2 u_j u_{i,j}
*/
void Burgers::convection2d( vField &Uf, vField &Ff ) {
  //comm->cout()<<"Burgers::convection2d(...) [strong form]"<<endl;
  Element *U[Nfields], *F[Nfields];
  dVector u, v, uu, uv, vv, ux, vy, uux, uvx, uvy, vvy, div;
  dVector uy, vx;
  Uf.fill_sides();                      // put interior soln on the sides
  Uf.share_sides();
  enforce_bc(Uf);                       // update bc side values
  convective_flux_2d( Uf, Ff );             // compute surface fluxes on sides
  for (LocalSize e=0; e<Uf[0]->ne; e++) {
    U[0] = Uf[0]->el[e];
    U[1] = Uf[1]->el[e];
    F[0] = Ff[0]->el[e];
    F[1] = Ff[1]->el[e];

    const Ordinal qtot = U[0]->qtot;

    u.alias(U[0]->u);
    v.alias(U[1]->u);

    uu.alias(wk1,0*qtot,qtot);
    uv.alias(wk1,1*qtot,qtot);
    vv.alias(wk1,2*qtot,qtot);
    ux.alias(wk1,3*qtot,qtot);
    vy.alias(wk1,4*qtot,qtot);
    uy.alias(wk1,5*qtot,qtot);
    vx.alias(wk1,6*qtot,qtot);

    U[0]->gradient(u, ux, uy);
    U[1]->gradient(v, vx, vy);

    // F[0]
    dvmul(u, ux, F[0]->u);
    dvvtvp(v, uy, F[0]->u, F[0]->u);

    // F[1]
    dvmul(u, vx, F[1]->u);
    dvvtvp(v, vy, F[1]->u, F[1]->u);

    for (LocalSize n=0; n<Nfields; ++n) {
      U[n]->lift( F[n], F[n]->u );
    }
  }
}

#elif defined(REO_BURGERS_FLUX_FORM)

/// Computes 2d Burgers equation
/** u_j u_{i,j} = (u_j u_i)_{,j} - u_{j,j} u_i. */
void Burgers::convection2d( vField &Uf, vField &Ff ) {
  //comm->cout()<<"Burgers::convection2d(...) [flux form]"<<endl;
  Element *U[Nfields], *F[Nfields];
  dVector u, v, uu, uv, vv, ux, vy, uux, uvx, uvy, vvy, div;
  Uf.fill_sides();                      // put interior soln on the sides
  Uf.share_sides();
  enforce_bc(Uf);                       // update bc side values
  convective_flux_2d( Uf, Ff );             // compute surface fluxes on sides
  for (LocalSize e=0; e<Uf[0]->ne; e++) {
    U[0] = Uf[0]->el[e];
    U[1] = Uf[1]->el[e];
    F[0] = Ff[0]->el[e];
    F[1] = Ff[1]->el[e];

    const Ordinal qtot = U[0]->qtot;

    u.alias(U[0]->u);
    v.alias(U[1]->u);

    uu.alias(wk1,0*qtot,qtot);
    uv.alias(wk1,1*qtot,qtot);
    vv.alias(wk1,2*qtot,qtot);
    ux.alias(wk1,3*qtot,qtot);
    vy.alias(wk1,4*qtot,qtot);

    uux.alias(wk1,5*qtot,qtot);
    uvx.alias(wk1,6*qtot,qtot);
    uvy.alias(wk1,7*qtot,qtot);
    vvy.alias(wk1,8*qtot,qtot);

    div.alias(wk1,9*qtot,qtot);

    dvmul( u, u, uu );
    dvmul( u, v, uv );
    dvmul( v, v, vv );
    U[0]->gradient( u, ux, 'x' );
    U[1]->gradient( v, vy, 'y' );
    dvadd( ux, vy, div );
    scale(-one,div);

    U[0]->gradient( uu, uux, 'x');
    U[0]->gradient( uv, uvx, uvy);
    U[0]->gradient( vv, vvy, 'y');

    // F[0]
    dvadd( uux, uvy, F[0]->u );
    dvvtvp( div, u, F[0]->u, F[0]->u );

    // F[1]
    dvadd( uvx, vvy, F[1]->u );
    dvvtvp( div, v, F[1]->u, F[1]->u );

    for (LocalSize n=0; n<Nfields; ++n) {
      U[n]->lift( F[n], F[n]->u );
    }
  }
}

#else  // skew-symmetric

/// Computes 2d Burgers equation in skew symmetric form
/** u_j u_{i,j} = 1/2 (u_j u_i)_{,j} + 1/2 ( u_j u_{i,j} - u_{j,j} u_i ). */
void Burgers::convection2d( vField &Uf, vField &Ff ) {
  //comm->cout()<<"Burgers::convection2d(...) [skew-symmetric form]"<<endl;
  Element *U[Nfields], *F[Nfields];
  dVector u, v, uu, uv, vv, ux, vy, uy, vx, uux, uvx, uvy, vvy, mdiv;
  Uf.fill_sides();                      // put interior soln on the sides
  Uf.share_sides();
  enforce_bc(Uf);                       // update bc side values
  convective_flux_2d( Uf, Ff );             // compute surface fluxes on sides
  for (LocalSize e=0; e<Uf[0]->ne; e++) {
    U[0] = Uf[0]->el[e];
    U[1] = Uf[1]->el[e];
    F[0] = Ff[0]->el[e];
    F[1] = Ff[1]->el[e];

    const Ordinal qtot = U[0]->qtot;

    u.alias(U[0]->u);
    v.alias(U[1]->u);

    uu.alias(wk1,0*qtot,qtot);
    uv.alias(wk1,1*qtot,qtot);
    vv.alias(wk1,2*qtot,qtot);
    ux.alias(wk1,3*qtot,qtot);
    vy.alias(wk1,4*qtot,qtot);

    uux.alias(wk1,5*qtot,qtot);
    uvx.alias(wk1,6*qtot,qtot);
    uvy.alias(wk1,7*qtot,qtot);
    vvy.alias(wk1,8*qtot,qtot);

    mdiv.alias(wk1,9*qtot,qtot);
    uy.alias(wk1,10*qtot,qtot);
    vx.alias(wk1,11*qtot,qtot);

    dvmul( u, u, uu );
    dvmul( u, v, uv );
    dvmul( v, v, vv );
    U[0]->gradient( u, ux, uy );
    U[1]->gradient( v, vx, vy );
    dvadd( ux, vy, mdiv );
    scale( -one, mdiv );

    U[0]->gradient( uu, uux, 'x');
    U[0]->gradient( uv, uvx, uvy);
    U[0]->gradient( vv, vvy, 'y');

    // F[0]
    dvadd( uux, uvy, F[0]->u );
    dvvtvp( mdiv, u, F[0]->u, F[0]->u );
    dvvtvp( u, ux, F[0]->u, F[0]->u );
    dvvtvp( v, uy, F[0]->u, F[0]->u );
    scale( pt5, F[0]->u);

    // F[1]
    dvadd( uvx, vvy, F[1]->u );
    dvvtvp( mdiv, v, F[1]->u, F[1]->u );
    dvvtvp( u, vx, F[1]->u, F[1]->u );
    dvvtvp( v, vy, F[1]->u, F[1]->u );
    scale( pt5, F[1]->u);

    for (vField::size_type n=0; n<Nfields; ++n) {
      U[n]->lift( F[n], F[n]->u );
    }
  }
}

#endif

/// Computes the Lax-Friedrichs numerical flux (2d)
void Burgers::convective_flux_2d(vField &Uf, vField &Ff) {
  //comm->cout() << "Burgers::convective_flux_2d(...)" << endl;
#ifdef REO_USE_GETSIDEMAPS
  iVector mapl, mapr;
#endif
  Scalar Ul[Nfields], Ur[Nfields], Fpl[Nfields], Fmr[Nfields], Fh[Nfields];
  vector<Side *> sl(Nfields), sr(Nfields);
  vector<Side *> fl(Nfields), fr(Nfields);
  const Scalar fact = pt5;
  for (LocalSize e=0; e<Uf[0]->ne; e++) {
    Element *U = Uf[0]->el[e];
    for (SideLoop S(Uf[0]->el[e]); !S.end(); ++S) {
      if (S.master_side()) {
        for (vField::size_type n=0; n<Nfields; n++) {
          sl[n] = S.side(Uf[n]->el[e]);  // left state side
          sr[n] = S.link(Uf[n]->el[e]);  // right state side
          fl[n] = S.side(Ff[n]->el[e]);  // left flux side
          fr[n] = S.link(Ff[n]->el[e]);  // right flux side
        }
#ifdef REO_USE_GETSIDEMAPS
        get_side_maps( sl[0], sr[0], mapl, mapr );
#endif
        const Ordinal qtot = S.qtot();

        for (Ordinal q=0; q<qtot; ++q) {
#ifdef REO_USE_GETSIDEMAPS
          const Ordinal ql = mapl[q];              // quadrature on the left
          const Ordinal qr = mapr[q];              // quadrature on the right
#else
          const Ordinal ql = U->sideMap(sl[0],q);  // quadrature on the left
          const Ordinal qr = U->sideMap(sr[0],q);  // quadrature on the right
#endif
          const Scalar nx = S.nx(ql); 
          const Scalar ny = S.ny(ql); 

          // left side
          Ul[0] = sl[0]->u[ql];
          Ul[1] = sl[1]->u[ql];

          const Scalar ul = Ul[0];
          const Scalar vl = Ul[1];

          const Scalar unl = ul*nx + vl*ny;
          const Scalar usl = vl*nx - ul*ny;

          sl[0]->u[ql] = Fpl[0] = fact*(unl*unl*nx - usl*unl*ny);
          sl[1]->u[ql] = Fpl[1] = fact*(unl*unl*ny + usl*unl*nx);

          // right side
          Ur[0] = sr[0]->u[qr];
          Ur[1] = sr[1]->u[qr];

          const Scalar ur = Ur[0];
          const Scalar vr = Ur[1];

          const Scalar unr = ur*nx + vr*ny;
          const Scalar usr = vr*nx - ur*ny;

          sr[0]->u[qr] = Fmr[0] = fact*(unr*unr*nx - usr*unr*ny);
          sr[1]->u[qr] = Fmr[1] = fact*(unr*unr*ny + usr*unr*nx);

#if defined(REO_BURGERS_HACK_FLUX)
          const Scalar lmax = pt5;
#elif defined(REO_BURGERS_AVG_FLUX)
          const Scalar lmax = pt5*(fabs(unl)+fabs(unr));
#elif defined(REO_BURGERS_CENTRAL_FLUX)
          const Scalar lmax = zero;
#else
          const Scalar lmax = max(fabs(unl),fabs(unr));
#endif
          // Lax-Friedrichs flux
          Fh[0] = pt5 * ( Fpl[0] + Fmr[0] + lmax * (Ul[0] - Ur[0] ) );
          Fh[1] = pt5 * ( Fpl[1] + Fmr[1] + lmax * (Ul[1] - Ur[1] ) );

          // put fluxes on field sides
          for (vField::size_type n=0; n<Nfields; ++n) {
            sr[n]->u[qr] *= -one;
            fl[n]->u[ql]  =  Fh[n];
            fr[n]->u[qr]  = -Fh[n];
          }
        }
      }
    }
  }
}

/// Computes the Lax-Friedrichs numerical flux
void Burgers::convective_flux(vField &Uf, vField &Ff) {
  //cout << "Burgers::convective_flux(...)" << endl;
  Scalar ul, ur, lmax, fl, fr, fh;
  for (LocalSize e=0; e<Uf[0]->ne; e++) {
    Element *U = Uf[0]->el[e];
    Element *F = Ff[0]->el[e];
    //if (e==0) cout<<e<<": "<<U->side[0]->u[0]<<", "<<U->side[1]->u[0]<<endl;
    for (LocalSize i=0; i<U->nSides(); i++) {
      if (U->side[i]->master()) {
        for (LocalSize q=0; q<U->side[i]->qtot(); q++) {
          const Scalar nx = U->side[i]->nx(q);
          // left side
          ul = U->side[i]->u[q];
          fl = pt5*ul*nx*ul;
          // right side
          ur = U->side[i]->link->u[q];
          fr = pt5*ur*nx*ur;
#if defined(REO_BURGERS_HACK_FLUX)
          lmax = pt5;
#elif defined(REO_BURGERS_AVG_FLUX)
          lmax = pt5*(fabs(ul)+fabs(ur));
#elif defined(REO_BURGERS_CENTRAL_FLUX)
          lmax = zero;
#else
          lmax = max(fabs(ul),fabs(ur));
#endif
          // Lax-Friedrichs flux
          fh = pt5 * ( fl + fr + lmax * (ul - ur) );

          // put numerical flux on the F field sides
          F->side[i]->u[q]       =  fh;
          F->side[i]->link->u[q] = -fh;

          // put interior flux on the U field sides
          U->side[i]->u[q]       =  fl;
          U->side[i]->link->u[q] = -fr;
        }
      }
    }
  }
}

///  Compute (stabilized) Bassi and Rebay diffusive flux
void Burgers::diffusion( vField &Uf, vField &Ff, vField &Rf ) {
  // comm->cout()<<"Burgers::diffusion(...)"<<endl;
  if (mu == 0) return;
  const LocalSize nsd = Uf[0]->nsd();
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
      U->project(ux);                         // lifted ux
#endif
      U->lift( F, uy, 'y' );
#ifdef REO_PROJECT_DIFF_FLUX
      U->project(uy);                         // lifted uy
#endif
      U->lift( F, uz, 'z' );
#ifdef REO_PROJECT_DIFF_FLUX
      U->project(uz);                         // lifted uz
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
      U->project(ux);                         // lifted ux
#endif
      U->lift( F, uy, 'y' );
#ifdef REO_PROJECT_DIFF_FLUX
      U->project(uy);                         // lifted uy
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
      U->project(ux);                         // lifted ux
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
  scale( -one, Ff);                           // Currently on LHS
  add( Ff, Rf );                              // add in viscous contribution
}

/// put the interior penalty flux on the sides
void Burgers::interior_penalty_flux(const vField &Up, const vField &Us,
                                    vField &Uf, const Scalar sigma) {
#ifdef REO_USE_GETSIDEMAPS
  iVector mapl, mapr;
#endif
  for (vField::size_type n=0; n<Us.size(); n++) {
    for (LocalSize e=0; e<Us[n]->ne; e++) {
      const Element * const P = Up[n]->el[e];
      const Element * const S = Us[n]->el[e];
      Element * const F = Uf[n]->el[e];
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
#else
            const Ordinal ql = F->sideMap(sl,q);
            const Ordinal qr = F->sideMap(sr,q);
#endif
            fl->u[ql] = pt5 * (sl->u[ql] - sr->u[qr]) +
                        sigma*(pr->u[qr] - pl->u[ql]);
            fr->u[qr] = -fl->u[ql];
          }
        }
      }
    }
  }
}

/*! \warning Does this work with general side orientations. */
void Burgers::enforce_boundary_penalty(const vField &S, vField &F,
                                       const Scalar sigma) {
  //  cout << "Burgers::enforce_boundary_penalty()" << endl;
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
void Burgers::setup_BCdb( ) {

  // set default BC types
  BC_db["D"].reset( new DirichletBC("D", 0.0) );
  BC_db["F"].reset( new NeumannBC("F", 0.0) );
  BC_db["N"].reset( new NeumannBC("N", 0.0) );
  BC_db["O"].reset( new OutflowBC("O") );
  BC_db["R"].reset( new RobinBC("R",0.0) );

  // read new BC types from file
  string fname = root+".bct";
  ifstream in(fname.c_str());
  if (in) Burgers::read_BCdb( in );   // database of active BC types
}

/// Read in the boundary conditions
void Burgers::read_BCdb( ifstream &in ) {
  //  cout << "Burgers::read_BCdb( ifstream &in )" << endl;
  string tag;
  BC *pbc;
  while ( (pbc = Burgers::make_BC(in,tag)) ) {
    if ( BC_db.find(tag) != BC_db.end() )
      comm->cout() << "Burgers::read_BCdb() Overriding BC type \""
                   << tag << "\"." << endl;
    BC_db[tag].reset( pbc );
  }
}

/// Make the boundary condition objects
BC* Burgers::make_BC( ifstream &in, string &tag ) {
  // cout << "Burgers::make_BC(ifstream &in, string &tag)" << endl;
  string code;
  if (!(in >> code)) return NULL;
  code = lowerCase(code);
  if (code == "dirichlet") {
    if (!(in >> tag)) error("Burgers::make_BC() Cannot read Dirichlet tag");
    return new DirichletBC(tag,in);
  } else if (code == "neumann") {
    if (!(in >> tag)) error("Burgers::make_BC()  Cannot read Neumann tag");
    return new NeumannBC(tag,in);
  } else if (code == "robin") {
    if (!(in >> tag))
      error("Burgers::make_BC() Cannot read Robin tag");
    return new RobinBC(tag,in);
  } else if (code == "dirichletcontrol") {
    if (!(in >> tag))
      error("Burgers::make_BC() Cannot read DirichletControl tag");
    return new DirichletControlBC(tag,in);
  } else if (code == "neumanncontrol") {
    if (!(in >> tag))
      error("Burgers::make_BC() Cannot read NeumannControl tag");
    return new NeumannControlBC(tag,in);
  } else if (code == "robincontrol") {
    if (!(in >> tag))
      error("Burgers::make_BC() Cannot read RobinControl tag");
    return new RobinControlBC(tag,in);
  } else if (code == "steadydirichletcontrol") {
    if (!(in >> tag))
      error("Burgers::make_BC() Cannot read SteadyDirichletControl tag");
    return new SteadyDirichletControlBC(tag,in);
  } else if (code == "steadyneumanncontrol") {
    if (!(in >> tag))
      error("Burgers::make_BC() Cannot read SteadyNeumannControl tag");
    return new SteadyNeumannControlBC(tag,in);
  } else if (code == "steadyrobincontrol") {
    if (!(in >> tag))
      error("Burgers::make_BC() Cannot read SteadyRobinControl tag");
    return new SteadyRobinControlBC(tag,in);
  } else {
    error("Burgers::make_BC() Illegal BC type:  "+code);
  }
  return NULL;
}

/// Construct source terms
Source::Ptr Burgers::make_Source( ifstream &in, string &tag ) {
  string code;
  Source::Ptr p;
  if (!(in >> code)) return p;
  while (code[0]=='#') {  // eat comment lines
    string buffer;
    getline(in,buffer);
    if (!(in >> code)) return p;
  }
  if (lowerCase(code) == "constant") {
    if (!(in >> tag)) error("Burgers::Cannot read ConstSource tag");;
    p.reset( new ConstSource(tag,in,1) );
  } else if (lowerCase(code) == "function") {
    if (!(in >> tag)) error("Burgers::Cannot read FuncSource tag");;
    p.reset( new FuncSource(tag,in,1) );
  } else if (lowerCase(code) == "distributedcontrol") {
    if (!(in >> tag)) error("Burgers::Cannot read distributedcontrol tag");
    p.reset( new DistributedControl(tag, in, U) );
  } else if (lowerCase(code) == "steadydistributedcontrol") {
    if (!(in >> tag))
      error("Burgers::Cannot read steady distributedcontrol tag");
    p.reset( new SteadyDistributedControl(tag, in, U) );
  } else {
    error("Burgers::make_Source() Illegal Source type");
  }
  return p;
}

// Add source terms
void Burgers::add_source(const vField &Us, vField &Ur) {
  // cout << "Burgers::add_source(vField &)" << endl;
  for (Source::db_citr i=Source_db.begin(); i!= Source_db.end(); ++i) {
    // cout << "Adding source: " << i->first << endl;
    i->second->apply( t, Us, Ur );
  }
}

/// Set the field from a file
void Burgers::set_ic(vField &F, string ext) {
  t = 0.0; step = 0;
  string fname = root+ext;
  ifstream in(fname.c_str());
  if (!in) {
    comm->cerr() << "Could not open initial condition " << fname << endl;
    comm->exit(DGM::FAILURE);
  }
  string buffer, code;
  getline(in,buffer);
  if (!(in>>code)) error("Cannot read IC code");
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
  } else if (lowerCase(code) == "shock") {
    ShockIC shock;
    for (LocalSize e=0; e<ne; e++) {
      for (LocalSize q=0; q<F[0]->el[e]->qtot; q++) {
        F[0]->el[e]->u[q] += shock.eval( (*F[0]->el[e]->C)[q] );
      }
    }
  } else if (lowerCase(code) == "cockburnshock") {
    CockburnShockIC shock;
    for (LocalSize e=0; e<ne; e++) {
      for (LocalSize q=0; q<F[0]->el[e]->qtot; q++) {
        F[0]->el[e]->u[q] += shock.eval( (*F[0]->el[e]->C)[q] );
      }
    }
  } else if (lowerCase(code) == "step") {
    StepIC ic;
    for (LocalSize e=0; e<ne; e++) {
      for (LocalSize q=0; q<F[0]->el[e]->qtot; q++) {
        F[0]->el[e]->u[q] += ic.eval( (*F[0]->el[e]->C)[q] );
      }
    }
  } else {
    comm->error("Burgers:set_ic()  Unsupported IC type");
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
