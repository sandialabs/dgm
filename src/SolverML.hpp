#ifndef DGM_SOLVER_ML_HPP
#define DGM_SOLVER_ML_HPP

/** \file SolverML.hpp
    \brief Declarations of an ML solver object
    \author Axel Gerstenberger
    \author Scott Collis
*/

// DGM includes
#include "vField.hpp"

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
#endif

namespace DGM {

#ifdef DGM_USE_EPETRA

/// Contains all methods and some variables to solve DG via ML
/*!
 *  Can handle only scalar DG fields at the moment (vField::size() = 1)
 */
class SolverML {

  const DGM::Comm::Ptr comm; ///< Communicator for this vField

  map<int,vector<int> > cdofperelement_CG; ///< global nodal DOF ids per global
                                           ///< element id

  /// map for the Continuous Galerkin degree of freedom
  DGM::Shared<Epetra_Map>::Ptr  nodal_rdofmap_CG; ///< data map for CG DOFs

  /// copy nModesToExtract into vector submodes
  vector<int> ExtractModes(const vector<int> &allmodes,
                           const Element *const ele,
                           const Ordinal &pmax) const;

  /// compute non-overlapping linear Continuous Galerkin DOF map
  void compute_CG_rdofmap(const vField &F);

  /// returns list of nodal DOF GIDs for the element
  const vector<int>& get_nodal_dofs(const int egid) const;

public:

  /// Constructor
  explicit SolverML(const DGM::Comm::Ptr &comm_) : comm(comm_) {}

  /// access to DGM communicator
  DGM::Comm* GetDGMComm() {return comm.get();}

  Teuchos::RCP<Epetra_CrsMatrix> G;  ///< rect. trafo matrix for AMG solve

  /// Computes and assemble the global transformation matrix
  void compute_transformation_matrix(
      const vField &Uf
  );

  /// Computes and assemble the global transformation matrix
  void compute_transformation_matrix_global_appr(
      const vField &Uf
  );

  /// output element corner coordinates for debugging
  void output_element_corner_coordinates(
      const vField &F,
      const string root
      ) const;

  /// Compute the coordinates in nodal Lagrange ordering.
  void compute_nodal_coordinates(const vField &F,
                                 std::vector<double>& coordx,
                                 std::vector<double>& coordy,
                                 std::vector<double>& coordz) const;
};

#endif

}

#endif // DGM_SOLVER_ML_HPP
