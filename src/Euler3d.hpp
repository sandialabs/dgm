#ifndef REO_EULER3D_HPP
#define REO_EULER3D_HPP

/** \file Euler3d.hpp
    \brief Declarations for the 3d Euler equations
    \author Scott Collis
*/

// DGM includes
#include "Comm.hpp"
#include "Domain.hpp"
using namespace DGM;

// Reo includes
#include "Channel.hpp"

namespace Reo {

/// Three-dimensional compressible Euler Domain
class Euler3d : public Domain {

  vField S;       ///< Extra storage for statistics
  vField St;      ///< Extra storage for statistics

  /// Wall boundary condition
  class WallBC : public BC {
    int ndof;        ///< number of degrees of freedom
  public:
    /// Default constructor
    WallBC( const string t, const int ndof_) : BC(t), ndof(ndof_) { }
    /// Construct from an input file stream
    WallBC( const string t, ifstream &in ) : BC(t) {
      scan_lb(in);
      ndof = 5;
      scan_rb(in);
    }
    void apply( const Scalar, const vField & ) ;
    void apply_flux( const Scalar, const vField & ) ;

    void adjoint_apply( const Scalar, const vField &, const vField & ) ;
    void adjoint_apply_flux( const Scalar, const vField &, const vField & ) ;
  };

 protected:

  dVector wk1;                         ///< local work space

  static const int NFIELDS = 5;        ///< number of fields for static arrays

  DGM::Shared<Channel>::Ptr channel;   ///< Channel data-structure

  Scalar gamma;                        ///< Ratio of specific heats

 public:

  /// Constructor
  Euler3d( DGM::ArgList &args, const DGM::Comm::Ptr = DGM::Comm::World );

  /// Destructor
  virtual ~Euler3d(){}

  // methods
  void parse_args( DGM::ArgList &args );
  void showUsage();

  void compute_stats(const string &);
  void plot_stats(const int);

  void time_derivative( vField &, vField & );
  virtual int plot(const string&);

  void set_ic( vField &, string=".ic" );

  void setup_BCdb( );
  void read_BCdb( ifstream & );
  BC* make_BC( ifstream &, string & );

  Scalar set_time_step( vField & );

  void enforce_bc( vField & );
  void enforce_flux_bc( vField & );

  void write_bndry_stats();

protected:

  /// Supported convective numerical fluxes
  enum flux_type {
    Roe,                               ///< Roe numerical flux
    vanLeer,                           ///< van Leer numerical flux
    StegerWarming,                     ///< Steger-Warming numerical flux
    LaxFriedrichs                      ///< Lax-Friedrichs numerical flux
  };

  // local methods

  void convection( vField &, vField & );
  void gradient( Element *, Element *, dVector &, dVector &,
                 dVector &, dVector & );
  void primitive_sides( vField & );
  void convective_flux( vField &, vField & );
  void compute_vorticity();

};

} // namespace Reo

#endif // REO_EULER3D_HPP
