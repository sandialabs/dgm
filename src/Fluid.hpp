#ifndef REO_FLUID_HPP
#define REO_FLUID_HPP

/** \file Fluid.hpp
    \brief Declares and defines the Reo Fluid Material class
    \author Scott Collis
*/

// DGM includes
#include "Material.hpp"
using namespace DGM;

namespace Reo {

//============================================================================
// Fluid is a abstract base class that represents fluid properties
//============================================================================

/// Abstract Fluid Material
class Fluid : public Material {
public:
  /// Constructor
  Fluid(const string iname="Fluid") : Material(iname) { }
  virtual ~Fluid() { }
  // virtual methods
  virtual Scalar mu(Scalar T) const = 0;       ///< dynamic viscosity
  virtual Scalar lambda(Scalar T) const = 0;   ///< second coefficient
  virtual Scalar kappa(Scalar T) const = 0;    ///< thermal diffusivity
};

/// General divariant gas
class DivariantGas : public Fluid {
public:
  DivariantGas(const string iname="DivariantGas") : Fluid(iname) { }
  virtual ~DivariantGas() { }
};

/// Ideal gas equation of state
class IdealGas : public Fluid {
protected:
  Scalar Gamma;
  Scalar rgas;
  Scalar Ma_ref;
public:
  IdealGas(Scalar g, Scalar r, const string iname="IdealGas") :
    Fluid(iname), Gamma(g), rgas(r) {
    Ma_ref = sqrt(1.0/(Gamma*rgas));
  }
  virtual ~IdealGas() {};
  // Cv and Cp can be functions of temperature
  virtual Scalar cv(Scalar T) const = 0;
  virtual Scalar cp(Scalar T) const = 0;
  virtual Scalar Rgas() const {return rgas;}
  virtual Scalar gamma() const {return Gamma;}
  virtual Scalar Ma() const {return Ma_ref;}
};

/// Calorically perfect gas
class PerfectGas : public IdealGas {
  Scalar Cv, Cp;
public:
  PerfectGas(Scalar g, Scalar r, const string iname="PerfectGas") :
    IdealGas(g,r,iname), Cv(rgas/(Gamma-1.0)),Cp(Gamma*Cv) {}
  virtual ~PerfectGas() {};
  // Cv and Cp are constants
  Scalar cv(Scalar T) const {return Cv;}
  Scalar cp(Scalar T) const {return Cp;}
};

/// Perfect gass with constant fluid properties (viscosities)
class ConstProp : public PerfectGas {
protected:
  Scalar Pr;                      // Prandtl number
  Scalar Mu;                      // reference first coefficient of viscosity
  Scalar Lambda;                  // reference second coef. of viscosity
public:
  ConstProp(const Scalar gammai=1.4, const Scalar Rgasi=287.0,
            const Scalar Pri=0.72, const Scalar Mui=1.716e-5,
            const string iname="ConstPropPerfectGas") :
    PerfectGas(gammai,Rgasi,iname), Pr(Pri), Mu(Mui) { }
  virtual ~ConstProp() {};

  // should have a constructor from a file

  // methods
  void set( const Scalar gammai, const Scalar Rgasi, const Scalar Pri,
            const Scalar Mui ) {
    Gamma = gammai;
    rgas  = Rgasi;
    Pr    = Pri;
    Mu    = Mui;
  }
  Scalar mu(Scalar T) const { return Mu; }
  Scalar lambda(Scalar T) const { return 1.5*mu(T); }
  Scalar kappa(Scalar T) const { return Pr*mu(T); }
};

/// Perfect gass with power law for viscosities
class PowerLaw : public ConstProp {
  Scalar S;                       // Sutherland's constant
  Scalar Tref, Pref;              // reference temperature and pressure
public:
  PowerLaw(const Scalar gammai=1.4, const Scalar Rgasi=287.0,
           const Scalar Pri=0.72, const Scalar Mui=1.716e-5,
           const Scalar Trefi=110.0, const Scalar Prefi =101000.0,
           const Scalar Si=111, const string iname="PowerLawConstProp" ) :
    ConstProp(gammai,Rgasi,Pri,Mui,iname), S(Si), Tref(Trefi), Pref(Prefi) { }
  virtual ~PowerLaw() {};

  // should add a constructor from a file

  // This is taken from LNS3D
  void set( const Scalar Re ) {
    Scalar mu0    = 1.715336725523065e-05;     // (AIR) from White
    Scalar T0     = 273.0;                     // K
    Scalar S0     = 110.4;                     // K
    Scalar rgas   = 286.6;
    Scalar muref  = mu0*pow(Tref/T0,1.5)*(T0+S0)/(Tref+S0);
    Scalar rhoref = Pref / ( rgas * Tref );
    Scalar Uref   = Re / rhoref * muref;
    cout << "Uref * Lref= " << Uref;
    S0 = S0 / Tref;                           // nondimensionalize
  }

  Scalar mu(Scalar T) const {
    return Mu*pow(T/Tref,1.5)*(Tref+S)/(T+S);
  }
  Scalar lambda(Scalar T) const { return 1.5*mu(T); }
  Scalar kappa(Scalar T) const { return Pr*mu(T); }
};

/// Perfect gas with Sutherland's law for viscosity
class Sutherland : public ConstProp {
  Scalar S;                       // Sutherland's constant
  Scalar Tref, Pref;              // reference temperature and pressure
public:
  Sutherland(const Scalar gammai=1.4, const Scalar Rgasi=287.0,
             const Scalar Pri=0.72, const Scalar Mui=1.716e-5,
             const Scalar Trefi=110.0, const Scalar Prefi =101000.0,
             const Scalar Si=111, const string iname="Sutherland" ) :
    ConstProp(gammai,Rgasi,Pri,Mui,iname), S(Si), Tref(Trefi), Pref(Prefi) { }

  // should add a constructor from a file

  // This is taken from LNS3D
  void set( const Scalar Re ) {
    Scalar mu0    = 1.715336725523065e-05;     // (AIR) from White
    Scalar T0     = 273.0;                     // K
    Scalar S0     = 110.4;                     // K
    Scalar rgas   = 286.6;
    Scalar muref  = mu0*pow(Tref/T0,1.5)*(T0+S0)/(Tref+S0);
    Scalar rhoref = Pref / ( rgas * Tref );
    Scalar Uref   = Re / rhoref * muref;
    cout << "Uref * Lref= " << Uref;
    S0 = S0 / Tref;                           // nondimensionalize
  }

  Scalar mu(Scalar T) const {
    return Mu*pow(T/Tref,1.5)*(Tref+S)/(T+S);
  }
  Scalar lambda(Scalar T) const { return 1.5*mu(T); }
  Scalar kappa(Scalar T) const { return Pr*mu(T); }
};

} // namespace Reo

#endif  // REO_FLUID_HPP
