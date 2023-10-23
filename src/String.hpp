#ifndef DGM_STRING_HPP
#define DGM_STRING_HPP

/** \file String.hpp
    \brief DGM string utilities
*/

// system includes
#include <string>
#include <vector>
#include <set>
#include <locale>
#include <iostream>
#include <sstream>
#include <fstream>
#include <limits>
#include <cassert>

namespace DGM {

/// \name String utilities
//@{

/// Make an uppercase copy of s:
inline std::string upperCase(const std::string& s) {
  using std::ctype;
  using std::locale;
  using std::string;
  using std::toupper;
  using std::use_facet;
  if (s.empty()) return string();
  locale loc;
  char* buf = new char[s.length()];
  s.copy(buf, s.length());
  for(size_t i = 0; i < s.length(); i++)
#if 1
    buf[i] = use_facet< ctype<char> >(loc).toupper(buf[i]);
#else
    buf[i] = toupper(buf[i]);
#endif
  string r(buf, s.length());
  delete[] buf;
  return r;
}

/// Make a lowercase copy of s:
inline std::string lowerCase(const std::string& s) {
  using std::ctype;
  using std::locale;
  using std::string;
  using std::toupper;
  using std::use_facet;
  // or
  // if(s.empty()) return string();
  // string a(s);
  // std::use_facet<std::ctype<char> >
  //   (std::locale("")).tolower(&a[0],&a[0]+a.size());
  // return a;
  if (s.empty()) return string();
  locale loc;
  char* buf = new char[s.length()];
  s.copy(buf, s.length());
  for(size_t i = 0; i < s.length(); i++)
#if 1
    buf[i] = use_facet< ctype<char> >(loc).tolower(buf[i]);
#else
    buf[i] = tolower(buf[i]);
#endif
  string r(buf, s.length());
  delete[] buf;
  return r;
}

/// Replace all occurrences of string f with string r
inline std::string replaceAll(std::string s, const std::string f, 
                              const std::string r) 
{
  using std::string;
  size_t found = s.find(f);
  while(found != string::npos) {
    s.replace(found, f.length(), r);
    found = s.find(f);
  }
  return s;
}

/// Remove HTML tags from a string
inline std::string stripHTMLTags(std::string s) {
  using std::string;
  while(true) {
    size_t left = s.find('<');
    size_t right = s.find('>');
    if(left==string::npos || right==string::npos)
      break;
    s = s.erase(left, right - left + 1);
  }
  s = replaceAll(s, "&lt;", "<");
  s = replaceAll(s, "&gt;", ">");
  s = replaceAll(s, "&amp;", "&");
  s = replaceAll(s, "&nbsp;", " ");
  // Etc...
  return s;
}

/// Return an empty string
inline std::string asString() {
  std::string value="";
  return value;
}

/// Convert object to a string
template <class T>
inline std::string asString(const T &t) {
  std::stringstream ss;
  ss << t;
  return ss.str();
}

/// Convert vector<int> to a string
template <>
inline std::string asString<std::vector<int> >(const std::vector<int> &t) {
  std::stringstream ss;
  ss << "[";
  for (size_t i=0; i< t.size(); i++)
    ss << " " << t[i];
  ss << " ]";
  return ss.str();
}

/// Convert vector<long> to a string
template <>
inline std::string asString<std::vector<long int> >
(const std::vector<long int> &t) {
  std::stringstream ss;
  ss << "[";
  for (size_t i=0; i< t.size(); i++)
    ss << " " << t[i];
  ss << " ]";
  return ss.str();
}

/// Convert vector<size_t> to a string
template <>
inline std::string asString<std::vector<long unsigned int> >
(const std::vector<long unsigned int> &t) {
  std::stringstream ss;
  ss << "[";
  for (size_t i=0; i< t.size(); i++)
    ss << " " << t[i];
  ss << " ]";
  return ss.str();
}

/// Convert vector<long long unsigned int> to a string
template <>
inline std::string asString<std::vector<long long unsigned int> >
(const std::vector<long long unsigned int> &t) {
  std::stringstream ss;
  ss << "[";
  for (size_t i=0; i< t.size(); i++)
    ss << " " << t[i];
  ss << " ]";
  return ss.str();
}

/// Convert set<int> to a string
template <>
inline std::string asString<std::set<int> >(const std::set<int> &t) {
  std::stringstream ss;
  ss << "std::set(";
  for (std::set<int>::const_iterator i=t.begin(); i!=t.end(); i++)
    ss << " " << *i;
  ss << " )";
  return ss.str();
}

/// Convert to a nice byte representation and add units
template<typename T>
inline std::string toXBytes(T b) {
  static const char *B[]={" B","KB","MB","GB","TB","PB"};
  static const unsigned n = sizeof(B)/sizeof(char*);
  static const T upper_bound =  1<<14;
  unsigned i=0;
  for (; i<(n-1) && upper_bound < b && std::numeric_limits<T>::is_integer; ++i)
    b = b>>10;
#ifdef DGM_STRING_VERBOSE
    std::cout << "upper_bound " << upper_bound << std::endl;
    std::cout << "n = " << n << std::endl;
    std::cout << "i = " << i << std::endl;
    std::cout << "b = " << b << std::endl;
#endif
  assert(i<n);
  std::string F = asString(b)+' '+B[i];
  return F;
}

/// Scan for a left curly bracket
inline int scan_lb(std::istream &in ) {
  std::string token;
  if (!(in >> token)) return 1;
  if ( token != "{" ) return 2;
  return 0;
}

/// Scan for a right curly bracket
inline int scan_rb(std::istream &in ) {
  std::string token;
  while (token != "}" ) if (!(in >> token)) return 1;
  return 0;
}

/// Read a block of characters between curly brackets
/** \note This assumes that the first '{' is already gone so it
    adds it back to the output buffer before returning. */
inline std::string read_block( std::istream &in ) {
  std::string buffer;
  char c;
  unsigned nb(1);
  while ( in.good() ) {
    c = (char)in.get();
    if (in.good()) {
      if (c=='{') nb++;
      if (c=='}') nb--;
      buffer += c;
      if (nb==0) {
        in.unget();
        break;
      }
    }
  }
  buffer = "{ " + buffer;
  return buffer;
}

/// Generates a line of characters in an output stream
inline void line(std::ostream &out, const char c='=', const int w=80) {
  char prev = out.fill(c);
  out.width(w-1);
  out << c << std::endl;
  out.fill(prev);
}

/// Generates a header in an output stream
inline void header(std::ostream &out, const std::string head,
                  const char c='=', const int w=80) {
  line(out,c,w);
  out << head << std::endl;
  line(out,c,w);
}

//@}

} // namespace DGM

#endif  // DGM_STRING_HPP
