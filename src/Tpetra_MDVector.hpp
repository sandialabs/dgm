#ifndef TPETRA_MDVECTOR_HPP
#define TPETRA_MDVECTOR_HPP

//! \file   Tpetra_MDVector.hpp
//! \brief  Tpetra MDVector declaration and implementation
//! \author Bill Spotz

// Tpetra includes
#include "Tpetra_MultiVector.hpp"
#include "Tpetra_Vector.hpp"

// Local includes
#include "Tpetra_MDMap.hpp"

//////////////////////////////////////////////////////////////////
//
// To Do List:
// -----------
// * Non-member constructors?  Concrete dimensionality sub-classes?
// * Array bounds checking in DEBUG mode
//
//////////////////////////////////////////////////////////////////

namespace Tpetra
{

//! A class for using dense, distributed, n-dimensional vectors

//! The MDVector class inherits from \c Tpetra::Vector and
//! enforces structure by requiring a \c MDMap at
//! construction.

template< class Scalar,
          class LocalOrdinal,
          class GlobalOrdinal = LocalOrdinal,
          class Node = KokkosClassic::DefaultNode::DefaultNodeType >
class MDVector : public Tpetra::Vector< Scalar,
                                        LocalOrdinal,
                                        GlobalOrdinal,
                                        Node >
{

public:

  //! MDMap constructor

  //! This constructor mirrors the \c Vector constructor that takes a
  //! \c Map argument, but here the \c Map is required to be a \c
  //! MDMap
  MDVector(const Teuchos::RCP< const MDMap< LocalOrdinal,
                                            GlobalOrdinal,
                                            Node > > & map,
           bool zeroOut = true);

  //! Copy constructor
  MDVector(const MDVector< Scalar,
                           LocalOrdinal,
                           GlobalOrdinal,
                           Node > & source);

  //! MDMap and ArrayView constructor

  //! Determine the structure and decomposition via the \c
  //! MDMap argument, and initialize the values with the \c
  //! Teuchos::ArrayView argument
  MDVector(const Teuchos::RCP< const MDMap< LocalOrdinal,
                                            GlobalOrdinal,
                                            Node > > & map,
           const Teuchos::ArrayView< Scalar > & A);

  //! Destructor
  virtual ~MDVector();

  //! Set operator, ArrayView index

  //! Note that local axis index (0,0,...) refers to the index of the
  //! first element of the interior, or non-halo region
  inline Scalar & operator[](const Teuchos::ArrayView< LocalOrdinal > index);

  //! Set operator, single index
  inline Scalar & operator()(const LocalOrdinal index);

  //! Set operator, two indexes

  //! Note that local axis index (0,0) refers to the index of the
  //! first element of the interior, or non-halo region
  inline Scalar & operator()(const LocalOrdinal i, const LocalOrdinal j);

  //! Set operator, three indexes

  //! Note that local axis index (0,0,0) refers to the index of the
  //! first element of the interior, or non-halo region
  inline Scalar & operator()(const LocalOrdinal i,
                             const LocalOrdinal j,
                             const LocalOrdinal k);

  //! Get operator, ArrayView index

  //! Note that local axis index (0,0,...) refers to the index of the
  //! first element of the interior, or non-halo region
  inline const Scalar &
  operator[](const Teuchos::ArrayView< LocalOrdinal > index) const;

  //! Get operator, single index
  inline const Scalar & operator()(const LocalOrdinal index) const;

  //! Get operator, two indexes

  //! Note that local axis index (0,0) refers to the index of the
  //! first element of the interior, or non-halo region
  inline const Scalar & operator()(const LocalOrdinal i,
                                   const LocalOrdinal j) const;

  //! Get operator, three indexes

  //! Note that local axis index (0,0,0) refers to the index of the
  //! first element of the interior, or non-halo region
  inline const Scalar & operator()(const LocalOrdinal i,
                                   const LocalOrdinal j,
                                   const LocalOrdinal k) const;

  //! MDMap accessor method
  const Teuchos::RCP< const MDMap< LocalOrdinal, GlobalOrdinal, Node > > &
  getMDMap() const;

private:

  //! Initialize the indexing variables

  //! Compute the _buffer pointer and whichever offsets -- _offset1,
  //! _offset2 and _offset3 -- are appropriate for the MDVector.
  void initializeIndexing();

  //! An RCP pointing to the \c MDMap object
  Teuchos::RCP< const MDMap< LocalOrdinal,
                             GlobalOrdinal,
                             Node> > _mdMap;

  //! Halo sizes along each axis at each boundary
  const Teuchos::ArrayRCP< Teuchos::Tuple< int, 2 > > _halos;

  //! Local striding information
  const Teuchos::ArrayRCP< LocalOrdinal > _localStrides;

  //! Pointer to data buffer for efficient indexing
  Scalar * _buffer;

  //! 1D indexing offset
  LocalOrdinal _offset1;

  //! 2D indexing offset
  LocalOrdinal _offset2;

  //! 3D indexing offset
  LocalOrdinal _offset3;

};

//////////////////////////////////////////////////////////////////////
// Implementations
//////////////////////////////////////////////////////////////////////

//! Constructor from MDMap and optional bool
template< class Scalar, class LocalOrdinal, class GlobalOrdinal, class Node >
MDVector< Scalar, LocalOrdinal, GlobalOrdinal, Node >::
MDVector(const Teuchos::RCP< const MDMap< LocalOrdinal,
                                          GlobalOrdinal,
                                          Node > > & map,
                 bool zeroOut) :
  Tpetra::Vector< Scalar, LocalOrdinal, GlobalOrdinal, Node >(map, zeroOut),
  _mdMap(map),
  _halos(map->getHalos()),
  _localStrides(map->getLocalStrides())
{
  initializeIndexing();
}

//! Copy constructor
template< class Scalar, class LocalOrdinal, class GlobalOrdinal, class Node >
MDVector< Scalar, LocalOrdinal, GlobalOrdinal, Node >::
MDVector(const MDVector< Scalar, LocalOrdinal,
                         GlobalOrdinal,
                         Node > & source) :
  Tpetra::Vector< Scalar, LocalOrdinal, GlobalOrdinal, Node >(source),
  _mdMap(source.getMDMap()),
  _halos(_mdMap->getHalos()),
  _localStrides(_mdMap->getLocalStrides())
{
  initializeIndexing();
}

//! Constructor from MDMap and Teuchos::ArrayView arguments
template< class Scalar, class LocalOrdinal, class GlobalOrdinal, class Node >
MDVector< Scalar, LocalOrdinal, GlobalOrdinal, Node >::
MDVector(const Teuchos::RCP< const MDMap< LocalOrdinal,
                                          GlobalOrdinal,
                                          Node > > & map,
                 const Teuchos::ArrayView< Scalar > & A) :
  Tpetra::Vector< Scalar, LocalOrdinal, GlobalOrdinal, Node >(map, A),
  _mdMap(map),
  _halos(map->getHalos()),
  _localStrides(map->getLocalStrides())
{
  initializeIndexing();
}

//! Destructor
template< class Scalar, class LocalOrdinal, class GlobalOrdinal, class Node >
MDVector< Scalar, LocalOrdinal, GlobalOrdinal, Node >::
~MDVector()
{
}

//! Initialize the indexing data
template< class Scalar, class LocalOrdinal, class GlobalOrdinal, class Node >
void
MDVector< Scalar, LocalOrdinal, GlobalOrdinal, Node >::
initializeIndexing()
{
  // Extract the raw pointer to the data buffer
  _buffer = this->getDataNonConst(0).getRawPtr();
  // Compute the 1D offset
  _offset1 = _mdMap->getHalos(0)[0] * _localStrides[0];
  // Compute the 2D offset
  _offset2 = _offset1;
  if (_mdMap->getNumDims() > 1)
    _offset2 += _mdMap->getHalos(1)[0] * _localStrides[1];
  // Compute the 3D offset
  _offset3 = _offset2;
  if (_mdMap->getNumDims() > 2)
    _offset3 += _mdMap->getHalos(2)[0] * _localStrides[2];
}

//! Set operator, ArrayView index
template< class Scalar, class LocalOrdinal, class GlobalOrdinal, class Node >
Scalar &
MDVector< Scalar, LocalOrdinal, GlobalOrdinal, Node >::
operator[](const Teuchos::ArrayView< LocalOrdinal > index)
{
  return _buffer[_mdMap->getLocalElement(index)];
}

//! Set operator, single index
template< class Scalar, class LocalOrdinal, class GlobalOrdinal, class Node >
Scalar &
MDVector< Scalar, LocalOrdinal, GlobalOrdinal, Node >::
operator()(const LocalOrdinal index)
{
  return _buffer[index + _offset1];
}

//! Set operator, two indexes
template< class Scalar, class LocalOrdinal, class GlobalOrdinal, class Node >
Scalar &
MDVector< Scalar, LocalOrdinal, GlobalOrdinal, Node >::
operator()(const LocalOrdinal i, const LocalOrdinal j)
{
  return _buffer[i*_localStrides[0] + j*_localStrides[1] + _offset2];
}

//! Set operator, three indexes
template< class Scalar, class LocalOrdinal, class GlobalOrdinal, class Node >
Scalar &
MDVector< Scalar, LocalOrdinal, GlobalOrdinal, Node >::
operator()(const LocalOrdinal i,
           const LocalOrdinal j,
           const LocalOrdinal k)
{
  return _buffer[i*_localStrides[0] + j*_localStrides[1] +
                 k*_localStrides[2] + _offset3];
}

//! Get operator, ArrayView index
template< class Scalar, class LocalOrdinal, class GlobalOrdinal, class Node >
const Scalar &
MDVector< Scalar, LocalOrdinal, GlobalOrdinal, Node >::
operator[](const Teuchos::ArrayView< LocalOrdinal > index) const
{
  return _buffer[_mdMap->getLocalElement(index)];
}

//! Get operator, single index
template< class Scalar, class LocalOrdinal, class GlobalOrdinal, class Node >
const Scalar &
MDVector< Scalar, LocalOrdinal, GlobalOrdinal, Node >::
operator()(const LocalOrdinal index) const
{
  return _buffer[index + _offset1];
}

//! Get operator, two indexes
template< class Scalar, class LocalOrdinal, class GlobalOrdinal, class Node >
const Scalar &
MDVector< Scalar, LocalOrdinal, GlobalOrdinal, Node >::
operator()(const LocalOrdinal i, const LocalOrdinal j) const
{
  return _buffer[i*_localStrides[0] + j*_localStrides[1] + _offset2];
}

//! Get operator, three indexes
template< class Scalar, class LocalOrdinal, class GlobalOrdinal, class Node >
const Scalar &
MDVector< Scalar, LocalOrdinal, GlobalOrdinal, Node >::
operator()(const LocalOrdinal i,
           const LocalOrdinal j,
           const LocalOrdinal k) const
{
  return _buffer[i*_localStrides[0] + j*_localStrides[1] +
                 k*_localStrides[2] + _offset3];
}

//! MDMap retrieval method
template< class Scalar, class LocalOrdinal, class GlobalOrdinal, class Node >
const Teuchos::RCP< const MDMap< LocalOrdinal, GlobalOrdinal, Node > > &
MDVector< Scalar, LocalOrdinal, GlobalOrdinal, Node >::
getMDMap() const
{
  return _mdMap;
}

}  // Namespace Tpetra

#endif
