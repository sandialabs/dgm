#ifndef DGM_OBS_HPP
#define DGM_OBS_HPP

/** \file Obs.hpp
    \brief Obs(ervation) base class declaration
*/

// DTK includes
#include "DTK.hpp"

// DGM includes
#include "Types.hpp"
#include "vField.hpp"

namespace DGM {

/// Abstract concept of an observation within an objective functional
/** The basic idea is that the Obs class is the interface to the
    implementation of an observation term in DGM.  Any object that you
    would like to serve as an observaton term within an objective
    functional should derive off of the Obs class and provide the required
    interface.  For example, a distributed observation would derive off of
    both a Source (for an Adjoint source term) and Obs (for a State
    observation).

    The Obs can be both distributed in time as well as terminal in time.
    If it supportes a terminal cost, then it must also implement an
    end_condition for use by the Adjoint.

    Note that the Obs objects are stored and managed by the Objective class
    analogous to the Control class which holds Ctrl objects.
*/
class Obs : public DTK::Obs<vField,dVector,Scalar,Ordinal> {

 protected:

  Scalar penalty;  ///< Penalty for this observation term
  Ordinal ndof;    ///< Number of degrees of freedom
  
 public:
  /// Constructor
  /** @param[in] p penalty factor for this observation (defaults to 0)
      @param[in] n number of degrees of freedom (defaults to 0)
   */
  Obs(const Scalar p=0, const Ordinal n=0) : penalty(p), ndof(n) {}
  virtual ~Obs() {};
  /// Initialize this observation
  virtual void initialize() = 0;
  /// Set the Obs data on a given vField at a give timestep (and substep)
  /** @param[in] U State to observe
      @param[in] step time step
      @param[in] sstep substep for RK methods (optional)
    */
  virtual void set_data(const vField &U, const Ordinal step, 
                        const Ordinal sstep=0) = 0;
  /// Apply the end condition to the Adjoint
  /** @param[in] A Adjoint vField on which to apply the end-condition
    */
  virtual void end_condition( vField &A ) = 0;
  /// Compute the norm of this observation (in space-time)
  virtual Scalar norm() const = 0;
  /// Returns 1/2*penalty*norm(). Override to measure cost differently.
  virtual Scalar cost() const { return pt5*penalty*norm(); }
  /// Override to provide a terminal observation (defaults to zero)
  virtual Scalar terminal_cost() const { return zero; }
  /// Reset the objective function
  /** This is useful with the data or parameters of the objective
      functional need to be updated during the solution of an optimization
      problem.  The default is a zero operation so this needs to be
      overriden in a derived class to define a useful action for that
      observation. */
  virtual void reset_obs() {}
  /// Reset the objective function
  /** This is useful with the data or parameters of the objective
      functional need to be updated during the solution of an optimization
      problem.  The default is a zero operation so this needs to be
      overriden in a derived class to define a useful action for that
      observation. */
  virtual void reset_obs( const dVector & ) {}
  /// Returns the number of observation terms
  /** Normally each Obs object represents one observation term in the
      objective function.  However, it is also useful to have a collection
      of similar observations actually collected and treated as a single
      Obs object with a number of term.  This method returns the number of
      terms (defaults to 1) in this Obs. */
  virtual Ordinal Nterms() const { return 1; }

}; // class Obs

} // namespace DGM

#endif  // DGM_OBS_HPP
