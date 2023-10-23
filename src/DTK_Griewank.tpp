// -*- c++ -*-w
#ifndef DTK_GRIEWANK_TPP
#define DTK_GRIEWANK_TPP

/** \file DTK_Griewank.tpp
    \brief Template implementation of database for Griewank algorithm storage
    \author James Overfelt
    \author Scott Collis
    \author Bill Spotz
*/

// System includes
#include <algorithm>
#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <limits>
#include <queue>

// DTK includes
#include "DTK.hpp"
#include "DTK_AtomicOps.hpp"
#include "DTK_InCore.hpp"
#include "DTK_InCore.tpp"
#include "DTK_Griewank.hpp"

// DGM includes
#include "Table.hpp"
#include "Comm.hpp"
#ifdef DGM_PARALLEL
#include "MpiComm.hpp"
#endif
#include "Domain.hpp"
#include "TimeInt.hpp"
#include "Format.hpp"

// Asynchronous I/O includes
#ifdef DGM_INCORE_ASYNCHRONOUS_IO
#include <unistd.h>
#ifdef _POSIX_ASYNCHRONOUS_IO
#include <aio.h>
#endif
#endif

namespace DTK {

//===========================================================================
//                  Griewank Storage Class Implementations
//===========================================================================

/// Determine the time steps to save
/** If interested: The algorithm goes something like,
     -# Add all records from 1 to n including substeps to list to save.
     -# Keep track, cur_db_size, of total listed in stored_records.
     -# If too big, max_db_size<cur_db_size, go back to the beginning of
        stored_records and delete some records.
     -# Be careful in doing (2). It is not just first in first out. So
        create "levels" to keep track of which to delete to make room
        for more at the end.
     -# Do this in terms of whole steps.  Not necessary but I like to
        do all substeps within a step at one time and not keep partial
        steps around.
*/
template < typename Scalar,
           typename Ordinal,
           typename VectorField,
           typename Domain >
void Griewank<Scalar,Ordinal,VectorField,Domain>::
determine_steps_to_save(const DGM::Comm::Ptr comm,
                        const Ordinal start,
                        const Ordinal input_num_iter) 
{
  Database &v = stored_records;

  const Ordinal MAX_LEV=10;
  const Ordinal num_iter = 
    numeric_limits<Ordinal>::max() == input_num_iter  ? num_steps  :
                                     (0<input_num_iter? input_num_iter : 1);
  const Ordinal end_time_step = start + num_iter;

  Key end_key(end_time_step,0);
  typename Database::iterator del_at_end         = v.upper_bound(end_key);
  typename Database::iterator del_at_start_begin = v.end();
  typename Database::iterator del_at_start_end   = v.end();

  vector<queue<typename Database::iterator> > levels(MAX_LEV+1);
  queue       <typename Database::iterator>   freelist;
  
  // Iterate from step at end of storage to the desired iteration number
  for (Ordinal step=start; step<=end_time_step; ++step) {
    Ordinal level=0;

    Ordinal without_restart = 0;
    Ordinal with_restart    = 0;
    for (Ordinal sstep=0; sstep!=num_substeps; ++sstep) {
      const Key   key(step,sstep);
      if (v.count(key)) continue;
      const bool t = saved_init.count(key);
      without_restart            += t ? saved_init[key].Size() : adjoint_size;
      if (sstep) with_restart    += t ? saved_init[key].Size() : restart_size;
      else       with_restart    += t ? saved_init[key].Size() : adjoint_size;
    }  
    if (step==end_time_step-1) { // Add in last step if next to last
      for (Ordinal sstep=0; sstep!=num_substeps; ++sstep) {
        const Key   key(end_time_step,sstep);
        if (v.count(key)) continue;
        const bool t = saved_init.count(key);
        without_restart            += t ? saved_init[key].Size() : adjoint_size;
        if (sstep) with_restart    += t ? saved_init[key].Size() : restart_size;
        else       with_restart    += t ? saved_init[key].Size() : adjoint_size;
      }  
    }

    // Check if there is room in the database for the record about to add
    while (max_db_size < cur_db_size + (level ? with_restart:without_restart)){
      if (del_at_end != v.end()) {
        // First try deleting special unused snapshots at the end.
        const Ordinal s = v.rbegin()->first.Step();
        while (del_at_end != v.end() && s == v.rbegin()->first.Step()) {
          if (del_at_end->first==v.rbegin()->first) del_at_end=v.end();
          cur_db_size   -= v.rbegin()->second.Size();
          const string n = v.rbegin()->second.Name();
          if (!n.empty()) in_core_storage.erase(n);
          v.erase(v.rbegin()->first);
        }   
      } else if (del_at_start_begin != del_at_start_end) {
        // First try deleting special unused snapshots at the beginning. 
        const Ordinal s = del_at_start_begin->first.Step();
        while (del_at_start_begin != del_at_start_end && 
               s == del_at_start_begin->first.Step()) {
            cur_db_size   -= del_at_start_begin->second.Size();
            const string n = del_at_start_begin->second.Name();
            if (!n.empty()) in_core_storage.erase(n);
            typename Database::iterator r = del_at_start_begin;
            ++del_at_start_begin;
            v.erase(r);
        }   
      } else if (!freelist.empty()) {
        // delete a few standard snapshots.
        const Ordinal s=freelist.front()->first.Step();
        while (!freelist.empty() && s==freelist.front()->first.Step()) {
            const typename Database::iterator r = freelist.front();
            cur_db_size   -= r->second.Size();
            const string n = r->second.Name();
            if (!n.empty()) in_core_storage.erase(n);
            v.erase(r);
            freelist.pop();
        }   
      } else if (MAX_LEV <= level) {
        // Completely out of steps to delete.  freelist buffer
        // is empty and del_at_end_end is empty.  Last chance
        // search for steps to delete. Reset level to zero.
        level = 0;
        if (!saved_init.empty()) {
          for (typename Database::const_iterator j=saved_init.begin(),i=j++; 
               j!=saved_init.end() && del_at_start_begin==del_at_start_end; 
               ++i,++j) {
            del_at_start_begin  = v.upper_bound(i->first);
            del_at_start_end    = v.lower_bound(j->first);
          }
        }
        if (del_at_start_begin==del_at_start_end) {
          cout <<__FILE__<<":"<<__LINE__
               <<" Exceeded levels and saved_init is empty."<<endl;
          comm->error(" Exceeded levels and saved_init is empty.");
        }
      } else {
          // get next level of snapshots to delete
          while (levels[level].empty() && level<MAX_LEV) ++level;
          swap(freelist,levels[level]);
          ++level;
      }
    }
    if (MAX_LEV < level) {
      cout <<__FILE__<<":"<<__LINE__;
      cout <<" Error: level:"<<level<<" exceeds max:"<<MAX_LEV<<endl;
      cout <<" Recompile with a larger maximum number of levels:"
           <<MAX_LEV<<endl;
      comm->error(" Recompile with a larger maximum number of levels.");
    }
    for (Ordinal sstep=0; sstep!=num_substeps; ++sstep) {
      // Insert records into list of records to save.  This inserted 
      // record could end up being deleted with the above logic if
      // needed to make room for even more records at the end.
      const Key key(step,sstep);
      if (!v.count(key)) { // Should never happen but harmless if does.
        Ordinal snapshot_size = level ? restart_size : adjoint_size;
        if (saved_init.count(key)) snapshot_size = saved_init[key].Size();
        const Value val(snapshot_size,string());
        const typename Database::value_type r(key,val);
        const typename Database::iterator iter = v.insert(v.end(),r);
        levels[level].push(iter);
        cur_db_size += val.Size();
        level = 0;
      }
    }   
  }   
  return;
}

namespace {
template < typename Ordinal >
Ordinal instance_counter() {
  static Ordinal instance=0;
  return instance++;
}
} // anonymous namespace

/// Constructor
template < typename Scalar,
           typename Ordinal,
           typename VectorField,
           typename Domain >
Griewank<Scalar,Ordinal,VectorField,Domain>::
Griewank(AtomicOps< Scalar, Ordinal > *a) :
  instance(instance_counter<Ordinal>()),
  num_snapshots(0),
  num_substeps (0),
  cur_db_size  (0),
  max_db_size  (0),
  restart_size (0),
  adjoint_size (0),
  debug_level  (1),
  debug_iterations(0),
  atomic_ops   (a),
  stored_records(),
  in_core_storage()
{
}

/// Output statistics to std out
template < typename Scalar,
           typename Ordinal,
           typename VectorField,
           typename Domain >
void Griewank<Scalar,Ordinal,VectorField,Domain>::
write_stats() const
{
  if (DGM::Comm::World->Master()) {
    cout <<"Griewank "<<instance<<" statistics:"<<endl;
    cout <<"         Number of records in storage          :"
         <<stored_records.size()<<endl;
    cout <<"         Number of iterations from stored steps:"
         <<debug_iterations<<endl;
  }
}

/// Destructor
template < typename Scalar,
           typename Ordinal,
           typename VectorField,
           typename Domain >
Griewank<Scalar,Ordinal,VectorField,Domain>::
~Griewank()
{
  if (2<debug_level) write_stats();
  atomic_ops=NULL;
}

namespace {
template < typename Ordinal >
void parse_json(unsigned &debug_level,
                size_t   &snapshots,
                Ordinal  &Npredict,
                const Json::Value &json){

  Json::Value griewank = json["Griewank"];
  if (griewank.isMember("Statistics")) 
    debug_level = griewank["Statistics"].asUInt();
  if (griewank.isMember("Number of Snapshots")) 
    snapshots = griewank["Number of Snapshots"].asUInt();
  if (json.isMember("Optimizer") && json["Optimizer"].isMember("npredict"))
    Npredict = json["Optimizer"]["npredict"].asUInt();
}

template < typename Ordinal >
void parse_tabl(unsigned &debug_level,
                bool     &griewank,
                size_t   &snapshots,
                Ordinal  &Npredict,
                DGM::Table &params,
                const std::string &root) {
  // Determine debug level of printout  
  params["griewank-stats"] = "XXX";
  const string p1 = params.read(root, "griewank-stats");
  if (p1 != "XXX") {
    istringstream s(p1);
    s >> debug_level ;
  }

  // Determine if Griewank storage is to be used
  params["griewank"] = "XXX";
  const string p2 = params.read(root, "griewank");
  griewank = (p2 != "XXX" && p2 != "0");
  if (griewank) {
    istringstream s(p2);
    s >> snapshots;
    // Special case, 1 means use Griewank with all available memory
    if (snapshots==1) snapshots=0;
  }

  params["npredict"] = "XXX";
  const string p3 = params.read(root, "npredict");
  if (p3 != "XXX") {
    istringstream s(p3);
    s >> Npredict ;
  }
}

}
/// Initialize the Griewank strategy
/** This reads a parameter from the primary input file called "griewank"
    that, if set, specifies another input file that controls the Griewank
    optimal checkpointing strategy   */
template < typename Scalar,
           typename Ordinal,
           typename VectorField,
           typename Domain >
bool Griewank<Scalar,Ordinal,VectorField,Domain>::
initialize(Domain *domain)
{
  const DGM::Comm::Ptr comm(domain->get_comm());

  Json::Value json = domain->json_root;

  bool    griewank  = false;
  size_t  snapshots = 0;
  Ordinal Npredict  = 0;
  if (json.isMember("Griewank")) {
    comm->cout()<<"  Reading Griewank options from Json file."<<std::endl;
    griewank = true;
    parse_json         (debug_level,         snapshots,Npredict,json);

    if (!Npredict) {
      // Possible this parameter is specified in root.inp file:
      DGM::Table &params(domain->params);
      const std::string root=domain->getRoot()+".inp";
      params["npredict"] = "XXX";
      const string p = params.read(root, "npredict");
      if (p != "XXX") {
        istringstream s(p);
        s >> Npredict ;
      }
    }
  } else {                         
    DGM::Table &params(domain->params);
    const std::string root=domain->getRoot()+".inp";
    parse_tabl<Ordinal>(debug_level,griewank,snapshots,Npredict,params,root);
    if (griewank) 
      comm->cout()<<"Reading Griewank options from "<<root<<" file."<<std::endl;
  }


  // Initializes the in-core storage
  const size_t max_num_snapshots_in_core =
    in_core_storage.initialize(domain, griewank);

  // For Griewank, override the default InCore storage pattern.
  in_core_storage.clear();
  stored_records.clear();

  if (griewank) {
    num_steps = domain->get_Nt();
    {
      if (num_steps < Npredict) {
        ostringstream s;
        s <<" Error in Griewank::initialize file "<<__FILE__
          <<" line "<<__LINE__<<endl
          <<"Error: The number of time steps, "<<num_steps
          <<" from the num_steps parameter in the inp file "<<endl
          <<"is less than the number to predict, "<<Npredict
          <<" from the Npredict parameter in the inp file."<<endl
          <<" Can't predict beyond the data available."<<endl;
         comm->error(s.str());
      }
    }
    const size_t num_sub_steps = 
      std::max(static_cast<DGM::Ordinal>(1),domain->get_sstep());
    const size_t tot_substeps  = num_sub_steps*(num_steps+1);

    if (!snapshots) snapshots = max_num_snapshots_in_core;
    griewank = (snapshots < tot_substeps);
    if (griewank) {
      if (snapshots <= 2*num_sub_steps) {
        ostringstream s;
        s <<" Error in Griewank::initialize file "<<__FILE__
          <<" line "<<__LINE__<<endl
          <<"Error: Not enough snapshots to even use Griewank.  "
          <<"There must be at least twice the number of snapshots "
          <<"than the number of substeps in a single RK time step."<<endl
          <<"Found that "<<snapshots<<" will fit in memory but "
          <<num_sub_steps<<" are needed for each time step. "<<endl
          <<"Going to have to fix a few things in Griewank to use so "
          <<"few snapshots."<<endl;
         comm->error(s.str());
      }
      num_snapshots = numeric_cast<Ordinal>(std::max(snapshots-num_sub_steps,
                                                     num_sub_steps+2));
      num_substeps  = numeric_cast<Ordinal>(num_sub_steps);
      max_db_size   = numeric_cast<uint64_t>(in_core_storage.size_of_memory());
      restart_size  = numeric_cast<Ordinal>(in_core_storage.size_of_record());
      adjoint_size  = numeric_cast<Ordinal>(in_core_storage.size_of_adjoint());

      const Key zero(0,0);
      const Value val(restart_size,string());
      const typename Database::value_type r(zero,val);
      stored_records.insert(r);
      cur_db_size += val.Size();
      saved_init.clear();
      reinitialize(domain); 
      saved_init = stored_records;
      if (comm->Master() && debug_level) {
        comm->cout() <<"Using Griewank algorithm with "
                     <<num_snapshots<<" snapshots."<<endl;
      }
    } else {
      if (comm->Master() && debug_level)  
        comm->cout() <<"No need for Griewank algorithm since "
                     <<"all snapshots fit in core."<<endl;
    }
  }
  return true;
}

/// Re-initialize the Griewank database
template < typename Scalar,
           typename Ordinal,
           typename VectorField,
           typename Domain >
void Griewank<Scalar,Ordinal,VectorField,Domain>::
reinitialize(Domain *domain)
{
  if (num_snapshots)  {                         // using Griewank
    if (3<debug_level)  
      cout<<"pid:"<<DGM::Comm::World->MyPID() <<" Griewank::reinitialize"<<endl;
    const DGM::Comm::Ptr comm(domain->get_comm());
    remove_states_after    (comm,0);
    determine_steps_to_save(comm,0);
  }
}

/// Delete used states from all of: in_core_storage, file storage
template < typename Scalar,
           typename Ordinal,
           typename VectorField,
           typename Domain >
void Griewank<Scalar,Ordinal,VectorField,Domain>::
remove_states_after( const DGM::Comm::Ptr comm,
                     const Ordinal step)
{
  const Key start_from(step,0);
  const typename Database::iterator del =
    stored_records.upper_bound(start_from);

  if (3<debug_level) {
    ostringstream os;
    os<<"Griewank "<<instance<<" level 4 debug after step "<<step<<" -- Erase:";
    bool p=false;
    for (typename Database::const_iterator i=del; i!=stored_records.end(); ++i){
      os<<'"'<<i->second.Name()<<'"'<<"  ";
      p=true;
    }
    if (p) comm->cout()<<os.str()<<endl;
  }

  for (typename Database::const_iterator i=del; i!=stored_records.end(); ++i){
    cur_db_size   -= i->second.Size();
    const string s = i->second.Name();
    if (!s.empty()) in_core_storage.erase(s);
  }
  stored_records.erase(del, stored_records.end());
}

/// Perform recomputation if needed
template < typename Scalar,
           typename Ordinal,
           typename VectorField,
           typename Domain >
void Griewank<Scalar,Ordinal,VectorField,Domain>::
iterate_to_step_from_saved(const Ordinal end_step, Domain *domain)
{
  const DGM::Comm::Ptr comm(domain->get_comm());

  const Key key(end_step,0);
  typename Database::const_iterator start_iter=stored_records.lower_bound(key);
  if (start_iter != stored_records.begin()) --start_iter;

  const Ordinal start_step = start_iter->first.Step();

  const Key start_step_key(start_step,0);
  start_iter = stored_records.find(start_step_key);

  if (start_iter==stored_records.end()) {
    ostringstream s;
    s << " Griewank: Did not find expected key in InCore Database:"<<start_step
      << endl
      <<" In file "<<__FILE__<<" line "<<__LINE__<<endl
      <<" Debug information -- "
      <<" step:"<<start_step
      <<endl;
    comm->error(s.str());
  }

  const string step_name  = start_iter->second.Name();

  // check to make sure that the step_name is valid
  if (step_name.empty()) {
    ostringstream s;
        s << "Griewank: tried to find empty name in InCore Database:"<< endl
          << " In file "<<__FILE__<<" line "<<__LINE__<<endl
          << " Debug information -- "
          << " step:"<< end_step;
        s <<endl;
        comm->error(s.str());
  }

  // now restore the file and iterate to step......
  if (!in_core_storage.local_exists(step_name, domain->getU(), domain)) {
    ostringstream s;
    s << " Griewank: Did not find expected key in InCore Database:"<<step_name
      << endl
      <<" In file "<<__FILE__<<" line "<<__LINE__<<endl
      <<" Debug information -- "
      <<" step:"<<end_step
      <<" step_name:"<<step_name;
    s <<endl;
    comm->error(s.str());
  }

  in_core_storage.local_read(step_name, domain->getU(), domain);

  const Ordinal num_iter = end_step - start_step;
  determine_steps_to_save(comm, start_step, num_iter);
  atomic_ops->atomic_advance   (start_step, num_iter);
  debug_iterations += num_iter;
}

/// Write debugging information
template < typename Scalar,
           typename Ordinal,
           typename VectorField,
           typename Domain >
void Griewank<Scalar,Ordinal,VectorField,Domain>::
local_write_information(const Ordinal step,
                        const Ordinal substep,
                        const string &name)
{
  cout
    <<"pid:"<<DGM::Comm::World->MyPID()
    <<" Debug info for Griewank debug_level greater than 4 "<<endl
    <<"pid:"<<DGM::Comm::World->MyPID()
    <<" Griewank storing record with name '"<<name<<"'"<<endl
    <<"pid:"<<DGM::Comm::World->MyPID()
    <<" for step number "<<step<<" substep number "<<substep<<endl;

  if (!substep && stored_records.count(Key(step,0))) {
    cout
      <<"pid:"<<DGM::Comm::World->MyPID()
      <<" This is the 0th substep and step number "<<step
      <<" was found in storage database as a step to save."<<endl;
  }
  cout
    <<"pid:"<<DGM::Comm::World->MyPID()
    <<" The current size of the InCore database is "
    <<in_core_storage.database_size()<<" number of records."<<endl;
}

/// Parallel write to in-core storage
template < typename Scalar,
           typename Ordinal,
           typename VectorField,
           typename Domain >
void Griewank<Scalar,Ordinal,VectorField,Domain>::
local_write(const Ordinal step,
            const Ordinal substep,
            const string &name,
            VectorField &U,
            Domain *domain)
{
  const DGM::Comm::Ptr comm(domain->get_comm());
  Key storage_key(step,substep);
  if (!num_snapshots)  {                         // not using Griewank
    in_core_storage.local_write(name, U, domain);
  } else if (stored_records.count(storage_key)) {       // found in list to save
    if (4<debug_level) local_write_information(step, substep, name);
    if (!in_core_storage.local_room(name)) {
      determine_steps_to_save(comm,step);
      if (!in_core_storage.local_room(name)) {
        remove_states_after(comm,step);
        determine_steps_to_save(comm,step);
        if (!in_core_storage.local_room(name)) {
          ostringstream s;
          s << " Griewank instance "<<instance
            <<" : No room in InCore database to store key "<<name
            <<" In file "<<__FILE__<<" line "<<__LINE__<<endl
            <<" Debug information -- "
            <<" step:"<<step
            <<" substep:"<<substep
            <<" num_snapshots:"<<num_snapshots
            <<" stored_records.size():"<<stored_records.size()
            <<" in_core_storage.database_size():"<<in_core_storage.database_size()
            <<endl;
          comm->error(s.str());
        }
      }
    }

    // found in database write restart or adjoint record
    // but since this is not really supported right now.....
    if (stored_records[storage_key].Size()==restart_size)
      in_core_storage.local_write(name, U, domain);
    else
      in_core_storage.local_write(name, U, domain);
    stored_records[storage_key].second=name;
  }
}

/// Parallel read from in-core storage
template < typename Scalar,
           typename Ordinal,
           typename VectorField,
           typename Domain >
void Griewank<Scalar,Ordinal,VectorField,Domain>::
local_read(const Ordinal step,
           const Ordinal substep,
           const string &name,
           VectorField &U,
           Domain *domain)
{
  if (num_snapshots && !in_core_storage.local_exists(name, U, domain)) {
    // using Griewank and not found in InCore database

    // If wanting to go to a substep, have to iterate one past step...
    const Ordinal iterate_to = substep ? step+1 : step;
    iterate_to_step_from_saved(iterate_to, domain);
    if (!in_core_storage.local_exists(name, U, domain)) {
      const DGM::Comm::Ptr comm(domain->get_comm());
      ostringstream s;
      const vector<string> keys = in_core_storage.database_keys();
      s << " Griewank instance "<<instance
        <<" : Did not find expected key "<<name
        <<" In file "<<__FILE__<<" line "<<__LINE__<<endl
        <<" Debug information -- "
        <<" step:"<<step
        <<" substep:"<<substep
        <<" iterate_to:"<<iterate_to
        <<endl;
      s <<" Database Keys:"<<endl;
      if (!comm->MyPID())
        for (vector<string>::const_iterator i=keys.begin();i!=keys.end();++i)
          s << *i<<",  ";
      s << endl;
      comm->error(s.str());
    }
  }
  in_core_storage.local_read(name, U, domain);
}

} // namespace DTK
#endif   // DTK_GRIEWANK_TPP
