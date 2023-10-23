/*=============================================================================
  Title:      Discontinuous Galerkin Mesh Generator

  Author:     S. Scott Collis
              Scalable Algorithms
              Sandia National Laboratories
              Albuquerque, NM 87175-1320
              (505) 284-1123
              sscoll@sandia.gov

  Copyright:  Rice University and Sandia National Laboratories
=============================================================================*/

/** \file dgm_mesh.cpp
    \brief File containing the main program for the DGM mesh generator. */

// system libraries
#include <algorithm>
#include <array>
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
using namespace std;

// CMC libraries
#include "Stopwatch.hpp"
using CMC::Stopwatch;

// DGM libraries
#include "Comm.hpp"
#ifdef DGM_PARALLEL
#include "MpiComm.hpp"
#else
#include "SerialComm.hpp"
#endif
#include "Table.hpp"
#include "Mesh.hpp"
#include "Field.hpp"
#include "Point.hpp"
#include "Info.hpp"
#include "AsciiFileIO.hpp"
using namespace DGM;

// forward declarations

/// Manage command line inputs
void parse_args(int argc, char *argv[], Table &params );

/// Printout the correct usage
void showUsage(const string& code, bool help=false);

/// DGM rectangular mesh generator
/** Manage command line inputs, create the parallel process(es) and
    construct the DGM mesh generator. */
int main(int argc, char *argv[]) {
  int status = 0;
  try {
#ifdef DGM_PARALLEL
    DGM::Comm::World.reset( new DGM::MpiComm( &argc, &argv ) );
#else
    DGM::Comm::World.reset( new DGM::SerialComm() );
#endif
    DGM::Comm::Interupt();
    DGM::Comm::Ptr &comm(DGM::Comm::World);
    std::ostream &out(comm->cout());
    {
      DGM::Info info;
      info.name(out);
      comm->cout()<< "Started DGM Mesh Generator on " << DGM::dateTime() <<endl;
      comm->cout()<<"  Running on: "<<info.hostname()<<endl;
      comm->cout()<<"  Compiled with: "<<info.compiler()<<endl;
      comm->cout()<<"  System set to: "<<info.system()<<endl;
    }
    Stopwatch cpu;
    cpu.start();

    Table params;

    // set default values
    params["nsd"] = 1;       // number of space dimensions
    params["Lx"] = 1.0;      // domain length in x
    params["Ly"] = 1.0;      // domain length in y
    params["Lz"] = 1.0;      // domain length in z
    params["nx"] = 4;        // number of elements in x
    params["ny"] = 4;        // number of elements in y
    params["nz"] = 4;        // number of elements in z
    params["x0"] = 0.0;      // offset in x
    params["y0"] = 0.0;      // offset in y
    params["z0"] = 0.0;      // offset in z
    params["Cx"] = 0.0;      // stretch factor in x
    params["Cy"] = 0.0;      // stretch factor in y
    params["Cz"] = 0.0;      // stretch factor in z
    params["Dx"] = 0;        // stretch dirs (-1=left, 0=left&right, 1=right)
    params["Dy"] = 0;        // stretch direction in y
    params["Dz"] = 0;        // stretch direction in z
    params["phi"] = 0.0;     // rotation about z-axis
    params["theta"] = 0.0;   // rotation about y-axis
    params["root"] = "new";  // root file name for output
    params["verb"] = 0   ;   // verbosity level
    params["tecplot"] = 0;   // output a tecplot file
    params["layers"] = "";   // layers file
    params["ascii"] = 1;     // use ASCII output file
    params["binary"] = 1;    // output binary mesh file
    params["info"] = 0;      // output mesh information
    params["nodal"] = false; // use nodal elements
    params["spectral"] = false; // use spectral elements
    params["periodic"] = true;  // use periodic mesh     
    params["graph"] = true;   // output graph and weights
    params["pencils"] = false;  // vertical element numbering
    params["tri"] = 0;          // tri mesh generation is off
    params["low-memory"] = false; // low memory mesh generation is off

    parse_args( argc, argv, params );

    const int verb = params["verb"];
    const int tecplot = params["tecplot"];
    const string root = params["root"];
    const int nsd = params["nsd"];
    const int ascii = params["ascii"];
    const int binary = params["binary"];
    const int tri = params["tri"];
    const int use_info = params["info"];
    const bool nodal = params["nodal"];
    const bool spectral = params["spectral"];
    const bool periodic = params["periodic"];
    const bool graph = params["graph"];

    cout << "  Building mesh in " << nsd << " space dimensions" << endl;
    cout << "  ASCII output is ";
    if (ascii) cout << "on";
    else cout << "off";
    cout << endl;
    cout << "  Binary output is ";
    if (binary) cout << "on";
    else cout << "off";
    cout << endl;
    if ( !ascii && !binary )
      cout << "Warning, no mesh output is active...?" << endl;

    if (nodal) cout << "  Building Nodal elements" << endl;
    if (spectral) cout << "  Building Spectral elements" << endl;
    if (periodic) cout << "  Building Periodic mesh" << endl;
    if (!periodic && tri) {
      comm->cerr()<< "Etype can not be tri with non-periodic mesh" << endl;
      comm->exit(DGM::FAILURE);
    }
    if ( nodal && spectral ) {
      comm->cerr()<< "Etype can not be both Nodal and Spectral" << endl;
      comm->exit(DGM::FAILURE);
    }
    if (graph) cout << "  Will output graph and weights" << endl;

    // construct an informational string that describes the mesh
    string info;
    if (use_info) {
      ostringstream os;
      os << " "<<params;
      info = os.str();
      replace(info.begin(), info.end(), '\n',' ');
      info.erase(info.size()-1);
      replace(info.begin(), info.end(), '\t',' ');
      const string eq("  =  ");
      for (size_t b=info.find(eq);
           b != string::npos; b=info.find(eq)) info.replace(b,5,1,'=');
      for (size_t b=info.find(' ');
           b != string::npos; b=info.find(' ',b+1)) info.replace(b,1," -");
      replace(info.begin(), info.end(), '=',' ');
      info.replace(info.find("root"),4,1,'r');
      const string layers = params["layers"];
      if (layers == "") info.replace(info.find("-layers"),7,1,' ');
    }

    // add the ability to specify mesh layers
    const string layers = params["layers"];
    ifstream in(layers.c_str());
    iVector elem_depth;           // Elements per depth
    dVector depths;               // Depths in x (1D), or y (2D), or z (3D)
    vector<string> ifnames;       // Interface filenames
    bool curvedElems = false;
    if (in) {
      if (tri) {
        comm->cerr()<< "No layer support for tri elements yet." << endl;
        comm->exit(DGM::FAILURE);
      }
      int nlayers;
      if (!(in>>nlayers)) {
        comm->cerr()<< "Invalid number of layers in " << layers << endl;
        comm->exit(DGM::FAILURE);
      }
      elem_depth.resize(nlayers);
      depths.resize(nlayers);
      ifnames.resize(nlayers);
      int ed;
      double d;
      string buffer;
      getline(in,buffer);   // Finish previous line.
      for (int i=0; i<nlayers; i++){
        getline(in,buffer);
        istringstream issin(buffer);
        if (!(issin>>d>>ed)) {
          comm->cerr()<< "Error reading layer " << i << endl;
          comm->exit(DGM::FAILURE);
        }
        elem_depth[i] = ed;
        depths[i] = d;
        if (issin>>buffer) {
          ifnames[i] = buffer;
          curvedElems = true;
        } else {
          ifnames[i] = "";
        }
      }
    }
    in.close();

    DGM::Mesh mesh(params, elem_depth, depths, ifnames, nodal, spectral, 
                   periodic, verb);
    if (verb>1) comm->cout() << mesh << endl;
#ifdef DGM_TEST_MESH_IO
    mesh.write(root+".grd");
    int offset = mesh.read(root+".grd");
#endif
    const bool low_memory = params["low-memory"];
    if (low_memory && tecplot) {
      comm->cerr() << "Can't generate tecplot files in "
                      "low-memory mode" << endl;
    }
    else if (low_memory && graph) {
      comm->cout() << "  Can't generate graph and weight files in "
                     "low-memory mode."
        "\n    Mesh will be generated but not the root.grf "
        "nor root.wgt." << endl;
    }

    if (!low_memory) {
      comm->cout() << "  Building a minimal DGM::Field..." << endl;
      Field::Ptr U( new Field(1, 2, mesh, "grid", "mesh", Field::MINIMAL) );
      if (verb) comm->cout() << "    Setting side links..." << endl;
      U->set_side_links( mesh );
      if (verb) comm->cout() << "    Setting global ids..." << endl;
      U->set_global_side_id();
      if (verb) comm->cout() << "    Setting side flips..." << endl;
      U->set_flip();
      if (ascii) {
        if (verb) comm->cout() << "  Writing ASCII mesh..." << endl;
        if (use_info)
          U->write_mesh(root+".msh",info);
        else
          U->write_mesh(root+".msh");
        if (verb) comm->cout() << "  Writing ASCII connectivity..." << endl;
        U->write_connectivity(root+".con");
#ifdef DGM_TEST_MESH_IO
        mesh.write_connectivity(root+".grd",offset);
#endif
      }
      if (graph) {
        if (verb) comm->cout() << "  Writing weights..." << endl;
        U->write_weights( root+".wgt" );
        if (verb) comm->cout() << "  Writing graph..." << endl;
        U->write_graph( root+".grf" );
      }
      // make sure that connectivity is sorted
      mesh.CopyIn(U->el);
      // Warning:  use tecplot output sparingly in 3d
      if (tecplot) {
        if (verb)
          comm->cout() << "  Building storage and making tecplot file..." <<endl;
        U->make_storage();
        U->compute_geometry();
        //U->compute_side_geometry();
        U->zero();
        U->tecplot(root+".dat","mesh");
      }
    }
    else {
      if (verb) comm->cout() << "  Writing ASCII mesh..." << endl;
       if (ascii) {
         msh_file msh_f(root+".msh", mesh.nsd, mesh.ne);
         write_coordinates(mesh.point.begin(), mesh.point.end(), 
                           mesh.etype.begin(), msh_f);
         if (verb) comm->cout() << "  Writing ASCII connectivity..." << endl;
         con_file con_f(root+".con", mesh.ne);
         write_connectivity(mesh.con.begin(), mesh.con.end(), con_f);
      }
    }
    if (binary) {
#if 1
      if (verb) comm->cout() << "  Writing binary mesh file..." << endl;
      mesh.write(root+".grd",mesh.write_header(root+".grd"));
      //Json::Value header;
      //mesh.read_header(root+".grd",header);
      //cout << header << endl;
      //header.clear();
      if (verb) comm->cout() << "  Writing binary connectivity..." << endl;
      mesh.write_connectivity(root+".cn",mesh.write_header(root+".cn"));
      //mesh.read_header(root+".cn",header);
      //cout << header << endl;
#ifdef DGM_TEST_MESH_HEADER
      Json::Value header;
      mesh.read(root+".grd",mesh.read_header(root+".grd",header));
      mesh.read_connectivity(root+".cn",mesh.read_header(root+".cn",header));
#endif
#else
      if (verb) comm->cout() << "  Writing binary mesh file..." << endl;
      mesh.write(root+".grd");
      if (verb) comm->cout() << "  Writing binary connectivity..." << endl;
      mesh.write_connectivity(root+".cn");
#endif
    }
    if (curvedElems) {
      if (verb) comm->cout() << "  Creating curve file..." <<endl;
      mesh.write_curve(root+".crv");
    }
    comm->cout()<<"Total execution time: "<<cpu.stop()<<" seconds"<<endl;
  }
  catch (int x) {
    cout << DGM::Comm::World->MyPID() << ": Integer exception: " << x << endl;
    if (DGM::Comm::World->NumProc()>1) DGM::Comm::World->abort(x);
    return x;
  }
  catch (DGM::exception &e) {
    if (e.error_code!=0) {
      cout << DGM::Comm::World->MyPID() << ": DGM exception:  "
          << e.what() << endl;
      if (DGM::Comm::World->NumProc()>1) DGM::Comm::World->abort(DGM::FAILURE);
    }
    return e.error_code;
  }
  catch (std::exception &e) {
    cout << DGM::Comm::World->MyPID() << ": Standard exception: "
        << e.what() << endl;
    if (DGM::Comm::World->NumProc()>1) DGM::Comm::World->abort(DGM::FAILURE);
    return DGM::FAILURE;
  }
  catch (...) {
    cout << DGM::Comm::World->MyPID() << ": Unknown exception..." << endl;
    if (DGM::Comm::World->NumProc()>1) DGM::Comm::World->abort(DGM::FAILURE);
    return DGM::FAILURE;
  }
#ifdef OPEN_MPI
#if !((OMPI_MAJOR_VERSION <= 1) && (OMPI_MINOR_VERSION <= 8) && \
    (OMP_RELEASE_VERSION <= 4))
  comm->cout()<<"Explicitly calling World::reset()"<<endl;
  DGM::Comm::World.reset();
#endif
#endif
  return status;
}

/** Creates a parameter Table of the input arguments. */
void parse_args(int argc, char *argv[], Table &params ) {
  string name, value;
  while ( --argc && (*++argv)[0] == '-') {
    name = *argv;
    if (name == "-nx") {
      value = *(++argv);
      argc--;
      params["nx"] = atoi(value.c_str());
    } else if (name == "-ny") {
      value = *(++argv);
      argc--;
      params["ny"] = atoi(value.c_str());
    } else if (name == "-nz") {
      value = *(++argv);
      argc--;
      params["nz"] = atoi(value.c_str());
    } else if (name == "-Lx") {
      value = *(++argv);
      argc--;
      params["Lx"] = atof(value.c_str());
    } else if (name == "-Ly") {
      value = *(++argv);
      argc--;
      params["Ly"] = atof(value.c_str());
    } else if (name == "-Lz") {
      value = *(++argv);
      argc--;
      params["Lz"] = atof(value.c_str());
    } else if (name == "-x0") {
      value = *(++argv);
      argc--;
      params["x0"] = atof(value.c_str());
    } else if (name == "-y0") {
      value = *(++argv);
      argc--;
      params["y0"] = atof(value.c_str());
    } else if (name == "-z0") {
      value = *(++argv);
      argc--;
      params["z0"] = atof(value.c_str());
    } else if (name == "-Cx") {
      value = *(++argv);
      argc--;
      params["Cx"] = atof(value.c_str());
    } else if (name == "-Cy") {
      value = *(++argv);
      argc--;
      params["Cy"] = atof(value.c_str());
    } else if (name == "-Cz") {
      value = *(++argv);
      argc--;
      params["Cz"] = atof(value.c_str());
    } else if (name == "-Dx") {
      value = *(++argv);
      argc--;
      params["Dx"] = atoi(value.c_str());
    } else if (name == "-Dy") {
      value = *(++argv);
      argc--;
      params["Dy"] = atoi(value.c_str());
    } else if (name == "-Dz") {
      value = *(++argv);
      argc--;
      params["Dz"] = atoi(value.c_str());
    } else if (name == "-phi") {
      value = *(++argv);
      argc--;
      params["phi"] = atof(value.c_str());
    } else if (name == "-theta") {
      value = *(++argv);
      argc--;
      params["theta"] = atof(value.c_str());
     } else if (name == "-nsd") {
      value = *(++argv);
      argc--;
      params["nsd"] = atoi(value.c_str());
     } else if (name == "-verb") {
      value = *(++argv);
      argc--;
      params["verb"] = atoi(value.c_str());
     } else if (name == "-tecplot") {
      if (argc<2) throw DGM::exception("-tecplot requires 0/1");
      value = *(++argv);
      argc--;
      params["tecplot"] = atoi(value.c_str());
     } else if (name == "-r") {
      value = *(++argv);
      argc--;
      params["root"] = value;
     } else if (name == "-layers") {
      value = *(++argv);
      argc--;
      params["layers"] = value;
     } else if (name == "-ascii") {
      value = *(++argv);
      argc--;
      params["ascii"] = atoi(value.c_str());
     } else if (name == "-binary") {
      value = *(++argv);
      argc--;
      params["binary"] = atoi(value.c_str());
     } else if (name == "-info") {
      value = *(++argv);
      argc--;
      params["info"] = atoi(value.c_str());
    } else if (name == "-nodal") {
      params["nodal"] = true;
    } else if (name == "-spectral") {
      params["spectral"] = true;
    } else if (name == "-non-periodic") {
      params["periodic"] = false;
    } else if (name == "-nograph") {
      params["graph"] = false;
    } else if (name == "-pencils") {
      params["pencils"] = true;
    } else if (name == "-tri") {
      value = *(++argv);
      argc--;
      params["tri"] = atoi(value.c_str());
    } else if (name == "-help") {
      showUsage("dgm_mesh.exe", false);
    } else if (name == "-low-memory") {
      params["low-memory"] = true;
    } else if (name == "-help-layers") {
      showUsage("dgm_mesh.exe", true);
    } else
      showUsage("dgm_mesh.exe");
  }
}

/** If there is an error in the input argument list, this routine prints the
    correct usage information. */
void showUsage(const string& code, bool help) {
  cerr << "=================================================================\n"
       << "Usage:       \t" << code << " [Options]                          \n"
       << "=================================================================\n"
       << "Options:       " << '\t' << "Description                         \n"
       << "=================================================================\n"
       << "-nsd <int>     " << '\t' << "Number of dimensions                \n"
       << "-nx <int>      " << '\t' << "Elements in x                       \n"
       << "-ny <int>      " << '\t' << "Elements in y                       \n"
       << "-nz <int>      " << '\t' << "Elements in z                       \n"
       << "-Lx <double>   " << '\t' << "Length in x                         \n"
       << "-Ly <double>   " << '\t' << "Length in y                         \n"
       << "-Lz <double>   " << '\t' << "Length in z                         \n"
       << "-x0 <double>   " << '\t' << "x offset                            \n"
       << "-y0 <double>   " << '\t' << "y offset                            \n"
       << "-z0 <double>   " << '\t' << "z offset                            \n"
       << "-Cx <double>   " << '\t' << "Stretch in x                        \n"
       << "-Cy <double>   " << '\t' << "Stretch in y                        \n"
       << "-Cz <double>   " << '\t' << "Stretch in z                        \n"
       << "-Dx <int>      " << '\t' << "Stretch dir x [-1:2]                \n"
       << "-Dy <int>      " << '\t' << "Stretch dir y [-1:2]                \n"
       << "-Dz <int>      " << '\t' << "Stretch dir z [-1:2]                \n"
       << "-theta <double>" << '\t' << "Rotation y'-axis (deg)(3d)(CW+)     \n"
       << "-phi <double>  " << '\t' << "Rotation z-axis (deg)(2d & 3d)(CW+) \n"
       << "-verb <int>    " << '\t' << "Set verbosity level                 \n"
       << "-tecplot 0/1   " << '\t' << "Tecplot output                      \n"
       << "-layers <str>  " << '\t' << "Layers filename                     \n"
       << "-ascii 0/1     " << '\t' << "ASCII mesh output                   \n"
       << "-binary 0/1    " << '\t' << "Binary mesh output                  \n"
       << "-r <string>    " << '\t' << "Root filename                       \n"
       << "-info 0/1      " << '\t' << "Activate mesh info                  \n"
       << "-nodal         " << '\t' << "Output nodal elements               \n"
       << "-spectral      " << '\t' << "Output spectral elements            \n"
       << "-non-periodic  " << '\t' << "Output non-periodic mesh            \n"
       << "-low-memory    " << '\t' << "Output large mesh (disables generation"
                                       " of tecplot, root.wgt, and root.grf files\n"
       << "-nograph       " << '\t' << "Do not output weights and graph     \n"
       << "-pencils       " << '\t' << "Vertical element numbering          \n"
       << "-tri 1/2/3/4   " << '\t' << "1 tl-br, 2 bl-tr, 3 random, "
                                       "4 both diagonals                    \n"
       << "-help          " << '\t' << "This help message                   \n"
       << "-help-layers   " << '\t' << "Detailed help on layers             \n"
       << "=================================================================\n";
  if (help) {
    cerr << "\n\n"
       << "=================================================================\n"
       << "Help using '-layers <filename>' option                           \n"
       << "                                                                 \n"
       << "With this file, a mesh is generated which matches the described  \n"
       << "layers. The format for the file is simply an ascii file where the\n"
       << "first line is the number of interfaces, N, followed by N lines   \n"
       << "of 2 (or optional 3) columns:                                    \n"
       << "                                                                 \n"
       << " 1) the distance, D, in the layered direction (the x-direction   \n"
       << "    for 1D, the y-direction for 2D, and the z-direction for 3D), \n"
       << "    for each interface.                                          \n"
       << " 2) the number of elements, E, between this interface and the    \n"
       << "    previous interface, where the first interface would list     \n"
       << "    zero elements, and                                           \n"
       << " 3) [optionally] a filename, F, which contains distance values   \n"
       << "    for this interface, so one can prescribe the interface       \n"
       << "    shape.  This file should be ascii data of size nx+1 for      \n"
       << "    1D and (nx+1)*(ny+1) for 2D.  Elements will be uniformly     \n"
       << "    distributed between the interfaces.                          \n"
       << "                                                                 \n"
       << "Example:                                                         \n"
       << "                                                                 \n"
       << "N                                                                \n"
       << "D1  0  [optionally F1]                                           \n"
       << "D2 E2  [optionally F2]                                           \n"
       << "D3 E3  [optionally F3]                                           \n"
       << "    ...                                                          \n"
       << "DN EN  [optionally FN]                                           \n"
       << "                                                                 \n"
       << "An example for a 12-layer (13-interfaces) with a sine            \n"
       << "wave on the fourth interface is root.lyr:                        \n"
       << "                                                                 \n"
       << "<root.lyr>                                                       \n"
       << "13                                                               \n"
       << "    0.0 0                                                        \n"
       << "    18.0 1                                                       \n"
       << "    50.0 2                                                       \n"
       << "    100.0 3 sine.dat                                             \n"
       << "    200.0 6                                                      \n"
       << "    300.0 6                                                      \n"
       << "    400.0 6                                                      \n"
       << "    500.0 6                                                      \n"
       << "    600.0 6                                                      \n"
       << "    1000.0 22                                                    \n"
       << "    1200.0 11                                                    \n"
       << "    1500.0 17                                                    \n"
       << "    2000.0 27                                                    \n"
       << "<EOF>                                                            \n"
       << "                                                                 \n"
       << "This defines 12 layers with 113 elements in the depth direction. \n"
       << "The ny value should be 113 elements in order to correctly build. \n"
       << "For layer files, root.lyr, without interface files can be used   \n"
       << "for 1D, 2D and 3D runs without modification.                     \n"
       << "=================================================================\n";
  }
  throw DGM::exception("Help printed");
}
