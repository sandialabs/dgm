/*=============================================================================
  Module:     Reo Adv_Diff_State Module

  Author:     S. Scott Collis

  Copyright:  S. Scott Collis
              Department of Mechanical Engineering and Materials Science
              Rice University, MS 321
              Houston, TX 77005-1892
              (713) 348-3617
              collis@rice.edu
=============================================================================*/

/** \file Adv_Diff_State.cpp
    \brief Advection diffusion State implementation
    \author Scott Collis
*/

// local includes
#include "Adv_Diff_State.hpp"
#include "Adv_Diff_Adjoint.hpp"

namespace Reo {

/// Constructor
Adv_Diff_State::Adv_Diff_State( DGM::ArgList &args, 
                                const DGM::Comm::Ptr comm_, const int pinc ) :
  Adv_Diff(args,comm_,pinc), State(pinc) {

  // initialize parameters
  int p = params["p"];
  p += p_inc;
  comm->cout() << "Adv_Diff_State:  p = "<< p <<endl;

  // allocate local workspace
  wk4.resize(max(Lmax(),Qmax()));
  wk5.resize(max(Lmax(),Qmax()));
  wk6.resize(max(Lmax(),Qmax()));
  wk7.resize(max(Lmax(),Qmax()));

  zero_all_fields();
}

#ifdef DGM_STATE_USE_DTK_TIMEINTEGRATE
/** Need to override the default from Domain to integrate objective */
void Adv_Diff_State::set_TimeInt( Ordinal ) {
  int inttype = params["inttype"];
  switch(inttype) {
  case TimeInt::FORWARD_EULER: {
    comm->cout() << "Adv_Diff_Adjoint:: using Forward Euler" << endl;
    time_int = new ForwardEuler( this );
    break; }
  case TimeInt::TVD_RK: {
    comm->cout() << "Adv_Diff_Adjoint:: using TVD RK" << endl;
    time_int = new TVD( this );
    break; }
  case TimeInt::RUNGE_KUTTA: {
    comm->cout() << "Adv_Diff_Adjoint:: using Runge-Kutta-4" << endl;
    time_int = new RungeKutta( this );
    break; }
  case TimeInt::SSPRK: {
    comm->cout() << "Adv_Diff_Adjoint:: using SSPRK" << endl;
    time_int = new SSPRK( this );
    break; }
#ifdef DGM_USE_ITL
  case TimeInt::BACKWARD_EULER: {
    comm->cout() << "Adv_Diff_Adjoint:: using Backward-Euler" << endl;
    time_int = new BackwardEuler( this );
    break; }
#endif
  case TimeInt::LSRK14: {
    comm->cout() << "Adv_Diff_Adjoint:: using LSRK14" << endl;
    time_int = new LSRK14( this );
    break; }
 default:
    comm->error("Adv_Diff_Adjoint::set_TimeInt() Unsupported time "
                "integration type");
    break;
  }
#if 0
  // We would need an ObjFunc to instantiate this...
  // try out a DTK time integrator
  typedef DTK::TimeIntegrate<Scalar,Ordinal,CompositeData,CompositeFunc> TI;
  typedef DTK::RungeKutta<Scalar,Ordinal,CompositeData,CompositeFunc> RK;
  Shared<CompositeFunc>::Ptr compositeFunc(new CompositeFunc(domain(),&J));
  Shared<TI>::Ptr DTK_ti(new RK(compositeFunc.get()));
#endif
}
#endif

void Adv_Diff_State::steady_residual( vField &Us, vField &Uf,
                                      const bool source ) {
  //cout << "Adv_Diff_State::steady_residual(...)"<<endl;
#ifdef HARD_BC
  enforce_hard_bc(Us);
#endif
  convection( Us, Uf );
#ifdef AD_LOCAL_DIFFUSION
  local_diffusion( Us, Uv, Uf );
#else
  diffusion( Us, Uv, Uf );
#endif
  if (source) add_source( Us, Uf );

  // NB:  I think that the issue is that you always need to project the
  // source to the coarse space or you won't get consistent results!

  // This projection shouldn't be here...
  project(Uf);
}


void Adv_Diff_State::residual( vField &Us, vField &Uf, const bool source ) {
  // WARNING:  Hardwired for backward Euler...
#ifdef HARD_BC
  enforce_hard_bc(Us);
#endif
  if (fv) { // finite volume reconstruction
    Us.make_constant();
    linear_reconstruction( Us, Uv, Uf );
  }
  //time_derivative(Us,Uf);
  //Uf.norm();
  convection( Us, Uf );
  diffusion( Us, Uv, Uf );
  if (source) add_source( Us, Uf );
  // This projection is questionable [ssc]
  //project(Uf);
#if 0
  if (fv) { // finite volume reconstruction
    Uf.make_constant();
    Us.make_constant();
  }
#endif
  scale( dt, Uf );
  axpy( -1.0, Ut, Uf );
  add( Us, Uf );
  scale( 1/dt, Uf );
}

Scalar Adv_Diff_State::estimate_error( const Ordinal npredict, Adjoint *adjoint,
                                       dVector &error ) {
  static Format sci(8); sci.scientific().width(15);
  char tmp[80];
  comm->cout()<<"Adv_Diff_State::estimate_error(...)"<<endl;

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
  //St.norm();
  if (fv) {  // finite volume reconstruction
    St.make_constant();
    linear_reconstruction( St, dynamic_cast<Adv_Diff_Adjoint*>(adjoint)->Uv,
                           dynamic_cast<Adv_Diff_State*>(this)->Uv );
  }

  // loop over time steps
  for (lstep=1; lstep<=(Ordinal)npredict; ++lstep) {
    step++;

    //load_field( S, lstep, 0 );   // load State (doesn't get t right)
    load( S, lstep, 0 );           // load State
    //S.norm();

    // State residual in Adjoint space
    residual(S, R);
#if 0
    if (lstep%Ntout==0) {
      cout<<"R:";
      R.norm();
      sprintf(tmp,"%s.res.%d_%d.dat",root.c_str(),lstep,0);
      R.tecplot(tmp,"Residual");
    }
#endif
    adjoint->load_field(A, lstep, 0);    // load Adjoint
    // project(A);
    if (fv) {
      A.make_constant();
      linear_reconstruction( A, dynamic_cast<Adv_Diff_Adjoint*>(adjoint)->Uv,
                             dynamic_cast<Adv_Diff_State*>(this)->Uv );
      //A.kill_constant();
    }
#if 0
    if (lstep%Ntout==0) {
      cout<<"A:";
      A.norm();
      sprintf(tmp,"%s.adj.%d_%d.dat",root.c_str(),lstep,0);
      A.tecplot(tmp,"Adjoint");
    }
#endif
    // A.tecplot("adjoint.dat","Adjoint");

    // Integrate the adjoint times the residual over each element
    for (LocalSize e=0; e<S[0]->ne; ++e) {
      Element *r = R[0]->el[e];
      Element *a = A[0]->el[e];
      dvmul( a->u, r->u );
      error[e] += dt*r->integrate(&area[e]);
      //error[e] += dt*fabs(r->integrate(&area[e]));
      //error[e] = r->integrate(&area[e]);
    }
    if (lstep%Ntout==0) {
      cout<<"E:";
      R.norm();
      sprintf(tmp,"%s.err.%lld_%d.dat",root.c_str(),(long long)lstep,0);
      R.tecplot(tmp,"Error");
    }
    load( St, lstep, 0 );
    if (fv) { // finite volume reconstruction
      St.make_constant();
      linear_reconstruction( St, dynamic_cast<Adv_Diff_Adjoint*>(adjoint)->Uv,
                             dynamic_cast<Adv_Diff_State*>(this)->Uv );
    }
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


Scalar Adv_Diff_State::estimate_error_steady(const Ordinal npredict,
                                             Adjoint *adjoint_,
                                             dVector &error ) {
  static Format sci(8); sci.scientific().width(15);
  comm->cout()<<"Adv_Diff_State::estimate_error_steady()"<<endl;

  Adv_Diff_Adjoint *adjoint = dynamic_cast<Adv_Diff_Adjoint*>(adjoint_);

  // Build residual on each element
  vField &S  = U;  // p + p_inc
  vField &R  = Ut; // p + p_inc

  //vField &S1  = adjoint->get_state()->domain()->U;  // p
  //vField &R1  = adjoint->get_state()->domain()->Ut; // p

  vField &A  = adjoint->domain()->U;  // p + p_inc

  if (error.size() != S[0]->ne) error.resize(S[0]->ne);
  if (area.size() != S[0]->ne) area.resize(S[0]->ne);
  error = 0.0;
  area = 0.0;

  Scalar total_error = 0.0;
  Scalar total_abs_error = 0.0;
  Scalar total_area = 0.0;

  load_field(S, npredict, 0);      // load State in larger space
  S.tecplot("state.dat","State");

  // load exact solution
  set_ic(R,".sol");
  R.tecplot("exact.dat","Exact");
  // axpy(-1.0,S,R);
  // The estimated fine scales should only be in the fine-space
  R.fine_scales(p_inc);
  R.tecplot("true_error.dat","Error");
  cout<<"\nNorm of true error\n";
  R.norm();

  S.zero();
  steady_residual(R, S, false); // evaluate without source term
  scale(-1.0,S);
  S.coarse_scales(p_inc);
  S.tecplot("exact_source.dat","Source");
  S.write("exact_source.fld");
  cout<<"\nNorm of exact source\n";
  S.norm();

  // get back to estimating things

  load_field(S, npredict, 0);      // load State in larger space
  S.tecplot("state.dat","State");

#if 0
  load_field(S1, npredict, 0);      // load State at p
  S1.tecplot("state-1.dat","State");
  adjoint->get_state()->steady_residual(S1, R1); // evaluate residual at p
  cout<<"\nNorms of residual-1 ="<<endl;
  R1.norm();
  R1.tecplot("residual-1.dat","Residual");
  adjoint->get_state()->store(R1, npredict, 0);
  load_field(R, npredict, 0);      // residual at p lifted to p + p_inc
#else
  steady_residual(S, R, true);     // evaluate residual in larger space
#ifdef AD_TRUNCATE_RESIDUAL
  cout<<"\nTruncate modes in residual\n";
  R.truncate_modes(p_inc);         // try this as a means of killing high modes
#endif
#endif
#ifdef AD_COARSE_RESIDUAL
  cout<<"\nCoarse scale residual\n";
  R.coarse_scales(p_inc);
#endif
#ifdef AD_FINE_RESIDUAL
  cout<<"\nFine scale residual\n";
  R.fine_scales(p_inc);
#endif
  R.tecplot("residual.dat","Residual");
  cout<<"\nNorms of residual ="<<endl;
  project(R);
  R.norm();
  R.write("residual.fld");

  adjoint->load_field(A, 1, 0);    // load Adjoint
  cout<<"\nNorm of the adjoint\n";
  A.norm();
  A.tecplot("adjoint.dat","Adjoint");
#ifdef AD_FINE_ADJOINT
  A.fine_scales(p_inc);
  A.tecplot("adjoint_fine.dat","Error");
  cout<<"\nNorm of the adjoint fine scales\n";
  A.norm();
#endif

  // Integrate the adjoint times the residual over each element
  for (LocalSize e=0; e<S[0]->ne; ++e) {
    Element *r = R[0]->el[e];
    Element *a = A[0]->el[e];
    dvmul( a->u, r->u );
    error[e] = r->integrate(&area[e]);
  }
  cout<<"\nNorms of predicted error ="<<endl;
  R.coarse_scales(p_inc);
  R.norm();
#ifdef ADV_DIFF_STATE_CONST_ERROR
  // This is just a little test to see if the constant mode of the error
  // has any useful information in it
  cout<<"WARNING, making error constant for a little test\n";
  R.make_constant();
#endif
  R.tecplot("error.dat","Error");

  // Now compute a source term that is the operator applied to the fine scales

  S.zero();
  steady_residual(R, S, false); // evaluate without source term
  scale(-1.0,S);
  S.coarse_scales(p_inc);
  S.tecplot("source.dat","Source");
  S.write("source.fld");
  cout<<"\nNorm of source\n";
  S.norm();

  // print out the total error
  cout<<endl;
  for (LocalSize e=0; e<S[0]->ne; ++e) {
    cout << "Error(" << e << ") = " << sci(error[e]) << ", Error(" << e
         << ")/area = "<< sci(error[e]/area[e]) << endl;
    total_error += error[e];
    total_abs_error += abs(error[e]);
    total_area += area[e];
  }
  cout<<"Total abs(error) = "<<total_abs_error<<endl;

  return total_error;
}

//=============================================================================

/// Compute the diffusion term without using the jump-savvy gradients
void Adv_Diff_State::local_diffusion( vField &Uf, vField &Ff, vField &Rf ) {
  if (mu == 0) return;
  cout << "Local_Diffusion for Field = " << Uf[0]->name << endl;
  LocalSize nsd = Uf[0]->nsd();
  Uf.fill_sides();                   // put solution on the sidess
  Uf.share_sides();
  enforce_bc(Uf);                    // update bc side values
  average_flux( Uf, Ff, '+' );       // F's sides are average of the solution
  for (LocalSize e=0; e<Uf[0]->ne; e++) {
    Element *U = Uf[0]->el[e];
    Element *F = Ff[0]->el[e];
    const LocalSize qtot = U->qtot;
    const LocalSize nModes = U->nModes();
    dVector ux(wk4,qtot);
    dVector uxh(ux,nModes);
    if (nsd==3) {
      dVector uy(wk5,qtot);
      dVector uyh(uy,nModes);
      dVector uz(wk6,qtot);
      dVector uzh(uz,nModes);
      U->gradient(U->u, ux, uy, uz);
      scale( mu, ux );
      scale( mu, uy );
      scale( mu, uz );
      U->fill_sides( ux, uy, uz );            // normal viscous flux on sides
      U->gradient(ux, ux, 'x');               // ux = u_{,xx}
      U->gradient(uy, uy, 'y');               // uy = u_{,yy}
      U->gradient(uz, uz, 'z');               // uz = u_{,zz}
      dvadd( ux, uy, F->u );                  // F->u = u_{,xx} + u_{,yy}
      dvadd( uz, F->u );                      // F->u += u_{,zz}
    } else if (nsd==2) {
      dVector uy(wk5,qtot);
      dVector uyh(uy,nModes);
      // Note that this is the whole magic here.  You need to include the
      // gradient at all scales but the jump only on the coarse scales [ssc]
      ux=0;
      uy=0;
      //#ifdef AD_LOCAL_DIFFUSION_LIFT
      // lift ux (possibly to a reduced space)
      U->lift( F, ux, 'x' );
      U->forward_transform(ux,uxh);
      U->coarse_scales(p_inc,uxh);
      U->backward_transform(uxh,ux);          // lifted ux
      // lift uy (possibly to a reduced space)
      U->lift( F, uy, 'y' );
      U->forward_transform(uy,uyh);
      U->coarse_scales(p_inc,uyh);
      U->backward_transform(uyh,uy);          // lifted uy
      //#endif
      dVector uxt(wk6,qtot);
      dVector uyt(wk7,qtot);
      U->gradient(U->u, uxt, uyt);
      dvadd(uxt,ux);
      dvadd(uyt,uy);
      // build the viscous flux
      scale( mu, ux );
      scale( mu, uy );
      U->fill_sides( ux, uy );                // normal viscous flux on sides
      U->gradient(ux, ux, 'x');               // ux = u_{,xx}
      U->gradient(uy, uy, 'y');               // uy = u_{,yy}
      dvadd( ux, uy, F->u );                  // F->u = u_{,xx} + u_{,yy}
    } else if (nsd==1) {
      U->gradient(U->u, ux, ux);
      scale( mu, ux );
      U->fill_sides( ux, ux );                // normal viscous flux on sides
      U->gradient(ux, F->u, 'x');             // ux = uxx
    } else {
      comm->cerr()<< "Adv_Diff:diffusion -- illegal value of nsd" << endl;
      comm->exit(DGM::FAILURE);
    }
  }
#ifdef AD_LOCAL_DIFFUSION_LIFT
  Uf.share_sides();
  enforce_flux_bc(Uf);                        // put flux BC's on bc sides
  average_flux( Uf, Ff, '-' );
  for (int e=0; e<Uf[0]->ne; e++) {
    Element *U = Uf[0]->el[e];
    Element *F = Ff[0]->el[e];
    U->lift( F, F->u );      // add side fluxes to interior
  }
#endif
  scale( -1.0, Ff);                           // Currently on LHS
  add( Ff, Rf );                              // add in viscous contribution
}

} // namespace Reo
