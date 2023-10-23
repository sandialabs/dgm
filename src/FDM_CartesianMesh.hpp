#ifndef FDM_CARTESIANMESH_HPP
#define FDM_CARTESIANMESH_HPP

//! \file   FDM_CartesianMesh.hpp
//! \brief  Declarations for the FDM CartesianMesh
//! \author Bill Spotz

// Standard includes
#include <stdexcept>

// FDM includes
#include "FDM_Mesh.hpp"

// Teuchos classes
using Teuchos::Array;

namespace FDM
{

//! FDM Cartesian Mesh class

//! The CartesianMesh class describes meshes that are 1D, 2D or 3D,
//! but whose coordinates can be accessed with a single index.  In
//! practice this is enforced by requiring that the CartesianMesh be
//! constructed with a MDMap, and that the coordinates be built on the
//! getAxisMaps() of that MDMap.
class CartesianMesh : public Mesh
{

public:

  /** \brief CartesianMesh constructor without coordinates
   *
   * \param mdMap [in] Full MDMap for the Cartesian Mesh. The
   *        coordinates will be built from the axis maps of argument
   *        mdMap.
   *
   * \param coordinateNames [in] An array of strings that represent
   *        the name of each coordinate.
   *
   * User provides a MDMap and an optional set of coordinate names.
   * Coordinate vectors are allocated from the MDMap axis maps and
   * are uninitialized.
   */
  CartesianMesh(const MDMapPtr            mdMap,
                const ArrayView< string > coordinateNames =
                    ArrayView< string >());

  /** \brief CartesianMesh constructor with coordinates
   *
   * \param mdMap [in] Full MDMap for the Cartesian Mesh.
   *
   * \param coordinates [in] An array of RCPs to MDVectors that
   *        represent the coordinate values of the mesh. The MDMaps of
   *        each MDVector should be the corresponding axis map of the
   *        mdMap argument.
   *
   * \param coordinateNames [in] An array of strings that represent
   *        the name of each coordinate.
   *
   * User provides a MDMap, a set of coordinates and an optional set
   * of coordinate vectors.  The coordinates are Domi::Vectors
   * constructed from the MDMap axis maps.  If the coordinate names
   * are not provided, they will be given default names.
   */
  CartesianMesh(const MDMapPtr                 mdMap,
                const ArrayView< MDVectorPtr > coordinates,
                const ArrayView< string >      coordinateNames =
                    ArrayView< string >());

  /** \brief Parent/single global ordinal sub-mesh constructor
   *
   * \param parent [in] a CartesianMesh, from which this sub-mesh will
   *        be derived
   *
   * \param axis [in] the axis to which this index ordinal applies
   *
   * \param index [in] the global ordinal that defines the sub-mesh
   */
  CartesianMesh(const CartesianMesh & parent,
                int axis,
                Domi::dim_type index);

  /** \brief Parent/single slice sub-mesh constructor
   *
   * \param parent [in] a CartesianMesh, from which this sub-mesh will
   *        be derived
   *
   * \param axis [in] the axis to which this slice applies
   *
   * \param slice [in] a slice of global ordinals describing the
   *        sub-mesh
   *
   * \param bndryPad [in] the boundary padding along the altered axis
   *        of the new sub-mesh.  This may include indexes from the
   *        boundary padding of the parent CartesianMesh, but it does
   *        not have to.
   */
  CartesianMesh(const CartesianMesh & parent,
                int axis,
                Domi::Slice slice,
                int bndryPad);

  /** \brief CartesianMesh destructor
   */
  virtual ~CartesianMesh();

  /* \brief Set coordinates using a delta
   *
   * \param axis [in] The axis index of the coordinate to be set
   *
   * \param coord0 [in] Value to set the global lower boundary of the
   *        coordinate axis. Note that this will be assigned to the
   *        first non-boundary-padding index.
   *
   * \param delta [in] Value of the uniform difference between
   *        discrete coordinates
   */
  void setCoordinatesWithDelta(int axis,
                               const Scalar coord0,
                               const Scalar delta);

  /* \brief Set coordinates using a range
   *
   * \param axis [in] The axis index of the coordinate to be set
   *
   * \param coord0 [in] Value to set the global lower boundary of the
   *        coordinate axis. Note that this will be assigned to the
   *        first non-boundary-padding index.
   *
   * \param coord1 [in] Value to set the global upper boundary of the
   *        coordinate axis. Note that this will be assigned to the
   *        last non-boundary-padding index.
   */
  void setCoordinatesWithRange(int axis,
                               const Scalar coord0,
                               const Scalar coord1);

  /** \brief Is a given coordinate on this processor?
   *
   * \param axis [in] The axis index of the coordinate in question
   *
   * \param coord [in] The value of the coordinate in question along
   *        the given axis
   *
   * \param includePad [in] Flag indicating whether the padding should
   *        be included in the search
   */
  bool coordinateOnProcessor(int    axis,
                             Scalar coord,
                             bool   includePad=false) const;

  /** \brief Return the index of the coordinate that is just less than
   *         or equal to the given coordinate
   *
   * \param axis [in] The axis index of the coordinate in question
   *
   * \param coord [in] The value of the coordinate in question along
   *        the given axis
   *
   * \param includePad [in] Flag indicating whether the padding should
   *        be included in the search
   */
  Ordinal nearestCoordinateIndex(int    axis,
                                 Scalar coord,
                                 bool   includePad=false) const;

private:

  // Construct the coordinates
  static ArrayView< MDVectorPtr >
  constructCoordinates(const MDMapPtr mdMap);

  // Nullify the static class data
  void nullifyStaticData();

  // Temporary coordinates
  static ArrayRCP< MDVectorPtr > _temp_coordinates;

};

////////////////////////////////////////////////////////////

//! Pointer to CartesianMesh
typedef Teuchos::RCP< CartesianMesh > CartesianMeshPtr;

}  // Namespace FDM

#endif
