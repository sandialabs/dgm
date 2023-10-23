
// Configuration
#include "FDM_TestConfig.hpp"

// System includes
#include <assert.h>
#include <string>
#include <sstream>
using std::string;

// Teuchos includes
#include "Teuchos_StandardCatchMacros.hpp"
#include "Teuchos_CommandLineProcessor.hpp"
#include "Teuchos_DefaultComm.hpp"
#include "Teuchos_RCP.hpp"
#include "Teuchos_Tuple.hpp"
using Teuchos::Array;
using Teuchos::tuple;

// Local includes
#include "FDM_TestUtils.hpp"
#include "FDM_MDMap.hpp"
#include "FDM_Mesh.hpp"
#include "FDM_CartesianMesh.hpp"
using FDM_TestUtils::splitString;
using FDM_TestUtils::to_string;
using FDM_TestUtils::readable;

////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{

#ifdef ENABLE_MPI
  MPI_Init(&argc,&argv);
#endif

  bool verbose = true;
  bool success = true;

  try
  {

    Teuchos::CommandLineProcessor clp;
    clp.setDocString
      ("Mesh test code allows the user to specify the parameters\n"
       "for constructing a Mesh.\n");

    //int    test        = 0;
    string shape       = "8,8";
    string axisNumProc = "-1";
    string halos       = "0";

    //clp.setOption("test"       , &test,
    //		  "Predefined test specification");
    clp.setOption("shape"      , &shape,
    		  "Comma-separated global dimensions of MDMap");
    clp.setOption("axisNumProc", &axisNumProc,
    		  "Comma-separated number of processors along each axis");
    clp.setOption("halos"      , &halos,
    		  "Comma-separated list of halo sizes along each axis");

    Teuchos::CommandLineProcessor::EParseCommandLineReturn
      parseReturn = clp.parse(argc,argv);

    if (parseReturn == Teuchos::CommandLineProcessor::PARSE_HELP_PRINTED)
      return 0;

    if (parseReturn != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL)
      return 1;

    // Parse the command-line arguments into usable arrays
    Array< int > shapeVals;
    Array< int > axisNumProcVals;
    Array< int > haloVals;
    splitString(shape,       shapeVals      );
    splitString(axisNumProc, axisNumProcVals);
    splitString(halos,       haloVals       );

    FDM::CommPtr comm = Teuchos::DefaultComm< int >::getComm();
    bool iAmRoot = (comm->getRank() == 0);

    if (iAmRoot) std::cout << "Constructing MDMap" << std::endl;
    FDM::MDMapPtr map =
      Teuchos::rcp(new FDM::MDMap< int >(comm, shapeVals, axisNumProcVals, haloVals));
    std::cout << comm->getRank() << ": ";
    std::cout << map->description() << std::endl << std::endl;

    if (iAmRoot) std::cout << "Constructing coordinates" << std::endl;
    FDM::VectorPtr x = Teuchos::rcp(new FDM::MDVector< double, int >(map));
    FDM::VectorPtr y = Teuchos::rcp(new FDM::MDVector< double, int >(map));
    FDM::VectorPtr x1 = Teuchos::rcp(new Tpetra::Vector< double, int >(map->getAxisMap(0)));
    FDM::VectorPtr y1 = Teuchos::rcp(new Tpetra::Vector< double, int >(map->getAxisMap(1)));
    FDM::MDVectorPtr xs = Teuchos::rcp(new FDM::MDVector< double, int >(map));
    FDM::MDVectorPtr ys = Teuchos::rcp(new FDM::MDVector< double, int >(map));
    std::cout << comm->getRank() << ": ";
    std::cout << "x  = " << x->description()  << std::endl;
    std::cout << comm->getRank() << ": ";
    std::cout << "y  = " << y->description()  << std::endl;
    std::cout << comm->getRank() << ": ";
    std::cout << "x1 = " << x1->description() << std::endl;
    std::cout << comm->getRank() << ": ";
    std::cout << "y1 = " << y1->description() << std::endl;
    std::cout << comm->getRank() << ": ";
    std::cout << "xs = " << xs->description() << std::endl;
    std::cout << comm->getRank() << ": ";
    std::cout << "ys = " << ys->description() << std::endl << std::endl;

    if (iAmRoot) std::cout << "Constructing Mesh with number of dimensions" << std::endl;
    FDM::Mesh mesh1(2, map);
    std::cout << comm->getRank() << ": ";
    std::cout << mesh1.description() << std::endl << std::endl;

    if (iAmRoot) std::cout << "Constructing Mesh with coordinate names" << std::endl;
    FDM::Mesh mesh2(tuple< string >("lon","lat"), map);
    std::cout << comm->getRank() << ": ";
    std::cout << mesh2.description() << std::endl << std::endl;

    if (iAmRoot) std::cout << "Constructing Mesh with coordinates" << std::endl;
    FDM::Mesh mesh3(map, tuple(x, y));
    std::cout << comm->getRank() << ": ";
    std::cout << mesh3.description() << std::endl << std::endl;

    if (iAmRoot) std::cout << "Constructing MDMesh with MDMap" << std::endl;
    FDM::MDMesh mesh4(map);
    std::cout << comm->getRank() << ": ";
    std::cout << mesh4.description() << std::endl << std::endl;

    if (iAmRoot) std::cout << "Constructing Mesh with MDMap and coordinate names"
			   << std::endl;
    FDM::Mesh mesh5(map, tuple< string >("lon","lat"));
    std::cout << comm->getRank() << ": ";
    std::cout << mesh5.description() << std::endl << std::endl;

    if (iAmRoot) std::cout << "Constructing Mesh with coordinates" << std::endl;
    FDM::Mesh mesh6(tuple(xs, ys));
    std::cout << comm->getRank() << ": ";
    std::cout << mesh6.description() << std::endl << std::endl;

    if (iAmRoot) std::cout << "Constructing FDM::Mesh with coordinates and coordinate names"
			   << std::endl;
    FDM::Mesh mesh7(tuple(xs, ys), tuple< string >("lon","lat"));
    std::cout << comm->getRank() << ": ";
    std::cout << mesh7.description() << std::endl << std::endl;

    if (iAmRoot) std::cout << "Constructing Mesh with MDMap and 1D coordinates"
			   << std::endl;
    FDM::Mesh mesh8(map, tuple(x1, y1));
    std::cout << comm->getRank() << ": ";
    std::cout << mesh8.description() << std::endl << std::endl;

    if (iAmRoot) std::cout << "Constructing Mesh w/MDMap, 1D coordinates and names"
			   << std::endl;
    FDM::Mesh mesh9(map, tuple(x1, y1), tuple< string >("lon","lat"));
    std::cout << comm->getRank() << ": ";
    std::cout << mesh9.description() << std::endl << std::endl;

    if (iAmRoot) std::cout << "Constructing CartesianMesh with MDMap" << std::endl;
    FDM::CartesianMesh mesh10(map);
    std::cout << comm->getRank() << ": ";
    std::cout << mesh10.description() << std::endl << std::endl;

    if (iAmRoot) std::cout << "Constructing CartesianMesh with MDMap and coordinate names"
			   << std::endl;
    FDM::CartesianMesh mesh11(map, tuple< string >("lon","lat"));
    std::cout << comm->getRank() << ": ";
    std::cout << mesh11.description() << std::endl << std::endl;

    if (iAmRoot) std::cout << "Constructing CartesianMesh with MDMap and 1D coordinates"
			   << std::endl;
    FDM::CartesianMesh mesh12(map, tuple(x1, y1));
    std::cout << comm->getRank() << ": ";
    std::cout << mesh12.description() << std::endl << std::endl;

    if (iAmRoot) std::cout << "Constructing CartesianMesh w/MDMap, 1D coordinates and names"
			   << std::endl;
    FDM::CartesianMesh mesh13(map, tuple(x1, y1), tuple< string >("lon","lat"));
    std::cout << comm->getRank() << ": ";
    std::cout << mesh13.description() << std::endl << std::endl;

    //std::cout << "Test " << test << " passed on processor " << comm->getRank() << std::endl;
  }
  catch (Teuchos::CommandLineProcessor::HelpPrinted &e)
  {
    return 0;
  }
  TEUCHOS_STANDARD_CATCH_STATEMENTS(verbose,std::cerr,success);

#ifdef ENABLE_MPI
  MPI_Finalize();
#endif
}
