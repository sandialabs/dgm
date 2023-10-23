#ifndef FDM_KERNEL_HPP
#define FDM_KERNEL_HPP

/** \file FDM_Kernel.hpp
    \brief FDM kernel class declarations
    \author Scott Collis
    \author Bill Spotz
*/

// system includes
#include <limits>

// JSON includes
#ifdef DGM_USE_JSON
#include "json/json.h"
#endif

// FDM includes
#include "FDM_Types.hpp"
#include "FDM_Field.hpp"

namespace FDM
{

//=============================================================================
//                              K e r n e l
//=============================================================================

/// Abstract base class for spatial kernels
class Kernel
{

protected:

  Ordinal _id;          ///< Kernel ID
  Scalar  _x0;          ///< location in x
  Scalar  _y0;          ///< location in y
  Scalar  _z0;          ///< location in z
  int     _verb;        ///< verbosity level

  Teuchos::Array< InterpInfo > _interp;     ///< interpolation info
  Teuchos::Array< InterpInfo > _padInterp;  ///< interpolation info on padding

public:

  /// Constructor
  Kernel(const Ordinal id,
         const Scalar x0=0,
         const Scalar y0=0,
         const Scalar z0=0,
         const int    verb=0);

  /// Destructor
  virtual ~Kernel();

  /// Shared pointer type
  typedef Teuchos::RCP<Kernel> Ptr;

  /// Get the local size, defined as the number of interpolation
  /// points
  Ordinal local_size() const;

  /// Evaluate at a 1D point
  virtual Scalar operator()(const Scalar & x) const = 0;

  /// Evaluate at a 2D point
  virtual Scalar operator()(const Scalar & x,
                            const Scalar & y) const = 0;

  /// Evaluate at a 3D point
  virtual Scalar operator()(const Scalar & x,
                            const Scalar & y,
                            const Scalar & z) const = 0;

  /// Get the Kernel ID
  Ordinal id() const;

  /// Apply the kernel to a Field.  In practice, multiple processors
  /// can obtain a local value in this method, and then those values
  /// would have to be reduced.  Therefore, this method should not
  /// include the _padInterp interpolation points.
  virtual Scalar apply(const Field & f,
                       const Scalar factor=1.0) const = 0;

  /// Add scaled kernel to a Field.  This method alters the Field in
  /// place.  Therefore, including the _padInterp interpolation points
  /// can prevent the need for a communication padding update.
  virtual void addScaled(Field & f,
                         const Scalar amp) const = 0;

  /// Add kernel to a Field.  The Kernel implementation of this method
  /// simply calls the (Field &, const Scalar) version with the Scalar
  /// set to 1.0.
  virtual void add(Field & f) const;

  /// Return the center of the kernel
  virtual Teuchos::Array<Scalar> center() const;

protected:

  /// Split of the interpolation points that are in the padding to
  /// their own array.  Padding is determined by the MDMap of the
  /// provided Field.
  void splitOffPadInterp(const Field & f);
};

//=============================================================================
//                              D e l t a
//=============================================================================

/// Delta spatial kernel
class Delta : public Kernel
{
public:

  /// Constructor
  Delta(const Ordinal id,
        const Scalar x0=0,
        const Scalar y0=0,
        const Scalar z0=0);

  /// Destructor
  virtual ~Delta();

  /// Evaluate at a 1D point
  virtual Scalar operator()(const Scalar & x0) const;

  /// Evaluate at a 2D point
  virtual Scalar operator()(const Scalar & x0,
                            const Scalar & y0) const;

  /// Evaluate at a 3D point
  virtual Scalar operator()(const Scalar & x0,
                            const Scalar & y0,
                            const Scalar & z0) const;

  /// Apply the Delta to a field
  virtual Scalar apply(const Field & f,
                       const Scalar factor=1.0) const = 0;

  /// Evaluate on a Field
  virtual void addScaled(Field & f,
                         const Scalar value) const = 0;
};

//=============================================================================
//                            D e l t a 1 d
//=============================================================================

/// Delta spatial kernel
class Delta1d : public Delta
{
public:

  /// Constructor
  Delta1d(const Ordinal id,
          const Field & f,
          const Scalar x0);

  /// Destructor
  ~Delta1d();

  /// Evaluate at a 1D point
  virtual Scalar operator()(const Scalar & x0) const;

  /// Apply the 1D Delta to a Field
  virtual Scalar apply(const Field & f,
                       const Scalar factor=1.0) const;

  /// Evaluate on a Field
  virtual void addScaled(Field & f,
                         const Scalar value) const;
};

//=============================================================================
//                            D e l t a 2 d
//=============================================================================

/// Delta spatial kernel
class Delta2d : public Delta
{
public:

  /// Constructor
  Delta2d(const Ordinal id,
          const Field & f,
          const Scalar x0,
          const Scalar y0);

  /// Destructor
  ~Delta2d();

  /// Evaluate at a 2D point
  virtual Scalar operator()(const Scalar & x0,
                            const Scalar & y0) const;

  /// Apply a 2D Delta to a Field
  virtual Scalar apply(const Field & f,
                       const Scalar factor=1.0) const;

  /// Evaluate on a Field
  virtual void addScaled(Field & f,
                         const Scalar value) const;
};

//=============================================================================
//                            D e l t a 3 d
//=============================================================================

/// Delta spatial kernel
class Delta3d : public Delta
{
public:

  /// 3D Constructor
  Delta3d(const Ordinal id,
          const Field & f,
          const Scalar x0,
          const Scalar y0,
          const Scalar z0);

  /// Destructor
  ~Delta3d();

  /// Evaluate at a 3D point
  virtual Scalar operator()(const Scalar & x0,
                            const Scalar & y0,
                            const Scalar & z0) const;

  virtual Scalar apply(const Field & f,
                       const Scalar factor=1.0) const;

  /// Evaluate on a Field
  virtual void addScaled(Field & f,
                         const Scalar value) const;
};

//=============================================================================
//                           G a u s s i a n
//=============================================================================

/// Gaussian spatial kernel
class Gaussian : public Kernel
{
protected:
  static const int NSIGMA = 5;    ///< default number of std dev.
  const Scalar _sigma;            ///< Standard deviation, \f$\sigma\f$
  const Scalar _twos2i;           ///< \f$ 1/(2\sigma^2)\f$
  const Scalar _sr2pi;            ///< \f$ 1/(\sigma \sqrt{2\pi}) \f$
  const Scalar _numStdDev;        ///< number of standard deviations

public:

  /// Constructor
  Gaussian(const Ordinal id,
           const Scalar sigma,
           const Scalar x0,
           const Scalar y0,
           const Scalar z0,
           const Scalar numStdDev=NSIGMA);

  /// Destructor
  ~Gaussian();

  /// Evaluate at a 1D point
  virtual Scalar operator()(const Scalar & x) const;

  /// Evaluate at a 2D point
  virtual Scalar operator()(const Scalar & x,
                            const Scalar & y) const;

  /// Evaluate at a 3D point
  virtual Scalar operator()(const Scalar & x,
                            const Scalar & y,
                            const Scalar & z) const;

  /// Apply the kernel to a Field
  virtual Scalar apply(const Field & f,
                       const Scalar factor=1.0) const = 0;

  /// Add scaled kernel to a Field
  virtual void addScaled(Field & f,
                         const Scalar value) const = 0;

  /// Determine if a point is near the kernel
  virtual bool within_distance(const Teuchos::ArrayView<Scalar> & coords,
                               const Teuchos::ArrayView<Scalar> & centroid,
                               const Scalar distance);

protected:
  static Scalar Exp(const Scalar arg);
};

//=============================================================================
//                         G a u s s i a n 1 d
//=============================================================================

/// Gaussian 1d kernel
class Gaussian1d : public Gaussian
{

public:
  /// Constructor
  Gaussian1d(const Ordinal id,
             const Field & f,
             const Scalar sigma,
             const Scalar x0,
             const Scalar numStdDev=NSIGMA);

  /// Array constructor
  Gaussian1d(const Ordinal id,
             const Field & f,
             const Scalar sigma,
             const Teuchos::ArrayView<Scalar> &x,
             const Scalar numStdDev=NSIGMA);

  /// Destructor
  ~Gaussian1d();

  /// Evaluate at a point
  virtual Scalar operator()(const Scalar & x) const;

  /// Apply the kernel to a Field
  virtual Scalar apply(const Field & f,
                       const Scalar factor=1.0) const;

  /// Add scaled kernel to a Field
  virtual void addScaled(Field & f,
                         const Scalar value) const;

  /// Return the center of the kernel
  virtual Teuchos::Array<Scalar> center() const;
};

//=============================================================================
//                         G a u s s i a n 2 d
//=============================================================================

/// Gaussian 2d spatial kernel
class Gaussian2d : public Gaussian
{
  const Scalar _sr2pi2;

public:
  /// Constructor
  Gaussian2d(const Ordinal id,
             const Field & f,
             const Scalar sigma,
             const Scalar x0,
             const Scalar y0,
             const Scalar numStdDev=NSIGMA);

  /// Array constructor
  Gaussian2d(const Ordinal id,
             const Field & f,
             const Scalar sigma,
             const Teuchos::ArrayView<Scalar> & c,
             const Scalar numStdDev=NSIGMA);

  /// Destructor
  ~Gaussian2d();

  /// Evaluate at a point
  virtual Scalar operator()(const Scalar & x,
                            const Scalar & y) const;

  /// Apply the kernel to a Field
  virtual Scalar apply(const Field & f,
                       const Scalar factor=1.0) const;

  /// Add scaled kernel to a Field
  virtual void addScaled(Field & f,
                         const Scalar value) const;

  /// Return the center of the kernel
  virtual Teuchos::Array<Scalar> center() const;
};

//=============================================================================
//                         G a u s s i a n 3 d
//=============================================================================

/// Gaussian 3d spatial kernel
class Gaussian3d : public Gaussian
{
  const Scalar _sr2pi3;

public:
  /// Constructor
  Gaussian3d(const Ordinal id,
             const Field & f,
             const Scalar sigma,
             const Scalar x0,
             const Scalar y0,
             const Scalar z0,
             const Scalar numStdDev=NSIGMA);

  /// Array Constructor
  Gaussian3d(const Ordinal id,
             const Field & f,
             const Scalar sigma,
             const Teuchos::ArrayView<Scalar> & c,
             const Scalar numStdDev=NSIGMA);

  /// Destructor
  ~Gaussian3d();

  /// Evaluate at a point
  virtual Scalar operator()(const Scalar & x,
                            const Scalar & y,
                            const Scalar & z) const;

  /// Apply the kernel to a Field
  virtual Scalar apply(const Field & f,
                       const Scalar factor=1.0) const;

  /// Add scaled kernel to a Field
  virtual void addScaled(Field & f,
                         const Scalar value) const;
};

}  // namespace FDM

#endif // FDM_KERNEL_HPP
