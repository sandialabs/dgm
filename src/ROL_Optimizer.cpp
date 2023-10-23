/** \file ROL_Optimizer.cpp
    \brief ROL Optimizer implementation
    \author Drew Kouri
    \author Denis Ridzal
    \author Bart van Bloemen Waanders
    \author Scott Collis
    \author Greg von Winckel
*/

#ifdef DGM_USE_ROL

// System includes
#include <ctime>
#include <cmath>

// DGM includes
#include "Comm.hpp"
#include "ROL_Optimizer.hpp"
#include "ROL_Factory.hpp"
#include "Format.hpp"
#include "Info.hpp"
#include "String.hpp"

#include "ROL_MaskedObjective.hpp"
#include "ROL_ParameterList.hpp"

// Set the default for debug output to "off"
#ifndef ROL_OPTIMIZER_DEBUG
#define ROL_OPTIMIZER_DEBUG 0
#endif

// Boost includes
#ifdef DGM_USE_BOOST_FS
#include "boost/filesystem.hpp"
#endif
#include "boost/numeric/conversion/cast.hpp"
using boost::numeric_cast;

namespace DGM {

ROL_Optimizer::ROL_Optimizer( State *state_, 
                              Adjoint *adjoint_,
                              Control::Ptr control_,
                              Control::Ptr diag_precond_,
                              Control::Ptr mask_,
                              const DGM::Comm::Ptr comm_)
  : Optimizer(state_, adjoint_, control_, comm_),
    algo_state_(0), step_(0), status_(0),
    output_type_(0), print_header_(false), screen_print_(false),
    useTrustRegion_(false),
    gtol_(0), stol_(0), gnorm_old_(0), fval_old_(0), fdorders_(),
    use_precond(true), reset_obj(0), verb(0), skip_update(false),
    root(control_->root), json(state->domain()->json_root)
{

  comm->cout() << "Building 1st order MaskedObjective ROL solvers...\n";

  setupParameters();
  
  // Initialize Gradient Vector
  gradient.reset(control_->clone());
  gradient->control_type(Control::GRADIENT);
  gradient->zero();

  // Initialize Time Regularized Control Vector
#ifdef DGM_USE_TIME_REG
  gt_control.reset(control_->clone());
  gt_control->control_type(Control::GRADIENT);
  gt_control->zero();
#endif

  // ROL Algorithm State
  algo_state_ = ROL::makePtr<ROL::AlgorithmState<Scalar>>();
  algo_state_->iter = 1;


    obj_ = ROL::makePtr<ROLinterface::MaskedObjective<Scalar>>( state,
                                                                adjoint,
                                                                gradient,
                                                                params, 
                                                                diag_precond_,
                                                                mask_,
                                                                this ); 

  // Sanity check on parameters
  if (comm->verbosity()) {
    header(comm->cout(),"Begin ROL parameters");
    comm->cout() << parlist_;
    header(comm->cout(),"End ROL parameters");
    comm->cout() << "ROL_Optimizer is using npredict = " << npredict << "\n";
  }

  // it is a good idea to initialize everything
  control->initialize();
  diag_precond->initialize();
  mask->initialize();
  gradient->initialize();
  state->initialize();
  adjoint->initialize();
#ifdef DGM_USE_TIME_REG
  gt_control->initialize();
#endif

  comm->cout() << "Completed ROL_Optimizer (1st order MaskedObjective) construction\n";
}



ROL_Optimizer::ROL_Optimizer( State *state_, Adjoint *adjoint_,
                              Control::Ptr control_,
                              Preconditioner::Ptr preconditioner_,
                              const DGM::Comm::Ptr comm_) :
    Optimizer(state_,adjoint_,control_,comm_),
    algo_state_(0), step_(0), status_(0),
    output_type_(0), print_header_(false), screen_print_(false),
    useTrustRegion_(false),
    gtol_(0), stol_(0), gnorm_old_(0), fval_old_(0), fdorders_(),
    use_precond(false), reset_obj(0), verb(0), skip_update(false),
    root(control_->root), json(state->domain()->json_root)
{

  comm->cout() << "Building 1st order ROL solvers...\n";

  setupParameters();
  
  // Initialize Gradient Vector
  gradient.reset(control->clone());
  gradient->control_type(Control::GRADIENT);
  gradient->zero();

  // Initialize Diagonal Preconditioner
  diag_precond.reset(control->clone());
  diag_precond->control_type(Control::GRADIENT);
  diag_precond->zero();

  // Initialize Time Regularized Control Vector
#ifdef DGM_USE_TIME_REG
  gt_control.reset(control->clone());
  gt_control->control_type(Control::GRADIENT);
  gt_control->zero();
#endif

  // ROL Algorithm State
  algo_state_ = ROL::makePtr<ROL::AlgorithmState<Scalar>>();
  algo_state_->iter = 1;

   obj_ = ROL::makePtr<ROLinterface::Objective<Scalar>>(state,adjoint,gradient,
          params, diag_precond, this);

  // Sanity check on parameters
  if (comm->verbosity()) {
    header(comm->cout(),"Begin ROL parameters");
    comm->cout() << parlist_;
    header(comm->cout(),"End ROL parameters");
    comm->cout() << "ROL_Optimizer is using npredict = " << npredict << "\n";
  }

  // it is a good idea to initialize everything
  control->initialize();
  gradient->initialize();
  state->initialize();
  adjoint->initialize();
#ifdef DGM_USE_TIME_REG
  gt_control->initialize();
#endif

  // this is extraneous (but left in as it might be nice in the future)
  resetPreconditioner( preconditioner_ );

  comm->cout() << "Completed ROL_Optimizer (1st order) construction\n";
}






// Constructor for second order algorithms
ROL_Optimizer::ROL_Optimizer(State *state_, Adjoint *adjoint_,
                             Control::Ptr control_,
                             State *aux_state, Adjoint *aux_adjoint,
                             Preconditioner::Ptr preconditioner_,
                             const DGM::Comm::Ptr comm_)
  : Optimizer(state_,adjoint_,control_,comm_),
    algo_state_(0), step_(0), status_(0),
    aux_state_(aux_state), aux_adjoint_(aux_adjoint),
    output_type_(0), print_header_(false), screen_print_(false),
    useTrustRegion_(false),
    gtol_(0), stol_(0), gnorm_old_(0), fval_old_(0), fdorders_(),
    use_precond(false), reset_obj(0), verb(0), skip_update(false),
    root(control_->root), json(state->domain()->json_root)
{
  comm->cout() << "Building 2nd order ROL solvers...\n";

  setupParameters();
  
  // Initialize Gradient Vector
  gradient.reset(control->clone());
  gradient->control_type(Control::GRADIENT);
  gradient->zero();

  // Initialize Diagonal Preconditioner
  diag_precond.reset(control->clone());
  diag_precond->control_type(Control::GRADIENT);
  diag_precond->zero();

  // Initialize Time Regularized Control Vector
#ifdef DGM_USE_TIME_REG
  gt_control.reset(control->clone());
  gt_control->control_type(Control::GRADIENT);
  gt_control->zero();
#endif

  // ROL Algorithm State
  algo_state_ = ROL::makePtr<ROL::AlgorithmState<Scalar>>();
  algo_state_->iter = 1;

   obj_ = ROL::makePtr<ROLinterface::Objective<Scalar>>(state,adjoint,gradient,
          aux_state_,aux_adjoint_,params, diag_precond, this);

  // Sanity check on parameters
  if (comm->verbosity()) {
    header(comm->cout(),"Begin ROL parameters");
    comm->cout() << parlist_;
    header(comm->cout(),"End ROL parameters");
    comm->cout() << "ROL_Optimizer is using npredict = " << npredict << "\n";
  }

  // it is a good idea to initialize everything
  control->initialize();
  gradient->initialize();
  state->initialize();
  adjoint->initialize();
  aux_state_->initialize();
  aux_adjoint_->initialize();
#ifdef DGM_USE_TIME_REG
  gt_control->initialize();
#endif

  // set the preconditioner on the Adjoint
  adjoint->set_preconditioner(diag_precond);
  aux_adjoint->set_preconditioner(diag_precond);

  // this is extraneous (but left in as it might be nice in the future)
  resetPreconditioner( preconditioner_ );

  comm->cout() << "Completed ROL_Optimizer (2nd order) construction\n";
}

// Print ROL-style output to root.ocs.  This also appends a time stamp.
void ROL_Optimizer::rol_style_output(bool printHeader, string ext) {
  // Open output ocs file
  std::string name = root + ext;
  FILE* file = fopen(name.c_str(),"a+");
  // Get time of day
  time_t rawtime;
  time(&rawtime);
  // Get iteration output - tweak to look more like DGM
  Real gnorm = algo_state_->gnorm;
  if(algo_state_->iter==1) {
    algo_state_->gnorm=0;
  }
  algo_state_->iter--;
  std::string out = step_->print(*algo_state_,printHeader);
  algo_state_->gnorm = gnorm;
  algo_state_->iter++;
  if(algo_state_->iter == 1) 
    out = step_->printName() + out; 
  // Print to file
  if ( printHeader ) {
    fprintf(file, "%s",out.c_str());
  } else {
    out.erase(out.end()-2,out.end());
    fprintf(file, "%s %11.4e %s",out.c_str(),timer.read(),ctime(&rawtime));
  }
  fflush(file);
  fclose(file);
}

// Print DGM-style output to root.ocs.  This also appends a time stamp.
void ROL_Optimizer::dgm_style_output(bool printHeader, string ext) {
  Scalar gnorm = algo_state_->gnorm;
  if(algo_state_->iter==1) algo_state_->gnorm = 0;

  // Open output ocs file
  std::string name = root + ext;
  FILE* file = fopen(name.c_str(),"a+");
  // Get time of day
  time_t rawtime;
  time(&rawtime);

  // Print iteration information
  if ( printHeader ) {
    fprintf(file, "VARIABLES=\"iter\" \"J\"  \"NormG\" \"Alpha\" \"NormS\" "
                  " \"Time\" \"fnum\" \"gnum\" \n");
    //fprintf(file,"%5d %11.4e %11.4e %11.4e %11.4e %11.4e %5d %5d \t %s",
    //        0, algo_state_->value, 0.0, 0.0, 0.0, timer.read(), 
    //        1, 0, ctime(&rawtime));
  }

  ROL::Ptr<const ROL::StepState<Scalar> >
    step_state = step_->getStepState();

  const Scalar snorm =
    defined<Scalar>(algo_state_->snorm) ? algo_state_->snorm : 0.0;

  fprintf(file,"%5lld %11.4e %11.4e %11.4e %11.4e %11.4e %5lld %5lld \t %s",
    numeric_cast<long long>(algo_state_->iter-1), algo_state_->value,
               algo_state_->gnorm,
               step_state->searchSize,
               snorm,
               timer.read(),
    numeric_cast<long long>(algo_state_->nfval),
    numeric_cast<long long>(algo_state_->ngrad),
    ctime(&rawtime));

  algo_state_->gnorm = gnorm;
  fflush(file);
  fclose(file);
}

// Print PEopt-style output to root.ocs.  This also appends a time stamp.
void ROL_Optimizer::peopt_style_output(bool printHeader, string ext) {
  // Open output ocs file
  std::string name = root + ext;
  FILE* file = fopen(name.c_str(),"a+");
  // Get time of day
  time_t rawtime;
  time(&rawtime);
  // Print iteration information
  if ( printHeader ) {
    std::ostringstream hout;
    hout << std::setw(10) << std::left << "Iter"
         << std::setw(10) << std::left << "f(x)"
         << std::setw(10) << std::left << "merit(x)"
         << std::setw(10) << std::left << "||grad||"
         << std::setw(10) << std::left << "alpha"
         << std::setw(10) << std::left << "||dx||"
         << std::setw(10) << std::left << "WallTime"
         << std::endl;
    fprintf(file, "%s",hout.str().c_str());
  }
  ROL::Ptr<const ROL::StepState<Scalar> >
    step_state = step_->getStepState();
  const Scalar snorm =
    defined<Scalar>(algo_state_->snorm) ? algo_state_->snorm : 0.0;
  std::ostringstream out;
  out << std::setw(10) << std::left << algo_state_->iter
      << std::setprecision(2) << std::scientific
      << std::setw(10) << std::left << algo_state_->value
      << std::setprecision(2) << std::scientific
      << std::setw(10) << std::left << algo_state_->value
      << std::setprecision(2) << std::scientific
      << std::setw(10) << std::left << algo_state_->gnorm
      << std::setprecision(2) << std::scientific
      << std::setw(10) << std::left << step_state->searchSize
      << std::setprecision(2) << std::scientific
      << std::setw(10) << std::left << snorm
      << std::setprecision(2) << std::scientific
      << std::setw(10) << std::left << timer.read()
      << std::setw(10) << std::left << ctime(&rawtime);
  fprintf(file, "%s",out.str().c_str());
  fflush(file);
  fclose(file);
}

// Function which prints output
void ROL_Optimizer::print_output(bool printHeader) {
  if (verb>1) comm->cout() << "print_output("<<printHeader<<")"<<endl;
  // optionall print ROL output to screen
  if (screen_print_) comm->cout() << step_->print(*algo_state_,printHeader);
  // Print output to file
  if (comm->Master()) {
    // always output RoL optimization statistics
    rol_style_output(printHeader,".ros");
    switch ( output_type_ ) {
      case 0: rol_style_output(printHeader);   break;
      case 1: dgm_style_output(printHeader);   break;
      case 2: peopt_style_output(printHeader); break;
    }
  }
  // Write the control restart file
  writeRestart();
}

void ROL_Optimizer::set_max_iter(const Ordinal i) {
  Optimizer::set_max_iter(i);
  // Read Restart File, set correct iteration number
  iter = algo_state_->iter = numeric_cast<int>(readRestart()+1);
  status_ = ROL::makePtr<ROL::StatusTest<Scalar>>(gtol_, stol_, i);
  skip_update = true;
}

/// Solve optimization problem
/** Main Optimizer method that initializes and solves the optimization
    problem to the requested tolerance or maximum number of iterations

    \note Input parameter is currently ignored
*/
void ROL_Optimizer::optimize(const Ordinal) {

  static Format sci(8); sci.scientific().width(15);

  // Read Restart File
  if (!skip_update)
    algo_state_->iter = numeric_cast<int>(readRestart());


  // Initialize Gradient Vector
  Control::Ptr step;
  step.reset(control->clone());
  step->control_type(Control::STEP);
  step->zero();

  // Initialize ROL DGM Vector
  ROLinterface::Vector<Scalar> x(control);
  ROLinterface::Vector<Scalar> s(step);
  ROLinterface::Vector<Scalar> g(gradient);

  // Initialize Current Iterate Container
  if ( is_nullPtr( algo_state_->iterateVec)  ) {
    algo_state_->iterateVec = x.clone();
    algo_state_->iterateVec->set(x);
  }

  // Initialize (Dummy) Constraint
  ROL::BoundConstraint<Scalar> con;
  con.deactivate();

  // Start Timer
  timer.start();
  
  if(split_update_) { 
    ROL::Ptr<SplitUpdateLineSearchStep<Scalar> > split_step = 
      ROL::dynamicPtrCast<SplitUpdateLineSearchStep<Scalar> >(step_);
    if ( ROL::is_nullPtr( split_step)) 
      throw DGM::exception("ROL_Optimizer::optimize ROL::dynamicPtrCast failed, split_step is null pointer");

    // Store previous function value and gradient norm
    fval_old_  = algo_state_->value;
    gnorm_old_ = algo_state_->gnorm;

    printBanner();

    if(reset_obj) {
      obj_->reset(x,algo_state_->iter);
    }
    
    // INITIALIZE Step
    split_step->initialize(x, s, g, *obj_, con, *algo_state_);

    // Print optimization iteration and write restart file
    print_output( algo_state_->iter==1 ? true : print_header_);

    // COMPUTE Step vector
    split_step->compute(s, x, *obj_, con, *algo_state_);

    // UPDATE Optimization vector
    split_step->updateVector(x, s, *obj_, con, *algo_state_);

    // Bound controls -- this is ad hoc
    control->bound();
    if ( !control->realizable() ) {
      comm->cout() << "WARNING:  Your step is invalid..."<<endl;
    }

    if(grad_check) {
      check_grad();
      if (grad_check > 1) comm->exit(0);
    }

    // Run Algorithm
    while (status_->check(*algo_state_)) {
    
      // Print optimization iteration and write restart file
      print_output( algo_state_->iter==1 ? true : print_header_);

      printBanner();

      // Store previous function value and gradient norm
      fval_old_  = algo_state_->value;
      gnorm_old_ = algo_state_->gnorm;

      if(reset_obj) {
        obj_->reset(x,algo_state_->iter);
      }
    
      // UPDATE Objective value and gradient
      split_step->updateObjective(x, s, *obj_, con, *algo_state_);
      
      // COMPUTE Step vector
      split_step->compute(s, x, *obj_, con, *algo_state_);

      // UPDATE Optimization vector
      split_step->updateVector(x, s, *obj_, con, *algo_state_);

      // Bound controls -- this is ad hoc
      control->bound();
      if ( !control->realizable() ) {
        comm->cout() << "WARNING:  Your step is invalid..."<<endl;
      }

      if(grad_check) {
        check_grad();
        if (grad_check > 1) comm->exit(0);
      }

    }
    // Print optimization iteration and write restart file
    print_output( algo_state_->iter==1 ? true : print_header_);


  }
  else { // !split_update_

    printBanner();

    // RESET Objective
    if(reset_obj) {
      obj_->reset(x,algo_state_->iter);
    }

    // INITIALIZE Step
    step_->initialize(x, s, g, *obj_, con, *algo_state_);

    // Print optimization iteration and write restart file
    print_output( algo_state_->iter==1 ? true : print_header_);


    if(grad_check) {
      check_grad();
      if (grad_check > 1) comm->exit(0);
    }

    // Run Algorithm
    while (status_->check(*algo_state_)) {

      // Store previous function value and gradient norm
      fval_old_  = algo_state_->value;
      gnorm_old_ = algo_state_->gnorm;

      // COMPUTE descent direction and update iterate
      if (verb) header(cout,"C o m p u t e   d e s c e n t   d i r e c t i o n");
      step_->compute(s, x, *obj_, con, *algo_state_);

      if (verb) header(cout,"U p d a t e   t h e   c o n t r o l");
      if (verb) header(cout,"F i n i s h e d   a   s t e p");
      // Bound controls -- this is ad hoc
      control->bound();
      if ( !control->realizable() ) {
        comm->cout() << "WARNING:  Your step is invalid..."<<endl;
      }

      printBanner();

     // RESET Objective
     if(reset_obj) {
       obj_->reset(x,algo_state_->iter);
     }

   
      // UPDATE Optimization Vector
      // UPDATE Objective
      step_->update(x, s, *obj_, con, *algo_state_);

      // Print optimization iteration and write restart file
      print_output( algo_state_->iter==1 ? true : print_header_);



    } // while(status_->check(*algo_state_)) 
  } // end(split_update_)


#if 0
  // Reset to objective function
  if(reset_obj) {
    obj_->reset(x,algo_state_->iter);
  }

  // Initialize Step
  step_->initialize(x, s, g, *obj_, con, *algo_state_);

  // Print optimization iteration and write restart file
  // print_output( algo_state_->iter==1 ? true : print_header_);

  if(grad_check) {
    check_grad();
    if (grad_check > 1) comm->exit(0);
  }


  // Run Algorithm
  while (status_->check(*algo_state_)) {

    // Store previous function value and gradient norm
    fval_old_  = algo_state_->value;
    gnorm_old_ = algo_state_->gnorm;

    // compute descent direction and update iterate
    if (verb) header(cout,"C o m p u t e   d e s c e n t   d i r e c t i o n");
    step_->compute(s, x, *obj_, con, *algo_state_);
    if (verb) header(cout,"U p d a t e   t h e   c o n t r o l");
    if (verb) header(cout,"F i n i s h e d   a   s t e p");
    // Bound controls -- this is ad hoc
    control->bound();
    if ( !control->realizable() ) {
      comm->cout() << "WARNING:  Your step is invalid..."<<endl;
    }
/*
    // take the step
    x.plus(s);     

    // Compute new gradient
    obj_->update(x,true,algo_state_->iter);

   // output the results
    print_output( algo_state_->iter==1 ? true : print_header_);
    // undue the step
    s.scale(-1.0);
    x.plus(s);
    s.scale(-1.0);
    // Reset to objective function
    if(reset_obj) {
      obj_->reset(x,algo_state_->iter);
      comm->cout() << "Resetting objective" << std::endl;
    }
*/
    // Iteration banner
    comm->cout()
      <<"===================================================================="
      <<endl<<"ROL Optimization iteration = "<< algo_state_->iter+1 << endl
      <<"===================================================================="
      <<endl;

    if(split_update_) { // Manually perform the step update in stages

      ROL::Ptr<SplitUpdateLineSearchStep<Scalar> > split_step = 
        Teuchos::ROL::dynamicPtrCast<SplitUpdateLineSearchStep<Scalar> >(step_);

      split_step->updateVector(x,s,*algo_state_);

      split_step->updateObjective(x,*obj_,*algo_state_);
    }
    else {
      step_->update(x, s, *obj_, con, *algo_state_);
    }
  }
  // Print optimization iteration and write restart file
  print_output( algo_state_->iter==1 ? true : print_header_);
#endif
}

void ROL_Optimizer::test_vector() {
  // Fill x with ones
  Control::Ptr x1_p;
  x1_p.reset(control->clone());
  using DGM::fill;
  fill(1.0,x1_p);
  ROLinterface::Vector<Scalar> x1(x1_p);
  Scalar xnorm = x1.norm();
  comm->cout() << "\nNorm of ROL_DGM_Vector x: " << xnorm << "\n";

  // Fill y with twos
  Control::Ptr y1_p;
  y1_p.reset(control->clone());
  using DGM::fill;
  fill(2.0,y1_p);
  ROLinterface::Vector<Scalar> y1(y1_p);
  Scalar ynorm = y1.norm();
  comm->cout() << "\nNorm of ROL_DGM_Vector y: " << ynorm << "\n";

  x1.scale(0.5);
  Scalar xnorm2 = x1.norm();
  comm->cout() << "\nNorm of half of x: " << xnorm2 << "\n";
  if ( std::abs(xnorm/xnorm2 - 2.0) > 1.e-8 ) {
    comm->cout() << "---> POSSIBLE ERROR ABOVE!\n";
  };

  ROL::Ptr<ROL::Vector<Scalar> > z = x1.clone();
  z->set(x1);
  Scalar znorm = z->norm();
  comm->cout() << "\nNorm of ROL::Vector z (clone of x): " << znorm << "\n";
  if ( std::abs(xnorm2 - znorm) > 1.e-8 ) {
    comm->cout() << "---> POSSIBLE ERROR ABOVE!\n";
  };

  z->set(x1);
  x1.scale(-1.0);
  z->plus(x1);
  y1.zero();
  z->axpy(-1.0, y1);
  znorm = z->norm();
  comm->cout() << "\nNorm of (x - x) - 0: " << znorm << "\n";
  if ( std::abs(znorm) > 1.e-8 ) {
    comm->cout() << "---> POSSIBLE ERROR ABOVE!\n";
  };
}

/// Advance the solution
Scalar ROL_Optimizer::advance(const Ordinal outer) {
  // don't advance if done
  if (!status_->check(*algo_state_)) return 0;
  // Check: if Control unsteady && nadvance>npredict,  Error!!
  if(!(control->steady()) && nadvance%npredict!=0){
    comm->cerr()<<"Error: nadvance > npredict for the unsteady control\n";
    comm->exit(DGM::FAILURE);
  }
  state->set_initial_condition();
#ifndef DGM_USE_TIME_REG
  return state->advance(nadvance, control, outer);
#else
  return state->advance(nadvance, gt_control, control, outer);
#endif
}

/// Check the adjoint gradient quality using directional finite difference
void ROL_Optimizer::check_grad() {
  Format sci(10); sci.scientific().width(17);
  Format percent(2); percent.fixed().width(6);

  comm->cout() << "ROL_Optimizer::check_grad()"<<endl;
  //comm->cout() << "ROL_Optimizer::check_grad() with fdorders.size() = "
  //             << fdorders_.size() << endl;

  // set a new arbitrary direction
  Control::Ptr dir_control;
  dir_control.reset(control->clone());
  dir_control->control_type(Control::STEP);
  dir_control->set_direction();

  // SSC added this
  ROLinterface::Vector<Scalar> g(gradient);


  // Number of sweep steps in checking the gradient
  int numSteps = gclist_.get("Number of Steps", 1);

  // Largest step to take in the sweep
  double largestStep = gclist_.get("Largest Step", fd_eps);

  // Factor to reduce the step size by
  double stepReduction = gclist_.get("Reduction Factor", 1.0e-1);

  std::vector<Scalar> steps(numSteps,largestStep);
  
  for(int i=1;i<numSteps;++i) {
    steps[i] = stepReduction * steps[i-1];
  }

  // run derivative check(s)
  ROLinterface::Vector<Scalar> x(control);
  ROLinterface::Vector<Scalar> d(dir_control);
  
  for(unsigned i=0;i<fdorders_.size();++i) {

    unsigned order = fdorders_[i];

    std::vector<std::vector<Scalar> >
    output = obj_->checkGradient(x,g,d,steps,false,std::cout,order);
    
    comm->cout() << "\nCheck gradient with finite differences of order "
                << order << "\n";
    
    // Print output
    comm->cout() << std::right
    << std::setw(20) << "Step size"
    << std::setw(20) << "grad'*dir"
    << std::setw(20) << "FD approx"
    << std::setw(20) << "abs error"
    << std::setw(20) << "rel error"
    << "\n";
    for (unsigned i = 0; i < output.size(); i++ ) {
      comm->cout() << std::scientific << std::setprecision(8) << std::right
      << std::setw(20) << output[i][0]
      << std::setw(20) << output[i][1]
      << std::setw(20) << output[i][2]
      << std::setw(20) << output[i][3]
      << std::setw(20) << output[i][3]/std::abs(output[i][1])
      << "\n";
    }
    comm->cout() << "\n";
  }
}

//==============================================================================
//                            Restart file I/O
//==============================================================================

// Write the optimization restart file
void ROL_Optimizer::writeRestart(const string *ctl) const {
  streamoff skip;
  string fname;
  if (ctl) {
    fname = *ctl;
  } else {
    char tmp[80];
    sprintf(tmp,".%lld",(long long)algo_state_->iter);
    fname = root+tmp+".ctl";
  }
  ctl_comm->cout()<<"Writing control restart file "<<fname<<".\n";
  skip = writeJsonHeader(fname);
  skip = control->write(fname,skip);
#ifdef DGM_USE_TIME_REG
  skip = gt_control_->write(fname,skip);
#endif
  skip = gradient->write(fname,skip);
}

/// Read the optimization restart file
Ordinal ROL_Optimizer::readRestart(streamoff &skip, const string *ctl) {
  Ordinal riter=0;
  string format, fname;
  if (ctl)
    fname = *ctl;
  else
    fname = root+".ctl";
  skip = readJsonHeader(fname,riter);
  if (riter==0) return 1;
  comm->cout() << "Restarting optimization from " << fname << ".\n";
  skip = control->read(fname,skip);
#ifdef DGM_USE_TIME_REG
  skip = gt_control->read(fname,skip);
#endif
  skip = gradient->read(fname,skip);
  return riter;
}

// Original readRestart interface
Ordinal ROL_Optimizer::readRestart(const string *ctl) {
  streamoff skip(0);
  return readRestart(skip,ctl);
}

/// Read the optimization Json header
streamoff ROL_Optimizer::readJsonHeader(const string &fname, Ordinal &riter) {
  const int verb=0;
  if (verb>1) comm->cout()<<"ROL_Optimizer::readJsonHeader("<<fname<<")\n";
  ifstream fs(fname.c_str());
  if (!fs) {
    timer.reset();
    riter = 0;
    return 0;
  }
  char c = fs.peek();
  if (!fs) throw DGM::exception("Cannot read Json header from "+fname);
  if (c!='{') {
    throw DGM::exception("Error reading Json header from "+fname);
  } else {
    string token;
    if (!(fs >> token))
      throw DGM::exception("Error reading Json header from "+fname);
  }
  Json::Value header;
  string buffer = read_block(fs);
  const int status = scan_rb(fs);
  if (status) comm->error("Could not find closing bracket for Json header "
                          " on file "+fname);
  if (verb>2)
    comm->cout() << "Read header from " << fname << "\n" << buffer << "\n";
  Json::Reader reader;
  bool parsingSuccessful = reader.parse( buffer, header, true );
  if (!parsingSuccessful)
    comm->error("ROL_Optimizer readJsonHeader could not parse input from "+
                fname+"\n"+reader.getFormattedErrorMessages());
  getline(fs,buffer);
  if (fs.fail())
    throw DGM::exception("Could not read Json data from file "+fname);
  if (fs.bad())
    throw DGM::exception("Stream is bad when reading Json data "
                         "from file "+fname);
  if (fs.eof())
    throw DGM::exception("End of file encountered when reading from "+fname);

  // extract information from Json header
  if (!header.isMember("Iteration"))
    throw DGM::exception("Header is missing \"Iteration\" from file "+fname);
  riter = numeric_cast<Ordinal>(header["Iteration"].asUInt64());

  if (!header.isMember("Wall time"))
    throw DGM::exception("Header is missing \"Wall time\" from file "+fname);
  timer.reset(header["Wall time"].asDouble());

  if (!header.isMember("Objective function"))
    throw DGM::exception("Header is missing \"Objective function\" "
                         "from file "+fname);
  algo_state_->value =
    numeric_cast<Scalar>(header["Objective function"].asDouble());

  // ROL Optimizer block
  if (!header.isMember("ROL_Optimizer"))
    throw DGM::exception("Header missing \"ROL_Optimizer\" block from "
                         "file "+fname);
  Json::Value &rolopt = header["ROL_Optimizer"];
  if (!rolopt.isMember("||Grad(J)||"))
    throw DGM::exception("Header is missing \"||Grad(J)||\""
                         " from file "+fname);
  algo_state_->gnorm =
    numeric_cast<Scalar>(rolopt["||Grad(J)||"].asDouble());

  if (!rolopt.isMember("Number of Function Evaluations"))
    throw DGM::exception("Header is missing \"Number of Function Evaluations\""
                         " from file "+fname);
  algo_state_->nfval =
    numeric_cast<int>(rolopt["Number of Function Evaluations"].asInt64());

  if (!rolopt.isMember("Number of Gradient Computations"))
    throw DGM::exception("Header is missing \"Number of Gradient Computations\""
                         " from file "+fname);
  algo_state_->ngrad =
    numeric_cast<int>(rolopt["Number of Gradient Computations"].asInt64());

  if (!rolopt.isMember("Linesearch step size"))
    throw DGM::exception("Header missing \"ROL_Optimizer::Linesearch step\" "
                         "size from file "+fname);
  alpha_ = numeric_cast<Scalar>(rolopt["Linesearch step size"].asDouble());

  // Types block
  if (!header.isMember("Types"))
    throw DGM::exception("Header missing \"Types\" block from "
                         "file "+fname);
  Json::Value &types = header["Types"];
  if (!types.isMember("GlobalSize"))
    throw DGM::exception("Header is missing \"GlobalSize\""
                         " from file "+fname);
#if 0
  if (types["GlobalSize"].asString() != type<DGM::Size>() )
    throw DGM::exception("Control restart file "+fname+" is incompatible: "
                         "GlobalSize = "+types["GlobalSize"].asString()+
                         "\n  while code expects "+type<DGM::Size>());
#endif
  if (!types.isMember("LocalSize"))
    throw DGM::exception("Header is missing \"LocalSize\""
                         " from file "+fname);
#if 0
  if (types["LocalSize"].asString() != type<DGM::Ordinal>() )
    throw DGM::exception("Control restart file "+fname+" is incompatible: "
                         "LocalSize = "+types["LocalSize"].asString()+
                         "\n  while code expects "+type<DGM::Ordinal>());
#endif
  if (!types.isMember("Scalar"))
    throw DGM::exception("Header is missing \"Scalar\""
                         " from file "+fname);
  if (types["Scalar"].asString() != type<DGM::Scalar>() )
    throw DGM::exception("Control restart file "+fname+" is incompatible: "
                         "Scalar = "+types["Scalar"].asString()+
                         "\n  while code expects "+type<DGM::Scalar>());
  // check the byte order
  if (types.isMember("ByteOrder")) {
    DGM::ByteOrder byteOrder;
    if (!byteOrder.is(types["ByteOrder"].asString())) {
      throw DGM::exception("Optimizer ctl file "+fname+" is incompatible: "
                           "ByteOrder = "+types["ByteOrder"].asString()+
                           "\n  while code requires "+byteOrder.asString());
    }
  }

  streamoff disp = fs.tellg();
  if (verb>2) comm->cout() << "ROL_Optimizer::readJsonHeader(" << fname <<
    ") with displacement = " << disp << "\n";
  return disp;
}

// Write the optimization Json header
streamoff ROL_Optimizer::writeJsonHeader(const string &fname) const {
  const int verb=comm->verbosity();
  if (verb)
    ctl_comm->cout() << "ROL_Optimizer::writeJsonHeader("<<fname<<")" << "\n";
  streamoff disp=0;
  const int buflen=128;
  char now[buflen] = "Time is not available";
  if (ctl_comm->Master()) {
    ofstream fs(fname.c_str());
    if (!fs) throw DGM::exception("ROL_Optimizer::writeJsonHeader could not "
                                  "open file name "+fname);
#if !defined(DGM_NO_TIME)
    time_t tp = ::time(0);
    strftime(now,buflen,"%a %b %d %H:%M:%S %Y", localtime(&tp));
#endif
    Json::Value header;
    header["File created"] = now;
    header["Root file name"] = root;
    header["Number of processors"] = ctl_comm->NumProc();
    header["Restart file name"] = fname;
    header["Executable"] = control->code;

    header["DGM library"] = Json::Value(Json::objectValue);
    header["DGM library"]["Version"] = DGM::Comm::information.version();
    header["DGM library"]["Build date"] = DGM::Comm::information.date();
    header["DGM library"]["Build time"] = DGM::Comm::information.time();
    header["DGM library"]["Compiler"] = DGM::Comm::information.compiler();
    header["DGM library"]["Host name"] = DGM::Comm::information.hostname();
    header["DGM library"]["System"] = DGM::Comm::information.system();

    header["Iteration"] = algo_state_->iter;
    header["Wall time"] = timer.read();
    header["Objective function"] = algo_state_->value;
    header["Norm of the gradient"] = algo_state_->gnorm;
    header["Npredict"] = npredict;
    header["Time steps"] = npredict + 1;

    header["ROL_Optimizer"] = Json::Value(Json::objectValue);
    header["ROL_Optimizer"]["||Grad(J)||"] = algo_state_->gnorm;
    header["ROL_Optimizer"]["||Grad(J_prior)||"] = gnorm_old_;
    header["ROL_Optimizer"]["J"] = algo_state_->value;
    header["ROL_Optimizer"]["J_prior"] = fval_old_;
    ROL::Ptr<const ROL::StepState<Real> > step_state = step_->getStepState();
    header["ROL_Optimizer"]["Linesearch step size"] = step_state->searchSize;
    header["ROL_Optimizer"]["Number of Function Evaluations"] = algo_state_->nfval;
    header["ROL_Optimizer"]["Number of Gradient Computations"] = algo_state_->ngrad;

    // control information
    header["Control"] = Json::Value(Json::objectValue);
    header["Control"]["Number"] = control->num_ctrl();
    vector<string> names = control->names();
    header["Control"]["Names"] = Json::Value(Json::arrayValue);
    header["Control"]["Names"].resize(
      numeric_cast<Json::ArrayIndex>(names.size()));
    for (size_t i=0; i<names.size(); ++i) {
      const Json::ArrayIndex m = numeric_cast<Json::ArrayIndex>(i);
      header["Control"]["Names"][m] = names[i];
    }
    header["Control"]["Global control length"] = control->global_size();

    // type information
    header["Types"] = Json::Value(Json::objectValue);
    header["Types"]["GlobalSize"] = type<DGM::Size>();
    header["Types"]["LocalSize"] = type<DGM::Ordinal>();
    header["Types"]["Scalar"] = type<DGM::Scalar>();
    DGM::ByteOrder byteOrder;
    header["Types"]["ByteOrder"] = byteOrder.asString();

    Json::StyledWriter writer;
    string output = writer.write(header);
    if (!fs)
      throw DGM::exception("ROL_Optimizer::writeJsonHeader file stream in bad "
                           "state for restart file "+fname);
    fs << output;
    if (!fs) throw DGM::exception("ROL_Optimizer::writeJsonHeader could not "
                                  "write header to restart file "+fname);
    disp = fs.tellp();
  }
  const int stat = ctl_comm->Broadcast(&disp);
  if (stat) throw DGM::exception("ROL_Optimizer::writeJsonHeader: error in "
                                 "broadcast of displacement");
  if (verb>2)
    ctl_comm->cout() << "ROL_Optimizer::writeJsonHeader("<<fname
                     <<") completed with disp = " << disp <<" bytes\n";
  return disp;
}

void ROL_Optimizer::plotControl(const Ordinal ntout,
                                const Ordinal riter) const {
  control->plot(ntout, riter);
}

void ROL_Optimizer::plotGradient(const Ordinal ntout,
                                 const Ordinal riter) const {
  string ext("grd");
  gradient->plot(ntout, riter, &ext);
}

void ROL_Optimizer::printBanner() const {
  comm->cout()
    <<"===================================================================="
    <<endl<<"ROL Optimization iteration = "<<algo_state_->iter<<endl
    <<"===================================================================="
    <<endl;
}

int ROL_Optimizer::diff(const string& ctl1, const string& ctl2,
                        const Scalar aeps, const Scalar reps)
{
  Ordinal riter1 = 0, riter2 = 0;
  streamoff skip1 = 0, skip2 = 0;

  skip1 = readJsonHeader(ctl1, riter1);
  skip2 = readJsonHeader(ctl2, riter2);

  // second control
  Control::Ptr control_2(control->clone());
  // read first control
  control->read(ctl1, skip1);
  // read second control
  control_2->read(ctl2, skip2);
  // compute diff
  return control->diff(*control_2, aeps, reps);
}

int ROL_Optimizer::sum(const double mult,
      const vector<Size> &sub_to_mstr, Optimizer *optimizer) 
{
  ROL_Optimizer* optimizer1 = this;
  ROL_Optimizer* optimizer2 = dynamic_cast<ROL_Optimizer*>(optimizer);
  if (!optimizer2) 
     throw DGM::exception("ROL_Optimizer::sum could not dynamic "
        "cast Optimizer to ROL_Optimizer.");

  optimizer1->algo_state_->iter = 0;
  optimizer2->algo_state_->iter = 0;

  Control* control1 = optimizer1->getControl();
  Control* control2 = optimizer2->getControl();

  const int ret = control1->sum(*control2, mult, sub_to_mstr);
  return ret;
}

int ROL_Optimizer::sum(const double mult)
{
  const vector<Size> sub_to_mstr;
  ROL_Optimizer* optimizer1 = this;
  optimizer1->algo_state_->iter = 0;
  Control* control1 = optimizer1->getControl();
  Control* control2 = optimizer1->getDirControl();
  int ret = 0;
  if (control2) control1->sum(*control2, mult, sub_to_mstr);
  return ret;
}

int ROL_Optimizer::ext(const vector<Size> &sub_to_mstr, Optimizer *optimizer) 
{
  ROL_Optimizer* optimizer1 = this;
  ROL_Optimizer* optimizer2 = dynamic_cast<ROL_Optimizer*>(optimizer);
  if (!optimizer2) 
     throw DGM::exception("ROL_Optimizer::ext could not dynamic "
        "cast Optimizer to ROL_Optimizer.");

  optimizer1->algo_state_->iter = 0;
  optimizer2->algo_state_->iter = 0;

  Control* control1 = optimizer1->getControl();
  Control* control2 = optimizer2->getControl();

  const int ret = control1->ext(*control2, sub_to_mstr);
  return ret;
}

void ROL_Optimizer::setupParameters() {

  // set default values
  params["npredict"] = 100;                 // predictive steps
  params["nadvance"] = 100;                 // advance steps
  params["grad_check"] = grad_check;        // whether to gradient check
  params["reset_obj"] = reset_obj;          // frequency resetting the objective
  params["use_precond"] = use_precond;      // use diagonal preconditioner
  params["output_type"] = output_type_;     // type of OCS output
  params["print_header"] = print_header_;   // whether to print the header
  params["useTrustRegion"]  = false;        // Use Trust-Region algorithm
  params["useFDhessvec"]    = 0;            // Use FD hessvec
  params["scaleFDstepsize"] = 1.0;          // Scale FD step length for HessVec 
  params["fd_eps"] = fd_eps;                // FD for check gradient
  params["screen_print"] = screen_print_;   // Print info to screen
  
  // comm->cout() << "Before reading params = \n" << params;
  
  // read parameters from an input file
  params.read( root+".inp" );
  
  // initialize parameters
  npredict      = params["npredict"];
  nadvance      = params["nadvance"];
  grad_check    = params["grad_check"];
  reset_obj     = params["reset_obj"];
  use_precond   = params["use_precond"];
  output_type_  = params["output_type"];
  print_header_ = params["print_header"];
  fd_eps        = params["fd_eps"];
  screen_print_ = params["screen_print"];

  // comm->cout() << "After reading params = \n" << params;
  
  // Check if we have the Optimizer block.
  if (json.isMember("Optimizer") == true) {
    
    Json::Value& optBlock = json["Optimizer"];
    
    // New names if used override old names
    grad_check = optBlock.get("Check Gradient", grad_check).asUInt();
    reset_obj = optBlock.get("Reset Objective Frequency", reset_obj).asInt();
    const int useFDhessvec = optBlock.get("Use Finite Difference Hessian",
                                          0).asInt();
    const double scaleFDstepsize = optBlock.get("Finite Difference Step Size",
                                                1.0).asDouble();
    useTrustRegion_ = optBlock.get("Use Trust Region",
                                   useTrustRegion_).asBool();
    use_precond = optBlock.get("Use Preconditioner", use_precond).asBool() ;
    
    output_type_  = optBlock.get("Output Type", output_type_).asInt();
    print_header_ = optBlock.get("Print Header", print_header_).asBool();
    fd_eps = optBlock.get("Gradient Check FD Step Size",fd_eps).asDouble();
    screen_print_ = optBlock.get("Screen Print", screen_print_).asBool();
    
    // Store parameters in a table to pass to objective
    params["grad_check"]      = grad_check;
    params["use_precond"]     = use_precond;
    params["reset_obj"]       = reset_obj;
    params["output_type"]     = output_type_;
    params["print_header"]    = print_header_;
    params["useTrustRegion"]  = useTrustRegion_;
    params["useFDhessvec"]    = useFDhessvec;
    params["scaleFDstepsize"] = scaleFDstepsize;
    params["fd_eps"]          = fd_eps;
    params["screen_print"]    = screen_print_;
    
    // Create Step and StatusTest objects
    ROL_Factory<Real> rol_factory(optBlock, comm, useTrustRegion_, fdorders_);
    step_ = rol_factory.getStep();
    status_ = rol_factory.getStatusTest();

    rol_factory.fillParameterList(parlist_);
    rol_factory.getFDOrders(fdorders_);

    if(grad_check) {
      rol_factory.fillGradientCheckParameterList(gclist_);
    }

    compute_obj_  = parlist_.sublist("General").get("Recompute Objective Function",true);
//    split_update_ = parlist_.sublist("Step").sublist("Line Search").get("Split Update",false);
    split_update_ = optBlock.get("Split Update",true).asBool();

  } else {
    throw DGM::exception("No Optimizer block found in JSON (ROL_Optimizer "
                         "constructor)");
  }
  // comm->cout() << "After parsing Json params = \n" << params
}

} // namespace DGM

#endif // DGM_USE_ROL
