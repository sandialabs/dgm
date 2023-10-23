/** \file Epetra_MDMap.cpp
    \brief Implementation of a concrete Epetra MD map
    \author Bill Spotz
*/

// local includes
#include "Epetra_MDMap.h"

// boost includes
#include "boost/numeric/conversion/cast.hpp"

////////////////////////////////////////////////////////////
// Epetra_MDMap Implementations
////////////////////////////////////////////////////////////

/// @cond DOXYGEN_SHOULD_SKIP_THIS

// Initialize the temporary static variables to be null or zero
int
Epetra_MDMap::_temp_numDims = 0;

Teuchos::ArrayRCP< int >
Epetra_MDMap::_temp_globalShape = Teuchos::ArrayRCP< int >();

Teuchos::ArrayRCP< int >
Epetra_MDMap::_temp_globalGhostShape = Teuchos::ArrayRCP< int >();

Teuchos::ArrayRCP< int >
Epetra_MDMap::_temp_localOwnShape = Teuchos::ArrayRCP< int >();

Teuchos::ArrayRCP< int >
Epetra_MDMap::_temp_localShape = Teuchos::ArrayRCP< int >();

Teuchos::ArrayRCP< Teuchos::Tuple< int, 2 > >
Epetra_MDMap::_temp_localInteriorBounds =
  Teuchos::ArrayRCP< Teuchos::Tuple< int, 2 > >();

Teuchos::ArrayRCP< int >
Epetra_MDMap::_temp_axisStart = Teuchos::ArrayRCP< int >();

Teuchos::ArrayRCP< int >
Epetra_MDMap::_temp_axisNumProcs = Teuchos::ArrayRCP< int >();

Teuchos::ArrayRCP< int >
Epetra_MDMap::_temp_axisRanks = Teuchos::ArrayRCP< int >();

Teuchos::ArrayRCP< Teuchos::Tuple< int, 2 > >
Epetra_MDMap::_temp_halos = Teuchos::ArrayRCP< Teuchos::Tuple< int, 2 > >();

Teuchos::ArrayRCP< int >
Epetra_MDMap::_temp_ghostPoints = Teuchos::ArrayRCP< int >();

Teuchos::ArrayRCP< int>
Epetra_MDMap::_temp_periodic = Teuchos::ArrayRCP< int >();

Teuchos::ArrayRCP< int >
Epetra_MDMap::_temp_globalStrides = Teuchos::ArrayRCP< int >();

Teuchos::ArrayRCP< int >
Epetra_MDMap::_temp_localStrides = Teuchos::ArrayRCP< int >();

Teuchos::ArrayRCP< int >
Epetra_MDMap::_temp_elements = Teuchos::ArrayRCP< int >();

/// @endcond

////////////////////////////////////////////////////////////

// N-dimensional Constructor
Epetra_MDMap::
Epetra_MDMap(const Epetra_Comm & comm,
             const Teuchos::ArrayView< int > & globalShape,
             const Teuchos::ArrayView< int > & axisNumProc,
             const Teuchos::ArrayView< int > & halos,
             const Teuchos::ArrayView< int > & ghostPoints,
             const Teuchos::ArrayView< int > & periodic) :
  Epetra_Map(-1,
             computeNumElements(comm,
                                globalShape,
                                axisNumProc,
                                halos,
                                ghostPoints,
                                periodic),
             //_temp_elements.getRawPtr(),
             computeElementsPtr(comm,
                                globalShape,
                                axisNumProc,
                                halos,
                                ghostPoints,
                                periodic),
             0,
             comm),
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
#ifdef FDM_DEBUG
  std::cout << comm->getRank() << ": MDMap constructor ... "
            << "initialization list completed" << std::endl;
#endif
  nullifyStaticData();
}

////////////////////////////////////////////////////////////

// 2D Constructor
Epetra_MDMap::
Epetra_MDMap(const Epetra_Comm & comm,
             const int globalNum_i,
             const int globalNum_j,
             const int numProc_i,
             const int numProc_j,
             const int halo_i,
             const int halo_j,
             const int ghostPoints_i,
             const int ghostPoints_j,
             const int periodic_i,
             const int periodic_j) :
  Epetra_Map(-1,
             computeNumElements(comm,
                                Teuchos::tuple< int >(globalNum_i, globalNum_j),
                                Teuchos::tuple< int >(numProc_i, numProc_j),
                                Teuchos::tuple< int >(halo_i, halo_j),
                                Teuchos::tuple< int >(ghostPoints_i, ghostPoints_j),
                                Teuchos::tuple< int >(periodic_i, periodic_j)),
             //_temp_elements.getRawPtr(),
             computeElementsPtr(comm,
                                Teuchos::tuple< int >(globalNum_i, globalNum_j),
                                Teuchos::tuple< int >(numProc_i, numProc_j),
                                Teuchos::tuple< int >(halo_i, halo_j),
                                Teuchos::tuple< int >(ghostPoints_i, ghostPoints_j),
                                Teuchos::tuple< int >(periodic_i, periodic_j)),
             0,
             comm),
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
Epetra_MDMap::
Epetra_MDMap(const Epetra_MDMap & source) :
  Epetra_Map(source),
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
Epetra_MDMap &
Epetra_MDMap::
operator=(const Epetra_MDMap& rhs)
{
  // Check for assignment to self
  if (this == &rhs) return *this;
  // Copy rhs to *this and return
  *this = rhs;
  return *this;
}

////////////////////////////////////////////////////////////

// Halo presence
bool
Epetra_MDMap::
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
Teuchos::ArrayRCP< int >
Epetra_MDMap::
getNominalHalos() const
{
  Teuchos::ArrayRCP< int > result = Teuchos::ArrayRCP< int >(_numDims);
  for (int i = 0; i < _numDims; ++i)
    result[i] = std::max(_halos[i][0], _halos[i][1]);
  return result;
}

////////////////////////////////////////////////////////////

// Convert a global index into an array of global axis indexes
Teuchos::Array< int >
Epetra_MDMap::
getGlobalAxisIndex(const int globalIndex) const
{
  Teuchos::Array< int > result(_numDims);
  int reducedIndex = globalIndex;
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
Teuchos::Array< int >
Epetra_MDMap::
getLocalAxisIndex(const int localIndex) const
{
  Teuchos::Array< int > result(_numDims);
  int reducedIndex = localIndex;
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
int
Epetra_MDMap::
getGlobalElement(const Teuchos::ArrayView< const int > globalAxisIndex) const
{
  if (globalAxisIndex.size() != _numDims)
    throw std::invalid_argument("Number of global axis indexes does not match "
                                "MDMap dimensionality");
  int result = 0;
  int offset = 0;
  for (int i = 0; i < _numDims; ++i)
  {
    offset = (_periodic[i]) ? 0 : _ghostPoints[i];
    result += (globalAxisIndex[i] + offset) * _globalStrides[i];
  }
  return result;
}

////////////////////////////////////////////////////////////

// Convert an array of local axis indexes into a local index
int
Epetra_MDMap::
getLocalElement(const Teuchos::ArrayView< const int > localAxisIndex) const
{
  if (localAxisIndex.size() != _numDims)
    throw std::invalid_argument("Number of local axis indexes does not match "
                                "MDMap dimensionality");
  int result = 0;
  for (int i = 0; i < _numDims; ++i)
    result += (localAxisIndex[i] + _halos[i][0]) * _localStrides[i];
  return result;
}

////////////////////////////
// Private static methods //
////////////////////////////

////////////////////////////////////////////////////////////

int
Epetra_MDMap::
computeNumElements(const Epetra_Comm & comm,
                   const Teuchos::ArrayView< int > & globalShape,
                   const Teuchos::ArrayView< int > & axisNumProc,
                   const Teuchos::ArrayView< int > & halos,
                   const Teuchos::ArrayView< int > & ghostPoints,
                   const Teuchos::ArrayView< int > & periodic)
{
  // Check to see if calculations have already been done
  if (!_temp_elements.is_null())
    return boost::numeric_cast<int>(_temp_elements.size());
  //
  // Set the temporary static variables
  _temp_numDims = boost::numeric_cast<int>(globalShape.size());
  computeGlobalShape(globalShape);
  computeAxisNumProcs(comm.NumProc(), axisNumProc);
  computeAxisRanks(comm.MyPID());
  computeHalos(halos);
  computePeriodic(periodic);
  computeGhostPoints(ghostPoints);
  computeAxisRanges();
  //
  // Allocate arrays for the temporary strides
  _temp_globalStrides = Teuchos::ArrayRCP< int >(_temp_numDims);
  _temp_localStrides  = Teuchos::ArrayRCP< int >(_temp_numDims);
  //
  // Compute the total size and the stride values
  int globalSize = 1;
  int localSize  = 1;
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
  int offset = 0;
  for (int i = 0; i < _temp_numDims; ++i)
    if (!_temp_periodic[i])
      offset += _temp_ghostPoints[i] * _temp_globalStrides[i];
  //
  // Allocate the index array and initialize it with the appropriate
  // starting values
  Teuchos::Array< int > index(_temp_numDims);
  for (int j = 0; j < _temp_numDims; ++j)
    index[j] = -_temp_halos[j][0];
  // Allocate the result array and initialize it with the starting
  // offset value
  _temp_elements = Teuchos::ArrayRCP< int >(localSize, offset);
  //
  // Loop over all of the local elements
  for (int i = 0; i < localSize; ++i)
  {
    // Compute _temp_elements[i]
    for (int j = 0; j < _temp_numDims; ++j)
      _temp_elements[i] += (_temp_axisStart[j] + index[j]) * _temp_globalStrides[j];
    // Adjust for periodic boundaries
    for (int j = 0; j < _temp_numDims; ++j)
      if (_temp_periodic[j])
      {
        if (_temp_axisRanks[j] == 0 && index[j] < 0)
          _temp_elements[i] += _temp_globalStrides[j] * _temp_globalShape[j];
        if (_temp_axisRanks[j] == _temp_axisNumProcs[j] - 1 &&
            index[j] >= _temp_localOwnShape[j])
          _temp_elements[i] -= _temp_globalStrides[j] * _temp_globalShape[j];
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

#ifdef FDM_DEBUG
  std::stringstream filename;
  filename << "elements." << comm->getRank();
  std::ofstream ofile(filename.str().c_str());
  for (int i = 0; i < _temp_elements.size();  ++i)
    ofile << _temp_elements[i] << std::endl;
  ofile.close();
#endif

  return boost::numeric_cast<int>(_temp_elements.size());
}

////////////////////////////////////////////////////////////

int *
Epetra_MDMap::
computeElementsPtr(const Epetra_Comm & comm,
                   const Teuchos::ArrayView< int > & globalShape,
                   const Teuchos::ArrayView< int > & axisNumProc,
                   const Teuchos::ArrayView< int > & halos,
                   const Teuchos::ArrayView< int > & ghostPoints,
                   const Teuchos::ArrayView< int > & periodic)
{
  if (_temp_elements.is_null())
    computeNumElements(comm, globalShape, axisNumProc,
                       halos, ghostPoints, periodic);
  return _temp_elements.getRawPtr();
}

////////////////////////////////////////////////////////////

void
Epetra_MDMap::
computeGlobalShape(const Teuchos::ArrayView< int > & globalShape)
{
  _temp_globalShape = Teuchos::ArrayRCP< int >(globalShape.size());
  for (int i=0; i < globalShape.size(); ++i)
    _temp_globalShape[i] = globalShape[i];
}

////////////////////////////////////////////////////////////

void
Epetra_MDMap::
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
    if (block != numProc) throw std::invalid_argument("Product of axis processors does not "
                                                      "equal total processors");
    return;
  }
  // For underspecified processor partitions, give the remainder to
  // the first unspecified axis and set all the rest to 1
  if (numProc % block) throw std::invalid_argument("Number of processors do not divide evenly");
  int quotient = numProc / block;
  for (int i=0; i < _temp_axisNumProcs.size(); ++i)
  {
    if (_temp_axisNumProcs[i] < 0)
    {
      _temp_axisNumProcs[i] = quotient;
      quotient = 1;
    }
  }

#ifdef FDM_DEBUG
  std::cout << std::endl << "MDMap::computeAxisNumProcs(): "
            << _temp_axisNumProcs() << std::endl;
#endif

}

////////////////////////////////////////////////////////////

void
Epetra_MDMap::
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

#ifdef FDM_DEBUG
  std::cout << std::endl << "MDMap::computeAxisRanks(): " << rank << " => "
            << _temp_axisRanks() << std::endl;
#endif

}

////////////////////////////////////////////////////////////

void
Epetra_MDMap::
computeHalos(const Teuchos::ArrayView< int > & halos)
{
  _temp_halos = Teuchos::ArrayRCP< Teuchos::Tuple< int, 2 > >(_temp_numDims,
                                                               Teuchos::tuple< int >(0,0));
  for (int i=0; i < std::min(_temp_halos.size(), halos.size()); ++i)
  {
    _temp_halos[i][0]  = halos[i];
    _temp_halos[i][1]  = halos[i];
  }

#ifdef FDM_DEBUG
  std::cout << std::endl << "MDMap::computeHalos(): temp halos = "
            << _temp_halos() << std::endl;
#endif

}

////////////////////////////////////////////////////////////

void
Epetra_MDMap::
computePeriodic(const Teuchos::ArrayView< int > & periodic)
{
  _temp_periodic = Teuchos::ArrayRCP< int >(_temp_numDims, 0);
  for (int i = 0; i < std::min(_temp_periodic.size(), periodic.size()); ++i)
      _temp_periodic[i]  = periodic[i];

#ifdef FDM_DEBUG
  std::cout << std::endl << "MDMap::computePeriodic(): temp periodic = "
            << _temp_periodic() << std::endl;
#endif

}

////////////////////////////////////////////////////////////

void
Epetra_MDMap::
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

#ifdef FDM_DEBUG
  std::cout << std::endl << "MDMap::computeGhostPoints(): temp ghost points = "
            << _temp_ghostPoints() << std::endl;
#endif

}

////////////////////////////////////////////////////////////

void
Epetra_MDMap::
computeAxisRanges()
{
  // Initialize the shapes, starting indexes and interior bounds
  _temp_globalGhostShape   = Teuchos::ArrayRCP< int >(_temp_numDims);
  _temp_localOwnShape         = Teuchos::ArrayRCP< int  >(_temp_numDims);
  _temp_localShape  = Teuchos::ArrayRCP< int  >(_temp_numDims);
  _temp_axisStart          = Teuchos::ArrayRCP< int >(_temp_numDims);
  _temp_localInteriorBounds =
    Teuchos::ArrayRCP< Teuchos::Tuple< int, 2 > >(_temp_numDims,
                                                  Teuchos::tuple< int >(0,0));
  for (int i = 0; i < _temp_numDims; ++i)
  {
    // First estimates for local shape and axis starts.  Use integer
    // division to estimate the number of local points along this axis
    // and the starting global index.
    _temp_localOwnShape[i] = _temp_globalShape[i] / _temp_axisNumProcs[i];
    _temp_axisStart[i]  = _temp_axisRanks[i] * _temp_localOwnShape[i];

    // Adjustments for non-zero remainder.  Compute the remainder using
    // the mod operator.  If the remainder is > 0, then add an element
    // to the appropriate number of processors with the highest axis
    // ranks.  Note that this is the opposite of the standard
    // Tpetra::Map constructor (which adds an elements to the lowest
    // processor ranks), and provides better balance for finite
    // differencing systems with staggered data location.
    int remainder = _temp_globalShape[i] % _temp_axisNumProcs[i];
    if (_temp_axisNumProcs[i] - _temp_axisRanks[i] - 1 < remainder)
    {
      _temp_localOwnShape[i]++;
      _temp_axisStart[i] += (remainder - _temp_axisNumProcs[i] + _temp_axisRanks[i]);
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

#ifdef FDM_DEBUG
  std::cout << std::endl << "MDMap::computeAxisRanges():" << std::endl;
  std::cout << "  final halos     = " << _temp_halos()         << std::endl;
  std::cout << "  local own shape = " << _temp_localOwnShape() << std::endl;
  std::cout << "  local shape     = " << _temp_localShape()    << std::endl;
  std::cout << "  axis start      = " << _temp_axisStart()     << std::endl;
#endif

}

////////////////////////////////////////////////////////////

Teuchos::ArrayRCP< Teuchos::RCP< Epetra_Map > >
Epetra_MDMap::
computeAxisMaps(const Epetra_Comm & comm)
{
#ifdef FDM_DEBUG
  std::cout << "Inside computeAxisMaps()" << std::endl;
#endif
  Teuchos::ArrayRCP<
    Teuchos::RCP< Epetra_Map > > result(_temp_numDims);

  for (int i = 0; i < _temp_numDims; ++i)
  {
    int indexBase = 0;
    if (!_temp_periodic[i])
      indexBase -= _temp_ghostPoints[i];
    //
    // Create an array of contiguous global 1D indexes along the i-th
    // axis that represent the 1D decomposition.
    Teuchos::Array< int > elements(_temp_localShape[i]);
    for (int j = 0; j < _temp_localShape[i]; j++)
      elements[j] = j + _temp_axisStart[i] - _temp_halos[i][0];
    //
    // Adjust boundaries for periodic case
    if (_temp_periodic[i])
    {
      // Lower boundary
      if (_temp_axisRanks[i] == 0)
        for (int j = 0; j < _temp_ghostPoints[i]; ++j)
          elements[j] = _temp_globalShape[i] - _temp_ghostPoints[i] + j;
      // Upper boundary
      if (_temp_axisRanks[i] == _temp_axisNumProcs[i] - 1)
        for (int j = 0; j < _temp_ghostPoints[i]; ++j)
          elements[_temp_localShape[i] - _temp_ghostPoints[i] + j] = j;
    }
    // Use the array to build a 1D Tpetra::Map along the i-th axis
#ifdef FDM_DEBUG
    std::cout << comm->getRank() << ": axis " << i << ", indexBase = "
              << indexBase << ", elements = " << elements() << std::endl;
#endif
    const int elements_size = boost::numeric_cast<int>(elements.size());
    result[i] = Teuchos::rcp(new Epetra_Map(-1, elements_size,
                                            elements.getRawPtr(), indexBase,
                                            comm));
  }

  return result;
}

////////////////////////////////////////////////////////////

void
Epetra_MDMap::
nullifyStaticData()
{
  _temp_numDims             = 0;
  _temp_globalShape         = Teuchos::ArrayRCP< int >();
  _temp_globalGhostShape    = Teuchos::ArrayRCP< int >();
  _temp_localOwnShape       = Teuchos::ArrayRCP< int >();
  _temp_localShape          = Teuchos::ArrayRCP< int >();
  _temp_localInteriorBounds = Teuchos::ArrayRCP< Teuchos::Tuple< int, 2 > >();
  _temp_axisStart           = Teuchos::ArrayRCP< int >();
  _temp_axisNumProcs        = Teuchos::ArrayRCP< int >();
  _temp_axisRanks           = Teuchos::ArrayRCP< int >();
  _temp_halos               = Teuchos::ArrayRCP< Teuchos::Tuple< int, 2 > >();
  _temp_ghostPoints         = Teuchos::ArrayRCP< int >();
  _temp_periodic            = Teuchos::ArrayRCP< int >();
  _temp_globalStrides       = Teuchos::ArrayRCP< int >();
  _temp_localStrides        = Teuchos::ArrayRCP< int >();
  _temp_elements            = Teuchos::ArrayRCP< int >();
}
