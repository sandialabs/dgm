/** \file PEDgm.cpp
    \brief Provides DGM specific functionality to peopt.
    \author Joe Young
    \copyright (c)2013 Sandia National Laboratories
*/

// system includes
#include <string>
#include <fstream>
#include <cmath>

// Json includes
#include "json/json.h"

// Local includes
#include "PEDgm.hpp"

namespace peopt{

  // Writes a string to file
  void write_string(string fname,string output) {
    // Write everything to file
    ofstream fout(fname.c_str(),ios_base::out);
    fout << output;
    fout.close();
  }

  // Parses a JSON file and returns the root
  Json::Value Params::parse(
    const DGM::Shared <DGM::Comm>::Ptr comm,
    const std::string fname
  ) {

    // Read in the input file
    Json::Value root;
    Json::Reader reader;
    std::ifstream file(fname.c_str(),std::ifstream::in);
    bool parsingSuccessful = reader.parse( file, root, true );
    if ( !parsingSuccessful )
        comm->error("Failed to parse the parameter file " + fname + ":  "
          + reader.getFormattedErrorMessages());

    // Close everything out and return the root
    file.close();
    return root;
  }

  // Parse a parameter file in json format
  void Params::Dgm::read(string fname){
    // Read in the input file
    Json::Value root=parse(comm,fname);

    // Read in the parameters
    restart_file_frequency=root["DGM"]
        .get("restart file frequency",restart_file_frequency).asInt();
    objective_name=root["DGM"].get("objective name",objective_name).asString();
    num_groups=root["DGM"].get("parallel solves",num_groups).asInt();
    beta=root["DGM"].get("regularization amount",beta).asDouble();
    gamma=root["DGM"].get("regularization roundness",gamma).asDouble();

    std::string reg_type_ = root["DGM"]
        .get("regularization type",
            DGM::Regularization::Type::to_string(reg_type)).asString();
    if(DGM::Regularization::Type::is_valid()(reg_type_))
        reg_type=DGM::Regularization::Type::from_string(reg_type_);
    else
        comm->error("In the parameter file " + fname + ", " + reg_type_ +
            " is not a valid regularization type.");

    std::string problem_class_ = root["DGM"].get("problem class",
        ProblemClass::to_string(problem_class)).asString();
    if(ProblemClass::is_valid()(problem_class_))
        problem_class=ProblemClass::from_string(problem_class_);
    else
        comm->error("In the parameter file " + fname + ", " + problem_class_ +
            " is not a valid problem class.");

    // Validate the input
    validate();
  }

  /// Validates the current set of input parameters
  void Params::Dgm::validate(){
    // Create a base error message
    std::string base="Error in the .peopt file.  ";

    // Check that we have an objective.  This really should
    // not exist and we should determine this ourselves.
    if(objective_name=="")
      comm->error(base + "We require an objective term for optimization.\n");

    // Check that the number of parallel solves is greater than or equal to 1
    if(num_groups<1)
      comm->error("The number of of parallel solves must be at least one.\n") ;

    // Check that the regularization scaling is nonnegative
    if(beta<0.)
      comm->error("The regularization amount must be nonnegative.\n") ;

    // Check that the regularization roundness is positive
    if(gamma<=0.)
      comm->error("The regularization roundness must be positive.\n") ;
  }

  string Params::Dgm::to_string(){
    // Create a new root for writing
    Json::Value root;

    // Write the general optimization parameters
    root["DGM"]["restart file frequency"]=restart_file_frequency;
    root["DGM"]["objective name"]=objective_name;
    root["DGM"]["parallel solves"]=num_groups;
    root["DGM"]["regularization amount"]=beta;
    root["DGM"]["regularization roundness"]=gamma;
    root["DGM"]["regularization type"]=DGM::Regularization::Type
      ::to_string(reg_type);
    root["DGM"]["problem class"]=ProblemClass::to_string(problem_class);

    // Create a string with the above output
    Json::StyledWriter writer;
    string output=writer.write(root);

    return output;
  }

  void Params::Dgm::write(string fname){
    write_string(fname,to_string());
  }

  // Parse diagnostic parameter information
  void Params::Diagnostic::read(string fname){
    // Read in the input file
    Json::Value root=parse(comm,fname);

    // Determine which diagnostic tests to run, if any
    objective=root["Diagnostic"]
      .get("calculate objective",objective).asBool();
    fd_gradient=root["Diagnostic"]
      .get("gradient finite difference test",fd_gradient).asBool();
    hessian_discretize=root["Diagnostic"]
      .get("discretize the hessian",hessian_discretize).asBool();
    fd_gauss_newton=root["Diagnostic"]
      .get("Gauss-Newton finite difference test",fd_gauss_newton).asBool();
    symmetry_check=root["Diagnostic"]
      .get("Hessian symmetry check",symmetry_check).asBool();
    fd_linearized_state=root["Diagnostic"]
      .get("linearized state finite difference test",fd_linearized_state)
      .asInt();
    add_time=root["Diagnostic"]
      .get("append time to output",add_time).asBool();

    // Validate the input
    validate();
  }

  void Params::Diagnostic::validate(){}

  string Params::Diagnostic::to_string(){
    // Create a new root for writing
    Json::Value root;

    // Write out the diagnostic tests that are currently turned on
    root["Diagnostic"]["calculate objective"]=objective;
    root["Diagnostic"]["gradient finite difference test"]=fd_gradient;
    root["Diagnostic"]["discretize the hessian"]=hessian_discretize;
    root["Diagnostic"]["Gauss-Newton finite difference test"]=fd_gauss_newton;
    root["Diagnostic"]["Hessian symmetry check"]=symmetry_check;
    root["Diagnostic"]["linearized state finite difference test"]
      =fd_linearized_state;
    root["Diagnostic"]["append time to output"]=add_time;

    // Create a string with the above output
    Json::StyledWriter writer;
    string output=writer.write(root);

    return output;
  }

  void Params::Diagnostic::write(string fname){
    write_string(fname,to_string());
  }
}
