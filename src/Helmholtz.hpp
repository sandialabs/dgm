#ifndef REO_HELMHOLTZ_HPP
#define REO_HELMHOLTZ_HPP

/** \file Helmholtz.hpp
    \brief Basic Helmholtz equation module declaration
    \author S. Scott Collis and Axel Gerstenberger
    \copyright (c)2010 Sandia National Laboratories
*/

// DGM includes
#include "Comm.hpp"
#include "Domain.hpp"
#include "SolverML.hpp"
using namespace DGM;

// Reo includes
#include "ReoConfig.hpp"

namespace Reo {

/// Helmholtz equation
/** This module solves the Helmholtz equation using discontinuous Galerkin.

    \section Helmholtz_formulation Problem Formulation

    The Helmholtz equation is of the form

    \f[ \nabla^2 u + \omega^2 u = s \f]

    where \f$\omega=2\pi f\f$ is the angular frequency, \f$u\f$ is the
    solution variable, and \f$s\f$ is the source term.  Note that in
    general, \f$u\f$ and \f$s\f$ are complex valued.  Since the DGM
    library currently only supports Scalar variables, we solve this
    instead as a system of equations in terms of the real and imaginary
    parts of the solution

    \f[ \bU = \left\{\begin{array}{c} u_r \\ u_i \end{array}\right\}\f]

    and source term

    \f[ \bS = \left\{\begin{array}{c} s_r \\ s_i \end{array}\right\}\f]

    such that

    \f[ \nabla^2 \bU + \omega^2 \bU = \bS \f].

    The dispersion relation is given by

    \f[ \omega = k c \f]

    where \f$k=2\pi/\lambda\f$ is the wavenumber with wavelength
    \f$\lambda\f$ and \f$c\f$ is the phase velocity.
*/
class Helmholtz : public Domain {

  mutable dVector wk1;        ///< Local workspace
  mutable dVector wk2;        ///< Local workspace
  mutable dVector wk3;        ///< Local workspace

  bool restart;       ///< false forces solve to read an initial guess
  bool do_solve;      ///< allows to skip solving (used in convergence tests)

  // vField Uv;       ///< Extra vector Field (not needed)
  vField Sffile;      ///< Extra vector Field

  vField Omega;       ///< angular frequency field (scalar)

protected:

  static const LocalSize NfieldsT = 2;    ///< number of fields

public:

  std::map<int,Scalar> is_sponge_element; ///< sponge value for global ele id

  // Source term declarations
  class GaussianSource;
  class Sponge;

  // BC declarations
  class DirichletBC;

  DGM::Shared<Sponge>::Ptr sponge; ///< sponge for matrix computation

  // constructor
  Helmholtz( DGM::ArgList &args, const DGM::Comm::Ptr = DGM::Comm::World );

  // destructor
  virtual ~Helmholtz() {
    comm->cout() << "~Helmholtz()" << endl;
  }

  // local methods
  void parse_args( DGM::ArgList &args );
  void showUsage();

  // override virtual Domain methods
  virtual int solve();
  virtual int plot(const string&);
  void time_derivative( vField &, vField & ) {
    comm->error("Helmholtz::time_derivative not implemented");
  }
  void zero_all_fields();
  void set_ic( vField &, string=".ic" );

  // override BC methods
  void setup_BCdb( );
  BC* make_BC( ifstream &, string & );

  // override Source methods
  Source::Ptr make_Source( ifstream &, string & );
  void add_source(const vField &, vField & );

  /// Evaluation the action of the Helmholtz operator
  void action( vField &Us, vField &Uf );

  /// Sets the restart flag to true -- defaults to false in the constructor
  void set_restart() { restart = true; }

  /// Sets the medium field from file
  void set_medium(vField &Omega,
                  std::map<int,Scalar> &is_sponge_element) const;

private:

  void residual( vField &Us, vField &Ur );

  /// Compute the stabilization factor \f$C_{11}\f$
  Scalar computeC11(
    const Side * const Us_loc,
    const Side * const Us_adj
    ) const;

  /// Helper function to read input from file that is not in the params table
  template <typename T>
  T input(
    const string &key,  ///< parameter name in input file
    const T &defaultval ///< default value
    )
    {
      return DGM::read_from_input<T>(params, root+".inp", key, defaultval);
    }

  /// Returns a Scalar between [0.0,1.0)
  /** \note Use of rand() is discouraged as it is not portable, prefer
      random(). */
  static Scalar RandomReal01() {
#ifdef REO_HELMHOLTZ_USE_RAND
    const Scalar maxrand = RAND_MAX;
    const Scalar numrand(rand());
    const Scalar fluct = numrand/maxrand;     // range: [0,1]
#else
    // rand() is a poor random number generator that, amoung other bad
    // features, is not consistent across platforms.  random() performs much
    // better.
    const Scalar a = 0.0;
    const Scalar b = 1.0;
    const Scalar numrand =
      ((Scalar)::random()/((Scalar)(RAND_MAX)+(Scalar)(1.0)));
    const Scalar fluct = (b-a)*numrand+a;
#endif
    return fluct;
  }

  /// Random fluctuation functions in one space dimension
  static Scalar fluct1d(Scalar x, Scalar Lx, int nModes, Scalar alpha) {
    Scalar val = 0.0;
    for (int k = 1; k < (nModes +1); ++k) {
      val += alpha * sin(2.0* pi * k * ((x/Lx) - RandomReal01()));
    }
    return val;
  }

  /// Random fluctuation functions
  static Scalar fluct(
    const Scalar x,           ///< x in physical units
    const Scalar y,           ///< y in physical units
    const int nModes,         ///< wavenumbers
    const Scalar fluctuation  ///< fluctuation
    ) {
#ifdef REO_HELMHOLTZ_USE_RAND
    srand(2012);
#else
    srandom(2012);
#endif
    const Scalar Lx = one;
    const Scalar Ly = one;
    const Scalar alpha = sqrt(two/Scalar(nModes) * fluctuation);
    const Scalar p = fluct1d(x, Lx, nModes, alpha) *
                     fluct1d(y, Ly, nModes, alpha);
    return p;
  }

#ifdef DGM_USE_EPETRA
  // matrix implementation
  void Matrix_sides_bndry(const vField &PV,
                          Epetra_CrsMatrix &A) const;
  void RHS_sides_bndry(const vField &PV, const vField &Ff,
                       Epetra_Vector &b) const;
  void Matrix_sides_interior(const vField &PV,
                             Epetra_CrsMatrix &A) const;
  void RHS_sides_interior(const vField &Uf,
                          Epetra_Vector &b) const;
  void Matrix_domain_integrals(const vField &Uf,
                               Epetra_CrsMatrix &A) const;
  void RHS_domain_integrals(const vField &Uf,
                            Epetra_Vector &b) const;
  void buildMatrix( Epetra_CrsMatrix &A) const;
  void buildRHS( Epetra_Vector &b) const;
#endif

};

} // namespace Reo

#endif  // REO_HELMHOLTZ_HPP
