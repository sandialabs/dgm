#ifndef DGM_TRILINOS_TIME_INT_HPP
#define DGM_TRILINOS_TIME_INT_HPP

/** \file Trilinos.hpp
    \brief DGM::Trilinos interface declaration
    \author S. Scott Collis
*/

// DGM includes
#include "TimeInt.hpp"

#ifdef DGM_USE_EPETRA

// Trilinos includes
#include "NOX.H"
#include "NOX_Epetra.H"
#ifdef HAVE_TEUCHOS_EXTENDED
#include "Teuchos_XMLParameterListHelpers.hpp"
#endif
#ifdef DGM_PARALLEL
#include "Epetra_MpiComm.h"
#else
#include "Epetra_SerialComm.h"
#endif

// Json includes
#include "json/value.h"

namespace DGM {

  /// Contains DGM classes that build on Trilinos components
  /** These are interfaces to Trilinos capabilities such as the ModelEvaluator,
   *  NOX, and Rythmos.
   */
  namespace Trilinos {

  //========================================================================
  //                         Model Evaluator
  //========================================================================

  /** \brief Epetra-based model evaluator subclass
   *
   *  This class will support a wide number of different types of
   *  abstract problem types that will allow NOX, LOCA, Rythmos, Aristos,
   *  and MOOCHO to solve different types of problems.
   */
  class ModelEvaluator : public EpetraExt::ModelEvaluator {
  public:

    /** \name Constructors/initializers */
    //@{

    /** \brief Takes the number of elements in the discretization   */
    ModelEvaluator( Domain *omega );

    //@}

    ~ModelEvaluator();

    /** \name Overridden from EpetraExt::ModelEvaluator   */
    //@{

    Teuchos::RCP<const Epetra_Map> get_g_map(int j) const;

    Teuchos::RCP<const Epetra_Vector> get_p_init(int l) const;

    Teuchos::RCP<Epetra_Operator> create_W() const;

    EpetraExt::ModelEvaluator::InArgs createInArgs() const;

    EpetraExt::ModelEvaluator::OutArgs createOutArgs() const;

    void evalModel( const InArgs& inArgs, const OutArgs& outArgs ) const;

    Teuchos::RCP<const Epetra_Map> get_x_map() const;

    Teuchos::RCP<const Epetra_Map> get_f_map() const;

    Teuchos::RCP<const Epetra_Vector> get_x_init() const;

    Teuchos::RCP<const Epetra_Map> get_p_map(int l) const;

    //@}

  private:

    // These are set in the constructor and used in evalModel
    Teuchos::RCP<Epetra_Map> x_map;
    DGM::Domain *Omega;

  };

  //========================================================================
  //                             Rythmos
  //========================================================================

  /// DGM interface to Trilinos::Rythmos time integrators
  class Rythmos : public TimeInt {
    Epetra_Comm *Comm;          ///< Epetra communicator
  public:
    /// Constructor
    Rythmos(Domain *Omega, string="" ) : Comm( Omega->U.eComm.get() ) {}

    /// unique time-integration identifier
    static const int id = TimeInt::TRILINOS_RYTHMOS;

    /// override from TimeInt
    void advance( Domain *Omega ) { DGM_UNDEFINED; }

    /// override from TimeInt
    void residual( Domain *Omega, const vec &, vec &) { DGM_UNDEFINED; }
  };

  //========================================================================
  //                           Base Solver
  //========================================================================

  /// Base class for Trilinos solvers
  class BaseSolver {

  public:
    /// constructor
    BaseSolver( Domain *Omega_, string="" ) :
      Omega(Omega_),
      comm(Omega->get_comm()),
      Comm(Omega->U.eComm.get()),
      nlParams( Teuchos::rcp(new Teuchos::ParameterList) ),
      printParams( nlParams->sublist("Printing") ),
      searchParams( nlParams->sublist("Line Search") ),
      dirParams( nlParams->sublist("Direction") ),
      newtonParams( dirParams.sublist("Newton") ),
      lsParams( newtonParams.sublist("Linear Solver") ),
      slParams( nlParams->sublist("Solver Options") ),
      reltol(0), buildPreconditioner(false) { }

    /// destructor
    ~BaseSolver() {}

    /// setup the solver
    void setup(const string &name);

    /// setup status tests
    void setupStatusTests(const string &name,
                          Teuchos::RCP<NOX::Epetra::Group> grp);

  protected:

    Domain *Omega;          ///< The domain for this solver

    DGM::Comm::Ptr comm;    ///< DGM communicator
    Epetra_Comm *Comm;      ///< Epetra communicator

    Json::Value value;

    Teuchos::RCP<Teuchos::ParameterList> nlParams;
    Teuchos::ParameterList &printParams;
    Teuchos::ParameterList &searchParams;
    Teuchos::ParameterList &dirParams;
    Teuchos::ParameterList &newtonParams;
    Teuchos::ParameterList &lsParams;
    Teuchos::ParameterList &slParams;

    Teuchos::RCP<NOX::StatusTest::NormF> absresid;
    Teuchos::RCP<NOX::StatusTest::NormF> relresid;
    Teuchos::RCP<NOX::StatusTest::NormUpdate> update;
    Teuchos::RCP<NOX::StatusTest::NormWRMS> wrms;
    Teuchos::RCP<NOX::StatusTest::Combo> converged;
    Teuchos::RCP<NOX::StatusTest::MaxIters> maxiters;
    Teuchos::RCP<NOX::StatusTest::FiniteValue> fv;
    Teuchos::RCP<NOX::StatusTest::Combo> combo;

    double reltol;

    bool buildPreconditioner;
  };

  //========================================================================
  //                           Backward Euler
  //========================================================================

  /// First-order backward Euler with Trilinos
  class BackwardEuler : public TimeInt, public BaseSolver {

  public:

    /// Provides the required interface to Trilinos::NOX::Epetra
    class Interface : public NOX::Epetra::Interface::Required {
      Domain *Omega;
      vField R;
      bool _adjoint;
      void convert( const Epetra_Vector &x, dVector &y);
      void convert( const dVector &x, Epetra_Vector &y);
      void convert( const Epetra_Vector &x, vField &y);
      void convert( const vField &x, Epetra_Vector &y);
    public:
      typedef Teuchos::RCP<BackwardEuler::Interface> Ptr;
      Interface( Domain *omega);
      bool computeF( const Epetra_Vector &x, Epetra_Vector &r, FillType flag);
      void setup( vField & ) {};
      void adjoint(const bool adjoint) { _adjoint=adjoint; }
      bool adjoint() const { return _adjoint; }
      void set_domain(Domain *domain) { Omega=domain; }
    private:
      bool residual(const Epetra_Vector &x, Epetra_Vector &r, FillType flag);
      bool adjoint_residual(const Epetra_Vector &x, Epetra_Vector &r,
                            FillType flag);
    };

  private:

    Teuchos::RCP<Epetra_Vector> soln;
    Teuchos::RCP<Interface> interface;
    Teuchos::RCP<NOX::Epetra::MatrixFree> A;
    Teuchos::RCP<NOX::Epetra::FiniteDifference> FD;
    Teuchos::RCP<NOX::Epetra::Interface::Jacobian> iJac;
    Teuchos::RCP<NOX::Epetra::Interface::Preconditioner> iPrec;
    Teuchos::RCP<NOX::Epetra::Vector> x;
    Teuchos::RCP<NOX::Epetra::LinearSystem> linSys;
    Teuchos::RCP<NOX::Epetra::Group> grp;
    Teuchos::RCP<NOX::Solver::Generic> solver;

    bool nox_initialized;          ///< status of NOX initialization
    void initialize_nox(Domain *); ///< helper to setup the NOX+AztecOO solver

  public:
    /// constructor
    BackwardEuler( Domain *, string="" );

    /// destructor
    ~BackwardEuler() {}

    /// unique time-integration identifier
    static const int id = TimeInt::TRILINOS_BACKWARD_EULER;

    /// \name Override from TimeInt
    //@{
    /// Advance the domain
    void advance(Domain *);
    /// Advance a function
    void advance(DGM::Function *);
    /// Accumulate a function for the gradient
    void accumulate(DGM::Function *);
    /// Advance a Domain and ObjFunc
    void advance(Domain *, ObjFunc *);
    /// Adjoint advance a domain
    void adjoint_advance(Domain *);

    /// Defines the residual
    void residual( Domain *, const vec &, vec &);
    /// Defines the adjoint residual
    void adjoint_residual(Domain *, const vec &, vec &);

    bool is_implicit() const { return true; }
    //@}
  };

  //========================================================================
  //                           BDF2
  //========================================================================

  /// Second-order BDF with Trilinos
  class BDF2 : public TimeInt, public BaseSolver {

  public:

    /// Provides the required interface to Trilinos::NOX::Epetra
    class Interface : public NOX::Epetra::Interface::Required {
      Domain *Omega;
      vField R;
      void convert( const Epetra_Vector &x, dVector &y);
      void convert( const dVector &x, Epetra_Vector &y);
      void convert( const Epetra_Vector &x, vField &y);
      void convert( const vField &x, Epetra_Vector &y);
    public:
      typedef Teuchos::RCP<BackwardEuler::Interface> Ptr;
      Interface( Domain *omega );
      bool computeF( const Epetra_Vector &x, Epetra_Vector &b, FillType flag);
      void setup( vField & ) {};
    };

  private:

    Teuchos::RCP<Epetra_Vector> soln;

    Teuchos::RCP<Interface> interface;
    Teuchos::RCP<NOX::Epetra::MatrixFree> A;
    Teuchos::RCP<NOX::Epetra::Vector> x;
    Teuchos::RCP<NOX::Epetra::LinearSystem> linSys;
    Teuchos::RCP<NOX::Epetra::Group> grp;

    Teuchos::RCP<NOX::Solver::Generic> solver;

    bool nox_initialized;          ///< status of NOX initialization
    void initialize_nox(Domain *); ///< a helper to setup the NOX+AztecOO solver

  public:
    /// constructor
    BDF2( Domain *, string="" );

    /// destructor
    ~BDF2() {}

    /// unique time-integration identifier
    static const int id = TimeInt::TRILINOS_BDF2;

    /// override from TimeInt
    void advance( Domain * );

    /// override from TimeInt
    void residual( Domain *, const vec &, vec &);

    bool is_implicit() const { return true; }
  };

  //========================================================================
  //                             Trapezoidal
  //========================================================================

  /// Second-order trapezoidal integration with Trilinos
  class Trapezoidal : public TimeInt, public BaseSolver {

  public:

    /// Interface to Trilinos::NOX::Epetra
    class Interface : public NOX::Epetra::Interface::Required {
      int verb;
      Domain *Omega;
      DGM::Comm::Ptr comm;
      vField R, S;
      bool _adjoint;
      void convert( const Epetra_Vector &x, dVector &y);
      void convert( const dVector &x, Epetra_Vector &y);
      void convert( const Epetra_Vector &x, vField &y);
      void convert( const vField &x, Epetra_Vector &y);
    public:
      typedef Teuchos::RCP<Trapezoidal::Interface> Ptr;
      Interface( Domain *omega );
      virtual ~Interface() { };
      bool computeF( const Epetra_Vector &x, Epetra_Vector &b, FillType flag);
      /// \warning Requires Nt==Npredict
      void setup( vField &X) {
        if (!adjoint() || (Omega->lstep < Omega->Nt) )
          Omega->time_derivative(X,S);
      }
      void adjoint(const bool adjoint) { _adjoint=adjoint; }
      bool adjoint() const { return _adjoint; }
      void set_domain(Domain *domain) { Omega=domain; }
      bool adjoint_corrector();
    private:
      bool residual(const Epetra_Vector &x, Epetra_Vector &r, FillType flag);
      bool adjoint_residual(const Epetra_Vector &x, Epetra_Vector &r,
                            FillType flag);
    };

  private:

    Teuchos::RCP<Epetra_Vector> soln;
    Teuchos::RCP<Interface> interface;
    Teuchos::RCP<NOX::Epetra::MatrixFree> A;
    Teuchos::RCP<NOX::Epetra::FiniteDifference> FD;
    Teuchos::RCP<NOX::Epetra::Interface::Jacobian> iJac;
    Teuchos::RCP<NOX::Epetra::Interface::Preconditioner> iPrec;
    Teuchos::RCP<NOX::Epetra::Vector> x;
    Teuchos::RCP<NOX::Epetra::LinearSystem> linSys;
    Teuchos::RCP<NOX::Epetra::Group> grp;
    Teuchos::RCP<NOX::Solver::Generic> solver;

    bool nox_initialized;    ///< status of NOX initialization
    void initialize_nox();   ///< a helper to setup the NOX+AztecOO solver

  public:

    Trapezoidal( Domain *, string="" );

    ~Trapezoidal() {}

    /// Unique time-integration identifier
    static const int id = TimeInt::TRILINOS_TRAPEZOIDAL;

    /// \name Override from TimeInt
    //@{
    /// Advance a domain
    void advance(Domain *);
    /// Advance a function
    void advance(DGM::Function *);
    /// Accumulate the gradient
    void accumulate(DGM::Function *);
    /// Advance a Domain and ObjFunc
    void advance(Domain *, ObjFunc *);
    /// Adjoint advance a domain
    void adjoint_advance(Domain *);

    /// Defines the residual
    void residual( Domain *, const vec &, vec &);
    /// Defines the adjoint residual
    void adjoint_residual(Domain *, const vec &, vec &);

    bool is_implicit() const { return true; }
    //@}
  };

} // namespace Trilinos

} // namespace DGM


#ifdef DGM_USE_RYTHMOS

//=============================================================================
//                    Stuff Hacked in for Trilinos::Piro
//=============================================================================

#include <iostream>

#include "Epetra_Vector.h"
#include "Epetra_LocalMap.h"

#ifdef HAVE_MPI
#include "Epetra_MpiComm.h"
#else
typedef int MPI_Comm;
#define MPI_COMM_WORLD 1
#include "Epetra_SerialComm.h"
#endif

#include "EpetraExt_ModelEvaluator.h"

#include "Rythmos_DefaultIntegrator.hpp"
#include "Rythmos_IntegrationObserverBase.hpp"
#include "Rythmos_TimeStepNonlinearSolver.hpp"


/** \brief Epetra-based Model Evaluator subclass for Charon!
 *
 * This class will support a wide number of different types of abstract
 * problem types that will allow NOX, LOCA, Rythmos, Aristos, and MOOCHO to
 * solve different types of problems with Charon.
 *
 * ToDo: Finish documentation!
*/

namespace Piro {
namespace Epetra {

  class RythmosSolver : public EpetraExt::ModelEvaluator
  {

    typedef double Scalar;

  public:

    /** \name Constructors/initializers */
    //@{

    /** \brief Takes the number of elements in the discretization   */
    RythmosSolver(Teuchos::RCP<Teuchos::ParameterList> appParams,
                  Teuchos::RCP<EpetraExt::ModelEvaluator> model,
                  Teuchos::RCP<Rythmos::IntegrationObserverBase<Scalar> >
                  observer = Teuchos::null
                  );

    //@}

    ~RythmosSolver();


    /** \name Overridden from EpetraExt::ModelEvaluator   */
    //@{

    Teuchos::RCP<const Epetra_Map> get_g_map(int j) const;
    /** \brief   */
    Teuchos::RCP<const Epetra_Vector> get_p_init(int l) const;
    /** \brief   */
    //  Teuchos::RCP<Epetra_Operator> create_W() const;
    /** \brief   */
    EpetraExt::ModelEvaluator::InArgs createInArgs() const;
    /** \brief   */
    EpetraExt::ModelEvaluator::OutArgs createOutArgs() const;
    /** \brief   */
    void evalModel( const InArgs& inArgs, const OutArgs& outArgs ) const;

  private:
    /** \brief   */
    Teuchos::RCP<const Epetra_Map> get_x_map() const;
    /** \brief   */
    Teuchos::RCP<const Epetra_Map> get_f_map() const;
    /** \brief   */
    Teuchos::RCP<const Epetra_Vector> get_x_init() const;
    /** \brief   */
    Teuchos::RCP<const Epetra_Map> get_p_map(int l) const;
    /** \brief   */
    void setProblemParamDefaults(Teuchos::ParameterList* appParams_);
    /** \brief   */
    void setSolverParamDefaults(Teuchos::ParameterList* appParams_);
    /** \brief   */
    Teuchos::RCP<const Teuchos::ParameterList>
    getValidRythmosParameters() const;

    //@}

  private:

    //These are set in the constructor and used in evalModel
    mutable Teuchos::RCP<Teuchos::ParameterList> appParams;
    Teuchos::RCP<EpetraExt::ModelEvaluator> model;

    int num_p;
    int num_g;

    Teuchos::RCP<Rythmos::StepperBase<Scalar> > fwdStateStepper;
    Teuchos::RCP<Teuchos::FancyOStream> out;
    Teuchos::EVerbosityLevel solnVerbLevel;
    Teuchos::RCP<Rythmos::DefaultIntegrator<Scalar> > fwdStateIntegrator;
    Teuchos::RCP<Thyra::ModelEvaluator<double> > fwdStateModel;
    Teuchos::RCP<Rythmos::TimeStepNonlinearSolver<double> > fwdTimeStepSolver;
    Scalar t_final;
  };

}  // namespace Epetra
}  // namespace Piro

//=============================================================================
//                  End of Stuff Hacked in for Trilinos::Piro
//=============================================================================

#endif // DGM_USE_RYTHMOS

#endif // DGM_USE_EPETRA

#endif // DGM_TRILINOS_TIME_INT_HPP
