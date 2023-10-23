
//! \file   FDM_CartesianMesh.cpp
//! \brief  Implementation of the FDM cartesian mesh class
//! \author Bill Spotz

#include "FDM_CartesianMesh.hpp"

namespace FDM
{
////////////////////////////////////////////////////////////////////////

ArrayRCP< MDVectorPtr >
CartesianMesh::_temp_coordinates = ArrayRCP< MDVectorPtr >();

////////////////////////////////////////////////////////////////////////

CartesianMesh::CartesianMesh(const MDMapPtr            mdMap,
                             const ArrayView< string > coordinateNames) :
  Mesh(mdMap, constructCoordinates(mdMap), coordinateNames)
{
  nullifyStaticData();
}

////////////////////////////////////////////////////////////////////////

CartesianMesh::CartesianMesh(const MDMapPtr                 mdMap,
                             const ArrayView< MDVectorPtr > coordinates,
                             const ArrayView< string >      coordinateNames) :
  Mesh(mdMap, coordinates, coordinateNames)
{
  // Check that the individual coordinate Maps correspond to the MDMap
  // getAxisMaps() members
  for (int i=0; i < numDims(); ++i)
  {
    if (!getCoordinates()[i]->getMDMap()->isSameAs(*(mdMap->getAxisMap(i))))
      throw std::invalid_argument("Coordinate Maps do not match CartesianMesh "
                                  "MDMap");
  }
}

////////////////////////////////////////////////////////////////////////

CartesianMesh::CartesianMesh(const CartesianMesh & parent,
                             int axis,
                             Domi::dim_type index) :
  Mesh(parent, axis, index)
{
}

////////////////////////////////////////////////////////////////////////

CartesianMesh::CartesianMesh(const CartesianMesh & parent,
                             int axis,
                             Domi::Slice slice,
                             int bndryPad) :
  Mesh(parent, axis, slice, bndryPad)
{
}

////////////////////////////////////////////////////////////////////////

CartesianMesh::~CartesianMesh()
{
}

////////////////////////////////////////////////////////////////////////

void
CartesianMesh::setCoordinatesWithDelta(int axis,
                                       const Scalar coord0,
                                       const Scalar delta)
{
  Domi::MDArrayView< FDM::Scalar > coord = getCoordinatesNonConst(axis);
  FDM::MDMapPtr axisMap = getMDMap()->getAxisMap(axis);
  Domi::Slice bounds    = axisMap->getLocalBounds(0,true);
  Domi::dim_type i0     = axisMap->getLocalBounds(0,false).start();
  Domi::dim_type I0     = axisMap->getGlobalRankBounds(0,false).start()-i0;
  for (Domi::dim_type i = bounds.start(); i < bounds.stop(); ++i)
  {
    coord(i) = coord0 + (i-i0+I0) * delta;
  }
}

////////////////////////////////////////////////////////////////////////

void
CartesianMesh::setCoordinatesWithRange(int axis,
                                       const Scalar coord0,
                                       const Scalar coord1)
{
  Domi::MDArrayView< FDM::Scalar > coord = getCoordinatesNonConst(axis);
  FDM::MDMapPtr axisMap = getMDMap()->getAxisMap(axis);
  Domi::Slice gBounds   = axisMap->getLocalBounds(0,false);
  Domi::Slice bounds    = axisMap->getLocalBounds(0,true);
  Domi::dim_type i0     = gBounds.start();
  Domi::dim_type I0     = axisMap->getGlobalRankBounds(0,false).start()-i0;
  Scalar delta          = (coord1 - coord0) /
                          (gBounds.stop() - gBounds.start() - 1);
  for (Domi::dim_type i = bounds.start(); i < bounds.stop(); ++i)
  {
    coord(i) = coord0 + (i-i0+I0) * delta;
  }
}

////////////////////////////////////////////////////////////////////////

bool
CartesianMesh::coordinateOnProcessor(int    axis,
                                     Scalar coord,
                                     bool   includePad) const
{
  if (axis >= numDims()) return false;
  MDMapPtr axisMap   = getMDMap()->getAxisMap(axis);
  Domi::Slice bounds = axisMap->getLocalBounds(0,includePad);
  Ordinal lo         = bounds.start();
  Ordinal hi         = bounds.stop();
  Domi::MDArrayView< const Scalar > coords = getCoordinates(axis);
  return ((coords(lo) <= coord) && (coord <= coords(hi-1)));
}

////////////////////////////////////////////////////////////////////////

Ordinal
CartesianMesh::nearestCoordinateIndex(int    axis,
                                      Scalar coord,
                                      bool   includePad) const
{
  if (coordinateOnProcessor(axis, coord, includePad))
  {
    MDMapPtr axisMap   = getMDMap()->getAxisMap(axis);
    Domi::Slice bounds = axisMap->getLocalBounds(0,includePad);
    Ordinal lo         = bounds.start()+1;
    Ordinal hi         = bounds.stop();
    Domi::MDArrayView< const Scalar > coords = getCoordinates(axis);
#if 0
    cout << "  CartesianMesh::nearestCoordinateIndex(): search range = ["
         << coords(lo) << "..." << coords(hi-1) << "]" << endl;
#endif
    for (Ordinal i = lo; i < hi; ++i)
    {
      if (coords(i) == coord) return  i ;
      if (coords(i) >  coord) return i-1;
    }
  }
  stringstream msg;
  msg << getCoordinateName(axis) << " = " << coord << " is not on "
      << "processor " << getMDComm()->getTeuchosComm()->getRank() << endl;
  throw std::out_of_range(msg.str());
}

////////////////////////////////////////////////////////////////////////

////////////////////////////
// Private static methods //
////////////////////////////

////////////////////////////////////////////////////////////////////////

ArrayView< MDVectorPtr >
CartesianMesh::constructCoordinates(const MDMapPtr mdMap)
{
  // typedef KokkosClassic::DefaultNode::DefaultNodeType node_type;

  // Initialize the static, temporary coordinates
  _temp_coordinates = ArrayRCP< MDVectorPtr >(mdMap->numDims());

  // Fill the static, temporary coordinates
  for (int i=0; i < mdMap->numDims(); ++i)
    _temp_coordinates[i] =
      Teuchos::rcp(new Domi::MDVector< Scalar >(mdMap->getAxisMap(i)));

  // Return a view of the static, temporary coordinates
  return _temp_coordinates();
}

////////////////////////////////////////////////////////////////////////

void
CartesianMesh::nullifyStaticData()
{
  _temp_coordinates = ArrayRCP< MDVectorPtr >();
}

////////////////////////////////////////////////////////////////////////

}  // Namespace FDM
