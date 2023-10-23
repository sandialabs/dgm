#ifndef DGM_SEARCH_HPP
#define DGM_SEARCH_HPP

/** \file Search.hpp
    \brief Search for elements in mesh containing a certain point*/

// System includes
#include <map>

// Local includes
#include "Types.hpp"
#include "Field.hpp"

namespace DGM {

/// Helper functions for Searching for Elements within a Field
namespace Search {

/// Search for the elements of a field containing a point.
/** NOTE: This is a local search only! Both the Trilinos and non-Trilinos
versions should return the same thing; a list of elements defined by this
field on this processor.  The extension of the Trilinos search to the whole
processsor mesh is trivial, just change the communicator.  But to extend
the non-Trilinos search to the entire mesh is more difficult. */
void field(std::multimap<unsigned, unsigned> &elements,
           const Field *F,
           const dMatrix &centroids,
           const Scalar radius);

}

} // namespace DGM

#endif  // DGM_SEARCH_HPP

