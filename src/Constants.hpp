#ifndef DGM_CONSTANTS_HPP
#define DGM_CONSTANTS_HPP

/** \file Constants.hpp
    \brief Defines a number of useful constants available in the DGM namespace
    \author Scott Collis
*/

// system includes
#include <cfloat>
#include <complex>
#include <limits>

// DGM includes
#include "Types.hpp"

namespace DGM {
  
  const int BUFLEN = 256;   ///< standard length of a char buffer

  // Using these makes sure that constants are at the correct precision

  const Scalar zero    = (Scalar)0.0;                   ///< zero
  const Scalar pt5     = (Scalar)0.5;                   ///< one half
  const Scalar pt25    = (Scalar)0.25;                  ///< one quarter
  const Scalar pt33    = (Scalar)0.3333333333333333333; ///< one third
  const Scalar pt66    = (Scalar)0.6666666666666666667; ///< two thirds
  const Scalar one     = (Scalar)1.0;                   ///< one
  const Scalar onept25 = (Scalar)1.25;                  ///< one and one-quarter
  const Scalar onept33 = (Scalar)1.3333333333333333333; ///< one and one-third
  const Scalar onept5  = (Scalar)1.5;                   ///< one and one-half
  const Scalar two     = (Scalar)2.0;                   ///< two
  const Scalar three   = (Scalar)3.0;                   ///< three
  const Scalar pi      = (Scalar)3.1415926535897932385; ///< \f$\pi\f$
  const Scalar four    = (Scalar)4.0;                   ///< four

  /// Imaginary one, \f$\iota\f$
  const complex<Scalar> im = complex<Scalar>(zero,one);

  /// Machine precision
  const Scalar epsM    = std::numeric_limits<Scalar>::epsilon();
  const Scalar repsM   = (Scalar)sqrt(epsM);            ///< relative tolerance
  const Scalar aepsM   = (Scalar)pow(epsM,pt66);        ///< absolute tolerance
  const Scalar tiny    = (Scalar)aepsM;                 ///< A tiny number

} // namespace DGM

#endif  // DGM_CONSTANTS_HPP
