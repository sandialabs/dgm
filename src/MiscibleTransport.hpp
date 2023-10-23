#ifndef REO_MISCIBLE_TRANSPORT_HPP
#define REO_MISCIBLE_TRANSPORT_HPP

/** \file MiscibleTransport.hpp
    \brief Multi-component miscible displacement transport 
    \author Scott Collis
*/

// DGM includes
#include "Comm.hpp"
#include "Domain.hpp"
#include "Field.hpp"
#include "vField.hpp"
#include "Multi_Component_Transport.hpp"
using namespace DGM;

namespace Reo {

// forward declarations
class Darcy;

/// Multi-Component Miscible Transport
class Multi_Comp_Misc_Trans : public Multi_Comp_Trans {

//  mutable dVector wk1;  ///< local workspace
//  mutable dVector wk2;  ///< local workspace
//  mutable dVector wk3;  ///< local workspace
//  mutable dVector wk4;  ///< local workspace

public:

//  // BC declarations
//  class DirichletBC;
//  class DirichletBC_Function;
//  class UnsteadyDirichletBC;
//  class NeumannBC;
//  class OutflowBC;
//  class RobinBC;
//  class DirichletControlBC;
//  class NeumannControlBC;
//  class RobinControlBC;
//  class SteadyDirichletControlBC;
//  class SteadyNeumannControlBC;
//  class SteadyRobinControlBC;
//
//  // Source term declarations
//  class DistributedControl;
//  class SteadyDistributedControl;
//  class TransientManufactured;
//  class TransientGaussian;
//  class DiracRicker;

protected:

//  // material properties
//  Scalar eff_diff;          ///< effective diffusivity of aquifer = tau * D
//  std::vector<Scalar> rho;  ///< densities for ALL species (NFIELD + 1)
//                            ///< order in rho matters!
//  Scalar porosity_phi;      ///< porosity coefficient
//
//  int p;                    ///< polynomial_order
//
//  Scalar tmax;              ///< final physical computation time
//
//  vField Cf;                ///< convective field
//  vField Vf;                ///< work vector for the diffusive flux field
//
//  typedef DGM::Shared<Reo::Darcy_Misc>::Ptr DarcyPtr;
//  Darcy_Misc *darcy;        ///< Associated Darcy flow object
//  const bool CO2_seq;       ///< is true, if Darcy problem (pointer) is present

  Scalar R;                 ///< logarithm of mobility ratio

public:
  /// Constructor
  Multi_Comp_Misc_Trans( DGM::ArgList &args,
                         const DGM::Comm::Ptr = DGM::Comm::World,
                         const bool coupled_darcy = false );

  /// Destructor
  virtual ~Multi_Comp_Misc_Trans() {
    cout << "~Multi_Comp_Misc_Trans()" << endl;
  }

  // local methods
  // void parse_args( DGM::ArgList &args );
  void showUsage();

  // override virtual Domain methods
  virtual int plot(const string&);
  void make_contiguous();

  void prestep( vField&, const Ordinal, const Ordinal, const Scalar );
  virtual void time_derivative( vField &, vField & );

  Scalar set_time_step( vField &Uf );
  Scalar compute_critical_timestep() const;
  void zero_all_fields();
  void set_ic(vField &, string=".ic");

  BC* make_BC( ifstream &, string & );

  void write_bndry_stats();

  Source::Ptr make_Source( ifstream &, string & );
  void add_source(const vField &, vField &);

  virtual int solve();

protected:

  void convection( const vField & , vField &, vField & ) const;
  void constant_convection( const vField &, vField & ) const;
  void variable_convection_Euler_Lagrange( const vField &, vField & ) const;

  void diffusion( const vField &, vField &, vField & );
  void convective_flux( const vField &, vField &, vField & ) const;

  void interior_penalty_boundary_correction( const vField &,
      vField &, const Scalar ) const;
  void average_flux_plus_interior_penalty( const vField &,
      const vField &, vField &, const Scalar ) const;

  Scalar compute_h_n(const Side *const Xs) const;

private:

  void flux_in_one_sd(
      const Element *const Ue, const Element *const Fe,
      const char sd, dVector &X1x) const;

  /// Helper function to read input from file that is not in the params table
  template <typename T>
  T read_from_input(
      const string &file, ///< input file
      const string &key,  ///< parameter name in input file
      const T &defaultval ///< default value
      )
  {
    return DGM::read_from_input<T>(params, file, key, defaultval);
  }

  /// Helper function to read input from file that is not in the params table
  template <typename T>
  T input(
      const string &key,  ///< parameter name in input file
      const T &defaultval ///< default value
      )
  {
    return DGM::read_from_input<T>(params, root+".inp", key, defaultval);
  }

  void setup_convective_field();
  void read_convective_field(vField &, string);
  void post_process_initial_field(vField &F, const bool proj);

  void compute_average_density( const vField &Uf, vField &rhomixf ) const;
  void compute_total_mobility( const vField &Uf, const vField &Kabs,
      vField &Lt ) const;

  /// Compute Source term for Darcy flow
  void compute_darcy_source( vField &Sf ) const;

  /// Adds in the viscous flux
  void add_viscflux_to_source(
      const Field &Vf, const Scalar rho_alpha, const Scalar rho_extra,
      Field &Sf) const;

  /// Compute viscous flux for one element
  void compute_gradS_per_element(
      const Element *const,
      const Element *const,
      Element *const,
      dVector &
  ) const;

  /// compute penalty factor C_11
  Scalar compute_C11(
      const Scalar stab,
      const Scalar h_n
      ) const {
    return stab*porosity_phi*eff_diff/h_n;
  }

  /// compute element Peclet number (one value per element)
  void compute_element_Peclet_number(
      vField &Pef) const ;

  /// set circular initial condition for mass fraction X_1
  Scalar circular_mass_fraction(const Element *const Xe, Ordinal q,
                                Scalar radius, Scalar eps,
                                Scalar innerval) const;

  bool solve_Darcy; ///< allows to selectively turn on and of the Darcy solution

};

} // namespace Reo

#endif  // REO_MISCIBLE_TRANSPORT_HPP
