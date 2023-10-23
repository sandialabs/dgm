/** \file PEReo.cpp
    \brief Provides Reo specific functionality to peopt. */

#include <string>
#include <fstream>
#include <cmath>
#include "json/json.h"
#include "PEReo.hpp"

namespace peopt{

  // Parse a parameter file in JSON format
  void Params::Reo::read(string fname){
    // Read in the input file
    Json::Value root=parse(comm,fname);

    // Read in the parameters
    std::string weighting_ = root["Reo"]
        .get("weighting scheme",Weighting::to_string(weighting)).asString();
    if(Weighting::is_valid()(weighting_))
        weighting=Weighting::from_string(weighting_);
    else
        comm->error("In the parameter file " + fname + ", " + weighting_ +
            " is not a valid weighting scheme.");

    weights.clear();
    for(int i=0;i<(int)root["Reo"]["weights"].size();i++){
      vector <DGM::Scalar> tmp;
      for(int j=0;j<(int)root["Reo"]["weights"][i].size();j++)
        tmp.push_back(root["Reo"]["weights"][i][j].asDouble());
      weights.push_back(tmp);
    }

    // Validate the input
    validate();
  }

  /// Validates the current set of input parameters
  void Params::Reo::validate(){}

  string Params::Reo::to_string(){
    // Create a new root for writing
    Json::Value root;

    // Write the Reo parameters
    root["Reo"]["weighting scheme"]=Weighting::to_string(weighting);

    for(int i=0;i<(int)weights.size();i++)
      for(int j=0;j<(int)weights[i].size();j++)
        root["Reo"]["weights"][i][j]=weights[i][j];

    // Create a string with the above output
    Json::StyledWriter writer;
    string output=writer.write(root);

    return output;
  }

  void Params::Reo::write(string fname){
    write_string(fname,to_string());
  }
}
