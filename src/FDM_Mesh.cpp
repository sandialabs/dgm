//! \file   FDM_Mesh.cpp
//! \brief  Finite Difference Mesh implementation
//! \author Bill Spotz

// FDM includes
#include "FDM_Mesh.hpp"

// Domi include
#include "Domi_MDVector.hpp"

namespace FDM
{

////////////////////////////////////////////////////////////////////////

ArrayRCP< MDVectorPtr >
Mesh::constructCoordinates(const MDMapPtr mdMap)
{
  ArrayRCP< MDVectorPtr > result(mdMap->numDims());
  for (int i = 0; i < result.size(); ++i)
    result[i] = Teuchos::rcp(new Domi::MDVector< Scalar >(mdMap));
  return result;
}

////////////////////////////////////////////////////////////////////////

ArrayRCP< string >
Mesh::initializeCoordinateNames(const int numDims,
                                const ArrayView< string > coordinateNames)
{
  // Construct the array of coordinate names
  ArrayRCP< string > result(numDims);

  // Copy and/or initialize the coordinate names from the constructor
  // argument
  for (int i=0; i < numDims; ++i)
  {
    if (i < coordinateNames.size())
    {
      result[i] = coordinateNames[i];
    }
    else
    {
      switch(i)
      {
      case 0:
        result[i] = "x";
        break;
      case 1:
        result[i] = "y";
        break;
      case 2:
        result[i] = "z";
        break;
      case 3:
        result[i] = "t";
        break;
      default:
        result[i] = "COORDINATE";
      }
    }
  }
  return result;
}

////////////////////////////////////////////////////////////////////////

MDMapPtr
Mesh::getMapFromCoordinates(const ArrayView< MDVectorPtr > coordinates)
{
  if (coordinates.size() == 0)
    throw std::runtime_error("Coordinates array is empty");
  MDMapPtr mdMap = coordinates[0]->getMDMap();
  for (int i = 1; i < coordinates.size(); ++i)
  {

    if (!mdMap->isSameAs(*(coordinates[i]->getMDMap())))
      throw std::runtime_error("Coordinates have different maps");
  }
  return mdMap;
}

////////////////////////////////////////////////////////////////////////

Mesh::Mesh(const MDMapPtr                 mdMap,
           const ArrayView< std::string > coordinateNames) :
  _mdMap(mdMap),
  _ownMdMap(),
  _mdComm(mdMap->getMDComm()),
  _coordinates(constructCoordinates(mdMap)),
  _coordinateNames(initializeCoordinateNames(mdMap->numDims(),
                                             coordinateNames))
{
}

////////////////////////////////////////////////////////////////////////

Mesh::Mesh(const ArrayView< MDVectorPtr > coordinates,
           const ArrayView< string >      coordinateNames) :
  _mdMap(getMapFromCoordinates(coordinates)),
  _ownMdMap(),
  _mdComm(_mdMap->getMDComm()),
  _coordinates(initializeCoordinates< MDVectorPtr >(coordinates)),
  _coordinateNames(initializeCoordinateNames
                   //(boost::numeric_cast<int>(coordinates.size()),
                   ((int)(coordinates.size()),
                    coordinateNames))
{
}

////////////////////////////////////////////////////////////////////////

Mesh::Mesh(const MDMapPtr                 mdMap,
           const ArrayView< MDVectorPtr > coordinates,
           const ArrayView< std::string > coordinateNames) :
  _mdMap(mdMap),
  _ownMdMap(),
  _mdComm(mdMap->getMDComm()),
  _coordinates(initializeCoordinates< MDVectorPtr >(coordinates)),
  _coordinateNames(initializeCoordinateNames
                   //(boost::numeric_cast<int>(coordinates.size()),
                   ((int)(coordinates.size()),
                    coordinateNames))
{
}

////////////////////////////////////////////////////////////////////////

Mesh::Mesh(const Mesh & source) :
  _mdMap(          source._mdMap          ),
  _ownMdMap(       source._ownMdMap       ),
  _mdComm(         source._mdComm         ),
  _coordinates(    source._coordinates    ),
  _coordinateNames(source._coordinateNames)
{
}

////////////////////////////////////////////////////////////////////////

Mesh::Mesh(const Mesh & parent,
           int axis,
           Domi::dim_type index) :
  _mdMap(Teuchos::rcp(new Domi::MDMap(*parent._mdMap,
                                        axis,
                                        index))),
  _ownMdMap(),
  _mdComm(_mdMap->getMDComm()),
  _coordinates(),
  _coordinateNames()
{
  if (_mdMap->onSubcommunicator())
  {
    TEUCHOS_TEST_FOR_EXCEPTION(
      (axis < parent.numDims()),
      Domi::InvalidArgument,
      "axis = " << axis << ", but parent number of dims = "
                << parent.numDims());

    TEUCHOS_TEST_FOR_EXCEPTION(
      (index < (Domi::dim_type)parent.getGlobalDim(axis)),
      Domi::InvalidArgument,
      "index = " << index << ", but parent dimension for axis " << axis
                 << " = " << parent.getGlobalDim(axis));

    int newDims = _mdMap->numDims();
    _coordinates.resize(newDims);
    _coordinateNames.resize(newDims);

    int newAxis = 0;
    for (int i = 0; i < parent.numDims(); ++i)
    {
      if (i != axis)
      {
        _coordinates[    newAxis] = _coordinates[    i];
        _coordinateNames[newAxis] = _coordinateNames[i];
        ++newAxis;
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////

Mesh::Mesh(const Mesh & parent,
           int axis,
           const Domi::Slice & slice,
           int bndryPad) :
  _mdMap(Teuchos::rcp(new Domi::MDMap(*parent._mdMap,
                                        axis,
                                        slice,
                                        bndryPad))),
  _ownMdMap(),
  _mdComm(_mdMap->getMDComm()),
  _coordinates(parent._coordinates),
  _coordinateNames(parent._coordinateNames)
{
  // N.B.: We have to take slices of the coordinate data, which has to
  // be done on all of the processors of the parent Field, or MPI will
  // hang.
  if (_coordinates[axis]->numDims() == 1)
  {
    // 1D coordinate data
    _coordinates[axis] =
      Teuchos::rcp(new Domi::MDVector< FDM::Scalar >(*_coordinates[axis],
                                                     0,
                                                     slice,
                                                     bndryPad));
  }
  else if (_coordinates[axis]->numDims() > 1)
  {
    // Multi-dimensional coordinate data
    for (int i = 0; i < parent.numDims(); ++i)
    {
      _coordinates[i] =
        Teuchos::rcp(new Domi::MDVector< FDM::Scalar >(*_coordinates[i],
                                                       axis,
                                                       slice,
                                                       bndryPad));
    }
  }
}

////////////////////////////////////////////////////////////////////////

Mesh::Mesh(const Mesh & parent,
           const Teuchos::ArrayView< Domi::Slice > & slices,
           const Teuchos::ArrayView< int > & bndryPad)
{
  // Temporarily store the number of dimensions
  int numDims = parent.numDims();

  // Sanity check on dimensions
  TEUCHOS_TEST_FOR_EXCEPTION(
    (slices.size() != numDims),
    Domi::InvalidArgument,
    "number of slices = " << slices.size() << " != parent Mesh number of "
    "dimensions = " << numDims);

  // Apply the single-Slice constructor to each axis in succession
  Mesh tempMesh1(parent);
  for (int axis = 0; axis < numDims; ++axis)
  {
    int bndryPadding = (axis < bndryPad.size()) ? bndryPad[axis] : 0;
    Mesh tempMesh2(tempMesh1,
                   axis,
                   slices[axis],
                   bndryPadding);
    tempMesh1 = tempMesh2;
  }
  *this = tempMesh1;
}

////////////////////////////////////////////////////////////////////////

Mesh::~Mesh()
{
}

////////////////////////////////////////////////////////////////////////

Mesh & Mesh::operator=(const Mesh & source)
{
  // Check for assignment to self
  if (this == &source) return *this;
  // Copy source to *this and return
  *this = source;
  return *this;
}

////////////////////////////////////////////////////////////////////////

const MDMapPtr
Mesh::getOwnMDMap()
{
  if (_ownMdMap.is_null())
  {
    if (_mdMap->hasPadding())
    {
      // WFS: we may need to check the MDComm for periodicity, and if
      // it exists, construct a new MDComm that is not periodic.
      _ownMdMap =
        Teuchos::rcp(new Domi::MDMap(_mdMap->getMDComm(),
                                        _mdMap->getGlobalDims()(),
                                        ArrayView< int >(), // No comm padding
                                        _mdMap->getBndryPadSizes()(),
                                        ArrayView< int >(), // No communication,
                                        // so replicated boundaries are not an issue
                                        _mdMap->getLayout() ));
    }
    else
    {
      _ownMdMap = _mdMap;
    }
  }
  return _ownMdMap;
}

////////////////////////////////////////////////////////////////////////

Scalar
Mesh::getCoordinateAtPoint(Ordinal i, int axis) const
{
  return _coordinates[axis]->getDataNonConst()(i);
}

////////////////////////////////////////////////////////////////////////

Array< Scalar >
Mesh::getCoordinatesAtPoint(Ordinal i, Ordinal j) const
{
  if (numDims() != 2)
  {
    stringstream msg;
    msg << "getCoordinatesAtPoint(Ordinal i, Ordinal j) "
        << "requires 2D mesh, but mesh is " << numDims() << "D";
    throw std::domain_error(msg.str());
  }
  Array< Scalar > coords(2);
  coords[0] = getCoordinateAtPoint(i, 0);
  coords[1] = getCoordinateAtPoint(j, 1);
  return coords;
}

////////////////////////////////////////////////////////////////////////

Array< Scalar >
Mesh::getCoordinatesAtPoint(Ordinal i,
                            Ordinal j,
                            Ordinal k) const
{
  if (numDims() != 3)
  {
    stringstream msg;
    msg << "getCoordinatesAtPoint(Ordinal i, Ordinal j, Ordinal k) "
        << "requires 3D mesh, but mesh is " << numDims() << "D";
    throw std::domain_error(msg.str());
  }
  Array< Scalar > coords(3);
  coords[0] = getCoordinateAtPoint(i, 0);
  coords[1] = getCoordinateAtPoint(j, 1);
  coords[2] = getCoordinateAtPoint(k, 2);
  return coords;
}

////////////////////////////////////////////////////////////////////////

string
Mesh::description() const
{
  std::stringstream ss;
  Ordinal numGlobalGridPoints = 1;
  ss << "FDM::Mesh{";
  for (int i = 0; i < numDims(); ++i)
  {
    ss << _coordinateNames[i];
    if (i < numDims() - 1)
      ss << ",";
    numGlobalGridPoints *= _mdMap->getGlobalDim(i);
  }
  ss << "}(grid points=" << numGlobalGridPoints << ")";
  return ss.str();
}

////////////////////////////////////////////////////////////////////////

bool
Mesh::operator==(const Mesh & mesh2) const
{
  if (this == &mesh2) return true;
  if (numDims() != mesh2.numDims())    return false;
  if (_mdComm.get()  != mesh2.getMDComm().get()) return false;
  if (!_mdMap->isSameAs(*(mesh2.getMDMap())))   return false;
  for (int i = 0; i < numDims(); ++i)
  {
    if (_coordinateNames[i] != mesh2.getCoordinateName(i)) return false;
    Domi::MDArrayView< const Scalar > data;
    Domi::MDArrayView< const Scalar > coord;
    data = _coordinates[i]->getData();
    coord = mesh2.getCoordinates(i);
    for (Ordinal j = 0; j < (Ordinal)data.size(); ++j)
      if (data[j] != coord[j]) return false;
  }
  return true;
}

////////////////////////////////////////////////////////////////////////

}  // Namespace FDM
