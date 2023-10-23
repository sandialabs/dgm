/** \file AdvDiff2dFD.hpp
    \brief Finite 2D difference methods for AdvDiff equation
    \author Scott Collis
    \author Bill Spotz

    AdvDiffFD classes are sub-classes of the Domain class that
    contain fields for solution variables and implement finite
    differences in the spatial directions.
*/
#ifndef REO_ADVDIFF2DFD_HPP
#define REO_ADVDIFF2DFD_HPP

// Standard includes
#include <string>
#include <map>
#include <cmath>

// Trilinos includes
#include "Teuchos_RCP.hpp"
#include "Teuchos_Array.hpp"
#include "Teuchos_Time.hpp"

// DTK includes
#include "DTK.hpp"
#include "DTK_TimeIntegrate.hpp"

// FDM includes
#include "FDM_Types.hpp"
#include "FDM_CartesianMesh.hpp"
#include "FDM_Domain.hpp"
#include "FDM_Field.hpp"
#include "FDM_State.hpp"
#include "FDM_BC.hpp"
#include "FDM_Source.hpp"
#include "FDM_Kernel.hpp"

// Make the Teuchos tuple available
using Teuchos::Array;
using Teuchos::tuple;

namespace Reo {

//! 2d AdvDiff finite difference
class AdvDiff2dFD : public FDM::Domain {
public:

  // BCs

  // Sources

  //! AdvDiff2dFD mesh
  AdvDiff2dFD(const FDM::CartesianMeshPtr mesh,
               Json::Value &root,
               std::string ext="");

  //! AdvDiff2dFD destructor
  ~AdvDiff2dFD() {
#ifdef REO_FD_CODETRACE
    out() << "AdvDiff2dFD destructor" << endl;
#endif
  }

  //! Compute the source term
  void computeSource(const FDM::Scalar time);

  //! Output all probes to a set of files
  void outputProbes();

  //! Output a trace to a file
  void outputTrace(std::string & traceFile);

  //! \name DTK::Domain interface
  //@{
  //! Domain solve interface
  virtual int solve();

  //! time derivative method
  virtual void time_derivative(FDM::VectorField &,
                               FDM::VectorField &);
  //! time derivative method
  virtual void time_derivative(FDM::VectorField &,
                               FDM::VectorField &,
                               FDM::Ordinal) { FDM_UNDEFINED; }

  //! Prestep setup
  virtual void prestep(FDM::VectorField &,
                       const FDM::Ordinal,
                       const FDM::Ordinal,
                       const FDM::Scalar );

  //! Poststep setup
  virtual void poststep(FDM::VectorField &, const FDM::Ordinal,
                        const FDM::Ordinal, const FDM::Scalar);

  //! Apply source terms
  virtual void applySource(const FDM::Scalar time,
                           const FDM::VectorField &S,
                           FDM::VectorField &R );

  //! Apply boundary conditions
  virtual void applyBC(const FDM::Scalar time,
                       FDM::VectorField &R);

  //@}

  FDM::CartesianMeshPtr mesh() const { return _mesh; }

private:

  //! Initialization method, called by the constructors
  void initialize();

  //! Setup the source parameters
  void setup_sources();

  //! Validate the source parameters
  void validate_sources() const;

  //! Setup the receiver parameters
  void setup_receivers();

  //! Setup the initial condition
  void setup_initial_condition();

  //! Setup the boundary conditions
  void setup_boundary_conditions() {}

  //! \name Special versions for LeapFrog that should be removed
  //@{
  //! Apply source terms
  void applySource(const FDM::Scalar        time,
                   const FDM::VectorField & S,
                   FDM::VectorField &       R,
                   const FDM::Scalar        fact);

  //! Apply boundary conditions
  void applyBC(const FDM::Scalar  time,
               FDM::VectorField & R,
               const FDM::Scalar  fact);
  //@}

  //! \name Accessors
  //@{
  inline FDM::Scalar dx()  const { return _dx;  }
  inline FDM::Scalar dy()  const { return _dy;  }
  inline FDM::Scalar dxi() const { return _dxi; }
  inline FDM::Scalar dyi() const { return _dyi; }
  //@}

protected:

  Json::Value &_root;                  ///< hold a Json root

  //! \name BC database
  //@{
  /// Pointer to BC
  //typedef Teuchos::RCP< FDM::BC > BCPtr;

  /// BC database type
  typedef std::map< std::string, FDM::BC::Ptr > BC_db_type;

  /// BC database iterator
  typedef BC_db_type::iterator BC_db_itr;

  /// BC database
  BC_db_type BC_db;
  //@}

  //! \name Mesh and finite-difference parameters
  //@{
  FDM::CartesianMeshPtr _mesh;         ///< Cartesian mesh

  FDM::Ordinal          _order;        ///< finite-difference order

  const int             _halo;         ///< constant halo size

  FDM::Scalar           _dx;           ///< mesh spacing in x-direction
  FDM::Scalar           _dy;           ///< mesh spacing in y-direction

  FDM::Scalar           _dxi;          ///< inverse of mesh spacing in x
  FDM::Scalar           _dyi;          ///< inverse of mesh spacing in y
  //@}

  //! \name Probe and trace data
  //@{
  FDM::Ordinal              _nProbe;        ///< total number of probes
  Array< FDM::Kernel::Ptr > _probes;        ///< kernels for probes
  //Array< ProbeFile >      _probefiles;    ///< array of ProbeFiles
  Array< FDM::InterpInfo >  _trace;         ///< trace interpolation info
  //@}

};

}  // namespace Reo

#endif
