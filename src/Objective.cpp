/** \file Objective.cpp
 *  \brief Implementation of DGM Objective
 *  \author S. Scott Collis
 *  \copyright (c)2013 Sandia National Laboratories
*/

// DGM includes
#include "Objective.hpp"
#include "State.hpp"
#include "Adjoint.hpp"

namespace DGM {

  /// Constructor
  Objective::Objective(DGM::ArgList &args, State *state_, Adjoint *adjoint_,
                       const DGM::Comm::Ptr comm_) :
    params(Table()), state(state_), adjoint(adjoint_), comm(comm_) {

    // set default values
    params["dt"] = 0.001;       // time step
    params["npredict"] = 100;   // predictive steps

    // get basic information from argument list
    code = args.front();
    root = args.back();

    // read parameters from an input file
    params.read( root+".inp" );

    // override from command line arguments
    parse_args( args );

    // Initialization
    dt       = params["dt"];
    npredict = params["npredict"];

    // get the adjoint domain
    Domain *omega(adjoint->domain());

    // loop through the adjoint sources
    for (Source::db_citr i=omega->Source_db.begin();
         i!= omega->Source_db.end(); ++i) {
      if (i->second->obs()) {
        i->second->obs()->initialize();
        Entry::Ptr entry(new Entry(i->first, i->second->obs()));
        obs_db.push_back(entry);
        comm->cout() <<"Found observation region: " << i->first << endl;
      }
    }

    // make sure that the state and adjoint know about this objective
    state->set_objective( this );
    adjoint->set_objective( this );
  }

  /// Parse parameters from the argument list
  void Objective::parse_args( DGM::ArgList &args ) {
    string name, value;
    list< DGM::ArgList::iterator > li;
    for ( DGM::ArgList::iterator a = args.begin(); a != args.end(); a++ ) {
      if ( (*a)[0] == '-' ) {
        name = *a;
        if (name == "-npredict") {
          li.push_back(a);
          value = *(++a);
          li.push_back(a);
          params["npredict"] = atoi(value.c_str());
        } else if (name == "-dt") {
          li.push_back(a);
          value = *(++a);
          li.push_back(a);
          params["dt"] = atof(value.c_str());
        }
      }
    }
#ifdef DGM_REMOVE_ARGUMENTS
    // remove tagged arguments
    for ( list< DGM::ArgList::iterator >::iterator a=li.begin();
          a!=li.end(); a++) args.erase(*a);
#endif
  }

}  // namespace DGM



