#ifndef XPETRA_MDMAP_HPP
#define XPETRA_MDMAP_HPP

//! \file   Xpetra_MDMap.hpp
//! \brief  Xpetra declaration of Finite Difference MDMap
//! \author Bill Spotz

// Teuchos includes
#include "Teuchos_Tuple.hpp"

// Xpetra includes
#include "Xpetra_ConfigDefs.hpp"
#include "Xpetra_Map.hpp"

namespace Xpetra
{

/// Xpetra base class for a multidimensional Map
/** A pure virtual class for switching between Epetra_MDMap
    and Tpetra::MDMap. */
template< class LocalOrdinal,
          class GlobalOrdinal = LocalOrdinal,
          class Node = KokkosClassic::DefaultNode::DefaultNodeType >
class MDMap : public virtual Map< LocalOrdinal, GlobalOrdinal, Node >
{

public:

  // Inherit base class method implementations
  using Map< LocalOrdinal, GlobalOrdinal, Node >::description;
  using Map< LocalOrdinal, GlobalOrdinal, Node >::describe;
  using Map< LocalOrdinal, GlobalOrdinal, Node >::getGlobalNumElements;
  using Map< LocalOrdinal, GlobalOrdinal, Node >::getNodeNumElements;
  using Map< LocalOrdinal, GlobalOrdinal, Node >::getIndexBase;
  using Map< LocalOrdinal, GlobalOrdinal, Node >::getMinLocalIndex;
  using Map< LocalOrdinal, GlobalOrdinal, Node >::getMaxLocalIndex;
  using Map< LocalOrdinal, GlobalOrdinal, Node >::getMinGlobalIndex;
  using Map< LocalOrdinal, GlobalOrdinal, Node >::getMaxGlobalIndex;
  using Map< LocalOrdinal, GlobalOrdinal, Node >::getMinAllGlobalIndex;
  using Map< LocalOrdinal, GlobalOrdinal, Node >::getMaxAllGlobalIndex;
  using Map< LocalOrdinal, GlobalOrdinal, Node >::getRemoteIndexList;
  using Map< LocalOrdinal, GlobalOrdinal, Node >::getNodeElementList;
  using Map< LocalOrdinal, GlobalOrdinal, Node >::isNodeLocalElement;
  using Map< LocalOrdinal, GlobalOrdinal, Node >::isNodeGlobalElement;
  using Map< LocalOrdinal, GlobalOrdinal, Node >::isContiguous;
  using Map< LocalOrdinal, GlobalOrdinal, Node >::isDistributed;
  using Map< LocalOrdinal, GlobalOrdinal, Node >::isCompatible;
  using Map< LocalOrdinal, GlobalOrdinal, Node >::isSameAs;
  using Map< LocalOrdinal, GlobalOrdinal, Node >::getComm;

  //! Destructor
  virtual ~MDMap() { }

  /////////////////////////////////
  // Attribute retrieval methods //
  /////////////////////////////////

  //! Number of dimensions

  //! Describes the dimensionality of the problem represented by the
  //! \c MDMap: 1 for 1D, 2 for 2D, etc.
  virtual
  int
  getNumDims() const = 0;

  //! Global dimension values

  //! Returns a \c Teuchos::ArrayRCP containing the global size of the
  //! problem along each axis, excluding ghost points.
  virtual
  const Teuchos::ArrayRCP< GlobalOrdinal >
  getGlobalShape() const = 0;

  //! Global dimension value

  //! Returns the global dimension of the problem, excluding ghost
  //! points, along the requested axis.
  virtual
  GlobalOrdinal
  getGlobalShape(int axis) const = 0;

  //! Global dimension values

  //! Returns a \c Teuchos::ArrayRCP containing the global size of the
  //! problem along each axis, including ghost points.
  virtual
  const Teuchos::ArrayRCP< GlobalOrdinal >
  getGlobalGhostShape() const = 0;

  //! Global dimension value

  //! Returns the global dimension of the problem, including ghost
  //! points, along the requested axis.
  virtual
  GlobalOrdinal
  getGlobalGhostShape(int axis) const = 0;

  //! Local dimension values, excluding halos

  //! Returns a \c Teuchos::ArrayRCP containing the local size of the
  //! problem along each axis, excluding halos.
  virtual
  const Teuchos::ArrayRCP< LocalOrdinal >
  getLocalOwnShape() const = 0;

  //! Local dimension value, excluding halos

  //! Returns the local dimension of the problem along the requested
  //! axis, excluding halos.
  virtual
  LocalOrdinal
  getLocalOwnShape(int axis) const = 0;

  //! Local dimension values

  //! Returns a \c Teuchos::ArrayRCP containing the local size of the
  //! problem along each axis, including halos.
  virtual
  const Teuchos::ArrayRCP< LocalOrdinal >
  getLocalShape() const = 0;

  //! Local dimension value

  //! Returns the local dimension of the problem along the requested
  //! axis, including halos.
  virtual
  LocalOrdinal
  getLocalShape(int axis) const = 0;

  //! Local interior (non-boundary) loop bounds

  //! Returns a \c Teuchos::ArrayRCP of \c Teuchos::Tuple of 2
  //! LocalOrdinals corresponding to the lower and upper bounds for
  //! looping over interior (non-boundary) elements on each axis.
  virtual
  const Teuchos::ArrayRCP< Teuchos::Tuple< LocalOrdinal, 2 > >
  getLocalInteriorBounds() const = 0;

  //! Local interior (non-boundary) loop bounds

  //! Returns a Teuchos::Tuple of 2 LocalOrdinals corresponding to the
  //! lower and upper bounds for looping over interior (non-boundary)
  //! elements on the given axis.
  virtual
  const Teuchos::Tuple< LocalOrdinal, 2 >
  getLocalInteriorBounds(int axis) const = 0;

  //! Starting axis index along each axis

  //! Returns a \c Teuchos::Array::RCP containing the starting global
  //! axis index along each axis.
  virtual
  const Teuchos::ArrayRCP< GlobalOrdinal >
  getAxisStart() const = 0;

  //! Starting axis index along requested axis

  //! Returns the starting global axis index along the requested
  //! axis.
  virtual
  GlobalOrdinal
  getAxisStart(int axis) const = 0;

  //! Processor partitions

  //! Returns a \c Teuchos::ArrayRCP containing the number of
  //! processors assigned along each axis.
  virtual
  const Teuchos::ArrayRCP< int >
  getAxisNumProcs() const = 0;

  //! Processor partition

  //! Returns the number of processors assigned along the requested
  //! axis.
  virtual
  int
  getAxisNumProcs(int axis) const = 0;

  //! Processor axis ranks

  //! Returns a \c Teuchos::ArrayRCP containing the axis processor
  //! ranks along each axis for the local processor.
  virtual
  const Teuchos::ArrayRCP< int >
  getAxisRanks() const = 0;

  //! Processor axis rank

  //! Returns the axis processor rank along the requested axis for the
  //! local processor.
  virtual
  int
  getAxisRank(int axis) const = 0;

  //! Halo sizes for each axis

  //! Returns a \c Teuchos::ArrayRCP containing a \c Teuchos::Tuple
  //! along each axis that contains the upper and lower halo values.
  virtual
  const Teuchos::ArrayRCP< Teuchos::Tuple< int, 2 > >
  getHalos() const = 0;

  //! Halo sizes for requested axis

  //! Returns a \c Teuchos::Tuple along the requeseted axis that
  //! contains the upper and lower halo values.
  virtual
  const Teuchos::Tuple< int, 2 >
  getHalos(int axis) const = 0;

  //! Halo presence

  //! Returns true if map has any non-zero halos
  virtual
  bool
  hasHalos() const = 0;

  //! Nominal halos

  //! Returns an array of the requested halo size along each axis,
  //! regardless of the presence of boundaries
  virtual
  Teuchos::ArrayRCP< int >
  getNominalHalos() const = 0;

  //! Ghost points

  //! Returns an array of integers indicating the number of ghost
  //! points to be used on each axis.
  virtual
  Teuchos::ArrayRCP< int >
  getGhostPoints() const = 0;

  //! Ghost points for requested axis

  //! Returns an integer indicating the number of ghost points on the
  //! requested axis.
  virtual
  int getGhostPoints(int axis) const = 0;

  //! Periodic flags

  //! Returns an array of integer flags indicating whether each axis
  //! is periodic.
  virtual
  Teuchos::ArrayRCP< int >
  getPeriodic() const = 0;

  //! Periodic flag for requested axis

  //! Returns an integer flag indicating whether the requested axis is
  //! periodic.
  virtual
  int
  getPeriodic(int axis) const = 0;

  //! Global stride information

  //! Returns a \c Teuchos::ArrayRCP containing the stride length
  //! along each axis.
  virtual
  const Teuchos::ArrayRCP< GlobalOrdinal >
  getGlobalStrides() const = 0;

  //! Global stride information

  //! Returns a \c Teuchos::ArrayRCP containing the stride length
  //! along each axis.
  virtual
  GlobalOrdinal
  getGlobalStride(int axis) const = 0;

  //! Local stride information

  //! Returns a \c Teuchos::ArrayRCP containing the stride length
  //! along each axis.
  virtual
  const Teuchos::ArrayRCP< LocalOrdinal >
  getLocalStrides() const = 0;

  //! Local stride information

  //! Returns a \c Teuchos::ArrayRCP containing the stride length
  //! along each axis.
  virtual
  LocalOrdinal
  getLocalStride(int axis) const = 0;

  //! 1D maps along each axis

  //! Returns a \c Teuchos::ArrayRCP containing a 1D \c Xpetra::Map
  //! along each axis, representing the decomposition of that axis
  //! index along that axis.
  virtual
  const Teuchos::ArrayRCP< Teuchos::RCP< const Xpetra::Map< LocalOrdinal,
                                                            GlobalOrdinal,
                                                            Node > > >
  getAxisMaps() const = 0;

  //! 1D map along requested axis

  //! Returns a 1D \c Xpetra::Map along the requested axis,
  //! representing the decomposition of that axis index along that
  //! axis.
  virtual
  const Teuchos::RCP< const Xpetra::Map< LocalOrdinal, GlobalOrdinal, Node > >
  getAxisMap(int axis) const = 0;

  //////////////////////
  // Indexing methods //
  //////////////////////

  //! Convert a global index into an array of global axis indexes
  virtual
  Teuchos::Array< GlobalOrdinal >
  getGlobalAxisIndex(const GlobalOrdinal globalIndex) const = 0;

  //! Convert a local index into an array of local axis indexes

  //! Note that the local origin (0,0,...) refers to the index of the
  //! first element of the interior, or non-halo region.
  virtual
  Teuchos::Array< LocalOrdinal >
  getLocalAxisIndex(const LocalOrdinal LocalIndex) const = 0;

  //! Convert a local index into a global index
  virtual
  GlobalOrdinal
  getGlobalElement(LocalOrdinal localIndex) const = 0;

  //! Convert an array of global axis indexes into a global index
  virtual
  GlobalOrdinal
  getGlobalElement(const Teuchos::ArrayView< const GlobalOrdinal >
                     globalAxisIndex) const = 0;

  //! Convert a global index into a local index
  virtual
  LocalOrdinal
  getLocalElement(GlobalOrdinal globalIndex) const = 0;

  //! Convert an array of local axis indexes into a local index

  //! Note that the local origin (0,0,...) refers to the index of the
  //! first element of the interior, or non-halo region.
  virtual
  LocalOrdinal
  getLocalElement(const Teuchos::ArrayView< const LocalOrdinal >
                    localAxisIndex) const = 0;

};  // MDMap class

} // Xpetra namespace

#endif
