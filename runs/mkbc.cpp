#include <iostream>
using namespace std;

int main() {
  int nx(40);
  int ny(40);
  cout << "** Boundary Conditions **" << endl;
  cout << 2*nx+2*ny << " nbc" << endl; 
  int i, e, j=0;
  for( i=0; i<nx; i++ ) {
    e=i+j*nx;
    cout << "N " << e << " " << 0 << endl;
  }
  j = ny-1;
  for( i=0; i<nx; i++ ) {
    e=i+j*nx; 
    cout << "N " << e << " " << 2 << endl;
  }
  i = 0;
  for (j=0; j<ny; j++) {
    e = i+j*nx; 
    cout << "N " << e << " " << 3 << endl;
  }
  i = nx-1; 
  for (j=0; j<ny; j++) {
    e = i+j*nx; 
    cout << "N " << e << " " << 1 << endl;
  }
}
