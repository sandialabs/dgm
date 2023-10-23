#include "Types.hpp"
#include "Polylib.hpp"
#include "Polylib.tpp"
#include "Matrix.hpp"

/** \file Polylib.cpp
    \brief Explicit instantiations of Polylib for DGM types
    \author Scott Collis
*/

namespace DGM {

// This explicitly instantiates these templates on the DGM Scalar and
// Ordinal types

template void jacobf(Ordinal, const Scalar *, Scalar *, Ordinal, Scalar, Scalar);
template void jacobd(Ordinal, const Scalar *, Scalar *, Ordinal, Scalar, Scalar);
template void jacobd2(Ordinal, const Scalar *, Scalar *, Ordinal, Scalar, Scalar);

template void fntri(Ordinal, Ordinal, Scalar *, Scalar *, 
                    CMC::Matrix<Scalar,Ordinal>&);
template void fntet(const Ordinal, const Ordinal,
                    const Scalar *, const Scalar *, const Scalar *,
                    CMC::Matrix<Scalar,Ordinal>&);


template void zwgj(Scalar *, Scalar *, Ordinal, Scalar, Scalar);
template void zwgrj(Scalar *, Scalar *, Ordinal, Scalar, Scalar);
template void zwglj(Scalar *, Scalar *, Ordinal, Scalar, Scalar);

template void zwntri(Scalar *, Scalar *, Ordinal);
template void zwntet(Scalar *, Scalar *, Scalar *, Ordinal);

template void dgj(CMC::Matrix<Scalar,Ordinal>&, CMC::Matrix<Scalar,Ordinal>&, 
                  Scalar *, Ordinal, Scalar, Scalar);
template void dgrj(CMC::Matrix<Scalar,Ordinal>&, CMC::Matrix<Scalar,Ordinal>&, 
                   Scalar *, Ordinal, Scalar, Scalar);
template void dglj(CMC::Matrix<Scalar,Ordinal>&, CMC::Matrix<Scalar,Ordinal>&,
                   Scalar *, Ordinal, Scalar, Scalar);

template void dntri(CMC::Matrix<Scalar,Ordinal>&, CMC::Matrix<Scalar,Ordinal>&,
                    Scalar *, Scalar *, Ordinal);
template void dntet(CMC::Matrix<Scalar,Ordinal>&,
                    CMC::Matrix<Scalar,Ordinal>&,
                    CMC::Matrix<Scalar,Ordinal>&,
                    const Scalar*,const Scalar*,const Scalar*,Ordinal);

template void igjm(CMC::Matrix<Scalar,Ordinal>&,
                   Scalar*, const Scalar*, Ordinal, Ordinal,
                   Scalar, Scalar);
template void igrjm(CMC::Matrix<Scalar,Ordinal>&,
                    Scalar*, const Scalar*, Ordinal, Ordinal,
                    Scalar, Scalar);
template void igljm(CMC::Matrix<Scalar,Ordinal>&,
                    const Scalar*, const Scalar*, Ordinal, Ordinal,
                    Scalar, Scalar);
template void zwgrj(float *, float *, Ordinal, float, float);
template void zwglj(float *, float *, Ordinal, float, float);
template void igrjm(CMC::Matrix<float,Ordinal>&,
                    float*, const float*, Ordinal, Ordinal,
                    float, float);
template void igljm(CMC::Matrix<float,Ordinal>&, const float*, const float*, Ordinal, Ordinal,
                    float, float);

#ifdef DGM_POLYLIB_MORE_EXPLICIT
// Likely shouldn't need these, but if you compile on non-int for Ordinal
// and Scalar then you need these.
template void jacobf(Size, const Scalar *, Scalar *, Size, Scalar, Scalar);
template void jacobd(Size, const Scalar *, Scalar *, Size, Scalar, Scalar);
template void jacobd2(Size, const Scalar *, Scalar *, Size, Scalar, Scalar);

template void zwgj(Scalar *, Scalar *, Size, Scalar, Scalar);
template void zwgrj(Scalar *, Scalar *, Size, Scalar, Scalar);
template void zwglj(Scalar *, Scalar *, Size, Scalar, Scalar);

template void dgj(CMC::Matrix<Scalar,Ordinal>&, CMC::Matrix<Scalar,Ordinal>&, 
                  Scalar *, Size, Scalar, Scalar);
template void dgrj(CMC::Matrix<Scalar,Ordinal>&, CMC::Matrix<Scalar,Ordinal>&,
                   Scalar *, Size, Scalar, Scalar);
template void dglj(CMC::Matrix<Scalar,Ordinal>&, CMC::Matrix<Scalar,Ordinal>&,
                   Scalar *, Size, Scalar, Scalar);

template void igjm(CMC::Matrix<Scalar,Ordinal>&,
                   Scalar*, const Scalar*, Size, Size,
                   Scalar, Scalar);
template void igrjm(CMC::Matrix<Scalar,Ordinal>&,
                    Scalar*, const Scalar*, Size, Size,
                    Scalar, Scalar);
template void igljm(CMC::Matrix<Scalar,Ordinal>&,
                    const Scalar*, const Scalar*, Size, Size,
                    Scalar, Scalar);
template void zwgrj(float *, float *, Size, float, float);
template void zwglj(float *, float *, Size, float, float);
template void igrjm(CMC::Matrix<float,Ordinal>&,
                    float*, const float*, Size, Size,
                    float, float);
template void igljm(CMC::Matrix<float,Ordinal>&, const float*, const float*, Size, Size,
                    float, float);
#endif

}  // namespace DGM
