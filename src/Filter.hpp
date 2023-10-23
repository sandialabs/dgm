#ifndef DGM_FILTER_HPP
#define DGM_FILTER_HPP

/** \file Filter.hpp
    \brief Declares and defines the DGM Filter class
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
#include "Comm.hpp"
#include "Types.hpp"
#include "Element.hpp"

namespace DGM {

/// General spatial Filter class
class Filter {
public:
  Ordinal P;                ///< Polynomial order (discretization parameter)
  Ordinal fdim;             ///< Filter spatial dimension
  char dir;                 ///< Direction of filter

  dVector filter_a;         ///< Filter Transfer function in 'a' dir.
  dVector filter_b;         ///< Filter Transfer function in 'b' dir.
  dVector filter_c;         ///< Filter Transfer function in 'c' dir.

  dVector kernel;           ///< Filter mask/kernel

  // only derived classes can construct filter

  /// do not allow copy construction
  virtual void make_filter(const Ordinal, const Ordinal, dVector &)=0;
  /// constructor call to make filter
  virtual void make_filter(const Ordinal, const Ordinal, const char)=0;

  /// make filter kernel for efficient filter application
  virtual void  get_kernel(const Ordinal)=0;

  /// destructor
  virtual ~Filter() {}

protected:
  /// Default constructor
  inline Filter( Ordinal P_=0, Ordinal fdim_=0) : P(P_), fdim(fdim_) {}

private:
  /// do not allow copy construction
  inline Filter(const Filter&);
  /// do not allow copy construction
  inline Filter(const Filter*);
};

/// copy constructor
Filter::Filter(const Filter &F) {
  DGM::Comm::World->cout()
    << "Filter reference copy constructor not implemented!" << endl;
  DGM::Comm::World->exit(DGM::FAILURE);
}

/// copy constructor
Filter::Filter(const Filter *F) {
  DGM::Comm::World->cout()
    << "Filter pointer copy constructor not implemented!" << endl;
  DGM::Comm::World->exit(DGM::FAILURE);
  *this = *F;
}

} // namespace DGM

#endif  // DGM_FILTER_HPP
