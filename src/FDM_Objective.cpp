/** \file FDM_Objective.cpp
    \brief FDM::Objective interface
    \author Scott Collis
    \author Bill Spotz
*/

// Boost Includes
#include "boost/numeric/conversion/cast.hpp"

// FDM includes
#include "FDM_Objective.hpp"

namespace FDM
{

Objective::Entry::Entry(const std::string n,
                        Obs *o) :
  obs(Teuchos::rcp(o,false)),
  name(n)
{
}

void Objective::Entry::set_data(const VectorField & S,
                                const Ordinal istep,
                                const Ordinal sstep)
{
  obs->set_data(S,istep,sstep);
}

void Objective::Entry::end_condition(VectorField & S)
{
  obs->end_condition(S);
}

Scalar Objective::Entry::cost()
{
  return obs->cost();
}

Scalar Objective::Entry::terminal_cost()
{
  return obs->terminal_cost();
}

void Objective::Entry::reset()
{
  obs->reset_obs();
}

void Objective::Entry::reset(const ScalarVector &data)
{
  obs->reset_obs(data);
}

// Constructor
Objective::Objective() :
  npredict(0)
{
}

// Destructor
Objective::~Objective()
{
}

// Returns the number of observation terms in this objective
size_t Objective::num_obs() const
{
  return obs_db.size();
}

// Sets the Obs data from the given vField and timestep
void Objective::set_data(const VectorField & S,
                         const Ordinal istep,
                         const Ordinal sstep)
{
  typedef list<Entry::Ptr>::iterator LI;
  for (LI i = obs_db.begin(); i != obs_db.end(); ++i)
  {
    (*i)->set_data( S, istep, sstep );
  }
}

// Applies the end conditions for each Obs
void Objective::end_condition(VectorField & S)
{
  typedef list<Entry::Ptr>::iterator LI;
  for (LI i = obs_db.begin(); i != obs_db.end(); ++i)
  {
    (*i)->end_condition( S );
  }
}

// Computes the cost associated with one time-slab
Scalar Objective::cost(const VectorField & S,
                       const Ordinal istep,
                       const Ordinal sstep) const
{
  Scalar result = 0;
  Ordinal n = 0;
  typedef list<Entry::Ptr>::const_iterator LI;
  for (LI i = obs_db.begin(); i != obs_db.end(); ++i)
  {
    (*i)->set_data(S,istep,sstep);
    costs[n] = (*i)->cost();
    result += costs[n];
    n++;
  }
  return result;
}

// Computes the time-integrated costs
Scalar Objective::cost() const
{
  FDM_UNDEFINED;
  return 0.0;
}

// Return the vector of current costs
/** \note Assumes that the costs vector contains valid information. */
ScalarVector Objective::get_costs() const
{
  return costs;
}

// Compute the terminal cost(s) for this objective
Scalar Objective::terminal_cost(const VectorField & S,
                                const Ordinal sstep) const
{
  if (sstep != npredict) return 0;
  Scalar result = 0;
  typedef list<Entry::Ptr>::const_iterator LI;
  for (LI i = obs_db.begin(); i != obs_db.end(); ++i)
  {
    (*i)->set_data(S,sstep,0);
    result += (*i)->terminal_cost();
  }
  return result;
}

// Resizes and initializes to zero the individual observation costs
void Objective::reset_costs()
{
  costs.resize(boost::numeric_cast<Ordinal>(obs_db.size()));
  //costs.resize(obs_db.size());
  costs = 0;
}

// Outputs the current individual costs to an output stream.
/** Assumes that the costs vector contains valid information. */
void Objective::output_costs(std::ostream & os) const
{
  Ordinal n = 0;
  typedef list<Entry::Ptr>::const_iterator LI;
  for (LI c = obs_db.begin(); c != obs_db.end(); ++c)
  {
    os<<"J["<<(*c)->name<<"] = "<<costs[n++]<<std::endl;
  }
}

// Returns the names for each Obs in this Objective
std::vector< std::string > Objective::names() const
{
  std::vector< std::string > result(num_obs());
  typedef list<Entry::Ptr>::const_iterator LI;
  size_t i = 0;
  for (LI c = obs_db.begin(); c != obs_db.end(); ++c, ++i)
  {
    result[i] = (*c)->name;
  }
  return result;
}

// Reset individual Obs(ervations) with no prescribed data
void Objective::reset()
{
  typedef list<Entry::Ptr>::const_iterator LI;
  for (LI i = obs_db.begin(); i != obs_db.end(); ++i)
  {
    (*i)->reset();
  }
}

// Reset individual Obs(ervations) with a prescribed data message
/** Might be expensive to iterative over the whole linked list. */
void Objective::reset(const std::string name,
                      const ScalarVector &data )
{
  typedef list<Entry::Ptr>::const_iterator LI;
  for (LI i = obs_db.begin(); i != obs_db.end(); ++i)
  {
    if ( (*i)->name == name )
    {
      (*i)->reset(data);
    }
  }
}

// State accessor
State * Objective::get_state() const
{
  return state;
}

}  // namespace FDM
