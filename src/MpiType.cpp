/** \file MpiType.cpp
    \brief Covert standard types to MPI_Datatypes
    \author Bill Spotz and Scott Collis
*/

#ifdef DGM_PARALLEL

#include "MpiType.hpp"

namespace DGM {

// Specialized template functions for converting standard data types to
// MPI_Datatype
template<> MPI_Datatype mpiType<char          >() {return MPI_CHAR;          }
template<> MPI_Datatype mpiType<signed char   >() {return MPI_SIGNED_CHAR;   }
template<> MPI_Datatype mpiType<unsigned char >() {return MPI_UNSIGNED_CHAR; }
template<> MPI_Datatype mpiType<short         >() {return MPI_SHORT;         }
template<> MPI_Datatype mpiType<unsigned short>() {return MPI_UNSIGNED_SHORT;}
template<> MPI_Datatype mpiType<int           >() {return MPI_INT;           }
template<> MPI_Datatype mpiType<unsigned int  >() {return MPI_UNSIGNED;      }
template<> MPI_Datatype mpiType<long          >() {return MPI_LONG;          }
template<> MPI_Datatype mpiType<unsigned long >() {return MPI_UNSIGNED_LONG; }
template<> MPI_Datatype mpiType<long long     >() {return MPI_LONG_LONG;     }
template<> MPI_Datatype mpiType<unsigned long long>()
                                              {return MPI_UNSIGNED_LONG_LONG;}
template<> MPI_Datatype mpiType<float         >() {return MPI_FLOAT;         }
template<> MPI_Datatype mpiType<double        >() {return MPI_DOUBLE;        }
template<> MPI_Datatype mpiType<long double   >() {return MPI_LONG_DOUBLE;   }

}

#endif  // DGM_PARALLEL
