#ifndef REO_WAVETYPE_HPP
#define REO_WAVETYPE_HPP

/** \file Wavetype.hpp
    \brief Defines a variety of Acoustic waves for the Wave module
    \author Scott Collis
    \todo Each wave type should really be a different class.
*/

// DGM includes
#include "Comm.hpp"
#include "Coordinates.hpp"
#include "Constants.hpp"

namespace Reo {

using namespace DGM;

/// Define a plane wave as: \f$\rho = a*\sin(x+y)\f$
class AcousticWave {

public:
  enum WaveType {
    Sine,                    ///< Sine wave
    Gaussian,                ///< Guassian wave packet
    ObliqueGaussian,         ///< Oblique Gaussian wave packet
    Cylindrical              ///< Cylindrical wave
  };

private:
  Scalar Ma;                 ///< Mach number
  //Scalar Pr;               ///< Prandlt number
  Scalar amp;                ///< Amplitude
  Scalar x0;                 ///< x-location
  Scalar sigma;              ///< Standard deviation
  Scalar gamma;              ///< ratio of specific heats
  Scalar mC;                 ///< what is this?
  //Scalar rho;              ///< density
  //Scalar p;                ///< pressure
  //Scalar u1;               ///< velocity in x1-direction
  //Scalar u2;               ///< velocity in x2-direction
  //Scalar t;                ///< temperature

  WaveType wavetype;         ///< type of wave

  // 1d acoustics
  char wavedir;              ///< wave direction

  // 2d acoustics
  Scalar y0;                 ///< y-location
  Scalar xn;                 ///< Wavelength in x
  Scalar yn;                 ///< Wavelength in y
  Scalar kx;                 ///< Wavenumber in x
  Scalar ky;                 ///< Wavenumber in y

  // for 2d cylindrical wave
  Scalar r0;                 ///< Initial radius
  int wavesign;              ///< Wave propagation direction, should be in amp

public:

  /// 1d acoustic wave constructor
  AcousticWave(Scalar M_a, Scalar P_r, Scalar gamma_,
               Scalar am_p, Scalar x_0, Scalar sigm_a, char c ='x',
               char d='p', WaveType wt=Sine ) :
  Ma(M_a),
  //Pr(P_r),
  amp(am_p),
  x0(x_0),
  sigma(sigm_a),
  gamma(gamma_),
  wavetype(wt),
  wavedir(c),
  y0(0.0),
  r0(one)
  {
    mC = one/Ma*one; // what is the meaning of this [SSC]?
    if(d=='p')
      wavesign = 1;
    else
      wavesign =-1;
    r0 = one;
  }

  /// 2d acoustic wave constructor
  AcousticWave(Scalar M_a, Scalar P_r, Scalar gamma_,
               Scalar am_p, Scalar x_0, Scalar y_0,
               Scalar sigm_a, char d='p', WaveType wt=Sine,
               Scalar r_0=one, Scalar x_n=one, Scalar y_n=one ) :
  Ma(M_a),
  //Pr(P_r),
  amp(am_p),
  x0(x_0),
  sigma(sigm_a),
  gamma(gamma_),
  wavetype(wt),
  wavedir('x'),
  y0(y_0),
  xn(x_n),
  yn(y_n),
  r0(r_0)
  {
    mC = one/Ma*one;
    if(d=='p')
      wavesign =  1;
    else
      wavesign = -1;
    // these wavenumbers are only used for planar waves
    kx = x_n/::sqrt(xn*xn+yn*yn);
    ky = y_n/::sqrt(xn*xn+yn*yn);
  }

  /// Compute density at a point
  Scalar R(const DGM::Point &C) {
    Scalar rho1=1,xh,rh;
    switch(wavetype) {
    case Sine: // 1d Sine wave
      if(wavedir=='x')
        rho1 = pt5*amp*(one+sin(C.x/sigma*2*pi))/mC/mC;
      else
        rho1 = pt5*amp*(one+sin(C.y/sigma*2*pi))/mC/mC;
      break;
    case Gaussian: // 1d Gaussian plane wave
      if(wavedir=='x') {
        rho1 = pt5*amp*exp( -pt5 * pow((C.x - x0)/sigma,2) )/mC/mC;
        // rho1 = pt5*amp/mC/mC;
      } else
        rho1 = pt5*amp*exp( -pt5 * pow((C.y - x0)/sigma,2) )/mC/mC;
      break;
    case ObliqueGaussian: // general 2d plane-wave with Gaussian profile
      xh = kx*(C.x - x0) + ky*(C.y - y0);
      // Scalar xh1 = kx*( C.x - 3 ) + ky * ( C.y - 3 );
      rho1 = pt5*amp*exp(-pt5*(xh/sigma )*(xh/sigma))/mC/mC ;
      // ++exp( -pt5 * ( xh1/sigma )*(xh1/sigma))
      break;
    case Cylindrical:
      rh = ::sqrt((C.x-x0)*(C.x-x0)+(C.y-y0)*(C.y-y0));
      if (rh < 1.0e-10) { }
      // kx = (C.x-x0)/rh;
      // ky = (C.y-y0)/rh;
      rh = rh - r0;
      rho1 = pt5*amp*exp( -pt5 * (rh/sigma )*(rh/sigma) )/mC/mC ;
      break;
    default:
      DGM::Comm::World->cerr() << " AcousticWave::Unsupported Wave type"
                               << wavetype << endl;
      DGM::Comm::World->exit(DGM::FAILURE);
    }
    return rho1;
  }

  /// Compute x1 velocity at a point
  Scalar U(const DGM::Point &C) {
    Scalar u1=0,xh,rh;
    switch(wavetype) {
    case Sine: // 1d Sine wave
      if(wavedir=='x')
        u1 = wavesign*amp*pt5*(one+sin(C.x/sigma*2*pi))/mC/one ; //rhom
      else
        u1 = 0.0; //rhom
      break;
    case Gaussian: // 1d Gaussian plane wave
      if(wavedir=='x')
        u1 = wavesign*amp*pt5*exp( -pt5 * pow((C.x - x0)/sigma,2))/mC/one;
      // u1= wavesign*amp*pt5/mC/one ;
      else
        u1 = 0.0;
      break;
    case ObliqueGaussian:  // general plane wave -gauss
      xh = kx*(C.x - x0) + ky*(C.y - y0);
      // Scalar xh1 = kx*( C.x - 3 ) + ky * ( C.y - 3 );
      u1 = wavesign*kx*pt5*amp*exp( -pt5 * ( xh/sigma )*(xh/sigma))/mC/one;
      // +exp( -pt5 * ( xh1/sigma )*(xh1/sigma)
      break;
    case Cylindrical:
      rh = ::sqrt((C.x-x0)*(C.x-x0)+(C.y-y0)*(C.y-y0));
      if (rh < 1.0e-10) {
        u1=zero;
        break;
      }
      kx = (C.x-x0)/rh;
      ky = (C.y-y0)/rh;
      rh = rh - r0;
      u1 = wavesign*kx*pt5*amp*exp(-pt5*(rh/sigma)*(rh/sigma))/mC/one;
      break;
    default:
      DGM::Comm::World->cerr() << "AcousticWave::Unsupported Wave type: "
                               << wavetype << endl;
      DGM::Comm::World->exit(DGM::FAILURE);
    }
    return u1;
  }

  /// Compute x2 velocity at a point
  Scalar V(const DGM::Point &C) {
    Scalar v1=0,xh,rh;
    switch(wavetype) {
    case Sine: // 1d Sine wave
      if(wavedir=='y')
        v1 = wavesign*amp*pt5*(one+sin(C.y/sigma*2*pi))/mC/one ; // rhom
      else
        v1=0 ;
      break;
    case Gaussian:  // 1d Gaussian plane wave
      if(wavedir=='y')
        v1 = wavesign*amp*pt5*exp( -pt5 * pow((C.y - x0)/sigma,2) )/mC/one;
      else
        v1 = 0 ;
      break;
    case ObliqueGaussian:  // general plane wave -gauss
      xh = kx*(C.x - x0) + ky*(C.y - y0) ;
      // Scalar xh1 = kx*( C.x - 3 ) + ky * ( C.y - 3 );
      v1 = wavesign*ky*pt5*amp*exp( -pt5 * (xh/sigma )*(xh/sigma))/mC/one;
      // +exp( -pt5 * ( xh1/sigma )*(xh1/sigma)
      break;
    case Cylindrical: // Cylindrical wave
      rh = ::sqrt((C.x-x0)*(C.x-x0)+(C.y-y0)*(C.y-y0));
      if(rh<1.0e-10) {
        v1=0;
        break;
      }
      kx = (C.x-x0)/rh;
      ky = (C.y-y0)/rh;
      rh = rh - r0;
      v1 = wavesign*ky*pt5*amp*exp(-pt5*(rh/sigma)*(rh/sigma))/mC/one;
      break;
    default:
      DGM::Comm::World->cerr() << " AcousticWave::Unsupported Wave type"
                               << wavetype << endl;
      DGM::Comm::World->exit(DGM::FAILURE);
    }
    return v1;
  }

  /// Compute temperature at a point
  Scalar T(const DGM::Point &C) {
    Scalar rho1, xh, rh, T1=1;
    switch(wavetype) {
    case Sine: // 1d Sine
      if(wavedir=='x') {
        rho1 = pt5*(one+sin(C.x/sigma*2*pi))/mC/mC;
        // T = ( gamma * Ma**2 * p - tm * rho ) / rhom
        T1 = amp*(gamma*Ma*Ma*rho1*mC*mC - one *rho1)/one;
      }
      else {
        rho1 = pt5*(one+sin(C.y/sigma*2*pi))/mC/mC;
        // T1 = ( gamma * Ma**2 * p - tm * rho ) / rhom
        T1 = amp*(gamma*Ma*Ma*rho1*mC*mC - one *rho1)/one;
      }
      break;
    case Gaussian:  // 1d Gaussian plane wave
      if(wavedir=='x') {
        rho1 = pt5*exp( -pt5 * pow((C.x - x0)/sigma,2) )/mC/mC;
        // rho1 = pt5/mC/mC;
        // T1   = ( gamma * Ma**2 * p - tm * rho ) / rhom
        T1 = amp*(gamma*Ma*Ma*rho1*mC*mC - one *rho1)/one;
      }
      else {
        rho1 = pt5*exp( -pt5 * pow((C.y - x0)/sigma,2) )/mC/mC;
        // rho1 = pt5*exp( -pt5 * 1 )/mC/mC;
        // T1   = ( gamma * Ma**2 * p - tm * rho ) / rhom
        T1 = amp*(gamma*Ma*Ma*rho1*mC*mC - one *rho1)/one;
      }
      break;
    case ObliqueGaussian:  // general plane wave -gauss
      xh = kx*(C.x - x0) + ky*(C.y - y0);
      // Scalar xh1 = kx*( C.x - 3 ) + ky * ( C.y - 3 );
      rho1 = pt5*exp( -pt5 * ( xh/sigma )*(xh/sigma))/mC/mC;
      // ++exp( -pt5 * ( xh1/sigma )*(xh1/sigma))
      // T1 = ( gamma * Ma**2 * p - tm * rho ) / rhom
      T1 = amp*(gamma*Ma*Ma*rho1*mC*mC - one *rho1)/one;
      break;
    case Cylindrical:
      rh = ::sqrt((C.x-x0)*(C.x-x0)+(C.y-y0)*(C.y-y0));
      if (rh<1.0e-10) { }
      // kx = (C.x-x0)/rh;
      // ky = (C.y-y0)/rh;
      rh = rh - r0;
      rho1 = pt5*exp(-pt5*(rh/sigma)*(rh/sigma))/mC/mC ;
      // T1 = ( gamma * Ma**2 * p - tm * rho ) / rhom
      T1 = amp*(gamma*Ma*Ma*rho1*mC*mC - one *rho1)/one;
      break;
    default:
      DGM::Comm::World->cerr() << " AcousticWave::Unsupported Wave type"
                               <<wavetype<<endl;
      DGM::Comm::World->exit(DGM::FAILURE);
    }
    return T1;
  }

};

} // namespace

#endif  // REO_WAVETYPE_HPP
