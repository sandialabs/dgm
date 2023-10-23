#ifndef REO_MAXWELL_IC_HPP
#define REO_MAXWELL_IC_HPP

/** \file MaxwellIC.hpp
    \brief Compressible Maxwell initial conditions
    \author S. Scott Collis
*/

// system includes
#include <iostream>

// local includes
#include "Comm.hpp"
#include "Types.hpp"
#include "Format.hpp"
#include "IC.hpp"

#ifdef DGM_USE_BOOST_RANDOM
// #include "boost/random.hpp"
#endif

#ifdef DGM_USE_BOOST_MATH
#include "boost/math/special_functions/expint.hpp"
#endif

#ifdef DGM_USE_FFTW
#include "rfftw.h"
#endif

namespace Reo {

// put initial condition classes here

} // namespace

#endif  // REO_MAXWELL_IC_HPP
