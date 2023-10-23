#ifndef REO_ADV_DIFF_HPP
#define REO_ADV_DIFF_HPP

/** \file Adv_Diff.hpp
    \brief Advection diffusion declaration
    \author Scott Collis
    \copyright 2003 Rice University
    \copyright 2014 Sandia National Laboratories
*/

// DGM includes
#include "Comm.hpp"
#include "Domain.hpp"
#include "Field.hpp"
#include "vField.hpp"
using namespace DGM;

// Reo includes
#include "ReoConfig.hpp"

// Trilinos includes
#ifdef REO_TEST_SACADO
#include "Sacado.hpp"
#endif

namespace Reo {

#ifdef REO_TEST_SACADO
/// Test function for differentiation
template <typename ScalarT>
ScalarT func(const ScalarT &a, const ScalarT &b, const ScalarT &c) {
  ScalarT r = c*std::log(b+1.0)/std::sin(a);
  return r;
}

/// Templated Lax-Friedrichs flux
template <typename ScalarT>
ScalarT LF_flux(const ScalarT &ul, const ScalarT &ur,
                const ScalarT &cl, const ScalarT &cr) {
  ScalarT lambda = 0.5*(cl+cr);
  ScalarT flux = 0.5*( cr*ul + cl*ur + lambda * ( ul - ur ) );
  return flux;
}

/// Templated vector Lax-Friedrichs flux
/** \note this is just a stub for now. */
template <typename ScalarT>
ScalarT LF_flux(const CMC::Vector<ScalarT, int> &ul,
                const CMC::Vector<ScalarT, int> &ur) {
  ScalarT flux = ul[0] + ur[0];
  return flux;
}
#endif

/// Advection Diffusion Domain
class Adv_Diff : public Domain {

  dVector wk1;  ///< local workspace
  dVector wk2;  ///< local workspace
  dVector wk3;  ///< local workspace

public:

  // BC declarations
  class DirichletBC;
  class UnsteadyDirichletBC;
  class NeumannBC;
  class OutflowBC;
  class RobinBC;
  class DirichletControlBC;
  class NeumannControlBC;
  class RobinControlBC;
  class SteadyDirichletControlBC;
  class SteadyNeumannControlBC;
  class SteadyRobinControlBC;

  // Source term declarations
  class DistributedControl;
  class SteadyDistributedControl;
  class TransientGaussian;
  class DiracRicker;

  Scalar mu;              ///< Viscosity coefficient
  Scalar cx;              ///< Wave speed in x-direction
  Scalar cy;              ///< Wave speed in y-direction
  Scalar cz;              ///< Wave speed in z-direction

  bool cfield;            ///< Convective field flag (true to use field)

  int fv;                 ///< Non-zero means use finite volume reconstruction

  vField Uv;              ///< Viscous vector field
  vField Uc;              ///< Convective vector field

  /// Constructor
  Adv_Diff( DGM::ArgList &args, const DGM::Comm::Ptr = DGM::Comm::World,
            const int p_inc=0 );

  /// Destructor
  virtual ~Adv_Diff() {
    if(verbosity()) comm->cout() << "~Reo::Adv_Diff()" << endl;
  }

  /// \name Provide Domain interface
  //@{
  void parse_args( DGM::ArgList &args );
  void showUsage();
  void make_contiguous();
  void time_derivative( vField &, vField & );
  virtual int plot(const string&);
  Scalar set_time_step( vField & );
  void zero_all_fields();
  void set_ic(vField &, string=".ic");
  //@}

  /// \name Boundary Condition interface
  //@{
  void setup_BCdb( );
  void read_BCdb( ifstream & );
  BC* make_BC( ifstream &, std::string & );
  //@}

  /// \name Source term interface
  //@{
  Source::Ptr make_Source( ifstream &, string & );
  void add_source(const vField &, vField &);
  //@}

protected:

  /// \name Local methods
  //@{
  void convection( vField &, vField & );
  void constant_convection( vField &, vField & );
  void variable_convection( vField &, vField & );
  void convective_flux( vField &, vField & );

  void diffusion( vField &, vField &, vField & );
  void linear_reconstruction( vField &, vField &, vField & );

  void enforce_hard_bc(vField &);
  void enforce_boundary_penalty( const vField &, vField &, const Scalar );
  void interior_penalty_flux( const vField &, const vField &,
                              vField &, const Scalar );
  //@}

private:

#ifdef DGM_JSON_TO_TABLE
  /// Type for holding a hierarchical path
  typedef std::vector<std::string> JSON_PATH;
  /// Type for converting from DGM::Table to JSON::Value
  typedef std::map<std::string,JSON_PATH> TBL_TO_JSON;

  /// Object that maps DGM::Table keys to JSON keys
  static TBL_TO_JSON tbl_to_json;

  /// Setup and return the tbl_to_json mapping
  static inline TBL_TO_JSON & table_to_json_map() {
    using namespace std;
    if (tbl_to_json.empty()) {
      JSON_PATH P(2);
#if !defined(DGM_INPUT_SPEC) || DGM_INPUT_SPEC == 1
      // Version 1 of the input specification matches identically the original
      // DGM parameters
      P[0] = "Advection diffusion";
      P[1] = "cfield";    tbl_to_json["cfield"]=P;
      P[1] = "cx";        tbl_to_json["cx"]=P;
      P[1] = "cy";        tbl_to_json["cy"]=P;
      P[1] = "cz";        tbl_to_json["cz"]=P;
      P[1] = "vis";       tbl_to_json["vis"]=P;
      P[1] = "fv";        tbl_to_json["fv"]=P;
#elif DGM_INPUT_SPEC == 2
      // Version 2 of the input specification uses long names and maps the
      // original DGM parameter names to the long names
      P[0] = "Advection diffusion";
      P[1] = "Variable convective field";          tbl_to_json["cfield"]=P;
      P[1] = "X wave speed";                       tbl_to_json["cx"]=P;
      P[1] = "Y wave speed";                       tbl_to_json["cy"]=P;
      P[1] = "Z wave speed";                       tbl_to_json["cz"]=P;
      P[1] = "Viscosity";                          tbl_to_json["vis"]=P;
      P[1] = "Finite volume reconstruction";       tbl_to_json["fv"]=P;
#else
#error Undefined value for REO_INPUT_SPEC
#endif
    }
    return tbl_to_json;
  }
#endif

};  // class Adv_Diff

} // namespace Reo

#endif  // REO_ADV_DIFF_HPP
