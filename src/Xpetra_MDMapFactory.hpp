#ifndef XPETRA_MDMAPFACTORY_HPP
#define XPETRA_MDMAPFACTORY_HPP

/** \file   Xpetra_MDMapFactory.hpp
    \brief  Factory for Xpetra multidimensional maps
    \author Bill Spotz
*/

// Xpetra includes
#include "Xpetra_ConfigDefs.hpp"
#include "Xpetra_Exceptions.hpp"
#include "Xpetra_MDMap.hpp"
#ifdef HAVE_XPETRA_TPETRA
#include "Xpetra_TpetraMDMap.hpp"
#endif
#ifdef HAVE_XPETRA_EPETRA
#include "Xpetra_EpetraMDMap.hpp"
#endif

// This factory creates an Xpetra::MDMap. User has to specify the
// exact class of object that he want to create (ie: an
// Xpetra::TpetraMDMap or an Xpetra::EpetraMDMap).

namespace Xpetra
{

/// Factory for building multidimensional maps
template < class LocalOrdinal,
           class GlobalOrdinal = LocalOrdinal,
           class Node = KokkosClassic::DefaultNode::DefaultNodeType >
class MDMapFactory
{

private:
  //! Private constructor. This is a static class.
  MDMapFactory() {}

public:

  //! N-dimensional factory
  static Teuchos::RCP< MDMap< LocalOrdinal, GlobalOrdinal, Node > >
  Build(UnderlyingLib lib,
        const Teuchos::RCP< const Teuchos::Comm< int > > & comm,
        const Teuchos::ArrayView< GlobalOrdinal > & globalShape,
        const Teuchos::ArrayView< int > & axisNumProc =
            Teuchos::ArrayView< int >(),
        const Teuchos::ArrayView< int > & halos =
            Teuchos::ArrayView< int >(),
        const Teuchos::ArrayView< int > & ghostPoints =
            Teuchos::ArrayView< int >(),
        const Teuchos::ArrayView< int > & periodic =
            Teuchos::ArrayView< int >(),
        const Teuchos::RCP< Node > & node =
            Teuchos::RCP< Node >())
  {

#ifdef HAVE_XPETRA_TPETRA
    if (lib == UseTpetra)
      return rcp( new TpetraMDMap< LocalOrdinal,
                                   GlobalOrdinal,
                                   Node >(comm,
                                          globalShape,
                                          axisNumProc,
                                          halos,
                                          ghostPoints,
                                          periodic,
                                          node) );
#endif

    XPETRA_FACTORY_ERROR_IF_EPETRA(lib);
    XPETRA_FACTORY_END;
  }

  //! 2-dimensional factory
  static Teuchos::RCP< MDMap< LocalOrdinal, GlobalOrdinal, Node> >
  Build(UnderlyingLib lib,
        const Teuchos::RCP< const Teuchos::Comm< int > > & comm,
        const GlobalOrdinal globalNum_i,
        const GlobalOrdinal globalNum_j,
        const int           numProc_i     = -1,
        const int           numProc_j     = -1,
        const int           halo_i        =  0,
        const int           halo_j        =  0,
        const int           ghostPoints_i =  0,
        const int           ghostPoints_j =  0,
        const int           periodic_i    = false,
        const int           periodic_j    = false,
        const Teuchos::RCP< Node > & node =
            Teuchos::RCP< Node >())
  {

#ifdef HAVE_XPETRA_TPETRA
      if (lib == UseTpetra)
        return rcp( new TpetraMDMap< LocalOrdinal,
                                     GlobalOrdinal,
                                     Node> (comm,
                                            globalNum_i,
                                            globalNum_j,
                                            numProc_i,
                                            numProc_j,
                                            halo_i,
                                            halo_j,
                                            ghostPoints_i,
                                            ghostPoints_j,
                                            periodic_i,
                                            periodic_j,
                                            node) );
#endif

    XPETRA_FACTORY_ERROR_IF_EPETRA(lib);
    XPETRA_FACTORY_END;
  }

};   // MDMapFactory class

/// MDMapFactory< int, int > specialization
template <>
class MDMapFactory<int, int>
{

  typedef int LocalOrdinal;
  typedef int GlobalOrdinal;
  typedef KokkosClassic::DefaultNode::DefaultNodeType Node;

private:
  //! Private constructor. This is a static class.
  MDMapFactory() {}

public:

  // N-dimensional factory
  static RCP< MDMap< LocalOrdinal, GlobalOrdinal, Node> >
  Build(UnderlyingLib lib,
        const Teuchos::RCP< const Teuchos::Comm< int > > & comm,
        const Teuchos::ArrayView< GlobalOrdinal > & globalShape,
        const Teuchos::ArrayView< int > & axisNumProc =
            Teuchos::ArrayView< int >(),
        const Teuchos::ArrayView< int > & halos =
            Teuchos::ArrayView< int >(),
        const Teuchos::ArrayView< int > & ghostPoints =
            Teuchos::ArrayView< int >(),
        const Teuchos::ArrayView< int > & periodic =
            Teuchos::ArrayView< int >(),
        const Teuchos::RCP< Node >      & node =
            Teuchos::RCP< Node >())
  {

#ifdef HAVE_XPETRA_TPETRA
    if (lib == UseTpetra)
      return rcp( new TpetraMDMap< LocalOrdinal,
                                   GlobalOrdinal,
                                   Node> (comm,
                                          globalShape,
                                          axisNumProc,
                                          halos,
                                          ghostPoints,
                                          periodic,
                                          node) );
#endif

#ifdef HAVE_XPETRA_EPETRA
    if (lib == UseEpetra)
      return rcp( new EpetraMDMap(comm,
                                  globalShape,
                                  axisNumProc,
                                  halos,
                                  ghostPoints,
                                  periodic) );
#endif

    XPETRA_FACTORY_END;

  }

  // 2-dimensional factory
  static RCP< MDMap< LocalOrdinal, GlobalOrdinal, Node> >
  Build(UnderlyingLib lib,
        const Teuchos::RCP<const Teuchos::Comm< int > > & comm,
        const GlobalOrdinal globalNum_i,
        const GlobalOrdinal globalNum_j,
        const int           numProc_i     = -1,
        const int           numProc_j     = -1,
        const int           halo_i        =  0,
        const int           halo_j        =  0,
        const int           ghostPoints_i =  0,
        const int           ghostPoints_j =  0,
        const int           periodic_i    = false,
        const int           periodic_j    = false,
        const Teuchos::RCP<KokkosClassic::DefaultNode::DefaultNodeType> & node =
            Teuchos::RCP< Node >())
  {

#ifdef HAVE_XPETRA_TPETRA
    if (lib == UseTpetra)
      return rcp( new TpetraMDMap< LocalOrdinal,
                                   GlobalOrdinal,
                                   Node> (comm,
                                          globalNum_i,
                                          globalNum_j,
                                          numProc_i,
                                          numProc_j,
                                          halo_i,
                                          halo_j,
                                          ghostPoints_i,
                                          ghostPoints_j,
                                          periodic_i,
                                          periodic_j,
                                          node) );
#endif

#ifdef HAVE_XPETRA_EPETRA
    if (lib == UseEpetra)
      return rcp( new EpetraMDMap(comm,
                                  globalNum_i,
                                  globalNum_j,
                                  numProc_i,
                                  numProc_j,
                                  halo_i,
                                  halo_j,
                                  ghostPoints_i,
                                  ghostPoints_j,
                                  periodic_i,
                                  periodic_j) );
#endif

    XPETRA_FACTORY_END;

  }

};   // MDMapFactory< int, int > specialization

}    // Xpetra namespace

#endif
