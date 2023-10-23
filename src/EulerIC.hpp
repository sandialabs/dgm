#ifndef REO_EULERIC_HPP
#define REO_EULERIC_HPP

/** \file EulerIC.hpp
    \brief Compressible Euler initial conditions
    \author S. Scott Collis
*/

// system includes
#include <iostream>

// local includes
#include "Comm.hpp"
#include "Types.hpp"
#include "Format.hpp"
#include "FFT.hpp"

#ifdef DGM_USE_BOOST_RANDOM
#include "boost/random/linear_congruential.hpp"
#include "boost/random/uniform_01.hpp"
#endif

#ifdef DGM_USE_BOOST_MATH
#include "boost/math/special_functions/expint.hpp"
#endif

namespace Reo {

/// Vortex Sheet
class Vortex_Sheet {
  // The reference conditions are at the centerline where u = 1,
  Scalar U_0;   ///< far-field velocity
  Scalar T_0;   ///< far-field temperature
  Scalar Ma;    ///< reference Mach number
  Scalar gamma; ///< ratio of specific heats
  Scalar r;     ///< shear layer width parameter
  //Scalar delta; ///< amplitude of perturbation

  Scalar rho(const Point &C) {
    return 1.0/T(C); // constant pressure approximation thru a shear layer
  }
  Scalar u(const Point &C) {
    return tanh(r*(C.y));
  }
  Scalar v(const Point &C) {
    // This is a divergence free disturbance (Brown & Minion, JCP)
    return 0.0; // delta*sin(2*pi*(C.x+0.25));
    // This disturbance has nonzero divergence (Chaniotis et al., JCP)
    // return delta*sin(2*pi*(C.x+0.25))*cos(2*pi*(C.y+0.25));
  }
  Scalar T(const Point &C) {
    Scalar ul = u(C);
    return (Ma*Ma*0.5*(gamma-1)*(ul*(1+U_0) - pow(ul,2) - U_0) +
      (T_0*(1-ul) + ul-U_0)/(1-U_0));
  }
public:
  Vortex_Sheet( Scalar r_Ma, Scalar r_r=80, Scalar r_delta=0.05,
                Scalar r_gamma=1.4) :
    Ma(r_Ma),
    gamma(r_gamma),
    r(r_r)
    //delta(r_delta)
{
    U_0 = -1.0;
    T_0 =  0.5;
  }
  Scalar R(const Point &C) { return rho(C); }
  Scalar U(const Point &C) { return rho(C) * u(C); }
  Scalar V(const Point &C) { return rho(C) * v(C); }
  Scalar W(const Point &C) { return 0.0; }
  Scalar E(const Point &C) { return rho(C)*T(C)/(gamma*(gamma-1)*Ma*Ma) +
      0.5*rho(C)*(u(C)*u(C)+v(C)*v(C));
  }
};

/// Brown and Minion Double shear layer
class Brown_Minion {
  // The reference conditions are at the centerline where u = 1,
  Scalar U_0;   ///< far-field velocity
  Scalar T_0;   ///< far-field temperature
  Scalar Ma;    ///< reference Mach number
  Scalar gamma; ///< ratio of specific heats
  Scalar r;     ///< shear layer width parameter
  Scalar delta; ///< amplitude of perturbation

  Scalar rho(const Point &C) {
    return 1.0/T(C); // constant pressure approximation thru a shear layer
  }
  Scalar u(const Point &C) {
    if (C.y <= 0.5)
      return tanh(r*(C.y-0.25));
    else
      return tanh(r*(0.75-C.y));
  }
  Scalar v(const Point &C) {
    // This is a divergence free disturbance (Brown & Minion, JCP)
    return delta*sin(2*pi*(C.x+0.25));
    // This disturbance has nonzero divergence (Chaniotis et al., JCP)
    // return delta*sin(2*pi*(C.x+0.25))*cos(2*pi*(C.y+0.25));
  }
  Scalar T(const Point &C) {
    Scalar ul = u(C);
    return (Ma*Ma*0.5*(gamma-1)*(ul*(1+U_0) - pow(ul,2) - U_0) +
      (T_0*(1-ul) + ul-U_0)/(1-U_0));
  }
public:
  Brown_Minion( Scalar r_Ma, Scalar r_r=80, Scalar r_delta=0.05,
                Scalar r_gamma=1.4) :
    Ma(r_Ma), gamma(r_gamma), r(r_r), delta(r_delta) {
    U_0 = -1.0;
    T_0 =  0.5;
  }
  Scalar R(const Point &C) { return rho(C); }
  Scalar U(const Point &C) { return rho(C) * u(C); }
  Scalar V(const Point &C) { return rho(C) * v(C); }
  Scalar W(const Point &C) { return 0.0; }
  Scalar E(const Point &C) { return rho(C)*T(C)/(gamma*(gamma-1)*Ma*Ma) +
      0.5*rho(C)*(u(C)*u(C)+v(C)*v(C));
  }
};

/// Compressible Scalar shear layer
/** Chaniotis, Poulikakos, and Koumoutsakos JCP, 182, 67-90 (2002) */
class Double_Shear {
  // The reference conditions are at the centerline where u = 1,
  Scalar U_0;   ///< far-field velocity
  Scalar T_0;   ///< far-field temperature
  Scalar delta; ///< amplitude of perturbation
  Scalar x_0;   ///< offset in x
  Scalar y_0;   ///< offset in y
  Scalar Ma, gamma;
  Scalar rho(const Point &C) {
    return 1.0/T(C); // constant pressure approximation thru a shear layer
  }
  Scalar u(const Point &C) {
    return U_0 + (1.0 - U_0) * exp(-pow(10*(C.y-y_0),6));
  }
  Scalar v(const Point &C) {
    return delta*sin(2*pi*(C.x-x_0))*cos(2*pi*(C.y-y_0));
  }
  Scalar T(const Point &C) {
    Scalar ul = u(C);
    return (Ma*Ma*0.5*(gamma-1)*(ul*(1+U_0) - pow(ul,2) - U_0) +
      (T_0*(1-ul) + ul-U_0)/(1-U_0));
  }
public:
  Double_Shear( Scalar r_Ma, Scalar r_gamma) : Ma(r_Ma), gamma(r_gamma) {
    U_0   = -1.0;
    T_0   =  0.5;
    delta =  0.01;
    x_0   =  0.5;
    y_0   =  0.5;
  }
  Scalar R(const Point &C) { return rho(C); }
  Scalar U(const Point &C) { return rho(C) * u(C); }
  Scalar V(const Point &C) { return rho(C) * v(C); }
  Scalar W(const Point &C) { return 0.0; }
  Scalar E(const Point &C) { return rho(C)*T(C)/(gamma*(gamma-1)*Ma*Ma) +
      0.5*rho(C)*(u(C)*u(C)+v(C)*v(C));
  }
};

/// Taylor Green vortex
/** Compressible analogue due to Chaniotis, Poulikakos, and Koumoutsakos
    JCP, 182, 67-90 (2002) */
class Taylor_Green {
  Scalar U_ref, Re, Ma, b, p_ref, gamma;
  Scalar rho(const Point &C, const Scalar t=0) {
    return pow(p(C,t)/p_ref, 1.0/gamma);
  }
  Scalar u(const Point &C, const  Scalar t=0) {
    return -U_ref * exp(b*t) * cos(2*pi*C.x) * sin(2*pi*C.y);
  }
  Scalar v(const Point &C, const Scalar t=0) {
    return U_ref * exp(b*t) * sin(2*pi*C.x) * cos(2*pi*C.y);
  }
  Scalar T(const Point &C, const Scalar t=0) {
    return pow(rho(C),gamma-1.0);
  }
  Scalar p(const Point &C, const Scalar t=0) {
    return p_ref - 0.25*U_ref*U_ref*exp(b*t)*(cos(4*pi*C.x) + cos(4*pi*C.y));
  }
public:
  Taylor_Green( Scalar r_U_ref, Scalar r_Re, Scalar r_Ma, Scalar r_gamma)
    : U_ref(r_U_ref), Re(r_Re), Ma(r_Ma), gamma(r_gamma) {
    b = -8.0*pi*pi/Re;
    p_ref = 1.0/(gamma*Ma*Ma);
    // cout << U_ref << ", " << Re << ", " << Ma << ", " << gamma << ", "
    //      << b << ", " << p_ref << endl;
  }
  Scalar R(const Point &C, const Scalar t=0) { return rho(C,t); }
  Scalar U(const Point &C, const Scalar t=0) { return rho(C,t) * u(C,t); }
  Scalar V(const Point &C, const Scalar t=0) { return rho(C,t) * v(C,t); }
  Scalar W(const Point &C, const Scalar t=0) { return 0.0; }
  Scalar E(const Point &C, const Scalar t=0) {
    return rho(C,t)*T(C,t)/(gamma*(gamma-1)*Ma*Ma) +
           0.5*rho(C,t)*(u(C,t)*u(C,t)+v(C,t)*v(C,t));
  }
};

/// Defines a single Compressible Oseen vortex.
/** This is an exact solution of the Euler equations. */
class OseenVortex {
  Scalar x0, y0, radius, amp, Ma;
  Scalar gamma;
  Scalar r2(Scalar x, Scalar y) {
    return ((x-x0)*(x-x0)+(y-y0)*(y-y0))/radius/radius;
  }
public:
  Scalar rho(const Point &C) {
    return pow(1.0 - 0.5*(gamma-1.0)*Ma*Ma*exp(1.0-r2(C.x,C.y)),
               1.0/(gamma-1.0));
  }
  Scalar u(const Point &C) {
    return -amp*(C.y-y0)/radius * exp(0.5*(1.0-r2(C.x,C.y)));
  }
  Scalar v(const Point &C) {
    return  amp*(C.x-x0)/radius * exp(0.5*(1.0-r2(C.x,C.y)));
  }
  Scalar t(const Point &C) { return pow(rho(C),gamma-1.0); }
  OseenVortex(Scalar x_0, Scalar y_0, Scalar rad, Scalar a, Scalar M_a,
              Scalar gamma_) {
    x0=x_0; y0=y_0; radius=rad; amp=a; Ma=M_a; gamma=gamma_;
    // cout << x0 << " " << y0 << " " << radius << " " << amp << " " << Ma
    //      << " " << gamma << endl;
  }
  // methods
  Scalar R(const Point &C) { return rho(C); }
  Scalar U(const Point &C) { return rho(C) * u(C); }
  Scalar V(const Point &C) { return rho(C) * v(C); }
  Scalar W(const Point &C) { return 0.0; }
  Scalar E(const Point &C) { return amp*amp*rho(C)*t(C)/(gamma*(gamma-1)*Ma*Ma)
      + 0.5*rho(C)*(u(C)*u(C)+v(C)*v(C)); }
};


/// Makes a Gaussian Acoustic pulse in the x-direction
class AcousticPulse {
  Scalar amp, x0, sigma, gamma, gm1;
public:
  AcousticPulse(Scalar _amp, Scalar _x0, Scalar _sigma, Scalar _gamma) :
    amp(_amp), x0(_x0), sigma(_sigma), gamma(_gamma) { gm1 = gamma-1.0; }
  AcousticPulse(ifstream &in, Scalar _gamma) :
    amp(1.0), x0(0.0), sigma(0.0), gamma(_gamma) {
    gm1 = gamma-1.0;
    if (!(in >> amp >> x0 >> sigma)) {
      DGM::Comm::World->cerr() << "AcousticPulse: error reading parameters"
                               << endl;
      DGM::Comm::World->exit(DGM::FAILURE);
    }
  }
  void evaluate( const Point &C, dVector &s ) const {

    if (s.size() != 5) {
      DGM::Comm::World->cerr()<<"AcousticPulse::evaluate -- only works in 3-d"
                              << endl;
      DGM::Comm::World->exit(DGM::FAILURE);
    }

    // No-flow state
    Scalar Ma = 1.0;   // reference Mach number
    Scalar r  = 1.0;
    Scalar u  = 0.0;
    Scalar v  = 0.0;
    Scalar w  = 0.0;
    Scalar e  = 1.0/(gamma*gm1*Ma*Ma);
    Scalar c  = sqrt( gamma*gm1*e );

    // set characteristic amplitudes
    Scalar c1 = 0.0;
    Scalar c2 = 0.0;
    Scalar c3 = exp( -0.5 * pow((C.x - x0)/sigma,2.0) );
    Scalar c4 = 0.0;

    // perturbations
    Scalar rp = (-c1 + 0.5*( c3 + c4 ))/(c*c);
    Scalar up = (c3 - c4 )*0.5/(r*c);
    Scalar vp = c2/(r*c);
    Scalar wp = 0.0;
    Scalar pp = 0.5*( c3 + c4 );
    Scalar ep = (pp/gm1 - rp*e)/r;

    // add perturbations
    r += amp * rp;
    u += amp * up;
    v += amp * vp;
    w += amp * wp;
    e += amp * ep;

    // load up conservative variables
    s[0] = r;
    s[1] = r*u;
    s[2] = r*v;
    s[3] = r*w;
    s[4] = r*e + 0.5*r*(u*u + v*v + w*w);

#ifdef EULER_IC_DEBUG
    Format sci(4);
    sci.scientific().width(12);
    cout << sci(C.x) << sci(r) << sci(u) << sci(v) << sci(w) << sci(e) << endl;
#endif
  }
};

#ifdef DGM_USE_BOOST_RANDOM

/// Make a turbulent channel flow
class TurbulentChannel {

  // The Mach number is now based on the centerline velocity
  Scalar Re_tau, Mach, U_bulk, Noise, Factor, gamma, U_c;
  Scalar Lx, Ly;
  int    Exponent, Nx, Ny;

  static Scalar xshape( const Scalar z ) {
    return -20.0*pow(z-1.0,6.0) + 19.0*pow(z-1.0,4.0) + 1.0;
  }
  static Scalar yshape( const Scalar z ) {
    return -5.0*pow(z-1.0,6.0) + 4.0*pow(z-1.0,4.0) + 1.0;
  }
  static Scalar zshape( const Scalar z ) {
    return yshape(z);
  }
  Scalar mean( const Scalar z ) const {
    return Factor * ( 1.0 - pow(z-1.0,(Scalar)Exponent) );
  }

public:

  // setup random number generators
  typedef boost::minstd_rand random_number_generator;
  typedef boost::uniform_01< random_number_generator, Scalar >
    random_distribution;

  static random_number_generator generator;
  static random_distribution urand;

  TurbulentChannel(Scalar retau, Scalar mach, int nx, int ny, Scalar noise,
                   Scalar gamma_) {
    Re_tau   = retau;
    Mach     = mach;
    U_bulk   = 7.4 * pow(Re_tau, 1.0/7.0);
    Noise    = noise;
    Factor   = 7.0/6.0 * U_bulk;
    Exponent = 6;
    Nx       = nx;  // Number of Fouier modes in streamwise direction
    Ny       = ny;  // Number of Fouier modes in spanwise direction
    gamma    = gamma_;
    U_c      = mean(1.0);
    Lx       = 4.0*pi;      // reasonable for Re_\tau = 180
    Ly       = 4.0*pi/3.0;  // reasonable for Re_\tau = 180
  }

  TurbulentChannel(ifstream &in, Scalar gamma_) :
    Re_tau(0), Mach(0), Noise(0), Lx(0), Ly(0), Nx(0), Ny(0){
    // cout << "Building TurbulentChannel initial condition" << endl;
    if (!(in >> Re_tau >> Mach >> Lx >> Ly >> Nx >> Ny >> Noise )) {
      DGM::Comm::World->cerr() << "TurbulentChannel: error reading parameters"
                               << endl;
      DGM::Comm::World->exit(DGM::FAILURE);
    }
    U_bulk   = 7.4 * pow(Re_tau, 1.0/7.0);
    Factor   = 7.0/6.0 * U_bulk;
    Exponent = 6;
    gamma    = gamma_;
    U_c      = mean(1.0);
    if (Lx < 0) Lx = fabs(Lx)*pi;
    if (Ly < 0) Ly = fabs(Ly)*pi;
  }

  void evaluate( const Point &C, dVector &s ) const {
    if (s.size() != 5) {
      DGM::Comm::World->cerr()
        <<"TurbulentChannel::evaluate -- only works in 3-d"<<endl;
      DGM::Comm::World->exit(DGM::FAILURE);
    }

    // Mean flow
    Scalar r  = 1.0;
    Scalar u  = mean(C.z);
    Scalar v  = 0.0;
    Scalar w  = 0.0;
    Scalar e  = 1.0/( gamma * (gamma-1.0) * pow(Mach/U_c,2.0) );
    // Scalar c  = sqrt( gamma * (gamma-1.0) * e );

    // define fundamental wavenumbers and add noise
    Scalar kx = 2.0*pi/Lx;
    Scalar ky = 2.0*pi/Ly;

    // loop over Fourier modes
    for (int i=1; i<Nx; i++) {     // make sure not to mess up mean
      for (int j=1; j<Ny; j++) {
        Scalar k2i = 1.0/ ( pow(i*kx,2.0) + pow(j*ky,2.0) );
        u += Noise * xshape(C.z) * sin( i*kx*C.x + 2*pi*urand() ) *
          sin( j*ky*C.y + 2*pi*urand() ) * k2i;
        v += Noise * yshape(C.z) * sin( i*kx*C.x + 2*pi*urand() ) *
          sin( j*ky*C.y + 2*pi*urand() ) * k2i;
        w += Noise * zshape(C.z) * sin( i*kx*C.x + 2*pi*urand() ) *
          sin( j*ky*C.y + 2*pi*urand() ) * k2i;
      }
    }

    // load up conservative variables
    s[0] = r;
    s[1] = r*u;
    s[2] = r*v;
    s[3] = r*w;
    s[4] = r*e + 0.5*r*(u*u + v*v + w*w);

#ifdef EULER_IC_DEBUG
    Format sci(4);
    sci.scientific().width(12);
    cout << sci(C.x) << sci(r) << sci(u) << sci(v) << sci(w) << sci(e) << endl;
#endif
  }

};

#endif // DGM_USE_BOOST_RANDOM

#if defined(DGM_USE_BOOST_RANDOM)

/// Make an isotropic turbulent field
/** \warning Not yet finished [SSC 11/28/06]. */
class IsotropicTurbulence {

  Scalar Noise;
  int Nx, Ny, Nz;
  Scalar gamma;

public:

  // setup random number generators
  typedef boost::minstd_rand random_number_generator;
  typedef boost::uniform_01< random_number_generator, Scalar >
    random_distribution;

  static random_number_generator generator;
  static random_distribution urand;

  IsotropicTurbulence(int nx, int ny, int nz, int noise) {
    Noise = noise;
    Nx = nx;
    Ny = ny;
    Nz = nz;
  }

  IsotropicTurbulence(ifstream &in, Scalar gamma_) {
    // cout << "Building IsotropicTurbulence initial condition" << endl;
    if (!(in >> Nx >> Ny >> Nz >> Noise )) {
      DGM::Comm::World->cerr()
        << "IsotropicTurbulence: error reading parameters" << endl;
      DGM::Comm::World->exit(DGM::FAILURE);
    }
    gamma = gamma_;
  }

  void evaluate( const Point &C, dVector &s ) const {

    if (s.size() != 5) {
      DGM::Comm::World->cerr()
        <<"IsotropicTurbulence::evaluate -- only works in 3-d"<<endl;
      DGM::Comm::World->exit(DGM::FAILURE);
    }

    // add noise
    Scalar Lx = 2.0*pi;      // Hardwired for now (shame, shame...)
    Scalar Ly = 2.0*pi;
    Scalar Lz = 2.0*pi;

    // oddball wavenumbers
    int Mx = (Nx+2)/2;
    int My = (Ny+2)/2;
    int Mz = (Nz+2)/2;

    // setup wavenumbers
    dVector kx(My), ky(Ny), kz(Nz);
    for (int i=0; i<Mx; ++i) {
      kx[i] = 2.0 * pi / Lx * (Scalar)(i);
    }
    //cout << "kx = " << kx;
    ky[0] = 0.0;
    for (int j=1; j<My; ++j) {
      ky[Ny-j] = -2.0 * pi / Ly * (Scalar)(j);
      ky[j]    =  2.0 * pi / Ly * (Scalar)(j);
    }
    //cout << "ky = " << ky;
    kz[0] = 0.0;
    for (int k=1; k<Mz; ++k) {
      kz[Nz-k] = -2.0 * pi / Lz * (Scalar)(k);
      kz[k]    =  2.0 * pi / Lz * (Scalar)(k);
    }
    //cout << "kz = " << kz;

    // loop over Fourier modes
    Scalar fact;

    cVector u(Nz*Ny*Mx);
    cVector v(Nz*Ny*Mx);
    cVector w(Nz*Ny*Mx);

    for (int k=0; k<Nz; k++) {
      for (int j=0; j<Ny; j++) {
        for (int i=0; i<Mx; i++) {
          Scalar theta1 = urand();
          Scalar theta2 = urand();
          Scalar phi    = urand();
          //cout << i << ", " << j << ", " << ", " << k << ", " << theta1
          //     << ", " << theta2 << ", " << phi << endl;
          Scalar kmag = sqrt( pow(kx[i],2) + pow(ky[j],2) + pow(kz[k],2) );
          Scalar k12  = sqrt( pow(kx[i],2) + pow(ky[j],2) );

          if (kmag == 0)
            fact = 0.0;
          else
            fact = sqrt( E0(kmag)/ (2.0 * pi) ) / kmag;

          complex<Scalar> iota(0.0,1.0);
          complex<Scalar> alp, beta;

          // for random (no mean) helicity
          alp  = fact * exp( 2.0 * iota * pi * theta1 ) * cos( two * pi * phi);
          beta = fact * exp( 2.0 * iota * pi * theta2 ) * sin( two * pi * phi);

          // cout << alp << " " << beta << endl;

          int n = i + j*Mx + k*(Mx*Ny);

          if ( k12 == 0 ) {
            u[n] = alp;
            v[n] = beta;
            if ( k == 0 ) w[n] = 0.0;
          } else {
            u[n] = ( alp * kmag * ky[j] + beta * kx[i] * kz[k] ) / (kmag*k12);
            v[n] = ( beta * ky[j] * kz[k] - alp * kmag * kz[i] ) / (kmag*k12);
            if ( k == 0 ) w[n] = -beta * k12 / kmag;
          }
        }
      }
    }

    // WARNING:  NOT TESTED YET
    // satisfy conjugate symmetry
    {
      int i, j, k, m, n;
      for (j=1; j<My; ++j) {
        i=0; k=0; n=i + j*Mx + k*(Mx*Ny);
        m = i + Ny-j + k*(Mx*Ny);
        w[n] = conj( w[m] );
      }
      u[0] = 0.0;
      v[0] = 0.0;
      for (j=1; j<My; ++j) {
        i=0; k=0; n=i + j*Mx + k*(Mx*Ny); m=i + (Ny-j)*Mx + k*(Mx*Ny);
        u[n] = conj( u[m] );
        v[n] = conj( v[m] );
      }
      for (k=1; k<Mz; ++k) {
        i=0; j=0; n=i + j*Mx + k*(Mx*Ny); m=i + j*Mx + (Nz-k)*(Mx*Ny);
        u[n] = conj( u[m] );
        v[n] = conj( v[m] );
        for (j=1; j<Ny+1; ++j) {
          i=0; n=i + j*Mx + k*(Mx*Ny); m=i + (Ny-j)*Mx + (Nz-k)*(Mx*Ny);
          u[n] = conj( u[m] );
          v[n] = conj( v[m] );
        }
      }
    }

    // WARNING:  NOT TESTED YET
    // satisfy continuity
    {
      for (int i=1; i<Mx; ++i) {
        int j(0), k(0), n(i + j*Mx + k*(Mx*Ny));
        u[n] = 0.0;
      }
      for (int j=1; j<Ny; ++j) {
        for (int i=0; i<Mx; ++i) {
          int k(0), n(i + j*Mx + k*(Mx*Ny));
          v[n] = -(kx[i]/ky[j])*u[n];
        }
      }
      for (int k=1; k<Nz; ++k) {
        for (int j=0; j<Ny; ++j) {
          for (int i=0; i<Mx; ++i) {
            int n(i + j*Mx + k*(Mx*Ny));
            w[n] = -(kx[i]*u[n] + ky[j]*v[n])/kz[k];
          }
        }
      }
    }

    // construct thermodynamic field
    cout << "Not implemented: construct thermodynamic field..." << endl;

    // evaluate in physical space
    cout << "Not implemented: evaluate in physical space..." << endl;

    cout << "Setting up FFT for conversion to physical space..."<<endl;

    DGM::FFT fft(Nx,Ny,Nz);
    dVector ur(Nx*Ny*Nz);

    cout << "Initial u[0] = " << u[0] << endl;

    // take the fast Fourier transform
    fft.forward_transform(u, ur);

    // now go back and make sure that you have the same thing
    fft.backward_transform(ur, u);

    cout << "Final u[0] = " << u[0] << endl;

    // There is a fundamental problem here in that evaulate() is intended to
    // return a state vector at a point in space while this routine is
    // designed to compute an entire field.  One option is to evaluate the
    // field on the first call and then to just query it on subsequent calls.
    // If this is done, then there should be a reset() method to make a new
    // field if needed.

    cout << "Finished IsotropicTurbulence::evaluate(...)" << endl;
    cout << "Exiting since IsotropicTurbulence IC is not yet completed"<<endl;
    exit(1);
  }

  // Comte-Bellot & Corrsin spectra parameters, the value of v_0 is used
  // to match to the initial energy of the experimental spectra
  Scalar E0( Scalar k ) const {
    Scalar result(0);

    Scalar v0(27.1893);  // from CBC experiment
    Scalar c1(0), c2(0);

    // matches Germiso
    const Scalar l(55.0); //, m(5.08), t0(42.0), u_inf(1000.0);

    dVector a(7);
    a[0] =  0.56102E+01;   a[1] = -0.11236E+01;   a[2] = -0.30961E+00;
    a[3] =  0.33172E+00;   a[4] = -0.10959E+00;   a[5] = -0.22320E-01;
    a[6] =  0.66575E-02;

    c1 = 2.0 * pi / l;
    c2 = c1 / (v0*v0);

    if (k==0)
      result = 0.0;
    else {
      Scalar arg=0.0;
      for (int i=0; i<7; ++i) arg += a[i]*pow(log(c1*k),i);
      result = c2 * exp(arg);
    }
    return result;
  }

};

#endif // defined(DGM_USE_BOOST_RANDOM)

/// Defines a single Compressible Colonius vortex.
/** This is an exact solution of the Euler equations. It requires the use of
    the exponential integral Ei. */
class ColoniusVortex {
  Scalar x0, y0;
  //Scalar radius;
  Scalar amp, Ma;
  Scalar gamma;
  Scalar fact,alpha, xi;
  Scalar f(Scalar x) {
#ifdef DGM_USE_BOOST_MATH
    if (x>sqrt(200.0))
      return 0.5;
    else
      return pt5 - exp(-x) + pt5*exp(-two*x) + x * boost::math::expint(-two*x)
             - x * boost::math::expint(-x);
#else
    error("The exponential integral Ei is required for the ColoniusVortex");
    return 0.0;
#endif
  }
  Scalar r(Scalar x, Scalar y) {
    return sqrt((x-x0)*(x-x0)+(y-y0)*(y-y0));
  }
  Scalar theta(Scalar x, Scalar y) {
    return atan2((y-y0),(x-x0));
  }
  Scalar p(Scalar x, Scalar y) {
    if(r(x,y)<1.0e-10)
      return fact;
    else
      return fact * pow( 1.0 - (gamma-1.0) * Ma*Ma/(xi*r(x,y)*xi*r(x,y))
                         *f(alpha * r(x,y)*r(x,y)),gamma/(gamma-1.0));
  }
public:
  Scalar rho(const Point &C) {
#if 0
   return pow(p(C.x,C.y)/fact,1.0/gamma);
#else
   // This density expression is incorrect?, but leads to a simplier flow to
   // resolve [SSC]
   return pow(p(C.x,C.y)/fact,-gamma);
#endif
  }
  Scalar u(const Point &C) {
    if(r(C.x,C.y)<1.0e-10)
      return 0.0;
    else
      return -sin(theta(C.x,C.y))*amp*(1.0-exp(-alpha*r(C.x,C.y)*r(C.x,C.y)))
        /(r(C.x,C.y)*xi);
  }
  Scalar v(const Point &C) {
    if(r(C.x,C.y)<1.0e-10)
      return 0.0;
    else
      return cos(theta(C.x,C.y))*amp*
             (1.0-exp(-alpha*r(C.x,C.y)*r(C.x,C.y)))/(r(C.x,C.y)*xi);
  }
  Scalar t(const Point &C) { return p(C.x,C.y)/(fact*rho(C)); }

  ColoniusVortex (Scalar x_0, Scalar y_0, Scalar rad, Scalar a, Scalar M_a,
                  Scalar gamma_) :
    x0(x_0),
    y0(y_0),
    //radius(rad),
    amp(a),
    Ma(M_a),
    gamma(gamma_)
  {
    fact = 1.0/(gamma*Ma*Ma);
    alpha = 1.2564312086261696770;
    xi = 1.0 - exp(-alpha);
  }
  // methods
  Scalar R(const Point &C) { return rho(C); }
  Scalar U(const Point &C) { return rho(C) * u(C); }
  Scalar V(const Point &C) { return rho(C) * v(C); }
  Scalar W(const Point &C) { return 0.0; }
  Scalar E(const Point &C) { return rho(C)*t(C)/(gamma*(gamma-1)*Ma*Ma)
      + 0.5*rho(C)*(u(C)*u(C)+v(C)*v(C)); }
};

} // namespace

#endif  // REO_EULERIC_HPP
