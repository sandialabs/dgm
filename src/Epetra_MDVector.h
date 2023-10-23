#ifndef EPETRA_MDVECTOR_H
#define EPETRA_MDVECTOR_H

//! \file Epetra_MDVector.h
//! \brief Finite Difference MDVector declaration and implementation
//! \author Bill Spotz

// Epetra includes
#include "Epetra_MultiVector.h"
#include "Epetra_Vector.h"

// Local includes
#include "Epetra_MDMap.h"

//////////////////////////////////////////////////////////////////
//
// To Do List:
// -----------
// * Non-member constructors?  Concrete dimensionality sub-classes?
// * Array bounds checking in DEBUG mode
//
//////////////////////////////////////////////////////////////////

//! A class for using dense, distributed, n-dimensional vectors

//! The Epetra_MDVector class inherits from \c Epetra_Vector and
//! enforces structure by requiring a \c Epetra_MDMap at construction.

class Epetra_MDVector : public Epetra_Vector
{

public:

  //! Epetra_MDVector constructor

  //! This constructor mirrors the \c Vector constructor that takes a
  //! \c Map argument, but here the \c Map is required to be a \c
  //! Epetra_MDMap
  Epetra_MDVector(const Teuchos::RCP< const Epetra_MDMap > & map,
                  bool zeroOut = true);

  //! Copy constructor
  Epetra_MDVector(const Epetra_MDVector &source);

  //! Epetra_MDMap and ArrayView constructor

  //! Determine the structure and decomposition via the \c
  //! Epetra_MDMap argument, and initialize the values with the \c
  //! Teuchos::ArrayView argument
  Epetra_MDVector(const Teuchos::RCP< const Epetra_MDMap > & map,
                  const Teuchos::ArrayView< double > & A);

  //! Destructor
  virtual ~Epetra_MDVector();

  //! Set operator, ArrayView index

  //! Note that local axis index (0,0,...) refers to the index of the
  //! first element of the interior, or non-halo region
  inline double & operator[](const Teuchos::ArrayView< int > index);

  //! Set operator, single index
  inline double & operator()(const int index);

  //! Set operator, two indexes

  //! Note that local axis index (0,0) refers to the index of the
  //! first element of the interior, or non-halo region
  inline double & operator()(const int i, const int j);

  //! Set operator, three indexes

  //! Note that local axis index (0,0,0) refers to the index of the
  //! first element of the interior, or non-halo region
  inline double & operator()(const int i,
                             const int j,
                             const int k);

  //! Get operator, ArrayView index

  //! Note that local axis index (0,0,...) refers to the index of the
  //! first element of the interior, or non-halo region
  inline const double & operator[](const Teuchos::ArrayView< int > index) const;

  //! Get operator, single index
  inline const double & operator()(const int index) const;

  //! Get operator, two indexes

  //! Note that local axis index (0,0) refers to the index of the
  //! first element of the interior, or non-halo region
  inline const double & operator()(const int i, const int j) const;

  //! Get operator, three indexes

  //! Note that local axis index (0,0,0) refers to the index of the
  //! first element of the interior, or non-halo region
  inline const double & operator()(const int i,
                                   const int j,
                                   const int k) const;

  //! Epetra_MDMap accessor method
  inline const Teuchos::RCP< const Epetra_MDMap > &
  getMDMap() const;

private:

  //! Initialize the indexing variables

  //! Compute the _buffer pointer and whichever offsets -- _offset1,
  //! _offset2 and _offset3 -- are appropriate for the
  //! Epetra_MDVector.
  void initializeIndexing();

  //! An RCP pointing to the \c Epetra_MDMap object
  Teuchos::RCP< const Epetra_MDMap > _mdMap;

  //! Halo sizes along each axis at each boundary
  const Teuchos::ArrayRCP< Teuchos::Tuple< int, 2 > > _halos;

  //! Local striding information
  const Teuchos::ArrayRCP< int > _localStrides;

  //! Pointer to data buffer for efficient indexing
  double * _buffer;

  //! 1D indexing offset
  int _offset1;

  //! 2D indexing offset
  int _offset2;

  //! 3D indexing offset
  int _offset3;

};

//////////////////////////////////////////////////////////////////////
// In-line implementations
//////////////////////////////////////////////////////////////////////

//! Set operator, ArrayView index
double &
Epetra_MDVector::
operator[](const Teuchos::ArrayView< int > index)
{
  return _buffer[_mdMap->getLocalElement(index)];
}

//! Set operator, single index
double &
Epetra_MDVector::
operator()(const int index)
{
  return _buffer[index + _offset1];
}

//! Set operator, two indexes
double &
Epetra_MDVector::
operator()(const int i, const int j)
{
  return _buffer[i*_localStrides[0] + j*_localStrides[1] + _offset2];
}

//! Set operator, three indexes
double &
Epetra_MDVector::
operator()(const int i,
           const int j,
           const int k)
{
  return _buffer[i*_localStrides[0] + j*_localStrides[1] +
                 k*_localStrides[2] + _offset3];
}

//! Get operator, ArrayView index
const double &
Epetra_MDVector::
operator[](const Teuchos::ArrayView< int > index) const
{
  return _buffer[_mdMap->getLocalElement(index)];
}

//! Get operator, single index
const double &
Epetra_MDVector::
operator()(const int index) const
{
  return _buffer[index + _offset1];
}

//! Get operator, two indexes
const double &
Epetra_MDVector::
operator()(const int i, const int j) const
{
  return _buffer[i*_localStrides[0] + j*_localStrides[1] + _offset2];
}

//! Get operator, three indexes
const double &
Epetra_MDVector::
operator()(const int i,
           const int j,
           const int k) const
{
  return _buffer[i*_localStrides[0] + j*_localStrides[1] +
                 k*_localStrides[2] + _offset3];
}

//! Epetra_MDMap retrieval method
const Teuchos::RCP< const Epetra_MDMap > &
Epetra_MDVector::
getMDMap() const
{
  return _mdMap;
}

#endif
