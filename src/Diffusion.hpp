#ifndef DGM_DIFFUSION_HPP
#define DGM_DIFFUSION_HPP

/** \file Diffusion.hpp
    \brief Diffusion operator declaration
    \author Scott Collis
*/

// DTK includes
#include "DTK.hpp"

// DGM includes
#include "Comm.hpp"
#include "Domain.hpp"
#include "vField.hpp"
#include "Vector.hpp"

namespace DGM {

/// Diffusion term
class Diffusion : public DTK::Term<vField,dVector,Scalar,Ordinal>,
                  public DGM::Domain {

  const Scalar mu;              ///< constant diffusivity

  dVector wk1, wk2, wk3;

public:

  /// Constructor
  Diffusion(DGM::ArgList &args, vField &S,
            const DGM::Comm::Ptr comm_ = DGM::Comm::World ) :
    Domain(args,comm_), mu(1.0)
  {
    //comm->cout() << "Diffusion::Diffusion(...)" << endl;
    U = S;

    Nfields = U.size();

    // set some additional domain parameters
    ne = U[0]->ne;
    nsd = U[0]->nsd();

    // allocate local workspace
    wk1.resize(max(Lmax(),Qmax()));
    wk2.resize(max(Lmax(),Qmax()));
    wk3.resize(max(Lmax(),Qmax()));
  }

  /// Zero all fields
  void zero_all_fields() {
    //U.zero();
  }

  /// Destructor
  virtual ~Diffusion() {}

  /// Time derivative
  virtual void time_derivative(vField &U, vField &F) { DGM_UNDEFINED; }

  /// Set the initial condition
  virtual void set_ic( vField &, string=".ic" ) { DGM_UNDEFINED; }

  /// Evaluate the diffusion term assuming zero normal flux boundary conditions
  void operator()(vField &Uf, vField &Ff, vField &Rf) {
    //comm->cout() << "Diffusion::operator() for vField = "
    //    << Uf.get_name() << endl;
    if (mu == 0) return;
    const Ordinal nsd = Uf[0]->nsd();
    Uf.fill_sides();                   // put solution on the sides
    Uf.fill_bc_sides();                // put solution on the boundary sides
    Uf.share_sides();                  // share sides in parallel
    average_flux( Uf, Ff, '+' );       // F's sides are average of the solution
    for (vField::size_type n=0; n<Uf.size(); ++n) {
      for (Ordinal e=0; e<Uf[n]->ne; ++e) {
        Element *U = Uf[n]->el[e];
        Element *F = Ff[n]->el[e];
        const Ordinal qtot = U->qtot;
        const Ordinal nModes = U->nModes();
        dVector ux(wk1,qtot);
        dVector uxh(ux,nModes);
        if (nsd==3) {
          dVector uy(wk2,qtot);
          dVector uyh(uy,nModes);
          dVector uz(wk3,qtot);
          dVector uzh(uz,nModes);
          U->gradient(U->u, ux, uy, uz);
          U->lift( F, ux, 'x' );
          U->project(ux);
          U->lift( F, uy, 'y' );
          U->project(uy);
          U->lift( F, uz, 'z' );
          U->project(uz);
          scale( mu, ux );
          scale( mu, uy );
          scale( mu, uz );
          U->fill_sides( ux, uy, uz );        // normal diffusive flux on sides
          U->gradient(ux, ux, 'x');           // ux = u_{,xx}
          U->gradient(uy, uy, 'y');           // uy = u_{,yy}
          U->gradient(uz, uz, 'z');           // uz = u_{,zz}
          dvadd( ux, uy, F->u );              // F->u = u_{,xx} + u_{,yy}
          dvadd( uz, F->u );                  // F->u += u_{,zz}
        } else if (nsd==2) {
          dVector uy(wk2,qtot);
          dVector uyh(uy,nModes);
          U->gradient(U->u, ux, uy);
          U->lift( F, ux, 'x' );
          U->project(ux);
          U->lift( F, uy, 'y' );
          U->project(uy);
          scale( mu, ux );
          scale( mu, uy );
          U->fill_sides( ux, uy );            // normal diffusive flux on sides
          U->gradient(ux, ux, 'x');           // ux = u_{,xx}
          U->gradient(uy, uy, 'y');           // uy = u_{,yy}
          dvadd( ux, uy, F->u );              // F->u = u_{,xx} + u_{,yy}
        } else if (nsd==1) {
          U->gradient(U->u, ux, ux);
          U->lift( F, ux, 'x' );
          U->project(ux);
          scale( mu, ux );
          U->fill_sides( ux, ux );            // normal diffusive flux on sides
          U->gradient(ux, F->u, 'x');         // ux = uxx
        } else {
          throw DGM::exception("Diffusion -- illegal value of nsd = "
              +asString(nsd));
        }
      }
    }
    Uf.share_sides();
    Uf.fill_bc_sides();                       // should really zero flux bc's
    average_flux( Uf, Ff, '-' );
    for (vField::size_type n=0; n<Uf.size(); ++n) {
      for (Ordinal e=0; e<Uf[n]->ne; ++e) {
        const Element *U = Uf[n]->el[e];
        Element *F = Ff[n]->el[e];
        U->lift( F, F->u );                   // add side fluxes to interior
      }
    }
    scale( -1.0, Ff);                         // Currently on LHS
    add( Ff, Rf );                            // add in diffusion contribution
  }

};

} // namespace DGM

#endif  // DGM_DIFFUSION_HPP
