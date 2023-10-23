/*============================================================================
  Module:     ML Solver for DG method

  Contact:    Scott Collis
              sscoll@sandia.gov

  Copyright:  (c)2012 Sandia National Laboratories
=============================================================================*/

/** \file SolverML.cpp
    \brief implementation for the ML solver class
    \author Axel Gerstenberger, Guglielmo Scovazzi, and Scott Collis
*/

// DGM includes
#include "SolverML.hpp"
#include "Domain.hpp"
#include "Matrix.hpp"
#include "ParUtils.hpp"

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
#include "Epetra_FECrsMatrix.h"
#include "Epetra_LinearProblem.h"
#include "AztecOO.h"
#include "EpetraExt_OperatorOut.h"
#include "EpetraExt_RowMatrixOut.h"
#include "EpetraExt_VectorOut.h"
#include "EpetraExt_MultiVectorOut.h"
#include "EpetraExt_CrsMatrixIn.h"
#include <EpetraExt_MatrixMatrix.h>
#include "Teuchos_RCP.hpp"

void DGM::SolverML::compute_CG_rdofmap(const vField &F) {
  // CG map Todo: needs generalization+testing for vector fields
  // tested only for scalar fields (Poisson)
  cdofperelement_CG.clear();
  for (vField::size_type ifield = 0; ifield < F.size(); ++ifield) {
    for (Ordinal e = 0; e < F[ifield]->ne; ++e) {
      const Element *const ele = F[ifield]->el[e];
      // sanity check: test if node has same id as previous node
      // This may indicate that no .cgc file was read and all ids
      // have the same value (probably 0 depending on the Vertex constructor)
      if (ele->vert[0]->gid == ele->vert[1]->gid)
        error("Multiple identical Vertex.gid in element! Missing .cgc file?");
      // now go ahead
      const int nVerts = ele->nVerts();
      cdofperelement_CG[ele->gid()] = vector<int>(nVerts);
      for (int inode = 0; inode < nVerts; ++inode) {
        const int gid = ele->vert[inode]->gid;
        cdofperelement_CG[ele->gid()][inode] = gid;
      }
    }
  }

  // collect DOF GIDs for each processor in a set
  std::set<int> N;
  for (map<int,vector<int> >::const_iterator iter = cdofperelement_CG.begin();
       iter != cdofperelement_CG.end(); iter++) {
    const vector<int> &dofids = iter->second;
    N.insert(dofids.begin(),dofids.end());
  }

  // create unique DOF GID distribution, i.e. make sure that each DOF GID
  // exists only once over all procs
#ifdef DGM_USE_GENERAL_GHOSTING
  make_unique(*(GetDGMComm()), N);
#else
  throw DGM::exception("Requires DGM_USE_GENERAL_GHOSTING");
#endif

  // copy unique nodal gid values to vector
  const vector<int> rdoflist(N.begin(), N.end());

  // create unique dofmap
  const int rsize = numeric_cast<int>(rdoflist.size());
  nodal_rdofmap_CG.reset( new Epetra_Map( -1, rsize, &rdoflist[0],
                                          0, F.RowDofMapPtr()->Comm()) );
  // test for uniqueness
  assert(nodal_rdofmap_CG->UniqueGIDs());
}

vector<int> DGM::SolverML::ExtractModes(
    const vector<int> &allmodes,
    const Element *const ele,
    const Ordinal &pmax) const {
  vector<int> submodes;
  int imode = 0;
  for (Ordinal ix = 0; ix < ele->pOrder()+1; ix++) {
    for (Ordinal iy = 0; iy < ele->pOrder()+1; iy++) {
      if (ix <= pmax and iy <= pmax) {
        submodes.push_back( allmodes[imode] );
      }
      imode++;
    }
  }
  return submodes;
}

const vector<int>& DGM::SolverML::get_nodal_dofs(const int egid) const {
  map<int,vector<int> >::const_iterator entry = cdofperelement_CG.find(egid);
  if (entry == cdofperelement_CG.end()) {
    ostringstream s;
    s << "DGM::SolverML::get_nodal_dofs(egid): "
      << "No DOF indices found for element with GID " << egid << "!" << endl;
    error(s.str());
  }
  return entry->second;
}

void DGM::SolverML::compute_transformation_matrix(const vField &Uf) {
  compute_CG_rdofmap(Uf);
  G = Teuchos::rcp(new Epetra_FECrsMatrix(Copy, *Uf.RowDofMapPtr(), 0));
  for (Ordinal e=0; e<Uf[0]->ne; e++) {
    const Element *const Ue = Uf[0]->el[e];
    if (Ue->nVerts() != 4 and Uf[0]->nsd() != 2)
      error("SolverML currently implemented only for Quads");
    // copy trafo matrix into Gloc
    dMatrix Gloc;
    Ue->fill_basis_shift_matrix(Gloc);
    // scatter local to global, but only for low order modes
    const vector<int> &indDG = Uf.get_row_elem_dofs(Ue->gid());
    const vector<int> &indLagr = this->get_nodal_dofs(Ue->gid());
    // use only first four DG modes. The rest remains zero.
    Domain::scatterMatrix( ExtractModes(indDG,Ue,1), indLagr, Gloc, *G);
  } // end of loop over elements
  if (0 != G->FillComplete()) error("FillComplete() failed");
}

void DGM::SolverML::
compute_transformation_matrix_global_appr(const vField &Uf) {
  compute_CG_rdofmap(Uf);
  G = Teuchos::rcp(new Epetra_CrsMatrix(Copy, *Uf.RowDofMapPtr(), 0));
  // Teuchos::RCP<Epetra_CrsMatrix> M =
  // Teuchos::rcp(new Epetra_CrsMatrix(Copy, *Uf.RowDofMapPtr(), 0));
  for (Ordinal e=0; e<Uf[0]->ne; e++) {
    const Element *const Ue = Uf[0]->el[e];
    const int nModes = Ue->nModes();

    // Interior element contribution local assembly matrix
    dMatrix Mloc(nModes, nModes); Mloc = 0.0;

    // const double Jac = Ue->geom->J[0];

    // copy trafo matrix into Gloc
    dMatrix Dloc;
    Ue->fill_basis_shift_matrix(Dloc);
    // Dloc *= Jac;

    // Mloc(0,0) = 1.0/Jac;
    // Mloc(1,1) = 1.0/Jac;
    // Mloc(2,2) = 1.0/Jac;
    // Mloc(3,3) = 1.0/Jac;

    // iVector A_pivots;
    // int i = LU_factor( Mloc, A_pivots );
    // if (i != 0) error("factorization fail");
    // i = LU_inverse( Mloc, A_pivots );
    // if (i != 0) error("inversion fail");

    // scatter local to global, but only for low order modes
    const vector<int> &indDG = Uf.get_row_elem_dofs(Ue->gid());
    const vector<int> &indLagr = this->get_nodal_dofs(Ue->gid());
    // Domain::scatterMatrix( ExtractModes(indDG,Ue,1),
    //                        ExtractModes(indDG,Ue,1),
    //                        Mloc, *M);
    Domain::scatterMatrix( ExtractModes(indDG,Ue,1), indLagr, Dloc, *G);
  } // end of loop over elements
  // const int fillStatus = M->FillComplete(*Uf.RowDofMapPtr(), 
  //                                        *Uf.RowDofMapPtr()) == 0);
  // if (fillStatus != 0) throw DGM::exception("SolverML error in FillComplete);
  // comm->cout()<<"M("<<M->NumGlobalRows()<<"x"
  //             << M->NumGlobalCols()<<")"<<flush;
  const int fillStatus = G->FillComplete(*(nodal_rdofmap_CG.get()), 
                                         *Uf.RowDofMapPtr());
  if (fillStatus != 0) throw DGM::exception("SolverML error in FillComplete");
  comm->cout()<<", G("<<G->NumGlobalRows()<<"x"<<G->NumGlobalCols()<<")"<<flush;

  // Matrix product M^-1 * D
  // Epetra_Vector Mdiag(M->RowMap());
  // assert(M->ExtractDiagonalCopy(Mdiag) == 0);
  // assert(G->LeftScale(Mdiag) == 0);
}

void DGM::SolverML::output_element_corner_coordinates(
    const vField &F,
    const string root
    ) const {
  const string fname = root+"_dump_elem_corner_coordinates.dat";
  ofstream f(fname.c_str());
  for (Ordinal e = 0; e<F[0]->ne; e++) {
    Element *ele = F[0]->el[e];
    for (Ordinal i = 0; i<ele->nVerts(); i++) {
      f << scientific << setw(16) << ele->vert[i]->x
        << scientific << setw(16) << ele->vert[i]->y
        << scientific << setw(16) << ele->vert[i]->z;
    }
    f << endl;
  }
  f.close();
}

void DGM::SolverML::compute_nodal_coordinates(const vField &F,
                                              std::vector<double>& coordx,
                                              std::vector<double>& coordy,
                                              std::vector<double>& coordz)
  const{
  int N=nodal_rdofmap_CG->NumMyElements();
  Ordinal Ne=F[0]->ne;
  coordx.resize(N);
  coordy.resize(N);
  coordz.resize(N);
  for (Ordinal e = 0; e<Ne; e++) {
    Element *ele = F[0]->el[e];
    const std::vector<int> &mydofs = get_nodal_dofs(ele->gid());
    // This will 2x touch entries.  But that is not a huge waste.
    for(int i=0; i<(int)mydofs.size(); i++){
      int ngid=mydofs[i];
      int nlid=nodal_rdofmap_CG->LID(ngid);
      if(nlid>=0){
        coordx[nlid] = ele->vert[i]->x;
        coordy[nlid] = ele->vert[i]->y;
        coordz[nlid] = ele->vert[i]->z;
      }
    }
  }
}

#endif
