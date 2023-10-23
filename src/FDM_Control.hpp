#ifndef FDM_CONTROL_HPP
#define FDM_CONTROL_HPP

/** \file FDM_Control.hpp
    \brief FDM::Control interface
    \author Scott Collis
    \author Bill Spotz
*/

// DGM includes
#include "Comm.hpp"

// FDM includes
#include "FDM_Types.hpp"
#include "FDM_VectorField.hpp"
#include "FDM_Ctrl.hpp"

// JSON includes
#include "json/json.h"

namespace FDM
{

// Forward declarations
class Control;
class State;
class Adjoint;

//============================================================================
//                             FDM::Control
//============================================================================

//! FDM Control class holds multiple controls (Ctrls)
class Control : public DTK::Control< Scalar,
                                     Ordinal,
                                     VectorField,
                                     ScalarVector,
                                     State,
                                     Control >
{
protected:
  State *state;               ///< State to control
  Scalar dt;                  ///< Constant time-step
  Ordinal npredict;           ///< Number of time step
  Ordinal nsstep;             ///< Number of sub-steps
  Ordinal npp;                ///< Number of time-step * number of sub_steps

  /// \name Parallel processing data-structures
  /** These data-structures make parallel communication of Control information
      much easier. */
  //@{
  Ordinal gnum;               ///< Global number of controls across all procs
  Ordinal glen;               ///< Global control length across parallel procs
  OrdinalVector global_len;   ///< Global lengths for parallel gather/scatter
  OrdinalVector global_disp;  ///< Global displ for parallel gather/scatter
  //@}

  const int verb;             ///< Verbosity level
  ostream & vout;             ///< verbose output stream

  DGM::Comm::Ptr comm;        ///< Communicator for this Control

  virtual void setup();       ///< Setup the Control database

public:

  /// Shared pointer to Control
  typedef Teuchos::RCP< Control > Ptr;

  /// Control database entry
  class Entry;
  typedef Teuchos::RCP< Entry > EntryPtr;

  ScalarVector phi;                 ///< Control vector
  list< EntryPtr >  phi_db;         ///< Control Entry database
  mutable ScalarVector costs;       ///< Work vector for entry costs

  /// Constructor
  Control(State *_state,
          Json::Value &root);

  /// Destructor
  virtual ~Control();

  /// accessor for DGM::Comm
  DGM::Comm::Ptr get_comm() const { return comm; }

  /// \name Provide DTK::Control interface
  //@{
  virtual Control *clone() const = 0;

  virtual size_t num_ctrl() const;

  virtual void reset_costs();

  /// Outputs the costs to a supplied output stream
  virtual void output_costs(std::ostream &os) const;

  /// Returns the local length of phi for this Control
  virtual size_t size() const;

  /// Resizes the local length of phi for this Control
  virtual void resize(Ordinal n);

  /// Returns the global length of phi for this Control
  virtual Ordinal global_size() const;

  /// Plot the control
  virtual void plot(const Ordinal ntout,
                    const Ordinal iter,
                    const std::string *ext=0) const;

  /// Number of substeps (assumed fixed) for this Control object
  Ordinal get_nsstep() const;

  /// Number of timesteps (assumed fixed) to predict the solution
  Ordinal get_npredict() const;

  /// Return the timestep (assumed fixed) for this Control object
  Scalar get_dt() const;

  /// Initialize the Control
  virtual void initialize();

  /// zero out the Control
  virtual void zero();

  /// output the Control
  virtual void output(Ordinal);

  /// Set the data on this Control
  virtual void set_data(const Ordinal istep,
                        const Ordinal sstep=0);

  virtual void load(ScalarVector &,
                    const Ordinal,
                    const Ordinal=0) const;

  virtual void store(ScalarVector&,
                     const Ordinal,
                     const Ordinal=0);

  virtual void set_direction();

  virtual Scalar cost() const;

  virtual Scalar cost(const Ordinal,
                      const Ordinal=0) const;

  /// Call the bound method over all Ctrl's and all time
  virtual void bound();

  /// Call the bound method on each Ctrl at each time/sub step
  virtual void bound(const Ordinal istep,
                     const Ordinal sstep=0);

  /// Call the realizable  method over all Ctrl's and all time
  virtual bool realizable();

  /// Call the realizable method on each Ctrl at each time/sub step
  virtual bool realizable(const Ordinal,
                          const Ordinal=0);

  /// Compute the inner-product between two Control objects
  virtual Scalar inner_product(const Control * Y) const;

  /// Compute the inner-product between two Control objects
  virtual Scalar inner_product(const Control & Y) const;

  virtual Scalar norm() const;

  /// Compute a contribution to the gradient
  virtual void gradient(const VectorField & S,
                        const VectorField & A,
                        Control & G,
                        const Ordinal istep,
                        const Ordinal sstep=0);

  /// Compute a contribution to a diagonal preconditioner at one timestep
  virtual void computePreconditioner(const VectorField & S,
                                     const VectorField & A,
                                     Control & P,
                                     const Ordinal istep,
                                     const Ordinal sstep=0);

  /// Apply a preconditioner
  virtual void applyPreconditioner(const Control & G,
                                   Control & P);

  /// Compute Hessian vector product for the observation term
  virtual void HessVecProd_obs(const VectorField & S,
                               const VectorField & A,
                               const Control & x,
                               const Control & dx,
                               Control & H_dx,
                               const Ordinal istep,
                               const Ordinal sstep=0);

  /// Compute Hessian vector product for the regularization term
  virtual void HessVecProd_reg(const Control & x,
                               const Control & dx,
                               Control & H_dx,
                               const Ordinal istep,
                               const Ordinal sstep=0);

  /// Read the control from a file:  needed for control restart
  virtual std::streamoff read(const std::string &,
                              const std::streamoff);

  /// Write the control to a file:  needed for control restart
  virtual std::streamoff write(const std::string &,
                               const std::streamoff);

  /// If any Control::Entry is unsteady then return false, otherwise true
  virtual bool steady() const;

  /// Gather control vector from across a parallel machine
  virtual void gather(ScalarVector &) const;

  /// Scatter control vector across parallel machine
  virtual void scatter(ScalarVector &);

  /// Accessor for the global (across a parallel processor) control length
  virtual Ordinal get_glen() const;

  /// Accessor that gives access to the State pointer
  virtual State* get_state();

  /// Accessor for Control vector
  virtual const ScalarVector & get_phi() const;

  /// Accessor to Control vector as a raw pointer
  // virtual const Scalar * get_phi_ptr() const;

  //@}

  friend void scale(const Scalar a,
                    const Control::Ptr & X);

  friend void add(const Control::Ptr & X,
                  Control::Ptr & Y);

  friend void axpy(const Scalar a,
                   const Control::Ptr & X,
                   Control::Ptr & Y);

  friend void axpy(const Scalar a,
                   const Control::Ptr & X,
                   const Control::Ptr & Y,
                   Control::Ptr & Z);

protected:

  // Copy constructor
  Control(const Control *in);

private:

  Control(const Control &);

};

// Inline implementations

inline void scale(const Scalar a,
                  const Control::Ptr & X)
{
  X->phi *= a;
}

inline void add(const Control::Ptr & X,
                Control::Ptr & Y)
{
  Y->phi.Add(X->phi);
}

inline void axpy(const Scalar a,
                 const Control::Ptr & X,
                 Control::Ptr & Y)
{
  daxpy(a,X->phi,Y->phi);
}

inline void axpy(const Scalar a,
                 const Control::Ptr & X,
                 const Control::Ptr & Y,
                 Control::Ptr & Z)
{
  daxpy(a,X->phi,Y->phi,Z->phi);
}

//============================================================================
//                       Control Database Entry
//============================================================================

class Control::Entry
{
  Control *control;       ///< Control database that owns this entry
  std::string name_;      ///< Name of this control entry
  Size offset_;           ///< Offset to start of Entry's data in phi
  Size length_;           ///< Total length of Entry's data in phi
  Ordinal ntime_;         ///< Number of time slabs
  Ctrl *ctrl;             ///< Abstract control object
  const int verb;         ///< Verbosity level
  ostream & vout;         ///< Verbosity output stream
  ScalarVector Grad_data; ///< Storage for gradient information
  ScalarVector Prec_data; ///< Storage for preconditioner information
  DGM::Comm::Ptr comm;    ///< Communicator

public:
  /// Shared pointer
  typedef Teuchos::RCP< Control::Entry > Ptr;

private:
  /// Disabled Constructors
  Entry();
  Entry(const Entry &);

public:
  /// Constructor
  Entry(Control *C,
        const string n,
        const Ordinal off,
        const Ordinal nt,
        Ctrl *c);

  /// Destructor
  ~Entry();

  /// Accessor for name
  void name(const std::string name);

  /// Accessor for name
  std::string name() const;

  /// Accessor for ntime
  Ordinal ntime() const;

  /// Set for ntime
  void ntime(const Ordinal ntime);

  /// Accessor for length
  Size length() const;

  /// Setter for length
  void length(const Size length);

  /// Set for offset
  void offset(const Size offset);

  /// Accessor for offset
  Size offset() const;

  /// Length of each slab
  Size ctrl_size() const;

  /// Get a pointer to Ctrl for this Entry
  Ctrl* get_ctrl();

  /// Get a constant pointer to Ctrl for this Entry
  const Ctrl* get_ctrl() const;

  /// Puts the data in global_phi into the ctrl's
  void set_data(const Ordinal index,
                const ScalarVector & global_phi);

  /// Gets the data from Ctrl objects and puts in global_phi
  void get_data(const Ordinal index,
                ScalarVector & global_phi);

  /// query whether the fill method is overloaded
  bool has_fill() const;

  /// Gets the data from Ctrl objects and puts in global_phi
  void fill(const Ordinal index,
            const Scalar time,
            ScalarVector & global_phi);

  /// Simply calls the Ctrl::output() method
  void output() const;

  /// Sets the correct view into the global control and sets the direction
  void set_direction(const Ordinal index,
                     ScalarVector & global_phi );

  /// Load a vector with the global control data
  void load(const Ordinal index,
            const ScalarVector & global_phi,
            ScalarVector &out ) const;

  /// Store a vector into the global control data
  void store(ScalarVector & in,
             const Ordinal index,
             ScalarVector & global_phi );

  /// Take the Ctrl inner product of two control vectors
  /** Does so on a particular time slice given the index */
  Scalar inner_product(const Ordinal index,
                       const ScalarVector & Xphi,
                       const ScalarVector & Yphi);

  /// Compute the contribution to the total cost for this Ctrl and timeslice
  Scalar cost(const Ordinal index,
              const ScalarVector & phi);

  /// Bound the Ctrl data for timeslice=index
  void bound(const Ordinal index,
             ScalarVector & phi);

  /// Determine realizability for timeslice=index
  bool realizable(const Ordinal index,
                  ScalarVector & phi);

  /// Compute the contribution to the gradient
  inline void gradient(const Ordinal istep,
                       const Ordinal sstep,
                       const ScalarVector & phi,
                       const VectorField & S,
                       const VectorField & A,
                       ScalarVector & Gphi);

  void computePreconditioner(const Ordinal istep,
                             const Ordinal sstep,
                             const ScalarVector &phi,
                             const VectorField &S,
                             const VectorField &A,
                             ScalarVector & Gphi);

  void applyPreconditioner(const ScalarVector & phi,
                           const ScalarVector & Gphi,
                           ScalarVector & Pphi);

  streamoff read(const string & fname,
                 const streamoff skip,
                 ScalarVector & Gphi );

  streamoff write(const string & fname,
                  const streamoff skip,
                  const ScalarVector & Gphi);

  void plot(const VectorField & S,
            const ScalarVector & Gphi,
            const Ordinal npredict,
            const Ordinal ntout,
            const Ordinal nsstep,
            const Ordinal riter,
            const string *ext) const;

  /// set the time for this Ctrl
  void time(const Scalar time) { ctrl->time(time); }

  /// get the time for this Ctrl
  Scalar time() const { return ctrl->time(); }

private:

  streamoff serial_read(const string & fname,
                        const streamoff skip,
                        ScalarVector & Gphi );

  streamoff serial_write(const string & fname,
                         const streamoff skip,
                         const ScalarVector & Gphi);

#ifdef DGM_PARALLEL
  MPI_Offset mpi_read(const string & fname,
                      const MPI_Offset skip,
                      ScalarVector & Gphi );

  MPI_Offset mpi_write(const string & fname,
                       const MPI_Offset skip,
                       const ScalarVector & Gphi);

#endif

};

}  // namespace FDM

#endif
