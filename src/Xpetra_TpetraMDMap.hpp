
/** \file Xpetra_TpetraMDMap.hpp
    \brief Xpetra wrapper for a Tpetra multidimensional Map
    \author Bill Spotz
*/

#ifndef XPETRA_TPETRAMDMAP_HPP
#define XPETRA_TPETRAMDMAP_HPP

// Xpetra includes
#include "Xpetra_TpetraConfigDefs.hpp"
#include "Xpetra_Utils.hpp"
#include "Xpetra_Exceptions.hpp"
#include "Xpetra_TpetraMap.hpp"

// Local includes
#include "Tpetra_MDMap.hpp"
#include "Xpetra_MDMap.hpp"

namespace Xpetra
{

// Conversion functions
template <class LocalOrdinal, class GlobalOrdinal, class Node>
const Tpetra::MDMap< LocalOrdinal, GlobalOrdinal, Node > &
toTpetra(const Xpetra::MDMap< LocalOrdinal, GlobalOrdinal, Node> & map);

template <class LocalOrdinal, class GlobalOrdinal, class Node>
const RCP< const Tpetra::MDMap< LocalOrdinal, GlobalOrdinal, Node > > &
toTpetra(const RCP< const MDMap< LocalOrdinal,
                                 GlobalOrdinal,
                                 Node > > & map);

template <class LocalOrdinal, class GlobalOrdinal, class Node>
const RCP< const MDMap< LocalOrdinal, GlobalOrdinal, Node > >
toXpetra(const RCP< const Tpetra::MDMap< LocalOrdinal,
                                         GlobalOrdinal,
                                         Node > > & map);

/// Xpetra wrapper for a Tpetra MD map
template < class LocalOrdinal,
           class GlobalOrdinal = LocalOrdinal,
           class Node          = KokkosClassic::DefaultNode::DefaultNodeType >
class TpetraMDMap :
    public MDMap< LocalOrdinal, GlobalOrdinal, Node >,
    public TpetraMap< LocalOrdinal, GlobalOrdinal, Node >
{
public:

  //! The N-dimensional constructor utilizes \c Teuchos::ArrayView to
  //! provide the required global shape and optional axis number of
  //! processors and halos.  In practice, users can utilize the
  //! Teuchos::Tuple class to specify these quantities.  The
  //! dimensionality of the \c MDMap is determined by the number of
  //! elements in argument \c globalShape.  Arguments \c axisNumProc
  //! and \c halos can be underspecified, with logical defaults
  //! automatically substituted.
  TpetraMDMap(const Teuchos::RCP< const Teuchos::Comm< int > > & comm,
              const Teuchos::ArrayView< GlobalOrdinal > & globalShape,
              const Teuchos::ArrayView< int > & axisNumProc =
                  Teuchos::ArrayView< int >(),
              const Teuchos::ArrayView< int > & halos =
                  Teuchos::ArrayView< int >(),
              const Teuchos::ArrayView< int > & ghostPoints =
                  Teuchos::ArrayView< int >(),
              const Teuchos::ArrayView< int > & periodic =
                  Teuchos::ArrayView< int >(),
              const Teuchos::RCP< Node > & node =
                  Teuchos::RCP< Node >());

  //! The 2D constructor creates a map for two-dimensional data and
  //! only requires that the number of indexes in the i and j
  //! directions be specified.  Optional arguments include the number
  //! of processors along the i and j axes, as well as the halos in
  //! the i and j directions.
  TpetraMDMap(const Teuchos::RCP< const Teuchos::Comm< int > > & comm,
              const GlobalOrdinal globalNum_i,
              const GlobalOrdinal globalNum_j,
              const int           numProc_i     = -1,
              const int           numProc_j     = -1,
              const int           halo_i        =  0,
              const int           halo_j        =  0,
              const int           ghostPoints_i =  0,
              const int           ghostPoints_j =  0,
              const int           periodic_i    = false,
              const int           periodic_j    = false,
              const Teuchos::RCP< Node > & node =
                  Teuchos::RCP< Node >());

  //! TpetraMDMap destructor.
  ~TpetraMDMap() { }

  ///////////////////////////////////////
  // Base class method implementations //
  ///////////////////////////////////////

  using TpetraMap< LocalOrdinal, GlobalOrdinal, Node >::description;
  using TpetraMap< LocalOrdinal, GlobalOrdinal, Node >::describe;
  using TpetraMap< LocalOrdinal, GlobalOrdinal, Node >::getGlobalNumElements;
  using TpetraMap< LocalOrdinal, GlobalOrdinal, Node >::getNodeNumElements;
  using TpetraMap< LocalOrdinal, GlobalOrdinal, Node >::getIndexBase;
  using TpetraMap< LocalOrdinal, GlobalOrdinal, Node >::getMinLocalIndex;
  using TpetraMap< LocalOrdinal, GlobalOrdinal, Node >::getMaxLocalIndex;
  using TpetraMap< LocalOrdinal, GlobalOrdinal, Node >::getMinGlobalIndex;
  using TpetraMap< LocalOrdinal, GlobalOrdinal, Node >::getMaxGlobalIndex;
  using TpetraMap< LocalOrdinal, GlobalOrdinal, Node >::getMinAllGlobalIndex;
  using TpetraMap< LocalOrdinal, GlobalOrdinal, Node >::getMaxAllGlobalIndex;
  using TpetraMap< LocalOrdinal, GlobalOrdinal, Node >::getRemoteIndexList;
  using TpetraMap< LocalOrdinal, GlobalOrdinal, Node >::getNodeElementList;
  using TpetraMap< LocalOrdinal, GlobalOrdinal, Node >::isNodeLocalElement;
  using TpetraMap< LocalOrdinal, GlobalOrdinal, Node >::isNodeGlobalElement;
  using TpetraMap< LocalOrdinal, GlobalOrdinal, Node >::isContiguous;
  using TpetraMap< LocalOrdinal, GlobalOrdinal, Node >::isDistributed;
  using TpetraMap< LocalOrdinal, GlobalOrdinal, Node >::isCompatible;
  using TpetraMap< LocalOrdinal, GlobalOrdinal, Node >::isSameAs;
  using TpetraMap< LocalOrdinal, GlobalOrdinal, Node >::getComm;

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
  const Teuchos::ArrayRCP< GlobalOrdinal >
  getGlobalShape() const
  {
    return map_->getGlobalShape();
  }

  //! Global dimension value

  //! Returns the global dimension of the problem, excluding ghost
  //! points, along the requested axis.
  inline
  GlobalOrdinal
  getGlobalShape(int axis) const
  {
    return map_->getGlobalShape(axis);
  }

  //! Global dimension values

  //! Returns a \c Teuchos::ArrayRCP containing the global size of the
  //! problem along each axis, including ghost points.
  inline
  const Teuchos::ArrayRCP< GlobalOrdinal >
  getGlobalGhostShape() const
  {
    return map_->getGlobalGhostShape();
  }

  //! Global dimension value

  //! Returns the global dimension of the problem, including ghost
  //! points, along the requested axis.
  inline
  GlobalOrdinal
  getGlobalGhostShape(int axis) const
  {
    return map_->getGlobalGhostShape(axis);
  }

  //! Local dimension values, excluding halos

  //! Returns a \c Teuchos::ArrayRCP containing the local size of the
  //! problem along each axis, excluding halos.
  inline
  const Teuchos::ArrayRCP< LocalOrdinal >
  getLocalOwnShape() const
  {
    return map_->getLocalOwnShape();
  }

  //! Local dimension value, excluding halos

  //! Returns the local dimension of the problem along the requested
  //! axis, excluding halos.
  inline
  LocalOrdinal
  getLocalOwnShape(int axis) const
  {
    return map_->getLocalOwnShape(axis);
  }

  //! Local dimension values

  //! Returns a \c Teuchos::ArrayRCP containing the local size of the
  //! problem along each axis, including halos.
  inline
  const Teuchos::ArrayRCP< LocalOrdinal >
  getLocalShape() const
  {
    return map_->getLocalShape();
  }

  //! Local dimension value

  //! Returns the local dimension of the problem along the requested
  //! axis, including halos.
  inline
  LocalOrdinal
  getLocalShape(int axis) const
  {
    return map_->getLocalShape(axis);
  }

  //! Local interior (non-boundary) loop bounds

  //! Returns a \c Teuchos::ArrayRCP of \c Teuchos::Tuple of 2
  //! LocalOrdinals corresponding to the lower and upper bounds for
  //! looping over interior (non-boundary) elements on each axis.
  inline
  const Teuchos::ArrayRCP< Teuchos::Tuple< LocalOrdinal, 2 > >
  getLocalInteriorBounds() const
  {
    return map_->getLocalInteriorBounds();
  }

  //! Local interior (non-boundary) loop bounds

  //! Returns a Teuchos::Tuple of 2 LocalOrdinals corresponding to the
  //! lower and upper bounds for looping over interior (non-boundary)
  //! elements on the given axis.
  inline
  const Teuchos::Tuple< LocalOrdinal, 2 >
  getLocalInteriorBounds(int axis) const
  {
    return map_->getLocalInteriorBounds(axis);
  }

  //! Starting axis index along each axis

  //! Returns a \c Teuchos::Array::RCP containing the starting global
  //! axis index along each axis.
  inline
  const Teuchos::ArrayRCP< GlobalOrdinal >
  getAxisStart() const
  {
    return map_->getAxisStart();
  }

  //! Starting axis index along requested axis

  //! Returns the starting global axis index along the requested
  //! axis.
  inline
  GlobalOrdinal
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
  const Teuchos::ArrayRCP< GlobalOrdinal >
  getGlobalStrides() const
  {
    return map_->getGlobalStrides();
  }

  //! Global stride information

  //! Returns a \c Teuchos::ArrayRCP containing the stride length
  //! along each axis.
  inline
  GlobalOrdinal
  getGlobalStride(int axis) const
  {
    return map_->getGlobalStride(axis);
  }

  //! Local stride information

  //! Returns a \c Teuchos::ArrayRCP containing the stride length
  //! along each axis.
  inline
  const Teuchos::ArrayRCP< LocalOrdinal >
  getLocalStrides() const
  {
    return map_->getLocalStrides();
  }

  //! Local stride information

  //! Returns a \c Teuchos::ArrayRCP containing the stride length
  //! along each axis.
  inline
  LocalOrdinal
  getLocalStride(int axis) const
  {
    return map_->getLocalStride(axis);
  }

  //! 1D maps along each axis

  //! Returns a \c Teuchos::ArrayRCP containing a 1D \c Xpetra::Map
  //! along each axis, representing the decomposition of that axis
  //! index along that axis.
  inline
  const Teuchos::ArrayRCP< Teuchos::RCP< const Xpetra::Map< LocalOrdinal,
                                                            GlobalOrdinal,
                                                            Node > > >
  getAxisMaps() const
  {
    return axisMaps_;
  }

  //! 1D map along requested axis

  //! Returns a 1D \c Xpetra::Map along the requested axis,
  //! representing the decomposition of that axis index along that
  //! axis.
  inline
  const Teuchos::RCP< const Xpetra::Map< LocalOrdinal, GlobalOrdinal, Node > >
  getAxisMap(int axis) const
  {
    return axisMaps_[axis];
  }

  //////////////////////
  // Indexing methods //
  //////////////////////

  //! Convert a global index into an array of global axis indexes
  inline Teuchos::Array< GlobalOrdinal >
  getGlobalAxisIndex(const GlobalOrdinal globalIndex) const
  {
    return map_->getGlobalAxisIndex(globalIndex);
  }

  //! Convert a local index into an array of local axis indexes

  //! Note that the local origin (0,0,...) refers to the index of the
  //! first element of the interior, or non-halo region.
  inline Teuchos::Array< LocalOrdinal >
  getLocalAxisIndex(const LocalOrdinal localIndex) const
  {
    return map_->getLocalAxisIndex(localIndex);
  }

  //! Convert a local index into a global index
  inline GlobalOrdinal
  getGlobalElement(LocalOrdinal localIndex) const
  {
    return map_->getGlobalElement(localIndex);
  }

  //! Convert an array of global axis indexes into a global index
  inline GlobalOrdinal
  getGlobalElement(const Teuchos::ArrayView< const GlobalOrdinal >
                     globalAxisIndex) const
  {
    return map_->getGlobalElement(globalAxisIndex);
  }

  //! Convert a global index into a local index
  inline LocalOrdinal
  getLocalElement(GlobalOrdinal globalIndex) const
  {
    return map_->getLocalElement(globalIndex);
  }

  //! Convert an array of local axis indexes into a local index

  //! Note that the local origin (0,0,...) refers to the index of the
  //! first element of the interior, or non-halo region.
  inline LocalOrdinal
  getLocalElement(const Teuchos::ArrayView< const LocalOrdinal >
                    localAxisIndex) const
  {
    return map_->getLocalElement(localAxisIndex);
  }

  //! @name Xpetra specific
  //@{

  //! TpetraMDMap constructor to wrap a Tpetra::MDMap object
  TpetraMDMap(const Teuchos::RCP< const
                                  Tpetra::MDMap< LocalOrdinal,
                                                 GlobalOrdinal,
                                                 Node > > & map);

  //! Get the library used by this object (Tpetra or Epetra?)
  UnderlyingLib lib() const
  {
    return Xpetra::UseTpetra;
  }

  //! Get the underlying Tpetra map
  const RCP< const Tpetra::MDMap<LocalOrdinal, GlobalOrdinal, Node> > &
  getTpetra_MDMap() const
  {
    return map_;
  }

  //@}

private:

  // Private static method for constructing and storing a reference
  // counted pointer to a Tpetra::MDMap.  This allows the
  // Xpetra::TpetraMDMap constructors to construct a map and
  // provide it to the Xpetra::TpetraMap base class as the first step
  // in the constructor process.
  static RCP< const Tpetra::MDMap< LocalOrdinal, GlobalOrdinal, Node > >
  computeMDMap(const Teuchos::RCP< const Teuchos::Comm< int > > & comm,
               const Teuchos::ArrayView< GlobalOrdinal > & globalShape,
               const Teuchos::ArrayView< int > & axisNumProc,
               const Teuchos::ArrayView< int > & halos,
               const Teuchos::ArrayView< int > & ghostPoints,
               const Teuchos::ArrayView< int > & periodic,
               const Teuchos::RCP< Node >      & node);

  // Private method to convert the MDMap's axis Maps from
  // pointers to Tpetra::Maps to pointers to Xpetra::Maps.
  void convertAxisMaps();

  // Static variable that allows the computeMDMap method store
  // a reference counted pointer to a Tpetra::MDMap.
  static RCP< const Tpetra::MDMap< LocalOrdinal,
                                   GlobalOrdinal,
                                   Node > > temp_map_;

  // Reference counted pointer to the underlying Tpetra::MDMap.
  const RCP< const Tpetra::MDMap< LocalOrdinal,
                                  GlobalOrdinal,
                                  Node > > map_;

  // An array of the MDMap's axis maps, cast to Xpetra::Maps
  Teuchos::ArrayRCP< RCP< const Xpetra::Map< LocalOrdinal,
                                             GlobalOrdinal,
                                             Node > > > axisMaps_;

};  // TpetraMDMap class

/////////////////////
// Implementations //
/////////////////////

// Conversion functions
template <class LocalOrdinal, class GlobalOrdinal, class Node>
const Tpetra::MDMap< LocalOrdinal, GlobalOrdinal, Node > &
toTpetra(const Xpetra::MDMap< LocalOrdinal, GlobalOrdinal, Node> & map)
{
  const TpetraMDMap< LocalOrdinal,
                     GlobalOrdinal,
                     Node> & tpetraMDMap =
    dynamic_cast< const TpetraMDMap< LocalOrdinal,
                                     GlobalOrdinal,
                                     Node > & >(map);
  return *tpetraMDMap.getTpetra_MDMap();
}

template <class LocalOrdinal, class GlobalOrdinal, class Node>
const RCP< const Tpetra::MDMap< LocalOrdinal, GlobalOrdinal, Node > > &
toTpetra(const RCP< const MDMap< LocalOrdinal,
                                 GlobalOrdinal,
                                 Node > > & map)
{
  typedef TpetraMDMap< LocalOrdinal, GlobalOrdinal, Node >
    TpetraMDMapClass;
  XPETRA_RCP_DYNAMIC_CAST(const TpetraMDMapClass, map,
                          tpetraMDMap, "toTpetra");
  return tpetraMDMap->getTpetra_MDMap();
}

template <class LocalOrdinal, class GlobalOrdinal, class Node>
const RCP< const MDMap< LocalOrdinal, GlobalOrdinal, Node > >
toXpetra(const RCP< const Tpetra::MDMap< LocalOrdinal,
                                         GlobalOrdinal,
                                         Node > > & map)
{
  return rcp(new TpetraMDMap< LocalOrdinal, GlobalOrdinal, Node >(map));
}

// Static variable
template <class LocalOrdinal, class GlobalOrdinal, class Node>
Teuchos::RCP< const Tpetra::MDMap< LocalOrdinal, GlobalOrdinal, Node > >
TpetraMDMap< LocalOrdinal, GlobalOrdinal, Node >::temp_map_ =
  Teuchos::RCP< const Tpetra::MDMap< LocalOrdinal,
                                     GlobalOrdinal,
                                     Node > >();

// N-dimensional constructor
template <class LocalOrdinal, class GlobalOrdinal, class Node>
TpetraMDMap< LocalOrdinal, GlobalOrdinal, Node >::
TpetraMDMap(const Teuchos::RCP< const Teuchos::Comm< int > > & comm,
            const Teuchos::ArrayView< GlobalOrdinal > & globalShape,
            const Teuchos::ArrayView< int > & axisNumProc,
            const Teuchos::ArrayView< int > & halos,
            const Teuchos::ArrayView< int > & ghostPoints,
            const Teuchos::ArrayView< int > & periodic,
            const Teuchos::RCP< Node >      & node) :
  TpetraMap< LocalOrdinal, GlobalOrdinal, Node >
  (Teuchos::rcp_static_cast< const Tpetra::Map< LocalOrdinal,
                                                GlobalOrdinal,
                                                Node > >
   (computeMDMap(comm,
                 globalShape,
                 axisNumProc,
                 halos,
                 ghostPoints,
                 periodic,
                 node))),
  map_(temp_map_)
{
  temp_map_ = RCP< const Tpetra::MDMap< LocalOrdinal,
                                        GlobalOrdinal,
                                        Node > >();
  convertAxisMaps();
}

// 2 dimensional constructor
template< class LocalOrdinal, class GlobalOrdinal, class Node >
TpetraMDMap< LocalOrdinal, GlobalOrdinal, Node >::
TpetraMDMap(const Teuchos::RCP< const Teuchos::Comm< int > > & comm,
            const GlobalOrdinal globalNum_i,
            const GlobalOrdinal globalNum_j,
            const int           numProc_i,
            const int           numProc_j,
            const int           halo_i,
            const int           halo_j,
            const int           ghostPoints_i,
            const int           ghostPoints_j,
            const int           periodic_i,
            const int           periodic_j,
            const Teuchos::RCP< Node > & node) :
  TpetraMap< LocalOrdinal, GlobalOrdinal, Node >
  (Teuchos::rcp_static_cast< const Tpetra::Map< LocalOrdinal,
                                                GlobalOrdinal,
                                                Node > >
   (computeMDMap(comm,
                 tuple(globalNum_i,globalNum_j),
                 tuple(numProc_i,numProc_j),
                 tuple(halo_i,halo_j),
                 tuple(ghostPoints_i,ghostPoints_j),
                 tuple(periodic_i,periodic_j),
                 node))),
  map_(temp_map_)
{
  temp_map_ = RCP< const Tpetra::MDMap< LocalOrdinal,
                                        GlobalOrdinal,
                                        Node > >();
  convertAxisMaps();
}

// RCP constructor
template <class LocalOrdinal, class GlobalOrdinal, class Node>
TpetraMDMap< LocalOrdinal, GlobalOrdinal, Node >::
TpetraMDMap(const Teuchos::RCP< const
                                Tpetra::MDMap< LocalOrdinal,
                                               GlobalOrdinal,
                                               Node > > & map) :
  TpetraMap< LocalOrdinal, GlobalOrdinal, Node >
  (static_cast< const TpetraMap< LocalOrdinal,
                                 GlobalOrdinal,
                                 Node > >(*map)),
  map_(map)
{
  convertAxisMaps();
}

//////////////////////////////////////////////////////////////////////

template <class LocalOrdinal, class GlobalOrdinal, class Node>
Teuchos::RCP< const Tpetra::MDMap< LocalOrdinal, GlobalOrdinal, Node> >
TpetraMDMap< LocalOrdinal, GlobalOrdinal, Node >::
computeMDMap(const Teuchos::RCP< const Teuchos::Comm< int > > & comm,
             const Teuchos::ArrayView< GlobalOrdinal > & globalShape,
             const Teuchos::ArrayView< int > & axisNumProc,
             const Teuchos::ArrayView< int > & halos,
             const Teuchos::ArrayView< int > & ghostPoints,
             const Teuchos::ArrayView< int > & periodic,
             const Teuchos::RCP< Node >      & node)
{
  temp_map_ =
    Teuchos::rcp(new Tpetra::MDMap< LocalOrdinal,
                                    GlobalOrdinal,
                                    Node >(comm,
                                           globalShape,
                                           axisNumProc,
                                           halos,
                                           ghostPoints,
                                           periodic,
                                           node));
  return temp_map_;
}

//////////////////////////////////////////////////////////////////////

template <class LocalOrdinal, class GlobalOrdinal, class Node>
void
TpetraMDMap< LocalOrdinal, GlobalOrdinal, Node >::
convertAxisMaps()
{
  axisMaps_.resize(map_->getNumDims());
  for (int i=0; i < axisMaps_.size(); ++i)
    axisMaps_[i] = toXpetra(map_->getAxisMap(i));
}

}  // Xpetra namespace

#endif
