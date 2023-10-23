/** \file Estimate.cpp
    \brief DGM error estimation problem class implementation
    \author Scott Collis
*/

// system includes
#include <fstream>

// DGM includes
#include "Tools.hpp"
#include "ErrProblem.hpp"
#include "Estimate.hpp"

// Reo includes
#include "Reo.hpp"
#include "Adv_Diff_State.hpp"
#include "Adv_Diff_Adjoint.hpp"
#include "Adv_Diff_Control.hpp"

#include "Euler_State.hpp"
#include "Euler_Adjoint.hpp"
#include "Euler_Control.hpp"

namespace DGM {

Estimate::Estimate(DGM::ArgList&args, const Table &params_,
                 const DGM::Comm* comm_)
  : comm(comm_), params(params_) {

  root = (string)params["root"];
  p_inc = params["p_inc"];
  p_ref = params["p_ref"];
  npredict = params["npredict"];
  refine = params["refine"];
  steady = params["steady"];
  J_exact = params["J_exact"];

  int eqntype = params["eqntype"];

  switch (eqntype) {
  case Reo::ADV_DIFF:  {
    comm -> cout () << "Preparing to estimate error for: Adv_Diff" << endl;
    state = new Reo::Adv_Diff_State(args, comm);
    adjoint = new Reo::Adv_Diff_Adjoint(args, state, comm, p_inc);
    control.reset( new Reo::Adv_Diff_Control(args, state, comm) );
    gradient.reset( control->clone() );
    gradient->control_type(Control::GRADIENT);
    objective = new Reo::Adv_Diff_Objective(args, state, adjoint, comm);

    state2 = new Reo::Adv_Diff_State(args, comm, p_inc);
#ifdef USE_FULL_SECOND_PROBLEM
    // not needed [ssc]
    adjoint2 = new Reo::Adv_Diff_Adjoint(args, state2, comm, p_inc);
    control2.reset( new Reo::Adv_Diff_Control(args, state2, comm) );
    gradient2.reset( control2->clone() );
    gradient2->control_type(Control::GRADIENT);
    objective2 = new Reo::Adv_Diff_Objective(args, state2, adjoint2, comm);
#endif
    break; }
  case Reo::EULER:  {
    comm -> cout () << "Preparing to estimate error for: Euler" << endl;
    state = new Reo::Euler_State(args, comm);
    adjoint = new Reo::Euler_Adjoint(args, state, comm, p_inc);
    control.reset( new Reo::Euler_Control(args, state, comm) );
    gradient.reset( control->clone() );
    gradient->control_type(Control::GRADIENT);
    objective = new Reo::Euler_Objective(args, state, adjoint, comm);

    state2 = new Reo::Euler_State(args, comm, p_inc);
    break; }
  default: {
    comm->cerr() << "ERROR: Estimate: undefined eqntype" << endl;
    comm->exit(1); }
  }
}

void Estimate::estimate() {
  static Format sci(15); sci.scientific().width(22);

  comm->cout() << "Estimating error..." << endl;

  state->initialize();
  control->initialize();
  adjoint->initialize();

  state2->initialize();
#ifdef USE_FULL_SECOND_PROBLEM
  // not needed [ssc]
  control2->initialize();
  adjoint2->initialize();
#endif

  // Just for debugging purposes
  //  state2->set_initial_condition();
  //  Scalar J_h_2 = state2->compute(npredict, control2);

  state->set_initial_condition();
  Scalar J_h = state->compute(npredict, control);

  gradient->zero();

  adjoint->set_end_condition();
  adjoint->compute(npredict, control, gradient);

  dVector error;

  Scalar total_error;
  const Scalar J(J_exact);
  if (steady) {
    total_error = state2->estimate_error_steady(npredict, adjoint, error);
    //J = 0.5;                     // u^2
    //J = 7.640917153662007e-02;   // ?
    //J = 2.9903252370026e-02;     // Gaussian, dirichlet, sigma=0.1
    //J = 1.322044832033884e-01;   // Gaussian, sigma=1
  } else {
    total_error = state2->estimate_error(npredict, adjoint, error);
    //J = 1.255679620266458e-01;   // Average value
    //J = 2.155068524101516e-03;   // u^2
  }

  const Scalar actual_error = J - J_h;

  Scalar coef = actual_error/total_error;

  comm->cout() << endl
               << "J                       = " << sci(J) << endl
               << "J_h                     = " << sci(J_h) << endl
               << "Computed Error Estimate = " << sci(total_error) << endl;

  comm->cout() << "Actual Error, (J - J_h) = " << sci(actual_error) << endl;
  comm->cout() << "Effectivity             = " << sci(coef) << endl;

  if (refine == DGM::ErrProblem::PERCENT) {
    comm->cout() << endl << "Starting p-Refinement based on percentage..."
                 << endl;
    pRefine_20(error.data(), error.size());
  } else if (refine == DGM::ErrProblem::TOLERANCE) {
    Scalar tol = abs(total_error/error.size()/10.0);
    comm->cout() << endl
                 << "Starting p-Refinement based on relative tolerance "
                 << tol
                 << endl;
    pRefine_TOL(error.data(), error.size(), tol);
  } else if (refine == DGM::ErrProblem::ABSOLUTE) {
    Scalar tol(0.0001);
    comm->cout() << endl
                 << "Starting p-Refinement based on absolute tolerance "
                 << tol
                 << endl;
    pRefine_TOL(error.data(), error.size(), tol );
  }
}

/* To do list for pRefine():

   1) Fix up type differences between 'int' and 'unsigned int' mixed types -
      this is my own fault and is probably not good practice.

   2) Deal with efficientcy issues and work on parallelization (i kant spel) -
      this should be easy if one can determine how to parallelize quicksort()
      - even so, the quick sort is O(n lg n) which is decent for a sorting
      routine.

   3) Is the 20% heuristic decent or should this somehow be changed?
*/

void Estimate::pRefine_20(Scalar* err, int len) {
  string newfile = get_root_name() + ".ord.new";

  ofstream outfile;
  outfile.open(newfile.c_str());

  int top20;                 // Number of elements to refine (top 20%)
  int newP;                  // New value of p

  ErrorElmtInfo* elmts;      // Structure that contains element information
  int p;                     // Increment value and temporary value of p
  int refinedElmt;           // Element number of refined element

  outfile << "** p-Refinement Output -- Generated Automatically ** "
          << endl;

  /* Extract element information into the struct 'elmts' before sorting the
     errors. Once we sort the errors, we loose the element information. That
     is, the vector 'err' has been set up so that its value corresponds to the
     error at its index. For example, err[0] is the error of Element 0. When we
     sort the array, we will loose this information (i.e. err[0] will not
     necesserily correspond to the error at Element 0 any longer. Thus, we
     store this information so that we can use it after we sort the array.
*/

  elmts = new ErrorElmtInfo[len];
  for (int e = 0; e < len; e++) {
    elmts[e].elementNumber = e;
    elmts[e].error = err[e];
    err[e] = fabs(err[e]);    // We want to compare absolute values of errors
    elmts[e].marked = false;  // We mark elements that are to be refined
    elmts[e].output = false;  /* We mark elements once they have been outputed
                                 (to prevent repeats) */
    p = adjoint->domain()->U[0]->el[e]->get_p();
    elmts[e].pElement = p - p_inc;
  }

  /*
     Now, sort the error using a QuickSort - this is O(n lg(n)) at best. Since
     we will refine the top 20% of elements with high error, we set this value
     as well.
*/

  QuickSort<Scalar> qs(err);
  qs.Sort(0,len-1);

  top20 = (int)((0.2) * len);

  /* Now, we loop through the errors on the elements we desire to refine and
     assign a new polynomial order to these elements. Here, we make use of the
     match() method in the pRefineTools namespace. This method simply searches
     for the error of interest and matches that error to its corresponding
     element.

     The match() routine returns -1 if an error has occured.

     Once we have the error matched with its corresponding element, we output
     this data to the appropriate file so that our next run will refine the
     selected elements in p.
*/

  int start = len - top20;  // Starting value

  for (int i = start - 1; i < len; ++i) {
    refinedElement = ErrorElmtInfo::match(err[i], elmts, len);

    if (refinedElement == -1) {
      comm->cout() << "ERROR: p-Refinement Failed in pRefine()." << endl;
      exit(1);
    }

    comm->cout() << "Refining Element " << refinedElement << endl;

    newP = elmts[refinedElmt].pElement + p_ref;
    outfile << refinedElement << "    " << newP << "    0" << endl;
    elmts[refinedElmt].output = true;
  }

  // Now, we output the remaining elements

  for (int j = 0; j < len; j++) {
    // Element not refined or been outputed
    if ((!elmts[j].marked) && (!elmts[j].output)) {

      /* To do: Change class declaration and constructor to remove p - we only
         need to worry about p on each element rather than a global p passed
         through the command line. Also, once p is changed, change the value
         where we assign pElement to p. */

      outfile << j << "    " << elmts[j].pElement << "    0" << endl;
      elmts[j].output = true;
    }
  }

  /* Finally, we perform some good housekeeping procedures like good little
     C++ programmers :-) */

  delete [] elmts;
  outfile.close();
}


/* pRefineTol - Activates the tolerance p-refinement heuristic. Basically, you
   give this function a tolerance and it will check to see if each element
   divided by the total number of elements is less than a given tolerance. If
   so, we do nothing. Otherwise, we refine.
*/
void Estimate::pRefine_TOL(Scalar* err, int len, Scalar TOL) {
  string newfile = get_root_name() + ".ord.new";

  ofstream outfile;
  outfile.open(newfile.c_str());

  outfile << "** p-Refinement Output -- Generated Automatically ** "
          << endl;
  comm -> cout() << "Refinement tolerance: " << TOL << endl;

  Scalar check;
  int current_p, p;

  for (size_t i = 0; i < len; i++) {
    p = adjoint->domain()->U[0]->el[i]->get_p();
    current_p = p - p_inc;
    check = err[i]/len;
    // added additional diagnostic [SSC]
    // comm->cout() << i << " " << err[i] << " " << check << endl;
    if (fabs(check) < TOL)
      outfile << i << "    " << current_p << "    0" << endl; // Do nothing
    else {
      comm->cout() << "Refining Element " << i << endl;
      outfile << i << "    " << current_p + p_ref << "    0"
              << endl;  // Refine by p_ref
    }
  }
  outfile.close();
}

} // namespace DGM
