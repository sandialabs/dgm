// Author: K. Noel Belcourt

// build from dgm directory with
// g++ -O2 util/test_subdomain_grouping.cpp -Isrc -I../boost

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <map>
#include <vector>

#include <boost/lexical_cast.hpp>

#include <SubdomainGrouping.hpp>

using boost::lexical_cast;
using DGM::id_coords;
using std::copy;
using std::cout;
using std::endl;
using std::generate;
using std::map;
using std::ostream_iterator;
using std::size_t;
using std::swap;
using std::vector;

extern "C" {
  int rmax = 65536; // INT_MAX; // 65536;
  int rand_max() {
    return rand() % rmax;
  }
}
// used to test the subdomain layout algorithm
int main(int argc, char **argv) {
  int n_subdomains = 17;
  if (2 == argc) n_subdomains = lexical_cast<int>(argv[1]);
  srand(5);


  // Test 2d interface
  typedef id_coords<double, size_t> idc_t;
  idc_t idc_2d;
  for (int i=0; i<n_subdomains; ++i) {
    int xmin = rand() % rmax;
    int xmax = rand() % rmax;
    int ymin = rand() % rmax;
    int ymax = rand() % rmax;
    if (xmax < xmin) swap(xmin, xmax);
    if (ymax < ymin) swap(ymin, ymax);
    idc_2d.add_2d(xmin, xmax, ymin, ymax, i);
#if 0
    cout << "subdomain id " << i << " x[" << xmin << "," << xmax
      << "] y[" << ymin << "," << ymax << "]" << endl;
#endif
  }
  // solve the subdomain layout problem
  idc_2d.setup_and_solve();
  idc_2d.output_histogram(cout, n_subdomains, "2d");

  // Test 3d interface
  idc_t idc_3d;
  vector<double> xs(8), ys(8), zs(8);
  for (int i=0; i<n_subdomains; ++i) {
#if 0
    generate(xs.begin(), xs.end(), rand_max);
    generate(ys.begin(), ys.end(), rand_max);
    generate(zs.begin(), zs.end(), rand_max);
    // orient x axis points
    if (xs[1] < xs[0]) swap(xs[0], xs[1]);
    if (xs[2] < xs[3]) swap(xs[2], xs[3]);
    if (xs[5] < xs[4]) swap(xs[4], xs[5]);
    if (xs[6] < xs[7]) swap(xs[6], xs[7]);
    // orient y axis points
    if (ys[1] < ys[0]) swap(ys[0], ys[1]);
    if (ys[2] < ys[3]) swap(ys[2], ys[3]);
    if (ys[5] < ys[4]) swap(ys[4], ys[5]);
    if (ys[6] < ys[7]) swap(ys[6], ys[7]);
    // orient z axis points
    if (zs[1] < zs[0]) swap(zs[0], zs[1]);
    if (zs[2] < zs[3]) swap(zs[2], zs[3]);
    if (zs[5] < zs[4]) swap(zs[4], zs[5]);
    if (zs[6] < zs[7]) swap(zs[6], zs[7]);
    idc_3d.add_3d(xs.begin(), xs.end(), ys.begin(), zs.begin(), i);
#if 1
    cout << "subdomain id " << i << endl;
    cout << "  x[ ";
    copy (xs.begin(), xs.end(), ostream_iterator<double>(cout, " "));
    cout << "]\n  y[ ";
    copy (ys.begin(), ys.end(), ostream_iterator<double>(cout, " "));
    cout << "]\n  z[ ";
    copy (zs.begin(), zs.end(), ostream_iterator<double>(cout, " "));
    cout << "]" << endl;
#endif
#else
    int xmin = rand() % rmax;
    int xmax = rand() % rmax;
    int ymin = rand() % rmax;
    int ymax = rand() % rmax;
    int zmin = rand() % rmax;
    int zmax = rand() % rmax;
    if (xmax < xmin) swap(xmin, xmax);
    if (ymax < ymin) swap(ymin, ymax);
    if (zmax < zmin) swap(zmin, zmax);
    idc_3d.add_3d(xmin, xmax, ymin, ymax, zmin, zmax, i);
#if 0
    cout << "subdomain id " << i << " x[" << xmin << "," << xmax << "]"
      << " y[" << ymin << "," << ymax << "]"
      << " z[" << zmin << "," << zmax << "]" << endl;
#endif
#endif
  }
  // solve the subdomain layout problem
  idc_3d.setup_and_solve();
  idc_3d.output_histogram(cout, n_subdomains, "3d");

  return 0;
}
