/*****************************************************************************
  Title:        Reo Finite Difference Simulator

  Author:       Bill Spotz & Scott Collis
                Sandia National Laboratories
                Albuquerque, NM 87175-1320

  Copyright:    (c)2014 Sandia National Laboratories
*****************************************************************************/

/** \file reo-fd.cpp
    \brief Main program for Reo Finite Difference.
    \author Scott Collis
    \author Bill Spotz
*/

// system libraries
#include <cstdio>
#include <fstream>

#if defined(DGM_USE_FENV) || defined(DGM_DISABLE_DENORMS)
#include <fenv.h>
#if defined(__x86_64__) && !defined(__APPLE__)
// These are needed to turn off denormals on x86 processors when not APPLE
#include <xmmintrin.h>
#include <pmmintrin.h>
#endif
#endif

// Teuchos includes
#include "Teuchos_StandardCatchMacros.hpp"
#include "Teuchos_CommandLineProcessor.hpp"
#include "Teuchos_DefaultComm.hpp"
#include "Teuchos_Tuple.hpp"
#include "Teuchos_Array.hpp"
using Teuchos::Array;

// DGM includes
#include "Comm.hpp"
#ifdef DGM_PARALLEL
#include "MpiComm.hpp"
#else
#include "SerialComm.hpp"
#endif
#include "Format.hpp"
#include "LineSearch.hpp"
#include "FDM_Types.hpp"
#include "Xpetra_MDMapFactory.hpp"

// Reoincludes
#include "ReoInfo.hpp"
#include "AdvDiff2dFD.hpp"

#if defined(DGM_USE_KOKKOS) || defined(DGM_USE_CUDA)
#include "GpGpu.hpp"
#endif

namespace FDM
{

class Eval : public DGM::Eval<FDM::Scalar>
{
  Ordinal      _npredict;
  State::Ptr   _state;
  Control::Ptr _control;
  Control::Ptr _direction;
  Control::Ptr _new_control;
public:
  Eval(Ordinal      npredict,
       State::Ptr   state,
       Control::Ptr control,
       Control::Ptr direction) :
    _npredict(npredict),
    _state(state),
    _control(control),
    _direction(direction),
    _new_control(Teuchos::rcp(_control->clone()))
  {
  }
  /** Implements the DGM::Eval interface. */
  Scalar operator()(const Scalar &a)
  {
    axpy(-a, _direction, _control, _new_control);
    _state->set_initial_condition();
    Scalar J = _state->test(_npredict, _new_control);
    return J;
  }
};

}  // namespace FDM

/// Reo Finite Difference main driver
int main(int argc, char *argv[])
{
  static DGM::Format sci(4,10,'e');
  bool success = true;

#if defined(DGM_USE_KOKKOS)
    // initialize kokkos
    DGM::GpGpu::initialize_gpu gpu;
#endif

#define REO_FD_USE_DGM_COMM_WORLD

#ifdef REO_FD_USE_DGM_COMM_WORLD
#ifdef DGM_PARALLEL
  DGM::Comm::World.reset( new DGM::MpiComm( &argc, &argv ) );
  string suffix("");
  if (DGM::Comm::World->NumProc()!=1) suffix="s";
  DGM::Comm::World->cout() << "Running Reo::FD on "
                           << DGM::Comm::World->NumProc()
                           << " processor"<<suffix<<"..." << endl;
#else
  DGM::Comm::World.reset( new DGM::SerialComm() );
#endif
  FDM::CommPtr comm = DGM::Comm::World->getTeuchosComm();
#else
#ifdef DGM_PARALLEL
  MPI_Init(&argc,&argv);
#endif
  FDM::CommPtr comm = Teuchos::DefaultComm< int >::getComm();
#endif
  int  rank    = comm->getRank();
  int  numProc = comm->getSize();
  bool iAmRoot = (rank == 0);
  Reo::Info info;
  ofstream nout("/dev/null");
  ostream & out = (iAmRoot ? cout : nout);
  info.name(out);
  out <<  "Started Reo on "  << DGM::dateTime()  << endl;
  out << "  Running on: "    << info.hostname()  << endl;
  out << "  Compiled with: " << info.compiler()  << endl;
  out << "  System set to: " << info.system()    << endl;
  out << "  Directory is: "  << info.directory() << endl;
  //
  // Flush denormals to zero if requested
  //
#if defined(DGM_USE_FENV) || defined(DGM_DISABLE_DENORMS)
  out << "  Flushing denormals to zero..." << endl;
#ifdef __APPLE__
  if (fesetenv(&_FE_DFL_DISABLE_SSE_DENORMS_ENV)) {
    out << "ERROR setting FP environment to disable subnormals" << endl;
    std::exit(EXIT_FAILURE);
  }
#elif defined(__x86_64__)
  _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
  _MM_SET_DENORMALS_ZERO_MODE(_MM_DENORMALS_ZERO_ON);
#else
  out << "WARNING: Unable to flush denormals to zero for "
    "this architecture..." << endl;
#endif
#endif

  try {
    out <<
      "===================================================================\n"
      "                             Reo::FD                               \n"
      "===================================================================  "
        << endl;

    Teuchos::CommandLineProcessor clp;
    clp.setDocString
      ("Reo Finite Difference Simulator currently solves the two-\n"
       "and three-dimensional advection-diffusion equations using a\n"
       "second-order accurate, space-time finite-difference method.\n");

    std::string input     = "root.inp";
    std::string title     = "Reo::FD run";
    int         verbosity = 0;
    int         Nx        = 100;
    int         Ny        = 100;
    int         Nz        = 1;
    int         Nt        = 1000;
    int         Ntout     = 100;
    int         Nfout     = 1000;
    int         Px        = -1;
    int         Py        = -1;
    int         Pz        = -1;
    double      dx        = 0.04;
    double      dy        = 0.04;
    double      dz        = 0.04;
    double      t0        = 0.0;
    double      dt        = 0.002;
    int         order     = 2;
    double      cx        = 1.0;
    double      cy        = 0.0;
    double      cz        = 0.0;
    int         Cx        = 1;
    int         Cy        = 1;
    int         Cz        = 0;
    int         pause     = -1;
    bool        inverse   = false;

    // setup commandline parser
    clp.setOption("input"    , &input    , "Input file"              );
    clp.setOption("verbosity", &verbosity, "Verbosity (0=none)"      );
    clp.setOption("Nx"       , &Nx       , "Number of cells in x"    );
    clp.setOption("Ny"       , &Ny       , "Number of cells in y"    );
    clp.setOption("Nz"       , &Nz       , "Number of cells in z"    );
    clp.setOption("dx"       , &dx       , "Mesh spacing in x-axis " );
    clp.setOption("dy"       , &dy       , "Mesh spacing in y-axis " );
    clp.setOption("dz"       , &dz       , "Mesh spacing in z-axis " );
    clp.setOption("Nt"       , &Nt       , "Number of time steps"    );
    clp.setOption("Ntout"    , &Ntout    , "Time output interval"    );
    clp.setOption("Nfout"    , &Nfout    , "Field output interval"   );
    clp.setOption("t0"       , &t0       , "Starting time"           );
    clp.setOption("dt"       , &dt       , "Time step"               );
    clp.setOption("Px"       , &Px       , "Processors along x-axis" );
    clp.setOption("Py"       , &Py       , "Processors along y-axis" );
    clp.setOption("Pz"       , &Pz       , "Processors along z-axis" );
    clp.setOption("order"    , &order    , "Finite-difference order" );
    clp.setOption("c_x"      , &cx       , "Convection in x-axis"    );
    clp.setOption("c_y"      , &cy       , "Convection in y-axis"    );
    clp.setOption("c_z"      , &cz       , "Convection in z-axis"    );
    clp.setOption("Cx"       , &Cx       , "Cyclic on x-axis"        );
    clp.setOption("Cy"       , &Cy       , "Cyclic on y-axis"        );
    clp.setOption("Cz"       , &Cz       , "Cyclic on z-axis"        );
    clp.setOption("pause"    , &pause    , "Pause rank for debugging");
    clp.setOption("inverse", "forward", &inverse, "Solve direction");

    Teuchos::CommandLineProcessor::EParseCommandLineReturn
      parseReturn = clp.parse(argc,argv);
    if (parseReturn == Teuchos::CommandLineProcessor::PARSE_HELP_PRINTED)
    {
      return 0;
    }
    if (parseReturn != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL)
    {
      return 1;
    }

    // Read a JSON input file
    Json::Value root;
    Json::Reader reader;
    ifstream inp(input.c_str());
    if (!inp)
    {
      out << "Reo::FD could not read \"" << input << "\"" << endl;
      return 1;
    }
    else
    {
      bool parsingSuccessful = reader.parse(inp,root,true);
      if (!parsingSuccessful)
      {
        out << "Reo::FD could not parse " << input << endl;
        out << reader.getFormattedErrorMessages();
        return 1;
      }
      //
      // General parameters
      //
      verbosity = root.set("Verbosity" , verbosity).asInt();
      input     = root.set("Input file", input    ).asString();
      title     = root.set("Title"     , title    ).asString();
      //
      // Domain parameters
      //
      Json::Value &domain = root["Domain"];
      Nx      = domain.set("Nx"     , Nx     ).asInt();
      Ny      = domain.set("Ny"     , Ny     ).asInt();
      Nz      = domain.set("Nz"     , Nz     ).asInt();
      dx      = domain.set("dx"     , dx     ).asDouble();
      dy      = domain.set("dy"     , dy     ).asDouble();
      dz      = domain.set("dz"     , dz     ).asDouble();
      order   = domain.set("order"  , order  ).asInt();
      t0      = domain.set("t0"     , t0     ).asDouble();
      dt      = domain.set("dt"     , dt     ).asDouble();
      Nt      = domain.set("Nt"     , Nt     ).asInt();
      Ntout   = domain.set("Ntout"  , Ntout  ).asInt();
      Nfout   = domain.set("Nfout"  , Nfout  ).asInt();
      Px      = domain.set("Px"     , Px     ).asInt();
      Py      = domain.set("Py"     , Py     ).asInt();
      Pz      = domain.set("Pz"     , Pz     ).asInt();
      cx      = domain.set("c_x"    , cx     ).asDouble();
      cy      = domain.set("c_y"    , cy     ).asDouble();
      cz      = domain.set("c_z"    , cz     ).asDouble();
      Cx      = domain.set("Cx"     , Cx     ).asInt();
      Cy      = domain.set("Cy"     , Cy     ).asInt();
      Cz      = domain.set("Cz"     , Cz     ).asInt();
      pause   = domain.set("pause"  , pause  ).asInt();
      inverse = domain.set("inverse", inverse).asBool();
    }

    // Re-parse the commandline options so that they over-rule inputfile
    parseReturn = clp.parse(argc,argv);

    if (parseReturn == Teuchos::CommandLineProcessor::PARSE_HELP_PRINTED)
    {
      return 0;
    }
    if (parseReturn != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL)
    {
      return 1;
    }

    // Override the JSON input given command line parameters
    root["Verbosity" ] = Json::Value(verbosity);
    root["Input file"] = Json::Value(input);
    root["Title"     ] = Json::Value(title);

    Json::Value &domain = root["Domain"];
    domain["Nx"     ] = Json::Value(Nx     );
    domain["Ny"     ] = Json::Value(Ny     );
    domain["Nz"     ] = Json::Value(Nz     );
    domain["Nt"     ] = Json::Value(Nt     );
    domain["dx"     ] = Json::Value(dx     );
    domain["dy"     ] = Json::Value(dy     );
    domain["dz"     ] = Json::Value(dz     );
    domain["order"  ] = Json::Value(order  );
    domain["t0"     ] = Json::Value(t0     );
    domain["dt"     ] = Json::Value(dt     );
    domain["Nt"     ] = Json::Value(Nt     );
    domain["Ntout"  ] = Json::Value(Ntout  );
    domain["Nfout"  ] = Json::Value(Nfout  );
    domain["Px"     ] = Json::Value(Px     );
    domain["Py"     ] = Json::Value(Py     );
    domain["Pz"     ] = Json::Value(Pz     );
    domain["c_x"    ] = Json::Value(cx     );
    domain["c_y"    ] = Json::Value(cy     );
    domain["c_z"    ] = Json::Value(cz     );
    domain["Cx"     ] = Json::Value(Cx     );
    domain["Cy"     ] = Json::Value(Cy     );
    domain["Cz"     ] = Json::Value(Cz     );
    domain["pause"  ] = Json::Value(pause  );
    domain["inverse"] = Json::Value(inverse);

    Json::StyledWriter writer;
    string output = writer.write(root);
    if (verbosity > 1)
    {
      out << "Reo::FD parsed the following input parameters:" << endl;
      out << output;
    }

    // Pause for debugging
    if (pause == rank || pause == numProc) {
      int go = 0;
      char hostname[256];
      gethostname(hostname, sizeof(hostname));
      printf("PID %d on %s ready for attach\n", getpid(), hostname);
      fflush(stdout);
      while (go == 0) sleep(5);
    }

    // Some initialization
    Teuchos::Time timer("Reo-fd Timer", true);
    Teuchos::RCP< FDM::Domain > Omega;

    // Generate the arguments for the MDComm and MDMap
    Array< int > commDims(     Teuchos::tuple(Px     , Py     , Pz     ));
    Array< int > periodicFlags(Teuchos::tuple(Cx     , Cy     , Cz     ));
    Array< int > dimensions(   Teuchos::tuple(Nx+1   , Ny+1   , Nz+1   ));
    Array< int > commPads(     Teuchos::tuple(order/2, order/2, order/2));
    Array< int > bndryPads(    Teuchos::tuple(order/2, order/2, order/2));

    // If problem is 2D, reduce the MDComm and MDMap constructor
    // arguments to 2D
    if (Nz == 1)
    {
      commDims.pop_back();
      periodicFlags.pop_back();
      dimensions.pop_back();
      commPads.pop_back();
      bndryPads.pop_back();
      if ((commDims[0] == -1) && (commDims[1] == -1)) commDims[0] = 1;
    }
    else
    {
      if ((commDims[0] == -1) && (commDims[1] == -1) && (commDims[2] == -1))
        commDims[0] = 1;
    }

    // Construct the multi-dimensional communicator
    if (verbosity > 2)
    {
      out << comm->getRank() << ": Constructing MDComm" << endl;
      out << comm->getRank() << ":   commDims = " << commDims() << endl;
      out << comm->getRank() << ":   periodicFlags = " << periodicFlags()
          << endl;
    }
    Teuchos::RCP< const Domi::MDComm > mdComm =
      Teuchos::rcp(new Domi::MDComm(comm,
                                    commDims(),
                                    periodicFlags()));

    // Construct the multi-dimensional map
    if (verbosity > 2)
    {
      out << comm->getRank() << ": Constructing MDMap" << endl;
      out << comm->getRank() << ":   dimensions = "    << dimensions() << endl;
      out << comm->getRank() << ":   commPads   = "    << commPads() << endl;
      out << comm->getRank() << ":   bndryPads  = "    << bndryPads() << endl;
    }
    // Note: Any axis that is periodic will also have replicated
    // boundary points. Therefore, we just use the periodicFlags for
    // the replicatedBoundary argument.
    FDM::MDMapPtr map =
      Teuchos::rcp(new Domi::MDMap(mdComm,
                                     dimensions(),
                                     commPads(),
                                     bndryPads(),
                                     periodicFlags()));

    // Construct the Cartesian Mesh
    if (verbosity > 2)
      out << comm->getRank() << ": Constructing CartesianMesh" << endl;
    FDM::CartesianMeshPtr mesh = Teuchos::rcp(new FDM::CartesianMesh(map));
    if (verbosity > 1)
      out << comm->getRank() << ": CartesianMesh = " << *mesh << endl;

    // The CartesianMesh constructor we chose to use allocated, but
    // did not assign, our coordinates, so we now need to fill in
    // the coordinate data

    // Set values of coordinates
    if (verbosity > 2)
      out << comm->getRank() << ": Setting coordinate values" << endl;
    mesh->setCoordinatesWithDelta(0, 0.0, dx);
    mesh->setCoordinatesWithDelta(1, 0.0, dy);
    if (Nz > 1)
    {
      mesh->setCoordinatesWithDelta(2, 0.0, dz);
    }
    if (verbosity > 2)
    {
      out << comm->getRank() << ": x = " << mesh->getCoordinates(0)
          << endl;
      out << comm->getRank() << ": y = " << mesh->getCoordinates(1)
          << endl;
      if (Nz > 1)
        out << comm->getRank() << ": z = " << mesh->getCoordinates(2)
            << endl;
    }

    /////////////////////////////////////////////////
    // T W O   D I M E N S I O N A L   S O L V E R //
    /////////////////////////////////////////////////

    if (Nz == 1)
    {
      // Forward 2D problems
      if (not inverse)
      {
        Omega = Teuchos::rcp(new Reo::AdvDiff2dFD(mesh, root));
        Omega->solve();
      }
    }
    else
    {
      out << "Only 2d is currently supported" << endl;
    }
    if (iAmRoot)
      out << "Total run time: " << sci(timer.stop()) << " sec" << endl;
  }

  TEUCHOS_STANDARD_CATCH_STATEMENTS(true, std::cerr, success);

#if defined(DGM_PARALLEL) && !defined(REO_FD_USE_DGM_COMM_WORLD)
  MPI_Finalize();
#endif

  return( success ? 0 : 1 );
}
