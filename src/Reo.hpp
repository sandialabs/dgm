#ifndef REO_HPP 
#define REO_HPP

/** \file Reo.hpp
    \brief The Reo Flow and Transport Module
    \author Scott Collis
*/

// system includes
#include <stdexcept>
#include <string>
#include <strings.h>

// DGM includes
#include "String.hpp"

/// Flow and transport module for forward simulation and optimal control
/** The Reo module includes Advection-Diffusion, Burgers, Euler,
    Navier-Stokes, LES, Helmholtz, Darcy and Poisson equations built
    upon the DGM library   */
namespace Reo {

  /// Number of equation types
#ifndef DGM_REMOVE_FOR_RELEASE
  static const unsigned NumEqntype = 26;
#else
  static const unsigned NumEqntype = 25;
#endif

  /// Type of PDE that can be defined on a Reo Domain.
  /** Note that linearized PDEs should have values that are 100+ the
      non-linearized value. */
  enum EqnType {
    ADV_DIFF=0,               ///< Advection-Diffusion equation
    EULER=1,                  ///< 2d Euler equations
    NAVIER_STOKES=2,          ///< 2d Navier-Stokes equations
    WAVE=3,                   ///< 2d wave equation
    LINEULER_QUASI=4,         ///< Conservative linearized Euler equations (2d)
    LINEULER_PRIM=5,          ///< Primative linearized Euler equations (2d)
    BURGERS=6,                ///< Burgers equation
    TURBULENCE=7,             ///< Reynolds Averaged Navier-Stokes
    EULER3D=8,                ///< 3d Euler equations
    NAVIER_STOKES3D=9,        ///< 3d Navier-Stokes equations
    COUPLE=10,                ///< Multi-physics coupling demonstration
    IEULER=11,                ///< Incompressible Euler equations
    INS=12,                   ///< Incompressible Navier-Stokes equations
    EULERDC=18,               ///< 2d Euler with discontinuity capturing
    HELMHOLTZ=22,             ///< Helmholtz equation
    DARCY=24,                 ///< Darcy for gravity-driven multiphase flow
    POISSON=27,               ///< Poisson solver
    MAXWELL=28,               ///< Maxwell equations
#ifndef DGM_REMOVE_FOR_RELEASE
    SHALLOW=30,               ///< Shallow water equations
#endif // DGM_REMOVE_FOR_RELEASE
    MULTI_COMP_MISC_TRANS=49, ///< Miscible displacement transport
    MULTI_MAT_ADV_DIFF=50,    ///< Multiple material advection-diffusion
    MISC_DISPL_FLOW=72,       ///< Coupled misc. displacements (72 = 49 + 23)
    DENS_DRIVEN_CO2_SEQ=74,   ///< Coupled CO_2 dissolution (74 = 50 + 24)
    LINADV_DIFF=100,          ///< Linearized advection-diffusion equation
    LIN_NS_QUASI=102,         ///< Linearized Navier_Stokes equation
    LINBURGERS=106            ///< Linearized Burgers equation
  };

  /// Map Reo::EqnType enums to sequential integer
  /** Convert non-sequential physics enums (Reo.hpp) into
      sequential numbers for use as array indices. */
  inline int p2i(const EqnType p) {
    switch (p) {
      case Reo::ADV_DIFF:              return 0;
      case Reo::EULER:                 return 1;
      case Reo::NAVIER_STOKES:         return 2;
      case Reo::WAVE:                  return 3;
      case Reo::LINEULER_QUASI:        return 4;
      case Reo::LINEULER_PRIM:         return 5;
      case Reo::BURGERS:               return 6;
      case Reo::TURBULENCE:            return 7;
      case Reo::EULER3D:               return 8;
      case Reo::NAVIER_STOKES3D:       return 9;
      case Reo::COUPLE:                return 10;
      case Reo::IEULER:                return 11;
      case Reo::INS:                   return 12;
      case Reo::EULERDC:               return 13;
      case Reo::HELMHOLTZ:             return 14;
      case Reo::POISSON:               return 15;
#ifndef DGM_REMOVE_FOR_RELEASE
      case Reo::SHALLOW:               return 16;
#endif // DGM_REMOVE_FOR_RELEASE
      case Reo::LINADV_DIFF:           return 17;
      case Reo::LINBURGERS:            return 18;
      case Reo::DARCY:                 return 19;
      case Reo::MULTI_COMP_MISC_TRANS: return 20;
      case Reo::MULTI_MAT_ADV_DIFF:    return 21;
      case Reo::MISC_DISPL_FLOW:       return 22;
      case Reo::DENS_DRIVEN_CO2_SEQ:   return 23;
      case Reo::MAXWELL:               return 24;
      case Reo::LIN_NS_QUASI:          return 25;
      default:
        throw std::logic_error("Unknown Reo::EqnType");
    }
    return -1;
  }

  /// Map Reo::EqnType enums to sequential integer
  /** Convert non-sequential physics enums (Reo.hpp) into
      sequential numbers for use as array indices. */
  inline EqnType i2p(const int i) {
    switch (i) {
      case 0 : return Reo::ADV_DIFF;
      case 1 : return Reo::EULER;
      case 2 : return Reo::NAVIER_STOKES;
      case 3 : return Reo::WAVE;
      case 4 : return Reo::LINEULER_QUASI;
      case 5 : return Reo::LINEULER_PRIM;
      case 6 : return Reo::BURGERS;
      case 7 : return Reo::TURBULENCE;
      case 8 : return Reo::EULER3D;
      case 9 : return Reo::NAVIER_STOKES3D;
      case 10: return Reo::COUPLE;
      case 11: return Reo::IEULER;
      case 12: return Reo::INS;
      case 13: return Reo::EULERDC;
      case 14: return Reo::HELMHOLTZ;
      case 15: return Reo::POISSON;
#ifndef DGM_REMOVE_FOR_RELEASE
      case 16: return Reo::SHALLOW;
#endif // DGM_REMOVE_FOR_RELEASE
      case 17: return Reo::LINADV_DIFF;
      case 18: return Reo::LINBURGERS;
      case 19: return Reo::DARCY;
      case 20: return Reo::MULTI_COMP_MISC_TRANS;
      case 21: return Reo::MULTI_MAT_ADV_DIFF;
      case 22: return Reo::MISC_DISPL_FLOW;
      case 23: return Reo::DENS_DRIVEN_CO2_SEQ;
      case 24: return Reo::MAXWELL;
      case 25: return Reo::LIN_NS_QUASI;
      default:
        const std::string M = "Index out of range:"+DGM::asString(i)+
          " Must be less than "+DGM::asString(NumEqntype)+" in i2p.";
        throw std::logic_error(M);
    }
    return Reo::ADV_DIFF;
  }

  static const char *EqnTypeNames[NumEqntype] = {
    "Advection diffusion",
    "Euler",
    "Navier Stokes",
    "Wave",
    "Linear Euler quasi",
    "Linear Euler prim",
    "Burgers",
    "Turbulence",
    "Euler 3d",
    "Navier Stokes 3d",
    "Couple",
    "IEuler",
    "INS",
    "Euler DC",
    "Helmholtz",
    "Poission",
#ifndef DGM_REMOVE_FOR_RELEASE
    "Shallow",
#else 
    "",
#endif // DGM_REMOVE_FOR_RELEASE
    "Linear advection diffusion",
    "Linear Burgers",
    "Darcy",
    "Multi comp misc trans",
    "Multi material advection diffusion",
    "Misc displ flow",
    "Density driven CO2 seq",
    "Maxwell",
    "Linear NS quasi"
  };

  /// Map Reo::EqnType enums to string
  /** Convert non-sequential physics enums (Reo.hpp) into strings. */
  inline std::string p2s(const EqnType p) {
    const char *name = EqnTypeNames[p2i(p)];
    return name;
  }

  /// Map string to Reo::EqnType enum
  /** Convert physics strings into enum. */
  inline EqnType s2p(const std::string s) {
    const char *c_str = s.c_str();
    for (unsigned i=0; i<NumEqntype; ++i) 
      if (!strcasecmp(c_str,EqnTypeNames[i])) return i2p(i);
    std::string M = "Unknown physics string:"+s+" in s2p. Options are:";
    for (unsigned i=0; i<NumEqntype; ++i) M+=std::string(", ")+EqnTypeNames[i];
    throw std::logic_error(M);
    return Reo::ADV_DIFF;
  }

} // namespace Reo

#endif  // REO_HPP
