/*  Test of the GNU Scientific Library

Compile using

g++ -o gsl-test gsl-test.cpp -lgsl -L/home/collis/dist/atlas/lib \
-lcblas -latlas

or

g++ -o gsl-test gsl-test.cpp -lgsl -lgslcblas

SSC: Fri Jan 31 17:05:19 CST 2003

*/

#include <stdio.h>
#include "gsl/gsl_sf_bessel.h"
#include "gsl/gsl_sf_erf.h"

int
main (void)
{
  double x = 5.0;

  double y = gsl_sf_bessel_J0 (x);

  printf("J0(%g) = %.18e\n", x, y);

  y = gsl_sf_erfc(1);

  printf("erfc(%g) = %.18e\n", x, y);

  return 0;
}

