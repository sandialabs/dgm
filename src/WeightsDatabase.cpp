/** \file WeightsDatabase.cpp
    \brief Weights database implementation
    \author Noel Belcourt
*/

// system includes
#include <cstdio>
#include <fstream>
#include <iomanip>
#include <iterator>
#include <stdexcept>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <limits>
#include <errno.h>
#include <time.h>
#include <cassert>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
using namespace std;

// boost includes
#include <boost/lexical_cast.hpp>
#include <boost/numeric/conversion/cast.hpp>

// DGM includes
#include "WeightsDatabase.hpp"

namespace {
  std::string dateTime() {
    const int buflen = 256;
    char now[buflen] = "Time is not available";
    time_t tp = ::time(0);
    strftime(now,buflen,"%a %b %d %Y at %H:%M:%S", localtime(&tp));
    return now;
  }
}

namespace DGM {

//===========================================================================
//         W e i g h t   D a t a b a s e   I m p l e m e n t a t i o n
//===========================================================================

// there's base-1 p orders in the database, numbered [0,base-1)
static const int curvature_max = 2;
static const int base = 21;  // highest supported p order
static const int polynomial_order_max = base + 1;
static const int verb = 0;  // verbosity flag

// real size will be set when database is read
WeightsDatabase::WeightsDatabase()
  : scale(1.0e7), num_groups(4), physics_min(617)
  , size(0), physics_index(0), values(0), p_names(0), e_names(0)
{
}

WeightsDatabase::WeightsDatabase(std::string file_name, unsigned num_physics,
  const int physics)
  : scale(1.0e7), num_groups(4), physics_min(num_physics)
  , size(0), physics_index(0), values(0), p_names(0), e_names(0)
{
  read(file_name);
  size = physics_min * Topology::NumElementTypes * curvature_max *
    polynomial_order_max;
  physics_index = physics * Topology::NumElementTypes * curvature_max *
                  polynomial_order_max;
}

WeightsDatabase::WeightsDatabase(unsigned num_physics, const int physics,
  std::vector<std::string>& pnames, std::vector<std::string>& enames)
  : scale(1.0e7), num_groups(4), physics_min(num_physics)
  , size(physics_min * Topology::NumElementTypes * curvature_max *
         polynomial_order_max)
  , physics_index(0), values(size), p_names(0), e_names(0)
{
  assert(pnames.size() == num_physics);
  p_names.swap(pnames);
  e_names.swap(enames);

  physics_index = physics * Topology::NumElementTypes * curvature_max *
                  polynomial_order_max;
  if (0 < verb) {
    cout << "num_physics: " << num_physics << endl;
    cout << "physics: " << physics << endl;
    cout << "physics_index: " << physics_index << endl;
  }
#if 0
  // initialize default weight values to w = 100 * p ^ d
  // where p is polynomial order and d is element dimension
  for (unsigned i=0; i<num_physics; ++i)
    for (unsigned j=0; j<Topology::NumElementTypes; ++j) {
      // get element dimension
      int d = dimension(Etype(j));
      for (int k=0; k<2; ++k)
        for (int m=0; m<base; ++m) {
          int index = get_index(i, Mesh::Etype(j), k, m);
          values[index] = boost::numeric_cast<int>(100.0 * pow(Scalar(m+1),d));
        }
    }
#endif
}

int WeightsDatabase::get_index(unsigned p, Topology::ElementType e, bool c,
                               Ordinal porder) {
  int index = p * Topology::NumElementTypes * curvature_max *
    polynomial_order_max;
  index += e * curvature_max * polynomial_order_max;
  index += int(c) * polynomial_order_max;
  index += porder;
  assert(0 <= index && index < size);
  return index;
}

int WeightsDatabase::get_index(Topology::ElementType e, bool is_affine,
                               Ordinal porder) {
  using boost::lexical_cast;
  int index = physics_index;
  index += e * curvature_max * polynomial_order_max;
  index += int(is_affine) * polynomial_order_max;
  index += porder;
  if (!(0 <= index && index < size)) {
    string s = "WeightsDatabase dimensions don't match current "
      "code capabilities, you may need to regenerate the weights database.\n";
    s += " physics_index: " + lexical_cast<string>(physics_index);
    s += " curvature_max: " + lexical_cast<string>(curvature_max);
    s += " polynomial_max: " + lexical_cast<string>(polynomial_order_max);
    s += " e: " + lexical_cast<string>(e);
    s += " is_affine: " + lexical_cast<string>(is_affine);
    s += " porder: " + lexical_cast<string>(porder);
    s += " index: " + lexical_cast<string>(index);
    s += "\n";
    throw runtime_error(s);
  }
  return index;
}

void WeightsDatabase::add_weight(Topology::ElementType e, bool is_affine,
                                 Ordinal porder, Scalar v)
{
  if (0 < verb) {
    cout << "ElementType: " << e << endl;
    cout << "is_affine: " << is_affine << endl;
    cout << "porder: " << porder << endl;
    cout << "v: " << v << endl;
  }
  // ensure porder is in range
  if (base-1 < porder) throw invalid_porder();
  // negative and zero timings are disallowed
  assert(0 < v);
  // check that requested value is in database
  int index = get_index(e, is_affine, porder);
  if (0 < verb) cout << "index: " << index << endl;
  // if p order is zero, affine curvature (true) and element
  // is quad (2d) or hex (3d), this is base value for normalization
  if (0 == porder && is_affine &&
      (e == Topology::Quad || e == Topology::Hex)) {
    // convert weight to int
    int i = int(v * scale);
    // index of porder values for this curvature
    int pbase_index = get_index(e, true, base);
    // save base value for normalization by averaging
    // if non-zero base value
    if (0 == values[pbase_index])
      values[pbase_index] = i;
    else
      // average to smooth out variability
      values[pbase_index] = (values[pbase_index] + i) / 2;
    // normalize
    values[index] = 100;
  } else {
    // get (affine) normalization value (quad for 2d, hex for 3d)
    if (dimension(e) == 2)
      e = Topology::Quad;
    else if (dimension(e) == 3)
      e = Topology::Hex;
    else {
      // 1d not supported
      assert(0 /* graph weights don't support 1d elements */);
    }
    int affine_index = get_index(e, true, base);
    Scalar d = values[affine_index];
    // if normalization value is zero, store scaled time
    if (d == 0.0) {
      // store scaled time, will be normalized when affine value is stored
      d = v * scale;
    } else {
      // store weight value at this index
      d = 100.0 * (v * scale) / d;
    }
    // average timing value to smooth out variability
    if (0 == values[index])
      // no previous value, store it
      values[index] = static_cast<int>(d);
    else
      // a previous value, average it
      values[index] = (values[index] + int(d)) / 2;
  }
  if (0 < verb) cout << "add_weight completed" << endl;
}

int WeightsDatabase::get_weight(Topology::ElementType e, bool c,
                                Ordinal porder) {
  using std::abs;
  using boost::numeric_cast;

  // if user requests porder larger than table supports
  // extrapolate to requested porder based on two
  // largest table values
  if (base-1 <= porder) {
    // grab last two values and straight line extrapolate
    int im2 = get_index(e, c, base-3);
    int im1 = get_index(e, c, base-2);
    int pm2 = values[im2];
    int pm1 = values[im1];
    // ensure non-zero values
    if (0 < pm1 && 0 < pm2) {
      // y = mx+b
      int m = abs(pm1 - pm2);  // could be negative so abs
      int y = m * (numeric_cast<int>(porder)-base+2) + pm1;
      // sanity check that extrapolation gave us reasonable value
      if (y < pm1) y = pm1;
      return y;
    }
    else {
      // default weight normalized to 100
      // 99 + (p+1)^d
      int d = Topology::dimension(e);
      int v = numeric_cast<int>(porder)+1;
      if (1 < d) v *= v;
      if (2 < d) v *= v;
      return 99 + v;
    }
  }
  else {
    // check that requested value is in database
    int index = get_index(e, c, porder);
    // return weight at this index if non-zero or
    // return default value p^d
    int v = values[index];
    if (0 == v) {
      // 99 + (p+1)^d
      int d = Topology::dimension(e);
      int v = numeric_cast<int>(porder)+1;
      if (1 < d) v *= v;
      if (2 < d) v *= v;
      v += 99;
    }
    return v;
  }
}

// raii idiom for ensuring we release file lock.
// Rely on unix advisory locking, if locking is
// mandatory, then the exclusive lock will fail
// as we open and lock, then open for real, the
// second open for writing will block.
struct shared_flock {
  int fd;
  shared_flock(string& filename) : fd(0) {
    fd = open(filename.c_str(), O_RDONLY);
    int rc = 0;
    while ((rc = flock(fd, LOCK_SH)) == EINTR) ;
  }
  ~shared_flock() {
    flock(fd, LOCK_UN);
    close(fd);
  }
};

struct exclusive_flock {
  int fd;
  exclusive_flock(string& filename) : fd(0) {
    if (0 < verb) cout << "exclusive_flock constructor" << endl;
    mode_t mode = S_IRWXU | S_IRGRP | S_IXGRP;
    if ((fd = open(filename.c_str(), O_CREAT|O_WRONLY, mode)) == -1) {
      perror("exclusive_flock failed:");
      assert(0 /* unexpectedly failed to open file */);
    }
    int rc = 0;
    while ((rc = flock(fd, LOCK_EX)) == EINTR) ;
    if (0 < verb) cout << "completed exclusive_flock constructor" << endl;
  }
  ~exclusive_flock() {
    if (0 < verb) cout << "exclusive_flock destructor" << endl;
    flock(fd, LOCK_UN);
    close(fd);
    if (0 < verb) cout << "completed exclusive_flock destructor" << endl;
  }
};

void WeightsDatabase::read(std::string file_name) {
  using std::copy;
  using std::ifstream;
  using std::istream_iterator;

  // get exclusive lock to weights file
  shared_flock sfl(file_name);

  // write max indices for each enumertaion so can check for consistency
  // and report an error if they don't match
  ifstream ifp(file_name.c_str());
  // ensure we found a file
  if (ifp.eof() || !ifp.good()) throw file_not_found();

  // read date time string off file line
  char buf[80];
  string buffer;
  getline(ifp, buffer);

  int ng = 0, c, o;
  Topology::size_type p, e;

  // number of top-level groups
  ifp >> ng;
  assert(ng == num_groups);

  // check that number of entries in each group match this code
  ifp >> p >> e >> c >> o;
  // may be more physics than DGM knows about
  if (p != physics_min || e != Topology::NumElementTypes ||
    c != curvature_max || o != polynomial_order_max)
    throw runtime_error("WeightsDatabase dimensions don't match current "
                         "code capabilities\n"
                         "  Regenerate the weights database.");

  // read physics and element names
  p_names.resize(p);
  e_names.resize(e);
  for (unsigned i=0; i<p; ++i) ifp >> p_names[i];
  for (unsigned i=0; i<e; ++i) ifp >> e_names[i];

  // allocate for bulk data
  values.resize(p * e * c * o);

  // read bulk data
  vector<int>::iterator it = values.begin();
  for (unsigned i=0; i<physics_min; ++i) {
    for (unsigned j=0; j<Topology::NumElementTypes; ++j) {
      for (int k=0; k<curvature_max; ++k) {
        ifp >> ws;
        ifp.getline(&buf[0], 80);
        for (int p=0; p<polynomial_order_max; ++p) {
          ifp >> *it;
          ++it;
        }
      }
    }
  }

  // done
  ifp.close();
}

void WeightsDatabase::write(string file_name)
{
  using std::copy;
  using std::ofstream;
  using std::ostream_iterator;

  if (0 < verb) cout << "in WeightsDatabase::write" << endl;
  // get exclusive lock to weights file
  exclusive_flock efl(file_name);
  // write max indices for each enumertaion so can check for consistency
  // and report an error if they don't match
  ofstream ofp(file_name.c_str());
  // output date, time, and hostname into the file
  char buf[80];
  gethostname(buf, 80);
  ofp << "# file updated: " << dateTime() << " on machine " << buf << endl;
  // number of top-level groups
  ofp << 4 << '\n';
  // number of entries in each group
  ofp << physics_min << ' ' << Topology::NumElementTypes << ' '
      << curvature_max << ' ' << polynomial_order_max << '\n';

  // write physics and element names
  copy(p_names.begin(), p_names.end(), ostream_iterator<string>(ofp, " "));
  ofp << endl;
  copy(e_names.begin(), e_names.end(), ostream_iterator<string>(ofp, " "));
  ofp << endl;

  string curves[2];
  curves[0] = "nonaffine";
  curves[1] = "affine";

  // write data, newline delimited
  vector<int>::iterator it = values.begin();
  for (unsigned i=0; i<physics_min; ++i) {
    for (unsigned j=0; j<Topology::NumElementTypes; ++j) {
      for (int k=0; k<curvature_max; ++k) {
        ofp << "# " << p_names[i] << " " << e_names[j] << " "
            << curves[k] << endl;
        copy(it, it+polynomial_order_max, ostream_iterator<int>(ofp, "\n"));
        it += polynomial_order_max;
      }
    }
  }
  // done
  ofp.close();
  if (0 < verb) cout << "completed WeightsDatabase::write" << endl;
}

} // namespace DGM
