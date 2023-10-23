/** \file Topology.cpp
    \brief Defines the topologies (element shapes) available in DGM
    \author Noel Belcourt
    \author Scott Collis
*/

// system includes
#include <cassert>
#include <string>
#include <vector>

// local includes
#include "Topology.hpp"

using std::string;
using std::vector;

namespace DGM {

  namespace Topology {

    /// element geometric dimension used to set default graph weights
    unsigned dimension(ElementType et) {
      switch (et) {
        case Topology::Line:
        case Topology::SpectralLine:
        case Topology::NodalLine:
          return 1;
        case Topology::Slab:
        case Topology::Quad:
        case Topology::Tri:
        case Topology::NodalQuad:
        case Topology::NodalTri:
        case Topology::SpectralQuad:
          return 2;
        case Topology::Hex:
        case Topology::Tet:
        case Topology::Pyramid:
        case Topology::NodalHex:
        case Topology::NodalTet:
        case Topology::SpectralHex:
          return 3;
        default:
          return 0;
      }
    }

    /// convert string to element type
    ElementType string2ElementType(case_insensitive_string s) {
      if (s == "SpectralLine") return Topology::SpectralLine;
      else if (s == "NodalLine") return Topology::NodalLine;
      else if (s == "Slab") return Topology::Slab;
      else if (s == "Quad") return Topology::Quad;
      else if (s == "SpectralQuad") return Topology::SpectralQuad;
      else if (s == "NodalQuad") return Topology::NodalQuad;
      else if (s == "Tri") return Topology::Tri;
      else if (s == "NodalTri") return Topology::NodalTri;
      else if (s == "Hex") return Topology::Hex;
      else if (s == "SpectralHex") return Topology::SpectralHex;
      else if (s == "NodalHex") return Topology::NodalHex;
      else if (s == "Tet") return Topology::Tet;
      else if (s == "NodalTet") return Topology::NodalTet;
      else if (s == "Pyramid") return Topology::Pyramid;
      return Topology::Line;
    }

    /// Provides element names
    void names(vector<string>& e) {
      e.push_back("line");
      e.push_back("quad");
      e.push_back("tri");
      e.push_back("hex");
      e.push_back("tet");
      e.push_back("pyramid");
      e.push_back("nodalline");
      e.push_back("nodalquad");
      e.push_back("nodalhex");
      e.push_back("nodaltri");
      e.push_back("nodaltet");
      e.push_back("spectraline");
      e.push_back("spectralquad");
      e.push_back("spectralhex");
      e.push_back("slab");
    }

    /// Get number of sides (3d faces) of this element type
    unsigned int num_vertices(Topology::ElementType et) {
      switch (et) {
      case Topology::Line:
      case Topology::SpectralLine:
      case Topology::NodalLine:
        return 2;
      case Topology::Tri:
      case Topology::NodalTri:
        return 3;
      case Topology::Slab:
      case Topology::Quad:
      case Topology::NodalQuad:
      case Topology::SpectralQuad:
      case Topology::Tet:
      case Topology::NodalTet:
        return 4;
      case Topology::Pyramid:
        return 5;
      case Topology::Hex:
      case Topology::NodalHex:
      case Topology::SpectralHex:
        return 8;
      default:
        assert(0);
      }
      return 0;
    }

    /// Get number of sides (3d faces) of this element type
    unsigned int num_sides(Topology::ElementType et) {
      switch (et) {
      case Topology::Line:
      case Topology::SpectralLine:
      case Topology::NodalLine:
        return 2;
      case Topology::Tri:
      case Topology::NodalTri:
        return 3;
      case Topology::Slab:
      case Topology::Quad:
      case Topology::NodalQuad:
      case Topology::SpectralQuad:
      case Topology::Tet:
      case Topology::NodalTet:
        return 4;
      case Topology::Pyramid:
        return 5;
      case Topology::Hex:
      case Topology::NodalHex:
      case Topology::SpectralHex:
        return 6;
      default:
        assert(0);
      }
      return 0;
    }

    /// Return string valid for use in root.msh file
    string topology_name(ElementType et) {
      string s;
      switch (et) {
      case Topology::Line:
        s = "LINE";
        break;
      case Topology::SpectralLine:
        s = "SPECTRAL_LINE";
        break;
      case Topology::NodalLine:
        s = "NODAL_LINE";
        break;
      case Topology::Tri:
        s = "TRI";
        break;
      case Topology::NodalTri:
        s = "NODAL_TRI";
        break;
      case Topology::Slab:
        s = "SLAB";
        break;
      case Topology::Quad:
        s = "QUAD";
        break;
      case Topology::NodalQuad:
        s = "NODAL_QUAD";
        break;
      case Topology::SpectralQuad:
        s = "SPECTRAL_QUAD";
        break;
      case Topology::Tet:
        s = "TET";
        break;
      case Topology::NodalTet:
        s = "NODAL_TET";
        break;
      case Topology::Pyramid:
        s = "PYRAMID";
        break;
      case Topology::Hex:
        s = "HEX";
        break;
      case Topology::NodalHex:
        s = "NODAL_HEX";
        break;
      case Topology::SpectralHex:
        s = "SPECTRAL_HEX";
        break;
      default:
        assert(0);
      }
      return s;
    }

  }  // namespace Topology

} // namespace DGM
