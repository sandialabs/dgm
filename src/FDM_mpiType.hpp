#ifndef FDM_MPITYPE_HPP
#define FDM_MPITYPE_HPP

/** \file   FDM_mpiType.hpp
    \brief  Covert standard types to MPI_Datatypes
    \author Bill Spotz
*/

#include "mpi.h"

namespace FDM
{

/** Base template function for converting standard data types to
    MPI_Datatype. */
template< class T > MPI_Datatype mpiType();

}

#endif
