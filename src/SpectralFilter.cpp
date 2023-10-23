/** \file SpectralFilter.cpp
    \brief Defines a DGM spectral filter class
    \author Scott Collis
*/

// system includes
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <utility>
#include <cmath>
using namespace std;

// DGM includes
#include "SpectralFilter.hpp"

#ifdef DGM_USE_BOOST_MATH
#include "boost/math/special_functions/erf.hpp"
#endif

namespace DGM {

// Constructor
SpectralFilter::SpectralFilter(const Ordinal P_l, const Ordinal fdiml,
                               const string &rt) :
  Filter(P_l, fdiml), s(0) {
  string buffer;
  string fname = rt +".fil";
  ifstream specfil(fname.c_str());
  if (specfil) {
    Ordinal sl;
    getline(specfil,buffer);
    if (!(specfil>>sl)) error("Cannot read filter spectral shift",1);
    s = sl;
    //  cout<<"Spectral shift, s" <<s<<endl;
    if(s>=P) {
      DGM::Comm::World->cerr()
        << "illegal value of spectral shift s:" << s <<  endl;
      DGM::Comm::World->exit(DGM::FAILURE);
    }
  }

  if (fdim>3 || fdim <= 0) {
    DGM::Comm::World->cerr()
      << "SpectralFilter:: illegal spatial dimension for filter" <<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }

  // allocate storage
  filter_a.resize(P);
  make_filter(P,s,'a');
  if(fdim >2  ) {
    filter_b.resize(P);
    make_filter(P, s, 'b');
    filter_c.resize(P);
    make_filter(P, s, 'c');
  } else {
    filter_b.resize(P);
    make_filter(P, s, 'b');
  }

  // generates appropriate kernel i.e. mask function
  // held in => kernel
  get_kernel(fdim);
}

void SpectralFilter::make_filter(const Ordinal P, const Ordinal s,
                                 const char dir) {
  switch(dir){
  case 'a': {
    make_filter(P, s, filter_a);
    break;}
  case 'b': {
    make_filter(P, s, filter_b);
    break;}
  case  'c':{
      make_filter(P, s, filter_c);
      break;}
  default:
    DGM::Comm::World->cerr()
      << "SpectralFilter::make_filter -- unknown direction" << endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
}

void SpectralFilter::make_filter(const Ordinal P, const Ordinal s,
                                 dVector &filt ) {
  Scalar theta, omega, xi;
  Scalar iPms, dindex, omega_log, temp;

  iPms = 1.0/(static_cast<Scalar>(P-s));

  for(Ordinal i=0;i<P;i++) {
    dindex = static_cast<Scalar>(i);
    if (i < s ){
      filt[i] = 1.0;
    }
    else {
      theta = (dindex - s)*iPms;
      if (theta == 0.5) {
        xi = 1.0;
      } else {
        omega = fabs(theta) - 0.5;
        omega *=omega;
        omega *=4;
        omega_log = 1.0-omega;
        if (omega_log == 0) {
          xi = 1.0;
        } else {
          xi = sqrt(-log(omega_log)/omega);
        }
      }
      temp = 2*sqrt(static_cast<Scalar>(P-1))*xi*(fabs(theta)-0.5);
#ifdef DGM_USE_BOOST_MATH
      filt[i] = 0.5*boost::math::erfc(temp);
#else
      error("SpectralFilter::make_filter requires an Erfc function");
#endif
    }
  }
}

void SpectralFilter::get_kernel(const Ordinal f_dim){
  if(f_dim==1) {
    kernel.alias(filter_a);
  } else if (f_dim ==2) {
    Ordinal i, j , n ;
    kernel.resize(P*P);
    for(i=0;i<P;i++) {
      for(j=0;j<P;j++) {
        n = j + i*P;
        kernel[n] = filter_a[i]*filter_b[j];
      }
    }
  } else {
    Ordinal i, j , k,  n ;
    kernel.resize(P*P*P);
    for(i=0;i<P;i++) {
      for(j=0;j<P;j++) {
        for(k=0;k<P;k++) {
          n = k + j*P + i*P*P;
          kernel[n] = filter_a[i]*filter_b[j]*filter_c[k];
        }
      }
    }
  }
}

} // namespace DGM
