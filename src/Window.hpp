#ifndef DGM_WINDOW_HPP
#define DGM_WINDOW_HPP

/** \file Window.hpp
 *  \brief Classes for window functions
 *  \author Scott Collis
*/

// system includes
#include <iostream>

// Json includes
#include "json/value.h"
#include "json/reader.h"
#include "json/writer.h"

// DGM includes
#include "Config.hpp"
#include "Types.hpp"
#include "Constants.hpp"

namespace DGM {

/// Defines a base Window class
class Window {
protected:
  Scalar tbeg0;
  Scalar tbeg1;
  Scalar tend0;
  Scalar tend1;
  Scalar amp;
public:
  /// Shared pointer to Window
  typedef DGM::Shared<Window>::Ptr Ptr;
  /// default constructor
  Window() : tbeg0(0), tbeg1(0), tend0(0), tend1(0), amp(1.0) {}
  /// virtual destructor
  virtual ~Window() {}
  /// Json constructor
  Window(Json::Value &reg) :
    tbeg0(reg.set("Begin time amplitude zero",0.0).asDouble()),
    tbeg1(reg.set("Begin time amplitude one",0.0).asDouble()),
    tend0(reg.set("End time amplitude zero",0.0).asDouble()),
    tend1(reg.set("End time amplitude one",0.0).asDouble()),
    amp(reg.set("Amplitude",1.0).asDouble()) {}
  /// Operator interface
  virtual Scalar operator()(const Scalar time) const = 0;
  /// Factory for windows
  inline static void factory(Json::Value &root, DGM::Window::Ptr &window);
};

/// Hyperbolic tangent window
class TanhWindow : public Window {
  Scalar strength;
public:
  TanhWindow() : Window() {}
  virtual ~TanhWindow() {}
  TanhWindow(Json::Value &reg) : Window(reg),
      strength(reg.set("Strength",3.0).asDouble()) {}
  virtual inline Scalar operator()(const Scalar time) const {
    return amp*Tanh(time);
  }
private:
  inline Scalar Tanh(const Scalar t) const {
    Scalar result;
    if (tbeg1>tbeg0)
      result = 0.5*(1.0+tanh(strength*(2.0*(t-tbeg0)/(tbeg1-tbeg0)-1.0)));
    else
      result = 1.0;
    if (tend0>tend1)
      result *= 0.5*(1.0-tanh(strength*(2.0*(t-tend1)/(tend0-tend1)-1.0)));
    return result;
  }
};

/// Hann(ing) window
class HannWindow : public Window {
public:
  HannWindow() : Window() {}
  virtual ~HannWindow() {}
  HannWindow(Json::Value &reg) : Window(reg) {}
  virtual inline Scalar operator()(const Scalar time) const {
    return amp*Hann(time);
  }
private:
  inline Scalar Hann(const Scalar time) const {
    if ((tbeg1<=time) && (time<=tend1))
      return 1.0;
    if (time<=tbeg0)
      return 0.0;
    if (time>=tend0)
      return 0.0;
    if ((tbeg0<time) && (time<tbeg1))
      return 0.5*(1.0+cos(pi*(tbeg1-time)/(tbeg1-tbeg0)));
    else
      return 0.5*(1.0+cos(pi*(time-tend1)/(tend0-tend1)));
    return 0.0;
  }
};

/// No window
class NoWindow : public Window {
public:
  NoWindow() : Window() {}
  virtual ~NoWindow() {}
  NoWindow(Json::Value &reg) : Window(reg) {}
  virtual inline Scalar operator()(const Scalar time) const {
    return amp;
  }
};

/// Factory for windows
void Window::factory(Json::Value &root, DGM::Window::Ptr &window) {
  // default to no window if Type is not specified
  if (!root.isMember("Type")) root.set("Type","None");
  if (root["Type"] == "Tanh" || root["Type"] == "tanh") {
    window.reset( new DGM::TanhWindow(root) );
  } else if (root["Type"] == "Hann" || root["Type"] == "hann") {
    window.reset( new DGM::HannWindow(root) );
  } else if (root["Type"] == "None" || root["Type"] == "none") {
    window.reset( new DGM::NoWindow(root) );
  } else {
    throw DGM::exception("Unknown window type = "+root["Type"].asString());
  }
}

} // namespace DGM

#endif
