/** \file clapack.hpp
    \brief This is a partial C interface to the LAPACK.
    \author Scott Collis

    It is needed when C-LAPACK is not available as part of a more complete
    math library on your system.  In particular, ATLAS supplied a version of
    C-LAPACK that makes this file unneeded.
*/
#ifndef CMC_CLAPACK_HPP
#define CMC_CLAPACK_HPP

#include "stdlib.h"

#define CMC_CLAPACK_VERSION "1.0.0"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef CMC_USE_MKL
#include "mkl.h"
#define ENUM
#else
#include "cblas.h"
#define ENUM enum
#endif

int clapack_dgetrf(const ENUM CBLAS_ORDER Order, const int M, const int N,
                   double *A, const int lda, int *ipiv);

int clapack_dgetri(const ENUM CBLAS_ORDER Order, const int N, double *A,
                   const int lda, const int *ipiv);

int clapack_dgesv(const ENUM CBLAS_ORDER Order, const int N, const int NRHS,
                 double *A, const int lda, int *ipiv,
                 double *B, const int ldb);

int clapack_dgetrs (const ENUM CBLAS_ORDER Order,
                    const ENUM CBLAS_TRANSPOSE Trans,
                    const int N, const int NRHS, const double *A,
                    const int lda, const int *ipiv, double *B,
                    const int ldb);

int clapack_dpotrf(const ENUM CBLAS_ORDER Order,
                   const ENUM CBLAS_UPLO uplo, const int N,
                   double *A, const int lda);

int clapack_dpotrs(const ENUM CBLAS_ORDER Order,
                   const ENUM CBLAS_UPLO uplo, const int N, const int nrhs,
                   const double *A, const int lda,
                   double *B, const int ldb);

#undef ENUM

#ifdef __cplusplus
}
#endif

#endif  // CMC_CLAPACK_HPP
