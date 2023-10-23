
/** \file   Xpetra_EpetraMDMap.cpp
    \brief  Xpetra wrapper to an Epetra multidimensional map
    \author Bill Spotz
*/

#include "Xpetra_EpetraMDMap.hpp"
#include "Xpetra_EpetraUtils.hpp"

namespace Xpetra
{

// Conversion functions
const Epetra_MDMap &
toEpetra(const MDMap<int, int> & map)
{
  const EpetraMDMap & epetraMDMap =
    dynamic_cast<const EpetraMDMap & >(map);
  return *epetraMDMap.getEpetra_MDMap();
}

const RCP< const Epetra_MDMap > &
toEpetra(const RCP< const MDMap< int, int > > & map)
{
  typedef EpetraMDMap EpetraMDMapClass;
  XPETRA_RCP_DYNAMIC_CAST(const EpetraMDMapClass, map,
                          epetraMDMap, "toEpetra");
  return epetraMDMap->getEpetra_MDMap();
}

// Static variable initialization

Teuchos::RCP< const Epetra_MDMap >
EpetraMDMap::temp_map_ =
  Teuchos::RCP< const Epetra_MDMap >();

// N-dimensional constructor
EpetraMDMap::
EpetraMDMap(const Teuchos::RCP< const Teuchos::Comm< int > > & comm,
            const Teuchos::ArrayView< int > & globalShape,
            const Teuchos::ArrayView< int > & axisNumProc,
            const Teuchos::ArrayView< int > & halos,
            const Teuchos::ArrayView< int > & ghostPoints,
            const Teuchos::ArrayView< int > & periodic) :
  Base(Teuchos::rcp_static_cast< const Epetra_BlockMap >
            (computeMDMap(comm,
                          globalShape,
                          axisNumProc,
                          halos,
                          ghostPoints,
                          periodic))),
  map_(temp_map_)
{
  temp_map_  = RCP< const Epetra_MDMap >();
  convertAxisMaps();
}

// 2 dimensional constructor
EpetraMDMap::
EpetraMDMap(const Teuchos::RCP< const Teuchos::Comm< int > > & comm,
            const int globalNum_i,
            const int globalNum_j,
            const int numProc_i,
            const int numProc_j,
            const int halo_i,
            const int halo_j,
            const int ghostPoints_i,
            const int ghostPoints_j,
            const int periodic_i,
            const int periodic_j) :
  Base(Teuchos::rcp_static_cast< const Epetra_BlockMap >
            (computeMDMap(comm,
                          tuple(globalNum_i,globalNum_j),
                          tuple(numProc_i,numProc_j),
                          tuple(halo_i,halo_j),
                          tuple(ghostPoints_i,ghostPoints_j),
                          tuple(periodic_i,periodic_j)))),
  map_(temp_map_)
{
  temp_map_  = RCP< const Epetra_MDMap >();
  convertAxisMaps();
}

// RCP constructor
EpetraMDMap::
EpetraMDMap(const Teuchos::RCP<const Epetra_MDMap > & map) :
  Base((const Base &)(*map)),
  map_(map)
{
  convertAxisMaps();
}

RCP< const Epetra_MDMap > EpetraMDMap::
computeMDMap(const Teuchos::RCP< const Teuchos::Comm< int > > & comm,
             const Teuchos::ArrayView< int > & globalShape,
             const Teuchos::ArrayView< int > & axisNumProc,
             const Teuchos::ArrayView< int > & halos,
             const Teuchos::ArrayView< int > & ghostPoints,
             const Teuchos::ArrayView< int > & periodic)
{
  temp_map_  = Teuchos::rcp(new Epetra_MDMap(*toEpetra(comm),
                                             globalShape,
                                             axisNumProc,
                                             halos,
                                             ghostPoints,
                                             periodic));
  return temp_map_;
}

void EpetraMDMap::
convertAxisMaps()
{
  typedef global_ordinal_type GO;
  typedef node_type NT;

  axisMaps_.resize(map_->getNumDims());
  for (int i=0; i < axisMaps_.size(); ++i) {
    const Epetra_Map& map = * (map_->getAxisMap (i));
    // This overload of toXpetra takes two arguments,
    // _not_ the local ordinal type, because Epetra has
    // a 64-bit option (in which GO=long long makes sense)
    // as well as its default 32-bit option (GO=int).
    // The local ordinal type in Epetra is always int.
    axisMaps_[i] = toXpetra<GO, NT> (static_cast<const Epetra_BlockMap& > (map));
  }
}

}  // Namespace Xpetra
