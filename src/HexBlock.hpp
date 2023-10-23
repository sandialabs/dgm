#ifndef DGM_HEX_BLOCK_HPP
#define DGM_HEX_BLOCK_HPP

/** \file HexBlock.hpp
    \brief HexBlock declaration
    \author James Overfelt
    \author Scott Collis
    \author K. Noel Belcourt
*/

// system includes
#include <cstdio>
#include <fstream>
#include <string>
#include <vector>

// DGM includes
#include "Comm.hpp"
#include "Hex.hpp"
#include "Element.hpp"
#include "ElementBlock.hpp"
#include "Types.hpp"
#include "Parser.hpp"
#include "Utils.hpp"

// Cuda (and eventually Kokkos)
#if defined(DGM_USE_CUDA) || defined(DGM_USE_KOKKOS)
#include "GpGpu.hpp"
#endif

namespace DGM {

/// Element block abstract base class.
/** Note this is not a PURE abstract class. */
class HexBlock : public ElementBlock {

public:

  HexBlock(Element *e, const Ordinal blocksize);
  virtual ~HexBlock() {}

  virtual void forward_transform(ElementBlock *F, ElementBlock *);

  virtual void backward_transform();

  virtual void gradient(const dVector &f, dVector &fx,
                        dVector &fy, dVector &fz) const;
  virtual void lift(ElementBlock *eb, dVector &in, const char dir='n') const;

private:

  // do not allow copy construction
  HexBlock(const HexBlock &QB);
  HexBlock(const HexBlock *QB);

#if defined(DGM_USE_CUDA) || defined(DGM_USE_KOKKOS)
  GpGpu::hex_kernels gpu_hex;

  /// Allocate Gpu memory and other initialization
  virtual void initialize_gpu();
#endif

  dVector flux_vector(const ElementBlock *Fb,
                      const char dir,
                      const Ordinal qtot_edges,
                      const Ordinal edge) const;
};

} // namespace DGM

#endif  // DGM_HEX_BLOCK_HPP
