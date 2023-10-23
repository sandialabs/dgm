#ifndef REO_MULTI_COMPONENT_TRANSPORT_HPP
#define REO_MULTI_COMPONENT_TRANSPORT_HPP

/** \file Multi_Component_Transport.hpp
    \brief Multi component transport declaration
    \author Axel Gerstenberger
    \author Guglielmo Scovazzi
    \author Scott Collis
    \copyright (c)2013 Sandia National Laboratories
*/

// DGM includes
#include "ReoConfig.hpp"
#include "Comm.hpp"
#include "Domain.hpp"
#include "Field.hpp"
#include "vField.hpp"
using namespace DGM;

namespace Reo {

// forward declarations
class Darcy;

/// Multi-Component Transport
class Multi_Comp_Trans: public Domain {

protected:

  mutable dVector wk1;  ///< local workspace
  mutable dVector wk2;  ///< local workspace
  mutable dVector wk3;  ///< local workspace
  mutable dVector wk4;  ///< local workspace

public:

  //===========================================================================
  //                            Dirichlet BC
  //===========================================================================

  /// Constant valued Dirichlet boundary condition
  class DirichletBC : public BC {
  protected:
    Scalar value; ///< Dirichlet value
  public:
    /// Constructor
    DirichletBC(const string t, const Scalar v=0) : BC(t), value(v) { }
    /// Constructor
    DirichletBC(const string t, ifstream &in) : BC(t), value(0) {
      scan_lb(in);
      if (!(in >> value))
        error("Multi_Comp_Trans::DirichletBC: could not read value",-1);
      scan_rb(in);
    }
    void apply( const Scalar, const vField & ) ;
    void apply_flux( const Scalar, const vField & ) ;

    void adjoint_apply( const Scalar, const vField &, const vField & ) ;
    void adjoint_apply_flux( const Scalar, const vField &,
                             const vField & ) ;
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
      for (LocalSize n=0; n<F[0]->nbc; ++n) {   // loop over field boundaries
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
  };

  //===========================================================================
  //                       Unsteady Dirichlet BC
  //===========================================================================

  /// Single frequency transient Dirichlet boundary condition
  class UnsteadyDirichletBC : public DirichletBC {
    Scalar freq;   ///< frequency
    Scalar t0;     ///< reference time
  public:
    /// Constructor
    UnsteadyDirichletBC(const string t, ifstream &in) :
    	DirichletBC(t), freq(0), t0(0) {
      scan_lb(in);
      if (!(in >> value >> freq >> t0))
        error("Multi_Comp_Trans::UnsteadyDirichletBC: could not read "
              "value, freq, t0");
      scan_rb(in);
    }
    void apply( const Scalar t, const vField &F ) {
      for (LocalSize n=0; n<F[0]->nbc; ++n)   // loop over field boundaries
        if (F[0]->bc[n]->type == type )
          for (vField::size_type i=0; i<F.size(); ++i) {
            F[i]->bc[n]->B->u = value*sin(two*pi*freq*(t-t0));
  #ifdef REO_CONSISTENT_BC
            scale( 2.0, F[i]->bc[n]->B->u );
            F[i]->bc[n]->B->u.Sub(F[i]->bc[n]->S->u);
  #endif
          }
    }
  };
  //===========================================================================
  //                            Neumann BC
  //===========================================================================

  /// Constant valued Neumann boundary condition
  /*! \todo Generalize to arbitrary convective velocities */
  class NeumannBC : public BC {
    Scalar cx, cy, cz;
    Scalar value;
  public:
    /// Constructor
    NeumannBC(const string& t, const Scalar v=0, const Scalar c_x=0,
              const Scalar c_y=0, const Scalar c_z=0)
      : BC(t), cx(c_x), cy(c_y), cz(c_z), value(v) {
      if (cy!=0.0) error("MCT::NeumannBC non-zero cy detected");
      if (cz!=0.0) error("MCT::NeumannBC non-zero cz detected");
    }
    /// Constructor
    NeumannBC(const string& t, ifstream &in,
              Scalar c_x, Scalar c_y, Scalar c_z)
      : BC(t), cx(c_x), cy(c_y), cz(c_z), value(0) {
      scan_lb(in);
      if (!(in >> value))
        error("Multi_Comp_Trans::NeumannBC: could not read value",-1);
      scan_rb(in);
      if (cy!=0.0) error("MCT::NeumannBC non-zero cy detected");
      if (cz!=0.0) error("MCT::NeumannBC non-zero cz detected");
    }
    void apply( const Scalar, const vField & ) ;
    void apply_flux( const Scalar, const vField & ) ;

    void adjoint_apply( const Scalar, const vField &, const vField & ) ;
    void adjoint_apply_flux( const Scalar, const vField &,
                             const vField & ) ;
  };

  //===========================================================================
  //                            Robin BC
  //===========================================================================

  /// Constant valued Robin boundary condition
  /*! \todo Generalize to arbitrary convective velocities */
  class RobinBC : public BC {
    Scalar cx, cy, cz;
    Scalar theta;
    Scalar value;
   public:
    /// Default constructor
    RobinBC(const string t, const Scalar value_=0.0, const Scalar theta_=1.0,
            const Scalar c_x=0, const Scalar c_y=0, const Scalar c_z=0 )
      : BC(t), cx(c_x), cy(c_y), cz(c_z), theta(theta_), value(value_) {
      if (cy!=0.0) error("MCT::RobinBC non-zero cy detected");
      if (cz!=0.0) error("MCT::RobinBC non-zero cz detected");
    }
    /// Construct from a file stream
    RobinBC(const string t, ifstream &in,
            Scalar c_x, Scalar c_y, Scalar c_z)
      : BC(t), cx(c_x), cy(c_y), cz(c_z), theta(0), value(0) {
      scan_lb(in);
      if (!(in >> value >> theta))
        error("Multi_Comp_Trans::RobinBC: could not read theta and value",-1);
      scan_rb(in);
      if (cy!=0.0) error("MCT::RobinBC non-zero cy detected");
      if (cz!=0.0) error("MCT::RobinBC non-zero cz detected");
    }
    void apply( const Scalar, const vField & );
    void apply_flux( const Scalar, const vField &);

    void adjoint_apply( const Scalar, const vField &, const vField & );
    void adjoint_apply_flux( const Scalar, const vField &,
                             const vField & );
  };

  //===========================================================================
  //                            Outflow BC
  //===========================================================================

  /// Outflow boundary condition
  class OutflowBC : public BC {
   public:
    /// Constructor
    OutflowBC( const string t) : BC(t) { }
    /// Constructor
    OutflowBC( const string t, ifstream &in ) : BC(t) {
      scan_lb(in);
      scan_rb(in);
    }
    void apply( const Scalar, const vField & ) ;
    void apply_flux( const Scalar, const vField & ) ;

    void adjoint_apply( const Scalar, const vField &, const vField & ) ;
    void adjoint_apply_flux( const Scalar, const vField &,
                             const vField & ) ;
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
    Scalar rho1;   ///< First density
    Scalar rho2;   ///< Second density
    Scalar nu;     ///< diffusivity
    Scalar phi;    ///< advection diffusion porosity
  public:
    /// Constructor
    TransientManufactured(const string tag, ifstream &in) : Source(tag),
    type(sinwave), rho1(0), rho2(0), nu(0), phi(0) {
      cout << "Multi_Comp_Trans::TransientManufactured::Constructor" << endl;
      scan_lb(in);
      int typeint = 0;
      if (!(in >> typeint >> nu >> rho1 >> rho2 >> phi))
        error("Multi_Comp_Trans::TransientManufactured::Cannot read data.");
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
      // cout << "TransientManufactured::apply" << endl;
      for (LocalSize e = 0; e < F[0]->ne; e++) { // Loop over elements
        Element* E = F[0]->el[e];
        for (LocalSize q = 0; q < E->qtot; q++)  // Loop over quadrature pts
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
        const Scalar in = 2.0*pi*(x - t/phi);
        const Scalar numerator = 4*pow(pi,2)*nu*rho1*rho2*phi*
          (-rho1 + rho2 + (rho1+3*rho2)*sin(in));
        const Scalar denominator = pow(rho1+3*rho2+(rho2-rho1)*sin(in),2);
        return numerator/denominator;
      }
      case p1:
        return 2*(2+nu)/pow(2+x,2);
      default:
        error("Multi_Comp_Trans::manufactured_source::unknown type.");
        return 0.0;
      }
    }
  };

  // ==========================================================================
  //                      Unsteady Gaussian Source Term
  // ==========================================================================

  /// This is a spatial Gaussian source that moves
  class TransientGaussian : public Source {
  public:
    /// Constructor
    TransientGaussian(const string tag, ifstream &in) : Source(tag),
    x0(0), y0(0), t0(0), sigma(0), amp(0), cx(0), cy(0), sigma_inv(0) {
      scan_lb(in);
      if (!(in >> x0 >> y0 >> t0 >> sigma >> amp >> cx >> cy))
        error("Multi_Comp_Trans::TransientGaussian::Cannot read data.");
      sigma_inv = 1.0/sigma;
      scan_rb(in);
    }

    virtual ~TransientGaussian() {};

    void apply(const Scalar time, const vField &, vField &F) {
      //cout<<"time = "<<time<<endl;
      for (LocalSize e = 0; e < F[0] -> ne; e++) { // Loop over elements
        Element* E = F[0] -> el[e];
        for (LocalSize q = 0; q < E -> qtot; q++)  // Loop over quadrature pts
          E->u[q] -= gaussian( (*E->C)[q], time );
      }
    }

    void adjoint_apply(const Scalar, const vField &, const vField &, vField &)
    {}

  private:
    Scalar x0, y0, t0, sigma, amp, cx, cy;
    Scalar sigma_inv;
    Scalar gaussian(const Point &C, const Scalar t) {
      return amp*exp(-(pow(C.x-x0-cx*(t-t0),2)+
                       pow(C.y-y0-cy*(t-t0),2))*sigma_inv);
    }
  };

  // ==========================================================================
  //                       DiracRicker Source Term
  // ==========================================================================

  /// Dirac source in space with a Ricker wavelet signature in time
  /**
   * This class places a source term that is a Dirac delta function on a given
   * elements quadrature point with a Ricker wavelet in time.
*/
  class DiracRicker : public Source {
    GlobalSize eid;   ///< element id
    LocalSize qpt;    ///< quadrature point within element
    Point p;          ///< source location;
    Scalar amp;       ///< source amplitude
    Scalar fp;        ///< Ricker peak frequency
    Scalar t0;        ///< Ricker delay time
  public:
    /// Constructor
    DiracRicker(const string tag, ifstream &in) : Source(tag),
    eid(undefined<GlobalSize>()), qpt(undefined<LocalSize>()), p(), amp(1.0),
    fp(0), t0(0) {
      scan_lb(in);
  #ifdef DGM_USE_NEW_DELTA
      if (!(in >> eid >> p >> amp >> fp ))
        error("Multi_Comp_Trans::DiracRicker::Cannot read: eid, x, y, z, "
              "amp, fp");
  #else
      if (!(in >> eid >> qpt >> amp >> fp ))
        error("Multi_Comp_Trans::DiracRicker::Cannot read: eid, qpt, amp, fp");
  #endif
      t0 = 1.5/fp; // this is a good value for the delay time
      scan_rb(in);
    }
    virtual ~DiracRicker() {};
    /// Source apply method
    void apply(const Scalar time, const vField &, vField &F) {
      Element *E;
      if (F.partition->owns(eid)) {
        E = F[0]->el[F.partition->inc(eid)];
      } else {
        return;                              // element is not in my partition
      }
  #ifdef DGM_USE_NEW_DELTA
      E->add_Dirac_delta(p, -amp*ricker(time));
  #else
      E->add_Dirac_delta(qpt, -amp*ricker(time));
  #endif
    }
    /// Adjoint apply method
    void adjoint_apply(const Scalar, const vField &, const vField &, vField &)
    {}
  private:
    /// Compute a Ricker wavelet in time
    Scalar ricker(const Scalar time) const {
      const Scalar T = pow(pi*fp*(time-t0),2);
      return (one-two*T)*exp(-T);
    }
  };

protected:

  // material properties
  Scalar eff_diff;          ///< effective diffusivity of aquifer = tau * D
  std::vector<Scalar> rho;  ///< densities for ALL species (NFIELD + 1)
                            ///< order in rho matters!
  Scalar porosity_phi;      ///< porosity coefficient

  Scalar tmax;              ///< final physical computation time

  vField Cf;                ///< convective field
  vField Vf;                ///< work vector for the diffusive flux field

  const bool coupled_darcy; ///< is true, if Darcy problem is present
  typedef DGM::Shared<Reo::Darcy>::Ptr DarcyPtr;
  DarcyPtr darcy;           ///< Associated Darcy flow object

public:
  /// Constructor
  Multi_Comp_Trans( DGM::ArgList &args,
                    const DGM::Comm::Ptr = DGM::Comm::World,
                    const bool coupled_darcy_ = false );

  /// Destructor
  virtual ~Multi_Comp_Trans() {
    cout << "~Multi_Comp_Trans()" << endl;
  }

  // local methods
  // void parse_args( DGM::ArgList &args );
  void showUsage();

  // override virtual Domain methods
  void make_contiguous();

  void prestep( vField&, const Ordinal, const Ordinal, const Scalar );

  Scalar set_time_step( vField &Uf );
  Scalar compute_critical_timestep() const;
  void zero_all_fields();
  void set_ic(vField &, string=".ic");

  BC* make_BC( ifstream &, string & );

  Source::Ptr make_Source( ifstream &, string & );
  void add_source(const vField &, vField &);

protected:

  void convection( const vField &, const vField & , vField &, vField & ) const;
  void constant_convection( const vField &, vField & ) const;
  void variable_convection_Euler_Lagrange( const vField &, vField & ) const;

  void diffusion( const vField &, const vField &, vField &, vField & );
  void convective_flux( const vField &, const vField &, vField &, vField & ) const;

  void interior_penalty_boundary_correction( const vField &, const vField &,
      vField &, const Scalar ) const;
  void average_flux_plus_interior_penalty( const vField &, const vField &,
      const vField &, vField &, const Scalar ) const;

  void convective_flux(const Scalar& cn, const Scalar& ul, const Scalar& ur,
                   Scalar& fluxl, Scalar& fluxr) const;
  Scalar compute_h_n(const Side *const Xs) const;

private:

  void flux_in_one_sd(
      const Element *const Ue, const Element *const Fe,
      const char sd, const dVector &rho, dVector &X1x) const;

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

  void setup_convective_field();
  void read_convective_field(vField &, string);
  void post_process_initial_field(vField &F, const bool proj);

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
      const Element *const,
      Element *const,
      dVector &
  ) const;

  /// compute penalty factor C_11
  Scalar compute_C11(
      const Scalar stab,
      const Scalar h_n,
      const Scalar rho_avg
      ) const {
    return stab*porosity_phi*eff_diff*rho_avg/h_n;
  }

  /// compute element Peclet number (one value per element)
  void compute_element_Peclet_number(
      vField &Pef) const ;

  /// set circular initial condition for mass fraction X_1
  Scalar circular_mass_fraction(
      const Element *const Xe, Ordinal q, Scalar radius,
      Scalar eps, Scalar innerval) const;

protected:
  // constant convection, for debugging only
  // every convective field - constant or not - must be given in the .cfd file
  const bool variable_cfield; ///< convective field flag
                              ///< if true, convective field is a vField
                              ///< if false, use spatially constant convective
  const Scalar cx;  ///< wave speed in x (cannot read from file anymore!)
  const Scalar cy;  ///< wave speed in y
  const Scalar cz;  ///< wave speed in z

  bool solve_Darcy; ///< turn on and off the Darcy solution

};

} // namespace Reo

#endif
