#ifndef DGM_TIME_INT_HPP
#define DGM_TIME_INT_HPP

// System includes
#include <fstream>
#include <iostream>
#include <vector>
#include <iterator>
#include <string>
using namespace std;

// DGM includes
#include "Comm.hpp"
#include "vField.hpp"
#include "Domain.hpp"
#include "Function.hpp"

namespace DGM {

// forward declarations
class ObjFunc;

/** \file TimeInt.hpp
    \brief Time discretization interface class
    \author Scott Collis

    Domain must have the following members:
    Scalar dt;
    Ordinal    lstep;
    Scalar t;
    vField U;
    vField Ut;

    And member functions:
    void prestep( vField &, const Ordinal, const Ordinal, const Scalar );
    void poststep( vField &, const Ordinal, const Ordinal, const Scalar );
    void time_derivative( vField &, vField &);

    Notes:
    1) I should introduce a template type for "vField"
    2) time_derivative is misleading since du/dt + rhs = 0 right now.
    3) Should I check to make sure that Omega is in physical space?
    4) Currently turned off template.  It can easily be templatized...

    \deprecated This non-templated version is deprecated by DTK::TimeIntegrate
*/

/// Time Integration base class
class TimeInt {

 protected:

  Ordinal nsubstep;         ///< number of substeps for this method
  Ordinal substep;          ///< internal substep counter

 public:

  /// Shared pointer to TimeInt
  typedef DGM::Shared<TimeInt>::Ptr Ptr;

  /// Supported integration types
  enum IntType {
    UNDEFINED     = -1,  ///< undefined time stepper
    FORWARD_EULER =  0,  ///< first-order forward Euler, one-step method
#ifdef DGM_USE_ITL
    BACKWARD_EULER=  1,  ///< ITL first-order accurate backward Euler
#endif
    MULTISTEP     =  2,  ///< Second order, two-step method
    TVD_RK        =  3,  ///< Third-order, TVD Runge-Kutta method
    RUNGE_KUTTA   =  4,  ///< Standard, symmetric fourth-order Runge-Kutta
#ifdef DGM_USE_ITL
    TRAPEZOIDAL   =  5,  ///< ITL second-order accurate trapezoidal method
#endif
    SSPRK         =  6,  ///< Strongly-stable Runge-Kutta method
    HALE_RK7      =  7,  ///< Seven-stage Runge-Kutta method
    JAMESON       =  8,  ///< Jameson's dissipative Runge-Kutta method
    LSRK14        = 14,  ///< Fourth-order, 14-stage, low-storage Runge-Kutta
    HALE_RK67     = 67,  ///< Sixth-order, seven-stage Runge-Kutta method
#ifdef DGM_USE_EPETRA
    TRILINOS_RYTHMOS        = 100, ///< Trilinos Rythmos integrator
    TRILINOS_BACKWARD_EULER = 101, ///< Trilinos 1st order backward Euler
    TRILINOS_TRAPEZOIDAL    = 102, ///< Trilinos 2nd order trapezoidal
    TRILINOS_BDF2           = 103, ///< Trilinos 2nd order BDF
#endif
    UNUSED        = 1000           ///< Extra just to fix missing comma
  };

  /// Constructor
  TimeInt() : nsubstep(1), substep(0) {}

  /// Destructor
  virtual ~TimeInt() {}

  static std::string enumToName(const IntType i) {
    static const char *names[16] =
     {"Undefined",
      "Forward Euler",
      "Backward Euler",
      "Multistep",
      "TVD RK",
      "Runge Kutta"  ,
      "Trapezoidal"  ,
      "SSPRK"        ,
      "Hale_RK7"     ,
      "Jameson"      ,
      "Hale_RK67"    ,
      "LSRK14"       ,
      "Trilinos::Rythmos",
      "Trilinos::Backward Euler",
      "Trilinos::Trapezoidal",
      "Trilinso::BDF2" };
    switch (i) {
      case UNDEFINED      : return names[ 0]; break;
      case FORWARD_EULER  : return names[ 1]; break;
      case MULTISTEP      : return names[ 3]; break;
      case TVD_RK         : return names[ 4]; break;
      case RUNGE_KUTTA    : return names[ 5]; break;
      case SSPRK          : return names[ 7]; break;
      case HALE_RK7       : return names[ 8]; break;
      case JAMESON        : return names[ 9]; break;
      case HALE_RK67      : return names[10]; break;
      case LSRK14         : return names[11]; break;
#ifdef DGM_USE_ITL
      case BACKWARD_EULER : return names[ 2]; break;
      case TRAPEZOIDAL    : return names[ 6]; break;
#endif
#ifdef DGM_USE_EPETRA
      case TRILINOS_RYTHMOS        : return names[12]; break;
      case TRILINOS_BACKWARD_EULER : return names[13]; break;
      case TRILINOS_TRAPEZOIDAL    : return names[14]; break;
      case TRILINOS_BDF2           : return names[15]; break;
#endif
      default             : return names[ 0]; break;
    }
  }

  static IntType nameToEnum(const std::string &n) {
    if      (n == enumToName(UNDEFINED     )) return UNDEFINED;
    else if (n == enumToName(FORWARD_EULER )) return FORWARD_EULER;
    else if (n == enumToName(MULTISTEP     )) return MULTISTEP;
    else if (n == enumToName(TVD_RK)      || n == "TVD") return TVD_RK;
    else if (n == enumToName(RUNGE_KUTTA) || n == "RK4") return RUNGE_KUTTA;
    else if (n == enumToName(SSPRK         )) return SSPRK;
    else if (n == enumToName(HALE_RK7      )) return HALE_RK7;
    else if (n == enumToName(JAMESON       )) return JAMESON;
    else if (n == enumToName(HALE_RK67     )) return HALE_RK67;
    else if (n == enumToName(LSRK14        )) return LSRK14;
#ifdef DGM_USE_ITL
    else if (n == enumToName(BACKWARD_EULER)) return BACKWARD_EULER;
    else if (n == enumToName(TRAPEZOIDAL   )) return TRAPEZOIDAL;
#endif
#ifdef DGM_USE_EPETRA
    else if (n == enumToName(TRILINOS_RYTHMOS)) return TRILINOS_RYTHMOS;
    else if (n == enumToName(TRILINOS_BACKWARD_EULER)) 
      return TRILINOS_BACKWARD_EULER;
    else if (n == enumToName(TRILINOS_TRAPEZOIDAL)) return TRILINOS_TRAPEZOIDAL;
    else if (n == enumToName(TRILINOS_BDF2)) return TRILINOS_BDF2;
#endif
    else return UNDEFINED;
  }

  /// Get total number of substeps for this method (useful for RK methods)
  Ordinal numsubstep() const { return nsubstep; }
  /// Get the current substep index (useful for RK methods)
  Ordinal getsubstep() const { return substep; }
  /// Initialize the time integration method
  void initialize() { substep = 0; }
  /// Query whether the current time integration method is implicit
  virtual bool is_implicit() const { return false; }
  /// Query whether the current time integration method is explicit
  virtual bool is_explicit() const { return (!is_implicit()); }

  /// Flattened vector storage
  typedef std::vector<Scalar> vec;

  /// Basic advance method
  virtual void advance( Domain *Omega) {
    Omega->get_comm()->cerr() << "TimeInt:advance(Domain *Omega) not "
        "implemented" << endl;
    Omega->get_comm()->exit(DGM::FAILURE);
  }
  /// Basic advance method
  virtual void advance( DGM::Function *Omega) {
    DGM::Comm::World->cerr() << "TimeInt:advance(DGM::Function *Omega) not "
        "implemented" << endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  /// Basic accumulate method (for gradient accumulation)
  virtual void accumulate( DGM::Function *Omega) {
    advance(Omega);
  }
  /// Advance method for optimization problems
  virtual void advance( Domain *Omega, ObjFunc *) {
    Omega->get_comm()->cerr() << "TimeInt:advance(Domain *Omega, ObjFunc *) "
        "not implemented" << endl;
    Omega->get_comm()->exit(DGM::FAILURE);
  }
  /// Adjoint advance method for optimization problems
  virtual void adjoint_advance( Domain *Omega ) {
    Omega->get_comm()->cerr() << "TimeInt:adjoint_advance(Domain *Omega) not "
        "implemented" << endl;
    Omega->get_comm()->exit(DGM::FAILURE);
  }
  /// Adjoint advance method for optimization problems
  virtual void adjoint_advance( Domain *Omega, ObjFunc *) {
    Omega->get_comm()->cerr() << "TimeInt:adjoint_advance(Domain *Omega, "
        "ObjFunc *) not implemented" << endl;
    Omega->get_comm()->exit(DGM::FAILURE);
  }
  /// Residual evaluation for implicit methods
  virtual void residual( Domain *Omega, const vec &, vec & ) {
    Omega->get_comm()->cerr()<<"TimeInt:residual(Domain *, const vec &, vec&) "
        "not implemented" << endl;
    Omega->get_comm()->exit(DGM::FAILURE);
  }
  /// Adjoint residual evaluation for implicit methods
  virtual void adjoint_residual( Domain *Omega, const vec &, vec & ) {
    Omega->get_comm()->cerr()<<"TimeInt:adjoint_residual(Domain *, "
        "const vec &, vec &) not implemented" << endl;
    Omega->get_comm()->exit(DGM::FAILURE);
  }
  /// Interpolation method
  virtual void interpolate( const Ordinal, const vField &, vField & ) {
    DGM::Comm::World->cerr()<<"TimeInt:interpolate(const Ordinal, "
        "const vField &, vField &) not implemented"<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  /// Interpolation method
  virtual void interpolate( const Ordinal, const Scalar &, Scalar & ) {
    DGM::Comm::World->cerr()<<"TimeInt:interpolate(const Ordinal, "
        "const Scalar &, Scalar &) not implemented"<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  /// Interpolation method
  virtual Scalar interpolate(const Scalar, const Scalar, const Ordinal) const {
    DGM::Comm::World->cerr()<<"TimeInt:interpolate(const Scalar, "
        "const Scalar, const Ordinal) not implemented"<<endl;
    DGM::Comm::World->exit(DGM::FAILURE);
    return 0;
  }
  /// Get the relative substep time for a given substep
  virtual Scalar getsubtime( const Ordinal s) const { 
    // Use linearly spaced substeps as default
    return ((Scalar) s) / ((Scalar) nsubstep);
  }

  /// Convert from ITL to vField storage
  void convert( const vec &X, vField &F ) const;

  /// Convert from vField to ITL storage
  void convert( const vField &F, vec &X ) const;
};

/// One-step Forward Euler time integrator
class ForwardEuler : public TimeInt {
  const Ordinal NR;                ///< Number of registers
  vector<vField> R;                ///< Temporary fields
 public:
  ForwardEuler( DGM::Domain * );
  void advance( DGM::Domain * );
  void advance( DGM::Function * );
  void advance( Domain *, ObjFunc * );
  void adjoint_advance( Domain * );
  void adjoint_advance( Domain *, ObjFunc * ) {DGM_UNDEFINED;}
  Scalar getsubtime(const Ordinal ) const;
};

/// Function evaluator class for implicit time advancement
class Evaluator {
  typedef std::vector<Scalar> vec;  ///< flattened vector storage
  mutable Domain *Omega;            ///< active domain
  mutable TimeInt *Method;          ///< time integration method
 public:
  /// constructor
  Evaluator( Domain *omega, TimeInt *method ) : Omega(omega),
                                                Method(method) {}
  /// function method
  void operator() ( const vec &X, vec &Y ) const {
    //cout << "computing residual" << endl;
    Method->residual( Omega, X, Y );
  }
};

/// Function evaluator class for implicit time advancement
class AdjointEvaluator {
  typedef std::vector<Scalar> vec; ///< flattened vector storage
  mutable Domain *Omega;           ///< active domain
  mutable TimeInt *Method;         ///< time integration method
 public:
  /// constructor
  AdjointEvaluator( Domain *omega, TimeInt *method ) : Omega(omega),
                                                       Method(method) {}
  /// function method
  void operator() ( const vec &X, vec &Y ) const {
    Method->adjoint_residual( Omega, X, Y );
  }
};

/// Four-step multi-step time integration method
class Multistep : public TimeInt {
  const Ordinal NR;      ///< Number of temporary (registers) fields
  vector<vField> R;      ///< Temporary fields
 public:
  Multistep( Domain * );
  void advance( Domain * );
  void advance( DGM::Function * ) {DGM_UNDEFINED;}
  void advance( Domain *, ObjFunc * ) {DGM_UNDEFINED;}
};

/// Fourth order symmetric Runge-Kutta method
class RungeKutta : public TimeInt {
  const Ordinal NR;         ///< Number of temporary (registers) fields
  vector<vField> R;         ///< Temporary fields
  static const Scalar a[3]; ///< sub time step
  static const Scalar b[4]; ///< weights
 public:
  RungeKutta( Domain * );
  void advance( Domain * );
  void advance( DGM::Function * );
  void advance( Domain *, ObjFunc * );
  void advance_old( Domain *, ObjFunc * );
  void adjoint_advance( Domain * );
  void adjoint_advance( Domain *, ObjFunc * );
  void interpolate( const Ordinal, const vField &, vField & );
  void interpolate( const Ordinal, const Scalar &, Scalar & );
  Scalar interpolate(const Scalar, const Scalar, const Ordinal ) const;
  Scalar getsubtime(const Ordinal ) const;
};

/// Jameson's dissipative Runge-Kutta method
class Jameson : public TimeInt {
  const Ordinal NR;  ///< Number of temporary (registers) fields
  vector<vField> R;  ///< Temporary fields
 public:
  Jameson( Domain * );
  void advance( Domain * );
  void advance( DGM::Function * ) {DGM_UNDEFINED;}
  void advance( Domain *, ObjFunc * ) {DGM_UNDEFINED;}
};

/// Third-order accurate TVD Runge-Kutta method
class TVD : public TimeInt {
  const Ordinal NR;    ///< Number of temporary (registers) fields
  vector<vField> R;    ///< Temporary fields
  static const Scalar a[3];     ///< sub time step
  static const Scalar b[3];     ///< weights
  static const Scalar c[3];     ///< Time step coef.
  static const Scalar w[3];     ///< adjoint weights
 public:
  TVD( Domain * );
  void advance( Domain * );
  void advance( DGM::Function * );
  void advance( Domain *, ObjFunc * );
  void adjoint_advance( Domain * );
  void adjoint_advance( Domain *, ObjFunc * ) {DGM_UNDEFINED;}
  void interpolate( const Ordinal, const vField &, vField & );
  void interpolate( const Ordinal, const Scalar &, Scalar & );
  Scalar interpolate(const Scalar, const Scalar, const Ordinal ) const;
  Scalar getsubtime(const Ordinal ) const;
};

/// Strong Stability-Preserving Runge-Kutta method
class SSPRK : public TimeInt {
  const Ordinal NR;       ///< maximum number of stages supported
  vector<vField> R;       ///< vector of temporary fields
  Ordinal m;              ///< number of stages (and order of accuracy)
  Table params;           ///< parameters table
  static const Scalar a[][5];   ///< weights
 public:
  SSPRK( Domain * );
  void advance( Domain * );
  void advance( DGM::Function * );
  void advance( Domain *, ObjFunc * );
  void adjoint_advance( Domain * );
  void adjoint_advance( Domain *, ObjFunc * ) {DGM_UNDEFINED;}
  void interpolate( const Ordinal, const vField &, vField & );
  void interpolate( const Ordinal, const Scalar &, Scalar & );
  Scalar interpolate(const Scalar, const Scalar, const Ordinal ) const;
  Scalar getsubtime(const Ordinal ) const;
};

#ifdef DGM_USE_ITL

/// First-order accurate Implicit (Backward) Euler method
class BackwardEuler : public TimeInt {
  const Ordinal NR;        ///< Number of temporary (registers) fields
  vector<vField> R;        ///< Temporary fields
  Table params;            ///< Parameters table
  Ordinal ntout;           ///< output frequency
  ofstream *out;           ///< my output stream
  Ordinal newton_max_iter; ///< Parameters for iterative method
  Scalar newton_rtol, newton_atol, newton_stol;
  Ordinal gmres_max_iter,gmres_restart;
  Scalar gmres_rtol, gmres_atol;
  Scalar fd_step_size;     ///< finite difference step size
 public:
  BackwardEuler( Domain *, string="" );
  void advance( Domain * );
  void advance( DGM::Function * );
  void advance( Domain *, ObjFunc * );
  void adjoint_advance( Domain * );
  void adjoint_advance( Domain *, ObjFunc * ) {DGM_UNDEFINED;}
  void residual( Domain *, const vec &, vec &);
  void adjoint_residual( Domain *, const vec &, vec &);
  bool is_implicit() const { return true; }
  Scalar getsubtime(const Ordinal ) const;
};

/// Second-order accurate implicit Trapezoidal method
class Trapezoidal : public TimeInt {
  const Ordinal NR;           ///< Number of temporary (registers) fields
  vector<vField> R;           ///< Temporary fields
  Table params;               ///< Parameters table
  Ordinal ntout;              ///< output frequency
  ostream *out;               ///< my output stream
  Ordinal newton_max_iter;    ///< Parameters for iterative method
  Scalar newton_rtol, newton_atol, newton_stol;
  Ordinal gmres_max_iter,gmres_restart;
  Scalar gmres_rtol, gmres_atol;
  Scalar fd_step_size;        ///< finite difference step size
 public:
  Trapezoidal( Domain *, string="" );
  void advance( Domain * );
  void advance( DGM::Function * ) {DGM_UNDEFINED;}
  void advance( Domain *, ObjFunc * ) {DGM_UNDEFINED;}
  void residual( Domain *, const vec &, vec &);
  bool is_implicit() const { return true; }
};

#endif  // DGM_USE_ITL

/// High-Accuracy Large-Step Explicit Runge-Kutta, see AIAA paper 2006-797
class HALERK7 : public TimeInt {
  const Ordinal NR;             ///< Number of temporary (registers) fields
  vector<vField> R;             ///< Temporary fields
  static const Scalar a[7];     ///< sub time step
  static const Scalar b[7];     ///< weights
  static const Scalar c[7];     ///< Time step coef.
 public:
  HALERK7( Domain * );
  void advance( Domain * );
  void advance( DGM::Function * ) {DGM_UNDEFINED;}
  void advance( Domain *, ObjFunc * ) {DGM_UNDEFINED;}
  void adjoint_advance( Domain * ) {DGM_UNDEFINED;}
  void adjoint_advance( Domain *, ObjFunc * ) {DGM_UNDEFINED;}
  void interpolate( const Ordinal, const vField &, vField & ) {DGM_UNDEFINED;}
  void interpolate( const Ordinal, const Scalar &, Scalar & ) {DGM_UNDEFINED;}
};

/// High-Accuracy Large-Step Explicit Runge-Kutta, see AIAA paper 2006-797
class HALERK67 : public TimeInt {
  const Ordinal NR;              ///< Number of temporary (registers) fields
  vector<vField> R;              ///< Temporary fields
  static const Scalar a1[6];     ///< sub time step
  static const Scalar b1[6];     ///< weights
  static const Scalar c1[6];     ///< Time step coef.
  static const Scalar a2[7];     ///< sub time step
  static const Scalar b2[7];     ///< weights
  static const Scalar c2[7];     ///< Time step coef.
 public:
  HALERK67( Domain * );
  void advance( Domain * );
  void advance( DGM::Function * ) {DGM_UNDEFINED;}
  void advance( Domain *, ObjFunc * ) {DGM_UNDEFINED;}
  void adjoint_advance( Domain * ) {DGM_UNDEFINED;}
  void adjoint_advance( Domain *, ObjFunc * ) {DGM_UNDEFINED;}
  void interpolate( const Ordinal, const vField &, vField & ) {DGM_UNDEFINED;}
  void interpolate( const Ordinal, const Scalar &, Scalar & ) {DGM_UNDEFINED;}
};

/// Low-Storage Runge-Kutta time integration method (14 stage, 2 registers),
/** See doi:10.1016/j.jcp.2011.09.003 */
class LSRK14 : public TimeInt {
  const Ordinal NR;              ///< Number of temporary (registers) fields
  vector<vField> R;              ///< Temporary fields
  static const Scalar A[15];     ///< sub time step
  static const Scalar B[14];     ///< weights
  static const Scalar c[14];     ///< Time step coef.
  static const Scalar w[15];     ///< adjoint weights
 public:
  LSRK14( Domain * );
  void advance( Domain * );
  void advance( DGM::Function * );
  void advance( Domain *, ObjFunc * );
  void adjoint_advance( Domain * );
  void adjoint_advance( Domain *, ObjFunc * ) {DGM_UNDEFINED;}
  void interpolate( const Ordinal, const vField &, vField & );
  void interpolate( const Ordinal, const Scalar &, Scalar & );
  Scalar interpolate(const Scalar, const Scalar, const Ordinal ) const;
  Scalar getsubtime(const Ordinal ) const;
};

} // namespace DGM

#endif  // DGM_TIME_INT_HPP
