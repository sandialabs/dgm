#ifndef DGM_REGULARIZATION_MANAGER_HPP
#define DGM_REGULARIZATION_MANAGER_HPP

/**
 *   \file RegularizationManager.hpp
 *   \brief This class creates a set of regularization terms given JSON block
 *   \author Greg von Winckel
 *   \author S. Scott Collis
 */

// DTK includes
#include "DTK.hpp"

// DGM includes
#include "Comm.hpp"
#include "Domain.hpp"
#include "vField.hpp"
#include "Vector.hpp"
#include "LocalTV.hpp"
#include "LocalH1.hpp"
#include "Tikhonov.hpp"
#include "JumpPenalty.hpp"
#include "JumpPenaltyTV.hpp"

// DGM regularization terms
#include "Tikhonov.hpp"
#include "LocalH1.hpp"
#include "LocalTV.hpp"
#include "JumpPenalty.hpp"
#include "JumpPenaltyTV.hpp"

// JSON include
#include "json/value.h"

namespace DGM {

/// Container for regularization terms
class RegularizationManager :
  public DTK::Regularization<Scalar,dVector,vField> {

  const DGM::Comm::Ptr comm;        ///< Communicator for this domain

  const int verb;                   ///< verbosity level

  typedef DGM::Shared<DTK::Regularization<Scalar,dVector,vField> >::Ptr regType;
  typedef std::vector<regType> dbType;
  typedef dbType::size_type size_type;

  dbType regTerms;                  ///< database of reg(ularization) terms

  vField Sf;                        ///< vector Field for scratch computation


public:
  
  /// Construct from a JSON value
  RegularizationManager(vField &S, const Json::Value& json,
                        const DGM::Comm::Ptr comm_ = DGM::Comm::World) 
  : comm(comm_), verb(comm_->verbosity()), Sf(comm_)
  {
    if(json.isMember("Type")) {                    // Backward compatibility
      std::string type = json.get("Type","Tikhonov").asString();
      regType reg;

      if(type == "Tikhonov") {
        reg.reset( new DGM::Tikhonov(S,json,comm) );
      } else if(type == "LocalH1") {
        reg.reset( new DGM::LocalH1(S,json,comm) );
      } else if(type == "LocalTV") {
        reg.reset( new DGM::LocalTV(S,json,comm) );
      } else if(type == "Jump Penalty") {
        reg.reset( new DGM::JumpPenalty(S,json,comm) );
      } else if(type == "Jump Penalty TV") {
        reg.reset( new DGM::JumpPenaltyTV(S,json,comm) );
      } else {
        throw DGM::exception("RegularizationManager: Unsupported "
            "regularization type = "+type);
      }
      regTerms.push_back(reg);

    } else {                                        // New approach

      // Iterate over sub-blocks
      for(Json::ValueIterator itr = json.begin(); itr != json.end(); ++itr) {
        // Get a sub-block
        std::string name = itr.key().asString();
        Json::Value block = json[name];
        // Get the type of the sub-block
        std::string type = block.get("Type","Tikhonov").asString();
        regType reg;
        if(type == "Tikhonov") {
          reg.reset( new DGM::Tikhonov(S,block,comm) );
        } else if(type == "LocalH1") {
          reg.reset( new DGM::LocalH1(S,block,comm) );
        } else if(type == "LocalTV") {
          reg.reset( new DGM::LocalTV(S,block,comm) );
        } else if(type == "Jump Penalty") {
          reg.reset( new DGM::JumpPenalty(S,block,comm) );
        } else if(type == "Jump Penalty TV") {
          reg.reset( new DGM::JumpPenaltyTV(S,block,comm) );
        } else {
          throw DGM::exception("RegularizationManager: Unsupported "
                               "regularization type = "+type);
        }
        regTerms.push_back(reg);
      }
    }
  }
 
  /// Destructor 
  virtual ~RegularizationManager() {}

  /// \name Provide the DTK::Regularization interface
  //@{
  /// Evaluate the regularizaiton term as return value
  virtual Scalar operator()(const vField &x) const {
    dVector result(x.size());
    return operator()(x,result);
  }

  /// Evaluate the regularization term and return Field contributions in result
  virtual Scalar operator()(const vField &x, dVector &result) const {
   dVector temp(result.size());
   Scalar sum = 0;
   for(size_type i=0; i<regTerms.size(); ++i) {
     sum += regTerms[i]->operator()(x,temp);
     result += temp;       
   }
   return sum;
  }

  /// Compute contributions to the gradient
  virtual void grad(const vField &x, vField &g) const {
    for(size_type i=0; i<regTerms.size(); ++i) {
     regTerms[i]->grad(x,g);  
    }         
  }
  
  /// Compute the Hessian-vector product
  virtual void hessvec(const vField &x, const vField &dx, vField &H_dx) const {
    DGM_UNDEFINED;
  }
  //@}     

}; // class RegularizationManager
   
} // namespace DGM

#endif 
