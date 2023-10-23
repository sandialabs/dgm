
/** \file   mkbnd.cpp
    \brief  Generate a boundary
    \author Scot Collis
**/

#include <iostream>
using namespace std;

int main() {
  int s(1920);
  int e(128);
  int inc(1);
  for( int i=s; i<s+e; i++ )
    cout << i << " " << 0 << endl;
}
