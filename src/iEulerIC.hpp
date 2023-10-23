#ifndef REO_IEULERIC_HPP
#define REO_IEULERIC_HPP

/** \file iEulerIC.hpp
    \brief This is a collection of classes for incompressible Euler
    initial conditions
    \author Scott Collis
*/

// system includes
#include <iostream>

// DGM includes
#include "Comm.hpp"
#include "Types.hpp"
#include "Format.hpp"

// Reo includes
#include "ReoConfig.hpp"

namespace Reo {

/// Defines a single incompressible Oseen vortex.
class iEuler::OseenVortex {
  const Scalar alpha;
  Scalar x0, y0, radius, gamma, xi;
  Scalar r2(Scalar x, Scalar y) {
    return ((x-x0)*(x-x0)+(y-y0)*(y-y0))/radius/radius;
  }
  Scalar theta(Scalar x, Scalar y) {
    return atan2( y-y0, x-x0 );
  }
  Scalar v_theta(Scalar x, Scalar y) {
    Scalar v_th;
    Scalar r = sqrt(r2(x,y));
    if (r==0) {
      v_th = 0.0;
    } else {
      v_th = gamma * ( 1.0 - exp( -alpha * r*r ) ) / ( r * xi );
    }
    return v_th;
  }
  Scalar v_r(Scalar x, Scalar y) {
    return 0.0;
  }
public:
  Scalar u(const Point &C) {
    Scalar th = theta(C.x,C.y);
    return cos(th) * v_r(C.x,C.y) - sin(th) * v_theta(C.x,C.y);
  }
  Scalar v(const Point &C) {
    Scalar th = theta(C.x,C.y);
    return sin(th) * v_r(C.x,C.y) + cos(th) * v_theta(C.x,C.y);
  }
  OseenVortex(Scalar x_0, Scalar y_0, Scalar rad, Scalar amp) :
    alpha(1.2564312086261696770)
  {
    gamma=amp;
    x0=x_0;
    y0=y_0;
    radius=rad;
    xi = 1.0 - exp(-alpha);
  }
};

} // namespace Reo

#endif   // REO_IEULERIC_HPP
