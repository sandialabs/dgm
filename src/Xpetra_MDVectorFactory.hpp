#ifndef XPETRA_MDVECTORFACTORY_HPP
#define XPETRA_MDVECTORFACTORY_HPP

/** \file   Xpetra_MDVectorFactory.hpp
    \brief  Xpetra MDVector factory
    \author Bill Spotz
*/

// Xpetra includes
#include "Xpetra_ConfigDefs.hpp"
#include "Xpetra_Exceptions.hpp"
#include "Xpetra_MDVector.hpp"
#ifdef HAVE_XPETRA_TPETRA
#include "Xpetra_TpetraMDVector.hpp"
#endif
#ifdef HAVE_XPETRA_EPETRA
#include "Xpetra_EpetraMDVector.hpp"
#endif

namespace Xpetra
{

/// This factory creates an Xpetra::MDVector.
/** User has to specify the exact class of object that he wants to create
    (ie: Xpetra::TpetraMDVector or Xpetra::EpetraMDVector).
*/
template < class Scalar,
           class LocalOrdinal,
           class GlobalOrdinal = LocalOrdinal,
           class Node = KokkosClassic::DefaultNode::DefaultNodeType >
class MDVectorFactory
{

private:
  //! Private constructor. This is a static class.
  MDVectorFactory() {}

public:

  //! MDMap and zeroOut flag constructor
  static Teuchos::RCP< MDVector< Scalar,
                                 LocalOrdinal,
                                 GlobalOrdinal,
                                 Node > >
  Build(const Teuchos::RCP< const MDMap< LocalOrdinal,
                                         GlobalOrdinal,
                                         Node > > & map,
        bool zeroOut = true)
  {

#ifdef HAVE_XPETRA_TPETRA
    if (map->lib() == UseTpetra)
      return rcp( new TpetraMDVector< Scalar,
                                      LocalOrdinal,
                                      GlobalOrdinal,
                                      Node >(map, zeroOut) );
#endif

    XPETRA_FACTORY_ERROR_IF_EPETRA(map->lib());
    XPETRA_FACTORY_END;
  }

  //! MDMap and ArrayView constructor
  static Teuchos::RCP< MDVector< Scalar,
                                 LocalOrdinal,
                                 GlobalOrdinal,
                                 Node> >
  Build(const Teuchos::RCP< const MDMap< LocalOrdinal,
                                         GlobalOrdinal,
                                         Node > > & map,
        const Teuchos::ArrayView< Scalar > & A)
  {

#ifdef HAVE_XPETRA_TPETRA
    if (map->lib() == UseTpetra)
        return rcp( new TpetraMDVector< Scalar,
                                        LocalOrdinal,
                                        GlobalOrdinal,
                                        Node> (map, A) );
#endif

    XPETRA_FACTORY_ERROR_IF_EPETRA(map->lib());
    XPETRA_FACTORY_END;
  }

};   // MDVectorFactory class

/// MDVectorFactory< double, int > specialization
template <>
class MDVectorFactory< double, int >
{

  typedef double Scalar;
  typedef int LocalOrdinal;
  typedef int GlobalOrdinal;
  typedef KokkosClassic::DefaultNode::DefaultNodeType Node;

private:
  //! Private constructor. This is a static class.
  MDVectorFactory() {}

public:

  // MDMap and zeroOut flag constructor
  static RCP< MDVector< Scalar, LocalOrdinal, GlobalOrdinal, Node> >
  Build(const Teuchos::RCP< const MDMap< LocalOrdinal,
                                         GlobalOrdinal,
                                         Node > > & map,
        bool zeroOut = true)
  {

#ifdef HAVE_XPETRA_TPETRA
    if (map->lib() == UseTpetra)
      return rcp( new TpetraMDVector< Scalar,
                                      LocalOrdinal,
                                      GlobalOrdinal,
                                      Node > (map, zeroOut) );
#endif

#ifdef HAVE_XPETRA_EPETRA
    if (map->lib() == UseEpetra)
      return rcp( new EpetraMDVector(map, zeroOut) );
#endif

    XPETRA_FACTORY_END;

  }

  // MDMap and ArrayView constructor
  static RCP< MDVector< Scalar, LocalOrdinal, GlobalOrdinal, Node> >
  Build(const Teuchos::RCP<const MDMap< LocalOrdinal,
                                        GlobalOrdinal,
                                        Node > > & map,
        const Teuchos::ArrayView< Scalar > & A)
  {

#ifdef HAVE_XPETRA_TPETRA
    if (map->lib() == UseTpetra)
      return rcp( new TpetraMDVector< Scalar,
                                      LocalOrdinal,
                                      GlobalOrdinal,
                                      Node> (map, A) );
#endif

#ifdef HAVE_XPETRA_EPETRA
    if (map->lib() == UseEpetra)
      return rcp( new EpetraMDVector(map, A) );
#endif

    XPETRA_FACTORY_END;

  }

};   // MDVectorFactory< int, int > specialization

}    // Xpetra namespace

#endif
