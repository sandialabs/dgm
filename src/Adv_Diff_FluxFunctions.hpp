/**
 * \file Adv_Diff_FluxFunctions.hpp
 * \brief Templated flux functions for testing AD
 * \author John Mitchell
 *
 *  Created on: Oct 24, 2013
 *  Author: jamitch
 */

#ifndef REO_ADV_DIFF_FLUXFUNCTIONS_HPP
#define REO_ADV_DIFF_FLUXFUNCTIONS_HPP

// system includes
#include <algorithm>

namespace Reo {

namespace Adv_Diff_Flux {

template<typename T> struct flux {
  T fl, fr;
  T sl, sr;
};

template<typename T, typename DT>
struct ConstantAdvection {
  const DT c[3];
  flux<DT> eval(const T n[3], T ul, T ur) {
    DT cn = c[0] * n[0] + c[1] * n[1] + c[2] * n[2];
    if (cn < 0) {
      return flux<DT> { -ur, ur, ul * cn, -ur * cn };
    } else {
      return flux<DT> { ul, -ul, ul * cn, -ur * cn };
    }
  }
};

template<typename T, typename DT>
struct VariableAdvection {
  const DT cl[3], cr[3];
  flux<DT> eval(const T n[3], T ul, T ur) {
    DT cnl = cl[0] * n[0] + cl[1] * n[1] + cl[2] * n[2];
    DT fpl = cnl * ul;
    DT cnr = cr[0] * n[0] + cr[1] * n[1] + cr[2] * n[2];
    DT fmr = cnr * ur;

    // Lax-Friedrichs flux
    DT lmax = std::max(fabs(cnl),fabs(cnr));
    DT fh = 0.5 * ( fpl + fmr + lmax * (ul - ur) );
    // put numerical flux on the flux field sides
    // put interior flux on the state field sides
    return flux<DT> { fh, -fh, fpl, -fmr };
  }
};

} // Adv_Diff_Flux

} // Reo

#endif /* REO_ADV_DIFF_FLUXFUNCTIONS_HPP */
