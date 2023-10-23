#ifndef DGM_OBJFUNC_HPP
#define DGM_OBJFUNC_HPP

/** \file ObjFunc.hpp
    \brief Objective function class that holds Objectives and Controls
    \author Scott Collis
*/

// standard libraries
#include <string>
using namespace std;

// DGM includes
#include "Comm.hpp"
#include "Types.hpp"
#include "Control.hpp"
#include "Objective.hpp"
#include "Format.hpp"

namespace DGM {

class TimeInfo {
  Ordinal _istep;
  Ordinal _sstep;
  Scalar  _time;
public:
  TimeInfo() : _istep(0), _sstep(0), _time(0) {}
  Ordinal istep() const { return _istep; }
  void istep(const Ordinal istep) { _istep=istep; }
  Ordinal sstep() const { return _sstep; }
  void sstep(const Ordinal sstep) { _sstep=sstep; }
  Scalar time() const { return _time; }
  void time(const Scalar time) { _time=time; }
  void set(const Scalar time, const Ordinal istep, const Ordinal sstep=0) {
    _time=time;  _istep=istep; _sstep=sstep;
  }
};

/// Defines the complete objection function
/** Includes the Objective (i.e. all observations) and Control (i.e. all
    regularizations) for a complete objective function and provides methods
    that execute on all of these objects

    \todo Refactor the time-regularization implementation

    \note The use of raw pointers here means that this class has no
    responsibility to delete the Control or Objective objects.
*/
class ObjFunc : public DTK::ObjFunc<Scalar,Ordinal,vField> {

  Control *control;          ///< the Control database (i.e. regularizations)
  Objective *objective;      ///< the Objective database (i.e. observations)

  const DGM::Comm::Ptr comm; ///< parallel communicator

#ifdef DGM_USE_TIME_REG
#error "Time regularization has not be updated to use inline integration,\n"\
"consult DGM r4995 and prior versions for deprecated code."
#endif

  TimeInfo timeInfo;        ///< Time step information

  dVector terms_;           ///< value of each term in the objective function
  dVector tterms_;          ///< value of each term in the objective function

  /// Initializer helper method for constructors
  void initialize() {
    const Ordinal nterms =
      numeric_cast<Ordinal>(control->num_ctrl() + objective->num_obs());
    objective->reset_costs();
    control->reset_costs();
    terms_.resize(nterms);
    terms_ = 0.0;
    tterms_.resize(nterms);
    tterms_ = 0.0;
  }

public:

  typedef DGM::Shared<ObjFunc>::Ptr Ptr;        ///< shared pointer type

  /// default constructor
  ObjFunc() : control(0), objective(0), comm(), timeInfo() {}

  /// clone method
  void clone(const ObjFunc &in) {
    control = in.control;
    objective = in.objective;
    const_cast<DGM::Comm::Ptr&>(comm) = in.comm;
    timeInfo = in.timeInfo;
    terms_.resize(in.terms_.size()); terms_ = in.terms_;
    tterms_.resize(in.tterms_.size()); tterms_ = in.tterms_;
  }

  /// constructor taking shared pointers
  ObjFunc( Control::Ptr c, Objective::Ptr o,
           const DGM::Comm::Ptr comm_ = DGM::Comm::World ) :
    control(c.get()), objective(o.get()), comm(comm_), timeInfo() {
    initialize();
  }

  /// constructor taking raw pointers (should be deprecated)
  ObjFunc( Control* c, Objective* o,
           const DGM::Comm::Ptr comm_ = DGM::Comm::World ) :
    control(c), objective(o), comm(comm_), timeInfo() {
    initialize();
  }

  /// constructor taking one shared pointer (should be removed)
  ObjFunc( Control::Ptr c, Objective* o,
           const DGM::Comm::Ptr comm_ = DGM::Comm::World ) :
    control(c.get()), objective(o), comm(comm_), timeInfo() {
    initialize();
  }

  /// construction from a reference does a deep copy on dVectors
  ObjFunc(const ObjFunc &x) :
      control(x.control), objective(x.objective), comm(x.comm),
      timeInfo(x.timeInfo), terms_(x.terms_.size(),0.0),
      tterms_(x.tterms_.size(),0.0) {}

  /// construction from a pointer does a shallow copy on dVectors
  ObjFunc(const ObjFunc *x) :
      control(x->control), objective(x->objective), comm(x->comm),
      timeInfo(x->timeInfo), terms_(x->terms_), tterms_(x->tterms_) {}

  /// get the timestep
  Scalar dt() const { assert(control!=0); return control->get_dt(); }

  /// get npredict
  Ordinal npredict() const {
    assert(control!=0);
    return control->get_npredict();
  }

  /// Returns a vector of names for each term in the objective functional
  vector<string> names() const {
    vector<string> obs_names = objective->names();
    vector<string> ctrl_names = control->names();
    vector<string> names = ctrl_names;
    for (size_t i=0; i<obs_names.size(); ++i) {
      names.push_back(obs_names[i]);
    }
    return names;
  }

  /** Evaluate objective function at a given time step and substep. */
  virtual Scalar evaluate(const vField &S, const Ordinal istep,
                          const Ordinal sstep=0 ) {
    Scalar result(0.0);
    result += objective->cost( S, istep, sstep );
    result += control->cost( istep, sstep );
    //cout << "istep = "<<istep<<", sstep = "<<sstep<<" obj = "<<result<<endl;
    return result;
  }

  /// Function evaluator for time integration
  /** Evaluates in place. */
  void operator()(const vField &S, const Ordinal istep,
                  const Ordinal sstep=0, const Scalar sign=1.0 ) {
    evaluate(S,istep,sstep);
    dVector ctrl_terms, obs_terms;
    const Ordinal numCtrl = numeric_cast<Ordinal>(control->num_ctrl());
    const Ordinal numObs = numeric_cast<Ordinal>(objective->num_obs());
    ctrl_terms.alias(terms_,0,numCtrl);
    obs_terms.alias(terms_,numCtrl,numObs);
    ctrl_terms = control->get_costs();
    ctrl_terms.Mul(sign);
    obs_terms  = objective->get_costs();
    obs_terms.Mul(sign);
  }

  /// \name Provide DTK::TimeIntegrate interface
  //@{
  /// Must be called before time_derivative
  void prestep( dVector &, const Ordinal istep, const Ordinal sstep,
                const Scalar time) { timeInfo.set(time,istep,sstep); }
  /// Must be called after time_derivative
  void poststep( dVector &, const Ordinal, const Ordinal, const Scalar ) {}
  /// Evaluate the (negative) time derivative (time integrand)
  void time_derivative(const vField &S, dVector &R) {
    const Ordinal istep = timeInfo.istep();
    const Ordinal sstep = timeInfo.sstep();
    evaluate(S,istep,sstep);
    dVector ctrl_terms, obs_terms;
    const Ordinal numCtrl = numeric_cast<Ordinal>(control->num_ctrl());
    const Ordinal numObs = numeric_cast<Ordinal>(objective->num_obs());
    ctrl_terms.alias(R,0,numCtrl);
    obs_terms.alias(R,numCtrl,numObs);
    ctrl_terms = control->get_costs();
    ctrl_terms.Mul(-1.0);
    obs_terms  = objective->get_costs();
    obs_terms.Mul(-1.0);
  }
  dVector & getU() { return terms_; }
  dVector & getUt() { return tterms_; }
  //@}

  /// evaluate the terminal condition if istep==npredict
  virtual Scalar terminal(const vField &S, const Ordinal istep,
                          const Ordinal sstep=0) {
    Scalar result(0.0);
    if(istep==npredict()) result += objective->terminal_cost( S, istep );
    return result;
  }

  /// add in the terminal condition
  virtual void add_terminal(const vField &S) {
    terminal(S,npredict());
    dVector obs_terms;
    const Ordinal numCtrl = numeric_cast<Ordinal>(control->num_ctrl());
    const Ordinal numObs = numeric_cast<Ordinal>(objective->num_obs());
    obs_terms.alias(terms_,numCtrl,numObs);
    obs_terms.AddScale(one,objective->get_costs());
  }

  /// constant value accessor
  Scalar value() const { return terms_.Sum(); }

  /// zero the terms
  void zero() { terms_ = 0; }

  /// constant term accessor
  const dVector &terms() const { return terms_; }

  /// term accessor
  dVector &terms() { return terms_; }

  /// return the size (number of terms) in this objective function
  Ordinal size() const { return terms_.size(); }

  /// globalize the values
  void globalize() {
    dVector lterms(terms_.size()); lterms = terms_;
    comm->SumAll(lterms.ptr(), terms_.ptr(), numeric_cast<int>(terms_.size()));
  }

  /// \name Linear algebra on ObjFunc
  //@{
  /// Scale an objective functional
  inline friend void scale( const Scalar a, ObjFunc &x );
  /// Add a scaled objective functional
  inline friend void axpy(const Scalar a, const ObjFunc &x, ObjFunc &y);
  /// Add a scaled objective functional
  inline friend void axpy(const Scalar a, const ObjFunc &x, const ObjFunc &y,
                          ObjFunc &z);
  //@}

  /// stream output method
  inline friend std::ostream & operator<<(std::ostream &, const ObjFunc &);

};  // class ObjFunc

//=============================================================================
//                       I m p l e m e n t a t i o n
//=============================================================================

/// output ObjFunc to a stream
inline std::ostream & operator<<(std::ostream &os, const ObjFunc &J) {
  J.objective->output_costs(os);
  J.control->output_costs(os);
  return os;
}

inline void scale( const Scalar a, ObjFunc &x ) {
  x.terms_.Mul(a);
}

inline void axpy(const Scalar a, const ObjFunc &x, ObjFunc &y) {
  y.terms_.AddScale(a,x.terms_);
}

inline void axpy(const Scalar a, const ObjFunc &x, const ObjFunc &y,
                 ObjFunc &z) {
  z.terms_.ScaleAdd(a,x.terms_,y.terms_);
}

} // namespace DGM

#endif  // DGM_OBJFUNC_HPP
