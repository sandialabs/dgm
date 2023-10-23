/** \file CaseInsensitiveString.cpp
    \brief A case insensitive string
    \author K. Noel Belcourt
*/

#include <algorithm>
#include <cctype>
#include <cstring>
#include <string>

#include "CaseInsensitiveString.hpp"

using std::min;
using std::string;
using std::strlen;
using std::toupper;

namespace DGM {

bool ci_char_traits::eq(char c1, char c2)
  { int t = toupper(c1); return t == toupper(c2); }

bool ci_char_traits::ne(char c1, char c2)
  { int t = toupper(c1); return t != toupper(c2); }

bool ci_char_traits::lt(char c1, char c2)
  { int t = toupper(c1); return t < toupper(c2); }

int ci_char_traits::compare(const char *s1, const char *s2, size_t n) {
  for (unsigned int i=0; i<n; ++i) {
    if (!eq(s1[i],s2[i])) return 0;
  }
  return 1;
}

const char *ci_char_traits::find(const char *s, int n, char t) {
  int a = toupper(t);
  while (n-- > 0 && toupper(*s) != a) {
      ++s;
  }
  return s;
}

int compare(const char *s1, const char *s2) {
  size_t l1 = strlen(s1);
  size_t l2 = strlen(s2);
  if (l1 != l2) return 0;
  return ci_char_traits::compare(s1, s2, l1);
}

int compare(const char c, const char *s) {
  return ci_char_traits::eq(c, *s);
}

int compare(const char *s, const char c) {
  return ci_char_traits::eq(*s, c);
}

// interoperability with std::string
bool operator ==(const string &s, const case_insensitive_string &ci_string) {
  const char *c = s.c_str();
  return static_cast<bool>(compare(ci_string.c_str(), c));
}

bool operator ==(const case_insensitive_string &ci_string, const string &s) {
  const char *c = s.c_str();
  return static_cast<bool>(compare(ci_string.c_str(), c));
}

// interoperability with const char *
bool operator ==(const char* c, const case_insensitive_string &ci_string) {
  return static_cast<bool>(compare(ci_string.c_str(), c));
}

bool operator ==(const case_insensitive_string &ci_string, const char* c) {
  return static_cast<bool>(compare(ci_string.c_str(), c));
}

}  // namespace DGM
