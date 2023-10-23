/** \file ArgList.cpp
    \brief Argument list class implementation
    \author Scott Collis
*/

#include <iostream>

// DGM includes
#include "ArgList.hpp"

namespace DGM {
  using std::cout;
  using std::endl;
  using std::list;
  using std::string;
  
  /// Construct an empty list of arguments
  ArgList::ArgList() {
  }

  /// Construct a list of arguments stored as strings
  ArgList::ArgList( int *argc, char ***argv ) {
    make_argument_list( argc, argv, *this );
  }

  /// Print out an ArgList
  void ArgList::print() const { print(*this); }

  /// Make a list of arguments
  void ArgList::make_argument_list( int *argc, char ***argv,
                                    list<string> &args ) {
    // load up list of arguments
    for (int i = 0; i < *argc; i++) {
      args.push_back( (*argv)[i] );
    }
    // cout << "args.size() = " << args.size() << endl;
  }

  /// Print an list of arguments
  void ArgList::print( const std::list< std::string > &args ) {
    for (list<string>::const_iterator a=args.begin(); a!=args.end();
          a++) {
      cout << *a << " ";
    }
    cout << endl;
  }

} // namespace DGM
