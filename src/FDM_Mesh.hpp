#ifndef FDM_MESH_HPP
#define FDM_MESH_HPP

//! \file   FDM_Mesh.hpp
//! \brief  Finite Difference Mesh declaration
//! \author Bill Spotz

// System includes
#include <string>
using std::string;

// FDM includes
#include "FDM_Types.hpp"

// Domi includes
#include "Domi_MDMap.hpp"

// Teuchos classes
using Teuchos::Array;
using Teuchos::ArrayView;
using Teuchos::ArrayRCP;
using Teuchos::Tuple;

namespace FDM
{

//! FDM Mesh class

//! The FDM::Mesh class is the most general type of finite
//! differencing mesh.  It is a structured mesh and uses MDMap for
//! domain decomposition and MDVectors for coordinate data.
class Mesh : public DTK::Mesh, public Teuchos::Describable
{
public:

  /** \brief Mesh constructor with MDMap and optional coordinate names
   *
   * \param mdMap [in] MDMap for the mesh.  Should include
   *        communication padding.
   *
   * \param coordinateNames [in] An array of strings that represent
   *        the name of each coordinate.
   *
   * User provides a set of coordinate names and an MDMap.  The MDMap
   * determines the ownership map.  Coordinate vectors are allocated
   * based on the map and are uninitialized.
   */
  Mesh(const MDMapPtr            mdMap,
       const ArrayView< string > coordinateNames = ArrayView< string >());

  /** \brief Mesh constructor with structured coordinates
   *
   * \param coordinates [in] An array of RCPs to MDVectors that
   *        represent the coordinate values of the mesh. Each MDVector
   *        should have an MDMap that is the same dimension as the
   *        number of coordinates provided; OR each MDVector should
   *        have a 1D MDMap that is suitable as an axis map for the
   *        given axis.
   *
   * \param coordinateNames [in] An array of strings that represent
   *        the name of each coordinate.
   *
   * User provides a set of coordinates which are MDVectors, and an
   * optional set of coordinate names.  The MDVectors must either be
   * constructed with the same MDMap, which is used as the Mesh map
   * and to determine the ownership mesh; OR the MDVectors must be
   * constructed from the axis maps of a single MDMap.
   */
  Mesh(const ArrayView< MDVectorPtr > coordinates,
       const ArrayView< string >      coordinateNames = ArrayView< string >());

  /** \brief Mesh constructor with 1D coordinates
   *
   * \param mdMap [in] MDMap for the mesh.  Should include
   *        communication padding.
   *
   * \param coordinates [in] An array of RCPs to MDVectors that
   *        represent the coordinate values of the mesh. Each MDVector
   *        should have a 1D MDMap that is suitable as an axis map for
   *        the given axis, compatible with parameter mdMap.
   *
   * \param coordinateNames [in] An array of strings that represent
   *        the name of each coordinate.
   *
   * User provides a MDMap, a set of 1D coordinates, and an optional
   * set of coordinate names.  The coordinates are Domi::MDVectors
   * that must be constructed with the axis maps of the MDMap.
   */
  Mesh(const MDMapPtr                 mdMap,
       const ArrayView< MDVectorPtr > coordinates,
       const ArrayView< string >      coordinateNames = ArrayView< string >());

  /** \brief Parent/single global ordinal sub-mesh constructor
   *
   * \param parent [in] a Mesh, from which this sub-mesh will be
   *        derived
   *
   * \param axis [in] the axis to which this index ordinal applies
   *
   * \param index [in] the global ordinal that defines the sub-mesh
   */
  Mesh(const Mesh & parent,
       int axis,
       Domi::dim_type index);

  /** \brief Parent/single slice sub-mesh constructor
   *
   * \param parent [in] a Mesh, from which this sub-mesh will be
   *        derived
   *
   * \param axis [in] the axis to which this slice applies
   *
   * \param slice [in] a slice of global ordinals describing the
   *        sub-mesh
   *
   * \param bndryPad [in] the boundary padding along the altered axis
   *        of the new sub-mesh.  This may include indexes from the
   *        boundary padding of the parent Mesh, but it does not
   *        have to.
   */
  Mesh(const Mesh & parent,
       int axis,
       const Domi::Slice & slice,
       int bndryPad = 0);

  /** \brief Parent/array of slices sub-mesh constructor
   *
   * \param parent [in] a Mesh, from which this sub-mesh will be
   *        derived.
   *
   * \param slices [in] an array of Slices of global axis indexes that
   *        defines the sub-mesh.  These slices must not include
   *        indexes from the boundary padding along each axis.
   *
   * \param bndryPad [in] The boundary padding of the new sub-mesh.
   *        These may include indexes from the boundary padding of the
   *        parent Mesh, but they do not have to.
   */
  Mesh(const Mesh & parent,
       const Teuchos::ArrayView< Domi::Slice > & slices,
       const Teuchos::ArrayView< int > & bndryPad =
         Teuchos::ArrayView< int >());

  /** \brief Mesh copy constructor
   */
  Mesh(const Mesh & source);

  /** \brief Mesh destructor
   */
  virtual ~Mesh();

  /** \brief Assignment operator
   *
   * \param source [in]  Assignment source
   */
  Mesh & operator=(const Mesh & source);

  /** \brief Number of dimensions accessor method
   */
  inline 
  int numDims() const;

  /** \brief Communicator accessor method
   */
  inline const
  CommPtr getComm() const;

  /** \brief Multi-dimensional communicator accessor method
   */
  inline const
  MDCommPtr getMDComm() const;

  /** \brief MDMap accessor method
   */
  inline const
  MDMapPtr getMDMap() const;

  /** \brief Ownership map accessor method
   */
  const
  MDMapPtr getOwnMDMap();

  /** Processor rank accessor method
   */
  inline
  int getRank() const;

  /** \brief Array of coordinates accessor method
   */
  inline
  ArrayView< MDVectorPtr > getCoordinates() const;

  /** \brief Coordinate accessor method
   */
  inline
  Domi::MDArrayView< const Scalar > getCoordinates(int axis) const;

  /** \brief Non-const coordinate accessor method
   */
  inline
  Domi::MDArrayView< Scalar > getCoordinatesNonConst(int axis) const;

  /** \brief Get the coordinate at a specified 1D point
   */
  virtual Scalar getCoordinateAtPoint(Ordinal i,
                                      int axis=0) const;

  /** \brief Get the coordinates at a specified 2D point
   */
  Array< Scalar > getCoordinatesAtPoint(Ordinal i,
                                        Ordinal j) const;

  /** \brief Get the coordinates at a specified 3D point
   */
  Array< Scalar > getCoordinatesAtPoint(Ordinal i,
                                        Ordinal j,
                                        Ordinal k) const;

  /** \brief Coordinate names accessor method
   */
  inline ArrayRCP< string > getCoordinateNames() const;

  /** \brief Coordinate names accessor method
   *
   * \param axis [in] Axis whose coordinate is requested
   */
  inline string & getCoordinateName(int axis) const;

  /** \brief Description
   */
  virtual string description() const;

  /** \brief Equivalence
   *
   * \brief mesh2 [in] Mesh for comparison
   */
  bool operator==(const Mesh & mesh2) const;

  /** \brief Global dimensions accessor method
   */
  inline
  const Array< Domi::dim_type > getGlobalDims() const;

  /** \brief Global dimension accessor method
   *
   * \param axis [in] Axis whose dimension is requested
   *
   * \param withBndryPad [in] Flag whether to include boundary padding
   */
  inline
  Ordinal
  getGlobalDim(int axis,
               bool withBndryPad=false) const;

  /** \brief Global bounds accessor method
   *
   * \param axis [in] Axis whose global bounds are requested
   *
   * \param withBndryPad [in] Flag whether to include boundary padding
   */
  inline
  Domi::Slice
  getGlobalBounds(int axis,
                  bool withBndryPad=false) const;

  /** \brief Global rank bounds accessor method
   *
   * \param axis [in] Axis whose global rank bounds are requested
   *
   * \param withBndryPad [in] Flag whether to include boundary padding
   */
  inline
  Domi::Slice
  getGlobalRankBounds(int axis,
                      bool withBndryPad=false) const;

  /** \brief Get local ownership shape method
   */
  inline
  const Array< Domi::dim_type > getLocalDims() const;

  /** \brief Local dimension accessor method
   *
   * \param axis [in] Axis whose local dimension is requested
   *
   * \param withPad [in] Flag whether to include padding
   */
  inline Ordinal getLocalDim(int axis,
                             bool withPad=false) const;

  /** \brief Local bounds accessor method
   */
  inline Teuchos::ArrayView< const Domi::Slice > getLocalBounds() const;

  /** \brief Local bounds accessor method
   *
   * \param axis [in] Axis whose local bounds are requested
   */
  inline const Domi::Slice getLocalBounds(int axis) const;

  /** \brief Local interior bounds accessor method
   *
   * \param axis [in] Axis whose local interior bounds are requested
   */
  inline const Domi::Slice getLocalInteriorBounds(int axis) const;

private:

  // Construct the coordinates
  static ArrayRCP< MDVectorPtr >
  constructCoordinates(const MDMapPtr mdMap);

  // Initialize the coordinates
  template< class T >
  static ArrayRCP< T >
  initializeCoordinates(const ArrayView< T > coordinates);

  // Initialize the coordinates
  static ArrayRCP< MDVectorPtr >
  initializeCoordinates(const ArrayView< MDVectorPtr > coordinates);

  // Initialize the coordinate names
  static ArrayRCP< string >
  initializeCoordinateNames(const int numDims,
                            const ArrayView< string > coordinateNames);

  // Extract a map from the list of coordinates
  static MDMapPtr
  getMapFromCoordinates(const ArrayView< MDVectorPtr > coordinates);

private:

  // MDMap for the mesh
  const MDMapPtr          _mdMap;

  // Ownership MDMap for the mesh
  MDMapPtr                _ownMdMap;

  // MDComm for the mesh
  const MDCommPtr         _mdComm;

  // Coordinates for the mesh
  ArrayRCP< MDVectorPtr > _coordinates;

  // Array of coordinate names
  ArrayRCP< string >      _coordinateNames;

};

// Implementation of templated static method

//! Static routine to construct an ArrayRCP<T> from and ArrayView<T>.
/** T will be either VectorPtr or MDVectorPtr. */
template< class T >
ArrayRCP< T >
Mesh::initializeCoordinates(const ArrayView< T > coordinates)
{
  ArrayRCP< T > result(coordinates.size());
  for (int i = 0; i < result.size(); ++i)
    result[i] = coordinates[i];
  return result;
}

////////////////////////////
// Inline implementations //
////////////////////////////

////////////////////////////////////////////////////////////////////////

inline 
int
Mesh::numDims() const
{
  return _mdMap->numDims();
}

////////////////////////////////////////////////////////////////////////

inline const
CommPtr
Mesh::getComm() const
{
  return _mdComm->getTeuchosComm();
}

////////////////////////////////////////////////////////////////////////

inline const
MDCommPtr
Mesh::getMDComm() const
{
  return _mdComm;
}

////////////////////////////////////////////////////////////////////////

inline const
MDMapPtr
Mesh::getMDMap() const
{
  return _mdMap;
}

////////////////////////////////////////////////////////////////////////

inline
int
Mesh::getRank() const
{
  return _mdComm->getTeuchosComm()->getRank();
}

////////////////////////////////////////////////////////////////////////

inline
ArrayView< MDVectorPtr >
Mesh::getCoordinates() const
{
  return _coordinates();
}

////////////////////////////////////////////////////////////////////////

inline
Domi::MDArrayView< const Scalar >
Mesh::getCoordinates(int axis) const
{
  return _coordinates[axis]->getData();
}

////////////////////////////////////////////////////////////////////////

inline
Domi::MDArrayView< Scalar >
Mesh::getCoordinatesNonConst(int axis) const
{
  return _coordinates[axis]->getDataNonConst();
}

////////////////////////////////////////////////////////////////////////

inline ArrayRCP< string >
Mesh::getCoordinateNames() const
{
  return _coordinateNames;
}

////////////////////////////////////////////////////////////////////////

inline string &
Mesh::getCoordinateName(int axis) const
{
  return _coordinateNames[axis];
}

////////////////////////////////////////////////////////////////////////

inline
const Array< Domi::dim_type >
Mesh::getGlobalDims() const
{
  return _mdMap->getGlobalDims();
}

////////////////////////////////////////////////////////////////////////

inline
Ordinal
Mesh::getGlobalDim(int axis,
                   bool withBndryPad) const
{ 
  return _mdMap->getGlobalDim(axis, withBndryPad);
}

////////////////////////////////////////////////////////////////////////

inline
Domi::Slice
Mesh::getGlobalBounds(int axis,
                      bool withBndryPad) const
{
  return _mdMap->getGlobalBounds(axis, withBndryPad);
}

////////////////////////////////////////////////////////////////////////

inline
Domi::Slice
Mesh::getGlobalRankBounds(int axis,
                          bool withBndryPad) const
{
  return _mdMap->getGlobalRankBounds(axis, withBndryPad);
}

////////////////////////////////////////////////////////////////////////

inline
const Array< Domi::dim_type >
Mesh::getLocalDims() const
{
  return _mdMap->getLocalDims();
}

////////////////////////////////////////////////////////////////////////

inline
Ordinal
Mesh::getLocalDim(int axis,
                  bool withPad) const
{
  return _mdMap->getLocalDim(axis, withPad);
}

////////////////////////////////////////////////////////////////////////

inline
Teuchos::ArrayView< const Domi::Slice >
Mesh::getLocalBounds() const
{ 
  return _mdMap->getLocalBounds();
}

////////////////////////////////////////////////////////////////////////

inline
const Domi::Slice
Mesh::getLocalBounds(int axis) const
{ 
  return _mdMap->getLocalBounds(axis);
}

////////////////////////////////////////////////////////////////////////

inline
const Domi::Slice
Mesh::getLocalInteriorBounds(int axis) const
{ 
  return _mdMap->getLocalInteriorBounds(axis);
}

////////////////////////////////////////////////////////////////////////

/// Reference counted pointer to FDM::Mesh
typedef Teuchos::RCP< FDM::Mesh > MeshPtr;

} // namespace FDM

#endif
