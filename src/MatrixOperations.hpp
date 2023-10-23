#ifndef DGM_MATRIX_OPERATIONS_HPP
#define DGM_MATRIX_OPERATIONS_HPP

/** \file MatrixOperations.hpp
    \brief Matrix Matrix and Matrix Vector operations
    \author N. Belcourt, S. Collis

    Uses sfinae to select near-optimal implementation at compile time
    Key point is that matrix operations enhance cancellation, unlike Atlas
*/

// clang++ -mavx -O3 -std=c++11 -I $DGM_TPL/atlas/include -I $DGM_DIST/src
//   -I $DGM_TPL/boost/include test_matrix_operations.cpp

#include <algorithm>
#include <type_traits>

#if defined(__AVX__) || defined(__AVX2__)
#include <immintrin.h>
#endif

using std::copy;
using std::enable_if;
using std::fill;
using std::iterator_traits;
using std::multiplies;
using std::transform;

namespace DGM {

  // cache line size (8 doubles)
  constexpr int cache_line_size = 8;
  // avx register size (4 doubles)
  constexpr int avx_size = 4;
  // broadcast 3 registers from A
  constexpr int nreg_a = 3;
  // load 4 registers from B
  constexpr int nreg_b = 4;
  
  // C[IxJ] = A[IxK] * B[KxJ]
  template <int I, int K, int J, typename Iterator, typename enable_if<
    // enable if all matrix dimension are an integral multiple
    // of the avx_size and at least as large as the cache_line_size
    0 == I % avx_size && 0 == K % avx_size && 0 == J % avx_size
    && cache_line_size <= I && cache_line_size <= K
    && cache_line_size <= J, int>::type = 0>
  void multiply(Iterator C, Iterator A, Iterator B)
  {
#if defined(__AVX__)
    int i2, j2, k2;
    Scalar *c_ = 0, *a_ = 0, *b_ = 0;
    Scalar zero = 0;
    for (int i=0; i<I; i+=avx_size) {
      // zero out next block
      fill(C+i*J, C+(i+avx_size)*J, zero);
      for (int j=0; j<J; j+=avx_size) {
        for (int k=0; k<K; k+=avx_size) {
          for (i2=0, c_=C+i*J+j, a_=A+i*K+k; i2<avx_size; ++i2, c_+=J, a_+=K) {
            // don't pollute l2 cache, load directly into l1 cache
            _mm_prefetch(a_+cache_line_size, _MM_HINT_NTA);
            // load c
            __m256d c = _mm256_load_pd(c_);
            for (k2=0, b_=B+k*J+j; k2<avx_size; ++k2, b_+=J) {
              // load single value into a and replicate into m256
              __m128d a_tmp = _mm_load1_pd(a_+k2);
              __m256d a = _mm256_broadcast_pd(&a_tmp);
              // load b
              __m256d b = _mm256_load_pd(b_);
              // multiply a * b, sum product, accumulate into c
              c = _mm256_add_pd(c, _mm256_mul_pd(a, b));
            }
            _mm256_store_pd(c_, c);
          }
        }
      }
    }
#else
		// haswell has 2 fma execution ports with 5 cycle latency
		// so need 10 fma's to keep pipeline full
#if 0
    alignas(64) Scalar cdot[nreg_a][nreg_b] = {{ 0 }};
    Scalar* s_it = csum;
    for (int k=0; k<n; ++k) {
    	// dot product
	    for (int j=0; j<nreg_b; ++j) {
	    	__m256d bdot = b(k,j);
  	  	for (int i=0; i<nreg_a; ++i) {
  	  		cdot[k][j] += a(k,i) * b(i,j);
  	  	}
  	  }
			// accumulate into c
			for (int j=0; j<nreg_a; ++j) {
				for (int k=0; k<nreg_b; ++k) {
					c += cdot[j][k];
				}
			}
		}
#else
    int i2, j2, k2;
    Scalar *c = 0, *a = 0, *b = 0;
    Scalar zero = 0;
    for (int i=0; i<I; i+=cache_line_size) {
      // zero out next block
      fill(C+i*J, C+(i+cache_line_size)*J, zero);
      for (int j=0; j<J; j+=cache_line_size) {
        for (int k=0; k<K; k+=cache_line_size) {
          // C[i*J,j]
          // A[i*K,k]
          for (i2=0, c=C+i*J+j, a=A+i*K+k; i2<cache_line_size; ++i2, c+=J, a+=K) {
            // B[k*J,j]
            for (k2=0, b=B+k*J+j; k2<cache_line_size; ++k2, b+=J) {
              for (j2=0; j2<cache_line_size; ++j2) {
              	// 5 cycle latency if assembled with fma
                c[j2] += a[k2] * b[j2];
              }
            }
          }
        }
      }
    }
#endif
#endif
  }

  // C[IxJ] = A[IxK] * B[KxJ]
  template <int I, int K, int J, typename Iterator, typename enable_if<
    // enable if any matrix dimension is smaller than the cache_line_size
    I < cache_line_size || K < cache_line_size || J < cache_line_size, int>::type = 1>
  void multiply(Iterator C, Iterator a, const Iterator B) {
#if 1
    using std::copy;
    typedef typename iterator_traits<Iterator>::value_type T;
    constexpr T zero = 0;
    // always align so that b and c each fit into one cache line
    alignas(64) T b[cache_line_size], c[cache_line_size];
    Iterator b_tmp = B;
    for (int i=0; i<I; ++i) {
      fill(c, c+J, zero);
      for (int j=0; j<J; ++j, ++a) {
        copy(b_tmp, b_tmp+J, b);
        for (int k=0; k<K; ++k) {
          c[k] += *a * b[k];
        }
        b_tmp += J;
      }
      copy(c, c+J, C);
      C += J;
      b_tmp = B;
    }
#else
#endif
  }

  // C[IxJ] = A[IxK] * B[KxJ]
  template <int I, int K, int J, typename Iterator, typename enable_if<
    // enable if all matrix dimensions are larger than cache_line_size and
    // at least one dimension is not an integral multiple of cache_line_size
    (0 != I % cache_line_size || 0 != J % cache_line_size ||
     0 != K % cache_line_size) &&
    (cache_line_size <= I && cache_line_size <= K &&
     cache_line_size <= K), int>::type = 2>
  void multiply(Iterator C, Iterator A, Iterator B) {
#if defined(__AVX) || defined(__AVX2__)
    int i2, j2, k2;
    Scalar *c_ = 0, *a_ = 0, *b_ = 0;
    Scalar zero = 0;
    for (int i=0; i<I; i+=avx_size) {
      // zero out next block
      fill(C+i*J, C+(i+avx_size)*J, zero);
      for (int j=0; j<J; j+=avx_size) {
        for (int k=0; k<K; k+=avx_size) {
          for (i2=0, c_=C+i*J+j, a_=A+i*K+k; i2<avx_size; ++i2, c_+=J, a_+=K) {
            // don't pollute l2 cache, load directly into l1 cache
            _mm_prefetch(a_+cache_line_size, _MM_HINT_NTA);
            // load c
            __m256d c = _mm256_load_pd(c_);
            for (k2=0, b_=B+k*J+j; k2<avx_size; ++k2, b_+=J) {
              // load single value into a and replicate into m256
              __m128d a_tmp = _mm_load1_pd(a_+k2);
              __m256d a = _mm256_broadcast_pd(&a_tmp);
              // load b
              __m256d b = _mm256_load_pd(b_);
              // multiply a * b, sum product, accumulate into c
              c = _mm256_add_pd(c, _mm256_mul_pd(a, b));
            }
            _mm256_store_pd(c_, c);
          }
        }
      }
    }
#else
    int i2, j2, k2;
    Scalar *c = 0, *a = 0, *b = 0;
    Scalar zero = 0;
    // vectorize this square block (not the remainders below)
    for (int i=0; i<I; i+=cache_line_size) {
      for (int j=0; j<J; j+=cache_line_size) {
        for (int k=0; k<K; k+=cache_line_size) {
          c = C+i*J+j;
          a = A+i*K+k;
          for (i2=0; i2<cache_line_size; ++i2, c+=J, a+=K) {
            fill(c, c+J, zero);
            b = B+k*J+j;
            for (k2=0; k2<cache_line_size; ++k2, b+=J) {
              for (j2=0; j2<cache_line_size; ++j2) {
                c[j2] += a[k2] * b[j2];
              }
            }
          }
        }
      }
    }
    // pick up the remainders
#endif
  }

  // multiply two vectors [a_it,a_end) and [b_it, b_it+a_end-a_it): A *= B
  // return result in vector [a_it, a_end)
  // implementation requires vector length integratl multiple of avx_size
  template <int N, typename Iterator
    , typename enable_if<0 == N % avx_size, int>::type = 0>
  void multiply(Iterator a_it, Iterator a_end, Iterator b_it) {
#if defined(__AVX__) || defined(__AVX2__)
    for (int i=0; i<N; i += avx_size, a_it += avx_size, b_it += avx_size) {
      // compute a *= b
      _mm256_store_pd(a_it
        , _mm256_mul_pd(_mm256_load_pd(a_it), _mm256_load_pd(b_it)));
    }
#else
    typedef typename iterator_traits<Iterator>::value_type T;
    transform(a_it, a_end, b_it, a_it, multiplies<T>());
#endif
  }

  // multiply two vectors [a_it,a_end) and [b_it, b_it+a_end-a_it): A *= B
  // return result in vector [a_it, a_end)
  // handle case where vector length is not integral multiple of avx_size
  template <int N, typename Iterator
    , typename enable_if<0 != N % avx_size, int>::type = 1>
  void multiply(Iterator a_it, Iterator a_end, Iterator b_it) {
#if defined(__AVX__) || defined(__AVX2__)
    for (int i=0; i<=N-avx_size; i += avx_size, a_it += avx_size, b_it += avx_size) {
      // compute a *= b
      _mm256_store_pd(a_it
        , _mm256_mul_pd(_mm256_load_pd(a_it), _mm256_load_pd(b_it)));
    }
#endif
    // handle the remainder (there's always a remainder)
    typedef typename iterator_traits<Iterator>::value_type T;
    transform(a_it, a_end, b_it, a_it, multiplies<T>());
  }

} // namespace DGM

#endif  // MATRIX_OPERATIONS_HPP
