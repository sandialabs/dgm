/** \file Epetra_MDVector.cpp
    \brief Implementation of a concrete Epetra MD vector
    \author Bill Spotz
*/

#include "Epetra_MDVector.h"

//! Constructor from Epetra_MDMap and optional bool
Epetra_MDVector::
Epetra_MDVector(const Teuchos::RCP< const Epetra_MDMap > & map,
                bool zeroOut) :
  Epetra_Vector(*map, zeroOut),
  _mdMap(map),
  _halos(map->getHalos()),
  _localStrides(map->getLocalStrides())
{
  initializeIndexing();
}

//! Copy constructor
Epetra_MDVector::
Epetra_MDVector(const Epetra_MDVector & source) :
  Epetra_Vector(source),
  _mdMap(source.getMDMap()),
  _halos(_mdMap->getHalos()),
  _localStrides(_mdMap->getLocalStrides())
{
  initializeIndexing();
}

//! Constructor from Epetra_MDMap and Teuchos::ArrayView arguments
Epetra_MDVector::
Epetra_MDVector(const Teuchos::RCP< const Epetra_MDMap > & map,
                const Teuchos::ArrayView< double > & A) :
  Epetra_Vector(Copy,
                *Teuchos::rcp_static_cast< const Epetra_BlockMap >(map),
                A.getRawPtr()),
  _mdMap(map),
  _halos(map->getHalos()),
  _localStrides(map->getLocalStrides())
{
  initializeIndexing();
}

//! Destructor
Epetra_MDVector::
~Epetra_MDVector()
{
}

//! Initialize the indexing data
void
Epetra_MDVector::
initializeIndexing()
{
  // Extract the raw pointer to the data buffer
  ExtractView(&_buffer);
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
