#ifndef DGM_MPITYPE_HPP
#define DGM_MPITYPE_HPP

/** \file MpiType.hpp
    \brief MPI implementation of the DGM communicator
    \author Scott Collis
*/

#ifdef DGM_PARALLEL

// MPI includes
#include "mpi.h"
#ifndef OPEN_MPI
#include "mpio.h"
#endif

// DGM includes
#include "Config.hpp"

namespace DGM {

  /// Template function for converting standard data types to MPI_Datatype. */
  template< class T > MPI_Datatype mpiType();

} // namespace DGM

#endif

#endif  // DGM_MPITYPE_HPP
