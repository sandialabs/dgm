#ifndef DTK_TIME_INTEGRATE_HPP
#define DTK_TIME_INTEGRATE_HPP

/** \file DTK_TimeIntegrate.hpp
    \brief DTK Time discretization interface class
    \author Scott Collis
*/

// System includes
#include <fstream>
#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include <sstream>
#include <stdexcept>
#include <map>

// DTK includes
#include "DTK.hpp"

namespace DTK {

/// Simple scalar function class used by DTK::TimeIntegrate
template <typename Scalar, typename Ordinal>
class ScalarFunction {
public:
  Scalar dt;           ///< time step
  Scalar t;            ///< time
  Scalar value;        ///< value
  Ordinal lstep;       ///< local step index
  /// Constructor
  ScalarFunction( const Scalar t_, const Scalar dt_ )
  : dt(dt_), t(t_), value(0), lstep(0) { }
  /// Destructor
  virtual ~ScalarFunction() {};
  /// Evaluation interface
  virtual Scalar evaluate( const Ordinal, const Ordinal ) = 0;
};

/// Templated time integration base class
template< typename Scalar,
          typename Ordinal,
          typename Data,
          typename Function >
class TimeIntegrate : virtual public Object
{

protected:

  Ordinal nsubstep;     ///< number of substeps for this method
  Ordinal substep;      ///< internal substep counter

  /// Convert object to a string
  template <class T>
  inline static std::string asString(const T &t) {
    std::stringstream ss;
    ss << t;
    return ss.str();
  }

public:

  /// Supported integration types
  enum IntType
  {
    UNDEFINED=-1,       ///< undefined method
    FORWARD_EULER=0,    ///< 1st accurate forward Euler, one-step method
    MULTISTEP=2,        ///< Second order, two-step method
    TVD_RK=3,           ///< Third-order, TVD Runge-Kutta method
    RUNGE_KUTTA=4,      ///< Standard, symmetric fourth-order Runge-Kutta
    SSPRK=6,            ///< Strongly-stable Runge-Kutta method
    HALE_RK7=7,         ///< Seven-stage Runge-Kutta method
    JAMESON=8,          ///< Jameson's dissipative Runge-Kutta method
    LEAPFROG=9,         ///< Second-order LeapFrog
    NOTHING=10,         ///< No time integrator (for debugging)
    LSRK14=14,          ///< Low-storage 14-stage Runge-Kutta
    HALE_RK67=67        ///< Sixth-order, seven-stage Runge-Kutta method
  };

  /// Constructor
  TimeIntegrate(const Ordinal _nsubstep=0) :
    nsubstep(_nsubstep),
    substep(0)
  {
  }

  /// Destructor
  virtual ~TimeIntegrate()
  {
  }

  static std::string enumToName(const IntType i) {
    switch (i) {
      case UNDEFINED     : return "Undefined"    ; break;
      case FORWARD_EULER : return "Forward Euler"; break;
      case MULTISTEP     : return "Multistep"    ; break;
      case TVD_RK        : return "TVD RK"       ; break;
      case RUNGE_KUTTA   : return "Runge Kutta"  ; break;
      case SSPRK         : return "SSPRK"        ; break;
      case HALE_RK7      : return "Hale_RK7"     ; break;
      case JAMESON       : return "Jameson"      ; break;
      case LEAPFROG      : return "Leap Frog"    ; break;
      case NOTHING       : return "Nothing"      ; break;
      case LSRK14        : return "LSRK14"       ; break;
      case HALE_RK67     : return "Hale_RK67"    ; break;
           default       : return ""             ; break;
    }
  }

  static IntType nameToEnum(const std::string &n) {
    if      (enumToName(UNDEFINED    ) == n) return UNDEFINED    ;
    else if (enumToName(FORWARD_EULER) == n) return FORWARD_EULER;
    else if (enumToName(MULTISTEP    ) == n) return MULTISTEP    ;
    else if (enumToName(TVD_RK       ) == n) return TVD_RK       ;
    else if (enumToName(RUNGE_KUTTA  ) == n) return RUNGE_KUTTA  ;
    else if (enumToName(SSPRK        ) == n) return SSPRK        ;
    else if (enumToName(HALE_RK7     ) == n) return HALE_RK7     ;
    else if (enumToName(JAMESON      ) == n) return JAMESON      ;
    else if (enumToName(LEAPFROG     ) == n) return LEAPFROG     ;
    else if (enumToName(NOTHING      ) == n) return NOTHING      ;
    else if (enumToName(LSRK14       ) == n) return LSRK14       ;
    else if (enumToName(HALE_RK67    ) == n) return HALE_RK67    ;
    else throw DTK::exception("nameToEnum: name not defined"+n);
  }

  /// Get total number of substeps for this method (useful for RK methods)
  Ordinal numsubstep() const
  {
    return nsubstep;
  }

  /// Get the current substep index (useful for RK methods)
  Ordinal getsubstep() const
  {
    return substep;
  }

  /// Initialize the time integration method
  virtual void initialize()
  {
    substep = 0;
  }

  /// Query whether the current time integration method is implicit
  virtual bool is_implicit() const
  {
    return false;
  }

  /// Query whether the current time integration method is explicit
  virtual bool is_explicit() const
  {
    return (!is_implicit());
  }

  /// Flattened vector storage
  typedef std::vector< Scalar > vec;

  /// Basic advance method
  virtual void advance( Function *) = 0;

  /// Adjoint advance method
  virtual void adjoint_advance( Function *) = 0;

  virtual void integrate( ScalarFunction<Scalar,Ordinal> *J ) {
    throw std::runtime_error("DTK::TimeIntegrate::integrate() not implemented");
  }

  /// Interpolation method for Data
  virtual void interpolate(const Ordinal sstep,
                           const Data &,
                           Data & )
  {
    throw DTK::exception("DTK::TimeIntegrate::interpolate() not implemented");
  }

  /// Interpolation method for Scalar
  virtual void interpolate(const Ordinal sstep,
                           const Scalar &,
                           Scalar & )
  {
    throw DTK::exception("DTK::TimeIntegrate::interpolate() not implemented");
  }

  /// Get the relative substep time for a given substep
  virtual Scalar getsubtime( const Ordinal )
  { 
    throw DTK::exception("DTK::TimeIntegrate::getsubtime() not implemented");
  }

};

//=============================================================================
//                   Nothing method
//=============================================================================

/// Nothing time integration method
template< typename Scalar,
          typename Ordinal,
          typename Data,
          typename Function >
class Nothing : public TimeIntegrate< Scalar,Ordinal,Data,Function >
{
  const Ordinal NR;         ///< Number of temporary (registers) fields
  std::vector<Data> R;      ///< Temporary fields
  /// typedef for base class
  typedef TimeIntegrate<Scalar,Ordinal,Data,Function> ti;

 public:
  Nothing( Function *Omega ) : NR(1), R(NR, Data(Omega->get_comm()))
  {
    initialize();
    for (Ordinal n=0; n<NR; ++n)
    {
      R[n].clone(Omega->getU());
      R[n].zero();
      R[n].set_name("R["+this->asString(n)+"]");
    }
  }

  virtual ~Nothing()
  {
  }

  virtual void advance(Function *Omega)
  {
  }

  virtual void adjoint_advance(Function *)
  {
    throw DTK::exception("adjoint_advance not implemented");
  }

private:
  void initialize()
  {
  }

};

//=============================================================================
//                   First-order Forward Euler method
//=============================================================================

/// One-step Forward Euler time integration method
template< typename Scalar,
          typename Ordinal,
          typename Data,
          typename Function >
class ForwardEuler : public TimeIntegrate< Scalar,Ordinal,Data,Function >
{
  const Ordinal NR;         ///< Number of temporary (registers) fields
  std::vector<Data> R;      ///< Temporary fields
  /// typedef for base class
  typedef TimeIntegrate<Scalar,Ordinal,Data,Function> ti;

 public:
  ForwardEuler( Function *Omega ) : NR(1), R(NR, Data(Omega->get_comm()))
  {
    initialize();
    for (Ordinal n=0; n<NR; ++n)
    {
      R[n].clone(Omega->getU());
      R[n].zero();
      R[n].set_name("R["+this->asString(n)+"]");
    }
  }

  virtual ~ForwardEuler()
  {
  }

  virtual void advance(Function *Omega)
  {
    const Scalar dt = Omega->timeStep();
    Scalar t = Omega->time();
    Data &U = Omega->getU();
    t += dt;
    Omega->time(t);
    Omega->time_derivative( U, R[0] );
#if 1
    axpy( -dt, R[0], U );
#else
    scale( -dt, R[0] );
    add( R[0], U );
#endif
  }

  virtual void adjoint_advance(Function *)
  {
    throw DTK::exception("adjoint_advance not implemented");
  }

private:
  void initialize()
  {
  }

};

//=============================================================================
//                   Third-order Multistep method
//=============================================================================

/// Four-step multi-step time integration method
template< typename Scalar,
          typename Ordinal,
          typename Data,
          typename Function >
class Multistep : public TimeIntegrate< Scalar,Ordinal,Data,Function >
{
  const Ordinal NR;      ///< Number of temporary (registers) fields
  std::vector<Data>  R;  ///< Temporary fields
  /// typedef for base class
  typedef TimeIntegrate<Scalar,Ordinal,Data,Function> ti;

 public:
  Multistep( Function *Omega ) : NR(4), R(NR, Data(Omega->get_comm()))
  {
    initialize();
    for (Ordinal n=0; n<NR; ++n)
    {
      R[n].clone(Omega->getU());
      R[n].zero();
      R[n].set_name("R["+this->asString(n)+"]");
    }
  }

  virtual ~Multistep()
  {
  }

  virtual void advance( Function *Omega )
  {
    static Scalar beta[][3] = {
      {1.0 ,       0.0    ,  0.0      },
      {3.0/2.0,   -1.0/2.0,  0.0      },
      {23.0/12.0, -4.0/3.0,  5.0/12.0 }};
    const Ordinal Order = 3;
    const Scalar  dt = Omega->timeStep();
    const Ordinal &lstep = Omega->lstep;
    Scalar t = Omega->time();
    Data &U = Omega->getU();
    // compute RHS
    t += dt;
    Omega->time(t);
    Omega->time_derivative( U, R[0] );
    // three step multistep method
    Ordinal j = (lstep < Order) ? lstep-1: Order-1;
    scale( -beta[j][Order-1]*dt, R[Order-1] );
    for(Ordinal i=0; i<Order-1; ++i)
      axpy( -beta[j][i]*dt, R[i], R[Order-1] );
    add( R[Order-1], U );
    // pointer manipulation (no memory is create/destroyed)
    Data Tmp(R[Order-1]);
    for(Ordinal i=Order-1; i>0; --i) R[i] = R[i-1];
    R[0] = Tmp;
  }

  virtual void adjoint_advance(Function *)
  {
    throw DTK::exception("adjoint_advance not implemented");
  }

private:
  void initialize()
  {
  }

};

//============================================================================
//                   Third-order TVD Runge-Kutta
//============================================================================

/// Third-order accurate TVD Runge-Kutta time-integration method
/** Butcher Tableau:
    \verbatim
    0   | 0
    1   | 1     0
    1/2 | 1/4 1/4  0
    -----------------
        | 1/6 1/6 2/3
    \endverbatim
*/
template< typename Scalar,
          typename Ordinal,
          typename Data,
          typename Function >
class TVD : public TimeIntegrate< Scalar,Ordinal,Data,Function >
{
  const Ordinal NR;           ///< Number of temporary (registers) fields
  std::vector<Scalar> a;      ///< weights
  std::vector<Scalar> b;      ///< weights
  std::vector<Scalar> c;      ///< sub time step
  std::vector<Scalar> w;      ///< adjoint weights
  std::vector<Data> R;        ///< Temporary fields
  typedef TimeIntegrate<Scalar,Ordinal,Data,Function> ti;  ///< base class

 public:
  TVD(Function *Omega) : ti(3), NR(1), R(NR, Data(Omega->get_comm()))
  {
    a.resize(3);
    a[0] = (Scalar)0.0;
    a[1] = (Scalar)3.0/4.0;
    a[2] = (Scalar)1.0/3.0;
    b.resize(3);
    b[0] = (Scalar)0.0;
    b[1] = (Scalar)1.0/4.0;
    b[2] = (Scalar)2.0/3.0;
    c.resize(3);
    c[0] = (Scalar)0.0;
    c[1] = (Scalar)1.0;
    c[2] = (Scalar)1.0/2.0;
    w.resize(3);
    w[0] = (Scalar)1.0/6.0;
    w[1] = (Scalar)1.0/6.0;
    w[2] = (Scalar)2.0/3.0;
    initialize();
    for (Ordinal n=0; n<NR; ++n)
    {
      R[n].clone(Omega->getU());
      R[n].zero();
      R[n].set_name("R["+this->asString(n)+"]");
    }
  }

  virtual ~TVD()
  {
  }

  virtual void advance(Function *);

  virtual void integrate( ScalarFunction<Scalar,Ordinal> *J );

  virtual void adjoint_advance(Function *);

  virtual void interpolate(const Ordinal sstep,
                           const Data &,
                           Data & );

  virtual void interpolate(const Ordinal sstep,
                           const Scalar &,
                           Scalar & );

  virtual Scalar getsubtime( const Ordinal);

private:

  void initialize() { }

};

template< typename Scalar,
          typename Ordinal,
          typename Data,
          typename Function >
void TVD< Scalar,Ordinal,Data,Function >::advance(Function *Omega)
{
  const Scalar dt = Omega->timeStep();
  const Scalar tn = Omega->time();
  const Ordinal lstep = Omega->stepNumber();
  Scalar t = Omega->time();
  Ordinal &substep = ti::substep;
  Data &U = Omega->getU();
  Data &Ut = Omega->getUt();

  substep = 0;
  t = tn + c[substep]*dt;
  Omega->prestep( U, lstep-1, substep, t );
  Omega->time_derivative( U, R[0] ); // R0 = -f(Un)
  axpy( -dt, R[0], U, Ut );          // Ut = U - dt*R0
  // scale( b[0], Ut );              // Can omit since b[0] = 1.0
  t = tn + c[substep+1]*dt;
  Omega->time(t);
  Omega->poststep( Ut, lstep-1, substep+1, t );
  
  substep = 1;
  Omega->prestep( Ut, lstep-1, substep, t );
  Omega->time_derivative( Ut, R[0] ); // R0 = -f(Ut)
  axpy( -dt, R[0], Ut, R[0] );        // R0 = Ut - dt*R0
  axpby( a[substep], U, b[substep], R[0], Ut); // Ut = a1*Un + b1*R0
  t = tn + c[substep+1]*dt;
  Omega->time(t);
  Omega->poststep( Ut, lstep-1, substep+1, t );

  substep = 2;
  Omega->prestep( Ut, lstep-1, substep, t );
  Omega->time_derivative( Ut, R[0] ); // R0 = -f(Ut)
  axpy( -dt, R[0], Ut, R[0] );        // R0 = Ut - dt*R0
  axpby( b[substep], R[0], a[substep], U, U); // Un1 = a2*Un + b2*R0
  t = tn + dt;
  Omega->time(t);
  Omega->poststep( U, lstep, 0, t );
}

template< typename Scalar,
          typename Ordinal,
          typename Data,
          typename Function >
void TVD< Scalar,Ordinal,Data,Function >::
integrate( ScalarFunction<Scalar,Ordinal> *J ) {
  const Scalar dt = J->dt;
  const Ordinal &lstep = J->lstep;
  Scalar &t = J->t;
  Ordinal &substep = ti::substep;
  Scalar Jev;

  substep = 0;
  Jev  = J->evaluate( lstep-1, substep );
  J->value += dt*w[substep]*Jev; // J = J + dt*w0*Jev
  t += dt;

  substep = 1;
  Jev  = J->evaluate( lstep-1, substep );
  J->value += dt*w[substep]*Jev; // J = J + dt*w1*Jev
  t -= 0.5*dt;

  substep = 2;
  Jev  = J->evaluate( lstep-1, substep );
  J->value += dt*w[substep]*Jev; // J = J + dt*w2*Jev
  t += 0.5*dt;

}

template< typename Scalar,
          typename Ordinal,
          typename Data,
          typename Function >
void TVD< Scalar,Ordinal,Data,Function >::
adjoint_advance(Function *Omega)
{
  const Scalar dt = Omega->timeStep();
  const Ordinal lstep = Omega->stepNumber();
  const Scalar tn = Omega->time();
  Scalar t = Omega->time();
  Data &U = Omega->getU();
  Data &Ut = Omega->getUt();
  Ordinal &substep = ti::substep;

  substep = 2;
  t = tn + c[substep]*dt;
  Omega->prestep(U, lstep-1, substep, t);
  Omega->time_derivative(U, R[0]);
  axpby(dt*b[substep], R[0], b[substep], U, Ut);  // Ut = b2*U + dt*b2*R0
  axpby( a[substep-1], Ut, a[substep], U, U);     // U  = a2*U + a1*Ut
  t = tn + c[substep-1]*dt;
  Omega->time(t);
  Omega->poststep(Ut, lstep-1, substep, t);

  substep = 1;
  scale(b[substep]/w[substep], Ut);               // Ut = b1*Ut/w1
  Omega->prestep(Ut, lstep-1, substep, t);
  Omega->time_derivative(Ut, R[0]);
  axpby(dt*w[substep], R[0], w[substep], Ut, Ut); // Ut = w1*Ut + dt*w1*R0
  t = tn + c[substep-1]*dt;
  Omega->time(t);
  Omega->poststep(Ut, lstep-1, substep, t);

  substep = 0;
  scale(b[substep]/w[substep], Ut);               // Ut = b0*Ut/w0
  Omega->prestep(Ut, lstep-1, substep, t);
  Omega->time_derivative(Ut, R[0]);
  axpby(dt*w[substep], R[0], w[substep], Ut, Ut); // Ut = w0*Ut + dt*w0*R0
  axpy(b[substep], Ut, U);                        // U = U + b0*Ut
  t = tn;
  Omega->time(t);
  Omega->poststep(U, lstep-1, substep, t);
}

template< typename Scalar,
          typename Ordinal,
          typename Data,
          typename Function >
void TVD< Scalar,Ordinal,Data,Function >::
interpolate(const Ordinal sstep,
            const Data &U_ip1,
            Data &U_i)
{
  scale( 1.0 - c[sstep], U_i );
  axpy( c[sstep], U_ip1, U_i );
}

template< typename Scalar,
          typename Ordinal,
          typename Data,
          typename Function >
void TVD< Scalar,Ordinal,Data,Function >::
interpolate(const Ordinal sstep,
            const Scalar &U_ip1,
            Scalar &U_i)
{
  U_i = (1.0 - c[sstep]) * U_i + c[sstep] * U_ip1;
}

template< typename Scalar,
          typename Ordinal,
          typename Data,
          typename Function >
Scalar TVD< Scalar,Ordinal,Data,Function >::
getsubtime(const Ordinal sstep)
{
  return c[sstep];
}

//============================================================================
//                     Fourth order Runge-Kutta
//============================================================================

/// Fourth-order symmetric Runge-Kutta time integration method
template< typename Scalar,
          typename Ordinal,
          typename Data,
          typename Function >
class RungeKutta : public TimeIntegrate< Scalar,Ordinal,Data,Function >
{
  const Ordinal NR;           ///< Number of temporary (registers) fields
  std::vector<Scalar> a;      ///< sub time step
  std::vector<Scalar> b;      ///< weights
  std::vector<Data>   R;      ///< Temporary fields
  typedef TimeIntegrate<Scalar,Ordinal,Data,Function> ti;  ///< base class
 public:
  RungeKutta(Function *Omega) : ti(4), NR(2)
  {
    const Data data(Omega->get_comm());
    R.resize(NR, data);
    //cout << "DTK::RungeKutta constructor" << endl;
    a.resize(3);
    a[0] = (Scalar)0.5;
    a[1] = (Scalar)0.5;
    a[2] = (Scalar)1.0;
    b.resize(4);
    b[0] = (Scalar)0.16666666666666667;
    b[1] = (Scalar)0.33333333333333333;
    b[2] = (Scalar)0.33333333333333333;
    b[3] = (Scalar)0.16666666666666667;
    initialize();
    for (Ordinal n=0; n<NR; ++n) {
      R[n].clone(Omega->getU());
      R[n].zero();
      R[n].set_name("R["+this->asString(n)+"]");
    }
  }

  virtual ~RungeKutta() { }

  virtual void advance(Function *);

  virtual void integrate( ScalarFunction<Scalar,Ordinal> *J );

  virtual void adjoint_advance(Function *);

  virtual void interpolate(const Ordinal sstep,
                           const Data &,
                           Data & );

  virtual void interpolate(const Ordinal sstep,
                           const Scalar &,
                           Scalar & );

  virtual Scalar getsubtime( const Ordinal);

private:

  void initialize() { }
};

template< typename Scalar,
          typename Ordinal,
          typename Data,
          typename Function >
void RungeKutta< Scalar,Ordinal,Data,Function >::advance(Function *Omega)
{
  //cout << "RungeKutta::advance() with nsubstep = " << ti::nsubstep << endl;
  const Scalar dt = Omega->timeStep();
  const Ordinal lstep = Omega->stepNumber();
  Scalar t = Omega->time();
  Data &U = Omega->getU();
  Data &Ut = Omega->getUt();
  Ordinal &substep = ti::substep;
                                                // y_1 = x_k
  substep = 0;
  Omega->prestep( U, lstep-1, substep, t );     // u_1
  Omega->time_derivative( U, R[0] );
  axpy( -a[0]*dt, R[0], U, Ut );
  scale(-b[0], R[0] );
  t += 0.5*dt;
  Omega->time(t);
  Omega->poststep( Ut, lstep-1, substep+1, t ); // y_2

  substep = 1;
  Omega->prestep( Ut, lstep-1, substep, t );    // u_2
  Omega->time_derivative( Ut, R[1] );
  axpy( -a[1]*dt, R[1], U, Ut );
  axpy( -b[1], R[1], R[0]);
  Omega->poststep( Ut, lstep-1, substep+1, t ); // y_3

  substep = 2;
  Omega->prestep( Ut, lstep-1, substep, t );    // u_3
  Omega->time_derivative( Ut, R[1] );
  axpy( -a[2]*dt, R[1], U, Ut );
  axpy( -b[2], R[1], R[0]);
  t += 0.5*dt;
  Omega->time(t);
  Omega->poststep( Ut, lstep-1, substep+1, t ); // y_4

  substep = 3;
  Omega->prestep( Ut, lstep-1, substep, t );    // u_4
  Omega->time_derivative( Ut, R[1] );
  axpy( -b[3], R[1], R[0]);
  axpy( dt, R[0], U);
  Omega->poststep( U, lstep, 0, t );            // x_{k+1}
}

template< typename Scalar,
          typename Ordinal,
          typename Data,
          typename Function >
void RungeKutta< Scalar,Ordinal,Data,Function >::
integrate( ScalarFunction<Scalar,Ordinal> *J ) {
  const Scalar dt = J->dt;
  const Ordinal &lstep = J->lstep;
  Scalar &t = J->t;
  Ordinal &substep = ti::substep;
  Scalar r[2];

  substep = 0;
  r[0]  = J->evaluate( lstep-1, substep );
  r[0] *= b[0];
  t += 0.5*dt;

  substep = 1;
  r[1]  = J->evaluate( lstep-1, substep );
  r[0] += b[1]*r[1];

  substep = 2;
  r[1]  = J->evaluate( lstep-1, substep );
  r[0] += b[2]*r[1];
  t += 0.5*dt;

  substep = 3;
  r[1]  = J->evaluate( lstep-1, substep );
  r[0] += b[3]*r[1];
  J->value += dt*r[0];
}

template< typename Scalar,
          typename Ordinal,
          typename Data,
          typename Function >
void RungeKutta< Scalar,Ordinal,Data,Function >::
adjoint_advance(Function *Omega)
{
  const Scalar dt = Omega->timeStep();
  const Ordinal lstep = Omega->stepNumber();
  Scalar t = Omega->time();
  Data &U = Omega->getU();
  Data &Ut = Omega->getUt();
  Ordinal &substep = ti::substep;
                                                 // \xi_4 = \psi_{k+1}
  substep = 3;
  Omega->prestep(U,lstep-1,substep,t);           // y_4, u_4
  Omega->time_derivative( U, R[0] );
  axpy(  a[0]*dt, R[0], U, Ut );
  scale( b[3], R[0] );
  t -= 0.5*dt;
  Omega->time(t);
  Omega->poststep(Ut,lstep-1,substep,t);         // \xi_3

  substep = 2;
  Omega->prestep(Ut,lstep-1,substep,t);          // y_3, u_3
  Omega->time_derivative( Ut, R[1] );
  axpy( a[1]*dt, R[1], U, Ut );
  axpy( b[2], R[1], R[0]);
  Omega->poststep(Ut,lstep-1,substep,t);         // \xi_2

  substep = 1;
  Omega->prestep(Ut,lstep-1,substep,t);          // y_2, u_2
  Omega->time_derivative( Ut, R[1] );
  axpy( a[2]*dt, R[1], U, Ut );
  axpy( b[1], R[1], R[0]);
  t -= 0.5*dt;
  Omega->time(t);
  Omega->poststep(Ut,lstep-1,substep,t);         // \xi_1

  substep = 0;
  Omega->prestep(Ut,lstep-1,substep,t);          // y_1, u_1
  Omega->time_derivative( Ut, R[1] );
  axpy( b[0], R[1], R[0]);
  axpy( dt, R[0], U);
  Omega->poststep(U,lstep-1,substep,t);          // \psi_k
}

template< typename Scalar,
          typename Ordinal,
          typename Data,
          typename Function >
void RungeKutta< Scalar,Ordinal,Data,Function >::
interpolate(const Ordinal sstep,
            const Data &U_ip1,
            Data &U_i)
{
  const Scalar w2 = (sstep == 0) ? 0.0 : a[sstep-1];
  const Scalar w1 = 1.0 - w2;
  scale( w1, U_i );
  axpy( w2, U_ip1, U_i );
}

template< typename Scalar,
          typename Ordinal,
          typename Data,
          typename Function >
void RungeKutta< Scalar,Ordinal,Data,Function >::
interpolate(const Ordinal sstep,
            const Scalar &U_ip1,
            Scalar &U_i)
{
  const Scalar w2 = (sstep == 0) ? 0.0 : a[sstep-1];
  const Scalar w1 = 1.0 - w2;
  U_i = w1 * U_i + w2 * U_ip1;
}

template< typename Scalar,
          typename Ordinal,
          typename Data,
          typename Function >
Scalar RungeKutta< Scalar,Ordinal,Data,Function >::
getsubtime(const Ordinal sstep)
{
  return (sstep == 0) ? 0.0 : a[sstep-1];
}

//=============================================================================
//                        Second-order LeapFrop
//=============================================================================

/// Second-order LeapFrop multi-step method
/** \warning This is untested
    \note Need to refactor so that an additional register is not needed
    \note This requires a different interface to the Function::time_integrate
    \note Perhaps instead of time_integrate, there should be an update method
    \note But, then there is redundancy...
*/
template< typename Scalar,
          typename Ordinal,
          typename Data,
          typename Function >
class LeapFrog : public TimeIntegrate< Scalar,Ordinal,Data,Function >
{
  const Ordinal NR;         ///< Number of temporary (registers) fields
  std::vector<Data> R;      ///< Temporary fields
  /// typedef for base class
  typedef TimeIntegrate<Scalar,Ordinal,Data,Function> ti;

 public:

  /// Constructor
  LeapFrog(Function *Omega) : NR(1), R(NR, Data(Omega->get_comm()))
  {
    initialize();
    for (Ordinal n=0; n<NR; ++n)
    {
      R[n].clone(Omega->U);
      R[n].zero();
      R[n].set_name("R["+this->asString(n)+"]");
    }
    std::cout<<"Warning:  LeapFrog is not yet fully implemented."<<std::endl;
  }

  virtual ~LeapFrog()
  {
  }

  /// Advance method
  virtual void advance(Function *Omega)
  {
    const Scalar dt = Omega->timeStep();
    Data &U = Omega->U;
    Scalar t = Omega->time();

    // first 1/2 step
    Omega->time_derivative( U, R[0], 0);
    t += 0.5*dt;
    Omega->time(t);
    scale( -0.5*dt, R[0] );
    add( R[0], U );

    // second 1/2 step
    Omega->time_derivative( U, R[0], 1);
    t += 0.5*dt;
    Omega->time(t);
    scale( -0.5*dt, R[0] );
    add( R[0], U );
  }

  /// Adjoint advance method
  virtual void adjoint_advance(Function *)
  {
    throw DTK::exception("LeapFrog adjoint_advance not implemented");
  }

private:

  /// No special initialization at this time
  void initialize()
  {
  }

};

//============================================================================
//                   Low-Storage Runge-Kutta (14 stage)
//============================================================================

/// Low-Storage Runge-Kutta time integration method (14 stage, 2 registers)
/** This Low-Storage Runge-Kutta time integration method (14 stage, 2 registers)
    is based on:
    \verbatim
    Jens Niegemann, Richard Diehl, and Kurt Busch
    Efficient Low-Storage Runge-Kutta Schemes with Optimized Stability Regions
    Journal of Computational Physics, 231(2), pp. 364-372, 2012,
    doi 10.1016/j.jcp.2011.09.003, issn 0021-9991
    \endverbatim

    For the system of ODEs
    \f[ \frac{\partial}{\partial t} y(t) = F(t,y) \f]
    and using low-storage RK formulation of Williamson
    \f[ K_1 = y_n \f]
    \f[ K_2 = A_i K_2 + \Delta t F( t_n + c_i \Delta t, K_1) \f]
    \f[ K_1 = K_1 + B_i K_2 \f]
    \f[ y_{n+1} = K_1 \f]

    \verbatim
    | 1     0   0   0   0 | | K_1^0 | = | y_n |
    | F_1  -1   0   0   0 | | K_2^1 | = | 0   |
    | 1   B_1  -1   0   0 | | K_1^1 | = | 0   |
    | 0   A_2 F_2   0   0 | | K_2^2 | = | 0   |
    | 0     0 B_2  -1   0 | | K_1^2 | = | 0   |
    | 0     0   0   1  -1 | | y_n+1 | = | 0   |
    \endverbatim

*/
template< typename Scalar,
          typename Ordinal,
          typename Data,
          typename Function >
class LSRK14 : public TimeIntegrate< Scalar,Ordinal,Data,Function >
{
  const Ordinal NR;           ///< Number of temporary (registers) fields
  std::vector<Scalar> A;      ///< sub-time-step
  std::vector<Scalar> B;      ///< weights
  std::vector<Scalar> c;      ///< time locations
  std::vector<Scalar> w;      ///< adjoint weights
  std::vector<Data>   R;      ///< temporary fields
  int verb;                   ///< verbosity

  typedef TimeIntegrate<Scalar,Ordinal,Data,Function> ti;  ///< base class

public:

  LSRK14(Function *Omega, const int _verb) :  ti(14), NR(1), 
    R(NR, Data(Omega->get_comm())), verb(_verb)
  {
    if (verb>1) std::cout << "DTK::LSRK14 constructor" << std::endl;
    const int nstages = 14;
    A.resize(nstages+1);
    A[0]  = (Scalar) 0.0;
    A[1]  = (Scalar)-0.7188012108672410;
    A[2]  = (Scalar)-0.7785331173421570;
    A[3]  = (Scalar)-0.0053282796654044;
    A[4]  = (Scalar)-0.8552979934029281;
    A[5]  = (Scalar)-3.9564138245774565;
    A[6]  = (Scalar)-1.5780575380587385;
    A[7]  = (Scalar)-2.0837094552574054;
    A[8]  = (Scalar)-0.7483334182761610;
    A[9]  = (Scalar)-0.7032861106563359;
    A[10] = (Scalar) 0.0013917096117681;
    A[11] = (Scalar)-0.0932075369637460;
    A[12] = (Scalar)-0.9514200470875948;
    A[13] = (Scalar)-7.1151571693922548;
    A[14] = (Scalar) 0.0;

    B.resize(nstages);
    B[0]  = (Scalar)0.0367762454319673;
    B[1]  = (Scalar)0.3136296607553959;
    B[2]  = (Scalar)0.1531848691869027;
    B[3]  = (Scalar)0.0030097086818182;
    B[4]  = (Scalar)0.3326293790646110;
    B[5]  = (Scalar)0.2440251405350864;
    B[6]  = (Scalar)0.3718879239592277;
    B[7]  = (Scalar)0.6204126221582444;
    B[8]  = (Scalar)0.1524043173028741;
    B[9]  = (Scalar)0.0760894927419266;
    B[10] = (Scalar)0.0077604214040978;
    B[11] = (Scalar)0.0024647284755382;
    B[12] = (Scalar)0.0780348340049386;
    B[13] = (Scalar)5.5059777270269628;

    c.resize(nstages);
    c[0]  = (Scalar)0.0;
    c[1]  = (Scalar)0.0367762454319673;
    c[2]  = (Scalar)0.1249685262725025;
    c[3]  = (Scalar)0.2446177702277698;
    c[4]  = (Scalar)0.2476149531070420;
    c[5]  = (Scalar)0.2969311120382472;
    c[6]  = (Scalar)0.3978149645802642;
    c[7]  = (Scalar)0.5270854589440328;
    c[8]  = (Scalar)0.6981269994175695;
    c[9]  = (Scalar)0.8190890835352128;
    c[10] = (Scalar)0.8527059887098624;
    c[11] = (Scalar)0.8604711817462826;
    c[12] = (Scalar)0.8627060376969976;
    c[13] = (Scalar)0.8734213127600976;

    w.resize(nstages+1);
    w[0]  = (Scalar)-0.116683473041717417;
    w[1]  = (Scalar) 0.213493962104674251;
    w[2]  = (Scalar) 0.128620987881127052;
    w[3]  = (Scalar) 4.610096100109887907;
    w[4]  = (Scalar)-5.386527768056724064;
    w[5]  = (Scalar) 1.445540684241274576;
    w[6]  = (Scalar)-0.761388932107154526;
    w[7]  = (Scalar) 0.543874700576422732;
    w[8]  = (Scalar) 0.102277834602298279;
    w[9]  = (Scalar) 0.07127466608688701188;
    w[10] = (Scalar)-3.459648919807762457;
    w[11] = (Scalar) 37.20095449534884580;
    w[12] = (Scalar)-39.09786206496502814;
    w[13] = (Scalar) 5.505977727026962754; 
    w[14] = (Scalar) 0.0;

    initialize();
    for (Ordinal n=0; n<NR; ++n) {
      R[n].clone(Omega->getU());
      R[n].zero();
      R[n].set_name("R["+this->asString(n)+"]");
    }
  }

  virtual ~LSRK14() { }

  virtual void advance(Function *);

  virtual void integrate( ScalarFunction<Scalar,Ordinal> *J );

  virtual void adjoint_advance(Function *);

  virtual void interpolate(const Ordinal sstep,
                           const Data &,
                           Data & );

  virtual void interpolate(const Ordinal sstep,
                           const Scalar &,
                           Scalar & );

  virtual Scalar getsubtime( const Ordinal);

private:
  void initialize() { }

};

template< typename Scalar,
          typename Ordinal,
          typename Data,
          typename Function >
void LSRK14< Scalar,Ordinal,Data,Function >::advance(Function *Omega)
{
  if (verb>2)
    std::cout<<"LSRK14::advance() with nsubstep = "<<ti::nsubstep<<std::endl;
  const Scalar dt = Omega->timeStep();
  const Ordinal lstep = Omega->stepNumber();
  Scalar t = Omega->time();
  Data &U = Omega->getU();
  Data &Ut = Omega->getUt();
  Ordinal &substep = ti::substep;
  const Ordinal &nsubstep = ti::nsubstep;
  const Scalar tn = t;
  // Note A[0] = 0, 
  // so Ut is scaled by zero in the first step and we don't need Ut.zero();

  for (substep=0; substep<nsubstep; substep++) {
    t = tn + c[substep]*dt;
    Omega->time(t);
    Omega->prestep(U, lstep-1, substep, t);
    Omega->time_derivative(U, R[0]);          // recall time_derivative is -F
    axpby(-dt, R[0], A[substep], Ut, Ut);     // Ut = A_{s}*Ut - dt*R0
    axpy(B[substep], Ut, U);                  // U = U + B_{s}*Ut
    Omega->poststep(U, lstep-1, substep+1, t);
  }
  t = tn + dt;
  Omega->time(t);
}

template< typename Scalar,
          typename Ordinal,
          typename Data,
          typename Function >
void LSRK14< Scalar,Ordinal,Data,Function >::
integrate( ScalarFunction<Scalar,Ordinal> *J ) {
  const Scalar dt = J->dt;
  const Ordinal &lstep = J->lstep;
  Scalar &t = J->t;
  Ordinal &substep = ti::substep;
  const Ordinal &nsubstep = ti::nsubstep;
  Scalar Jev;
  const Scalar tn = J->t;

  for (substep=0; substep<nsubstep; substep++) {
    t = tn + c[substep]*dt;
    Jev  = J->evaluate( lstep-1, substep );
    J->value += w[substep]*dt*Jev; // J = J + w_{s}*dt*Jev
    if(substep+1 < nsubstep) {
      t = tn + c[substep+1]*dt;
    }
  }
  t = tn + dt;
}

template< typename Scalar,
          typename Ordinal,
          typename Data,
          typename Function >
void LSRK14< Scalar,Ordinal,Data,Function >::
adjoint_advance(Function *Omega)
{
  const Scalar dt = Omega->timeStep();
  const Ordinal lstep = Omega->stepNumber();
  Scalar t = Omega->time();
  Data &U = Omega->getU();
  Data &Ut = Omega->getUt();
  Ordinal &substep = ti::substep;
  const Ordinal &nsubstep = ti::nsubstep;
  const Scalar tn = t - dt;
  // Note A[nsubstep] = 0, which means 
  // Ut is scaled by zero in the first step and we don't need Ut.zero();

  for (substep=nsubstep; substep-- > 0; ) {
    // Scale:   Ut = w_{s+1}*Ut
    // Update:  Ut = A_{s+1}*Ut + B_{s}*U
    // Unscale: Ut = Ut / w_{s}
    axpby(B[substep]/w[substep], U, 
	  A[substep+1]*w[substep+1]/w[substep], Ut, Ut); 
    t = tn + c[substep]*dt;
    Omega->time(t);
    Omega->prestep(Ut, lstep-1, substep, t);
    Omega->time_derivative(Ut, R[0]);     // -f^*(\tilde x_i)
    axpy(w[substep]*dt, R[0], U);         // U = U + w_{s}*dt*R0
    Omega->poststep(U, lstep-1, substep+1, t);
  }
  t = tn;
  Omega->time(t);
}

template< typename Scalar,
          typename Ordinal,
          typename Data,
          typename Function >
void LSRK14< Scalar,Ordinal,Data,Function >::
interpolate(const Ordinal sstep,
            const Data &U_ip1,
            Data &U_i)
{
  scale( 1.0 - c[sstep], U_i );
  axpy( c[sstep], U_ip1, U_i );
}

template< typename Scalar,
          typename Ordinal,
          typename Data,
          typename Function >
void LSRK14< Scalar,Ordinal,Data,Function >::
interpolate(const Ordinal sstep,
            const Scalar &U_ip1,
            Scalar &U_i)
{
  U_i = (1.0 - c[sstep]) * U_i + c[sstep] * U_ip1;
}

template< typename Scalar,
          typename Ordinal,
          typename Data,
          typename Function >
Scalar LSRK14< Scalar,Ordinal,Data,Function >::
getsubtime(const Ordinal sstep)
{
  return c[sstep];
}

} // namespace DTK

#endif  // DTK_TIME_INTEGRATE_HPP
