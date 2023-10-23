#ifndef DGM_DOMAIN_HPP
#define DGM_DOMAIN_HPP

/** \file Domain.hpp
    \brief Domain base class declaration
    \author Scott Collis
*/

// standard libraries
#include <iostream>
#include <string>
#include <vector>

// DTK includes
#include "DTK.hpp"
#include "DTK_TimeIntegrate.hpp"

// DGM libraries
#include "Comm.hpp"
#include "Types.hpp"
#include "Table.hpp"
#include "ArgList.hpp"
#include "Field.hpp"
#include "vField.hpp"
#include "BC.hpp"
#include "Source.hpp"
#include "Parameter.hpp"
#include "Response.hpp"
#include "String.hpp"
#include "Format.hpp"
#include "SolverML.hpp"
#include "FieldSlice.hpp"
#include "Statistics.hpp"
#include "SideLoop.hpp"

// Boost includes
#ifdef DGM_USE_GENERAL_GHOSTING
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#endif

// Json include
#ifdef DGM_USE_JSON
#include "json/json.h"
#include "json/serialization.h"
/// Turn on JSON file header
#define DGM_USE_JSON_HEADER
#endif

namespace DGM {

// forward declarations
class TimeInt;
class Material;
class Operator;
class IC;

/// Base class for all DGM computational space-time domains
/** The Domain is a base class.  We then inherit the general Domain
    characteristics but for specific problem types like Euler,
    Navier-Stokes, Burgers, Advection-Diffusion, etc. */
class Domain : public DTK::Domain<Scalar,Ordinal,vField> {

protected:

  ArgList &args;                ///< local reference to the arglist

  FieldSlice fieldslice;        ///< helper class for slicing a Field

  static const int buflen=256;  ///< Length of C-string buffers

  const DGM::Comm::Ptr comm;    ///< Communicator for this domain

public:

  typedef Size GlobalSize;      ///< Size of global variables
  typedef Ordinal LocalSize;    ///< Size of local variables

  /// Shared pointer to Domain
  typedef DGM::Shared<Domain>::Ptr Ptr;

  ofstream history;             ///< History file (C++)
  FILE *his;                    ///< History file (C)

  BC::db_type BC_db;            ///< BC database

  Source::db_type Source_db;    ///< Source term database

  /// Initial condition for this Domain
  DGM::Shared<IC>::Ptr initialCondition;

  Parameter::db_type Param_db;  ///< Parameter database

  vField U;                     ///< Solution field
  vField Ut;                    ///< Temporary field

  /// Domain partition for parallel execution
  Partition<Size,Ordinal,Scalar>::Ptr partition;

  std::string code;           ///< Name of the program
  const std::string root;     ///< Root name of input files
  std::string title;          ///< Title of the current run
  Table params;               ///< Table of parameters
  Json::Value json_root;      ///< Root of all Json parameters
  Json::Value &json_domain;   ///< Subset of Json parameters for this Domain
  vField::size_type Nfields;  ///< Number of fields on this Domain
  bool IO;                    ///< Turns Domain I/O on or off

  // diffusion stabilization
  Scalar stab;                ///< Diffusion stabilization factor
  Scalar bstab;               ///< Boundary diffusion stabilization factor

  Size ndof;                  ///< Total Domain degrees of freedom
  Ordinal nsd;                ///< Number of space dimensions

  Ordinal ne;                 ///< Local Number of elements

  TimeInt *time_int;          ///< Time integration object

  /// The DTK time integrator
  typedef DTK::TimeIntegrate<Scalar,Ordinal,vField,Domain> TimeIntegrate;
  DGM::Shared<TimeIntegrate>::Ptr timeIntegrate; ///< DTK time integration

  Material *material;         ///< Material properties object

  Response *response;         ///< Data analysis object

  Statistics *stats;          ///< Statistics object

  Ordinal lstep;              ///< Local time step index
  Ordinal step;               ///< Global time step index
  Scalar t;                   ///< Time
  Scalar CFL;                 ///< Stability estimate
  bool compute_CFL;           ///< Indicates CFL needs calculation
  Scalar dt;                  ///< Time step
  Scalar atime;               ///< Average cpu time per step
  dVector dtl;                ///< local time step
  Scalar dtmax;               ///< Maximum allowable time step
  Scalar CFLmax;              ///< Maximum allowable CFL
  Scalar tf;                  ///< Final time
  Ordinal Nt;                 ///< Number of time steps to solve
  Ordinal Ntout;              ///< Output interval (stats and restarts)
  Ordinal ntout;              ///< Time-step statistics output interval
  Ordinal Ntprb;              ///< Output interval for Response probe
  int ssiorder;               ///< Substep interpolation order
  bool useRTC;                ///< Whether to use RuntimeControl

  mutable CMC::Stopwatch wallTime;    ///< Cumulative wall time

  /// constructor
  Domain( DGM::ArgList &args, const DGM::Comm::Ptr = DGM::Comm::World);

  /// destructor
  virtual ~Domain();

  /// Return a pointer to the Domain communicator
  const DGM::Comm::Ptr get_comm() const {return comm;}

  /// accessor for args
  ArgList & get_args() const { return args; }

  /// \name Domain interface
  //@{

  /// Parses the argument list passed to Domain
  virtual void parse_args( DGM::ArgList &args );

  /// Shows the supported command line parameters for the Domain
  virtual void showUsage();

  /// Access the number of time steps
  virtual Ordinal get_Nt() const {return Nt;}

  /// Access the time step value
  virtual Scalar get_dt() const {return dt;}

  /// Get number of substeps
  virtual Ordinal get_sstep() const;

  /// Access the substep interpolation order
  virtual int get_ssiorder() const {return ssiorder;}

  /// Set the substep interpolation order
  virtual void set_ssiorder(const int so) {ssiorder = so;}

  /// Access the cpu time per solution step
  Scalar get_avg_cpu_per_step() const {return atime;}

  /// Primary Domain solve interface
  virtual int solve();

  /// Evaluate the action of the Domain operator
  virtual void action( vField &Us, vField &Uf ) { DGM_UNDEFINED; };

  /// Setup time integrator
  virtual void set_TimeInt( Ordinal=0 );

  /// Setup the old time integrator
  virtual void old_set_TimeInt(const int inttype);

  /// Setup Material properties
  virtual void set_material() {
    //comm->cout() << "Domain::set_material: using default material" << endl;
    //material = 0;
  }

  /// Solution accessor
  virtual vField & getU() { return U; }

  /// Temporary solution accessor
  virtual vField & getUt() { return Ut; }

  //! Timestep get method
  virtual Scalar timeStep() const { return dt; }

  //! Step number get method
  virtual Ordinal stepNumber() const { return lstep; }

  //! Time get method
  virtual Scalar time() const { return t; }

  //! Time set method
  virtual void time(const Scalar time) { t = time; }

  //! Get the number of time steps
  inline Ordinal numSteps() const { return Nt; }

  /// Support for TimeInt interface
  virtual void prestep(vField&, const Ordinal, const Ordinal, const Scalar) {}

  /// Support for TimeInt interface
  virtual void poststep(vField&, const Ordinal, const Ordinal, const Scalar) {}

  /// Support TimeInt interface
  virtual void prepareToAdvance() {}

  /// Support for TimeInt interface:  the time derivative for this PDE
  /** \param[in,out] U Solution vector Field
      \param[out]    F Negative of the time derivative

      \note You are responsible for zeroing or overwriting F
   */
  virtual void time_derivative(vField &U, vField &F) = 0;

  /// Support for DTK::TimeIntegrate for split schemes
  /** \param[in,out] U Solution vector Field
      \param[out]    F Negative of the time derivative
   */
  virtual void time_derivative(vField &U, vField &F, Ordinal) {DGM_UNDEFINED;}

  /// Compute the time derivative but without source terms
  virtual void time_derivative_no_source(vField&, vField&) {DGM_UNDEFINED;}

  /// Plot the solution on the Domain
  virtual int plot(const std::string&) {
    using std::endl;
    comm->cerr() << "Domain::plot() not implemented" << endl;
    comm->exit(DGM::FAILURE);
    return 0;
  }

  /// Compute the difference between two vFields on the Domain
  virtual int diff(const std::string &rst1, const std::string &rst2,
                   const Scalar aeps, const Scalar reps, const Scalar meps);

  /// Set the time step on the Domain
  virtual Scalar set_time_step( vField & ) {
    using std::endl;
    comm->cerr() << "Domain::set_time_step() not implemented" << endl;
    comm->exit(DGM::FAILURE);
    return 0;
  }

  /// Zeros all the Fields defined in this Domain
  virtual void zero_all_fields();

  /// Makes all Fields contiguous in memory for this Domain
  virtual void make_contiguous();

  /// Sets the initial condition for this Domain
  virtual void set_ic( vField &, std::string=".ic" ) = 0;

  /// Set both the time (t) and the step on the Domain
  virtual void set_t_step() { DGM_UNDEFINED; }

  /// Return the maximum quadrature order for all elements in the field
  inline Ordinal Qmax() const {
    if (U.size()==0)
      throw DGM::exception("Domain tried to access Qmax without first "
          "allocating a Field");
    return U[0]->Qmax;
  }

  /// Return the maximum modal order for all elements in the field
  inline Ordinal Lmax() const {
    if (U.size()==0)
      throw DGM::exception("Domain tried to access Lmax without first "
          "allocating a Field");
    return U[0]->Lmax;
  }
  //@}

  /// \name Boundary Conditions
  //@{
  /// Setup the boundary condition database
  virtual void setup_BCdb( );

  /// Read new boundary conditions (from the .bct file) into the database
  virtual void read_BCdb( ifstream & );

  /// Builds new boundary conditions
  virtual BC* make_BC( ifstream &, std::string & );

  /// loop over all boundary sides to check, if their type is valid
  virtual void verifyBCs(const vField &F) const;

  /// clear the BCdb map
  virtual void clear_BCdb();

  //===========================================================================
  // Temporary change to make NS_opt work [SSC]. This leads to a serious change
  // in the behavior of the boundary conditions routines and is undesirable.
  // This change should NOT be merged into the main development tree.

  /// Deprecated, try not to use
  virtual void enforce_bc(vField &);

  /// Deprecated, try not to use
  virtual void enforce_flux_bc(vField &);
  //===========================================================================
  //@}

  /// \name Source term database routines
  //@{
  /// Setup the Source database
  virtual void setup_Sourcedb( );

  /// Read the Source database
  virtual void read_Sourcedb( ifstream & );

  /// Make a source from a file stream
  virtual Source::Ptr make_Source( ifstream &, std::string & );

  /// Make a source from a vector of Sources
  virtual void make_Source(std::vector<std::pair<std::string,Source::Ptr> >&);

  /// Clear the Source database
  virtual void clear_Sourcedb();

  /// Provides the mechanism to add the source terms to the righthand side
  virtual void add_source(const vField &, vField &) { DGM_UNDEFINED; }

  /// Provide a mechanism to reset all source terms
  virtual void reset_source(const dVector &) { DGM_UNDEFINED; }

  /// Provide a mechanism to reset source term called "name"
  virtual void reset_source(const std::string name, const dVector &) {
    DGM_UNDEFINED;
  }
  //@}

  /// \name Provide DTK interface
  //@{
  /// Apply source terms
  virtual void applySource(const Scalar time, const vField &S, vField &R) {
    DGM_UNDEFINED;
  }
  /// Apply boundary conditions
  virtual void applyBC(const Scalar time, vField &R) {
    DGM_UNDEFINED;
  }
  //@}

  /// \name I/O on domains
  //@{
  /// Get the root of the input filenames
  inline std::string getRoot() const { return root; }

  /// Make file name at a given timestep and substep
  std::string mkname( const Ordinal iter, const Ordinal istep,
                      const Ordinal sstep,
                      const std::string &s = std::string() ) const;

  /// Make file name at a given timestep and substep with path prefix
  std::string mkname( const std::string &path, const Ordinal iter,
                      const Ordinal istep, const Ordinal sstep) const;

  /// Read from restart file, optionally read the header
  virtual void read( const std::string &, vField &,
                     const HeaderType = READ_HEADER);
  /// Read only the field
  /** \param[in] fname - filename to read from
      \param[in,out] F - Field to read data into   */
  virtual void read_field( const std::string &fname, vField &F ) const;
  /// Write to a restart file
  virtual void write( const std::string &, const vField & ) const;
  /// Read to a restart file with name root.ver.rst
  virtual void read( const Ordinal ver, vField & );
  /// Write to a restart file with name root.ver.rst
  virtual void write( const Ordinal ver, const vField & ) const;
  //@}

  /// \name Local parallel I/O on domains
  //@{
  /// Read my part of the domain in parallel
  virtual void local_read( const std::string &, vField &,
                           const HeaderType = READ_HEADER,
                           const bool saved_as_float=false );
  /// Read my part of the Domain (stream version)
  virtual void local_read( istream &, vField &, const std::string &,
                           const HeaderType = READ_HEADER,
                           const bool saved_as_float=false );
  /// Read just my part of the field
  virtual void local_read_field( const std::string &, vField & ) const;
  /// Write my part of the domain in parallel
  virtual void local_write( const std::string &, const vField &,
                            const bool save_as_float=false ) const;
  /// Write my part of the Domain (stream version)
  virtual void local_write( ostream &, const vField &, const std::string &,
                            const bool save_as_float=false ) const;
  /// Determin if a local file exists
  bool local_exists(const std::string &fs, const vField &F ) const;
  //@}

  /// \name Local parallel I/O with compression
  //@{
  /// Read my part of the domain in parallel
  void comp_read( const std::string &, vField &,
                  const HeaderType, const Json::Value &traits );
  /// Read my part of the Domain
  void comp_read( istream &, vField &, const std::string &,
                  const HeaderType, const Json::Value &traits );
  /// Write my part of the domain in parallel
  void comp_write( const std::string &, const vField &,
                   const Json::Value &traits ) const;
  /// Write my part of the Domain
  void comp_write( ostream &, const vField &, const std::string &,
                   const Json::Value &traits ) const;
  //@}

  /// \name Analysis methods
  //@{
  virtual void write_bndry_stats();
  virtual void compute_stats(const std::string &);
  virtual void plot_stats(const int);
  /// Output slices of the default vector field
  virtual void output_slices() {fieldslice.output_slices(U, step);}
  //@}

  /// \name Flux methods
  //@{
  /// Sets up the forward and reverse side maps
  void setup_side_maps();
  /// Applies the forward and reverse side maps
  void get_side_maps(const Side *const sl, const Side *const sr,
                     iVector &idr, iVector &idl) const;
  /// Compute the average flux (optionally accounting for the normal sign)
  virtual void average_flux(const vField &Uf, vField &Ff,
                            const char sign) const;
  //@}

#ifdef DGM_USE_GENERAL_GHOSTING
  /// \name Experimental methods for serialization
  //@{
  /// Save this Domain to a text archive
  void save(ostream &os) const {
    using std::cout;
    using std::endl;
    boost::archive::text_oarchive oa(os);
    oa << *this;
    cout << "step = " << step << endl;
    cout << "t    = " << t << endl;
  }
  /// Restore this Domain from a text archive
  void restore(istream &is) {
    using std::cout;
    using std::endl;
    boost::archive::text_iarchive ia(is);
    ia >> *this;
    cout << "step = " << step << endl;
    cout << "t    = " << t << endl;
  }
  //@}
#endif

  /// Returns the verbosity level
  int verbosity() const { return comm->verbosity(); }

  /// Connects integration points of two adjacent elements along a common side
  class SideMap {
  private:
    iVector idl_;  ///< global to local numbering on the left side (master)
    iVector idr_;  ///< global to local numbering on the right side
  public:
    /// read/write access to left map
    iVector &idl() {return idl_;}
    /// read/write access to right map
    iVector &idr() {return idr_;}
    /// read/write access to left map
    const iVector &idl() const {return idl_;}
    /// read/write access to right map
    const iVector &idr() const {return idr_;}
    /// reference to left side value
    Scalar &l(Side *s, const Ordinal q) { return s->u[idl_[q]]; }
    /// const reference to left side value
    Scalar l(const Side *s, const Ordinal q) const {
      return s->u[idl_[q]];
    }
    /// reference to right side value
    Scalar &r(Side *s, const Ordinal q) { return s->link->u[idr_[q]]; }
    /// constant reference to right side value
    Scalar r(const Side *s, const Ordinal q) const {
      return s->link->u[idr_[q]];
    }
    /// reorder vector values to match the local side integration point order
    void renumber(const dVector &adj, dVector &loc) const {
      const Ordinal qstot = loc.size();
      // assume that both sides have the same number of quadrature points
      assert(adj.size() == loc.size());
      for (Ordinal q = 0; q < qstot; ++q) {
        loc(idl()[q]) = adj(idr()[q]);
      }
    }
  };

#ifdef DGM_USE_EPETRA

protected:

  Teuchos::RCP<Epetra_CrsMatrix> A;              ///< system matrix
  Teuchos::RCP<Epetra_Vector> x;                 ///< solution vector
  Teuchos::RCP<Epetra_Vector> b;                 ///< rhs vector

  Teuchos::RCP<Epetra_LinearProblem> lp;         ///< linear problem
  Teuchos::RCP<Amesos_BaseSolver> AmesosSolver;  ///< a direct solver
  Teuchos::RCP<AztecOO> AztecOOSolver;           ///< an iterative solver

  Teuchos::RCP<DGM::SolverML> ml;                ///< multi-level solver

  /// Build the lefthand-side matrix
  virtual void Matrix( Epetra_CrsMatrix &A ) const { DGM_UNDEFINED; }

  /// Build the righthand-side vector
  virtual void RHS( Epetra_Vector &b ) const { DGM_UNDEFINED; }

  /// Supported linear solvers
  enum SolverType {
    solve_direct = 0,                            ///< Direct solver
    solve_iterative = 1,                         ///< Iterative solver
    solve_iterative_ML = 2                       ///< Multi-Level solvers
  };

  Epetra_CrsMatrix* GenerateMatrixViaMatlabOutput(
      const DGM::Operator &op) const;

  void iterative_solve_matrixfree(const Teuchos::ParameterList &params,
                                  const bool refactor) const;
  void iterative_solve(const Teuchos::ParameterList &params,
                       const bool refactor) const;
  void iterative_ML_solve(const Teuchos::ParameterList &params,
                          const bool rebuild,
                          const bool matlab_output = false
                          );
  void direct_solve(const bool refactor);

public:

  /// Scatter values to global Epetra vector
  static void scatterVector(
      const std::vector<int> &indexlist,        ///< global ids for test modes
      const dVector     &vh,                    ///< local vector
      Epetra_Vector     &erhs                   ///< parallel, global vector
      );

  /// Scatter local matrix to global matrix
  static void scatterMatrix(
      const std::vector<int> &indexlist_test,   ///< global ids for test modes
      const std::vector<int> &indexlist_trial,  ///< global ids for trial modes
      const dMatrix     &MATloc,                ///< local matrix
      Epetra_CrsMatrix  &A                      ///< parallel, global matrix
      );

  /// Reset the A matrix
  void reset_system_matrix() { A = Teuchos::null; }

#else

public:

  /// Reset the A matrix (default is undefined method)
  void reset_system_matrix() { DGM_UNDEFINED; }

#endif

protected:

#ifdef DGM_USE_GENERAL_GHOSTING
  /// \name Serialization
  //@{
  /// Provide access for boost
  friend class boost::serialization::access;
  /// Serialize method
  template<typename Archive>
  void serialize(Archive &ar, const unsigned int version) {
    ar & step;
    ar & t;
  }
  //@}
#endif

private:

  /// Read the Domain header from a restart file
  virtual streamoff read_old_header(Json::Value&,istream&,
                                    const vField&,const std::string&);

  /// Skip over the Domain header from a restart file
  virtual streamoff skip_old_header(Json::Value&,istream&, const vField&) const;

  /// Read the Domain header from a restart file
  virtual streamoff read_header(Json::Value&,istream&,
                                const vField&,const std::string&);

  /// Skip over the Domain header from a restart file
  virtual streamoff skip_header(Json::Value&,istream &,
                                const std::string &, const vField & ) const;

  /// Write the Domain header to a restart file
  virtual streamoff write_header(ostream &, const vField &, const std::string &,
                                 const bool=false) const;

  /// Read the Domain header from a restart file
  virtual streamoff read_header(Json::Value&,const std::string &,
                                const vField &);

  /// Skip over the Domain header from a restart file
  virtual streamoff skip_header(Json::Value&, const std::string&,
                                const vField&) const;

  /// Write the Domain header to a restart file
  virtual streamoff write_header(const std::string &, const vField &,
                                 const bool=false) const;

  //======================== Json Headers =====================================

  /// Read JSON header to a restart file
  virtual streamoff read_json_header(Json::Value&,istream&,
                                     const vField&, const std::string&) const;

  /// Write JSON header to a restart file
  virtual streamoff write_json_header(ostream &, const vField &,
                                      const std::string &,
                                      const bool=false) const;
};

} // namespace DGM

#endif  // DGM_DOMAIN_HPP
