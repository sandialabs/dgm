#ifndef REO_BURGERS_HPP
#define REO_BURGERS_HPP

/** \file Burgers.hpp
    \brief Burgers equation solver declarations
    \author S. Scott Collis
*/

// DGM includes
#include "ReoConfig.hpp"
#include "Domain.hpp"
#include "TimeInt.hpp"
#include "Field.hpp"
#include "vField.hpp"
using namespace DGM;

// Reo includes
#include "ReoConfig.hpp"

namespace Reo {

/// Burgers equation Domain
/** Solves the multi-dimensional Burgers equation. */
class Burgers : public Domain {

  int limit;                  ///< limiter flag

protected:

  dVector wk1;                ///< local workspace
  dVector wk2;                ///< local workspace
  dVector wk3;                ///< local workspace

public:

  /// \name IC declarations
  //@{
  class ShockIC;
  class CockburnShockIC;
  class StepIC;
  //@}

  /// \name BC declarations
  //@{
  class DirichletBC;
  class NeumannBC;
  class OutflowBC;
  class RobinBC;
  class DirichletControlBC;
  class NeumannControlBC;
  class RobinControlBC;
  class SteadyDirichletControlBC;
  class SteadyNeumannControlBC;
  class SteadyRobinControlBC;
  //@}

  /// \name Source term declarations
  //@{
  class DistributedControl;
  class SteadyDistributedControl;
  //@}

  /// \name local data
  //@{
  Scalar mu;             ///< viscosity
  vField Uv;             ///< viscous field
  //@}

  /// Constructor
  Burgers( DGM::ArgList &args, const DGM::Comm::Ptr = DGM::Comm::World );

  /// Destructor
  virtual ~Burgers() {
    // comm->cout() << "~Burgers()" << endl;
  }

  /// \name local helper methods
  //@{
  void parse_args( DGM::ArgList &args );
  void showUsage();
  //@}

  /// \name Override virtual Domain methods
  //@{
  virtual int plot(const string&);

  Scalar set_time_step( vField & );
  void zero_all_fields();
  void set_ic(vField &, string=".ic");

  void setup_BCdb( );
  void read_BCdb( ifstream & );
  BC* make_BC( ifstream &, string & );

  Source::Ptr make_Source( ifstream &, string & );
  void add_source(const vField &, vField &);
  //@}

  /// \name provide TimeInt interface
  //@{
  void time_derivative( vField &, vField & );
  //@}

protected:

  /// \name Local methods
  //@{
  void convection( vField &, vField & );
  void convection2d( vField &, vField & );
  void diffusion( vField &, vField &, vField & );
  void limiter( vField & );
  void convective_flux( vField &, vField & );
  void convective_flux_2d( vField &, vField & );
  void enforce_boundary_penalty( const vField &, vField &, const Scalar );
  void interior_penalty_flux( const vField &, const vField &,
                              vField &, const Scalar );
  //@}
};

} // namespace Reo

#endif  // REO_BURGERS_HPP
