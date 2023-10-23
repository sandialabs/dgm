#ifndef FDM_DOMAIN_HPP
#define FDM_DOMAIN_HPP

//! \file   FDM_Domain.hpp
//! \brief  Declarations for the FDM Domain
//! \author Bill Spotz

// Std includes
#include <map>
using std::map;

// Teuchos includes
#include "Teuchos_RCP.hpp"

// DTK includes
#include "DTK_TimeIntegrate.hpp"

// FDM includes
#include "FDM_Field.hpp"
#include "FDM_VectorField.hpp"

// JSON includes
#include "json/json.h"

// DGM includes
#ifdef DGM_PARALLEL
#include "MpiComm.hpp"
#else
#include "SerialComm.hpp"
#endif
#include "Table.hpp"

namespace FDM
{

class Source;

//! Domain for finite difference methods

//! A Domain is a collection of Fields and related physical data.  A
//! Domain should contain enough information to fully describe a
//! steady state problem or a single time slice of a time-dependent
//! problem.  For this base class, the number of Fields and what those
//! Fields represent is completely arbitrary.
class Domain : public DTK::Domain< Scalar, Ordinal, VectorField >
{
public:

  DGM::Table     params;
  Json::Value    json_root;   // Needed to compile but not used.

  //! Available time integration methods
  enum TimeMethod
  {
    LeapFrog,
    RungeKutta,
    TVD,
    ForwardEuler,
    LSRK14
  };

  /** \brief Domain constructor with time step info
   *
   * \param startTime [in] Value of time at start
   *
   * \param timeStep [in] Size of time steps
   *
   * \param numSteps [in] Number of time steps
   *
   * \param timeOutInterval [in] Time output interval
   *
   * \param fieldOutInterval [in] Field output interval
   */
  Domain(const Scalar  startTime        =   0,
         const Scalar  timeStep         =   1,
         const Ordinal numSteps         =   1,
         const Ordinal timeOutInterval  =  20,
         const Ordinal fieldOutInterval = 100);

  /** \brief Domain constructor with mesh and time step info
   *
   * \param mesh [in] Pointer to Mesh for Domain
   *
   * \param startTime [in] Value of time at start
   *
   * \param timeStep [in] Size of time steps
   *
   * \param numSteps [in] Number of time steps
   *
   * \param timeOutInterval [in] Time output interval
   *
   * \param fieldOutInterval [in] Field output interval
   */
  Domain(const MeshPtr mesh,
         const Scalar  startTime        =   0,
         const Scalar  timeStep         =   1,
         const Ordinal numSteps         =   1,
         const Ordinal timeOutInterval  =  20,
         const Ordinal fieldOutInterval = 100);

  /** \brief Copy constructor
   *
   * \param domain [in] Source Domain
   */
  Domain(const Domain & domain);

  /** \brief Domain destructor
   */
  virtual ~Domain();

  /** \brief Virtual solve method
   */
  virtual int solve() = 0;

  /** \brief Prepare to advance
   */
  virtual inline void prepareToAdvance();

  /** \brief Add a Field to the Domain
   *
   * \param field [in] Field to be added to Domain
   */
  virtual void addField(const FieldPtr field);

  /** \brief Create a Field and add it to the Domain
   *
   * \param symbol [in] New Field symbol
   *
   * \param name [in] New Field name
   *
   * \param stagger [in] Array of Field stagger flags
   */
  virtual FieldPtr createField(const string & symbol,
                               const string & name,
                               const ArrayView< const int > stagger =
                                 ArrayView< const int >());

  /** \brief Return an array of Field symbol names
   */
  virtual inline ArrayView< const string >
  fieldSymbols() const;

  /** \brief Field query
   *
   * \param symbol [in] Name of Field being queried
   */
  virtual bool
  hasField(const string & symbol) const;

  /** \brief Field accessor method
   *
   * \param symbol [in] Symbol of Field being requested
   */
  virtual FieldPtr field(const string & symbol);

  /** \brief Add a constant to the Domain
   *
   * \param symbol [in] Symbol of constant being set
   *
   * \param constant [in] Value of constant being set
   */
  virtual void setConstant(const string & symbol,
                           const Scalar constant);

  /** \brief Return an array of constant symbol names
   */
  virtual inline ArrayView< const string >
  constantSymbols() const;

  /** \brief Constant accessor method
   *
   * \param symbol [in] Symbol of constant being requested
   */
  virtual Scalar getConstant(const string & symbol) const;

  /** \brief Root of input filenames accessor
   */
  virtual inline string getRoot() const;

  /** \brief Parallel output
   */
  inline std::ostream & out() const;

  /** \brief Parallel error
   */
  inline std::ostream & err() const;

  /** \brief Mesh accessor method
   */
  virtual inline MeshPtr getMesh() const;

  /** \brief Pass-through getRank method
   */
  virtual inline int getRank() const;

  /** \brief Pass-through getCommIndex method
   *
   * \param axis [in] Axis along which this comm index is requested
   */
  inline int getCommIndex(int axis) const;

  /** \brief Pass-through getMDComm method
   */
  virtual inline MDCommPtr getMDComm() const;

  /** \brief Pass-through getComm method
   */
  virtual inline CommPtr getComm() const;

  /** \brief DTK/DGM get_comm method
   */
  inline const DGM::Comm::Ptr get_comm() const;

  /** \brief Pass-through getCoordinates method
   */
  virtual inline ArrayView< MDVectorPtr > getCoordinates() const;

  /** \brief Pass-through getCoordinates method
   *
   * \param axis [in] Axis along which the coordinates are requested
   */
  virtual inline Domi::MDArrayView< const Scalar >
  getCoordinates(int axis) const;

  /** \brief Pass-through getCoordinatesNonConst method
   *
   * \param axis [in] Axis along which the coordinates are requested
   */
  virtual inline Domi::MDArrayView< Scalar >
  getCoordinatesNonConst(int axis) const;

  /** \brief Pass-through getGlobalDims method
   */
  inline
  const Array< Domi::dim_type > getGlobalDims() const;

  /** \brief Pass-through getGlobalDim method
   *
   * \param axis [in] Axis along which the global dimension is requested
   */
  inline Ordinal getGlobalDim(int axis) const;

  /** \brief Pass-through getLocalDims method
   */
  inline const Array< Domi::dim_type > getLocalDims() const;

  /** \brief Pass-through getLocalDim method
   *
   * \param axis [in] Axis along which the local dimension is requested
   *
   * \param withPad [in] Flag indicating whether the padding should be
   *        included in the local dimension
   */
  inline Domi::dim_type getLocalDim(int axis,
                                    bool withPad=false) const;

  /** \brief Pass-through getGlobalRankBounds method
   *
   * \param axis [in] Axis along which the global rank bounds are
   *        requested
   *
   * \param withBndryPad [in] Flag indicating whether the boundary
   *        padding should be included in the global rank bounds
   */
  inline Domi::Slice getGlobalRankBounds(int axis,
                                         bool withBndryPad=false) const;

  /** \name Time stepping set/get methods */
  //@{

  /** \brief Solution accessor
   */
  inline VectorField & getU();

  /** \brief Temporary solution accessor
   */
  inline VectorField & getUt();

  /** \brief Start time set method
   *
   * \param time [in] Value of the start time
   */
  virtual inline void startTime(const Scalar time);

  /** \brief Start time get method
   */
  virtual inline Scalar startTime() const;

  /** \brief End time set method
   *
   * \param time [in] Value of the end time
   */
  virtual inline void endTime(const Scalar time);

  /** \brief End time get method
   */
  virtual inline Scalar endTime() const;

  /** \brief Timestep set method
   *
   * \param timeStep [in] Value of the time step
   */
  virtual inline void timeStep(const Scalar timeStep);

  /** \brief Timestep get method
   */
  virtual inline Scalar timeStep() const;

  /** \brief Number of steps set method
   *
   * \param numSteps [in] Number of time steps
   */
  virtual inline void numSteps(const Ordinal numSteps);

  /** \brief Number of steps get method
   */
  virtual inline Ordinal get_Nt() const;

  /** \brief Numer of substeps get method
   */
  virtual inline Ordinal get_sstep() const;

  /** \brief Time output interval set method
   *
   * \param interval [in] Interval, in time steps, between time
   *        stepping output
   */
  virtual inline void timeOutInterval(const Ordinal interval);

  /** \brief Time output interval get method
   */
  virtual inline Ordinal timeOutInterval() const;

  /** \brief Field output interval set method
   */
  virtual inline void fieldOutInterval(const Ordinal interval);

  /** \brief Field output interval get method
   */
  virtual inline Ordinal fieldOutInterval() const;

  /** \brief Step number get method
   */
  virtual inline Ordinal stepNumber() const;

  /** \brief Step number set method
   *
   * \param stepNumber [in] Current time step number
   */
  virtual inline void stepNumber(const Ordinal stepNumber);

  /** \brief Time get method
   */
  virtual inline Scalar time() const;

  /** \brief Time set method
   *
   * \param time [in] Value of the current time
   */
  virtual inline void time(const Scalar time);

  /** \brief TimeMethod get
   */
  virtual inline TimeMethod timeMethod() const;

  /** \brief TimeMethod set
   *
   * \param timeMethod [in] Value of the time method
   */
  virtual void timeMethod(const TimeMethod timeMethod);

  /** \brief TimeIntegrator get method
   */
  virtual inline
  Teuchos::RCP<
    DTK::TimeIntegrate< 
      FDM::Scalar,
      FDM::Ordinal,
      FDM::VectorField,
      FDM::Domain > > timeIntegrator() const;

  /** \brief TimeIntegrator set method
   *
   * \param timeIntegrator [in] Value of the time integrator
   */
  virtual void
  timeIntegrator(const Teuchos::RCP<
                   DTK::TimeIntegrate<
                     FDM::Scalar,
                     FDM::Ordinal,
                     FDM::VectorField,
                 FDM::Domain > > timeIntegrator);

  //@}

  /** \name Time stepping actions */
  //@{

  /** \brief Start the time stepping
   */
  virtual void startTimeStepping();

  /** \brief Advance the time by the specified number of time steps
   *
   * \param numSteps [in] Number of time steps to advance
   */
  virtual void advanceTime(const int numSteps=1);

  /** \brief Advance the time steps by the specified number of time
   *         steps
   *
   * \param numSteps [in] Number of time steps to advance
   */
  virtual inline void advanceStep(const int numSteps=1);

  /** \brief Report whether time stepping is finished
   */
  virtual inline bool finished() const;

  //@}

  /** \name I/O methods */
  //@{

  virtual void global_read(const std::string & fname);
  virtual std::string mkname(const Ordinal iter,
                             const Ordinal istep,
                             const Ordinal sstep,
                             const std::string &s=std::string()) const;
  virtual void local_read(const string & fname,
                          VectorField & F,
                          HeaderType ht=READ_HEADER,
                          const bool saved_as_float=false);
  virtual void local_read(istream & fs,
                          VectorField & F,
                          const string & fname,
                          HeaderType ht=READ_HEADER,
                          const bool saved_as_float=false);
  virtual void local_read_field(const string & fname,
                                VectorField & F) const;
  virtual void local_write(const string & fname,
                           const VectorField & F,
                           const bool save_as_float=false) const;
  virtual void local_write(ostream & fs,
                           const VectorField & F,
                           const string & fname,
                           const bool save_as_float=false) const;

  //@}

  /** \name Compressed local I/O required for DTK::InCore */
  //@{

  inline void comp_read(const std::string &fname,
                        VectorField &F,
                        const HeaderType headerType,
                        const Json::Value &traits);
  inline void comp_read(std::istream &fs,
                        VectorField &F,
                        const std::string &fname,
                        const HeaderType headerType,
                        const Json::Value &traits);
  inline void comp_write(const std::string &fname,
                         const VectorField &F,
                         const Json::Value &traits) const;
  inline void comp_write(std::ostream &fs,
                         const VectorField &F,
                         const std::string &fname,
                         const Json::Value &traits) const;

  //@}

  /** \name Source database */
  //@{

  /** \brief Pointer to Source
   */
  typedef Teuchos::RCP< FDM::Source > SourcePtr;

  /** \brief Source database type
   */
  typedef std::map< std::string, SourcePtr > Source_db_type;

  /** \brief Source database iterator
   */
  typedef Source_db_type::iterator Source_db_itr;

  /** \brief Source database
   */
  Source_db_type Source_db;

  //@}

private:

  // Pointer to the mesh shared by all of the Fields in the Domain
  MeshPtr _mesh;

  // An array of all of the Field symbols
  Array< string > _fieldSymbols;

  // An array of all of the constant symbol names
  Array< string > _constantSymbols;

  // A map between Field names and the corresponding Field
  map< string, FieldPtr > _fields;

  // A map between constant names and the corresponding constant
  map< string, Scalar > _constants;

  // The root name
  string _root;

  // The DGM Comm, equivalent to the Teuchos::Comm underlying the Mesh
  DGM::Comm::Ptr _dgmComm;

  // A Black Hole stream, for output in an MPI setting
  static Teuchos::oblackholestream _blackHole;

protected:

  // Solution vector field
  VectorField _U;

  // Temporary solution vector field
  VectorField _Ut;

  // Start time
  Scalar _startTime;

  // Time step
  Scalar _timeStep;

  // Number of steps
  Ordinal _numSteps;

  // Time stepping output interval
  Ordinal _timeOutInterval;

  // Field output interval
  Ordinal _fieldOutInterval;

  // Current time step number
  Ordinal _stepNumber;

  // Current time
  Scalar _time;

  // Time stepping method
  TimeMethod _timeMethod;

  // Parallel output stream
  std::ostream * _pout;

  // Parallel error stream
  std::ostream * _perr;

  // Time integrator
  Teuchos::RCP < DTK::TimeIntegrate < FDM::Scalar,
                                      FDM::Ordinal,
                                      FDM::VectorField,
                                      FDM::Domain > > _timeIntegrator;
};

////////////////////////////
// Inline implementations //
////////////////////////////

////////////////////////////////////////////////////////////////////////

inline
void
Domain::prepareToAdvance()
{
}

////////////////////////////////////////////////////////////////////////

inline
ArrayView< const string >
Domain::fieldSymbols() const
{
  return _fieldSymbols();
}

////////////////////////////////////////////////////////////////////////

inline
ArrayView< const string >
Domain::constantSymbols() const
{
  return _constantSymbols();
}

////////////////////////////////////////////////////////////////////////

inline
string
Domain::getRoot() const
{
  return _root;
}

////////////////////////////////////////////////////////////////////////

inline
std::ostream &
Domain::out() const
{
  return *_pout;
}

////////////////////////////////////////////////////////////////////////

inline
std::ostream &
Domain::err() const
{
  (*_perr) << getRank() << ": ";
  return (*_perr);
}

////////////////////////////////////////////////////////////////////////

inline
MeshPtr
Domain::getMesh() const
{
  return _mesh;
}

////////////////////////////////////////////////////////////////////////

inline
int
Domain::getRank() const
{
  return _mesh->getRank();
}

////////////////////////////////////////////////////////////////////////

int
Domain::getCommIndex(int axis) const
{
  return _mesh->getMDMap()->getCommIndex(axis);
}

////////////////////////////////////////////////////////////////////////

inline
MDCommPtr
Domain::getMDComm() const
{
  return _mesh->getMDComm();
}

////////////////////////////////////////////////////////////////////////

inline
CommPtr
Domain::getComm() const
{
  return _mesh->getMDComm()->getTeuchosComm();
}

////////////////////////////////////////////////////////////////////////

const DGM::Comm::Ptr
Domain::get_comm() const
{
  return _dgmComm;
}

////////////////////////////////////////////////////////////////////////

inline
ArrayView< MDVectorPtr >
Domain::getCoordinates() const
{
  return _mesh->getCoordinates();
}

////////////////////////////////////////////////////////////////////////

inline
Domi::MDArrayView< const Scalar >
Domain::getCoordinates(int axis) const
{
  return _mesh->getCoordinates(axis);
}

////////////////////////////////////////////////////////////////////////

inline
Domi::MDArrayView< Scalar >
Domain::getCoordinatesNonConst(int axis) const
{
  return _mesh->getCoordinatesNonConst(axis);
}

////////////////////////////////////////////////////////////////////////

inline
const Array< Domi::dim_type >
Domain::getGlobalDims() const
{
  return _mesh->getGlobalDims();
}

////////////////////////////////////////////////////////////////////////

inline
Ordinal
Domain::getGlobalDim(int axis) const
{
  return _mesh->getGlobalDim(axis);
}

////////////////////////////////////////////////////////////////////////

inline
const Array< Domi::dim_type >
Domain::getLocalDims() const
{
  return _mesh->getLocalDims();
}

////////////////////////////////////////////////////////////////////////

inline
Domi::dim_type
Domain::getLocalDim(int axis,
                    bool withPad) const
{
  return _mesh->getLocalDim(axis, withPad);
}

////////////////////////////////////////////////////////////////////////

inline
Domi::Slice
Domain::getGlobalRankBounds(int axis,
                            bool withBndryPad) const
{
  return _mesh->getGlobalRankBounds(axis, withBndryPad);
}

////////////////////////////////////////////////////////////////////////

VectorField &
Domain::getU()
{
  return _U;
}

////////////////////////////////////////////////////////////////////////

VectorField &
Domain::getUt()
{
  return _Ut;
}

////////////////////////////////////////////////////////////////////////

inline
void
Domain::startTime(const Scalar time)
{
  _startTime = time;
}

////////////////////////////////////////////////////////////////////////

inline
Scalar
Domain::startTime() const
{
  return _startTime;
}

////////////////////////////////////////////////////////////////////////

inline
void
Domain::endTime(const Scalar time)
{
  _numSteps = Ordinal((time - _startTime) / _timeStep);
}

////////////////////////////////////////////////////////////////////////

inline
Scalar
Domain::endTime() const
{
  return _startTime + _timeStep * _numSteps;
}

////////////////////////////////////////////////////////////////////////

inline
void
Domain::timeStep(const Scalar timeStep)
{
  _timeStep = timeStep;
}

////////////////////////////////////////////////////////////////////////

inline
Scalar
Domain::timeStep() const
{
  return _timeStep;
}

////////////////////////////////////////////////////////////////////////

inline
void
Domain::numSteps(const Ordinal numSteps)
{
  _numSteps = numSteps;
}

////////////////////////////////////////////////////////////////////////

inline
Ordinal
Domain::get_Nt() const
{
  return _numSteps;
}

////////////////////////////////////////////////////////////////////////

inline
Ordinal
Domain::get_sstep() const
{
  return _timeIntegrator->numsubstep();
}

////////////////////////////////////////////////////////////////////////

inline
void
Domain::timeOutInterval(const Ordinal interval)
{
  _timeOutInterval = interval;
}

////////////////////////////////////////////////////////////////////////

inline
Ordinal
Domain::timeOutInterval() const
{
  return _timeOutInterval;
}

////////////////////////////////////////////////////////////////////////

inline
void
Domain::fieldOutInterval(const Ordinal interval)
{
  _fieldOutInterval = interval;
}

////////////////////////////////////////////////////////////////////////

inline
Ordinal
Domain::fieldOutInterval() const
{
  return _fieldOutInterval;
}

////////////////////////////////////////////////////////////////////////

inline
Ordinal
Domain::stepNumber() const
{
  return _stepNumber;
}

////////////////////////////////////////////////////////////////////////

inline
void
Domain::stepNumber(const Ordinal stepNumber)
{
  _stepNumber = stepNumber;
}

////////////////////////////////////////////////////////////////////////

inline
Scalar
Domain::time() const
{
  return _time;
}

////////////////////////////////////////////////////////////////////////

inline
void
Domain::time(const Scalar time)
{
  _time = time;
}

////////////////////////////////////////////////////////////////////////

inline
Domain::TimeMethod
Domain::timeMethod() const
{
  return _timeMethod;
}

////////////////////////////////////////////////////////////////////////

inline
void
Domain::timeMethod(const Domain::TimeMethod timeMethod)
{
  _timeMethod = timeMethod;
}

////////////////////////////////////////////////////////////////////////

inline
Teuchos::RCP<
  DTK::TimeIntegrate< 
    FDM::Scalar,
    FDM::Ordinal,
    FDM::VectorField,
    FDM::Domain > >
Domain::timeIntegrator() const
{
  return _timeIntegrator;
}

////////////////////////////////////////////////////////////////////////

inline
void
Domain::timeIntegrator(const Teuchos::RCP<
                         DTK::TimeIntegrate<
                           FDM::Scalar,
                           FDM::Ordinal,
                           FDM::VectorField,
                           FDM::Domain > > timeIntegrator)
{
  _timeIntegrator = timeIntegrator;
}

////////////////////////////////////////////////////////////////////////

inline
void
Domain::advanceStep(const int numSteps)
{
  _stepNumber += numSteps;
}

////////////////////////////////////////////////////////////////////////

inline
bool
Domain::finished() const
{
  return (stepNumber() >= get_Nt());
}

////////////////////////////////////////////////////////////////////////

inline
void
Domain::comp_read(const std::string &fname,
                  VectorField &F,
                  const HeaderType headerType,
                  const Json::Value &traits)
{
  local_read(fname,F,headerType,
             traits["Save as single precision"].asBool());
}

////////////////////////////////////////////////////////////////////////

inline
void
Domain::comp_read(std::istream &fs,
                  VectorField &F,
                  const std::string &fname,
                  const HeaderType headerType,
                  const Json::Value &traits)
{
  local_read(fs,F,fname,headerType,
             traits["Save as single precision"].asBool());
}

////////////////////////////////////////////////////////////////////////

inline
void
Domain::comp_write(const std::string &fname,
                   const VectorField &F,
                   const Json::Value &traits) const
{
  local_write(fname,F,traits["Save as single precision"].asBool());
}

////////////////////////////////////////////////////////////////////////

inline
void
Domain::comp_write(std::ostream &fs,
                   const VectorField &F,
                   const std::string &fname,
                   const Json::Value &traits) const
{
  local_write(fs,F,fname,traits["Save as single precision"].asBool());

}

////////////////////////////////////////////////////////////////////////

}  // namespace FDM

#endif
