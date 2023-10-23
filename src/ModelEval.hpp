#ifndef DGM_MODELEVAL_HPP
#define DGM_MODELEVAL_HPP

/*============================================================================
  Module:     DGM ModelEvaluator

  Authors:    S. Scott Collis

  Copyright:  Sandia National Laboratories
              Albuquerque, NM 87175-0321
              (505) 284-1123
              sscoll@sandia.gov
=============================================================================*/

/** \file ModelEval.hpp
    \brief Declarations for a Thyra::ResponseOnlyModelEvaluator for DGM
    \author Scott Collis
*/

// Trilinos includes
#include "Thyra_ResponseOnlyModelEvaluatorBase.hpp"
#include "Thyra_SpmdVectorSpaceDefaultBase.hpp"

// DGM includes
#include "Comm.hpp"

namespace DGM {

// forward declarations
class OptProblem;
class Optimizer;

using Teuchos::RCP;

/** \brief Defines a scalar product for Control. */
class ControlScalarProd : public Thyra::ScalarProdBase<Scalar> {

  const DGM::Comm::Ptr dgm_comm;   ///< DGM parallel communicator

  const Optimizer *optimizer;      ///< DGM::Optimizer for this problem

public:

  /// Constructor
  ControlScalarProd( const Optimizer *opt, const DGM::Comm::Ptr comm ) :
    dgm_comm(comm), optimizer(opt) { }

private:

  /** \brief This scalar project is not Euclidean */
  virtual bool isEuclideanImpl() const {
    return false;
  }

  /** \brief This is implemented using the Control::inner_product() method */
  virtual void scalarProdsImpl
  (
   const Thyra::MultiVectorBase<Scalar>& X,
   const Thyra::MultiVectorBase<Scalar>& Y,
   const Thyra::ArrayView<Scalar> &scalarProds_out ) const;
};

/** \brief Simple parallel response-only ModelEvaluator.for DGM. */
class ModelEval
   : public Thyra::ResponseOnlyModelEvaluatorBase<Scalar> {

public:

  /** \name Constructors, Initialization, Misc. */
  //@{
  /// Constructor
  ModelEval(OptProblem *ocp);
  //@}
  /** \name Public functions overridden from ModelEvaluator. */
  //@{
  /// Number of parameters
  int Np() const;

  /// Number of responses
  int Ng() const;

  /// Returns the InArgs with initial guess for the model parameters
  Thyra::ModelEvaluatorBase::InArgs<Scalar> getNominalValues() const;

  /// Returns the vector space for the parameters
  RCP<const Thyra::VectorSpaceBase<Scalar> > get_p_space(int l) const;

  /// Returns the vector space for the responses
  RCP<const Thyra::VectorSpaceBase<Scalar> > get_g_space(int j) const;

  /// Tells the Model Evaluator what inputs are supported
  Thyra::ModelEvaluatorBase::InArgs<Scalar> createInArgs() const;
  //@}
private:

  /** \name Private functions overridden from ModelEvaluatorDefaultBase. */
  //@{
  /// Tells the Model Evaluator what outputs are supported
  Thyra::ModelEvaluatorBase::OutArgs<Scalar> createOutArgsImpl() const;

  /// This is the actual evaluation implementation
  void evalModelImpl(
    const Thyra::ModelEvaluatorBase::InArgs<Scalar>& inArgs,
    const Thyra::ModelEvaluatorBase::OutArgs<Scalar>& outArgs
    ) const;
  //@}
private:

  /** \name Private data members */
  //@{
  int Np_;   ///< the number of parameters
  int Ng_;   ///< the number of responses

  /// Parameter vector space
  RCP<Thyra::SpmdVectorSpaceDefaultBase<Scalar> > p_space_;

  /// parameter vector space
  RCP<const Thyra::VectorSpaceBase<Scalar> > g_space_;
  //@}

  /** \name DGM specific data members */
  //@{
  OptProblem *ocp;              ///< DGM optimization Problem

  const Comm::Ptr dgm_comm;     ///< parallel communicator
  //@}
};

} // namespace DGM


#endif // DGM_MODELEVAL_HPP
