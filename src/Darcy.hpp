#ifndef REO_DARCY_HPP
#define REO_DARCY_HPP

/** \file Darcy.hpp
    \brief Basic Darcy equation module declaration
    \author Scott Collis
*/

// system includes
#include <boost/array.hpp>

// DGM includes
#include "Comm.hpp"
#include "Domain.hpp"
#include "SolverML.hpp"
using namespace DGM;

// Reo includes
#include "ReoConfig.hpp"

namespace Reo {

/// Two-dimensional Darcy equation
/** This module solves the 2d Darcy equation using discontinuous Galerkin.

    \section Darcy_formulation Problem Formulation

    The Darcy equation is of the form

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
class Darcy : public Domain {

  mutable dVector wk1;   ///< Local workspace
  mutable dVector wk2;   ///< Local workspace
  mutable dVector wk3;   ///< Local workspace

public:

  bool restart;       ///< false forces solve to read an initial guess
  bool do_solve;      ///< allows to skip solving (used in convergence tests)

  vField Uv;          ///< Extra vector Field
  vField Un;          ///< Extra vField to store old time-step solution (n)
  vField Uo;          ///< Another vector Field

  vField Kabs;        ///< Absolute rock permeability vector field
  vField Lt;          ///< Total mobility vector field: Lt = Lambda*Kabs

  vField Gf;          ///< Premultiplicative gravity factor vector field
  vField Sf;          ///< Source vector filled by Advect_Diff (scalar)

protected:

  vField Sffile;      ///< Source vector from file (scalar)

  static const LocalSize NfieldsT = 1;  ///< Number of fields

  boost::array<Scalar,3> gravity;  ///< gravity vector

  boost::array<Scalar,3> u_misc;   ///< velocity vector for miscible flow

public:

  // BC declarations

  /// Constant valued Dirichlet boundary condition
  class DirichletBC : public BC {
  protected:
    Scalar value;
  public:
    DirichletBC(const string t, const Scalar v=0) : BC(t), value(v) { }
    DirichletBC(const string t, ifstream &in) : BC(t) {
      scan_lb(in);
      if (!(in >> value))
        error("Darcy::DirichletBC: could not read value");
      scan_rb(in);
    }
    void apply( const Scalar, const vField & ) ;
    void apply_flux( const Scalar, const vField & ) ;
    void matrix_apply( const Scalar, const vField & ) ;
    void matrix_apply_flux( const Scalar, const vField & ) ;

  };
  //===========================================================================
  //                         Function Dirichlet BC
  //===========================================================================

  /// Dirichlet boundary condition using a prescribed function
  class DirichletBC_Function : public FuncBC {
  public:
    /// Constructor
    DirichletBC_Function(const string t, ifstream &in, int ndof=0) :
      FuncBC(t,in,ndof) {}
    void apply(const Scalar t, const vField &F) {
      //cout << "DirichletBC_Function::apply(...)" << endl;
      assert( 1 == expr.size() );
      evaluate(F);
      LocalSize start=0;
      dVector wk;
      for (LocalSize n=0; n<F[0]->nbc; ++n) {    // loop over field boundaries
        if (F[0]->bc[n]->type == type ) {
          for (vField::size_type i=0; i<F.size(); ++i) {
            Side *B = F[i]->bc[n]->B;
            B->u = F[i]->bc[n]->S->u;
            wk.alias(s,start,B->qtot());
            scale(-one,B->u);
            daxpy(2.0,wk,B->u);
            start += B->qtot();
          }
        }
      }
    }
    void apply_flux( const Scalar t, const vField &F ) {
      for (LocalSize n=0; n<F[0]->nbc; ++n)   // loop over field boundaries
        if (F[0]->bc[n]->type == type )
          for (vField::size_type i=0; i<F.size(); ++i) {
            F[i]->bc[n]->B->u = F[i]->bc[n]->S->u;
            scale(-1.0, F[i]->bc[n]->B->u );
          }
    }
    void matrix_apply(const Scalar t, const vField &F) {
      //cout << "DirichletBC_Function::apply(...)" << endl;
      assert( 1 == expr.size() );
      evaluate(F);
      LocalSize start=0;
      dVector wk;
      for (LocalSize n=0; n<F[0]->nbc; ++n) {    // loop over field boundaries
        if (F[0]->bc[n]->type == type ) {
          for (vField::size_type i=0; i<F.size(); ++i) {
            const Ordinal qtot = F[i]->bc[n]->B->qtot();
            wk.alias(s,start,qtot);
            F[i]->bc[n]->B->u = wk;
            start += qtot;
          }
        }
      }
    }
    void matrix_apply_flux( const Scalar t, const vField &F ) {
      for (LocalSize n=0; n<F[0]->nbc; ++n)   // loop over field boundaries
        if (F[0]->bc[n]->type == type )
          for (vField::size_type i=0; i<F.size(); ++i) {
            F[i]->bc[n]->B->u = F[i]->bc[n]->S->u;
          }
    }
  };

  //===========================================================================
  //                       Unsteady Dirichlet BC
  //===========================================================================

  /// Single frequency transient Dirichlet boundary condition
  class UnsteadyDirichletBC : public DirichletBC {
    Scalar freq;   ///< frequency
    Scalar t0;     ///< reference time
  public:
    UnsteadyDirichletBC(const string t, ifstream &in) : DirichletBC(t) {
      scan_lb(in);
      if (!(in >> value >> freq >> t0))
        error("Darcy::UnsteadyDirichletBC: could not read value, freq, t0");
      scan_rb(in);
    }
    void apply( const Scalar t, const vField &F ) {
      for (LocalSize n=0; n<F[0]->nbc; ++n)   // loop over field boundaries
        if (F[0]->bc[n]->type == type )
          for (vField::size_type i=0; i<F.size(); ++i) {
            F[i]->bc[n]->B->u = value*sin(two*pi*freq*(t-t0));
            scale( 2.0, F[i]->bc[n]->B->u );
            F[i]->bc[n]->B->u.Sub(F[i]->bc[n]->S->u);
          }
    }
  };

  //===========================================================================
  //                            Neumann BC
  //===========================================================================

  /// Constant valued Neumann boundary condition
  class NeumannBC : public BC {
    Scalar value;
  public:
    NeumannBC(const string t, const Scalar v=0) : BC(t), value(v) { }
    NeumannBC(const string t, ifstream &in) : BC(t) {
      scan_lb(in);
      if (!(in >> value))
        error("Darcy::NeumannBC: could not read value");
      scan_rb(in);
    }
    void apply( const Scalar, const vField & ) ;
    void apply_flux( const Scalar, const vField & ) ;
    void matrix_apply( const Scalar, const vField & ) ;
    void matrix_apply_flux( const Scalar, const vField & ) ;
  };

  //===========================================================================
  //                          Function Neumann BC
  //===========================================================================

  /// Applies a function for velocity boundary conditions
  class NeumannBC_Function : public FuncBC {
  public:
    /// Constructor
    NeumannBC_Function(const string t, ifstream &in, int ndof=0) :
      FuncBC(t,in,ndof) {}
    void apply( const Scalar t, const vField &F ) {
      for (LocalSize n=0; n<F[0]->nbc; ++n)   // loop over field boundaries
        if (F[0]->bc[n]->type == type )
          for (vField::size_type i=0; i<F.size(); ++i)
            F[i]->bc[n]->B->u = F[i]->bc[n]->S->u;
    }
    void apply_flux(const Scalar t, const vField &F) {
      //cout << "NeumannBC_Function::apply(...)" << endl;
      assert( 1 == expr.size() );
      evaluate(F);
      LocalSize start=0;
      dVector wk;
      for (LocalSize n=0; n<F[0]->nbc; ++n) {  // loop over field boundaries
        if (F[0]->bc[n]->type == type ) {
          for (vField::size_type i=0; i<F.size(); ++i) {
            Side *B = F[i]->bc[n]->B;
            wk.alias(s,start,B->qtot());
            B->u = F[i]->bc[n]->S->u;
            daxpy(-2.0,wk,B->u);
            start += B->qtot();
          }
        }
      }
    }
  };

  // ==========================================================================
  //                      Unsteady Manufactured Source Term
  // ==========================================================================

  /// This is a spatial Manufactured source that changes
  class TransientManufactured : public Source {
    enum Solutiontype{
      sinwave = 0,
      p1 = 1,
      p2 = 2,
      p3 = 3,
      p4 = 4
    };
    Solutiontype type;
    Scalar rho1;
    Scalar rho2;
    Scalar nu; ///< diffusivity
    Scalar phi; ///< advection diffusion porosity
  public:
    /// Constructor
    TransientManufactured(const string tag, ifstream &in) : Source(tag) {
      cout << "Darcy::TransientManufactured::Constructor" << endl;
      scan_lb(in);
      int typeint = 0;
      if (!(in >> typeint >> nu >> rho1 >> rho2 >> phi))
        error("Darcy::TransientManufactured::Cannot read data.");
      scan_rb(in);
      type = (Solutiontype)typeint;
      cout << "  type = " << type << endl;
      cout << "  nu   = " << nu   << endl;
      cout << "  rho1 = " << rho1 << endl;
      cout << "  rho2 = " << rho2 << endl;
      cout << "  phi  = " << phi  << endl;
    }

    virtual ~TransientManufactured() {};

    void apply(const Scalar time, const vField &, vField &F) {
      // cout << "Darcy::TransientManufactured::apply" << endl;
      // cout<<"time = "<<time<<endl;
      for (LocalSize e = 0; e < F[0]->ne; e++) { // Loop over elements
        Element* E = F[0]->el[e];
        for (Ordinal q = 0; q < E->qtot; q++)  // Loop over quadrature pts
          E->u[q] -= manufactured_source( (*E->C)[q], time );
      }
    }

    void adjoint_apply(const Scalar, const vField &, const vField &, vField &)
    {}

  private:
    Scalar manufactured_source(const Point &p, const Scalar t) const {
      const Scalar x = p.x;
      const Scalar pi = DGM::pi;
      switch (type) {
      case sinwave: {
        const Scalar in = 2.0*pi*(x -t/phi);
        const Scalar numerator = -4*pow(pi,2)*nu*(rho1-rho2)*
          phi*(-rho1 + rho2 + (rho1+3*rho2)*sin(in));
        const Scalar denominator = pow(rho1+3*rho2+(rho2-rho1)*sin(in),2);
        return numerator/denominator;
      }
      case p1:
        return nu/pow(2+x,2);
      default:
        error("Multi_Mat_Adv_Diff::manufactured_source::unknown type.");
        return 0.0;
      }
    }
  };

  // constructor
  Darcy( DGM::ArgList &args, const DGM::Comm::Ptr = DGM::Comm::World );

  // destructor
  virtual ~Darcy() {
    comm->cout() << "~Darcy()" << endl;
  }

  // local methods
  void parse_args( DGM::ArgList &args );
  void showUsage();

  // override virtual Domain methods
  virtual int solve();
  virtual int plot(const string&);
  void time_derivative( vField &, vField & ) {
    comm->error("Darcy::time_derivative not implemented");
  }
  void set_ic( vField &, string=".ic" );
  void set_given_field(vField &, const string, const bool projic) const;
  void project_out_avg(Field &U, vField &F) const;

  // override BC methods
  BC* make_BC( ifstream &, string & );

  // override Source methods
  Source::Ptr make_Source( ifstream &, string & );
  void add_source(const vField &, vField & );

  /// Evaluation the action of the Darcy operator
  void action( vField &Us, vField &Uf );

  /// Sets the restart flag to true -- defaults to false in the constructor
  void set_restart() { restart = true; }

  /// Sets the porous medium absolute permeability field from input file .kabs
  void set_medium( vField &Kabs, const string ) const;

#ifdef DGM_USE_EPETRA
  /// Delete the system matrix to trigger a rebuild
  void reset_system_matrix() {A = Teuchos::null;}

#endif

  Scalar get_viscosity() const { return myparams.get("viscosity");}

  void solve_and_get_Darcy_velocity( vField & );

  void postprocess_Darcy_velocity( vField &, vField & ,vField &);

private:

  Table myparams;

  /// Helper function to read input from file that is not in the params table
  template <typename T>
  T input(const string &key,    ///< parameter name in input file
          const T &defaultval)  ///< default value
    {
      return DGM::read_from_input<T>(myparams, root+".inp", key, defaultval);
    }

  /// Returns a random number in the range [0,1)
  static Scalar RandomReal01() {
#ifdef REO_DARCY_USE_RAND
    const Scalar maxrand = RAND_MAX;
    const Scalar numrand(rand());
    const Scalar fluct = numrand/maxrand; // range: [0,1]
    return fluct;
#else
    // rand() is a poor random number generator that, amoung other bad
    // features, is not consistent across platforms.  random() performs much
    // better.
    const Scalar a = 0.0;
    const Scalar b = 1.0;
    const Scalar r = ((Scalar)::random()/((Scalar)(RAND_MAX)+(Scalar)(1)));
    return (b-a)*r+a;
#endif
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
#ifdef REO_DARCY_USE_RAND
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

  void residual( vField &Us, vField &Ur );
  void solution_flux(const vField &, vField &, vField &) const;
  void solution_flux_new_bc(const vField &, vField &, vField &) const;
  void interior_penalty_boundary_correction(
      const vField &, const vField &, const vField &, vField & ) const;
  void average_flux_plus_interior_penalty( const vField &,
      const vField &, const vField &, vField & ) const;
  void average_flux_plus_interior_penalty_new_bc(
      const vField &, const vField &, const vField &, vField & ) const;

#ifdef REO_USE_GETSIDEMAPS
  Scalar computeC11(
      const Side * const Us_loc,
      const Side * const Us_adj,
      const Side * const Lt_loc,
      const Side * const Lt_adj,
      const SideMap &smap,
      const Ordinal qstot
  ) const;

  Scalar compute_average_mobility(
      const Side * const Lt_loc,
      const Side * const Lt_adj,
      const SideMap &smap,
      const Ordinal q
  ) const;
#else
  Scalar computeC11(
    const Side * const Us_loc,
    const Side * const Us_adj,
    const Side * const Lt_loc,
    const Side * const Lt_adj,
    const Element * const S,
    const Ordinal qstot
  ) const;

  Scalar compute_average_mobility(
    const Side * const Lt_loc,
    const Side * const Lt_adj,
    const Ordinal ql,
    const Ordinal qr
  ) const;
#endif

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
  void Matrix( Epetra_CrsMatrix &A) const;
  void RHS( Epetra_Vector &b) const;
  void test_serialization() const;
#endif

};

} // namespace Reo

#endif  // REO_DARCY_HPP
