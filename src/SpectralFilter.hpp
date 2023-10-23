#ifndef DGM_SPECTRAL_FILTER_HPP
#define DGM_SPECTRAL_FILTER_HPP

/** \file SpectralFilter.hpp
    \brief Declares a DGM spectral filter class
    \author Scott Collis
*/

// system includes
#include <fstream>
#include <cstdio>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

// DGM includes
#include "Filter.hpp"

namespace DGM {

/// Database of Filter function
/** Defines a database of filter functions to find transfer functions based on
    appropriate polynomial order, i.e. based on element type. */
class FilterDB {

public:
  typedef map<string,Filter*>::iterator iterator;

  map<string,Filter*> filters;
};

/// Spectral Filter
/** Spectral filter implementation based on the Boyd-Vandeven filter defined
    in "A spectral filtering procedure for eddy-resolving simulations with a
    spectral element ocean model" - Levin, G., Iskandarani, M., Haidvogel, D.,
    JCP vol.137 pp. 130-154, 1997.
*/
class SpectralFilter : public Filter {
public:
  Ordinal s;  ///< spectral shift parameter

  /// Constructor
  SpectralFilter(const Ordinal, const Ordinal, const string &);

  /// \name Methods
  void make_filter(const Ordinal, const Ordinal, dVector & );
  void make_filter(const Ordinal, const Ordinal, const char);

  /// Transfer function
  void get_kernel(const Ordinal);
};

} // namespace DGM

#endif  // DGM_SPECTRAL_FILTER_HPP
