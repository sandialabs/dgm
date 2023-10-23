#ifndef FDM_FIELD_HPP
#define FDM_FIELD_HPP

//! \file   FDM_Field.hpp
//! \brief  Finite Difference Field declaration
//! \author Bill Spotz

// FDM includes
#include "FDM_Mesh.hpp"
#include "FDM_CartesianMesh.hpp"

// Teuchos classes
using Teuchos::Array;
using Teuchos::ArrayView;
using Teuchos::ArrayRCP;

// #define FDM_FIELD_DEBUG_IO

//! Finite Difference Method namespace
namespace FDM
{

// Forward declare the Field class so that we can define the reference
// counted pointer typedef
class Field;

// Pointer to a Field
typedef Teuchos::RCP< Field > FieldPtr;

/** \brief Interp info struct
 *
 * For a value to be extracted or applied at a coordinate that does
 * not correspond to a precise set of indexes, we will need to
 * interpolate among a set of weights near that coordinate.  This
 * simple struct encapsulates the required information at a single
 * index.
 */
struct InterpInfo
{
  Array< Ordinal > index;
  Scalar           weight;

  /** \brief 1D constructor
   *
   * \param i [in]   First index
   *
   * \param wt [in]  Interpolation weight
   */
  InterpInfo(Ordinal i,
             Scalar wt) :
    index(Teuchos::tuple(i)),
    weight(wt)
  {
  }

  /** \brief 2D constructor
   *
   * \param i [in]   First index
   *
   * \param j [in]   Second index
   *
   * \param wt [in]  Interpolation weight
   */
  InterpInfo(Ordinal i,
             Ordinal j,
             Scalar wt) :
    index(Teuchos::tuple(i,j)),
    weight(wt)
  {
  }

  /** \brief 3D constructor
   *
   * \param i [in]   First index
   *
   * \param j [in]   Second index
   *
   * \param k [in]   Third index
   *
   * \param wt [in]  Interpolation weight
   */
  InterpInfo(Ordinal i,
             Ordinal j,
             Ordinal k,
             Scalar wt) :
    index(Teuchos::tuple(i,j,k)),
    weight(wt)
  {
  }

  /** \brief Arbitrary dimension constructor
   *
   * \param indx [in]  Array of indexes
   *
   * \param wt [in]    Interpolation weight
   */
  InterpInfo(ArrayView< Ordinal > indx,
             Scalar wt) :
    index(indx),
    weight(wt)
  {
  }
};

////////////////////////////////////////////////////////////////////////

/** \brief FDM Field class
 *
 * The FDM::Field class describes an object that associates an
 * MDVector with a Mesh, which are both built upon the same MDMap.
 * The Field data can therefore be accessed with a tuple of indexes,
 * rather than a single Ordinal.
 */
class Field : public DTK::Field< Scalar, Ordinal >, 
              public Teuchos::Describable
{

private:

  /** \brief A simple struct for storing file-related information
   */
  struct FileInfo
  {
    Array< int > fileDims;
    Array< int > bufferDims;
    Array< int > dataDims;
    Array< int > fileStart;
    Array< int > dataStart;
#ifdef DGM_PARALLEL
    Teuchos::RCP< MPI_Datatype > filetype;
    Teuchos::RCP< MPI_Datatype > datatype;
#endif
  };

public:

  /** \name Constructors and destructor */
  //@{

  /** \brief Field constructor without Vector data
   *
   * \param symbol [in]   Short mathematical symbol for this field
   *
   * \param name [in]     Longer string version of field name
   *
   * \param mesh [in]     Pointer to the Mesh object for this field
   *
   * \param stagger [in]  Array of stagger flags, one for each
   *                      dimension. Unspecified stagger flags are
   *                      assumed to be false
   *
   */
  Field(const string &               symbol,
        const string &               name,
        const MeshPtr                mesh,
        const ArrayView< const int > stagger = ArrayView< const int >());

  /** \brief Field constructor with MDVector data
   *
   * \param symbol [in]   Short mathematical symbol for this field
   *
   * \param name [in]     Longer string version of field name
   *
   * \param mesh [in]     Pointer to the Mesh object for this field
   *
   * \param data [in]     An MDVector that is the Field data
   *
   * \param stagger [in]  Array of stagger flags, one for each
   *                      dimension. Unspecified stagger flags are
   *                      assumed to be false
   */
  Field(const string &               symbol,
        const string &               name,
        const MeshPtr                mesh,
        const MDVectorPtr            data,
        const ArrayView< const int > stagger = ArrayView< const int >());

  /** \brief Parent/single global ordinal sub-Field constructor
   *
   * \param symbol [in]  Short mathematical symbol for this field
   *
   * \param name [in]    Longer string version of field name
   *
   * \param parent [in]  A Field, from which this sub-Field will be
   *                     derived
   *
   * \param axis [in]    The axis to which this index ordinal applies
   *
   * \param index [in]   The global ordinal that defines the sub-Field
   */
  Field(const string & symbol,
        const string & name,
        const Field &  parent,
        int            axis,
        Domi::dim_type index);

  /** \brief Parent/single slice sub-Field constructor
   *
   * \param symbol [in]    Short mathematical symbol for this field
   *
   * \param name [in]      Longer string version of field name
   *
   * \param parent [in]    A Field, from which this sub-Field will be
   *                       derived
   *
   * \param axis [in]      The axis to which this slice applies
   *
   * \param slice [in]     A slice of global ordinals describing the
   *                       sub-Field
   *
   * \param bndryPad [in]  The boundary padding along the altered axis
   *                       of the new sub-Field.  This may include
   *                       indexes from the boundary padding of the
   *                       parent Field, but it does not have to.
   */
  Field(const string &      symbol,
        const string &      name,
        const Field &       parent,
        int                 axis,
        const Domi::Slice & slice,
        int                 bndryPad = 0);

  /** \brief Parent/array of slices sub-Field constructor
   *
   * \param symbol [in]     Short mathematical symbol for this field
   *
   * \param name [in]       Longer string version of field name
   *
   * \param parent [in]     A Field, from which this sub-Field will be
   *                        derived
   *
   * \param slices [in]     An array of slices of global ordinals describing the
   *                        sub-Field
   *
   * \param bndryPads [in]  The boundary padding along each altered axis
   *                        of the new sub-Field.  This may include
   *                        indexes from the boundary padding of the
   *                        parent Field, but it does not have to.
   */
  Field(const string &                            symbol,
        const string &                            name,
        const Field &                             parent,
        const Teuchos::ArrayView< Domi::Slice > & slices,
        const Teuchos::ArrayView< int >         & bndryPads =
          Teuchos::ArrayView< int >());

  /** \brief Field destructor
   */
  virtual ~Field();

  //@}

  /** \name Field meta-data accessor methods */
  //@{

  /** \brief Number of dimensions accessor method
   */
  virtual inline int numDims() const;

  /** \brief Field symbol accessor method
   */
  virtual inline const string symbol() const;

  /** \brief Field name accessor method
   */
  virtual inline const string name() const;

  /** \brief Field description accessor method
   */
  virtual string description() const;

  /** \brief Stagger flags accessor
   */
  inline ArrayView< const int > getStagger() const;

  /** \brief Stagger flags accessor
   */
  inline bool getStagger(int axis) const;

  //@}

  /** \name MDMap-related methods */
  //@{

  /** \brief MDMap accessor method
   */
  virtual inline MDMapPtr getMDMap() const;

  /** \brief Ownership MDMap accessor method
   */
  virtual inline MDMapPtr getOwnMDMap() const;

  /** \brief Return a flag indicating whether Field is defined on this
   *         processor
   */
  inline bool isOnProcessor() const;

  /** \brief Get the Teuchos communicator
   *
   * Note that if the communicator is not a full communicator, i.e. a
   * sub-communicator, that the underlying Comm pointer may be NULL,
   * depending on this processor's rank.
   */
  inline Teuchos::RCP< const Teuchos::Comm< int > > getTeuchosComm() const;

  /** \brief Get the communicator size along the given axis
   *
   * \param axis [in] the index of the axis (from zero to the number
   *        of dimensions - 1)
   *
   * This method will throw a Domi::SubcommunicatorError if the
   * communicator is a sub-communicator and this processor does not
   * belong to the sub-communicator.
   */
  inline int getCommDim(int axis) const;

  /** \brief Return the periodic flag for the given axis.
   *
   * \param axis [in] the index of the axis (from zero to the number
   *        of dimensions - 1)
   *
   * This method will throw a Domi::SubcommunicatorError if the
   * communicator is a sub-communicator and this processor does not
   * belong to the sub-communicator.
   */
  inline bool isPeriodic(int axis) const;

  /** \brief Get the axis rank of this processor
   *
   * \param axis [in] the index of the axis (from zero to the number
   *        of dimensions - 1)
   *
   * This method will throw a Domi::SubcommunicatorError if the
   * communicator is a sub-communicator and this processor does not
   * belong to the sub-communicator.
   */
  inline int getCommIndex(int axis) const;

  /** \brief Get the rank of the lower neighbor
   *
   * \param axis [in] the index of the axis (from zero to the number
   *        of dimensions - 1)
   *
   * This method will throw a Domi::SubcommunicatorError if the
   * communicator is a sub-communicator and this processor does not
   * belong to the sub-communicator.
   *
   * If the periodic flag for the given axis is off, and the axis rank
   * of the calling processor is zero, then this method returns -1.
   *
   * If the periodic flag for the given axis is on, and the axis rank
   * of the calling processor is the highest axis rank processor along
   * this axis, then the returned lower neighbor will be zero.
   */
  inline int getLowerNeighbor(int axis) const;

  /** \brief Get the rank of the upper neighbor
   *
   * \param axis [in] the index of the axis (from zero to the number
   *        of dimensions - 1)
   *
   * This method will throw a Domi::SubcommunicatorError if the
   * communicator is a sub-communicator and this processor does not
   * belong to the sub-communicator.
   *
   * If the periodic flag for the given axis is off, and the axis rank
   * of the calling processor is the highest axis rank processor along
   * this axis, then this method returns -1.
   *
   * If the periodic flag for the given axis is on, and the axis rank
   * of the calling processor is zero, then the returned lower
   * neighbor will be the highest axis rank processor along this axis.
   */
  inline int getUpperNeighbor(int axis) const;

  /** \brief Get the number of global elements along each axis
   */
  inline ArrayView< const Domi::dim_type > getGlobalDims() const;

  /** \brief Get the number of global elements along given axis
   *
   * \param axis [in]  Axis index
   *
   * \param withBndryPad [in] specify whether the bounds should
   *        include boundary padding or not
   */
  inline Ordinal getGlobalDim(int axis,
                              bool withBndryPad=false) const;

  /** \brief Get the bounds of the global problem
   *
   * \param axis [in] the index of the axis (from zero to the number
   *        of dimensions - 1)
   *
   * \param withBndryPadding [in] specify whether the bounds should
   *        include boundary padding or not
   */
  inline Domi::Slice getGlobalBounds(int axis,
                                     bool withBndryPadding=false) const;

  /** \brief Get the global loop bounds on this processor along the
   *         specified axis
   *
   * \param axis [in] the index of the axis (from zero to the number
   *        of dimensions - 1)
   *
   * \param withBndryPadding [in] specify whether the dimension should
   *        include boundary padding or not
   *
   * The loop bounds are returned in the form of a <tt>Slice</tt>, in
   * which the <tt>start()</tt> method returns the loop begin value,
   * and the <tt>stop()</tt> method returns the non-inclusive end
   * value.
   */
  inline Domi::Slice getGlobalRankBounds(int axis,
                                         bool withBndryPadding=false) const;

  /** \brief Get an array of the local dimensions
   * 
   *  The local dimensions are the locally owned dimensions plus
   *  communication padding.
   */
  inline ArrayView< const Domi::dim_type > getLocalDims() const;

  /** \brief Get the local dimension along the given axis
   *
   *  \param axis [in]     Axis index
   *
   *  \param withPad [in]  Flag whether to include padding
   */
  inline Ordinal getLocalDim(int axis,
                             bool withPad=false) const;

  /** \brief Local loop bounds
   *
   *  Returns an ArrayView of \c Slices of loop bounds for every axis.
   *  Loop bounds include padding.
   */
  inline Teuchos::ArrayView< const Domi::Slice > getLocalBounds() const;

  /** \brief Local loop bounds
   *
   *  \param axis [in]     Axis index
   *
   *  \param withPad [in]  Flag whether to include padding in the loop
   *                       bounds
   *
   *  Returns a \c Slice of local loop bounds for the given axis.
   */
  inline Domi::Slice getLocalBounds(int axis,
                                    bool withPad=false) const;

  /** \brief Local interior (non-boundrary) loop bounds for a given
   *         axis
   *
   *  \param axis [in]  Axis index
   *
   *  Returns a \c Slice of local interior loop bounds for the given
   *  axis.  For either periodic or staggered axes, the local interior
   *  loop bounds are exactly the same as the local loop bounds
   *  without padding. For non-periodic, non-staggered axes, the local
   *  interior looping bounds exclude the global end points.
   */
  inline const Domi::Slice getLocalInteriorBounds(int axis) const;

  /** \brief Return true if there is any padding stored locally
   *
   * Note that it is not as simple as whether there were communication
   * padding specified in the constructor.  Suppose non-zero
   * communication padding was specified, but the problem is on one
   * processor and no boundary padding was specified: this method will
   * return false.  Similarly, if no communication padding was
   * specified but boundary padding was, then boundary processors will
   * have padding and this method will return true.
   */
  inline bool hasPadding() const;

  /** \brief Get the size of the lower padding along the given axis
   *
   * \param axis [in] the index of the axis (from zero to the number
   *        of dimensions - 1)
   *
   * Note that the returned padding can be either communication
   * padding or boundary padding as appropriate.
   */
  inline int getLowerPadSize(int axis) const;

  /** \brief Get the size of the upper padding along the given axis
   *
   * \param axis [in] the index of the axis (from zero to the number
   *        of dimensions - 1)
   *
   * Note that the returned padding can be either communication
   * padding or boundary padding as appropriate.
   */
  inline int getUpperPadSize(int axis) const;

  /** \brief Communication padding size accessor
   *
   *  \param axis [in]  Axis index
   */
  inline int getCommPadSize(int axis) const;

  /** \brief Get the size of the lower boundary padding along the
   *         given axis
   *
   * \param axis [in] the index of the axis (from zero to the number
   *        of dimensions - 1)
   */
  inline int getLowerBndryPad(int axis) const;

  /** \brief Get the size of the upper boundary padding along the
   *         given axis
   *
   * \param axis [in] the index of the axis (from zero to the number
   *        of dimensions - 1)
   */
  inline int getUpperBndryPad(int axis) const;

  /** \brief Get the boundary padding size along the given axis
   *
   * \param axis [in] the index of the axis (from zero to the number
   *        of dimensions - 1)
   *
   * This returns the value of the boundary padding along the given
   * axis at the time of construction, regardless of whether a sub-map
   * reduced these values.
   */
  inline int getBndryPadSize(int axis) const;

  /** \brief Assign all elements of the lower pad a constant value
   *
   * \param axis [in] the axis along which the lower padding is chosen
   *
   * \param value [in] the value to be assigned to all elements of the
   *        lower padding
   */
  inline void setLowerPad(int axis,
                          const Scalar value);

  /** \brief Assign all elements of the upper pad a constant value
   *
   * \param axis [in] the axis along which the upper padding is chosen
   *
   * \param value [in] the value to be assigned to all elements of the
   *        upper padding
   */
  inline void setUpperPad(int axis,
                          const Scalar value);

  /* \brief Return whether given local index is in the padding
   *
   * \param index [in] An array of indexes ((i) for 1D, (i,j) for 2D,
   *        (i,j,k) for 3D, etc)
   */
  inline bool isPad(const Teuchos::ArrayView< Domi::dim_type > & index) const;

  /* \brief Return whether given local index is in the communication
   *        padding
   *
   * \param index [in] An array of indexes ((i) for 1D, (i,j) for 2D,
   *        (i,j,k) for 3D, etc)
   */
  inline bool
  isCommPad(const Teuchos::ArrayView< Domi::dim_type > & index) const;

  /* \brief Return whether given local index is in the boundary
   *        padding
   *
   * \param index [in] An array of indexes ((i) for 1D, (i,j) for 2D,
   *        (i,j,k) for 3D, etc)
   */
  bool isBndryPad(const Teuchos::ArrayView< Domi::dim_type > & index) const;

  /** \brief Get the storage order
   */
  inline Domi::Layout getLayout() const;

  /** \brief True if there are no stride gaps on any processor
   *
   * An MDVector constructed from a communicator and dimensions will
   * always be contiguous.  An MDVector that is a slice of a parent
   * MDMVector will generally be non-contiguous, with some exceptions.
   * There are cases where some local data is contiguous and some is
   * not, but this method returns True only if all processes' local
   * data is contiguous.
   */
  inline bool isContiguous() const;

  //@}

  /** \name Mesh-related accessor methods */

  /** \brief Mesh accessor method
   */
  virtual inline MeshPtr getMesh() const;

  /** \brief CartesianMesh accessor method
   */
  virtual inline CartesianMeshPtr getCartesianMesh() const;

  /** \brief Check for Cartesian mesh
   */
  virtual inline bool meshIsCartesian() const;

  //@}

  /** \name MDVector-related accessor methods */
  //@{

  /** \brief MDVector accessor
   */
  virtual inline MDVectorPtr getMDVector() const;

  /** \brief Const MDArrayView accessor
   */
  virtual inline Domi::MDArrayView< const Scalar > getData() const;

  /** \brief Non-const MDArrayView accessor
   */
  virtual inline Domi::MDArrayView< Scalar > getDataNonConst();

  /** \brief Get a non-const view of the lower padding data along the
   *         given axis as an MDArrayView
   *
   * \param axis [in] the axis from which to extract the lower padding
   */
  inline Domi::MDArrayView< Scalar > getLowerPadDataNonConst(int axis);

  /** \brief Get a const view of the lower padding data along the
   *         given axis as an MDArrayView
   *
   * \param axis [in] the axis from which to extract the lower padding
   */
  inline Domi::MDArrayView< const Scalar > getLowerPadData(int axis) const;

  /** \brief Get a non-const view of the upper padding data along the
   *         given axis as an MDArrayView
   *
   * \param axis [in] the axis from which to extract the upper padding
   */
  inline Domi::MDArrayView< Scalar > getUpperPadDataNonConst(int axis);

  /** \brief Get a const view of the upper padding data along the
   *         given axis as an MDArrayView
   *
   * \param axis [in] the axis from which to extract the upper padding
   */
  inline Domi::MDArrayView< const Scalar > getUpperPadData(int axis) const;

  /** \brief Set operator, single index
   *
   *  \param i [in]  Axis 0 index
   */
  inline Scalar & operator()(const Ordinal i);

  /** \brief Set operator, two indexes
   *
   *  \param i [in]  Axis 0 index
   *
   *  \param j [in]  Axis 1 index
   */
  inline Scalar & operator()(const Ordinal i,
                             const Ordinal j);

  /** \brief Set operator, three indexes
   *
   *  \param i [in]  Axis 0 index
   *
   *  \param j [in]  Axis 1 index
   *
   *  \param k [in]  Axis 2 index
   */
  inline Scalar & operator()(const Ordinal i,
                             const Ordinal j,
                             const Ordinal k);

  /** \brief Get operator, single index
   *
   *  \param i [in]  Axis 0 index
   */
  inline const Scalar & operator()(const Ordinal i) const;

  /** \brief Get operator, two indexes
   *
   *  \param i [in]  Axis 0 index
   *
   *  \param j [in]  Axis 1 index
   */
  inline const Scalar & operator()(const Ordinal i,
                                   const Ordinal j) const;

  /** \brief Get operator, three indexes
   *
   *  \param i [in]  Axis 0 index
   *
   *  \param j [in]  Axis 1 index
   *
   *  \param k [in]  Axis 2 index
   */
  inline const Scalar & operator()(const Ordinal i,
                                   const Ordinal j,
                                   const Ordinal k) const;

  /** \brief Equivalence operator
   *
   *  \param field2 [in]  Field operand
   */
  virtual inline bool operator==(const Field & field2) const;

  /** \brief Copy data method
   *
   *  \param source [in]  Field source
   */
  inline void copyData(const Field & source);

  /** \brief Copy data method
   *
   *  \param source [in]  Field source
   */
  inline void copyData(const FieldPtr & source);

  /** \brief Update all communication padding with values from
   *         neighboring processors
   */
  inline void updateCommPad();

  /** \brief Update communication padding method along given axis from
   *         neighboring processors
   *
   *  \param axis [in]  Axis along which to perform communication
   */
  virtual inline void updateCommPad(int axis);

  /** \brief Pass-through dot method for a Vector argument
   *
   *  \param a [in]  Operand
   */
  virtual inline Scalar dot(const Domi::MDVector< Scalar > & a) const;

  /** \brief Pass-through dot method for a Field argument
   *
   *  \param a [in]  Operand
   */
  virtual inline Scalar dot(const Field & a) const;

  /** \brief Pass-through norm1 method
   */
  virtual inline Teuchos::ScalarTraits< Scalar >::magnitudeType norm1() const;

  /** \brief Pass-through norm2 method
   */
  virtual inline Teuchos::ScalarTraits< Scalar >::magnitudeType norm2() const;

  /** \brief Pass-through normInf method
   */
  virtual inline Teuchos::ScalarTraits< Scalar >::magnitudeType normInf() const;

  /** \brief Pass-through meanValue method
   */
  virtual inline Scalar meanValue() const;

  /** \brief Pass-through putScalar method
   *
   *  \param alpha [in]  Scalar to be assigned
   */
  virtual inline void putScalar(const Scalar & alpha);

  /** \brief Pass-through randomize method
   */
  virtual inline void randomize();

  /** \brief Add method with Field
   *
   *  \param in [in]  Field to be added
   */
  virtual inline void add(const Field & in);

  /** \brief Scale method with Scalar
   *
   *  \param alpha [in]  Scale factor
   */
  virtual inline void scale(const Scalar & alpha);

  /** \brief Update method with one Field
   *
   *  \param alpha [in]  Scale factor
   *
   *  \param in [in]     Field to be added
   *
   *  \param beta [in]   Scale factor
   *
   *  Results in this Field's values being replaced with beta * this +
   *  alpha * in
   */
  virtual inline void update(const Scalar & alpha,
                             const Field & in,
                             const Scalar & beta = 0);

  /** \brief Update method with two Fields
   *
   *  \param alpha1 [in]  First scale factor
   *
   *  \param in1 [in]     First Field to be added
   *
   *  \param alpha2 [in]  Second scale factor
   *
   *  \param in2 [in]     Second Field to be added
   *
   *  \param beta [in]    Scale factor
   *
   *  Results in this Field's values being replaced with beta * this +
   *  alpha1 * in1 + alpha2 * in2
   */
  virtual inline void update(const Scalar & alpha1,
                             const Field & in1,
                             const Scalar & alpha2,
                             const Field & in2,
                             const Scalar & beta = 0);

  //@}

  /** \name Mesh-related indexing methods */
  //@{

  /** \brief Get nearest index
   *
   *  Return the index of the Field element whose location (which
   *  might be staggered) is just less than or equal to the given
   *  coordinate
   *
   *  \param axis [in]            Axis index
   *
   *  \param coord [in]           Coordinate value
   *
   *  \param includeCommPad [in]  Flag whether to include communication
   *                              padding
   */
  Ordinal nearestIndex(int    axis,
                       Scalar coord,
                       bool   includeCommPad=false) const;

  /** \brief Get method for 1D Scalar coordinate (as opposed to 1D Ordinal)
   *
   *  \param c0 [in]  Coordinate value along 0 axis
   */
  Scalar atCoordinate(Scalar c0) const;

  /** \brief Get method for 2D Scalar coordinates (as opposed to 2D Ordinals)
   *
   *  \param c0 [in]  Coordinate value along 0 axis
   *
   *  \param c1 [in]  Coordinate value along 1 axis
   */
  Scalar atCoordinate(Scalar c0,
                      Scalar c1) const;

  /** \brief Get method for 3D Scalar coordinates (as opposed to 3D Ordinals)
   *
   *  \param c0 [in]  Coordinate value along 0 axis
   *
   *  \param c1 [in]  Coordinate value along 1 axis
   *
   *  \param c2 [in]  Coordinate value along 2 axis
   */
  Scalar atCoordinate(Scalar c0,
                      Scalar c1,
                      Scalar c2) const;

  /** \brief Get 1D interpolation information
   *
   *  Get an array of InterpInfo (a 1D index and a weight) for
   *  interpolating at coordinate c0 on a 1D Field
   *
   *  \param c0 [in]          Coordinate value along 0 axis
   *
   *  \param interp [out]     Resulting interpolation information
   *
   *  \param uniqueProc [in]  Flag whether interpolation should occur
   *                          on a single processor
   */
  void getInterpInfo(Scalar c0,
                     Array< InterpInfo > & interp,
                     bool uniqueProc=false) const;

  /** \brief Get 2D interpolation information
   *
   *  Get an array of InterpInfo (a 2D index and a weight) for
   *  interpolating at coordinate (c0,c1) on a 2D Field
   *
   *  \param c0 [in]          Coordinate value along 0 axis
   *
   *  \param c1 [in]          Coordinate value along 1 axis
   *
   *  \param interp [out]     Resulting interpolation information
   *
   *  \param uniqueProc [in]  Flag whether interpolation should occur
   *                          on a single processor
   */
  void getInterpInfo(Scalar c0,
                     Scalar c1,
                     Array< InterpInfo > & interp,
                     bool uniqueProc=false) const;

  /** \brief Get 3D interpolation information
   *
   *  Get an array of InterpInfo (a 3D index and a weight) for
   *  interpolating at coordinate (c0,c1,c2) on a 3D Field
   *
   *  \param c0 [in]          Coordinate value along 0 axis
   *
   *  \param c1 [in]          Coordinate value along 1 axis
   *
   *  \param c2 [in]          Coordinate value along 2 axis
   *
   *  \param interp [out]     Resulting interpolation information
   *
   *  \param uniqueProc [in]  Flag whether interpolation should occur
   *                          on a single processor
   */
  void getInterpInfo(Scalar c0,
                     Scalar c1,
                     Scalar c2,
                     Array< InterpInfo > & interp,
                     bool uniqueProc=false) const;

  /** \brief Get coordinate value
   *
   *  Return the 1D coordinate of the Field at the given index, along
   *  the given axis
   *
   *  \param i [in]     Index along given axis
   *
   *  \param axis [in]  Axis index
   */
  Scalar getCoordinateAtPoint(Ordinal i,
                              int axis=0) const;

  /** \brief Return the 2D coordinate of the Field at the given indexes
   *
   *  \param i [in]  Axis 0 index
   *
   *  \param j [in]  Axis 1 index
   */
  Array< Scalar > getCoordinatesAtPoint(Ordinal i,
                                        Ordinal j) const;

  /** \brief Return the 3D coordinate of the Field at the given indexes
   *
   *  \param i [in]  Axis 0 index
   *
   *  \param j [in]  Axis 1 index
   *
   *  \param k [in]  Axis 2 index
   */
  Array< Scalar > getCoordinatesAtPoint(Ordinal i,
                                        Ordinal j,
                                        Ordinal k) const;

  //@}

  /** \name Inpu/Output methods */
  //@{

  /** \brief Output a binary file of the Field data
   */
  void
  writeBinary(const string & filename        = string(""),
              bool           includeBndryPad = false) const;

  /** \brief Write a binary file of the Field data
   *
   *  Use the time step number as the argument (for building the
   *  filename)
   */
  void
  writeBinary(int  n,
              bool includeBndryPad = false) const;

  /** \brief Input a binary file of the Field data
   */
  void
  readBinary(const string & filename        = string(""),
             bool           includeBndryPad = false);

  /** \brief Read a binary file of the Field data
   *
   *  Use the time step number as the argument (for building the
   *  filename)
   */
  void
  readBinary(int  n,
             bool includeBndryPad = false);

  //@}

private:

  // Field description
  string _name;

  // Mesh for the Field.
  MeshPtr _mesh;

  // CartesianMesh for the Field.  If the underlying mesh is not a
  // cartesian mesh, then this pointer will be null.
  CartesianMeshPtr _cMesh;

  // MDMap with communication padding for the the Field.
  MDMapPtr _mdMap;

  // MDVector of underlying data for the Field.
  MDVectorPtr _mdVector;

  // MDArrayView of the field data.
  Domi::MDArrayView< Scalar > _mdArrayView;

  // Flags indicating the Field stagger status along each axis.
  const Array< int > _stagger;

  // FileInfo struct for an input or output file that does not store
  // boundary padding.  This is mutable because it does not get set until
  // the first time the Field is read or written to a file, and the
  // writeBinary() methods should logically be const.
  mutable Teuchos::RCP< FileInfo > _fileInfo;

  // FileInfo struct for an input or output file that does store
  // boundary points.  This is mutable because it does not get set
  // until the first time the Field is read or written to a file, and
  // the writeBinary() methods should logically be const.
  mutable Teuchos::RCP< FileInfo > _fileInfoBndryPad;

  //////////////////////////////////////////////////////////////////////

  // Static helper methods

  // Construct the stagger flags from a possibly incomplete list of
  // user supplied stagger flags
  static Array< int >
  constructStagger(const int                    numDims,
                   const ArrayView< const int > stagger);

  // Construct the communication padding from a posibly incomplete
  // list of user supplied communication padding
  static ArrayRCP< int > constructCommPads(const int              numDims,
                                           const ArrayView< int > commPads);

  // Construct a new MDMap using the Mesh MDMap as a parent, and
  // modifying it according to the stagger flags
  static MDMapPtr constructMdMapFromStagger(const MeshPtr mesh,
                                            ArrayView< int const > stagger);

  // Helper function for copying an ArrayView into an ArrayRCP
  static ArrayRCP< Ordinal >
  copyArray(const ArrayView< Ordinal > & source);

  // Non-static construction helper functions

  // Compute the rank of a neighboring processor
  int neighborRank(ArrayView< int > indexes);

  // Set the cartesian mesh pointer.  If the underlying mesh is not a
  // cartesian mesh, then set the pointer to be null.
  inline void setCartesianMeshPtr();

  // Construct a default file name
  inline string defaultFilename() const;

  // Compute either the _fileInfo or _fileInfoBndryPad data members.
  // This private method gets called by the writeBinary() and
  // readBinary() methods, and sets the requested fileInfo object,
  // unless it has already been set.  This is const so that it can be
  // called by writeBinary(), but its whole purpose is to change
  // mutable data members.
  Teuchos::RCP< FileInfo > & computeFileInfo(bool includeBndryPad) const;

};

/////////////////////////
// Inline implementations
/////////////////////////

////////////////////////////////////////////////////////////////////////

inline 
int
Field::numDims() const
{
  return _mdMap->numDims();
}

////////////////////////////////////////////////////////////////////////

inline const
string
Field::symbol() const
{
  return getObjectLabel();
}

////////////////////////////////////////////////////////////////////////

inline const
string
Field::name() const
{
  if (_name.empty())
    return symbol();
  else
    return _name;
}

////////////////////////////////////////////////////////////////////////

inline
ArrayView< const int >
Field::getStagger() const
{
  return _stagger();
}

////////////////////////////////////////////////////////////////////////

inline
bool
Field::getStagger(int axis) const
{
  return bool(_stagger[axis]);
}

////////////////////////////////////////////////////////////////////////

inline
ArrayView< const Domi::dim_type >
Field::getGlobalDims() const
{
  return _mdMap->getGlobalDims();
}

////////////////////////////////////////////////////////////////////////

inline
Ordinal
Field::getGlobalDim(int axis,
                    bool withBndryPadding) const
{
  return _mdMap->getGlobalDim(axis, withBndryPadding);
}

////////////////////////////////////////////////////////////////////////

inline
Domi::Slice
Field::getGlobalBounds(int axis,
                       bool withBndryPadding) const
{
  return _mdMap->getGlobalBounds(axis, withBndryPadding);
}

////////////////////////////////////////////////////////////////////////

inline
Domi::Slice
Field::getGlobalRankBounds(int axis,
                           bool withBndryPadding) const
{
  return _mdMap->getGlobalRankBounds(axis, withBndryPadding);
}

////////////////////////////////////////////////////////////////////////

inline
ArrayView< const Domi::dim_type >
Field::getLocalDims() const
{
  return _mdMap->getLocalDims();
}

////////////////////////////////////////////////////////////////////////

inline
Ordinal
Field::getLocalDim(int axis,
                   bool withPad) const
{
  return _mdMap->getLocalDim(axis, withPad);
}

////////////////////////////////////////////////////////////////////////

inline
Teuchos::ArrayView< const Domi::Slice >
Field::getLocalBounds() const
{
  return _mdMap->getLocalBounds();
}

////////////////////////////////////////////////////////////////////////

inline
Domi::Slice
Field::getLocalBounds(int axis,
                      bool withPad) const
{
  return _mdMap->getLocalBounds(axis, withPad);
}

////////////////////////////////////////////////////////////////////////

inline
const Domi::Slice
Field::getLocalInteriorBounds(int axis) const
{
  if (_stagger[axis])
    return _mdMap->getLocalBounds(axis, false);
  else
    return _mdMap->getLocalInteriorBounds(axis);
}

////////////////////////////////////////////////////////////////////////

inline
bool
Field::hasPadding() const
{
  return _mdMap->hasPadding();
}

////////////////////////////////////////////////////////////////////////

inline
int
Field::getLowerPadSize(int axis) const
{
  return _mdMap->getLowerPadSize(axis);
}

////////////////////////////////////////////////////////////////////////

inline
int
Field::getUpperPadSize(int axis) const
{
  return _mdMap->getUpperPadSize(axis);
}

////////////////////////////////////////////////////////////////////////

inline
int
Field::getCommPadSize(int axis) const
{
  return _mdMap->getCommPadSize(axis);
}

////////////////////////////////////////////////////////////////////////

inline
int
Field::getLowerBndryPad(int axis) const
{
  return _mdMap->getLowerBndryPad(axis);
}

////////////////////////////////////////////////////////////////////////

inline
int
Field::getUpperBndryPad(int axis) const
{
  return _mdMap->getUpperBndryPad(axis);
}

////////////////////////////////////////////////////////////////////////

inline
int
Field::getBndryPadSize(int axis) const
{
  return _mdMap->getBndryPadSize(axis);
}

////////////////////////////////////////////////////////////////////////

inline
void
Field::setLowerPad(int axis,
                   const Scalar value)
{
  _mdVector->setLowerPad(axis, value);
}

////////////////////////////////////////////////////////////////////////

inline
void
Field::setUpperPad(int axis,
                   const Scalar value)
{
  _mdVector->setUpperPad(axis,value);
}

////////////////////////////////////////////////////////////////////////

inline
bool
Field::isPad(const Teuchos::ArrayView< Domi::dim_type > & index) const
{
  return _mdMap->isPad(index);
}

////////////////////////////////////////////////////////////////////////

inline
bool
Field::isCommPad(const Teuchos::ArrayView< Domi::dim_type > & index) const
{
  return _mdMap->isCommPad(index);
}

////////////////////////////////////////////////////////////////////////

inline
bool
Field::isBndryPad(const Teuchos::ArrayView< Domi::dim_type > & index) const
{
  return _mdMap->isBndryPad(index);
}

////////////////////////////////////////////////////////////////////////

inline
Domi::Layout
Field::getLayout() const
{
  return _mdMap->getLayout();
}

////////////////////////////////////////////////////////////////////////

inline
bool
Field::isContiguous() const
{
  return _mdMap->isContiguous();
}

////////////////////////////////////////////////////////////////////////

inline
MeshPtr
Field::getMesh() const
{
  return _mesh;
}

////////////////////////////////////////////////////////////////////////

inline
CartesianMeshPtr
Field::getCartesianMesh() const
{
  return _cMesh;
}

////////////////////////////////////////////////////////////////////////

inline
bool
Field::meshIsCartesian() const
{
  return !_cMesh.is_null();
}

////////////////////////////////////////////////////////////////////////

inline
MDMapPtr
Field::getMDMap() const
{
  return _mdMap;
}

////////////////////////////////////////////////////////////////////////

inline
MDMapPtr
Field::getOwnMDMap() const
{
  return _mesh->getOwnMDMap();
}

////////////////////////////////////////////////////////////////////////

inline
bool
Field::isOnProcessor() const
{
  return _mdMap->onSubcommunicator();
}

////////////////////////////////////////////////////////////////////////

inline
Teuchos::RCP< const Teuchos::Comm< int > >
Field::getTeuchosComm() const
{
  return _mdMap->getTeuchosComm();
}

////////////////////////////////////////////////////////////////////////

inline
int
Field::getCommDim(int axis) const
{
  return _mdMap->getCommDim(axis);
}

////////////////////////////////////////////////////////////////////////

inline
bool
Field::isPeriodic(int axis) const
{
  return _mdMap->isPeriodic(axis);
}

////////////////////////////////////////////////////////////////////////

inline
int
Field::getCommIndex(int axis) const
{
  return _mdMap->getCommIndex(axis);
}

////////////////////////////////////////////////////////////////////////

inline
int
Field::getLowerNeighbor(int axis) const
{
  return _mdMap->getLowerNeighbor(axis);
}

////////////////////////////////////////////////////////////////////////

inline
int
Field::getUpperNeighbor(int axis) const
{
  return _mdMap->getUpperNeighbor(axis);
}

////////////////////////////////////////////////////////////////////////

inline
MDVectorPtr
Field::getMDVector() const
{
  return _mdVector;
}

////////////////////////////////////////////////////////////////////////

inline
Domi::MDArrayView< const Scalar >
Field::getData() const
{
  return _mdVector->getData();
}

////////////////////////////////////////////////////////////////////////

inline
Domi::MDArrayView< Scalar >
Field::getDataNonConst()
{
  return _mdVector->getDataNonConst();
}

////////////////////////////////////////////////////////////////////////

inline
Domi::MDArrayView< Scalar >
Field::getLowerPadDataNonConst(int axis)
{
  return _mdVector->getLowerPadDataNonConst(axis);
}

////////////////////////////////////////////////////////////////////////

inline
Domi::MDArrayView< const Scalar >
Field::getLowerPadData(int axis) const
{
  return _mdVector->getLowerPadData(axis);
}

////////////////////////////////////////////////////////////////////////

inline
Domi::MDArrayView< Scalar >
Field::getUpperPadDataNonConst(int axis)
{
  return _mdVector->getUpperPadDataNonConst(axis);
}

////////////////////////////////////////////////////////////////////////

inline
Domi::MDArrayView< const Scalar >
Field::getUpperPadData(int axis) const
{
  return _mdVector->getUpperPadData(axis);
}

////////////////////////////////////////////////////////////////////////

Scalar &
Field::operator()(const Ordinal i)
{
  return _mdArrayView(i);
}

////////////////////////////////////////////////////////////////////////

Scalar &
Field::operator()(const Ordinal i, const Ordinal j)
{
#if 1
  return _mdArrayView(i,j);
#else
  return _mdArrayView.getRawPtr()[i*_mdArrayView.strides()[0]+
                                  j*_mdArrayView.strides()[1]];
#endif
}

////////////////////////////////////////////////////////////////////////

Scalar &
Field::operator()(const Ordinal i,
                  const Ordinal j,
                  const Ordinal k)
{
  return _mdArrayView(i,j,k);
}

////////////////////////////////////////////////////////////////////////

const Scalar &
Field::operator()(const Ordinal i) const
{
  return _mdArrayView(i);
}

////////////////////////////////////////////////////////////////////////

const Scalar &
Field::operator()(const Ordinal i,
                  const Ordinal j) const
{
  return _mdArrayView(i,j);
}

////////////////////////////////////////////////////////////////////////

const Scalar &
Field::operator()(const Ordinal i,
                  const Ordinal j,
                  const Ordinal k) const
{
  return _mdArrayView(i,j,k);
}

////////////////////////////////////////////////////////////////////////

inline
bool
Field::operator==(const Field & field2) const
{ 
  return (this == &field2);
}

////////////////////////////////////////////////////////////////////////

inline
void
Field::copyData(const Field & source)
{
  *_mdVector = *(source._mdVector);
}

////////////////////////////////////////////////////////////////////////

inline
void
Field::copyData(const FieldPtr & source)
{
  copyData(*source);
}

////////////////////////////////////////////////////////////////////////

inline
void
Field::updateCommPad()
{
#ifdef DGM_PARALLEL
  _mdVector->updateCommPad();
#else
  for (int axis = 0; axis < _mdVector->numDims(); ++axis)
    updateCommPad(axis);
#endif
}

////////////////////////////////////////////////////////////////////////

inline
void
Field::updateCommPad(int axis)
{
#ifdef DGM_PARALLEL
  _mdVector->updateCommPad(axis);
#else
  static int warn = 0;
  Domi::MDArrayView< Scalar > data = getDataNonConst();
  int dim = getGlobalDim(axis, true);
  int pad = getLowerPadSize(axis);

  Domi::MDArrayView< Scalar > source1 =
    Domi::MDArrayView< Scalar >(data, axis, Domi::ConcreteSlice(dim-2*pad,
                                                                dim-pad));
  Domi::MDArrayView< Scalar > source2 =
    Domi::MDArrayView< Scalar >(data, axis, Domi::ConcreteSlice(pad,2*pad));
  Domi::MDArrayView< Scalar > target1 =
    Domi::MDArrayView< Scalar >(data, axis, Domi::ConcreteSlice(0,pad));
  Domi::MDArrayView< Scalar > target2 =
    Domi::MDArrayView< Scalar >(data, axis, Domi::ConcreteSlice(dim-pad,dim));

  if (_mdVector->isPeriodic(axis))
  {
    switch(data.numDims())
    {
    case 1:
      for (int i = 0; i < source1.dimension(0); ++i)
      {
        target1(i) = source1(i);
        target2(i) = source2(i);
      }
      break;
    case 2:
      if (data.layout() == Domi::C_ORDER)
        for (int i = 0; i < source1.dimension(0); ++i)
          for (int j = 0; j < source1.dimension(1); ++j)
          {
            target1(i,j) = source1(i,j);
            target2(i,j) = source2(i,j);
          }
      else
        for (int j = 0; j < source1.dimension(1); ++j)
          for (int i = 0; i < source1.dimension(0); ++i)
          {
            target1(i,j) = source1(i,j);
            target2(i,j) = source2(i,j);
          }
      break;
    case 3:
      if (data.layout() == Domi::C_ORDER)
        for (int i = 0; i < source1.dimension(0); ++i)
          for (int j = 0; j < source1.dimension(1); ++j)
            for (int k = 0; k < source1.dimension(2); ++k)
            {
              target1(i,j,k) = source1(i,j,k);
              target2(i,j,k) = source2(i,j,k);
            }
      else
        for (int k = 0; k < source1.dimension(2); ++k)
          for (int j = 0; j < source1.dimension(1); ++j)
            for (int i = 0; i < source1.dimension(0); ++i)
            {
              target1(i,j,k) = source1(i,j,k);
              target2(i,j,k) = source2(i,j,k);
            }
      break;
    default:
      if (warn == 0)
      {
        std::cout << "*** Warning *** Field::updateCommPad(int) is using "
                  << "Domi::MDIterator, which is slow, because" << std::endl
                  << "                the number of dimensions = "
                  << data.numDims() << ". Consider upgrading "
                  << "Field::updateCommPad(int)" << std::endl
                  << "                to use nested loops for this case."
                  << std::endl;
        warn += 1;
      }
      _mdVector->updateCommPad(axis);
    }
  }
#endif
}

////////////////////////////////////////////////////////////////////////

inline
Scalar
Field::dot(const Domi::MDVector< Scalar > & a) const
{
  return _mdVector->dot(a);
}

////////////////////////////////////////////////////////////////////////

inline
Scalar
Field::dot(const Field & a) const
{
  return _mdVector->dot(*(a.getMDVector()));
}

////////////////////////////////////////////////////////////////////////

inline
Teuchos::ScalarTraits< Scalar >::magnitudeType
Field::norm1() const
{
  return _mdVector->norm1();
}

////////////////////////////////////////////////////////////////////////

inline Teuchos::ScalarTraits< Scalar >::magnitudeType
Field::norm2() const
{
  return _mdVector->norm2();
}

////////////////////////////////////////////////////////////////////////

inline
Teuchos::ScalarTraits< Scalar >::magnitudeType
Field::normInf() const
{
  return _mdVector->normInf();
}

////////////////////////////////////////////////////////////////////////

inline
Scalar
Field::meanValue() const
{
  return _mdVector->meanValue();
}

////////////////////////////////////////////////////////////////////////

inline
void
Field::putScalar(const Scalar & alpha)
{
  _mdVector->putScalar(alpha);
}

////////////////////////////////////////////////////////////////////////

inline
void
Field::randomize()
{
  _mdVector->randomize();
}

////////////////////////////////////////////////////////////////////////

inline
void
Field::add(const Field & in)
{
  typedef typename Domi::MDArrayView< Scalar       >::iterator iterator;
  typedef typename Domi::MDArrayView< const Scalar >::iterator citerator;
  static int warn = 0;
  Domi::MDArrayView< Scalar >       data   = getDataNonConst();
  Domi::MDArrayView< const Scalar > inData = in.getData();
  switch(data.numDims())
  {
  case 1:
    for (Domi::dim_type i = 0; i < data.dimension(0); ++i)
      data(i) += inData(i);
    break;
  case 2:
    if (data.layout() == Domi::C_ORDER)
      for (Domi::dim_type i = 0; i < data.dimension(0); ++i)
        for (Domi::dim_type j = 0; j < data.dimension(1); ++j)
          data(i,j) += inData(i,j);
    else
      for (Domi::dim_type j = 0; j < data.dimension(1); ++j)
        for (Domi::dim_type i = 0; i < data.dimension(0); ++i)
          data(i,j) += inData(i,j);
    break;
  case 3:
    if (data.layout() == Domi::C_ORDER)
      for (Domi::dim_type i = 0; i < data.dimension(0); ++i)
        for (Domi::dim_type j = 0; j < data.dimension(1); ++j)
          for (Domi::dim_type k = 0; k < data.dimension(2); ++k)
            data(i,j,k) += inData(i,j,k);
    else
      for (Domi::dim_type k = 0; k < data.dimension(2); ++k)
        for (Domi::dim_type j = 0; j < data.dimension(1); ++j)
          for (Domi::dim_type i = 0; i < data.dimension(0); ++i)
            data(i,j,k) += inData(i,j,k);
    break;
  default:
    if (warn == 0)
      std::cout << "*** Warning *** Field::add() is using Domi::MDIterator"
                << ", which is slow, because" << std::endl
                << "                the number of dimensions = "
                << data.numDims() << ". Consider upgrading Field::add()"
                << std::endl
                << "                to use nested loops for this case."
                << std::endl;
    warn += 1;
    citerator inIt = inData.begin();
    for (iterator it = data.begin(); it != data.end(); ++it)
      *it += *(inIt++);
    break;
  }
}

////////////////////////////////////////////////////////////////////////

inline
void
Field::scale(const Scalar & alpha)
{
  typedef typename Domi::MDArrayView< Scalar       >::iterator iterator;
  static int warn = 0;
  Domi::MDArrayView< Scalar > data = getDataNonConst();
  switch(data.numDims())
  {
  case 1:
    for (Domi::dim_type i = 0; i < data.dimension(0); ++i)
      data(i) *= alpha;
    break;
  case 2:
    if (data.layout() == Domi::C_ORDER)
      for (Domi::dim_type i = 0; i < data.dimension(0); ++i)
        for (Domi::dim_type j = 0; j < data.dimension(1); ++j)
          data(i,j) *= alpha;
    else
      for (Domi::dim_type j = 0; j < data.dimension(1); ++j)
        for (Domi::dim_type i = 0; i < data.dimension(0); ++i)
          data(i,j) *= alpha;
    break;
  case 3:
    if (data.layout() == Domi::C_ORDER)
      for (Domi::dim_type i = 0; i < data.dimension(0); ++i)
        for (Domi::dim_type j = 0; j < data.dimension(1); ++j)
          for (Domi::dim_type k = 0; k < data.dimension(2); ++k)
            data(i,j,k) *= alpha;
    else
      for (Domi::dim_type k = 0; k < data.dimension(2); ++k)
        for (Domi::dim_type j = 0; j < data.dimension(1); ++j)
          for (Domi::dim_type i = 0; i < data.dimension(0); ++i)
            data(i,j,k) *= alpha;
    break;
  default:
    if (warn == 0)
      std::cout << "*** Warning *** Field::scale() is using Domi::MDIterator"
                << ", which is slow, because" << std::endl
                << "                the number of dimensions = "
                << data.numDims() << ". Consider upgrading Field::scale()"
                << std::endl
                << "                to use nested loops for this case."
                << std::endl;
    warn += 1;
    for (iterator it = data.begin(); it != data.end(); ++it)
      *it *= alpha;
    break;
  }
}

////////////////////////////////////////////////////////////////////////

inline
void
Field::update(const Scalar & alpha,
              const Field & in,
              const Scalar & beta)
{
  typedef typename Domi::MDArrayView< Scalar       >::iterator iterator;
  typedef typename Domi::MDArrayView< const Scalar >::iterator citerator;
  static int warn = 0;
  Domi::MDArrayView< Scalar >       data   = getDataNonConst();
  Domi::MDArrayView< const Scalar > inData = in.getData();
  switch(data.numDims())
  {
  case 1:
    for (Domi::dim_type i = 0; i < data.dimension(0); ++i)
      data(i) = beta * data(i) + alpha * inData(i);
    break;
  case 2:
    if (data.layout() == Domi::C_ORDER)
      for (Domi::dim_type i = 0; i < data.dimension(0); ++i)
        for (Domi::dim_type j = 0; j < data.dimension(1); ++j)
          data(i,j) = beta * data(i,j) + alpha * inData(i,j);
    else
      for (Domi::dim_type j = 0; j < data.dimension(1); ++j)
        for (Domi::dim_type i = 0; i < data.dimension(0); ++i)
          data(i,j) = beta * data(i,j) + alpha * inData(i,j);
    break;
  case 3:
    if (data.layout() == Domi::C_ORDER)
      for (Domi::dim_type i = 0; i < data.dimension(0); ++i)
        for (Domi::dim_type j = 0; j < data.dimension(1); ++j)
          for (Domi::dim_type k = 0; k < data.dimension(2); ++k)
            data(i,j,k) = beta * data(i,j,k) + alpha * inData(i,j,k);
    else
      for (Domi::dim_type k = 0; k < data.dimension(2); ++k)
        for (Domi::dim_type j = 0; j < data.dimension(1); ++j)
          for (Domi::dim_type i = 0; i < data.dimension(0); ++i)
            data(i,j,k) = beta * data(i,j,k) + alpha * inData(i,j,k);
    break;
  default:
    if (warn == 0)
      std::cout << "*** Warning *** Field::update() is using Domi::MDIterator"
                << ", which is slow, because" << std::endl
                << "                the number of dimensions = "
                << data.numDims() << ". Consider upgrading Field::update()"
                << std::endl
                << "                to use nested loops for this case."
                << std::endl;
    warn += 1;
    citerator inIt = inData.begin();
    for (iterator it = data.begin(); it != data.end(); ++it)
      *it = beta * (*it) + alpha * (*(inIt++));
    break;
  }
}

////////////////////////////////////////////////////////////////////////

inline
void
Field::update(const Scalar & alpha1,
              const Field & in1,
              const Scalar & alpha2,
              const Field & in2,
              const Scalar & beta)
{
  typedef typename Domi::MDArrayView< Scalar       >::iterator iterator;
  typedef typename Domi::MDArrayView< const Scalar >::iterator citerator;
  static int warn = 0;
  Domi::MDArrayView< Scalar >       data    = getDataNonConst();
  Domi::MDArrayView< const Scalar > in1Data = in1.getData();
  Domi::MDArrayView< const Scalar > in2Data = in2.getData();
  switch(data.numDims())
  {
  case 1:
    for (Domi::dim_type i = 0; i < data.dimension(0); ++i)
      data(i) = beta * data(i) + alpha1 * in1Data(i) + alpha2 * in2Data(i);
    break;
  case 2:
    if (data.layout() == Domi::C_ORDER)
      for (Domi::dim_type i = 0; i < data.dimension(0); ++i)
        for (Domi::dim_type j = 0; j < data.dimension(1); ++j)
          data(i,j) = beta * data(i,j) + alpha1 * in1Data(i,j) +
                      alpha2 * in2Data(i,j);
    else
      for (Domi::dim_type j = 0; j < data.dimension(1); ++j)
        for (Domi::dim_type i = 0; i < data.dimension(0); ++i)
          data(i,j) = beta * data(i,j) + alpha1 * in1Data(i,j) +
                      alpha2 * in2Data(i,j);
    break;
  case 3:
    if (data.layout() == Domi::C_ORDER)
      for (Domi::dim_type i = 0; i < data.dimension(0); ++i)
        for (Domi::dim_type j = 0; j < data.dimension(1); ++j)
          for (Domi::dim_type k = 0; k < data.dimension(2); ++k)
            data(i,j,k) = beta * data(i,j,k) + alpha1 * in1Data(i,j,k) +
                          alpha2 * in2Data(i,j,k);
    else
      for (Domi::dim_type k = 0; k < data.dimension(2); ++k)
        for (Domi::dim_type j = 0; j < data.dimension(1); ++j)
          for (Domi::dim_type i = 0; i < data.dimension(0); ++i)
            data(i,j,k) = beta * data(i,j,k) + alpha1 * in1Data(i,j,k) +
                          alpha2 * in2Data(i,j,k);
    break;
  default:
    if (warn == 0)
      std::cout << "*** Warning *** Field::update() is using Domi::MDIterator"
                << ", which is slow, because" << std::endl
                << "                the number of dimensions = "
                << data.numDims() << ". Consider upgrading Field::update()"
                << std::endl
                << "                to use nested loops for this case."
                << std::endl;
    warn += 1;
    citerator in1It = in1Data.begin();
    citerator in2It = in2Data.begin();
    for (iterator it = data.begin(); it != data.end(); ++it)
      *it = beta * (*it) + alpha1 * (*(in1It++)) + alpha2 * (*(in2It));
    break;
  }
}

////////////////////////////////////////////////////////////////////////

inline
void
Field::setCartesianMeshPtr()
{
  // Attempt to dynamic cast _mesh from an RCP of type Mesh to an RCP
  // of type CartesiamMesh.  If this is not possible, _cMesh will be a
  // NULL RCP.
  _cMesh = Teuchos::rcp_dynamic_cast< CartesianMesh >(_mesh);
}

////////////////////////////////////////////////////////////////////////

inline
string
Field::defaultFilename() const
{
  return symbol() + ".bin";
}

////////////////////////////////////////////////////////////////////////

}  // Namespace FDM

#endif
