/** \file GpGpu.hpp
    \brief Gpu utilities like those in Utils.hpp
    \author K. Noel Belcourt
    \author Pedro Bello-Maldonado

    This provides BLAS and LAPACK interfaces for GpGpu
*/

#ifndef DGM_GPGPU_HPP
#define DGM_GPGPU_HPP

#include <cstddef>

namespace DGM {
namespace GpGpu {

#ifdef DGM_USE_KOKKOS
  struct initialize_gpu {
    initialize_gpu();
    ~initialize_gpu();
  };
#endif

  // forward declare
  struct hex_kernels_impl;

  struct hex_kernels {
    // std opaque pointer technique to avoid
    // compiling all of DGM with nvcc
    hex_kernels_impl* impl;

    hex_kernels();
    ~hex_kernels();

    // set number of elemnent and p order
    void initialize(std::size_t ne, std::size_t nmodes, std::size_t qa
      , std::size_t qb, std::size_t qc);

    // set weighted Jacobian
    template <typename Iter>
    void wJ(Iter wJ_ptr);

    // set Basis vector B
    template <typename Iter>
    void Basis(Iter Ba_ptr, Iter Bb_ptr, Iter Bc_ptr);

    // set U field, compute inner product, return result
    template <typename Iter>
    void inner_product(Iter u_ptr);

     // Backward Transform
     void backward_transform(double* u_ptr);

    // Computes the number of blocks (i.e. grid size) of size 'num_threads'
    // needed to/ cover all the values in 'num_elements'.
    int size_grid(int num_elements, int num_threads);
  };

  // return the dot product with optional stride
  template<typename Scalar, typename Stride>
  Scalar dot(const std::size_t n, const Scalar* x, const Scalar* y,
    Stride nx, Stride ny);

  } // namespace GpGpu
} // namespace DGM

#endif  // DGM_GPGPU_HPP
