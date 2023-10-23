#ifndef REO_MAXWELL_BC_HPP
#define REO_MAXWELL_BC_HPP

/** \file  MaxwellBC.hpp
    \brief Maxwell equation boundary conditions
    \author Scott Collis
*/

// DGM includes
#include "BC.hpp"
#include "Source.hpp"
#include "Ctrl.hpp"

using DGM::BC;
using DGM::Source;
using DGM::Ctrl;

namespace Reo {

//===========================================================================
//                              Solid Wall
//===========================================================================

/// Wall boundary condition for 2d Maxwell equations
class Maxwell::WallBC : public BC {
public:
  /// default constructor
  WallBC( const string t ) : BC(t) { }
  /// construct from an input file stream
  WallBC( const string t, ifstream &in) : BC(t) {
    scan_lb(in);
    // parse arguments here
    scan_rb(in);
  }
  inline void apply( const Scalar, const vField & ) ;
  inline void apply_flux( const Scalar, const vField & ) ;

  inline void adjoint_apply( const Scalar, const vField &, const vField & ) ;
  inline void adjoint_apply_flux( const Scalar, const vField &,
                                  const vField & ) ;
};

void Maxwell::WallBC::apply( const Scalar t, const vField &F ) {
  static bool firstTime=true;
  if (firstTime) {
    warning("Maxwell::WallBC::apply() not implemented.");
    firstTime=false;
  }
}

void Maxwell::WallBC::apply_flux( const Scalar t, const vField &F ) {
  static bool firstTime=true;
  if (firstTime) {
    warning("Maxwell::WallBC::apply_flux() not implemented.");
    firstTime=false;
  }
}

void Maxwell::WallBC::adjoint_apply( const Scalar t, const vField &state,
                                     const vField &adjoint) {
  error("Maxwell::WallBC::adjoint_apply() not implemented.");
}

void Maxwell::WallBC::adjoint_apply_flux( const Scalar t, const vField &state,
                                          const vField &adjoint) {
  error("Maxwell::WallBC::adjoint_apply_flux() not implemented.");
}

} // namespace Reo

#endif  // REO_MAXWELL_BC_HPP
