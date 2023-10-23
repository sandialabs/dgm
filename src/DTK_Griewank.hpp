#ifndef DTK_GRIEWANK_HPP
#define DTK_GRIEWANK_HPP

/** \file DTK_Griewank.hpp
    \brief Template implementation of database for Griewank algorithm storage
    \author James Overfelt
    \author Scott Collis
    \author Bill Spotz
*/

// System includes
#include <map>
#include <string>
#include <sstream>
#include <limits>

// DTK includes
#include "DTK.hpp"
#include "DTK_AtomicOps.hpp"
#include "DTK_InCore.hpp"

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

/// Manages Griewank optimal checkpoint strategies
/** This class allows the Record class to, optionally, store the Record
    database to memory instead of to disk.  For small to medium sized
    problems, this should make things faster, especially for parallel
    execution where out-of-core storage to a shared disk can be very slow
    due to contention. This particular version also supports recomputing
    the State information if it is not available either in-core or on
    disk using a Griewank-type strategy.
*/
template < typename Scalar,
           typename Ordinal,
           typename VectorField,
           typename Domain >
class Griewank : public DTK::Checkpoint<Scalar,Ordinal,VectorField,Domain> {
public:
  /// Defines the type of database object used in the Griewank class
  struct KEY : public std::pair<Ordinal, Ordinal> {
      KEY() : std::pair<Ordinal,Ordinal>(){}
      KEY(const Ordinal i,const Ordinal j) :
      std::pair<Ordinal, Ordinal>(i,j){}
      Ordinal Step()    const {return this->first;}
      Ordinal SubStep() const {return this->second;}
  };
  /// Defines the type of the values held in the Griewank database
  struct VALUE : public std::pair<Ordinal, std::string> {
      VALUE() : std::pair<Ordinal,std::string>(){}
      VALUE(const Ordinal i,const std::string s) :
      std::pair<Ordinal, std::string>(i,s){}
      Ordinal     Size() const {return this->first;}
      std::string Name() const {return this->second;}
  };
  typedef KEY            Key;
  typedef VALUE          Value;
  typedef map<Key,Value> Database;

  /// There is only one constructor and no other way to create
  explicit Griewank(AtomicOps< Scalar, Ordinal > *atomic);
  ~Griewank();
  bool initialize(Domain *domain);
  void reinitialize(Domain *domain);
  void local_write(const Ordinal step,
                   const Ordinal substep,
                   const string &name,
                   VectorField &U,
                   Domain *domain);
  void local_read (const Ordinal step,
                   const Ordinal substep,
                   const string &name,
                   VectorField &U,
                   Domain *domain);
  void write_stats() const;
private:
  const Ordinal instance;             ///< Incremented for each new Instance
  Ordinal     num_snapshots;          ///< number of snapshots
  Ordinal     num_steps;              ///< number of steps
  Ordinal     num_substeps;           ///< number of substeps
  uint64_t    cur_db_size;
  uint64_t    max_db_size;
  Ordinal     restart_size;
  Ordinal     adjoint_size;
  unsigned    debug_level;            ///< Write summary of reads/writes
  unsigned    debug_iterations;       ///< Count of iterations needed
  AtomicOps< Scalar, Ordinal >*
              atomic_ops;             ///< Atomic operations interface
  Database    stored_records;         ///< List of Keys to save to InCore
  Database    saved_init;             ///< Copy of stored_records at time 0
  InCore< Scalar, Ordinal, VectorField, Domain >
              in_core_storage;        ///< In-core storage object

  void remove_states_after(const DGM::Comm::Ptr, const Ordinal);
  void iterate_to_step_from_saved(const Ordinal, Domain *);
  void local_write_information(const Ordinal,
                               const Ordinal,
                               const string &);

  void determine_steps_to_save(const DGM::Comm::Ptr comm,const Ordinal start,
      const Ordinal iterate_to = std::numeric_limits<Ordinal>::max());

  /// Do not allow default construction
  Griewank();
  /// Do not allow copy construction
  Griewank(const Griewank&);
  /// Do not allow copy construction
  Griewank operator=(const Griewank &);
};

} // namespace DTK

#endif   // DTK_GRIEWANK_HPP
