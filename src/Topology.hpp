#ifndef DGM_TOPOLOGY_HPP
#define DGM_TOPOLOGY_HPP

/** \file Topology.hpp
    \brief Defines the topologies (shapes of elements) available in DGM
    \author Noel Belcourt
    \author Scott Collis
*/

// system includes
#include <string>
#include <vector>

// local includes
#include "CaseInsensitiveString.hpp"

namespace DGM {

  /// Defines the topologies (element types) supported by DGM
  namespace Topology {

    /// size type for topology
    typedef unsigned size_type;

    /// Number of element types
    static const size_type NumElementTypes = 15;

    /// Supported mesh element types
    enum ElementType {
      Line=0,                     ///< Line element in 1d
      Quad=1,                     ///< Quad element in 2d
      Tri=2,                      ///< Triangular element in 2d
      Hex=3,                      ///< Hexahedral element in 3d
      Tet=4,                      ///< Tetahedral element in 3d
      Pyramid=5,                  ///< Pyramid element in 3d
      NodalLine=6,                ///< Nodal 1d line element
      NodalQuad=7,                ///< Nodal 2d quad element
      NodalHex=8,                 ///< Nodal 3d hex element
      NodalTri=9,                 ///< Nodal 2d triangular element
      NodalTet=10,                ///< Nodal 3d tetrahedral element
      SpectralLine=11,            ///< Spectral 1d line element
      SpectralQuad=12,            ///< Spectral Quad 2d element
      SpectralHex=13,             ///< Spectral Hex 3d element
      Slab=14                     ///< Slab
    };

    /// element geometric dimension used to set default graph weights
    unsigned dimension(ElementType et);

    /// convert string to element type
    ElementType string2ElementType(case_insensitive_string s);

    /// Provides element names
    void names(std::vector<std::string> &e);

    /// Get number of sides (faces) for this element type
    unsigned int num_sides(ElementType et);

    /// Get number of vertices for this element type
    unsigned int num_vertices(ElementType et);

    /// Return string valid for use in root.msh file
    std::string topology_name(ElementType et);

  }  // namespace Topology

}  // namespace DGM

#endif
