#include <iostream>
using namespace std;
int main() {
  int nx=16;
  int ny=8;
  int nz=8;
  int i, j, k;
  int eid;
#if 0
  for (k=0; k<nz; ++k) {
    for (i=0; i<nx; ++i) {
      j = 0;
      eid = i + j * (nx) + k * (nx)*(ny);
      cout << "T " << eid << " 1" << endl;
      j = ny-1;
      eid = i + j * (nx) + k * (nx)*(ny);
      cout << "T " << eid << " 3" << endl;
    }
  }
#endif
  for (j=0; j<ny; ++j) {
    for (i=0; i<nx; ++i) {
      k = 0;
      eid = i + j * (nx) + k * (nx)*(ny);
      cout << "T " << eid << " 0" << endl;
      k = nz-1;
      eid = i + j * (nx) + k * (nx)*(ny);
      cout << "T " << eid << " 5" << endl;
    }
  }
}
