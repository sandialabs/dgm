/*=============================================================================
  Module:     Simple Poisson Solver

  Author:     S. Scott Collis

  Copyright:  (c) 2010 Sandia National Laboratories
              sscollis@sandia.gov
=============================================================================*/

/** \file Poisson.cpp
    \brief Basic Poisson equation module implementation
*/

// Reo includes
#include "Reo.hpp"
#include "Poisson.hpp"
#include "PoissonBC.hpp"

// DGM includes
#include "Operator.hpp"

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

namespace Reo {

using namespace DGM;

/// Poisson constructor
Poisson::Poisson( DGM::ArgList &args, const DGM::Comm::Ptr comm_ ) :
  Domain(args, comm_), restart(false), Uv(comm_), Uo(comm_) {

  // Initialize output parameters
  input("auxtec",       0);      // Compute derivative quantities
  input("plot3d_x",     1);      // plot3d grid file
  input("plot3d_q",     1);      // plot3d mesh file
  input("darcy_pin",    0);      // pin constant mode or not
  input("ghosting",     0);      // test the ghosting framework

  // Initialize solver parameters
  input("matrix_solve", false);  // solve with matrix, otherwise, matrix free
  input("solver",       0);      // default is matrix-free GMRES
  input("matrix_out",   false);  // dump (and build) matrices
  input("use_ldg",      true);   // default is ldg with residual formulation
  input("use_new_bc",   false);  // default is old BC with residual formulation
  input("projic",       true);   // project IC to poly space
  input("projavg",      true);   // project out the average
  input("iterations",   500);    // max number of GMRES iterations
  input("tolerance",    1e-9);   // tolerance for the GMERS solver
  input("kspace",       100);    // dimension of Krylov space for GMRES solver

  // read arguments (overrides defaults and input file)
  parse_args( args );

  // initialize parameters
  const int p = params.get("p");       // polynomial order
  comm->cout() << " Poisson: p = " << p << endl;
  const int q = p + 2;                 // number of quadrature points
  comm->cout() << " Poisson: q = " << q << endl;
  nsd = params.get("nsd");             // number of space dimensions

  vector<string> field_names;          // Field names
  field_names.push_back("u");

  // build a Field of Elements and Sides
  if (params.get("imesh")) {
    Mesh mesh(params);
    U.push_back( new Field(p, q, mesh, root, field_names[0],
                           Field::FULL, comm ) );
    partition = U[0]->partition;
  } else if (params.get("bmesh")) {
    U.push_back( new Field(p, q, root, field_names[0], partition, 1,
                           Reo::NumEqntype, p2i(POISSON), comm ) );
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
  for (vField::size_type i=1; i<Nfields; i++)
    U.push_back( new Field( U[0], root, field_names[i] ) );

  // make auxiliary Fields using copy constructor
  Ut.set_name("Ut");
  for (vField::size_type i=0; i<Nfields; i++) {
    Ut.push_back( new Field( U[i], root, field_names[i] ) );
  }

  // this makes U and Ut contiguous
  make_contiguous();

  // make auxiliary Fields using copy constructor
  Uv.set_name("Uv");
  for (vField::size_type i=0; i<Nfields; i++) {
    Uv.push_back( new Field( U[i], root, field_names[i] ) );
  }

  if (params.get("darcy_pin")) {
    // make auxiliary Fields using copy constructor
    Uo.set_name("Uo");
    for (vField::size_type i=0; i<Nfields; i++) {
      Uo.push_back( new Field( U[i], root, field_names[i] ) );
    }
  }

  // allocate workspace
  wk.resize(5*max(Lmax(),Qmax()));

  // make sure that storage is initialized
  zero_all_fields();

  // make analysis object
  response = Response::factory(U, this);

  setup_BCdb();

  setup_Sourcedb();

  set_TimeInt();

  verifyBCs(U);

  if (params.get("use_ldg")) // turn on or off LDG for testing
    comm->cout() << "Enabled LDG" << endl;
  else
    comm->cout() << "Disabled LDG" << endl;
  if (params.get("matrix_solve")) // there is no LDG formulation for matrices
    params["use_ldg"] = false;

  if (params.get("use_new_bc"))
    comm->cout() << "Using new BCs" << endl;
  else
    comm->cout() << "Using old BCs" << endl;
}

/// Parse parameters from the argument list
void Poisson::parse_args( DGM::ArgList &args ) {
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
  for ( list< DGM::ArgList::iterator >::iterator a=li.begin();
        a!=li.end(); a++) args.erase(*a);
}

/// Show usage for Poisson solver
void Poisson::showUsage() {
  comm->cout()
    << "Poisson Class Options \n"
    << "----------------------------------------------------------------\n"
    << "-nox       " << '\t' << "No grid file                           \n"
    << "-noq       " << '\t' << "No solution file                       \n"
    << "-aux       " << '\t' << "Auxiliary Tecplot file                 \n"
    << "-solver    " << '\t' << "Specify the solver type                \n"
    << "-projic    " << '\t' << "Project the initial condition          \n"
    << "-projavg   " << '\t' << "Project out the average                \n"
    << "-iterations" << '\t' << "GM-Res maximum number of iterations    \n"
    << "-tolerance " << '\t' << "GM-Res relative residual tolerance     \n"
    << "-dim_krylov" << '\t' << "GM-Res dimension of krylov space       \n"
    << "----------------------------------------------------------------\n";
}

/// Zero all fields
void Poisson::zero_all_fields() {
  Domain::zero_all_fields();
  Uv.zero();
  Uo.zero();
}

//===========================================================================
//                             Solve Methods
//===========================================================================

/// Evaluate the action of the Poisson operator on a solution vector
void Poisson::action( vField &Us, vField &Uf ) {
  residual(Us, Uf);
  axpy(one, Ut, Uf, Uf);
  if (params.get("darcy_pin")) {
    // pin a constant mode to zero
    Us.forward_transform();
    axpy( Us[0]->el[0]->uh[0], Uo, Uf, Uf);  // does that work in parallel?
    Uf[0]->el[0]->uh[0] = Us[0]->el[0]->uh[0];  // does that work in parallel?
    Us.backward_transform();
  }
}

/// Computes the complete DG residual for Poisson
void Poisson::residual( vField &Us, vField &Uf ) {
  //comm->cout() << "Poisson::residual()" << endl;
  const bool use_ldg = params.get("use_ldg");
  dVector ux, uxh, uy, uyh;
  Us.fill_sides();
  Us.share_sides();
  enforce_bc(Us);
  average_flux( Us, Uf, '+' );          // replace with {u_h} - C_12\cdot[u_h]
  if (stab!=0 || bstab!=0.0) {
    copy_sides(Us,Uv);
    Uv.share_sides();
    enforce_bc(Uv);
  }
  for (vField::size_type i=0; i<Us.size(); ++i) {
    for (LocalSize e=0; e<Us[i]->ne; ++e) {
      Element *U = Us[i]->el[e];
      Element *F = Uf[i]->el[e];
      const Ordinal qtot = U->qtot;
      const Ordinal nModes = U->nModes();
      ux.alias(wk,qtot);
      uxh.alias(ux,nModes);
      uy.alias(wk,qtot,qtot);
      uyh.alias(uy,nModes);
      U->gradient(U->u, ux, uy);
      if ( use_ldg ) {
        U->lift( F, ux, 'x' );
        U->project(ux);
        U->lift( F, uy, 'y' );
        U->project(uy);
      }
      U->fill_sides( ux, uy );                // normal flux on sides
      U->gradient(ux, ux, 'x');               // ux = u_{,xx}
      U->gradient(uy, uy, 'y');               // uy = u_{,yy}
      dvadd( ux, uy, F->u );                  // F->u = u_{,xx} + u_{,yy}
    }
  }
  Us.share_sides();
  enforce_flux_bc(Us);
  if (stab!=0.0) {
    interior_penalty_flux( Uv, Us, Uf, stab*Us.get_max_sigma() );
  } else
    average_flux( Us, Uf, '-' );
  if (bstab!=0.0)
    enforce_boundary_penalty( Uv, Uf, bstab*Us.get_max_sigma() );
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

/// Compute the interior penalty flux on the sides
void Poisson::interior_penalty_flux(const vField &Up, const vField &Us,
                                    vField &Uf, const Scalar sigma) {
  // cout<<"Poisson::interior_penalty_flux(...)"<<endl;
#ifdef REO_USE_GETSIDEMAPS
  iVector mapl, mapr;
#endif
  for (vField::size_type n=0; n<Us.size(); n++) {
    for (LocalSize e=0; e<Us[n]->ne; e++) {
      const Element * const P = Up[n]->el[e];
      const Element * const S = Us[n]->el[e];
      Element * const F = Uf[n]->el[e];
#ifndef REO_POISSON_USE_OLD_INTERIOR_PENALTY_FLUX
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
            const Ordinal ql = S->sideMap(sl, q);
            const Ordinal qr = S->sideMap(sr, q);
#endif
            fl->u[ql] = pt5 * (sl->u[ql] - sr->u[qr]) +
                        sigma*(pr->u[qr] - pl->u[ql]);
            fr->u[qr] = -fl->u[ql];
          }
        }
      }
#else
      for (LocalSize i=0; i<S->nSides(); i++) {
        if (S->side[i]->master()) {
          const LocalSize qtot = S->side[i]->qtot();
#ifdef REO_USE_GETSIDEMAPS
          get_side_maps( S->side[i], S->side[i]->link, mapl, mapr );
#endif
          for (LocalSize q=0; q<qtot; q++) {
#ifdef REO_USE_GETSIDEMAPS
            const Ordinal ql = mapl[q];
            const Ordinal qr = mapr[q];
#else
            const Ordinal ql = S->sideMap(S->side[i], q);
            const Ordinal qr = S->sideMap(S->side[i]->link, q);
#endif
            F->side[i]->u[ql] = pt5  *(S->side[i]->u[ql] -
                                       S->side[i]->link->u[qr]) -
                                    sigma*(P->side[i]->u[ql] -
                                           P->side[i]->link->u[qr]);
            F->side[i]->link->u[qr] = -F->side[i]->u[ql];
          }
        }
      }
#endif
    }
  }
}

/// Enforce the penalty term on the boundary
/** \todo Make sure to debug this
    \warning This does not work with general side orientations. */
void Poisson::enforce_boundary_penalty(const vField &S, vField &F,
                                       const Scalar sigma) {
  comm->cout() << "Poisson::enforce_boundary_penalty() not debugged" << endl;
  for (LocalSize n=0; n<S[0]->nbc; ++n) {
    for(LocalSize i=0; i<S[0]->bc[n]->S->qtot(); ++i) {
      F[0]->bc[n]->S->u[i] -= pt5*sigma*(   S[0]->bc[n]->S->u[i]
                                          - S[0]->bc[n]->S->link->u[i] );
      F[0]->bc[n]->S->link->u[i] = -F[0]->bc[n]->S->u[i];
    }
  }
}

Scalar Poisson::computeC11( const Side * const Us_loc,
                            const Side * const Us_adj) const {
  const Scalar h_n = 0.5*(1.0/Us_loc->h_n_inv() + 1.0/Us_adj->h_n_inv());
  const Scalar C11 = stab/h_n;
  return C11;
}

#ifdef DGM_USE_EPETRA

/// Computes the BC side contribution to the matrix and righthand-side
void Poisson::Matrix_sides_bndry(
    const vField &Uf,
    Epetra_CrsMatrix &A
    ) const {

  std::set<string> Dirichlet;
  std::set<string> Neumann;

  // Hack alarm: this should be implemented in the various BC classes-> no casts
  for (BC::db_citr i=BC_db.begin(); i!= BC_db.end(); ++i) {
    const BC *const bc = &*(i->second);
    if (dynamic_cast<Reo::Poisson::DirichletBC const*const>(bc)!=NULL) {
      Dirichlet.insert(bc->type);
    }
  }

  for (LocalSize n=0; n<Uf[0]->nbc; ++n) {
    const Side *const Us_loc = Uf[0]->bc[n]->S;
    const Side *const Us_adj = vField::select_adj(Us_loc);

    const int nModes_loc = Us_loc->nModes();

    // easy pointers to elements
    const Element *const e_loc = Us_loc->elink;

    // load side quadrature points
    const int qstot  = Us_loc->qtot();

    // work vector: shape function mode in physical space
    dVector phi_loc(e_loc->qtot);

    dMatrix MATlocloc(nModes_loc, nModes_loc, 0.0);

    // side ids
    const Ordinal sid_loc = Us_loc->id();

    // work vectors
    dVector ws_loc(qstot);
    dVector ws_adj(qstot);
    dVector wh_loc(nModes_loc);

    assert(Us_loc->is_bc() == true);

    const Boundary *const bnd = Uf[0]->bc[n];
    const string type = bnd->type;

    if (Dirichlet.find(type) != Dirichlet.end() ) {
      // - ( v , nabla u * n )_G_Dirichlet
      for (int jtrial=0; jtrial<nModes_loc; jtrial++) {
        e_loc->fill(e_loc->psi->mode[jtrial],phi_loc);
        e_loc->normal_times_gradient_side( phi_loc, sid_loc, ws_loc );
        e_loc->test_on_shape_side( ws_loc, sid_loc, wh_loc);
        for (int itest=0; itest<nModes_loc; itest++) {
          MATlocloc(itest,jtrial) -= wh_loc(itest);
        }
      }
      // - ( nabla v * n , u )_G_Dirichlet
      for (int jtrial=0; jtrial<nModes_loc; jtrial++) {
        e_loc->fill(e_loc->psi->mode[jtrial], phi_loc);
        e_loc->load_side(phi_loc,sid_loc,ws_loc);
        e_loc->test_on_normal_times_gradient_side(ws_loc, sid_loc, wh_loc );
        for (int itest=0; itest<nModes_loc; itest++) {
          MATlocloc(itest,jtrial) -= wh_loc(itest);
        }
      }
      // + ( v , C11 u )_G_Dirichlet
      for (int jtrial=0; jtrial<nModes_loc; jtrial++) {
        const Scalar C11 = computeC11(Us_loc, Us_adj);
        e_loc->fill(e_loc->psi->mode[jtrial], phi_loc);
        e_loc->load_side(phi_loc,sid_loc,ws_loc);
        scale(C11, ws_loc);
        e_loc->test_on_shape_side(ws_loc, sid_loc, wh_loc );
        for (int itest=0; itest<nModes_loc; itest++) {
          MATlocloc(itest,jtrial) += wh_loc[itest];
        }
      }

    } else if (Neumann.find(type) != Neumann.end() ) {

    }

    // scatter the local matrix to global
    const vector<int> &indices_loc = Uf.get_row_elem_dofs(e_loc->gid());
    scatterMatrix(indices_loc, indices_loc, MATlocloc, A);

  } // loop over boundary sides
}


/// Computes the BC side contribution to the matrix and righthand-side
void Poisson::RHS_sides_bndry(
    const vField &Uf,
    const vField &Ff,
    Epetra_Vector &b
    ) const {

  std::set<string> Dirichlet;
  std::set<string> Neumann;

  // Hack: this should be implemented in the various BC classes-> no casts
  for (BC::db_citr i=BC_db.begin(); i!= BC_db.end(); ++i) {
    const BC *const bc = &*(i->second);
    if (dynamic_cast<Reo::Poisson::DirichletBC const*const>(bc)!=NULL) {
      Dirichlet.insert(bc->type);
    }
  }

  for (LocalSize n=0; n<Uf[0]->nbc; ++n) {
    const Side *const Us_loc = Uf[0]->bc[n]->S;
    const Side *const Us_adj = vField::select_adj(Us_loc);

    const int nModes_loc = Us_loc->nModes();

    // easy pointers to elements
    const Element *const e_loc = Uf[0]->el[Us_loc->leid()];

    // load side quadrature points
    const int qstot  = Us_loc->qtot();

    // work vector: shape function mode in physical space
    dVector bh(nModes_loc, 0.0);

    // side ids
    const Ordinal sid_loc = Us_loc->id();

    // work vectors
    dVector ws_loc(qstot);
    dVector wh_loc(nModes_loc);

    assert(Us_loc->is_bc() == true);

    Boundary* bnd = Uf[0]->bc[n];
    string type = bnd->type;

    // entries for rhs vector b
    if (Dirichlet.find(type) != Dirichlet.end() ) {

      // - ( nabla v * n , g_Dirichlet )_G_Dirichlet
      ws_loc = Us_adj->u; // <-- contains the right stuff due to matrix_apply
      e_loc->test_on_normal_times_gradient_side(ws_loc, sid_loc, wh_loc );
      bh -= wh_loc;

      // + ( v , C11 g_Dirichlet )_G_Dirichlet
      ws_loc = Us_adj->u; // <-- contains the right stuff due to matrix_apply
      const Scalar C11 = computeC11(Us_loc, Us_adj);
      scale(C11, ws_loc);
      e_loc->test_on_shape_side(ws_loc, sid_loc, wh_loc );
      bh += wh_loc;

    } else if (Neumann.find(type) != Neumann.end() ) {

      const Side *const Fs_loc = Ff[0]->bc[n]->S;
      const Side *const Fs_adj = vField::select_adj(Fs_loc);

      // + ( v , g_Neumann )_G_Neumann
      ws_loc = Fs_adj->u; // <-- contains the right stuff due to matrix_apply_flux
      e_loc->test_on_shape_side(ws_loc, sid_loc, wh_loc );
      bh += wh_loc;
    } else {
      comm->error("only Dirichlet and Neumann implemented!");
    }

    // scatter the local matrix to global
    const vector<int> &indices_loc = Uf.get_row_elem_dofs(e_loc->gid());
    scatterVector(indices_loc, bh, b);

  } // loop over boundary sides
}


/// Computes the side contribution to the matrix and righthand-side
void Poisson::Matrix_sides_interior(
    const vField &Uf,
    Epetra_CrsMatrix &A) const {

  for (LocalSize e=0; e<Uf[0]->ne; e++) {
    // localize elements
    const Element *const Ue = Uf[0]->el[e];
    // terms from the sides
    for (Ordinal i=0; i<Ue->nSides(); i++) {
      const Side *const Us_loc = Ue->side[i];
      const Side *const Us_adj = vField::select_adj(Us_loc);

      if (Us_loc->is_bc() == true) {
        continue;
      }
      else
      {
        // and may be the same as eid_loc at boundary
        const int nModes_loc = Us_loc->nModes();
        const int nModes_adj = Us_adj->nModes();

        // easy pointers to elements
        const Element *const e_loc = Uf[0]->el[Us_loc->leid()];
        const Element *const e_adj = Uf[0]->el[Us_adj->leid()];
        // in parallel & and at the boundary, adj is not existent

        // load side quadrature points
        const int qstot  = Us_loc->qtot();

#ifdef REO_USE_GETSIDEMAPS
        // synchronize the quadrature points between neighbors
        SideMap smap;
        get_side_maps(Us_loc,Us_adj,smap.idl(),smap.idr());
#endif

        // work vector: shape function mode in physical space
        dVector phi_loc(e_loc->qtot);
        dVector phi_adj(e_adj->qtot);

        dMatrix MATlocloc(nModes_loc, nModes_loc, 0.0);
        dMatrix MATlocadj(nModes_loc, nModes_adj, 0.0);

        // side ids
        const Ordinal sid_loc = Us_loc->id();
        assert(i == sid_loc);
        const int sid_adj = Us_adj->id();

        // work vectors
        dVector ws_loc(qstot);
        dVector ws_adj(qstot);
        dVector wh_loc(nModes_loc);

        // - ( [v] , {nabla u * n} )_G_i
        for (int jtrial=0; jtrial<nModes_loc; jtrial++) {
          e_loc->fill(e_loc->psi->mode[jtrial],phi_loc);
          e_loc->normal_times_gradient_side( phi_loc, sid_loc, ws_loc );
          scale(0.5, ws_loc);
          e_loc->test_on_shape_side( ws_loc, sid_loc, wh_loc);
          for (int itest=0; itest<nModes_loc; itest++) {
            MATlocloc(itest,jtrial) -= wh_loc(itest);
          }
        }
        for (int jtrial=0; jtrial<nModes_adj; jtrial++) {
          e_adj->fill(e_adj->psi->mode[jtrial],phi_adj);
          e_adj->normal_times_gradient_side( phi_adj, sid_adj, ws_adj );
          scale(0.5, ws_adj);
#ifdef REO_USE_GETSIDEMAPS
          smap.renumber(ws_adj, ws_loc);
#else
          const Size qstot = ws_loc.size();
          // assume that both sides have the same number of quadrature points
          assert(ws_adj.size() == ws_loc.size());
          for (Size q = 0; q < qstot; ++q) {
            const Ordinal ql = Ue->sideMap(Us_loc, q);
            const Ordinal qr = Ue->sideMap(Us_adj, q);
            ws_loc(ql) = ws_adj(qr);
          }
#endif
          e_loc->test_on_shape_side( ws_loc, sid_loc, wh_loc);
          for (int itest=0; itest<nModes_loc; itest++) {
            MATlocadj(itest,jtrial) += wh_loc(itest);
          }
        }
        // - ( {nabla v * n} , [u] )_G_i
        for (int jtrial=0; jtrial<nModes_loc; jtrial++) {
          e_loc->fill(e_loc->psi->mode[jtrial], phi_loc);
          e_loc->load_side(phi_loc,sid_loc,ws_loc);
          scale(0.5, ws_loc);
          e_loc->test_on_normal_times_gradient_side(ws_loc, sid_loc, wh_loc );
          for (int itest=0; itest<nModes_loc; itest++) {
            MATlocloc(itest,jtrial) -= wh_loc(itest);
          }
        }
        for (int jtrial=0; jtrial<nModes_adj; jtrial++) {
          e_adj->fill(e_adj->psi->mode[jtrial], phi_adj);
          e_adj->load_side(phi_adj,sid_adj,ws_adj);
#ifdef REO_USE_GETSIDEMAPS
          smap.renumber(ws_adj, ws_loc);
#else
          const Size qstot = ws_loc.size();
          // assume that both sides have the same number of quadrature points
          assert(ws_adj.size() == ws_loc.size());
          for (Size q = 0; q < qstot; ++q) {
            const Ordinal ql = Ue->sideMap(Us_loc, q);
            const Ordinal qr = Ue->sideMap(Us_adj, q);
            ws_loc(ql) = ws_adj(qr);
          }
#endif
          scale(0.5, ws_loc);
          e_loc->test_on_normal_times_gradient_side(ws_loc, sid_loc, wh_loc );
          for (int itest=0; itest<nModes_loc; itest++) {
            MATlocadj(itest,jtrial) += wh_loc(itest);
          }
        }

        // + ( [v] , C11 [u] )_G_i
        for (int jtrial=0; jtrial<nModes_loc; jtrial++) {
          const Scalar C11 = computeC11(Us_loc, Us_adj);
          e_loc->fill(e_loc->psi->mode[jtrial], phi_loc);
          e_loc->load_side(phi_loc,sid_loc,ws_loc);
          scale(C11, ws_loc);
          e_loc->test_on_shape_side(ws_loc, sid_loc, wh_loc );
          for (int itest=0; itest<nModes_loc; itest++) {
            MATlocloc(itest,jtrial) += wh_loc[itest];
          }
        }
        for (int jtrial=0; jtrial<nModes_adj; jtrial++) {
          const Scalar C11 = computeC11(Us_loc, Us_adj);
          e_adj->fill(e_adj->psi->mode[jtrial], phi_adj);
          e_adj->load_side(phi_adj,sid_adj,ws_adj);
#ifdef REO_USE_GETSIDEMAPS
          smap.renumber(ws_adj, ws_loc);
#else
          const Size qstot = ws_loc.size();
          // assume that both sides have the same number of quadrature points
          assert(ws_adj.size() == ws_loc.size());
          for (Size q = 0; q < qstot; ++q) {
            const Ordinal ql = Ue->sideMap(Us_loc, q);
            const Ordinal qr = Ue->sideMap(Us_adj, q);
            ws_loc(ql) = ws_adj(qr);
          }
#endif
          scale(C11, ws_loc);
          e_loc->test_on_shape_side(ws_loc, sid_loc, wh_loc );
          for (int itest=0; itest<nModes_loc; itest++) {
            MATlocadj(itest,jtrial) -= wh_loc[itest];
          }
        }

        // scatter the local matrix to global
        const vector<int> &indices_loc = Uf.get_row_elem_dofs(e_loc->gid());
        const vector<int> &indices_adj = Uf.get_row_elem_dofs(e_adj->gid());
        scatterMatrix(indices_loc,indices_loc, MATlocloc, A);
        scatterMatrix(indices_loc,indices_adj, MATlocadj, A);
      }
    } // loop over sides
  } // loop over elements
}


/// Computes the side contribution to the matrix and righthand-side
void Poisson::RHS_sides_interior(
    const vField &Uf,
    Epetra_Vector &b) const {

  for (LocalSize e=0; e<Uf[0]->ne; e++) {
    // localize elements
    const Element *const Ue = Uf[0]->el[e];
    // terms from the sides
    for (Ordinal i=0; i<Ue->nSides(); i++) {
      const Side *const Us_loc = Ue->side[i];
      if (Us_loc->is_bc() == true) {
        continue;
      } else {
        // and may be the same as eid_loc at boundary
        const int nModes_loc = Us_loc->nModes();

        // easy pointers to elements
        const Element *const e_loc = Uf[0]->el[Us_loc->leid()];

        // load side quadrature points
        const int qstot  = Us_loc->qtot();

        dVector bh(nModes_loc, 0.0);

        // side ids
        const Ordinal sid_loc = Us_loc->id();
        if (i != sid_loc) throw DGM::exception("Side id mismatch");

        // work vectors
        dVector ws_loc(qstot);
        dVector ws_adj(qstot);
        dVector ws_avg(qstot);
        dVector wh_loc(nModes_loc);

        // scatter the local matrix to global
        const vector<int> &indices_loc = Uf.get_row_elem_dofs(e_loc->gid());
        scatterVector(indices_loc, bh, b);
      }
    } // loop over sides
  } // loop over elements
}

/// Computes the domain integrals
void Poisson::Matrix_domain_integrals(
    const vField &Uf,
    Epetra_CrsMatrix &A
    ) const {

  char vdir[3] = {'x','y','z'}; // direction vector
  for (LocalSize e=0; e<Uf[0]->ne; e++) {
    const Element *const e_loc = Uf[0]->el[e];
    const int nModes = e_loc->nModes();
    const int qtot  = e_loc->qtot;

    // work vectors (SSC:  would be better to use alias to wk space)
    dVector psi(qtot);  // shape function in physical space
    dVector dpsi(qtot);
    dVector fh(nModes);

    // Interior element contribution local assembly matrix
    dMatrix MATloc(nModes, nModes, 0.0);

    // + ( nabla v , nabla u )_Omega
    for (int jtrial=0; jtrial<nModes; jtrial++) {
      e_loc->fill( e_loc->psi->mode[jtrial], psi );
      for (Ordinal i=0; i<nsd; i++) {
        e_loc->gradient( psi, dpsi, vdir[i]);
        e_loc->test_on_grad_shape(dpsi,vdir[i],fh);
        for (int itest=0; itest<nModes; itest++) {
          MATloc(itest,jtrial) += fh[itest];
        }
      }
    }

    /// scatter local to global
    const vector<int> &indexlist = Uf.get_row_elem_dofs(e_loc->gid());
    scatterMatrix( indexlist, indexlist, MATloc, A);

  } // end of loop over elements
}

/// element interior contributions to the RHS
void Poisson::RHS_domain_integrals(
    const vField &Uf,
    Epetra_Vector &b
    ) const {

  for (LocalSize e=0; e<Uf[0]->ne; e++) {
    const Element *const e_loc = Uf[0]->el[e];
    const LocalSize nModes = e_loc->nModes();

    // work vectors (SSC:  would be better to use alias to wk space)
    dVector fh(nModes);
    dVector bh(nModes, 0.0);

    // + ( v , f_source_file )_Omega
    e_loc->test_on_shape(Uv[0]->el[e]->u,fh);
    bh += fh;

    // scatter local to global
    const vector<int> &indexlist = Uf.get_row_elem_dofs(e_loc->gid());
    scatterVector( indexlist, bh, b);

  } // end of loop over elements
}

/** Computes the matrix for the Hughes, Masud, Wan
    stabilized DG method for the Poisson equation */
void Poisson::Matrix(
    Epetra_CrsMatrix &A) const {

  // note: modes (in 2d) are ordered like:
  // N0 = 1/2
  // N1 = sqrt(3)/2 y
  // N2 = sqrt(3)/2 x
  // N3 = 3/2 xy
  // N4 = ...

  Matrix_sides_interior( U, A );
  Matrix_sides_bndry( U, A );
  Matrix_domain_integrals( U, A );

  const int status = A.FillComplete();
  if (status != 0) throw DGM::exception("Poisson error in FillComplete");
}


/** Computes the right hand-side for the Hughes, Masud, Wan
    stabilized DG method for the Poisson equation */
void Poisson::RHS( Epetra_Vector &b ) const {

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
int Poisson::solve() {
  comm->cout() << "Poisson::solve() " << std::endl;

#ifdef DGM_USE_EPETRA

  const bool rebuild = (A == Teuchos::null);

  const bool matrix_solve = params.get("matrix_solve");
  if (matrix_solve == true) {

    comm->cout() << "Matrix formulation, ";

    U.ghost(root, 1);

    if ((bool)params.get("ghosting") == true) {
      return 0;
    }

    // data on sides and boundaries and parallel communication
    U.zero();
    U.fill_sides();
    U.share_sides();

    // prepare source and boundary data
    Uv.zero();
    add_source( U, Uv );

    // instead of enforce_BC, which calls apply, use matrix_apply()
    for (BC::db_citr i=BC_db.begin(); i!= BC_db.end(); ++i)
      i->second->matrix_apply( t, U );

    Ut.zero();
    Ut.fill_sides();
    Ut.share_sides();
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
    comm->cout() << "build b" << std::flush;
    if ((int)params.get("solver") >= 0) { // works only in serial right now
      RHS(*b);
      if ( rebuild ) {
        const int n = A->Map().NumGlobalElements();
        comm->cout() << ", build A("<<n<<"x"<<n<<")" << std::flush;
        Matrix(*A);
      }
    }

    if (params.get("matrix_out")) {
      comm->cout() << ", output A & b" << std::flush;
      EpetraExt::OperatorToMatlabFile((root+"_dump_A.dat").c_str(),*A);
      EpetraExt::VectorToMatlabFile((root+"_dump_b.dat").c_str(),*b);
    }

    U.forward_transform();
    U.pack(*x); // <-- put initial guess into Epetra vector
    //U.pack();

    if ((int)params.get("solver") == solve_direct){
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

    comm->cout() << "Matrix-free formulation, " << std::flush;

    // evaluate the residual and store in Ut
    U.zero();
    residual(U,Ut);  // compute r(0) (make sure U = 0)
    scale(-one,Ut);  // compute -r(0)
    Ut.pack();
    b = Teuchos::rcp(new Epetra_Vector( *Ut.modal_vec ));
    Ut.unpack();

    if (params.get("darcy_pin")) {
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
    if (!restart) {
      set_ic(U);
      if (params.get("tecplot"))
        U.tecplot("ic.dat","Initial Guess");
    }
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

  comm->cout() << endl;

  U.norm();

  if (!restart) {
    write(root+".rst",U);
#ifndef DGM_PARALLEL
    if (params.get("tecplot"))
      U.tecplot("out.dat","Poisson solution");
#endif
  }

  if (step%Ntout==0) {
    write(step, U);
  }

#else  // !DGM_USE_EPETRA

  comm->error("Poisson::solve() must be built with Trilinos");

#endif // DGM_USE_EPETRA

  return 0;
}

//===========================================================================
//                            Initial Conditions
//===========================================================================

/// Set the initial condition
void Poisson::set_ic(vField &F, string ext) {
  t = 0.0; step = 0;
  string fname = root+ext;
  ifstream in(fname.c_str());
  if (!in) {
    comm->cerr()<< "Poisson::set_ic: Could not open initial condition file "
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
    comm->error("Poisson::set_ic()  Unsupported IC type");
  }
  // determine whether to project the initial condition to the p-space
  if (params.get("projic")) {
    // comm->cout() << "  Note: Projecting IC to polynomial space" << endl;
    project( F );
  } else {
    comm->cout() << "  WARNING:  No projection of Initial condition" << endl;
    for (vField::size_type i=0; i<F.size(); i++)
      for (LocalSize e=0; e<ne; e++)
        F[i]->el[e]->state = Element::Physical;
  }
  if (params.get("projavg")) {                // project out the average
    project_out_avg( *Uv[0], F );
  }
}

/// project out the average
void Poisson::project_out_avg(Field &U, vField &F) const {
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

// Load up the available BC types
void Poisson::setup_BCdb( ) {
  // comm->cout() << "Poisson::setup_BCdb()" << endl;

  // set default BC types
  dVector ub(1);
  ub[0] = 1.0;
  BC_db["D"].reset( new DirichletBC("D", 0.0) );
  BC_db["S"].reset( new StateBC("S", ub) );

  // read new BC types from file
  string fname = root+".bct";
  ifstream in(fname.c_str());
  if (in) Poisson::read_BCdb( in );   // database of active BC types
}

BC* Poisson::make_BC( ifstream &in, string &tag ) {
  // comm->cout() << "Poisson::make_BC(ifstream &in, string &tag)" << endl;
  string code;
  if (!(in >> code)) return NULL;
  code = lowerCase(code);
  if (code == "state") {
    if (!(in >> tag)) error("Poisson::make_BC: Cannot read State tag",1);
    return new StateBC(tag,in,Nfields);
  }
  else if (code == "dirichlet") {
      if (!(in >> tag)) error("Poisson::make_BC() Cannot read Dirichlet tag");
      return new DirichletBC(tag,in);
  } else {
    if(comm->Master())
      comm->cerr()<<"WARNING Poisson::make_BC() Illegal BC type: "+code<<endl;
  }
  return NULL;
}

//===========================================================================
//                       Source database management
//===========================================================================

/// Construct source terms
Source::Ptr Poisson::make_Source( ifstream &in, string &tag ) {
  string code;
  Source::Ptr p;
  if (!(in >> code)) return p;
  while (code[0]=='#') {  // eat comment lines
    string buffer;
    getline(in,buffer);
    if (!(in >> code)) return p;
  }
  if (lowerCase(code) == "constant") {
    if (!(in >> tag)) error("Poisson::Cannot read ConstSource tag",1);;
    p.reset( new ConstSource(tag,in,U.size()) );
  } else if (lowerCase(code) == "file") {
    if (!(in >> tag)) error("Poisson::Cannot read FileSource tag",1);
    p.reset( new FileSource(tag,in,U) );
  } else if (lowerCase(code) == "function") {
    if (!(in >> tag)) error("Poisson::Cannot read FuncSource tag",1);
    p.reset( new FuncSource(tag,in,U.size()) );
  } else {
    error("Poisson::make_Source() Illegal Source type",1);
  }
  return p;
}

/// Add source terms
void Poisson::add_source(const vField &Us, vField &Ur) {
  for (Source::db_citr i=Source_db.begin(); i!= Source_db.end(); ++i)
    i->second->apply( t, Us, Ur);
}

//===========================================================================
//                             Output Methods
//===========================================================================

/// Plot the Poisson solution
/** \note Does not generate full output in parallel for all writers. */
int Poisson::plot(const string &rst) {
  read( rst, U );
  const string rootname(rst.substr(0,rst.find(".rst")));
  ostringstream caption;
  caption << "State variables at t = " << scientific << t
          << ", step = " << step;
  if (params["tecplot"])
    if (comm->Master())
      U.tecplot(rootname+".dat",caption.str());
  if (params["paraview"]) U.paraview(rootname,caption.str());
  if (params.get("plot3d")) {
    if (params.get("plot3d_x")) {
      if (comm->Master()) U.plot3d_x(rootname+".xyz");
    }
    if (params.get("plot3d_q")) {
      if (comm->Master()) U.plot3d_q(rootname+".q");
    }
  }
  if (params.get("auxtec")) {
    comm->error("Auxiliary output not currently supported");
  }
  return 0;
}

} // namespace Reo
