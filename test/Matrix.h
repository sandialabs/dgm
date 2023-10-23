#ifndef MATRIX_H
#define MATRIX_H

#include<iostream>
#include<string>
#include<valarray>
#include<algorithm>
using namespace std;

#include "mtl/matrix_market_stream.h"

//----------------------------------------------------------------------------
//
//  Slice Iterator
//
//----------------------------------------------------------------------------

template<class T> class Slice_iter {
  valarray<T>* v;
  slice s;
  size_t curr;    // index of current element  
  T& ref(size_t i) const { return (*v)[s.start()+i*s.stride()]; }
public:
  Slice_iter(valarray<T>* vv, slice ss) :v(vv), s(ss), curr(0) { }
  
  Slice_iter end() const {
    Slice_iter t = *this;
    t.curr = s.size();  // index of last-plus-one element
    return t;
  }

  size_t size() const { return s.size(); }
  size_t start() const { return s.start(); }
  size_t stride() const { return s.stride(); }
  T* data() const { return &(ref(0)); };
  
  Slice_iter& operator++() { curr++; return *this; }
  Slice_iter operator++(int) { Slice_iter t = *this; curr++; return t; }
  
  T& operator[](size_t i) { return ref(i); }         // C style subscript
  T& operator()(size_t i) { return ref(i); }         // Fortran-style subscript
  T& operator*() { return ref(curr); }               // current element
  
  Slice_iter& operator=(const T&);

  friend bool operator==<>(const Slice_iter& p, const Slice_iter& q);
  friend bool operator!=<>(const Slice_iter& p, const Slice_iter& q);
  friend bool operator< <>(const Slice_iter& p, const Slice_iter& q);
};

template<class T>
inline bool operator==(const Slice_iter<T>& p, const Slice_iter<T>& q) {
  return p.curr==q.curr
    && p.s.stride()==q.s.stride()
    && p.s.start()==q.s.start();
}

template<class T>
inline bool operator!=(const Slice_iter<T>& p, const Slice_iter<T>& q) {
  return !(p==q);
}

template<class T>
inline bool operator<(const Slice_iter<T>& p, const Slice_iter<T>& q) {
  return p.curr<q.curr
    && p.s.stride()==q.s.stride()
    && p.s.start()==q.s.start();
}

template<class T>
inline Slice_iter<T>& Slice_iter<T>::operator=(const T &s) {
  for (Slice_iter<T> si=*this; si!=this->end(); si++) {
    *si = s;
  }
  return *this;
}

template<class T>
ostream& operator<<(ostream& os, Slice_iter<T> &m)
{
  for(int x=0; x<m.size(); x++) {
    os << '\t' << m[x];
    os << "\n";
  }
  return os;
}

//----------------------------------------------------------------------------
//
//  Constant Slice Iterator
//
//----------------------------------------------------------------------------

template<class T> class Cslice_iter 
{
  valarray<T>* v;
  slice s;
  size_t curr; // index of current element
  const T& ref(size_t i) const { return (*v)[s.start()+i*s.stride()]; }
public:
  Cslice_iter(valarray<T>* vv, slice ss): v(vv), s(ss), curr(0){}
  Cslice_iter end() const {
    Cslice_iter t = *this;
    t.curr = s.size();  // index of one plus last element
    return t;
  }

  Cslice_iter& operator++() { curr++; return *this; }
  Cslice_iter operator++(int) { Cslice_iter t = *this; curr++; return t; }
  
  const T& operator[](size_t i) const { return ref(i); }
  const T& operator()(size_t i) const { return ref(i); }
  const T& operator*() const { return ref(curr); }
  
  friend bool operator==<>(const Cslice_iter& p, const Cslice_iter& q);
  friend bool operator!=<>(const Cslice_iter& p, const Cslice_iter& q);
  friend bool operator< <>(const Cslice_iter& p, const Cslice_iter& q);
};

template<class T>
inline bool operator==(const Cslice_iter<T>& p, const Cslice_iter<T>& q) {
  return p.curr==q.curr
    && p.s.stride()==q.s.stride()
    && p.s.start()==q.s.start();
}

template<class T>
inline bool operator!=(const Cslice_iter<T>& p, const Cslice_iter<T>& q) {
  return !(p==q);
}

template<class T>
inline bool operator<(const Cslice_iter<T>& p, const Cslice_iter<T>& q) {
  return p.curr<q.curr
    && p.s.stride()==q.s.stride()
    && p.s.start()==q.s.start();
}

// Forward declaration

template<class T> class Vector;

//------------------------------------------------------------------------
//
// Template Matrix class
//
//------------------------------------------------------------------------

template<class T> 
class Matrix {
  valarray<T>* v;    // stores elements by in Row Major format (like C)
  size_t d1, d2;     // d1 == number of rows, d2 == number of columns
  size_t *num_refs;
public:
  Matrix();
  Matrix(size_t x, size_t y);
  Matrix(const Matrix&);
  Matrix(valarray<T> *, size_t, size_t);
  Matrix(string &);
  
  void initialize( mtl::matrix_market_stream<T> & );

  Matrix<T>& operator=(const Matrix&);
  ~Matrix();
  
  void resize(size_t x, size_t y);
  void resize(const Matrix&);

  void alias(Matrix&);
  void alias(valarray<T> &, size_t, size_t);
  void alias(Vector<T> &, size_t, size_t);

  size_t size() const { return d1*d2; }
  size_t dim1() const { return d1; }
  size_t rows() const { return d1; }
  size_t dim2() const { return d2; }
  size_t cols() const {return d2; }
  size_t nrefs() const { return *num_refs; }

  T* data() const { return &(*v)[0]; };
  
  Slice_iter<T> row(size_t i);
  Cslice_iter<T> row(size_t i) const;
  
  Slice_iter<T> column(size_t i);
  Cslice_iter<T> column(size_t i) const;
  
  double& operator()(size_t x, size_t y);      // Fortran-style subscripts
  double operator()(size_t x, size_t y) const;
  
  Slice_iter<T> operator()(size_t i) { return row(i); }
  Cslice_iter<T> operator()(size_t i) const { return row(i); }
  
  Slice_iter<T> operator[](size_t i) { return row(i); }   // C-style subscript
  Cslice_iter<T> operator[](size_t i) const { return row(i); }
  
  Matrix<T>& operator*=(const double);
  Matrix<T>& operator=(const T);
  
  valarray<T>& array() { return *v; }
  valarray<T>* parray() { return v; }
};

// Member functions

template<class T>
inline Slice_iter<T> Matrix<T>::row(size_t i)
{
  return Slice_iter<T>(v,slice(i*d2,d2,1));
}

template<class T>
inline Cslice_iter<T> Matrix<T>::row(size_t i) const
{
  return Cslice_iter<T>(v,slice(i*d2,d2,1));
}

template<class T>
inline Slice_iter<T> Matrix<T>::column(size_t i)
{
  return Slice_iter<T>(v,slice(i,d1,d2));
}

template<class T>
inline Cslice_iter<T> Matrix<T>::column(size_t i) const
{
  return Cslice_iter<T>(v,slice(i,d1,d2));
}

template<class T>
Matrix<T>::Matrix<T>()
{
  d1 = d2 = 0;
  v = 0;
  num_refs = new size_t;
  *num_refs = 1;
}

template<class T>
Matrix<T>::Matrix<T>(size_t x, size_t y)
{
  d1 = x;    // should check that x and y are sensible
  d2 = y;
  v = new valarray<T>(x*y);
  num_refs = new size_t;
  *num_refs = 1;
}

// construct a matrix from a Matrix Market File
template<class T>
Matrix<T>::Matrix<T>(string &fname)
{
  // Note that you need to cast away the constant here
  mtl::matrix_market_stream<T> mms( const_cast<char*>(fname.c_str()) );
  d1 = mms.nrows();
  d2 = mms.ncols();
  v = new valarray<T>(d1*d2);
  num_refs = new size_t;
  *num_refs = 1;
  initialize( mms );
}

// initialize from a Matrix Market Stream
template<class T>
void Matrix<T>::initialize(mtl::matrix_market_stream<T> &mms) {
  register int i, j;
  mtl::entry2<double> e;
  while( !mms.eof() ) {
    mms >> e; i = e.row; j = e.col;
    (*this)(i,j) = e.value;
  }
}

// option 1:  copy constructor makes a new valarray
#if 0
template<class T>
Matrix<T>::Matrix<T>(const Matrix<T> &M)
{
  d1 = M.dim1();
  d2 = M.dim2();
  v = new valarray<T>(d1*d2);
  (*v) = (*M.v);
  num_refs = new size_t;
  *num_refs = 1;
}
#else
// option 2: copy constructor makes a reference to the current matrix
template<class T>
Matrix<T>::Matrix<T>(const Matrix<T> &M)
{
  d1 = M.dim1();
  d2 = M.dim2();
  v = M.v;
  num_refs = M.num_refs;
  (*num_refs)++;
}
#endif

// Construct a matrix that is a reference to a valarray, since this is a
// reference, we set num_refs = 2 so that it is impossible to destroy the
// input valarray.  It is the users responsibility to allocate and destroy the
// valarray.
template<class T>
Matrix<T>::Matrix<T>(valarray<T> *m, size_t x, size_t y) 
{
  if (m == 0) {
    cerr << "Matrix::Matrix: attempted construction from a NULL valarray*" 
	 << endl;
    exit(1);
  }
  if (m->size() < x*y) {
    cerr << "Matrix::Matrix: valarray* too small" << endl;
    exit(1);
  }
  d1 = x;
  d2 = y;
  v = m;
  *num_refs = 2;
}

template<class T>
Matrix<T>::~Matrix<T>()
{
  if (*num_refs==1)
    delete v;
  else
    (*num_refs)--;
}

template<class T>
void Matrix<T>::resize(size_t x, size_t y)
{
  d1 = x;
  d2 = y;
  if (v!=0) {
    if (*num_refs==1) {
      delete v;
    } else {
      (*num_refs)--;
      num_refs = new size_t;
    }
  }
  v = new valarray<T>(d1*d2);
  *num_refs = 1;
}

template<class T>
void Matrix<T>::resize(const Matrix<T> &m)
{
  resize(m.dim1(), m.dim2());
}

template<class T>
void Matrix<T>::alias(Matrix<T> &m)
{
  d1 = m.dim1();
  d2 = m.dim2();

  if (v!=0) {
    if (*num_refs==1) {
      delete v;
    } else {
      (*num_refs)--;
    }
  }
  v = m.v;
  num_refs = m.num_refs;
  (*num_refs)++;
}

template<class T>
void Matrix<T>::alias(valarray<T> &m, size_t x, size_t y)
{
  if (&m == 0) {
    cerr << "Matrix<T>::Matrix<T>: attempted construction from a NULL valarray"
	 << endl;
    exit(1);
  }
  if (m.size() < x*y) {
    cerr << "Matrix<T>::Matrix<T>: valarray too small" << endl;
    exit(1);
  }
  d1 = x;
  d2 = y;
  if (v!=0) {
    if (*num_refs==1) {
      delete v;
    } else {
      (*num_refs)--;
      num_refs = new size_t;
    }
  }    
  v = &m;
  *num_refs = 2;
}

template<class T>
void Matrix<T>::alias(Vector<T> &m, size_t x, size_t y)
{
  if (m.v == 0) {
    cerr << "Matrix<T>::Matrix<T>: attempted construction from a NULL Vector"
	 << endl;
    exit(1);
  }
  if (m.size() < x*y) {
    cerr << "Matrix<T>::Matrix<T>: Vector too small" << endl;
    exit(1);
  }
  d1 = x;
  d2 = y;
  if (v!=0) {
    if (*num_refs==1) {
      delete v;
    } else {
      (*num_refs)--;
    }
  }
  v = m.v;
  num_refs = m.num_refs;
  (*num_refs)++;
}

template<class T>
inline double& Matrix<T>::operator()(size_t x, size_t y)
{
  return row(x)[y];
}

template<class T>
inline Matrix<T>& Matrix<T>::operator*=(const double d)
{
  (*v) *= d;
  return *this;
}

template<class T>
inline Matrix<T>& Matrix<T>::operator=(const T d)
{
  (*v) = d;
  return *this;
}

template<class T>
inline Matrix<T>& Matrix<T>::operator=(const Matrix<T> &m)
{
  // check to make sure that dimensions match
  //    for(int x=0; x<m.dim1(); x++)
  //      for(int y=0; y<m.dim2(); y++)
  //        (*this)[x][y] = m[x][y];
  *(this->v) = *(m.v);
  return *this;
}

template<class T>
ostream& operator<<(ostream& os, Matrix<T> &m)
{
  for(int x=0; x<m.dim1(); x++) {
    for(int y=0; y<m.dim2(); y++)
      os<<m[x][y]<<"\t";
    os << "\n";
  }
  return os;
}

//------------------------------------------------------------------------
//
// Template Vector class
//
//------------------------------------------------------------------------

template<class T> 
class Vector {
  valarray<T>* v;    // stores elements in a valarray
  size_t d;          // d == number of elements
  size_t *num_refs;  // number of references to representation
public:
  Vector();
  Vector(size_t x);
  Vector(const Vector<T>&);
  Vector(valarray<T> *, size_t);
  Vector<T>& operator=(const Vector<T>&);
  ~Vector();
  
  void resize(size_t x);
  void resize(const Vector<T>&);

  void alias(Vector<T>&);
  void alias(valarray<T> &, size_t);

  size_t size() const { return d; }
  size_t nrefs() const { return *num_refs; }

  T* data() const { return &(*v)[0]; };
  
  double& operator()(size_t x);      // Fortran-style subscripts
  double operator()(size_t x) const;
  
  double& operator[](size_t x);      // Fortran-style subscripts
  double operator[](size_t x) const;

  Vector<T>& operator*=(const double);
  Vector<T>& operator=(const T);
  
  valarray<T>& array() { return *v; }
  valarray<T>* parray() { return v; }

  friend void Matrix<T>::alias(Vector<T> &, size_t, size_t);
};

// Member functions

template<class T>
Vector<T>::Vector<T>()
{
  d = 0;
  v = 0;
  num_refs = new size_t;
  *num_refs = 1;
}

template<class T>
Vector<T>::Vector<T>(size_t x)
{
  d = x;
  v = new valarray<T>(x);
  num_refs = new size_t;
  *num_refs = 1;
}

// copy constructor makes a reference to the current matrix
template<class T>
Vector<T>::Vector<T>(const Vector<T> &M)
{
  d = M.size();
  v = M.v;
  num_refs = M.num_refs;
  (*num_refs)++;
}

// Construct a matrix that is a reference to a valarray, since this is a
// reference, we set num_refs = 2 so that it is impossible to destroy the
// input valarray.  It is the users responsibility to allocate and destroy the
// valarray.
template<class T>
Vector<T>::Vector<T>(valarray<T> *m, size_t x) 
{
  if (m == 0) {
    cerr << "Vector::Vector: attempted construction from a NULL valarray*" 
	 << endl;
    exit(1);
  }
  if (m->size() < x) {
    cerr << "Vector::Vector: valarray* too small" << endl;
    exit(1);
  }
  d = x;
  v = m;
  *num_refs = 2;
}

template<class T>
Vector<T>::~Vector<T>()
{
  if (*num_refs==1)
    delete v;
  else
    (*num_refs)--;
}

template<class T>
void Vector<T>::resize(size_t x)
{
  d = x;
  if (v!=0) {
    if (*num_refs==1) {
      delete v;
    } else {
      (*num_refs)--;
      num_refs = new size_t;
    }
  }
  v = new valarray<T>(d);
  *num_refs = 1;
}

template<class T>
void Vector<T>::resize(const Vector<T> &m)
{
  resize(m.size());
}

template<class T>
void Vector<T>::alias(Vector<T> &m)
{
  d = m.size();

  if (v!=0) {
    if (*num_refs==1) {
      delete v;
    } else {
      (*num_refs)--;
    }
  }
  v = m.v;
  num_refs = m.num_refs;
  (*num_refs)++;
}

template<class T>
void Vector<T>::alias(valarray<T> &m, size_t x)
{
  if (&m == 0) {
    cerr << "Vector<T>::Vector<T>: attempted construction from a NULL valarray"
	 << endl;
    exit(1);
  }
  if (m.size() < x) {
    cerr << "Vector<T>::Vector<T>: valarray too small" << endl;
    exit(1);
  }
  d = x;
  if (v!=0) {
    if (*num_refs==1) {
      delete v;
    } else {
      (*num_refs)--;
      num_refs = new size_t;
    }
  }    
  v = &m;
  *num_refs = 2;
}

template<class T>
inline double& Vector<T>::operator()(size_t x)
{
  return (*v)[x];
}

template<class T>
inline double& Vector<T>::operator[](size_t x)
{
  return (*v)[x];
}

template<class T>
inline Vector<T>& Vector<T>::operator*=(const double d)
{
  (*v) *= d;
  return *this;
}

template<class T>
inline Vector<T>& Vector<T>::operator=(const T d)
{
  (*v) = d;
  return *this;
}

template<class T>
inline Vector<T>& Vector<T>::operator=(const Vector<T> &m)
{
  *(this->v) = *(m.v);
  return *this;
}

template<class T>
ostream& operator<<(ostream& os, Vector<T> &m)
{
  for(int x=0; x<m.size(); x++) {
    os << '\t' << m[x];
    os << "\n";
  }
  return os;
}

template<class T>
ostream& operator<<(ostream& os, const valarray<T>& v)
{
  for (int i = 0; i<v.size(); ++i){
    os << '\t' << v[i];
    os << "\n";
  }
  return os;
}

//------------------------------------------------------------------------
//
// Interface to CBLAS and CLAPACK (ATLAS)
//
//------------------------------------------------------------------------

// CBLAS AND CLAPACK interface from Atlas 

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

// Interface to Atlas

typedef Matrix<double> dmatrix;
typedef Vector<double> dvector;
typedef Slice_iter<double> sdvector;
typedef Vector<int>    ivector;

// x = a x
 
inline void dscal( const double alpha, dvector &X ) {
  const int stride = 1;
  cblas_dscal( X.size(), alpha, X.data(), stride );
}

inline void dscal( const double alpha, sdvector &X ) {
  cblas_dscal( X.size(), alpha, X.data(), X.stride() );
}

// y = x + y

inline void dvadd( dvector &X, dvector &Y ) {
  cblas_daxpy( X.size(), 1.0, X.data(), 1, Y.data(), 1 );
}

inline void dvadd( sdvector &X, sdvector &Y ) {
  cblas_daxpy( X.size(), 1.0, X.data(), X.stride(), Y.data(), Y.stride() );
}

inline void dvadd( dvector &X, sdvector &Y ) {
  cblas_daxpy( X.size(), 1.0, X.data(), 1, Y.data(), Y.stride() );
}

inline void dvadd( sdvector &X, dvector &Y ) {
  cblas_daxpy( X.size(), 1.0, X.data(), X.stride(), Y.data(), 1 );
}

// y = a x + y

inline void daxpy( const double alpha, dvector &X, dvector &Y) {
  const int stride = 1;
  cblas_daxpy( X.size(), alpha, X.data(), stride, Y.data(), stride );
}

inline void daxpy( const double alpha, sdvector &X, sdvector &Y) {
  cblas_daxpy( X.size(), alpha, X.data(), X.stride(), Y.data(), Y.stride() );
}

// y = alpha A x + beta y

inline void dgemv(const double alpha, dmatrix &A, dvector &X, 
		  const double beta, dvector &Y) {
  cblas_dgemv( CblasRowMajor, CblasNoTrans, 
	       A.rows(), A.cols(), alpha, A.data(), A.cols(), 
	       X.data(), 1, beta, Y.data(), 1 );
}

inline void dgemv(const double alpha, dmatrix &A, sdvector &X, 
		  const double beta, dvector &Y) {
  cblas_dgemv( CblasRowMajor, CblasNoTrans, 
	       A.rows(), A.cols(), alpha, A.data(), A.cols(), 
	       X.data(), X.stride(), beta, Y.data(), 1 );
}

inline void dgemv(const double alpha, dmatrix &A, dvector &X, 
		  const double beta, sdvector &Y) {
  cblas_dgemv( CblasRowMajor, CblasNoTrans, 
	       A.rows(), A.cols(), alpha, A.data(), A.cols(), 
	       X.data(), 1, beta, Y.data(), Y.stride() );
}

inline void dgemv(const double alpha, dmatrix &A, sdvector &X, 
		  const double beta, sdvector &Y) {
  cblas_dgemv( CblasRowMajor, CblasNoTrans, 
	       A.rows(), A.cols(), alpha, A.data(), A.cols(), 
	       X.data(), X.stride(), beta, Y.data(), Y.stride() );
}

// y = A x

inline void mvmult(dmatrix &A, dvector &X, dvector &Y) {
  cblas_dgemv( CblasRowMajor, CblasNoTrans, 
	       A.rows(), A.cols(), 1.0, A.data(), A.cols(), 
	       X.data(), 1, 0.0, Y.data(), 1 );
}

inline void mvmult(dmatrix &A, sdvector &X, dvector &Y) {
  cblas_dgemv( CblasRowMajor, CblasNoTrans, 
	       A.rows(), A.cols(), 1.0, A.data(), A.cols(), 
	       X.data(), X.stride(), 0.0, Y.data(), 1 );
}

inline void mvmult(dmatrix &A, dvector &X, sdvector &Y) {
  cblas_dgemv( CblasRowMajor, CblasNoTrans, 
	       A.rows(), A.cols(), 1.0, A.data(), A.cols(), 
	       X.data(), 1, 0.0, Y.data(), Y.stride() );
}

inline void mvmult(dmatrix &A, sdvector &X, sdvector &Y) {
  cblas_dgemv( CblasRowMajor, CblasNoTrans, 
	       A.rows(), A.cols(), 1.0, A.data(), A.cols(), 
	       X.data(), X.stride(), 0.0, Y.data(), Y.stride() );
}

// C = A B

inline void matmult(dmatrix &A, dmatrix &B, dmatrix &C) {
  double alpha = 1.0;
  double beta = 0.0;
  cblas_dgemm( CblasRowMajor, CblasNoTrans, CblasNoTrans, 
	       A.rows(), B.cols(), A.cols(), alpha,
	       A.data(), A.cols(), B.data(), B.cols(), beta, 
	       C.data(), C.cols() );
}

inline void gmatmult(const double alpha, dmatrix &A, dmatrix &B, 
		     const double beta, dmatrix &C) {
  cblas_dgemm( CblasRowMajor, CblasNoTrans, CblasNoTrans, 
	       A.rows(), B.cols(), A.cols(), alpha,
	       A.data(), A.cols(), B.data(), B.cols(), beta, 
	       C.data(), C.cols() );
}

inline int LU_factor( dmatrix &A, ivector &A_pivots ) {
  A_pivots.resize( min(A.rows(),A.cols()) );
  return clapack_dgetrf( CblasRowMajor, A.rows(), A.cols(), A.data(), 
			 A.cols(), A_pivots.data() );
}

inline void LU_solve( dmatrix &A, ivector &A_pivots, dvector &X ) {
  const int NRHS = 1;
  clapack_dgetrs( CblasRowMajor, CblasNoTrans, A.rows(), NRHS, 
		  A.data(), A.cols(), A_pivots.data(), 
		  X.data(), A.cols() );
}

#endif
