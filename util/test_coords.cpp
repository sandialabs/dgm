// g++ -g -Isrc -I../local/boost/include -I../local/atlas/include util/test_coords.cpp

#include <ftw.h>
#include <unistd.h>

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <boost/lexical_cast.hpp>

#include <SubdomainGrouping.hpp>

using std::cout;
using std::endl;
using std::ifstream;
using std::min;
using std::max;
using std::string;
using std::vector;

using boost::lexical_cast;

using DGM::id_coords;

template <typename T>
struct point {
  T x, y, z;
  point() : x(0), y(0), z(0) {}
  point(T x_, T y_, T z_) : x(x_), y(y_), z(z_) {}
};

struct subdomain {
  int id;
  point<double> src_location;
  vector< point<double> > rec_locations;
};

  double x, y, z;
  string file;
  typedef vector< point<double> >::iterator s_iterator;
  typedef vector<subdomain>::iterator n_iterator;
  vector<subdomain> subdomains;

int fn(const char *fpath, const struct stat *sb, int typeflag,
  struct FTW *ftwbuf)
{
  if (S_ISREG(sb->st_mode)) {
    // get this setting number
    string setting = fpath;
    int begin = setting.find("setting.");
    if (string::npos == begin) return 0;
    begin += 8;
    int end = setting.find("/", begin) - 1;
    assert(0 < begin && begin < end);
    // string s = setting.substr(begin, end-begin+1);
    int n = lexical_cast<int>(setting.substr(begin, end-begin+1));
    // a regular file, not a directory
    file = fpath;
    if (string::npos != file.find("src")) {
      // cout << "processing source for subdomain " << n << endl;
      ifstream src(fpath);
      src >> x >> y >> z;
      // cout << x << " " << y << " " << z << endl;
      src.close();
      // if (subdomains.size() < n) subdomains.resize(n);
      subdomain &a = subdomains[n];
      a.id = n;
      a.src_location.x = x;
      a.src_location.y = y;
      a.src_location.z = z;
    }
    else if (string::npos != file.find("rec")) {
      // cout << "processing receivers for subdomain " << n << endl;
      ifstream rec(fpath);
      // if (subdomains.size() < n) subdomains.resize(n);
      subdomain &a = subdomains[n];
      a.id = n;
      while (rec.good() && !rec.eof()) {
        rec >> x >> y >> z;
        // cout << x << " " << y << " " << z << endl;
        a.rec_locations.push_back(point<double>(x, y, z));
      }
      rec.close();
    }
  }
  return 0;
}

int main(int, char **) {
  subdomains.resize(48000);
  string dirpath;
  int flags = 0;
#if defined(__APPLE__)
  char buffer[1024];
  getcwd(buffer, 1024);  // get_current_dir_name();
  dirpath = buffer;
#else
  flags = FTW_CONTINUE;
  dirpath = get_current_dir_name();
#endif
  cout << "dirpath: " << dirpath << endl;
  int nopenfd = 1000;
  int rc = nftw(dirpath.c_str(), fn, nopenfd, flags);
  // Test 3d subdomain grouping interface
  typedef id_coords<double, DGM::XYZ, int> idc_t;
  idc_t idc_3d;
  // compute bounding box for each subdomain
  n_iterator it = subdomains.begin(), end = subdomains.end();
  s_iterator s_it, s_end;
  double x_min, x_max, y_min, y_max, z_min, z_max;
  for (; it != end; ++it) {
    subdomain &s = *it;
    x_min = x_max = s.src_location.x;
    y_min = y_max = s.src_location.y;
    z_min = z_max = s.src_location.z;
    s_it = s.rec_locations.begin();
    s_end = s.rec_locations.end();
    for (; s_it != s_end; ++s_it) {
      point<double> &p = *s_it;
      x_min = min(x_min, p.x);
      x_max = max(x_max, p.x);
      y_min = min(y_min, p.y);
      y_max = max(y_max, p.y);
      z_min = min(z_min, p.z);
      z_max = max(z_max, p.z);
    }
    cout << "bounding box for subdomain " << s.id << endl;
    cout << "  x[" << x_min << " " << x_max << "] ";
    cout << "y[" << y_min << " " << y_max << "] ";
    cout << "z[" << z_min << " " << z_max << "]" << endl;
    // add box
    idc_3d.add_3d(x_min, x_max, y_min, y_max, z_min, z_max, s.id);
  }
  // solve the subdomain layout problem
  idc_3d.setup_and_solve();
  idc_3d.output_histogram(cout, subdomains.size(), "3d");
  return 0;
}
