#include "time.h"
#include <iostream>
#include <valarray>
#include <complex>
using namespace std;

//  This is a test of slice_arrays.  Note that you must use the const tag for
//  the slice_array references.

//  S. Scott Collis

//  8-15-2001

typedef double T;  // Make it easy to change the type

class Matrix {
  valarray<T>* v;
  size_t d1, d2;
public:
  Matrix(size_t, size_t);
  //  Matrix(const Matrix&);
  //  Matrix& operator=(const Matrix&);
  //  ~Matrix();

  size_t size() const {return d1*d2;};
  size_t dim1() const {return d1;};
  size_t dim2() const {return d2;};

  //  Slice_iter<T> row(size_t i);
  //  Cslice_iter<T> row(size_t i) const;

  //  T& operator() (size_t x, size_t y);
  //  T  operator() (size_t x, size_t y) const;
};

Matrix::Matrix(size_t x, size_t y) {
  d1 = x; d2 = y; v = new valarray<T>(x*y);
}

//  inline Slice_iter<T> Matrix::row(size_t i) {
//    return Slice_iter<T>(v.slice(i,d2,d1));
//  }

//  inline Cslice_iter<T> Matrix::row(size_t i) const {
//    return Cslice_iter<T>(v.slice(i,d2,d1));
//  }

//    T& Matrix::operator()(size_t x, size_t y) {
//      return v[slice(x,1,d1*y)];
//    }

void f(valarray<T> &d) {

  const slice_array<T>& v_even = d[slice(0,d.size()/2,2)];
  const slice_array<T>& v_odd  = d[slice(1,d.size()/2,2)];
  const slice_array<T>& v_col  = d[slice(0,10,1)];
  const slice_array<T>& v_row  = d[slice(0,50,10)];
  //  v_odd  += v_even;   // works on GCC 2.95.2, not on GCC 2.96, works on SGI
  v_even  = 1;    // doesn't work on GCC 2.95.2, works on SGI
  //  v_col   = 0; 
  //  v_row   = 10;
}

int main(int argc, char *argv[]) {

  double cpu = (double) clock();

  valarray<T> u(10*50); // put the value first, then size

  for (int i=0; i<u.size(); i++) u[i]=i;
  f(u);
  for (int i=0; i<u.size(); i++)
    cout << "i = " << i << ", u[i] = " << u[i] << endl;

  cpu = ((double)clock() - cpu)/(double)CLOCKS_PER_SEC;
  cout << "Total execution time:  " << cpu << endl;
  
  return 0;
}

