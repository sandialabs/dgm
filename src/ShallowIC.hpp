#ifndef DGM_REMOVE_FOR_RELEASE

#ifndef REO_SHALLOWIC_HPP
#define REO_SHALLOWIC_HPP

/** \file ShallowIC.hpp
    \brief This is a collection of classes for Shallow water initial conditions
    \author Vincent Mousseau
    \author S. Scott Collis
*/

// system includes
#include <iostream>

// local includes
#include "Comm.hpp"
#include "Types.hpp"
#include "Format.hpp"
#include "Coordinates.hpp"
using namespace DGM;

/// define this to use Sacado AD (as long as Trilinos is active)
#ifndef DGM_USE_KOKKOS
#define REO_SHALLOW_USE_AD
#endif

// Trilinos includes
#if defined(DGM_USE_EPETRA) && defined(REO_SHALLOW_USE_AD)
#include "Sacado.hpp"
#endif

namespace Reo {

/// Defines a 2-D shallow water bore problem (equivalent to a shock tube)
class Bore {

  const int verb;     ///< Verbosity level

  /// Geopotential
  Scalar Geopotential(const Point &C) const {
    Scalar grav = Gravity(C);
    Scalar eval = Eta(C);
    Scalar hval = Height(C);
    Scalar gpval = grav * (eval + hval);
    return gpval;
  }

  /// Eta
  Scalar Eta(const Point &C) const {
    Scalar eval;
    Scalar elt = 0.01;
    Scalar elb = 0.01;
    Scalar ert = 0.01;
    Scalar erb = 0.01;
    Scalar xval = C.x;
    Scalar yval = C.y;
    Scalar eps = -1.0e-18;
    if (xval < eps){
      if (yval < eps){
        eval = elb;
      } else {
        eval = elt;
      }
    } else {
      if (yval < eps){
        eval = erb;
      } else {
        eval = ert;
      }
    }
    return eval;
  }

  /// Templated bottom function so that we can use AD on it
  template <typename ScalarT>
  ScalarT bottom(const ScalarT &x, const ScalarT &y) const {
//#if 1
//#ifdef REO_SHALLOW_LINEAR_BOTTOM
    const ScalarT dhdx = 2.375;
    const ScalarT dhdy = 2.375;
    const ScalarT x0 = 0.0;
    const ScalarT y0 = 0.0;
    const ScalarT h0 = 20.0;
    return h0 + dhdx*(x-x0) + dhdy*(y-y0);
//#else
//    const ScalarT h0 = 20.0;
//    return h0 + 0.10*h0*sin(2.0*pi/4.0*x);
//#endif
  }

  /// Sloping Bottom
  Scalar Bottom(const Scalar xval, const Scalar yval) const {
#if defined(DGM_USE_EPETRA) && defined(REO_SHALLOW_USE_AD)
    return bottom(xval,yval);
#else
    const Scalar dhdx = 2.375;
    const Scalar dhdy = 2.375;
    //Scalar dhdx = 0.000;
    //Scalar dhdy = 0.000;
    const Scalar xnot = 0.0;
    const Scalar ynot = 0.0;
    const Scalar hnot = 20.0;
    const Scalar hval = hnot + ( dhdx * (xval - xnot) )
                             + ( dhdy * (yval - ynot) );
    return hval;
#endif
  }

  /// Height
  Scalar Height(const Point &C) const {
    return 20.0;
//    Scalar hval;
//    Scalar xval = C.x;
//    Scalar yval = C.y;
//    hval = Bottom(xval,yval);
//    return hval;
  }

  /// DhDx
  /** \note Need to use SFad instead of DFad for performance. */
  Scalar DhDx(const Point &C) const {
#if defined(DGM_USE_EPETRA) && defined(REO_SHALLOW_USE_AD)
    const Scalar x = C.x;
    const Scalar y = C.y;
    const int num_deriv = 2;
    Sacado::Fad::SFad<Scalar,2> xfad(num_deriv, 0, x); // First (0) indep. var
    Sacado::Fad::SFad<Scalar,2> yfad(num_deriv, 1, y); // Second (1) indep. var
    Sacado::Fad::SFad<Scalar,2> hfad;                  // Result

    // compute function and derivative with AD
    hfad = bottom(xfad, yfad);

    // extract value and derivatives
    //const Scalar h = hfad.val();
    const Scalar dhdx = hfad.dx(0);
    //const Scalar dhdy = hfad.dx(1);
    //if (verb) cout << "dhdx = " << dhdx << endl;
    return dhdx;
#else
//    Scalar hm, hp, dhdx;
//    Scalar xval = C.x;
//    Scalar yval = C.y;
//    Scalar eps = fabs(1.0e-8 * xval) + 1.0e-12;
//    Scalar xpval = xval + eps;
//    Scalar xmval = xval - eps;
//    hp = Bottom(xpval,yval);
//    hm = Bottom(xmval,yval);
//    if (fabs(hp - hm) < 1.0e-32) {
//      dhdx = 0.0;
//    } else {
//      dhdx = (hp - hm) / (2.0 * eps);
//    }
//    //if (verb) cout << "dhdx = " << dhdx << endl;
//    return dhdx;
    return 0.0;
#endif
  }

  /// DhDy
  /** \note Need to use SFad instead of DFad for performance. */
  Scalar DhDy(const Point &C) const {
#if defined(DGM_USE_EPETRA) && defined(REO_SHALLOW_USE_AD)
    const Scalar x = C.x;
    const Scalar y = C.y;
    const int num_deriv = 2;
    Sacado::Fad::SFad<Scalar,2> xfad(num_deriv, 0, x); // First (0) indep. var
    Sacado::Fad::SFad<Scalar,2> yfad(num_deriv, 1, y); // Second (1) indep. var
    Sacado::Fad::SFad<Scalar,2> hfad;                  // Result

    // compute function and derivative with AD
    hfad = bottom(xfad, yfad);

    // extract value and derivatives
    //const Scalar h = hfad.val();
    //const Scalar dhdx = hfad.dx(0);
    const Scalar dhdy = hfad.dx(1);
    //if (verb) cout << "dhdy = " << dhdy << endl;
    return dhdy;
#else
//    Scalar hm, hp, dhdy;
//    Scalar xval = C.x;
//    Scalar yval = C.y;
//    Scalar eps = fabs(1.0e-8 * yval) + 1.0e-12;
//    Scalar ypval = yval + eps;
//    Scalar ymval = yval - eps;
//    hp = Bottom(xval,ypval);
//    hm = Bottom(xval,ymval);
//    if (fabs(hp - hm) < 1.0e-32) {
//      dhdy = 0.0;
//    } else {
//      dhdy = (hp - hm) / (2.0 *eps);
//    }
//    //if (verb) cout << "dhdy = " << dhdy << endl;
//    return dhdy;
    return 0.0;
#endif
  }

  /// X-velocity
  inline Scalar XVel(const Point &C) const {
    return 0.0;
  }

  /// Y-velocity
  inline Scalar YVel(const Point &C) const {
    return 0.0;
  }

  // Gravity
  inline Scalar Gravity(const Point &C) const {
    return 9.8;
  }

public:

  /// Shock Tube Initial Condition Function
  Bore() : verb(DGM::Comm::World->verbosity()) { }

  /// \name Interface
  //@{
  inline Scalar PHI(const Point &C) const { return Geopotential(C); }
  inline Scalar UPHI(const Point &C) const { return Geopotential(C)*XVel(C); }
  inline Scalar VPHI(const Point &C) const { return Geopotential(C)*YVel(C); }
  inline Scalar DHDX(const Point &C) const { return DhDx(C); }
  inline Scalar DHDY(const Point &C) const { return DhDy(C); }
  inline Scalar G(const Point &C) const { return Gravity(C); }
  inline Scalar h(const Point &C) const { return Height(C); }
  //@}
};

//===============================================================================
//      Initialize to mms solution
//===============================================================================

class MMSInitialCondition {

  // no member data, only methods

public:

  /// Shock Tube Initial Condition Function
  MMSInitialCondition(){ }

  /// \name Interface
  //@{
  inline Scalar PHI(const Point &C) const { return (49.0*std::sin(3.141592654/2.0)*std::cos(C.x)*std::sin(C.y))/5.0 + 539.0/5.0; }
  inline Scalar UPHI(const Point &C) const { return (49.0*C.x*C.y*(std::sin(3.141592654/2.0)*std::cos(C.x)*std::sin(C.y) + 11.0))/(20.0*3.141592654*3.141592654); }
  inline Scalar VPHI(const Point &C) const { return -1.0*(49.0*C.x*C.y*(std::sin(3.141592654/2.0)*std::cos(C.x)*std::sin(C.y) + 11.0))/(20.0*3.141592654*3.141592654); }
  inline Scalar DHDX(const Point &C) const { return -std::sin(3.141592654/2.0)*std::sin(C.x)*std::sin(C.y); }
  inline Scalar DHDY(const Point &C) const { return std::sin(3.141592654/2.0)*std::cos(C.x)*std::cos(C.y); }
  inline Scalar G(const Point &C) const { return 9.8; }
  inline Scalar h(const Point &C) const { return std::sin(3.141592654/2.0)*std::cos(C.x)*std::sin(C.y) + 10.0; }
  //@}
};

//===============================================================================
//      Initialize to BRS solution
//===============================================================================

// the bottom profile is h = 1.0 - sin(r), where r=||x^2 + y^2||
// eta is constant at 1.0
// and

class BRSInitialCondition {

  // no member data, only methods

public:

  /// Shock Tube Initial Condition Function
  BRSInitialCondition(){ }

  /// \name Interface
  //@{
  inline Scalar PHI(const Point &C) const { return 9.8*(1.0 - sin(sqrt(pow(C.x,2.0) + pow(C.y,2.0)))); }
  inline Scalar UPHI(const Point &C) const { return 0.0; }
  inline Scalar VPHI(const Point &C) const { return 0.0; }
  inline Scalar DHDX(const Point &C) const { return cos(sqrt(pow(C.x,2.0) + pow(C.y,2.0)))*0.5*pow((pow(C.x,2.0) + pow(C.y,2.0)),-0.5)*2.0*C.x; }
  inline Scalar DHDY(const Point &C) const { return cos(sqrt(pow(C.x,2.0) + pow(C.y,2.0)))*0.5*pow((pow(C.x,2.0) + pow(C.y,2.0)),-0.5)*2.0*C.y; }
  inline Scalar G(const Point &C) const { return 9.8; }
  inline Scalar h(const Point &C) const { return 1.0 - sin(sqrt(pow(C.x,2.0) + pow(C.y,2.0))); } // sin(r)
  //@}
};

//===============================================================================
//      Initialize to Parabolic Bowl solution from Xing Zhang Shu (2006?)
//===============================================================================

// eta = h0(x/a)^2

class PBInitialCondition {

public:

  /// Shock Tube Initial Condition Function
  PBInitialCondition(){ }

  /// \name Interface
  //@{
  inline Scalar PHI(const Point &C) const {
    const Scalar a = 3000.0;
    const Scalar h0 = 10.0;
    const Scalar B = 5.0;
    const Scalar g = 9.8;
    const Scalar w = sqrt(2.0*g*h0)/a;
    const Scalar t = 0.0; // assumes initial condition is at time t = 0.0
    const Scalar h_plus_eta = h0 - pow(B,2.0)/(4.0*g) * cos(2.0*w*t) - pow(B,2.0)/(4.0*g) - B*C.x/(2.0*a)*sqrt(8.0*h0/g)*cos(w*t);
    return g*(h_plus_eta);
  }
  inline Scalar UPHI(const Point &C) const { return 0.0; }
  inline Scalar VPHI(const Point &C) const { return 0.0; }
  inline Scalar DHDX(const Point &C) const {
    const Scalar a = 3000.0;
    const Scalar h0 = 10.0;
    const Scalar B = 5.0;
    const Scalar g = 9.8;
    const Scalar w = sqrt(2.0*g*h0)/a;
    const Scalar t = 0.0; // assumes initial condition is at time t = 0.0
    return -B/(2.0*a)*sqrt(8.0*h0/g)*cos(w*t) - 2.0*h0*C.x/pow(a,2.0);
  }
  inline Scalar DHDY(const Point &C) const { return 0.0; }
  inline Scalar G(const Point &C) const { return 9.8; }
  inline Scalar h(const Point &C) const { return 1.0 - sin(sqrt(pow(C.x,2.0) + pow(C.y,2.0))); } // sin(r)
  //@}
};



} // namespace Reo

#endif  // REO_SHALLOWIC_HPP

#else // DGM_REMOVE_FOR_RELEASE
// This capability is under development.
#endif // DGM_REMOVE_FOR_RELEASE
