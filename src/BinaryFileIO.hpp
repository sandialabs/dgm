#ifndef DGM_BinaryFileIO_hpp
#define DGM_BinaryFileIO_hpp

/** \file BinaryFileIO.hpp
    \brief A basic interface to DGM binary file formats

    This supports both 32/64 bit file IO through same interface as 
    ASCII text files

    \author K. Noel Belcourt

    int MPI_Type_contiguous(int count, MPI_Datatype old_type, 
                            MPI_Datatype *new_type_p)

    int MPI_Type_indexed(int count, int blocklens[], int indices[], 
                         MPI_Datatype old_type, MPI_Datatype *newtype)

    int MPI_Type_create_hindexed(int count, int blocklengths[], 
      MPI_Aint displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype)

    int MPI_File_set_view(MPI_File mpi_fh, MPI_Offset disp, MPI_Datatype etype, 
      MPI_Datatype filetype, char *datarep, MPI_Info info)

    int MPI_File_read_all(MPI_File mpi_fh, void *buf, int count, 
      MPI_Datatype datatype, MPI_Status *status)
*/

// std includes
#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>
#include <string>
#include <utility>
#include <vector>

// DGM includes
#include "Comm.hpp"
#include "GlobalScan.hpp"
#include "Mesh.hpp"
#include "String.hpp"
#include "Topology.hpp"
#include "Utilities.hpp"
#include "json/json.h"

// Boost includes
#include <boost/lexical_cast.hpp>

#ifdef DGM_PARALLEL

// DGM includes
#include "MpiType.hpp"

// MPI includes
#include <mpi.h>

// boost includes
#include <boost/cast.hpp>
#include <boost/mpi/communicator.hpp>

namespace DGM {

struct mpi_binary_file {
  typedef std::vector<MPI_Datatype> v_types;
  v_types types;
  MPI_File fh;
  MPI_Info info;
  MPI_Status status;
  MPI_Offset json_disp;
  MPI_Datatype mdt_int;
  MPI_Datatype mdt_double;
  boost::mpi::communicator world;
  size_t isize;
  char native[7];

  void check_for_json(const std::string fname) {
    using std::ifstream;
    using std::string;
    using DGM::read_block;
    string strbuf;
    ifstream is(fname.c_str());
    if ('{' == is.get()) {
      read_block(is);
      getline(is, strbuf);
      json_disp = is.tellg();
    }
    is.close();
  }

  void initialize(const std::string fname, const int amode, MPI_Comm comm) {
    using std::cout;
    using std::endl;
    using std::strcpy;
    using std::string;
    using DGM::exception;
    strcpy(native, "native");
    int stat = MPI_Info_create(&info);
    if (stat) throw exception(string("MPI_Info_create failed."));
    stat = MPI_File_open(comm, const_cast<char*>(fname.c_str())
      , amode, info, &fh);
    if (stat)
      throw exception(string("MPI_File_open failed to open file " + fname));
  }

  // interface for writing
  template <typename IntType>
  mpi_binary_file(const std::string fname, IntType
    , boost::mpi::communicator w, bool)
    : json_disp(0), world(w), isize(sizeof(IntType))
  {
    initialize(fname, MPI_MODE_WRONLY | MPI_MODE_CREATE,
               static_cast<MPI_Comm>(world));
    mdt_int = DGM::mpiType<IntType>();
    mdt_double = DGM::mpiType<double>();
  }

  // interface for reading
  template <typename IntType>
  mpi_binary_file(const std::string fname, IntType, boost::mpi::communicator w)
    : json_disp(0), world(w), isize(sizeof(IntType))
  {
    using std::string;
    using DGM::exception;
    using DGM::file_exists;
    // require file to be valid
    if (!file_exists(fname))
      throw exception(string("mpi_binary_file can't open " + fname));
    // for now, skip json header if one exists
    check_for_json(fname);
#if 0
    if (0 < json_disp && 0 == world.rank())
      cout << "  Json header size (bytes) = " << json_disp << endl;
#endif
    initialize(fname, MPI_MODE_RDONLY, static_cast<MPI_Comm>(world));
    mdt_int = DGM::mpiType<IntType>();
    mdt_double = DGM::mpiType<double>();
  }

  ~mpi_binary_file() {
    for (v_types::size_type i=0; i<types.size(); ++i)
      MPI_Type_free(&types[i]);
    MPI_File_close(&fh);
    MPI_Info_free(&info);
  }

  // interface to read one int (displacement is incremented)
  int read(MPI_Offset& disp) {
    using DGM::exception;
    int n = 0;
    int stat = MPI_File_set_view(fh, disp, MPI_INT, mdt_int, native, info);
    if (stat) throw exception(string("mpi_binary_file::write"
      " call to MPI_File_set_view failed"));
    stat = MPI_File_read_all(fh, &n, 1, MPI_INT, &status);
    if (stat) throw exception(string("mpi_binary_file::write"
      " call to MPI_File_write_all failed"));
    disp += isize;
    return n;
  }

  // interface to write one int at a given displacement (non-const, incremented)
  void write(int n, MPI_Offset& disp) {
    using DGM::exception;
    int stat = MPI_File_set_view(fh, disp, MPI_INT, mdt_int, native, info);
    if (stat) throw exception(string("mpi_binary_file::write"
      " call to MPI_File_set_view failed"));
    stat = MPI_File_write_all(fh, &n, 1, MPI_INT, &status);
    if (stat) throw exception(string("mpi_binary_file::write"
      " call to MPI_File_write_all failed"));
    disp += isize;
  }

  // write string to file
  void write_string(const std::string s, MPI_Offset& disp) {
    using DGM::exception;
    // write string length
    int len = s.length();
    write(len, disp);
    // write string name
    int stat = MPI_File_set_view(fh, disp, MPI_CHAR, MPI_CHAR, native, info);
    char* ptr = const_cast<char*>(s.c_str());
    MPI_File_write_all(fh, ptr, len, MPI_CHAR, &status);
    if (stat) throw exception(string("mpi_binary_file::write_string failed to"
      " write string " + s + " to binary file"));
    disp += len;
  }

  // read string from file
  std::string read_string(MPI_Offset& disp) {
    using std::string;
    using DGM::exception;
    // read string length
    int len = read(disp);
    if (len <= 0) throw exception(string("mpi_binary_file::read_string invalid"
      " string length read from binary file"));
    // read string name (length + null), initialize string to null
    string s(len+1, 0);
    int stat = MPI_File_set_view(fh, disp, MPI_CHAR, MPI_CHAR, native, info);
    char* ptr = const_cast<char*>(s.c_str());
    stat = MPI_File_read_all(fh, ptr, len, MPI_CHAR, &status);
    if (stat) throw exception(string("mpi_binary_file::read_string unable to"
      " read string from binary file"));
    disp += len;
    return s;
  }

  // type created using indices
  template <typename Length>
  MPI_Datatype create_indexed_type(int* lengths, int* displacements, Length n)
  {
    using boost::numeric_cast;
    using DGM::exception;
    MPI_Datatype mpi_type;
    int stat = MPI_Type_indexed(numeric_cast<int>(n), lengths
      , displacements, mdt_int, &mpi_type);
    if (stat) throw exception(string("mpi_binary_file::create_indexed_type"
      " call to MPI_Type_indexed failed"));
    stat = MPI_Type_commit(&mpi_type);
    if (stat) throw exception(string("mpi_binary_file::create_indexed_type"
      " call to MPI_Type_commit failed"));
    types.push_back(mpi_type);
    return mpi_type;
  }

  // MPI type using byte displacements
  template <typename Size>
  MPI_Datatype create_const_displacement(Size n)
  {
    using boost::numeric_cast;
    using std::vector;
    using DGM::exception;
    MPI_Datatype mpi_type;
    vector<int> ilen(n, 1);
    vector<MPI_Aint> byte_disp(n);
    for (Size i=0; i<n; ++i)
      byte_disp[i] = static_cast<MPI_Aint>(i) * sizeof(int);
    int stat = MPI_Type_create_hindexed(numeric_cast<int>(n), &ilen[0]
      , &byte_disp[0], mdt_int, &mpi_type);
    if (stat) throw exception(string("mpi_binary_file::create_const_displacement"
      " call to MPI_Type_create_hindexed failed"));
    MPI_Type_commit(&mpi_type);
    if (stat) throw exception(string("mpi_binary_file::create_const_displacement"
      " call to MPI_Type_commit failed"));
    types.push_back(mpi_type);
    return mpi_type;
  }

  // use this interface for non-contiguous id sequences
  template <typename ElementIter>
  MPI_Datatype create_global_displacement(ElementIter it, const ElementIter end)
  {
    using boost::numeric_cast;
    using DGM::exception;
    using DGM::global_scan;
    using std::distance;
    using std::iterator_traits;
    using std::vector;
    // value_type is type of Element id
    // typedef typename iterator_traits<ElementIter>::value_type value_type;
    typename iterator_traits<ElementIter>::difference_type n = distance(it, end);
    MPI_Datatype mpi_type;
    vector<int> ilen(n, 1);
    vector<MPI_Aint> byte_disp(n);
    global_scan(it, end, byte_disp.begin(), world);
    int stat = MPI_Type_create_hindexed(numeric_cast<int>(n), &ilen[0]
      , &byte_disp[0], mdt_int, &mpi_type);
    if (stat) throw exception(string("mpi_binary_file::create_global_displacement"
      " call to MPI_Type_create_hindexed failed"));
    stat = MPI_Type_commit(&mpi_type);
    if (stat) throw exception(string("mpi_binary_file::create_global_displacement"
      " call to MPI_Type_commit failed"));
    types.push_back(mpi_type);
    return mpi_type;
  }

  // MPI type using byte displacements
  template <typename ElementIter>
  MPI_Datatype create_displacement_type(ElementIter it, const ElementIter end)
  {
    using boost::numeric_cast;
    using DGM::exception;
    using std::distance;
    using std::iterator_traits;
    using std::vector;
    // value_type is type of Element id
    typedef typename iterator_traits<ElementIter>::value_type value_type;
    typedef typename iterator_traits<ElementIter>::difference_type difference_type;
    difference_type n = distance(it, end);
    // new mpi type
    MPI_Datatype mpi_type;
    vector<int> ilen(n, 1);
    vector<MPI_Aint> byte_disp(n);
    for (difference_type i=0; i<n; ++i, ++it)
      byte_disp[i] = static_cast<MPI_Aint>(*it) * sizeof(value_type);
    int stat = MPI_Type_create_hindexed(numeric_cast<int>(n), &ilen[0]
      , &byte_disp[0], mdt_int, &mpi_type);
    if (stat) throw exception(string("mpi_binary_file::create_displacement_type"
      " call to MPI_Type_create_hindexed failed"));
    stat = MPI_Type_commit(&mpi_type);
    if (stat) throw exception(string("mpi_binary_file::create_displacement_type"
      " call to MPI_Type_commit failed"));
    types.push_back(mpi_type);
    return mpi_type;
  }

  template <typename Size>
  MPI_Datatype create_contiguous_type(Size n) {
    using boost::numeric_cast;
    using DGM::exception;
    // n must be in bytes
    MPI_Datatype con_type;
    int stat = MPI_Type_contiguous(numeric_cast<int>(n), MPI_BYTE, &con_type);
    if (stat) throw exception(string("mpi_binary_file::create_contiguous_type"
      " call to MPI_Type_commit failed"));
    stat = MPI_Type_commit(&con_type);
    if (stat) throw exception(string("mpi_binary_file::create_contiguous_type"
      " call to MPI_Type_commit failed"));
    types.push_back(con_type);
    return con_type;
  }

  // MPI type using byte displacements and lengths
  template <typename DispIter, typename LengthIter, typename Size>
  MPI_Datatype create_displacement_type(DispIter it, const DispIter end
    , LengthIter l_it, const Size cs, MPI_Datatype con_type)
  {
    using boost::numeric_cast;
    using std::distance;
    using std::iterator_traits;
    using std::vector;
    using DGM::exception;
    //
    typedef typename vector<DispIter>::size_type size_type;
    typename iterator_traits<DispIter>::difference_type n = distance(it, end);
    MPI_Datatype mpi_type;
    vector<MPI_Aint> byte_disp(numeric_cast<size_type>(n));
    for (int i=0; i<n; ++i, ++it)
      byte_disp[i] = static_cast<MPI_Aint>(*it) * cs * sizeof(cs);
    // cast to require MPI argument type
    int stat = MPI_Type_create_hindexed(numeric_cast<int>(n), &*l_it
      , &byte_disp[0], con_type, &mpi_type);
    if (stat) throw exception(string("mpi_binary_file::create_displacement_type"
      "(5 arg) call to MPI_Type_create_hindexed failed"));
    stat = MPI_Type_commit(&mpi_type);
    if (stat) throw exception(string("mpi_binary_file::create_displacement_type"
      "(5 arg) call to MPI_Type_commit failed"));
    types.push_back(mpi_type);
    return mpi_type;
  }
};

struct cv_data {
  std::string int_name, ext_name;
  std::vector<double> args;
  cv_data() {
  }
  cv_data(const std::string in, const std::string ex)
    : int_name(in), ext_name(ex) {
  }
  cv_data(const cv_data& c)
    : int_name(c.int_name), ext_name(c.ext_name) {
  }
};

inline std::string internal_name(const cv_data& cd) {
  return cd.int_name;
}

inline std::string user_defined_name(const cv_data& cd) {
  return cd.ext_name;
}

inline vector<double>::size_type num_args(const cv_data& cd) {
  return cd.args.size();
}

inline double* arguments(cv_data& cd) {
  return &cd.args[0];
}

struct cv_file : mpi_binary_file {
  std::map<std::string, int> name_map;
  std::vector<int> is_affine;
  MPI_Offset disp;

  // interface for reading
  cv_file(const std::string fname, boost::mpi::communicator world)
    : mpi_binary_file(fname, int(0), world), disp(0) {
  }

  // interface for writing
  cv_file(const std::string fname, const int ncrv
    , boost::mpi::communicator world)
    : mpi_binary_file(fname, int(0), world, true), disp(0) {
  }

  // data in binary curve (root.cv) file
  /* Number of curve types
      each curve type has internal name, external name, zero or more arguments
      write number of arguments, then write each argument as double
      each curve type has associated zero-based index
      write number of curved sides (maybe more than one curved side per element)
      for each curved side: write gid, local side, and external name (as index)
*/
  template <typename CurveDataIter>
  void write_curve_types(CurveDataIter it, const CurveDataIter end)
  {
    using std::distance;
    // write number of curve types
    int nct = distance(it, end);
    is_affine.resize(nct, 0);
    write(nct, disp);
    // write curve types
    for (int i=0; it != end; ++it, ++i) {
      // write internal and user defined curve names
      write_string(internal_name(*it), disp);
      write_string(user_defined_name(*it), disp);
      // create map for writing curved sides
      name_map[user_defined_name(*it)] = i;
      // save whether this curve type index is affine or not
      is_affine[i] = user_defined_name(*it) == "affine" ? 1 : 0;
      // write number of arguments, then each arg as double
      int n_args = num_args(*it);
      write(n_args, disp);
      // write arguments as doubles
      MPI_File_set_view(fh, disp, MPI_DOUBLE, MPI_DOUBLE, native, info);
      MPI_File_write_all(fh, arguments(*it), n_args, MPI_DOUBLE, &status);
      disp += sizeof(double) * n_args;
    }
  }

  // Write out curved elements
  /* This interface called from Mesh::write_curve always uses local
      side 0 and a skewed curve type */
  template <typename Size, typename ElemIter, typename CurveIter,
            typename SizeIter>
  void write_curved_elements(const Size gne, const ElemIter it,
    const ElemIter end, CurveIter c_it, SizeIter s_it)
  {
#if 0
    using DGM::global_scan;
    using std::distance;
    using std::iterator_traits;
    using std::vector;
    // value_types
    typedef typename iterator_traits<SizeIter>::value_type size_vt;
    typedef typename iterator_traits<CurveIter>::value_type curve_vt;
    // write number of curved sides (global number of elements)
    write(gne, disp);
    // number of elements I own
    int ne = distance(it, end);
    // copy sizes into diplacement vector for global_scan
    vector<size_vt> displacements(s_it, s_it + ne);
    SizeIter d_it = displacements.begin();
    // compute parallel prefix using global element id and lengths
    global_scan(it, end, d_it, world);
    // write displacements
    MPI_Datatype mpi_type = create_displacement_type(it, end);
    MPI_File_set_view(fh, disp, MPI_INT, mpi_type, native, info);
    MPI_File_write_all(fh, &*d_it, ne, MPI_INT, &status);
    disp += gne;
    // write lengths
    MPI_File_set_view(fh, disp, MPI_INT, mpi_type, native, info);
    MPI_File_write_all(fh, &*s_it, ne, MPI_INT, &status);
    disp += gne;
    // get contiguous memory and mpi file type
    int cs = 2;  // two ints for each element side
    MPI_Datatype con_type = create_contiguous_type(cs * sizeof(int));
    mpi_type = create_displacement_type(d_it, d_it+ne, s_it, cs, con_type);
    // get number of curve side records
    int n = accumulate(s_it, s_it+ne, 0);
    // write sides for each element
    vector<curve_vt> csd(n*cs);
    CurveIter csd_it = csd.begin();
    // use same curve type for each side of element
    for (int i=0; i<n; ++i, ++s_it, ++c_it)
      for (size_vt j=0; j<*s_it; ++j, ++csd_it)
        *csd_it = *c_it;
    MPI_File_set_view(fh, disp, con_type, mpi_type, native, info);
    MPI_File_write_all(fh, &csd[0], n, con_type, &status);
#endif
  }

  void read_curve_types() {
    using std::string;
    // read number of curve types
    disp = 0;
    int nct = read(disp);
    is_affine.resize(nct, 0);
    // write curve types
    for (int i=0; i<nct; ++i) {
      // read internal and user defined curve names
      read_string(disp);
      string s = read_string(disp);
      // create map for writing curved sides
      name_map[s] = i;
      is_affine[i] = s == "affine" ? 1 : 0;
      // read number of arguments for this curve type
      int n_args = read(disp);
      // read arguments as doubles
      if (0 < n_args) {
#if 0
        // don't really care what they are just yet
        MPI_File_set_view(fh, disp, MPI_DOUBLE, MPI_DOUBLE, native, info);
        MPI_File_read_all(fh, arguments(*it), n_args, MPI_DOUBLE, &status);
#endif
        disp += sizeof(double) * n_args;
      }
    }
  }

  template <typename ElemIter, typename Size, typename CurveIter>
  void get_element_curvature(ElemIter g_it, const ElemIter g_end
    , const Size gne, CurveIter c_it)
  {
    using std::distance;
    using std::vector;
    // if haven't read header yet, update curve type database
    if (name_map.empty()) read_curve_types();
    // number of locally owned elements
    int ne = distance(g_it, g_end);
    // read global number of elements
    int ncs = read(disp);
    // ensure inputs are consistent
    if (ncs != gne) throw DGM::exception("Error: binary curve file gne"
      " not equal to partition global number of elements");
    // read displacements
    vector<int> displacements(ne);
    vector<int>::iterator d_it = displacements.begin();
    MPI_Datatype mpi_type = create_displacement_type(g_it, g_end);
    MPI_File_set_view(fh, disp, MPI_INT, mpi_type, native, info);
    MPI_File_read_all(fh, &*d_it, ne, MPI_INT, &status);
    disp += ncs * sizeof(int);
    // read lengths
    vector<int> lengths(ne);
    vector<int>::iterator l_it = lengths.begin();
    MPI_File_set_view(fh, disp, MPI_INT, mpi_type, native, info);
    MPI_File_read_all(fh, &*l_it, ne, MPI_INT, &status);
    disp += ncs * sizeof(int);
    // get contiguous memory and file types
    int cs = 2;  // number of ints for each curvature record
    MPI_Datatype con_type = create_contiguous_type(cs * sizeof(int));
    mpi_type = create_displacement_type(d_it, d_it+ne, l_it, cs, con_type);
    // get total length of curvature records (ne * num_sides(elem type))
    int n = accumulate(l_it, lengths.end(), 0);
    // read element side curvature records
    vector<Size> escr(n*cs);
    typename vector<Size>::iterator escr_it = escr.begin();
    MPI_File_set_view(fh, disp, con_type, mpi_type, native, info);
    MPI_File_read_all(fh, &escr[0], n, con_type, &status);
    // Update curve iterator with one curve record per element
    for (; c_it != c_it+ne; ++c_it, ++l_it) {
      // get the curve type index and use it to see if is_affine or not
      int cti = *(escr_it+1);
      *c_it = is_affine[cti];
      escr_it += *l_it;
    }
  }
};

template <typename CurveDataIter>
void write_curve_types(CurveDataIter it, const CurveDataIter end
  , const cv_file& cf)
{
  const_cast<cv_file&>(cf).write_curve_types(it, end);
}

template <typename Size, typename ElemIter, typename CurveIter
  , typename SizeIter>
void write_curved_elements(const Size gne, const ElemIter it
  , const ElemIter end, const CurveIter c_it, const SizeIter s_it, cv_file& cf)
{
  cf.write_curved_elements(gne, it, end, c_it, s_it);
}

template <typename ElemIter, typename Size, typename CurveIter>
void get_element_curvature(ElemIter g_it, const ElemIter g_end,
  const Size gne, CurveIter c_it, cv_file& cf)
{
  cf.get_element_curvature(g_it, g_end, gne, c_it);
}

struct od_file : mpi_binary_file {
  // element id, p order, q order

  // interface for reading
  od_file(const std::string fname, boost::mpi::communicator world)
    : mpi_binary_file(fname, int(0), world) {
  }

  // interface for writing
  od_file(const std::string fname, boost::mpi::communicator world, bool)
    : mpi_binary_file(fname, int(0), world, true) {
  }

  // interface for reading
  int global_number_elements() {
    MPI_Offset disp = json_disp;
    int gne = read(disp);
    return gne;
  }

  template <typename Size>
  void global_number_elements(const Size gne) {
    MPI_Offset disp = json_disp;
    write(gne, disp);
  }

  template <typename ElemIter, typename pOrderIter>
  void read_element_porder(const ElemIter it, const ElemIter end
    , pOrderIter p_it)
  {
    using boost::numeric_cast;
    using std::distance;
    using std::iterator_traits;
    typename iterator_traits<ElemIter>::difference_type n = distance(it, end);
    MPI_Offset disp = json_disp + sizeof(int);
    MPI_Datatype mpi_type = create_displacement_type(it, end);
    MPI_File_set_view(fh, disp, MPI_INT, mpi_type, native, info);
    MPI_File_read_all(fh, &*p_it, numeric_cast<int>(n), MPI_INT, &status);
  }

  template <typename ElemIter, typename pOrderIter>
  void write_element_porder(const ElemIter it, const ElemIter end
    , pOrderIter p_it)
  {
    using std::distance;
    MPI_Offset disp = json_disp + sizeof(int);
    MPI_Datatype mpi_type = create_displacement_type(it, end);
    MPI_File_set_view(fh, disp, MPI_INT, mpi_type, native, info);
    MPI_File_write_all(fh, &*p_it, distance(it, end), MPI_INT, &status);
  }

  template <typename ElemIter, typename QorderIter, typename Size>
  void element_qorder(const ElemIter it, const ElemIter end
    , const QorderIter q_it, const Size gne)
  {
    using std::distance;
    MPI_Offset disp = json_disp + sizeof(int) * (1 + gne);
    MPI_Datatype mpi_type = create_displacement_type(it, end);
    MPI_File_set_view(fh, disp, MPI_INT, mpi_type, native, info);
    MPI_File_write_all(fh, &*q_it, distance(it, end), MPI_INT, &status);
  }
};

// binary connectivity (*.cn) file
struct cn_file : mpi_binary_file {

  cn_file(const std::string fname, boost::mpi::communicator world)
    : mpi_binary_file(fname, int(0), world) {
  }

  // read data displacements
  template <typename DispIter, typename Size, typename MPI_datatype>
  void data_displacements(const DispIter it, const Size ne
    , MPI_datatype mpi_type)
  {
    using boost::numeric_cast;
    MPI_Offset disp = json_disp;
    MPI_File_set_view(fh, disp, MPI_INT, mpi_type, native, info);
    MPI_File_read_all(fh, &*it, numeric_cast<int>(ne), MPI_INT, &status);
  }

  // read data lengths
  template <typename LengthIter, typename Size, typename DiffType
    , typename MPI_datatype>
  void data_lengths(const LengthIter it, const Size gne, DiffType ne
    , MPI_datatype mpi_type)
  {
    using boost::numeric_cast;
    MPI_Offset disp = json_disp + gne * sizeof(int);
    MPI_File_set_view(fh, disp, MPI_INT, mpi_type, native, info);
    MPI_File_read_all(fh, &*it, numeric_cast<int>(ne), MPI_INT, &status);
  }

  // read connectivity (uses nrvo)
  template <typename Size>
  vector<Size> connectivity(const Size gne, const Size cs);

  // read connectivity given locally owned element ids (uses nrvo)
  template <typename ElemIter, typename Size>
  std::vector<Size> connectivity(const ElemIter e_it, const ElemIter e_end
    , const Size gne, const Size cs);
};

// binary mesh (grid) file
struct grd_file : mpi_binary_file {
  grd_file(const std::string fname, boost::mpi::communicator world)
    : mpi_binary_file(fname, int(0), world) {
  }

  // read the global number of elements
  template <typename Size>
  void global_number_elements(Size& gne) {
    MPI_Offset disp = json_disp;
    gne = read(disp);
  }

  // read number of space dimensions
  template <typename Size>
  void number_space_dimensions(Size& nsd) {
    MPI_Offset disp = json_disp + sizeof(int);
    nsd = read(disp);
  }

  // read the global data length
  int global_data_length() {
    MPI_Offset disp = json_disp + 2 * sizeof(int);
    int glen = read(disp);
    return glen;
  }

  // parallel read all the element types
  template <typename ElementIter, typename ElementTypeIter>
  void element_types(const ElementIter it, const ElementIter end
    , ElementTypeIter e_it)
  {
    // requires zero based contiguous element ids
    // requires element iterators are contiguous block of memory length lne
    using boost::numeric_cast;
    using std::distance;
    using std::iterator_traits;
    using std::vector;
    // compute file offset to begin reading
    MPI_Offset disp = json_disp + 3 * sizeof(int);
    // get number of elements on this processor (local number elements)
    typename iterator_traits<ElementIter>::difference_type
      lne = distance(it, end);
    // create displacement type
    MPI_Datatype inttype = create_displacement_type(it, end);
    MPI_File_set_view(fh, disp, MPI_INT, inttype, native, info);
    MPI_File_read_all(fh, &*e_it, numeric_cast<int>(lne), MPI_INT, &status);
  }

  // read all the element types on this rank
  template <typename ElementTypeIter>
  void element_types(ElementTypeIter e_it, const ElementTypeIter e_end) {
    using boost::numeric_cast;
    using std::iterator_traits;
    using std::distance;
    // requires ets be contiguous block of memory of length gne
    MPI_Offset disp = json_disp + 3 * sizeof(int);
    typename iterator_traits<ElementTypeIter>::difference_type
      gne = distance(e_it, e_end);
    MPI_File_set_view(fh, disp, MPI_INT, MPI_INT, native, info);
    MPI_File_read_all(fh, &*e_it, numeric_cast<int>(gne), MPI_INT, &status);
  }

  // currently hard-coded for quads, needs generalization
  template <typename ElemIter, typename CoordIter>
  void get_coordinates(ElemIter e_it, ElemIter e_end, CoordIter x_it
    , CoordIter y_it, CoordIter z_it)
  {
    using boost::numeric_cast;
    using DGM::Mesh;
    using DGM::mpiType;
    namespace Topology = DGM::Topology;
    using std::distance;
    using std::iterator_traits;
    using std::vector;
    typedef typename iterator_traits<ElemIter>::value_type Size;
    typedef typename iterator_traits<CoordIter>::value_type Scalar;
    Size gne = 0;
    global_number_elements(gne);
    Size nsd = 0;
    number_space_dimensions(nsd);
    Size glen = global_data_length();
    // displacement
    typename iterator_traits<ElemIter>::difference_type
      ne = distance(e_it, e_end);
    // skip json header
    MPI_Offset disp = json_disp + 3 * sizeof(int);
    // read element types
    vector<Topology::ElementType> etypes(ne);
    element_types(e_it, e_end, etypes.begin());
    disp += gne * sizeof(int);
    // read data displacements
    vector<int> displ(ne);
    MPI_Datatype disptype = create_displacement_type(e_it, e_end);
    MPI_File_set_view(fh, disp, MPI_INT, disptype, native, info);
    MPI_File_read_all(fh, &displ[0], numeric_cast<int>(ne), MPI_INT, &status);
    disp += gne * sizeof(int);
    // make the data lengths
    vector<Topology::ElementType>::iterator et_it = etypes.begin(),
      et_end = etypes.end();
    vector<int> lengths(ne);
    for (int i=0; et_it != et_end; ++et_it, ++i)
      lengths[i] = Mesh::nodes[*et_it];
    // create type for reading coordinates
    Scalar cs = 1;
    MPI_Datatype filetype = create_displacement_type(displ.begin(), displ.end()
      , lengths.begin(), cs, mpiType<Scalar>());
    // x coordinates
    MPI_File_set_view(fh, disp, mpiType<Scalar>(), filetype, native, info);
    MPI_File_read_all(fh, &*x_it, numeric_cast<int>(lengths[0]*ne),
      mpiType<Scalar>(), &status);
    disp += glen * sizeof(Scalar);
    if (1 < nsd) {
      // y coordinates
      MPI_File_set_view(fh, disp, mpiType<Scalar>(), filetype, native, info);
      MPI_File_read_all(fh, &*y_it, numeric_cast<int>(lengths[0]*ne),
        mpiType<Scalar>(), &status);
      disp += glen * sizeof(Scalar);
      if (2 < nsd) {
        // z coordinates
        MPI_File_set_view(fh, disp, mpiType<Scalar>(), filetype, native, info);
        MPI_File_read_all(fh, &*z_it, numeric_cast<int>(lengths[0]*ne),
          mpiType<Scalar>(), &status);
        disp += glen * sizeof(Scalar);
      }
    }
  }
};

/// \name binary mesh (grd) file interface
//@{
template <typename Size>
inline void get_global_number_elements(Size& gne, grd_file& gf) {
  gf.global_number_elements(gne);
}

template <typename Size>
void get_number_space_dimensions(Size& nsd, grd_file& gf) {
  gf.number_space_dimensions(nsd);
}

inline int get_global_data_length(grd_file& gf) {
  return gf.global_data_length();
}

template <typename ElemIter, typename CoordIter>
void get_coordinates(ElemIter e_it, ElemIter e_end, CoordIter x_it
  , CoordIter y_it, CoordIter z_it, grd_file& gf)
{
  gf.get_coordinates(e_it, e_end, x_it, y_it, z_it);
}

template <typename ElementIter, typename ElementTypeIter>
void get_element_types(const ElementIter it, const ElementIter end
  , ElementTypeIter e_it, grd_file& gf)
{
  gf.element_types(it, end, e_it);
}
//@}

/// \name binary connectivity (cn) file interface
//@{
template <typename DispIter>
void get_displacements(const DispIter it, const DispIter end, cn_file& cn) {
  using std::distance;
  int ne = distance(it, end);
  MPI_Datatype mpi_type = cn.create_const_displacement(ne);
  cn.data_displacements(it, ne, mpi_type);
}

template <typename LengthIter, typename Size>
void get_lengths(const LengthIter it, const LengthIter end, const Size gne
  , cn_file& cn)
{
  using std::distance;
  int ne = distance(it, end);
  MPI_Datatype mpi_type = cn.create_const_displacement(ne);
  cn.data_lengths(it, gne, ne, mpi_type);
}

template <typename Size>
std::vector<Size> get_connectivity(const Size gne, const Size cs, cn_file& cn) {
  // uses rvo
  return cn.connectivity(gne, cs);
}

template <typename ElemIter, typename Size>
std::vector<Size> get_connectivity(const ElemIter e_it, const ElemIter e_end
  , const Size gne, const Size cs, cn_file& cn)
{
  // uses rvo
  return cn.connectivity(e_it, e_end, gne, cs);
}
//@}

/// \name Binary order file (root.od) interface
//@{
template <typename Size>
void write_global_number_elements(const Size gne, od_file& of) {
  of.global_number_elements(gne);
}

template <typename ElemIter, typename pOrderIter>
void write_porder(const ElemIter e_it, const ElemIter e_end
  , pOrderIter p_it, od_file& of)
{
  of.write_element_porder(e_it, e_end, p_it);
}

template <typename ElemIter, typename QorderIter, typename Size>
void write_qorder(const ElemIter e_it, const ElemIter e_end
  , const QorderIter q_it, const Size gne, od_file& of)
{
  of.element_qorder(e_it, e_end, q_it, gne);
}

// read binary order file (root.od)
inline int read_global_number_elements(od_file& of) {
  return of.global_number_elements();
}

template <typename ElemIter, typename pOrderIter>
void read_porder(const ElemIter e_it, const ElemIter e_end
  , pOrderIter p_it, od_file& of)
{
  of.read_element_porder(e_it, e_end, p_it);
}

template <typename ElemIter, typename QorderIter, typename Size>
void read_qorder(const ElemIter e_it, const ElemIter e_end
  , QorderIter q_it, const Size gne , od_file& of)
{
  of.element_qorder(e_it, e_end, q_it, gne);
}
//@}

// read connectivity
template <typename Size>
std::vector<Size> cn_file::connectivity(const Size gne, const Size cs)
{
  using std::accumulate;
  using std::distance;
  using std::vector;

  // read displacements
  vector<int> displacements(gne);
  vector<int>::iterator d_it = displacements.begin();
  vector<int>::iterator d_end = displacements.end();
  get_displacements(d_it, d_end, *this);

  // read lengths
  vector<int> lengths(gne);
  vector<int>::iterator l_it = lengths.begin(), l_end = lengths.end();
  get_lengths(l_it, l_end, gne, *this);

  // skip past displacements and lengths
  MPI_Offset disp = json_disp + 2 * gne * sizeof(int);
  MPI_Datatype con_type = create_contiguous_type(cs * sizeof(int));
  MPI_Datatype mpi_type = create_displacement_type(d_it, d_end, l_it
    , cs, con_type);

  // get number of connectivity records
  int n = accumulate(l_it, l_end, 0);

  // uses nrvo
  vector<Size> conn(n*cs);
  MPI_File_set_view(fh, disp, con_type, mpi_type, native, info);
  MPI_File_read_all(fh, &conn[0], n, con_type, &status);
  return conn;
}

// read connectivity given locally owned element ids (uses nrvo)
template <typename ElemIter, typename Size>
std::vector<Size> cn_file::connectivity(const ElemIter e_it, const ElemIter e_end
  , const Size gne, const Size cs)
{
  using boost::numeric_cast;
  using std::accumulate;
  using std::distance;
  using std::iterator_traits;
  using std::runtime_error;
  using std::vector;

  // typedef typename iterator_traits<ElemIter>::value_type value_type;
  typedef typename iterator_traits<ElemIter>::difference_type difference_type;
  typedef typename vector<Size>::size_type size_type;

  // number of elements I own
  difference_type ne = distance(e_it, e_end);

  // mpi type for displacements and lengths
  MPI_Datatype mpi_type = create_displacement_type(e_it, e_end);

  // read displacements
  vector<int> displacements(ne);
  vector<int>::iterator d_it = displacements.begin();
  vector<int>::iterator d_end = displacements.end();
  data_displacements(d_it, ne, mpi_type);

  // read lengths
  vector<int> lengths(ne);
  vector<int>::iterator l_it = lengths.begin(), l_end = lengths.end();
  data_lengths(l_it, gne, ne, mpi_type);

  // get contiguous memory and file types (size of type written to file)
  MPI_Datatype con_type = create_contiguous_type(cs * sizeof(int));
  mpi_type = create_displacement_type(d_it, d_end, l_it, cs, con_type);

  // get number of connectivity records
  int n = accumulate(l_it, l_end, 0);

  // uses nrvo
  size_type st = n;
  vector<Size> conn(numeric_cast<size_type>(st*cs));
  MPI_Offset disp = json_disp + 2 * gne * sizeof(Size);
  int stat = MPI_File_set_view(fh, disp, con_type, mpi_type, native, info);
  if (0 != stat)
    throw runtime_error("MPI_File_set_view failed reading connectivity");
  stat = MPI_File_read_all(fh, &conn[0], numeric_cast<int>(n)
    , con_type, &status);
  if (0 != stat)
    throw runtime_error("MPI_File_read_all failed reading connectivity");
  return conn;
}

}  // namespace DGM

#else

namespace DGM {

inline
std::string generate_header(std::string fname, int ne, int nsd) {
  using boost::lexical_cast;
  string s = "{\n";
  s += "   \"Date\" : \"" + DGM::dateTime() + "\",\n";
  s += "   \"GlobalSize\" : \"int32\",\n";
  s += "   \"LocalSize\" : \"int32\",\n";
  s += "   \"Name\" : \"" + fname + "\",\n";
  s += "   \"Nel\" : " + lexical_cast<string>(ne) + ",\n";
  s += "   \"Nsd\" : " + lexical_cast<string>(nsd) + ",\n";
  s += "   \"Scalar\" : \"float64\",\n";
  s += "   \"Version\" : 1.0\n}";
  return s;
}

struct cn_file {
  std::ofstream ofs;
  cn_file(std::string fname, Size nsd, Size ne) {
    ofs.open(fname.c_str(), std::ios::binary | std::ios::out);
    ofs << generate_header(fname, ne, nsd);
  }
};

template <typename Iterator>
void write_connectivity(Iterator it, Iterator end, cn_file& cf) {
  for (; it != end; ++it) {
    cf.ofs << "E " << (*it).eid << " " << (*it).side << " "
      << (*it).leid << " " << (*it).lside << "\n";
  }
}

struct grd_file {
  std::ofstream ofs;
  int m_gne, m_nsd;

  // interface for writing
  grd_file(const std::string fname, Size nsd, Size ne) :
    m_gne(ne), m_nsd(nsd)
  {
    ofs.open(fname.c_str(), std::ios::binary | std::ios::out);
    ofs << generate_header(fname, ne, nsd);
  }
};

// interfaces for writing msh file
template <typename Iterator, typename Eiterator>
void write_coordinates(Iterator it, Iterator end, 
  Eiterator ei, grd_file& gf) {
}

} // namespace DGM

#endif  // DGM_PARALLEL

namespace DGM {
  // ctl_file valid in either serial or parallel since only reads Json header
  struct ctl_file {
    std::ifstream in;
    std::string fname;
    Json::Value value;
    int size;


    ctl_file(const std::string fname_) : 
      fname(fname_), size(0) 
    {
      // only open ctl file
      in.open(fname.c_str(), std::ios::binary | std::ios::in);
      // read json header
      Json::Reader reader;
      if (!reader.parse(in, value, true)) {
        throw DGM::exception("Failed to parse the ctl_file " +
          fname + ":  " + reader.getFormattedErrorMessages());
      }
    }

    ~ctl_file() {
      in.close();
    }

    template <typename T>
    bool get_tag(std::string block, std::string code, T& t) {
      // return the value associated with the tag, t is unchanged if not found
      using boost::lexical_cast;
      using DGM::scan_tag;
      using std::string;
      // find top-level block
      bool b = value.isMember(block);
      if (b) {
        // find the value associated with the code tag 
        value = value[block];
        b = value.isMember(code);
        if (b) t = value[code].asInt();
      }
      return b;
    }

    bool get_tag(std::string code, DGM::Scalar& t) {
      // return the value associated with the tag, t is unchanged if not found
      bool b = value.isMember(code);
      if (b) t = value[code].asDouble();
      return b;
    }
  };

}  // namespace DGM
#endif // DGM_BinaryFileIO_hpp
