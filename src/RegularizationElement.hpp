#ifndef DGM_REGULARIZATION_ELEMENT_HPP
#define DGM_REGULARIZATION_ELEMENT_HPP

/** \file   RegularizationElement.hpp
 *  \brief  Generic regularization term on elemental interiors 
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
 *  \class DGM::RegularizationElement
 *  \brief Regularization using integrals over elemental volumes
 *
 *         This class gives reading methods and a mask container to 
 *         the classes which derive from it. 
 */
class RegularizationElement : public DTK::Regularization<Scalar,dVector,vField> {

protected:

  vector<Ordinal> mask;  ///< Regularization mask (no contribution on these elements) 
  bool isMaskEmpty;
  bool invertMask;       ///< Set this to true to use complement of mask

  /// Read elements and store them in mask
  void readMaskElements(const Json::Value &json) {
    using std::sort;
    using std::unique;

    /// Read in mask elements specified directly in the JSON
    if( json.isMember("Mask Elements") ) {
      Json::Value maskElements = json["Mask Elements"];
      Ordinal numElements = static_cast<Ordinal>(maskElements.size());
      for(Ordinal e=0; e<numElements; ++e) {
        Ordinal eid = static_cast<Ordinal> (maskElements[e].asUInt());
        mask.push_back(eid);
      } 
    }

    if( json.isMember("Invert Mask") ) {
      Json::Value maskInvert = json["Invert Mask"];
      invertMask = maskInvert.asBool(); 
    } else {
      invertMask = false;
    }

    /// Read in list of elements located in a specified file
    if( json.isMember("Mask File") ) {
      std::string maskFile = json["Mask File"].asString();

      char buffer[80];

      Ordinal eid = 0;
      std::ifstream ifp(maskFile.c_str());  
      ifp.getline(buffer, 80);           // Ignore first line
      while(!ifp.eof() && ifp.good()) {
        ifp >> eid;
        mask.push_back(eid);
      }
      ifp.close();    

    }

    /// Make unique list of element indices
    sort(mask.begin(), mask.end());
    mask.erase(unique(mask.begin(), mask.end()), mask.end());
  }

  /// Determine if the given element is masked
  bool inMask(Ordinal e) const {
    bool isInMask = !isMaskEmpty && 
         (std::find(mask.begin(),mask.end(),e) != mask.end() );
   
    return invertMask ? !isInMask : isInMask; 
  }

public:

  virtual ~RegularizationElement() {} 

}; 
  
} // namespace DGM

#endif // DGM_REGULARIZATION_ELEMENT_HPP
