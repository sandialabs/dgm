#ifndef CMC_MMIO_HPP
#define CMC_MMIO_HPP

/** \file MMio.hpp
    \brief Reads a Matrix Market file using the MTL interface.
    \author S. Scott Collis

    This enables the CMC Matrix class to use MTL to initialize a matrix
    from a Matrix-Market file.

    Since this currently requires MTL, this is off by default and can be
    activated by defining CMC_USE_MMIO during build.
*/

// CMC includes
#include "Matrix.hpp"

#ifdef CMC_USE_MMIO

// MTL includes
#include "mtl/matrix_market_stream.hpp"

namespace CMC {

/// Construct a matrix from a Matrix Market File
template<typename T>
Matrix<T>::Matrix<T>(char *fname) {
  // Note that you need to cast away the constant here
  mtl::matrix_market_stream<T> mms( fname );
  d1 = mms.nrows();
  d2 = mms.ncols();
  v = new T[d1*d2];
  num_refs = new int;
  *num_refs = 1;
  initialize(mms);
  p_row = 0;
  set_pointers();
}

/// Initialize from a Matrix Market Stream
template<typename T>
void Matrix<T>::initialize(mtl::matrix_market_stream<T> &mms) {
  register int i, j;
  mtl::entry2<double> e;
  while( !mms.eof() ) {
    mms >> e; i = e.row; j = e.col;
    (*this)(i,j) = e.value;
  }
}

} // namespace CMC

#endif

#endif
