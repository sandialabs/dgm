#ifndef DGM_MULTI_OPT_PROBLEM_HPP
#define DGM_MULTI_OPT_PROBLEM_HPP

#ifdef DGM_PARALLEL

/** \file MultiOptProblem.hpp
    \brief Multiple Optimal Control Problem
    \author Joe Young
    \author Scott Collis
*/

// system includes
#include <sys/stat.h>
#include <unistd.h>
#include <limits>
#include <sstream>
#include <iostream>

// DGM includes
#ifdef DGM_PARALLEL
#include "MpiComm.hpp"
#endif
#include "ArgList.hpp"
#include "Table.hpp"
#include "BlackBox.hpp"
#include "Control.hpp"
#include "Domain.hpp"
#include "Format.hpp"
#include "BlackBox.hpp"

// boost includes
#include "boost/lexical_cast.hpp"

// local include
#include <limits>

using DGM::Control;
using DGM::Table;
using DGM::Domain;
using DGM::Source;
using DGM::Format;
using DGM::Obs;

namespace DGM {

/// Functions for determining the multi-parallel optimization
namespace Multi {

/** Returns the smallest group size given the total number of objects
    divided between the specified number of groups */
int get_smallest(int total,int ngroups);

/// Returns the largest group size
int get_largest(int total,int ngroups);

/** Returns the number of groups that contain extra objects (the largest
    group size) */
int get_extra(int total,int ngroups);

/// Given an id to an object, determine which group this object belongs
int get_group(int total,int ngroups,int id);

/// Given an id to an object, determine the id to the head of the group
int get_head(int total,int ngroups,int id);

/** Given an id to an object, determine the number of objects in that id's
    group. */
int get_num_in_group(int total,int ngroups,int id);

/// Divides some integer between groups as evenly as possible
int divide_groups(int total,int ngroups,int id);

}  // namespace Multi

/// DGM Optimal control problem for use in multi-source optimization routines
template <class OptProblem>
class MultiOptProblem {

public:

  /// Create a shortcut for the OptProblem type
  typedef typename DGM::Shared<OptProblem>::Ptr OptProblemPtr;

private:

  /// The objective function name
  string oname;

  /// Directory temporary files are written to
  string dirname;

  /// Local parameter table
  DGM::Table params;

  /// Last point that we evaluated at
  DGM::Control::Ptr x_last;

  /// Last objective value we calculated
  Scalar obj_last;

  /// Whether to recompute the State (default is true)
  bool recomputeState;

  /// Prints out the message.  In addition, if it's the head node, it writes
  /// the message to the .ocs file.
  void print(const std::string msg) const {
    // Determine if we're the head node.
    bool head_node = gcomm->MyPID()==0 && rcomm->MyPID()==0;

    // If we're the head node, open the file for writing
    std::string fname = root + ".ocs";
    std::ofstream fout;
    if(head_node) {
        fout.open(fname.c_str(),std::ios::app);
        if(!fout.is_open())
          gcomm->error("Unable to open the file " + fname + " for writing.");
    }

    // Write the message to the screen
    gcomm->cout() << msg << std::endl;

    // Write the message to file and close the file
    if(head_node) {
      fout << msg << std::endl;
      fout.close();
    }
  }

  /** Computes either the state or, given a state, the gradient.  More
      specifically, if we let h:U->Y be the state operator to the problem
      and r:Y->Y be the residual operator, then this function has the
      following semantics:
      do_grad=false : y=h(u) to disk.  return .5*||r(y)||.
      do_grad=true : h'(u)^* r'(y)^* r(y)
   */
  void state_gradient_compute(
    bool do_grad,
    const Control::Ptr& p,
    Scalar& obj_val,
    Control::Ptr& g
    ){

    // SSC:  These should just use the Control::clone methods

    // Make a control to aggregate our results
    dVector grad_loc(ocp->optimizer->gradient->phi.size());

    // Make controls to aggregate our final results
    dVector grad_agg(ocp->optimizer->gradient->phi.size());

    // Make a control to aggregate our preconditioner
    dVector precond_loc(ocp->optimizer->gradient->phi.size());

    // Make a control to aggregate our final preconditioner
    dVector precond_agg(ocp->optimizer->gradient->phi.size());

    // Get a pointer to the domain so that we can reset the sources later
    // Domain *domain=ocp->adjoint->domain();

    // Loop over all of the PDEs that we need to solve
    Scalar obj_val_loc=0.0;
    for(vector < vector<Scalar> >::iterator weight=weights.begin();
        weight!=weights.end();weight++){

      // Set the right hand side
      dVector weight_copy(npdes);
      for(size_t i=0;i<weight->size();i++) weight_copy[i]=(*weight)[i];
      ocp->objective->reset(oname,weight_copy);

      // Copy in the parameters p.  Again, we cannot do a simply alias, but
      // require this class to own the memory for the reasons given above.
      copy(p,ocp->control);

      // In either case, forward or adjoint, we set the initial condition
      ocp->state->set_initial_condition();
      chdir(dirname.c_str());
      // If we do the adjoint, compute and save the forward solve, then
      // follow with the adjoint solve
      if(do_grad){
        // Forward solve
        ocp->state->save();
        obj_val_loc += ocp->state->
          compute(ocp->optimizer->get_npredict(),ocp->control);

        // Adjoint solve
        ocp->adjoint->set_end_condition();
        ocp->adjoint->compute( ocp->optimizer->get_npredict(), ocp->control,
                               ocp->optimizer->gradient, 1 );
      } else {
        // Otherwise, don't save the solution and just do the forward solve
        ocp->state->no_save();
        obj_val_loc += ocp->state->test(ocp->optimizer->get_npredict(),
                                        ocp->control);
      }
      chdir("..");

      // Copy the result into the aggregator
      if(do_grad){
        // If we're on the first iteration, move the result into the
        // aggregate
        if(weight==weights.begin()){
          grad_loc=ocp->optimizer->gradient->phi;
          precond_loc=diag_precond->phi;
        }
        // On subsequent iterations, add them together
        else{
          dvadd( ocp->optimizer->gradient->phi, grad_loc);
          dvadd( diag_precond->phi, precond_loc);
        }
      }
    }

    // After running over all the PDEs, accumulate the rest of the results
    if(do_grad){
      // Accumulate the gradient
      rcomm->SumAll(grad_loc.ptr(),grad_agg.ptr(),grad_agg.size());
      ocp->optimizer->gradient->phi=grad_agg;
      copy(optimizer->gradient,g);

      // Accumulate the preconditioner
      rcomm->SumAll(precond_loc.ptr(),precond_agg.ptr(),precond_agg.size());
      diag_precond->phi=precond_agg;
    }
    // Accumulate the objective
    rcomm->SumAll(&obj_val_loc,&obj_val,1);
  }

  // Conducts a finite difference approximation of the linearized
  // state at the point u in the direction eta at the timestep step.
  void linearized_state_fd(
    const Control::Ptr& u,
    const Control::Ptr& eta,
    const Scalar epsilon,
    const int step,
    vField& yp_fd
    ){
    // Create storage for the perturbed point
    Control::Ptr u_eps;
    u_eps.reset(ocp->control->clone());

    // Find the domain for the problem
    DGM::Domain* domain=dynamic_cast <Domain*> (ocp->state);

    // Set the file name that we'll read the linearized state from
    string file=root + "." + boost::lexical_cast<std::string>(step)+".rst";

    // Create storage for the point y(u +/- {1,2}eps p) at the given
    // timestep
    vField y_p_eps(domain->get_comm()), y_m_eps(domain->get_comm());
    vField y_p2_eps(domain->get_comm()), y_m2_eps(domain->get_comm());
    y_p_eps.clone(domain->U); y_m_eps.clone(domain->U);
    y_p2_eps.clone(domain->U); y_m2_eps.clone(domain->U);

    // Make a variable to locally aggregate the result.
    vField yp_loc(domain->get_comm());
    yp_loc.clone(domain->U);

    // Loop over all of the PDEs that we need to solve
    for(vector < vector<Scalar> >::iterator weight=weights.begin();
        weight!=weights.end();weight++){

      // Set the right hand side
      dVector weight_copy(npdes);
      for(size_t i=0;i<weight->size();i++) weight_copy[i]=(*weight)[i];
      ocp->objective->reset(oname,weight_copy);

      // Determine u + epsilon * eta
      copy(u,u_eps);
      axpy(epsilon,eta,u_eps);

      // Determine y_eps=y(u+eps eta) over all time
      copy(u_eps,ocp->control);
      ocp->state->set_initial_condition();
      chdir(dirname.c_str());
      ocp->state->save();
      header(gcomm->cout(),"Compute y(u+eps eta)");
      ocp->state->compute(ocp->optimizer->get_npredict(),ocp->control);

      // Read in y(u+eps eta) at the given timestep
      domain->read(file,y_p_eps);
      chdir("..");

      // Determine u + 2 epsilon * eta
      copy(u,u_eps);
      axpy(2.*epsilon,eta,u_eps);

      // Determine y_p_eps=y(u + 2 eps eta) over all time
      copy(u_eps,ocp->control);
      ocp->state->set_initial_condition();
      chdir(dirname.c_str());
      ocp->state->save();
      header(gcomm->cout(),"Compute y(u+2eps eta)");
      ocp->state->compute(ocp->optimizer->get_npredict(),ocp->control);

      // Read in y(u + 2 eps p) at the given timestep
      domain->read(file,y_p2_eps);
      chdir("..");

      // Determine u - epsilon * eta
      copy(u,u_eps);
      axpy(-epsilon,eta,u_eps);

      // Determine y_m_eps=y(u - eps eta) over all time
      copy(u_eps,ocp->control);
      ocp->state->set_initial_condition();
      chdir(dirname.c_str());
      ocp->state->save();
      header(gcomm->cout(),"Compute y(u-eps eta)");
      ocp->state->compute(ocp->optimizer->get_npredict(),ocp->control);

      // Read in y(u - eps eta) at the given timestep
      domain->read(file,y_m_eps);
      chdir("..");

      // Determine u - 2 epsilon * eta
      copy(u,u_eps);
      axpy(-2.*epsilon,eta,u_eps);

      // Determine y_m2_eps=y(u - 2 eps eta) over all time
      copy(u_eps,ocp->control);
      ocp->state->set_initial_condition();
      chdir(dirname.c_str());
      ocp->state->save();
      header(gcomm->cout(),"Compute y(u-2eps eta)");
      ocp->state->compute(ocp->optimizer->get_npredict(),ocp->control);

      // Read in y(u - 2 eps eta) at the given timestep
      domain->read(file,y_m2_eps);
      chdir("..");

      // Determine fourth-order finite-difference
      copy(y_p_eps,yp_fd);
      axpy(-1.,y_m_eps,yp_fd);
      scale(8.,yp_fd);
      axpy(-1.,y_p2_eps,yp_fd);
      axpy(1.,y_m2_eps,yp_fd);
      scale(1./(12.*epsilon),yp_fd);

      // Copy the result into the aggregator
      // If we're on the first iteration, move the result into the
      // aggregate
      if(weight==weights.begin())
        yp_loc=yp_fd;
      // On subsequent iterations, add them together
      else
        add(yp_fd,yp_loc);
    }

    // After running over all the PDEs, accumulate the rest of the results
    // and story the result in yp_fd.
    dVector loc(yp_loc.qtot());
    dVector agg(yp_loc.qtot());
    yp_loc.extract(loc);
    rcomm->SumAll(loc.ptr(),agg.ptr(),agg.size());
    yp_fd.fill(agg);
  }

  /// Computes a finite difference approximation to the inner product
  /// between Gauss-Newton Hessian applied to the direction eta and
  /// xi
  Scalar gauss_newton_fd_innr(const Control::Ptr& u,
                              const Control::Ptr& eta,
                              const Control::Ptr& xi,
                              const Scalar eps){

    // Make a control to aggregate our results
    dVector gn_loc(ocp->optimizer->gradient->phi.size());

    // Make controls to aggregate our final results
    dVector gn_agg(ocp->optimizer->gradient->phi.size());

    // Loop over all of the PDEs that we need to solve
    Scalar J_eta_p_xi_loc=0.;
    Scalar J_eta_m_xi_loc=0.;
    Scalar J_eta_p2_xi_loc=0.;
    Scalar J_eta_m2_xi_loc=0.;

    for(vector < vector<Scalar> >::iterator weight=weights.begin();
        weight!=weights.end();weight++){

      // Set the right hand side
      dVector weight_copy(npdes);
      for(size_t i=0;i<weight->size();i++)
        weight_copy[i]=(*weight)[i];
      ocp->objective->reset(oname,weight_copy);
      locp->objective->reset(oname,weight_copy);

      // Compute a regular forward solve.  Save the state.
      copy(u,ocp->control);
      ocp->state->set_initial_condition();
      chdir(dirname.c_str());
      ocp->state->save();
      header(gcomm->cout(),"Compute the regular forward solve, y(u)");
      ocp->state->compute(ocp->optimizer->get_npredict(),ocp->control);
      chdir("..");

      // Next, compute a linearized forward solve in the direction
      // eta + eps xi.  Do not save the state.
      copy(u,ocp->control);
      copy(eta,locp->control);
      axpy(eps,xi,locp->control);
      locp->state->set_initial_condition();
      chdir(dirname.c_str());
      locp->state->no_save();
      header(gcomm->cout(),"Compute the linearized forward solve, "
                           "y'(u)(eta+eps xi)");
      J_eta_p_xi_loc+=
        locp->state->test(locp->optimizer->get_npredict(),locp->control);
      chdir("..");

      // Next, compute a linearized forward solve in the direction
      // eta - eps xi.  Do not save the state.
      copy(u,ocp->control);
      copy(eta,locp->control);
      axpy(-eps,xi,locp->control);
      locp->state->set_initial_condition();
      chdir(dirname.c_str());
      locp->state->no_save();
      header(gcomm->cout(),"Compute the linearized forward solve, "
                           "y'(u)(eta-eps xi)");
      J_eta_m_xi_loc+=
        locp->state->test(locp->optimizer->get_npredict(),locp->control);
      chdir("..");

      // Next, compute a linearized forward solve in the direction
      // eta + 2 eps xi.  Do not save the state.
      copy(u,ocp->control);
      copy(eta,locp->control);
      axpy(2.0*eps,xi,locp->control);
      locp->state->set_initial_condition();
      chdir(dirname.c_str());
      locp->state->no_save();
      header(gcomm->cout(),"Compute the linearized forward solve, "
                           "y'(u)(eta+2eps xi)");
      J_eta_p2_xi_loc+=
        locp->state->test(locp->optimizer->get_npredict(),locp->control);
      chdir("..");

      // Next, compute a linearized forward solve in the direction
      // eta - 2 eps xi.  Do not save the state.
      copy(u,ocp->control);
      copy(eta,locp->control);
      axpy(-2.0*eps,xi,locp->control);
      locp->state->set_initial_condition();
      chdir(dirname.c_str());
      locp->state->no_save();
      header(gcomm->cout(),"Compute the linearized forward solve, "
                           "y'(u)(eta-2eps xi)");
      J_eta_m2_xi_loc+=
        locp->state->test(locp->optimizer->get_npredict(),locp->control);
      chdir("..");
    }

    // Accumulate the objectives
    Scalar J_eta_p_xi, J_eta_m_xi, J_eta_p2_xi, J_eta_m2_xi;
    rcomm->SumAll(&J_eta_p_xi_loc,&J_eta_p_xi,1);
    rcomm->SumAll(&J_eta_m_xi_loc,&J_eta_m_xi,1);
    rcomm->SumAll(&J_eta_p2_xi_loc,&J_eta_p2_xi,1);
    rcomm->SumAll(&J_eta_m2_xi_loc,&J_eta_m2_xi,1);

    // Compute the finite difference
    return (J_eta_m2_xi-8.*J_eta_m_xi+8.*J_eta_p_xi-J_eta_p2_xi)/(12.*eps);
  }

public:

  /// Communicator for the sub group
  DGM::Shared <DGM::Comm>::Ptr gcomm;

  /** Communicator between processors with the same rank, but
      in different subgroups. */
  DGM::Shared <DGM::Comm>::Ptr rcomm;

  /// DGM optimal control problem
  OptProblemPtr ocp;

  /// DGM linearized optimal control problem
  OptProblemPtr locp;

  /// DGM Blackbox optimizer
  DGM::BlackBox *optimizer;

  // Number of prediction steps.  We do not use this value, but it is
  // used in some of the old file formats.
  int npredict;

  /// Group number the node belongs to
  int gnum;

  /// Position in the current group
  int rnum;

  /// Total number of pdes in the problem
  int npdes;

  /// Weights used for each pde
  vector < vector <Scalar> > weights;

  /// The root file name for this problem
  string root;

  /// Diagonal preconditioner
  Control::Ptr diag_precond;

  static void line(ostream &out, const char c='=', const int w=80) {
    char prev = out.fill(c);
    out.width(w-1);
    out << c << std::endl;
    out.fill(prev);
  }

  static void header(ostream &out, const string head,
                     const char c='=', const int w=80) {
    line(out,c,w);
    out << head << std::endl;
    line(out,c,w);
  }

  /// Allows this object to extract arguments
  /** If MultiOptProblem had been properly derived off of DGM::Problem,
      then this wouldn't have been necessary. */
  static void parse_args(DGM::ArgList &args, DGM::Table &params) {
    std::string name, value;

    // get basic information from argument list
    std::string code = args.front();
    if (args.size() < 2) {
      showUsage(code);
      exit(1);
    }
    std::string root = args.back();

    std::list< DGM::ArgList::iterator > li;
    for ( DGM::ArgList::iterator a = args.begin(); a != args.end(); a++ ) {
      if ( (*a)[0] == '-' ) {
        name = *a;
        if (name == "-help") {
          params["showUsage"] = 1;
          showUsage(code);
        } else if (name == "-opttype") {
          li.push_back(a);
          value = *(++a);
          li.push_back(a);
          params["opttype"] = atoi(value.c_str());
        }
      }
    }
#ifdef DGM_REMOVE_ARGUMENTS
    // remove tagged arguments
    for ( std::list< DGM::ArgList::iterator >::iterator a=li.begin();
          a!=li.end(); a++) args.erase(*a);
#endif
  }

  /// Shows the supported command line arguments
  /** If MultiOptProblem had been properly derived off of DGM::Problem then
      this wouldn't have been necessary. */
  static void showUsage(const std::string &code) {
    std::cerr
      << "DGM::MultiOptProblem Class Options \n"
      << "---------------------------------------------------------------\n"
      << "-opttype #" << '\t' << "Type of optimizer to use (see docs)    \n"
      << "---------------------------------------------------------------\n";
  }

  /// Constructor
  MultiOptProblem(
    const int ngroups,
    const string oname_,
    DGM::ArgList &args,
    const DGM::Table &table=DGM::Table(),
    const DGM::Comm::Ptr comm=DGM::Comm::World,
    const bool build_linearized=false
  ) : oname(oname_), params(table),
      obj_last(std::numeric_limits<Scalar>::quiet_NaN()),
      recomputeState(true)
  {
    // Grab the root file name
    root=args.back();

    // Grab the npredict variable.  We do not use this, but some of the old
    // file formats like to see this value
    params["npredict"] = 0;
    params["opttype"] = OptProblem::BLACKBOX;

    params.read(root+".inp");

    parse_args(args,params);

    npredict = params["npredict"];
    const int opttype = params["opttype"];

    // Read extra Json parameters
    if (comm->Master()) {
      Json::Value value;
      string file = root + ".json";
      ifstream json(file.c_str());
      if (json) {
        Json::Reader reader;
        if (!reader.parse(json,value,true)) {
          throw DGM::exception("Failed to parse the parameter file " +
                               file + ":  " +
                               reader.getFormattedErrorMessages());
        }
        if (value.isMember("MultiOptProblem")) {
          value = value["MultiOptProblem"];
          recomputeState = value.set("Recompute state",recomputeState).asBool();
          const int verb = value.set("Verbosity",0).asInt();
          if (verb) {
            Json::StyledWriter writer;
            string output = writer.write(value);
            cout << "Read MultiOptProblem extra parameters:\n" << output;
          }
        }
      }
    }
    comm->Broadcast(&recomputeState);

    // Determine the number of processors
    int nprocs=comm->NumProc();

    // Verify that the number of groups divides the number of processors
    if( nprocs % ngroups != 0) {
      if(comm->MyPID()==0)
        comm->cerr() << "Number of parallel solves ("
                     << ngroups << ") must divide the number of processors ("
                     << nprocs << ")" << endl;
      comm->exit(DGM::FAILURE);
    }
    //
    // Create the subgroup that this processor belongs
    //
    int myid=comm->MyPID();
    // Get the new group number
    gnum=Multi::get_group(nprocs,ngroups,myid);
    // Get the number of processors in the new group
    int ng=Multi::get_num_in_group(nprocs,ngroups,myid);
    // Get the starting node in the group
    int s=Multi::get_head(nprocs,ngroups,myid);
    // Create an array containing all the ids in the group
    vector <int> gids(ng);
    for(int i=0;i<ng;i++) gids[i]=s+i;
    // Create the sub communicator.  For the time being, let us supress
    // output from all groups save group 0.
    // \warning This leaks memory and should be fixed.
    ostream* gout=new ostream(std::cout.rdbuf());
    gout->clear(std::ios::failbit);
    if(gnum==0)
      gcomm=DGM::Comm::Ptr(comm->CreateSubComm(gids));
    else
      gcomm=DGM::Comm::Ptr(comm->CreateSubComm(gids,"",*gout,*gout));

    // Based on this subgroup, create an OptProblem
    if (opttype != OptProblem::BLACKBOX)
      throw DGM::exception("PEopt requires a BlackBox optimizer");

    ocp=OptProblemPtr(new OptProblem(args,params,gcomm));

    // In a similar manner, create the linearized OptProblem
    if(build_linearized)
      locp=OptProblemPtr(new OptProblem(ocp.get(),args,params,gcomm));

    // Hook the diagonal preconditioner to the adjoint PDE solver in the
    // base optimization objective
    diag_precond.reset(ocp->optimizer->gradient->clone());
    ocp->adjoint->set_preconditioner(diag_precond);

    // Check that we're using the black box optimizaer
    optimizer=dynamic_cast<DGM::BlackBox*>(ocp->optimizer);
    if (!optimizer){
      if(comm->MyPID()==0)
        comm->cerr() << "The multisource optimal control problem must use "
          "the BlackBox Optimizer (opttype=" << OptProblem::BLACKBOX <<
          ")" << std::endl;
      comm->exit(DGM::FAILURE);
    }
    //
    // Next, create a group that contains members who share the same rank in
    // their new subgroup.
    //
    vector <int> rids;
    for(int i=0;i<nprocs;i++){
      // Find the head of the group given this processor
      s=Multi::get_head(nprocs,ngroups,i);
      // Figure out the group id for this processor based on the head
      int gid=i-s;
      // If this id matches this processors group id, then add it to the rank
      // ids that the new communicator is based on
      if(gid==gcomm->MyPID()) rids.push_back(i);
    }
    // Create the subcommunicator based on these rank ids.  Similar to above,
    // let us only save the output from group 0.  Note, we allocate additional
    // memory here for the output since each communicator manages its own
    // memory for the output stream.  In theory, the destructor for the
    // communicator should free this memory, so if we share the output stream
    // problems could occur.
    ostream* rout=new ostream(std::cout.rdbuf());
    rout->clear(std::ios::failbit);
    if(gnum==0)
      rcomm=DGM::Comm::Ptr(comm->CreateSubComm(rids));
    else
      rcomm=DGM::Comm::Ptr(comm->CreateSubComm(rids,"",*rout,*rout));

    // Determine the number of PDEs (the number of sequential experiments)
    Domain* domain=ocp->adjoint->domain();
    Source::db_citr src=domain->Source_db.find(oname);
    if(src==domain->Source_db.end())
      comm->error("Could not find objective term named: "+oname+".  This "
      "is specified in the .peopt file.");
    Obs* obs;
    if(!(obs=dynamic_cast <Obs*> (&(*(src->second)))))
      comm->error("Specified objective term in the .peopt file not really "
                  "an observation: "+oname);
    npdes=obs->Nterms();

    // Create a directory for this group and move into it.  This is required
    // to insure that each group can manage its own I/O without interference.
    stringstream str_in;
    str_in << "group-" << gnum;
    dirname=str_in.str();
    mkdir(dirname.c_str(),S_IRWXU);

    // Create a readme file in this directory detailing which PDEs the group
    // will solve in addition to who belongs to this group.
    if(gcomm->MyPID()==0){
      chdir(dirname.c_str());
      fstream fout("README.txt",fstream::out);
      fout << "Group number: " << gnum << endl;
      fout << "Group members: ";
      for(vector <int>::iterator x=gids.begin();x!=gids.end();x++)
        fout << *x << ' ';
      fout << endl;
      fout.close();
      chdir("..");
    }

    // Determine the rank in the particular group
    rnum=gcomm->MyPID();

    // Allocate memory for the last point that we evaluate at
    x_last.reset(ocp->control->clone());

    // Make sure this point is something absurd so that we cache correctly
    // on the first iteration.
    scale(std::numeric_limits<Scalar>::quiet_NaN(),x_last);
  }

  /// Calculates the gradient given a control
  Scalar gradient(const Control::Ptr& x,Control::Ptr& g) {
    // Calculate the gradient
    state_gradient_compute(true,x,obj_last,g);

    // SSC added diagnostic so we can see what is going on
    gcomm->cout()<<"||Grad(J)|| = "<<g->norm()<<std::endl;

    // Store the point that we evaluated at
    DGM::copy(x,x_last);

    // Return the objective value
    return obj_last;
  }

  /// Calculates the objective value given a control
  Scalar obj_func(const Control::Ptr& x) {
#ifdef DGM_CHECK_RECOMPUTE
    // Determine if we've evaluated this point already
    DGM::Control::Ptr diff; diff.reset(x->clone());
    DGM::axpy(-1.,x_last,diff);
    Scalar err=std::sqrt(diff->inner_product(diff.get()));
    // In theory, this should be zero, but this tolerance should be good enough
    if(err<1e-14) {
      return obj_last;
    } else { // If we haven't saved the objective value, calculate it
      Control::Ptr g;
      state_gradient_compute(false,x,obj_last,g);
      DGM::copy(x,x_last);
      return obj_last;
    }
#else
    Control::Ptr g;
    state_gradient_compute(false,x,obj_last,g);
    DGM::copy(x,x_last);
    return obj_last;
#endif
  }

  /// Computes the Gauss-Newton Hessian approximation
  void gauss_newton(const Control::Ptr& u,
                    const Control::Ptr& p,
                    Control::Ptr& p_gn){

    // Make a control to aggregate our results
    dVector gn_loc(ocp->optimizer->gradient->phi.size());

    // Make controls to aggregate our final results
    dVector gn_agg(ocp->optimizer->gradient->phi.size());

    // Get a pointer to the domain so that we can reset the sources later
    //Domain* domain=ocp->adjoint->domain();

    // Loop over all of the PDEs that we need to solve
    //Scalar obj_val_loc=0.;
    for(vector < vector<Scalar> >::iterator weight=weights.begin();
        weight!=weights.end();weight++){

      // Set the right hand side
      dVector weight_copy(npdes);
      for(size_t i=0;i<weight->size();i++)
        weight_copy[i]=(*weight)[i];
      ocp->objective->reset(oname,weight_copy);
      locp->objective->reset(oname,weight_copy);
#if 0
      // make a unique tag for this combination of weights and control
      // Will this work with Griewank?
      stringstream tag;
      tag << "Control=" << &*u << ", weights=" << &*weight;
      //std::cout << "Tag = " << tag.str() << std::endl;

      // Compute a regular forward solve.  Save the state.
      copy(u,ocp->control);
      ocp->state->set_initial_condition();
      chdir(dirname.c_str());
      if (ocp->state->get_tag() != tag.str()) {
        header(gcomm->cout(),"Compute the State...");
        ocp->state->save(tag.str());
        ocp->state->compute(ocp->optimizer->get_npredict(),ocp->control);
      } else {
        gcomm->cout()<<"Using the cached State..."<<endl;
      }
      chdir("..");
#else
      if (!recomputeState) {
        // New stuff that Joe added, but messes up GN check so only use if you
        // know what you are doing and you set "Recompute state" in the json
        // input

        // Clear out any state stored by Griewank.  Because we may have
        // multiple sources (more than one weight), we don't know if the
        // previously calculated state is the one we require for this solve.
        // This means we have two options.  Either we can calculate the state
        // here and then calculated the linearized state or we can calculate
        // the linearized state and allow it to calculate the state on demand.
        // The problem with the first approach is that if the entire state
        // doesn't fit into memory, we're basically going to need to calculate
        // the state on the fly anyway, which puts us into the second
        // situation.  Hence, in order to save an extra state solve every
        // Gauss-Newton application when checkpointing becomes active, we just
        // calculate on the fly.
        ocp->state->griewank.reinitialize(ocp->state->domain());
      } else {
        // Forces a state solve which is slow but fills the database correctly.

        // Compute a regular forward solve.  Save the state.
        copy(u,ocp->control);
        ocp->state->set_initial_condition();
        chdir(dirname.c_str());
        header(gcomm->cout(),"Compute the State...");
        ocp->state->save();
        ocp->state->compute(ocp->optimizer->get_npredict(),ocp->control);
        chdir("..");
      }
#endif
      // Next, compute a linearized forward solve.  Save the linearized state
      copy(u,ocp->control);
      copy(p,locp->control);
      locp->state->set_initial_condition();
      chdir(dirname.c_str());
      locp->state->save();
      header(gcomm->cout(),"Compute the Linearized State...");
      locp->state->compute(locp->optimizer->get_npredict(),locp->control);

      // Finally, compute a regular adjoint using information from both
      // solves above (we need to drive the adjoint solve with the linearized
      // forward solve above.  In theory, our wiring should choose the right
      // file names or memory locations.
      copy(u,ocp->control);
      header(gcomm->cout(),
             "Compute the Adjoint driven by linearized State...");
      locp->adjoint->set_end_condition();

      // The new AcousticAdjoint::prestep stuff necessitates this since
      // it can potentially create a new vector field which requires us
      // to read the .bc file

      /// \note SSC:  I don't understand this.
      string main_bc="../"+root+".lin.bc";
      string new_bc="./"+root+".lin.bc";
      symlink(main_bc.c_str(),new_bc.c_str());
      locp->adjoint->compute(locp->optimizer->get_npredict(),ocp->control,
                             locp->optimizer->gradient, 1 );

      // Move us back into the correct directory
      chdir("..");

      // If we're on the first iteration, move the result into the aggregate
      if(weight==weights.begin())
        gn_loc=locp->optimizer->gradient->phi;

      // On subsequent iterations, add them together
      else
        dvadd( locp->optimizer->gradient->phi, gn_loc );
    }

    // After running over all the PDEs, accumulate the rest of the results
    rcomm->SumAll(gn_loc.ptr(),gn_agg.ptr(),gn_agg.size());
    ocp->optimizer->gradient->phi=gn_agg;
    copy(optimizer->gradient,p_gn);
  }

  /// Computes a finite difference check on the linearized state
  void linearized_state_fd_check(const Control::Ptr& u,const int step){
    // Create a direction in order to compute the finite difference check
    Control::Ptr eta;
    eta.reset(u->clone());
    eta->set_direction();

    // Print out what we're doing
    print("Beginning the difference check on the linearized state.");

    // Find the domain for the problem
    DGM::Domain* domain=dynamic_cast <Domain*> (ocp->state);

    // Set the file name that we'll read the linearized state from
    string file=root +".lin." + boost::lexical_cast<std::string>(step)+".rst";

    // Make a variable to store a slice of the state.  Also, create
    // a variables to locally aggregate the result.
    DGM::Domain* ldomain=dynamic_cast <Domain*> (locp->state);
    vField yp(domain->get_comm()), yp_loc(domain->get_comm());
    yp.clone(ldomain->U);
    yp_loc.clone(ldomain->U);

    // Loop over all of the PDEs that we need to solve
    //Scalar obj_val_loc=0.0;
    for(vector < vector<Scalar> >::iterator weight=weights.begin();
        weight!=weights.end();weight++){

      // Set the right hand side
      dVector weight_copy(npdes);
      for(size_t i=0;i<weight->size();i++) weight_copy[i]=(*weight)[i];
      ocp->objective->reset(oname,weight_copy);

      // Begin by calculating the linearized state in the direction eta.
      // Compute a regular forward solve, y(u).  Save the state.
      copy(u,ocp->control);
      ocp->state->set_initial_condition();
      chdir(dirname.c_str());
      ocp->state->save();
      header(gcomm->cout(),"Compute regular forward solve, y(u)");
      ocp->state->compute(ocp->optimizer->get_npredict(),ocp->control);
      chdir("..");

      // Next, compute a linearized forward solve y'(u)eta.  Save the state
      locp->objective->reset(oname,weight_copy);
      copy(u,ocp->control);
      copy(eta,locp->control);
      locp->state->set_initial_condition();
      chdir(dirname.c_str());
      locp->state->save();
      header(gcomm->cout(),"Compute linearized forward solve, y'(u)eta");
      locp->state->compute(locp->optimizer->get_npredict(),locp->control);

      // Get y'(u)eta the given timestep
      ldomain->read(file,yp);

      // Move back into the correct directory
      chdir("..");

      // Copy the result into the aggregator
      // If we're on the first iteration, move the result into the
      // aggregate
      if(weight==weights.begin())
        yp_loc=yp;
      // On subsequent iterations, add them together
      else
        add(yp,yp_loc);
    }

    // After running over all the PDEs, accumulate the rest of the results
    // and story the result in yp.
    dVector loc(yp_loc.qtot());
    dVector agg(yp.qtot());
    yp_loc.extract(loc);
    rcomm->SumAll(loc.ptr(),agg.ptr(),agg.size());
    yp.fill(agg);

    // Create storage for the finite difference approximation to y'(u)p
    vField yp_fd(domain->get_comm());
    yp_fd.clone(domain->U);

    // Create storage for the residual
    vField yp_delta(domain->get_comm());
    yp_delta.clone(domain->U);

    // Compute several difference approximations
    for(int i=-2;i<=5;i++){
      Scalar eps=pow(.1,i);

      // Find the finite difference approximation to y'(u)eta
      linearized_state_fd(u,eta,eps,step,yp_fd);

      // Find the relative error
      copy(yp,yp_delta);
      axpy(-1.,yp_fd,yp_delta);
      Scalar delta=sqrt(vField::L2_inner_product(yp_delta,yp_delta));
      Scalar norm_yp=sqrt(vField::L2_inner_product(yp,yp));
      if(gnum==0){
        stringstream ss;
        if(i<0)
            ss << "The relative difference (1e+" << -i << "): ";
        else
            ss << "The relative difference (1e-" << i << "): ";
        ss << scientific << setprecision(16)
           << delta/(1e-16+norm_yp);
        print(ss.str());
      }
    }
  }

  /// Computes a finite difference check on the Gauss-Newton Hessian
  void gauss_newton_fd_check(const Control::Ptr& u){
    // Create two directions.  We will evaluate compute a finite difference
    // check to <H(u)eta,xi>.
    Control::Ptr eta,xi;
    eta.reset(u->clone());
    xi.reset(u->clone());
    eta->set_direction();
    xi->set_direction();

    // Print out what we're about to do.
    print("Beginning the difference check on the Gauss-Newton Hessian.");

    // Begin by calculating the Hessian vector product H(u)eta
    Control::Ptr H_eta;
    H_eta.reset(u->clone());
    gauss_newton(u,eta,H_eta);

    // Find the inner product between H(u)eta and xi
    Scalar innr_Heta_xi=xi->inner_product(H_eta.get());

    // Compute several difference approximations
    for(int i=-2;i<=5;i++){
      Scalar eps=pow(.1,i);

      // Find the finite difference approximation to <H(u)eta,xi>
      Scalar innr_Heta_xi_fd=gauss_newton_fd_innr(u,eta,xi,eps);

      // Find the relative error
      if(gnum==0){
        std::stringstream ss;
        if(i<0)
          ss << "The relative difference (1e+" << -i << "): ";
        else
          ss << "The relative difference (1e-" << i << "): ";
        ss << scientific << setprecision(16)
           << fabs(innr_Heta_xi-innr_Heta_xi_fd)/(1e-16+fabs(innr_Heta_xi));
        print(ss.str());
      }
    }
  }

  /// Compute the difference between two control files
  virtual Ordinal diff(const string& ctl1, const string& ctl2,
                       const Scalar aeps, const Scalar reps) {
    return optimizer->diff(ctl1, ctl2, aeps, reps);
  }

  virtual ~MultiOptProblem() {}
};

}  // namespace DGM

#endif  // DGM_PARALLEL

#endif  // DGM_MULTI_OPT_PROBLEM_HPP
