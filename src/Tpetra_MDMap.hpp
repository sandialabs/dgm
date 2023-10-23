#ifndef TPETRA_MDMAP_HPP
#define TPETRA_MDMAP_HPP

//! \file   Tpetra_MDMap.hpp
//! \brief  Tpetra MDMap declaration and implementation
//! \author Bill Spotz

// System includes
#include <algorithm>

// boost includes
#include "boost/numeric/conversion/cast.hpp"

// Teuchos includes
#include "Teuchos_Tuple.hpp"

// Tpetra includes
#include "Tpetra_Map.hpp"
using Tpetra::global_size_t;

//////////////////////////////////////////////////////////////////
//
// \todo Const-correctness for methods and member variables
// \todo Teuchos::ParameterList constructor
// \todo Non-member constructors?  Concrete dimensionality sub-classes?
// \todo Array bounds checking in TPETRA_ARRAY_BOUNDS_CHECK mode
//
//////////////////////////////////////////////////////////////////

/// Extensions to Tpetra
namespace Tpetra
{

//! A class for partitioning distributed multidimensional objects

//! This class inherits from \c Tpetra::Map, and maintains the same
//! templating structure.  It is intended to decompose MD entities,
//! such as coordinates and fields that are represented on MD meshes.

//! By inheriting from \c Tpetra::Map, it can be used wherever a \c
//! Tpetra::Map can be used and maintains the paradigm of mapping
//! between single-dimension local and global IDs.  However, the \c
//! MDMap class assumes that the data being indexed can be expressed
//! as an N-dimensional array (where N is arbitrary), and so axis
//! indexing is also supported.

//! A note about terminology: within the \c MDMap class, it is common
//! to have related one-dimensional and N-dimensional indexing
//! concepts.  In these situations, the prefix "axis" is intended to
//! signify reference to an N-dimensional index.  For example, the
//! method \c getGlobalAxisIndex() will return an N-dimensional index.

//! The \c MDMap class adds the capability of axis indexing
//! (i.e. N-dimensional indexing) to local data, global data, and
//! processor ranks.  This last feature enables to user to specify how
//! many processors are assigned to each axis, with the restriction
//! that the product of all axis processor counts equal the total
//! number of processors.

//! Halos are also supported.  Halo regions represent overlap regions,
//! and with proper communication, allow the local processing node to
//! access copies of remote data.  If all halos are zero, then the \c
//! MDMap is one-to-one and each processor "owns" all of its global
//! IDs.  A halo value along each axis can be specified at
//! construction, but two values are ultimately stored on each
//! processor, because halos at boundaries will be set to zero.

//! NB: a local axis index of (0,0,...), i.e. the local origin, refers
//! to the first element of the non-halo region.  Equivalently, it
//! refers to the first element of the locally-owned data.  This means
//! that the user can use negative indexes to reference the
//! lower-boundary halo region.

//! \c MDMap also provides an array of 1D \c Tpetra::Map objects, one
//! along each axis, representing the decomposition along that axis.

template< class LocalOrdinal,
          class GlobalOrdinal = LocalOrdinal,
          class Node = KokkosClassic::DefaultNode::DefaultNodeType >
class MDMap : public Tpetra::Map< LocalOrdinal, GlobalOrdinal, Node >
{

public:

  /////////////////
  // Constructors
  /////////////////

  //! N-dimensional Constructor

  //! The N-dimensional constructor utilizes \c Teuchos::ArrayView to
  //! provide the required global shape and optional axis number of
  //! processors and halos.  In practice, users can utilize the
  //! Teuchos::Tuple class to specify these quantities.  The
  //! dimensionality of the \c MDMap is determined by the number of
  //! elements in argument \c globalShape.  Arguments \c axisNumProc
  //! and \c halos can be underspecified, with logical defaults
  //! automatically substituted.
  MDMap(const Teuchos::RCP< const Teuchos::Comm< int > > & comm,
        const Teuchos::ArrayView< GlobalOrdinal > & globalShape,
        const Teuchos::ArrayView< int > & axisNumProc = Teuchos::ArrayView< int >(),
        const Teuchos::ArrayView< int > & halos = Teuchos::ArrayView< int >(),
        const Teuchos::ArrayView< int > & ghostPoints = Teuchos::ArrayView< int >(),
        const Teuchos::ArrayView< int > & periodic = Teuchos::ArrayView< int >(),
        const Teuchos::RCP< Node > & node = Teuchos::RCP< Node >());

  //! 2D Constructor

  //! The 2D constructor creates a map for two-dimensional data and
  //! only requires that the number of indexes in the i and j
  //! directions be specified.  Optional arguments include the number
  //! of processors along the i and j axes, as well as the halos in
  //! the i and j directions.
  MDMap(const Teuchos::RCP< const Teuchos::Comm< int > > & comm,
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
        const Teuchos::RCP< Node > & node = Teuchos::RCP< Node >());

  //! Copy Constructor
  MDMap(const MDMap< LocalOrdinal, GlobalOrdinal, Node > & source);

  //! Destructor
  ~MDMap() { }

  ///////////////
  // Operators //
  ///////////////

  //! Assignment operator
  MDMap< LocalOrdinal, GlobalOrdinal, Node >&
  operator=(const MDMap< LocalOrdinal, GlobalOrdinal, Node >& rhs);

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
    return _numDims;
  }

  //! Global dimension values

  //! Returns a \c Teuchos::ArrayRCP containing the global size of the
  //! problem along each axis, excluding ghost points.
  inline
  const Teuchos::ArrayRCP< GlobalOrdinal >
  getGlobalShape() const
  {
    return _globalShape;
  }

  //! Global dimension value

  //! Returns the global dimension of the problem, excluding ghost
  //! points, along the requested axis.
  inline
  GlobalOrdinal
  getGlobalShape(int axis) const
  {
    return _globalShape[axis];
  }

  //! Global dimension values

  //! Returns a \c Teuchos::ArrayRCP containing the global size of the
  //! problem along each axis, including ghost points.
  inline
  const Teuchos::ArrayRCP< GlobalOrdinal >
  getGlobalGhostShape() const
  {
    return _globalGhostShape;
  }

  //! Global dimension value

  //! Returns the global dimension of the problem, including ghost
  //! points, along the requested axis.
  inline
  GlobalOrdinal
  getGlobalGhostShape(int axis) const
  {
    return _globalGhostShape[axis];
  }

  //! Local dimension values, excluding halos

  //! Returns a \c Teuchos::ArrayRCP containing the local size of the
  //! problem along each axis, excluding halos.
  inline
  const Teuchos::ArrayRCP< LocalOrdinal >
  getLocalOwnShape() const
  {
    return _localOwnShape;
  }

  //! Local dimension value, excluding halos

  //! Returns the local dimension of the problem along the requested
  //! axis, excluding halos.
  inline
  LocalOrdinal
  getLocalOwnShape(int axis) const
  {
    return _localOwnShape[axis];
  }

  //! Local dimension values

  //! Returns a \c Teuchos::ArrayRCP containing the local size of the
  //! problem along each axis, including halos.
  inline
  const Teuchos::ArrayRCP< LocalOrdinal >
  getLocalShape() const
  {
    return _localShape;
  }

  //! Local dimension value

  //! Returns the local dimension of the problem along the requested
  //! axis, including halos.
  inline
  LocalOrdinal
  getLocalShape(int axis) const
  {
    return _localShape[axis];
  }

  //! Local interior (non-boundary) loop bounds

  //! Returns a \c Teuchos::ArrayRCP of \c Teuchos::Tuple of 2
  //! LocalOrdinals corresponding to the lower and upper bounds for
  //! looping over interior (non-boundary) elements on each axis.
  inline
  const Teuchos::ArrayRCP< Teuchos::Tuple< LocalOrdinal, 2 > >
  getLocalInteriorBounds() const
  {
    return _localInteriorBounds;
  }

  //! Local interior (non-boundary) loop bounds

  //! Returns a Teuchos::Tuple of 2 LocalOrdinals corresponding to the
  //! lower and upper bounds for looping over interior (non-boundary)
  //! elements on the given axis.
  inline
  const Teuchos::Tuple< LocalOrdinal, 2 >
  getLocalInteriorBounds(int axis) const
  {
    return _localInteriorBounds[axis];
  }

  //! Starting axis index along each axis

  //! Returns a \c Teuchos::Array::RCP containing the starting global
  //! axis index along each axis.
  inline
  const Teuchos::ArrayRCP< GlobalOrdinal >
  getAxisStart() const
  {
    return _axisStart;
  }

  //! Starting axis index along requested axis

  //! Returns the starting global axis index along the requested
  //! axis.
  inline
  GlobalOrdinal
  getAxisStart(int axis) const
  {
    return _axisStart[axis];
  }

  //! Processor partitions

  //! Returns a \c Teuchos::ArrayRCP containing the number of
  //! processors assigned along each axis.
  inline
  const Teuchos::ArrayRCP< int >
  getAxisNumProcs() const
  {
    return _axisNumProcs;
  }

  //! Processor partition

  //! Returns the number of processors assigned along the requested
  //! axis.
  inline
  int
  getAxisNumProcs(int axis) const
  {
    return _axisNumProcs[axis];
  }

  //! Processor axis ranks

  //! Returns a \c Teuchos::ArrayRCP containing the axis processor
  //! ranks along each axis for the local processor.
  inline
  const Teuchos::ArrayRCP< int >
  getAxisRanks() const
  {
    return _axisRanks;
  }

  //! Processor axis rank

  //! Returns the axis processor rank along the requested axis for the
  //! local processor.
  inline
  int
  getAxisRank(int axis) const
  {
    return _axisRanks[axis];
  }

  //! Halo sizes for each axis

  //! Returns a \c Teuchos::ArrayRCP containing a \c Teuchos::Tuple
  //! along each axis that contains the upper and lower halo values.
  inline
  const Teuchos::ArrayRCP< Teuchos::Tuple< int, 2 > >
  getHalos() const
  {
    return _halos;
  }

  //! Halo sizes for requested axis

  //! Returns a \c Teuchos::Tuple along the requeseted axis that
  //! contains the upper and lower halo values.
  inline
  const Teuchos::Tuple< int, 2 >
  getHalos(int axis) const
  {
    return _halos[axis];
  }

  //! Halo presence

  //! Returns true if map has any non-zero halos
  bool
  hasHalos() const;

  //! Nominal halos

  //! Returns an array of the requested halo size along each axis,
  //! regardless of the presence of boundaries
  Teuchos::ArrayRCP< int >
  getNominalHalos() const;

  //! Ghost points

  //! Returns an array of integers indicating the number of ghost
  //! points to be used on each axis.
  inline
  Teuchos::ArrayRCP< int >
  getGhostPoints() const
  {
    return _ghostPoints;
  }

  //! Ghost points for requested axis

  //! Returns an integer indicating the number of ghost points on the
  //! requested axis.
  inline
  int getGhostPoints(int axis) const
  {
    return _ghostPoints[axis];
  }

  //! Periodic flags

  //! Returns an array of integer flags indicating whether each axis
  //! is periodic.
  inline
  Teuchos::ArrayRCP< int >
  getPeriodic() const
  {
    return _periodic;
  }

  //! Periodic flag for requested axis

  //! Returns an integer flag indicating whether the requested axis is
  //! periodic.
  inline
  int
  getPeriodic(int axis) const
  {
    return _periodic[axis];
  }

  //! Global stride information

  //! Returns a \c Teuchos::ArrayRCP containing the stride length
  //! along each axis.
  inline
  const Teuchos::ArrayRCP< GlobalOrdinal >
  getGlobalStrides() const
  {
    return _globalStrides;
  }

  //! Global stride information

  //! Returns a \c Teuchos::ArrayRCP containing the stride length
  //! along each axis.
  inline
  GlobalOrdinal
  getGlobalStride(int axis) const
  {
    return _globalStrides[axis];
  }

  //! Local stride information

  //! Returns a \c Teuchos::ArrayRCP containing the stride length
  //! along each axis.
  inline
  const Teuchos::ArrayRCP< LocalOrdinal >
  getLocalStrides() const
  {
    return _localStrides;
  }

  //! Local stride information

  //! Returns a \c Teuchos::ArrayRCP containing the stride length
  //! along each axis.
  inline
  LocalOrdinal
  getLocalStride(int axis) const
  {
    return _localStrides[axis];
  }

  //! 1D maps along each axis

  //! Returns a \c Teuchos::ArrayRCP containing a 1D \c Tpetra::Map
  //! along each axis, representing the decomposition of that axis
  //! index along that axis.
  inline
  const Teuchos::ArrayRCP< Teuchos::RCP< const Tpetra::Map< LocalOrdinal,
                                                            GlobalOrdinal,
                                                            Node > > >
  getAxisMaps() const
  {
    return _axisMaps;
  }

  //! 1D map along requested axis

  //! Returns a 1D \c Tpetra::Map along the requested axis,
  //! representing the decomposition of that axis index along that
  //! axis.
  inline
  const Teuchos::RCP< const Tpetra::Map< LocalOrdinal, GlobalOrdinal, Node > >
  getAxisMap(int axis) const
  {
    return _axisMaps[axis];
  }

  //////////////////////
  // Indexing methods //
  //////////////////////

  //! Convert a global index into an array of global axis indexes
  Teuchos::Array< GlobalOrdinal >
  getGlobalAxisIndex(const GlobalOrdinal globalIndex) const;

  //! Convert a local index into an array of local axis indexes

  //! Note that the local origin (0,0,...) refers to the index of the
  //! first element of the interior, or non-halo region.
  Teuchos::Array< LocalOrdinal >
  getLocalAxisIndex(const LocalOrdinal LocalIndex) const;

  //! Convert a local index into a global index
  inline GlobalOrdinal
  getGlobalElement(LocalOrdinal localIndex) const
  {
    return Tpetra::Map< LocalOrdinal,
                        GlobalOrdinal,
                        Node >::getGlobalElement(localIndex);
  }

  //! Convert an array of global axis indexes into a global index
  GlobalOrdinal
  getGlobalElement(const Teuchos::ArrayView< const GlobalOrdinal >
                     globalAxisIndex) const;

  //! Convert a global index into a local index
  inline LocalOrdinal
  getLocalElement(GlobalOrdinal globalIndex) const
  {
    return Tpetra::Map< LocalOrdinal,
                        GlobalOrdinal,
                        Node >::getLocalElement(globalIndex);
  }

  //! Convert an array of local axis indexes into a local index

  //! Note that the local origin (0,0,...) refers to the index of the
  //! first element of the interior, or non-halo region.
  LocalOrdinal
  getLocalElement(const Teuchos::ArrayView< const LocalOrdinal >
                    localAxisIndex) const;

private:

  ////////////////////////
  // Private member data
  ////////////////////////

  //! Number of dimensions
  const int _numDims;

  //! Number of global elements along each axis, excluding ghost points
  const Teuchos::ArrayRCP< GlobalOrdinal > _globalShape;

  //! Number of global elements along each axis, including ghost points
  const Teuchos::ArrayRCP< GlobalOrdinal > _globalGhostShape;

  //! Number of local elements along each axis, excluding halos
  const Teuchos::ArrayRCP< LocalOrdinal > _localOwnShape;

  //! Number of local elements along each axis, including halos
  const Teuchos::ArrayRCP< LocalOrdinal > _localShape;

  //! Local loop bounds over interior (non-boundary) elements
  const Teuchos::ArrayRCP< Teuchos::Tuple< LocalOrdinal, 2 > >
    _localInteriorBounds;

  //! Starting axis index along each axis
  const Teuchos::ArrayRCP< GlobalOrdinal > _axisStart;

  //! Number of processors along each axis
  const Teuchos::ArrayRCP< int > _axisNumProcs;

  //! Rank of processor along each axis
  const Teuchos::ArrayRCP< int > _axisRanks;

  //! Actual halo sizes along each axis at each boundary
  const Teuchos::ArrayRCP< Teuchos::Tuple< int, 2 > > _halos;

  //! Ghost points
  const Teuchos::ArrayRCP< int > _ghostPoints;

  //! Periodicity flags
  const Teuchos::ArrayRCP< int > _periodic;

  //! Global striding information
  const Teuchos::ArrayRCP< GlobalOrdinal > _globalStrides;

  //! Local striding information
  const Teuchos::ArrayRCP< LocalOrdinal > _localStrides;

  //! Tpetra::Map along each axis
  const Teuchos::ArrayRCP<
    Teuchos::RCP<
      Tpetra::Map< LocalOrdinal, GlobalOrdinal, Node > > > _axisMaps;

  /////////////////////////////
  // Private static member data
  /////////////////////////////

  // Most of the private member data has to be computed as a
  // prerequisite before the Tpetra::Map base class constructor is
  // called.  However, C++ rules dictate that base classes must be
  // initialized first.  To satisfy both of these requirements, I
  // declare several static member variables whose purpose is to hold
  // these values temporarily until it is OK to initialize the
  // non-static private member data.  Thus, they only hold useful data
  // during the construction process.  As a result, the constructor
  // should null them out as a cleanup process before returning, by
  // calling nullifyStaticData().

  //! Number of dimensions
  static int _temp_numDims;

  //! Number of global elements along each axis
  static Teuchos::ArrayRCP< GlobalOrdinal > _temp_globalShape;

  //! Number of global elements along each axis, including exterior
  //! ghost points
  static Teuchos::ArrayRCP< GlobalOrdinal > _temp_globalGhostShape;

  //! Number of local elements along each axis, excluding halos
  static Teuchos::ArrayRCP< LocalOrdinal > _temp_localOwnShape;

  //! Number of local elements along each axis, including halos
  static Teuchos::ArrayRCP< LocalOrdinal > _temp_localShape;

  //! Local loop bounds over interior (non-boundary) elements
  static Teuchos::ArrayRCP< Teuchos::Tuple< LocalOrdinal, 2 > >
    _temp_localInteriorBounds;

  //! Starting axis index along each axis
  static Teuchos::ArrayRCP< GlobalOrdinal > _temp_axisStart;

  //! Number of processors along each axis
  static Teuchos::ArrayRCP< int > _temp_axisNumProcs;

  //! Rank of processor along each axis
  static Teuchos::ArrayRCP< int > _temp_axisRanks;

  //! Actual halo sizes along each axis at each boundary
  static Teuchos::ArrayRCP< Teuchos::Tuple< int, 2 > > _temp_halos;

  //! Ghost points
  static Teuchos::ArrayRCP< int > _temp_ghostPoints;

  //! Periodicity flags
  static Teuchos::ArrayRCP< int > _temp_periodic;

  //! Global striding information
  static Teuchos::ArrayRCP< GlobalOrdinal > _temp_globalStrides;

  //! Local striding information
  static Teuchos::ArrayRCP< LocalOrdinal > _temp_localStrides;

  //! Array of global ID values for this node
  static Teuchos::ArrayRCP< GlobalOrdinal > _temp_elements_;

  ///////////////////////////
  // Private static functions
  ///////////////////////////

  //! Compute the global elements for the base \c Tpetra::Map class

  //! Static member function computeElements() is called by the
  //! constructor initialization list and returns an array of
  //! GlobalOrdinals that corresponds the the global IDs of the
  //! elements on this processor.  It is the only static member
  //! function called by the Tpetra::Map base class constructor, and
  //! so it sets several temporary static variables used later in the
  //! MDMap constructor initialization list.
  static Teuchos::ArrayView< GlobalOrdinal >
  computeElements(const Teuchos::RCP< const Teuchos::Comm< int > > & comm,
                  const Teuchos::ArrayView< GlobalOrdinal > & globalShape,
                  const Teuchos::ArrayView< int >  & axisNumProc,
                  const Teuchos::ArrayView< int >  & halos,
                  const Teuchos::ArrayView< int >  & ghostPoints,
                  const Teuchos::ArrayView< int > & periodic);

  //! Compute the global shape of the MD data

  //! Static member function computeGlobalShape() is called by
  //! computeElements() and simply computes _temp_globalShape by
  //! converting a Teuchos::ArrayView< GlobalOrdinal > to a
  //! Teuchos::ArrayRCP< GLobalOrdinal >.  This allows the generic
  //! N-dimensional constructor to accept a Teuchos::Tuple of
  //! dimensions, which is the most convenient way to specify a short
  //! array.
  static void
  computeGlobalShape(const Teuchos::ArrayView< GlobalOrdinal > & globalShape);

  //! Compute the number of processors along each axis

  //! Static member function computeAxisNumProcs() is called by
  //! computeElements() and computes _temp_axisNumProcs.  It allows
  //! the user to not specify the number of processors along selected
  //! axes in favor of having them computed automatically.  To compute
  //! the number of axes along an axis automatically, provide a value
  //! <= 0 or use the default value.
  static void
  computeAxisNumProcs(const int numProc,
                      const Teuchos::ArrayView< int > & axisNumProc);

  //! Compute the axis ranks of this processor

  //! Static member function computeAxisRanks() is called by
  //! computeElements() and, given the number of processors along each
  //! axis, computes _temp_axisRanks, an array of axis processor
  //! ranks.  For example in 3D, processor rank 0 -> (0,0,0) and
  //! processor rank 1 -> (1,0,0), etc.
  static void
  computeAxisRanks(const int rank);

  //! Compute the halos along each axis

  //! Static member function computeHalos() is called by
  //! computeElements() and computes _temp_halos, an array of halos
  //! of the correct length.  This allows the user to underspecify the
  //! halos (or not specify them at all) and have those halo values
  //! set to a default value of 0.
  static void
  computeHalos(const Teuchos::ArrayView< int > & halos);

  //! Compute the periodic flags along each axis

  //! Static member function computePeriodic() is called by
  //! computeElements() and computes _temp_periodic, an array of
  //! integer flags specifying whether each axis is periodic.  This
  //! allows the user to underspecify the periodic flags (or not
  //! specify them at all) at the time of construction, and have those
  //! periodic flags be set to a default value of 0 (false).
  static void
  computePeriodic(const Teuchos::ArrayView< int > & periodic);

  //! Compute the ghost point flags along each axis

  //! Static member function computeGhostPoints() is called by
  //! computeElements() and computes _temp_ghostPoints, an array of
  //! integer flags specifying whether each axis supports ghost points
  //! exterior to the domain.  This allows the user to underspecify
  //! the ghost point flags (or not specify them at all) at the time
  //! of construction, and have those ghost point flags be set to a
  //! default value.  The default value is the corresponding
  //! periodicity flag: the ghost point flag must be true if
  //! periodicity is true and is false if the periodicity is false.
  static void
  computeGhostPoints(const Teuchos::ArrayView< int > & ghostPoints);

  //! Compute the index ranges along each axis

  //! Static member function computeAxisRanges() computes the static
  //! arrays _temp_localOwnShape, _temp_localShape,
  //! _temp_localInteriorBounds and _temp_axisStart based upon the
  //! other static temporary variables.
  static void
  computeAxisRanges();

  //! Compute a 1D \c Tpetra::Map along each axis

  //! Static member function computeAxisMaps() is called by the
  //! constructor initialization list and uses _temp_localShape and
  //! _temp_axisStart to return an array of 1D maps that contain a 1D
  //! decomposition along a single axis.
  static Teuchos::ArrayRCP< Teuchos::RCP< Tpetra::Map< LocalOrdinal,
                                                       GlobalOrdinal,
                                                       Node > > >
  computeAxisMaps(const Teuchos::RCP< const Teuchos::Comm< int > > & comm);

  //! Nullify all static data

  //! The constructors all utilize temporary static variables in order
  //! to compute private member data before initializing the
  //! Tpetra::Map base class.  This static function sets all of those
  //! temporary static variables to a null state, to make it clear
  //! that they are not in use.
  static void
  nullifyStaticData();

};


////////////////////////////////////////////////////////////
// Implementations
////////////////////////////////////////////////////////////

// Initialize the temporary static variables to be null or zero
template< class LocalOrdinal, class GlobalOrdinal, class Node >
int
MDMap< LocalOrdinal, GlobalOrdinal, Node >::_temp_numDims = 0;

template< class LocalOrdinal, class GlobalOrdinal, class Node >
Teuchos::ArrayRCP< GlobalOrdinal >
MDMap< LocalOrdinal, GlobalOrdinal, Node >::_temp_globalShape =
  Teuchos::ArrayRCP< GlobalOrdinal >();

template< class LocalOrdinal, class GlobalOrdinal, class Node >
Teuchos::ArrayRCP< GlobalOrdinal >
MDMap< LocalOrdinal, GlobalOrdinal, Node >::_temp_globalGhostShape =
  Teuchos::ArrayRCP< GlobalOrdinal >();

template< class LocalOrdinal, class GlobalOrdinal, class Node >
Teuchos::ArrayRCP< LocalOrdinal >
MDMap< LocalOrdinal, GlobalOrdinal, Node >::_temp_localOwnShape =
  Teuchos::ArrayRCP< LocalOrdinal >();

template< class LocalOrdinal, class GlobalOrdinal, class Node >
Teuchos::ArrayRCP< LocalOrdinal >
MDMap< LocalOrdinal, GlobalOrdinal, Node >::_temp_localShape =
  Teuchos::ArrayRCP< LocalOrdinal >();

template< class LocalOrdinal, class GlobalOrdinal, class Node >
Teuchos::ArrayRCP< Teuchos::Tuple< LocalOrdinal, 2 > >
MDMap< LocalOrdinal, GlobalOrdinal, Node >::_temp_localInteriorBounds =
  Teuchos::ArrayRCP< Teuchos::Tuple< LocalOrdinal, 2 > >();

template< class LocalOrdinal, class GlobalOrdinal, class Node >
Teuchos::ArrayRCP< GlobalOrdinal >
MDMap< LocalOrdinal, GlobalOrdinal, Node >::_temp_axisStart =
  Teuchos::ArrayRCP< GlobalOrdinal >();

template< class LocalOrdinal, class GlobalOrdinal, class Node >
Teuchos::ArrayRCP< int >
MDMap< LocalOrdinal, GlobalOrdinal, Node >::_temp_axisNumProcs =
  Teuchos::ArrayRCP< int >();

template< class LocalOrdinal, class GlobalOrdinal, class Node >
Teuchos::ArrayRCP< int >
MDMap< LocalOrdinal, GlobalOrdinal, Node >::_temp_axisRanks =
  Teuchos::ArrayRCP< int >();

template< class LocalOrdinal, class GlobalOrdinal, class Node >
Teuchos::ArrayRCP< Teuchos::Tuple< int, 2 > >
MDMap< LocalOrdinal, GlobalOrdinal, Node >::_temp_halos =
  Teuchos::ArrayRCP< Teuchos::Tuple< int, 2 > >();

template< class LocalOrdinal, class GlobalOrdinal, class Node >
Teuchos::ArrayRCP< int >
MDMap< LocalOrdinal, GlobalOrdinal, Node >::_temp_ghostPoints =
  Teuchos::ArrayRCP< int >();

template< class LocalOrdinal, class GlobalOrdinal, class Node >
Teuchos::ArrayRCP< int>
MDMap< LocalOrdinal, GlobalOrdinal, Node >::_temp_periodic =
  Teuchos::ArrayRCP< int >();

template< class LocalOrdinal, class GlobalOrdinal, class Node >
Teuchos::ArrayRCP< GlobalOrdinal >
MDMap< LocalOrdinal, GlobalOrdinal, Node >::_temp_globalStrides =
  Teuchos::ArrayRCP< GlobalOrdinal >();

template< class LocalOrdinal, class GlobalOrdinal, class Node >
Teuchos::ArrayRCP< LocalOrdinal >
MDMap< LocalOrdinal, GlobalOrdinal, Node >::_temp_localStrides =
  Teuchos::ArrayRCP< LocalOrdinal >();

template< class LocalOrdinal, class GlobalOrdinal, class Node >
Teuchos::ArrayRCP< GlobalOrdinal >
MDMap< LocalOrdinal, GlobalOrdinal, Node >::_temp_elements_ =
  Teuchos::ArrayRCP< GlobalOrdinal >();

////////////////////////////////////////////////////////////

// N-dimensional Constructor
template< class LocalOrdinal, class GlobalOrdinal, class Node >
MDMap< LocalOrdinal, GlobalOrdinal, Node >::
MDMap(const Teuchos::RCP< const Teuchos::Comm< int > > & comm,
      const Teuchos::ArrayView< GlobalOrdinal > & globalShape,
      const Teuchos::ArrayView< int > & axisNumProc,
      const Teuchos::ArrayView< int > & halos,
      const Teuchos::ArrayView< int > & ghostPoints,
      const Teuchos::ArrayView< int > & periodic,
      const Teuchos::RCP< Node > & ) :
  Tpetra::Map< LocalOrdinal, GlobalOrdinal, Node >
  (Teuchos::OrdinalTraits<global_size_t>::invalid(),
   computeElements(comm, globalShape, axisNumProc, halos, ghostPoints,
                   periodic), 0, comm),
  _numDims(_temp_numDims),
  _globalShape(_temp_globalShape),
  _globalGhostShape(_temp_globalGhostShape),
  _localOwnShape(_temp_localOwnShape),
  _localShape(_temp_localShape),
  _localInteriorBounds(_temp_localInteriorBounds),
  _axisStart(_temp_axisStart),
  _axisNumProcs(_temp_axisNumProcs),
  _axisRanks(_temp_axisRanks),
  _halos(_temp_halos),
  _ghostPoints(_temp_ghostPoints),
  _periodic(_temp_periodic),
  _globalStrides(_temp_globalStrides),
  _localStrides(_temp_localStrides),
  _axisMaps(computeAxisMaps(comm))
{
#ifdef TPETRA_DEBUG
  std::cout << comm->getRank() << ": MDMap constructor ... "
            << "initialization list completed" << std::endl;
#endif
  nullifyStaticData();
}

////////////////////////////////////////////////////////////

// 2D Constructor
template< class LocalOrdinal, class GlobalOrdinal, class Node >
MDMap< LocalOrdinal, GlobalOrdinal, Node >::
MDMap(const Teuchos::RCP< const Teuchos::Comm< int > > & comm,
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
  Tpetra::Map< LocalOrdinal, GlobalOrdinal, Node >
  (Teuchos::OrdinalTraits<global_size_t>::invalid(),
   computeElements(comm,
                   Teuchos::tuple< GlobalOrdinal >(globalNum_i, globalNum_j),
                   Teuchos::tuple< int >(numProc_i, numProc_j),
                   Teuchos::tuple< int >(halo_i, halo_j),
                   Teuchos::tuple< int >(ghostPoints_i, ghostPoints_j),
                   Teuchos::tuple< int >(periodic_i, periodic_j)),
   0, comm),
  _numDims(_temp_numDims),
  _globalShape(_temp_globalShape),
  _globalGhostShape(_temp_globalGhostShape),
  _localOwnShape(_temp_localOwnShape),
  _localShape(_temp_localShape),
  _localInteriorBounds(_temp_localInteriorBounds),
  _axisStart(_temp_axisStart),
  _axisNumProcs(_temp_axisNumProcs),
  _axisRanks(_temp_axisRanks),
  _halos(_temp_halos),
  _ghostPoints(_temp_ghostPoints),
  _periodic(_temp_periodic),
  _globalStrides(_temp_globalStrides),
  _localStrides(_temp_localStrides),
  _axisMaps(computeAxisMaps(comm))
{
  nullifyStaticData();
}

////////////////////////////////////////////////////////////

// Copy Constructor
template< class LocalOrdinal, class GlobalOrdinal, class Node >
MDMap< LocalOrdinal, GlobalOrdinal, Node >::
MDMap(const MDMap< LocalOrdinal, GlobalOrdinal, Node > & source) :
  Tpetra::Map< LocalOrdinal, GlobalOrdinal, Node >(source),
  _numDims(source._numDims),
  _globalShape(source._globalShape),
  _globalGhostShape(source._globalGhostShape),
  _localOwnShape(source._localOwnShape),
  _localShape(source._localShape),
  _localInteriorBounds(source._localInteriorBounds),
  _axisStart(source._axisStart),
  _axisNumProcs(source._axisNumProcs),
  _axisRanks(source._axisRanks),
  _halos(source._halos),
  _ghostPoints(source._ghostPoints),
  _periodic(source._periodic),
  _globalStrides(source._globalStrides),
  _localStrides(source._localStrides),
  _axisMaps(source._axisMaps)
{
}

////////////////////////////////////////////////////////////

// Assignment operator
template< class LocalOrdinal, class GlobalOrdinal, class Node >
MDMap< LocalOrdinal, GlobalOrdinal, Node > &
MDMap< LocalOrdinal, GlobalOrdinal, Node >::
operator=(const MDMap< LocalOrdinal, GlobalOrdinal, Node >& rhs)
{
  // Check for assignment to self
  if (this == &rhs) return *this;
  // Copy rhs to *this and return
  *this = rhs;
  return *this;
}

////////////////////////////////////////////////////////////

// Halo presence
template< class LocalOrdinal, class GlobalOrdinal, class Node >
bool
MDMap< LocalOrdinal, GlobalOrdinal, Node >::
hasHalos() const
{
  for (int i=0; i < _numDims; ++i)
  {
    if (_halos[i][0] > 0) return true;
    if (_halos[i][1] > 0) return true;
  }
  return false;
}

////////////////////////////////////////////////////////////

// Nominal halos
template< class LocalOrdinal, class GlobalOrdinal, class Node >
Teuchos::ArrayRCP< int >
MDMap< LocalOrdinal, GlobalOrdinal, Node >::
getNominalHalos() const
{
  Teuchos::ArrayRCP< int > result = Teuchos::ArrayRCP< int >(_numDims);
  for (int i = 0; i < _numDims; ++i)
    result[i] = std::max(_halos[i][0], _halos[i][1]);
  return result;
}

////////////////////////////////////////////////////////////

// Convert a global index into an array of global axis indexes
template< class LocalOrdinal, class GlobalOrdinal, class Node >
Teuchos::Array< GlobalOrdinal >
MDMap< LocalOrdinal, GlobalOrdinal, Node >::
getGlobalAxisIndex(const GlobalOrdinal globalIndex) const
{
  Teuchos::Array< GlobalOrdinal > result(_numDims);
  GlobalOrdinal reducedIndex = globalIndex;
  for (int i = _numDims - 1; i >= 0; --i)
  {
    result[i] = reducedIndex / _globalStrides[i];
    reducedIndex -= result[i] * _globalStrides[i];
    if (!_periodic[i]) result[i] -= _ghostPoints[i];
  }
  return result;
}

////////////////////////////////////////////////////////////

// Convert a local index into an array of local axis indexes
template< class LocalOrdinal, class GlobalOrdinal, class Node >
Teuchos::Array< LocalOrdinal >
MDMap< LocalOrdinal, GlobalOrdinal, Node >::
getLocalAxisIndex(const LocalOrdinal localIndex) const
{
  Teuchos::Array< LocalOrdinal > result(_numDims);
  LocalOrdinal reducedIndex = localIndex;
  for (int i = _numDims - 1; i >= 0; --i)
  {
    result[i] = reducedIndex / _localStrides[i];
    reducedIndex -= result[i] * _localStrides[i];
    result[i] -= _halos[i][0];
  }
  return result;
}

////////////////////////////////////////////////////////////

// Convert an array of global axis indexes into a global index
template< class LocalOrdinal, class GlobalOrdinal, class Node >
GlobalOrdinal
MDMap< LocalOrdinal, GlobalOrdinal, Node >::
getGlobalElement(const Teuchos::ArrayView< const GlobalOrdinal >
                   globalAxisIndex) const
{
  if (globalAxisIndex.size() != _numDims)
    throw std::invalid_argument("Number of global axis indexes does not match "
                                "MDMap dimensionality");
  GlobalOrdinal result = 0;
  GlobalOrdinal offset = 0;
  for (int i = 0; i < _numDims; ++i)
  {
    offset = (_periodic[i]) ? 0 : _ghostPoints[i];
    result += (globalAxisIndex[i] + offset) * _globalStrides[i];
  }
  return result;
}

////////////////////////////////////////////////////////////

// Convert an array of local axis indexes into a local index
template< class LocalOrdinal, class GlobalOrdinal, class Node >
LocalOrdinal
MDMap< LocalOrdinal, GlobalOrdinal, Node >::
getLocalElement(const Teuchos::ArrayView< const LocalOrdinal >
                  localAxisIndex) const
{
  if (localAxisIndex.size() != _numDims)
    throw std::invalid_argument("Number of local axis indexes does not match "
                                "MDMap dimensionality");
  LocalOrdinal result = 0;
  for (int i = 0; i < _numDims; ++i)
    result += (localAxisIndex[i] + _halos[i][0]) * _localStrides[i];
  return result;
}

////////////////////////////
// Private static methods //
////////////////////////////

////////////////////////////////////////////////////////////

template< class LocalOrdinal, class GlobalOrdinal, class Node >
Teuchos::ArrayView< GlobalOrdinal >
MDMap< LocalOrdinal, GlobalOrdinal, Node >::
computeElements(const Teuchos::RCP< const Teuchos::Comm< int > > & comm,
                const Teuchos::ArrayView< GlobalOrdinal > & globalShape,
                const Teuchos::ArrayView< int > & axisNumProc,
                const Teuchos::ArrayView< int > & halos,
                const Teuchos::ArrayView< int > & ghostPoints,
                const Teuchos::ArrayView< int > & periodic)
{
  //
  // Set the temporary static variables
  _temp_numDims = boost::numeric_cast<int>(globalShape.size());
  computeGlobalShape(globalShape);
  computeAxisNumProcs(comm->getSize(), axisNumProc);
  computeAxisRanks(comm->getRank());
  computeHalos(halos);
  computePeriodic(periodic);
  computeGhostPoints(ghostPoints);
  computeAxisRanges();
  //
  // Allocate arrays for the temporary strides
  _temp_globalStrides = Teuchos::ArrayRCP< GlobalOrdinal >(_temp_numDims);
  _temp_localStrides  = Teuchos::ArrayRCP< LocalOrdinal  >(_temp_numDims);
  //
  // Compute the total size and the stride values
  GlobalOrdinal globalSize = 1;
  LocalOrdinal  localSize  = 1;
  for (int i = 0; i < _temp_numDims; ++i)
  {
    _temp_globalStrides[i] = globalSize;
    _temp_localStrides[i]  = localSize;
    if (_temp_periodic[i])
      globalSize *= _temp_globalShape[i];
    else
      globalSize *= _temp_globalGhostShape[i];
    localSize *= _temp_localShape[i];
    // Note that upon exit, localSize is the size of the local buffer
  }
  //
  // Compute the global indexing offset due to non-periodic ghost points
  GlobalOrdinal offset = 0;
  for (int i = 0; i < _temp_numDims; ++i)
    if (!_temp_periodic[i])
      offset += _temp_ghostPoints[i] * _temp_globalStrides[i];
  //
  // Allocate the index array and initialize it with the appropriate
  // starting values
  Teuchos::Array< GlobalOrdinal > index(_temp_numDims);
  for (int j = 0; j < _temp_numDims; ++j)
    index[j] = -_temp_halos[j][0];
  // Allocate the result array and initialize it with the starting
  // offset value
  _temp_elements_ = Teuchos::ArrayRCP< GlobalOrdinal >(localSize, offset);
  //
  // Loop over all of the local elements
  for (LocalOrdinal i = 0; i < localSize; ++i)
  {
    // Compute _temp_elements_[i]
    for (int j = 0; j < _temp_numDims; ++j)
      _temp_elements_[i] += (_temp_axisStart[j] + index[j]) *
                             _temp_globalStrides[j];
    // Adjust for periodic boundaries
    for (int j = 0; j < _temp_numDims; ++j)
      if (_temp_periodic[j])
      {
        if (_temp_axisRanks[j] == 0 && index[j] < 0)
          _temp_elements_[i] += _temp_globalStrides[j] * _temp_globalShape[j];
        if (_temp_axisRanks[j] == _temp_axisNumProcs[j] - 1 &&
            index[j] >= _temp_localOwnShape[j])
          _temp_elements_[i] -= _temp_globalStrides[j] * _temp_globalShape[j];
      }
    //
    // Increment the index array
    int dim = 0;
    bool done = false;
    while (not done)
    {
      index[dim]++;
      done = (index[dim] < _temp_localOwnShape[dim] + _temp_halos[dim][1]);
      if (not done)
      {
          index[dim] = -_temp_halos[dim][0];
          dim++;
          done = (dim >= _temp_numDims);
      }
    }
  }

#ifdef TPETRA_DEBUG
  std::stringstream filename;
  filename << "elements." << comm->getRank();
  std::ofstream ofile(filename.str().c_str());
  for (int i = 0; i < _temp_elements_.size();  ++i)
    ofile << _temp_elements_[i] << std::endl;
  ofile.close();
#endif

  return _temp_elements_();
}

////////////////////////////////////////////////////////////

template< class LocalOrdinal, class GlobalOrdinal, class Node >
void
MDMap< LocalOrdinal, GlobalOrdinal, Node >::
computeGlobalShape(const Teuchos::ArrayView< GlobalOrdinal > & globalShape)
{
  _temp_globalShape = Teuchos::ArrayRCP< GlobalOrdinal >(globalShape.size());
  for (int i=0; i < globalShape.size(); ++i)
    _temp_globalShape[i] = globalShape[i];
}

////////////////////////////////////////////////////////////

template< class LocalOrdinal, class GlobalOrdinal, class Node >
void
MDMap< LocalOrdinal, GlobalOrdinal, Node >::
computeAxisNumProcs(const int numProc,
                    const Teuchos::ArrayView< int > & axisNumProc)
{
  int block = 1;
  int numUnspecified = 0;
  _temp_axisNumProcs = Teuchos::ArrayRCP< int >(_temp_numDims);
  for (int i=0; i < _temp_numDims; ++i)
  {
    // Copy axisNumProc to _temp_axisNumProcs; if the axisNumProc
    // array size is too small, initialize the _temp_axisNumProcs
    // element as an unspecified processor partition
    if (i < axisNumProc.size())
      _temp_axisNumProcs[i] = axisNumProc[i];
    else
      _temp_axisNumProcs[i] = -1;
    // For specified processor partitions, include the number of
    // processors in the block product; else increment the unspecified
    // counter
    if (_temp_axisNumProcs[i] > 0)
      block *= _temp_axisNumProcs[i];
    else
      numUnspecified += 1;
  }
  // If all processor counts are specified, check the processor block
  // against the total number of processors and return
  if (numUnspecified == 0)
  {
    if (block != numProc)
      throw std::invalid_argument("Product of axis processors does not "
                                  "equal total processors");
    return;
  }
  // For underspecified processor partitions, give the remainder to
  // the first unspecified axis and set all the rest to 1
  if (numProc % block)
    throw std::invalid_argument("Number of processors do not divide evenly");
  int quotient = numProc / block;
  for (int i=0; i < _temp_axisNumProcs.size(); ++i)
  {
    if (_temp_axisNumProcs[i] < 0)
    {
      _temp_axisNumProcs[i] = quotient;
      quotient = 1;
    }
  }

#ifdef TPETRA_DEBUG
  std::cout << std::endl << "MDMap::computeAxisNumProcs(): "
            << _temp_axisNumProcs() << std::endl;
#endif

}

////////////////////////////////////////////////////////////

template< class LocalOrdinal, class GlobalOrdinal, class Node >
void
MDMap< LocalOrdinal, GlobalOrdinal, Node >::
computeAxisRanks(const int rank)
{
  int myRank = rank;
  _temp_axisRanks = Teuchos::ArrayRCP< int >(_temp_axisNumProcs.size());
  int numProc = 1;
  for (int i=0; i < _temp_axisNumProcs.size(); ++i)
    numProc *= _temp_axisNumProcs[i];
  const int _temp_axisRanks_size = boost::numeric_cast<int>(_temp_axisRanks.size());
  for (int i = _temp_axisRanks_size-1; i >= 0; --i)
  {
    numProc /= _temp_axisNumProcs[i];
    _temp_axisRanks[i] = myRank / numProc;
    myRank = myRank % numProc;
  }

#ifdef TPETRA_DEBUG
  std::cout << std::endl << "MDMap::computeAxisRanks(): " << rank << " => "
            << _temp_axisRanks() << std::endl;
#endif

}

////////////////////////////////////////////////////////////

template< class LocalOrdinal, class GlobalOrdinal, class Node >
void
MDMap< LocalOrdinal, GlobalOrdinal, Node >::
computeHalos(const Teuchos::ArrayView< int > & halos)
{
  _temp_halos =
    Teuchos::ArrayRCP< Teuchos::Tuple< int, 2 > >(_temp_numDims,
                                                  Teuchos::tuple< int >(0,0));
  for (int i=0; i < std::min(_temp_halos.size(), halos.size()); ++i)
  {
    _temp_halos[i][0]  = halos[i];
    _temp_halos[i][1]  = halos[i];
  }

#ifdef TPETRA_DEBUG
  std::cout << std::endl << "MDMap::computeHalos(): temp halos = " << _temp_halos()
            << std::endl;
#endif

}

////////////////////////////////////////////////////////////

template< class LocalOrdinal, class GlobalOrdinal, class Node >
void
MDMap< LocalOrdinal, GlobalOrdinal, Node >::
computePeriodic(const Teuchos::ArrayView< int > & periodic)
{
  _temp_periodic = Teuchos::ArrayRCP< int >(_temp_numDims, 0);
  for (int i = 0; i < std::min(_temp_periodic.size(), periodic.size()); ++i)
      _temp_periodic[i]  = periodic[i];

#ifdef TPETRA_DEBUG
  std::cout << std::endl << "MDMap::computePeriodic(): temp periodic = "
            << _temp_periodic() << std::endl;
#endif

}

////////////////////////////////////////////////////////////

template< class LocalOrdinal, class GlobalOrdinal, class Node >
void
MDMap< LocalOrdinal, GlobalOrdinal, Node >::
computeGhostPoints(const Teuchos::ArrayView< int > & ghostPoints)
{
  _temp_ghostPoints = Teuchos::ArrayRCP< int >(_temp_numDims, 0);
  for (int i=0; i < _temp_ghostPoints.size(); ++i)
  {
    // Ghost point default values are 0 or halo when periodic is false
    // or true, respectively
    if (_temp_periodic[i]) _temp_ghostPoints[i] = _temp_halos[i][0];

    // Override defaults with provided ghost points, with the caveat
    // that the resulting ghost points cannot be less than the default
    if (i < ghostPoints.size())
      _temp_ghostPoints[i] = std::max(_temp_ghostPoints[i], ghostPoints[i]);
  }

#ifdef TPETRA_DEBUG
  std::cout << std::endl << "MDMap::computeGhostPoints(): temp ghost points = "
            << _temp_ghostPoints() << std::endl;
#endif

}

////////////////////////////////////////////////////////////

template< class LocalOrdinal, class GlobalOrdinal, class Node >
void
MDMap< LocalOrdinal, GlobalOrdinal, Node >::
computeAxisRanges()
{
  // Initialize the shapes, starting indexes and interior bounds
  _temp_globalGhostShape = Teuchos::ArrayRCP< GlobalOrdinal >(_temp_numDims);
  _temp_localOwnShape    = Teuchos::ArrayRCP< LocalOrdinal  >(_temp_numDims);
  _temp_localShape       = Teuchos::ArrayRCP< LocalOrdinal  >(_temp_numDims);
  _temp_axisStart        = Teuchos::ArrayRCP< GlobalOrdinal >(_temp_numDims);
  _temp_localInteriorBounds =
    Teuchos::ArrayRCP<
      Teuchos::Tuple< LocalOrdinal, 2 > >(_temp_numDims,
                                          Teuchos::tuple< LocalOrdinal >(0,0));
  for (int i = 0; i < _temp_numDims; ++i)
  {
    // First estimates for local shape and axis starts.  Use integer
    // division to estimate the number of local points along this axis
    // and the starting global index.
    _temp_localOwnShape[i] = _temp_globalShape[i] / _temp_axisNumProcs[i];
    _temp_axisStart[i]  = _temp_axisRanks[i] * _temp_localOwnShape[i];

    // Adjustments for non-zero remainder.  Compute the remainder
    // using the mod operator.  If the remainder is > 0, then add an
    // element to the appropriate number of processors with the
    // highest axis ranks.  Note that this is the opposite of the
    // standard Tpetra::Map constructor (which adds an elements to the
    // lowest processor ranks), and provides better balance for finite
    // differencing systems with staggered data location.
    LocalOrdinal remainder = _temp_globalShape[i] % _temp_axisNumProcs[i];
    if (_temp_axisNumProcs[i] - _temp_axisRanks[i] - 1 < remainder)
    {
      _temp_localOwnShape[i]++;
      _temp_axisStart[i] += (remainder - _temp_axisNumProcs[i] +
                             _temp_axisRanks[i]);
    }

    // Adjust the lower boundary halo value
    if (_temp_axisRanks[i] == 0)
      _temp_halos[i][0] = _temp_ghostPoints[i];

    // Adjust the upper boundary halo value
    if (_temp_axisRanks[i] == _temp_axisNumProcs[i] - 1)
      _temp_halos[i][1] = _temp_ghostPoints[i];

    // Compute the local shape
    _temp_localShape[i] = _temp_localOwnShape[i] + _temp_halos[i][0] +
      _temp_halos[i][1];
    //_temp_axisStart[i] -= _temp_halos[i][0];

    // Compute the global ghost shape
    _temp_globalGhostShape[i] = _temp_globalShape[i] + 2 * _temp_ghostPoints[i];

    // Set the lower interior loop bound
    if (_temp_axisRanks[i] == 0) _temp_localInteriorBounds[i][0] = 1;

    // Set the upper interior loop bound
    _temp_localInteriorBounds[i][1] = _temp_localOwnShape[i];
    if (_temp_axisRanks[i] == _temp_axisNumProcs[i] - 1)
      _temp_localInteriorBounds[i][1] -= 1;
  }

#ifdef TPETRA_DEBUG
  std::cout << std::endl << "MDMap::computeAxisRanges():" << std::endl;
  std::cout << "  final halos     = " << _temp_halos()         << std::endl;
  std::cout << "  local own shape = " << _temp_localOwnShape() << std::endl;
  std::cout << "  local shape     = " << _temp_localShape()    << std::endl;
  std::cout << "  axis start      = " << _temp_axisStart()     << std::endl;
#endif

}

////////////////////////////////////////////////////////////

template< class LocalOrdinal, class GlobalOrdinal, class Node >
Teuchos::ArrayRCP< Teuchos::RCP< Tpetra::Map< LocalOrdinal,
                                              GlobalOrdinal,
                                              Node > > >
MDMap< LocalOrdinal, GlobalOrdinal, Node >::
computeAxisMaps(const Teuchos::RCP< const Teuchos::Comm< int > > & comm)
{
  Teuchos::ArrayRCP<
    Teuchos::RCP<
      Tpetra::Map< LocalOrdinal, GlobalOrdinal, Node > > >
        result(_temp_numDims);

  for (int i = 0; i < _temp_numDims; ++i)
  {
    GlobalOrdinal indexBase = 0;
    if (!_temp_periodic[i])
      indexBase -= _temp_ghostPoints[i];
    //
    // Create an array of contiguous global 1D indexes along the i-th
    // axis that represent the 1D decomposition.
    Teuchos::Array< GlobalOrdinal > elements(_temp_localShape[i]);
    for (LocalOrdinal j = 0; j < _temp_localShape[i]; j++)
      elements[j] = j + _temp_axisStart[i] - _temp_halos[i][0];
    //
    // Adjust boundaries for periodic case
    if (_temp_periodic[i])
    {
      // Lower boundary
      if (_temp_axisRanks[i] == 0)
        for (LocalOrdinal j = 0; j < _temp_ghostPoints[i]; ++j)
          elements[j] = _temp_globalShape[i] - _temp_ghostPoints[i] + j;
      // Upper boundary
      if (_temp_axisRanks[i] == _temp_axisNumProcs[i] - 1)
        for (LocalOrdinal j = 0; j < _temp_ghostPoints[i]; ++j)
          elements[_temp_localShape[i] - _temp_ghostPoints[i] + j] = j;
    }
    // Use the array to build a 1D Tpetra::Map along the i-th axis
#ifdef TPETRA_DEBUG
    std::cout << comm->getRank() << ": axis " << i << ", indexBase = "
              << indexBase << ", elements = " << elements() << std::endl;
#endif
    result[i] = Teuchos::rcp(new Tpetra::Map< LocalOrdinal,
                                              GlobalOrdinal,
                                              Node >
         (Teuchos::OrdinalTraits<global_size_t>::invalid(), elements,
          indexBase, comm));
  }

#ifdef TPETRA_DEBUG
  std::cout << std::endl << comm->getRank()
            << ": MDMap::computeAxisMaps():" << std::endl;
  for (int i = 0; i < result.size(); ++i)
    std::cout << "Axis " << i << ", proc " << comm->getRank() << ": "
              << result[i]->description() << " "
              << result[i]->getNodeElementList() << std::endl;
  std::cout.flush();
#endif

  return result;
}

////////////////////////////////////////////////////////////

template< class LocalOrdinal, class GlobalOrdinal, class Node >
void
MDMap< LocalOrdinal, GlobalOrdinal, Node >::
nullifyStaticData()
{
  _temp_numDims             = 0;
  _temp_globalShape         = Teuchos::ArrayRCP< GlobalOrdinal >();
  _temp_globalGhostShape    = Teuchos::ArrayRCP< GlobalOrdinal >();
  _temp_localOwnShape       = Teuchos::ArrayRCP< LocalOrdinal >();
  _temp_localShape          = Teuchos::ArrayRCP< LocalOrdinal >();
  _temp_localInteriorBounds =
    Teuchos::ArrayRCP< Teuchos::Tuple< LocalOrdinal, 2 > >();
  _temp_axisStart           = Teuchos::ArrayRCP< GlobalOrdinal >();
  _temp_axisNumProcs        = Teuchos::ArrayRCP< int >();
  _temp_axisRanks           = Teuchos::ArrayRCP< int >();
  _temp_halos               = Teuchos::ArrayRCP< Teuchos::Tuple< int, 2 > >();
  _temp_ghostPoints         = Teuchos::ArrayRCP< int >();
  _temp_periodic            = Teuchos::ArrayRCP< int >();
  _temp_globalStrides       = Teuchos::ArrayRCP< GlobalOrdinal >();
  _temp_localStrides        = Teuchos::ArrayRCP< LocalOrdinal >();
  _temp_elements_           = Teuchos::ArrayRCP< GlobalOrdinal >();
}

} // namespace Tpetra

#endif
