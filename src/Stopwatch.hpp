#ifndef CMC_STOPWATCH_HPP
#define CMC_STOPWATCH_HPP

/** \file Stopwatch.hpp
    \brief CMC Stopwatch class declaration
    \author Scott Collis
    \copyright (c)2003 Rice University
    \copyright (c)2014 Sandia National Laboratories
*/

// system includes
#include <cstdlib>
#ifndef VCC
#include <sys/time.h>
#else
#include <time.h>
#endif
#include <iostream>

namespace CMC {

  /// Use the hi-resolution timer (this gives wall time, not CPU time)
  inline double seconds() {
#ifndef VCC
    struct timeval tp;
    struct timezone tzp;
    if ( gettimeofday(&tp,&tzp) ) {
      std::cerr << "ERROR: CMC::seconds()" << std::endl;
      std::exit(EXIT_FAILURE);
    }
    return ((double) tp.tv_sec + .000001 * (double) tp.tv_usec);
#else
    return 0;
#endif
  }

  /// Simple code timer
  /** Simple Stopwatch object:
      void    start()     : start timing
      double  stop()      : stop timing
      void    reset()     : set elapsed time to 0.0
      double  read()      : read elapsed time (in seconds)
   */
  class Stopwatch {
  private:
    mutable int running;        ///< tells whether the Stopwatch is running
    mutable double last_time;   ///< stores the last time
    mutable double total;       ///< stores the total time
    long starts;                ///< Number of times start() is called.
  public:
    /// build a Stopwatch
    Stopwatch(const double baseline=0.0) : running(0), last_time(0.0),
    total(baseline), starts(0) {}
    /// destructor
    virtual ~Stopwatch() {}
    /// set elaped time to zero
    void reset(const double baseline=0.0) {
      running = 0; last_time = 0.0; total=baseline; starts=0;
    }
    /// start timing
    void start() {++starts; if(!running){last_time = seconds(); running = 1;}}
    /// stop timing
    double stop() const {
      if (running) {
        total += seconds() - last_time;
        running = 0;
      }
      return total;
    }
    /// read elapsed time in seconds
    double read() const {
      if (running) {
        total += seconds() - last_time;
        last_time = seconds();
      }
      return total;
    }
    /// read the number of times start() was called.
    long count() const {return starts;}
    /// restart the timer
    double restart() { double total = stop(); reset(); start(); return total; }
  };

} // end namespace CMC

#endif
