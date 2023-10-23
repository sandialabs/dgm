#ifndef DGM_MATERIAL_HPP
#define DGM_MATERIAL_HPP

/** \file Material.hpp
    \brief Material class declaration
    \author Scott Collis
*/

// system includes
#include <string>

namespace DGM {

//============================================================================
// Material is an abstract base class that represents generic materials
//============================================================================

// Clearly there is not much (anything) in here, but one could add general
// utilities such as writing out a material state to a stream or asking
// what type of material it is.  The first step in this is that the Material
// holds its name so that one can query that.

/// Abstract Material class
class Material {
  string name;  ///< the name of this material
public:
  /// Constructor
  Material(const string iname="Material") : name(iname) {}
  /// Destructor
  virtual ~Material() {}
  /// Accessor for the name of this Material
  string get_name() {return name;}
};

/// Abstract Solid Material
class Solid : public Material {
public:
  /// Constructor
  Solid(const string iname="Solid") : Material(iname) {}
};

} // namespace DGM

#endif  // DGM_ MATERIAL_HPP
