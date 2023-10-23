#include <fenv.h>
#include <stdio.h>
#include <float.h>
#include <iostream>

/* How to build on Mac OS-X:
   c++ -O2 -std=c++11 -D DISABLE_DENORMS dnorm.cpp -o dnorm && time ./dnorm
   c++ -O2 -std=c++11 dnorm.cpp -o dnorm && time ./dnorm
 Results:
   0.162u 0.001s 0:00.16 100.0%  0+0k 0+0io 2pf+0w
   6.273u 0.016s 0:06.31 99.5% 0+0k 0+0io 2pf+0w
*/
int main() {
try {
typedef double scalar;
#ifdef DISABLE_DENORMS
int stat = fesetenv(&_FE_DFL_DISABLE_SSE_DENORMS_ENV);
#endif
const scalar x[16] = { 1.1,   1.2,   1.3,     1.4,   1.5,   1.6,   1.7,   1.8,
                       1.9,   2.0,   2.1,     2.2,   2.3,   2.4,   2.5,   2.6};
const scalar z[16] = {1.123, 1.234, 1.345, 156.467, 1.578, 1.689, 1.790, 1.812,
                      1.923, 2.034, 2.145,   2.256, 2.367, 2.478, 2.589, 2.690};
scalar y[16];
for (int i = 0; i < 16; i++) {
  y[i] = x[i];
}
for (int j = 0; j < 9000000; j++) {
  for (int i = 0; i < 16; i++) {
    y[i] *= x[i];
    y[i] /= z[i];
#ifdef USE_SCALING
    y[i] = y[i] + 0.1;
    y[i] = y[i] - 0.1;
#else
    y[i] = y[i] + 0;
    y[i] = y[i] - 0;
#endif
  }
}
} 
catch(...) { 
  std::cout<<"Caught an unknown exception"<<std::endl;
}
return 0;
}
