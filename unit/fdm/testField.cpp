
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
#include "Teuchos_oblackholestream.hpp"
#include "Teuchos_Array.hpp"
#include "Teuchos_Tuple.hpp"
using Teuchos::Array;
using Teuchos::ArrayView;
using Teuchos::Tuple;
using Teuchos::tuple;

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

  // Initialization
  int    test            = 0;
  string filename        = "";
  string dims            = "8,8";
  string commDims        = "-1";
  string commPads        = "0";
  string bndryPads       = "";
  string periodic        = "";
  string stagger         = "0";
  string subOrigin       = "";
  string subDims         = "";
  bool   includeBndryPad = false;
  bool   verbose         = false;
  bool   success         = true;

  // Construct the communicator
  Teuchos::RCP< const Teuchos::Comm< int > > comm =
    Teuchos::DefaultComm< int >::getComm();
  int pid = comm->getRank();

  // Construct the output stream
  Teuchos::oblackholestream blackHole;
  std::ostream & out = (pid == 0) ? std::cout : blackHole;

  // Construct and initialize the command-line processor
  Teuchos::CommandLineProcessor clp;
  clp.setDocString
    ("Field test code allows the user to specify the parameters for\n"
     "constructing a Field.  The 'test' option specifies an integer ID of a\n"
     "standard suite of tests.  If 'test' is zero, then the user can specify\n"
     "the parameters for constructing a Field and receive output for what\n"
     "that Field looks like.  In this case, the 'dims', 'commDims' and\n"
     "'commPads' options should be one or more comma-separated integers.\n"
     "The number of integers specified in the 'dims' option will determine\n"
     "the dimension of the MDMap (1D, 2D, 3D, etc.).  The 'commDims' and\n"
     "'commPads' options can have fewer integers specified than the 'dims'\n"
     "option, and those unspecified values will then receive default\n"
     "values.\n");
  clp.setOption("test"       , &test,
                "Predefined test specification");
  clp.setOption("writeto"    , &filename,
                "Write the Field to the given filename.  An empty string "
                "suppresses output");
  clp.setOption("dims"         , &dims,
                "Comma-separated global dimensions of Field");
  clp.setOption("commDims"     , &commDims,
                "Comma-separated number of processors along each axis");
  clp.setOption("commPads"     , &commPads,
                "Comma-separated list of commPad sizes along each axis");
  clp.setOption("bndryPad"     , &bndryPads,
                "Comma-separated list of bndryPad points on each axis");
  clp.setOption("periodic"     , &periodic,
                "Comma-separated list of axis periodicity flags (use 0,1)");
  clp.setOption("stagger"      , &stagger,
                "Comma-separated list of stagger flags (use 0,1)");
  clp.setOption("subOrigin"    , &subOrigin,
                "Comma-separated coordinates of origin of subfield");
  clp.setOption("subDims"      , &subDims,
                "Comma-separated dimensions of subfield");
  clp.setOption("writeBndryPad", "doNotWriteBndryPad", &includeBndryPad,
                "Write (or do not write) boundary pad points to binary file");
  clp.setOption("verbose"   , "quiet"          , &verbose,
                "Verbose or quiet output");

  // Main algorithm: parse the command line and execute the Field test
  try
  {
    Teuchos::CommandLineProcessor::EParseCommandLineReturn
      parseReturn = clp.parse(argc,argv);

    out << "Command line parsed" << endl;
    out << "test = " << test << endl;

    if (parseReturn == Teuchos::CommandLineProcessor::PARSE_HELP_PRINTED)
      return 0;

    if (parseReturn != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL)
      return 1;

    // Default commPads should be at least 1,1 to ensure that there is
    // communication
    if ((test == 1) && (commPads == "0")) commPads = "1,1";

    // Parse the command-line arguments into usable arrays
    Array< FDM::Ordinal > dimVals;
    Array< FDM::Ordinal > commDimVals;
    Array< FDM::Ordinal > commPadVals;
    Array< FDM::Ordinal > bndryPadVals;
    Array< FDM::Ordinal > periodicFlags;
    Array< FDM::Ordinal > staggerFlags;
    Array< FDM::Ordinal > subOriginVals;
    Array< FDM::Ordinal > subDimVals;
    splitString(dims     , dimVals      );
    splitString(commDims , commDimVals  );
    splitString(commPads , commPadVals  );
    splitString(bndryPads, bndryPadVals );
    splitString(periodic , periodicFlags);
    splitString(stagger  , staggerFlags );
    splitString(subOrigin, subOriginVals);
    splitString(subDims  , subDimVals   );

    // Get the number of dimensions
    int numDims = dimVals.size();
    if (numDims == 3 && dimVals[2] == 1)
    {
      numDims = 2;
      dimVals.pop_back();
    }

    // Fix the commDimVals, if necessary
    while (commDimVals.size() < numDims)
      commDimVals.push_back(1);

    // Print the arrays that will be passed to the MDComm and MDMap
    // constructors
    out << "dims:      " << readable(dimVals      ) << endl;
    out << "commDims:  " << readable(commDimVals  ) << endl;
    out << "commPads:  " << readable(commPadVals  ) << endl;
    out << "bndryPads: " << readable(bndryPadVals ) << endl;
    out << "periodic:  " << readable(periodicFlags) << endl;
    out << "stagger:   " << readable(staggerFlags ) << endl;
    out << "subOrigin  " << readable(subOriginVals) << endl;
    out << "subDims    " << readable(subDimVals   ) << endl;

    ////////////////////////////////////////////////////////////////////////////
    // TEST 0: User-specified construction parameters and a printout
    // of the resulting field.
    if (test == 0)
    {
      // Construct the MDComm
      out << endl << "Constructing the MDComm" << endl;
      FDM::MDCommPtr mdComm = Teuchos::rcp(new Domi::MDComm(comm,
                                                            commDimVals(),
                                                            periodicFlags()));

      // Construct the MDMap
      out << endl << "Constructing the MDMap" << endl;
      FDM::MDMapPtr map = Teuchos::rcp(new Domi::MDMap<>(mdComm,
                                                         dimVals(),
                                                         commPadVals(),
                                                         bndryPadVals()));

      // Construct the mesh
      out << endl << "Constructing the CartesianMesh" << endl;
      FDM::CartesianMeshPtr mesh =
	Teuchos::rcp(new FDM::CartesianMesh(map));

      // Construct the Field
      out << endl << "Constructing the Field" << endl;
      FDM::FieldPtr field = Teuchos::rcp(new FDM::Field("f",
                                                        "field",
                                                        mesh,
                                                        staggerFlags()));

      // Initilize with -1 everywhere
      out << endl << "Initializing the Field with -1" << endl;
      field->putScalar(-1.0);

      // Assign each owned element the value of its global ID
      out << endl << "Assigning the Field data global IDs" << endl;
      if (numDims == 2)
      {
        // Get the looping bounds
        Domi::Slice xBounds = field->getLocalBounds(0);
        Domi::Slice yBounds = field->getLocalBounds(1);
        // Loop over the 2D domain
	for (Domi::dim_type j = yBounds.start(); j < yBounds.stop(); ++j)
	{
	  for (Domi::dim_type i = xBounds.start(); i < xBounds.stop(); ++i)
	  {
	    Domi::size_type lid = map->getLocalID(Teuchos::tuple(i,j));
	    Domi::size_type gid = map->getGlobalID(lid);
	    field->operator()(i,j) = (FDM::Scalar) gid;
	  }
	}
      }
      else  // 3D
      {
        // Get the looping bounds
        Domi::Slice xBounds = field->getLocalBounds(0);
        Domi::Slice yBounds = field->getLocalBounds(1);
        Domi::Slice zBounds = field->getLocalBounds(2);
        // Loop over the 3D domain
      	for (Domi::dim_type k = zBounds.start(); k < zBounds.stop(); ++k)
      	{
      	  for (Domi::dim_type j = yBounds.start(); j < yBounds.stop(); ++j)
      	  {
      	    for (Domi::dim_type i = xBounds.start(); i < xBounds.stop(); ++i)
      	    {
      	      Domi::size_type lid = map->getLocalID(Teuchos::tuple(i,j,k));
      	      Domi::size_type gid = map->getGlobalID(lid);
      	      field->operator()(i,j,k) = (FDM::Scalar) gid;
      	    }
      	  }
      	}
      }

      // Subfield?
      if (subOriginVals.size() > 0 && subDimVals.size() > 0)
      {
        out << endl << "Constructing the sub-Field" << endl;
        // Construct the array of slices
        Teuchos::Array< Domi::Slice > slices(numDims);
        Domi::dim_type start;
        Domi::dim_type stop;
        for (int axis = 0; axis < numDims; ++axis)
        {
          start = (axis < subOriginVals.size()) ? subOriginVals[axis] : 0;
          stop  = (axis < subDimVals.size())  ? subDimVals[axis] :
            field->getGlobalDim(axis);
          slices[axis] = Domi::Slice(start, stop);
        }
        // Construct the subfield
        FDM::FieldPtr subfield =
          Teuchos::rcp(new FDM::Field("s",
                                      "subfield",
                                      *field,
                                      slices()));

        out << endl << "Writing the sub-Field" << endl;
        // Print the subfield
        out << endl << pid << ": " << subfield->description() << endl;
        // Write the subfield to a file
        if (filename.length() > 0)
          subfield->writeBinary(filename, includeBndryPad);
      }
      else
      {
        out << endl << "Writing the Field" << endl;
        // Print the Field
        out << endl << pid << ": " << field->description() << endl;
        // Write the Field to a file
        if (filename.length() > 0)
          field->writeBinary(filename, includeBndryPad);
      }
    }

    ////////////////////////////////////////////////////////////////////////////
    // TEST 1: Build a Field with size, processor
    //         decomposition, boundary pads and communication pads
    //         specified by the user.  Initialize such that owned
    //         points are assigned their global ID, and communication
    //         and and boundary pad regions are assigned -1.  Perform
    //         an updateCommPad() and check that the owned points and
    //         boundary pad points are unchanged and that
    //         communication pad points are updated with the
    //         corresponding global ID.
    if (test == 1)
    {
      // Check for 2D or 3D
      if (numDims < 2 || numDims > 3)
      {
        out << "TEST 1 must be 2D or 3D." << endl;
#ifndef SERIAL
        MPI_Finalize();
#endif
        return 1;
      }

      // Construct the MDComm
      out << endl << "Constructing MDComm" << endl;
      FDM::MDCommPtr mdComm = Teuchos::rcp(new Domi::MDComm(comm,
                                                            commDimVals(),
                                                            periodicFlags()));

      // Construct the MDMap
      out << endl << "Constructing MDMap" << endl;
      FDM::MDMapPtr map = Teuchos::rcp(new Domi::MDMap<>(mdComm,
                                                         dimVals(),
                                                         commPadVals(),
                                                         bndryPadVals()));

      // Construct the mesh
      out << endl << "Constructing CartesianMesh" << endl;
      FDM::CartesianMeshPtr mesh =
	Teuchos::rcp(new FDM::CartesianMesh(map));

      // Construct the Field
      out << endl << "Constructing Field" << endl;
      FDM::FieldPtr fieldPtr =
        Teuchos::rcp(new FDM::Field("f",
                                    "field",
                                    mesh,
                                    staggerFlags()));
      FDM::Field & field = *fieldPtr;

      //////////////////////////////////////////////////////////////////
      //
      // Phase I
      // -------
      // Initilize with -1 everywhere
      //
      //////////////////////////////////////////////////////////////////
      field.putScalar(-1.0);

      //////////////////////////////////////////////////////////////////
      //
      // Phase II
      // --------
      // Assign each owned element the value of its global ID
      //
      //////////////////////////////////////////////////////////////////
      if (numDims == 2)
      {
        // Get the looping bounds
        Domi::Slice xBounds = field.getLocalBounds(0);
        Domi::Slice yBounds = field.getLocalBounds(1);
        // Loop over the 2D domain
	for (Domi::dim_type j = yBounds.start(); j < yBounds.stop(); ++j)
	{
	  for (Domi::dim_type i = xBounds.start(); i < xBounds.stop(); ++i)
	  {
	    Domi::size_type lid = map->getLocalID(Teuchos::tuple(i,j));
	    Domi::size_type gid = map->getGlobalID(lid);
	    field(i,j) = (FDM::Scalar) gid;
	  }
	}
        out << endl << "Field initialized" << endl;
      }
      else  // 3D
      {
        // Get the looping bounds
        Domi::Slice xBounds = field.getLocalBounds(0);
        Domi::Slice yBounds = field.getLocalBounds(1);
        Domi::Slice zBounds = field.getLocalBounds(2);
        // Loop over the 3D domain
      	for (Domi::dim_type k = zBounds.start(); k < zBounds.stop(); ++k)
      	{
      	  for (Domi::dim_type j = yBounds.start(); j < yBounds.stop(); ++j)
      	  {
      	    for (Domi::dim_type i = xBounds.start(); i < xBounds.stop(); ++i)
      	    {
      	      Domi::size_type lid = map->getLocalID(Teuchos::tuple(i,j,k));
      	      Domi::size_type gid = map->getGlobalID(lid);
      	      field(i,j,k) = (FDM::Scalar) gid;
      	    }
      	  }
      	}
      }

      //////////////////////////////////////////////////////////////////
      //
      // Phase III
      // ---------
      // Check that the Field has the expected pre-communication
      // values
      //
      //////////////////////////////////////////////////////////////////
      if (numDims == 2)
      {
        // Get the looping bounds
        Domi::Slice xBounds = field.getLocalBounds(0,true);
        Domi::Slice yBounds = field.getLocalBounds(1,true);

	for (Domi::dim_type j = yBounds.start(); j < yBounds.stop(); ++j)
	{
	  for (Domi::dim_type i = xBounds.start(); i < xBounds.stop(); ++i)
	  {
            Teuchos::ArrayView< Domi::dim_type > index = Teuchos::tuple(i,j);
	    Domi::size_type lid = map->getLocalID(index);
	    Domi::size_type gid = map->getGlobalID(lid);
            if (field.isPad(index)) gid = -1;
	    if (verbose)
	      cout << pid << ": field(" << i << "," << j << ") = "
                   << field(i,j) << " (should be " << gid << ")"
                   << endl;
	    assert(field(i,j) == gid);
	  }
	}
      }
      else
      {
        // Get the looping bounds
        Domi::Slice xBounds = field.getLocalBounds(0,true);
        Domi::Slice yBounds = field.getLocalBounds(1,true);
        Domi::Slice zBounds = field.getLocalBounds(2,true);

	for (Domi::dim_type k = zBounds.start(); k < zBounds.stop(); ++k)
	{
          for (Domi::dim_type j = yBounds.start(); j < yBounds.stop(); ++j)
          {
            for (Domi::dim_type i = xBounds.start(); i < xBounds.stop(); ++i)
            {
              Teuchos::ArrayView< Domi::dim_type > index =
                Teuchos::tuple(i,j,k);
              Domi::size_type lid = map->getLocalID(index);
              Domi::size_type gid = map->getGlobalID(lid);
              if (field.isPad(index)) gid = -1;
              if (verbose)
                cout << pid << ": field(" << i << "," << j << "," << k << ") = "
                     << field(i,j,k) << " (should be " << gid << ")"
                     << endl;
              assert(field(i,j,k) == gid);
            }
          }
        }
      }

      //////////////////////////////////////////////////////////////////
      //
      // Phase IV
      // --------
      // Update the communication pad values.  After returning from
      // this method, communication pad points corresponding to
      // communication buffers should now have values that correspond
      // to their global IDs.  Communication pad points corresponding
      // to boundary pad points should still be equal to -1.
      //
      //////////////////////////////////////////////////////////////////
      field.updateCommPad();
      out << endl << "CommPads updated" << endl;

      //////////////////////////////////////////////////////////////////
      //
      // Phase V
      // -------
      // Check that the Field has the expected post-communication
      // values
      //
      //////////////////////////////////////////////////////////////////
      if (numDims == 2)
      {
        // Get the looping bounds
        Domi::Slice xBounds = field.getLocalBounds(0,true);
        Domi::Slice yBounds = field.getLocalBounds(1,true);

	for (Domi::dim_type j = yBounds.start(); j < yBounds.stop(); ++j)
	{
	  for (Domi::dim_type i = xBounds.start(); i < xBounds.stop(); ++i)
	  {
            Teuchos::ArrayView< Domi::dim_type > index = Teuchos::tuple(i,j);
	    Domi::size_type lid = map->getLocalID(index);
	    Domi::size_type gid = map->getGlobalID(lid);
            if (field.isBndryPad(index)) gid = -1;
	    if (verbose)
	      cout << pid << ": field(" << i << "," << j << ") = "
                   << field(i,j) << " (should be " << gid << ")"
                   << endl;
	    assert(field(i,j) == gid);
	  }
	}
      }
      else
      {
        // Get the looping bounds
        Domi::Slice xBounds = field.getLocalBounds(0,true);
        Domi::Slice yBounds = field.getLocalBounds(1,true);
        Domi::Slice zBounds = field.getLocalBounds(2,true);

	for (Domi::dim_type k = zBounds.start(); k < zBounds.stop(); ++k)
	{
          for (Domi::dim_type j = yBounds.start(); j < yBounds.stop(); ++j)
          {
            for (Domi::dim_type i = xBounds.start(); i < xBounds.stop(); ++i)
            {
              Teuchos::ArrayView< Domi::dim_type > index =
                Teuchos::tuple(i,j,k);
              Domi::size_type lid = map->getLocalID(index);
              Domi::size_type gid = map->getGlobalID(lid);
              if (field.isBndryPad(index)) gid = -1;
              if (verbose)
                cout << pid << ": field(" << i << "," << j << "," << k << ") = "
                     << field(i,j,k) << " (should be " << gid << ")"
                     << endl;
              assert(field(i,j,k) == gid);
            }
          }
        }
      }

    }
    out << endl;
    comm->barrier();
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
