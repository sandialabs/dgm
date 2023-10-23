
/** \file   Xpetra_EpetraMDVector.cpp
    \brief  Xpetra wrapper for an Epetra multidimensional vector
    \author Bill Spotz
*/

#include "Xpetra_EpetraMDVector.hpp"

namespace Xpetra
{

////////////////////////////////////////////////////////////////////////

const Epetra_MDVector &
toEpetra(const Xpetra::MDVector< double, int, int > & vector)
{
  const EpetraMDVector & epetraMDVector =
    dynamic_cast< const EpetraMDVector & >(vector);
  return *epetraMDVector.getEpetra_MDVector();
}

////////////////////////////////////////////////////////////////////////

const Teuchos::RCP< Epetra_MDVector > &
toEpetra(const Teuchos::RCP< MDVector< double, int, int > > & vector)
{
  typedef EpetraMDVector EpetraMDVectorClass;
  XPETRA_RCP_DYNAMIC_CAST(EpetraMDVectorClass, vector,
                          epetraMDVector, "toEpetra");
  return epetraMDVector->getEpetra_MDVector();
}

////////////////////////////////////////////////////////////////////////

const Teuchos::RCP< MDVector< double, int, int > >
toXpetra(const Teuchos::RCP< Epetra_MDVector > & vector)
{
  return Teuchos::rcp(new EpetraMDVector(vector));
}

// Static variable initialization
Teuchos::RCP< Epetra_MDVector >
EpetraMDVector::temp_vector_ =
  Teuchos::RCP< Epetra_MDVector >();

EpetraMDVector::
EpetraMDVector(const Teuchos::RCP< const MDMap< LocalOrdinal,
                                                GlobalOrdinal,
                                                Node > > & map,
               bool zeroOut) :
  Base(Teuchos::rcp_static_cast< Epetra_Vector >
               (computeMDVector(map, zeroOut))),
  vector_(temp_vector_),
  mdMap_(map)
{
  temp_vector_ = Teuchos::RCP< Epetra_MDVector >();
}

////////////////////////////////////////////////////////////////////////

EpetraMDVector::
EpetraMDVector(const Teuchos::RCP< const MDMap< LocalOrdinal,
                                                GlobalOrdinal,
                                                Node > > & map,
               const Teuchos::ArrayView< double > & A) :
  Base(Teuchos::rcp_static_cast< Epetra_Vector >
               (computeMDVector(map, A))),
  vector_(temp_vector_),
  mdMap_(map)
{
  temp_vector_ = Teuchos::RCP< Epetra_MDVector >();
}

////////////////////////////////////////////////////////////////////////

EpetraMDVector::
EpetraMDVector(const Teuchos::RCP< Epetra_MDVector > & vector) :
  Base(Teuchos::rcp_static_cast< Epetra_Vector >(vector)),
  vector_(vector),
  mdMap_(Teuchos::rcp_static_cast< const MDMap< LocalOrdinal,
                                                        GlobalOrdinal,
                                                        Node > >
                 (Teuchos::rcp(new
                               EpetraMDMap(vector->getMDMap()))
                  ))
{
}


////////////////////////////////////////////////////////////////////////

Teuchos::RCP< Epetra_MDVector >
EpetraMDVector::
computeMDVector(const Teuchos::RCP< const
                                    MDMap< LocalOrdinal,
                                           GlobalOrdinal,
                                           Node > > & map,
                bool zeroOut)
{
  // Teuchos::RCP< const EpetraMDMap > esm =
  //   Teuchos::rcp_dynamic_cast< const EpetraMDMap >(map);
  typedef EpetraMDMap EpetraMDMapClass;
  XPETRA_RCP_DYNAMIC_CAST(const EpetraMDMapClass, map, esm,
                          "EpetraMDVector::computeMDVector")
  temp_vector_ =
    Teuchos::rcp(new Epetra_MDVector(esm->getEpetra_MDMap(),
                                     zeroOut));
  return temp_vector_;
}

////////////////////////////////////////////////////////////////////////

Teuchos::RCP< Epetra_MDVector > EpetraMDVector::
computeMDVector(const Teuchos::RCP< const MDMap< LocalOrdinal,
                                                 GlobalOrdinal,
                                                 Node > > & map,
                        const Teuchos::ArrayView< double > & A)
{
  // Teuchos::RCP< const EpetraMDMap > esm =
  //   Teuchos::rcp_dynamic_cast< const EpetraMDMap >(map);
  typedef EpetraMDMap EpetraMDMapClass;
  XPETRA_RCP_DYNAMIC_CAST(const EpetraMDMapClass, map, esm,
                          "EpetraMDVector::computeMDVector")
  temp_vector_ =
    Teuchos::rcp(new Epetra_MDVector(esm->getEpetra_MDMap(),
                                     A));
  return temp_vector_;
}

}  // Xpetra namespace
