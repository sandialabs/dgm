#include <iostream>
using namespace std;

int main() {
  for( int i=0; i<4840; i++) {
    if ( ((i >= 1600) && (i <= 3200)) && ((i-1600)%40==0) ) { 
      cout << i << " " << 2 << " arc" << endl;
    } else {
      cout << i << " " << 0 << " skew" << endl;
    }
  }
}
