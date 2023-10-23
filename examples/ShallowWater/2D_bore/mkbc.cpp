#include <iostream>
using namespace std;

int main() {
  int nx(32);
  int ny(32);
  cout << "** Boundary Conditions **" << endl;
  int i = (2*nx) + (2*ny);
  cout << i << " nbc" << endl;
  for( i=0; i<nx; i++ )
    cout << "W "<< i << " " << 0 << endl;
  int j = nx * (ny -1);
  for( i=j; i<(nx*ny); i++ )
    cout << "W "<< i << " " << 2 << endl;
  for( i=0; i<ny; i++ )
    cout << "W "<< i*nx << " " << 3 << endl;
  for( i=0; i<ny; i++ )
    cout << "W "<< ((i+1)*nx)-1 << " " << 1 << endl;
}
