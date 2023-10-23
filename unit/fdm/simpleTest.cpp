
// Configuration
#include "FDM_TestConfig.hpp"

// Teuchos includes
#include "Teuchos_DefaultComm.hpp"
#include "Teuchos_Array.hpp"
#include "Teuchos_Tuple.hpp"
using Teuchos::Array;
using Teuchos::ArrayView;
using Teuchos::Tuple;

// Xpetra includes
// #include "Xpetra_MDMapFactory.hpp"

// FDM includes
#include "FDM_CartesianMesh.hpp"
#include "FDM_Field.hpp"

////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{

#ifndef SERIAL
  MPI_Init(&argc,&argv);
#endif

  // Construct the communicator
  FDM::CommPtr comm = Teuchos::DefaultComm< int >::getComm();
  int pid = comm->getRank();

  // Construct the MDComm
  FDM::MDCommPtr mdComm = Teuchos::rcp(new Domi::MDComm(comm,
                                                        Teuchos::tuple(1,-1),
                                                        Teuchos::tuple(0,0)));

  // Construct the MDMap
  FDM::MDMapPtr mdMap = Teuchos::rcp(new Domi::MDMap<>(mdComm,
                                                       Teuchos::tuple(6,6),
                                                       Teuchos::tuple(1,1),
                                                       Teuchos::tuple(2,2)));

  // Construct the mesh
  FDM::CartesianMeshPtr mesh = Teuchos::rcp(new FDM::CartesianMesh(mdMap));

  // Construct the Field
  FDM::FieldPtr field = Teuchos::rcp(new FDM::Field("f", "field", mesh));

  // Initilize with -1 everywhere
  field->putScalar(-1.0);

#ifndef SERIAL
  MPI_Finalize();
#endif

}
