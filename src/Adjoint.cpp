/** \file Adjoint.cpp
    \brief Adjoint base class implementation
    \author Scott Collis
*/

// system includes
#include <iostream>
#include <limits>
using namespace std;

// DGM includes
#include "Comm.hpp"
#include "Adjoint.hpp"
#include "TimeInt.hpp"
#include "Memory.hpp"

namespace DGM {

Adjoint::Adjoint(const State *s, const int pinc) :
  num_(0), name(s->domain()->root), p_inc(pinc), npredict(0), state_(s),
  objective(NULL), Ustate(s->domain()->get_comm(),"Ustate"), iter(0), 
  use_in_core(false), in_core_storage()
{
  // cout << "Adjoint::Adjoint()" << endl;
}

Adjoint::~Adjoint() {
  // cout << "Adjoint::~Adjoint()" << endl;
}

void Adjoint::initialize() {
  domain()->get_comm()->cout() << "Initialize Adjoint = " << name << endl;
  domain()->U.zero();
  scratch = domain()->get_comm()->Scratch();
  if (use_in_core) in_core_storage.initialize(domain(), iter);
}

void Adjoint::set_end_condition() {
  // domain()->get_comm()->cout() << "Adjoint::set_end_condition()" << endl;
  domain()->set_ic( domain()->U, ".adj.ic" );  // allow for a nonzero EC
  const_cast<State*>(state_)->load(Ustate, npredict, 0);
  domain()->set_t_step();
  objective->set_data( Ustate, npredict, 0 );
  objective->end_condition( domain()->U );
  project(domain()->U);
}

void Adjoint::set_end_condition(const dVector &X, const Scalar t_,
                                const Ordinal step_) {
  // domain()->get_comm()->cout() << "Adjoint::set_end_condition(...)" << endl;
  const_cast<State*>(state_)->load(Ustate, npredict, 0);
  domain()->set_t_step();
  objective->set_data( Ustate, npredict, 0 );
  domain()->U.fill(X);       // put the given dVector on the vField U
  project(domain()->U);
}

void Adjoint::compute(const Ordinal npredict, Control::Ptr control_,
                      Control::Ptr gcontrol_, const Ordinal iteration) {
  const DGM::Comm::Ptr comm(domain()->get_comm());
  set_iter(iteration);
  static Format sci_lo(4,10,'e');
  static Format sci(6,15,'e');
  static Format sta(4,12,'e');
  char tmp[BUFLEN];

  num_++;

  control = control_;
  g_control = gcontrol_;
  g_control->zero();

  if (p_control.get()) p_control->zero();
  control->set_data(npredict, 0);
  control->finalize(npredict, 0);

  string caption;
  if (defined<Ordinal>(iter)) {
#ifndef DGM_PARALLEL
    char buffer[128];
    sprintf(buffer,"Adjoint EC at t = %11.4e, step = %lld",
            domain()->t,(long long)domain()->step);
    caption = buffer;
    sprintf(tmp,"%s.adj.%lld_%lld.dat", domain()->root.c_str(),
            (long long)npredict,(long long)iter);
    domain()->U.tecplot(tmp,caption);
#endif
    string fname;
    sprintf(tmp,"%s.adj.%lld_%lld.rst",domain()->root.c_str(),
            (long long)npredict,(long long)iter);
    fname = tmp;
    domain()->write(fname,domain()->U);
  }
#if 1
  // Added by SSC on 1-16-2013 for debugging
  domain()->get_comm()->cout() << "Norms of Adjoint end condition" << endl;
  domain()->U.norm();
#endif
  computeGrad(domain()->U,Ustate,npredict,0);
  Stopwatch wall; wall.start();
  string timestamp = comm->dateTime();
  comm->cout() << "Starting Adjoint solve on " << timestamp << endl;
  domain()->get_comm()->cout() << "Advancing adjoint solution " << npredict
                               << " time steps" << endl;
  comm->cout()<<"    Step iStep          t             dt            "
                "CFL           dCPU\n";
  Scalar ctime=0, stime=0, ttime=0;
  Ordinal cnt=0;
  Stopwatch cpu; cpu.start();
  Memory memory;

  for (domain()->lstep=npredict; domain()->lstep>=1; domain()->lstep--) {
    if (domain()->timeIntegrate.get())
      domain()->timeIntegrate->adjoint_advance(domain());
    else
      domain()->time_int->adjoint_advance(domain());
    ctime = cpu.restart();
    if (domain()->lstep<npredict) {
      ttime += ctime; stime += ctime*ctime; cnt++;
    }
    if ((domain()->lstep-1)%domain()->ntout==0) {
      const Ordinal t = const_cast<State*>(state_)->atomic_advances();
      domain()->get_comm()->cout()
        <<setw(8)<<domain()->lstep-1<<setw(6)
        <<domain()->step-1<<sci(domain()->t)
        <<sci(domain()->dt)<<sci(domain()->CFL)<<sci(ctime);
      if (t) domain()->get_comm()->cout()<<"   *";
      domain()->get_comm()->cout()<<endl;
    }
    if ((domain()->lstep-1)%domain()->Ntout==0) {
      if (defined<Ordinal>(iter)) {
        string fname;
        sprintf(tmp,"%s.adj.%lld_%lld.rst",domain()->root.c_str(),
                (long long)(domain()->lstep-1),(long long)iter);
        fname = tmp;
        domain()->write(fname,domain()->U);
#ifndef DGM_PARALLEL
        char buffer[128];
        sprintf(buffer,"Adjoint at t = %11.4e, step = %lld",
                domain()->t,(long long)(domain()->step-1));
        caption = buffer;
        sprintf(tmp,"%s.adj.%lld_%lld.dat",domain()->root.c_str(),
                (long long)(domain()->lstep-1),(long long)iter);
        domain()->U.tecplot(tmp,caption);
#endif
      }
      domain()->U.norm();
      cpu.restart();
    }
    domain()->step--;
  }
  timestamp = comm->dateTime();
  comm->cout() << "Finished Adjoint solve on " << timestamp << " in "
      << sci_lo(wall.stop()) << " sec" << endl;
  Scalar atime=0, otime=0, xtime=0, ntime=0;
  domain()->get_comm()->SumAll( &ttime, &atime, 1 );  // average cpu time
  domain()->get_comm()->SumAll( &stime, &otime, 1 );  // standard deviation
  domain()->get_comm()->MaxAll( &ttime, &xtime, 1 );  
  domain()->get_comm()->MinAll( &ttime, &ntime, 1 );  
  Ordinal n = max(Ordinal(1),cnt*domain()->get_comm()->NumProc());
  atime /= n; otime /= n; 
  xtime /= max(Ordinal(1),cnt); ntime /= max(Ordinal(1),cnt);
  Scalar stdev = ::sqrt(otime - atime*atime);
  domain()->get_comm()->cout()
    << "Average time per step: " << sta(atime)
    << ", standard deviation:  " << sta(stdev) 
#ifdef DGM_PARALLEL
    << ",\n      minimum average: " << sta(ntime) 
    << ",    maximum average:  " << sta(xtime) 
#endif
    << endl;
  uint64_t min_node_memory = memory.avail();
  comm->MinAll(min_node_memory);
  uint64_t number_of_cores = memory.ncores();
  uint64_t min_core_memory = min_node_memory/number_of_cores;
  comm->cout()<<"Minimum memory per "<<number_of_cores<<" core node: "
              << toXBytes(min_node_memory) << " which is "
              << toXBytes(min_core_memory) << " per core" << endl;
  domain()->write(domain()->root+".adj.rst", domain()->U );
}

#ifdef DGM_USE_TIME_REG

// Adjoint computing with time regularization
void Adjoint::compute(const Ordinal npredict, Control::Ptr gt_control_,
                      Control::Ptr control_, Control::Ptr g_control_,
                      const Ordinal iteration) {
  set_iter(iteration);
  char tmp[80];
  static Format sci(6,15,'e');
  DGM::Comm::Ptr comm(domain()->get_comm());

  num_++;

  control = control_;
  g_control = g_control_;

  ObjFunc J(gt_control_.get(), control.get(),
            objective, domain()->get_comm(), g_control.get() );

#ifndef DGM_PARALLEL
  if (defined<Ordinal>(iter)) {
    sprintf(tmp,"%s.adj.%d_%d.dat", domain()->root.c_str(), npredict, iter);
    domain()->U.tecplot(tmp,"Adjoint IC");
  }
#endif

  comm->cout() << "Advancing adjoint solution " << npredict
               << " time steps" << endl;

  Scalar ctime=0, stime=0, ttime=0;
  Ordinal cnt=0;
  Stopwatch cpu; cpu.start();

  for (domain()->lstep=npredict; domain()->lstep>=1; domain()->lstep--) {
    if (domain()->timeIntegrate.get())
      domain()->timeIntegrate->adjoint_advance(domain(), &J);
    else
      domain()->time_int->adjoint_advance(domain(), &J);
    ctime = cpu.restart();
    if (domain()->lstep<npredict) {
      ttime += ctime; stime += ctime*ctime; cnt++;
    }
    if ((domain()->lstep-1)%domain()->ntout==0) {
      const Ordinal t=const_cast<State*>(state_)->atomic_advances();
      domain()->get_comm()->cout()<<setw(8)<<domain()->lstep-1
                                  <<sci(domain()->t)<<sci(domain()->dt)
                                  <<sci(ctime);
      if (t) domain()->get_comm()->cout()<<"   *";
      domain()->get_comm()->cout()<<endl;
    }
    if ((domain()->lstep-1)%domain()->Ntout==0) {
#ifndef DGM_PARALLEL
      if (defined<Ordinal>(iter)) {
        sprintf(tmp,"%s.adj.%d_%d.dat",domain()->root.c_str(),
                domain()->lstep-1,iter);
        domain()->U.tecplot(tmp,"Adjoint");
      }
#endif
      domain()->U.norm();
      cpu.restart();
    }
  }
#ifdef DGM_PARALLEL
  Scalar atime=0, otime=0, xtime=0, ntime=0;
  domain()->get_comm()->SumAll( &ttime, &atime, 1 );  // average cpu time
  domain()->get_comm()->SumAll( &stime, &otime, 1 );  // standard deviation
  domain()->get_comm()->MaxAll( &ttime, &xtime, 1 );                         
  domain()->get_comm()->MinAll( &ttime, &ntime, 1 );                         
  Ordinal n = max(1,cnt*domain()->get_comm()->NumProc());
  atime /= n; otime /= n; xtime /= max(1,cnt); ntime /= max(1,cnt);
  Scalar stdev = ::sqrt(otime - atime*atime);
  comm->cout() << "Average time per step: " << sci(atime)
               << ", standard deviation:  " << sci(stdev) 
               << ", maximum average:  " << sci(xtime) 
               << ", minimum average:  " << sci(ntime) 
               << endl;
#endif
  domain()->write(domain()->root+".adj.rst", domain()->U);
}

#endif  // DGM_USE_TIME_REG

void Adjoint::store(vField &Uf, const Ordinal istep, const Ordinal sstep) {
  const string name = domain()->mkname(iter,istep,sstep,"adj");
  if (use_in_core) in_core_storage.local_write(name, Uf, domain());
}

void Adjoint::load(vField &Uf, const Ordinal istep, const Ordinal sstep) {
  const string name = domain()->mkname(iter,istep,sstep,"adj");
  if (use_in_core) in_core_storage.local_read(name, Uf, domain());
}

void Adjoint::load_field(vField &Uf, const Ordinal istep,
                         const Ordinal sstep) const {
  const string name = domain()->mkname(iter,istep,sstep,"adj");
  if (use_in_core)
    in_core_storage.local_read( name, Uf, const_cast<Domain*>(domain()));
}

} // namespace DGM
