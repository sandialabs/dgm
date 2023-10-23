/*=============================================================================
  Module:     Helmholtz Solver

  Authors:    S. Scott Collis
              Axel Gerstenberger (IP matrix formulation)

  Copyright:  (c)2010 Sandia National Laboratories
=============================================================================*/

/** \file Helmholtz.cpp
    \brief Basic Helmholtz equation module implementation
    \author S. Scott Collis and Axel Gerstenberger
    \copyright (c)2010 Sandia National Laboratories
*/

// system includes
#include <sstream>

// bost includes
#include <boost/array.hpp>

// Reo includes
#include "Reo.hpp"
#include "Helmholtz.hpp"
#include "HelmholtzBC.hpp"

// DGM includes
#include "Operator.hpp"
#include "Assembler.hpp"
#include "Utilities.hpp"

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

namespace DGM {

namespace Matrix {

#ifdef DGM_USE_EPETRA
/// Field number for the real component of the solution
template<> struct FieldNum<ur> {static const std::size_t pos = 0;};
/// Field number for the imaginary component of the solution
template<> struct FieldNum<ui> {static const std::size_t pos = 1;};
#endif

} // Matrix

} // DGM

namespace Reo {

using namespace DGM;

/// Constructor
Helmholtz::Helmholtz( DGM::ArgList &args, const DGM::Comm::Ptr comm_ ) :
  Domain(args, comm_), restart(false), do_solve(true),
  Sffile(comm_), Omega(comm_) 
{
  comm->cout()<<"Building Helmholtz..."<<endl;

  // initialize output parameters
  input("auxtec",       0);      // Compute derivative quantities
  input("plot3d_x",     1);      // plot3d grid file
  input("plot3d_q",     1);      // plot3d mesh file
  input("ghosting",     0);      // test the ghosting framework

  // initialize solver parameters
  input("matrix_solve", true);   // solve with matrix, otherwise, matrix free
  input("solver",       0);      // default is direct solve (Amesos_KLU)
  input("matrix_out",   false);  // dump (and build) matrices
  input("iterations",   1000);   // max number of GMRES iterations
  input("tolerance",    1e-12);  // tolerance for the GMERS solver
  input("kspace",       500);    // dimension of Krylov space for GMRES solver

  // read arguments (overrides defaults and input file)
  parse_args( args );

  // initialize parameters
  const int p = params.get("p"); // polynomial order
  comm->cout() << "  Helmholtz: p = " << p << endl;
  const int q = p + 2;           // number of quadrature points
  comm->cout() << "  Helmholtz: q = " << q << endl;
  nsd = params.get("nsd");       // number of space dimensions

  vector<string> field_names;    // Field names
  field_names.push_back("ur");
  field_names.push_back("ui");

  // build a Field of Elements and Sides
  if (params.get("imesh")) {
    Mesh mesh(params);
    U.push_back( new Field(p, q, mesh, root, field_names[0],
                           Field::FULL, comm ) );
    partition = U[0]->partition;
  } else if (params.get("bmesh")) {
    U.push_back( new Field(p, q, root, field_names[0], partition, 1,
                           Reo::NumEqntype, p2i(HELMHOLTZ), comm ) );
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
  Sffile.set_name("Sffile");
  for (LocalSize i=0; i<NfieldsT; i++) {
    Sffile.push_back( new Field( U[i], root, field_names[i] ) );
  }
  Sffile.reset_storage();

  // build the Omega vField
  Omega.set_name("Omega");
  Omega.push_back( new Field(U[0], root, "Omega") );
  Omega.reset_storage();

  set_medium(Omega, is_sponge_element);

  // allocate workspace
  wk1.resize(5*max(Lmax(),Qmax()));
  wk2.resize(5*max(Lmax(),Qmax()));
  wk3.resize(5*max(Lmax(),Qmax()));

  // make sure that storage is initialized
  zero_all_fields();

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
}

/// Parse parameters from the argument list
void Helmholtz::parse_args( DGM::ArgList &args ) {
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
      } else if (name == "-ghosting") {
        li.push_back(a);
        params["ghosting"] = 1;
      } else if (name == "-solver") {
        li.push_back(a);
        value = *(++a);
        li.push_back(a);
        params["solver"] = atoi(value.c_str());
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

/// Show usage for solver
void Helmholtz::showUsage() {
  comm->cout()
    << "Helmholtz Class Options \n"
    << "----------------------------------------------------------------\n"
    << "-nox     " << '\t' << "No grid file                             \n"
    << "-noq     " << '\t' << "No solution file                         \n"
    << "-aux     " << '\t' << "Auxiliary Tecplot file                   \n"
    << "-solver  " << '\t' << "Specify the solver type                  \n"
    << "----------------------------------------------------------------\n";
}

/// Zero all fields
void Helmholtz::zero_all_fields() {
  Domain::zero_all_fields();
}

//===========================================================================
//                             Solve Methods
//===========================================================================

/// Evaluate the action of the operator on a solution vector
void Helmholtz::action( vField &Us, vField &Uf ) {
  residual(Us, Uf);
  axpy(one, Ut, Uf, Uf);
}

/// Computes the complete DG residual
void Helmholtz::residual( vField &Us, vField &Uf ) {
  //comm->cout() << "Helmholtz::residual() is not yet correct..." << endl;
  Us.fill_sides();
  Us.share_sides();
  enforce_bc(Us);
  average_flux( Us, Uf, '+' );
  for (vField::size_type i=0; i<Us.size(); ++i) {
    for (LocalSize e=0; e<Us[i]->ne; ++e) {
      Element *U = Us[i]->el[e];
      Element *F = Uf[i]->el[e];
      Element *O = Omega[0]->el[e];
      const Ordinal qtot = U->qtot;
      dVector ux(wk1,qtot);
      dVector uy(wk2,qtot);
      U->gradient(U->u, ux, uy);
      U->lift( F, ux, 'x' );
      U->project(ux);
      U->lift( F, uy, 'y' );
      U->project(uy);
      U->fill_sides( ux, uy );                // normal flux on sides
      U->gradient(ux, ux, 'x');               // ux = u_{,xx}
      U->gradient(uy, uy, 'y');               // uy = u_{,yy}
      dvadd( ux, uy, F->u );                  // F->u = u_{,xx} + u_{,yy}
      dVector omegasq(wk1, O->qtot);
      omegasq = O->u;
      omegasq *= omegasq;                     // \omega^2
      dVector utmp(wk2, O->qtot);
      utmp = U->u;
      utmp *= omegasq;                        // u \omega^2
      F->u += utmp;                           // u_{,xx} + u_{,yy} + \omega^2 u
    }
  }
  Us.share_sides();
  enforce_flux_bc(Us);
  average_flux( Us, Uf, '-' );
  for (vField::size_type i=0; i<Us.size(); ++i) {
    for (LocalSize e=0; e<Us[i]->ne; ++e) {
      Element *U = Us[i]->el[e];
      Element *F = Uf[i]->el[e];
      U->lift( F, F->u );
    }
  }
  add_source( Us, Uf );
  project( Uf );
  Uf.forward_transform();
}

Scalar Helmholtz::computeC11(const Side * const Us_loc,
                            const Side * const Us_adj) const {
  const Scalar h_n = 0.5*(1.0/Us_loc->h_n_inv() + 1.0/Us_adj->h_n_inv());
  const Scalar pmax = max(Us_loc->elink->pOrder(), Us_adj->elink->pOrder());
  const Scalar C11 = stab*pmax*pmax/h_n;
  return C11;
}

#ifdef DGM_USE_EPETRA

/// Computes the BC side contribution to the matrix and righthand-side
void Helmholtz::Matrix_sides_bndry(
    const vField &Uf,
    Epetra_CrsMatrix &A
) const {

  using namespace Matrix;

  std::set<string> Dirichlet;

  // Hack alarm: this should be implemented in the various BC classes-> no
  // casts
  for (BC::db_citr i=BC_db.begin(); i!= BC_db.end(); ++i) {
    const BC *const bc = &*(i->second);
    if (dynamic_cast<Reo::Helmholtz::DirichletBC const*const>(bc)!=NULL) {
      Dirichlet.insert(bc->type);
    }
  }

  Matrix::MatrixSideAssembler<NfieldsT> assembler(Uf, false);

  for (LocalSize n=0; n<Uf[0]->nbc; ++n) {
    boost::array<Side*, NfieldsT> Us_loc;
    Us_loc[FieldNum<ur>::pos] = Uf[FieldNum<ur>::pos]->bc[n]->S;
    Us_loc[FieldNum<ui>::pos] = Uf[FieldNum<ui>::pos]->bc[n]->S;

    assembler.setup(this, Us_loc);

    const string type0 = Uf[FieldNum<ur>::pos]->bc[n]->type;
    if (Dirichlet.find(type0) != Dirichlet.end() ) {
      // - ( v , nabla u * n )_G_Dirichlet
      assembler.locloc<ur, d0, ur, dn>( -1.0 );
      assembler.locloc<ui, d0, ui, dn>( 1.0 );
      // - ( nabla v * n , u )_G_Dirichlet
      assembler.locloc<ur, dn, ur, d0>( -1.0 );
      assembler.locloc<ui, dn, ui, d0>( 1.0 );
      // + ( v , C11 u )_G_Dirichlet
      const Scalar C11 = computeC11(Us_loc[FieldNum<ur>::pos],
                                    Us_loc[FieldNum<ur>::pos]);
      assembler.locloc<ur, d0, ur, d0>( C11 );
      assembler.locloc<ui, d0, ui, d0>( -C11 );
    }

    // scatter the local matrix to global
    assembler.scatter(Uf, A);

  } // loop over boundary sides
}

/// Computes the BC side contribution to the matrix and righthand-side
void Helmholtz::RHS_sides_bndry(
    const vField &Uf,
    const vField &Ff,
    Epetra_Vector &b
    ) const {
}

/// Computes the side contribution to the matrix and righthand-side
void Helmholtz::Matrix_sides_interior(
    const vField &Uf,
    Epetra_CrsMatrix &A ) const {

  using namespace Matrix;

  Matrix::MatrixSideAssembler<NfieldsT> assembler(Uf, true);

  for (LocalSize e=0; e<Uf[0]->ne; e++) {
    // localize elements
    boost::array<Element*, NfieldsT> Ue;
    Ue[0] = Uf[0]->el[e];
    Ue[1] = Uf[1]->el[e];
    // terms from the sides
    for (Ordinal i=0; i<Ue[0]->nSides(); i++) {
      boost::array<Side*, NfieldsT> Us_loc;
      Us_loc[0] = Ue[0]->side[i];
      Us_loc[1] = Ue[1]->side[i];
      boost::array<Side*, NfieldsT> Us_adj = select_adj<2>(Us_loc);

      if (Us_loc[0]->is_bc() == true) {
        continue;
      } else {
        assembler.setup(this, Us_loc, Us_adj);

        // - ( [v] , {nabla u * n} )_G_i
        assembler.locloc<ur, d0, ur, dn>( -0.5 );
        assembler.locadj<ur, d0, ur, dn>(  0.5 );
        assembler.locloc<ui, d0, ui, dn>(  0.5 );
        assembler.locadj<ui, d0, ui, dn>( -0.5 );

        // - ( {nabla v * n} , [u] )_G_i
        assembler.locloc<ur, dn, ur, d0>( -0.5 );
        assembler.locadj<ur, dn, ur, d0>(  0.5 );
        assembler.locloc<ui, dn, ui, d0>(  0.5 );
        assembler.locadj<ui, dn, ui, d0>( -0.5 );

        // + ( [v] , C11 [u] )_G_i
        const Scalar C11 = computeC11(Us_loc[0], Us_adj[0]);
        assembler.locloc<ur, d0, ur, d0>(  C11*0.5 );
        assembler.locadj<ur, d0, ur, d0>( -C11*0.5 );
        assembler.locloc<ui, d0, ui, d0>( -C11*0.5 );
        assembler.locadj<ui, d0, ui, d0>(  C11*0.5 );

        // scatter the local matrix to global
        assembler.scatter(Uf, A);
      }
    } // loop over sides
  } // loop over elements
}


/// Computes the side contribution to righthand-side
void Helmholtz::RHS_sides_interior(
    const vField &Uf,
    Epetra_Vector &b) const {
}

/// Computes the domain integrals
void Helmholtz::Matrix_domain_integrals(
    const vField &Uf,
    Epetra_CrsMatrix &A
    ) const {
  using namespace Matrix;

  Matrix::MatrixDomainAssembler<NfieldsT> assembler(Uf);

  for (LocalSize e=0; e<Uf[0]->ne; e++) {
    boost::array<Element*, NfieldsT> e_loc;
    e_loc[0] = Uf[0]->el[e];
    e_loc[1] = Uf[1]->el[e];

    assembler.setup(e_loc);

    // + ( nabla v , nabla u )_Omega
    if (nsd >= 1) assembler.locloc<ur, dx, ur, dx>( 1.0 );
    if (nsd >= 2) assembler.locloc<ur, dy, ur, dy>( 1.0 );
    if (nsd >= 3) assembler.locloc<ur, dz, ur, dz>( 1.0 );
    if (nsd >= 1) assembler.locloc<ui, dx, ui, dx>( -1.0 );
    if (nsd >= 2) assembler.locloc<ui, dy, ui, dy>( -1.0 );
    if (nsd >= 3) assembler.locloc<ui, dz, ui, dz>( -1.0 );

    // omega^2
    dVector omegasq(wk1, Omega[0]->el[e]->qtot);
    omegasq = Omega[0]->el[e]->u;
    omegasq *= omegasq;

    // - ( v , omega^2 u )_Omega
    omegasq *= -1.0;
    assembler.locloc<ur, d0, ur, d0>( omegasq );
    omegasq *= -1.0;
    assembler.locloc<ui, d0, ui, d0>( omegasq );

#ifndef REO_HELMHOLTZ_NO_SPONGE
    // Add in a sponge term if active
    if (sponge.get()!=0 || !is_sponge_element.empty()) {
      // tau is the sponge value
      dVector tau(e_loc[0]->qtot, 0.0);
      if (sponge.get() != 0) {
        sponge->compute_reaction_coeff(e_loc, tau);
      } else {
        std::map<int,Scalar>::const_iterator
        entry = is_sponge_element.find(e_loc[0]->gid());
        if (entry->second > 0.0) {
          const int qtot = e_loc[0]->qtot;
          for (int q=0; q<qtot; q++) {
            tau[q] = entry->second;
          }
        }
      }
      // omega^2 * tau
      dVector fac(e_loc[0]->qtot, 0.0);
      for (Ordinal q=0; q < e_loc[0]->qtot; q++) {
        fac[q] = omegasq[q]*tau[q];
      }
      // + ( v , i omega^2 * tau u )_Omega
      assembler.locloc<ur, d0, ui, d0>( fac );
      assembler.locloc<ui, d0, ur, d0>( fac );
    }
#endif

    // scatter local to global
    assembler.scatter(Uf, A);

  } // end of loop over elements
}

/// element interior contributions to the RHS
void Helmholtz::RHS_domain_integrals(
    const vField &Uf,
    Epetra_Vector &b
) const {

  using namespace Matrix;

  Matrix::VectorDomainAssembler<NfieldsT> assembler(Uf);

  for (LocalSize e=0; e<Uf[0]->ne; e++) {
    boost::array<Element*, NfieldsT> e_loc;
    e_loc[0] = Uf[0]->el[e];
    e_loc[1] = Uf[1]->el[e];

    assembler.setup(e_loc);

    // + ( v , f_source_file )_Omega
    assembler.loc<ur, d0>( Sffile[FieldNum<ur>::pos]->el[e]->u );
    assembler.loc<ui, d0>( Sffile[FieldNum<ui>::pos]->el[e]->u );

    // scatter local to global
    assembler.scatter(Uf, b);

  } // end of loop over elements
}

/// Computes the matrix for the Helmholtz equation
/** Modes (in 2d) are ordered like:
    N0 = 1/2
    N1 = sqrt(3)/2 y
    N2 = sqrt(3)/2 x
    N3 = 3/2 xy
    N4 = ...
*/
void Helmholtz::buildMatrix(Epetra_CrsMatrix &A) const {
  //static FunctionTimer timer(__PRETTY_FUNCTION__);
  //FunctionSentry sentry(timer);
  Matrix_sides_interior( U, A );
  Matrix_sides_bndry( U, A );
  Matrix_domain_integrals( U, A );
  const int fillStatus = A.FillComplete();
  if (fillStatus != 0) throw DGM::exception("Error in FillComplete");
}

/// Computes the right hand-side for the Helmholtz equation
/** Modes (in 2d) are ordered like:
    N0 = 1/2
    N1 = sqrt(3)/2 y
    N2 = sqrt(3)/2 x
    N3 = 3/2 xy
    N4 = ...
*/
void Helmholtz::buildRHS( Epetra_Vector &b ) const {
  //static FunctionTimer timer(__PRETTY_FUNCTION__);
  //FunctionSentry sentry(timer);
  b.PutScalar(0.0);
  // right hand side b
  RHS_sides_interior( U, b );
  RHS_sides_bndry( U, Ut, b );
  RHS_domain_integrals( U, b );
}

#endif

/// Supplies a steady-state solve method to override Domain::solve()
int Helmholtz::solve() {
  if (do_solve) {
    comm->cout() << "Helmholtz::solve(): " << std::endl;
  } else {
    comm->cout() << "Helmholtz::solve(): skipping!" << std::endl;
    return 0;
  }

#ifdef DGM_USE_EPETRA

  const bool rebuild = (A == Teuchos::null);

  const bool matrix_solve = params.get("matrix_solve");
  if (matrix_solve == true) {

    comm->cout() << "Using Matrix formulation" << endl;

    // ghost elements and DOF layout
    U.ghost(root, 1);
    Ut.ghost();
    Omega.ghost();

    U.share_ghost_element_data();
    Omega.share_ghost_element_data();

    if ((bool)params.get("ghosting") == true) {
      return 0;
    }

    // data on sides and boundaries and parallel communication
    U.zero();
    U.share_ghost_element_data();
    U.fill_sides();
    U.fill_sides_of_ghost_elements();

    // prepare source and boundary data
    Sffile.zero();
    add_source( U, Sffile );
#ifndef DGM_PARALLEL
    if (params.get("tecplot"))
      Sffile.tecplot("Sffile.dat","Helmholtz source");
#endif

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
    if ((int)params.get("solver") >= 0) {
      buildRHS(*b);
      if ( rebuild ) {
        const int n = A->Map().NumGlobalElements();
        comm->cout() << "  build A("<<n<<"x"<<n<<")" << std::endl;
        buildMatrix(*A);
      }
    }
#ifdef REO_HELMHOLTZ_DEBUG
    Scalar norm2;
    b->Norm2(&norm2);
    comm->cout() << "  b norm2 = " << norm2 << endl;
    comm->cout() << "  A->NormInf() = " << A->NormInf() << endl;
    comm->cout() << "  A->NormFrobenius() = " << A->NormFrobenius() << endl;
#endif
    if (params.get("matrix_out")) {
      comm->cout() << "  output A & b" << std::endl;
      EpetraExt::OperatorToMatlabFile((root+"_dump_A.dat").c_str(),*A);
      EpetraExt::VectorToMatlabFile((root+"_dump_b.dat").c_str(),*b);
    }

    U.forward_transform();
    U.pack(*x); // <-- put initial guess into Epetra vector
    //U.pack();

    if ((int)params.get("solver") == solve_direct) {
      direct_solve( rebuild );
    } else if ((int)params.get("solver") == solve_iterative){
      Teuchos::ParameterList solparams;
      int kspace = params.get("kspace");
      solparams.set("kspace", kspace);
      int iterations = params.get("iterations");
      solparams.set("iterations", iterations);
      Scalar tolerance = params.get("tolerance");
      solparams.set("tolerance", tolerance);
      iterative_solve( solparams, rebuild );
    } else {
      comm->cout() << "No attempt to solve the linear system per user request"
                   << endl;
    }

    // extract the solution
    U.unpack(*x);

  } else {

    comm->cout() << "Matrix-free formulation" << std::endl;

    // evaluate the residual and store in Ut
    U.zero();
    residual(U,Ut);  // compute r(0) (make sure U = 0)
    scale(-one,Ut);  // compute -r(0)
    Ut.pack();
    b = Teuchos::rcp(new Epetra_Vector( *Ut.modal_vec ));
    Ut.unpack();

    U.forward_transform();
    U.pack();

    Operator op( this, U.eComm.get(), U.modal_map.get() );

    if ((int)params.get("solver") == 1) {
      lp = Teuchos::rcp(new Epetra_LinearProblem(
          &op, U.modal_vec.get(), b.get()));
      Teuchos::ParameterList solparams;
      int kspace = params.get("kspace");
      solparams.set("kspace", kspace);
      int iterations = params.get("iterations");
      solparams.set("iterations", iterations);
      Scalar tolerance = params.get("tolerance");
      solparams.set("tolerance", tolerance);
      iterative_solve_matrixfree( solparams, rebuild );
    } else {  // Use matrix-free approach with AztecOO to solve
      Epetra_CrsMatrix *A_ = GenerateMatrixViaMatlabOutput(op);
      // comm->cout() << "Finished Epetra CRS matrix" << endl;
      lp = Teuchos::rcp(new Epetra_LinearProblem(A_, U.modal_vec.get(),
                                                 b.get()));
      direct_solve( true );
      delete A_;
    }

    // transform Ut back to physical space
    Ut.backward_transform();

    // extract solution
    U.unpack();
  }

  U.backward_transform();

  U.norm();

  if (!restart) {
    write(root+".rst",U);
#ifndef DGM_PARALLEL
    if (params.get("tecplot"))
      U.tecplot("out.dat","Helmholtz solution");
#endif
  }

  if (step%Ntout==0) {
    write(step, U);
  }

#else  // !DGM_USE_EPETRA

  comm->error("Helmholtz::solve() must be built with Trilinos");

#endif // DGM_USE_EPETRA

  return 0;
}

//===========================================================================
//                            Initial Conditions
//===========================================================================

/// Set the initial condition
void Helmholtz::set_ic(vField &F, string ext) {
  t = 0.0; step = 0;
  string fname = root+ext;
  ifstream in(fname.c_str());
  if (not in.is_open()) {
    comm->cerr()<< "Helmholtz::set_ic: Could not open initial condition file "
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
      comm->cerr() << "Cannot read restart file name from " << fname << endl;
      comm->exit(DGM::FAILURE);
    }
    read(rstfile, F);
    comm->cout() << "Restarting from: " << rstfile << endl;
  } else {
    comm->cout() << lowerCase(code) << endl;
    comm->error("Helmholtz::set_ic()  Unsupported IC type");
  }
#ifdef DGM_NO_PROJECT_IC
  comm->cout() << "WARNING:  No projection of Initial condition" << endl;
  for (LocalSize i=0; i<F.size(); i++)
    for (LocalSize e=0; e<ne; e++)
      F[i]->el[e]->state = Element::Physical;
#else
  project( F );
#endif
}

//===========================================================================
//                        BC database management
//===========================================================================

// Load up the available BC types
void Helmholtz::setup_BCdb( ) {
  // comm->cout() << "Helmholtz::setup_BCdb()" << endl;

  // set default BC types
  dVector ub(2);
  ub[0] = 1.0;
  ub[1] = 0.0;
  BC_db["S"].reset( new StateBC("S", ub) );

  // read new BC types from file
  string fname = root+".bct";
  ifstream in(fname.c_str());
  if (in.is_open()) read_BCdb( in );   // database of active BC types
}

BC* Helmholtz::make_BC( ifstream &in, string &tag ) {
  // comm->cout() << "Helmholtz::make_BC(ifstream &in, string &tag)" << endl;
  string code;
  if (!(in >> code)) return NULL;
  code = lowerCase(code);

  if (code == "dirichlet") {
    if (!(in >> tag)) error("Helmholtz::make_BC() Cannot read Dirichlet tag");
    return new DirichletBC(tag,in);
  } else if (code == "state") {
    if (!(in >> tag)) error("Helmholtz::make_BC: Cannot read State tag",1);
    return new StateBC(tag,in,4);
  } else {
    if(comm->Master())
      comm->cerr()<<"WARNING Helmholtz::make_BC() Illegal BC type: "+code<<endl;
  }
  return NULL;
}

//===========================================================================
//                       Source database management
//===========================================================================

/// Construct source terms
Source::Ptr Helmholtz::make_Source( ifstream &in, string &tag ) {
  string code;
  Source::Ptr p;
  if (!(in >> code)) return p;
  while (code[0]=='#') {  // eat comment lines
    string buffer;
    getline(in,buffer);
    if (!(in >> code)) return p;
  }
  if (lowerCase(code) == "constant") {
    if (!(in >> tag)) error("Helmholtz::Cannot read ConstSource tag",1);;
    p.reset( new ConstSource(tag,in,1) );
  } else if (lowerCase(code) == "file") {
    if (!(in >> tag)) error("Helmholtz::Cannot read FileSource tag",1);
    p.reset( new FileSource(tag,in,U) );
  } else if (lowerCase(code) == "function") {
    if (!(in >> tag)) error("Helmholtz::Cannot read FuncSource tag",1);
    p.reset( new FuncSource(tag,in,U.size()) );
  } else if (lowerCase(code) == "gaussian") {
    if (!(in >> tag)) error("Helmholtz::Cannot read GaussianSource tag",1);
    p.reset( new GaussianSource(tag,in,U.nsd()) );
  } else if (lowerCase(code) == "sponge") {
    if (!(in >> tag)) error("Helmholtz::Cannot read SpongeSource tag",1);
    const bool matrix_solve = params.get("matrix_solve");
    if (matrix_solve == true) {
      comm->cout() << "make_Source: Sponge is used a reaction term "
                   << "(matrix approach)" << endl;
      sponge.reset( new Sponge(tag,in,U.nsd()) );
    } else {
      comm->cout() << "make_Source: Sponge is used a source term "
                   << "(matrix free approach)" << endl;
      p.reset( new Sponge(tag,in,U.nsd()) );
    }
  } else {
    error("Helmholtz::make_Source() Illegal Source type",1);
  }
  return p;
}

/// Add source terms
void Helmholtz::add_source(const vField &Us, vField &Ur) {
  for (Source::db_citr i=Source_db.begin(); i!= Source_db.end(); ++i)
    i->second->apply( t, Us, Ur);
}

//===========================================================================
//                             Output Methods
//===========================================================================

/// Plot the solution
/** \warning Does not work in parallel for all data formats
    In particular, tecplot output will only be for the master rank. */
int Helmholtz::plot(const string &rst) {
  read( rst, U );
  const string rootname(rst.substr(0,rst.find(".rst")));
  ostringstream caption;
  caption << " at t = " << scientific << t << ", step = " << step;
  if (comm->Master())
    U.tecplot(rootname+".dat","State variables"+caption.str());
  if (params.get("paraview") ) U.paraview(rootname,caption.str());
  if (params.get("plot3d")) {
    if (params.get("plot3d_x")) U.plot3d_x(rootname+".xyz");
    if (params.get("plot3d_q")) U.plot3d_q(rootname+".q");
  }
  if (params.get("auxtec")) {
    comm->error("Auxiliary output not currently supported");
  }
  return 0;
}

//===========================================================================
//                   Initialize the Medium Parameters
//===========================================================================

/// Set the medium for Helmholtz
void Helmholtz::set_medium(
    vField &Omega,
    std::map<int,Scalar> &is_sponge_element
    ) const {
  Omega.zero();
  const string fname = root+".omega";
  comm->cout()<<"Helmholtz::set_medium(): Initializing Omega from "
              << fname << endl;
  ifstream in(fname.c_str());
  if (not in.is_open()) comm->error("Could not open medium "+fname);
  string buffer, code;
  getline(in,buffer);
  if (!(in>>code)) comm->error("Cannot read medium code");
  getline(in,buffer);
  if (lowerCase(code) == "given") {
    Omega.fill(in);
  } else if (lowerCase(code) == "randomizedfourier") {
    // randomize kabs assuming a constant kabs per element
    Scalar mean, fluctuation;
    int nModes;
    if (!(in>>mean>>fluctuation>>nModes))
      comm->error("Cannot read fluctuation");
    for (LocalSize e=0; e<Omega[0]->ne; e++) {
      for (LocalSize q=0; q<Omega[0]->el[e]->qtot; q++) {
        const Scalar x = Omega[0]->el[e]->C->x[q];
        const Scalar y = Omega[0]->el[e]->C->y[q];
        Omega[0]->el[e]->u[q] = mean*(1.0 + fluct(x, y, nModes, fluctuation));
      }
      Omega[0]->el[e]->state = Element::Physical;
    }
  } else {
    comm->error("Darcy::set_medium() Unsupported type");
  }

  is_sponge_element.clear();
  string fnameasc = root+".asc";
  ifstream asc(fnameasc.c_str());
  if (asc.is_open()) {
    comm->cout() << "Figure out Sponge region..." << endl;
    int numele, nsddummy;
    if (!(asc>>numele>>nsddummy))
      comm->error("Cannot read first line");
    for (int ei = 0; ei < numele; ei++) {
      int geid, block;
      Scalar sponge_As;
      if (!(asc>>geid>>block>>geid>>sponge_As))
        comm->error("Cannot read element line");
      if (partition->owns(geid)) {               // only work on local elements
        const Size leid = partition->inc(geid);
        Omega[0]->el[leid]->u *= block;
      }
      is_sponge_element.insert(pair<const int, Scalar>(geid, sponge_As));
    }
  }
}

} // namespace Reo
