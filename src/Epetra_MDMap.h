#ifndef EPETRA_MDMAP_H
#define EPETRA_MDMAP_H

//! \file Epetra_MDMap.h
//! \brief Epetra MDMap declaration and implementation

// System includes
#include <algorithm>

// Teuchos includes
#include "Teuchos_Array.hpp"
#include "Teuchos_Tuple.hpp"

// Epetra includes
#include "Epetra_Comm.h"
#include "Epetra_Map.h"

//////////////////////////////////////////////////////////////////
//
// \todo Const-correctness for methods and member variables
// \todo Teuchos::ParameterList constructor
// \todo Non-member constructors?  Concrete dimensionality sub-classes?
// \todo Array bounds checking in FDM_ARRAY_BOUNDS_CHECK mode
//
//////////////////////////////////////////////////////////////////

//! A class for partitioning distributed MD objects

//! This class inherits from \c Epetra_Map.  It is intended to
//! decompose multidimensional entities, such as coordinates and
//! fields that are represented on structured meshes.

//! By inheriting from \c Epetra_Map, it can be used wherever an \c
//! Epetra_Map can be used and maintains the paradigm of mapping
//! between single-dimension local and global IDs.  However, the \c
//! Epetra_MDMap class assumes that the data being indexed can be
//! expressed as an N-dimensional array (where N is arbitrary), and so
//! axis indexing is also supported.

//! A note about terminology: within the \c Epetra_MDMap class, it is
//! common to have related one-dimensional and N-dimensional indexing
//! concepts.  In these situations, the prefix "axis" is intended to
//! signify reference to an N-dimensional index.  For example, the
//! method \c getGlobalAxisIndex() will return an N-dimensional index.

//! The \c Epetra_MDMap class adds the capability of axis indexing
//! (i.e. N-dimensional indexing) to local data, global data, and
//! processor ranks.  This last feature enables to user to specify how
//! many processors are assigned to each axis, with the restriction
//! that the product of all axis processor counts equal the total
//! number of processors.

//! Halos are also supported.  Halo regions represent overlap regions,
//! and with proper communication, allow the local processing node to
//! access copies of remote data.  If all halos are zero, then the \c
//! Epetra_MDMap is one-to-one and each processor "owns" all of its
//! global IDs.  A halo value along each axis can be specified at
//! construction, but two values are ultimately stored on each
//! processor, because halos at boundaries will be set to zero.

//! NB: a local axis index of (0,0,...), i.e. the local origin, refers
//! to the first element of the non-halo region.  Equivalently, it
//! refers to the first element of the locally-owned data.  This means
//! that the user can use negative indexes to reference the
//! lower-boundary halo region.

//! \c Epetra_MDMap also provides an array of 1D \c Epetra_Map
//! objects, one along each axis, representing the decomposition along
//! that axis.

class Epetra_MDMap : public Epetra_Map
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
  //! dimensionality of the \c MDMap is determined by the
  //! number of elements in argument \c globalShape.  Arguments \c
  //! axisNumProc and \c halos can be underspecified, with logical
  //! defaults automatically substituted.
  Epetra_MDMap(const Epetra_Comm & comm,
               const Teuchos::ArrayView< int > & globalShape,
               const Teuchos::ArrayView< int > & axisNumProc =
                   Teuchos::ArrayView< int >(),
               const Teuchos::ArrayView< int > & halos =
                   Teuchos::ArrayView< int >(),
               const Teuchos::ArrayView< int > & ghostPoints =
                   Teuchos::ArrayView< int >(),
               const Teuchos::ArrayView< int > & periodic =
                   Teuchos::ArrayView< int >());

  //! 2D Constructor

  //! The 2D constructor creates a map for two-dimensional data and
  //! only requires that the number of indexes in the i and j
  //! directions be specified.  Optional arguments include the number
  //! of processors along the i and j axes, as well as the halos in
  //! the i and j directions.
  Epetra_MDMap(const Epetra_Comm & comm,
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

  //! Copy Constructor
  Epetra_MDMap(const Epetra_MDMap & source);

  //! Destructor
  ~Epetra_MDMap() { }

  ///////////////
  // Operators //
  ///////////////

  //! Assignment operator
  Epetra_MDMap &
  operator=(const Epetra_MDMap & rhs);

  /////////////////////////////////
  // Attribute retrieval methods //
  /////////////////////////////////

  //! Number of dimensions

  //! Describes the dimensionality of the problem represented by the
  //! \c MDMap: 1 for 1D, 2 for 2D, etc.
  inline
  int
  getNumDims() const { return _numDims; }

  //! Global dimension values

  //! Returns a \c Teuchos::ArrayRCP containing the global size of the
  //! problem along each axis, excluding ghost points.
  inline
  const Teuchos::ArrayRCP< int >
  getGlobalShape() const { return _globalShape; }

  //! Global dimension value

  //! Returns the global dimension of the problem, excluding ghost
  //! points, along the requested axis.
  inline
  int
  getGlobalShape(int axis) const { return _globalShape[axis]; }

  //! Global dimension values

  //! Returns a \c Teuchos::ArrayRCP containing the global size of the
  //! problem along each axis, including ghost points.
  inline
  const Teuchos::ArrayRCP< int >
  getGlobalGhostShape() const { return _globalGhostShape; }

  //! Global dimension value

  //! Returns the global dimension of the problem, including ghost
  //! points, along the requested axis.
  inline
  int
  getGlobalGhostShape(int axis) const { return _globalGhostShape[axis]; }

  //! Local dimension values, excluding halos

  //! Returns a \c Teuchos::ArrayRCP containing the local size of the
  //! problem along each axis, excluding halos.
  inline
  const Teuchos::ArrayRCP< int >
  getLocalOwnShape() const { return _localOwnShape; }

  //! Local dimension value, excluding halos

  //! Returns the local dimension of the problem along the requested
  //! axis, excluding halos.
  inline
  int
  getLocalOwnShape(int axis) const { return _localOwnShape[axis]; }

  //! Local dimension values

  //! Returns a \c Teuchos::ArrayRCP containing the local size of the
  //! problem along each axis, including halos.
  inline
  const Teuchos::ArrayRCP< int >
  getLocalShape() const { return _localShape; }

  //! Local dimension value

  //! Returns the local dimension of the problem along the requested
  //! axis, including halos.
  inline
  int
  getLocalShape(int axis) const { return _localShape[axis]; }

  //! Local interior (non-boundary) loop bounds

  //! Returns a \c Teuchos::ArrayRCP of \c Teuchos::Tuple of 2
  //! ints corresponding to the lower and upper bounds for
  //! looping over interior (non-boundary) elements on each axis.
  inline
  const Teuchos::ArrayRCP< Teuchos::Tuple< int, 2 > >
  getLocalInteriorBounds() const { return _localInteriorBounds; }

  //! Local interior (non-boundary) loop bounds

  //! Returns a Teuchos::Tuple of 2 ints corresponding to the
  //! lower and upper bounds for looping over interior (non-boundary)
  //! elements on the given axis.
  inline
  const Teuchos::Tuple< int, 2 >
  getLocalInteriorBounds(int axis) const { return _localInteriorBounds[axis]; }

  //! Starting axis index along each axis

  //! Returns a \c Teuchos::Array::RCP containing the starting global
  //! axis index along each axis.
  inline
  const Teuchos::ArrayRCP< int >
  getAxisStart() const { return _axisStart; }

  //! Starting axis index along requested axis

  //! Returns the starting global axis index along the requested
  //! axis.
  inline
  int
  getAxisStart(int axis) const { return _axisStart[axis]; }

  //! Processor partitions

  //! Returns a \c Teuchos::ArrayRCP containing the number of
  //! processors assigned along each axis.
  inline
  const Teuchos::ArrayRCP< int >
  getAxisNumProcs() const { return _axisNumProcs; }

  //! Processor partition

  //! Returns the number of processors assigned along the requested
  //! axis.
  inline
  int
  getAxisNumProcs(int axis) const { return _axisNumProcs[axis]; }

  //! Processor axis ranks

  //! Returns a \c Teuchos::ArrayRCP containing the axis processor
  //! ranks along each axis for the local processor.
  inline
  const Teuchos::ArrayRCP< int >
  getAxisRanks() const { return _axisRanks; }

  //! Processor axis rank

  //! Returns the axis processor rank along the requested axis for the
  //! local processor.
  inline
  int
  getAxisRank(int axis) const { return _axisRanks[axis]; }

  //! Halo sizes for each axis

  //! Returns a \c Teuchos::ArrayRCP containing a \c Teuchos::Tuple
  //! along each axis that contains the upper and lower halo values.
  inline
  const Teuchos::ArrayRCP< Teuchos::Tuple< int, 2 > >
  getHalos() const { return _halos; }

  //! Halo sizes for requested axis

  //! Returns a \c Teuchos::Tuple along the requeseted axis that
  //! contains the upper and lower halo values.
  inline
  const Teuchos::Tuple< int, 2 >
  getHalos(int axis) const { return _halos[axis]; }

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
  getGhostPoints() const { return _ghostPoints; }

  //! Ghost points for requested axis

  //! Returns an integer indicating the number of ghost points on the
  //! requested axis.
  inline
  int getGhostPoints(int axis) const { return _ghostPoints[axis]; }

  //! Periodic flags

  //! Returns an array of integer flags indicating whether each axis
  //! is periodic.
  inline
  Teuchos::ArrayRCP< int >
  getPeriodic() const { return _periodic; }

  //! Periodic flag for requested axis

  //! Returns an integer flag indicating whether the requested axis is
  //! periodic.
  inline
  int
  getPeriodic(int axis) const { return _periodic[axis]; }

  //! Global stride information

  //! Returns a \c Teuchos::ArrayRCP containing the stride length
  //! along each axis.
  inline
  const Teuchos::ArrayRCP< int >
  getGlobalStrides() const { return _globalStrides; }

  //! Global stride information

  //! Returns a \c Teuchos::ArrayRCP containing the stride length
  //! along each axis.
  inline
  int
  getGlobalStride(int axis) const { return _globalStrides[axis]; }

  //! Local stride information

  //! Returns a \c Teuchos::ArrayRCP containing the stride length
  //! along each axis.
  inline
  const Teuchos::ArrayRCP< int >
  getLocalStrides() const { return _localStrides; }

  //! Local stride information

  //! Returns a \c Teuchos::ArrayRCP containing the stride length
  //! along each axis.
  inline
  int
  getLocalStride(int axis) const { return _localStrides[axis]; }

  //! 1D maps along each axis

  //! Returns a \c Teuchos::ArrayRCP containing a 1D \c Tpetra::Map
  //! along each axis, representing the decomposition of that axis
  //! index along that axis.
  inline
  const Teuchos::ArrayRCP< const Teuchos::RCP< Epetra_Map > >
  getAxisMaps() const { return _axisMaps; }

  //! 1D map along requested axis

  //! Returns a 1D \c Tpetra::Map along the requested axis,
  //! representing the decomposition of that axis index along that
  //! axis.
  inline
  const Teuchos::RCP< Epetra_Map >
  getAxisMap(int axis) const { return _axisMaps[axis]; }

  //////////////////////
  // Indexing methods //
  //////////////////////

  //! Convert a global index into an array of global axis indexes
  Teuchos::Array< int >
  getGlobalAxisIndex(const int globalIndex) const;

  //! Convert a local index into an array of local axis indexes

  //! Note that the local origin (0,0,...) refers to the index of the
  //! first element of the interior, or non-halo region.
  Teuchos::Array< int >
  getLocalAxisIndex(const int LocalIndex) const;

  //! Convert a local index into a global index
  inline int
  getGlobalElement(int localIndex) const
  { return Epetra_Map::GID(localIndex); }

  //! Convert an array of global axis indexes into a global index
  int
  getGlobalElement(const Teuchos::ArrayView< const int > globalAxisIndex) const;

  //! Convert a global index into a local index
  inline int
  getLocalElement(int globalIndex) const
  { return Epetra_Map::LID(globalIndex); }

  //! Convert an array of local axis indexes into a local index

  //! Note that the local origin (0,0,...) refers to the index of the
  //! first element of the interior, or non-halo region.
  int
  getLocalElement(const Teuchos::ArrayView< const int > localAxisIndex) const;

private:

  ////////////////////////
  // Private member data
  ////////////////////////

  //! Number of dimensions
  const int _numDims;

  //! Number of global elements along each axis, excluding ghost points
  const Teuchos::ArrayRCP< int > _globalShape;

  //! Number of global elements along each axis, including ghost points
  const Teuchos::ArrayRCP< int > _globalGhostShape;

  //! Number of local elements along each axis, excluding halos
  const Teuchos::ArrayRCP< int > _localOwnShape;

  //! Number of local elements along each axis, including halos
  const Teuchos::ArrayRCP< int > _localShape;

  //! Local loop bounds over interior (non-boundary) elements
  const Teuchos::ArrayRCP< Teuchos::Tuple< int, 2 > > _localInteriorBounds;

  //! Starting axis index along each axis
  const Teuchos::ArrayRCP< int > _axisStart;

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
  const Teuchos::ArrayRCP< int > _globalStrides;

  //! Local striding information
  const Teuchos::ArrayRCP< int > _localStrides;

  //! Epetra_Map along each axis
  const Teuchos::ArrayRCP< const Teuchos::RCP< Epetra_Map > > _axisMaps;

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
  static Teuchos::ArrayRCP< int > _temp_globalShape;

  //! Number of global elements along each axis, including exterior ghost points
  static Teuchos::ArrayRCP< int > _temp_globalGhostShape;

  //! Number of local elements along each axis, excluding halos
  static Teuchos::ArrayRCP< int > _temp_localOwnShape;

  //! Number of local elements along each axis, including halos
  static Teuchos::ArrayRCP< int > _temp_localShape;

  //! Local loop bounds over interior (non-boundary) elements
  static Teuchos::ArrayRCP< Teuchos::Tuple< int, 2 > >
    _temp_localInteriorBounds;

  //! Starting axis index along each axis
  static Teuchos::ArrayRCP< int > _temp_axisStart;

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
  static Teuchos::ArrayRCP< int > _temp_globalStrides;

  //! Local striding information
  static Teuchos::ArrayRCP< int > _temp_localStrides;

  //! Array of global ID values for this node
  static Teuchos::ArrayRCP< int > _temp_elements;

  ///////////////////////////
  // Private static functions
  ///////////////////////////

  //! Compute the number of local elements for the base \c Epetra_Map class

  //! Static member function computeNumElements() is called by the
  //! constructor initialization list and returns an int that
  //! corresponds the the number of global IDs of the elements on this
  //! processor.  It is the only static member function called by the
  //! Epetra_Map base class constructor, and so it sets several
  //! temporary static variables used later in the Epetra_MDMap
  //! constructor initialization list.
  static int
  computeNumElements(const Epetra_Comm & comm,
                     const Teuchos::ArrayView< int > & globalShape,
                     const Teuchos::ArrayView< int > & axisNumProc,
                     const Teuchos::ArrayView< int > & halos,
                     const Teuchos::ArrayView< int > & ghostPoints,
                     const Teuchos::ArrayView< int > & periodic);

  // Compute the pointer to the local elements list

  // Static member function computeElementsPtr() is called by the
  // constructor initializaion list and returns an int pointer that
  // corresponds to the list of local elements on this processor.
  // Functions computeNumElements() and computeElementsPtr() are
  // designed to work regardless of which is called first.
  static int*
  computeElementsPtr(const Epetra_Comm & comm,
                     const Teuchos::ArrayView< int > & globalShape,
                     const Teuchos::ArrayView< int > & axisNumProc,
                     const Teuchos::ArrayView< int > & halos,
                     const Teuchos::ArrayView< int > & ghostPoints,
                     const Teuchos::ArrayView< int > & periodic);

  //! Compute the global shape of the MD data

  //! Static member function computeGlobalShape() is called by
  //! computeNumElements() and simply computes _temp_globalShape by
  //! converting a Teuchos::ArrayView< int > to a Teuchos::ArrayRCP<
  //! GLobalOrdinal >.  This allows the generic N-dimensional
  //! constructor to accept a Teuchos::Tuple of dimensions, which is
  //! the most convenient way to specify a short array.
  static void
  computeGlobalShape(const Teuchos::ArrayView< int > & globalShape);

  //! Compute the number of processors along each axis

  //! Static member function computeAxisNumProcs() is called by
  //! computeNumElements() and computes _temp_axisNumProcs.  It
  //! allows the user to not specify the number of processors along
  //! selected axes in favor of having them computed automatically.
  //! To compute the number of axes along an axis automatically,
  //! provide a value <= 0 or use the default value.
  static void
  computeAxisNumProcs(const int numProc,
                      const Teuchos::ArrayView< int > & axisNumProc);

  //! Compute the axis ranks of this processor

  //! Static member function computeAxisRanks() is called by
  //! computeNumElements() and, given the number of processors along
  //! each axis, computes _temp_axisRanks, an array of axis processor
  //! ranks.  For example in 3D, processor rank 0 -> (0,0,0) and
  //! processor rank 1 -> (1,0,0), etc.
  static void
  computeAxisRanks(const int rank);

  //! Compute the halos along each axis

  //! Static member function computeHalos() is called by
  //! computeNumElements() and computes _temp_halos, an array of
  //! halos of the correct length.  This allows the user to
  //! underspecify the halos (or not specify them at all) and have
  //! those halo values set to a default value of 0.
  static void
  computeHalos(const Teuchos::ArrayView< int > & halos);

  //! Compute the periodic flags along each axis

  //! Static member function computePeriodic() is called by
  //! computeNumElements() and computes _temp_periodic, an array of
  //! integer flags specifying whether each axis is periodic.  This
  //! allows the user to underspecify the periodic flags (or not
  //! specify them at all) at the time of construction, and have those
  //! periodic flags be set to a default value of 0 (false).
  static void
  computePeriodic(const Teuchos::ArrayView< int > & periodic);

  //! Compute the ghost point flags along each axis

  //! Static member function computeGhostPoints() is called by
  //! computeNumElements() and computes _temp_ghostPoints, an array
  //! of integer flags specifying whether each axis supports ghost
  //! points exterior to the domain.  This allows the user to
  //! underspecify the ghost point flags (or not specify them at all)
  //! at the time of construction, and have those ghost point flags be
  //! set to a default value.  The default value is the corresponding
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
  static Teuchos::ArrayRCP< Teuchos::RCP< Epetra_Map > >
  computeAxisMaps(const Epetra_Comm & comm);

  //! Nullify all static data

  //! The constructors all utilize temporary static variables in order
  //! to compute private member data before initializing the
  //! Tpetra::Map base class.  This static function sets all of those
  //! temporary static variables to a null state, to make it clear
  //! that they are not in use.
  static void
  nullifyStaticData();

};

#endif
