/** \file clapack.cpp
    \brief This is the implementation of a partial C interface to the LAPACK
    \author Scott Collis
*/
#include <stdio.h>

#include "clapack.hpp"

// Use the correct FORTRAN function signature
#ifdef CMC_USE_MKL
#define ENUM
#define DGETRF DGETRF
#define DPOTRS DPOTRS
#define DGETRI DGETRI 
#define DGETRF DGETRF 
#define DGESV  DGESV 
#define DGETRS DGETRS 
#else
#define ENUM enum
#define SP_NAME(X) X##_
#define DPOTRF SP_NAME(dpotrf)
#define DPOTRS SP_NAME(dpotrs)
#define DGETRI SP_NAME(dgetri)
#define DGETRF SP_NAME(dgetrf)
#define DGESV  SP_NAME(dgesv)
#define DGETRS SP_NAME(dgetrs)
#endif

extern "C" {
int DPOTRF(char*, int*, double*, int*, int*);
int DGETRF(int*, int*, double*, int*, int*, int*);
int DPOTRS(char*, int*, int*, double*, int*, double*, int*, int*);
int DGETRI(int*, double*, int*, int*, double*, int*, int*);
int DGESV(int*, int*, double*, int*, int*, double*, int*, int*);
int DGETRS(char*, int*, int*, double*, int*, int*, double *, int*, int*);
}

int clapack_dpotrf(const ENUM CBLAS_ORDER Order,
                   const ENUM CBLAS_UPLO uplo, const int N,
                   double *A, const int lda) {
  if (Order != CblasRowMajor) {
    printf("Illegal value of CBLAS_ORDER\n");
    exit(EXIT_FAILURE);
  }
  int info=0;
  char tmp;
  if (uplo == CblasUpper) {
    tmp = 'U';
    DPOTRF( &tmp, const_cast<int*>(&N), A, const_cast<int*>(&lda), &info );
  } else if (uplo == CblasLower) {
    tmp = 'L';
    DPOTRF( &tmp, const_cast<int*>(&N), A, const_cast<int*>(&lda), &info );
  } else {
    printf("Illegal value of CBLAS_UPLO\n");
    exit(EXIT_FAILURE);
  }
  return info;
}

int clapack_dpotrs(const ENUM CBLAS_ORDER Order,
                   const ENUM CBLAS_UPLO uplo, const int N, const int nrhs,
                   const double *A, const int lda,
                   double *B, const int ldb) {
  if (Order != CblasRowMajor) {
    printf("Illegal value of CBLAS_ORDER\n");
    exit(EXIT_FAILURE);
  }
  int info=0;
  char tmp;
  if (uplo == CblasUpper) {
    tmp = 'U';
    DPOTRS( &tmp, const_cast<int*>(&N), const_cast<int*>(&nrhs), 
            const_cast<double*>(A), 
            const_cast<int*>(&lda), B, const_cast<int*>(&ldb), &info );
  } else if (uplo == CblasLower) {
    tmp = 'L';
    DPOTRS( &tmp, const_cast<int*>(&N), const_cast<int*>(&nrhs), 
            const_cast<double*>(A), 
            const_cast<int*>(&lda), B, const_cast<int*>(&ldb), &info );
  } else {
    printf("Illegal value of CBLAS_UPLO\n");
    exit(EXIT_FAILURE);
  }
  return info;
}

int clapack_dgetrf(const ENUM CBLAS_ORDER Order, const int M, const int N,
                   double *A, const int lda, int *ipiv) {
  int info;
  if (Order == CblasColMajor) {
    DGETRF( const_cast<int*>(&M), const_cast<int*>(&N), A, 
            const_cast<int*>(&lda), ipiv, &info );
  } else if (Order == CblasRowMajor) {
    DGETRF( const_cast<int*>(&N), const_cast<int*>(&M), A, 
            const_cast<int*>(&lda), ipiv, &info );
  } else {
    printf("Illegal value of CBLAS_ORDER\n");
    exit(EXIT_FAILURE);
  }
  return info;
}

int clapack_dgetri(const ENUM CBLAS_ORDER Order, const int N, double *A,
                   const int lda, const int *ipiv) {
  int info;
  int lwork = N*32;
  double *work = (double*)calloc(lwork,sizeof(double));
  if (Order == CblasColMajor) {
    DGETRI( const_cast<int*>(&N), A, const_cast<int*>(&lda), 
            const_cast<int*>(ipiv), work, &lwork, &info );
  } else if (Order == CblasRowMajor) {
    DGETRI( const_cast<int*>(&N), A, const_cast<int*>(&lda), 
            const_cast<int*>(ipiv), work, &lwork, &info );
  } else {
    printf("Illegal value of CBLAS_ORDER\n");
    exit(EXIT_FAILURE);
  }
  free(work);
  return info;
}

int clapack_dgesv(const ENUM CBLAS_ORDER Order, const int N, const int NRHS,
                  double *A, const int lda, int *ipiv,
                  double *B, const int ldb) {
  int info;
  if (Order == CblasColMajor) {
    DGESV( const_cast<int*>(&N), const_cast<int*>(&NRHS), A, 
           const_cast<int*>(&lda), ipiv, B, const_cast<int*>(&ldb), &info );
  } else if (Order == CblasRowMajor) {
    DGESV( const_cast<int*>(&N), const_cast<int*>(&NRHS), A, 
           const_cast<int*>(&lda), ipiv, B, const_cast<int*>(&ldb), &info );
  } else {
    printf("Illegal value of CBLAS_ORDER\n");
    exit(EXIT_FAILURE);
  }
  return info;
}

int clapack_dgetrs(const ENUM CBLAS_ORDER Order,
                   const ENUM CBLAS_TRANSPOSE Trans,
                   const int N, const int NRHS, const double *A,
                   const int lda, const int *ipiv, double *B,
                   const int ldb) {
  int info;
  char trans[1];
  if (Order == CblasColMajor) {
    if (Trans == CblasNoTrans)
      *trans = 'N';
    else if (Trans == CblasTrans)
      *trans = 'T';
    else if (Trans == CblasConjTrans)
      *trans = 'C';
    DGETRS( trans, const_cast<int*>(&N), const_cast<int*>(&NRHS), 
            const_cast<double*>(A), const_cast<int*>(&lda), 
            const_cast<int*>(ipiv), B, const_cast<int*>(&ldb), &info );
  } else if (Order == CblasRowMajor)  {
    if (Trans == CblasNoTrans)
      *trans = 'T';
    else if (Trans == CblasTrans)
      *trans = 'N';
    else if (Trans == CblasConjTrans) {
      printf("CblasConjTran not implemented\n");
      exit(EXIT_FAILURE);
    }
    DGETRS( trans, const_cast<int*>(&N), const_cast<int*>(&NRHS), 
            const_cast<double*>(A), const_cast<int*>(&lda), 
            const_cast<int*>(ipiv), B, const_cast<int*>(&ldb), &info );
  } else {
    printf("Illegal value of CBLAS_ORDER\n");
    exit(EXIT_FAILURE);
  }
  return info;
}
