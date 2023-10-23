#ifndef REO_IEULER_HPP
#define REO_IEULER_HPP

/** \file iEuler.hpp
    \brief Incompressible Euler equations
    \author Scott Collis
*/

// DGM includes
#include "Comm.hpp"
#include "Domain.hpp"
using namespace DGM;

// Reo includes
#include "ReoConfig.hpp"

namespace Reo {

/// Incompressible 2d Euler Domain
class iEuler : public Domain {

  dVector wk1;       ///< local workspace
  dVector wk2;       ///< local workspace

 protected:

 public:

  vField P;           ///< Pressure
  vField Pr;          ///< Pressure residual

  // BC declarations (definitions below)
  class WallBC;

  // IC declarations (definitions below)
  class OseenVortex;

  /// Constructor
  iEuler( DGM::ArgList &args, const DGM::Comm::Ptr = DGM::Comm::World );

  /// Destructor
  virtual ~iEuler() {}

  /// \name Provide Domain interface
  //@{
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
  //@}

  /// Compute the convection term
  void convection( vField &, vField & );

  /// Evaluate the gradient
  void gradient( Element *, Element *, dVector &, dVector &, dVector & );

  /// Supported numerical fluxes
  enum flux_type {
    LaxFriedrichs            ///< Lax-Friedrichs numerical flux
  };

  /// Compute the upwind flux contribution
  void convective_flux( vField &, vField & );

  /// Compute the vorticity and other derivative quantities
  void compute_vorticity();

  /// Evaluate pressure Poisson operator
  void Laplace( vField &, vField &, vField & );

  /// Evaluate the divergence of a vector field
  void divergence( vField &, vField &, vField &, int=0 );

  /// Evaluate the divergence of a vector field without jumps
  void local_divergence( vField &, vField &, vField &, int=0 );

  /// Evaluate the divergence in a weak sense
  void weak_divergence( vField &, vField &, vField &, int=0 );

  /// Compute the pressure projection operation
  void pressure_projection( vField &, vField &, vField &, vField & );

  /// Stabilize the Laplace operator
  void penalty_flux(const vField &Up, const vField &Us,
                    vField &Uf, const Scalar sigma, const char='-');
};

} // namespace Reo

#endif  // REO_IEULER_HPP
