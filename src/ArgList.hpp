#ifndef DGM_ARGLIST_HPP
#define DGM_ARGLIST_HPP

/** \file ArgList.hpp
    \brief Argument list class declaration
    \author Scott Collis
*/

// system includes
#include <list>
#include <string>

// DGM includes
#include "Config.hpp"

namespace DGM {

  /// Simple data structure to hold a list of arguments as strings
  /** Currently a thin wrapper around a list<string> data-structure but use
      this so that it would be easy to enhance in the future. */
  class ArgList : public std::list<std::string> {
  public:
    typedef std::list<std::string>::iterator iterator;
    typedef std::list<std::string>::const_iterator const_iterator;
    ArgList();
    ArgList( int *argc, char ***argv );
    void print() const;
  private:
    static void make_argument_list( int *argc, char ***argv,
                                    std::list<std::string> &args );
    static void print( const std::list<std::string> &args );
  };

} // namespace DGM

#endif
