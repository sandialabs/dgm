#ifndef TDD_CTOCP_DGM_HPP
#define TDD_CTOCP_DGM_HPP

#include "OptProblem.hpp"

// TDD
#include "CTOCP.hpp"

// Epetra
#ifdef DGM_PARALLEL
#include "Epetra_MpiComm.h"
#else
#include "Epetra_SerialComm.h"
#endif
#include "Epetra_Map.h"
#include "Epetra_Vector.h"

// TSFCore
#include "TSFCoreEpetraVectorSpace.hpp"
#include "TSFCoreEpetraVector.hpp"
#include "TSFCoreEpetraLinearOp.hpp"

#include "TSFCoreSerialVectorSpace.hpp"
#include "TSFCoreExplicitVectorView.hpp"

/// Time-Domain-Decomposition
namespace TDD {

///  Continuous-Time Optimal-Control Problem
/** Subclass of <tt>CTOCP</tt> interfacing to dgm solve
 *
 * ToDo: Finish documentation!
*/
  class CTOCPdgm : public CTOCP<double> {

public:

  typedef double Scalar;

  ///
  /** Constructor.
   *
   */
  CTOCPdgm(int i, int n_i, Scalar t_i, Scalar t_ip1,
           const Epetra_Comm &,
           OptProblem *ocp, OptProblem *locp);

  /** @name Overridden from CTOCP. */
  //@{

  ///
  Teuchos::RefCountPtr<const TSFCore::VectorSpace<Scalar> >
     space_y_bar_i() const;
  ///
  Teuchos::RefCountPtr<const TSFCore::VectorSpace<Scalar> >
     space_u_bar_i() const;
  ///
  void computeState(
    const TSFCore::Vector<Scalar>    *y_bar_i
    ,const TSFCore::Vector<Scalar>   &u_bar_i
    ,TSFCore::Vector<Scalar>         *y_i_t_ip1
    );
  ///
  Scalar computeObjective(bool terminal);
  ///
  void computeAdjoint(
    const TSFCore::Vector<Scalar>    *lambda_bar_ip1
    ,TSFCore::Vector<Scalar>         *lambda_i_t_i
    );
  ///
  void computeGrad(
    TSFCore::Vector<Scalar>          *g_bar_i
    ) const;
  ///
  Scalar applyGrad( const TSFCore::Vector<Scalar> *g_bar_i,
                    const TSFCore::Vector<Scalar> *delta_u_bar_i ) const;
  ///
  void computeLinState(
    const TSFCore::Vector<Scalar>    *delta_y_bar_i
    ,const TSFCore::Vector<Scalar>   &delta_u_bar_i
    ,TSFCore::Vector<Scalar>         *z_i_t_ip1
    );
  ///
  void computeLinAdjoint(
    const TSFCore::Vector<Scalar>    &delta_u_bar_i
    ,const TSFCore::Vector<Scalar>   *delta_lambda_bar_ip1
    ,TSFCore::Vector<Scalar>         *eta_i_t_i
    );
  ///
  void computeLinGrad(
    const TSFCore::Vector<Scalar>    &delta_u_bar_i
    ,TSFCore::Vector<Scalar>         *delta_g_bar_i
    ) const;
  ///
  Scalar applyLinGrad( const TSFCore::Vector<Scalar> *delta_g_bar_i,
                       const TSFCore::Vector<Scalar> *delta_delta_u_bar_i )
    const;
  ///
  void resetCounters() {
    numStateTimeSteps_ = numAdjointTimeSteps_
      = numGradTimeSteps_ = numLinStateTimeSteps_
      = numLinAdjointTimeSteps_ = numLinGradTimeSteps_
      = 0;
  }
  ///
  int numStateTimeSteps() const { return numStateTimeSteps_; }
  ///
  int numAdjointTimeSteps() const { return numAdjointTimeSteps_; }
  ///
  int numGradTimeSteps() const { return numGradTimeSteps_; }
  ///
  int numLinStateTimeSteps() const { return numLinStateTimeSteps_; }
  ///
  int numLinAdjointTimeSteps() const { return numLinAdjointTimeSteps_; }
  ///
  int numLinGradTimeSteps() const { return numLinGradTimeSteps_; }

  void printControl( const int N, const TSFCore::Vector<Scalar>* u_bar_i[],
                     std::ostream &out ) const;

  void readControl( std::istream &in, const int N,
                    TSFCore::Vector<Scalar>* u_bar_i[] ) const;

  void writeControl( std::ostream &in, const int N,
                     TSFCore::Vector<Scalar>* u_bar_i[] ) const;
  //@}

private:

  // //////////////////////////////////
  // Private types

  typedef TSFCore::ExplicitVectorView<Scalar> evv;
  typedef TSFCore::ExplicitMutableVectorView<Scalar> emvv;

  // //////////////////////////////////
  // Private data members

  Scalar t_i_, t_ip1_; // start time, end time for this time-domain
  int i_, n_i_;  // time domain index, initial step number
  int Nt_;       // number of steps in time-domain

  Teuchos::RefCountPtr<const Epetra_Map> y_bar_map;
  Teuchos::RefCountPtr<const Epetra_Map> u_bar_map;

  Teuchos::RefCountPtr<const TSFCore::VectorSpace<Scalar> > space_y_bar_i_;
  Teuchos::RefCountPtr<const TSFCore::VectorSpace<Scalar> > space_u_bar_i_;

  Teuchos::RefCountPtr<TSFCore::Vector<Scalar> > y_bar_i_;
  Teuchos::RefCountPtr<TSFCore::Vector<Scalar> > u_bar_i_;
  Teuchos::RefCountPtr<TSFCore::Vector<Scalar> > lambda_bar_ip1_;

  Teuchos::RefCountPtr<TSFCore::Vector<Scalar> > y_i_;
  Teuchos::RefCountPtr<TSFCore::Vector<Scalar> > lambda_i_;
  Teuchos::RefCountPtr<TSFCore::Vector<Scalar> > z_i_;
  Teuchos::RefCountPtr<TSFCore::Vector<Scalar> > eta_i_;

  // DGM stuff

  OptProblem *dgm_ocp;     // optimal control problem
  OptProblem *dgm_lin_ocp; // linearized optimal control problem

  Scalar     J, lin_J;
  ControlPtr gradient, lin_gradient, direction, lin_direction;

  mutable int numStateTimeSteps_;
  mutable int numAdjointTimeSteps_;
  mutable int numGradTimeSteps_;
  mutable int numLinStateTimeSteps_;
  mutable int numLinAdjointTimeSteps_;
  mutable int numLinGradTimeSteps_;

  // additional DGM Optimizer-like methods

  ///
  void readRestart(int=0);
  ///
  void writeRestart(int=0) const;
  ///
  void plotControl(const int=1, const int=0) const;

}; // class CTOCPdgm

} // TDD namespace

#endif
