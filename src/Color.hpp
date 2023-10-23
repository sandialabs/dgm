#ifndef DGM_COLOR_HPP
#define DGM_COLOR_HPP

/**  \file Color.hpp
 *   \brief Adds simple methods for controlling ANSI color output
 *   \author Scott Collis
 */

#include<iostream>
#include<cstdlib>

namespace DGM {

/// Determines from environment whether to use color output
class UseColor {
  bool value;
public:
  UseColor() : value(false) {
    const char *tmp = getenv("DGM_COLOR_OUTPUT");
    if (tmp != NULL) value = true;
  }
  bool get() const { return value; }
};

/// Simple stream modifier to change ANSI colors
class Color {
  static UseColor useColor;
public:
  enum Code {
    DEFAULT = 0,
    BOLD = 1,
    BLACK = 30,
    RED,
    GREEN, 
    YELLOW, 
    BLUE,
    MAGENTA,
    CYAN,
    WHITE
  };
private:
  Code code;
public:
  Color(Code pCode=DEFAULT) : code(pCode) { }
  friend std::ostream & operator << (std::ostream& os, const Color mod) {
  if (useColor.get())
    return os << "\033[" << mod.code << "m";
  else
    return os << "";
  }
  Code get() const { return code; }
  void set(const Code newCode) { code = newCode; }
};

} // namespace DGM

#endif // DGM_COLOR_HPP

