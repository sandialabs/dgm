#ifndef DGM_SIDELOOP_HPP
#define DGM_SIDELOOP_HPP

/*! \file SideLoop.hpp 
    \brief An iterator-like class for looping over sides
    \author James Overfelt
*/

// DGM includes
#include "Config.hpp"
#include "Types.hpp"
#include "Constants.hpp"
#include "Element.hpp"
#include "Side.hpp"

namespace DGM {

/// Enables simple loops over sides and subsides
/*! This is used in the convective_flux function of derived codes
      to simplify the looping over of sides and subsides. The
      subsides are due to hanging nodes.
*/
struct SideLoop {
  Ordinal s;         ///< The local side id
  Ordinal ss;        ///< The local sub-side id
  Ordinal nss;       ///< The number of sub-sides
  const Element *E;  ///< The element for these sides
  const Side    *S;  ///< Pointer to the current side
  /// Constructor
  SideLoop(const Element *e) :
    s     (0),
    ss    (0),
    nss   (numeric_cast<Ordinal>(e->side[0]->subsides().size())),
    E     (e),
    S(side(e))
  {
  }
  /// Determine if at end of sides
  bool end() const {
    if (!E->skip_element()) return !(s<E->nSides());
    return true;
  }
  /// Return true if there are sub-sides
  bool has_subsides() const {return nss;}
  /// Return true if on the master side
  bool master_side() const {
    return // compute if link defined
        (!has_subsides() && E->side[s]->link) ||
        ( has_subsides() && E->side[s]->subsides()[ss]->master());
  }
  /// Increment the SideLoop
  SideLoop& operator++() {
    ++ss;
    if (nss<=ss) {
      ++s;
      ss=0;
      nss = end() ? 0 : numeric_cast<Ordinal>(E->side[s]->subsides().size());
    }
    S = end() ? NULL : side(E);
    return *this;
  }
  /// Number of quadrature points on current side (sub-side)
  Ordinal qtot() const {
    return has_subsides() ? E->side[s]->subsides()[ss]->qtot():
        E->side[s]->qtot();
  }
  /// Returns a pointer either the local side or sub-side
  Side * side(const Element *e) const {
    return has_subsides() ? e->side[s]->subsides()[ss].get():
        e->side[s];
  }
  /// Returns a pointer to either the adjacent side or sub-side
  Side * link(const Element *e) const {
    return has_subsides() ? e->side[s]->subsides()[ss]->link:
        e->side[s]->link;
  }
  /// Returns the normal x-component at the ith quadrature point
  Scalar nx(const Ordinal i) const { return S->nx(i); }
  /// Returns the normal y-component at the ith quadrature point
  Scalar ny(const Ordinal i) const { return S->ny(i); }
  /// Returns the normal z-component at the ith quadrature point
  Scalar nz(const Ordinal i) const { return S->nz(i); }
};

} // namespace DGM

#endif // DGM_SIDELOOP_HPP
