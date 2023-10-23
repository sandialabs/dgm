#ifndef FDM_OBJECTIVE_HPP
#define FDM_OBJECTIVE_HPP

/** \file FDM_Objective.hpp
    \brief FDM::Objective interface
    \author Scott Collis
    \author Bill Spotz
*/

// FDM includes
#include "FDM_Types.hpp"
#include "FDM_VectorField.hpp"

namespace FDM
{

// Forward declare State and Adjoint classes
class State;
class Adjoint;

//! FDM Obs class
typedef DTK::Obs< VectorField,
                  ScalarVector,
                  Scalar,
                  Ordinal > Obs;

//! FDM Objective class holds multiple observations (Obs)
class Objective : public DTK::Objective< Scalar,
                                         Ordinal,
                                         VectorField,
                                         ScalarVector,
                                         State >
{
protected:
  Ordinal   npredict;
  State *   state;
  Adjoint * adjoint;

  class Entry
  {
    Teuchos::RCP< Obs > obs;

  public:
    typedef Teuchos::RCP< Entry > Ptr;
    std::string name;

    Entry(const std::string n,
          Obs *o);

    void set_data(const VectorField & S,
                  const Ordinal istep,
                  const Ordinal sstep=0);

    void end_condition(VectorField &S);
    Scalar cost();
    Scalar terminal_cost();
    void reset();
    void reset(const ScalarVector & data);
  };

  std::list< Entry::Ptr > obs_db;   ///< List of observation terms
  mutable ScalarVector costs;       ///< Costs associated with each obs

public:
  /// Pointer to self
  typedef Teuchos::RCP< Objective > Ptr;

  /// Constructor
  Objective();

  /// Destructor
  virtual ~Objective();

  /// Returns the number of observation terms in this objective
  size_t num_obs() const;

  /// Sets the Obs data from the given vField and timestep
  virtual void set_data(const VectorField & S,
                        const Ordinal istep,
                        const Ordinal sstep=0);

  /// Applies the end conditions for each Obs
  virtual void end_condition(VectorField &S);

  /// Computes the cost associated with one time-slab
  virtual Scalar cost(const VectorField & S,
                      const Ordinal istep,
                      const Ordinal sstep=0) const;

  /// Computes the time-integrated costs
  virtual Scalar cost() const;

  /// Return the vector of current costs
  /** \note Assumes that the costs vector contains valid information. */
  virtual ScalarVector get_costs() const;

  /// Compute the terminal cost(s) for this objective
  virtual Scalar terminal_cost(const VectorField & S,
                               const Ordinal sstep) const;

  /// Resizes and initializes to zero the individual observation costs
  void reset_costs();

  /// Outputs the current individual costs to an output stream.
  /** Assumes that the costs vector contains valid information. */
  void output_costs(std::ostream &os) const;

  /// returns the names for each Obs in this Objective
  virtual std::vector<std::string> names() const;

  /// Reset individual Obs(ervations) with no prescribed data
  virtual void reset();

  /// Reset individual Obs(ervations) with a prescribed data message
  /** Might be expensive to iterative over the whole linked list. */
  virtual void reset(const std::string name,
                     const ScalarVector & data);

  /// State accessor
  virtual State * get_state() const;

};

}  // namespace FDM

#endif
