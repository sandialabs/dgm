#ifndef DGM_REGULARIZATION_SIDE_HPP
#define DGM_REGULARIZATION_SIDE_HPP

/** \file   RegularizationSide.hpp
 *  \brief  Generic regularization term on elemental sides 
 *  \author S. Scott Collis
 *  \author Greg von Winckel
 */

// DTK includes
#include "DTK.hpp"

// DGM includes
#include "Comm.hpp"
#include "Domain.hpp"
#include "vField.hpp"
#include "Vector.hpp"

// JSON include
#include "json/value.h"


namespace DGM {

/**
 *  \class DGM::RegularizationSide
 *  \brief Regularization using integrals over elemental sides
 *
 *         This class gives reading methods and a mask container to 
 *         the classes which derive from it. 
 */
class RegularizationSide : public DTK::Regularization<Scalar,dVector,vField> {

protected:


  struct Pair {
    Ordinal elem;
    Ordinal side;
    Pair(Ordinal e, Ordinal s) : elem(e), side(s) {}
    inline bool operator == (const Pair &x) const {
      return (elem == x.elem) && (side == x.side);
    }
    inline bool operator < (const Pair &x) const {
      return (elem < x.elem) | ((elem == x.elem) && (side < x.side));
    }
  };
  

  vector<Pair> mask;     ///< Regularization mask (no contribution on these elements) 
  bool isMaskEmpty; 
  bool invertMask;       ///< Set this to true to use complement of mask

  /// Read the (Element,Side) pairs and store them in mask
  void readMaskSides(const Json::Value &json) {
    using std::ifstream;
    using std::sort;
    using std::unique;

    /// Read in (Element,Side) pairs specified directly in the JSON
    if( json.isMember("Mask Sides") ) {
      Json::Value maskSides = json["Mask Sides"];
      Ordinal numSides = static_cast<Ordinal>(maskSides.size());
      for(Ordinal n=0; n<numSides; ++n) {
        Json::Value maskPair = maskSides[n];
        Ordinal eid  = static_cast<Ordinal>(maskPair[0].asInt());
        Ordinal side = static_cast<Ordinal>(maskPair[1].asInt());
        mask.push_back(Pair(eid,side));
      } 
    }

    if( json.isMember("Invert Mask") ) {
      Json::Value maskInvert = json["Invert Mask"];
      invertMask = maskInvert.asBool(); 
    } else {
      invertMask = false;
    }

    /// Read in (Element,Side) pairs located in a specified file
    if( json.isMember("Mask File") ) {
      std::string maskFile = json["Mask File"].asString();

      char buffer[80];

      Size eid = 0;
      Ordinal side = 0;

      ifstream ifp(maskFile.c_str());  

      ifp.getline(buffer, 80);           // Ignore first line

      while(!ifp.eof() && ifp.good()) {
        ifp >> eid >> side;
        mask.push_back(Pair(eid,side));
      }

      ifp.close();

      /// unique list of element ids
      sort(mask.begin(), mask.end());
      mask.erase(unique(mask.begin(), mask.end()), mask.end());
    }
  }

  /// Determine if the given (element,side) is in the mask 
  bool inMask(Ordinal e, Ordinal s) const {
    Pair pair(e,s);
    bool isInMask = !isMaskEmpty && 
                    (std::find(mask.begin(),mask.end(),pair) != mask.end() );

      return invertMask ? !isInMask : isInMask; 
  } 

public:

  virtual ~RegularizationSide() {} 

}; 
  
} // namespace DGM


#endif // DGM_REGULARIZATION_SIDE_HPP
