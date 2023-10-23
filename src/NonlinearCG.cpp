/** \file NonlinearCG.cpp
    \brief Nonlinear CG Optimizer implementation
    \author Scott Collis
*/

// System includes
#include <ctime>
#include <cmath>

// DGM includes
#include "Comm.hpp"
#include "NonlinearCG.hpp"
#include "Format.hpp"
#include "Info.hpp"
#include "Color.hpp"

// Set the default for debug output to "off"
#ifndef DGM_NONLINEAR_CG_DEBUG
#define DGM_NONLINEAR_CG_DEBUG 0
#endif

namespace DGM {

/// Constructor
NonlinearCG::NonlinearCG(State *state_, Adjoint *adjoint_,
                         Control::Ptr control_,
                         Preconditioner::Ptr preconditioner_,
                         const DGM::Comm::Ptr comm_,
                         const std::string rel_path_,
                         const Table &passed_param)
  : Optimizer(state_,adjoint_,control_,comm_),
    total_g(0), total_g_old(0), total_j_old(0), total_g_dot_g_old(0),
    alpha(0), tol_alpha(0), norm_alpha(false), use_precond(false),
    stop_on_nan(false), norm_dir(false), reset_obj(0), reset_dir(0),
    lineSearch(*this,comm_), adjoint_num(0), bracket_output(0)
{
  comm->cout() << "Building NonlinearCG solver..." << endl;

  new_control.reset(control->clone());
  dir_control.reset(control->clone());
  gradient.reset(control->clone());
  old_gradient.reset(control->clone());
  diag_precond.reset(control->clone());
  pre_gradient.reset(control->clone());

  new_control ->control_type(Control::CONTROL);
  dir_control ->control_type(Control::GRADIENT);
  gradient    ->control_type(Control::GRADIENT);
  old_gradient->control_type(Control::GRADIENT);
  diag_precond->control_type(Control::STEP);
  pre_gradient->control_type(Control::STEP);

  new_control->zero();
  dir_control->zero();
  gradient->zero();
  diag_precond->zero();
  old_gradient->zero();

#ifdef DGM_USE_TIME_REG
  gt_control.reset(control->clone());
  gt_control->control_type(Control::GRADIENT);
  gt_control->zero();
#endif

  // set default values
  params["dt"] = 0.001;                    // time step
  params["npredict"] = 100;                // predictive steps
  params["nadvance"] = 100;                // after-control advance step
  params["max_iter"] = 10;                 // the maximum number of iterations
  params["max_sub_iter"] = 10;             // maximum steps for line-search
  params["alpha"]  = 0.01;                 // default step size
  params["tol_alpha"] =1.0e-5;             // line search tolerance
  params["tol_j"] = 1.0;                   // objective tolerance
  params["norm_alpha"] = norm_alpha;       // normalized the stepsize
  params["gradient"] = SimpleFixedStepSize;// grad_type type
  params["grad_check"] = 0;                // whether to gradient check
  params["fd_eps"] = 0.001;                // finite-difference step-size
  params["io_type"] = 0;                   // IO control parameter (not used)
  params["reset_obj"] = 0;                 // frequency resetting the objective
  params["reset_dir"] = 0;                 // frequency resetting the direction
  params["use_precond"] = use_precond;     // use diagonal preconditioner
  params["stop_on_nan"] = stop_on_nan;     // stop on a NaN
  params["norm_dir"] = false;              // normalize the direction
  params["brents_type"] = "DGM";           // Use DGM Brent's by default
  params["bracket_output"] = bracket_output; // type of bracket output to use
  
  // Compute only the gradient
  // Check to see if this were passed on the command line through the params
  {
    const std::string eval_gradient = "eval_gradient";
    const bool defined = passed_param.defined(eval_gradient);
    params[eval_gradient] = defined ? 
      bool(passed_param.get(eval_gradient)) : false; 
  }

  // read parameters from an input file
  root = control->root;
  params.read( root+".inp" );

  // initialization
  dt            = params["dt"];
  npredict      = params["npredict"];
  nadvance      = params["nadvance"];
  max_iter      = params["max_iter"];
  max_sub_iter  = params["max_sub_iter"];
  alpha         = params["alpha"];
  tol_alpha     = params["tol_alpha"];
  norm_alpha    = params["norm_alpha"];
  tol_j         = params["tol_j"];
  grad_type     = params["gradient"];
  grad_check    = params["grad_check"];
  fd_eps        = params["fd_eps"];
  io_type       = params["io_type"];
  reset_obj     = params["reset_obj"];
  reset_dir     = params["reset_dir"];
  use_precond   = params["use_precond"];
  stop_on_nan   = params["stop_on_nan"];
  norm_dir      = params["norm_dir"];
  bracket_output = params["bracket_output"];
  eval_gradient  = params["eval_gradient"];

  string brents_type = params["brents_type"];
  //comm->cout() << "brents_type = " << brents_type << std::endl;
  bool useOriginalBrents = true;
  if (lowerCase(brents_type) == "rol" || lowerCase(brents_type) == "new" ||
      lowerCase(brents_type) == "drew") {
    useOriginalBrents = false;
    comm->cout() << "NonlinearCG() : Using Drew Kouri's new Brent's linesearch "
                    "implementation" << endl ;
  } else {
    comm->cout() << "NonlinearCG() : Using original Brent's linesearch "
                    "implementation" << endl ;
  }
  lineSearch.setUseOriginalBrents(useOriginalBrents);

  // setup linesearch parameter history
  alpha_bar.resize(max_iter+1);
  alpha_bar = 0.0;

  // path to ocs file
  objname = rel_path_ + root + ".ocs";

  // it is a good idea to initialize everything
  state->initialize();
  control->initialize();
  gradient->initialize();
#ifdef DGM_USE_TIME_REG
  gt_control->initialize();  // h = g_t
#endif
  adjoint->initialize();

  // set the preconditioner on the Adjoint
  adjoint->set_preconditioner(diag_precond);

  // this is extraneous (but left in as it might be nice in the future)
  resetPreconditioner( preconditioner_ );

  // comm->cout() << "Completed NonlinearCG construction" << endl;
}

void NonlinearCG::computeUpdate() {
  // update the line-search direction
  computeUpdateDirection();

  // compute the line-search step
  if (grad_type>1) computeBestStepSize();

  // update the control
  updateControl(alpha, 1);
}

void NonlinearCG::prepare_history_file() {
  // prepare optimization history file
  if (comm->Master()) {
    bool exist = DGM::file_exists(objname);
    if (opt_stat==NULL)
      opt_stat = fopen(objname.c_str(),"a+");  // append to end of file
    if (!exist)
      fprintf(opt_stat, "VARIABLES=\"iter\" \"J\"  \"NormG\" \"Alpha\" "
            " \"Time\" \"fnum\" \"gnum\" \n");
  }
}

void NonlinearCG::write_history_file() {
  // output the first Objective function value
  if (comm->Master()) {
    fprintf(opt_stat,"%5lld %11.4e %11.4e %11.4e %11.4e %5lld %5lld\n",
            (long long)iter,total_j,total_g,alpha,timer.read(),
            (long long)state->num(), (long long)adjoint_num);
    fflush(opt_stat);
  }
}

/// Solve optimization problem
/** Main Optimizer method that initializes and solves the optimization
    problem to the requested tolerance or maximum number of iterations

    \note Input parameter is currently ignored
*/
void NonlinearCG::optimize(const Ordinal) {
  static Format sci(8); sci.scientific().width(15);
  static Color bold(Color::BOLD);
  static Color red(Color::RED);
  static Color def(Color::DEFAULT);
  static Color green(Color::GREEN);

  // prepare optimization history file
  prepare_history_file();

  for(iter=readRestart()+1; iter<= max_iter; iter++) {
    timer.start();
    comm->cout()
      <<"===================================================================="
      <<endl<<"Optimization iteration = "<<iter<<endl
      <<"===================================================================="
      <<endl;

    if (reset_obj)
      if (iter%reset_obj==0) state->get_objective()->reset();

#if DGM_NONLINEAR_CG_DEBUG > 1
    // put this in for debugging control restart
    control->set_data(0);
    control->output(0);
#endif

    // solve the state and compute the objective function
    set_iter(iter);
    set_npredict(npredict);
#ifndef DGM_USE_TIME_REG
    total_j = computeState(control, state->get_objective());
#else
    total_j = computeState(gt_control, control, state->get_objective());
#endif
    if( comm->verbosity()>3 ) {
      comm->cout() << "total_j = " << total_j << std::endl;
    }
    if (grad_check==3) comm->exit(0);  // exit after state solution

    adjoint_num = adjoint->num();

    total_j_old = total_j;

    if(iter>1) {
      copy(gradient,old_gradient);
      total_g_old = total_g;
    }
    gradient->zero();

    // solve the adjoint and get the gradient of the objective function
#ifndef DGM_USE_TIME_REG
    computeAdjoint(control, state->get_objective());
#else
    computeAdjoint(gt_control, control, state->get_objective());
#endif

    // finalize the computation of the gradient
    computeGradient();
    
    // total_j may have been changed by a derived code
    total_j_old = total_j;

    // output the first Objective function value
    if (iter==1) {
      Scalar local_alpha = alpha;
      alpha = 0;
      iter = 0;
      write_history_file();
      iter = 1;
      alpha = local_alpha;
    }

#ifdef DGM_USE_SCALED_GRADIENT
    total_g = gradient->norm();
    scale( one/total_g, gradient );
#endif

    total_g = gradient->norm();
    comm->cout()<<"||Grad(J)|| = "<<sci(total_g)<<endl;
    gradient_norms.resize(numeric_cast<Ordinal>(gradient->num_ctrl()));
    gradient_norms = gradient->norms();
    vector<string> names(gradient->names());
    for (Ordinal i=0; i<gradient_norms.size(); ++i)
      comm->cout()<<"  ||dJ/d(" << names[i] << ")|| = "
                  <<sci(gradient_norms[i])<<endl;

    // start of work on preconditioner (this needs to be tested)
    if (use_precond) {
      diag_precond->applyPreconditioner(gradient,pre_gradient);

      gradient_norms = pre_gradient->norms();
      vector<string> names(pre_gradient->names());
      for (Ordinal i=0; i<gradient_norms.size(); ++i)
        comm->cout()<<"  ||M^-1 dJ/d(" << names[i] << ")|| = "
                    <<sci(gradient_norms[i])<<endl;

      Scalar norm_sgrad = pre_gradient->norm();
      comm->cout()<<"||M^-1 Grad(J)|| = "<<sci(norm_sgrad)<<endl;
      // delta_new
      total_g = sqrt(gradient->inner_product(pre_gradient));
      comm->cout()<<"<Grad(j), M^-1 Grad(J)> = "<<sci(total_g)<<endl;
    }

    if(iter>1)
      total_g_dot_g_old = old_gradient->inner_product(gradient);

    // gradient check against finite-difference
    if(grad_check) {
      check_grad();
      if (grad_check > 1) comm->exit(0);
    }

    // check for hard convergence of the gradient
    /** \note Would be better to have a separate tolerance for this. */
    if ( total_g < tol_j ) {
      comm->cout()<<bold<<"\nCongratulations:  Hard Convergence!!!\n"
                  <<def<<endl;
      write_history_file();
      writeRestart();
      break;
    }
    
    if(eval_gradient) {
       	comm->cout()<<"Dumping the gradient to disk and quiting."<<std::endl;
       	
       	// string ext("preconinside");
     	// pre_gradient->plot(0, 0, &ext);
       	
       	computeUpdateDirection();
    	writeRestart();
    	comm->exit(0);
    }

    // update line-search direction, compute step, update control
    computeUpdate();

    // write the control restart file
    writeRestart();

    // output optimization history
    if (comm->Master()) {
      fprintf(opt_stat,"%5lld %11.4e %11.4e %11.4e %11.4e %5lld %5lld\n",
              (long long)iter,total_j,total_g,alpha,timer.read(),
              (long long)state->num(), (long long)adjoint->num());
      fflush(opt_stat);
    }

    // optimization convergence condition
    if (grad_type>1) {
      comm->cout()<<endl;
      comm->cout()<<"Improvement in J:    "
                  <<sci(total_j_old-total_j)
                  <<endl;
      comm->cout()<<"Tolerance for exit:  "
                  <<sci(tol_j * total_j_old)
                  <<endl;
      if(total_j_old-total_j < tol_j*total_j_old){
        comm->cout()<<"Adjoint iteration loop converged!!"<<endl<<endl;
        break;
      }
      else if (iter < max_iter)
        comm->cout()<<"Continuing adjoint iteration loop..."<<endl;
      else
        comm->cout()<<"Iteration loop ran up to MAX_ITER, exiting loop."
                    <<endl;
      comm->cout()<<endl;
    }

  } // iter
}

/// Advance the solution
Scalar NonlinearCG::advance(const Ordinal outer) {
  // Check: if Control unsteady && nadvance>npredict,  Error!!
  if(!(control->steady()) && nadvance%npredict!=0){
    comm->cerr()<<"Error: nadvance > npredict for the unsteady control"<<endl;
    comm->cerr()<<"       nadvance = "<<nadvance<<endl;
    comm->cerr()<<"       npredict = "<<npredict<<endl;
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
void NonlinearCG::check_grad() {
  Format sci(10); sci.scientific().width(17);
  Format percent(2); percent.fixed().width(6);
  comm->cout() << "NonlinearCG::check_grad()" << endl;

  Scalar Jobj0 = total_j;

  // backup the direction
  Control::Ptr dir_save( dir_control->clone() );
  dir_save->control_type(Control::GRADIENT);

  // set a new arbitrary direction
  dir_control->set_direction();

  Scalar g2 = dir_control->inner_product(gradient);

#if DGM_NONLINEAR_CG_DEBUG > 3
  comm->cout()<<"||Grad(J)|| = "<<sci(gradient->norm())<<endl;
  comm->cout()<<"||Direction|| = "<<sci(dir_control->norm())<<endl;
#endif
  comm->cout()<<"(Grad(J),dir) = "<<sci(g2)<<endl;

  // Note that the signs are flipped due to update_control
  Scalar Jobj1 = test(fd_eps);

  Scalar Jobj2 = test(-fd_eps);

  Scalar Jobj3 = test(2.*fd_eps);

  Scalar Jobj4 = test(-2.*fd_eps);

  // first order finite difference
  Scalar g0 = -(Jobj1 - Jobj0) / fd_eps;

  // Second order finite difference
  Scalar g1 = (Jobj2 - Jobj1) / (2. * fd_eps);

  // Fourth order finite difference
  Scalar g3 = -( -1. * Jobj3 + 8. * Jobj1 - 8. * Jobj2 + Jobj4 ) /
    (12. * fd_eps);

  comm->cout()<<"First Order  FD  Gradient    = "<<sci(g0)<<endl;
  comm->cout()<<"Second Order FD  Gradient    = "<<sci(g1)<<endl;
  comm->cout()<<"Fourth order FD  Gradient    = "<<sci(g3)<<endl;
  comm->cout()<<"Adjoint Formulation Gradient = "<<sci(g2)<<endl;

  if (g0 != 0)
    comm->cout()<<"err w.r.t. first order fd    = "<<sci((g2-g0)/g0)
                <<" ("<<percent((g2-g0)/g0*100)<<"%)"<<endl;
  else
    comm->cout()<<"first order fd gradient is zero!"<<endl;

  if (g1 != 0)
    comm->cout()<<"err w.r.t. second order fd   = "<<sci((g2-g1)/g1)
                <<" ("<<percent((g2-g1)/g1*100)<<"%)"<<endl;
  else
    comm->cout()<<"second order fd gradient is zero!"<<endl;

  if (g3 != 0)
    comm->cout()<<"err w.r.t. fourth order fd   = "<<sci((g2-g3)/g3)
                <<" ("<<percent((g2-g3)/g3*100)<<"%)"<<endl;
  else
    comm->cout()<<"fourth order fd gradient is zero!"<<endl;

  // recover the old search direction
  copy(dir_save, dir_control);
}

/** Do a test evaluation of the objective functional. */
Scalar NonlinearCG::test_evaluation(Scalar a) {
  // comm->cout()<<"NonlinearCG::test("<<a<<")"<<endl;
  Format sci(8); sci.scientific().width(15);
  test_count++;
  bool valid = updateControl(a);
  Scalar J;
  if (valid) {
    state->set_initial_condition();
#ifndef DGM_USE_TIME_REG
    J = state->test(npredict, new_control);
#else
    J = state->test(npredict, new_control, control);
#endif
    comm->cout()<<"J = "<<sci(J)<<", alpha_test = "<<sci(a)<<endl;
#if !defined(_CRAYC) && !defined(__PGI)
    if (stop_on_nan) {
      if ( std::isnan(J) ) error("NAN in NonLinearCG::test()");
      if ( std::isinf(J) ) error("INF in NonLinearCG::test()");
    }
#endif
  } else {  // return maximum possible value for an invalid control
    J = numeric_limits<Scalar>::max();
    comm->cout()<<"J = "<<sci(J)<<", alpha_test = "<<sci(a)<<endl;
  }
  return J;
}

Scalar NonlinearCG::test(Scalar a) {
  return test_evaluation(a);
}

/** Solves the one-dimensional optimization problem by first bracketing the
    solution and then using Brent's algorithm. */
void NonlinearCG::computeBestStepSize() {
  static Format sci(10); sci.scientific().width(17);
  static Color bold(Color::BOLD);
  static Color red(Color::RED);
  static Color def(Color::DEFAULT);
  static Color green(Color::GREEN);

  comm->cout()<<bold<<"ComputeBestStepSize"<<def<<endl;
  Scalar ax, bx, cx, fa, fb, fc;
  test_count = 0;
  ax = 0.0;
  fa = total_j;
  if( alpha_bar[iter] == 0.0 ) alpha_bar[iter]= fabs(alpha);
  bx = fabs( alpha_bar[iter] );

  fb = test(bx);

  lineSearch.bracket(ax,bx,cx,fa,fb,fc);

  comm->cout()<<red<<bold<<"Bracketing interval found with "<<test_count
  	          <<" function evaluations." << endl;
  if (bracket_output) {
    comm->cout()<<"[ xa, xb, xc ] = [ "<<sci(ax)<<", "<<sci(bx)<<", "
                <<sci(cx)<<"]"<<endl;
    comm->cout()<<"[ fa, fb, fc ] = [ "<<sci(fa)<<", "<<sci(fb)<<", "
                <<sci(fc)<<"]"<<endl;
  } else {
    comm->cout()<<"[ "<<sci(ax)<<" "<<sci(bx)<<" "<<sci(cx)<<"]"<<endl;
  }
  comm->cout()<<def;

  lineSearch.brents_fmin( ax,bx,cx,fa,fb,fc,tol_alpha,max_sub_iter );

  alpha = bx;
  total_j = fb;
  comm->cout()<<green<<bold;
  comm->cout()<<"Best step size found with "<< test_count
              <<" function evaluations.\n"<<"Alpha = "<< sci(alpha)
              <<", Total_J = "<< sci(total_j) <<endl;
  comm->cout()<<def;

  alpha_bar[iter] = fabs(alpha);
}

/** Use either steepest decent or three flavors of congugate gradients:
    Fletcher-Reeves, Polak-Ribiere, or Hestenes-Stiefel

    \note Currently preconditioner is only implemented for steepest descent
    \todo Implement preconditioner for nonlinear CG
*/
void NonlinearCG::computeUpdateDirection() {
  Scalar momentum=0;
  if(iter == 1 || grad_type<3) {  // simple gradient (always on first iter)
    if (use_precond)
      copy(pre_gradient, dir_control);
    else
      copy(gradient, dir_control);
  } else {                        // conjugate gradient
    if (grad_type==FletcherReeves) {
      momentum = pow(total_g,2)/pow(total_g_old,2); // ||g||^2 / ||g_old||^2
    } else if (grad_type==PolakRibiere) {
      // ( ||g||^2 - <g,g_old> ) / ||g_old||^2
      momentum = (pow(total_g,2) - total_g_dot_g_old) / pow(total_g_old,2);
    } else if (grad_type==HestenesStiefel
               || grad_type==ScaledHestenesStiefel
               || grad_type==RescaledScaledHestenesStiefel
               || grad_type==ModifiedHestenesStiefel){
      // In the traditional Hestenes-Stiefel, we have
      // ( ||g||^2 - <g,g_old> ) / ( <g,p_old> - <g_old,p_old> )
      // In the scaled gradient version, we divide each gradient by it's norm.
      // This simplifies the equation to
      // ( 1 - <g,g_old> / ( ||g||*||g_old|| ) ) /
      //     ( <g,p_old> / ||g|| - <g_old,p_old> / ||g_old|| )
      // In the rescaled, scaled version we pull out a term 1/||g||.  This
      // becomes
      // 1/||g|| ( ||g||^2 - <g,g_old> ( ||g||/||g_old|| ) /
      //     ( <g,p_old>  - <g_old,p_old> (||g||/||g_old||) )
      // In this implementation, we ignore the factor of 1/||g|| since
      // we need only a search direction and the scaling shouldn't matter
      // if the line search works properly (which is somewhat tricky
      // since the linesearch parameter is problem dependent.)
      // The modified Hestenes-Stiefel direction comes from a new paper
      // entitled, "A Modified Hestenes-Stiefel Conjugate Gradient Method
      // and Its Convergence," from Wei, Huang, and Tao.  The authors provide
      // a slight variation on HS and prove its global convergence (which it
      // does not natively possess.)

      const Scalar dir_old_dot_g =
        dir_control->inner_product(gradient);
      const Scalar dir_old_dot_g_old =
        dir_control->inner_product(old_gradient);

      // Strictly speaking, we don't have to calculate these unless we're
      // scaling the gradients which is unnecessary in the traditional
      // Hestenes-Stiefel approach.  It probably doesn't cost too much, so
      // we'll leave it here for now.
      const Scalar norm_grad = gradient->norm();
      const Scalar norm_grad_old = old_gradient->norm();

      Scalar numerator=0;
      switch(grad_type){
      case HestenesStiefel:
        numerator=pow(total_g,2) - total_g_dot_g_old;
        break;
      case ScaledHestenesStiefel:
        numerator=1-total_g_dot_g_old/(norm_grad*norm_grad_old);
        break;
      case RescaledScaledHestenesStiefel:
        numerator=pow(norm_grad,2)-
          total_g_dot_g_old*(norm_grad/norm_grad_old);
        break;
      case ModifiedHestenesStiefel:
        numerator=pow(total_g,2) - pow(total_g_dot_g_old,2) /
          pow(norm_grad_old,2);
        break;
      }

      Scalar denominator=0;
      switch(grad_type){
      case HestenesStiefel:
      case ModifiedHestenesStiefel:
        denominator=dir_old_dot_g - dir_old_dot_g_old;
        break;
      case ScaledHestenesStiefel:
        denominator=dir_old_dot_g/norm_grad-dir_old_dot_g_old/norm_grad_old;
        break;
      case RescaledScaledHestenesStiefel:
        denominator=dir_old_dot_g-dir_old_dot_g_old*(norm_grad/norm_grad_old);
        break;
      default:
        error("Unknown grad_type in NonlinearCG::computeUpdateDirection()");
        break;
      }

      if (denominator != 0) {
        momentum = numerator/denominator;
      } else
        momentum = zero;
    } else if (grad_type==DGKSHestenesStiefel) {
      // This is an experiment to see how bad some of the numerics are when
      // computing the Hestenes-Stiefel search direction.  In the linear
      // conjugate gradient case, the search directions at each iteration
      // are A-orthogonal to one another.  This orthogonalization is
      // computed using Gram-Schmidt which is known to be numerically
      // problematic.  As a result, we can compute corrections such as the
      // DKGS correction step (which essentially does the orthongonlization
      // twice.)  Although we don't maintain conjugate directions in
      // nonlinear CG, we can repeat this process.  We know whether or not
      // this has an affect because, if it doesn't, the search direction
      // and behavior will be the exact same as the regular
      // Hestenes-Stiefel direction.

      // Get the old search direction
      Control::Ptr old_p(dir_control);

      // Find the initial search direction
      // We need a physical copy of the gradient because we modify p
      Control::Ptr p(gradient->clone());
      scale(-one,p);
      Scalar denominator =
        old_p->inner_product(gradient) - old_p->inner_product(old_gradient);
      Scalar beta;
      momentum=zero;
      for(int i=0;i<=1;i++) {
        Scalar numerator =
          -(p->inner_product(gradient) - p->inner_product(old_gradient));
        if (denominator == 0) {
          momentum=zero;
          break;
        }
        beta=numerator/denominator;
        axpy(beta,old_p,p);
        momentum=momentum+beta;
      }
    }
    if (reset_dir) if (iter%reset_dir) momentum = zero;

    // dir = momentum * dir + gradient
    axpy(momentum, dir_control, gradient, dir_control);
  }
}

/** Generates a new control object that is new_control = control -
    a*dir_control where dir_control is the decent direction and control is the
    current control.  If the finalUpdate flag is true, then on exit new is
    copied into control. */
bool NonlinearCG::updateControl(Scalar a, Ordinal finalUpdate) {
  bool valid = true;
  Scalar factor = one;
  // normalize the search direction if desired
  if (norm_dir) factor = one/dir_control->norm();
#ifndef DGM_USE_TIME_REG
  axpy(-a*factor, dir_control, control, new_control);
  new_control->bound();
  valid = new_control->realizable();
  if (!valid) comm->cout() << "Your control is unrealizable ..." << endl;
  if (finalUpdate) copy(new_control, control);
#else
  axpy(-a*factor, dir_control, gt_control, new_control);
  valid = new_control->realizable();
  if (!valid) comm->cout() << "Your control is unrealizable ..." << endl;
  new_control->bound();
  if (finalUpdate) copy(new_control, gt_control);
#endif
  return valid;
}

void NonlinearCG::set_max_iter(const Ordinal i) {
  Optimizer::set_max_iter(i);
  alpha_bar.resize(max_iter+1);
  alpha_bar = 0.0;
}

//=============================================================================
//                        Original Header Support
//=============================================================================

/// Write the optimization restart file header
streamoff NonlinearCG::writeHeader(const string &fname) const {
  const int verb=0;
  streamoff disp=0;
#ifndef DGM_NO_CONTROL_HEADER
  const int width = 40;
  if (ctl_comm->Master()) {
    // get the current date and time from <time.h>
    char now[128]="Time is not available";
#if !defined(DGM_NO_TIME)
    time_t tp = time(0);
    strftime(now,128,"%a %b %d %H:%M:%S %Y", localtime(&tp));
#endif
    ofstream res_out(fname.c_str());
    res_out.setf(ios::left);
    res_out<<setw(width)<<now<<" Created"<<endl;
    res_out<<setw(width)<<fname.c_str()<<" Name"<<endl;
    res_out<<setw(width)<<iter<<" Iteration"<<endl;
    res_out<<setw(width)<<alpha<<" Linesearch step size"<<endl;
    res_out<<setw(width)<<total_g<<" Gradient L2 norm"<<endl;
    res_out<<setw(width)<<(npredict+1)<<" Time steps"<<endl;
    res_out<<setw(width)<<"<unused>"<<endl;  // make header 10 lines
    res_out<<setw(width)<<"<unused>"<<endl;
    res_out<<setw(width)<<"<unused>"<<endl;
    res_out<<setw(width)<<"NonlinearCG"<<" Optimizer"<<endl;
    disp = res_out.tellp();  // get the header length (in bytes)
    res_out.close();
  }
  const int stat = ctl_comm->Broadcast(&disp);
  if (stat)
    ctl_comm->error("NonlinearCG::writeHeader: Error in broadcast of displacement");
  if (verb)
    ctl_comm->cout()<<"Wrote control restart header of length "<<disp<<endl;
#else
  disp = 0;
#endif
  return disp;
}

/// Read the optimization restart file header
streamoff NonlinearCG::readHeader(const string &fname, Ordinal &riter) {
  const int verb=0;
  streamoff skip;
  Ordinal steps;
#ifndef DGM_NO_CONTROL_HEADER
  ifstream res_in(fname.c_str());
  if (!res_in) {
    timer.reset();
    riter = 0;
    return 0;
  }
  string buf;
  getline(res_in,buf);
  if (!(res_in>>buf)) error("Cannot read restart name",1);
  getline(res_in,buf);
  if (!(res_in>>riter)) error("Cannot read iteration number",1);
  getline(res_in,buf);
  if (!(res_in>>alpha)) error("Cannot read linesearch step size",1);
  getline(res_in,buf);
  if (!(res_in>>total_g)) error("Cannot read the norm of gradient",1);
  getline(res_in,buf);
  if (!(res_in>>steps)) error("Cannot read time steps",1);
  getline(res_in,buf);
  if(steps!=(npredict+1)) {
    comm->cerr()<<"WARNING:  Steps not consistent with restart file"<<endl;
    comm->cerr()<<"  steps = "<<steps<<endl;
    comm->cerr()<<"  npredict+1 = "<<npredict+1<<endl;
  }
  // eat four more lines
  getline(res_in,buf);  getline(res_in,buf);
  getline(res_in,buf);  getline(res_in,buf);
  skip = res_in.tellg();    // get the header length (in bytes)
  if (verb)
    comm->cout() << "Read control restart header of length = " <<skip<<endl;
#else
  riter = 1;
  skip = 0;
#endif
  return skip;
}

//=============================================================================
//                          JSON Header Support
//=============================================================================

/// Write the optimization Json header
streamoff NonlinearCG::writeJsonHeader(const string &fname) const {
  const int verb=ctl_comm->verbosity();
  if (verb)
    ctl_comm->cout()<<"NonlinearCG::writeJsonHeader("<<fname<<")"<<endl;
  streamoff disp=0;
  const int buflen=128;
  char now[buflen] = "Time is not available";
  if (ctl_comm->Master()) {
    ofstream fs(fname.c_str());
    if (!fs) throw DGM::exception("NonlinearCG::writeJsonHeader could not "
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

    header["Iteration"] = iter;
    header["Wall time"] = timer.read();
    header["Objective function"] = total_j;
    header["Norm of the gradient"] = total_g;
    header["Npredict"] = npredict;
    header["Time steps"] = npredict + 1;
    header["Number of State solves"] = state->num();
    header["Number of Adjoint solves"] = adjoint->num();

    header["NonlinearCG"] = Json::Value(Json::objectValue);
    header["NonlinearCG"]["Linesearch step size"] = alpha;
    header["NonlinearCG"]["Type"] = grad_type;
    header["NonlinearCG"]["||Grad(J)||"] = total_g;
    header["NonlinearCG"]["||dJ/dphi_i||"] = Json::Value(Json::arrayValue);
    header["NonlinearCG"]["||dJ/dphi_i||"].resize(
      numeric_cast<Json::ArrayIndex>(gradient_norms.size()));
    for (Ordinal i=0; i<gradient_norms.size(); ++i) {
      const Json::ArrayIndex m = numeric_cast<Json::ArrayIndex>(i);
      header["NonlinearCG"]["||dJ/dphi_i||"][m] = gradient_norms[i];
    }
    header["NonlinearCG"]["||Grad(J_prior)||"] = total_g_old;
    header["NonlinearCG"]["J"] = total_j;
    header["NonlinearCG"]["J_prior"] = total_j_old;
    header["NonlinearCG"]["<G(J),G(J_prior)>"] = total_g_dot_g_old;

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

    if (control->phi_db.size() != names.size()) 
      throw DGM::exception("NonlinearCG::writeJsonHeader size of control"
        " database not equal to number of names in database.");
#if __cplusplus >= 201103L
    header["Control Specific Info"] = Json::Value(Json::objectValue);
    typedef list<Control::Entry::Ptr>::iterator LI;
    for (LI c = control->phi_db.begin(); c != control->phi_db.end(); ++c) {
      const Control::dbEntry_t entry = *c;
      const Ctrl *ctrl = entry->ctrl;
      const std::map<std::string,std::string> s = ctrl->info();
      if (!s.empty()) {
        const int i =
          numeric_cast<int>(std::distance(control->phi_db.begin(),c));
        const std::string name = names[i];
        header["Control Specific Info"][name] = Json::Value(Json::objectValue);
        for (auto it : s) 
          header["Control Specific Info"][name][it.first] = it.second; 
      }
    }
#endif
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
      throw DGM::exception("NonlinearCG::writeJsonHeader file stream in bad "
                           "state for restart file "+fname);
    fs << output;
    if (!fs) throw DGM::exception("NonlinearCG::writeJsonHeader could not "
                                  "write header to restart file "+fname);
    disp = fs.tellp();
  }
  const int stat = ctl_comm->Broadcast(&disp);
  if (stat) throw DGM::exception("NonlineaerCG::writeJsonHeader: error in "
                                 "broadcast of displacement");
  if (verb>2)
    ctl_comm->cout() << "NonlinearCG::writeJsonHeader("<<fname
                 <<") completed with disp = " << disp <<" bytes" << endl;
  return disp;
}

/// Read the optimization Json header
streamoff NonlinearCG::readJsonHeader(const string &fname, Ordinal &riter) {
  const int verb=0;
  if (verb>1) comm->cout()<<"NonlinearCG::readJsonHeader("<<fname<<")"<<endl;
  ifstream fs(fname.c_str());
  if (!fs) {
    timer.reset();
    riter = 0;
    return 0;
  }
  char c = fs.peek();
  if (!fs) throw DGM::exception("Cannot read Json header from "+fname);
  if (c!='{') {
    return readHeader(fname,riter);
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
    comm->cout() << "Read header from " << fname << "\n" << buffer << endl;
  Json::Reader reader;
  bool parsingSuccessful = reader.parse( buffer, header, true );
  if (!parsingSuccessful)
    comm->error("NonlinearCG readJsonHeader could not parse input from "+
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

  if (!header.isMember("Number of State solves"))
    state->num(0);
  else
    state->num(numeric_cast<Ordinal>(
               header["Number of State solves"].asUInt64()));

  if (!header.isMember("Number of Adjoint solves"))
    adjoint->num(0);
  else
    adjoint->num(numeric_cast<Ordinal>(
               header["Number of Adjoint solves"].asUInt64()));

  if (!header.isMember("Objective function"))
    throw DGM::exception("Header is missing \"Objective function\" "
                         "from file "+fname);
  total_j = numeric_cast<Scalar>(header["Objective function"].asDouble());

  // NonlinearCG block
  if (!header.isMember("NonlinearCG"))
    throw DGM::exception("Header missing \"NonlinearCG\" block from "
                         "file "+fname);
  Json::Value &nonlinearcg = header["NonlinearCG"];
  if (!nonlinearcg.isMember("||Grad(J)||"))
    throw DGM::exception("Header is missing \"||Grad(J)||\""
                         " from file "+fname);
  total_g = numeric_cast<Scalar>(nonlinearcg["||Grad(J)||"].asDouble());

  if (!nonlinearcg.isMember("Linesearch step size"))
    throw DGM::exception("Header missing \"NonlinearCG::Linesearch step\" "
                         "size from file "+fname);
  alpha = numeric_cast<Scalar>(nonlinearcg["Linesearch step size"].asDouble());

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

  vector<string> names = control->names();
  if (control->phi_db.size() != names.size()) 
    throw DGM::exception("NonlinearCG::writeJsonHeader size of control"
      " database not equal to number of names in database.");

  // output diagnostic information if available and use to populate
  // diagnostics for gradient, dir_control, and pre_gradient
  const string csi = "Control Specific Info";
  if (header.isMember(csi)) {
    typedef list<Control::Entry::Ptr>::iterator LI;
    for (LI c = control->phi_db.begin(); c != control->phi_db.end(); ++c) {
      const Control::dbEntry_t entry = *c;
      const size_t i = std::distance(control->phi_db.begin(), c);
      const std::string name = names[i];
      if (header[csi].isMember(name)) {
        comm->cout()<<"  Control entry:  " << name << endl;
        for (Json::ValueIterator it=header[csi][name].begin(); 
                                 it!=header[csi][name].end(); ++it) {
          const std::string key = it.key().asString(); 
          const std::string val = (*it).asString(); 
          comm->cout()<<"    "<<key<<" = "<<val<<std::endl;
          control->set_parameter(key,val);
          gradient->set_parameter(key,val);
          dir_control->set_parameter(key,val);
          pre_gradient->set_parameter(key,val);
        }
      }
    }
  }

  streamoff disp = fs.tellg();
  if (verb>2) comm->cout()<<"NonlinearCG::readJsonHeader("<<fname<<") with "
    "displacement = "<<disp<<endl;
  return disp;
}

//==============================================================================
//                            Restart file I/O
//==============================================================================

/// Make the JSON header the default
#define DGM_USE_JSON_CTL_HEADER

/// Write the optimization restart file
void NonlinearCG::writeRestart(const string *ctl) const {
  streamoff skip;
  string fname;
  if (ctl) {
    fname = *ctl;
  } else {
    char tmp[80];
    sprintf(tmp,".%lld",(long long)iter);
    fname = root+tmp+".ctl";
  }
  ctl_comm->cout()<<"Writing control restart file "<<fname<<"."<<endl;
#ifdef DGM_USE_JSON_CTL_HEADER
  skip = writeJsonHeader(fname);
#else
  skip = writeHeader(fname);
#endif
  skip = control->write(fname,skip);
#ifdef DGM_USE_TIME_REG
  skip = gt_control->write(fname,skip);
#endif
  skip = dir_control->write(fname,skip);
  skip = gradient->write(fname,skip);
}

/// Read the optimization restart file
Ordinal NonlinearCG::readRestart(streamoff &skip, const string *ctl) {
  Ordinal riter=0;
  string format, fname;
  if (ctl)
    fname = *ctl;
  else
    fname = root+".ctl";
#if 0
  // throw if file doesn't exist
  if (!file_exists(fname)) {
    string s = "Unable to open file " + fname;
    throw DGM::exception(s.c_str());
  }
#endif
#ifdef DGM_USE_JSON_CTL_HEADER
  skip = readJsonHeader(fname,riter);
#else
  skip = readHeader(fname,riter);
#endif
  if (riter==0) return 0;
  comm->cout()<<"Restarting optimization from "<<fname<<endl;
  skip = control->read(fname,skip);
#ifdef DGM_USE_TIME_REG
  skip = gt_control->read(fname,skip);
#endif
  skip = dir_control->read(fname,skip);
  skip = gradient->read(fname,skip);
#ifndef DGM_USE_TIME_REG
  copy(control,new_control);
#else
  copy(gt_control,new_control);
#endif
  return riter;
}

/// Original readRestart interface
Ordinal NonlinearCG::readRestart(const string *ctl) {
  streamoff skip(0);
  return readRestart(skip,ctl);
}

int NonlinearCG::diff(const string& ctl1, const string& ctl2,
                      const Scalar aeps, const Scalar reps) {
  Ordinal riter1 = 0, riter2 = 0;
  streamoff skip1 = 0, skip2 = 0;
#ifdef DGM_USE_JSON_CTL_HEADER
  skip1 = readJsonHeader(ctl1, riter1);
  skip2 = readJsonHeader(ctl2, riter2);
#else
  skip1 = readHeader(ctl1, riter1);
  skip2 = readHeader(ctl2, riter2);
#endif
  // second control
  Control::Ptr control_2(control->clone());
  // read first control
  control->read(ctl1, skip1);
  // read second control
  control_2->read(ctl2, skip2);
  // compute diff
  return control->diff(*control_2, aeps, reps);
}

int NonlinearCG::sum(const double mult,
                     const std::vector<Size>&sub_to_mstr, Optimizer *optimizer){
  NonlinearCG *optimizer1 = this;
  NonlinearCG *optimizer2 = dynamic_cast<NonlinearCG*>(optimizer);
  if (!optimizer2) 
     throw DGM::exception("NonlinearCG::sum could not dynamic "
        "cast Optimizer to NonlinearCG.");
  Control* control1 = optimizer1->getDirControl();
  Control* control2 = optimizer2->getDirControl();
  int ret = control1->sum(*control2, mult, sub_to_mstr);

  Control* controlgrad1 = optimizer1->getGradient();
  Control* controlgrad2 = optimizer2->getGradient();
  ret += controlgrad1->sum(*controlgrad2, mult, sub_to_mstr);

  return ret;
}

int NonlinearCG::sum(const double mult) {
  const std::vector<Size> sub_to_mstr;
  NonlinearCG *optimizer1 = this;
  Control* control1 = optimizer1->getControl();
  Control* control2 = optimizer1->getDirControl();
  const int ret = control1->sum(*control2, mult, sub_to_mstr);
  return ret;
}

int NonlinearCG::ext(const std::vector<Size>&sub_to_mstr, Optimizer *optimizer){
  NonlinearCG *optimizer1 = this;
  NonlinearCG *optimizer2 = dynamic_cast<NonlinearCG*>(optimizer);
  if (!optimizer2) 
     throw DGM::exception("NonlinearCG::ext could not dynamic "
        "cast Optimizer to NonlinearCG.");
  optimizer1->iter = 0;
  optimizer2->iter = 0;
  Control* control1 = optimizer1->getControl();
  Control* control2 = optimizer2->getControl();
  const int ret = control1->ext(*control2, sub_to_mstr);
  return ret;
}

void NonlinearCG::plotControl(const Ordinal ntout, const Ordinal riter) const {
  control->plot(ntout, riter);
}

void NonlinearCG::plotGradient(const Ordinal ntout, const Ordinal riter) const {
  string ext("grd");
  gradient->plot(ntout, riter, &ext);
 
  ext.assign("dir");
  dir_control->plot(ntout, riter, &ext);
  
  ext.assign("precon");
  pre_gradient->plot(ntout, riter, &ext);
}

/** Implements the DGM::Eval interface. */
Scalar NonlinearCG::operator()(const Scalar &x) {
  increment();
  return test(x);
}

} // namespace DGM
