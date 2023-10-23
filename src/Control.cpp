/** \file Control.cpp
    \brief Control base class implementation
    \author Scott Collis
    \author Noel Belcourt
*/

// system includes
#include <algorithm>
#include <cassert>
#include <cmath>
#include <functional>
#include <iterator>
#include <numeric>
#include <typeinfo>

// boost includes
#include "boost/numeric/conversion/cast.hpp"
using boost::numeric_cast;

// DGM includes
#ifdef DGM_PARALLEL
#include "MpiComm.hpp"
#endif
#include "TimeInt.hpp"
#include "Control.hpp"
#include "Ctrl.hpp"
#include "Domain.hpp"
#include "State.hpp"
#include "Function.hpp"
#include "Source.hpp"
#include "BC.hpp"
#include "IC.hpp"
#include "Parameter.hpp"

// set the default gradient testing to "off"
#ifndef DGM_TEST_GRADIENT
#define DGM_TEST_GRADIENT 0
#endif

namespace DGM {

/// Constructor
Control::Control(DGM::ArgList &args, State *state_,
                 const DGM::Comm::Ptr comm_) :
  params(Table()), gnum(0), glen(0), state(state_), comm(comm_),
  controlType(CONTROL), verb(comm->verbosity()>3 ? 1 : 0)
{
  if (verb) comm->cout() << "Control constructor for type "
                         << control_type() << endl;

  // set default values
  params["dt"] = 0.001;                    // root of the input file names
  params["inttype"] = TimeInt::UNDEFINED;  // Undefined time integration
  params["npredict"] = 100;                // predictive steps

  // get basic information from argument list
  code = args.front();
  root = args.back();

  // read parameters from an input file
  params.read( root+".inp" );

  // override from command line arguments
  parse_args( args );

  // initalization
  dt        = params["dt"];
  npredict  = params["npredict"];

  // setup temporal data length
  nsstep = state->domain()->time_int->numsubstep();
  npp = nsstep*npredict+1;

  // parallel processing data-structures
  glen = 0;
  global_len.resize(1);
  global_len = 0;
  global_disp.resize(1);
  global_disp = 0;
}

/// Copy constructor
/** \warning is copying the phi_db the best thing to do?
 *  This means that the copied Control object shares the exact same collection
 *  of Control::Entry objects.  This is okay because the actual storage,
 *  \f$phi\f$, is distinct but this does require some care. */
Control::Control(const Control* in) :
  gnum(in->gnum),
  glen(in->glen),
  state(in->state),
  comm(in->comm),
  controlType(in->control_type()),
  verb(in->verb),
  phi_db(in->phi_db)
{
  if (verb) comm->cout() << "Control::Control(const Control*) for type "
                         << control_type() << endl;
  params = in->params;

  // control data information
  phi.resize( in->phi.size() );
  phi = in->phi;
  // if costs are allocated, allocate and copy
  if(in->costs.size()>0) {
    costs.resize(in->costs.size());
    costs = in->costs;
  }

  // run information
  code = in->code;
  root = in->root;

  // time-stepping information
  dt = in->dt;
  npredict = in->npredict;
  nsstep = in->nsstep;
  npp = in->npp;

  // parallel processing data structures
  global_len.resize(in->global_len.size());
  global_len = in->global_len;
  global_disp.resize(in->global_disp.size());
  global_disp = in->global_disp;
}

/// Parse parameters from the argument list
void Control::parse_args( DGM::ArgList &args ) {
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

/// Destructor
Control::~Control() {
  if (verb) comm->cout() << "~Control()" << endl;
}

/// Setup the Control data-structures and prepare for parallel processing
void Control::setup() {
  if (verb) comm->cout() << "Control::setup()" << endl;
  Ordinal phi_size = 0;

  // get the state domain
  Domain *omega(state->domain());

  //===========================================================================
  //  Source terms
  //===========================================================================

  comm->cout()<<"  Looping over source controls..."<<endl;
  // loop through the sources to build Entries
  for (Source::db_citr i=omega->Source_db.begin();
       i!= omega->Source_db.end(); ++i) {
    if (i->second->ctrl()) {
      i->second->ctrl()->initialize();
      Ctrl *ctrl(i->second->ctrl());
      // get the len/disp for the Source control when in parallel
      GlobalSize cglen(0);
      CMC::Vector<GlobalSize,LocalSize> cdisp;
      CMC::Vector<LocalSize,LocalSize> clen;
      if (!ctrl->get_parallel_info(cglen,cdisp,clen)) {
        // Ctrl object is not parallel-aware so assume it is a nodal vField
        // this block of code is retained for backwards compatibility but
        // can/should be removed once every Ctrl object supples a
        // get_parallel_info method
        GlobalSize size=0;
#ifdef DGM_PARALLEL
        // WARNING: this only works if the source has a field that is
        // distributed over the domain so generate an error if otherwise
        if (ctrl->F.size()==0) {
          comm->cout()<<"Error: Ctrl "<<i->first
                      <<" has no vField therefore parallel I/O will "
                      <<"currently fail.  \nYou should implement the "
                      <<"get_parallel_info method for this object."<<endl;
          comm->exit();
        }
#endif
        for (vField::size_type n=0; n<ctrl->F.size(); n++)
          size += ctrl->F[n]->partition->nodal_disp.size();
        // make sure that local data-structures can address global size
        const LocalSize lsize = numeric_cast<LocalSize>(size);
        cdisp.resize(lsize);
        clen.resize(lsize);
        Ordinal index(0);
        cglen=0;
        for (vField::size_type n=0; n<ctrl->F.size(); n++) {
          CMC::Vector<Size,Ordinal> &nodal_disp(ctrl->F[n]->
                                                partition->nodal_disp);
          CMC::Vector<Ordinal,Ordinal> &nodal_len(ctrl->F[n]->
                                                  partition->nodal_len);
          const GlobalSize nodal_glen(ctrl->F[n]->partition->nodal_glen());
          for (Ordinal j=0; j<nodal_disp.size(); j++) {
            cdisp[index] = nodal_disp[j] + cglen;
            clen[index] = nodal_len[j];
            index++;
          }
          cglen += nodal_glen;
        }
      }
      Entry::Ptr entry(new Entry(this, i->first, phi_size, npp,
                                 ctrl, dt, cdisp, clen, cglen, comm));
      phi_db.push_back(entry);
      phi_size += phi_db.back()->length;
      comm->cout() <<"  Found source control: " << i->first
#ifdef DGM_CONTROL_DETAILS
                   <<", ctrl_size = " << phi_db.back()->ctrl_size()
                   <<", offset = "<< phi_db.back()->offset
                   <<", length = "<< phi_db.back()->length
#endif
                   << endl;
    }
  }
  
  //===========================================================================
  //  Parameters
  //===========================================================================

  /// \todo Implement parameter logic here...
  
#if __cplusplus >= 201103L
  // loop through the parameters to build Entries
  comm->cout()<<"  Looping over parameter controls..."<<endl;
  for (auto i=omega->Param_db.begin(); i!= omega->Param_db.end(); ++i) {
    if (i->second->ctrl()) {
      comm->cout()<<"  Found parameter control: "<<i->first<<endl;
    }
  }
#endif

  //===========================================================================
  //  Initial conditions
  //===========================================================================

  /// \todo Implement initial condition logic here...
  
  comm->cout()<<"  Looping over initial condition controls..."<<endl;
  if (omega->initialCondition) {
    if (omega->initialCondition->ctrl()) {
      comm->cout()<<"  Found initial condition control: "<<endl;
    }
  }

  //===========================================================================
  //  Boundary conditions
  //===========================================================================

  comm->cout()<<"  Looping over boundary controls..."<<endl;
  // SSC:  it really shouldn't be necessary to zero the ctrl size but
  // as it is supposed to be initialized to zero but, it causes no harm
  for (LocalSize n=0; n<omega->U[0]->nbc; n++) {
    if ( omega->BC_db.find(omega->U[0]->bc[n]->type) == omega->BC_db.end() ) {
      DGM::Comm::World->error("    Unknown BC type (root.bc) = "
                              + omega->U[0]->bc[n]->type);
    }
    BC::db_citr i = omega->BC_db.find(omega->U[0]->bc[n]->type);
    if (i->second->ctrl()) i->second->ctrl()->size(0);
  }
  // loop through the state boundaries and accumulate ctrl sizes
  for (LocalSize n=0; n<omega->U[0]->nbc; n++) {
    BC::db_citr i = omega->BC_db.find(omega->U[0]->bc[n]->type);
    if (i->second->ctrl()) {
      const Ordinal new_size = i->second->ctrl()->size() +
                               omega->U[0]->bc[n]->S->qtot();
      i->second->ctrl()->size(new_size);
    }
  }

  // loop through the boundary conditions and initialize controls
  for (BC::db_citr i=omega->BC_db.begin(); i!= omega->BC_db.end(); ++i) {
    if (i->second->ctrl()) {
      i->second->ctrl()->initialize();
      // get the len/disp for the Boundary control
      CMC::Vector<GlobalSize,LocalSize> cdisp;
      CMC::Vector<LocalSize,LocalSize> clen;
      GlobalSize glen=0;
#ifdef DGM_PARALLEL
      vector<GlobalSize> global_eid;
      vector<LocalSize> global_sid;
      CMC::Vector<LocalSize,LocalSize> global_len;
      CMC::Vector<GlobalSize,LocalSize> global_disp;
      LocalSize lnbc=0;
      LocalSize sum_size=0;

      // get the global boundary len/disp information
      string fname = omega->root+".bc";
      ifstream in(fname.c_str());
      string buffer,type;
      GlobalSize geid, gnbc;
      LocalSize gsid;
      getline(in,buffer);        // strip off header line
      if (!(in>>gnbc))           // global number of boundary conditions
        error("Cannot read number of boundary conditions",1);
      getline(in,buffer);
      for (GlobalSize j=0; j<gnbc; j++) {
        in >> type >> geid >> gsid;
        if (type == i->second->type) {  // only include the current BC
          global_eid.push_back(geid);
          global_sid.push_back(gsid);
        }
        getline(in,buffer);
      }
      global_disp.resize(global_eid.size());
      global_len.resize(global_eid.size());
      global_len = 0;
      global_disp[0] = 0;
      // get the global displacement/length information
      for(size_t e=0; e<global_eid.size(); e++) {
        if (e!=0) global_disp[e] = global_disp[e-1] + sum_size;
        // if element is in my partition
        if(omega->U[0]->partition->owns(global_eid[e])) {
          const Ordinal leid = omega->U[0]->partition->inc(global_eid[e]);
          global_len[e] = omega->U[0]->el[leid]->side[global_sid[e]]->qtot();
          lnbc++;
        }
        comm->SumAll(&global_len[e], &sum_size, 1 );
        glen += sum_size;
      }
      clen.resize(lnbc);
      cdisp.resize(lnbc);

      // Distribute the displacement/length among processes
      Ordinal n=0;
      for (size_t j=0;j<global_eid.size();j++) {
        if (omega->U[0]->partition->owns(global_eid[j])) {
          cdisp[n] = global_disp[j];
          clen[n]  = global_len[j];
          n++;
        }
      }
#endif  // DGM_PARALLEL
      Entry::Ptr entry(new Entry(this, i->first, phi_size, npp,
                                 i->second->ctrl(), dt,
                                 cdisp, clen, glen, comm) );
      phi_db.push_back(entry);
      phi_size += phi_db.back()->length;
      comm->cout() <<"  Found boundary control: " << i->first
#ifdef DGM_CONTROL_DETAILS
                   <<", ctrl_size = " << phi_db.back()->ctrl_size()
                   <<", offset = "    << phi_db.back()->offset
                   <<", length = "    << phi_db.back()->length
#endif
                   << endl;
    }
  }
  
  // setup the phi control storage vector
  if (verb) comm->cout()<<"  Control::phi_size = "<<phi_size<<endl;
  phi.resize( phi_size );
  zero();

  // get the global control vector length
#ifndef DGM_PARALLEL
  glen = phi_size;
  global_len.resize(1);
  global_disp.resize(1);
  global_disp = 0;
  global_len = numeric_cast<int>(glen);
#else
  comm->SumAll( &phi_size, &glen, 1 );
  global_len.resize(comm->NumProc());
  global_disp.resize(comm->NumProc());
  intVector len(comm->NumProc());
  intVector disp(comm->NumProc());
  len = 1;
  for (int i=0; i<comm->NumProc(); ++i) disp[i] = i;
  {
    const int i = static_cast<int>(phi_size);
    comm->GatherAll( &i, 1, global_len.data(), len.data(), disp.data() );
  }
  global_disp[0] = 0;
  for (int i=1; i<comm->NumProc(); ++i)
    global_disp[i] = global_disp[i-1] + global_len[i-1];
#ifdef DGM_CONTROL_DETAILS
  if (comm->Master()) {
    for (int i=0; i<comm->NumProc(); ++i) {
      cout << "  global_disp["<<i<<"] = " << global_disp[i]
           << ", global_len["<<i<<"] = " << global_len[i] << endl;
    }
  }
#endif
#endif
  comm->cout() << "  Total number of controls = " << phi_db.size() << endl;
  comm->cout() << "  Total length of control vector = " << glen << endl;
}

/** Output the cost of each Entry to a supplied output stream. */
void Control::output_costs(ostream &os) const {
  Ordinal n=0;
  typedef db_t::const_iterator LI;
  for (LI c = phi_db.begin(); c != phi_db.end(); ++c) {
    os<<"J["<<(*c)->name<<"] = "<<costs[n++]<<std::endl;
  }
}

/** Loops over the Ctrl Entries and determine is all are steady. */
bool Control::steady() const{
  typedef db_t::const_iterator LI;
  // loop over controls
  for (LI c = phi_db.begin(); c != phi_db.end(); ++c)
    if(!(*c)->get_ctrl()->steady())
      return false;
  return true;
}

/// Plot the control
void Control::plot(const Ordinal ntout, const Ordinal iter,
                   const string *ext) const {
  typedef db_t::const_iterator LI;
  for (LI c = phi_db.begin(); c != phi_db.end(); ++c)
    (*c)->plot(state->domain()->U,this,npredict,ntout,nsstep,iter,ext);
}
/// Plot the control
void Control::set_parameter(const std::string &key, const std::string &val) {
  typedef db_t::const_iterator LI;
  for (LI c = phi_db.begin(); c != phi_db.end(); ++c)
    (*c)->set_parameter(key,val);
}


/** Gather the distributed DGM::Control::phi and pack it into output which is
    a vector of length Control::glen that is replicated on each processor. */
void Control::gather( dVector &output ) const {
  if (verb) comm->cout() << "Control::gather(...)" << endl;
#ifndef DGM_PARALLEL
  assert( phi.size() == output.size() );
  for(Ordinal i=0; i<phi.size(); i++)
    output[i] = phi[i];
#else
  // Do I need to do a GatherAll or can I send it to the Master only?
  assert( output.size() == glen );
#ifdef DGM_PARALLEL_DEBUG
  cout << "global_len.size()=" << global_len.size() << endl;
  cout << "phi.size()=" << phi.size() << ", global_len[" << comm->MyPID()
       << "]=" << global_len[comm->MyPID()] << endl;
#endif
  output = 0.0;
  typedef db_t::const_iterator LI;
  for (LI c = phi_db.begin(); c != phi_db.end(); ++c)
    (*c)->get_ctrl()->gather(output);
#endif
}

/** Scatter input data from the Master(0) process to the distributed
    DGM::Control::phi.  The input vector must be of length Control::glen
    and it is assumed that only the Master(0) has the correct data. */
void Control::scatter( dVector &input ) {
  if (verb) comm->cout() << "Control::scatter(...)" << endl;
#ifndef DGM_PARALLEL
  assert( phi.size() == input.size() );
  for(Ordinal i=0; i<phi.size(); i++) phi[i] = input[i];
#else
  // scatter from master, assumes that only the Master has the data
  if ( input.size() != glen ) {
    comm->cerr() << "Control vector mismatch:   "
                 << "Dakota control vector size = " << input.size()
                 << ", DGM Control size = " << glen << endl;
    comm->exit(DGM::FAILURE);
  }
  typedef db_t::const_iterator LI;
  for (LI c = phi_db.begin(); c != phi_db.end(); ++c) {
    (*c)->get_ctrl()->scatter(input);
    (*c)->get_data(0, this);
  }
#endif
}

/// Fill the initial Control phi vector from the Ctrl entries
/** \note This method will fail if you attempt to fill
          using an unsupported time integration scheme.                  */
void Control::initialize() {
  static bool firsttime=true;
  if (verb) comm->cout() << "Control::initialize()"<<endl;
  if (firsttime) {
    //    comm->cout()<<"WARNING: Control::initialize() not implemented "
    //                  "for all methods"<<endl;
    firsttime=false;
  }
  typedef db_t::iterator LI;
  for (LI c = phi_db.begin(); c != phi_db.end(); ++c) {
    if ((*c)->has_fill() && !(*c)->filled()) {
      // make a reference to avoid potentially-evaluated-expression warning
      // in clang.
      // DGM::TimeInt &ti = *state->domain()->time_int;

      // Create a vector for storing the relative substep time coefficients
      std::vector<Scalar> a(nsstep);
      // Fill the vector of relative substep time coefficients
      // This will fail if the method does not have getsubtime()
      for (Ordinal s=0; s<nsstep; s++) {
	a[s] = state->domain()->time_int->getsubtime(s);
      }
      // Now fill the control
      for (Ordinal i=0; i<npredict; i++) {
        for (Ordinal s=0; s<nsstep; s++) {
          const Ordinal n = s + i*nsstep;
          const Scalar time = i*dt + a[s]*dt;
          (*c)->fill(n,time,this);
        }
      }
      (*c)->filled(true);
    } else {
      for (Ordinal n=0; n<(*c)->ntime; ++n) (*c)->get_data(n,this);
    }
  }
}

/// Set the Control storage to zero
void Control::zero() {
  if (verb) comm->cout() << "Control::zero()" << endl;
  phi = 0.0;
}

/// Output the control at a given iteration (not currently implemented)
/** \todo Implement the Control::output method */
void Control::output(Ordinal iter_) {
  comm->cout() << "Control::output(int) is not implemented" << endl;
  return;
}

/// Put the control into the BC, Source and other Ctrl objects
void Control::set_data(const Ordinal istep, const Ordinal sstep) {
  if (verb)
    comm->cout() << "Control::set_data("<<istep<<", "<<sstep<<") "
                 << "for type = "<<control_type()<<endl;
  typedef db_t::iterator LI;
  for (LI i = phi_db.begin(); i != phi_db.end(); ++i) {
    DGM::Shared<Entry>::Ptr E = *i;
    E->time(state->domain()->time());
    E->set_data(istep*nsstep+sstep, this);
  }
}

/// Put the control into the BC, Source and other Ctrl objects
void Control::finalize(const Ordinal istep, const Ordinal sstep) {
  if (verb)
    comm->cout() << "Control::finalize("<<istep<<", "<<sstep<<") "
                 << "for type = "<<control_type()<<endl;
  typedef db_t::iterator LI;
  for (LI i = phi_db.begin(); i != phi_db.end(); ++i) {
    DGM::Shared<Entry>::Ptr E = *i;
    E->time(state->domain()->time());
    E->finalize(istep*nsstep+sstep);
  }
}

/// Load the Control by iterating over all entries
void Control::load(dVector &dcontrol, const Ordinal istep,
                   const Ordinal sstep) const {
  if (verb)
    comm->cout() << "Control::load(dVector&, "<<istep<<", "<<sstep<<")"<<endl;
  typedef db_t::const_iterator LI;
  dVector tmp;
  Ordinal offset=0;
  for (LI i = phi_db.begin(); i != phi_db.end(); ++i) {
    tmp.alias( dcontrol, offset, (*i)->ctrl_size() );
    (*i)->load(istep*nsstep+sstep, this, tmp);
    offset += (*i)->ctrl_size();
  }
}

/// Store the Control by iterating over all entries
void Control::store(dVector& dcontrol, const Ordinal istep,
                    const Ordinal sstep) {
  if (verb)
    comm->cout() << "Control::store(dVector&,"<<istep<<", "<<sstep<<")"<<endl;
  typedef db_t::iterator LI;
  dVector tmp;
  Ordinal offset=0;
  for (LI i = phi_db.begin(); i != phi_db.end(); ++i) {
    tmp.alias( dcontrol, offset, (*i)->ctrl_size() );
    (*i)->store(tmp, istep*nsstep+sstep, this);
    offset += (*i)->ctrl_size();
  }
}

/// Control cost for one time-slab for all entries
Scalar Control::cost(const Ordinal istep, const Ordinal sstep) const {
  if (istep*nsstep+sstep == npp) return 0.0;
  if (verb) comm->cout() << "Control::cost("<<istep<<","<<sstep<<")"<<endl;
  Scalar result = 0;
  Ordinal n = 0;
  typedef db_t::const_iterator LI;
  for (LI c = phi_db.begin(); c != phi_db.end(); ++c) {
    // cout << "Computing cost for control " << (*c)->name << endl;
    costs[n] = (*c)->cost(istep*nsstep+sstep, this);
    result += costs[n];
    n++;
  }
  return result;
}

/// (deprecated) Compute the total cost using Trapezoid integration in time
/** \warning Do not use, this is deprecated */
Scalar Control::cost() const {
  comm->cerr() << "ERROR:  Scalar Control::cost() const is deprecated"<<endl;
  comm->exit(DGM::FAILURE);
  Scalar result = 0;
  typedef db_t::const_iterator LI;
  for (LI c = phi_db.begin(); c != phi_db.end(); ++c) {
#if defined(DGM_USE_TIME_REG) || defined(OBJECTIVE_RK4)
    assert(nsstep==4);
    Scalar b[4] = {0.16666666666666667,  // RK4 coefficients
                   0.33333333333333333,
                   0.33333333333333333,
                   0.16666666666666667};
    // time integration using RK4
    for(Ordinal i=0; i<npredict; ++i)
      for(Ordinal j=0;j<nsstep;++j){
        Scalar t_int_factor = b[j]*dt;
        result += t_int_factor * (*c)->cost( i*nsstep+j, this);
    }
#else
    for(Ordinal istep=0; istep<=npredict; ++istep) {
      Scalar t_int_factor = dt;
      if (istep==0||istep==npredict) t_int_factor = pt5*dt;
      result += t_int_factor * (*c)->cost( istep*nsstep, this);
    }
#endif
  }
  return result;
}

/// Defines a DGM::Function class that is compatible with DGM::TimeInt
/** Integrates \f$ zero \f$, this is done just to keep track of time. */
class BoundFunction : public DGM::Function {
  Control *X;              ///< Control object \f$\bX\f$
public:
  BoundFunction( Control *x) :
    DGM::Function(0.0, x->get_dt()), X(x) { }
  Scalar evaluate( const Ordinal istep, const Ordinal sstep ) {
    typedef Control::db_t::const_iterator LI;
    for (LI c = X->phi_db.begin(); c != X->phi_db.end(); ++c) (*c)->time(t);
    X->bound(istep,sstep);
    return zero;
  }
};

/// Bound the entire Control over all time
/** \note If it is important that time be correct when you call Ctrl's bound
    then the experimental time integration interface can do so. */
void Control::bound() {
  if (verb) comm->cout() << "Control::bound() at all time steps" << endl;
#if 1
  BoundFunction f( this );
  //f.evaluate(0,0);        // you might need this for implicit methods
  for(f.lstep=1; f.lstep<=npredict; ++f.lstep)
    state->domain()->time_int->advance( &f );
#else
  for (Ordinal i=0; i<npredict; ++i)
    for (Ordinal j=0; j<nsstep; ++j)
      bound(i,j);
#endif
}

/// Bound the Control on one timestep
void Control::bound(const Ordinal istep, const Ordinal sstep) {
  if (verb) comm->cout() << "Control::bound("<<istep<<","<<sstep<<")" << endl;
  typedef db_t::const_iterator LI;
  for (LI c = phi_db.begin(); c != phi_db.end(); ++c) {
    (*c)->bound(istep*nsstep+sstep, this);
  }
}

/// Defines a DGM::Function class that is compatible with DGM::TimeInt
/** Integrates \f$ zero \f$, this is done just to keep track of time. */
class RealizableFunction : public DGM::Function {
  Control *X;              ///< Control object \f$\bX\f$
  bool _status;            ///< Status
public:
  RealizableFunction( Control *x) :
    DGM::Function(0.0, x->get_dt()), X(x), _status(true) { }
  Scalar evaluate( const Ordinal istep, const Ordinal sstep ) {
    typedef Control::db_t::const_iterator LI;
    for (LI c = X->phi_db.begin(); c != X->phi_db.end(); ++c) (*c)->time(t);
    _status = _status && X->realizable(istep,sstep);
    return zero;
  }
  bool status() const { return _status; }
};

/// Determine realizability of the entire Control over all time
/** \note If it is important that time be correct when you call Ctrl's bound
    then the experimental time integration interface can do so. */
bool Control::realizable() {
  if (verb) comm->cout() << "Control::realizable() at all time steps" << endl;
#if 1
  RealizableFunction f( this );
  //f.evaluate(0,0);             // you might need this for implicit methods
   for(f.lstep=1; f.lstep<=npredict; ++f.lstep)
     state->domain()->time_int->advance( &f );
  return f.status();
#else
  bool result = true;
  for (Ordinal i=0; i<npredict; ++i)
    for (Ordinal j=0; j<nsstep; ++j)
      result = result && realizable(i,j);
  return result;
#endif
}

/// Determine realizability of the Control on one timestep
bool Control::realizable(const Ordinal istep, const Ordinal sstep) {
  if (verb)
    comm->cout() << "Control::realizable("<<istep<<","<<sstep<<")" << endl;
  bool result = true;
  typedef db_t::const_iterator LI;
  for (LI c = phi_db.begin(); c != phi_db.end(); ++c) {
    result = result && (*c)->realizable(istep*nsstep+sstep,this);
  }
  return result;
}

/// Compute the norm of this control based on the Control's inner_product
Scalar Control::norm() const {
  if (verb) comm->cout() << "Control::norm()" << endl;
  return sqrt(inner_product(this));
}

/// Defines a DGM::Function class that is compatible with DGM::TimeInt
/** Integrates \f$ \bX \cdot \bY \f$. */
class ControlFunction : public DGM::Function {
  Control::Entry::Ptr C;   ///< Control entry object
  const Control *X;        ///< Control object \f$\bX\f$
  const Control *Y;        ///< Control object \f$\bY\f$
  const Ordinal nsstep;    ///< Number of substeps
public:
  /// Constructor
  ControlFunction( Control::Entry::Ptr c,
                   const Control *x, const Control *y ) :
    DGM::Function(0.0, x->get_dt()), C(c), X(x), Y(y),
    nsstep(X->get_nsstep()) { }
  /// Provide the Function interface for the inner product of two Controls
  Scalar evaluate( const Ordinal istep, const Ordinal sstep ) {
    // cout << C->comm->MyPID() << ": ControlFunction::evaluation" << endl;
    C->time(t);  // register the current time with the Control::Entry
    return C->inner_product(istep*nsstep+sstep,X,Y);
  }
};

/// Inner product
Scalar Control::inner_product(const Control::Ptr Y) const {
  if (verb) comm->cout() << "Control::inner_product(Control::Ptr)" << endl;
  return inner_product(Y.get());
}

/// Inner product (in space and time as appropriate) for this Control and Y
Scalar Control::inner_product(const Control *Y) const {
  if (verb) comm->cout() << "Control::inner_product(const Control *Y)" << endl;
  Scalar result = 0;
  typedef db_t::const_iterator LI;
  // loop over controls
  for (LI c = phi_db.begin(); c != phi_db.end(); ++c) {
    if((*c)->get_ctrl()->steady()) // steady control
      result += (*c)->inner_product(0, this, Y);
    else {  // unsteady control
#if defined(DGM_USE_TIME_REG) || defined(CONTROL_RK4)
      /// \deprecated Hardwired RK4 integration
      // Warning: hardwired for RK-4 integral weights [gqchen]
      assert(nsstep==4);
      Scalar b[4] = {0.16666666666666667,  // RK4 coefficients
                     0.33333333333333333,
                     0.33333333333333333,
                     0.16666666666666667};
      // time integration using RK4
      for(int i=0; i<npredict; ++i)
        for(int j=0;j<nsstep;++j){
          Scalar t_int_factor = b[j]*dt;
          result += t_int_factor *
            (*c)->inner_product( i*nsstep+j, phi, Y->phi);
        }
#else
      ControlFunction f( *c, this, Y );
      for(f.lstep=1; f.lstep<=npredict; ++f.lstep)
        state->domain()->time_int->advance( &f );
      result += f.value;
#endif
    }
  }
  // should this be here our should it be assumed that the Ctrl will do this?
  Scalar lresult = result;
  comm->SumAll( &lresult, &result, 1 );
  return result;
}

/// Inner products (in space and time as appropriate) for this Control and Y
dVector Control::inner_products(const Control *Y) const {
  if (verb) comm->cout() << "Control::inner_products(const Control *Y)" << endl;
  dVector result(numeric_cast<Ordinal>(num_ctrl()),0.0);
  typedef db_t::const_iterator LI;
  Ordinal i = 0;
  for (LI c = phi_db.begin(); c != phi_db.end(); ++c, ++i) {
    if((*c)->get_ctrl()->steady()) // steady control
      result[i] = (*c)->inner_product(0, this, Y);
    else {  // unsteady control
#if defined(DGM_USE_TIME_REG) || defined(CONTROL_RK4)
      /// \deprecated Hardwired RK4 integration
      assert(nsstep==4);
      Scalar b[4] = {0.16666666666666667,  // RK4 coefficients
                     0.33333333333333333,
                     0.33333333333333333,
                     0.16666666666666667};
      // time integration using RK4
      for(Ordinal n=0; n<npredict; ++n)
        for(Ordinal s=0; s<nsstep; ++s){
          Scalar t_int_factor = b[s]*dt;
          result[i] = t_int_factor *
              (*c)->inner_product(n*nsstep+s,phi,Y->phi);
        }
#else
      ControlFunction f(*c, this, Y);
      for(f.lstep=1; f.lstep<=npredict; ++f.lstep)
        state->domain()->time_int->advance(&f);
      result[i] = f.value;
#endif
    }
  }
  // should this be here our should it be assumed that the Ctrl will do this?
  dVector lresult(result.size()); lresult = result;
  comm->SumAll( lresult.ptr(), result.ptr(), numeric_cast<int>(result.size()));
  return result;
}

/** returns the names for each Ctrl in this Control. */
vector<string> Control::names() const {
  vector<string> result(num_ctrl());
  typedef db_t::const_iterator LI;
  size_t i = 0;
  for (LI c = phi_db.begin(); c != phi_db.end(); ++c, ++i) {
    result[i] = (*c)->name;
  }
  return result;
}

/// Compute a contribution to the gradient (preferred interface)
void Control::gradient( const vField &S, const vField &A, Control::Ptr G,
                        const Ordinal istep, const Ordinal sstep) {
  if (verb) comm->cout() << "Control::gradient(...)" << endl;
  typedef db_t::const_iterator LI;
  for (LI c = phi_db.begin(); c != phi_db.end(); ++c) {
    (*c)->gradient( istep, sstep, this, S, A, G.get());
  }
}

/// Compute a contribution to the gradient (preferred interface)
void Control::gradient( const vField &S, const vField &A, Control &G,
                        const Ordinal istep, const Ordinal sstep) {
  if (verb) comm->cout() << "Control::gradient(...)" << endl;
  typedef db_t::const_iterator LI;
  for (LI c = phi_db.begin(); c != phi_db.end(); ++c) {
    (*c)->gradient(istep, sstep, this, S, A, &G);
  }
}

/// Compute Hessian vector product for the regularization term
void Control::HessVecProd_reg(const Control &x,
                              const Control &dx,
                              Control &H_dx,
                              const Ordinal istep,
                              const Ordinal sstep) {
  if (verb) comm->cout() << "Control::gradient(...)" << endl;
  typedef db_t::const_iterator LI;
  for (LI c = phi_db.begin(); c != phi_db.end(); ++c) {
    (*c)->HessVecProd_reg(istep, sstep, &x, &dx, &H_dx);
  }
}

/// Computes a contribution to a preconditioner
void Control::computePreconditioner( const vField &S, const vField &A,
                                     Control::Ptr G, const Ordinal istep,
                                     const Ordinal sstep) {
  if (verb)
    comm->cout()<<"Control::computePreconditioner(S,A,G,istep,step)"<<endl;
  typedef db_t::const_iterator LI;
  for (LI c = phi_db.begin(); c != phi_db.end(); ++c) {
    (*c)->computePreconditioner(istep, sstep, this, S, A, G.get());
  }
}

/// Applies a preconditioner
void Control::applyPreconditioner(const Control::Ptr G, Control::Ptr P) {
  if (verb) comm->cout()<<"Control::applyPreconditioner(G,P)"<<endl;
  typedef db_t::const_iterator LI;
  for (LI c = phi_db.begin(); c != phi_db.end(); ++c) {
    (*c)->applyPreconditioner(this, G.get(), P.get());
  }
}

/// Set the Control to a prescribed direction by iterating over entries
/** This is used to call each Entries::set_direction() method.  NOTE that the
    result is normalized by the norm of the resulting Control vector.  This
    method is useful for setting an arbitrary direction for finite difference
    gradient checks. */
void Control::set_direction() {
  if (verb) comm->cout() << "Control::set_direction()" << endl;
  typedef db_t::iterator LI;
  // loop over control entries
  for (LI c = phi_db.begin(); c != phi_db.end(); ++c)
    for (Ordinal i=0; i<(*c)->ntime; ++i) (*c)->set_direction(i, this);
  // normalize direction
  Scalar phi_norm = norm();
  if (phi_norm != 0.0) scale(1.0/phi_norm, phi);
}

struct scalar_abs {
  Scalar operator()(Scalar x) {
    using std::abs;
    return abs(x);
  }
};

struct scalar_sqrt {
  Scalar operator()(Scalar x) {
    using std::sqrt;
    return sqrt(x);
  }
};

struct scalar_inv {
  Scalar operator()(Scalar x) {
    Scalar one = 1.0;
    return one / x;
  }
};

/// Diff two control files given absolute and relative epsilon
int Control::diff(const Control& control, const Scalar aeps,
                  const Scalar reps) {
  using std::isnan;
  int status = 0;
  // iterate Control::Entry's (Ctrl's are shared between Controls)
  typedef db_t::const_iterator LI;
  LI c = phi_db.begin(), c_end = phi_db.end(), c2 = control.phi_db.begin();
  // control databases are same size
  assert(phi_db.size() == control.phi_db.size());
  for (; c != c_end; ++c, ++c2) {
    Ctrl *ctrl = (*c)->ctrl;
    if (ctrl->steady()) { // steady control
      (*c)->set_data(0, this);
      Ctrl *ctrl2 = (*c2)->ctrl;
      assert(ctrl2->steady());  // ensure both controls are steady
      dVector Ydata;
      (*c2)->load(0, &control, Ydata);
      ctrl->diff(*ctrl2, Ydata);
    }
    else {  // unsteady control
#if defined(DGM_USE_TIME_REG) || defined(CONTROL_RK4)
      /// \deprecated Hardwired RK4 integration
      assert(nsstep==4);
      Scalar b[4] = {0.16666666666666667,  // RK4 coefficients
                     0.33333333333333333,
                     0.33333333333333333,
                     0.16666666666666667};
      // time integration using RK4
      for (Ordinal n=0; n<npredict; ++n)
        for (Ordinal s=0; s<nsstep; ++s) {
          int index = n*nsstep+s;
          ctrl->set_data(index, phi);
          dVector Ydata;
          ctrl2->load(index, Control->phi, Ydata);
          ctrl->diff(*ctrl2, Ydata);
        }
#else
#if 0
      ControlFunction f(*c, this, Y);
      for(f.lstep=1; f.lstep<=npredict; ++f.lstep)
        state->domain()->time_int->advance(&f);
      result[i] = f.value;
#endif
#endif
    }
  }
    static int LINF_FAILED(0x01);
    static int L2_FAILED(0x02);
    static int H1_FAILED(0x04);
    static int LINF_REL_FAILED(0x08);
    static int L2_REL_FAILED(0x010);
    static int H1_REL_FAILED(0x020);
    static Format sci(10,18,'e');
    string s(8, ' ');
    // absolute results
    if (aeps >= 0) {
      comm->cout()<<"Absolute Tolerance:  aeps = "<<aeps<<endl;
      for (c = phi_db.begin(); c != c_end; ++c) {
        Ctrl* ctrl = (*c)->ctrl;
        if (ctrl->steady()) { // steady control
          (*c)->set_data(0, this);
          for (vField::size_type i=0; i<ctrl->F.size(); ++i) {
            string s = ctrl->F[i]->get_name();
            comm->cout()<<"Field: "<<setw(5)<<s<<sci(ctrl->Linf[i])
                        <<sci(ctrl->L2[i])<<sci(ctrl->H1[i])
                        <<" (Linf L2 H1)"<<endl;
            if (ctrl->Linf[i]>aeps || isnan(ctrl->Linf[i]))
              status |= LINF_FAILED;
            if (ctrl->L2[i]>aeps || isnan(ctrl->L2[i])) status |= L2_FAILED;
            if (ctrl->H1[i]>aeps || isnan(ctrl->H1[i])) status |= H1_FAILED;
          }
        }
      }
    }
    // relative results
    if (0 <= reps) {
      comm->cout()<<"Relative Tolerance:  reps = "<<reps<<endl;
      for (c = phi_db.begin(); c != c_end; ++c) {
        Ctrl* ctrl = (*c)->ctrl;
        if (ctrl->steady()) { // steady control
          (*c)->set_data(0, this);
          for (vField::size_type i=0; i<ctrl->F.size(); ++i) {
            string s = ctrl->F[i]->get_name();
            comm->cout()<<"Field: "<<setw(5)<<s;
            if (ctrl->rLinf[i]>repsM || isnan(ctrl->rLinf[i])) {
              if (ctrl->Linf[i]/ctrl->rLinf[i]>reps ||
                isnan(ctrl->Linf[i]/ctrl->rLinf[i])) status |= LINF_REL_FAILED;
              comm->cout() << sci(ctrl->Linf[i]/ctrl->rLinf[i]);
            } else
              comm->cout() << sci(ctrl->Linf[i]);
            if (ctrl->rL2[i]>repsM || isnan(ctrl->rL2[i])) {
              if (ctrl->L2[i]/ctrl->rL2[i]>reps ||
                isnan(ctrl->L2[i]/ctrl->rL2[i])) status |= L2_REL_FAILED;
              comm->cout() << sci(ctrl->L2[i]/ctrl->rL2[i]);
            } else
              comm->cout() << sci(ctrl->L2[i]);
            if (ctrl->rH1[i]>repsM || isnan(ctrl->rH1[i])) {
              if (ctrl->H1[i]/ctrl->rH1[i]>reps ||
                isnan(ctrl->H1[i]/ctrl->rH1[i])) status |= H1_REL_FAILED;
              comm->cout() << sci(ctrl->H1[i]/ctrl->rH1[i]);
            } else
              comm->cout() << sci(ctrl->H1[i]);
            comm->cout() <<" (Linf L2 H1)"<<endl;
          }
        }
      }
    }
    if (aeps < 0 && reps < 0) comm->error("Control::diff() No tests requested");

  // Parallel consistent return status
  comm->Broadcast(&status);
  return status;
}

/// sum control file into this control 
int Control::sum(const Control& control2, const double mult,
                 const std::vector<Size>&sub_to_mstr) {
  Control &control1 = *this;
  // control databases are same size
  assert(control1.phi_db.size() == control2.phi_db.size());

  const bool sum_unsteady = mult!=numeric_limits<double>::max();

  const int control2_type = static_cast<int>(control2.control_type());
  const int control1_type = static_cast<int>(control1.control_type());

  typedef db_t::const_iterator LI;
  LI c2 = control2.phi_db.begin();
  LI c1 = control1.phi_db.begin(); 
  LI ce = control1.phi_db.end(); 
  for (; c1 != ce; ++c1, ++c2) {
    const dbEntry_t e1 = *c1;
    const dbEntry_t e2 = *c2;
    Ctrl *ctrl1 = e1->ctrl;
    Ctrl *ctrl2 = e2->ctrl;
    if (ctrl1->steady()) { 
      if (!ctrl2->steady())  
         throw DGM::exception("Control::sum incompatible control classes");

      dVector Ydata;
      e2->load    (0, &control2, Ydata);
      e1->set_data(0, &control1);
      if (sum_unsteady) Ydata *= mult;
      ctrl1->sum(*ctrl2, Ydata, sum_unsteady, sub_to_mstr, 
                  control1_type, control2_type);
      e1->store(Ydata, 0, &control1);
    }
    else {  // unsteady control
      if (ctrl2->steady())  
         throw DGM::exception("Control::sum incompatible control classes");
      for (Ordinal n=0; n<npredict; ++n)
        for (Ordinal s=0; s<nsstep; ++s) {
          dVector Ydata;
          const int index = n*nsstep+s;
          e2->load    (index, &control2, Ydata);
          e1->set_data(index, &control1);
          if (sum_unsteady) Ydata *= mult;
          ctrl1->sum(*ctrl2, Ydata, sum_unsteady, sub_to_mstr, 
                      control1_type, control2_type);
          e1->store(Ydata, index, &control1);
        }
    }
  }
  return 0;
}

/// extract control file from this control 
int Control::ext(Control& control2, 
                 const std::vector<Size>&sub_to_mstr) const {
  const Control &control1 = *this;
  // control databases are same size
  assert(control1.phi_db.size() == control2.phi_db.size());

  typedef db_t::const_iterator LI;
  LI c2 = control2.phi_db.begin();
  LI c1 = control1.phi_db.begin(); 
  LI ce = control1.phi_db.end(); 
  for (; c1 != ce; ++c1, ++c2) {
    const dbEntry_t e1 = *c1;
    const dbEntry_t e2 = *c2;
    Ctrl *ctrl1 = e1->ctrl;
    Ctrl *ctrl2 = e2->ctrl;
    if (ctrl1->steady()) { 
      if (!ctrl2->steady())  
         throw DGM::exception("Control::ext incompatible control classes");

      dVector Ydata;
      e1->set_data(0, &control1);
      e2->load    (0, &control2, Ydata);
      ctrl1->ext(*ctrl2, Ydata, sub_to_mstr);
      e2->store(Ydata, 0, &control2);
    }
    else {  // unsteady control
      if (ctrl2->steady())  
         throw DGM::exception("Control::ext incompatible control classes");
      for (Ordinal n=0; n<npredict; ++n)
        for (Ordinal s=0; s<nsstep; ++s) {
          dVector Ydata;
          const int index = n*nsstep+s;
          e1->set_data(index, &control1);
          e2->load    (index, &control2, Ydata);
          ctrl1->ext(*ctrl2, Ydata, sub_to_mstr);
          e2->store(Ydata, index, &control2);
        }
    }
  }
  return 0;
}

/// Read Control::Entries from a file named fname into Control::phi
/** The return value is the total length of the control data read. */
streamoff Control::read(const string &fname, const streamoff skip) {
  if (verb) comm->cout() << "Control::read("<<fname<<","<<skip<<")" << endl;
  streamoff r_skip(skip);
  typedef db_t::const_iterator LI;
  // loop over control database entries
  for (LI c = phi_db.begin(); c != phi_db.end(); ++c) {
    r_skip = (*c)->read(fname, r_skip, this);
  }
  return r_skip;
}

/// Write Control::Entries from Control::phi into a file named fname
/** The return value is the total length of the control data written. */
streamoff Control::write(const string &fname, const streamoff skip) {
  if (verb) comm->cout() << "Control::write("<<fname<<","<<skip<<")"<<endl;
  streamoff w_skip(skip);
  typedef db_t::const_iterator LI;
  // loop over control database entries
  for (LI c = phi_db.begin(); c != phi_db.end(); ++c) {
    w_skip = (*c)->write(fname, w_skip, this);
  }
  return w_skip;
}

/// Experimental method, may not be useful
void Control::beLinear() {
  typedef db_t::iterator LI;
  for (LI i = phi_db.begin(); i != phi_db.end(); ++i) {
    (*i)->ctrl->beLinear();
  }
}

/// Experimental method, may not be useful
void Control::beNormal() {
  typedef db_t::iterator LI;
  for (LI i = phi_db.begin(); i != phi_db.end(); ++i) {
    (*i)->ctrl->beNormal();
  }
}

//============================================================================
//                   T I M E   R E G U L A R I Z A T I O N
//============================================================================

#ifdef DGM_USE_TIME_REG

/// \warning only works for unsteady control [gqchen]
void Control::axpy( const Scalar a, const Ordinal index_gt, const Control* X,
                    const Ordinal index_g1, const Ordinal index_g2) {
  if (phi.size() != X->phi.size()) {
    comm->cerr()<< "Attempted to axpy incompatible Controls" << endl;
    comm->exit(DGM::FAILURE);
  }
  dVector dg1, dg2;
  dVector dgt;
  typedef db_t::iterator LI;
  for (LI i = phi_db.begin(); i != phi_db.end(); ++i) {
    if(!(*i)->get_ctrl()->steady()) { // unsteady control
      dg1.alias(phi,(*i)->offset + index_g1*(*i)->ctrl_size(),
                (*i)->ctrl_size() );
      dg2.alias(phi,(*i)->offset + index_g2*(*i)->ctrl_size(),
                (*i)->ctrl_size() );
      dgt.alias(X->phi,(*i)->offset + index_gt*(*i)->ctrl_size(),
                (*i)->ctrl_size());
      daxpy(a,dgt,dg1,dg2);
    }
    else {
      // Steady control
    }
  }
}

// ok
void Control::reg_load(dVector& dcontrol, const Ordinal istep,
                       const Ordinal sstep) const {
  typedef db_t::const_iterator LI;
  dVector tmp;
  Ordinal offset=0;
  for (LI i = phi_db.begin(); i != phi_db.end(); ++i) {
    tmp.alias( dcontrol, offset, (*i)->ctrl_size() );
    (*i)->load( istep*nsstep+sstep, phi, tmp );
    scale((*i)->get_ctrl()->get_pt(),tmp);
    offset += (*i)->ctrl_size();
  }
}

/// Compute the cost for one time-slab for the g_t
Scalar Control::cost_t(const Ordinal istep, const Ordinal sstep) const {
  if (istep*nsstep+sstep == npp) return 0.0;
  Scalar result = 0;
  Ordinal n = 0;
  typedef db_t::const_iterator LI;
  for (LI c = phi_db.begin(); c != phi_db.end(); ++c) {
    // cout << "Computing cost for control " << (*c)->name << endl;
    Scalar penalty    =  (*c)->get_ctrl()->get_p();
    SCalar penalty_t  =  (*c)->get_ctrl()->get_pt();
    costs[n] = (*c)->cost( istep*nsstep+sstep, phi );
    if(penalty != 0)
      costs[n] = costs[n]*penalty_t/penalty;
    else{
      comm->cerr()<<"Error: penalty in Control ZERO"<<endl;
      comm->exit(DGM::FAILURE);
    }
    result += costs[n];
    n++;
  }
  return result;
}

#endif   // DGM_USE_TIME_REG

//============================================================================
//                      Control::Entry implementation
//============================================================================

/// Constructor
Control::Entry::Entry(Control *C, const string n, const Ordinal off,
                      const Ordinal nt, Ctrl *c, const Scalar dt_,
                      const CMC::Vector<Size,Ordinal> &cdisp_,
                      const CMC::Vector<Ordinal,Ordinal> &clen_,
                      const Size cglen_, const DGM::Comm::Ptr comm_)
  : verb(comm_->verbosity()>3 ? 1 : 0), control(C), _filled(false), ctrl(c),
    name(n), offset(off), ntime(nt), cglen(0), comm(comm_)
{
  if (ctrl->steady()) {
    ntime = 1;
#if DGM_CONTROL_DETAILS > 1
    comm->cout() << "  Integrating the Control Inline with storage of size "
                 << control->get_nsstep()*ctrl_size() << endl;
#endif
    Grad_data.resize(control->get_nsstep()*ctrl_size());
    Prec_data.resize(control->get_nsstep()*ctrl_size());
    Grad_data = 0.0;
    Prec_data = 0.0;
  }
  // A replicated control only reports a length on the Master
  if ( ctrl->owner() )
    length = ntime*ctrl_size();
  else
    length = 0;

  // set the global disp/len information for control restart
#ifdef DGM_PARALLEL
  // while one could loop over the time levels and write the data, it is
  // potentially faster to do it all in one MPI-IO call
  Ordinal size = cdisp_.size() * ntime;
  cdisp.resize(size);
  clen.resize(size);
  Ordinal index=0;
  for(Ordinal i=0; i<ntime; ++i)
    for (Ordinal j=0; j<cdisp_.size(); ++j) {
      cdisp[index] = cdisp_[j] + i*cglen_;
      clen[index] = clen_[j];
      index++;
    }
  cglen = ntime*cglen_;
#ifdef DGM_CONTROL_DETAILS
  cout << comm->MyPID() << ": Entry.name = " << name
       << ", cdisp.size() = " << cdisp.size()
       << ", clen.size() = " << clen.size() << endl;
#endif
#endif
}

/// Puts the data in global_phi into the ctrl's
void Control::Entry::set_data( const Ordinal index,
                               const dVector &global_phi,
                               const Control::Control_Type type) {
  if (ctrl->steady() && index>0) return;
  if (verb)
    comm->cout() << "Control::Entry::set_data(" << index << ") for "
                 << name << endl;
  const Ordinal i = (ctrl->steady()) ? 0 : index;
  if (ntime<=i) {
    comm->cerr() <<__FILE__<<":"<<__LINE__
     <<" Error ntime is less than i.  ntime:"<<ntime<<" i:"<<i
     <<" Calling abort......"<<endl;
  }
  assert( i < ntime );
#ifdef DGM_CONTROL_DETAILS
  cout<<comm->MyPID()<<": global_phi.size() = "<<global_phi.size()<<endl;
#endif
  dVector view;
  if (ctrl->owner())
    view.alias( *(const_cast<dVector*>(&global_phi)),
                offset+i*ctrl_size(), ctrl_size() );
  if (Control::CONTROL==type)
    ctrl->set_data( view );
  else
    ctrl->set_data_no_transform( view );
}

/// Function class for gradient integration
class GradientFunction : public DGM::Function {
  const dVector &X;        ///< Integrand data
  const Ordinal nsstep;    ///< Number of substeps
  const Size size;         ///< Number of timesteps
  const Size index;        ///< Index within substep
public:
  /// Constructor
  GradientFunction( Control *control, dVector &x, Size size_, Size index_ )
  : DGM::Function(0.0, control->get_dt()), X(x),
    nsstep(control->get_nsstep()), size(size_), index(index_) { }
  /// Provide the Function interface
  Scalar evaluate( const Ordinal istep, const Ordinal sstep ) {
    const Ordinal loc = numeric_cast<Ordinal>(sstep*size+index);
    return X[loc];
  }
};

/// Evaluate the gradient
void Control::Entry::gradient( const Ordinal istep, const Ordinal sstep,
                               const dVector &phi, const vField &S,
                               const vField &A, dVector &Gphi,
                               const Control_Type type) {
  Ordinal index = istep*control->get_nsstep()+sstep;
  if (verb)
    cout << comm->MyPID() << ":  Control::Entry::gradient(...) for index = "
         << index << " for name = " << name << endl;
  dVector Gdata;
  if (ctrl->steady()) {
    set_data(index, phi, type);
    if ( !ctrl->owner() )
      Gdata.resize(ctrl_size());
    else
      Gdata.alias( Grad_data, sstep*ctrl_size(), ctrl_size() );
  } else {
    set_data(index, phi, type);
    if ( !ctrl->owner() )
      Gdata.resize(ctrl_size());
    else
      Gdata.alias( Gphi, offset+index*ctrl_size(), ctrl_size() );
  }
  ctrl->time( control->state->domain()->time() );
  ctrl->objective_function_gradient( S, A, ctrl->time(), Gdata );

#if DGM_TEST_GRADIENT > 1
  Format sci(12,20,'e');
  Scalar pnorm2 = Gdata.Norm2();
  Scalar gnorm2 = 0.0;
  DGM::Comm::World->SumAll( &pnorm2, &gnorm2, 1 );
  DGM::Comm::World->cout() << "||Gdata|| = "<< sci(sqrt(gnorm2)) << endl;
#endif

  // Accumulate steady gradients in time

#if DGM_TEST_GRADIENT > 1
  DGM::Comm::World->cout() << "Control::Entry::gradient: steady = "
      << ctrl->steady() << " index = " << index << " size = "
      << ctrl_size() << endl;
#endif

  /// This now works for RK4, Backward Euler, and Trapezoidal
  /** \note We use the accumulate method on the time integrator as it turns
   *   out that depending on the integrator, the gradient is accumulated more
   *   as Euclidean inner product then as a time integral
   */
  if ( ctrl->steady() && ctrl_size()>0 ) {
    // Make sure the there is a DGM::TimeInt
    if (control->state->domain()->time_int == 0) {
      throw DGM::exception("Optimization currently requires DGM::TimeInt use");
    }
    if ( istep == control->get_npredict() && sstep == 0 ) {
      //cout << "Control::Entry::Gradient inline time integration "
      //     << "zeroing integrand" << endl;
      dVector Grad_int;
      if (!ctrl->owner())
        Grad_int.resize(ctrl_size());
      else
        Grad_int.alias( Gphi, offset, ctrl_size() );
      Grad_int = 0.0;
      // for implicit, the following is currently done twice, once for the end
      // condition, which is thrown away, and once after the first solve, which
      // is correct.  While a bit confusing and wasteful, it is still correct.
      if ( control->state->domain()->time_int->is_implicit() ) {
        for (Ordinal k=0; k<ctrl_size(); k++) {
          GradientFunction f( control, Grad_data, ctrl_size(), k );
          f.lstep = istep;
          control->state->domain()->time_int->accumulate( &f );
          Grad_int[k] += f.value;
          //cout<<"lstep = "<<f.lstep<<", int = "<<f.value
          //    <<", value = "<<Grad_int[k]<<endl;
        }
      }
#if DGM_TEST_GRADIENT > 1
      Format sci(12,20,'e');
      Scalar pnorm2 = Grad_int.Norm2();
      Scalar gnorm2 = 0.0;
      DGM::Comm::World->SumAll( &pnorm2, &gnorm2, 1 );
      DGM::Comm::World->cout() << sci(sqrt(gnorm2)) << endl;
#endif
    }
    if ( istep < control->get_npredict() && sstep == 0 ) {
      //cout << "Control::Entry::Gradient inline time integration" << endl;
      //cout << "index = " << index << " npredict = "
      //     << control->get_npredict() << " istep = " << istep
      //     << " sstep = " << sstep << endl;
      dVector Grad_int;
      if (!ctrl->owner())
        Grad_int.resize(ctrl_size());
      else
        Grad_int.alias( Gphi, offset, ctrl_size() );
      for (Ordinal k=0; k<ctrl_size(); k++) {
        GradientFunction f( control, Grad_data, ctrl_size(), k );
        f.lstep = istep;
        control->state->domain()->time_int->accumulate( &f );
        Grad_int[k] += f.value;
        //cout << "lstep = " << f.lstep<<", int = "<<f.value
        //     << ", value = " << Grad_int[k] << endl;
      }
#if DGM_TEST_GRADIENT > 1
      Format sci(12,20,'e');
      Scalar pnorm2 = Grad_int.Norm2();
      Scalar gnorm2 = 0.0;
      DGM::Comm::World->SumAll( &pnorm2, &gnorm2, 1 );
      DGM::Comm::World->cout() << sci(sqrt(gnorm2)) << endl;
#endif
    }
  }
}

/// Compute the Hessian vector product
void Control::Entry::HessVecProd_reg(const Ordinal istep, const Ordinal sstep,
                                     const dVector &x, const dVector &dx,
                                     dVector &H_dx) {
  DGM_UNDEFINED;
}


/// Compute a preconditioner
/** \note Only supports inline integration
    \warning This has not been fully tested. 
    \todo Need to verify this for both implicit and explicit methods
*/
void Control::Entry::computePreconditioner( const Ordinal istep,
                                            const Ordinal sstep,
                                            const dVector &phi,
                                            const vField &S,
                                            const vField &A,
                                            dVector &Pphi,
                                            const Control::Control_Type type) {

  if ( !ctrl->needsComputePreconditioner() ) return;

  Ordinal index = istep*control->get_nsstep()+sstep;

  if (verb)
    comm->cout() << "Control::Entry::computePreconditioner() for index = "
                 << index<<endl;

  dVector Pdata;
  if (ctrl->steady()) {
    if (Prec_data.size()==0) {
      Prec_data.resize( control->get_nsstep()*ctrl_size() );
      Prec_data = 0.0;
    }
    set_data( index, phi, type );
    Pdata.alias( Prec_data, sstep*ctrl_size(), ctrl_size() );
  } else {
    set_data( index, phi, type );
    Pdata.alias( Pphi, offset+index*ctrl_size(), ctrl_size() );
  }

  ctrl->computePreconditioner( S, A, Pdata );

  // Integrate steady preconditioners in time

  if ( ctrl->steady() && ctrl_size()>0 ) {
    if ( istep == control->get_npredict() && sstep == 0 ) {
      dVector Pcond_int;
      Pcond_int.alias( Pphi, offset, ctrl_size() );
      Pcond_int = 0.0;
      if ( control->state->domain()->time_int->is_implicit() ) {
        for (Ordinal k=0; k<ctrl_size(); k++) {
          GradientFunction f( control, Prec_data, ctrl_size(), k );
          f.lstep = istep;
          control->state->domain()->time_int->advance( &f );
          Pcond_int[k] += f.value;
        }
      }
    }
    if ( istep < control->get_npredict() && sstep == 0 ) {
      dVector Pcond_int;
      Pcond_int.alias( Pphi, offset, ctrl_size() );
      for (Ordinal k=0; k<ctrl_size(); k++) {
        GradientFunction f( control, Prec_data, ctrl_size(), k );
        f.lstep = istep;
        control->state->domain()->time_int->advance( &f );
        Pcond_int[k] += f.value;
      }
    }
  }
}

/// Apply a preconditioner
/** \todo TEST transient preconditioner. */
void Control::Entry::applyPreconditioner( const dVector &phi,
                                          const dVector &Gphi,
                                          dVector &Pphi,
                                          const Control::Control_Type type) {
  if (verb)
    comm->cout() << "Control::Entry::applyPrecondition(phi,Gphi,Pphi)" << endl;
  dVector Gdata, Pdata;
  if (ctrl->steady() ) {
    const int index = 0;
    set_data( index, phi, type);
    Gdata.alias( Gphi, offset + index*ctrl_size(), ctrl_size() );
    Pdata.alias( Pphi, offset + index*ctrl_size(), ctrl_size() );
    ctrl->applyPreconditioner( Gdata, Pdata );
  } else {
    // This needs to be tested!
    for (Ordinal i=0; i<control->get_npredict(); ++i) {
      for (Ordinal j=0; j<control->get_nsstep(); ++j) {
        const int index = i*control->get_nsstep()+j;
        set_data( index, phi, type);
        if (ctrl->owner()) {
          Gdata.alias( Gphi, offset + index*ctrl_size(), ctrl_size() );
          Pdata.alias( Pphi, offset + index*ctrl_size(), ctrl_size() );
          ctrl->applyPreconditioner( Gdata, Pdata );
        }
      }
    }
  }
}

/// Plot the control entry
void Control::Entry::plot(const vField &S, const dVector &Gphi,
                          const Ordinal npredict, const Ordinal ntout,
                          const Ordinal nsstep, const Ordinal riter,
                          const string *ext, const int control_type) const {
  if (ext) {
    // cout <<__FILE__<<":"<<__LINE__<<" Control::Entry::plot "<<endl;
    ctrl->plot(S,offset,Gphi,npredict,ntout,nsstep,riter,*ext,control_type);
  } else {
    // cout <<__FILE__<<":"<<__LINE__<<" Control::Entry::plot "<<endl;
    ctrl->plot(S,offset,Gphi,npredict,ntout,nsstep,riter);
  }
}

/// Plot the control entry
void Control::Entry::set_parameter(const std::string &key,
                                   const std::string &val) {
  ctrl->set_parameter(key,val);
}

//============================================================================
//                          Control::Entry I/O
//============================================================================

streamoff Control::Entry::read(const string &fname, const streamoff skip,
                               dVector &Gphi ) {
  if (verb) comm->cout() << "Control::Entry::read for " << name << endl;
#ifdef DGM_PARALLEL
  if ( !ctrl->replicated() ) {
    return mpi_read(fname,skip,Gphi);
  } else {
    // If this Ctrl is replicated, just have the master read it and bcast
    streamoff result(0);
    if (comm->Master()) result = serial_read(fname,skip,Gphi);
    comm->Broadcast(&result);
    return result;
  }
#else
  return serial_read(fname,skip,Gphi);
#endif
}

streamoff Control::Entry::write(const string &fname, const streamoff skip,
                                const dVector &Gphi ) {
  if (verb) comm->cout() << "Control::Entry::write for " << name << endl;
#ifdef DGM_PARALLEL
  if ( !ctrl->replicated() ) {
    return mpi_write(fname,skip,Gphi);
  } else {
    // If this Ctrl is replicated, just have the owner write it
    streamoff result(0);
    if (comm->Master()) result = serial_write(fname,skip,Gphi);
    comm->Broadcast(&result);
    return result;
  }
#else
  return serial_write(fname,skip,Gphi);
#endif
}

#ifdef DGM_PARALLEL

/// MPI-IO for reading Entries from a file
streamoff Control::Entry::mpi_read(const string &fname, const streamoff skip,
                                   dVector &Gphi ) {
  // split the communicator into only the active ranks
  MPI_Comm mpiComm = dynamic_cast<DGM::MpiComm *>(comm.get())->mpicomm();
  MPI_Comm ioComm = MPI_COMM_NULL;
  const int membershipKey = length ? 1 : MPI_UNDEFINED;
  if (MPI_Comm_split(mpiComm,membershipKey,0,&ioComm))
    throw DGM::exception("Error splitting MPI_Comm");

  // absolute offset in bytes from the beginning
  MPI_Offset disp = numeric_cast<MPI_Offset>(skip);

  if (membershipKey==1) {
    MPI_File fh;
    MPI_Status status;
    MPI_Datatype filetype;
    Ordinal cne = clen.size();

    dVector view;
    view.alias(Gphi, offset, length);

    DGM::MpiComm::Ptr mycomm( new MpiComm(ioComm,"Control::ioComm") );
    if (MPI_File_open(ioComm, const_cast<char *>(fname.c_str()),
                      MPI_MODE_RDWR | MPI_MODE_CREATE, MPI_INFO_NULL, &fh)) {
      throw exception(string("MPI_File_open failed to open file " + fname));
    }

#ifdef DGM_DEBUG_CONTROL_IO
    if (mycomm->MyPID()<2)
      cout<<mycomm->MyPID()<<": cne="<<cne<<", disp="<<disp<<", offset="<<offset
      <<", length="<<length<<endl;

    mycomm->Barrier();
    mycomm->cout()<<"Local mapping data"<<endl;
    if(mycomm->Master()) {
      for(int e=0; e<cdisp.size(); ++e) {
        cout << mycomm->MyPID() << ": " << cdisp[e] << "  "
            << clen[e] << endl;
      }
    }
    mycomm->Barrier();
    if(mycomm->MyPID()==1) {
      for(int e=0; e<cdisp.size(); ++e) {
        cout << mycomm->MyPID() << ": " << cdisp[e] << "  "
            << clen[e] << endl;
      }
    }
    mycomm->Barrier();
#endif

    // MPI requires these to be int
    intVector ilen(cne), idisp(cne);
    for (Ordinal i=0; i<cne; ++i) {
      ilen[i] = numeric_cast<int>(clen[i]);
      idisp[i] = numeric_cast<int>(cdisp[i]);
    }

    // Build filetype for data using MPI_Type_indexed
    if (int stat = MPI_Type_indexed( cne, ilen.data(), idisp.data(),
                                     mpiType<Scalar>(), &filetype))
      error("MPI_Type_indexed", stat);

    if (int stat = MPI_Type_commit( &filetype ))
      error("MPI_type_commit", stat);

    // read data (use collective IO for efficiency)
    const char *native = "native";
    if (int stat = MPI_File_set_view(fh, disp, mpiType<Scalar>(), filetype,
                                     const_cast<char*>(native), MPI_INFO_NULL))
      error("MPI_File_set_view", stat);

    if (int stat = MPI_File_read_all(fh, view.data(), length,
                                     mpiType<Scalar>(), &status))
      error("MPI_File_read_all", stat);
    disp += cglen*sizeof(Scalar);

    if (int stat = MPI_Type_free( &filetype ))
      error("MPI_Type_free", stat);

    if (int stat = MPI_File_close(&fh))
      error("MPI_File_close", stat);
#ifdef DGM_DEBUG_CONTROL_IO
    cout << mycomm->MyPID()<<": Entry " << name << " skip = " << skip
        << " disp = " << disp << endl;
#endif
  }
  if (ioComm != MPI_COMM_NULL && 
      ioComm != MPI_COMM_WORLD && 
      ioComm != MPI_COMM_SELF) MPI_Comm_free(&ioComm);
  comm->Barrier();
  streamoff result = numeric_cast<streamoff>(disp);
  comm->MaxAll(result);
  return result;
}

/// MPI-IO for writing Entries to a file
streamoff Control::Entry::mpi_write(const string &fname, const streamoff skip,
                                    const dVector &Gphi) {
  // split the communicator into only the active ranks
  MPI_Comm mpiComm = dynamic_cast<DGM::MpiComm *>(comm.get())->mpicomm();
  MPI_Comm ioComm = MPI_COMM_NULL;
  const int membershipKey = length ? 1 : MPI_UNDEFINED;
  if (MPI_Comm_split(mpiComm,membershipKey,0,&ioComm))
    throw DGM::exception("Error splitting MPI_Comm");

  // absolute offset in bytes from the beginning
  MPI_Offset disp = numeric_cast<MPI_Offset>(skip);

  if (membershipKey==1) {
    MPI_File fh;
    MPI_Status status;
    MPI_Datatype filetype;
    const char *native="native";
    Ordinal cne = clen.size();

    DGM::MpiComm::Ptr mycomm( new MpiComm(ioComm,"Control::ioComm") );

    dVector view;
    view.alias( *(const_cast<dVector*>(&Gphi)), offset, length);

#ifdef DGM_HACK_CONTROL_WRITE
    // hack for debugging
    mycomm->cout()<<"Hack in Control::Entry::write()"<<endl;
    dVector tmp(length);
    for (int i=0; i<length; ++i) tmp[i] = i;
#endif

#ifdef DGM_DEBUG_CONTROL_IO
            cout<<mycomm->MyPID()<<": cne="<<cne<<", disp="<<disp<<", "
                "offset="<<offset <<", length="<<length<<endl;
    mycomm->Barrier();
    mycomm->cout()<<"Local mapping data"<<endl;
    if(mycomm->Master()) {
      cout << mycomm->MyPID() << ": cdisp.size() = " << cdisp.size() << endl;
      for(int e=0; e<cdisp.size(); ++e) {
        cout << mycomm->MyPID() << ": " << cdisp[e] << "  "
            << clen[e] << endl;
      }
    }
    mycomm->Barrier();
    if(mycomm->MyPID()==1) {
      cout << mycomm->MyPID() << ": cdisp.size() = " << cdisp.size() << endl;
      for(int e=0; e<cdisp.size(); ++e) {
        cout << mycomm->MyPID() << ": " << cdisp[e] << "  "
            << clen[e] << endl;
      }
    }
    mycomm->Barrier();
    // throw DGM::exception("debug termination");
#endif
    // Build datatype using MPI_Type_indexed
    intVector ilen(cne), idisp(cne);
    for (Ordinal i=0; i<cne; ++i) {
      ilen[i] = numeric_cast<int>(clen[i]);
      idisp[i] = numeric_cast<int>(cdisp[i]);
    }
    if (int stat = MPI_Type_indexed( cne, ilen.data(), idisp.data(),
                                     mpiType<Scalar>(), &filetype) )
      error("MPI_Type_indexed ", stat);
    if (int stat = MPI_Type_commit( &filetype ) )
      error("MPI_Type_commit ", stat);

    if (int stat=MPI_File_open(ioComm,const_cast<char*>(fname.c_str()),
                               MPI_MODE_WRONLY | MPI_MODE_CREATE,
                               MPI_INFO_NULL, &fh) )
      error("MPI_File_open", stat);

    if (int stat = MPI_File_set_view(fh, disp, mpiType<Scalar>(), filetype,
                                     const_cast<char*>(native), MPI_INFO_NULL) )
      error("MPI_File_set_view", stat);

#ifdef DGM_HACK_CONTROL_WRITE
    if (int stat = MPI_File_write_all(fh, tmp.data(), length,
                                      mpiType<Scalar>(), &status))
      error("MPI_File_write",stat);
#else
    if (int stat = MPI_File_write_all(fh, view.data(), length,
                                      mpiType<Scalar>(), &status))
      error("MPI_File_write",stat);
#endif
    disp += cglen*sizeof(Scalar);

    if (int stat=MPI_File_close(&fh)) error("MPI_File_close ",stat);
    if (int stat=MPI_Type_free(&filetype)) error("MPI_Type_free ",stat);
#ifdef DGM_DEBUG_CONTROL_IO
    cout << mycomm->MyPID()<<": Entry " << name << " skip = " << skip
         << " disp = " << disp << endl;
#endif
  }
  if (ioComm != MPI_COMM_NULL &&
      ioComm != MPI_COMM_WORLD && 
      ioComm != MPI_COMM_SELF) MPI_Comm_free(&ioComm);
  comm->Barrier();
  streamoff result = numeric_cast<streamoff>(disp);
  comm->MaxAll(result);
#if DGM_DEBUG_CONTROL_IO>1
  cout << "Entry " << name << ", skip = " << skip
       << ", disp = " << disp << ", cglen = " << cglen
       << ", length = " << length
       << ", disp - skip = " << disp - skip
       << ", cglen*sizeof(Scalar) = " << cglen*sizeof(Scalar) << endl;

  // debugging stuff
  if (comm->Master()) {
    ifstream in(fname.c_str());
    in.seekg(0,in.end);
    streamoff disp = in.tellg();
    cout << "The file is of length " << disp <<endl;
  }
#endif
  return result;
}

#endif  // DGM_PARALLEL

/// Serial method for reading entries from a file
streamoff Control::Entry::serial_read(const string &fname, const streamoff skip,
                                      dVector &Gphi) {
  streamoff disp=skip;  // ending disp is at least equal to skip
  dVector view;         // get a local view of this Entries control data
#if 0
  for (int i=0; i<ntime; i++) {
    view.alias(Gphi, offset+i*ctrl_size(), ctrl_size());
    disp = ctrl->read(fname, disp, view);
  }
#else  // read it all in one big chunk
  view.alias(Gphi, offset, length);  // length = ntime*ctrl_size
  ifstream res_in(fname.c_str());
  res_in.seekg(skip); // position file pointer at offset
  res_in.read(reinterpret_cast<char*>(view.data()),
              sizeof(Scalar)*length);
  disp = res_in.tellg();
  res_in.close();
#endif
  // cout << "Entry " << name << " skip = " << skip << " disp = " <<disp<<endl;
  return disp;
}

/// Serial method for writing entries to a file
streamoff Control::Entry::serial_write(const string &fname,
                                       const streamoff skip,
                                       const dVector &Gphi) {
  streamoff disp=skip;  // ending disp is at least equal to skip
  dVector view;         // get a local view of this Entries control data
#if 0
  for (int i=0; i<ntime; i++) {
    view.alias( *(const_cast<dVector*>(&Gphi)),
                offset+i*ctrl_size(), ctrl_size() );
    disp = ctrl->write(fname, disp, view);
  }
#else  // write it all in one big chunk
  view.alias( *(const_cast<dVector*>(&Gphi)), offset, length);
#if 0
  static int ind(0);
  comm->cout() << "Entry::write skip = " << skip << endl;
  comm->cout() << "Entry::write offset = " << offset << endl;
  comm->cout() << "Entry::write length = " << length << endl;
  comm->cout() << "Entry::view.Norm()= " << view.Norm() << endl;
  if (comm->Master()) {
    stringstream ss;
    ss << "ctl." << ind++ << ".dat";
    ofstream tmp(ss.str().c_str());
    for (int i=0; i<length; i++) tmp << i << " " << view[i] << endl;
  }
#endif
  ofstream res_out(fname.c_str(), ios::in|ios::out);
  if (!res_out.good())
    throw DGM::exception("Could not open file "+fname+" at offset "+
                         asString(skip)+" for Control::Entry "+name);
  res_out.seekp(skip); // position file pointer at offset
  if (!res_out.good())
    throw DGM::exception("Could not seek in file "+fname+" at offset "+
                         asString(skip)+" for Control::Entry "+name);
  res_out.write(reinterpret_cast<const char*>(view.data()),
                sizeof(Scalar)*length);
  if (!res_out.good())
    throw DGM::exception("Could not write to file "+fname+" at offset "+
                         asString(skip)+" for Control::Entry "+name);
  disp = res_out.tellp();
  res_out.close();
#endif
#if 0
  cout << "Entry " << name << ", skip = " << skip
       << ", disp = " << disp << ", disp - skip = " << disp-skip
       << ", cglen = " << cglen
       << ", length = " << length << endl;
#endif
  return disp;
}

} // namespace DGM
