#ifndef REO_BURGERSIC_HPP
#define REO_BURGERSIC_HPP

/** \file BurgersIC.hpp
    \brief This is a collection of Classes for Burgers Initial conditions
    \author Scott Collis
*/

namespace Reo {

/// Defines an initial condition that produces a shock
class Burgers::ShockIC {
 public:
  Scalar eval(const Point &P) {
    if (P.x<= 1.0)
      return 0;
    else if (P.x > 1.0 && P.x <= 3.0)
      return cos(pi*(P.x-1.0)*(P.x-1.0)/2.0)*(1.0-cos(pi*(P.x-1.0)));
    else if (P.x > 3.0 && P.x <= 4.0)
      return 0.0;
    else {
      DGM::Comm::World->cerr()
        <<"Shock::eval(const Point&) Point exceeds the limits!"<<endl;
      DGM::Comm::World->exit(DGM::FAILURE);
    }
    return 0;
  }
};

/// Cockburn's Shock initial condition
/** Test case(2) from "Discontinuous Methods For Convection Dominated Flows"
    by Bernardo Cockburn */
class Burgers::CockburnShockIC {
 public:
  Scalar eval(const Point &P) { return (0.25+0.5*sin(pi*(2.0*P.x-1.0))); }
};

/// Step function initial condition
class Burgers::StepIC {
 public:
  Scalar eval(const Point &P) {
    if (P.x >= 0.0 && P.x < 0.5) return 1.0;
    else return 0.0;
  }
};

} // namespace Reo

#endif  // REO_BURGERSIC_HPP
