/** \file FDM_Kernel.cpp
    \brief FDM kernel class implementations
    \author Scott Collis
    \author Bill Spotz
*/

// FDM includes
#include "FDM_Kernel.hpp"

namespace FDM
{

/// Constructor
Kernel::Kernel(const Ordinal id,
               const Scalar x0,
               const Scalar y0,
               const Scalar z0,
               const int    verb) :
  _id(id),
  _x0(x0),
  _y0(y0),
  _z0(z0),
  _verb(verb),
  _interp(),
  _padInterp()
{
}

/// Destructor
Kernel::~Kernel()
{
}

/// Get the local size, defined as the number of interpolation points
Ordinal Kernel::local_size() const
{
  //return boost::numeric_cast<Ordinal>(_interp.size() + _padInterp.size());
  return (Ordinal)(_interp.size() + _padInterp.size());
}

/// Get the Kernel ID
Ordinal Kernel::id() const
{
  return _id;
}

/// Add kernel to a Field
void Kernel::add(Field & f) const
{
  addScaled(f,1.0);
}

/// Return the center of the kernel
Teuchos::Array<Scalar> Kernel::center() const
{
  Teuchos::Array<Scalar> centroid(3);
  centroid[0] = _x0;
  centroid[1] = _y0;
  centroid[2] = _z0;
  return centroid;
}

/// Split of the interpolation points that are in the padding to their
/// own array.  Padding is determined by the MDMap of the provided
/// Field.
void Kernel::splitOffPadInterp(const Field & f)
{
  Teuchos::Array< InterpInfo >::iterator it = _interp.begin();
  while(it != _interp.end())
  {
    // Check each axis to see if we are in the padding
    bool inPad = false;
    for (int axis = 0; axis < it->index.size(); ++axis)
      if (it->index[axis] < 0 || it->index[axis] >= f.getLocalDim(axis, false))
        inPad = true;
    if (inPad)
    {
      // Copy this InterpInfo to _padInterp
      _padInterp.append(*it);
      // Remove this InterpInfo from _interp
      it = _interp.erase(it);
    }
    else
    {
      ++it;
    }
  }
}

//=============================================================================

/// Constructor
Delta::Delta(const Ordinal id,
             const Scalar x0,
             const Scalar y0,
             const Scalar z0) :
  Kernel(id,x0,y0,z0)
{
}

/// Destructor
Delta::~Delta()
{
}

/// Evaluate at a 1D point
Scalar Delta::operator()(const Scalar & x0) const
{
  FDM_UNDEFINED;
  return 0;
}

/// Evaluate at a 2D point
Scalar Delta::operator()(const Scalar & x0,
                          const Scalar & y0) const
{
  FDM_UNDEFINED;
  return 0;
}

/// Evaluate at a 3D point
Scalar Delta::operator()(const Scalar & x0,
                         const Scalar & y0,
                         const Scalar & z0) const
{
  FDM_UNDEFINED;
  return 0;
}

//=============================================================================

/// Constructor
Delta1d::Delta1d(const Ordinal id,
                 const Field & f,
                 const Scalar x0) :
  Delta(id,x0)
{
  if (_verb)
    cout << "Building Delta at coordinate {" << x0 << "}" << endl;
  // Compute the interpolation information.
  f.getInterpInfo(x0, _interp, false);
  splitOffPadInterp(f);
}

/// Destructor
Delta1d::~Delta1d()
{
}

/// Evaluate at a 1D point
Scalar Delta1d::operator()(const Scalar & x0) const
{
  if (x0 == _x0) return 1.0;
  return 0.0;
}

/// Apply the 1D Delta to a Field
Scalar Delta1d::apply(const Field & f,
                      const Scalar factor) const
{
  Scalar result = 0.0;
  Teuchos::Array< InterpInfo >::const_iterator it;
  for (it = _interp.begin(); it != _interp.end(); ++it)
    result += f(it->index[0]) * factor * it->weight;
  return result;
}

/// Evaluate on a Field
void Delta1d::addScaled(Field & f,
                        const Scalar value) const
{
  Teuchos::Array< InterpInfo >::const_iterator it;
  for (it = _interp.begin(); it != _interp.end(); ++it)
    f(it->index[0]) -= value * it->weight;
  for (it = _padInterp.begin(); it != _padInterp.end(); ++it)
    f(it->index[0]) -= value * it->weight;
}

//=============================================================================

/// Constructor
Delta2d::Delta2d(const Ordinal id,
                 const Field & f,
                 const Scalar x0,
                 const Scalar y0) :
  Delta(id,x0,y0)
{
  if (_verb)
    cout << "Building Delta at coordinates " << Teuchos::tuple(x0,y0) << endl;
  // Compute the interpolation information.
  f.getInterpInfo(x0, y0, _interp, false);
  splitOffPadInterp(f);
}

/// Destructor
Delta2d::~Delta2d()
{
}

/// Evaluate at a 2D point
Scalar Delta2d::operator()(const Scalar & x0,
                           const Scalar & y0) const
{
  if (x0 == _x0 && y0 == _y0) return 1.0;
  return 0.0;
}

/// Apply a 2D Delta to a Field
Scalar Delta2d::apply(const Field & f,
                      const Scalar factor) const
{
  Scalar result = 0.0;
  Teuchos::Array< InterpInfo >::const_iterator it;
  for (it = _interp.begin(); it != _interp.end(); ++it)
    result += f(it->index[0], it->index[1]) * factor * it->weight;
  return result;
}

/// Evaluate on a Field
void Delta2d::addScaled(Field & f,
                        const Scalar value) const
{
  Teuchos::Array< InterpInfo >::const_iterator it;
  for (it = _interp.begin(); it != _interp.end(); ++it)
    f(it->index[0], it->index[1]) -= value * it->weight;
  for (it = _padInterp.begin(); it != _padInterp.end(); ++it)
    f(it->index[0], it->index[1]) -= value * it->weight;
}

//=============================================================================

/// 3D Constructor
Delta3d::Delta3d(const Ordinal id,
                 const Field & f,
                 const Scalar x0,
                 const Scalar y0,
                 const Scalar z0) :
  Delta(id,x0,y0,z0)
{
  if (_verb)
    cout << "Building Delta at coordinates " << Teuchos::tuple(x0,y0,z0)
         << endl;
  // Compute the interpolation information.
  f.getInterpInfo(x0, y0, z0, _interp, false);
  splitOffPadInterp(f);
}

/// Destructor
Delta3d::~Delta3d()
{
}

/// Evaluate at a 3D point
Scalar Delta3d::operator()(const Scalar & x0,
                           const Scalar & y0,
                           const Scalar & z0) const
{
  if (x0 == _x0 && y0 == _y0 && z0 == _z0) return 1.0;
  return 0.0;
}

Scalar Delta3d::apply(const Field & f,
                      const Scalar factor) const
{
  Scalar result = 0.0;
  Teuchos::Array< InterpInfo >::const_iterator it;
  for (it = _interp.begin(); it != _interp.end(); ++it)
    result += f(it->index[0], it->index[1], it->index[2]) * factor *
      it->weight;
  return result;
}

/// Evaluate on a Field
void Delta3d::addScaled(Field & f,
                        const Scalar value) const
{
  Teuchos::Array< InterpInfo >::const_iterator it;
  for (it = _interp.begin(); it != _interp.end(); ++it)
    f(it->index[0], it->index[1], it->index[2]) -= value * it->weight;
  for (it = _padInterp.begin(); it != _padInterp.end(); ++it)
    f(it->index[0], it->index[1], it->index[2]) -= value * it->weight;
}

//=============================================================================

// Constructor
Gaussian::Gaussian(const Ordinal id,
                   const Scalar sigma,
                   const Scalar x0,
                   const Scalar y0,
                   const Scalar z0,
                   const Scalar numStdDev) :
  Kernel(id,x0,y0,z0),
  _sigma(sigma),
  _twos2i(1.0/(2.0*pow(_sigma,2))),
  _sr2pi(1.0/(_sigma*sqrt(2.0*Teuchos::Utils::pi()))),
  _numStdDev(numStdDev)
{
}

/// Destructor
Gaussian::~Gaussian()
{
}

// Default operator()
Scalar Gaussian::operator()(const Scalar & x) const
{
  FDM_UNDEFINED;
  return 0.0;
}

Scalar Gaussian::operator()(const Scalar & x,
                            const Scalar & y) const
{
  FDM_UNDEFINED;
  return 0.0;
}

Scalar Gaussian::operator()(const Scalar & x,
                            const Scalar & y,
                            const Scalar & z) const
{
  FDM_UNDEFINED;
  return 0.0;
}

/// Determine if a point is near the kernel
bool Gaussian::within_distance(const Teuchos::ArrayView<Scalar> & coords,
                               const Teuchos::ArrayView<Scalar> & centroid,
                               const Scalar distance)
{
  Scalar d = pow(coords[0] - centroid[0], 2);
  if (1 < centroid.size()) d += pow(coords[1] - centroid[1], 2);
  if (2 < centroid.size()) d += pow(coords[2] - centroid[2], 2);
  const bool t = (d < pow(distance,2));
  return t;
}

Scalar Gaussian::Exp(const Scalar arg)
{
  return ( arg > -34.0 ? exp(arg) : 1.0e-15 );
}

//=============================================================================

/// Constructor
Gaussian1d::Gaussian1d(const Ordinal id,
                       const Field & f,
                       const Scalar sigma,
                       const Scalar x0,
                       const Scalar numStdDev) :
  Gaussian(id,sigma,x0,0,0,numStdDev)
{
  Ordinal imin = -1 * f.getCommPadSize(0);
  Ordinal imax = f.getLocalDim(0);
  Scalar  distance = _numStdDev * _sigma;
  Scalar  xlo  = f.getCoordinateAtPoint(0,imin);
  Scalar  xhi  = f.getCoordinateAtPoint(0,imax-1);
  Scalar  xmin = x0 - distance;
  Scalar  xmax = x0 + distance;
  if      (xmin >= xlo && xmin < xhi) imin = f.nearestIndex(0, xmin, true);
  else if (xmin >= xhi)               imin = imax;
  if      (xmax < xlo)                imax = imin;
  else if (xmax >= xlo && xmax < xhi) imax = f.nearestIndex(0, xmax, true);
  _interp.clear();
  _padInterp.clear();
  for (Ordinal i = imin; i < imax; ++i)
  {
    Scalar x = f.getCoordinateAtPoint(i);
    _interp.push_back(InterpInfo(i, operator()(x)));
  }
  splitOffPadInterp(f);
}

/// Array constructor
Gaussian1d::Gaussian1d(const Ordinal id,
                       const Field & f,
                       const Scalar sigma,
                       const Teuchos::ArrayView<Scalar> &x,
                       const Scalar numStdDev) :
  Gaussian(id,sigma,x[0],0,0,numStdDev)
{
}

/// Destructor
Gaussian1d::~Gaussian1d()
{
}

/// Evaluate at a point
Scalar Gaussian1d::operator()(const Scalar & x) const
{
  return _sr2pi*Exp(-(pow(x-_x0,2))*_twos2i);
}

/// Apply the kernel to a Field
Scalar Gaussian1d::apply(const Field & f,
                         const Scalar factor) const
{
  Scalar result = 0.0;
  Teuchos::Array< InterpInfo >::const_iterator it;
  for (it = _interp.begin(); it != _interp.end(); ++it)
    result += f(it->index[0]) * factor * it->weight;
  return result;
}

/// Add scaled kernel to a Field
void Gaussian1d::addScaled(Field & f,
                           const Scalar value) const
{
  Teuchos::Array< InterpInfo >::const_iterator it;
  for (it = _interp.begin(); it != _interp.end(); ++it)
    f(it->index[0]) -= value * it->weight;
  for (it = _padInterp.begin(); it != _padInterp.end(); ++it)
    f(it->index[0]) -= value * it->weight;
}

/// Return the center of the kernel
Teuchos::Array<Scalar> Gaussian1d::center() const
{
  Teuchos::Array<Scalar> centroid(1);
  centroid[0] = _x0;
  return centroid;
}

//=============================================================================

/// Constructor
Gaussian2d::Gaussian2d(const Ordinal id,
                       const Field & f,
                       const Scalar sigma,
                       const Scalar x0,
                       const Scalar y0,
                       const Scalar numStdDev) :
  Gaussian(id,sigma, x0, y0, 0, numStdDev),
  _sr2pi2(pow(_sr2pi,2))
{
  Ordinal imin = -1 * f.getCommPadSize(0);
  Ordinal jmin = -1 * f.getCommPadSize(1);
  Ordinal imax = f.getLocalDim(0);
  Ordinal jmax = f.getLocalDim(1);
  Scalar  distance = _numStdDev * _sigma;
  Scalar  xlo  = f.getCoordinateAtPoint(0,imin);
  Scalar  ylo  = f.getCoordinateAtPoint(1,jmin);
  Scalar  xhi  = f.getCoordinateAtPoint(0,imax-1);
  Scalar  yhi  = f.getCoordinateAtPoint(1,jmax-1);
  Scalar  xmin = x0 - distance;
  Scalar  ymin = y0 - distance;
  Scalar  xmax = x0 + distance;
  Scalar  ymax = y0 + distance;
  if      (xmin >= xlo && xmin < xhi) imin = f.nearestIndex(0, xmin, true);
  else if (xmin >= xhi)               imin = imax;
  if      (ymin >= ylo && ymin < yhi) jmin = f.nearestIndex(1, ymin, true);
  else if (ymin >= yhi)               jmin = jmax;
  if      (xmax < xlo)                imax = imin;
  else if (xmax >= xlo && xmax < xhi) imax = f.nearestIndex(0, xmax, true);
  if      (ymax < ylo)                jmax = jmin;
  else if (ymax >= ylo && ymax < yhi) jmax = f.nearestIndex(1, ymax, true);
  _interp.clear();
  _padInterp.clear();
  Scalar tol = 1e-12;
  for (Ordinal j = jmin; j < jmax; ++j)
  {
    Scalar y = f.getCoordinateAtPoint(j,1);
    for (Ordinal i = imin; i < imax; ++i)
    {
      Scalar x = f.getCoordinateAtPoint(i,0);
      InterpInfo ii(i, j, operator()(x, y));
      if (ii.weight > tol) _interp.push_back(ii);
    }
  }
  splitOffPadInterp(f);
}

/// Array constructor
Gaussian2d::Gaussian2d(const Ordinal id,
                       const Field & f,
                       const Scalar sigma,
                       const Teuchos::ArrayView<Scalar> & c,
                       const Scalar numStdDev) :
  Gaussian(id, sigma, c[0], c[1], 0, numStdDev),
  _sr2pi2(pow(_sr2pi,2))
{
}

/// Destructor
Gaussian2d::~Gaussian2d()
{
}

/// Evaluate at a point
Scalar Gaussian2d::operator()(const Scalar & x,
                              const Scalar & y) const
{
  return _sr2pi2*Exp(-(pow(x-_x0,2)+pow(y-_y0,2))*_twos2i);
}

/// Apply the kernel to a Field
Scalar Gaussian2d::apply(const Field & f,
                         const Scalar factor) const
{
  Scalar result = 0.0;
  Teuchos::Array< InterpInfo >::const_iterator it;
  for (it = _interp.begin(); it != _interp.end(); ++it)
    result += f(it->index[0], it->index[1]) * factor * it->weight;
  return result;
}

/// Add scaled kernel to a Field
void Gaussian2d::addScaled(Field & f,
                           const Scalar value) const
{
  Teuchos::Array< InterpInfo >::const_iterator it;
  for (it = _interp.begin(); it != _interp.end(); ++it)
    f(it->index[0], it->index[1]) -= value * it->weight;
  for (it = _padInterp.begin(); it != _padInterp.end(); ++it)
    f(it->index[0], it->index[1]) -= value * it->weight;
}

/// Return the center of the kernel
Teuchos::Array<Scalar> Gaussian2d::center() const
{
  Teuchos::Array<Scalar> centroid(2);
  centroid[0] = _x0;
  centroid[1] = _y0;
  return centroid;
}

//=============================================================================

/// Constructor
Gaussian3d::Gaussian3d(const Ordinal id,
                       const Field & f,
                       const Scalar sigma,
                       const Scalar x0,
                       const Scalar y0,
                       const Scalar z0,
                       const Scalar numStdDev) :
  Gaussian(id, sigma, x0, y0, z0, numStdDev),
  _sr2pi3(pow(_sr2pi,3))
{
  Ordinal imin = -1 * f.getCommPadSize(0);
  Ordinal jmin = -1 * f.getCommPadSize(1);
  Ordinal kmin = -1 * f.getCommPadSize(2);
  Ordinal imax = f.getLocalDim(0);
  Ordinal jmax = f.getLocalDim(1);
  Ordinal kmax = f.getLocalDim(2);
  Scalar  distance = _numStdDev * _sigma;
  Scalar  xlo  = f.getCoordinateAtPoint(0,imin);
  Scalar  ylo  = f.getCoordinateAtPoint(1,jmin);
  Scalar  zlo  = f.getCoordinateAtPoint(2,kmin);
  Scalar  xhi  = f.getCoordinateAtPoint(0,imax-1);
  Scalar  yhi  = f.getCoordinateAtPoint(1,jmax-1);
  Scalar  zhi  = f.getCoordinateAtPoint(2,kmax-1);
  Scalar  xmin = x0 - distance;
  Scalar  ymin = y0 - distance;
  Scalar  zmin = z0 - distance;
  Scalar  xmax = x0 + distance;
  Scalar  ymax = y0 + distance;
  Scalar  zmax = z0 + distance;
  if      (xmin >= xlo && xmin < xhi) imin = f.nearestIndex(0, xmin, true);
  else if (xmin >= xhi)               imin = imax;
  if      (ymin >= ylo && ymin < yhi) jmin = f.nearestIndex(1, ymin, true);
  else if (ymin >= yhi)               jmin = jmax;
  if      (zmin >= zlo && zmin < zhi) kmin = f.nearestIndex(2, zmin, true);
  else if (zmin >= zhi)               kmin = kmax;
  if      (xmax < xlo)                imax = imin;
  else if (xmax >= xlo && xmax < xhi) imax = f.nearestIndex(0, xmax, true);
  if      (ymax < ylo)                jmax = jmin;
  else if (ymax >= ylo && ymax < yhi) jmax = f.nearestIndex(1, ymax, true);
  if      (zmax < zlo)                kmax = kmin;
  else if (zmax >= zlo && zmax < zhi) kmax = f.nearestIndex(2, zmax, true);
  _interp.clear();
  _padInterp.clear();
  Scalar tol = 1e-12;
  for (Ordinal k = kmin; k < kmax; ++k)
  {
    Scalar z = f.getCoordinateAtPoint(k,2);
    for (Ordinal j = jmin; j < jmax; ++j)
    {
      Scalar y = f.getCoordinateAtPoint(j,1);
      for (Ordinal i = imin; i < imax; ++i)
      {
        Scalar x = f.getCoordinateAtPoint(i,0);
        InterpInfo ii(i, j, k, operator()(x, y, z));
        if (ii.weight > tol) _interp.push_back(ii);
      }
    }
  }
  splitOffPadInterp(f);
}

/// Array Constructor
Gaussian3d::Gaussian3d(const Ordinal id,
                       const Field & f,
                       const Scalar sigma,
                       const Teuchos::ArrayView<Scalar> & c,
                       const Scalar numStdDev) :
  Gaussian(id, sigma, c[0], c[1], c[2], numStdDev),
  _sr2pi3(pow(_sr2pi,3))
{
}

/// Destructor
Gaussian3d::~Gaussian3d()
{
}

/// Evaluate at a point
Scalar Gaussian3d::operator()(const Scalar & x,
                              const Scalar & y,
                              const Scalar & z) const
{
  return _sr2pi3*Exp(-(pow(x-_x0,2) +
                      pow(y-_y0,2) +
                      pow(z-_z0,2)  ) * _twos2i);
}

/// Apply the kernel to a Field
Scalar Gaussian3d::apply(const Field & f,
                         const Scalar factor) const
{
  Scalar result = 0.0;
  Teuchos::Array< InterpInfo >::const_iterator it;
  for (it = _interp.begin(); it != _interp.end(); ++it)
    result += f(it->index[0], it->index[1], it->index[2]) * factor *
      it->weight;
  return result;
}

/// Add scaled kernel to a Field
void Gaussian3d::addScaled(Field & f,
                           const Scalar value) const
{
  Teuchos::Array< InterpInfo >::const_iterator it;
  for (it = _interp.begin(); it != _interp.end(); ++it)
    f(it->index[0], it->index[1], it->index[2]) -= value * it->weight;
  for (it = _padInterp.begin(); it != _padInterp.end(); ++it)
    f(it->index[0], it->index[1], it->index[2]) -= value * it->weight;
}

}  // namespace FDM
