/*=============================================================================
  Module: Advection-Diffusion Module

  Contact:    S. Scott Collis
              sscoll@sandia.gov

  Copyright:  (c)2003 Rice University
              (c)2008 Sandia National Laboratories
=============================================================================*/

/** \file Adv_Diff.cpp
    \brief Advection diffusion implementation
    \author Scott Collis
    \copyright (c)2003 Rice University
    \copyright (c)2014 Sandia National Laboratories
*/

// DGM includes
#include "Comm.hpp"
#include "Domain.hpp"
#include "Field.hpp"
#include "vField.hpp"
#ifdef REO_TRY_DIFFUSION_TERM
#include "Diffusion.hpp"
#endif
using namespace DGM;

// local includes
#include "Reo.hpp"
#include "Adv_Diff.hpp"
#include "Adv_DiffBC.hpp"

// Trilinos includes
#ifdef REO_TEST_SACADO
#include "Sacado.hpp"
#endif

namespace Reo {

// static variables
#ifdef DGM_JSON_TO_TABLE
Adv_Diff::TBL_TO_JSON Adv_Diff::tbl_to_json;
#endif

/// if defined then perform a projection to compute diffusive flux
#define REO_PROJECT_DIFF_FLUX

#ifdef REO_TEST_SACADO
/// The analytic derivative of func(a,b,c) with respect to a and b
void func_deriv(Scalar a, Scalar b, Scalar c, Scalar &drda, Scalar &drdb) {
  drda = -(c*std::log(b+1.)/std::pow(std::sin(a),2))*std::cos(a);
  drdb = c/((b+1.)*std::sin(a));
}
#endif

/// Constructor
Adv_Diff::Adv_Diff( DGM::ArgList &args, const DGM::Comm::Ptr comm_,
                    const int p_inc) : Domain(args,comm_), Uv(comm_),
                    Uc(comm_)
{
  if (verbosity()) comm->cout() << "Adv_Diff::Adv_Diff()" << endl;

  // set the number of fields in the domain
  Nfields = 1;                         // = 1 for a scalar problem

  Ordinal p, q;
  p = params["p"];                     // polynomial order
  p += p_inc;                          // increment polynomial order if needed
  if ( !(q=params["q"]) ) q = p + 2;   // number of quadrature points
  if (verbosity())
    comm->cout() << "Adv_Diff:  p = "<< p<<", q = "<<q<<endl;

  nsd = params["nsd"];                 // number of space dimensions

  // read arguments (overrides defaults and input file)
  parse_args(args);

#ifdef DGM_JSON_TO_TABLE
  params.convert(json_domain,table_to_json_map());
#endif

  // initialize parameters
  cfield = params.get("cfield",false); // convective field flag
  cx = params.get("cx",1.0);           // x wave speed
  cy = params.get("cy",0.0);           // y wave speed
  cz = params.get("cz",0.0);           // z wave speed
  mu = params.get("vis",0.0);          // viscosity
  fv = params.get("fv",0);             // finite volume reconstruction

  // optionally output the parameter table
#if DGM_TABLE_USE_JSON
  {
    int table = 0;
    const char *tmp = getenv("DGM_OUTPUT_TABLE");
    if (tmp != NULL) table = atoi(tmp);
    if (table) comm->cout()<<params<<endl;
  }
#endif
#if defined(DGM_TABLE_USE_JSON) && defined(DGM_USE_JSON)
  {
    // Output the JSON value
    if (!json_root.isMember("Input")) json_root["Input"] = Json::Value();
    json_root["Input"]["AdvDiff"] = Json::Value();
    params.convert(json_root["Input"]["AdvDiff"]);
    Json::StyledWriter writer;
    string output = writer.write(json_root["Input"]);
    std::cout<<"DGM AdvDiff Domain parameters:\n" << output;
    ofstream fs("AdvDiff-inp.json");
    fs<<output;
  }
#endif

#ifdef DGM_JSON_TO_TABLE
  if(json_domain.isMember("Advection diffusion")) {
    if (json_domain["Advection diffusion"].isMember("Verbosity")) {
      if (json_domain["Advection diffusion"]["Verbosity"]>0) {
        Json::StyledWriter writer;
        string output = writer.write(json_root);
        std::cout<<"All DGM parameters:\n" << output;
        ofstream fs("Root-inp.json");
        fs<<output;
      }
    }
  }
#endif

  if (verbosity()) {
    if (cfield)
      comm->cout()<<"  Using a variable convective field: "<<root+".cfd"<<endl;
    else {
      comm->cout()<<"  Using a constant convective field:"<<endl;
      comm->cout()<<"    (cx, cy, cz) = ("<<cx<<","<<cy<<","<<cz<<")"<<endl;
    }
  }

  // build a Field of Elements and Sides
  if (params["imesh"]) {
    Mesh mesh(params);
    U.push_back( new Field(p, q, mesh, root, "u", Field::FULL, comm ) );
    partition = U[0]->partition;
  } else if (params["bmesh"]) {
    U.push_back( new Field(p, q, root, "u", partition, 1, Reo::NumEqntype,
                           p2i(ADV_DIFF), comm, p_inc ) );
  } else {
    U.push_back( new Field(p, q, root, "u", partition, comm, p_inc ) );
  }

  // set some additional domain parameters
  ne = U[0]->ne;
  nsd = U[0]->nsd();  params["nsd"] = nsd;

  // make auxiliary Fields using copy constructor
  if (verbosity()>1) comm->cout()<<"Making Ut Field"<<endl;
  Ut.push_back( new Field(U[0], root, U[0]->name) );
  if (verbosity()>1) comm->cout()<<"Making Uv Field"<<endl;
  Uv.push_back( new Field(U[0], root, U[0]->name) );

  // setup vField names
  U.set_name("U");
  Ut.set_name("Ut");
  Uv.set_name("Uv");
  Uc.set_name("Uc");

  // Optionally make the solution vFields contiguous storage
  const bool contiguous = params["contiguous"];
  if (contiguous) make_contiguous();

  // setup the convective field
  if (cfield) {
    comm->cout()<<"  Reading variable convective field..."<<endl;
    Uc.push_back( new Field(U[0], root, "Cx") );
    if (nsd>1) Uc.push_back( new Field(U[0], root, "Cy") );
    if (nsd>2) Uc.push_back( new Field(U[0], root, "Cz") );
    Uc.reset_storage();     // make the vField contiguous
    set_ic( Uc, ".cfd" );
    Uc.fill_sides();
    Uc.share_sides();
    Uc.fill_bc_sides();     // make sure that boundary sides are valid
    Uc.tecplot("cfield.dat","cfield");
    comm->cout()<<"  WARNING:  check the implementation for variable "
                  "convective fields"<<endl;
  }

  // allocate local workspace
  wk1.resize(max(Lmax(),Qmax()));
  wk2.resize(max(Lmax(),Qmax()));
  wk3.resize(max(Lmax(),Qmax()));

  // make sure that storage is initialized
  zero_all_fields();

  // make response object
  response = Response::factory(U, this);

  setup_BCdb();

  setup_Sourcedb();

  if (verbosity())
    comm->cout()<<"Adv_Diff::Adv_Diff() setup time integration"<<endl;

  set_TimeInt();

#ifdef REO_TEST_SACADO
  // Sacado of Lax-Friedrichs flux
  comm->cout()<<"Adv_Diff trying out Sacado Lax-Friedrichs flux"<<endl;
  {
    Scalar cl = 1.0;
    Scalar cr = 1.1;
    Scalar ul = 2.0;
    Scalar ur = 2.5;
    int nd = 4;
    Sacado::Fad::DFad<Scalar> ulf(nd,0,ul);
    Sacado::Fad::DFad<Scalar> urf(nd,1,ur);
    Sacado::Fad::DFad<Scalar> clf(nd,2,cl);
    Sacado::Fad::DFad<Scalar> crf(nd,3,cr);

    Scalar f = LF_flux(ul,ur,cl,cr);
    Sacado::Fad::DFad<Scalar> ff = LF_flux(ulf,urf,clf,crf);
    Scalar f_ad  = ff.val();
    Scalar dfdul = ff.dx(0);
    Scalar dfdur = ff.dx(1);
    Scalar dfdcl = ff.dx(2);
    Scalar dfdcr = ff.dx(3);

    std::cout << " f = " << f << " f_ad = " << f_ad << endl;
    std::cout << " dfdul = " << dfdul << endl;
    std::cout << " dfdur = " << dfdur << endl;
    std::cout << " dfdcl = " << dfdcl << endl;
    std::cout << " dfdcr = " << dfdcr << endl;
  }

  // test of Sacado
  {
    Scalar a = pi/3.0;
    Scalar b = 2.0;
    Scalar c = 3.0;
    int num_deriv = 3;
    Sacado::Fad::DFad<Scalar> afad(num_deriv, 0, a); // First (0) indep. var
    Sacado::Fad::DFad<Scalar> bfad(num_deriv, 1, b); // Second (1) indep. var
    Sacado::Fad::DFad<Scalar> cfad(num_deriv, 3, c); // Passive variable
    Sacado::Fad::DFad<Scalar> rfad;                  // Result

    // compute the function
    Scalar r = func(a, b, c);

    // compute function and derivative analytically
    Scalar drda, drdb;
    func_deriv(a, b, c, drda, drdb);

    // compute function and derivative with AD
    rfad = func(afad, bfad, cfad);

    // extract value and derivatives
    Scalar r_ad = rfad.val();     // r
    Scalar drda_ad = rfad.dx(0);  // dr/da
    Scalar drdb_ad = rfad.dx(1);  // dr/db

    // output the results
    int p = 4;
    int w = p+7;
    std::cout.setf(std::ios::scientific);
    std::cout.precision(p);
    std::cout << "    r =  " << r << " (original) == " << std::setw(w) << r_ad
              << " (AD) Error = " << std::setw(w) << r - r_ad << std::endl
              << "dr/da = " << std::setw(w) << drda << " (analytic) == "
              << std::setw(w) << drda_ad << " (AD) Error = " << std::setw(w)
              << drda - drda_ad << std::endl
              << "dr/db = " << std::setw(w) << drdb << " (analytic) == "
              << std::setw(w) << drdb_ad << " (AD) Error = " << std::setw(w)
              << drdb - drdb_ad << std::endl;
    Scalar tol = 1.0e-14;
    if (std::fabs(r - r_ad)       < tol &&
        std::fabs(drda - drda_ad) < tol &&
        std::fabs(drdb - drdb_ad) < tol) {
      std::cout << "Example passed!" << std::endl;
      //exit(DGM::SUCCESS);
    }
    else {
      std::cout <<"Something is wrong, example failed!" << std::endl;
      //exit(DGM::FAILURE);
    }
  }
#endif

#ifdef REO_TRY_DIFFUSION_TERM
  comm->cout()<<"Adv_Diff trying out a diffusion term"<<endl;
  Diffusion diffTerm(comm);
  diffTerm(U,Uv,Ut);
#endif

  if (verbosity()) comm->cout()<<"Adv_Diff::Adv_Diff() completed"<<endl;
}

void Adv_Diff::make_contiguous() {
  comm->cout()<<"Adv_Diff::make_contiguous()"<<endl;
  U.reset_storage();
  Ut.reset_storage();
  Uv.reset_storage();
}

/// Parse parameters from the argument list
void Adv_Diff::parse_args( DGM::ArgList &args ) {
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
      } else if (name == "-vis") {
        li.push_back(a);
        value = *(++a);
        li.push_back(a);
        params["vis"] = atof(value.c_str());
      } else if (name == "-fv") {
        li.push_back(a);
        value = *(++a);
        li.push_back(a);
        params["fv"] = atoi(value.c_str());
      } else if (name == "-cfield") {
        li.push_back(a);
        params["cfield"] = true;
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


/// Print usage for the Adv_Diff Domain
void Adv_Diff::showUsage() {
  comm->cout()
    << "Adv_Diff Class Options \n"
    << "----------------------------------------------------------------\n"
    << "-cx       " << '\t' << "Wave speed in x-direction\n"
    << "-cy       " << '\t' << "Wave speed in y-direction\n"
    << "-cz       " << '\t' << "Wave speed in z-direction\n"
    << "-fv       " << '\t' << "Finite volume reconstuction (0=none)\n"
    << "-cfield   " << '\t' << "File name for convective field\n"
    << "----------------------------------------------------------------\n";
}

/// Generate visualization output formats
/** \warning Does not work in parallel for all formats. */
int Adv_Diff::plot(const string &rst) {
  string fname, name(rst), caption;
  char buf[128];
  read( rst, U );
  name.erase(name.find(".rst"));  // erase extension
  sprintf(buf,"%s.dat",name.c_str()); fname = buf;
  sprintf(buf,"State variables at t =%11.4e, step = %lld",t,(long long)step);
  caption = buf;
  if (fv==2) linear_reconstruction( U, Uv, Ut );
  if (params["tecplot"])
    if (comm->Master()) U.tecplot(fname,caption);
  if (params["paraview"]) U.paraview(name,caption);
  if (params["plot3d"]) {
    sprintf(buf,"%s.xyz",name.c_str()); fname = buf;
    U.plot3d_x(fname);
    sprintf(buf,"%s.q",name.c_str()); fname = buf;
    U.plot3d_q(fname);
  }
  fieldslice.output_slices(U, step, true);
  return 0;
}

/// Zero all fields
void Adv_Diff::zero_all_fields() {
  Domain::zero_all_fields();
  Uv.zero();
}

/// Use the old way on computing CFL
//#define REO_ADV_DIFF_OLD_CFL

/// Setup time step
/** This needs to be implemented for each type of physics and should return
    a CFL-like condition.
    \todo Implement set_time_step for advection diffusion phyiscs. */
Scalar Adv_Diff::set_time_step(vField &U) {
  static bool firsttime=false;
  static Scalar cfl=0;
  if (!firsttime) return cfl;
  // Scalar c_dt = dt * sqrt( cx*cx + cy*cy + cz*cz );
  dVector c, idt;
  if (dtl.size()==0) dtl.resize(U[0]->ne);  // make space for local dt
  for (LocalSize e=0; e<U[0]->ne; e++) {
    Element *S = U[0]->el[e];
    const Ordinal qtot = S->qtot;
    // c.alias(wk1,0,qtot);
    // idt.alias(wk1,qtot,qtot);
    c.resize(qtot);
    idt.resize(qtot);
    Scalar cl = cx*cx;
    if (nsd>1) cl += cy*cy;
    if (nsd>2) cl += cz*cz;
    c = sqrt(cl);
#ifdef DGM_STORE_METRICS
#ifdef REO_ADV_DIFF_OLD_CFL
    // Original approach, but does not carry over to 3D.
    dvmul( S->geom->acoustic, c, idt );
    dvmul( S->geom->ivol, idt );
#else
    // Create characteristic length to use for CFL calc.
    for (Ordinal i=0; i<idt.size(); i++)
      idt[i] = pow(S->geom->ivol[i],one/nsd);
    dvmul( c, idt );
#endif
#else
    Element::StabMetrics cfl_metrics = S->compute_metrics();
#ifdef REO_ADV_DIFF_OLD_CFL
    // Original approach, but does not carry over to 3D.
    // comm->cout() << "Using original approach" << endl;
    dvmul( cfl_metrics[Element::ACOUSTIC], c, idt );
    dvmul( cfl_metrics[Element::IVOL], idt );
#else
    // Create characteristic length to use for CFL calc.
    // comm->cout() << "Using new approach" << endl;
    dVector &ivol = cfl_metrics[Element::IVOL];
    for (Ordinal i=0; i<idt.size(); i++) idt[i] = pow(ivol[i],one/nsd);
    // for (Ordinal i=0; i<idt.size(); ++i) comm->cout()<<i<<" "<<idt[i]<<endl;
    dvmul( c, idt );
#endif
#endif // DGM_STORE_METRICS
    multiply( two, idt, idt );
    cfl = max( cfl, dt * idt.Max() );
    dtl[e] = idt.Max() ? one/idt.Max() : 0;
  }
#ifdef DGM_PARALLEL
  Scalar local = cfl;
  comm->MaxAll( &local, &cfl, 1 );
#endif
  // cout << "CFLmax = " << cfl << endl;
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
  // cout << "cfl = " << cfl << ", dt = " << dt << endl;
  return cfl;
}

/** \pre You must call convection first
    \note that convection overwrites Uf, no need to zero it. */
void Adv_Diff::time_derivative( vField &Us, vField &Uf ) {
#ifdef HARD_BC
  enforce_hard_bc(Us);
#endif
  if (fv) {  // finite volume reconstruction
    Us.make_constant();
    linear_reconstruction( Us, Uv, Uf );
  }
  //scale(0.,Uf); convection overwrites Uf, no need to zero it
  convection( Us, Uf );
  diffusion( Us, Uv, Uf );
  add_source( Us, Uf );
  project( Uf );
  if (fv) {  // finite volume reconstruction
    Uf.make_constant();
    Us.make_constant();
  }
}

/// Compute the advection-diffusion convection term
void Adv_Diff::convection( vField &Uf, vField &Ff ) {
  if (cfield) {
    variable_convection( Uf, Ff );
  } else {
    constant_convection( Uf, Ff );
  }
}

/// Advection-diffusion convection term with variable media
/** This is the nonconservative form:
    \f[ \int_{\Omega_e} w ( c_x u_{,x} + c_y u_{,y} ) d\Omega -
    \int_{\Gamma_e} w ( \hat F_n - F_n ) d\Gamma \f]
    and this is incorrect, it should be implemented as
    \f[ \int_{\Omega_e} w ( (c_x u)_{,x} + (c_y u)_{,y} ) d\Omega -
    \int_{\Gamma_e} w ( \hat F_n - F_n ) d\Gamma \f]

    \todo Make this the correct conservative implementation.

    \warning This is not the correct implementation, it is in
    nonconservative form without the appropriate correction term.
*/
void Adv_Diff::variable_convection( vField &Uf, vField &Ff ) {
  Ordinal nsd = Uf[0]->nsd();
  Uf.fill_sides();                           // put interior soln on the sides
  Uf.share_sides();
  enforce_bc(Uf);                            // update bc side values
  convective_flux( Uf, Ff );                 // compute surface fluxes on sides
  for (LocalSize e=0; e<Uf[0]->ne; e++) {
    Element *U = Uf[0]->el[e];               // solution
    Element *F = Ff[0]->el[e];               // flux
    Element *Cx = Uc[0]->el[e];              // convective velocity
    if (nsd == 3) {
      Element *Cy = Uc[1]->el[e];            // convective velocity
      Element *Cz = Uc[2]->el[e];            // convective velocity
      dVector uy(wk1,U->qtot);
      dVector uz(wk2,U->qtot);
      U->gradient( U->u, F->u, uy, uz );
      dvmul( Cx->u, F->u );
      dvmul( Cy->u, uy );
      dvmul( Cz->u, uz );
      dvadd( uy, F->u );
      dvadd( uz, F->u );
    } else if (nsd == 2) {
      Element *Cy = Uc[1]->el[e];            // convective velocity
      dVector uy(wk1,U->qtot);
      U->gradient( U->u, F->u, uy );
      dvmul( Cx->u, F->u );
      dvmul( Cy->u, uy );
      dvadd( uy, F->u );
    } else if (nsd == 1) {
      U->gradient( U->u, F->u );
      dvmul( Cx->u, F->u );
    } else {
      comm->cerr()<< "Adv_Diff:variable_convection -- illegal value of nsd"
                  << endl;
      comm->exit(DGM::FAILURE);
    }
    U->lift( F, F->u );                      // add side fluxes to interior
  }
}

/// Computes the constant coefficient convection term
/** \f[ \int_{\Omega_e} w ( c_x u_{,x} + c_y u_{,y} ) d\Omega -
    \int_{\Gamma_e} w ( \hat F_n - F_n ) d\Gamma \f]
    This implementation is correct since the convective velocities are
    spatially constant. */
void Adv_Diff::constant_convection( vField &Uf, vField &Ff ) {
  const Ordinal nsd = Uf[0]->nsd();
  Uf.fill_sides();                           // put interior soln on the sides
  Uf.share_sides();
  enforce_bc(Uf);                            // update bc side values
  convective_flux( Uf, Ff );                 // compute surface fluxes on sides
  for (LocalSize e=0; e<Uf[0]->ne; e++) {
    const Element *U = Uf[0]->el[e];         // solution
    Element       *F = Ff[0]->el[e];         // flux
    if (nsd == 3) {
      dVector uy(wk1,U->qtot);
      dVector uz(wk2,U->qtot);
      U->gradient( U->u, F->u, uy, uz );
      scale( cx, F->u );
      daxpy( cy, uy, F->u );
      daxpy( cz, uz, F->u );
    } else if (nsd == 2) {
      dVector uy(wk1,U->qtot);
      U->gradient( U->u, F->u, uy );
      scale( cx, F->u );
      daxpy( cy, uy, F->u );
    } else if (nsd == 1) {
      U->gradient( U->u, F->u );
      scale( cx, F->u );
    } else {
      comm->cerr()<< "Adv_Diff:constant_convection -- illegal value of nsd"
                   << endl;
      comm->exit(DGM::FAILURE);
    }
    U->lift( F, F->u );                      // add side fluxes to interior
  }
}

/// Compute the Advective flux
/** For descriptions of the numerical fluxes See: E.F. Toro, "Riemann
    Solvers and Numerical Methods for Fluid Dynamics," 2nd Edition,
    Springer, 1999. */
void Adv_Diff::convective_flux(vField &Us, vField &Uf) {
  Side *fl, *fr, *sl, *sr;
#ifdef REO_USE_GETSIDEMAPS
  iVector mapl, mapr;
#endif
  for (LocalSize e=0; e<Us[0]->ne; e++) {
    Element *U = Us[0]->el[e];
    Element *F = Uf[0]->el[e];
    for (SideLoop S(U); !S.end(); ++S) {
      if (S.master_side()) {
        // localize the state and flux side pointers
        sl = S.side(U);
        sr = S.link(U);
        fl = S.side(F);
        fr = S.link(F);
        const Ordinal qtot = S.qtot();
#ifdef REO_USE_GETSIDEMAPS
        get_side_maps(sl,sr,mapl,mapr);
#endif
        if (!cfield) {                            // Constant convection
          for (Ordinal q=0; q<qtot; q++) {
#ifdef REO_USE_GETSIDEMAPS
            const Ordinal ql = mapl[q];
            const Ordinal qr = mapr[q];
#else
            const Ordinal ql = U->sideMap(sl,q);
            const Ordinal qr = U->sideMap(sr,q);
#endif
            const Scalar nx =          S.nx(ql);
            const Scalar ny = (nsd>1 ? S.ny(ql) : 0.0 );
            const Scalar nz = (nsd>2 ? S.nz(ql) : 0.0 );
            const Scalar cn = cx*nx + cy*ny + cz*nz;
            // put interior flux on the state field sides
            sl->u[ql] *=  cn;
            sr->u[qr] *= -cn;
            // put numerical flux on the flux field sides
            if ( cn < 0 ) {
              fl->u[ql] = -sr->u[qr];
              fr->u[qr] =  sr->u[qr];
            } else {
              fl->u[ql] =  sl->u[ql];
              fr->u[qr] = -sl->u[ql];
            }
          }
        } else {                                  // Variable convection
          for (Ordinal q=0; q<qtot; q++) {
#ifdef REO_USE_GETSIDEMAPS
            const Ordinal ql = mapl[q];
            const Ordinal qr = mapr[q];
#else
            const Ordinal ql = U->sideMap(sl,q);
            const Ordinal qr = U->sideMap(sr,q);
#endif
            const Scalar nx =          S.nx(ql) ;
            const Scalar ny = (nsd>1 ? S.ny(ql) : 0.0 );
            const Scalar nz = (nsd>2 ? S.nz(ql) : 0.0 );

            const Scalar ul  = sl->u[ql];
            const Scalar cxl =         S.side(Uc[0]->el[e])->u[ql];
            const Scalar cyl = nsd>1 ? S.side(Uc[1]->el[e])->u[ql] : 0.0 ;
            const Scalar czl = nsd>2 ? S.side(Uc[2]->el[e])->u[ql] : 0.0 ;
            const Scalar cnl = cxl*nx + cyl*ny + czl*nz;
            const Scalar fpl = cnl*ul;

            const Scalar ur  = sr->u[qr];
            const Scalar cxr =         S.link(Uc[0]->el[e])->u[qr];
            const Scalar cyr = nsd>1 ? S.link(Uc[1]->el[e])->u[qr] : 0.0 ;
            const Scalar czr = nsd>2 ? S.link(Uc[2]->el[e])->u[qr] : 0.0 ;
            const Scalar cnr = cxr*nx + cyr*ny + czr*nz;
            const Scalar fmr = cnr*ur;

            // Lax-Friedrichs flux
            const Scalar lmax = max(fabs(cnl),fabs(cnr));
            const Scalar fh = pt5 * ( fpl + fmr + lmax * (ul - ur) );

            // put numerical flux on the flux field sides
            fl->u[ql] =  fh;
            fr->u[qr] = -fh;

            // put interior flux on the state field sides
            sl->u[ql] =  fpl;
            sr->u[qr] = -fmr;
          }
        }
      }
    }
  }
}

/// Does a linear reconstruction for use in finite volume methods
/** The purpose of this method is to simulate a second-order finite-volume
    method by doing a linear reconstruction. */
void Adv_Diff::linear_reconstruction( vField &Uf, vField &Ff, vField &Rf ) {
  Ordinal nsd = Uf[0]->nsd();
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
      comm->cerr()<< "Adv_Diff:reconstruction -- illegal value of nsd" << endl;
      comm->exit(DGM::FAILURE);
    }
  }
}

/// Compute (stabilized) Bassi and Rebay diffusive term
void Adv_Diff::diffusion( vField &Uf, vField &Ff, vField &Rf ) {
  if (mu == 0) return;
  Ordinal nsd = Uf[0]->nsd();
  Uf.fill_sides();                   // put solution on the sides
  Uf.share_sides();
  enforce_bc(Uf);                    // update bc side values
  average_flux( Uf, Ff, '+' );       // F's sides are average of the solution
  if (stab!=0 || bstab!=0.0) {
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
      U->gradient(ux, F->u, 'x');             // ux = uxx
    } else {
      comm->cerr()<< "Adv_Diff:diffusion -- illegal value of nsd" << endl;
      comm->exit(DGM::FAILURE);
    }
  }
  Uf.share_sides();
  enforce_flux_bc(Uf);                        // put flux BC's on bc sides
  if (stab!=0.0) {
    interior_penalty_flux( Rf, Uf, Ff, stab*Uf.get_max_sigma() );
  } else {
    average_flux( Uf, Ff, '-' );
  }
  if (bstab!=0.0) {
    enforce_boundary_penalty( Rf, Ff, bstab*Uf.get_max_sigma() );
  }
  for (LocalSize e=0; e<Uf[0]->ne; e++) {
    const Element *U = Uf[0]->el[e];
    Element *F = Ff[0]->el[e];
    U->lift( F, F->u );                       // add side fluxes to interior
  }
  scale( -1.0, Ff);                           // Currently on LHS
  add( Ff, Rf );                              // add in viscous contribution
}

/// Compute the interior penalty flux on the sides
void Adv_Diff::interior_penalty_flux(const vField &Up, const vField &Us,
                                     vField &Uf, const Scalar sigma) {
  comm->cout()<<"Adv_Diff::interior_penalty_flux(...)"<<endl;
  //const Ordinal Qmax(Us[0]->Qmax);
  iVector mapl, mapr;
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
          for (Ordinal q=0; q<qtot; q++) {
            const Ordinal ql = F->sideMap(fl,q);
            const Ordinal qr = F->sideMap(fr,q);
            fl->u[ql] = pt5 * (sl->u[ql] - sr->u[qr]) +
                        sigma*(pr->u[qr] - pl->u[ql]);
            fr->u[qr] = -fl->u[ql];
          }
        }
      }
    }
  }
}

/// This compute the boundary penalty term
/** The boundary penalty is similar to the interior penalty term and helps
    to stabilize the DG method for diffusion.  This implementation is just
    a demonstration and is not for general use.

    \warning This does not work with general side orientations
*/
void Adv_Diff::enforce_boundary_penalty(const vField &S, vField &F,
                                        const Scalar sigma) {
  static bool first=true;
  if (first) {
    comm->cout() << "WARNING:  Adv_Diff::enforce_boundary_penalty() "
      "is not correct in general and must be used with caution." << endl;
    first=false;
  }
  for (LocalSize n=0; n<S[0]->nbc; ++n) {
    for(LocalSize i=0; i<S[0]->bc[n]->S->qtot(); ++i) {
      F[0]->bc[n]->S->u[i] += sigma*( S[0]->bc[n]->S->link->u[i] -
                                      S[0]->bc[n]->S->u[i] );
      F[0]->bc[n]->S->link->u[i] = -F[0]->bc[n]->S->u[i];
    }
  }
}

/// Enforces Dirichlet conditions directly
/** This method is used to show what happens when you implement boundary
    conditions directly (hard) as opposed to the normal weak implementations
    used by default in DGM.  This is not a general implementation and should
    be used with caution.

    \warning Only works for line elements and with no reversed sides!
*/
void Adv_Diff::enforce_hard_bc(vField &U) {
  // comm->cout() << "Adv_Diff::enforce_hard_bc(vField &U)" << endl;
  vector<Boundary*> &bc = U[0]->bc;
  vector<Element*> &el = U[0]->el;
  for (LocalSize n=0; n<U[0]->nbc; n++) {
    if (bc[n]->type=="D") {
      if (bc[n]->sid==0)
        el[bc[n]->eid]->u[0] = 0.0;
      else
        el[bc[n]->eid]->u[el[bc[n]->eid]->qa-1] = 0.0;
    } else {
      comm->cerr()<< "Hard BC not implemented" << endl;
      comm->exit(DGM::FAILURE);
    }
  }
  project( U );
}

//===========================================================================
//                        BC database management
//===========================================================================

// Load up the available boundary condition types
void Adv_Diff::setup_BCdb( ) {
  dVector values(1);
  values = 0.0;
  // set default BC types
  BC_db["S"].reset( new StateBC("S", values) );
  BC_db["D"].reset( new DirichletBC("D", 0.0) );
  BC_db["F"].reset( new NeumannBC("F", 0.0, cx, cy, cz) );
  BC_db["N"].reset( new NeumannBC("N", 0.0, cx, cy, cz) );
  BC_db["O"].reset( new OutflowBC("O") );
  BC_db["R"].reset( new RobinBC("R", 0.0, 1.0, cx, cy, cz) );

  // read new BC types from file
  string fname = root+".bct";
  ifstream in(fname.c_str());
  if (in) Adv_Diff::read_BCdb( in );   // database of active BC types
}

void Adv_Diff::read_BCdb( ifstream &in ) {
  // comm->cout() << "Adv_Diff::read_BCdb( ifstream &in )" << endl;
  string tag;
  BC *pbc;
  while ( (pbc = Adv_Diff::make_BC(in,tag)) ) {
    if ( BC_db.find(tag) != BC_db.end() )
      comm->cout() << "Adv_Diff::read_BCdb() Overriding BC type \""
             << tag << "\"." << endl;
    BC_db[tag].reset( pbc );
  }
}

BC* Adv_Diff::make_BC( ifstream &in, string &tag ) {
  // comm->cout() << "Adv_Diff::make_BC(ifstream &in, string &tag)" << endl;
  string code;
  if (!(in >> code)) return NULL;
  code = lowerCase(code);
  if (code == "dirichlet") {
    if (!(in >> tag)) error("Adv_Diff::make_BC() Cannot read Dirichlet tag");
    return new DirichletBC(tag,in);
  } else if (code == "unsteadydirichlet") {
    if (!(in >> tag))
      error("Adv_Diff::make_BC() Cannot read UnsteadyDirichletBC tag");
    return new UnsteadyDirichletBC(tag,in);
  } else if (code == "function") {
    if (!(in >> tag))
      error("Adv_Diff::make_BC() Cannot read FuncBC tag");
    return new FuncBC(tag,in,1);
  } else if (code == "robin") {
    if (!(in >> tag)) error("Adv_Diff::make_BC()  Cannot read Neumann tag");
    return new RobinBC(tag,in,cx,cy,cz);
  } else if (code == "neumann") {
    if (!(in >> tag)) error("Adv_Diff::make_BC()  Cannot read Neumann tag");
    return new NeumannBC(tag,in,cx,cy,cz);
  } else if (code == "dirichletcontrol") {
    if (!(in >> tag))
      error("Adv_Diff::make_BC() Cannot read DirichletControl tag");
    return new DirichletControlBC(tag,in);
  } else if (code == "neumanncontrol") {
    if (!(in >> tag))
      error("Adv_Diff::make_BC() Cannot read NeumannControl tag");
    return new NeumannControlBC(tag,in,cx,cy,cz);
  } else if (code == "robincontrol") {
    if (!(in >> tag))
      error("Adv_Diff::make_BC() Cannot read RobinControl tag");
    return new RobinControlBC(tag,in,comm,cx,cy,cz);
 } else if (code == "steadydirichletcontrol") {
    if (!(in >> tag))
      error("Adv_Diff::make_BC() Cannot read SteadyDirichletControl tag");
    return new SteadyDirichletControlBC(tag,in);
  } else if (code == "steadyneumanncontrol") {
    if (!(in >> tag))
      error("Adv_Diff::make_BC() Cannot read SteadyNeumannControl tag");
    return new SteadyNeumannControlBC(tag,in,cx,cy,cz);
  } else if (code == "steadyrobincontrol") {
    if (!(in >> tag))
      error("Adv_Diff::make_BC() Cannot read SteadyRobinControl tag");
    return new SteadyRobinControlBC(tag,in,comm,cx,cy,cz);
  } else if (code == "state") {
    if (!(in>>tag)) error("Adv_Diff::make_BC() Cannot read State tag");
    return new StateBC(tag,in,1);
  } else if (code == "outflow") {
    if (!(in>>tag)) error("Adv_Diff::make_BC() Cannot read Outflow tag");
    return new OutflowBC(tag,in);
  } else {
    error("Adv_Diff::make_BC() Illegal BC type:  "+code);
  }
  return 0;
}

//===========================================================================
//                        Source database management
//===========================================================================

/// Construct source terms
Source::Ptr Adv_Diff::make_Source( ifstream &in, string &tag ) {
  // comm->cout() << "Adv_Diff::make_Source" << endl;
  string code;
  Source::Ptr p;
  if (!(in >> code)) return p;
  while (code[0]=='#') {  // eat comment lines
    string buffer;
    getline(in,buffer);
    if (!(in >> code)) return p;
  }
  if (lowerCase(code) == "constant") {
    if (!(in >> tag)) error("Adv_Diff::Cannot read ConstSource tag",1);;
    p.reset( new ConstSource(tag,in,1) );
  } else if (lowerCase(code) == "file") {
    if (!(in >> tag)) error("Adv_Diff::Cannot read FileSource tag",1);;
    p.reset( new FileSource(tag,in,U) );
  } else if (lowerCase(code) == "function") {
    if (!(in >> tag)) error("Adv_Diff::Cannot read FuncSource tag",1);;
    p.reset( new FuncSource(tag,in,1) );
  } else if (lowerCase(code) == "distributedcontrol") {
    if (!(in >> tag)) error("Adv_Diff::Cannot read DistributedControl tag",1);
    p.reset( new DistributedControl(tag, in, U) );
  } else if (lowerCase(code) == "steadydistributedcontrol") {
    if (!(in >> tag))
      error("Adv_Diff::Cannot read SteadyDistributedControl tag",1);
    p.reset( new SteadyDistributedControl(tag, in, U) );
  } else if (lowerCase(code) == "transientgaussian") {
    if (!(in >> tag)) error("Adv_Diff::Cannot read TransientGaussian tag",1);
    p.reset( new TransientGaussian(tag, in) );
  } else if (lowerCase(code) == "diracricker") {
    if (!(in >> tag)) error("Adv_Diff::Cannot read DiracRicker tag",1);
    p.reset( new DiracRicker(tag, in) );
  } else {
    error("Adv_Diff::make_Source() Illegal Source type",1);
  }
  return p;
}

/// Add source terms
void Adv_Diff::add_source(const vField &Us, vField &Ur) {
  // comm->cout() << "Adv_Diff::add_source(vField &)" << endl;
  for (Source::db_citr i=Source_db.begin(); i!= Source_db.end(); ++i) {
    // comm->cout() << "Adding source: " << i->first << endl;
    i->second->apply( t, Us, Ur );
  }
}

//===========================================================================
//                        Initial Conditions
//===========================================================================

/// Set the initial condition
void Adv_Diff::set_ic(vField &F, string ext) {
  // comm->cout() << "Adv_Diff::set_ic(vField &F, string)" << endl;
  t = 0.0; step = 0;
  string fname = root+ext;
  ifstream in(fname.c_str());
  if (!in)
    comm->error("Adv_Diff::set_ic() Could not open initial condition "+fname);
  string buffer, code;
  getline(in,buffer);
  if (!(in>>code)) comm->error("Adv_Diff::set_ic() Cannot read IC code",1);
  getline(in,buffer);
  // cout << "IC code = " << code << endl;
  if (lowerCase(code) == "given") {
    F.fill(in);
  } else if (lowerCase(code) == "restart") {
    string rstfile;
    if (!(in>>rstfile))
      comm->error("Adv_Diff::set_ic() Cannot read restart file name from "
                  +fname);
    read(rstfile,F);
  } else {
    comm->error("Adv_Diff::set_ic() Unsupported IC type");
  }
#ifdef DGM_NO_PROJECT_IC
  comm->cout() << "WARNING:  No projection of Initial condition" << endl;
  for (LocalSize i=0; i<F.size(); i++)
    for (LocalSize e=0; e<ne; e++)
      F[i]->el[e]->state = Element::Physical;
#else
  // project field to the polynomial space just to make sure
  // comm->cout()<<"Projecting initial condition to polynomial space"<<endl;
  project( F );
  if (fv!=0) F.make_constant();
#endif
#ifdef DGM_TEST_LOW_MODES
  comm->cout()<<"Applying low modes to initial condition"<<endl;
#ifdef DGM_TEST_OLD_LOW_MODES
  Ordinal pmax(0);
  comm->cout()<<"Enter pmax: "; cin >> pmax;
  F.low_modes(pmax);
#else
  Ordinal pinc(0), pmin(0);
  comm->cout()<<"Enter pinc, pmin: "; cin >> pinc >> pmin;
  F.low_modes(pinc,pmin);
#endif
#endif
}

} // namespace Reo
