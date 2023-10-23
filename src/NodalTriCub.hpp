#ifndef DGM_NODALTRICUB_HPP
#define DGM_NODALTRICUB_HPP

/** \file NodalTriCub.hpp
    \brief Cubiture rules for triangles up to arbitrary order
    \author James Overfelt

    Lower order rules have symmetric expansions taken from
    Hesthaven & Warburton, "Nodal Discontinuous Balerkin Methods".
    Higher order rules are the cartesian product of Gauss and Radau
    on the quad with a collapsed edge along the Radau side.

*/
/// Undefine this to turn this feature off if you need to build without C++11
#define DGM_USE_NODAL_TRI_CUB

#ifdef DGM_USE_NODAL_TRI_CUB

#include <vector>
#include <array>

namespace DGM {
  const std::vector< std::array<double,3> > &NodalTriCub(const Ordinal q);
}

#endif   // DGM_USE_NODAL_TRI_CUB

#endif   // DGM_NODALTRILCUB_HPP
