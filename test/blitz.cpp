#include <algorithm>

// Using Blitz with Atlas/Blas

// Atlas 

extern "C" {
#include "cblas.h"
int clapack_dgetrf(const enum CBLAS_ORDER Order, const int M, const int N,
                   double *A, const int lda, int *ipiv);
int clapack_dgesv(const enum CBLAS_ORDER Order, const int N, const int NRHS, 
                  double *A, const int lda, int *ipiv, 
                  double *B, const int ldb);
void clapack_dgetrs (const enum CBLAS_ORDER Order, 
		     const enum CBLAS_TRANSPOSE Trans,
		     const int N, const int NRHS, const double *A, 
		     const int lda, const int *ipiv, double *B, const int ldb);
}

// Blitz++

#include <blitz/Array.h>
using namespace blitz;

typedef Array<double,2> dMatrix;
typedef Array<double,1> dVector;
typedef Array<int,1>    iVector;

// TNT

#include <tnt/tnt.h>
#include <tnt/stopwatch.h>
using TNT::stopwatch;

// Interface Blitz to Atlas/Blas

inline void daxpy( const double alpha, Array<double,1> &X, 
		   Array<double,1> &Y) {
  const int stride = 1;
  cblas_daxpy( X.size(), alpha, X.data(), stride, Y.data(), stride );
} 
inline void matmult(Array<double,2> &A, Array<double,2> &B, 
		    Array<double,2> &C) {
  double alpha = 1.0;
  double beta = 0.0;
  cblas_dgemm( CblasRowMajor, CblasNoTrans, CblasNoTrans, 
	       A.rows(), B.cols(), A.cols(), alpha,
	       A.data(), A.cols(), B.data(), B.cols(), beta, 
	       C.data(), C.cols() );
}
inline void gmatmult(const double alpha, Array<double,2> &A, 
		     Array<double,2> &B, const double beta, 
		     Array<double,2> &C) {
  cblas_dgemm( CblasRowMajor, CblasNoTrans, CblasNoTrans, 
	       A.rows(), B.cols(), A.cols(), alpha,
	       A.data(), A.cols(), B.data(), B.cols(), beta, 
	       C.data(), C.cols() );
}
inline int LU_factor( Array<double,2> &A, Array<int,1> &A_pivots ) {
  A_pivots.resize( min(A.rows(),A.cols()) );
  return clapack_dgetrf( CblasRowMajor, A.rows(), A.cols(), A.data(), 
			 A.cols(), A_pivots.data() );
}
inline void LU_solve( Array<double,2> &A, Array<int,1> &A_pivots, 
		      Array<double,1> &X ) {
  const int NRHS = 1;
  clapack_dgetrs( CblasRowMajor, CblasNoTrans, A.rows(), NRHS, 
		  A.data(), A.cols(), A_pivots.data(), 
		  X.data(), A.cols() );
}

// Read in a Matrix Market file

#include "mtl/matrix_market_stream.h"

// main routine

int main() {

  // open a matrix_market_stream and place in a Blitz array
  char* fname = "e05r0500.mtx";
  mtl::matrix_market_stream<double> mms(fname);
  Array<double,2> MM(mms.nrows(),mms.ncols());
  mtl::entry2<double> e;
  while( !mms.eof() ) {
    mms >> e;
    int row = e.row;
    int col = e.col;
    MM(row,col) = e.value;
  }
  cout << "MM.size() = (" << MM.rows() << ", " << MM.cols() << ")" << endl;

  // make a copy of the Matrix

  Array<double,2> A(MM.shape());
  A = MM;

  // LAPACK LU factorization
  Array<int,1> pivots(A.rows());
  stopwatch cpu; cpu.start();
  if (LU_factor(A, pivots) != 0) {
    cout << "LU_factor() failed." << endl;
    exit(1);
  }
  cout << "Finished LU_factor() " << cpu.stop() << endl;
  
  // LAPACK LU solve
  Array<double,1> b(A.rows());
  cpu.reset();
  cpu.start();
  for (int n=0; n<1000; n++) {
    b = 2.0;
    LU_solve( A, pivots, b );
  }
  cout << "LU solve time :  " << cpu.stop() << endl;
  cout.flush();
  
  // Test the Mflops of Matrix-Matrix multiply

  const int ntimes = 40;  // number of times

  // Reset the original matrix

  A = MM;
  Array<double,2> B(A.shape()), C(A.shape());
  B = A;
  cpu.reset();
  cpu.start();
  for (int n=0; n<ntimes; n++)
    matmult( A, B, C );  // ATLAS matmult
  double walltime = cpu.stop() / (double)ntimes;
  double mflops = (double)A.rows()*(double)B.cols()*(2.0*(double)A.cols()-1.0)/
    (walltime * 1.0e+06);
  cout << "matmult time   = " << walltime << endl;
  cout << "matmult MFLOPS = " << mflops << endl;
  
  // Reset and try Blitz tensor notation

  A = MM;
  B = A; A.transpose(secondDim, firstDim);
  Array<double,2> C2(A.shape());
  firstIndex i;
  secondIndex j;
  thirdIndex k;  
  cpu.reset();
  cpu.start();
  C2 = sum( A(i,k) * B(k,j), k);
  cout << "Blitz tensor sum time: " << cpu.stop() << endl;

  cout << sum( C - C2 ) << endl;  // are the answers the same?
  
  int Nx = 10;
  Array<double,2> D(Nx,Nx), E(Nx,Nx), F(Nx,Nx);
  E = 1.0;
  D = 0.0;
  for (int i=0; i<Nx; i++)
    for (int j=0; j<Nx; j++) 
      D(j,i) = i + j * Nx + 1;
  //  cout << D << endl;
  cout << "Starting Matmult for N = " << Nx << endl;
  matmult( D, E, F );
  cout << "LAPACK Matmult complete\n";
  
  Array<double,1> X(10), Y(10);
  X = 1;
  Y = 2;
  daxpy( 2.0, X, Y );
  cout << "daxpy complete" << endl;
  
  return 0;
}


  
