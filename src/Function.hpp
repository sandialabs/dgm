#ifndef DGM_FUNCTION_HPP
#define DGM_FUNCTION_HPP

/** \file Function.hpp
    \brief Simple function class used by DGM::TimeInt
    \author Scott Collis
*/

namespace DGM {

/// Simple function class used by TimeInt
class Function {
public:
  Scalar dt;           ///< time step
  Scalar t;            ///< time
  Scalar value;        ///< value
  Ordinal lstep;       ///< local step index
  /// Constructor
  Function( const Scalar t_, const Scalar dt_ ) : dt(dt_), t(t_)  {
    value = 0;
    lstep = 0;
  }
  /// Destructor
  virtual ~Function() {};
  /// Evaluation interface
  virtual Scalar evaluate( const Ordinal, const Ordinal ) = 0;
};

} // namespace DGM

#endif
