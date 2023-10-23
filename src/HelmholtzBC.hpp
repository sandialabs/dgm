#ifndef REO_HELMHOLTZ_BC_HPP
#define REO_HELMHOLTZ_BC_HPP

/** \file HelmholtzBC.hpp
    \brief Helmholtz boundary conditions
    \author Axel Gerstenberger and Scott Collis
*/

// DGM includes
#include "BC.hpp"
#include "Source.hpp"
#include "Ctrl.hpp"
using namespace DGM;

// system includes
#include <boost/array.hpp>

namespace Reo {

//===========================================================================
//                            Dirichlet BC
//===========================================================================

/// Constant valued Dirichlet boundary condition
class Helmholtz::DirichletBC : public BC {
protected:
  Scalar value;
public:
  DirichletBC(const string t, const Scalar v=0) : BC(t), value(v) { }
  DirichletBC(const string t, ifstream &in) : BC(t) {
    scan_lb(in);
    if (!(in >> value))
      error("Helmholtz::DirichletBC: could not read value");
    scan_rb(in);
  }
  inline void apply( const Scalar, const vField & ) ;
  inline void apply_flux( const Scalar, const vField & ) ;
  inline void matrix_apply( const Scalar, const vField & ) ;
  inline void matrix_apply_flux( const Scalar, const vField & ) ;

};
void Helmholtz::DirichletBC::apply( const Scalar t, const vField &F ) {
  for (LocalSize n=0; n<F[0]->nbc; ++n)   // loop over field boundaries
    if (F[0]->bc[n]->type == type )
      for (vField::size_type i=0; i<F.size(); ++i) {
        F[i]->bc[n]->B->u = value;
        scale( 2.0, F[i]->bc[n]->B->u );
        F[i]->bc[n]->B->u.Sub(F[i]->bc[n]->S->u);
      }
}
void Helmholtz::DirichletBC::apply_flux( const Scalar t, const vField &F ) {
  for (LocalSize n=0; n<F[0]->nbc; ++n)   // loop over field boundaries
    if (F[0]->bc[n]->type == type )
      for (vField::size_type i=0; i<F.size(); ++i) {
        F[i]->bc[n]->B->u = F[i]->bc[n]->S->u;
        scale(-1.0, F[i]->bc[n]->B->u );
      }
}
void Helmholtz::DirichletBC::matrix_apply( const Scalar t, const vField &F ) {
  for (LocalSize n=0; n<F[0]->nbc; ++n)   // loop over field boundaries
    if (F[0]->bc[n]->type == type )
      for (vField::size_type i=0; i<F.size(); ++i) {
        F[i]->bc[n]->B->u = value;
      }
}
void Helmholtz::DirichletBC::matrix_apply_flux( const Scalar t,
                                                const vField &F ) {
  for (LocalSize n=0; n<F[0]->nbc; ++n)   // loop over field boundaries
    if (F[0]->bc[n]->type == type )
      for (vField::size_type i=0; i<F.size(); ++i) {
        F[i]->bc[n]->B->u = F[i]->bc[n]->S->u;
      }
}

//===========================================================================
//                        Gaussian Ricker Source
//===========================================================================

/// Gaussian source distribution in space
class Helmholtz::GaussianSource : public Source {
public:
  GaussianSource(const string tag, ifstream &in, const Ordinal nsd_) :
    Source(tag), nsd(nsd_) {
    scan_lb(in);
    if (nsd==1) {
      if (!(in >> x0 >> sigma >> amp))
        error("Helmholtz::GaussianSource::Cannot read data for 1D");
    } else if (nsd==2) {
      if (!(in >> x0 >> y0 >> sigma >> amp))
        error("Helmholtz::GaussianSource::Cannot read data for 2D");
    } else if (nsd==3) {
      if (!(in >> x0 >> y0 >> z0 >> sigma >> amp))
        error("Helmholtz::GaussianSource::Cannot read data for 3D");
    } else {
      error("Helmholtz::GaussianSource::Illegal value nsd");
    }
    twos2i = one/(two*pow(sigma,2));
    sr2pi = one/(sigma*sqrt(two*pi));
    scan_rb(in);
  }

  // currently only put the source in the real part
  void apply(const Scalar time, const vField &, vField &F) {
    for (LocalSize e=0; e<F[0]->ne; e++) {
      Element *E = F[0]->el[e];
      for (LocalSize q=0; q<E->qtot; q++) {
        F[0]->el[e]->u[q] -=  amp*Gaussian((*E->C)[q]);
        // F[1]->el[e]->u[q] -= -amp*Gaussian((*E->C)[q]);
      }
    }
  }

  void adjoint_apply(const Scalar, const vField &,
                     const vField &, vField &) {}

private:

  const Ordinal nsd;
  Scalar x0, y0, z0, sigma, amp;
  Scalar twos2i, sr2pi;
  /// Gaussian in space
  Scalar Gaussian(const Point &C) {
    if (nsd==1)
      return sr2pi*exp(-(pow(C.x-x0,2))*twos2i);
    else if (nsd==2)
      return pow(sr2pi,2)*
        exp(-(pow(C.x-x0,2)+pow(C.y-y0,2))*twos2i);
    else if (nsd==3)
      return pow(sr2pi,3)*
        exp(-(pow(C.x-x0,2)+pow(C.y-y0,2)+pow(C.z-z0,2))*twos2i);
    else
      DGM::Comm::World->error("Helmholtz::Gaussian::Illegal nsd");
    return 0.0;
  }
};

//===========================================================================
//                   S p o n g e   S o u r c e   T e r m
//===========================================================================

/// Sponge nonreflecting boundary treatment a.k.a. "Bob"
/** Simple reaction term to damp the solution near boundaries. */
class Helmholtz::Sponge : public Source {
  int N;                            ///< polynomial order
  Scalar As;                        ///< strength
  Scalar xs_m, xt_m, xs_p, xt_p;    // left and right
  Scalar ys_m, yt_m, ys_p, yt_p;    // bottom and top
  Scalar zs_m, zt_m, zs_p, zt_p;    // fore and aft
  const Ordinal nsd;                ///< number of space dimensions
public:
  Sponge( const string t, ifstream &in, const Ordinal nsd_ ) :
    Source(t,SPONGE), N(3), As(1), nsd(nsd_) {
    scan_lb(in);
    if (nsd==1) {
      if (!(in>>N>>As>>xs_m>>xt_m>>xs_p>>xt_p))
        error("Helmholtz::Sponge::Cannot read parameters for 1D");
    } else if (nsd==2) {
      if (!(in>>N>>As>>xs_m>>xt_m>>xs_p>>xt_p
                     >>ys_m>>yt_m>>ys_p>>yt_p))
        error("Helmholtz::Sponge::Cannot read parameters for 2D");
    } else if (nsd==3) {
      if (!(in>>N>>As>>xs_m>>xt_m>>xs_p>>xt_p
                     >>ys_m>>yt_m>>ys_p>>yt_p
                     >>zs_m>>zt_m>>zs_p>>zt_p))
        error("Helmholtz::Sponge::Cannot read parameters for 3D");
    } else {
      error("Helmholtz::Sponge() unsupported nsd");
    }
    scan_rb(in);
  }
  inline void apply(const Scalar, const vField &, vField & );
  inline void adjoint_apply(const Scalar, const vField &,
                            const vField &, vField &);

  Scalar get_tau(const Scalar d, const Scalar thickness) const {
    return As*pow(d/thickness, N);
  }

  /// fill a rhs with the source term
  /** \note May be in the wrong components. */
  void compute_reaction(
      const boost::array<Element*,2> &S,
      dVector &re,
      dVector &im
      ) const {
    const Ordinal qtot = S[0]->qtot;
    for (Ordinal q=0; q<qtot; q++) {
      const Scalar tau = compute_tau(S, q);
      re[q] += tau*(S[0]->u[q]);
      im[q] += tau*(S[1]->u[q]);
    }
  }

  /// this variant stores the tau per Gauss point -> matrix implementation
  void compute_reaction_coeff(
      const boost::array<Element*,2> &S,  ///< real and imaginary elements
      dVector &taus                       ///< tau per Gauss point
      ) const {
    const Ordinal qtot = S[0]->qtot;
    for (Ordinal q=0; q<qtot; q++) {
      taus[q] = compute_tau(S, q);
    }
  }

  Scalar compute_tau(
      const boost::array<Element*,2> &S,  ///< real and imaginary elements
      const Ordinal q                     ///< current Gauss point
      ) const {
    Scalar tau = 0.0;

    const Scalar x = S[0]->C->x[q];
    if (xs_m<xt_m && x<=xt_m)   tau += get_tau(xt_m-x, xt_m-xs_m); // left
    if (xs_p<xt_p && x>=xs_p)   tau += get_tau(x-xs_p, xt_p-xs_p); // right
    if (nsd>1) {
      const Scalar y = S[0]->C->y[q];
      if (ys_m<yt_m && y<=yt_m) tau += get_tau(yt_m-y, yt_m-ys_m); // bottom
      if (ys_p<yt_p && y>=ys_p) tau += get_tau(y-ys_p, yt_p-ys_p); // top
    }
    if (nsd>2) {
      const Scalar z = S[0]->C->z[q];
      if (zs_m<zt_m && z<=zt_m) tau += get_tau(zt_m-z, zt_m-zs_m); // fore
      if (zs_p<zt_p && z>=zs_p) tau += get_tau(z-zs_p, zt_p-zs_p); // aft
    }
    if (nsd>3) error("Helmholtz::Sponge() unsupported nsd");

    return tau;
  }
};

void Helmholtz::Sponge::apply( const Scalar time, const vField &Us,
                               vField &Ur ) {
  boost::array<Element*,2> S, R;
  for (LocalSize e=0; e<Us[0]->ne; e++) {
    S[0] = Us[0]->el[e];  // local version of the state
    S[1] = Us[1]->el[e];
    R[0] = Ur[0]->el[e];  // local version of the RHS
    R[1] = Ur[1]->el[e];
    compute_reaction(S, R[0]->u, R[1]->u);
  }
}

void Helmholtz::Sponge::adjoint_apply(const Scalar time, const vField &Ustate,
                                      const vField &Us, vField &Ur ) {
  error("Helmholtz::Spongs::adjoint_apply not implemented");
}

} // namespace Reo

#endif // REO_HELMHOLTZ_BC_HPP
