#ifndef XPETRA_MDVECTOR_HPP
#define XPETRA_MDVECTOR_HPP

/** \file   Xpetra_MDVector.hpp
    \brief  Xpetra abstract base class MDVector declaration
    \author Bill Spotz
*/

// Xpetra includes
#include "Xpetra_MultiVector.hpp"
#include "Xpetra_Vector.hpp"

// Local includes
#include "Xpetra_MDMap.hpp"

namespace Xpetra
{

//! A class for using dense, distributed, n-dimensional vectors

//! The MDVector class inherits from \c Tpetra::Vector and
//! enforces structure by requiring a \c MDMap at
//! construction.

template< class Scalar,
          class LocalOrdinal,
          class GlobalOrdinal = LocalOrdinal,
          class Node = KokkosClassic::DefaultNode::DefaultNodeType >
class MDVector :
    public virtual Vector< Scalar, LocalOrdinal, GlobalOrdinal, Node >
{

public:

  //! Destructor
  virtual ~MDVector() { }

  ////////////////////////////////
  // Inherit base class methods //
  ////////////////////////////////

  using Vector< Scalar, LocalOrdinal, GlobalOrdinal, Node >::dot;
  using Vector< Scalar, LocalOrdinal, GlobalOrdinal, Node >::norm1;
  using Vector< Scalar, LocalOrdinal, GlobalOrdinal, Node >::norm2;
  using Vector< Scalar, LocalOrdinal, GlobalOrdinal, Node >::normInf;
  // using Vector< Scalar, LocalOrdinal, GlobalOrdinal, Node >::normWeighted;
  using Vector< Scalar, LocalOrdinal, GlobalOrdinal, Node >::meanValue;
  using Vector< Scalar, LocalOrdinal, GlobalOrdinal, Node >::description;
  using Vector< Scalar, LocalOrdinal, GlobalOrdinal, Node >::describe;

  //! Set operator, ArrayView index

  //! Note that local axis index (0,0,...) refers to the index of the
  //! first element of the interior, or non-halo region
  virtual Scalar &
  operator[](const Teuchos::ArrayView< LocalOrdinal > index) = 0;

  //! Set operator, single index
  virtual Scalar & operator()(const LocalOrdinal index) = 0;

  //! Set operator, two indexes

  //! Note that local axis index (0,0) refers to the index of the
  //! first element of the interior, or non-halo region
  virtual Scalar & operator()(const LocalOrdinal i, const LocalOrdinal j) = 0;

  //! Set operator, three indexes

  //! Note that local axis index (0,0,0) refers to the index of the
  //! first element of the interior, or non-halo region
  virtual Scalar & operator()(const LocalOrdinal i,
                              const LocalOrdinal j,
                              const LocalOrdinal k) = 0;

  //! Get operator, ArrayView index

  //! Note that local axis index (0,0,...) refers to the index of the
  //! first element of the interior, or non-halo region
  virtual const Scalar &
  operator[](const Teuchos::ArrayView< LocalOrdinal > index) const = 0;

  //! Get operator, single index
  virtual const Scalar & operator()(const LocalOrdinal index) const = 0;

  //! Get operator, two indexes

  //! Note that local axis index (0,0) refers to the index of the
  //! first element of the interior, or non-halo region
  virtual const Scalar & operator()(const LocalOrdinal i,
                                    const LocalOrdinal j) const = 0;

  //! Get operator, three indexes

  //! Note that local axis index (0,0,0) refers to the index of the
  //! first element of the interior, or non-halo region
  virtual const Scalar & operator()(const LocalOrdinal i,
                                    const LocalOrdinal j,
                                    const LocalOrdinal k) const = 0;

  //! Get the underlying MD map
  virtual const
  Teuchos::RCP< const Xpetra::MDMap< LocalOrdinal,
                                     GlobalOrdinal,
                                     Node > > getMDMap() const = 0;
};

}  // Namespace Xpetra

#endif
