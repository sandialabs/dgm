#ifndef DGM_FORMAT_HPP
#define DGM_FORMAT_HPP

/*============================================================================
  Format class:

  A helper class for formating floating point output when using C++ streams.

  The original version was inspired by the example class on p. 631 of
  "The C++ Programming Language," by Bjarne Stroustrup.

  Author:     S. Scott Collis

  Copyright:  (c)2003 Rice University
              (c)2010 Sandia National Laboratories
  ===========================================================================*/

/** \file Format.hpp
    \brief Formats floating point output when using C++ streams.
    \author Scott Collis
*/

// system includes
#include <sstream>
#include <iomanip>
using namespace std;

namespace DGM {

// forward declaration
struct BoundFormat;

/// Provides a convenient means of formating stream output
class Format{
  friend std::ostream& operator<<(std::ostream &, const BoundFormat &);
  int prc;
  int wdt;
  ios::fmtflags fmt;
public:
  explicit Format(int p=6) : prc(p) {
    fmt = ios::fmtflags(0);
    wdt = 0;
  }

  explicit Format(int p, int w, char f) : prc(p), wdt(w) {
    switch (f) {
    case 'f':
      fmt=ios::fixed;
      break;
    case 'e':
      fmt=ios::scientific;
      break;
    }
  }

  BoundFormat operator() (double d) const;

  Format& scientific() {fmt=ios::scientific; return *this;}
  Format& fixed() {fmt=ios::fixed; return *this;}
  Format& general() {fmt=ios::fmtflags(0); return *this;}

  Format& uppercase();  // unimplemented
  Format& lowercase();  // unimplemented
  Format& precision(int p) {prc=p; return *this;}

  Format& width(int w) {wdt=w; return *this;}
  Format& fill(char);   // unimplemented

  Format& plus(bool b=true);
  Format& trailing_zeros(bool b=true);
};

/// Bounds a format to a double
struct BoundFormat {
  const Format &f;
  double val;
  BoundFormat(const Format &ff, double v) : f(ff), val(v) {}
};

/// evaluate
inline BoundFormat Format::operator() (double d) const {
  return BoundFormat(*this,d);
}

/// output to a stream
inline std::ostream &operator << (std::ostream &os, const BoundFormat &bf) {
  ostringstream s;
  s.precision(bf.f.prc);
  s.width(bf.f.wdt);
  s.setf(bf.f.fmt,ios::floatfield);
  s<<bf.val;
  return os << s.str();
}

} // namespace DGM

#endif  // DGM_FORMAT_HPP
