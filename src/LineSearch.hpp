#ifndef DGM_LINESEARCH_HPP
#define DGM_LINESEARCH_HPP

/** \file LineSearch.hpp
    \brief DGM line search class declaration
    \author Scott Collis
*/

// DGM includes
#include "Comm.hpp"

namespace DGM {

  /// Basic DGM functional interface
  /** This class is used to provide a simple, templated functor class
      for DGM optimizers. */
  template <class Scalar>
  class Eval {
    int count_;
  public:
    /// Constructor
    Eval() : count_() {}
    /// Destructor
    virtual ~Eval() {}
    /// reset the count
    inline void reset() { count_=0; }
    /// set the count
    inline void count(const int count) { count_ = count; }
    /// get the count
    inline int count() const { return count_; }
    /// increment the count
    inline void increment() { count_++; }
    /// Functor interface that derived class must provide
    virtual Scalar operator()(const Scalar &x) = 0;
  };

  /// Base class for Globalization
  /** This could be a line search or a trust region and should, one day
      provide a nontrivial interface. For now, make it a placeholder to
      clarify the design. */
  template <class Scalar>
  class Globalizer {
  public:
    virtual ~Globalizer() {}
  };

  /// DGM line search interface
  /** Currently this implements a bracket/Brents method.  It would be easy
      to turn this into a base class and derive specific line searches but
      since there is only one right now, no need to bother.

      We have two implementations of Brent's line search here - one
      that existed before mid-February 2016, and one that Drew Kouri
      modified in mid-February.   The default is the original DGM version.
  */
  class LineSearch : public Globalizer<Scalar> {
  public:
  
    /// Verbosity level for line search
    enum OutputLevel { SILENT_OUTPUT, QUIET_OUTPUT, NORMAL_OUTPUT,
      VERBOSE_OUTPUT, DEBUG_OUTPUT, TEST_OUTPUT };
    
  private:
  
    const DGM::Comm::Ptr comm;  ///< local version of communicator

    /// Output verbosity level
    OutputLevel outputLevel;

    /// DGM evaluator
    Eval<Scalar> &eval;

    /// True uses the original DGM version of Brents (default)
    bool useOriginalBrents;

  public:

    /// Constructor
    LineSearch(Eval<Scalar> &, const DGM::Comm::Ptr = DGM::Comm::World,
               const OutputLevel outputLevel_ = SILENT_OUTPUT);

    /// Destructor
    virtual ~LineSearch() { };

    /// General purpose bracketing routine
    Ordinal bracket(Scalar &xa, Scalar &xb, Scalar &xc,
                    Scalar &fa, Scalar &fb, Scalar &fc);

    /// Line minimization using Brent's quadratic interpolation
    Ordinal brents_fmin(Scalar &xa, Scalar &xb, Scalar &xc,
                        Scalar &fa, Scalar &fb, Scalar &fc,
                        Scalar tol, Ordinal itmax);

    /// change the version of Brents
    void setUseOriginalBrents(bool a) { useOriginalBrents = a; }

    /// get the output level
    OutputLevel getOutputLevel() const { return outputLevel; }

    /// set the output level
    void setOutputLevel(const OutputLevel outputLevel_) {
      outputLevel = outputLevel_;
    }

  private:

    /// Line minimization using Brent's quadratic interpolation
    Ordinal brents_fmin_new(Scalar &xa, Scalar &xb, Scalar &xc,
                            Scalar &fa, Scalar &fb, Scalar &fc,
                            Scalar tol, Ordinal itmax);

    /// Line minimization using Brent's quadratic interpolation
    Ordinal brents_fmin_old(Scalar &xa, Scalar &xb, Scalar &xc,
                            Scalar &fa, Scalar &fb, Scalar &fc,
                            Scalar tol, Ordinal itmax);
  };

} // end DGM namespace

#endif  // DGM_LINESEARCH_HPP
