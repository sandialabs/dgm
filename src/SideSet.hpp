#ifndef DGM_SIDELOOP_HPP
#define DGM_SIDELOOP_HPP

/*! \file SideSet.hpp 
    \brief An iterator-like class for looping over sides
    \author Scott Collis
*/

// DGM includes
#include "Config.hpp"
#include "Types.hpp"
#include "Constants.hpp"
#include "Field.hpp"
#include "vField.hpp"
#include "Element.hpp"
#include "Side.hpp"
#include "SideLoop.hpp"

namespace DGM {

/// A more powerful SideSet
/*! There is a need to have a more powerful abstraction of a side loop
    that allows looping over a collection of sides
*/
class SideSet {
vector<Side*> sides;
vector<Side*> links;
public:
/// Constructor
SideSet(const vField &F) {
  for (LocalSize e=0; e<F[0]->ne, e++) {
    Element *E = F[0]->el[e];
    for (SideLoop S(E); !S.end(); ++S) {
      if (S.master_side()) {
        sides.push_back(S.side(E));
        links.push_back(S.link(E));
      }
    }
  }
};

} // namespace DGM
