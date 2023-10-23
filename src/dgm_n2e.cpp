/*=============================================================================
  Title:      Discontinuous Galerkin Nodal-to-Element Converter

  Author:     S. Scott Collis
              Sandia National Laboratories
              Albuquerque, NM 87175
              (505) 284-1123
              sscoll@sandia.gov

  Copyright:  (c)2003 Rice University
              (c)2010 Sandia National Laboratories
=============================================================================*/

//=============================================================================
//  g++ n_to_e.cpp -o n_to_e
//=============================================================================
//
//   Purpose:
//      This is a utility for DGM to translate nodal connectivity
//   data files that are the typical produced by unstructured mesh
//   generation programs into edge connectivity that is utilized by
//   DGM.
//
//   This only works for 2-d
//   - Works for arbitrary number of nodes on each element
//   - Assumes counter clockwise connectivity
//   - Reads in nodal coordinates form a file named "xyz.asc"
//   - Reads in from a connectivity file named "ien.asc"
//
//   Author:  Zach Smith
//   Date:    10/23/01
//
//   edited:  11/13/01
//   changed: Cleaned up previous version, allowed for arbitrary number
//            of edges on each element
//
//   edited:  Scott Collis, 02/21/02
//   changes: Fixed for triangles, removed hard limit on number of nodes,
//            Formated for consistency
//
//   edited:  Scott Collis, 02/27/02
//   changes: Changed the input file names for consistency
//
//   edited:  Scott Collis, 03/21/02
//   changes: Fixed for different element types
//
//   edited:  Scott Collis, 05/28/02
//   changes: Updated for 3D (Hex)
//
//   edited:  George Hagstrom, 8/22/05
//   changes: Added command-line switch to accept input from Cubit
//
//   edited:  Guoquan Chen 06/15/06
//   change:  Updated for Gambit NEU file format (ASCII)
//
//============================================================================

/** \file dgm_n2e.cpp
    \brief File containing DGM N2E:  Nodal-to-Element connectivitiy utility. */

// system includes
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <list>
using namespace std;

// DGM includes
#include "Comm.hpp"
#ifdef DGM_PARALLEL
#include "MpiComm.hpp"
#else
#include "SerialComm.hpp"
#endif
#include "Types.hpp"
#include "Table.hpp"
#include "Mesh.hpp"
#include "Field.hpp"
#include "Topology.hpp"

// local defines

/// Enables the generation of boundary conditions
#define N2E_MAKE_BC

/// Enables the specification of periodicity
#define N2E_PERIODIC

/// Flag to generate the dual graph for hybrid mesh/multimodel partition
#define N2E_DGRAPH

// Turns on debug statements
#undef N2E_DEBUG

namespace DGM {

/// Nodal-to-Element conversion utilities
namespace N2E {

/// Tolerance for identifying boundaries
static const double EPSILON = 1.0e-6;

/// Define a pair of periodic sides
class Periodic {
public:
  /// Constructor
  Periodic() : inc(0), sid1(0), sid2(0) {}
  int inc;                      ///< Element increment across periodic sides
  int sid1;                     ///< Side 1 mates to side 2
  int sid2;                     ///< Side 2 mates to side 1
};

/// Defines periodic parameters
static Periodic periodic;

/// Holds information needed for nodal to element conversion
class Side {
public:
  int id;                       ///< Local side id
  int eid;                      ///< Element id
  Side *link;                   ///< Linked side
  vector<int> node;             ///< Nodal numbers that form the side
  /// Constructor
  Side(int A, int B, int ID, int EID) {
    id=ID; eid=EID; link=0;
    node.push_back(A); node.push_back(B);
    sort( node.begin(), node.end() );  // makes equality test easier
  }
  /// Constructor
  Side(int A, int B, int C, int D, int ID, int EID) {
    id=ID; eid=EID; link=0;
    node.push_back(A); node.push_back(B);
    node.push_back(C); node.push_back(D);
    sort( node.begin(), node.end() );  // makes equality test easier
  }
  Side(int A, int B, int C, int ID, int EID) {
    id=ID; eid=EID; link=0;
    node.push_back(A); node.push_back(B); node.push_back(C);
    sort( node.begin(), node.end() );  // makes equality test easier
  }
  /// Side iterator
  typedef list<Side>::iterator SI;
  /// Constant side iterator
  typedef list<Side>::const_iterator CSI;
};

/// Holds the verts and sides for nodal to element conversion
class Element {
public:
  vector<Side> loc_edgs;
  int Nverts;
  int elmid;
  Element();
};

/// Defines boundary condition sides
class Boundary {
public:
  int eid;                      ///< Element id
  int sid;                      ///< Side id
  Side::SI link;                ///< Link to N2E::Side
  /// Constructor
  Boundary(int EID, int SID, Side::SI SIDE) : eid(EID), sid(SID), link(SIDE) {}
  /// Iterator
  typedef list<Boundary*>::iterator BCI;
  /// Constant iterator
  typedef list<Boundary*>::const_iterator CBCI;
};

//! \name Overloaded operators
//@{

/// Determines if two sides are equal
/** Two sides are equal if their node id's match and they are from
    different elements.  Requiring that they be from different elements
    automatically excludes a side from equaling itself.  Now includes the
    possibility of periodicity. */
bool operator==(const Side side1, const Side side2) {
#if 1
  // more general approach suitable for 3d meshes with periodicity
  // if (side1.eid == side2.eid) return false;
  if (side1.node.size() != side2.node.size()) return false;
  int test = 1;
  for (size_t i=0; i<side1.node.size(); i++)
    test = test && (side1.node[i]==side2.node[i]);
  if (test && side1.eid != side2.eid) return true;
#ifdef N2E_PERIODIC
  if (periodic.inc) {
    // inc is used to specify the periodicity increment between nodes
    // sid1 and sid2 are the sides that mate
    const int  &inc = periodic.inc;
    const int &sid1 = periodic.sid1;
    const int &sid2 = periodic.sid2;
    int testp = 0;
    int testq = 0;
    if (side1.id==sid1) {
      testp = 1;
      for (size_t i=0; i<side1.node.size(); i++)
        testp = testp && (side1.node[i]==side2.node[i]-inc); // periodicity
    }
    if (side1.id==sid2) {
      testq = 1;
      for (size_t i=0; i<side1.node.size(); i++)
        testq = testq && (side1.node[i]==side2.node[i]+inc); // periodicity
    }
    if ( testp || testq ) {
      // cout << side1.eid << ", " << side1.id << " matches "
      //      << side2.eid << ", " << side2.id << endl;
      return true;
    }
  }
#endif
  return false;
#else
  // Hardwired for 2d meshes
  if ( ( (side1.node[0]==side2.node[0] && side1.node[1]==side2.node[1]) ||
         (side1.node[0]==side2.node[1] && side2.node[0]==side1.node[1]) ) &&
       ( side1.eid != side2.eid ) )
    return true;
  else
    return false;
#endif
}

/// Determines if a side is less than another side
/** A side is less than another if its sorted node IDs are less
    than the other side's node IDs.  For example, if the ID of
    the first node of side1 is less than the ID of the first node
    of side2, return true; if the ID of the first node of side1 is
    greater than the ID of the first node of side2, return false.
    If the ID of the first node of side1 is equal to the ID of the
    first node of side2, then do a similar test on the second nodes
    of side1 and side2.  Continue this to the third and forth nodes
    for quad sides. */
bool operator<(const Side side1, const Side side2) {
  for (size_t i=0; i<side1.node.size(); i++) {
    if      (side1.node[i] < side2.node[i]) return true;
    else if (side1.node[i] > side2.node[i]) return false;
  }
  return false;
}

/// Determines if two side are not equal
bool operator!= ( const Side side1, const Side side2 ) {
  return (!(side1==side2));
}

/// Output a Side
ostream& operator<< (ostream &os, const Side &c) {
  os << "Side:      " << &c << endl
     << "  id     = " << c.id << endl
     << "  eid    = " << c.eid << endl
     << "  link   = " << c.link << endl;
  for (size_t i=0; i<c.node.size(); i++)
    os << "node["<<i<<"] = "<< c.node[i] << endl;
  return os;
}

//@}

//! \name N2E functions
//@{

/// Print out N2E usage
void showUsage(const string& code) {
  cerr << "\n"
       << "=================================================\n"
       << "Usage: dgm_n2e.exe [Options] [Input Type]        \n"
       << "=================================================\n"
       << "Input type:                                      \n"
       << "  TFE (Traditional Finite Element)               \n"
       << "  UCD (GridGen output)                           \n"
       << "  NEU (Gambit general solver output)             \n"
       << "=================================================\n"
       << "Options:               Description               \n"
       << "=================================================\n"
       << "-o \"#\"                 Nodal Offset (# = offset) \n"
       << "-orien \"cw or ccw\"     Connectivity  orientation \n"
       << "-cubit or -Cubit       Use a cubit mesh          \n"
       << "-f \"Filename(s)\"       xyz file first for TFE    \n"
       << "-r root                root filename for output  \n"
       << "-p inc sid1 sid2       Support for periodicity   \n"
#ifdef N2E_DGRAPH
       << "-w \"Filename(s)\"       weights file for elements \n"
       << "-dg \"Filename(s)\"      dual graph file           \n"
#endif
       << "-cgc                   write CG node connectivity\n"
       << "-nodal                 create nodal elements     \n"
       << "-spectral              create spectral elements  \n"
       << "-noascii               do not make ascii output  \n"
       << "-tecplot               generate Tecplot output   \n"
       << "-help                  For more information      \n";
}

/// Print out N2E help
void showHelp(const string& code) {
  cerr << "\n"
       << "Help for: dgm_n2e.exe                            \n"
       << "_________________________________________________\n"
       << "  In it's current state this program can only    \n"
       << "  read in ASCII files meshes.                    \n"
       << "_________________________________________________\n"
       << "Default settings for:                            \n"
       << "TFE (Traditional Finite Element)                 \n"
       << "    dgm_n2e.exe -o 1 -orien ccw TFE     or       \n"
       << "    dgm_n2e.exe TFE                            \n\n"
       << "    Default nodal coordinate file:  xyz.asc      \n"
       << "    Default connectivity file:      ien.asc      \n"
       << "    Default nodal offset = 1                     \n"
       << "    Default connectivity is CCW                  \n"
       << "UCD (Unstructured Cell Data)                     \n"
       << "    dgm_n2e.ese -o 1 -orien cw UCD     or        \n"
       << "    dgm_n2e.exe UCD                            \n\n"
       << "    Default mesh file:              grid.grd     \n"
       << "    Default nodal offset = 1                     \n"
       << "    Default connectivity is CW)                  \n"
       << "_________________________________________________\n"
       << "Special file format for TFE:                     \n"
       << "   -The first number on the first line of the    \n"
       << "    of the nodal coordinate file is the number of\n"
       << "    nodes in the mesh.                           \n"
       << "   -The first number on the first line of the    \n"
       << "    connectivity file is the number of elements  \n"
       << "    in the mesh.                                 \n"
       << "_________________________________________________\n";
}

//@}

} // end of N2E namespace

} // end of DGM namespace

//=============================================================================
//                     Nodal to Element main program
//=============================================================================

/// DGM Nodal to Element main program
int main(int argc, char *argv[]) {
  using DGM::Mesh;
  using DGM::Point;
  using DGM::Field;
  using DGM::dMatrix;
  using namespace DGM::N2E;

#ifdef DGM_PARALLEL
  DGM::Comm::World.reset( new DGM::MpiComm( &argc, &argv ) );
#else
  DGM::Comm::World.reset( new DGM::SerialComm() );
#endif
  DGM::Comm::Interupt();        // install a Posix signal handeler

  int verb = 0;                 ///< Verbosity level
  int nn;                       ///< Number of nodes in mesh
  int nsd = 2;                  ///< Use default of 2-d for now
  int ne;                       ///< Number of elements in mesh
  int miniflag = 1;             ///< Flag for orientation in UCD format
  double max_x = 0.0;           ///< Max value in x
  double max_y = 0.0;           ///< Max value in y
  double max_z = 0.0;           ///< Max value in z
  double min_x = 0.0;           ///< Min value in x
  double min_y = 0.0;           ///< Min value in y
  double min_z = 0.0;           ///< Min value in z
  int CubitFlag = 0;            ///< CubitFlag=1 when Cubit is used
  bool writeCGCfile = false;    ///< if writeCGCfile == true, write
                                ///< Continuous Galerkin nodal connectivity
  bool nodal = false;           ///< if true, use nodal elements (not modal)
  bool spectral = false;        ///< if true, use spectral elements
  bool writeASCII = true;       ///< if true, do not output ASCII files
  bool writeTecplot = false;    ///< if true, write a Tecplot file
  list<Side> side_list;         ///< List of sides
  list<Boundary*> bc_list;      ///< List of boundary conditions
  string buffer;                ///< temporary buffer

  string code, format, name, value, root="new";

  // Setup defaults
  int OFFSET = 1;               ///< Nodal offset
  int CLOCKWISE = 0;            ///< Connectivity orientation: 1=cw, 0=ccw

  // Setup default filenames

  // Traditional FE
  string ienfile = "ien.asc";   ///< ASCII Nodal connectivity file
  string xyzfile = "xyz.asc";   ///< ASCII coordinate file

  // UCD (gridgen format)
  string ucdfile = "grid.grd";  ///< UCD grid file

  // data file for UCD or NEU format
  ifstream data;                ///< data stream

#ifdef N2E_DGRAPH
  // In future, the weights will includes three factors: Element type,
  // Polynomial order(curve/straight) and physical models
  string weightfile = "weight.asc";
  string dgraphfile = "dgraph.asc";
#endif

  // NEU (Gambit general solver mesh format: element side)
  string neufile = "grid.neu";  ///< Gambit mesh file name
  int ngrps;                    ///< group numbers in Gambit
  int nbsets;                   ///< boundary type
  int ndfcd;                    ///< not sure??  Dimension??
  int ndfvl;                    ///< not sure??

  // echo arguments
  if (verb>2) {
    cout << "Echoing input arguments" << endl;
    for (int i=0;i<argc-1;i++) {
      cout << "i = " << i << " argv[] = " << argv[i+1] << endl;
    }
  }

  code = argv[0];

  if (argc == 1) {
    cerr << "\nNeed to specify Input Type" << endl;
    showUsage(code);
    return DGM::SUCCESS;
  }

  string temp = argv[1];
  if (temp == "-help") {
    showHelp(code);
    return DGM::SUCCESS;
  }

  format = argv[argc-1];
  if (format != "UCD" && format != "TFE"  && format != "NEU") {
    cerr << "\nUnsupported Input Type, "<<format<<", for " << code << endl;
    showUsage(code);
    return DGM::FAILURE;
  }

  if (argc > 2) {
    while ( --argc && (*++argv)[0] == '-') {
      name = *argv;
      if (name == "-o") {
        value = *(++argv);
        argc--;
        OFFSET = atoi(value.c_str());
      } else if (name == "-p") {
        value = *(++argv);
        argc--;
        periodic.inc = atoi(value.c_str());
        value = *(++argv);
        argc--;
        periodic.sid1 = atoi(value.c_str());
        value = *(++argv);
        argc--;
        periodic.sid2 = atoi(value.c_str());
#ifdef N2E_DGRAPH
      } else if (name == "-w") { // weights file
        weightfile = *(++argv);
        argc--;
      } else if (name == "-dg") { // output dual graph file
        dgraphfile = *(++argv);
        argc--;
#endif
      } else if (name == "-orien") {
        value = *(++argv);
        argc--;
        if (value == "ccw") {
          miniflag=0;
          cout << "setting CLOCKWISE = 0" << endl;
          CLOCKWISE = 0;
        } else if (value == "cw") {
          miniflag = 0;
          cout << "setting CLOCKWISE = 1" << endl;
          CLOCKWISE = 1;
        } else {
          cerr << "Connectivity orientation value, "
               << ", is incorrect.\n" << endl;
          showUsage(code);
        }
      } else if (name == "-help") {
        showHelp(code);
      } else if (name == "-f") {
        if (format == "TFE") {
          xyzfile = *(++argv);
          argc--;
          ienfile = *(++argv);
          argc--;
        } else if (format == "UCD") {
          ucdfile = *(++argv);
          argc--;
        } else if (format == "NEU") {
          neufile = *(++argv);
          argc--;
        } else showUsage(code);
      } else if (name == "-r") {
        value = *(++argv);
        argc--;
        root = value;
      } else if (name == "-Cubit" || name == "-cubit") {
        CubitFlag = 1;
      } else if (name == "-cgc") {
        writeCGCfile = true;
      } else if (name == "-nodal") {
        nodal = true;
      } else if (name == "-spectral") {
        spectral = true;
      } else if (name == "-noascii") {
        writeASCII = false;
      } else if (name == "-tecplot") {
        writeTecplot = true;
      } else {
        cerr << "Flag used, " << name << ", is not supported.\n" << endl;
        showUsage(code);
      }
    }
  }

  if (format == "UCD" && miniflag) {
    cerr << "setting CLOCKWISE = 1" << endl;
    CLOCKWISE = 1;
  }

  // ==========================================================================

  // Storage for the coordinate information of the nodes
  DGM::dMatrix xyz;

  // Storage for FE-like nodal connectivity
  vector<vector<int> > nglob;

  // Construct "mesh" for translation from nodal knowledge (resize later)
  Mesh mesh(1,1);

  if (format == "TFE") {

    cout << "________________________________________________________\n\n"
         << "   HHHHH  HHHHH  HHHHH                                  \n"
         << "     H    H      H                                      \n"
         << "     H    HHH    HHH   (Traditional Finite Element Data)\n"
         << "     H    H      H                                      \n"
         << "     H    H      HHHHH                                  \n"
         << "________________________________________________________\n"
         <<endl;

    // read node points
    ifstream nodes(xyzfile.c_str());
    if (!nodes) {
      cerr << "Could not open coordinate file " << xyzfile << endl;
      return DGM::FAILURE;
    }

    nodes >> nn >> nsd;
    getline(nodes, buffer);
    cout << "Number of nodes = " << nn << ", nsd = " << nsd << endl;
    xyz.resize(nn,3);
    xyz = 0;

    for (int i=0; i<nn; i++) {
      for (int j=0; j<nsd; j++) {
        nodes >> xyz[i][j];
        // cout << xyz[i][j] << endl;
        if (j==0) {
          if (xyz[i][j] > max_x) max_x = xyz[i][j];
          if (xyz[i][j] < min_x) min_x = xyz[i][j];
        }
        if (j==1) {
          if (xyz[i][j] > max_y) max_y = xyz[i][j];
          if (xyz[i][j] < min_y) min_y = xyz[i][j];
        }
        if (j==2) {
          if (xyz[i][j] > max_z) max_z = xyz[i][j];
          if (xyz[i][j] < min_z) min_z = xyz[i][j];
        }
      }
      getline(nodes, buffer);  // get rest of line
      // cout << "x: " << xyz[i][0] << " y: " << xyz[i][1] << endl;
    }
    cout << "  x: Min, Max = " << min_x << ", " << max_x << endl;
    cout << "  y: Min, Max = " << min_y << ", " << max_y << endl;
    cout << "  z: Min, Max = " << min_z << ", " << max_z << endl;

    // read element nodal-connectivity
    ifstream connectivity(ienfile.c_str());
    if (!connectivity) {
      cerr << "Could not open connectivity file: " << ienfile << endl;
      return DGM::FAILURE;
    }

    // Get the number of elements
    int nsd_i;
    connectivity >> ne >> nsd_i;
    cout << "Number of elements = " << ne << ", nsd = " << nsd << endl;
#if 0
    // turn off this check since Metis expects the element type and not nsd
    if (nsd_i != nsd) {
      DGM::Comm::World->cerr()
        << "Error nsd in IEN file does not match XYZ fild" << endl;
      return DGM::FAILURE;
    }
#endif
    // Construct "mesh" for translation from nodal knowledge
    mesh.resize(nsd, ne);

    // Grabs the rest of the first line
    getline(connectivity, buffer);

    // loop over the elements
    for (int eid=0; eid<ne; eid++) {
      getline(connectivity,buffer);
      istringstream ist(buffer);
      int node;
      vector<int> n;
      while (ist >> node) {
        n.push_back( node - OFFSET );
        // cout << n[n.size()-1] << endl;
      }
      // cout << "Nodes on element "<< eid << " = " << n.size() << endl;

      // determine the element type
      switch(n.size()) {
      case 2:
        if      (nodal)    mesh.etype.push_back( DGM::Topology::NodalLine );
        else if (spectral) mesh.etype.push_back( DGM::Topology::SpectralLine );
        else               mesh.etype.push_back( DGM::Topology::Line );
        break;
      case 3:
        if (nodal) mesh.etype.push_back( DGM::Topology::NodalTri );
        else       mesh.etype.push_back( DGM::Topology::Tri );
        break;
      case 4:
        if      (3==nsd)   mesh.etype.push_back( DGM::Topology::NodalTet  );
        else if (nodal)    mesh.etype.push_back( DGM::Topology::NodalQuad );
        else if (spectral) mesh.etype.push_back( DGM::Topology::SpectralQuad );
        else               mesh.etype.push_back( DGM::Topology::Quad );
        break;
      case 8:
        if      (nodal)    mesh.etype.push_back( DGM::Topology::NodalHex );
        else if (spectral) mesh.etype.push_back( DGM::Topology::SpectralHex );
        else               mesh.etype.push_back( DGM::Topology::Hex );
        break;
      default:
        cerr << "Could not determine element type with " << n.size()
             << " nodes." << endl;
        return DGM::FAILURE;
      }

      if (CLOCKWISE) {
        vector<int> tmp(n.size());
        for (size_t k=0; k<n.size(); k++)
          tmp[k] = n[n.size()-k-1];
        for (size_t k=0; k<n.size(); k++)
          n[k] = tmp[k];
      }

      Point C(0.0, 0.0, 0.0);
      for (size_t k=0; k<n.size(); k++) {
        C.x = xyz[n[k]][0];
        C.y = xyz[n[k]][1];
        C.z = xyz[n[k]][2];
        // cout << k << " " << n[k] << " " << C << endl;
        // cout << C << endl;
        mesh.point.push_back(C);
      }

      // store connectivity for Continuous Galerkin (CG) use
      nglob.push_back(n);

      // add sides
      if (  mesh.etype[eid] != DGM::Topology::NodalHex     &&
            mesh.etype[eid] != DGM::Topology::SpectralHex  &&
            mesh.etype[eid] != DGM::Topology::NodalTet     &&
            mesh.etype[eid] != DGM::Topology::Hex         ) {
        int nSides=0;
        for (size_t p=0; p<n.size()-1; p++) {
          side_list.push_back(*(new Side(n[p], n[p+1], nSides++, eid)));
        }
        side_list.push_back(*(new Side(n.back(), n[0], nSides++, eid)));
      } else {
        int nSides=0;
        if ( mesh.etype[eid] != DGM::Topology::NodalTet) {
          side_list.push_back(*(new Side(n[0],n[1],n[2],n[3],nSides++,eid)));
          side_list.push_back(*(new Side(n[0],n[1],n[5],n[4],nSides++,eid)));
          side_list.push_back(*(new Side(n[1],n[2],n[6],n[5],nSides++,eid)));
          side_list.push_back(*(new Side(n[3],n[2],n[6],n[7],nSides++,eid)));
          side_list.push_back(*(new Side(n[0],n[3],n[7],n[4],nSides++,eid)));
          side_list.push_back(*(new Side(n[4],n[5],n[6],n[7],nSides++,eid)));
        } else {
          side_list.push_back(*(new Side(n[0],n[1],n[2],nSides++,eid)));
          side_list.push_back(*(new Side(n[0],n[1],n[3],nSides++,eid)));
          side_list.push_back(*(new Side(n[1],n[2],n[3],nSides++,eid)));
          side_list.push_back(*(new Side(n[2],n[0],n[3],nSides++,eid)));
        }
      }

    }
    cout << "Total number of sides = " << side_list.size() << endl;

  } else if (format == "UCD") {

    cout << "___________________________________________________________\n\n"
         << "       H   H  HHHHH  HHHH                                  \n"
         << "       H   H  H      H   H                                 \n"
         << "       H   H  H      H   H   (Unstructured Cell Data)      \n"
         << "       H   H  H      H   H                                 \n"
         << "       HHHHH  HHHHH  HHHH                                  \n"
         << "___________________________________________________________\n"
         <<endl;

    // read node points
    data.open(ucdfile.c_str());

    if (!data) {
      cerr << "Could not open UCD mesh file: " << ucdfile << endl;
      return DGM::FAILURE;
    }

    for (int i=0;i<3;i++) getline(data,buffer);

    data >> nn;
    data >> ne;
    getline(data, buffer);

    cout << "Number of nodes = " << nn << endl;
    cout << "Number of elements = " << ne << endl;

    // Just in case the order of the elements or the nodes are not
    // consecutive in the UCD mesh file, they are orginized when read in

    xyz.resize(nn,3);
    xyz = 0;
    int node_num=-1;

    for (int i=0; i<nn; i++) {
      data >> node_num;
      for (int j=0; j<nsd; j++) {
        data >> xyz[node_num-1][j];
        if (j==0) {
          if (xyz[node_num-1][j]>max_x) {
            max_x = xyz[node_num-1][j];
          }
          if ( xyz [node_num-1][j]<min_x ) {
            min_x = xyz[node_num-1][j];
          }
        }
        if (j==1) {
          if (xyz[node_num-1][j]>max_y) {
            max_y = xyz[node_num-1][j];
          }
          if ( xyz [node_num-1][j]<min_y ) {
            min_y = xyz[node_num-1][j];
          }
        }
      }
      getline(data, buffer);
      // cout << "x: " << xyz[i][0] << " y: " << xyz[i][1] << endl;
    }
    // read element connectivity and construct "mesh" for translation from
    // nodal knowledge
    mesh.resize(nsd, ne);

    // loop over the elements
    int junk;
    string eltype;
    int eltype_num;             // number indicator for switch

    for (int eid=0; eid<ne; eid++) {
      data >> junk;
      data >> junk;
      data >> eltype;

      if (eltype == "line") {
        eltype_num = 1;
      } else if (eltype == "tri") {
        eltype_num = 2;
      } else if (eltype == "quad") {
        eltype_num = 3;
      } else if (eltype == "hex") {
        eltype_num = 4;
      } else if (eltype == "tet") {
        eltype_num = 5;
      } else {
        cerr << "Element type, " << eltype << ", is not supported" << endl;
        return DGM::FAILURE;
      }

      getline(data,buffer);
      istringstream ist(buffer);
      int node;
      vector<int> n;
      while (ist >> node)
        n.push_back( node - OFFSET );
      switch(eltype_num) {
      case 1:
        if (nodal)         mesh.etype.push_back( DGM::Topology::NodalLine );
        else if (spectral) mesh.etype.push_back( DGM::Topology::SpectralLine );
        else               mesh.etype.push_back( DGM::Topology::Line );
        break;
      case 2:
        if (nodal) mesh.etype.push_back( DGM::Topology::NodalTri );
        else       mesh.etype.push_back( DGM::Topology::Tri );
        break;
      case 3:
        if      (nodal)    mesh.etype.push_back( DGM::Topology::NodalQuad );
        else if (spectral) mesh.etype.push_back( DGM::Topology::SpectralQuad );
        else               mesh.etype.push_back( DGM::Topology::Quad );
        break;
      default:
        cerr << "Could not determine element type with " << n.size()
             << " nodes." << endl;
        return DGM::FAILURE;
      }

      if (CLOCKWISE) {
        vector<int> tmp(n.size());
        for (size_t k=0; k<n.size(); k++)
          tmp[k] = n[n.size()-k-1];
        for (size_t k=0; k<n.size(); k++)
          n[k] = tmp[k];
      }

      Point C(0.0, 0.0, 0.0);
      for (size_t k=0; k<n.size(); k++) {
        C.x = xyz[n[k]][0];
        C.y = xyz[n[k]][1];
        C.z = xyz[n[k]][2];
        // cout << k << " " << n[k] << " " << C << endl;
        mesh.point.push_back(C);
      }

      // add sides (only works for 2-d)
      int nSides=0;
      for (size_t p=0; p<n.size()-1; p++) {
        side_list.push_back(*(new Side(n[p], n[p+1], nSides++, eid)));
      }
      side_list.push_back(*(new Side(n.back(), n[0], nSides++, eid)));
    }
    cout << "Total number of sides = " << side_list.size() << endl;

  } else if (format == "NEU") {

    cout << "___________________________________________________________\n\n"

         << "       (Gambit general solver mesh Data)                   \n"
         << "___________________________________________________________\n"
         <<endl;

    // read node points
    data.open(neufile.c_str());

    if (!data) {
      cerr << "Could not open NEU mesh file: " << neufile << endl;
      return DGM::FAILURE;
    }

    for (int i=0;i<6;i++) getline(data,buffer);

    data >> nn;
    data >> ne;
    data >> ngrps;
    data >> nbsets;
    data >> ndfcd;
    data >> ndfvl;
    getline(data, buffer);

    /*                GAMBIT NEU format for Hex element
       Vertices

       b
       |
       |                 Face order:  0) back   {0,1,5,4}
       2-------3                      1) bottom {1,3,7,5}
      /.      /|                      2) right  {3,2,6,7}
     / .     / |                      3) top    {2,0,4,6}
    6------ 7  |                      4) left   {1,0,2,3}
    |  0....|..1 --- a                5) front  {4,5,7,6}
    | .     | /          Edge order: {{0,4}, {0,1}, {1,5}, {4,5},
    |.      |/                        {1,3}, {3,7}, {5,7}, {2,3},
    4-------5                         {2,6}, {6,7}, {0,2}, {4,6}};
   /
  c

*/

  /*                 DGM support
       Vertices

       b
       |
       |                 Face order:  0) back   {0,1,2,3}
       3-------2                      1) bottom {0,1,5,4}
      /.      /|                      2) right  {1,2,6,5}
     / .     / |                      3) top    {3,2,6,7}
    7------ 6  |                      4) left   {0,3,7,4}
    |  0....|..1 --- a                5) front  {4,5,6,7}
    | .     | /          Edge order: {{0,1}, {1,2}, {3,2}, {0,3},
    |.      |/                        {0,4}, {1,5}, {2,6}, {3,7},
    4-------5                         {4,5}, {5,6}, {7,6}, {4,7}};
   /
  c

*/
    cout << "Number of nodes = " << nn << endl;
    cout << "Number of elements = " << ne << endl;
    cout << "Number of groups =" << ngrps << endl;
    cout << "Number of boundary types =" << nbsets << endl;

    nsd = ndfcd; // dimensions

    getline(data, buffer);
    getline(data, buffer);
    // Just in case the order of the elements or the nodes are not
    // consecutive in the NEU mesh file, they are organized when read in

    xyz.resize(nn,3);
    xyz = 0;
    int node_num=-1;

    for (int i=0; i<nn; i++) {
      data >> node_num;
      for (int j=0; j<nsd; j++) {
        data >> xyz[node_num-1][j];
        if (j==0) {
          if (xyz[node_num-1][j]>max_x) {
            max_x = xyz[node_num-1][j];
          }
          if ( xyz [node_num-1][j]<min_x ) {
            min_x = xyz[node_num-1][j];
          }
        }
        if (j==1) {
          if (xyz[node_num-1][j]>max_y) {
            max_y = xyz[node_num-1][j];
          }
          if ( xyz [node_num-1][j]<min_y ) {
            min_y = xyz[node_num-1][j];
          }
        }
        if (j==2) {
          if (xyz[node_num-1][j]>max_z) {
            max_z = xyz[node_num-1][j];
          }
          if ( xyz [node_num-1][j]<min_z ) {
            min_z = xyz[node_num-1][j];
          }
        }
      }
      getline(data, buffer);
      // cout << "x: " << xyz[i][0] << " y: " << xyz[i][1] << endl;
    }

    getline(data, buffer);  // get rid of the last line in this block

    getline(data, buffer);  // get rid of the fist line in the coming block

    // read element connectivity
    // Construct "mesh" for translation from nodal knowledge
    mesh.resize(nsd, ne);

    // loop over the elements
    int junk;
    string eltype;
    int eltype_num;   // number indicator for switch

    for (int eid=0; eid<ne; eid++) {
      data >> junk;
      data >> junk;
      data >> eltype_num;
      eltype_num --;
      if (eltype_num<1 || eltype_num >8) {
        cerr << "Element type, " << eltype_num +1
             << ", is not supported" << endl;
        return DGM::FAILURE;
      }
      getline(data,buffer);
      istringstream ist(buffer);
      int node;
      vector<int> n;
      while (ist >> node)
        n.push_back( node - OFFSET );
      // For Hex element, the connectivity info, of each element uses two lines
      if(eltype_num >=7){
        getline(data,buffer);
        istringstream ist1(buffer);
        while (ist1 >> node)
          n.push_back( node - OFFSET );
      }
      switch(eltype_num) {
      case 1:
        if      (nodal)    mesh.etype.push_back( DGM::Topology::NodalLine );
        else if (spectral) mesh.etype.push_back( DGM::Topology::SpectralLine );
        else               mesh.etype.push_back( DGM::Topology::Line );
        break;
      case 2:
        if (nodal) mesh.etype.push_back( DGM::Topology::NodalTri );
        else       mesh.etype.push_back( DGM::Topology::Tri );
        break;
      case 3:
        if      (nodal)    mesh.etype.push_back( DGM::Topology::NodalQuad );
        else if (spectral) mesh.etype.push_back( DGM::Topology::SpectralQuad );
        else               mesh.etype.push_back( DGM::Topology::Quad );
        break;
      case 7:
        if      (nodal)    mesh.etype.push_back( DGM::Topology::NodalHex );
        else if (spectral) mesh.etype.push_back( DGM::Topology::SpectralHex );
        else               mesh.etype.push_back( DGM::Topology::Hex );
        // conversion from NEU order to DGM order for Hex
        int tmp;
        tmp  = n[2];
        n[2] = n[3];
        n[3] = tmp;
        tmp  = n[6];
        n[6] = n[7];
        n[7] = tmp;
        break;
      default:
        cerr << "Could not determine element type with " << n.size()
             << " nodes." << endl;
        return DGM::FAILURE;
      }

      if (CLOCKWISE) {
        vector<int> tmp(n.size());
        for (size_t k=0; k<n.size(); k++)
          tmp[k] = n[n.size()-k-1];
        for (size_t k=0; k<n.size(); k++)
          n[k] = tmp[k];
      }

      Point C(0.0, 0.0, 0.0);
      for (size_t k=0; k<n.size(); k++) {
        C.x = xyz[n[k]][0];
        C.y = xyz[n[k]][1];
        C.z = xyz[n[k]][2];
        // cout << k << " " << n[k] << " " << C << endl;
        mesh.point.push_back(C);
      }

      if ( (mesh.etype[eid] != DGM::Topology::NodalHex)    &&
           (mesh.etype[eid] != DGM::Topology::SpectralHex) &&
           (mesh.etype[eid] != DGM::Topology::Hex)        ) {
        // add sides (only works for 2-d)
        int nSides=0;
        for (size_t p=0; p<n.size()-1; p++) {
          side_list.push_back(*(new Side(n[p], n[p+1], nSides++, eid)));
        }
        side_list.push_back(*(new Side(n.back(), n[0], nSides++, eid)));
      } else {
        int nSides=0;
        side_list.push_back(*(new Side(n[0],n[1],n[2],n[3],nSides++,eid)));
        side_list.push_back(*(new Side(n[0],n[1],n[5],n[4],nSides++,eid)));
        side_list.push_back(*(new Side(n[1],n[2],n[6],n[5],nSides++,eid)));
        side_list.push_back(*(new Side(n[3],n[2],n[6],n[7],nSides++,eid)));
        side_list.push_back(*(new Side(n[0],n[3],n[7],n[4],nSides++,eid)));
        side_list.push_back(*(new Side(n[4],n[5],n[6],n[7],nSides++,eid)));
      }
    }
    cout << "Total number of sides = " << side_list.size() << endl;

    // Processing the groups, not useful for us
    string sjunk;
    int Ngroup, ngnodes, nlines;

    getline(data,buffer);
    getline(data,buffer);
    data >> sjunk >> Ngroup >> sjunk >> ngnodes;
    getline(data,buffer);
    getline(data,buffer);
    getline(data,buffer);
    if( ngnodes%10 ==0)  //10 node number for each line
      nlines = ngnodes/10;
    else
      nlines = ngnodes/10 +1;

    for(int i =0; i<nlines; i++)
      getline(data,buffer);

    getline(data,buffer);

  } else {
    cerr << "The format " << format << " is not supported" << endl;
    return DGM::FAILURE;
  }

#ifdef N2E_DGRAPH
  // storage for the connectivity of the dual graph
#if 1
  vector< vector<int> > en_con(ne);
#else
  iMatrix en_con(ne,5);
  iVector ien(ne);
  en_con = -1;
  ien =0;
#endif
  vector<int> weight(ne);
#endif

  // ==========================================================================

  // Search through the side list and make bi-directional links
  cout << "Making side links..." << endl;
  Mesh::MyCon con;
  side_list.sort();
  Side::SI e;
  for ( Side::SI cur=side_list.begin(); cur!=side_list.end(); cur++)  {
    e = cur; e++;
    if ( *(cur) == *(e) ) {
      cur->link = &(*e);
      e->link = &(*cur);
      mesh.con.push_back( con.set( cur->eid, cur->id, e->eid, e->id ) );
      mesh.con.push_back( con.set( e->eid, e->id, cur->eid, cur->id ) );
#ifdef N2E_DGRAPH
      if(e->eid!=cur->eid){
#if 1
        en_con[cur->eid].push_back(e->eid);
        en_con[e->eid].push_back(cur->eid);
#else
        en_con[cur->eid][ien[cur->eid]++] = e->eid;
        en_con[e->eid][ien[e->eid]++] = cur->eid;
#endif
      }
#endif
      cur++;  // Since we matched the next side in list, skip it.
    } else {
#ifdef N2E_DEBUG
      cout << "Element " << cur->eid << ", side " << cur->id
           << " must be on the boundary" << endl;
#endif
      bc_list.push_back( new Boundary( cur->eid, cur->id, cur ) );
    }
    if ( ++e == side_list.end() ) {
      // Check if the last side matched or is a boundary side.
      e--;
      cur = e; cur--;
      if ( *(cur) != *(e) )
        bc_list.push_back( new Boundary( e->eid, e->id, e ) );
      break;
    }
  }
  cout << "Number of boundary sides " << bc_list.size() << endl;

#if 0
  // print the side list
  for (Side::SI e=side_list.begin(); e!=side_list.end(); e++)
    cout << *e << endl;
#endif

#ifdef N2E_DGRAPH
  cout << "Making dual graph ..." << endl;
  ifstream fweight(weightfile.c_str());
  if(fweight)
    for ( int en=0; en<ne; en++) fweight>>weight[en];
  else
    for ( int en=0; en<ne; en++) weight[en] = 1;
  ofstream fdgraph(dgraphfile.c_str());
  // output the headline of the weight graph
  fdgraph<<ne<<" "<<(side_list.size() - bc_list.size())/2.0
         <<" 10"<<endl;
  for(int en=0;en<ne;en++){
#if 1
    // output the weights of the vertex
    fdgraph<<weight[en]<<" ";
    // output the id of the vertex
    for(size_t k=0;k<en_con[en].size();k++)
      fdgraph<<en_con[en][k]+1<<" ";
#else
    fdgraph<<weight[en]<<" ";
    for(int k=0;k<ien[en];k++)
      fdgraph<<en_con[en][k]+1<<" ";
#endif
    fdgraph<<endl;
  }
  fweight.close();
  fdgraph.close();
#endif

#ifdef N2E_MAKE_BC
  // print the bc list
  value = root + ".bc";
  ofstream fout(value.c_str());
  fout << "**BOUNDARY CONDITION DATA**" << endl;
  fout << bc_list.size() << " nbc" << endl;
  if (format == "NEU") {
    string bc_type;
    int nbc_side;
    int junk, eid,sid;
    for (int nbc_count=0; nbc_count < nbsets; nbc_count ++) {
      getline(data,buffer);
      data >> bc_type >> junk >> nbc_side;
      getline(data,buffer);
      for (int i=0; i< nbc_side; i++) {
        if ( data >> eid >> junk >> sid ) {
          if ( (mesh.etype[eid-OFFSET] == DGM::Topology::NodalHex)    ||
               (mesh.etype[eid-OFFSET] == DGM::Topology::SpectralHex) ||
               (mesh.etype[eid-OFFSET] == DGM::Topology::Hex)        ) {
            // conversion from Gambit NEU to DGM
            switch(sid){
            case 1:
            case 2:
            case 3:
            case 4:
              sid ++;
              break;
            case 5:
              sid = 1;
              break;
            case 6:
              break;
            }
          }
          fout << bc_type << " " << eid-OFFSET
               << " " << sid-OFFSET << endl;
        }
        getline(data,buffer);
      }
      getline(data,buffer);
    }
  } else {
    ifstream ss("side.asc");
    if (ss) {  // works for sidesets generated from an ExodusII file
      cout << "Reading BC's from file side.asc..." << endl;
      int id, eid, sid;

      /*                Cubit format for Hex elements
           Vertices

           b
           |
           |                 Face order:  0) bottom {0,1,5,4}
           3-------2                      1) right  {1,2,6,5}
          /.      /|                      2) top    {3,2,6,7}
         / .     / |                      3) left   {0,3,7,4}
        7------ 6  |                      4) back   {0,1,2,3}
        |  0....|..1 --- a                5) front  {4,5,6,7}
        | .     | /
        |.      |/
        4-------5
       /
      c

      */

      // This map fixes a problem with the connectivity file in 3 dimensions
      // by reassigning the side values.
      const int map[6] = {1, 2, 3, 4, 0, 5};
      string vss = root + ".ss";
      ofstream fss(vss.c_str());
      while ( ss >> id >> eid >> sid ) {
        eid -= OFFSET;
        if (CubitFlag == 1 && (mesh.etype[eid] == DGM::Topology::Hex          ||
                               mesh.etype[eid] == DGM::Topology::NodalHex     ||
                               mesh.etype[eid] == DGM::Topology::SpectralHex) ){
          fout << "bc" << id << " " << setw(10) << eid
               << " " << setw(10) << map[sid-1] << endl;
          fss  << id << " " << setw(10) << eid
               << " " << setw(10) << map[sid-1] << endl;
        } else if (CubitFlag == 1 &&
                   mesh.etype[eid] == DGM::Topology::NodalTet){
          fout << "bc" << id << " " << setw(10) << eid
               << " " << setw(10) << sid%4          << endl;
          fss  << id << " " << setw(10) << eid
               << " " << setw(10) << sid%4          << endl;
        } else {
          fout << "bc" << id << " " << setw(10) << eid
               << " " << setw(10) << sid-OFFSET << endl;
          fss  << id << " " << setw(10) << eid
               << " " << setw(10) << sid-OFFSET << endl;
        }
      }
      fss.close();
      ss.close();
    } else {
      for (Boundary::BCI i=bc_list.begin(); i!=bc_list.end(); i++) {
#if 1   // works for objects embedded in a box
        DGM::Ordinal numnodes = (*i)->link->node.size();
        int testx = 1;
        int testy = 1;
        int testz = 1;
        for (DGM::Ordinal j=0; j<numnodes-1; j++) {
          testx = testx && ( fabs(xyz[(*i)->link->node[j]][0] -
                                  xyz[(*i)->link->node[j+1]][0]) < EPSILON);
          testy = testy && ( fabs(xyz[(*i)->link->node[j]][1] -
                                  xyz[(*i)->link->node[j+1]][1]) < EPSILON);
          testz = testz && ( fabs(xyz[(*i)->link->node[j]][2] -
                                  xyz[(*i)->link->node[j+1]][2]) < EPSILON);
        }
        if (testx)
          if ( fabs(xyz[(*i)->link->node[0]][0]-max_x) < EPSILON )
            fout << "e " << (*i)->eid << " " << (*i)->sid << endl;
          else if ( fabs(xyz[(*i)->link->node[0]][0]-min_x) < EPSILON )
            fout << "w " << (*i)->eid << " " << (*i)->sid << endl;
          else {
            cout << (*i)->eid << " " << xyz[(*i)->link->node[0]][0] << endl;
            fout << "Wx " << (*i)->eid << " " << (*i)->sid << endl;
          }
        else if (testy)
          if ( fabs(xyz[(*i)->link->node[0]][1]-max_y) < EPSILON )
            fout << "n " << (*i)->eid << " " << (*i)->sid << endl;
          else if ( fabs(xyz[(*i)->link->node[0]][1]-min_y) < EPSILON )
            fout << "s " << (*i)->eid << " " << (*i)->sid << endl;
          else {
            cout << (*i)->eid << " " << xyz[(*i)->link->node[0]][1] << endl;
            fout << "Wy " << (*i)->eid << " " << (*i)->sid << endl;
          }
        else if (testz)
          if ( fabs(xyz[(*i)->link->node[0]][2]-max_z) < EPSILON )
            fout << "f " << (*i)->eid << " " << (*i)->sid << endl;
          else if ( fabs(xyz[(*i)->link->node[0]][2]-min_z) < EPSILON )
            fout << "b " << (*i)->eid << " " << (*i)->sid << endl;
          else {
            cout << (*i)->eid << " " << xyz[(*i)->link->node[0]][1] << endl;
            fout << "Wz " << (*i)->eid << " " << (*i)->sid << endl;
          }
        else
          fout << "W " << (*i)->eid << " " << (*i)->sid << endl;
#endif

#if 0   // works for box domains
        if (xyz[(*i)->link->node[0]][0] == xyz[(*i)->link->node[1]][0]) {
          if (xyz[(*i)->link->node[0]][0] == max_x)
            fout << "r " << (*i)->eid << " " << (*i)->sid << endl;
          else if ( xyz[(*i)->link->node[0]][0] == min_x )
            fout << "l " << (*i)->eid << " " << (*i)->sid << endl;
          else
            fout << "W " << (*i)->eid << " " << (*i)->sid << endl;
        } else if (xyz[(*i)->link->node[0]][1] == xyz[(*i)->link->node[1]][1]){
          if ( xyz[(*i)->link->node[0]][1] == max_y)
            fout << "t " << (*i)->eid << " " << (*i)->sid << endl;
          else if (xyz[(*i)->link->node[0]][1] == min_y)
            fout << "b " << (*i)->eid << " " << (*i)->sid << endl;
          else
            fout << "W " << (*i)->eid << " " << (*i)->sid << endl;
        } else
          fout << "W " << (*i)->eid << " " << (*i)->sid << endl;
#endif

#if 0   // works for airfoils
        double xl = xyz[(*i)->link->node[0]][0];
        double yl = xyz[(*i)->link->node[0]][1];
        double rl = sqrt(xl*xl+yl*yl);
        if ( rl > 2 )
          fout << "S " << (*i)->eid << " " << (*i)->sid << endl;
        else
          fout << "W " << (*i)->eid << " " << (*i)->sid << endl;
#endif
      }
      fout.close();
    }
#endif
  }
  //
  // Generate mesh output
  //
  cout << "Building a minimal Field..." << endl;
  Field::Ptr U(new Field (1, 2, mesh, "grid", "mesh", Field::MINIMAL));
  cout << "Setting side links..." << endl;
  U->set_side_links( mesh );
  if (writeASCII) {
    cout << "Writing ASCII mesh file..." << endl;
    U->write_mesh(root+".msh");
    cout << "Writing ASCII connectivity..." << endl;
    U->write_connectivity(root+".con");
  }
  if ( writeCGCfile ) {
    cout << "Writing ASCII nodal connectivity..." << endl;
    U->set_vertex_gid(nglob);
    U->write_node_connectivity(root+".cgc");
  }
  cout << "Writing weights..." << endl;
  U->write_weights( root+".wgt" );
  cout << "Writing graph..." << endl;
  U->write_graph( root+".grf" );
  cout << "Making data storage..."<<endl;
  U->make_storage();
  if (writeTecplot) {
    cout << "Compute geometry..."<<endl;
    U->compute_geometry();
    U->zero();
    cout << "Writing tecplot file..." << endl;
    U->tecplot(root+".dat","mesh");
  }
  //
  // Generate binary mesh output
  //
  U->set_global_side_id();
  U->set_flip();
  mesh.CopyIn(U->el);
  cout << "Writing binary mesh file..." << endl;
  mesh.write(root+".grd",mesh.write_header(root+".grd"));

  // Output the connectivity
  if (verb>2) {
    ofstream out("con.out");
    typedef vector<Mesh::MyCon>::iterator mci;
    for (mci i=mesh.con.begin(); i<mesh.con.end(); ++i)
      out << *i << endl;
  }

  cout << "Writing binary connectivity..." << endl;
  mesh.write_connectivity(root+".cn",mesh.write_header(root+".cn"));
#ifdef OPEN_MPI
#if !((OMPI_MAJOR_VERSION <= 1) && (OMPI_MINOR_VERSION <= 8) && \
    (OMP_RELEASE_VERSION <= 4))
  comm->cout()<<"Explicitly calling World::reset()"<<endl;
  DGM::Comm::World.reset();
#endif
#endif
  return DGM::SUCCESS;
}
