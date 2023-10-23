#include <iostream>
#include <string>

// TNT

#include <tnt/tnt.h>
#include <tnt/stopwatch.h>
using TNT::stopwatch;

// Using MTL++

#include "mtl/matrix.h"
#include "mtl/mtl.h"
#include "mtl/utils.h"
#include "mtl/lu.h"
#include "mtl/linalg_vec.h"
#include "mtl/mtl2lapack.h"
#include "mtl/matrix_market_stream.h"

using namespace mtl;
using std::cout;
using std::endl;

typedef matrix< double, rectangle<>, dense<mtl::internal>, 
                column_major >::type Matrix;
typedef external_vec<int> iVector;
typedef external_vec<double> Vector;

// MTL to Atlas interface

extern "C" {
#include "cblas.h"
// need my own interface to clapack
int clapack_dgetrf(const enum CBLAS_ORDER Order, const int M, const int N,
                   double *A, const int lda, int *ipiv);
void clapack_dgetrs (const enum CBLAS_ORDER Order, 
		     const enum CBLAS_TRANSPOSE Trans,
		     const int N, const int NRHS, const double *A, 
		     const int lda, const int *ipiv, double *B, const int ldb);
}
inline int LU_factor( Matrix &A, iVector &pivots ) {
  cout << "In LU_factor" << endl;
  return clapack_dgetrf( CblasColMajor, A.nrows(), A.ncols(), A.data(), 
			 A.ncols(), pivots.data() );
}
inline void LU_solve( Matrix &A, iVector &pivots, Vector &X ) {
  const int NRHS = 1;
  clapack_dgetrs( CblasColMajor, CblasNoTrans, A.nrows(), NRHS, 
		  A.data(), A.ncols(), pivots.data(), 
		  X.data(), A.ncols() );
}

int main() {

  // open a matrix_market_stream and place in a Blitz array
  char* fname = "e05r0500.mtx";
  matrix_market_stream<double> mms(fname);
  Matrix A(mms);                  // read in a matrix market file

  Matrix B(A.nrows(),A.ncols());  // Make a copy of A
  mtl::copy(A, B);

  // The MTL LU factorization

  iVector pivots(new int[A.nrows()],A.nrows());
  stopwatch cpu; 
#if 1
  cpu.start();
  if ( lu_factor(A,pivots) != 0 ) {
      cout << "mtl::lu_factor() failed." << endl;
      exit(1);
  }
  cout << "MTL LU factor time :  " << cpu.stop() << endl;
  //  print_all_matrix(A);
#endif

  // Call the LAPACK factorization (this only works with column_major storage

#if 0
  using namespace mtl2lapack;
  lapack_matrix<double,internal>::type LA_B(B); // Make LA_pack handle to B
  cpu.reset();
  cpu.start();
  if ( getrf( LA_B, pivots ) != 0 ) {
      cout << "mtl2lapack::getrf() failed." << endl;
      exit(1);
  }
  cout << "LAPACK LU factor time :  " << cpu.stop() << endl;
#else
  // Call Atlas version of LU factorization
  cpu.reset();
  cpu.start();
  if (LU_factor(B, pivots) != 0) {
    cout << "LU_factor() failed." << endl;
    exit(1);
  }
  cout << "ATLAS LAPACK LU factor time :  " << cpu.stop() << endl;
#endif
  //  print_all_matrix( LA_B );

  mtl::add( scaled(A,-1), B );
  cout << "Infinity norm = " << mtl::infinity_norm(B) << endl;

  // dot product

  double *dx, *dy;
  dx = new double[10];
  dy = new double[10];
  for (int j=0; j<10; j++)
    dx[j] = dy[j] = 1.0;
  Vector x(dx,10), y(dy,10);
  dense1D<double> z(10);

  mtl::set( z, 0.0);
  mtl::add( scaled(x,5), z );
  print_vector( z );
  cout << "dot(x,z) = " << dot(x,z) << endl;

  double alpha = 2.0;
  mtl::set( x, alpha );
  mtl::add( scaled(x,2.0), y );
  print_vector( x );
  print_vector( y );
  
  cout << "dot(x,y) = " << dot(x,y) << endl;
  
  return 0;
}

