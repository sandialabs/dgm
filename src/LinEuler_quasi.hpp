#ifndef REO_LINEULER_QUASI_HPP
#define REO_LINEULER_QUASI_HPP

/** \file  LinEuler_quasi.hpp
    \brief Linearized Euler equations in quasi-conservative variables. */

// Reo includes
#include "Euler.hpp"

namespace Reo {

/// Linearized Euler in quasi-conservative variables
class LinEuler_quasi : public Euler {

  dVector wk3, wk4;

 public:

  // BC declarations (definitions below)
  class LinWallBC;
  class LinStateBC;

  // Source terms
  class Sponge;

  vField Up;   // Solution field (primitive)
  vField Um;   // Mean flow field

  // constructor
  LinEuler_quasi( DGM::ArgList &args,
                  const DGM::Comm::Ptr = DGM::Comm::World );

  // override virtual Domain methods
  virtual int solve();
  virtual int plot(const string&);

  void time_derivative( vField &, vField & );

  void zero_all_fields();
  void set_ic( vField &, string=".ic" );

  void setup_BCdb( );
  void read_BCdb( ifstream & );
  BC* make_BC( ifstream &, string & );

  // override public Euler methods
  void convection( vField &, vField & );
  void convective_flux( vField &, vField & );

  void compute_vorticity();

  void enforce_mean_state_bc(vField &);

  void set_mean(vField &, const char c = 'p');
  void make_U(const vField &, const vField &, vField &);
  void get_Up(const vField &, const vField &, vField &);

  void enforce_bc(vField &);
  void enforce_flux_bc(vField &);

  void set_sponge(vField &,vField &);
};

} // namespace Reo

#endif  // REO_LINEULER_QUASI_HPP
