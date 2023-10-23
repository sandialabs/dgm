/** \file   mkcrv.cpp
    \brief  Generate a curve
    \author Scott Collis
**/

#include <iostream>
using namespace std;

int main() {
  for( int i=0; i<800; i++)
    if ( i%20 ) cout << i << " " << 0 << " skew" << endl;
}
