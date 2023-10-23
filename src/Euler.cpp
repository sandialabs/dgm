/*=============================================================================
  Module:     Euler Module

  Contact:    S. Scott Collis
              sscoll@sandia.gov

  Copyright:  (c)2003 Rice University
              (c)2008-2013 Sandia National Laboratories
=============================================================================*/

/** \file Euler.cpp
    \brief Implementation of the 2d Euler equations
    \author S. Scott Collis
*/

// local includes
#include "Reo.hpp"
#include "Euler.hpp"
#include "EulerIC.hpp"
#include "EulerBC.hpp"
#include "Wavetype.hpp"
#include "Fluid.hpp"

// DGM includes
#include "Edge.hpp"
#include "Side.hpp"
#include "Vertex.hpp"

namespace Reo {

using namespace DGM;

#ifdef DGM_DOXYGEN
/// Print out detailed flux information
#define DGM_VERBOSE_FLUX
#endif

/// A simple class for size tests
template <typename T>
class Trial {
public:
  T a;
  T b;
};

/// Constructor
Euler::Euler(DGM::ArgList &args, const DGM::Comm::Ptr comm_, const int p_inc) :
  Domain(args, comm_), flux(LaxFriedrichs) {
  const int verb(comm->verbosity());
  Stopwatch cpu; cpu.start();
  if (verb) comm->cout() << "Building Euler domain..." << endl;

  // Memory diagnostics
  if (verb>1) {
    comm->cout() << "  Size of Element = " << sizeof(Element) << endl;
    comm->cout() << "  Size of Tri = " << sizeof(Tri) << endl;
    comm->cout() << "  Size of Edge = " << sizeof(Edge) << endl;
    comm->cout() << "  Size of Side = " << sizeof(Side) << endl;
    comm->cout() << "  Size of Vertex = " << sizeof(Vertex) << endl;
    comm->cout() << "  Size of Euler = " << sizeof(Euler) << endl;
    comm->cout() << "  Size of Field = " << sizeof(Field) << endl;
    comm->cout() << "  Size of vField = " << sizeof(vField) << endl;
    comm->cout() << "  Size of dVector = " << sizeof(dVector) << endl;
    comm->cout() << "  Size of Vector<Scalar,size_t> = "
                 << sizeof(CMC::Vector<Scalar,size_t>) << endl;
    comm->cout() << "  Size of Vector<Scalar,int> = "
                 << sizeof(CMC::Vector<Scalar,int>) << endl;
    comm->cout() << "  Size of Vector<float,int> = "
                 << sizeof(CMC::Vector<float,int>) << endl;
    comm->cout() << "  Size of DGM::Size = " << sizeof(DGM::Size) << endl;
    comm->cout() << "  Size of DGM::Ordinal = " << sizeof(DGM::Ordinal) << endl;
    comm->cout() << "  Size of DGM::Side::Info<Size,Ordinal,Scalar> = "
                 << sizeof(DGM::Side::Info<Size,Ordinal,Scalar>) << endl;
    comm->cout() << "  Size of DGM::Side::Info<Size,Ordinal,Scalar>::Ptr = "
                 << sizeof(DGM::Side::Info<Size,Ordinal,Scalar>::Ptr) << endl;
    comm->cout() << "  Size of DGM::Trial<int> = "
                 << sizeof(Reo::Trial<int>) << endl;
    comm->cout() << "  Size of DGM::Trial<size_t> = "
                 << sizeof(Reo::Trial<size_t>) << endl;
  }

  // set vField names
  U.set_name("U");
  Ut.set_name("Ut");

  // set discretization
  Ordinal p, q;
  p = params["p"];                     // polynomial order
  p += p_inc;                          // increment p if requested
  if ( !(q=params["q"]) ) q = p + 2;   // number of quadrature points
  nsd = params["nsd"];                 // number of space dimensions

  params["auxout"] = 0;                // Compute derivative quantities
  params["incjump"] = 1;               // whether to include jumps in div/vort
  params["plot3d_x"] = 1;              // plot3d grid file
  params["plot3d_q"] = 1;              // plot3d mesh file

  params.get("flux", "LaxFriedrichs"); // Numerical flux
  params.get("filter", false);         // Whether to filter solution

  // read arguments (overrides defaults and input file)
  parse_args( args );

  gamma = params["gamma"];             // ratio of specific heats

  // Numerical fluxes
  string value = (string)params["flux"];
  if (lowerCase(value).compare("laxfriedrichs") == 0)
    flux = LaxFriedrichs;
  else if (lowerCase(value).compare("stegerwarming") == 0)
    flux = StegerWarming;
  else if (lowerCase(value).compare("vanleer") == 0)
    flux = vanLeer;
  else if (lowerCase(value).compare("roe") == 0)
    flux = Roe;
  else
    comm->error("Reo::Euler::Unknown numerical flux");

  vector<string> field_names;          // Field names
  field_names.push_back("r");

  // build a Field of Elements and Sides
  if (params["imesh"]) {
    Mesh mesh(params);
    U.push_back( new Field(p, q, mesh, root, field_names[0],
                           Field::FULL, comm ) );
    partition = U[0]->partition;
  } else if (params["bmesh"]) {
    U.push_back( new Field(p, q, root, field_names[0], partition, 1,
                           Reo::NumEqntype, p2i(EULER), comm ) );
  } else {
    U.push_back( new Field(p, q, root, field_names[0], partition, comm ) );
  }

  // set some additional domain parameters
  ne = U[0]->ne;
  nsd = U[0]->nsd();    params["nsd"] = nsd;

#ifdef REO_USE_GETSIDEMAPS
  setup_side_maps();
#endif

  if (nsd == 1) {
    comm->error("Reo::Euler: nsd must be 2");
  } else if (nsd == 2) {
    Nfields = 4;  // is equal to NFIELDS in Euler.hpp
    field_names.push_back("ru");
    field_names.push_back("rv");
    field_names.push_back("rE");
  } else if (nsd == 3) {
    comm->error("Reo::Euler: nsd must be 2");
  } else {
    comm->cerr() << "Illegal value for nsd = " << nsd
                 << " in Reo::Euler::Euler" << endl;
    comm->exit(DGM::FAILURE);
  }

  // build the rest of the vector field
  for (vField::size_type i=1; i<Nfields; i++) {
    // comm->cout() << "Push back field " << field_names[i] << endl;
    U.push_back( new Field( U[0], root, field_names[i] ) );
  }

  // make auxiliary Fields using copy constructor
  for (vField::size_type i=0; i<Nfields; i++) {
    // comm->cout() << "Push back auxiliary field " << field_names[i] << endl;
    Ut.push_back( new Field( U[i], root, field_names[i] ) );
  }

  // optionally make storage contiguous
  if (json_domain["Space"]["Contiguous Memory Storage"].asBool()) {
    comm->cout() << "  Making U vField contiguous" << endl;
    U.reset_storage();
    Ut.reset_storage();
  }

  // allocate workspace
  wk1.resize(5*max(Lmax(),Qmax()));
  wk2.resize(5*max(Lmax(),Qmax()));

  CMC::Stopwatch timer;

  // make sure that storage is initialized
  timer.start();
  zero_all_fields();
  if (verb)
    comm->cout() << "Zero fields in " << timer.restart() << " seconds" << endl;

  // make analysis object
  response = Response::factory(U, this);
  if (verb)
    comm->cout() << "Built Response in " << timer.restart()
                 << " seconds" << endl;

  setup_BCdb();            // setup BC database
  if (verb)
    comm->cout() << "Built BCs in " << timer.restart() << " seconds" << endl;

  setup_Sourcedb();        // setup Source term database
  if (verb)
    comm->cout() << "Built Sources in " << timer.restart()
                 << " seconds" << endl;

  timer.restart();
  set_TimeInt();
  if (verb) comm->cout() << "Built Time integrator in " << timer.restart()
                         << " seconds" << endl;

  if (verb) comm->cout() << "Completed Euler construction in " << cpu.stop()
                         << " seconds"<< endl;
}

/// Parse parameters from the argument list
void Euler::parse_args( DGM::ArgList &args ) {
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
        params["auxout"] = 1;
      } else if (name == "-nojump") {
        li.push_back(a);
        params["incjump"] = 0;
      } else if (name == "-filter") {
        li.push_back(a);
        params["filter"] = true;
      } else if (name == "-flux") {
        li.push_back(a);
        value = *(++a);
        li.push_back(a);
        params["flux"] = value;
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

Euler::~Euler() {
  if (fluid) delete fluid;
}

void Euler::showUsage() {
  comm->cout()
    << "Reo::Euler Class Options \n"
    << "----------------------------------------------------------------\n"
    << "-nox     " << '\t' << "No grid file                             \n"
    << "-noq     " << '\t' << "No solution file                         \n"
    << "-aux     " << '\t' << "Auxiliary output file                    \n"
    << "-nojump  " << '\t' << "Do not include jumps in div/vort         \n"
    << "-filter  " << '\t' << "Apply spectral filter                    \n"
    << "-flux    " << '\t' << "Select the numerical flux                \n"
    << "----------------------------------------------------------------\n";
}

void Euler::set_material() {
  fluid = new ConstProp(gamma);
  material = fluid;
#ifdef DGM_TEST_FLUID
  cout << "ConstProp::gamma() = " << fluid->gamma() << endl;
  cout << "ConstProp::Ma_ref() = " << fluid->Ma() << endl;
  cout << "ConstProp::Rgas() = " << fluid->Rgas() << endl;
  cout << "ConstProp::cp() = " << fluid->cp(0) << endl;
  cout << "ConstProp::cv() = " << fluid->cv(0) << endl;
#endif
}

void Euler::time_derivative( vField &Us, vField &Uf ) {
  convection( Us, Uf );
  add_source( Us, Uf );
  project( Uf );
  if (params["filter"]) Uf.exp_filter(0.75,3.0);
}

/// Evaluate the convection term
/** See: E.F. Toro, "Riemann Solvers and Numerical Methods for Fluid
    Dynamics," 2nd Edition, Springer, 1999, Chapter 3 for a detailed
    description of the Euler equations.  In general, we follow the now
    standard notation presented therein except that we use S for the state
    vector of conservation variables in lieu of U since U is used for
    the solution vector field at the Domain level. */
void Euler::convection( vField &Us, vField &Uf ) {
#ifdef DGM_TIME_EULER
  static FunctionTimer T("Euler::convection");
  FunctionSentry sentry(T);
#endif
  Element *S[NFIELDS], *F[NFIELDS];
  dVector u, v, p, d, d1;
  dVector r, ru, rv, rE;
  const Scalar gm1 = gamma-one;
  const Scalar mpt5gm1 = -pt5*gm1;
  Us.fill_sides();
#ifdef USE_EULER_BC
  // The purpose of this compiler define is to override the default behavior
  // where the Euler BC's are enforced during the convection phase and the NS
  // BCs are used in the diffusion term.  This is useful when performing
  // optimization, although I still do not understand why this is
  // necessary. [SSC]
  Euler::enforce_bc(Us);
#else
  enforce_bc(Us);
#endif
  Us.begin_share_sides();
  // Add the interior contribution
  for (LocalSize e=0; e<Us[0]->ne; e++) {
    S[0] = Us[0]->el[e]; // local version of the state
    S[1] = Us[1]->el[e];
    S[2] = Us[2]->el[e];
    S[3] = Us[3]->el[e];

    F[0] = Uf[0]->el[e]; // local version of the flux
    F[1] = Uf[1]->el[e];
    F[2] = Uf[2]->el[e];
    F[3] = Uf[3]->el[e];

    const Ordinal qtot = S[0]->qtot;

    r.alias (S[0]->u);  // rho
    ru.alias(S[1]->u);  // rho u
    rv.alias(S[2]->u);  // rho v
    rE.alias (S[3]->u); // total Energy density

    u.alias(wk1,0,qtot);
    v.alias(wk1,qtot,qtot);
    p.alias(wk1,2*qtot,qtot);
    d.alias(wk1,3*qtot,qtot);
    d1.alias(wk1,4*qtot,qtot);

    dvdiv(ru, r, u);    // compute u
    dvdiv(rv, r, v);    // compute v

    // p = (gamma-1.0)*(rE-0.5*(r*u*u + r*v*v))
    dvmul(u, ru, p);
    dvmul(v, rv, d);
    dvadd(d, p);
    scale(mpt5gm1, p);
    daxpy(gm1, rE, p);

    // F[0] = (ru),x + (rv),y
    S[0]->gradient(ru, F[0]->u, 'x');
    S[0]->gradient(rv, d, 'y');
    dvadd(d, F[0]->u);

    // F[1] = (ru*u+p),x + (ru*v),y
    dvmul(ru, u, d);
    dvadd(p, d);
    S[1]->gradient(d, F[1]->u, 'x');
    dvmul(ru, v, d);
    S[1]->gradient(d, d1, 'y');
    dvadd(d1, F[1]->u);

    // F[2] = (rv*u),x + (rv*v+p),y
    dvmul(rv, u, d);
    S[2]->gradient(d, F[2]->u, 'x');
    dvmul(rv, v, d);
    dvadd(p, d);
    S[2]->gradient(d, d1, 'y');
    dvadd( d1, F[2]->u );

    // F[3] = (u*(rE+p)),x + (v*(rE+p)),y
    dvadd(rE, p);
    dvmul(u, p, d);
    S[3]->gradient(d, F[3]->u, 'x');
    dvmul(v, p, d);
    S[3]->gradient(d, d1, 'y');
    dvadd( d1, F[3]->u );
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

/// Compute the Euler convectiveflux
/** For descriptions of the numerical fluxes See: E.F. Toro, "Riemann
    Solvers and Numerical Methods for Fluid Dynamics," 2nd Edition,
    Springer, 1999.  In particular, see section 3.2 for the
    multi-dimensional Euler equations, Chapter 8 for flux vector splitting
    methods such as Steger-Warming and van Leer, and Chapter 11 for the Roe
    method. */
void Euler::convective_flux(vField &Us, vField &Uf) {
#ifdef DGM_TIME_EULER
  static FunctionTimer T("Euler::convective_flux");
  FunctionSentry sentry(T);
#endif
#ifdef REO_USE_GETSIDEMAPS
  iVector mapl, mapr;
#endif
#define REO_EULER_USE_STACK_VARS
#ifdef REO_EULER_USE_STACK_VARS
  Scalar Ul[NFIELDS], Ur[NFIELDS];
  Scalar Fh[NFIELDS], Gh[NFIELDS], Fpl[NFIELDS], Fmr[NFIELDS];
  Scalar lambda[NFIELDS], alpha[NFIELDS];
  for (vField::size_type n=0; n<Nfields; ++n) Fh[n]=zero;
#else
  vector<Scalar> Ul(Nfields), Ur(Nfields);
  vector<Scalar> Fh(Nfields), Gh(Nfields), Fpl(Nfields), Fmr(Nfields);
  vector<Scalar> lambda(Nfields), alpha(Nfields);
#endif
#undef REO_EULER_USE_STACK_VARS
  Scalar rl, rul, rvl, rEl, ul, vl, pl, Hl;
  Scalar rr, rur, rvr, rEr, ur, vr, pr, Hr;
  vector<Side *> sl(Nfields), sr(Nfields);
  vector<Side *> fl(Nfields), fr(Nfields);
  const Scalar gm1=gamma-one;
#ifdef TRY_NUMERICAL_FLUX
  NumericalFlux<Scalar,int> LF(gamma,type);
#endif
  for (LocalSize e=0; e<ne; ++e) {         // loop over elements
    Element *U = Us[0]->el[e];
    for (SideLoop S(U); !S.end(); ++S) {
      if (S.master_side()) {
        const Ordinal qtot = S.qtot();
        // localize the state and flux sides
        for (vField::size_type n=0; n<Nfields; ++n) {
          sl[n] = S.side(Us[n]->el[e]);    // left state side
          sr[n] = S.link(Us[n]->el[e]);    // right state side
          fl[n] = S.side(Uf[n]->el[e]);    // left flux side
          fr[n] = S.link(Uf[n]->el[e]);    // right flux side
        }
#ifdef REO_USE_GETSIDEMAPS
        get_side_maps( sl[0], sr[0], mapl, mapr );
#endif
        for (Ordinal q=0; q<qtot; ++q) {          // loop over side quad-pts
#ifdef REO_USE_GETSIDEMAPS
          const Ordinal ql = mapl[q];             // quadrature on the left
          const Ordinal qr = mapr[q];             // quadrature on the right
#else
          const Ordinal ql = U->sideMap(sl[0],q); // quadrature on the left
          const Ordinal qr = U->sideMap(sr[0],q); // quadrature on the left
#endif
          const Scalar nxl = sl[0]->nx(ql);
          const Scalar nyl = sl[0]->ny(ql);

          // compute normal flux from interior (left)

          // left state
          Ul[0] = sl[0]->u[ql];                   // rho
          Ul[1] = sl[1]->u[ql];                   // rho u
          Ul[2] = sl[2]->u[ql];                   // rho v
          Ul[3] = sl[3]->u[ql];                   // E

          // left state projected to the normal
          rl  = Ul[0];                            // density
          rul = Ul[1]*nxl + Ul[2]*nyl;            // normal momentum
          rvl = Ul[2]*nxl - Ul[1]*nyl;            // tangent momentum
          rEl = Ul[3];                            // total energy per volume

          // left primative variables (projected to left normal)
          const Scalar irl = one/rl;
          ul = irl*rul;                           // normal velocity
          vl = irl*rvl;                           // tangent velocity
          pl = gm1*(rEl - pt5*(rul*ul + rvl*vl)); // pressure
          Hl = irl*(rEl + pl);                    // total enthalpy
#if 0
          comm->cout()<<"L:"<<partition->eid(e)<<":"<<i<<" "
                      <<rl<<" "<<ul<<" "<<vl<<" "<<pl<<" "<<Hl
                      <<" nx="<<nxl<<" ny="<<nyl<<endl;
#endif
          // make sure that density and pressure are realizable
          if (rl < aepsM) {
            comm->cerr()<<"Element: "<<partition->eid(e)<<", Side: "
                        << S.s <<", Density (l): "<<rl<<endl;
            comm->abort();
          }
          if (pl < aepsM) {
            comm->cerr()<<"Element: "<<partition->eid(e)<<", Side: "
                        << S.s <<", Pressure (l): "<<pl<<endl;
            comm->abort();
          }

          // put the left flux on the left state sides
          sl[0]->u[ql] = Fpl[0] = rul;
          sl[1]->u[ql] = Fpl[1] = (rul*ul+pl)*nxl - (rvl*ul)*nyl;
          sl[2]->u[ql] = Fpl[2] = (rul*ul+pl)*nyl + (rvl*ul)*nxl;
          sl[3]->u[ql] = Fpl[3] = ul*(rEl + pl);

          // compute normal flux from exterior (right)

          // right state
          Ur[0] = sr[0]->u[qr];
          Ur[1] = sr[1]->u[qr];
          Ur[2] = sr[2]->u[qr];
          Ur[3] = sr[3]->u[qr];

          // normal right state (note that left normal is used!)
          rr = Ur[0];
          rur = Ur[1]*nxl + Ur[2]*nyl;
          rvr = Ur[2]*nxl - Ur[1]*nyl;
          rEr = Ur[3];

          // right primative variables (projected to left normal)
          const Scalar irr=one/rr;
          ur = irr*rur;
          vr = irr*rvr;
          pr = gm1*(rEr - pt5*(rur*ur + rvr*vr));
          Hr = irr*(rEr + pr);
#if 0
          comm->cout()<<"R:"<<partition->eid(e)<<":"<<S.s<<" "
                      <<rr<<" "<<ur<<" "<<vr<<" "<<pr<<" "<<Hr<<endl;
#endif
          // make sure that density and pressure are realizable
          if (rr < aepsM) {
            comm->cerr()<<"Element: "<<partition->eid(e)<<", Side: "<< S.s
                        <<", Density (r): "<<rr<<" aepsM: "<<aepsM<<endl;
            comm->abort();
          }
          if (pr < aepsM) {
            comm->cerr()<<"Element: "<<partition->eid(e)<<", Side: "<< S.s
                        <<", Pressure (r): "<<pr<<endl;
            comm->abort();
          }

          // put the left flux on the left state sides
          sr[0]->u[qr] = Fmr[0] = rr*ur;
          sr[1]->u[qr] = Fmr[1] = (rur*ur+pr)*nxl - (rvr*ur)*nyl;
          sr[2]->u[qr] = Fmr[2] = (rur*ur+pr)*nyl + (rvr*ur)*nxl;
          sr[3]->u[qr] = Fmr[3] = ur*(rEr + pr);

#ifdef TRY_NUMERICAL_FLUX
          // test of the new class to compute the fluxes
          dVector N(2);
          N[0] = nxl; N[1] = nyl;
          LF.evaluate( Ul, Ur, N, Fpl, Fmr, Fh );
#else
          switch (flux) {
          case LaxFriedrichs: {
            Scalar lmax = zero;

            const Scalar al = sqrt(gm1*(Hl - pt5*(ul*ul + vl*vl)));
            lambda[0] = ul-al;
            lambda[1] = ul;
            lambda[2] = ul;
            lambda[3] = ul+al;
            for(vField::size_type n=0; n<Nfields; ++n)
              lmax=max(lmax,fabs(lambda[n]));

            const Scalar ar = sqrt(gm1*(Hr - pt5*(ur*ur + vr*vr)));
            lambda[0] = ur-ar;
            lambda[1] = ur;
            lambda[2] = ur;
            lambda[3] = ur+ar;
            for(vField::size_type n=0; n<Nfields; ++n)
              lmax=max(lmax,fabs(lambda[n]));

            // Lax-Friedrichs flux
            Fh[0] = pt5 * ( Fpl[0] + Fmr[0] + lmax * ( Ul[0] - Ur[0] ) );
            Fh[1] = pt5 * ( Fpl[1] + Fmr[1] + lmax * ( Ul[1] - Ur[1] ) );
            Fh[2] = pt5 * ( Fpl[2] + Fmr[2] + lmax * ( Ul[2] - Ur[2] ) );
            Fh[3] = pt5 * ( Fpl[3] + Fmr[3] + lmax * ( Ul[3] - Ur[3] ) );

#ifdef DGM_VERBOSE_FLUX
            cout << "Lax-Friedrichs: Element " << e << ", Side " << i << endl;
            cout << Fh[0]<< ", "<<Fh[1]<<", "<<Fh[2]<< ", "<<Fh[3]<<endl;
#endif
            break;
          }
          case StegerWarming: { // Steger-Warming splitting, see Toro p.275

            { // positive flux on left side
              const Scalar r = rl;
              const Scalar u = ul;
              const Scalar v = vl;
              const Scalar H = Hl;
              const Scalar a = sqrt((gamma-one)*(H - pt5*(u*u + v*v)));

              // get the positive eigenvalues
              lambda[0] = max(u-a,zero);
              lambda[1] = max(u,zero);
              lambda[2] = max(u,zero);
              lambda[3] = max(u+a,zero);

              const Scalar c1 = pt5*r/gamma;
              const Scalar c2 = two*(gamma-one);
              Fpl[0] = c1*(lambda[0] + c2*lambda[1] + lambda[3]);
              Fpl[1] = c1*((u-a)*lambda[0] + c2*u*lambda[1] + (u+a)*lambda[3]);
              Fpl[2] = c1*(v*lambda[0] + c2*v*lambda[1] + v*lambda[3]);
              Fpl[3] = c1*((H-u*a)*lambda[0] + (gamma-one)*(u*u+v*v)*lambda[1]
                           + (H+u*a)*lambda[3]);
            }
            { // negative flux on right side
              const Scalar r = rr;
              const Scalar u = ur;
              const Scalar v = vr;
              const Scalar H = Hr;
              const Scalar a = sqrt((gamma-one)*(H - pt5*(u*u + v*v)));

              // get the negative eigenvalues
              lambda[0] = min(u-a,zero);
              lambda[1] = min(u,zero);
              lambda[2] = min(u,zero);
              lambda[3] = min(u+a,zero);

              const Scalar c1 = pt5*r/gamma;
              const Scalar c2 = two*(gamma-one);
              Fmr[0] = c1*(lambda[0] + c2*lambda[1] + lambda[3]);
              Fmr[1] = c1*((u-a)*lambda[0] + c2*u*lambda[1] + (u+a)*lambda[3]);
              Fmr[2] = c1*(v*lambda[0] + c2*v*lambda[1] + v*lambda[3]);
              Fmr[3] = c1*((H-u*a)*lambda[0] + (gamma-one)*(u*u+v*v)*lambda[1]
                           + (H+u*a)*lambda[3]);
            }

            // Godunov upwind flux in normal coordinates
            Gh[0] = Fpl[0] + Fmr[0];
            Gh[1] = Fpl[1] + Fmr[1];
            Gh[2] = Fpl[2] + Fmr[2];
            Gh[3] = Fpl[3] + Fmr[3];

            // reconstruct local flux in native coordinates
            Fh[0] = Gh[0];
            Fh[1] = Gh[1]*nxl - Gh[2]*nyl;
            Fh[2] = Gh[1]*nyl + Gh[2]*nxl;
            Fh[3] = Gh[3];

#ifdef DGM_VERBOSE_FLUX
            cout << "Steger-Warming: Element " << e << ", Side " << i << endl;
            cout << Fh[0]<<", "<<Fh[1]<<", "<<Fh[2]<<", "<<Fh[3]<<endl;
#endif
            break;
          }
          case vanLeer: { // van Leer splitting, see Toro p.276.

            // van Leer flux vector splitting (positive flux on left side)
            const Scalar al = sqrt((gamma-one)*(Hl - pt5*(ul*ul + vl*vl)));
            const Scalar Ml = ul/al;
            const Scalar c1l = pt25*rl*al*(one+Ml)*(one+Ml);
            const Scalar c2l = 0.5*(gamma-one)*Ml+one;
            const Scalar igamma = one/gamma;

            Fpl[0] = c1l;
            Fpl[1] = c1l*two*al*igamma*c2l;
            Fpl[2] = c1l*vl;
            Fpl[3] = c1l*(two*al*al/(gamma*gamma-one)*c2l*c2l + pt5*vl*vl);

            // van Leer flux vector splitting (negative flux on right side)
            const Scalar ar = sqrt((gamma-one)*(Hr - pt5*(ur*ur + vr*vr)));
            const Scalar Mr = ur/ar;
            const Scalar c1r = -pt25*rr*ar*(one-Mr)*(one-Mr);
            const Scalar c2r = pt5*(gamma-one)*Mr-one;

            Fmr[0] = c1r;
            Fmr[1] = c1r*two*ar/gamma*c2r;
            Fmr[2] = c1r*vr;
            Fmr[3] = c1r*(two*ar*ar/(gamma*gamma-one)*c2r*c2r + pt5*vr*vr);

            // Godunov upwind flux in normal coordinates
            Gh[0] = Fpl[0] + Fmr[0];
            Gh[1] = Fpl[1] + Fmr[1];
            Gh[2] = Fpl[2] + Fmr[2];
            Gh[3] = Fpl[3] + Fmr[3];

            // reconstruct local flux in native coordinates
            Fh[0] = Gh[0];
            Fh[1] = Gh[1]*nxl - Gh[2]*nyl;
            Fh[2] = Gh[1]*nyl + Gh[2]*nxl;
            Fh[3] = Gh[3];

#ifdef DGM_VERBOSE_FLUX
            cout << "van Leer: Element " << e << ", Side " << i << endl;
            cout << Fh[0]<< ", "<<Fh[1]<< ", "<<Fh[2]<< ", "<<Fh[3]<<endl;
#endif
            break;
          }
          case Roe: {  // Roe average flux (no entropy fix), see Toro p. 352
            /// \todo add the entropy fix to the Roe flux, this confuses me...

            const Scalar gm1 = (gamma-one);
            const Scalar R = sqrt(rr/rl);            // Roe factor
            const Scalar iRp1 = one/(one+R);
            const Scalar u = (ul + R*ur)*iRp1;       // normal velocity
            const Scalar v = (vl + R*vr)*iRp1;       // tangent velocity
            const Scalar H = (Hl + R*Hr)*iRp1;       // enthalpy
            const Scalar a2 = gm1*(H - pt5*(u*u + v*v));
            const Scalar a = sqrt(a2);               // speed of sound
            const Scalar ainv = one/a;               // inverse speed of sound
            const Scalar c1 = gm1*ainv*ainv;
            const Scalar c1inv = one/c1;

            // Compute the wave strengths
            alpha[2] = (rvr-rvl)-v*(rr-rl);
            alpha[1] = (gamma-one)*ainv*ainv*((rr-rl)*(H-u*u)+u*(rur-rul) -
                                      ((rEr-rEl)-((rvr-rvl)-v*(rr-rl))*v));
            alpha[0] = pt5*ainv*((rr-rl)*(u+a)-(rur-rul)-a*alpha[1]);
            alpha[3] = (rr-rl)-(alpha[0]+alpha[1]);

            // get the negative eigenvalues
            lambda[0] = min(u-a,zero);
            lambda[1] = min(u,zero);
            lambda[2] = min(u,zero);
            lambda[3] = min(u+a,zero);

            // right eigenvectors scaled by wave strengths and eigenvalues,
            // see Toro, p. 346, (11.27)
            Gh[0] = lambda[0]*alpha[0];
            Gh[1] = lambda[0]*(u-a)*alpha[0];
            Gh[2] = lambda[0]*v*alpha[0];
            Gh[3] = lambda[0]*(H-u*a)*alpha[0];

            Gh[0] += lambda[1]*alpha[1];
            Gh[1] += lambda[1]*u*alpha[1];
            Gh[2] += lambda[1]*v*alpha[1];
            Gh[3] += lambda[1]*(H-c1inv)*alpha[1];

            Gh[2] += lambda[2]*alpha[2];
            Gh[3] += lambda[2]*v*alpha[2];

            Gh[0] += lambda[3]*alpha[3];
            Gh[1] += lambda[3]*(u+a)*alpha[3];
            Gh[2] += lambda[3]*v*alpha[3];
            Gh[3] += lambda[3]*(H+u*a)*alpha[3];

            // reconstruct local flux
            Fh[0] = Fpl[0] + Gh[0];
            Fh[1] = Fpl[1] + Gh[1]*nxl - Gh[2]*nyl;
            Fh[2] = Fpl[2] + Gh[1]*nyl + Gh[2]*nxl;
            Fh[3] = Fpl[3] + Gh[3];

#ifdef DGM_VERBOSE_FLUX
            cout << "Roe     : Element " << e << ", Side " << i << endl;
            cout << Fh[0]<<", "<<Fh[1]<<", "<<Fh[2]<<", "<<Fh[3]<<endl;
#endif
            break;
          }
          default:
            comm->error("Illegal value of flux type");
            break;
          }
#endif
          // put fluxes on field sides
          for (vField::size_type n=0; n<Nfields; ++n) {
            sr[n]->u[qr] *= -one;        // correct for right normal
            fl[n]->u[ql]  =  Fh[n];      // upwind flux
            fr[n]->u[qr]  = -Fh[n];      // correct for right normal
          }
        }
      }
    }
  }
}

/// Generate plot output
/** \todo Not all writers work in parallel */
int Euler::plot(const string &rst) {
  string fname, name(rst), caption;
  char buf[80];
  read( rst, U );
  size_t loc = name.find(".rst");
  if ( loc != string::npos )
    name.erase(loc);
  sprintf(buf,"%s.dat",name.c_str()); fname = buf;
  sprintf(buf,"State variables at t =%11.4e, step = %lld",t,(long long)step);
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
  if (params["auxout"]) {
    compute_vorticity();    // puts auxiliary variables (i.e. vorticity) in Ut
    if (params["tecplot"]) {
      sprintf(buf,"%s.aux.dat",name.c_str()); fname = buf;
      sprintf(buf,"Auxiliary variables at t =%11.4e, step = %lld",t,
              numeric_cast<long long>(step)); caption = buf;
      if (comm->Master()) Ut.tecplot(fname,caption);
    }
    if (params["paraview"]) {
      sprintf(buf,"%s.aux",name.c_str()); fname = buf;
      sprintf(buf,"Auxiliary variables at t =%11.4e, step = %lld",t,
              numeric_cast<long long>(step)); caption = buf;
      Ut.paraview(fname,caption);
    }
  }
  return 0;
}

/** This is rather expensive and many of these steps are already done
    in the convection phase. */
Scalar Euler::set_time_step(vField &U) {
  // cout << "Euler::set_time_step()" << endl;
  Scalar cfl = 0;
#ifdef DGM_STORE_METRICS
  Element *S;
  dVector r, ru, rv, rE;
  dVector u, v, c, wk, idt;

  if (dtl.size()==0) dtl.resize(U[0]->ne);  // make space for local dt

  for (LocalSize e=0; e<ne; e++) {
    S = U[0]->el[e];
    const int qtot = S->qtot;

    r.alias (U[0]->el[e]->u);  // rho
    ru.alias(U[1]->el[e]->u);  // rho u
    rv.alias(U[2]->el[e]->u);  // rho v
    rE.alias (U[3]->el[e]->u); // total Energy density

    u.alias(wk1,0,qtot);
    v.alias(wk1,qtot,qtot);
    c.alias(wk1,2*qtot,qtot);
    wk.alias(wk1,3*qtot,qtot);
    idt.alias(wk1,4*qtot,qtot);

    dvdiv(ru, r, u);  // compute u
    dvdiv(rv, r, v);  // compute v

    // c = sqrt( gamma*(gamma-1.0)*(rE-0.5*(r*u*u + r*v*v))/r )
    dvmul(u, ru, c);
    dvvtvp(v, rv, c, c);
    scale(-pt5, c);
    dvadd(rE, c);
    scale(gamma*(gamma-1.0), c);
    dvdiv( r, c );
    dvsqrt( c, c );

    dvmul( u, S->geom->dxr, idt );
    dvvtvp( v, S->geom->dyr, idt, idt );
    abs( idt );
    dvmul( u, S->geom->dxs, wk );
    dvvtvp( v, S->geom->dys, wk, wk );
    abs( wk );
    dvadd( wk, idt );
    dvvtvp( c, S->geom->acoustic, idt, idt );
    dvmul( S->geom->ivol, idt );
#ifdef REO_EULER_DEBUG
    if (comm->MyPID() == 0)
      cout << "Eid = " << e << ", max(idt) = " << idt[max(idt)]
           << ", max(c) = " << c[max(c)] << endl;
#endif
    cfl = max( cfl, dt * idt.Max() );
    dtl[e] = one/idt.Max();
  }
#ifdef DGM_PARALLEL
  Scalar local = cfl;
  // cout << comm->MyPID() << " cfl = " << local << endl;
  comm->MaxAll( &local, &cfl, 1 );
#endif

  Scalar dt_old = dt;
  if (CFLmax != 0 && dtmax != 0) {
    dt = min( dtmax, CFLmax * dt / cfl );
    for (LocalSize e=0; e<U[0]->ne; e++) dtl[e] = min(dtmax, CFLmax * dtl[e]);
  } else if (CFLmax != 0) {
    dt = CFLmax * dt / cfl;
    for (LocalSize e=0; e<U[0]->ne; e++) dtl[e] = CFLmax * dtl[e];
  } else {
    for (LocalSize e=0; e<U[0]->ne; e++) dtl[e] = dt;
  }
  cfl = cfl * dt / dt_old;
#endif  // DGM_STORE_METRICS
  return cfl;
}

/// Set the initial condition
void Euler::set_ic(vField &F, string ext) {
  t = 0.0; step = 0;
  string fname = root+ext;
  ifstream in(fname.c_str());
  if (!in) {
    comm->cerr() << "Reo::Euler: Could not open initial condition "
                 << fname << endl;
    comm->exit(DGM::FAILURE);
  }
  string buffer, code;
  getline(in,buffer);
  if (!(in>>code)) error("Cannot read IC code");
  getline(in,buffer);
  // cout << "IC code = " << code << endl;
  if (lowerCase(code) == "given") {
    F.fill(in);
  } else if (lowerCase(code) == "restart") {
    string rstfile;
    if (!(in>>rstfile)) {
      comm->cerr() << "Cannot read restart file name from " << fname << endl;
      comm->exit(DGM::FAILURE);
    }
    read(rstfile, F);
    // comm->cout() << "Restarting from: " << rstfile << endl;
  } else if (lowerCase(code) == "restart_p") {
    // restart with a perterbation
    string rstfile;
    if (!(in>>rstfile)) {
      comm->cerr() << "Cannot read restart file name from " << fname << endl;
      comm->exit(DGM::FAILURE);
    }
    GlobalSize eid;
    LocalSize dof;
    Scalar eps;
    in >> eid >> dof >> eps;
    read(rstfile, F);
    if ( partition->owns(eid) )
      F[dof]->el[partition->inc(eid)]->u += eps;
    comm->cout() << "Restarting from: " << rstfile
                 << " with added perturbations." << endl;
  } else if (lowerCase(code) == "vortex") {
    // superimpose Oseen vortices in conservation variables
    int nVorts;
    Scalar x0, y0, radius, amp, Ma;
    in>>nVorts;
    for (int nv=0; nv<nVorts; nv++) {
      in>>x0>>y0>>radius>>amp>>Ma;
      OseenVortex vortex(x0,y0,radius,amp,Ma,gamma);
      for (LocalSize e=0; e<ne; e++) {
        for (LocalSize q=0; q<F[0]->el[e]->qtot; q++) {
          F[0]->el[e]->u[q] += vortex.R( (*F[0]->el[e]->C)[q] );
          F[1]->el[e]->u[q] += vortex.U( (*F[1]->el[e]->C)[q] );
          F[2]->el[e]->u[q] += vortex.V( (*F[2]->el[e]->C)[q] );
          F[3]->el[e]->u[q] += vortex.E( (*F[3]->el[e]->C)[q] );
        }
      }
    }
  } else if (lowerCase(code) == "oseenvortex_prim") {
    // superimpose Oseen vortices in primative variables
    int nVorts;
    Scalar x0, y0, radius, amp, Ma=0;
    Scalar r,u,v,t;
    in>>nVorts;
    for (int nv=0; nv<nVorts; nv++) {
      in>>x0>>y0>>radius>>amp>>Ma;
      OseenVortex vortex(x0,y0,radius,amp,Ma,gamma);
      for (LocalSize e=0; e<ne; e++) {
        for (LocalSize q=0; q<F[0]->el[e]->qtot; q++) {
          F[0]->el[e]->u[q] += vortex.R( (*F[0]->el[e]->C)[q] );
          F[1]->el[e]->u[q] += vortex.u( (*F[1]->el[e]->C)[q] );
          F[2]->el[e]->u[q] += vortex.v( (*F[2]->el[e]->C)[q] );
          F[3]->el[e]->u[q] += vortex.t( (*F[3]->el[e]->C)[q] );
        }
      }
    }
    // Transform to conservative variables
    for (LocalSize e=0; e<ne; e++) {
      for (LocalSize q=0; q<F[0]->el[e]->qtot; q++) {
        r = F[0]->el[e]->u[q];
        u = F[1]->el[e]->u[q];
        v = F[2]->el[e]->u[q];
        t = F[3]->el[e]->u[q];
        F[0]->el[e]->u[q] = r;
        F[1]->el[e]->u[q] = r*u;
        F[2]->el[e]->u[q] = r*v;
        F[3]->el[e]->u[q] = r*t/(gamma*(gamma-1.0)*Ma*Ma) + 0.5*r*(u*u+v*v);
      }
    }
  } else if (lowerCase(code) == "coloniusvortex") {
    // superimpose Colonius vortices in primative variables
    int nVorts;
    Scalar x0, y0, radius, amp, Ma=0;
    Scalar r,u,v,t;
    in>>nVorts;
    for (int nv=0; nv<nVorts; nv++) {
      in>>x0>>y0>>radius>>amp>>Ma;
      ColoniusVortex vortex(x0,y0,radius,amp,Ma,gamma);
      for (LocalSize e=0; e<ne; e++) {
        for (LocalSize q=0; q<F[0]->el[e]->qtot; q++) {
          F[0]->el[e]->u[q] += vortex.R( (*F[0]->el[e]->C)[q] );
          F[1]->el[e]->u[q] += vortex.u( (*F[1]->el[e]->C)[q] );
          F[2]->el[e]->u[q] += vortex.v( (*F[2]->el[e]->C)[q] );
          F[3]->el[e]->u[q] += vortex.t( (*F[3]->el[e]->C)[q] );
        }
      }
    }
    // Transform to conservative variables
    for (LocalSize e=0; e<ne; e++) {
      for (LocalSize q=0; q<F[0]->el[e]->qtot; q++) {
        r = F[0]->el[e]->u[q];
        u = F[1]->el[e]->u[q];
        v = F[2]->el[e]->u[q];
        t = F[3]->el[e]->u[q];
        F[0]->el[e]->u[q] = r;
        F[1]->el[e]->u[q] = r*u;
        F[2]->el[e]->u[q] = r*v;
        F[3]->el[e]->u[q] = r*t/(gamma*(gamma-1.0)*Ma*Ma) + 0.5*r*(u*u+v*v);
      }
    }
  } else if (lowerCase(code) == "vortex_flow") {
    // superimpose Oseen vortices on a uniform flow in the +x direction
    int nVorts;
    Scalar x0, y0, radius, amp, Ma;
    in>>nVorts;
    for (int nv=0; nv<nVorts; nv++) {
      in>>x0>>y0>>radius>>amp>>Ma;
      OseenVortex vortex(x0,y0,radius,amp,Ma,gamma);
      for (LocalSize e=0; e<ne; e++) {
        for (LocalSize q=0; q<F[0]->el[e]->qtot; q++) {
          F[0]->el[e]->u[q] = vortex.R( (*F[0]->el[e]->C)[q] );
          F[1]->el[e]->u[q] = F[0]->el[e]->u[q] *
            (1.0+vortex.U((*F[1]->el[e]->C)[q])/
             vortex.R((*F[0]->el[e]->C)[q]));
          F[2]->el[e]->u[q] = F[0]->el[e]->u[q] *
            (0.0+vortex.V((*F[1]->el[e]->C)[q])/
             vortex.R((*F[0]->el[e]->C)[q]));
          Scalar T  = 1.0;
          Scalar T1 = vortex.E((*F[3]->el[e]->C)[q])-
            0.5*(pow(vortex.U((*F[1]->el[e]->C)[q]),2) +
                 pow(vortex.V((*F[2]->el[e]->C)[q]),2) )/
            vortex.R((*F[0]->el[e]->C)[q]);
          T1 *= gamma*(gamma-1)*Ma*Ma/vortex.R((*F[3]->el[e]->C)[q]);
          Scalar T2 = T + T1 - 1.0;
          F[3]->el[e]->u[q] = F[0]->el[e]->u[q] * T2 / (gamma*(gamma-1)*Ma*Ma)
            + 0.5*(pow(F[1]->el[e]->u[q],2) +
                   pow(F[2]->el[e]->u[q],2))/F[0]->el[e]->u[q];
        }
      }
    }
  } else if (lowerCase(code) == "vortex_super") {
    // superimpose a vortex on a given flow
    string rstfile;  // read a restart file
    if (!(in>>rstfile)) {
      comm->cerr() << "Cannot read restart file name from " << fname << endl;
      comm->exit(DGM::FAILURE);
    }
    read(rstfile, F);
    // superposition an Oseen vortex
    Scalar x0, y0, radius, amp, Ma;  // amp = Ma / Ma_flow
    in>>x0>>y0>>radius>>amp>>Ma;
    OseenVortex vortex(x0,y0,radius,amp,Ma,gamma);
    Scalar R1, u1, v1, E1, e1;
    Scalar R2, u2, v2, E2, e2;
    Scalar R3, u3, v3, E3, e3;
    for (LocalSize e=0; e<ne; e++) {
      for (LocalSize q=0; q<F[0]->el[e]->qtot; q++) {
        R1 = F[0]->el[e]->u[q];
        u1 = F[1]->el[e]->u[q]/R1;
        v1 = F[2]->el[e]->u[q]/R1;
        E1 = F[3]->el[e]->u[q];
        e1 = E1/R1 - 0.5*(u1*u1+v1*v1);

        R2 = vortex.R( (*F[0]->el[e]->C)[q] );
        u2 = vortex.U( (*F[1]->el[e]->C)[q] )/R2;
        v2 = vortex.V( (*F[2]->el[e]->C)[q] )/R2;
        E2 = vortex.E( (*F[3]->el[e]->C)[q] );
        e2 = E2/R2 - 0.5*(u2*u2+v2*v2);

        R3 = R1 + R2 - 1.0;
        u3 = u1 + u2;
        v3 = v1 + v2;
        e3 = e1 + e2 - (amp*amp)/(gamma*(gamma-1)*Ma*Ma);
        E3 = R3 * ( e3 + 0.5*( u3*u3 + v3*v3 ) );

        F[0]->el[e]->u[q] = R3;
        F[1]->el[e]->u[q] = R3 * u3;
        F[2]->el[e]->u[q] = R3 * v3;
        F[3]->el[e]->u[q] = E3;
      }
    }
  } else if (lowerCase(code) == "taylor_green") {
    // Taylor Green vortices
    Scalar U, Re, Ma;
    in>>U>>Re>>Ma;
    Taylor_Green ic(U,Re,Ma,gamma);  // make a Taylor_Green object
    for (LocalSize e=0; e<ne; e++) {
      for (LocalSize q=0; q<F[0]->el[e]->qtot; q++) {
        F[0]->el[e]->u[q] = ic.R( (*F[0]->el[e]->C)[q] );
        F[1]->el[e]->u[q] = ic.U( (*F[1]->el[e]->C)[q] );
        F[2]->el[e]->u[q] = ic.V( (*F[2]->el[e]->C)[q] );
        F[3]->el[e]->u[q] = ic.E( (*F[3]->el[e]->C)[q] );
      }
    }
  } else if (lowerCase(code) == "scalar_shear") {
    // Chaniotis, Poulikakos, Koumoutsakos Scalar shear layer
    Scalar Ma;
    in>>Ma;
    Double_Shear ic(Ma, gamma);
    for (LocalSize e=0; e<ne; e++) {
      for (LocalSize q=0; q<F[0]->el[e]->qtot; q++) {
        F[0]->el[e]->u[q] = ic.R( (*F[0]->el[e]->C)[q] );
        F[1]->el[e]->u[q] = ic.U( (*F[1]->el[e]->C)[q] );
        F[2]->el[e]->u[q] = ic.V( (*F[2]->el[e]->C)[q] );
        F[3]->el[e]->u[q] = ic.E( (*F[3]->el[e]->C)[q] );
      }
    }
  } else if (lowerCase(code) == "brown_minion") {
    // Brown and Minion Scalar shear layer
    Scalar Ma, r, d;
    in>>Ma>>r>>d;
    Brown_Minion ic(Ma, r, d, gamma);
    for (LocalSize e=0; e<ne; e++) {
      for (LocalSize q=0; q<F[0]->el[e]->qtot; q++) {
        F[0]->el[e]->u[q] = ic.R( (*F[0]->el[e]->C)[q] );
        F[1]->el[e]->u[q] = ic.U( (*F[1]->el[e]->C)[q] );
        F[2]->el[e]->u[q] = ic.V( (*F[2]->el[e]->C)[q] );
        F[3]->el[e]->u[q] = ic.E( (*F[3]->el[e]->C)[q] );
      }
    }
  } else if (lowerCase(code) == "vortex_sheet") {
    // simple hyperbolic tangent shear layer
    Scalar Ma, r, d;
    in>>Ma>>r>>d;
    Vortex_Sheet ic(Ma, r, d, gamma);
    for (LocalSize e=0; e<ne; e++) {
      for (LocalSize q=0; q<F[0]->el[e]->qtot; q++) {
        F[0]->el[e]->u[q] = ic.R( (*F[0]->el[e]->C)[q] );
        F[1]->el[e]->u[q] = ic.U( (*F[1]->el[e]->C)[q] );
        F[2]->el[e]->u[q] = ic.V( (*F[2]->el[e]->C)[q] );
        F[3]->el[e]->u[q] = ic.E( (*F[3]->el[e]->C)[q] );
      }
    }
  } else if (lowerCase(code) == "wave") {
    // 1D acoustic wave
    // Scalar Re = 50.0;  // not currently used so comment out
    Scalar Pr = 1.0;
    Scalar Ma = 0.5;
    Scalar amp = 0.001;
    Scalar s_0 = 8.0;
    Scalar sigma = 0.25;
    char   dir = 'x';
    char   sign = 'p';
    in>>Ma>>amp>>s_0>>sigma>>dir>>sign;  // read wave properties from input
    AcousticWave ic(Ma, Pr, gamma, amp, s_0, sigma, dir, sign,
                    AcousticWave::Gaussian);
    Scalar rhom = one;
    Scalar Tm = one;
    for (LocalSize e=0; e<ne; e++) {
      for (LocalSize q=0; q<F[0]->el[e]->qtot; q++) {
        Point cxy = Point(F[0]->el[e]->C->x[q], F[0]->el[e]->C->y[q]);
        Scalar rho = rhom + ic.R(cxy);
        Scalar u   = ic.U(cxy);
        Scalar v   = ic.V(cxy);
        Scalar T   = Tm + ic.T(cxy);
        F[0]->el[e]->u[q] = rho;
        F[1]->el[e]->u[q] = rho*u;
        F[2]->el[e]->u[q] = rho*v;
        F[3]->el[e]->u[q] = rho*T/(gamma*(gamma-one)*Ma*Ma)+pt5*rho*(u*u+v*v);
      }
    }
  } else if (lowerCase(code) == "cylindricalwave") {
    // 2D cylindrical wave
    // Scalar Re = 50.0;  // not currently used so comment out
    Scalar Pr = 1.0;
    Scalar Ma = 0.3;
    Scalar amp = 0.005;
    Scalar x0(2.0), y0(2.0), xn(1.0), yn(1.0);
    Scalar sigma = 0.2;
    char   sign = 'p';
    Scalar r0 = 1.2;
    // in>>Ma>>amp>>s_0>>sigma>>dir>>sign;  // read wave properties from input
    AcousticWave ic( Ma, Pr, gamma, amp, x0, y0, sigma, sign,
                     AcousticWave::Cylindrical, r0, xn, yn);
    Scalar rhom = one;
    Scalar Tm = one;
    for (LocalSize e=0; e<ne; e++) {
      for (LocalSize q=0; q<F[0]->el[e]->qtot; q++) {
        Point cxy = Point(F[0]->el[e]->C->x[q], F[0]->el[e]->C->y[q]);
        Scalar rho = rhom + ic.R(cxy);
        Scalar u   = ic.U(cxy);
        Scalar v   = ic.V(cxy);
        Scalar T   = Tm + ic.T(cxy);
        F[0]->el[e]->u[q] = rho;
        F[1]->el[e]->u[q] = rho*u;
        F[2]->el[e]->u[q] = rho*v;
        F[3]->el[e]->u[q] = rho*T/(gamma*(gamma-one)*Ma*Ma)+pt5*rho*(u*u+v*v);
      }
    }
  } else {
    comm->error("Reo::Euler::set_ic()  Unsupported IC type");
  }
#define DGM_NO_PROJECT_IC
#ifdef DGM_NO_PROJECT_IC
  comm->cout() << "WARNING:  No projection of Initial condition" << endl;
  for (LocalSize i=0; i<F.size(); i++)
    for (LocalSize e=0; e<ne; e++)
      F[i]->el[e]->state = Element::Physical;
#else
  comm->cout() << "Projecting initial condition to DG space" << endl;
  project( F );
#endif
#undef DGM_NO_PROJECT_IC
}

//===========================================================================
//                        BC database management
//===========================================================================

/// Load up the available BC types
void Euler::setup_BCdb( ) {
  // cout << "Euler::setup_BCdb()" << endl;
  // set default BC types
  dVector ub(Nfields);
  ub[0] = 1.0;
  ub[1] = 1.0;
  ub[2] = 0.0;
  ub[3] = 20.34126984126985;  // Uniform flow at Ma = 0.3
  BC_db["S"].reset( new StateBC("S", ub) );
  BC_db["W"].reset( new WallBC("W") );
  BC_db["O"].reset( new SupersonicOutflowBC("O") );

  // read new BC types from file
  string fname = root+".bct";
  ifstream in(fname.c_str());
  if (in) Euler::read_BCdb( in );   // database of active BC types
}

void Euler::read_BCdb( ifstream &in ) {
  // cout << "Euler::read_BCdb( ifstream &in )" << endl;
  string tag;
  BC *pbc;
  while ( (pbc = Euler::make_BC(in,tag)) ) {
    if ( BC_db.find(tag) != BC_db.end() )
      comm->cerr() << "WARNING in Reo::Euler::read_BCdb() Overriding BC "
        "type \"" << tag << "\"." << endl;
    BC_db[tag].reset( pbc );
  }
}

/** Note that caution is required here as the Euler module searches for
    substrings within the BC tag.  This makes it possible that many
    Navier-Stokes BCs map onto a single Euler BC, but care is required to
    make the substring search order correct and unique. */
BC* Euler::make_BC( ifstream &in, string &tag ) {
  // cout << "Euler::make_BC(ifstream &in, string &tag)" << endl;
  string code;
  if (!(in >> code)) return NULL;
  code = lowerCase(code);
  if (code == "state") {
    if (!(in >> tag)) error("Euler::make_BC: Cannot read State tag");
    return new StateBC(tag,in,4);
  } else if ( code.find("wall") != code.npos ) {
    if (!(in >>tag)) error("Euler::make_BC: Cannot read WallBC tag");
    return new WallBC(tag,in);
  } else if ( code.find("steadycontrol") != code.npos ) {
    if (!(in >>tag)) error("Euler::make_BC: Cannot read SteadyControlBC tag");
    return new SteadyControlBC(tag,in,&U,gamma);
  } else if ( code.find("linearcontrol") != code.npos ) {
    if (!(in >>tag)) error("Euler::make_BC: Cannot read LinearControlBC tag");
    return new LinearControlBC(tag,in,&U,gamma);
  } else if ( code.find("control") != code.npos ) {
    if (!(in >>tag)) error("Euler::make_BC: Cannot read ControlBC tag");
    return new ControlBC(tag,in,&U,gamma);
  } else if ( code.find("subsonicoutflow") != code.npos ) {
    if (!(in>>tag)) error("Euler::make_BC: Cannot read SubsonicOutflow tag");
    return new SubsonicOutflowBC(tag,in);
  } else if ( code.find("supersonicoutflow") != code.npos ) {
    if (!(in >>tag)) error("Euler::make_BC: Cannot read SupersonicOutflow tag");
    return new SubsonicOutflowBC(tag,in);
  } else {
    if(comm->Master())
      comm->cerr()<<"WARNING in Euler::make_BC() Illegal BC type: "+code<<endl;
  }
  return NULL;
}

//===========================================================================
//                        Source database management
//===========================================================================

// here you use the State vField for the construction of the SourceControl
// scratch vField, is it important to use the local projection. [gqchen]

/// Construct source terms
Source::Ptr Euler::make_Source( ifstream &in, string &tag ) {
  // cout << "Euler::make_Source" << endl;
  string code;
  Source::Ptr p;
  if (!(in >> code)) return p;
  while (code[0]=='#') {  // eat comment lines
    string buffer;
    getline(in,buffer);
    if (!(in >> code)) return p;
  }
  if (lowerCase(code) == "constant") {
    if (!(in >> tag)) error("Reo::Euler::Cannot read ConstSource tag",1);;
    p.reset( new ConstSource(tag,in,1) );
  } else if (lowerCase(code) == "sponge") {
    if (!(in >> tag)) error("Reo::Euler::Cannot read Sponge tag",1);;
    p.reset( new Sponge(tag, in) ); // this generates two scratch vFields*
  } else {
    error("Reo::Euler::make_Source() Illegal Source type",1);
  }
  return p;
}

// Add source terms
void Euler::add_source(const vField &Us, vField &Ur) {
  // cout << "Euler::add_source(vField &)" << endl;
  for (Source::db_citr i=Source_db.begin(); i!= Source_db.end(); ++i)
    // cout << "Adding source: " << i->first << endl;
    i->second->apply( t, Us, Ur);
}

//===========================================================================
//                             Output methods
//===========================================================================

/// Computes the vorticity and other derived quantities
void Euler::compute_vorticity() {
  Element *S[NFIELDS], *F[NFIELDS];
  dVector u, v, p, e, wk;
  dVector r, ru, rv, rE;

  const bool incjump = params["incjump"];

  if (incjump) {
    U.fill_sides();
    U.share_sides();
    enforce_bc( U );
    primitive_sides( U );
    average_flux( U, Ut, '+' );
  }

  for (LocalSize k=0; k<U[0]->ne; k++) {
    // local version of the state
    S[0] = U[0]->el[k];
    S[1] = U[1]->el[k];
    S[2] = U[2]->el[k];
    S[3] = U[3]->el[k];

    // local version of the state
    F[0] = Ut[0]->el[k];
    F[1] = Ut[1]->el[k];
    F[2] = Ut[2]->el[k];
    F[3] = Ut[3]->el[k];

    const Ordinal qtot = U[0]->el[k]->qtot;

    r.alias (S[0]->u);  // rho
    ru.alias(S[1]->u);  // rho u
    rv.alias(S[2]->u);  // rho v
    rE.alias (S[3]->u); // total Energy

    u.alias(wk1,0,qtot);
    v.alias(wk1,qtot,qtot);
    p.alias(wk1,2*qtot,qtot);
    e.alias(wk1,3*qtot,qtot);
    wk.alias(wk1,4*qtot,qtot);

    dvdiv(ru, r, u);   // compute u
    dvdiv(rv, r, v);   // compute v
    dvdiv(rE, r, e);   // internal energy + 0.5 |V|^2

    dvmul(u,u,wk);     // wk = u^2
    dvvtvp(v,v,wk,wk); // wk = u^2 + v^2
    daxpy(-pt5,wk,e);  // e  = e - 0.5 * wk = internal energy

    // p = (gamma-1.0)*(rE-0.5*(r*u*u + r*v*v))
    dvmul(u, ru, p);
    dvvtvp(v, rv, p, p);
    scale(-pt5*(gamma-1.0), p);
    daxpy(gamma-1.0, rE, p);

    if (incjump) {
      dVector ux(qtot);
      dVector uy(qtot);
      dVector vx(qtot);
      dVector vy(qtot);

      gradient( S[1], F[1], u, ux, uy );
      gradient( S[2], F[2], v, vx, vy );

      // vorticity:   F[0]
      scale(-1.0, uy);
      dvadd(vx, uy, F[0]->u);

      // divergence:  F[1]
      dvadd(ux, vy, F[1]->u);
    } else {
      // vorticity:   F[0]
      F[0]->gradient(u, F[0]->u, 'y');
      F[1]->gradient(v, F[1]->u, 'x');
      scale(-one, F[0]->u);
      dvadd(F[1]->u, F[0]->u);

      // divergence:  F[1]
      F[1]->gradient(u, F[1]->u, 'x');
      F[2]->gradient(v, F[2]->u, 'y');
      dvadd(F[2]->u, F[1]->u);
    }
    F[2]->fill(p);
    F[3]->fill(e);
  }
  vector<string> names;
  names.push_back("Vorticity");
  names.push_back("Divergence");
  names.push_back("Pressure");
  names.push_back("Energy");
  Ut.set_Field_names(names);
}

/// if defined then perform a projection to compute diffusive flux
#define EULER_GRADIENT_PROJECT

/// Compute a jump savy gradient
void Euler::gradient( Element *S, Element *F, dVector &u,
                      dVector &ux, dVector &uy ) {
    S->gradient( u, ux, uy );
    S->lift( F, ux, 'x' );
#ifdef EULER_GRADIENT_PROJECT
    S->project(ux);
#endif
    S->lift( F, uy, 'y' );
#ifdef EULER_GRADIENT_PROJECT
    S->project(uy);
#endif
}

/// Convert edge values from conservative to primitive variables
void Euler::primitive_sides( vField &Us ) {
  // loop over all sides including boundary sides
  for (LocalSize k=0; k<Us[0]->ne; k++) {
    for (LocalSize i=0; i<Us[0]->el[k]->nSides(); i++) {
      if (Us[0]->el[k]->side[i]->master()) {
        dVector wk(Us[0]->el[k]->side[i]->qtot()); // WARNING: new memory
        // left side
        dVector  r(Us[0]->el[k]->side[i]->u);      // rho
        dVector  u(Us[1]->el[k]->side[i]->u);      // rho u
        dVector  v(Us[2]->el[k]->side[i]->u);      // rho v
        dVector  e(Us[3]->el[k]->side[i]->u);      // total energy per volume
        dvdiv(u, r, u);       // u-velocity
        dvdiv(v, r, v);       // v-velocity
        dvdiv(e, r, e);       // internal energy + 0.5 |V|^2
        dvmul(u, u, wk);      // wk = u^2
        dvvtvp(v, v, wk, wk); // wk = u^2 + v^2
        daxpy(-pt5, wk, e);   // e  = e - 0.5 * wk = internal energy
        // right side
        r.alias(Us[0]->el[k]->side[i]->link->u);   // rho
        u.alias(Us[1]->el[k]->side[i]->link->u);   // rho u
        v.alias(Us[2]->el[k]->side[i]->link->u);   // rho v
        e.alias(Us[3]->el[k]->side[i]->link->u);   // total energy per volume
        dvdiv(u, r, u);       // u-velocity
        dvdiv(v, r, v);       // v-velocity
        dvdiv(e, r, e);       // internal energy + 0.5 |V|^2
        dvmul(u, u, wk);      // wk = u^2
        dvvtvp(v, v, wk, wk); // wk = u^2 + v^2
        daxpy(-pt5, wk, e);   // e  = e - 0.5 * wk = internal energy
      }
    }
  }
}

/** Computes lift and drag and saves every time-step. Also output profiles
    every Ntout time steps. */
void Euler::write_bndry_stats() {
  static FILE *frc = NULL;
  if (!U[0]->bndry_stats->valid) return;
  if (comm->Master()) {  // unsteady forces
    if (!frc) {
      string fname;
      char buf[80];
      sprintf(buf,"%s.frc",root.c_str());
      fname = buf;
      frc = fopen(fname.c_str(),"a+");  // append to end of file
    }
  }
  Coord C;
  dVector r, ru, rv, rE;
  U[0]->bndry_stats->get_coordinates( C );
  U[0]->bndry_stats->get_solution( r );
  U[1]->bndry_stats->get_solution( ru );
  U[2]->bndry_stats->get_solution( rv );
  U[3]->bndry_stats->get_solution( rE );

  const Ordinal qtot = r.size();
  dVector u(qtot), v(qtot), p(qtot), e(qtot), wk(qtot);

  dvdiv(ru, r, u);   // compute u
  dvdiv(rv, r, v);   // compute v
  dvdiv(rE, r, e);   // internal energy + 0.5 |V|^2

  dvmul(u,u,wk);     // wk = u^2
  dvvtvp(v,v,wk,wk); // wk = u^2 + v^2
  daxpy(-pt5,wk,e);  // e  = e - 0.5 * wk = internal energy

  // p = (gamma-1.0)*(rE-0.5*(r*u*u + r*v*v))
  dvmul(u, ru, p);
  dvvtvp(v, rv, p, p);
  scale(-pt5*(gamma-1.0), p);
  daxpy(gamma-1.0, rE, p);

#ifdef DGM_PARALLEL
  // output unsteady forces (lift and drag)
  Scalar llift=0, ldrag=0;  // local values
  llift = U[0]->bndry_stats->liftcalc(p);
  ldrag = U[0]->bndry_stats->dragcalc(p);

  Scalar lift, drag;
  comm->SumAll( &llift, &lift, 1);
  comm->SumAll( &ldrag, &drag, 1);

  if (comm->Master()) {
    fprintf(frc, "%18.11e %18.11e %18.11e\n", t, drag, lift);
    // fflush(frc);  // makes parallel run times inconsistent
  }

  if (step%Ntout==0) {
    // output pressure distribution
    int np = comm->NumProc();
    intVector recvcounts(np);
    intVector displs(np);
    {
      const int i = static_cast<int>(qtot);
      comm->GatherAll( &i, recvcounts.data(), 1 );
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

    comm->GatherAll( C.x, qtot, gx,    recvcounts, displs);
    comm->GatherAll( C.y, qtot, gy,    recvcounts, displs);
    comm->GatherAll(   p, qtot, gdata, recvcounts, displs);

    if (comm->Master()) {
      string fname;
      char buf[80];
      sprintf(buf, "%s.%lld.cp", root.c_str(), (long long)step);
      fname = buf;
      FILE *out = fopen(fname.c_str(),"w");
      for (Ordinal q=0; q<gdata.size(); ++q )
        fprintf(out," %18.11e %18.11e %18.11e\n", gx[q], gy[q], gdata[q]);
      fclose(out);
    }
  }
#else
  // output unsteady loads
  fprintf(frc, "%18.11e %18.11e %18.11e\n", t, U[0]->bndry_stats->dragcalc(p),
          U[0]->bndry_stats->liftcalc(p));
  fflush(frc);

  if (step%Ntout==0) {
    // output full boundary data
    string fname;
    char buf[80];
    sprintf(buf,"%s.%lld.bdt",root.c_str(), (long long)step);
    fname = buf;
    FILE *out = fopen(fname.c_str(),"w");
    for (Ordinal q=0; q<qtot; ++q )
      fprintf(out,
      "%18.11e %18.11e %18.11e %18.11e %18.11e %18.11e %18.11e %18.11e\n",
              C.x[q], C.y[q], r[q], ru[q], rv[q], rE[q], p[q], e[q]);
    fclose(out);

    // output pressure distribution
    sprintf(buf,"%s.%lld.cp",root.c_str(), (long long)step);
    fname = buf;
    out = fopen(fname.c_str(),"w");
    fprintf(out,"#%18.11e %18.11e\n", U[0]->bndry_stats->dragcalc(p),
            U[0]->bndry_stats->liftcalc(p));
    for (Ordinal q=0; q<qtot; ++q )
      fprintf(out," %18.11e %18.11e %18.11e\n", C.x[q], C.y[q], p[q]);
    fclose(out);
  }
#endif  // DGM_PARALLEL
}

} // namespace Reo
