/** \file Cartesian.hpp
    \brief Define a Cartesian space
    \author K. Noel Belcourt
*/

#ifndef DGM_Cartesian_hpp
#define DGM_Cartesian_hpp

// standard libraries
#include <ostream>
#include <string>

namespace DGM {

typedef enum {
  one_d, two_d, three_d
} dimension;

typedef enum {
    X_axis = 0
  , Y_axis = 1
  , Z_axis = 2
} axis;

struct X {};
struct XY {};
struct YZ {};
struct ZX {};
struct XYZ {};

template <typename Space>
unsigned int n_dimensions(Space);

template <>
inline unsigned int n_dimensions(XY) {
  return 2;
}

template <>
inline unsigned int n_dimensions(XYZ) {
  return 3;
}

inline std::string to_string(axis a) {
  using std::string;
  string axes[] = { "X", "Y", "Z" };
  return axes[a];
}

inline std::ostream& operator<<(std::ostream& ofp, axis a) {
  ofp << "cartesian " << to_string(a) << " axis";
  return ofp;
}

}  // namespace DGM

#endif
