
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
#include "Teuchos_Array.hpp"
#include "Teuchos_Tuple.hpp"
using Teuchos::Array;
using Teuchos::ArrayView;
using Teuchos::Tuple;
using Teuchos::tuple;

// Domi includes
#include "Domi_MDComm.hpp"
#include "Domi_MDMap.hpp"
#include "Domi_MDVector.hpp"

// FDM includes
#include "FDM_CartesianMesh.hpp"
#include "FDM_Field.hpp"

// Local includes
#include "FDM_TestUtils.hpp"
using FDM_TestUtils::splitString;
using FDM_TestUtils::to_string;
using FDM_TestUtils::readable;

////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{

#ifndef SERIAL
  MPI_Init(&argc,&argv);
#endif

  bool success = true;
  try
  {

    Teuchos::CommandLineProcessor clp;
    clp.setDocString
      ("VectorField test code allows the user to specify the parameters for\n"
       "constructing a VectorField.  The 'test' option specifies an integer ID\n"
       "of a standard suite of tests.  If 'test' is zero, then the user can\n"
       "specify the parameters for constructing a Field and receive output\n"
       "for what that VectorField looks like.  In this case, the 'shape',\n"
       "'axisNumProc' and 'commPads' options should be one or more comma-\n"
       "separated integers.  The number of integers specified in the 'shape'\n"
       "option will determine the dimension of the MDMap (1D, 2D, 3D, etc.).\n"
       "The 'axisNumProc' and 'commPads' options can have fewer integers\n"
       "specified than the 'shape' option, and those unspecified values will\n"
       "then receive default values.\n");

    int    test            = 0;
    int    numField        = 3;
    string filename        = "";
    string shape           = "8,8";
    string axisNumProc     = "-1";
    string commPads        = "0";
    string bndryPad        = "";
    string periodic        = "";
    string subOrigin       = "";
    string subShape        = "";
    bool   includeBndryPad = false;
    bool   verbose      = false;

    clp.setOption("test"       , &test,
		  "Predefined test specification");
    clp.setOption("numField"   , &numField,
		  "Number of Fields in VectorField");
    clp.setOption("writeto"    , &filename,
                  "Write the Field to the given filename.  An empty\n"
                  "                                 "
                  "string suppresses output");
    clp.setOption("shape"        , &shape,
		  "Comma-separated global dimensions of Field");
    clp.setOption("axisNumProc"  , &axisNumProc,
		  "Comma-separated number of processors along each axis");
    clp.setOption("commPads"     , &commPads,
		  "Comma-separated list of commPad sizes along each axis");
    clp.setOption("bndryPad"     , &bndryPad,
		  "Comma-separated list of bndryPad points on each axis");
    clp.setOption("periodic"     , &periodic,
		  "Comma-separated list of axis periodicity flags (use 0,1)");
    clp.setOption("subOrigin"    , &subOrigin,
                  "Comma-separated coordinates of origin of subfield");
    clp.setOption("subShape"     , &subShape,
                  "Comma-separated dimensions of shape of subfield");
    clp.setOption("writeBndryPad", "doNotWriteBndryPad", &includeBndryPad,
                  "Write (or do not write) bndryPad points to the binary file");
    clp.setOption("verbose"   , "quiet"          , &verbose,
		  "Verbose or quiet output");

    Teuchos::CommandLineProcessor::EParseCommandLineReturn
      parseReturn = clp.parse(argc,argv);

    cout << "Command line parsed" << endl;
    cout << "test = " << test << endl;

    if (parseReturn == Teuchos::CommandLineProcessor::PARSE_HELP_PRINTED)
      return 0;

    if (parseReturn != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL)
      return 1;

    // Construct the communicator
    Teuchos::RCP< const Teuchos::Comm< int > > comm =
      Teuchos::DefaultComm< int >::getComm();
    int pid = comm->getRank();

    ////////////////////////////////////////////////////////////////////////////
    // TEST 0: User-specified construction parameters and a printout
    // of the resulting field.
    if (test == 0)
    {
      // Parse the command-line arguments into usable arrays
      Array< FDM::Ordinal > shapeVals;
      Array< FDM::Ordinal > axisNumProcVals;
      Array< FDM::Ordinal > commPadVals;
      Array< FDM::Ordinal > bndryPadVals;
      Array< FDM::Ordinal > periodicFlags;
      Array< FDM::Ordinal > subOriginVals;
      Array< FDM::Ordinal > subShapeVals;
      splitString(shape,       shapeVals      );
      splitString(axisNumProc, axisNumProcVals);
      splitString(commPads,    commPadVals    );
      splitString(bndryPad,    bndryPadVals   );
      splitString(periodic,    periodicFlags  );
      splitString(subOrigin,   subOriginVals  );
      splitString(subShape,    subShapeVals   );

      int numDims = shapeVals.size();

      // Print the arrays that will be passed to the MDMap constructor
      if (pid == 0)
      {
	cout << "shape:       " << readable(shapeVals      ) << endl;
	cout << "axisNumProc: " << readable(axisNumProcVals) << endl;
	cout << "commPads:    " << readable(commPadVals    ) << endl;
	cout << "bndryPad:    " << readable(bndryPadVals   ) << endl;
	cout << "periodic:    " << readable(periodicFlags  ) << endl;
        cout << "subOrigin    " << readable(subOriginVals  ) << endl;
        cout << "subShape     " << readable(subShapeVals   ) << endl;
      }

      // Construct the MDComm
      Teuchos::RCP< const Domi::MDComm > mdComm =
        Teuchos::rcp(new Domi::MDComm(comm,
                                      axisNumProcVals(),
                                      periodicFlags()));

      // Construct the MDMap
      FDM::MDMapPtr map =
        Teuchos::rcp(new Domi::MDMap<>(mdComm,
                                       shapeVals(),
                                       commPadVals(),
                                       bndryPadVals()));

      // Construct the mesh
      FDM::CartesianMeshPtr mesh =
	Teuchos::rcp(new FDM::CartesianMesh(map));

      // Construct the Field
      FDM::FieldPtr field = Teuchos::rcp(new FDM::Field("f",
                                                        "field",
                                                        mesh));
      FDM::Field & f = *field;

      // Initilize with -1 everywhere
      f.putScalar(-1.0);

      // Assign each owned element the value of its global ID
      if (numDims == 2)
      {
        Domi::Slice xBounds = f.getLocalBounds(0);
        Domi::Slice yBounds = f.getLocalBounds(1);
	for (Domi::dim_type j = yBounds.start(); j < yBounds.stop(); ++j)
	{
	  for (Domi::dim_type i = xBounds.start(); i < xBounds.stop(); ++i)
	  {
	    FDM::Ordinal lid = map->getLocalID(Teuchos::tuple(i,j));
	    FDM::Ordinal gid = map->getGlobalID(lid);
	    f(i,j) = (FDM::Scalar) gid;
	  }
	}
      }
      else  // 3D
      {
        Domi::Slice xBounds = f.getLocalBounds(0);
        Domi::Slice yBounds = f.getLocalBounds(1);
        Domi::Slice zBounds = f.getLocalBounds(2);
	for (Domi::dim_type k = zBounds.start(); k < zBounds.stop(); ++k)
	{
          for (Domi::dim_type j = yBounds.start(); j < yBounds.stop(); ++j)
          {
            for (Domi::dim_type i = xBounds.start(); i < xBounds.stop(); ++i)
            {
              FDM::Ordinal lid = map->getLocalID(Teuchos::tuple(i,j));
              FDM::Ordinal gid = map->getGlobalID(lid);
              f(i,j) = (FDM::Scalar) gid;
            }
	  }
	}
      }

      // Subfield?
      if (subOriginVals.size() > 0 && subShapeVals.size() > 0)
      {
        // Construct the array of Slices
        Teuchos::Array< Domi::Slice > slices(numDims);
        for (int axis = 0; axis < numDims; ++axis)
        {
          Domi::dim_type start =
            axis < subOriginVals.size() ? subOriginVals[axis] : 0;
          Domi::dim_type stop  =
            axis < subShapeVals.size() ? subShapeVals[axis] : 1;
          slices[axis] = Domi::Slice(start, stop);
        }
        
        // Construct the subfield
        FDM::FieldPtr subfield =
          Teuchos::rcp(new FDM::Field("s",
                                      "subfield",
                                      f,
                                      slices()));
        FDM::Field & s = *subfield;
        // Print the subfield
        cout << endl << pid << ": " << s.description() << endl;
        // Write the subfield to a file
        if (filename.length() > 0)
          s.writeBinary(filename, includeBndryPad);
      }
      else
      {
        // Print the Field
        cout << endl << pid << ": " << f.description() << endl;
        // Write the Field to a file
        if (filename.length() > 0)
          f.writeBinary(filename, includeBndryPad);
      }
    }

    ////////////////////////////////////////////////////////////////////////////
    // TEST 1: Build a Field with size, processor
    //         decomposition, bndryPad points and commPads specified by the
    //         user.  Initialize such that owned points are assigned
    //         their global ID, and commPad and bndryPad regions are
    //         assigned -1.  Perform an updateCommPads() and check that
    //         the owned points and bndryPad points are unchanged and
    //         that commPad points are updated with the corresponding
    //         global ID.
    if (test == 1)
    {
      // Default commPads should be at least 1,1 to ensure that there
      // is communication
      if (commPads == "0") commPads = "1,1";

      // Parse the command-line arguments into usable arrays
      Array< FDM::Ordinal > shapeVals;
      Array< FDM::Ordinal > axisNumProcVals;
      Array< FDM::Ordinal > commPadVals;
      Array< FDM::Ordinal > bndryPadVals;
      Array< FDM::Ordinal > periodicFlags;
      splitString(shape,       shapeVals      );
      splitString(axisNumProc, axisNumProcVals);
      splitString(commPads,    commPadVals    );
      splitString(bndryPad,    bndryPadVals   );
      splitString(periodic,    periodicFlags  );

      // Check for 2D or 3D
      int numDims = shapeVals.size();
      if (numDims == 3 && shapeVals[2] == 1)
      {
	numDims = 2;
	shapeVals.pop_back();
      }
      if (numDims < 2 || numDims > 3)
      {
	if (pid == 0)
          cout << "TEST 1 must be 2D or 3D." << endl;
#ifndef SERIAL
        MPI_Finalize();
#endif
        return 1;
      }

      // Construct the MDComm
      cout << "constructing map" << endl;
      cout << "axisNumProcVals = " << axisNumProcVals() << endl;
      Teuchos::RCP< const Domi::MDComm > mdComm =
        Teuchos::rcp(new Domi::MDComm(comm,
                                      axisNumProcVals(),
                                      periodicFlags()));

      // Construct the MDMap
      cout << "constructing map" << endl;
      cout << "shapeVals = " << shapeVals() << endl;
      FDM::MDMapPtr map =
        Teuchos::rcp(new Domi::MDMap<>(mdComm,
                                       shapeVals(),
                                       commPadVals(),
                                       bndryPadVals()));

      // Construct the mesh
      cout << "constructing mesh" << endl;
      FDM::CartesianMeshPtr mesh =
	Teuchos::rcp(new FDM::CartesianMesh(map));

      // Construct the Field
      cout << "constructing field" << endl;
      FDM::FieldPtr field =
	Teuchos::rcp(new FDM::Field("f",
                                    "field",
                                    mesh));
      FDM::Field & f = *field;

      // Initilize with -1 everywhere
      f.putScalar(-1.0);

      // Assign each owned element the value of its global ID
      if (numDims == 2)
      {
        Domi::Slice xBounds = f.getLocalBounds(0);
        Domi::Slice yBounds = f.getLocalBounds(1);

	for (Domi::dim_type j = yBounds.start(); j < yBounds.stop(); ++j)
	{
	  for (Domi::dim_type i = xBounds.start(); i < xBounds.stop(); ++i)
	  {
	    FDM::Ordinal lid = map->getLocalID(Teuchos::tuple(i,j));
	    FDM::Ordinal gid = map->getGlobalID(lid);
	    f(i,j) = (FDM::Scalar) gid;
	  }
	}
      cout << "field initialized" << endl;
      }
      else  // 3D
      {
        Domi::Slice xBounds = f.getLocalBounds(0);
        Domi::Slice yBounds = f.getLocalBounds(1);
        Domi::Slice zBounds = f.getLocalBounds(2);

	for (Domi::dim_type k = zBounds.start(); k < zBounds.stop(); ++k)
	{
          for (Domi::dim_type j = yBounds.start(); j < yBounds.stop(); ++j)
          {
            for (Domi::dim_type i = xBounds.start(); i < xBounds.stop(); ++i)
      	    {
      	      FDM::Ordinal lid = map->getLocalID(Teuchos::tuple(i,j,k));
      	      FDM::Ordinal gid = map->getGlobalID(lid);
      	      f(i,j,k) = (FDM::Scalar) gid;
      	    }
      	  }
      	}
      }

      // Update the commPad values.  After returning from this method,
      // commPad points corresponding to communication buffers should now
      // have values that correspond to their global IDs.  CommPad points
      // corresponding to bndryPad points should still be equal to -1.
      f.updateCommPad();
      cout << "CommPads updated" << endl;

      // Check the Field values
      if (numDims == 2)
      {
        Domi::dim_type i0 = f.getGlobalRankBounds(0).start();
        Domi::dim_type j0 = f.getGlobalRankBounds(1).start();
        Domi::Slice xBounds = f.getLocalBounds(0);
        Domi::Slice yBounds = f.getLocalBounds(1);

	// Check Field values
	for (int j = yBounds.start(); j < yBounds.stop(); ++j)
	{
	  for (int i = xBounds.start(); i < xBounds.stop(); ++i)
	  {
	    FDM::Ordinal lid = map->getLocalID(Teuchos::tuple(i,j));
	    FDM::Ordinal gid = map->getGlobalID(lid);
            if (f.isBndryPad(Teuchos::tuple(i+i0,j+j0))) gid = -1;
	    if (verbose)
	      cout << pid << ": field(" << i << "," << j << ") = "
                   << f(i,j) << " (should be " << gid << ")"
                   << endl;
	    assert(f(i,j) == gid);
	  }
	}
      }
      else
      {
        Domi::dim_type i0 = f.getGlobalRankBounds(0).start();
        Domi::dim_type j0 = f.getGlobalRankBounds(1).start();
        Domi::dim_type k0 = f.getGlobalRankBounds(2).start();
        Domi::Slice xBounds = f.getLocalBounds(0);
        Domi::Slice yBounds = f.getLocalBounds(1);
        Domi::Slice zBounds = f.getLocalBounds(2);

	// Check Field values
	for (int k = zBounds.start(); k < zBounds.stop(); ++k)
	{
          for (int j = yBounds.start(); j < yBounds.stop(); ++j)
          {
            for (int i = xBounds.start(); i < xBounds.stop(); ++i)
            {
              FDM::Ordinal lid = map->getLocalID(Teuchos::tuple(i,j,k));
              FDM::Ordinal gid = map->getGlobalID(lid);
              if (f.isBndryPad(Teuchos::tuple(i+i0,j+j0,k+k0))) gid = -1;
              if (verbose)
                cout << pid << ": field(" << i << "," << j << "," << k << ") = "
                     << f(i,j,k) << " (should be " << gid << ")"
                     << endl;
              assert(f(i,j,k) == gid);
            }
          }
	}
      }
    }
    cout << "Test " << test << " passed on processor " << pid << endl;
  }
  catch (Teuchos::CommandLineProcessor::HelpPrinted &e)
  {
    return 0;
  }
  TEUCHOS_STANDARD_CATCH_STATEMENTS(true,std::cerr,success);

#ifndef SERIAL
  MPI_Finalize();
#endif

}
