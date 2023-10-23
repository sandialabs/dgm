/** \file Dakota.cpp
    \brief Direct DGM-DAKOTA interface implementation
*/

// system libraries
#include <cassert>
#include <iostream>

// DGM libraries
#include "OptProblem.hpp"
#include "Dakota.hpp"

// DAKOTA libraries
#include "ProblemDescDB.H"
#include "DakotaModel.H"

// local libraries
#include "Comm.hpp"

namespace DGM {

DirectApplicInterface::
DirectApplicInterface(const Dakota::ProblemDescDB &problem_db,
                      const size_t &num_fns,
                      DGM::ArgList &args_in, const Table &params_in,
                      const DGM::Comm *comm_in )
  :  comm(comm_in), Dakota::DirectApplicInterface(problem_db),
     args(args_in), params(params_in)
{
  // put the root filename for this direct interface at the back of the args
  if ( analysisComponents.size() !=0 )
    args.push_back( analysisComponents[0][0] );
  else {
    cout << "WARNING:  no analysisComponents defined, using 'burg'" << endl;
    args.push_back( "burg" );
  }
  ocp = new Reo::OptProblem( args, params, comm );

  // set the initial guess assuming that ocp has initialized it
  cout << xC.length() << endl;
#if 1
  Dakota::Model &first_model =
    *(const_cast<Dakota::ProblemDescDB*>(&problem_db)->model_list().begin());
  int num_dakota_vars = first_model.acv();
  Dakota::RealVector drv(num_dakota_vars);
  dVector x(drv.values(),num_dakota_vars);
  ocp->optimizer->control->gather( x );
  first_model.continuous_variables(drv);
#else
  dVector x(const_cast<double*>(&(xC[0])),xC.length());
  ocp->optimizer->control->gather( x );
#endif
}

DirectApplicInterface::~DirectApplicInterface()
{
  delete ocp;
}


int DirectApplicInterface::derived_map_if(const Dakota::String& if_name)
{
  (*Dakota::dakota_cerr)
    << if_name << " is not available as an input filter within "
    << "DGM::DirectFnApplicInterface." << endl;
  Dakota::abort_handler(-1);

  return 0;
}


int DirectApplicInterface::derived_map_ac(const Dakota::String& ac_name)
{
  //comm->cout() << "derived_map_ac(...)" << endl;
  //comm->cout() << "analysis server " << analysisServerId << " invoking "
  //             << ac_name << " within DGM::DirectFnApplicInterface." << endl;

  // ------------
  // Error checks
  // ------------

  if (numFns != 1) {
    Cerr << "Error: Bad number of functions in DGM direct fn." << endl;
    Dakota::abort_handler(-1);
  }
  if (numVars < 1) {
    Cerr << "Error: Bad number of variables in DGM direct fn." << endl;
    Dakota::abort_handler(-1);
  }
  if (hessFlag) {
    Cerr << "Error: Hessians not yet supported in DGM direct "
         << "fn." <<endl;
    Dakota::abort_handler(-1);
  }

  // -----------------------
  // DGM input processing
  // -----------------------

#ifdef DGM_PARALLEL
  //comm->cout() << "Input processing " << ac_name << " on analysisComm "
  //     << analysisComm << " with DGM::Comm " << comm->get_id() << endl;
  dVector x(const_cast<double*>(&(xC[0])),xC.length());
  ocp->optimizer->control->scatter( x );
  //if (ocp->optimizer->control->phi.size()>0)
  //  cout << comm->MyPID()<<":  phi = " << ocp->optimizer->control->phi
  //<< endl << flush;
#else
  assert(numACV==ocp->optimizer->control->phi.size());
  for (int i=0; i<numACV; ++i) {
    ocp->optimizer->control->phi[i] = xC[i];
    // cout << i << " " << ocp->optimizer->control->phi[i] << endl;
  }
#endif

  // ----------------
  // DGM execution
  // ----------------

  //comm->cout() << "Execute " << ac_name << " with DGM::Comm "
  //             << comm->get_id() << endl;

  ocp->optimizer->optimize(directFnASV[0]);

  // ------------------------
  // DGM output processing
  // ------------------------

  // Compute objective function and constraints

  // **** f:
  if (directFnASV[0] & 1)
    fnVals[0] = ocp->optimizer->get_j();

  // **** df/dx:
#ifdef DGM_PARALLEL
  if (directFnASV[0] & 2) {
    dVector x(const_cast<double*>(fnGrads[0]),fnGrads.numRows());
    ocp->optimizer->gradient->gather( x );
  }
#else
  if (directFnASV[0] & 2) {
    assert(numACV == ocp->optimizer->gradient->phi.size());
    assert(fnGrads.numRows() == numACV);
    for (int i=0; i<numACV; ++i) {
      // cout << i << " " << ocp->optimizer->gradient->phi[i] << endl;
      fnGrads[0][i] = ocp->optimizer->gradient->phi[i];
    }
  }
#endif
  return 0;
}

int DirectApplicInterface::derived_map_of(const Dakota::String& of_name)
{
  Cerr << of_name << " is not available as an output filter within "
       << "DGM::DirectFnApplicInterface." << endl;
  Dakota::abort_handler(-1);

  return 0;
}

} // namespace DGM
