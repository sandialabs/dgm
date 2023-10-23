/*============================================================================
  Module:     Darcy Solver using LDG method

  Contact:    S. Scott Collis
              sscoll@sandia.gov

  Copyright:  (c)2010 Sandia National Laboratories
=============================================================================*/

/** \file Darcy.cpp
    \brief Basic Darcy equation module implementation
    \author Axel Gerstenberger
    \author Guglielmo Scovazzi
    \author S. Scott Collis
*/

// Reo includes
#include "Reo.hpp"
#include "Darcy.hpp"
#include "DarcyBC.hpp"

// DGM includes
#include "Operator.hpp"
#include "Assembler.hpp"

// Trilinos includes
#ifdef DGM_USE_EPETRA
#ifdef DGM_PARALLEL
#include "Epetra_MpiComm.h"
#else
#include "Epetra_SerialComm.h"
#endif
#include "Epetra_Map.h"
#include "Epetra_BlockMap.h"
#include "Epetra_Vector.h"
#include "Epetra_CrsGraph.h"
#include "Epetra_CrsMatrix.h"
#include "Epetra_LinearProblem.h"
#include "AztecOO.h"
#include "EpetraExt_OperatorOut.h"
#include "EpetraExt_RowMatrixOut.h"
#include "EpetraExt_VectorOut.h"
#include "EpetraExt_MultiVectorOut.h"
#include "EpetraExt_CrsMatrixIn.h"
#endif

// system includes
#include <sstream>
#include <boost/array.hpp>
#include <set>
#include <string>

namespace DGM {
namespace Matrix {
#ifdef DGM_USE_EPETRA
/// Field number for pressure
template<> struct FieldNum<pres> {static const std::size_t pos = 0;};
#endif
}
}

namespace Reo {

using namespace DGM;

/// Constructor
Darcy::Darcy( DGM::ArgList &args, const DGM::Comm::Ptr comm_ ) :
  Domain(args, comm_), restart(false), do_solve(true), Uv(comm_),
  Un(comm_), Uo(comm_), Kabs(comm_), Lt(comm_), Gf(comm_), Sf(comm_),
  Sffile(comm_) {

  comm->cout()<<"Building Darcy..."<<endl;

  // initialize output parameters
  input("plot_init",    false);  // Plot initial fields
  input("darcy_pin",    false);  // pin constant mode or not
  input("ghosting",     0);      // test the ghosting framework
  input("ghostvis",     false);  // true to generated ghost visualization

  // initialize solver parameters
  input("matrix_solve", false);  // solve with matrix, otherwise, matrix free
  input("solver",       0);      // default is matrix-free GMRES
  input("matrix_out",   false);  // dump (and build) matrices
  input("use_ldg",      true);   // default is ldg with residual formulation
  input("use_new_bc",   false);  // default is old BC with matrix-free formul.
  input("projic",       true);   // project IC to poly space
  input("projavg",      true);   // project out the average
  input("iterations",   1000);   // max number of GMRES iterations
  input("tolerance",    1e-12);  // tolerance for the GMERS solver
  input("dim_krylov",   500);    // dimension of Krylov space for GMRES solver

  // initialize physics parameters
  input("viscosity",    1.0);    // average flow viscosity
  input("density",      1.0);    // average flow density
  input("g_x",          0.0);    // x-component of gravity
  input("g_y",          0.0);    // y-component of gravity
  input("g_z",          0.0);    // z-component of gravity
  input("u_x",          0.0);    // x-component of miscible velocity
  input("u_y",          0.0);    // y-component of miscible velocity
  input("u_z",          0.0);    // z-component of miscible velocity

  myparams["paraview"] = (bool) params["paraview"];
  myparams["plot3d"]   = (bool) params["plot3d"];
  myparams["tecplot"]  = (bool) params["tecplot"];
  // read arguments (overrides defaults and input file)
  parse_args( args );

  // test serialization
#ifdef DGM_USE_EPETRA
  test_serialization();
#endif

  // initialize parameters
  const int p = params.get("p");         // polynomial order
  comm->cout() << "  Darcy: p = " << p << endl;
  int q;
  if ( !(q=params.get("q")) ) q = p + 2; // number of quadrature points
  comm->cout() << "  Darcy: q = " << q << endl;
  nsd = params.get("nsd");               // number of space dimensions

  vector<string> field_names;            // Field names
  field_names.push_back("p");

  // store gravity components
  gravity[0] = myparams.get("g_x");
  gravity[1] = myparams.get("g_y");
  gravity[2] = myparams.get("g_z");
  comm->cout() << "  gravity: [" << gravity[0] << " "
                                 << gravity[1] << " "
                                 << gravity[2] << "]" << endl;

  // store miscible velocity components
  u_misc[0] = myparams.get("u_x");
  u_misc[1] = myparams.get("u_y");
  u_misc[2] = myparams.get("u_z");
  comm->cout() << "  u_misc: [" << u_misc[0] << " "
                                << u_misc[1] << " "
                                << u_misc[2] << "]" << endl;

  // build a Field of Elements and Sides
  if (params.get("imesh")) {
    Mesh mesh(params);
    U.push_back( new Field(p, q, mesh, root, field_names[0],
                           Field::FULL, comm ) );
    partition = U[0]->partition;
  } else if (params.get("bmesh")) {
    U.push_back( new Field(p, q, root, field_names[0], partition, 1,
                           Reo::NumEqntype, p2i(DARCY), comm ) );
  } else {
    U.push_back( new Field(p, q, root, field_names[0], partition, comm ) );
  }

  // set some additional domain parameters
  ne = U[0]->ne;
  nsd = U[0]->nsd();

#ifdef REO_USE_GETSIDEMAPS
  setup_side_maps();
#endif

  Nfields = NfieldsT;
  t = zero;
  step = 0;

  // build the rest of the vector field
  U.set_name("U");
  for (LocalSize i=1; i<NfieldsT; i++)
    U.push_back( new Field( U[0], root, field_names[i] ) );
  U.reset_storage();

  // make auxiliary Fields using copy constructor
  Ut.set_name("Ut");
  for (LocalSize i=0; i<NfieldsT; i++) {
    Ut.push_back( new Field( U[i], root, field_names[i] ) );
  }
  Ut.reset_storage();

  // make auxiliary Fields using copy constructor
  Uv.set_name("Uv");
  for (LocalSize i=0; i<NfieldsT; i++) {
    Uv.push_back( new Field( U[i], root, field_names[i] ) );
  }
  Uv.reset_storage();

  // solution at the old timestep (use to restart iterative solvers)
  Un.set_name("Un");
  for (LocalSize i=0; i<NfieldsT; i++) {
    Un.push_back( new Field( U[i], root, field_names[i] ) );
  }
  Un.reset_storage();
  if (!restart) set_ic(Un); // old timestep value is set to initial condition

  const bool matrix_solve = myparams.get("matrix_solve");
  if (myparams.get("darcy_pin") and matrix_solve == false) {
    Uo.set_name("Uo");
    for (vField::size_type i=0; i<Nfields; i++) {
      Uo.push_back( new Field( U[i], root, field_names[i] ) );
    }
  }

  // build the rock absolute permeability vField
  Kabs.set_name("Kabs");
  Kabs.push_back( new Field(U[0], root, "Kabs_xx") );
  if (nsd>1) Kabs.push_back( new Field(U[0], root, "Kabs_yy") );
  if (nsd>2) Kabs.push_back( new Field(U[0], root, "Kabs_zz") );

  // read Kabs from input file ".kabs"
  set_medium( Kabs, ".kabs" );
#ifndef DGM_PARALLEL
  if (myparams.get("plot_init")) {
    Kabs.tecplot(root+".Kabs.dat","Rock permeability");
  }
#endif

  // Build the total mobility vField
  Lt.set_name("Lt");
  Lt.push_back( new Field(U[0], root, "Lt") );
  Lt.reset_storage();

  // Setup the Lt vField as total mobility
  const Scalar visc = myparams.get("viscosity");
  Lt.fill(one/visc);
  for (LocalSize e=0; e<Lt[0]->ne; e++) {
    dvmul(Kabs[0]->el[e]->u, Lt[0]->el[e]->u);
    Lt[0]->el[e]->state = Element::Physical;
  }

#if 0
  // debugging the random kabs field
  comm->cout() << "Visualize parallel layout" << endl;
  const int mypid = comm->MyPID();
  ostringstream fname;
  fname << "Lt" << "." << mypid << ".pos";
  ofstream s(fname.str().c_str());
  for (int i=0; i<Lt.size(); i++) {
    Lt[i]->visualize_scalar_field_as_point_cloud(1.0, s);
  }
  s.close();
#endif

  // Final adjustments to the Kabs vField in the matrix application, we don't
  // need Kabs anymore...
  if (matrix_solve == true) {
    // Kabs.clear();
  } else {
    Kabs.fill_sides();
    Kabs.share_sides();
    Kabs.fill_bc_sides();  // make sure that boundary sides are valid
  }

  // Final adjustments to the Lt vField
  Lt.fill_sides();
  Lt.share_sides();
  Lt.fill_bc_sides();      // make sure that boundary sides are valid
#ifndef DGM_PARALLEL
  if (myparams.get("plot_init")) {
    Lt.tecplot(root+".Lt_ini.dat","Total mobility");
  }
#endif

  // Build the premultiplicative gravity factor vField
  Gf.set_name("Gf");
  Gf.push_back( new Field(U[0], root, "Gf") );
  Gf.reset_storage();

  const Scalar dens = myparams.get("density");
  Gf.fill(dens);

  // Final adjustments to the Gf vField
  Gf.fill_sides();
  Gf.share_sides();
  Gf.fill_bc_sides();     // make sure that boundary sides are valid
#ifndef DGM_PARALLEL
  if (myparams.get("plot_init")) {
    Gf.tecplot(root+".Gf_ini.dat","Gravity prefactor");
  }
#endif

  // if run in coupled mode, build a source vector filled by Advect_Diff
  Sf.set_name("Sf");
  Sf.push_back( new Field(U[0], root, "Sf") );
  Sf.reset_storage();
  Sf.zero();

  Sffile.set_name("Sffile");
  Sffile.push_back( new Field(U[0], root, "Sffile") );
  Sffile.reset_storage();

  // allocate workspace
  wk1.resize(5*max(Lmax(),Qmax()));
  wk2.resize(5*max(Lmax(),Qmax()));
  wk3.resize(5*max(Lmax(),Qmax()));

  // to read an analytic solution and print it to rst for dgm_diff
  set_ic(U);
  Nt = params.get("Nt");
  if (Nt == 0) {
    write(root+".0.rst", U);
    do_solve = false;
  }

  // make analysis object
  response = Response::factory(U, this);

  setup_BCdb();

  setup_Sourcedb();

  set_TimeInt();

  verifyBCs(U);

  if (myparams.get("matrix_solve")) {
    if (myparams.get("use_ldg")) {
      comm->error("use 'use_ldg = 0' in your Darcy input file");
    }
  }

  // debug output to make sure we read the correct input from file
  if (not myparams.get("matrix_solve")) {
    if (myparams.get("use_ldg")) // turn on or off LDG for testing
      comm->cout() << "Darcy: Enabled LDG" << endl;
    else
      comm->cout() << "Darcy: Disabled LDG" << endl;

    if (myparams.get("use_new_bc"))
      comm->cout() << "Darcy: Using new BCs" << endl;
    else
      comm->cout() << "Darcy: Using old BCs" << endl;
  }
}

/// Parse parameters from the argument list
void Darcy::parse_args( DGM::ArgList &args ) {
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
      } else if (name == "-ghostvis") {
        li.push_back(a);
        params["ghostvis"] = 1;
        myparams["paraview"] = true;
      } else if (name == "-ghosting") {
        li.push_back(a);
        myparams["ghosting"] = 1;
      } else if (name == "-solver") {
        li.push_back(a);
        value = *(++a);
        li.push_back(a);
        params["solver"] = atoi(value.c_str());
      } else if (name == "-projic") {
        li.push_back(a);
        value = *(++a);
        li.push_back(a);
        const int ivalue = atoi(value.c_str());
        params["projic"] = (bool)ivalue;
      } else if (name == "-projavg") {
        li.push_back(a);
        value = *(++a);
        li.push_back(a);
        const int ivalue = atoi(value.c_str());
        params["projavg"] = (bool)ivalue;
      } else if (name == "-g_x") {
        li.push_back(a);
        value = *(++a);
        li.push_back(a);
        params["g_x"] = atof(value.c_str());
      } else if (name == "-g_y") {
        li.push_back(a);
        value = *(++a);
        li.push_back(a);
        params["g_y"] = atof(value.c_str());
      } else if (name == "-g_z") {
        li.push_back(a);
        value = *(++a);
        li.push_back(a);
        params["g_z"] = atof(value.c_str());
      } else if (name == "-viscosity") {
        li.push_back(a);
        value = *(++a);
        li.push_back(a);
        params["viscosity"] = atof(value.c_str());
      } else if (name == "-density") {
        li.push_back(a);
        value = *(++a);
        li.push_back(a);
        params["density"] = atof(value.c_str());
      } else if (name == "-tolerance") {
        li.push_back(a);
        value = *(++a);
        li.push_back(a);
        params["tolerance"] = atof(value.c_str());
      } else if (name == "-iterations") {
        li.push_back(a);
        value = *(++a);
        li.push_back(a);
        params["iterations"] = atoi(value.c_str());
      } else if (name == "-dim_krylov") {
        li.push_back(a);
        value = *(++a);
        li.push_back(a);
      } else if (name == "-help") {
        params["showUsage"] = 1;
        showUsage();
      }
    }
  }
  // remove tagged arguments
  for (list< DGM::ArgList::iterator >::iterator a=li.begin();
       a!=li.end(); a++) args.erase(*a);
}

/// Show usage for solver
void Darcy::showUsage() {
  comm->cout()
    << "Darcy Class Options \n"
    << "----------------------------------------------------------------\n"
    << "-nox       " << '\t' << "No grid file         \n"
    << "-noq       " << '\t' << "No solution file     \n"
    << "-aux       " << '\t' << "Auxiliary Tecplot file\n"
    << "-solver    " << '\t' << "Specify the solver type\n"
    << "-projic    " << '\t' << "Project the initial condition\n"
    << "-projavg   " << '\t' << "Project out the average\n"
    << "-g_x       " << '\t' << "Gravity: x-component\n"
    << "-g_y       " << '\t' << "Gravity: y-component\n"
    << "-g_z       " << '\t' << "Gravity: z-component\n"
    << "-viscosity " << '\t' << "Fluid viscosity\n"
    << "-density   " << '\t' << "Fluid density\n"
    << "-iterations" << '\t' << "GM-Res maximum number of iterations\n"
    << "-tolerance " << '\t' << "GM-Res relative residual tolerance\n"
    << "-dim_krylov" << '\t' << "GM-Res dimension of krylov space\n"
    << "----------------------------------------------------------------\n";
}

//===========================================================================
//                             Solve Methods
//===========================================================================

/// Evaluate the action of the operator on a solution vector
void Darcy::action( vField &Us, vField &Uf ) {
  residual(Us, Uf);
  axpy(one, Ut, Uf, Uf);
  if (myparams.get("darcy_pin")) {
    // pin a constant mode to zero
    Us.forward_transform();
    axpy( Us[0]->el[0]->uh[0], Uo, Uf, Uf);    // does that work in parallel?
    Uf[0]->el[0]->uh[0] = Us[0]->el[0]->uh[0]; // does that work in parallel?
    Us.backward_transform();
  }
}

/// Computes the complete DG residual
void Darcy::residual( vField &Us, vField &Uf ) {
  // comm->cout() << "Darcy::residual()" << endl;

  const bool use_ldg = myparams.get("use_ldg");
  const bool use_new_bc = myparams.get("use_new_bc");

  Uf.zero(); // may be removed, if Uf is 100% (check!)
             // overwritten within residual(...)
  Us.fill_sides();
  Us.share_sides();
  if (use_new_bc) {
    for (BC::db_citr i=BC_db.begin(); i!= BC_db.end(); ++i)
      i->second->matrix_apply( t, Us );
  } else {
    enforce_bc(Us);  // Dirichlet BCs
  }
  // make a copy of Us into Uv
  if (stab!=0) {
    copy_sides(Us,Uv);
    Uv.share_sides();
    if (use_new_bc) {
      for (BC::db_citr i=BC_db.begin(); i!= BC_db.end(); ++i)
        i->second->matrix_apply( t, Uv );
    } else {
      enforce_bc(Uv);  // Dirichlet BCs
    }
  }

  if (use_new_bc) {
    solution_flux_new_bc( Lt, Us, Uf );
  } else {
    solution_flux( Lt, Us, Uf );
  }

  for (vField::size_type i=0; i<Us.size(); ++i) {
    for (LocalSize e=0; e<Us[i]->ne; ++e) {
      Element *const U = Us[i]->el[e];
      Element *const F = Uf[i]->el[e];
      const Element *const L_t=   Lt[0]->el[e];
            Element *const GF =   Gf[0]->el[e];
      const LocalSize qtot = U->qtot;

      dVector wkv(qtot);
      if (nsd==1) { // 1D
         dVector sigma_x(wk1,qtot);
         dVector sigma_dummy(wk2,qtot);
         U->gradient(U->u, sigma_x);
         dvmul(L_t->u,sigma_x); // sigma_x = Lt*u_{,x}
         dvmul(L_t->u,GF->u,wkv);
         scale(-gravity[0],wkv);
         /// \note the sign here needs to be reversed
         dvadd(wkv,sigma_x); // sigma_x = Lt*(u_{,x}-avg_rho*g_x)
         if ( !use_ldg ) {   // IP: gradient goes into the unused sides of GF
           GF->fill_sides( sigma_x, sigma_dummy );
         }
         U->lift( F, sigma_x, 'x' );
         U->project(sigma_x);
         // don't use the apparently obvious U->fill_sides( ux ); !
         // the line element has two fill_sides meanings, so the second
         // argument just triggers the alternative implementation
         U->fill_sides( sigma_x, sigma_dummy );    // normal flux on sides
         U->gradient(sigma_x, sigma_x, 'x');       // sigma_x = (sigma_x)_{,x}
         dvadd( sigma_x, F->u );                   // F->u = (sigma_x)_{,x}
      } else if (nsd==2) { // 2D
         dVector sigma_x(wk1,qtot);
         dVector sigma_y(wk2,qtot);
         U->gradient(U->u, sigma_x, sigma_y);
         dvmul(L_t->u,sigma_x); // sigma_x = Lt*u_{,x}
         dvmul(L_t->u,sigma_y); // sigma_y = Lt*u_{,y}
         dvmul(L_t->u,GF->u,wkv);
         scale(-gravity[0],wkv);
         /// \note the sign here needs to be reversed
         dvadd(wkv,sigma_x); // sigma_x = Lt*(u_{,x}-avg_rho*g_x)
         dvmul(L_t->u,GF->u,wkv);
         scale(-gravity[1],wkv);
         /// \note the sign here needs to be reversed
         dvadd(wkv,sigma_y); // sigma_y = Lt*(u_{,y}-avg_rho*g_y)
         if ( !use_ldg ) {   // IP: gradient goes into the unused sides of GF
           GF->fill_sides( sigma_x, sigma_y );
         }
         U->lift( F, sigma_x, 'x' );
         U->project(sigma_x);
         U->lift( F, sigma_y, 'y' );
         U->project(sigma_y);
         U->fill_sides( sigma_x, sigma_y );    // normal flux on sides
         U->gradient(sigma_x, sigma_x, 'x');   // sigma_x = u_{,xx}
         U->gradient(sigma_y, sigma_y, 'y');   // sigma_y = u_{,yy}
         dvadd( sigma_x, sigma_y, F->u ); // F->u =\sum_{i=1}^2 (sigma_i)_{,x_i}
      } else if (nsd==3) { // 3D
         dVector sigma_x(wk1,qtot);
         dVector sigma_y(wk2,qtot);
         dVector sigma_z(wk3,qtot);
         U->gradient(U->u, sigma_x, sigma_y, sigma_z);
         dvmul(L_t->u,sigma_x); // sigma_x = Lt*u_{,x}
         dvmul(L_t->u,sigma_y); // sigma_y = Lt*u_{,y}
         dvmul(L_t->u,sigma_z); // sigma_z = Lt*u_{,z}
         dvmul(L_t->u,GF->u,wkv);
         scale(-gravity[0],wkv);
         /// \note the sign here needs to be reversed
         dvadd(wkv,sigma_x); // sigma_x = Lt*(u_{,x}-avg_rho*g_x)
         dvmul(L_t->u,GF->u,wkv);
         scale(-gravity[1],wkv);
         /// \note the sign here needs to be reversed
         dvadd(wkv,sigma_y); // sigma_y = Lt*(u_{,y}-avg_rho*g_y)
         dvmul(L_t->u,GF->u,wkv);
         scale(-gravity[2],wkv);
         /// \note the sign here needs to be reversed
         dvadd(wkv,sigma_z); // sigma_z = Lt*(u_{,z}-avg_rho*g_z)
         if ( !use_ldg ) { // IP: gradient goes into the unused sides of GF ...
           GF->fill_sides( sigma_x, sigma_y, sigma_z );  // normal flux
         }
         U->lift( F, sigma_x, 'x' );
         U->project(sigma_x);
         U->lift( F, sigma_y, 'y' );
         U->project(sigma_y);
         U->lift( F, sigma_z, 'z' );
         U->project(sigma_z);
         U->fill_sides( sigma_x, sigma_y, sigma_z );  // normal flux on sides
         U->gradient(sigma_x, sigma_x, 'x');          // sigma_x = u_{,xx}
         U->gradient(sigma_y, sigma_y, 'y');          // sigma_y = u_{,yy}
         U->gradient(sigma_z, sigma_z, 'z');          // sigma_z = u_{,zz}
         dvadd( sigma_x, sigma_y, sigma_z, F->u );    // F->u = (sigma_i)_{,i}
      }
    }
  }

  if ( !use_ldg ) { // IP: gradient goes into the unused sides of GF...
    Us.share_sides();
    if (use_new_bc) {
      for (BC::db_citr i=BC_db.begin(); i!= BC_db.end(); ++i)
        i->second->matrix_apply_flux( t, Gf );
      for (BC::db_citr i=BC_db.begin(); i!= BC_db.end(); ++i)
        i->second->matrix_apply_flux( t, Us );
    } else {
      enforce_flux_bc(Gf); // Neumann BCs
      enforce_flux_bc(Us); // Neumann BCs
    }
    //
    if (stab!=0.0) {
      if (use_new_bc) {
        average_flux_plus_interior_penalty_new_bc( Uv, Gf, Lt, Uf );
      } else {
        average_flux_plus_interior_penalty( Uv, Gf, Lt, Uf );
        interior_penalty_boundary_correction( Uv, Gf, Lt, Uf );
      }
    } else {
      average_flux( Gf, Uf, '-' );
    }
  } else {
    Us.share_sides();
    if (use_new_bc) {
      for (BC::db_citr i=BC_db.begin(); i!= BC_db.end(); ++i)
        i->second->matrix_apply_flux( t, Us );
    } else {
      enforce_flux_bc(Us); // Neumann BCs
    }
    //
    if (stab!=0.0) {
      if (use_new_bc) {
        average_flux_plus_interior_penalty_new_bc( Uv, Us, Lt, Uf );
      } else {
        average_flux_plus_interior_penalty( Uv, Us, Lt, Uf );
        interior_penalty_boundary_correction( Uv, Us, Lt, Uf );
      }
    } else {
      average_flux( Us, Uf, '-' );
    }
  }

  for (vField::size_type i=0; i<Us.size(); ++i) {
    for (LocalSize e=0; e<Us[i]->ne; ++e) {
      Element *U = Us[i]->el[e];
      Element *F = Uf[i]->el[e];
      U->lift( F, F->u );
    }
  }

  // source term from file
  Sffile.zero();
  add_source( Us, Sffile );
  add(Sffile, Uf);
  // source term from advection-diffusion
  add(Sf, Uf);
  // debug output
  if (myparams.get("tecplot")) {
    Sffile.tecplot(root+".Sffile_last.dat","Viscous source term from file");
    Sf.tecplot(root+".Sf_last.dat","Viscous source term from AdvDiff");
  }

  project( Uf );
  Uf.forward_transform();
}

Scalar Darcy::compute_average_mobility(
    const Side * const Lt_loc,
    const Side * const Lt_adj,
    const Ordinal ql,
    const Ordinal qr
    ) const {
  Scalar avg_tot_abs_mobility = 0.5*(Lt_loc->u[ql] + Lt_adj->u[qr]);
  return avg_tot_abs_mobility;
}

#ifdef REO_USE_GETSIDEMAPS
Scalar Darcy::compute_average_mobility(
    const Side * const Lt_loc,
    const Side * const Lt_adj,
    const SideMap &smap,
    const Ordinal q
    ) const {
  Scalar avg_tot_abs_mobility = 0.5*(   Lt_loc->u[smap.idl()[q]]
                                      + Lt_adj->u[smap.idr()[q]] );
  return avg_tot_abs_mobility;
}
#endif

/// Local Discontinuous Galerkin Solution flux
void Darcy::solution_flux(const vField &L_t, vField &Uf, vField &Ff) const {
  //cout<<"Darcy::ldg_solution_flux(...)"<<endl;
#ifdef REO_USE_GETSIDEMAPS
  SideMap smap;
#endif
  for (vField::size_type ni=0; ni<Nfields; ni++) {
    for (LocalSize e=0; e<Uf[ni]->ne; e++) {
      Element *const U = Uf[ni]->el[e];
      Element *const F = Ff[ni]->el[e];
      const Element *const Ltot = L_t[0]->el[e];

      for (LocalSize i=0; i<U->nSides(); i++) {
        if (U->side[i]->master()) {
          const LocalSize qtot = U->side[i]->qtot();
#ifdef REO_USE_GETSIDEMAPS
          get_side_maps(U->side[i], U->side[i]->link, smap.idl(), smap.idr() );
#endif
          for (LocalSize q=0; q<qtot; q++) {
#ifdef REO_USE_GETSIDEMAPS
            const Scalar avg_tot_abs_mobility = compute_average_mobility(
                Ltot->side[i], Ltot->side[i]->link, smap, q );

            smap.l(F->side[i], q) = 0.5*(  smap.l(U->side[i], q)
                                          +smap.r(U->side[i], q) );
            smap.l(F->side[i], q) *= avg_tot_abs_mobility;
            smap.r(F->side[i], q) = smap.l(F->side[i], q);

            smap.l(U->side[i], q) *= avg_tot_abs_mobility;
            smap.r(U->side[i], q) *= avg_tot_abs_mobility;
#else
            const Ordinal ql = U->sideMap(U->side[i], q);
            const Ordinal qr = U->sideMap(U->side[i]->link, q);

            const Scalar avg_tot_abs_mobility = compute_average_mobility(
                Ltot->side[i], Ltot->side[i]->link, ql, qr);

            F->side[i]->u[ql] = 0.5*(U->side[i]->u[ql] + U->side[i]->link->u[qr]);
            F->side[i]->u[ql] *= avg_tot_abs_mobility;
            F->side[i]->link->u[qr] = F->side[i]->u[ql];

            U->side[i]->u[ql] *= avg_tot_abs_mobility;
            U->side[i]->link->u[qr] *= avg_tot_abs_mobility;
#endif
          }
        }
      }
    }
  }

}

/// Local Discontinuous Galerkin Solution flux
/** Does something different depending on whether it is a BC side. */
void Darcy::solution_flux_new_bc(const vField &L_t,
                                 vField &Uf, vField &Ff) const {
  //cout<<"Darcy::ldg_solution_flux(...)"<<endl;
#ifdef REO_USE_GETSIDEMAPS
  SideMap smap;
#endif
  for (vField::size_type ni=0; ni<Nfields; ni++) {
    for (LocalSize e=0; e<Uf[ni]->ne; e++) {
      Element *const U = Uf[ni]->el[e];
      Element *const F = Ff[ni]->el[e];
      const Element *const Ltot = L_t[0]->el[e];

      for (LocalSize i=0; i<U->nSides(); i++) {
        if (U->side[i]->master()) {
          const LocalSize qtot = U->side[i]->qtot();
#ifdef REO_USE_GETSIDEMAPS
          get_side_maps(U->side[i], U->side[i]->link, smap.idl(), smap.idr() );
#endif
          // New conditional on whether a BC side
          if (U->side[i]->is_bc()) {
            for (LocalSize q=0; q<qtot; q++) {
#ifdef REO_USE_GETSIDEMAPS
              const Scalar avg_tot_abs_mobility = compute_average_mobility(
                  Ltot->side[i], Ltot->side[i]->link, smap, q );

              smap.l(F->side[i], q) = smap.r(U->side[i], q);
              smap.l(F->side[i], q) *= avg_tot_abs_mobility;

              smap.l(U->side[i], q) *= avg_tot_abs_mobility;
#else
              const Ordinal ql = U->sideMap(U->side[i], q);
              const Ordinal qr = U->sideMap(U->side[i]->link, q);
              const Scalar avg_tot_abs_mobility = compute_average_mobility(
                  Ltot->side[i], Ltot->side[i]->link, ql, qr );
              F->side[i]->u[ql] = U->side[i]->link->u[qr];
              F->side[i]->u[ql] *= avg_tot_abs_mobility;
              U->side[i]->u[ql] *= avg_tot_abs_mobility;
#endif
            }
          } else {
            for (LocalSize q=0; q<qtot; q++) {
#ifdef REO_USE_GETSIDEMAPS
              const Scalar avg_tot_abs_mobility = compute_average_mobility(
                  Ltot->side[i], Ltot->side[i]->link, smap, q );

              smap.l(F->side[i], q) = 0.5*(  smap.l(U->side[i], q)
                                            +smap.r(U->side[i], q) );
              smap.l(F->side[i], q) *= avg_tot_abs_mobility;
              smap.r(F->side[i], q) = smap.l(F->side[i], q);

              smap.l(U->side[i], q) *= avg_tot_abs_mobility;
              smap.r(U->side[i], q) *= avg_tot_abs_mobility;
#else
              const Ordinal ql = U->sideMap(U->side[i], q);
              const Ordinal qr = U->sideMap(U->side[i]->link, q);
              const Scalar avg_tot_abs_mobility = compute_average_mobility(
                  Ltot->side[i], Ltot->side[i]->link, ql, qr );

              F->side[i]->u[ql] = 0.5*(U->side[i]->u[ql] +
                    U->side[i]->link->u[qr]);
              F->side[i]->u[ql] *= avg_tot_abs_mobility;
              F->side[i]->link->u[qr] = F->side[i]->u[ql];
              U->side[i]->u[ql] *= avg_tot_abs_mobility;
              U->side[i]->link->u[qr] *= avg_tot_abs_mobility;
#endif
            }
          }
        }
      }
    }
  }

}

/// Compute the ldg flux on the sides
void Darcy::average_flux_plus_interior_penalty(
    const vField &Up,
    const vField &Us,
    const vField &L_t,
    vField &Uf) const {
  //cout<<"Darcy::average_flux_plus_interior_penalty(...)"<<endl;
#ifdef REO_USE_GETSIDEMAPS
  SideMap smap;
#endif
  for (vField::size_type n=0; n<Us.size(); n++) {
    for (LocalSize e=0; e<Us[n]->ne; e++) {
      const Element *const P = Up[n]->el[e];
      const Element *const S = Us[n]->el[e];
      const Element *const Ltot = L_t[0]->el[e];
      Element *F = Uf[n]->el[e];
      for (LocalSize i=0; i<S->nSides(); i++) {
        if (S->side[i]->master()) {
          const LocalSize qstot = S->side[i]->qtot();
#ifdef REO_USE_GETSIDEMAPS
          get_side_maps(S->side[i],S->side[i]->link,smap.idl(),smap.idr());
#endif
          for (LocalSize q=0; q<qstot; q++) {
#ifdef REO_USE_GETSIDEMAPS
            const Scalar C11 = computeC11(
                S->side[i],    S->side[i]->link,
                Ltot->side[i], Ltot->side[i]->link,
                smap, qstot);
            smap.l(F->side[i],q) = pt5*( smap.l(S->side[i], q)
                                        -smap.r(S->side[i], q))
                                  -C11*( smap.l(P->side[i], q)
                                        -smap.r(P->side[i], q));
            smap.r(F->side[i], q) = -smap.l(F->side[i], q);
#else
            const Ordinal ql = S->sideMap(S->side[i], q);
            const Ordinal qr = S->sideMap(S->side[i]->link, q);
            const Scalar C11 = computeC11(
                S->side[i],    S->side[i]->link,
                Ltot->side[i], Ltot->side[i]->link,
                S, qstot);
            F->side[i]->u[ql] = pt5*(S->side[i]->u[ql]
                                        -S->side[i]->link->u[qr])
                                  -C11*(P->side[i]->u[ql]
                                        -P->side[i]->link->u[qr]);
            F->side[i]->link->u[qr] = -F->side[i]->u[ql];
#endif
          }
        }
      }
    }
  }
}

/// Compute the ldg flux on the sides
/** Does something different on BC sides. */
void Darcy::average_flux_plus_interior_penalty_new_bc(
    const vField &Up,
    const vField &Us,
    const vField &L_t,
    vField &Uf) const {
  // cout<<"Darcy::average_flux_plus_interior_penalty(...)"<<endl;
#ifdef REO_USE_GETSIDEMAPS
  SideMap smap;
#endif
  for (vField::size_type n=0; n<Us.size(); n++) {
    for (LocalSize e=0; e<Us[n]->ne; e++) {
      const Element *P = Up[n]->el[e];
      const Element *S = Us[n]->el[e];
      const Element *Ltot =   L_t[0]->el[e];
      Element *F = Uf[n]->el[e];
      for (LocalSize i=0; i<S->nSides(); i++) {
        if (S->side[i]->master()) {
          const LocalSize qstot = S->side[i]->qtot();
#ifdef REO_USE_GETSIDEMAPS
          get_side_maps(S->side[i],S->side[i]->link,smap.idl(),smap.idr());
#endif
          if (S->side[i]->is_bc()) {
            for (LocalSize q=0; q<qstot; q++) {
#ifdef REO_USE_GETSIDEMAPS
              const Scalar C11 = computeC11(
                  S->side[i],    S->side[i]->link,
                  Ltot->side[i], Ltot->side[i]->link,
                  smap, qstot);
              smap.l(F->side[i],q) = smap.r(S->side[i], q)
                              -C11*( smap.l(P->side[i], q)
                                    -smap.r(P->side[i], q));
              // smap.r(F->side[i], q) = -smap.l(F->side[i], q);
#else
              const Ordinal ql = S->sideMap(S->side[i], q);
              const Ordinal qr = S->sideMap(S->side[i]->link, q);
              const Scalar C11 = computeC11(
                  S->side[i],    S->side[i]->link,
                  Ltot->side[i], Ltot->side[i]->link,
                  S, qstot);
             F->side[i]->u[ql] = S->side[i]->link->u[qr]
                              -C11*( P->side[i]->u[ql]
                                    -P->side[i]->link->u[qr]);
#endif
            }
          } else {
            for (LocalSize q=0; q<qstot; q++) {
#ifdef REO_USE_GETSIDEMAPS
              const Scalar C11 = computeC11(
                  S->side[i],    S->side[i]->link,
                  Ltot->side[i], Ltot->side[i]->link,
                  smap, qstot);
              smap.l(F->side[i],q) = pt5*( smap.l(S->side[i], q)
                                          -smap.r(S->side[i], q))
                                    -C11*( smap.l(P->side[i], q)
                                          -smap.r(P->side[i], q));
              smap.r(F->side[i], q) = -smap.l(F->side[i], q);
#else
              const Ordinal ql = S->sideMap(S->side[i], q);
              const Ordinal qr = S->sideMap(S->side[i]->link, q);
              const Scalar C11 = computeC11(
                  S->side[i],    S->side[i]->link,
                  Ltot->side[i], Ltot->side[i]->link,
                  S, qstot);
              F->side[i]->u[ql] = pt5*(S->side[i]->u[ql]
                                          -S->side[i]->link->u[qr])
                                    -C11*( P->side[i]->u[ql]
                                          -P->side[i]->link->u[qr]);
              F->side[i]->link->u[qr] = -F->side[i]->u[ql];
#endif
            }
          }
        }
      }
    }
  }
}

/// \warning This does not work with reversed sides
void Darcy::interior_penalty_boundary_correction(const vField &Up,
                                 const vField &Us,
                                 const vField &L_t,
                                 vField &F) const {
  // comm->cout() << "Darcy::interior_penalty_boundary_correction()" << endl;
#ifdef REO_USE_GETSIDEMAPS
  SideMap smap;
#endif
  for (LocalSize n=0; n<Up[0]->nbc; ++n) {
#ifdef REO_USE_GETSIDEMAPS
    get_side_maps(Up[0]->bc[n]->S, Up[0]->bc[n]->S->link,
                  smap.idl(), smap.idr());
#endif
    for(LocalSize q=0; q<Up[0]->bc[n]->S->qtot(); ++q) {
#ifdef REO_USE_GETSIDEMAPS
      const Scalar C11 = computeC11(
        Us[0]->bc[n]->S,    Us[0]->bc[n]->S->link,
        L_t[0]->bc[n]->S,   L_t[0]->bc[n]->S->link,
        smap,               Us[0]->bc[n]->S->qtot());
      const Scalar correction =0.5*C11*( smap.l(Up[0]->bc[n]->S, q)
                                         -smap.r(Up[0]->bc[n]->S, q) );
      smap.l(F[0]->bc[n]->S, q) += correction;
      smap.r(F[0]->bc[n]->S, q) -= correction;
#else
      Element* U = Up[0]->bc[n]->S->elink;
      const Ordinal ql = U->sideMap(Up[0]->bc[n]->S, q);
      const Ordinal qr = U->sideMap(Up[0]->bc[n]->S->link, q);
      const Scalar C11 = computeC11(
        Us[0]->bc[n]->S,    Us[0]->bc[n]->S->link,
        L_t[0]->bc[n]->S,   L_t[0]->bc[n]->S->link,
        U,               Us[0]->bc[n]->S->qtot());
      const Scalar correction =0.5*C11*( Up[0]->bc[n]->S->u[ql]
                                         -Up[0]->bc[n]->S->link->u[qr] );
      F[0]->bc[n]->S->u[ql] += correction;
      F[0]->bc[n]->S->link->u[qr] -= correction;
#endif
    }
  }
}

Scalar Darcy::computeC11(
    const Side * const Us_loc,
    const Side * const Us_adj,
    const Side * const Lt_loc,
    const Side * const Lt_adj,
    const Element * const S,
    const Ordinal qstot
) const {
  // the mesh length selection below will not work for parallel matrix-free,
  // since there is no ghosting available !!!!!!!!!!!!!!!!!
  const Scalar h_n = 0.5*(1.0/Us_loc->h_n_inv() + 1.0/Us_adj->h_n_inv());
  // for optimal stabilization, we should take max(p) between neighbor
  // elements.  But since we don't have access to neighbors p, we can only
  // take the local p
  //
  // Does the side have some information about p? Maybe via q?  then we
  // could use at least the opposing sides p.
  //
  // The polynomial order selection below will not work for parallel
  // matrix-free, since there is no ghosting available !!!!!!!!!!!!!!!!!
  const Scalar p = max(Us_loc->elink->pOrder(), Us_adj->elink->pOrder());
  // const Scalar p = Us_loc->elink->pOrder();
  Scalar avg_tot_abs_mobility = 0.0;
  for (Ordinal q = 0; q < qstot; ++q) {
    const Ordinal ql = S->sideMap(Us_loc, q);
    const Ordinal qr = S->sideMap(Us_adj, q);
    avg_tot_abs_mobility +=
      compute_average_mobility( Lt_loc, Lt_adj, ql, qr);
  }
  avg_tot_abs_mobility /= qstot;
  avg_tot_abs_mobility = abs(avg_tot_abs_mobility);
  const Scalar C11 = stab*avg_tot_abs_mobility*p*p/h_n;
  return C11;
}

#ifdef REO_USE_GETSIDEMAPS
Scalar Darcy::computeC11(
    const Side * const Us_loc,
    const Side * const Us_adj,
    const Side * const Lt_loc,
    const Side * const Lt_adj,
    const SideMap &smap,
    const Ordinal qstot
) const {
  // the mesh length selection below will not work for parallel matrix-free,
  // since there is no ghosting available !!!!!!!!!!!!!!!!!
  const Scalar h_n = 0.5*(1.0/Us_loc->h_n_inv() + 1.0/Us_adj->h_n_inv());
  // for optimal stabilization, we should take max(p) between neighbor
  // elements.  But since we don't have access to neighbors p, we can only
  // take the local p
  //
  // Does the side have some information about p? Maybe via q?  then we
  // could use at least the opposing sides p.
  //
  // The polynomial order selection below will not work for parallel
  // matrix-free, since there is no ghosting available !!!!!!!!!!!!!!!!!
  const Scalar p = max(Us_loc->elink->pOrder(), Us_adj->elink->pOrder());
  // const Scalar p = Us_loc->elink->pOrder();
  Scalar avg_tot_abs_mobility = 0.0;
  for (Ordinal q = 0; q < qstot; ++q) {
    avg_tot_abs_mobility +=
      compute_average_mobility( Lt_loc, Lt_adj, smap, q );
  }
  avg_tot_abs_mobility /= qstot;
  avg_tot_abs_mobility = abs(avg_tot_abs_mobility);
  const Scalar C11 = stab*avg_tot_abs_mobility*p*p/h_n;
  return C11;
}
#endif

#ifdef DGM_USE_EPETRA

/// test serialization for a number of used objects
void Darcy::test_serialization() const {
#ifdef DGM_USE_GENERAL_GHOSTING
  if ((int)myparams.get("ghosting") == 1) {
    // let's start with some tests (they are tiny and fast!)
    const int status = 
      CMC::test_CMC_Vector_serialization<Scalar,int>();
    if (status != 0) throw DGM::exception("Error in serialization");
    assert(DGM::Vertex::test_serialization() == 0);
    assert(DGM::Edge::test_serialization() == 0);
  }
#endif
}

/// Computes the BC side contribution to the matrix and right-hand side
void Darcy::Matrix_sides_bndry(
    const vField &Uf,
    Epetra_CrsMatrix &A
    ) const {

  using namespace Matrix;

  std::set<string> Dirichlet; // names from the .bct file (e.g. "bc100")
  std::set<string> Neumann;   // names from the .bct file (e.g. "bc101")

  // Hack alarm: this should be implemented in the various BC classes-> no
  // casts
  for (BC::db_citr i=BC_db.begin(); i!= BC_db.end(); ++i) {
    const BC *const bc = &*(i->second);
    if (dynamic_cast<Reo::Darcy::DirichletBC const*const>(bc)!=NULL) {
      Dirichlet.insert(bc->type); // ("bc100" is added to the set "Dirichlet")
    } else if (dynamic_cast<Reo::Darcy::NeumannBC const*const>(bc)!=NULL) {
      Neumann.insert(bc->type); // ("bc101" is added to the set "Neumann")
    }
  }

  MatrixSideAssembler<NfieldsT> assembler(Uf, true);

  for (LocalSize n=0; n<Uf[0]->nbc; ++n) {
    boost::array<Side*, NfieldsT> Us_loc;
    // "FieldNum<pres>::pos" selects the index associated with "pres"
    // (pressure) and points Us_loc to it
    Us_loc[FieldNum<pres>::pos] = Uf[FieldNum<pres>::pos]->bc[n]->S;
    // use internal links of Us_loc to point to Us_adj
    boost::array<Side*, NfieldsT> Us_adj = select_adj<NfieldsT>(Us_loc);

    assembler.setup(this, Us_loc, Us_adj);

    const Side *const Lt_loc = Lt[0]->bc[n]->S;
    const Side *const Lt_adj = vField::select_adj(Lt_loc);

    // load side quadrature points
    const int qstot = Us_loc[0]->qtot();

    // work vectors
    dVector ws_loc(qstot);

    const Boundary *const bnd = Uf[0]->bc[n];
    const string type = bnd->type;

    if (Dirichlet.find(type) != Dirichlet.end() ) {
      // - ( v , Lt * nabla u * n )_G_Dirichlet
      ws_loc.Mul(-1.0, Lt_loc->u);
      assembler.locloc<pres, d0, pres, dn>( ws_loc );
      // - ( Lt * nabla v * n , u )_G_Dirichlet
      assembler.locloc<pres, dn, pres, d0>( ws_loc );
      // + ( v , C11 u )_G_Dirichlet
      const Scalar C11 = computeC11(Us_loc[0], Us_adj[0],
                                    Lt_loc, Lt_adj, Us_loc[0]->elink, qstot);
      assembler.locloc<pres, d0, pres, d0>( C11 );

    } else if (Neumann.find(type) != Neumann.end() ) {

    }

    // scatter the local matrix to global
    assembler.scatter(Uf, A);

  } // loop over boundary sides
}


/// Computes the BC side contribution to the matrix and righthand-side
void Darcy::RHS_sides_bndry(
    const vField &Uf,
    const vField &Ff,
    Epetra_Vector &b
    ) const {

  std::set<string> Dirichlet;
  std::set<string> Neumann;

  // Hack: this should be implemented in the various BC classes-> no casts
  for (BC::db_citr i=BC_db.begin(); i!= BC_db.end(); ++i) {
    const BC *const bc = &*(i->second);
    if (dynamic_cast<Reo::Darcy::DirichletBC const*const>(bc)!=NULL) {
      Dirichlet.insert(bc->type);
    } else if (dynamic_cast<Reo::Darcy::NeumannBC const*const>(bc)!=NULL) {
      Neumann.insert(bc->type);
    }
  }

  using namespace Matrix;

  VectorSideAssembler<NfieldsT> assembler(Uf);

  for (LocalSize n=0; n<Uf[0]->nbc; ++n) {
    boost::array<Side*, NfieldsT> Us_loc;
    Us_loc[0] = Uf[0]->bc[n]->S;
    boost::array<Side*, NfieldsT> Us_adj = select_adj<NfieldsT>(Us_loc);

    assembler.setup(Us_loc);

    // synchronize the quadrature points between neighbors
#ifdef REO_USE_GETSIDEMAPS
    SideMap smap;
    get_side_maps(Us_loc[0],Us_adj[0],smap.idl(),smap.idr());
#endif

    Boundary* bnd = Uf[0]->bc[n];
    string type = bnd->type;

    // entries for rhs vector b
    if (Dirichlet.find(type) != Dirichlet.end() ) {

      // work vectors
      dVector ws_loc(Us_loc[0]->qtot());

      const Side *const Gf_loc = Gf[0]->bc[n]->S;
      //const Side *const Gf_adj = vField::select_adj(Gf_loc);

      const Side *const Lt_loc = Lt[0]->bc[n]->S;
      const Side *const Lt_adj = vField::select_adj(Lt_loc);

      // - ( Lt * nabla v * n , g_Dirichlet )_G_Dirichlet
      // Us_adj->u contains the right stuff due to matrix_apply
      dvmul(Us_adj[0]->u, Lt_loc->u, ws_loc);
      ws_loc *= -1.0;
      assembler.loc<pres, dn>( ws_loc );

      // + ( v , C11 g_Dirichlet )_G_Dirichlet
      // Us_adj->u contains the right stuff due to matrix_apply
#ifdef REO_USE_GETSIDEMAPS
      const Scalar C11 = computeC11(Us_loc[0], Us_adj[0],
                                    Lt_loc, Lt_adj, smap, Us_loc[0]->qtot());
#else
      const Scalar C11 = computeC11(Us_loc[0], Us_adj[0],
                                    Lt_loc, Lt_adj, Us_loc[0]->elink,
                                    Us_loc[0]->qtot());
#endif
      ws_loc.Mul(C11, Us_adj[0]->u);
      assembler.loc<pres, d0>( ws_loc );

      // - ( v , Lt * rho * gravity * n )_G_Dirichlet
      dvmul(Lt_loc->u, Gf_loc->u, ws_loc);
      dVector wkvgrav(ws_loc.size(), 0.0);
      dVector tmp(ws_loc.size());
      if (nsd >= 1) {
        dvmul(ws_loc, Us_loc[0]->nx(), tmp);
        tmp *= -gravity[0]; wkvgrav += tmp;
      }
      if (nsd >= 2) {
        dvmul(ws_loc, Us_loc[0]->ny(), tmp);
        tmp *= -gravity[1]; wkvgrav += tmp;
      }
      if (nsd >= 3) {
        dvmul(ws_loc, Us_loc[0]->nz(), tmp);
        tmp *= -gravity[2]; wkvgrav += tmp;
      }
      assembler.loc<pres, d0>( wkvgrav );

      // - ( [v] , u_misc )_G_Dirichlet
      dVector wkv_umisc(ws_loc.size(), 0.0);
      if (nsd >= 1) {
        ws_loc.Mul(-u_misc[0], Us_loc[0]->nx()); wkv_umisc += ws_loc;
      }
      if (nsd >= 2) {
        ws_loc.Mul(-u_misc[1], Us_loc[0]->ny()); wkv_umisc += ws_loc;
      }
      if (nsd >= 3) {
        ws_loc.Mul(-u_misc[2], Us_loc[0]->nz()); wkv_umisc += ws_loc;
      }
      assembler.loc<pres, d0>( wkv_umisc );

    } else if (Neumann.find(type) != Neumann.end() ) {

      const Side *const Fs_loc = Ff[0]->bc[n]->S;
      const Side *const Fs_adj = vField::select_adj(Fs_loc);

      // + ( v , g_Neumann )_G_Neumann
      assembler.loc<pres, d0>( Fs_adj->u );

    } else {
      comm->error("only Dirichlet and Neumann implemented!");
    }

    // scatter the local matrix to global
    assembler.scatter(Uf, b);

  } // loop over boundary sides
}


/// Computes the side contribution to the matrix and righthand-side
void Darcy::Matrix_sides_interior(
    const vField &Uf,
    Epetra_CrsMatrix &A ) const {

  using namespace Matrix;

  MatrixSideAssembler<NfieldsT> assembler(Uf, true);

  for (LocalSize e=0; e<Uf[0]->ne; e++) {
    // localize elements
    boost::array<Element*, NfieldsT> Ue;
    Ue[0] = Uf[0]->el[e];
    // terms from the sides
    for (LocalSize i=0; i<Ue[0]->nSides(); i++) {
      boost::array<Side*, NfieldsT> Us_loc;
      Us_loc[0] = Ue[0]->side[i];
      boost::array<Side*, NfieldsT> Us_adj = select_adj<NfieldsT>(Us_loc);

      if (Us_loc[0]->is_bc() == true) {
        continue;
      } else {
        assembler.setup(this, Us_loc, Us_adj);

        const Side *const Lt_loc = Lt[0]->el[e]->side[i];
        const Side *const Lt_adj = vField::select_adj(Lt_loc);

        // - ( [v] , {nabla u * n} )_G_i
        dVector pt5Ltloc(Lt_loc->u.size(), 0.0);
        pt5Ltloc += Lt_loc->u; pt5Ltloc *= -0.5;
        dVector pt5Ltadj(Lt_adj->u.size(), 0.0);
        pt5Ltadj += Lt_adj->u; pt5Ltadj *= -0.5;
        assembler.locloc<pres, d0, pres, dn>( pt5Ltloc );
        pt5Ltadj *= -1.0;
        assembler.locadj<pres, d0, pres, dn>
          ( pt5Ltadj, MatrixSideAssembler<NfieldsT>::adj );

        // - ( {nabla v * n} , [u] )_G_i
        assembler.locloc<pres, dn, pres, d0>( pt5Ltloc );
        pt5Ltloc *= -1.0;
        assembler.locadj<pres, dn, pres, d0>
          ( pt5Ltloc, MatrixSideAssembler<NfieldsT>::loc );

        // + ( [v] , C11 [u] )_G_i
        const Scalar C11 = computeC11(Us_loc[0], Us_adj[0],
                                      Lt_loc, Lt_adj, Us_loc[0]->elink,
                                      Us_loc[0]->qtot());
        assembler.locloc<pres, d0, pres, d0>( C11 );
        assembler.locadj<pres, d0, pres, d0>(-C11 );

        // scatter the local matrix to global
        assembler.scatter(Uf, A);
      }
    } // loop over sides
  } // loop over elements
}


/// Computes the side contribution to the matrix and righthand-side
void Darcy::RHS_sides_interior(
    const vField &Uf,
    Epetra_Vector &b) const {

  using namespace Matrix;

  VectorSideAssembler<NfieldsT> assembler(Uf);

  for (LocalSize e=0; e<Uf[0]->ne; e++) {
    boost::array<Element*, NfieldsT> Ue;
    Ue[0] = Uf[0]->el[e];

    // terms from the sides
    for (LocalSize i=0; i<Ue[0]->nSides(); i++) {
      boost::array<Side*, NfieldsT> Us_loc;
      Us_loc[0] = Ue[0]->side[i];
      boost::array<Side*, NfieldsT> Us_adj = select_adj<NfieldsT>(Us_loc);

      if (Us_loc[0]->is_bc() == true) {
        continue;
      } else {
        assembler.setup(Us_loc);

        const Side *const Lt_loc = Lt[0]->el[e]->side[i];
        const Side *const Lt_adj = vField::select_adj(Lt_loc);

        const Side *const Gf_loc = Gf[0]->el[e]->side[i];
        const Side *const Gf_adj = vField::select_adj(Gf_loc);

        // load side quadrature points
        const int qstot  = Us_loc[0]->qtot();

        // synchronize the quadrature points between neighbors
#ifdef REO_USE_GETSIDEMAPS
        SideMap smap;
        get_side_maps(Us_loc[0],Us_adj[0],smap.idl(),smap.idr());
#endif

        // work vectors
        dVector ws_loc(qstot);
        dVector ws_adj(qstot);
        dVector ws_avg(qstot);

        // - ( [v] , { Lt rho gravity } )_Gamma_i
        dvmul(Lt_loc->u, Gf_loc->u, ws_loc);
        if (Lt_adj->u.size() == 0 or Gf_adj->u.size() == 0) {
          comm->cerr() << " Lt_adj->u: " << Lt_adj->u << endl;
          comm->cerr() << " Gf_adj->u: " << Gf_adj->u << endl;
          comm->cerr() << *Lt_adj << endl;
        }
        dvmul(Lt_adj->u, Gf_adj->u, ws_adj);
#ifdef REO_USE_GETSIDEMAPS
        smap.renumber(ws_adj, ws_avg);
#else
        Element* U = Us_loc[0]->elink;
        const Size qs_tot = ws_avg.size();
        // assume that both sides have the same number of quadrature points
        assert(ws_adj.size() == ws_avg.size());
        for (Size q = 0; q < qs_tot; ++q) {
          const Ordinal ql = U->sideMap(Us_loc[0], q);
          const Ordinal qr = U->sideMap(Us_adj[0], q);
          ws_avg(ql) = ws_adj(qr);
        }
#endif
        ws_avg += ws_loc;
        scale(0.5, ws_avg);

        dVector wkvgrav(ws_avg.size(), 0.0);
        dVector tmp(ws_avg.size());
        if (nsd >= 1) {
          dvmul(ws_avg, Us_loc[0]->nx(), tmp);
          tmp *= -gravity[0];
          wkvgrav += tmp;
        }
        if (nsd >= 2) {
          dvmul(ws_avg, Us_loc[0]->ny(), tmp);
          tmp *= -gravity[1];
          wkvgrav += tmp;
        }
        if (nsd >= 3) {
          dvmul(ws_avg, Us_loc[0]->nz(), tmp);
          tmp *= -gravity[2];
          wkvgrav += tmp;
        }
        assembler.loc<pres, d0>( wkvgrav );

        // - ( [v] , { u_misc } )_Gamma_i
        dVector wkv_umisc(ws_avg.size(), 0.0);
        if (nsd >= 1) {
          ws_avg.Mul(-u_misc[0], Us_loc[0]->nx());
          wkv_umisc += ws_avg;
        }
        if (nsd >= 2) {
          ws_avg.Mul(-u_misc[1], Us_loc[0]->ny());
          wkv_umisc += ws_avg;
        }
        if (nsd >= 3) {
          ws_avg.Mul(-u_misc[2], Us_loc[0]->nz());
          wkv_umisc += ws_avg;
        }
        assembler.loc<pres, d0>( wkv_umisc );

        // scatter the local matrix to global
        assembler.scatter(Uf, b);
      }
    } // loop over sides
  }   // loop over elements
}

/// Computes the domain integrals
void Darcy::Matrix_domain_integrals(
    const vField &Uf,
    Epetra_CrsMatrix &A
    ) const
{
  using namespace Matrix;

  Matrix::MatrixDomainAssembler<NfieldsT> assembler(Uf);

  for (LocalSize e=0; e<Uf[0]->ne; e++) {
    boost::array<Element*, NfieldsT> e_loc;
    e_loc[0] = Uf[0]->el[e];

    assembler.setup(e_loc);

    // + ( nabla v , nabla u )_Omega
    if (nsd >= 1) assembler.locloc<pres, dx, pres, dx>( Lt[0]->el[e]->u );
    if (nsd >= 2) assembler.locloc<pres, dy, pres, dy>( Lt[0]->el[e]->u );
    if (nsd >= 3) assembler.locloc<pres, dz, pres, dz>( Lt[0]->el[e]->u );

    // scatter local to global
    assembler.scatter(Uf, A);

  } // end of loop over elements
}

/// element interior contributions to the RHS
void Darcy::RHS_domain_integrals(
    const vField &Uf,
    Epetra_Vector &b
    ) const
{
  using namespace Matrix;

  VectorDomainAssembler<NfieldsT> assembler(Uf);

  for (LocalSize e=0; e<Uf[0]->ne; e++) {
    boost::array<Element*, NfieldsT> e_loc;
    e_loc[0] = Uf[0]->el[e];

    assembler.setup(e_loc);

    // + ( nabla v , rho gravity )_Omega
    dVector mobTimesDens(wk1, e_loc[0]->qtot);
    dvmul(Lt[0]->el[e]->u, Gf[0]->el[e]->u, mobTimesDens);
    dVector src(wk2, e_loc[0]->qtot);
    if (nsd >= 1) {
      src.Mul(gravity[0], mobTimesDens); assembler.loc<pres, dx>( src );
    }
    if (nsd >= 2) {
      src.Mul(gravity[1], mobTimesDens); assembler.loc<pres, dy>( src );
    }
    if (nsd >= 3) {
      src.Mul(gravity[2], mobTimesDens); assembler.loc<pres, dz>( src );
    }

    // + ( nabla v , u_misc )_Omega
    dVector tmp(wk1, e_loc[0]->qtot);
    if (nsd >= 1) { tmp = u_misc[0]; assembler.loc<pres, dx>( tmp );}
    if (nsd >= 2) { tmp = u_misc[1]; assembler.loc<pres, dy>( tmp );}
    if (nsd >= 3) { tmp = u_misc[2]; assembler.loc<pres, dz>( tmp );}

    // + ( v , f_source_adv_diff )_Omega
    assembler.loc<pres, d0>( Sf[FieldNum<pres>::pos]->el[e]->u );

    // + ( v , f_source_file )_Omega
    assembler.loc<pres, d0>( Sffile[FieldNum<pres>::pos]->el[e]->u );

    // scatter local to global
    assembler.scatter(Uf, b);

  } // end of loop over elements
}

/** Computes the matrix for the Hughes, Masud, Wan
    stabilized DG method for the Darcy equation */
void Darcy::Matrix(
    Epetra_CrsMatrix &A) const {

  // note: modes (in 2d) are ordered like:
  // N0 = 1/2
  // N1 = sqrt(3)/2 y
  // N2 = sqrt(3)/2 x
  // N3 = 3/2 xy
  // N4 = ...

  Matrix_sides_interior( U, A);
  Matrix_sides_bndry( U, A);
  Matrix_domain_integrals( U, A);

  const int status = A.FillComplete();
  if (status != 0) throw DGM::exception("Darcy error in FillComplete");
}

/** Computes the right hand-side for the Hughes, Masud, Wan
    stabilized DG method for the Darcy equation */
void Darcy::RHS( Epetra_Vector &b ) const {

  // note: modes (in 2d) are ordered like:
  // N0 = 1/2
  // N1 = sqrt(3)/2 y
  // N2 = sqrt(3)/2 x
  // N3 = 3/2 xy
  // N4 = ...

  b.PutScalar(0.0);
  // right hand side b
  RHS_sides_interior( U, b );
  RHS_sides_bndry( U, Ut, b );
  RHS_domain_integrals( U, b );
}

#endif

/// Supplies a steady-state solve method to override Domain::solve()
int Darcy::solve() {
  if (do_solve) {
    comm->cout() << "Darcy::solve(): " << std::endl;
  } else {
    comm->cout() << "Darcy::solve(): skipping!" << std::endl;
    return 0;
  }

#ifdef DGM_USE_EPETRA

  const bool rebuild = (A == Teuchos::null);
  const bool matrix_solve = myparams.get("matrix_solve");

  if (matrix_solve == true) {

    // ghost elements and DOF layout
    if ((bool)myparams.get("ghostvis"))
      U.ghost(root, 1);
    else
      U.ghost();
    Ut.ghost();
    Lt.ghost();
    Gf.ghost();

    // data on ghosts, sides and boundaries and parallel communication
    Lt.share_ghost_element_data();
    Lt.fill_sides();
    Lt.fill_sides_of_ghost_elements();
    Lt.fill_bc_sides();

    U.zero();
    U.share_ghost_element_data();
    U.fill_sides();
    U.fill_sides_of_ghost_elements();

    if ((bool)myparams.get("ghosting") == true) {
      return 0;
    }

    // prepare source and boundary data
    Sffile.zero();
    add_source( U, Sffile );

    // instead of enforce_BC, which calls apply, use matrix_apply()
    for (BC::db_citr i=BC_db.begin(); i!= BC_db.end(); ++i)
      i->second->matrix_apply( t, U );

    Ut.zero();
    Ut.share_ghost_element_data();
    Ut.fill_sides();
    Ut.fill_sides_of_ghost_elements();

    // instead of enforce_flux_BC, which calls apply,
    // we like to have matrix_flux_apply()
    for (BC::db_citr i=BC_db.begin(); i!= BC_db.end(); ++i)
      i->second->matrix_apply_flux( t, Ut );

    // generate matrix and rhs
    if ( rebuild ) {
      A = Teuchos::null; // dump matrix, otherwise, 2 matrices are in memory
      A = Teuchos::rcp(new Epetra_CrsMatrix(Copy, *U.RowDofMapPtr(), 0));
      b = Teuchos::rcp(new Epetra_Vector(*U.RowDofMapPtr()));
      x = Teuchos::rcp(new Epetra_Vector(*U.RowDofMapPtr(), true));
      lp = Teuchos::rcp(new Epetra_LinearProblem( A.get(), x.get(), b.get()));
    }
    // compute matrix and rhs
    comm->cout() << "  build b" << std::endl;
    if ((int)myparams.get("solver") >= 0) {
      Gf.share_ghost_element_data();
      Gf.fill_sides();  // make sure density from Adv-Diff is on the sides!
      Gf.fill_sides_of_ghost_elements();
      Gf.fill_bc_sides();
      RHS(*b);
      if ( rebuild ) {
        const int n = A->Map().NumGlobalElements();
        comm->cout() << "  build A("<<n<<"x"<<n<<")" << std::endl;
        Matrix(*A);
      }
    }
    //Scalar norm2;
    //b->Norm2(&norm2);
    //comm->cout() << "b norm2 = " << norm2 << endl;
    //comm->cout() << "A->NormInf() = " << A->NormInf() << endl;
    //comm->cout() << "A->NormFrobenius() = " << A->NormFrobenius() << endl;

    if (myparams.get("matrix_out")) {
      comm->cout() << ", output A & b" << std::endl;
      EpetraExt::OperatorToMatlabFile((root+"_dump_A.dat").c_str(),*A);
      EpetraExt::VectorToMatlabFile((root+"_dump_b.dat").c_str(),*b);
    }

    // setup the initial guess and store in U
    // needs update to fill x vector , if iterative solver is used
    for (vField::size_type i=0; i<Un.size(); ++i) {
      for (LocalSize e=0; e<Un[i]->ne; ++e) {
        U[i]->el[e]->u = Un[i]->el[e]->u; // is there a function to copy this?
      }
    }
    U.forward_transform();
    U.pack(*x); // <-- put initial guess into Epetra vector
    //U.pack();

    if ((int)myparams.get("solver") == solve_direct) {
      direct_solve( rebuild );
    } else if ((int)myparams.get("solver") == solve_iterative){
      Teuchos::ParameterList solparams;
      int kspace = myparams.get("dim_krylov");
      solparams.set("kspace", kspace);
      int iterations = myparams.get("iterations");
      solparams.set("iterations", iterations);
      Scalar tolerance = myparams.get("tolerance");
      solparams.set("tolerance", tolerance);
      iterative_solve( solparams, rebuild );
    } else if ((int)myparams.get("solver") == solve_iterative_ML){
      Teuchos::ParameterList solparams;
      int kspace = myparams.get("dim_krylov");
      solparams.set("kspace", kspace);
      int iterations = myparams.get("iterations");
      solparams.set("iterations", iterations);
      Scalar tolerance = myparams.get("tolerance");
      solparams.set("tolerance", tolerance);
      int p = params.get("p");
      solparams.set("Legendre polynomial order", p);
      iterative_ML_solve( solparams, rebuild );
    } else {
      comm->cout() << "No attempt to solve the linear system per user request"
                   << endl;
    }

    // extract the solution
    U.unpack(*x);

  } else {

    comm->cout() << "Matrix-free formulation, " << std::endl;

    // evaluate the residual and store in Ut
    U.zero();
    residual(U,Ut);  // compute r(0) (make sure U = 0)
    scale(-one,Ut);  // compute -r(0)
    Ut.pack();
    b = Teuchos::rcp(new Epetra_Vector( *Ut.modal_vec ));
    Ut.unpack();

    if (myparams.get("darcy_pin")) {
      // pin one constant mode to zero
      (*b)[0] = 0;
      U.zero();
      U.forward_transform();
      U[0]->el[0]->uh[0] = 1; // does that work in parallel?
      U.backward_transform();
      residual( U, Uo );
      axpy( one, Ut, Uo, Uo );
      scale(-one,Uo);
    }

    // setup the initial guess and store in U
    for (vField::size_type i=0; i<Un.size(); ++i) {
      for (LocalSize e=0; e<Un[i]->ne; ++e) {
        U[i]->el[e]->u = Un[i]->el[e]->u; // is there a function to copy this?
      }
    }
    if (!restart) {
      set_ic(U);
      if (myparams.get("tecplot"))   U.tecplot(root+"_ic.dat","Initial Guess");
    }
    U.forward_transform();
    U.pack();

    Operator op( this, U.eComm.get(), U.modal_map.get() );

    if ((int)myparams.get("solver") == 1) {
      lp = Teuchos::rcp(new Epetra_LinearProblem(
          &op, U.modal_vec.get(), b.get()));
      Teuchos::ParameterList solparams;
      int kspace = myparams.get("dim_krylov");
      solparams.set("kspace", kspace);
      int iterations = myparams.get("iterations");
      solparams.set("iterations", iterations);
      Scalar tolerance = myparams.get("tolerance");
      solparams.set("tolerance", tolerance);
      iterative_solve_matrixfree( solparams, rebuild );
    } else {  // Use matrix-free approach with AztecOO to solve
      Epetra_CrsMatrix *A_ = GenerateMatrixViaMatlabOutput(op);
      // comm->cout() << "Finished Epetra CRS matrix" << endl;
      lp = Teuchos::rcp(new Epetra_LinearProblem(
          A_, U.modal_vec.get(), b.get()));
      direct_solve( true );
      delete A_;
    }

    // transform Ut back to physical space
    Ut.backward_transform();

    // extract solution
    U.unpack();
  }

  U.backward_transform();

  //U.norm();

  if (!restart) {
    write(root+".rst",U);
#ifndef DGM_PARALLEL
    if (myparams.get("tecplot"))
      U.tecplot((root+"out.dat").c_str(),"Darcy solution");
#endif
  }

  // debug output
  if (myparams.get("tecplot")) {
    U.tecplot(root+".pres_last.dat","Last Darcy pressure solution");
  }

  if (step%Ntout==0) {
    write(step, U);
  }

  copy(U, Un);

#if 0
  // output convective field for debugging
  // the memory(?) bug shows in the velocity field after one Darcy solve
  // temporary convective field
  vField Cf;
  Cf.set_name("Cf");
  Cf.push_back( new Field(U[0], root, "Cx") );
  if (nsd>1) Cf.push_back( new Field(U[0], root, "Cy") );
  if (nsd>2) Cf.push_back( new Field(U[0], root, "Cz") );
#ifdef MAKE_CONTIGUOUS
  Cf.reset_storage();     // make the vField contiguous
#endif

  postprocess_Darcy_velocity( U, Ut, Cf);

#ifndef DGM_PARALLEL
//  if (myparams.get("tecplot"))
    Cf.tecplot(root+".Cf_last.dat","Darcy solution");
#endif
  comm->exit();
#endif

#else  // !DGM_USE_EPETRA

  comm->error("Darcy::solve() must be built with Trilinos");

#endif // DGM_USE_EPETRA

  return 0;
}

void Darcy::solve_and_get_Darcy_velocity( vField &Cf )
{
  // don't start from IC, use last solution available
  set_restart();

  // solve
  solve();
  postprocess_Darcy_velocity( U, Ut, Cf);

#ifndef DGM_PARALLEL
  if (myparams.get("tecplot"))
    Cf.tecplot(root+".Cf_last.dat","Darcy solution");
#endif
}


/// Supplies a post-processed velocity field from the pressure field
void Darcy::postprocess_Darcy_velocity(
    vField &Us,  ///< Darcy pressure
    vField &Uf,  ///< dummy , we use sides of this vField to do computations
    vField &Vt   ///< convective velocity [out]
) {
  //  comm->cout() << "Darcy::postprocess_Darcy_velocity() " << endl;
  const bool use_new_bc = myparams.get("use_new_bc");
  const bool matrix_solve = myparams.get("matrix_solve");

  if (matrix_solve) {
#ifdef DGM_USE_EPETRA
    Us.ghost();
    Us.share_ghost_element_data();
#endif
    Us.fill_sides();
    Us.fill_sides_of_ghost_elements();
  } else {
    Us.fill_sides();
    Us.share_sides();
  }
  if (use_new_bc) {
    for (BC::db_citr i=BC_db.begin(); i!= BC_db.end(); ++i)
      i->second->matrix_apply( t, Us );
  } else {
    enforce_bc(Us);  // Dirichlet BCs
  }

  if (use_new_bc) {
    solution_flux_new_bc( Lt, Us, Uf );
  } else {
    solution_flux( Lt, Us, Uf );
  }
//  Gf.norm();
//  Lt.norm();
//  Us.norm();
//  Uf.norm();

//  for (LocalSize i=0; i<Us.size(); ++i) {
    for (LocalSize e=0; e<Us[0]->ne; ++e) {
      const Element *const U = Us[0]->el[e];
      const Element *const F = Uf[0]->el[e];
      const Element *const L_t=   Lt[0]->el[e];
      const Element *const GF =   Gf[0]->el[e];
      const LocalSize qtot = U->qtot;

      dVector wkv(qtot);
      if (nsd==1) { // 1D
        dVector sigma_x(wk1,qtot);
        dVector sigma_dummy(wk2,qtot);
        U->gradient(U->u, sigma_x);
        dvmul(L_t->u,sigma_x); // sigma_x = Lt*u_{,x}
        dvmul(L_t->u,GF->u,wkv);
        scale(-gravity[0],wkv);
        dvadd(wkv,sigma_x); // sigma_x = Lt*(u_{,x}-avg_rho*g_x)
        wkv = -u_misc[0];
        dvadd(wkv,sigma_x); // sigma_x = Lt*(u_{,x}-avg_rho*g_x) - u_misc_x
        U->lift( F, sigma_x, 'x' );
        U->project(sigma_x);
        // sigma_x ("v_x") = - ( Lt*(u_{,x}-avg_rho*g_x) - u_misc_x )
        scale(-1.0,sigma_x);
        Vt[0]->el[e]->u = sigma_x;
      } else if (nsd==2) { // 2D
        dVector sigma_x(wk1,qtot);
        dVector sigma_y(wk2,qtot);
        U->gradient(U->u, sigma_x, sigma_y);
        dvmul(L_t->u,sigma_x); // sigma_x = Lt*u_{,x}
        dvmul(L_t->u,sigma_y); // sigma_y = Lt*u_{,y}
        dvmul(L_t->u,GF->u,wkv);
        scale(-gravity[0],wkv);
        dvadd(wkv,sigma_x); // sigma_x = Lt*(u_{,x}-avg_rho*g_x)
        dvmul(L_t->u,GF->u,wkv);
        scale(-gravity[1],wkv);
        dvadd(wkv,sigma_y); // sigma_y = Lt*(u_{,y}-avg_rho*g_y)
        wkv = -u_misc[0];
        dvadd(wkv,sigma_x); // sigma_x = Lt*(u_{,x}-avg_rho*g_x) - u_misc_x
        wkv = -u_misc[1];
        dvadd(wkv,sigma_y); // sigma_y = Lt*(u_{,y}-avg_rho*g_y) - u_misc_y
        U->lift( F, sigma_x, 'x' );
        U->project(sigma_x);
        U->lift( F, sigma_y, 'y' );
        U->project(sigma_y);
        // sigma_x ("v_x") = - ( Lt*(u_{,x}-avg_rho*g_x) - u_misc_x )
        scale(-1.0,sigma_x);
        Vt[0]->el[e]->u = sigma_x;
        // sigma_y ("v_y") = - ( Lt*(u_{,y}-avg_rho*g_y) - u_misc_y )
        scale(-1.0,sigma_y);
        Vt[1]->el[e]->u = sigma_y;
      } else if (nsd==3) { // 3D
        dVector sigma_x(wk1,qtot);
        dVector sigma_y(wk2,qtot);
        dVector sigma_z(wk3,qtot);
        U->gradient(U->u, sigma_x, sigma_y, sigma_z);
        dvmul(L_t->u,sigma_x); // sigma_x = Lt*u_{,x}
        dvmul(L_t->u,sigma_y); // sigma_y = Lt*u_{,y}
        dvmul(L_t->u,sigma_z); // sigma_z = Lt*u_{,z}
        dvmul(L_t->u,GF->u,wkv);
        scale(-gravity[0],wkv);
        dvadd(wkv,sigma_x); // sigma_x = Lt*(u_{,x}-avg_rho*g_x)
        dvmul(L_t->u,GF->u,wkv);
        scale(-gravity[1],wkv);
        dvadd(wkv,sigma_y); // sigma_y = Lt*(u_{,y}-avg_rho*g_y)
        dvmul(L_t->u,GF->u,wkv);
        scale(-gravity[2],wkv);
        dvadd(wkv,sigma_z); // sigma_z = Lt*(u_{,z}-avg_rho*g_z)
        wkv = -u_misc[0];
        dvadd(wkv,sigma_x); // sigma_x = Lt*(u_{,x}-avg_rho*g_x) - u_misc_x
        wkv = -u_misc[1];
        dvadd(wkv,sigma_y); // sigma_y = Lt*(u_{,y}-avg_rho*g_y) - u_misc_y
        wkv = -u_misc[2];
        dvadd(wkv,sigma_z); // sigma_y = Lt*(u_{,z}-avg_rho*g_z) - u_misc_z
        U->lift( F, sigma_x, 'x' );
        U->project(sigma_x);
        U->lift( F, sigma_y, 'y' );
        U->project(sigma_y);
        U->lift( F, sigma_z, 'z' );
        U->project(sigma_z);
        // sigma_x ("v_x") = - ( Lt*(u_{,x}-avg_rho*g_x) - u_misc_x )
        scale(-1.0,sigma_x);
        Vt[0]->el[e]->u = sigma_x;
        // sigma_y ("v_y") = - ( Lt*(u_{,y}-avg_rho*g_y) - u_misc_y )
        scale(-1.0,sigma_y);
        Vt[1]->el[e]->u = sigma_y;
        // sigma_z ("v_z") = - ( Lt*(u_{,z}-avg_rho*g_z) - u_misc_z )
        scale(-1.0,sigma_z);
        Vt[2]->el[e]->u = sigma_z;
      }
    }
//  }
  Vt.fill_sides();
  Vt.share_sides();
  Vt.fill_bc_sides();
}

//===========================================================================
//                            Initial Conditions
//===========================================================================

/// Set the initial condition
void Darcy::set_ic(vField &F, string ext) {
  t = 0.0; step = 0;
  string fname = root+ext;
  ifstream in(fname.c_str());
  if (not in.is_open()) {
    comm->cerr()<< "Darcy::set_ic: Could not open initial condition file "
                << fname << endl;
    comm->exit(DGM::FAILURE);
  }
  string buffer, code;
  getline(in,buffer);
  if (!(in>>code)) error("Cannot read IC code");
  getline(in,buffer);
  //comm->cout() << "IC code = " << code << endl;
  if (lowerCase(code) == "given") {
    F.fill(in);
  } else if (lowerCase(code) == "restart") {
    string rstfile;
    if (!(in>>rstfile)) {
      comm->cerr()<< "Cannot read restart file name from " << fname << endl;
      comm->exit(DGM::FAILURE);
    }
    read(rstfile,F);
    comm->cout() << "Restarting from: " << rstfile << endl;
  } else {
    comm->cout() << lowerCase(code) << endl;
    comm->error("Darcy::set_ic()  Unsupported IC type");
  }
  // determine whether to project the initial condition to the p-space
  if (myparams.get("projic")) {
    //comm->cout() << "  Note: Projecting IC to polynomial space" << endl;
    project( F );
  } else {
    comm->cout() << "  WARNING:  No projection of Initial condition" << endl;
    for (vField::size_type i=0; i<F.size(); i++)
      for (LocalSize e=0; e<ne; e++)
        F[i]->el[e]->state = Element::Physical;
  }
  if (myparams.get("projavg")) {                // project out the average
    project_out_avg( *Uv[0], F );
  }
}

/// Set the initial condition
void Darcy::set_given_field(vField &F, const string ext,
    const bool projic) const {
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
  //comm->cout() << "IC code = " << code << endl;
  if (lowerCase(code) == "given") {
    F.fill(in);
  } else {
    comm->error("Darcy::set_ic()  Unsupported IC type");
  }
  // determine whether to project the initial condition to the p-space
  if (projic) {
    //comm->cout() << "  Note: Projecting IC to polynomial space" << endl;
    project( F );
  } else {
    comm->cout() << "  WARNING:  No projection of Initial condition" << endl;
    for (vField::size_type i=0; i<F.size(); i++)
      for (LocalSize e=0; e<ne; e++)
        F[i]->el[e]->state = Element::Physical;
  }
}

/// project out the average
void Darcy::project_out_avg(Field &U, vField &F) const {
  Scalar measure;
  U.fill(one);
  Scalar average = Field::L2_inner_product( &U, F[0], &measure );
  average /= measure;
  if (measure==0) DGM::Comm::World->error("Zero measure Domain");
  DGM::Comm::World->cout() << "Domain measure = " << measure
      << ",  Field average = " << average << endl;
  U.zero();
  subtract( average, F[0] );
}

//===========================================================================
//                        BC database management
//===========================================================================
BC* Darcy::make_BC( ifstream &in, string &tag ) {
  // comm->cout() << "Darcy::make_BC(ifstream &in, string &tag)" << endl;
  string code;
  if (!(in >> code)) return NULL;
  code = lowerCase(code);
  if (code == "dirichlet") {
    if (!(in >> tag)) error("Darcy::make_BC() Cannot read Dirichlet tag");
    return new DirichletBC(tag,in);
  } else if (code == "dirichlet_function") {
    if (!(in >> tag))
      error("Darcy::make_BC() Cannot read DirichletBC_Function tag");
    return new DirichletBC_Function(tag,in,1);
  } else if (code == "unsteadydirichlet") {
    if (!(in >> tag))
      error("Darcy::make_BC() Cannot read UnsteadyDirichletBC tag");
    return new UnsteadyDirichletBC(tag,in);
  } else if (code == "neumann") {
    if (!(in >> tag)) error("Darcy::make_BC()  Cannot read Neumann tag");
    return new NeumannBC(tag,in);
  } else if (code == "neumann_function") {
    if (!(in >> tag))
      error("Darcy::make_BC() Cannot read NeumannBC_Function tag");
    return new NeumannBC_Function(tag,in,1);
  } else {
    if(comm->Master())
      comm->cerr()<<"WARNING Darcy::make_BC() Illegal BC type: "+code<<endl;
  }
  return NULL;
}

//===========================================================================
//                       Source database management
//===========================================================================

/// Construct source terms
Source::Ptr Darcy::make_Source( ifstream &in, string &tag ) {
  string code;
  Source::Ptr p;
  if (!(in >> code)) return p;
  while (code[0]=='#') {  // eat comment lines
    string buffer;
    getline(in,buffer);
    if (!(in >> code)) return p;
  }
  if (lowerCase(code) == "constant") {
    if (!(in >> tag)) error("Darcy::Cannot read ConstSource tag",1);;
    p.reset( new ConstSource(tag,in,U.size()) );
  } else if (lowerCase(code) == "file") {
    if (!(in >> tag)) error("Darcy::Cannot read FileSource tag",1);
    p.reset( new FileSource(tag,in,U) );
  } else if (lowerCase(code) == "function") {
    if (!(in >> tag)) error("Darcy::Cannot read FuncSource tag",1);
    p.reset( new FuncSource(tag,in,U.size()) );
  } else if (lowerCase(code) == "transientmanufactured") {
    if (!(in >> tag))
      error("Darcy::Cannot read TransientManufactured tag");
    p.reset( new TransientManufactured(tag, in) );
  } else {
    error("Darcy::make_Source() Illegal Source type",1);
  }
  return p;
}

/// Add source terms
void Darcy::add_source(const vField &Us, vField &Ur) {
  for (Source::db_citr i=Source_db.begin(); i!= Source_db.end(); ++i)
    i->second->apply( t, Us, Ur);
}

//===========================================================================
//                             Output Methods
//===========================================================================

/// Plot the solution
/** \warning Does not work in parallel for all data formats
    In particular, tecplot output will only be for the master rank. */
int Darcy::plot(const string &rst) {
  if (comm->NumProc() > 1) comm->error("Works only sequentially", DGM::FAILURE);
  read( rst, U );
  const string rootname(rst.substr(0,rst.find(".rst")));
  ostringstream caption;
  caption << " at t = " << scientific << t << ", step = " << step;
  if (comm->Master()) U.tecplot(rootname+".dat","Pressure"+caption.str());
  if (myparams.get("paraview") ) U.paraview(rootname,"Pressure"+caption.str());
  if (myparams.get("plot3d")) {
    if (params.get("plot3d_x")) {
      if (comm->Master()) U.plot3d_x(rootname+".xyz");
    }
    if (params.get("plot3d_q")) {
      if (comm->Master()) U.plot3d_q(rootname+".q");
    }
  }
//  if (params.get("auxtec")) {
//    comm->error("Auxiliary output not currently supported");
//  }
  return 0;
}

//===========================================================================
//                   Initialize the Medium Parameters
//===========================================================================

/// Set the medium for Darcy which includes the gravity factors (chi) and
/// relative mobilities
void Darcy::set_medium(vField &Kabs, const string ext) const {
  Kabs.zero();
  const string fname = root+ext;
  comm->cout()<<"Darcy::set_medium(): Initializing Kabs from " << fname << endl;
  ifstream in(fname.c_str());
  if (not in.is_open()) comm->error("Could not open medium "+fname);
  string buffer, code;
  getline(in,buffer);
  if (!(in>>code)) comm->error("Cannot read medium code");
  getline(in,buffer);
  if (lowerCase(code) == "given") {
    Kabs.fill(in);
  } else if (lowerCase(code) == "2d-n-stripes-permeabilities") {
    string fname;
    LocalSize qtot;
    int nx, ny, nstripes;
    Scalar Lx_min, Lx_max, Ly_min, Ly_max;
    vector<Scalar> kabs;
    if (!(in>>fname>>nstripes>>nx>>ny>>Lx_min>>Lx_max>>Ly_min>>Ly_max))
      comm->error("Cannot read 2d-n-stripes filename and parameters");
    //Scalar dx = (Lx_max-Lx_min)/Scalar(nx);
    //Scalar dy = (Ly_max-Ly_min)/Scalar(ny);
    kabs.resize(nstripes);
    ifstream eth(fname.c_str());
    for (int istripe=0; istripe<nstripes; istripe++) {
      if (!(eth>>kabs[istripe]))
        comm->error("Error reading data in Medium filename "+fname);
    }
    for (LocalSize n=0; n<nsd; n++) {
      Scalar epsx = 1.0e-3;   // force sample points on element interiors
      //Scalar epsy = 1.0e-3; // force sample points on element interiors
      Scalar x, x_c, y_c;
      for (LocalSize e=0; e<Kabs[n]->ne; e++) {
        qtot = Kabs[n]->el[e]->qtot;
        x_c = y_c = 0.0;
        for (LocalSize q=0; q<qtot; q++) {
          x_c += Kabs[n]->el[e]->C->x[q];
          y_c += Kabs[n]->el[e]->C->y[q];
        }
        x_c /= Scalar(qtot);
        y_c /= Scalar(qtot);
        for (LocalSize q=0; q<Kabs[n]->el[e]->qtot; q++) {
          x = Kabs[n]->el[e]->C->x[q];
          //Scalar y = Kabs[n]->el[e]->C->y[q];
          Scalar xe = (1.0-epsx)*x+epsx*x_c;
          //Scalar ye = (1.0-epsy)*y+epsy*y_c;
          for (int istripe=0; istripe<nstripes; istripe++) {
            if ((xe>(Lx_min+Scalar(istripe  )/Scalar(nstripes)*
                (Lx_max-Lx_min))) &&
                (xe<(Lx_min+Scalar(istripe+1)/Scalar(nstripes)*
                    (Lx_max-Lx_min)))    )
              Kabs[n]->el[e]->u[q] = kabs[istripe];
          }
        }
        Kabs[n]->el[e]->state = Element::Physical;
      }
    }
  } else if (lowerCase(code) == "2d-4-spot-permeabilities") {
    int nx, ny;
    LocalSize qtot;
    Scalar Lx_min, Lx_max, Ly_min, Ly_max;
    dVector kabs(4);
    //bool constant;
    if (!(in>>nx>>ny>>Lx_min>>Lx_max>>Ly_min>>Ly_max>>kabs[0]>>kabs[1]>>
          kabs[2]>>kabs[3]))
      comm->error("Cannot read 2d-4-spot-permeability parameters");
    //Scalar dx = (Lx_max-Lx_min)/Scalar(nx);
    //Scalar dy = (Ly_max-Ly_min)/Scalar(ny);
    for (LocalSize n=0; n<nsd; n++) {
      Scalar epsx = 1.0e-3; // force sample points on element interiors
      Scalar epsy = 1.0e-3; // force sample points on element interiors
      Scalar x, y, x_c, y_c;
      for (LocalSize e=0; e<Kabs[n]->ne; e++) {
        qtot = Kabs[n]->el[e]->qtot;
        x_c = y_c = 0.0;
        for (LocalSize q=0; q<qtot; q++) {
          x_c += Kabs[n]->el[e]->C->x[q];
          y_c += Kabs[n]->el[e]->C->y[q];
        }
        x_c /= Scalar(qtot);
        y_c /= Scalar(qtot);
        for (LocalSize q=0; q<Kabs[n]->el[e]->qtot; q++) {
          x = Kabs[n]->el[e]->C->x[q];
          y = Kabs[n]->el[e]->C->y[q];
          Scalar xe = (1.0-epsx)*x+epsx*x_c;
          Scalar ye = (1.0-epsy)*y+epsy*y_c;
          if ((xe<(Lx_max+Lx_min)/2.0) && (ye<(Ly_max+Ly_min)/2.0))
            Kabs[n]->el[e]->u[q] = kabs[0];
          else if ((xe>(Lx_max+Lx_min)/2.0) && (ye<(Ly_max+Ly_min)/2.0))
            Kabs[n]->el[e]->u[q] = kabs[1];
          else if ((xe<(Lx_max+Lx_min)/2.0) && (ye>(Ly_max+Ly_min)/2.0))
            Kabs[n]->el[e]->u[q] = kabs[2];
          else
            Kabs[n]->el[e]->u[q] = kabs[3];
        }
        Kabs[n]->el[e]->state = Element::Physical;
      }
    }
  } else if (lowerCase(code) == "fluctuation") {
    // randomize kabs assuming a constant kabs per element
    Scalar mean, fluctuation;
    if (!(in>>mean>>fluctuation))
      comm->error("Cannot read fluctuation");
    for (LocalSize n=0; n<nsd; n++) {
#ifdef REO_DARCY_USE_RAND
      srand(2012);
#else
      srandom(2012);
#endif
      for (LocalSize e=0; e<Kabs[n]->ne; e++) {
#ifdef REO_DARCY_USE_RAND
        const Scalar maxrand = RAND_MAX;
        const Scalar numrand(rand());
        const Scalar fluct = numrand/maxrand - 0.5; // range: [-1,1]
#else
        // random number between [-1,1]
        const Scalar a = -1.0;
        const Scalar b =  1.0;
        const Scalar r = ((Scalar)::random()/((Scalar)(RAND_MAX)+(Scalar)(1)));
        const Scalar fluct = (b-a)*r+a;
#endif
        const Scalar variance = mean * fluctuation* fluct;
        for (LocalSize q=0; q<Kabs[n]->el[e]->qtot; q++) {
          Kabs[n]->el[e]->u[q] = mean + variance;
        }
        Kabs[n]->el[e]->state = Element::Physical;
      }
    }
  } else if (lowerCase(code) == "randomizedfourier") {
    // randomize kabs assuming a constant kabs per element
    Scalar mean, fluctuation;
    int nModes;
    if (!(in>>mean>>fluctuation>>nModes))
      comm->error("Cannot read fluctuation");
    for (LocalSize n=0; n<nsd; n++) {
      for (LocalSize e=0; e<Kabs[n]->ne; e++) {
        for (LocalSize q=0; q<Kabs[n]->el[e]->qtot; q++) {
          const Scalar x = Kabs[n]->el[e]->C->x[q];
          const Scalar y = Kabs[n]->el[e]->C->y[q];
          Kabs[n]->el[e]->u[q] = mean*(1.0 + fluct(x, y, nModes, fluctuation));
        }
        Kabs[n]->el[e]->state = Element::Physical;
      }
    }
  } else {
    comm->error("Darcy::set_medium() Unsupported type");
  }

  string fnameasc = root+".asc";
  ifstream asc(fnameasc.c_str());
  if (asc.is_open()) {
    comm->cout() << "Modifying Kabs..." << endl;
    int numele, nsddummy;
    if (!(asc>>numele>>nsddummy))
      comm->error("Cannot read first line");
    for (int ei = 0; ei < numele; ei++) {
      int geid, block;
      if (!(asc>>geid>>block))
        comm->error("Cannot read element line");
      if (partition->owns(geid)) {             // only work on local elements
        for (LocalSize n=0; n<nsd; n++) {
          const LocalSize leid = partition->inc(geid);
          Kabs[n]->el[leid]->u *= 1.0/block;
        }
      }
    }
  }
}

} // namespace Reo
