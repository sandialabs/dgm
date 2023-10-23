/** \file Trilinos.cpp
    \brief DGM::Trilinos interface implementation
    \author S. Scott Collis
*/

// DGM includes
#ifdef DGM_PARALLEL
#include "MpiComm.hpp"
#endif
#include "Trilinos.hpp"
#include "Format.hpp"
#include "ObjFunc.hpp"

#ifdef DGM_USE_EPETRA

// Trilinos includes
#include "Teuchos_TestForException.hpp"
#include "Teuchos_RCP.hpp"
#include "EpetraExt_ModelEvaluator.h"

// Json includes
#include "json/reader.h"
#include "json/value.h"
#include "json/writer.h"

#define DGM_USE_FD_PRECONDITIONER

namespace DGM {

  namespace Trilinos {

    using Teuchos::RCP;
    using Teuchos::rcp;

    //=========================================================================
    //                      Trilinos::ModelEvaluator
    //=========================================================================

    ModelEvaluator::ModelEvaluator(Domain *omega) :
      Omega(omega) {
      x_map = vField::BlockMap2PointMap( *(Omega->U.nodal_map.get()) );
    }

    ModelEvaluator::~ModelEvaluator() {}

    RCP<const Epetra_Map> ModelEvaluator::get_x_map() const {
      return x_map;
    }

    RCP<const Epetra_Map> ModelEvaluator::get_f_map() const {
      return x_map;
    }

    // Jacobian
    RCP<Epetra_Operator> ModelEvaluator::create_W() const {
      TEUCHOS_TEST_FOR_EXCEPTION(true, std::logic_error, std::endl <<
                         "ModelEvaluator -- no Jacobian" << std::endl);
      return Teuchos::null;
    }

    RCP<const Epetra_Map> ModelEvaluator::get_p_map(int l) const {
      TEUCHOS_TEST_FOR_EXCEPTION(true, std::logic_error, std::endl <<
                         "ModelEvaluator -- no p_map" << std::endl);
      return Teuchos::null;
    }


    RCP<const Epetra_Map> ModelEvaluator::get_g_map(int j) const {
      TEUCHOS_TEST_FOR_EXCEPTION(true, std::logic_error, std::endl <<
                         "ModelEvaluator -- no g_map" << std::endl);
      return Teuchos::null;
    }

    // like Thyra::get_nominal_values
    RCP<const Epetra_Vector> ModelEvaluator::get_x_init() const {
      Omega->set_ic(Omega->U);
      return rcp(Omega->U.nodal_pnt_vec.get(),false);
    }

    RCP<const Epetra_Vector> ModelEvaluator::get_p_init(int l) const {
      TEUCHOS_TEST_FOR_EXCEPTION(true, std::logic_error, std::endl <<
                         "ModelEvaluator -- no p_init" << std::endl);
      return Teuchos::null;
    }

    EpetraExt::ModelEvaluator::InArgs ModelEvaluator::createInArgs() const {
      EpetraExt::ModelEvaluator::InArgsSetup inArgs;
      inArgs.setModelEvalDescription(this->description());
      inArgs.set_Np(0);
      inArgs.setSupports(IN_ARG_x,true);
      inArgs.setSupports(IN_ARG_t,true);

      // This ModelEvaluator only supports explicit time integration...
      inArgs.setSupports(IN_ARG_x_dot,false);  // implicit activates here
      inArgs.setSupports(IN_ARG_alpha,false);
      inArgs.setSupports(IN_ARG_beta,false);

#if __cplusplus >= 201103L
      return std::move(inArgs);
#else
      return inArgs;
#endif
    }

    EpetraExt::ModelEvaluator::OutArgs ModelEvaluator::createOutArgs() const {
      EpetraExt::ModelEvaluator::OutArgsSetup outArgs;
      outArgs.setModelEvalDescription(this->description());
      outArgs.set_Np_Ng(0,0);
      outArgs.setSupports(OUT_ARG_f,true);
#if __cplusplus >= 201103L
      return std::move(outArgs);
#else
      return outArgs;
#endif
    }

    void ModelEvaluator::evalModel( const InArgs& inArgs,
                                    const OutArgs& outArgs ) const {
      // Parse InArgs
      RCP<const Epetra_Vector> x_in = inArgs.get_x();
      if (x_in==Teuchos::null)
        cout << "ERROR: ModelEvaluator requires x as inargs" << endl;

      //int vecLength = x_in->GlobalLength();
      int myVecLength = x_in->MyLength();

      // Parse OutArgs
      RCP<Epetra_Vector> f_out = outArgs.get_f();

      DGM::vField &X = Omega->U;
      DGM::vField &F = Omega->Ut;

      if (f_out != Teuchos::null) {
        //*(X.nodal_pnt_vec) = *x_in;   // deep copy
        assert( (dVector::size_type)myVecLength == X.elmt_data.size() );
        assert( X.elmt_data.size() == X.qtot() );
        std::copy(&((*x_in)[0]), &((*x_in)[0])+myVecLength,
                  X.elmt_data.data());
        Omega->time_derivative( X, F );
        scale( -1.0, F );
        //*f_out = *(F.nodal_pnt_vec); // deep copy
        std::copy(F.elmt_data.data(),F.elmt_data.data()+F.qtot(),
                  &((*f_out)[0]));
      }
    }

  //===========================================================================
  //                            BaseSolver
  //===========================================================================

  void BaseSolver::setup(const string &name) {
    using Teuchos::RCP; using Teuchos::rcp;

    if (!Omega->U.is_contiguous())
      error("DGM::Trilinos only works for contiguous vFields");

    // Setup Json Value input
    const string file = Omega->root + ".json";
    ifstream json(file.c_str());
    Json::Reader reader;
    const bool parsingSuccessful = reader.parse(json, value, true);
    if (!parsingSuccessful)
    comm->error(name+" could not parse input from "+
                file+"\n"+reader.getFormattedErrorMessages());
    if (!value.isMember("Domain"))
      throw DGM::exception("Domain block is missing");
    Json::Value &domain = value["Domain"];
    const int verb = domain.set("Verbosity",0).asInt();
    if (!domain.isMember(name))
      throw DGM::exception(name+" block is missing");
    Json::Value &method = domain[name];
    if (!method.isMember("Solver options"))
      throw DGM::exception("Solver options block is missing");
    Json::Value &printing = method["Printing"];
    int outInfo = 0;
    if (printing.isMember("Output Information")) {
      Json::Value &oi = printing["Output Information"];
      if (oi.set("Outer Iteration",true).asBool()) 
        outInfo += NOX::Utils::OuterIteration;
      if (oi.set("Outer Iteration StatusTest",true).asBool()) 
        outInfo += NOX::Utils::OuterIterationStatusTest;
      if (oi.set("Inner Iteration",true).asBool())
        outInfo += NOX::Utils::InnerIteration;
      if (oi.set("Parameters",true).asBool())
        outInfo += NOX::Utils::Parameters;
      if (oi.set("Details",true).asBool())
        outInfo += NOX::Utils::Details;
      if (oi.set("Test Details",false).asBool())
        outInfo += NOX::Utils::TestDetails;
      if (oi.set("Stepper Iteration",false).asBool())
        outInfo += NOX::Utils::StepperIteration;
      if (oi.set("Stepper Details",false).asBool())
        outInfo += NOX::Utils::StepperDetails;
      if (oi.set("Stepper Parameters",false).asBool())
        outInfo += NOX::Utils::StepperParameters;
      if (oi.set("Linear Solver Details",true).asBool())
        outInfo += NOX::Utils::LinearSolverDetails;
      if (oi.set("Warning",true).asBool())
        outInfo += NOX::Utils::Warning;
      if (oi.set("Error",true).asBool())
        outInfo += NOX::Utils::Error;
      if (oi.set("Debug",false).asBool())
        outInfo += NOX::Utils::Debug;
    }
    if (verb>1) {
      Json::StyledWriter writer;
      string output = writer.write(printing);
      comm->cout() << "NOX Printing parameters:\n" << output;
    }
    const bool writeXML = method.set("Write parameters to XML",false).asBool();
    const bool readXML = method.set("Read parameters from XML",false).asBool();

    nlParams->set("Nonlinear Solver", "Line Search Based");

    // Set the printing parameters in the "Printing" sublist
    printParams.set("MyPID", Comm->MyPID() );
    printParams.set("Output Precision", 3);
    printParams.set("Output Processor", 0);
    printParams.set("Output Information", outInfo);
    string root(Omega->params["root"]);
    string fname=root+".tri";
    RCP<std::ostream> out(new ofstream(fname.c_str()));
    printParams.set("Output Stream", out);

    // Sublist for line search
    searchParams.set("Method", "Full Step");
    //searchParams.set("Method", "Interval Halving");
    //searchParams.set("Method", "Polynomial");
    //searchParams.set("Method", "NonlinearCG");
    //searchParams.set("Method", "Quadratic");
    //searchParams.set("Method", "More'-Thuente");

    // Sublist for direction
    Json::Value &dirValue = method["Direction"];
    //  dirParams.set("Method", "Modified-Newton");
    //  newtonParams = &dirParams.sublist("Modified-Newton");
    //  newtonParams.set("Max Age of Jacobian", 2);
    dirParams.set("Method", dirValue["Method"].asString());
    Json::Value &newtonValue = dirValue["Newton"];
    newtonParams.set("Forcing Term Method",
        newtonValue["Forcing term method"].asString());
    //newtonParams.set("Forcing Term Method", "Type 1");
    //newtonParams.set("Forcing Term Method", "Type 2");
    //newtonParams.set("Forcing Term Minimum Tolerance", 1.0e-4);
    //newtonParams.set("Forcing Term Maximum Tolerance", 0.1);
    //dirParams.set("Method", "Steepest Descent");
    //sdParams = &dirParams.sublist("Steepest Descent");
    //sdParams.set("Scaling Type", "None");
    //sdParams.set("Scaling Type", "2-Norm");
    //sdParams.set("Scaling Type", "Quadratic Model Min");
    //dirParams.set("Method", "NonlinearCG");
    //nlcgParams = &dirParams.sublist("Nonlinear CG");
    //nlcgParams.set("Restart Frequency", 2000);
    //nlcgParams.set("Precondition", "On");
    //nlcgParams.set("Orthogonalize", "Polak-Ribiere");
    //nlcgParams.set("Orthogonalize", "Fletcher-Reeves");

    // Sublist for linear solver for the Newton method
    Json::Value &lsValue = newtonValue["Linear solver"];
    //lsParams.set("Aztec Solver", "BiCGStab");
    //lsParams.set("Jacobian Operator", "Finite Difference");
    //lsParams.set("Preconditioner Operator", "Use Jacobian");
    //lsParams.set("Preconditioner Operator", "Finite Difference");
    lsParams.set("Aztec Solver", lsValue["Aztec solver"].asString());
    lsParams.set("Max Iterations", lsValue["Max iterations"].asInt());
    lsParams.set("Size of Krylov Subspace",
        lsValue["Size of Krylov subspace"].asInt());
    lsParams.set("Tolerance", lsValue["Tolerance"].asDouble());
    lsParams.set("Output Frequency", lsValue["Output frequency"].asInt());

    if (lsValue.isMember("Preconditioner")) {
      if (lsValue["Preconditioner"].isObject()) {
        Json::Value &pcValue = lsValue["Preconditioner"];
        string pcType = pcValue.set("Type","None").asString();
        if (pcType=="New Ifpack" || pcType=="Ifpack") {
          pcType="Ifpack";
          lsParams.set("Preconditioner","New Ifpack");
        } else if (pcType=="AztecOO" || pcType=="None") {
          lsParams.set("Preconditioner", pcType);
        } else {
          throw DGM::exception("Unknown preconditioner "+pcType);
        }
        if (pcType=="None") {
          buildPreconditioner=false;
        } else {
          buildPreconditioner=true;
          lsParams.set("Preconditioner Reuse Policy",
              pcValue.set("Reuse policy","Recompute").asString());
          lsParams.set("Max Age Of Prec",pcValue.set("Max age",1).asInt());
          if (pcType=="AztecOO") {
            Json::Value &azValue = pcValue["AztecOO"];
            string azType = azValue.set("Type","Jacobi").asString();
            lsParams.set("Aztec Preconditioner",azType);
            // ilu
            lsParams.set("Overlap", azValue.set("Overlap",0).asInt());
            lsParams.set("Graph Fill", azValue.set("Graph fill",0).asInt());
            // ilut
            lsParams.set("Fill Factor", 
                         azValue.set("Fill factor",1.0).asDouble());
            lsParams.set("Drop Tolerance",
                azValue.set("Drop tolerance",1.0e-12).asDouble());
            // Jacobi & Symmetric Gauss-Siedel
            lsParams.set("Steps",azValue.set("Steps",3).asInt());
            // Polynomial & Least-squares Polynomial
            lsParams.set("Polynomial Order",
                azValue.set("Polynomial order",3).asInt());

          }
        }
      } else if (lsValue["Preconditioner"].isString()) {
        if (lsValue["Preconditioner"]!="None")
          throw DGM::exception("Preconditioner must be an object or None");
        buildPreconditioner=false;
      }
    }

    // Sublist for solver options
    Json::Value &slValue = method["Solver options"];
    slParams.set("Status Test Check Type",
      slValue.set("Status test check type","Complete").asString());

#ifdef HAVE_TEUCHOS_EXTENDED
    if (writeXML) {
      // Write the parameter list to a file
      comm->cout() << "Writing parameter list..." << endl;
      if (comm->Master())
        Teuchos::writeParameterListToXmlFile( *nlParams, root+"-imp.xml");
    }
    if (readXML) {
      // Read in the parameter list from a file
      comm->cout() << "Reading parameter list..." << endl;
      RCP<Teuchos::ParameterList> finalParamsPtr =
        rcp(new Teuchos::ParameterList);
      Teuchos::updateParametersFromXmlFile(root+"-imp.xml", nlParams.ptr() );
    }
#else
    if (writeXML) comm->cout() << "XML output requires TeuchosExt" << endl;
    if (readXML)  comm->cout() << "XML input requires TeuchosExt" << endl;
#endif
  }

  void BaseSolver::setupStatusTests(const string &name,
    Teuchos::RCP<NOX::Epetra::Group> grp) {
    // set the status test from Json input
    if (!value.isMember("Domain"))
      throw DGM::exception("Domain block is missing");
    Json::Value &domain = value["Domain"];
    const int verb = domain.set("Verbosity",0).asInt();
    if (!domain.isMember(name))
      throw DGM::exception(name+" block is missing");
    Json::Value &method = domain[name];
    if (!method.isMember("Solver options"))
      throw DGM::exception("Solver options block is missing");
    Json::Value &options = method["Solver options"];
    options.set("Maximum iterations",2);
    options.set("Norm F",1.0e-9);
    options.set("Norm update",1.0e-19);
    if (verb>1) {
      Json::StyledWriter writer;
      string output = writer.write(options);
      comm->cout() << "NOX StatusTest parameters:\n" << output;
    }
    // Create the convergence tests
    absresid = rcp(new NOX::StatusTest::NormF(options["Norm F"].asDouble()));
    reltol = options["Norm F relative"].asDouble();
    if (options.isMember("Norm F relative"))
      relresid = rcp(new NOX::StatusTest::NormF(*grp,
          options["Norm F relative"].asDouble(),
          NOX::StatusTest::NormF::Unscaled));
    update = rcp(new NOX::StatusTest::NormUpdate(
        options["Norm update"].asDouble()));
    if (options.isMember("Norm WRMS")) {
      if (!options["Norm WRMS"].isObject())
        throw DGM::exception("\"Norm WRMS\" must be an object");
      Json::Value &wrmsValue = options["Norm WRMS"];
      if (!wrmsValue.isMember("Absolute tolerance"))
        throw DGM::exception("\"Norm WRMS\" have an "
                             "\"Absolute tolerance\"");
      if (!wrmsValue.isMember("Relative tolerance"))
        throw DGM::exception("\"Norm WRMS\" have an "
                             "\"Relative tolerance\"");
      const double wrms_rtol = wrmsValue["Relative tolerance"].asDouble();
      const double wrms_atol = wrmsValue["Absolute tolerance"].asDouble();
      wrms = rcp(new NOX::StatusTest::NormWRMS(wrms_rtol, wrms_atol));
    }
    converged = rcp(new NOX::StatusTest::Combo(NOX::StatusTest::Combo::OR));
    converged->addStatusTest(absresid);
    if (relresid.get())
      converged->addStatusTest(relresid);
    if (wrms.get())
      converged->addStatusTest(wrms);
    converged->addStatusTest(update);
    maxiters = rcp(new NOX::StatusTest::MaxIters(
        options["Maximum iterations"].asInt()));
    fv = rcp(new NOX::StatusTest::FiniteValue);
    combo = rcp(new NOX::StatusTest::Combo(NOX::StatusTest::Combo::OR));
    combo->addStatusTest(fv);
    combo->addStatusTest(converged);
    combo->addStatusTest(maxiters);
  }

  //===========================================================================
  //                            Backward-Euler
  //===========================================================================

  BackwardEuler::Interface::Interface( Domain *omega ) :
      Omega(omega), R(omega->get_comm()), _adjoint(false) {
    for (vField::size_type i=0; i< Omega->U.size(); ++i)
      R.push_back( new Field( Omega->U[i], Omega->root, Omega->U[i]->name ));
    R.set_name("R");
    R.reset_storage();
    R.zero();
  }
  void BackwardEuler::Interface::convert(const Epetra_Vector &x,dVector &y ) {
    assert( y.size() == (dVector::size_type)x.MyLength() );
    std::copy( &x[0], &x[0] + x.MyLength(), y.data() );
  }
  void BackwardEuler::Interface::convert(const dVector &x,Epetra_Vector &y ) {
    assert( x.size() == (dVector::size_type)y.MyLength() );
    std::copy( x.data(), x.data() + x.size(), &y[0] );
  }
  void BackwardEuler::Interface::convert(const Epetra_Vector &x, vField &y ) {
    convert( x, y[0]->elmt_data );
  }
  void BackwardEuler::Interface::convert(const vField &x, Epetra_Vector &y ) {
    convert( x[0]->elmt_data, y );
  }
  bool BackwardEuler::Interface::computeF(const Epetra_Vector &x,
                                          Epetra_Vector &r,
                                          FillType flag) {
    //cout<<"DGM::BackwardEuler::Interface::computeF(...)"<<endl;
    //Stopwatch cpu; cpu.start();
    bool result(true);
    if (!adjoint())
      result = residual(x,r,flag);
    else
      result = adjoint_residual(x,r,flag);
    //cout<<"ComputeF cpu time = "<<cpu.restart()<<" sec"<<endl;
    return result;
  }
  bool BackwardEuler::Interface::
  residual(const Epetra_Vector &x, Epetra_Vector &r, FillType flag) {
    // cout<<"DGM::BackwardEuler::Interface::residual(...)"<<endl;
    const double dt = Omega->dt;
    vField &U  = Omega->U;
    vField &Ut = Omega->Ut;
    // Stopwatch cpu; cpu.start();
    // convert( x, U );
    *(U.nodal_pnt_vec) = x; // deep copy
    Omega->time_derivative( U, R );
    scale( dt, R );
    axpy( -1.0, Ut, R );
    add( U, R );
    r = *(R.nodal_pnt_vec); // deep copy
    // convert( R, r );
    // comm->cout()<<"Residual cpu time = "<<cpu.restart()<<"sec"<<endl;
    return true;
  }
  bool BackwardEuler::Interface::
  adjoint_residual(const Epetra_Vector &x, Epetra_Vector &r, FillType flag) {
    // cout << "DGM::BackwardEuler::Interface::adjoint_residual(...)"<<endl;
    const double dt = Omega->dt;
    vField &U  = Omega->U;
    vField &Ut = Omega->Ut;
    // Stopwatch cpu; cpu.start();
    // convert( x, U );
    *(U.nodal_pnt_vec) = x; // deep copy
    Omega->time_derivative( U, R );
    scale( dt, R );
    axpy( -1.0, U, R );
    add( Ut, R );
    r = *(R.nodal_pnt_vec); // deep copy
    // convert( R, r );
    // comm->cout()<<"Adjoint cpu time = " << cpu.restart()<<"sec"<<endl;
    return true;
  }

  /// Constructor
  BackwardEuler::BackwardEuler( Domain *Omega_, string ) :
    BaseSolver(Omega_),
    soln( &(*(Omega->U.nodal_pnt_vec)), false ),
    nox_initialized(false)
  {
    if (comm->verbosity()>1)  comm->cout() << "DGM::BackwardEuler()" << endl;
    setup("Backward Euler");
    interface = rcp( new DGM::Trilinos::BackwardEuler::Interface(Omega) );
  }

  void BackwardEuler::initialize_nox(Domain *Omega) {
    static Format sci_lo(4,10,'e');
    using namespace NOX::Epetra;
    using Teuchos::RCP; using Teuchos::rcp;
    DGM::Comm::Ptr comm = Omega->get_comm();

    if (buildPreconditioner) {
      // This version builds a linear system with a finite-difference
      // preconditioner
      A = rcp(new MatrixFree(printParams,interface,soln));
      iJac = A;
      Stopwatch cpu; cpu.start();
      string timestamp = comm->dateTime();
      comm->cout()<<"Starting to build FD preconditioner on "<<timestamp<<endl;
      FD = rcp(new FiniteDifference(printParams,interface,soln));
      iPrec = FD;
      timestamp = comm->dateTime();
      comm->cout()<<"Finished building FD preconditioner on "<<timestamp<<
          sci_lo(cpu.stop())<<" sec"<<endl;
      linSys = rcp(new LinearSystemAztecOO(printParams,lsParams,
          iJac, A, iPrec, FD, soln));
    } else {
      A = rcp(new MatrixFree(printParams,interface,soln));
      iJac = A;
      // This version builds a linear system without a Jacobian or Preconditioner
      linSys = rcp(new LinearSystemAztecOO(printParams,lsParams,interface,
          iJac, A, soln));
    }
    grp = rcp(new Group(printParams,interface,soln,linSys));

    Teuchos::RCP<Epetra_Vector> epv = soln;
#ifdef DGM_USE_EPETRA_DEEP_COPY
    x = rcp(new NOX::Epetra::Vector( epv, NOX::Epetra::Vector::CreateCopy));
#else
    x = rcp(new NOX::Epetra::Vector( epv, NOX::Epetra::Vector::CreateView));
#endif

    setupStatusTests("Backward Euler",grp);

    solver = NOX::Solver::buildSolver(grp, combo, nlParams);

    nox_initialized = true;
    comm->cout()<<"finished nox initialize"<<endl;
  }

  void BackwardEuler::advance( Domain *Omega ) {
    if (comm->verbosity()>2)
      comm->cout() << "DGM::BackwardEuler::advance(Domain *)" << endl;
    using namespace NOX::Epetra;
    using Teuchos::RCP; using Teuchos::rcp;
    NOX::StatusTest::StatusType status;

    const double dt = Omega->dt;
    const int &lstep = Omega->lstep;
    double &t = Omega->t;
    vField &U = Omega->U;
    vField &Ut = Omega->Ut;

    Omega->prestep( U, lstep, 0, t );

    copy(U, Ut);

    interface->setup(Ut);  // setup prior time derivative
    t += dt;

    if (nox_initialized)
      solver->reset(*x);
    else
      initialize_nox(Omega);

    interface->set_domain(Omega);

#define DGM_USE_NOX_SOLVE

#ifdef DGM_USE_NOX_SOLVE
    status = solver->solve();
#else
    do {
      status = solver->step();
      comm->cout() << "=====> ";
      comm->cout() << solver->getNumIterations() << "  ";
      if (absresid.get())
        comm->cout() << absresid->getNormF() << "  ";
      if (relresid.get())
        comm->cout() << relresid->getNormF() << "  ";
      if (wrms.get())
        comm->cout() << wrms->getNormWRMS() << "  ";
      comm->cout() << lsParams.sublist("Output").get<int>
        ("Number of Linear Iterations") << "  ";
      comm->cout() << lsParams.sublist("Output").get<double>
        ("Achieved Tolerance") << "  ";
      comm->cout() << endl;
    } while (status == NOX::StatusTest::Unconverged);
#endif

#undef DGM_USE_NOX_SOLVE

    if (status != NOX::StatusTest::Converged)
      if (Comm->MyPID()==0)
        cout << "Nonlinear solver failed to converge!" << endl;

    static Format sci(3,10,'e');
    comm->cout() << "=====> ";
    comm->cout() << solver->getNumIterations() << ": ";
    if (absresid.get())
      comm->cout() << sci(absresid->getNormF()) << " ";
    if (relresid.get())
      comm->cout() << sci(relresid->getNormF()) << " ";
    if (wrms.get())
      comm->cout() << sci(wrms->getNormWRMS()) << " ";
    comm->cout() << lsParams.sublist("Output").get<int>
      ("Number of Linear Iterations") << "  ";
    comm->cout() << sci(lsParams.sublist("Output").get<double>
      ("Achieved Tolerance")) << " ";
    comm->cout() << endl;

#ifdef DGM_USE_EPETRA_DEEP_COPY
    // Get the Epetra_Vector with the final solution from the solver
    const Group& finalGroup =
      dynamic_cast<const Group&>(solver->getSolutionGroup());
    const Epetra_Vector& finalSolution =
      (dynamic_cast<const Vector&>(finalGroup.getX())).getEpetraVector();
    // still need to copy it out of Epetra storage into DGM storage
#endif

    Omega->poststep( U, lstep, 0, t);
  }

  void BackwardEuler::advance( Domain *Omega, ObjFunc *Jp ) {
    const Scalar dt = Omega->dt;
    const Ordinal &lstep = Omega->lstep;
    //Scalar &t = Omega->t;
    vField &U = Omega->U;
    //vField &Ut = Omega->Ut;
    advance( Omega );
    ObjFunc &J = *Jp;
    ObjFunc R(J);
    R(U,lstep,0);
    axpy(dt,R,J);
  }

  /// Advanced a function
  void BackwardEuler::advance( DGM::Function *J ) {
    const Scalar dt = J->dt;
    const Ordinal &lstep = J->lstep;
    J->value += dt * J->evaluate( lstep, 0 );
  }

  /// Accumulate the gradient for steady controls
  /** This is used to accumulate the gradient and the analysis shows that this
   *  should compute \f$ \sum_{i=1}^n \Delta t g_i \f$
   *  Added the check for lstep>0 but this should never really be called
   */
  void BackwardEuler::accumulate( DGM::Function *J ) {
    const Scalar dt = J->dt;
    const Ordinal &lstep = J->lstep;
    if (lstep>0) J->value += dt * J->evaluate( lstep, 0 );
  }

  void BackwardEuler::adjoint_advance( Domain *Omega ) {
    if (comm->verbosity()>2)
      comm->cout() << "DGM::BackwardEuler::adjoint_advance(Domain *)" << endl;
    using namespace NOX::Epetra;
    using Teuchos::RCP; using Teuchos::rcp;
    NOX::StatusTest::StatusType status;

    const double dt = Omega->dt;
    const int &lstep = Omega->lstep;
    double &t = Omega->t;
    vField &U = Omega->U;
    vField &Ut = Omega->Ut;

    Omega->prestep( U, lstep, 0, t );

    copy(U, Ut);

    interface->setup(Ut);  // setup prior time derivative
    interface->adjoint(true);
    t -= dt;
    if (nox_initialized)
      solver->reset(*x);
    else
      initialize_nox(Omega);

    interface->set_domain(Omega);

#define DGM_USE_NOX_SOLVE

#ifdef DGM_USE_NOX_SOLVE
    status = solver->solve();
#else
    do {
      status = solver->step();
      comm->cout() << "=====> ";
      comm->cout() << solver->getNumIterations() << "  ";
      if (absresid.get())
        comm->cout() << absresid->getNormF() << "  ";
      if (relresid.get())
        comm->cout() << relresid->getNormF() << "  ";
      if (wrms.get())
        comm->cout() << wrms->getNormWRMS() << "  ";
      comm->cout() << lsParams.sublist("Output").get<int>
        ("Number of Linear Iterations") << "  ";
      comm->cout() << lsParams.sublist("Output").get<double>
        ("Achieved Tolerance") << "  ";
      comm->cout() << endl;
    } while (status == NOX::StatusTest::Unconverged);
#endif

#undef DGM_USE_NOX_SOLVE

    if (status != NOX::StatusTest::Converged)
      if (Comm->MyPID()==0)
        cout << "Nonlinear solver failed to converge!" << endl;

    static Format sci(3,10,'e');
    comm->cout() << "=====> ";
    comm->cout() << solver->getNumIterations() << ": ";
    if (absresid.get())
      comm->cout() << sci(absresid->getNormF()) << " ";
    if (relresid.get())
      comm->cout() << sci(relresid->getNormF()) << " ";
    if (wrms.get())
      comm->cout() << sci(wrms->getNormWRMS()) << " ";
    comm->cout() << lsParams.sublist("Output").get<int>
      ("Number of Linear Iterations") << "  ";
    comm->cout() << sci(lsParams.sublist("Output").get<double>
      ("Achieved Tolerance")) << " ";
    comm->cout() << endl;

#ifdef DGM_USE_EPETRA_DEEP_COPY
    // Get the Epetra_Vector with the final solution from the solver
    const Group& finalGroup =
      dynamic_cast<const Group&>(solver->getSolutionGroup());
    const Epetra_Vector& finalSolution =
      (dynamic_cast<const Vector&>(finalGroup.getX())).getEpetraVector();
    // still need to copy it out of Epetra storage into DGM storage
#endif

    Omega->poststep( U, lstep, 0, t);

    interface->adjoint(false);
  }

  void BackwardEuler::residual( Domain *, const vec &, vec & ) {
    comm->cout() << "DGM::BackwardEuler::residual(Domain *, const vec&, vec&) "
        "not implemented." << endl;
  }
  void BackwardEuler::adjoint_residual( Domain *, const vec &, vec & ) {
    comm->cout() << "DGM::BackwardEuler::adjoint_residual(Domain *, "
        "const vec&, vec&) not implemented." << endl;
  }

  //===========================================================================
  //                                BDF2
  //===========================================================================

  BDF2::Interface::Interface( Domain *omega ) : Omega(omega),
    R(omega->get_comm()) {
    for (vField::size_type i=0; i< Omega->U.size(); ++i)
      R.push_back( new Field( Omega->U[i], Omega->root, Omega->U[i]->name ));
    R.set_name("R");
    R.reset_storage();
    R.zero();
  }
  void BDF2::Interface::convert(const Epetra_Vector &x,dVector &y ) {
    assert( y.size() == (dVector::size_type)x.MyLength() );
    std::copy( &x[0], &x[0] + x.MyLength(), y.data() );
  }
  void BDF2::Interface::convert(const dVector &x,Epetra_Vector &y ) {
    assert( x.size() == (dVector::size_type)y.MyLength() );
    std::copy( x.data(), x.data() + x.size(), &y[0] );
  }
  void BDF2::Interface::convert(const Epetra_Vector &x, vField &y ) {
    convert( x, y[0]->elmt_data );
  }
  void BDF2::Interface::convert(const vField &x, Epetra_Vector &y ) {
    convert( x[0]->elmt_data, y );
  }
  bool BDF2::Interface::computeF(const Epetra_Vector &x,
                                          Epetra_Vector &r,
                                          FillType flag) {
    //cout << "DGM::BDF2::Interface::computeF(...)"<<endl;
    const double dt = Omega->dt;
    vField &U  = Omega->U;
    vField &Ut = Omega->Ut;
    //Stopwatch cpu; cpu.start();
    //convert( x, U );
    *(U.nodal_pnt_vec) = x; // deep copy
    Omega->time_derivative( U, R );
    scale( dt, R );
    axpy( -1.0, Ut, R );
    add( U, R );
    r = *(R.nodal_pnt_vec); // deep copy
    //convert( R, r );
    //comm->cout() << "Residual cpu time = " << cpu.restart()
    //                         << "sec" << endl;
    return true;
  }

  /// Constructor
  BDF2::BDF2( Domain *Omega_, string ) :
    BaseSolver(Omega_),
    soln( &(*(Omega->U.nodal_pnt_vec)), false ),
    nox_initialized(false)
  {
    if (comm->verbosity()>1)  comm->cout() << "DGM::BDF2()" << endl;
    setup("BDF2");
    interface = rcp( new DGM::Trilinos::BDF2::Interface(Omega) );
  }

  void BDF2::initialize_nox(Domain *Omega) {
    using namespace NOX::Epetra;
    using Teuchos::RCP; using Teuchos::rcp;
    DGM::Comm::Ptr comm = Omega->get_comm();

    A = rcp(new MatrixFree(printParams,interface,soln));
    linSys = rcp(new LinearSystemAztecOO(printParams,lsParams,interface,soln));
    grp = rcp(new Group(printParams,interface,soln,linSys));

    Teuchos::RCP<Epetra_Vector> epv = soln;
#ifdef DGM_USE_EPETRA_DEEP_COPY
    x = rcp(new NOX::Epetra::Vector( epv, NOX::Epetra::Vector::CreateCopy));
#else
    x = rcp(new NOX::Epetra::Vector( epv, NOX::Epetra::Vector::CreateView));
#endif

    setupStatusTests("BDF2",grp);

    solver = NOX::Solver::buildSolver(grp, combo, nlParams);

    nox_initialized = true;
  }

  void BDF2::advance( Domain *Omega ) {
    if (comm->verbosity()>2)
      comm->cout() << "DGM::BDF2::advance(Domain *)" << endl;
    using namespace NOX::Epetra;
    using Teuchos::RCP; using Teuchos::rcp;
    NOX::StatusTest::StatusType status;

    const double dt = Omega->dt;
    const int &lstep = Omega->lstep;
    double &t = Omega->t;
    vField &U = Omega->U;
    vField &Ut = Omega->Ut;

    Omega->prestep( U, lstep, 0, t );

    copy(U, Ut);

    interface->setup(Ut);  // setup prior time derivative
    t += dt;

    if (nox_initialized)
      solver->reset(*x);
    else
      initialize_nox(Omega);

#define DGM_USE_NOX_SOLVE

#ifdef DGM_USE_NOX_SOLVE
    status = solver->solve();
#else
    do {
      status = solver->step();
      comm->cout() << "=====> ";
      comm->cout() << solver->getNumIterations() << "  ";
      if (absresid.get())
        comm->cout() << absresid->getNormF() << "  ";
      if (relresid.get())
        comm->cout() << relresid->getNormF() << "  ";
      if (wrms.get())
        comm->cout() << wrms->getNormWRMS() << "  ";
      comm->cout() << lsParams.sublist("Output").get<int>
        ("Number of Linear Iterations") << "  ";
      comm->cout() << lsParams.sublist("Output").get<double>
        ("Achieved Tolerance") << "  ";
      comm->cout() << endl;
    } while (status == NOX::StatusTest::Unconverged);
#endif

#undef DGM_USE_NOX_SOLVE

    if (status != NOX::StatusTest::Converged)
      if (Comm->MyPID()==0)
        cout << "Nonlinear solver failed to converge!" << endl;

    static Format sci(3,10,'e');
    comm->cout() << "=====> ";
    comm->cout() << solver->getNumIterations() << ": ";
    if (absresid.get())
      comm->cout() << sci(absresid->getNormF()) << " ";
    if (relresid.get())
      comm->cout() << sci(relresid->getNormF()) << " ";
    if (wrms.get())
      comm->cout() << sci(wrms->getNormWRMS()) << " ";
    comm->cout() << lsParams.sublist("Output").get<int>
      ("Number of Linear Iterations") << "  ";
    comm->cout() << sci(lsParams.sublist("Output").get<double>
      ("Achieved Tolerance")) << " ";
    comm->cout() << endl;

#ifdef DGM_USE_EPETRA_DEEP_COPY
    // Get the Epetra_Vector with the final solution from the solver
    const Group& finalGroup =
      dynamic_cast<const Group&>(solver->getSolutionGroup());
    const Epetra_Vector& finalSolution =
      (dynamic_cast<const Vector&>(finalGroup.getX())).getEpetraVector();
    // still need to copy it out of Epetra storage into DGM storage
#endif

    Omega->poststep( U, lstep, 0, t);
  }

  void BDF2::residual( Domain *, const vec &, vec & ) {
    comm->cout() << "DGM::BDF2::residual(Domain *, const vec&, vec&)"
                 << endl;
  }

  //========================================================================
  //                             Trapezoidal
  //========================================================================

  Trapezoidal::Interface::Interface( Domain *omega )
  : verb(0), Omega(omega), comm(Omega->get_comm()), R(omega->get_comm()),
    S(omega->get_comm()), _adjoint(false) {
    for (vField::size_type i=0; i< Omega->U.size(); ++i)
      R.push_back( new Field( Omega->U[i], Omega->root, Omega->U[i]->name ));
    R.set_name("R");
    R.reset_storage();
    R.zero();
    for (vField::size_type i=0; i< Omega->U.size(); ++i)
      S.push_back( new Field( Omega->U[i], Omega->root, Omega->U[i]->name ));
    S.set_name("S");
    S.reset_storage();
    S.zero();
  }
  void Trapezoidal::Interface::convert( const Epetra_Vector &x, dVector &y ) {
    assert( y.size() == (dVector::size_type)x.MyLength() );
    std::copy( &x[0], &x[0] + x.MyLength(), y.data() );
  }
  void Trapezoidal::Interface::convert( const dVector &x, Epetra_Vector &y ) {
    assert( x.size() == (dVector::size_type)y.MyLength() );
    std::copy( x.data(), x.data() + x.size(), &y[0] );
  }
  void Trapezoidal::Interface::convert( const Epetra_Vector &x, vField &y ) {
    convert( x, y[0]->elmt_data );
  }
  void Trapezoidal::Interface::convert( const vField &x, Epetra_Vector &y ) {
    convert( x[0]->elmt_data, y );
  }
  bool Trapezoidal::Interface::computeF(const Epetra_Vector &x,
                                        Epetra_Vector &r,
                                        FillType flag) {
    if (verb) comm->cout()<<"DGM::Trapezoidal::Interface::computeF(...)"<<endl;
    Stopwatch cpu; cpu.start();
    bool result(true);
    if (!adjoint())
      result = residual(x,r,flag);
    else
      result = adjoint_residual(x,r,flag);
    if (verb) comm->cout()<<"ComputeF cpu time = "<<cpu.restart()<<"sec"<<endl;
    return result;
  }

  bool Trapezoidal::Interface::
  residual( const Epetra_Vector &x, Epetra_Vector &r, FillType flag) {
    if (verb)
      comm->cout() << "DGM::Trapezoidal::Interface::residual(...)"<<endl;
    const double dt = Omega->dt;
    vField &U  = Omega->U;
    vField &Ut = Omega->Ut;
    Stopwatch cpu; cpu.start();
    // convert( x, U );
    *(U.nodal_pnt_vec) = x;
    Omega->time_derivative( U, R );
    add( S, R );
    scale( 0.5*dt, R );
    axpy( -1.0, Ut, R );
    add( U, R);
    r = *(R.nodal_pnt_vec);
    // convert( R, r );
    if (verb)
      comm->cout() << "Residual cpu time = " << cpu.restart() << "sec" << endl;
    return true;
  }
  /// The adjoint residual
  /** See the notes in dgm/math/adjoint_time.tex. */
  bool Trapezoidal::Interface::
  adjoint_residual( const Epetra_Vector &x, Epetra_Vector &r, FillType flag) {
    if (verb)
      comm->cout()<<"DGM::Trapezoidal::Interface::adjoint_residual(...)"<<endl;
    const double dt = Omega->dt;
    vField &U  = Omega->U;
    vField &Ut = Omega->Ut;
    const Ordinal lstep = Omega->lstep;
    const Ordinal Nt = Omega->Nt;              // requires Nt == Nadvance
    Stopwatch cpu; cpu.start();
    *(U.nodal_pnt_vec) = x; // deep copy
    Omega->time_derivative( U, R );
    if (lstep<Nt) add( S, R );
    scale( 0.5*dt, R );
    axpy( -1.0, U, R );
    add( Ut, R );
    r = *(R.nodal_pnt_vec); // deep copy
    if (verb) comm->cout()<<"Adjoint cpu time = " << cpu.restart()<<"sec"<<endl;
    return true;
  }

  /// Constructor
  Trapezoidal::Trapezoidal( Domain *Omega, string ) :
    BaseSolver(Omega),
    soln( &(*(Omega->U.nodal_pnt_vec)), false ),
    nox_initialized(false)
  {
    if (comm->verbosity()>1) comm->cout() << "DGM::Trapezoidal()" << endl;
    using Teuchos::RCP; using Teuchos::rcp;
    if (!Omega->U.is_contiguous())
      error("Trilinos::Trapezoidal only works for contiguous vFields");
    setup("Trapezoidal");
    interface = rcp(new DGM::Trilinos::Trapezoidal::Interface(Omega));
  }

  void Trapezoidal::initialize_nox() {
    static Format sci_lo(4,10,'e');
    using namespace NOX::Epetra;
    using Teuchos::RCP; using Teuchos::rcp;

    if (buildPreconditioner) {
      // This version builds a linear system with a finite-difference
      // preconditioner
      A = rcp(new MatrixFree(printParams,interface,soln));
      iJac = A;
      Stopwatch cpu; cpu.start();
      string timestamp = comm->dateTime();
      comm->cout()<<"Starting to build FD preconditioner on "<<timestamp<<endl;
      FD = rcp(new FiniteDifference(printParams,interface,soln));
      iPrec = FD;
      timestamp = comm->dateTime();
      comm->cout()<<"Finished building FD preconditioner on "<<timestamp<<
          sci_lo(cpu.stop())<<" sec"<<endl;
      linSys = rcp(new LinearSystemAztecOO(printParams,lsParams,
          iJac, A, iPrec, FD, soln));
    } else {
      A = rcp(new MatrixFree(printParams,interface,soln));
      linSys = rcp(new LinearSystemAztecOO(printParams,lsParams,interface,soln));
    }
    grp = rcp(new Group(printParams,interface,soln,linSys));

    Teuchos::RCP<Epetra_Vector> epv = soln;
    x = rcp(new NOX::Epetra::Vector( epv, NOX::Epetra::Vector::CreateView));

    setupStatusTests("Trapezoidal",grp);
#if 0
    // Create the convergence tests
    using namespace NOX::StatusTest;
    absresid = rcp( new NormF(1.0e-9) );
#ifdef DGM_USE_RELATIVE_STATUS_TEST
    relresid = rcp( new NormF( grp, 1.0e-3, NormF::Unscaled));
#endif
    update = rcp( new NormUpdate(1.0e-9) );
    wrms =  rcp( new NormWRMS(1.0e-2, 1.0e-8) );
    converged = rcp( new Combo(Combo::OR) );
    converged->addStatusTest(absresid);
#ifdef DGM_USE_RELATIVE_STATUS_TEST
    converged->addStatusTest(relresid);
#endif
    converged->addStatusTest(update);
    maxiters = rcp( new MaxIters(10) );
    fv = rcp( new FiniteValue );
    combo = rcp( new Combo(Combo::OR) );
    combo->addStatusTest(fv);
    combo->addStatusTest(converged);
    combo->addStatusTest(maxiters);
#endif
#if 0
    {
      // Try working with a StatusTest parameter file.  The problem right now
      // is that the relative NormF isn't supported
      using Teuchos::RCP;
      using Teuchos::rcp;
      using Teuchos::ParameterList;
      using NOX::StatusTest::Combo;
      using NOX::StatusTest::FiniteValue;
      using NOX::StatusTest::MaxIters;
      using NOX::StatusTest::Divergence;
      using NOX::StatusTest::Stagnation;
      using namespace NOX::StatusTest;

      NOX::Utils utils(printParams);

#ifdef DGM_OLD_STATUSTEST
      ParameterList stl;
#else
      ParameterList &stl( nlParams->sublist("Status Test") );
#endif
      stl.set("Test Type", "Combo");
      stl.set("Combo Type", "OR");
      stl.set("Number of Tests", 5);
      Teuchos::ParameterList& conv = stl.sublist("Test 0");
      Teuchos::ParameterList& fv = stl.sublist("Test 1");
      Teuchos::ParameterList& divergence = stl.sublist("Test 2");
      Teuchos::ParameterList& stagnation = stl.sublist("Test 3");
      Teuchos::ParameterList& maxiters = stl.sublist("Test 4");

      conv.set("Test Type", "Combo");
      conv.set("Combo Type", "AND");
      conv.set("Number of Tests", 3);
      Teuchos::ParameterList& normF = conv.sublist("Test 0");
      Teuchos::ParameterList& normWRMS = conv.sublist("Test 1");
      Teuchos::ParameterList& normUpdate = conv.sublist("Test 2");
      normF.set("Test Type", "NormF");
      normF.set("Tolerance", 1.0e-12);
      normF.set("Norm Type", "Two Norm");
      normF.set("Scale Type", "Unscaled");
      normWRMS.set("Test Type", "NormWRMS");
      normWRMS.set("Absolute Tolerance", 1.0e-8);
      normWRMS.set("Relative Tolerance", 1.0e-5);
      normWRMS.set("Tolerance", 1.0);
      normWRMS.set("BDF Multiplier", 1.0);
      normWRMS.set("Alpha", 1.0);
      normWRMS.set("Beta", 0.5);
      normUpdate.set("Test Type", "NormUpdate");
      normUpdate.set("Norm Type", "One Norm");
      normUpdate.set("Scale Type", "Scaled");

      fv.set("Test Type", "FiniteValue");
      fv.set("Vector Type", "F Vector");
      fv.set("Norm Type", "Two Norm");

      divergence.set("Test Type", "Divergence");
      divergence.set("Tolerance", 1.0e+20);
      divergence.set("Consecutive Iterations", 3);

      stagnation.set("Test Type", "Stagnation");
      stagnation.set("Tolerance", 1.0);
      stagnation.set("Consecutive Iterations", 5);

      maxiters.set("Test Type", "MaxIters");
      maxiters.set("Maximum Iterations", 20);

      Teuchos::RCP<NOX::StatusTest::Generic> statusTestsCombo;

#if defined(HAVE_TEUCHOS_EXTENDED) && defined(DGM_USE_XML)
#ifdef DGM_OLD_STATUSTEST
      cout << "Writing parameter list to \"input.xml\"" << endl;
      Teuchos::writeParameterListToXmlFile(stl, "input.xml");
      cout << "Reading parameter list from \"input.xml\"" << endl;
      // only valid if Status Test are at the top of the Tree
      statusTestsCombo = buildStatusTests("input.xml", utils);
#else
      cout << "Writing parameter list to \"input.xml\"" << endl;
      Teuchos::writeParameterListToXmlFile(*nlParams, "input.xml");
      cout << "Reading parameter list from \"input.xml\"" << endl;
      Teuchos::updateParametersFromXmlFile("input.xml",
        Teuchos::Ptr<Teuchos::ParameterList>(nlParams.get()));
      statusTestsCombo =
        buildStatusTests(nlParams->sublist("Status Test"), utils);
      string fname="output.tri";
      RCP<std::ostream> out(new ofstream(fname.c_str()));
      printParams.set("Output Stream", out);
#endif
#else
      statusTestsCombo = buildStatusTests(stl, utils);
#endif
    }
#endif

    solver = NOX::Solver::buildSolver(grp, combo, nlParams);

    nox_initialized = true;
  }

  void Trapezoidal::advance( Domain *Omega ) {
    if (comm->verbosity()>2)
      comm->cout() << "DGM::Trapezoidal::advance(Domain *)" << endl;
    using namespace NOX::Epetra;
    using Teuchos::RCP; using Teuchos::rcp;

    const double dt = Omega->dt;
    const int &lstep = Omega->lstep;
    double &t = Omega->t;
    vField &U = Omega->U;
    vField &Ut = Omega->Ut;
    NOX::StatusTest::StatusType status;

    Omega->prestep( U, lstep, 0, t );

    copy(U, Ut);

    interface->adjoint(false);
    interface->setup(Ut);  // setup time-derivative at previous time
    t += dt;

    if (nox_initialized) {
      solver->reset(*x);
    } else
      initialize_nox();

    // Try reseting relative 
    relresid->reset(*grp, reltol);

//#define DGM_USE_NOX_SOLVE

#ifdef DGM_USE_NOX_SOLVE
    status = solver->solve();
    static Format sci(3,10,'e');
    comm->cout() << "=====> ";
    comm->cout() << solver->getNumIterations() << ": ";
    if (absresid.get())
      comm->cout() << sci(absresid->getNormF()) << " ";
    if (relresid.get())
      comm->cout() << sci(relresid->getNormF()) << " ";
    if (wrms.get())
      comm->cout() << sci(wrms->getNormWRMS()) << " ";
    comm->cout() << lsParams.sublist("Output").get<int>
      ("Number of Linear Iterations") << "  ";
    comm->cout() << sci(lsParams.sublist("Output").get<double>
      ("Achieved Tolerance")) << " ";
    comm->cout() << endl;
#else
    do {
      status = solver->step();
      static Format sci(3,10,'e');
      comm->cout() << "=====> ";
      comm->cout() << solver->getNumIterations() << ": ";
      if (absresid.get())
        comm->cout() << sci(absresid->getNormF()) << " ";
      if (relresid.get())
        comm->cout() << sci(relresid->getNormF()) << " ";
      if (wrms.get())
        comm->cout() << sci(wrms->getNormWRMS()) << " ";
      comm->cout() << lsParams.sublist("Output").get<int>
        ("Number of Linear Iterations") << "  ";
      comm->cout() << sci(lsParams.sublist("Output").get<double>
        ("Achieved Tolerance")) << " ";
      comm->cout() << endl;
    } while (status == NOX::StatusTest::Unconverged);
#endif

#undef DGM_USE_NOX_SOLVE

    // cout << "MatrixFree perturbation = " << A->getPerturbation() << endl;

    if (status != NOX::StatusTest::Converged)
      if (Comm->MyPID()==0)
        cout << "Nonlinear solver failed to converge!" << endl;

    Omega->poststep( U, lstep, 0, t);
  }

  /// Advanced a domain and objective function with trapezoidal
  void Trapezoidal::advance( Domain *Omega, ObjFunc *Jp ) {
    const Scalar dt = Omega->dt;
    const Ordinal &lstep = Omega->lstep;
    //Scalar &t = Omega->t;
    vField &U = Omega->U;
    advance( Omega );
    ObjFunc &J = *Jp;
    vField &Ut = Omega->Ut;
    ObjFunc S(J);
    S(Ut,lstep-1,0);
    axpy(pt5*dt,S,J);
    ObjFunc R(J);
    R(U,lstep,0);
    axpy(pt5*dt,R,J);
  }

  /// Advance a function with trapezoidal
  void Trapezoidal::advance( DGM::Function *J ) {
    const Scalar dt = J->dt;
    const Ordinal &lstep = J->lstep;
    J->value += pt5*dt * ( J->evaluate( lstep-1, 0 ) +
                           J->evaluate( lstep  , 0 ) );
  }

  /// Accumulate for the gradient
  /** This is only used to accumulate the gradient and the analysis shows
   *  that you should do \f$ \sum_{i=1}^n \Delta t \f$
   */
  void Trapezoidal::accumulate( DGM::Function *J ) {
    const Scalar dt = J->dt;
    const Ordinal &lstep = J->lstep;
    if (lstep>0) J->value += dt * J->evaluate( lstep, 0 );
  }

  /// \todo Update to adjoint trapezoidal
  void Trapezoidal::adjoint_advance( Domain *Omega ) {
    if (comm->verbosity()>2)
      comm->cout() << "DGM::Trapezoidal::adjoint_advance(Domain *)" << endl;
    using namespace NOX::Epetra;
    using Teuchos::RCP; using Teuchos::rcp;

    const double dt = Omega->dt;
    const int &lstep = Omega->lstep;
    double &t = Omega->t;
    vField &U = Omega->U;
    vField &Ut = Omega->Ut;
    NOX::StatusTest::StatusType status;

    Omega->prestep( U, lstep, 0, t );

    copy(U, Ut);

    interface->adjoint(true);
    interface->setup(Ut);          // setup time-derivative at previous time
    t -= dt;
    if (nox_initialized) {
      solver->reset(*x);
    } else
      initialize_nox();

    // is this really necessary?
    interface->set_domain(Omega);

    // Try reseting relative
    relresid->reset(*grp, reltol);

//#define DGM_USE_NOX_SOLVE

#ifdef DGM_USE_NOX_SOLVE
    status = solver->solve();
    static Format sci(3,10,'e');
    comm->cout() << "=====> ";
    comm->cout() << solver->getNumIterations() << ": ";
    if (absresid.get())
      comm->cout() << sci(absresid->getNormF()) << " ";
    if (relresid.get())
      comm->cout() << sci(relresid->getNormF()) << " ";
    if (wrms.get())
      comm->cout() << sci(wrms->getNormWRMS()) << " ";
    comm->cout() << lsParams.sublist("Output").get<int>
      ("Number of Linear Iterations") << "  ";
    comm->cout() << sci(lsParams.sublist("Output").get<double>
      ("Achieved Tolerance")) << " ";
    comm->cout() << endl;
#else
    do {
      status = solver->step();
      static Format sci(3,10,'e');
      comm->cout() << "=====> ";
      comm->cout() << solver->getNumIterations() << ": ";
      if (absresid.get())
        comm->cout() << sci(absresid->getNormF()) << " ";
      if (relresid.get())
        comm->cout() << sci(relresid->getNormF()) << " ";
      if (wrms.get())
        comm->cout() << sci(wrms->getNormWRMS()) << " ";
      comm->cout() << lsParams.sublist("Output").get<int>
        ("Number of Linear Iterations") << "  ";
      comm->cout() << sci(lsParams.sublist("Output").get<double>
        ("Achieved Tolerance")) << " ";
      comm->cout() << endl;
    } while (status == NOX::StatusTest::Unconverged);
#endif

#undef DGM_USE_NOX_SOLVE

    // cout << "MatrixFree perturbation = " << A->getPerturbation() << endl;

    if (status != NOX::StatusTest::Converged)
      if (Comm->MyPID()==0)
        cout << "Nonlinear solver failed to converge!" << endl;

    // now correct the adjoint
    // interface->adjoint_corrector();

    Omega->poststep( U, lstep, 0, t);

    interface->adjoint(false);
  }
  /// Method is not implemented
  void Trapezoidal::residual( Domain *, const vec &, vec & ) {
    comm->cout() << "DGM::Trapezoidal::residual(Domain *, const vec&, vec&) "
        "not implemented." << endl;
  }
  /// Method is not implemented
  void Trapezoidal::adjoint_residual( Domain *, const vec &, vec & ) {
    comm->cout() << "DGM::Trapezoidal::adjoint_residual(Domain *, "
        "const vec&, vec&) not implemented." << endl;
  }

  } // namespace Trilinos

} // namespace DGM

#ifdef DGM_USE_RYTHMOS

//=============================================================================
//                    Stuff Hacked in for Trilinos::Piro
//=============================================================================

#include <cmath>

//#include "Piro_Epetra_RythmosSolver.hpp"
//#include "Piro_Epetra_InvertMassMatrixDecorator.hpp"
//#include "Piro_ValidPiroParameters.hpp"

#include "EpetraExt_ModelEvaluator.h"

#include "Rythmos_BackwardEulerStepper.hpp"
#include "Rythmos_ExplicitRKStepper.hpp"
#include "Rythmos_SimpleIntegrationControlStrategy.hpp"
#include "Rythmos_ForwardSensitivityStepper.hpp"
#include "Rythmos_StepperAsModelEvaluator.hpp"
#include "Stratimikos_DefaultLinearSolverBuilder.hpp"
#include "Thyra_EpetraModelEvaluator.hpp"
#include "Thyra_EpetraThyraWrappers.hpp"


Piro::Epetra::RythmosSolver::RythmosSolver(
    Teuchos::RCP<Teuchos::ParameterList> appParams_,
    Teuchos::RCP<EpetraExt::ModelEvaluator> model_,
    Teuchos::RCP<Rythmos::IntegrationObserverBase<Scalar> > observer ) :
  appParams(appParams_),
  model(model_)
{
 // appParams->validateParameters(*Piro::getValidPiroParameters(),0);

  using Teuchos::RCP;
  using Teuchos::rcp;

      out = Teuchos::VerboseObjectBase::getDefaultOStream();

  num_p = model->createInArgs().Np();
  num_g = model->createOutArgs().Ng();

  TEUCHOS_TEST_FOR_EXCEPTION(num_p > 1, Teuchos::Exceptions::InvalidParameter,
                     std::endl << "Error in Piro::Epetra::RythmosSolver " <<
                     "Not Implemented for Np>1 : " << num_p << std::endl);
  TEUCHOS_TEST_FOR_EXCEPTION(num_g > 1, Teuchos::Exceptions::InvalidParameter,
                     std::endl << "Error in Piro::Epetra::RythmosSolver " <<
                     "Not Implemented for Ng>1 : " << num_g << std::endl);

  //
  *out << "\nA) Get the base parameter list ...\n";
  //

  RCP<Teuchos::ParameterList> rythmosPL = sublist(appParams, "Rythmos", true);
  rythmosPL->validateParameters(*getValidRythmosParameters(),0);

  {
    const string verbosity = rythmosPL->get("Verbosity Level", "VERB_DEFAULT");
    solnVerbLevel = Teuchos::VERB_DEFAULT;
    if      (verbosity == "VERB_NONE")    solnVerbLevel = Teuchos::VERB_NONE;
    else if (verbosity == "VERB_LOW")     solnVerbLevel = Teuchos::VERB_LOW;
    else if (verbosity == "VERB_MEDIUM")  solnVerbLevel = Teuchos::VERB_MEDIUM;
    else if (verbosity == "VERB_HIGH")    solnVerbLevel = Teuchos::VERB_HIGH;
    else if (verbosity == "VERB_EXTREME") solnVerbLevel = Teuchos::VERB_EXTREME;
  }

  const int numTimeSteps = rythmosPL->get("Num Time Steps", 10);
  const Scalar t_init = 0.0;
  t_final = rythmosPL->get("Final Time", 0.1);

  const Rythmos::TimeRange<Scalar> fwdTimeRange(t_init, t_final);
  const Scalar delta_t = t_final / numTimeSteps;
  *out << "\ndelta_t = " << delta_t;

  const string stepperType = rythmosPL->get("Stepper Type", "Backward Euler");

  //
  *out << "\nB) Create the Stratimikos linear solver factory ...\n";
  //
  // This is the linear solve strategy that will be used to solve for the
  // linear system with the W.
  //

  Stratimikos::DefaultLinearSolverBuilder linearSolverBuilder;
  linearSolverBuilder.setParameterList(sublist(rythmosPL, "Stratimikos", true));
  RCP<Thyra::LinearOpWithSolveFactoryBase<Scalar> >
    W_factory = createLinearSolveStrategy(linearSolverBuilder);

  //
  *out << "\nC) Create and initalize the forward model ...\n";
  //

  // C.1) Create the underlying EpetraExt::ModelEvaluator

  // already constructed as "model". Decorate if needed.

/*
      if (stepperType == "Explicit RK") {
        if (rythmosPL->get("Invert Mass Matrix", false)) {
          Teuchos::RCP<EpetraExt::ModelEvaluator> origModel = model;
          model = Teuchos::rcp(new Piro::Epetra::InvertMassMatrixDecorator(
                   sublist(rythmosPL,"Stratimikos", true), origModel));
        }
      }
*/

  // C.2) Create the Thyra-wrapped ModelEvaluator

  fwdStateModel = epetraModelEvaluator(model, W_factory);

  const RCP<const Thyra::VectorSpaceBase<Scalar> >
    x_space = fwdStateModel->get_x_space();

  //
  *out << "\nD) Create the stepper and integrator for the forward problem ...\n";
  //

  fwdTimeStepSolver = Rythmos::timeStepNonlinearSolver<double>();

  if (rythmosPL->getEntryPtr("NonLinear Solver")) {
    RCP<Teuchos::ParameterList> nonlinePL =
      sublist(rythmosPL, "NonLinear Solver", true);
    fwdTimeStepSolver->setParameterList(nonlinePL);
  }

  if (stepperType == "Backward Euler")
    fwdStateStepper = Rythmos::backwardEulerStepper<double>
      (fwdStateModel, fwdTimeStepSolver);
  else if (stepperType == "Explicit RK")
    fwdStateStepper = Rythmos::explicitRKStepper<double>(fwdStateModel);
  else
    TEUCHOS_TEST_FOR_EXCEPTION( true, Teuchos::Exceptions::InvalidParameter,
    std::endl << "Error! Piro::Epetra::RythmosSolver: Invalid Steper Type: "
      << stepperType << std::endl);

  fwdStateStepper->setParameterList(
      sublist(rythmosPL, "Rythmos Stepper", true));
  {
    RCP<Teuchos::ParameterList>
      integrationControlPL = sublist(
          rythmosPL, "Rythmos Integration Control", true);
      integrationControlPL->set( "Take Variable Steps", false );
      integrationControlPL->set( "Fixed dt", Teuchos::as<double>(delta_t) );

      // RCP<Rythmos::IntegratorBase<Scalar> >
      RCP<Rythmos::DefaultIntegrator<Scalar> >
        defaultIntegrator = Rythmos::controlledDefaultIntegrator<Scalar>(
          Rythmos::simpleIntegrationControlStrategy<Scalar>(integrationControlPL)
        );
      fwdStateIntegrator = defaultIntegrator;
    }
    fwdStateIntegrator->setParameterList(
        sublist(rythmosPL, "Rythmos Integrator", true));

  if (observer != Teuchos::null)
    fwdStateIntegrator->setIntegrationObserver(observer);
}

Piro::Epetra::RythmosSolver::~RythmosSolver()
{
}

Teuchos::RCP<const Epetra_Map> Piro::Epetra::RythmosSolver::get_x_map() const
{
  Teuchos::RCP<const Epetra_Map> neverused;
  return neverused;
}

Teuchos::RCP<const Epetra_Map> Piro::Epetra::RythmosSolver::get_f_map() const
{
  Teuchos::RCP<const Epetra_Map> neverused;
  return neverused;
}

Teuchos::RCP<const Epetra_Map> Piro::Epetra::RythmosSolver::
get_p_map(int l) const
{
  TEUCHOS_TEST_FOR_EXCEPTION(l >= num_p || l < 0,
                             Teuchos::Exceptions::InvalidParameter,
                             std::endl <<
                             "Error in Piro::Epetra::RythmosSolver::"
                             "get_p_map(): Invalid parameter index l = " <<
                             l << std::endl);
  return model->get_p_map(l);
}

Teuchos::RCP<const Epetra_Map> Piro::Epetra::RythmosSolver::
get_g_map(int j) const
{
  TEUCHOS_TEST_FOR_EXCEPTION(j > num_g || j < 0,
                             Teuchos::Exceptions::InvalidParameter,
                             std::endl <<
                             "Error in Piro::Epetra::RythmosSolver::"
                             "get_g_map(): Invalid response index j = " <<
                             j << std::endl);

  if      (j < num_g) return model->get_g_map(j);
  else if (j == num_g) return model->get_x_map();

  throw logic_error("Impossible logic in get_g_map");
  return model->get_x_map();
}

Teuchos::RCP<const Epetra_Vector> Piro::Epetra::RythmosSolver::
get_x_init() const
{
  Teuchos::RCP<const Epetra_Vector> neverused;
  return neverused;
}

Teuchos::RCP<const Epetra_Vector> Piro::Epetra::RythmosSolver::
get_p_init(int l) const
{
  TEUCHOS_TEST_FOR_EXCEPTION(l >= num_p || l < 0,
                             Teuchos::Exceptions::InvalidParameter,
                             std::endl <<
                             "Error in Piro::Epetra::RythmosSolver::"
                             "get_p_init(): Invalid parameter index l = " <<
                             l << std::endl);
  return model->get_p_init(l);
}

EpetraExt::ModelEvaluator::InArgs Piro::Epetra::RythmosSolver::
createInArgs() const
{
  // return underlyingME->createInArgs();
  EpetraExt::ModelEvaluator::InArgsSetup inArgs;
  inArgs.setModelEvalDescription(this->description());
  inArgs.set_Np(num_p);
  // inArgs.setSupports(IN_ARG_x,true);
  return inArgs;
}

EpetraExt::ModelEvaluator::OutArgs Piro::Epetra::RythmosSolver::
createOutArgs() const
{
  EpetraExt::ModelEvaluator::OutArgsSetup outArgs;
  outArgs.setModelEvalDescription(this->description());

  // Ng is 1 bigger then model-Ng so that the solution vector can be an outarg
  outArgs.set_Np_Ng(num_p, num_g+1);

  EpetraExt::ModelEvaluator::OutArgs model_outargs = model->createOutArgs();
  for (int i=0; i<num_g; i++)
    for (int j=0; j<num_p; j++)
      if (!model_outargs.supports(OUT_ARG_DgDp, i, j).none())
        outArgs.setSupports(OUT_ARG_DgDp, i, j,
                            DerivativeSupport(DERIV_MV_BY_COL));

  return outArgs;
}

void Piro::Epetra::RythmosSolver::evalModel( const InArgs& inArgs,
                                             const OutArgs& outArgs ) const
{
  using Teuchos::RCP;
  using Teuchos::rcp;

  // Parse InArgs

  RCP<const Epetra_Vector> p_in;
  if (num_p > 0) p_in = inArgs.get_p(0);

  // Parse OutArgs: always 1 extra
  RCP<Epetra_Vector> g_out;
  if (num_g > 0) g_out = outArgs.get_g(0);
  RCP<Epetra_Vector> gx_out = outArgs.get_g(num_g);

  // Parse out-args for sensitivity calculation
  RCP<Epetra_MultiVector> dgdp_out;
  if (num_p>0 && num_g>0)
    dgdp_out = outArgs.get_DgDp(0,0).getMultiVector();

  RCP<const Epetra_Vector> finalSolution;

  Thyra::ModelEvaluatorBase::InArgs<Scalar>
     state_ic = fwdStateModel->getNominalValues();

  // Set paramters p_in as part of initial conditions
  if (num_p > 0)
    state_ic.set_p(0,Thyra::create_Vector(p_in,fwdStateModel->get_p_space(0)));
  *out << "\nstate_ic:\n" << Teuchos::describe(state_ic,solnVerbLevel);

  if (dgdp_out == Teuchos::null) {
    //
    *out << "\nE) Solve the forward problem ...\n";
    //

    fwdStateStepper->setInitialCondition(state_ic);
    fwdStateIntegrator->setStepper(fwdStateStepper, t_final, true);

    Teuchos::Array<RCP<const Thyra::VectorBase<Scalar> > > x_final_array;
    fwdStateIntegrator->
      getFwdPoints(Teuchos::tuple<Scalar>(t_final), &x_final_array,NULL,NULL);
    const RCP<const Thyra::VectorBase<Scalar> > x_final = x_final_array[0];

    finalSolution = Thyra::get_Epetra_Vector(*model->get_x_map(), x_final);

    if (Teuchos::VERB_MEDIUM <= solnVerbLevel)
      cout << "Final Solution\n" << *finalSolution << std::endl;

    // As post-processing step, calc responses at final solution
    EpetraExt::ModelEvaluator::InArgs model_inargs = model->createInArgs();
    EpetraExt::ModelEvaluator::OutArgs model_outargs = model->createOutArgs();
    model_inargs.set_x(finalSolution);
    if (num_p > 0)  model_inargs.set_p(0, p_in);
    if (g_out != Teuchos::null) {
      g_out->PutScalar(0.0);
      model_outargs.set_g(0, g_out);
    }
    model->evalModel(model_inargs, model_outargs);
  }
  else {//Doing sensitivities
    //
    *out << "\nE) Solve the forward problem with Sensitivities...\n";
    //

    RCP<Rythmos::ForwardSensitivityStepper<Scalar> > stateAndSensStepper =
      Rythmos::forwardSensitivityStepper<Scalar>();
    stateAndSensStepper->initializeSyncedSteppers(
          fwdStateModel, 0, fwdStateModel->getNominalValues(),
          fwdStateStepper, fwdTimeStepSolver);

    //
    // Set the initial condition for the state and forward sensitivities
    //

    RCP<Thyra::VectorBase<Scalar> > s_bar_init
      = createMember(stateAndSensStepper->getFwdSensModel()->get_x_space());
    assign( s_bar_init.ptr(), 0.0 );
    RCP<Thyra::VectorBase<Scalar> > s_bar_dot_init
      = createMember(stateAndSensStepper->getFwdSensModel()->get_x_space());
    assign( s_bar_dot_init.ptr(), 0.0 );
    // Above, I believe that these are the correct initial conditions for
    // s_bar and s_bar_dot given how the EpetraExt::DiagonalTransientModel
    // is currently implemented!

    RCP<const Rythmos::StateAndForwardSensitivityModelEvaluator<Scalar> >
      stateAndSensModel = stateAndSensStepper->getStateAndFwdSensModel();

    Thyra::ModelEvaluatorBase::InArgs<Scalar>
      state_and_sens_ic = stateAndSensStepper->getModel()->createInArgs();

    // Copy time, parameters etc.
    state_and_sens_ic.setArgs(state_ic);
    // Set initial condition for x_bar = [ x; s_bar ]
    state_and_sens_ic.set_x(
      stateAndSensModel->create_x_bar_vec(state_ic.get_x(),s_bar_init)
      );
    // Set initial condition for x_bar_dot = [ x_dot; s_bar_dot ]
    state_and_sens_ic.set_x_dot(
      stateAndSensModel->create_x_bar_vec(state_ic.get_x_dot(),s_bar_dot_init)
      );

//  *out << "\nstate_and_sens_ic:\n" <<
//    Teuchos::describe(state_and_sens_ic,Teuchos::VERB_DEFAULT);

    stateAndSensStepper->setInitialCondition(state_and_sens_ic);

    //
    // Use a StepperAsModelEvaluator to integrate the state+sens
    //

    RCP<Rythmos::StepperAsModelEvaluator<Scalar> >
      stateAndSensIntegratorAsModel = Rythmos::stepperAsModelEvaluator(
        Teuchos::rcp_implicit_cast<Rythmos::StepperBase<Scalar> >(
          stateAndSensStepper),
        Teuchos::rcp_implicit_cast<Rythmos::IntegratorBase<Scalar> >(
          fwdStateIntegrator),
        state_and_sens_ic
      );

    *out << "\nUse the StepperAsModelEvaluator to integrate state + "
            "sens x_bar(p,t_final) ... \n";

    RCP<Thyra::VectorBase<Scalar> > x_bar_final;

    Teuchos::OSTab tab(out);

    x_bar_final = createMember(stateAndSensIntegratorAsModel->get_g_space(0));

    eval_g( *stateAndSensIntegratorAsModel, 0, *state_ic.get_p(0),
        t_final, 0, &*x_bar_final);

    *out << "\nx_bar_final = x_bar(p,t_final) evaluated using "
      << "stateAndSensIntegratorAsModel:\n"
      << Teuchos::describe(*x_bar_final,solnVerbLevel);

    // As post-processing step, calc responses and gradient at final solution
    const RCP<const Thyra::VectorBase<Scalar> > x_final =
      Thyra::productVectorBase<Scalar>(x_bar_final)->getVectorBlock(0);
    finalSolution = Thyra::get_Epetra_Vector(*model->get_x_map(), x_final);

    *out << "\nF) Check the solution to the forward problem ...\n";

    // Extract sensitivity vectors into Epetra_MultiVector
    Teuchos::RCP<const Epetra_MultiVector> dxdp =
      Thyra::get_Epetra_MultiVector(*model->get_x_map(),
      Teuchos::rcp_dynamic_cast<
        const Thyra::DefaultMultiVectorProductVector<Scalar> >
          (Thyra::productVectorBase<Scalar>(x_bar_final)->getVectorBlock(1))
          ->getMultiVector() );;

    dgdp_out->PutScalar(0.0);

    Teuchos::RCP<Epetra_MultiVector> dgdx
      = Teuchos::rcp(new Epetra_MultiVector(finalSolution->Map(),
        dgdp_out->GlobalLength()));
    Teuchos::Array<int> p_indexes =
      outArgs.get_DgDp(0,0).getDerivativeMultiVector().getParamIndexes();

    EpetraExt::ModelEvaluator::DerivativeMultiVector dmv_dgdp(dgdp_out,
      DERIV_MV_BY_COL, p_indexes);

    EpetraExt::ModelEvaluator::InArgs model_inargs = model->createInArgs();
    EpetraExt::ModelEvaluator::OutArgs model_outargs = model->createOutArgs();
    model_inargs.set_x(finalSolution);
    model_inargs.set_p(0, p_in);

    if (g_out != Teuchos::null) {
      g_out->PutScalar(0.0);
      model_outargs.set_g(0, g_out);
    }
    model_outargs.set_DgDp(0,0,dmv_dgdp);
    model_outargs.set_DgDx(0,dgdx);

    model->evalModel(model_inargs, model_outargs);

    // (3) Calculate dg/dp = dg/dx*dx/dp + dg/dp
    // This may be the transpose of what we want since we specified
    // we want dg/dp by column in createOutArgs().
    // In this case just interchange the order of dgdx and dxdp
    // We should really probably check what the underlying ME does

    if (Teuchos::VERB_MEDIUM <= solnVerbLevel)
      cout << " dgdx \n" << *dgdx << endl;
    if (Teuchos::VERB_MEDIUM <= solnVerbLevel)
      cout << " dxdp \n" << *dxdp << endl;

    dgdp_out->Multiply('T', 'N', 1.0, *dgdx, *dxdp, 1.0);
  }

  // return the final solution as an additional g-vector, if requested
  if (gx_out != Teuchos::null)  *gx_out = *finalSolution;
}

Teuchos::RCP<const Teuchos::ParameterList>
Piro::Epetra::RythmosSolver::getValidRythmosParameters() const {
  Teuchos::RCP<Teuchos::ParameterList> validPL =
    rcp(new Teuchos::ParameterList("ValidRythmosParams"));;
  validPL->sublist("NonLinear Solver", false, "");
  validPL->set<int>("Num Time Steps", 0, "");
  validPL->set<double>("Final Time", 1.0, "");
  validPL->sublist("Rythmos Stepper", false, "");
  validPL->sublist("Rythmos Integrator", false, "");
  validPL->sublist("Rythmos Integration Control", false, "");
  validPL->sublist("Stratimikos", false, "");
  validPL->set<std::string>("Verbosity Level", "", "");
  validPL->set<std::string>("Stepper Type", "", "");
  validPL->set<double>("Alpha", 1.0, "");
  validPL->set<double>("Beta", 1.0, "");
  validPL->set<double>("Max State Error", 1.0, "");
  validPL->set<std::string>("Name", "", "");
  validPL->set<bool>("Invert Mass Matrix", false, "");
  validPL->set<std::string>("Stepper Method", "", "");
  return validPL;
}

//=============================================================================
//                  End of Stuff Hacked in for Trilinos::Piro
//=============================================================================

#endif // DGM_USE_RYTHMOS

#endif // DGM_USE_EPETRA
