#ifndef DGM_ARTDIFF_HPP
#define DGM_ARTDIFF_HPP

/** \file ArtDiff.hpp
    \brief Artificial diffusion declaration
    \author Scott Collis
    \warning This is currently experimental, use with caution
*/

// DGM includes
#include "Comm.hpp"
#include "Domain.hpp"

namespace DGM {

/// Abstract base class for a term in the governing equations
class Term {
protected:
  Domain *omega;            ///< pointer to Domain
public:
  Term() : omega(0) {}
  Term(Domain *domain) : omega(domain) {}
  virtual ~Term() {}
};

/// Artificial Diffusion term
class ArtDiff : public Term {

  const DGM::Comm::Ptr comm;    ///< parallel communicator

public:

  /// default constructor
  ArtDiff() : Term(0), comm(DGM::Comm::World), C_epsi0(0.0), kappa_dc(3.0),
  L_fs(1), C_s0(0.1), sensor(Resolution),
  //eps_w(0),
  //eps_g(0),
  Vt(comm,"Vt"), Sv(comm,"Sv"), Nu(comm,"Nu") {}

  /// constructor
  ArtDiff(Domain *domain, const DGM::Comm::Ptr comm_ = DGM::Comm::World ) :
    Term(domain),
    comm(comm_),
    C_epsi0(0.1),
    kappa_dc(3.0),
    L_fs(1),
    C_s0(0.1),
    sensor(Resolution),
    //eps_w(0),
    //eps_g(0),
    Vt(comm,"Vt"), Sv(comm,"Sv"), Nu(comm,"Nu")
  {
    comm->cout() << "ArtDiff::ArtDiff(...)" << endl;

    // make auxiliary Fields using copy constructor
    for (vField::size_type i=0; i<omega->U.size(); i++) {
      Vt.push_back( new Field( omega->U[i], omega->root, omega->U[i]->name ) );
      Sv.push_back( new Field( omega->U[i], omega->root, omega->U[i]->name ) );
    }

    // make a field to store and plot the artificial viscosity
    Nu.push_back( new Field( omega->U[0], omega->root, "Nu" ) );

    // All this workspace should be consolidated
    const Ordinal Lmax = omega->Lmax();
    const Ordinal Qmax = omega->Qmax();
    wka.resize(10*max(Lmax,Qmax));
    wkb.resize(10*max(Lmax,Qmax));
    wkc.resize(10*max(Lmax,Qmax));
    wk1.resize(10*max(Lmax,Qmax));
    wk2.resize(10*max(Lmax,Qmax));
    wk3.resize(10*max(Lmax,Qmax));
    wk4.resize(10*max(Lmax,Qmax));
  }

  /// destructor
  virtual ~ArtDiff() {
    if (comm->verbosity()) comm->cout()<<"~DGM::ArtDiff()"<<endl;
  }

  /// Supported sensor options
  enum sensor_type {
    None,        ///< no sensor defined
    Jump,        ///< jump sensor
    Resolution   ///< resolution sensor
  };

  // local methods

  void jump_sensor( vField &) const;

  void resolution_sensor( vField &) const;

  void operator() ( vField &, vField &, vField & ) const;

  void average_flux( vField &, vField &, const char) const;
  void average_flux_exp( vField &, vField &, const char) const;

private:

  Scalar C_epsi0;           ///< artificial viscosity coefficient
  Scalar kappa_dc;          ///< artificial viscosity wave number bound
  int    L_fs;              ///< fine scale polynomial order bound
  Scalar C_s0;              ///< artificial viscosity decay parameter
  enum sensor_type sensor;  ///< user-selected discontinity sensor

  //Scalar eps_w;
  //Scalar eps_g;

  mutable vField Vt;        ///< Velocity field
  mutable vField Sv;        ///< Sensor field
  mutable vField Nu;        ///< artificial viscosity

  // All these should be consolodated
  dVector wka;
  dVector wkb;
  dVector wkc;
  dVector wk1;
  dVector wk2;
  dVector wk3;
  dVector wk4;
};

} // namespace DGM

#endif  // DGM_ARTDIFF_HPP
