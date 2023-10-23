#ifndef DGM_REMOVE_FOR_RELEASE

/*=============================================================================
  Module:     ShallowState Module

  Contact:    S. Scott Collis

  Copyright:  (c)2013 Sandia National Laboratories
=============================================================================*/

/** \file  ShallowState.cpp
    \brief State class implementation for the 2d Shallow equations
    \author Vincent Mousseau
    \author S. Scott Collis
*/

// system includes
#include <cassert>

// boost includes
#include "boost/numeric/conversion/cast.hpp"
using boost::numeric_cast;

// DGM includes
#include "TimeInt.hpp"

// Reo includes
#include "ShallowState.hpp"
#include "ShallowAdjoint.hpp"

namespace Reo {

/// Constructor
ShallowState::ShallowState( DGM::ArgList &args, const DGM::Comm::Ptr comm_,
                          const int pinc) :
  Shallow(args,comm_,pinc), State(pinc) {

  // initialize parameters
  int p = params["p"];
  p += p_inc;
  comm->cout() << "ShallowState:  p = "<< p <<endl;

  // allocate local workspace
  wk3.resize(5*max(Lmax(),Qmax()));
  wk4.resize(5*max(Lmax(),Qmax()));

  // make sure that storage is initialized
  zero_all_fields();
}

void ShallowState::steady_residual( vField &Us, vField &Uf, const bool ) {
  convection( Us, Uf );
  add_source( Us, Uf );
  project(Uf);
}

void ShallowState::residual( vField &Us, vField &Uf, const bool ) {
  // WARNING:  Hardwired for backward Shallow...
  convection( Us, Uf );
  add_source( Us, Uf );
  scale( dt, Uf );
  axpy( -1.0, Ut, Uf );
  add( U, Uf );
  scale( 1/dt, Uf );
}

Scalar ShallowState::estimate_error( const Ordinal npredict, Adjoint *adjoint,
                                      dVector &error ) {
  static Format sci(8); sci.scientific().width(15);
  char tmp[80];
  comm->cout()<<"ShallowState::estimate_error(...)"<<endl;

  time_int->initialize();

  // Build residual on each element
  vField &S  = U;
  vField &St = Ut;
  vField &R  = adjoint->domain()->Ut;
  vField &A  = adjoint->domain()->U;

  if (error.size() != S[0]->ne) error.resize(S[0]->ne);
  if (area.size() != S[0]->ne) area.resize(S[0]->ne);
  error = 0.0;
  area = 0.0;

  load_field( St, 0, 0 );

  // loop over time steps
  for (lstep=1; lstep<=numeric_cast<Ordinal>(npredict); ++lstep) {
    step++;

    load_field( S, lstep, 0 );               // load State

    // State residual in Adjoint space
    residual(S, R);
    //cout<<"\nNorms of residual ="<<endl;
    //R.norm();
    //R.tecplot("residual.dat","Residual");

    adjoint->load_field(A, lstep, 0);    // load Adjoint
    //A.tecplot("adjoint.dat","Adjoint");

    // Integrate the adjoint times the residual over each element
    for (LocalSize e=0; e<S[0]->ne; ++e) {
      Element *r = R[0]->el[e];
      Element *a = A[0]->el[e];
      dvmul( a->u, r->u );
      error[e] += dt*r->integrate(&area[e]);
    }
    if (lstep%Ntout==0) {
      R.norm();
      sprintf(tmp,"%s.err.%lld_%lld.dat",root.c_str(),(long long)lstep,(long long)0);
      R.tecplot(tmp,"Error");
    }
    load( St, lstep, 0 );
  }

  // print out the total error (over time)
  Scalar total_error(0), total_area(0);
  cout<<endl;
  for (LocalSize e=0; e<S[0]->ne; ++e) {
    cout << "Error(" << e << ") = " << sci(error[e]) << ", Error(" << e
         << ")/area = "<< sci(error[e]/area[e]) << endl;
    total_error += error[e];
    total_area += area[e];
  }
  return total_error;
}

Scalar ShallowState::estimate_error_steady(const Ordinal npredict,
                                          Adjoint *adjoint_,
                                          dVector &error ) {
  static Format sci(8); sci.scientific().width(15);
  comm->cout()<<"ShallowState::estimate_error_steady()"<<endl;

  ShallowAdjoint *adjoint = dynamic_cast<ShallowAdjoint*>(adjoint_);

  // Build residual on each element
  vField &S  = U;
  vField &R  = Ut;
  vField &A  = adjoint->domain()->U;

  if (error.size() != S[0]->ne) error.resize(S[0]->ne);
  if (area.size() != S[0]->ne) area.resize(S[0]->ne);
  error = 0.0;
  area = 0.0;

  Scalar total_error = 0.0;
  Scalar total_area = 0.0;

  load_field(S, npredict, 0);      // load State into Adjoint storage
  S.tecplot("state.dat","State");

  // State residual in Adjoint space
  steady_residual(S, R);
  cout<<"\nNorms of residual ="<<endl;
  R.norm();
  R.tecplot("residual.dat","Residual");

  adjoint->load_field(A, 1, 0);    // load Adjoint
  A.tecplot("adjoint.dat","Adjoint");

  // Integrate the adjoint times the residual over each element
  for (vField::size_type i=0; i<S.size(); ++i) {
    for (LocalSize e=0; e<S[i]->ne; ++e) {
      Element *r = R[i]->el[e];
      Element *a = A[i]->el[e];
      dvmul( a->u, r->u );
      error[e] += r->integrate(&area[e]);
    }
  }
  cout<<"\nNorms of error ="<<endl;
  R.norm();
  R.tecplot("error.dat","Error");

  // print out the total error
  cout<<endl;
  for (LocalSize e=0; e<S[0]->ne; ++e) {
    cout << "Error(" << e << ") = " << sci(error[e]) << ", Error(" << e
         << ")/area = "<< sci(error[e]/area[e]) << endl;
    total_error += error[e];
    total_area += area[e];
  }

  return total_error;
}

} // namespace Reo

#else // DGM_REMOVE_FOR_RELEASE
// This capability is under development.
#endif // DGM_REMOVE_FOR_RELEASE
