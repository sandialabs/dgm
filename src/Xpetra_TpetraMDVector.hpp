#ifndef XPETRA_TPETRAMDVECTOR_HPP
#define XPETRA_TPETRAMDVECTOR_HPP

/** \file   Xpetra_TpetraMDVector.hpp
    \brief  Xpetra wrapper for a Tpetra MDVector
    \author Bill Spotz
*/

// Xpetra includes
#include "Xpetra_TpetraConfigDefs.hpp"
#include "Xpetra_Utils.hpp"
#include "Xpetra_Exceptions.hpp"
#include "Xpetra_TpetraVector.hpp"

// Local includes
#include "Xpetra_TpetraMDMap.hpp"
#include "Tpetra_MDVector.hpp"
#include "Xpetra_MDVector.hpp"

namespace Xpetra
{

// Conversion functions
template< class Scalar,
          class LocalOrdinal,
          class GlobalOrdinal,
          class Node >
const Tpetra::MDVector< Scalar, LocalOrdinal, GlobalOrdinal, Node > &
toTpetra(const Xpetra::MDVector< Scalar,
                                 LocalOrdinal,
                                 GlobalOrdinal,
                                 Node > & vector);

template< class Scalar,
          class LocalOrdinal,
          class GlobalOrdinal,
          class Node >
const Teuchos::RCP< Tpetra::MDVector< Scalar,
                                      LocalOrdinal,
                                      GlobalOrdinal,
                                      Node > > &
toTpetra(const Teuchos::RCP< MDVector< Scalar,
                                       LocalOrdinal,
                                       GlobalOrdinal,
                                       Node > > & vector);

template< class Scalar,
          class LocalOrdinal,
          class GlobalOrdinal,
          class Node >
const Teuchos::RCP< MDVector< Scalar,
                              LocalOrdinal,
                              GlobalOrdinal,
                              Node > >
toXpetra(const Teuchos::RCP< Tpetra::MDVector< Scalar,
                                               LocalOrdinal,
                                               GlobalOrdinal,
                                               Node > > & vector);

/// Xpetra wrapper for a Tpetra MD vector
template< class Scalar,
          class LocalOrdinal,
          class GlobalOrdinal = LocalOrdinal,
          class Node = KokkosClassic::DefaultNode::DefaultNodeType >
class TpetraMDVector :
    public MDVector< Scalar, LocalOrdinal, GlobalOrdinal, Node >,
    public TpetraVector< Scalar, LocalOrdinal, GlobalOrdinal, Node >
{

public:

  //! Tpetra::MDVector constructor

  //! This constructor mirrors the \c Vector constructor that takes a
  //! \c Map argument, but here the \c Map is required to be a \c
  //! MDMap
  explicit
  TpetraMDVector(const Teuchos::RCP< const
                                     MDMap< LocalOrdinal,
                                            GlobalOrdinal,
                                            Node > > & map,
                 bool zeroOut = true);

  //! TpetraMDMap and ArrayView constructor

  //! Determine the structure and decomposition via the \c
  //! MDMap argument, and initialize the values with the \c
  //! Teuchos::ArrayView argument
  explicit
  TpetraMDVector(const Teuchos::RCP< const
                                     MDMap< LocalOrdinal,
                                            GlobalOrdinal,
                                            Node > > & map,
                 const Teuchos::ArrayView< Scalar > & A);

  TpetraMDVector(const MDVector< Scalar,
                                 LocalOrdinal,
                                 GlobalOrdinal,
                                 Node > & vec);

  //! Destructor
  virtual ~TpetraMDVector() { }

  ////////////////////////////////
  // Inherit base class methods //
  ////////////////////////////////

  using TpetraVector< Scalar, LocalOrdinal, GlobalOrdinal, Node >::dot;
  using TpetraVector< Scalar, LocalOrdinal, GlobalOrdinal, Node >::norm1;
  using TpetraVector< Scalar, LocalOrdinal, GlobalOrdinal, Node >::norm2;
  using TpetraVector< Scalar, LocalOrdinal, GlobalOrdinal, Node >::normInf;
  //using TpetraVector< Scalar, LocalOrdinal, GlobalOrdinal, Node >::normWeighted;
  using TpetraVector< Scalar, LocalOrdinal, GlobalOrdinal, Node >::meanValue;
  using TpetraVector< Scalar, LocalOrdinal, GlobalOrdinal, Node >::description;
  using TpetraVector< Scalar, LocalOrdinal, GlobalOrdinal, Node >::describe;

  //! Set operator, ArrayView index

  //! Note that local axis index (0,0,...) refers to the index of the
  //! first element of the interior, or non-halo region
  inline Scalar & operator[](const Teuchos::ArrayView< LocalOrdinal > index)
  { return vector_->operator[](index); }

  //! Set operator, single index
  inline Scalar & operator()(const LocalOrdinal index)
  { return vector_->operator()(index); }

  //! Set operator, two indexes

  //! Note that local axis index (0,0) refers to the index of the
  //! first element of the interior, or non-halo region
  inline Scalar & operator()(const LocalOrdinal i,
                             const LocalOrdinal j)
  { return vector_->operator()(i,j); }

  //! Set operator, three indexes

  //! Note that local axis index (0,0,0) refers to the index of the
  //! first element of the interior, or non-halo region
  inline Scalar & operator()(const LocalOrdinal i,
                             const LocalOrdinal j,
                             const LocalOrdinal k)
  { return vector_->operator()(i,j,k); }

  //! Get operator, ArrayView index

  //! Note that local axis index (0,0,...) refers to the index of the
  //! first element of the interior, or non-halo region
  inline const
  Scalar & operator[](const Teuchos::ArrayView< LocalOrdinal > index) const
  { return vector_->operator[](index); }

  //! Get operator, single index
  inline const Scalar & operator()(const int index) const
  { return vector_->operator()(index); }

  //! Get operator, two indexes

  //! Note that local axis index (0,0) refers to the index of the
  //! first element of the interior, or non-halo region
  inline const Scalar & operator()(const LocalOrdinal i,
                                   const LocalOrdinal j) const
  { return vector_->operator()(i,j); }

  //! Get operator, three indexes

  //! Note that local axis index (0,0,0) refers to the index of the
  //! first element of the interior, or non-halo region
  inline const Scalar & operator()(const LocalOrdinal i,
                                   const LocalOrdinal j,
                                   const LocalOrdinal k) const
  { return vector_->operator()(i,j,k); }

  //! Get the underlying MD map
  const inline
  Teuchos::RCP< const
  Xpetra::MDMap< LocalOrdinal,
                         GlobalOrdinal,
                         Node > > getMDMap() const
  {
    return mdMap_;
  }

  //! @name Xpetra specific
  TpetraMDVector(const Teuchos::RCP< Tpetra::MDVector< Scalar,
                                                       LocalOrdinal,
                                                       GlobalOrdinal,
                                                       Node > > &
                 vector);

  //! Get the library used by this object
  inline UnderlyingLib lib() const
  {
    return Xpetra::UseTpetra;
  }

  //! MDVector accessor method
  inline const Teuchos::RCP< Tpetra::MDVector< Scalar,
                                               LocalOrdinal,
                                               GlobalOrdinal,
                                               Node > > &
  getTpetra_MDVector() const
  {
    return vector_;
  }

private:

  // Private static methods for constructing and storing a reference
  // counted pointer to a Tpetra::MDVector.  This allows the
  // Xpetra::TpetraMDVector constructors to construct a vector
  // and provide it to the Xpetra::TpetraVector base class as the
  // first step in the constructor process.
  static Teuchos::RCP< Tpetra::MDVector< Scalar,
                                         LocalOrdinal,
                                         GlobalOrdinal,
                                         Node > >
  computeMDVector(const Teuchos::RCP< const
                                      MDMap< LocalOrdinal,
                                             GlobalOrdinal,
                                             Node > > & map,
                  bool zeroOut = true);

  static Teuchos::RCP< Tpetra::MDVector< Scalar,
                                         LocalOrdinal,
                                         GlobalOrdinal,
                                         Node > >
  computeMDVector(const Teuchos::RCP< const
                                      MDMap< LocalOrdinal,
                                             GlobalOrdinal,
                                             Node > > & map,
                  const Teuchos::ArrayView< Scalar > & A);

  // Static variable that allows the computeMDVector methods
  // to store a reference counted pointer to an
  // Tpetra::MDVector
  static Teuchos::RCP< Tpetra::MDVector< Scalar,
                                         LocalOrdinal,
                                         GlobalOrdinal,
                                         Node > > temp_vector_;

  // Reference counted pointer to the underlying
  // Tpetra::MDVector
  Teuchos::RCP< Tpetra::MDVector< Scalar,
                                  LocalOrdinal,
                                  GlobalOrdinal,
                                  Node > > vector_;

  // Reference counted pointer to the vector's underlying MD map, cast
  // as an Xpetra::MDMap
  Teuchos::RCP< const MDMap< LocalOrdinal,
                             GlobalOrdinal,
                             Node > > mdMap_;

};

/////////////////////
// Implementations //
/////////////////////
template < class Scalar,
           class LocalOrdinal,
           class GlobalOrdinal,
           class Node >
const Tpetra::MDVector< Scalar, LocalOrdinal, GlobalOrdinal, Node > &
toTpetra(const Xpetra::MDVector< Scalar,
                                 LocalOrdinal,
                                 GlobalOrdinal,
                                 Node > & vector)
{
  const TpetraMDVector< Scalar, LocalOrdinal, GlobalOrdinal, Node > &
    tpetraMDVector =
    dynamic_cast< const TpetraMDVector< Scalar,
                                        LocalOrdinal,
                                        GlobalOrdinal,
                                        Node > & >(vector);
  return *tpetraMDVector.getTpetra_MDVector();
}

template < class Scalar,
           class LocalOrdinal,
           class GlobalOrdinal,
           class Node >
const Teuchos::RCP< Tpetra::MDVector< Scalar,
                                      LocalOrdinal,
                                      GlobalOrdinal,
                                      Node > > &
toTpetra(const Teuchos::RCP< MDVector< Scalar,
                                       LocalOrdinal,
                                       GlobalOrdinal,
                                       Node > > & vector)
{
  typedef TpetraMDVector< Scalar,
                          LocalOrdinal,
                          GlobalOrdinal,
                          Node > TpetraMDVectorClass;
  XPETRA_RCP_DYNAMIC_CAST(TpetraMDVectorClass, vector,
                          tpetraMDVector, "toTpetra");
  return tpetraMDVector->getTpetra_MDVector();
}

template < class Scalar,
           class LocalOrdinal,
           class GlobalOrdinal,
           class Node >
const Teuchos::RCP< MDVector< Scalar,
                              LocalOrdinal,
                              GlobalOrdinal,
                              Node > >
toXpetra(const Teuchos::RCP< Tpetra::MDVector< Scalar,
                                               LocalOrdinal,
                                               GlobalOrdinal,
                                               Node > > & vector)
{
  return Teuchos::rcp(new TpetraMDVector< Scalar,
                                          LocalOrdinal,
                                          GlobalOrdinal,
                                          Node >(vector));
}

// Static variable initialization
template < class Scalar,
           class LocalOrdinal,
           class GlobalOrdinal,
           class Node >
Teuchos::RCP< Tpetra::MDVector< Scalar,
                                LocalOrdinal,
                                GlobalOrdinal,
                                Node > >
TpetraMDVector< Scalar, LocalOrdinal, GlobalOrdinal, Node >::
temp_vector_ = Teuchos::RCP< Tpetra::MDVector< Scalar,
                                               LocalOrdinal,
                                               GlobalOrdinal,
                                               Node > >();

template < class Scalar,
           class LocalOrdinal,
           class GlobalOrdinal,
           class Node >
TpetraMDVector< Scalar, LocalOrdinal, GlobalOrdinal, Node >::
TpetraMDVector(const Teuchos::RCP< const
                                   MDMap< LocalOrdinal,
                                          GlobalOrdinal,
                                          Node > > & map,
               bool zeroOut) :
  TpetraVector< Scalar, LocalOrdinal, GlobalOrdinal, Node >
  (Teuchos::rcp_static_cast< Tpetra::Vector< Scalar,
                                             LocalOrdinal,
                                             GlobalOrdinal,
                                             Node > >
   (computeMDVector(map, zeroOut))),
  vector_(temp_vector_),
  mdMap_(map)
{
  temp_vector_ = Teuchos::RCP< Tpetra::MDVector< Scalar,
                                                 LocalOrdinal,
                                                 GlobalOrdinal,
                                                 Node > >();
}

template < class Scalar,
           class LocalOrdinal,
           class GlobalOrdinal,
           class Node >
TpetraMDVector< Scalar, LocalOrdinal, GlobalOrdinal, Node >::
TpetraMDVector(const Teuchos::RCP< const
                                   MDMap< LocalOrdinal,
                                          GlobalOrdinal,
                                          Node > > & map,
               const Teuchos::ArrayView< Scalar > & A) :
  TpetraVector< Scalar, LocalOrdinal, GlobalOrdinal, Node >
  (Teuchos::rcp_static_cast< Tpetra::Vector< Scalar,
                                             LocalOrdinal,
                                             GlobalOrdinal,
                                             Node > >
   (computeMDVector(map, A))),
  vector_(temp_vector_),
  mdMap_(map)
{
  temp_vector_ = Teuchos::RCP< Tpetra::MDVector< Scalar,
                                                 LocalOrdinal,
                                                 GlobalOrdinal,
                                                 Node > >();
}

template < class Scalar,
           class LocalOrdinal,
           class GlobalOrdinal,
           class Node >
TpetraMDVector< Scalar, LocalOrdinal, GlobalOrdinal, Node >::
TpetraMDVector(const Teuchos::RCP< Tpetra::MDVector< Scalar,
                                                     LocalOrdinal,
                                                     GlobalOrdinal,
                                                     Node > > &
               vector) :
  TpetraVector< Scalar, LocalOrdinal, GlobalOrdinal, Node >
  (Teuchos::rcp_static_cast< Tpetra::Vector< Scalar,
                                             LocalOrdinal,
                                             GlobalOrdinal,
                                             Node > >(vector)),
  vector_(vector),
  mdMap_(Teuchos::rcp_static_cast< const MDMap< LocalOrdinal,
                                                GlobalOrdinal,
                                                Node > >
         (Teuchos::rcp(TpetraMDMap< LocalOrdinal,
                                    GlobalOrdinal,
                                    Node >
                       (vector->getMDMap()))))
{
}

template < class Scalar,
           class LocalOrdinal,
           class GlobalOrdinal,
           class Node >
Teuchos::RCP< Tpetra::MDVector< Scalar,
                                LocalOrdinal,
                                GlobalOrdinal,
                                Node > >
TpetraMDVector< Scalar, LocalOrdinal, GlobalOrdinal, Node >::
computeMDVector(const Teuchos::RCP< const MDMap< LocalOrdinal,
                                                 GlobalOrdinal,
                                                 Node > > & map,
                bool zeroOut)
{
  typedef TpetraMDMap< LocalOrdinal, GlobalOrdinal, Node >
    TpetraMDMapClass;
  XPETRA_RCP_DYNAMIC_CAST(const TpetraMDMapClass, map, tsm,
                          "TpetraMDVector::computeMDVector")
  temp_vector_ =
    Teuchos::rcp(new Tpetra::MDVector< Scalar,
                                       LocalOrdinal,
                                       GlobalOrdinal,
                                       Node >
                 (tsm->getTpetra_MDMap(), zeroOut));
  return temp_vector_;
}

template < class Scalar,
           class LocalOrdinal,
           class GlobalOrdinal,
           class Node >
Teuchos::RCP< Tpetra::MDVector< Scalar,
                                LocalOrdinal,
                                GlobalOrdinal,
                                Node > >
TpetraMDVector< Scalar, LocalOrdinal, GlobalOrdinal, Node >::
computeMDVector(const Teuchos::RCP< const MDMap< LocalOrdinal,
                                                 GlobalOrdinal,
                                                 Node > > & map,
                const Teuchos::ArrayView< Scalar > & A)
{
  typedef TpetraMDMap< LocalOrdinal, GlobalOrdinal, Node >
    TpetraMDMapClass;
  XPETRA_RCP_DYNAMIC_CAST(const TpetraMDMapClass, map, tsm,
                          "TpetraMDVector::computeMDVector")
  temp_vector_ =
    Teuchos::rcp(new Tpetra::MDVector< Scalar,
                                       LocalOrdinal,
                                       GlobalOrdinal,
                                       Node >
                 (tsm->getTpetra_MDMap(), A));
  return temp_vector_;
}

}  // Xpetra namespace

#endif
