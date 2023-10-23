/** \file exo2ien.cpp
    \brief Converts Exodus to IEN finite-element format

    To compile on SCICO:

    \verbatim
    g++ exo2ien.cpp -I/home/gbarter/local/exodusii/cbind/include \
    -I/home/gbarter/dgm/src \
    -I/home/gbarter/local/netcdf/include \
    -I/home/gbarter/local/atlas/include \
    -L/home/gbarter/local/exodusii/lib \
    -L/home/gbarter/local/atlas/lib \
    -L/home/gbarter/local/netcdf/lib \
    -lexodus -lnetcdf -o exo2ien
    \endverbatim

    \mainpage Exo2Ien Converter

    \section Summary

    The Exo2Ien converter takes and Exodus (Genesis) mesh file and converts
    it to a typical format used by finite-element simulators.

    The output files that include \c xyz.asc which is an ASCII file that
    lists the \f$x, y, z\f$ coordinates for each node point in the mesh and
    the \c ien.asc file that is the nodal connectivity for each element.

    This converter is intended to be used as part of the the DGM library.

    \section Copyright Copyright

    Portions predating July 2003 are copyright Rice University and have been
    declared open source (see License.txt file for more details).

    Portions after July 2003 are copyright Sandia National Laboratories and are
    available for use within Sandia National Laboratories and its partners.  Do
    no distribute without authorization. (see License.txt for more details).

    \section Author Author

    S. Scott Collis,
    Scalable Algorithms,
    Sandia National Laboratories,
    Albuquerque, NM 87175-1320,
    (505) 284-1123,
    sscoll@sandia.gov
**/

// system includes
#include <string>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

// Exodus includes
#include "exodusII.h"

// CMC includes
#include "Types.hpp"
#include "Vector.hpp"
#include "Matrix.hpp"
using namespace DGM;
using namespace CMC;

/// The main Exo2Ien program
int main(int argc, char *argv[]) {
  using namespace std;
  if (argc<2) {
    cerr << "  Usage: exo2ien <Exodus File>\n\n"
         << "     Example:  exo2ien tri.gen\n\n"
         << "  The exo2ien converter takes an Exodus (Genesis) mesh file\n"
         << "  and converts it to a typical format used by finite-element\n"
         << "  simulators (IEN).\n\n"
         << "  The output files include:\n"
         << "    att.asc  - the Exodus attributes for each element (if any).\n"
         << "               Used to ID curved elements, set p and q on\n"
         << "               within element blocks, set material properties\n"
         << "               density, etc., within element blocks.\n"
         << "    bodydefs.json - body or element-block definitions in JSON\n"
         << "               format for elementwise model specification.\n"
         << "               Assumes continuous element numbering within\n"
         << "               element blocks.\n"
         << "    ien.asc  - the nodal connectivity for each element\n"
         << "    side.asc - side set identification for each element\n"
         << "               and element side\n"
         << "    xyz.asc  - an ASCII file that lists the (x, y, z)\n"
         << "               coordinates for each node point in the mesh\n"
         << endl;

    exit(-1);
  }
  std::string fname=argv[1];
  int CPU_word_size, IO_word_size, exoid;
  CPU_word_size = sizeof(double); /* use float or double */
  IO_word_size = 0;  /* store variables as doubles */
  float version;
  printf("Opening %s\n",fname.c_str());
  exoid = ex_open(fname.c_str(),
                  EX_READ,
                  &CPU_word_size,
                  &IO_word_size,
                  &version);
  if (exoid<0) {
    cout << "Error opening " << fname << endl;
    return 1;
  }

  std::cout << "Opened file " << fname << endl
            << " exoid " << exoid << endl
            << " IO_word_size = " << IO_word_size << endl
            << " CPU_word_size = " << CPU_word_size << endl
            << " version = " << version << endl;

  // get the file initiation information

  int num_dim, num_nodes, num_elem, num_elem_blk, num_node_sets, num_side_sets;
  char title[MAX_LINE_LENGTH+1];
  int error = ex_get_init( exoid, title, &num_dim, &num_nodes, &num_elem,
                           &num_elem_blk, &num_node_sets, &num_side_sets);

  cout << " Title = " << title << endl
       << " num_dim = " << num_dim << endl
       << " num_nodes = " << num_nodes << endl
       << " num_elem = " << num_elem << endl
       << " num_elem_blk = " << num_elem_blk << endl
       << " num_node_sets = " << num_node_sets << endl
       << " num_side_sets = " << num_side_sets << endl;

  // get the node coordinates

  dVector x, y, z;
  x.resize(num_nodes);
  y.resize(num_nodes);
  if (num_dim > 2) z.resize(num_nodes);
  error = ex_get_coord( exoid, x.data(), y.data(), z.data() );
  iVector node_map(num_nodes);
  error = ex_get_node_num_map( exoid, node_map.data() );
  cout << "Writing nodal coordinates to xyz.asc..." << endl;
  FILE *xyz = fopen("xyz.asc","w");
  fprintf(xyz,"%7d %7d\n", num_nodes, num_dim);
  if (num_dim == 1) {
    for (int i=0; i<num_nodes; i++)
      fprintf(xyz,"%22.15e\n", x[i]);
  } else if (num_dim == 2) {
    for (int i=0; i<num_nodes; i++)
      fprintf(xyz,"%22.15e %22.15e\n", x[i], y[i]);
  } else if (num_dim == 3) {
    for (int i=0; i<num_nodes; i++)
      fprintf(xyz,"%22.15e %22.15e %22.15e\n", x[i], y[i], z[i]);
  }
  fclose(xyz);

  // get node number map (this is optional)

  // get element number map (optional)

  // get element order map (optional)

  // get element block ids (this does not assume that element block ids are
  // contiguous)

  iVector el_blk_ids(num_elem_blk);
  error = ex_get_elem_blk_ids( exoid, el_blk_ids.data() );

  // loop over the element blocks

  cout << "Writing element connectivity to ien.asc..." << endl;
  ofstream ien("ien.asc");
  ien << setw(10) << num_elem << " "
      << setw(10) << num_dim << endl;
  ofstream att("att.asc"); // element attributes
  att << setw(10) << num_elem << " "
      << setw(10) << num_dim << endl;
  int element(0);

  ofstream json("bodydefs.json"); // element attributes
  json << "  \"BodyDefs\" : {" << endl;
  int eid(0);
  for (int blk=0; blk<num_elem_blk; blk++) {
    cout << " elm_blk = " << blk;
    int id = el_blk_ids[blk];
    int num_el_in_blk, num_nod_per_el, num_attr;
    char elem_type[MAX_STR_LENGTH+1];

    // read element block parameters
    error = ex_get_elem_block( exoid, id, elem_type, &num_el_in_blk,
                               &num_nod_per_el, &num_attr);

    cout << ",  num_nod_per_el = " << num_nod_per_el
         << ",  num_el_in_blk  = " << num_el_in_blk
         << ",  num_attr = " << num_attr << endl;

    // read element connectivity
    iVector connect(num_nod_per_el*num_el_in_blk);
    iMatrix Connect;
    Connect.alias( connect, num_el_in_blk, num_nod_per_el );
    error = ex_get_elem_conn(exoid, id, connect.data());

    // element mapping
    iVector elem_map(num_elem);
    error = ex_get_map(exoid, elem_map.data());

    // need to map the connectivity?

    // output the connectivity for this block
    //ien << setw(10) << num_el_in_blk << " "
    //    << setw(10) << num_nod_per_el << endl;
    for (int e=0; e<num_el_in_blk; e++) {
      // ien << setw(10) << elem_map[e];
      for (int n=0; n<num_nod_per_el; n++)
        ien << "  " << setw(10) << Connect[e][n];
      ien << endl;
    }

    // read the element block attributes
    dVector attrib(num_attr*num_el_in_blk);
    dMatrix Attrib;
    Attrib.alias(attrib, num_el_in_blk, num_attr);
    error = ex_get_elem_attr(exoid, id, attrib.data());

    // output the attributes for this block
    for (int e=0; e<num_el_in_blk; e++) {
      if (num_attr>0) {
        for (int n=0; n<num_attr; n++) {
          att << setw(10) << element << "  " << setw(10) << Attrib[e][n];
        }
        element++;
        att << endl;
      }
    } // elements

    json << "    \"" << id << "\" : {" << endl;
    json << "      \"IdRanges\" : [[" << eid << ","
         << eid+num_el_in_blk-1 << ",1]]" << endl;
    if ( blk == num_elem_blk-1 )  json << "    }" << endl;
    else                          json << "    }," << endl;
    eid+=num_el_in_blk;

  }  // blk
  json << "  }" << endl;
  json.close();

  ien.close();
  att.close();

  // inquire about the side sets
  int num_sides_in_set, num_df_in_set, num_elem_in_set;
  float fdum;
  char cdum;
  error = ex_inquire( exoid, EX_INQ_SIDE_SETS, &num_side_sets, &fdum, &cdum);
  iVector side_set_ids(num_side_sets);
  error = ex_get_side_set_ids(exoid, side_set_ids.data());
  cout << "Writing side set data..." << endl;
  ofstream bc("side.asc");
  for (int i=0; i<num_side_sets; i++) {
    error = ex_get_side_set_param( exoid, side_set_ids[i], &num_sides_in_set,
                                   &num_df_in_set );
    num_elem_in_set = num_sides_in_set;
    cout << " side_set = " << i << ", side_set_id = " << side_set_ids[i]
         << ", num_sides_in_set = " << num_sides_in_set << endl;
    iVector elem_list(num_elem_in_set);
    iVector side_list(num_sides_in_set);
    error = ex_get_side_set( exoid, side_set_ids[i],
                             elem_list.data(), side_list.data() );

    // need to map the side ids

    static int hex_map[6] = {1, 2, 3, 4, 5, 6 };

    for (int j=0; j<num_sides_in_set; j++) {
      bc << setw(10) << side_set_ids[i] << " " << setw(10)
         << elem_list[j] << " " << setw(10) << side_list[j] << endl;
    }
  }
  bc.close();

  //return exoid;
  return 0;
}
