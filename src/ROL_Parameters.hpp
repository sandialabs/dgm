#ifndef DGM_ROL_PARAMETERS_HPP
#define DGM_ROL_PARAMETERS_HPP

/** \file ROL_Parameters.hpp
 *  \brief  Convert ROL parameters from JSON to ROL::ParameterList
 *
 *  Given the ROL block of a JSON file, extract parameters and
 *  put them in a ROL::ParameterList for use by ROL.
 *
 *  \author Greg von Winckel
 *  \copyright (c)2014 Sandia National Laboratories
 */

// DGM includes
#include "ROL_Optimizer.hpp"

// system includes
#include <string>

namespace DGM {

/// Namespace for DGM-ROL interface
namespace ROLinterface {

/// Set default ROL parameters
void setDefaultParameters(ROL::ParameterList& parlist) {
  //          Parameter Name                                       Default value
  parlist.set("Descent Type",                                      "Nonlinear CG"        );
  parlist.set("Nonlinear CG Type",                                 "Hagar-Zhang"         );
  parlist.set("Secant Type",                                       "Limited-Memory BFGS" );
  parlist.set("Linesearch Type",                                   "Cubic Interpolation" );
  parlist.set("Linesearch Curvature Condition",                    "Wolfe Conditions"    );
  parlist.set("Trust-Region Subproblem Solver Type",               "Truncated CG"        );
  parlist.set("Use Secant Preconditioning",                        false                 );
  parlist.set("Use Secant Hessian-Times-A-Vector",                 false                 );
  parlist.set("Maximum Secant Storage",                            10                    );
  parlist.set("Barzilai-Borwein Type",                             1                     );
  parlist.set("Use Inexact Objective Function",                    false                 );
  parlist.set("Use Inexact Gradient",                              false                 );
  parlist.set("Use Inexact Hessian-Times-A-Vector",                true                  );
  parlist.set("Maximum Number of Function Evaluations",            20                    );
  parlist.set("Sufficient Decrease Parameter",                     1.e-4                 );
  parlist.set("Curvature Conditions Parameter",                    0.9                   );
  parlist.set("Curvature Conditions Parameter: Generalized Wolfe", 0.6                   );
  parlist.set("Bracketing Tolerance",                              1.e-8                 );
  parlist.set("Backtracking Rate",                                 0.5                   );
  parlist.set("Initial Linesearch Parameter",                      1.e1                  );
  parlist.set("User Defined Linesearch Parameter",                 true                  );
  parlist.set("Absolute Krylov Tolerance",                         1.e-4                 );
  parlist.set("Relative Krylov Tolerance",                         1.e-2                 );
  parlist.set("Maximum Number of Krylov Iterations",               4                     );
  parlist.set("Initial Trust-Region Radius",                       1.e-0                 );
  parlist.set("Minimum Trust-Region Radius",                       1.e-12                );
  parlist.set("Maximum Trust-Region Radius",                       5.e3                  );
  parlist.set("Step Acceptance Parameter",                         0.05                  );
  parlist.set("Radius Shrinking Threshold",                        0.05                  );
  parlist.set("Radius Growing Threshold",                          0.9                   );
  parlist.set("Radius Shrinking Rate (Negative rho)",              0.0625                );
  parlist.set("Radius Shrinking Rate (Positive rho)",              0.25                  );
  parlist.set("Radius Growing Rate",                               2.5                   );
  parlist.set("Trust-Region Safeguard",                            1.e4                  );
  parlist.set("Gradient Tolerance",                                1.e-6                 );
  parlist.set("Step Tolerance",                                    1.e-12                );
  parlist.set("Maximum Number of Iterations",                      20                    );
}

void addJSONBlockToPL(const Json::Value& block,ROL::ParameterList& parlist);
void addJSONPairToPL(const Json::Value& block, const std::string &key,
                     ROL::ParameterList& parlist);

/** \brief Given a JSON block and a key
 *  Get the value and insert the key-value pair into a ROL::ParameterList.
 *  If the value is itself a block, recursively iterate.
 *
 *  @param[in]     block     is a block from a JSON object
 *  @param[in]     key       is a string key
 *  @param[in,out] parlist   is a ROL::ParameterList
*/
void addJSONPairToPL(const Json::Value& block,
                     const std::string &key,
                     ROL::ParameterList& parlist) {

  Json::Value val = block[key];

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
  } else if(val.isObject()) { // This is a block. Iterate over its pairs
    addJSONBlockToPL(val,parlist);
  }
  else {
    throw DGM::exception("Json value has unsupported type.");
  }
}

/** \brief Iterate over a block and insert key-value pairs
           into the ROL::ParameterList

    @param[in]     block     is a block from a JSON object
    @param[in,out] parlist   is a ROL::ParameterList
*/
void addJSONBlockToPL(const Json::Value& block,
                      ROL::ParameterList& parlist) {
  if(block.size()>0) {
    for(Json::ValueIterator itr = block.begin();
        itr != block.end(); ++itr) {
      addJSONPairToPL(block,itr.key().asString(),parlist);
    }
  }
}

/** \brief  Read a JSON block and store all in a flat ROL::ParameterList.

    Checks for a key called "Algorithm" which has a string value which
    can specify a Step Type (Linesearch or Trust-Region) and either a
    Descent Type or a Trust-Region Subproblem Solver Type.

    @param[in]     json      is a block from a JSON object
    @param[in,out] parlist   is a ROL::ParameterList
    @param[out]    fdorders  is a vector of finite difference orders to use
*/
void getROL_JSON_Parameters( const Json::Value& json,
	        	                 ROL::ParameterList& parlist,
                             std::vector<int>& fdorders ) {

  parlist.set("Use Inexact Hessian-Times-A-Vector",true);

  if(json.isMember("ROL")) {
    Json::Value rolBlock = json["ROL"];

    if(rolBlock.isMember("Gradient Check")) {
      Json::Value gradCheckBlock = rolBlock["Gradient Check"];

      // Look for a specified FD gradient check order
      Json::Value fdval = gradCheckBlock.get("Gradient Check Order",1);

      // Test gradient for a single order
      if(fdval.isInt()) {
        fdorders.resize(1);
        fdorders[0] = fdval.asInt();
        if( fdorders[0] < 1 || fdorders[0] > 4 ) {
          throw DGM::exception("Finite difference order must be 1,2,3, or 4");
        }
      }

      // Test gradient for multiple orders
      else if ( fdval.isArray() ) {
        int nvals = fdval.size();

        fdorders.resize(nvals);
        for(int i=0;i<nvals;++i) {
          fdorders[i] = fdval[i].asInt();
          if( fdorders[i] < 1 || fdorders[i] > 4 ) {
            throw DGM::exception("Finite difference order must be 1,2,3, or 4");
          }
        }
      }

      // Unsupported type
      else {
        throw DGM::exception("Json value has unsupported type.");
      }
    }

    // Make a flat parameter list from the ROL JSON block
    addJSONBlockToPL(rolBlock,parlist);

    // Check for an algorithm
    if(rolBlock.isMember("Algorithm")) {
      std::string rolAlgorithm = rolBlock["Algorithm"].asString();

      if(rolAlgorithm.find("Trust-Region") != std::string::npos) {

        parlist.set("Step Type","Trust-Region");

        // Set subproblem solver
        if(rolAlgorithm.find("Cauchy Point") != std::string::npos) {
          parlist.set("Trust-Region Subproblem Solver Type","Cauchy Point");
        }
        else if(rolAlgorithm.find("Double Dogleg") != std::string::npos) {
          parlist.set("Trust-Region Subproblem Solver Type","Double Dogleg");
        }
        else if(rolAlgorithm.find("Dogleg") != std::string::npos) {
          parlist.set("Trust-Region Subproblem Solver Type","Dogleg");
        }
        else if(rolAlgorithm.find("Truncated CG") != std::string::npos) {
          parlist.set("Trust-Region Subproblem Solver Type","Truncated CG");
        }

      }
      else { // Use Linesearch
        parlist.set("Step Type","Linesearch");

        // Set descent type
        if(rolAlgorithm.find("Steepest Descent") != std::string::npos) {
          parlist.set("Descent Type","Steepest Descent");
        }
        else if(rolAlgorithm.find("Quasi-Newton") != std::string::npos) {
          parlist.set("Descent Type","Quasi-Newton Method");
        }
        else if(rolAlgorithm.find("Newton-Krylov") != std::string::npos) {
          parlist.set("Descent Type","Newton-Krylov");
        }
        else if(rolAlgorithm.find("Nonlinear CG") != std::string::npos) {
          parlist.set("Descent Type","Nonlinear CG");
        }

      }

    }
    else { // No algorithm block found - use defaults
      parlist.set("Step Type","Linesearch");
      parlist.set("Descent Type","Nonlinear CG");
    }

  }
}

/** \brief  Read a JSON block and store all in a heirarchical
 *  ROL::ParameterList.
 *
 *  @param[in]     json      is a block from a JSON object
 *  @param[in,out] parlist   is a ROL::ParameterList
 */
 void tieredParameterListFromJson( const Json::Value& json,
                                   ROL::ParameterList& parlist) {
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
        tieredParameterListFromJson(val, sublist); 
      }
      else {
        throw DGM::exception("Json value has unsupported type.");
      }
    }
  }
}

}  // namespace ROLinterface

}  // namespace DGM

#endif
