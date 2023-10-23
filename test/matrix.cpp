#include "Matrix.h"

// test my Matrix class

// Use TNT stopwatch

#include <tnt/tnt.h>
#include <tnt/stopwatch.h>
using TNT::stopwatch;

int main()
{
  dmatrix A(5,6);
  cout << A.dim1() << " " << A.dim2() << endl;
  for (int i=0; i<A.dim1(); i++)
    for (int j=0; j<A.dim2(); j++)
      A(i,j) = i + j;

  cout << "Matrix A = " << endl << A << endl;
  {
    dmatrix B(A);  // make a reference to A
    B = 2;
    cout << A.nrefs() << endl;
    cout << "Matrix B = " << endl << B << endl;
  }
  cout << A.nrefs() << endl;
  cout << "Matrix A = " << endl << A << endl;

#if 0
  //  Another way of making a reference to A is to use a Slice_iter
  {
    sdvector row( A.parray(), slice(0,A.dim2(),1) );
    sdvector col( A.parray(), slice(0,A.dim1(),A.dim2()) );
    for (sdvector si=col; si!=col.end(); si++) *si = 1.0;
    cout << "A = " << endl << A << endl;
  }
#endif

  A.row(0) = 1.0;
  A.column(2) = 3.0;
  cout << "A = " << endl << A << endl;
  A = 1.0;
  cout << "A = " << endl << A << endl;
  sdvector r1 = A.row(0);
  sdvector r2 = A.row(1);
  daxpy( 2.0, r1, r2 );
  cout << "A(daxpy) = " << endl << A << endl;

  dmatrix C;
  C.resize(A);  // Make C the same size as A
  C = A;        // this does a copy (they had better be the same size)
  cout << "C = " << endl << C << endl;

  C.alias(A);   // Make C an alias of A
  cout << "A.nrefs() = " << A.nrefs() << endl;
  A = 9.0;
  C = 5;
  cout << "C = " << endl << C << endl; 

  //  valarray<double> va(10);
  Vector<double> va(10);
  va = 2.5;
  C.alias(va,5,2);
  cout << "A.nrefs() = " << A.nrefs() << endl;
  cout << "C = " << endl << C << endl;

  C.resize(5,5);
  C = 3.5;
  cout << "C = " << endl << C << endl;
  cout << "va = " << endl << va << endl;

  Vector<double> x(4), y(4);
  x = 1.0;
  y = 2.0;
  daxpy( 2.0, x, y );
  cout << "y = 1.0 * x + y " << endl << y << endl;

  dmatrix M(4,4), N(4,4), O(4,4);
  M = 1.0;
  N = 2.0;
  matmult( M, N, O );
  cout << "O = " << endl << O << endl;

  gmatmult( 2.0, M, N, 0.0, O );
  cout << "O = " << endl << O << endl;

  {
    string fname = "e05r0500.mtx";
    dmatrix MM(fname);
    dmatrix A(MM.rows(),MM.cols());
    A = MM;
    
    // LAPACK LU factorization
    ivector pivots(A.rows());
    stopwatch cpu; cpu.start();
    if (LU_factor(A, pivots) != 0) {
      cout << "LU_factor() failed." << endl;
      exit(1);
    }
    cout << "Finished LU_factor() " << cpu.stop() << endl;
    
    // LAPACK LU solve
    dvector b(A.rows());
    cpu.reset();
    cpu.start();
    for (int n=0; n<1000; n++) {
      b = 2.0;
      LU_solve( A, pivots, b );
    }
    cout << "LU solve time :  " << cpu.stop() << endl;
    cout.flush(); 
  }

  {
    dvector x(10), y(10);
    x = y = 1.0;
    dvadd( x, y );
    cout << "x = " << endl << x << endl;
    cout << "y = " << endl << y << endl;

    sdvector x2( x.parray(), slice(0,x.size()/2,2) );
    dscal( 2.0, x2 );  // scale the even elements by two
    cout << "x = " << endl << x << endl;
  }


  // test matrix vector multiply

  {
    dvector x(10), y(10);
    dmatrix A(10,10);
    A = 1.0;
    x = 1.0;
    sdvector sx( x.parray(), slice(0,x.size(), 1) );
    mvmult( A, sx, y );
    cout << "y = A x " << endl << y << endl;
  }

  
}
