/** \file Info.cpp
    \brief Runtime information for DGM library and applications
    \author Scott Collis
*/

// boost includes
#include "boost/numeric/conversion/cast.hpp"
using boost::numeric_cast;

// DGM includes
#include "Info.hpp"

void DGM::Info::name(std::ostream &out) const {
  out << "                         ____  ________  ___ \n"
         "                        / __ \\/ ____/  |/  / \n"
         "                       / / / / / __/ /|_/ /  \n"
         "                      / /_/ / /_/ / /  / /   \n"
         "                     /_____/\\____/_/  /_/      " << endl;
  std::string date(__DATE__);
  std::string time(__TIME__);
  out << "                     Created on " << date << " at "
      << time << std::endl;
}

std::string DGM::Info::date() const {
  std::string date(__DATE__);
  return date;
}

std::string DGM::Info::time() const {
  std::string time(__TIME__);
  return time;
}

std::string DGM::Info::compiler() const {
#ifndef __VERSION__
  std::string version("unknown version");
#else
  std::string version(__VERSION__);
#endif

#if defined(__clang__)
  std::string compiler("CLANG: " + version);
#elif defined(__ICC) || defined(__INTEL_COMPILER)
  std::string compiler("ICC: " + version);
#elif defined(__GNUC__) || defined(__GNUG__)
  std::string compiler("GCC: " + version);
#elif defined(__HP_cc) || defined(__HP_aCC)
  std::string compiler("HP C/C++: " + version);
#elif defined(__IBMC__) || defined(__IBMCPP__)
  std::string compiler("IBM XL C/C++: " + version);
#elif defined(_MSC_VER)
  std::string compiler("MS Visual Studio: " + version);
#elif defined(__PGI)
  std::string compiler("PGI: " + version);
#elif defined(__SUNPRO_C) || defined(__SUNPRO_CC)
  std::string compiler("Solaris: " + version);
#else
  std::string compiler("Unknown compiler:  " + version);
#endif
  return compiler;
}

std::string DGM::Info::hostname() const {
  char hostname[256];
  gethostname(hostname, sizeof(hostname));
  std::string retval(hostname);
  return retval;
}

std::string DGM::Info::system() const {
  const char *tmp = getenv("SYSTEM");
  std::string system = "Undefined";
  if (tmp != NULL) system = tmp;
  return system;
} 

void DGM::Info::banner(std::ostream &out) const {
  using std::setfill;
  using std::setw;
  const unsigned i(2);
  const unsigned w(64);
  out << setfill(' ') << setw(i-1) << "\0";
  out << setfill('*') << setw(w) << "\n" << setfill(' ');
  out
    << setw(i) << "*"
    << "  This application uses the DGM library " << version() 
    << setw(23-numeric_cast<int>(version().size())) << "*\n"
    << setw(i) << "*"
    << "                                                             *\n"
    << setw(i) << "*"
    << "  Copyright (c)2014 Sandia Corporation                       *\n" 
    << setw(i) << "*"
    << "            (c)2003 Rice University                          *\n"
    << setw(i) << "*"
    << "                                                             *\n"
    << setw(i) << "*" 
    << "  Under the terms of Contract DE-AC04-94AL85000 with Sandia  *\n"
    << setw(i) << "*"
    << "  Corporation, the U.S. Government retains certain rights    *\n"
    << setw(i) << "*"
    << "  in this software.                                          *\n"
    << setw(i) << "*"
    << "                                                             *\n"
    << setw(i) << "*"
    << "  See License.txt in the DGM distribution directory for      *\n"
    << setw(i) << "*"
    << "  additional details.                                        *\n"
    << setw(i) << "*"
    << "                                                             *\n";
  string date(__DATE__);
  string time(__TIME__);
  string revision("__REVISION__");
  out
    << setw(i) << "*"
    << "  DGM Library created on " << date << " at " << time << setw(15) 
    << "*\n";
  // SVN uses short revision numbers while Git are 40 long
  const int REV_LEN = numeric_cast<int>(revision.size());
  const int GIT_LEN = 40;
  if (REV_LEN < GIT_LEN) {
    out
      << setw(i) << "*"
      << "              based on revision " << setw(REV_LEN) << std::left 
      << revision << setw(31-REV_LEN) << setfill(' ') << std::right << "*\n";
  } else {
    out
      << setw(i) << "*"
      << "  based on revision " << std::left << revision 
      << std::right << " *\n";
  }
  out << setfill(' ') << setw(i-1) << "\0";
  out << setfill('*') << setw(w) << "\n" << setfill(' ');
}
