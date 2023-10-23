#ifndef REO_INFO_HPP
#define REO_INFO_HPP

/** \file ReoInfo.hpp
    \brief Runtime information for Reo applications
    \author S. Collis and A. Gerstenberger
*/

// system includes
#include <iostream>
#include <fstream>

// DGM includes
#include "Info.hpp"

namespace Reo {

/// Make a self aware Reo class
/** All compile-time defines should be registered here

*/
class Info : public DGM::Info {

public:

  Info() {}

  virtual ~Info() {}

  virtual void name(std::ostream &out) const;

  virtual string code() const { return "Reo"; }

  virtual string date() const;

  virtual string time() const;

  virtual string version() const { return "1.0"; }

  virtual void defines(std::ostream &out) {
    using std::endl;
#ifdef REO_USE_GETSIDEMAPS
    db["REO_USE_GETSIDEMAPS"] = MACROVALUE(REO_USE_GETSIDEMAPS);
#endif
#ifdef REO_CONSISTENT_BC
    db["REO_CONSISTENT_BC"] = MACROVALUE(REO_CONSISTENT_BC);
#endif
#ifdef REO_BURGERS_AVG_FLUX
    db["REO_BURGERS_AVG_FLUX"] = MACROVALUE(REO_BURGERS_AVG_FLUX);
#endif
    DGM::Info::defines(out);
  }

};

} // namespace Reo

#endif // REO_INFO_HPP
