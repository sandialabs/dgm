#ifndef DGM_INFO_HPP
#define DGM_INFO_HPP

/** \file Info.hpp
    \brief Runtime information for DGM library and applications. */

// system includes
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <map>

// DGM includes
#include "Comm.hpp"
#include "String.hpp"

/// Convert a macro argument to a string
#define STRINGIFY(x) #x 
/// Convert a macro to a string
#define STRINGIFYMACRO(y) STRINGIFY(y)
/// Convert the value of a macro to a string
#define MACROVALUE(z) macroValue(STRINGIFYMACRO(z))
/// Add a define to the database
#define DGM_ADD_DEFINE(a) db[#a] = MACROVALUE(a)

/// Returns either a string value or "<defined>"
inline std::string macroValue(const std::string x) {
  if (x=="") return "<defined>";
  return x;
}

namespace DGM {

/// Make a self aware DGM class
/** All DGM compile-time defines should be registered here. */
class Info {
public:
  typedef std::map<string,string> dbType;
protected:
  bool verb;                   ///< verbosity level
  dbType db;                   ///< database of defines
public:
  /// Constructor
  Info() : verb(false) {}
  /// Destructor
  virtual ~Info() {}
  /// Print the code banner to an output stream
  virtual void banner(std::ostream &out) const;
  /// Print the name of the code to an output stream
  virtual void name(std::ostream &out) const;
  virtual string code() const { return "DGM"; }
  /// Get the compile data
  virtual string date() const;
  /// Get the compile time 
  virtual string time() const;
  /// Get the name of the compiler
  virtual string compiler() const;
  /// Get the name of the host currently running code 
  virtual string hostname() const;
  /// Get the name of the system currently running the code
  virtual string system() const;
  /// Get the version of DGM library
  virtual string version() const { return DGM_VERSION_STRING; }
  /// Get current working directory
  virtual string directory() const {
    char *buf=0;
    buf = getcwd(buf, 0);
    if (!buf) error("Could not get current working directory");
    string retval(buf);
    free(buf);
    return retval;
  }
  /// Print a listing the current defines to a stream
  virtual void defines(std::ostream &out) {
    using std::endl;
    if (verb) out << "DGM compile time defines for this executable: " << endl;
    //
    // Dependancies
    //
#ifdef DGM_PARALLEL
    db["DGM_PARALLEL"] = MACROVALUE(DGM_PARALLEL);
#endif
#ifdef DGM_USE_FDM
    db["DGM_USE_FDM"] = MACROVALUE(DGM_USE_FDM);
#endif
#ifdef DGM_USE_ROL
    db["DGM_USE_ROL"] = MACROVALUE(DGM_USE_ROL);
#endif
#ifdef DGM_USE_ITL
    db["DGM_USE_ITL"] = MACROVALUE(DGM_USE_ITL);
#endif
#ifdef DGM_USE_FFTW
    db["DGM_USE_FFTW"] = MACROVALUE(DGM_USE_FFTW);
#endif
#ifdef DGM_USE_TRILINOS
    db["DGM_USE_TRILINOS"] = MACROVALUE(DGM_USE_TRILINOS);
#endif
#ifdef DGM_USE_EPETRA
    db["DGM_USE_EPETRA"] = MACROVALUE(DGM_USE_EPETRA);
#endif
#ifdef DGM_USE_RYTHMOS
    db["DGM_USE_RYTHMOS"] = MACROVALUE(DGM_USE_RYTHMOS);
#endif
#ifdef DGM_USE_ZOLTAN
    db["DGM_USE_ZOLTAN"] = MACROVALUE(DGM_USE_ZOLTAN);
#endif
#ifdef DGM_USE_JSON
    db["DGM_USE_JSON"] = MACROVALUE(DGM_USE_JSON);
#endif
#ifdef DGM_USE_BOOST_FS
    db["DGM_USE_BOOST_FS"] = MACROVALUE(DGM_USE_BOOST_FS);
#endif
#ifdef DGM_USE_BOOST_RANDOM
    db["DGM_USE_BOOST_RANDOM"] = MACROVALUE(DGM_USE_BOOST_RANDOM);
#endif
#ifdef DGM_USE_BOOST_MATH
    db["DGM_USE_BOOST_MATH"] = MACROVALUE(DGM_USE_BOOST_MATH);
#endif
#ifdef DGM_USE_BOOST_DATETIME
    db["DGM_USE_BOOST_DATETIME"] = MACROVALUE(DGM_USE_BOOST_DATETIME);
#endif
#ifdef DGM_USE_BLOSC
    DGM_ADD_DEFINE(DGM_USE_BLOSC);
#endif
#ifdef DGM_RESPONSE_USE_BOOST_SERIALIZATION
    DGM_ADD_DEFINE(DGM_RESPONSE_USE_BOOST_SERIALIZATION);
#endif
#ifdef DGM_RESPONSE_USE_BLOCKING_ALLREDUCE
    DGM_ADD_DEFINE(DGM_RESPONSE_USE_BLOCKING_ALLREDUCE);
#endif
#ifdef DGM_CHECK_CONSTANT_JACOBIAN
    DGM_ADD_DEFINE(DGM_CHECK_CONSTANT_JACOBIAN);
#endif
#ifdef DGM_USE_TEUCHOS_RCP
    db["DGM_USE_TEUCHOS_RCP"] = MACROVALUE(DGM_USE_TEUCHOS_RCP);
#endif
#ifdef DGM_USE_TEUCHOS_COMM
    db["DGM_USE_TEUCHOS_COMM"] = MACROVALUE(DGM_USE_TEUCHOS_COMM);
#endif
#ifdef DGM_USE_STK_SEARCH
    db["DGM_USE_STK_SEARCH"] = MACROVALUE(DGM_USE_STK_SEARCH);
#endif
#ifdef DGM_USE_PBS_API
    db["DGM_USE_PBS_API"] = MACROVALUE(DGM_USE_PBS_API);
#endif
    //
    // Capabilities and configuration
    //
#ifdef NDEBUG
    DGM_ADD_DEFINE(NDEBUG);
#endif
#ifdef DGM_USE_TIME_REG
    DGM_ADD_DEFINE(DGM_USE_TIME_REG);
#endif
#ifdef DGM_TEST_FOR_NORMAL
    DGM_ADD_DEFINE(DGM_TEST_FOR_NORMAL);
#endif
#ifdef DGM_USE_FENV
    DGM_ADD_DEFINE(DGM_USE_FENV);
#endif
#ifdef DGM_DISABLE_DENORMS
    DGM_ADD_DEFINE(DGM_DISABLE_DENORMS);
#endif
#ifdef DGM_FIELD_TRANSFORM
    DGM_ADD_DEFINE(DGM_FIELD_TRANSFORM);
#endif
#ifdef DGM_USE_ASSEMBLER_TIMERS
    DGM_ADD_DEFINE(DGM_USE_ASSEMBLER_TIMERS;
#endif
#ifdef DGM_USE_HEX_TIMERS
    DGM_ADD_DEFINE(DGM_USE_HEX_TIMERS;
#endif
#ifdef DGM_USE_SPECTRALHEX_TIMERS
    DGM_ADD_DEFINE(DGM_USE_SPECTRALHEX_TIMERS;
#endif
#ifdef DGM_USE_BASIS_TIMERS
    DGM_ADD_DEFINE(DGM_USE_BASIS_TIMERS;
#endif
#ifdef DGM_USE_GEOM_DB
    db["DGM_USE_GEOM_DB"] = MACROVALUE(DGM_USE_GEOM_DB);
#endif
#ifdef DGM_USE_WJ
    db["DGM_USE_WJ"] = MACROVALUE(DGM_USE_WJ);
#endif
#ifdef DGM_USE_ELEMENT_BLOCKS
    db["DGM_USE_ELEMENT_BLOCKS"] = MACROVALUE(DGM_USE_ELEMENT_BLOCKS);
#endif
#ifdef DGM_USE_GRIEWANK
    db["DGM_USE_GRIEWANK"] = MACROVALUE(DGM_USE_GRIEWANK);
#endif
#ifdef DGM_USE_MPI_IREDUCE
    db["DGM_USE_MPI_IREDUCE"] = MACROVALUE(DGM_USE_MPI_IREDUCE);
#endif
#ifdef DGM_USE_GENERAL_GHOSTING
    db["DGM_USE_GENERAL_GHOSTING"] = 
      MACROVALUE(DGM_USE_GENERAL_GHOSTING);
#endif
#ifdef DGM_CONTIGUOUS
    db["DGM_CONTIGUOUS"] = MACROVALUE(DGM_CONTIGUOUS);
#endif
#ifdef DGM_NO_SYSTEM 
    db["DGM_NO_SYSTEM"] = MACROVALUE(DGM_NO_SYSTEM);
#endif
#ifdef DGM_NO_TIME 
    db["DGM_NO_TIME"] = MACROVALUE(DGM_NO_TIME);
#endif
#ifdef DGM_ALLOW_HANGING_NODES
    db["DGM_ALLOW_HANGING_NODES"] = MACROVALUE(DGM_ALLOW_HANGING_NODES);
#endif
#ifdef DGM_CLEAN_SCRATCH_PPN
    db["DGM_CLEAN_SCRATCH_PPN"] = MACROVALUE(DGM_CLEAN_SCRATCH_PPN);
#endif
#ifdef DGM_USE_SYSTEM_RM
    db["DGM_USE_SYSTEM_RM"] = MACROVALUE(DGM_USE_SYSTEM_RM);
#endif
#ifdef DGM_STATE_USE_DTK_TIMEINTEGRATE 
    DGM_ADD_DEFINE(DGM_STATE_USE_DTK_TIMEINTEGRATE);
#endif
    //
    // CMC diagnostics and capabilities 
    //
#ifdef CMC_USE_MKL
    DGM_ADD_DEFINE(CMC_USE_MKL);
#endif
#ifdef CMC_USE_TEUCHOS_LAPACK
   db["CMC_USE_TEUCHOS_LAPACK"] = MACROVALUE(CMC_USE_TEUCHOS_LAPACK);
#endif
#ifdef CMC_USE_INTERNAL_CLAPACK
   db["CMC_USE_INTERNAL_CLAPACK"] = MACROVALUE(CMC_USE_INTERNAL_CLAPACK);
#endif
#ifdef CMC_CHECK_BOUNDS
    db["CMC_CHECK_BOUNDS"] = MACROVALUE(CMC_CHECK_BOUNDS);
#endif
#ifdef CMC_CHECK_ALL_BOUNDS
    db["CMC_CHECK_ALL_BOUNDS"] = MACROVALUE(CMC_CHECK_ALL_BOUNDS);
#endif
#ifdef CMC_CHECK_INT
    db["CMC_CHECK_INT"] = MACROVALUE(CMC_CHECK_INT);
#endif
#ifdef CMC_USE_AVX
    DGM_ADD_DEFINE(CMC_USE_AVX);
#endif
#ifdef CMC_USE_KOKKOS
    DGM_ADD_DEFINE(CMC_USE_KOKKOS);
#endif
#ifdef CMC_USE_MATRIX_ROW_SLICE
    DGM_ADD_DEFINE(CMC_USE_MATRIX_ROW_SLICE);
#endif
#ifdef CMC_USE_MMIO
    DGM_ADD_DEFINE(CMC_USE_MMIO);
#endif
#ifdef CMC_USE_REF_METHOD
    DGM_ADD_DEFINE(CMC_USE_REF_METHOD);
#endif
#ifdef CMC_USE_ARRAY
    DGM_ADD_DEFINE(CMC_USE_ARRAY);
#endif
    //
    // DTK configuration
    //
#ifdef DTK_USE_TEUCHOS_RCP
    DGM_ADD_DEFINE(DTK_USE_TEUCHOS_RCP);
#endif
#ifdef DTK_ORDINAL_INT64
    DGM_ADD_DEFINE(DTK_ORDINAL_INT64);
#endif
#ifdef DTK_ORDINAL_SIZE_T
    DGM_ADD_DEFINE(DTK_ORDINAL_SIZE_T);
#endif
#ifdef DTK_ORDINAL_UINT64
    DGM_ADD_DEFINE(DTK_ORDINAL_UINT64);
#endif
#ifdef DTK_ORDINAL_UINT32
    DGM_ADD_DEFINE(DTK_ORDINAL_UINT32);
#endif
#ifdef DTK_ORDINAL_UNSIGNED_LONG_LONG
    DGM_ADD_DEFINE(DTK_ORDINAL_UNSIGNED_LONG_LONG);
#endif
#ifdef DTK_ORDINAL_LONG_LONG_UNSIGNED
    DGM_ADD_DEFINE(DTK_ORDINAL_LONG_LONG_UNSIGNED);
#endif
#ifdef DTK_ORDINAL_UNSIGNED_LONG
    DGM_ADD_DEFINE(DTK_ORDINAL_UNSIGNED_LONG);
#endif
#ifdef DTK_ORDINAL_LONG_UNSIGNED
    DGM_ADD_DEFINE(DTK_ORDINAL_LONG_UNSIGNED);
#endif

#ifdef DTK_ORDINAL_SIZE_T
    DGM_ADD_DEFINE(DTK_ORDINAL_SIZE_T);
#endif
#ifdef DTK_SIZE_UINT64
    DGM_ADD_DEFINE(DTK_SIZE_UINT64);
#endif
#ifdef DTK_SIZE_INT64
    DGM_ADD_DEFINE(DTK_SIZE_INT64);
#endif
#ifdef DTK_SIZE_SIZE_T
    DGM_ADD_DEFINE(DTK_SIZE_SIZE_T);
#endif
#ifdef DTK_SIZE_UINT32
    DGM_ADD_DEFINE(DTK_SIZE_UINT32);
#endif
#ifdef DTK_SIZE_UNSIGNED_LONG_LONG
    DGM_ADD_DEFINE(DTK_SIZE_UNSIGNED_LONG_LONG);
#endif
#ifdef DTK_SIZE_LONG_LONG_UNSIGNED
    DGM_ADD_DEFINE(DTK_SIZE_LONG_LONG_UNSIGNED);
#endif
#ifdef DTK_SIZE_UNSIGNED_LONG
    DGM_ADD_DEFINE(DTK_SIZE_UNSIGNED_LONG);
#endif
#ifdef DTK_SIZE_LONG_UNSIGNED
    DGM_ADD_DEFINE(DTK_SIZE_LONG_UNSIGNED);
#endif
/// DTK_SIZE_UNSIGNED_LONG or DTK_SIZE_LONG_UNSIGNED are defined.

    // output database to output stream
    out << "#" << endl;
    out << "# This is the configuration used for "<< code() << endl;
    out << "# version "<<version()<<" built on "<<date()<<" at "<<time()<<endl;
    out << "#" << endl;
    out << "# Based on DGM library"<<endl;
    out << "# version "<<DGM::Info::version()<<" built on "
        <<DGM::Info::date()<<" at "<<DGM::Info::time()<<endl;
    out << "#" << endl;
    for (dbType::iterator it=db.begin(); it!=db.end(); ++it)
      out << it->first << " = " << it->second << endl;
  }
  /// Print the dependances to an output stream
  void dependancies(std::ostream &out) {
  }

};

} // namespace DGM

#endif // DGM_INFO_HPP
