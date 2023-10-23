#ifndef DGM_FFT_HPP
#define DGM_FFT_HPP

/** \file FFT.hpp
    \brief DGM interface to FFT libraries
    \author Scott Collis

    \note The intent here is to supply interfaces to multiple FFT libraries
    as needed.

    \note You are responsible for not distributing code or objects that
    contain GPL software as this is incompatible with the DGM BSD licence.

    \note There are commercially licenced versions FFT implementations from
    Cray (LibSci), Intel (MKL) and IBM (ESSL) and the goal of this class
    is to provide a flexible interface to these so that you can use the
    one that is available to you or best for your purpose.
*/

// system includes
#include <vector>

// external includes
#ifdef DGM_USE_FFTW
// =====================================================================
// Please be careful when linking to FFTW libraries as they may be GPL.  
// Some vendors package commercially licensed FFTW libraries (Cray, MLK)
// =====================================================================
#include "rfftw.h"
#endif

// local include
#include "Types.hpp"

namespace DGM {

/// FFT interface class
class FFT {

  std::vector<Ordinal> N;  ///< FFT dimensions
  std::vector<Scalar> L;   ///< Domain dimensions
  std::vector<dVector> K;  ///< Wavenumbers
  iVector M;  ///< Odd-ball wavenumber

  Scalar _scale;           ///< FFT scale factor

#ifdef DGM_USE_FFTW
  rfftw_plan rfft_plan;    ///< FFT 1d plan
  rfftw_plan irfft_plan;   ///< inverse FFT plan

  rfftwnd_plan fft_plan;   ///< FFT multi-d plan
  rfftwnd_plan ifft_plan;  ///< inverse FFT multi-d plan
#endif

  public:

  typedef DGM::Shared<FFT>::Ptr Ptr;   ///< FFT pointer type

  /// 1d constructor
  FFT(const Ordinal n0) : N(1,0), L(1,two*pi), _scale(0) {
    N[0] = n0;
#ifdef DGM_USE_FFTW
    rfft_plan = rfftw_create_plan(N[0], FFTW_REAL_TO_COMPLEX,
                                  FFTW_ESTIMATE | FFTW_IN_PLACE);
    irfft_plan = rfftw_create_plan(N[0], FFTW_COMPLEX_TO_REAL,
                                   FFTW_ESTIMATE);
    _scale = 1.0/((Scalar)N[0]);
#else
    DGM_UNDEFINED;
#endif
  }

  /// 2d constructor
  FFT(const Ordinal n0, const Ordinal n1) : N(2,0), L(2,two*pi), _scale(0) {
    N[0] = n0;
    N[1] = n1;
#ifdef DGM_USE_FFTW
    cout<<"Building 2d FFT plans"<<endl;
    fft_plan = rfftw2d_create_plan(N[0], N[1], FFTW_REAL_TO_COMPLEX,
                                   FFTW_ESTIMATE | FFTW_IN_PLACE);
    ifft_plan = rfftw2d_create_plan(N[0], N[1], FFTW_COMPLEX_TO_REAL,
                                    FFTW_ESTIMATE);
    _scale = 1.0/((Scalar)N[0]*(Scalar)N[2]);

    cout << "N[0] = " << N[0] << endl;
    cout << "N[1] = " << N[1] << endl;

    // oddball wavenumbers
    M.resize(2);
    M[0] = (N[0]+2)/2;
    M[1] = (N[1]+2)/2;

    cout << "Oddball wavenumbers " << M << endl;

    // setup wavenumbers
    K.resize(2);
    K[0].resize(M[0]);
    K[1].resize(N[1]);
    for (Ordinal i=0; i<M[0]; ++i) {
      K[0][i] = 2.0*pi / L[0] * (Scalar)(i);
    }
    K[1][0] = 0.0;
    for (Ordinal j=1; j<M[1]; ++j) {
      K[1][N[1]-j] = -2.0*pi / L[1] * (Scalar)(j);
      K[1][j]      =  2.0*pi / L[1] * (Scalar)(j);
    }
    cout<<"Finished building 2d FFT plans"<<endl;
#else
    DGM_UNDEFINED;
#endif
  }

  /// 3d constructor
  FFT(const Ordinal n0, const Ordinal n1, const Ordinal n2)
  : N(3,0), L(3,two*pi), _scale(0) {
    N[0] = n0;
    N[1] = n1;
    N[2] = n2;
#ifdef DGM_USE_FFTW
    fft_plan  = rfftw3d_create_plan(N[0], N[1], N[2], FFTW_REAL_TO_COMPLEX,
                                    FFTW_ESTIMATE);
    ifft_plan = rfftw3d_create_plan(N[0], N[1], N[2], FFTW_COMPLEX_TO_REAL,
                                    FFTW_ESTIMATE);
    _scale = 1.0/((Scalar)N[0]*(Scalar)N[1]*(Scalar)N[2]);
#else
    DGM_UNDEFINED;
#endif
  }

  /// return the fft scale factor
  Scalar scale() { return _scale; }

  /// set the fft scale factor
  void scale(const Scalar scale) { _scale = scale; }

  void forward_transform(cVector &u, dVector &ur) {
#ifdef DGM_USE_FFTW
    // This next call is a problem in that the std::complex<Scalar>* cannot be
    // cast to fftw_complex* (which is a simple struct with real, imag).  I
    // searched the FFTW web site and they indicate that in FFTW-3 the
    // fftw_complex data type is conformal with the C++ complex<Scalar> type.
    // Likewise, there is a C99 standard enhancement to C that enables complex
    rfftwnd_one_complex_to_real( ifft_plan,
                                 reinterpret_cast<fftw_complex*>(u.data()),
                                 ur.data() );
#else
    DGM_UNDEFINED;
#endif
  }

  void backward_transform(dVector &ur, cVector &u) {
#ifdef DGM_USE_FFTW
    rfftwnd_one_real_to_complex( fft_plan, ur.data(),
                                 reinterpret_cast<fftw_complex*>(u.data()) );
#else
    DGM_UNDEFINED;
#endif
  }

};

} // namespace DGM

#endif
