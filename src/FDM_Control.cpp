/** \file FDM_Control.cpp
    \brief FDM::Control interface
    \author Scott Collis
    \author Bill Spotz
*/

// DTK includes
//#include "DTK_Function.hpp"

// FDM includes
#include "FDM_Control.hpp"
#include "FDM_Domain.hpp"
#include "FDM_State.hpp"
#include "FDM_Source.hpp"

// #define FDM_CODETRACE

namespace FDM
{

/// Simple function class used by DTK::TimeIntegrate
class Function : public DTK::ScalarFunction<FDM::Scalar,FDM::Ordinal>
{
public:
  /// Constructor
  Function(const Scalar t_,
           const Scalar dt_) :
    DTK::ScalarFunction<FDM::Scalar,FDM::Ordinal>(t_,dt_)
  {
  }

  /// Destructor
  virtual ~Function()
  {
  };

  /// Evaluation interface
  virtual FDM::Scalar evaluate(const Ordinal,
                               const Ordinal) = 0;
};

// Setup the control database
void Control::setup()
{
#ifdef FDM_CODETRACE
  cout << "FDM::Control::setup" << endl;
#endif

  Ordinal phi_size = 0;
  Domain *omega(state->domain());
  for (Source::db_citr i=omega->Source_db.begin();
       i!= omega->Source_db.end(); ++i)
  {
    if (i->second->ctrl()) {
      Ctrl *ctrl(i->second->ctrl());
      ctrl->initialize();
      omega->out() << "Setting up Control::Entry for " << i->second->type
                   << endl;
      Size cglen(0);
      IntVector cdisp, clen;
      if (!ctrl->get_parallel_info(cglen,cdisp,clen))
        omega->out() << "WARNING: " << i->first << " has no parallel info "
                     << "implemented" << endl;
//  \warning SSC commented this out on 10/3/2015 but beware...!!!
//      if (!ctrl->get_parallel_info(cglen,cdisp,clen))
//      {
//        // Size size=0;
//#ifdef DGM_PARALLEL
//        // WARNING: this only works if the source has a field that is
//        // distributed over the domain so generate an error if otherwise
//        if (ctrl->F.size()==0)
//        {
//          vout << "Error: Ctrl " << i->first
//               << " has no VectorField therefore parallel I/O will "
//               << "currently fail.  \nYou should implement the "
//               << "get_parallel_info method for this object." << endl;
//          exit(1);
//        }
//#endif
//      }
      Entry::Ptr entry(new Entry(this, i->first, phi_size, npp, ctrl));
      phi_db.push_back(entry);
      phi_size += phi_db.back()->length();
#ifdef FDM_CONTROL_DETAILS
      vout << "  Found source control: " << i->first
           << ", ctrl_size = " << phi_db.back()->ctrl_size()
           << ", offset = " << phi_db.back()->offset()
           << ", length = " << phi_db.back()->length()
           << endl;
#endif
    }
  }
  if (verb) comm->cout() << "  phi_size = " << phi_size << endl;
  phi.resize( phi_size );
  zero();

  FDM::Ordinal glen = 0;
  comm->SumAll( &phi_size, &glen, 1 );
  comm->cout() << "  Total number of controls = " << phi_db.size() << endl;
  comm->cout() << "  Total length of control vector = " << glen << endl;

  vout << "Control::setup() completed" << endl;
}


// Constructor
/** \todo Need to get parameters setup. */
Control::Control(FDM::State *_state,
                 Json::Value &root) :
  state(_state),
  dt(root["Domain"]["dt"].asDouble()),
  npredict(root["Optimizer"]["npredict"].asInt()),
  nsstep(state->domain()->timeIntegrator()->numsubstep()),
  npp(nsstep*npredict+1),
  gnum(0),
  glen(0),
  verb(1),
  vout(std::cout),
  comm(state->domain()->get_comm())
{

#ifdef FDM_CODETRACE
  cout << "FDM::Control constructor" << endl;
#endif

}

// Constructor
Control::Control(const Control *in) :
  state(in->state),
  dt(in->dt),
  npredict(in->npredict),
  nsstep(in->nsstep),
  npp(in->npp),
  gnum(in->gnum),
  glen(in->glen),
  verb(in->verb),
  vout(in->vout),
  comm(in->comm),
  phi_db(in->phi_db)
{
#ifdef FDM_CODETRACE
  cout << "FDM::Control::constructor" << endl;
#endif

  phi.resize(in->phi.size());
  phi = in->phi;
  global_len.resize(in->global_len.size());
  global_len = in->global_len;
  global_disp.resize(in->global_disp.size());
  global_disp = in->global_disp;
}

// Destructor
Control::~Control()
{
#ifdef FDM_CODETRACE
  cout << "FDM::Control destructor" << endl;
#endif
}

size_t Control::num_ctrl() const
{
#ifdef FDM_CODETRACE
  cout << "FDM::Control::num_ctrl" << endl;
#endif

  return phi_db.size();
}

void Control::reset_costs()
{
#ifdef FDM_CODETRACE
  cout << "FDM::Control::reset_costs" << endl;
#endif

  costs.resize(numeric_cast<Ordinal>(phi_db.size()));
  costs = 0;
}

// Output the cost of each Entry to a supplied output stream
void Control::output_costs(std::ostream &os) const
{
#ifdef FDM_CODETRACE
  cout << "FDM::Control::output_costs" << endl;
#endif

  Ordinal n=0;
  typedef list<Entry::Ptr>::const_iterator LI;
  for (LI c = phi_db.begin(); c != phi_db.end(); ++c)
  {
    os<<"J["<<(*c)->name()<<"] = "<<costs[n++]<<std::endl;
  }
}

// Returns the local length of phi for this Control
size_t Control::size() const
{
#ifdef FDM_CODETRACE
  cout << "FDM::Control::size" << endl;
#endif

  return phi.size();
}

// Resizes the local length of phi for this Control
void Control::resize(Ordinal n)
{
#ifdef FDM_CODETRACE
  cout << "FDM::Control::resize" << endl;
#endif

  phi.resize(n);
}

// Returns the global length of phi for this Control
Ordinal Control::global_size() const
{
#ifdef FDM_CODETRACE
  cout << "FDM::Control::global_size" << endl;
#endif

  return glen;
}

// Plot the control
void Control::plot(const Ordinal ntout,
                   const Ordinal iter,
                   const std::string *ext) const
{
#ifdef FDM_CODETRACE
  cout << "FDM::Control::plot" << endl;
#endif

  typedef list<Entry::Ptr>::const_iterator LI;
  for (LI c = phi_db.begin(); c != phi_db.end(); ++c)
    (*c)->plot(state->domain()->getU(),phi,npredict,ntout,nsstep,iter,ext);
}

// Number of substeps (assumed fixed) for this Control object
Ordinal Control::get_nsstep() const
{
#ifdef FDM_CODETRACE
  cout << "FDM::Control::get_nsstep" << endl;
#endif

  return nsstep;
}

// Number of timesteps (assumed fixed) to predict the solution
Ordinal Control::get_npredict() const
{
#ifdef FDM_CODETRACE
  cout << "FDM::Control::get_npredict" << endl;
#endif

  return npredict;
}

// Return the timestep (assumed fixed) for this Control object
Scalar Control::get_dt() const
{
#ifdef FDM_CODETRACE
  cout << "FDM::Control::get_dt" << endl;
#endif

  return dt;
}

// Fill the initial phi vector from the Ctrl entries
/** \todo Need to generalize so that it works with all time integrators. */
void Control::initialize()
{
#ifdef FDM_CODETRACE
  cout << "FDM::Control::initialize" << endl;
#endif

  //if (verb) vout << "Control::initialize()" << endl;
  typedef list<Entry::Ptr>::iterator LI;
  for (LI c = phi_db.begin(); c != phi_db.end(); ++c)
  {
    if ((*c)->has_fill())
    {
      /// \warning Hardwired for RK4!
      assert(nsstep==4);
      Scalar a[4] = {0.0, 0.5, 0.5, 1.0};
      for (Ordinal i=0; i<npredict; i++)
      {
        for (Ordinal s=0; s<nsstep; s++)
        {
          Ordinal n = s + i*nsstep;
          Scalar time = i*dt + a[s]*dt;
          (*c)->fill(n,time,phi);
        }
      }
    }
    else
    {
      for (Ordinal n=0; n<(*c)->ntime(); ++n) (*c)->get_data( n, phi );
    }
  }
  //if (verb) vout << "Control::initialize() complete" << endl;
}

// Set the Control storage to zero
void Control::zero()
{
#ifdef FDM_CODETRACE
  cout << "FDM::Control::zero" << endl;
#endif

  phi = 0.0;
}

// Output the control at a given iteration (not currently implemented)
/** \todo Implement the Control::output method */
void Control::output(Ordinal iter_)
{
#ifdef FDM_CODETRACE
  cout << "FDM::Control::output" << endl;
#endif

  vout << "Control::output(int) is not implemented" << endl;
}

// Set the data on this Control
void Control::set_data(const Ordinal istep, const Ordinal sstep)
{
#ifdef FDM_CODETRACE
  cout << "FDM::Control::set_data" << endl;
#endif

  typedef list<Entry::Ptr>::iterator LI;
  for (LI i = phi_db.begin(); i != phi_db.end(); ++i)
  {
    (*i)->set_data( istep*nsstep+sstep, phi );
  }
}

// Load the Control by iterating over all entries
void Control::load(ScalarVector & dcontrol,
                   const Ordinal istep,
                   const Ordinal sstep) const
{
#ifdef FDM_CODETRACE
  cout << "FDM::Control::load" << endl;
#endif

  typedef list<Entry::Ptr>::const_iterator LI;
  ScalarVector tmp;
  Ordinal offset=0;
  for (LI i = phi_db.begin(); i != phi_db.end(); ++i)
  {
    tmp.alias( dcontrol, offset, (*i)->ctrl_size() );
    (*i)->load( istep*nsstep+sstep, phi, tmp );
    offset += (*i)->ctrl_size();
  }
}

// Store the Control by iterating over all entries
void Control::store(ScalarVector & dcontrol,
                    const Ordinal istep,
                    const Ordinal sstep)
{
#ifdef FDM_CODETRACE
  cout << "FDM::Control::store" << endl;
#endif

  typedef list<Entry::Ptr>::iterator LI;
  ScalarVector tmp;
  Ordinal offset=0;
  for (LI i = phi_db.begin(); i != phi_db.end(); ++i)
  {
    tmp.alias( dcontrol, offset, (*i)->ctrl_size() );
    (*i)->store( tmp, istep*nsstep+sstep, phi );
    offset += (*i)->ctrl_size();
  }
}

// Set the Control to a prescribed direction by iterating over entries
/** This is used to call each Entries::set_direction() method.  NOTE that the
    result is normalized by the norm of the resulting Control vector.  This
    method is useful for setting an arbitrary direction for finite difference
    gradient checks. */
void Control::set_direction()
{
#ifdef FDM_CODETRACE
  cout << "FDM::Control::set_direction" << endl;
#endif

  typedef list<Entry::Ptr>::iterator LI;
  for (LI c = phi_db.begin(); c != phi_db.end(); ++c)
    for(Ordinal i=0; i<(*c)->ntime(); ++i) (*c)->set_direction( i, phi );
  Scalar phi_norm = norm();
  if (phi_norm != 0.0) scale( 1.0/phi_norm, phi );
}

Scalar Control::cost() const
{
#ifdef FDM_CODETRACE
  cout << "FDM::Control::cost()" << endl;
#endif

  FDM_UNDEFINED;
  return 0;
}

// Control cost for one time-slab for all entries
Scalar Control::cost(const Ordinal istep, const Ordinal sstep) const
{
#ifdef FDM_CODETRACE
  cout << "FDM::Control::cost(2 args)" << endl;
#endif

  if (istep*nsstep+sstep == npp) return 0.0;
  //if (verb) vout << "Control::cost" << endl;
  Scalar result = 0;
  Ordinal n = 0;
  typedef list<Entry::Ptr>::const_iterator LI;
  for (LI c = phi_db.begin(); c != phi_db.end(); ++c)
  {
    // cout << "Computing cost for control " << (*c)->name << endl;
    costs[n] = (*c)->cost( istep*nsstep+sstep, phi );
    result += costs[n];
    n++;
  }
  return result;
}

// Bound the entire Control over all time
void Control::bound()
{
#ifdef FDM_CODETRACE
  cout << "FDM::Control::bound()" << endl;
#endif

  for(Ordinal i=0; i<npredict; ++i)
    for(Ordinal j=0; j<nsstep; ++j)
      bound(i,j);
}

// Bound the Control on one timestep
void Control::bound(const Ordinal istep, const Ordinal sstep)
{
#ifdef FDM_CODETRACE
  cout << "FDM::Control::bound(2 args)" << endl;
#endif

  typedef list<Entry::Ptr>::const_iterator LI;
  for (LI c = phi_db.begin(); c != phi_db.end(); ++c)
  {
    (*c)->bound( istep*nsstep+sstep, phi );
  }
}

// Determine realizability of the entire Control over all time
bool Control::realizable()
{
#ifdef FDM_CODETRACE
  cout << "FDM::Control::realizable()" << endl;
#endif

  bool result = true;
  for(Ordinal i=0; i<npredict; ++i)
    for(Ordinal j=0; j<nsstep; ++j)
      result = result && realizable(i,j);
  return result;
}

// Determine realizability of the Control on one timestep
bool Control::realizable(const Ordinal istep, const Ordinal sstep)
{
#ifdef FDM_CODETRACE
  cout << "FDM::Control::realizable(2 args)" << endl;
#endif

  bool result = true;
  typedef list<Entry::Ptr>::const_iterator LI;
  for (LI c = phi_db.begin(); c != phi_db.end(); ++c)
  {
    result = result && (*c)->realizable( istep*nsstep+sstep, phi );
  }
  return result;
}

/// Defines a DGM::Function class that is compatible with DGM::TimeInt
/** Integrates \f$ \bX \cdot \bY \f$. */
class ControlFunction : public FDM::Function
{
  Control::Entry::Ptr C;   ///< Control entry object
  const Control &X;        ///< Control object \f$\bX\f$
  const Control &Y;        ///< Control object \f$\bY\f$
  const Ordinal nsstep;    ///< Number of substeps
public:
  /// Constructor
  ControlFunction(Control::Entry::Ptr c,
                  const Control &x,
                  const Control &y ) :
    FDM::Function(0.0, x.get_dt()),
    C(c),
    X(x),
    Y(y),
    nsstep(X.get_nsstep())
  {
#ifdef FDM_CODETRACE
  cout << "FDM::ControlFunction constructor" << endl;
#endif

  }
  /// Provide the Function interface for the inner product of two Controls
  Scalar evaluate( const Ordinal istep,
                   const Ordinal sstep )
  {
#ifdef FDM_CODETRACE
  cout << "FDM::ControlFunction::evaluate" << endl;
#endif

    C->time(t);  // register the current time with the Control::Entry
    return C->inner_product(istep*nsstep+sstep,X.phi,Y.phi);
  }
};

// Inner product
Scalar Control::inner_product(const Control *Y) const
{
#ifdef FDM_CODETRACE
  cout << "FDM::Control::inner_product(ptr)" << endl;
#endif

  return inner_product(*Y);
}

// Inner product (in space and time as appropriate) for this Control and Y
Scalar Control::inner_product(const Control &Y) const
{
#ifdef FDM_CODETRACE
  cout << "FDM::Control::inner_product(ref)" << endl;
#endif

  Scalar result = 0;
  typedef list<Entry::Ptr>::const_iterator LI;
  for (LI c = phi_db.begin(); c != phi_db.end(); ++c)
  {
    if ((*c)->get_ctrl()->steady())
    {
      result += (*c)->inner_product(0, phi, Y.phi );
    }
    else
    {
      ControlFunction f( *c, *this, Y );
      for(f.lstep=1; f.lstep<=npredict; ++f.lstep)
        state->domain()->timeIntegrator()->integrate( &f );
      result += f.value;
    }
  }
  Scalar lresult = result;
  comm->SumAll( &lresult, &result, 1 );
  return result;
}

// Compute the norm of this control based on the Control's inner_product
Scalar Control::norm() const
{
#ifdef FDM_CODETRACE
  cout << "FDM::Control::norm" << endl;
#endif

  return sqrt(inner_product(this));
}

// Compute a contribution to the gradient (preferred interface)
void Control::gradient(const VectorField & S,
                       const VectorField & A,
                       Control & G,
                       const Ordinal istep,
                       const Ordinal sstep)
{
#ifdef FDM_CODETRACE
  cout << "FDM::Control::gradient" << endl;
#endif

  typedef list<Entry::Ptr>::const_iterator LI;
  for (LI c = phi_db.begin(); c != phi_db.end(); ++c) {
    (*c)->gradient( istep, sstep, phi, S, A, G.phi );
  }
}

// Computes a contribution to a preconditioner
void Control::computePreconditioner(const VectorField & S,
                                    const VectorField & A,
                                    Control & G,
                                    const Ordinal istep,
                                    const Ordinal sstep)
{
#ifdef FDM_CODETRACE
  cout << "FDM::Control::computePreconditioner" << endl;
#endif

  typedef list<Entry::Ptr>::const_iterator LI;
  for (LI c = phi_db.begin(); c != phi_db.end(); ++c)
  {
    (*c)->computePreconditioner(istep, sstep, phi, S, A, G.phi);
  }
}

// Applies a preconditioner
void Control::applyPreconditioner(const Control & G,
                                  Control & P)
{
#ifdef FDM_CODETRACE
  cout << "FDM::Control::applyPreconditioner" << endl;
#endif

  typedef list<Entry::Ptr>::const_iterator LI;
  for (LI c = phi_db.begin(); c != phi_db.end(); ++c)
  {
    (*c)->applyPreconditioner(phi, G.phi, P.phi);
  }
}

// Compute Hessian vector product for the observation term
void Control::HessVecProd_obs(const VectorField & S,
                              const VectorField & A,
                              const Control & x,
                              const Control & dx,
                              Control & H_dx,
                              const Ordinal istep,
                              const Ordinal sstep)
{
#ifdef FDM_CODETRACE
  cout << "FDM::Control::HessVecProd_obs" << endl;
#endif

  FDM_UNDEFINED;
}

// Compute Hessian vector product for the regularization term
void Control::HessVecProd_reg(const Control & x,
                              const Control & dx,
                              Control & H_dx,
                              const Ordinal istep,
                              const Ordinal sstep)
{
#ifdef FDM_CODETRACE
  cout << "FDM::Control::HessVecProd_reg" << endl;
#endif

  FDM_UNDEFINED;
}

// Read the control from a file:  needed for control restart
std::streamoff Control::read(const std::string &,
                             const std::streamoff)
{
#ifdef FDM_CODETRACE
  cout << "FDM::Control::read" << endl;
#endif

  FDM_UNDEFINED;
  return 0;
}

// Write the control to a file:  needed for control restart
std::streamoff Control::write(const std::string &,
                              const std::streamoff)
{
#ifdef FDM_CODETRACE
  cout << "FDM::Control::write" << endl;
#endif

  FDM_UNDEFINED;
  return 0;
}

/** Loops over the Ctrl Entries and determine if all are steady */
bool Control::steady() const
{
#ifdef FDM_CODETRACE
  cout << "FDM::Control::steady" << endl;
#endif

  typedef list<Entry::Ptr>::const_iterator LI;
  for (LI c = phi_db.begin(); c != phi_db.end(); ++c)
    if(!(*c)->get_ctrl()->steady())
      return false;
  return true;
}

// Gather control vector from across a parallel machine
void Control::gather(ScalarVector &) const
{
#ifdef FDM_CODETRACE
  cout << "FDM::Control::gather" << endl;
#endif

  FDM_UNDEFINED;
}

// Scatter control vector across parallel machine
void Control::scatter(ScalarVector &)
{
#ifdef FDM_CODETRACE
  cout << "FDM::Control::scatter" << endl;
#endif

  FDM_UNDEFINED;
}

// Accessor for the global (across a parallel processor) control length
Ordinal Control::get_glen() const
{
#ifdef FDM_CODETRACE
  cout << "FDM::Control::get_glen" << endl;
#endif

  FDM_UNDEFINED;
  return 0;
}

// Accessor that gives access to the State pointer
State* Control::get_state()
{
#ifdef FDM_CODETRACE
  cout << "FDM::Control::get_state" << endl;
#endif

  return state;
}

// Accessor for Control vector
const ScalarVector & Control::get_phi() const
{
#ifdef FDM_CODETRACE
  cout << "FDM::Control::get_phi" << endl;
#endif

  return phi;
}

///////////////////////////////////
// Control::Entry Implementation //
///////////////////////////////////

// Control::Entry Constructor
Control::Entry::Entry(Control *C,
                      const string n,
                      const Ordinal off,
                      const Ordinal nt,
                      Ctrl *c) :
  control(C),
  name_(n),
  offset_(off),
  length_(0),
  ntime_(nt),
  ctrl(c),
  verb(1),
  vout(std::cout),
  comm(C->comm)
{
#ifdef FDM_CODETRACE
  cout << "FDM::Control::Entry constructor" << endl;
#endif

  if (ctrl->steady())
  {
    ntime(1);
    Grad_data.resize(control->get_nsstep()*ctrl_size());
    Prec_data.resize(control->get_nsstep()*ctrl_size());
    Grad_data = 0.0;
    Prec_data = 0.0;
  }
  // A replicated control only reports a length on the Master
  if ( ctrl->owner() )
    length(ntime()*ctrl_size());
  else
    length(0);
}

// Destructor
Control::Entry::~Entry()
{
#ifdef FDM_CODETRACE
  cout << "FDM::Control::Entry destructor" << endl;
#endif

}

// Accessor for name
void Control::Entry::name(const std::string name)
{
#ifdef FDM_CODETRACE
  cout << "FDM::Control::Entry::name(string)" << endl;
#endif

  name_ = name;
}

// Accessor for name
std::string Control::Entry::name() const
{
  return name_;
}

// Accessor for ntime
Ordinal Control::Entry::ntime() const
{
#ifdef FDM_CODETRACE
  cout << "FDM::Control::Entry::ntime() for " << name() << endl;
#endif

  return ntime_;
}

// Set for ntime
void Control::Entry::ntime(const Ordinal ntime)
{
#ifdef FDM_CODETRACE
  cout << "FDM::Control::Entry::ntime(Ordinal) for " << name() << endl;
#endif

  ntime_=ntime;
}

// Accessor for length
Size Control::Entry::length() const
{
#ifdef FDM_CODETRACE
  cout << "FDM::Control::Entry::length() for " << name() << endl;
#endif

  return length_;
}

// Setter for length
void Control::Entry::length(const Size length)
{
#ifdef FDM_CODETRACE
  cout << "FDM::Control::Entry::length(Size) for " << name() << endl;
#endif

  length_ = length;
}

// Set for offset
void Control::Entry::offset(const Size offset)
{
#ifdef FDM_CODETRACE
  cout << "FDM::Control::Entry::offset(Size) for " << name() << endl;
#endif

  offset_ = offset;
}

// Accessor for offset
Size Control::Entry::offset() const
{
#ifdef FDM_CODETRACE
  cout << "FDM::Control::Entry::offset() for " << name() << endl;
#endif

  return offset_;
}

// Length of each slab
Size Control::Entry::ctrl_size() const
{
#ifdef FDM_CODETRACE
  cout << "FDM::Control::Entry::ctrl_size for " << name() << endl;
#endif

  return ctrl->data_size();
}

// Get a pointer to Ctrl for this Entry
Ctrl* Control::Entry::get_ctrl()
{
#ifdef FDM_CODETRACE
  cout << "FDM::Control::Entry::get_ctrl for " << name() << endl;
#endif

  return ctrl;
}

// Get a constant pointer to Ctrl for this Entry
const Ctrl* Control::Entry::get_ctrl() const
{
#ifdef FDM_CODETRACE
  cout << "FDM::Control::Entry::get_ctrl for " << name() << endl;
#endif

  return ctrl;
}

// Puts the data in global_phi into the ctrl's
void Control::Entry::set_data(const Ordinal index,
                              const ScalarVector & global_phi)
{
#ifdef FDM_CODETRACE
  cout << "FDM::Control::Entry::set_data for " << name() << endl;
#endif

  if (ctrl->steady() && index>0) return;
  const Ordinal i = (ctrl->steady()) ? 0 : index;
  assert( i < ntime() );
  ScalarVector view;
  if (ctrl->owner())
    view.alias( *(const_cast<ScalarVector*>(&global_phi)),
                offset()+i*ctrl_size(), ctrl_size() );
  ctrl->set_data( view );
}

// Gets the data from Ctrl objects and puts in global_phi
void Control::Entry::get_data(const Ordinal index,
                              ScalarVector & global_phi)
{
#ifdef FDM_CODETRACE
  cout << "FDM::Control::Entry::get_data for " << name() << endl;
#endif

  const Ordinal i = (ctrl->steady()) ? 0 : index;
  assert( i < ntime() );
  if ( !ctrl->owner() ) return;
  ScalarVector view;
  view.alias( global_phi, offset()+i*ctrl_size(), ctrl_size() );
  ctrl->get_data( view );
}

// query whether the fill method is overloaded
bool Control::Entry::has_fill() const
{
#ifdef FDM_CODETRACE
  cout << "FDM::Control::Entry::has_fill for " << name() << endl;
#endif

  return ctrl->has_fill();
}

// Gets the data from Ctrl objects and puts in global_phi
void Control::Entry::fill(const Ordinal index,
                          const Scalar time,
                          ScalarVector & global_phi )
{
#ifdef FDM_CODETRACE
  cout << "FDM::Control::Entry::fill for " << name() << endl;
#endif

  const Ordinal i = (ctrl->steady()) ? 0 : index;
  assert( i < ntime() );
  ScalarVector view;
  if ( ctrl->owner() )
    view.alias( global_phi, offset()+i*ctrl_size(), ctrl_size() );
  ctrl->fill( time, view );
}

// Simply calls the Ctrl::output() method
void Control::Entry::output() const
{
#ifdef FDM_CODETRACE
  cout << "FDM::Control::Entry::output for " << name() << endl;
#endif

  ctrl->output();
}

// Sets the correct view into the global control and sets the direction
void Control::Entry::set_direction(const Ordinal index,
                                   ScalarVector & global_phi)
{
#ifdef FDM_CODETRACE
  cout << "FDM::Control::Entry::set_direction for " << name() << endl;
#endif

  assert( (Ordinal)index < ntime() );
  ScalarVector view;
  if ( ctrl->owner() )
    view.alias( global_phi, offset()+index*ctrl_size(), ctrl_size() );
  ctrl->set_direction( view );
}

// Load a vector with the global control data
void Control::Entry::load(const Ordinal index,
                          const ScalarVector & global_phi,
                          ScalarVector & out) const
{
#ifdef FDM_CODETRACE
  cout << "FDM::Control::Entry::load for " << name() << endl;
#endif

  const Ordinal i = (ctrl->steady()) ? 0 : index;
  assert( i < ntime() );
  if ( !ctrl->owner() ) return;
  ScalarVector view;
  view.alias( *(const_cast<ScalarVector*>(&global_phi)),
              offset()+i*ctrl_size(), ctrl_size() );
  if (out.size() != view.size()) out.resize(view.size());
  out = view;
}

// Store a vector into the global control data
void Control::Entry::store(ScalarVector & in,
                           const Ordinal index,
                           ScalarVector & global_phi )
{
#ifdef FDM_CODETRACE
  cout << "FDM::Control::Entry::store for " << name() << endl;
#endif

  const Ordinal i = (ctrl->steady()) ? 0 : index;
  assert( i < ntime() );
  assert( in.size() == ctrl_size() );
  if ( !ctrl->owner() ) return;
  ScalarVector view;
  view.alias( global_phi, offset()+i*ctrl_size(), ctrl_size() );
  view = in;
}

// Take the Ctrl inner product of two control vectors
/** Does so on a particular time slice given the index */
Scalar Control::Entry::inner_product(const Ordinal index,
                                     const ScalarVector & Xphi,
                                     const ScalarVector & Yphi)
{
#ifdef FDM_CODETRACE
  cout << "FDM::Control::Entry::inner_product for " << name() << endl;
#endif

  ScalarVector Ydata;
  set_data( index, Xphi );
  load( index, Yphi, Ydata );
  if ( !ctrl->owner() ) return 0.0;
  return ctrl->inner_product( Ydata );
}

// Compute the contribution to the total cost for this Ctrl and timeslice
Scalar Control::Entry::cost(const Ordinal index,
                            const ScalarVector & phi)
{
#ifdef FDM_CODETRACE
  cout << "FDM::Control::Entry::cost for " << name() << endl;
#endif

  set_data( index, phi );
  if ( !ctrl->owner() ) return 0.0;
  return ctrl->cost();
}

// Bound the Ctrl data for timeslice=index
void Control::Entry::bound(const Ordinal index,
                           ScalarVector & phi)
{
#ifdef FDM_CODETRACE
  cout << "FDM::Control::Entry::bound for " << name() << endl;
#endif

  if (ctrl->steady() && index>0) return;
  const Ordinal i = (ctrl->steady()) ? 0 : index;
  assert( i < ntime() );
  ScalarVector view;
  if (ctrl->owner())
    view.alias( *(const_cast<ScalarVector*>(&phi)),
                offset()+i*ctrl_size(), ctrl_size() );
  ctrl->bound( view );
  get_data( index, phi);
}

// Determine realizability for timeslice=index
bool Control::Entry::realizable(const Ordinal index,
                                ScalarVector & phi)
{
#ifdef FDM_CODETRACE
  cout << "FDM::Control::Entry::realizable for " << name() << endl;
#endif

  if (ctrl->steady() && index>0) return true;
  set_data( index, phi );
  bool result = ctrl->realizable();
  get_data( index, phi);
  return result;
}

/// Function class for gradient integration
class GradientFunction : public FDM::Function
{
  const FDM::ScalarVector &X;        ///< Integrand data
  const FDM::Ordinal nsstep;         ///< Number of substeps
  const FDM::Size size;              ///< Number of timesteps
  const FDM::Size index;             ///< Index within substep
public:
  /// Constructor
  GradientFunction(Control *control,
                   ScalarVector &x,
                   Size size_,
                   Size index_) :
    FDM::Function(0.0, control->get_dt()),
    X(x),
    nsstep(control->get_nsstep()),
    size(size_),
    index(index_)
  {
#ifdef FDM_CODETRACE
  cout << "FDM::GradientFunction constructor" << endl;
#endif

  }
  /// Provide the Function interface
  Scalar evaluate(const Ordinal istep,
                  const Ordinal sstep)
  {
#ifdef FDM_CODETRACE
  cout << "FDM::GradientFunction::evaluate" << endl;
#endif

    const Ordinal loc = numeric_cast<Ordinal>(sstep*size+index);
    return X[loc];
  }
};

void Control::Entry::gradient(const Ordinal istep,
                              const Ordinal sstep,
                              const ScalarVector & phi,
                              const VectorField & S,
                              const VectorField & A,
                              ScalarVector & Gphi)
{
#ifdef FDM_CODETRACE
  cout << "FDM::Control::Entry::gradient for " << name() << endl;
#endif

  Ordinal index = istep*control->get_nsstep()+sstep;
  ScalarVector Gdata;
  if (ctrl->steady())
  {
    set_data( index, phi );
    if ( !ctrl->owner() )
    {
      Gdata.resize(ctrl_size());
    }
    else
    {
      Gdata.alias( Grad_data, sstep*ctrl_size(), ctrl_size() );
    }
  }
  else
  {
    set_data( index, phi );
    if ( !ctrl->owner() )
      Gdata.resize(ctrl_size());
    else
      Gdata.alias( Gphi, offset_+index*ctrl_size(), ctrl_size() );
  }
  const Scalar time = control->state->domain()->time();
  ctrl->objective_function_gradient( S, A, time, Gdata );

  // WARNING this is a hacked test of integrate
  //Gdata = 1.0;
  //cout<<"Gdata[0]="<<Gdata[0]<<", Grad_data[0]="<<Grad_data[0]<<endl;

#define FDM_TEST_GRADIENT 0

#if FDM_TEST_GRADIENT > 1
  DGM::Format sci(12,20,'e');
  Scalar pnorm2 = Gdata.Norm2();
  Scalar gnorm2 = 0.0;
  DGM::Comm::World->SumAll( &pnorm2, &gnorm2, 1 );
  DGM::Comm::World->cout() << "istep = " << istep << ", sstep = " << sstep
    << ", ||Gdata|| = "<< sci(sqrt(gnorm2)) << endl;
#endif

  // Accumulate steady gradients in time

#if FDM_TEST_GRADIENT > 1
  DGM::Comm::World->cout() << "Control::Entry::gradient: steady = "
      << ctrl->steady() << " index = " << index << " size = "
      << ctrl_size() << endl;
#endif

  if ( ctrl->steady() && ctrl_size()>0 )
  {
    if ( istep == control->get_npredict() && sstep == 0 )
    {
      FDM::ScalarVector Grad_int;
      if (!ctrl->owner())
        Grad_int.resize(ctrl_size());
      else
        Grad_int.alias( Gphi, offset_, ctrl_size() );
      Grad_int = 0.0;
      // for implicit, the following is currently done twice, once for the end
      // condition, which is thrown away, and once after the first solve, which
      // is correct.  While a bit confusing and wasteful, it is still correct.
      if ( control->state->domain()->timeIntegrator()->is_implicit() )
      {
        for (Ordinal k=0; k<ctrl_size(); k++)
        {
          GradientFunction f( control, Grad_data, ctrl_size(), k );
          f.lstep = istep;
          control->state->domain()->timeIntegrator()->integrate( &f );
          Grad_int[k] += f.value;
        }
      }
#if FDM_TEST_GRADIENT > 1
      DGM::Format sci(12,20,'e');
      Scalar pnorm2 = Grad_int.Norm2();
      Scalar gnorm2 = 0.0;
      DGM::Comm::World->SumAll( &pnorm2, &gnorm2, 1 );
      DGM::Comm::World->cout() << "istep = npredict = " << istep
          << ", ||Grad_int|| = "<< sci(sqrt(gnorm2)) << endl;
#endif
    }
    if ( istep < control->get_npredict() && sstep == 0 )
    {
      FDM::ScalarVector Grad_int;
      if (!ctrl->owner())
        Grad_int.resize(ctrl_size());
      else
        Grad_int.alias( Gphi, offset_, ctrl_size() );
#if FDM_TEST_GRADIENT > 1
      {
        DGM::Format sci(12,20,'e');
        Scalar pnorm2 = Grad_data.Norm2();
        Scalar gnorm2 = 0.0;
        DGM::Comm::World->SumAll( &pnorm2, &gnorm2, 1 );
        DGM::Comm::World->cout() << "||Grad_data|| = "<<sci(sqrt(gnorm2))
            <<", pnorm2 = "<<sci(sqrt(pnorm2))<<endl;
      }
#endif
      for (Ordinal k=0; k<ctrl_size(); k++)
      {
        GradientFunction f( control, Grad_data, ctrl_size(), k );
        f.lstep = istep;
        control->state->domain()->timeIntegrator()->integrate( &f );
        Grad_int[k] += f.value;
      }
#if FDM_TEST_GRADIENT > 1
      {
        DGM::Format sci(12,20,'e');
        Scalar pnorm2 = Grad_int.Norm2();
        Scalar gnorm2 = 0.0;
        DGM::Comm::World->SumAll( &pnorm2, &gnorm2, 1 );
        DGM::Comm::World->cout() << "istep = " << istep
            << ", ||Grad_int|| = "<< sci(sqrt(gnorm2)) << endl;
      }
#endif
    }
  }
}

void Control::Entry::computePreconditioner(const Ordinal istep,
                                           const Ordinal sstep,
                                           const ScalarVector & phi,
                                           const VectorField & S,
                                           const VectorField & A,
                                           ScalarVector & Gphi)
{
#ifdef FDM_CODETRACE
  cout << "FDM::Control::Entry::computePreconditioner for " << name() << endl;
#endif

  FDM_UNDEFINED;
}

void Control::Entry::applyPreconditioner(const ScalarVector & phi,
                                         const ScalarVector & Gphi,
                                         ScalarVector & Pphi)
{
#ifdef FDM_CODETRACE
  cout << "FDM::Control::Entry::applyPreconditioner for " << name() << endl;
#endif

  FDM_UNDEFINED;
}

streamoff Control::Entry::read(const string & fname,
                               const streamoff skip,
                               ScalarVector & Gphi )
{
#ifdef FDM_CODETRACE
  cout << "FDM::Control::Entry::read for " << name() << endl;
#endif

  FDM_UNDEFINED;
  return 0;
}

streamoff Control::Entry::write(const string & fname,
                                const streamoff skip,
                                const ScalarVector & Gphi)
{
#ifdef FDM_CODETRACE
  cout << "FDM::Control::Entry::write for " << name() << endl;
#endif

  FDM_UNDEFINED;
  return 0;
}

void Control::Entry::plot(const VectorField & S,
                          const ScalarVector & Gphi,
                          const Ordinal npredict,
                          const Ordinal ntout,
                          const Ordinal nsstep,
                          const Ordinal riter,
                          const string * ext) const
{
#ifdef FDM_CODETRACE
  cout << "FDM::Control::Entry::plot for " << name() << endl;
#endif

  if (ext)
  {
    ctrl->plot(S,offset(),Gphi,npredict,ntout,nsstep,riter,*ext);
  }
  else
  {
    ctrl->plot(S,offset(),Gphi,npredict,ntout,nsstep,riter);
  }
}

streamoff Control::Entry::serial_read(const string & fname,
                                      const streamoff skip,
                                      ScalarVector & Gphi )
{
#ifdef FDM_CODETRACE
  cout << "FDM::Control::Entry::serial_read for " << name() << endl;
#endif

  FDM_UNDEFINED;
  return 0;
}

streamoff Control::Entry::serial_write(const string & fname,
                                       const streamoff skip,
                                       const ScalarVector & Gphi)
{
#ifdef FDM_CODETRACE
  cout << "FDM::Control::Entry::serial_write for " << name() << endl;
#endif

  FDM_UNDEFINED;
  return 0;
}

#ifdef DGM_PARALLEL
MPI_Offset Control::Entry::mpi_read(const string & fname,
                                    const MPI_Offset skip,
                                    ScalarVector & Gphi)
{
#ifdef FDM_CODETRACE
  cout << "FDM::Control::Entry::mpi_read for " << name() << endl;
#endif

  FDM_UNDEFINED;
  return 0;
}

MPI_Offset Control::Entry::mpi_write(const string & fname,
                                     const MPI_Offset skip,
                                     const ScalarVector & Gphi)
{
#ifdef FDM_CODETRACE
  cout << "FDM::Control::Entry::mpi_write for " << name() << endl;
#endif

  FDM_UNDEFINED;
  return 0;
}

#endif

}  // namespace FDM
