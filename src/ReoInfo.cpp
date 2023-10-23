/** \file ReoInfo.cpp
    \brief Runtime information for Reo applications
    \author S. Collis and A. Gerstenberger
*/

// DGM includes
#include "ReoInfo.hpp"

// system includes
#include <string>
#include <iostream>

void Reo::Info::name(std::ostream &out) const {
  out << "                          _____               \n"   
         "                         |  __ \\             \n"
         "                         | |__) |___  ___     \n"
         "                         |  _  // _ \\/ _ \\  \n"
         "                         | | \\ \\  __/ (_) | \n"
         "                         |_|  \\_\\___|\\___/   " << endl;
  std::string date(__DATE__);
  std::string time(__TIME__);
  out << "                         Created on " << date << " at " 
      << time << std::endl;
}

std::string Reo::Info::date() const {
  std::string date(__DATE__);
  return date;
}

std::string Reo::Info::time() const {
  std::string time(__TIME__);
  return time;
}

