//ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
//
//  g++ -I/usr/local/include fsine.cpp -o fsine -L/usr/local/lib -lrfftw -lfftw -lm
//
//ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <complex>
#include "rfftw.h"
#include "fftw.h"
using namespace std;

int Nx = 32;             
double up[32];           // Vector holding sine function
double uf[32];
double ufp[32];

double Kx[32];              // wavenumbers for Fourier modes
const double pi = 3.1415926535897932;

complex<double> a[17];

const double one = 1.0;
const double zero = 0.0;

const complex<double> iota(zero,one);

#if 0 
class FFT {
  rfftw_plan fft_plan;   // FFT plan
  rfftw_plan ifft_plan;  // inverse FFT plan
  double fft_scale;      // FFT scale factor
  dVector uf;
public:
  int Nx;
  dVector Kx, Kz;
  FFT(int nx) : Nx(nx) {   
    fft_plan =  rfftw_create_plan(Nx, FFTW_REAL_TO_COMPLEX, FFTW_ESTIMATE); // | FFTW_IN_PLACE );
    ifft_plan =  rfftw_create_plan(Nx, FFTW_COMPLEX_TO_REAL, FFTW_ESTIMATE); // | FFTW_IN_PLACE );
    fft_scale = 1.0 / ((double)Nx);
    uf.resize( Nx );
  };
  
  transform_to_fourier( const dVector &up, cVector &a ) {
    rfftw_one(fft_plan, up, uf);
    uf *= fft_scale;    // overloaded for dVectors
    a[0] = uf[0];
    for (int n=1; n<Nx/2; n++) {
      complex<double> z( uf[n], uf[Nx-n] );
      a[n] = z;
    }
    a[Nx/2] = uf[Nx/2];
  };

  transform_to_real( const cVector &a, dVector &up ) {} ;

  gradient( int order, const cVector &a, cVector &g1, cVector &g2 ) {
    static const iota(0,1);
  } ;
};
#endif

rfftw_plan fft_plan;   // FFT plan
rfftw_plan ifft_plan;  // inverse FFT plan
double fft_scale;      // FFT scale factor

int main() {

  fft_plan =  rfftw_create_plan(Nx, FFTW_REAL_TO_COMPLEX, FFTW_ESTIMATE); // | FFTW_IN_PLACE );
  ifft_plan =  rfftw_create_plan(Nx, FFTW_COMPLEX_TO_REAL, FFTW_ESTIMATE); // | FFTW_IN_PLACE );
  fft_scale = 1.0 / ((double)Nx);

  //calculate wave numbers

  for (int n=0;n<Nx/2+1;n++) Kx[n] = n;
  for (int n=Nx/2+1; n<Nx; n++) Kx[n] = Nx-n;

  for (int n=0; n<Nx; n++) cout << n << " " << Kx[n] << endl;

  for (int i=0;i<Nx;i++) { 
    up[i] = sin((double)i*2.0*pi/(double)(Nx)); 
  }

  rfftw_one(fft_plan, up, uf);
  for (int j=0;j<Nx;j++) {
    //    cout << "up "<< up[j] << " uf " << uf[j] << endl;
    uf[j] *= fft_scale;
    cout << up[j] << '\t' << uf[j] << endl;
  }

  a[0] = uf[0];
  for (int n=1; n<Nx/2; n++) {
    complex<double> z( uf[n], uf[Nx-n] );
    a[n] = z;
  }
  a[Nx/2] = uf[Nx/2];

  //  for (int n=0; n<Nx/2+1; n++) cout << Kx[n] << " " << a[n] << endl;
  
  cout << iota << endl;
  cout << pi << endl;

  // take derivative
  for (int j=0; j<Nx/2+1; j++) a[j] *= iota * Kx[j];

  uf[0] = a[0].real();
  for (int n=1; n<Nx/2; n++) {
    uf[n] = a[n].real();
    uf[Nx-n] = a[n].imag();
  }
  uf[Nx/2] = a[Nx/2].real();

  rfftw_one(ifft_plan, uf, ufp);
  for (int k=0;k<Nx;k++) {
    cout << "uf " << uf[k] << " ufp " << ufp[k] << endl;
  }
  
  
  return 0;
}

