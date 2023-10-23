//! \file   FDM_Field.cpp
//! \brief  Finite Difference Field implementation
//! \author Bill Spotz

// Teuchos includes
#ifdef DGM_PARALLEL
#include "Teuchos_DefaultMpiComm.hpp"
#endif
#include "Teuchos_RCP.hpp"

// Local includes
#ifdef DGM_PARALLEL
#include "FDM_mpiType.hpp"
#endif
#include "FDM_Field.hpp"

namespace FDM
{

////////////////////////////////////////////////////////////////////////

Field::Field(const string &               symbol,
             const string &               name,
             const MeshPtr                mesh,
             const ArrayView< const int > stagger) :
  _name(name),
  _mesh(mesh),
  _mdMap(),
  _mdVector(),
  _mdArrayView(),
  _stagger(constructStagger(mesh->numDims(), stagger))
{
  setObjectLabel(symbol);
  setCartesianMeshPtr();
  _mdMap       = constructMdMapFromStagger(mesh, _stagger());
  _mdVector    = Teuchos::rcp(new Domi::MDVector< Scalar >(_mdMap));
  _mdArrayView = _mdVector->getDataNonConst();
}

////////////////////////////////////////////////////////////////////////

Field::Field(const string &               symbol,
             const string &               name,
             const MeshPtr                mesh,
             const MDVectorPtr            data,
             const ArrayView< const int > stagger) :
  _name(name),
  _mesh(mesh),
  _mdMap(data->getMDMap()),
  _mdVector(data),
  _mdArrayView(data->getDataNonConst()),
  _stagger(constructStagger(mesh->numDims(), stagger))
{
  setObjectLabel(symbol);
  setCartesianMeshPtr();
  MDMapPtr tempMap = constructMdMapFromStagger(mesh, _stagger());
  TEUCHOS_TEST_FOR_EXCEPTION(
    !_mdMap->isSameAs(*tempMap),
    Domi::InvalidArgument,
    "Data MDMap is not the same as the mesh MDMap (adjusted for stagger)");
}

////////////////////////////////////////////////////////////////////////

Field::Field(const string & symbol,
             const string & name,
             const Field  & parent,
             int            axis,
             Domi::dim_type index) :
  _name(name),
  _stagger(parent._stagger())
{
  setObjectLabel(symbol);
  if (parent._cMesh.is_null())
  {
    _mesh = Teuchos::rcp(new Mesh(*parent._mesh,
                                  axis,
                                  index));
  }
  else
  {
    _mesh = Teuchos::rcp(new CartesianMesh(*parent._cMesh,
                                           axis,
                                           index));
    setCartesianMeshPtr();
  }
  _mdMap = _mesh->getMDMap();
  _mdVector =
    Teuchos::rcp(new Domi::MDVector< FDM::Scalar >(*parent.getMDVector(),
                                                   axis,
                                                   index));
  _mdArrayView = _mdVector->getDataNonConst();
}

////////////////////////////////////////////////////////////////////////

Field::Field(const string &      symbol,
             const string &      name,
             const Field &       parent,
             int                 axis,
             const Domi::Slice & slice,
             int                 bndryPad) :
  _name(name),
  _stagger(parent._stagger())
{
  setObjectLabel(symbol);
  if (parent.isOnProcessor())
  {
    // Determine the Mesh Slice.  If axis is not staggered, it is the
    // same as the input Slice. If the axis is staggered, then the
    // Mesh Slice will be one larger than the input Slice.
    Domi::Slice meshSlice(slice.bounds(parent.getGlobalDim(axis)));
    if (_stagger[axis])
    {
      meshSlice = Domi::Slice(meshSlice.start(), meshSlice.stop()+1);
    }
    // Construct the sub-Mesh. If the parent Mesh is a CartesianMesh,
    // then use that constructor, else use the Mesh constructor.
    if (parent._cMesh.is_null())
    {
      _mesh = Teuchos::rcp(new Mesh(*parent._mesh,
                                    axis,
                                    meshSlice,
                                    bndryPad));
    }
    else
    {
      _mesh = Teuchos::rcp(new CartesianMesh(*parent._cMesh,
                                             axis,
                                             meshSlice,
                                             bndryPad));
      setCartesianMeshPtr();
    }
    // Determine the sub-MDMap. If the axis is not staggered, it is
    // the same as the Mesh MDMap. If the axis is staggered, construct
    // the sub-MDMap from the input Slice.
    _mdMap = _mesh->getMDMap();
    if (_stagger[axis])
    {
      _mdMap = Teuchos::rcp(new Domi::MDMap(*_mdMap,
                                              axis,
                                              slice,
                                              bndryPad));
    }
    // Construct the sub-MDVector from the input Slice
    _mdVector =
      Teuchos::rcp(new Domi::MDVector< FDM::Scalar >(*parent.getMDVector(),
                                                     axis,
                                                     slice,
                                                     bndryPad));
    // Obtain the MDArrayView from the MDVector
    _mdArrayView = _mdVector->getDataNonConst();
  }
}

////////////////////////////////////////////////////////////////////////

Field::Field(const string &                            symbol,
             const string &                            name,
             const Field &                             parent,
             const Teuchos::ArrayView< Domi::Slice > & slices,
             const Teuchos::ArrayView< int >         & bndryPads) :
  _name(name),
  _mesh(Teuchos::rcp(new Mesh(*parent._mesh,
                              slices,
                              bndryPads))),
  _mdMap(_mesh->getMDMap()),
  _mdVector(Teuchos::rcp(new Domi::MDVector< FDM::Scalar >(*parent.getMDVector(),
                                                           slices,
                                                           bndryPads))),
  _mdArrayView(_mdVector->getDataNonConst()),
  _stagger(parent._stagger())
{
  setObjectLabel(symbol);
  setCartesianMeshPtr();
}

////////////////////////////////////////////////////////////////////////

Field::~Field()
{
}

////////////////////////////////////////////////////////////////////////

string
Field::description() const
{
  std::stringstream ss;
  ss << "FDM::Field{" << getObjectLabel() << "}(" << _name << ", mesh = "
     << _mesh->description() << ")";
  return ss.str();
}

////////////////////////////////////////////////////////////////////////

Ordinal
Field::nearestIndex(int    axis,
                    Scalar coord,
                    bool   includeCommPad) const
{
  // Throw an exception if the Field mesh is not a cartesian mesh
  if (_cMesh.is_null())
    throw std::domain_error("Field::nearestIndex() method requires a "
                            "CartesianMesh");
  // Determine the index such that coord is bracketed between index
  // and index+1.  If coord is not on this processor, this method will
  // throw an out_of_range error.
  Ordinal index = _cMesh->nearestCoordinateIndex(axis,
                                                 coord,
                                                 includeCommPad);
  // If the Field is staggered along this axis, determine the
  // bracketing coordinates and correct the index if needed
  if (getStagger(axis))
  {
    Domi::MDArrayView< const Scalar > coords = _cMesh->getCoordinates(axis);
    Scalar lo = coords(index  );
    Scalar hi = coords(index+1);
    if (coord < (lo + hi)/2.0) index -= 1;
  }
  return index;
}

////////////////////////////////////////////////////////////////////////

Scalar
Field::atCoordinate(Scalar c0) const
{
  // Check the dimensions
  int nd = _mdMap->numDims();
  if (nd != 1)
  {
    stringstream msg;
    msg << "atCoordinate() called on " << nd << "D Field with 1 coordinate";
    throw std::invalid_argument(msg.str());
  }
  Array< InterpInfo > interp;
  getInterpInfo(c0, interp, true);
  if (interp.size() == 0)
  {
    stringstream msg;
    msg << c0 << " not on processor " << _mdMap->getTeuchosComm()->getRank();
    throw std::out_of_range(msg.str());
  }
  Scalar result = 0;
  for (Array< InterpInfo >::iterator it = interp.begin();
       it != interp.end(); ++it)
    result += operator()(it->index[0]) * it->weight;
  return result;
}

////////////////////////////////////////////////////////////////////////

Scalar
Field::atCoordinate(Scalar c0,
                    Scalar c1) const
{
  int rank = _mdMap->getTeuchosComm()->getRank();
  // Check the dimensions
  int nd = _mdMap->numDims();
  if (nd != 2)
  {
    stringstream msg;
    msg << "atCoordinate() called on " << nd << "D Field with 2 coordinates";
    throw std::invalid_argument(msg.str());
  }
  Array< InterpInfo > interp;
  getInterpInfo(c0, c1, interp, true);
  if (interp.size() == 0)
  {
    stringstream msg;
    msg << "(" << c0 << "," << c1 << ") not on processor "
        << rank;
    throw std::out_of_range(msg.str());
  }
  Scalar result = 0;
  for (Array< InterpInfo >::iterator it = interp.begin();
       it != interp.end(); ++it)
    result += operator()(it->index[0], it->index[1]) * it->weight;
  return result;
}

////////////////////////////////////////////////////////////////////////

Scalar
Field::atCoordinate(Scalar c0,
                    Scalar c1,
                    Scalar c2) const
{
  // Check the dimensions
  int nd = _mdMap->numDims();
  if (nd != 3)
  {
    stringstream msg;
    msg << "atCoordinate() called on " << nd << "D Field with 3 coordinates";
    throw std::invalid_argument(msg.str());
  }
  Array< InterpInfo > interp;
  getInterpInfo(c0, c1, c2, interp, true);
  if (interp.size() == 0)
  {
    stringstream msg;
    msg << "(" << c0 << "," << c1 << "," << c2 << ") not on processor "
        << _mdMap->getTeuchosComm()->getRank();
    throw std::out_of_range(msg.str());
  }
  Scalar result = 0;
  for (Array< InterpInfo >::iterator it = interp.begin();
       it != interp.end(); ++it)
    result += operator()(it->index[0], it->index[1], it->index[2]) * 
              it->weight;
  return result;
}

////////////////////////////////////////////////////////////////////////

void
Field::getInterpInfo(Scalar c0,
                     Array< InterpInfo > & interp,
                     bool uniqueProc) const
{
  interp.clear();

  // Determine minimum and maximum indexes.  Note that the min is
  // inclusive and the max is exclusive.
  Domi::Slice iBounds = getLocalBounds(0, false);
  Ordinal     imin    = iBounds.start();
  Ordinal     imax    = iBounds.stop();
  if (getLowerNeighbor(0) == -1) imin -= getLowerBndryPad(0);
  if (getUpperNeighbor(0) == -1) imax += getUpperBndryPad(0);

  try
  {
    // Obtain the bracketing coordinates
    Ordinal i = nearestIndex(0, c0, true);
    if (uniqueProc)
      if (i < imin || i >= imax)
        return;
    Scalar c0lo = getCoordinateAtPoint( i );
    Scalar c0hi = getCoordinateAtPoint(i+1);
    // Translate and normalize the given coordinate
    c0 = (c0 - c0lo) / (c0hi - c0lo);
    // Create the array of InterpInfo
    Scalar tol = 1e-12;
    Scalar wt = 1 - c0;
    if (abs(wt) > tol) interp.append( InterpInfo( i , wt) );
    wt = c0;
    if (abs(wt) > tol) interp.append( InterpInfo(i+1, wt) );
  }
  catch (std::out_of_range & e)
  {
    // This means the coordinates are on a different processor
  }
}

////////////////////////////////////////////////////////////////////////

void
Field::getInterpInfo(Scalar c0,
                     Scalar c1,
                     Array< InterpInfo > & interp,
                     bool uniqueProc) const
{
  interp.clear();

  // Determine minimum and maximum indexes.  Note that the min is
  // inclusive and the max is exclusive.
  Domi::Slice iBounds = getLocalBounds(0, false);
  Domi::Slice jBounds = getLocalBounds(1, false);
  Ordinal     imin    = iBounds.start();
  Ordinal     imax    = iBounds.stop();
  Ordinal     jmin    = jBounds.start();
  Ordinal     jmax    = jBounds.stop();
  if (getLowerNeighbor(0) == -1) imin -= getLowerBndryPad(0);
  if (getUpperNeighbor(0) == -1) imax += getUpperBndryPad(0);
  if (getLowerNeighbor(1) == -1) jmin -= getLowerBndryPad(1);
  if (getUpperNeighbor(1) == -1) jmax += getUpperBndryPad(1);

  try
  {
    // Obtain the bracketing coordinates
    Ordinal i = nearestIndex(0, c0, true);
    Ordinal j = nearestIndex(1, c1, true);
    if (uniqueProc)
      if ((i < imin) || (i >= imax) ||
          (j < jmin) || (j >= jmax)    )
        return;
    Scalar c0lo = getCoordinateAtPoint( i ,0);
    Scalar c0hi = getCoordinateAtPoint(i+1,0);
    Scalar c1lo = getCoordinateAtPoint( j ,1);
    Scalar c1hi = getCoordinateAtPoint(j+1,1);
    // Translate and normalize the given coordinate
    c0 = (c0 - c0lo) / (c0hi - c0lo);
    c1 = (c1 - c1lo) / (c1hi - c1lo);
    // Create the array of InterpInfo
    Scalar tol = 1e-12;
    Scalar wt;
    wt = (1-c0) * (1-c1);
    if (abs(wt) > tol) interp.append( InterpInfo( i ,  j , wt) );
    wt =   c0   * (1-c1);
    if (abs(wt) > tol) interp.append( InterpInfo(i+1,  j , wt) );
    wt = (1-c0) *   c1  ;
    if (abs(wt) > tol) interp.append( InterpInfo( i , j+1, wt) );
    wt =   c0   *   c1  ;
    if (abs(wt) > tol) interp.append( InterpInfo(i+1, j+1, wt) );
  }
  catch (std::out_of_range & e)
  {
    // This means the coordinates are on a different processor
  }
}

////////////////////////////////////////////////////////////////////////

void
Field::getInterpInfo(Scalar c0,
                     Scalar c1,
                     Scalar c2,
                     Array< InterpInfo > & interp,
                     bool uniqueProc) const
{
  interp.clear();

  // Determine minimum and maximum indexes.  Note that the min is
  // inclusive and the max is exclusive.
  Domi::Slice iBounds = getLocalBounds(0, false);
  Domi::Slice jBounds = getLocalBounds(1, false);
  Domi::Slice kBounds = getLocalBounds(2, false);
  Ordinal     imin    = iBounds.start();
  Ordinal     imax    = iBounds.stop();
  Ordinal     jmin    = jBounds.start();
  Ordinal     jmax    = jBounds.stop();
  Ordinal     kmin    = kBounds.start();
  Ordinal     kmax    = kBounds.stop();
  if (getLowerNeighbor(0) == -1) imin -= getLowerBndryPad(0);
  if (getUpperNeighbor(0) == -1) imax += getUpperBndryPad(0);
  if (getLowerNeighbor(1) == -1) jmin -= getLowerBndryPad(1);
  if (getUpperNeighbor(1) == -1) jmax += getUpperBndryPad(1);
  if (getLowerNeighbor(2) == -1) kmin -= getLowerBndryPad(2);
  if (getUpperNeighbor(2) == -1) kmax += getUpperBndryPad(2);

  try
  {
    // Obtain the bracketing coordinates.  Note that nearestIndex() is
    // called with includeCommPad=true, regardless of the value of the
    // includeCommPad method argument.  This is to catch interpolations
    // that span communication padding boundaries.
    Ordinal i = nearestIndex(0, c0, true);
    Ordinal j = nearestIndex(1, c1, true);
    Ordinal k = nearestIndex(2, c2, true);
    if (uniqueProc)
      if ((i < imin) || (i >= imax) ||
          (j < jmin) || (j >= jmax) ||
          (k < kmin) || (k >= kmax)    )
        return;
    Scalar c0lo = getCoordinateAtPoint( i ,0);
    Scalar c0hi = getCoordinateAtPoint(i+1,0);
    Scalar c1lo = getCoordinateAtPoint( j ,1);
    Scalar c1hi = getCoordinateAtPoint(j+1,1);
    Scalar c2lo = getCoordinateAtPoint( k ,2);
    Scalar c2hi = getCoordinateAtPoint(k+1,2);
    // Translate and normalize the given coordinate
    c0 = (c0 - c0lo) / (c0hi - c0lo);
    c1 = (c1 - c1lo) / (c1hi - c1lo);
    c2 = (c2 - c2lo) / (c2hi - c2lo);
    // Create the array of InterpInfo
    Scalar tol = 1e-12;
    Scalar wt;
    wt = (1-c0) * (1-c1) * (1-c2);
    if (abs(wt) > tol) interp.append( InterpInfo( i ,  j ,  k , wt) );
    wt =   c0   * (1-c1) * (1-c2);
    if (abs(wt) > tol) interp.append( InterpInfo(i+1,  j ,  k , wt) );
    wt = (1-c0) *   c1   * (1-c2);
    if (abs(wt) > tol) interp.append( InterpInfo( i , j+1,  k , wt) );
    wt =   c0   *   c1   * (1-c2);
    if (abs(wt) > tol) interp.append( InterpInfo(i+1, j+1,  k , wt) );
    wt = (1-c0) * (1-c1) *   c2  ;
    if (abs(wt) > tol) interp.append( InterpInfo( i ,  j , k+1, wt) );
    wt =   c0   * (1-c1) *   c2  ;
    if (abs(wt) > tol) interp.append( InterpInfo(i+1,  j , k+1, wt) );
    wt = (1-c0) *   c1   *   c2  ;
    if (abs(wt) > tol) interp.append( InterpInfo( i , j+1, k+1, wt) );
    wt =   c0   *   c1   *   c2  ;
    if (abs(wt) > tol) interp.append( InterpInfo(i+1, j+1, k+1, wt) );
  }
  catch (std::out_of_range & e)
  {
    // This means the coordinates are on a different processor
  }
}

////////////////////////////////////////////////////////////////////////

Scalar
Field::getCoordinateAtPoint(Ordinal i,
                            int axis) const
{
  Scalar coord = _mesh->getCoordinateAtPoint(i, axis);
  if (getStagger(axis))
    coord = (coord + _mesh->getCoordinateAtPoint(i+1, axis))/2.0;
  return coord;
}

////////////////////////////////////////////////////////////////////////

Array< Scalar >
Field::getCoordinatesAtPoint(Ordinal i,
                             Ordinal j) const
{
  Array< Scalar > coords(2);
  coords[0] = getCoordinateAtPoint(i, 0);
  coords[1] = getCoordinateAtPoint(j, 1);
  return coords;
}

////////////////////////////////////////////////////////////////////////

Array< Scalar >
Field::getCoordinatesAtPoint(Ordinal i,
                             Ordinal j,
                             Ordinal k) const
{
  Array< Scalar > coords(3);
  coords[0] = getCoordinateAtPoint(i, 0);
  coords[1] = getCoordinateAtPoint(j, 1);
  coords[2] = getCoordinateAtPoint(k, 2);
  return coords;
}

////////////////////////////////////////////////////////////////////////

void
Field::writeBinary(const string & filename,
                   bool           includeBndryPad) const
{
  // Generate default filename
  string fname;
  if (filename == "")
    fname = defaultFilename();
  else
    fname = filename;

  // If we are using MPI and overwriting an existing file, and the new
  // file is shorter than the old file, it appears that the new file
  // will retain the old file's length and trailing data.  To prevent
  // this behavior, we open and close the file to give it zero length.
  CommPtr comm = _mdMap->getTeuchosComm();
  int     pid  = comm->getRank();
  FILE  * datafile;
  if (pid == 0)
  {
    datafile = fopen(fname.c_str(), "w");
    fclose(datafile);
  }
  comm->barrier();

#ifdef DGM_PARALLEL

  // Parallel output

  // Get the buffer location for the first point of data, including
  // any communication padding or boundary padding.
  const Scalar * buffer = _mdVector->getData().arrayView().getRawPtr();

  // Compute either _fileInfo or _fileInfoBndryPad, whichever is
  // appropriate, and return a reference to that fileInfo object
  Teuchos::RCP< FileInfo > & fileInfo = computeFileInfo(includeBndryPad);

  // Since DGM_PARALLEL is defined, we know that comm points to a
  // const Teuchos::MpiComm< int >.  We downcast, extract and
  // dereference so that we can get access to the MPI_Comm used to
  // construct it.
  Teuchos::RCP< const Teuchos::MpiComm< int > > mpiComm =
    Teuchos::rcp_dynamic_cast< const Teuchos::MpiComm< int > >(comm);
  const Teuchos::OpaqueWrapper< MPI_Comm > & communicator =
    *(mpiComm->getRawMpiComm());

  // Compute the access mode
  int access = MPI_MODE_WRONLY | MPI_MODE_CREATE;

  // I copy the fname C string, because the c_str() method returns
  // a const char*, and the MPI_File_open() function requires
  // (incorrectly) a non-const char*.
  char * cstr = new char[fname.size()+1];
  std::strcpy(cstr, fname.c_str());

  // Use MPI I/O to write the binary file
  MPI_File   mpiFile;
  MPI_Status status;
  char       datarep[7] = "native";
  MPI_File_open(communicator(),
                cstr,
                access,
                MPI_INFO_NULL,
                &mpiFile);
  MPI_File_set_view(mpiFile,
                    0,
                    mpiType< Scalar >(),
                    *(fileInfo->filetype),
                    datarep,
                    MPI_INFO_NULL);
  MPI_File_write_all(mpiFile,
                     (void*)buffer,
                     1,
                     *(fileInfo->datatype),
                     &status);
  MPI_File_close(&mpiFile);

  // Delete the C string
  delete [] cstr;

#else

  // Serial output

  // Initialize the data file
  datafile = fopen(fname.c_str(), "w");

  typedef typename Domi::MDArrayView< const Scalar >::iterator iterator;

  Domi::MDArrayView< const Scalar > data = _mdVector->getData(includeBndryPad);
  for (iterator it = data.begin(); it != data.end(); ++it)
    fwrite(&*it, sizeof(Scalar), 1, datafile);

  // Close the data file
  fclose(datafile);

#endif

}

////////////////////////////////////////////////////////////////////////

void
Field::writeBinary(int  n,
                   bool includeBndryPad) const
{
  std::stringstream ss;
  ss << symbol() << "." << n << ".bin";
  writeBinary(ss.str(), includeBndryPad);
}

////////////////////////////////////////////////////////////////////////

void
Field::readBinary(const string & filename,
                  bool           includeBndryPad)
{
  // Generate default filename
  string fname;
  if (filename == "")
    fname = defaultFilename();
  else
    fname = filename;

#ifdef DGM_PARALLEL

  // Parallel input

  // Get the buffer location for the first point of data, including
  // any communication padding or boundary padding.
  Scalar * buffer = _mdVector->getDataNonConst(0).getRawPtr();

  // Compute either _fileInfo or _fileInfoBndryPad, whichever is
  // appropriate, and return a reference to that fileInfo object
  Teuchos::RCP< FileInfo > & fileInfo = computeFileInfo(includeBndryPad);

  // Since DGM_PARALLEL is defined, we know that comm points to a
  // const Teuchos::MpiComm< int >.  We downcast, extract and
  // dereference so that we can get access to the MPI_Comm used to
  // construct it.
  CommPtr comm = _mdMap->getTeuchosComm();
  Teuchos::RCP< const Teuchos::MpiComm< int > > mpiComm =
    Teuchos::rcp_dynamic_cast< const Teuchos::MpiComm< int > >(comm);
  const Teuchos::OpaqueWrapper< MPI_Comm > & communicator =
    *(mpiComm->getRawMpiComm());

  // Compute the access mode
  int access = MPI_MODE_RDONLY;

  // I copy the fname C string, because the c_str() method returns
  // a const char*, and the MPI_File_open() function requires
  // (incorrectly) a non-const char*.
  char * cstr = new char[fname.size()+1];
  std::strcpy(cstr, fname.c_str());

  // Use MPI I/O to read the binary file
  MPI_File   mpiFile;
  MPI_Status status;
  char       datarep[7] = "native";
  MPI_File_open(communicator(), cstr, access, MPI_INFO_NULL, &mpiFile);
  MPI_File_set_view(mpiFile, 0, mpiType< Scalar >(),
                           *(fileInfo->filetype), datarep, MPI_INFO_NULL);
  MPI_File_read_all(mpiFile, (void*)buffer, 1, *(fileInfo->datatype),
                           &status);
  MPI_File_close(&mpiFile);

  // Delete the C string
  delete [] cstr;

  // Serial output
#else

  // Initialize the data file
  FILE * datafile;
  datafile = fopen(fname.c_str(), "r");

  typedef typename Domi::MDArrayView< Scalar >::iterator iterator;

  Domi::MDArrayView< Scalar > data =
    _mdVector->getDataNonConst(includeBndryPad);
  for (iterator it = data.begin(); it != data.end(); ++it)
    fread(&*it, sizeof(Scalar), 1, datafile);

  // Close the data file
  fclose(datafile);

#endif

}

////////////////////////////////////////////////////////////////////////

void
Field::readBinary(int  n,
                  bool includeBndryPad)
{
  std::stringstream ss;
  ss << symbol() << "." << n << ".bin";
  readBinary(ss.str());
}

////////////////////////
// Static helper methods
////////////////////////

////////////////////////////////////////////////////////////////////////

Array< int >
Field::constructStagger(const int                    numDims,
                        const ArrayView< const int > stagger)
{
  Array< int > result(numDims, 0);
  for (int i = 0; i < std::min(numDims, (int)stagger.size()); ++i)
    result[i] = stagger[i];
  return result;
}

////////////////////////////////////////////////////////////////////////

ArrayRCP< int >
Field::constructCommPads(const int              numDims,
                         const ArrayView< int > commPads)
{
  ArrayRCP< int > result(numDims, 0);
  for (int i = 0; i < std::min(numDims, (int)commPads.size()); ++i)
    result[i] = commPads[i];
  return result;
}

////////////////////////////////////////////////////////////////////////

MDMapPtr
Field::constructMdMapFromStagger(const MeshPtr mesh,
                                 ArrayView< const int > stagger)
{
  // The returned MDMap will be similar to the MDMap of the provided
  // Mesh, except that the dimensions will be reduced by one along
  // every axis for which the stagger flag is set.
  int       numDims    = mesh->numDims();
  MDCommPtr meshMdComm = mesh->getMDComm();
  MDMapPtr  meshMdMap  = mesh->getMDMap();
  MDMapPtr  newMdMap   = meshMdMap;
  for (int axis = 0; axis < numDims; ++axis)
  {
    if (stagger[axis])
    {
      Domi::Slice bounds = meshMdMap->getGlobalBounds(axis,false);
      Domi::Slice slice(bounds.start(),
                        bounds.stop()-1);
      int bndryPad = meshMdMap->getBndryPadSize(axis);
      MDMapPtr tempMdMap = Teuchos::rcp(new Domi::MDMap(*newMdMap,
                                                          axis,
                                                          slice,
                                                          bndryPad));
      newMdMap = tempMdMap;
    }
  }
  return newMdMap;
}

////////////////////////////////////////////////////////////////////////

ArrayRCP< Ordinal >
Field::copyArray(const ArrayView< Ordinal > & source)
{
  ArrayRCP< Ordinal > result(source.size());
  for (int i = 0; i < result.size(); ++i)
    result[i] = source[i];
  return result;
}

//////////////////////////////////////////
// Non-static constructor helper functions
//////////////////////////////////////////

////////////////////////////////////////////////////////////////////////

int
Field::neighborRank(ArrayView<int> indexes)
{
  // Get references to domain decomposition info
  //ArrayRCP< int > axisRanks    = _mdMap->getAxisRanks();
  Array< int > axisNumProcs = _mdMap->getCommDims();

  // Axis 0
  //int rank = axisRanks[0] + indexes[0];
  int rank = _mdMap->getCommIndex(0) + indexes[0];
  if (rank < 0) rank += axisNumProcs[0];
  if (rank >= axisNumProcs[0]) rank -= axisNumProcs[0];

  //Axis 1
  if (_mdMap->numDims() > 1)
  {
    //int rank1 = axisRanks[1] + indexes[1];
    int rank1 = _mdMap->getCommIndex(1) + indexes[1];
    if (rank1 < 0) rank1 += axisNumProcs[1];
    if (rank1 >= axisNumProcs[1]) rank1 -= axisNumProcs[1];
    rank += rank1 * axisNumProcs[0];
  }

  // Axis 2
  if (_mdMap->numDims() > 2)
  {
    //int rank2 = axisRanks[2] + indexes[2];
    int rank2 = _mdMap->getCommIndex(2) + indexes[2];
    if (rank2 < 0) rank2 += axisNumProcs[2];
    if (rank2 >= axisNumProcs[2]) rank2 -= axisNumProcs[2];
    rank += rank2 * axisNumProcs[0] * axisNumProcs[1];
  }
  return rank;
}

////////////////////////////////////////////////////////////////////////

Teuchos::RCP< Field::FileInfo > &
Field::computeFileInfo(bool includeBndryPad) const
{
  // Work with the appropriate FileInfo object.  By using a reference
  // here, we are working directly with the member data.
  Teuchos::RCP< Field::FileInfo > & fileInfo =
    includeBndryPad ? _fileInfoBndryPad : _fileInfo;

  // If the fileInfo object already has been set, our work is done
  if (!fileInfo.is_null()) return fileInfo;

  // Initialize the new FileInfo object
  int ndims = _mdMap->numDims();
  fileInfo.reset(new Field::FileInfo);
  fileInfo->fileDims.resize(ndims);
  fileInfo->bufferDims.resize(ndims);
  fileInfo->dataDims.resize(ndims);
  fileInfo->fileStart.resize(ndims);
  fileInfo->dataStart.resize(ndims);

  // Initialize the shapes and starts.
  Teuchos::Array< int > bndryPad(ndims);
  for (int axis = 0; axis < ndims; ++axis)
  {
    // Initialize arrays as if boundary padding is not included in
    // output
    Domi::Slice bounds = getLocalBounds(axis,false);
    Domi::Slice pBounds = _mdMap->getLocalBounds(axis,true);
    bndryPad[axis]      = _mdMap->getBndryPadSize(axis);
    fileInfo->fileDims[axis]   = getGlobalDim(axis,includeBndryPad);
    fileInfo->bufferDims[axis] = pBounds.stop() - pBounds.start();
    fileInfo->dataDims[axis]   = bounds.stop()  - bounds.start();
    fileInfo->fileStart[axis]  = _mdMap->getGlobalRankBounds(axis).start();
    fileInfo->dataStart[axis]  = bounds.start();
    // Modify arrays if boundary padding is included
    if (includeBndryPad)
    {
      if (_mdMap->getLowerNeighbor(axis) == -1)
      {
        fileInfo->dataDims[axis] += bndryPad[axis];
        fileInfo->fileStart[axis] = 0;
        fileInfo->dataStart[axis] = 0;
      }
      if (_mdMap->getUpperNeighbor(axis) == -1)
      {
        fileInfo->dataDims[axis] += bndryPad[axis];
      }
    }
    else
    {
      fileInfo->fileStart[axis] -= bndryPad[axis];
    }
  }

#ifdef FDM_FIELD_DEBUG_IO
  int pid = _mdMap->getTeuchosComm()->getRank();
  cout << pid << ": bndryPad   = " << bndryPad()             << endl;
  cout << pid << ": fileDims   = " << fileInfo->fileDims()   << endl;
  cout << pid << ": bufferDims = " << fileInfo->bufferDims() << endl;
  cout << pid << ": dataDims   = " << fileInfo->dataDims()   << endl;
  cout << pid << ": fileStart  = " << fileInfo->fileStart()  << endl;
  cout << pid << ": dataStart  = " << fileInfo->dataStart()  << endl;
#endif

#if DGM_PARALLEL
  // Build the MPI_Datatype for the file
  fileInfo->filetype = Teuchos::rcp(new MPI_Datatype);
  MPI_Type_create_subarray(ndims,
                           fileInfo->fileDims.getRawPtr(),
                           fileInfo->dataDims.getRawPtr(),
                           fileInfo->fileStart.getRawPtr(),
                           MPI_ORDER_FORTRAN,
                           mpiType< Scalar >(),
                           fileInfo->filetype.get());
  MPI_Type_commit(fileInfo->filetype.get());

  // Build the MPI_Datatype for the data
  fileInfo->datatype = Teuchos::rcp(new MPI_Datatype);
  MPI_Type_create_subarray(ndims,
                           fileInfo->bufferDims.getRawPtr(),
                           fileInfo->dataDims.getRawPtr(),
                           fileInfo->dataStart.getRawPtr(),
                           MPI_ORDER_FORTRAN,
                           mpiType< Scalar >(),
                           fileInfo->datatype.get());
  MPI_Type_commit(fileInfo->datatype.get());
#endif  // DGM_PARALLEL

  return fileInfo;
}

}  // namespace FDM
