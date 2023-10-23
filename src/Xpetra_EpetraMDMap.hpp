#ifndef XPETRA_EPETRAMDMAP_HPP
#define XPETRA_EPETRAMDMAP_HPP

/** \file   Xpetra_EpetraMDMap.hpp
    \brief  Xpetra wrapper of a concrete Epetra multidimensional map
    \author Bill Spotz
*/

// Xpetra includes
#include "Xpetra_EpetraConfigDefs.hpp"
#include "Xpetra_Utils.hpp"
#include "Xpetra_EpetraUtils.hpp"
#include "Xpetra_Exceptions.hpp"
#include "Xpetra_EpetraMap.hpp"

// Local includes
#include "Epetra_MDMap.h"
#include "Xpetra_MDMap.hpp"

namespace Xpetra
{
// Conversion functions
const Epetra_MDMap &
toEpetra(const MDMap< int, int > & map);

const RCP< const Epetra_MDMap > &
toEpetra(const RCP< const MDMap< int, int > > & map);

#if 0
// FIXME (mfh 04 Nov 2015) returning const RCP& is a bad idea.
// Not our fault; we maintain the interface as it stands.
const RCP< const Xpetra::Map< int, int > > &
toXpetra(const Epetra_Map & map);
#endif

/// Xpetra wrapper to an Epetra MD Map
class EpetraMDMap :
    public MDMap< int, int >,
    public EpetraMapT< int, Xpetra::Map<int, int>::node_type >
{
public:
  typedef int local_ordinal_type;
  typedef int global_ordinal_type;
  typedef EpetraMapT<global_ordinal_type, node_type> Base;
  typedef Base::node_type node_type;

  //! The N-dimensional constructor utilizes \c Teuchos::ArrayView to
  //! provide the required global shape and optional axis number of
  //! processors and halos.  In practice, users can utilize the
  //! Teuchos::Tuple class to specify these quantities.  The
  //! dimensionality of the \c MDMap is determined by the number of
  //! elements in argument \c globalShape.  Arguments \c axisNumProc
  //! and \c halos can be underspecified, with logical defaults
  //! automatically substituted.
  EpetraMDMap(const Teuchos::RCP< const Teuchos::Comm< int > > & comm,
              const Teuchos::ArrayView< int > & globalShape,
              const Teuchos::ArrayView< int > & axisNumProc =
                  Teuchos::ArrayView< int >(),
              const Teuchos::ArrayView< int > & halos =
                  Teuchos::ArrayView< int >(),
              const Teuchos::ArrayView< int > & ghostPoints =
                  Teuchos::ArrayView< int >(),
              const Teuchos::ArrayView< int > & periodic =
                  Teuchos::ArrayView< int >());

  //! The 2D constructor creates a map for two-dimensional data and
  //! only requires that the number of indexes in the i and j
  //! directions be specified.  Optional arguments include the number
  //! of processors along the i and j axes, as well as the halos in
  //! the i and j directions.
  EpetraMDMap(const Teuchos::RCP< const Teuchos::Comm< int > > & comm,
              const int globalNum_i,
              const int globalNum_j,
              const int numProc_i     = -1,
              const int numProc_j     = -1,
              const int halo_i        =  0,
              const int halo_j        =  0,
              const int ghostPoints_i =  0,
              const int ghostPoints_j =  0,
              const int periodic_i    = false,
              const int periodic_j    = false);

  //! EpetraMDMap destructor.
  ~EpetraMDMap() { }

  ///////////////////////////////////////
  // Base class method implementations //
  ///////////////////////////////////////

  using Base::description;
  using Base::describe;
  using Base::getGlobalNumElements;
  using Base::getNodeNumElements;
  using Base::getIndexBase;
  using Base::getMinLocalIndex;
  using Base::getMaxLocalIndex;
  using Base::getMinGlobalIndex;
  using Base::getMaxGlobalIndex;
  using Base::getMinAllGlobalIndex;
  using Base::getMaxAllGlobalIndex;
  using Base::getRemoteIndexList;
  using Base::getNodeElementList;
  using Base::isNodeLocalElement;
  using Base::isNodeGlobalElement;
  using Base::isContiguous;
  using Base::isDistributed;
  using Base::isCompatible;
  using Base::isSameAs;
  using Base::getComm;

  /////////////////////////////////
  // Attribute retrieval methods //
  /////////////////////////////////

  //! Number of dimensions

  //! Describes the dimensionality of the problem represented by the
  //! \c MDMap: 1 for 1D, 2 for 2D, etc.
  inline
  int
  getNumDims() const
  {
    return map_->getNumDims();
  }

  //! Global dimension values

  //! Returns a \c Teuchos::ArrayRCP containing the global size of the
  //! problem along each axis, excluding ghost points.
  inline
  const Teuchos::ArrayRCP< int >
  getGlobalShape() const
  {
    return map_->getGlobalShape();
  }

  //! Global dimension value

  //! Returns the global dimension of the problem, excluding ghost
  //! points, along the requested axis.
  inline
  int
  getGlobalShape(int axis) const
  {
    return map_->getGlobalShape(axis);
  }

  //! Global dimension values

  //! Returns a \c Teuchos::ArrayRCP containing the global size of the
  //! problem along each axis, including ghost points.
  inline
  const Teuchos::ArrayRCP< int >
  getGlobalGhostShape() const
  {
    return map_->getGlobalGhostShape();
  }

  //! Global dimension value

  //! Returns the global dimension of the problem, including ghost
  //! points, along the requested axis.
  inline
  int
  getGlobalGhostShape(int axis) const
  {
    return map_->getGlobalGhostShape(axis);
  }

  //! Local dimension values, excluding halos

  //! Returns a \c Teuchos::ArrayRCP containing the local size of the
  //! problem along each axis, excluding halos.
  inline
  const Teuchos::ArrayRCP< int >
  getLocalOwnShape() const
  {
    return map_->getLocalOwnShape();
  }

  //! Local dimension value, excluding halos

  //! Returns the local dimension of the problem along the requested
  //! axis, excluding halos.
  inline
  int
  getLocalOwnShape(int axis) const
  {
    return map_->getLocalOwnShape(axis);
  }

  //! Local dimension values

  //! Returns a \c Teuchos::ArrayRCP containing the local size of the
  //! problem along each axis, including halos.
  inline
  const Teuchos::ArrayRCP< int >
  getLocalShape() const
  {
    return map_->getLocalShape();
  }

  //! Local dimension value

  //! Returns the local dimension of the problem along the requested
  //! axis, including halos.
  inline
  int
  getLocalShape(int axis) const
  {
    return map_->getLocalShape(axis);
  }

  //! Local interior (non-boundary) loop bounds

  //! Returns a \c Teuchos::ArrayRCP of \c Teuchos::Tuple of 2
  //! ints corresponding to the lower and upper bounds for
  //! looping over interior (non-boundary) elements on each axis.
  inline
  const Teuchos::ArrayRCP< Teuchos::Tuple< int, 2 > >
  getLocalInteriorBounds() const
  {
    return map_->getLocalInteriorBounds();
  }

  //! Local interior (non-boundary) loop bounds

  //! Returns a Teuchos::Tuple of 2 ints corresponding to the
  //! lower and upper bounds for looping over interior (non-boundary)
  //! elements on the given axis.
  inline
  const Teuchos::Tuple< int, 2 >
  getLocalInteriorBounds(int axis) const
  {
    return map_->getLocalInteriorBounds(axis);
  }

  //! Starting axis index along each axis

  //! Returns a \c Teuchos::Array::RCP containing the starting global
  //! axis index along each axis.
  inline
  const Teuchos::ArrayRCP< int >
  getAxisStart() const
  {
    return map_->getAxisStart();
  }

  //! Starting axis index along requested axis

  //! Returns the starting global axis index along the requested
  //! axis.
  inline
  int
  getAxisStart(int axis) const
  {
    return map_->getAxisStart(axis);
  }

  //! Processor partitions

  //! Returns a \c Teuchos::ArrayRCP containing the number of
  //! processors assigned along each axis.
  inline
  const Teuchos::ArrayRCP< int >
  getAxisNumProcs() const
  {
    return map_->getAxisNumProcs();
  }

  //! Processor partition

  //! Returns the number of processors assigned along the requested
  //! axis.
  inline
  int
  getAxisNumProcs(int axis) const
  {
    return map_->getAxisNumProcs(axis);
  }

  //! Processor axis ranks

  //! Returns a \c Teuchos::ArrayRCP containing the axis processor
  //! ranks along each axis for the local processor.
  inline
  const Teuchos::ArrayRCP< int >
  getAxisRanks() const
  {
    return map_->getAxisRanks();
  }

  //! Processor axis rank

  //! Returns the axis processor rank along the requested axis for the
  //! local processor.
  inline
  int
  getAxisRank(int axis) const
  {
    return map_->getAxisRank(axis);
  }

  //! Halo sizes for each axis

  //! Returns a \c Teuchos::ArrayRCP containing a \c Teuchos::Tuple
  //! along each axis that contains the upper and lower halo values.
  inline
  const Teuchos::ArrayRCP< Teuchos::Tuple< int, 2 > >
  getHalos() const
  {
    return map_->getHalos();
  }

  //! Halo sizes for requested axis

  //! Returns a \c Teuchos::Tuple along the requeseted axis that
  //! contains the upper and lower halo values.
  inline
  const Teuchos::Tuple< int, 2 >
  getHalos(int axis) const
  {
    return map_->getHalos(axis);
  }

  //! Halo presence

  //! Returns true if map has any non-zero halos
  inline bool
  hasHalos() const
  {
    return map_->hasHalos();
  }

  //! Nominal halos

  //! Returns an array of the requested halo size along each axis,
  //! regardless of the presence of boundaries
  inline Teuchos::ArrayRCP< int >
  getNominalHalos() const
  {
    return map_->getNominalHalos();
  }

  //! Ghost points

  //! Returns an array of integers indicating the number of ghost
  //! points to be used on each axis.
  inline
  Teuchos::ArrayRCP< int >
  getGhostPoints() const
  {
    return map_->getGhostPoints();
  }

  //! Ghost points for requested axis

  //! Returns an integer indicating the number of ghost points on the
  //! requested axis.
  inline
  int getGhostPoints(int axis) const
  {
    return map_->getGhostPoints(axis);
  }

  //! Periodic flags

  //! Returns an array of integer flags indicating whether each axis
  //! is periodic.
  inline
  Teuchos::ArrayRCP< int >
  getPeriodic() const
  {
    return map_->getPeriodic();
  }

  //! Periodic flag for requested axis

  //! Returns an integer flag indicating whether the requested axis is
  //! periodic.
  inline
  int
  getPeriodic(int axis) const
  {
    return map_->getPeriodic(axis);
  }

  //! Global stride information

  //! Returns a \c Teuchos::ArrayRCP containing the stride length
  //! along each axis.
  inline
  const Teuchos::ArrayRCP< int >
  getGlobalStrides() const
  {
    return map_->getGlobalStrides();
  }

  //! Global stride information

  //! Returns a \c Teuchos::ArrayRCP containing the stride length
  //! along each axis.
  inline
  int
  getGlobalStride(int axis) const
  {
    return map_->getGlobalStride(axis);
  }

  //! Local stride information

  //! Returns a \c Teuchos::ArrayRCP containing the stride length
  //! along each axis.
  inline
  const Teuchos::ArrayRCP< int >
  getLocalStrides() const
  {
    return map_->getLocalStrides();
  }

  //! Local stride information

  //! Returns a \c Teuchos::ArrayRCP containing the stride length
  //! along each axis.
  inline
  int
  getLocalStride(int axis) const
  {
    return map_->getLocalStride(axis);
  }

  //! 1D maps along each axis

  //! Returns a \c Teuchos::ArrayRCP containing a 1D \c Xpetra::Map
  //! along each axis, representing the decomposition of that axis
  //! index along that axis.
  inline
  const Teuchos::ArrayRCP< Teuchos::RCP< const Xpetra::Map< int, int > > >
  getAxisMaps() const
  {
    return axisMaps_;
  }

  //! 1D map along requested axis

  //! Returns a 1D \c Xpetra::Map along the requested axis,
  //! representing the decomposition of that axis index along that
  //! axis.
  inline
  const Teuchos::RCP< const Xpetra::Map< int, int > >
  getAxisMap(int axis) const
  {
    return axisMaps_[axis];
  }

  //////////////////////
  // Indexing methods //
  //////////////////////

  //! Convert a global index into an array of global axis indexes
  inline Teuchos::Array< int >
  getGlobalAxisIndex(const int globalIndex) const
  {
    return map_->getGlobalAxisIndex(globalIndex);
  }

  //! Convert a local index into an array of local axis indexes

  //! Note that the local origin (0,0,...) refers to the index of the
  //! first element of the interior, or non-halo region.
  inline Teuchos::Array< int >
  getLocalAxisIndex(const int localIndex) const
  {
    return map_->getLocalAxisIndex(localIndex);
  }

  //! Convert a local index into a global index
  inline int
  getGlobalElement(int localIndex) const
  {
    return map_->getGlobalElement(localIndex);
  }

  //! Convert an array of global axis indexes into a global index
  inline int
  getGlobalElement(const Teuchos::ArrayView< const int > globalAxisIndex) const
  {
    return map_->getGlobalElement(globalAxisIndex);
  }

  //! Convert a global index into a local index
  inline int
  getLocalElement(int globalIndex) const
  {
    return map_->getLocalElement(globalIndex);
  }

  //! Convert an array of local axis indexes into a local index

  //! Note that the local origin (0,0,...) refers to the index of the
  //! first element of the interior, or non-halo region.
  inline int
  getLocalElement(const Teuchos::ArrayView< const int > localAxisIndex) const
  {
    return map_->getLocalElement(localAxisIndex);
  }

  //! @name Xpetra specific
  //@{

  //! EpetraMDMap constructor to wrap an Epetra_MDMap object
  EpetraMDMap(const Teuchos::RCP<const Epetra_MDMap > & map);

  //! Get the library used by this object (Tpetra or Epetra?)
  UnderlyingLib lib() const
  {
    return Xpetra::UseEpetra;
  }

  //! Get the underlying Tpetra map
  const RCP< const Epetra_MDMap > &
  getEpetra_MDMap() const
  {
    return map_;
  }

  //@}

private:

  // Private static method for constructing and storing a reference
  // counted pointer to an Epetra_MDMap.  This allows the
  // Xpetra::EpetraMDMap constructors to construct a map and
  // provide it to the Xpetra::EpetraMap base class as the first step
  // in the constructor process.
  static RCP< const Epetra_MDMap >
  computeMDMap(const Teuchos::RCP< const Teuchos::Comm< int > > & comm,
               const Teuchos::ArrayView< int > & globalShape,
               const Teuchos::ArrayView< int > & axisNumProc,
               const Teuchos::ArrayView< int > & halos,
               const Teuchos::ArrayView< int > & ghostPoints,
               const Teuchos::ArrayView< int > & periodic);

  // Private method to convert the MDMap's axis Maps from
  // pointers to Epetra_Maps to pointers to Xpetra::Maps.
  void convertAxisMaps();

  // Static variable that allows the computeMDMap method to
  // store a reference counted pointer to an Epetra_MDMap.
  static RCP< const Epetra_MDMap > temp_map_;

  // Reference counted pointer to the underlying Epetra_MDMap.
  const RCP< const Epetra_MDMap > map_;

  // An array of the MDMap's axis maps, cast to Xpetra::Maps
  Teuchos::ArrayRCP< RCP< const Xpetra::Map< int, int > > > axisMaps_;

};  // EpetraMDMap class

}  // Namespace Xpetra

#endif
