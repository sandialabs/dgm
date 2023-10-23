#ifndef DGM_ROL_FACTORY_HPP
#define DGM_ROL_FACTORY_HPP

/** \file   ROL_Factory.hpp
    \brief  Create a ROL::Step object from a JSON block
    \author Greg von Winckel
*/

#ifdef DGM_USE_ROL

// DGM includes
#include "State.hpp"
#include "Adjoint.hpp"
#include "Optimizer.hpp"
#include "OptProblem.hpp"
#include "Preconditioner.hpp"

// DGM ROLinterface includes
#include "ROL_Interface.hpp"
#include "ROL_Parameters.hpp"
#include "ROL_DGM_LineSearch.hpp"
#include "ROL_SplitUpdateLineSearchStep.hpp"
#include "FivePointLineSearch.hpp"

#include "Color.hpp"

// ROL includes
#include "ROL_Step.hpp"
#include "ROL_LineSearchStep.hpp"
#include "ROL_TrustRegionStep.hpp"
#include "ROL_StatusTest.hpp"
#include "ROL_ValidParameters.hpp"

namespace DGM {

/// Factory to make a ROL compatible optimizer for DGM
template<class Real> 
class ROL_Factory {

  typedef ROL::Step<Real>            Step;
  typedef ROL::Bracketing<Real>      Bracketing;
  typedef ROL::LineSearchStep<Real>  LineSearchStep;
  typedef ROL::TrustRegionStep<Real> TrustRegionStep; 
  typedef ROL::StatusTest<Real>      StatusTest;
  
private:

  ROL::ParameterList rolParams_;
  ROL::ParameterList gcParams_;
  DGM::Comm::Ptr comm_;

  const bool useTrustRegion_;
  std::vector<int> fdorders_;
  bool split_update_;

  Real dgm_brents_tol_alpha_; // Alpha tolerance to use DGM's Brent's implementation

public:
  
  ROL_Factory( const Json::Value &json, const DGM::Comm::Ptr comm,
               const bool uTR, std::vector<int> &fd ) :
    comm_(comm), useTrustRegion_(uTR), fdorders_(fd) {

    ROL::Ptr<const ROL::ParameterList> validParams = ROL::getValidROLParameters();
 
    ROL::ParameterList optParams;


    // Copy eveything in the "Optimizer" block into a ParameterList
    jsonToParameterList( json, optParams );

    dgm_brents_tol_alpha_ = optParams.get("DGM Brent's tol_alpha",1.e-5);

    rolParams_ = optParams.sublist("ROL");

    // Increment the maximum number of iterations in the status test, because ROL
    // expects iterate counting to begin at 0
    if( rolParams_.sublist("Status Test").isParameter("Iteration Limit") ) {
      rolParams_.sublist("Status Test").set("Iteration Limit",1+
        rolParams_.sublist("Status Test").get("Iteration Limit", 10));
    } 

    // If a "Gradient Check" sublist is found in "ROL", move it to 
    // "Optimizer" if no such block exists there, otherwise delete it
    if( rolParams_.isParameter("Gradient Check") ) {
      comm_->cout() << "Moving \"Gradient Check\" from \"ROL\" to \"Optimizer\"" << std::endl;
      optParams.set("Gradient Check",rolParams_.sublist("Gradient Check"));
      rolParams_.remove("Gradient Check");
    }

    if( optParams.isParameter("Gradient Check") ) {
      gcParams_ = optParams.sublist("Gradient Check");
    }

    // If "Step">"Line Search">"Split Update" exists, delete it and add
    // a "Split Update" to "Optimizer" if it is not already there (active by default)
     ROL::ParameterList &lsParams = rolParams_.sublist("Step").sublist("Line Search");
    if( lsParams.isParameter("Split Update") && !optParams.isParameter("Split Update") ) {
      optParams.set("Split Update",lsParams.get("Split Update",true));
      lsParams.remove("Split Update");
      split_update_ = optParams.get("Split Update", true);
      comm_->cout() << "Moving \"Split Update\" from \"ROL\"->\"Line Search\" to " 
        "\"Optimizer\"" << std::endl;
    }
    else {
      if(!optParams.isParameter("Split Update") ){
        split_update_ = true;
        optParams.set("Split Update",true);
      }
      else {
        split_update_ = optParams.get("Split Update",true);
      }
    }
       
    // If "Optimizer" contains a "User Defined Line-Search" other than "None"
    // create the desired LineSearchStep
    if( optParams.isParameter("User Defined Line-Search") ) {
      std::string udls = optParams.get("User Defined Line-Search","None");
      lsParams.sublist("Line-Search Method").set("User Defined Line-Search Name",udls);
    }

    // If a "Scalar Minimization" block exists, delete it
    if( rolParams_.isParameter("Scalar Minimization") ) {
      comm->cout() << "WARNING: Deleting deprecated \"Scalar Minimization\" block in \"ROL\"" << std::endl;
      rolParams_.remove("Scalar Minimization");
    }    

    rolParams_.setName("ROL");

    if(comm->verbosity()) {
      comm->cout() << "Supplied ROL Parameters:\n" << rolParams_;
    }

    // Validate the ParameterList - currently validates only names and types, not values
    comm->cout() << "Validating ROL Parameters" << std::endl;

    // Put the validation in a try-catch block so that we can suppress Teuchos' exception
    // message to all but the first process
    try {
      rolParams_.validateParametersAndSetDefaults(*validParams);
    }
    catch ( const std::logic_error& e ) {
      comm->cout() << e.what() << std::endl;
      throw DGM::exception("Invalid Parameter Name");
    }

    if( optParams.isParameter("Gradient Check") ) {
      ROL::ParameterList &gradParams = optParams.sublist("Gradient Check");

      if( gradParams.isType<int>("Order") ) {
        fdorders_.push_back( gradParams.get("Order",1) );
      }
    } // End gradient check
  } // End constructor



  ROL::Ptr<Step> getStep( ) {
    using ROL::Ptr; 
    using ROL::ParameterList;

    ROL::Ptr<Step> step;

    if( useTrustRegion_ ) {
      comm_->cout() << "Creating ROL Trust-Region step\n";
      step = ROL::makePtr<TrustRegionStep>(rolParams_);  
    } else { // Use a LineSearch
      comm_->cout() << "Creating ROL Linesearch step\n";
      ParameterList &lsParams = rolParams_.sublist("Step").sublist("Line Search");
      ParameterList &lsmParams = lsParams.sublist("Line-Search Method"); 

      std::string lstype = lsmParams.get("Type","Cubic Interpolation");

      ROL::Ptr<ROL::LineSearch<Real> > lineSearch;      

      // Handle special DGM-special cases   
      if(split_update_) {
        if( lstype == "Five Point" ) {
          lineSearch = ROL::makePtr<FivePointLineSearch<Real>>(rolParams_); 
          step = ROL::makePtr<SplitUpdateLineSearchStep<Real>>( comm_, rolParams_, lineSearch );
        } else if( (lstype == "DGM Brent's") || (lstype == "ROL Brent's") ) {
          lineSearch = ROL::makePtr<ROLinterface::LineSearch<Real>>(rolParams_, 
                            comm_, dgm_brents_tol_alpha_);
          step = ROL::makePtr<SplitUpdateLineSearchStep<Real>>( comm_, rolParams_, lineSearch );  
        } else { // Use ROL's provided methods
          step = ROL::makePtr<SplitUpdateLineSearchStep<Real>>( comm_, rolParams_ );
        }
      } // end if split_update
      else {
        if( lstype == "Five Point" ) {
          lineSearch = ROL::makePtr<FivePointLineSearch<Real>>(rolParams_); 
          step = ROL::makePtr<LineSearchStep>( rolParams_, lineSearch );
        } else if( (lstype == "DGM Brent's") || (lstype == "ROL Brent's") ) {
          lineSearch = ROL::makePtr<ROLinterface::LineSearch<Real>>(rolParams_, 
                            comm_, dgm_brents_tol_alpha_);
          step = ROL::makePtr<LineSearchStep>( rolParams_, lineSearch );  
        } else { // Use ROL's provided methods
          step = ROL::makePtr<LineSearchStep>( rolParams_ );
        }
      } // end else split_update
    }
    return step; 
  } // getStep

  ROL::Ptr<StatusTest> getStatusTest( ) {
    return ROL::makePtr<StatusTest>(rolParams_);
  } 

  void getFDOrders( std::vector<int> &fd ) {
    fd = fdorders_;
  }

  void fillParameterList( ROL::ParameterList &parlist ) {
    parlist = rolParams_;
  }

  void fillGradientCheckParameterList( ROL::ParameterList &gclist ) {
    gclist = gcParams_;
  }

  void jsonToParameterList( const Json::Value &json, 
                            ROL::ParameterList &parlist ) {
    if(json.size()>0) {

      // Iterate over JSON
      for(Json::ValueIterator itr = json.begin(); itr != json.end(); ++itr) {

        // Get the current element 
        const std::string key = itr.key().asString();
        const Json::Value &val = json[key];

        if(val.isString()) {
          parlist.set(key,val.asString());
        } else if(val.isBool()) {
          parlist.set(key,val.asBool());
        } else if(val.isInt()) {
          parlist.set(key,val.asInt());
        } else if(val.isUInt()) {
          parlist.set(key,val.asUInt());
        } else if(val.isDouble()) {
          parlist.set(key,val.asDouble());
        } else if(val.isArray()) {
          // Allowed but not inserted into ROL::ParameterList
        } else if(val.isObject()) { // If this is a block, make a recursive call
          ROL::ParameterList &sublist = parlist.sublist(key);
          jsonToParameterList(val, sublist); 
        }
        else {
          throw DGM::exception("Json value has unsupported type.");
        }
      } // end loop over json blocks
    } // end if json.size()>0
  } // end jsonToParameterList

}; // Factory

} // namespace DGM

#endif // DGM_USE_ROL

#endif // DGM_ROL_FACTORY_HPP
