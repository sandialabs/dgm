/** \file CaseInsensitiveString.hpp
    \brief A case insensitive string
    \author K. Noel Belcourt
*/

#ifndef CaseInsensitiveString_hpp
#define CaseInsensitiveString_hpp

#include <string>

// DGM includes
#include "Config.hpp"

namespace DGM {

struct ci_char_traits : public std::char_traits<char>
{
  static bool eq(char, char);

  static bool ne(char, char);

  static bool lt(char, char);

  static int compare(const char *, const char *, size_t);

  static const char *find(const char *, int, char);
};

int compare(const char *, const char *);

int compare(const char, const char *);

int compare(const char *, const char);

typedef std::basic_string<char, ci_char_traits> case_insensitive_string;

// interoperability with std::string
bool operator ==(const std::string&, const case_insensitive_string&);
bool operator ==(const case_insensitive_string&, const std::string&);

bool operator ==(const char*, const case_insensitive_string&);
bool operator ==(const case_insensitive_string&, const char*);

}  // namespace DGM

#endif
