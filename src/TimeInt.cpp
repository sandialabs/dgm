/** \file TimeInt.cpp
    \brief Time discretization interface class implementation
    \author Scott Collis
*/

// Boost includes
#include "boost/numeric/conversion/cast.hpp"
using boost::numeric_cast;

// Iterative Template Library
#ifdef DGM_USE_ITL
#ifdef DGM_USE_CMC_CBLAS
#ifdef DGM_TIME_INT_CBLAS
#include "itl_cblas.hpp"            // My C-BLAS interface
#else
#include "itl_blas.hpp"             // My FORTRAN BLAS interface
#ifdef DGM_USE_STD_VECTOR
#include "interface_std.h"          // Std vector interface
#else
#include "interface_cmc.h"          // CMC vector and matrix interface
#endif
#endif
#else
#ifdef DGM_TIME_INT_CBLAS
#include "itl/interface/cblas.hpp"  // C-BLAS interface
#else
#include "itl/interface/blas.h"     // Problems with amux at load
#endif
#endif
#include "itl/matrix_free_operator.h"
#include "itl/krylov/gmres.h"
#endif

// DGM includes
#include "TimeInt.hpp"
#include "Domain.hpp"
#include "ObjFunc.hpp"
#include "String.hpp"

namespace DGM {

//=============================================================================
//                            Helper Methods
//=============================================================================

/// Convert from vector storage to vField storage
/** The ordering of this really makes a difference to the solver. */
void TimeInt::convert( const vec &X, vField &F ) const {
  if (F.is_contiguous()) {
    assert( X.size() == numeric_cast<vec::size_type>(F.elmt_data.size()) );
    Ordinal i = 0;
    for (Ordinal q=0; q<F[0]->elmt_data.size(); ++q)
      for (vField::size_type n=0; n<F.size(); ++n)
        F[n]->elmt_data[q] = X[i++];
  } else {
    Ordinal i = 0;
    for (Ordinal e=0; e<F[0]->ne; e++)
      for (Ordinal q=0; q<F[0]->el[e]->qtot; q++)
        for (vField::size_type n=0; n<F.size(); n++, i++)
          F[n]->el[e]->u[q] = X[i];
  }
}

/// Convert from Vector_Field to vector storage
/** The ordering of this really makes a difference to the solver. */
void TimeInt::convert( const vField &F, vec &X ) const {
  if (F.is_contiguous()) {
    assert( X.size() == numeric_cast<vec::size_type>(F.elmt_data.size()) );
    Ordinal i = 0;
    for (Ordinal q=0; q<F[0]->elmt_data.size(); ++q)
      for (vField::size_type n=0; n<F.size(); ++n)
        X[i++] = F[n]->elmt_data[q];
  } else {
    Ordinal i = 0;
    for (Ordinal e=0; e<F[0]->ne; e++)
      for (Ordinal q=0; q<F[0]->el[e]->qtot; q++)
        for (vField::size_type n=0; n<F.size(); n++, i++)
          X[i] = F[n]->el[e]->u[q];
  }
}

//=============================================================================
//                   First-order Forward Euler method
//=============================================================================

/// Constructor
ForwardEuler::ForwardEuler( DGM::Domain *Omega ) : NR(1), 
  R(NR, DGM::vField(Omega->get_comm()))
{
  initialize();
  for (Ordinal nr=0; nr<NR; ++nr) {
    for (vField::size_type i=0; i< Omega->U.size(); ++i)
      R[nr].push_back( new Field( Omega->U[i], Omega->root,
                       Omega->U[i]->name ) );
    R[nr].zero();
    R[nr].set_name("R["+asString(nr)+"]");
  }
}

void ForwardEuler::advance( DGM::Domain *Omega ) {
  const Scalar dt = Omega->dt;
  vField &U = Omega->U;
  Omega->time_derivative( U, R[0] );
  Omega->t += dt;
  scale( -dt, R[0] );
  add( R[0], U );
}

void ForwardEuler::advance( Domain *Omega, ObjFunc *Jp ) {
  const Scalar dt = Omega->dt;
  const Ordinal &lstep = Omega->lstep;
  Scalar &t = Omega->t;
  vField &U = Omega->U;
  ObjFunc &J = *Jp;
  vector<ObjFunc> r(1, J);
  Omega->prestep( U, lstep-1, 0, t );
  r[0]( U, lstep-1, 0 );
  Omega->time_derivative( U, R[0] );
  axpy( dt, r[0], J );
  axpy( -dt, R[0], U);
  t += dt;
  Omega->poststep( U, lstep, 0, t );
}

void ForwardEuler::advance( DGM::Function *J ) {
  const Scalar dt = J->dt;
  const Ordinal &lstep = J->lstep;
  Scalar &t = J->t;
  Scalar r[1];

  r[0] = J->evaluate( lstep-1, 0 );
  t += dt;
  J->value += dt*r[0];
}

void ForwardEuler::adjoint_advance( Domain *Omega ) {
  const Scalar dt = Omega->dt;
  const Ordinal &lstep = Omega->lstep;
  Scalar &t = Omega->t;
  vField &U = Omega->U;

  Omega->prestep(U,lstep-1, 0, t);
  Omega->time_derivative( U, R[0] );
  t -= dt;
  axpy( dt, R[0], U);
  Omega->poststep(U,lstep-1,0,t);
}

// compute the relative local time at a given substep
Scalar ForwardEuler::getsubtime( const Ordinal sstep ) const {
  assert( sstep >= 0 );
  assert( sstep <  nsubstep );
  return 0.0;
}

//=============================================================================
//                   Third-order Multistep method
//=============================================================================

/// Constructor
Multistep::Multistep( DGM::Domain *Omega ) : NR(4), 
  R(NR, DGM::vField(Omega->get_comm()))
{
  initialize();
  for (Ordinal nr=0; nr<NR; ++nr) {
    for (vField::size_type i=0; i< Omega->U.size(); ++i)
      R[nr].push_back( new Field( Omega->U[i], Omega->root,
                                  Omega->U[i]->name ) );
    R[nr].zero();
    R[nr].set_name("R["+asString(nr)+"]");
  }
}

void Multistep::advance( Domain *Omega ) {
  static Scalar beta[][3] = {
    {1.0 ,       0.0    ,  0.0      },
    {3.0/2.0,   -1.0/2.0,  0.0      },
    {23.0/12.0, -4.0/3.0,  5.0/12.0 }};
  Ordinal Order = 3;
  const Scalar dt = Omega->dt;
  const Ordinal &lstep = Omega->lstep;
  Scalar &t = Omega->t;
  vField &U = Omega->U;

  // compute RHS
  t += dt;
  Omega->time_derivative( U, R[0] );

  // three step multistep method
  Ordinal j = (lstep < Order) ? lstep-1: Order-1;

  scale( -beta[j][Order-1]*dt, R[Order-1] );

  for(Ordinal i=0; i<Order-1; ++i)
    axpy( -beta[j][i]*dt, R[i], R[Order-1] );

  add( R[Order-1], U );

  // pointer manipulation (no memory is create/destroyed)
  vField Tmp(R[Order-1]);
  for(Ordinal i=Order-1; i>0; --i) R[i] = R[i-1];
  R[0] = Tmp;
}

//============================================================================
//                     Fourth order Runge Kutta
//============================================================================
const Scalar RungeKutta::a[3] = {0.5, 0.5, 1.0};
const Scalar RungeKutta::b[4] = {0.16666666666666667,  // RK4 coefficients
                                  0.33333333333333333,
                                  0.33333333333333333,
                                  0.16666666666666667};

/// Constructor
RungeKutta::RungeKutta( Domain *Omega ) : NR(2), 
  R(NR, DGM::vField(Omega->get_comm()))
{
  if (Omega->verbosity())
    Omega->get_comm()->cout()<<"Building RungeKutta time integrator"<<endl;
  nsubstep = 4;
  initialize();
  for (Ordinal nr=0; nr<NR; ++nr) {
    for (vField::size_type i=0; i< Omega->U.size(); ++i)
      R[nr].push_back( new Field( Omega->U[i], Omega->root,
                                  Omega->U[i]->name ) );
    R[nr].zero();
    R[nr].set_name("R["+asString(nr)+"]");
  }
  if (Omega->verbosity())
    Omega->get_comm()->cout()<<"Finished RungeKutta time integrator"<<endl;
}

// compute interpolated solution at a substep given step values
void RungeKutta::interpolate( const Ordinal sstep, const vField &U_ip1,
                              vField &U_i ) {
  assert( sstep >= 0 );
  assert( sstep <  nsubstep );
  const Scalar w2 = (sstep==0) ? 0.0 : a[sstep-1];
  const Scalar w1 = 1.0 - w2;
  scale( w1, U_i );
  axpy( w2, U_ip1, U_i );
}

// compute interpolated solution at a substep given step values
void RungeKutta::interpolate( const Ordinal sstep, const Scalar &U_ip1,
                              Scalar &U_i ) {
  assert( sstep >= 0 );
  assert( sstep <  nsubstep );
  const Scalar w2 = (sstep==0) ? 0.0 : a[sstep-1];
  const Scalar w1 = 1.0 - w2;
  U_i = w1 * U_i + w2 * U_ip1;
}

// compute interpolated solution at a substep given step values
Scalar RungeKutta::interpolate( const Scalar U_i,
                                const Scalar U_ip1,
                                const Ordinal sstep ) const {
  assert( sstep >= 0 );
  assert( sstep <  nsubstep );
  const Scalar w2 = (sstep==0) ? 0.0 : a[sstep-1];
  const Scalar w1 = 1.0 - w2;
  const Scalar U = w1 * U_i + w2 * U_ip1;
  return U;
}

void RungeKutta::advance( Domain *Omega ) {
  const Scalar dt = Omega->dt;
  const Ordinal &lstep = Omega->lstep;
  Scalar &t = Omega->t;
  vField &U = Omega->U;
  vField &Ut = Omega->Ut;
                                                // y_1 = x_k
  substep = 0;
  Omega->prestep( U, lstep-1, substep, t );     // u_1
  Omega->time_derivative( U, R[0] );
  axpy( -a[0]*dt, R[0], U, Ut );
  scale(-b[0], R[0] );
  t += 0.5*dt;
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
  Omega->poststep( Ut, lstep-1, substep+1, t ); // y_4

  substep = 3;
  Omega->prestep( Ut, lstep-1, substep, t );    // u_4
  Omega->time_derivative( Ut, R[1] );
  axpy( -b[3], R[1], R[0]);
  axpy( dt, R[0], U);
  Omega->poststep( U, lstep, 0, t );            // x_{k+1}
}

void RungeKutta::advance( Domain *Omega, ObjFunc *Jp ) {
  const Scalar dt = Omega->dt;
  const Ordinal &lstep = Omega->lstep;
  Scalar &t = Omega->t;
  vField &U = Omega->U;
  vField &Ut = Omega->Ut;
  ObjFunc &J = *Jp;
  vector<ObjFunc> r(2, J);

  substep = 0;
  Omega->prestep( U, lstep-1, substep, t );       // u_1
  r[0]( U, lstep-1, substep );
  scale( b[0], r[0] );
  Omega->time_derivative( U, R[0] );
  axpy( -a[0]*dt, R[0], U, Ut );
  scale(-b[0], R[0] );
  t += 0.5*dt;
  Omega->poststep( Ut, lstep-1, substep+1, t );   // y_2

  substep = 1;
  Omega->prestep( Ut, lstep-1, substep, t );      // u_2
  r[1]( Ut, lstep-1, substep );
  axpy( b[1], r[1], r[0] );
  Omega->time_derivative( Ut, R[1] );
  axpy( -a[1]*dt, R[1], U, Ut );
  axpy( -b[1], R[1], R[0]);
  Omega->poststep( Ut, lstep-1, substep+1, t );   // y_3

  substep = 2;
  Omega->prestep( Ut, lstep-1, substep, t );      // u_3
  r[1]( Ut, lstep-1, substep );
  axpy( b[2], r[1], r[0] );
  Omega->time_derivative( Ut, R[1] );
  axpy( -a[2]*dt, R[1], U, Ut );
  axpy( -b[2], R[1], R[0]);
  t += 0.5*dt;
  Omega->poststep( Ut, lstep-1, substep+1, t );   // y_4

  substep = 3;
  Omega->prestep( Ut, lstep-1, substep, t );      // u_4
  r[1]( Ut, lstep-1, substep );
  axpy( b[3], r[1], r[0] );
  axpy( dt, r[0], J );
  Omega->time_derivative( Ut, R[1] );
  axpy( -b[3], R[1], R[0]);
  axpy( dt, R[0], U);
  Omega->poststep( U, lstep, 0, t );              // x_{k+1}
}

void RungeKutta::advance_old( Domain *Omega, ObjFunc *J ) {

#if 1
  throw std::runtime_error("RungeKutta::advance_old() not implemented");
#else 
  const Scalar dt = Omega->dt;
  const Ordinal &lstep = Omega->lstep;
  Scalar &t = Omega->t;
  vField &U = Omega->U;
  vField &Ut = Omega->Ut;

  //Scalar ut;
  Scalar r[2];

#ifndef DGM_USE_TIME_REG
                                                  // y_1 = x_k
  substep = 0;
  Omega->prestep( U, lstep-1, substep, t );       // u_1
  r[0]  = J->evaluate( U, lstep-1, substep );
  //ut  = J->value() + a[0]*dt*r[0];
  r[0] *= b[0];
  Omega->time_derivative( U, R[0] );
  axpy( -a[0]*dt, R[0], U, Ut );
  scale(-b[0], R[0] );
  t += 0.5*dt;
  Omega->poststep( Ut, lstep-1, substep+1, t );   // y_2

  substep = 1;
  Omega->prestep( Ut, lstep-1, substep, t );      // u_2
  r[1]  = J->evaluate( Ut, lstep-1, substep );
  //ut  = J->value() + a[1]*dt*r[1];
  r[0] += b[1]*r[1];
  Omega->time_derivative( Ut, R[1] );
  axpy( -a[1]*dt, R[1], U, Ut );
  axpy( -b[1], R[1], R[0]);
  Omega->poststep( Ut, lstep-1, substep+1, t );   // y_3

  substep = 2;
  Omega->prestep( Ut, lstep-1, substep, t );      // u_3
  r[1]  = J->evaluate( Ut, lstep-1, substep );
  //ut  = J->value() + a[2]*dt*r[1];
  r[0] += b[2]*r[1];
  Omega->time_derivative( Ut, R[1] );
  axpy( -a[2]*dt, R[1], U, Ut );
  axpy( -b[2], R[1], R[0]);
  t += 0.5*dt;
  Omega->poststep( Ut, lstep-1, substep+1, t );   // y_4

  substep = 3;
  Omega->prestep( Ut, lstep-1, substep, t );      // u_4
  r[1]  = J->evaluate( Ut, lstep-1, substep );
  r[0] += b[3]*r[1];
  J->value() += dt*r[0];
  Omega->time_derivative( Ut, R[1] );
  axpy( -b[3], R[1], R[0]);
  axpy( dt, R[0], U);
  Omega->poststep( U, lstep, 0, t );              // x_{k+1}

#else

  substep = 0;
  r[0]  = J->evaluate( U, lstep-1, substep );
  //ut    = J->value() + a[0]*dt*r[0];
  r[0] *= b[0];
  Omega->time_derivative( U, R[0] );
  axpy( -a[0]*dt, R[0], U, Ut );
  scale(-b[0], R[0] );
  t += 0.5*dt;
  Omega->poststep( Ut, lstep-1, substep+1, t );   // y_2

  //control [0,1,2,3]
  //Integrate Control here

  //control[lstep,1] = control[lstep,0]+a[0]*dt*gt_control[lstep,0]
  J->int_control(a[0]*dt,(lstep-1)*nsubstep+substep, (lstep-1)*nsubstep,
                 (lstep-1)*nsubstep+substep+1);
  //control[lstep+1,0] = control[lstep,0]+b[0]*dt*gt_control[lstep,0]
  J->int_control(b[0]*dt,(lstep-1)*nsubstep+substep, (lstep-1)*nsubstep,
                 lstep*nsubstep);

  substep = 1;
  r[1]  = J->evaluate( Ut, lstep-1, substep );
  //ut    = J->value() + a[1]*dt*r[1];
  r[0] += b[1]*r[1];
  Omega->time_derivative( Ut, R[1] );
  axpy( -a[1]*dt, R[1], U, Ut );
  axpy( -b[1], R[1], R[0]);
  Omega->poststep( Ut, lstep-1, substep+1, t ); // y_3

   //control[lstep,2] = control[lstep,0]+a[1]*dt*gt_control[lstep,1]
  J->int_control(a[1]*dt,(lstep-1)*nsubstep+substep, (lstep-1)*nsubstep,
                 (lstep-1)*nsubstep+substep+1);
  //control[lstep+1,0] = control[lstep+1,0]+b[1]*dt*gt_control[0]
  J->int_control(b[1]*dt,(lstep-1)*nsubstep+substep, lstep*nsubstep,
                 lstep*nsubstep);

  substep = 2;
  r[1]  = J->evaluate( Ut, lstep-1, substep );
  //ut    = J->value() + a[2]*dt*r[1];
  r[0] += b[2]*r[1];
  Omega->time_derivative( Ut, R[1] );
  axpy( -a[2]*dt, R[1], U, Ut );
  axpy( -b[2], R[1], R[0]);
  t += 0.5*dt;
  Omega->poststep( Ut, lstep-1, substep+1, t ); // y_4

  // control[lstep,3] = control[lstep,0]+a[2]*dt*gt_control[lstep,2]
  J->int_control(a[2]*dt,(lstep-1)*nsubstep+substep, (lstep-1)*nsubstep,
                 (lstep-1)*nsubstep+substep+1);
  // control[lstep+1,0] = control[lstep+1,0]+b[2]*dt*gt_control[lstep,2]
  J->int_control(b[2]*dt,(lstep-1)*nsubstep+substep, lstep*nsubstep,
                 lstep*nsubstep);

  substep = 3;
  r[1]  = J->evaluate( Ut, lstep-1, substep );
  r[0] += b[3]*r[1];
  J->value() += dt*r[0];
  Omega->time_derivative( Ut, R[1] );
  axpy( -b[3], R[1], R[0]);
  axpy( dt, R[0], U);
  Omega->poststep( U, lstep, 0, t );            // x_{k+1}

  // control[lstep+1,0] = control[lstep+1,0]+b[3]*dt*gt_control[lstep,3]
  J->int_control(b[3]*dt,(lstep-1)*nsubstep+substep, lstep*nsubstep,
                 lstep*nsubstep);

#endif  // DGM_USE_TIME_REG
#endif
}

void RungeKutta::advance( DGM::Function *J ) {
  const Scalar dt = J->dt;
  const Ordinal &lstep = J->lstep;
  Scalar &t = J->t;
  // Scalar ut;
  Scalar r[2];

  substep = 0;
  r[0]  = J->evaluate( lstep-1, substep );
  //ut  = J->value() + a[0]*dt*r[0];
  r[0] *= b[0];
  t += 0.5*dt;

  substep = 1;
  r[1]  = J->evaluate( lstep-1, substep );
  //ut  = J->value + a[1]*dt*r[1];
  r[0] += b[1]*r[1];

  substep = 2;
  r[1]  = J->evaluate( lstep-1, substep );
  //ut  = J->value + a[2]*dt*r[1];
  r[0] += b[2]*r[1];
  t += 0.5*dt;

  substep = 3;
  r[1]  = J->evaluate( lstep-1, substep );
  r[0] += b[3]*r[1];
  J->value += dt*r[0];
}

void RungeKutta::adjoint_advance( Domain *Omega ) {
  const Scalar dt = Omega->dt;
  const Ordinal &lstep = Omega->lstep;
  Scalar &t = Omega->t;
  vField &U = Omega->U;
  vField &Ut = Omega->Ut;
                                                 // \xi_4 = \psi_{k+1}
  substep = 3;
  Omega->prestep(U,lstep-1,substep,t);           // y_4, u_4
  Omega->time_derivative( U, R[0] );
  axpy(  a[0]*dt, R[0], U, Ut ); // Note: a[0] = a[2]*b[3]/b[2]
  scale( b[3], R[0] );
  t -= 0.5*dt;
  Omega->poststep(Ut,lstep-1,substep,t);         // \xi_3

  substep = 2;
  Omega->prestep(Ut,lstep-1,substep,t);          // y_3, u_3
  Omega->time_derivative( Ut, R[1] );
  axpy( a[1]*dt, R[1], U, Ut ); // Note: a[1] = a[1]*b[2]/b[1]
  axpy( b[2], R[1], R[0]);
  Omega->poststep(Ut,lstep-1,substep,t);         // \xi_2

  substep = 1;
  Omega->prestep(Ut,lstep-1,substep,t);          // y_2, u_2
  Omega->time_derivative( Ut, R[1] );
  axpy( a[2]*dt, R[1], U, Ut ); // Note: a[2] = a[0]*b[1]/b[0]
  axpy( b[1], R[1], R[0]);
  t -= 0.5*dt;
  Omega->poststep(Ut,lstep-1,substep,t);         // \xi_1

  substep = 0;
  Omega->prestep(Ut,lstep-1,substep,t);          // y_1, u_1
  Omega->time_derivative( Ut, R[1] );
  axpy( b[0], R[1], R[0]);
  axpy( dt, R[0], U);
  Omega->poststep(U,lstep-1,substep,t);          // \psi_k
}

// To be consistent, I should do gradient integral for STEADY control [gqchen]
void RungeKutta::adjoint_advance( Domain *Omega, ObjFunc *J ) {
  const Scalar dt = Omega->dt;
  const Ordinal &lstep = Omega->lstep;
  Scalar &t = Omega->t;
  vField &U = Omega->U;
  vField &Ut = Omega->Ut;

#ifndef DGM_USE_TIME_REG
                                                 // \xi_4 = \psi_{k+1}
  substep = 3;
  Omega->prestep(U,lstep-1,substep,t);           // y_4, u_4
  Omega->time_derivative( U, R[0] );
  axpy(  a[0]*dt, R[0], U, Ut ); // Note: a[0] = a[2]*b[3]/b[2]
  scale( b[3], R[0] );
  t -= 0.5*dt;
  Omega->poststep(Ut,lstep-1,substep,t);         // \xi_3

  substep = 2;
  Omega->prestep(Ut,lstep-1,substep,t);          // y_3, u_3
  Omega->time_derivative( Ut, R[1] );
  axpy( a[1]*dt, R[1], U, Ut ); // Note: a[1] = a[1]*b[2]/b[1]
  axpy( b[2], R[1], R[0]);
  Omega->poststep(Ut,lstep-1,substep,t);         // \xi_2

  substep = 1;
  Omega->prestep(Ut,lstep-1,substep,t);          // y_2, u_2
  Omega->time_derivative( Ut, R[1] );
  axpy( a[2]*dt, R[1], U, Ut ); // Note: a[2] = a[0]*b[1]/b[0]
  axpy( b[1], R[1], R[0]);
  t -= 0.5*dt;
  Omega->poststep(Ut,lstep-1,substep,t);         // \xi_1

  substep = 0;
  Omega->prestep(Ut,lstep-1,substep,t);          // y_1, u_1
  Omega->time_derivative( Ut, R[1] );
  axpy( b[0], R[1], R[0]);
  axpy( dt, R[0], U);
  Omega->poststep(U,lstep-1,substep,t);          // \psi_k

#else

  substep = 3;

  // get the pre-gradient
  //  Omega->prestep(U,lstep-1,substep+1,t);
  Omega->prestep(U,lstep,0,t);           // y_4, u_4

  // Integrate \phi from pre-gradient
  J->int_slab(-a[0]*dt,(lstep-1),substep+1,0,1);
  J->int_slab(-b[3]*dt,(lstep-1),substep+1,0,3);

  // Update the gradient
  J->grad_update((lstep-1),substep+1,0 );
  //  J->grad_scale((lstep-1),substep+1);

  Omega->time_derivative( U, R[0] );
  axpy(  a[0]*dt, R[0], U, Ut );
  scale( b[3], R[0] );
  t -= 0.5*dt;
  Omega->poststep(Ut,lstep-1,substep,t);         // \xi_3

  substep = 2;
  Omega->prestep(Ut,lstep-1,substep+1,t);          // y_3, u_3

  // Integrate \phi from pre-gradient
  J->int_slab(-a[1]*dt,(lstep-1),substep+1,0,2);
  J->int_slab(-b[2]*dt,(lstep-1),substep+1,3,3);

  // Update the gradient
  J->grad_update((lstep-1),substep+1,1 );
  //  J->grad_scale((lstep-1),substep+1);

  Omega->time_derivative( Ut, R[1] );
  axpy( a[1]*dt, R[1], U, Ut );
  axpy( b[2], R[1], R[0]);
  Omega->poststep(Ut,lstep-1,substep,t);         // \xi_2

  substep = 1;
  Omega->prestep(Ut,lstep-1,substep+1,t);          // y_2, u_2

  // Integrate \phi from pre-gradient
  J->int_slab(-a[2]*dt,(lstep-1),substep+1,0,1);
  J->int_slab(-b[1]*dt,(lstep-1),substep+1,3,3);

  // Update the gradient
  J->grad_update((lstep-1),substep+1,2);
  //  J->grad_scale((lstep-1),substep+1);

  Omega->time_derivative( Ut, R[1] );
  axpy( a[2]*dt, R[1], U, Ut );
  axpy( b[1], R[1], R[0]);
  t -= 0.5*dt;
  Omega->poststep(Ut,lstep-1,substep,t);         // \xi_1

  substep = 0;
  Omega->prestep(Ut,lstep-1,substep+1,t);          // y_1, u_1

  // Integrate \phi from pre-gradient
  J->int_slab(-b[0]*dt,(lstep-1),substep+1,3,0);
  // Update the gradient
  J->grad_update((lstep-1),substep+1,1 );
  //  J->grad_scale((lstep-1),substep+1);

  Omega->time_derivative( Ut, R[1] );
  axpy( b[0], R[1], R[0]);
  axpy( dt, R[0], U);
  Omega->poststep(U,lstep-1,substep,t);          // \psi_k

#endif  // DGM_USE_TIME_REG
}

// compute the relative local time at a given substep
Scalar RungeKutta::getsubtime( const Ordinal sstep ) const {
  assert( sstep >= 0 );
  assert( sstep <  nsubstep );
  return (sstep == 0) ? 0.0 : a[sstep-1];
}

//============================================================================
//                    Jameson Four Stage Runge Kutta
//============================================================================

/// Constructor
/** See AIAA-91-1596 for details.  Note that this method splits convective and
    diffusion terms and treats them differently so that the interface requires
    some change.  Note that Jameson is really only defined to work in
    pseudo-time which is why the physical time is not updated.   */
Jameson::Jameson( Domain *Omega ) : NR(4), 
  R(NR, DGM::vField(Omega->get_comm()))
{
  Omega->get_comm()->cout()
    << "WARNING:  Jameson method is under development..." << endl;;
  nsubstep = 4;
  initialize();
  for (Ordinal nr=0; nr<NR; ++nr) {
    for (vField::size_type i=0; i< Omega->U.size(); ++i)
      R[nr].push_back( new Field( Omega->U[i], Omega->root,
                                  Omega->U[i]->name ) );
    R[nr].zero();
    R[nr].set_name("R["+asString(nr)+"]");
  }
}

// Currently have assumed that only convection is active.  No current evidence
// that the method as coded works.  I suspect that this is because I haven't
// yet split the convective and diffusive parts and trying to treat the
// combined method with just the convective method doesn't really work that
// well.
void Jameson::advance( Domain *Omega ) {
  // Convection coefficients
  static const Scalar a[4] = {1.0/3.0, 4.0/15.0, 5.0/9.0, 1.0};
  // Diffusion coefficients
  // static const Scalar b[4] = {1.0, 1.0/12.0, 0.0, 0.0};

  const Scalar dt = Omega->dt;
  //Scalar &t = Omega->t;
  vField &U = Omega->U;
  vField &Ut = Omega->Ut;

  Omega->time_derivative( U, R[0] );
  axpy( -a[0]*dt, R[0], U, Ut );

  Omega->time_derivative( Ut, R[0] );
  axpy( -a[1]*dt, R[0], U, Ut );

  Omega->time_derivative( Ut, R[0] );
  axpy( -a[2]*dt, R[0], U, Ut );

  Omega->time_derivative( Ut, R[0] );
  axpy( -a[3]*dt, R[0], U );
}

//============================================================================
//          Third-order Total Variational Dimenishing Runge Kutta
//============================================================================

/// Constructor
/** Butcher Tableau:
    \verbatim
    0   | 0
    1   | 1     0
    1/2 | 1/4 1/4  0
    -----------------
        | 1/6 1/6 2/3
    \endverbatim
*/
const Scalar TVD::a[3] = {    0.0, 3.0/4.0, 1.0/3.0};
const Scalar TVD::b[3] = {    1.0, 1.0/4.0, 2.0/3.0};
const Scalar TVD::c[3] = {    0.0,     1.0, 1.0/2.0};
const Scalar TVD::w[3] = {1.0/6.0, 1.0/6.0, 2.0/3.0};

TVD::TVD( Domain *Omega ) : NR(1), R(NR, DGM::vField(Omega->get_comm())) {
  if (Omega->verbosity())
    Omega->get_comm()->cout()<<"Building TVD time integrator"<<endl;
  nsubstep = 3;
  initialize();
  for (Ordinal nr=0; nr<NR; ++nr) {
    for (vField::size_type i=0; i< Omega->U.size(); ++i)
      R[nr].push_back( new Field( Omega->U[i], Omega->root,
                                  Omega->U[i]->name ) );
    R[nr].zero();
    R[nr].set_name("R["+asString(nr)+"]");
  }
  if (Omega->verbosity())
    Omega->get_comm()->cout()<<"Finished building TVD time integrator"<<endl;
}

// compute interpolated solution at a substep given step values
void TVD::interpolate( const Ordinal sstep, const vField &U_ip1,
                              vField &U_i ) {
  assert( sstep >= 0 );
  assert( sstep <  nsubstep );
  const Scalar w2 = c[sstep];
  const Scalar w1 = 1.0 - w2;
  scale( w1, U_i );
  axpy( w2, U_ip1, U_i );
}

// compute interpolated solution at a substep given step values
void TVD::interpolate( const Ordinal sstep, const Scalar &U_ip1,
                              Scalar &U_i ) {
  assert( sstep >= 0 );
  assert( sstep <  nsubstep );
  const Scalar w2 = c[sstep];
  const Scalar w1 = 1.0 - w2;
  U_i = w1 * U_i + w2 * U_ip1;
}

// compute interpolated solution at a substep given step values
Scalar TVD::interpolate( const Scalar U_i,
                                const Scalar U_ip1,
                                const Ordinal sstep ) const {
  assert( sstep >= 0 );
  assert( sstep <  nsubstep );
  const Scalar w2 = c[sstep];
  const Scalar w1 = 1.0 - w2;
  const Scalar U = w1 * U_i + w2 * U_ip1;
  return U;
}

// HACK to try out local time stepping...
#ifdef DGM_LOCAL_TIME_STEPPING

/** \warning Is this advancing time correctly?. */
void TVD::advance( Domain *Omega ) {
  const Scalar dt = Omega->dt;
  Scalar &t = Omega->t;
  vField &U = Omega->U;
  vField &Ut = Omega->Ut;
  dVector tmp(Omega->dtl.size());

  // substep = 0;
  Omega->time_derivative( U, R[0] ); // R0 = -f(Un)
  tmp = Omega->dtl;
  axpy( -tmp, R[0], U, Ut );         // Ut = U - dt*R0
  // scale( b[0], Ut );              // Can omit since b[0] = 1.0

  // substep = 1;
  t += dt;
  Omega->time_derivative( Ut, R[0] ); // R0 = -f(Ut)
  tmp = Omega->dtl;
  axpy( -tmp, R[0], Ut, R[0] );       // R0 = Ut - dt*R0
  axpby( a[1], U, b[1], R[0], Ut);    // Ut = a1*Un + b1*R0

  // substep = 2;
  t -= 0.5*dt;
  Omega->time_derivative( Ut, R[0] ); // R0 = -f(Ut)
  tmp = Omega->dtl;
  axpy( -tmp, R[0], Ut, R[0] );       // R0 = Ut - dt*R0
  axpby( b[substep], R[0], a[substep], U, U); // Un1 = a2*Un + b2*R0
}

#else

void TVD::advance( Domain *Omega ) {
  const Scalar dt = Omega->dt;
  const Scalar tn = Omega->t;
  const Ordinal &lstep = Omega->lstep;
  Scalar &t = Omega->t;
  vField &U = Omega->U;
  vField &Ut = Omega->Ut;

  substep = 0;
  t = tn + c[substep]*dt;
  Omega->prestep( U, lstep-1, substep, t );
  Omega->time_derivative( U, R[0] ); // R0 = -f(Un)
  axpy( -dt, R[0], U, Ut );          // Ut = U - dt*R0
  // scale( b[0], Ut );              // Can omit since b[0] = 1.0
  t = tn + c[substep+1]*dt;
  Omega->poststep( Ut, lstep-1, substep+1, t );

  substep = 1;
  Omega->prestep( Ut, lstep-1, substep, t );
  Omega->time_derivative( Ut, R[0] ); // R0 = -f(Ut)
  axpy( -dt, R[0], Ut, R[0] );        // R0 = Ut - dt*R0
  axpby( a[substep], U, b[substep], R[0], Ut); // Ut = a1*Un + b1*R0
  t = tn + c[substep+1]*dt;
  Omega->poststep( Ut, lstep-1, substep+1, t );

  substep = 2;
  Omega->prestep( Ut, lstep-1, substep, t );
  Omega->time_derivative( Ut, R[0] ); // R0 = -f(Ut)
  axpy( -dt, R[0], Ut, R[0] );        // R0 = Ut - dt*R0
  axpby( b[substep], R[0], a[substep], U, U); // Un1 = a2*Un + b2*R0
  t = tn + dt;
  Omega->poststep( U, lstep, 0, t );
}

#endif  // DGM_LOCAL_TIME_STEPPING

void TVD::advance( Domain *Omega, ObjFunc *Jp ) {
  const Scalar dt = Omega->dt;
  const Scalar tn = Omega->t;
  const Ordinal &lstep = Omega->lstep;
  Scalar &t = Omega->t;
  vField &U = Omega->U;
  vField &Ut = Omega->Ut;
  ObjFunc &J = *Jp;
  vector<ObjFunc> r(1, J);

  substep = 0;
  t = tn + c[substep]*dt;
  Omega->prestep( U, lstep-1, substep, t );
  Omega->time_derivative( U, R[0] ); // R0 = -f(Un)
  r[0]( U, lstep-1, substep );
  axpy( -b[substep]*dt, R[0], U, Ut );      // Ut = U - dt*b0*R0
  axpy(  w[substep]*dt, r[0], J);           // J = J + w0*dt*Jev
  t = tn + c[substep+1]*dt;
  Omega->poststep( Ut, lstep-1, substep+1, t );

  substep = 1;
  Omega->prestep( Ut, lstep-1, substep, t );
  Omega->time_derivative( Ut, R[0] ); // R0 = -f(Ut)
  r[0]( Ut, lstep-1, substep );
  axpby(a[substep], U, b[substep], Ut, Ut); // Ut = a1*Un + b1*Ut 
  axpy( -b[substep]*dt, R[0] , Ut );        // Ut = Ut - dt*b1*R0
  axpy(  w[substep]*dt, r[0], J);           // J = J + w1*dt*Jev
  t = tn + c[substep+1]*dt;
  Omega->poststep( Ut, lstep-1, substep+1, t );

  substep = 2;
  Omega->prestep( Ut, lstep-1, substep, t );
  Omega->time_derivative( Ut, R[0] ); // R0 = -f(Ut)
  r[0]( Ut, lstep-1, substep );
  axpby( b[substep], Ut, a[substep], U, U); // Un1 = a2*Un + b2*Ut
  axpy( -b[substep]*dt, R[0],  U );         // Un1 = Un1 - dt*b2*R0
  axpy(  w[substep]*dt, r[0], J);           // J = J + w2*dt*Jev
  t = tn + dt;
  Omega->poststep( U, lstep, 0, t );
}

void TVD::advance( DGM::Function *J ) {
  const Scalar dt = J->dt;
  const Scalar tn = J->t;
  const Ordinal &lstep = J->lstep;
  Scalar &t = J->t;
  Scalar Jev;

  substep = 0;
  Jev  = J->evaluate( lstep-1, substep );
  J->value += w[substep]*dt*Jev; // J = J + w0*dt*Jev
  t = tn + c[substep+1]*dt;

  substep = 1;
  Jev  = J->evaluate( lstep-1, substep );
  J->value += w[substep]*dt*Jev; // J = J + w1*dt*Jev
  t = tn + c[substep+1]*dt;

  substep = 2;
  Jev  = J->evaluate( lstep-1, substep );
  J->value += w[substep]*dt*Jev; // J = J + w2*dt*Jev
  t = tn + dt;
}

void TVD::adjoint_advance( Domain *Omega ) {
  const Scalar dt = Omega->dt;
  const Ordinal &lstep = Omega->lstep;
  Scalar &t = Omega->t;
  vField &U = Omega->U;
  vField &Ut = Omega->Ut;
  const Scalar tn = Omega->t - dt;

  substep = 2;
  t = tn + c[substep]*dt;
  Omega->prestep(U, lstep-1, substep, t);
  Omega->time_derivative(U, R[0]);
  axpby(dt*b[substep], R[0], b[substep], U, Ut);  // Ut = b2*U + dt*b2*R0
  axpby( a[substep-1], Ut, a[substep], U, U);     // U  = a2*U + a1*Ut
  t = tn + c[substep-1]*dt;
  Omega->poststep(Ut, lstep-1, substep, t);

  substep = 1;
  scale(b[substep]/w[substep], Ut);               // Ut = b1*Ut/w1
  Omega->prestep(Ut, lstep-1, substep, t);
  Omega->time_derivative(Ut, R[0]);
  axpby(dt*w[substep], R[0], w[substep], Ut, Ut); // Ut = w1*Ut + dt*w1*R0
  t = tn + c[substep-1]*dt;
  Omega->poststep(Ut, lstep-1, substep, t);

  substep = 0;
  scale(b[substep]/w[substep], Ut);               // Ut = b0*Ut/w0
  Omega->prestep(Ut, lstep-1, substep, t);
  Omega->time_derivative(Ut, R[0]);
  axpby(dt*w[substep], R[0], w[substep], Ut, Ut); // Ut = w0*Ut + dt*w0*R0
  axpy(b[substep], Ut, U);                        // U = U + b0*Ut
  t = tn;
  Omega->poststep(U, lstep-1, substep, t);
}

// compute the relative local time at a given substep
Scalar TVD::getsubtime( const Ordinal sstep ) const {
  assert( sstep >= 0 );
  assert( sstep <  nsubstep );
  return c[sstep];
}

//============================================================================
//                  Strong Stability-Preserving Runge-Kutta
//============================================================================

const Scalar SSPRK::a[][5] = {
    {      1.0,     0.0,     0.0,      0.0,       0.0 },
    {  1.0/2.0, 1.0/2.0,     0.0,      0.0,       0.0 },
    {  1.0/3.0, 1.0/2.0, 1.0/6.0,      0.0,       0.0 },
    {  3.0/8.0, 1.0/3.0, 1.0/4.0, 1.0/24.0,       0.0 },
    {11.0/30.0, 3.0/8.0, 1.0/6.0, 1.0/12.0, 1.0/120.0 }};

/// Constructor
SSPRK::SSPRK( Domain *Omega ) : NR(1), 
  R(NR, DGM::vField(Omega->get_comm()))
{
  if (Omega->verbosity())
    Omega->get_comm()->cout()<<"Building SSPRK time integrator"<<endl;
  initialize();
  string root(Omega->params["root"]);

  // default is third order
  m = 3;
  params["m"] = m;
  Omega->get_comm()->cout()
    << "SSPRK: reading parameters from " << root+".int" <<endl;
  params.read( root+".int" );
  m = params["m"];
  nsubstep = m;

  // sanity check
  if (m < 1 || m > 5) {
    Omega->get_comm()->error("SSPRK::invalid number of stages, m = "
                             +asString(m));
  }

  // setup registers
  Omega->get_comm()->cout()
    << "SSPRK::SSPRK(...) setting up for " << m << " stages." << endl;

  for (vField::size_type i=0; i< Omega->U.size(); ++i)
    R[0].push_back( new Field( Omega->U[i], Omega->root,
                                  Omega->U[i]->name ) );
  R[0].zero();
  R[0].set_name("R[0]");

  if (Omega->verbosity())
    Omega->get_comm()->cout()<<"Finished building SSPRK time integrator"<<endl;
}

// compute interpolated solution at a substep given step values
void SSPRK::interpolate( const Ordinal sstep, const vField &U_ip1,
                              vField &U_i ) {
  assert( sstep >= 0 );
  assert( sstep <  nsubstep );
  const Scalar w2 = (Scalar) sstep;
  const Scalar w1 = 1.0 - w2;
  scale( w1, U_i );
  axpy( w2, U_ip1, U_i );
}

// compute interpolated solution at a substep given step values
void SSPRK::interpolate( const Ordinal sstep, const Scalar &U_ip1,
                              Scalar &U_i ) {
  assert( sstep >= 0 );
  assert( sstep <  nsubstep );
  const Scalar w2 = (Scalar) sstep;
  const Scalar w1 = 1.0 - w2;
  U_i = w1 * U_i + w2 * U_ip1;
}

// compute interpolated solution at a substep given step values
Scalar SSPRK::interpolate( const Scalar U_i,
                                const Scalar U_ip1,
                                const Ordinal sstep ) const {
  assert( sstep >= 0 );
  assert( sstep <  nsubstep );
  const Scalar w2 = (Scalar) sstep;
  const Scalar w1 = 1.0 - w2;
  const Scalar U = w1 * U_i + w2 * U_ip1;
  return U;
}

void SSPRK::advance( Domain *Omega ) {
  Ordinal i;
  const Scalar dt = Omega->dt;
  const Scalar tn = Omega->t;
  const Ordinal &lstep = Omega->lstep;
  Scalar &t = Omega->t;
  vField &U = Omega->U;
  vField &Ut = Omega->Ut;

  if( m == 1 ) {
    /* This is the same as Forward Euler */
    Omega->prestep( U, lstep-1, 0, t );
    Omega->time_derivative( U, R[0] );
    t += dt;
    axpy( -dt, R[0], U);
    Omega->poststep( U, lstep, 0, t );

  } else {
    substep = 0;
    Omega->prestep( U, lstep-1, substep, t );
    Omega->time_derivative( U, R[0] );
    axpy( -dt, R[0], U, Ut );
    scale( a[m-1][0], U );

    t += dt;
    Omega->poststep( Ut, lstep-1, substep+1, t );

    // substep = 1, .., m-2
    for (i=2; i<m; i++) {
      substep = substep + 1;
      Omega->prestep( Ut, lstep-1, substep, t );
      Omega->time_derivative( Ut, R[0] );
      axpy( a[m-1][i-1], Ut, U );
      t += dt;
      axpy( -dt, R[0], Ut );
      Omega->poststep( Ut, lstep-1, substep+1, t );
    }

    // substep = m-1
    i = m;
    substep = substep + 1;
    Omega->prestep( Ut, lstep-1, substep, t );
    Omega->time_derivative( Ut, R[0] );
    axpy( -dt, R[0], Ut );
    axpy( a[m-1][i-1], Ut, U );

    t = tn + dt;
    Omega->poststep( U, lstep, 0, t );
  }
}

void SSPRK::advance( Domain *Omega, ObjFunc *Jp ) {
  Ordinal i;
  const Scalar dt = Omega->dt;
  const Scalar tn = Omega->t;
  const Ordinal &lstep = Omega->lstep;
  Scalar &t = Omega->t;
  vField &U = Omega->U;
  vField &Ut = Omega->Ut;

  ObjFunc &J = *Jp;
  vector<ObjFunc> r(1, J);

  if( m == 1 ) {
    /* This is the same as Forward Euler */
    Omega->prestep( U, lstep-1, 0, t );
    r[0]( U, lstep-1, 0 );
    Omega->time_derivative( U, R[0] );
    axpy( dt, r[0], J );
    axpy( -dt, R[0], U);
    t += dt;
    Omega->poststep( U, lstep, 0, t );

  } else {
    substep = 0;
    Omega->prestep( U, lstep-1, substep, t );
    Omega->time_derivative( U, R[0] );
    r[0](U, lstep-1, substep);
    axpy( dt*a[m-1][0], r[0], J);
    axpy( -dt, R[0], U, Ut );
    scale( a[m-1][0], U );

    t += dt;
    Omega->poststep( Ut, lstep-1, substep+1, t );

    // substep = 1, ..., m-2
    for (i=2; i<m; i++) {
      substep = substep + 1;
      Omega->prestep( Ut, lstep-1, substep, t );
      Omega->time_derivative( Ut, R[0] );
      r[0](Ut, lstep-1, substep);
      axpy( dt*a[m-1][i-1], r[0], J);
      axpy( a[m-1][i-1], Ut, U );
      t += dt;
      axpy( -dt, R[0], Ut );
      Omega->poststep( Ut, lstep-1, substep+1, t );
    }

    // substep = m-1
    i = m;
    substep = substep + 1;
    Omega->prestep( Ut, lstep-1, substep, t );
    Omega->time_derivative( Ut, R[0] );
    r[0](Ut, lstep-1, substep);
    axpy( dt*a[m-1][i-1], r[0], J);
    axpy( -dt, R[0], Ut );
    axpy( a[m-1][m-1], Ut, U );

    t = tn + dt;
    Omega->poststep( U, lstep, 0, t );
  }
}

void SSPRK::advance( DGM::Function *J ) {
  Ordinal i;
  const Scalar dt = J->dt;
  const Scalar tn = J->t;
  const Ordinal &lstep = J->lstep;
  Scalar &t = J->t;
  Scalar Jev;

  if( m == 1 ) {
    /* This is the same as Forward Euler */
    Jev = J->evaluate( lstep-1, 0 );
    J->value += dt*Jev;
    t += dt;

  } else {
    substep = 0;
    Jev = J->evaluate(lstep-1, substep);
    J->value += dt*a[m-1][0]*Jev; 
    t += dt;

    // substep = 1, ..., m-2
    for (i=2; i<m; i++) {
      substep = substep + 1;
      Jev  = J->evaluate( lstep-1, substep );
      J->value += dt*a[m-1][i-1]*Jev; 
      t += dt;
    }

    // substep = m-1
    i = m;
    substep = substep + 1;
    Jev  = J->evaluate( lstep-1, substep );
    J->value += dt*a[m-1][m-1]*Jev; 

    t = tn + dt;
  }
}

void SSPRK::adjoint_advance( Domain *Omega ) {
  const Scalar dt = Omega->dt;
  const Ordinal &lstep = Omega->lstep;
  Ordinal i;
  Scalar &t = Omega->t;
  vField &U = Omega->U;
  vField &Ut = Omega->Ut;
  const Scalar tn = Omega->t - dt;

  if( m == 1 ) {
    /* This is the same as Forward Euler */
    Omega->prestep(U,lstep-1, 0, t);
    Omega->time_derivative( U, R[0] );
    t -= dt;
    axpy( dt, R[0], U);
    Omega->poststep(U,lstep-1,0,t);

  } else {
    t = tn + (m-1)*dt;

    substep = m - 1;
    Omega->prestep(U, lstep-1, substep, t);
    Omega->time_derivative(U, R[0]);
    // Ut = a_{m-1}*U + a_{m-1}*dt*R0
    axpby(dt*a[m-1][m-1], R[0], a[m-1][m-1], U, Ut); 
    Omega->poststep(Ut, lstep-1, substep, t);

    // substep = m-2, ..., 0  
    for (i=(m-2); i>=0 && i>m; i--) {
      substep = i;
      t = t - dt;

      scale(1./a[m-1][i], Ut);
      Omega->prestep(Ut, lstep-1, substep, t);
      Omega->time_derivative(Ut, R[0]);
      // Ut = a_i * Ut + a_i*U
      axpby(a[m-1][i], U, a[m-1][i], Ut, Ut);
      if(i > 0) {
	axpy(dt*a[m-1][i], R[0], Ut);
	Omega->poststep(Ut, lstep-1, substep, t);
      } else {
	axpy(dt*a[m-1][i], R[0], Ut, U);
      }
    }
    t = tn;
    Omega->poststep(U, lstep-1, substep, t);
  }
}

// compute the relative local time at a given substep
Scalar SSPRK::getsubtime( const Ordinal sstep ) const {
  assert( sstep >= 0 );
  assert( sstep <  nsubstep );
  return (Scalar) sstep;
}

#ifdef DGM_USE_ITL

//============================================================================
//                     First-order implicit Euler
//============================================================================

/// Constructor
BackwardEuler::BackwardEuler( Domain *Omega, string ext ) : NR(1),
  R(NR, DGM::vField(Omega->get_comm())) {
  initialize();
  for (Ordinal nr=0; nr<NR; ++nr) {
    for (Ordinal i=0; i< Omega->U.size(); ++i)
      R[nr].push_back( new Field( Omega->U[i], Omega->root,
                                  Omega->U[i]->name ) );
    R[nr].zero();
    R[nr].set_name("R["+asString(nr)+"]");
  }

  if (Omega->get_comm()->NumProc() != 1) {
    Omega->get_comm()->cerr()<<"BackwardEuler does not support parallel"
                           <<endl;
    Omega->get_comm()->exit(DGM::FAILURE);
  }

  string root(Omega->params["root"]);
  ntout = Omega->params["ntout"];

  string fname=root+ext+".out";
  out = new ofstream(fname.c_str());

  // These default settings are more appropriate for steady state solutions
  newton_max_iter = 2;
  newton_rtol = 1.0e-3;
  newton_atol = 1.0e-19;
  newton_stol = 1.0e-19;

  gmres_max_iter = 20;
  gmres_restart = 20;
  gmres_rtol = newton_rtol/10;
  gmres_atol = 1.0e-19;

  fd_step_size = 0.0;  // default to ITL value

  params["newton_max_iter"] = newton_max_iter;
  params["newton_rtol"] = newton_rtol;
  params["newton_atol"] = newton_atol;
  params["newton_stol"] = newton_stol;

  params["gmres_max_iter"] = gmres_max_iter;
  params["gmres_restart"] = gmres_restart;
  params["gmres_rtol"] = gmres_rtol;
  params["gmres_atol"] = gmres_atol;

  params["fd_step_size"] = fd_step_size;

  Omega->get_comm()->cout()
    << "BackwardEuler: reading parameters from " << root+ext+".imp" <<endl;
  params.read( root+ext+".imp" );

  newton_max_iter = params["newton_max_iter"];
  newton_rtol = params["newton_rtol"];
  newton_atol = params["newton_atol"];
  newton_stol = params["newton_stol"];

  gmres_max_iter = params["gmres_max_iter"];
  gmres_restart = params["gmres_restart"];
  gmres_rtol = params["gmres_rtol"];
  gmres_atol = params["gmres_atol"];

  fd_step_size = params["fd_step_size"];

  Omega->get_comm()->cout()
    << "newton_rtol = " << newton_rtol << ", gmres_rtol = "
    << gmres_rtol << ", fd_step_size = " ;
  if (fd_step_size==0)
    Omega->get_comm()->cout() << "default" << endl;
  else
    Omega->get_comm()->cout() << fd_step_size << endl;
}

void BackwardEuler::residual( Domain *Omega, const vec &X, vec &Y ) {
  // cout << "BackwardEuler::residual( Domain *Omega )" << endl;
  const Scalar dt = Omega->dt;
  vField &U  = Omega->U;
  vField &Ut = Omega->Ut;
  convert( X, U );
  Omega->time_derivative( U, R[0] );
  //R[0].norm();
  scale( dt, R[0] );
  axpy( -1.0, Ut, R[0] );
  add( U, R[0]);
  convert( R[0], Y );
}

void BackwardEuler::adjoint_residual( Domain *Omega, const vec &X, vec &Y ) {
  // cout << "BackwardEuler::adjoint_residual( Domain *Omega )" << endl;
  const Scalar dt = Omega->dt;
  vField &U  = Omega->U;
  vField &Ut = Omega->Ut;
  convert( X, U );
  Omega->time_derivative( U, R[0] );
  scale( dt, R[0] );
  axpy( -1.0, U, R[0] );
  add( Ut, R[0]);
  convert( R[0], Y );
}

void BackwardEuler::advance( Domain *Omega ) {
  const Scalar dt = Omega->dt;
  const Ordinal &lstep = Omega->lstep;
  Scalar &t = Omega->t;
  vField &U = Omega->U;
  vField &Ut = Omega->Ut;

  Omega->prestep( U, lstep, 0, t );

  // save prior solution
  copy( U, Ut);

  // set initial condition
  Ordinal N = U.qtot();
  vec x( N );
  convert( U, x );
  vec F( N, 0.0 );

  Evaluator r(Omega,this);   // make residual evaluator function
  t += dt;
  r( x, F );                 // evaluate initial residual

  Scalar norm0 = itl::two_norm(F);
  Scalar two_norm_F = norm0, old_two_norm_F = 0.0;
  *out << "Initial |F| = " << two_norm_F << endl;

  // setup Iterative Template Library (ITL)
#ifdef ITL_FD_STEP_SIZE
  itl::matrix_free_operator< vec, Evaluator > A( r, x, F, fd_step_size );
#else
  itl::matrix_free_operator< vec, Evaluator > A( r, x, F );
#endif
  itl::modified_gram_schmidt< vec > krylov( gmres_restart, x.size() );
  itl::identity_preconditioner p;

  // Newton iteration
  for (Ordinal newton_iter=1; newton_iter<=newton_max_iter; ++newton_iter) {
    vec dx( N, 0.0 );
    itl::basic_iteration<Scalar> gmres_iter( F, gmres_max_iter,
                                             gmres_rtol, gmres_atol);
    Ordinal stat=itl::gmres(A, dx, F, p, gmres_restart, gmres_iter, krylov);
    if (stat!=0) *out << "GMRES error code " << stat << endl;
    itl::add( itl::scaled(dx, -1.0), x );

    r( x, F );
    old_two_norm_F = two_norm_F;
    two_norm_F     = itl::two_norm(F);

    *out << "Number of iteration used in GMRES: " << gmres_iter.iterations()
         << " Residual: " << gmres_iter.resid()
         << " normb: " << gmres_iter.normb()
         << endl;
    *out << "Newton iteration " << newton_iter << ", |F| = "
         << two_norm_F << endl;

    if ( two_norm_F < newton_rtol * norm0
         || std::abs( old_two_norm_F - two_norm_F ) < newton_stol
         || two_norm_F < newton_atol )
      break;
  }
  Omega->poststep( U, lstep, 0, t );
}

void BackwardEuler::advance( Domain *Omega, ObjFunc *J ) {
  const Scalar dt = Omega->dt;
  const Ordinal &lstep = Omega->lstep;
  //Scalar &t = Omega->t;
  vField &U = Omega->U;
  //vField &Ut = Omega->Ut;
  advance( Omega );
  J->value() += dt * J->evaluate( U, lstep, 0 );
}

void BackwardEuler::advance( DGM::Function *J ) {
  const Scalar dt = J->dt;
  const Ordinal &lstep = J->lstep;
  //Scalar &t = J->t;
  J->value() += dt * J->evaluate( lstep, 0 );
}

void BackwardEuler::adjoint_advance( Domain *Omega ) {
  const Scalar dt = Omega->dt;
  const Ordinal &lstep = Omega->lstep;
  Scalar &t = Omega->t;
  vField &U = Omega->U;
  vField &Ut = Omega->Ut;

  Omega->prestep( U, lstep, 0, t);

  // save prior solution
  copy( U, Ut);

  // set initial condition
  Ordinal N = U.qtot();
  vec x( N );
  convert( U, x );
  vec F( N, 0.0 );

  AdjointEvaluator r(Omega,this);  // make residual evaluator function
  t -= dt;
  r( x, F );                       // evaluate initial residual

  Scalar norm0 = itl::two_norm(F);
  Scalar two_norm_F = norm0, old_two_norm_F = 0.0;
  *out << "Initial |F| = " << two_norm_F << endl;

  // setup Iterative Template Library (ITL)
  itl::matrix_free_operator< vec, AdjointEvaluator > A( r, x, F );
  itl::modified_gram_schmidt< vec > krylov( gmres_restart, x.size() );
  //itl::identity_preconditioner p;

  // Newton iteration
  for (Ordinal newton_iter=1; newton_iter<=newton_max_iter; ++newton_iter) {

    vec dx( N, 0.0 );

    itl::basic_iteration<Scalar> gmres_iter( F, gmres_max_iter,
                                             gmres_rtol, gmres_atol);
    //Ordinal stat=itl::gmres(A, dx, F, p, gmres_restart, gmres_iter, krylov);
    //if (stat!=0) *out << "GMRES error code " << stat << endl;
    itl::add( itl::scaled(dx, -1.0), x );

    r( x, F );
    old_two_norm_F = two_norm_F;
    two_norm_F     = itl::two_norm(F);

    *out << "Number of iteration used in GMRES: " << gmres_iter.iterations()
         << " Residual: " << gmres_iter.resid()
         << " normb: " << gmres_iter.normb()
         << endl;
    *out << "Newton iteration " << newton_iter << ", |F| = "
         << two_norm_F << endl;

    if ( two_norm_F < newton_rtol * norm0
         || std::abs( old_two_norm_F - two_norm_F ) < newton_stol
         || two_norm_F < newton_atol )
      break;
  }

  Omega->poststep( U, lstep, 0, t );
}

// compute the relative local time at a given substep
Scalar BackwardEuler::getsubtime( const Ordinal sstep ) const {
  assert( sstep >= 0 );
  assert( sstep <  nsubstep );
  return 1.0;
}

//============================================================================
//                        Second order Trapezoidal
//============================================================================

/// Constructor
Trapezoidal::Trapezoidal( Domain *Omega, string ext ) : NR(2),
  R(NR, DGM::vField(Omega->get_comm())) {
  initialize();
  for (Ordinal nr=0; nr<NR; ++nr) {
    for (Ordinal i=0; i< Omega->U.size(); ++i)
      R[nr].push_back( new Field( Omega->U[i], Omega->root,
                                  Omega->U[i]->name ) );
    R[nr].zero();
    R[nr].set_name("R["+asString(nr)+"]");
  }

  if (Omega->get_comm()->NumProc() != 1) {
    Omega->get_comm()->cerr()<<"Trapezoidal does not support parallel"
                           <<endl;
    Omega->get_comm()->exit(DGM::FAILURE);
  }

  string root(Omega->params["root"]);
  ntout = Omega->params["ntout"];

  string fname=root+ext+".out";
  out = new ofstream(fname.c_str());

  // These default settings are more appropriate for unsteady solutions
  newton_max_iter = 10;
  newton_rtol = 1.0e-3;
  newton_atol = 1.0e-19;
  newton_stol = 1.0e-19;

  gmres_max_iter = 30;
  gmres_restart = 30;
  gmres_rtol = newton_rtol/5;
  gmres_atol = 1.0e-19;

  params["newton_max_iter"] = newton_max_iter;
  params["newton_rtol"] = newton_rtol;
  params["newton_atol"] = newton_atol;
  params["newton_stol"] = newton_stol;

  params["gmres_max_iter"] = gmres_max_iter;
  params["gmres_restart"] = gmres_restart;
  params["gmres_rtol"] = gmres_rtol;
  params["gmres_atol"] = gmres_atol;

  params["fd_step_size"] = fd_step_size;

  Omega->get_comm()->cout()
    << "Trapezoid: reading parameters from " << root+ext+".imp" <<endl;
  params.read( root+".imp" );

  newton_max_iter = params["newton_max_iter"];
  newton_rtol = params["newton_rtol"];
  newton_atol = params["newton_atol"];
  newton_stol = params["newton_stol"];

  gmres_max_iter = params["gmres_max_iter"];
  gmres_restart = params["gmres_restart"];
  gmres_rtol = params["gmres_rtol"];
  gmres_atol = params["gmres_atol"];

  fd_step_size = params["fd_step_size"];

  Omega->get_comm()->cout()
    << "newton_rtol = " << newton_rtol << ", gmres_rtol = "
    << gmres_rtol << ", fd_step_size = " ;
  if (fd_step_size==0)
    Omega->get_comm()->cout() << "default" << endl;
  else
    Omega->get_comm()->cout() << fd_step_size << endl;
}

void Trapezoidal::residual( Domain *Omega, const vec &X, vec &Y ) {
  const Scalar dt = Omega->dt;
  vField &U  = Omega->U;
  vField &Ut = Omega->Ut;
  //Stopwatch cpu; cpu.start();
  convert( X, U );
  Omega->time_derivative( U, R[0] );
  add( R[1], R[0] );
  scale( 0.5*dt, R[0] );
  axpy( -1.0, Ut, R[0] );
  add( U, R[0]);
  convert( R[0], Y );
  //cout << "Residual cpu time = " << cpu.restart() << "sec" << endl;
}

void Trapezoidal::advance( Domain *Omega ) {
  const Scalar dt = Omega->dt;
  const Ordinal    &lstep = Omega->lstep;
  Scalar &t = Omega->t;
  vField &U = Omega->U;
  vField &Ut = Omega->Ut;

  Omega->prestep( U, lstep, 0, t );

  // save prior solution
  copy( U, Ut );

  // setup prior time derivative
  Omega->time_derivative( Ut, R[1] );

  // set initial condition
  Ordinal N = U.qtot();
  vec x( N );
  convert( U, x );
  vec F( N, 0.0 );

  Evaluator r(Omega,this);   // make residual evaluator function
  t += dt;

  r( x, F );                 // evaluate initial residual
  Scalar norm0 = itl::two_norm(F);
  Scalar two_norm_F = norm0, old_two_norm_F = 0.0;
  *out << "Newton iteration 0, |F| = " << two_norm_F << endl;

  //cout <<"Starting Newton iteration"<<endl;

  // setup Iterative Template Library (ITL)
#ifdef ITL_FD_STEP_SIZE
  itl::matrix_free_operator<vec,Evaluator> A( r, x, F, fd_step_size );
#else
  itl::matrix_free_operator<vec,Evaluator> A( r, x, F );
#endif
  itl::modified_gram_schmidt< vec > krylov( gmres_restart, x.size() );
  itl::identity_preconditioner p;

  // Newton iteration
  for (Ordinal newton_iter=1; newton_iter<=newton_max_iter; ++newton_iter) {
    vec dx( N, 0.0 );
    itl::basic_iteration<Scalar> gmres_iter( F, gmres_max_iter,
                                             gmres_rtol, gmres_atol);
    itl::gmres(A, dx, F, p, gmres_restart, gmres_iter, krylov);
    itl::add( itl::scaled(dx, -1.0), x );

    *out << "Iterations used in GMRES: " << gmres_iter.iterations()
         << "     Residual: " << gmres_iter.resid() << endl;

    //cout << "completed GMRES and computing Newton convergence" << endl;
    r( x, F );
    old_two_norm_F = two_norm_F;
    two_norm_F     = itl::two_norm(F);

    *out << "Newton iteration " << newton_iter << ", |F| = "
         << two_norm_F << endl;

    if ( two_norm_F < newton_rtol * norm0
         || std::abs( old_two_norm_F - two_norm_F ) < newton_stol
         || two_norm_F < newton_atol )
      break;
  }

  Omega->poststep( U, lstep, 0, t );
}

#endif  // DGM_USE_ITL

//============================================================================
//              High-Accuracy Large-Step Explicit Runge-Kutta7
//============================================================================

const Scalar HALERK7::a[7] = {0.0,
                               -0.761346747988321,
                               -2.77322222591202,
                               -0.316419740215259,
                               -0.643027215754751,
                               -5.30826663524038,
                               -0.502238095571852};
const Scalar HALERK7::b[7] = {0.07,
                               0.571148669794394,
                               0.269458393191951,
                               0.323313273749574,
                               0.951825658561456,
                               0.201392408904290,
                               0.160679143013867};
const Scalar HALERK7::c[7] = {0.07,
                               0.206306487428577,
                               0.297426941112912,
                               0.586145379953224,
                               0.991411159927887,
                               0.737628619842485,
                               1.0};

/// Constructor
HALERK7::HALERK7( Domain *Omega ) : 
  NR(1), R(NR, DGM::vField(Omega->get_comm())) 
{
  nsubstep = 7;
  initialize();
  for (Ordinal nr=0; nr<NR; ++nr) {
    for (vField::size_type i=0; i< Omega->U.size(); ++i)
      R[nr].push_back( new Field( Omega->U[i], Omega->root,
                                  Omega->U[i]->name ) );
    R[nr].zero();
    R[nr].set_name("R["+asString(nr)+"]");
  }
}

/// Advance RK7
void HALERK7::advance( Domain *Omega ) {
  const Scalar dt = Omega->dt;
  const Ordinal &lstep = Omega->lstep;
  Scalar t0 = Omega->t;
  Scalar &t = Omega->t;
  vField &U = Omega->U;
  vField &Ut = Omega->Ut;
  for (Ordinal nstage = 0; nstage < nsubstep; nstage++){
    substep = nstage;
    Omega->prestep( U, lstep-1, substep, t );      // u_1
    Omega->time_derivative( U, R[0] );             // -F
    axpby( -dt, R[0], a[nstage], Ut, Ut );         // W_i+1 = a_i W_i + dt F
    axpy( b[nstage], Ut, U);                       // U_i+1 = U_i + b_i W_i+1
    t = t0 + c[nstage]*dt;
    if(nstage != (nsubstep - 1))
      Omega->poststep( U, lstep-1, substep+1, t ); // y_2
    else
      Omega->poststep( U, lstep, 0, t );           // y_2
  }
}


//============================================================================
//              High-Accuracy Large-Step Explicit Runge-Kutta-67
//============================================================================
const Scalar HALERK67::a1[6] = {0.0,
                                 -1.0,
                                 -1.2200753774027558,
                                 -0.4855203139585440,
                                 -2.0049766886152282,
                                 -0.96630706132773678};

const Scalar HALERK67::b1[6] = {0.15259627988362773,
                                 0.41690681557832531,
                                 0.33198952871964376,
                                 0.68406153879445826,
                                 0.37551772516945155,
                                 0.17013279299558018};

const Scalar HALERK67::c1[6] = {0.15259627988362773,
                                 0.15259627988362773,
                                 0.48458580860327149,
                                 0.83652157431527965,
                                 0.82468533925354644,
                                 1.0};

const Scalar HALERK67::a2[7] = {0.0,
                                 -0.73831495306182581,
                                 -2.4721817198092085,
                                 -0.49453326271445394,
                                 -0.70908186071536016,
                                 -5.3082666352403812,
                                 -0.69686748771438564};

const Scalar HALERK67::b2[7] = {0.07,
                                 0.52634933297156350,
                                 0.30938941816614590,
                                 0.34431868938699142,
                                 0.95185692225821417,
                                 0.22519875943385069,
                                 0.14948193736303792};

const Scalar HALERK67::c2[7] = {0.07,
                                 0.20773774990454027,
                                 0.31697294689145703,
                                 0.60117242906818840,
                                 0.99593246133520197,
                                 0.72536123998940797,
                                 1.0};
/// Constructor
HALERK67::HALERK67( Domain *Omega ) : NR(1), 
  R(NR, DGM::vField(Omega->get_comm()))
{
  nsubstep = 7;
  initialize();
  for (Ordinal nr=0; nr<NR; ++nr) {
    for (vField::size_type i=0; i< Omega->U.size(); ++i)
      R[nr].push_back( new Field( Omega->U[i], Omega->root,
                                  Omega->U[i]->name ) );
    R[nr].zero();
    R[nr].set_name("R["+asString(nr)+"]");
  }
}

/// Advance Hale RK6-7
void HALERK67::advance( Domain *Omega ) {
  const Scalar dt = Omega->dt;
  const Ordinal &lstep = Omega->lstep;
  Scalar t0 = Omega->t;
  Scalar &t = Omega->t;
  vField &U = Omega->U;
  vField &Ut = Omega->Ut;
  if (lstep%2==1) {                                  // Step 1
    // cout << "lstep = " << lstep << " in stage 1" << endl;
    for (Ordinal nstage = 0; nstage < (nsubstep-1); nstage++ ) {
      substep = nstage;
      Omega->prestep( U, lstep-1, substep, t );      // u_1
      Omega->time_derivative( U, R[0] );             // -F
      axpby( -dt, R[0], a1[nstage], Ut, Ut );        // W_i+1 = a_i W_i + dt F
      axpy( b1[nstage], Ut, U);                      // U_i+1 = U_i + b_i W_i+1
      t = t0 + c1[nstage]*dt;
      if(nstage != (nsubstep - 2))
        Omega->poststep( U, lstep-1, substep+1, t ); // y_2
      else
        Omega->poststep( U, lstep, 0, t );           // y_2
    }
  } else {                                           // Step 2
    // cout << "lstep = " << lstep << " in stage 2" << endl;
    for (Ordinal nstage = 0; nstage < nsubstep; nstage++ ) {
      substep = nstage;
      Omega->prestep( U, lstep-1, substep, t );      // u_1
      Omega->time_derivative( U, R[0] );             // -F
      axpby( -dt, R[0], a2[nstage], Ut, Ut );        // W_i+1 = a_i W_i + dt F
      axpy( b2[nstage], Ut, U);                      // U_i+1 = U_i + b_i W_i+1
      t = t0 + c2[nstage]*dt;
      if(nstage != (nsubstep - 1))
        Omega->poststep( U, lstep-1, substep+1, t ); // y_2
      else
        Omega->poststep( U, lstep, 0, t );           // y_2
    }
  }
}

//============================================================================
//              14 Stage, 4th Order, Low Storage Runge Kutta
//============================================================================

/** This Low-Storage Runge-Kutta time integration method (14 stage, 2 registers)
    is based on:
    \verbatim
    Jens Niegemann, Richard Diehl, and Kurt Busch
    Efficient Low-Storage Runge-Kutta Schemes with Optimized Stability Regions
    Journal of Computational Physics, 231(2), pp. 364-372, 2012,
    doi:10.1016/j.jcp.2011.09.003, issn 0021-9991
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
const Scalar LSRK14::A[15] = {
   0.0,
  -0.7188012108672410,
  -0.7785331173421570,
  -0.0053282796654044,
  -0.8552979934029281,
  -3.9564138245774565,
  -1.5780575380587385,
  -2.0837094552574054,
  -0.7483334182761610,
  -0.7032861106563359,
   0.0013917096117681,
  -0.0932075369637460,
  -0.9514200470875948,
  -7.1151571693922548,
   0.0};

const Scalar LSRK14::B[14] = {
  0.0367762454319673,
  0.3136296607553959,
  0.1531848691869027,
  0.0030097086818182,
  0.3326293790646110,
  0.2440251405350864,
  0.3718879239592277,
  0.6204126221582444,
  0.1524043173028741,
  0.0760894927419266,
  0.0077604214040978,
  0.0024647284755382,
  0.0780348340049386,
  5.5059777270269628};

const Scalar LSRK14::c[14] = {
  0.0,
  0.0367762454319673,
  0.1249685262725025,
  0.2446177702277698,
  0.2476149531070420,
  0.2969311120382472,
  0.3978149645802642,
  0.5270854589440328,
  0.6981269994175695,
  0.8190890835352128,
  0.8527059887098624,
  0.8604711817462826,
  0.8627060376969976,
  0.8734213127600976};

const Scalar LSRK14::w[15] = {
 -0.116683473041717417,
  0.213493962104674251,
  0.128620987881127052,
  4.610096100109887907,
 -5.386527768056724064,
  1.445540684241274576,
 -0.761388932107154526,
  0.543874700576422732,
  0.102277834602298279,
  0.07127466608688701188,
 -3.459648919807762457,
  37.20095449534884580,
 -39.09786206496502814,
  5.505977727026962754, 
  0.0};

/// Constructor
LSRK14::LSRK14( Domain *Omega ) : 
  NR(1), R(NR, DGM::vField(Omega->get_comm()))
{
  if (Omega->verbosity())
    Omega->get_comm()->cout()<<"Building LSRK14 time integrator"<<endl;
  nsubstep = 14;
  initialize();
  for (Ordinal nr=0; nr<NR; ++nr) {
    for (vField::size_type i=0; i< Omega->U.size(); ++i)
      R[nr].push_back( new Field( Omega->U[i], Omega->root,
                                  Omega->U[i]->name ) );
    R[nr].zero();
    R[nr].set_name("R["+asString(nr)+"]");
  }
  if (Omega->verbosity())
    Omega->get_comm()->cout()<<"Finished LSRK14 time integrator"<<endl;
}

// compute interpolated solution at a substep given step values
void LSRK14::interpolate( const Ordinal sstep, const vField &U_ip1,
                              vField &U_i ) {
  assert( sstep >= 0 );
  assert( sstep <  nsubstep );
  const Scalar w2 = c[sstep];
  const Scalar w1 = 1.0 - w2;
  scale( w1, U_i );
  axpy( w2, U_ip1, U_i );
}

// compute interpolated solution at a substep given step values
void LSRK14::interpolate( const Ordinal sstep, const Scalar &U_ip1,
                              Scalar &U_i ) {
  assert( sstep >= 0 );
  assert( sstep <  nsubstep );
  const Scalar w2 = c[sstep];
  const Scalar w1 = 1.0 - w2;
  U_i = w1 * U_i + w2 * U_ip1;
}

// compute interpolated solution at a substep given step values
Scalar LSRK14::interpolate( const Scalar U_i,
                                const Scalar U_ip1,
                                const Ordinal sstep ) const {
  assert( sstep >= 0 );
  assert( sstep <  nsubstep );
  const Scalar w2 = c[sstep];
  const Scalar w1 = 1.0 - w2;
  const Scalar U = w1 * U_i + w2 * U_ip1;
  return U;
}

/// Advance LSRK14
void LSRK14::advance( Domain *Omega ) {
  const Scalar dt = Omega->dt;
  const Ordinal &lstep = Omega->lstep;
  Scalar &t = Omega->t;
  vField &U = Omega->U;
  vField &Ut = Omega->Ut;
  const Scalar tn = Omega->t;
  // Note A[0] = 0, 
  // so Ut is scaled by zero in the first step and we don't need Ut.zero();
 
  for (substep=0; substep<nsubstep; substep++) {
    t = tn + c[substep]*dt;
    Omega->prestep( U, lstep-1, substep, t );
    Omega->time_derivative( U, R[0] );        // recall time_derivative is -F
    axpby(-dt, R[0], A[substep], Ut, Ut);     // Ut = A_{s}*Ut - dt*R0
    axpy(B[substep], Ut, U);                  // U = U + B_{s}*Ut
    if(substep+1 < nsubstep) {
      t = tn + c[substep+1]*dt;
      Omega->poststep( U, lstep-1, substep+1, t);
    } else {
      t = tn + dt;
      Omega->poststep( U, lstep, 0, t );
    }
  }
}

void LSRK14::advance( Domain *Omega, ObjFunc *Jp ) {
  const Scalar dt = Omega->dt;
  const Ordinal &lstep = Omega->lstep;
  Scalar &t = Omega->t;
  vField &U = Omega->U;
  vField &Ut = Omega->Ut;
  ObjFunc &J = *Jp;
  vector<ObjFunc> r(1, J);
  const Scalar tn = Omega->t;
  // Note A[0] = 0, 
  // so Ut is scaled by zero in the first step and we don't need Ut.zero();

  for (substep=0; substep<nsubstep; substep++) {
    t = tn + c[substep]*dt;
    Omega->prestep( U, lstep-1, substep, t );
    Omega->time_derivative(U, R[0]);          // recall time_derivative is -F
    r[0]( U, lstep-1, substep );
    axpby(-dt, R[0], A[substep], Ut, Ut);     // Ut = A_{s}*Ut - dt*R1
    axpy(B[substep], Ut, U);                  // U = U + B_{s}*Ut
    axpy(w[substep]*dt, r[0], J);             // J = J + w_{s}*dt*r0
    if(substep+1 < nsubstep) {
      t = tn + c[substep+1]*dt;
      Omega->poststep( U, lstep-1, substep+1, t);
    } else {
      t = tn + dt;
      Omega->poststep( U, lstep, 0, t );
    }
  }
}

void LSRK14::advance( DGM::Function *J ) {
  const Scalar dt = J->dt;
  const Ordinal &lstep = J->lstep;
  Scalar &t = J->t;
  Scalar Jev;
  const Scalar tn = J->t;

  for (substep=0; substep<nsubstep; substep++) {
    t = tn + c[substep]*dt;
    Jev  = J->evaluate( lstep-1, substep );
    J->value += w[substep]*dt*Jev;            // J = J + w_{s}*dt*Jev
    if(substep+1 < nsubstep) {
      t = tn + c[substep+1]*dt;
    }
  }
  t = tn + dt;
}

/// Adjoint advance LSRK14
void LSRK14::adjoint_advance( Domain *Omega ) {
  const Scalar dt = Omega->dt;
  const Ordinal &lstep = Omega->lstep;
  Scalar &t = Omega->t;
  vField &U = Omega->U;
  vField &Ut = Omega->Ut;
  const Scalar tn = Omega->t - dt;
  // Note A[nsubstep] = 0, which means 
  // Ut is scaled by zero in the first step and we don't need Ut.zero();

  for (substep=nsubstep-1; substep>=0 && nsubstep>substep; substep--) {
    // Scale:   Ut = w_{s+1}*Ut
    // Update:  Ut = A_{s+1}*Ut + B_{s}*U
    // Unscale: Ut = Ut / w_{s}
    axpby(B[substep]/w[substep], U, 
	  A[substep+1]*w[substep+1]/w[substep], Ut, Ut); 
    t = tn + c[substep]*dt;                     // t  = t_{s}
    Omega->prestep(Ut, lstep-1, substep, t);
    Omega->time_derivative(Ut, R[0]);
    axpy(w[substep]*dt, R[0], U);               // U = U + w_{s}*dt*R0
    if(substep > 0) {
      t = tn + c[substep-1]*dt;
      Omega->poststep(Ut, lstep-1, substep, t);
    } else {
      t = tn;
      Omega->poststep(U, lstep-1, substep, t);
    }
  }
}

// compute the relative local time at a given substep
Scalar LSRK14::getsubtime( const Ordinal sstep ) const {
  assert( sstep >= 0 );
  assert( sstep <  nsubstep );
  return c[sstep];
}

} // DGM namespace
