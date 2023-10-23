/** \file matmult.cu
    \brief Cuda kernel for arbitrary (non-square) 
           matrix multiplication.  This implementation
           is single precision (double).
    \author K. Noel Belcourt

    Compile this file with: 
      nvcc -arch sm_35 -I /home/kbelco/local/boost/include matmult.cu 
      -L /home/kbelco/local/boost/lib -l boost_system -l boost_chrono
**/

#include <algorithm>
#include <cassert>
#include <iostream>
#include <iostream>
#include <vector>

#include <boost/chrono.hpp>
#include <boost/chrono/duration.hpp>
#include <boost/chrono/system_clocks.hpp>

using std::ceil;
using std::copy;
using std::cout;
using std::endl;
using std::ostream_iterator;
using std::vector;

using namespace boost::chrono;
using boost::chrono::steady_clock;
using boost::chrono::duration;
using boost::chrono::nanoseconds;
using boost::chrono::milliseconds;

const int TILE_DIM = 32;
const int BLOCK_ROWS = 8;

__global__ void vector_multiply(double *odata, const double *idata
  , const size_t length)
{
  int x = blockIdx.x * TILE_DIM + threadIdx.x;
  int y = blockIdx.y * TILE_DIM + threadIdx.y;
  int width = gridDim.x * TILE_DIM;
  for (int i=0; i<TILE_DIM; i+=BLOCK_ROWS) {
    size_t j = (y + i) * width + x;
    if (j < length) 
      odata[j] *= idata[j];
  }
}

__global__ void transpose(double *a, const double *b
  , const size_t n, const size_t m)
{
  // a[m,n] = b[n,m]
  __shared__ double tile[TILE_DIM][TILE_DIM+1];

  int bx = blockIdx.x;
  int by = blockIdx.y;
  int tx = threadIdx.x;
  int ty = threadIdx.y;
  int col = bx * TILE_DIM + tx;
  int row = by * TILE_DIM + ty;

  for (int j=0; j<TILE_DIM; j+=BLOCK_ROWS) {
    if (row < n && col < m) {
      size_t i = (row + j) * m + col;
      tile[ty+j][tx] = b[i];
    }
  }

  col = by * TILE_DIM + tx;
  row = bx * TILE_DIM + ty;
  __syncthreads();

  for (int j=0; j<TILE_DIM; j+=BLOCK_ROWS) {
    if (row < m && col < n) {
      size_t i = (row + j) * n + col;
      a[i] = tile[tx][ty+j];
    }
  }
}

__global__ void matmult(const double* a, const double* b, double* c
  , size_t width_c, size_t width_a, size_t height_c) 
{
  __shared__ double m[TILE_DIM][TILE_DIM];
  __shared__ double n[TILE_DIM][TILE_DIM];

  size_t bx = blockIdx.x;
  size_t by = blockIdx.y;
  size_t tx = threadIdx.x; 
  size_t ty = threadIdx.y;
  size_t row = by * TILE_DIM + ty;
  size_t col = bx * TILE_DIM + tx;

  double v = 0;
  size_t nb = width_a <= TILE_DIM ? 1 : ceil(double(width_a)/TILE_DIM);
  for (size_t i=0; i<nb; ++i) {
    // zero entry in shared memory
    m[ty][tx] = 0;
    n[ty][tx] = 0;
    if (row < height_c && tx < width_a) {
      // load shared memory from a 
      m[ty][tx] = a[row * width_a + i * TILE_DIM + tx];
    }
    if (i * TILE_DIM + ty < width_a) {
      // load shared memory from b
      n[ty][tx] = b[col + width_c * (i * TILE_DIM + ty)];
    }
    __syncthreads();
    for (int j=0; j<TILE_DIM; ++j) {
      v += m[ty][j] * n[j][tx];
    }
    __syncthreads();
  }
  // store c
  if (row < height_c && col < width_c) {
    c[row * width_c + col] = v;
  }
}

void vector_multiply() {
  // a[n] *= b[n]
  size_t n = 17293154;
  size_t m = ceil(sqrt(n));
  // compute block size
  size_t bs = m <= TILE_DIM ? 1 : ceil(double(m)/TILE_DIM);
  // treat linear vectors as 2d arrays
  cout << "a[" << n << "] *= b[" << n << "]" << endl;
  double* dev_a = 0, *dev_b = 0;
  vector<double> a(n, -2), b(n, -3);

  size_t s = sizeof(double);
  cudaError_t err = cudaMalloc(&dev_a, s*n);
  assert(err == cudaSuccess);
  cudaDeviceSynchronize();
  err = cudaMalloc(&dev_b, s*n);
  assert(err == cudaSuccess);
  cudaDeviceSynchronize();
  err = cudaMemcpy(dev_a, &a[0], s*n, cudaMemcpyHostToDevice);
  assert(err == cudaSuccess);
  cudaDeviceSynchronize();
  err = cudaMemcpy(dev_b, &b[0], s*n, cudaMemcpyHostToDevice);
  assert(err == cudaSuccess);
  cudaDeviceSynchronize();

  // 2d blocking for matrices
  dim3 blocks_per_grid(bs, bs);
  dim3 threads_per_block(TILE_DIM, BLOCK_ROWS);

  // very simple sanity check that arrays are big enough
  assert(n <= threads_per_block.x * 4 * threads_per_block.y *
    blocks_per_grid.x * blocks_per_grid.y);

  // time launch and wait for completion before ending timing
  steady_clock::time_point start = steady_clock::now();
  vector_multiply<<<blocks_per_grid, threads_per_block>>>(dev_a, dev_b, n);
  cudaDeviceSynchronize();
  steady_clock::time_point end = steady_clock::now();
  nanoseconds elapsed = end - start;

  // results
  cout << "Vector Multiply Elapsed: " << elapsed.count() << " ns" << endl;
  cout << "  BandWidth: " << s*2*n/elapsed.count() << " GB/s" << endl;
  cout << "  Floating Point Performance: " << n/elapsed.count() << " GFlop/s" << endl;

  // pull data back from device
  err = cudaMemcpy(&a[0], dev_a, s*n, cudaMemcpyDeviceToHost);
  assert(err == cudaSuccess);
  cudaDeviceSynchronize();

  // same answer at beginning, end and middle
#if 1
  for (size_t i=0; i<n; ++i) {
    if (6 != a[i]) {
      cout << i << " " << a[i] << endl;
    }
  }
#else
  cout << "result a: ";
  cout << "front = " << a[0] << " middle = " << a[a.size()/2] << " back = " << a.back() << endl;
  copy(a.begin(), a.end(), ostream_iterator<double>(cout, " "));
  cout << endl;
#endif
}

void matrix_transpose() {
  // matrix dimensions
  // a[m,n] = b[n,m]
  size_t n = 1724;
  size_t m = n-2;
  cout << "a[" << m << "," << n << "] = b[" << n << "," << m << "]" << endl;
  // compute block size in x (# columns in c) and y (# rows in c)
  int bs_n = n <= TILE_DIM ? 1 : ceil(double(n)/TILE_DIM);
  int bs_m = m <= TILE_DIM ? 1 : ceil(double(m)/TILE_DIM);
  double* dev_a = 0, *dev_b = 0;
  vector<double> a(m*n, -2), b(n*m, -3);
  for (int i=0; i<m*n; ++i) b[i] = i;

  size_t s = sizeof(double);
  cudaError_t err = cudaMalloc(&dev_a, s*m*n);
  assert(err == cudaSuccess);
  cudaDeviceSynchronize();
  err = cudaMalloc(&dev_b, s*n*m);
  assert(err == cudaSuccess);
  cudaDeviceSynchronize();
  err = cudaMemcpy(dev_a, &a[0], s*m*n, cudaMemcpyHostToDevice);
  assert(err == cudaSuccess);
  cudaDeviceSynchronize();
  err = cudaMemcpy(dev_b, &b[0], s*n*m, cudaMemcpyHostToDevice);
  assert(err == cudaSuccess);
  cudaDeviceSynchronize();

  // 2d blocking for matrices
  dim3 blocks_per_grid(bs_m, bs_n);
  dim3 threads_per_block(TILE_DIM, BLOCK_ROWS);

  // very simple sanity check that arrays are big enough
  assert(n <= threads_per_block.x * threads_per_block.y *
    blocks_per_grid.x * blocks_per_grid.y);

  // time launch and wait for completion before ending timing
  steady_clock::time_point start = steady_clock::now();
  transpose<<<blocks_per_grid, threads_per_block>>>(dev_a, dev_b, n, m);
  cudaDeviceSynchronize();
  steady_clock::time_point end = steady_clock::now();
  nanoseconds elapsed = end - start;

  // results
  cout << "Matrix Transpose Elapsed: " << elapsed.count() << " ns" << endl;
  cout << "  BandWidth: " << s*2*n*m/elapsed.count() << " GB/s" << endl;

  // pull data back from device
  err = cudaMemcpy(&a[0], dev_a, s*n*m, cudaMemcpyDeviceToHost);
  assert(err == cudaSuccess);
  cudaDeviceSynchronize();

  // check results
#if 1
  // a[m,n] = b[n,m]
  for (size_t i=0,k=0; i<n; ++i) {
    for (size_t j=0; j<m; ++j, ++k) {
      if (k != a[j*n+i]) {
        cout << " index: " << k << " != " << a[j*n+i] << endl;
      }
    }
  }
#else
  cout << "result a:\n";
  vector<double>::iterator it = a.begin();
  for (size_t i=0; i<m; ++i, it+=n) {
    copy(it, it+n, ostream_iterator<double>(cout, " "));
    cout << endl;
  }
#endif
}

// 260 Gflops if large enough matrices
//   e.g. NxN matrices with N = 9^3 on Curie.
// This implementation supports arbitrary matrix dimensions.
// Round up matrix sizes as necessary so there's no if tests in kernel.
void matrix_multiply() {
  // matrix dimensions
  // c[n,r] = a[n,m] * b[m,r]
  size_t n = 729;
  size_t m = 727;
  size_t r = 731;
  cout << "c[" << n << "," << r << "] = a[" << n << "," << m 
    << "] * b[" << m << "," << r << "]" << endl;
  // compute block size in x (# columns in c) and y (# rows in c)
  size_t bs_r = r <= TILE_DIM ? 1 : ceil(double(r)/TILE_DIM);
  size_t bs_n = n <= TILE_DIM ? 1 : ceil(double(n)/TILE_DIM);
  size_t bs_m = m <= TILE_DIM ? 1 : ceil(double(m)/TILE_DIM);
#if 0
  // handle non-square matrices
  int dn = bs_n * TILE_DIM;
  int dr = bs_r * TILE_DIM;
  int dm = bs_m * TILE_DIM;
#endif
  // number of flops
  size_t n3 = n*r*m;
  double* dev_a = 0, *dev_b = 0, *dev_c = 0;
  vector<double> a(n * m, -1), b(m * r, -2), c(n * r, -5);

#if 0
  a[0] = 1;
  a[1] = 2;
  a[2] = 3;
  a[3] = 4;
  a[4] = 5;
  a[5] = 6;
  a[6] = 7;
  a[7] = 8;
  a[8] = 9;
  a[9] = 10;
  a[10] = 11;
  a[11] = 12;
  a[12] = 2;
  a[13] = 3;
  a[14] = 4;
  a[15] = 4;
  a[16] = 3;
  a[17] = 2;
 
  b[0] = 1;
  b[1] = 2;
  b[2] = 3;
  b[3] = 4;
  b[4] = 5;
  b[5] = 6;
#endif

  size_t s = sizeof(double);
  cudaError_t err = cudaMalloc(&dev_a, n*m*s);
  assert(err == cudaSuccess);
  cudaDeviceSynchronize();
  err = cudaMalloc(&dev_b, m*r*s);
  assert(err == cudaSuccess);
  cudaDeviceSynchronize();
  err = cudaMalloc(&dev_c, n*r*s);
  assert(err == cudaSuccess);
  cudaDeviceSynchronize();
  err = cudaMemcpy(dev_a, &a[0], n*m*s, cudaMemcpyHostToDevice);
  assert(err == cudaSuccess);
  cudaDeviceSynchronize();
  err = cudaMemcpy(dev_b, &b[0], m*r*s, cudaMemcpyHostToDevice);
  assert(err == cudaSuccess);
  cudaDeviceSynchronize();
  err = cudaMemcpy(dev_c, &c[0], n*r*s, cudaMemcpyHostToDevice);
  assert(err == cudaSuccess);
  cudaDeviceSynchronize();

  // 2d blocking for matrices
  dim3 threads_per_block(TILE_DIM, TILE_DIM);
  dim3 blocks_per_grid(bs_r, bs_n);

  // very simple sanity check that arrays are big enough
  assert(n <= threads_per_block.x * threads_per_block.y *
    blocks_per_grid.x * blocks_per_grid.y);

  // time launch and wait for completion before ending timing
  steady_clock::time_point start = steady_clock::now();
  matmult<<<blocks_per_grid, threads_per_block>>>(dev_a, dev_b, dev_c, r, m, n);
  cudaDeviceSynchronize();
  steady_clock::time_point end = steady_clock::now();
  nanoseconds elapsed = end - start;

  // results
  cout << "Matrix Multiply Elapsed: " << elapsed.count() << " ns" << endl;
  cout << "  BandWidth: " << s*(n*r+n*m+m*r)/elapsed.count() << " GB/s" << endl;
  cout << "  Floating Point Performance: " << 2*n3/elapsed.count() << " GFlop/s" << endl;

  // pull data back from device
  err = cudaMemcpy(&c[0], dev_c, n*r*sizeof(double), cudaMemcpyDeviceToHost);
  assert(err == cudaSuccess);
  cudaDeviceSynchronize();

  // same answer at beginning, end and middle
#if 1
  for (size_t i=0; i<n*r; ++i) {
    if (2*m != c[i]) {
      cout << i << " ";
    }
  }
#else
  cout << "result c: ";
  copy(c.begin(), c.end(), ostream_iterator<double>(cout, " "));
  cout << endl;
#endif
}

int main(int, char **) {
  matrix_transpose();
  cout << endl;
  vector_multiply();
  cout << endl;
  matrix_multiply();
  cout << endl;
  return 0;
}
