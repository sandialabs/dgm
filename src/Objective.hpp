#ifndef DGM_OBJECTIVE_HPP
#define DGM_OBJECTIVE_HPP

/** \file Objective.hpp
    \brief Objective class declaration
*/

// system includes
#include <string>

// DTK includes
#include "DTK.hpp"

// DGM includes
#include "Comm.hpp"
#include "ArgList.hpp"
#include "Types.hpp"
#include "Obs.hpp"

namespace DGM {

// forward declarations
class State;
class Adjoint;

/// DGM Objective class that holds multiple observations (Obs)
/** There can and often will be multiple observations (Obs) in a given
    optimization problem and this class is a database of these terms. */
class Objective : public DTK::Objective<Scalar,Ordinal,vField,dVector,State> {

 protected:

  Table params;           ///< Parameter table

  Scalar dt;              ///< Constant time-step (watch out)
  Ordinal npredict;       ///< Number of time-steps

  State* state;           ///< Observing this state (no ownership)
  Adjoint* adjoint;       ///< Forcing this adjoint (no ownership)

  const DGM::Comm::Ptr comm;  ///< Communicator for this Objective

  string code;            ///< Executable code name
  string root;            ///< Root file name (run name)

  /// Generic Entry for the Objective database
  class Entry {
    Obs* obs;             ///< Abstract observation object
   public:
    string name;          ///< Name of this observation term
    /// shared pointer to Objective::Entry
    typedef DGM::Shared<Entry>::Ptr Ptr;
    /// Constructor
    Entry( const string n, Obs *o ) : obs(o), name(n) {}
    /// Set the data for the particular Obs
    void set_data(const vField &S, const Ordinal istep, const Ordinal sstep=0) {
      obs->set_data( S, istep, sstep );
    }
    /// Apply the end condition for this Obs
    void end_condition(vField &S) {
      obs->end_condition( S );
    }
    /// Compute the time-integrated cost for this Obs
    Scalar cost() {
      return obs->cost();
    }
    /// Compute the terminal cost for this Obs
    Scalar terminal_cost() {
      return obs->terminal_cost();
    }
    /// Send a reset message to this Obs (no message)
    void reset() {
      obs->reset_obs();
    }
    /// Send a reset message to this Obs with a data message
    void reset(const dVector &data) {
      obs->reset_obs(data);
    }
  };

  list<Entry::Ptr> obs_db; ///< List of observation terms for this Objective
  mutable dVector costs;   ///< Costs associated with each observation term

 public:

  typedef DGM::Shared<Objective>::Ptr Ptr;  ///< Shared pointer to Objective

  /// Constructor
  Objective(DGM::ArgList &args, State *state_, Adjoint *adjoint_,
            const DGM::Comm::Ptr comm_ = DGM::Comm::World);

  /// Parse parameters from the argument list
  void parse_args( DGM::ArgList &args );

  /// Destructor
  virtual ~Objective() {
    //comm->cout() << "~Objective" << endl;
  }

  /// Returns the number of observation terms in this objective
  size_t num_obs() const {return obs_db.size();}

  /// Sets the Obs data from the given vField and timestep
  virtual void set_data(const vField &S, const Ordinal istep,
                        const Ordinal sstep=0) {
    //cout<<"Objective::set_data()"<<endl;
   typedef list<Entry::Ptr>::iterator LI;
    for (LI i = obs_db.begin(); i != obs_db.end(); ++i) {
      //cout << "Set_data for Observation " << (*i)->name << endl;
      (*i)->set_data( S, istep, sstep );
    }
  }

  /// Applies the end conditions for each Obs
  /** \pre This assumes the the vField S is already initialized
           appropriately. */
  virtual void end_condition(vField &S) {
    //cout<<"Objective::end_condition()"<<endl;
    //S.zero(); // this should be done at a higher level
    typedef list<Entry::Ptr>::iterator LI;
    for (LI i = obs_db.begin(); i != obs_db.end(); ++i) {
      (*i)->end_condition( S );
    }
  }

  /// Computes the cost associated with one time-slab
  virtual Scalar cost(const vField &S, const Ordinal istep,
                      const Ordinal sstep=0) const {
    // cout<<"Objective::cost(...)"<<endl;
    Scalar result = 0; costs = 0;
    Ordinal n = 0;
    typedef list<Entry::Ptr>::const_iterator LI;
    for (LI i = obs_db.begin(); i != obs_db.end(); ++i, ++n) {
      // cout << "Computing cost for Observation " << (*i)->name << endl;
      (*i)->set_data(S,istep,sstep);
      costs[n] = (*i)->cost();
      result += costs[n];
    }
    return result;
  }

  /// Computes the time-integrated costs
  /** \deprecated Time integration is now done using the TimeInt class. */
  virtual Scalar cost() const {
    DGM_UNDEFINED;
    return 0.0;
  }

  /// Return the vector of current costs
  /** \note Assumes that the costs vector contains valid information. */
  virtual dVector get_costs() const { return costs; }

  /// Compute the terminal cost(s) for this objective
  virtual Scalar terminal_cost(const vField &S, const Ordinal istep) const {
    costs = 0;
    if (istep != npredict) return 0;
    // cout<<"Objective::terminal_cost(...)"<<endl;
    Scalar result = 0;
    Ordinal n = 0;
    typedef list<Entry::Ptr>::const_iterator LI;
    for (LI i = obs_db.begin(); i != obs_db.end(); ++i, ++n) {
      (*i)->set_data(S,istep,0);
      costs[n] = (*i)->terminal_cost();
      result += costs[n];
    }
    return result;
  }

  /// Resizes and initializes to zero the individual observation costs
  void reset_costs() { costs.resize(numeric_cast<Ordinal>(obs_db.size())); costs=0; }

  /// Outputs the current individual costs to an output stream.
  /** \note Assumes that the costs vector contains valid information. */
  void output_costs(ostream &os) const {
    Ordinal n=0;
    typedef list<Entry::Ptr>::const_iterator LI;
    for (LI c = obs_db.begin(); c != obs_db.end(); ++c) {
      os<<"J["<<(*c)->name<<"] = "<<costs[n++]<<std::endl;
    }
  }

  /// returns the names for each Obs in this Objective
  virtual vector<string> names() const {
    vector<string> result(num_obs());
    typedef list<Entry::Ptr>::const_iterator LI;
    size_t i = 0;
    for (LI c = obs_db.begin(); c != obs_db.end(); ++c, ++i) {
      result[i] = (*c)->name;
    }
    return result;
  }

  /// Reset individual Obs(ervations) with no prescribed data
  virtual void reset() {
    typedef list<Entry::Ptr>::const_iterator LI;
    for (LI i = obs_db.begin(); i != obs_db.end(); ++i) {
      (*i)->reset();
    }
  }

  /// Reset individual Obs(ervations) with a prescribed data message
  /** Might be expensive to iterative over the whole linked list. */
  virtual void reset(const string name, const dVector &data) {
    typedef list<Entry::Ptr>::const_iterator LI;
    for (LI i = obs_db.begin(); i != obs_db.end(); ++i) {
      if ( (*i)->name == name ) {
        (*i)->reset(data);
      }
    }
  }

  /// Accessor for the state objective observed by this objective
  virtual State *get_state() const { return state; }

}; // class Objective

} // namespace DGM

#endif  // DGM_OBJECTIVE_HPP
