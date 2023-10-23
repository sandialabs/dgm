/*=============================================================================
  Module:     Multi-Material Advection-Diffusion Module

  Contact:    S. Scott Collis
              sscoll@sandia.gov

  Copyright:  (c)2013 Sandia National Laboratories
=============================================================================*/

/** \file Multi_Mat_Adv_Diff.cpp
    \brief Multi material advection diffusion implementation
    \author Guglielmo Scovazzi
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
#include "Multi_Mat_Adv_Diff.hpp"
#include "Darcy.hpp"

#define REO_CONSISTENT_SIGMA

namespace Reo {

/// Constructor
Multi_Mat_Adv_Diff::Multi_Mat_Adv_Diff(
    DGM::ArgList &args,
    const DGM::Comm::Ptr comm_,
    const bool coupled_darcy_)
: Multi_Comp_Trans(args,comm_,coupled_darcy_), Xf(comm_), Xfextra(comm_),
  rhof(comm_) {
  comm->cout() << "Multi_Mat_Adv_Diff::Multi_Mat_Adv_Diff() on "
      << comm->NumProc() <<" processors." << endl;

  input("tecplot", true);
  input("plot3d", false);
  input("use_ldg", true);

  // set the number of fields in the domain
  Nfields = 1;                         // = 1 for a scalar problem

  // initialize material
  // tortuosity of aquifer
  const Scalar tau = input("tortuosity_tau" , 1.0);
  // diffusivity of aquifer (default is zero to allow turning off diffusivity)
  const Scalar D  = input("diffusivity_D" ,  0.0);
  eff_diff = tau * D;
  porosity_phi = input("porosity_phi", 1.0);

  rho.clear();
  rho.push_back(input("rho_CO2"     , 1.0));
  rho.push_back(input("rho_water"   , 1.0));

  input("projic", true);
  input("projcfd", true);

  // time step control
  CFLmax = input("CFLmax" , 0.5);
  dtmax = input("dtmax" , 1e9);
  tmax = input("tmax" , 1.0);

  int q;
  const int p = params.get("p");                     // polynomial order
  if ( !(q=params.get("q")) ) q = p + 2;   // number of quadrature points
  if (coupled_darcy) {
    const int pdarcy = darcy->params.get("p");
    if (p != pdarcy) {
      comm->error("\n Input error: Darcy and Adv_Diff need the same p!!!",
          DGM::FAILURE);
    }
  }

  nsd = params.get("nsd");                 // number of space dimensions
  stab = params.get("stab");

  // build a Field of Elements and Sides
  if (params.get("imesh")) {
    Mesh mesh(params);
    U.push_back( new Field(p, q, mesh, root, "u", Field::FULL, comm ) );
    partition = U[0]->partition;
  } else if (params.get("bmesh")) {
    U.push_back( new Field(p, q, root, "u", partition, 1, Reo::NumEqntype,
                           p2i(MULTI_MAT_ADV_DIFF), comm ) );
  } else {
    U.push_back( new Field(p, q, root, "u", partition, comm ) );
  }

  // set some additional domain parameters
  ne = U[0]->ne;
  if (nsd != U[0]->nsd()) comm->error("\n nsd mismatch", DGM::FAILURE);

#ifdef REO_USE_GETSIDEMAPS
  setup_side_maps();
#endif

  // make auxiliary Fields using copy constructor
  Ut.push_back( new Field(U[0], root, "Ut") );
  Vf.push_back( new Field(U[0], root, "Vf") );
  Xf.push_back( new Field(U[0], root, "Xf") );
  Xfextra.push_back( new Field(U[0], root, "Xfextra") );
  rhof.push_back( new Field(U[0], root, "rhof") );

  // setup vField names
  U.set_name("U");
  Ut.set_name("Ut");
  Vf.set_name("Vf");
  Xf.set_name("Xf");
  Xfextra.set_name("Xfextra");
  rhof.set_name("rhof");

#ifdef MAKE_CONTIGUOUS
  make_contiguous();
#endif

  // convective field
  Cf.set_name("Cf");
  Cf.push_back( new Field(U[0], root, "Cx") );
  if (nsd>1) Cf.push_back( new Field(U[0], root, "Cy") );
  if (nsd>2) Cf.push_back( new Field(U[0], root, "Cz") );
#ifdef MAKE_CONTIGUOUS
  Cf.reset_storage();     // make the vField contiguous
#endif

  if (not coupled_darcy) {
    setup_convective_field();
  }

  // initial pressure solution or truth solution
  if (coupled_darcy) {
    comm->cout() << "Reading initial pressure solution" << endl;
    darcy->set_given_field(darcy->U, ".ic", true);
    darcy->write(0, darcy->U);
  }

  // set parameters that should be the same for both fields
  if (myparams.get("use_ldg")) // turn on or off LDG for testing
    comm->cout() << "Multi_Mat: Enabled LDG" << endl;
  else
    comm->cout() << "Multi_Mat: Disabled LDG" << endl;

  // workspace
  wk1.resize(max(Lmax(),Qmax()));
  wk2.resize(max(Lmax(),Qmax()));
  wk3.resize(max(Lmax(),Qmax()));
  wk4.resize(max(Lmax(),Qmax()));

  // make sure that storage is initialized
  zero_all_fields();

  // make analysis object
  response = Response::factory(U, this);

  setup_BCdb();

  setup_Sourcedb();

  set_TimeInt();

  verifyBCs(Xf);

#ifdef REO_CONSISTENT_SIGMA
#ifdef DGM_USE_EPETRA
#ifdef DGM_USE_GENERAL_GHOSTING
  // ghosting provides an easy way to share neighbor element data, but I don't
  // want to mess with ghosting in this class. So I use a dummy vField that is
  // ghosted and use its shared data to fill in data on the virtual parallel
  // sides that they are missing. Right now, this is only
  // h_n_inv, but the polynomial order p would be another candidate.
  // repeat this for all fields, that use side geometry information.
  // This way, share_sides() works for unghosted fields as before
  vField Dummy(comm_);
  Dummy.push_back( new Field(Xf[0], root, "dummy") );
  Dummy.reset_storage();
  Dummy.ghost();
  comm->cout() << "  Ghosting of dummy is done" << endl;
  for (vField::size_type ifield = 0; ifield < Xf.size(); ifield++) {
    for (LocalSize iele = 0; iele < Xf[ifield]->ne; iele++) {
      Element* Xele = Xf[ifield]->el[iele];
      Element* Dele = Dummy[0]->el[iele]; // a scalar field, so use [0]
      for (Ordinal iside = 0; iside < Xele->nSides(); iside++) {
        if (Xele->side[iside]->master()) {
          Xele->side[iside]->link->h_n_inv(Dele->side[iside]->link->h_n_inv());
        }
      }
    }
  }
#endif
#endif
#endif

}

/// needed for implicit computations using Epetra vectors and matrices
void Multi_Mat_Adv_Diff::make_contiguous() {
  U.reset_storage();
  Ut.reset_storage();
  Vf.reset_storage();
  Xf.reset_storage();
  Xfextra.reset_storage();
  rhof.reset_storage();
}

/// Print usage for the Multi_Mat_Adv_Diff Domain
void Multi_Mat_Adv_Diff::showUsage() {
  comm->cout()
    << "Multi_Mat_Adv_Diff Class Options \n"
    << "----------------------------------------------------------------\n"
    << "----------------------------------------------------------------\n";
}

/// compute element Peclet number (use a constant value for each element)
void Multi_Mat_Adv_Diff::compute_element_Peclet_number(vField &Pef) const {
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

/** \warning Does not work in parallel, should gather to master */
int Multi_Mat_Adv_Diff::plot(const string &rst) {
  if (comm->NumProc() > 1)
    comm->error("Works only sequentially", DGM::FAILURE);
  read( rst, Xf );
  compute_Uf(Xf, U);
  split_into_massfraction(U, Xf, Xfextra, rhof );
  const string rootname(rst.substr(0,rst.find(".rst")));
  ostringstream caption;
  caption << " at t = " << scientific << t << ", step = " << step;
  if (comm->Master()) {
    // U.tecplot(rootname+".U.dat","U a = X_a*rho"+caption.str());
    Xf.tecplot(rootname+".X.dat","X_a"+caption.str());
    // Xfextra.tecplot(rootname+".Xextra.dat","X extra"+caption.str());
    rhof.tecplot(rootname+".rho.dat","rho"+caption.str());
    if (myparams.get("plot3d")) {
      Xf.plot3d_x(rootname+".xyz");
      Xf.plot3d_q(rootname+".q");
    }
  }

  // in the coupled case, the convective velocity has to be computed first
  if (coupled_darcy) {
    // copy density of mixture into darcy Gf vector
    for (LocalSize e=0; e<rhof[0]->ne; e++) {
      darcy->Gf[0]->el[e]->u = rhof[0]->el[e]->u;
    }
    // mimic the default naming convention
    ostringstream darcy_rst_fname;
    darcy_rst_fname << darcy->root << "." << this->step << ".rst";
    read( darcy_rst_fname.str(), darcy->U );
    darcy->postprocess_Darcy_velocity( darcy->U, darcy->Ut, Cf );
  }
  if (comm->Master()) {
    // convective field
    vField Cfout(comm); // convective field for output
    Cfout.set_name("Cf");
    Cfout.push_back( new Field(U[0], root, "Cx") );
    if (nsd>1) Cfout.push_back( new Field(U[0], root, "Cy") );
    if (nsd>2) Cfout.push_back( new Field(U[0], root, "Cz") );
    Cfout.push_back( new Field(U[0], root, "abs(C)") );
#ifdef MAKE_CONTIGUOUS
    Cfout.reset_storage();     // make the vField contiguous
#endif
    for (LocalSize e=0; e<Cfout[0]->ne; e++) {
      for (LocalSize isd=0; isd<nsd; isd++) {
        Cfout[isd]->el[e]->u = Cf[isd]->el[e]->u;
      }
      for (LocalSize q=0; q<Cfout[nsd]->el[e]->qtot; q++) {
        Scalar usqrsum = 0.0;
        for (LocalSize isd=0; isd<nsd; isd++) {
          usqrsum += pow(Cfout[isd]->el[e]->u[q],2);
        }
        Cfout[nsd]->el[e]->u[q] = sqrt(usqrsum);
      }
    }
    Cfout.tecplot(rootname+".C.dat","Darcy velocity "+caption.str());
  }

  // output an element Peclet number (use Ut[0] as work array)
  //compute_element_Peclet_number(Ut);
  //if (comm->Master()) Ut.tecplot(rootname+".Pe.dat",
  //                               "Peclet number"+caption);

  return 0;
}

/// Zero all fields
void Multi_Mat_Adv_Diff::zero_all_fields() {
  Domain::zero_all_fields();
}

/// Compute critical timestep
/** Estimate is taken from AdvDiff where the polynomial order dependence is
    incorporated in the length scale computation for each integration point
    (he[i]). */
Scalar Multi_Mat_Adv_Diff::compute_critical_timestep() const {
  Scalar dtcritical = 1.0e9;        // minimum timestep over all elements
  for (LocalSize e=0; e<U[0]->ne; e++) {
    std::vector<Element*> Ce;
    Ce.push_back(Cf[0]->el[e]);
    if (nsd>1) Ce.push_back(Cf[1]->el[e]);
    if (nsd>2) Ce.push_back(Cf[2]->el[e]);
    const Ordinal qtot = Ce[0]->qtot;
    dVector c(qtot); c = 0;         // advective velocity at quadrature points
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
Scalar Multi_Mat_Adv_Diff::set_time_step(vField &) {
  const Scalar dtcritical = compute_critical_timestep();
  //cout << "CFLmax = " << cfl << endl;
  // max. 20% increase of time step size per time step
  dt = min(dt*1.2, min(dtmax, CFLmax * dtcritical ));
  const Scalar cfl = dt/dtcritical;
  //cout << "cfl = " << cfl << ", dt = " << dt << endl;
  return cfl;
}

/// add viscous flux to Darcy source term
void Multi_Mat_Adv_Diff::add_viscflux_to_source(
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
void Multi_Mat_Adv_Diff::compute_darcy_source(
    vField &Sf   ///< [out] Darcy source field
    ) const {
  Sf.zero();
  for (vField::size_type ifield=0; ifield < Vf.size(); ifield++) {
    add_viscflux_to_source( *Vf[ifield], rho[ifield], rho[Vf.size()], *Sf[0] );
  }
}

void Multi_Mat_Adv_Diff::prestep(vField& U, const Ordinal lstep_minus_one,
                                 const Ordinal substep, const Scalar t
) {
  //cout << "time integrator substep: " << substep << endl;
  if (substep == 0)
    solve_Darcy = true;
}

void Multi_Mat_Adv_Diff::time_derivative(
    vField & Uf, ///< [in]  vector field corresponding to rho * X[nfields]
    vField & Rf  ///< [out] flux field Rf[nfields]
) {
  // reset R
  Rf.zero();

  split_into_massfraction(Uf, Xf, Xfextra, rhof );
  if (step%ntout==0) Xf.norm();

  // fill sides and enforce Dirichlet BC
  Xf.fill_sides();                   // put solution on the sides
  Xf.share_sides();
  enforce_bc(Xf);                    // update bc side values

  // fill sides and copy element sides to boundary sides
  rhof.fill_sides();
  rhof.share_sides();
  rhof.fill_bc_sides();

  diffusion( Xf, rhof, Vf, Rf);

  // form residual
  scale( -1.0, Vf);          // Currently on LHS
  add( Vf, Rf );        // add in diffusive contribution

  if (coupled_darcy and solve_Darcy) {

    // Darcy doesn't know that the time changed
    darcy->t = this->t;
    darcy->step = this->step;
    darcy->lstep = this->lstep;
    darcy->Ntout = this->Ntout;

    // compute darcy source and put it into Sf
    compute_darcy_source( darcy->Sf );

    // copy density of mixture into darcy Gf vector
    for (LocalSize e=0; e<rhof[0]->ne; e++) {
      darcy->Gf[0]->el[e]->u = rhof[0]->el[e]->u;
    }

    // call darcy flow computation to obtain convective velocity using Sf
    darcy->solve_and_get_Darcy_velocity( Cf );
    solve_Darcy = false; // use prestep() to enable another solve

    // debug, may be removed if everything works...
    if ( !darcy->U[0]->finite() ) {
      comm->error("Darcy pressure is not finite", DGM::FAILURE);
    }
  }

  // fill sides and enforce Dirichlet BC
  Xf.fill_sides();
  Xf.share_sides();
  enforce_bc(Xf);

  // fill sides and copy element sides to boundary sides
  Uf.fill_sides();
  Uf.share_sides();
  Uf.fill_bc_sides();

  // fill sides and copy element sides to boundary sides
  Cf.fill_sides();
  Cf.share_sides();
  Cf.fill_bc_sides();
  if (step%ntout==0) Cf.norm();

  // compute conv.-diff. problem using darcy flow convective velocity
  convection( Xf, rhof, Uf, Vf ); add( Vf, Rf );
  add_source( Uf, Rf );
  scale( 1.0/porosity_phi, Rf );
  project( Rf );
}

/// add convective flux to Ff
void Multi_Mat_Adv_Diff::convection(
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
void Multi_Mat_Adv_Diff::variable_convection_Euler_Lagrange(
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
          << "Multi_Mat_Adv_Diff:variable_convection_Euler_Lagrange "
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
void Multi_Mat_Adv_Diff::constant_convection(
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
      comm->cerr()<< "Multi_Mat_Adv_Diff:constant_convection -- "
                  << "illegal value of nsd"
                  << endl;
      comm->exit(DGM::FAILURE);
    }
  }

  // debug, may be removed if everything works...
  if ( !Uf[0]->finite() ) error("Uf is not finite");
  if ( !Ff[0]->finite() ) error("Ff is not finite");
}

/// Compute the Advective flux
/** For descriptions of the numerical fluxes See: E.F. Toro, "Riemann
    Solvers and Numerical Methods for Fluid Dynamics," 2nd Edition,
    Springer, 1999.*/
void Multi_Mat_Adv_Diff::convective_flux(
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
        Element *const U = Xs->elink;
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
          const Ordinal ql = U->sideMap(Us, q);
          const Ordinal qr = U->sideMap(Us->link, q);
#endif
          const Scalar nx =          Us->nx(ql);
          const Scalar ny = (nsd>1 ? Us->ny(ql) : 0.0 );
          const Scalar nz = (nsd>2 ? Us->nz(ql) : 0.0 );

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
            Multi_Comp_Trans::convective_flux(cn, smap.l(Xs, q)*smap.l(rhos, q),
                                              smap.r(Xs, q)*smap.r(rhos, q),
                                              smap.l(Fs, q),
                                              smap.r(Fs, q));
            // put interior flux on the state field sides
            smap.l(Us, q) *=  cln;
            smap.r(Us, q) *= -crn;
#else
            Multi_Comp_Trans::convective_flux(cn, Xs->u[ql]*rhos->u[ql],
                                              Xs->link->u[qr]*rhos->link->u[qr],
                                              Fs->u[ql],
                                              Fs->link->u[qr]);
            // put interior flux on the state field sides
            Us->u[ql] *=  cln;
            Us->link->u[qr] *= -crn;
#endif

          } else {

            const Scalar cn = cx*nx + cy*ny + cz*nz;

            // put numerical flux on the flux field sides
#ifdef REO_USE_GETSIDEMAPS
            Multi_Comp_Trans::convective_flux(cn, smap.l(Xs, q)*smap.l(rhos, q),
                                              smap.r(Xs, q)*smap.r(rhos, q),
                                              smap.l(Fs, q),
                                              smap.r(Fs, q));
            // put interior flux on the state field sides
            smap.l(Us, q) *=  cn;
            smap.r(Us, q) *= -cn;
#else
            Multi_Comp_Trans::convective_flux(cn, Xs->u[ql]*rhos->u[ql],
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
void Multi_Mat_Adv_Diff::flux_in_one_sd(
    const Element *const Xae, ///< [in] mass fraction X_alpha
    const Element *const Fe,  ///< [in] side fluxes (uses side data only)
    const char sdi,           ///< [in] space dimension
    const dVector &rho,       ///< [in] density of mixture
    dVector &Sa_i             ///< [in/out] in: dX/dx_i, out: flux_i
) const {
  // sides of Fe are used only
  if ( myparams.get("use_ldg") ) {
    Xae->lift(Fe, Sa_i, sdi); // Sa_i += lift (u - \hat{u})
    Xae->project(Sa_i);
  }
  scale(porosity_phi*eff_diff, Sa_i);
  dvmul(rho, Sa_i);
  // now, Sa_i contains the hybrid diffusive flux S in space direction sdi
}

void Multi_Mat_Adv_Diff::compute_gradS_per_element(
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
    comm->cerr()<< "Multi_Mat_Adv_Diff:diffusion -- illegal value of nsd"
                << endl;
    comm->exit(DGM::FAILURE);
  }
}


/// Compute (stabilized) Bassi and Rebay diffusive flux
void Multi_Mat_Adv_Diff::diffusion(
    const vField &Xf,   ///< [in] mass fraction
    const vField &rhof, ///< [in] density of mixture
    vField &Vf,         ///< [out] diffusive contribution to residual
    vField &Sf          ///< aux field (used only as side scratch space,
                        ///< interior not touched nor used, resulting side
                        ///< values not used outside)
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

Scalar Multi_Mat_Adv_Diff::compute_h_n(const Side *const Xs) const {
//  if (Xs->h_n_inv - Xs->link->h_n_inv > 1.0e-10) {
//    cout << Xs->h_n_inv - Xs->link->h_n_inv << endl;
//  }
  const Scalar h_n = 0.5*(1.0/Xs->h_n_inv() + 1.0/Xs->link->h_n_inv());
  if (h_n == 0.0) comm->error("bug", DGM::FAILURE);
  return h_n;
}

/// Compute the flux on the sides \f$\hat{sigma}\f$
void Multi_Mat_Adv_Diff::average_flux_plus_interior_penalty(
    const vField &Sf,    ///< [in] normal flux field (use side values)
    const vField &Xf,    ///< [in] mass fraction (use side values)
    const vField &rhof,  ///< [in] density (use side values)
    vField &Vf,          ///< [out] diffusive contribution to residual
    const Scalar stab    ///< [in] diffusion stabilization parameter
) const {
  // comm->cout()<<"Multi_Mat_Adv_Diff::interior_penalty_flux(...)"<<endl;
#ifdef REO_USE_GETSIDEMAPS
  SideMap smap;
#endif
  for (vField::size_type ifield=0; ifield<Sf.size(); ifield++) {
    for (LocalSize e=0; e<Sf[ifield]->ne; e++) {
      for (LocalSize i=0; i<Sf[ifield]->el[e]->nSides(); i++) {
        const Side *const Ss   = Sf[ifield]->el[e]->side[i];
        const Side *const Xs   = Xf[ifield]->el[e]->side[i];
        const Element *const U   = Xs->elink;
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
void Multi_Mat_Adv_Diff::interior_penalty_boundary_correction(
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
BC* Multi_Mat_Adv_Diff::make_BC( ifstream &in, string &tag ) {
  // comm->cout()<<"Multi_Mat_Adv_Diff::make_BC(ifstream &, string &)"<<endl;
  string command;
  if (!(in >> command)) return NULL;
  command = lowerCase(command);
  if (command == "dirichlet") {
    if (!(in >> tag))
      error("Multi_Mat_Adv_Diff::make_BC() Cannot read Dirichlet tag");
    return new DirichletBC(tag,in);
  } else if (command == "dirichlet_function") {
    if (!(in >> tag))
      error("Multi_Mat_Adv_Diff::make_BC() Cannot read "
            "DirichletBC_Function tag");
    return new DirichletBC_Function(tag,in,1);
  } else if (command == "unsteadydirichlet") {
    if (!(in >> tag))
      error("Multi_Mat_Adv_Diff::make_BC() Cannot read "
            "UnsteadyDirichletBC tag");
    return new UnsteadyDirichletBC(tag,in);
  } else if (command == "function") {
    if (!(in >> tag))
      error("Multi_Mat_Adv_Diff::make_BC() Cannot read FuncBC tag");
    return new FuncBC(tag,in,1);
  } else if (command == "robin") {
    if (!(in >> tag)) error("Multi_Mat_Adv_Diff::make_BC()  Cannot read "
                            "Neumann tag");
    return new RobinBC(tag,in,cx,cy,cz);
  } else if (command == "neumann") {
    if (!(in >> tag)) error("Multi_Mat_Adv_Diff::make_BC()  Cannot read "
                            "Neumann tag");
    return new NeumannBC(tag,in,cx,cy,cz);
  } else if (command == "outflow") {
    if (!(in >> tag)) error("Multi_Mat_Adv_Diff::make_BC()  Cannot read "
                            "outflow tag");
    return new OutflowBC(tag,in);
  } else {
    error("Multi_Mat_Adv_Diff::make_BC() Illegal BC type:  "+command);
  }
  return 0;
}

//===========================================================================
//                        Source database management
//===========================================================================

/// Construct source terms
Source::Ptr Multi_Mat_Adv_Diff::make_Source( ifstream &in, string &tag ) {
  // comm->cout() << "Multi_Mat_Adv_Diff::make_Source" << endl;
  string command;
  Source::Ptr p;
  if (!(in >> command)) return p;
  while (command[0]=='#') {  // eat comment lines
    string buffer;
    getline(in,buffer);
    if (!(in >> command)) return p;
  }
  if (lowerCase(command) == "constant") {
    if (!(in >> tag)) error("Multi_Mat_Adv_Diff::Cannot read ConstSource tag");
    p.reset( new ConstSource(tag,in,1) );
  } else if (lowerCase(command) == "file") {
    if (!(in >> tag)) error("Multi_Mat_Adv_Diff::Cannot read FileSource tag");
    p.reset( new FileSource(tag,in,U) );
  } else if (lowerCase(command) == "function") {
    if (!(in >> tag)) error("Multi_Mat_Adv_Diff::Cannot read FuncSource tag");
    p.reset( new FuncSource(tag,in,1) );
  } else if (lowerCase(command) == "transientmanufactured") {
    if (!(in >> tag))
      error("Multi_Mat_Adv_Diff::Cannot read TransientManufactured tag");
    p.reset( new TransientManufactured(tag, in) );
  } else if (lowerCase(command) == "transientgaussian") {
    if (!(in >> tag))
      error("Multi_Mat_Adv_Diff::Cannot read TransientGaussian tag");
    p.reset( new TransientGaussian(tag, in) );
  } else if (lowerCase(command) == "diracricker") {
    if (!(in >> tag)) error("Multi_Mat_Adv_Diff::Cannot read DiracRicker tag");
    p.reset( new DiracRicker(tag, in) );
  } else {
    error("Multi_Mat_Adv_Diff::make_Source() Illegal Source type");
  }
  return p;
}

/// Add source terms
void Multi_Mat_Adv_Diff::add_source(const vField &Uf, vField &Rf) {
  // comm->cout() << "Multi_Mat_Adv_Diff::add_source(vField &)" << endl;
  for (Source::db_citr i=Source_db.begin(); i!= Source_db.end(); ++i) {
    // comm->cout() << "Adding source: " << i->first << endl;
    i->second->apply( t, Uf, Rf );
  }
}

/// Output the boundary statistics
void Multi_Mat_Adv_Diff::write_bndry_stats() {
  //cout<<"Domain::write_bndry_stats()"<<endl;

  if (!Xf[0]->bndry_stats->valid) return;

  dVector X, rho, cx, cy, cz;
  Xf[0]->bndry_stats->get_solution( X );
  rhof[0]->bndry_stats->get_solution( rho );
                Cf[0]->bndry_stats->get_solution( cx );
  if (nsd >= 2) Cf[1]->bndry_stats->get_solution( cy );
  if (nsd >= 3) Cf[2]->bndry_stats->get_solution( cz );

  const LocalSize qtot = X.size();
  dVector wk(qtot);
  dVector fx(qtot);
  dVector fy(qtot);
  dVector fz(qtot);

  // convection
  dvmul(X, rho, wk);
                dvmul(wk, cx, fx);
  if (nsd >= 2) dvmul(wk, cy, fy);
  if (nsd >= 3) dvmul(wk, cz, fz);

  // diffusion
  dVector X_x, X_y, X_z;
  if      (nsd == 1) Xf[0]->bndry_stats->get_solution_gradient(X_x);
  else if (nsd == 2) Xf[0]->bndry_stats->get_solution_gradient(X_x, X_y);
  else if (nsd == 3) Xf[0]->bndry_stats->get_solution_gradient(X_x, X_y, X_z);
  wk = 0.0;
  dvadd(rho, wk);
  scale(-porosity_phi*eff_diff, wk);
                dvmulsum(wk, X_x, fx);
  if (nsd >= 2) dvmulsum(wk, X_y, fy);
  if (nsd >= 3) dvmulsum(wk, X_z, fz);

  Scalar flux = 0.0;
  if      (nsd == 1) flux=Xf[0]->bndry_stats->flux_boundary_integral(fx);
  else if (nsd == 2) flux=Xf[0]->bndry_stats->flux_boundary_integral(fx,fy);
  else if (nsd == 3) flux=Xf[0]->bndry_stats->flux_boundary_integral(fx,fy,fz);
  else comm->error("4d computations not supported!");

#ifdef DGM_PARALLEL
  const Scalar lflux = flux;
  comm->SumAll( &lflux, &flux, 1 );
#endif
  if (comm->Master()) {
    const string fname(root+".bflx");
    ofstream fluxfile(fname.c_str(), std::ios::app);
    fluxfile << std::setw(10) << step
             << std::setw(16) << std::scientific << t
             << std::setw(16) << std::scientific << flux
             << std::endl;
    fluxfile.flush();
  }
  // bugfix: write_side_stats fills sides of Xf, which gives funny whiggles
  // in the boundary flux output above. At least, it appears to be
  // the source of the problem. So I comment it out and the whiggles are gone.
//  if (step%Ntout==0) Xf.write_side_stats(step);
}


//===========================================================================
//                        Basic Domain Solver
//===========================================================================

/// Solve the equations for this Domain
int Multi_Mat_Adv_Diff::solve() {
  enum Status { Normal=0, Restart=1 };
  static Format sci(2,8,'e');
  Status status = Normal;
  if (comm->Master()) {               // history file
    string fname = root+".his";
    his = fopen(fname.c_str(),"a+");  // append to end of file
  }
  set_ic(Xf);
  compute_Uf(Xf, U);
  if (step==0) {
    write(step,Xf);
  }
#ifndef DGM_PARALLEL
  if (nsd<3) {
    ostringstream caption;
    caption << "Initial condition at t = " << scientific << t
        << ", step = " << step;
    Xf.tecplot(root+"_ic_Xf.dat",caption.str());
    U.tecplot(root+"_ic_Uf.dat",caption.str());
  }
#endif
  comm->cout() << "Advancing solution " << Nt << " time steps (max. until time "
      << tmax << " )" << endl;
  Scalar stime=0, ttime=0;
  int cnt=0;
  bool stop_time_integration = false;
  Stopwatch cpu; cpu.start();
  for (lstep=1; lstep<=Nt; lstep++) {
    step++;
    CFL = set_time_step(U);
    if (t + dt > tmax) {
      dt = tmax - t;  // run exactly till final time tmax
      stop_time_integration = true;
    }
    time_int->advance(this);
    const Scalar ctime = cpu.restart();
    if (lstep>1) {
      ttime += ctime;
      stime += ctime*ctime;
      cnt++;
    }
    if (step%ntout==0) {
      comm->cout()<<"Step: "<<setw(8)<<step
        <<", t = "<<sci(t)
        <<", dt = "<<sci(dt)
        <<", CFL = "<<sci(CFL)
        <<", dtCPU = "<<sci(ctime)
        <<", dt/dtCPU = "<<setprecision(1)<<(dt/ctime)<<endl;
    }
    if (comm->Master()) {
      fprintf(his,"%5lld %11.4e %11.4e %11.4e %11.4e\n",(long long)step,t,dt,
              CFL,ctime);
    }
    if (step%Ntout==0 || stop_time_integration)  {
      split_into_massfraction(U, Xf, Xfextra, rhof );
      write(step, Xf);
      cpu.restart();
    }
    write_bndry_stats();
    if (stop_time_integration) break;
  }
  if (t < tf) status = Restart;
  Scalar atime=0, otime=0;
  comm->SumAll( &ttime, &atime, 1 );  // average cpu time
  comm->SumAll( &stime, &otime, 1 );  // standard deviation of the cpu time
  const int nproc = max(1,cnt*comm->NumProc());
  atime /= nproc; otime /= nproc;
  const Scalar stdev = ::sqrt(otime - atime*atime);
  comm->cout() << "Average CPU time per step:" << sci(atime)
         << ", std deviation:" << sci(stdev) << endl;
  split_into_massfraction(U, Xf, Xfextra, rhof );
  write(root+".rst", Xf);
  if (coupled_darcy) write(darcy->root+".rst", darcy->U);
  if (step%ntout==0) Xf.norm();
  if (step%Ntout!=0) write_bndry_stats();
  if (comm->Master()) fclose(his);
  return status;
}

//===========================================================================
//                        Initial Conditions
//===========================================================================

Scalar Multi_Mat_Adv_Diff::circular_mass_fraction
  (const Element *const Xe, Ordinal q, Scalar radius,
   Scalar eps, Scalar innerval) const {
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


void Multi_Mat_Adv_Diff::post_process_initial_field(vField &F,
                                                    const bool proj){
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
void Multi_Mat_Adv_Diff::set_ic(vField &F, string ext) {
  // cout << "Multi_Mat_Adv_Diff::set_ic(vField &F, string)" << endl;
  t = 0.0; step = 0;
  const string fname = root+ext;
  ifstream in(fname.c_str());
  if (!in) {
    comm->error("Multi_Mat_Adv_Diff::Could not open initial condition file "
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
    comm->error("Multi_Mat_Adv_Diff::set_ic()  Unsupported IC type");
  }
  const bool projic = myparams.get("projic");
  post_process_initial_field( F, projic );
}

/// compute U from X1
void Multi_Mat_Adv_Diff::compute_Uf(
    const vField &Xf,
    vField &Uf
) const {
  const Scalar rho1 = rho[0];
  const Scalar rho2 = rho[Vf.size()];
  for (LocalSize e=0; e<Uf[0]->ne; e++) {
    const Element *const Xe = Xf[0]->el[e];
    Element *const Ue = Uf[0]->el[e];

    // above
    Ue->u = Xe->u;
    Ue->u *= rho2;

    // below
    dVector quotient(wk1, Xe->u.size());
    quotient = Xe->u;
    quotient *= rho2/rho1 - 1.0;
    quotient += 1.0;

    // division
    for (Ordinal i=0; i<Xe->u.size(); i++) {
      Ue->u[i] = Ue->u[i]/quotient[i];
    }
  }
}

/// split U into rho and X1
void Multi_Mat_Adv_Diff::split_into_massfraction(
    const vField &Uf,
    vField &Xf,
    vField &Xfextra,
    vField &rhomixf
) const {

  const Scalar rho1 = rho[0];
  const Scalar rho2 = rho[Vf.size()];

  for (LocalSize e=0; e<Uf[0]->ne; e++) {

    // compute rho of mixture
    const Element *const Uae = Uf[0]->el[e];
    Element *const rhomixe = rhomixf[0]->el[e];
    rhomixe->u = Uae->u;
    rhomixe->u *= 1.0 - rho2/rho1;
    rhomixe->u += rho2;

    // check, whether X1 or X2 grow beyond meaningful numbers
    const Scalar errortol = 1.0e-1;

    // compute mass fraction 1
    Element *const X1e  = Xf[0]->el[e];
    for (LocalSize i=0; i<X1e->u.size(); i++) {
      X1e->u[i] = Uae->u[i]/rhomixe->u[i];
      if (X1e->u[i] < -errortol or X1e->u[i] > (1.0 + errortol)) {
        comm->cerr()
            << "Multi_Mat_Adv_Diff::split_into_massfraction: "
               "X1 = "<< X1e->u[i] <<" not between 0 and 1!"
            << endl;
        comm->exit(DGM::FAILURE);
      }
    }

    // compute remaining mass fraction
    Element *const X2e  = Xfextra[0]->el[e];
    for (LocalSize i=0; i<X2e->u.size(); i++) {
      X2e->u[i] = 1.0 - X1e->u[i];
      // There is no need to check for bounds, if X1 is checked.
    }

  }
}

/// if required, read convective field from input file
void Multi_Mat_Adv_Diff::setup_convective_field(){
  comm->cout()<<"Reading convective field..."<<endl;
  read_convective_field( Cf, ".cfd" );
  Cf.fill_sides();
  Cf.share_sides();
  Cf.fill_bc_sides();  // make sure that boundary sides are valid
  //Cf.tecplot("cfield.dat","cfield"); // <-- not needed, use dgm_post
}

/// Set the initial condition
void Multi_Mat_Adv_Diff::read_convective_field(vField &F, string ext) {
  //cout<<"Multi_Mat_Adv_Diff::read_convective_field(vField &F, string)"
  //    << endl;
  const string fname = root+ext;
  ifstream in(fname.c_str());
  if (!in) {
    comm->cerr()<< "Multi_Mat_Adv_Diff::Could not open convective field file "
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
    comm->error("Multi_Mat_Adv_Diff::read_convective_field() "
        "Unsupported IC type");
  }
  post_process_initial_field( F, myparams.get("projcfd") );
}

} // namespace Reo
