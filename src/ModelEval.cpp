/*=============================================================================
  Module:     DGM ModelEvaluator

  Authors:    S. Scott Collis

  Copyright:  Sandia National Laboratories
              Albuquerque, NM 87175-0321
              (505) 284-1123
              sscoll@sandia.gov
=============================================================================*/

/** \file ModelEval.cpp
    \brief Implementation of a Thyra::ResponseOnlyModelEvaluator for DGM
    \author Scott Collis
*/

// Trilinos includes
#include "Teuchos_DefaultComm.hpp"
#ifdef DGM_PARALLEL
#include "Teuchos_DefaultMpiComm.hpp"
#endif
#include "Teuchos_OpaqueWrapper.hpp"

#include "Thyra_OperatorVectorTypes.hpp"
#include "Thyra_VectorStdOps.hpp"
#include "Thyra_DefaultSpmdVectorSpace.hpp"
#include "Thyra_DetachedSpmdVectorView.hpp"
#include "Thyra_ScalarProdBase.hpp"

// DGM includes
#include "ModelEval.hpp"
#include "OptProblem.hpp"
#include "Format.hpp"
#ifdef DGM_PARALLEL
#include "MpiComm.hpp"
#endif

namespace DGM {

//=============================================================================
//                DGM::ControlScalarProd implementation
//=============================================================================

void ControlScalarProd::scalarProdsImpl
(const Thyra::MultiVectorBase<Scalar> &X,
 const Thyra::MultiVectorBase<Scalar> &Y,
 const Thyra::ArrayView<Scalar> &scalarProds_out ) const {
#if 0
  // steal the Thyra::EuclideanScalarProd
  std::cout << "DGM::ScalarProd::scalarProdsImpl(...) "
            << "needs to be implemented" << std::endl;
  Thyra::dots(X, Y, scalarProds_out);
#else
#if (DGM_MODELEVAL_VERBOSE >= 2)
  std::cout << "DGM::ScalarProd::scalarProdsImpl(...) " << std::endl;
#endif
  // store references to the original storage
  dVector control_copy( optimizer->control->phi );
  dVector gradient_copy( optimizer->gradient->phi );

  assert( X.domain()->dim() == 1 );
  assert( X.domain()->dim() == Y.domain()->dim() );
  assert( scalarProds_out.size() == 1 );

  // loop over the vectors in the MultiVector
  for (int i=0; i< X.domain()->dim(); i++) {
    Thyra::ConstDetachedSpmdVectorView<Scalar> x(X.col(i));
    Thyra::ConstDetachedSpmdVectorView<Scalar> y(Y.col(i));
    assert( x.subDim() == optimizer->control->phi.size() );
    assert( y.subDim() == optimizer->gradient->phi.size() );
    optimizer->control->phi.alias( const_cast<Scalar*>(&(x[0])), x.subDim() );
    optimizer->gradient->phi.alias( const_cast<Scalar*>(&(y[0])), y.subDim() );
    scalarProds_out[i] =
      optimizer->control->inner_product(optimizer->gradient.get());
  }

  // return to the original storage
  optimizer->control->phi.alias( control_copy );
  optimizer->gradient->phi.alias( gradient_copy );
#endif
}

//=============================================================================
//                     DGM::ModelEval implementation
//=============================================================================

// Constructors, Initialization, Misc.

ModelEval::ModelEval(OptProblem *OCP) :
  Np_(1), Ng_(1), ocp(OCP), dgm_comm(ocp->get_comm()) {

#if (DGM_MODELEVAL_VERBOSE >= 2)
  dgm_comm->cout() << "DGM::ModelEval construction" << std::endl;
#endif

#ifdef DGM_PARALLEL
  // use the same communicator as the DGM optimal control problem
  MPI_Comm mpicomm =
    (dynamic_cast<const DGM::MpiComm*>(dgm_comm.get()))->mpicomm();
  const RCP<const Teuchos::OpaqueWrapper<MPI_Comm> > rawMpiComm =
    Teuchos::opaqueWrapper((MPI_Comm)mpicomm);
  const RCP<const Teuchos::Comm<Thyra::Ordinal> > comm =
    Teuchos::createMpiComm<Thyra::Ordinal>(rawMpiComm);
#else
  const RCP<const Teuchos::Comm<Thyra::Ordinal> > comm =
    Teuchos::DefaultComm<Thyra::Ordinal>::getComm();
#endif

  // Parallel space for p
  p_space_ = Thyra::defaultSpmdVectorSpace<Scalar>
    (comm, ocp->control->size(), -1);

  // redefine the scalar product
  p_space_->setScalarProd
    ( Teuchos::rcp(new DGM::ControlScalarProd(ocp->optimizer,dgm_comm)) );

  // Locally replicated space for g
  g_space_ = Thyra::defaultSpmdVectorSpace<Scalar>(comm, 1, 1);

#if (DGM_MODELEVAL_VERBOSE >= 2)
  dgm_comm->cout() << "DGM::ModelEval finished construction" << std::endl;
#endif
}

// Public functions overridden from ModelEvaulator

int ModelEval::Np() const {
  return Np_;
}

int ModelEval::Ng() const {
  return Ng_;
}

Thyra::ModelEvaluatorBase::InArgs<Scalar>
ModelEval::getNominalValues() const {
  dgm_comm->cout() << "DGM::ModelEval::getNominalValues" << std::endl;

  typedef Thyra::ModelEvaluatorBase MEB;
  MEB::InArgs<Scalar> initialGuess = this->createInArgs();

  // Create p vector, fill it with controls, and put it in InArgs
  const Teuchos::RCP<Thyra::VectorBase<Scalar> >
    p = Thyra::createMember<Scalar>(p_space_);
  {
  Thyra::DetachedSpmdVectorView<Scalar> my_p(p);
    for (int i = 0; i < my_p.subDim(); ++i) {
       my_p[i] = ocp->optimizer->control->phi[i];
    }
  }
  initialGuess.set_p(0,p);
  return initialGuess;
}

RCP<const Thyra::VectorSpaceBase<Scalar> >
ModelEval::get_p_space(int l) const {
#ifdef TEUCHOS_DEBUG
  TEUCHOS_ASSERT_IN_RANGE_UPPER_EXCLUSIVE( l, 0, Np_ );
#endif
  return p_space_;
}

RCP<const Thyra::VectorSpaceBase<Scalar> >
ModelEval::get_g_space(int j) const {
#ifdef TEUCHOS_DEBUG
  TEUCHOS_ASSERT_IN_RANGE_UPPER_EXCLUSIVE( j, 0, Ng_ );
#endif
  return g_space_;
}

Thyra::ModelEvaluatorBase::InArgs<Scalar>
ModelEval::createInArgs() const {
  typedef Thyra::ModelEvaluatorBase MEB;
  MEB::InArgsSetup<Scalar> inArgs;
  inArgs.setModelEvalDescription(this->description());
  inArgs.set_Np(Np_);
  return inArgs;
}

// Private functions overridden from ModelEvaulatorDefaultBase

Thyra::ModelEvaluatorBase::OutArgs<Scalar>
ModelEval::createOutArgsImpl() const {
  typedef Thyra::ModelEvaluatorBase MEB;
  typedef MEB::DerivativeSupport DS;
  MEB::OutArgsSetup<Scalar> outArgs;
  outArgs.setModelEvalDescription(this->description());
  outArgs.set_Np_Ng(Np_,Ng_);
  outArgs.setSupports(MEB::OUT_ARG_DgDp, 0 ,0, MEB::DERIV_TRANS_MV_BY_ROW);
  return outArgs;
}

// Implementation

void ModelEval::evalModelImpl(
  const Thyra::ModelEvaluatorBase::InArgs<Scalar>& inArgs,
  const Thyra::ModelEvaluatorBase::OutArgs<Scalar>& outArgs
  ) const {

  static Format sci(8); sci.scientific().width(15);

#if (DGM_MODELEVAL_VERBOSE >= 2)
  dgm_comm->cout() << "DGM::ModelEval::evalModelImpl(...)" << endl;
#endif

  using Teuchos::as;
  using Teuchos::outArg;
  typedef Teuchos::ScalarTraits<Scalar> ST;
  using Thyra::get_mv;
  using Thyra::ConstDetachedSpmdVectorView;
  using Thyra::DetachedSpmdVectorView;
  typedef Thyra::Ordinal Ordinal;
  typedef Thyra::ModelEvaluatorBase MEB;
  typedef MEB::DerivativeMultiVector<Scalar> DMV;

  // Detached is like checking out a copy and then checking it back in on
  // destruction and a Const version doesn't allow you to change the view
  const ConstDetachedSpmdVectorView<Scalar> p(inArgs.get_p(0));

  // put p into DGM control data structure
#ifdef DGM_MODELEVAL_COPY
  // std::cout<<"Stuffing "<<p.subDim()<<" parameters into phi"<< std::endl;
  for (Ordinal i = 0; i < p.subDim(); ++i) {
    ocp->optimizer->control->phi[(int)i] = p[i];
    // std::cout << "i = " << i << " p = " << p[i] << std::endl;
  }
#else
  dVector control_copy( ocp->optimizer->control->phi );
  ocp->optimizer->control->phi.alias( const_cast<Scalar*>(&p[0]), p.subDim() );
#endif

  bool do_adjoint = !outArgs.get_DgDp(0,0).isEmpty();
  bool do_state = !is_null(outArgs.get_g(0));

  if (do_state) {
    Scalar g_val = zero;
    ocp->state->set_initial_condition();
    if (do_adjoint) {
      ocp->state->save();
      g_val = ocp->state->compute(ocp->optimizer->get_npredict(),ocp->control);
    } else {
      ocp->state->no_save();
      g_val = ocp->state->test(ocp->optimizer->get_npredict(), ocp->control);
    }
    DetachedSpmdVectorView<Scalar>(outArgs.get_g(0))[0] = g_val;
  }

  if (do_adjoint) {
    if (!do_state) {
      ocp->state->set_initial_condition();
      ocp->state->save();
      Scalar g_val = ocp->state->compute(ocp->optimizer->get_npredict(),
                                         ocp->control);
    }
    ocp->adjoint->set_end_condition();
    ocp->adjoint->compute( ocp->optimizer->get_npredict(), ocp->control,
                           ocp->optimizer->gradient, 1 );

#if (DGM_MODELEVAL_VERBOSE >= 2)
    Scalar total_g2 = ocp->optimizer->gradient->norm();
    dgm_comm->cout() <<"||Grad(J)||^2 = " << sci(total_g2) << endl;
    dgm_comm->cout() <<"||Grad(J)||   = " << sci(sqrt(total_g2)) << endl;
#endif

    const RCP<Thyra::MultiVectorBase<Scalar> > DgDp_trans_mv =
      get_mv<Scalar>(outArgs.get_DgDp(0,0), "DgDp^T",
                     MEB::DERIV_TRANS_MV_BY_ROW);
    const DetachedSpmdVectorView<Scalar> DgDp_grad(DgDp_trans_mv->col(0));
    for (Ordinal i = 0; i < p.subDim(); ++i) {
      DgDp_grad[i] = ocp->optimizer->gradient->phi[(int)i];
    }
  }

#ifndef DGM_MODELEVAL_COPY
  ocp->optimizer->control->phi.alias( control_copy );
#endif

}

} // namespace DGM
