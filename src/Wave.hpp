#ifndef REO_WAVE_HPP
#define REO_WAVE_HPP

/** \file Wave.hpp
    \brief DGM wave equation module declaration
    \author Scott Collis
*/

// DGM includes
#include "Comm.hpp"
#include "Domain.hpp"
#include "Field.hpp"
#include "vField.hpp"

using namespace DGM;

namespace Reo {

/// The Wave (linear, homoentropic Euler) equation module
/**
   This 2-D Wave module is based on the linear, homentropic Euler Equations
   using primitive variables, \f$\rho\f$, \f$u\f$, and \f$v\f$ where \f$p =
   c^2*\rho\f$ and \f$c\f$ is the local sound speed.

   SSC: I believe that this is currently hacked for uniform base
   flow. Likewise, it assumes a uniform baseflow temperature which means
   that the sound spead is uniform.  This is bad and completely
   unnecessary.
*/
class Wave : public Domain {

  dVector wk1;             ///< first scratch space
  dVector wk2;             ///< second scratch space

 protected:

  /// Spported convective numerical fluxes
  enum flux_type {
    LaxFriedrichs
  };

 public:

  virtual ~Wave(){}
  // Source term declarations
  class RickerSource;
  class BerlageSource;

  Scalar Ma;                     ///< the mean flow reference Mach
  Scalar Pr;                     ///< Prandtl number
  Scalar gamma;                  ///< ratio of specific heats

  vField Up;                     ///< Solution field -- primitive variables
  vField Um;                     ///< Mean flow field

  /// constructor
  Wave( DGM::ArgList &args, const DGM::Comm::Ptr = DGM::Comm::World );

  /// \name override virtual Domain methods
  //@{
  virtual int solve();
  virtual int plot(const std::string&);
  void time_derivative( vField &U, vField &F );
  void zero_all_fields() ;

  void showUsage() {
    comm->cout()
      << "Wave Class Options \n"
      << "----------------------------------------------------------------\n"
      << "-gamma <double>" << '\t' << "Ratio of specific heats            \n"
      << "----------------------------------------------------------------\n";
    }
  void parse_args(DGM::ArgList &args);

  Scalar set_time_step( vField &U );
  void set_ic( vField &, std::string=".ic" );

  // overriding this is deprecated, it would be better to use the BC database
  void enforce_bc( vField & );
  // overriding this is deprecated, it would be better to use the BC database
  void enforce_flux_bc( vField & );

  Source::Ptr make_Source( std::ifstream &, std::string & );
  void add_source(const vField &, vField & );

  void write_bndry_stats();
  //@}

 private:

  /// \name local methods
  //@{
  void convection( vField &, vField & );
  void convective_flux( vField &, vField & );
  void compute_vorticity();
  void enforce_mean_state_bc(vField &);
  void set_mean(vField &);
  void make_U(vField &, const vField &, const vField &);
  void get_Up(vField &, const vField &, const vField &);
  //@}
};


// ===========================================================================
//                             Ricker Source
// ===========================================================================

/// Ricker in time with Gaussian in space
class Wave::RickerSource : public Source {

public:
  RickerSource(const std::string tag, std::ifstream &in) : Source(tag) {
    using std::pow;
    scan_lb(in);
    if (!(in >> x0 >> y0 >> t0 >> fp >> sigma >> amp))
      error("Wave::RickerSource::Cannot read data.");
    s2i = one/pow(sigma,2);
    scan_rb(in);
  }

  void apply(const Scalar time, const vField &, vField &F) {
    // cout << "RickerSource::apply() time = " << time << endl;
    // Only put the source term in the first Field which is scaled pressure
    for (LocalSize e=0; e<F[0]->ne; e++) { // Loop over elements
      Element* E = F[0] -> el[e];
      for (LocalSize q=0; q<E->qtot; q++)  // Loop over quadrature pts
        E->u[q] -= Ricker( (*E->C)[q], time );
    }
  }

  void adjoint_apply(const Scalar, const vField &, const vField &, vField &) {
    error("Wave::RickerSource::adjoint_apply() not implemented",1);
  }

private:
  Scalar x0, y0, t0, fp, sigma, amp;
  Scalar s2i;
  Scalar Ricker(const Point &C, const Scalar t) {
    using std::exp;
    using std::pow;
    Scalar T = pow(pi*fp*t,2);
    return amp*(one-two*T)*exp(-T)*                  // Ricker wavelet in time
      exp(-(pow(C.x-x0,2)+pow(C.y-y0,2))*s2i);       // Gaussian in space
  }
};
// ===========================================================================
//                         Berlage Source
// ===========================================================================

/// Berlage in time and Gaussian in space
class Wave::BerlageSource : public Source {
  // Aldridge's Berlage wavelet with default values:
  //   h=1, n=3, theta=-pi/2
  // where n determines the smoothness at t=0 and theta sets the shape
public:
  BerlageSource(const std::string tag, std::ifstream &in) :
    Source(tag), n(3), h(1), theta(-pi*pt5) {
    using std::pow;
    scan_lb(in);
    if (!(in >> x0 >> y0 >> fp >> amp))
      error("Wave::BerlageSource::Cannot read data.");
    s2i = one/pow(sigma,2);
    scan_rb(in);
  }

  void apply(const Scalar time, const vField &, vField &F) {
    // cout << "BerlageSource::apply() time = " << time << endl;
    // Only put the source term in the first Field which is scaled pressure
    for (LocalSize e=0; e<F[0]->ne; e++) { // Loop over elements
      Element* E = F[0] -> el[e];
      for (LocalSize q=0; q<E->qtot; q++)  // Loop over quadrature pts
        E->u[q] -= Berlage( (*E->C)[q], time );
    }
  }

  void adjoint_apply(const Scalar, const vField &, const vField &, vField &) {
    error("Wave::BerlageSource::adjoint_apply() not implemented",1);
  }

private:
  int n;
  Scalar x0, y0, h, fp, theta, sigma, amp;
  Scalar s2i;
  Scalar Berlage(const Point &C, const Scalar t) {
    using std::cos;
    using std::exp;
    using std::pow;
    Scalar Ht = t>zero ? one : zero;
    Scalar omegat = two*pi*t;
    return amp*Ht*pow(omegat,n)*
      exp(-h*omegat)*cos(omegat+theta)*         // Berlage wavelet in time
      exp(-(pow(C.x-x0,2)+pow(C.y-y0,2))*s2i);  // Gaussian in space
  }
};

} // namespace Reo

#endif // REO_WAVE_HPP
