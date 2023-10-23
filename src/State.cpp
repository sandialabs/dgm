/** \file State.cpp
    \brief State base class implementation
    \author S. Scott Collis
*/

// System includes
#include <sys/time.h>
#include <sys/resource.h>
#include <sstream>
#include <fstream>
#include <limits>
#include <cstdio>

// DTK includes
#include "DTK.hpp"
#include "DTK_TimeIntegrate.hpp"
#include "DTK_Composite.hpp"
#include "DTK_InCore.tpp"
#include "DTK_Griewank.tpp"

// DGM includes
#include "State.hpp"
#include "AtomicOps.hpp"
#include "ObjFunc.hpp"
#include "TimeInt.hpp"
#include "Format.hpp"
#include "Memory.hpp"
#include "Partition.tpp"

// boost includes
#include "boost/numeric/conversion/cast.hpp"

// put defines you wish to document here
//#ifdef DGM_DOXYGEN
/// Use this flag to store initial value which was original default
#define DGM_STATE_STORE_INITIAL_VALUE
//#endif

namespace DGM {

//===========================================================================
//                      Composite Data Methods
//===========================================================================

#ifdef DGM_STATE_USE_DTK_TIMEINTEGRATE

/// axpy for composite data
void axpy(const Scalar a, const CompositeData &X, const CompositeData &Y,
          CompositeData &Z) {
  axpy(a,X.U,Y.U,Z.U);
  axpy(a,X.J,Y.J,Z.J);
}

/// axpy for composite data
void axpy(const Scalar a, const CompositeData &X, CompositeData &Y) {
  axpy(a,X.U,Y.U);
  axpy(a,X.J,Y.J);
}

/// scale for composite data
void scale(const Scalar a, CompositeData &X) {
  scale(a,X.U);
  scale(a,X.J);
}

#endif

//===========================================================================
//                       State Class Implementation
//===========================================================================

/// Construct the State
State::State(const int pinc, const DGM::Comm::Ptr comm) :
  comm_(comm), num_(0), p_inc(pinc), outputTest_(false), Uf2(comm),
  control(NULL), objective(NULL),
#ifdef DGM_USE_GRIEWANK
  griewank(this)
#else
  in_core_storage()
#endif
{ }

/// Destroy the State
State::~State() {}

void State::initialize() {
  name = domain()->root;
  comm_->cout() << "Initializing State = " << name << endl;
  domain()->set_ic(domain()->U);    // start from initial condition
  // Should this be in set_initial_condition?
  DGM::Comm::Ptr comm = domain()->get_comm();
  // comm->cout() << "Initialize storage database" << endl;
#ifdef DGM_USE_GRIEWANK
  griewank.initialize(domain());
#else
  in_core_storage.initialize(domain(), 0);
#endif
  // comm->cout() << "Completed initialize storage database" << endl;
  // Initialize the ss_rtime vector if we are using ss interpolation
  // comm->cout() << "State::initialize found ssiorder = " << domain()->get_ssiorder() << endl;
  if (domain()->get_ssiorder() > 0) {
    Ordinal nsstep = domain()->time_int->numsubstep();
    ss_rtime.resize(nsstep);
    for (Ordinal s=0; s<nsstep; s++) {
      ss_rtime[s] = domain()->time_int->getsubtime(s);
    }
  }
#ifdef DGM_STATE_STORE_INITIAL_VALUE
  store(domain()->U,0);             // save the initial field to the database
#endif
}

void State::set_initial_condition(const dVector &X,
                                  const Scalar t_, const Ordinal step_) {
  domain()->t = t_;
  domain()->step = step_;
  domain()->U.fill(X);              // put the given dVector on the vField U
  project(domain()->U);             // project U to the polynomial space
#ifdef DGM_USE_GRIEWANK
  griewank.reinitialize(domain());
#endif
  // this store shouldn't really be here
#ifdef DGM_STATE_STORE_INITIAL_VALUE
  store(domain()->U,0);             // save the initial field
#endif
}

void State::set_initial_condition() {
  domain()->set_ic(domain()->U);
#ifdef DGM_USE_GRIEWANK
  griewank.reinitialize(domain());
#endif
  // this store shouldn't really be here
#ifdef DGM_STATE_STORE_INITIAL_VALUE
  store(domain()->U, 0);
#endif
}

#ifdef DGM_STATE_USE_DTK_TIMEINTEGRATE
void State::setTimeIntegrate(Control::Ptr ctrl, Objective *obj) {
  const DGM::Comm::Ptr comm(domain()->get_comm());
  ObjFunc J(ctrl.get(),obj,comm);
  compositeFunc.reset(new CompositeFunc(domain(),&J));
  DTK_ti.reset(new RK(compositeFunc.get()));
}
#endif

Scalar State::compute(const Ordinal npredict, Control::Ptr control_,
                      const Ordinal iter) {
  const DGM::Comm::Ptr comm(domain()->get_comm());
  const string root(domain()->root);
  // comm->cout() << "State::compute for iteration = " << iter << endl;
  static Format sci_lo(4,10,'e');
  static Format sci(6,15,'e');
  static Format sci_hi(10,17,'e');
  static Format sta(4,12,'e');
  char tmp[BUFLEN];

#ifdef DGM_CHECK_ITER_SIGN
  if (std::numeric_limits<Ordinal>::is_signed) {
    if (boost::numeric_cast<long long>(iter) < 0)
      throw DGM::exception("DGM::State iteration index is negative");
  }
#endif
  increment();
  domain()->time_int->initialize();

  // initialize the control
  control = control_.get();
  assert(control!=0 /* Tried to evaluate on undefined Control */);

  if (1 < domain()->verbosity())
    comm->cout()<<"State::compute setting initial data"<<endl;
  control->set_data(0);
  control->finalize(0);
  if (1 < domain()->verbosity())
    comm->cout()<<"State::compute finished setting initial data"<<endl;

  ObjFunc J( control, objective, comm );

#ifdef DGM_STATE_USE_DTK_TIMEINTEGRATE
  compositeFunc->reset(&J);
#endif

#ifndef DGM_PARALLEL
  char buffer[256];
  sprintf(buffer,"State IC at t = %11.4e, step = %lld",
          domain()->t,(long long)domain()->step);
  string caption = buffer;
  if (defined<Ordinal>(iter)) {
    if (iter==0)
      sprintf(tmp,"%s.%lld.dat",root.c_str(),(long long)domain()->step);
    else
      sprintf(tmp,"%s.%lld_%lld.dat",root.c_str(),(long long)domain()->step,
              (long long)iter);
    domain()->U.tecplot(tmp,caption);
  }
#endif
  Stopwatch wall; wall.start();
  string timestamp = comm->dateTime();
  comm->cout() << "Starting State solve on " << timestamp << endl;
  if (defined<Ordinal>(iter)) {
    if (iter==0) {
      sprintf(tmp,"%s.%lld.rst",domain()->root.c_str(),(long long)0);
      comm->cout() << "Advancing solution " << npredict
                   << " time steps" << endl;
    } else {
      sprintf(tmp,"%s.%lld_%lld.rst",domain()->root.c_str(),(long long)0,
             (long long)iter);
      comm->cout() << "Predicting solution " << npredict
                   << " time steps" << endl;
    }
    string fname = tmp;
    domain()->write(fname,domain()->U);
  }

  // store the initial condition in the database
  store(domain()->U,0,0);

  Scalar ctime=0, stime=0, ttime=0;
  Ordinal cnt=0;
  Stopwatch cpu; cpu.start();
  Memory memory;

  domain()->prepareToAdvance();
  domain()->compute_CFL = true;
  comm->cout()<<"    Step iStep          t             dt            CFL"
                "           dCPU"<<endl;
  for (domain()->lstep=1; domain()->lstep<=npredict; domain()->lstep++) {
    domain()->step++;
    domain()->CFL = domain()->set_time_step(domain()->U);
#ifdef DGM_STATE_USE_DTK_TIMEINTEGRATE
    if (DTK_ti.get()) {
      DTK_ti->advance(&*compositeFunc);
    } else {
      domain()->time_int->advance(domain(),&J);
    }
#else
    domain()->time_int->advance(domain(),&J);
#endif
    ctime = cpu.restart();
    if (domain()->lstep>1) { 
      ttime += ctime; stime += ctime*ctime; cnt++;
    }
    if (domain()->lstep%domain()->ntout==0)
      comm->cout()<<setw(8)<<domain()->lstep<<setw(6)
                  <<domain()->step<<sci(domain()->t)
                  <<sci(domain()->dt)<<sci(domain()->CFL)<<sci(ctime)<<endl;
    if (domain()->lstep%domain()->Ntout==0) {
      if (defined<Ordinal>(iter)) {
        if (iter==0)
          sprintf(tmp,"%s.%lld.rst",root.c_str(),(long long)domain()->step);
        else
          sprintf(tmp,"%s.%lld_%lld.rst",root.c_str(),(long long)domain()->step,
                  (long long)iter);
        string fname = tmp;
        domain()->write(fname,domain()->U);
  #ifndef DGM_PARALLEL
        sprintf(buffer,"State at t = %11.4e, step = %lld",domain()->t,
                (long long)domain()->step);
        caption = buffer;
        if (iter==0)
          sprintf(tmp,"%s.%lld.dat",root.c_str(),(long long)domain()->step);
        else
          sprintf(tmp,"%s.%lld_%lld.dat",root.c_str(),(long long)domain()->step,
                  (long long)iter);
        domain()->U.tecplot(tmp,caption);
  #endif
      }
      domain()-> U.norm();
      cpu.restart();
    }
  }
  timestamp = comm->dateTime();
  comm->cout() << "Finished State solve on " << timestamp << " in "
      << sci_lo(wall.stop()) << " sec" << endl;
  Scalar atime=0, otime=0, xtime=0, ntime=0;
  comm->SumAll( &ttime, &atime, 1 );  // average cpu time
  comm->SumAll( &stime, &otime, 1 );  // standard deviation
  comm->MaxAll( &ttime, &xtime, 1 );                          
  comm->MinAll( &ttime, &ntime, 1 );                          
  Ordinal n = max(Ordinal(1), cnt*comm->NumProc());
  atime /= n; otime /= n; 
  xtime /= max(Ordinal(1),cnt); ntime /= max(Ordinal(1),cnt);
  Scalar stdev = ::sqrt(otime - atime*atime);
  comm->cout() << "Average time per step: " << sta(atime)
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
  domain()->write(root+".rst", domain()->U);
  J.add_terminal(domain()->U);
  J.globalize();
  comm->cout()<<"J = "<<sci_hi(J.value())<<endl;
  vector<string> names = J.names();
  dVector &terms = J.terms();
  for (Ordinal i=0; i<J.size(); ++i) {
    comm->cout()<<"  J_{"<<names[i]<<"} = "<<sci_hi(terms[i])<<endl;
  }
  return J.value();
}

Scalar State::test(const Ordinal npredict, Control::Ptr control_){
  const DGM::Comm::Ptr comm(domain()->get_comm());
  static Format sci_lo(4,10,'e');
  static Format sci(8,15,'e');
  static Format sci_hi(10,17,'e');
  string caption;

  increment();
  testflag = 1;
  domain()->time_int->initialize();

  // initialize the control
  control = control_.get();
  assert(control!=0 /* Tried to evaluate on undefined Control */);

  control->set_data(0);
  control->finalize(0);

  ObjFunc J( control, objective, comm );

#ifdef DGM_STATE_USE_DTK_TIMEINTEGRATE
  compositeFunc->reset(&J);
#endif

  domain()->prepareToAdvance();

  Stopwatch wall; wall.start();
  string timestamp = comm->dateTime();
  comm->cout() << "Starting function evaluation on " << timestamp << endl;
  for(domain()->lstep=1; domain()->lstep<=npredict; domain()->lstep++) {
    domain()->step++;
#ifdef DGM_STATE_USE_DTK_TIMEINTEGRATE
    if (DTK_ti.get()) {
      DTK_ti->advance(&*compositeFunc);
    } else {
      domain()->time_int->advance(domain(),&J);
    }
#else
    domain()->time_int->advance(domain(),&J);
#endif
    // Added optional diagnostics to see what is going wrong in the linesearch
#ifdef DGM_STATE_VERBOSE_TEST
    const int iter = 0;
    if (domain()->lstep%domain()->ntout==0)
      domain()->get_comm()->cout()<<setw(6)<<domain()->lstep<<setw(6)
                  <<domain()->step<<sci(domain()->t)<<sci(domain()->dt)<<endl;
    if (domain()->lstep%domain()->Ntout==0) {
      if (defined<Ordinal>(iter)) {
        char tmp[128];
#ifdef DGM_PARALLEL
        string fname;
        if (iter==0)
          sprintf(tmp,"%s.%lld.rst","test",(long long)domain()->step);
        else
          sprintf(tmp,"%s.%lld_%lld.rst","test",(long long)domain()->step,
                  (long long)iter);
        fname = tmp;
        domain()->write(fname,domain()->U);
#else
        char buffer[128];
        sprintf(buffer,"State at t = %11.4e, step = %lld",domain()->t,
                (long long)domain()->step);
        caption = buffer;
        if (iter==0)
          sprintf(tmp,"%s.%lld.dat","test",(long long)domain()->step);
        else
          sprintf(tmp,"%s.%lld_%lld.dat","test",(long long)domain()->step,
                  (long long)iter);
        domain()->U.tecplot(tmp,caption);
#endif
      }
      domain()->U.norm();
    }
#endif
  }
  timestamp = comm->dateTime();
  comm->cout() << "Finished function evaluation on " << timestamp << " in "
               << sci_lo(wall.stop()) << " sec" << endl;
  testflag = 0;
  J.add_terminal(domain()->U);
  J.globalize();
  // Sometimes it is nice to output the parts of the objective
  if (outputTest()) {
    comm->cout()<<"J = "<<sci_hi(J.value())<<endl;
    vector<string> names = J.names();
    dVector &terms = J.terms();
    for (Ordinal i=0; i<J.size(); ++i) {
      comm->cout()<<"  J_{"<<names[i]<<"} = "<<sci_hi(terms[i])<<endl;
    }
  }
  return J.value();
}

//=============================================================================

/// Checkpointing interface
/** Do the bear minimal steps needed to initialize the State to begin forward
    computations. */
void State::atomic_initialize() {
  const DGM::Comm::Ptr comm(domain()->get_comm());
  if (1 < domain()->verbosity())
    comm->cout()<<"State::atomic_initialize()"<<endl;
  // make a new ObjFunc object for this control and objective
  objfunc.reset( new ObjFunc(control, objective, comm) );
  // SSC:  why would be always set_data(0) here?
  control->set_data(0);
}

/// Checkpointing interface
/** Advance from current lstep to nstep using current Control and ObjFunc. */
Scalar State::atomic_advance(const Ordinal nstep) {
  const DGM::Comm::Ptr comm(domain()->get_comm());
  if (1 < domain()->verbosity())
    comm->cout()<<"State::atomic_advance("<<nstep<<")"<<endl;
  testflag = 1;                               // turn off default I/O
  domain()->time_int->initialize();           // setup substep = 0
  Ordinal npredict = control->get_npredict();
  if (domain()->lstep==0) domain()->prepareToAdvance();
  for (domain()->lstep++; domain()->lstep<=nstep; domain()->lstep++) {
    domain()->step++;
    domain()->time_int->advance(domain(),objfunc.get());
  }
  if (1<nstep) atomic_advances(nstep);
  testflag = 0;                               // turn I/O back on
  if (domain()->lstep==npredict) objfunc->add_terminal(domain()->U);
  objfunc->globalize();
  return objfunc->value();
}

/// Checkpointing interface
/** Advance from current lstep to nstep using current Control and ObjFunc. */
Scalar State::atomic_advance(const Ordinal lstep, const Ordinal nstep) {
  const DGM::Comm::Ptr comm(domain()->get_comm());
  if (1 < domain()->verbosity())
    comm->cout()<<"State::atomic_advance("<<lstep<<","<<nstep<<")"<<endl;
  atomic_initialize();
  domain()->time_int->initialize();           // setup substep = 0
  Ordinal npredict = control->get_npredict();
  domain()->lstep = lstep;
  domain()->step = lstep;
#if 0
  // A diagnostic to track what recomputation is done
  comm->cout()<<"State::atomic_advance from "<<lstep
              <<" to "<<lstep+nstep<<endl;
#endif
  if(domain()->lstep==0) domain()->prepareToAdvance();
  for (domain()->lstep++; domain()->lstep<=lstep+nstep; domain()->lstep++) {
    domain()->step++;
    domain()->time_int->advance(domain(),objfunc.get());
  }
  if (1<nstep) atomic_advances(nstep);
  if (domain()->lstep==npredict) objfunc->add_terminal(domain()->U);
  objfunc->globalize();
  return objfunc->value();
}

//=============================================================================

Scalar State::advance( const Ordinal npredict, Control::Ptr control_,
                       const Ordinal outer) {
  if (npredict==0) return 0;

  const DGM::Comm::Ptr comm(domain()->get_comm());
  const string &root(domain()->root);
  static Format sci(6,15,'e');
  char tmp[BUFLEN];

  increment();
  testflag = 1;
  domain()->time_int->initialize();

  // initialize the control
  control = control_.get();
  assert(control!=0 /* Tried to evaluate on undefined Control */);
  control->set_data( 0 );

  ObjFunc J( control, objective, domain()->get_comm() );

  domain()->response->probe( domain()->U, domain()->root, domain()->t, false );

#ifdef DGM_PARALLEL
  string fname;
  sprintf(tmp,"%s.%lld.rst",root.c_str(),(long long)domain()->step);
  fname = tmp;
  domain()->write(fname,domain()->U);
#else
  sprintf(tmp,"%s.%lld.dat",root.c_str(),(long long)domain()->step);
  char buffer[80];
  string caption;
  sprintf(buffer,"State IC at t = %11.4e, step = %lld",
          domain()->t,(long long)domain()->step);
  caption = buffer;
  domain()->U.tecplot(tmp,caption);
#endif
  if(comm->Master())
    comm->cout() << "Advancing solution " << npredict
                 << " time steps" << endl;

  Scalar ctime=0, stime=0, ttime=0;
  Ordinal cnt=0;
  Stopwatch cpu; cpu.start();
  domain()->prepareToAdvance();
  for (domain()->lstep=1; domain()->lstep<=npredict; domain()->lstep++) {
    domain()->step++;
    domain()->time_int->advance(domain(),&J);
    ctime = cpu.restart();
    if (domain()->lstep>1) { 
      ttime += ctime; stime += ctime*ctime; cnt++; 
    }
    if (domain()->lstep%domain()->ntout==0)
      comm->cout()<<setw(8)<<domain()->lstep<<sci(domain()->t)
                  <<sci(domain()->dt)<<sci(domain()->CFL)<<sci(ctime)<<endl;
    if (domain()->lstep%domain()->Ntout==0) {
#ifdef DGM_PARALLEL
      string fname;
      sprintf(tmp,"%s.%lld.rst",root.c_str(),(long long)domain()->step);
      fname = tmp;
      domain()->write(fname,domain()->U);
#else
      sprintf(buffer,"State at t = %11.4e, step = %lld",
              domain()->t,(long long)domain()->step);
      caption = buffer;
      sprintf(tmp,"%s.%lld.dat",root.c_str(),(long long)domain()->step);
      domain()->U.tecplot(tmp,caption);
#endif
      domain()->U.norm();
      cpu.restart();
    }
    if (domain()->step%domain()->Ntprb==0)
      domain()->response->probe( domain()->U, domain()->root, domain()->t,
                                            domain()->lstep==npredict );
  }
  testflag = 0;
  J.add_terminal(domain()->U);
  J.globalize();
  domain()->get_comm()->cout()<<" J = "<<sci(J.value())<<endl;
  return J.value();
}

//=============================================================================

#ifdef DGM_USE_TIME_REG

// State computing with Time regularization
Scalar State::compute(const Ordinal npredict, Control::Ptr gt_control_,
                      Control::Ptr control_, const Ordinal iter) {
  const DGM::Comm::Ptr comm(domain()->get_comm());
  const string &root(domain()->root);
  static Format sci(6,15,'e');
  char tmp[BUFLEN];

  increment();
  domain()->time_int->initialize();

  // initialize the control
  control = control_.get();
  assert(control!=0 /* Tried to evaluate on undefined Control */);
  control->set_data(0);

  gt_control_->set_data(0,0);

  ObjFunc J(gt_control_.get(), control.get(), objective, comm);

#ifndef DGM_PARALLEL
  sprintf(tmp,"%s.%lld_%lld.dat",root.c_str(),(long long)0,(long long)iter);
  domain()->U.tecplot(tmp,"State IC");
#endif

  if (iter==0) {
    comm->cout() << "Advancing solution " << npredict
                 << " time steps" << endl;
  } else {
    comm->cout() << "Predicting solution " << npredict
                 << " time steps" << endl;
  }

  Scalar ctime=0, stime=0, ttime=0;
  Ordinal cnt=0;
  Stopwatch cpu; cpu.start();
  domain()->prepareToAdvance();
  for (domain()->lstep=1; domain()->lstep<=npredict; domain()->lstep++) {
    domain()->step++;

    domain()->time_int->advance(domain(), &J);

    ctime = cpu.restart();
    if (domain()->lstep>1) { 
      ttime += ctime; stime += ctime*ctime; cnt++; 
    }
    if (domain()->lstep%domain()->ntout==0)
      comm->cout()<<setw(8)<<domain()->lstep<<sci(domain()->t)
                  <<sci(domain()->dt)<<sci(domain()->CFL)<<sci(ctime)<<endl;
    if (domain()->lstep%domain()->Ntout==0) {
      if (defined<Ordinal>(iter)) {
#ifdef DGM_PARALLEL
        string fname;
        sprintf(tmp,"%s.%lld_%lld.rst",root.c_str(),(long long)domain()->lstep,
                (long long)iter);
        fname = tmp;
        domain()->write(fname,domain()->U);
#else
        sprintf(tmp,"%s.%lld_%lld.dat",root.c_str(),(long long)domain()->lstep,
                (long long)iter);
        domain()->U.tecplot(tmp,"State");
#endif
      }
      domain()->U.norm();
      cpu.restart();
    }
  }
#ifdef DGM_PARALLEL
  Scalar atime=0, otime=0, xtime=0, ntime=0;
  comm->SumAll( &ttime, &atime, 1 );  // average cpu time
  comm->SumAll( &stime, &otime, 1 );  // standard deviation of the cpu time
  comm->MaxAll( &ttime, &xtime, 1 ); 
  comm->MinAll( &ttime, &ntime, 1 ); 
  Ordinal n = max(1,cnt*comm->NumProc());
  atime /= n; otime /= n; xtime /= max(1,cnt); ntime /= max(1,cnt);
  Scalar stdev = ::sqrt(otime - atime*atime);
  comm->cout() << "Average time per step: " << sci(atime)
               << ", standard deviation:  " << sci(stdev) 
               << ", maximum:  " << sci(xtime) 
               << ", minimum:  " << sci(ntime) 
               << endl;
#endif

  Scalar Jvalue=0;
  J.value() += J.terminal( domain()->U, npredict );
  comm->SumAll( &J.value(), &Jvalue, 1 );
  comm->cout()<<"RK integrated J = "<<Jvalue<<endl;
  J.stat();  // Statistics
  return Jvalue;
}

// Testflow with Time regularization
Scalar State::test(const Ordinal npredict, Control::Ptr gt_control_,
                   Control::Ptr control_) {
  const DGM::Comm::Ptr comm(domain()->get_comm());
  const string &root(domain()->root);

  testflag = 1;

  domain()->time_int->initialize();

  control_->set_data(0);
  gt_control_->set_data(0,0);

  ObjFunc J( gt_control_.get(), control_.get(), objective, comm );
  domain()->prepareToAdvance();
  for(domain()->lstep=1; domain()->lstep<=npredict; domain()->lstep++) {
    domain()->step++;
    domain()->time_int->advance(domain(),&J);
  }
  testflag = 0;

  Scalar Jvalue;
  J.value() += J.terminal( domain()->U, npredict );
  comm->SumAll( &J.value(), &Jvalue, 1 );
  comm->cout()<<"RK integrated J = "<<Jvalue<<endl;
  J.stat();   // Statistics
  return Jvalue;
}

Scalar State::advance( const Ordinal npredict, Control::Ptr gt_control_,
                       Control::Ptr control_, const Ordinal outer) {
  const DGM::Comm::Ptr comm(domain()->get_comm());
  const string &root(domain()->root);
  static Format sci(6,15,'e');
  char tmp[BUFLEN];

  increment();
  testflag = 1;

  domain()->time_int->initialize();

  // initialize the control
  control = control_.get();
  assert(control!=0 /* Tried to evaluate on undefined Control */);
  control->set_data(0);
  gt_control_->set_data(0,0);

  ObjFunc J(gt_control_.get(), control.get(), objective, comm );

#ifdef DGM_PARALLEL
  string fname;
  sprintf(tmp,"%s.%lld_%lld.rst",root.c_str(),(long long)0,(long long)outer);
  fname = tmp;
  domain()->write(fname,domain()->U);
#else
  sprintf(tmp,"%s.%lld_%lld.dat",root.c_str(),(long long)0,(long long)outer);
  domain()->U.tecplot(tmp,"State IC");
#endif
  if(comm->Master())
    comm->cout() << "Continue advancing solution " << npredict
                 << " time steps" << endl;
  domain()->prepareToAdvance();
  for (domain()->lstep=1; domain()->lstep<=npredict; domain()->lstep++) {
    domain()->step++;
    domain()->time_int->advance(domain(),&J);
    if (domain()->lstep%domain()->ntout==0)
      comm->cout()<<setw(8)<<domain()->lstep<<sci(domain()->t)
                  <<sci(domain()->dt)<<endl;
    if (domain()->lstep%domain()->Ntout==0) {
#ifdef DGM_PARALLEL
      string fname;
      sprintf(tmp,"%s.%lld_%lld.rst",root.c_str(),(long long)domain()->lstep,
              (long long)outer);
      fname = tmp;
      domain()->write(fname,domain()->U);
#else
      sprintf(tmp,"%s.%lld_%lld.dat",root.c_str(),(long long)domain()->lstep,
              (long long)outer);
      domain()->U.tecplot(tmp,"State");
#endif
      domain()->U.norm();
    }
  }
  testflag = 0;
  Scalar Jvalue;
  J.value() += J.terminal( domain()->U, npredict );
  comm->SumAll( &J.value(), &Jvalue, 1 );
  comm->cout()<<"RK integrated J = "<<Jvalue<<endl;
  J.stat();
  return Jvalue;
}

#endif  // DGM_USE_TIME_REG

//=============================================================================
void State::store(vField &Uf, const Ordinal istep, const Ordinal sstep) {
  if (testflag) return;
  const int ssiorder = domain()->get_ssiorder();
  if ( (ssiorder < 0) || (sstep == 0) ) {
    const string name = domain()->mkname(0,istep,sstep);
#ifdef DGM_USE_GRIEWANK
    griewank.local_write(istep, sstep, name, Uf, domain());
#else
    in_core_storage.local_write(name, Uf, domain());
#endif
  }
}

void State::local_load(vField &Uf, const Ordinal istep, 
		       const Ordinal sstep, Domain *d) const {
  const string name = d->mkname(0,istep,sstep);
#ifdef DGM_USE_GRIEWANK
  griewank.local_read(istep, sstep, name, Uf, d);
#else
  in_core_storage.local_read(name, Uf, d);
#endif
}

void State::load(vField &Uf, const Ordinal istep, const Ordinal sstep) {
  const int ssiorder = domain()->get_ssiorder();
  if ( (ssiorder < 0) || (sstep == 0) ) {
    local_load(Uf, istep, sstep, domain());
  } else {
    interpolate_field(Uf, istep, sstep, domain());
  }
}

void State::load_field(vField &Uf, const Ordinal istep,
                       const Ordinal sstep) const {
  const int ssiorder = domain()->get_ssiorder();
  if ( (ssiorder < 0) || (sstep == 0) ) {
    local_load(Uf, istep, sstep, const_cast<Domain*>(domain()));
  } else {
    interpolate_field(Uf, istep, sstep, const_cast<Domain*>(domain()));
  }
}

void State::interpolate_field(vField &Uf, const Ordinal istep, 
			      const Ordinal sstep, Domain *d) const {
  const int ssiorder = d->get_ssiorder();
  switch (ssiorder) {
  case 1: // Use the left end point
    {
      local_load(Uf, istep, 0, d);
      break;
    }
  case 2: // Two-node linear interpolation
    {
      if (Uf2.size() == 0) Uf2.clone(Uf);
      // Coefficients for interpolation
      const Scalar a0 = ss_rtime[sstep];
      const Scalar a1 = 1. - a0;

      // Load states at step0 (as Uf) and step1 (as Uf2)
      local_load(Uf,  istep  , 0, d);
      local_load(Uf2, istep+1, 0, d);

      // Interpolate
      axpby(a0, Uf2, a1, Uf, Uf); // Uf = a0*Uf + a1*Uf2
      break;
    }
  case 4: // Four-node cubic interpolation
    {
      Scalar max_istep = control->get_npredict();
      int ioffset = -1;
      if ((istep > 0) && ((istep+1) < max_istep)) {
	ioffset = -1;        // Use centered interpolation
      } else if((istep == 0) && ((istep+2) < max_istep)) {
	ioffset =  0;        // Use right-sided interpolation
      } else if(((istep + 1) == max_istep) && ((istep-1) > 0)) {
	ioffset = -2;        // Use left-sided interpolation
      } else {
	throw DGM::exception("State::load could not find enough steps for cubic interpolation");
      }
      if (Uf2.size() == 0) Uf2.clone(Uf);

      // Create interpolation coefficients
      const Scalar t = ss_rtime[sstep] - ioffset;
      const Scalar a0 = (t-1)*(t-2)*(t-3)/(-6.);
      const Scalar a1 = (t-0)*(t-2)*(t-3)/( 2.);
      const Scalar a2 = (t-0)*(t-1)*(t-3)/(-2.);
      const Scalar a3 = (t-0)*(t-1)*(t-2)/( 6.);
      
      // Load states at step0 (as Uf2) and step1 (as Uf)
      local_load(Uf2, istep+ioffset+0, 0, d);
      local_load(Uf , istep+ioffset+1, 0, d);
      axpby(a0, Uf2, a1, Uf, Uf); // Uf = a1*Uf + a0*Uf2

      // Load state at step2 (as Uf2)
      local_load(Uf2, istep+ioffset+2, 0, d);
      axpby(a2, Uf2, 1., Uf, Uf); // Uf = Uf + a2*Uf2

      // Load state at step3 (as Uf2)
      local_load(Uf2, istep+ioffset+3, 0, d);
      axpby(a3, Uf2, 1., Uf, Uf); // Uf = Uf + a3*Uf2
      break;
    }
  default:
    throw DGM::exception("State::load unsupported interpolation order = "+asString(ssiorder));
  }
}

} // namespace DGM
