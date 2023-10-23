//==============================================================================
//   Title:     DGM configuration
//
//   Author:    Scott Collis
//              sscoll@sandia.gov
//
//   Copyright: (c)2013 Sandia National Laboratories
//==============================================================================

#ifndef DGM_CONFIG_HPP
#define DGM_CONFIG_HPP

/** \file Config.hpp
 *  \brief File contains macro definitions and documentation
 *  \author Scott Collis
 */

//==============================================================================
//                 The following are ON by default
//==============================================================================

/// The major ersion number
#define DGM_MAJOR_VERSION 1

/// The full version number xx.yy.zz
#define DGM_MAJOR_MINOR_VERSION 010210

/// The version number as a string
#define DGM_VERSION_STRING "1.2.10 (dev)"

/// If defined the boost::random class is used
#define DGM_USE_BOOST_RANDOM 1

/// Use HWLOC library
// #define DGM_USE_HWLOC 1

/// Enable homogenous list of quad or hex elements
// #define DGM_USE_ELEMENT_BLOCKS 1

/// Provides many nice special functions 
#define DGM_USE_BOOST_MATH 1

/// Turns on the geometry database. >=2, more printout
#define DGM_USE_GEOM_DB 1

/// Turns on the computation and storage of weighted Jacobians
#define DGM_USE_WJ 1

/// Turns on Griewank I/O for state files.
#define DGM_USE_GRIEWANK 1

/// Stores Field variables in transformed space when writing to rst files
#define DGM_FIELD_TRANSFORM 1

/// Checks to see if elements are nonaffine
#define DGM_CHECK_CONSTANT_JACOBIAN 1

/// Enables logic to check and enable hanging nodes
#define DGM_ALLOW_HANGING_NODES 1

/// Use collectives rather than point to point
#define DGM_RESPONSE_USE_BLOCKING_ALLREDUCE 1

/// These are only active if Trilinos (Epetra) is active
#if defined(DGM_USE_EPETRA)
  // # define Teuchos
  // # define STK
  /// Define to use Zoltan for inline mesh partitioning
  #if defined(DGM_PARALLEL)
    #define DGM_USE_ZOLTAN 1
  #endif
#endif

/// define this to make element and edge storage contiguous in memory.
#define DGM_CONTIGUOUS

/// Checks integral arguments against the max value for int
#define CMC_CHECK_INT

/// Create ROL heirarchical parameter lists from flat parameter lists
#define DGM_USE_ROL_HEIRARCHICAL_PARAMETERS 1

/// Enable split lineasearch step
// #define DGM_USE_SPLITSTEP_LINESEARCH

//==============================================================================
//                 The following are OFF by default
//==============================================================================

// Needed to protect documentation for defines that are off by default
#ifdef DGM_DOXYGEN

  /// Turn on blocking communicaiton in Response::integrate_probes.
  /** This is the old slow method but could be used to check the result
      of the complicated non-blocking communication. */
  #define DGM_USE_RESPONSE_BLOCKING_ALLREDUCE

  /// Use this to turn on CMC::Vector/Matrix/Array bounds checking for debugging
  #define CMC_CHECK_BOUNDS

  /// This also has to be on to check ALL bounds!
  #define CMC_CHECK_ALL_BOUNDS

  /// Use this define to return to using Slices for row access
  #define CMC_USE_MATRIX_ROW_SLICE

  /// Turns on the use of MPI-3 call to do asynchronous collective communication
  #define DGM_USE_MPI_IREDUCE

  /// Activate the finite difference method FDM
  #define DGM_USE_FDM

  /// Use Json for parsing some input files
  #define DGM_USE_JSON

  /// Use the general element ghosting capability
  /** Requires: Trilinos, boost::mpi, boost::serialization. */
  #define DGM_USE_GENERAL_GHOSTING

  /// Use matrix market file IO (requires MKL)
  #define CMC_USE_MMIO

  /// CMC_USE_ARRAY This is a little faster for small matrices and vectors
  #define CMC_USE_ARRAY

  /// Use MKL for linear algebrea (deprecated)
  #define CMC_USE_MKL

  /// DGM_FIELD_VERBOSE
  /** Dump a lot of field information during field construction. */
  #define DGM_FIELD_VERBOSE

  /// Use the new parallel binary mesh reader to read just the local partition
  /** Just read the local partition of the mesh insted of each processor
      reading the whole mesh.  This should be faster for large parallel
      jobs but requires the binary mesh files needed for input to have already
      been created. See DGM_WRITE_BINARY_FILES. */
  #define DGM_PARALLEL_CONSTRUCTION
  #undef DGM_PARALLEL_CONSTRUCTION

  /// DGM_WRITE_BINARY_FILES    Read the mesh files in the standard way in
  ///                           which each process reads the whole file.
  ///                           Then dump out the files needed to read in
  ///                           using the DGM_PARALLEL_CONSTRUCTION option.
  #define DGM_WRITE_BINARY_FILES

  /// DGM_INCORE_ASYNCHRONOUS_IO (turns on asynchronous I/O for writing
  ///                            the InCore files.  It is unclear if this
  ///                            is a big savings or not, probably depends
  ///                            on the platform.
  #define DGM_INCORE_ASYNCHRONOUS_IO

  /// CMC_FLUX_INLINED_BLAS (use inline loops instead of blas)
  #define CMC_FLUX_INLINED_BLAS

  /// DGM_SIDE_FLUX__TO_SIDE (This option is for SpectralHex and SpectralQuad
  ///                        with variable p order.  In this case, interpolation
  ///                        is performed in such a way as to preserve the
  ///                        magnitude and modes of the higher-q flux when
  ///                        adding to the lower-q element.)
  #define DGM_SIDE_FLUX_TO_SIDE

  /// DGM_GROUPS (turns on the ability to split MPI communicators)
  #define DGM_GROUPS

  /// DGM_PARALLEL (turns on parallel communication)
  #define DGM_PARALLEL

  /// DGM_USE_TIME_REG (turns on time regularization term)
  #define DGM_USE_TIME_REG

  /// DGM_USE_MONITOR (monitors all output in parallel)
  #define DGM_USE_MONITOR

  /// DGM_STORE_METRICS (turns on storage of CFL metrics
  ///                    -- not fully implemented for all physics
  ///                    -- primarily used for nonlinear physics where
  ///                       CFL and timestep size are calculated every timestep)
  #define DGM_STORE_METRICS

  /// DGM_CHOLESKY_MASS_MATRIX (Use Cholesky on the symmetric mass
  ///                           matrix instead of LU)
  #define DGM_CHOLESKY_MASS_MATRIX

  /// DGM_USE_ELEMENT_BLOCKS=1 (Group Quad or Hex elements into homogenous
  ///                           lists that can be operated on as a group.
  ///                           This sometimes is not an improvement, =2 forces
  ///                           blocking even when slower.
  #define DGM_USE_ELEMENT_BLOCKS

  /// DGM_USE_MALLINFO (print summary of memory blocks used,
  ///                       requires gcc's mallinfo function)
  #define DGM_USE_MALLINFO

  /// DGM_PRE_ADD_SOURCE (Adds source before mass matrix)
  #define DGM_PRE_ADD_SOURCE

  /// DGM_SCRATCH="directory" (sets the directory to use for scratch work.
  ///                          Undefined by default.)
  /// This is read from the user's environment via getenv("DGM_SCRATCH")
  /// and therefore is a runtime variable (Just documenting it using a define!).
  #define DGM_SCRATCH

  /// DGM_NO_SCRATCH=1 (Makes sure that the scratch directory is not created
  ///                   or used.  Cray systems require this.  Undefined by
  ///                   default.)
  /// This is read from the user's environment via getenv("DGM_NO_SCRATCH")
  /// and therefore is a runtime variable (Just documenting it using a define!).
  #define DGM_NO_SCRATCH

  /// DGM_KEEP_SCRATCH=1 (Keep the scratch directory around for diagnositics.
  ///                     Undefined by default.)
  /// This is read from the user's environment via getenv("DGM_KEEP_SCRATCH")
  /// and therefore is a runtime variable (Just documenting it using a define!).
  #define DGM_KEEP_SCRATCH

  /// DGM_SAVE_SCRATCH (Do not delete scratch file created by serial
  ///                   communication in /tmp.  Can also be controled at
  ///                   runtime using the environment variable
  ///                   DGM_SAVE_SCRATCH.
  #define DGM_SAVE_SCRATCH

  /// DGM_USE_ELEMENT_SOURCE_BLOCKS (Create and save a list of quad or hex
  ///                                elements where boundary conditions are to
  ///                                be applied instead of iterating over every
  ///                                element on every time step)
  #define DGM_USE_ELEMENT_SOURCE_BLOCKS

  /// DGM_USE_MD_COUPLE (turns on multi-domain coupling)
  #define DGM_USE_MD_COUPLE
  #undef DGM_USE_MD_COUPLE

  /// DGM_USE_EPETRA (must be defined for incompressible flow solves)
  #define DGM_USE_EPETRA

  /// \name Platform specific options
  //@{
  /// DGM_REDSTORM (Easy way to turn off features not on compute nodes)
  #define DGM_REDSTORM

  /// Activate some optimizations for older Myrinet systems
  #define DGM_OPT_FOR_MYRINET
  //@}

  /// \name Options that control the use of third party libraries:
  //@{
  /// DGM_USE_EPETRA (will build in Trilinos::Epetra support)
  #define DGM_USE_EPETRA

  /// DGM_USE_RYTHMOS (will build in Trilinos::Rythmos time integration support)
  #define DGM_USE_RYTHMOS

  /// DGM_USE_ITL (use the Iterative Template Library (ITL)
  /** \note This library is only available for non-commercial use only! */
  #define DGM_USE_ITL

  /// ITL_FD_STEP_SIZE (Iterative Template Library)
  #define ITL_FD_STEP_SIZE

  /// DGM_USE_STD_VECTOR (used by Iterative Template Library)
  #define DGM_USE_STD_VECTOR

  /// DGM_USE_FFTW (parts of the code that rely on FFTW are turned on)
  /** \note General license is non-commercial only, but some systems (Cray) have
      commercial licenses as part of their general software distribution. */
  #define DGM_USE_FFTW

  /// DGM_USE_BOOST_RANDOM  (if defined the boost::random class is used)
  #define DGM_USE_BOOST_RANDOM

  /// DGM_USE_BOOST_MATH (provides many nice special functions)
  #define DGM_USE_BOOST_MATH

  /// DGM_USE_BOOST_FS (Use the boost::filesystem instead of system calls)
  #define DGM_USE_BOOST_FS

  /// DGM_USE_TEUCHOS_RCP (this replaces the boost::shared_ptr with Teuchos::RCP
  /** \note DGM requires a shared pointer type and will use
      boost::shared_ptr by default unless you specify DGM_USE_TEUCHOS_RCP
      which will instead use the Trilinos::Teuchos::RCP reference counted
      pointer which is syntax compatible (almost) with boost::shared_ptr. */
  #define DGM_USE_TEUCHOS_RCP

  /// DGM_USE_TEUCHOS_COMM (enables DGM::Comm's to generate Teuchos::Comm's)
  #define DGM_USE_TEUCHOS_COMM

  /// DGM_USE_STK_SEARCH (turns on linking in stk_search from Trilinos)
  #define DGM_USE_STK_SEARCH

  /// DGM_USE_PBS_API (Turns on the use of the PBS API)
  /** \note Watch out for license compatibility with this library. */
  #define DGM_USE_PBS_API
  //@}

  /// DGM_NODALHEX_USE_MATRIX_STORAGE
  #define DGM_NODALHEX_USE_MATRIX_STORAGE

  /// Define if the system does not support the strftime command
  #define DGM_NO_TIME

  /// PATH (the PATH from the environment).
  /** Used to find the partition weights if needed. This is read from the
      user's environment via getenv("PATH") and therefore is a runtime
      variable (Just documenting it using a define!). */
  #define PATH

  /// USER (the user id from the environment)
  /** Used to build scratch path with DGM_SCRATCH. This is read from the
      user's environment via getenv("USER") and therefore is a runtime
      variable (Just documenting it using a define!). */
  #define USER

  /// DGM_VERBOSE=1 (Set the verbosity level [0-10]).
  /** Increasing values produces increased output. This is read from the
      user's environment via getenv("DGM_VERBOSE") and therefore is a
      runtime variable (Just documenting it using a define!).

      Descriptions of DGM_VERBOSE levels
      ----------------------------------
      - 0 = DGM is basically quiet -- most output is application
      - 1 = Minimal DGM verbosity -- suitable for production use
      - 2 = More information during construction, no verbosity during execution
      - 3 = Very noisy construction and destruction, modest verbosity during
            execution
      - 4 = Noisy during execution
      - 5 = May actually dump out data, so watch out
  */
  #define DGM_VERBOSE

  /// Memory class will optionall use sysinfo instead of the proc filesystem
  /** \note Not recommended for use, availability is experimental. */
  #define DGM_LINUX_USE_SYSINFO

  /// Activate to use Boost date/time instead of system (experimental)
  #define DGM_USE_BOOST_DATETIME

  /// Activate to output debug information on mesh header
  #define DGM_MESH_DEBUG_HEADER

  /// Activate to output debug information on mesh connectivity
  #define DGM_MESH_DEBUG_CONNECTIVITY

  /// Activate to output debug information for general mesh construction
  #define DGM_MESH_DEBUG

  /// Used by the transport modules
  #define REO_CONSISTENT_SIGMA

  /// Activate debug output for the ModelEvaluator interface
  #define DGM_MODELEVAL_VERBOSE 0

  /// Activate additional Teuchos asserts for debugging
  #define DGM_TEUCHOS_DEBUG

  /// Do explicit copy as opposed to alias/view of data
  #define DGM_MODELEVAL_COPY

  /// Sets the number of processors per node for cleaning up scratch
  #define DGM_CLEAN_SCRATCH_PPN

  /// Tells DGM that this computer cannot execute the OS system calls
  #define DGM_NO_SYSTEM

  /// Activate some verbosity during MPI communication
  #define DGM_MPICOMM_VERBOSE

  /// Remove scratch files one by one
  #define DGM_MPICOMM_ONEBYONE

  /// Use the system function and /bin/rm to remove files
  #define DGM_USE_SYSTEM_RM

  /// Use C++ exceptions to abort execution (local to MpiComm and SerialComm)
  #define DGM_USE_EXCEPTIONS

  /// Use colored output to Terminal
//  #define DGM_USE_COLORED_OUTPUT

#endif

#endif
