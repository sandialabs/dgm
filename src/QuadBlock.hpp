#ifndef DGM_QUAD_BLOCK_HPP
#define DGM_QUAD_BLOCK_HPP

/** \file QuadBlock.hpp
    \brief QuadBlock declaration
    \author James Overfelt
    \author Scott Collis
*/

// system includes
#include <cstdio>
#include <fstream>
#include <string>
#include <vector>

// DGM includes
#include "Comm.hpp"
#include "Quad.hpp"
#include "Element.hpp"
#include "ElementBlock.hpp"
#include "Types.hpp"
#include "Parser.hpp"
#include "Utils.hpp"

namespace DGM {

/// Element block abstract base class. Note this is not a PURE abstract class
class QuadBlock : public ElementBlock {

public:

  QuadBlock(Element *e, const Ordinal blocksize) :
    ElementBlock(e, blocksize), scratcha(), scratchb() {}

  virtual ~QuadBlock() {}

  virtual void gradient(const dVector &f, dVector &fx, dVector &fy) const;
  virtual void gradient(const dVector &f, dVector &fx, char dir) const;

  virtual void lift(ElementBlock *eb, dVector &in, const char dir='n') const;

  virtual void inner_product(dVector &f, dVector &fh) const;
  virtual void forward_transform(ElementBlock *F, ElementBlock *);
  virtual void solve_mass_matrix(dVector&) const ;

private:

  /// first scratch memory location
  mutable dVector scratcha;
  /// second scratch memory location
  mutable dVector scratchb;

  /// do not allow copy construction
  QuadBlock(const QuadBlock &QB);
  /// do not allow copy construction
  QuadBlock(const QuadBlock *QB);

  dVector flux_vector(const ElementBlock *Fb,
                      const char dir,
                      const Ordinal qtot_edges,
                      const Ordinal edge) const;
};

} // namespace DGM

#endif  // DGM_QUAD_BLOCK_HPP
