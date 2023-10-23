/*=============================================================================
  Module:     Multi-Component-Transport

  Contact:    G. Scovazzi

  Copyright:  (c)2011 Sandia National Laboratories
=============================================================================*/

/** \file Multi_Component_Transport.cpp
    \brief Multi component transport implementation
    \author Guglielmo Scovazzi
    \author Axel Gerstenburger
    \author Scott Collis
*/

// DGM includes
#include "Comm.hpp"
#include "Domain.hpp"
#include "TimeInt.hpp"
#include "Field.hpp"
#include "vField.hpp"
using namespace DGM;

// local includes
#include "Reo.hpp"
#include "Multi_Component_Transport.hpp"
#include "Multi_Component_TransportBC.hpp"
#include "Darcy.hpp"

namespace Reo {

/// Constructor
Multi_Comp_Trans::Multi_Comp_Trans(
    DGM::ArgList &args,
    const DGM::Comm::Ptr comm_,
    const bool coupled_darcy_)
: Domain(args,comm_), eff_diff(0), porosity_phi(0), tmax(0),
  Cf(comm_), Vf(comm_), coupled_darcy(coupled_darcy_), variable_cfield(true),
  cx(0.0), cy(0.0), cz(0.0), solve_Darcy(false) {

  if (coupled_darcy) {
    const string root = args.back();
    args.back() = root+"_darcy";
    darcy.reset(new Reo::Darcy( args, comm));
    args.back() = root;
  }
  // cout << "Multi_Comp_Trans::Multi_Comp_Trans()" << endl;

//  params["use_ldg"] = read_from_input<bool>(root+".inp", "use_ldg", true);
//
//  // set the number of fields in the domain
//  Nfields = 1;                         // = 1 for a scalar problem
//
//  // initialize material
//  // tortuosity of aquifer
//  const Scalar tau = read_from_input<Scalar>(root+".inp",
//                                             "tortuosity_tau" , 1.0);
//  // diffusivity of aquifer (default is zero to allow turning off diffusivity)
//  const Scalar D  = read_from_input<Scalar>(root+".inp",
//                                            "diffusivity_D" ,  0.0);
//  eff_diff = tau * D;
//
//  rho.clear();
//  rho.push_back(read_from_input<Scalar>(root+".inp", "rho_CO2"     , 1.0));
//  rho.push_back(read_from_input<Scalar>(root+".inp", "rho_water"   , 1.0));
//  porosity_phi = read_from_input<Scalar>(root+".inp", "porosity_phi", 1.0);
//
//  params["tecplot"] = read_from_input<int>(root+".inp", "tecplot"     , 0);
//  params["plot3d"]  = 0;               // Generate plot3d files
//
//  params["projic"] = read_from_input<bool>(root+".inp", "projic", true);
//  params["projcfd"] = read_from_input<bool>(root+".inp", "projcfd", true);
//
//  // time step control
//  CFLmax = read_from_input<Scalar>(root+".inp", "CFLmax" , 0.5);
//  dtmax = read_from_input<Scalar>(root+".inp", "dtmax" , 1e9);
//  tmax = read_from_input<Scalar>(root+".inp", "tmax" , 1);
//
//  int q;
//  p = params.get("p");                     // polynomial order
//  if ( !(q=params.get("q")) ) q = p + 2;   // number of quadrature points
//  if (coupled_darcy) {
//    const int pdarcy = darcy->params.get("p");
//    if (p != pdarcy) {
//      comm->error("\n Input error: Darcy and Adv_Diff need the same p!!!",
//          DGM::FAILURE);
//    }
//  }
//
//  nsd = params.get("nsd");                 // number of space dimensions
//  stab = params.get("stab");
//
//  // build a Field of Elements and Sides
//  if (params.get("imesh")) {
//    Mesh mesh(params);
//    U.push_back( new Field(p, q, mesh, "u", Field::FULL, comm ) );
//  } else if (params.get("bmesh")) {
//    U.push_back( new Field(p, q, root, "u", partition, 1, comm ) );
//  } else {
//    U.push_back( new Field(p, q, root, "u", partition, comm ) );
//  }
//
//  // set some additional domain parameters
//  ne = U[0]->ne;
//  if (nsd != U[0]->nsd()) comm->error("\n nsd mismatch", DGM::FAILURE);
//
//  // make auxiliary Fields using copy constructor
//  Ut.push_back( new Field(U[0], root, "Ut") );
//  Vf.push_back( new Field(U[0], root, "Vf") );
//  Xf.push_back( new Field(U[0], root, "Xf") );
//  Xfextra.push_back( new Field(U[0], root, "Xfextra") );
//  rhof.push_back( new Field(U[0], root, "rhof") );
//
//  // setup vField names
//  U.set_name("U");
//  Ut.set_name("Ut");
//  Vf.set_name("Vf");
//  Xf.set_name("Xf");
//  Xfextra.set_name("Xfextra");
//  rhof.set_name("rhof");
//
//#ifdef MAKE_CONTIGUOUS
//  make_contiguous();
//#endif
//
//  // convective field
//  Cf.set_name("Cf");
//  Cf.push_back( new Field(U[0], root, "Cx") );
//  if (nsd>1) Cf.push_back( new Field(U[0], root, "Cy") );
//  if (nsd>2) Cf.push_back( new Field(U[0], root, "Cz") );
//#ifdef MAKE_CONTIGUOUS
//  Cf.reset_storage();     // make the vField contiguous
//#endif
//
//  if (not coupled_darcy) {
//    setup_convective_field();
//  }
//
//  // initial pressure solution or truth solution
//  if (coupled_darcy) {
//    comm->cout() << "Reading initial pressure solution" << endl;
//    darcy->set_given_field(darcy->U, ".ic", true);
//    darcy->write(0, darcy->U);
//  }
//
//  // set parameters that should be the same for both fields
//  if (coupled_darcy) {
//    darcy->params["use_ldg"] = params.get("use_ldg");
//  }
//  if (params.get("use_ldg")) // turn on or off LDG for testing
//    comm->cout() << "Multi_Mat: Enabled LDG" << endl;
//  else
//    comm->cout() << "Multi_Mat: Disabled LDG" << endl;
//
//  // workspace
//  wk1.resize(max(Lmax(),Qmax()));
//  wk2.resize(max(Lmax(),Qmax()));
//  wk3.resize(max(Lmax(),Qmax()));
//  wk4.resize(max(Lmax(),Qmax()));
//
//  // make sure that storage is initialized
//  zero_all_fields();
//
//  setup_BCdb();
//
//  setup_Sourcedb();
//
//  set_TimeInt();
//
//  verifyBCs(Xf);
}

/// needed for implicit computations using Epetra vectors and matrices
void Multi_Comp_Trans::make_contiguous() {
  U.reset_storage();
  Ut.reset_storage();
  Vf.reset_storage();
//  Xf.reset_storage();
//  Xfextra.reset_storage();
//  rhof.reset_storage();
}

/// Print usage for the Multi_Mat_Adv_Diff Domain
void Multi_Comp_Trans::showUsage() {
  comm->cout()
    << "Multi_Comp_Trans Class Options \n"
    << "----------------------------------------------------------------\n"
    << "----------------------------------------------------------------\n";
}

/// compute element Peclet number (use a constant value for each element)
void Multi_Comp_Trans::compute_element_Peclet_number(vField &Pef) const {
  for (LocalSize e=0; e<Pef[0]->ne; e++) {
    Element *const Pe = Pef[0]->el[e];
    // compute absolute velocity
    Scalar velo = 0.0;
    for (LocalSize isd = 0; isd < nsd; ++isd) {
      dVector uh(wk1,Pe->nModes());
      Pe->forward_transform(Cf[isd]->el[e]->u, uh);
      velo += pow(uh(0),2); // a_i^2
    }
    velo = sqrt(velo);
    const Scalar h = 1.0/Pe->sigma(); // kind of the maximal h in the element
    const Scalar Peclet = velo * h / (2.0 * eff_diff);
    Pe->u = Peclet;
  }
  Pef.set_name("Pe");
  Pef[0]->set_name("Pe");
}

/// Zero all fields
void Multi_Comp_Trans::zero_all_fields() {
  Domain::zero_all_fields();
}

/// Compute critical timestep
/** Estimate is taken from AdvDiff where the polynomial order dependence is
    incorporated in the length scale computation for each integration point
    (he[i]). */
Scalar Multi_Comp_Trans::compute_critical_timestep() const {
  Scalar dtcritical = 1.0e9;        // minimum timestep over all elements
  for (LocalSize e=0; e<U[0]->ne; e++) {
    std::vector<Element*> Ce;
    Ce.push_back(Cf[0]->el[e]);
    if (nsd>1) Ce.push_back(Cf[1]->el[e]);
    if (nsd>2) Ce.push_back(Cf[2]->el[e]);
    const Ordinal qtot = Ce[0]->qtot;
    dVector c(qtot); c = 0;        // advective velocity at quadrature points
    dVector ctmp(qtot);
    for (LocalSize isd = 0; isd < nsd; ++isd) {
      dvmul(Ce[isd]->u, Ce[isd]->u, ctmp);
      c += ctmp;
    }
    dvsqrt(c);

    // Create characteristic length to use for CFL calc.
    Element::StabMetrics cfl_metrics(Ce[0]->compute_metrics());
    dVector &ivol = cfl_metrics[Element::IVOL];

    // advection (do it at each Gauss point to check for zero velocities)
    for (LocalSize i = 0; i < qtot; ++i) {
      if (c[i] > 0.0 || eff_diff > 0.0) {
        // the calculation is problematic for stretched elements!!!
        const Scalar he = pow(ivol[i],-one/nsd);
        const Scalar numerator = he*he;
        const Scalar denominator = eff_diff +
          sqrt( pow(eff_diff,2) + pow(c[i]*he/porosity_phi,2));
        dtcritical = min(dtcritical, numerator/ denominator);
      }
    }
  }
#ifdef DGM_PARALLEL
  Scalar localdt = dtcritical;
  comm->MinAll( &localdt, &dtcritical, 1 );
#endif

  return dtcritical;
}

/// Set the time step based on CFL-type condition
Scalar Multi_Comp_Trans::set_time_step(vField &) {
  const Scalar dtcritical = compute_critical_timestep();
  //cout << "CFLmax = " << cfl << endl;
  // max. 20% increase of time step size per time step
  dt = min(dt*1.2, min(dtmax, CFLmax * dtcritical ));
  const Scalar cfl = dt/dtcritical;
  //cout << "cfl = " << cfl << ", dt = " << dt << endl;
  return cfl;
}

/// add viscous flux to Darcy source term
void Multi_Comp_Trans::add_viscflux_to_source(
    const Field & Vf,        ///< [in] viscous flux field
    const Scalar rho_alpha,  ///< [in] density of species alpha
    const Scalar rho_extra,  ///< [in] density of extra species
    Field & Sf               ///< [in/out] density scaled flux field
) const {

  for (LocalSize e=0; e<Vf.ne; e++) {
    const Element *const Vae = Vf.el[e];
    Element *const Se = Sf.el[e];

    dVector ua(wk4, Vae->qtot); // work vector, contains flux per species
    ua = Vae->u;
    ua *= 1.0/rho_alpha - 1.0/rho_extra;
    Se->u += ua;
  }
}

/// compute viscous flux source term for Darcy computation
void Multi_Comp_Trans::compute_darcy_source(
    vField &Sf   ///< [out] Darcy source field
    ) const {
  Sf.zero();
  for (vField::size_type ifield=0; ifield < Vf.size(); ifield++) {
    add_viscflux_to_source( *Vf[ifield], rho[ifield], rho[Vf.size()], *Sf[0] );
  }
}

void Multi_Comp_Trans::prestep(vField& U, const Ordinal lstep_minus_one,
                               const Ordinal substep, const Scalar t) {
  //cout << "time integrator substep: " << substep << endl;
  if (substep == 0) solve_Darcy = true;
}


/// add convective flux to Ff
void Multi_Comp_Trans::convection(
    const vField & Xf,   ///< [in]  X, note: sides are modified
    const vField & rhof, ///< [in]  rho, note: sides are modified
    vField & Uf,         ///< [in/out] X*rho (only sides are modified)
    vField & Ff          ///< [out] rhs / overall flux field
) const {
  Ff.zero();
  convective_flux( Xf, rhof, Uf, Ff );    // compute surface fluxes on sides of Ff
  if (variable_cfield) {
    variable_convection_Euler_Lagrange( Uf, Ff );
  } else {
    constant_convection( Uf, Ff );
  }
  for (vField::size_type ifield=0; ifield < Ff.size(); ifield++) {
    for (LocalSize e=0; e<Ff[ifield]->ne; e++) {
      const Element *const Ue = Uf[ifield]->el[e];
      Element *const Fe = Ff[ifield]->el[e];
      Ue->lift( Fe, Fe->u );
    }
  }
}


/// add convective flux to Ff using a spatially variable velocity field
void Multi_Comp_Trans::variable_convection_Euler_Lagrange(
    const vField &Uf, ///< [in]  solution field
    vField &Ff        ///< [out] rhs / overall flux field
) const {
  // comm->cout() << "Variable_convection_Euler_Lagrange for field = "
  // << Uf[0]->name << endl;
  for (LocalSize e=0; e<Uf[0]->ne; e++) {
    const Element *const Ue = Uf[0]->el[e];         // solution
    Element *const Fe = Ff[0]->el[e];               // flux
    Fe->zero();
    if (nsd == 3) {
      dVector cxu(wk1,Ue->qtot);
      dVector cyu(wk2,Ue->qtot);
      dVector czu(wk3,Ue->qtot);
      dvmul(Ue->u, Cf[0]->el[e]->u, cxu);
      dvmul(Ue->u, Cf[1]->el[e]->u, cyu);
      dvmul(Ue->u, Cf[2]->el[e]->u, czu);
      dVector deriv(wk4,Ue->qtot);
      Ue->gradient( cxu, deriv, 'x'); Fe->u += deriv;
      Ue->gradient( cyu, deriv, 'y'); Fe->u += deriv;
      Ue->gradient( cyu, deriv, 'z'); Fe->u += deriv;
    } else if (nsd == 2) {
      dVector cxu(wk1,Ue->qtot);
      dVector cyu(wk2,Ue->qtot);
      dvmul(Ue->u, Cf[0]->el[e]->u, cxu);
      dvmul(Ue->u, Cf[1]->el[e]->u, cyu);
      dVector deriv(wk4,Ue->qtot);
      Ue->gradient( cxu, deriv, 'x'); Fe->u += deriv;
      Ue->gradient( cyu, deriv, 'y'); Fe->u += deriv;
    } else if (nsd == 1) {
      dVector cxu(wk1,Ue->qtot);
      dvmul(Ue->u, Cf[0]->el[e]->u, cxu);
      dVector deriv(wk4,Ue->qtot);
      Ue->gradient( cxu, deriv, 'x'); Fe->u += deriv;
    } else {
      comm->cerr()
          << "Multi_Comp_Trans:variable_convection_Euler_Lagrange "
          << "-- illegal value of nsd" << endl;
      comm->exit(DGM::FAILURE);
    }
  }
}

/// Computes the convection term in the form:
/** \f[ \int_{\Omega_e} w ( c_x u_{,x} + c_y u_{,y} ) d\Omega -
    \int_{\Gamma_e} w ( \hat F_n - F_n ) d\Gamma \f]
    add convective flux to Ff using a spatially constant velocity field
    defined by cx, cy, and cz. */
void Multi_Comp_Trans::constant_convection(
    const vField & Uf, ///< solution field
    vField & Ff        ///< rhs / overall flux field
    ) const {
  // comm->cout() << "Constant_Convection for Field = " << Uf[0]->name << endl;
  for (LocalSize e=0; e<Uf[0]->ne; e++) {
    const Element *const Ue = Uf[0]->el[e];        // solution
    Element *const Fe = Ff[0]->el[e];              // flux
    if (nsd == 3) {
      dVector uy(wk1,Ue->qtot);
      dVector uz(wk2,Ue->qtot);
      Ue->gradient( Ue->u, Fe->u, uy, uz );
      scale( cx, Fe->u );
      daxpy( cy, uy, Fe->u );
      daxpy( cz, uz, Fe->u );
    } else if (nsd == 2) {
      dVector uy(wk1,Ue->qtot);
      Ue->gradient( Ue->u, Fe->u, uy );
      scale( cx, Fe->u );
      daxpy( cy, uy, Fe->u );
    } else if (nsd == 1) {
      Ue->gradient( Ue->u, Fe->u, Fe->u );
      scale( cx, Fe->u );
    } else {
      comm->cerr()<< "Multi_Comp_Trans:constant_convection -- "
                  << "illegal value of nsd"
                  << endl;
      comm->exit(DGM::FAILURE);
    }
  }

  // debug, may be removed if everything works...
  if ( !Uf[0]->finite() ) error("Uf is not finite");
  if ( !Ff[0]->finite() ) error("Ff is not finite");
}

/// Put numerical flux on the flux field sides
/** For descriptions of the numerical fluxes See: E.F. Toro, "Riemann
    Solvers and Numerical Methods for Fluid Dynamics," 2nd Edition,
    Springer, 1999. */
void Multi_Comp_Trans::convective_flux(
    const Scalar& cn,  ///< convecting velocity vector * left normal vector
    const Scalar& ul,  ///< scalar field on left side
    const Scalar& ur,  ///< scalar field on right side
    Scalar& fluxl,     ///< flux field on left side
    Scalar& fluxr      ///< flux field on right side
    ) const {

  // put numerical flux on the upwind flux field sides
  const Scalar cnl =  cn;
  const Scalar cnr = -cn;
  if ( cn < 0 ) {
    fluxl = cnl * ur;
    fluxr = cnr * ur;
  } else {
    fluxl = cnl * ul;
    fluxr = cnr * ul;
  }
}

/// Compute the Advective flux
/** For descriptions of the numerical fluxes See: E.F. Toro, "Riemann
    Solvers and Numerical Methods for Fluid Dynamics," 2nd Edition,
    Springer, 1999.*/
void Multi_Comp_Trans::convective_flux(
    const vField &Xf,
    const vField &rhof,
    vField &Uf,
    vField &Ff) const {

  for (LocalSize e=0; e<Uf[0]->ne; e++) {
    const Element *const Xe   = Xf[0]->el[e];
    const Element *const rhoe = rhof[0]->el[e];
    Element *const Ue = Uf[0]->el[e];
    Element *const Fe = Ff[0]->el[e];
    for (LocalSize i=0; i<Ue->nSides(); i++) {
      if (Ue->side[i]->master()) {

        // localize the state and flux side pointers
        const Side *const Xs   = Xe->side[i];
        const Side *const rhos = rhoe->side[i];
        Side *const Us = Ue->side[i];
        Side *const Fs = Fe->side[i];

#ifdef REO_USE_GETSIDEMAPS
        SideMap smap;
        get_side_maps( Us, Us->link, smap.idl(), smap.idr() );
#endif

        for (LocalSize q=0; q < Us->qtot(); q++) {
#ifdef REO_USE_GETSIDEMAPS
          const Ordinal ql = smap.idl()[q];
#else
          const Ordinal ql = rhoe->sideMap(Us, q);
          const Ordinal qr = rhoe->sideMap(Us->link, q);
#endif
          const Scalar nx =          Us->nx(ql);
          const Scalar ny = (nsd>1 ? Us->ny(ql) : 0.0);
          const Scalar nz = (nsd>2 ? Us->nz(ql) : 0.0);

          if (variable_cfield) {

            // get left discont. velo field and multiply by the left normal
#ifdef REO_USE_GETSIDEMAPS
            const Scalar cxl =          smap.l(Cf[0]->el[e]->side[i], q);
            const Scalar cyl = (nsd>1 ? smap.l(Cf[1]->el[e]->side[i], q) : 0.0);
            const Scalar czl = (nsd>2 ? smap.l(Cf[2]->el[e]->side[i], q) : 0.0);
#else
            const Scalar cxl =          Cf[0]->el[e]->side[i]->u[ql];
            const Scalar cyl = (nsd>1 ? Cf[1]->el[e]->side[i]->u[ql] : 0.0);
            const Scalar czl = (nsd>2 ? Cf[2]->el[e]->side[i]->u[ql] : 0.0);
#endif
            const Scalar cln = cxl*nx + cyl*ny + czl*nz;

            // get right discont. velo field and multiply by the left normal
#ifdef REO_USE_GETSIDEMAPS
            const Scalar cxr =          smap.r(Cf[0]->el[e]->side[i], q);
            const Scalar cyr = (nsd>1 ? smap.r(Cf[1]->el[e]->side[i], q) : 0.0);
            const Scalar czr = (nsd>2 ? smap.r(Cf[2]->el[e]->side[i], q) : 0.0);
#else
            const Scalar cxr =          Cf[0]->el[e]->side[i]->link->u[qr];
            const Scalar cyr = (nsd>1 ? Cf[1]->el[e]->side[i]->link->u[qr] : 0.0);
            const Scalar czr = (nsd>2 ? Cf[2]->el[e]->side[i]->link->u[qr] : 0.0);
#endif
            const Scalar crn = cxr*nx + cyr*ny + czr*nz;

            // average normal velocity
            const Scalar cn = 0.5 * (cln + crn);

            // put numerical flux on the flux field sides
#ifdef REO_USE_GETSIDEMAPS
            convective_flux(cn, smap.l(Xs, q)*smap.l(rhos, q),
                            smap.r(Xs, q)*smap.r(rhos, q),
                            smap.l(Fs, q),
                            smap.r(Fs, q));
#else
            convective_flux(cn, Xs->u[ql]*rhos->u[ql],
                            Xs->link->u[qr]*rhos->link->u[qr],
                            Fs->u[ql],
                            Fs->link->u[qr]);
#endif

            // put interior flux on the state field sides
#ifdef REO_USE_GETSIDEMAPS
            smap.l(Us, q) *=  cln;
            smap.r(Us, q) *= -crn;
#else
            Us->u[ql] *=  cln;
            Us->link->u[qr] *= -crn;
#endif

          } else {

            const Scalar cn = cx*nx + cy*ny + cz*nz;

            // put numerical flux on the flux field sides
#ifdef REO_USE_GETSIDEMAPS
            convective_flux(cn, smap.l(Xs, q)*smap.l(rhos, q),
                            smap.r(Xs, q)*smap.r(rhos, q),
                            smap.l(Fs, q),
                            smap.r(Fs, q));

            // put interior flux on the state field sides
            smap.l(Us, q) *=  cn;
            smap.r(Us, q) *= -cn;
#else
            convective_flux(cn, Xs->u[ql]*rhos->u[ql],
                            Xs->link->u[qr]*rhos->link->u[qr],
                            Fs->u[ql],
                            Fs->link->u[qr]);

            // put interior flux on the state field sides
            Us->u[ql] *=  cn;
            Us->link->u[qr] *= -cn;
#endif
          }
        }
      }
    }
  }
}

/// Compute flux in given space dimension
void Multi_Comp_Trans::flux_in_one_sd(
    const Element *const Xae, ///< [in] mass fraction X_alpha
    const Element *const Fe,  ///< [in] side fluxes (uses side data only)
    const char sdi,           ///< [in] space dimension
    const dVector &rho,       ///< [in] density of mixture
    dVector &Sa_i             ///< [in/out] in: dX/dx_i, out: flux_i
) const {
  // sides of Fe are used only
  if ( params.get("use_ldg") ) {
    Xae->lift(Fe, Sa_i, sdi); // Sa_i += lift (u - \hat{u})
    Xae->project(Sa_i);
  }
  scale(porosity_phi*eff_diff, Sa_i);
  dvmul(rho, Sa_i);
  // now, Sa_i contains the hybrid diffusive flux S in space direction sdi
}

void Multi_Comp_Trans::compute_gradS_per_element(
    const Element *const Xae,      ///< [in] mass fraction alpha
    const Element *const rhomixe,  ///< [in] density of mixture
    const Element *const Ve,       ///< [in] side fluxes (uses side data only)
    Element *const Se,             ///< [out]
    dVector &grad_S                ///< [out]
) const {
  grad_S = 0.0; // reset

  if (nsd==3) {
    dVector Sx(wk1, Xae->qtot);
    dVector Sy(wk2, Xae->qtot);
    dVector Sz(wk3, Xae->qtot);
    // compute flux components Si
    Xae->gradient(Xae->u, Sx, Sy, Sz); // u_{,i}
    flux_in_one_sd(Xae, Ve, 'x', rhomixe->u, Sx);
    flux_in_one_sd(Xae, Ve, 'y', rhomixe->u, Sy);
    flux_in_one_sd(Xae, Ve, 'z', rhomixe->u, Sz);
    // compute gradient of flux grad_Sa
    Se->fill_sides( Sx, Sy, Sz );      // store normal diffusive flux on sides
    Se->gradient(Sx, Sx, 'x');         // Sx = S_{,x}
    Se->gradient(Sy, Sy, 'y');         // Sy = S_{,y}
    Se->gradient(Sz, Sz, 'z');         // Sz = S_{,z}
    grad_S += Sx;                      // grad_Sa += S_{,x}
    grad_S += Sy;                      // grad_Sa += S_{,y}
    grad_S += Sz;                      // grad_Sa += S_{,z}

  } else if (nsd==2) {
    dVector Sx(wk1, Xae->qtot);
    dVector Sy(wk2, Xae->qtot);
    // compute flux components Si
    Xae->gradient(Xae->u, Sx, Sy);     // u_{,i}
    flux_in_one_sd(Xae, Ve, 'x', rhomixe->u, Sx);
    flux_in_one_sd(Xae, Ve, 'y', rhomixe->u, Sy);
    // compute gradient of flux grad_qa
    Se->fill_sides( Sx, Sy );          // normal viscous flux on sides
    Se->gradient(Sx, Sx, 'x');         // Sx = S_{,x}
    Se->gradient(Sy, Sy, 'y');         // Sy = S_{,y}
    grad_S += Sx;                      // grad_Sqa += S_{,x}
    grad_S += Sy;                      // grad_Sa += S_{,y}

  } else if (nsd==1) {
    dVector Sx(wk1, Xae->qtot);
    // compute flux components Si
    Xae->gradient(Xae->u, Sx);         // u_{,i}
    flux_in_one_sd(Xae, Ve, 'x', rhomixe->u, Sx);
    // compute gradient of flux grad_qa
    Se->fill_sides( Sx, Sx );          // normal viscous flux on sides
    Se->gradient(Sx, Sx, 'x');         // Sx = S_{,x}
    grad_S += Sx;                      // grad_Sa += S_{,x}

  } else {
    comm->cerr()<< "Multi_Comp_Trans:diffusion -- illegal value of nsd"
                << endl;
    comm->exit(DGM::FAILURE);
  }
}


/// Compute (stabilized) Bassi and Rebay diffusive flux
void Multi_Comp_Trans::diffusion(
    const vField &Xf,   ///< [in] mass fraction
    const vField &rhof, ///< [in] density of mixture
    vField &Vf,         ///< [out] diffusive contribution to residual
    vField &Sf          ///< aux field (used only as side scratch space,
                        ///< interior not touched nor used, resulting side
                        ///< values not use outside)
    ) {
  Vf.zero();
  if (eff_diff == 0) return;

  average_flux( Xf, Vf, '+' );       // Vf's sides are average of the solution
  for (vField::size_type ifield=0; ifield < Xf.size(); ifield++) {
    for (LocalSize e=0; e<Xf[ifield]->ne; e++) {
      const Element *const rhomixe = rhof[0]->el[e];
      const Element *const Xae = Xf[ifield]->el[e];
      Element *const Vae = Vf[ifield]->el[e];
      Element *const Sae = Sf[ifield]->el[e];

      dVector grad_sigma_a(wk4, Xae->qtot); // flux gradient per species
      compute_gradS_per_element(Xae, rhomixe, Vae, Sae, grad_sigma_a);
      Vae->u += grad_sigma_a;
    }
  }

  Sf.share_sides();
  enforce_flux_bc(Sf);                 // put flux BC's on bc sides

  if ( stab != 0.0 ) {
    average_flux_plus_interior_penalty(Sf, Xf, rhof, Vf, stab);
    interior_penalty_boundary_correction( Xf, rhof, Vf, stab);
  } else {
    average_flux( Sf, Vf, '-' );
  }

  for (vField::size_type ifield=0; ifield < Sf.size(); ifield++) {
    for (LocalSize e=0; e<Sf[ifield]->ne; e++) {
      const Element *const Se = Sf[ifield]->el[e];
      Element *const Ve = Vf[ifield]->el[e];
      // (sides of Ve - sides of Se) --> interior Ve->u (lift)
      Se->lift( Ve, Ve->u );
    }
  }
}

Scalar Multi_Comp_Trans::compute_h_n(const Side *const Xs) const {
  const Scalar h_n = 0.5*(1.0/Xs->h_n_inv() + 1.0/Xs->link->h_n_inv());
  if (h_n == 0.0) comm->error("bug", DGM::FAILURE);
  return h_n;
}

/// Compute the flux on the sides \f$\hat{sigma}\f$
void Multi_Comp_Trans::average_flux_plus_interior_penalty(
    const vField &Sf,    ///< [in] normal flux field (use side values)
    const vField &Xf,    ///< [in] mass fraction (use side values)
    const vField &rhof,  ///< [in] density (use side values)
    vField &Vf,          ///< [out] diffusive contribution to residual
    const Scalar stab    ///< [in] diffusion stabilization parameter
) const {
  // comm->cout()<<"Multi_Comp_Trans::interior_penalty_flux(...)"<<endl;
#ifdef REO_USE_GETSIDEMAPS
  SideMap smap;
#endif
  for (vField::size_type ifield=0; ifield<Sf.size(); ifield++) {
    for (LocalSize e=0; e<Sf[ifield]->ne; e++) {
      const Element *const U   = Sf[ifield]->el[e];
      for (LocalSize i=0; i<Sf[ifield]->el[e]->nSides(); i++) {
        const Side *const Ss   = Sf[ifield]->el[e]->side[i];
        const Side *const Xs   = Xf[ifield]->el[e]->side[i];
        const Side *const rhos = rhof[ifield]->el[e]->side[i];
        Side *const Vs         = Vf[ifield]->el[e]->side[i];
        if (Xs->master()) {
          const Scalar h_n = compute_h_n(Xs);
#ifdef REO_USE_GETSIDEMAPS
          get_side_maps(Ss, Ss->link, smap.idl(), smap.idr());
#endif
          for (LocalSize q=0; q<Ss->qtot(); q++) {
#ifdef REO_USE_GETSIDEMAPS
            const Scalar rho_avg = 0.5*(smap.l(rhos, q) + smap.r(rhos, q));
            const Scalar C_11 = compute_C11( stab, h_n, rho_avg);
            smap.l(Vs, q) = 0.5*(smap.l(Ss, q) - smap.r(Ss, q))  // {S}
                         - C_11*(smap.l(Xs, q) - smap.r(Xs, q)); // [S]
            smap.r(Vs, q) = -smap.l(Vs, q);
#else
            const Ordinal ql = U->sideMap(Ss, q);
            const Ordinal qr = U->sideMap(Ss->link, q);
            const Scalar rho_avg = 0.5*(rhos->u[ql] + rhos->link->u[qr]);
            const Scalar C_11 = compute_C11( stab, h_n, rho_avg);
            Vs->u[ql] = 0.5*(Ss->u[ql] - Ss->link->u[qr])  // {S}
                         - C_11*(Xs->u[ql] - Xs->link->u[qr]); // [S]
            Vs->link->u[qr] = -Vs->u[ql];
#endif
          }
        }
      }
    }
  }
}

/// Compute the correction penalty flux on the sides \f$\hat{sigma}\f$
///
/// Needed, since average_flux_plus_interior_penalty() loops also over
/// boundary sides
void Multi_Comp_Trans::interior_penalty_boundary_correction(
    const vField &Xf,    ///< [in] mass fraction (use side values)
    const vField &rhof,  ///< [in] density (use side values)
    vField &Vf,          ///< [in/out] diffusive contribution to residual
    const Scalar stab    ///< [in] diffusion stabilization parameter
    ) const {
#ifdef REO_USE_GETSIDEMAPS
  SideMap smap;
#endif
  for (vField::size_type ifield=0; ifield < Xf.size(); ifield++) {
    for (LocalSize ibc=0; ibc<Xf[ifield]->nbc; ++ibc) {
      const Side *const Xs   = Xf[ifield]->bc[ibc]->S;
      const Element *const U   = Xs->elink;
      const Side *const rhos = rhof[ifield]->bc[ibc]->S;
      Side *const Vs         = Vf[ifield]->bc[ibc]->S;
      const Scalar h_n = compute_h_n(Xs);
#ifdef REO_USE_GETSIDEMAPS
      get_side_maps(Xs, Xs->link, smap.idl(), smap.idr());
#endif
      for(LocalSize q=0; q<Xs->qtot(); ++q) {
#ifdef REO_USE_GETSIDEMAPS
        const Scalar rho_avg = smap.l(rhos, q);
        const Scalar C_11 = compute_C11( stab, h_n, rho_avg);
        const Scalar correction = 0.5*C_11*( smap.l(Xs, q) - smap.r(Xs, q) );
        smap.l(Vs, q) -= correction;
        smap.r(Vs, q) += correction; // may not be needed (not lifted)
#else
        const Ordinal ql = U->sideMap(Xs, q);
        const Ordinal qr = U->sideMap(Xs->link, q);
        const Scalar rho_avg = rhos->u[ql];
        const Scalar C_11 = compute_C11( stab, h_n, rho_avg);
        const Scalar correction = 0.5*C_11*( Xs->u[ql] - Xs->link->u[qr] );
        Vs->u[ql] -= correction;
        Vs->link->u[qr] += correction; // may not be needed (not lifted)
#endif
      }
    }
  }
}


//===========================================================================
//                        BC database management
//===========================================================================
BC* Multi_Comp_Trans::make_BC( ifstream &in, string &tag ) {
  // comm->cout()<<"Multi_Comp_Trans::make_BC(ifstream &, string &)"<<endl;
  string command;
  if (!(in >> command)) return NULL;
  command = lowerCase(command);
  if (command == "dirichlet") {
    if (!(in >> tag))
      error("Multi_Comp_Trans::make_BC() Cannot read Dirichlet tag");
    return new DirichletBC(tag,in);
  } else if (command == "dirichlet_function") {
    if (!(in >> tag))
      error("Multi_Comp_Trans::make_BC() Cannot read "
            "DirichletBC_Function tag");
    return new DirichletBC_Function(tag,in,1);
  } else if (command == "unsteadydirichlet") {
    if (!(in >> tag))
      error("Multi_Comp_Trans::make_BC() Cannot read "
            "UnsteadyDirichletBC tag");
    return new UnsteadyDirichletBC(tag,in);
  } else if (command == "function") {
    if (!(in >> tag))
      error("Multi_Comp_Trans::make_BC() Cannot read FuncBC tag");
    return new FuncBC(tag,in,1);
  } else if (command == "robin") {
    if (!(in >> tag)) error("Multi_Comp_Trans::make_BC()  Cannot read "
                            "Neumann tag");
    return new RobinBC(tag,in,cx,cy,cz);
  } else if (command == "neumann") {
    if (!(in >> tag)) error("Multi_Comp_Trans::make_BC()  Cannot read "
                            "Neumann tag");
    return new NeumannBC(tag,in,cx,cy,cz);
  } else if (command == "outflow") {
    if (!(in >> tag)) error("Multi_Comp_Trans::make_BC()  Cannot read "
                            "outflow tag");
    return new OutflowBC(tag,in);
  } else {
    error("Multi_Comp_Trans::make_BC() Illegal BC type:  "+command);
  }
  return 0;
}

//===========================================================================
//                        Source database management
//===========================================================================

/// Construct source terms
Source::Ptr Multi_Comp_Trans::make_Source( ifstream &in, string &tag ) {
  // comm->cout() << "Multi_Comp_Trans::make_Source" << endl;
  string command;
  Source::Ptr p;
  if (!(in >> command)) return p;
  while (command[0]=='#') {  // eat comment lines
    string buffer;
    getline(in,buffer);
    if (!(in >> command)) return p;
  }
  if (lowerCase(command) == "constant") {
    if (!(in >> tag)) error("Multi_Comp_Trans::Cannot read ConstSource tag");
    p.reset( new ConstSource(tag,in,1) );
  } else if (lowerCase(command) == "file") {
    if (!(in >> tag)) error("Multi_Comp_Trans::Cannot read FileSource tag");
    p.reset( new FileSource(tag,in,U) );
  } else if (lowerCase(command) == "function") {
    if (!(in >> tag)) error("Multi_Comp_Trans::Cannot read FuncSource tag");
    p.reset( new FuncSource(tag,in,1) );
  } else if (lowerCase(command) == "transientmanufactured") {
    if (!(in >> tag))
      error("Multi_Comp_Trans::Cannot read TransientManufactured tag");
    p.reset( new TransientManufactured(tag, in) );
  } else if (lowerCase(command) == "transientgaussian") {
    if (!(in >> tag))
      error("Multi_Comp_Trans::Cannot read TransientGaussian tag");
    p.reset( new TransientGaussian(tag, in) );
  } else if (lowerCase(command) == "diracricker") {
    if (!(in >> tag)) error("Multi_Comp_Trans::Cannot read DiracRicker tag");
    p.reset( new DiracRicker(tag, in) );
  } else {
    error("Multi_Comp_Trans::make_Source() Illegal Source type");
  }
  return p;
}

/// Add source terms
void Multi_Comp_Trans::add_source(const vField &Uf, vField &Rf) {
  // comm->cout() << "Multi_Comp_Trans::add_source(vField &)" << endl;
  for (Source::db_citr i=Source_db.begin(); i!= Source_db.end(); ++i) {
    // comm->cout() << "Adding source: " << i->first << endl;
    i->second->apply( t, Uf, Rf );
  }
}



//===========================================================================
//                        Initial Conditions
//===========================================================================

Scalar Multi_Comp_Trans::circular_mass_fraction(const Element *const Xe,
                                                Ordinal q, Scalar radius,
                                                Scalar eps, Scalar innerval)
const {
  const Scalar x = Xe->C->x[q];
  const Scalar y = Xe->C->y[q];
  const Scalar r = sqrt(x*x + y*y);
  const Scalar inner_r = radius - eps/2.0;
  const Scalar outer_r = radius + eps/2.0;
  const bool in_transition = (inner_r < r and r < outer_r) ? true : false;
  Scalar val;
  if (in_transition) {
    val = innerval*(0.5+(0.5*cos(pi*(r-inner_r)/eps)));
  } else {
    if (r < radius) {
      val = innerval;
    } else {
      val = 0.0;
    }
  }
  return val;
}


void Multi_Comp_Trans::post_process_initial_field(vField &F, const bool proj){
  if (proj) {
    // project field to the polynomial space
    project( F );
  } else {
    comm->cout() << "WARNING:  No projection of Initial condition" << endl;
    for (vField::size_type i=0; i<F.size(); i++)
      for (LocalSize e=0; e<ne; e++)
        F[i]->el[e]->state = Element::Physical;
  }
}


/// Set the initial condition
void Multi_Comp_Trans::set_ic(vField &F, string ext) {
  // cout << "Multi_Comp_Trans::set_ic(vField &F, string)" << endl;
  t = 0.0; step = 0;
  const string fname = root+ext;
  ifstream in(fname.c_str());
  if (!in) {
    comm->error("Multi_Comp_Trans::Could not open initial condition file "
                +fname+"\n");
  }
  string buffer, command;
  getline(in,buffer);
  if (!(in>>command)) error("Cannot read IC code",1);
  getline(in,buffer);
  //  cout << "IC code = " << code << endl;
  if (lowerCase(command) == "given") {
    F.fill(in);
  } else if (lowerCase(command) == "restart") {
    string rstfile;
    if (!(in>>rstfile)) {
      comm->error("Cannot read restart file name from " + fname + "\n");
    }
    read(rstfile,F);
    comm->cout() << "Restarting from: " << rstfile << endl;
  } else if (lowerCase(command) == "circle") {
    Scalar radius, eps, innerval;
    if (!(in>>radius>>eps>>innerval)) {
      comm->error("Cannot read circular initial condition from " +fname+ "\n");
    }
    for (size_t e = 0; e < F[0]->el.size(); ++e) {
      for (LocalSize q = 0; q < F[0]->el[e]->qtot; ++q) {
        F[0]->el[e]->u[q] = circular_mass_fraction(
            F[0]->el[e], q, radius, eps, innerval);
      }
    }
    comm->cout() << "Created a circular initial condition." << endl;
  } else {
    comm->cerr() << lowerCase(command) << endl;
    comm->error("Multi_Comp_Trans::set_ic()  Unsupported IC type");
  }
  const bool projic = params.get("projic");
  post_process_initial_field( F, projic );
}

/// if required, read convective field from input file
void Multi_Comp_Trans::setup_convective_field(){
  comm->cout()<<"Reading convective field..."<<endl;
  read_convective_field( Cf, ".cfd" );
  Cf.fill_sides();
  Cf.share_sides();
  Cf.fill_bc_sides();  // make sure that boundary sides are valid
  //Cf.tecplot("cfield.dat","cfield"); // <-- not needed, use dgm_post
}

/// Set the initial condition
void Multi_Comp_Trans::read_convective_field(vField &F, string ext) {
  //cout<<"Multi_Comp_Trans::read_convective_field(vField &F, string)" << endl;
  const string fname = root+ext;
  ifstream in(fname.c_str());
  if (!in) {
    comm->cerr()<< "Multi_Comp_Trans::Could not open convective field file "
                << fname << endl;
    comm->exit(DGM::FAILURE);
  }
  string buffer, command;
  getline(in,buffer);
  if (!(in>>command)) error("Cannot read IC code",1);
  getline(in,buffer);
  //  cout << "IC code = " << code << endl;
  if (lowerCase(command) == "given") {
    F.fill(in);
  } else {
    comm->cerr() << lowerCase(command) << endl;
    comm->error("Multi_Comp_Trans::read_convective_field() "
        "Unsupported IC type");
  }
  const bool proj_conv_field = params.get("projcfd");
  post_process_initial_field( F, proj_conv_field );
}

} // namespace Reo
