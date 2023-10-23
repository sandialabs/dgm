#ifndef DGM_WAVELET_HPP
#define DGM_WAVELET_HPP

/** \file Wavelet.hpp
    \brief DGM wavelet class declarations
    \author Scott Collis
*/

// system includes
#include <limits>

// JSON includes
#ifdef DGM_USE_JSON
#include "json/json.h"
#endif

// DGM includes
#include "Types.hpp"
#include "String.hpp"
#include "Element.hpp"
#include "Coordinates.hpp"
#include "Field.hpp"
#include "vField.hpp"

namespace DGM {

//============================================================================
//                              W a v e l e t
//============================================================================

  /// Base class for wavelets
  class Wavelet {
  protected:
    string name_;  ///< name of this wavelet
    Scalar amp;    ///< amplitude
    Scalar fp;     ///< peak frequency
    Scalar t0;     ///< delay time (t0 > 0)
    Scalar toff;   ///< cutoff time (toff > t0)
    int verb;      ///< verbosity level
  public:
    /// Constructor
    Wavelet(const Scalar t_0, const Scalar f_p) :
      amp(1.0), fp(f_p), t0(t_0), toff(t0+2.5/fp), verb(0) { }
    /// JSON Constructor
    Wavelet(Json::Value &root) :
      name_(root.set("name","Wavelet").asString()),
      amp(root.set("amp",1.0).asDouble()),
      fp(root.set("fp",1.0).asDouble()),
      t0(root.set("t0",1.5/fp).asDouble()),
      toff(root.set("toff",t0+2.5/fp).asDouble()),
      verb(root.set("Verbosity",0).asInt()) { }
    /// destructor
    virtual ~Wavelet() { }
    typedef DGM::Shared<Wavelet>::Ptr Ptr;
    /// Evaluate the wavelet (or its derivative) at a given time
    virtual Scalar operator() (const Scalar t, const int der=0) const = 0;
    /// Is the wavelet active
    inline bool active(const Scalar t) const {
      if (t<toff)
        return true;
      else
        return false;
    }
    string name() const { return name_; }
    Scalar amplitude() const { return amp; }
    Scalar frequency() const { return fp; }
    Scalar startTime() const { return t0; }
    Scalar cuttoffTime() const { return toff; }
    int verbosity() const { return verb; }
  protected:
    static Scalar Exp(const Scalar arg) {
      return ( arg > -34.0 ? exp(arg) : 1.0e-15 );
    }
  };

  /// Zero wavelet
  class NoWavelet : public Wavelet {
  public:
    NoWavelet(Json::Value &root) : Wavelet(root) {
      root.removeMember("amp");
      root.removeMember("fp");
      root.removeMember("t0");
      root.removeMember("toff");
      amp  =  0.0;
      fp   =  0.0;
      t0   =  numeric_limits<Scalar>::max();
      toff = -numeric_limits<Scalar>::max();
    }
    virtual Scalar operator()(const Scalar t, const int der=0) const {
      return 0.0;
    }
  };

  /// Normalized Gaussian Wavelet class
  /** This is the wavelet that Dave Aldridge favors. */
  class NormalizedGaussian : public Wavelet {
  public:
    /// Constructor
    NormalizedGaussian(const Scalar t_0, const Scalar f_p) :
      Wavelet(t_0,f_p) { }
    /// Construct from JSON
    NormalizedGaussian(Json::Value &root) : Wavelet(root) {
      root.set("Type","NormalizedGaussian");
      if (verb>1) DGM::Comm::World->cout()
                    << "  NormalizedGaussian wavelet with t0 = " << t0
                    << ", fp = " << fp <<endl;
    }
    virtual ~NormalizedGaussian() { }
    /// Operator interface
    Scalar operator() (const Scalar t, const int der=0) const {
      if (!active(t)) return zero;
      Scalar T = pow(pi*fp*(t-t0),2);
      if (der==0) return amp*Exp(-T);
      if (der==1) return -amp*two*pow(pi*fp,2)*(t-t0)*Exp(-T);
      DGM::Comm::World->error("NormalizedGaussian illegal derivative: "+
                              asString(der));
      return zero;
    }
  };

  /// Ricker Wavelet class
  class Ricker : public Wavelet {
    Scalar fact;  ///< Time multiplicative factor
  public:
    /// Constructor
    Ricker(const Scalar t_0, const Scalar f_p) : Wavelet(t_0,f_p) {
      fact = -two*fp*fp*pi*pi;
    }
    /// Construct from JSON
    Ricker(Json::Value &root) : Wavelet(root) {
      root.set("Type","Ricker");
      fact = -two*fp*fp*pi*pi;
      if (verb>1) DGM::Comm::World->cout() << "  Ricker wavelet with t0 = "
                                           << t0 << ", fp = " << fp <<endl;
    }
    virtual ~Ricker() { }
    /// Operator interface
    Scalar operator() (const Scalar t, const int der=0) const {
      if (!active(t)) return zero;
      Scalar T = pow(pi*fp*(t-t0),2);
      if (der==0)
        return amp*(one-two*T)*Exp(-T);               // Ricker
      else if (der==1)
        return amp*fact*Exp(-T)*(-3.0+two*T)*(t-t0);  // derivative of Ricker
      else
        DGM::Comm::World->error("Ricker illegal derivative: "+asString(der));
      return zero;
    }
  };

  /// Integral of Ricker Wavelet class
  class iRicker : public Wavelet {
  public:
    /// Constructor
    iRicker(const Scalar t_0, const Scalar f_p) : Wavelet(t_0,f_p) { }
    /// Constructor from JSON
    iRicker(Json::Value &root) : Wavelet(root) {
      root.set("Type","iRicker");
    }
    virtual ~iRicker() { }
    /// Operator interface
    Scalar operator() (const Scalar t, const int der=0) const {
      if (!active(t)) return zero;
      Scalar T = pow(pi*fp*(t-t0),2);
      if (der==0)
        return amp*(t-t0)*Exp(-T);       // integral of Ricker
      else if (der==1) {
        const Scalar result = amp*(one-two*T)*Exp(-T);  // Ricker
        return result;
      } else
        DGM::Comm::World->error("iRicker illegal derivative: "+
                                asString(der));
      return zero;
    }
  };

  /// Double integral of Ricker Wavelet class
  class i2Ricker : public Wavelet {
    const Scalar ipifp2;
  public:
    /// Constructor
    i2Ricker(const Scalar t_0, const Scalar f_p) :
      Wavelet(t_0,f_p), ipifp2(one/pow(pi*fp,2)) { }
    /// Constructor from JSON
    i2Ricker(Json::Value &root) : Wavelet(root), ipifp2(one/pow(pi*fp,2)) {
      root.set("Type","i2Ricker");
    }
    virtual ~i2Ricker() { }
    /// Operator interface
    Scalar operator() (const Scalar t, const int der=0) const {
      if (!active(t)) return zero;
      Scalar T = pow(pi*fp*(t-t0),2);
      if (der==0)
        return -amp*pt5*Exp(-T)*ipifp2;  // twice integrated = (-Gaussian)
      if (der==1)
        return amp*(t-t0)*Exp(-T);       // integral of Ricker
      else
        DGM::Comm::World->error("i2Ricker illegal derivative: "+
                                asString(der));
      return zero;
    }
  };

  /// Derivative of Ricker Wavelet class
  class dRicker : public Wavelet {
    Scalar fact;  ///< Time multiplicative factor
  public:
    /// Constructor
    dRicker(const Scalar t_0, const Scalar f_p) : Wavelet(t_0,f_p) {
      fact = -two*fp*fp*pi*pi;
    }
    /// Constructor from JSON
    dRicker(Json::Value &root) : Wavelet(root) {
      root.set("Type","dRicker");
      fact = -two*fp*fp*pi*pi;
    }
    /// Operator interface
    Scalar operator() (const Scalar t, const int der=0) const {
      if (!active(t)) return zero;
      Scalar T = pow(pi*fp*(t-t0),2);
      if (der==0)
        return amp*fact*Exp(-T)*(-3.0+two*T)*(t-t0);
      else
        DGM::Comm::World->error("dRicker illegal derivative: "+
                                asString(der));
      return zero;
    }
  };

  /// Berlage Wavelet class
  class Berlage : public Wavelet {
    int n;          ///< Determines the smoothness at t=0
    Scalar h;       ///<
    Scalar theta;   ///< Set the shape
  public:
    /// Constructor
    Berlage(const Scalar t_0, const Scalar f_p,
            const int n_=3, const Scalar h_=1.0,
            const Scalar theta_=-pi*pt5) :
      Wavelet(t_0,f_p), n(n_), h(h_), theta(theta_) { }
    Berlage(Json::Value &root) : Wavelet(root),
        n(root.set("n",3).asInt()),
        h(root.set("h",1.0).asDouble()),
        theta(root.set("theta",-pi*pt5).asDouble()) {
      root.set("Type","Berlage");
    }
    virtual ~Berlage() { }
    /// Operator interface
    Scalar operator() (const Scalar t, const int der=0) const {
      Scalar Ht = t > zero ? one : zero;
      Scalar omegat = two*pi*fp*t;
      if (der==0)
        return amp*Ht*pow(omegat,n)*Exp(-h*omegat)*cos(omegat+theta);
      else
        DGM::Comm::World->error("Berlage illegal derivative: "+asString(der));
      return zero;
    }
  };

  /// Derivative of Berlage Wavelet class (need to complete)
  class dBerlage : public Wavelet {
    int n;          ///< Determines the smoothness at t=0
    Scalar h;       ///< Berlage parameter (need more detail here)
    Scalar theta;   ///< Set the shape
  public:
    /// Constructor
    dBerlage(const Scalar t_0, const Scalar f_p,
             const int n_=3, const Scalar h_=1.0,
             const Scalar theta_=-pi*pt5) :
      Wavelet(t_0,f_p), n(n_), h(h_), theta(theta_) {
      DGM::Comm::World->error("dBerlage not yet implemented");
    }
    dBerlage(Json::Value &root) : Wavelet(root),
        n(root.set("n",3).asInt()),
        h(root.set("h",1.0).asDouble()),
        theta(root.set("theta",-pi*pt5).asDouble()) {
      root.set("Type","dBerlage");
    }
    virtual ~dBerlage() { }
    /// Operator interface
    Scalar operator() (const Scalar t, const int der=0) const {
      DGM::Comm::World->error("dBerlage is not implemented: "+asString(der));
      return zero;
    }
  };

  /// RampedSine Wavelet class
  class RampedSine : public Wavelet {
  public:
    /// Constructor
    RampedSine(const Scalar t_0, const Scalar f_p) : Wavelet(t_0,f_p) {}
    /// Construct from JSON
    RampedSine(Json::Value &root) : Wavelet(root) {
      root.set("Type","RampedSine");
      if (verb>1) DGM::Comm::World->cout()
                    << "  RampedSine wavelet with t0 = "
                    << t0 << ", fp = " << fp <<endl;
    }
    virtual ~RampedSine() { }
    /// Operator interface
    Scalar operator() (const Scalar t, const int der=0) const {
      if (!active(t)) return zero;
      if (der==0)
        if ( t <= t0 )
          return zero;
        else if ( t > t0+1.0/fp )
          return amp*sin(two*pi*fp*(t-t0));
        else
          return amp*sin(two*pi*fp*(t-t0))*pt5*(one-cos(pi*fp*(t-t0)));
      else if (der==1)
        if ( t <= t0 )
          return zero;
        else if ( t > t0+1.0/fp )
          return amp*two*pi*fp*cos(two*pi*fp*(t-t0));
        else
          return amp*pi*fp*cos(two*pi*fp*(t-t0))*(one-cos(pi*fp*(t-t0)))
               + amp*sin(two*pi*fp*(t-t0))*pt5*pi*fp*sin(pi*fp*(t-t0));
      else
        DGM::Comm::World->error("RampedSine illegal derivative:"+
                                asString(der));
      return zero;
    }
  };

  /// Chapeau (hat function) Wavelet class
  /** This is the classic Chapeau or hat function.
   *  \verbatim
   *         Chapeau function               derivative
   *   _________ .                 ______._____
   *    ^       / \                 ^    |     |
   *    |      /   \                |    |     |
   *   amp    /     \             amp*fp |     |
   *    |    /       \              |    |     |
   *    v   /         \             v    |     |
   *   ____/     .     \____       ______|     .      ____
   *  |        ->|1/fp |<-        |            |     |
   *  |<-  t0  ->|                |<-   t0   ->|     |
   *                                           |     |
   *                                           |     |
   *                                           |     |
   *                                           |_____.
   *                                         ->|1/fp |<-
   *
   * If fp = 1/dt where dt is the time step size, then one has a
   *  sampled Delta impluse function.
   * \endverbatim
   */
  class Chapeau : public Wavelet {
  public:
    /// Constructor
    Chapeau(const Scalar t_0, const Scalar f_p) :
      Wavelet(t_0,f_p) { }
    /// Construct from JSON
    Chapeau(Json::Value &root) : Wavelet(root) {
      root.set("Type","Chapeau");
      if (verb>1) DGM::Comm::World->cout()
                    << "  Chapeau wavelet with t0 = " << t0
                    << ", fp = " << fp <<endl;
    }
    virtual ~Chapeau() { }
    /// Operator interface
    Scalar operator() (const Scalar t, const int der=0) const {
      if (!active(t)) return zero;
      const Scalar dt = 1.0/fp;
      if (der==0) {
        const Scalar s = abs(t-t0)/dt;
        if (s <= 1.0) return amp*(1.0-s);
        else return zero;
      } else if (der==1) {
        const Scalar s = (t-t0)/dt;
        const Scalar reltol = 1.0e-12;
        if ((s < -1.0) || ( s > 1.0) || (abs(s) < reltol) ) return zero;
        else if (s < 0.0) return amp*fp;
        else return -amp*fp;
      } else {
        DGM::Comm::World->error("Chapeau illegal derivative: "+
                                asString(der));
      }
      return zero;
    }
  };

}  // namespace DGM

#endif // DGM_WAVELET_HPP
