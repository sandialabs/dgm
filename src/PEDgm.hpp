#ifndef DGM_PEDGM_HPP
#define DGM_PEDGM_HPP

/** \file PEDgm.hpp
    \brief Provides DGM specific functionality to peopt.
    \author Joe Young
    \author Scott Collis
    \copyright (c)2013 Sandia National Laboratories
*/

// system includes
#include <iostream>
#include <memory>

// DGM includes
#include "Comm.hpp"
#include "MultiOptProblem.hpp"
#include "Regularization.hpp"
#include "Format.hpp"

// peopt includes
#include "peopt/peopt.h"
#include "peopt/json.h"

// Boost includes
#include <boost/numeric/conversion/cast.hpp>

using boost::numeric_cast;
using std::streamoff;

/// DGM interface to the PEopt library
namespace peopt {

  // Writes out a string to file
  void write_string(string fname,string output);

  /// Defines the Hilbert space for the DGM controls
  template <typename Real>
  struct DGM_HS {

    /// Create a shortcut for the control space
    typedef DGM::Control::Ptr Vector;

    /// Scalar multiple
    static void scal(const Real alpha, Vector& x){
      DGM::scale(alpha,x);
    }

    /// Copy
    static void copy(const Vector& from, Vector& to){
      DGM::copy(from,to);
    }

    /// alpha*x+y
    static void axpy(const Real alpha, const Vector& x, Vector& y){
      DGM::axpy(alpha,x,y);
    }

    /// Takes an element and sets it to all zeros
    static void zero(Vector& x){
      scal(0.,x);
    }

    /// Inner product
    static Real innr(const Vector& x, const Vector& y){
      return x->inner_product(y.get());
    }

    /// Initializes one vector from another
    static void init(const Vector& from, Vector& to){
      to.reset(from->clone());
    }

    /// Jordan product, z <- x o y
    static void prod(const Vector& x, const Vector& y, Vector& z) { }

    /// Identity element, x <- e such that x o e = x
    static void id(Vector& x) { }

    /// Jordan product inverse, z <- inv(L(x)) y where L(x) y = x o y
    static void linv(const Vector& x,const Vector& y,Vector& z) { }

    /// Barrier function, barr <- barr(x) where x o grad barr(x) = e
    static Real barr(const Vector& x) { return Real(0.);}

    /// Line search, srch <- argmax {alpha in Real >= 0 : alpha x + y >= 0}
    /// where y > 0.  If the argmax is infinity, then return Real(-1.).
    static Real srch(const Vector& x,const Vector& y) { return Real(0.);}

    /// Symmetrization, x <- symm(x) such that L(symm(x)) is a symmetric
    /// operator.
    static void symm(Vector& x) { }
  };

  /// Define the objective function
  template <typename OptProblem>
  struct DGM_Obj : public peopt::ScalarValuedFunction <DGM::Scalar,DGM_HS> {
  public:
    typedef DGM_HS <DGM::Scalar> X;
    typedef DGM::Scalar Real;

  private:
    /// Underlying optimization problem
    DGM::MultiOptProblem <OptProblem> &mocp;

    /// Regularization
    const DGM::Regularization::Base<Real>& reg;

    /// Amount of regularization
    const Real beta;

  public:
    /// Constructor
    DGM_Obj(
      DGM::MultiOptProblem <OptProblem>& mocp_,
      const DGM::Regularization::Base<Real>& reg_,
      Real beta_
    ) : mocp(mocp_), reg(reg_), beta(beta_) {}

    /// Evaluation
    DGM::Scalar operator()(const X::Vector& x) const {
      static DGM::Format sci_hi(10,17,'e');
      // Inform the user of an objective solve
      DGM::MultiOptProblem <OptProblem>::header(mocp.gcomm->cout(),
        "Objective Computation");

      // Apply bounding here
      x->bound();

      // If we're feasible, return the objective function
      if(x->realizable()) {
        const double J = mocp.obj_func(x)+beta*reg(x);
        mocp.gcomm->cout() << "J = " << sci_hi(J) << std::endl;
        return J;
      }
      // If we're not feasible, return a NaN
      else {
        mocp.gcomm->cout()
          << "Current parameter not realizable.  Shortcutting computation."
          << std::endl;
        return std::numeric_limits<DGM::Scalar>::quiet_NaN();
      }
    }

    /// Update for POS                                                           
    void next_pos_selection(X::Vector&, X::Vector&, X::Vector&,
      X::Vector&, X::Vector&, X::Vector&) const {
    }

    /// Gradient
    void grad(
      const X::Vector& x,
      X::Vector& g
    ) const {
      // Inform the user of a gradient solve
      DGM::MultiOptProblem <OptProblem>::header(mocp.gcomm->cout(),
        "Gradient Computation");

      // If we're feasible, compute the gradient
      if(x->realizable()) {
        // Find the gradient of the objective
        mocp.gradient(x,g);

        // Find the gradient of the regularization
        X::Vector g_reg; g_reg.reset(g->clone());
        reg.grad(x,g_reg);

        // Find the overall regularization
        X::axpy(beta,g_reg,g);

      // If we're not feasible, return NaNs in the objective function and
      // gradient
      } else {
        mocp.gcomm->cout()
          << "Current parameter not realizable.  Shortcutting computation."
          << std::endl;
        X::scal(std::numeric_limits<DGM::Scalar>::quiet_NaN(),g);
      }
    }

    /// Hessian-vector product
    void hessvec(
      const X::Vector& x,
      const X::Vector& dx,
      X::Vector& H_dx
    ) const {
      // Inform the user of a Gauss-Newton solve
      DGM::MultiOptProblem <OptProblem>::header(mocp.gcomm->cout(),
        "Hessian-Vector Product Computation");

      // If we're feasible, compute the Gauss-Newton Hessian
      if(x->realizable()) {
        mocp.gauss_newton(x,dx,H_dx);

        // Find the Hessian-vector product of regularization
        X::Vector H_dx_reg; H_dx_reg.reset(H_dx->clone());
        reg.hessvec(x,dx,H_dx_reg);
        X::axpy(beta,H_dx_reg,H_dx);
      }

      // If we're not feasible, return NaNs in the Hessian-vector product
      else {
        mocp.gcomm->cout()
          << "Current parameter not realizable.  Shortcutting computation."
          << std::endl;
        X::scal(std::numeric_limits<DGM::Scalar>::quiet_NaN(),H_dx);
      }
    }
  };

  /// Applies the external diagonal preconditioner
  template <class OptProblem>
  class ExternalPreconditioner :
    public peopt::Operator<DGM::Scalar,DGM_HS,DGM_HS> {
  public:
    typedef DGM_HS <DGM::Scalar> X;
    typedef typename X::Vector X_Vector;
  private:
    /// Underlying optimization problem
    DGM::MultiOptProblem <OptProblem>& mocp;
  public:
    // Grab a reference to the multiopt problem object
    ExternalPreconditioner(DGM::MultiOptProblem <OptProblem>& mocp_)
      : mocp(mocp_) {};

    // Apply the diagonal preconditioner to in and save the result to out
    void operator () ( const X_Vector& in,X_Vector& out) const{
      mocp.diag_precond->applyPreconditioner(in,out);
    }
  };

  /// Messaging object
  struct DGM_Messaging : public peopt::Messaging {
  private:
    // Communicator for printing to screen (and figuring out who the head
    // node is)
    DGM::Shared <DGM::Comm>::Ptr comm;

    // Name of the problem
    std::string name;

    // Whether or not we append the time to the output
    bool add_time;
  public:
    // During construction, copy in the communicator and the root name
    DGM_Messaging(
        DGM::Shared <DGM::Comm>::Ptr comm_,
        std::string name_,
        bool add_time_)
        : comm(comm_), name(name_), add_time(add_time_) {}

    // In this constructor, we don't have a file name, so we don't write to file
    DGM_Messaging(DGM::Shared <DGM::Comm>::Ptr comm_)
        : comm(comm_), add_time(false)
    {
      name.clear();
    }

    // Get current date/time in format YYYY-MM-DD.HH:mm:ss
    const std::string currentDateTime() const {
      time_t     now = time(0);
      struct tm  tstruct;
      char       buf[80];
      tstruct = *localtime(&now);
      strftime(buf, sizeof(buf), "\t%Y-%m-%d.%X", &tstruct);
      if(add_time)
        return buf;
      else
        return "";
    }

    // Prints a message
    void print(const std::string msg) const {
      // Write the output to screen
      comm->cout() << msg + currentDateTime() << std::endl;

      // If we're the head node, write the output to file
      if(comm->MyPID()==0 && name.size() > 0) {
        std::string fname=name + ".ocs";
        std::ofstream fout(fname.c_str(),std::ios::app);
        if(fout.is_open())
          fout << msg + currentDateTime() << std::endl;
        else
          error("Unable to open the file " + fname + " for writing.");
        fout.close();
      }
    }

    // Prints a message to the screen only
    void diagnostic(const std::string msg) const {
      // Write the output to screen
      comm->cout() << msg << std::endl;
    }

    // Prints an error
    void error(const std::string msg) const {
      comm->error(msg + currentDateTime());
    }
  };

  /// Setup some typedefs for unconstrained and inequality constrained problems
  typedef peopt::Unconstrained <DGM::Scalar,peopt::DGM_HS> DGM_Unconstrained;
  typedef peopt::InequalityConstrained <DGM::Scalar,peopt::DGM_HS,peopt::DGM_HS>
    DGM_InequalityConstrained;
  typedef peopt::json::Unconstrained <DGM::Scalar,peopt::DGM_HS>
    DGM_JsonUnconstrained;
  typedef peopt::json::InequalityConstrained
    <DGM::Scalar,peopt::DGM_HS,peopt::DGM_HS> DGM_JsonInequalityConstrained;

  /// Parameters for the problem setup
  namespace Params {

    // Parses a JSON file and returns the root
    Json::Value parse(
      const DGM::Shared <DGM::Comm>::Ptr comm,
      const std::string fname
    );

    /// This merges two different parameter classes.
    template <class A,class B>
    class Merge : public A, public B{
    public:
      /// Reads all the parameters from a file
      void read(string fname) { A::read(fname); B::read(fname); }

      /// Writes the current input to a string
      std::string to_string(){
        std::string output1=A::to_string();
        std::string output2=B::to_string();

        // In the case we have an empty json section, just ignore it
        if(output2=="{ }\n")
            return output1;

        // Otherwise, combine the two sections
        else
            return output1.substr(0,output1.size()-3)+",\n"+
              output2.substr(2,output2.size());
      }

      /// Writes out all the parameters to file
      void write(string fname) { write_string(fname,to_string()); }

      /// Validates the current input arguments
      void validate() { A::validate(); B::validate(); }

      /// Constructor where we make an empty parameter object
      Merge(DGM::Shared <DGM::Comm>::Ptr comm_) : A(comm_), B(comm_) {}
    };

    /// DGM specific parameters
    class Dgm {
    private:
      /// Used for the error messages
      DGM::Shared <DGM::Comm>::Ptr comm;

    public:
      /// How often we write out restart files
      unsigned int restart_file_frequency;

      /// Name of the objective function
      std::string objective_name;

      /// Number of parallel solves
      unsigned int num_groups;

      /// Amount of regularization
      DGM::Scalar beta;

      /// Roundness of the regularization for T.V. style regularization
      DGM::Scalar gamma;

      /// Kind of regularization
      DGM::Regularization::Type::t reg_type;

      /// Problem class that we're solve
      ProblemClass::t problem_class;

      /// Reads all the parameters from a file
      void read(string fname);

      /// Writes the current inputs to a string
      string to_string();

      /// Writes out all the parameters to file
      void write(string fname);

      /// Validates the current input arguments
      void validate();

      /// Constructor where we make an empty parameter object
      Dgm(DGM::Shared <DGM::Comm>::Ptr comm_)
        : comm(comm_), restart_file_frequency(1), objective_name(""),
        num_groups(1), beta(0.), gamma(1e-3),
        reg_type(DGM::Regularization::Type::None),
        problem_class(ProblemClass::Unconstrained) {}
    };

    /// Diagnostic parameters
    class Diagnostic{
    private:
      /// Used for the error messages
      DGM::Shared <DGM::Comm>::Ptr comm;

    public:
      /// Calculate the objective function?
      bool objective;

      /// Calculate a finite difference test on the gradient?
      bool fd_gradient;

      /// Discretize the hessian?
      bool hessian_discretize;

      /// Calculate a finite difference check on the Gauss-Newton Hessian?
      bool fd_gauss_newton;

      /// Calculate a symmetry check on the Hessian?
      bool symmetry_check;

      /// Calculate a finite difference on the linearized state at the
      /// given timestep.  Any negative number means do not do the check.
      int fd_linearized_state;

      /// Do we append the date/time to each line in the output?
      bool add_time;

      /// Reads all the parameters from a file
      void read(string fname);

      /// Writes the current inputs to a string
      string to_string();

      /// Writes out all the parameters to file
      void write(string fname);

      /// Validates the current input arguments
      void validate();

      /// Constructor where we make an empty parameter object
      Diagnostic(DGM::Shared <DGM::Comm>::Ptr comm_)
      : comm(comm_), objective(false), fd_gradient(false),
        hessian_discretize(false), fd_gauss_newton(false),
        symmetry_check(false), fd_linearized_state(-1), add_time(false) {}
    };

    /// Implements all the necessary routines to output the peopt state to
    /// file.
    /** \todo I would like this to be refactored so that only the ctl file
              is produced with a full json header that includes all the peopt
              information. */
    template <typename OptProblem>
    class Restart {
    private:
      /// Used for the error messages
      DGM::Shared <DGM::Comm>::Ptr comm;

    public:
      /// Underlying optimization problem
      DGM::MultiOptProblem <OptProblem>* mocp;

      /// Underlying optimization state
      typename DGM_InequalityConstrained::State::t* state;

      /// Underlying problem class
      ProblemClass::t* dgm_problem_class;

      /// Filename for the binary portions of restart
      std::string bname;

      /// Constructor where we make an empty parameter object
      Restart(DGM::Shared <DGM::Comm>::Ptr comm_)
        : comm(comm_), mocp(NULL), state(NULL),
          dgm_problem_class(NULL), bname("") {}

      /// Finds the position where we append the vectors to file
      streamoff get_append_pos() {
        // Open the file for appending in order to determine how long the
        // file is
        ofstream fout(bname.c_str(),ios_base::app | ios_base::out);

        // Make sure the file is open
        if(!fout.is_open())
          comm->error("Unable to open the file " + bname + " in order to "
            "determine the proper write position for the restart.");

        // Find the file offset and close the file
        streamoff skip=fout.tellp();
        if(fout.fail())
          comm->error("Unable to find the append position in the file "
            + bname + " in order to determine the proper write position for "
            "the restart.");
        fout.close();

        // Return the append position
        return skip;
      }

      /// Writes out the current header to file
      /** \todo This should use the new json header and should be merged
                with the perst file. */
      void writeHeader(
          const unsigned int& iter,
          const DGM::Scalar& norm_dx,
          const DGM::Scalar& norm_grad,
          const int& npredict
      ){
#ifndef DGM_PEOPT_USE_JSON_HEADER
        // Make sure the header is only being written by the head node
        if(mocp->rnum!=0) return;

        // Open the file
        ofstream fout(bname.c_str(),ios_base::out);

        // Make sure the file is open
        if(!fout.is_open())
          comm->error("Unable to open the file " + bname + " in order to "
            "write the restart header.");

        // Write the header
        const int width = 40;
        char now[128]="Time is not available";
#if !defined(DGM_REDSTORM) && !defined(DGM_NO_TIME)
        time_t tp = time(0);
        strftime(now,128,"%a %b %d %H:%M:%S %Y", localtime(&tp));
#endif
        fout.setf(ios::left);
        fout<<setw(width)<<now<<" Created"<<endl;
        fout<<setw(width)<<bname.c_str()<<" Name"<<endl;
        fout<<setw(width)<<iter<<" Iteration"<<endl;
        fout<<setw(width)<<norm_dx<<" Norm dx"<<endl;
        fout<<setw(width)<<norm_grad<<" Gradient L2 norm"<<endl;
        fout<<setw(width)<<npredict+1<<" Time steps"<<endl;
        fout<<setw(width)
            <<mocp->optimizer->get_asv()<<" Active set vector"<<endl;
        fout<<setw(width)<<"<unused>"<<endl;   // make header 10 lines
        fout<<setw(width)<<"<unused>"<<endl;
        fout<<setw(width)<<"BlackBox"<<" Optimizer"<<endl;

        // Check that the header writing went ok
        if(fout.fail())
          comm->error("File I/O error occurred when writing the header "
            "information for the restart file in " + bname);

        // Close the file
        fout.close();
#else
        /// Try out a better way
        mocp->ocp->optimizer->set_j(0.0);
        mocp->ocp->optimizer->set_iter(iter);
        mocp->ocp->optimizer->outputHeader(bname);
#endif
      }

      /// Reads in a vector from X from file
      void readX(
          const streamoff& offset,
          typename DGM_InequalityConstrained::X_Vector& x
      ){
        // Ask the control to read from file
        x->read(bname.c_str(),offset);
      }

      /// Writes out the given control to file
      streamoff writeX(
        const typename DGM_InequalityConstrained::X_Vector& x
      ){
        // The location of where we're writing
        streamoff loc(-1);

        // Find the file offset
        if(mocp->rnum==0) loc=get_append_pos();
        mocp->gcomm->Broadcast(&loc);

        // If the offset is negative, something bad happened and throw
        // an error
        if(loc < 0 )
          comm->error("When writing out a primal control variable, the "
              "location of the write in the restart file was negative.");

        // Write the vector to file
        x->write(bname.c_str(),loc);

        // Return the location where the vector was written
        return loc;
      }

      /// Reads in a vector from Z from file
      void readZ(
          const streamoff& offset,
          typename DGM_InequalityConstrained::Z_Vector& z
      ){
        // Ask the control to read from file
        z->read(bname.c_str(),offset);
      }

      /// Writes out the given control to file
      streamoff writeZ(
        const typename DGM_InequalityConstrained::Z_Vector& z
      ){
        // The location of where we're writing
        streamoff loc(-1);

        // Find the file offset
        if(mocp->rnum==0) loc=get_append_pos();
        mocp->gcomm->Broadcast(&loc);

        if(loc < 0 )
          comm->error("When writing out an inequality multiplier, the location "
            "of the write in the restart file was negative.");

        // Write the vector to file
        z->write(bname.c_str(),loc);

        // Return the location where the vector was written
        return loc;
      }

      /// Reads all the parameters from a file
      void read(string fname) {
        // Make sure that we've successfully attached to an mocp,
        // optimization state, and problem class.  Without this information,
        // we can't restart properly.
        if(mocp==NULL || state==NULL || dgm_problem_class==NULL) return;

        // Read in the input file
        Json::Value root=parse(comm,fname);

        // Reads in the binary file name
        bname=root["Restart"].get("binary data",bname).asString();

        // Check that the binary file exists
        std::ifstream test(bname.c_str());
        bool binary_exists=test.good();
        test.close();
        if(!binary_exists)
          comm->error("We tried to restart from the binary file \""
            + bname + "\", which could not be read.");

        // Setup the peopt parameters
        peopt::DGM_InequalityConstrained::X_Vectors xs;
        peopt::DGM_InequalityConstrained::Z_Vectors zs;
        peopt::DGM_InequalityConstrained::Reals reals;
        peopt::DGM_InequalityConstrained::Nats nats;
        peopt::DGM_InequalityConstrained::Params params;

        // Read in the reals
        for(Json::Value::iterator x=root["Restart"]["Reals"].begin();
          x!=root["Restart"]["Reals"].end();
          x++
        ){
          reals.first.push_back(x.key().asString());
          reals.second.push_back((*x).asDouble());
        }

        // Read in the naturals
        for(Json::Value::iterator x=root["Restart"]["Naturals"].begin();
          x!=root["Restart"]["Naturals"].end();
          x++
        ){
          nats.first.push_back(x.key().asString());
          nats.second.push_back((*x).asUInt64());
        }

        // Read in the parameters
        for(Json::Value::iterator x=root["Restart"]["Parameters"].begin();
          x!=root["Restart"]["Parameters"].end();
          x++
        ){
          params.first.push_back(x.key().asString());
          params.second.push_back((*x).asString());
        }

        // Read in the X vectors
        for(Json::Value::iterator x=root["Restart"]["X Vectors"].begin();
          x!=root["Restart"]["X Vectors"].end();
          x++
        ){
          xs.first.push_back(x.key().asString());
          streamoff loc=(*x).asInt64();
          xs.second.push_back(typename DGM_InequalityConstrained::X_Vector());
            DGM_HS<DGM::Scalar>::init(mocp->ocp->control,xs.second.back());
          readX(loc,xs.second.back());
        }

        // Read in the Z vectors
        if(*dgm_problem_class==ProblemClass::InequalityConstrained)
          for(Json::Value::iterator x=root["Restart"]["Z Vectors"].begin();
            x!=root["Restart"]["Z Vectors"].end();
            x++
          ){
            zs.first.push_back(x.key().asString());
            streamoff loc=(*x).asInt64();
            zs.second.push_back(typename DGM_InequalityConstrained::Z_Vector());
              DGM_HS<DGM::Scalar>::init(mocp->ocp->control,zs.second.back());
            readZ(loc,zs.second.back());
          }

        // Capture the data
        switch(*dgm_problem_class) {
        case ProblemClass::Unconstrained:
          DGM_Unconstrained::Restart::capture(DGM_Messaging(comm),
            *state,xs,reals,nats,params);
          break;
        case ProblemClass::InequalityConstrained:
          DGM_InequalityConstrained::Restart::capture(DGM_Messaging(comm),
            *state,xs,zs,reals,nats,params);
          break;
        case peopt::ProblemClass::EqualityConstrained:
        case peopt::ProblemClass::Constrained:
          DGM::Comm::World->error("Equality and fully constrained problems are"
            " not currently implemented.");
          break;
        }

        // Validate the input
        validate();
      }

      /// Writes the current inputs to a string
      std::string to_string() {
        // Make sure that we've successfully attached to a mocp,
        // optimization state, problem class, and have a mildly reasonable
        // binary filename
        if(mocp==NULL || state==NULL || dgm_problem_class==NULL || bname=="")
          return "{ }\n";

        // Determine the norm of the gradient and the step
        const DGM::Scalar norm_dx
            = sqrt(state->dx.back()->inner_product(state->dx.back()));
        const DGM::Scalar norm_grad
            = sqrt(state->grad.back()->inner_product(state->grad.back()));

        // Write out the header for the binary storage
        writeHeader(
            state->iter,
            norm_dx != norm_dx ? 0. : norm_dx,
            norm_grad,
            mocp->npredict);

        // Create a new root for writing
        Json::Value root;

        // Write out the binary filename
        root["Restart"]["binary data"]=bname;

        // Setup the peopt parameters
        peopt::DGM_InequalityConstrained::X_Vectors xs;
        peopt::DGM_InequalityConstrained::Z_Vectors zs;
        peopt::DGM_InequalityConstrained::Reals reals;
        peopt::DGM_InequalityConstrained::Nats nats;
        peopt::DGM_InequalityConstrained::Params params;

        // Release the state
        switch(*dgm_problem_class) {
        case ProblemClass::Unconstrained:
          DGM_Unconstrained::Restart::release(*state,xs,reals,nats,params);
          break;
        case ProblemClass::InequalityConstrained:
          DGM_InequalityConstrained::Restart
            ::release(*state,xs,zs,reals,nats,params);
          break;
        case peopt::ProblemClass::EqualityConstrained:
        case peopt::ProblemClass::Constrained:
          DGM::Comm::World->error("Equality and fully constrained problems are"
            " not currently implemented.");
          break;
        }

        // Output the reals
        {
          std::list <std::string>::iterator name=reals.first.begin();
          for(std::list <DGM::Scalar>::iterator x=reals.second.begin();
            x!=reals.second.end();
            x++,name++
          ) {
            // Do not output NaN parameters
            const DGM::Scalar p = *x;
            if (!(p!=p)) root["Restart"]["Reals"][*name]=p;
          }
        }

        // Output the naturals
        {
          std::list <std::string>::iterator name=nats.first.begin();
          for(std::list <peopt::Natural>::iterator x=nats.second.begin();
            x!=nats.second.end();
            x++,name++
          )
            root["Restart"]["Naturals"][*name]=Json::Value::UInt64(*x);
        }

        // Output the parameters
        {
          std::list <std::string>::iterator name=params.first.begin();
          for(std::list <string>::iterator x=params.second.begin();
            x!=params.second.end();
            x++,name++
          )
            root["Restart"]["Parameters"][*name]=*x;
        }

        // Output the X-vectors
        {
          std::list <std::string>::iterator name=xs.first.begin();
          for(std::list <DGM_InequalityConstrained::X_Vector>::iterator
              x=xs.second.begin();
            x!=xs.second.end();
            x++,name++
          ) {
            streamoff loc=writeX(*x);
            Json::Value::Int64 v = numeric_cast<Json::Value::Int64>(loc);
            root["Restart"]["X Vectors"][*name]=v;
          }
        }

        // Output the Z-vectors
        if(*dgm_problem_class==ProblemClass::InequalityConstrained) {
          std::list <std::string>::iterator name=zs.first.begin();
          for(std::list <DGM_InequalityConstrained::Z_Vector>::iterator
              x=zs.second.begin();
            x!=zs.second.end();
            x++,name++
          ) {
            streamoff loc=writeZ(*x);
            Json::Value::Int64 v = numeric_cast<Json::Value::Int64>(loc);
            root["Restart"]["Z Vectors"][*name]=v;
          }
        }

        // Recapture the data
        switch(*dgm_problem_class) {
        case ProblemClass::Unconstrained:
          DGM_Unconstrained::Restart::capture(DGM_Messaging(comm),
            *state,xs,reals,nats,params);
          break;
        case ProblemClass::InequalityConstrained:
          DGM_InequalityConstrained::Restart::capture(DGM_Messaging(comm),
            *state,xs,zs,reals,nats,params);
          break;
        case peopt::ProblemClass::EqualityConstrained:
        case peopt::ProblemClass::Constrained:
          DGM::Comm::World->error("Equality and fully constrained problems are"
            " not currently implemented.");
          break;
        }

        // Create a string with the above output
        Json::StyledWriter writer;
        string output=writer.write(root);

        return output;
      }

      /// Writes out all the parameters to file
      void write(string fname) {
        write_string(fname,to_string());
      }

      /// Validates the current input arguments
      void validate() {
        // Create a base error message
        std::string base="Error in the .peopt_restart file.  ";

        // Make sure we have a binary file name
        if(bname==""){
          comm->error(base + "We require a binary filename for restarting.\n");
          comm->exit(EXIT_FAILURE);
        }
      }
    };

  }  // namespace Params

  /// A state manipulator that facilitates restarting
  template <class OptProblem,class Params>
  class RestartManipulator
      : public peopt::StateManipulator<DGM_InequalityConstrained>
  {
  private:
    /// This communicator needs to span all the groups.  Basically, the
    /// group and rank communicators needed to have been carved out of this
    /// communicator.
    DGM::Shared <DGM::Comm>::Ptr comm;

    /// The optimization problem that we're controlling
    DGM::MultiOptProblem <OptProblem>& mocp;

    /// Parameters that contain, at the very least, the restart information
    Params& params;

  public:

    /// Constructor
    RestartManipulator(
      DGM::Shared <DGM::Comm>::Ptr comm_,
      DGM::MultiOptProblem <OptProblem>& mocp_,
      Params& params_
    ) : comm(comm_), mocp(mocp_), params(params_) {};

    /// Application of the manipulator
    void operator() (
      const typename DGM_InequalityConstrained::Functions::t& fns,
      typename DGM_InequalityConstrained::State::t& state,
      peopt::OptimizationLocation::t loc
    ) const {
      switch(loc) {
      case peopt::OptimizationLocation::AfterInitialFuncAndGrad:
      case peopt::OptimizationLocation::EndOfOptimizationIteration:
        // Only participate in restarting if we're in the head group.
        if(mocp.gnum==0
           && ((state.iter % params.restart_file_frequency==0)
               || state.opt_stop!=peopt::StoppingCondition::NotConverged)
        ){
          // Write the restart information

          // If we read the restart directly, by looking at the file, always
          // read the iteration number as, "At the start of iteration ##, the
          // the optimization state is ____."

          // Get the filename for the parameters.
          std::string fname;
          {
              stringstream ss;
              ss << mocp.root << "." << state.iter << ".perst";
              fname=ss.str();
          }
          // Get the binary filename
          {
              stringstream ss;
              ss << mocp.root << "." << state.iter << ".ctl";
              params.bname=ss.str();
          }
          // Write the restart file
          params.write(fname);
        }
        break;
      default:
        break;
      }
    }
  };

  // This finds a specific column of the Hessian.  It's useful for debugging
  // purposes
  template <class OptProblem>
  void get_Hessian_col(
    DGM::MultiOptProblem <OptProblem>& mocp,
    peopt::ScalarValuedFunction <DGM::Scalar,DGM_HS>& f,
    typename DGM_HS <DGM::Scalar>::Vector& x,
    const int col,
    std::vector <DGM::Scalar>& v
  ){
    // Allocate memory for the ith cannonical vector and the Hessian
    // applied to this vector
    typename DGM_HS <DGM::Scalar>::Vector ei;
    DGM_HS <DGM::Scalar>::init(x,ei);
    typename DGM_HS <DGM::Scalar>::Vector H_ei;
    DGM_HS <DGM::Scalar>::init(x,H_ei);

    // Communicate within the group the number of elements held in the
    // cannonical vector
    int num_proc=mocp.gcomm->NumProc();
    int num_my_ele=ei->phi.size();
    int sizes[num_proc];
    mocp.gcomm->GatherAll(&num_my_ele,sizes,1);

    // Create a vector of offsets.  We use this to determine who needs
    // to set the cannonical vector
    int offsets[num_proc+1];
    offsets[0]=0;
    for(int i=1;i<=num_proc;i++)
      offsets[i]=offsets[i-1]+sizes[i-1];

    // Determine the number of elements in the total cannonical vector
    int num_ele=0;
    for(int i=0;i<num_proc;i++)
      num_ele+=sizes[i];

    // Zero out the cannonical vector
    ei->phi.Zero();

    // Determine who needs to set the 1
    int which_proc;
    for(which_proc=0;which_proc<num_proc && (col-1)>=offsets[which_proc+1];
        which_proc++);

    if(mocp.rnum==which_proc)
      ei->phi[(col-1)-offsets[which_proc]]=1.;

    // Apply the Hessian approximation
    f.hessvec(x,ei,H_ei);

    // Accumulate the result
    v.resize(num_ele);
    mocp.gcomm->GatherAll(H_ei->phi.data(),sizes[mocp.rnum],&(v[0]),sizes,
      offsets);
  }

  template <class OptProblem>
  void discretizeH(
    DGM::MultiOptProblem <OptProblem>& mocp,
    peopt::ScalarValuedFunction <DGM::Scalar,DGM_HS>& f,
    typename DGM_HS <DGM::Scalar>::Vector& x
  ){
    // Create the filename for writing
    std::string fname = mocp.root + ".hessian";

    // Notify the user of the process and open the file for writing if
    // we're the head node.
    ofstream fout;
    mocp.gcomm->cout()
      << "Writing out the Hessian approximation to the file: "
      << fname << endl;
    if(mocp.gnum==0 && mocp.rnum==0) {
      fout.open(fname.c_str(),ios_base::out);
      if(fout.is_open())
        mocp.gcomm->error("Unable to open the file " + fname + " for writing "
          "out the Hessian.");
    }

    // Communicate within the group the number of elements held in the
    // cannonical vector
    int n=mocp.gcomm->NumProc();
    int num_my_ele=x->phi.size();
    int sizes[n];
    mocp.gcomm->GatherAll(&num_my_ele,sizes,1);

    // Determine the number of elements in the total canonical vector
    int num_ele=0;
    for(int i=0;i<n;i++){
      num_ele+=sizes[i];
      mocp.gcomm->cout() << sizes[i] << endl;
    }

    // Build the discrete Hessian
    for(int i=1;i<=num_ele;i++){
      // Notify us which column we're processing
      mocp.gcomm->cout() << "HESSIAN COL: " <<
        i << '/' << num_ele << endl;

      // Find this column in the Hessian
      vector <DGM::Scalar> v;
      get_Hessian_col(mocp,f,x,i,v);

      // Write the result to file if the proc is the head node
      if(mocp.gnum==0 && mocp.rnum==0){
        for(int j=0;j<num_ele;j++) {
          fout << scientific << setprecision(16) << v[j] << endl;
          if(fout.fail())
            mocp.gcomm->error("Failure occured when writing out a column of"
              " the Hessian.");
        }
      }
    }
    if(mocp.gnum==0 && mocp.rnum==0) fout.close();
  }

  /// Split Peopt into separate setup and solve phases so can
  /// get access to MultiOptProblem for diffing ctl files
  template <typename OptProblem,typename Params,typename Manipulator>
  class setupAndSolve {
    DGM::ArgList& args;
    DGM::Table& dgm_params;
    bool peopt_params_exist;
    // Find the filename for the optimization parameters
    std::string fname;
    // Create some parameters required for peopt
    Params peopt_params;
    // Create an initial messaging object
    peopt::DGM_Messaging *msg;
    // Create a state so that we can see the optimization parameters.
    peopt::DGM_InequalityConstrained::State::t state;
  public:
    ~setupAndSolve() {
      delete msg; msg = 0;
    }
    setupAndSolve(DGM::ArgList& _args, DGM::Table& _dgm_params,
    const bool& genparams, const std::string& root, bool partial_init = false)
    : args(_args), dgm_params(_dgm_params), fname(root+".peopt")
      , peopt_params(DGM::Comm::World), msg(0)
  {
    //std::cout<<"I am in peopt::setupAndSolve(..)"<<std::endl;

    // Check if the .peopt parameter file exists
    {
      std::ifstream test(fname.c_str());
      peopt_params_exist=test.good();
      test.close();
    }

    //std::cout<<"Finished testing for .peopt file"<<std::endl;
    //DGM::Comm::World->Barrier();

    //std::cout<<"Reading the peopt parameters from "<<fname<<std::endl;
    //DGM::Comm::World->Barrier();

    // If the peopt parameters exist, read them from file
    if(peopt_params_exist) peopt_params.read(fname);

    //std::cout<<"Read the peopt parameters from "<<fname<<std::endl;
    //DGM::Comm::World->Barrier();

    // Create an initial messaging object
    msg = new peopt::DGM_Messaging(DGM::Comm::World,root,peopt_params.add_time);

    //std::cout<<"Setup DGM messaging"<<std::endl;
    //DGM::Comm::World->Barrier();

    //std::cout<<"Created a State"<<std::endl;
    //DGM::Comm::World->Barrier();

    // If the peopt parameters exist, create an initial state
    if(peopt_params_exist)
        peopt::json::InequalityConstrained <DGM::Scalar,peopt::DGM_HS,
           peopt::DGM_HS>::read(*msg,fname,state);

    // if reading ctl files, return
    if (partial_init) return;

    // If one case, we do not solve the optimization problem, but simply
    // output the parameters.  This is good for checking for errors in our
    // problem setup.
    if (genparams) {

      // Create the optimization objects
      DGM::Comm::World->cout()
        << "================================================================\n"
        << "Generating parameters for use in peopt...\n"
        << "================================================================\n";

      // Write the optimization parameters to screen
      std::string params1;
      switch(peopt_params.problem_class) {
        case peopt::ProblemClass::Unconstrained:
          params1=peopt::DGM_JsonUnconstrained::to_string(state);
          break;
        case peopt::ProblemClass::InequalityConstrained:
          params1=peopt::DGM_JsonInequalityConstrained::to_string(state);
          break;
      case peopt::ProblemClass::EqualityConstrained:
      case peopt::ProblemClass::Constrained:
        DGM::Comm::World->error("Equality and fully constrained problems are"
          " not currently implemented.");
        break;
      }
      std::string params2 = peopt_params.to_string();
      std::string params3 = params1.substr(0,params1.size()-3) + ",\n"
          + params2.substr(2,params2.size());
      DGM::Comm::World->cout() << params3;

    // In the other case, we go ahead and solve the optimization problem
    } else {

      // Create the optimization objects
      DGM::Comm::World->cout()
        << "================================================================\n"
        << "Solving parameter estimation problem using peopt...\n"
        << "================================================================\n";

      // Start a clock on the solve
      Stopwatch cpu;
      cpu.start();

      // If the parameters don't exist, remind the user and exit
      if(!peopt_params_exist) {
        DGM::Comm::World->error("We require a .peopt file for optimization."
          "  In order to generate a blank parameter file, run with the"
          " -params flag.");
      }

      // Setup the parallelism
      bool build_linearized=(state.H_type==peopt::Operators::UserDefined);
      DGM::MultiOptProblem <OptProblem> mocp(
          peopt_params.num_groups,peopt_params.objective_name,
          args,dgm_params,DGM::Comm::World,build_linearized);

      // Hook together everything required for the restart parameters
      peopt_params.mocp=&mocp;
      peopt_params.dgm_problem_class=&peopt_params.problem_class;
      peopt_params.state=&state;

      // Create the regularization
      std::unique_ptr< DGM::Regularization::Base<DGM::Scalar> > reg;
      switch(peopt_params.reg_type) {
      case DGM::Regularization::Type::None:
        reg.reset(new DGM::Regularization::None<DGM::Scalar>());
        break;
      case DGM::Regularization::Type::Tikhonov: {
        typename DGM_InequalityConstrained::X_Vector zero;
        DGM_HS <DGM::Scalar>::init(mocp.optimizer->control,zero);
        DGM_HS <DGM::Scalar>::zero(zero);
        reg.reset(new DGM::Regularization::Tikhonov<DGM::Scalar>(zero));
        break;
      } case DGM::Regularization::Type::TikhonovWithBase:
        reg.reset(new DGM::Regularization
          ::Tikhonov<DGM::Scalar>(mocp.optimizer->control));
        break;
      case DGM::Regularization::Type::Lasso: {
        typename DGM_InequalityConstrained::X_Vector zero;
        DGM_HS <DGM::Scalar>::init(mocp.optimizer->control,zero);
        DGM_HS <DGM::Scalar>::zero(zero);
        reg.reset(new DGM::Regularization
          ::Lasso <DGM::Scalar>(zero,peopt_params.gamma));
        break;
      } case DGM::Regularization::Type::LassoWithBase:
        reg.reset(new DGM::Regularization
          ::Lasso<DGM::Scalar>(mocp.optimizer->control,peopt_params.gamma));
        break;
      case DGM::Regularization::Type::TotalVariation: {
        typename DGM_InequalityConstrained::X_Vector zero;
        DGM_HS <DGM::Scalar>::init(mocp.optimizer->control,zero);
        DGM_HS <DGM::Scalar>::zero(zero);
        reg.reset(new DGM::Regularization
          ::TotalVariation<DGM::Scalar>(zero,peopt_params.gamma));
        break;
      } }

      // Setup pieces required for both classes of optimization problems
      peopt::DGM_InequalityConstrained::Functions::t fns;
      fns.f.reset(new peopt::DGM_Obj <OptProblem>(mocp,*reg,peopt_params.beta));
      //fns.g.reset(new peopt::DGM_Obj <OptProblem>
      //  (mocp,*reg,peopt_params.beta));
      fns.PH.reset(new peopt::ExternalPreconditioner <OptProblem> (mocp));

      // Setup the restart manipulator
      peopt::RestartManipulator <OptProblem,Params>
        rmanip(DGM::Comm::World,mocp,peopt_params);

      // Setup the custom manipulator
      Manipulator smanip(DGM::Comm::World,mocp,peopt_params,rmanip);

      // Determine if we have a restart file
      std::string rst_fname=root+".perst";
      bool restart_exist;
      {
        std::ifstream test(rst_fname.c_str());
        restart_exist=test.good();
        test.close();
      }

      // Restart if required
      if(restart_exist)
        peopt_params.read(rst_fname);

      // Otherwise, read in an initial guess of the solution and allocate
      // memory for the other structures
      else {
        switch(peopt_params.problem_class){
        case peopt::ProblemClass::Unconstrained:
          peopt::DGM_Unconstrained::State
            ::init_vectors(state,mocp.optimizer->control);
          break;
        case peopt::ProblemClass::InequalityConstrained:
          peopt::DGM_InequalityConstrained::State::init_vectors(
            state,mocp.optimizer->control,mocp.optimizer->control);
          break;
        case peopt::ProblemClass::EqualityConstrained:
        case peopt::ProblemClass::Constrained:
          DGM::Comm::World->error("Equality and fully constrained problems are"
            " not currently implemented.");
          break;
        }
      }

      // Now, we run any diagnostics that have been requested.  If we run
      // a diagnostic, we do not do optimization
      if(peopt_params.objective || peopt_params.fd_gradient
        || peopt_params.hessian_discretize || peopt_params.fd_gauss_newton
        || peopt_params.symmetry_check || peopt_params.fd_linearized_state>=0
      ) {
        // Create some shortcuts
        typename DGM_InequalityConstrained::X_Vector& x=state.x.front();

        // Execute any state manipulator required at the start of optimization
        smanip(fns,state,peopt::OptimizationLocation::BeginningOfOptimization);

        // Calculate the objective function
        if(peopt_params.objective) {
          std::stringstream ss;
          ss << std::setprecision(16) << std::scientific <<
            "Objective value: " << (*fns.f)(x);
          msg->print(ss.str());
        }

        // Create some directions for finite difference tests
        typename DGM_InequalityConstrained::X_Vector dx,dxx;
        DGM_HS <DGM::Scalar>::init(x,dx); DGM_HS <DGM::Scalar>::init(x,dxx);
        dx->set_direction(); dxx->set_direction();

        // Do a gradient finite difference check
        if(peopt_params.fd_gradient)
          peopt::Diagnostics::gradientCheck<>(*msg,*(fns.f),x,dx);

        // Do a finite difference test on the linearized state
        if(peopt_params.fd_linearized_state>=0)
          mocp.linearized_state_fd_check(x,peopt_params.fd_linearized_state);

        // Do a finite difference check on the Gauss-Newton Hessian
        if(peopt_params.fd_gauss_newton)
          mocp.gauss_newton_fd_check(x);

        // Do a symmetry check on the Hessian
        if(peopt_params.symmetry_check)
          peopt::Diagnostics::hessianSymmetryCheck<>(*msg,*(fns.f),x,dx,dxx);

        // Write a discretized Hessian to file
        if(peopt_params.hessian_discretize)
          discretizeH(mocp,*(fns.f),x);

      // Solve an optimization problem
      } else {
        switch(peopt_params.problem_class){
        // Setup and solve the unconstrained optimization problem
        case peopt::ProblemClass::Unconstrained: {
          // Unconstrained problems required unconstrained state manipulators.
          // Now, internally, we're always using an inequality constrained
          // state. As such, we simply need to convert the manipulator to the
          // appropriate type.
          peopt::ConversionManipulator
            <peopt::DGM_InequalityConstrained,peopt::DGM_Unconstrained>
            unsmanip(smanip);
          peopt::DGM_Unconstrained::Algorithms::getMin(*msg,unsmanip,fns,state);
          break;

        // Setup and solve the inequality constrained optimization problem
        } case peopt::ProblemClass::InequalityConstrained:
          peopt::DGM_InequalityConstrained::Algorithms
            ::getMin(*msg,smanip,fns,state);
          break;
        case peopt::ProblemClass::EqualityConstrained:
        case peopt::ProblemClass::Constrained:
          DGM::Comm::World->error("Equality and fully constrained problems are"
            " not currently implemented.");
          break;
        }

        // Write out why we converged
        msg->print("The algorithm converged due to: "
            + peopt::StoppingCondition::to_string(state.opt_stop));
      }

      // Write out the timing information
      DGM::Format sci(4,10,'e');
      DGM::Comm::World->cout() << "Total run time: " << sci(cpu.stop())
                               << " sec = " << sci(cpu.stop()/3600.0)
                               << " hr " << endl;
    }
  }

    DGM::MultiOptProblem<OptProblem> problem() {
      // Setup the parallelism
      bool build_linearized=(state.H_type==peopt::Operators::UserDefined);
      return DGM::MultiOptProblem<OptProblem>(peopt_params.num_groups
          , peopt_params.objective_name, args, dgm_params, DGM::Comm::World
          , build_linearized);
    }
  };

}  // namespace peopt

#endif  // DGM_PEDGM_HPP
