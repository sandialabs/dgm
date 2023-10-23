#ifndef XPETRA_EPETRAMDVECTOR_HPP
#define XPETRA_EPETRAMDVECTOR_HPP

/** \file   Xpetra_EpetraMDVector.hpp
    \brief  Concrete Epetra implementation of class MDVector
    \author Bill Spotz
*/

// Xpetra includes
#include "Xpetra_EpetraConfigDefs.hpp"
#include "Xpetra_Utils.hpp"
#include "Xpetra_EpetraUtils.hpp"
#include "Xpetra_Exceptions.hpp"
#include "Xpetra_EpetraVector.hpp"

// Local includes
#include "Xpetra_EpetraMDMap.hpp"
#include "Epetra_MDVector.h"
#include "Xpetra_MDVector.hpp"

/// Xpetra wraps both Epetra and Tpetra
namespace Xpetra
{

// Conversion functions
const Epetra_MDVector &
toEpetra(const Xpetra::MDVector< double, int, int > & vector);

const Teuchos::RCP< Epetra_MDVector > &
toEpetra(const Teuchos::RCP< MDVector< double, int, int > > & vector);

const Teuchos::RCP< MDVector< double, int, int > >
toXpetra(const Teuchos::RCP< Epetra_MDVector > & vector);

/// Xpetra wrapper of an Epetra MD vector
class EpetraMDVector :
    public MDVector< double, int, int >,
    public EpetraVectorT<int, KokkosClassic::DefaultNode::DefaultNodeType>
{

    typedef double Scalar;
    typedef int LocalOrdinal;
    typedef int GlobalOrdinal;
    typedef KokkosClassic::DefaultNode::DefaultNodeType Node;
    typedef EpetraVectorT<GlobalOrdinal, KokkosClassic::DefaultNode::DefaultNodeType> Base;


public:

  //! EpetraMDVector constructor

  //! This constructor mirrors the \c Vector constructor that takes a
  //! \c Map argument, but here the \c Map is required to be a \c
  //! MDMap
  explicit EpetraMDVector(const
                          Teuchos::RCP< const
                                        MDMap< LocalOrdinal,
                                               GlobalOrdinal,
                                               Node > > & map,
                          bool zeroOut = true);

  //! MDMap and ArrayView constructor

  //! Determine the structure and decomposition via the \c MDMap
  //! argument, and initialize the values with the \c
  //! Teuchos::ArrayView argument
  explicit EpetraMDVector(const
                          Teuchos::RCP< const
                                        MDMap< LocalOrdinal,
                                               GlobalOrdinal,
                                               Node > > & map,
                          const Teuchos::ArrayView< double > & A);

  EpetraMDVector(const MDVector< Scalar,
                                 LocalOrdinal,
                                 GlobalOrdinal,
                                 Node > & vec);

  EpetraMDVector(const Teuchos::RCP< Epetra_MDVector > & vec);

  //! Destructor
  virtual ~EpetraMDVector() { }

  ////////////////////////////////
  // Inherit base class methods //
  ////////////////////////////////

  using Base::dot;
  using Base::norm1;
  using Base::norm2;
  using Base::normInf;
  //using EpetraVector::normWeighted;
  using Base::meanValue;
  using Base::description;
  using Base::describe;

  //! Set operator, ArrayView index

  //! Note that local axis index (0,0,...) refers to the index of the
  //! first element of the interior, or non-halo region
  inline double & operator[](const Teuchos::ArrayView< int > index)
  { return vector_->operator[](index); }

  //! Set operator, single index
  inline double & operator()(const int index)
  { return vector_->operator()(index); }

  //! Set operator, two indexes

  //! Note that local axis index (0,0) refers to the index of the
  //! first element of the interior, or non-halo region
  inline double & operator()(const int i, const int j)
  { return vector_->operator()(i,j); }

  //! Set operator, three indexes

  //! Note that local axis index (0,0,0) refers to the index of the
  //! first element of the interior, or non-halo region
  inline double & operator()(const int i,
                             const int j,
                             const int k)
  { return vector_->operator()(i,j,k); }

  //! Get operator, ArrayView index

  //! Note that local axis index (0,0,...) refers to the index of the
  //! first element of the interior, or non-halo region
  inline const double & operator[](const Teuchos::ArrayView< int > index)
    const { return vector_->operator[](index); }

  //! Get operator, single index
  inline const double & operator()(const int index) const
  { return vector_->operator()(index); }

  //! Get operator, two indexes

  //! Note that local axis index (0,0) refers to the index of the
  //! first element of the interior, or non-halo region
  inline const double & operator()(const int i,
                                   const int j) const
  { return vector_->operator()(i,j); }

  //! Get operator, three indexes

  //! Note that local axis index (0,0,0) refers to the index of the
  //! first element of the interior, or non-halo region
  inline const double & operator()(const int i,
                                   const int j,
                                   const int k) const
  { return vector_->operator()(i,j,k); }

  //! Get the underlying MD map
  inline const
  Teuchos::RCP< const Xpetra::MDMap< int, int > >
  getMDMap() const
  { return mdMap_; }

  //! @name Xpetra specific

  //! Get the library used by this object
  inline UnderlyingLib lib() const { return Xpetra::UseEpetra; }

  //! MDVector accessor method
  inline const Teuchos::RCP< Epetra_MDVector > &
  getEpetra_MDVector() const { return vector_; }

private:

  // Private static methods for constructing and storing a reference
  // counted pointer to an Epetra_MDVector.  This allows the
  // Xpetra::EpetraMDVector constructors to construct a vector and
  // provide it to the Xpetra::EpetraVector base class as the first
  // step in the constructor process.
  static Teuchos::RCP< Epetra_MDVector >
  computeMDVector(const Teuchos::RCP< const
                                      MDMap< LocalOrdinal,
                                             GlobalOrdinal,
                                             Node > > & map,
                  bool zeroOut = true);

  static Teuchos::RCP< Epetra_MDVector >
  computeMDVector(const Teuchos::RCP< const
                                      MDMap< LocalOrdinal,
                                             GlobalOrdinal,
                                             Node > > & map,
                  const Teuchos::ArrayView< double > & A);

  // Static variable that allows the computeMDVector methods to store
  // a reference counted pointer to an Epetra_MDVector
  static Teuchos::RCP< Epetra_MDVector > temp_vector_;

  // Reference counted pointer to the underlying Epetra_MDVector
  Teuchos::RCP< Epetra_MDVector > vector_;

  // Reference counted pointer to the underlying vector's
  // Epetra_MDMap, cast as an Xpetra::MDMap.
  Teuchos::RCP< const MDMap< LocalOrdinal,
                             GlobalOrdinal,
                             Node > > mdMap_;

};

}  // Namespace Xpetra

#endif
