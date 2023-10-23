#ifndef DGM_LIN_TEST_HPP
#define DGM_LIN_TEST_HPP

/** \file  LinTest.hpp
    \brief Tests the DGM linearized State solve

    \todo Make the finite-difference order a runtime option
    \todo Make the range of epsilon a runtime option
*/

// DGM includes
#ifdef DGM_PARALLEL
#include "MpiComm.hpp"
#else
#include "SerialComm.hpp"
#endif
#include "Types.hpp"
#include "ArgList.hpp"
#include "Table.hpp"
#include "Format.hpp"
#include "Domain.hpp"
#include "vField.hpp"
#include "Control.hpp"

/// Use a second-order accurate central difference
#define DGM_LINTEST_ORDER 4

namespace DGM {

/// Computes a finite difference test for the linearized state solve
template <class OptProblem>
void lin_state_test(DGM::ArgList &args,
                    const DGM::Table &params=DGM::Table(),
                    const DGM::Comm::Ptr comm=DGM::Comm::World
  ) {

  const int DGM_LINTEST_LOWER = -1;
  const int DGM_LINTEST_UPPER = 4;

  // Grab the problem file name
  string root=args.back();

  // Get a string representation of the step we're conducting the linearized
  // state test at.
  string step = *(++args.begin());

  // Create both a regular optimization problem as well as a linearized
  // optimization problem
  OptProblem ocp(args,params,comm);
  OptProblem locp(&ocp,args,params,comm);

  // Create a base set of parameters initialized to something valid
  Control::Ptr u;
  u.reset(ocp.control->clone());
  u->initialize();

  // Create a direction initialized to something random
  Control::Ptr p;
  p.reset(ocp.control->clone());
  p->set_direction();

  // Run the test multiple times while halving the search direction
  for(int i=0;i<1;i++){

    if (i>0)
      comm->cout()
        << "================================================================\n"
        << "             Re-running with half the step size                 \n"
        << "================================================================\n";

    // Compute a regular forward solve, y(u).  Save the state.
    copy(u,ocp.control);
    ocp.state->set_initial_condition();
    ocp.state->save();
    ocp.state->compute(ocp.optimizer->get_npredict(),ocp.control);

    // Next, compute a linearized forward solve y'(u)p.  Save the state
    copy(u,ocp.control);
    copy(p,locp.control);
    locp.state->set_initial_condition();
    locp.state->save();
    locp.state->compute(locp.optimizer->get_npredict(),locp.control);

    // Do a finite difference check on the linearized state

    // Get y'(u)p at the given timestep
    DGM::Domain* ldomain=dynamic_cast <Domain*> (locp.state);
    vField yp;
    yp.clone(ldomain->U);
    ldomain->read(root+".lin." + step + ".rst",yp);

    // Get y(u) at the given timestep
    DGM::Domain* domain=dynamic_cast <Domain*> (ocp.state);
    vField y;
    y.clone(domain->U);
    domain->read(root+"." + step + ".rst",y);

    // Create storage for the perturbed point
    Control::Ptr u_eps;
    u_eps.reset(ocp.control->clone());

    // Create storage for the point y(u + eps p) at the given timestep
    vField y_p_eps;
    y_p_eps.clone(domain->U);

#if DGM_LINTEST_ORDER > 1
    // Create storage for the point y(u - eps p) at the given timestep
    vField y_m_eps;
    y_m_eps.clone(domain->U);
#endif

#if DGM_LINTEST_ORDER > 2
    // Create storage for the point y(u - 2 eps p) at the given timestep
    vField y_m2_eps;
    y_m2_eps.clone(domain->U);

    // Create storage for the point y(u + 2 eps p) at the given timestep
    vField y_p2_eps;
    y_p2_eps.clone(domain->U);
#endif

    // Create storage for the finite difference approximation to y'(u)p
    vField yp_fd;
    yp_fd.clone(domain->U);

    // Create storage for the residual y'(u)p - y_fd(u)p
    vField yp_delta;
    yp_delta.clone(domain->U);

    for(int i=DGM_LINTEST_LOWER;i<=DGM_LINTEST_UPPER;i++){

#if DGM_LINTEST_ORDER == 2

      // Determine u + epsilon * p
      Scalar epsilon=pow(0.1,i);
      copy(u,u_eps);
      axpy(epsilon,p,u_eps);

      // Determine y_eps=y(u+eps p) over all time
      copy(u_eps,ocp.control);
      ocp.state->set_initial_condition();
      ocp.state->save();
      ocp.state->compute(ocp.optimizer->get_npredict(),ocp.control);

      // Read in y(u+eps p) at the given timestep
      domain->read(root+"." + step + ".rst",y_p_eps);

      // Determine u - epsilon * p
      copy(u,u_eps);
      axpy(-epsilon,p,u_eps);

      // Determine y_meps=y(u-eps p) over all time
      copy(u_eps,ocp.control);
      ocp.state->set_initial_condition();
      ocp.state->save();
      ocp.state->compute(ocp.optimizer->get_npredict(),ocp.control);

      // Read in y(u+eps p) at the given timestep
      domain->read(root+"." + step + ".rst",y_m_eps);

      // Determine (y(u+eps p)-y(u-esp p))/(two epsilon)
      copy(y_p_eps,yp_fd);
      axpy(-one,y_m_eps,yp_fd);
      scale(pt5/epsilon,yp_fd);

#elif DGM_LINTEST_ORDER == 4

      // Determine u + epsilon * p
      Scalar epsilon=pow(0.1,i);
      copy(u,u_eps);
      axpy(epsilon,p,u_eps);

      // Determine y_eps=y(u+eps p) over all time
      copy(u_eps,ocp.control);
      ocp.state->set_initial_condition();
      ocp.state->save();
      ocp.state->compute(ocp.optimizer->get_npredict(),ocp.control);

      // Read in y(u+eps p) at the given timestep
      domain->read(root+"." + step + ".rst",y_p_eps);

      // Determine u + 2 epsilon * p
      copy(u,u_eps);
      axpy(two*epsilon,p,u_eps);

      // Determine y_p_eps=y(u + 2 eps p) over all time
      copy(u_eps,ocp.control);
      ocp.state->set_initial_condition();
      ocp.state->save();
      ocp.state->compute(ocp.optimizer->get_npredict(),ocp.control);

      // Read in y(u + 2 eps p) at the given timestep
      domain->read(root+"." + step + ".rst",y_p2_eps);

      // Determine u - epsilon * p
      copy(u,u_eps);
      axpy(-epsilon,p,u_eps);

      // Determine y_m_eps=y(u - eps p) over all time
      copy(u_eps,ocp.control);
      ocp.state->set_initial_condition();
      ocp.state->save();
      ocp.state->compute(ocp.optimizer->get_npredict(),ocp.control);

      // Read in y(u - eps p) at the given timestep
      domain->read(root+"." + step + ".rst",y_m_eps);

      // Determine u - 2 epsilon * p
      copy(u,u_eps);
      axpy(-two*epsilon,p,u_eps);

      // Determine y_m2_eps=y(u - 2 eps p) over all time
      copy(u_eps,ocp.control);
      ocp.state->set_initial_condition();
      ocp.state->save();
      ocp.state->compute(ocp.optimizer->get_npredict(),ocp.control);

      // Read in y(u - 2 eps p) at the given timestep
      domain->read(root+"." + step + ".rst",y_m2_eps);

      // Determine fourth-order finite-difference
      copy(y_p_eps,yp_fd);
      axpy(-one,y_m_eps,yp_fd);
      scale(8.0,yp_fd);
      axpy(-one,y_p2_eps,yp_fd);
      axpy( one,y_m2_eps,yp_fd);
      scale(one/(12.0*epsilon),yp_fd);
#else
      // Determine u + epsilon * p
      Scalar epsilon=pow(0.1,i);
      copy(u,u_eps);
      axpy(epsilon,p,u_eps);

      // Determine y_p_eps=y(u+eps p) over all time
      copy(u_eps,ocp.control);
      ocp.state->set_initial_condition();
      ocp.state->save();
      ocp.state->compute(ocp.optimizer->get_npredict(),ocp.control);

      // Read in y(u+eps p) at the given timestep
      domain->read(root+"." + step + ".rst",y_p_eps);

      // Determine (y(u+eps p)-y(u))/epsilon
      copy(y_p_eps,yp_fd);
      axpy(-one,y,yp_fd);
      scale(one/epsilon,yp_fd);
#endif

      // Now, take the relative difference between yp and yp_approx in norm
      copy(yp,yp_delta);
      axpy(-one,yp_fd,yp_delta);
      Scalar delta=sqrt(vField::L2_inner_product(yp_delta,yp_delta));
      Scalar normf=sqrt(vField::L2_inner_product(yp,yp));
      if (normf!=0) {
        Format sci(8); sci.scientific().width(14);
        comm->cout()
          << "The relative difference (1e-" << i << "): "
          << sci(delta/normf) << endl;
      } else {
        Format sci(8); sci.scientific().width(14);
        comm->cout()
          << "The absolute difference (1e-" << i << "): "
          << sci(delta) << endl;
      }
    }

    // Half the size of the search direction
    scale(.5,p);
  }
}
}

#endif   // DGM_LIN_TEST_HPP
