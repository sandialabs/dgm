#include <fenv.h>
#include <stdio.h>
#include <float.h>

#ifndef __APPLE__
#include <xmmintrin.h>
#include <pmmintrin.h>
#endif

/* How to build on Mac OS-X:
   cc -O2 -D DISABLE_DENORMS dnorm.c -o dnorm && time ./dnorm
   cc -O2 dnorm.c -o dnorm && time ./dnorm

 Results:
   0.162u 0.001s 0:00.16 100.0%  0+0k 0+0io 2pf+0w
   6.273u 0.016s 0:06.31 99.5% 0+0k 0+0io 2pf+0w

 On a Cray use:

   CC -msse3 -D DISABLE_DENORMS dnorm.c - dnorm && time aprun ./dnorm

   real	0m2.958s
   user	0m0.124s
   sys	0m0.020s

   CC -msse3 dnorm.c -o dnorm && time aprun ./dnorm

   real	1m51.478s
   user	0m0.116s
   sys	0m0.016s

 Note:  on the Cray and Linux you cannot use optimization or it will just 
 skip the whole code (which is annoying)
*/
int main() {
typedef double scalar;
#ifdef DISABLE_DENORMS
#ifdef __APPLE__
int stat = fesetenv(&_FE_DFL_DISABLE_SSE_DENORMS_ENV);
#else
_MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
_MM_SET_DENORMALS_ZERO_MODE(_MM_DENORMALS_ZERO_ON);
#endif
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
return 0;
}
