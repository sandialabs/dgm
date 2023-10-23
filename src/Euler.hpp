#ifndef REO_EULER_HPP
#define REO_EULER_HPP

/** \file  Euler.hpp
    \brief Declarations for the 2d Euler equations
    \author Scott Collis
*/

// DGM includes
#include "Comm.hpp"
#include "Domain.hpp"
#include "Element.hpp"
using namespace DGM;

// Reo includes
#include "ReoConfig.hpp"

namespace DGM {
  /// Generic flux class
  template <class Scalar=Scalar, class Ordinal=int>
  class Flux {
  };
} // namespace DGM

namespace Reo {

// forward declarations
class IdealGas;

/// Two-dimensional compressible Euler Domain
class Euler : public Domain {

  dVector wk1;   ///< local workspace
  dVector wk2;   ///< local workspace

protected:

  static const int NFIELDS = 4; ///< fixed number of fields for static arrays

public:

  // fluxes
  template <class Scalar=Scalar, class Ordinal=int> class Flux;
  template <class Scalar=Scalar, class Ordinal=int> class NumericalFlux;

  // BC declarations (definitions below)
  class WallBC;
  class SubsonicOutflowBC;
  class SupersonicOutflowBC;
  class LinearControlBC;
  class SteadyLinearControlBC;
  class ControlBC;
  class SteadyControlBC;

  // Source terms
  class Sponge;

  Scalar gamma;                   ///< Ratio of specific heats

  IdealGas *fluid;                ///< Fluid properties

  /// Constructor
  Euler( DGM::ArgList &args, const DGM::Comm::Ptr = DGM::Comm::World,
         const int pinc=0);

  /// Destructor
  virtual ~Euler();

  // override virtual Domain methods
  void parse_args( DGM::ArgList &args );
  void showUsage();

  virtual int plot(const string&);

  void set_material();

  void time_derivative( vField &, vField & );

  Scalar set_time_step( vField & );
  void set_ic( vField &, string=".ic" );

  void setup_BCdb( );
  void read_BCdb( ifstream & );
  BC* make_BC( ifstream &, string & );

  Source::Ptr make_Source( ifstream &, string & );
  void add_source(const vField &, vField & );

  void write_bndry_stats();

protected:

  /// Supported numerical fluxes
  enum flux_type {
    Roe,                   ///< Roe flux
    vanLeer,               ///< van Leer flux
    StegerWarming,         ///< Steger-Warming flux
    LaxFriedrichs          ///< Lax-Friedrichs flux
  };

  /// Active numerical flux
  flux_type flux;

  // local methods
  void convection( vField &, vField & );
  void gradient( Element *, Element *, dVector &, dVector &, dVector & );
  void primitive_sides( vField & );
  void convective_flux( vField &, vField & );
  void compute_vorticity();

};

/// The Euler flux
template <class Scalar, class Ordinal>
class Euler::Flux : public DGM::Flux<Scalar,Ordinal> {
  const Scalar gamma;  ///< ratio of specific heats
public:
  Flux( Scalar gamma_ ) : gamma(gamma_) {}
  void evaluate( const CMC::Vector<Scalar,Size> &U,
                 const CMC::Vector<Scalar,Size> &N,
                 CMC::Vector<Scalar,Size> &F ) {
    // normal interior state
    const Scalar rl  = U[0];
    const Scalar rul = U[1]*N[0] + U[2]*N[2];
    const Scalar rvl = U[2]*N[0] - U[1]*N[2];
    const Scalar rEl = U[3];
    // compute primitive variables
    const Scalar ul = rul/rl;                      // normal velocity
    const Scalar vl = rvl/rl;                      // tangent velocity
    const Scalar pl = (gamma-1.0)*(rEl - 0.5*(rul*ul + rvl*vl));  // pressure
    const Scalar Hl = (rEl + pl)/rl;               // total enthalpy
    // normal flux
    F[0] = rl*ul;
    F[1] = (rul*ul+pl)*N[0] - (rvl*ul)*N[1];
    F[2] = (rul*ul+pl)*N[1] + (rvl*ul)*N[0];
    F[3] = ul*(rEl + pl);
  }
};

/// The Euler numerical flux
template <class Scalar, class Ordinal>
class Euler::NumericalFlux : public DGM::Flux<Scalar,Ordinal> {
  const Ordinal Nfields;
  const Scalar gamma;    ///< ratio of specific heats
  const Scalar gm1;      ///< gamma - 1.0
  const flux_type type;  ///< type of numerical fuls
public:
  NumericalFlux( Scalar gamma_, flux_type type_) :
    Nfields(4), gamma(gamma_), gm1(gamma-one), type(type_) {}
  void evaluate( const CMC::Vector<Scalar,Size> &Ul,
                 const CMC::Vector<Scalar,Size> &Ur,
                 const CMC::Vector<Scalar,Size> &N,
                 CMC::Vector<Scalar,Size> &Fl,
                 CMC::Vector<Scalar,Size> &Fr,
                 CMC::Vector<Scalar,Size> &Fh ) {
    // left state projected to normal
    const Scalar rl  = Ul[0];
    const Scalar rul = Ul[1]*N[0] + Ul[2]*N[1];
    const Scalar rvl = Ul[2]*N[0] - Ul[1]*N[1];
    const Scalar rEl = Ul[3];
    // left primative variables
    const Scalar ul = rul/rl;                             // normal velocity
    const Scalar vl = rvl/rl;                             // tangent velocity
    const Scalar pl = gm1*(rEl - pt5*(rul*ul + rvl*vl));  // pressure
    const Scalar Hl = (rEl + pl)/rl;                      // total enthalpy
    // left normal flux
    Fl[0] = rl*ul;
    Fl[1] = (rul*ul+pl)*N[0] - (rvl*ul)*N[1];
    Fl[2] = (rul*ul+pl)*N[1] + (rvl*ul)*N[0];
    Fl[3] = ul*(rEl + pl);
    // right state projected to normal
    const Scalar rr  = Ur[0];
    const Scalar rur = Ur[1]*N[0] + Ur[2]*N[1];
    const Scalar rvr = Ur[2]*N[0] - Ur[1]*N[1];
    const Scalar rEr = Ur[3];
    // right primitive variables
    const Scalar ur = rur/rr;                             // normal velocity
    const Scalar vr = rvr/rr;                             // tangent velocity
    const Scalar pr = gm1*(rEr - pt5*(rur*ur + rvr*vr));  // pressure
    const Scalar Hr = (rEr + pr)/rr;                      // total enthalpy
    // right normal flux
    Fr[0] = rr*ur;
    Fr[1] = (rur*ur+pr)*N[0] - (rvr*ur)*N[1];
    Fr[2] = (rur*ur+pr)*N[1] + (rvr*ur)*N[0];
    Fr[3] = ur*(rEr + pr);
    switch (type) {
    case LaxFriedrichs: {
      Scalar lmax = zero;
      CMC::Vector<Scalar,Size> lambda(Nfields);
      const Scalar cl = sqrt(gm1*(Hl - pt5*(ul*ul + vl*vl)));
      lambda[0] = ul-cl;
      lambda[1] = ul;
      lambda[2] = ul;
      lambda[3] = ul+cl;
      for(Ordinal j=0; j<Nfields; j++) lmax=max(lmax,fabs(lambda[j]));
      const Scalar cr = sqrt(gm1*(Hr - pt5*(ur*ur + vr*vr)));
      lambda[0] = ur-cr;
      lambda[1] = ur;
      lambda[2] = ur;
      lambda[3] = ur+cr;
      for(Ordinal j=0; j<Nfields; j++) lmax=max(lmax,fabs(lambda[j]));
      // Lax-Friedrichs flux
      Fh[0] = pt5 * ( Fl[0] + Fr[0] + lmax * ( Ul[0] - Ur[0] ) );
      Fh[1] = pt5 * ( Fl[1] + Fr[1] + lmax * ( Ul[1] - Ur[1] ) );
      Fh[2] = pt5 * ( Fl[2] + Fr[2] + lmax * ( Ul[2] - Ur[2] ) );
      Fh[3] = pt5 * ( Fl[3] + Fr[3] + lmax * ( Ul[3] - Ur[3] ) );
      break;
    } default:
      DGM::Comm::World->error("Illegal value of flux type");
      break;
    }
    return;
  }
};

} // namespace Reo

#endif  // REO_EULER_HPP
