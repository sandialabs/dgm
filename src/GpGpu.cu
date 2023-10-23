/** \file GpGpu.hpp
    \brief Gpu utilities like those in Utils.hpp
    \author K. Noel Belcourt
    \author Pedro Bello-Maldonado

    This provides BLAS and LAPACK interfaces for GpGpu
*/

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <iterator>
#include <ostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "GpGpu.hpp"

#include <boost/lexical_cast.hpp>
#include <boost/numeric/conversion/cast.hpp>

using std::ceil;
using std::copy;
using std::cout;
using std::endl;
using std::distance;
using std::ostream_iterator;
using std::size_t;
using std::string;
using std::swap;
using std::runtime_error;
using std::vector;

using boost::lexical_cast;
using boost::numeric_cast;

const int TILE_DIM = 32;  // TILE_DIM^2 is number of threads in block

#ifdef DGM_USE_CUDA
namespace DGM {

namespace GpGpu {

  const int BLOCK_ROWS = 8;

  // inplace vector multiply
  __global__ void vec_mult(double* a, const double* b,
    const int length)
  {
    a += blockIdx.z * length;
    for (int j=0; j<TILE_DIM; j+=BLOCK_ROWS) {
      int index = ((blockIdx.y * TILE_DIM + threadIdx.y) + j) *
                  (gridDim.x * TILE_DIM)
        + (blockIdx.x * TILE_DIM + threadIdx.x);
      if (index < length) a[index] *= b[index];
    }
  }

  // Theoretical bandwidth on K20X (c.f. http://www.nvidia.com/content/
  // tesla/pdf/nvidia-tesla-kepler-family-datasheet.pdf). Note that
  // this is not my algorithm, though I did modify it to handle
  // rectangular matrices.  Mark Harris of Nvidia seems to be the author
  // of the square transpose implementaiton (c.f. http://devblogs.nvidia.com/
  // parallelforall/efficient-matrix-transpose-cuda-cc/
  __global__ void transpose(double *a, const double *b,
    const int n, const int m)
  {
    __shared__ double tile[TILE_DIM][TILE_DIM+1];

    // a[m,n] = b[n,m]
    int bx = blockIdx.x;
    int by = blockIdx.y;
    int tx = threadIdx.x;
    int ty = threadIdx.y;
    int col = bx * TILE_DIM + tx;
    int row = by * TILE_DIM + ty;

    for (int j = 0; j < TILE_DIM; j += BLOCK_ROWS) {
      // load b into column in the cache
      if (row < n && col < m) {
        int i = (row + j) * m + col;
        tile[ty + j][tx] = b[i];
      }
    }

    // transpose block offsets
    col = by * TILE_DIM + tx;
    row = bx * TILE_DIM + ty;
    __syncthreads();

    for (int j = 0; j < TILE_DIM; j += BLOCK_ROWS) {
      // store a from a row in the cache
      if (row < m && col < n) {
        int i = (row + j) * n + col;
        a[i] = tile[tx][ty + j];
      }
    }
  }

  // compute c[height_c, width_c] = a[height_c, width_a] * b[width_a, width_c]
  __device__ void device_matmult(const double *a, const double *b, double *c,
    const int width_c, const int width_a, const int height_c)
  {
    __shared__ double m[TILE_DIM][TILE_DIM];
    __shared__ double n[TILE_DIM][TILE_DIM];

    int bx = blockIdx.x;
    int by = blockIdx.y;
    int tx = threadIdx.x;
    int ty = threadIdx.y;
    int row = by * TILE_DIM + ty;
    int col = bx * TILE_DIM + tx;

    double v = 0;
    int nb = width_a <= TILE_DIM ? 1 : ceil(double(width_a)/TILE_DIM);
    for (int i=0; i<nb; ++i) {
      // zero shared memory
      m[ty][tx] = 0;
      n[ty][tx] = 0;
      // skip load of a if outside matrix size
      if (row < height_c && tx < width_a) {
        m[ty][tx] = a[row * width_a + i * TILE_DIM + tx];
      }
      // skip load of b if outside matrix size
      if (i * TILE_DIM + ty < width_a) {
        n[ty][tx] = b[col + (i * TILE_DIM + ty) * width_c];
      }
      __syncthreads();
      for (int j=0; j<TILE_DIM; ++j) {
        v += m[ty][j] * n[j][tx];
      }
      __syncthreads();
    }
    if (row < height_c && col < width_c) {
      c[row * width_c + col] = v;
    }
  }

  // compute c[height_c, width_c] = a[height_c, width_a] * b[width_a, width_c]
  __global__ void matmult_load_a_once(double *a, double *b, double *c,
    const int width_c, const int width_a, const int height_c,
    const int inc)
  {
    b += blockIdx.z * inc;
    c += blockIdx.z * inc;
    device_matmult(a, b, c, width_c, width_a, height_c);
  }

  // compute c[height_c, width_c] = a[height_c, width_a] * b[width_a, width_c]
  __global__ void matmult_load_b_once(double *a, double *b, double *c,
    const int width_c, const int width_a, const int height_c,
    const int a_inc, const int c_inc)
  {
    a += blockIdx.z * a_inc;
    c += blockIdx.z * c_inc;
    device_matmult(a, b, c, width_c, width_a, height_c);
  }

  // and calls the real matmult for each submatrix
  // compute c[nm, qb * qc] = a[nm, qb] * b[qa, qb * qc]
  __global__ void submatrix_matmult(double *a, double *b,
    double *c, const int q, const int nm,
    const int b_inc, const int c_inc)
  {
    // each element and submatrix runs in its own block
    b += (blockIdx.z / nm) * b_inc + (blockIdx.z % nm) * q * q;
    c += (blockIdx.z / nm) * c_inc + (blockIdx.z % nm) * nm * q;
    // submatrix sizes of Ha[nm, qc] = Bb[nm, qb] * H[qb, qc]
    device_matmult(a, b, c, q, q, nm);
  }

struct hex_kernels_impl {
  double *wJ;        // weighted Jacobian
  double *B, *BT;  // basis
  double *u;
  double *Ha;  // temporary

  int ne;  // number of elements
  int nm;  // number of modes
  int q, inc;
  int bs_nm, bs_nm2, bs_qbqc, bs_qa, bs_qb, bs_qc;

  hex_kernels_impl() : wJ(0), B(0), BT(0),
    u(0), Ha(0), ne(0), nm(0), q(0), inc(0),
    bs_nm(0), bs_nm2(0), bs_qbqc(0), bs_qa(0), bs_qb(0), bs_qc(0)
  {}

  ~hex_kernels_impl() {
    cudaFree(Ha);
    cudaFree(u);
    cudaFree(BT);
    cudaFree(B);
    cudaFree(wJ);
    cudaDeviceSynchronize();
    Ha = 0;
    u = 0;
    BT = 0;
    B = 0;
    wJ = 0;
  }

  void transpose_B() {
    // setup for transpose: BcT[qc, nm] = Bc[nm, qc];
    // fix to use tiled implementation
    dim3 blocks_per_grid(bs_qc, bs_nm);
    dim3 threads_per_block(TILE_DIM, BLOCK_ROWS);
    transpose<<<blocks_per_grid, threads_per_block>>>(BT, B, nm, q);
    cudaDeviceSynchronize();
  }

  // copy from device to host and write to cout
  void output_results(double* it, double* end, string field_name)
  {
    // although the iterators are pointers into gpu memory,
    // distance doesn't dereference them so safe to use on
    // memory that's not locally accessable.
    int s = sizeof(double);
    int d = distance(it, end);
    // cpu memory to hold result
    vector<double> v(d);
    // copy field from device to host memory
    cudaError_t err = cudaMemcpy(&v[0], it, s * d, cudaMemcpyDeviceToHost);
    if (err != cudaSuccess)
      throw runtime_error("Error in hex_kernels::u"
        " cudaMemcpy failed to copy into device memory for u.");
    cudaDeviceSynchronize();
    // output array
    cout << "host " << field_name << ": ";
    copy(v.begin(), v.end(), ostream_iterator<double>(cout, " "));
    cout << endl;
  }

  // should eventually look like Hex::inner_product
  void inner_product() {
    // launch dimensions (z dimension is number of elements)
    dim3 blocks_per_grid(bs_qbqc, bs_qa, ne);
    dim3 threads_per_block(TILE_DIM, BLOCK_ROWS);

    // u *= wJ
    vec_mult<<<blocks_per_grid, threads_per_block>>>(u, wJ, inc);
    cudaDeviceSynchronize();

    // u[nm, qb*qc] = B[nm, qa] * u[qa, qb*qc]
    blocks_per_grid = dim3(bs_qbqc, bs_nm, ne);
    threads_per_block = dim3(TILE_DIM, TILE_DIM);
    matmult_load_a_once<<<blocks_per_grid, threads_per_block>>>(
      B, u, u, q*q, q, nm, inc);

    // compute Ha[nm, qb * qc] = B[nm, qb] * u[qa, qb * qc]
    blocks_per_grid = dim3(bs_qc, bs_nm, ne*nm);
    submatrix_matmult<<<blocks_per_grid, threads_per_block>>>(B, u,
      Ha, q, nm, inc, inc);
    cudaDeviceSynchronize();

    // u[nm2, nm] = Ha[nm2, qc] * BT[qc, nm]
    int nm2 = nm * nm;
    blocks_per_grid = dim3(bs_nm, bs_nm2, ne);
    matmult_load_b_once<<<blocks_per_grid, threads_per_block>>>(
      Ha, BT, u, nm, q, nm2, inc, nm * nm2);
    cudaDeviceSynchronize();
  }
};

hex_kernels::hex_kernels() : impl(0)
{
  impl = new hex_kernels_impl;
}

hex_kernels::~hex_kernels() {
  cudaDeviceReset();
  delete impl;
  impl = 0;
}

void hex_kernels::initialize(size_t ne, size_t nmodes, size_t qa
  , size_t qb, size_t qc)
{
  impl->ne = ne;
  impl->q = qa;
  impl->nm = nmodes;
  // size of one element in double precision words used by
  // cuda to increment pointers for threads and blocks
  int inc = impl->inc = qa * qb * qc;
  // int td2 = TILE_DIM * TILE_DIM;
  // overallocate for each element to avoid memory bank conflicts
  // impl->inc = inc = ceil(double(inc)/td2) * td2;
  // compute block sizes, ensure always at least one
  int bs_nm = impl->bs_nm = nmodes <= TILE_DIM ? 1 : ceil(double(nmodes)/TILE_DIM);
  impl->bs_nm2 = nmodes*nmodes <= TILE_DIM ? 1 : ceil(double(nmodes*nmodes)/TILE_DIM);
  int bs_qbqc = impl->bs_qbqc = qa*qa <= TILE_DIM ? 1 : ceil(double(qa*qa)/TILE_DIM);
  int bs_qa = impl->bs_qa = qa <= TILE_DIM ? 1 : ceil(double(qa)/TILE_DIM);
  int bs_qb = impl->bs_qb = qb <= TILE_DIM ? 1 : ceil(double(qb)/TILE_DIM);
  int bs_qc = impl->bs_qc = qc <= TILE_DIM ? 1 : ceil(double(qc)/TILE_DIM);
  // allocate cuda memory for u[qa, qb*qc]
  int s = sizeof(double);
  int count = ne * s * inc;
  cudaError_t err = cudaMalloc(&impl->u, count);
  if (err != cudaSuccess)
    throw runtime_error("Error in hex_kernels::init"
      " unable to allocate device memory for U err = " +
      lexical_cast<string>(err) + ".");
  // allocate temporary Ha
  err = cudaMalloc(&impl->Ha, count);
  if (err != cudaSuccess)
    throw runtime_error("Error in hex_kernels::init"
      " unable to allocate device memory for Ha.");
  // allocate weighted Jacobian wJ[qa*qb*qc]
  count = s * inc;
  err = cudaMalloc(&impl->wJ, count);
  if (err != cudaSuccess)
    throw runtime_error("Error in hex_kernels::init"
      " unable to allocate device memory for wJ.");
  // B[nm,qa]
  count = s * nmodes * qa;
  err = cudaMalloc(&impl->B, count);
  if (err != cudaSuccess)
    throw runtime_error("Error in hex_kernels::init"
      " unable to allocate device memory for B.");
  // Bc transpose [qc,nm]
  err = cudaMalloc(&impl->BT, count);
  if (err != cudaSuccess)
    throw runtime_error("Error in hex_kernels::init"
      " unable to allocate device memory for BT.");
  // wait for allocation kernels to finishs
  cudaDeviceSynchronize();
}

// set weighted Jacobian
template <>
void hex_kernels::wJ<double*>(double* it, double* end) {
  int s = sizeof(double);
  // length of memory for one element
  int d = distance(it, end);
  // simple check that the sizes match
  int inc = impl->inc;
  assert(d == inc);
  // copy wJ into Cuda memory as 2d array [qa, qb*qc]
  cudaError_t err = cudaMemcpy(impl->wJ, it, s*inc, cudaMemcpyHostToDevice);
  if (err != cudaSuccess)
    throw runtime_error("Error in hex_kernels::wJ"
      " cudaMemcpy failed to copy into device memory for wJ.");
  cudaDeviceSynchronize();
}

// set Basis vector
template <>
void hex_kernels::Basis<double*>(double* ba_it, double* bb_it
  , double* bc_it)
{
  int s = sizeof(double);
  int nm = impl->nm;
  int q = impl->q;
  // copy in basis memory B[nm,qa]
  cudaError_t err = cudaMemcpy(impl->B, ba_it, s * nm * q, cudaMemcpyHostToDevice);
  if (err != cudaSuccess)
    throw runtime_error("Error in hex_kernels::Basis"
      " cudaMemcpy failed to copy into device memory for B, err = " +
      lexical_cast<string>(err) + ".");
  cudaDeviceSynchronize();
  // use Cuda to transpose B into BT
  impl->transpose_B();
}

template <>
void hex_kernels::inner_product<double*>(double* it, double* ht) {
  // set U field
  int s = sizeof(double);
  // data in one element
  int inc = impl->inc;
  int ne = impl->ne;
  // copy in field data u[qa, qb*qc] from host to device
  if (cudaSuccess != cudaMemcpy(impl->u, it, s * ne * inc,
    cudaMemcpyHostToDevice))
  {
    throw runtime_error("Error in hex_kernels::u"
      " cudaMemcpy failed to copy into device memory for u.");
  }
  cudaDeviceSynchronize();
  // invoke gpu kernels
  impl->inner_product();
  // copy out field data from device to host
  int nm = impl->nm;
  int nm3 = nm * nm * nm;
  // device to host copy
  for (int i=0; i<ne; ++i) {
    double *u_it = ht + i * inc;
    if (cudaSuccess != cudaMemcpy(u_it, impl->u + i * nm3, s * nm3,
      cudaMemcpyDeviceToHost))
    {
      throw runtime_error("Error in hex_kernels::u"
        " cudaMemcpy failed to copy into host from device memory for u.");
    }
  }
  // wait for all memcpy kernels to finish
  cudaDeviceSynchronize();
}

template<>
double dot<double,int>(const size_t n, const double* x, const double* y,
  int nx, int ny)
{
  cout<<"CUDA dot product not implemented"<<endl;
  return 0;
}

template<>
float dot<float,int>(const size_t n, const float* x, const float* y,
  int nx, int ny)
{
  cout<<"CUDA dot product not implemented"<<endl;
  return 0;
}

} // namespace GpGpu
} // namespace DGM

#endif  // defined DGM_USE_CUDA

// Kokkos specific code
#ifdef DGM_USE_KOKKOS

#define KOKKOS_HAVE_CUDA
#include "Kokkos_Core.hpp"
#include "Kokkos_DualView.hpp"
#include "Cuda/Kokkos_Cuda_Parallel.hpp"

using Kokkos::Cuda;
using Kokkos::DualView;
using Kokkos::LayoutLeft;
using Kokkos::LayoutRight;
using Kokkos::RangePolicy;
using Kokkos::TeamPolicy;
using Kokkos::TeamThreadRange;
using Kokkos::ThreadVectorRange;
using Kokkos::View;

using Kokkos::finalize;
using Kokkos::initialize;
using Kokkos::fence;
using Kokkos::parallel_for;

namespace {
  // track number of times Kokkos is initialized
  static int instances = 0;

  // execution space
  typedef Cuda Space;

  // layout
  typedef LayoutLeft Layout;

  // views
  typedef View<double****, Layout, Space> ArrayView4D;
  typedef View<double***, Layout, Space> ArrayView3D;
  typedef View<double**, Layout, Space> ArrayView2D;
  typedef DualView<double****, Layout, Space> ArrayDualView4D;
  typedef DualView<double***, Layout, Space> ArrayDualView3D;
  typedef DualView<double**, Layout, Space> ArrayDualView2D;

  // policy
  typedef TeamPolicy<Space> TeamPolicyExec;
  typedef TeamPolicy<Space>::member_type MemberTypeExec;
}

namespace DGM {
namespace GpGpu {

  struct hex_kernels_impl {
    // u[num_elem, quad_a, quad_b, quad_c]
    ArrayView4D u_dev;
    ArrayView4D::HostMirror u_hst;
    ArrayDualView4D u;

    // H[num_elem, num_modes, quad_b, quad_c]
    ArrayView4D H_dev;
    ArrayView4D::HostMirror H_hst;
    ArrayDualView4D H;

    // Ha[num_elem, num_modes, num_modes, quad_c]
    ArrayView4D Ha_dev;
    ArrayView4D::HostMirror Ha_hst;
    ArrayDualView4D Ha;

    // wJ[quad_a, quad_b, quad_c]
    ArrayView3D wJ_dev;
    ArrayView3D::HostMirror wJ_hst;
    ArrayDualView3D wJ;

    // Ba[num_elem, quad_a], Bb[num_elem, quad_b], Bc[num_elem, quad_c]
    ArrayView2D Ba_dev, Bb_dev, Bc_dev;
    ArrayView2D::HostMirror Ba_hst, Bb_hst, Bc_hst;
    ArrayDualView2D Ba, Bb, Bc;

    int num_elem;
    int num_modes;
    int quad_a, quad_b, quad_c;
    int length;

    hex_kernels_impl() : num_elem(0), num_modes(0), quad_a(0)
      , quad_b(0), quad_c(0), length(0) {
    }

    void inner_product() {
      int num_elem = this->num_elem;
      int num_modes = this->num_modes;
      int quad_a = this->quad_a;
      int quad_b = this->quad_b;
      int quad_c = this->quad_c;

      int num_threads = 128;

      // For each element in num_elem, compute
      // u[num_elem, quad_a, quad_b, quad_c] *= wJ[quad_a, quad_b, quad_c]
      double* u_ptr = u_dev.data();
      double* wJ_ptr = wJ_dev.data();

      parallel_for(TeamPolicyExec(num_elem, num_threads), 
        [u_ptr, wJ_ptr, num_elem, quad_a, quad_b, quad_c] 
        __device__ (const MemberTypeExec& team_member)
      {
        const int n_e = team_member.league_rank();

        parallel_for(TeamThreadRange(team_member, quad_a * quad_b * quad_c), 
          [=] (const int idx)
        {
          u_ptr[n_e * (quad_a * quad_b * quad_c) + idx] *= wJ_ptr[idx];
        });
      });

      // For each element in num_elem, compute
      // H[num_elem, num_modes, quad_b * quad_c] = 
      // Ba[num_modes, quad_a] * u[num_elem, quad_a, quad_b * quad_c]
      int block_x = 16;
      int block_y = 16;
      double* H_ptr = H_dev.data();
      double* Ba_ptr = Ba_dev.data();

      parallel_for(TeamPolicyExec(num_elem, block_y, block_x), 
        [H_ptr, Ba_ptr, u_ptr, num_elem, num_modes, quad_a, quad_b, quad_c] 
        __device__ (const MemberTypeExec& team_member)
      {
        int n_e = team_member.league_rank();

        parallel_for(TeamThreadRange(team_member, num_modes), 
          [=] (const int i)
        {
          parallel_for(ThreadVectorRange(team_member, quad_b * quad_c), 
            [=] (const int j)
          {
            int n = num_modes;
            int m = quad_b * quad_c;
            int p = quad_a;
            double sum = 0.0;
            double* A = Ba_ptr;
            double* B = u_ptr + n_e * (p * m);
            double* C = H_ptr + n_e * (n * m);

            for (int k=0; k<p; ++k) {
              sum += A[i * p + k] * B[k * m + j];
            }
            C[i * m + j] = sum;
          });
        });
      });

      // For each element in num_elem, compute
      // Ha[num_elem, num_modes, num_modes, quad_c] = 
      // Bb[num_modes, quad_b] * H[num_elem, num_modes, quad_b, quad_c]
      double* Bb_ptr = Bb_dev.data();
      double* Ha_ptr = Ha_dev.data();

      parallel_for(TeamPolicyExec(num_elem, block_y, block_x), 
        [Ha_ptr, Bb_ptr, H_ptr, num_elem, num_modes, quad_b, quad_c] 
        __device__ (const MemberTypeExec& team_member)
      {
        int n_e = team_member.league_rank();

        parallel_for(TeamThreadRange(team_member, num_modes), 
          [=] (const int i)
        {
          parallel_for(ThreadVectorRange(team_member, quad_c), 
            [=] (const int j)
          {
            int n = num_modes;
            int m = quad_c;
            int p = quad_b;
            double sum = 0.0;
            double* A = Bb_ptr;

            for (int n_m = 0; n_m < num_modes; ++n_m) {
              double* B = H_ptr + n_e * (n * m * p) + n_m * (p * m);
              double* C = Ha_ptr + n_e * (n * n * m) + n_m * (n * m);

              sum = 0.0;
              for (int k=0; k<p; ++k) {
                sum += A[i * p + k] * B[k * m + j];
              }
              C[i * m + j] = sum;
            }
          });
        });
      });

      // For each element in num_elem, compute
      // u[num_elem, num_modes, num_modes, num_modes] = 
      // Ha[num_elem, num_modes, num_modes, quad_c] * Bc.T[quad_c, num_modes]
      double* Bc_ptr = Bc_dev.data();

      parallel_for(TeamPolicyExec(num_elem, block_y, block_x), 
        [u_ptr, Ha_ptr, Bc_ptr, num_elem, num_modes, quad_a, quad_b, quad_c] 
        __device__ (const MemberTypeExec& team_member)
      {
        int n_e = team_member.league_rank();

        parallel_for(TeamThreadRange(team_member, num_modes), 
          [=] (const int i)
        {
          parallel_for(ThreadVectorRange(team_member, num_modes), 
            [=] (const int j)
          {
            int n = num_modes;
            int m = num_modes;
            int p = quad_c;
            double sum = 0.0;
            double* B = Bc_ptr;

            for (int n_m = 0; n_m < num_modes; ++n_m) {
              double* A = Ha_ptr + n_e * (n * m * p) + n_m * (n * p);
              double* C = u_ptr + n_e * (quad_a * quad_b * quad_c) + n_m * (n * m);

              sum = 0.0;
              for (int k=0; k<p; ++k) {
                sum += A[i * p + k] * B[j * p + k];
              }
              C[i * m + j] = sum;
            }
          });
        });
      });
    }

    void backward_transform() {
      // HexBlock Data
      int num_elem = this->num_elem;
      int num_modes = this->num_modes;
      int quad_a = this->quad_a;
      int quad_b = this->quad_b;
      int quad_c = this->quad_c;

      // For each element in num_elem, compute
      // H[num_elem, quad_a, num_modes, num_modes] = 
      // Ba.T[quad_a, num_modes] * u[num_elem, num_modes, num_modes, num_modes]
      int block_x = 16;
      int block_y = 16;
      double* u_ptr = u_dev.data();
      double* H_ptr = H_dev.data();
      double* Ba_ptr = Ba_dev.data();

      parallel_for(TeamPolicyExec(num_elem, block_y, block_x), 
        [H_ptr, Ba_ptr, u_ptr, num_elem, num_modes, quad_a, quad_b, quad_c] 
        __device__ (const MemberTypeExec& team_member)
      {
        int elem = team_member.league_rank();

        parallel_for(TeamThreadRange(team_member, quad_a), 
          [=] (const int i)
        {
          parallel_for(ThreadVectorRange(team_member, num_modes * num_modes), 
            [=] (const int j)
          {
            int n = quad_a;
            int m = num_modes * num_modes;
            int p = num_modes;
            double sum = 0.0;
            double* A = Ba_ptr;
            double* B = u_ptr + elem * (quad_a * quad_b * quad_c);
            double* C = H_ptr + elem * (quad_a * num_modes * num_modes);

            for (int k=0; k<p; ++k) {
              sum += A[k * n + i] * B[k * m + j];
            }
            C[i * m + j] = sum;
          });
        });
      });

      // For each element in num_elem and for each quadrature point, compute
      // Ha[num_elem, quad_a, quad_b, num_modes] = 
      // Bb.T[quad_b, num_modes] * H[num_elem, quad_a, num_modes, num_modes]
      double* Bb_ptr = Bb_dev.data();
      double* Ha_ptr = Ha_dev.data();

      parallel_for(TeamPolicyExec(num_elem, block_y, block_x), 
        [Ha_ptr, Bb_ptr, H_ptr, num_elem, num_modes, quad_a, quad_b] 
        __device__ (const MemberTypeExec& team_member)
      {
        int elem = team_member.league_rank();

        parallel_for(TeamThreadRange(team_member, quad_b), 
          [=] (const int i)
        {
          parallel_for(ThreadVectorRange(team_member, num_modes), 
            [=] (const int j)
          {
            int n = quad_b;
            int m = num_modes;
            int p = num_modes;
            double sum = 0.0;
            double* A = Bb_ptr;

            for (int q_a = 0; q_a < quad_a; ++q_a) {
              double* B = H_ptr + elem * (quad_a * num_modes * num_modes) 
                        + q_a * (num_modes * num_modes);
              double* C = Ha_ptr + elem * (quad_a * quad_b * num_modes) 
                        + q_a * (quad_b * num_modes);

              sum = 0.0;
              for (int k=0; k<p; ++k) {
                sum += A[k * n + i] * B[k * m + j];
              }
              C[i * m + j] = sum;
            }
          });
        });
      });

      // For each element in num_elem, compute
      // u[num_elem, quad_a, quad_b, quad_c] = 
      // Ha[num_elem, quad_a, quad_b, num_modes] * Bc[num_modes, quad_c]
      double* Bc_ptr = Bc_dev.data();

      parallel_for(TeamPolicyExec(num_elem, block_y, block_x), 
        [u_ptr, Ha_ptr, Bc_ptr, num_elem, num_modes, quad_a, quad_b, quad_c] 
        __device__ (const MemberTypeExec& team_member)
      {
        int elem = team_member.league_rank();

        parallel_for(TeamThreadRange(team_member, quad_a * quad_b), 
          [=] (const int i)
        {
          parallel_for(ThreadVectorRange(team_member, quad_c), 
            [=] (const int j)
          {
            int n = quad_a * quad_b;
            int m = quad_c;
            int p = num_modes;
            double sum = 0.0;
            double* A = Ha_ptr + elem * (quad_a * quad_b * num_modes);
            double* B = Bc_ptr;
            double* C = u_ptr + elem * (quad_a * quad_b * quad_c);

            for (int k=0; k<p; ++k) {
              sum += A[i * p + k] * B[k * m + j];
            }
            C[i * m + j] = sum;
          });
        });
      });
    }
  };

  hex_kernels::hex_kernels() : impl(0) {
    impl = new hex_kernels_impl;
  }

  hex_kernels::~hex_kernels() {
    delete impl;
    impl = 0;
  }

  int hex_kernels::size_grid(int num_elements, int num_threads) {
    return (num_elements + (num_threads - 1)) / num_threads;
  }

  void hex_kernels::initialize(size_t num_elem, size_t num_modes
    , size_t quad_a, size_t quad_b, size_t quad_c)
  {
    impl->num_elem = num_elem;
    impl->num_modes = num_modes;
    impl->quad_a = quad_a;
    impl->quad_b = quad_b;
    impl->quad_c = quad_c;

    // Length must be a power of 2
    impl->length = 1;

    while ((impl->length < quad_c / 2) && (impl->length < TILE_DIM)) {
      impl->length *= 2;
    }
  }

  // Set weighted Jacobian
  template <>
  void hex_kernels::wJ(double* wJ_ptr) {
    int quad_a = impl->quad_a;
    int quad_b = impl->quad_b;
    int quad_c = impl->quad_c;

    impl->wJ_dev = ArrayView3D("wJ_dev", quad_a, quad_b, quad_c);
    impl->wJ_hst = ArrayView3D::HostMirror(wJ_ptr, quad_a, quad_b, quad_c);
    impl->wJ = ArrayDualView3D(impl->wJ_dev, impl->wJ_hst);

    impl->wJ.modify<ArrayDualView3D::host_mirror_space>();
    impl->wJ.sync<ArrayDualView3D::memory_space>();
  }

  template<>
  void hex_kernels::Basis(double* Ba_ptr, double* Bb_ptr, double* Bc_ptr) {
    int quad_a = impl->quad_a;
    int quad_b = impl->quad_b;
    int quad_c = impl->quad_c;
    int num_modes = impl->num_modes;

    impl->Ba_dev = ArrayView2D("Ba_dev", num_modes, quad_a);
    impl->Ba_hst = ArrayView2D::HostMirror(Ba_ptr, num_modes, quad_a);
    impl->Ba = ArrayDualView2D(impl->Ba_dev, impl->Ba_hst);

    impl->Bb_dev = ArrayView2D("Bb_dev", num_modes, quad_b);
    impl->Bb_hst = ArrayView2D::HostMirror(Bb_ptr, num_modes, quad_b);
    impl->Bb = ArrayDualView2D(impl->Bb_dev, impl->Bb_hst);

    impl->Bc_dev = ArrayView2D("Bc_dev", num_modes, quad_c);
    impl->Bc_hst = ArrayView2D::HostMirror(Bc_ptr, num_modes, quad_c);
    impl->Bc = ArrayDualView2D(impl->Bc_dev, impl->Bc_hst);

    impl->Ba.modify<ArrayDualView2D::host_mirror_space>();
    impl->Ba.sync<ArrayDualView2D::memory_space>();

    impl->Bb.modify<ArrayDualView2D::host_mirror_space>();
    impl->Bb.sync<ArrayDualView2D::memory_space>();

    impl->Bc.modify<ArrayDualView2D::host_mirror_space>();
    impl->Bc.sync<ArrayDualView2D::memory_space>();
  }

  template<>
  void hex_kernels::inner_product(double* u_ptr) {
    int quad_a = impl->quad_a;
    int quad_b = impl->quad_b;
    int quad_c = impl->quad_c;
    int num_elem = impl->num_elem;
    int num_modes = impl->num_modes;

    impl->u_dev = ArrayView4D("u_dev", num_elem, quad_a, quad_b, quad_c);
    impl->u_hst = ArrayView4D::HostMirror(u_ptr, num_elem, quad_a, quad_b, quad_c);
    impl->u = ArrayDualView4D(impl->u_dev, impl->u_hst);

    impl->H_dev = ArrayView4D("H_dev", num_elem, num_modes, quad_b, quad_c);
    impl->H_hst = ArrayView4D::HostMirror("H_hst", num_elem, num_modes, quad_b, quad_c);
    impl->H = ArrayDualView4D(impl->H_dev, impl->H_hst);

    impl->Ha_dev = ArrayView4D("Ha_dev", num_elem, num_modes, num_modes, quad_c);
    impl->Ha_hst = ArrayView4D::HostMirror("Ha_hst", num_elem, num_modes, num_modes, quad_c);
    impl->Ha = ArrayDualView4D(impl->Ha_dev, impl->Ha_hst);

    impl->u.modify<ArrayDualView4D::host_mirror_space>();
    impl->u.sync<ArrayDualView4D::memory_space>();

    impl->inner_product();

    impl->u.modify<ArrayDualView4D::memory_space>();
    impl->u.sync<ArrayDualView4D::host_mirror_space>();

    fence();
  }

  void hex_kernels::backward_transform(double* u_ptr) {
    // Variables
    int quad_a = impl->quad_a;
    int quad_b = impl->quad_b;
    int quad_c = impl->quad_c;
    int num_elem = impl->num_elem;
    int num_modes = impl->num_modes;

    // Instantiate views
    impl->u_dev = ArrayView4D("u_dev", num_elem, quad_a, quad_b, quad_c);
    impl->u_hst = ArrayView4D::HostMirror(u_ptr, num_elem, quad_a, quad_b, quad_c);
    impl->u = ArrayDualView4D(impl->u_dev, impl->u_hst);

    impl->H_dev = ArrayView4D("H_dev", num_elem, quad_a, num_modes, num_modes);
    impl->H_hst = ArrayView4D::HostMirror("H_hst", num_elem, quad_a, num_modes, num_modes);
    impl->H = ArrayDualView4D(impl->H_dev, impl->H_hst);

    impl->Ha_dev = ArrayView4D("Ha_dev", num_elem, quad_a, quad_b, num_modes);
    impl->Ha_hst = ArrayView4D::HostMirror("Ha_hst", num_elem, quad_a, quad_b, num_modes);
    impl->Ha = ArrayDualView4D(impl->Ha_dev, impl->Ha_hst);

    // Synchronize host and device
    impl->u.modify<ArrayDualView4D::host_mirror_space>();
    impl->u.sync<ArrayDualView4D::memory_space>();

    // Invoke kernels
    impl->backward_transform();

    // Synchronize host and device
    impl->u.modify<ArrayDualView4D::memory_space>();
    impl->u.sync<ArrayDualView4D::host_mirror_space>();
  }

  initialize_gpu::initialize_gpu() {
    if (0 == instances) {
      initialize();
    }
    ++instances;
  }

  initialize_gpu::~initialize_gpu() {
    if (0 == --instances) {
      finalize();
    }
  }

template <typename T, typename View>
struct dot_ {
  typedef T value_type;

  View x, y;
  dot_(View x_, View y_) : x(x_), y(y_) {}

  KOKKOS_INLINE_FUNCTION
  void operator()(int i, T& result) const {
    result += x(i) * y(i);
  }
};

template <typename View, typename T, typename S>
void strided_copy(View v, const int n, const T* x, S nx) {
  if (1 == nx) {
    copy(x, x+n, &v[0]);
  }
  else {
    for (S i=0; i<n; ++i)
      v[i] = x[i*nx];
  }
}

#if 0
// Host, View, Type, Scalar
template <typename H, typename V, typename T, typename S>
T dot_t(const int n, const T* x, const T* y, S nx, S ny) {
  view_t vx("x", n), vy("y", n);

  host_view_t hx = Kokkos::create_mirror_view(vx);
  strided_copy(hx, n, x, nx);
  Kokkos::deep_copy(vx, hx);

  host_view_t hy = Kokkos::create_mirror_view(vy);
  strided_copy(hy, n, y, ny);
  Kokkos::deep_copy(vy, hy);

  T result = 0;
  Kokkos::parallel_reduce(n, dot_<T, view_t>(vx, vy), result);
  return result;
}
#endif

#if 0
template <>
double dot<double, int>(const int n, const double* x, const double* y,
  int nx, int ny) {
#if 0
  if (n != fv[0].size()) {
    // x
    dv[0] = double_view_t("x", n);
    dhv[0] = Kokkos::create_mirror_view(dv[0]);
    // y
    dv[1] = double_view_t("y", n);
    dhv[1] = Kokkos::create_mirror_view(dv[1]);
  }
  // copy data to device
  strided_copy(dhv[0], n, x, nx);
  Kokkos::deep_copy(dv[0], dhv[0]);
  strided_copy(dhv[1], n, y, ny);
  Kokkos::deep_copy(dv[1], dhv[1]);
  // launch kernel
  double result = 0;
  Kokkos::parallel_reduce(n, dot_<double, double_view_t>(dv[0], dv[1]), result);
  return result;
#endif
  return 0;
}

template <>
float dot<float, int>(const int n, const float* x, const float* y,
  int nx, int ny) {
#if 0
  if (n != fv[0].size()) {
    // x
    fv[0] = float_view_t("x", n);
    fhv[0] = Kokkos::create_mirror_view(fv[0]);
    // y
    fv[1] = float_view_t("y", n);
    fhv[1] = Kokkos::create_mirror_view(fv[1]);
  }
  // copy data to device
  strided_copy(fhv[0], n, x, nx);
  Kokkos::deep_copy(fv[0], fhv[0]);
  strided_copy(fhv[1], n, y, ny);
  Kokkos::deep_copy(fv[1], fhv[1]);
  // launch kernel
  float result = 0;
  Kokkos::parallel_reduce(n, dot_<float, float_view_t>(fv[0], fv[1]), result);
  return result;
#endif
  return 0;
}
#endif

template<typename Size, typename Array, typename Stride>
Array dot(Size n, Array x, Array y, Size nx, Size ny)
{
    return Array();
}

}  // namespace GpGpu
}  // namespace DGM

#endif // defined DGM_USE_KOKKOS
