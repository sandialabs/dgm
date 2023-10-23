/** \file ErrProblem.cpp
    \brief Error estimation problem implementation
    \author Scott Collis
*/

// DGM includes
#include "ErrProblem.hpp"

// Reo includes
#include "Reo.hpp"

namespace DGM {

ErrProblem::ErrProblem(DGM::ArgList& args, const Table& table,
                       const DGM::Comm *comm_)
  : comm(comm_), params(table) {

  params["eqntype"]  = Reo::ADV_DIFF;
  params["p_inc"]    = 2;            // increment in p-order for adjoint
  params["p_ref"]    = 2;            // increment in p-order for refinement
  params["npredict"] = 100;          // Set default value - needed for ErrEst
  params["refine"]   = TOLERANCE;    // refinement strategy
  params["root"]     = "root";       // root file name
  params["steady"]   = true;         // default is steady problems
  params["J_exact"]  = 0.5;          // default value for exact J.

  use_err = true;                    // default is to compute Error estimate

  parse_args(args);

  err = new Estimate(args, params, comm);

  // Final check of argument list
  if ( params.defined("showUsage") ) comm->exit(0);
#ifdef DGM_REMOVE_ARGUMENTS
  if ( args.size() != 2 ) {
    comm->cout() << "WARNING:  " << args.size() << " unused arguments:  ";
    print( args );
  }
#endif
}

void ErrProblem::parse_args( DGM::ArgList &args ) {
  string name, value;

  // get basic information from argument list
  code = args.front();
  if (args.size() < 2) {
    showUsage(code);
    comm->exit(DGM::FAILURE);
  }
  root = args.back();
  params["root"] = root;
  params.read(root+".inp");

  list< DGM::ArgList::iterator > li;
  for ( DGM::ArgList::iterator a = args.begin(); a != args.end(); a++ ) {
    if ( (*a)[0] == '-' ) {
      name = *a;
      if (name == "-help") {
        params["showUsage"] = 1;
        showUsage(code);
      } else if (name == "-noerr") {
        comm->cout() << "OK... solving problem without error estimation."
                     << endl;
        use_err = false;
      } else if (name == "-p_inc") {
        li.push_back(a);
        value = *(++a);
        li.push_back(a);
        params["p_inc"] = atoi(value.c_str());
      } else if (name == "-p_ref") {
        li.push_back(a);
        value = *(++a);
        li.push_back(a);
        params["p_ref"] = atoi(value.c_str());
      } else if (name == "-npredict") {
        li.push_back(a);
        value = *(++a);
        li.push_back(a);
        params["npredict"] = atoi(value.c_str());
      } else if (name == "-unsteady") {
        li.push_back(a);
        params["steady"] = false;
      } else if (name == "-refine") {
        li.push_back(a);
        value = *(++a);
        li.push_back(a);
        params["refine"] = atoi(value.c_str());
      } else if (name == "-J_exact") {
        li.push_back(a);
        value = *(++a);
        li.push_back(a);
        params["J_exact"] = atof(value.c_str());
      }
    }
  }
#ifdef DGM_REMOVE_ARGUMENTS
  // remove tagged arguments
  for ( list< DGM::ArgList::iterator >::iterator a=li.begin();
        a!=li.end(); a++) args.erase(*a);
#endif
}


void ErrProblem::showUsage(const string& code) const {
  comm->cout()
    << "Problem_err Class Options \n"
    << "----------------------------------------------------------------\n"
    << "-noerr   " << '\t' << "Just solve the problem\n"
    << "-p_inc   " << '\t' << "Increment in p for Adjoint problem\n"
    << "-p_ref   " << '\t' << "Increment in p for refinement\n"
    << "-npredict" << '\t' << "Number of timestep to predict Error\n"
    << "-unsteady" << '\t' << "Set for unsteady problems\n"
    << "-refine  " << '\t' << "Refinement strategy\n"
    << "-J_exact " << '\t' << "Exact value of Objective function\n"
    << "----------------------------------------------------------------\n";
}

} // namespace DGM
