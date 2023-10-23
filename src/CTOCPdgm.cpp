// /////////////////////////////////////////////////////
// CTOCPdgm.cpp

#include "CTOCPdgm.hpp"
#include "Format.hpp"

namespace TDD {

// Several helper functions for copying from dVector to TSFCore::Vector

#include "TSFCoreExplicitVectorView.hpp"

void copy( const TSFCore::Vector<double> &v_in, dVector &x  )
{
  const TSFCore::EpetraVector
    *e_v = dynamic_cast<const TSFCore::EpetraVector*>(&v_in);
  if(e_v) {
    const Epetra_Vector &ee_v = *e_v->epetra_vec();
    // std::cout<<x.size()<<" "<<ee_v.MyLength()<<std::endl;
    assert( x.size() == ee_v.MyLength() );
    std::copy( &ee_v[0], &ee_v[0]+ee_v.MyLength(), x.data() );
  } else {
    TSFCore::ExplicitVectorView<double> v(v_in);
    assert( x.size() == v.subDim() );
    std::copy( v.values(), v.values() + v.subDim(), x.data() );
  }
}

void copy( const dVector &x, TSFCore::Vector<double> &v_in)
{
  TSFCore::EpetraVector
    *e_v = dynamic_cast<TSFCore::EpetraVector*>(&v_in);
  if(e_v) {
    Epetra_Vector &ee_v = *e_v->epetra_vec();
    assert( x.size() == ee_v.MyLength() );
    std::copy( x.data(), x.data() + x.size(), &ee_v[0] );
  } else {
    TSFCore::ExplicitMutableVectorView<double> v(v_in);
    assert( x.size() == v.subDim() );
    std::copy( x.data(), x.data() + x.size(), v.values() );
  }
}

} // end namespace TDD


namespace TSFCore {

///
// Implementation of a scalar product for the control
class DGMControlScalarProd : public ScalarProd<double> {
public:
  typedef double Scalar;
  DGMControlScalarProd
  (const Teuchos::RefCountPtr<const TDD::CTOCPdgm > &ctocp_)
    : ctocp(ctocp_) {}
  void scalarProds( const MultiVector<Scalar>& X,
                    const MultiVector<Scalar>& Y,
                    Scalar scalar_prods[] ) const {
    const int m = X.domain()->dim();
    for( int k = 1; k <= m; ++k ) {
      scalar_prods[k-1] = ctocp->applyLinGrad( &*X.col(k), &*Y.col(k) );
    }
  }
private:
  Teuchos::RefCountPtr<const TDD::CTOCPdgm > ctocp;
};

///
// Implementation of a scalar product for the state
//
// This ScalarProd requires to vFields for evaluation of the L2_inner_product
// pointers to these two vFields must be passed into the constructor and
// and one must ensure that there is no important data stored on these vFields
class DGMStateScalarProd : public ScalarProd<double> {
public:
  typedef double Scalar;
  DGMStateScalarProd(const Teuchos::RefCountPtr<const TDD::CTOCPdgm > &ctocp_,
                     vField *f, vField *g)
    : ctocp(ctocp_), F(f), G(g) {}
  void scalarProds( const MultiVector<Scalar>& X,
                    const MultiVector<Scalar>& Y,
                    Scalar scalar_prods[] ) const {
    const int m = X.domain()->dim();
    dVector tmp1(F->qtot()), tmp2(F->qtot());
    for( int k = 1; k <= m; ++k ) {
      TDD::copy( *X.col(k), tmp1 );
      TDD::copy( *Y.col(k), tmp2 );
      F->fill( tmp1 ); G->fill( tmp2 );
      scalar_prods[k-1] = vField::L2_inner_product( *F, *G );
    }
  }
private:
  Teuchos::RefCountPtr<const TDD::CTOCPdgm > ctocp;
  vField *F, *G;  // these vField will be used as scratch space
};

} // end namespace TSFCore

namespace TDD {

CTOCPdgm::CTOCPdgm ( int i, int n_i, Scalar t_i, Scalar t_ip1,
                     const Epetra_Comm &Comm,
                     OptProblem *ocp,
                     OptProblem *lin_ocp)
  : i_(i), n_i_(n_i)
  , t_i_(t_i)
  , t_ip1_(t_ip1)
  , y_bar_map(Teuchos::rcp(new Epetra_Map
      ((dynamic_cast<Domain*>(ocp->state))->U.qtot(), 0, Comm)))
  , u_bar_map(Teuchos::rcp(new Epetra_Map(ocp->control->phi.size(),0,Comm)))
//, space_y_bar_i_(Teuchos::rcp(new TSFCore::EpetraVectorSpace(y_bar_map)))
//, y_bar_i_(space_y_bar_i_->createMember())
//, lambda_bar_ip1_(space_y_bar_i_->createMember())
//, y_i_(space_y_bar_i_->createMember())
//, lambda_i_(space_y_bar_i_->createMember())
//, z_i_(space_y_bar_i_->createMember())
//, eta_i_(space_y_bar_i_->createMember())
  , dgm_ocp(ocp), dgm_lin_ocp(lin_ocp)
{
  using Teuchos::rcp;
  using Teuchos::RefCountPtr;

  std::cout<<"Constructing CTOCPdgm() object..."<<std::endl;

  // need to declare State and Adjoint spaces and endow with scalar products

  RefCountPtr<TSFCore::EpetraVectorSpace>
    space_y_bar_i = rcp(new TSFCore::EpetraVectorSpace(y_bar_map));
#ifndef DGM_NO_USE_STATE_SCALAR_PROD
  space_y_bar_i->setScalarProd
    (rcp(new TSFCore::DGMStateScalarProd(rcp(this,false),
                                         &(dgm_ocp->state->domain()->Ut),
                                         &(dgm_ocp->adjoint->domain()->Ut))));
#endif
  space_y_bar_i_ = space_y_bar_i;

  y_bar_i_ = space_y_bar_i_->createMember();
  lambda_bar_ip1_ = space_y_bar_i_->createMember();
  y_i_ = space_y_bar_i_->createMember();
  lambda_i_ = space_y_bar_i_->createMember();
  z_i_ = space_y_bar_i_->createMember();
  eta_i_ = space_y_bar_i_->createMember();

  // need to declare Control space and endow with a scalar product

  RefCountPtr<TSFCore::EpetraVectorSpace>
    space_u_bar_i = rcp(new TSFCore::EpetraVectorSpace(u_bar_map));
#ifndef DGM_NO_USE_CONTROL_SCALAR_PROD
  // endow space with a custom Scalar Product
  space_u_bar_i->setScalarProd(
    rcp(new TSFCore::DGMControlScalarProd(rcp(this,false))));
#endif
  space_u_bar_i_ = space_u_bar_i;

  u_bar_i_ = space_u_bar_i_->createMember();

  Nt_ = dgm_ocp->control->get_npredict();

  // make storage for the gradient
  gradient.reset( dgm_ocp->control->clone() ); 
  gradient->control_type(Control::GRADIENT);
  gradient->zero();

  lin_gradient.reset( dgm_lin_ocp->control->clone() ); 
  lin_gradient->control_type(Control::GRADIENT);
  lin_gradient->zero();

  direction.reset( dgm_ocp->control->clone() ); 
  direction->control_type(Control::STEP);
  direction->zero();

  lin_direction.reset( dgm_lin_ocp->control->clone() ); 
  lin_direction->control_type(Control::STEP);
  lin_direction->zero();

  dgm_ocp->state->initialize();
  dgm_ocp->control->initialize();
  dgm_ocp->adjoint->initialize();

  dgm_lin_ocp->state->initialize();
  dgm_lin_ocp->control->initialize();
  dgm_lin_ocp->adjoint->initialize();
}

Teuchos::RefCountPtr<const TSFCore::VectorSpace<CTOCPdgm::Scalar> >
CTOCPdgm::space_y_bar_i() const
{
  return space_y_bar_i_;
}

Teuchos::RefCountPtr<const TSFCore::VectorSpace<CTOCPdgm::Scalar> >
CTOCPdgm::space_u_bar_i() const
{
  return space_u_bar_i_;
}

void CTOCPdgm::computeState(
   const TSFCore::Vector<Scalar>   *y_bar_i
   ,const TSFCore::Vector<Scalar>  &u_bar_i
   ,TSFCore::Vector<Scalar>        *y_i_tjp1_out
   )
{
  std::cout<<"CTOCPdgm::computeState() for i = "<<i_<<std::endl;
  dgm_ocp->state->set_iter(i_);
  if (y_bar_i==NULL) {
    dgm_ocp->state->set_initial_condition();
  } else {
    dVector tmp( y_bar_i->space()->dim() );
    copy( *y_bar_i, tmp );
    dgm_ocp->state->set_initial_condition(tmp, t_i_, n_i_);
  }
  copy( u_bar_i, dgm_ocp->control->phi );
  J = dgm_ocp->state->compute( Nt_, dgm_ocp->control );
  if(y_i_tjp1_out) {
    dVector tmp( y_i_tjp1_out->space()->dim() );
    dgm_ocp->state->domain()->U.extract(tmp);
    copy( tmp, *y_i_tjp1_out );
  }
  numStateTimeSteps_ += Nt_;
}

// assumes that computeState has been called
CTOCPdgm::Scalar CTOCPdgm::computeObjective(bool terminal) {
  // WARNING:  This currently doesn't work for distributed observation
  if (terminal) return J;
  return 0.0;
}

void CTOCPdgm::computeAdjoint(
  const TSFCore::Vector<Scalar>    *lambda_bar_ip1
  ,TSFCore::Vector<Scalar>         *lambda_i_tj
  )
{
  std::cout<<"CTOCPdgm::computeAdjoint() for i = "<<i_<<std::endl;
  dgm_ocp->state->set_iter(i_);
  dgm_ocp->adjoint->set_iter(i_);
  if (lambda_bar_ip1==NULL)
    dgm_ocp->adjoint->set_end_condition();
  else {
    dVector tmp( lambda_bar_ip1->space()->dim() );
    copy( *lambda_bar_ip1, tmp );
    dgm_ocp->adjoint->set_end_condition(tmp, t_ip1_, n_i_ + Nt_);
  }
  dgm_ocp->adjoint->compute( Nt_, dgm_ocp->control, gradient );
  if(lambda_i_tj) {
    dVector tmp( lambda_i_tj->space()->dim() );
    dgm_ocp->adjoint->domain()->U.extract(tmp);
    copy( tmp, *lambda_i_tj );
  }
  numAdjointTimeSteps_ += Nt_;
}

void CTOCPdgm::computeGrad(
  TSFCore::Vector<Scalar>          *g_bar_i
  ) const
{
  //cout<<"CTOCPdgm::computeGrad()"<<endl;
  //cout<<"Dimension of g "<<g_bar_i->space()->dim()<<endl;
  //cout<<"Dimension of gradient "<<gradient->size()<<endl;

  std::cout<<"\n||Grad(J)|| = "<<sqrt(gradient->norm())<<std::endl;
  copy( gradient->phi, *g_bar_i );

  //cout<<"norm_2(g_bar_i) "<< norm_2(*g_bar_i) << endl;
  //cout<<"gradient->norm() " << sqrt(gradient->norm()) << endl;

  numGradTimeSteps_ += Nt_;
}

CTOCPdgm::Scalar CTOCPdgm::applyGrad
( const TSFCore::Vector<Scalar> *g_bar_i,
  const TSFCore::Vector<Scalar> *delta_u_bar_i )
  const
{
  // std::cout<<"CTOCPdgm::applyGrad()"<<std::endl;
  copy( *g_bar_i, gradient->phi );
  copy( *delta_u_bar_i, direction->phi );
  return direction->inner_product( gradient.get() );
}


void CTOCPdgm::computeLinState(
    const TSFCore::Vector<Scalar>    *delta_y_bar_i
    ,const TSFCore::Vector<Scalar>   &delta_u_bar_i
    ,TSFCore::Vector<Scalar>         *z_i_tjp1_out
    )
{
  std::cout<<"CTOCPdgm::computeLinState() for i = "<<i_<<std::endl;
  dgm_lin_ocp->state->set_iter(i_);
  // setup the initial condition
  if (delta_y_bar_i==NULL) {
    dgm_lin_ocp->state->set_initial_condition();
  } else {
    //cout<<"Making tmp("<<delta_y_bar_i->space()->dim()<<") dVector"<<endl;
    dVector tmp( delta_y_bar_i->space()->dim() );
    copy( *delta_y_bar_i, tmp );
    dgm_lin_ocp->state->set_initial_condition(tmp, t_i_, n_i_);
  }
  // setup the control
  copy( delta_u_bar_i, dgm_lin_ocp->control->phi );

  // evaluate norms to see if a computation is required
  double norm_y = vField::L2_norm(dgm_lin_ocp->state->domain()->U);
  double norm_u = dgm_lin_ocp->control->norm();
  std::cout<<"||delta_y_bar_i|| = "<<norm_y
           <<"\n||delta_u_bar_i|| = "<<norm_u<<std::endl;
  J = dgm_lin_ocp->state->compute( Nt_, dgm_lin_ocp->control );
  if(z_i_tjp1_out) {
    //cout<<"Making tmp("<< z_i_tjp1_out->space()->dim()<<") dVector"<<endl;
    dVector tmp( z_i_tjp1_out->space()->dim() );
    dgm_lin_ocp->state->domain()->U.extract(tmp);
    copy( tmp, *z_i_tjp1_out );
  }
  numLinStateTimeSteps_ += Nt_;
}


void CTOCPdgm::computeLinAdjoint(
    const TSFCore::Vector<Scalar>    &delta_u_bar_i
    ,const TSFCore::Vector<Scalar>   *delta_lambda_bar_ip1
    ,TSFCore::Vector<Scalar>         *eta_i_tj
    )
{
  std::cout<<"CTOCPdgm::computeLinAdjoint() for i = "<<i_<<std::endl;
  dgm_lin_ocp->state->set_iter(i_);
  dgm_lin_ocp->adjoint->set_iter(i_);
  if (delta_lambda_bar_ip1==NULL)
    dgm_lin_ocp->adjoint->set_end_condition();
  else {
    dVector tmp( delta_lambda_bar_ip1->space()->dim() );
    copy( *delta_lambda_bar_ip1, tmp );
    dgm_lin_ocp->adjoint->set_end_condition(tmp, t_ip1_, n_i_ + Nt_);
  }
  // setup the control
  copy( delta_u_bar_i, dgm_lin_ocp->control->phi );

  // evaluate norms to see if a computation is required
  //double norm_lambda = vField::L2_norm(dgm_lin_ocp->adjoint->domain()->U);
  //double norm_u = dgm_lin_ocp->control->norm();
  //std::cout<<"||delta_lambda_bar_ip1|| = "<<norm_lambda
  //   <<"\n||delta_u_bar_i|| = "<<norm_u<<std::endl;
  //  if (norm_lambda!=0 || norm_u!=0) {
  dgm_lin_ocp->adjoint->compute( Nt_, dgm_lin_ocp->control, lin_gradient );
  numLinAdjointTimeSteps_ += Nt_;
  //  } else
  //    lin_gradient->zero();
  if(eta_i_tj) {
    //cout<<"Making tmp("<< y_i_tjp1_out->space()->dim()<<") dVector"<<endl;
    dVector tmp( eta_i_tj->space()->dim() );
    dgm_lin_ocp->adjoint->domain()->U.extract(tmp);
    copy( tmp, *eta_i_tj );
  }
}


void CTOCPdgm::computeLinGrad(
    const TSFCore::Vector<Scalar>    &delta_u_bar_i
    ,TSFCore::Vector<Scalar>         *delta_g_bar_i
    ) const
{
  static Format sci(8); sci.scientific().width(15);
  // cout<<"CTOCPdgm::computeLinGrad()"<<endl;
  // cout<<"Dimension of delta_g "<<delta_g_bar_i->space()->dim()<<endl;
  // cout<<"Dimension of lin_gradient "<<lin_gradient->size()<<endl;
  copy( lin_gradient->phi, *delta_g_bar_i );
  //cout<<"norm_2(delta_g_bar_i) "<< norm_2(*delta_g_bar_i) << endl;
  std::cout<<"\n||lin_Grad(J)|| = "<<sci(sqrt(lin_gradient->norm()))
           <<std::endl;
  numLinGradTimeSteps_ += Nt_;
}


CTOCPdgm::Scalar CTOCPdgm::applyLinGrad(
  const TSFCore::Vector<Scalar> *delta_g_bar_i,
  const TSFCore::Vector<Scalar> *delta_delta_u_bar_i ) const
{
  //std::cout<<"CTOCPdgm::applyLinGrad()"<<std::endl;
  copy( *delta_g_bar_i, lin_gradient->phi );
  copy( *delta_delta_u_bar_i, lin_direction->phi );
  return lin_direction->inner_product( lin_gradient.get() );
}

// TTD:  need to implement readControl, printState, printAdjoint

void CTOCPdgm::printControl(
  const int N, const TSFCore::Vector<Scalar>*  u_bar[], std::ostream &out)
  const {
  for (int i=0; i<N; ++i) {
    std::cout <<"CTOCPdgm::printControl(...) for i="<<i<<std::endl;
    copy( *u_bar[i], dgm_ocp->control->phi );
    plotControl(1,i);
    writeRestart(i);
  }
}

void CTOCPdgm::readControl(std::istream &, const int N,
                           TSFCore::Vector<Scalar>*  u_bar[] ) const {
  for (int i=0; i<N; ++i) {
    std::cout <<"CTOCPdgm::readControl(...) for i="<<i<<std::endl;
    dgm_ocp->control->phi = 0;
    const_cast<CTOCPdgm*>(this)->readRestart(i);
    copy( dgm_ocp->control->phi, *u_bar[i] );
  }
}

void CTOCPdgm::writeControl(std::ostream &, const int N,
                            TSFCore::Vector<Scalar>*  u_bar[] ) const {
  for (int i=0; i<N; ++i) {
    std::cout <<"CTOCPdgm::writeControl(...) for i="<<i<<std::endl;
    copy( *u_bar[i], dgm_ocp->control->phi );
    writeRestart(i);
  }
}

//  DGM specific helper methods

#include <time.h>

void CTOCPdgm::writeRestart(int i) const {
  int skip=0;
  char tmp[80];
  sprintf(tmp,"%s.%d.ctl", dgm_ocp->control->root.c_str(), i);
  string fname(tmp);
  //string fname = dgm_ocp->control->root+".ctl";
  std::cout <<"Writing control restart "<<fname<<std::endl;
  // Write the header
  const int width = 40;
  time_t tp = time(0); // get the current date and time from <time.h>
  char now[128];
  strftime(now,128,"%a %b %d %H:%M:%S %Y", localtime(&tp));
  ofstream res_out(fname.c_str());
  res_out.setf(ios::left);
  res_out<<setw(width)<<now<<" Created"<<endl;
  res_out<<setw(width)<<fname.c_str()<<" Name"<<endl;
  res_out<<endl;
  res_out<<endl;
  res_out<<endl;
  res_out<<endl;
  skip = res_out.tellp(); // get the header length (in bytes)
  res_out.close();
  skip = dgm_ocp->control->write(fname,skip);
}

void CTOCPdgm::readRestart(int i) {
  int skip=0;
  string buf;
  char tmp[80];
  sprintf(tmp,"%s.%d.ctl", dgm_ocp->control->root.c_str(), i);
  string fname(tmp);
  ifstream res_in(fname.c_str());
  if (!res_in) return;
  std::cout <<"Reading control restart "<<fname<<std::endl;
#if 0
  // Read the header
  getline(res_in,buf);  // read the date
  if (!(res_in>>buf)) error("Cannot read restart name",1);
  getline(res_in,buf);
#else
  // Read the header
  getline(res_in,buf);
  getline(res_in,buf);
  getline(res_in,buf);
  getline(res_in,buf);
  getline(res_in,buf);
  getline(res_in,buf);
#endif
  skip = res_in.tellg(); // get the header length (in bytes)
  skip = dgm_ocp->control->read(fname,skip);
}

void CTOCPdgm::plotControl(const int ntout, const int iter) const {
  dgm_ocp->control->plot( ntout, iter);
}

} // TDD namespace
