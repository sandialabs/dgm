#ifndef REO_POISSON_HPP
#define REO_POISSON_HPP

/** \file Poisson.hpp
    \brief Basic Poisson equation module declaration
    \author Scott Collis
*/

// DGM includes
#include "Comm.hpp"
#include "Domain.hpp"
#include "SolverML.hpp"
using namespace DGM;

// Reo includes
#include "ReoConfig.hpp"

namespace Reo {

/// Poisson equation
/** This module solves the 2d Poisson equation using discontinuous Galerkin.

    \section Poisson_formulation Problem Formulation

    The Poisson equation is of the form

    \f[ \nabla^2 u = s \f]

    where \f$u\f$ is the solution variable, and \f$s\f$ is the source term.
*/
  class Poisson : public Domain {

    dVector wk;         ///< Local workspace

    bool restart;       ///< false forces solve to read an initial guess

    vField Uv;          ///< Extra vector Field
    vField Uo;          ///< Another vector Field

    static const Size NfieldsT = 1;

  public:

    // BC declarations
    class DirichletBC;

    // constructor
    Poisson( DGM::ArgList &args, const DGM::Comm::Ptr = DGM::Comm::World );

    // destructor
    virtual ~Poisson() {}

    // local methods
    void parse_args( DGM::ArgList &args );
    void showUsage();

    // override virtual Domain methods
    virtual int solve();
    virtual int plot(const string&);
    void time_derivative( vField &, vField & ) {
      comm->error("Poisson::time_derivative not implemented");
    }
    void zero_all_fields();
    void set_ic( vField &, string=".ic" );
    void project_out_avg(Field &U, vField &F) const;

    // override BC methods
    void setup_BCdb( );
    BC* make_BC( ifstream &, string & );

    // override Source methods
    Source::Ptr make_Source( ifstream &, string & );
    void add_source(const vField &, vField & );

    /// Evaluation the action of the Poisson operator
    void action( vField &Us, vField &Uf );

    /// Sets the restart flag to true -- defaults to false in the constructor
    void set_restart() { restart = true; }

  private:

    void residual( vField &Us, vField &Ur );
    void enforce_boundary_penalty( const vField &, vField &, const Scalar );
    void interior_penalty_flux( const vField &, const vField &,
                                vField &, const Scalar );
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

  // matrix implementation
#ifdef DGM_USE_EPETRA
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
#endif
  };

} // namespace Reo

#endif  // REO_POISSON_HPP
